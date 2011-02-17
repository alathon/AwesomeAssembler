#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "lexer"

// Max number of arguments possible for an instruction.
#define MAX_ARGUMENTS 5

using namespace std;

enum ParserState { STATE_INST, STATE_ARG, STATE_COMMA, STATE_EOL };

class Instruction {
	private:
		int argCount;
		vector<string> args;

	public:
		Instruction() {
			argCount=0;
		}
		
		virtual string getName() { }

		virtual int desiredArgs() { }

		void receiveArg(const char *s) {
			args.push_back(string(s));
		}

		string binaryRep() {
			return "Hohoho";
		}
};

class AddOp: public Instruction {
	public:
		string getName() { return "add"; }
		int desiredArgs() { return 2; }
};

class SubOp: public Instruction {
	public: 
		string getName() { return "sub"; }
		int desiredArgs() { return 2; }
};

class MulOp: public Instruction {
	public: 
		string getName() { return "mul"; }
		int desiredArgs() { return 2; }
};

class DivOp: public Instruction {
	public: 
		string getName() { return "div"; }
		int desiredArgs() { return 2; }
};

class MovOp: public Instruction {
	public: 
		string getName() { return "mov"; }
		int desiredArgs() { return 2; }
};

class Parser {
	private:
		ParserState state;
		int count; // Used to keep track of how many arguments we've received.
		vector<quex::Token*> tokens;
		vector<Instruction*> instructions;

	public:
		Parser(vector<quex::Token*> t) {
			count=0;
			tokens = t;
		}

		vector<Instruction*> getInst() { return this->instructions; }

		void init() {
			state = STATE_INST;
			Instruction* cur_ins;

			vector<quex::Token*>::iterator itr;
			for( itr = tokens.begin(); itr != tokens.end(); ++itr) {
				quex::Token* token = *itr;
				int tID = token->type_id();
				cout << "Token: ";
				if(tID == QUEX_TKN_IDENTIFIER || tID == QUEX_TKN_STRING)
					cout << string(*token) << endl;
					// To get only the text contained by token:
					//cout << token->get_text().c_str() << endl;
				else if(tID == QUEX_TKN_NUMBER)
					cout << "NUMBER: " << string(*token) << endl;
				else
					cout << token->type_id_name() << endl;
				continue;

				switch(state) {
					case STATE_INST:
						switch(tID) {
							case QUEX_TKN_OP_ADD:
								cur_ins = new AddOp();
								break;
							case QUEX_TKN_OP_SUB:
								cur_ins = new SubOp();
								break;
							case QUEX_TKN_OP_MOVE:
								cur_ins = new MovOp();
								break;
							case QUEX_TKN_OP_MULTIPLY:
								cur_ins = new MulOp();
								break;
							case QUEX_TKN_OP_DIVIDE:
								cur_ins = new DivOp();
								break;
							default:
								cout << "AAAH INVALID STATE AHHHHH!" << endl;
								exit(0);
						}
						count = cur_ins->desiredArgs();
						state = STATE_ARG;
						break;

					case STATE_ARG:
						switch(tID) {
							case QUEX_TKN_IDENTIFIER:
							case QUEX_TKN_STRING:
								cur_ins->receiveArg((const char*)token->get_text().c_str());
								break;

							case QUEX_TKN_NUMBER:
								//out << token->get_number();
								//const string& tmp = out.str();
								//const char* cstr = tmp.c_str();
								cur_ins->receiveArg((const char*)
										    token->get_text().c_str());
								break;
							default:
								cout << "INVALID TOKEN JKLASJK" << endl;
								exit(0);
						}

						if(!--count)
							state = STATE_EOL;
						else
							state = STATE_COMMA;
						break;

					case STATE_COMMA:
						if(! (tID == QUEX_TKN_COMMA)) {
							cout << "AAAAAH INVALID STATE OMGOMMGOMG!" << endl;
							exit(0);
						}
						
						state = STATE_ARG;
						break;

					case STATE_EOL:
						if(! (tID == QUEX_TKN_EOL)) {
							cout << "AAH OMG WE WANT EOL!!!!" << endl;
							exit(0);
						}
						
						instructions.push_back(cur_ins);
						state = STATE_INST;
						break;

					default:
						break;
						
				}
			
			}
		}
};








int main(int argc, char** argv)
{
	quex::Token* token_p = 0x0;
	quex::lexer qlex("example.txt");
	vector<quex::Token*> tokens;
	do {
		qlex.receive(&token_p);
		cout << "Token received: " << token_p->type_id_name() << endl;
		tokens.push_back(token_p);
	} while( token_p->type_id() != QUEX_TKN_TERMINATION );

	Parser parser(tokens);
	parser.init();
	vector<Instruction*> inst = parser.getInst();
	cout << "Size of instruction vector: " << inst.size() << endl;
	for(int i=0; i < inst.size(); i++) {
		cout << inst[i]->getName() << endl;
	}
	return 0;
}

// STATE_INST	= Waiting for valid instruction.
// STATE_ARG	= Waiting for instruction
// STATE_COMMA	= Waiting for comma
// STATE_EOL	= Waiting for an end-of-line (\n)


/*
 *
 * add 5, $1
 *
 * Grammar of language(Sort of. This isn't valid CFG, just for
 * own reference.):
 *
 * Eol -> \n
 * Line ->
 * Line -> Comment Eol Line
 * Line -> Instruction Arg Eol
 * Instruction -> 'add'|'sub'|'mul'|'div'|'mov'
 * Arg -> Number|String|Id
 * Arg -> Number|String|Id Comma Arg
 * Arg ->
 * Comma -> ','
 * Number -> [0-9]+
 * Id -> [_a-zA-Z-]+
 * String -> \"([^\"\\\\]|\\\\.)*\"
 * Comment -> '#' *
 */
