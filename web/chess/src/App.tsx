import React, { useEffect, useState } from 'react';
import init, { ChessGame } from '../pkg'; // 确保路径正确

const App: React.FC = () => {


    useEffect(() => {
        const loadWasm = async () => {
            try {
                await init() // 初始化 WASM 模块
                const chessboard= ChessGame.new(5*60)
                console.log(chessboard.render())

            } catch (error) {
                console.error("Failed to load WASM module:", error);
            }
        };

        loadWasm();
    }, []);

    return (
        <div>
            <h1>WASM Module Loaded</h1>
        </div>
    );
};

export default App;
