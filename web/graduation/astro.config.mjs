// @ts-check
import { defineConfig } from 'astro/config';
import tailwindcss from '@tailwindcss/vite';

import react from '@astrojs/react';

// https://astro.build/config
export default defineConfig({
  vite: {
    plugins: [tailwindcss()]
  },

  // 服务器配置
  server: {
    port: 3000,
    host: true
  },

  // Markdown 配置
  markdown: {
    syntaxHighlight: 'prism',
    gfm: true,
    shikiConfig: {
      theme: 'github-dark',
      langs: [],
      wrap: true,
    }
  },

  integrations: [react()]
});