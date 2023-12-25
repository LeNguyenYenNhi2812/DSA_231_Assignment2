#include "main.h"
int MAXSIZE;	// NUMBER OF MAX khu

class Node 
{
public:	
	int result;
    Node* pLeft, * pRight;
	int ID;
	
	
	Node(int result) 
	{
	this->result=result;
	this->ID=result%MAXSIZE;
	this->pLeft=nullptr;
	this->pRight=nullptr;
	};
	~Node() {};
	

};


class HuffNode {
public:
 char ch;
	int freq;
	HuffNode* pLeft=nullptr;
	HuffNode* pRight=nullptr;

	HuffNode(HuffNode* pLeft, HuffNode* pRight)
	{
		this->ch='!';
		this->freq=pLeft->freq+pRight->freq;
		this->pLeft=pLeft;
		this->pRight=pRight;
	}
	HuffNode(char ch, int freq)
	{
		this->ch=ch;
		this->freq=freq;
	}
	~HuffNode()
	{
		pLeft=nullptr;
		pRight=nullptr;
	}
};

class HuffmanTree
{
public:
HuffNode* root;

void printNSpace(int n) {
    for (int i = 0; i < n - 1; i++)
      cout << " ";
  }

  void printTreeStructure(HuffNode *root) {
    int height = getHeight(root);
    if (!root) {
      cout << "NULL\n";
      return;
    }
    queue<HuffNode *> q;
    q.push(root);
    HuffNode *temp;
    int count = 0;
    int maxNode = 1;
    int level = 0;
    int space = pow(2, height);
    printNSpace(space / 2);
    while (!q.empty()) {
      temp = q.front();
      q.pop();
      if (temp == nullptr) {
        cout << " ";
        q.push(nullptr);
        q.push(nullptr);
      } else {
        if (temp->ch != '!') cout << temp->ch;
        else cout << temp->freq;
        q.push(temp->pLeft);
        q.push(temp->pRight);
      }
      printNSpace(space);
      count++;
      if (count == maxNode) {
        cout << endl;
        count = 0;
        maxNode *= 2;
        level++;
        space /= 2;
        printNSpace(space / 2);
      }
      if (level == height)
        return;
    }
  }
//Build a Huffman tree from a collection of frequencies
static bool compareHuffman(HuffNode* a, HuffNode* b)
{
	return a->freq < b->freq; 
	//  if (a->freq != b->freq) {
    //     return a->freq < b->freq; // Sắp xếp theo tần suất tăng dần
    // } else {
    //     // Nếu tần suất bằng nhau, sắp xếp theo thứ tự xuất hiện trong cây
    //     return find(arrHuffman.begin(), arrHuffman.end(), a) < find(arrHuffman.begin(), arrHuffman.end(), b);
    // }
	
}
vector<HuffNode*> vectorToHuffNode(vector<pair<char,int>> arr)
{
	
	vector<HuffNode*> ans;
	for(unsigned i=0;i<arr.size();++i)
	{
		//cout<<arr[i].first<<"-"<<arr[i].second<<" ";
		HuffNode* tmp1= new HuffNode (arr[i].first,arr[i].second);
		ans.push_back(tmp1);

	}
	return ans;
}
pair<HuffNode*, string> findParent(HuffNode* root, HuffNode*node){
    if(!root) return make_pair(nullptr,"");
    
    if(root->pLeft == node) return make_pair(root, "pLeft");
    else if (root->pRight == node) return make_pair(root, "pRight");
    auto leftResult = findParent(root->pLeft, node);
    if (leftResult.first) {
        return leftResult;
    }
    auto rightResult = findParent(root->pRight, node);
    if (rightResult.first) {
        return rightResult;
    }
    return make_pair(nullptr, "");
}
HuffNode* buildHuff(vector<HuffNode*> arrHuffman) 
{
   bool flag=true;
   while (arrHuffman.size()>1 && flag)
   {
	
		HuffNode* tmp1 = arrHuffman.front(); 
        arrHuffman.erase(arrHuffman.begin());
        HuffNode* tmp2 = arrHuffman.front();
        arrHuffman.erase(arrHuffman.begin());
        HuffNode* newNode = new HuffNode(tmp1, tmp2);
        this->root = newNode;
		// checkBalande(this->root); // ktra xem can bang ko
		//cout<<"TRC khi xoay"<<endl;
		//printTreeStructure(root);
		rotate(this->root);
		cout<<"SAU khi xoay"<<endl;
		printTreeStructure(root);
        arrHuffman.push_back(this->root);
        stable_sort(arrHuffman.begin(), arrHuffman.end(), compareHuffman);
// xoay cay pla pla ch lam
 	// sort(arrHuffman.begin(), arrHuffman.end(), [&arrHuffman](HuffNode* a, HuffNode* b) {
    //         if (a->freq != b->freq) {
    //             return a->freq < b->freq; // Sort by frequency in ascending order
    //          } else {
    //              // If frequencies are equal, maintain the order of appearance in the original vector
    //             //return a<b;
	// 			return find(arrHuffman.begin(), arrHuffman.end(), a) < find(arrHuffman.begin(), arrHuffman.end(), b);
    //         }
    //     });
   }
return arrHuffman[0];
}
void encodeHuffman(HuffNode* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (root == nullptr) {
        return;
    }

    // If the current node is a leaf, assign its binary code
    if (!root->pLeft && !root->pRight) {
        huffmanCodes[root->ch] = code;
    }

    // Traverse left and append '0' to the code
    encodeHuffman(root->pLeft, code + '0', huffmanCodes);

    // Traverse right and append '1' to the code
    encodeHuffman(root->pRight, code + '1', huffmanCodes);
}
void rotate(HuffNode*& root)
{
	if(root==nullptr) return;
    bool flag = false; // check cay co cb khong
    int num = 3;
    while (num>0 && !flag)
	{
	HuffNode* unBalanceNode=nullptr;
    findNodeNotBalance(this->root,unBalanceNode);
    if (!flag)
		{
		if(unBalanceNode==nullptr) 
		{
			flag=true;
			//return;
		}

    //TH1: root: cập nhật root
	if(unBalanceNode==this->root)
	{
		HuffNode* newNode=ToRotate(unBalanceNode);
		//delete this->root;
		this->root=newNode;
		//return;
	}
    // xoay (return node)
    // delete root
    // this->root = ...
    

    //TH2: Không phải là root
   // Tìm cha nó, temp
	else
	{
	pair<HuffNode*, string> parent=findParent(this->root,unBalanceNode);

   // gọi hàm xoay, (return node)
   HuffNode* newNode=ToRotate(unBalanceNode);
   if(parent.second=="pLeft")
   {
	parent.first->pLeft=newNode;
   }
   else if(parent.second=="pRight")
   {
	parent.first->pRight=newNode;
   }
	}
		}
		num--;
 	}
}
HuffNode *rightRotate(HuffNode *y)  
{  
    HuffNode *x = y->pLeft;  
    HuffNode *T2 = x->pRight;  
  
    // Perform rotation  
    //x->pLeft = y; 
	x->pRight=y; 
   // y->pRight = T2; 
	y->pLeft=T2;  
  
    // Return new root  
    return x;  
}  
  

HuffNode *leftRotate(HuffNode *x)  
{  
    HuffNode *y = x->pRight;  
    HuffNode *T2 = y->pLeft;  
  
    // Perform rotation  
    y->pLeft = x;  
    x->pRight = T2;  
    // Return new root  
    return y;  
}  

HuffNode* ToRotate(HuffNode* node)
{
	int tall=getBalance(node);
	 //!!!!!!!!!!!!!!!!!!!!!!!!!Left Left Case  
    if (tall > 1 &&  getBalance(node->pLeft)>=0)  
        return rightRotate(node);  
	// !!!!!!!!!!!!!!!!!!!!!!!!Right Right Case  
    else if (tall < -1 && getBalance(node->pRight)<=0)  
        return leftRotate(node);  
  
    //!!!!!!!!!!!!!!!!!!!!!!!!! Left Right Case  
    else if (tall > 1 && getBalance(node->pLeft)<0 )  
    {  
        node->pLeft = leftRotate(node->pLeft);  
        return rightRotate(node);  
    }  
  
    // !!!!!!!!!!!!!!!!!!!!!!!!!Right Left Case  
   else if (tall < -1 && getBalance(node->pRight)>0)  
    {  
        node->pRight = rightRotate(node->pRight);  
        return leftRotate(node);  
    }  
  return nullptr;
}
//Get Balance factor of node N  
int getBalance(HuffNode *N)  
{  
    if (N == nullptr)  
        return 0;  
    return getHeight(N->pLeft) - getHeight(N->pRight);  
}  
  
 
void  getHeight(HuffNode* root, int count, int& height)
{
    if(root==nullptr) return;
    count++;
    if(count>height) height=count;
    getHeight(root->pLeft,count,height);
    getHeight(root->pRight,count,height);
}

int getHeight(HuffNode* root) {
    // TODO: return height of the binary tree.
    if(root==nullptr) return 0;
    int height=0;
    getHeight(root,0,height);
    return height;
}

void findNodeNotBalance(HuffNode* root,HuffNode*& unBalanceNode)
{
	if (root==nullptr)
	{
		return;
	}
	int tall=getBalance(root);
	if(tall==0 || tall==-1 || tall==1)
	{
		findNodeNotBalance(root->pLeft,unBalanceNode);
		if(unBalanceNode!=nullptr) return;
		findNodeNotBalance(root->pRight,unBalanceNode);
		if(unBalanceNode!=nullptr) return;
	}
	else 
	{
		unBalanceNode=root;
		return;
	}

}

void printIn(HuffNode* root)
{
if(root->pLeft) printIn(root->pLeft);
if(root->ch!='!')
cout<<root->ch<<endl;
else
cout<<root->freq<<endl;		
if(root->pRight) printIn(root->pRight);
}
void printIn()
{
	if(root==nullptr) return;
	printIn(root);
}
};
class BST
{
public:
    Node* root;
	vector<Node*> OrderCus;
    int count; // so luong khach
    BST()  
	{
		root=nullptr;
		
	}
	BST(Node* root)
	{
		this->root=root;
		
	}
    ~BST(){};

