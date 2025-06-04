import { useState, useEffect } from 'react';
import { useSearchParams } from 'react-router-dom';
import { allProducts, filterOptions } from '../data/mockData';

const ProductList = () => {
  const [searchParams, setSearchParams] = useSearchParams();
  const [products, setProducts] = useState<typeof allProducts>([]);
  const [filters, setFilters] = useState({
    category: searchParams.get('category') || 'all',
    price: 'all',
    sort: 'recommended',
    featured: searchParams.get('featured') === 'true',
  });

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

  return (
    <div className="container mx-auto px-4 py-8">
      {/* 页面标题 */}
      <div className="mb-8">
        <h1 className="text-3xl font-bold">{getCategoryTitle()}</h1>
        <p className="text-gray-600 mt-2">共找到 {products.length} 件商品</p>
      </div>

      {/* 筛选器和排序 */}
      <div className="flex flex-col md:flex-row justify-between mb-8">
        <div className="flex flex-wrap gap-4 mb-4 md:mb-0">
          <div className="relative">
            <select 
              value={filters.price}
              onChange={(e) => handleFilterChange('price', e.target.value)}
              className="appearance-none bg-white border border-gray-300 rounded-md py-2 pl-4 pr-10 text-sm focus:outline-none focus:ring-2 focus:ring-[#ff6b6b] focus:border-transparent"
            >
              {filterOptions.price.map((option) => (
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
              onClick={() => handleFilterChange('category', 'all')}
              className={`px-4 py-2 text-sm rounded-md ${
                filters.category === 'all' && !filters.featured 
                  ? 'bg-[#1a365d] text-white' 
                  : 'bg-gray-100 text-gray-800 hover:bg-gray-200'
              }`}
            >
              全部
            </button>
            <button 
              onClick={() => handleFilterChange('category', 'women')}
              className={`px-4 py-2 text-sm rounded-md ${
                filters.category === 'women' 
                  ? 'bg-[#1a365d] text-white' 
                  : 'bg-gray-100 text-gray-800 hover:bg-gray-200'
              }`}
            >
              女装
            </button>
            <button 
              onClick={() => handleFilterChange('category', 'men')}
              className={`px-4 py-2 text-sm rounded-md ${
                filters.category === 'men' 
                  ? 'bg-[#1a365d] text-white' 
                  : 'bg-gray-100 text-gray-800 hover:bg-gray-200'
              }`}
            >
              男装
            </button>
            <button 
              onClick={() => handleFilterChange('category', 'accessories')}
              className={`px-4 py-2 text-sm rounded-md ${
                filters.category === 'accessories' 
                  ? 'bg-[#1a365d] text-white' 
                  : 'bg-gray-100 text-gray-800 hover:bg-gray-200'
              }`}
            >
              配饰
            </button>
          </div>
        </div>

        <div className="relative">
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
      </div>

      {/* 商品列表 */}
      <div className="grid grid-cols-1 sm:grid-cols-2 md:grid-cols-3 lg:grid-cols-4 gap-8">
        {products.map((product) => (
          <div key={product.id} className="group">
            <a href={`/products/${product.id}`} className="block">
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
                  <button className="bg-white text-gray-900 hover:bg-gray-100 rounded-full p-3 mx-1 transform translate-y-4 group-hover:translate-y-0 transition-transform delay-150">
                    <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor" className="w-5 h-5">
                      <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M16 11V7a4 4 0 00-8 0v4M5 9h14l1 12H4L5 9z" />
                    </svg>
                  </button>
                </div>
              </div>
            </a>
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

      {/* 空状态 */}
      {products.length === 0 && (
        <div className="text-center py-16">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor" className="w-16 h-16 mx-auto text-gray-400 mb-4">
            <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M9.172 16.172a4 4 0 015.656 0M9 10h.01M15 10h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z" />
          </svg>
          <h3 className="text-xl font-medium text-gray-900 mb-2">没有找到符合条件的商品</h3>
          <p className="text-gray-600">请尝试调整筛选条件</p>
        </div>
      )}
    </div>
  );
};

export default ProductList; 