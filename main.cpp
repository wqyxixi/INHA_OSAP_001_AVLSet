// author: CHEN XUYAN
// date: 2024-11-19

#include "OSAP_001_AVLSet.h"
#include <iostream>

int main()
{
    // 输入循环的次数
    int loop;
    std::cin >> loop;
    for (int i = 0; i < loop; i++)
    {
        int num;
        std::cin >> num;
        AVLTree avlTree;
        for (int j = 0; j < num; j++)
        {
            std::string command;
            std::cin >> command;
            if (command == "Height")
            {
                std::cout << avlTree.height() << std::endl;
            }
            else if (command == "Empty")
            {
                std::cout << (avlTree.empty() ? 1 : 0) << std::endl;
            }
            else if (command == "Insert")
            {
                int value;
                std::cin >> value;
                std::cout << avlTree.insert(value)<< std::endl;
            }
            else if (command == "Size")
            {
                std::cout << avlTree.size() << std::endl;
            }
            else if (command == "Find")
            {
                int value;
                std::cin >> value;
                std::cout << avlTree.find(value)<< std::endl;
            }
            else if (command == "Average")
            {
                int value;
                std::cin >> value;
                std::cout << avlTree.average(value) << std::endl;
            }
            else if (command == "Ancestor")
            {
                int value;
                std::cin >> value;
                avlTree.ancestor(value);
            }
            else
            {
                std::cout << "error commond!" << command << std::endl;
            }
        }
    }
}
