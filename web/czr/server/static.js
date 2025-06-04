import express from 'express';
import { fileURLToPath } from 'url';
import { dirname, join } from 'path';
import cors from 'cors';

const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);
const app = express();
const PORT = process.env.PORT || 3000;

// 启用CORS
app.use(cors());

// 静态文件服务
app.use(express.static(join(__dirname, '../build')));

// 所有请求都返回index.html
app.get('*', (req, res) => {
  res.sendFile(join(__dirname, '../build/index.html'));
});

// 启动服务器
app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}`);
}); 