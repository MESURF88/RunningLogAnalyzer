/*******************************************************************************
** Program name: Running Log Analyzer (XBOX Input)
** Author: Kevin Hill
** Date:  12/25/2019
** Description: Class specification file for the Frame Viewer class.
********************************************************************************/
#ifndef FRAME_VIEWER_H
#define FRAME_VIEWER_H

#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <assert.h>

struct runLog
{
	int miles;
	std::string details;
	std::string date;
	//constructor
	runLog(const int x, const std::string y, const std::string z)
		: miles(x), details(y), date(z) {}
};

class Frame_Viewer
{
public:
	Frame_Viewer();
	~Frame_Viewer();

public:
	std::vector<runLog> buffer;
	void initialize();
	void view_left();
	void view_right();
	

private:
	std::vector<runLog> runs;
	int bookmark;
	int number_of_runs;
	const int max_buffer = 47;
};

#endif