   Node* addBST(Node* root, int result)
 {
	//cout<<" da add node " << result<<endl;
    if(root==nullptr){
        count++;
        return  new Node(result);
		
    } 
    if(result<root->result) root->pLeft=addBST(root->pLeft,result);
    else root->pRight=addBST(root->pRight,result);
    return root;
	
}
void addBST(Node* node){
    //TODO
	//cout<<" da add BST "<<node->ID+1<<endl;
    root=addBST(root,node->result);
	OrderCus.push_back(node);
   
}
Node *min(Node *node)
{
    Node *current = node;
    while (current && current->pLeft != nullptr)
        current = current->pLeft;
    return current;
}

Node* deleteNode(Node* root, int result)
{
    if(!root) return nullptr;
    
    if (result < root->result)
        root->pLeft = deleteNode(root->pLeft, result);
    else if (result > root->result)
        root->pRight = deleteNode(root->pRight, result);
    else
    {
        if (root->pLeft == nullptr)
        {
            
            Node *temp = root->pRight;
            delete root;
            return temp;
        }
        else if (root->pRight == nullptr)
        {
           
            Node *temp = root->pLeft;
            delete root;
            return temp;
        }
        Node *temp = min(root->pRight);
        root->result = temp->result;
        root->pRight = deleteNode(root->pRight, temp->result);
    }
    return root;
}


void deleteNodeBST(int result){
    //TODO
	if(root==nullptr) return;
    root=deleteNode(root,result);
    count--;
	// không biết lúc xóa khách có cần xóa cả trong vector lưu thứ tự không. giả bộ xóa đại
	OrderCus.erase(OrderCus.begin());
}
void printInOrder(Node* root)
{ 
	if (root==nullptr) return; 
	if(root->pLeft!=nullptr)
	printInOrder(root->pLeft);
	cout<<root->result<<endl;
	if(root->pRight!=nullptr)
	printInOrder(root->pRight);
}
void printInOrder()
{
	//cout<<"print in order"<<endl;
	if (this->root==nullptr) return;
	printInOrder(this->root);
}
void postOrder(Node* root, vector<Node*>& ans)
{
	if(root==nullptr) return;
	if(root->pLeft) postOrder(root->pLeft,ans);
	if(root->pRight) postOrder(root->pRight,ans);
	ans.push_back(root);
}
vector<Node*> postOrder()
{
	vector<Node*> ans;
	if(root==nullptr) return ans;
	postOrder(root,ans);
	return ans;
}
};

