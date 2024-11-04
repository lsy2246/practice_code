from typing import TypedDict, List, Dict
import requests
from requests import Response
from bs4 import BeautifulSoup, ResultSet
import numpy as np
import matplotlib.pyplot as plt

class ScrapeData(TypedDict):
    str: List[Dict[str, str]]


def spider(index: int, length: int) -> ScrapeData:
    data: ScrapeData = {}
    for i in range(length):
        url: str = f"https://quotes.toscrape.com/page/{index + i}/"
        response: Response = requests.get(url)
        soup: BeautifulSoup = BeautifulSoup(response.text, 'html.parser')
        quotes: ResultSet = soup.select('.quote')
        for quote in quotes:
            text: str = quote.select_one('.text').text
            author: str = quote.select_one('.author').text
            tags_ele: ResultSet = quote.select('.tags .tag')
            if tags_ele:
                for tag_ele in tags_ele:
                    tag: str = str(tag_ele.text)

                    pick: (List[Dict[str, str]] | None) = data.get(tag, None)
                    if pick is None:
                        data[tag]: List[Dict[str, str]] = []
                    data[tag].append({
                        "text": text,
                        "author": author
                    })
    return data


quotes = spider(1, 100)
quotes_count = np.array([len(quote) for quote in quotes.values()])
quotes_average = np.mean(quotes_count)
labels=quotes.keys()


plt.pie(quotes_count, labels=labels)
plt.title("quotes")
plt.show()

