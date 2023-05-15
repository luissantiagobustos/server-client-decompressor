// A simple server in the internet domain using TCP
// The port nu1mber is passed as an argument

// Please note this is a C program
// It compiles without warnings with gcc

//#include <unistd.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <iostream>
#include "huffmanTree.h"


void error2(const std::string &msg)
{
   std::cout << msg  << std::endl;
   exit(1);
}

char getSymbolFromTree2(node* root, const std::vector<char>& symbols, int count){
  if(root->left == nullptr && root->right == nullptr){
    return root->symbol;
  }
  else if(symbols[count] == '0'){
    return getSymbolFromTree2(root->left, symbols, count + 1);
  }
  else{
    return getSymbolFromTree2(root->right, symbols, count + 1);
  }
}


int main(int argc, char *argv[])
{
   huffmanTree obj1;
   obj1.readFile(argv[2]);
   int sizeSymbols = obj1.getSizeSymbols();
   obj1.sortVector();
   obj1.callTree();
   node* curr = obj1.getRootNode();

   int sockfd, newsockfd, portno, clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int n;
   if (argc < 2)
   {
      fprintf(stderr, "ERROR, no port provided\n");
      exit(1);
   }
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0)
      error2("ERROR opening socket");
   bzero((char *)&serv_addr, sizeof(serv_addr));
   portno = atoi(argv[1]);
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   if (::bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
            error2("ERROR on Binding");

   listen(sockfd, sizeSymbols);
   clilen = sizeof(cli_addr);
   newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *)&clilen);
   if (newsockfd < 0)
            error2("ERROR on accept");


   pid_t pid;
   for(int i = 0; i < sizeSymbols; ++i){
      pid = fork();
      if(pid == 0){

         bzero(buffer, 256);
         char value;
         n = read(newsockfd, buffer, 255);
         if (n < 0)
            error2("ERROR reading from socket");
         //printf("Here is the message: %s\n", buffer);
         int sizeArray = buffer[0] - '0';
         std::vector<char> symbols;
         for(int i = 1; i < sizeArray; ++i){
            symbols.push_back(buffer[i]);
         }
         /*for(int i = 0; i < symbols.size(); ++i){
            std::cout << symbols[i];
         }
         std::cout << std::endl;*/

         value = getSymbolFromTree2(curr, symbols, 0);
         //std::cout << value << std::endl;
         n = write(newsockfd, &value, sizeof(char));
         if (n < 0)
            error2("ERROR writing to socket");
         _exit(0);
      }
   }
   
   for(int i = 0 ; i < sizeSymbols; ++i){
      wait(0);
   }
   close(newsockfd);
   close(sockfd);
   return 0;
}
