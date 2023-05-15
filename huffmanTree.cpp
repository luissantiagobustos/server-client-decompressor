#include "huffmanTree.h"

huffmanTree::huffmanTree(){
  totalSymbols = 0;
  totalSymbols2 = 0;
  root = new rootNode;
}

void huffmanTree::readFile(std::string inputName){
  std::ifstream input;
  input.open(inputName);
  std::string str;
  // gets first line and parse frq and symbol, just we just have frequence of one digit thats why we use str[0] 
  while(getline(input,str)){
    char symbol = str[0];
    int freq = str[2] - '0';
    node* temp = new node(symbol,freq);
    totalSymbols += freq;
    priorityQueue.push_back(temp);
  }
  input.close();
}

void huffmanTree::printVector(){
  // function to check how our vector is behaving
  for(int i = 0; i < priorityQueue.size(); ++i){
    std::cout << "SYMBOL = " << priorityQueue[i]->symbol <<  " FREQ = ";
    std::cout << priorityQueue[i]->freq << std::endl;
  }
  std::cout << std::endl;
}

void huffmanTree::sortVector(){
  // using quick sort since it is really efficient
  quickSort(0, priorityQueue.size()-1);
}

void huffmanTree::swap(node* a, node* b){
  char tempSymbol = a->symbol;
  int tempFreq = a->freq;

  a->symbol = b->symbol;
  a->freq = b->freq;
  b->symbol = tempSymbol;
  b->freq = tempFreq;
}

// partition logic gotten from geeksforgeeks website
int huffmanTree::partition(int start, int end){
    
    int pivotFreq = priorityQueue[start]->freq;
    char pivotSmybol = priorityQueue[start]->symbol;
  
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if(priorityQueue[i]->freq < pivotFreq || ((priorityQueue[i]->freq == pivotFreq) && (priorityQueue[i]->symbol <= pivotSmybol)))
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(priorityQueue[pivotIndex], priorityQueue[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (priorityQueue[i]->freq < pivotFreq || ((priorityQueue[i]->freq == pivotFreq) && (priorityQueue[i]->symbol <= pivotSmybol))) {
            i++;
        }
 
        while (priorityQueue[j]->freq > pivotFreq || ((priorityQueue[j]->freq == pivotFreq) && (priorityQueue[j]->symbol > pivotSmybol))) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap(priorityQueue[i++], priorityQueue[j--]);
        }
    }
    return pivotIndex;
}

void huffmanTree::quickSort(int start, int end){
  if(start >= end)  //base case
    return;
  int p = partition(start,end);
  //sorting left  part
  quickSort(start, p - 1);
  //sorting right part
  quickSort(p + 1, end);
}

node* huffmanTree::popFront(){
  node* temp = new node(priorityQueue[0]->symbol, priorityQueue[0]->freq, priorityQueue[0]->left, priorityQueue[0]->right);
  priorityQueue.erase(priorityQueue.begin());
  return temp;
}

void huffmanTree::insertNode(node* temp){
  priorityQueue.push_back(temp);
  int end = priorityQueue.size() - 1;
  while(end > 0 && ((temp->freq < priorityQueue[end - 1]->freq) || ((temp->freq == priorityQueue[end - 1]->freq) && (temp->symbol <= priorityQueue[end - 1]->symbol)))){
    priorityQueue[end] = priorityQueue[end - 1];
    end--;
  }
  priorityQueue[end] = temp;
}

void huffmanTree::callTree(){
  if(isEmpty()){
    std::cout << "array is empty please insert inputfile" << std::endl;
    return;
  }
  while(priorityQueue.size() > 1){
    node* temp1 = popFront();
    node* temp2 = popFront();
    node* newNode = new node('\n', temp1->freq + temp2->freq, temp1, temp2);
    insertNode(newNode);
  }
  root->curr = popFront();
  int array[totalSymbols-1];  //max height of a huffman tree is the number of symbols - 1
  printTree(root->curr,0,array);
}

bool huffmanTree::isEmpty(){
  if(priorityQueue.size() == 0) return true;
  return false;
}

void huffmanTree::printTree(node* curr, int count, int arr[]){
  if(curr->left != nullptr){
    arr[count] = 0;
    printTree(curr->left,count + 1, arr);
  }
  if(curr->right != nullptr){
    arr[count] = 1;
    printTree(curr->right, count + 1, arr);
  }
  if(curr->left == nullptr && curr->right == nullptr){
    std::cout << "Symbol: " << curr->symbol << ", Frequency: ";
    std::cout << curr->freq << ", Code: ";
    for(int i = 0; i < count; ++i)
      std::cout << arr[i];
    std::cout << std::endl;
  }
}

