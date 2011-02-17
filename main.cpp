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
		vector<string> args;

		bool validateToken(int ttype) {
			int realType = argTypes.at(args.size());
			return (realType == ttype);
		}

	public:
		virtual string getName() { }
		virtual int desiredArgs() { }
		vector<int> argTypes;

		void receiveArg(int tokenType, const char *s) {
			if(!validateToken(tokenType))
				cout << "Bad argument type!" << endl;
				exit(0);
			string n(s);
			args.push_back(n);
		}

		string binaryRep() {
			return "Hohoho";
		}
};

// Format:
// addi [register] [any]
class AddInPlaceOp: public Instruction {
	public:
		AddInPlaceOp() {
			argTypes.push_back(QUEX_TKN_IDENTIFIER);
			argTypes.push_back(-1);
		}

		string getName() { return "addi"; }
		int desiredArgs() { return 2; }
};

// Format:
// add [register] [any] [any]
class AddOp: public Instruction {
	public:
		AddOp() {
			argTypes.push_back(QUEX_TKN_IDENTIFIER);
			argTypes.push_back(-1);
			argTypes.push_back(-1);
		}

		string getName() { return "add"; }
		int desiredArgs() { return 3; }


};

class SubInPlaceOp: public Instruction {
	public:
		SubInPlaceOp() {
			argTypes.push_back(QUEX_TKN_IDENTIFIER);
			argTypes.push_back(-1);
		}

		string getName() { return "subi"; }
		int desiredArgs() { return 2; }
};

class SubOp: public Instruction {
	public:
		SubOp() {
			argTypes.push_back(QUEX_TKN_IDENTIFIER);
			argTypes.push_back(-1);
			argTypes.push_back(-1);
		}

		string getName() { return "sub"; }
		int desiredArgs() { return 3; }
};

class MulInPlaceOp: public Instruction {
	public:
		MulInPlaceOp() {
			argTypes.push_back(QUEX_TKN_IDENTIFIER);
			argTypes.push_back(-1);
		}

		string getName() { return "muli"; }
		int desiredArgs() { return 2; }
};

class MulOp: public Instruction {
	public:
		MulOp() {
			argTypes.push_back(QUEX_TKN_IDENTIFIER);
			argTypes.push_back(-1);
			argTypes.push_back(-1);
		}

		string getName() { return "mul"; }
		int desiredArgs() { return 3; }
};

class DivInPlaceOp: public Instruction {
	public:
		DivInPlaceOp() {
			argTypes.push_back(QUEX_TKN_IDENTIFIER);
			argTypes.push_back(-1);
		}

		string getName() { return "divi"; }
		int desiredArgs() { return 2; }
};

class DivOp: public Instruction {
	public:
		DivOp() {
			argTypes.push_back(QUEX_TKN_IDENTIFIER);
			argTypes.push_back(-1);
			argTypes.push_back(-1);
		}

		string getName() { return "div"; }
		int desiredArgs() { return 3; }
};

class AssignOp: public Instruction {
	public:
		AssignOp() {
			argTypes.push_back(QUEX_TKN_IDENTIFIER);
			argTypes.push_back(-1);
		}

		string getName() { return "assign"; }
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

			// size() - 1 to leave out the termination token at
			// the end of the file.
			for(int i=0; i < tokens.size()-1; i++) {
				quex::Token* token = tokens[i];
				int tID = token->type_id();
				cout << "Token: ";
				if(tID == QUEX_TKN_IDENTIFIER || tID == QUEX_TKN_STRING)
					cout << string(*token) << endl;
					// To get only the text contained by token:
					//cout << token->get_text().c_str() << endl;
				else if(tID == QUEX_TKN_NUMBER) {
					cout << string(*token) << endl; }
				else
					cout << token->type_id_name() << endl;
				
//				continue;

				switch(state) {
					case STATE_INST:
						switch(tID) {
							case QUEX_TKN_OP_ADD:
								cur_ins = new AddOp();
								break;
							case QUEX_TKN_OP_ADDI:
								cur_ins = new AddInPlaceOp();
								break;
							case QUEX_TKN_OP_SUB:
								cur_ins = new SubOp();
								break;
							case QUEX_TKN_OP_SUBI:
								cur_ins = new SubInPlaceOp();
								break;
							case QUEX_TKN_OP_ASSIGN:
								cur_ins = new AssignOp();
								break;
							case QUEX_TKN_OP_MULTIPLY:
								cur_ins = new MulOp();
								break;
							case QUEX_TKN_OP_MULTIPLYI:
								cur_ins = new MulInPlaceOp();
								break;
							case QUEX_TKN_OP_DIVIDE:
								cur_ins = new DivOp();
								break;
							case QUEX_TKN_OP_DIVIDEI:
								cur_ins = new DivInPlaceOp();
								break;
							default:
								printf("State_Inst: Bad instruction %i", tID);
								exit(0);
						}
						count = cur_ins->desiredArgs();
						state = STATE_ARG;
						break;

					case STATE_ARG:
						switch(tID) {
							case QUEX_TKN_IDENTIFIER:
							case QUEX_TKN_STRING:
								cur_ins->receiveArg(tID, (const char*)token->get_text().c_str());
								break;

							case QUEX_TKN_NUMBER:
								cur_ins->receiveArg(tID, (const char*)
										    token->get_text().c_str());
								break;
							default:
								cout << "State_Arg: Bad argument token type" << endl;
								exit(0);
						}

						if(!--count)
							state = STATE_EOL;
						else
							state = STATE_COMMA;
						break;

					case STATE_COMMA:
						if(! (tID == QUEX_TKN_COMMA)) {
							cout << "State_Comma: Expecting comma, received other token." << endl;
							exit(0);
						}
						
						state = STATE_ARG;
						break;

					case STATE_EOL:
						if(! (tID == QUEX_TKN_EOL)) {
							cout << "State_Eol: Expecting EOL, received token." << endl;
							exit(0);
						}
						
						instructions.push_back(cur_ins);
						char testbuffer [30];
						printf("Pushed new instruction. Size = %i\n", instructions.size());
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
		tokens.push_back(token_p);
	} while( token_p->type_id() != QUEX_TKN_TERMINATION );
	
	Parser parser(tokens);
	parser.init();
	vector<Instruction*> inst = parser.getInst();
	cout << "Size is " << inst.size() << endl;
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
