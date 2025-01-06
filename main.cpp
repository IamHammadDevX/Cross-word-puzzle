#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>    // For sleep (blinking effect)
#include <chrono>    // For sleep duration
#include <sstream>   // For stringstream
#include <fstream>   // For file handling
#include <algorithm> // For transform
#include <ctime>     // For timer
#include <cstdlib>   // For rand() and srand()
#include <random>
using namespace std;

// Structure to store clue positions
struct CluePosition
{
    int row;
    int col;
    string number;
    string direction;
    string word;
};

struct Clue
{
    string number;
    string direction;
    int row;
    int col;
    string clueText;
    string answer;
    bool solved;
    string hint;       // Hint includes starting letter and length
    string difficulty; // Easy, Medium, Hard
};
const string USERS_FILE = "users.txt";
const string LEADERBOARD_FILE = "leaderboard.txt";

// Function to clear the screen (platform-independent)
void clearScreen()
{
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux/Mac
#endif
}
string colorCyan = "\033[1;36m";
string colorYellow = "\033[1;33m";
string colorMagenta = "\033[1;35m";
string colorGreen = "\033[1;32m";
string colorDONT = "\033[1;34m";
string resetColor = "\033[0m";
string colorRed = "\033[1;31m";
string colorBlue = "\033[1;34m";
string colorWhite = "\033[1;37m";
string colorBlack = "\033[1;30m";
string colorBrightCyan = "\033[1;96m";
string colorBrightGreen = "\033[1;92m";
string colorBrightYellow = "\033[1;93m";
string colorBrightMagenta = "\033[1;95m";
string colorBrightRed = "\033[1;91m";
string colorBrightBlue = "\033[1;94m";
string colorBrightWhite = "\033[1;97m";
string colorDimGray = "\033[2;37m"; // Dimmed gray
string textBold = "\033[1m";
string textDim = "\033[2m";
string textItalic = "\033[3m";
string textUnderline = "\033[4m";
string textBlink = "\033[5m";
string textInverse = "\033[7m"; // Swap foreground and background colors
string textHidden = "\033[8m";
string textStrikeThrough = "\033[9m";
string textReset = "\033[0m"; // Reset all styles

