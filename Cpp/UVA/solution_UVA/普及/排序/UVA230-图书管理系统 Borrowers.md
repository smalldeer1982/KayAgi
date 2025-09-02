# 图书管理系统 Borrowers

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=4&page=show_problem&problem=166

[PDF](https://uva.onlinejudge.org/external/2/p230.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA230/080bb4c03724a95130bfbcbf99ca56637343b6dc.png)

## 样例 #1

### 输入

```
"The Canterbury Tales" by Chaucer, G.
"Algorithms" by Sedgewick, R.
"The C Programming Language" by Kernighan, B. and Ritchie, D.
END
BORROW "Algorithms"
BORROW "The C Programming Language"
RETURN "Algorithms"
RETURN "The C Programming Language"
SHELVE
END```

### 输出

```
Put "The C Programming Language" after "The Canterbury Tales"
Put "Algorithms" after "The C Programming Language"
END```

# 题解

## 作者：imTars (赞：4)

这题技巧性很强，主要技巧有：

1.用map<string, int>对书本进行编号，编号小的优先级高

2.用集合set<int> shelve,desk记录 书架上的图书编号 和 桌子上图书编号（未上架图书）。  
3.碰到命令RETURN时, desk.insert(book)保存要入架的书，shelve.inser(book)模拟上架过程，很方便吧…  
4.碰到命令SHELVE时，由于已在RETURN时模拟上架，所以遍历desk中编号x， 查询shelve中前于x的书本，按规定输出即可。
  
另外要注意的是，之所以desk用的是set容器而不是vector，是因为题目要求桌子上未归库的书本要按优先级排序。
  
code
  
  ```cpp
#include <bits/stdc++.h>
#define ALL(a) a.begin(),a.end()

using namespace std;
struct Book {
    string title, author;
    friend bool operator < (const Book &a, const Book &b) {
        return a.author < b.author || (a.author==b.author && a.title < b.title);
    }
}tmp;

vector<Book> books;
map<string, int> ID;
set<int> desk, shelve;
string op, line, title;

int main() {
    ios::sync_with_stdio(false)
    while(getline(cin, line) && line!="END") {  
        int p = line.find("by");
        tmp = Book{ line.substr(0, p-1), line.substr(p+3) };
        books.push_back(tmp);
    }
    sort(ALL(books));
    for(int i = 0; i < books.size(); i++) {
        ID[ books[i].title ] = i;		//为书本名称编号
        shelve.insert(i);
    }
    while(cin>>op && op!="END") {
        if(op=="SHELVE") {
            for(auto x:desk) {
                auto p = shelve.find(x);
                cout << "Put " << books[x].title;
                if(p == shelve.begin()) cout << " first" << endl;
                else cout << " after " << books[*(--p)].title << endl;
            }
            desk.clear();
            cout << "END\n";
            continue;
        } else {
            getline(cin, title);
            title = title.substr(1);        ///getline不会忽略cin>>op时留下的空格
            if(op == "RETURN") desk.insert(ID[title]), shelve.insert(ID[title]);
            else if(op == "BORROW") shelve.erase(ID[title]);
        }
    }
    return 0;
}
```

  


---

## 作者：Eason_AC (赞：3)

## Content
你需要完成一个图书管理系统的构建。

具体地，你先要完成初始时书架上所有书的信息的读入，格式形如 `"xxx" by yyy`，其中 $\texttt{xxx}$ 表示书的标题，$\texttt{yyy}$ 表示作者名字。书架上的书始终都是排成一排的。

随后，你需要处理若干次操作，每次操作分如下三种：

- $\texttt{BORROW xxx}$：有人借了一本标题为 $\texttt{xxx}$ 的书。
- $\texttt{RETURN xxx}$：有人还了一本标题为 $\texttt{yyy}$ 的书。这本书会放到书桌上，但**不会直接放回书架**。
- $\texttt{SHELVE}$：将所有在书桌上的书一一放回书架，输出每本书是插入在书架的最前面还是在某本书的后面。

书架和书桌上的书一旦发生了变化，立即先按照作者名字的字典序从小到大排序，如果作者名字相同，再按照标题名字的字典序从小到大排序。**保证不会有两本书的标题相同**。

**数据范围：标题名字和作者名字的长度不超过 $80$。**
## Solution
一道比较小清新的模拟，做了可以对 STL 中的各种容器（主要是 `set`）有更深入的了解。

首先，我们开一个自定义结构体 `node`，描述一本书的信息，包含这本书的标题和作者。然后，再按照如上所述题意弄一个重载运算符 `<` 出来。

接下来就可以开 `set` 容器了。一个比较重要的性质是，`set` 容器中的所有元素是按照重载运算符 `<` 自动排序得到的。因此，我们开两个 `set` 容器，一个用来存储书架里面的所有书的信息 $S_0$，另一个用来存储书桌上的所有书的信息 $S_1$。至此，排序的问题就已经解决了。

接下来看每一个操作。

对于 $\texttt{BORROW}$ 操作，我们直接在 $S_0$ 里面直接根据名字找到这本书，并用 `set` 自带的 `erase` 函数把这本书从 $S_0$ 里面移除即可。

对于 $\texttt{RETURN}$ 操作，我们可以事先拿一个 `map` 容器，将书的标题和书的作者名字之间的关系形成一个映射，然后直接根据我们得到的书的标题和书的作者名字“新建”出一本书，**同时插入**到 $S_0,S_1$ 中。具体这么做的原因，我们马上就会在 $\texttt{SHELVE}$ 操作中讲到。

对于 $\texttt{SHELVE}$ 操作，我们直接遍历一遍 $S_1$ 里面的所有元素，并在 $S_0$ 当中找到这个元素所在的位置，再根据其位置判断其是在书架的最前面还是在某本书的后面。然后把 $S_1$ 清空，整个操作就干净利落的完成了。

大体上就是这些，`set` 实现的具体细节可以看 `set` 相关的博客，也可以直接看以下代码实现加以理解。字符串相关处理细节在此不多作赘述。
## Code
```cpp
namespace Solution {
	string s, op;
	struct node {
		string name, auth;
		
		bool operator < (const node& t) const {return auth < t.auth || (auth == t.auth && name < t.name);}
	};
	set<node> S, S2;
	map<string, string> auths;
	
	iv Main() {
		while(1) {
			getline(cin, s);
			if(s == "END") break;
			int cur = 1;
			string name = "", auth = "";
			for(; s[cur] != '\"'; name += s[cur++]);
			for(cur += 5; cur < (int)s.size(); auth += s[cur++]);
			S.insert((node){name, auth}), auths[name] = auth;
		}
		while(1) {
			cin >> op;
			if(op == "END") break;
			if(op == "SHELVE") {
				for(set<node> :: iterator it = S2.begin(); it != S2.end(); ++it) {
					set<node> :: iterator It = S.find((node){(*it).name, (*it).auth});
					if(It == S.begin()) cout << "Put \"" << (*It).name << "\" first" << endl;
					else {
						cout << "Put \"" << (*It).name << "\" after \"";
						It--, cout << (*It).name << "\"" << endl;
					}
				}
				S2.clear(), puts("END");
			} else {
				getline(cin, s);
				string name = "";
				for(int cur = 2; s[cur] != '\"'; name += s[cur++]);
				if(op == "BORROW") {for(set<node> :: iterator it = S.begin(); it != S.end(); it++) if((*it).name == name) {S.erase(it); break;}}
				else S2.insert((node){name, auths[name]}), S.insert((node){name, auths[name]});
			}
		}
		return;
	}
}
```

---

## 作者：StayAlone (赞：2)

### Hack  
Input
```
"bybyby" by byby
"by ppp" by liangruichen
"by sbsb" by Lh AK IOI
END
BORROW "bybyby"
BORROW "by ppp"
RETURN "bybyby"
RETURN "by ppp"
SHELVE
END
```  
Output
```
Put "bybyby" after "by sbsb"
Put "by ppp" after "bybyby"
END
```  
原理：另外两篇题解直接使用 `s.find("by")` 来确定中间 `by`的位置。但是当书名或作者的名字中出现 `by` 时，会出现异常。

~~如果题目保证了不含 `by`，可重喷~~。

### 题意  
现在有一个书架，有作者和书名两个信息。保证没有两本一样的书。还书的时候会先放到一个书桌上，如果输入 `SHELVE`，则要先把书桌上的书从小到大排序（作者为第一关键字，书名为第二关键字），依次还到书架上，书架上的排序方式也和书桌一样。如果书 $p$ 要还到书 $t$ 的后面，则输出 `Put p after t`。特殊地，若放到第一位，输出 `Put p first`。  


### 思路

思路比较简单，主要在代码能力的模拟上。  

请仔细辨别下面所写的**书架**和**书桌**。	

拿两个 `set`，一个表示真正的书架上的书，一个表示临时的书桌。注意它们的类型均为 `pair <string, string>`。  
每一次按照操作直接模拟。`BORROW` 对应删除，`INSERT` 对应插入。这里的小技巧是 `INSERT` 时其实可以插入真正的书架，并不影响结果。所以在 `SHELVE` 的时候，遍历每一个书桌上的书，并查找它在书架上的位置，按照题意输出它的前一本书或者它第一本书即可。注意 `SHELVE` 完要清空书桌。  

[AC code 记录](https://www.luogu.com.cn/record/62395405)
```cpp
#include <bits/stdc++.h>
#define rep1(i, j, n) for (int i = j; i <= int(n); ++i)
#define rep2(i, j, n) for (int i = j; i >= int(n); --i)
#define......
using namespace std;
typedef long long ll;
typedef......
const int MAXN = 1e5 + 10, inf = ~0U >> 2, INF = ~0U >> 1;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
namespace stupid_lrc
{
	template <typename T>
	il void read(T &x)
    
    il int read()
    
	template <typename T>
	il void write(T x)
	
	template <typename T>
	il T my_max(const T &x, const T &y)
	
	template <typename T>
	il T my_min(const T &x, const T &y)
	
	template <typename T>
	il T lowbit(const T &x)
    
	il void restr(string &s)

	il void wrstr(const string &s, const unsigned &len)
	
	il string ItS(int k)
	
	il int StI(const string &s)
}
using namespace stupid_lrc;
typedef pair<string, string> psi;
typedef set<psi> :: iterator iter;
map <string, string> bok; // bok[s] 表示书名为 s 的书的作者 
set <psi> shf, dsk;

int main()
{
	string s, bk;
	while (getline(cin, s))
	{
		if (s == "END") break;
		string bn = "", aut = "";
		int len = s.size(), r;
		rep1(i, 1, len - 1)
		{
			if (s[i] == '"') break;
			bn += s[i]; r = i;
		}
		r += 6;
		rep1(i, r, len - 1) aut += s[i];
//		cout << bn << " " << aut << endl;
		bok[bn] = aut; shf.insert(mp(aut, bn));
	}
	while(cin >> s)
	{
		if (s == "END") break;
		if (s == "SHELVE")
		{
			for (iter p = dsk.begin(); p != dsk.end(); ++p)
			{
				psi k = *p;
				iter t = shf.find(mp(k.fst, k.snd));
				ptc('P'); ptc('u'); ptc('t'); ptc(' ');
				cout << '"' << k.snd << '"';
				if (t == shf.begin()) puts(" first");
				else
				{
					printf(" after "); --t;
					cout << '"' << (*t).snd << '"'; ptc('\n');
				}
			}
			dsk.clear(); puts("END"); continue;
		}
		getchar(); getline(cin, bk);
		int len = bk.size();
		bk = bk.substr(1, len - 2);
		if (s == "BORROW") shf.erase(mp(bok[bk], bk));
		else if (s == "RETURN") dsk.insert(mp(bok[bk], bk)), shf.insert(mp(bok[bk], bk));
	}
	rout;
}
```

---

## 作者：flora715 (赞：1)

//建立vector<book>保存图书信息
//使用map<string,int>建立标题到图书编号的映射，方便查找。
//两个set<int>保存已归还而未上架的书籍shelf，还在书架上的书籍lib。


```cpp
#include <bits/stdc++.h>
using namespace std;

/*【图书管理系统】（UVa230）
图书管理系统。首先输入若干图书的标题和作者（标题不同，以END结束），
然后是若干指令：BORROW指令表示借书，RETURN指令表示还书，
SHELVE指令表示把所有已归还但还未上架的图书排序后依次插入书架，
并输出图书标题和插入位置（可能是第一本书或者某本书的后面）。
图书排序的方法是先按作者从小到大排，再按标题从小到大排。
在处理第一条指令之前，你应当先将所有图书按照这种方式排序。 */

//建立vector<book>保存图书信息
//使用map<string,int>建立标题到图书编号的映射，方便查找。
//两个set<int>保存已归还而未上架的书籍shelf，还在书架上的书籍lib。

struct Node {  
    string name,title;  
    Node(string a,string b) {  
        name=b;  
        title=a;  
    }  
    friend bool operator<(Node a,Node b) {  
        if(a.name==b.name) return a.title<b.title;  
        return a.name<b.name;  
    }  
};  
  
int main() {  
    string str,aa("by");  
    vector<Node>cnt;  
    vector<Node>xyz;  
    while(getline(cin,str)) {  
        if(str=="END") break;  
        cnt.push_back(Node(str.substr(1,str.find(aa)-3),
            str.substr(str.find(aa)+3,str.size()-str.find(aa)-3)));  
    }  
    string str2; xyz=cnt;  
    vector<Node>dict;  
    while(getline(cin,str2)) {  
        string cmd1,cmd2;  
        cmd1=str2.substr(0,6);  
        if(str2.size()>6)  
            cmd2=str2.substr(8,str2.size()-9);  
        if(cmd1=="END") break;  
        if(cmd1[0]=='B')//借走就要删除    
            for(vector<Node>::iterator it=cnt.begin(); it!=cnt.end();) {  
                if((*it).title==cmd2) {  
                    cnt.erase(it); break;  
                }  
                else it++;  
            }  
        else if(cmd1[0]=='R') {
            for(vector<Node>::iterator it=xyz.begin(); it!=xyz.end(); it++) 
                if((*it).title==cmd2)   
                    dict.push_back(*it);//还得书保存在dict  
        }  
        else {  
            sort(cnt.begin(),cnt.end());  
            sort(dict.begin(),dict.end());  
            for(vector<Node>::iterator t=dict.begin(); t!=dict.end(); ){
            //对于每一本要还回来的书都要寻找它们的位置。  
                if(cnt.size()==0){ //放在开头  
                    cout<<"Put "<<'\"'<<(*t).title<<'\"'<<" first"<<endl;  
                    cnt.push_back(*t);  
                    dict.erase(t);  
                    continue;  
                }  
                sort(cnt.begin(),cnt.end());  
                int ok=0;  
                vector<Node>::iterator i;  
                for(i=cnt.begin(); i!=cnt.end(); i++) {  
                    if((*i)<(*t)) continue;  
                    else{ //放在中间  
                        ok=1;  
                        if(i==cnt.begin())  {  
                            cout<<"Put "<<'\"'<<(*t).title<<'\"'<<" first"<<endl;  
                            cnt.push_back(*t);  
                            dict.erase(t); break;  
                        }  
                        cout<<"Put "<<'\"'<<(*t).title<<'\"'<<" after "<<'\"'<<(*(--i)).title<<'\"'<<endl;  
                        cnt.push_back(*t);  
                        dict.erase(t);  
                        break;  
                    }  
                }  
                if(!ok){ //放在末尾  
                    cout<<"Put "<<'\"'<<(*t).title<<'\"'
                       <<" after "<<'"'<<(*(--i)).title<<'\"'<<endl;  
                    cnt.push_back(*t);  
                    dict.erase(t);  
                }  
                sort(cnt.begin(),cnt.end());  
            }  
            cout<<"END"<<endl;//最后一定要有“END”  
        }  
    }  
    return 0;  
}  
```

---

## 作者：SimonGao0322 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA230)

## 题目思路

创建一个结构体 $book$ 来记录每本书的名字和作者。

创建一个映射来记录每一个书的名字和作者，一个集合 $s$ 来记录书架上的书，一个集合 $desk$ 记录已经归还但没有放回书架的书。

借书时，将书从 $s$ 中删除。还书时，将书插入 $desk$。放回书架时，将 $desk$ 的数据插入 $s$ 然后清空 $desk$。

## 前置知识

### 映射

映射是一种基于红黑树的数据结构，主要有以下几个操作。

1. 插入：插入可以用 ```insert``` 实现。
2. ```operator []```：可以返回键所对应的值。

### 集合

集合是一种基于红黑树的数据结构，主要有以下几个操作。

1. 插入：插入可以用 ```insert``` 实现。
2. 删除：插入可以用 ```erase``` 实现。
3. 查找：查找可以用 ```find``` 实现。

## 代码

```cpp
/* ********UVA230******** */

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <stdexcept>
#include <thread>
#include <tuple>
#include <queue>
#include <utility>
#include <vector>

using ll=long long;
using ull=unsigned long long;
using namespace std;
using std::vector;
using std::bitset;
#define For(i,a,b,x) for(auto i=a;b;x)
#define ret(a) return a
#define FASTIO ios::sync_with_stdio(false),cin.tie(0),cout.tie(0); 
#define mems(a,x) memset(a,x,sizeof(a));
struct book{
    string name,author;
    bool operator<(const book& o)const{    //用于set排序
        if(author!=o.author)return author<o.author;
        return name<o.name;
    }
};
int main(){
    FASTIO;    //输入输出优化
    map<string,string>all;
    set<book>desk,s;
    char c=getchar();
    while(c!='E'){  //输入
        string name;
        getline(cin,name,'\"');
        getchar();
        getchar();
        getchar();
        getchar();
        string author;
        getline(cin,author);
        s.insert({name,author});
        all.insert({name,author});
        c=getchar();
    }
    string s2;
    string dommy;
    getline(cin,dommy);
    cin>>s2;
    while(s2!="END"){
        if(s2=="BORROW"){  //借书
            string name;
            getchar();
            getchar();
            getline(cin,name,'\"');
            string dommy;
            getline(cin,dommy);
            s.erase({name,all[name]});
        }
        if(s2=="RETURN"){  //还书
            string name;
            getchar();
            getchar();
            getline(cin,name,'\"');
            string dommy;
            getline(cin,dommy);
            desk.insert({name,all[name]});
        }
        if(s2=="SHELVE"){ //放回书架
            for(auto it=desk.begin();it!=desk.end();++it){
                s.insert(*it);
                auto it2=s.find(*it);
                if(it2==s.begin())cout<<"Put "<<'\"'<<it->name<<'\"'<<" first\n";
                else{
                    auto it3=--it2;
                    cout<<"Put "<<'\"'<<it->name<<'\"'<<" after "<<'\"'<<it3->name<<'\"'<<"\n";
                }
                desk.erase(*it);
            }
            cout<<"END\n";
        }
        cin>>s2;
    }
    return 0;
}
```

---

