import express from 'express';
import { createRequestHandler } from "@remix-run/express";
import * as build from "../build/server/index.js";

const app = express();

// 静态文件服务
app.use(express.static("public"));
app.use(express.static("build/client"));

// Remix 请求处理
app.all(
  "*",
  createRequestHandler({
    build,
    mode: "production",
  })
);

const port = process.env.PORT || 3000;
app.listen(port, () => {
  console.log(`Express server listening on port ${port}`);
}); 