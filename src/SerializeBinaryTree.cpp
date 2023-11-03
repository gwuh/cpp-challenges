/*
    ######### Problem description: #########
    Given the root to a binary tree, implement serialize(root), which serializes the tree into a string, and deserialize(s), which deserializes the string back into the tree.

    For example, given the following Node class

    class Node:
        def __init__(self, val, left=None, right=None):
            self.val = val
            self.left = left
            self.right = right

    The following test should pass:

    node = Node('root', Node('left', Node('left.left')), Node('right'))
    assert deserialize(serialize(node)).left.left.val == 'left.left'
*/

#include "helpers.hpp"
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

template <typename T>
class BinaryTree {
public:
    struct Node {
        Node() = default;
        Node(const T& data, Node* left = nullptr, Node* right = nullptr)
            : val(data)
            , left(left)
            , right(right)
        {
        }

        ~Node()
        {
            delete left;
            delete right;
        }

        T val {};
        Node* left {};
        Node* right {};
    };
    BinaryTree()
        : root_(new Node())
    {
    }
    BinaryTree(Node* node)
        : root_(node)
    {
    }
    BinaryTree(const T& val)
        : root_(new Node(val))
    {
    }

    ~BinaryTree()
    {
        delete root_;
    }

    constexpr Node* root() const
    {
        return root_;
    }

private:
    Node* root_;
};

// Serialize tree into a string starting from a given node
// Tree nodes must contain values of a type that implements the stream << operator.
template <typename T>
std::string serialize(typename BinaryTree<T>::Node* start)
{
    std::ostringstream serialized {};
    if (start != nullptr) {
        serialized << "val=\"" << start->val << "\",";
        if (start->left != nullptr) {
            serialized << "left={" << serialize<T>(start->left) << "},";
        }
        if (start->right != nullptr) {
            serialized << "right={" << serialize<T>(start->right) << "},";
        }
    }
    return serialized.str();
}

// Deserialize string into Nodes of a BinaryTree<T>
// Where T is any type that implements the stream >> operator.
// Pretty wordy... not a particularly elegant solution here
template <typename T>
typename BinaryTree<T>::Node* deserialize(const std::string& serialized)
{
    using Node = BinaryTree<T>::Node;
    Node* node = new Node();

    // Find the start and end of a matching set of open and close chars
    const auto findScope = [&serialized](char open, char close, size_t off = 0) -> std::pair<size_t, size_t> {
        size_t openPos = serialized.find_first_of(open, off);
        size_t closePos = std::string::npos;
        // Find matching closing char
        unsigned depth = 1;
        for (size_t i = openPos + 1; i < serialized.size(); ++i) {
            char c = serialized[i];
            if (c == close) {
                if (--depth == 0) {
                    closePos = i;
                    break;
                }
            } else if (c == open) {
                ++depth;
            }
        }
        return { openPos, closePos };
    };

    // Deserialize substrings within curly braces into this Node's children
    auto [openPos, closePos] = findScope('{', '}');
    while (openPos != std::string::npos && closePos != std::string::npos) {
        Node* leftOrRight = deserialize<T>(serialized.substr(openPos + 1, closePos - openPos - 1));
        // This is a pretty messy way to find whether it should be a left or right child...
        if (serialized.substr(openPos - 6, 6).find("left") != std::string::npos) {
            node->left = leftOrRight;
        } else {
            node->right = leftOrRight;
        }
        std::tie(openPos, closePos) = findScope('{', '}', closePos);
    };

    // Deserialize the value and store in this Node's val member
    size_t valPos = serialized.find("val");
    if (valPos != std::string::npos) {
        std::tie(openPos, closePos) = findScope('"', '"', valPos);
        if (openPos != std::string::npos && closePos != std::string::npos) {
            std::istringstream ss { serialized.substr(openPos + 1, closePos - openPos - 1) };
            ss >> node->val;
        }
    }

    return node;
}

TEST_CASE("SerializeBinaryTree")
{
    SECTION("Sample BinaryTree<std::string> case")
    {
        using val_t = std::string;
        using Node = BinaryTree<val_t>::Node;

        BinaryTree<val_t> stringTree("root");
        stringTree.root()->left = new Node("left", new Node("left.left"));
        stringTree.root()->right = new Node("right");
        std::string serialized = serialize<val_t>(stringTree.root());

        std::cout << serialized << std::endl;
        auto deserialized = deserialize<val_t>(serialized);

        REQUIRE(deserialize<val_t>(serialize<val_t>(stringTree.root()))->left->left->val == "left.left");
    }
    SECTION("BinaryTree<int> case")
    {
        using val_t = int;
        using Node = BinaryTree<val_t>::Node;

        BinaryTree<val_t> intTree(50);
        intTree.root()->left = new Node(40, new Node(30));
        intTree.root()->right = new Node(60, new Node(55, nullptr, new Node(58)));
        std::string serialized = serialize<val_t>(intTree.root());

        std::cout << serialized << std::endl;
        auto deserialized = deserialize<val_t>(serialized);

        REQUIRE(deserialize<val_t>(serialize<val_t>(intTree.root()))->left->val == 40);
        REQUIRE(deserialize<val_t>(serialize<val_t>(intTree.root()))->right->val == 60);
        REQUIRE(deserialize<val_t>(serialize<val_t>(intTree.root()))->left->left->val == 30);
        REQUIRE(deserialize<val_t>(serialize<val_t>(intTree.root()))->right->left->right->val == 58);
    }
    SECTION("BinaryTree<double> case")
    {
        // using Node = BinaryTree<double>::Node;
        // BinaryTree<double> doubleTree;
        // serialize(doubleTree);
    }
}