jar#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <string>

unsigned width = 1920;
unsigned height = 1080;
float p_Width = static_cast<float>(width);    //panel width
float p_Height = 200;                         //panel height

float fl_Height = static_cast<float>(height); //float scale
float char_Size = 40;


class Word {
private:
    std::string text;       //sfText setter
    bool show = false;      //show object
    bool user = true;       //flag for user input object
    bool isSkipped = false; //skipped check
    float bounds = 0;       //ge object bounds
    int cnt = 0;
    int miss = 0;

    int font = 1;           // }
    int speed = 1;          // } mods
    int spawn = 1;          // }

public:
    sf::Text sfText;        //showing word

    Word(const std::string& text, const sf::Color color, const sf::Font& font, bool isSkipped) : text(text), sfText(font, text, 30), isSkipped(isSkipped) {
        sfText.setFillColor(color);
        bounds = sfText.getLocalBounds().size.x;
        sfText.setPosition({-bounds, static_cast<float>(rand() % 800)});
    } //words

    Word(const std::string& text, const sf::Color color, const sf::Font& font) : text(text), sfText(font, text, 30) {
        sfText.setFillColor(color);
    } //common objects

    Word(const std::string& text, const sf::Color color, const sf::Font& font, bool input, bool isUser) : text(text), sfText(font, text, char_Size) {
        sfText.setFillColor(color);
        sfText.setPosition({110, (fl_Height - p_Height) + p_Height / 2 - char_Size});
    } //user input object

    Word(const std::string& text, const sf::Color color, const sf::Font& font, int cnt) : text(text), sfText(font, text, 30) {
        sfText.setFillColor(color);
    } //counters



    auto getText() const -> std::string {
        return this->text;
    }

    auto getCount() const -> int {
        return this->cnt;
    }

    auto getMissCount() const -> int {
        return miss;
    }

    auto getShow() const -> bool {
        return this->show;
    }

    auto setShow(const bool sh) -> void {
        this->show = sh;
    }

    auto getSpeed() const -> int {
        return this->speed;
    }

    auto setSpeed(const int sp) -> void {
        this->speed = sp;
    }

    auto getSkipped() const -> bool {
        return this->isSkipped;
    }

    auto setSkipped(const bool sk) -> void {
        this->isSkipped = sk;
    }



    auto charAppend(const char ch) -> void {
        if (ch == ' ' || ch == '\n' || ch == '\r' || ch == '1' || ch == '2' || ch == '3' || ch == '\x1B') {
            return;
        }
        text += ch;
        sfText.setString(text);
    }

    auto nullify() -> void {
        sfText.setString("");
        text.clear();
    }

    auto getPosition() const -> unsigned {
        const uint32_t pos = static_cast<uint32_t>(sfText.getPosition().x);
        return pos;
    }

    auto cntPlus() -> void {
        cnt++;
        sfText.setString(std::to_string(cnt));
        std::cout << "Written: " << cnt << std::endl;
    }

    auto cntSkip() -> void {
        miss++;
        sfText.setString(std::to_string(miss));
        std::cout << "Missed: " << miss << std::endl;
    }



    auto fontChange() -> void {
        if (font >= 3) font = 0;
        font++;
        sfText.setString(std::to_string(font));
        std::cout << "LOG: [Font changed to: " << font << ']' << std::endl;
    }

    auto speedChange() -> void {
        if (speed >= 3) speed = 0;
        speed++;
        sfText.setString(std::string(std::to_string(speed)));
        std::cout << "LOG: [Speed changed to: " << speed << ']' << std::endl;
    }

    auto spawnChange() -> void {
        if (spawn >= 3) spawn = 0;
        spawn++;
        sfText.setString(std::string(std::to_string(spawn)));
        std::cout << "LOG: [Spawn changed to: " << spawn << '\n' << std::endl;
    }

    auto move() -> void {
        auto pos = sfText.getPosition();
        sfText.setPosition({pos.x + static_cast<float>(speed), pos.y});
    }

    auto drawTo(sf::RenderWindow& window) const -> void {
        window.draw(sfText);
    }
};

class Panel {
private:
    sf::RectangleShape back;
    Word userInput;
    Word counter;
    Word skip;
    Word fontPanel;
    Word speedPanel;
    Word spawnPanel;
public:

    Panel(const sf::RectangleShape& background, const Word &uInput, const Word &count, const Word &skipped, const Word &fPanel, const Word &spePanel, const Word &spaPanel)
    : back(background), userInput(uInput), counter(count), skip(skipped), fontPanel(fPanel), speedPanel(spePanel), spawnPanel(spaPanel) {
            back.setSize({p_Width, p_Height});
            back.setFillColor(sf::Color::Blue);
            back.setPosition({0, fl_Height - p_Height});
            //
            // left_Bracket.sfText.setCharacterSize(40);
            // right_Bracket.sfText.setCharacterSize(40);
            // left_Bracket.sfText.setPosition({110 - gap, (static_cast<float>(height) - pHeight) + pHeight / 2 - charSize});
            // right_Bracket.sfText.setPosition({300 + gap, (static_cast<float>(height) - pHeight) + pHeight / 2 - charSize});
            userInput.sfText.setPosition({p_Width / 5, (fl_Height - p_Height) + p_Height / 2});
            counter.sfText.setPosition({p_Width / 4, fl_Height - p_Height + 40});
            skip.sfText.setPosition({p_Width / 4, fl_Height - p_Height + 40 * 3});
            fontPanel.sfText.setPosition({p_Width / 2, fl_Height - p_Height + char_Size});
            speedPanel.sfText.setPosition({p_Width / 2, fl_Height - p_Height + char_Size * 2});
            spawnPanel.sfText.setPosition({p_Width / 2, fl_Height - p_Height + char_Size * 3});
        }

    void drawTo(sf::RenderWindow& window) {
            window.draw(back);
            // left_Bracket.drawTo(window);
            // right_Bracket.drawTo(window);
            userInput.drawTo(window);
            counter.drawTo(window);
            skip.drawTo(window);
            fontPanel.drawTo(window);
            speedPanel.drawTo(window);
            spawnPanel.drawTo(window);
        }
};

