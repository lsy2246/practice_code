import { useState, useEffect, useCallback } from 'react';

interface CarouselProps {
  items: {
    content: React.ReactNode;
  }[];
  interval?: number;
}

export function Carousel({ 
  items, 
  interval = 5000
}: CarouselProps) {
  const [currentIndex, setCurrentIndex] = useState(0);

  const goToNext = useCallback(() => {
    setCurrentIndex((current) => (current + 1) % items.length);
  }, [items.length]);

  useEffect(() => {
    if (interval > 0) {
      const timer = setInterval(goToNext, interval);
      return () => clearInterval(timer);
    }
  }, [interval, goToNext]);

  return (
    <div className="relative">
      <div className="flex justify-center items-center">
        <div>
          {items[currentIndex].content}
        </div>
      </div>
    </div>
  );
}