class ResHashTable // hash table
{
public:
	BST* hash;
	int count;
	
	 
	 void setHash(int max) {
        hash = new BST[max];
        count = 0;
    }
	int getHash(int ID)
	{
		return ID;
	}
	
	void insert(Node* node) 
	{
   // cout<<"inser gojo res"<<endl;
    hash[node->ID].addBST(node);
    this->count++;
	}
	void remove(Node* node)
	{

	}
};

// class Heap
// {
// 	public:
// 	int num=0;
// 	int lable; // ID 
// 	deque<Node*> dq;
// 	Heap(int lable)
// 	{
// 		this->num=0;
// 		this->lable=lable;
// 	}
// 	void addHeap(Node* node)
// 	{
// 		cout<<"da add vao heap";
// 		dq.push_back(node); 
// 		this->num++;
// 	}
// 	void removeHeap(Node* node)
// 	{
// 		cout<<" da toi removeHeap" << endl;
// 		int len=num;
// 		while(len>0)
// 		{
// 			Node* top=dq.front();
// 			dq.pop_front();
// 			if (top==node) 
// 			{
// 				cout<<"da xoa"<<node->result<<endl;
// 				num--;
// 				break;
// 			}
// 			else
// 			{
// 				dq.push_back(top);
// 				len--;
// 			}

