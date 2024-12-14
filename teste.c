// #include <stdio.h>
// #include <unistd.h>

// #define RESET "\033[0m"
// #define RED "\033[31m"
// #define YELLOW "\033[33m"
// #define GREEN "\033[32m"
// #define CYAN "\033[36m"
// #define BLUE "\033[34m"
// #define MAGENTA "\033[35m"

// // Gradient color array
// const char *colors[] = {RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA};

// void gradientSpinner(int duration) {
//     char spinner[] = "|/-\\";
//     int spinnerIndex = 0;

//     printf("\nStarting up...\n");

//     for (int i = 0; i < 100; i++) {
//         printf("\r%s%c " RESET "Loading... %d%%", colors[i % 6], spinner[spinnerIndex], i + 1);

//         fflush(stdout);
//         spinnerIndex = (spinnerIndex + 1) % 4;
//         usleep(duration * 1000); // Adjust speed
//     }

//     printf("\nDone!\n");
// }

// int main() {
//     gradientSpinner(50); // 50 ms per frame
//     return 0;
// }

// ##############################################################

// #include <stdio.h>
// #include <unistd.h>

// void expandingBox(int duration) {
//     int size = 10;

//     printf("\nStarting Application...\n");

//     for (int step = 0; step < 20; step++) {
//         int width = (step % size) + 1;
//         int direction = (step / size) % 2; // 0 = expand, 1 = shrink

//         printf("\033[H\033[J"); // Clear screen
//         printf("Loading...\n");

//         for (int i = 0; i < size; i++) {
//             for (int j = 0; j < (direction ? size - width : width); j++) {
//                 printf("*");
//             }
//             printf("\n");
//         }

//         usleep(duration * 1000);
//     }

//     printf("\nDone!\n");
// }

// int main() {
//     expandingBox(100);
//     return 0;
// }


// ############################################################################

// #include <stdio.h>
// #include <math.h>
// #include <unistd.h>

// #define RESET "\033[0m"
// #define GREEN "\033[32m"

// void waveAnimation(int duration, int cycles) {
//     int width = 50; // Width of the wave
//     int height = 5; // Height of the wave

//     for (int t = 0; t < cycles; t++) {
//         printf("\033[H\033[J"); // Clear screen

//         for (int y = 0; y < height; y++) {
//             for (int x = 0; x < width; x++) {
//                 if ((int)(sin((x + t) * 0.2) * height / 2 + height / 2) == y) {
//                     printf(GREEN "*");
//                 } else {
//                     printf(" ");
//                 }
//             }
//             printf("\n");
//         }

//         usleep(duration * 1000);
//     }

//     printf(RESET "\nAnimation Complete!\n");
// }

// int main() {
//     waveAnimation(50, 100); // 50 ms per frame, 100 cycles
//     return 0;
// }

// #######################################################################

// #include <stdio.h>
// #include <unistd.h>

// #define RESET "\033[0m"
// #define GREEN "\033[32m"

// void progressWheel(int duration) {
//     char wheel[] = {'|', '/', '-', '\\'};
//     int stars = 0;

//     printf("\nLaunching Application...\n");

//     for (int i = 0; i < 100; i++) {
//         stars = i / 10; // Add stars gradually
//         printf("\r%c " GREEN, wheel[i % 4]);

//         for (int j = 0; j < stars; j++) {
//             printf("*");
//         }

//         printf(RESET " %d%%", i + 1);
//         fflush(stdout);
//         usleep(duration * 1000);
//     }

//     printf("\nComplete!\n");
// }

// int main() {
//     progressWheel(100);
//     return 0;
// }

// ############################################################################################

// #include <stdio.h>
// #include <unistd.h>
// #include <string.h>

// void typingEffect(const char *text, int speed) {
//     for (int i = 0; i < strlen(text); i++) {
//         printf("%c", text[i]);
//         fflush(stdout);
//         usleep(speed * 1000);
//     }
//     printf("\n");
// }

// int main() {
//     printf("\n");
//     typingEffect("Initializing system...\n", 50);
//     typingEffect("Loading modules...\n", 50);
//     typingEffect("Launching application...\n", 50);
//     printf("Done!\n");
//     return 0;
// }

// #########################################################################

// #include <stdio.h>
// #include <unistd.h>

// #define RESET "\033[0m"
// #define BLUE "\033[34m"
// #define WHITE "\033[97m"

