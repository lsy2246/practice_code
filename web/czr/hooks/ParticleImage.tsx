import { useEffect, useRef, useState, useCallback } from 'react';
import * as THREE from 'three';
import { gsap } from 'gsap';
import throttle from 'lodash/throttle';

interface HSL {
  h: number;
  s: number;
  l: number;
}

interface Particle {
  x: number;
  y: number;
  z: number;
  originalX: number;
  originalY: number;
  originalColor: THREE.Color;
  delay: number;
}

const createErrorParticles = (width: number, height: number) => {
  const particles: Particle[] = [];
  const positionArray: number[] = [];
  const colorArray: number[] = [];
  
  const errorColor = new THREE.Color(0.8, 0, 0);
  const size = Math.min(width, height);
  const scaleFactor = size * 0.3;
  const particlesPerLine = 50;

  // X 形状的两条线
  const lines = [
    // 左上到右下的线
    { start: [-1, 1], end: [1, -1] },
    // 右上到左下的线
    { start: [1, 1], end: [-1, -1] }
  ];

  lines.forEach(line => {
    for (let i = 0; i < particlesPerLine; i++) {
      const t = i / (particlesPerLine - 1);
      const x = line.start[0] + (line.end[0] - line.start[0]) * t;
      const y = line.start[1] + (line.end[1] - line.start[1]) * t;

      // 添加一些随机偏移
      const randomOffset = 0.1;
      const randomX = x + (Math.random() - 0.5) * randomOffset;
      const randomY = y + (Math.random() - 0.5) * randomOffset;

      const scaledX = randomX * scaleFactor;
      const scaledY = randomY * scaleFactor;

      particles.push({
        x: scaledX,
        y: scaledY,
        z: 0,
        originalX: scaledX,
        originalY: scaledY,
        originalColor: errorColor,
        delay: 0
      });

      // 修改初始位置生成方式
      const angle = Math.random() * Math.PI * 2;
      const distance = size * 2;
      positionArray.push(
        Math.cos(angle) * distance,
        Math.sin(angle) * distance,
        0
      );

      // 初始颜色设置为最终颜色的一半亮度
      colorArray.push(errorColor.r * 0.5, errorColor.g * 0.5, errorColor.b * 0.5);
    }
  });

  const particleSize = Math.max(1.2, (size / 200) * 1.2);
  
  return { particles, positionArray, colorArray, particleSize };
};

// 修改 createSmileParticles 函数
const createSmileParticles = (width: number, height: number) => {
  const particles: Particle[] = [];
  const positionArray: number[] = [];
  const colorArray: number[] = [];
  
  const size = Math.min(width, height);
  const scale = size / 200;
  const radius = size * 0.35;
  const particleSize = Math.max(1.2, scale * 1.2);
  const particleColor = new THREE.Color(0.8, 0.6, 0);

  // 预先计算所有需要的粒子位置
  const allPoints: { x: number; y: number }[] = [];

  // 计算脸部轮廓的点
  const outlinePoints = Math.floor(60 * scale);
  for (let i = 0; i < outlinePoints; i++) {
    const angle = (i / outlinePoints) * Math.PI * 2;
    allPoints.push({
      x: Math.cos(angle) * radius,
      y: Math.sin(angle) * radius
    });
  }

  // 修改眼睛的生成方式
  const eyeOffset = radius * 0.3;
  const eyeY = radius * 0.15;
  const eyeSize = radius * 0.1; // 稍微减小眼睛尺寸
  const eyePoints = Math.floor(20 * scale);

  [-1, 1].forEach(side => {
    // 使用同心圆的方式生成眼睛
    const eyeCenterX = side * eyeOffset;
    const rings = 3; // 同心圆的数量
    
    for (let ring = 0; ring < rings; ring++) {
      const ringRadius = eyeSize * (1 - ring / rings); // 从外到内递减半径
      const pointsInRing = Math.floor(eyePoints / rings);
      
      for (let i = 0; i < pointsInRing; i++) {
        const angle = (i / pointsInRing) * Math.PI * 2;
        allPoints.push({
          x: eyeCenterX + Math.cos(angle) * ringRadius,
          y: eyeY + Math.sin(angle) * ringRadius
        });
      }
    }
    
    // 添加中心点
    allPoints.push({
      x: eyeCenterX,
      y: eyeY
    });
  });

  // 计算嘴巴的点
  const smileWidth = radius * 0.6;
  const smileY = -radius * 0.35;
  const smilePoints = Math.floor(25 * scale);

  for (let i = 0; i < smilePoints; i++) {
    const t = i / (smilePoints - 1);
    const x = (t * 2 - 1) * smileWidth;
    const y = smileY + Math.pow(x / smileWidth, 2) * radius * 0.2;
    allPoints.push({ x, y });
  }

  // 为所有点创建粒子
  allPoints.forEach(point => {
    particles.push({
      x: point.x,
      y: point.y,
      z: 0,
      originalX: point.x,
      originalY: point.y,
      originalColor: particleColor,
      delay: 0
    });

    // 生成初始位置（从外围圆形区域开始）
    const initAngle = Math.random() * Math.PI * 2;
    const distance = size * 2;
    positionArray.push(
      Math.cos(initAngle) * distance,
      Math.sin(initAngle) * distance,
      0
    );
    
    // 初始颜色设置为最终颜色的一半亮度
    colorArray.push(
      particleColor.r * 0.5,
      particleColor.g * 0.5,
      particleColor.b * 0.5
    );
  });

  return { particles, positionArray, colorArray, particleSize };
};

