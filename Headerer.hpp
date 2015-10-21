#ifndef HEADERER_HPP
#define HEADERER_HPP

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

class Headerer
{
    public:
        Headerer(bool render);

        bool create(std::string const& header, std::string const& impl, std::string const& output = "");

        bool init(std::string const& header, std::string const& impl, std::string const& output);
        bool terminate(std::string const& output);

        void addLine(std::string const& line);

        std::string toImpl(std::string const& line);
        std::string simplify(std::string const& line);

        std::string getFilename(std::string const& filepath);
        std::string getScopename(std::string const& line);

        bool isFunction(std::string const& line);
        bool isInclude(std::string const& line);
        bool isNewScope(std::string const& line);
        bool isEndOfScope(std::string const& line);

    private:
        bool mRender;

        std::string hName;
        std::string cName;
        std::string oName;

        std::vector<std::string> scopes;

        std::vector<std::string> hLines;
        std::vector<std::string> cLines;
        std::vector<std::string> oLines;

        std::ifstream hFile;
        std::ifstream cFile;
        std::ofstream oFile;
};

#endif // HEADERER_HPP
