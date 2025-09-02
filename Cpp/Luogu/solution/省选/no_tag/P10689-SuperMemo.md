# SuperMemo

## 题目描述

你的朋友 Jackson 被邀请参加一个名为 SuperMemo 的电视节目，参与者需要玩一个记忆游戏。首先，主持人会告诉参与者一个数字序列 $A_1, A_2, \ldots A_n$。然后，主持人会对该序列进行一系列操作和查询，包括：

  * `ADD x y D`：将 $D$ 加到子序列 $A_x \ldots A_y$ 的每个数字上。例如，在 $1, 2, 3, 4, 5$ 上执行 "ADD 2 4 1" 后结果为 $1, 3, 4, 5, 5$。
  * `REVERSE x y`：反转子序列 ${A_x \ldots A_y}$。例如，在 $1, 2, 3, 4, 5$ 上执行 "REVERSE 2 4" 后结果为 $1, 4, 3, 2, 5$。
  * `REVOLVE x y T`：旋转子序列 ${A_x \ldots A_y}$ $T$ 次。例如，在 $1, 2, 3, 4, 5$ 上执行 "REVOLVE 2 4 2" 后结果为 $1, 3, 4, 2, 5$。
  * `INSERT x P`：在 $A_x$ 之后插入 $P$。例如，在 $1, 2, 3, 4, 5$ 上执行 "INSERT 2 4" 后结果为 $1, 2, 4, 3, 4, 5$。
  * `DELETE x`：删除 $A_x$。例如，在 $1, 2, 3, 4, 5$ 上执行 "DELETE 2" 后结果为 $1, 3, 4, 5$。
  * `MIN x y`：询问参与者子序列 $A_x \ldots A_y$ 中的最小数字是多少。例如，在 $1, 2, 3, 4, 5$ 上 "MIN 2 4" 的正确答案是 $2$。

为了让节目更有趣，参与者被授予一次求助他人的机会，这意味着当 Jackson 在回答查询时感到困难时，他可以向你求助。你的任务是观看电视节目并编写程序，以便在 Jackson 需要时为每个查询提供正确答案。

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
5
1
2
3
4
5
2
ADD 2 4 1
MIN 4 5```

### 输出

```
5```

# 题解

## 作者：microchip (赞：5)

题意翻译：

你需要维护一个序列，支持以下操作：

```ADD x y D``` 将序列中第 $x$ 到 $y$ 个元素加 $d$ .

```REVERSE x y``` 将序列中第 $x$ 到 $y$ 个元素进行区间翻转操作.

```REVOLVE x y D``` 定义右移操作为将某个区间的最后一个元素移动到该区间的最前面，将序列中第 $x$ 到 $y$ 个元素所在的区间进行 $d$ 次右移操作.

```INSERT x P``` 将元素 $P$ 插入到序列中第 $x$ 个元素的后面.

```DELETE x``` 删除序列中第 $x$ 个元素.

```MIN x y``` 求序列中第 $x$ 到 $y$ 个元素的最小值.



------------

### Solution：伸展树

众所周知，对于复杂的序列维护问题（如区间翻转），我们常用平衡树来维护.常用的序列平衡树有两种：Splay Tree 和 FHQ Treap.

这里我们使用 Splay 来解决此题.

阅读前请先使用 Splay 完成 [普通平衡树](https://www.luogu.com.cn/problem/P3369) 和 [文艺平衡树](https://www.luogu.com.cn/problem/P3391) 来熟悉 Splay 的基本操作，以及如何使用 Splay 来处理区间操作，本题解默认您已经了解这些内容.

### Step 1：建树

最简单粗暴的办法是以 $n \log n$ 的复杂度依次对每个元素执行插入操作，但我们有更高明的办法：

```cpp
void build(int l,int r,int &no,int a[]){
	if(l>r)return;
  	if(no==0)no=++nth;
	int mid=(l+r)/2;
	Tr[no].val=a[mid];
	Tr[no].min_val=Tr[no].val;
	build(l,mid-1,Tr[no].left,a);
	if(Tr[no].left){
		Tr[Tr[no].left].fa=no;
		Tr[no].min_val=min(Tr[no].min_val,Tr[Tr[no].left].min_val);
	}
	build(mid+1,r,Tr[no].right,a);
	if(Tr[no].right){
		Tr[Tr[no].right].fa=no;
		Tr[no].min_val=min(Tr[no].min_val,Tr[Tr[no].right].min_val);
	}
	update(no);
}
```

这里是将原有数列直接构造成一个完美的平衡树，每次选取数列的中位数作为根，将左半部分作为左儿子，右半部分作为右儿子，递归建树，这样建树的复杂度是 $O(n)$.

同时我们给每个节点维护了该点代表区间的最小值，用于查询 RMQ.

注意要在序列的头和尾多加一个元素，保证不出现越界问题.

### Step 2：查询区间最小值

通过文艺平衡树一题，我们知道 Splay 提取区间 $[l,r]$ 的方式是先将 $l-1$ 旋转至根处，再将 $r+1$ 旋转至根下，这样根节点的右子树的左子树就代表了区间 $[l,r]$.

问题在于在旋转的过程中，被旋转的点所代表的区间会变化，所以在旋转的过程中我们要注意区间最小值的更新.

先考虑左旋，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/g3nhl55b.png)

橙色是我们要向上旋转的一个节点，我们发现该节点所代表的区间变成了其父节点所代表的区间，而父节点所代表的区间变成了 $b$ 子树和 $c$ 子树的区间外加自己.

于是我们在原有旋转代码之中加上这样一个更新操作即可：

```
Tr[no].min_val=Tr[tmp].min_val;// tmp 表示 no 的父节点

Tr[tmp].min_val=min(Tr[tmp].val,min(Tr[Tr[tmp].right].min_val,Tr[Tr[no].right].min_val));
```

右旋操作同理.

这样我们就可以查询任意区间的最小值了.

### Step 3：修改操作

插入和删除是平衡树的基操，这里不再赘述.

翻转操作和区间加操作通过延时标记来高效解决，相信过了文艺树的您肯定可以很快写出来.

注意每次旋转操作和查询第 k 个元素时都要将遍历到的点进行标记下传.代码如下：

```cpp
void tag_pushdown(int no){
	if(Tr[no].tag_rev){//翻转标记
		swap(Tr[no].left,Tr[no].right);
		Tr[Tr[no].left].tag_rev^=1;
		Tr[Tr[no].right].tag_rev^=1;
		Tr[no].tag_rev=0;
	}
	if(Tr[no].tag_add){//加法标记
		Tr[Tr[no].left].val+=Tr[no].tag_add;
		Tr[Tr[no].left].min_val+=Tr[no].tag_add;
		Tr[Tr[no].left].tag_add+=Tr[no].tag_add;
		Tr[Tr[no].right].val+=Tr[no].tag_add;
		Tr[Tr[no].right].min_val+=Tr[no].tag_add;
		Tr[Tr[no].right].tag_add+=Tr[no].tag_add;
		Tr[no].tag_add=0;
	}
}

void range_rev(int l,int r){
	kth_num(r+2);
	int tmp=root;
	kth_num(l);
	splay_under_root(tmp);
	Tr[Tr[Tr[root].right].left].tag_rev^=1;
	tag_pushdown(Tr[Tr[root].right].left);
}
void range_add(int l,int r,int val){
	kth_num(r+2);
	int tmp=root;
	kth_num(l);
	splay_under_root(tmp);
	Tr[Tr[Tr[root].right].left].tag_add+=val;
	Tr[Tr[Tr[root].right].left].min_val+=val;
	Tr[Tr[Tr[root].right].left].val+=val;
}
```

区间右移操作可以等价于区间移动操作，显然，如果移动的步数等于区间长度，那么就相当于没有操作，所以我们先将 $D$ 对 $y-x+1$ 取模，此时就相当于将区间 $[x,y-D]$ 移动到区间 $[y-D+1,y]$ 的后方.

代码如下：

```cpp
void range_mov(int l,int r,int stp){
	kth_num(r-stp+2);
	int tmp=root;
	kth_num(l);
	splay_under_root(tmp);
	int Root=Tr[Tr[root].right].left;
	Tr[Tr[root].right].left=0;
	Tr[Tr[root].right].siz-=Tr[Root].siz;
	Tr[root].siz-=Tr[Root].siz;
	kth_num(l+stp+1);
	int tmp2=root;
	kth_num(l+stp);
	splay_under_root(tmp2);
	Tr[Tr[root].right].left=Root;
	Tr[Tr[root].right].siz+=Tr[Root].siz;
	Tr[root].siz+=Tr[Root].siz;
	Tr[Root].fa=Tr[root].right;
}
```

于是这道题就解决啦.

AC 代码如下，使用 class 封装的伸展树（~~码风有点抽象，见谅~~）：

```cpp
#include<iostream>
using namespace std;