// 在文件开头添加新的 helper 函数
const easeOutCubic = (t: number) => {
  return 1 - Math.pow(1 - t, 3);
};

const customEase = (t: number) => {
  return t < 0.5
    ? 4 * t * t * t
    : 1 - Math.pow(-2 * t + 2, 3) / 2;
};

// 在文件开头添加新的 LoaderStatus 接口
interface LoaderStatus {
  isLoading: boolean;
  hasError: boolean;
  timeoutError: boolean;
  animationPhase: 'assembling' | 'image' | 'dissolving' | 'transitioning';
}

// 修改 ParticleImage 组件的 props 接口
interface ParticleImageProps {
  src?: string;
  status?: LoaderStatus;
  onLoad?: () => void;
  onAnimationComplete?: () => void;
  transitionType?: 'in' | 'out' | 'none';
  previousParticles?: Particle[];
  onParticlesCreated?: (particles: Particle[]) => void;
  onAnimationPhaseChange?: (phase: 'assembling' | 'image' | 'dissolving' | 'transitioning') => void;
}

// 修改 BG_CONFIG
const BG_CONFIG = {
  colors: {
    from: 'rgb(10,37,77)',
    via: 'rgb(8,27,57)', 
    to: 'rgb(2,8,23)'
  },
  className: 'bg-gradient-to-br from-[rgb(248,250,252)] via-[rgb(241,245,249)] to-[rgb(236,241,247)] dark:from-[rgb(10,37,77)] dark:via-[rgb(8,27,57)] dark:to-[rgb(2,8,23)]',
  size: {
    container: ''
  }
};

// 修改图像采样函数
const createParticlesFromImage = (imageData: ImageData, width: number, height: number) => {
  const particles: Particle[] = [];
  const positionArray: number[] = [];
  const colorArray: number[] = [];
  
  // 根据容器尺寸计算缩放因子
  const aspectRatio = width / height;
  const scaleFactor = width / 2;  // 使用容器宽度的一半作为基准
  
  // 固定粒子数量以保持一致的视觉效果
  const particlesPerSide = Math.floor(Math.min(150, Math.max(80, Math.min(width, height) / 4))); 
  const stepX = width / particlesPerSide;
  const stepY = height / particlesPerSide;
  
  for (let y = 0; y < height; y += stepY) {
    for (let x = 0; x < width; x += stepX) {
      const pixelX = Math.floor(x);
      const pixelY = Math.floor(y);
      const i = (pixelY * width + pixelX) * 4;
      
      const r = imageData.data[i] / 255;
      const g = imageData.data[i + 1] / 255;
      const b = imageData.data[i + 2] / 255;
      
      // 计算亮度并设置最小值
      const brightness = Math.max(0.1, (r + g + b) / 3);
      
      // 将坐标映射到容器范围
      const px = ((x / width) * 2 - 1) * scaleFactor;
      const py = ((1 - y / height) * 2 - 1) * (scaleFactor / aspectRatio);
      
      // 创建粒子
      const finalColor = new THREE.Color(
        Math.max(0.1, r),
        Math.max(0.1, g),
        Math.max(0.1, b)
      );

      particles.push({
        x: px,
        y: py,
        z: 0,
        originalX: px,
        originalY: py,
        originalColor: finalColor,
        delay: Math.random() * 0.3
      });

      // 设置初始位置
      const angle = Math.random() * Math.PI * 2;
      const distance = Math.max(width, height);
      positionArray.push(
        Math.cos(angle) * distance,
        Math.sin(angle) * distance,
        0
      );

      // 设置初始颜色
      colorArray.push(
        finalColor.r * 0.3,
        finalColor.g * 0.3,
        finalColor.b * 0.3
      );
    }
  }

  // 调整粒子大小
  const particleSize = Math.max(2, Math.min(width, height) / 150);
  
  return { particles, positionArray, colorArray, particleSize };
};

