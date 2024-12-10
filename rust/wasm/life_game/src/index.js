import {Universe} from "@lsy2246/life_game";

const canvas = document.querySelector('#game-of-life-canvas');
const universe = Universe.new();

let animationId = null;
const width = universe.width();
const height = universe.height();

const CELL_SIZE = 5; // px
const GRID_COLOR = "#CCCCCC";
const DEAD_COLOR = "#FFFFFF";
const ALIVE_COLOR = "#000000";

canvas.height = (CELL_SIZE + 1) * height + 1;
canvas.width = (CELL_SIZE + 1) * width + 1;

const ctx = canvas.getContext('2d');

const renderLoop = () => {
    // 每一帧更新细胞状态
    universe.tick();

    // 绘制网格和细胞
    drawGrid();
    drawCells();

    // 请求下一帧
    animationId=requestAnimationFrame(renderLoop);
};

const drawGrid = () => {
    ctx.beginPath();
    ctx.strokeStyle = GRID_COLOR;
    for (let i = 0; i <= width; i++) {
        ctx.moveTo(i * (CELL_SIZE + 1) + 1, 0);
        ctx.lineTo(i * (CELL_SIZE + 1) + 1, (CELL_SIZE + 1) * height + 1);
    }
    for (let j = 0; j <= height; j++) {
        ctx.lineTo(0, j * (CELL_SIZE + 1) + 1);
        ctx.lineTo((CELL_SIZE + 1) * width + 1, j * (CELL_SIZE + 1) + 1);
    }

    ctx.stroke();
};

const drawCells = () => {
    const cells = universe.get_cells();

    ctx.beginPath();

    // 遍历每个细胞，渲染它们的颜色
    for (let row = 0; row < height; row++) {
        for (let col = 0; col < width; col++) {
            const idx = row * width + col;
            const cell = cells[idx];

            ctx.fillStyle = cell === 0 ? DEAD_COLOR : ALIVE_COLOR;
            ctx.fillRect(
                col * (CELL_SIZE + 1) + 1,
                row * (CELL_SIZE + 1) + 1,
                CELL_SIZE,
                CELL_SIZE
            );
        }
    }

    ctx.stroke();
};

// 开始游戏循环
drawGrid();
drawCells();
requestAnimationFrame(renderLoop);

const playPauseButton = document.getElementById("play-pause");
const play = () => {
    playPauseButton.textContent = "⏸";
    renderLoop();
};

const pause = () => {
    playPauseButton.textContent = "▶";
    cancelAnimationFrame(animationId);
    animationId = null;
};

playPauseButton.addEventListener("click", event => {
    if (animationId === null) {
        play();
    } else {
        pause();
    }
});


canvas.addEventListener("click", event => {
    const boundingRect = canvas.getBoundingClientRect();

    const scaleX = canvas.width / boundingRect.width;
    const scaleY = canvas.height / boundingRect.height;

    const canvasLeft = (event.clientX - boundingRect.left) * scaleX;
    const canvasTop = (event.clientY - boundingRect.top) * scaleY;

    const row = Math.min(Math.floor(canvasTop / (CELL_SIZE + 1)), height - 1);
    const col = Math.min(Math.floor(canvasLeft / (CELL_SIZE + 1)), width - 1);

    universe.toggle_cell(row, col);

    drawGrid();
    drawCells();
});

document.querySelector('#play-clear').addEventListener('click', () => {
    pause();
    universe.clear_cells();
    drawGrid();
    drawCells();
})