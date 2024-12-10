import type { MetaFunction } from "@remix-run/node";
import { ImageLoader } from "hooks/ParticleImage";
import { useLoaderData } from "@remix-run/react";
import { Carousel } from "~/components/Carousel";

export const meta: MetaFunction = () => {
  return [
    { title: "创新技术 - 新纪元科技" },
    { name: "description", content: "新纪元科技的创新技术" },
  ];
};

export const loader = () => {
  return { 
    isClient: true,
    innovations: [
      {
        title: "智能环境监测",
        image: "/a1.jpg",
      },
      {
        title: "清洁能源技术",
        image: "/a2.jpg",
      },
      {
        title: "废物处理创新",
        image: "/a3.jpg",
      }
    ]
  };
};

export default function Innovations() {
  const { isClient, innovations } = useLoaderData<typeof loader>();

  return (
    <div className="min-h-screen bg-gradient-to-br from-slate-50 to-white text-gray-800">
      {/* 头部区域：标题 + 轮播图 */}
      <div className="relative bg-gradient-to-b from-green-50 to-blue-50/30 pt-16 pb-32 overflow-hidden">
        <div className="max-w-7xl mx-auto px-4">
          {/* 标题部分 */}
          <div className="text-center mb-16">
            <h1 className="text-5xl font-bold bg-gradient-to-r from-green-600 to-blue-600 bg-clip-text text-transparent">
              创新技术
            </h1>
            <p className="text-gray-600 mt-6 text-lg max-w-2xl mx-auto">
              引领环保科技发展，推动行业技术革新
            </p>
          </div>

          {/* 轮播图部分 */}
          {isClient ? (
            <div className="relative">
              <div className="absolute inset-0 bg-gradient-to-b from-transparent to-white/10 pointer-events-none" />
              <div className="flex justify-center">
                <div className="w-[600px]">
                  <Carousel
                    items={innovations.map((innovation) => ({
                      content: (
                        <div className="w-[600px] h-[400px] relative rounded-xl overflow-hidden">
                          <ImageLoader
                            src={innovation.image}
                            alt={innovation.title}
                            className="relative z-[1]"
                            containerClassName="w-full h-full"
                          />
                          <div className="absolute inset-0 bg-gradient-to-t from-black/70 via-black/20 to-transparent z-[2]" />
                          <div className="absolute bottom-0 left-0 right-0 p-8 z-[3]">
                            <h3 className="text-white text-3xl font-bold mb-2">{innovation.title}</h3>
                            <p className="text-white/80 text-lg">探索环保科技的无限可能</p>
                          </div>
                        </div>
                      ),
                    }))}
                    interval={5000}
                  />
                </div>
              </div>
            </div>
          ) : (
            <div className="flex justify-center">
              <div className="w-[600px] h-[400px] bg-gray-100 rounded-xl" />
            </div>
          )}
        </div>
      </div>

      {/* 技术详情部分 */}
      <div className="py-24 bg-white">
        <div className="max-w-7xl mx-auto px-4">
          <h2 className="text-4xl font-bold text-center mb-20">
            <span className="bg-gradient-to-r from-green-600 to-blue-600 bg-clip-text text-transparent">
              核心技术详解
            </span>
          </h2>
          <div className="grid grid-cols-1 md:grid-cols-3 gap-8">
            <div className="bg-white rounded-lg p-8 shadow-lg transform transition-all duration-300 
              hover:-translate-y-2 hover:shadow-xl">
              <div className="bg-green-50 w-16 h-16 rounded-full flex items-center justify-center mb-6 
                transform transition-all duration-300 hover:scale-110 hover:rotate-12">
                <svg className="w-8 h-8 text-green-600" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                  <path strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M13 10V3L4 14h7v7l9-11h-7z" />
                </svg>
              </div>
              <h3 className="text-xl font-bold mb-4 relative">
                <span className="relative z-10">AI环境优化</span>
                <span className="absolute bottom-0 left-0 w-full h-2 bg-green-100 transform -skew-x-12"></span>
              </h3>
              <p className="text-gray-600">
                运用人工智能技术，实现环境数据的智能分析和决策优化，提供精准的环境治理方案。
              </p>
            </div>

            <div className="bg-white rounded-lg p-8 shadow-lg transform transition-all duration-300 
              hover:-translate-y-2 hover:shadow-xl">
              <div className="bg-blue-50 w-16 h-16 rounded-full flex items-center justify-center mb-6 
                transform transition-all duration-300 hover:scale-110 hover:rotate-12">
                <svg className="w-8 h-8 text-blue-600" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                  <path strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M20 7l-8-4-8 4m16 0l-8 4m8-4v10l-8 4m0-10L4 7m8 4v10M4 7v10l8 4" />
                </svg>
              </div>
              <h3 className="text-xl font-bold mb-4 relative">
                <span className="relative z-10">清洁能源转换</span>
                <span className="absolute bottom-0 left-0 w-full h-2 bg-blue-100 transform -skew-x-12"></span>
              </h3>
              <p className="text-gray-600">
                创新的能源转换技术，提高清洁能源利用效率，推动色能源革命。
              </p>
            </div>

            <div className="bg-white rounded-lg p-8 shadow-lg transform transition-all duration-300 
              hover:-translate-y-2 hover:shadow-xl">
              <div className="bg-purple-50 w-16 h-16 rounded-full flex items-center justify-center mb-6 
                transform transition-all duration-300 hover:scale-110 hover:rotate-12">
                <svg className="w-8 h-8 text-purple-600" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                  <path strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M9 12l2 2 4-4m5.618-4.016A11.955 11.955 0 0112 2.944a11.955 11.955 0 01-8.618 3.04A12.02 12.02 0 003 9c0 5.591 3.824 10.29 9 11.622 5.176-1.332 9-6.03 9-11.622 0-1.042-.133-2.052-.382-3.016z" />
                </svg>
              </div>
              <h3 className="text-xl font-bold mb-4 relative">
                <span className="relative z-10">生态修复系统</span>
                <span className="absolute bottom-0 left-0 w-full h-2 bg-purple-100 transform -skew-x-12"></span>
              </h3>
              <p className="text-gray-600">
                综合性生态环境修复解决方案，助力自然生态系统恢复与保护
              </p>
            </div>
          </div>
        </div>
      </div>

      {/* 页脚 */}
      <footer className="bg-gray-900 text-white py-12">
        {/* 同首页页脚内容 */}
      </footer>
    </div>
  );
} 