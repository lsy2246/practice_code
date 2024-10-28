import init, {ChessGame} from '../pkg';
import React, {useContext, useEffect, useState, createContext, useRef} from "react"; // 确保路径正确
import "./App.css"

const chessGameContext = createContext<{
    chessGame: ChessGame | undefined;
    setChessGame: React.Dispatch<React.SetStateAction<ChessGame | undefined>>;
}>({
    chessGame: undefined, setChessGame: () => {
    }
});

const gameStateContext = createContext<{
    gameState: boolean;
    setGameState: React.Dispatch<React.SetStateAction<boolean>>;
}>({
    gameState: false, setGameState: () => {
    }
});


const App: React.FC = () => {
    const [wasmLoading, setWasmLoading] = useState(false);
    const [gameState, setGameState] = useState(true);
    const [chessGame, setChessGame] = useState<undefined | ChessGame>(undefined);
    useEffect(() => {
        const load = async () => {
            try {
                await init();
                setWasmLoading(true);
            } catch (e) {
                console.log("wasm加载失败:", e)
            }
        }
        load();
    }, []);
    if (!wasmLoading) {
        return <div>正在获取 wasm...</div>;
    }
    return (
        <gameStateContext.Provider value={{gameState, setGameState}}>
            <chessGameContext.Provider value={{chessGame, setChessGame}}>
                <div>
                    {gameState ? <Home/> : <Game/>}
                </div>
            </chessGameContext.Provider>
        </gameStateContext.Provider>
    );
};


const Home: React.FC = () => {
    const [configureState, setConfigureState] = useState<boolean>(false);
    const {setGameState} = useContext(gameStateContext);
    const handleClick = () => {
        setConfigureState(true);
    };

    return (
        configureState ? (
            <div className="configure">
                <span className="title">配置菜单</span>
                <span className="x" onClick={()=>{setConfigureState(false)}}>✕</span>
                <div className="option">
                    <span>模式</span>
                    <select>
                        <option>1</option>
                        <option>2</option>
                    </select>
                    <span>每轮时间</span>
                    <select>
                        <option>1</option>
                        <option>2</option>
                    </select>
                    <span>每位玩家分钟数</span>
                    <select>
                        <option>1</option>
                        <option>2</option>
                    </select>
                    <span>谁先玩</span>
                    <select>
                        <option>1</option>
                        <option>2</option>
                    </select>
                </div>
                <span className="start">开始</span>
            </div>
        ) : (
            <div className="homeMenu chessBoard">
                <h1>国际象棋</h1>
                <ul>
                    <li onClick={handleClick}>创建对局</li>
                </ul>
            </div>
        )
    )
};

const Game: React.FC = () => {
    return (<div>游戏</div>)
}

export default App;