// filepath: /lemonc-ext-transpiler/lemonc-ext-transpiler/src/ext/lang.rs
use pest::Parser;
use pest_derive::Parser;

#[derive(Parser)]
#[grammar = "ext/grammar.pest"] // relative to src/
pub struct LangParser;

pub type Rule = self::Rule;

pub fn parse_source(source: &str) -> Result<pest::iterators::Pairs<Rule>, pest::error::Error<Rule>> {
    LangParser::parse(Rule::file, source)
}