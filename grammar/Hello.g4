grammar Hello;

@header {
    #include <vector>
}

/****** parser ******/
r  : 'hello' ID ;

/****** lexer  ******/
ID : [a-z]+ ;

/****** skips  ******/
WS : [ \t\r\n]+ -> skip ; 