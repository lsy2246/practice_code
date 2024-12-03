import React, { useState } from 'react';
import './App.css';

const App: React.FC = () => {
  const [text, setText] = useState('Hello World');
  const [fontSize, setFontSize] = useState(100);
  const [fontFile, setFontFile] = useState<File | null>(null);
  const [svg, setSvg] = useState<string | null>(null);
  const [isLoading, setIsLoading] = useState(false);

  const handleFileChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    if (e.target.files && e.target.files[0]) {
      setFontFile(e.target.files[0]);
    }
  };

  const generateSvg = async () => {
    if (!fontFile) return;

    setIsLoading(true);
    try {
      const wasm = await import('../pkg/font_to_svg');
      await wasm.default();
      wasm.init_panic_hook();

      const arrayBuffer = await fontFile.arrayBuffer();
      const fontHandler = new wasm.FontHandler(new Uint8Array(arrayBuffer));
      const svgString = fontHandler.generate_svg(text, fontSize);
      
      setSvg(svgString);
    } catch (error) {
      console.error('Error generating SVG:', error);
    } finally {
      setIsLoading(false);
    }
  };

  const handleConvert = () => {
    if (fontFile) {
      generateSvg();
    }
  };

  const handleDownload = () => {
    if (svg) {
      const blob = new Blob([svg], { type: 'image/svg+xml' });
      const url = URL.createObjectURL(blob);
      const a = document.createElement('a');
      a.href = url;
      a.download = `${text}.svg`;
      document.body.appendChild(a);
      a.click();
      document.body.removeChild(a);
      URL.revokeObjectURL(url);
    }
  };

  const handleDownloadCss = () => {
    const animationCss = `
.animated-text {
  max-width: 100%;
  height: auto;
}

.animated-text path {
  fill: transparent;
  stroke: currentColor;
  stroke-width: 2;
  stroke-dashoffset: var(--path-length);
  stroke-dasharray: var(--path-length) var(--path-length);
  animation: logo-anim 15s cubic-bezier(0.4, 0, 0.2, 1) infinite;
  transform-origin: center;
  stroke-linecap: round;
  stroke-linejoin: round;
}

@keyframes logo-anim {
  0% {
    stroke-dashoffset: var(--path-length);
    stroke-dasharray: var(--path-length) var(--path-length);
    opacity: 0;
    fill: transparent;
  }

  5% {
    opacity: 1;
    stroke-dashoffset: var(--path-length);
    stroke-dasharray: var(--path-length) var(--path-length);
  }

  /* 慢速绘画过程 */
  50% {
    stroke-dashoffset: 0;
    stroke-dasharray: var(--path-length) var(--path-length);
    fill: transparent;
  }

  /* 慢慢填充效果 */
  60% {
    stroke-dashoffset: 0;
    stroke-dasharray: var(--path-length) var(--path-length);
    fill: currentColor;
    opacity: 1;
  }

  /* 保持填充状态 */
  75% {
    stroke-dashoffset: 0;
    stroke-dasharray: var(--path-length) var(--path-length);
    fill: currentColor;
    opacity: 1;
  }

  /* 变回线条 */
  85% {
    stroke-dashoffset: 0;
    stroke-dasharray: var(--path-length) var(--path-length);
    fill: transparent;
    opacity: 1;
  }

  /* 线条消失 */
  95% {
    stroke-dashoffset: var(--path-length);
    stroke-dasharray: var(--path-length) var(--path-length);
    fill: transparent;
    opacity: 1;
  }

  100% {
    stroke-dashoffset: var(--path-length);
    stroke-dasharray: var(--path-length) var(--path-length);
    fill: transparent;
    opacity: 0;
  }
}`;

    const blob = new Blob([animationCss], { type: 'text/css' });
    const url = URL.createObjectURL(blob);
    const a = document.createElement('a');
    a.href = url;
    a.download = `${text}-animation.css`;
    document.body.appendChild(a);
    a.click();
    document.body.removeChild(a);
    URL.revokeObjectURL(url);
  };

  return (
    <div className="container">
      <h1>字体 SVG 转换器</h1>
      
      <div className="input-group">
        <label>
          选择字体文件 (TTF/OTF):
          <input
            type="file"
            accept=".ttf,.otf"
            onChange={handleFileChange}
            disabled={isLoading}
          />
        </label>
      </div>

      <div className="input-group">
        <label>
          输入文本:
          <input
            type="text"
            value={text}
            onChange={(e) => setText(e.target.value)}
            disabled={isLoading}
            placeholder="请输入要转换的文字"
          />
        </label>
      </div>

      <div className="input-group">
        <label>
          字体大小:
          <input
            type="number"
            value={fontSize}
            onChange={(e) => setFontSize(Number(e.target.value))}
            min="8"
            max="200"
            disabled={isLoading}
          />
        </label>
      </div>

      <button 
        className="convert-button"
        onClick={handleConvert}
        disabled={!fontFile || isLoading}
      >
        {isLoading ? '转换中...' : '生成预览'}
      </button>

      {isLoading && <div className="loading">正在生成 SVG...</div>}

      {svg && (
        <div className="svg-preview">
          <h3>预览:</h3>
          <div dangerouslySetInnerHTML={{ __html: svg }} />
          <div className="button-group">
            <button 
              className="download-button"
              onClick={handleDownload}
            >
              下载 SVG
            </button>
            <button 
              className="download-button"
              onClick={handleDownloadCss}
            >
              下载动画 CSS
            </button>
          </div>
        </div>
      )}
    </div>
  );
};

export default App;