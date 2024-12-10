import express from 'express';
import { dirname, resolve } from 'path';
import { fileURLToPath } from 'url';

const __dirname = dirname(fileURLToPath(import.meta.url));
const projectRoot = resolve(__dirname, '..');

const app = express();
const port = process.env.PORT || 3000;

// 设置静态文件目录
app.use(express.static(resolve(projectRoot, 'dist')));

// 所有路由都返回 index.html
app.get('*', (req, res) => {
  res.sendFile(resolve(projectRoot, 'dist', 'index.html'));
});

// 确保dist目录存在
import { mkdir } from 'fs/promises';
try {
  await mkdir(resolve(projectRoot, 'dist'), { recursive: true });
} catch (error) {
  console.error('Error creating dist directory:', error);
}

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
  console.log('Static files directory:', resolve(projectRoot, 'dist'));
  console.log('Index file path:', resolve(projectRoot, 'dist', 'index.html'));
}); 