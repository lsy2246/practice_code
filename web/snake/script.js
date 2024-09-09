// 随机数
function random(min, max) {
    if(max){
        return Math.floor(Math.random() * (max - min)) + min;
    }
    else{
        return Math.floor(Math.random() * 10);
    }
}
// 定义尺寸
const lengthX=50
const lengthY=50
const backWidth=16
const backHeight=16
// 游戏当前模式
let gameMode=null
// 蛇数组
let snakeAll=[]
// 食物模型
const food=document.createElement('div')
food.style.width=backWidth+'px'
food.style.height=backHeight+'px'
food.classList.add('food')
for(let i=0;i<4;i++){
    let foodSingle=document.createElement('div')
    foodSingle.classList.add('foodSingle')
    food.appendChild(foodSingle)
}
// 食物总数
let foodNumber=0
let foodNumberNow=0
// 颜色
let color=['AliceBlue','PaleGoldenrod','Cyan','LightBlue','LightCyan','Beige','LightGrey','LightGreen']
// 创建地图
const map=document.createElement('div')
map.style.width=lengthX*backWidth+'px'
map.style.height=lengthY*backHeight+'px'
map.classList.add('map')
document.body.appendChild(map)
// 添加地图格子
let mapBlock=[]
for(let i=0;i<lengthX;i++){
    mapBlock[i]=[]
}
for(let i=0;i<lengthX;i++){
    for(let j=0;j<lengthY;j++){
        mapBlock[i][j]=document.createElement('div')
        mapBlock[i][j].style.width=backWidth+'px'
        mapBlock[i][j].style.height=backHeight+'px'
        mapBlock[i][j].classList.add('mapBlock')
        mapBlock[i][j].dataset.mapBlockX=`${i}`
        mapBlock[i][j].dataset.mapBlockY=`${j}`
        map.appendChild(mapBlock[i][j])
    }
}
// 开始界面
const mapTextNameDiv=document.createElement('div')
const mapTextName=document.createElement('div')

mapTextName.classList.add('mapTextName')
mapTextName.innerText='贪吃蛇'

mapTextNameDiv.appendChild(mapTextName)

map.appendChild(mapTextNameDiv)

const mapTextStartDiv=document.createElement('div')
mapTextStartDiv.classList.add('mapTextStart')

const mapTextStartSingle=document.createElement('div')
mapTextStartSingle.innerText='单人'
mapTextStartDiv.appendChild(mapTextStartSingle)
mapTextStartSingle.addEventListener('click', singleMode)

const mapTextStartDouble=document.createElement('div')
mapTextStartDouble.innerText='双人'
mapTextStartDiv.appendChild(mapTextStartDouble)
mapTextStartDouble.addEventListener('click', doubleMode)


const mapTextStartAI=document.createElement('div')
mapTextStartAI.innerText='人机'
mapTextStartDiv.appendChild(mapTextStartAI)
mapTextStartAI.addEventListener('click', aiMode)


map.appendChild(mapTextStartDiv)

mapTextStartDiv.addEventListener('click',function(){
    mapTextNameDiv.style.display='none'
    mapTextStartDiv.style.display='none'
})
// 辅助操作界面
const playerOneDiv=document.createElement('div')
playerOneDiv.classList.add('playerOne')

const playerOneText=document.createElement('p')
playerOneText.innerText="一号玩家"
playerOneDiv.appendChild(playerOneText)

const playerOneScoreDiv=document.createElement('div')
const playerOneScoreText=document.createElement('p')
playerOneScoreText.innerText="长度："
const playerOneScore=document.createElement('p')
playerOneScoreDiv.appendChild(playerOneScoreText)
playerOneScoreDiv.appendChild(playerOneScore)
playerOneDiv.appendChild(playerOneScoreDiv)

const playerOneMove=document.createElement('div')
playerOneMove.innerText="移动：W A S D"
playerOneDiv.appendChild(playerOneMove)

const playerTwoDiv=document.createElement('div')
playerTwoDiv.classList.add('playerTwo')

const playerTwoText=document.createElement('p')
playerTwoText.innerText="二号玩家"
playerTwoDiv.appendChild(playerTwoText)

