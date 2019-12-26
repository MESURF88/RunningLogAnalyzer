/**********************************************************************************
** Program name: Running Log Analyzer (Keyboard Input)
** Author: Kevin Hill
** Date:  12/25/2019
** Description: Main method file for the Running Log Analyzer to show 
** running stats throughout the years and see the trend as well as details for
** each run. The file analyzed is developed by the using regular expressions to
** parse the personal excel document and capture the mileage, date and details.
** Keyboard control options allow the user to choose move the cursor see statistics
** or to quit program. Credit to javidx9 for inspiration with the dynamic console
** window based off of https://youtu.be/xW8skO7MFYw. 
***********************************************************************************/
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
    stat_map += L"[WASD]*Keys*to*move*******";
    stat_map += L"[Y Key]*For*statistic*****";
    stat_map += L"[E Key]*Scroll*Right******";
    stat_map += L"[Q Key]*Scroll*Left*******";
    stat_map += L"[L Key]*To*Quit***********";
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

        //CURSOR MOVEMENT
        if (GetAsyncKeyState((unsigned short)'A') & 0x8000) {
            if (fCursorX > 0) {
                fCursorX -= .1f;
            }
            if (fCursorX <= 0.5) {//scroll left
                frame_init->view_left();
                fCursorX = 1;
            }
        }
        if (GetAsyncKeyState((unsigned short)'D') & 0x8000) {
            if (fCursorX < nMapWidth - 1) {
                fCursorX += .1f;
            }
            if (fCursorX >= 94) {//scroll right
                frame_init->view_right();
                fCursorX = 93;
            }
        }
        if (GetAsyncKeyState((unsigned short)'W') & 0x8000) {
            if (fCursorY > 0) fCursorY-=.1f;
        }
        if (GetAsyncKeyState((unsigned short)'S') & 0x8000) {
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
        //See statistics tool button [Y key]
        if (GetAsyncKeyState((unsigned short)'Y') & 0x8000) {
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
        //Quick move to right tool button [E key]
        if (GetAsyncKeyState((unsigned short)'E') & 0x8000) {
            frame_init->view_right();
            fCursorX = 93;
        }
        //Quick move to left tool button [Q key]
        if (GetAsyncKeyState((unsigned short)'Q') & 0x8000) {
            frame_init->view_left();
            fCursorX = 1;
        }
        //Leave screen tool button [L Key]
        if (GetAsyncKeyState((unsigned short)'L') & 0x8000) {
            run_game = 0;
        }

        // Display Frame
        screen[nScreenWidth * nScreenHeight - 1] = '\0';
        WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
    }
}
