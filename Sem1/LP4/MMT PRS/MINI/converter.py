import tkinter as tk
from tkinter import filedialog
from PIL import Image
import PIL
import os

def compress_image(image, infile):
    size = 1920, 1080
    width = 1920
    height = 1080

    name = infile.split('.')
    first_name = name[0] + '.jpg'
    if image.size[0] > width and image.size[1] > height:
        image.thumbnail(size, Image.ANTIALIAS)
        image.save(first_name, quality=85)
    elif image.size[0] > width:
        wpercent = (width/float(image.size[0]))
        height = int((float(image.size[1])*float(wpercent)))
        image = image.resize((width,height), PIL.Image.ANTIALIAS)
        image.save(first_name, quality=85)
    elif image.size[1] > height:
        wpercent = (height/float(image.size[1]))
        width = int((float(image.size[0])*float(wpercent)))
        image = image.resize((width,height), PIL.Image.ANTIALIAS)
        image.save(first_name, quality=85)
    else:
        image.save(first_name, quality=85)

def process_image():
    file_path = filedialog.askopenfilename(filetypes=[("Image files", "*.png *.bmp *.gif")])
    if not file_path:
        return

    img = Image.open(file_path)

    if img.format == "JPEG":
        image = img.convert('RGB')
        compress_image(image, file_path)
    elif img.format == "GIF":
        i = img.convert("RGBA")
        bg = Image.new("RGBA", i.size)
        image = Image.composite(i, bg, i)
        compress_image(image, file_path)
    elif img.format == "PNG":
        try:
            image = Image.new("RGB", img.size, (255, 255, 255))
            image.paste(img, img)
            compress_image(image, file_path)
        except ValueError:
            image = img.convert('RGB')
            compress_image(image, file_path)
    elif img.format == "BMP":
        image = img.convert('RGB')
        compress_image(image, file_path)

    # Display a message indicating that the image has been processed
    result_label.config(text="Image processed and saved as .jpg")

# Create the main application window
root = tk.Tk()
root.title("Image Processor")

# Create a button to trigger image processing
process_button = tk.Button(root, text="Process Image", command=process_image)
process_button.pack(pady=10)

# Create a label to display processing result
result_label = tk.Label(root, text="", fg="green")
result_label.pack()

# Start the GUI application
root.mainloop()