// 		}	
		
// 	}

// };
class ResMinHeap
{
    
 class NodeHeap;
public:
    vector<string> KEITEIKEN_PRINT;
 
 private:
 vector<NodeHeap* > areaTable; 
 // nơi lưu trữ các khu vực trong nha hang
 list<NodeHeap* > LRU; //! Least Recently Used 
 private:
 bool LRUOrder(NodeHeap* node1, NodeHeap* node2) {
    auto it1 = find(LRU.begin(), LRU.end(), node1);
    auto it2 = find(LRU.begin(), LRU.end(), node2);

        return distance(LRU.begin(), it1) < std::distance(LRU.begin(), it2);
}
 void ReHeap_down(int index)
 {
	 int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int smallest = index;
    int arrTable_size=areaTable.size();
    // Find the index of the smallest element among the node and its children
    if (leftChild < arrTable_size &&
        (areaTable[leftChild]->size() < areaTable[smallest]->size() ||
         (areaTable[leftChild]->size() == areaTable[smallest]->size() &&
          LRUOrder(areaTable[leftChild], areaTable[smallest])))) {
        smallest = leftChild;
    }

    if (rightChild < arrTable_size &&
        (areaTable[rightChild]->size() < areaTable[smallest]->size() ||
         (areaTable[rightChild]->size() == areaTable[smallest]->size() &&
          LRUOrder(areaTable[rightChild], areaTable[smallest])))) {
        smallest = rightChild;
    }

    // If the smallest element is not the current node, swap them and continue re-heapify
    if (smallest != index) {
        swap(areaTable[index], areaTable[smallest]);
        ReHeap_down(smallest); // Recursive call to continue re-heapify
    }
 }
 void ReHeap_up(int index)
 {
 int parent = (index - 1) / 2;

    // If the current node is smaller than its parent, swap them and continue re-heapify
    if (index > 0 && areaTable[index]->ID < areaTable[parent]->ID) {
        swap(areaTable[index], areaTable[parent]);
        ReHeap_up(parent); // Recursive call to continue re-heapify
    }
 }
 void moveTop(NodeHeap* node)
 {
	 auto it = find(LRU.begin(), LRU.end(), node);

    // If the node is not in LRU, add it to the front
    if (it == LRU.end()) {
        LRU.push_front(node);
    } else {
        // If the node is already in LRU, move it to the front
        LRU.erase(it);
        LRU.push_front(node);
    }
 }
 void removeNode(NodeHeap* node)
 {
	auto it = find(LRU.begin(), LRU.end(), node);

    // Check if the node was found before attempting to erase it
    if (it != LRU.end()) {
        LRU.erase(it); // Erase the node from the LRU list
    }
 }
 public:
 void insertAreaTable(int result)
{
	int ID = result % MAXSIZE;
	int index=-1;
	for(unsigned i=0;i<areaTable.size();++i)
	{
		if(areaTable[i]->ID==ID) index=i;
	}
	if(index == -1)
	{
 	areaTable.push_back(new NodeHeap(ID));
 	index = areaTable.size() - 1;													
 	}
	areaTable[index]->insertNodeHeap(result); // them khach vao tung khu vuc
	this->moveTop(areaTable[index]); // cập nhật danh sách LRU thông qua hàm moveT op
	this->ReHeap_down(index);
}
 void remove_KEITEIKEN(int number)
 {
	if(areaTable.size() <= 0) return;

 //* đuổi num khách hàng tại num khu vực
 int numberRemove = number;
 while(areaTable.size() != 0 && number != 0)
 {
//cout << "remove customers in the area ID = " << areaTable[0]->ID ;
 areaTable[areaTable.size()-1]->removeNodeHeap(numberRemove);

 
// hàng xuống vì đang ở đầu hàng
 if(areaTable[0]->size() == 0)
 {
 swap(areaTable[0], areaTable[areaTable.size() - 1]);
 //! xóa nó khỏi danh sách liên kết
 this->removeNode(areaTable[areaTable.size() - 1]);
 delete areaTable[areaTable.size() - 1];

 //! xóa trong heap nữa
 areaTable.pop_back();
 }
 this->ReHeap_down(0);
 number --;
 }
 }
 void print_pre_order(int index, int number)
 {
    int thisareaTable_size=this->areaTable.size();
 if(index >= thisareaTable_size) return;

 this->areaTable[index]->print(number);
 print_pre_order(index * 2 + 1, number);
 print_pre_order(index * 2 + 2, number);
 }
 void print_CLEAVE(int number)
{
	print_pre_order(0, number);
}
 
