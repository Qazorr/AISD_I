#include "Visualizer.h"
#include <unistd.h>
#include <vector>
#include <stack>

//#define DARK

#ifdef DARK
using namespace DARK_THEME;
#else
using namespace LIGHT_THEME;
#endif // !DARK

Visualizer::Visualizer()
{
    if (!this->font.loadFromFile("dependencies/arial.ttf"))
    {
        std::cerr << "FONT ERROR" << std::endl;
        exit(-1);
    }
    this->window.create(sf::VideoMode(WIDTH, HEIGHT), "SFML BINARY TREE VISUALIZATION");
    this->window.setFramerateLimit(60);
    this->view = window.getDefaultView();
    this->moving = false;
    this->zoom = 1;
}

Tree* Visualizer::button_loop()
{
    sf::Event event;
    Button bst(WIDTH/2 - 350.f, HEIGHT/2 - 50.f, 200.f, 50.f, &this->font, "BST", STD_NODE_COLOR, sf::Color::Red, HIGHLIGHTED_NODE_COLOR);
    Button avl(WIDTH/2 + 150.f, HEIGHT/2 - 50.f, 200.f, 50.f, &this->font, "AVL", STD_NODE_COLOR, sf::Color::Red, HIGHLIGHTED_NODE_COLOR);
    while (window.isOpen()) 
    {
        while (window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                return new BST();
                break;

            case sf::Event::MouseButtonPressed:
                bst.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
                avl.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))); 
                if (bst.isPressed()) return new BST();
                if (avl.isPressed()) return new AVL();
                break;

            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                    return new BST();
                }
            default:
                break;
            }
            window.clear(BG_COLOR);
            bst.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
            avl.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
            bst.render(&window);
            avl.render(&window);
            window.display();
        }
    }
    return new BST();
}

void Visualizer::main_loop(Tree *tree)
{
    if (dynamic_cast<BST*>(tree)) this->window.setTitle("BST VISUALIZATION");
    else this->window.setTitle("AVL VISUALIZATION");
    std::cout << "Kliknij na okno, po czym kliknij jeden z ponizszych klawiszy oraz wprowadz swoj input do konsoli." << std::endl;
    std::cout << "A - dodaj wartosc do drzewa\n";
    std::cout << "D - usun wartosc z drzewa\n";
    std::cout << "F - znajdz wartosc w drzewie\n";
    std::cout << "K - znajdz najmniejsza wartosc w drzewie\n";
    std::cout << "L - znajdz najwieksza wartosc w drzewie\n";
    std::cout << "Q - wypisz drzewo inorder\n";
    std::cout << "W - wypisz drzewo preorder\n";
    std::cout << "E - wypisz drzewo postorder\n";
    while (window.isOpen())
    {
        window.clear(BG_COLOR);
        this->get_input(tree);
        this->draw_tree(tree);
        window.display();
    }
}

