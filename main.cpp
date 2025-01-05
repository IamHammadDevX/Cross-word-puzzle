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
    cout << "\n=== GAME FEATURES ===\n";
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

// Function to initialize the crossword grid with numbers for clues
vector<vector<string>> initializeGrid(int rows, int cols)
{
    vector<vector<string>> grid(rows, vector<string>(cols, " "));
    return grid;
}

// Function to display the crossword grid with numbers for clues
void displayGrid(const vector<vector<string>> &grid)
{
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
bool canPlaceWord(vector<vector<string>> &grid, const string &word, int row, int col, const string &direction)
{
    if (direction == "across")
    {
        if (col + word.length() > grid[0].size())
            return false; // Check bounds
        for (int i = 0; i < word.length(); i++)
        {
            if (grid[row][col + i] != " " && grid[row][col + i] != string(1, word[i]))
            {
                return false; // Conflict with existing letters
            }
        }
    }
    else if (direction == "down")
    {
        if (row + word.length() > grid.size())
            return false; // Check bounds
        for (int i = 0; i < word.length(); i++)
        {
            if (grid[row + i][col] != " " && grid[row + i][col] != string(1, word[i]))
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
    int rows = 15, cols = 15; // Larger grid to accommodate more words
    vector<vector<string>> grid = initializeGrid(rows, cols);

    // Across Clues
    vector<pair<string, string>> acrossClues = {
        {"1. Opposite of down", "UP"},
        {"3. A color of the sky", "BLUE"},
        {"5. A metal used in jewelry", "GOLD"},
        {"7. Opposite of cold", "HOT"},
        {"9. The largest planet in the solar system", "JUPITER"},
        {"11. A yellow fruit", "BANANA"},
        {"13. A famous wizard from Harry Potter", "HARRY"},
        {"15. A common table utensil", "SPOON"},
        {"17. The fastest land animal", "CHEETAH"},
        {"19. Something you wear on your feet", "SHOES"},
        {"21. A room where you cook", "KITCHEN"},
        {"23. The first meal of the day", "BREAKFAST"},
        {"25. A large mammal that lives in the ocean", "WHALE"},
        {"27. A color of grass", "GREEN"},
        {"29. A geometric shape with four equal sides", "SQUARE"},
        {"31. A precious metal", "SILVER"},
        {"33. A game involving kings, queens, and knights", "CHESS"},
        {"35. An animal known for its quills", "PORCUPINE"},
        {"37. A day of the weekend", "SUNDAY"},
        {"39. A season when leaves fall", "AUTUMN"}};

    // Down Clues
    vector<pair<string, string>> downClues = {
        {"2. Four-legged pet", "DOG"},
        {"4. A type of tree with acorns", "OAK"},
        {"6. A bird that cannot fly", "PENGUIN"},
        {"8. A precious stone that's red", "RUBY"},
        {"10. Popular programming language", "PYTHON"},
        {"12. A vehicle with two wheels", "BIKE"},
        {"14. A sweet treat made of chocolate", "CANDY"},
        {"16. Opposite of left", "RIGHT"},
        {"18. A fruit that is often red and round", "APPLE"},
        {"20. A popular search engine", "GOOGLE"},
        {"22. A unit of distance in kilometers", "MILE"},
        {"24. A day of love in February", "VALENTINE"},
        {"26. A famous superhero with a bat symbol", "BATMAN"},
        {"28. A large body of saltwater", "OCEAN"},
        {"30. A tool used for cutting", "KNIFE"},
        {"32. A planet with rings", "SATURN"},
        {"34. The opposite of happy", "SAD"},
        {"36. A common farm animal that gives milk", "COW"},
        {"38. A shiny object found in a pirate's chest", "TREASURE"},
        {"40. A long yellow pasta", "SPAGHETTI"}};

    // Place numbers for clues in the grid
    grid[0][0] = "1";   // Across
    grid[0][2] = "3";   // Across
    grid[0][4] = "5";   // Across
    grid[0][6] = "7";   // Across
    grid[0][8] = "9";   // Across
    grid[0][10] = "11"; // Across
    grid[0][12] = "13"; // Across
    grid[2][0] = "2";   // Down
    grid[4][0] = "4";   // Down
    grid[6][0] = "6";   // Down
    grid[8][0] = "8";   // Down
    grid[10][0] = "10"; // Down
    grid[12][0] = "12"; // Down

    // Display the grid
    displayGrid(grid);

    // Display clues
    cout << "\n=== ACROSS CLUES ===\n";
    for (const auto &clue : acrossClues)
    {
        cout << clue.first << "\n";
    }

    cout << "\n=== DOWN CLUES ===\n";
    for (const auto &clue : downClues)
    {
        cout << clue.first << "\n";
    }

    // Start the timer
    auto startTime = chrono::steady_clock::now();

    while (true)
    {
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

            cout << "Enter the direction (across/down): ";
            string direction;
            cin >> direction;

            cout << "Enter your answer: ";
            string userAnswer;
            cin >> userAnswer;

            // Convert to uppercase for consistency
            transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(), ::toupper);

            // Check if the answer matches any clue
            bool correct = false;
            if (direction == "across")
            {
                for (const auto &clue : acrossClues)
                {
                    if (clue.first.find(to_string(clueNumber)) != string::npos && clue.second == userAnswer)
                    {
                        correct = true;
                        break;
                    }
                }
            }
            else if (direction == "down")
            {
                for (const auto &clue : downClues)
                {
                    if (clue.first.find(to_string(clueNumber)) != string::npos && clue.second == userAnswer)
                    {
                        correct = true;
                        break;
                    }
                }
            }

            if (correct)
            {
                cout << "Correct! The word has been placed on the grid.\n";

                // Place the word in the grid
                if (direction == "across")
                {
                    for (int i = 0; i < userAnswer.length(); i++)
                    {
                        grid[0][i] = string(1, userAnswer[i]);
                    }
                }
                else if (direction == "down")
                {
                    for (int i = 0; i < userAnswer.length(); i++)
                    {
                        grid[i][0] = string(1, userAnswer[i]);
                    }
                }

                displayGrid(grid);
            }
            else
            {
                cout << "Incorrect answer. Try again.\n";
            }
        }
        else if (choice == 2)
        {
            cout << "Hint feature not implemented yet.\n";
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
    }

    // Stop the timer
    auto endTime = chrono::steady_clock::now();
    int timeTaken = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();

    // Save the user's score and time to the leaderboard
    saveLeaderboard(username, 100, timeTaken); // Default score of 100 for now

    // Display the leaderboard
    displayLeaderboard();
}

int main()
{
    displayHeader();
    unordered_map<string, string> users = loadUserCredentials();
    bool loggedIn = false;
    string username;

    while (true)
    {
        cout << "\n=== MAIN MENU ===\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Start Game\n";
        cout << "4. View Features\n";
        cout << "5. Exit\n";
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
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}