// Function to display the header with centered text and blinking effect
void displayHeader()
{
    clearScreen(); // Clear the screen for a fresh start

    string headerText1 = R"(
   _____                      _       _____           _       _ 
  / ____|                    | |     |  __ \         | |     | |
 | |      ___  _ __  ___   __| | ___ | |__) |_ _  ___| | __ _| |
 | |     / _ \| '_ \/ __| / _` |/ _ \|  ___/ _` |/ __| |/ _` | |
 | |____| (_) | | | \__ \| (_| | (_) | |  | (_| | (__| | (_| | |
  \_____|\___/|_| |_|___(_)__,_|\___/|_|   \__,_|\___|_|\__,_|_| 
    )";

    string headerText2 = R"(
  _______  _______  _______  _______  _______  _______  _______  _______ 
 |       ||       ||       ||       ||       ||       ||       ||       |
 |   _   ||   _   ||   _   ||   _   ||   _   ||   _   ||   _   ||   _   |
 |  |_|  ||  |_|  ||  |_|  ||  |_|  ||  |_|  ||  |_|  ||  |_|  ||  |_|  |
 |_______||_______||_______||_______||_______||_______||_______||_______|
 |               CROSSWORD PUZZLE - CHALLENGE YOUR MIND               |
 |   _   ||   _   ||   _   ||   _   ||   _   ||   _   ||   _   ||   _   |
 |  |_|  ||  |_|  ||  |_|  ||  |_|  ||  |_|  ||  |_|  ||  |_|  ||  |_|  |
 |_______||_______||_______||_______||_______||_______||_______||_______|
 |       ||       ||       ||       ||       ||       ||       ||       |
 |   _   ||   _   ||   _   ||   _   ||   _   ||   _   ||   _   ||   _   |
 |  |_|  ||  |_|  ||  |_|  ||  |_|  ||  |_|  ||  |_|  ||  |_|  ||  |_|  |
 |_______||_______||_______||_______||_______||_______||_______||_______|
    )";

    string projectTitle = "CROSSWORD PUZZLE PROJECT";
    string subtitle = "A Fun and Challenging Puzzle Experience";
    string developedBy = "Developed by Iconic Devs";
    string pressEnter = "Press Enter to Begin!";

    auto centerText = [](string text, int width = 80)
    {
        int padding = (width - text.length()) / 2;
        return string(max(padding, 0), ' ') + text;
    };

    // Randomly alternate headers (optional)
    string activeHeader = (rand() % 2 == 0) ? headerText1 : headerText2;

    // Display Header Content
    cout << colorCyan;
    stringstream ss(activeHeader);
    string line;
    while (getline(ss, line))
    {
        cout << centerText(line) << "\n";
    }
    cout << centerText("") << "\n";

    cout << colorYellow << centerText(projectTitle) << resetColor << "\n";
    cout << colorMagenta << centerText(subtitle) << resetColor << "\n";
    cout << colorCyan << centerText(developedBy) << resetColor << "\n";
    cout << centerText("") << "\n";

    // Blinking Press Enter Text
    bool blink = true;
    while (true)
    {
        if (blink)
        {
            cout << colorGreen << centerText(pressEnter) << resetColor << "\n";
        }
        else
        {
            cout << centerText("") << "\n";
        }

        blink = !blink;
        this_thread::sleep_for(chrono::milliseconds(500));

        if (cin.peek() == '\n')
        {
            cin.ignore();
            break;
        }
    }
}
// Function to display the game features
void displayGameFeatures()
{
    cout << colorDONT;
    cout
        << "\n=== GAME FEATURES ===\n";
    cout << "- Grid: A rectangular grid of black and white squares for solving clues.\n";
    cout << "- Clues: A set of clues leading to answers.\n";
    cout << "- Levels: Different levels of difficulty for all abilities.\n";
    cout << "- Hints: Use hint points for help, but they add time to the puzzle.\n";
    cout << "- Offline Mode: Play without an internet connection.\n";
    cout << "- Word Suggestions: Hints for tricky clues.\n";
    cout << "- Dark Mode: A dark theme for visual comfort.\n";
    cout << "- Multi-word Entry Hints: See if an answer has multiple words.\n";
    cout << "- Smart Step: Skip filled cells when navigating.\n";
    cout << "- Lock Completed Words: Keep correctly guessed letters locked.\n";
    cout << "- Incorrect Puzzle Assistance: Reminders for incorrect cells.\n";
    cout << "- Help: Reveal letters, words, or the entire puzzle.\n";
    cout << "- Show Errors: Highlight incorrect letters.\n";
    cout << "- Clear Errors: Remove incorrect letters easily.\n";
    cout << resetColor << endl;
}

string selectDifficulty()
{
    cout << "\n=== SELECT DIFFICULTY ===\n";
    cout << "1. Easy\n";
    cout << "2. Medium\n";
    cout << "3. Hard\n";
    cout << "Choose an option: ";

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        return "Easy";
    case 2:
        return "Medium";
    case 3:
        return "Hard";
    default:
        cout << "Invalid choice. Defaulting to Medium.\n";
        return "Medium";
    }
}
vector<Clue> getRandomClues(vector<Clue> &allClues, int count, const string &difficulty)
{
    // Filter clues by difficulty
    vector<Clue> filteredClues;
    for (const auto &clue : allClues)
    {
        if (clue.difficulty == difficulty)
        {
            filteredClues.push_back(clue);
        }
    }

    // Debug: Print the number of filtered clues
    cout << "Number of " << difficulty << " clues: " << filteredClues.size() << endl;

    if (filteredClues.size() < count)
    {
        cout << "Not enough " << difficulty << " clues available. Defaulting to all available clues.\n";
        count = filteredClues.size();
    }

    // Shuffle the filtered clues
    random_device rd;
    mt19937 g(rd());
    shuffle(filteredClues.begin(), filteredClues.end(), g);

    // Select the first 'count' clues
    vector<Clue> selectedClues(filteredClues.begin(), filteredClues.begin() + count);
    return selectedClues;
}

