
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

const int maxn = 58;

int number[maxn];
string code_list[maxn], Data, encode,hfcode;
int WEPL = 0;

struct Node {   
    int id, value;
    Node *lson, *rson;
};

struct cmp {
    bool operator() (Node *a, Node *b) {
        return a -> value > b -> value;
    }
};

void get_encode(Node *cur, string record) {
    if (cur -> id != -1) {
        code_list[cur -> id] = record;
    }
    else {
        get_encode(cur -> lson, record + "0");
        get_encode(cur -> rson, record + "1" );
    }
}
 
void decode(Node *root,string huffcode)  {
    cout << "decode : ";
    int chnumber=huffcode.length();
    
    Node *cur = root;
    for (int i = 0; i < huffcode.size(); i++) {
        if (huffcode[i] == '0') {
            cur = cur -> lson;
           
        }
        else {
            cur = cur -> rson;
            
        }
        if (cur -> id != -1) {
            cout << char(cur -> id + 'A');
            chnumber-=code_list[cur->id].length();//recode -wrong decode- 
            cur = root;
        }
    }
    
    if(chnumber>0) cout<<" -wrong decode- ";
    cout << "\n";
    
}

void output(string data,string hf,int flag) {
	
    for (int i = 0; i < Data.size(); i++) {
        encode += code_list[ Data[i] - 'A'];
    }
    int endline=0;
    if(data.length()!=0&&flag==0) cout<<"characters : "<<data<<"\n\n";
    for (int i = 0; i < 60; i++) {
        if(number[i]>0 )
		{
			cout  << char (i + 'A') << " = " << number[i] << " | ";
			endline++;
			if(endline%10==0) cout<<'\n';
		}
       
    }
    cout << "\n\n";
    if(data.length()!=0)
    for (int i = 0; i < 58; i++) {
        if(code_list[i].length()>0 )cout << "   " << char (i + 'A') << ": " << code_list[i] << "\n";
        WEPL = WEPL + code_list[i].size() * number[i];
    }
    cout << "\n";
}

int main() {
	
	int flag=0;
	char tre[100];
	cin.getline(tre,100);
	int size=0;
	for(int i=0;i<100;i++)
	{
		if(tre[i]=='\0') break;
		else size++;	
	}
	
	
    if(size==6)
	{
    cout<<"DSOO-Program2-Demo: ./tree";
	flag=1;
	Data="AAAAAAAAAAABBBBBCCDDDEEEEEEEEEEEEFFFGGGGGHHHHHHIIIIIIIIJKKLLLLMMMMMMMMNNNNNNNOOPPQRRRRRRRRRSSSSSSTTUUUUVWWWWWWWWWWXXXXXXXXXXYZ";
	hfcode="";	
	}
	else
	{
    for(int i=0;i<sizeof(tre)-7;i++)
    {
        tre[i]=tre[i+7];
    }
    std::ifstream ifs(tre, std::ios::in);//
	ifs >> Data >> hfcode;
	ifs.close();
    cout<<"DSOO-Program2-Demo: ./tree ";
	cout<<tre;

	}
    
	cout<<'\n';


    for (int i = 0; i < Data.size(); i++) {
        number[Data[i] - 'A']++;        
    }
    
    priority_queue<Node*, vector<Node*>, cmp> pq;
    for (int i = 0; i < 58; i++) {
        if (number[i] == 0) continue;
        Node *leaf = new Node;
        leaf -> value = number[i];
        leaf -> id = i;
        leaf -> lson = leaf -> rson = NULL;
        pq.push(leaf);
    }   

    while (pq.size() > 1) {
        Node *cur = new Node, *a, *b;
        a = pq.top();
        pq.pop();
        b = pq.top();
        pq.pop();
        cur -> value = a -> value + b -> value;
        cur -> id = -1;
        cur -> lson = a;
        cur -> rson = b;
        pq.push(cur);
    }
    Node *root = pq.top();
    get_encode(root, "");
    output(Data,hfcode,flag);
    if(hfcode.length()!=0)
    {
    	cout<<"Huffman code: "<<hfcode<<'\n';
    decode(root,hfcode);
	}
    
    cout << "WEPL:" << WEPL << "\n";

return 0;
}
