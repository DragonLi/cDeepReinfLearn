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
const LAST_NO:usize = 1000;

fn main() -> Result<(),Box<dyn Error>> {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        println!("使用方法 ch1 j / ch1 randhandgen (石头的比例)(剪刀的比例)(布的比例)");
        return Ok(());
    }
    if args[1] == "randhandgen" && args.len() >= 5 {
        let mut rate = [0f64;CAT_SIZE];
        for i in 0..CAT_SIZE {
            rate[i]= scan_fmt!(&args[i+2],"{}",f64)?;
        }
        // let mut stat = [0;CAT_SIZE];
        for _ in 0..LAST_NO {
            let h = hand(rate);
            // stat[h] += 1;
            println!("{}", h);
        }
        // println!("{:?}",stat);
    }else if args[1] == "j" {
        let mut rate = [1f64;CAT_SIZE];
        let payoff_matrix =[[DRAW,WIN,LOSE],
            [LOSE,DRAW,WIN],
            [WIN,LOSE,DRAW]];

        while let Some(opponent_hand) = scanln_fmt_some!( "{d}",usize) {
            if opponent_hand < GU || opponent_hand > PA {continue;}
            let my_hand = hand(rate);
            let gain = payoff_matrix[my_hand][opponent_hand];
            // too easy to overflow
            // rate[my_hand] += (gain as f64)* ALPHA * rate[my_hand];
            rate[my_hand] += (gain as f64)* ALPHA;
            println!("{my_hand} {opponent_hand} {gain} {:.6} {:.6} {:.6}",rate[GU],rate[CYOKI],rate[PA]);
        }
    }else{
        println!("使用方法 ch1 j / ch1 randhandgen (石头的比例)(剪刀的比例)(布的比例)");
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