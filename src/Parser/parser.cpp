#include "parser.hpp"

void Parser::advance() {
    // used to parse each token individually.
    if(token_idx < tokenList) {
        current_token = tokenList[token_idx];
        token_idx++;
    }
    return(current_token);
}

void Parser::classifiedNodes() {
    
}