// grid initliazation
vector<vector<string>> initializeGrid(int rows, int cols, const vector<Clue> &clues)
{
    vector<vector<string>> grid(rows, vector<string>(cols, " ")); // Initialize with spaces
    srand(time(0));                                               // Seed for randomness

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // Check if this cell is part of any clue
            bool isClueCell = false;
            for (const auto &clue : clues)
            {
                if (clue.direction == "across" && i == clue.row && j >= clue.col && j < clue.col + clue.answer.size())
                {
                    isClueCell = true;
                    break;
                }
                if (clue.direction == "down" && j == clue.col && i >= clue.row && i < clue.row + clue.answer.size())
                {
                    isClueCell = true;
                    break;
                }
            }
            // Fill with space if not a clue cell
            if (!isClueCell)
            {
                grid[i][j] = " "; // Fill with space
            }
        }
    }

    return grid;
}

void displayGrid(const vector<vector<string>> &grid, const vector<Clue> &clues)
{
    cout << colorBrightCyan;
    cout << "\n=== CROSSWORD PUZZLE ===\n";
    cout << resetColor << endl;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            cout << "+---";
        }
        cout << "+\n";

        for (int j = 0; j < grid[0].size(); j++)
        {
            cout << "| ";
            // Check if the cell is part of a clue answer
            bool isClueCell = false;
            for (const auto &clue : clues)
            {
                if (clue.direction == "across" && i == clue.row && j >= clue.col && j < clue.col + clue.answer.size())
                {
                    isClueCell = true;
                    break;
                }
                if (clue.direction == "down" && j == clue.col && i >= clue.row && i < clue.row + clue.answer.size())
                {
                    isClueCell = true;
                    break;
                }
            }
            // Display clue answers in green and "X" in red
            if (isClueCell)
            {
                cout << colorBrightYellow << grid[i][j] << resetColor;
            }
            else if (grid[i][j] == "X")
            {
                cout << colorBrightWhite << grid[i][j] << resetColor;
            }
            else
            {
                cout << grid[i][j];
            }
            cout << " ";
        }
        cout << "|\n";
    }

    for (int j = 0; j < grid[0].size(); j++)
    {
        cout << "+---";
    }
    cout << "+\n";
}
// Function to load user credentials from a file
unordered_map<string, string> loadUserCredentials()
{
    unordered_map<string, string> users;
    ifstream file(USERS_FILE);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            size_t delimiter = line.find(' ');
            if (delimiter != string::npos)
            {
                string username = line.substr(0, delimiter);
                string password = line.substr(delimiter + 1);
                users[username] = password;
            }
        }
        file.close();
    }
    return users;
}

// Function to save user credentials to a file
void saveUserCredentials(const unordered_map<string, string> &users)
{
    ofstream file(USERS_FILE, ios::trunc); // Overwrite file
    if (file.is_open())
    {
        for (const auto &[username, password] : users)
        {
            file << username << " " << password << "\n";
        }
        file.close();
    }
}

// Function to handle user registration
void registerUser(unordered_map<string, string> &users)
{
    string username, password;
    cout << "\n=== REGISTER ===\n";
    cout << "Enter a username: ";
    cin >> username;

    if (users.find(username) != users.end())
    {
        cout << "Username already exists. Please try again.\n";
        return;
    }

    cout << "Enter a password: ";
    cin >> password;

    users[username] = password;
    saveUserCredentials(users);
    cout << colorYellow;
    cout << "Registration successful! You can now log in.\n";
    cout << resetColor << endl;
}

// Function to handle user login
bool loginUser(const unordered_map<string, string> &users)
{
    string username, password;
    cout << "\n=== LOGIN ===\n";
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    auto it = users.find(username);
    if (it != users.end() && it->second == password)
    {
        cout << colorCyan;
        cout << "Login successful! Welcome, " << username << "!\n";
        cout << resetColor << endl;
        return true;
    }

    cout << "Invalid username or password. Please try again.\n";
    return false;
}

