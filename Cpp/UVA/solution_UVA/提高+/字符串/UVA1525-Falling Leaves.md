# Falling Leaves

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4300

[PDF](https://uva.onlinejudge.org/external/15/p1525.pdf)

# 题解

## 作者：golden_brick (赞：7)

这是一道二叉搜索树模板题！

思路：
- 根据题意我们只需要倒序建树即可。
- 最后我们只要输出先序遍历就行了。
- 其他的就只是二叉搜索树的模板把数字变成字符即可。
- 代码细节在**程序**里。

最后附上本蒟蒻的代码~~我是用结构体写的（逃~~：
```cpp
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
struct Node
{
	int l, r;
	char c;
} tr[N]; // 二叉搜索树结构体
int root, cnt;
string s[N];
// 二叉搜索树模板
void ins(char c, int &now)
{
	if (now == -1)
	// 如果当前点不存在
	{
		// 那么我们就在这里新建一个点
		tr[now = ++cnt] = {-1, -1, c};
		return;
	}
	// 把我们要插入的字符和当前点的字符作比较
	// 如果小于当前点的字符
	// 那么我们就去左子树遍历
	if (c < tr[now].c) ins(c, tr[now].l);
	// 否则去右子树遍历
	else ins(c, tr[now].r);
}
void dfs(int now)
{
	if (now == -1) return;
	// 输出
	cout << tr[now].c;
	// 遍历左右子树
	dfs(tr[now].l);
	dfs(tr[now].r);
}
int main()
{
	while(1)
	{
		int k = 0;
		root = -1, cnt = 0;// 初始化
		// 输入
		while(cin >> s[++k] && s[k] != "$" && s[k] != "*") ;
		// 倒序建树
		for (int i = k - 1; i >= 1; i--)
			for (int j = 0; j < s[i].size(); j++)
				ins(s[i][j], root);
		// 输出
		dfs(root);
		cout << endl;
		if (s[k] == "$") break; // 结束程序
	}
	return 0;
}
```

---

## 作者：Engulf (赞：4)

## 前置芝士

二叉搜索树是一种数据结构，它的每个节点都有一个值（一般是数字），每个节点的左子树都**小于**该节点的值，右子树都**大于**该节点的值。

显然题目中倒序给出了每一层的节点，所以我们只需要倒序插入值，再 dfs 一遍求出先序遍历即可。

推荐题目：

- [P3369 【模板】普通平衡树
](https://www.luogu.com.cn/problem/P3369)

- [P2234 [HNOI2002]营业额统计](https://www.luogu.com.cn/problem/P2234)

- [P2286 [HNOI2004]宠物收养场](https://www.luogu.com.cn/problem/P2286)

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 10005;
struct node
{
	char val;
	int son[2];
}tr[N];
int idx;
int root;

void insert(char c, int &p)
{
	if (!p)
	{
		p = ++ idx;
		tr[p].val = c;
		return;
	}
	insert(c, tr[p].son[c > tr[p].val]);
}

void dfs(int u)
{
	if (!u) return;
	cout << tr[u].val;
	dfs(tr[u].son[0]);
	dfs(tr[u].son[1]);
}

vector<string> a;

int main()
{
	string s;
	while (114514)
	{
		a.clear();
		memset(tr, 0, sizeof tr);
		root = 0, idx = 0;
		while (cin >> s && s != "*" && s != "$") a.push_back(s);
		for (int i = a.size() - 1; i >= 0; i -- )
			for (auto c: a[i])
				insert(c, root);
		dfs(root);
		cout << endl;
		if (s == "$") break;
	}
	return 0;
}
```

---

## 作者：tylon2006 (赞：1)

~~好像没题解那我来捡个漏~~

# 标准的二叉搜索树

## 下面是~~药店~~要点:

- 由题目可知需要倒着建树且最后一个字母一定为根

  我直接用cin读字符并用字符串存储
   
- 一个标准的二叉搜索树的建树函数
  
  小的往左子树大的往右子树搜
  
  我用的数组建图（我就是不想用指针QWQ，~~传播恶习~~）
  
- 愉快的**先根遍历**
  
- 养成初始化的好习惯

- 坑点：每组数据均需要换行，即使是最后一组

#### *先根遍历：即先根再左子树最后右子树的遍历

## 下面是蒟蒻代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
struct data{
	int l,r;
	char c;
}tree[101];
int sum=1;
void insert(int u,char ch){
	if(!tree[u].c){
		tree[u].c=ch;
		return;
	}
	if(ch<tree[u].c){
		if(!tree[u].l){
			tree[++sum].c=ch;
			tree[u].l=sum;
		}
		else insert(tree[u].l,ch);
	}
	if(ch>tree[u].c){
		if(!tree[u].r){
			tree[++sum].c=ch;
			tree[u].r=sum;
		}
		else insert(tree[u].r,ch);
	}
}
void dfs(int u){
	if(!tree[u].c) return;
	printf("%c",tree[u].c);
	dfs(tree[u].l);
	dfs(tree[u].r);
}
int main()
{
	char ch;
	string s;
	while(1){
		s="";
		memset(tree,0,sizeof(tree));
		while(cin>>ch&&ch!='*'&&ch!='$') s+=ch;
		for(int i=s.length()-1;i>-1;i--) 
		insert(1,s[i]);
		dfs(1);
		printf("\n");
		if(ch=='$') break;
	}
}
```

求过审QWQ

---

## 作者：Emp7iness (赞：0)

### 题意

有一棵二叉树，依次删除这棵二叉树的叶子，现在给出删除顺序，求原二叉树的先序遍历。

### 解法

删除序列是从树叶到树根，而建树是从树根到树叶，所以我们可以根据给出的删除顺序倒序建树，再先序遍历即可。

代码：

```cpp
#include<iostream>
#include<string>
using namespace std;
const int N=105;
int n,k,r;
struct tree
{
	int l,r;
	char c;
}t[N];
string s[N];
void insert(char c,int &u)
{
	if(u==-1)
	{
		t[u=++k]={-1,-1,c};
		return;
	}
	if(c<t[u].c)	insert(c,t[u].l);
	else	insert(c,t[u].r);
}
void dfs(int u)
{
	if(u==-1)	return;
	cout<<t[u].c;
	dfs(t[u].l);
	dfs(t[u].r);
}
int main()
{
	while(1)
	{
		n=k=0;
		r=-1;
		while(cin>>s[++n]&&s[n]!="$"&&s[n]!="*");
		for(int i=n-1;i>=1;i--)//倒序建树
		{
			for(int j=0;j<s[i].size();j++)	insert(s[i][j],r);
		}
		dfs(r);
		cout<<endl;
		if(s[n]=="$")	break;
	}
	return 0;
}
```


---

## 作者：Erotate (赞：0)

**题意：** 有一棵二叉树，每次移除他的若干个树叶，现在给出删除树叶的编号（均为大写字母）的顺序，求这棵树的前序遍历。

显然，最后一次被删除的一定是根，而倒数第二次被删除的是根的儿子……第一次被删除的一定是原树的叶子节点。那么，我们只需要**倒序**建出一棵**二叉搜索树**，再按前序遍历遍历即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct tree{
    int ls,rs;
    char ch;
}t[N];//储存二叉树的数组
int gen,cnt,k;
string s[N];
void insert(char c,int &u){//建树
    if(u==-1){//找到一个没有的节点并新建一个节点
        u=++cnt;
        t[u]=(tree){-1,-1,c};
        return;
    }
    if(c<t[u].ch) insert(c,t[u].ls);//按规则插入
    else insert(c,t[u].rs);
}
void dfs(int u){//输出前序遍历
    if(u==-1) return;
    printf("%c",t[u].ch);
    dfs(t[u].ls);
    dfs(t[u].rs);
}
int main(){
    while(1){//多组数据
        k=cnt=0;
        gen=-1;
        do cin>>s[++k];
        while(s[k]!="$" && s[k]!="*");//处理输入
        for(int i=k-1;i;--i)//逆序插入每一次输入
            for(int j=0;j<s[i].size();++j) insert(s[i][j],gen);//一个个字符插入
        dfs(gen);
        printf("\n");
        if(s[k]=="$") return 0;//结束条件
    }
}
```


---

## 作者：小火龙不摆烂 (赞：0)

标注的一道二叉查找树题目（也是POJ1577）

按照题目可知删除的树叶序列从树叶->树根，那么我们就可以逆序建树，读入字母序列后用字符串存储，将晓得字母插入左子树，将大的字母插入右子树（不懂的快去看二叉查找树定义！！）。输出就是该树的先序遍历 根左右即可
```cpp
#include<iostream>
#include<cstring>
#include<string>
using namespace std;
struct data{
    int l,r;
    char c;
}tree[110];
int cnt=1;

void insert(int t,char ch){//在二叉树中插入字符ch
    if(!tree[t].c){
        tree[t].c=ch;
        return;
    }
    if(ch<tree[t].c){
        if(!tree[t].l){
            tree[++cnt].c=ch;
            tree[t].l=cnt;
        }
        else
			insert(tree[t].l,ch);
    }
    if(ch>tree[t].c){
        if(!tree[t].r){
            tree[++cnt].c=ch;
            tree[t].r=cnt;
        }
        else
			insert(tree[t].r,ch);
    }
}

void preorder(int t){//先序遍历
    if(!tree[t].c)
		return;
    cout<<tree[t].c;
    preorder(tree[t].l);
    preorder(tree[t].r);
}

int main(){
    string s1,s;
    while(1){
        s="";
        memset(tree,0,sizeof(tree));
        while(cin>>s1&&s1[0]!='*'&&s1[0]!='$')
			s+=s1;
        for(int i=s.length()-1;i>=0;i--) 
        	insert(1,s[i]);
        preorder(1);
        cout<<endl;
        if(s1[0]=='$')//遇到符号$结束即可
			break;
    }
}
```


---

