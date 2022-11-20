#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <stack>

void panic_if(bool const condition, const char* reason)
{
    if (condition)
    {
        std::cerr << "error: " << reason << "\n";
        std::abort();
    }
}

void exit_loop_block(std::fstream& source_file)
{
    // first bracket was already read
    int brackets_to_close{1};
    while (source_file.good())
    {
        char symbol = static_cast<char>(source_file.get());
        if (symbol == '[')
        {
            ++brackets_to_close;
        }
        else if (symbol == ']')
        {
            --brackets_to_close;
            if (brackets_to_close == 0)
            {
                break;
            }
        }
    }
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " BRAIN_FUCK_SOURCE_FILE\n";
        return 1;
    }

    std::fstream source_file{argv[1]};
    if (!source_file.is_open())
    {
        std::cerr << "error: failed to open " << argv[1];
        return 1;
    }

    std::deque<char> cells{};
    cells.push_back(0);
    auto cell = cells.begin();

    std::stack<std::streampos> checkpoint{};
    bool skip_block{false};

    char symbol = static_cast<char>(source_file.get());
    while (source_file.good()) {
        switch (symbol)
        {
        case '>':
            ++cell;
            if (cell == cells.end())
            {
                cells.push_back(0);
                cell = cells.end() - 1;
            }
            break;
        case '<':
            if (cell == cells.begin())
            {
                cells.push_front(0);
                cell = cells.begin();
            }
            --cell;
            break;
        case '+':
            ++(*cell);
            break;
        case '-':
            --(*cell);
            break;
        case '.':
            std::cout << *cell;
            break;
        case ',':
            std::cin >> *cell;
            break;
        case '[':
            if (*cell != 0)
            {
                checkpoint.push(source_file.tellg());
            }
            else
            {
                exit_loop_block(source_file);
            }
            break;
        case ']':
            panic_if(checkpoint.empty(), "unexpected ']' operator");
            if (*cell != 0)
            {
                source_file.seekg(checkpoint.top());
            }
            else
            {
                checkpoint.pop();
            }
            break;
        }
        symbol = source_file.get();
    }

    return 0;
}
