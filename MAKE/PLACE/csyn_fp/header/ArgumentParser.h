#pragma once
#include "global.h"

class ArgumentParser {
public:
    ArgumentParser(int &argc, char **argv) {
        for (int i = 1; i < argc; i++)
            this->tokens.push_back(std::string(argv[i]));
    }

    // Get Argument
    const std::string& getCmdOption(const std::string &option) const {
        std::vector<std::string>::const_iterator itr;
        itr = std::find(this->tokens.begin(), this->tokens.end(), option);
        if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
            return *itr;
        }
        static const std::string empty_string("");
        return empty_string;
    }

    // Check if the option exists
    bool cmdOptionExists(const std::string &option) const {
        return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
    }


private:
    std::vector <std::string> tokens;
};