void Visualizer::get_input(Tree *tree)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            //wylaczanie okna za pomoca 'X'
        case sf::Event::Closed:
            window.close();
            break;

            //user kliknie przycisk na klawiaturze
        case sf::Event::KeyPressed:
            //escape -> wylacza program
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }

            //A -> zbiera input i dodaje wartosc do drzewa
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                int to_add;
                std::cout << "Wybierz liczbe ktora ma zostac dodana: ";
                std::cin >> to_add;
                add_node(tree, to_add);
                while (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {}
            }
            //D -> zbiera input i usuwa wartosc z drzewa
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                int to_rem;
                std::cout << "Wybierz liczbe ktora ma byc usunieta: ";
                std::cin >> to_rem;
                this->remove_node(tree, to_rem);
                if(tree->root) this->update_connections(tree);
            }
            //K -> znajdz liczbe o minimalnej wartosci w drzewie
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
                window.clear(BG_COLOR);
                this->find_minimum(tree);
                window.display();
                while (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {}
            }

            //L -> znajdz liczbe o maksymalnej wartosci w drzewie
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                window.clear(BG_COLOR);
                this->find_maximum(tree);
                window.display();
                while (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {}
            }
            //F -> zbierz input i znajdz wartosc w drzewie
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                int to_find;
                std::cout << "Jaka wartosc chcesz wyszukac? ";
                std::cin >> to_find;
                if (this->find(tree, to_find))
                    std::cout << "Wartosc " << to_find << " zostala znaleziona\n";
                else
                    std::cout << "Wartosc " << to_find << " nie zostala znaleziona\n";
                while (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {}
            }

            //Q/W/E -> wypisania drzewa na terminal
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                std::cout << "INORDER: ";
                tree->display_inorder();
                std::cout << std::endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                std::cout << "PREORDER: ";
                tree->display_preorder();
                std::cout << std::endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                std::cout << "POSTORDER: ";
                tree->display_postorder();
                std::cout << std::endl;
            }

            break;

        case sf::Event::MouseButtonPressed:
            // Przycisk myszki jest nacisniety, zbieramy pozycje kursora
            if (event.mouseButton.button == 0) {
                moving = true;
                oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
                std::cout << "x" << sf::Mouse::getPosition().x << "\ty" << sf::Mouse::getPosition().y << std::endl;
            }
            break;
        case  sf::Event::MouseButtonReleased:
            // Przycisk myszki zostal zwolniony, nie poruszamy ekranu
            if (event.mouseButton.button == 0) {
                moving = false;
            }
            break;


        case sf::Event::MouseMoved:
        {
            // Wylacznie jesli przycisk jest ciagle trzymany przez uzytkownika
            if (!moving)
                break;
            // Ustalamy nowa pozycje w swiecie
            const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
            // Ustalamy jak zmienila sie pozycja kursora podczas poruszania
            // Zamieniamy ich kolejnosc (jesli user porusza w prawo to view porusza sie w lewo)
            const sf::Vector2f deltaPos = oldPos - newPos;

            // Ustawiamy nowy view
            view.setCenter(view.getCenter() + deltaPos);
            window.setView(view);

            // Zapisujemy nowa pozycje
            oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
            break;
        }
        case sf::Event::MouseWheelScrolled:
            // Wylacznie jesli przycisk jest wciskany
            if (moving)
                break;

            // Ustalamy w ktora strone uzytkownik chce zoomowac (czy chce przyblizyc czy oddalic view)
            if (event.mouseWheelScroll.delta <= -1)
                zoom = std::min(2.f, zoom + .1f);
            else if (event.mouseWheelScroll.delta >= 1)
                zoom = std::max(.5f, zoom - .1f);

            // Zapisujemy nowy view
            view.setSize(window.getDefaultView().getSize());
            view.zoom(zoom);
            window.setView(view);
            break;
        default:
            break;
        }
    }
}

void Visualizer::update_connections(Tree* tree)
{
    if (!tree->root) return;

    tree->root->position.x = WIDTH / 2;
    tree->root->position.y = 1.5f * RADIUS;
    tree->root->move_x = ROOT_MOVE_X;

    std::stack<Node*> nodes;
    nodes.push(tree->root);

    //preorder traversal
    //przechodze przez kazdy node i zmieniam pozycje tak aby zgadzala sie z pozycja rodzica
    while (!nodes.empty())
    {
        Node* node = nodes.top();
        if (node->left) tree->update_node_position(node, node->left);
        if (node->right) tree->update_node_position(node, node->right);
        nodes.pop();

        if (node->left) nodes.push(node->left);
        if (node->right) nodes.push(node->right);
    }
}

void Visualizer::draw_line(sf::Vector2f from, sf::Vector2f to)
{
    sf::Vertex line[] =
    {
        sf::Vertex(from),
        sf::Vertex(to)
    };
    line->color = sf::Color::Red;
    window.draw(line, 2, sf::Lines);
}

void Visualizer::draw_line(Node* from, Node* to)
{
    sf::Vertex line[] =
    {
        sf::Vertex(from->position),
        sf::Vertex(to->position)
    };
    line->color = sf::Color::Red;
    window.draw(line, 2, sf::Lines);
}

