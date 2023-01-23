#[macro_use] extern crate scan_fmt;
use std::error::Error ;
use rand::prelude::*;
use std::env;

const GU:usize = 0;
const CYOKI:usize=1;
const PA:usize=2;
const CAT_SIZE:usize=3;

const WIN:i8=1;
const LOSE:i8=-1;
const DRAW:i8=0;

const ALPHA:f64=0.01;

fn main() -> Result<(),Box<dyn Error>> {
    let args: Vec<String> = env::args().collect();
    dbg!(args);

    let mut rate = [1f64,1f64,1f64];
    let payoff_matrix =[[DRAW,WIN,LOSE],
        [LOSE,DRAW,WIN],
        [WIN,LOSE,DRAW]];

    while let Some(opponent_hand) = scanln_fmt_some!( "{d}",usize) {
        if opponent_hand < GU || opponent_hand > PA {continue;}
        let my_hand = hand(rate);
        let gain = payoff_matrix[my_hand][opponent_hand];
        rate[my_hand] += (gain as f64)* ALPHA * rate[my_hand];
        println!("{} {} {} {} {} {}",my_hand,opponent_hand,gain,rate[GU],rate[CYOKI],rate[PA]);
    }
    Ok(())
}

fn hand(rate : [f64;CAT_SIZE])->usize {
    let mut rng = thread_rng();
    let mut acc=rate;
    for i in 1..CAT_SIZE {
        acc[i] += acc[i-1];
    }
    let max = acc[CAT_SIZE-1];
    let r: f64 = rng.gen_range(0.0..max); // generates a float between 0 and 1
    for i in 0..CAT_SIZE {
        if r < acc[i] {
            return i;
        }
    }
    return CAT_SIZE - 1;
}