class Splay_Tree{
	private:
		struct node{
			long long val,tag_add,min_val;
			int fa,left,right,siz;
			bool tag_rev;
		}Tr[200050];
		int root,nth,x,k;
	public:
		long long min(long long x,long long y){
			return x<y?x:y;
		}
		bool son(int no){
			return Tr[Tr[no].fa].right==no;
		}
		void update(int no){
			Tr[no].siz=Tr[Tr[no].left].siz+1+Tr[Tr[no].right].siz;
		}
		void tag_pushdown(int no){
			if(Tr[no].tag_rev){
				swap(Tr[no].left,Tr[no].right);
				Tr[Tr[no].left].tag_rev^=1;
				Tr[Tr[no].right].tag_rev^=1;
				Tr[no].tag_rev=0;
			}
			if(Tr[no].tag_add){
				Tr[Tr[no].left].val+=Tr[no].tag_add;
				Tr[Tr[no].left].min_val+=Tr[no].tag_add;
				Tr[Tr[no].left].tag_add+=Tr[no].tag_add;
				Tr[Tr[no].right].val+=Tr[no].tag_add;
				Tr[Tr[no].right].min_val+=Tr[no].tag_add;
				Tr[Tr[no].right].tag_add+=Tr[no].tag_add;
				Tr[no].tag_add=0;
			}
		}
		void rotate(int no){
			if(no==root)return;
			int tmp=Tr[no].fa;
			tag_pushdown(tmp);
			tag_pushdown(no);
			Tr[no].min_val=Tr[tmp].min_val;
			if(son(no)==0){
				Tr[tmp].min_val=min(Tr[tmp].val,min(Tr[Tr[tmp].right].min_val,Tr[Tr[no].right].min_val));
				Tr[tmp].left=Tr[no].right;Tr[Tr[no].right].fa=tmp;Tr[no].right=tmp;
			}else{
				Tr[tmp].min_val=min(Tr[tmp].val,min(Tr[Tr[tmp].left].min_val,Tr[Tr[no].left].min_val));
				Tr[tmp].right=Tr[no].left;Tr[Tr[no].left].fa=tmp;Tr[no].left=tmp;
			}update(tmp);update(no);
			if(tmp==root){
				root=no;
				Tr[no].fa=0;Tr[tmp].fa=no;
				return;
			}int tmp2=Tr[tmp].fa;
			bool flag=son(tmp);
			Tr[tmp].fa=no;Tr[no].fa=tmp2;
			if(flag==0)Tr[tmp2].left=no;
			else Tr[tmp2].right=no;
		}
		void splay(int no){
			while(no!=root){
				if(Tr[no].fa!=root&&son(no)==son(Tr[no].fa))rotate(Tr[no].fa);
				rotate(no);
			}
		}
		void build(int l,int r,int &no,int a[]){
			if(l>r)return;
			if(no==0)no=++nth;
			int mid=(l+r)/2;
			Tr[no].val=a[mid];
			Tr[no].min_val=Tr[no].val;
			build(l,mid-1,Tr[no].left,a);
			if(Tr[no].left){
				Tr[Tr[no].left].fa=no;
				Tr[no].min_val=min(Tr[no].min_val,Tr[Tr[no].left].min_val);
			}
			build(mid+1,r,Tr[no].right,a);
			if(Tr[no].right){
				Tr[Tr[no].right].fa=no;
				Tr[no].min_val=min(Tr[no].min_val,Tr[Tr[no].right].min_val);
			}
			update(no);
		}
		void prework(int len,int a[]){
			for(int i=0;i<100050;i++)Tr[i].val=Tr[i].min_val=1147483647;
			k=len;
			build(0,len+1,root,a);
		}
		int kth(int no){
			if(no==0)return 0;
			tag_pushdown(no);
			if(Tr[Tr[no].left].siz+1==x){
				splay(no);
				return Tr[root].val;
			}if(Tr[Tr[no].left].siz+1>x)return kth(Tr[no].left);
			x-=Tr[Tr[no].left].siz+1;
			return kth(Tr[no].right);
		}
		int kth_num(int val){
			x=val;
			return kth(root);
		}
		void splay_under_root(int no){
			while(Tr[no].fa!=root){
				if(Tr[Tr[no].fa].fa!=root&&son(no)==son(Tr[no].fa))rotate(Tr[no].fa);
				rotate(no);
			}
		}
		int range_min(int l,int r){
			kth_num(r+2);
			int tmp=root;
			kth_num(l);
			splay_under_root(tmp);
			tag_pushdown(root);
			tag_pushdown(tmp);
			tag_pushdown(Tr[Tr[root].right].left);
			Tr[Tr[root].right].min_val=min(Tr[Tr[root].right].min_val,min(Tr[Tr[Tr[root].right].left].min_val,Tr[Tr[Tr[root].right].right].min_val));
			Tr[root].min_val=min(Tr[root].min_val,min(Tr[Tr[root].left].min_val,Tr[Tr[root].right].min_val));
			return Tr[Tr[Tr[root].right].left].min_val;
		}
		void ins(int pos,int val){
			kth_num(pos+2);
			int tmp=root;
			kth_num(pos+1);
			splay_under_root(tmp);
			Tr[Tr[root].right].left=++nth;
			Tr[nth].val=val;
			Tr[nth].fa=Tr[root].right;
			Tr[nth].min_val=Tr[nth].val=val;
			Tr[nth].siz=1;
			Tr[Tr[root].right].siz++;
			Tr[root].siz++;
		}
		void del(int pos){
			kth_num(pos+2);
			int tmp=root;
			kth_num(pos);
			splay_under_root(tmp);
			Tr[Tr[root].right].left=0;
			Tr[Tr[root].right].siz--;
			Tr[root].siz--;
		}
		void range_mov(int l,int r,int stp){
			kth_num(r-stp+2);
			int tmp=root;
			kth_num(l);
			splay_under_root(tmp);
			int Root=Tr[Tr[root].right].left;
			Tr[Tr[root].right].left=0;
			Tr[Tr[root].right].siz-=Tr[Root].siz;
			Tr[root].siz-=Tr[Root].siz;
			kth_num(l+stp+1);
			int tmp2=root;
			kth_num(l+stp);
			splay_under_root(tmp2);
			Tr[Tr[root].right].left=Root;
			Tr[Tr[root].right].siz+=Tr[Root].siz;
			Tr[root].siz+=Tr[Root].siz;
			Tr[Root].fa=Tr[root].right;
		}
		void range_rev(int l,int r){
			kth_num(r+2);
			int tmp=root;
			kth_num(l);
			splay_under_root(tmp);
			Tr[Tr[Tr[root].right].left].tag_rev^=1;
			tag_pushdown(Tr[Tr[root].right].left);
		}
		void range_add(int l,int r,int val){
			kth_num(r+2);
			int tmp=root;
			kth_num(l);
			splay_under_root(tmp);
			Tr[Tr[Tr[root].right].left].tag_add+=val;
			Tr[Tr[Tr[root].right].left].min_val+=val;
			Tr[Tr[Tr[root].right].left].val+=val;
		}
}T;

int n,a[100050],m,x,y,z;
string op;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	a[0]=-1147483647;a[n+1]=1147483647;
	T.prework(n,a);
	cin>>m;
	while(m--){
		cin>>op;
		if(op=="ADD"){
			cin>>x>>y>>z;
			T.range_add(x,y,z);
		}
		if(op=="REVERSE"){
			cin>>x>>y;
			T.range_rev(x,y);
		}
		if(op=="REVOLVE"){
			cin>>x>>y>>z;
			z%=y-x+1;
			if(z)T.range_mov(x,y,z);
		}
		if(op=="INSERT"){
			cin>>x>>y;
			T.ins(x,y);
		}
		if(op=="DELETE"){
			cin>>x;
			T.del(x);
		}
		if(op=="MIN"){
			cin>>x>>y;
			cout<<T.range_min(x,y)<<endl;
		}
	}
	return 0;
}

```
这道题可以很好地考察你的序列平衡树，细节较多，如果你想透彻平衡树，这道题很值得做.

## 题外话

高级数据结构代码很长，可读性低？~~这时候就该显示出 class 的威力了！~~

我们把封装好的伸展树放在一个头文件里，然后......

```
#include<iostream>
#include "Data_Structure.h"
using namespace std;

int n,a[100050],m,x,y,z;
string op;

Splay_Tree T;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	a[0]=-1147483647;a[n+1]=1147483647;
	T.prework(n,a);
	cin>>m;
	while(m--){
		cin>>op;
		if(op=="ADD"){
			cin>>x>>y>>z;
			T.range_add(x,y,z);
		}
		if(op=="REVERSE"){
			cin>>x>>y;
			T.range_rev(x,y);
		}
		if(op=="REVOLVE"){
			cin>>x>>y>>z;
			z%=y-x+1;
			if(z)T.range_mov(x,y,z);
		}
		if(op=="INSERT"){
			cin>>x>>y;
			T.ins(x,y);
		}
		if(op=="DELETE"){
			cin>>x;
			T.del(x);
		}
		if(op=="MIN"){
			cin>>x>>y;
			cout<<T.range_min(x,y)<<endl;
		}
	}
	return 0;
}