auto main() -> int {

    //setting path
    auto path = std::filesystem::current_path();
    path = path.parent_path();
    //std::cout << "PATH: " << path << std::endl;

    //result
    auto best = path / "Txts" / "best.txt";
    auto best_Res = std::fstream(best);

    if (!best_Res.is_open()) {
        std::cerr << "LOG: [Could not open]" << '\n' << "Cause: file is missing"<< std::endl;
        return 1;
    }

    //hard-coded font paths
    auto font_Path_ChPe = path / "Fonts" / "ChakraPetch-Bold.ttf";
    auto font_Path_Ar = path / "Fonts" / "arial.ttf";
    auto font_Path_Lo = path / "Fonts" / "Lora-VariableFont_wght.ttf";

    //font list (hard-coded)
    auto fontChosen = 0;
    std::vector<sf::Font> fonts(3);
    fonts[0] = sf::Font(font_Path_ChPe);
    fonts[1] = sf::Font(font_Path_Ar);
    fonts[2] = sf::Font(font_Path_Lo);

    //basic font load
    sf::Font font(font_Path_ChPe);


    if (!fonts[0].openFromFile(font_Path_ChPe) || !fonts[1].openFromFile(font_Path_Ar) || !fonts[2].openFromFile(font_Path_Lo)) {
        std::cerr << "LOG: [Font not found]" << '\n' << "Cause: font is absent /// invalid pathname" << std::endl;
        return 1;
    }

    auto wordList_Path = path / "Txts" / "wordlist.txt";

    auto wordFile = std::fstream(wordList_Path);
    if (!wordFile.is_open()) {
        std::cerr << "LOG: [File not found]" << '\n' <<"Cause: file is absent /// invalid pathname" << std::endl;
        return 1;
    }



    std::vector<Word> buffer;   //read from file
    std::vector<Word*> visible; //words loaded
    std::string word_read;        //reader

    int speedMod = 0;
    std::vector<float> speedMods = {1, 3, 5};

    int spawnMod = 0;
    std::vector<float> spawnMods = {3, 2, 1};

    char user_Char;  //user input
    bool eq = true; //equality flag


    // Word game_over("GAME OVER", sf::Color::Red, fonts[fontChoice]);
    // game_over.sfText.setCharacterSize(70);
    // game_over.setShow(false);
    // game_over.sfText.setPosition({static_cast<float>(width) / 2, static_cast<float>(height) / 2});


    sf::RectangleShape pBackground;

    // Word left_Bracket("[", sf::Color::White, fonts[fontChoice]);
    // Word right_Bracket("]", sf::Color::White, fonts[fontChoice]);
    Word user_Word("", sf::Color::Yellow, fonts[fontChosen], true, true);             //user field

    Word word_Count("Total:", sf::Color::White, fonts[fontChosen]);                              //setting cnt
    Word cnt("0", sf::Color::Yellow, fonts[fontChosen], 0);
    cnt.sfText.setPosition({p_Width / 4 + 120, fl_Height - p_Height + char_Size});

    Word word_Skip("Missed:", sf::Color::White, fonts[fontChosen]);                              //setting missed cnt
    Word missed("0", sf::Color::Yellow, fonts[fontChosen], 0);
    missed.sfText.setPosition({p_Width / 4 + 120, fl_Height - p_Height + char_Size * 3});


    Word font_Panel("Current Font (Num1):", sf::Color::White, fonts[fontChosen]);                       //setting font panel
    Word font_Choice("1", sf::Color::Yellow, fonts[fontChosen]);
    font_Choice.sfText.setPosition({p_Width / 2 + 400, fl_Height - p_Height + char_Size});

    Word speed_Panel("Speed Mod. (Num 2):", sf::Color::White, fonts[fontChosen]);                        //setting speed panel
    Word speed_Choice("1", sf::Color::Yellow, fonts[fontChosen]);
    speed_Choice.sfText.setPosition({p_Width / 2 + 400, fl_Height - p_Height + char_Size * 2});

    Word spawn_Panel("Spawn Rate Mod. (Num3):", sf::Color::White, fonts[fontChosen]);                   //setting spawn rate panel
    Word spawn_Choice("1", sf::Color::Yellow, fonts[fontChosen]);
    spawn_Choice.sfText.setPosition({p_Width / 2 + 400, fl_Height - p_Height + char_Size * 3});


    Panel panel(pBackground, user_Word, word_Count, word_Skip, font_Panel, speed_Panel, spawn_Panel); //panel itself



    while (wordFile >> word_read) {
        std::cout << word_read << '\n';
        buffer.emplace_back(word_read, sf::Color::Green, fonts[fontChosen], false);
    } //load words from list


    auto window = sf::RenderWindow(
        sf::VideoMode({width, height}),
        "MONKEY_TYPER",
        sf::Style::Close,
        sf::State::Fullscreen,
        sf::ContextSettings{.antiAliasingLevel = 6}
        );
        window.setFramerateLimit(60);

    size_t current_Index = 0;
    sf::Clock clock;

    while (window.isOpen()) {
        while (auto const event = window.pollEvent()) {
            if (event ->is<sf::Event::Closed>()) window.close();

            if (auto const key = event ->getIf<sf::Event::KeyPressed>()) {

                if (key->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }   //close on escape

                if (key->code == sf::Keyboard::Key::Num1) {
                    font_Choice.fontChange();
                    fontChosen = (fontChosen + 1) % 3;
                    user_Word.sfText.setFont(fonts[fontChosen]);
                }     //font modifier

                if (key->code == sf::Keyboard::Key::Num2) {
                    speed_Choice.speedChange();
                    speedMod = (speedMod + 1) % 3;
                }     //speed modifier

                if (key->code == sf::Keyboard::Key::Num3) {
                    spawn_Choice.spawnChange();
                    spawnMod = (spawnMod + 1) % 3;
                }     //spawn rate modifier
            }

            if (event ->is<sf::Event::TextEntered>()) {
                auto input = event->getIf<sf::Event::TextEntered>();
                user_Char = static_cast<char>(input->unicode);
                user_Word.charAppend(user_Char);

                if (isKeyPressed(sf::Keyboard::Key::Enter)) {
                    for (int i = 0; i < visible.size(); ++i) {
                        if (user_Word.getText() == visible[i]->getText()) {
                            std::cout << "LOG: [USER: " << user_Word.getText() << " | MATCHED: " << visible[i]->getText() << ']' << '\n';
                            user_Word.nullify();
                            visible[i]->nullify();
                            cnt.cntPlus();
                        }
                        eq = false;
                    } //check for equality

                    if (eq == false) {
                        user_Word.nullify();
                        eq = true;
                    }
                }
            }
        }


        //init words on screen
        if (clock.getElapsedTime().asSeconds() >= spawnMods[spawnMod] && current_Index < buffer.size()) {
            buffer[current_Index].setShow(true);
            buffer[current_Index].setSpeed(speedMods[speedMod]);
            visible.push_back(&buffer[current_Index]);
            current_Index++;
            clock.restart();
        }


        //warning
        for (int i = 0; i < visible.size(); ++i) {
            if (visible[i]->sfText.getPosition().x > static_cast<float>(width) / 1.5f) {
                visible[i]->sfText.setFillColor(sf::Color::Red);
            }
        }
        //word skipped
        for (int i = 0; i < visible.size(); ++i) {
            if ((visible[i]->sfText.getPosition().x > window.getSize().x) && !visible[i]->sfText.getString().isEmpty()) {
                visible[i]->setSkipped(true);
                visible[i]->sfText.setString("");
            }
        }

        for (auto* word: visible) {
            if (word->getSkipped() == true) {
                missed.cntSkip();
                word->setSkipped(false);
            }
        }


        if (missed.getMissCount() >= 10) {
            std::string bt = std::to_string(cnt.getCount());
            best_Res << "Result: " << bt;
            std::cout << "LOG: [GAME OVER :P]" << std::endl;
            window.close();
        }


        window.clear(sf::Color::Black);

        panel.drawTo(window);
        user_Word.drawTo(window);
        cnt.drawTo(window);
        missed.drawTo(window);
        font_Choice.drawTo(window);
        speed_Choice.drawTo(window);
        spawn_Choice.drawTo(window);

        for (auto* word : visible) {
            word->sfText.setFont(fonts[fontChosen]);  // } setting params on drawing
            word->setSpeed(speedMods[speedMod]);      // }

            word->move();
            word->drawTo(window);
        }

        window.display();
    }
    return 0;
}