#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Utils.h"

// define Grid parameters
int startHorizontal, endHorizontal;
int startVertical, endVertical;
int gridColumns, gridRows;

// check if file path is available
bool CheckFileExists(std::string path)
{
    // open the path to check whether the chosen file is available or not
    std::ifstream f;
    f.open(path);

    // when file is existing, close the file and return true
    if (f)
    {
        f.close();
        return true;
    }

    // otherwise, return false
    return false;
}

// get file path contains definition of objects
bool GetObjectsFilePath(std::string& filePath)
{
    // get file path
    std::cout << "Input objects file path: ";
    std::getline(std::cin, filePath);

    // check if file exists, if not -> return
    if (CheckFileExists(filePath))
        std::cout << "Objects file exists." << endl;
    else
    {
        std::cout << "Objects file does not exist." << endl;
        return false;
    }

    return true;
}

// get file path contains definition of grid
bool GetGridInfo(int &gridId, std::string &filePath)
{
    // get Grid ID
    std::cout << "Input grid ID to be used: ";
    std::cin >> gridId;

    // get Grid define file path
    std::cout << "Input grid define file path (Press . to use default): ";
    std::cin.ignore();
    std::getline(std::cin, filePath);

    // check if file exists, if not -> return
    if (CheckFileExists(filePath))
        std::cout << "Grid file exists." << endl;
    else
    {
        std::cout << "Grid file does not exist." << endl;
        return false;
    }

    return true;
}

// get grid parameters via grid file path
bool GetGridParams(int gridId, std::string gridFilePath)
{
    std::ifstream f(gridFilePath);
    
    while (!f.eof())
    {
        std::string line;
        getline(f, line);
        if (line == "" || line[0] == '#') continue;

        std::vector<std::string> tokens = split(line);
        // if grid id is found, continue getting parameters
        if (atoi(tokens[0].c_str()) == gridId)
        {
            startHorizontal = atoi(tokens[1].c_str());
            endHorizontal = atoi(tokens[2].c_str());
            startVertical = atoi(tokens[3].c_str());
            endVertical = atoi(tokens[4].c_str());
            gridRows = atoi(tokens[5].c_str());
            gridColumns = atoi(tokens[6].c_str());

            return true;
        }
    }
    // not found any valid grid id
    return false;
}

// get postition of object in the grid
bool GetCellPosition(float x, float y, int &cellRow, int &cellColumn)
{
    // calculate grid width and height
    int gridWidth = endHorizontal - startHorizontal;
    int gridHeight = endVertical - startVertical;
        
    // calculate cell width and height
    float cellWidth = (float)gridWidth / gridRows;
    float cellHeight = (float)gridHeight / gridColumns;

    // calculate cell contains object initially
    cellRow = (int)((y - startVertical) / cellHeight);
    cellColumn = (int)((x - startHorizontal) / cellWidth);
    
    // return true when cell is within grid
    if (cellRow < gridRows && cellColumn < gridColumns) return true;
    // object position is out of grid range
    return false;
}

// get new object parameters (with cell row and cell column in addition)
std::vector<std::string> GetNewObjectDefinition(std::string line)
{
    std::vector<std::string> tokens = split(line);
    
    // get object position
    float object_x = (float)atof(tokens[1].c_str());
    float object_y = (float)atof(tokens[2].c_str());

    // calculate cell that includes of object in grid
    int cellRow, cellColumn;
    GetCellPosition(object_x, object_y, cellRow, cellColumn);

    // insert cellRow and cellColumn to their proper positions in vector
    tokens.insert(tokens.begin() + 3, to_string(cellRow));
    tokens.insert(tokens.begin() + 4, to_string(cellColumn));

    return tokens;
}

// convert from vector of string into string (with spaces)
std::string VectorToString(std::vector<std::string> v)
{
    std::string result = "";
    for (std::string str : v)
    {
        // when str is not the first element, add space before it
        if (str != v[0]) result += "\t";
        // add value (str) to result
        result += str;
    }

    return result;
}

void ExportToOutputFile(std::string fileIn, std::string fileOut)
{
    // Open Input file
    std::ifstream fi;
    fi.open(fileIn);

    // Open Output file
    std::ofstream fo;
    fo.open(fileOut);
    
    while (!fi.eof())
    {
        // Get the next line
        std::string line;
        getline(fi, line);

        // Skip comment or empty line
        if (line == "" || line[0] == '#') continue;

        // Write into Output file with new definition
        fo << VectorToString(GetNewObjectDefinition(line)) << endl;
    }

    // Close input and output files
    fi.close();
    fo.close();
}

int main()
{
    int gridId;
    std::string inputObjectsFilePath, outputObjectsFilePath, gridFilePath;

    // get Grid Id and Grid file path
    while (!GetGridInfo(gridId, gridFilePath))
    {
        std::cout << "Please try again!" << endl;
    }

    // get grid parameters
    if (!GetGridParams(gridId, gridFilePath))
    {
        std::cout << "Could not load parameters, program has been exited!" << endl;
        return 0;
    }

    // get input objects file path
    while (!GetObjectsFilePath(inputObjectsFilePath))
    {
        std::cout << "Please try again!" << endl;
    }

    // get output objects file path
    while (!GetObjectsFilePath(outputObjectsFilePath))
    {
        std::cout << "Please try again!" << endl;
    }

    // Export new objects definition into output file
    ExportToOutputFile(inputObjectsFilePath, outputObjectsFilePath);

    return 0;
}