// void starryWelcome() {
//     const char *stars[] = {
//         "            *         ",
//         "   *     *       *    ",
//         "*         WELCOME      *",
//         "      *     TO    *   ",
//         "   *  XYZ BANK MANAGEMENT SYSTEM *",
//         "     *        *        ",
//     };
//     int frames = sizeof(stars) / sizeof(stars[0]);

//     for (int i = 0; i < frames; i++) {
//         printf("\033[H\033[J"); // Clear screen
//         printf(BLUE "%s\n" RESET, stars[i]);
//         usleep(500000); // 500ms delay
//     }
// }

// int main() {
//     starryWelcome();
//     return 0;
// }

// ######################################################################################

// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>

// #define RESET "\033[0m"
// #define BLUE "\033[34m"
// #define CYAN "\033[36m"
// #define MAGENTA "\033[35m"
// #define GREEN "\033[32m"
// #define YELLOW "\033[33m"
// #define RED "\033[31m"
// #define WHITE "\033[97m"

// // Function to clear the screen
// void clearScreen() {
//     printf("\033[H\033[J");
// }

// // Gradient text with animation
// void printGradientText(const char *text) {
//     const char *colors[] = {RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA};
//     int colorCount = sizeof(colors) / sizeof(colors[0]);

//     for (int i = 0; text[i] != '\0'; i++) {
//         printf("%s%c" RESET, colors[i % colorCount], text[i]);
//         fflush(stdout);
//         usleep(30000); // Delay for typing effect
//     }
//     printf("\n");
// }

// // Animated progress bar with spinning icon
// void progressBar(int width, int delayMs) {
//     char spinner[] = "|/-\\";
//     int spinnerIndex = 0;

//     printf("\n");
//     for (int i = 0; i <= 100; i++) {
//         printf("\r[");
//         for (int j = 0; j < width; j++) {
//             if (j < (i * width) / 100) {
//                 printf(GREEN "=" RESET);
//             } else {
//                 printf(" ");
//             }
//         }
//         printf("] %d%% %c", i, spinner[spinnerIndex]);
//         fflush(stdout);

//         spinnerIndex = (spinnerIndex + 1) % 4;
//         usleep(delayMs * 1000); // Delay for progress
//     }
//     printf("\n");
// }

// // Dynamic ASCII logo animation
// void displayLogo() {
//     const char *logo[] = {
//         "    ██████╗ ██╗   ██╗███████╗    ",
//         "   ██╔═══██╗██║   ██║██╔════╝    ",
//         "   ██║   ██║██║   ██║███████╗    ",
//         "   ██║   ██║██║   ██║╚════██║    ",
//         "   ╚██████╔╝╚██████╔╝███████║    ",
//         "    ╚═════╝  ╚═════╝ ╚══════╝    ",
//     };

//     const char *colors[] = {RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA};
//     int colorCount = sizeof(colors) / sizeof(colors[0]);

//     for (int i = 0; i < sizeof(logo) / sizeof(logo[0]); i++) {
//         printf("%s%s\n" RESET, colors[i % colorCount], logo[i]);
//         usleep(200000); // Delay for line-by-line reveal
//     }
// }

// // Full animated startup sequence
// void startupAnimation() {
//     clearScreen();

//     // Step 1: Welcome Message
//     printf("\n");
//     printGradientText("WELCOME TO XYZ BANK MANAGEMENT SYSTEM");

//     // Step 2: Logo Reveal
//     displayLogo();

//     // Step 3: Progress Bar
//     printf("\nStarting system components...\n");
//     progressBar(30, 50);

//     // Step 4: Transition to Main Menu
//     clearScreen();
//     printf(GREEN "\nSystem is ready!" RESET "\n");
//     printf(CYAN "Accessing dashboard...\n" RESET);
//     usleep(1000000); // 1-second pause
// }

// int main() {
//     startupAnimation();
//     return 0;
// }

// ####################################################################################

// #include <stdio.h>
// #include <unistd.h> // For usleep

// #define RESET "\033[0m"
// #define GOLD "\033[38;5;220m"
// #define SILVER "\033[38;5;7m"
// #define BLUE "\033[38;5;25m"
// #define WHITE "\033[97m"

// // Function to clear the screen
// void clearScreen() {
//     printf("\033[H\033[J");
// }

