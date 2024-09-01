#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

// Function prototypes for each game
void playGuessTheNumber();
void playTicTacToe();
void playRockPaperScissors();
void playSnakeGame();

void displayBoard(char board[3][3]);
int isMoveValid(char board[3][3], int row, int col);
int isGameOver(char board[3][3]);
int checkWinner(char board[3][3]);

// Snake game constants
#define WIDTH 20
#define HEIGHT 10

typedef struct {
    int x, y;
} Position;

Position head, fruit;
Position tail[100]; // Assuming a maximum length of 100 for the snake
int tailLength = 0;
int score = 0;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum Direction dir;

void setupSnake();
void drawSnake();
void inputSnake();
void logicSnake();


int main() {
    int choice;

    do {
        system("cls"); // Clear the console screen

        // Display the gaming menu
        printf("===== Welcome to the Gaming Zone! =====\n");
        printf("1. Guess the Number\n");
        printf("2. Tic-Tac-Toe\n");
        printf("3. Rock-Paper-Scissors\n");
        printf("4. Snake Game\n");
        printf("5. Exit\n");
        printf("=======================\n");
        printf("Have fun! XD\n");

        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                playGuessTheNumber();
                break;
            case 2:
                playTicTacToe();
                break;
            case 3:
                playRockPaperScissors();
                break;
            case 4:
                playSnakeGame();
                break;
            case 5:
                printf("Exiting the gaming menu. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }

        // Wait for a key press before clearing the screen
        printf("\nPress any key to continue...");
        getch();

    } while (choice != 4);

    return 0;
}

// Function to play Guess the Number
void playGuessTheNumber() {
    srand(time(NULL));
    int secretNumber = rand() % 100 + 1;
    int guess, attempts = 0;

    printf("\n===== Guess the Number =====\n");
    printf("I have selected a number between 1 to 100. I challenge you to guess it!\n");

    do {
        printf("Enter your guess: ");
        scanf("%d", &guess);

        attempts++;

        if (guess < secretNumber)
            printf("Too low! Try again.\n");
        else if (guess > secretNumber)
        {
            if (guess > 100)
                printf("Pay attention! The number must be between 1 to 100.\nTry again.\n");
            else
                printf("Too high! Try again.\n");
        }
        else
            printf("Congratulations! You guessed the number in %d attempts.\n", attempts);

    } while (guess != secretNumber);

    printf("===========================\n");
}

// Function to play Tic-Tac-Toe
void playTicTacToe() {
        char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int row, col;
    int currentPlayer = 1; // 1 for Player 1, 2 for Player 2 or Computer
    int gameMode; // 1 for Two Players, 2 for Against Computer
    int userScore = 0, computerScore = 0;

    printf("\n===== Tic-Tac-Toe =====\n");

    // Ask the user for the game mode
    printf("Choose the game mode:\n");
    printf("1. Two Players\n");
    printf("2. Against Computer\n");
    printf("Enter your choice (1-2): ");
    scanf("%d", &gameMode);

    do {
        displayBoard(board);

        if (currentPlayer == 1 || (currentPlayer == 2 && gameMode == 1)) {
            printf("Player %d's turn\n", currentPlayer);
            printf("Enter the row (1-3): ");
            scanf("%d", &row);
            printf("Enter the column (1-3): ");
            scanf("%d", &col);
        } else if (currentPlayer == 2 && gameMode == 2) {
            // Computer's turn
            row = rand() % 3 + 1;
            col = rand() % 3 + 1;
            printf("Computer's turn\n");
        }

        // Convert user input to 0-based index
        row--;
        col--;

        if (isMoveValid(board, row, col)) {
            board[row][col] = (currentPlayer == 1) ? 'X' : 'O';

            if (isGameOver(board)) {
                displayBoard(board);
                if (currentPlayer == 1 || (currentPlayer == 2 && gameMode == 1)) {
                    printf("Player %d wins!\n", currentPlayer);
                    userScore++;
                } else if (currentPlayer == 2 && gameMode == 2) {
                    printf("Computer wins!\n");
                    computerScore++;
                }
                break;
            } else if (checkWinner(board) == 0) {
                displayBoard(board);
                printf("It's a tie!\n");
                break;
            }

            // Switch to the next player
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        } else {
            printf("Invalid move! Please try again.\n");
        }

    } while (1);

    // Display final scores
    printf("Final Scores - You: %d, Computer: %d\n", userScore, computerScore);
    printf("Game over!\n");
    printf("==============================\n");
}

// Function to display the Tic-Tac-Toe board
void displayBoard(char board[3][3]) {
    printf("\n  1   2   3\n");
    printf(" -------------\n");

    for (int i = 0; i < 3; i++) {
        printf("%d", i + 1);
        for (int j = 0; j < 3; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
        printf(" -------------\n");
    }
}

// Function to check if a move is valid in Tic-Tac-Toe
int isMoveValid(char board[3][3], int row, int col) {
    return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ');
}

// Function to check if the Tic-Tac-Toe game is over
int isGameOver(char board[3][3]) {
    return (checkWinner(board) != -1 || checkWinner(board) == 0);
}

// Function to check the winner of Tic-Tac-Toe
int checkWinner(char board[3][3]) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return (board[i][0] == 'X') ? 1 : 2; // Player 1 or Player 2 wins
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return (board[0][i] == 'X') ? 1 : 2; // Player 1 or Player 2 wins
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return (board[0][0] == 'X') ? 1 : 2; // Player 1 or Player 2 wins
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return (board[0][2] == 'X') ? 1 : 2; // Player 1 or Player 2 wins

    // Check if the board is full (tie)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ')
                return -1; // Game is not over
        }
    }

    return 0; // It's a tie
    printf("=======================\n");
}

