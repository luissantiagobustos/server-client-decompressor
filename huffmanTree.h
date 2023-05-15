#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <unistd.h> 
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <unistd.h>
#include <stdio.h>


struct node{
  node(char s, int f, node* l = nullptr, node* r = nullptr){
    symbol = s;
    freq = f;
    left = l;
    right = r;
  }
  char symbol;
  int freq;
  node* left;
  node* right;
};
// node where will be passed to the threads to retrieve information of each symbol to store in the massage array
struct rootNode{
  node* curr;
// vectors to store each n character for each n thread
  std::vector<std::vector<char>> symbols;
  std::vector<std::vector<int>> positions;
  int id;
  char* message;
  int sockfdRoot;

};

class huffmanTree{
private:
  std::vector<node*> priorityQueue;
  int totalSymbols;
  int totalSymbols2;
public:
  rootNode* root;
  huffmanTree();
  void readFile(std::string);
  void printVector();
  void sortVector();
  void quickSort(int,int);
  int partition(int,int);
  void swap(node*,node*);
  node* popFront();
  void insertNode(node*);
  bool isEmpty();
  void callTree();
  void printTree(node*,int,int[]);
  void readCompressedFile(std::string);
  void printCompressedFile();
  void getMessageThreads(int argc, char *argv[]);
  void printMessage();

  int getSizeSymbols();
  node* getRootNode();
  ~huffmanTree();
};

#endif