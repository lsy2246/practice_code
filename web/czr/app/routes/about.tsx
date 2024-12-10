import type { MetaFunction } from "@remix-run/node";
export const meta: MetaFunction = () => {
  return [
    { title: "关于我们 - 新纪元科技" },
    { name: "description", content: "了解新纪元科技的使命与愿景" },
  ];
};

export default function About() {
  return (
    <div className="min-h-screen bg-gradient-to-br from-slate-50 to-white text-gray-800">

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
              <h2 className="text-3xl font-bold mb-6 relative after:content-[''] after:absolute after:bottom-0 
                after:left-0 after:w-20 after:h-1 after:bg-gradient-to-r after:from-green-500 after:to-blue-500">
                愿景使命
              </h2>
              <div className="space-y-4">
                <div>
                  <h3 className="text-xl font-semibold mb-2">愿景</h3>
                  <p className="text-gray-600">成为全球领先的环保科技创新企业</p>
                </div>
                <div>
                  <h3 className="text-xl font-semibold mb-2">使命</h3>
                  <p className="text-gray-600">用科技创新守护地球家园</p>
                </div>
              </div>
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