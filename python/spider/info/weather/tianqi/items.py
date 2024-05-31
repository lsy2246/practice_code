# Define here the models for your scraped items
#
# See documentation in:
# https://docs.scrapy.org/en/latest/topics/items.html

import scrapy


class TianqiItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    pass

class WeatherItem(scrapy.Item):
    region = scrapy.Field()
    provincial = scrapy.Field()
    data_time = scrapy.Field()
    city = scrapy.Field()

    weather_1 = scrapy.Field()
    wind_direction_1 = scrapy.Field()
    wind_power_1 = scrapy.Field()
    temperature_1 = scrapy.Field()

    weather_2 = scrapy.Field()
    wind_direction_2 = scrapy.Field()
    wind_power_2 = scrapy.Field()
    temperature_2 = scrapy.Field()