void Visualizer::draw_node(Node* node, sf::Color color)
{
    sf::CircleShape circle(RADIUS);
    circle.setOrigin(sf::Vector2f(RADIUS, RADIUS));
    circle.setPosition(node->position);
    circle.setFillColor(color);
    circle.setOutlineColor(OUTLINE_COLOR);
    circle.setOutlineThickness(OUTLINE_THICKNESS);

    sf::Text text;
    text.setString(std::to_string(node->mData));
    text.setCharacterSize(FONT_SIZE);
    text.setFont(this->font);
    text.setFillColor(TEXT_COLOR);
    text.setOrigin(
        text.getLocalBounds().left + text.getLocalBounds().width / 2,
        text.getLocalBounds().top + text.getLocalBounds().height / 2
    );
    float min_size = std::min(
        (RADIUS * 1.5f) / text.getLocalBounds().width,
        (RADIUS * 1.5f / 2) / text.getLocalBounds().height
    );
    text.setScale(sf::Vector2f(min_size, min_size));
    text.setPosition(node->position);

    window.draw(circle);
    window.draw(text);
}

void Visualizer::draw_moving_node(Tree* tree, Node* from, Node* to)
{
    Node moving_node = *from;

    sf::Vector2f deltaPos(from->position - to->position);
    sf::Vector2f move_per_step(deltaPos.x / STEPS, deltaPos.y / STEPS);
    for (int i = 0; i < STEPS; i++) {
        moving_node.position.x -= move_per_step.x;
        moving_node.position.y -= move_per_step.y;
        window.clear(BG_COLOR);
        this->draw_tree(tree);
        this->draw_node(&moving_node, RUNNING_NODE_COLOR);
        window.display();
        usleep(20);
    }
}

void Visualizer::draw_tree(Tree *tree)
{
    std::stack<Node*> nodes;
    nodes.push(tree->root);
    if (!tree->root) return;

    while (!nodes.empty())
    {
        Node* node = nodes.top();
        if (node->left) draw_line(node, node->left);
        if (node->right) draw_line(node, node->right);
        draw_node(node, STD_NODE_COLOR);
        nodes.pop();

        if (node->left) nodes.push(node->left);
        if (node->right) nodes.push(node->right);
    }
}

void Visualizer::draw_top_left(Tree* tree, Node* left, Node* right, std::string symbol_, std::string instruction_)
{
    sf::Vector2i pixelPos = sf::Vector2i(static_cast<int>(RADIUS), static_cast<int>(RADIUS));
    sf::Vector2f temp = window.mapPixelToCoords(pixelPos);

    Node* top_left = new Node(left->mData, 0, 0, temp.x, temp.y);
    Node* top_left_opposite = new Node(right->mData, 0, 0, temp.x + 4 * RADIUS, temp.y);

    sf::Text symbol("x", this->font, 40);
    sf::Text instruction(" ", this->font, FONT_SIZE);
    symbol.setPosition(temp.x + 1.5f*RADIUS, temp.y - 1.375f * RADIUS);
    symbol.setFillColor(TOP_LEFT_COLOR);
    symbol.setString(symbol_);
    instruction.setPosition(top_left->position.x - RADIUS, top_left->position.y + RADIUS + 10);
    instruction.setFillColor(MESSAGE_COLOR);
    instruction.setString(instruction_);

    draw_node(top_left, TOP_LEFT_COLOR);
    draw_node(top_left_opposite, TOP_LEFT_COLOR);
    window.draw(symbol);
    window.draw(instruction);
}

