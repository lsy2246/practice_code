import { useState } from 'react';
import { Link } from 'react-router-dom';
import { recommendedProducts } from '../data/mockData';
import { useCart } from '../contexts/CartContext';

const Cart = () => {
  const { cartItems, updateQuantity, removeFromCart, clearCart, getCartTotal } = useCart();
  const [loading, setLoading] = useState(false);
  const [couponCode, setCouponCode] = useState('');
  const [couponApplied, setCouponApplied] = useState(false);
  const [couponDiscount, setCouponDiscount] = useState(0);

  // 计算商品小计
  const calculateItemSubtotal = (item: typeof cartItems[0]) => {
    const price = item.discount ? Math.round(item.price * item.discount) : item.price;
    return price * item.quantity;
  };

  // 计算折扣金额
  const calculateDiscount = () => {
    return couponApplied ? couponDiscount : 0;
  };

  // 计算运费
  const calculateShipping = () => {
    const subtotal = getCartTotal();
    return subtotal >= 500 ? 0 : 20; // 满500免运费，否则20元运费
  };

  // 计算总金额
  const calculateTotal = () => {
    return getCartTotal() - calculateDiscount() + calculateShipping();
  };

  // 应用优惠码
  const applyCoupon = () => {
    setLoading(true);
    // 模拟API请求
    setTimeout(() => {
      if (couponCode.toUpperCase() === 'DISCOUNT20') {
        setCouponApplied(true);
        setCouponDiscount(Math.round(getCartTotal() * 0.2)); // 20%折扣
        alert('优惠码已应用：八折优惠');
      } else {
        alert('无效的优惠码');
      }
      setLoading(false);
    }, 800);
  };

  // 确认清空购物车
  const handleClearCart = () => {
    if (window.confirm('确定要清空购物车吗？')) {
      clearCart();
    }
  };

  // 结算
  const checkout = () => {
    alert('跳转到结算页面...');
    // 实际项目中这里会跳转到结算页面
  };

  return (
    <div className="container mx-auto px-4 py-8">
      <h1 className="text-3xl font-bold mb-8">购物车</h1>

      {cartItems.length > 0 ? (
        <div className="flex flex-col lg:flex-row gap-8">
          {/* 购物车商品列表 */}
          <div className="lg:w-2/3">
            <div className="bg-white rounded-lg shadow-sm overflow-hidden">
              <table className="w-full">
                <thead className="bg-gray-50">
                  <tr>
                    <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">商品</th>
                    <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">单价</th>
                    <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">数量</th>
                    <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">小计</th>
                    <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">操作</th>
                  </tr>
                </thead>
                <tbody className="divide-y divide-gray-200">
                  {cartItems.map((item) => (
                    <tr key={item.id}>
                      <td className="px-6 py-4 whitespace-nowrap">
                        <div className="flex items-center">
                          <div className="h-20 w-20 flex-shrink-0 overflow-hidden rounded-md">
                            <img src={item.image} alt={item.name} className="h-full w-full object-cover object-center" />
                          </div>
                          <div className="ml-4">
                            <div className="text-sm font-medium text-gray-900">{item.name}</div>
                            <div className="text-sm text-gray-500">
                              {item.size && <span className="mr-2">尺码: {item.size}</span>}
                              {item.color && <span>颜色: {item.color}</span>}
                            </div>
                          </div>
                        </div>
                      </td>
                      <td className="px-6 py-4 whitespace-nowrap">
                        {item.discount ? (
                          <div>
                            <div className="text-sm font-medium text-[#ff6b6b]">¥{Math.round(item.price * item.discount)}</div>
                            <div className="text-xs text-gray-500 line-through">¥{item.price}</div>
                          </div>
                        ) : (
                          <div className="text-sm font-medium text-gray-900">¥{item.price}</div>
                        )}
                      </td>
                      <td className="px-6 py-4 whitespace-nowrap">
                        <div className="flex items-center">
                          <button
                            onClick={() => updateQuantity(item.id, item.quantity - 1)}
                            className="w-8 h-8 border border-gray-300 rounded-l-md flex items-center justify-center hover:bg-gray-100"
                            disabled={item.quantity <= 1}
                          >
                            <svg className="w-4 h-4 text-gray-600" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                              <path strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M20 12H4" />
                            </svg>
                          </button>
                          <input
                            type="number"
                            value={item.quantity}
                            onChange={(e) => updateQuantity(item.id, parseInt(e.target.value) || 1)}
                            className="w-12 h-8 border-t border-b border-gray-300 text-center focus:outline-none text-sm"
                          />
                          <button
                            onClick={() => updateQuantity(item.id, item.quantity + 1)}
                            className="w-8 h-8 border border-gray-300 rounded-r-md flex items-center justify-center hover:bg-gray-100"
                          >
                            <svg className="w-4 h-4 text-gray-600" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                              <path strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M12 4v16m8-8H4" />
                            </svg>
                          </button>
                        </div>
                      </td>
                      <td className="px-6 py-4 whitespace-nowrap text-sm font-medium text-gray-900">
                        ¥{calculateItemSubtotal(item)}
                      </td>
                      <td className="px-6 py-4 whitespace-nowrap text-right text-sm font-medium">
                        <button
                          onClick={() => removeFromCart(item.id)}
                          className="text-[#ff6b6b] hover:text-[#ff5252]"
                        >
                          删除
                        </button>
                      </td>
                    </tr>
                  ))}
                </tbody>
              </table>
            </div>

            <div className="flex justify-between mt-6">
              <Link to="/products" className="text-[#1a365d] hover:text-[#2a4365] flex items-center">
                <svg className="w-4 h-4 mr-1" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                  <path strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M10 19l-7-7m0 0l7-7m-7 7h18" />
                </svg>
                继续购物
              </Link>
              <button
                onClick={handleClearCart}
                className="text-gray-600 hover:text-gray-900"
              >
                清空购物车
              </button>
            </div>
          </div>

          {/* 订单摘要 */}
          <div className="lg:w-1/3">
            <div className="bg-white rounded-lg shadow-sm p-6">
              <h2 className="text-lg font-medium text-gray-900 mb-4">订单摘要</h2>
              
              <div className="border-t border-gray-200 pt-4">
                <div className="flex justify-between items-center mb-2">
                  <span className="text-gray-600">商品小计</span>
                  <span className="text-gray-900 font-medium">¥{getCartTotal()}</span>
                </div>
                
                {couponApplied && (
                  <div className="flex justify-between items-center mb-2 text-[#ff6b6b]">
                    <span>优惠券折扣</span>
                    <span>-¥{calculateDiscount()}</span>
                  </div>
                )}
                
                <div className="flex justify-between items-center mb-2">
                  <span className="text-gray-600">运费</span>
                  <span className="text-gray-900 font-medium">
                    {calculateShipping() === 0 ? '免运费' : `¥${calculateShipping()}`}
                  </span>
                </div>
                
                <div className="flex justify-between items-center pt-4 border-t border-gray-200 mt-4">
                  <span className="text-lg font-medium text-gray-900">总计</span>
                  <span className="text-xl font-bold text-[#1a365d]">¥{calculateTotal()}</span>
                </div>
              </div>

              {/* 优惠码 */}
              <div className="mt-6">
                <label htmlFor="coupon" className="block text-sm font-medium text-gray-700 mb-2">
                  优惠码
                </label>
                <div className="flex">
                  <input
                    type="text"
                    id="coupon"
                    value={couponCode}
                    onChange={(e) => setCouponCode(e.target.value)}
                    placeholder="输入优惠码"
                    className="flex-1 min-w-0 block w-full px-3 py-2 rounded-l-md border border-gray-300 focus:outline-none focus:ring-[#1a365d] focus:border-[#1a365d]"
                    disabled={couponApplied || loading}
                  />
                  <button
                    onClick={applyCoupon}
                    className={`inline-flex items-center px-4 py-2 border border-transparent text-sm font-medium rounded-r-md text-white ${
                      couponApplied || loading
                        ? 'bg-gray-400 cursor-not-allowed'
                        : 'bg-[#1a365d] hover:bg-[#2a4365]'
                    }`}
                    disabled={couponApplied || loading || !couponCode}
                  >
                    {loading ? (
                      <svg className="animate-spin -ml-1 mr-2 h-4 w-4 text-white" fill="none" viewBox="0 0 24 24">
                        <circle className="opacity-25" cx="12" cy="12" r="10" stroke="currentColor" strokeWidth="4"></circle>
                        <path className="opacity-75" fill="currentColor" d="M4 12a8 8 0 018-8V0C5.373 0 0 5.373 0 12h4zm2 5.291A7.962 7.962 0 014 12H0c0 3.042 1.135 5.824 3 7.938l3-2.647z"></path>
                      </svg>
                    ) : couponApplied ? '已应用' : '应用'}
                  </button>
                </div>
                {couponApplied && (
                  <p className="mt-2 text-sm text-[#ff6b6b]">
                    优惠码已应用：八折优惠
                  </p>
                )}
              </div>

              <button
                onClick={checkout}
                className="w-full mt-6 bg-[#ff6b6b] hover:bg-[#ff5252] text-white py-3 px-4 rounded-md font-medium transition-colors"
              >
                去结算
              </button>
            </div>
          </div>
        </div>
      ) : (
        <div className="text-center py-16 bg-white rounded-lg shadow-sm">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor" className="w-16 h-16 mx-auto text-gray-400 mb-4">
            <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M16 11V7a4 4 0 00-8 0v4M5 9h14l1 12H4L5 9z" />
          </svg>
          <h2 className="text-2xl font-medium text-gray-900 mb-4">购物车是空的</h2>
          <p className="text-gray-600 mb-8">您的购物车中还没有商品，快去选购吧！</p>
          <Link
            to="/products"
            className="inline-block bg-[#1a365d] text-white py-3 px-8 rounded-md hover:bg-[#2a4365] transition-colors"
          >
            浏览商品
          </Link>
        </div>
      )}

      {/* 推荐商品 */}
      {cartItems.length > 0 && (
        <div className="mt-16">
          <h2 className="text-2xl font-bold mb-8">猜您喜欢</h2>
          <div className="grid grid-cols-1 sm:grid-cols-2 md:grid-cols-3 lg:grid-cols-4 gap-6">
            {recommendedProducts.map((product) => (
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
      )}
    </div>
  );
};

export default Cart; 