import requests
from bs4 import BeautifulSoup
from urllib.parse import urlparse, urljoin

def crawl_web(seed_url, max_depth=3):
    visited_urls = set()  # To keep track of visited URLs
    queue = [(seed_url, 0)]  # Queue of URLs to be crawled with their depth

    while queue:
        url, depth = queue.pop(0)

        if depth > max_depth:
            continue

        if url not in visited_urls:
            try:
                response = requests.get(url)
                if response.status_code == 200:
                    visited_urls.add(url)
                    print(f"Depth {depth}: Crawling {url}")

                    # Parse the HTML content of the page
                    soup = BeautifulSoup(response.text, 'html.parser')

                    # You can perform various operations with the page content here
                    # For example, extract and print page title
                    page_title = soup.title.string.strip() if soup.title else "No Title"
                    print(f"Title: {page_title}")

                    # Extract links from the page and add them to the queue
                    for link in soup.find_all('a'):
                        href = link.get('href')
                        if href and not href.startswith('#'):
                            absolute_url = urljoin(url, href)
                            queue.append((absolute_url, depth + 1))

            except Exception as e:
                print(f"Error while crawling {url}: {str(e)}")

if __name__ == "__main__":
    seed_url = "https://google.com"  # Replace with the starting URL
    max_depth = 3  # Maximum depth to crawl

    crawl_web(seed_url, max_depth)
