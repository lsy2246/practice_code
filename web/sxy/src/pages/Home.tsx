import { useState, useEffect } from 'react';
import { Link } from 'react-router-dom';
import { carouselItems, categories, allProducts } from '../data/mockData';
import { useCart } from '../contexts/CartContext';

const Home = () => {
  const [currentSlide, setCurrentSlide] = useState(0);
  const [addedProduct, setAddedProduct] = useState<number | null>(null);
  const [animationItem, setAnimationItem] = useState<{
    id: number, 
    startX: number, 
    startY: number, 
    endX: number, 
    endY: number
  } | null>(null);
  
  // 使用购物车上下文
  const { addToCart } = useCart();

  // 筛选出热卖商品
  const featuredProducts = allProducts.filter(product => product.featured);

  // 自动轮播
  useEffect(() => {
    const interval = setInterval(() => {
      setCurrentSlide((prev) => (prev + 1) % carouselItems.length);
    }, 5000);
    return () => clearInterval(interval);
  }, []);

  // 手动切换轮播图
  const goToSlide = (index: number) => {
    setCurrentSlide(index);
  };

  // 添加商品到购物车
  const handleAddToCart = (product: typeof allProducts[0], event: React.MouseEvent) => {
    event.preventDefault();
    event.stopPropagation();
    
    // 获取点击按钮的位置
    const buttonRect = (event.currentTarget as HTMLElement).getBoundingClientRect();
    
    // 获取购物车图标的位置
    const cartIcon = document.querySelector('.cart-icon') as HTMLElement;
    if (!cartIcon) return;
    
    const cartRect = cartIcon.getBoundingClientRect();
    
    // 设置动画起始位置和目标位置
    setAnimationItem({
      id: product.id,
      startX: buttonRect.left + buttonRect.width / 2,
      startY: buttonRect.top + buttonRect.height / 2,
      endX: cartRect.left + cartRect.width / 2,
      endY: cartRect.top + cartRect.height / 2
    });
    
    // 创建购物车商品对象
    const cartItem = {
      id: Date.now(),
      productId: product.id,
      name: product.name,
      price: product.price,
      image: product.image,
      discount: product.discount,
      quantity: 1,
    };
    
    // 延迟添加到购物车，等待动画完成
    setTimeout(() => {
      // 添加到购物车
      addToCart(cartItem);
      
      // 显示添加成功提示
      setAddedProduct(product.id);
      setTimeout(() => setAddedProduct(null), 2000);
      
      // 清除动画状态
      setTimeout(() => {
        setAnimationItem(null);
      }, 1000);
    }, 800);
  };

  return (
    <div>
      {/* 添加到购物车成功提示 */}
      {addedProduct !== null && (
        <div className="fixed top-20 right-4 bg-green-100 border border-green-400 text-green-700 px-4 py-3 rounded z-50 shadow-md animate-fade-in-down">
          <div className="flex items-center">
            <svg className="w-5 h-5 mr-2" fill="currentColor" viewBox="0 0 20 20">
              <path fillRule="evenodd" d="M10 18a8 8 0 100-16 8 8 0 000 16zm3.707-9.293a1 1 0 00-1.414-1.414L9 10.586 7.707 9.293a1 1 0 00-1.414 1.414l2 2a1 1 0 001.414 0l4-4z" clipRule="evenodd" />
            </svg>
            <p>商品已添加到购物车</p>
          </div>
        </div>
      )}

      {/* 飞入购物车动画元素 */}
      {animationItem && (
        <div 
          className="fixed z-[9999] w-16 h-16 rounded-full shadow-lg pointer-events-none"
          style={{
            left: animationItem.startX - 32, // 32 = width/2
            top: animationItem.startY - 32, // 32 = height/2
            backgroundImage: `url(${featuredProducts.find(p => p.id === animationItem.id)?.image})`,
            backgroundSize: 'cover',
            backgroundPosition: 'center',
            animation: 'fly-to-cart 1s forwards cubic-bezier(0.18, 0.89, 0.32, 1.28)',
            transform: 'scale(1)',
            transition: 'transform 1s cubic-bezier(0.18, 0.89, 0.32, 1.28)',
            // 动态计算飞行轨迹
            '--end-x': `${animationItem.endX - animationItem.startX}px`,
            '--end-y': `${animationItem.endY - animationItem.startY}px`
          } as React.CSSProperties}
          onAnimationStart={(e) => {
            // 设置动画目标位置
            const element = e.currentTarget as HTMLElement;
            element.style.setProperty('transform', `translate(var(--end-x), var(--end-y)) scale(0.1)`);
          }}
        ></div>
      )}

      {/* Hero Carousel */}
      <section className="relative h-[600px] overflow-hidden">
        {carouselItems.map((item, index) => (
          <div
            key={item.id}
            className={`absolute inset-0 transition-opacity duration-1000 ${
              index === currentSlide ? 'opacity-100' : 'opacity-0 pointer-events-none'
            }`}
          >
            <div className="absolute inset-0 bg-black/30 z-10"></div>
            <img
              src={item.image}
              alt={item.title}
              className="w-full h-full object-cover"
            />
            <div className="absolute inset-0 flex items-center z-20">
              <div className="container mx-auto px-4">
                <div className="max-w-xl">
                  <h1 className="text-4xl md:text-5xl font-bold text-white mb-4">{item.title}</h1>
                  <p className="text-xl text-white mb-8">{item.description}</p>
                  <a
                    href={item.buttonLink}
                    className="inline-block bg-[#ff6b6b] hover:bg-[#ff5252] text-white font-medium py-3 px-8 rounded-md transition-colors"
                  >
                    {item.buttonText}
                  </a>
                </div>
              </div>
            </div>
          </div>
        ))}

        {/* Carousel Controls */}
        <div className="absolute bottom-5 left-0 right-0 flex justify-center space-x-2 z-30">
          {carouselItems.map((_, index) => (
            <button
              key={index}
              onClick={() => goToSlide(index)}
              className={`w-3 h-3 rounded-full transition-colors ${
                index === currentSlide ? 'bg-white' : 'bg-white/50'
              }`}
              aria-label={`Go to slide ${index + 1}`}
            ></button>
          ))}
        </div>
      </section>

      {/* Categories */}
      <section className="py-16 bg-gray-50">
        <div className="container mx-auto px-4">
          <h2 className="text-3xl font-bold text-center mb-12">浏览分类</h2>
          <div className="grid grid-cols-2 md:grid-cols-3 lg:grid-cols-5 gap-6">
            {categories.map((category) => (
              <Link
                key={category.id}
                to={`/products?category=${category.name === '女装' ? 'women' : category.name === '男装' ? 'men' : 'accessories'}`}
                className="group block overflow-hidden rounded-lg shadow-md hover:shadow-xl transition-shadow"
              >
                <div className="relative h-64 overflow-hidden">
                  <img
                    src={category.image}
                    alt={category.name}
                    className="w-full h-full object-cover transition-transform duration-500 group-hover:scale-110"
                  />
                  <div className="absolute inset-0 bg-gradient-to-t from-black/70 to-transparent flex items-end">
                    <h3 className="text-xl font-semibold text-white p-4 w-full text-center">
                      {category.name}
                    </h3>
                  </div>
                </div>
              </Link>
            ))}
          </div>
        </div>
      </section>

      {/* Featured Products */}
      <section className="py-16">
        <div className="container mx-auto px-4">
          <div className="flex justify-between items-center mb-12">
            <h2 className="text-3xl font-bold">热卖商品</h2>
            <Link to="/products?featured=true" className="text-[#ff6b6b] hover:text-[#ff5252] font-medium transition-colors">
              查看全部 &rarr;
            </Link>
          </div>
          <div className="grid grid-cols-1 sm:grid-cols-2 md:grid-cols-3 lg:grid-cols-4 gap-8">
            {featuredProducts.map((product) => (
              <div key={product.id} className="group">
                <Link to={`/products/${product.id}`} className="block">
                  <div className="relative overflow-hidden rounded-lg mb-4">
                    <img
                      src={product.image}
                      alt={product.name}
                      className="w-full h-80 object-cover transition-transform duration-500 group-hover:scale-105"
                    />
                    {product.discount && (
                      <div className="absolute top-2 right-2 bg-[#ff6b6b] text-white text-sm font-bold px-2 py-1 rounded">
                        {Math.round((1 - product.discount) * 100)}% OFF
                      </div>
                    )}
                    <div className="absolute inset-0 bg-black/40 opacity-0 group-hover:opacity-100 transition-opacity flex items-center justify-center">
                      <button className="bg-white text-gray-900 hover:bg-gray-100 rounded-full p-3 mx-1 transform translate-y-4 group-hover:translate-y-0 transition-transform">
                        <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor" className="w-5 h-5">
                          <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M15 12a3 3 0 11-6 0 3 3 0 016 0z" />
                          <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M2.458 12C3.732 7.943 7.523 5 12 5c4.478 0 8.268 2.943 9.542 7-1.274 4.057-5.064 7-9.542 7-4.477 0-8.268-2.943-9.542-7z" />
                        </svg>
                      </button>
                      <button className="bg-white text-gray-900 hover:bg-gray-100 rounded-full p-3 mx-1 transform translate-y-4 group-hover:translate-y-0 transition-transform delay-75">
                        <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor" className="w-5 h-5">
                          <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M4.318 6.318a4.5 4.5 0 000 6.364L12 20.364l7.682-7.682a4.5 4.5 0 00-6.364-6.364L12 7.636l-1.318-1.318a4.5 4.5 0 00-6.364 0z" />
                        </svg>
                      </button>
                      <button 
                        onClick={(e) => handleAddToCart(product, e)}
                        className="bg-white text-gray-900 hover:bg-gray-100 rounded-full p-3 mx-1 transform translate-y-4 group-hover:translate-y-0 transition-transform delay-150"
                      >
                        <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor" className="w-5 h-5">
                          <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M16 11V7a4 4 0 00-8 0v4M5 9h14l1 12H4L5 9z" />
                        </svg>
                      </button>
                    </div>
                  </div>
                </Link>
                <h3 className="font-medium text-lg mb-2">{product.name}</h3>
                <div className="flex items-center">
                  {product.discount ? (
                    <>
                      <span className="text-[#ff6b6b] font-bold">¥{Math.round(product.price * product.discount)}</span>
                      <span className="text-gray-400 line-through ml-2 text-sm">¥{product.price}</span>
                    </>
                  ) : (
                    <span className="font-bold">¥{product.price}</span>
                  )}
                </div>
              </div>
            ))}
          </div>
        </div>
      </section>

      {/* Promotion Banner */}
      <section className="py-16 bg-[#1a365d] text-white">
        <div className="container mx-auto px-4">
          <div className="flex flex-col md:flex-row items-center justify-between">
            <div className="mb-8 md:mb-0">
              <h2 className="text-3xl font-bold mb-4">订阅我们的通讯</h2>
              <p className="text-gray-300 max-w-md">
                获取最新的时尚趋势、新品发布和独家优惠信息。
              </p>
            </div>
            <div className="w-full md:w-auto">
              <form className="flex">
                <input
                  type="email"
                  placeholder="输入您的邮箱"
                  className="px-4 py-3 w-full md:w-64 rounded-l-md focus:outline-none text-gray-900"
                />
                <button
                  type="submit"
                  className="bg-[#ff6b6b] hover:bg-[#ff5252] px-6 py-3 rounded-r-md font-medium transition-colors"
                >
                  订阅
                </button>
              </form>
            </div>
          </div>
        </div>
      </section>
    </div>
  );
};

export default Home;