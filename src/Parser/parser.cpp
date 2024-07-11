#include "parser.hpp"

void Parser::advance() {
    // used to parse each token individually.
    if(token_idx < tokenList) {
        current_token = tokenList[token_idx];
        token_idx++;
    }
    return(current_token);
}

void Parser::parse(){
    return; // Come back to me!
}

NumNode Parser::factor() {
    Token tok = current_token;

    if(tok.type == TT_INT || tok.type == TT_FLOAT) {
        advance();
        return(NumNode(tok));
    }

    return(NumNode({UNKNOWN, -1}))
}

void Parser::term() {
    NumNode left = factor();
    if(left.getToken().type == UNKNOWN) return;

    while(current_token.type == TT_MUL || current_token.type == TT_DIV) {
        
    }
}

void Parser::expr() {
    return; // Come back to me!
}