 private:
 class NodeHeap
 {
    
 private:
 int ID;
 list<int> head;
 friend class ResMinHeap;
 public:
 NodeHeap(int ID) : ID(ID) {}
 int size() const { return head.size(); }
 //* thêm vô đầu danh sách
 void insertNodeHeap(int result)
 {
	head.push_front(result);
 }
//thêm khách hàng vào đầu danh sách
 void removeNodeHeap(int number)
 {
	for (int i = 0; i < number && !head.empty(); ++i) 
	{
        //cout<<"hello";
        cout << head.back() << "-"<<ID+1<<endl; 
     //  string ans=to_string(head.back())+"-"+to_string(ID+1);
    //    areaTable[i].
    //     KEITEIKEN_PRINT.push_back(ans);
        head.pop_back(); // Remove the element from the end
    }
    
 }

 void print(int number)
 {
	for(list<int>::iterator it = head.begin(); number > 0 && it != head.end();++it, --number)
	 {
	cout<<ID+1<<"-"<<*it<<"\n";
 	}
 }

};
 };
// class ResMinHeap
// {
// public:
// Heap** heapArr;
// int heap_size;
// Heap** heapCapacity;
// vector<Node*> deleleCus;
// void printDeletaCus()
// {
// 	for (int i=0;i<deleleCus.size();++i)
// 	{
// 		cout<<deleleCus[i]->result<<endl;
// 	}
// }
// void setHeap(int max)
// {
// 	heapCapacity= new Heap* [max];
	
// 	for (int i = 0; i < max; ++i)
//         {
//             heapCapacity[i] = new Heap(i);
//         }
// 	heapArr=heapCapacity; //????
// }
// void insert(Node* node)
// {
// 	cout<<"da them vao ResMinHeap"<<endl;
	
// 	heapCapacity[node->ID]->addHeap(node); cout<<"xong heap capa"<<endl;
// 	//reheap như lý thuyết
	
// }
// void remove(Heap* node)
// {

// }
// // method to heapify a subtree with the root at given index i
//     void MinHeapify(int i){
//         /* A recursive method to heapify 'heapArr' */
//         int l = left(i);
//         int r = right(i);

//         int smallest = i;
//         if (l < heap_size && heapArr[l] < heapArr[i])
//             smallest = l;
//         if (r < heap_size && heapArr[r] < heapArr[smallest])
//             smallest = r;

//         if (smallest != i){
//             swap(heapArr[i], heapArr[smallest]);
//             MinHeapify(smallest);
//         }
//     }

//     // method to get index of parent of node at index i
//     int parent(int i){ return (i-1)/2; }

//     // method to get index of left child of node at index i
//     int left(int i){ return (2*i + 1); }

//     // method to get index of right child of node at index i
//     int right(int i){ return (2*i + 2); }

