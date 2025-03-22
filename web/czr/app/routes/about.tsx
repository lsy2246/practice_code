import type { MetaFunction } from "@remix-run/node";
import Layout from "~/components/Layout";

export const meta: MetaFunction = () => {
  return [
    { title: "关于我们 - 新纪元科技" },
    { name: "description", content: "了解新纪元科技的使命与愿景" },
  ];
};

export default function About() {
  return (
    <Layout>
      <div className="bg-gradient-to-br from-slate-50 to-white text-gray-800">
        {/* 页面标题 */}
        <div className="bg-gradient-to-r from-green-50 to-blue-50 py-20">
          <div className="max-w-7xl mx-auto px-4">
            <h1 className="text-4xl font-bold text-center bg-gradient-to-r from-green-600 to-blue-600 bg-clip-text text-transparent">
              关于我们
            </h1>
            <p className="text-center text-gray-600 mt-4 max-w-2xl mx-auto">
              致力于用科技创新推动环保事业发展
            </p>
          </div>
        </div>

        {/* 公司介绍 */}
        <div className="py-20">
          <div className="max-w-7xl mx-auto px-4">
            <div className="grid grid-cols-1 md:grid-cols-2 gap-12">
              <div className="transform transition-all duration-500 hover:scale-105">
                <h2 className="text-3xl font-bold mb-6 relative after:content-[''] after:absolute after:bottom-0 
                  after:left-0 after:w-20 after:h-1 after:bg-gradient-to-r after:from-green-500 after:to-blue-500">
                  公司简介
                </h2>
                <p className="text-gray-600 mb-4">
                  新纪元科技成立于2020年，是一家专注于环保科技创新的高新技术企业。我们致力于通过技术创新解决环境问题，推动可持续发展。
                </p>
                <p className="text-gray-600">
                  公司拥有一支专业的研发团队，在环保技术领域具有深厚的积累和创新能力。
                </p>
              </div>
              <div className="transform transition-all duration-500 hover:scale-105">
                <h2 className="text-3xl font-bold mb-8 relative after:content-[''] after:absolute after:bottom-0 
                  after:left-0 after:w-20 after:h-1 after:bg-gradient-to-r after:from-green-500 after:to-blue-500">
                  愿景使命
                </h2>
                <div className="space-y-8">
                  <div className="bg-white rounded-lg p-6 shadow-lg border border-gray-100 hover:shadow-xl transition-shadow">
                    <h3 className="text-2xl font-semibold mb-4 text-green-600 flex items-center">
                      <svg className="w-6 h-6 mr-2" fill="none" stroke="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg">
                        <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M5 3v4M3 5h4M6 17v4m-2-2h4m5-16l2.286 6.857L21 12l-5.714 2.143L13 21l-2.286-6.857L5 12l5.714-2.143L13 3z" />
                      </svg>
                      愿景
                    </h3>
                    <p className="text-gray-600 text-lg leading-relaxed">
                      成为全球领先的环保科技创新企业
                    </p>
                  </div>
                  <div className="bg-white rounded-lg p-6 shadow-lg border border-gray-100 hover:shadow-xl transition-shadow">
                    <h3 className="text-2xl font-semibold mb-4 text-blue-600 flex items-center">
                      <svg className="w-6 h-6 mr-2" fill="none" stroke="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg">
                        <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M19.428 15.428a2 2 0 00-1.022-.547l-2.387-.477a6 6 0 00-3.86.517l-.318.158a6 6 0 01-3.86.517L6.05 15.21a2 2 0 00-1.806.547M8 4h8l-1 1v5.172a2 2 0 00.586 1.414l5 5c1.26 1.26.367 3.414-1.415 3.414H4.828c-1.782 0-2.674-2.154-1.414-3.414l5-5A2 2 0 009 10.172V5L8 4z" />
                      </svg>
                      使命
                    </h3>
                    <p className="text-gray-600 text-lg leading-relaxed">
                      用科技创新守护地球家园
                    </p>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </Layout>
  );
} 