/**
 *    author:     stein
 *    created:    2020.11.09 11:28:46
 * 
 *    source: https://github.com/patricksheehan/Huffman-Compression
**/
#include <bits/stdc++.h>

using namespace std;

class Node {
    unsigned char data;
    unsigned int freq;
    unsigned int mn;
    Node *leftC;
    Node *rightC;
  public:
    Node() {}
    Node(const Node& n) {
      data = n.data;
      freq = n.freq;
      leftC = n.leftC;
      rightC = n.rightC;
    }
    Node(unsigned char d, unsigned int f) : data(d), freq(f), mn(d) { }
    Node(Node* rc, Node* lc) {
      freq = rc->freq + lc->freq;
      rightC = rc;
      leftC = lc;
      mn = (rc->mn < lc->mn) ? rc->mn : lc->mn;
    }
    void fillCodeBook(string* codeBook, string& code) {
      if (!leftC && !rightC) {
        codeBook[data] = code;
        return;
      }
      if (leftC) {
        code += '0';
        leftC->fillCodeBook(codeBook, code);
        code.erase(code.end()-1);
      }
      if (rightC) {
        code += '1';
        rightC->fillCodeBook(codeBook, code);
        code.erase(code.end()-1);
      }
    }
    bool operator>(const Node& rhs) {
      if (freq > rhs.freq) {
        return true;
      }
      if (freq < rhs.freq) {
        return false;
      }
      if (freq == rhs.freq) {
        if (mn > rhs.mn) {
          return true;
        }
      }
      return false;
    }
};

class Heap {
    Node **minHeap;
    int heapSize;
  public:
    Heap() {
      heapSize = 0;
      minHeap = new Node*[257];
    }
    void push(Node *newNode) {
      int currentHeapNode = ++heapSize;
      while (currentHeapNode != 1 && *minHeap[currentHeapNode/2] > *newNode) {
        minHeap[currentHeapNode] = minHeap[currentHeapNode/2];
        currentHeapNode = currentHeapNode/2;
      }
      minHeap[currentHeapNode] = newNode;
    }
    void pop() {
      Node* lastNode = minHeap[heapSize];
      minHeap[heapSize--] = minHeap[1];
      int currentHeapNode = 1;
      int child = 1;
      while (child <= heapSize) {
        if (child < heapSize && *minHeap[child] > *minHeap[child+1]) {
          child++;
        }
        if (*minHeap[child] > *lastNode) {
          break;
        }
        minHeap[currentHeapNode] = minHeap[child];
        currentHeapNode = child;
        child *= 2;
      }
      minHeap[currentHeapNode] = lastNode;
    }
    int size() {
      return heapSize;
    }
    Node* top() {
      return minHeap[1];
    }
};

unsigned int freqs[256] = {0};
string codeBook[256];

Node* constructHeap() {
  Heap minHeap;
  Node *nextNode;
  for (int i = 0; i < 256; i++) {
    if (freqs[i]) {
      nextNode = new Node(i, freqs[i]);
      minHeap.push(nextNode);
    }
  }
  Node* node1;
  Node* node2;
  Node* merged;
  while (minHeap.size() > 1) {
    node1 = minHeap.top();
    minHeap.pop();
    node2 = minHeap.top();
    minHeap.pop();
    merged = new Node(node1, node2);
    minHeap.push(merged);
  }
  return minHeap.top();
}

void putOut() {
  cout << "HUFFMA3" << '\0';
  unsigned int i;
  for (int i = 0; i < 256; i++) {
    cout << (char)  (0x000000ff & freqs[i]);
    cout << (char) ((0x0000ff00 & freqs[i]) >> 8);
    cout << (char) ((0x00ff0000 & freqs[i]) >> 16);
    cout << (char) ((0xff000000 & freqs[i]) >> 24); 
  }
  unsigned char nextChar;
  char nextByte = 0;
  int bitCounter;
  cin.clear();
  cin.seekg(0);
  cin >> noskipws;
  while (cin >> nextChar) {
    for (i = 0; i < codeBook[nextChar].size(); i++, bitCounter++) {
      if (bitCounter == 8) {
        cout << nextByte;
        nextByte = 0;
        bitCounter = 0;
      }
      if (codeBook[nextChar][i] == '1') {
        nextByte = nextByte | (0x01 << bitCounter);
      }
    }
  }
  if (bitCounter) cout << nextByte;
}

void compress() {
  unsigned char nextChar;
  cin >> noskipws;
  while (cin >> nextChar) freqs[nextChar]++;
  Node* root = constructHeap();
  string code;
  root->fillCodeBook(codeBook, code);
  putOut();
}

void decompress() {
  cin >> noskipws;
  char magic[8];
  cin.read(magic, 8);
  char nextByte;
  for (int i = 0; i < 256; i++) {
    cin.read((char *) &freqs[i], 4);
  }
  Node* root = constructHeap();
  string code;
  root->fillCodeBook(codeBook, code);
  while (cin >> nextByte) {
    for (int i = 0; i < 8; i++) {
      if ((nextByte >> i) & 0x01) {
        code += '1';
      }else {
        code += '0';
      }
      for (int i = 0; i < 256; i++) {
        if (codeBook[i] == code) {
          if (freqs[i]) {
            cout << (unsigned char) i;
            code.clear();
            --freqs[i];
            break;
          }else return;
        }
      }
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc == 2) {
    if ((argv[1][0] == '-') && (argv[1][1] == 'd')) {
      decompress();
    }
  }else {
    compress();
  }
  return 0;
}


