#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include"sha256.h"
using namespace std;

struct Node {
    std::string hash;
    Node* left;
    Node* right;
    Node(string data)
    {
        this->hash = data;
    }
};

struct MerkleTree {
    Node* root;
    MerkleTree(vector<Node*> blocks);
    ~MerkleTree();
    void draw(Node* n, int indent);
    void dlt(Node* n);
};


string sha256(string str) {
    Sha256 hash0;
    string hash_str = hash0.getHexMessageDigest(str);
    return hash_str;
}


void printNodeHashes(vector<Node*> v) {
    for (unsigned int a = 0; a < v.size(); a++) {
        cout << v[a]->hash << endl;
    }
}


MerkleTree::MerkleTree(vector<Node*> blk)
{
    vector<Node*> nodes;
    while (blk.size() != 1) {
        for (unsigned int l = 0, n = 0; l < blk.size(); l = l + 2, n++) {
            if (l != blk.size() - 1) { 
                nodes.push_back(new Node(sha256(blk[l]->hash + blk[l + 1]->hash))); 
                nodes[n]->left = blk[l]; 
                nodes[n]->right = blk[l + 1];
            }
            else {
                nodes.push_back(blk[l]);
            }
        }
        blk = nodes;
        nodes.clear();

    }
    this->root = blk[0];
}

MerkleTree::~MerkleTree()
{

    dlt(root);
}



void MerkleTree::draw(Node* n, int space)
{
    if (n)
    {
        if (n->left) {
            draw(n->left, space + 4);
        }
        if (n->right) {
            draw(n->right, space + 4);
        }
        if (space) {
            std::cout << setw(space) << ' ';
        }
        std::cout << n->hash[0] << "\n ";
    }
}

void MerkleTree::dlt(Node* n)
{
    if (n) {
        dlt(n->left);
        dlt(n->right);
        n = NULL;
        delete n;
    }
}

int main() {
    vector<Node*> leaves;
    for (int i = 0; i < 10; i++)
    {       
        leaves.push_back(new Node(sha256("1")));  
        leaves[i]->left = NULL;
        leaves[i]->right = NULL;
    }
    MerkleTree* hashTree = new MerkleTree(leaves);
    cout << hashTree->root->hash;
    return 0;
}
