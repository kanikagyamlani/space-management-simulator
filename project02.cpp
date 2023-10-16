#include <bits/stdc++.h>
using namespace std;

/* this project is about Huffman coding, its a coding and encoding implementation which helps reduce the size of a given data to compress it, and helps us to decode it by decompressing it again, its a greedy algorithm */

class HuffTree{
public:
  int val; //this is the frequency
  char letter;
  HuffTree* left; //left represents 0 in binary
  HuffTree* right; // represents 1 in binary

  //constructor
  HuffTree(int val, char c){
    this->val= val;
    this->letter= c;
    this->left= NULL;
    this->right= NULL;
  }
};

vector <pair<int, char>> FrequencyDect (string s){
  map <char, int> mp;
  for (int i=0; i<s.size(); i++){
      mp[s[i]]++;
  }
  vector <pair<int, char>> v;
  for (int i=0; i<s.size(); i++){
    if (mp[s[i]]!=0){
      v.push_back(make_pair(mp[s[i]], s[i]));
      mp[s[i]]=0; //initialising
    }
  }

  // for (int i=0; i<v.size(); i++)
  //     cout<<v[i].second<<" "<<v[i].first<<endl; //frequency & char

  return v;
}

class Compare {
public:
  bool operator()(HuffTree* a, HuffTree* b){
    if (a->val>b->val)
      return true;
    else
      return false;
  }
}; //increasing order of frequencies

void print(priority_queue<HuffTree*, vector <HuffTree*>, Compare> q){
  while (q.size()){
    cout<<q.top()->letter<<" "<<q.top()->val<<endl;
    q.pop();
  }
}

HuffTree* makeTree(vector<pair<int, char>> &frq){
  //frequency and characters
  priority_queue<HuffTree*, vector <HuffTree*>, Compare> q;
  for(int i=0; i<frq.size(); i++){
    q.push(new HuffTree(frq[i].first, frq[i].second));
  }
  print(q);
  while (q.size()>1){
    HuffTree* left = q.top();
    q.pop();
    HuffTree* right= q.top();
    q.pop();

    HuffTree* nd= new HuffTree(left->val+ right->val, '~');
    nd->left=left;
    nd->right= right;
    q.push(nd);
  }

  return q.top(); //size is 1 and it contains the root ie largest node
}// this func returns the root node? 0(n logn)

void Inorder(HuffTree* tree){
  if (tree){
    cout<<tree->val<<endl;
    Inorder(tree->left);
    Inorder(tree->right);
  }
}

//a function to write corresponding binary values of characters
void getValues(HuffTree* root, string s, map<char, string> &vtr){
  if (!root){
    //if root is null
    return;
  }
  if (root->letter!='~'){
    //root is a leaf node: has  letter assigned to it
    vtr[root->letter]=s;
    return;
  }else{
    getValues(root->left, s+"0", vtr);
    getValues(root->right, s+"1", vtr);
  }
}

string decode(HuffTree *tree, string s, int &i){
  string str="";

  while (i<=s.size()){
      if (tree->letter!='~'){
        // its a node with a letter
        str+=tree->letter;
        return str;
      }

      else if (s[i]=='0'){
        if (tree->left){
          tree=tree->left;
          i++;
        }else{
          return str;
        }
      }
      else if (s[i]=='1'){
        if (tree->right){
            tree=tree->right;
            i++;
          }
        else return str;
      }
  }
  return "";
}

int main(){
  string s; getline(cin, s);

  vector <pair <int, char>> frq= FrequencyDect(s);

  sort(frq.begin(), frq.end());
  // for (int i=0; i<frq.size(); i++)
  //     cout<<frq[i].second<<" "<<frq[i].first<<endl;

  map<char, string> vtr;
  HuffTree* tree = makeTree(frq);
  getValues(tree, "", vtr);

  string res="";
  for (auto i: vtr){
      cout<<i.first<<" "<<i.second<<endl;
      // res+=i.second;
  }

  for (auto i: s)
    res+=vtr[i];

  cout<<"******************************"<<endl;
  cout<<s<<endl<<res<<endl;
  cout<<endl;

  // ye poora traverse karega
  // Inorder(tree);
  string back="";
  for (int i=0; i<res.size(); ){
    back+=decode(tree, res, i);
  }
  cout<<back<<endl;
}
