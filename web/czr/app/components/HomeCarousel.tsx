import { useState, useEffect } from 'react';

const images = [
  {
    url: "/b1.jpg",
    alt: "绿色科技",
    title: "创新环保技术"
  },
  {
    url: "/b2.jpg",
    alt: "可持续发展",
    title: "可持续未来"
  },
  {
    url: "/b3.jpg",
    alt: "科技创新",
    title: "引领科技创新"
  }
];

export default function HomeCarousel() {
  const [currentIndex, setCurrentIndex] = useState(0);

  useEffect(() => {
    const timer = setInterval(() => {
      setCurrentIndex((prevIndex) => 
        prevIndex === images.length - 1 ? 0 : prevIndex + 1
      );
    }, 5000);

    return () => clearInterval(timer);
  }, []);

  const nextSlide = () => {
    setCurrentIndex((prevIndex) => 
      prevIndex === images.length - 1 ? 0 : prevIndex + 1
    );
  };

  const prevSlide = () => {
    setCurrentIndex((prevIndex) => 
      prevIndex === 0 ? images.length - 1 : prevIndex - 1
    );
  };

  return (
    <div className="max-w-5xl mx-auto my-8">
      <div className="relative w-full h-[400px] overflow-hidden rounded-xl">
        {/* 图片容器 */}
        <div 
          className="absolute w-full h-full transition-transform duration-500 ease-in-out"
          style={{ transform: `translateX(-${currentIndex * 100}%)` }}
        >
          {images.map((image, index) => (
            <div
              key={index}
              className="absolute w-full h-full"
              style={{ left: `${index * 100}%` }}
            >
              <img
                src={image.url}
                alt={image.alt}
                className="w-full h-full object-cover"
              />
              <div className="absolute inset-0 bg-black bg-opacity-30">
                <div className="absolute bottom-20 left-1/2 transform -translate-x-1/2 text-white text-center">
                  <h2 className="text-4xl font-bold mb-4">{image.title}</h2>
                </div>
              </div>
            </div>
          ))}
        </div>

        {/* 修改控制按钮样式 */}
        <button
          onClick={prevSlide}
          className="absolute left-4 top-1/2 transform -translate-y-1/2 bg-white/20 hover:bg-white/40 backdrop-blur-sm w-10 h-10 rounded-full flex items-center justify-center transition-all duration-200"
          aria-label="上一张"
        >
          <svg 
            className="w-6 h-6 text-white" 
            fill="none" 
            stroke="currentColor" 
            viewBox="0 0 24 24"
          >
            <path 
              strokeLinecap="round" 
              strokeLinejoin="round" 
              strokeWidth={2} 
              d="M15 19l-7-7 7-7"
            />
          </svg>
        </button>
        <button
          onClick={nextSlide}
          className="absolute right-4 top-1/2 transform -translate-y-1/2 bg-white/20 hover:bg-white/40 backdrop-blur-sm w-10 h-10 rounded-full flex items-center justify-center transition-all duration-200"
          aria-label="下一张"
        >
          <svg 
            className="w-6 h-6 text-white" 
            fill="none" 
            stroke="currentColor" 
            viewBox="0 0 24 24"
          >
            <path 
              strokeLinecap="round" 
              strokeLinejoin="round" 
              strokeWidth={2} 
              d="M9 5l7 7-7 7"
            />
          </svg>
        </button>

        {/* 指示器 */}
        <div className="absolute bottom-4 left-1/2 transform -translate-x-1/2 flex space-x-2">
          {images.map((_, index) => (
            <button
              key={index}
              onClick={() => setCurrentIndex(index)}
              className={`w-3 h-3 rounded-full ${
                currentIndex === index ? 'bg-white' : 'bg-white bg-opacity-50'
              }`}
            />
          ))}
        </div>
      </div>
    </div>
  );
} 