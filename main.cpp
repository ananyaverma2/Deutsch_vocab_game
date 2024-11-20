#include "raylib.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <random>


// Struct to store a word and its meaning
struct Word {
    std::string german;
    std::string english;
};

// Struct to store a sentence with a placeholder for the word
struct Sentence {
    std::string sentence;
    std::string correctWord;
};

// Initialize game state
bool gameStarted = false;
int currentQuestion = 0;
int correctAnswers = 0;
bool answered = false;  // Flag to check if the question is answered
bool showCorrectAnswer = false;  // Flag to show the correct answer

// Define the words and sentences
std::vector<Word> words = {
    {"beeindruckend", "impressive"},
    {"weg", "way"},
    {"verwirklicht", "realized"},
    {"ziemlich", "really"},
    {"umziegen (zog)", "move"},
    {"großartiger", "great"},
    {"inspiriert", "inspiration"},
    {"Erfolge", "success"},
    {"Veränderung", "change"},
    {"geschafft", "managed"},
    {"fließend", "fluently"},
    {"trotzdem", "despite/inspite of"},
    {"sicherer", "safe"},
    {"leichter", "easier"},
    {"einzige", "only"},
    {"einsam", "lonely"},
    {"aufgegeben", "give up"},
    {"übte", "practice"},
    {"übung", "exercise"},
    {"hart arbeitet", "work hard"},
    {"schaffen (kann man alles schaffen)", "do anything"},
    {"aufhören", "to stop"},
    {"träumen", "dream"},
    {"absolut", "absolutely"},
    {"schwierigkeiten", "difficulty/difficult time"},
    {"anzupassen", "to adapt"},
    {"unsicher", "unsure"},
    {"hart gewesen", "been hard"},
    {"ehrgeizig", "ambitious"},
    {"Talent bemerkt", "noticed"},
    {"fleißig", "hardworking"},
    {"verdient", "earned"},
    {"gezeigt", "showed"},
    {"bereit", "ready"},
    {"Entscheidung", "decision"},
    {"mutig", "brave/courageous"},
    {"ausgewählt", "selected"},
    {"behalten", "keep"},
    {"tauschten", "traded"},
    {"entwickeln", "develop"},
    {"Erfahrung", "experience"},
    {"enttäuscht", "disappointed"},
    {"Stil", "style"},
    {"unschlagbar", "unbeatable"},
    {"hintereinander", "one after the other"},
    {"gestritten", "argued"},
    {"verließ", "left"},
    {"Leistung", "performance"},
    {"Entschlossenheit", "determination"},
    {"Legendär", "legendary"},
    {"Körper", "body"},
    {"aushalten", "endure"},
    {"begeistert", "thrilled"},
    {"Werke", "work"},
    {"sogar", "even"},
    {"Einfluss", "influence"},
    {"beweisen", "to prove"},
    {"schuben", "push/hit"},
    {"wehren", "defend"},
    {"ertragen", "bear"},
    {"bemerkt", "to notice"},
    {"böse", "evil"},
    {"peinlich", "awkward"},
    {"vertrauen", "trust"},
    {"kaum (kaum geld)", "very less"},
    {"überfordert", "overwhelmed"},
    {"Sorgen", "care for"},
    {"versuchte", "to make"},
    {"arm", "poor"},
    {"bemühte", "tried hard"},
    {"mut", "courage"},
    {"enttäuschen", "disappointed"},
    {"unterstützte", "supported"},
    {"ermutigte", "encouraged"},
    {"selbstvertrauen", "self-confidence"},
    {"stolz", "proud"},
    {"verletzte", "sad"},
    {"Beziehung", "relationship"},
    {"leidenschaft", "passion"},
    {"Hoffnung", "hopeful"},
    {"ausdrücken", "to express hope"},
    {"einzigartigen", "unique"},
    {"erlebnisse", "experiences"},
    {"herausforderungen", "challenges"},
    {"kritisierten", "criticised"},
    {"wütend", "angry"},
    {"ehrlich", "honest"},
    {"hervorgehen", "emerge"},
    {"zeigen", "show"},
    {"Verlust", "loss"},
    {"Erinnerungen", "memories"},
    {"Bühne", "stage"},
    {"jubeln", "cheer"},
    {"klatschen", "clap"},
    {"bereit", "ready"},
    {"Ziel", "goal"},
    {"kämpfen", "battle"},
    {"verdient", "earned"},
    {"Geduld", "patience"},
    {"scheitern", "fail"},
    {"entschlossen", "determined"},
    {"erreichen", "to reach"},
    {"Liedern", "songs"}
};

