#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Directive {
    std::string name;
    std::string argument;
};

struct Block
{
    std::string name;
    std::vector<Directive> directives;
    std::vector<Block> blocks;
};


// Function to parse a directive line
Directive parseDirective(const std::string& line)
{
    Directive directive;
    
    size_t pos = line.find(' ');
    if (pos != std::string::npos) {
        directive.name = line.substr(0, pos);
        directive.argument = line.substr(pos + 1);
    } else {
        directive.name = line;
        directive.argument = "";
    }
    return directive;
}

// Function to parse a block
Block parseBlock(std::ifstream& configFile)
{
    Block block;
    std::string line;

    // Read the block's name (e.g., "server" or "location")
    std::getline(configFile, line);
    block.name = line;

    // Read lines inside the block until the closing brace is encountered
    while (std::getline(configFile, line) && line != "}")
    {
        // Check for directives or nested blocks
        if (line.find('{') == std::string::npos)
        {
            // Parse and add directive
            Directive directive = parseDirective(line);
            block.directives.push_back(directive);
        } else {
            // Parse and add nested block
            Block nestedBlock = parseBlock(configFile);
            block.blocks.push_back(nestedBlock);
        }
    }
    return block;
}

int main() 
{
    std::ifstream configFile("test.config"); // Replace with your configuration file name

    if (!configFile.is_open()) {
        std::cerr << "Error: Unable to open the configuration file." << std::endl;
        return 1;
    }

    // Parse the configuration file
    Block mainBlock = parseBlock(configFile);

    // Close the configuration file
    configFile.close();

    // Print the parsed configuration for demonstration
    std::cout << "Parsed Configuration:" << std::endl;
    std::cout << "Block Name: " << mainBlock.name << std::endl;

    for (const auto& directive : mainBlock.directives) {
        std::cout << "Directive: " << directive.name << " Argument: " << directive.argument << std::endl;
    }

    for (const auto& nestedBlock : mainBlock.blocks) {
        std::cout << "Nested Block Name: " << nestedBlock.name << std::endl;
        // Additional processing of nested blocks or directives can be done here
    }

    return 0;
}
