import { Link } from 'react-router-dom';

const NotFound = () => {
  return (
    <div className="container mx-auto px-4 py-16 text-center">
      <div className="max-w-md mx-auto">
        <h1 className="text-9xl font-bold text-[#1a365d]">404</h1>
        <h2 className="text-3xl font-bold mt-6 mb-4">页面未找到</h2>
        <p className="text-gray-600 mb-8">
          抱歉，您访问的页面不存在或已被移除。
        </p>
        <Link
          to="/"
          className="inline-block bg-[#1a365d] text-white py-3 px-8 rounded-md hover:bg-[#2a4365] transition-colors"
        >
          返回首页
        </Link>
      </div>
      
      <div className="mt-16">
        <h3 className="text-xl font-medium mb-6">您可能想要查找：</h3>
        <div className="flex flex-wrap justify-center gap-4">
          <Link
            to="/products"
            className="bg-gray-100 text-gray-800 hover:bg-gray-200 px-4 py-2 rounded-md transition-colors"
          >
            所有商品
          </Link>
          <Link
            to="/products?category=women"
            className="bg-gray-100 text-gray-800 hover:bg-gray-200 px-4 py-2 rounded-md transition-colors"
          >
            女装
          </Link>
          <Link
            to="/products?category=men"
            className="bg-gray-100 text-gray-800 hover:bg-gray-200 px-4 py-2 rounded-md transition-colors"
          >
            男装
          </Link>
          <Link
            to="/products?category=accessories"
            className="bg-gray-100 text-gray-800 hover:bg-gray-200 px-4 py-2 rounded-md transition-colors"
          >
            配饰
          </Link>
          <Link
            to="/products?featured=true"
            className="bg-gray-100 text-gray-800 hover:bg-gray-200 px-4 py-2 rounded-md transition-colors"
          >
            热卖商品
          </Link>
        </div>
      </div>
    </div>
  );
};

export default NotFound; 