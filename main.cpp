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
using namespace std;

// File to store user credentials
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

// Function to display the header with centered text and blinking effect
void displayHeader()
{
    string colorCyan = "\033[1;36m";
    string colorYellow = "\033[1;33m";
    string colorMagenta = "\033[1;35m";
    string colorGreen = "\033[1;32m";
    string resetColor = "\033[0m";

    string headerText = R"(
   _____                      _       _____           _       _ 
  / ____|                    | |     |  __ \         | |     | |
 | |      ___  _ __  ___   __| | ___ | |__) |_ _  ___| | __ _| |
 | |     / _ \| '_ \/ __| / _` |/ _ \|  ___/ _` |/ __| |/ _` | |
 | |____| (_) | | | \__ \| (_| | (_) | |  | (_| | (__| | (_| | |
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

// Function to display the game description with features
void displayGameDescription()
{
    cout << "\n=== WELCOME TO THE CROSSWORD PUZZLE GAME ===\n";
    cout << "Features include:\n";
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
}

// Function to initialize the crossword grid
vector<vector<char>> initializeGrid(int rows, int cols)
{
    return vector<vector<char>>(rows, vector<char>(cols, '-'));
}

// Function to display the crossword grid
void displayGrid(const vector<vector<char>> &grid)
{
    cout << "\n=== CROSSWORD PUZZLE ===\n";
    for (const auto &row : grid)
    {
        for (char cell : row)
        {
            cout << cell << " ";
        }
        cout << "\n";
    }
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
    cout << "Registration successful! You can now log in.\n";
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
        cout << "Login successful! Welcome, " << username << "!\n";
        return true;
    }

    cout << "Invalid username or password. Please try again.\n";
    return false;
}

// Function to check if a word can be placed in the grid
bool canPlaceWord(const vector<vector<char>> &grid, const string &word, int row, int col, const string &direction)
{
    if (direction == "horizontal")
    {
        if (col + word.length() > grid[0].size())
            return false; // Check bounds
        for (int i = 0; i < word.length(); i++)
        {
            if (grid[row][col + i] != '-' && grid[row][col + i] != word[i])
            {
                return false; // Conflict with existing letters
            }
        }
    }
    else if (direction == "vertical")
    {
        if (row + word.length() > grid.size())
            return false; // Check bounds
        for (int i = 0; i < word.length(); i++)
        {
            if (grid[row + i][col] != '-' && grid[row + i][col] != word[i])
            {
                return false; // Conflict with existing letters
            }
        }
    }
    else
    {
        return false; // Invalid direction
    }
    return true;
}

// Function to place a word in the grid
void placeWord(vector<vector<char>> &grid, const string &word, int row, int col, const string &direction)
{
    if (direction == "horizontal")
    {
        for (int i = 0; i < word.length(); i++)
        {
            grid[row][col + i] = word[i];
        }
    }
    else if (direction == "vertical")
    {
        for (int i = 0; i < word.length(); i++)
        {
            grid[row + i][col] = word[i];
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

// Function to display the leaderboard
void displayLeaderboard()
{
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
}

// Function to play the crossword puzzle
void playCrosswordPuzzle(const string &username)
{
    int rows, cols;
    cout << "\nEnter the number of rows and columns for the grid (e.g., 10 10): ";
    cin >> rows >> cols;

    vector<vector<char>> grid = initializeGrid(rows, cols); // Initialize grid
    vector<string> clues = {"1. Opposite of down", "2. Four-legged pet", "3. A color of the sky"};
    vector<string> answers = {"UP", "DOG", "BLUE"};
    vector<bool> solved(answers.size(), false); // Track solved clues
    vector<int> attempts(answers.size(), 0);    // Track attempts per clue
    int score = 0;                              // User's score
    int hintPoints = 3;                         // Default hint points

    auto displayClues = [&]()
    {
        cout << "\n=== CLUES ===\n";
        for (size_t i = 0; i < clues.size(); i++)
        {
            cout << (i + 1) << ". " << clues[i];
            if (solved[i])
            {
                cout << " (Solved)";
            }
            cout << "\n";
        }
    };

    auto useHint = [&]()
    {
        if (hintPoints > 0)
        {
            cout << "You have " << hintPoints << " hint points remaining.\n";
            cout << "Enter the clue number to reveal its answer: ";
            int clueNumber;
            cin >> clueNumber;

            if (clueNumber > 0 && clueNumber <= static_cast<int>(answers.size()) && !solved[clueNumber - 1])
            {
                cout << "Hint: The answer to clue " << clueNumber << " is \"" << answers[clueNumber - 1] << "\".\n";
                hintPoints--;
            }
            else if (solved[clueNumber - 1])
            {
                cout << "This clue is already solved.\n";
            }
            else
            {
                cout << "Invalid clue number. Try again.\n";
            }
        }
        else
        {
            cout << "No hint points remaining!\n";
        }
    };

    // Start the timer
    auto startTime = chrono::steady_clock::now();

    while (true)
    {
        displayGrid(grid);
        displayClues();

        cout << "\n=== OPTIONS ===\n";
        cout << "1. Enter an Answer\n";
        cout << "2. Use a Hint\n";
        cout << "3. Exit to Main Menu\n";
        cout << "Choose an option: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter the clue number: ";
            int clueNumber;
            cin >> clueNumber;

            if (clueNumber > 0 && clueNumber <= static_cast<int>(answers.size()) && !solved[clueNumber - 1])
            {
                if (attempts[clueNumber - 1] >= 3)
                {
                    cout << "You have used all 3 attempts for this clue.\n";
                    continue;
                }

                cout << "Enter your answer: ";
                string userAnswer;
                cin >> userAnswer;

                // Convert to uppercase for consistency
                transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(), ::toupper);

                if (userAnswer == answers[clueNumber - 1])
                {
                    cout << "Correct! The word has been placed on the grid.\n";

                    // Place the word in the grid
                    int row = clueNumber - 1; // Place words in different rows for simplicity
                    int col = 0;
                    string direction = "horizontal";

                    if (canPlaceWord(grid, userAnswer, row, col, direction))
                    {
                        placeWord(grid, userAnswer, row, col, direction);
                        solved[clueNumber - 1] = true;
                        score += 10; // Award 10 points for each correct answer
                    }
                    else
                    {
                        cout << "Failed to place the word. Check boundaries or conflicts.\n";
                    }
                }
                else
                {
                    cout << "Incorrect answer. Try again.\n";
                    attempts[clueNumber - 1]++;
                }
            }
            else if (solved[clueNumber - 1])
            {
                cout << "This clue is already solved.\n";
            }
            else
            {
                cout << "Invalid clue number. Try again.\n";
            }
        }
        else if (choice == 2)
        {
            useHint();
        }
        else if (choice == 3)
        {
            cout << "Exiting to main menu...\n";
            break;
        }
        else
        {
            cout << "Invalid option. Please try again.\n";
        }

        // Check if all clues are solved
        if (all_of(solved.begin(), solved.end(), [](bool s)
                   { return s; }))
        {
            cout << "Congratulations! You've solved the crossword puzzle!\n";
            break;
        }
    }

    // Stop the timer
    auto endTime = chrono::steady_clock::now();
    int timeTaken = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();

    // Save the user's score and time to the leaderboard
    saveLeaderboard(username, score, timeTaken);

    // Display the leaderboard
    displayLeaderboard();
}

int main()
{
    displayHeader();
    displayGameDescription();
    unordered_map<string, string> users = loadUserCredentials();
    bool loggedIn = false;
    string username;

    while (true)
    {
        cout << "\n=== MAIN MENU ===\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Start Game\n";
        cout << "4. Exit\n";
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
            cout << "Exiting the game. Goodbye!\n";
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}