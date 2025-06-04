import { useState, useEffect, useRef } from 'react';
import { useNavigate } from 'react-router-dom';
import { allProducts } from '../data/mockData';

interface SearchProps {
  onClose?: () => void;
  isModal?: boolean;
}

const Search = ({ onClose, isModal = false }: SearchProps) => {
  const [query, setQuery] = useState('');
  const [suggestions, setSuggestions] = useState<typeof allProducts>([]);
  const navigate = useNavigate();
  const inputRef = useRef<HTMLInputElement>(null);

  // 当作为模态框展示时，自动聚焦到输入框
  useEffect(() => {
    if (isModal && inputRef.current) {
      inputRef.current.focus();
    }
  }, [isModal]);

  // 处理输入变化
  const handleInputChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const value = e.target.value;
    setQuery(value);

    // 当输入为空时，清空建议
    if (value.trim() === '') {
      setSuggestions([]);
      return;
    }

    // 根据输入过滤产品，最多展示5个建议
    const filtered = allProducts
      .filter(product => 
        product.name.toLowerCase().includes(value.toLowerCase()) ||
        product.category.toLowerCase().includes(value.toLowerCase())
      )
      .slice(0, 5);
    
    setSuggestions(filtered);
  };

  // 处理搜索提交
  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault();
    if (query.trim()) {
      // 跳转到搜索结果页面
      navigate(`/search?q=${encodeURIComponent(query.trim())}`);
      // 清空当前输入和建议
      setQuery('');
      setSuggestions([]);
      // 如果有关闭回调，则调用
      if (onClose) onClose();
    }
  };

  // 处理建议点击
  const handleSuggestionClick = (productId: number) => {
    // 跳转到产品详情页
    navigate(`/products/${productId}`);
    // 清空当前输入和建议
    setQuery('');
    setSuggestions([]);
    // 如果有关闭回调，则调用
    if (onClose) onClose();
  };

  // 转换分类名称为中文
  const getCategoryName = (category: string) => {
    switch (category) {
      case 'women': return '女装';
      case 'men': return '男装';
      case 'accessories': return '配饰';
      default: return category;
    }
  };

  return (
    <div className="w-full">
      <form onSubmit={handleSubmit} className="relative">
        <div className="relative">
          <input
            ref={inputRef}
            type="text"
            value={query}
            onChange={handleInputChange}
            placeholder="搜索商品..."
            className="w-full p-3 pl-10 pr-12 border border-gray-300 rounded-lg focus:outline-none focus:ring-2 focus:ring-[#ff6b6b] focus:border-transparent"
          />
          <div className="absolute inset-y-0 left-0 pl-3 flex items-center pointer-events-none">
            <svg xmlns="http://www.w3.org/2000/svg" className="h-5 w-5 text-gray-400" viewBox="0 0 20 20" fill="currentColor">
              <path fillRule="evenodd" d="M8 4a4 4 0 100 8 4 4 0 000-8zM2 8a6 6 0 1110.89 3.476l4.817 4.817a1 1 0 01-1.414 1.414l-4.816-4.816A6 6 0 012 8z" clipRule="evenodd" />
            </svg>
          </div>
          <button
            type="submit"
            className="absolute inset-y-0 right-0 pr-3 flex items-center text-sm font-medium text-[#ff6b6b] hover:text-[#ff8383]"
          >
            搜索
          </button>
        </div>

        {/* 搜索建议下拉框 */}
        {suggestions.length > 0 && (
          <div className="absolute z-10 w-full mt-1 bg-white rounded-md shadow-lg max-h-80 overflow-y-auto">
            <ul className="py-1">
              {suggestions.map((product) => (
                <li 
                  key={product.id}
                  onClick={() => handleSuggestionClick(product.id)}
                  className="px-4 py-2 hover:bg-gray-100 cursor-pointer"
                >
                  <div className="flex items-center">
                    <img src={product.image} alt={product.name} className="w-12 h-12 object-cover rounded mr-3" />
                    <div>
                      <div className="text-sm font-medium text-gray-900">{product.name}</div>
                      <div className="text-xs text-gray-500 flex items-center">
                        <span className="bg-gray-200 rounded px-1.5 py-0.5 text-xs mr-2">
                          {getCategoryName(product.category)}
                        </span>
                        <span className="text-[#ff6b6b] font-medium">
                          ¥{product.price.toFixed(2)}
                        </span>
                        {product.discount && (
                          <span className="ml-1 line-through text-gray-400">
                            ¥{(product.price / (1 - product.discount)).toFixed(2)}
                          </span>
                        )}
                      </div>
                    </div>
                  </div>
                </li>
              ))}
            </ul>
          </div>
        )}
      </form>
    </div>
  );
};

export default Search; 