// Function to check if a word can be placed in the grid
bool canPlaceWord(const vector<vector<string>> &grid, const string &word, int row, int col, const string &direction)
{
    if (direction == "across")
    {
        if (col + word.length() > grid[0].size())
            return false; // Check bounds
        for (int i = 0; i < word.length(); i++)
        {
            if (grid[row][col + i] != " " && grid[row][col + i] != string(1, word[i]))
                return false; // Conflict with existing letters
        }
    }
    else if (direction == "down")
    {
        if (row + word.length() > grid.size())
            return false; // Check bounds
        for (int i = 0; i < word.length(); i++)
        {
            if (grid[row + i][col] != " " && grid[row + i][col] != string(1, word[i]))
                return false; // Conflict with existing letters
        }
    }
    else
    {
        return false; // Invalid direction
    }
    return true;
}
// Function to place a word in the grid
void placeWord(vector<vector<string>> &grid, const string &word, int row, int col, const string &direction)
{
    if (direction == "across")
    {
        for (int i = 0; i < word.length(); i++)
        {
            grid[row][col + i] = string(1, word[i]);
        }
    }
    else if (direction == "down")
    {
        for (int i = 0; i < word.length(); i++)
        {
            grid[row + i][col] = string(1, word[i]);
        }
    }
}

// Function to save the leaderboard
void saveLeaderboard(const string &username, int score, int timeTaken)
{
    ofstream file(LEADERBOARD_FILE, ios::app);
    if (file.is_open())
    {
        file << username << " " << score << " " << timeTaken << "\n";
        file.close();
    }
}