const playerTwoScoreDiv=document.createElement('div')
const playerTwoScoreText=document.createElement('p')
playerTwoScoreText.innerText="长度："
const playerTwoScore=document.createElement('p')
playerTwoScoreDiv.appendChild(playerTwoScoreText)
playerTwoScoreDiv.appendChild(playerTwoScore)
playerTwoDiv.appendChild(playerTwoScoreDiv)

const playerTwoMove=document.createElement('div')
playerTwoMove.innerText="移动：↑↓←→"
playerTwoDiv.appendChild(playerTwoMove)

document.body.appendChild(playerOneDiv)
document.body.appendChild(playerTwoDiv)
// 随机生成食物函数
function foodCreate(){
    if(foodNumberNow<foodNumber){
        const foodX=random(0,lengthX)
        const foodY=random(0,lengthY)
        if (mapBlock[foodX][foodY].childNodes.length===0){
            mapBlock[foodX][foodY].appendChild(food.cloneNode(true))
            foodNumberNow+=1
        }
        else{
            foodCreate()
        }
    }
}
//  吃掉食物函数
function foodEat(foodParent,snakeArr,snake){
    foodParent.removeChild(foodParent.childNodes[0])
    snakeArr.unshift(snake)
    foodParent.appendChild(snake)
    foodNumberNow-=1
    foodCreate()
    if(gameMode==='single'||gameMode==='double'||gameMode==='ai'&&snake.dataset.id==='0'){
        playerOneScore.innerText=`${snakeAll[0].snake.length}`
    }
    else if(gameMode==='double'&&snake.dataset.id==='1'){
        playerTwoScore.innerText=`${snakeAll[1].snake.length}`
    }
}
// 生成蛇函数
function snakeCreate(){
    const snake=[]
    let snakeX=random(15,lengthX-15)
    let snakeY=random(15,lengthY-15)
    const snakeColor=color[random(0,color.length)]
    const snakeLength=5
    const direction=random(0,4)
    for (let i=0;i<snakeLength;i++){
        switch(direction){
            case 0:
                if(mapBlock[snakeX+i][snakeY].childNodes.length!==0){
                    snakeCreate()
                    return;
                }
                break
            case 1:
                if(mapBlock[snakeX-i][snakeY].childNodes.length!==0){
                    snakeCreate()
                    return;
                }
                break
            case 2:
                if(mapBlock[snakeX][snakeY+i].childNodes.length!==0){
                    snakeCreate()
                    return;
                }
                break
            case 3:
                if(mapBlock[snakeX][snakeY-i].childNodes.length!==0){
                    snakeCreate()
                    return;
                }
                break
        }
    }
    for (let i=0;i<snakeLength;i++){
        snake[i]=document.createElement('div')
        snake[i].classList.add('snake')
        snake[i].style.width=backWidth+'px'
        snake[i].style.height=backHeight+'px'
        snake[i].style.background=snakeColor
        snake[i].dataset.id=`${snakeAll.length}`
        switch(direction){
            case 0:
                mapBlock[snakeX+i][snakeY].appendChild(snake[i])
                break
            case 1:
                mapBlock[snakeX-i][snakeY].appendChild(snake[i])
                break
            case 2:
                mapBlock[snakeX][snakeY+i].appendChild(snake[i])
                break
            case 3:
                mapBlock[snakeX][snakeY-i].appendChild(snake[i])
                break    
        }
    }
    const snakeInfo={
        snake:snake,
        direction:direction,
        directionTest:direction,
    }
    console.log(snakeInfo)
    snakeAll.push(snakeInfo)
}
// 移动速度
moveSpeed=100
// 移动函数
function move(){
    let parentNode
    let snake
    for (let i = 0; i < snakeAll.length; i++) {
        snake=snakeAll[i].snake[0].cloneNode(true)
        if(snakeAll[i].directionTest===0){
            if(snakeAll[i].direction===1){
                snakeAll[i].directionTest=snakeAll[i].direction
            }
            else{
                snakeAll[i].direction=snakeAll[i].directionTest
            }
        }
        else if(snakeAll[i].directionTest===1){
            if(snakeAll[i].direction===0){
                snakeAll[i].directionTest=snakeAll[i].direction
            }
            else{
                snakeAll[i].direction=snakeAll[i].directionTest
            }
        }
        else if(snakeAll[i].directionTest===2){
            if(snakeAll[i].direction===3){
                snakeAll[i].directionTest=snakeAll[i].direction
            }
            else{
                snakeAll[i].direction=snakeAll[i].directionTest
            }
        }
        else if(snakeAll[i].directionTest===3){
            if(snakeAll[i].direction===2){
                snakeAll[i].directionTest=snakeAll[i].direction
            }
            else{
                snakeAll[i].direction=snakeAll[i].directionTest
            }
        }
        switch(snakeAll[i].directionTest){
            case 0:
                parentNode=snakeAll[i].snake[0].parentNode
                if (Number(parentNode.dataset.mapBlockX)-1>=0 && mapBlock[Number(parentNode.dataset.mapBlockX)-1][Number(parentNode.dataset.mapBlockY)].childNodes.length===0){
                    snakeAll[i].snake.unshift(snake)
                    mapBlock[Number(parentNode.dataset.mapBlockX)-1][Number(parentNode.dataset.mapBlockY)].appendChild(snake)
                    snakeAll[i].snake[snakeAll[i].snake.length-1].parentNode.removeChild(snakeAll[i].snake[snakeAll[i].snake.length-1])
                    snakeAll[i].snake.pop()
                }
                else if(Number(parentNode.dataset.mapBlockX)-1<=0){
                    snakeDie(snakeAll[i].snake,i)
                }
                else{
                    if(mapBlock[Number(parentNode.dataset.mapBlockX)-1][Number(parentNode.dataset.mapBlockY)].childNodes[0].classList.contains('food')){
                        foodEat(mapBlock[Number(parentNode.dataset.mapBlockX)-1][Number(parentNode.dataset.mapBlockY)],snakeAll[i].snake,snake)
                    }
                    else{
                        snakeDie(snakeAll[i].snake,i)
                    }
                }
                break
            case 1:
                parentNode=snakeAll[i].snake[0].parentNode
                if (Number(parentNode.dataset.mapBlockX)+1<lengthX && mapBlock[Number(parentNode.dataset.mapBlockX)+1][Number(parentNode.dataset.mapBlockY)].childNodes.length===0){
                    snakeAll[i].snake.unshift(snake)
                    mapBlock[Number(parentNode.dataset.mapBlockX)+1][Number(parentNode.dataset.mapBlockY)].appendChild(snake)
                    snakeAll[i].snake[snakeAll[i].snake.length-1].parentNode.removeChild(snakeAll[i].snake[snakeAll[i].snake.length-1])
                    snakeAll[i].snake.pop()
                }
                else if(Number(parentNode.dataset.mapBlockX)+1>=lengthX-1){
                    snakeDie(snakeAll[i].snake,i)
                }
                else{
                    if(mapBlock[Number(parentNode.dataset.mapBlockX)+1][Number(parentNode.dataset.mapBlockY)].childNodes[0].classList.contains('food')){
                        foodEat(mapBlock[Number(parentNode.dataset.mapBlockX)+1][Number(parentNode.dataset.mapBlockY)],snakeAll[i].snake,snake)
                    }
                    else{
                        snakeDie(snakeAll[i].snake,i)
                    }
                }
                break
            case 2:
                parentNode=snakeAll[i].snake[0].parentNode
                if (Number(parentNode.dataset.mapBlockY)-1>=0 && mapBlock[Number(parentNode.dataset.mapBlockX)][Number(parentNode.dataset.mapBlockY)-1].childNodes.length===0){
                    snakeAll[i].snake.unshift(snake)
                    mapBlock[Number(parentNode.dataset.mapBlockX)][Number(parentNode.dataset.mapBlockY)-1].appendChild(snake)
                    snakeAll[i].snake[snakeAll[i].snake.length-1].parentNode.removeChild(snakeAll[i].snake[snakeAll[i].snake.length-1])
                    snakeAll[i].snake.pop()
                }
                else if(Number(parentNode.dataset.mapBlockY)-1<=0){
                    snakeDie(snakeAll[i].snake,i)
                }
                else{
                    if(mapBlock[Number(parentNode.dataset.mapBlockX)][Number(parentNode.dataset.mapBlockY)-1].childNodes[0].classList.contains('food')){
                        foodEat(mapBlock[Number(parentNode.dataset.mapBlockX)][Number(parentNode.dataset.mapBlockY)-1],snakeAll[i].snake,snake)
                    }
                    else{
                        snakeDie(snakeAll[i].snake,i)
                    }
                }
                break
            case 3:
                parentNode=snakeAll[i].snake[0].parentNode
                if (Number(parentNode.dataset.mapBlockY)+1<lengthY && mapBlock[Number(parentNode.dataset.mapBlockX)][Number(parentNode.dataset.mapBlockY)+1].childNodes.length===0){
                    snakeAll[i].snake.unshift(snake)
                    mapBlock[Number(parentNode.dataset.mapBlockX)][Number(parentNode.dataset.mapBlockY)+1].appendChild(snake)
                    snakeAll[i].snake[snakeAll[i].snake.length-1].parentNode.removeChild(snakeAll[i].snake[snakeAll[i].snake.length-1])
                    snakeAll[i].snake.pop()
                }
                else if(Number(parentNode.dataset.mapBlockY)+1>=lengthY-1){
                    snakeDie(snakeAll[i].snake,i)
                }
                else{
                    if(mapBlock[Number(parentNode.dataset.mapBlockX)][Number(parentNode.dataset.mapBlockY)+1].childNodes[0].classList.contains('food')){
                        foodEat(mapBlock[Number(parentNode.dataset.mapBlockX)][Number(parentNode.dataset.mapBlockY)+1],snakeAll[i].snake,snake)
                    }
                    else{
                        snakeDie(snakeAll[i].snake,i)
                    }
                }
                break
        }
    }
}
setInterval(move,moveSpeed)
// 死亡函数
function snakeDie(snake,site){
    snakeAll.splice(site,1)
    if (snake[0].dataset.id==='0'){
        diePanelOpen(snake)
        return
    }
    if(gameMode==='double'&&snake[0].dataset.id==='1'){
        diePanelOpen(snake)
        return
    }
    
    for (let i = 0; i < snake.length/3*2 ; i++) {
        let parentNode = snake[snake.length-1].parentNode
        parentNode.removeChild(snake[snake.length-1])
        snake.pop()
        parentNode.appendChild(food.cloneNode(true))
        foodNumberNow+=1
    }
    for (let i = snake.length-1; i >= 0  ;--i) {
        snake[i].parentNode.removeChild(snake[i])
        snake.pop()
    }
    snakeCreate()
}
// 清空地图函数
function mapClear() {
    foodNumberNow=0
    snakeAll=null
    snakeAll=[]
    const snakeClear=document.querySelectorAll('.snake')
    for (let i = 0; i < snakeClear.length ; i++) {
        snakeClear[i].parentNode.removeChild(snakeClear[i])
    }
    const foodClear=document.querySelectorAll('.food')
    for (let i = 0; i < foodClear.length ; i++) {
        foodClear[i].parentNode.removeChild(foodClear[i])
    }
}
// 死亡面板
const diePanelInfo=document.createElement('div')
diePanelInfo.classList.add('diePanelInfo')
map.appendChild(diePanelInfo)

