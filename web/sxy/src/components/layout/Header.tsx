import { useState, useEffect, useRef } from 'react';
import { NavLink, Link, useLocation } from 'react-router-dom';
import { useCart } from '../../contexts/CartContext';
import Search from '../Search';

const Header = () => {
  const [isMenuOpen, setIsMenuOpen] = useState(false);
  const [isSearchOpen, setIsSearchOpen] = useState(false);
  const location = useLocation();
  const { getCartCount } = useCart();
  const [cartItemCount, setCartItemCount] = useState(0);
  const prevCountRef = useRef(0);
  const [animateBadge, setAnimateBadge] = useState(false);
  const searchModalRef = useRef<HTMLDivElement>(null);

  // 监听购物车商品数量变化
  useEffect(() => {
    const newCount = getCartCount();
    // 保存之前的计数
    prevCountRef.current = cartItemCount;
    setCartItemCount(newCount);
    
    // 只有当购物车数量增加时才触发动画
    if (newCount > prevCountRef.current) {
      setAnimateBadge(true);
      const timer = setTimeout(() => {
        setAnimateBadge(false);
      }, 600);
      return () => clearTimeout(timer);
    }
  }, [getCartCount]);

  // 处理搜索弹窗开关
  const toggleSearch = () => {
    setIsSearchOpen(!isSearchOpen);
    // 关闭移动端菜单（如果打开）
    if (isMenuOpen) setIsMenuOpen(false);
  };

  // 点击ESC键关闭搜索弹窗
  useEffect(() => {
    const handleEsc = (e: KeyboardEvent) => {
      if (e.key === 'Escape' && isSearchOpen) {
        setIsSearchOpen(false);
      }
    };
    
    window.addEventListener('keydown', handleEsc);
    return () => {
      window.removeEventListener('keydown', handleEsc);
    };
  }, [isSearchOpen]);

  // 点击外部区域关闭搜索弹窗
  useEffect(() => {
    const handleClickOutside = (e: MouseEvent) => {
      if (isSearchOpen && 
          searchModalRef.current && 
          !searchModalRef.current.contains(e.target as Node)) {
        setIsSearchOpen(false);
      }
    };

    document.addEventListener('mousedown', handleClickOutside);
    return () => {
      document.removeEventListener('mousedown', handleClickOutside);
    };
  }, [isSearchOpen]);

  // 自定义判断是否激活的函数
  const isLinkActive = (path: string, queryKey: string, queryValue: string) => {
    if (path === '/' && location.pathname === '/') {
      return true;
    }
    
    if (location.pathname.startsWith(path) && path !== '/') {
      const searchParams = new URLSearchParams(location.search);
      const paramValue = searchParams.get(queryKey);
      return paramValue === queryValue;
    }
    
    return false;
  };

  return (
    <header className="fixed top-0 left-0 right-0 z-50 bg-white/90 backdrop-blur-sm shadow-sm">
      <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
        <div className="flex justify-between items-center h-16">
          {/* Logo */}
          <div className="flex-shrink-0 flex items-center">
            <Link to="/" className="text-2xl font-bold text-[#1a365d]">FashionHub</Link>
          </div>

          {/* Desktop Navigation */}
          <nav className="hidden md:flex space-x-8">
            <NavLink 
              to="/" 
              className={({ isActive }) => 
                `px-3 py-2 text-sm font-medium transition-colors ${
                  isActive ? 'text-[#ff6b6b]' : 'text-gray-600 hover:text-[#ff6b6b]'
                }`
              }
            >
              首页
            </NavLink>
            <NavLink 
              to="/products?category=women" 
              className={
                `px-3 py-2 text-sm font-medium transition-colors ${
                  isLinkActive('/products', 'category', 'women') ? 'text-[#ff6b6b]' : 'text-gray-600 hover:text-[#ff6b6b]'
                }`
              }
            >
              女装
            </NavLink>
            <NavLink 
              to="/products?category=men" 
              className={
                `px-3 py-2 text-sm font-medium transition-colors ${
                  isLinkActive('/products', 'category', 'men') ? 'text-[#ff6b6b]' : 'text-gray-600 hover:text-[#ff6b6b]'
                }`
              }
            >
              男装
            </NavLink>
            <NavLink 
              to="/products?category=accessories" 
              className={
                `px-3 py-2 text-sm font-medium transition-colors ${
                  isLinkActive('/products', 'category', 'accessories') ? 'text-[#ff6b6b]' : 'text-gray-600 hover:text-[#ff6b6b]'
                }`
              }
            >
              配饰
            </NavLink>
            <NavLink 
              to="/products?featured=true" 
              className={
                `px-3 py-2 text-sm font-medium transition-colors ${
                  isLinkActive('/products', 'featured', 'true') ? 'text-[#ff6b6b]' : 'text-gray-600 hover:text-[#ff6b6b]'
                }`
              }
            >
              热卖
            </NavLink>
          </nav>

          {/* Search, Cart, and User */}
          <div className="hidden md:flex items-center space-x-4">
            <button 
              onClick={toggleSearch}
              className="p-2 rounded-full hover:bg-gray-100 transition-colors"
            >
              <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor" className="w-5 h-5 text-gray-600">
                <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M21 21l-6-6m2-5a7 7 0 11-14 0 7 7 0 0114 0z" />
              </svg>
            </button>
            <Link to="/cart" className="p-2 rounded-full hover:bg-gray-100 transition-colors relative">
              <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor" className="w-5 h-5 text-gray-600 cart-icon">
                <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M16 11V7a4 4 0 00-8 0v4M5 9h14l1 12H4L5 9z" />
              </svg>
              {cartItemCount > 0 && (
                <span className={`absolute top-0 right-0 w-4 h-4 bg-[#ff6b6b] text-white text-xs rounded-full flex items-center justify-center ${animateBadge ? 'animate-pulse-badge' : ''}`}>
                  {cartItemCount > 99 ? '99+' : cartItemCount}
                </span>
              )}
            </Link>
            <Link to="/profile" className="p-2 rounded-full hover:bg-gray-100 transition-colors">
              <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor" className="w-5 h-5 text-gray-600">
                <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M16 7a4 4 0 11-8 0 4 4 0 018 0zM12 14a7 7 0 00-7 7h14a7 7 0 00-7-7z" />
              </svg>
            </Link>
          </div>

          {/* Mobile menu button */}
          <div className="md:hidden flex items-center space-x-2">
            <button 
              onClick={toggleSearch}
              className="p-2 rounded-md text-gray-600 hover:text-gray-900 hover:bg-gray-100 focus:outline-none"
            >
              <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor" className="w-5 h-5">
                <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M21 21l-6-6m2-5a7 7 0 11-14 0 7 7 0 0114 0z" />
              </svg>
            </button>
            <button 
              onClick={() => setIsMenuOpen(!isMenuOpen)} 
              className="p-2 rounded-md text-gray-600 hover:text-gray-900 hover:bg-gray-100 focus:outline-none"
            >
              <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor" className="w-6 h-6">
                <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d={isMenuOpen ? "M6 18L18 6M6 6l12 12" : "M4 6h16M4 12h16M4 18h16"} />
              </svg>
            </button>
          </div>
        </div>
      </div>

      {/* Mobile menu */}
      {isMenuOpen && (
        <div className="md:hidden bg-white shadow-lg">
          <div className="px-2 pt-2 pb-3 space-y-1 sm:px-3">
            <Link 
              to="/" 
              className={`block px-3 py-2 rounded-md text-base font-medium ${location.pathname === '/' ? 'text-[#ff6b6b]' : 'text-gray-900 hover:bg-gray-50'}`}
              onClick={() => setIsMenuOpen(false)}
            >
              首页
            </Link>
            <Link 
              to="/products?category=women" 
              className={`block px-3 py-2 rounded-md text-base font-medium ${isLinkActive('/products', 'category', 'women') ? 'text-[#ff6b6b]' : 'text-gray-900 hover:bg-gray-50'}`}
              onClick={() => setIsMenuOpen(false)}
            >
              女装
            </Link>
            <Link 
              to="/products?category=men" 
              className={`block px-3 py-2 rounded-md text-base font-medium ${isLinkActive('/products', 'category', 'men') ? 'text-[#ff6b6b]' : 'text-gray-900 hover:bg-gray-50'}`}
              onClick={() => setIsMenuOpen(false)}
            >
              男装
            </Link>
            <Link 
              to="/products?category=accessories" 
              className={`block px-3 py-2 rounded-md text-base font-medium ${isLinkActive('/products', 'category', 'accessories') ? 'text-[#ff6b6b]' : 'text-gray-900 hover:bg-gray-50'}`}
              onClick={() => setIsMenuOpen(false)}
            >
              配饰
            </Link>
            <Link 
              to="/products?featured=true" 
              className={`block px-3 py-2 rounded-md text-base font-medium ${isLinkActive('/products', 'featured', 'true') ? 'text-[#ff6b6b]' : 'text-gray-900 hover:bg-gray-50'}`}
              onClick={() => setIsMenuOpen(false)}
            >
              热卖
            </Link>
          </div>
          <div className="pt-4 pb-3 border-t border-gray-200">
            <div className="flex items-center justify-around px-5">
              <Link to="/cart" className="p-2 rounded-full hover:bg-gray-100 transition-colors relative" onClick={() => setIsMenuOpen(false)}>
                <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor" className="w-5 h-5 text-gray-600 cart-icon">
                  <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M16 11V7a4 4 0 00-8 0v4M5 9h14l1 12H4L5 9z" />
                </svg>
                {cartItemCount > 0 && (
                  <span className={`absolute top-0 right-0 w-4 h-4 bg-[#ff6b6b] text-white text-xs rounded-full flex items-center justify-center ${animateBadge ? 'animate-pulse-badge' : ''}`}>
                    {cartItemCount > 99 ? '99+' : cartItemCount}
                  </span>
                )}
              </Link>
              <Link to="/profile" className="p-2 rounded-full hover:bg-gray-100 transition-colors" onClick={() => setIsMenuOpen(false)}>
                <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor" className="w-5 h-5 text-gray-600">
                  <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M16 7a4 4 0 11-8 0 4 4 0 018 0zM12 14a7 7 0 00-7 7h14a7 7 0 00-7-7z" />
                </svg>
              </Link>
            </div>
          </div>
        </div>
      )}

      {/* 搜索弹窗 - 新设计，无背景 */}
      {isSearchOpen && (
        <div className="fixed inset-0 z-50 flex items-start justify-center pt-24">
          <div 
            ref={searchModalRef}
            className="bg-white p-6 rounded-lg shadow-xl w-full max-w-2xl mx-4 border border-gray-200 animate-fade-in"
          >
            <div className="flex justify-between items-center mb-4">
              <h2 className="text-xl font-bold text-gray-900">搜索商品</h2>
              <button
                onClick={() => setIsSearchOpen(false)}
                className="text-gray-500 hover:text-gray-700 transition-colors"
              >
                <svg xmlns="http://www.w3.org/2000/svg" className="h-6 w-6" fill="none" viewBox="0 0 24 24" stroke="currentColor">
                  <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M6 18L18 6M6 6l12 12" />
                </svg>
              </button>
            </div>
            <Search onClose={() => setIsSearchOpen(false)} isModal={true} />
          </div>
        </div>
      )}
    </header>
  );
};

export default Header; 