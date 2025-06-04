import { useState, useEffect, useRef } from 'react';
import { useParams, Link } from 'react-router-dom';
import { productDetails, relatedProducts } from '../data/mockData';
import { useCart } from '../contexts/CartContext';
import { useFavorite } from '../contexts/FavoriteContext';

const ProductDetail = () => {
  const { id } = useParams<{ id: string }>();
  const [product, setProduct] = useState<typeof productDetails[0] | null>(null);
  const [loading, setLoading] = useState(true);
  const [selectedImage, setSelectedImage] = useState(0);
  const [selectedSize, setSelectedSize] = useState('');
  const [selectedColor, setSelectedColor] = useState('');
  const [quantity, setQuantity] = useState(1);
  const [activeTab, setActiveTab] = useState('description');
  const [addedToCart, setAddedToCart] = useState(false);
  const [animationItem, setAnimationItem] = useState<{
    startX: number, 
    startY: number, 
    endX: number, 
    endY: number
  } | null>(null);
  
  // 添加到购物车按钮引用
  const addToCartBtnRef = useRef<HTMLButtonElement>(null);
  
  // 使用购物车上下文
  const { addToCart } = useCart();
  
  // 使用收藏上下文
  const { addToFavorite, removeFromFavorite, isFavorite } = useFavorite();

  useEffect(() => {
    // 模拟API请求
    const fetchProduct = () => {
      setLoading(true);
      setTimeout(() => {
        const foundProduct = productDetails.find(p => p.id === Number(id));
        if (foundProduct) {
          setProduct(foundProduct);
          setSelectedSize(foundProduct.sizes[0]);
          setSelectedColor(foundProduct.colors[0]);
        }
        setLoading(false);
      }, 500);
    };

    fetchProduct();
  }, [id]);

  // 处理数量变更
  const handleQuantityChange = (newQuantity: number) => {
    if (newQuantity > 0 && product && newQuantity <= product.stock) {
      setQuantity(newQuantity);
    }
  };

  // 处理添加到购物车
  const handleAddToCart = () => {
    if (product && addToCartBtnRef.current) {
      // 获取按钮位置
      const buttonRect = addToCartBtnRef.current.getBoundingClientRect();
      
      // 获取购物车图标的位置
      const cartIcon = document.querySelector('.cart-icon') as HTMLElement;
      if (!cartIcon) return;
      
      const cartRect = cartIcon.getBoundingClientRect();
      
      // 设置动画起始位置和目标位置
      setAnimationItem({
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
        image: product.images[0],
        discount: product.discount,
        quantity: quantity,
        size: selectedSize,
        color: selectedColor
      };
      
      // 延迟添加到购物车，等待动画完成
      setTimeout(() => {
        // 添加到购物车
        addToCart(cartItem);
        
        // 显示添加成功提示
        setAddedToCart(true);
        setTimeout(() => setAddedToCart(false), 3000);
        
        // 清除动画状态
        setTimeout(() => {
          setAnimationItem(null);
        }, 1000);
      }, 800);
    }
  };
  
  // 处理收藏/取消收藏
  const handleToggleFavorite = () => {
    if (!product) return;
    
    if (isFavorite(product.id)) {
      removeFromFavorite(product.id);
    } else {
      addToFavorite({
        id: product.id,
        name: product.name,
        price: product.price,
        image: product.images[0],
        category: product.category,
        discount: product.discount,
        featured: product.featured
      });
    }
  };

  if (loading) {
    return (
      <div className="container mx-auto px-4 py-16 flex justify-center">
        <div className="animate-spin rounded-full h-12 w-12 border-t-2 border-b-2 border-[#1a365d]"></div>
      </div>
    );
  }

  if (!product) {
    return (
      <div className="container mx-auto px-4 py-16 text-center">
        <h2 className="text-2xl font-bold mb-4">商品未找到</h2>
        <p className="text-gray-600 mb-8">抱歉，您查找的商品不存在或已被移除。</p>
        <Link to="/products" className="bg-[#1a365d] text-white px-6 py-3 rounded-md hover:bg-[#2a4365] transition-colors">
          浏览所有商品
        </Link>
      </div>
    );
  }

  // 是否已收藏
  const productIsFavorite = isFavorite(product.id);

  return (
    <div className="container mx-auto px-4 py-8">
      {/* 添加到购物车成功提示 */}
      {addedToCart && (
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
            backgroundImage: `url(${product.images[selectedImage]})`,
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

      {/* 面包屑导航 */}
      <nav className="flex mb-8 text-sm">
        <Link to="/" className="text-gray-600 hover:text-[#ff6b6b]">首页</Link>
        <span className="mx-2 text-gray-400">/</span>
        <Link to="/products" className="text-gray-600 hover:text-[#ff6b6b]">所有商品</Link>
        <span className="mx-2 text-gray-400">/</span>
        <Link 
          to={`/products?category=${product.category}`} 
          className="text-gray-600 hover:text-[#ff6b6b]"
        >
          {product.category === 'women' ? '女装' : product.category === 'men' ? '男装' : '配饰'}
        </Link>
        <span className="mx-2 text-gray-400">/</span>
        <span className="text-gray-900">{product.name}</span>
      </nav>

      {/* 商品详情 */}
      <div className="flex flex-col lg:flex-row -mx-4">
        {/* 商品图片 */}
        <div className="lg:w-1/2 px-4 mb-8 lg:mb-0">
          <div className="relative overflow-hidden rounded-lg mb-4 h-[500px]">
            <img 
              src={product.images[selectedImage]} 
              alt={product.name} 
              className="w-full h-full object-cover"
            />
          </div>
          <div className="flex space-x-2 overflow-auto pb-2">
            {product.images.map((image, index) => (
              <button 
                key={index} 
                onClick={() => setSelectedImage(index)}
                className={`w-20 h-20 rounded-md overflow-hidden flex-shrink-0 ${
                  selectedImage === index ? 'ring-2 ring-[#ff6b6b]' : 'ring-1 ring-gray-200'
                }`}
              >
                <img 
                  src={image} 
                  alt={`${product.name} - 图片 ${index + 1}`} 
                  className="w-full h-full object-cover"
                />
              </button>
            ))}
          </div>
        </div>

        {/* 商品信息 */}
        <div className="lg:w-1/2 px-4">
          <h1 className="text-3xl font-bold mb-2">{product.name}</h1>
          
          {/* 价格 */}
          <div className="mb-6">
            {product.discount ? (
              <div className="flex items-center">
                <span className="text-2xl font-bold text-[#ff6b6b]">
                  ¥{Math.round(product.price * product.discount)}
                </span>
                <span className="text-gray-400 line-through ml-2">
                  ¥{product.price}
                </span>
                <span className="ml-2 bg-[#ff6b6b] text-white text-sm font-bold px-2 py-1 rounded">
                  {Math.round((1 - product.discount) * 100)}% OFF
                </span>
              </div>
            ) : (
              <span className="text-2xl font-bold">¥{product.price}</span>
            )}
          </div>

          {/* 尺码选择 */}
          <div className="mb-6">
            <h3 className="text-sm font-medium text-gray-900 mb-2">尺码</h3>
            <div className="flex flex-wrap gap-2">
              {product.sizes.map((size) => (
                <button
                  key={size}
                  onClick={() => setSelectedSize(size)}
                  className={`px-4 py-2 border rounded-md text-sm font-medium ${
                    selectedSize === size
                      ? 'border-[#1a365d] bg-[#1a365d] text-white'
                      : 'border-gray-300 text-gray-700 hover:border-[#1a365d]'
                  }`}
                >
                  {size}
                </button>
              ))}
            </div>
          </div>

          {/* 颜色选择 */}
          <div className="mb-6">
            <h3 className="text-sm font-medium text-gray-900 mb-2">颜色</h3>
            <div className="flex flex-wrap gap-2">
              {product.colors.map((color) => (
                <button
                  key={color}
                  onClick={() => setSelectedColor(color)}
                  className={`px-4 py-2 border rounded-md text-sm font-medium ${
                    selectedColor === color
                      ? 'border-[#1a365d] bg-[#1a365d] text-white'
                      : 'border-gray-300 text-gray-700 hover:border-[#1a365d]'
                  }`}
                >
                  {color}
                </button>
              ))}
            </div>
          </div>

          {/* 数量选择 */}
          <div className="mb-6">
            <h3 className="text-sm font-medium text-gray-900 mb-2">数量</h3>
            <div className="flex items-center">
              <button
                onClick={() => handleQuantityChange(quantity - 1)}
                className="w-10 h-10 border border-gray-300 rounded-l-md flex items-center justify-center hover:bg-gray-100"
                disabled={quantity <= 1}
              >
                <svg className="w-4 h-4 text-gray-600" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                  <path strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M20 12H4" />
                </svg>
              </button>
              <input
                type="number"
                value={quantity}
                onChange={(e) => handleQuantityChange(parseInt(e.target.value) || 1)}
                className="w-16 h-10 border-t border-b border-gray-300 text-center focus:outline-none"
              />
              <button
                onClick={() => handleQuantityChange(quantity + 1)}
                className="w-10 h-10 border border-gray-300 rounded-r-md flex items-center justify-center hover:bg-gray-100"
                disabled={product.stock <= quantity}
              >
                <svg className="w-4 h-4 text-gray-600" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                  <path strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M12 4v16m8-8H4" />
                </svg>
              </button>
              <span className="ml-4 text-sm text-gray-500">
                库存 {product.stock} 件
              </span>
            </div>
          </div>

          {/* 操作按钮 */}
          <div className="flex space-x-4 mb-8">
            <button
              ref={addToCartBtnRef}
              onClick={handleAddToCart}
              className="flex-1 bg-[#1a365d] text-white py-3 px-6 rounded-md hover:bg-[#2a4365] transition-colors relative overflow-hidden group"
            >
              <span className="relative z-10">加入购物车</span>
              <span className="absolute inset-0 bg-[#2a4365] scale-x-0 group-hover:scale-x-100 origin-left transition-transform duration-300"></span>
            </button>
            <button
              onClick={handleToggleFavorite}
              className={`w-12 h-12 flex items-center justify-center rounded-md border ${
                productIsFavorite 
                  ? 'bg-[#ffebee] border-[#ff6b6b] text-[#ff6b6b]'
                  : 'border-gray-300 text-gray-500 hover:border-[#ff6b6b] hover:text-[#ff6b6b]'
              }`}
              aria-label={productIsFavorite ? "取消收藏" : "加入收藏"}
            >
              <svg 
                className="w-6 h-6" 
                fill={productIsFavorite ? "currentColor" : "none"} 
                stroke="currentColor" 
                viewBox="0 0 24 24"
              >
                <path 
                  strokeLinecap="round" 
                  strokeLinejoin="round" 
                  strokeWidth="2" 
                  d="M4.318 6.318a4.5 4.5 0 000 6.364L12 20.364l7.682-7.682a4.5 4.5 0 00-6.364-6.364L12 7.636l-1.318-1.318a4.5 4.5 0 00-6.364 0z"
                />
              </svg>
            </button>
            <Link to="/cart" className="flex-1">
              <button 
                onClick={handleAddToCart}
                className="w-full bg-[#ff6b6b] text-white py-3 px-6 rounded-md hover:bg-[#ff5252] transition-colors relative overflow-hidden group"
              >
                <span className="relative z-10">立即购买</span>
                <span className="absolute inset-0 bg-[#ff5252] scale-x-0 group-hover:scale-x-100 origin-left transition-transform duration-300"></span>
              </button>
            </Link>
          </div>

          {/* 商品信息 */}
          <div className="border-t border-gray-200 pt-6">
            <div className="flex space-x-8 border-b border-gray-200">
              <button
                onClick={() => setActiveTab('description')}
                className={`pb-4 text-sm font-medium ${
                  activeTab === 'description'
                    ? 'border-b-2 border-[#1a365d] text-[#1a365d]'
                    : 'text-gray-600 hover:text-[#1a365d]'
                }`}
              >
                商品详情
              </button>
              <button
                onClick={() => setActiveTab('reviews')}
                className={`pb-4 text-sm font-medium ${
                  activeTab === 'reviews'
                    ? 'border-b-2 border-[#1a365d] text-[#1a365d]'
                    : 'text-gray-600 hover:text-[#1a365d]'
                }`}
              >
                用户评价 ({product.reviews.length})
              </button>
            </div>

            <div className="py-6">
              {activeTab === 'description' ? (
                <div>
                  <p className="text-gray-700 mb-4">{product.description}</p>
                  <div className="mt-6">
                    <h4 className="text-sm font-medium text-gray-900 mb-2">商品信息</h4>
                    <ul className="text-sm text-gray-700 space-y-2">
                      <li><span className="font-medium">商品编号：</span>{product.sku}</li>
                      <li><span className="font-medium">分类：</span>{product.category === 'women' ? '女装' : product.category === 'men' ? '男装' : '配饰'}</li>
                    </ul>
                  </div>
                </div>
              ) : (
                <div>
                  {product.reviews.length > 0 ? (
                    <ul className="space-y-6">
                      {product.reviews.map((review) => (
                        <li key={review.id} className="border-b border-gray-200 pb-6">
                          <div className="flex items-center mb-2">
                            <div className="flex text-yellow-400">
                              {[...Array(5)].map((_, i) => (
                                <svg
                                  key={i}
                                  className={`w-4 h-4 ${i < review.rating ? 'fill-current' : 'text-gray-300'}`}
                                  viewBox="0 0 20 20"
                                >
                                  <path d="M10 15l-5.878 3.09 1.123-6.545L.489 6.91l6.572-.955L10 0l2.939 5.955 6.572.955-4.756 4.635 1.123 6.545z" />
                                </svg>
                              ))}
                            </div>
                            <span className="ml-2 text-sm text-gray-600">{review.date}</span>
                          </div>
                          <h4 className="font-medium">{review.user}</h4>
                          <p className="text-gray-700 mt-1">{review.comment}</p>
                        </li>
                      ))}
                    </ul>
                  ) : (
                    <p className="text-gray-600">暂无评价</p>
                  )}
                </div>
              )}
            </div>
          </div>
        </div>
      </div>

      {/* 相关商品推荐 */}
      <div className="mt-16">
        <h2 className="text-2xl font-bold mb-8">相关推荐</h2>
        <div className="grid grid-cols-1 sm:grid-cols-2 md:grid-cols-3 lg:grid-cols-4 gap-6">
          {relatedProducts.map((product) => (
            <div key={product.id} className="group">
              <Link to={`/products/${product.id}`} className="block">
                <div className="relative overflow-hidden rounded-lg mb-4">
                  <img
                    src={product.image}
                    alt={product.name}
                    className="w-full h-64 object-cover transition-transform duration-500 group-hover:scale-105"
                  />
                  {product.discount && (
                    <div className="absolute top-2 right-2 bg-[#ff6b6b] text-white text-sm font-bold px-2 py-1 rounded">
                      {Math.round((1 - product.discount) * 100)}% OFF
                    </div>
                  )}
                </div>
              </Link>
              <h3 className="font-medium mb-2">{product.name}</h3>
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
    </div>
  );
};

export default ProductDetail; 