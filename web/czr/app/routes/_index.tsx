import type { MetaFunction } from "@remix-run/node";
import Layout from "~/components/Layout";
import HomeCarousel from "~/components/HomeCarousel";

export const meta: MetaFunction = () => {
  return [
    { title: "新纪元科技 - 引领创新未来" },
    { name: "description", content: "专注于环保科技创新，为可持续发展提供解决方案" },
  ];
};

export default function Index() {
  return (
    <Layout>
      <div className="bg-gradient-to-br from-slate-50 to-white text-gray-800">
        {/* Hero区域 */}
        <div className="relative overflow-hidden bg-gradient-to-r from-green-50 to-blue-50">
          <div className="max-w-7xl mx-auto px-4 pt-8">
            <HomeCarousel />
            <div className="text-center py-12">
              <h1 className="text-5xl font-bold mb-6 bg-gradient-to-r from-green-600 to-blue-600 bg-clip-text text-transparent">
                创新科技，守护地球
              </h1>
              <p className="text-xl text-gray-600 max-w-2xl mx-auto mb-10">
                致力于开发环保科技解决方案，用创新力量推动可持续发展
              </p>
              <button className="bg-gradient-to-r from-green-600 to-blue-600 text-white px-8 py-3 rounded-full font-semibold 
                hover:opacity-90 transition-all duration-300 hover:scale-105 hover:shadow-lg">
                了解更多
              </button>
            </div>
          </div>
        </div>
      </div>
    </Layout>
  );
} 