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
#include <string>
#include <type_traits>

template <typename T>
class BinaryTree {
public:
    struct Node {
        Node(const T& data)
            : val(data)
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

    BinaryTree() = default;
    BinaryTree(const T& val)
    {
        root_ = new Node(val);
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
    Node* root_ {};
};

// Only serializing trees of strings for now
std::string serialize(BinaryTree<std::string> b)
{
    return "binary tree of std::string serialized";
}

template <typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;

// Serialize arithmetic types
template <typename T>
requires arithmetic<T>
    std::string serialize(BinaryTree<T> b)
{
    return "binary tree of arithmetic type serialized";
}

TEST_CASE("SerializeBinaryTree")
{
    SECTION("Sample BinaryTree<std::string> case")
    {
        BinaryTree<std::string> stringTree;
        serialize(stringTree);
    }
    SECTION("BinaryTree<int> case")
    {
        BinaryTree<int> intTree;
        serialize(intTree);
    }
    SECTION("BinaryTree<double> case")
    {
        BinaryTree<double> doubleTree;
        serialize(doubleTree);
    }

    // Dummy test
    REQUIRE(true == false);
}