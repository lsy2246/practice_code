import { vitePlugin as remix } from "@remix-run/dev";
import { defineConfig } from "vite";
import tsconfigPaths from "vite-tsconfig-paths";
import { Plugin } from 'vite';

// 创建一个自定义插件，在构建完成后自动退出进程
const forceExit: Plugin = {
  name: 'force-exit',
  closeBundle() {
    if (process.env.NODE_ENV === 'production') {
      console.log('构建完成，正在退出进程...');
      setTimeout(() => {
        process.exit(0);
      }, 1000);
    }
  }
};

export default defineConfig({
  plugins: [
    remix({
      // 使用Vercel适配器
      serverModuleFormat: "esm",
      // 这里不需要其他future设置
    }),
    tsconfigPaths(),
    forceExit, // 添加强制退出插件
  ],
  css: {
    devSourcemap: true,
  },
  build: {
    outDir: 'build',
    assetsDir: 'assets',
    cssCodeSplit: true,
    cssMinify: true,
    manifest: true,
    rollupOptions: {
      output: {
        assetFileNames: `assets/[name].[hash][extname]`,
        chunkFileNames: `assets/[name].[hash].js`,
        entryFileNames: `assets/[name].[hash].js`
      }
    }
  },
  base: '/',
})
