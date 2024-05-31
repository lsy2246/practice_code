import scrapy
from urllib.parse import urljoin
from ..items import WeatherItem

class WeatherSpider(scrapy.Spider):
    name = "weather"
    allowed_domains = ["www.weather.com.cn"]
    start_urls = ["http://www.weather.com.cn/textFC/hb.shtml"]

    def parse(self, response):
        areas = response.xpath('/html/body/div[4]/div[2]/div/div/ul[1]/li')
        for area in areas:
            area_suffix = area.xpath('.//a/@href').extract_first()
            area_url = urljoin(response.url, area_suffix)
            yield scrapy.Request(area_url, callback=self.each_page)

    def each_page(self, response):
        all_days_info = response.xpath("//div[@class='hanml']/div[not(@style='display: none;')]//table")
        region = response.xpath('//title/text()').get().replace('天气预报', '')
        print(f"正在爬取{region}")
        for days_info in all_days_info:
            info_trs = days_info.css('tr')

            data_time = info_trs[0].xpath(".//td[3]/text()").extract_first().replace('白天', '').replace('夜间', '')
            provincial = info_trs[2].xpath(".//td[1]/a/text()").extract_first()

            loop_count = 1
            for info_tr in info_trs:
                loop_count += 1
                if loop_count < 4:
                    continue
                if loop_count == 4:
                    city = info_tr.xpath(".//td[2]/a/text()").extract_first()

                    weather_1 = info_tr.xpath(".//td[3]/text()").extract_first()
                    wind_direction_1 = info_tr.xpath(".//td[4]/span[1]/text()").extract_first()
                    wind_power_1 = info_tr.xpath(".//td[4]/span[2]/text()").extract_first()
                    temperature_1 = (info_tr.xpath(".//td[5]/text()").extract_first())

                    weather_2 = info_tr.xpath(".//td[6]/text()").extract_first()
                    wind_direction_2 = info_tr.xpath(".//td[7]/span[1]/text()").extract_first()
                    wind_power_2 = info_tr.xpath(".//td[7]/span[2]/text()").extract_first()
                    temperature_2 = (info_tr.xpath(".//td[8]/text()").extract_first())
                else:
                    city = info_tr.xpath(".//td[1]/a/text()").extract_first()

                    weather_1 = info_tr.xpath(".//td[2]/text()").extract_first()
                    wind_direction_1 = info_tr.xpath(".//td[3]/span[1]/text()").extract_first()
                    wind_power_1 = info_tr.xpath(".//td[3]/span[2]/text()").extract_first()
                    temperature_1 = (info_tr.xpath(".//td[4]/text()").extract_first())

                    weather_2 = info_tr.xpath(".//td[5]/text()").extract_first()
                    wind_direction_2 = info_tr.xpath(".//td[6]/span[1]/text()").extract_first()
                    wind_power_2 = info_tr.xpath(".//td[6]/span[2]/text()").extract_first()
                    temperature_2 = (info_tr.xpath(".//td[7]/text()").extract_first())
                weather_item = WeatherItem()
                weather_item['region'] = region
                weather_item['provincial'] = provincial
                weather_item['data_time'] = data_time
                weather_item['city'] = city
                weather_item['weather_1'] = weather_1
                weather_item['weather_2'] = weather_2
                weather_item['wind_direction_1'] = wind_direction_1
                weather_item['wind_power_1'] = wind_power_1
                weather_item['temperature_1'] = temperature_1
                weather_item['weather_2'] = weather_2
                weather_item['wind_direction_2'] = wind_direction_2
                weather_item['wind_power_2'] = wind_power_2
                weather_item['temperature_2'] = temperature_2
                yield weather_item






