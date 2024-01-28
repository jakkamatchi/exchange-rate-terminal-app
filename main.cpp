#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "Util.h"
#include "Node.h"
#include "JSONFile.h"

int main(int argc, char** argv) {
	std::stringstream RawJSONFile;			
	char* URL = "https://open.er-api.com/v6/latest/USD";
	
	//Included in Util.h	
	RawJSONFile = RetrieveData(URL);			
	std::vector<std::string> TokenisedJSON = TokeniseJSON(RawJSONFile.str());

	JSONFile ParsedFile(TokenisedJSON);

	//Set BaseNode. Can access subnodes by [] operator.
	//Failure will segfault as nullptr returned in case of no match
	std::shared_ptr<Node> BaseNode = ParsedFile.PrimaryNode;
	BaseNode = (*BaseNode)["OBJECT_NODE_0"];
	BaseNode = (*BaseNode)["rates"];
	
	//Child nodes = all Currency data
	//CurrencyNodes[i] will = currency name, child[i][j]->GetData() will be value
	//against USD
	std::vector<std::shared_ptr<Node> > CurrencyNodes = BaseNode->ChildNodes;
	
	//Colour constants for style
	const std::string BOLD_ON = "\033[1m";	
	const std::string BOLD_OFF = "\033[21m";
	
	const std::string UNDERLINE_ON = "\033[4m";	
	const std::string UNDERLINE_OFF = "\033[24m";
	
	const std::string RESET_COLOUR = "\033[49m";	
	const std::string BLUE= "\033[48;5;27m";
	const std::string RED = "\033[48;5;162m";
	const std::string GREEN = "\033[48;5;64m";


	for(int i = 0; i < CurrencyNodes.size(); i++) {
		std::cout << "\033[48;5;" << i << "m"  << CurrencyNodes[i]->GetData() << " : " << CurrencyNodes[i]->ChildNodes[0]->GetData() << RESET_COLOUR << "\n";
	}
	
	return 0;
}

