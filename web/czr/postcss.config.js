export default {
  plugins: {
    tailwindcss: {},
    autoprefixer: {
      // 添加更明确的浏览器支持范围
      overrideBrowserslist: [
        '> 1%',
        'last 2 versions',
        'not dead'
      ]
    }
    // 暂时移除cssnano，因为它还没有被安装
  },
};