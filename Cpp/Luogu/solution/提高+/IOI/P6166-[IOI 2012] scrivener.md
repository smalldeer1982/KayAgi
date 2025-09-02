# [IOI 2012] scrivener

## 题目描述

有些人说李奥纳多是一个对于 Johannes  Gutenberg 的崇拜者，Johannes 是一个发明活字印刷的德国铁匠，为了表达尊敬，李奥纳多设计了一台机器被称为小龙虾代书，那是一个非常简单的打字设备。这机器就像一部简单的现代打字机，但只能接受两个指令。一个指令是 输出一个字符，另一个指令是取消最近的指令。小龙虾代书的最大特点就是拥有这个功能强大的取消指令。因为一个取消指令本身也是一个指令，所以也可以被取消。

**说明**

你的任务是作出此小龙虾代书的程序，一开始并无输出任何文字，然后开始接受使用者输入的一连串指令，并可查询目前输出文字中的特定位置的字符。详细说明如下:

- `TypeLetter(L)` —附加一个小写字母L在输出文字的最后，$L$ 可以是 $a,b,\cdots, z$。

- `UndoCommands(U)` — 取消之前的 $U$ 个指令，$U$ 是一个正整数。

- `GetLetter(P)` — 回传在输出文字中位置为 $P$ 的字符，$P$ 是一个非负整数。 输出文字中的第一个字符的位置为 $0$。 （这个查询并不是一个指令，因此会被取消指令忽略。）

三种操作可以依照任何顺序被呼叫 $0$ 次或多次以上。

指令 `UndoCommands(U)` 会依照原本执行的相反顺序来取消前面 $U$ 个指令: 如果被取消的指令是 `TypeLetter(L)`，就会从输出文字最后面移除字母 $L$。如果被取消的指令是 `UndoCommands(X)`，那么将会依照原本执行的顺序重新执行之前被取消的 $X$ 个指令。

**范例**

我们列出一连串可能的指令，以及每次执行指令后的输出文字。

| 操作 | 回传 | 输出文字 |
| :-----------: | :-----------: | :-----------: |
| `TypeLetter(a)` |  | `a` |
| `TypeLetter(b)` |  | `ab` |
| `GetLetter(1)` | `b` | `ab` |
| `TypeLetter(d)` |  | `abd` |
| `UndoCommands(2)` |  | `a` |
| `UndoCommands(1)` |  | `abd` |
| `GetLetter(2)` | `d` | `abd` |
|  `TypeLetter(e)`|  | `abde` |
| `UndoCommands(1)` |  | `abd` |
| `UndoCommands(5)` |  | `ab` |
|`TypeLetter(c)`  |  | `abc` |
| `GetLetter(2)` | `c` | `abc` |
| `UndoCommands(2)` |  | `abd` |
| `GetLetter(2)` | `d` | `abd` |


## 说明/提示

对于 $100\%$ 的数据，$1 \le N \le 10^6$。参数 $U$ 保证不会超过前面已经输入的指令数目，而且参数 $P$ 一定小于输出文字的长度（也就是输出文字的字母数）。

## 样例 #1

### 输入

```
10
T c
T z
T u
T a
T i
T h
T f
T z
P 3
P 0
```

### 输出

```
a
c
```

## 样例 #2

### 输入

```
98
T u
T g
T p
T h
T w
P 3
P 0
T d
T d
T r
T v
T z
T w
T h
P 0
T d
T v
T b
P 9
T n
T e
P 0
T s
T i
T a
P 6
T b
T n
T m
T t
T m
T g
T y
T g
P 0
T m
P 18
T r
P 17
T w
T w
T o
T m
T m
P 0
T q
P 5
T t
P 27
P 34
T p
T f
T h
T j
T f
T l
P 3
T f
T q
T h
P 17
T w
T d
T p
T z
P 0
T m
P 10
T o
P 5
P 18
P 7
T q
T z
P 2
T u
P 10
T e
P 6
T s
T t
P 24
T s
P 0
T t
T c
P 4
T j
T o
P 5
T i
P 11
T a
T t
P 58
P 51
P 64
P 12
```

### 输出

```
h
u
u
z
u
d
u
i
s
u
d
g
m
h
s
u
w
d
i
r
p
w
d
m
u
w
d
h
s
o
a
d
```

# 题解

## 作者：Alex_Wei (赞：20)

