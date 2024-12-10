import { useEffect, useRef, useState } from 'react';
import gsap from 'gsap';
import { CustomEase } from 'gsap/CustomEase';
import ScrollTrigger from 'gsap/ScrollTrigger';
import Lenis from '@studio-freight/lenis';
import './Parallax.css';
import layer1 from '../assets/b1.png';
import layer2 from '../assets/b2.webp';
import layer3 from '../assets/b3.webp';

import { ImageModal } from './ImageModal';

// 导入旅行图片
import changbaishan from '../assets/a/changbaishan.jpg';
import chongqing from '../assets/a/chongqing.jpg';
import haerbing from '../assets/a/haerbing.jpg';
import qindao from '../assets/a/qindao.jpg';
import qinghuangdao from '../assets/a/qinghuangdao.jpg';
import shichuan from '../assets/a/shichuan.jpg';
import tianjin from '../assets/a/tianjin.jpg';
import xizhang from '../assets/a/xizhang.jpg';
import taian from '../assets/a/taian.jpg';

// 导入滑动卡片图片
import a1 from '../assets/b/a1.jpg';
import a2 from '../assets/b/a2.jpg';
import a3 from '../assets/b/a3.jpg';
import a4 from '../assets/b/a4.jpg';
import a5 from '../assets/b/a5.jpg';
import a6 from '../assets/b/a6.jpg';
import a7 from '../assets/b/a7.jpg';
import a8 from '../assets/b/a8.jpg';
import a9 from '../assets/b/a9.jpg';
import a10 from '../assets/b/a10.jpg';
import a11 from '../assets/b/a11.jpg';
import a12 from '../assets/b/a12.jpg';
import a13 from '../assets/b/a13.jpg';
import a14 from '../assets/b/a14.jpg';
import a15 from '../assets/b/a15.jpg';
import a16 from '../assets/b/a16.jpg';
import a17 from '../assets/b/a17.jpg';
import a18 from '../assets/b/a18.jpg';
import a19 from '../assets/b/a19.jpg';
import a20 from '../assets/b/a20.jpg';
import a21 from '../assets/b/a21.jpg';

gsap.registerPlugin(CustomEase, ScrollTrigger);

// 添加 CustomEase
CustomEase.create("cubic", "0.83, 0, 0.17, 1");

// 在组件外部创建图片数组
const allImages = [
  a1, a2, a3, a4, a5, a6, a7, a8, a9, a10,
  a11, a12, a13, a14, a15, a16, a17, a18,
  a19, a20, a21
];

// 在组件外部添加一个用于跟踪最近使用的图片的数组
let recentlyUsedImages: typeof allImages[number][] = [];

// 修改节流函数，使用闭包来保存状态
function throttle(func: Function, limit: number) {
  let inThrottle: boolean;
  let lastResult: any;
  return function(this: any, ...args: any[]) {
    if (!inThrottle) {
      lastResult = func.apply(this, args);
      inThrottle = true;
      setTimeout(() => {
        inThrottle = false;
      }, limit);
    }
    return lastResult;
  }
}

// 在组件内部，但在 useEffect 外部定义
function initializeCards() {
  const cards = Array.from(document.querySelectorAll(".card"));
  gsap.set(cards, {
    y: i => -15 + (15 * i) + "%",
    z: i => 15 * i,
    transformOrigin: "50% 50%"
  });
}

