import xml.etree.ElementTree as ET
import networkx as nx

# Step 1: Parse XML
def parse_xml(xml_string):
    root = ET.fromstring(xml_string)
    pages = root.findall('.//page')
    page_data = {}

    for page in pages:
        url = page.find('url').text
        links = [link.text for link in page.findall('.//link')]
        page_data[url] = links

    return page_data

# Step 2: Generate Web Graph
def generate_web_graph(page_data):
    graph = nx.DiGraph()

    for url, links in page_data.items():
        for link in links:
            graph.add_edge(url, link)

    return graph

# Step 3: Compute Topic-Specific Page Ranks
def topic_specific_page_rank(graph, topic, damping_factor=0.85, max_iterations=100, tol=1e-6):
    num_pages = len(graph)
    initial_rank = 1.0 / num_pages
    ranks = {page: initial_rank for page in graph.nodes()}

    for _ in range(max_iterations):
        new_ranks = {}
        total_diff = 0

        for page in graph.nodes():
            rank = (1 - damping_factor) / num_pages

            for neighbor in graph.neighbors(page):
                if neighbor == topic:
                    rank += damping_factor * (ranks[neighbor] / len(graph.neighbors(neighbor)))

            new_ranks[page] = rank
            total_diff += abs(new_ranks[page] - ranks[page])

        ranks = new_ranks

        if total_diff < tol:
            break

    return ranks

# Sample XML data
xml_data = """
<web>
    <page>
        <url>https://en.wikipedia.org/wiki/Blockchain</url>
        <content>Blockchain</content>
        <links>
            <link>https://en.wikipedia.org/wiki/Distributed_ledger</link>
            <link>https://en.wikipedia.org/wiki/Cryptographic_hash_function</link>
            <link>https://en.wikipedia.org/wiki/Consensus_(computer_science)</link>
        </links>
    </page>
    <page>
        <url>https://en.wikipedia.org/wiki/Climate_change</url>
        <content>Global Warming</content>
        <links>
            <link>https://en.wikipedia.org/wiki/Global_warming_(disambiguation)</link>
            <link>https://en.wikipedia.org/wiki/Climate_variability_and_change</link>
        </links>
    </page>
     <page>
        <url>https://www.investopedia.com/terms/b/blockchain.asp</url>
        <content>Blockchain</content>
        <links>
            <link>https://www.investopedia.com/10-biggest-blockchain-companies-5213784</link>
            <link>https://www.investopedia.com/what-are-layer-1-and-layer-2-blockchain-scaling-solutions-7104877</link>
        </links>
    </page>
</web>
"""

try:
    # Step 1: Parse XML
    page_data = parse_xml(xml_data)

    # Step 2: Generate Web Graph
    web_graph = generate_web_graph(page_data)

    # Step 3: Compute Topic-Specific Page Ranks
    topic = 'https://en.wikipedia.org/wiki/Blockchain'
    page_ranks = topic_specific_page_rank(web_graph, topic)

    # Now, you have the topic-specific page ranks for each page in the web graph.
    for page, rank in page_ranks.items():
        print(f"Page: {page}, Page Rank: {rank}")

except Exception as e:
    print(f"An unexpected error occurred: {str(e)}")
