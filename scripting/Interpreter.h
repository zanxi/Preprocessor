
#ifndef Interpreter_h
#define Interpreter_h

#include "Utils.h"

class Interpreter
{
public:
    
    static void init();
    static Variable process(const string& scriptData);

    static Variable processFor(ParsingScript& script);
    static Variable processIf(ParsingScript& script);
    static Variable processTry(ParsingScript& script);
    static Variable processWhile(ParsingScript& script);
  
private:
    static Variable processBlock(ParsingScript& script);
    static void skipBlock(ParsingScript& script);
    static void skipRestBlocks(ParsingScript& script);
  
    static void processArrayFor(ParsingScript& script, const string& forString);
    static void processCanonicalFor(ParsingScript& script, const string& forString);
  
    static void readConfig(const string& configFileName);
};

#endif /* Interpreter_h */
