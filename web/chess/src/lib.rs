use std::collections::HashMap;
use std::fmt;
use wasm_bindgen::prelude::*;
use wasm_bindgen_futures::js_sys;

const CHESS_LINE: u32 = 8;
const CHESS_ROW: u32 = 8;

enum Grade {
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn,
    None,
}

impl Grade {
    fn to_string(&self) -> String {
        match self {
            Grade::King => String::from("king"),
            Grade::Queen => String::from("queen"),
            Grade::Rook => String::from("rook"),
            Grade::Bishop => String::from("bishop"),
            Grade::Knight => String::from("knight"),
            Grade::Pawn => String::from("pawn"),
            Grade::None => String::from("none"),
        }
    }
}

#[derive(Hash, Eq, PartialEq)]
enum Camp {
    Black,
    White,
    None,
}
impl Camp {
    fn to_string(&self) -> String {
        match self {
            Camp::Black => String::from("black"),
            Camp::White => String::from("white"),
            Camp::None => String::from("none"),
        }
    }
    fn from_string(s: String) -> Camp {
        let s = s.to_lowercase();
        match s.as_str() {
            "black" => Camp::Black,
            "white" => Camp::White,
            _ => Camp::None,
        }
    }
}

struct Chessman {
    grade: Grade,
    camp: Camp,
}

struct Player {
    username: String,
    time: u32,
}

enum Mode {
    Local,
    Online,
    Robot,
}
impl Mode {
    pub fn as_string(&self) -> String {
        match self {
            Mode::Local => "local".to_string(),
            Mode::Online => "online".to_string(),
            Mode::Robot => "robot".to_string(),
        }
    }
    pub fn from_string(s: String) -> Mode {
        let s = s.to_lowercase();
        match s.as_str() {
            "local" => Mode::Local,
            "online" => Mode::Online,
            "robot" => Mode::Robot,
            _ => Mode::Local,
        }
    }
}
#[wasm_bindgen]
pub struct Info {
    current: Camp,
    winner: Camp,
    round_duration: u32,
    match_duration: u32,
    mode: Mode,
}

#[wasm_bindgen]
pub struct ChessGame {
    players: HashMap<Camp, Player>,
    chessboard: Vec<Chessman>,
    info: Info,
}

impl fmt::Display for ChessGame {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        for line in self.chessboard.as_slice().chunks(CHESS_ROW as usize) {
            for square in line {
                write!(f, " ")?;
                match square.camp {
                    Camp::White => match &square.grade {
                        Grade::King => {
                            write!(f, "♔")?;
                        }
                        Grade::Queen => {
                            write!(f, "♕")?;
                        }
                        Grade::Rook => {
                            write!(f, "♖")?;
                        }
                        Grade::Bishop => {
                            write!(f, "♗")?;
                        }
                        Grade::Knight => {
                            write!(f, "♘")?;
                        }
                        Grade::Pawn => {
                            write!(f, "♙")?;
                        }
                        Grade::None => {
                            write!(f, "※")?;
                        }
                    },
                    Camp::Black => match &square.grade {
                        Grade::King => {
                            write!(f, "♚")?;
                        }
                        Grade::Queen => {
                            write!(f, "♛")?;
                        }
                        Grade::Rook => {
                            write!(f, "♜")?;
                        }
                        Grade::Bishop => {
                            write!(f, "♝")?;
                        }
                        Grade::Knight => {
                            write!(f, "♞")?;
                        }
                        Grade::Pawn => {
                            write!(f, "♟")?;
                        }
                        Grade::None => {
                            write!(f, "※")?;
                        }
                    },
                    Camp::None => {
                        write!(f, "※")?;
                    }
                }
            }
            write!(f, "\n")?;
        }
        Ok(())
    }
}

#[wasm_bindgen]
impl ChessGame {
    pub fn new(
        current: String,
        round_duration: u32,
        match_duration: u32,
        mode: String,
    ) -> ChessGame {
        fn level_position(index: u8) -> Grade {
            match index {
                0 | 7 => Grade::Rook,
                1 | 6 => Grade::Knight,
                2 | 5 => Grade::Bishop,
                3 => Grade::King,
                4 => Grade::Queen,
                _ => Grade::None,
            }
        }
        let chess_game = (0..CHESS_LINE*CHESS_ROW)
            .map(|i| {
                let row = i / CHESS_LINE;
                let color = if row == 0 || row == 1 {
                    Camp::White
                } else if row == 6 || row == 7 {
                    Camp::Black
                } else {
                    Camp::None
                };
                if row == 1 || row == 6 {
                    return Chessman {
                        grade: Grade::Pawn,
                        camp: color,
                    };
                } else if row == 0 || row == 7 {
                    return Chessman {
                        grade: level_position((i % CHESS_ROW) as u8),
                        camp: color,
                    };
                } else {
                    Chessman {
                        grade: Grade::None,
                        camp: color,
                    }
                }
            })
            .collect();
        let mut players = HashMap::new();
        players.insert(
            Camp::Black,
            Player {
                username: String::from("黑色玩家"),
                time: 0,
            },
        );
        players.insert(
            Camp::White,
            Player {
                username: String::from("白色玩家"),
                time: 0,
            },
        );
        let mut current_convert: Camp;
        if current.to_string() == "black" || current.to_string() == "white" {
            current_convert = Camp::from_string(current);
        } else {
            if js_sys::Math::random() < 0.5 {
                current_convert = Camp::Black;
            } else {
                current_convert = Camp::White;
            }
        }

        let info = Info {
            current: current_convert,
            winner: Camp::None,
            round_duration,
            match_duration,
            mode: Mode::from_string(mode),
        };
        ChessGame {
            players,
            chessboard: chess_game,
            info,
        }
    }
    pub fn render(&self) -> String {
        self.to_string()
    }
}

#[wasm_bindgen]
impl ChessGame {
    pub fn get_chessboard(&self) -> Vec<JsValue> {
        let mut chessboard = Vec::new();
        for i in self.chessboard.iter() {
            let chess = vec![i.grade.to_string(), i.camp.to_string()];
            chessboard.push(JsValue::from(chess));
        }
        chessboard
    }

    pub fn get_chess_action(&self, index: u32) -> Vec<JsValue> {
        let un_index: usize = index as usize;
        if index >= self.chessboard.len() as u32 {
            return vec![JsValue::from(vec!["999", "点击的范围超出的棋盘"])];
        }
        let chess: &Chessman = &self.chessboard[un_index];
        if chess.camp != self.info.current {
            return vec![JsValue::from(vec!["998", "不是该阵营移动"])];
        }
        let line: u32 = index / CHESS_ROW ;
        let row: u32 = index - line * CHESS_LINE ;
        let mut available_locations: Vec<JsValue> = Vec::new();
        match chess.grade {
            Grade::King => {}
            Grade::Queen => {}
            Grade::Rook => {}
            Grade::Bishop => {}
            Grade::Knight => {}
            Grade::Pawn => {
                if chess.camp == Camp::Black && line != 0 {

                }
            },
            Grade::None => {}
        }

        available_locations
    }

}