export const Parallax = () => {
  const layersRef = useRef<HTMLDivElement>(null);
  const [selectedImage, setSelectedImage] = useState<string | null>(null);
  const [displayedCards, setDisplayedCards] = useState<string[]>(() => {
    const shuffled = [...allImages].sort(() => 0.5 - Math.random());
    const initial = shuffled.slice(0, 5);
    return initial;
  });
  


  useEffect(() => {
    const lenis = new Lenis({
      duration: 1.2,
      orientation: 'vertical',
      gestureOrientation: 'vertical',
      smoothWheel: true,
    });
    
    let rafId: number;
    let isAnimating = false;
    let autoPlayInterval: ReturnType<typeof setInterval>;

    function raf(time: number) {
      lenis.raf(time);
      rafId = requestAnimationFrame(raf);
    }
    rafId = requestAnimationFrame(raf);

    const scrollHandler = () => {
      ScrollTrigger.update();
    };

    lenis.on('scroll', scrollHandler);
    
    if (layersRef.current) {
      const tl = gsap.timeline({
        scrollTrigger: {
          trigger: layersRef.current,
          start: "top top",
          end: "bottom top",
          scrub: 1,
          invalidateOnRefresh: true,
        }
      });

      const layers = [
        { layer: "1", yPercent: 50 },
        { layer: "2", yPercent: 35 },
        { layer: "3", yPercent: 25 },
        { layer: "4", yPercent: 15 }
      ];

      layers.forEach((layerObj) => {
        const element = layersRef.current!.querySelector(`[data-parallax-layer="${layerObj.layer}"]`);
        if (element) {
          gsap.set(element, {
            y: 0,
            force3D: true
          });
          
          tl.to(element, {
            yPercent: layerObj.yPercent,
            ease: "none",
            force3D: true,
          }, 0);
        }
      });
    }

    // 修改 handleClick 函数
    const handleClick = () => {
      if (isAnimating) return;
      isAnimating = true;

      const slider = document.querySelector(".slider");
      if (!slider) return;

      const cards = Array.from(slider.querySelectorAll(".card"));
      const lastCard = cards[cards.length - 1];
      
      if (lastCard) {
        const currentDisplayed = new Set(displayedCards);
        const usedImages = new Set(recentlyUsedImages);
        const availableImages = allImages.filter(img => 
          !currentDisplayed.has(img) && !usedImages.has(img)
        );
        
        let newImage: string;
        
        if (availableImages.length < 5) {
          recentlyUsedImages = [];
          const newAvailableImages = allImages.filter(img => !currentDisplayed.has(img));
          const randomIndex = Math.floor(Math.random() * newAvailableImages.length);
          newImage = newAvailableImages[randomIndex];
        } else {
          const randomIndex = Math.floor(Math.random() * availableImages.length);
          newImage = availableImages[randomIndex];
        }
        
        recentlyUsedImages.push(newImage);

        // 更新状态，新图片添加到开头
        const newState = [newImage, ...displayedCards.slice(0, -1)];
        setDisplayedCards(newState);

        // 先创建新的卡片元素
        const newCard = lastCard.cloneNode(true) as HTMLElement;
        const newImg = newCard.querySelector('img');
        if (newImg) {
          newImg.src = newImage;
        }

        // 执行动画
        gsap.to(lastCard, {
          y: "+=150%",
          duration: 0.75,
          ease: "cubic",
          onComplete: () => {
            // 用新卡片替换旧卡片
            slider.replaceChild(newCard, lastCard);
            slider.prepend(newCard);
            
            gsap.set(cards, {
              clearProps: "all"
            });
            initializeCards();
            isAnimating = false;
          }
        });
      }
    };

    // 动播放函数
    const autoPlay = () => {
      if (!isAnimating) {
        handleClick();
      }
    };

    // 节流后的点击处理函数
    const throttledHandleClick = throttle(handleClick, 1000);

    // 开始自动播放
    autoPlayInterval = setInterval(autoPlay, 2000);

    // 鼠标进入时暂停自动播放
    const handleMouseEnter = () => {
      clearInterval(autoPlayInterval);
    };

    // 鼠标离开时恢复自动播放
    const handleMouseLeave = () => {
      autoPlayInterval = setInterval(autoPlay, 2000);
    };

    // 初始化卡片位置
    initializeCards();

    const slider = document.querySelector(".slider");
    if (slider) {
      slider.addEventListener("click", throttledHandleClick);
      slider.addEventListener("mouseenter", handleMouseEnter);
      slider.addEventListener("mouseleave", handleMouseLeave);
    }

    return () => {
      if (rafId) {
        cancelAnimationFrame(rafId);
      }
      const slider = document.querySelector(".slider");
      if (slider) {
        slider.removeEventListener("click", throttledHandleClick);
        slider.removeEventListener("mouseenter", handleMouseEnter);
        slider.removeEventListener("mouseleave", handleMouseLeave);
      }
      clearInterval(autoPlayInterval);
      lenis.destroy();
      ScrollTrigger.getAll().forEach(trigger => trigger.kill());
    };
  }, []);

  // 3. 添加始化函数
  useEffect(() => {
    // 只保留卡片初始化
    initializeCards();
  }, []);

  return (
    <div className="parallax">
      <section className="parallax__header">
        <div className="parallax__visuals">
          <div className="parallax__black-line-overflow"></div>
          <div ref={layersRef} data-parallax-layers className="parallax__layers">
            <img 
              src={layer3}
              loading="eager"
              width="800"
              data-parallax-layer="1"
              alt=""
              className="parallax__layer-img"
            />
            <img 
              src={layer2}
              loading="eager"
              width="800"
              data-parallax-layer="2"
              alt=""
              className="parallax__layer-img"
            />
            <div data-parallax-layer="3" className="parallax__layer-title">
              <h2 className="parallax__title">旅行故事</h2>
            </div>
            <img 
              src={layer1}
              loading="eager"
              width="800"
              data-parallax-layer="4"
              alt=""
              className="parallax__layer-img"
            />
          </div>
          <div className="parallax__fade"></div>
        </div>
      </section>
      <section className="parallax__content">
        <div className="travel-grid">
          <div className="travel-item" onClick={() => setSelectedImage(xizhang)}>
            <h3>西藏</h3>
            <p>在海拔4000米的高原上，感受着最接近天空的信仰。布达拉宫的庄严肃穆，大昭寺的虔诚香火，以及纳木错圣湖的碧蓝湖水，都让人内心无比平静。高原的星空璀璨得让人屏息。</p>
          </div>
          
          <div className="travel-item" onClick={() => setSelectedImage(shichuan)}>
            <h3>四川</h3>
            <p>在成都的宽窄巷子，感受悠闲的四川文化。稻城丁的雪山、草与湖泊构成了人间最后的香格里拉。乐山大佛巍峨庄严，都江堰千年智慧，让人不禁感叹古人的匠心。</p>
          </div>
          
          <div className="travel-item" onClick={() => setSelectedImage(chongqing)}>
            <h3>重庆</h3>
            <p>夜幕降临，这座不夜城开始绽放光。洪崖洞层层叠叠的灯光倒映在江面，两江交汇处的璀璨夜景令人沉醉。子坝轻轨穿楼而过，解放碑的繁华夜色，构成了这座立体城市最迷人的画卷。</p>
          </div>

          <div className="travel-item" onClick={() => setSelectedImage(haerbing)}>
            <h3>哈尔滨</h3>
            <p>冰雪世界的晶莹剔透，中央大街的欧式建筑，松花江的冰雪奇缘。在零下20度的寒冬感受着这座城市独特的俄罗斯风情和冰雪艺术。</p>
          </div>

          <div className="travel-item" onClick={() => setSelectedImage(changbaishan)}>
            <h3>长白山</h3>
            <p>天池的深邃神秘，瀑布的气势磅礴，温泉的温暖治愈。在这座火山与冰雪的天堂，感受大自然的鬼斧神工体验东北原始森林的神秘。</p>
          </div>

          <div className="travel-item" onClick={() => setSelectedImage(qindao)}>
            <h3>青岛</h3>
            <p>的海轻抚，八关的建，酒博物馆金色回。漫步在海边，品尝着新鲜的海鲜，欣赏着这座充满德国风情的海滨城市。</p>
          </div>

          <div className="travel-item" onClick={() => setSelectedImage(qinghuangdao)}>
            <h3>秦皇岛</h3>
            <p>在万里长的起点北戴河，听着渤海湾的浪涛。漫步在白色的沙滩上，日出东方，霞满。这里有最美的海岸线，也有最动人的历史故事。</p>
          </div>

          <div className="travel-item" onClick={() => setSelectedImage(tianjin)}>
            <h3>天津</h3>
            <p>五大洋楼群诉着百年历史，意式风情区的地域情调。古文化街的津味小吃，海河两岸的璨夜景。在这座中西合璧的城市里，感受着独特的海派文化。</p>
          </div>

          <div className="travel-item" onClick={() => setSelectedImage(taian)}>
            <h3>泰安</h3>
            <p>泰山巍峨雄伟，云海日出壮观无比。上南天门，俯瞰众渺小。岱庙的古老建，诉着千历史。这里不仅是五岳之首，更是中华文化的精神象征。</p>
          </div>
        </div>
        {selectedImage && (
          <ImageModal 
            image={selectedImage}
            onClose={() => setSelectedImage(null)}
          />
        )}
      </section>

      <section className="slider-section">
        <div className="circle-decoration circle-left"></div>
        <div className="circle-decoration circle-right"></div>
        <div className="number-decoration number-top">01</div>
        <div className="number-decoration number-bottom">21</div>
        <div className="side-text side-text-left">
          TRAVEL MEMORIES · 旅行记忆
        </div>
        <div className="side-text side-text-right">
          PHOTO COLLECTION · 影像集
        </div>
        <div className="year-display">
          2022 - 2024
        </div>
        <div className="container">
          <div className="slider">
            {displayedCards.map((img, index) => (
              <div className="card" key={index}>
                <img src={img} alt="" />
              </div>
            ))}
          </div>
        </div>
      </section>
    </div>
  );
}; 