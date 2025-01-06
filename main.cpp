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

struct Clue {
    string number;
    string direction;
    int row;
    int col;
    string clueText;
    string answer;
    bool solved;
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
// Function to display the header with centered text and blinking effect
void displayHeader()
{

    string headerText = R"(
   _____                      _       _____           _       _ 
  / ____|                    | |     |  __ \         | |     | |
 | |      ___  _ __  ___   __| | ___ | |__) |_ _  ___| | __ _| |
 | |     / _ \| '_ \/ __| / _` |/ _ \|  ___/ _` |/ __| |/ _` | |
 | |____| (_) | | | \__ \| (_, | (_) | |  | (_, | (__| | (_, | |
  \_____|\___/|_| |_|___(_)__,_|\___/|_|   \__,_|\___|_|\__,_|_| 
    )";

    string projectTitle = "CROSSWORD PUZZLE PROJECT";
    string subtitle = "A Fun and Challenging Puzzle Experience";
    string developedBy = "Developed by Iconic Devs";
    string pressEnter = "Press Enter to continue...";

    auto centerText = [](string text, int width = 80)
    {
        int padding = (width - text.length()) / 2;
        return string(max(padding, 0), ' ') + text;
    };

    cout << colorCyan;
    cout << centerText("") << "\n";

    stringstream ss(headerText);
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

// Function to initialize the crossword grid with numbers for clues
vector<vector<string>> initializeGrid(int rows, int cols)
{
    vector<vector<string>> grid(rows, vector<string>(cols, " "));
    return grid;
}

// Function to display the crossword grid with numbers for clues
void displayGrid(const vector<vector<string>> &grid)
{
    cout << colorYellow;
    cout << "\n=== CROSSWORD PUZZLE ===\n";
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            cout << "+---";
        }
        cout << "+\n";

        for (int j = 0; j < grid[0].size(); j++)
        {
            cout << "| " << grid[i][j] << " ";
        }
        cout << "|\n";
    }

    for (int j = 0; j < grid[0].size(); j++)
    {
        cout << "+---";
    }
    cout << "+\n";
    cout << resetColor << endl;
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
bool canPlaceWord(const vector<vector<string>> &grid, const string &word, int row, int col, const string &direction) {
    if (direction == "across") {
        if (col + word.length() > grid[0].size())
            return false; // Check bounds
        for (int i = 0; i < word.length(); i++) {
            if (grid[row][col + i] != " " && grid[row][col + i] != string(1, word[i]))
                return false; // Conflict with existing letters
        }
    } else if (direction == "down") {
        if (row + word.length() > grid.size())
            return false; // Check bounds
        for (int i = 0; i < word.length(); i++) {
            if (grid[row + i][col] != " " && grid[row + i][col] != string(1, word[i]))
                return false; // Conflict with existing letters
        }
    } else {
        return false; // Invalid direction
    }
    return true;
}
// Function to place a word in the grid
void placeWord(vector<vector<string>> &grid, const string &word, int row, int col, const string &direction) {
    if (direction == "across") {
        for (int i = 0; i < word.length(); i++) {
            grid[row][col + i] = string(1, word[i]);
        }
    } else if (direction == "down") {
        for (int i = 0; i < word.length(); i++) {
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
    clearScreen();
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

    this_thread::sleep_for(chrono::seconds(3));
}
// Function to play the crossword puzzle
void playCrosswordPuzzle(const string &username) {
    int rows = 10, cols = 10; // Smaller grid size
    vector<vector<string>> grid = initializeGrid(rows, cols);

    // Initialize clues
    vector<Clue> clues = {
        {"1", "across", 0, 0, "Opposite of down", "UP", false},
        {"3", "across", 0, 3, "A color of the sky", "BLUE", false},
        {"5", "across", 0, 5, "A metal used in jewelry", "GOLD", false},
        {"7", "across", 0, 7, "Opposite of cold", "HOT", false},
        {"9", "across", 0, 9, "A yellow fruit", "BANANA", false},
        {"2", "down", 2, 0, "Four-legged pet", "DOG", false},
        {"4", "down", 4, 0, "A type of tree with acorns", "OAK", false},
        {"6", "down", 6, 0, "A bird that cannot fly", "PENGUIN", false},
        {"8", "down", 8, 0, "A precious stone that's red", "RUBY", false},
        {"10", "down", 10, 0, "Popular programming language", "PYTHON", false}
    };

    // Place clue numbers in the grid
    for (size_t i = 0; i < clues.size(); ++i) {
        int maxAttempts = 100;
        bool placed = false;
        while (!placed && maxAttempts--) {
            int row = rand() % rows;
            int col = rand() % cols;
            if (canPlaceWord(grid, clues[i].answer, row, col, clues[i].direction)) {
                grid[row][col] = clues[i].number;
                clues[i].row = row;
                clues[i].col = col;
                placed = true;
            }
        }
        if (!placed) {
            // Handle the case where the clue couldn't be placed
            clues.erase(clues.begin() + i);
            i--;
        }
    }

    // Start the timer
    auto startTime = chrono::steady_clock::now();

    while (true) {
        // Display the grid
        displayGrid(grid);

        // Display remaining clues
        cout << colorGreen << "\n=== REMAINING CLUES ===\n" << resetColor << endl;
        bool hasClues = false;
        for (const auto &clue : clues) {
            if (!clue.solved) {
                hasClues = true;
                cout << clue.number << ". " << clue.clueText << "\n";
            }
        }
        if (!hasClues) {
            // All clues solved
            break;
        }

        // User input for answer
        string clueNumber, userAnswer;
        cout << "Enter the clue number: ";
        cin >> clueNumber;
        cout << "Enter your answer: ";
        cin >> userAnswer;
        transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(), ::toupper);

        // Find the corresponding clue
        auto it = find_if(clues.begin(), clues.end(),
                          [&clueNumber](const Clue &c) { return c.number == clueNumber && !c.solved; });
        if (it != clues.end()) {
            if (it->answer == userAnswer) {
                cout << colorYellow << "Correct! The word has been placed on the grid.\n" << resetColor << endl;
                // Place the word in the grid
                placeWord(grid, it->answer, it->row, it->col, it->direction);
                it->solved = true;
            } else {
                cout << "Incorrect answer. Try again.\n";
            }
        } else {
            cout << "Invalid clue number or already solved.\n";
        }

        // Check if all clues are solved
        bool allSolved = true;
        for (const auto &clue : clues) {
            if (!clue.solved) {
                allSolved = false;
                break;
            }
        }
        if (allSolved) {
            displayVictoryMessage();
            // Calculate final score based on time taken
            auto endTime = chrono::steady_clock::now();
            int timeTaken = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();
            int score = max(100 - timeTaken / 10, 10);
            // Save to leaderboard and display it
            saveLeaderboard(username, score, timeTaken);
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
    cout << colorDONT;
    while (true)
    {
        cout << "\n=== MAIN MENU ===\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Start Game\n";
        cout << "4. View Features\n";
        cout << "5. Exit\n";
        cout << "6. View Leaderboard\n"; // Added new option
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