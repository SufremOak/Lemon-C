// filepath: /lemonc-ext-transpiler/lemonc-ext-transpiler/src/transpiler.rs
use pest::iterators::Pairs;
use pest::Parser;
use std::fs::File;
use std::io::{self, Write};

use crate::ext::lang::{parse_source, Rule};

pub fn transpile_to_cpp(pairs: Pairs<Rule>, output_file: &str) -> io::Result<()> {
    let mut file = File::create(output_file)?;

    for pair in pairs {
        match pair.as_rule() {
            Rule::function => {
                let function_name = pair.into_inner().next().unwrap().as_str();
                writeln!(file, "void {}();", function_name)?;
            }
            Rule::struct_def => {
                let struct_name = pair.into_inner().next().unwrap().as_str();
                writeln!(file, "struct {} {{}};", struct_name)?;
            }
            _ => {}
        }
    }

    Ok(())
}

pub fn transpile(pairs: Pairs<Rule>) -> String {
    let mut output = String::from("// Generated C++ header\n\n");
    for pair in pairs {
        match pair.as_rule() {
            Rule::file => {
                for inner in pair.into_inner() {
                    output.push_str(&transpile_item(inner));
                }
            }
            _ => {}
        }
    }
    output
}

fn transpile_item(pair: pest::iterators::Pair<Rule>) -> String {
    match pair.as_rule() {
        // Add more rules as your grammar grows!
        Rule::EOI => String::new(),
        _ => format!("// Unhandled: {:?}\n", pair.as_str()),
    }
}