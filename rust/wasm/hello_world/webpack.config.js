module.exports = {
    entry: './src/index.js',
    mode: 'development',  // 或 'production'
    experiments: {
        asyncWebAssembly: true,  // 或 syncWebAssembly
    },
    module: {
        rules: [
            {
                test: /\.wasm$/,
                type: "webassembly/async"  // 如果你选择异步方式
            }
        ]
    },
    // 其他配置
};
