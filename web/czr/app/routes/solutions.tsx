import type { MetaFunction } from "@remix-run/node";
import Layout from "~/components/Layout";
import { ImageLoader } from "hooks/ParticleImage";
import { useLoaderData } from "@remix-run/react";

export const meta: MetaFunction = () => {
  return [
    { title: "解决方案 - 新纪元科技" },
    { name: "description", content: "新纪元科技提供的环保科技解决方案" },
  ];
};

export const loader = () => {
  return { isClient: true };
};

export default function Solutions() {
  const { isClient } = useLoaderData<typeof loader>();

  return (
    <Layout>
      <div className="bg-gradient-to-br from-slate-50 to-white text-gray-800">
        {/* 页面标题和轮播图 */}
        <div className="bg-gradient-to-r from-green-50 to-blue-50 py-20">
          <div className="max-w-7xl mx-auto px-4">
            <div className="flex flex-col items-center">
              {isClient ? (
                <div className="w-[60px] md:w-[70px] h-[60px] md:h-[70px]">
                  {/* 轮播图代码从这里开始 */}
                </div>
              ) : (
                <div className="w-[60px] md:w-[70px] h-[60px] md:h-[70px] bg-gray-100 rounded-lg" />
              )}
              <h1 className="text-4xl font-bold text-center mt-8 bg-gradient-to-r from-green-600 to-blue-600 bg-clip-text text-transparent">
                解决方案
              </h1>
              <p className="text-center text-gray-600 mt-4 max-w-2xl mx-auto">
                为不同行业提供定制化的环保科技解决方案，助力企业实现可持续发展
              </p>
            </div>
          </div>
        </div>

        {/* 解决方案详情 */}
        <div className="py-20">
          <div className="max-w-7xl mx-auto px-4">
            <div className="grid grid-cols-1 md:grid-cols-2 gap-12">
              <div className="bg-white rounded-lg p-8 shadow-lg transform transition-all duration-300 
                hover:-translate-y-2 hover:shadow-xl border border-transparent hover:border-green-100">
                <h2 className="text-2xl font-bold mb-6 relative inline-block">
                  <span className="relative z-10">智慧城市解决方案</span>
                  <span className="absolute bottom-0 left-0 w-full h-2 bg-green-100 transform -skew-x-12"></span>
                </h2>
                <div className="space-y-4">
                  <p className="text-gray-600">通过智能技能优化城市环境管理</p>
                  <ul className="space-y-2 text-gray-600">
                    <li className="transition-all duration-200 hover:text-green-600 hover:translate-x-2">
                      • 智能环境监测系统
                    </li>
                    <li className="transition-all duration-200 hover:text-green-600 hover:translate-x-2">
                      • 城市垃圾分类管理
                    </li>
                    <li className="transition-all duration-200 hover:text-green-600 hover:translate-x-2">
                      • 智慧能源管理平台
                    </li>
                    <li className="transition-all duration-200 hover:text-green-600 hover:translate-x-2">
                      • 城市空气质量优化
                    </li>
                  </ul>
                </div>
              </div>

              <div className="bg-white rounded-lg p-8 shadow-lg transform transition-all duration-300 
                hover:-translate-y-2 hover:shadow-xl border border-transparent hover:border-green-100">
                <h2 className="text-2xl font-bold mb-6 relative inline-block">
                  <span className="relative z-10">工业节能方案</span>
                  <span className="absolute bottom-0 left-0 w-full h-2 bg-green-100 transform -skew-x-12"></span>
                </h2>
                <div className="space-y-4">
                  <p className="text-gray-600">帮助工业企业实现节能减排</p>
                  <ul className="space-y-2 text-gray-600">
                    <li className="transition-all duration-200 hover:text-green-600 hover:translate-x-2">
                      • 工业能源审计
                    </li>
                    <li className="transition-all duration-200 hover:text-green-600 hover:translate-x-2">
                      • 节能改造方案
                    </li>
                    <li className="transition-all duration-200 hover:text-green-600 hover:translate-x-2">
                      • 废物循环利用
                    </li>
                    <li className="transition-all duration-200 hover:text-green-600 hover:translate-x-2">
                      • 清洁生产技术
                    </li>
                  </ul>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </Layout>
  );
} 