// Function to play Rock-Paper-Scissors
void playRockPaperScissors() {    
    // Your Rock-Paper-Scissors code goes here
    char choices[] = {'R', 'P', 'S'};
    int userScore = 0, computerScore = 0;
    char userChoice, computerChoice;

    printf("\n===== Rock-Paper-Scissors =====\n");

    do {
        // Display menu
        printf("1. Rock\n");
        printf("2. Paper\n");
        printf("3. Scissors\n");
        printf("4. Quit\n");

        printf("Enter your choice (1-4): ");
        scanf(" %c", &userChoice);

        if (userChoice == '4') {
            break; // Exit the game if the user chooses to quit
        }

        if (userChoice < '1' || userChoice > '4') {
            printf("Invalid choice. Please enter a number between 1 and 4.\n");
            continue;
        }

        // Map user's choice to 'R', 'P', or 'S'
        userChoice = choices[userChoice - '1'];

        // Generate a random choice for the computer
        computerChoice = choices[rand() % 3];

        // Display user and computer choices
        printf("You chose: %c\n", userChoice);
        printf("Computer chose: %c\n", computerChoice);

        // Determine the winner
        if (userChoice == computerChoice) {
            printf("It's a tie!\n");
        } else if ((userChoice == 'R' && computerChoice == 'S') ||
                   (userChoice == 'P' && computerChoice == 'R') ||
                   (userChoice == 'S' && computerChoice == 'P')) {
            printf("You win!\n");
            userScore++;
        } else {
            printf("Computer wins!\n");
            computerScore++;
        }

        // Display current scores
        printf("Score - You: %d, Computer: %d\n", userScore, computerScore);

    } while (1);

    // Display final scores
    printf("Final Scores - You: %d, Computer: %d\n", userScore, computerScore);
    printf("Game over!\n");
    printf("==============================\n");
    printf("==============================\n");
}
// Function to play Snake Game
void playSnakeGame() {
    setupSnake();

    while (1) {
        system("cls");
        drawSnake();
        inputSnake();
        logicSnake();

        // Introduce a delay to control the game speed
        Sleep(100);
    }
}

void setupSnake() {
    // Initialize snake head position
    head.x = WIDTH / 2;
    head.y = HEIGHT / 2;

    // Initialize fruit position
    fruit.x = rand() % WIDTH;
    fruit.y = rand() % HEIGHT;

    dir = STOP;
    score = 0;
}

void drawSnake() {
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("#");

            if (i == head.y && j == head.x)
                printf("O");
            else if (i == fruit.y && j == fruit.x)
                printf("F");
            else {
                int isTail = 0;
                for (int k = 0; k < tailLength; k++) {
                    if (tail[k].x == j && tail[k].y == i) {
                        printf("o");
                        isTail = 1;
                    }
                }

                if (!isTail)
                    printf(" ");
            }

            if (j == WIDTH - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    printf("Score: %d\n", score);
}

void inputSnake() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                exit(0);
        }
    }
}

void logicSnake() {
    Position prev = tail[0];
    Position prev2;
    tail[0] = head;

    for (int i = 1; i < tailLength; i++) {
        prev2 = tail[i];
        tail[i] = prev;
        prev = prev2;
    }

    switch (dir) {
        case LEFT:
            head.x--;
            break;
        case RIGHT:
            head.x++;
            break;
        case UP:
            head.y--;
            break;
        case DOWN:
            head.y++;
            break;
    }

    // Wrap snake around the screen edges
    if (head.x < 0)
        head.x = WIDTH - 1;
    else if (head.x >= WIDTH)
        head.x = 0;

    if (head.y < 0)
        head.y = HEIGHT - 1;
    else if (head.y >= HEIGHT)
        head.y = 0;

    // Check for collision with fruit
    if (head.x == fruit.x && head.y == fruit.y) {
        score++;
        tailLength++;
        fruit.x = rand() % WIDTH;
        fruit.y = rand() % HEIGHT;
    }

    // Check for collision with tail
    for (int i = 0; i < tailLength; i++) {
        if (tail[i].x == head.x && tail[i].y == head.y) {
            printf("\nGame Over! Your final score is: %d\n", score);
            exit(0);
        }
    }
}