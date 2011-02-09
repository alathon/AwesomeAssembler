MAIN_FILE=main.cpp
LEXER=lexer
OUT=main
CFLAGS=-DQUEX_OPTION_ASSERTS_DISABLED -I$(QUEX_PATH) -I.

nice: quex $(MAIN_FILE)
	g++ $(MAIN_FILE) $(LEXER).cpp $(CFLAGS) -o $(OUT)

quex: $(LEXER).qx
	quex -i $(LEXER).qx -o $(LEXER) 
clean: cleanaux
	rm -rf $(OUT)

cleanaux:
	rm -rf $(LEXER).cpp
	rm -rf $(LEXER) $(LEXER)-token $(LEXER)-token_ids 
	rm -rf $(LEXER)-configuration
