/*******************************************************************************
** Program name: Running Log Analyzer (XBOX Input)
** Author: Kevin Hill
** Date:  12/25/2019
** Description: Main method file for the Running Log Analyzer to show 
** running stats throughout the years and see the trend as well as details for
** each run. The file analyzed is developed by the using regular expressions to
** parse the personal excel document and capture the mileage, date and details.
** Xbox control options allow the user to choose move the cursor see statistics
** or to quit program. Credit to javidx9 for inspiration with the dynamic console
** window based off of https://youtu.be/xW8skO7MFYw. 
********************************************************************************/
#include "CXBOXController.h"
#include "Frame_Viewer.h"
#include <utility>
#include <algorithm>
#include <stdio.h>
#include <Windows.h>
#include <iostream>

//global screen layout variables
int nScreenWidth = 120;			// Console Screen Size X (columns)
int nScreenHeight = 40;			// Console Screen Size Y (rows)
int nMapWidth = 95;				// Graph Dimensions
int nMapHeight = 24;
int nStatMapWidth = 26;			// Statistics Sidebar Dimensions
int nStatHeight = 22;

float fCursorX = 45.0f;			//  Cursor Start Position
float fCursorY = nMapHeight - 12.0f;

int main()
{
    //GAMEPAD INTIALIZATION
    GamePadXbox* pad = new GamePadXbox(GamePadIndex_One);
   
    int run_game = 1; //controls window
    int cursor_index = 0; //cursor position in window

    //SCREEN
    wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    //MAPS
    // Create Map of Game Graph
    std::wstring map;

    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    map += L"|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|.|";
    
    // Create Map of Statistics Sidebar
    std::wstring stat_map;

    stat_map += L"The*Running*Log*Analyzer**";
    stat_map += L"Created*by*Kevin*Hill*****";
    stat_map += L"**************************";
    stat_map += L"**************************";
    stat_map += L"**************************";
    stat_map += L"**************************";
    stat_map += L"**************************";
    stat_map += L"==========================";
    stat_map += L"Controls******************";
    stat_map += L"[<^>]*Dpad*to*move********";
    stat_map += L"[Y]*For*statistics********";
    stat_map += L"[RB]*Scroll*Right*********";
    stat_map += L"[LB]*Scroll*Left**********";
    stat_map += L"[BACK]*To*Quit************";
    stat_map += L"Statistics****************";
    stat_map += L"distance*[mi]*************";
    stat_map += L"--------------------------";
    stat_map += L"details*******************";
    stat_map += L"--------------------------";
    stat_map += L"date*[YYYY-MM-DD]*********";
    stat_map += L"-------------------------";
    stat_map += L"==========================";

    //INITIALIZATIONS
    Frame_Viewer* frame_init = new Frame_Viewer;
    frame_init->initialize();
    
    while (run_game)
    {
        //INITIALIZATIONS
        char date_ch[25];
        //initialize array of chars for date
        for (int i = 0; i < 25; i++) {
            date_ch[i] = '-';
        }
        char detail_ch[35];
        //initialize array of chars for details
        for (int i = 0; i < 35; i++) {
            detail_ch[i] = '-';
        }
        int miles_select = 0;
        char miles_ch[2];
        //initialize array of chars for mile
        for (int i = 0; i < 2; i++) {
            miles_ch[i] = '-';
        }
       
        if (pad->is_connected())
        {
            pad->update();

            //CURSOR MOVEMENT
            if (pad->State._buttons[GamePad_Button_DPAD_LEFT] == true) {
                if (fCursorX > 0) {
                    fCursorX -= .1f;
                }
                if (fCursorX <= 0.5) {//scroll left
                    frame_init->view_left();
                    fCursorX = 1;
                }
            }
            if (pad->State._buttons[GamePad_Button_DPAD_RIGHT] == true) {
                if (fCursorX < nMapWidth - 1) {
                    fCursorX += .1f;
                }
                if (fCursorX >= 94) {//scroll right
                    frame_init->view_right();
                    fCursorX = 93;
                }
            }
            if (pad->State._buttons[GamePad_Button_DPAD_UP] == true) {
                if (fCursorY > 0) fCursorY-=.1f;
            }
            if (pad->State._buttons[GamePad_Button_DPAD_DOWN] == true) {
                if (fCursorY < nMapHeight-1) fCursorY+=.1f;
            }

            //GRAPH UPDATES
            //Update the screen background and constant statistics sidebar parameters
            const int origin_y = 2;
            const int origin_x = 94;
            for (int x = 0; x < nScreenWidth; x++)
            {
                for (int y = 0; y < nScreenHeight; y++)
                {
                    if (y > origin_y && y <= (origin_y + nStatHeight) && x > origin_x && x < (origin_x + nStatMapWidth)) {
                        screen[y * nScreenWidth + x] = stat_map[(y-origin_y-1) * nStatMapWidth + (x-origin_x-1)];
                    }
                    else {
                        screen[y * nScreenWidth + x] = '*';
                    }
                }
            }

            //Update the graph with data
            int idx = 0;
            for (int y = 1; y < (nMapWidth); y += 2)
            {
                if (idx < frame_init->buffer.size()) {
                    for (int z = nMapHeight-1; z > 0; z--) {
                        if (z > (nMapHeight - 1 - frame_init->buffer.at(idx).miles)) {
                            map[z * nMapWidth + y] = '#';
                        }
                        else {
                            map[z * nMapWidth + y] = '.';
                        }   
                    }
                }
                idx++;
            }
          
            //Update the viewing window and header
            swprintf_s(screen, 40, L"X=%3.2f, Y=%3.2f Running Log Analyzer", fCursorX, (nMapHeight - fCursorY - 1));
            for (int nx = 0; nx < nMapWidth; nx++) {
                for (int ny = 0; ny < nMapHeight; ny++)
                {
                    screen[(ny + 1) * nScreenWidth + nx] = map[ny * nMapWidth + nx];
                }
            }
            //Place 'X' where current cursor position is
            screen[((int)fCursorY + 1) * nScreenWidth + (int)fCursorX] = 'X';

            //TOOL BUTTONS
            //See statistics tool button [Y]
            if (pad->State._buttons[GamePad_Button_Y] == true) {
                cursor_index = ((int)fCursorX - 1)/2;
                //right bounds condition
                if (cursor_index > frame_init->buffer.size()-1) {
                    cursor_index = frame_init->buffer.size() - 1;
                }
                //putting date in array of chars and showing in statistics sidebar
                for (int i = 0; i < frame_init->buffer.at(cursor_index).date.length(); i++) {
                    date_ch[i] = frame_init->buffer.at(cursor_index).date[i];
                }
                for (int i = 0; i < (nStatMapWidth-1); i++) {
                    screen[(23) * nScreenWidth + 95+i] = date_ch[i];
                }
                //putting details in array of chars and showing in statistics sidebar
               for (int i = 0; i < frame_init->buffer.at(cursor_index).details.length(); i++) {
                    detail_ch[i] = frame_init->buffer.at(cursor_index).details[i];
                }
                for (int i = 0; i < (nStatMapWidth-1); i++) {
                    screen[(21) * nScreenWidth + 95 + i] = detail_ch[i];
                }
                //putting miles in array of chars and showing in statistics sidebar
                miles_select = frame_init->buffer.at(cursor_index).miles;
                if (miles_select > 9) {
                    miles_ch[1] = miles_select%10 + '0';
                    miles_select /= 10;
                    miles_ch[0] = miles_select + '0';
                    for (int i = 0; i < 2; i++) {
                        screen[(19) * nScreenWidth + 95 + i] = miles_ch[i];
                    }
                }
                else {
                    miles_ch[0] = miles_select + '0';
                    screen[(19) * nScreenWidth + 95 + 0] = miles_ch[0];
                }
            }
            //Quick move to right tool button [RB]
            if (pad->State._buttons[GamePad_Button_RIGHT_SHOULDER] == true) {
                frame_init->view_right();
                fCursorX = 93;
            }
            //Quick move to left tool button [LB]
            if (pad->State._buttons[GamePad_Button_LEFT_SHOULDER] == true) {
                frame_init->view_left();
                fCursorX = 1;
            }
            //Exit screen tool button [BACK]
            if (pad->State._buttons[GamePad_Button_BACK] == true) {
                run_game = 0;
            }
        }
        // Display Frame
        screen[nScreenWidth * nScreenHeight - 1] = '\0';
        WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
    }
    delete pad;
}