void displayLeaderboard()
{
    cout << colorMagenta;
    ifstream file(LEADERBOARD_FILE);
    if (file.is_open())
    {
        cout << "\n=== LEADERBOARD ===\n";
        cout << "Username\tScore\tTime Taken (seconds)\n";
        string username;
        int score, timeTaken;
        while (file >> username >> score >> timeTaken)
        {
            cout << username << "\t\t" << score << "\t" << timeTaken << "\n";
        }
        file.close();
    }
    else
    {
        cout << "No leaderboard data found.\n";
    }
    cout << resetColor << endl;
}
bool isGridComplete(const vector<vector<string>> &grid, const vector<CluePosition> &cluePositions)
{
    for (const auto &clue : cluePositions)
    {
        string expectedWord = clue.word;
        string currentWord = "";

        if (clue.direction == "across")
        {
            for (int i = 0; i < expectedWord.length(); i++)
            {
                currentWord += grid[clue.row][clue.col + i];
            }
        }
        else // down
        {
            for (int i = 0; i < expectedWord.length(); i++)
            {
                currentWord += grid[clue.row + i][clue.col];
            }
        }

        if (currentWord != expectedWord)
        {
            return false;
        }
    }
    return true;
}
// Function to display victory animation
void displayVictoryMessage()
{
    // clearScreen();
    string colorGreen = "\033[1;32m";
    string resetColor = "\033[0m";

    cout << colorGreen;
    cout << R"(
   ____                            _         _ 
  / ___|___  _ __   __ _ _ __ __ _| |_ ___  | |
 | |   / _ \| '_ \ / _` | '__/ _` | __/ __| | |
 | |__| (_) | | | | (_| | | | (_| | |_\__ \ |_|
  \____\___/|_| |_|\__, |_|  \__,_|\__|___/ (_)
                   |___/                        
    )" << endl;

    cout << "\n🎉 Congratulations! You've completed the crossword puzzle! 🎉" << endl;
    cout << "Congrats Champ! You have won!" << endl; // Add this line
    cout << "You're a crossword master!" << endl;
    cout << resetColor << endl;

    this_thread::sleep_for(chrono::seconds(2));
}
void displayPenaltyMessage()
{
    // clearScreen();
    string colorRed = "\033[1;31m";
    string resetColor = "\033[0m";

    cout << colorRed;
    cout << R"(
   ____                      _       _ 
  / ___| __ _ _ __ ___   ___| | __ _| |
 | |  _ / _` | '_ ` _ \ / _ \ |/ _` | |
 | |_| | (_| | | | | | |  __/ | (_| |_|
  \____|\__,_|_| |_| |_|\___|_|\__,_(_)
    )" << endl;

    cout << "\n⚠️ You have exceeded the maximum number of wrong answers. Game over! ⚠️" << endl;
    cout << "Better luck next time!" << endl;
    cout << resetColor << endl;

    this_thread::sleep_for(chrono::seconds(2));
}
// Function to play the crossword puzzle
void playCrosswordPuzzle(const string &username)
{
    int rows = 15, cols = 15;        // Larger grid to accommodate more clues
    int wrongAnswerCount = 0;        // Counter for wrong answers
    const int MAX_WRONG_ANSWERS = 5; // Maximum allowed wrong answers
    const int TOTAL_TIME = 300;      // Total time in seconds (5 minutes)

    // Select difficulty level
    string difficulty = selectDifficulty();

    vector<Clue> clues = {
        // Easy clues
        {"1", "across", 0, 0, "Opposite of down", "UP", false, "Starts with 'U', 2 letters", "Easy"},
        {"2", "across", 0, 3, "A color of the sky", "BLUE", false, "Starts with 'B', 4 letters", "Easy"},
        {"3", "across", 0, 5, "A metal used in jewelry", "GOLD", false, "Starts with 'G', 4 letters", "Medium"},
        {"4", "across", 0, 7, "Opposite of cold", "HOT", false, "Starts with 'H', 3 letters", "Easy"},
        {"5", "across", 0, 9, "A yellow fruit", "BANANA", false, "Starts with 'B', 6 letters", "Medium"},
        {"6", "down", 2, 0, "Four-legged pet", "DOG", false, "Starts with 'D', 3 letters", "Easy"},
        {"7", "down", 4, 0, "A type of tree with acorns", "OAK", false, "Starts with 'O', 3 letters", "Medium"},
        {"8", "down", 6, 0, "A bird that cannot fly", "PENGUIN", false, "Starts with 'P', 8 letters", "Hard"},
        {"9", "down", 8, 0, "A precious stone that's red", "RUBY", false, "Starts with 'R', 4 letters", "Medium"},
        {"10", "down", 10, 0, "Popular programming language", "PYTHON", false, "Starts with 'P', 6 letters", "Hard"},
        {"11", "across", 1, 0, "A large body of water", "OCEAN", false, "Starts with 'O', 5 letters", "Easy"},
        {"12", "across", 1, 3, "Opposite of left", "RIGHT", false, "Starts with 'R', 5 letters", "Easy"},
        {"13", "across", 1, 5, "A planet in our solar system", "MARS", false, "Starts with 'M', 4 letters", "Medium"},
        {"14", "across", 1, 7, "A type of flower", "ROSE", false, "Starts with 'R', 4 letters", "Easy"},
        {"15", "across", 1, 9, "A musical instrument", "PIANO", false, "Starts with 'P', 5 letters", "Medium"},
        {"16", "down", 3, 0, "A type of vehicle", "CAR", false, "Starts with 'C', 3 letters", "Easy"},
        {"17", "down", 5, 0, "A type of fruit", "APPLE", false, "Starts with 'A', 5 letters", "Medium"},
        {"18", "down", 7, 0, "A type of bird", "EAGLE", false, "Starts with 'E', 5 letters", "Medium"},
        {"19", "down", 9, 0, "A type of fish", "SALMON", false, "Starts with 'S', 6 letters", "Hard"},
        {"20", "down", 11, 0, "A type of reptile", "SNAKE", false, "Starts with 'S', 5 letters", "Medium"},
        {"21", "across", 2, 0, "A type of sport", "SOCCER", false, "Starts with 'S', 6 letters", "Medium"},
        {"22", "across", 2, 3, "A type of animal", "TIGER", false, "Starts with 'T', 5 letters", "Easy"},
        {"23", "across", 2, 5, "A type of food", "PIZZA", false, "Starts with 'P', 5 letters", "Easy"},
        {"24", "across", 2, 7, "A type of drink", "COFFEE", false, "Starts with 'C', 6 letters", "Medium"},
        {"25", "across", 2, 9, "A type of tree", "MAPLE", false, "Starts with 'M', 5 letters", "Medium"},
        {"26", "down", 4, 0, "A type of insect", "BEE", false, "Starts with 'B', 3 letters", "Easy"},
        {"27", "down", 6, 0, "A type of mammal", "BEAR", false, "Starts with 'B', 4 letters", "Easy"},
        {"28", "down", 8, 0, "A type of reptile", "LIZARD", false, "Starts with 'L', 6 letters", "Medium"},
        {"29", "down", 10, 0, "A type of bird", "OWL", false, "Starts with 'O', 3 letters", "Easy"},
        {"30", "down", 12, 0, "A type of fish", "TUNA", false, "Starts with 'T', 4 letters", "Easy"},
        {"31", "across", 3, 0, "A type of vehicle", "TRUCK", false, "Starts with 'T', 5 letters", "Medium"},
        {"32", "across", 3, 3, "A type of fruit", "GRAPE", false, "Starts with 'G', 5 letters", "Easy"},
        {"33", "across", 3, 5, "A type of bird", "PARROT", false, "Starts with 'P', 6 letters", "Medium"},
        {"34", "across", 3, 7, "A type of fish", "SALMON", false, "Starts with 'S', 6 letters", "Hard"},
        {"35", "across", 3, 9, "A type of reptile", "CROCODILE", false, "Starts with 'C', 9 letters", "Hard"},
        {"36", "down", 5, 0, "A type of insect", "ANT", false, "Starts with 'A', 3 letters", "Easy"},
        {"37", "down", 7, 0, "A type of mammal", "DEER", false, "Starts with 'D', 4 letters", "Easy"},
        {"38", "down", 9, 0, "A type of reptile", "TURTLE", false, "Starts with 'T', 6 letters", "Medium"},
        {"39", "down", 11, 0, "A type of bird", "PENGUIN", false, "Starts with 'P', 8 letters", "Hard"},
        {"40", "down", 13, 0, "A type of fish", "SHARK", false, "Starts with 'S', 5 letters", "Medium"}};
    // Get 10 random clues based on difficulty
    vector<Clue> selectedClues = getRandomClues(clues, 10, difficulty);

    // Initialize the grid with spaces
    vector<vector<string>> grid = initializeGrid(rows, cols, selectedClues);

    // Place clues in random positions
    for (auto &clue : selectedClues)
    {
        int maxAttempts = 3;
        bool placed = false;
        while (!placed && maxAttempts--)
        {
            // Choose a random starting point
            int row = rand() % rows;
            int col = rand() % cols;
            // Check if the word can fit from this position
            if (canPlaceWord(grid, clue.answer, row, col, clue.direction))
            {
                clue.row = row;
                clue.col = col;
                placed = true;

                // Place the clue number at the starting cell
                grid[row][col] = clue.number;
            }
        }
        if (!placed)
        {
            // Remove the clue if it couldn't be placed
            clue.solved = true; // Mark it as solved to skip further processing
        }
    }

    // Start the timer
    auto startTime = chrono::steady_clock::now();

    while (true)
    {
        // Calculate remaining time
        auto currentTime = chrono::steady_clock::now();
        int elapsedTime = chrono::duration_cast<chrono::seconds>(currentTime - startTime).count();
        int remainingTime = TOTAL_TIME - elapsedTime;

        // Check if time is up
        if (remainingTime <= 0)
        {
            cout << colorBrightRed << "\nTime's up! Game over.\n"
                 << resetColor << endl;
            return; // End the game
        }

        // Display the grid with color-coded clue answers and "X"
        displayGrid(grid, selectedClues);

        // Display remaining time
        cout << colorBrightYellow << "\nTime remaining: " << remainingTime << " seconds\n"
             << resetColor;

        // Display remaining clues
        cout << colorGreen << "\n=== REMAINING CLUES ===\n";
        bool hasClues = false;
        for (const auto &clue : selectedClues)
        {
            if (!clue.solved)
            {
                hasClues = true;
                cout << clue.number << ". " << clue.clueText << "\n";
            }
        }
        if (!hasClues)
        {
            // All clues solved
            break;
        }

        // Display the number of wrong answers remaining
        cout << colorBrightRed << "\nWrong answers remaining: " << MAX_WRONG_ANSWERS - wrongAnswerCount << resetColor << "\n";

        // User input for action
        cout << "Enter the clue number to solve, or 'hint' for a hint: ";
        string input;
        cin >> input;

        if (input == "hint")
        {
            // User requests a hint
            cout << "Enter the clue number for which you want a hint: ";
            string clueNumber;
            cin >> clueNumber;

            // Find the corresponding clue
            auto it = find_if(selectedClues.begin(), selectedClues.end(),
                              [&clueNumber](const Clue &c)
                              { return c.number == clueNumber && !c.solved; });
            if (it != selectedClues.end())
            {
                cout << colorBrightCyan << "Hint for clue " << clueNumber << ": " << it->hint << resetColor << "\n";
            }
            else
            {
                cout << colorBrightRed << "Invalid clue number or already solved.\n"
                     << resetColor << endl;
            }
        }
        else
        {
            // User is solving a clue
            string clueNumber = input;
            string userAnswer;
            cout << "Enter your answer: ";
            cin >> userAnswer;
            transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(), ::toupper);
            cout << resetColor << endl;

            // Find the corresponding clue
            auto it = find_if(selectedClues.begin(), selectedClues.end(),
                              [&clueNumber](const Clue &c)
                              { return c.number == clueNumber && !c.solved; });
            if (it != selectedClues.end())
            {
                if (it->answer == userAnswer)
                {
                    cout << colorYellow << "Correct! The word has been placed on the grid.\n"
                         << resetColor << endl;
                    // Place the word in the grid
                    placeWord(grid, it->answer, it->row, it->col, it->direction);
                    it->solved = true;
                }
                else
                {
                    wrongAnswerCount++; // Increment wrong answer counter
                    cout << colorRed << "Incorrect answer. Try again.\n"
                         << resetColor << endl;

                    // Check if the user has exceeded the maximum wrong answers
                    if (wrongAnswerCount >= MAX_WRONG_ANSWERS)
                    {
                        displayPenaltyMessage(); // Display the penalty message
                        return;                  // End the game
                    }
                }
            }
            else
            {
                cout << colorBrightRed << "Invalid clue number or already solved.\n"
                     << resetColor << endl;
            }
        }

        // Check if all clues are solved
        bool allSolved = true;
        for (const auto &clue : selectedClues)
        {
            if (!clue.solved)
            {
                allSolved = false;
                break;
            }
        }
        if (allSolved)
        {
            // Fill remaining spaces with "X"
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    if (grid[i][j] == " ")
                    {
                        grid[i][j] = "X";
                    }
                }
            }

            // Display the final grid with color-coded clue answers and "X"
            displayGrid(grid, selectedClues);
            displayVictoryMessage();

            // Calculate final score based on time taken
            auto endTime = chrono::steady_clock::now();
            int timeTaken = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();
            int baseScore = 100;                                   // Base score for completing the puzzle
            int timeBonus = max(0, (TOTAL_TIME - timeTaken) / 10); // Bonus for finishing quickly
            int finalScore = baseScore + timeBonus;

            cout << colorBrightGreen << "Time taken: " << timeTaken << " seconds\n";
            cout << "Final score: " << finalScore << resetColor << "\n";

            // Save to leaderboard and display it
            saveLeaderboard(username, finalScore, timeTaken);
            displayLeaderboard();
            break;
        }
    }
}
int main()
{
    displayHeader();
    unordered_map<string, string> users = loadUserCredentials();
    bool loggedIn = false;
    string username;
    cout << colorBrightRed;
    while (true)
    {
        cout << "\n=== MAIN MENU ===\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Start Game\n";
        cout << "4. View Features\n";
        cout << "5. Exit\n";
        cout << "6. View Leaderboard\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            loggedIn = loginUser(users);
            if (loggedIn)
            {
                cout << "Enter your username: ";
                cin >> username;
            }
        }
        else if (choice == 2)
        {
            registerUser(users);
        }
        else if (choice == 3)
        {
            if (loggedIn)
            {
                playCrosswordPuzzle(username);
            }
            else
            {
                cout << "Please log in first to start the game.\n";
            }
        }
        else if (choice == 4)
        {
            displayGameFeatures();
        }
        else if (choice == 5)
        {
            cout << "Exiting the game. Goodbye!\n";
            break;
        }
        else if (choice == 6)
        {
            displayLeaderboard();
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
    }
    cout << resetColor << endl;
    return 0;
}