// Function to randomize options
void ShuffleOptions(std::vector<std::string>& options, const std::string& correctWord) {
    options.clear();  // Clear any existing options
    options.push_back(correctWord);  // Add the correct word to the options

    // Add two random words to the options list
    std::vector<std::string> randomWords;
    for (const auto& word : words) {
        if (word.english != correctWord) {
            randomWords.push_back(word.english);  // Add only non-matching words
        }
    }

    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(randomWords.begin(), randomWords.end(), rng);

    options.push_back(randomWords[0]);
    options.push_back(randomWords[1]);

    std::shuffle(options.begin(), options.end(), rng);  // Shuffle options
}

// Function to draw text with custom font
void DrawTextCenter(const char* text, int y, int fontSize, Color color, Font font) {
    int textWidth = MeasureTextEx(font, text, fontSize, 2).x;
    DrawTextEx(font, text, {(float)(GetScreenWidth() - textWidth) / 2, (float)y}, fontSize, 2, color);
}

// Function to shuffle the words for each session
void ShuffleWords(std::vector<Word>& wordList) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(wordList.begin(), wordList.end(), rng);
}

int main() {
    // Initialize Raylib
    InitWindow(800, 600, "German Word Game");
    SetTargetFPS(60);

    Font customFont = LoadFontEx("../resources/noto.ttf", 32, nullptr, 255);


    if (customFont.baseSize == 0) {
        std::cout << "Font failed to load!" << std::endl;
    }

    // Seed the random number generator
    std::srand(std::time(0));

    // Shuffle the words to randomize their order
    ShuffleWords(words);

    // Initialize options vector
    std::vector<std::string> options;

    // Game loop
    while (!WindowShouldClose()) {
        // Update
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !gameStarted) {
            Vector2 mousePos = GetMousePosition();
            if (mousePos.x >= 300 && mousePos.x <= 500 && mousePos.y >= 300 && mousePos.y <= 350) {
                gameStarted = true;  // Start the game
                currentQuestion = 0;  // Reset the current question
                answered = false;
                showCorrectAnswer = false;
                ShuffleOptions(options, words[currentQuestion].english);  // Shuffle options for first question
            }
        }

        if (gameStarted && !answered) {
            // Check for player answer
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePos = GetMousePosition();
                for (int i = 0; i < 3; i++) {
                    int yPos = 250 + i * 50;
                    if (mousePos.x >= 200 && mousePos.x <= 300 && mousePos.y >= yPos && mousePos.y <= yPos + 30) {
                        if (options[i] == words[currentQuestion].english) {
                            correctAnswers++;
                        } else {
                            showCorrectAnswer = true;  // Show the correct answer if the selected one is wrong
                        }
                        answered = true;  // Mark the question as answered
                    }
                }
            }
        }

        if (answered) {
            // Wait for space key to move to the next question
            if (IsKeyPressed(KEY_SPACE)) {
                currentQuestion++;
                if (currentQuestion < words.size()) {
                    ShuffleOptions(options, words[currentQuestion].english);  // Shuffle options for next question
                } else {
                    gameStarted = false;  // End the game after all questions
                }
                answered = false;
                showCorrectAnswer = false;
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!gameStarted) {
            // Display game instructions
            DrawTextCenter("German Word Game", 100, 60, DARKBLUE, customFont);
            DrawTextCenter("Click 'Start Game' to begin", 170, 30, BLACK, customFont);

            // Display the Start button
            DrawRectangle(300, 300, 200, 60, LIGHTGRAY);
            DrawTextCenter("Start Game", 310, 40, BLACK, customFont);
        } else {
            // Show German word with options to choose the English meaning
            DrawTextCenter("Choose the correct English meaning", 50, 40, DARKBLUE, customFont);
            DrawTextCenter(words[currentQuestion].german.c_str(), 150, 35, BLACK, customFont);

            // Display the options
            for (int i = 0; i < 3; i++) {
                int yPos = 250 + i * 50;
                DrawRectangle(200, yPos, 50, 30, LIGHTGRAY);
                DrawTextCenter(options[i].c_str(), yPos, 30, BLACK, customFont);
            }

            // If the question is answered, show feedback
            if (answered) {
                if (showCorrectAnswer) {
                    DrawTextCenter("Incorrect!", 420, 40, RED, customFont);
                    DrawTextCenter(("Answer: " + words[currentQuestion].english).c_str(), 450, 40, RED, customFont);
                } else {
                    DrawTextCenter("Correct!", 400, 40, GREEN, customFont);
                }
            }
        }

        EndDrawing();
    }

    // Unload font after use
    UnloadFont(customFont);

    // Close Raylib
    CloseWindow();
    return 0;
}