const diePanelText=document.createElement('div')
diePanelInfo.appendChild(diePanelText)

const diePanelScoreDiv=document.createElement('div')
diePanelInfo.appendChild(diePanelScoreDiv)
const diePanelScoreText=document.createElement('p')
diePanelScoreText.innerText=`长度：`
diePanelScoreDiv.appendChild(diePanelScoreText)
const diePanelScore=document.createElement('p')
diePanelScoreDiv.appendChild(diePanelScore)


const diePanelPick=document.createElement('div')
diePanelPick.classList.add('diePanelPick')
map.appendChild(diePanelPick)
diePanelPick.addEventListener('click',mapClear)
diePanelPick.addEventListener('click',function () {
    diePanelInfo.style.display='none'
    diePanelPick.style.display='none'
})

const diePickHome=document.createElement('div')
diePickHome.innerText="返回主页"
diePanelPick.appendChild(diePickHome)
diePickHome.addEventListener('click',function (){
    gameMode = null
    mapTextNameDiv.style.display='block'
    mapTextStartDiv.style.display='block'
})

const diePickRest=document.createElement('div')
diePickRest.innerText="重新开始"
diePanelPick.appendChild(diePickRest)

diePickRest.addEventListener('click',function (){
    if (gameMode==='single'){singleMode()}
    else if (gameMode==='double'){doubleMode()}
    else if (gameMode==='double'){aiMode()}
})
// 开始死亡面板函数
function diePanelOpen(snake){
    document.removeEventListener('click',key1)
    document.removeEventListener('click',key2)
    clearInterval(aiMoveTime)
    playerOneDiv.style.display="none"
    playerTwoDiv.style.display="none"
    diePanelInfo.style.display='block'
    diePanelPick.style.display='block'
    snakeAll=null
    snakeAll=[]
    if(gameMode==='single'||gameMode==='ai'){
        diePanelScoreText.style.display='inline-block'
        diePanelText.innerText='游戏结束'
        diePanelScore.innerText=playerOneScore.innerText
    }
    else if(gameMode==='double'){
        diePanelScoreText.style.display='none'
        if(snake[0].dataset.id==='1'){
            diePanelScore.innerHTML='一号获胜'
        }
        else{
            diePanelScore.innerHTML='二号获胜'
        }
    }
}
// 人机移动逻辑
function aiMove(snake){
    const food=document.querySelectorAll('.food')[snake.snake[0].dataset.id]
    const snakeX=Number(snake.snake[0].parentNode.dataset.mapBlockX)
    const snakeY=Number(snake.snake[0].parentNode.dataset.mapBlockY)
    const foodX=Number(food.parentNode.dataset.mapBlockX)
    const foodY=Number(food.parentNode.dataset.mapBlockY)
    
    if(snake.direction!=='1'&&snakeX-1>=0&&mapBlock[snakeX-1][snakeY].childNodes.length>0){
        if (mapBlock[snakeX-1][snakeY].children[0].classList.contains('food')){
            snake.directionTest=0
            return
        }
    }
    if(snake.direction!=='0'&&snakeX+1<lengthX&&mapBlock[snakeX+1][snakeY].childNodes.length>0){
        if (mapBlock[snakeX+1][snakeY].children[0].classList.contains('food')){
            snake.directionTest=1
            return
        }
    }
    if(snake.direction!=='3'&&snakeY-1>=0&&mapBlock[snakeX][snakeY-1].childNodes.length>0){
        if (mapBlock[snakeX][snakeY-1].children[0].classList.contains('food')){
            snake.directionTest=2
            return
        }
    }
    if(snake.direction!=='2'&&snakeY+1<lengthY&&mapBlock[snakeX][snakeY+1].childNodes.length>0){
        if (mapBlock[snakeX][snakeY+1].children[0].classList.contains('food')){
            snake.directionTest=3
            return
        }
    }
    
    switch(random(0,2)){
        case 0:
            if(snake.direction!=='1'&&snakeX-1>=0&&foodX>snakeX&&mapBlock[snakeX-1][snakeY].childNodes.length===0){
                snake.directionTest=0
                return
            }
            if(snake.direction!=='0'&&snakeX+1<lengthX&&foodX<=snakeX&&mapBlock[snakeX+1][snakeY].childNodes.length===0){
                snake.directionTest=1
                return
            }
            if(snake.direction!=='3'&&snakeY-1>=0&&foodY>snakeY&&mapBlock[snakeX][snakeY-1].childNodes.length===0){
                snake.directionTest=2
                return
            }
            if(snake.direction!=='2'&&snakeY+1<lengthY&&foodY<=snakeY&&mapBlock[snakeX][snakeY+1].childNodes.length===0){
                snake.directionTest=3
                return
            }
        case 1:
            if(snake.direction!=='2'&&snakeY+1<lengthY&&mapBlock[snakeX][snakeY+1].childNodes.length===0){
                snake.directionTest=3
            }
            if(snake.direction!=='3'&&snakeY-1>=0&&mapBlock[snakeX][snakeY-1].childNodes.length===0){
                snake.directionTest=2
                return
            }
            if(snake.direction!=='0'&&snakeX+1<lengthX&&mapBlock[snakeX+1][snakeY].childNodes.length===0){
                snake.directionTest=1
                return
            }
            if(snake.direction!=='1'&&snakeX-1>=0&&mapBlock[snakeX-1][snakeY].childNodes.length===0){
                snake.directionTest=0
                return
            }
    }
    
    
}
function aiMoveOpen(){
    if (snakeAll.length===1){
        return
    }
    else if (snakeAll.length===0){
        clearInterval(aiMoveTime)
        return
    }
    
    for (let i = 1; i < snakeAll.length ; i++) {
        aiMove(snakeAll[i])
    }
}
let aiMoveTime
// 按键监听
const key1=function(e){
    if(snakeAll.length>0){
        if (e.key==='w'){
            snakeAll[0].directionTest=0
        }
        else if (e.key==='s'){
            snakeAll[0].directionTest=1
        }
        else if (e.key==='a'){
            snakeAll[0].directionTest=2
        }
        else if (e.key==='d'){
            snakeAll[0].directionTest=3
        }
    }
    if(snakeAll.length>0){
        if (e.key==="ArrowUp"){
            snakeAll[1].directionTest=0
        }
        else if (e.key==="ArrowDown"){
            snakeAll[1].directionTest=1
        }
        else if (e.key==="ArrowLeft"){
            snakeAll[1].directionTest=2
        }
        else if (e.key==="ArrowRight"){
            snakeAll[1].directionTest=3
        }
    }
}
const key2=function(e){
    if(snakeAll.length>0){
        if (e.key==="ArrowUp"||e.key==='w'){
            snakeAll[0].directionTest=0
        }
        else if (e.key==="ArrowDown"||e.key==='s'){
            snakeAll[0].directionTest=1
        }
        else if (e.key==="ArrowLeft"||e.key==='a'){
            snakeAll[0].directionTest=2
        }
        else if (e.key==="ArrowRight"||e.key==='d'){
            snakeAll[0].directionTest=3
        }
    }
}
// 单人模式
function singleMode(){
    // 改变当前模式
    gameMode='single'
    // 开启辅助操作页面
    playerOneDiv.style.display="block"
    // 生成蛇
    snakeCreate()
    // 更换提示文字颜色
    playerOneText.style.color=snakeAll[0].snake[0].style.backgroundColor;
    // 显示长度
    playerOneScore.innerHTML=`${snakeAll[0].snake.length}`
    // 生成食物
    foodNumber=10
    for(let i=0;i<foodNumber;i++){
        foodCreate()
    }
    // 绑定按钮
    document.addEventListener('keydown',key1)
}
// 双人模式
function doubleMode(){
    // 改变当前模式
    gameMode='double'
    // 开启辅助操作页面
    playerOneDiv.style.display="block"
    playerTwoDiv.style.display="block"
    // 生成蛇
    snakeCreate()
    snakeCreate()
    // 更换提示文字颜色
    playerOneText.style.color=snakeAll[0].snake[0].style.backgroundColor;
    playerTwoText.style.color=snakeAll[1].snake[1].style.backgroundColor;
    // 显示长度
    playerOneScore.innerHTML=`${snakeAll[0].snake.length}`
    playerTwoScore.innerHTML=`${snakeAll[1].snake.length}`
    // 生成食物
    foodNumber=10
    for(let i=0;i<foodNumber;i++){
        foodCreate()
    }
    // 绑定按钮
    document.addEventListener('keydown',key2 )
}
// 人机模式
function aiMode(){
    // 改变当前模式
    gameMode='ai'
    // 开启辅助操作页面
    playerOneDiv.style.display="block"
    // 生成蛇
    const snakeNumber=5
    for(let i=0;i<snakeNumber;i++){
        snakeCreate()
    }
    for(let i=0;i<snakeAll[0].snake.length;i++){
        snakeAll[0].snake[i].style.backgroundColor="rgba(0, 0, 0, 0.75)"
    }
    // 更换提示文字颜色
    playerOneText.style.color=snakeAll[0].snake[0].style.backgroundColor;
    // 显示长度
    playerOneScore.innerHTML=`${snakeAll[0].snake.length}`
    // 开始蛇移动
    aiMoveTime=setInterval(aiMoveOpen, moveSpeed/2)
    // 显示长度
    playerOneScore.innerText=`${snakeAll[0].snake.length}`
    // 生成食物
    foodNumber=15
    for(let i=0;i<foodNumber;i++){
        foodCreate()
    }
    // 绑定按钮
    document.addEventListener('keydown', key1)
}

// // 临时隐藏开始页面
// singleMode()
// mapTextNameDiv.style.display='none'
// mapTextStartDiv.style.display='none'