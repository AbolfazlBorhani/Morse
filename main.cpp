// Created By: Abolfazl Borhani (WHI3PER)

// Email: abolfazlborhani80@gmail.com
// Github: https://www.github.com/AbolfazlBorhani
// Linkdin: https://www.linkedin.com/in/abolfazl-borhani-a79541321/
// Telegram Channel: @THE_WHI3PER_WORLD

#include <Windows.h>
#include <Lmcons.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>
#include <string>
#include <map>

namespace Morse {
    HANDLE hConsole{ GetStdHandle(STD_OUTPUT_HANDLE) };

    const std::string textStr{ "Text.txt" };
    const std::string encyStr{ "Encrypt.txt" };
    const std::string decyStr{ "Decrypt.txt" };

    std::map<char, std::string> LTM{{'a', "._"}, {'b', "_..."}, {'c', "_._."},
        {'d', "_.."}, {'e', "."}, {'f', ".._."}, {'g', "__."}, {'h', "...."},
        {'i', ".."}, {'J', ".___"}, {'k', "_._"}, {'l', "._.."}, {'m', "__"},
        {'n', "_."}, {'o', "___"}, {'p', ".__."}, {'q', "__._"}, {'r', "._."},
        {'s', "..."}, {'t', "_"}, {'u', ".._"}, {'v', "..._"}, {'w', ".__"},
        {'x', "_.._"}, {'y', "_.__"}, {'z', "__.."}, {'1', ".____"}, {'2', "..___"},
        {'3', "...__"}, {'4', "...._"}, {'5', "....."}, {'6', "_...."}, {'7', "__..."},
        {'8', "___.."}, {'9', "____."}, {'0', "_____"}, {' ', "|"}, {'\n', "*\n"}};

    std::map<std::string, char> MTL{{"._", 'a'}, {"_...", 'b'}, {"_._.", 'c'},
        {"_..", 'd'}, {".", 'e'}, {".._.", 'f'}, {"__.", 'g'}, {"....", 'h'},
        {"..", 'i'}, {".___", 'j'}, {"_._", 'k'}, {"._..", 'l'}, {"__", 'm'},
        {"_.", 'n'}, {"___", 'o'}, {".__.", 'p'}, {"__._", 'q'}, {"._.", 'r'},
        {"...", 's'}, {"_", 't'}, {".._", 'u'}, {"..._", 'v'}, {".__", 'w'},
        {"_.._", 'x'}, {"_.__", 'y'}, {"__..", 'z'}, {".____", '1'}, {"..___", '2'},
        {"...__", '3'}, {"...._", '4'}, {".....", '5'}, {"_....", '6'}, {"__...", '7'},
        {"___..", '8'}, {"____.", '9'}, {"_____", '0'}, {"|", ' '}, {"*", '\n'}};

    void setFontAndCmd() {
        HANDLE hConsole{ GetStdHandle(STD_OUTPUT_HANDLE) };
        CONSOLE_FONT_INFOEX fontInfo;
        fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
        GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
        fontInfo.dwFontSize.X = 24;
        fontInfo.dwFontSize.Y = 24;
        SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

        HWND console{ GetConsoleWindow() };
        RECT rect;
        GetWindowRect(console, &rect);
        MoveWindow(console, rect.left, rect.top, 430, 330, TRUE);
    }

    void Show(std::string phrese1, std::string phrese2) {
        TCHAR username[UNLEN + 1];
        DWORD username_len = UNLEN + 1;
        GetUserName(username, &username_len);

        /*
        if (GetUserName(username, &username_len))
            std::wcout << L"Username: " << username << std::endl;
        else
            std::cerr << "Error Code: " << GetLastError() << std::endl;
        */

        std::string layout1{"╔══════════════════════════════════╗\n║"};
        std::string layout2{"                                  "};
        std::string layout3{"║\n╚══════════════════════════════════╝\n\n"};
        int percent{ 1 };

        for (std::size_t i{ 0 }; i < layout2.length(); i += 3){
            system("cls");
            layout2.replace(i, 1, "█");

            SetConsoleTextAttribute(hConsole, 10);
            std::cout << layout1;
            SetConsoleTextAttribute(hConsole, 12);
            std::cout << layout2;
            SetConsoleTextAttribute(hConsole, 10);
            std::cout << layout3;

            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "$ username\t-> ";
            SetConsoleTextAttribute(hConsole, 13);
            std::wcout << username << std::endl;

            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "$ mainFile\t-> ";
            SetConsoleTextAttribute(hConsole, 10);
            std::cout << "successful\n";
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "$ encryptFile\t-> ";
            SetConsoleTextAttribute(hConsole, 10);
            std::cout << "successful\n";
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "$ decryptFile\t-> ";
            SetConsoleTextAttribute(hConsole, 10);
            std::cout << "successful\n\n";

            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "> {" << phrese1  << "}\t";
            SetConsoleTextAttribute(hConsole, 14);
            std::cout << "[R]\n";
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "> {" << phrese2  << "}\t";
            SetConsoleTextAttribute(hConsole, 14);
            std::cout << "[W]\n";
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "> (";
            SetConsoleTextAttribute(hConsole, 14);
            std::cout << percent << "%";
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << ')';

            percent += 3;
            Sleep(100);
        }
        Sleep(500);
    }

    void encrypt() {
        std::ifstream mainFile(textStr);
        std::ofstream encryptFile(encyStr, std::ios::trunc);

        if (!mainFile) {
            SetConsoleTextAttribute(hConsole, 15);
            std::cerr << "$ mainFile -> ";
            SetConsoleTextAttribute(hConsole, 12);
            std::cerr << "failed\n";
            SetConsoleTextAttribute(hConsole, 14);
            std::cout << "[Text.txt not exist]\n";
            SetConsoleTextAttribute(hConsole, 15);
            std::exit(0);
        }

        if (!encryptFile) {
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "$ encryptFile -> ";
            SetConsoleTextAttribute(hConsole, 12);
            std::cerr << "failed\n";
            std::exit(0);
        }

        char buffer{};

        mainFile.get(buffer);
        while (!mainFile.eof()) {
            encryptFile << LTM[std::tolower(buffer)] << ' ';
            mainFile.get(buffer);
        }

        mainFile.close();
        encryptFile.close();

        Sleep(1000);
        Show(textStr, encyStr);
        system("cls");
    }

    void decrypt() {
        SetConsoleTextAttribute(hConsole, 10);
        std::ifstream encryptFile(encyStr);
        std::ofstream decryptFile(decyStr, std::ios::trunc);

        if (!decryptFile) {
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "$ decryptFile -> ";
            SetConsoleTextAttribute(hConsole, 12);
            std::cerr << "failed\n";
            std::exit(0);
        }

        std::string buffer{};

        encryptFile >> buffer;
        while (!encryptFile.eof()) {
            decryptFile << MTL[buffer];
            encryptFile >> buffer;
        }

        encryptFile.close();
        decryptFile.close();

        SetConsoleTextAttribute(hConsole, 15);

        Sleep(1000);
        Show(encyStr, decyStr);
    }

    void runProgram() {
        system("chcp 65001");
        system("cls");

        setFontAndCmd();
        encrypt();
        decrypt();

        SetConsoleTextAttribute(hConsole, 15);
        std::cout << " -> ";
        SetConsoleTextAttribute(hConsole, 10);
        std::cout << "Finish";

        system("pause>0");
    }
}

int main() { Morse::runProgram(); }