//     // method to remove minimum element (or root) from min heap
//     Heap* extractMin(){
//         if (heap_size <= 0)
//             return INT_MAX;
//         if (heap_size == 1){
//             heap_size--;
//             return heapArr[0];
//         }

//         // remove the minimum value from the heap.
//         Heap* root = heapArr[0];
//         heapArr[0] = heapArr[heap_size-1];
//         heap_size--;
//         MinHeapify(0);

//         return root;
//     }

//     // method to decrease key value of key at index i to new_val
//     void decreaseKey(int i, int new_val){
//         heapArr[i] = new_val;
//         while (i != 0 && heapArr[parent(i)] > heapArr[i]){
//             swap(heapArr[i], heapArr[parent(i)]);
//             i = parent(i);
//         }
//     }

//     // Returns the minimum key (key at root) from min heap
//     Heap* getMin(){ return heapArr[0]; }

//     // method deletes key at index i
//     // (It first reduced value to minus infinite, then calls extractMin() )
//     void deleteKey(int i){
//         decreaseKey(i, INT_MIN);
//         extractMin();
//     }

//     // method to inserts a new key 'k'
//     void insertKey(Node* node){
// 		this->heap_size+=1;
// 		if(heapCapacity[node->ID]->num!=0)
// 		{
// 			heapCapacity[node->ID]->addHeap(node);
// 			//heapCapacity[node->ID]->
// 		}
		// int temp=findIndex(node);
		// changeKey(temp,1);
        

        // Inserting the new key at the end
        // int i = heap_size;
        // heapArr[heap_size++] = k;

        // while (i != 0 && heapArr[parent(i)] > heapArr[i]){
        //     swap(heapArr[i], heapArr[parent(i)]);
        //     i = parent(i);
        // }
    //}
//};


ResHashTable GojoRes;
ResMinHeap SukunaRes;
//HuffmanTree Hufftree;
vector<string> arrNameCus;

bool compare(pair<char, int> a, pair<char, int> b) { // hmmm con loi trong nay
    // Sort by frequency in descending order
    if (a.second < b.second) { //???
        return true;
    }

    if (a.second == b.second)
	{
     if (isupper(a.first) && islower(b.first)) 
        //return true;
		return false;
     else if (islower(a.first) && isupper(b.first)) 
        //return false;
		return true;
	else 
	return a.first < b.first;
	}
    // Sort by character value if they are of the same type and frequency
   return false;
}
vector<pair<char, int>> getFreq(string name)
{
	unordered_map<char,int> mapCus;	
	for (char i : name)
	{
		mapCus[i]++; 
	}
	vector<pair<char, int>> arrFreq(mapCus.begin(), mapCus.end());
	//sort(arrFreq.begin(), arr.end(), compare);
	// for (const auto& pair : arrFreq) {
	// 	cout<<".......";
    //     cout << pair.first << ": " << pair.second << endl;
		
    // }
	return arrFreq;	
}
vector<pair<char, int>> Caesar(string name, string& stringResult0)
{
	string nameCaesar="";
	// ĐẾM TẦN SỐ MỖI KÍ TỰ, MÃ HÓA
	vector<pair<char, int>> arrFreq=getFreq(name);
	for(const auto& pair : arrFreq)
	{
		char charShift = pair.first;

        if (isalpha(charShift)) {
            char base = isupper(charShift) ? 'A' : 'a';
            int shift = charShift - base;
            int newShift = (shift + pair.second) % 26;

            charShift = base + newShift;
        }
		for(int j=0;j<pair.second;++j)
        nameCaesar+= charShift;
	}
	// MÃ HÓA XONG CỘNG DỒN LẠI SORT
	unordered_map<char,int> mapHuffman;
	for (char i : nameCaesar)
	{
		mapHuffman[i]++; 
	}
	vector<pair<char, int>> arr(mapHuffman.begin(), mapHuffman.end());
	sort(arr.begin(), arr.end(), compare); //: chưa sort
	for (const auto& pair : arr) 
	{
		cout << pair.first << ": " << pair.second << endl;
    }
	 unordered_map<char,int> mapCus;	
	for (char i : name)
	{
		mapCus[i]++; 
	}
	 for(auto& i : name)
	 {
	 if(isupper(i))
	 stringResult0+=(i-'A'+mapCus[i])%26+'A';
	 else 
	  stringResult0+=(i-'a'+mapCus[i])%26+'a';
	 }
	//cout<<"hello "<< nameCaesar<<endl;
	return arr;

}



