use std::fmt;
use std::collections::HashMap;
use wasm_bindgen::prelude::*;


enum Grade {
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn,
    None
}

impl Grade {
    fn as_str(&self) -> &'static str {
        match self {
            Grade::King => "king",
            Grade::Queen => "queen",
            Grade::Rook => "rook",
            Grade::Bishop => "bishop",
            Grade::Knight => "knight",
            Grade::Pawn => "pawn",
            Grade::None => "None"
        }
    }
}

#[derive(Hash, Eq, PartialEq)]
enum Camp {
    Black,
    White,
}

impl Camp {
    fn as_str(&self) -> &'static str {
        match self {
            Camp::Black => "black",
            Camp::White => "white",
        }
    }
}

struct Chessman {
    grade: Grade,
    camp: Camp,
}

struct Player {
    username: String,
    time:u32,
    score:u32
}

#[wasm_bindgen]
pub struct ChessGame {
    players: HashMap<Camp, Player>,
    chess: Vec<Chessman>,
}

impl fmt::Display for ChessGame {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        for line in self.chess.as_slice().chunks(8) {
            for square in line {
                write!(f, " ")?;
                match square.camp {
                    Camp::White => {
                        match &square.grade {
                            Grade::King => { write!(f, "♔")?; }
                            Grade::Queen => { write!(f, "♕")?; }
                            Grade::Rook => { write!(f, "♖")?; }
                            Grade::Bishop => { write!(f, "♗")?; }
                            Grade::Knight => { write!(f, "♘")?; }
                            Grade::Pawn => { write!(f, "♙")?; }
                            Grade::None => { write!(f, "※")?; }
                        }
                    }
                    Camp::Black => {
                        match &square.grade {
                            Grade::King => { write!(f, "♚")?; }
                            Grade::Queen => { write!(f, "♛")?; }
                            Grade::Rook => { write!(f, "♜")?; }
                            Grade::Bishop => { write!(f, "♝")?; }
                            Grade::Knight => { write!(f, "♞")?; }
                            Grade::Pawn => { write!(f, "♟")?; }
                            Grade::None => { write!(f, "※")?; }
                        }
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
    pub fn new(time:u32) -> ChessGame {
        fn level_position(index: u8) -> Grade {
            match index {
                0 | 7 => Grade::Rook,
                1 | 6 => Grade::Knight,
                2 | 5 => Grade::Bishop,
                3 => Grade::King,
                4 => Grade::Queen,
                _ => Grade::None
            }
        }
        let chess_game = (0..64).map(|i| {
            let row = i / 8;
            let color = if row == 0 || row == 1 { Camp::Black } else { Camp::White };
            if row == 1 || row == 6 {
                return Chessman { grade: Grade::Pawn, camp: color }
            } else if row == 0 || row == 7 {
                return Chessman { grade: level_position(i % 8), camp: color }
            }  else {
                Chessman { grade: Grade::None, camp: color }
            }
        }).collect();
        let mut players=HashMap::new();
        players.insert(Camp::Black, Player{username:String::from("黑色玩家"), time, score:0 });
        players.insert(Camp::White, Player{username:String::from("白色玩家"), time, score:0 });

        ChessGame { players, chess: chess_game }
    }
    pub fn render(&self) -> String { self.to_string() }
}

