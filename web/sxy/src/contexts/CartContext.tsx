import React, { createContext, useContext, useState, useEffect } from 'react';

// 购物车商品类型
export interface CartItem {
  id: number;
  productId: number;
  name: string;
  price: number;
  image: string;
  discount?: number;
  quantity: number;
  size?: string;
  color?: string;
}

// 购物车上下文类型
interface CartContextType {
  cartItems: CartItem[];
  addToCart: (item: CartItem) => void;
  updateQuantity: (id: number, quantity: number) => void;
  removeFromCart: (id: number) => void;
  clearCart: () => void;
  getCartTotal: () => number;
  getCartCount: () => number;
}

// 创建上下文
const CartContext = createContext<CartContextType | undefined>(undefined);

// 购物车提供者组件
export const CartProvider: React.FC<{ children: React.ReactNode }> = ({ children }) => {
  const [cartItems, setCartItems] = useState<CartItem[]>([]);

  // 初始化时从localStorage加载购物车数据
  useEffect(() => {
    const storedCart = localStorage.getItem('cart');
    if (storedCart) {
      try {
        setCartItems(JSON.parse(storedCart));
      } catch (error) {
        console.error('购物车数据解析错误:', error);
        localStorage.removeItem('cart');
      }
    }
  }, []);

  // 当购物车更新时，保存到localStorage
  useEffect(() => {
    localStorage.setItem('cart', JSON.stringify(cartItems));
  }, [cartItems]);

  // 添加商品到购物车
  const addToCart = (item: CartItem) => {
    setCartItems(prevItems => {
      const existingItemIndex = prevItems.findIndex(
        cartItem => 
          cartItem.productId === item.productId && 
          cartItem.size === item.size && 
          cartItem.color === item.color
      );

      if (existingItemIndex !== -1) {
        // 如果商品已经在购物车中，更新数量
        const updatedItems = [...prevItems];
        updatedItems[existingItemIndex].quantity += item.quantity;
        return updatedItems;
      } else {
        // 否则添加新商品
        return [...prevItems, { ...item, id: Date.now() }]; // 使用时间戳作为唯一ID
      }
    });
  };

  // 更新商品数量
  const updateQuantity = (id: number, quantity: number) => {
    if (quantity < 1) return;
    
    setCartItems(prevItems => 
      prevItems.map(item => 
        item.id === id ? { ...item, quantity } : item
      )
    );
  };

  // 从购物车移除商品
  const removeFromCart = (id: number) => {
    setCartItems(prevItems => prevItems.filter(item => item.id !== id));
  };

  // 清空购物车
  const clearCart = () => {
    setCartItems([]);
  };

  // 计算购物车总金额
  const getCartTotal = () => {
    return cartItems.reduce((total, item) => {
      const itemPrice = item.discount 
        ? Math.round(item.price * item.discount) 
        : item.price;
      return total + (itemPrice * item.quantity);
    }, 0);
  };

  // 获取购物车商品总数
  const getCartCount = () => {
    return cartItems.reduce((count, item) => count + item.quantity, 0);
  };

  // 提供上下文值
  const contextValue: CartContextType = {
    cartItems,
    addToCart,
    updateQuantity,
    removeFromCart,
    clearCart,
    getCartTotal,
    getCartCount
  };

  return (
    <CartContext.Provider value={contextValue}>
      {children}
    </CartContext.Provider>
  );
};

// 自定义hook，用于访问购物车上下文
export const useCart = () => {
  const context = useContext(CartContext);
  if (context === undefined) {
    throw new Error('useCart必须在CartProvider内部使用');
  }
  return context;
}; 