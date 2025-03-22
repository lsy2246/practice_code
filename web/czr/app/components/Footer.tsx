import React from 'react';

export default function Footer() {
  return (
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
  );
}