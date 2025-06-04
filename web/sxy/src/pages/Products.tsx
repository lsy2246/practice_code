import { useState, useEffect } from 'react';
import { Link, useSearchParams } from 'react-router-dom';
import { allProducts, filterOptions, categories } from '../data/mockData';
import { useCart } from '../contexts/CartContext';
import { useFavorite } from '../contexts/FavoriteContext';

const Products = () => {
  const [searchParams, setSearchParams] = useSearchParams();
  const [products, setProducts] = useState<typeof allProducts>([]);
  const [filters, setFilters] = useState({
    category: searchParams.get('category') || 'all',
    price: 'all',
    sort: 'recommended',
    featured: searchParams.get('featured') === 'true',
  });
  const [viewMode, setViewMode] = useState('grid'); // 'grid' 或 'list'
  const [loading, setLoading] = useState(true);
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
  
  // 使用收藏上下文
  const { addToFavorite, removeFromFavorite, isFavorite } = useFavorite();

  // 第一个 useEffect：从 URL 参数更新 filters
  useEffect(() => {
    const categoryParam = searchParams.get('category');
    const featuredParam = searchParams.get('featured');
    
    let shouldUpdateFilters = false;
    let newFilters = { ...filters };
    
    if (categoryParam && categoryParam !== filters.category) {
      newFilters.category = categoryParam;
      shouldUpdateFilters = true;
    }
    
    if ((featuredParam === 'true') !== filters.featured) {
      newFilters.featured = featuredParam === 'true';
      shouldUpdateFilters = true;
    }
    
    if (shouldUpdateFilters) {
      setFilters(newFilters);
    }
  }, [searchParams]);

  // 第二个 useEffect：根据 filters 过滤商品
  useEffect(() => {
    setLoading(true);
    
    // 模拟 API 请求延迟
    setTimeout(() => {
      let filtered = [...allProducts];
      
      // 应用分类筛选
      if (filters.category !== 'all') {
        filtered = filtered.filter(product => product.category === filters.category);
      }
      
      // 应用精选筛选
      if (filters.featured) {
        filtered = filtered.filter(product => product.featured);
      }
      
      // 应用价格筛选
      if (filters.price !== 'all') {
        const [min, max] = filters.price.split('-').map(Number);
        filtered = filtered.filter(product => {
          const finalPrice = product.discount 
            ? Math.round(product.price * product.discount) 
            : product.price;
          return finalPrice >= min && finalPrice <= max;
        });
      }
      
      // 应用排序
      switch (filters.sort) {
        case 'price-asc':
          filtered.sort((a, b) => {
            const priceA = a.discount ? Math.round(a.price * a.discount) : a.price;
            const priceB = b.discount ? Math.round(b.price * b.discount) : b.price;
            return priceA - priceB;
          });
          break;
        case 'price-desc':
          filtered.sort((a, b) => {
            const priceA = a.discount ? Math.round(a.price * a.discount) : a.price;
            const priceB = b.discount ? Math.round(b.price * b.discount) : b.price;
            return priceB - priceA;
          });
          break;
        case 'newest':
          // 假设 id 越大越新
          filtered.sort((a, b) => b.id - a.id);
          break;
        default:
          // 推荐排序，假设精选商品排在前面
          filtered.sort((a, b) => (b.featured ? 1 : 0) - (a.featured ? 1 : 0));
      }
      
      setProducts(filtered);
      setLoading(false);
    }, 500);
  }, [filters]);

  // 更新筛选条件
  const handleFilterChange = (filterType: string, value: string) => {
    setFilters(prev => {
      const newFilters = { ...prev, [filterType]: value };
      
      // 更新 URL 参数
      if (filterType === 'category') {
        if (value === 'all') {
          searchParams.delete('category');
        } else {
          searchParams.set('category', value);
        }
        setSearchParams(searchParams);
      }
      
      return newFilters;
    });
  };

  // 获取当前分类名称
  const getCategoryTitle = () => {
    switch (filters.category) {
      case 'women': return '女装';
      case 'men': return '男装';
      case 'accessories': return '配饰';
      default: return filters.featured ? '热卖商品' : '所有商品';
    }
  };

  // 获取分类中文名称
  const getCategoryName = (categoryKey: string) => {
    switch (categoryKey) {
      case 'women': return '女装';
      case 'men': return '男装';
      case 'accessories': return '配饰';
      default: return '全部';
    }
  };

  // 添加商品到购物车
  const handleAddToCart = (product: typeof allProducts[0], event: React.MouseEvent) => {
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

  // 处理收藏/取消收藏
  const handleToggleFavorite = (product: typeof allProducts[0]) => {
    if (isFavorite(product.id)) {
      removeFromFavorite(product.id);
    } else {
      addToFavorite({
        id: product.id,
        name: product.name,
        price: product.price,
        image: product.image,
        category: product.category,
        discount: product.discount,
        featured: product.featured
      });
    }
  };

  // 渲染加载状态
  if (loading) {
    return (
      <div className="container mx-auto px-4 py-16 flex justify-center">
        <div className="animate-spin rounded-full h-12 w-12 border-t-2 border-b-2 border-[#1a365d]"></div>
      </div>
    );
  }

  return (
    <div className="container mx-auto px-4 py-8">
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
            backgroundImage: `url(${products.find(p => p.id === animationItem.id)?.image})`,
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
      <nav className="flex mb-6 text-sm">
        <Link to="/" className="text-gray-600 hover:text-[#ff6b6b]">首页</Link>
        <span className="mx-2 text-gray-400">/</span>
        <span className="text-gray-900">{getCategoryTitle()}</span>
      </nav>

      {/* 页面标题 */}
      <div className="mb-8">
        <h1 className="text-3xl font-bold">{getCategoryTitle()}</h1>
        <p className="text-gray-600 mt-2">共找到 {products.length} 件商品</p>
      </div>

      <div className="flex flex-col lg:flex-row gap-8">
        {/* 左侧筛选器 */}
        <div className="lg:w-1/4">
          <div className="bg-white rounded-lg shadow-sm p-6 mb-6">
            <h3 className="text-lg font-medium mb-4">商品分类</h3>
            <ul className="space-y-2">
              <li>
                <button 
                  onClick={() => handleFilterChange('category', 'all')}
                  className={`w-full text-left py-1 ${
                    filters.category === 'all' 
                      ? 'text-[#ff6b6b] font-medium' 
                      : 'text-gray-700 hover:text-[#ff6b6b]'
                  }`}
                >
                  全部商品
                </button>
              </li>
              {categories.map((category) => (
                <li key={category.id}>
                  <button 
                    onClick={() => handleFilterChange('category', category.name === '女装' ? 'women' : category.name === '男装' ? 'men' : 'accessories')}
                    className={`w-full text-left py-1 ${
                      (category.name === '女装' && filters.category === 'women') ||
                      (category.name === '男装' && filters.category === 'men') ||
                      (category.name === '配饰' && filters.category === 'accessories')
                        ? 'text-[#ff6b6b] font-medium' 
                        : 'text-gray-700 hover:text-[#ff6b6b]'
                    }`}
                  >
                    {category.name}
                  </button>
                </li>
              ))}
            </ul>
          </div>

          <div className="bg-white rounded-lg shadow-sm p-6 mb-6">
            <h3 className="text-lg font-medium mb-4">价格范围</h3>
            <ul className="space-y-2">
              {filterOptions.price.map((option) => (
                <li key={option.value}>
                  <button 
                    onClick={() => handleFilterChange('price', option.value)}
                    className={`w-full text-left py-1 ${
                      filters.price === option.value 
                        ? 'text-[#ff6b6b] font-medium' 
                        : 'text-gray-700 hover:text-[#ff6b6b]'
                    }`}
                  >
                    {option.label}
                  </button>
                </li>
              ))}
            </ul>
          </div>

          <div className="bg-white rounded-lg shadow-sm p-6">
            <h3 className="text-lg font-medium mb-4">特色商品</h3>
            <div className="flex items-center">
              <input 
                type="checkbox" 
                id="featured"
                checked={filters.featured}
                onChange={() => {
                  const newValue = !filters.featured;
                  handleFilterChange('featured', newValue ? 'true' : 'false');
                  
                  // 更新 URL 参数
                  if (newValue) {
                    searchParams.set('featured', 'true');
                  } else {
                    searchParams.delete('featured');
                  }
                  setSearchParams(searchParams);
                }}
                className="w-4 h-4 text-[#ff6b6b] border-gray-300 rounded focus:ring-[#ff6b6b]" 
              />
              <label htmlFor="featured" className="ml-2 text-gray-700">
                只显示热卖商品
              </label>
            </div>
          </div>
        </div>

        {/* 右侧商品列表 */}
        <div className="lg:w-3/4">
          {/* 排序和视图切换 */}
          <div className="flex flex-col sm:flex-row justify-between mb-6">
            <div className="relative mb-4 sm:mb-0">
              <select 
                value={filters.sort}
                onChange={(e) => handleFilterChange('sort', e.target.value)}
                className="appearance-none bg-white border border-gray-300 rounded-md py-2 pl-4 pr-10 text-sm focus:outline-none focus:ring-2 focus:ring-[#ff6b6b] focus:border-transparent"
              >
                {filterOptions.sort.map((option) => (
                  <option key={option.value} value={option.value}>
                    {option.label}
                  </option>
                ))}
              </select>
              <div className="absolute inset-y-0 right-0 flex items-center px-2 pointer-events-none">
                <svg className="w-4 h-4 text-gray-400" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                  <path strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M19 9l-7 7-7-7" />
                </svg>
              </div>
            </div>

            <div className="flex space-x-2">
              <button 
                onClick={() => setViewMode('grid')}
                className={`p-2 rounded-md ${
                  viewMode === 'grid' 
                    ? 'bg-[#1a365d] text-white' 
                    : 'bg-gray-100 text-gray-600 hover:bg-gray-200'
                }`}
                aria-label="网格视图"
              >
                <svg className="w-5 h-5" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                  <path strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M4 6a2 2 0 012-2h2a2 2 0 012 2v2a2 2 0 01-2 2H6a2 2 0 01-2-2V6zM14 6a2 2 0 012-2h2a2 2 0 012 2v2a2 2 0 01-2 2h-2a2 2 0 01-2-2V6zM4 16a2 2 0 012-2h2a2 2 0 012 2v2a2 2 0 01-2 2H6a2 2 0 01-2-2v-2zM14 16a2 2 0 012-2h2a2 2 0 012 2v2a2 2 0 01-2 2h-2a2 2 0 01-2-2v-2z" />
                </svg>
              </button>
              <button 
                onClick={() => setViewMode('list')}
                className={`p-2 rounded-md ${
                  viewMode === 'list' 
                    ? 'bg-[#1a365d] text-white' 
                    : 'bg-gray-100 text-gray-600 hover:bg-gray-200'
                }`}
                aria-label="列表视图"
              >
                <svg className="w-5 h-5" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                  <path strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M4 6h16M4 12h16M4 18h16" />
                </svg>
              </button>
            </div>
          </div>

          {/* 商品列表 - 网格视图 */}
          {viewMode === 'grid' && (
            <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-6">
              {products.map((product) => (
                <div key={product.id} className="group bg-white rounded-lg shadow-sm overflow-hidden">
                  <Link to={`/products/${product.id}`} className="block">
                    <div className="relative overflow-hidden h-60">
                      <img
                        src={product.image}
                        alt={product.name}
                        className="w-full h-full object-cover transition-transform duration-500 group-hover:scale-105"
                      />
                      {product.discount && (
                        <div className="absolute top-2 right-2 bg-[#ff6b6b] text-white text-sm font-bold px-2 py-1 rounded">
                          {Math.round((1 - product.discount) * 100)}% OFF
                        </div>
                      )}
                      <div className="absolute inset-0 bg-black/40 opacity-0 group-hover:opacity-100 transition-opacity flex items-center justify-center">
                        <span className="text-white bg-[#ff6b6b] px-4 py-2 rounded-md font-medium transform translate-y-4 group-hover:translate-y-0 transition-transform">
                          查看详情
                        </span>
                      </div>
                    </div>
                  </Link>
                  <div className="p-4">
                    <div className="flex justify-between items-start mb-2">
                      <h3 className="font-medium text-lg">{product.name}</h3>
                      <span className="text-xs text-gray-500 bg-gray-100 px-2 py-1 rounded">
                        {getCategoryName(product.category)}
                      </span>
                    </div>
                    <div className="flex items-center justify-between">
                      <div>
                        {product.discount ? (
                          <>
                            <span className="text-[#ff6b6b] font-bold">¥{Math.round(product.price * product.discount)}</span>
                            <span className="text-gray-400 line-through ml-2 text-sm">¥{product.price}</span>
                          </>
                        ) : (
                          <span className="font-bold">¥{product.price}</span>
                        )}
                      </div>
                      <button 
                        onClick={() => handleToggleFavorite(product)}
                        className={`transition-colors ${isFavorite(product.id) ? 'text-[#ff6b6b]' : 'text-[#1a365d] hover:text-[#ff6b6b]'}`}
                        aria-label={isFavorite(product.id) ? "取消收藏" : "加入收藏"}
                      >
                        <svg xmlns="http://www.w3.org/2000/svg" 
                          fill={isFavorite(product.id) ? "currentColor" : "none"} 
                          viewBox="0 0 24 24" 
                          stroke="currentColor" 
                          className="w-6 h-6"
                        >
                          <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M4.318 6.318a4.5 4.5 0 000 6.364L12 20.364l7.682-7.682a4.5 4.5 0 00-6.364-6.364L12 7.636l-1.318-1.318a4.5 4.5 0 00-6.364 0z" />
                        </svg>
                      </button>
                    </div>
                    <button 
                      onClick={(e) => handleAddToCart(product, e)}
                      className="mt-4 w-full bg-[#1a365d] text-white py-2 rounded-md hover:bg-[#2a4365] transition-colors relative overflow-hidden group"
                    >
                      <span className="relative z-10">加入购物车</span>
                      <span className="absolute inset-0 bg-[#2a4365] scale-x-0 group-hover:scale-x-100 origin-left transition-transform duration-300"></span>
                    </button>
                  </div>
                </div>
              ))}
            </div>
          )}

          {/* 商品列表 - 列表视图 */}
          {viewMode === 'list' && (
            <div className="space-y-6">
              {products.map((product) => (
                <div key={product.id} className="flex flex-col sm:flex-row bg-white rounded-lg shadow-sm overflow-hidden group">
                  <Link to={`/products/${product.id}`} className="sm:w-1/3">
                    <div className="relative h-60 sm:h-full">
                      <img
                        src={product.image}
                        alt={product.name}
                        className="w-full h-full object-cover transition-transform duration-500 group-hover:scale-105"
                      />
                      {product.discount && (
                        <div className="absolute top-2 right-2 bg-[#ff6b6b] text-white text-sm font-bold px-2 py-1 rounded">
                          {Math.round((1 - product.discount) * 100)}% OFF
                        </div>
                      )}
                    </div>
                  </Link>
                  <div className="p-6 sm:w-2/3">
                    <div className="flex justify-between items-start mb-2">
                      <h3 className="font-medium text-lg">
                        <Link to={`/products/${product.id}`} className="hover:text-[#ff6b6b] transition-colors">
                          {product.name}
                        </Link>
                      </h3>
                      <span className="text-xs text-gray-500 bg-gray-100 px-2 py-1 rounded">
                        {getCategoryName(product.category)}
                      </span>
                    </div>
                    <p className="text-gray-600 mb-4">
                      这是{product.name}的简短描述。在实际项目中，可以添加商品的详细描述信息。
                    </p>
                    <div className="flex items-center justify-between mt-auto">
                      <div>
                        {product.discount ? (
                          <>
                            <span className="text-[#ff6b6b] font-bold text-xl">¥{Math.round(product.price * product.discount)}</span>
                            <span className="text-gray-400 line-through ml-2">¥{product.price}</span>
                          </>
                        ) : (
                          <span className="font-bold text-xl">¥{product.price}</span>
                        )}
                      </div>
                      <div className="flex space-x-2">
                        <button 
                          onClick={() => handleToggleFavorite(product)}
                          className={`transition-colors p-2 ${isFavorite(product.id) ? 'text-[#ff6b6b]' : 'text-[#1a365d] hover:text-[#ff6b6b]'}`}
                          aria-label={isFavorite(product.id) ? "取消收藏" : "加入收藏"}
                        >
                          <svg xmlns="http://www.w3.org/2000/svg" 
                            fill={isFavorite(product.id) ? "currentColor" : "none"} 
                            viewBox="0 0 24 24" 
                            stroke="currentColor" 
                            className="w-6 h-6"
                          >
                            <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M4.318 6.318a4.5 4.5 0 000 6.364L12 20.364l7.682-7.682a4.5 4.5 0 00-6.364-6.364L12 7.636l-1.318-1.318a4.5 4.5 0 00-6.364 0z" />
                          </svg>
                        </button>
                        <button 
                          onClick={(e) => handleAddToCart(product, e)}
                          className="bg-[#1a365d] text-white px-4 py-2 rounded-md hover:bg-[#2a4365] transition-colors relative overflow-hidden group"
                        >
                          <span className="relative z-10">加入购物车</span>
                          <span className="absolute inset-0 bg-[#2a4365] scale-x-0 group-hover:scale-x-100 origin-left transition-transform duration-300"></span>
                        </button>
                      </div>
                    </div>
                  </div>
                </div>
              ))}
            </div>
          )}

          {/* 空状态 */}
          {products.length === 0 && (
            <div className="text-center py-16 bg-white rounded-lg shadow-sm">
              <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor" className="w-16 h-16 mx-auto text-gray-400 mb-4">
                <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M9.172 16.172a4 4 0 015.656 0M9 10h.01M15 10h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z" />
              </svg>
              <h3 className="text-xl font-medium text-gray-900 mb-2">没有找到符合条件的商品</h3>
              <p className="text-gray-600">请尝试调整筛选条件</p>
              <button 
                onClick={() => {
                  setFilters({
                    category: 'all',
                    price: 'all',
                    sort: 'recommended',
                    featured: false
                  });
                  searchParams.delete('category');
                  searchParams.delete('featured');
                  setSearchParams(searchParams);
                }}
                className="mt-4 text-[#ff6b6b] hover:text-[#ff5252]"
              >
                清除所有筛选条件
              </button>
            </div>
          )}

          {/* 分页 */}
          {products.length > 0 && (
            <div className="flex justify-center mt-12">
              <nav className="flex items-center">
                <button className="px-4 py-2 rounded-md border border-gray-300 text-gray-600 hover:bg-gray-50 disabled:opacity-50 disabled:cursor-not-allowed" disabled>
                  上一页
                </button>
                <button className="mx-1 px-4 py-2 rounded-md bg-[#1a365d] text-white">
                  1
                </button>
                <button className="mx-1 px-4 py-2 rounded-md border border-gray-300 text-gray-600 hover:bg-gray-50">
                  2
                </button>
                <button className="mx-1 px-4 py-2 rounded-md border border-gray-300 text-gray-600 hover:bg-gray-50">
                  3
                </button>
                <span className="mx-1 text-gray-600">...</span>
                <button className="px-4 py-2 rounded-md border border-gray-300 text-gray-600 hover:bg-gray-50">
                  下一页
                </button>
              </nav>
            </div>
          )}
        </div>
      </div>
    </div>
  );
};

export default Products; 