#ifndef H_ASM
#define H_ASM

#include <string>
#include <vector>

using namespace std;

int analysisLine(string line);
int analysisCommand(string line,int &command);
int analysisOperation(vector<string> arrayLine);
string analysisComment(vector<string> arrayLine,string SymbolComment);

vector<string>stringSplit(string line);
#endif