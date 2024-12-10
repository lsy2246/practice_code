@echo off
title CZR启动程序
echo 正在启动程序...

:: 创建日志文件
echo %date% %time% > startup_log.txt
echo =============== 启动日志 =============== >> startup_log.txt

:: 获取批处理文件所在目录
cd /d "%~dp0"
echo 当前目录: %CD% >> startup_log.txt

:: 检查czr目录是否存在
if not exist "czr" (
    echo 错误：找不到czr文件夹！ >> startup_log.txt
    echo 错误：找不到czr文件夹！
    echo 当前目录是：%CD%
    echo 请确保start.bat文件与czr文件夹在同一目录
    type startup_log.txt
    pause
    exit /b 1
)

:: 切换到czr目录
cd czr
echo 已进入czr目录: %CD% >> startup_log.txt

:: 检查package.json是否存在
if not exist "package.json" (
    echo 错误：在czr目录中找不到package.json文件！ >> startup_log.txt
    echo 错误：在czr目录中找不到package.json文件！
    echo 当前目录是：%CD%
    type startup_log.txt
    pause
    exit /b 1
)

:: 检查是否安装了Node.js
where npm >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo 错误：未安装Node.js或npm！ >> startup_log.txt
    echo 错误：未安装Node.js或npm！
    echo 请先安装Node.js: https://nodejs.org/
    type startup_log.txt
    pause
    exit /b 1
)

:: 检查node_modules是否存在
if not exist "node_modules" (
    echo node_modules文件夹不存在，正在安装依赖... >> startup_log.txt
    echo node_modules文件夹不存在，正在安装依赖...
    call npm install
    if %ERRORLEVEL% neq 0 (
        echo npm install 失败！ >> startup_log.txt
        echo npm install 失败！
        type startup_log.txt
        pause
        exit /b 1
    )
)

:: 执行npm run start
echo 正在执行 npm run start... >> startup_log.txt
echo 正在执行 npm run start...
call npm run start

:: 如果npm命令执行失败
if %ERRORLEVEL% neq 0 (
    echo 执行npm run start时出错！ >> startup_log.txt
    echo 执行npm run start时出错！
    echo 错误代码：%ERRORLEVEL%
    type startup_log.txt
    pause
    exit /b 1
)

type startup_log.txt
pause 