// // Function for smooth typing animation
// void typeEffect(const char *text, int delayMs) {
//     for (int i = 0; text[i] != '\0'; i++) {
//         printf("%c", text[i]);
//         fflush(stdout);
//         usleep(delayMs * 1000);
//     }
// }

// // Progress bar with a glow effect
// void progressBar(int width, int delayMs) {
//     printf(SILVER "\nLoading: " RESET);
//     for (int i = 0; i <= width; i++) {
//         printf(GOLD "█" RESET);
//         fflush(stdout);
//         usleep(delayMs * 1000);
//     }
//     printf(WHITE " Done!\n" RESET);
// }

// // Elegant banner display
// void displayBanner() {
//     clearScreen();
//     printf(GOLD "**************************************************\n" RESET);
//     printf(GOLD "*                                                *\n" RESET);
//     printf(GOLD "*     " WHITE "WELCOME TO XYZ BANK MANAGEMENT SYSTEM" GOLD "     *\n" RESET);
//     printf(GOLD "*                                                *\n" RESET);
//     printf(GOLD "**************************************************\n" RESET);
// }

// // Logo with clean styling
// void displayLogo() {
//     const char *logo[] = {
//         " ███████╗██╗   ██╗███████╗",
//         " ██╔════╝██║   ██║██╔════╝",
//         " █████╗  ██║   ██║█████╗  ",
//         " ██╔══╝  ██║   ██║██╔══╝  ",
//         " ██║     ╚██████╔╝███████╗",
//         " ╚═╝      ╚═════╝ ╚══════╝",
//     };

//     printf("\n");
//     for (int i = 0; i < 6; i++) {
//         printf(BLUE "%s\n" RESET, logo[i]);
//         usleep(300000); // 300ms delay for each line
//     }
//     printf("\n");
// }

// // Full startup animation
// void startupAnimation() {
//     // Step 1: Display Banner
//     displayBanner();
//     usleep(1000000); // Pause for 1 second

//     // Step 2: Welcome Message with Typing Effect
//     typeEffect("\n" SILVER "Initializing system components...\n" RESET, 50);

//     // Step 3: Display Logo
//     displayLogo();

//     // Step 4: Progress Bar
//     progressBar(30, 80);

//     // Step 5: Final Message
//     typeEffect("\n" BLUE "System is now ready to use.\n" RESET, 50);
//     printf("\n" GOLD "Accessing main dashboard...\n" RESET);
//     usleep(1000000); // Pause for 1 second
// }

// int main() {
//     startupAnimation();
//     return 0;
// }

// #########################################################################################

// #include <stdio.h>
// #include <unistd.h>

// #define RESET "\033[0m"
// #define HIGHLIGHT "\033[1;33m"  // Yellow for highlights
// #define INFO "\033[1;36m"       // Cyan for informational text
// #define WHITE "\033[1;37m"      // Bright white for contrast
// #define PROGRESS "\033[1;32m"   // Green for the progress bar

// // Function to center text
// void centerText(const char *text, int width) {
//     int padding = (width - (int)strlen(text)) / 2;
//     for (int i = 0; i < padding; i++) {
//         printf(" ");
//     }
//     printf("%s\n", text);
// }

// // Progress bar animation
// void progressBarCentered(int totalWidth, int steps, int delayMs) {
//     char progressBar[totalWidth + 1];
//     for (int i = 0; i < totalWidth; i++) progressBar[i] = ' ';
//     progressBar[totalWidth] = '\0';

//     printf("\n");
//     for (int step = 0; step <= steps; step++) {
//         int progress = (step * totalWidth) / steps;
//         for (int i = 0; i < progress; i++) {
//             progressBar[i] = '=';
//         }
//         printf("\r");
//         centerText(PROGRESS "[" RESET "%s" PROGRESS "]" RESET, 80);
//         fflush(stdout);
//         usleep(delayMs * 1000);
//     }
//     printf("\n");
// }

// // Startup animation function
// void startupAnimation() {
//     int terminalWidth = 80; // Typical width for most terminals

//     // Step 1: Display a centered welcome message
//     printf("\n\n\n\n"); // Add blank lines for vertical centering
//     centerText(HIGHLIGHT "WELCOME TO XYZ BANK MANAGEMENT SYSTEM" RESET, terminalWidth);
//     usleep(1000000); // 1-second pause

//     // Step 2: Display centered "Loading..." message
//     centerText(INFO "Loading system components..." RESET, terminalWidth);
//     usleep(500000); // Half-second pause

