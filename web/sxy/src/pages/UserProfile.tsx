import { useState } from 'react';
import { userData, orderData } from '../data/mockData';
import { useFavorite } from '../contexts/FavoriteContext';
import { useCart } from '../contexts/CartContext';

const UserProfile = () => {
  const [activeTab, setActiveTab] = useState('profile');
  const [user, setUser] = useState(userData);
  const [orders] = useState(orderData);
  const { favoriteItems, removeFromFavorite } = useFavorite();
  const { addToCart } = useCart();
  const [editMode, setEditMode] = useState(false);
  const [formData, setFormData] = useState({
    name: user.name,
    email: user.email,
    phone: user.phone,
  });

  // 处理表单输入变化
  const handleInputChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const { name, value } = e.target;
    setFormData(prev => ({ ...prev, [name]: value }));
  };

  // 保存个人信息
  const handleSaveProfile = () => {
    setUser(prev => ({ ...prev, ...formData }));
    setEditMode(false);
    alert('个人信息已更新');
  };

  // 移除收藏
  const handleRemoveFavorite = (id: number) => {
    removeFromFavorite(id);
  };

  // 添加到购物车
  const handleAddToCart = (item: any) => {
    addToCart({
      id: Date.now(),
      productId: item.id,
      name: item.name,
      price: item.price,
      image: item.image,
      quantity: 1,
      discount: item.discount,
    });
    alert('已添加到购物车');
  };

  // 获取订单状态文本
  const getOrderStatusText = (status: string) => {
    switch (status) {
      case 'pending': return '待付款';
      case 'processing': return '处理中';
      case 'shipped': return '已发货';
      case 'delivered': return '已完成';
      case 'cancelled': return '已取消';
      default: return '未知状态';
    }
  };

  // 获取订单状态类名
  const getOrderStatusClass = (status: string) => {
    switch (status) {
      case 'pending': return 'bg-yellow-100 text-yellow-800';
      case 'processing': return 'bg-blue-100 text-blue-800';
      case 'shipped': return 'bg-purple-100 text-purple-800';
      case 'delivered': return 'bg-green-100 text-green-800';
      case 'cancelled': return 'bg-red-100 text-red-800';
      default: return 'bg-gray-100 text-gray-800';
    }
  };

  return (
    <div className="container mx-auto px-4 py-8">
      <h1 className="text-3xl font-bold mb-8">我的账户</h1>

      <div className="flex flex-col md:flex-row gap-8">
        {/* 侧边栏 */}
        <div className="md:w-1/4">
          <div className="bg-white rounded-lg shadow-sm overflow-hidden">
            <div className="p-6 border-b border-gray-200">
              <div className="flex items-center">
                <img src={user.avatar} alt={user.name} className="w-16 h-16 rounded-full object-cover" />
                <div className="ml-4">
                  <h3 className="text-lg font-medium text-gray-900">{user.name}</h3>
                  <p className="text-sm text-gray-600">{user.email}</p>
                </div>
              </div>
            </div>
            <nav className="p-4">
              <button
                onClick={() => setActiveTab('profile')}
                className={`w-full text-left px-4 py-2 rounded-md mb-1 ${
                  activeTab === 'profile'
                    ? 'bg-[#1a365d] text-white'
                    : 'text-gray-700 hover:bg-gray-100'
                }`}
              >
                个人信息
              </button>
              <button
                onClick={() => setActiveTab('orders')}
                className={`w-full text-left px-4 py-2 rounded-md mb-1 ${
                  activeTab === 'orders'
                    ? 'bg-[#1a365d] text-white'
                    : 'text-gray-700 hover:bg-gray-100'
                }`}
              >
                我的订单
              </button>
              <button
                onClick={() => setActiveTab('address')}
                className={`w-full text-left px-4 py-2 rounded-md mb-1 ${
                  activeTab === 'address'
                    ? 'bg-[#1a365d] text-white'
                    : 'text-gray-700 hover:bg-gray-100'
                }`}
              >
                收货地址
              </button>
              <button
                onClick={() => setActiveTab('favorites')}
                className={`w-full text-left px-4 py-2 rounded-md mb-1 ${
                  activeTab === 'favorites'
                    ? 'bg-[#1a365d] text-white'
                    : 'text-gray-700 hover:bg-gray-100'
                }`}
              >
                我的收藏
              </button>
            </nav>
          </div>
        </div>

        {/* 主内容区 */}
        <div className="md:w-3/4">
          <div className="bg-white rounded-lg shadow-sm p-6">
            {/* 个人信息 */}
            {activeTab === 'profile' && (
              <div>
                <div className="flex justify-between items-center mb-6">
                  <h2 className="text-xl font-medium text-gray-900">个人信息</h2>
                  <button
                    onClick={() => setEditMode(!editMode)}
                    className="text-[#1a365d] hover:text-[#2a4365]"
                  >
                    {editMode ? '取消' : '编辑'}
                  </button>
                </div>

                {editMode ? (
                  <form onSubmit={(e) => { e.preventDefault(); handleSaveProfile(); }}>
                    <div className="mb-4">
                      <label htmlFor="name" className="block text-sm font-medium text-gray-700 mb-1">
                        姓名
                      </label>
                      <input
                        type="text"
                        id="name"
                        name="name"
                        value={formData.name}
                        onChange={handleInputChange}
                        className="w-full px-3 py-2 border border-gray-300 rounded-md focus:outline-none focus:ring-[#1a365d] focus:border-[#1a365d]"
                      />
                    </div>
                    <div className="mb-4">
                      <label htmlFor="email" className="block text-sm font-medium text-gray-700 mb-1">
                        邮箱
                      </label>
                      <input
                        type="email"
                        id="email"
                        name="email"
                        value={formData.email}
                        onChange={handleInputChange}
                        className="w-full px-3 py-2 border border-gray-300 rounded-md focus:outline-none focus:ring-[#1a365d] focus:border-[#1a365d]"
                      />
                    </div>
                    <div className="mb-6">
                      <label htmlFor="phone" className="block text-sm font-medium text-gray-700 mb-1">
                        手机号码
                      </label>
                      <input
                        type="tel"
                        id="phone"
                        name="phone"
                        value={formData.phone}
                        onChange={handleInputChange}
                        className="w-full px-3 py-2 border border-gray-300 rounded-md focus:outline-none focus:ring-[#1a365d] focus:border-[#1a365d]"
                      />
                    </div>
                    <button
                      type="submit"
                      className="bg-[#1a365d] text-white py-2 px-4 rounded-md hover:bg-[#2a4365] transition-colors"
                    >
                      保存
                    </button>
                  </form>
                ) : (
                  <div>
                    <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
                      <div>
                        <h3 className="text-sm font-medium text-gray-500">姓名</h3>
                        <p className="mt-1 text-gray-900">{user.name}</p>
                      </div>
                      <div>
                        <h3 className="text-sm font-medium text-gray-500">邮箱</h3>
                        <p className="mt-1 text-gray-900">{user.email}</p>
                      </div>
                      <div>
                        <h3 className="text-sm font-medium text-gray-500">手机号码</h3>
                        <p className="mt-1 text-gray-900">{user.phone}</p>
                      </div>
                    </div>

                    <div className="mt-8">
                      <h3 className="text-lg font-medium text-gray-900 mb-4">账户安全</h3>
                      <div className="border-t border-gray-200 pt-4">
                        <div className="flex justify-between items-center">
                          <div>
                            <h4 className="text-sm font-medium text-gray-900">登录密码</h4>
                            <p className="text-sm text-gray-500">定期更改密码可以保护账户安全</p>
                          </div>
                          <button className="text-[#1a365d] hover:text-[#2a4365] text-sm">
                            修改
                          </button>
                        </div>
                      </div>
                    </div>
                  </div>
                )}
              </div>
            )}

            {/* 订单列表 */}
            {activeTab === 'orders' && (
              <div>
                <h2 className="text-xl font-medium text-gray-900 mb-6">我的订单</h2>
                
                {orders.length > 0 ? (
                  <div className="space-y-6">
                    {orders.map((order) => (
                      <div key={order.id} className="border border-gray-200 rounded-lg overflow-hidden">
                        <div className="bg-gray-50 px-4 py-3 flex justify-between items-center">
                          <div>
                            <span className="text-sm text-gray-500">订单号: {order.id}</span>
                            <span className="mx-3 text-gray-300">|</span>
                            <span className="text-sm text-gray-500">下单时间: {order.date}</span>
                          </div>
                          <span className={`px-2 py-1 text-xs font-medium rounded-full ${getOrderStatusClass(order.status)}`}>
                            {getOrderStatusText(order.status)}
                          </span>
                        </div>
                        
                        <div className="p-4">
                          {order.items.map((item) => (
                            <div key={item.id} className="flex items-center py-2">
                              <img src={item.image} alt={item.name} className="w-16 h-16 object-cover rounded-md" />
                              <div className="ml-4 flex-1">
                                <h3 className="text-sm font-medium">{item.name}</h3>
                                <p className="text-sm text-gray-500">数量: {item.quantity}</p>
                              </div>
                              <div className="text-right">
                                <p className="text-sm font-medium">
                                  {item.discount ? (
                                    <>
                                      <span className="text-[#ff6b6b]">¥{Math.round(item.price * item.discount)}</span>
                                      <span className="text-gray-400 line-through ml-1 text-xs">¥{item.price}</span>
                                    </>
                                  ) : (
                                    <span>¥{item.price}</span>
                                  )}
                                </p>
                              </div>
                            </div>
                          ))}
                        </div>
                        
                        <div className="bg-gray-50 px-4 py-3 flex justify-between items-center">
                          <div></div>
                          <div className="flex items-center">
                            <span className="text-sm text-gray-700 mr-4">总计: <span className="font-medium">¥{order.total}</span></span>
                            <button className="px-4 py-1 border border-[#1a365d] text-[#1a365d] rounded-md text-sm hover:bg-[#1a365d] hover:text-white transition-colors">
                              查看详情
                            </button>
                          </div>
                        </div>
                      </div>
                    ))}
                  </div>
                ) : (
                  <div className="text-center py-8">
                    <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor" className="w-12 h-12 mx-auto text-gray-400 mb-4">
                      <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M9 5H7a2 2 0 00-2 2v12a2 2 0 002 2h10a2 2 0 002-2V7a2 2 0 00-2-2h-2M9 5a2 2 0 002 2h2a2 2 0 002-2M9 5a2 2 0 012-2h2a2 2 0 012 2" />
                    </svg>
                    <h3 className="text-lg font-medium text-gray-900 mb-2">暂无订单</h3>
                    <p className="text-gray-600">您还没有任何订单记录</p>
                  </div>
                )}
              </div>
            )}

            {/* 收货地址 */}
            {activeTab === 'address' && (
              <div>
                <div className="flex justify-between items-center mb-6">
                  <h2 className="text-xl font-medium text-gray-900">收货地址</h2>
                  <button className="bg-[#1a365d] text-white py-1 px-3 rounded-md text-sm hover:bg-[#2a4365] transition-colors">
                    添加新地址
                  </button>
                </div>
                
                <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
                  {user.address.map((addr) => (
                    <div key={addr.id} className={`border rounded-lg p-4 relative ${addr.isDefault ? 'border-[#1a365d]' : 'border-gray-200'}`}>
                      {addr.isDefault && (
                        <span className="absolute top-2 right-2 bg-[#1a365d] text-white text-xs px-2 py-1 rounded-full">
                          默认地址
                        </span>
                      )}
                      <h3 className="font-medium">{addr.name}</h3>
                      <p className="text-gray-600 mt-1">{addr.phone}</p>
                      <p className="text-gray-600 mt-1">
                        {addr.province} {addr.city} {addr.district} {addr.detail}
                      </p>
                      <div className="mt-4 flex space-x-4">
                        <button className="text-[#1a365d] text-sm hover:text-[#2a4365]">
                          编辑
                        </button>
                        <button className="text-gray-600 text-sm hover:text-gray-900">
                          删除
                        </button>
                        {!addr.isDefault && (
                          <button className="text-[#ff6b6b] text-sm hover:text-[#ff5252]">
                            设为默认
                          </button>
                        )}
                      </div>
                    </div>
                  ))}
                </div>
              </div>
            )}

            {/* 收藏列表 */}
            {activeTab === 'favorites' && (
              <div>
                <h2 className="text-xl font-medium text-gray-900 mb-6">我的收藏</h2>
                
                {favoriteItems.length > 0 ? (
                  <div className="grid grid-cols-1 sm:grid-cols-2 md:grid-cols-3 gap-4">
                    {favoriteItems.map((item) => (
                      <div key={item.id} className="border border-gray-200 rounded-lg overflow-hidden group">
                        <div className="relative h-48">
                          <img src={item.image} alt={item.name} className="w-full h-full object-cover" />
                          <button
                            onClick={() => handleRemoveFavorite(item.id)}
                            className="absolute top-2 right-2 bg-white/80 rounded-full p-1.5 opacity-0 group-hover:opacity-100 transition-opacity"
                          >
                            <svg className="w-4 h-4 text-gray-600" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                              <path strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M6 18L18 6M6 6l12 12" />
                            </svg>
                          </button>
                        </div>
                        <div className="p-4">
                          <h3 className="font-medium text-gray-900">{item.name}</h3>
                          <div className="mt-1">
                            {item.discount ? (
                              <div className="flex items-center">
                                <span className="text-[#ff6b6b] font-medium">¥{Math.round(item.price * item.discount)}</span>
                                <span className="text-gray-400 line-through ml-2 text-sm">¥{item.price}</span>
                              </div>
                            ) : (
                              <span className="font-medium">¥{item.price}</span>
                            )}
                          </div>
                          <button 
                            onClick={() => handleAddToCart(item)}
                            className="mt-3 w-full bg-[#1a365d] text-white py-1 px-3 rounded-md text-sm hover:bg-[#2a4365] transition-colors"
                          >
                            加入购物车
                          </button>
                        </div>
                      </div>
                    ))}
                  </div>
                ) : (
                  <div className="text-center py-8">
                    <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor" className="w-12 h-12 mx-auto text-gray-400 mb-4">
                      <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M4.318 6.318a4.5 4.5 0 000 6.364L12 20.364l7.682-7.682a4.5 4.5 0 00-6.364-6.364L12 7.636l-1.318-1.318a4.5 4.5 0 00-6.364 0z" />
                    </svg>
                    <h3 className="text-lg font-medium text-gray-900 mb-2">暂无收藏</h3>
                    <p className="text-gray-600">您还没有收藏任何商品</p>
                  </div>
                )}
              </div>
            )}
          </div>
        </div>
      </div>
    </div>
  );
};

export default UserProfile; 