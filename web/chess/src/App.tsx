import init, {ChessGame} from '../pkg';
import React, {createContext, useContext, useEffect, useState} from "react"; // 确保路径正确
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
    const {setChessGame} = useContext(chessGameContext);
    const handleClick = () => {
        setConfigureState(true);
    };

    const dataSubmit = () => {
        const modeElemet=document.getElementById('mode') as HTMLSelectElement;
        const roundDurationElemet=document.getElementById('roundDuration') as HTMLSelectElement;
        const matchDurationElemet=document.getElementById('matchDuration') as HTMLSelectElement;
        const currentElment=document.getElementById('current') as HTMLSelectElement;
        if (modeElemet && roundDurationElemet && matchDurationElemet && currentElment ) {
            const mode=modeElemet.value;
            const current=currentElment.value;
            const roundDuration=Number(roundDurationElemet);
            const matchDuration=Number(roundDurationElemet.value);
            if(matchDuration!=0&&matchDuration<roundDuration||(matchDuration!=0&&roundDuration===0)) {
                alert("回合时长不能比对局时长长")
            }
            const chessGame=ChessGame.new(current,roundDuration,matchDuration,mode)
            setChessGame(chessGame)
            setGameState(false);
        }
        else{
            alert("信息不完整")
        }
    }

    return (
        configureState ? (
            <div className="configure">
                <span className="title">配置菜单</span>
                <span className="x" onClick={() => {
                    setConfigureState(false)
                }}>✕</span>
                <div className="option">
                    <span>模式</span>
                    <select id={"mode"}>
                        <option value={"local"}>本地对战</option>
                        <option value={"online"}>在线对战</option>
                        <option value={"robot"}>人机对战</option>
                    </select>
                    <span id={"roundDuration"}>每轮时间</span>
                    <select>
                        <option value={0}>无限制</option>
                        <option value={30}>30秒</option>
                        <option value={60}>60秒</option>
                        <option value={90}>90秒</option>
                        <option value={120}>120秒</option>
                    </select>
                    <span>总时长</span>
                    <select id={"matchDuration"}>
                        <option value={0}>无限制</option>
                        <option value={5 * 60}>5分钟</option>
                        <option value={10 * 60}>10分钟</option>
                        <option value={30 * 60}>30分钟</option>
                        <option value={60 * 60}>60分钟</option>
                    </select>
                    <span>谁先玩</span>
                    <select id={"current"}>
                        <option value={"black"}>黑棋</option>
                        <option value={"white"}>白棋</option>
                        <option value={"random"}>随机</option>
                    </select>
                </div>
                <span className="start" onClick={dataSubmit}>开始</span>
            </div>
        ) : (
            <div className="homeMenu">
                <h1>国际象棋</h1>
                <ul>
                    <li onClick={handleClick}>创建对局</li>
                </ul>
            </div>
        )
    )
};

function drawChess(chessGame:ChessGame|undefined) {
    const canvas = document.getElementById('chessBoardCanvas') as HTMLCanvasElement;
    const chessWidth=60
    const chessHeight=60
    canvas.width = chessWidth*8;
    canvas.height = chessHeight*8;
    const ctx = canvas.getContext('2d') as CanvasRenderingContext2D;
    ctx.beginPath();
    ctx.strokeStyle="#BF9970";
    for (let i = 1; i < 8; i++) {
        ctx.moveTo(i * chessWidth, 0);
        ctx.lineTo(i * chessWidth, canvas.height);
    }
    for (let i = 1; i < 8; i++) {
        ctx.moveTo(0, i * chessHeight);
        ctx.lineTo(canvas.width,i * chessHeight);
    }
    const loadImagePromises: Promise<void>[] = [];
    const chess_all= chessGame?.get_chessboard() as Array<Array<string>>; ;
    chess_all.forEach((chess,index) => {
        const row=Math.floor(index/8);
        const line=index-row*8;
        let color;
        const depth="#F0D9B5";
        const deep="#B58863";
        if (row%2==0){
            color=line%2==0?depth:deep;
        }else{
            color=line%2==1?depth:deep;
        }

        ctx.fillStyle = color;
        ctx.fillRect(chessWidth*line, row*chessHeight, chessWidth, chessHeight);
        if (chess[0]!="none"){
            const img = new Image();
            img.src = `/chess/${chess[1]}_${chess[0]}.svg`;

            const imgPromise=new Promise<void>(resolve => {
                img.onload = () => {
                    ctx.drawImage(img, chessWidth*line, row*chessHeight, chessWidth, chessHeight);
                    resolve();
                };
            })
            loadImagePromises.push(imgPromise);
        }
    })
    Promise.all(loadImagePromises).then(() => {
        ctx.stroke();
    })

}


const Game: React.FC = () => {
    const {chessGame} = useContext(chessGameContext);
    const [movestate,setMoveState] = useState(false);
    const [movechess,setMoveChess] = useState(Array);

    useEffect(()=>{
        drawChess(chessGame);
        console.log(chessGame?.render())
    },[])
    function chessBoardClick(e: React.MouseEvent<HTMLCanvasElement>) {
        const client=e.currentTarget.getBoundingClientRect();
        const clickX = e.clientX-client.x;
        const clickY = e.clientY-client.y;
        const row=Math.floor(clickX/60);
        const line=Math.floor(clickY/60);
        const index=row+line*8;
        console.log(row,line,chessGame?.get_chess_action(index));

        // if (result){
        //
        // }else{
        //     const result=chessGame?.get_chess(index);
        // }

    }
    return (<canvas id={"chessBoardCanvas"} onClick={chessBoardClick}></canvas>)
}


export default App;