//     // Step 3: Progress bar
//     progressBarCentered(50, 100, 30); // 50 characters wide, 100 steps, 30ms delay per step

//     // Step 4: Final centered "Ready" message
//     usleep(500000); // Half-second pause
//     centerText(HIGHLIGHT "System is now ready to use!" RESET, terminalWidth);
//     usleep(1000000); // 1-second pause
//     printf("\n\n"); // Add space after the animation
// }

// int main() {
//     startupAnimation();
//     return 0;
// }

//###################################################################

// #include <stdio.h>
// #include <windows.h>
// void gotoxy(int x, int y) {
//     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//     COORD pos;
//     pos.X = x;
//     pos.Y = y;
//     SetConsoleCursorPosition(hConsole, pos);
// }

// void smile(){
//     printf("erdtfyguij?\n");
//     printf("erdtfyguij?\n");
//     printf("erdtfyguij?\n");
//     printf("erdtfyguij?\n");
//     printf("erdtfyguij?\n");
//     printf("erdtfyguij?\n");
//     return;
// }



// Include the `gotoxy` implementation here.

// int main() {
//     printf("Enter your PIN: ****");
//     gotoxy(16, 2);
//     printf("1234");

//     printf("This is the default position.\n");
//     gotoxy(60, 5); // Move to (x=10, y=5)
//     smile();
//     printf("Now I'm here!\n");
    // gotoxy(60, 7); // Move to (x=10, y=5)
    // printf("Now I'm here!\n");
    // gotoxy(60, 9); // Move to (x=10, y=5)
    // printf("Now I'm here!\n");
    // gotoxy(60, 11); // Move to (x=10, y=5)
    // printf("Now I'm here!\n");
    // gotoxy(60, 13); // Move to (x=10, y=5)
    // printf("Now I'm here!\n");
    // gotoxy(60, 15); // Move to (x=10, y=5)
    // printf("Now I'm here!\n");
    // gotoxy(60, 17); // Move to (x=10, y=5)
    // printf("Now I'm here!\n");
    // gotoxy(60, 19); // Move to (x=10, y=5)
    // printf("Now I'm here!\n");
//     return 0;
// }


// #################################################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



// #include <stdio.h>
// #include <windows.h>
// void gotoxy(int x, int y) {
//     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//     COORD pos;
//     pos.X = x;
//     pos.Y = y;
//     SetConsoleCursorPosition(hConsole, pos);
// }

// COORD getCursorPosition() {
//     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//     CONSOLE_SCREEN_BUFFER_INFO csbi;
//     GetConsoleScreenBufferInfo(hConsole, &csbi);
//     return csbi.dwCursorPosition;
// }


// int main() {
//     // Print some output
//     printf("Now I'm here!\n");
//     printf("Now I'm here!\n");
//     printf("Now I'm here!\n");
//     printf("Now I'm here!\n");
//     printf("Now I'm here!\n");
//     printf("Enter your PIN: ****");
//     fflush(stdout); // Ensure the output is displayed immediately

//     // Get the current cursor position
//     int x, y;
//     COORD pos = getCursorPosition();
//     x = pos.X;
//     y = pos.Y;

//     // Move to the previous row at the appropriate column
//     gotoxy(x - 4, y-1); // `x - 4` adjusts to the start of "****" in the previous row
//     printf("1234");       // Overwrite the asterisks with the PIN

//     return 0;
// }


// ##########################################################################


// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h> // Pour usleep

// void clearScreen() {
//     #ifdef _WIN32
//         system("cls");
//     #else
//         system("clear");
//     #endif
// }

// void animateText(const char *text) {
//     int positions[] = {-5, -3, -1, 1, 3, 5, 3, 1, -1, -3, -5}; // Mouvement fluide gauche-droite
//     int count = sizeof(positions) / sizeof(positions[0]);

//     for (int repeat = 0; repeat < 5; repeat++) { // Répète l'animation 5 fois
//         for (int i = 0; i < count; i++) {
//             clearScreen();
            
//             // Insère des espaces pour déplacer le texte
//             for (int j = 0; j < abs(positions[i]); j++) {
//                 printf(" ");
//             }
//             printf("%s\n", text);

//             usleep(25000); // Pause de 25ms pour rendre l'animation rapide
//         }
//     }
// }

// int main() {
//     const char *message = "Password incorrect";
//     animateText(message);
//     return 0;
// }