void Visualizer::find_minimum(Tree *tree)
{
    Node* node = tree->root;

    sf::Vector2i pixelPos = sf::Vector2i(static_cast<int>(RADIUS), static_cast<int>(RADIUS));
    sf::Vector2f temp = window.mapPixelToCoords(pixelPos);

    sf::Text text("Aktualny min: ", this->font, 24);
    text.setPosition(temp.x, temp.y + text.getCharacterSize()/static_cast<float>(2));
    text.setFillColor(MESSAGE_COLOR);

    sf::Text found_null("Posiada lewe dziecko, przechodze dalej", this->font, 18);
    found_null.setPosition(temp.x, temp.y + text.getLocalBounds().height * 2 + RADIUS);
    found_null.setFillColor(MESSAGE_COLOR);

    Node* current_min = new Node(tree->root->mData, 0, 0, text.getLocalBounds().width + temp.x + RADIUS, temp.y + 1.375f*RADIUS);
    std::vector<std::pair<Node*, sf::Color>> nodes;
    while (node && node->left) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) return;
        window.clear(BG_COLOR);
        draw_tree(tree);
        nodes.push_back(std::make_pair(node, HIGHLIGHTED_NODE_COLOR));
        for (const auto& pair : nodes) {
            draw_node(pair.first, pair.second);
            if (pair.first->left) {
                draw_line(pair.first->position, pair.first->left->position);
                draw_node(pair.first->left, CONSIDERED_NODE_COLOR);
            }
        }
        window.draw(text);
        window.draw(found_null);
        draw_node(current_min, HIGHLIGHTED_NODE_COLOR);
        window.display();
        usleep(700000);
        current_min->mData = node->left->mData;
        node = node->left;
    }
    nodes.push_back(std::make_pair(node, sf::Color::Green));
    window.clear(BG_COLOR);
    for (const auto& pair : nodes) {
        if (pair.first->left) draw_line(pair.first->position, pair.first->left->position);
        draw_node(pair.first, pair.second);
    }
    window.draw(text);
    draw_node(current_min, HIGHLIGHTED_NODE_COLOR);
    window.display();
    usleep(1000000);
    std::cout << "Najmniejsza wartosc w drzewie: " << nodes.at(nodes.size() - 1).first->mData << std::endl;
}

void Visualizer::find_maximum(Tree *tree)
{
    Node* node = tree->root;

    sf::Vector2i pixelPos = sf::Vector2i(static_cast<int>(RADIUS), static_cast<int>(RADIUS));
    sf::Vector2f temp = window.mapPixelToCoords(pixelPos);

    sf::Text text("Aktualny max: ", this->font, 24);
    text.setPosition(temp.x, temp.y + text.getCharacterSize() / static_cast<float>(2));
    text.setFillColor(MESSAGE_COLOR);

    sf::Text found_null("Posiada prawe dziecko, przechodze dalej", this->font, 18);
    found_null.setPosition(temp.x, temp.y + text.getLocalBounds().height * 2 + RADIUS);
    found_null.setFillColor(MESSAGE_COLOR);

    Node* current_max = new Node(tree->root->mData, 0, 0, text.getLocalBounds().width + RADIUS + temp.x, RADIUS + temp.y);
    std::vector<std::pair<Node*, sf::Color>> nodes;
    while (node && node->right) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) return;
        window.clear(BG_COLOR);
        draw_tree(tree);
        nodes.push_back(std::make_pair(node, HIGHLIGHTED_NODE_COLOR));
        for (const auto& pair : nodes) {
            draw_node(pair.first, pair.second);
            if (pair.first->right) {
                draw_line(pair.first->position, pair.first->right->position);
                draw_node(pair.first->right, CONSIDERED_NODE_COLOR);
            }
        }
        window.draw(text);
        window.draw(found_null);
        draw_node(current_max, HIGHLIGHTED_NODE_COLOR);
        window.display();
        usleep(700000);
        current_max->mData = node->right->mData;
        node = node->right;
    }
    nodes.push_back(std::make_pair(node, sf::Color::Green));
    window.clear(BG_COLOR);
    for (const auto& pair : nodes) {
        if (pair.first->right) draw_line(pair.first->position, pair.first->right->position);
        draw_node(pair.first, pair.second);
    }
    window.draw(text);
    draw_node(current_max, HIGHLIGHTED_NODE_COLOR);
    window.display();
    usleep(1000000);
    std::cout << "Najwieksza wartosc w drzewie: " << nodes.at(nodes.size() - 1).first->mData << std::endl;
}