```


~~是不是清爽多了！（滑稽）~~

---

## 作者：Genius_Star (赞：4)

### 思路：

本题解使用 FHQ 平衡树进行维护，码量极小，跑的极快。

注意到除了 `REVOLVE l r d` 以外，其它的都是基础操作，打加法 $tag$ 和翻转 $tag$ 即可。

考虑右移 $d$ 次的本质是什么，显然右移 $(r - l + 1)$ 次后就还原了，故先将 $d$ 对 $(r - l + 1)$ 取模，然后相当于将区间 $[l, r - d]$ 与 $[r - d + 1, r]$ 交换位置，分裂出来后合并时交换顺序即可。

时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 2e5 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
mt19937 R(time(0));
char op[10];
int n, m, l, r, x, v, cnt, rt;
int a[N];
struct Node{
	int lson, rson;
	int siz, key;
	int data, Min, add;
	bool tag;
}X[N];
inline int newnode(int v){
	++cnt;
	X[cnt].lson = X[cnt].rson = X[cnt].add = X[cnt].tag = 0;
	X[cnt].key = (int)R();
	X[cnt].data = X[cnt].Min = v;
	X[cnt].siz = 1;
	return cnt;
}
inline void pushup(int k){
	X[k].Min = min({X[X[k].lson].Min, X[k].data, X[X[k].rson].Min});
	X[k].siz = X[X[k].lson].siz + 1 + X[X[k].rson].siz;
}
inline void add(int k, int v){
	if(!k)
	  return ;
	X[k].data += v, X[k].Min += v, X[k].add += v;
}
inline void push_down(int k){
	if(X[k].tag){
		swap(X[k].lson, X[k].rson);
		X[X[k].lson].tag ^= 1;
		X[X[k].rson].tag ^= 1;
		X[k].tag = 0;
	}
	if(X[k].add){
		add(X[k].lson, X[k].add);
		add(X[k].rson, X[k].add);
		X[k].add = 0;
	}
}
inline void split(int k, int v, int &x, int &y){
	if(!k){
		x = y = 0;
		return ;
	}
	push_down(k);
	if(X[X[k].lson].siz < v){
		x = k;
		split(X[k].rson, v - X[X[k].lson].siz - 1, X[k].rson, y);
	}
	else{
		y = k;
		split(X[k].lson, v, x, X[k].lson);
	}
	pushup(k);
}
inline int merge(int x, int y){
	if(!x || !y)
	  return x + y;
	if(X[x].key < X[y].key){
		push_down(x);
		X[x].rson = merge(X[x].rson, y);
		pushup(x);
		return x;
	}
	else{
		push_down(y);
		X[y].lson = merge(x, X[y].lson);
		pushup(y);
		return y;
	}
}
inline void insert(int i, int v){
	int x, y;
	split(rt, i, x, y);
	rt = merge(merge(x, newnode(v)), y);
}
inline void del(int i){
	int x, y, z;
	split(rt, i, x, z);
	split(x, i - 1, x, y);
	rt = merge(x, z);
}
inline void add(int l, int r, int v){
	int x, y, z;
	split(rt, r, x, z);
	split(x, l - 1, x, y);
	add(y, v);
	rt = merge(merge(x, y), z);
}
inline void reverse(int l, int r){
	int x, y, z;
	split(rt, r, x, z);
	split(x, l - 1, x, y);
	X[y].tag ^= 1;
	rt = merge(merge(x, y), z);
}
inline void revolve(int l, int r, int v){
	v %= (r - l + 1);
	int a, b, c, d;
	split(rt, r, a, d);
	split(a, r - v, a, c);
	split(a, l - 1, a, b);
	rt = merge(merge(merge(a, c), b), d);
}
inline int ask(int l, int r){
	int x, y, z, ans;
	split(rt, r, x, z);
	split(x, l - 1, x, y);
	ans = X[y].Min;
	rt = merge(merge(x, y), z);
	return ans;
}
bool End;
int main(){
	X[0].Min = INT_MAX;
	n = read();
	for(int i = 1; i <= n; ++i){
		a[i] = read();
		insert(i - 1, a[i]);
	}
	m = read();
	while(m--){
		scanf("%s", op + 1);
		if(op[1] == 'A'){
			l = read(), r = read(), v = read();
			add(l, r, v);
		}
		else if(op[1] == 'I'){
			x = read(), v = read();
			insert(x, v);
		}
		else if(op[1] == 'D'){
			x = read();
			del(x);
		}
		else if(op[1] == 'M'){
			l = read(), r = read();
			write(ask(l, r));
			putchar('\n');
		}
		else if(op[4] == 'E'){
			l = read(), r = read();
			reverse(l, r);
		}
		else{
			l = read(), r = read(), v = read();
			revolve(l, r, v);
		}
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：Tenil (赞：2)

# Solution

这里是博客：[Tenil](https://www.cnblogs.com/Tenil/p/18907399)，有更好的看题体验哦~

## 题意
[原题链接](https://www.luogu.com.cn/problem/P10689)

维护一个整数序列，要求能支持区间加，区间翻转，区间旋转（旋转 $T$ 次即为将区间末尾 $T$ 个数和前面的交换），在指定位置插入、删除，区间查询最小值。

区间长度 $n \le 100000$，操作次数 $m \le 100000$。

## 分析

ps：这里建议没写过 Splay 或 fhq-treap 的先做一下[这道题](https://www.luogu.com.cn/problem/P3391)。

维护序列的复杂操作（譬如本题的区间翻转）常用 Splay 或 fhq-treap，本题已经是明牌了。使用平衡树的原因是 BST 性质下，树进行 zig 或 zag 都不会改变其中序遍历的结果，从而可以在一棵树下同时维护序列顺序和最小值信息，且可以直接通过交换左右儿子的方式实现序列上的交换。

可以这么想：对于这种建在序列上的 BST，它初始排序依据的数据是数组角标，角标对应的具体数据只是附加信息，并且始终认为角标不变，用变动后的数据去对应角标。于是序列操作其实变成了在树上对角标和数据的对应关系进行改变。（如下图）

![](https://cdn.luogu.com.cn/upload/image_hosting/r10bh9x3.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/di1n9y22.png)

（红色表明中序遍历序，也即上文角标）原序列为 $32415$，经历平衡树的旋转后序列不变。

![](https://cdn.luogu.com.cn/upload/image_hosting/9ij3dnex.png)

（对比上左图）而不通过旋转直接交换儿子后，序列为 $42315$。我们认为角标始终与中序遍历序对应，故直接交换实际交换了对应角标上的数字。区间交换同理。

## 实现&分步Code

本文假设您已经会写 Splay，不对数据结构本身进行说明，只说说用法。

### 0.建树

最简单粗暴的一个想法就是挨个插入，但是这样会 $O(n\log n)$，令人不适。可以考虑类似线段树建树一样，直接建出一颗完全二叉树：


```cpp
void build(int l,int r,int &id) {
	if(l>r) return;
	int mid=(l+r)>>1;
	if(!id) id=New(a[mid]);
	build(l,mid-1,t[id].son[0]);
	if(t[id].son[0]) {
		t[id].min=std::min(t[id].min,t[t[id].son[0]].min);
		t[t[id].son[0]].f=id;
	}
	build(mid+1,r,t[id].son[1]);
	if(t[id].son[1]) {
		t[id].min=std::min(t[id].min,t[t[id].son[1]].min);
		t[t[id].son[1]].f=id;
	}
	upd(id);
	return;
}
```

或者直接建一条链然后一次伸展解决：


```cpp
inline void build() {
	for(int i = 1; i <= n+2; i++) {
		cnt++;
		t[cnt].son[0]=rt;
		if(rt) t[rt].f=cnt;
		rt=cnt;
		t[cnt].val=a[i-1];
	}
	splay(rt,1);
	return;
}
```

本文使用第一种方法，并在链段添加了两个哨兵节点。

### 1.插入&删除

这其实是 BST 的模版操作，但是由于我们在树上维护的数据并不参与树上的排序（维护的是数据，排序依据是角标），又有一点不一样。本题要求在 $A_x$ 之后插入、删除 $A_x$，实际上是在角标 $x$ 后插入、删除角标 $x$，回到树上即：在排名为 $x$ 的点后插入，删除排名为 $x$ 的节点。

插入时，可以先找角标为 $x$ 的节点 $A$，然后在它的右树找最小节点 $B$，这样 $B$ 的左儿子位上就是空的，直接加点就行；删除逆向考虑一下，先找 $x-1$，再在它的右树上找第二小节点 $A$，这样 $A$ 就有唯一左儿子对应角标 $x$，直接断掉。

其实这种类似“先找 xx，再找 xx，使某个节点为根的整个子树正好是操作区间”是本题的核心，建议画个图想想。


```cpp
void insert(int v,int p) {
	loc(rt,v);loc(t[rt].son[1],1);
  //loc(rt,rank)：在以rt为根的子树下找排名为rank的节点并提到根上
	int x=t[rt].son[1];
	t[x].son[0]=New(p);
	t[cnt].f=x;
	return;
}

void remove(int v) {
	loc(rt,v-1);loc(t[rt].son[1],2);
	int x=t[rt].son[1];
	t[x].son[0]=0;
	return;
}
```

### 2.区间最小

首先解决“最小”：由于平衡树拿去维护角标了，所以数据的最小值并不能直接获得。但是我们再想想线段树，可以直接用节点维护最小值信息。这个其实相对好想，旋转的时候记得维护一下就好了。

```cpp
inline void upd(int x) {
	t[x].size=1+t[t[x].son[0]].size+t[t[x].son[1]].size;
	t[x].min=std::min(std::min(
		t[t[x].son[0]].fix?t[t[x].son[0]].min:LONG_LONG_MAX,
		t[t[x].son[1]].fix?t[t[x].son[1]].min:LONG_LONG_MAX),
		t[x].val);
  //fix表示节点是否被使用，避免空节点的0错误更新
}
```

接下来问题就是“区间”了。类似删除的做法：先找角标为 $x-1$ 的节点 $A$，然后在它的右树找排名为 $y-x+2$ 的节点 $B$（$[x,n]$ 中第 $y-x+2$ 大，即角标为 $y+1$ 的点），这样的话 $B$ 的左树上就是所有角标在 $[x,y]$ 的节点，查询左树根节点上维护好的 $t[x].min$ 即可。

### 3.区间加、旋转、翻转

类似区间最小，区间加和翻转都可以简单的分出操作区间然后用懒标记维护了，相信这对于看完了上面的您来说并不难，这是代码：（其实你会发现这两个操作基本一模一样）

```cpp
void optr(int x) {
	std::swap(t[x].son[0],t[x].son[1]);
	t[x].stag^=1;return;
}

