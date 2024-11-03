import requests
from bs4 import BeautifulSoup
import pandas as pd
def spider(url):
    headers={"user-agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/130.0.0.0 Safari/537.36"}
    respond=requests.get(url, headers=headers)

    soup=BeautifulSoup(respond.text,'html.parser')
    
    data=[]
    for item in soup.select('.item'):
        href = item.select_one('.nbg')['href']
        img = item.select_one('.nbg img')['src']
        name_filed = item.select_one('.pl2')
        title = name_filed.find('a')['title']
        state = name_filed.find('img') 
        if ( state is not None):
            state = name_filed.find('img')['src']
        author = item.select_one('.pl').text.split('/')[0]
        grade = item.select_one('.rating_nums').text

        data.append({
            'href':href,
            'img':img,
            'title':title,
            'state':state,
            'author':author,
            'grade':grade
            })
    return data
data = []
for i in range(11):
    url=f"https://book.douban.com/top250?start={25*i}"
    info=spider(url)
    data+=info
df = pd.DataFrame(data)
new_df = df.dropna(subset=['state'])

print(new_df.state)