bool Visualizer::find(Tree* tree, int data, bool write)
{
    Node* curr = tree->root;

    sf::Vector2i pixelPos = sf::Vector2i(static_cast<int>(RADIUS), static_cast<int>(RADIUS));
    sf::Vector2f temp = window.mapPixelToCoords(pixelPos);

    Node* top_left = new Node(data, 0, 0, temp.x, temp.y);

    std::string symbol{};
    std::string instruction{};

    std::vector<std::pair<Node*, sf::Color>> nodes;
    bool found = false;
    while (curr)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) return false;
        window.clear(BG_COLOR);
        if (curr->mData > data) {
            nodes.push_back(std::make_pair(curr, HIGHLIGHTED_NODE_COLOR));
            draw_top_left(tree, top_left, curr, "<", "Liczba jest mniejsza, przechodze do lewego poddrzewa");
            curr = curr->left;
        }
        else if (curr->mData < data) {
            nodes.push_back(std::make_pair(curr, HIGHLIGHTED_NODE_COLOR));
            draw_top_left(tree, top_left, curr, ">", "Liczba jest wieksza, przechodze do prawego poddrzewa");
            curr = curr->right;
        }
        else {
            nodes.push_back(std::make_pair(curr, sf::Color::Green));
            draw_top_left(tree, top_left, curr, "=", "Znaleziono liczbe");
            found = true;
        }
        draw_tree(tree);
        for (const auto& pair : nodes) {
            draw_node(pair.first, pair.second);
            if (pair.first->left) {
                draw_line(pair.first, pair.first->left);
                draw_node(pair.first->left, CONSIDERED_NODE_COLOR);
            }

            if (pair.first->right) {
                draw_line(pair.first, pair.first->right);
                draw_node(pair.first->right, CONSIDERED_NODE_COLOR);
            }
        }
        window.display();
        usleep(1000000);
        if (found)
            break;
    }
    return found;
}

int Visualizer::get_height(Node* node)
{
    return node ? node->mHeight : 0;
}

int Visualizer::get_balance_factor(Node* node)
{
    return node != nullptr ? get_height(node->left) - get_height(node->right) : -1;
}

