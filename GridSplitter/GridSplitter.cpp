#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include "Utils.h"

#include "../mario-directx/GameObject.h"
#include "../mario-directx/Brick.h"
#include "../mario-directx/GroundBricks.h"
#include "../mario-directx/ColoredBlock.h"

// define Grid parameters
int startHorizontal, endHorizontal;
int startVertical, endVertical;
int gridColumns, gridRows;

// new object list (string)
std::vector<std::vector<std::string>> objectList;

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
    if (filePath == ".")
    {
        filePath = "..\\mario-directx\\Resources\\GRIDLIST.txt";
    }
    
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
    float cellWidth = (float)gridWidth / gridColumns;
    float cellHeight = (float)gridHeight / gridRows;

    // calculate cell contains object initially
    cellColumn = (int)((y - startVertical) / cellHeight);
    cellRow = (int)((x - startHorizontal) / cellWidth);
    
    //// return true when cell is within grid
    //if (cellRow < gridRows && cellColumn < gridColumns) return true;
    //// object position is out of grid range
    //return false;

    return true;
}

// get new object parameters (with cell row and cell column in addition)
void GetNewObjectDefinition(std::string line)
{
    std::vector<std::string> tokens = split(line);

    // Get object type, position and animation set
    int object_type = atoi(tokens[0].c_str());
    float x = (float)atof(tokens[1].c_str());
    float y = (float)atof(tokens[2].c_str());
    int ani_set = atoi(tokens[3].c_str());

    // Initialize cell row and column
    int grid_row = 0;
    int grid_column = 0;

    // Define object definition vector using for storing temporary definition
    std::vector<std::string> objectDefinition;

    // If current object is a brick
    if (object_type == OBJECT_TYPE_BRICK)
    {
        // Get number of rows and columns
        int numRows = atoi(tokens[4].c_str());
        int numColumns = atoi(tokens[5].c_str());

        // Create new object definition for each brick
        for (int i = 0; i < numRows; i++)
            for (int j = 0; j < numColumns; j++)
            {
                // Clear the list
                objectDefinition.clear();

                // Firstly, push object type into vector
                objectDefinition.push_back(to_string(object_type));

                // Calculate current brick's position
                float pos_x = x + BRICK_BBOX_WIDTH * j;
                float pos_y = y + BRICK_BBOX_HEIGHT * i;

                // Push object position into vector
                objectDefinition.push_back(to_string(pos_x));
                objectDefinition.push_back(to_string(pos_y));
                
                // Get cell row and column
                bool result = GetCellPosition(pos_x, pos_y, grid_row, grid_column);

                // If this object is contained in the grid, push grid position into vector
                if (result)
                {
                    objectDefinition.push_back(to_string(grid_row));
                    objectDefinition.push_back(to_string(grid_column));
                }
                else continue;  // Otherwise, continue the loop

                // Finally, push animation set id to vector
                objectDefinition.push_back(to_string(ani_set));

                // And add new definition to object list
                objectList.push_back(objectDefinition);
            }
    }
    else if (object_type == OBJECT_TYPE_COLORED_BLOCK)
    {
        // Get number of rows and columns
        int numRows = atoi(tokens[4].c_str());
        int numColumns = atoi(tokens[5].c_str());

        // Define object definition vector
        std::vector<std::string> objectDefinition;

        // Create new object definition for each cell
        for (int i = 0; i < numRows; i++)
            for (int j = 0; j < numColumns; j++)
            {
                // Clear the list
                objectDefinition.clear();

                // Firstly, push object type into vector
                objectDefinition.push_back(to_string(object_type));

                // Calculate current cell's position
                float pos_x = x + COLORED_BLOCK_CELL_WIDTH * j;
                float pos_y = y + COLORED_BLOCK_CELL_HEIGHT * i;

                // Push object position into vector
                objectDefinition.push_back(to_string(pos_x));
                objectDefinition.push_back(to_string(pos_y));

                // Get cell row and column
                bool result = GetCellPosition(pos_x, pos_y, grid_row, grid_column);

                // If this object is contained in the grid, push grid position into vector
                if (result)
                {
                    objectDefinition.push_back(to_string(grid_row));
                    objectDefinition.push_back(to_string(grid_column));
                }
                else continue;  // Otherwise, continue the loop

                // Next, push animation set id to vector
                objectDefinition.push_back(to_string(ani_set));

                // Store block cell position
                int block_cell_position;

                // Set block cell position in the block
                if (i == 0)
                {
                    if (j == 0)
                        block_cell_position = COLORED_BLOCK_TYPE_TOP_LEFT;
                    else if (j == numColumns - 1)
                        block_cell_position = COLORED_BLOCK_TYPE_TOP_RIGHT;
                    else
                        block_cell_position = COLORED_BLOCK_TYPE_TOP_MID;
                }
                else if (i == numRows - 1)
                {
                    if (j == 0)
                        block_cell_position = COLORED_BLOCK_TYPE_BOT_LEFT;
                    else if (j == numColumns - 1)
                        block_cell_position = COLORED_BLOCK_TYPE_BOT_RIGHT;
                    else
                        block_cell_position = COLORED_BLOCK_TYPE_BOT_MID;
                }
                else
                {
                    if (j == 0)
                        block_cell_position = COLORED_BLOCK_TYPE_MID_LEFT;
                    else if (j == numColumns - 1)
                        block_cell_position = COLORED_BLOCK_TYPE_MID_RIGHT;
                    else
                        block_cell_position = COLORED_BLOCK_TYPE_MID_MID;
                }

                // Continue pushing block cell position
                objectDefinition.push_back(to_string(block_cell_position));

                // Push object into object list
                objectList.push_back(objectDefinition);
            }
    }
    else if (object_type == OBJECT_TYPE_GROUNDBRICK)
    {
        // Get number of rows and columns
        int numRows = atoi(tokens[4].c_str());
        int numColumns = atoi(tokens[5].c_str());
        
        for (int i = 0; i < numRows; i++)
            for (int j = 0; j < numColumns; j++)
            {
                // Clear the list
                objectDefinition.clear();

                // Push object type into vector
                objectDefinition.push_back(to_string(object_type));

                // Calculate current cell's position
                float pos_x = x + BRICK_BBOX_WIDTH * j;
                float pos_y = y + BRICK_BBOX_HEIGHT * i;

                // Push object position into vector
                objectDefinition.push_back(to_string(pos_x));
                objectDefinition.push_back(to_string(pos_y));

                // Get cell row and column
                bool result = GetCellPosition(pos_x, pos_y, grid_row, grid_column);

                // If this object is contained in the grid, push grid position into vector
                if (result)
                {
                    objectDefinition.push_back(to_string(grid_row));
                    objectDefinition.push_back(to_string(grid_column));
                }
                else continue;  // Otherwise, continue the loop

                // Next, push animation set id to vector
                objectDefinition.push_back(to_string(ani_set));

                // Store block cell position
                int block_cell_position;

                // Set block cell position
                if (i == 0)
                {
                    if (j == 0)
                        block_cell_position = BRICK_POSITION_TOPLEFT;
                    else if (j == numColumns - 1)
                        block_cell_position = BRICK_POSITION_TOPRIGHT;
                    else
                        block_cell_position = BRICK_POSITION_TOPMID;
                }
                else if (i == numRows - 1)
                {
                    if (j == 0)
                        block_cell_position = BRICK_POSITION_BOTLEFT;
                    else if (j == numColumns - 1)
                        block_cell_position = BRICK_POSITION_BOTRIGHT;
                    else
                        block_cell_position = BRICK_POSITION_BOTMID;
                }

                // Continue pushing block cell position
                objectDefinition.push_back(to_string(block_cell_position));

                // Push object into object list
                objectList.push_back(objectDefinition);
            }
    }
    else
    {
        // Clear the list
        objectDefinition.clear();

        // Push object type into vector
        objectDefinition.push_back(to_string(object_type));

        // Push object position into vector
        objectDefinition.push_back(to_string(x));
        objectDefinition.push_back(to_string(y));

        // calculate cell that includes of object in grid
        bool result = GetCellPosition(x, y, grid_row, grid_column);

        // Push cell row and column into vector
        if (result)
        {
            objectDefinition.push_back(to_string(grid_row));
            objectDefinition.push_back(to_string(grid_column));
        }
        else return;

        // Push object animation set into vector
        objectDefinition.push_back(to_string(ani_set));

        // Push remaining properties into vector
        for (int i = 4; i < tokens.size(); i++)
            objectDefinition.push_back(tokens[i]);

        // Add new object definition to object list
        objectList.push_back(objectDefinition);

        // insert cellRow and cellColumn to their proper positions in vector
        /*tokens.insert(tokens.begin() + 3, to_string(grid_row));
        tokens.insert(tokens.begin() + 4, to_string(gird_column));*/
    }
}

// convert from vector of string into string (with spaces)
std::string VectorToString(std::vector<std::string> v)
{
    std::string result = "";
    for (int i = 0; i < v.size(); i++)
    {
        // when str is not the first element, add space before it
        if (i > 0) result += "\t";
        // add value (str) to result
        result += v[i];
    }

    return result;
}

// Import objects from input file
void ImportFromInputFile(std::string fileIn)
{
    // Open Input file
    std::ifstream fi;
    fi.open(fileIn);

    // Get new object definitions and store them inside object list
    while (!fi.eof())
    {
        // Get the next line
        std::string line;
        getline(fi, line);

        // Skip comment or empty line
        if (line == "" || line[0] == '#') continue;

        // Create object definition
        GetNewObjectDefinition(line);
    }

    // Close input file
    fi.close();
}

// Export object list to output file
void ExportToOutputFile(std::string fileOut)
{
    // Open Output file
    std::ofstream fo;
    fo.open(fileOut);

    for (auto objectDefinition : objectList)
    {
        fo << VectorToString(objectDefinition) << endl;
    }

    // Close output file
    fo.close();
}

void ExportToOutputFile(std::string fileIn, std::string fileOut)
{
    ImportFromInputFile(fileIn);
    ExportToOutputFile(fileOut);
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