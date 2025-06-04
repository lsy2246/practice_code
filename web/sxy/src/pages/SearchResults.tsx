import { useState, useEffect, useRef } from 'react';
import { Link, useSearchParams } from 'react-router-dom';
import { allProducts } from '../data/mockData';
import { useCart } from '../contexts/CartContext';
import Search from '../components/Search';

const SearchResults = () => {
  const [searchParams] = useSearchParams();
  const query = searchParams.get('q') || '';
  const [results, setResults] = useState<typeof allProducts>([]);
  const [loading, setLoading] = useState(true);
  const [addedProduct, setAddedProduct] = useState<number | null>(null);
  
  // 动画状态
  const [animationStartPos, setAnimationStartPos] = useState({ x: 0, y: 0 });
  const [cartIconPos, setCartIconPos] = useState({ x: 0, y: 0 });
  const cartIconRef = useRef<HTMLDivElement>(null);

  // 使用购物车上下文
  const { addToCart } = useCart();

  // 获取购物车图标位置
  useEffect(() => {
    const getCartIconPosition = () => {
      const cartIcon = document.querySelector('.cart-icon');
      if (cartIcon) {
        const rect = cartIcon.getBoundingClientRect();
        setCartIconPos({
          x: rect.left + rect.width / 2,
          y: rect.top + rect.height / 2
        });
      }
    };

    getCartIconPosition();
    // 添加窗口调整大小时更新位置的监听器
    window.addEventListener('resize', getCartIconPosition);
    return () => window.removeEventListener('resize', getCartIconPosition);
  }, []);

  // 搜索逻辑
  useEffect(() => {
    if (!query) {
      setResults([]);
      setLoading(false);
      return;
    }

    // 模拟加载
    setLoading(true);
    const timer = setTimeout(() => {
      const filtered = allProducts.filter(product => 
        product.name.toLowerCase().includes(query.toLowerCase()) ||
        product.category.toLowerCase().includes(query.toLowerCase())
      );
      setResults(filtered);
      setLoading(false);
    }, 500);

    return () => clearTimeout(timer);
  }, [query]);

  // 添加到购物车
  const handleAddToCart = (
    e: React.MouseEvent<HTMLButtonElement>,
    product: typeof allProducts[0]
  ) => {
    e.preventDefault();
    e.stopPropagation();

    // 获取按钮位置作为动画起始点
    const buttonRect = e.currentTarget.getBoundingClientRect();
    setAnimationStartPos({
      x: buttonRect.left + buttonRect.width / 2,
      y: buttonRect.top + buttonRect.height / 2
    });

    // 创建购物车项
    const cartItem = {
      id: Date.now(), // 使用时间戳作为唯一ID
      productId: product.id,
      name: product.name,
      price: product.price,
      image: product.image,
      quantity: 1,
      discount: product.discount || 0,
      size: 'M', // 默认尺码
      color: '默认' // 默认颜色
    };

    // 添加到购物车
    addToCart(cartItem);
    setAddedProduct(product.id);

    // 2秒后清除成功提示
    setTimeout(() => {
      setAddedProduct(null);
    }, 2000);
  };

  // 获取分类中文名称
  const getCategoryName = (category: string) => {
    switch (category) {
      case 'women': return '女装';
      case 'men': return '男装';
      case 'accessories': return '配饰';
      default: return category;
    }
  };

  return (
    <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-24">
      <div className="mb-8">
        <h1 className="text-2xl font-bold text-gray-900 mb-4">搜索结果: {query}</h1>
        <div className="mb-6">
          <Search />
        </div>
        {loading ? (
          <div className="flex justify-center items-center py-20">
            <div className="animate-spin rounded-full h-12 w-12 border-t-2 border-b-2 border-[#ff6b6b]"></div>
          </div>
        ) : results.length > 0 ? (
          <div>
            <p className="text-gray-600 mb-6">找到 {results.length} 个结果</p>
            <div className="grid grid-cols-1 sm:grid-cols-2 md:grid-cols-3 lg:grid-cols-4 gap-6">
              {results.map((product) => (
                <Link 
                  key={product.id} 
                  to={`/products/${product.id}`} 
                  className="group"
                >
                  <div className="bg-white rounded-lg overflow-hidden shadow-sm hover:shadow-md transition-shadow relative">
                    {product.discount && (
                      <div className="absolute top-2 left-2 z-10 bg-[#ff6b6b] text-white text-xs font-bold px-2 py-1 rounded">
                        {Math.round(product.discount * 100)}% OFF
                      </div>
                    )}
                    <div className="aspect-w-1 aspect-h-1 w-full overflow-hidden bg-gray-200 relative">
                      <img
                        src={product.image}
                        alt={product.name}
                        className="h-full w-full object-cover object-center group-hover:opacity-90 transition-opacity"
                      />
                      <div className="absolute inset-0 bg-black bg-opacity-0 group-hover:bg-opacity-10 transition-all duration-300 flex items-center justify-center">
                        <button
                          onClick={(e) => handleAddToCart(e, product)}
                          className="bg-white text-[#ff6b6b] font-medium py-2 px-4 rounded-full shadow-md transform translate-y-4 opacity-0 group-hover:translate-y-0 group-hover:opacity-100 transition-all duration-300 hover:bg-[#ff6b6b] hover:text-white"
                        >
                          加入购物车
                        </button>
                      </div>
                    </div>
                    <div className="p-4">
                      <div className="flex justify-between items-start">
                        <h3 className="text-gray-700 font-medium group-hover:text-[#ff6b6b] transition-colors">
                          {product.name}
                        </h3>
                        <span className="text-xs bg-gray-100 text-gray-600 px-2 py-1 rounded">
                          {getCategoryName(product.category)}
                        </span>
                      </div>
                      <div className="mt-2 flex items-center">
                        <span className="text-[#ff6b6b] font-bold">¥{product.price.toFixed(2)}</span>
                        {product.discount && (
                          <span className="ml-2 text-gray-400 text-sm line-through">
                            ¥{(product.price / (1 - product.discount)).toFixed(2)}
                          </span>
                        )}
                      </div>
                    </div>
                  </div>
                </Link>
              ))}
            </div>
          </div>
        ) : (
          <div className="text-center py-12">
            <svg
              className="mx-auto h-12 w-12 text-gray-400"
              fill="none"
              viewBox="0 0 24 24"
              stroke="currentColor"
              aria-hidden="true"
            >
              <path
                strokeLinecap="round"
                strokeLinejoin="round"
                strokeWidth={2}
                d="M9.172 16.172a4 4 0 015.656 0M9 10h.01M15 10h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"
              />
            </svg>
            <h3 className="mt-2 text-lg font-medium text-gray-900">未找到商品</h3>
            <p className="mt-1 text-gray-500">
              没有找到与"{query}"相关的商品，请尝试其他关键词。
            </p>
          </div>
        )}
      </div>

      {/* 用于跟踪购物车图标位置的隐藏元素 */}
      <div ref={cartIconRef} className="hidden" />

      {/* 动画元素 */}
      {addedProduct && (
        <div 
          className="fixed z-50 h-16 w-16 rounded-full animate-fly-to-cart" 
          style={{
            left: `${animationStartPos.x - 32}px`,
            top: `${animationStartPos.y - 32}px`,
            transform: `translate(${cartIconPos.x - animationStartPos.x}px, ${cartIconPos.y - animationStartPos.y}px)`,
          }}
        >
          <div className="h-full w-full bg-[#ff6b6b] rounded-full flex items-center justify-center text-white opacity-70">
            <svg xmlns="http://www.w3.org/2000/svg" className="h-8 w-8" fill="none" viewBox="0 0 24 24" stroke="currentColor">
              <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M5 13l4 4L19 7" />
            </svg>
          </div>
        </div>
      )}

      {/* 成功提示 */}
      {addedProduct && (
        <div className="fixed top-20 right-4 z-50 bg-green-100 border-l-4 border-green-500 text-green-700 p-4 rounded shadow-md animate-fade-in-down">
          <div className="flex items-center">
            <div className="py-1">
              <svg className="h-6 w-6 text-green-500 mr-4" fill="none" viewBox="0 0 24 24" stroke="currentColor">
                <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M5 13l4 4L19 7" />
              </svg>
            </div>
            <div>
              <p className="font-bold">成功添加到购物车</p>
              <p className="text-sm">您可以继续购物或前往购物车结算</p>
            </div>
          </div>
        </div>
      )}
    </div>
  );
};

export default SearchResults; 