void opta(int x,int k) {
  t[x].val+=k;
  t[x].min+=k;
  t[x].atag+=k;
}

void tagd(int x) {
	if(t[x].stag) {
		if(t[x].son[0]) optr(t[x].son[0]);//标记下放时一定要注意空节点
		if(t[x].son[1]) optr(t[x].son[1]);
		t[x].stag=0;
	}
	if(t[x].atag) {
		if(t[x].son[0]) opta(t[x].son[0]);
		if(t[x].son[1]) opta(t[x].son[1]);
		t[x].atag=0;
	}
	return;
}

void reverse(int l,int r) {
	loc(rt,l-1);loc(t[rt].son[1],r-l+2);
	int x=t[t[rt].son[1]].son[0];
	optr(x);tagd(x);splay(rt,x);
	return;
}

void add(int l,int r,int k) {
	loc(rt,l-1);loc(t[rt].son[1],r-l+2);
	int x=t[t[rt].son[1]].son[0];
	opta(x);tagd(x);splay(rt,x);
	return;
}
```

而区间旋转就相对棘手一点了。首先容易想到要先把 $T$ 对 $y-x+1$ 取模，因为 $y-x+1$ 的正整数倍次数的旋转等于不转。设 $T \bmod (y-x+1)=r$，则操作变为交换 $[x,y-r]$ 和 $[y-r+1,y]$。但是不可能找到一个它们的父亲能让他们直接交换，所以我们可以利用中序遍历根在左子树之后的性质，先分离出 $[x,y]$ 区间后，把 $y-r$ 对应的节点提出来作为根，交换两个儿子后，将两个儿子合并到左儿子上，也就达成了目的。


```cpp
int merge(int x,int y) {
	if(!x||!y) return x|y;
	loc(y,1);
	t[y].son[0]=x;
	t[x].f=y;
	upd(y);
	return y;
}

void revolve(int l,int r,int k) {
	loc(rt,l-1);loc(t[rt].son[1],r-l+2);
	int x=t[t[rt].son[1]].son[0];
	loc(x,r-l+1-k);//这里的r-l+1-k对应的就是上文 y-r，注意是子树内排名
	std::swap(t[x].son[0],t[x].son[1]);
	t[x].son[0]=merge(t[x].son[0],t[x].son[1]);
	t[x].son[1]=0;
	return;
}
```

### 4.注意事项

1. 有哨兵节点，排名记得先加一；
2. 一定不要对空节点做任何修改！！！
3. 找结点的时候每步都要伸展。

终于，你 AC 了！恭喜！

[完整代码](https://www.luogu.com.cn/paste/611fu2tq)

## 闲话

蒟蒻经历了漫长的鏖战终于胜利，本篇算是一些写 BST 的理解了。

如果觉得有用，点个赞吧！

---

## 作者：Rain_cyl (赞：2)

码风清晰的 splay！

~~在写这道题的时候遇到了极其神秘的玄学 bug，调了几个小时才过。~~

看到题目里有翻转区间，是典型的 splay 操作，所以本题解使用 splay 进行维护。


---

### Part 1：节点信息以及 pushup 和 pushdown
splay 的每个节点除维护儿子、父亲、子树大小外，还要维护当前点所代表的元素的值 $val$，当前点所代表区间的最小值 $minval$，区间加标记 $add$ 和区间翻转标记 $rev$。

下传翻转标记时要注意，如果一个节点有翻转标记，那这个节点的左右儿子一定得是已经交换过的，否则在进行 revolve 操作的时候可能来不及下传，造成错误。所以 pushdown 时给两个儿子附上标记的同时，要把儿子的儿子进行交换。
```
struct Splay{
    int s[2],p,size;
    LL val,min_val,add;
    bool rev;
    void init(int _v,int _p){
        val=min_val=_v;
        p=_p,size=1;
    }
}tr[N];
int root,idx;

void pushup(int u){
    auto &lson=tr[tr[u].s[0]],&rson=tr[tr[u].s[1]];
    tr[u].size=lson.size+1+rson.size;
    tr[u].min_val=tr[u].val;
    if(tr[u].s[0]) tr[u].min_val=min(tr[u].min_val,lson.min_val);
    if(tr[u].s[1]) tr[u].min_val=min(tr[u].min_val,rson.min_val);
}

void pushdown(int u){
    auto &lson=tr[tr[u].s[0]],&rson=tr[tr[u].s[1]];
    if(tr[u].rev){
        if(tr[u].s[0]) swap(lson.s[0],lson.s[1]),lson.rev^=1;
        if(tr[u].s[1]) swap(rson.s[0],rson.s[1]),rson.rev^=1;
        tr[u].rev=0;
    }
    if(tr[u].add){
        LL &v=tr[u].add;
        if(tr[u].s[0]) lson.val+=v,lson.min_val+=v,lson.add+=v;
        if(tr[u].s[1]) rson.val+=v,rson.min_val+=v,rson.add+=v;
        v=0;
    }
}
```

---

### Part 2：建树
在数组的开头和结尾分别加上一个值为无穷大的元素，作为哨兵。建树的时候每次取当前区间的中间元素作为父节点，再把左半边作为左儿子，右半边作为右儿子，分别递归。

这样可以把一一插入元素的 $O(n \log n)$ 的时间复杂度缩减到 $O(n)$。
```
void build(int &u,int p,int l,int r){
    if(l>r) return;
    u=++idx;
    int mid=l+r>>1;
    tr[u].init(a[mid],p);
    build(tr[u].s[0],u,l,mid-1);
    build(tr[u].s[1],u,mid+1,r);
    pushup(u);
}
```
```
scanf("%d",&n);
for(int i=1; i<=n; i++) scanf("%lld",&a[i]);
a[0]=a[n+1]=1e18; //两侧加哨兵
build(root,0,0,n+1);
```

---
### Part 3：rotate 和 splay 操作
splay 的模板操作。这里的 rotate 使用的是简化版，不需要分情况讨论左旋还是右旋。
```
void rotate(int x){
    int y=tr[x].p,z=tr[y].p;
    int k=(tr[y].s[1]==x);
    tr[z].s[tr[z].s[1]==y]=x,tr[x].p=z;
    tr[y].s[k]=tr[x].s[k^1],tr[tr[x].s[k^1]].p=y;
    tr[x].s[k^1]=y,tr[y].p=x;
    pushup(y),pushup(x);
}

