#include "Headerer.hpp"

Headerer::Headerer(bool render) : mRender(render)
{
}

bool Headerer::create(std::string const& header, std::string const& impl, std::string const& output)
{
    if (!init(header,impl,output)) return false;
    for (std::size_t i = 0; i < hLines.size(); i++)
    {
        if (isFunction(hLines[i]))
        {
            std::size_t cPos = 0;
            bool found = false;
            std::string iL = toImpl(hLines[i]);
            for (std::size_t j = 0; j < cLines.size(); j++)
            {
                if (iL == simplify(cLines[j]))
                {
                    cPos = j;
                    found = true;
                    break;
                }
            }
            if (found)
            {
                std::size_t spaceCounter = 0;
                while (hLines[i][spaceCounter] == ' ')
                    spaceCounter++;
                std::string spaces;
                for (std::size_t j = 0; j < spaceCounter; j++)
                {
                    spaces += " ";
                }
                addLine(hLines[i].erase(hLines[i].find(";"),1));
                if (cLines[cPos + 1].find("{") != std::string::npos)
                {
                    std::size_t bracesCount = 0;
                    do
                    {
                        cPos++;
                        for (std::size_t j = 0; j < cLines[cPos].size(); j++)
                        {
                            if (cLines[cPos][j] == '{')
                            {
                                bracesCount++;
                            }
                            if (cLines[cPos][j] == '}')
                            {
                                bracesCount--;
                            }
                        }
                        addLine(spaces + cLines[cPos]);
                    } while (bracesCount > 0);
                }
            }
            else
            {
                addLine(hLines[i]);
            }
        }
        else if (isNewScope(hLines[i]))
        {
            scopes.push_back(getScopename(hLines[i]));
            addLine(hLines[i]);
        }
        else if (isEndOfScope(hLines[i]))
        {
            scopes.pop_back();
            addLine(hLines[i]);
        }
        else
        {
            addLine(hLines[i]);
        }
    }
    return terminate(output);
}

bool Headerer::init(std::string const& header, std::string const& impl, std::string const& output)
{
    hName = getFilename(header);
    cName = getFilename(impl);
    oName = getFilename(output);

    std::string line;

    if (hFile.is_open())
        hFile.close();
    hFile.open(header);
    if (!hFile)
        return false;
    hLines.clear();
    while(std::getline(hFile,line))
        hLines.push_back(line);
    hFile.close();

    if (cFile.is_open())
        cFile.close();
    cFile.open(impl);
    if (!cFile)
        return false;
    cLines.clear();
    while(std::getline(cFile,line))
        cLines.push_back(line);
    cFile.close();

    oLines.clear();
    return true;
}

bool Headerer::terminate(std::string const& output)
{
    hLines.clear();
    cLines.clear();

    if (oFile.is_open())
        oFile.close();
    oFile.open(output);
    if (!oFile)
        return false;
    for (std::size_t i = 0; i < oLines.size(); i++)
    {
        oFile << oLines[i] << std::endl;
    }
    oFile.close();
    return true;
}

void Headerer::addLine(std::string const& line)
{
    oLines.push_back(line);
    if (mRender)
    {
        std::cout << line << std::endl;
    }
}

std::string Headerer::toImpl(std::string const& line)
{
    std::string l = line;

    // Remove spaces
    while (l.front() == ' ')
    {
        l.erase(0,1);
    }

    // TODO : Remove words like "virtual " "static " ...
    std::vector<std::string> keywords = {"virtual ", "static "};
    for (std::size_t i = 0; i < keywords.size(); i++)
    {
        std::size_t key = l.find(keywords[i]);
        if (key != std::string::npos)
        {
            l.erase(key,keywords[i].size());
        }
    }

    // TODO : handle function like : const Type& test(); --> Here the determined type will be "const"

    std::size_t space = l.find(" ");
    std::string b, e;
    if (space != std::string::npos)
    {
        b = l.substr(0, space + 1);
        e = l.substr(space + 1);
    }
    else
    {
        b = "";
        e = l;
    }
    std::string cap;
    for (std::size_t i = 0; i < scopes.size(); i++)
    {
        cap += scopes[i] + "::";
    }
    l = b + cap + e;

    // Remove the last ';'
    std::size_t v = l.find(";");
    if (v != std::string::npos)
    {
        l.erase(v,1);
    }

    return l;
}

std::string Headerer::simplify(std::string const& line)
{
    std::string l = line;
    while (l.front() == ' ')
    {
        l.erase(0,1);
    }
    return l;
}

std::string Headerer::getFilename(std::string const& filepath)
{
    return filepath.substr(filepath.find_last_of("/\\")+1);
}

std::string Headerer::getScopename(std::string const& line)
{
    if (line.find("class ") != std::string::npos)
    {
        return line.substr(line.find("class ") + std::string("class ").size());
    }
    else if (line.find("struct ") != std::string::npos)
    {
        return line.substr(line.find("struct ") + std::string("struct ").size());
    }
    return line;
}

bool Headerer::isFunction(std::string const& line)
{
    // TODO : Handle C++ Lambda
    return (line.find("(") != std::string::npos && line.find(")") != std::string::npos) ? true : false;
}

bool Headerer::isInclude(std::string const& line)
{
    return (line.find("#include ") != std::string::npos) ? true : false;
}

bool Headerer::isNewScope(std::string const& line)
{
    return (line.find("class") != std::string::npos || line.find("struct") != std::string::npos) ? true : false;
}

bool Headerer::isEndOfScope(std::string const& line)
{
    return (line.find("};") != std::string::npos) ? true : false;
}
