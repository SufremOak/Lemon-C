// filepath: /lemonc-ext-transpiler/lemonc-ext-transpiler/src/parser.rs
use pest::iterators::Pairs;
use pest::Parser;
use crate::ext::lang::{LangParser, Rule};

pub fn parse_and_process(source: &str) -> Result<Pairs<Rule>, pest::error::Error<Rule>> {
    let pairs = LangParser::parse(Rule::program, source)?;
    // Additional processing logic can be added here
    Ok(pairs)
}

// Additional helper functions for parsing can be implemented here.