// 优化动画效果
const animateParticles = (
  particles: Particle[],
  geometry: THREE.BufferGeometry,
  onComplete?: () => void
) => {
  const positionAttribute = geometry.attributes.position;
  const colorAttribute = geometry.attributes.color;
  
  particles.forEach((particle, i) => {
    const i3 = i * 3;
    
    // 位置动画
    gsap.to(positionAttribute.array, {
      duration: 1 + Math.random() * 0.5,
      delay: particle.delay,
      [i3]: particle.originalX,
      [i3 + 1]: particle.originalY,
      [i3 + 2]: 0,
      ease: "power2.out",
      onUpdate: () => void (positionAttribute.needsUpdate = true)
    });

    // 颜色动画
    gsap.to(colorAttribute.array, {
      duration: 0.8,
      delay: particle.delay,
      [i3]: particle.originalColor.r,
      [i3 + 1]: particle.originalColor.g,
      [i3 + 2]: particle.originalColor.b,
      ease: "power2.inOut",
      onUpdate: () => {
        colorAttribute.needsUpdate = true;
        return;
      },
      onComplete: i === particles.length - 1 ? onComplete : undefined
    });
  });
};

export const ParticleImage = ({ 
  src, 
  status,
  onLoad,
  onAnimationComplete,
  transitionType = 'in',
  previousParticles,
  onParticlesCreated,
  onAnimationPhaseChange
}: ParticleImageProps) => {
  const containerRef = useRef<HTMLDivElement>(null);
  const sceneRef = useRef<THREE.Scene>();
  const cameraRef = useRef<THREE.OrthographicCamera>();
  const rendererRef = useRef<THREE.WebGLRenderer>();
  const animationFrameRef = useRef<number>();
  const geometryRef = useRef<THREE.BufferGeometry>();
  const materialRef = useRef<THREE.PointsMaterial>();
  const pointsRef = useRef<THREE.Points>();

  // 清理函数
  const cleanup = useCallback(() => {
    if (animationFrameRef.current) {
      cancelAnimationFrame(animationFrameRef.current);
    }

    // 清理 Three.js 资源
    if (geometryRef.current) {
      geometryRef.current.dispose();
    }

    if (materialRef.current) {
      materialRef.current.dispose();
    }

    if (pointsRef.current) {
      if (pointsRef.current.geometry) {
        pointsRef.current.geometry.dispose();
      }
      if (pointsRef.current.material instanceof THREE.Material) {
        pointsRef.current.material.dispose();
      }
      sceneRef.current?.remove(pointsRef.current);
    }

    if (rendererRef.current) {
      rendererRef.current.dispose();
      if (containerRef.current?.contains(rendererRef.current.domElement)) {
        containerRef.current.removeChild(rendererRef.current.domElement);
      }
    }

    // 清理 GSAP 动画
    gsap.killTweensOf('*');
  }, []);

  useEffect(() => {
    if (!containerRef.current || !src) return;

    const width = containerRef.current.offsetWidth;
    const height = containerRef.current.offsetHeight;

    // 建错误动画函数
    const showErrorAnimation = () => {
      if (!sceneRef.current) return;
      
      const { particles, positionArray, colorArray, particleSize } = createErrorParticles(width, height);
      // ... 其余错误动画代码 ...
    };

    const timeoutId = setTimeout(() => showErrorAnimation(), 5000);

    // 初始化场景
    const scene = new THREE.Scene();
    sceneRef.current = scene;

    // 调整相机视角
    const camera = new THREE.OrthographicCamera(
      width / -2,
      width / 2,
      height / 2,
      height / -2,
      1,
      1000
    );
    camera.position.z = 500;
    cameraRef.current = camera;

    const renderer = new THREE.WebGLRenderer({ 
      alpha: true,
      antialias: true 
    });
    renderer.setSize(width, height);
    rendererRef.current = renderer;
    containerRef.current.appendChild(renderer.domElement);

    // 加载图片
    const img = new Image();
    img.crossOrigin = 'anonymous';
    
    img.onload = () => {
      clearTimeout(timeoutId);
      
      const canvas = document.createElement('canvas');
      const ctx = canvas.getContext('2d');
      
      if (ctx) {
        // 计算目标尺寸和裁剪区域
        const targetAspect = width / height;
        const imgAspect = img.width / img.height;
        
        let sourceWidth = img.width;
        let sourceHeight = img.height;
        let sourceX = 0;
        let sourceY = 0;
        
        // 裁剪源图片，确保比例匹配目标容器
        if (imgAspect > targetAspect) {
          sourceWidth = img.height * targetAspect;
          sourceX = (img.width - sourceWidth) / 2;
        } else {
          sourceHeight = img.width / targetAspect;
          sourceY = (img.height - sourceHeight) / 2;
        }

        canvas.width = width;
        canvas.height = height;
        
        // 清除画布
        ctx.clearRect(0, 0, width, height);
        
        // 绘制图像
        ctx.drawImage(
          img,
          sourceX, sourceY, sourceWidth, sourceHeight,
          0, 0, width, height
        );
        
        const imageData = ctx.getImageData(0, 0, width, height);
        const { particles, positionArray, colorArray, particleSize } = createParticlesFromImage(imageData, width, height);
        
        // 通知父组件新的粒子已创建
        onParticlesCreated?.(particles);
        
        // 创建粒子系统
        const geometry = new THREE.BufferGeometry();
        geometryRef.current = geometry;

        const material = new THREE.PointsMaterial({
          size: particleSize,
          vertexColors: true,
          transparent: true,
          opacity: 1,
          sizeAttenuation: true,
          blending: THREE.AdditiveBlending,
          depthWrite: false,
          depthTest: false
        });
        materialRef.current = material;

        geometry.setAttribute('position', new THREE.Float32BufferAttribute(positionArray, 3));
        geometry.setAttribute('color', new THREE.Float32BufferAttribute(colorArray, 3));

        const points = new THREE.Points(geometry, material);
        pointsRef.current = points;
        scene.add(points);

        // 动画分
        const timeline = gsap.timeline();

        const positionAttribute = geometry.attributes.position;
        const colorAttribute = geometry.attributes.color;

        // 立即执动画
        if (transitionType === 'in') {
          // 设置初始位置和颜色
          particles.forEach((particle, i) => {
            const i3 = i * 3;
            // 设置随机初始位置
            positionAttribute.array[i3] = (Math.random() - 0.5) * width * 2;
            positionAttribute.array[i3 + 1] = (Math.random() - 0.5) * height * 2;
            positionAttribute.array[i3 + 2] = Math.random() * 100;
            
            // 设置初始颜色
            colorAttribute.array[i3] = particle.originalColor.r * 0.2;
            colorAttribute.array[i3 + 1] = particle.originalColor.g * 0.2;
            colorAttribute.array[i3 + 2] = particle.originalColor.b * 0.2;
          });
          
          positionAttribute.needsUpdate = true;
          colorAttribute.needsUpdate = true;

          // 创建动画
          particles.forEach((particle, i) => {
            const i3 = i * 3;
            
            // 位置动画
            gsap.to(positionAttribute.array, {
              duration: 2,
              delay: particle.delay,
              [i3]: particle.originalX,
              [i3 + 1]: particle.originalY,
              [i3 + 2]: 0,
              ease: "power2.inOut",
              onUpdate: () => { positionAttribute.needsUpdate = true; }
            });

            // 颜色动画
            gsap.to(colorAttribute.array, {
              duration: 1.8,
              delay: particle.delay + 0.2,
              [i3]: particle.originalColor.r,
              [i3 + 1]: particle.originalColor.g,
              [i3 + 2]: particle.originalColor.b,
              ease: "power2.inOut",
              onUpdate: () => { colorAttribute.needsUpdate = true; }
            });
          });
        } else if (transitionType === 'out') {
          particles.forEach((particle, i) => {
            const i3 = i * 3;
            gsap.to(colorAttribute.array, {
              duration: 1,
              [i3]: particle.originalColor.r * 0.2,
              [i3 + 1]: particle.originalColor.g * 0.2,
              [i3 + 2]: particle.originalColor.b * 0.2,
              ease: "power2.in",
              onUpdate: () => {
                colorAttribute.needsUpdate = true;
              }
            });
          });
        }

        // 画循环
        const animate = () => {
          animationFrameRef.current = requestAnimationFrame(animate);
          renderer.render(scene, camera);
        };
        animate();

        onLoad?.();
      }
    };

    img.src = src;

    return () => {
      clearTimeout(timeoutId);
      cleanup();
    };
  }, [src, cleanup, onLoad, onAnimationComplete, transitionType, previousParticles, onParticlesCreated]);

  return <div ref={containerRef} className="w-full h-full" />;
};