Node* Visualizer::smallest_node(Node* node)
{
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

void Visualizer::update(Node* node)
{
    if (node)
        node->mHeight = std::max(get_height(node->left), get_height(node->right)) + 1;
}

void Visualizer::draw_left_rotation(Tree* tree, Node* parent, Node* left, Node* right)
{
    Node left_to_parent = *left;
    Node parent_to_right = *parent;
    Node child_left_to_left{};
    if (left->left) child_left_to_left = *left->left;

    sf::Vector2f step_left_left{};

    sf::Vector2f step_left_parent((left->position - parent->position).x / ROTATION_STEPS, (left->position - parent->position).y / ROTATION_STEPS);
    sf::Vector2f step_parent_right((parent->position - right->position).x / ROTATION_STEPS, (parent->position - right->position).y / ROTATION_STEPS);
    if (left->left) step_left_left = sf::Vector2f((left->left->position - left->position).x / ROTATION_STEPS, (left->left->position - left->position).y / ROTATION_STEPS);
    for (int i = 0; i < ROTATION_STEPS; i++) {
        left_to_parent.position.x -= step_left_parent.x;
        left_to_parent.position.y -= step_left_parent.y;

        parent_to_right.position.x -= step_parent_right.x;
        parent_to_right.position.y -= step_parent_right.y;

        if (left->left) {
            child_left_to_left.position.x -= step_left_left.x;
            child_left_to_left.position.y -= step_left_left.y;
        }

        this->window.clear(BG_COLOR);
        this->draw_tree(tree);
        this->draw_node(&left_to_parent, RUNNING_NODE_COLOR);
        this->draw_node(&parent_to_right, RUNNING_NODE_COLOR);
        if (left->left) this->draw_node(&child_left_to_left, RUNNING_NODE_COLOR);
        window.display();
        usleep(ROTATION_SLEEP);
    }
}

void Visualizer::draw_right_rotation(Tree* tree, Node* parent, Node* right, Node* left)
{
    Node right_to_parent = *right;
    Node parent_to_left = *parent;
    Node child_right_to_right{};
    if (right->right) child_right_to_right = *right->right;

    sf::Vector2f step_right_right{};

    sf::Vector2f step_left_parent((right->position - parent->position).x / ROTATION_STEPS, (right->position - parent->position).y / ROTATION_STEPS);
    sf::Vector2f step_parent_right((parent->position - left->position).x / ROTATION_STEPS, (parent->position - left->position).y / ROTATION_STEPS);
    if (right->right) step_right_right = sf::Vector2f((right->right->position - right->position).x / ROTATION_STEPS, (right->right->position - right->position).y / ROTATION_STEPS);
    for (int i = 0; i < ROTATION_STEPS; i++) {
        right_to_parent.position.x -= step_left_parent.x;
        right_to_parent.position.y -= step_left_parent.y;

        parent_to_left.position.x -= step_parent_right.x;
        parent_to_left.position.y -= step_parent_right.y;

        if (right->right) {
            child_right_to_right.position.x -= step_right_right.x;
            child_right_to_right.position.y -= step_right_right.y;
        }

        this->window.clear(BG_COLOR);
        this->draw_tree(tree);
        this->draw_node(&right_to_parent, RUNNING_NODE_COLOR);
        this->draw_node(&parent_to_left, RUNNING_NODE_COLOR);
        if (right->right) this->draw_node(&child_right_to_right, RUNNING_NODE_COLOR);
        window.display();
        usleep(ROTATION_SLEEP);
    }
}

Node* Visualizer::balance(Tree* tree, Node* node)
{
    if (!node) return node;
    update(node);
    if (get_balance_factor(node) == -2) {
        if (get_balance_factor(node->right) > 0) {
            node->right = left_rotation(tree, node->right);
            this->update_connections(tree);
        }
        return right_rotation(tree, node);
    }
    if (get_balance_factor(node) == 2) {
        if (get_balance_factor(node->left) < 0) {
            node->left = right_rotation(tree, node->left);
            this->update_connections(tree);
        }
        return left_rotation(tree, node);
    }
    return node;
}

Node* Visualizer::insert_f(Tree* tree, Node* node, int data)
{
    if (node == nullptr)
        return new Node(data, 1, 0, 0, 0);

    if (data < node->mData) {
        node->left = insert_f(tree, node->left, data);
    }
    else if (data > node->mData) {
        node->right = insert_f(tree, node->right, data);
    }
    else {}

    return balance(tree, node);
}

Node* Visualizer::remove_f(Tree* tree, Node* node, int data)
{
    if (!node)
        return nullptr;

    if (data < node->mData)
        node->left = remove_f(tree, node->left, data);
    else if (data > node->mData)
        node->right = remove_f(tree, node->right, data);
    else {
        if (node->left && node->right) {
            Node* temp = smallest_node(node->right);
            node->mData = temp->mData;
            node->right = remove_f(tree, node->right, node->mData);
        }
        else {
            Node* temp = node;
            if (!node->left)
                node = node->right;
            else if (!node->right)
                node = node->left;
            delete temp;
        }
    }

    return balance(tree, node);
}

Node* Visualizer::left_rotation(Tree* tree, Node*& parent_node)
{
    sf::Vector2i pixelPos = sf::Vector2i(static_cast<int>(RADIUS), static_cast<int>(RADIUS));
    sf::Vector2f tmp = window.mapPixelToCoords(pixelPos);

    sf::Text text("Lewa rotacja wokol ", this->font, 24);
    text.setPosition(tmp.x, tmp.y + text.getCharacterSize() / static_cast<float>(2));
    text.setFillColor(MESSAGE_COLOR);

    Node* top_left = new Node(parent_node->mData, 0, 0, text.getLocalBounds().width + tmp.x + RADIUS, tmp.y + 1.375f * RADIUS);
 
    window.clear(BG_COLOR);
    this->draw_tree(tree);
    window.draw(text);
    this->draw_node(top_left, HIGHLIGHTED_NODE_COLOR);
    this->draw_node(parent_node, HIGHLIGHTED_NODE_COLOR);
    window.display();
    usleep(1000000);
    
    Node* right = parent_node->right ? parent_node->right : new Node(0, 1, parent_node->move_x / MOVE_RATIO, parent_node->position.x, parent_node->position.y + MOVE_Y);
    if (!parent_node->right) right->update_pos(false);


    Node* temp = parent_node->left;
    this->draw_left_rotation(tree, parent_node, temp, right);
    parent_node->left = temp->right;
    temp->right = parent_node;
    update(parent_node);
    update(temp);
    delete top_left;
    return temp;
}

Node* Visualizer::right_rotation(Tree* tree, Node*& parent_node)
{
    sf::Vector2i pixelPos = sf::Vector2i(static_cast<int>(RADIUS), static_cast<int>(RADIUS));
    sf::Vector2f tmp = window.mapPixelToCoords(pixelPos);

    sf::Text text("Prawa rotacja wokol ", this->font, 24);
    text.setPosition(tmp.x, tmp.y + text.getCharacterSize() / static_cast<float>(2));
    text.setFillColor(MESSAGE_COLOR);

    Node* top_left = new Node(parent_node->mData, 0, 0, text.getLocalBounds().width + tmp.x + RADIUS, tmp.y + 1.375f * RADIUS);

    window.clear(BG_COLOR);
    this->draw_tree(tree);
    window.draw(text);
    this->draw_node(top_left, HIGHLIGHTED_NODE_COLOR);
    this->draw_node(parent_node, HIGHLIGHTED_NODE_COLOR);
    window.display();
    usleep(1000000);

    Node* left = parent_node->left ? parent_node->left : new Node(0, 1, parent_node->move_x / MOVE_RATIO, parent_node->position.x, parent_node->position.y + MOVE_Y);
    if (!parent_node->left) left->update_pos();

    Node* temp = parent_node->right;
    this->draw_right_rotation(tree, parent_node, temp, left);
    parent_node->right = temp->left;
    temp->left = parent_node;
    update(parent_node);
    update(temp);
    return temp;
}

void Visualizer::add_node(Tree* tree, int data)
{
    if (!tree->root) {
        tree->root = new Node(data, 1, ROOT_MOVE_X, WIDTH / 2.f, 1.5f * RADIUS);
        return;
    }

    sf::Vector2i pixelPos = sf::Vector2i(static_cast<int>(RADIUS), static_cast<int>(RADIUS));
    sf::Vector2f temp = window.mapPixelToCoords(pixelPos);

    Node* top_left = new Node(data, 0, 0, temp.x, temp.y);
    Node* top_left_opposite = new Node(data, 0, 0, temp.x + 4 * RADIUS, temp.y);

    window.clear(BG_COLOR);
    draw_node(top_left, HIGHLIGHTED_NODE_COLOR);
    draw_tree(tree);
    window.display();

    usleep(1000000);

    std::string symbol{}, instruction{};

    Node* curr = tree->root;
    Node running_node = *tree->root;
    running_node.mData = data;
    Node* last_node = tree->root;
    sf::Vector2f lastPos;
    bool last_is_left = false;

    while (curr)
    {
        top_left_opposite->mData = curr->mData;
        if (curr->mData > data) {
            symbol = "<";
            instruction = "Liczba jest mniejsza, przechodze do lewego poddrzewa";
        }
        else {
            symbol = ">";
            instruction = "Liczba jest wieksza, przechodze do prawego poddrzewa";
        }

        window.clear(BG_COLOR);
        this->draw_tree(tree);
        draw_top_left(tree, top_left, curr, symbol, instruction);
        draw_node(&running_node, RUNNING_NODE_COLOR);
        window.display();
        usleep(1000000);

        if (curr->mData > data) {
            if (!curr->left) {
                last_node = new Node(data, 1, curr->move_x / MOVE_RATIO, curr->position.x, curr->position.y + MOVE_Y);
                last_node->update_pos();
                last_is_left = true;
                break;
            }
            draw_moving_node(tree, &running_node, curr->left);
            running_node.position = curr->left->position;
            curr = curr->left;
        }
        //poruszam sie w prawo
        else if (curr->mData < data) {
            if (!curr->right) {
                last_node = new Node(data, 1, curr->move_x / MOVE_RATIO, curr->position.x, curr->position.y + MOVE_Y);
                last_node->update_pos(false);
                break;
            }
            draw_moving_node(tree, &running_node, curr->right);
            running_node.position = curr->right->position;
            curr = curr->right;
        }
        else {
            return;
        }
    }
    draw_moving_node(tree, &running_node, last_node);
    if (last_is_left) curr->left = last_node;
    else curr->right = last_node;
    usleep(200000);
    window.clear(BG_COLOR);
    this->draw_tree(tree);
    window.display();

    delete top_left;
    delete top_left_opposite;

    //jesli drzewo jest AVL wykonam dodatkowe rotacje
    if (dynamic_cast<AVL*>(tree)) {
        tree->root = insert_f(tree, tree->root, data);
        this->update_connections(tree);
    }
}

bool Visualizer::remove_node(Tree* tree, int data)
{
    if (!tree->root) return false;
    if (!tree->root->left && !tree->root->right) {
        Node* temp = tree->root;
        tree->root = nullptr;
        delete temp;
        return true;
    }

    if (!this->find(tree, data, false)) {
        std::cout << "Nie znaleziono liczby " << data << "w drzewie\n";
        return false;
    }

    if (dynamic_cast<BST*>(tree)) {
        Node* parent = nullptr, * curr = tree->root;
        Node* moving_node = nullptr;
        if(curr) moving_node = new Node(data, curr->position.x, curr->position.y);

        while (curr && curr->mData != data) {
            parent = curr;
            if (data < curr->mData) {
                //draw_moving_node(tree, moving_node, curr->left);
                moving_node->position = curr->left->position;
                curr = curr->left;
            }
            else {
                //draw_moving_node(tree, moving_node, curr->right);
                moving_node->position = curr->right->position;
                curr = curr->right;
            }
        }

        if (!curr) {
            return false;
        }

        usleep(400000);

        window.clear(BG_COLOR);
        draw_tree(tree);

        //case z 0 dziecmi
        if (!curr->left && !curr->right) {
            if (parent->left == curr) {
                parent->left = nullptr;
                delete curr;
                return true;
            }
            else {
                parent->right = nullptr;
                delete curr;
                return true;
            }
        }

        //case z 1 dzieckiem (^ <- xor)
        else if (!curr->left ^ !curr->right) {
            Node *temp = nullptr;

            if (!curr->left)
                temp = curr->right;
            else
                temp = curr->left;

            if (!parent) {
                draw_moving_node(tree, temp, tree->root);
                tree->root = temp;
                return true;
            }
            
            if (curr == parent->left) {
                draw_moving_node(tree, temp, parent->left);
                parent->left = temp;
            }
            else {
                draw_moving_node(tree, temp, parent->right);
                parent->right = temp;
            }

            delete curr;
            return true;
        }
        //2 dzieci
        else {
            Node *p = nullptr, *temp = curr->right;

            while (temp->left) {
                p = temp;
                temp = temp->left;
            }

            if (p)
                p->left = temp->right;
            else {
                curr->right = temp->right;
            }

            draw_moving_node(tree, temp, curr);
            curr->mData = temp->mData;
            delete temp;
            return true;
        }
    }
    else {
        tree->root = remove_f(tree, tree->root, data);
        this->update_connections(tree);
    }
    return false;
}