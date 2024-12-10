import { jsx as _jsx, jsxs as _jsxs } from "react/jsx-runtime";
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
let recentlyUsedImages = [];
// 修改节流函数，使用闭包来保存状态
function throttle(func, limit) {
    let inThrottle;
    let lastResult;
    return function (...args) {
        if (!inThrottle) {
            lastResult = func.apply(this, args);
            inThrottle = true;
            setTimeout(() => {
                inThrottle = false;
            }, limit);
        }
        return lastResult;
    };
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
    const layersRef = useRef(null);
    const [selectedImage, setSelectedImage] = useState(null);
    const [displayedCards, setDisplayedCards] = useState(() => {
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
        let rafId;
        let isAnimating = false;
        let autoPlayInterval;
        function raf(time) {
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
                const element = layersRef.current.querySelector(`[data-parallax-layer="${layerObj.layer}"]`);
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
            if (isAnimating)
                return;
            isAnimating = true;
            const slider = document.querySelector(".slider");
            if (!slider)
                return;
            const cards = Array.from(slider.querySelectorAll(".card"));
            const lastCard = cards[cards.length - 1];
            if (lastCard) {
                const currentDisplayed = new Set(displayedCards);
                const usedImages = new Set(recentlyUsedImages);
                const availableImages = allImages.filter(img => !currentDisplayed.has(img) && !usedImages.has(img));
                let newImage;
                if (availableImages.length < 5) {
                    recentlyUsedImages = [];
                    const newAvailableImages = allImages.filter(img => !currentDisplayed.has(img));
                    const randomIndex = Math.floor(Math.random() * newAvailableImages.length);
                    newImage = newAvailableImages[randomIndex];
                }
                else {
                    const randomIndex = Math.floor(Math.random() * availableImages.length);
                    newImage = availableImages[randomIndex];
                }
                recentlyUsedImages.push(newImage);
                // 更新状态，新图片添加到开头
                const newState = [newImage, ...displayedCards.slice(0, -1)];
                setDisplayedCards(newState);
                // 先创建新的卡片元素
                const newCard = lastCard.cloneNode(true);
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
    return (_jsxs("div", { className: "parallax", children: [_jsx("section", { className: "parallax__header", children: _jsxs("div", { className: "parallax__visuals", children: [_jsx("div", { className: "parallax__black-line-overflow" }), _jsxs("div", { ref: layersRef, "data-parallax-layers": true, className: "parallax__layers", children: [_jsx("img", { src: layer3, loading: "eager", width: "800", "data-parallax-layer": "1", alt: "", className: "parallax__layer-img" }), _jsx("img", { src: layer2, loading: "eager", width: "800", "data-parallax-layer": "2", alt: "", className: "parallax__layer-img" }), _jsx("div", { "data-parallax-layer": "3", className: "parallax__layer-title", children: _jsx("h2", { className: "parallax__title", children: "\u65C5\u884C\u6545\u4E8B" }) }), _jsx("img", { src: layer1, loading: "eager", width: "800", "data-parallax-layer": "4", alt: "", className: "parallax__layer-img" })] }), _jsx("div", { className: "parallax__fade" })] }) }), _jsxs("section", { className: "parallax__content", children: [_jsxs("div", { className: "travel-grid", children: [_jsxs("div", { className: "travel-item", onClick: () => setSelectedImage(xizhang), children: [_jsx("h3", { children: "\u897F\u85CF" }), _jsx("p", { children: "\u5728\u6D77\u62D44000\u7C73\u7684\u9AD8\u539F\u4E0A\uFF0C\u611F\u53D7\u7740\u6700\u63A5\u8FD1\u5929\u7A7A\u7684\u4FE1\u4EF0\u3002\u5E03\u8FBE\u62C9\u5BAB\u7684\u5E84\u4E25\u8083\u7A46\uFF0C\u5927\u662D\u5BFA\u7684\u8654\u8BDA\u9999\u706B\uFF0C\u4EE5\u53CA\u7EB3\u6728\u9519\u5723\u6E56\u7684\u78A7\u84DD\u6E56\u6C34\uFF0C\u90FD\u8BA9\u4EBA\u5185\u5FC3\u65E0\u6BD4\u5E73\u9759\u3002\u9AD8\u539F\u7684\u661F\u7A7A\u7480\u74A8\u5F97\u8BA9\u4EBA\u5C4F\u606F\u3002" })] }), _jsxs("div", { className: "travel-item", onClick: () => setSelectedImage(shichuan), children: [_jsx("h3", { children: "\u56DB\u5DDD" }), _jsx("p", { children: "\u5728\u6210\u90FD\u7684\u5BBD\u7A84\u5DF7\u5B50\uFF0C\u611F\u53D7\u60A0\u95F2\u7684\u56DB\u5DDD\u6587\u5316\u3002\u7A3B\u57CE\u4E01\u7684\u96EA\u5C71\u3001\u8349\u4E0E\u6E56\u6CCA\u6784\u6210\u4E86\u4EBA\u95F4\u6700\u540E\u7684\u9999\u683C\u91CC\u62C9\u3002\u4E50\u5C71\u5927\u4F5B\u5DCD\u5CE8\u5E84\u4E25\uFF0C\u90FD\u6C5F\u5830\u5343\u5E74\u667A\u6167\uFF0C\u8BA9\u4EBA\u4E0D\u7981\u611F\u53F9\u53E4\u4EBA\u7684\u5320\u5FC3\u3002" })] }), _jsxs("div", { className: "travel-item", onClick: () => setSelectedImage(chongqing), children: [_jsx("h3", { children: "\u91CD\u5E86" }), _jsx("p", { children: "\u591C\u5E55\u964D\u4E34\uFF0C\u8FD9\u5EA7\u4E0D\u591C\u57CE\u5F00\u59CB\u7EFD\u653E\u5149\u3002\u6D2A\u5D16\u6D1E\u5C42\u5C42\u53E0\u53E0\u7684\u706F\u5149\u5012\u6620\u5728\u6C5F\u9762\uFF0C\u4E24\u6C5F\u4EA4\u6C47\u5904\u7684\u7480\u74A8\u591C\u666F\u4EE4\u4EBA\u6C89\u9189\u3002\u5B50\u575D\u8F7B\u8F68\u7A7F\u697C\u800C\u8FC7\uFF0C\u89E3\u653E\u7891\u7684\u7E41\u534E\u591C\u8272\uFF0C\u6784\u6210\u4E86\u8FD9\u5EA7\u7ACB\u4F53\u57CE\u5E02\u6700\u8FF7\u4EBA\u7684\u753B\u5377\u3002" })] }), _jsxs("div", { className: "travel-item", onClick: () => setSelectedImage(haerbing), children: [_jsx("h3", { children: "\u54C8\u5C14\u6EE8" }), _jsx("p", { children: "\u51B0\u96EA\u4E16\u754C\u7684\u6676\u83B9\u5254\u900F\uFF0C\u4E2D\u592E\u5927\u8857\u7684\u6B27\u5F0F\u5EFA\u7B51\uFF0C\u677E\u82B1\u6C5F\u7684\u51B0\u96EA\u5947\u7F18\u3002\u5728\u96F6\u4E0B20\u5EA6\u7684\u5BD2\u51AC\u611F\u53D7\u7740\u8FD9\u5EA7\u57CE\u5E02\u72EC\u7279\u7684\u4FC4\u7F57\u65AF\u98CE\u60C5\u548C\u51B0\u96EA\u827A\u672F\u3002" })] }), _jsxs("div", { className: "travel-item", onClick: () => setSelectedImage(changbaishan), children: [_jsx("h3", { children: "\u957F\u767D\u5C71" }), _jsx("p", { children: "\u5929\u6C60\u7684\u6DF1\u9083\u795E\u79D8\uFF0C\u7011\u5E03\u7684\u6C14\u52BF\u78C5\u7934\uFF0C\u6E29\u6CC9\u7684\u6E29\u6696\u6CBB\u6108\u3002\u5728\u8FD9\u5EA7\u706B\u5C71\u4E0E\u51B0\u96EA\u7684\u5929\u5802\uFF0C\u611F\u53D7\u5927\u81EA\u7136\u7684\u9B3C\u65A7\u795E\u5DE5\u4F53\u9A8C\u4E1C\u5317\u539F\u59CB\u68EE\u6797\u7684\u795E\u79D8\u3002" })] }), _jsxs("div", { className: "travel-item", onClick: () => setSelectedImage(qindao), children: [_jsx("h3", { children: "\u9752\u5C9B" }), _jsx("p", { children: "\u7684\u6D77\u8F7B\u629A\uFF0C\u516B\u5173\u7684\u5EFA\uFF0C\u9152\u535A\u7269\u9986\u91D1\u8272\u56DE\u3002\u6F2B\u6B65\u5728\u6D77\u8FB9\uFF0C\u54C1\u5C1D\u7740\u65B0\u9C9C\u7684\u6D77\u9C9C\uFF0C\u6B23\u8D4F\u7740\u8FD9\u5EA7\u5145\u6EE1\u5FB7\u56FD\u98CE\u60C5\u7684\u6D77\u6EE8\u57CE\u5E02\u3002" })] }), _jsxs("div", { className: "travel-item", onClick: () => setSelectedImage(qinghuangdao), children: [_jsx("h3", { children: "\u79E6\u7687\u5C9B" }), _jsx("p", { children: "\u5728\u4E07\u91CC\u957F\u7684\u8D77\u70B9\u5317\u6234\u6CB3\uFF0C\u542C\u7740\u6E24\u6D77\u6E7E\u7684\u6D6A\u6D9B\u3002\u6F2B\u6B65\u5728\u767D\u8272\u7684\u6C99\u6EE9\u4E0A\uFF0C\u65E5\u51FA\u4E1C\u65B9\uFF0C\u971E\u6EE1\u3002\u8FD9\u91CC\u6709\u6700\u7F8E\u7684\u6D77\u5CB8\u7EBF\uFF0C\u4E5F\u6709\u6700\u52A8\u4EBA\u7684\u5386\u53F2\u6545\u4E8B\u3002" })] }), _jsxs("div", { className: "travel-item", onClick: () => setSelectedImage(tianjin), children: [_jsx("h3", { children: "\u5929\u6D25" }), _jsx("p", { children: "\u4E94\u5927\u6D0B\u697C\u7FA4\u8BC9\u7740\u767E\u5E74\u5386\u53F2\uFF0C\u610F\u5F0F\u98CE\u60C5\u533A\u7684\u5730\u57DF\u60C5\u8C03\u3002\u53E4\u6587\u5316\u8857\u7684\u6D25\u5473\u5C0F\u5403\uFF0C\u6D77\u6CB3\u4E24\u5CB8\u7684\u74A8\u591C\u666F\u3002\u5728\u8FD9\u5EA7\u4E2D\u897F\u5408\u74A7\u7684\u57CE\u5E02\u91CC\uFF0C\u611F\u53D7\u7740\u72EC\u7279\u7684\u6D77\u6D3E\u6587\u5316\u3002" })] }), _jsxs("div", { className: "travel-item", onClick: () => setSelectedImage(taian), children: [_jsx("h3", { children: "\u6CF0\u5B89" }), _jsx("p", { children: "\u6CF0\u5C71\u5DCD\u5CE8\u96C4\u4F1F\uFF0C\u4E91\u6D77\u65E5\u51FA\u58EE\u89C2\u65E0\u6BD4\u3002\u4E0A\u5357\u5929\u95E8\uFF0C\u4FEF\u77B0\u4F17\u6E3A\u5C0F\u3002\u5CB1\u5E99\u7684\u53E4\u8001\u5EFA\uFF0C\u8BC9\u7740\u5343\u5386\u53F2\u3002\u8FD9\u91CC\u4E0D\u4EC5\u662F\u4E94\u5CB3\u4E4B\u9996\uFF0C\u66F4\u662F\u4E2D\u534E\u6587\u5316\u7684\u7CBE\u795E\u8C61\u5F81\u3002" })] })] }), selectedImage && (_jsx(ImageModal, { image: selectedImage, onClose: () => setSelectedImage(null) }))] }), _jsxs("section", { className: "slider-section", children: [_jsx("div", { className: "circle-decoration circle-left" }), _jsx("div", { className: "circle-decoration circle-right" }), _jsx("div", { className: "number-decoration number-top", children: "01" }), _jsx("div", { className: "number-decoration number-bottom", children: "21" }), _jsx("div", { className: "side-text side-text-left", children: "TRAVEL MEMORIES \u00B7 \u65C5\u884C\u8BB0\u5FC6" }), _jsx("div", { className: "side-text side-text-right", children: "PHOTO COLLECTION \u00B7 \u5F71\u50CF\u96C6" }), _jsx("div", { className: "year-display", children: "2022 - 2024" }), _jsx("div", { className: "container", children: _jsx("div", { className: "slider", children: displayedCards.map((img, index) => (_jsx("div", { className: "card", children: _jsx("img", { src: img, alt: "" }) }, index))) }) })] })] }));
};
