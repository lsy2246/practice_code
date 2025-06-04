import React, { createContext, useContext, useState, useEffect } from 'react';

// 收藏商品类型
export interface FavoriteItem {
  id: number;
  name: string;
  price: number;
  image: string;
  category: string;
  discount?: number;
  featured?: boolean;
}

// 收藏上下文类型
interface FavoriteContextType {
  favoriteItems: FavoriteItem[];
  addToFavorite: (product: FavoriteItem) => void;
  removeFromFavorite: (id: number) => void;
  clearFavorites: () => void;
  isFavorite: (id: number) => boolean;
  getFavoriteCount: () => number;
}

// 创建上下文
const FavoriteContext = createContext<FavoriteContextType | undefined>(undefined);

// 收藏提供者组件
export const FavoriteProvider: React.FC<{ children: React.ReactNode }> = ({ children }) => {
  const [favoriteItems, setFavoriteItems] = useState<FavoriteItem[]>([]);

  // 初始化时从localStorage加载收藏数据
  useEffect(() => {
    const storedFavorites = localStorage.getItem('favorites');
    if (storedFavorites) {
      try {
        setFavoriteItems(JSON.parse(storedFavorites));
      } catch (error) {
        console.error('收藏数据解析错误:', error);
        localStorage.removeItem('favorites');
      }
    }
  }, []);

  // 当收藏更新时，保存到localStorage
  useEffect(() => {
    localStorage.setItem('favorites', JSON.stringify(favoriteItems));
  }, [favoriteItems]);

  // 添加商品到收藏
  const addToFavorite = (product: FavoriteItem) => {
    setFavoriteItems(prevItems => {
      // 检查商品是否已经收藏
      if (prevItems.some(item => item.id === product.id)) {
        return prevItems;
      }
      // 添加新商品到收藏
      return [...prevItems, product];
    });
  };

  // 从收藏中移除商品
  const removeFromFavorite = (id: number) => {
    setFavoriteItems(prevItems => prevItems.filter(item => item.id !== id));
  };

  // 清空收藏
  const clearFavorites = () => {
    setFavoriteItems([]);
  };

  // 检查商品是否已收藏
  const isFavorite = (id: number) => {
    return favoriteItems.some(item => item.id === id);
  };

  // 获取收藏商品数量
  const getFavoriteCount = () => {
    return favoriteItems.length;
  };

  // 提供上下文值
  const contextValue: FavoriteContextType = {
    favoriteItems,
    addToFavorite,
    removeFromFavorite,
    clearFavorites,
    isFavorite,
    getFavoriteCount
  };

  return (
    <FavoriteContext.Provider value={contextValue}>
      {children}
    </FavoriteContext.Provider>
  );
};

// 自定义hook，用于访问收藏上下文
export const useFavorite = () => {
  const context = useContext(FavoriteContext);
  if (context === undefined) {
    throw new Error('useFavorite必须在FavoriteProvider内部使用');
  }
  return context;
}; 