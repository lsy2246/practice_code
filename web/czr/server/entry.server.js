import fs from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

// 读取HTML模板
const template = fs.readFileSync(path.resolve(__dirname, '../index.html'), 'utf-8');

// 读取构建后的资源
const buildDir = path.resolve(__dirname, '../build');

// 生成静态HTML并写入构建目录
try {
  // 确保build目录存在
  if (!fs.existsSync(buildDir)) {
    fs.mkdirSync(buildDir, { recursive: true });
  }
  
  // 写入HTML文件
  fs.writeFileSync(path.join(buildDir, 'index.html'), template);
  console.log('Successfully generated HTML file');
  
  // 任务完成后退出
  process.exit(0);
} catch (error) {
  console.error('Error generating HTML:', error);
  process.exit(1);
} 