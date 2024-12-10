import type { MetaFunction } from "@remix-run/node";

export const meta: MetaFunction = () => {
  return [
    { title: "新纪元科技 - 引领创新未来" },
    { name: "description", content: "专注于环保科技创新，为可持续发展提供解决方案" },
  ];
};

export default function Index() {
  return (
    <div className="min-h-screen bg-gradient-to-br from-slate-50 to-white text-gray-800">

      {/* Hero区域 */}
      <div className="relative overflow-hidden bg-gradient-to-r from-green-50 to-blue-50">
        <div className="max-w-7xl mx-auto px-4 py-24">
          <div className="text-center">
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

      {/* 核心技术 */}
      <section className="py-20 bg-white" id="innovations">
        <div className="max-w-7xl mx-auto px-4">
          <h2 className="text-3xl font-bold text-center mb-16">核心创新技术</h2>
          <div className="grid grid-cols-1 md:grid-cols-3 gap-12">
            <div className="text-center group transform transition-all duration-300 hover:-translate-y-2 hover:shadow-xl rounded-xl p-6">
              <div className="bg-green-50 w-20 h-20 rounded-full flex items-center justify-center mx-auto mb-6 
                group-hover:bg-green-100 transition-colors duration-300 group-hover:scale-110">
                <svg className="w-10 h-10 text-green-600" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                  <path strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M13 10V3L4 14h7v7l9-11h-7z" />
                </svg>
              </div>
              <h3 className="text-xl font-semibold mb-4">智能环保系统</h3>
              <p className="text-gray-600">采用AI技术优化资源利用，提高能源使用效率</p>
            </div>
            
            <div className="text-center group transform transition-all duration-300 hover:-translate-y-2 hover:shadow-xl rounded-xl p-6">
              <div className="bg-blue-50 w-20 h-20 rounded-full flex items-center justify-center mx-auto mb-6 
                group-hover:bg-blue-100 transition-colors duration-300 group-hover:scale-110">
                <svg className="w-10 h-10 text-blue-600" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                  <path strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M20 7l-8-4-8 4m16 0l-8 4m8-4v10l-8 4m0-10L4 7m8 4v10M4 7v10l8 4" />
                </svg>
              </div>
              <h3 className="text-xl font-semibold mb-4">新能源转换</h3>
              <p className="text-gray-600">创新能源转换技术，实现清洁能源的高效利用</p>
            </div>

            <div className="text-center group transform transition-all duration-300 hover:-translate-y-2 hover:shadow-xl rounded-xl p-6">
              <div className="bg-cyan-50 w-20 h-20 rounded-full flex items-center justify-center mx-auto mb-6 
                group-hover:bg-cyan-100 transition-colors duration-300 group-hover:scale-110">
                <svg className="w-10 h-10 text-cyan-600" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                  <path strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M9 12l2 2 4-4m5.618-4.016A11.955 11.955 0 0112 2.944a11.955 11.955 0 01-8.618 3.04A12.02 12.02 0 003 9c0 5.591 3.824 10.29 9 11.622 5.176-1.332 9-6.03 9-11.622 0-1.042-.133-2.052-.382-3.016z" />
                </svg>
              </div>
              <h3 className="text-xl font-semibold mb-4">生态监测</h3>
              <p className="text-gray-600">全方位环境监测系统，保护生态平衡</p>
            </div>
          </div>
        </div>
      </section>

      {/* 解决方案 */}
      <section className="py-20 bg-gradient-to-r from-green-50 to-blue-50" id="solutions">
        <div className="max-w-7xl mx-auto px-4">
          <h2 className="text-3xl font-bold text-center mb-16">创新解决方案</h2>
          <div className="grid grid-cols-1 md:grid-cols-2 gap-8">
            <div className="bg-white rounded-lg p-8 shadow-sm hover:shadow-xl transition-all duration-300 hover:-translate-y-1">
              <h3 className="text-xl font-semibold mb-4">智慧城市环保系统</h3>
              <p className="text-gray-600 mb-4">整合城市环境数据，提供智能化环保解决方案</p>
              <ul className="text-gray-600 space-y-2">
                <li>• 空气质量实时监测</li>
                <li>• 智能垃圾分类系统</li>
                <li>• 城市能源管理优化</li>
              </ul>
            </div>
            
            <div className="bg-white rounded-lg p-8 shadow-sm hover:shadow-xl transition-all duration-300 hover:-translate-y-1">
              <h3 className="text-xl font-semibold mb-4">工业节能方案</h3>
              <p className="text-gray-600 mb-4">为工业企业提供全方位的节能减排解决方案</p>
              <ul className="text-gray-600 space-y-2">
                <li className="transition-all duration-200 hover:text-green-600 hover:translate-x-2">• 能源使用效率优化</li>
                <li className="transition-all duration-200 hover:text-green-600 hover:translate-x-2">• 废物循环利用系统</li>
                <li className="transition-all duration-200 hover:text-green-600 hover:translate-x-2">• 清洁生产技术改造</li>
              </ul>
            </div>
          </div>
        </div>
      </section>

      {/* 页脚 */}
      <footer className="bg-gray-900 text-white py-12">
        <div className="max-w-7xl mx-auto px-4">
          <div className="grid grid-cols-1 md:grid-cols-4 gap-8">
            <div>
              <h4 className="text-lg font-semibold mb-4">关于我们</h4>
              <p className="text-gray-400">新纪元科技致力于环保科技创新，为地球可持续发展贡献力量</p>
            </div>
            <div>
              <h4 className="text-lg font-semibold mb-4">联系方式</h4>
              <p className="text-gray-400">电话：400-888-8888</p>
              <p className="text-gray-400">邮箱：contact@xingjiyuan.com</p>
            </div>
            <div>
              <h4 className="text-lg font-semibold mb-4">解决方案</h4>
              <ul className="text-gray-400 space-y-2">
                <li>
                  <a href="#" className="hover:text-white transition-colors duration-200 hover:translate-x-2 inline-block">
                    智慧城市
                  </a>
                </li>
                <li>
                  <a href="#" className="hover:text-white transition-colors duration-200 hover:translate-x-2 inline-block">
                    工业节能
                  </a>
                </li>
                <li>
                  <a href="#" className="hover:text-white transition-colors duration-200 hover:translate-x-2 inline-block">
                    生态监测
                  </a>
                </li>
              </ul>
            </div>
            <div>
              <h4 className="text-lg font-semibold mb-4">公司地址</h4>
              <p className="text-gray-400">中国上海市浦东新区科技创新大道888号</p>
            </div>
          </div>
          <div className="border-t border-gray-800 mt-8 pt-8 text-center text-gray-400">
            <p>© 2024 新纪元科技 版权所有</p>
          </div>
        </div>
      </footer>
    </div>
  );
} 