void begin()
{
	 GojoRes.setHash(MAXSIZE);
	// SukunaRes.setHeap(MAXSIZE);
}
void print(HuffNode* root) // check cây huffman 
{
	if(root->pLeft) print(root->pLeft);
	cout<<root->ch<<"__"<<root->freq<<endl;
	if(root->pRight) print(root->pRight);
}
int binaryToDecimal(string str)
{
	int binarynum=stoi(str);
    int decimalnum = 0, temp = 0, remainder;
    while (binarynum!=0)
    {
        remainder = binarynum % 10;
        binarynum = binarynum / 10;
        decimalnum = decimalnum + remainder*pow(2,temp);
        temp++;
    }
    return decimalnum;
}

void LAPSE(string name)
{
	//cout<<"LAPSE"<<endl;
	//cout<<name<<endl;
	
	string stringResult0="";
	 vector<pair<char,int>> arrFreq=getFreq(name);
	 if(arrFreq.size()<3) return; // lát nhớ giữ lại nha :(
    arrNameCus.push_back(name);
	 vector<pair<char, int>> arr=Caesar(name,stringResult0); // 
	
	HuffmanTree Hufftree;
	HuffNode* root =Hufftree.buildHuff(Hufftree.vectorToHuffNode(arr));
	// đang mã hóa cây huffman
	unordered_map<char, string> huffmanCodes;
    Hufftree.encodeHuffman(root, "", huffmanCodes);
	
	string stringResult="";
	
	cout<<"!!!!!!!   "<<stringResult0<<endl;
    for (const auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }
	// thay mã vào chữ ban đâu fsau khi ceasar
    int stringResult0_size=stringResult0.size();
	 for(long long i=0;i<stringResult0_size;++i)
	 { //cout<<arr[i].first<<arr[i].second<<"hello"<<endl;
		for(const auto& pair : huffmanCodes)
		{

			
			if(stringResult0[i]==pair.first)
			{
			stringResult+=pair.second;
			break;
			}
		}
	 }
	 cout<<"NHI PHAN: "<<stringResult;
	 string stringResultFinal="";
	 for(long long i=stringResult.length()-1;i>=0;--i)
	 {
		if(stringResultFinal.length()<10)
		stringResultFinal+=stringResult[i];
		else break;
	 }
	 cout<<"day string result ch lay phai trai "<<stringResultFinal<<endl;
	
	int result=binaryToDecimal(stringResultFinal);
	 cout<<"result cuoi cung"<<result <<endl;

	
	
	Node* newCus=new Node (result);
	if (newCus->result%2==1)
	{
	GojoRes.insert(newCus); 
	//cout<<" gojo res dc goi"<<endl;
	}
	else
	{ 
		SukunaRes.insertAreaTable(result);
		//cout<<"sukuna res dc goi"<<endl;
	}
	
}

//!!!!! tính hoán vị của cây bst
void calculateFact(int fact[], int N)
{
    fact[0] = 1;
    for (long long int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i;
    }
}
 
// Function to get the value of nCr
int nCr(int fact[], int N, int R)
{
    if (R > N)
        return 0;
 
    // nCr= fact(n)/(fact(r)*fact(n-r))
    int res = fact[N] / fact[R];
    res /= fact[N - R];
 
    return res;
}
 