void huffmanTree::readCompressedFile(std::string fileName){
  std::ifstream input;
  input.open(fileName);
  std::string str;

  while(getline(input,str)){
    int j = 0;
    std::vector<char> sym;
    std::vector<int> pos;
    while(str[j] != ' '){
      sym.push_back(str[j]);
      j++;
    }
    while(j < str.length()){
      if(str[j] != ' '){
        bool status = false;
        int t1;
        int t2;
        int result;
        t1 = str[j] - '0';
        j++;
        if(j < str.length()){
          // Checks if position has 2 digits Note that every position has a maximun of two digits, so we can hardcode it.
          if(str[j] != ' '){
            status = true;
            t2 = str[j] - '0';
            t1 = t1 * 10;
            j++;
          }
        }
        result = t1;
          if(status){
            result += t2;
          }
        pos.push_back(result);
        totalSymbols2 += 1;
      }
      j++;
    }
    root->symbols.push_back(sym);
    root->positions.push_back(pos);
  }
  //std::cout << "TOTAL SYMBOLS= " << totalSymbols2 << std::endl;
  /*for(int i = 0; i < root->symbols.size(); ++i){
    std::cout << "symbol = ";
    for(int j = 0; j < root->symbols.at(i).size(); ++j){
      std::cout << root->symbols.at(i).at(j);
    }
     std::cout << " Positions = ";
     for(int j = 0; j < root->positions.at(i).size(); ++j){
      std::cout << root->positions.at(i).at(j) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;*/

  root->message = new char[totalSymbols2];
  input.close();
}

void huffmanTree::printCompressedFile(){
  for(int i = 0; i < root->symbols.size(); i++){
    for(int j = 0; j < root->symbols[i].size(); j++){
      std::cout << root->symbols[i][j];
    }
    std::cout << " ";
    for(int j = 0; j < root->positions[i].size(); j++){
      std::cout << root->positions[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

char getSymbolFromTree(node* root, const std::vector<char>& symbols, int count){
  if(root->left == nullptr && root->right == nullptr){
    return root->symbol;
  }
  else if(symbols[count] == '0'){
    return getSymbolFromTree(root->left, symbols, count + 1);
  }
  else{
    return getSymbolFromTree(root->right, symbols, count + 1);
  }
}

void error(const std::string& msg)
{
    std::cout << msg << std::endl;
    exit(0);
}

void* getSymbol(void* root_void_ptr){
  rootNode* root_ptr = (rootNode*) root_void_ptr;

  int k = root_ptr->id;
  int n;
  int sizeBuffer = root_ptr->symbols[k].size() + 1;
  char buffer[sizeBuffer];
  char symbol;
  bzero(buffer,sizeBuffer);
  buffer[0] = sizeBuffer + '0';
  for(int i = 1; i < sizeBuffer; ++i){
    buffer[i] = root_ptr->symbols[k].at(i-1);
  }
   n = write(root_ptr->sockfdRoot,buffer,sizeBuffer);
   if (n < 0) 
         error("ERROR writing to socket");
   n = read(root_ptr->sockfdRoot,&symbol,sizeof(char)); 
   if (n < 0) 
         error("ERROR reading from socket");
  // char symbol = getSymbolFromTree(root_ptr->curr, root_ptr->symbols[k], 0);
  //std::cout << root_ptr->positions[k].size() << std::endl;
  /* for(int i = 0; i < root_ptr->positions[k].size(); ++i){
    int index = root_ptr->positions[k].at(i);
    std::cout << index << " ";
  }
  std::cout << std::endl;*/

  for(int i = 0; i < root_ptr->positions[k].size(); ++i){
    int index = root_ptr->positions[k].at(i);
    root_ptr->message[index] = symbol;
  }
  return NULL;
}

void huffmanTree::getMessageThreads(int argc, char *argv[]){

    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;
    /*std::cout << "ARGC= " << argc << std::endl;
    std::cout << "ARGV[0]= " << argv[0] << std::endl;
    std::cout << "ARGC[1]= " << argv[1] << std::endl;
    std::cout << "ARGC[2]= " << argv[2] << std::endl;
    std::cout << "ARGC[3]= " << argv[3] << std::endl;*/
  
    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
  
  root->sockfdRoot = sockfd;
  const int NTHREADS = root->symbols.size();
  pthread_t tid[NTHREADS];
  
  for(int i = 0; i < NTHREADS; ++i){
    root->id = i;
    if(pthread_create(&tid[i],NULL,getSymbol,(void*)root)){
      std::cout << "Error creating the thread" << std::endl;
      return;
    }
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  for(int i = 0; i < NTHREADS; ++i)
    pthread_join(tid[i], NULL);

  close(sockfd);
}

void huffmanTree::printMessage(){
  std::cout << "Original message: ";
  for(int i = 0; i < totalSymbols2; ++i){
    std::cout << root->message[i];
  }
}

int huffmanTree::getSizeSymbols(){
  return priorityQueue.size();
}

node* huffmanTree::getRootNode(){
  return root->curr;
}

huffmanTree::~huffmanTree(){
  /// empty destructor
}