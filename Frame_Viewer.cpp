/*******************************************************************************
** Program name: Running Log Analyzer (XBOX Input)
** Author: Kevin Hill
** Date:  12/25/2019
** Description: Implementation file for the Frame Viewer class to show
** the current viewing the running log graph on the screen and scrolling.
** puts captured the mileage, date and details into two vectors.
********************************************************************************/
#include "Frame_Viewer.h"

Frame_Viewer::Frame_Viewer()
{
    bookmark = 0;
    number_of_runs = 0;
}

Frame_Viewer::~Frame_Viewer()
{
    runs.clear();
    buffer.clear();
}

//Read data from file and put into vector of runLogs, runs and set size buffer of runLogs, buffer
void Frame_Viewer::initialize() {
    std::ifstream infile("test.txt");
    assert(infile); //error checking

    std::string line;
    std::string date_val;
    std::string detail_val;
    int count = 0;
    double mileage_db;
    int mileage;

    //get all of  the lines
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
       
        if (!(iss >> mileage_db))
        {// error checking for string stream
                break;
        } 
        iss >> mileage_db;
        mileage = (int)mileage_db;
        std::getline(infile, line);
        detail_val = line;
        std::getline(infile, line);
        date_val = line;

        //add captured values to vector
        runs.emplace_back(runLog(mileage, detail_val, date_val));
        //place current values in set size buffer
        if (count < max_buffer) {
            buffer.emplace_back(runLog(mileage, detail_val, date_val));
        }
        count++;
    }
    number_of_runs = count;
}

//Shift the view to the right
void Frame_Viewer::view_right() {
    if (!(bookmark+max_buffer >= number_of_runs)) {
        bookmark++;
        buffer.erase(buffer.begin());
        buffer.push_back(runs.at(bookmark+max_buffer-1));
    }
}

//Shift the view to the left
void Frame_Viewer::view_left() {
    if (!(bookmark <= 0)) {
        bookmark--;
        buffer.erase(buffer.end()-1);
        buffer.insert(buffer.begin(), runs.at(bookmark));
    }
}