void splay(int x,int k){ //把x转到k下面
    while(tr[x].p!=k){
        int y=tr[x].p,z=tr[y].p;
        if(z!=k)
            if((tr[y].s[1]==x)^(tr[z].s[1]==y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if(!k) root=x;
}
```

---

### Part 4：区间加与区间翻转操作
注意提取 $[x,y]$ 区间时，应该把 $x-1$ 转到根，再把 $y+1$ 转到根下面，但由于一开始加入了哨兵，实际要找的是第 $x$ 个点和第 $y+2$ 个点。
```
int get_k(int k){ //找到编号为k的数在树中的下标
    int u=root;
    while(u){
        pushdown(u);
        int lsize=tr[tr[u].s[0]].size;
        if(lsize>=k) u=tr[u].s[0];
        else if(lsize==k-1) return u;
        else k-=lsize+1,u=tr[u].s[1];
    }
    return -1;
}

void modify_add(int x,int y,int d){
    int l=get_k(x),r=get_k(y+2);
    splay(l,0),splay(r,l);
    auto &T=tr[tr[r].s[0]];
    T.val+=d,T.min_val+=d,T.add+=d;
}

void modify_reverse(int x,int y){
    int l=get_k(x),r=get_k(y+2);
    splay(l,0),splay(r,l);
    tr[tr[r].s[0]].rev^=1;
    swap(tr[tr[r].s[0]].s[0],tr[tr[r].s[0]].s[1]);
}
```

---
### Part 5：区间旋转操作
这是本题最难也最核心的操作。注意到，将 $[x,y]$ 旋转 $y-x+1$ 的倍数次是无意义的，所以先让 $T$ 对 $y-x+1$ 取模。接下来，我们相当于让 $[x,y-T]$ 和 $[y-T+1,y]$ 交换。找到前一个区间把他删除，再加到后一个区间的后面即可。具体看代码。
```
void modify_revolve(int x,int y,int d){
    d%=y-x+1;
    if(!d) return;
    int l=get_k(x),r=get_k(y-d+2); //对应区间[x,y-d]
    splay(l,0),splay(r,l);
    pushdown(root),pushdown(r);
    int tmp=tr[r].s[0];
    tr[r].s[0]=0; //删除这个区间
    pushup(r),pushup(root);
    
    l=get_k(x+d),r=get_k(x+d+1); //找到删除后当前数列的第x+d个位置，对应删前的y位置
    splay(l,0),splay(r,l);
    pushdown(root),pushdown(r);
    tr[r].s[0]=tmp,tr[tmp].p=r; //把删掉的区间接在后面
    pushup(r),pushup(root);
}
```

---
### Part 6：插入和删除操作
splay 的基本操作。
```
void ins(int x,int d){
    int l=get_k(x+1),r=get_k(x+2);
    splay(l,0),splay(r,l);
    tr[r].s[0]=++idx;
    tr[tr[r].s[0]].init(d,r);
    pushup(r),pushup(root);
}

void del(int x){
    int l=get_k(x),r=get_k(x+2);
    splay(l,0),splay(r,l);
    tr[r].s[0]=0;
    pushup(r),pushup(root);
}
```

---
### Part 7：查询区间最值
只需把这个区间提取出来，其 $minval$ 就是答案。
```
LL query(int x,int y){
    int l=get_k(x),r=get_k(y+2);
    splay(l,0),splay(r,l);
    pushdown(root),pushdown(r);
    return tr[tr[r].s[0]].min_val;
}
```

---

### Part 8：完整代码
这样整道题就结束啦！总时间复杂度 $O(n \log n)$。最后附上完整代码~


```
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=2e5+5;

int n,m;
LL a[N];
struct Splay{
    int s[2],p,size;
    LL val,min_val,add;
    bool rev;
    void init(int _v,int _p){
        val=min_val=_v;
        p=_p,size=1;
    }
}tr[N];
int root,idx;

void pushup(int u){
    auto &lson=tr[tr[u].s[0]],&rson=tr[tr[u].s[1]];
    tr[u].size=lson.size+1+rson.size;
    tr[u].min_val=tr[u].val;
    if(tr[u].s[0]) tr[u].min_val=min(tr[u].min_val,lson.min_val);
    if(tr[u].s[1]) tr[u].min_val=min(tr[u].min_val,rson.min_val);
}

void pushdown(int u){
    auto &lson=tr[tr[u].s[0]],&rson=tr[tr[u].s[1]];
    if(tr[u].rev){
        if(tr[u].s[0]) swap(lson.s[0],lson.s[1]),lson.rev^=1;
        if(tr[u].s[1]) swap(rson.s[0],rson.s[1]),rson.rev^=1;
        tr[u].rev=0;
    }
    if(tr[u].add){
        LL &v=tr[u].add;
        if(tr[u].s[0]) lson.val+=v,lson.min_val+=v,lson.add+=v;
        if(tr[u].s[1]) rson.val+=v,rson.min_val+=v,rson.add+=v;
        v=0;
    }
}

void rotate(int x){
    int y=tr[x].p,z=tr[y].p;
    int k=(tr[y].s[1]==x);
    tr[z].s[tr[z].s[1]==y]=x,tr[x].p=z;
    tr[y].s[k]=tr[x].s[k^1],tr[tr[x].s[k^1]].p=y;
    tr[x].s[k^1]=y,tr[y].p=x;
    pushup(y),pushup(x);
}

void splay(int x,int k){
    while(tr[x].p!=k){
        int y=tr[x].p,z=tr[y].p;
        if(z!=k)
            if((tr[y].s[1]==x)^(tr[z].s[1]==y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if(!k) root=x;
}

void build(int &u,int p,int l,int r){
    if(l>r) return;
    u=++idx;
    int mid=l+r>>1;
    tr[u].init(a[mid],p);
    build(tr[u].s[0],u,l,mid-1);
    build(tr[u].s[1],u,mid+1,r);
    pushup(u);
}

int get_k(int k){ //找到编号为k的数在树中的下标
    int u=root;
    while(u){
        pushdown(u);
        int lsize=tr[tr[u].s[0]].size;
        if(lsize>=k) u=tr[u].s[0];
        else if(lsize==k-1) return u;
        else k-=lsize+1,u=tr[u].s[1];
    }
    return -1;
}

void modify_add(int x,int y,int d){
    int l=get_k(x),r=get_k(y+2);
    splay(l,0),splay(r,l);
    auto &T=tr[tr[r].s[0]];
    T.val+=d,T.min_val+=d,T.add+=d;
}

void modify_reverse(int x,int y){
    int l=get_k(x),r=get_k(y+2);
    splay(l,0),splay(r,l);
    tr[tr[r].s[0]].rev^=1;
    swap(tr[tr[r].s[0]].s[0],tr[tr[r].s[0]].s[1]);
}

void modify_revolve(int x,int y,int d){
    d%=y-x+1;
    if(!d) return;
    int l=get_k(x),r=get_k(y-d+2); //对应区间[x,y-d]
    splay(l,0),splay(r,l);
    pushdown(root),pushdown(r);
    int tmp=tr[r].s[0];
    tr[r].s[0]=0; //删除这个区间
    pushup(r),pushup(root);
    
    l=get_k(x+d),r=get_k(x+d+1); //找到删除后当前数列的第x+d个位置，对应删前的y位置
    splay(l,0),splay(r,l);
    pushdown(root),pushdown(r);
    tr[r].s[0]=tmp,tr[tmp].p=r; //把删掉的区间接在后面
    pushup(r),pushup(root);
}

void ins(int x,int d){
    int l=get_k(x+1),r=get_k(x+2);
    splay(l,0),splay(r,l);
    tr[r].s[0]=++idx;
    tr[tr[r].s[0]].init(d,r);
    pushup(r),pushup(root);
}

void del(int x){
    int l=get_k(x),r=get_k(x+2);
    splay(l,0),splay(r,l);
    tr[r].s[0]=0;
    pushup(r),pushup(root);
}

LL query(int x,int y){
    int l=get_k(x),r=get_k(y+2);
    splay(l,0),splay(r,l);
    pushdown(root),pushdown(r);
    return tr[tr[r].s[0]].min_val;
}

int main(){
    scanf("%d",&n);
    for(int i=1; i<=n; i++) scanf("%lld",&a[i]);
    a[0]=a[n+1]=1e18; //两侧加哨兵
    build(root,0,0,n+1);
    
    scanf("%d",&m);
    while(m--){
        string op;
        int x,y,z;
        cin>>op;
        if(op=="ADD"){
            scanf("%d%d%d",&x,&y,&z);
            modify_add(x,y,z);
        }
        else if(op=="REVERSE"){
            scanf("%d%d",&x,&y);
            modify_reverse(x,y);
        }
        else if(op=="REVOLVE"){
            scanf("%d%d%d",&x,&y,&z);
            modify_revolve(x,y,z);
        }
        else if(op=="INSERT"){
            scanf("%d%d",&x,&y);
            ins(x,y);
        }
        else if(op=="DELETE"){
            scanf("%d",&x);
            del(x);
        }
        else{
            scanf("%d%d",&x,&y);
            printf("%lld\n",query(x,y));
        }
    }
    return 0;
}
```

---

## 作者：Antarctica_Oabaijnaw (赞：2)

# 题目大意

您需要维护一个序列，支持以下操作：

- `ADD x y D` 将 $A_x$ 到 $A_y$ 加 $D$；
- `REVERSE x y` 翻转 $A_x$ 到 $A_y$；
- `REVOLVE x y T` 执行 $T$ 次将 $A_y$ 移动到 $A_x$ **之前**的操作；
- `INSERT x P` 将 $P$ 插入到 $A_x$ 之后；
- `DELETE x` 删除 $A_x$；
- `MIN x y` 查询 $A_x$ 到 $A_y$ 的最小值；

## **喜欢 Splay 指针版的同志们有福啦！**

谨以此题解纪念此题卡我 26 次的恩情！

众所周知，我们做此类区间操作的题目，都是用 FHQ-treap 或者 splay。由第一句可得，这是一篇 splay 的题解。不会 splay 区间操作的右转[【模板】文艺平衡树](https://www.luogu.com.cn/problem/P3391)。

---

**由于蒟蒻的指针版码风过于离谱，先把基础操作放前面：**

里面有 newnode, rotate, splay, pushup, pushdown, select 操作。

```cpp
struct node{
	node *ch[2],*fa;
	int siz;
	long long tag/*添加标记*/,minn/*最小值*/,val/*节点值*/;
	bool flag/*旋转标记*/;
}tree[1000005];
node *root/*根*/,*NIL/*空节点*/,*ncnt/*新建节点*/;
void init(){
	NIL=ncnt=&tree[0];
	NIL->minn=NIL->val=1e16;
	NIL->ch[0]=NIL->ch[1]=NIL->fa=NIL;
}
node *newnode(long long val){//新建节点
	node *p=++ncnt;
	p->ch[0]=p->ch[1]=p->fa=NIL;
	p->val=p->minn=val;
	p->siz=1;
	return p;
}
void rotate(node *x){//旋转
	node *y=x->fa;
	int d=(x==y->ch[0]);
	x->fa=y->fa;
	if(y->fa!=NIL)y->fa->ch[y==y->fa->ch[1]]=x;
	y->ch[!d]=x->ch[d]; 
	if(x->ch[d]!=NIL)x->ch[d]->fa=y;
	x->ch[d]=y;
	y->fa=x;
	if(root==y)root=x;
	pushup(y);
	pushup(x);
}
void splay(node *x,node *rt){//伸展
	node *y,*z;
	while(x->fa!=rt){
		y=x->fa;
		z=y->fa;
		if(z==rt)rotate(x);
		else{
			if((x==y->ch[0])^(y==z->ch[0]))rotate(x);
			else rotate(y);
			rotate(x);
		}
	}
}
void pushup(node *rt){
	if(rt==NIL)return;
	rt->siz=rt->ch[0]->siz+rt->ch[1]->siz+1;
	rt->minn=min({rt->val,rt->ch[0]->minn,rt->ch[1]->minn});
}
void pushdown(node *rt){
	if(rt->flag){
		swap(rt->ch[0],rt->ch[1]);
		if(rt->ch[0]!=NIL)rt->ch[0]->flag^=1;
		if(rt->ch[1]!=NIL)rt->ch[1]->flag^=1;
		rt->flag=0;
	}
	if(rt->tag){
		if(rt->ch[0]!=NIL){
			rt->ch[0]->tag+=rt->tag;
			rt->ch[0]->val+=rt->tag;
			rt->ch[0]->minn+=rt->tag;
		}
		if(rt->ch[1]!=NIL){
			rt->ch[1]->tag+=rt->tag;
			rt->ch[1]->val+=rt->tag;
			rt->ch[1]->minn+=rt->tag;
		}
		rt->tag=0;
	}
}
node *select(int k,node *fa){//根据排名查询值
	node *p=root;
	while(true){
		pushdown(p);
		if(p->ch[0]->siz+1>k)p=p->ch[0];
		else if(p->ch[0]->siz+1==k)break;
		else k-=(p->ch[0]->siz+1),p=p->ch[1];
	}
	splay(p,fa);
	return p;
}
```

注：由于加了**哨兵节点**，下文所有 select 操作第一个参数（即**排名**）都比**预期的**要多 $1$。

### Step 1：建树

~~我不会告诉你我以前建树都是直接无脑用 insert 函数。~~

由于此题太过毒瘤，我们使用专门的建树函数，将序列建成一棵近似于完全二叉树的形状。

```cpp
node *build(int l,int r){
	if(l>r)return NIL;
	int mid=(l+r)>>1;
	node *p=build(l,mid-1),*q=build(mid+1,r),*now=newnode(a[mid]);
	now->ch[0]=p;
	now->ch[1]=q;
	if(p!=NIL)p->fa=now;
	if(q!=NIL)q->fa=now;
	pushup(now);
	return now;
}
```

记得在主函数加上这么一句 `root=build(0,n+1);`。

---

### Step 2：ADD && REVERSE 操作

做过[【模板】文艺平衡树](https://www.luogu.com.cn/problem/P3391)都会的操作，标记即可。

```cpp
if(op=="ADD"){
    int l,r,k;
    cin>>l>>r>>k;
    node *p=select(l,NIL),*q=select(r+2,p);
    q->ch[0]->tag+=k;
    q->ch[0]->val+=k;
    q->ch[0]->minn+=k;
}else if(op=="REVERSE"){
    int l,r;
    cin>>l>>r;
    node *p=select(l,NIL),*q=select(r+2,p);
    q->ch[0]->flag^=1;
}
```

---

### Step 3：INSERT && DELETE 操作

本代码使用的 select 函数使得这两个操作变得尤为简便，代码如下：

```cpp
if(op=="INSERT"){
    int x,k;
    cin>>x>>k;
    node *p=select(x+1,NIL),*q=select(x+2,p);
    node *nw=newnode(k);
    q->ch[0]=nw;
    nw->fa=q;
}else if(op=="DELETE"){
    int x;
    cin>>x;
    node *p=select(x,NIL),*q=select(x+2,p);
    q->ch[0]=NIL;
}
```

---

### Step 4：REVOLVE 操作

**重中之重！**（蒟蒻就是因为特别构式的代码连 WA 20 余发，最后大改了一遍才 AC 的）

首先把 $T$ 对 $y-x+1$ 取模。

我们注意到（~~注意力惊人~~）REVOLVE 操作就表示将区间 $[y-T+1,y]$ 移到 $x$ 之前，于是就有下文的代码：

```cpp
if(op=="REVOLVE"){
    int l,r,d;
    cin>>l>>r>>d;
    d%=(r-l+1);
    if(d==0)continue;
    node *p=select(r-d+1,NIL),*q=select(r+2,p);
    node *tr=q->ch[0];
    q->ch[0]=NIL;
    p=select(l,NIL),q=select(l+1,p);
    q->ch[0]=tr;
    tr->fa=q;
}
```

---

### Step 5：MIN 操作

最简单的操作。

```cpp
if(op=="MIN"){
    int l,r;
    cin>>l>>r;
    node *p=select(l,NIL),*q=select(r+2,p);
    cout<<q->ch[0]->minn<<endl;
}
```

**终于结束了（狂喜！）**

## 完整代码

```cpp
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int n,m;
struct node{
	node *ch[2],*fa;
	int siz;
	long long tag,minn,val;
	bool flag;
}tree[1000005];
node *root,*NIL,*ncnt;
void init(){
	NIL=ncnt=&tree[0];
	NIL->minn=NIL->val=1e16;
	NIL->ch[0]=NIL->ch[1]=NIL->fa=NIL;
}
node *newnode(long long val){
	node *p=++ncnt;
	p->ch[0]=p->ch[1]=p->fa=NIL;
	p->val=p->minn=val;
	p->siz=1;
	return p;
}
void pushup(node *rt){
	if(rt==NIL)return;
	rt->siz=rt->ch[0]->siz+rt->ch[1]->siz+1;
	rt->minn=min({rt->val,rt->ch[0]->minn,rt->ch[1]->minn});
}
void pushdown(node *rt){
	if(rt->flag){
		swap(rt->ch[0],rt->ch[1]);
		if(rt->ch[0]!=NIL)rt->ch[0]->flag^=1;
		if(rt->ch[1]!=NIL)rt->ch[1]->flag^=1;
		rt->flag=0;
	}
	if(rt->tag){
		if(rt->ch[0]!=NIL){
			rt->ch[0]->tag+=rt->tag;
			rt->ch[0]->val+=rt->tag;
			rt->ch[0]->minn+=rt->tag;
		}
		if(rt->ch[1]!=NIL){
			rt->ch[1]->tag+=rt->tag;
			rt->ch[1]->val+=rt->tag;
			rt->ch[1]->minn+=rt->tag;
		}
		rt->tag=0;
	}
}
void rotate(node *x){
	node *y=x->fa;
	int d=(x==y->ch[0]);
	x->fa=y->fa;
	if(y->fa!=NIL)y->fa->ch[y==y->fa->ch[1]]=x;
	y->ch[!d]=x->ch[d]; 
	if(x->ch[d]!=NIL)x->ch[d]->fa=y;
	x->ch[d]=y;
	y->fa=x;
	if(root==y)root=x;
	pushup(y);
	pushup(x);
}
void splay(node *x,node *rt){
	node *y,*z;
	while(x->fa!=rt){
		y=x->fa;
		z=y->fa;
		if(z==rt)rotate(x);
		else{
			if((x==y->ch[0])^(y==z->ch[0]))rotate(x);
			else rotate(y);
			rotate(x);
		}
	}
}
void insert(node *&rt,node *p,long long val){
	if(rt==NIL){
		rt=newnode(val);
		rt->fa=p;
		splay(rt,NIL);
		return;
	}
	rt->siz++;
	insert(rt->ch[1],rt,val);
}
node *select(int k,node *fa){
	node *p=root;
	while(true){
		pushdown(p);
		if(p->ch[0]->siz+1>k)p=p->ch[0];
		else if(p->ch[0]->siz+1==k)break;
		else k-=(p->ch[0]->siz+1),p=p->ch[1];
	}
	splay(p,fa);
	return p;
}
long long a[100005];
node *build(int l,int r){
	if(l>r)return NIL;
	int mid=(l+r)>>1;
	node *p=build(l,mid-1),*q=build(mid+1,r),*now=newnode(a[mid]);
	now->ch[0]=p;
	now->ch[1]=q;
	if(p!=NIL)p->fa=now;
	if(q!=NIL)q->fa=now;
	pushup(now);
	return now;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	init();
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	a[0]=a[n+1]=1e16;//哨兵节点
	root=build(0,n+1);
	cin>>m;
	while(m--){
		string op;
		cin>>op;
		if(op=="ADD"){
			int l,r,k;
			cin>>l>>r>>k;
			node *p=select(l,NIL),*q=select(r+2,p);
			q->ch[0]->tag+=k;
			q->ch[0]->val+=k;
			q->ch[0]->minn+=k;
		}else if(op=="REVERSE"){
			int l,r;
			cin>>l>>r;
			node *p=select(l,NIL),*q=select(r+2,p);
			q->ch[0]->flag^=1;
		}else if(op=="REVOLVE"){
			int l,r,d;
			cin>>l>>r>>d;
			d%=(r-l+1);
			if(d==0)continue;
			node *p=select(r-d+1,NIL),*q=select(r+2,p);
			node *tr=q->ch[0];
			q->ch[0]=NIL;
			p=select(l,NIL),q=select(l+1,p);
			q->ch[0]=tr;
			tr->fa=q;
		}else if(op=="INSERT"){
			int x,k;
			cin>>x>>k;
			node *p=select(x+1,NIL),*q=select(x+2,p);
			node *nw=newnode(k);
			q->ch[0]=nw;
			nw->fa=q;
		}else if(op=="DELETE"){
			int x;
			cin>>x;
			node *p=select(x,NIL),*q=select(x+2,p);
			q->ch[0]=NIL;
		}else if(op=="MIN"){
			int l,r;
			cin>>l>>r;
			node *p=select(l,NIL),*q=select(r+2,p);
			cout<<q->ch[0]->minn<<endl;
		}
	}
}
```

---

## 作者：_zuoqingyuan (赞：2)

# 题目大意

给你一个初始长度为 $n$ 的不定长数列 $a$，要求你完成以下操作。

- 给定 $p,x$，在 $a_p$ 后**插入**一个数 $x$。

- 给定 $p$，删除 $a_p$。

- 给定 $l,r,x$，对于每个 $l\le i\le r$，令 $a_i\gets a_i+x$。

- 给定 $l,r$，求出 $\min\limits_{l\le i\le r}a_i$。

- 给定 $l,r$，将 $a_{l\sim r}$ **翻转**。

- 给定 $l,r,x$，将 $a_{l\sim r}$ 轮换 $x$ 次；每次轮换，将 $a_r$ 移至 $a_l$，将 $a_{l\sim r-1}$ 整体向后平移一个位置。**不保证 $x\le r-l+1$**。

其中，$n\le 10^5$。

# 思路分析

前置知识：平衡树。

插入，删除，区间翻转，这些均为平衡树的基本操作。对于这种维护序列的问题，我们普遍使用无旋 Treap 或 Splay。本文使用无旋 Treap。

在每个节点上，我们分别维护这个节点的左儿子，右儿子，本身的权值，子树大小，子树内的最小权值，在原数列中的下标。

实际上，一个数在数列中的下标，即为它的左子树大小加 $1$。所以我们只需要按照原数列中的顺序合并节点即可，不需要维护下标。

插入，删除，区间 $\min$，只需要通过简单的 split 即可实现，我们把重点放在区间加，区间翻转和区间轮换上。

## 区间轮换

对于 $a_{l\sim r}$ 轮换 $x$ 次，如果满足 $x\le r-l+1$，实际上相当于**倒序**把 $a_{r-x+1\sim r}$ 的元素依次插入到队头，即把 $a_{r-x+1\sim r}$ 这一段整体平移到了 $a_{l,r-x}$ 之前。

我们可以先分裂出 $a_{l\sim r}$，再将这一段分成  $a_{l,r-x}$ 和 $a_{r-x+1\sim r}$ ，然后我们再将**后者和前者**合并，注意顺序是颠倒的，因为这两段内部的先后关系不变，但是两段整体发生了变化，所以直接交换后合并即可。

且我们是通过子树大小的方法表示下标，不需要进行额外的操作修改，这样会方便许多，注意特判 $x> r-l+1$ 的情况。



```cpp
if(op[1]=='R'&&op[4]=='O'){
	scanf("%lld %lld %lld",&l,&r,&k);
	k%=(r-l+1);
	if(k==0)continue;
	split(rt,r,x,y),split(x,l-1,z,x);
	int a,b;split(x,r-l+1-k,a,b);
	rt=merge(merge(z,merge(b,a)),y);
}
```

## 区间加

收到线段树的启发，我们同样可以把懒标记搬到平衡树上。

我们额外在每个节点上维护一个 $tag1$，表示整颗子树内部增加了 $tag1$，对于懒标记下传，和线段树类似，分别更新子节点本身的权值，子树内最小值和它的 $tag1$。

对于何时下传懒标记，如果我们要访问一个节点的子节点，就下放这个节点的懒标记，防止子节点的信息未被更新。

```cpp
if(op[1]=='A'){
	scanf("%lld %lld %lld",&l,&r,&k);
	split(rt,r,x,y),split(x,l-1,z,x);
	a[x].tag1+=k,a[x].mn+=k,a[x].v+=k;
	rt=merge(merge(z,x),y);
}
```

## 区间翻转

[其实就是这个](https://www.luogu.com.cn/problem/P3391)。

对一棵平衡树整体翻转，等价于让这个平衡树内的每个节点都交换它的左右儿子。

这样我们也可以使用懒标记维护数列。


```cpp
if(op[1]=='R'&&op[4]=='E'){
	scanf("%lld %lld %lld",&l,&r,&k);
	split(rt,r,x,y),split(x,l-1,z,x);
	a[x].tag2^=1;//同一节点没有必要翻转两次
	rt=merge(merge(z,x),y);
}
```

然后我们就可以愉快的切了这道题啦，时间复杂度 $O(n\log n)$。

# Code


```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#define int long long
#define ls a[p].l
#define rs a[p].r
using namespace std;
const int N=2e5+10,inf=1e15+10;
int n,m,rt,tot;
struct node{
	int l,r,siz,v,mn,dat,tag1,tag2;//tag1 +,tag2 翻转 
}a[N];
int New(int val){//新建节点
	++tot;
	a[tot].l=0,a[tot].r=0;
	a[tot].v=a[tot].mn=val,a[tot].siz=1;
	a[tot].tag1=a[tot].tag2=0;
	a[tot].dat=rand();
	return tot;
}
void up(int p){//更新信息
	a[p].siz=a[ls].siz+a[rs].siz+1;
	a[p].mn=min(min(a[ls].mn,a[rs].mn),a[p].v);
}
void down(int p){//下穿标记
	if(a[p].tag1){//下穿加法标记
		int v=a[p].tag1;
		a[ls].tag1+=v,a[ls].v+=v,a[ls].mn+=v;
		a[rs].tag1+=v,a[rs].v+=v,a[rs].mn+=v;
		a[p].tag1=0;
	}
	if(a[p].tag2){//下传翻转标记
		a[ls].tag2^=1,a[rs].tag2^=1,swap(ls,rs),a[p].tag2=0;
	}
}
void split(int p,int k,int &x,int &y){//分裂
	if(!p)return x=y=0,void();
	down(p);//记得下传
	if(a[ls].siz>=k){
		split(ls,k,x,a[y=p].l);
		up(y);return;//记得更新
	}else{
		split(rs,k-a[ls].siz-1,a[x=p].r,y);
		up(x);return;
	}
	return;
}
int merge(int x,int y){
	if(!x||!y)return x+y;
	if(a[x].dat>a[y].dat){
		down(x),a[x].r=merge(a[x].r,y),up(x);//记得下传和更新
		return x;
	}else{
		down(y),a[y].l=merge(x,a[y].l),up(y);
		return y;
	}
}
signed main(){
	scanf("%lld",&n);
	a[0].mn=a[0].v=inf;//初始化
	for(int i=1,x;i<=n;i++){
		scanf("%lld",&x);
		rt=merge(rt,New(x));
	}
	scanf("%lld",&m);
	while(m--){
		char op[10];
		int l,r,k,x,y,z;
		scanf("%s",op+1);
		if(op[1]=='A'){//区间加
			scanf("%lld %lld %lld",&l,&r,&k);
			split(rt,r,x,y),split(x,l-1,z,x);
			a[x].tag1+=k,a[x].mn+=k,a[x].v+=k;
			rt=merge(merge(z,x),y);
		}
		if(op[1]=='R'&&op[4]=='E'){//区间翻转
			scanf("%lld %lld %lld",&l,&r,&k);
			split(rt,r,x,y),split(x,l-1,z,x);
			a[x].tag2^=1;
			rt=merge(merge(z,x),y);
		}
		if(op[1]=='R'&&op[4]=='O'){//区间轮换
			scanf("%lld %lld %lld",&l,&r,&k);
			k%=(r-l+1);
			if(k==0)continue;
			split(rt,r,x,y),split(x,l-1,z,x);
			int a,b;split(x,r-l+1-k,a,b);
			rt=merge(merge(z,merge(b,a)),y);
		}
		if(op[1]=='I'){//插入
			scanf("%lld %lld",&l,&k);
			split(rt,l,x,y);
			rt=merge(merge(x,New(k)),y);
		}
		if(op[1]=='D'){//删除
			scanf("%lld %lld",&l);
			split(rt,l,x,y),split(x,l-1,x,z);
			rt=merge(x,y);
		}
		if(op[1]=='M'){//查询 min
			scanf("%lld %lld",&l,&r);
			split(rt,r,x,y),split(x,l-1,z,x);
			printf("%lld\n",a[x].mn);
			rt=merge(merge(z,x),y);
		}
	}
	return 0;
}
```

如有错误，请指出。

---

## 作者：aCssen (赞：2)

### Solution
首先一个很重要的事情是 ```REVOLVE x y D``` 操作的含义是把 $[x,y]$ 中的最后一个数放到前面，重复这个操作 $D$ 次，其实就是把 $[y-D+1,y]$ 这个区间提到前面，再往后放上 $[x,y-D]$。

看到区间反转，直接上文艺平衡树。观察六个操作，发现中间的四个都不重要。只需要在平衡树维护区间最小值和加法 tag 即可。

使用 fhq treap，考虑分裂区间 $[x,y]$。首先在 $root$ 上分裂出大小为 $y$ 的区间，再在分裂出的树上分裂**掉**大小为 $x-1$ 的区间即可。剩下的这个根就有代表这个区间。可以直接查询这个点或在上面打 tag。

注意 tag 的含义与线段树一致：**该点信息已被正确维护，子节点信息还未更新。** 所以在分裂出的根上打 tag 时注意更新这个点的信息。

插入和删除都很简单，这里不再赘述。

轮换的时候，把代表这个区间的点在分裂出大小为 $y-D-x+1$ 的区间，假设这样分出来的树是 $a,b$，那么按照 $b,a$ 的顺序合并即可。记得把 $D$ 对区间长度取模。

时间复杂度 $\mathcal{O}(n \log n)$，难点主要在于实现。
### Code
```cpp
#include<iostream>
#include<cstdio>
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
typedef long long ll;
namespace FastIO{
    template<typename T=int> T read(){
        T x=0;int f=1;char c=getchar();
        while(!isdigit(c)){if(c=='-') f=~f+1;c=getchar();}
        while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
        return x*f;
    }
    template<typename T> void write(T x){
        if(x<0){putchar('-');x=-x;}
        if(x>9) write(x/10);
        putchar(x%10+'0');
    }
    template<typename T> void Write(T x,char c='\n'){write(x);putchar(c);}
}
using namespace FastIO;
const int maxn=2e5+5;
struct node{
    int ls,rs,key,dat,Min,siz,tag1,tag2;
}t[maxn];
int tot,root,seed=17539127,n,m,v;
int rnd(){
    int ret=seed;
    seed=(seed*7+13)%1000000007;
    return ret;
}
int Random(int N=998244353){
    return 1ll*rnd()*rnd()%N+1;
}
int New(int key){
    t[++tot]=(node){0,0,key,Random(),key,1,0,0};
    return tot;
}
void pushup(int p){
    t[p].siz=t[t[p].ls].siz+t[t[p].rs].siz+1;
    t[p].Min=t[p].key;
    if(t[p].ls) t[p].Min=min(t[p].Min,t[t[p].ls].Min);
    if(t[p].rs) t[p].Min=min(t[p].Min,t[t[p].rs].Min);
}
void pushtag(int p){
    t[p].tag1^=1;
    swap(t[p].ls,t[p].rs);
}
void pushdown(int p){
    if(t[p].tag1){
        pushtag(t[p].ls);
        pushtag(t[p].rs);
        t[p].tag1=0;
    }
    if(t[p].tag2){
        t[t[p].ls].tag2+=t[p].tag2;
        t[t[p].rs].tag2+=t[p].tag2;
        t[t[p].ls].Min+=t[p].tag2;
        t[t[p].rs].Min+=t[p].tag2;
        t[t[p].ls].key+=t[p].tag2;
        t[t[p].rs].key+=t[p].tag2;
        t[p].tag2=0;
    }
}
void split(int x,int S,int &p,int &q){
    if(!x){p=q=0;return;}
    pushdown(x);
    if(t[t[x].ls].siz+1<=S){
        p=x;
        split(t[x].rs,S-t[t[x].ls].siz-1,t[x].rs,q);
    }
    else{
        q=x;
        split(t[x].ls,S,p,t[x].ls);
    }
    pushup(x);
}
int merge(int x,int y){
    if(!x||!y) return x|y;
    if(t[x].dat<t[y].dat){
        pushdown(x);
        t[x].rs=merge(t[x].rs,y);
        pushup(x);
        return x;
    }
    pushdown(y);
    t[y].ls=merge(x,t[y].ls);
    pushup(y);
    return y;
}
void out(int x){
    if(!x) return;
    pushdown(x);
    out(t[x].ls);
    printf("%d ",t[x].key);
    out(t[x].rs);
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>v;
        root=merge(root,New(v));
    }
    cin>>m;
    while(m--){
        string opt;
        cin>>opt;
        if(opt=="ADD"){
            int l,r,x,y,z,k;
            cin>>l>>r>>k;
            split(root,r,x,z);
            split(x,l-1,x,y);
            t[y].Min+=k,t[y].key+=k,t[y].tag2+=k;
            root=merge(x,merge(y,z));
        }
        if(opt=="REVERSE"){
            int l,r,x,y,z;
            cin>>l>>r;
            split(root,r,x,z);
            split(x,l-1,x,y);
            pushtag(y);
            root=merge(x,merge(y,z));
        }
        if(opt=="REVOLVE"){
            int l,r,t,x,y1,y2,z;
            cin>>l>>r>>t;
            t%=(r-l+1);
            split(root,r,x,z);
            split(x,l-1,x,y1);
            split(y1,r-l+1-t,y1,y2);
            root=merge(merge(x,merge(y2,y1)),z);
        }
        if(opt=="INSERT"){
            int p,v,x,y;
            cin>>p>>v;
            split(root,p,x,y);
            root=merge(x,merge(New(v),y));
        }
        if(opt=="DELETE"){
            int p,x,y,z;
            cin>>p;
            split(root,p,x,z);
            split(x,p-1,x,y);
            root=merge(x,z);
        }
        if(opt=="MIN"){
            int l,r,x,y,z;
            cin>>l>>r;
            split(root,r,x,z);
            split(x,l-1,x,y);
            cout<<t[y].Min<<'\n';
            root=merge(x,merge(y,z));
        }
    //  out(root);
    }
    return 0;
}
```

---

## 作者：CNS_5t0_0r2 (赞：1)

建议先阅读我的 [FHQ-Treap 学习笔记](https://www.luogu.com.cn/article/spkrzsnn)，可能会有一些帮助。

插入、翻转、维护区间最值都是很简单的，只有这个 ``REVOLVE`` 是没见过的。

其实也不难，~~找一找规律~~，就会发现 ``REVOLVE`` 操作的本质就是将操作区间再分裂成左右两个区间，交换两个区间的位置。

知道了这一点，实现也就不难了。假设操作区间是 $[l,r]$，长度为 $len$，``REVOLVE`` 就是依次合并 $[l,l - 1]$，$[l + len - T + 1,r]$，$[l,l + len - T]$，$[r + 1,n]$。

```cpp
#include<bits/stdc++.h>
#define mid ((l + r) >> 1)
using namespace std;
const int N = 4e6 + 9,INF = 0x3f3f3f;
int n,m;
int a[N]; 
struct node{
	int val;
	int Min;
	int pri;
	int lc,rc;
	int siz;
	int rev_tag,add_tag;
} t[N];
int node_cnt,root;

void push_up(int u){
	t[u].siz = t[t[u].lc].siz + t[t[u].rc].siz + 1;
	t[u].Min = t[u].val;
	if(t[u].lc)
		t[u].Min = min(t[u].Min,t[t[u].lc].Min);
	if(t[u].rc)
		t[u].Min = min(t[u].Min,t[t[u].rc].Min);
}
void make_rev_tag(int u){
	t[u].rev_tag ^= 1;
	swap(t[u].lc,t[u].rc);
}
void make_add_tag(int u,int v){
	t[u].val += v;
	t[u].add_tag += v;
	t[u].Min += v;
} 
void push_down(int u){
	if(t[u].rev_tag){
		make_rev_tag(t[u].lc);
		make_rev_tag(t[u].rc);
		t[u].rev_tag = 0;
	}
	if(t[u].add_tag){
		make_add_tag(t[u].lc,t[u].add_tag);
		make_add_tag(t[u].rc,t[u].add_tag);
		t[u].add_tag = 0;
	}
}

void split(int u,int x,int &L,int &R){//将以u为根的子树分裂成以L,R为根的两棵子树满足左子树所大小为x，
	if(u == 0){
		L = R = 0;
		return;
	}
	push_down(u);
	if(t[t[u].lc].siz < x){
		L = u;
		split(t[u].rc,x - t[t[u].lc].siz - 1,t[u].rc,R);
	}
	else{
		R = u;
		split(t[u].lc,x,L,t[u].lc);
	}
	push_up(u);
}
int merge(int u,int v){//将以u为根的树和以v为根的子树合并并返回合并后的根 
	if(!u || !v)//如果其中一个根为空那么合并后的根就是另一个根 
		return u | v;
	push_down(u);
	push_down(v);
	if(t[u].pri > t[v].pri){//u优先级大于v优先级，则u应为v的父亲（大根堆性质） 
		t[u].rc = merge(t[u].rc,v);//t[t[u].lc].val <= t[u].val <= t[v].val，所以合并t[u].rc和v
		push_up(u);
		return u;
	}
	else{//否则v应为u的父亲 
		t[v].lc = merge(u,t[v].lc);//t[t[v].rc].val >= t[v].val >= t[u].val，所以合并u和t[v].lc 
		push_up(v);
		return v;
	}
}

int new_node(int x){
	t[++node_cnt] = (node){
						x,
						x,
						rand() * rand(),
						0,0,
						1,
						0,0
	};
	return node_cnt;
}

int build(int l,int r){
	if(l == r)
		return new_node(a[l]);
	int u = merge(build(l,mid),build(mid + 1,r));
	return u;
}
void Insert(int pos,int tot){
	int u,v;
	split(root,pos,u,v);
	for(int i = 1;i <= tot;i++)
		cin >> a[i];
	root = merge(merge(u,build(1,tot)),v);
}
void Delete(int l,int r){
	int u,v,w;
	split(root,r,u,w);
	split(u,l - 1,u,v);
	root = merge(u,w);
}
void Modify(int l,int r,int k){
	int u,v,w;
	split(root,r,u,w);
	split(u,l - 1,u,v);
	make_add_tag(v,k);
	root = merge(merge(u,v),w);
}
void Reverse(int l,int r){
	int u,v,w;
	split(root,r,u,w);
	split(u,l - 1,u,v);
	make_rev_tag(v);
	root = merge(merge(u,v),w);
}
void Revolve(int l,int r,int k){
	int u,v1,v2,w;
	split(root,r,u,w);
	split(u,l - 1,u,v1);
	split(v1,(r - l + 1) - k,v1,v2);
	root = merge(merge(u,merge(v2,v1)),w);
}

int query_Min(int l,int r){
	int u,v,w;
	split(root,r,u,w);
	split(u,l - 1,u,v);
	int ret = t[v].Min;
	root = merge(merge(u,v),w);
	return ret;
}

signed main(){
	srand(time(0));
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n;
	for(int i = 1;i <= n;i++)
		cin >> a[i];
	root = merge(root,build(1,n));
	cin >> m;
	while(m--){
		string op;
		int l,r,v;
		cin >> op;
		if(op == "ADD"){
			cin >> l >> r >> v;
			Modify(l,r,v);
		}
		else if(op == "REVERSE"){
			cin >> l >> r;
			Reverse(l,r);
		}
		else if(op == "REVOLVE"){
			cin >> l >> r >> v;
			v %= (r - l + 1);
			Revolve(l,r,v);
		}
		else if(op == "INSERT"){
			cin >> l;
			Insert(l,1);
		}
		else if(op == "DELETE"){
			cin >> l;
			Delete(l,l);
		}
		else if(op == "MIN"){
			cin >> l >> r;
			cout << query_Min(l,r) << '\n';
		}
	}
	return 0;
}
```

---