> [题面传送门](https://www.luogu.com.cn/problem/P6166)

> ~~原来 IOI 也有这么水的题目。~~

和 [P1383](https://www.luogu.com.cn/problem/P1383) 几乎一模一样，赶紧去水吧（

看到撤销操作，基本上就是主席树了，是一道主席树的练手题。

对于 `T` 操作：在原来的版本上新建一个版本。

对于 `U` 操作：把根换到 $x$ 次操作以前的版本。

对于 `P` 操作：打印当前版本上的第 $x$ 的字符，如果你的主席树区间从 $1$ 开始，就要 $x\gets x+1$。需要注意的是每次的修改不算一个指令。

然后就是很基础的实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,m,nd,r[N],ls[N<<5],rs[N<<5],sz[N<<5];
char val[N<<5];
void modify(int pre,int &x,int l,int r,char c){
	sz[x=++nd]=sz[pre]+1,ls[x]=ls[pre],rs[x]=rs[pre];
	if(l==r){val[x]=c; return;}
	int m=l+r>>1;
	if(sz[ls[pre]]<m-l+1)modify(ls[pre],ls[x],l,m,c);//左边还有空位，就往左边跑
	else modify(rs[pre],rs[x],m+1,r,c);
}
char query(int id,int l,int r,int pos){
	if(l==r)return val[id];
	int m=l+r>>1;
	if(pos<=sz[ls[id]])return query(ls[id],l,m,pos);
	else return query(rs[id],m+1,r,pos-sz[ls[id]]);
}
int main(){
	cin>>n,m=n;
	for(int i=1;i<=m;i++){
		char s,x; int p; cin>>s;
		if(s=='T')cin>>x,modify(r[i-1],r[i],1,n,x);
		if(s=='U')cin>>p,r[i]=r[i-p-1];
		if(s=='P')cin>>p,i--,m--,cout<<query(r[i],1,n,p+1)<<'\n';
	}
	return 0;
}
```

求赞 awa。

---

## 作者：cyffff (赞：7)

# P6166 [IOI2012]scrivener
#### [_传送门_](https://www.luogu.com.cn/problem/P6166)

~~蒟蒻第一道IOI题，开森$awa$~~
## 思路
看到一道可持久化的字符串操作题，我立马打了一个叫做`rope`的数据结构。机房dalao说这是一个用可持久化红黑树实现的数据结构，我们先来学习一下`rope`的用法。

首先要使用`rope`，需要加上一下两行：
```cpp
#include<ext/rope>
using namespace __gnu_cxx;
```

然后我们可以定义一个字符串类型的`rope`，叫做`crope`，要这样定义：

```cpp
crope now;
crope s[10];
```

`crope`支持的操作：

- `a.push_back(x)`：在`crope a`的末尾增加字符串`x`
- `a.insert(k,x)`：在`a`的第`k`个字符后加入字符串`x`
- `a.erase(k,x)`：在`a`的第`k`个字符后删除`x`个字符
- `a.replace(k,x)`：将`a`的第`k`个字符后`x`的长度个字符删除，并插入`x`
- `a.substr(k,x)`：获取`a`的第`k`个字符后的长度为`x`的字符串
- `a.at(k)`：获取`a`的第`k`个字符（从0开始）

我们可以拿一个数组来保存历史版本（反正不卡空间），每次读入操作，执行操作，保存到第$V$个历史版本中。

- 对于操作$T$，我们可以使用`push_back`（或`insert`）
- 对于操作$U$，我们可以直接回退到$V-x$的版本
- 对于操作$P$，我们可以使用`at`（或`substr`）

`crope`为什么可以通过此题呢？机房的dalao说它的复制操作是$O(log\enspace n)$的，可以较轻松地实现可持久化。

上AC代码~
```cpp
#include<bits/stdc++.h>
#include<ext/rope>//头文件
using namespace __gnu_cxx;
using namespace std;
const int N=1e6+10;
crope now,x[N];//定义crope，保存现在的串与历史版本
int t,p,V;
inline char read(){
	char ch=getchar();
	while((ch>'U'||ch<'P')&&(ch>'z'||ch<'a')){
		ch=getchar();
	}
	return ch;
}
inline void solve(){//操作
	char opt=read();
	switch(opt) {
		case 'T': {//T操作
			char q=read();
			now.insert(p,q);
			p++;
			x[++V]=now;
			break;
		}
		case 'U': {//U操作
			int q;
			scanf("%d",&q);
			now=x[V-q];
			x[++V]=now;
			break;
		}
		case 'P': {//P操作
			int q;
			scanf("%d",&q);
			putchar(now.at(q));
			puts("");
			break;
		}
	}
}
signed main() {
	scanf("%d",&t);
	while(t--) {
		solve();
	}
	return 0;
}
```
最后送出[ $\textcolor{#000000}{双倍经验}$ ](https://www.luogu.com.cn/problem/P1383)

再见qwq

---

## 作者：MY（一名蒟蒻） (赞：5)

向辛苦审核题解的管理道歉，感谢指出排版错误，确实是我孤陋寡闻了。

[P6166 [IOI2012]scrivener](https://www.luogu.com.cn/problem/P6166)
## 闲话
蒟蒻my最近学了主席树，这可真是个好东西，他决定写篇题解加深下印象。
- [P3919 【模板】可持久化线段树 1（可持久化数组）](https://www.luogu.com.cn/problem/P3919)
- [P3834 【模板】可持久化线段树 2（主席树）](https://www.luogu.com.cn/problem/P3834)

主席树，又名函数式线段树。由于发明人黄嘉泰的名字缩写和某位中国共产党领导人是一样的，故名主席树。

实现可持久化使用复制节点的方式，由于一次修改最多修改 $\log n$ 个节点，于是需要开 $n\log n$ 的空间。

弱化版 [P1383 高级打字机](https://www.luogu.com.cn/problem/P1383) ,所谓挑战指的应该就是这题了。

---
## 做法
首先没有初始版本，于是不需要建树。

1. 对于输入字符操作，我们维护一个 $\text{len}$ 表示这个节点维护的区间的字符长度，实际上只有根节点的 $\text{len}$ 值有用，但是我懒得理他了（doge
2. 对于撤销操作，直接让当前版本根节点指向之前的版本即可。**注意撤销最后 $\text{x}$ 个操作不是直接复制 $\text{x}$ 版本**。
3. 对于查询操作，记得线段树维护的区间从 $\text{1}$ 开始，位置要对应加一，然后在最新版本查询。
4. 注意询问操作并不生成一个新版本，所以版本号要另外统计。

---
## Code

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N=1e6+10;

int n,cnt,rt[N],tot;
struct node {int l,r,len; char c;} hjt[N << 5];
inline int clone(int now) {hjt[++cnt]=hjt[now]; return cnt;}//复制

int modify(int now,int l,int r,int p,char ch)
{
	now=clone(now); hjt[now].len++;//只会修改log个节点，不用写pushup 
	if(l == r) {hjt[now].c=ch; return now;}
	int mid=(l+r) >> 1;
	if(p <= mid) hjt[now].l=modify(hjt[now].l,l,mid,p,ch);
	else hjt[now].r=modify(hjt[now].r,mid+1,r,p,ch);
	return now;
}

char query(int now,int l,int r,int p)
{
	if(l == r) return hjt[now].c;
	int mid=(l+r) >> 1;
	if(p <= mid) return query(hjt[now].l,l,mid,p);
	return query(hjt[now].r,mid+1,r,p);
}

int main()
{
// 	freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	scanf("%d",&n);
	char op,ch;
	int x;
	for(int i=1;i<=n;i++)
	{
		scanf(" %c",&op);
		if(op == 'T') {scanf(" %c",&ch); tot++; rt[tot]=modify(rt[tot-1],1,n,hjt[rt[tot-1]].len+1,ch);}//在最后插入新字符
		if(op == 'U') {scanf("%d",&x); tot++; rt[tot]=rt[tot-x-1];}//指向旧版本，注意这个版本号
		if(op == 'P') {scanf("%d",&x); printf("%c\n",query(rt[tot],1,n,x+1));}
	}
// 	fclose(stdin); fclose(stdout);
	return 0;
}
```
吐槽弱化版数据过水，空间只开 $\text{n}$ 都能过。
## Thank you for your reading!
您的点赞和评论是对作者最大的支持！

---

## 作者：EnofTaiPeople (赞：3)

通过如下初始化：
```cpp
#include<ext/rope>
using namespace __gnu_cxx;
```
可以引用 $rope$——可持久化块状链表！

它支持 $O(\sqrt{n})$ 取出子序列、序列连接，$O(1)$ 在序列后添加元素。

优点在于，它自带可持久化，空间复杂度为 $O(n\sqrt{n}+C)$，$C$ 为插入的总数。

此题中，可以暴力开 $10^6$ 个 $rope$，直接通过：
```cpp
#include<cstdio>
#include<ext/rope>
using namespace __gnu_cxx; 
const int N=1e6+5;
typedef rope<char> Rp;
Rp rp[N];
char buf[N+5],*p1,*p2,c;
#define gc (p1==p2&&(p2=(p1=buf)+fread(buf,1,N,stdin),p1==p2)?EOF:*p1++)
inline void read(int &x){
	for(c=gc;c<'0'||c>'9';c=gc);
	for(x=0;c>='0'&&c<='9';x=x*10+c-'0',c=gc);
}
inline void read(char &x){while(!isalpha(x=gc));}
int q,now,x;
int main(){
	read(q);
	while(q--){
		read(c);
		if(c=='P'){read(x);putchar(rp[now][x]),putchar('\n');}
		else {++now;
			if(c=='T'){read(c),rp[now]=rp[now-1],rp[now].append(c);}
			else read(x),rp[now]=rp[now-x-1];
		}
	}return 0;
}
```

---

## 作者：KarL05 (赞：3)

这个问题存在一个极度简单的线性离线做法。

对于所有的 `T` 操作, 构造一棵树, 类似于一棵字典树。当有一个新的 `T` 的操作的时候, 做一个新的节点, 其父亲是上一个字符串所对应的在树上节点的位置。

对于所有的 `U` 操作, 可以理解为在树上进行移动。这个操作并不为我们目前有的字符串的集合做出任何改变, 所以我们只需要找到 Undo 若干个操作时候得到的字符串在树上的位置即可。对于一个 `U x`的 Undo 操作, 他的字符串一定是和第 $u-x-1$ 次操作所构成的字符串是一样的。

对于所有的 `P` 操作, 预处理找到这个目前的字符串在树上的位置。问题就被转化成了点到根的链的地 $x$ 个点的权值。

这个新的问题可以用 DFS 维护一个栈来解决。

具体而言, 进入某个点之后, 我们将这个点的字符压入栈。离开某个点之后, 将这个点的字符弹出栈, 此时, 我们就可以得到点到根的这个链的字符串。从根节点做一次 DFS, 然后在每次走到一个节点时求出这个节点所对应的询问即可。

时间复杂度 : $O(n)$

```
//#include<bits/stdc++.h>
#include<iostream>
#include<vector>
using namespace std;


const int maxn = 1e6+5;
vector<int> E[maxn];
vector<int> q[maxn];
vector<int> Q[maxn];
vector<int> query[maxn];
vector<int> Query[maxn];
int pter;
int id[maxn];
char val[maxn];
vector<char> Op;
vector<string> In;

int toInt (string s) {
	int ans = 0; int n = s.size();
	for (int i=0;i<n;i++) {
		ans = ans*10+s[i]-'0';
	}
	return ans;
}
void construct (int n) {
	int at = 0;
	Op.push_back(0);
	In.push_back("0");
	for (int i=1;i<=n;i++) {
		char op;cin>>op;
		string in;cin>>in;
		if (op=='P') {
			q[at].push_back(toInt(in));
			query[at].push_back(i);
			continue;
		}
		++at;
		Op.push_back(op);
		In.push_back(in);
	} 
	n = at; 
	at = 0;
	for (int i=1;i<=n;i++) {
		char op = Op[i];
		if (op=='T') {
			id[i] = ++pter;
			val[pter] = In[i][0];
			E[at].push_back(pter);
			at = pter;
		}
		if (op=='U') {
			int x = toInt(In[i]);
			id[i] = id[i-1-x];
			at = id[i];
		}
	}
	for (int i=0;i<=n;i++) {
		for (int j=0;j<q[i].size();j++) Q[id[i]].push_back(q[i][j]);
		for (int j=0;j<q[i].size();j++) Query[id[i]].push_back(query[i][j]);
	}
}

int stk[maxn];
int tail = 0;
char ans[maxn];

void debug () {
	cout<<"Stack : ";
	for (int i=2;i<=tail;i++) {
		cout<<stk[i]<<" ";
	}
	cout<<endl;
} 
void DFS (int u, int f) {
	stk[++tail] = val[u];
	// debug();
	for (int i=0;i<Q[u].size();i++) {
		int cur = Q[u][i];
		// cout<<stk[cur+2]<<endl;
		ans[Query[u][i]] = stk[cur+2];
	}
	for (int i=0;i<E[u].size();i++) {
		int v = E[u][i];
		if (v==f) continue;
		DFS(v,u);
	}
	--tail;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;cin>>n;
	construct(n);
	DFS(0,-1);
	// for (int w=1;w<=n;w++) {
		// int i = id[w];
		// cout<<"Id : "<<id[w]<<endl;
		// cout<<"Edge : ";
		// for (int j=0;j<E[i].size();j++) cout<<E[i][j]<<" ";
		// cout<<endl;
		// cout<<"Val : "<<val[i]<<endl;
		// cout<<"q : ";
		// for (int j=0;j<Q[i].size();j++) cout<<Q[i][j]<<" ";
		// cout<<endl;
		// cout<<"---------"<<endl;
	// }
	for (int i=1;i<=n;i++) {
		if (ans[i]) cout<<ans[i]<<"\n";
	}
}
```



---

## 作者：星空舞涵 (赞：3)

# 前言
关于这道题，我看题解里很多大佬都是用的主席树，但是身为一个蒟蒻我并不会，所以我选择了树上倍增。
# 正文
我们用$f[ i ][ j ]$表示j的第$2^i$个祖先

$lian[ i ]$表示在第i步修改操作结束后下一次增添的点得父亲的序号

$tree[ i ]$表示序号为i的节点的字符是什么

$fa$表示下一个添加的点得父亲，也是目前的叶节点

$deep[ i ]$表示深度，即第几个字符

对于“T”操作来讲 ：

每进行一次T操作，就增添一个新的节点，有效操作数增加

对于“P”操作来讲：

每进行一次P操作，就是找从根节点到叶节点（fa）这一条链上，深度为m的点

对于“U”操作来讲：

每进行一次U操作，就是相当于一次换爹操作，把fa换成$lian[ i ] $

大概内容就这些，下面是代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[21][1000001],lian[1000001],cnt,fa,l,m,er[21],deep[10000001],n,x;
char a,tree[1000001];
int main()
{
	cin>>n;
	er[0]=1;
	for(int i=1;i<=20;i++)	er[i]=er[i-1]*2;
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		if(a=='T')
		{
			x++;//有效操作+1
			cnt++;//增加新的点 
			cin>>tree[cnt];//点cnt的字符 
			lian[x]=cnt;//这一步结束后下一个点的父亲 
			f[0][cnt]=fa;//自己的父亲 
			deep[cnt]=deep[fa]+1;
			for(int i=1;i<=20;i++)f[i][cnt]=f[i-1][f[i-1][cnt]];
			fa=cnt;//下一个点的父亲是自己吧 
		}
		if(a=='P')
		{
			cin>>m;
			m=m+1;
			int r=fa;
			for(int i=20;i>=0;i--)
			{
				if(deep[r]-er[i]>=m)
				{
					r=f[i][r];
				} //能跳就跳 
				if(deep[r]==m)
				{
					cout<<tree[r]<<endl;
					break;
				}	
			}
		}
		if(a=='U')
		{
			cin>>m;
			x++;
			lian[x]=lian[x-m-1]; 
			fa=lian[x];
		} 
	}
} 
```


---

## 作者：Limit (赞：2)

# 题目大意

给出一个空字符串支持在末尾加上一个字符,查询某个位置的字符,回到 $k$ 个操作前.

# 分析

显然的可持久化数组,可以通过可持久化线段树实现,为了方便处理,开始的区间是 $1$ 到 $1000000$ 开始,这样保证不会出问题,加上一个数就直接单点修改,查询也只要直接单点查询,对于每次修改对于修改的区间部分产生一个新的版本,其他仍然用之前版本的部分.

# 代码

```cpp
#include<bits/stdc++.h>
#define RAP(i,first,last) for(int i=first;i<=last;++i)
#define LSON tree[now].lson
#define RSON tree[now].rson
#define MIDDLE ((left+right)>>1)
#define LEFT LSON,left,MIDDLE
#define RIGHT RSON,MIDDLE+1,right
#define NOW now_left,now_right
#define NEW_LSON tree[new_tree].lson
#define NEW_RSON tree[new_tree].rson
using namespace std;
const int maxM=2e6+7;
int N=1e6/*从1e6开始查询*/,M;
struct Tree
{
	int sum,lson,rson;
}tree[maxM*32];
int cnt=0;
void UpData(int &new_tree,int num,int ch,int now,int left=1,int right=N)//标准可持久化线段树
{
	if(num<left||right<num)//如果不会被修改就直接用原来的内容
	{
		new_tree=now;
		return;
	}
	new_tree=++cnt;//否则产生一个新的点
	if(left==right)//到叶节点就直接单点修改
	{
		tree[new_tree].sum=ch;
		return;
	}
	UpData(NEW_LSON,num,ch,LEFT);
	UpData(NEW_RSON,num,ch,RIGHT);
}
int Query(int k,int now,int left=1,int right=N)//单点查询
{
	if(k<left||right<k)return 0;
	if(left==right)//叶节点直接返回
	{
		return tree[now].sum;
	}
	return Query(k,LEFT)+Query(k,RIGHT);
}
int root[maxM];//记录每次修改的线段树的根节点编号
int len[maxM];//记录每个版本的数组长度
int main()
{
	cin>>M;
	char ch;
	int x;
	char add;
	int tot=0;//记录当前修改操作个数
	RAP(i,1,M)
	{
		cin>>ch;
		if(ch=='T')//修改部分
		{
			++tot;
			cin>>add;
			len[tot]=len[tot-1]+1;
			UpData(root[tot],len[tot],add,root[tot-1]);
		}
		if(ch=='U')//回到x个版本前,就直接改变线段树的根节点就好了
		{
			++tot;
			cin>>x;
			root[tot]=root[tot-x-1];
			len[tot]=len[tot-x-1];
		}
		if(ch=='P')//单点查询
		{
			cin>>x;
			printf("%c\n",Query(x+1,root[tot]));
		}
	}
	return 0;
}
```

---

## 作者：king_xbz (赞：1)

看到还没有用STL::rope方法来做的，我就来当第一个吃螃蟹的人吧！！！
# 前置芝士
rope是一种底层为平衡树的可持久化操作数据结构。

### 我们先来了解一下如何操作吧！

**使用rope需要使用新的头文件与空间**：
```cpp
#include<ext/rope>
using namespace __gnu_cxx;
```
该namespace与std不同，该头文件也与万能头不同，需要在代码中分别使用。

**rope常与指针相伴**：
定义方法
```cpp
rope<char> *now[p];
```
**如何申请更新一个新的可持久化版本**：
```cpp
now[0]=new rope<char>();
```
**如何继承版本**
```cpp
now[cnt]=new rope<char>(*now[cnt-1]);
```
**如何回到查询过去的版本**
```cpp
ans=now[cnt]->at(num);
```
那么我们就有了一棵主席树了，是不是很简单呢？！

# 具体实现
对于T操作，我们构建新版本（从上一个版本继承），并压入字符

对于U操作，我们继承之前第num个版本作为新版本继承

对于P操作，我们查询之前第num个版本并输出

完整代码：
```cpp
#include<bits/stdc++.h>
#include<ext/rope>
using namespace std;
using namespace __gnu_cxx;
const int p=5794385;
int cnt;
rope<char> *now[p];
int main()
{
	int n;
	cin>>n;
	char op,str;
	int num;
	now[0]=new rope<char>();
	for(int i=1;i<=n;i++)
	{
		cin>>op;
		if(op=='T')
		{
			cin>>str;
			cnt++;
			now[cnt]=new rope<char>(*now[cnt-1]);
			now[cnt]->push_back(str);
		}
		if(op=='U')
		{
			cin>>num;
			cnt++;
			now[cnt]=new rope<char>(*now[cnt-num-1]);
		}
		if(op=='P')
		{
			cin>>num;
			cout<<now[cnt]->at(num)<<endl;
		}
	}
	return 0;
}
```
最后，祝大家AC愉快。

**彩蛋**：还有双倍经验可以拿哟（略有不同）：[高级打字机](https://www.luogu.com.cn/problem/P1383)

---

## 作者：珈乐唯毒 (赞：1)

萌新做的第一道IOI！！！！

因为有撤销操作，所以可以想到主席树

主席树所占空间巨大，所以在建树时可以不记录左端点和右端点的值，只记录节点所代表的字母，这样可以节省大量空间。

下面讲代码思路。

用两个数组来分别记录当前版本的根节点编号以及当前字符串的长度，版本只在添加操作以及撤销操作时才会增加，对于查询操作不管它。

添加操作时，直接按照字典树常规操作添加，增加版本即可。

撤销操作直接将根节点更新为撤销操作版本号减去撤销次数的上一个版本即可

下见代码
```
#include<bits/stdc++.h>
using namespace std;
const int N=1000005,NN=N*32;
int n,tot,root[N];
char t[NN];
int ls[NN],rs[NN],len[N];
char ans;
void build(int f,int l,int r){
	if(l==r)
		return;
	int mid=(l+r)>>1;
	ls[f]=++tot;
	build(tot,l,mid);
	rs[f]=++tot;
	build(tot,mid+1,r);
	return;
}
void add(int ff,int tf,int w,int l,int r,char q){
	if(l==r){
		t[ff]=q;
		return;
	}
	ls[ff]=ls[tf];
	rs[ff]=rs[tf];
	int mid=(l+r)>>1;
	if(mid<w){
		rs[ff]=++tot;
		add(tot,rs[tf],w,mid+1,r,q);
	}
	else{
		ls[ff]=++tot;
		add(tot,ls[tf],w,l,mid,q);
	}
	return;
}
void query(int u,int l,int r,int w){
	if(l==r){
		ans=t[u];
		return;
	}
	int mid=(l+r)>>1;
	if(mid>=w)
		query(ls[u],l,mid,w);
	else
		query(rs[u],mid+1,r,w);
}
int main(){
	int tott=0;
	cin>>n;
	root[0]=++tot;
	build(1,1,n);
	for(int i=1;i<=n;i++){
		char c;
		getchar();
		c=getchar();
		if(c=='T'){
			tott++;
			len[tott]=len[tott-1];
			getchar();
			char u;
			u=getchar();
			root[tott]=++tot;
			len[tott]++;
			add(tot,root[tott-1],len[tott],1,n,u);
		}
		if(c=='P'){
			int u;
			scanf("%d",&u);
			u++;
			query(root[tott],1,n,u);
			putchar(ans);
			putchar('\n');
		}
		if(c=='U'){
			int u;
			scanf("%d",&u);
			tott++;
			root[tott]=root[tott-u-1];
			len[tott]=len[tott-u-1];
		}
	}
	return 0;
}
```


---

## 作者：happybob (赞：0)

本题与[这题](https://www.luogu.com.cn/problem/P1383)基本完全一样，只是字符的下标这里是从 $0$ 开始。

显然，这是可持久化线段树的较为简单的模板题。撤销事实上只是换根，就是将当前的根换成 $x$ 次操作之前的根，线段树动态开点即可。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

const int N = 1e6 + 5;

int n;

class Persis_Segment_Tree
{
public:
	struct Node
	{
		int l, r;
		char val;
		int cnt;
	}tr[N * 25];
	int root[N], idx;
	Persis_Segment_Tree() : idx(1) {}
	void insert(int& now, int pr, int l, int r, char p)
	{
		now = ++idx;
		tr[now] = tr[pr];
		if (l > r) return;
		if (l == r)
		{
			tr[now].cnt++;
			tr[now].val = p;
			return;
		}
		int mid = l + r >> 1;
		if (tr[tr[pr].l].cnt == mid - l + 1)
		{
			insert(tr[now].r, tr[pr].r, mid + 1, r, p);
		}
		else insert(tr[now].l, tr[pr].l, l, mid, p);
		tr[now].cnt = tr[tr[now].l].cnt + tr[tr[now].r].cnt;
	}
	char query(int u, int l, int r, int k)
	{
		if (l >= r) return tr[u].val;
		int mid = l + r >> 1;
		if (k <= tr[tr[u].l].cnt) return query(tr[u].l, l, mid, k);
		return query(tr[u].r, mid + 1, r, k - tr[tr[u].l].cnt);
	}
};

Persis_Segment_Tree sg;

int main()
{
	scanf("%d", &n);
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		char a, b;
		cin >> a;
		if (a == 'T')
		{
			cin >> b;
			cnt++;
			sg.insert(sg.root[cnt], sg.root[cnt - 1], 1, n, b);
		}
		else if (a == 'U')
		{
			int x;
			scanf("%d", &x);
			cnt++;
			sg.root[cnt] = sg.root[cnt - x - 1];
		}
		else
		{
			int x;
			scanf("%d", &x);
			x++;
			cout << sg.query(sg.root[cnt], 1, n, x) << "\n";
		}
	}
	return 0;
}
```


---

## 作者：gcwixsxr (赞：0)

这是本蒟蒻的第一道IOI题目，发现没有多少空间小的题解（~~万一卡空间呢~~），于是来分享一下本蒟蒻的想法。

看见各位大佬都用的主席树，本蒟蒻不会主席树，只能用一些简单的方法。

首先我们可以把每个增加了字符（即 $L$ 操作）的历史版本的编号作为该字符的编号，并且把它视为一个结点。那么对于 $L$ 操作，如果某个历史版本 $v_1$是从历史版本 $v_2$ 转变过来的，则我们可以在结点 $v_1$ 到 $v_2$ 之间连一条边。对于 $U$ 操作，就直接转移至 $U$ 操作所指的结点处，并且新增一个历史版本（因为$U$ 操作可以撤回$U$ 操作）即可。由此不断操作下去，则结点就连成了一棵树型的结构（以历史版本 $0$ 为根节点）。

解释一下几个变量：

```cpp
int n;
int fa[MAXN],a[MAXN],tot,cnt;
int ord[MAXN],num[MAXN];
```
$n$ 是指总共命令的个数，$tot$ 是 $L$ 操作的个数，$cnt$ 是 $L$ 操作和 $U$ 操作的总个数，也就是所有历史版本的个数。

$fa$数组：$fa_i$代表 $i$ 结点的父亲结点。

$a$数组：$a_i$代表 $i$ 结点的权值（即字符）。

$ord$数组：$ord_i$代表第 $i$ 个历史版本。

$num$数组：$num_i$代表 $i$ 结点的深度（以历史版本 $0$ 为根节点），这个数组的用处是，输出时由于输出的是从左往右数的第 $k$ 个字符，用 $num$ 数组可以将原数据转化为从右往左数的第 $num_i-k+1$ 个字符，即 $i$ 结点的第 $num_i-k+1$ 个祖先。

那么 $L$ 操作就变成了新增结点的过程，$U$ 操作就变成了转移结点的过程，$P$ 操作就变成了找到某个结点的某个祖先的过程。

以下为 $70$ 分的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e7+10;
int n;
int fa[MAXN],a[MAXN],tot,cnt;
int ord[MAXN],num[MAXN];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		char od;
		cin>>od;
		if(od=='T'){
			char x;cin>>x;
			a[++tot]=x;
			fa[tot]=ord[cnt];
			num[tot]=num[fa[tot]]+1;
			ord[++cnt]=tot;
		}
		else if(od=='U'){
			int x;cin>>x;
			++cnt;
			ord[cnt]=ord[cnt-1-x];
		}
		else{
			int x;cin>>x;
            x++;
			int ans=ord[cnt];
			x=num[ans]-x+1;
			while(--x){
				ans=fa[ans];
			}
			putchar(a[ans]);
			puts("");
		}
	}
	return 0;
}
```

- 问：为什么只有 $70$ 分？
- 答：向上找祖先的过程太久，时间复杂度太大，导致TLE。

那么怎么找祖先最快呢，（想想当时求LCA时用了什么），没错，就是倍增。

将$fa$数组删去，增加 $f$ 数组。

```cpp
int f[MAXN][20];
int lg[MAXN];
```
$f$数组：$f_{i,j}$代表 $i$ 结点的第$2^j$个祖先结点。

$lg$数组：$lg_i$代表 $\log_2i$。

以下为 $100$ 分的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+10;
int n;
int a[MAXN],tot,cnt;
int ord[MAXN],num[MAXN],lg[MAXN];
int read(){
	int res = 0;
	char c = getchar();
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) res = (res << 1) + (res << 3) + c - 48, c = getchar();
	return res;
}
int f[MAXN][20];
int climb(int x,int l){
	while(l){
		int p=lg[l];
		x=f[x][p];
		l-=(1<<p);
	}
	return x;
}
signed main(){
	n=read();
	for(int i=2;i<=MAXN;i++)lg[i]=lg[i/2]+1;
	for(int i=1;i<=n;i++){
		char od;
		cin>>od;
		if(od=='T'){
			char x;cin>>x;
			a[++tot]=x;
			f[tot][0]=ord[cnt];
			for(int i=1;i<=18;i++){
				int to1=f[tot][i-1];
				int to2=f[to1][i-1];
				if(to1==0||to2==0) break;
				f[tot][i]=to2;
			}
			num[tot]=num[f[tot][0]]+1;
			ord[++cnt]=tot;
		}
		else if(od=='U'){
			int x;x=read();
			++cnt;
			ord[cnt]=ord[cnt-1-x];
		}
		else{
			int x;x=read();
            x++;
			putchar(a[climb(ord[cnt],num[ord[cnt]]-x)]);
			puts("");
		}
	}
	return 0;
}
```
时间复杂度$O(nlogn)$，卡过此题。
空间实测 $60M$（至少比主席树小吧）。

---

