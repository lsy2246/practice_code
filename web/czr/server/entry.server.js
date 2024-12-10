import { renderToString } from 'react-dom/server';
import { RemixServer } from '@remix-run/react';
import { createReadStream, createWriteStream } from 'fs';
import { mkdir } from 'fs/promises';
import { dirname, resolve } from 'path';
import { fileURLToPath } from 'url';

const __dirname = dirname(fileURLToPath(import.meta.url));
const projectRoot = resolve(__dirname, '..');

async function generateHTML() {
  try {
    const distDir = resolve(projectRoot, 'dist');
    await mkdir(distDir, { recursive: true });
    
    const html = `
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Your App</title>
  </head>
  <body>
    <div id="root"></div>
    <script type="module" src="/assets/index.js"></script>
  </body>
</html>`;

    const indexPath = resolve(distDir, 'index.html');
    const writer = createWriteStream(indexPath);
    writer.write(html);
    writer.end();
    
    console.log('HTML file generated successfully at:', indexPath);
  } catch (error) {
    console.error('Error generating HTML:', error);
    process.exit(1);
  }
}

generateHTML(); 