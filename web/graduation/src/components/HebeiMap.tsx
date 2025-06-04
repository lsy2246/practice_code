import { useEffect, useRef, useState } from "react";
import * as echarts from "echarts";
import hebeiJson from "../assets/hebei.json";

// 定义正确的GeoJSON类型
interface GeoJSONFeature {
  type: "Feature";
  properties: {
    name: string;
    [key: string]: any;
  };
  geometry: any;
}

interface GeoJSONFeatureCollection {
  type: "FeatureCollection";
  features: GeoJSONFeature[];
}

interface Article {
  title: string;
  description: string;
  city: string[];
  slug: string;
  type: string;
}

interface HebeiMapProps {
  articles: Article[];
}

// ECharts事件参数类型
interface EChartsClickParams {
  name: string;
  value?: any;
  dataIndex?: number;
  seriesIndex?: number;
  data?: any;
  [key: string]: any;
}

const HebeiMap = ({ articles }: HebeiMapProps) => {
  const mapRef = useRef<HTMLDivElement>(null);
  const [selectedCity, setSelectedCity] = useState<string>("");
  const [filteredArticles, setFilteredArticles] = useState<Article[]>([]);
  const [isMobile, setIsMobile] = useState<boolean>(false);
  const [chart, setChart] = useState<echarts.ECharts | null>(null);
  const [isDarkMode, setIsDarkMode] = useState<boolean>(false);

  // 记录上次点击的城市，用于比较
  const lastClickedCity = useRef<string>("");

  // 检测是否为移动设备
  useEffect(() => {
    const checkMobile = () => {
      const mobile = window.innerWidth < 768;
      setIsMobile(mobile);
    };

    checkMobile();
    window.addEventListener("resize", checkMobile);

    return () => {
      window.removeEventListener("resize", checkMobile);
    };
  }, []);

  // 检测暗黑模式
  useEffect(() => {
    const checkDarkMode = () => {
      // 检查HTML元素是否有dark类
      const isDark = document.documentElement.classList.contains("dark");
      setIsDarkMode(isDark);
    };

    checkDarkMode();

    // 创建一个观察器来监听HTML元素的class变化
    const observer = new MutationObserver((mutations) => {
      mutations.forEach((mutation) => {
        if (mutation.attributeName === "class") {
          checkDarkMode();
        }
      });
    });

    observer.observe(document.documentElement, { attributes: true });

    return () => {
      observer.disconnect();
    };
  }, []);

  // 地图初始化
  useEffect(() => {
    if (!mapRef.current) return;

    // 确保GeoJSON格式正确
    const geoJson: GeoJSONFeatureCollection = {
      type: "FeatureCollection",
      features: hebeiJson.features.map((feature) => ({
        type: "Feature",
        properties: feature.properties,
        geometry: feature.geometry,
      })),
    };

    // 注册地图数据
    echarts.registerMap("hebei", geoJson);

    // 解决移动端多次初始化问题
    if (chart) {
      chart.dispose();
    }

    const newChart = echarts.init(mapRef.current);
    setChart(newChart);

    const option = {
      backgroundColor: "transparent",
      tooltip: {
        show: false,
      },
      series: [
        {
          name: "河北省",
          type: "map",
          map: "hebei",
          roam: isMobile, // 移动端允许缩放和平移
          zoom: isMobile ? 1.2 : 1, // 移动端稍微放大一点
          itemStyle: {
            normal: {
              areaColor: isDarkMode ? "#334155" : "#e0f3f8",
              borderColor: isDarkMode ? "#475569" : "#fff",
            },
            emphasis: {
              areaColor: isDarkMode ? "#3b82f6" : "#74add1",
            },
          },
          label: {
            show: true,
            fontSize: isMobile ? 10 : 12,
            color: isDarkMode ? "#e2e8f0" : "#1e293b",
          },
          emphasis: {
            label: {
              show: true,
              color: isDarkMode ? "#ffffff" : "#000000",
            },
          },
          data: hebeiJson.features.map((feature) => ({
            name: feature.properties.name,
            value: 0,
          })),
        },
      ],
    };

    newChart.setOption(option);

    // 点击事件处理 - 修改为点击同一城市时取消选择
    const clickHandler = (params: EChartsClickParams) => {
      const cityName = params.name.replace("市", "");

      // 如果点击的是已选中的城市，则取消选择
      if (cityName === lastClickedCity.current) {
        lastClickedCity.current = "";
        setSelectedCity("");
        setFilteredArticles([]);
      } else {
        // 否则选中新城市并筛选文章
        lastClickedCity.current = cityName;
        setSelectedCity(cityName);
        const cityArticles = articles.filter((article) =>
          article.city.some((city) => city.includes(cityName)),
        );
        setFilteredArticles(cityArticles);
      }
    };

    // 移除之前的点击事件（防止重复绑定）
    newChart.off("click");
    newChart.on("click", clickHandler);

    // 清理函数
    return () => {
      newChart.off("click");
      newChart.dispose();
    };
  }, [articles, isMobile, isDarkMode]); // 添加isDarkMode到依赖项

  // 窗口大小变化时调整地图大小
  useEffect(() => {
    if (chart) {
      chart.resize();
    }
  }, [isMobile, chart]);

  // 获取文章类型对应的图标
  const getTypeIcon = (type: string) => {
    switch (type) {
      case "attractions":
        return "🏛️";
      case "culture":
        return "🎭";
      case "cuisine":
        return "🍜";
      case "travel":
        return "🏞️";
      default:
        return "📄";
    }
  };

  return (
    <div className="container mx-auto px-4">
      <div className="grid grid-cols-1 md:grid-cols-3 gap-4">
        <div className="md:col-span-2">
          <div
            ref={mapRef}
            style={{
              height: isMobile ? "400px" : "600px",
              width: "100%",
            }}
          />
        </div>
        <div
          className={`md:col-span-1 ${isMobile && selectedCity ? "mt-4" : ""}`}
        >
          {selectedCity ? (
            <div className="bg-white dark:bg-slate-800 p-4 rounded-sm shadow border border-slate-200 dark:border-slate-700">
              <div className="flex justify-between items-center mb-4">
                <h2 className="text-xl font-bold text-slate-800 dark:text-primary-200">
                  {selectedCity}相关文章
                </h2>
                <button
                  onClick={(e) => {
                    e.stopPropagation(); // 阻止事件冒泡
                    lastClickedCity.current = ""; // 重置上次点击的城市
                    setSelectedCity("");
                    setFilteredArticles([]);
                  }}
                  className="text-slate-500 dark:text-slate-400 hover:text-slate-700 dark:hover:text-slate-200 p-2"
                >
                  ✕
                </button>
              </div>
              {filteredArticles.length > 0 ? (
                <ul className="space-y-4 max-h-[500px] overflow-y-auto">
                  {filteredArticles.map((article, index) => (
                    <li
                      key={index}
                      className="border-b border-slate-200 dark:border-slate-700 pb-2 hover:bg-slate-50 dark:hover:bg-slate-700/30 transition-colors cursor-pointer"
                      onClick={(e) => {
                        e.stopPropagation(); // 阻止事件冒泡
                        window.location.href = article.slug;
                      }}
                    >
                      <div className="flex items-start gap-2">
                        <span className="text-xl">
                          {getTypeIcon(article.type)}
                        </span>
                        <div>
                          <h3 className="font-semibold text-slate-800 dark:text-slate-200 hover:text-primary-600 dark:hover:text-primary-400">
                            {article.title}
                          </h3>
                          <p className="text-slate-600 dark:text-slate-400 text-sm">
                            {article.description}
                          </p>
                        </div>
                      </div>
                    </li>
                  ))}
                </ul>
              ) : (
                <p className="text-slate-500 dark:text-slate-400">
                  暂无相关文章
                </p>
              )}
            </div>
          ) : (
            <div className="bg-white dark:bg-slate-800 p-4 rounded-sm shadow border border-slate-200 dark:border-slate-700">
              <p className="text-slate-500 dark:text-slate-400 text-center">
                点击地图选择城市查看相关文章
              </p>
            </div>
          )}
        </div>
      </div>
    </div>
  );
};

export default HebeiMap;