// Function to count the number of ways
// to rearrange the array to obtain same BST
int countWays(vector<Node*>& arr, int fact[])
{
    // Store the size of the array
    int N = arr.size();
 
    // Base case
    if (N <= 2) {
        return 1;
    }
 
    // Store the elements of the
    // left subtree of BST
    vector<Node*> leftSubTree;
 
    // Store the elements of the
    // right subtree of BST
    vector<Node*> rightSubTree;
 
    // Store the root node
    Node* root = arr[0];
 
    for (int i = 1; i < N; i++) {
 
        // Push all the elements
        // of the left subtree
        if (arr[i]->result < root->result) {
            leftSubTree.push_back(arr[i]);
        }
 
        // Push all the elements
        // of the right subtree
        else {
            rightSubTree.push_back(arr[i]);
        }
    }
 
    // Store the size of leftSubTree
    int N1 = leftSubTree.size();
 
    // Store the size of rightSubTree
   // int N2 = rightSubTree.size();
 
    // Recurrence relation
    int countLeft= countWays(leftSubTree,fact);
    int countRight= countWays(rightSubTree,fact);
 
    return nCr(fact, N - 1, N1) * countLeft * countRight;
}
void KOKUSEN()
{
	//cout<<"KOKUSEN"<<endl;
	for(int z=0;z<MAXSIZE;++z)
	{
		if(GojoRes.count<=0) break;
	//cout<<z<<endl;
	vector<Node*> arrNode=GojoRes.hash[z].postOrder();
	int N = arrNode.size();
	if(N==0) continue;
	//cout<<"so luong node trong bts"<<N<<endl;
    // Store the factorial up to N
    int fact[N];
 
    // Precompute the factorial up to N
    calculateFact(fact, N);
 
  // cout<<"so hoan vi"<<  countWays(arrNode, fact)<<endl;
//    for(int i=0;i<2;++i)
//    cout<<GojoRes.hash[3].OrderCus[i]->result<<"________";
   int Y=countWays(arrNode, fact)%MAXSIZE;
   if(Y==0) break;
   int GojoReshashz_OrderCus_size=GojoRes.hash[z].OrderCus.size();
   if(Y>=GojoReshashz_OrderCus_size)
   {
//	cout<<"da xoa"<<endl;
   for(unsigned i=0;i<GojoRes.hash[z].OrderCus.size();++i)
	GojoRes.hash[z].deleteNodeBST(GojoRes.hash[z].OrderCus[i]->result);
//	cout<<"hello";
   }
   else
   {
	for(int i=0;i<Y;++i)
	GojoRes.hash[z].deleteNodeBST(GojoRes.hash[z].OrderCus[i]->result);
   }
   //cout<<"\n hello xoa"<<GojoRes.hash[3].OrderCus[i]->result<<"________";
   
	}
}
void KEITEIKEN(int num)
{
	//cout<<"KEITEIKEN"<<endl;
	SukunaRes.remove_KEITEIKEN(num);
//    int len= SukunaRes.KEITEIKEN_PRINT.size();
//    for(int i=len-1;i>=0;--i)
//    {
//     cout<<SukunaRes.KEITEIKEN_PRINT[i]<<endl;
//     SukunaRes.KEITEIKEN_PRINT.pop_back();
//    }
}
void HAND()
{
	//cout<<"HAND"<<endl;
    if(arrNameCus.size()<=0) return;
	string name=arrNameCus.at(arrNameCus.size()-1);
	string stringResult0="";
	 vector<pair<char, int>> arr=Caesar(name,stringResult0); // 
	HuffmanTree Hufftree;
	//HuffNode* root =
    Hufftree.buildHuff(Hufftree.vectorToHuffNode(arr));
	Hufftree.printIn();
}
void LIMITLESS(int num)
{
	//cout<<"LIMITLESS "<<num<<endl;
	if(num<0 || num > MAXSIZE) return;
    if(GojoRes.hash[num-1].count<=0) return;
    if(GojoRes.count<=0) return;
	GojoRes.hash[num-1].printInOrder();
}
void CLEAVE(int num)
{
	//cout<<"CLEAVE"<<endl;
	SukunaRes.print_CLEAVE(num);
}


void simulate(string filename)
{
	//cout << "Good Luck"<<endl;
	ifstream ifs(filename);
	string str;
	while(ifs>>str)
	{
		if(str=="MAXSIZE")
		{
			ifs>>str;
			MAXSIZE=stoi(str);
			begin();
		}
		else if (str=="LAPSE")
		{
			ifs>>str;
			string nameCus;
			nameCus=str;
			LAPSE(nameCus);
		}
		else if( str=="KOKUSEN")
		{
			KOKUSEN();
		}
		else if( str=="KEITEIKEN")
		{
			ifs>>str;
			int num=stoi(str);
			KEITEIKEN(num);
		}
		else if( str=="HAND")
		{
			HAND();
		}
		else if( str=="LIMITLESS")
		{
			ifs>>str;
			int num=stoi(str);
			LIMITLESS(num);
		}
		else if( str=="CLEAVE")
		{
			ifs>>str;
			int num=stoi(str);
			CLEAVE(num);
		}
	}
	
	return;
}