// 修改 ImageLoader 组件的 props 接口
interface ImageLoaderProps {
  src?: string;
  alt: string;
  className?: string;
  containerClassName?: string;  // 新增容器类名属性
}

// 修改 ImageLoader 组件
export const ImageLoader = ({ src, alt, className = '', containerClassName = '' }: ImageLoaderProps) => {
  const [status, setStatus] = useState<LoaderStatus>({
    isLoading: true,
    hasError: false,
    timeoutError: false,
    animationPhase: 'assembling'
  });
  const [showImage, setShowImage] = useState(false);
  const timeoutRef = useRef<NodeJS.Timeout>();
  const loadingRef = useRef(false);
  const imageRef = useRef<HTMLImageElement | null>(null);
  const [currentParticles, setCurrentParticles] = useState<Particle[]>([]);

  // 动画循环
  const startAnimationCycle = useCallback(async () => {
    while (true) {
      // 1. 粒子组合成图像
      setStatus(prev => ({ ...prev, animationPhase: 'assembling' }));
      setShowImage(false);
      await new Promise(resolve => setTimeout(resolve, 2500));

      // 2. 显示实际图片
      setShowImage(true);
      await new Promise(resolve => setTimeout(resolve, 3000));

      // 3. 隐藏图片，显示粒子
      setShowImage(false);
      setStatus(prev => ({ ...prev, animationPhase: 'dissolving' }));
      await new Promise(resolve => setTimeout(resolve, 3000));

      // 4. 粒子过渡状态
      setStatus(prev => ({ ...prev, animationPhase: 'transitioning' }));
      await new Promise(resolve => setTimeout(resolve, 1500));
    }
  }, []);

  // 处理图片预加载
  const preloadImage = useCallback(() => {
    if (!src || loadingRef.current) return;
    
    loadingRef.current = true;
    const img = new Image();
    img.crossOrigin = 'anonymous';

    img.onload = () => {
      imageRef.current = img;
      setStatus(prev => ({
        ...prev,
        isLoading: false,
        hasError: false,
        timeoutError: false
      }));
      startAnimationCycle();
    };

    img.onerror = () => {
      setStatus(prev => ({
        ...prev,
        isLoading: false,
        hasError: true,
        timeoutError: false
      }));
    };

    img.src = src;
  }, [src, startAnimationCycle]);

  useEffect(() => {
    preloadImage();
    return () => {
      loadingRef.current = false;
    };
  }, [preloadImage]);

  return (
    <div className={`relative shrink-0 overflow-hidden ${containerClassName}`}>
      <div className={`absolute inset-0 ${BG_CONFIG.className} rounded-lg overflow-hidden`}>
        <ParticleImage 
          src={src} 
          status={status}
          onParticlesCreated={setCurrentParticles}
          onAnimationPhaseChange={(phase) => {
            setStatus(prev => ({ ...prev, animationPhase: phase }));
          }}
        />
      </div>
      {!status.hasError && !status.timeoutError && imageRef.current && (
        <div className="absolute inset-0 rounded-lg overflow-hidden">
          <img 
            src={imageRef.current.src}
            alt={alt}
            className={`
              w-full h-full object-cover
              transition-opacity duration-1000
              ${className}
              ${showImage ? 'opacity-100' : 'opacity-0'}
            `}
            style={{ 
              visibility: showImage ? 'visible' : 'hidden',
              objectFit: 'cover',
              objectPosition: 'center'
            }}
          />
        </div>
      )}
    </div>
  );
};