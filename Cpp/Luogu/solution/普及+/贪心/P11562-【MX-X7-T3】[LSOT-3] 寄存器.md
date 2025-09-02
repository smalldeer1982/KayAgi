# 【MX-X7-T3】[LSOT-3] 寄存器

## 题目背景

原题链接：<https://oier.team/problems/X7D>。

这里不是 APIO，所以这个题也不是让你手搓 CPU。

## 题目描述

有 $n$ 个寄存器，编号为 $1 \sim n$。这些寄存器由 $n-1$ 条带有开关的电线连接。为了保证交换信息的顺利，保证每两个寄存器都可以通过若干条电线连接。

初始时每个寄存器存储的信息都是 $0$。小 H 每次可以独立地操纵所有电线的开关然后选择一个寄存器通电。若一个寄存器与一个通电的寄存器有**开启的电线**相连，则这个寄存器也会通电。所有通电的寄存器都会反转存储的信息（$0$ 会变成 $1$，$1$ 会变成 $0$）。小 H 想让寄存器存储他想要的信息，他希望你告诉他最少需要进行多少次**通电**。

## 说明/提示

**【样例解释 #1】**

先将电线 $(1, 2)$ 关闭，其余开启，给寄存器 $1$ 通电，此时 $1$ 的信息翻转，所有寄存器存储的信息变为 `1 0 0 0 0`。

然后将电线 $(2, 4)$ 关闭，其余开启，给寄存器 $4$ 通电，此时 $4$ 的信息翻转，所有寄存器存储的信息变为 `1 0 0 1 0`，满足要求。

可以证明不存在更优的方案。

**【数据范围】**

**本题采用捆绑测试。**

- 子任务 1（20 分）：$n\le 5$。
- 子任务 2（20 分）：对于第 $i$ 根电线，$u=i$，$v=i+1$。
- 子任务 3（30 分）：不存在一对相邻的寄存器希望储存的信息相同。
- 子任务 4（30 分）：无特殊性质。

对于全部的数据，$1\le n\le 10^6$，$1\le u,v\le n$，$0 \le a_i \le 1$，每两个寄存器都可以通过若干条电线连接。

## 样例 #1

### 输入

```
5
1 0 0 1 0
1 2
2 3
2 4
3 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
15
1 0 0 0 0 1 0 1 1 1 0 0 1 1 0
10 2
1 7
1 5
9 7
14 2
4 11
6 5
9 15
4 5
5 3
5 14
13 5
5 8
5 12
```

### 输出

```
4
```

# 题解

## 作者：icaijy (赞：16)

这一道题的 subtask 给了很多线索。先跳过用来打暴力的第一个子任务，我们从第二个子任务开始观察。

第二个子任务有 $u_i=i, v_i=i+1$，显然意思是整个树是一个链。我们可以把这题从树转换到数组来做。相当于给你一个只包含 $0$ 和 $1$ 的数组，求你对相同长度，全为 $0$ 的数组进行至少几次区间翻转操作能将其变成第一个数组。

考虑如下例子：

`1 1 1 0 0 0 1 1 1 0 0 0 0 0 0 1 1 1 1 0 0 0 1 1`

发现一段连续的相同的段，我们肯定会一起操作。因此我们可以把它简化成：

`1 0 1 0 1 0 1`

这时我们有两种选择，第一种是直接每次操作 $1$ 的位置把 $0$ 变成 $1$，这样要操作四次。或者先把整个数组翻转，再操作 $0$ 的位置，不过这样仍然是四次。因此这一子任务只需要输出有几个连续的 $1$ 即可。

接下来考虑第三个子任务，发现这个和我们刚刚考虑的情况很相似，即把联通的一大块看成一个点。但这时会发现我们刚刚只操作 $1$ 或都翻转后操作 $0$ 的办法行不通了。这时我们画一个新的例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/crurr5wi.png)

若沿用之前的思路，那这个图需要四次操作。不过我们发现这个图可以这样操作：

1. 翻转整个图。
2. 断开下面三个 $1$ 的边，再翻转整个图。
3. 翻转根节点，即顶部的 $1$。

我们发现，对于树只需要操作它的层数次即可。

不过层数该怎么求呢？首先发现假如 $0$ 在叶节点，或它的子孙也都是 $0$，那就可以不管了，直接断开连接让他们一直不改即可。我们真正要改的是 $1$。这时，我们只需构造一个树使得他的层数最小即可。这里的层数是指根节点到叶节点 $0,1$ 交替的次数。比如上图根节点到叶节点最远是 $1,0,1$，所以层数是 $3$，答案也是 $3$。

这时只需最小化最长的链。这时可以用树的直径的思路。找出从 $1$ 开始且以 $1$ 结束最长的链，让他们的中点作为根节点，这样就保证了层数最小，这题也就做出来了。这里我用两次 dfs 找直径，不会的话先去做一下[树的直径](https://www.luogu.com.cn/problem/B4016)。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a[1000005]={114514};
vector<int> adj[1000005];

int maxp,maxd;

void dfs(int cur,int par,int deep){
    if (a[cur]!=a[par]) deep++;
    if (a[cur]==1&&deep>maxd) {
        maxd=deep;
        maxp=cur;
    }
    for (int i:adj[cur]) if (i!=par) dfs(i,cur,deep);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin>>n;
    bool noone=true; // 特判一波全为0
    for (int i=1;i<=n;i++) {
        cin>>a[i];
        if (a[i]==1) noone=false;
    }
    if (noone){
        cout<<0;
        return 0;
    }
    for (int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0,0);
    maxd=0;
    dfs(maxp,0,0);
    cout<<(maxd+1)/2;
    return 0;
}
```

---

## 作者：keep_silence (赞：7)

很快就能发现，题目等价于一次翻转一个连通块，对于三个连通块 $a,b,c$，假设 $a,c$ 需要翻转，$b$ 不需要，而 $b$ 夹在两个中间，那么单独翻 $a,c$ 与一起翻花一样的次数，所以就等于值为 $1$ 的点的连通块数量。

很快就能发现还有一种情况，把包含所有权值为 $1$ 的点的最小的树给翻转了，再去把权值为 $0$ 的翻回来，那就是在这棵树上的权值为 $0$ 的点的连通块数量，两个取最小值。那问题来了，我们怎么找这棵树呢？

我们再仔细思考一下，就可以发现所有度数为 $1$ 的权值为 $0$ 的点都是不会进入这棵树中的，想想为什么。那么把第一波删完后，又有新的符合条件的点，这个过程拓扑即可。

然后就做完了。

代码？自己写去！

---

## 作者：良心WA题人 (赞：6)

题意可以是认为找到一块连通块并翻转 $0/1$。

考虑对于最终要求相同的一块连通块每次都可以同时操作，所以可以看成一个点。最后会缩成相邻两两不同的一颗树。显然想要操作这棵树对于每个相邻的都需要翻转一次，最优情况显然是以直径中点为根，对于每个 $i$，每次操作距离根长度小于等于 $i$ 的所有点。端点可能不需要操作，讨论一下即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace fastio
{
    const int bufl=1<<20;
    const double base1[16]={1,1e-1,1e-2,1e-3,1e-4,1e-5,1e-6,1e-7,1e-8,1e-9,1e-10,1e-11,1e-12,1e-13,1e-14,1e-15};
    const double base2[16]={1,1e1,1e2,1e3,1e4,1e5,1e6,1e7,1e8,1e9,1e10,1e11,1e12,1e13,1e14,1e15};
    struct IN{
        FILE *IT;char ibuf[bufl],*is=ibuf,*it=ibuf;
        IN(){IT=stdin;}IN(char *a){IT=fopen(a,"r");}
        inline char getChar(){if(is==it){it=(is=ibuf)+fread(ibuf,1,bufl,IT);if(is==it)return EOF;}return *is++;}
        template<typename Temp>inline void getInt(Temp &a){a=0;int b=0,c=getChar();while(c<48||c>57)b^=(c==45),c=getChar();while(c>=48&&c<=57)a=(a<<1)+(a<<3)+c-48,c=getChar();if(b)a=-a;}
        template<typename Temp>inline void getDouble(Temp &a){a=0;int b=0,c=getChar(),d=0;__int128 e=0,f=0;while(c<48||c>57)b^=(c==45),c=getChar();while(c>=48&&c<=57)e=(e<<1)+(e<<3)+c-48,c=getChar();if(c==46){c=getChar();while(c>=48&&c<=57)d++,f=(f<<1)+(f<<3)+c-48,c=getChar();}a=e+base1[d]*f;if(b)a=-a;}
        IN& operator>>(char &a){a=getChar();return *this;}
        IN& operator>>(char *a){do{*a=getChar();}while(*a<=32);while(*a>32)*++a=getChar();*a=0;return *this;}
        IN& operator>>(string &a){char b=getChar();while(b<=32)b=getChar();while(b>32)a+=b,b=getChar();return *this;}
        IN& operator>>(int &a){getInt(a);return *this;}
        IN& operator>>(long long &a){getInt(a);return *this;}
        IN& operator>>(__int128 &a){getInt(a);return *this;}
        IN& operator>>(float &a){getDouble(a);return *this;}
        IN& operator>>(double &a){getDouble(a);return *this;}
        IN& operator>>(long double &a){getDouble(a);return *this;}
    };
    struct OUT{
        FILE *IT;char obuf[bufl],*os=obuf,*ot=obuf+bufl;int Eps;long double Acc;
        OUT(){IT=stdout,Eps=6,Acc=1e-6;}OUT(char *a){IT=fopen(a,"w"),Eps=6,Acc=1e-6;}
        inline void ChangEps(int x=6){Eps=x;}
        inline void flush(){fwrite(obuf,1,os-obuf,IT);os=obuf;}
        inline void putChar(int a){*os++=a;if(os==ot)flush();}
        template<typename Temp>inline void putInt(Temp a){if(a<0){putChar(45);a=-a;}if(a<10){putChar(a+48);return;}putInt(a/10);putChar(a%10+48);}
        template<typename Temp>inline void putLeading(Temp a,int b){if(!b)return;putLeading(a/10,b-1);putChar(a%10+48);}
        template<typename Temp>inline void putDouble(Temp a){if(a<0){putChar(45);a=-a;}__int128 b=a;putInt(b);a-=b;a*=base2[Eps];b=a+Acc;putChar(46);putLeading(b,Eps);}
        OUT& operator<<(char a){putChar(a);return *this;}
        OUT& operator<<(char *a){while(*a>32)putChar(*a++);return *this;}
        OUT& operator<<(string a){for(auto c:a)putChar(c);return *this;}
        OUT& operator<<(int a){putInt(a);return *this;}
        OUT& operator<<(long long a){putInt(a);return *this;}
        OUT& operator<<(__int128 a){putInt(a);return *this;}
        OUT& operator<<(float a){putDouble(a);return *this;}
        OUT& operator<<(double a){putDouble(a);return *this;}
        OUT& operator<<(long double a){putDouble(a);return *this;}
        ~OUT(){flush();}
    };
}
using fastio::IN;
using fastio::OUT;
IN fin;
OUT fout;
const int NN=1e6+4;
int d[NN],w[NN];
bool vis[NN];
vector<int>g[NN];
int dfs(int u,int fa)
{
    vis[u]=true;
	int k=u;
	d[u]=1;
	for(auto v:g[u])
	{
		if(v==fa)
			continue;
		int p=dfs(v,u);
		if(w[u]==w[v]&&d[v]>d[u])
		{
			k=p;
			d[u]=d[v];
		}
		if(w[u]!=w[v]&&d[v]+1>d[u])
		{
			k=p;
			d[u]=d[v]+1;
		}
	}
	return k;
}
int main()
{
	int n;
	fin>>n;
	assert(n<=1000000);
	for(int i=1;i<=n;i++)
		fin>>w[i];
	for(int i=1;i<n;i++)
	{
		int u,v;
		fin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int x,y=dfs(x=dfs(1,0),0);
	int t=d[x];
	if(!w[x])
		t--;
	if(!w[y])
		t--;
	fout<<(t+1)/2;
	for(int i=1;i<=n;i++)
	    assert(vis[i]);
	return 0;
}
```

---

## 作者：wxccd2z (赞：6)

贪心 + 连通块 + 树上直径

首先，我们很容易发现操作的本质是选择一个连通块，并将其反转。连通块操作问题 trick，可以直接缩成点，因为本质缩成点后的点操作可以等价于连通块操作。

这时候树变成了一层 $1$ 和一层 $0$ 的树，随后开始贪心的构造最优方法。很显然，我们每次最多只能消掉最底下一层。所以我们发现我们在确定一个节点为根以后，答案就是树的高度，所以很显然，最优的根便是根节点，答案是 $\left \lceil \frac{len}{2} \right \rceil$，其中 $len$ 是直径。

[更多的内容](https://www.luogu.com.cn/article/bd0g6983)

---

## 作者：Dream_poetry (赞：6)

### 思路：

抽象图论。

可喜可贺，我最爱图论了。

![](https://cdn.luogu.com.cn/upload/image_hosting/d5uml4m3.png)

首先有个显然的东西是所给的一定是一棵树。

如图，我们要使 ```1 2 5 6 7 ``` 点为 $1$，其余点为 $0$。下文我们钦定目标为 $1$ 的点是黑点，反之是白点。

由于可以随便断边，所以我们考虑先找到一个最小覆盖，使它包含了黑点。

然后为了方便操作，我们应该先把同目标点进行缩点操作，上图也就变为了：

![](https://cdn.luogu.com.cn/upload/image_hosting/46ten2x7.png)

其中红框内部分是我们找到的最小覆盖。

我们可以发现，我们得到的是一棵树，满足它所有的根节点都是黑点。

我们考虑怎样操作是最优的。

我们考虑，第一次将全树染一边色，所有根节点达成目标为黑色，可以直接删去，使得根节点变为目标是白色的黑色点。

第二次全树染色，此时根节点变为白色，达成目标，可删去。

以此类推，不难发现这种做法每次都会使所有根节点达到可行状态，正确性比较明显，但可惜我并不是很会证明。

我们考虑统计答案吧，由于每次操作都会使得所有根节点变成目标颜色，相当于对于一条链来说，每次都使得它的两端被删掉了，也就是说一条链至多被处理它所包含的点数除以二上取整次。

对于整棵树来说，它至多被处理 $\dfrac{len+1+1}{2} \text{即} \dfrac{len+2}{2}$ 次，其中 $len$ 表示这棵树直径的长度，显然。

请注意，此处的树指的是我们得到的最小覆盖在缩点后形成的树，并非原树或最小覆盖，请注意甄别。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int a[5000005];
struct node{
	int nex,to;
}e[5000005],E[5000005];
int he[5000005],He[5000005];
int tot;
int ttt;

node e2[5000005];
int tt2;
int he2[5000005];

inline void add2(int x,int y){
	e2[++tt2].nex=he2[x];
	e2[tt2].to=y;
	he2[x]=tt2;	
}

inline void add(int x,int y){
	e[++tot].nex=he[x];
	e[tot].to=y;
	he[x]=tot;
}
int top;
int col[5000005];

inline void Add(int x,int y){
	E[++ttt].nex=He[x];
	E[ttt].to=y;
	He[x]=ttt;
}
int id[5000005];


inline void dfs(int x,int fa){
	col[x]=top;
	for (register int i=he[x];i;i=e[i].nex){
		int v=e[i].to;
		if (!col[v] && v!=fa && a[x]==a[v]){
			dfs(v,x);
		}
	}
}

int ans;
int bj[5000005];

inline void solve(int x,int fa){
	if (id[x]==1){
		bj[fa]=1;
	}	
	for (register int i=He[x];i;i=E[i].nex){
		int v=E[i].to;
		if (v!=fa){
			solve(v,x);
		}
	}
}


inline void Solve(int x,int fa){
	if (a[x]==1){
		bj[fa]=1;
	}	
	for (register int i=he[x];i;i=e[i].nex){
		int v=e[i].to;
		if (v!=fa){
			Solve(v,x);
		}
	}
}
int f[5000005];
int vis[5000005];


inline void dp(int x){
	vis[x]=1;
	for (int i=he2[x];i;i=e2[i].nex){
		int v=e2[i].to;
		int w=1;
		if (vis[v]) continue;
		dp(v);
		ans=max(ans,f[x]+f[v]+1);
		f[x]=max(f[x],f[v]+1);
	}
}
int flag;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for (register int i=1;i<=n;i++){
		cin>>a[i];
	}	
	for (register int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		if (a[x]==a[y]){
			flag=1;
		}
		add(x,y);
		add(y,x);
	}
	for (register int i=1;i<=n;i++){
		if (!col[i]){
			top++;
			dfs(i,0);
		}
	}
	for (register int x=1;x<=n;x++){
		id[col[x]]=a[x];
		for (register int i=he[x];i;i=e[i].nex){
			int v=e[i].to;
			if (col[x]!=col[v]){
				Add(col[x],col[v]);
			}
		}
	}
	for (register int T=1;T<=n;T++){
		if (a[T]==1){
			solve(col[T],0);
			int st;
			
			for (register int x=1;x<=top;x++){
				if (bj[x]==1){
					st=x;
					for (int i=He[x];i;i=E[i].nex){
						int v=E[i].to;
						add2(x,v);
						add2(v,x);
					}
				}
			}
			dp(st);
			cout<<(ans+2)/2;
			return 0;
		}
	}
	cout<<0;
	return 0;
}
```

---

## 作者：MnZnOIer (赞：5)

### 前言
考场上想了一个比较糖的连通块做法：要么先把整棵树染一遍，把 $0$ 的连通块单独染一遍，要么直接染 $1$ 的连通块。

### 解题思路
显然这种做法是假的，对于每个连通块只有一个点的情况显然不最优。

我们结合 sub 2，可以想到把所有连通块缩到同一点。继续思考，可以在树上交替反转染色，所以答案为 $\lceil \frac{d}{2}\rceil$，$d$ 为树的直径。

### 代码部分
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5;
int n, a[N], d[N], h[N], c;
struct Edge{int v, nxt;}e[N << 1];
void add (int a, int b){e[++ c] = Edge{b, h[a]}, h[a] = c;}
void dfs (int u, int fa)
{
	d[u] = d[fa] + (a[u] != a[fa]);
	for (int i = h[u]; i; i = e[i].nxt)
	{
		int v = e[i].v;
		if (v == fa)continue;
		dfs (v, u);
	}
}
signed main ()
{
	ios::sync_with_stdio (0), cin.tie (0), cout.tie (0);
	cin >> n;
	for (int i = 1; i <= n; ++ i)cin >> a[i];
	for (int i = 1, u, v; i < n; ++ i)
	{
		cin >> u >> v;
		add (u, v);
		add (v, u);
	}
	int p = 1;
	dfs (1, 0);
	for (int i = 1; i <= n; ++ i)if (d[i] > d[p])p = i;
	dfs (p, 0);
	for (int i = 1; i <= n; ++ i)if (d[i] > d[p])p = i;
	cout << ((d[p] + 1) >> 1);
	return 0;
}
```

---

## 作者：A_small_WA (赞：4)

本题的思路我就不讲了，这篇题解主要说一下具体的实现方式。楼上楼下很多大佬都说了：就是用黑色表示 $1$，用白色表示 $0$。把相邻的同颜色的点合并（缩点），最后求树的直径 $\div 2$，**注意要向上取整且直径首尾均为黑色点**。

本蒟蒻看完这些题解后，就立马开始缩点：
```cpp
void sd(int x,int y){
	//缩点，将X的连边全给Y并删除X 
	for(int i=0;i<vt[x].size();i++){
		int w=vt[x][i];
		if(w!=y) vt[y].push_back(w);
	}
	vt[x].erase(vt[x].begin(),vt[x].end());
}
void dfs1(int x,int fa){
	for(int i=0;i<vt[x].size();i++){
		int w=vt[x][i];
		if(w!=fa&&a[w]==a[x]){
			dfs1(w,x);
			sd(w,x);
			vt[x].erase(vt[x].begin()+i);
		}
	}
	sort(vt[x].begin(),vt[x].end());
	it=unique(vt[x].begin(),vt[x].end());
	vt[x].erase(it,vt[x].end());
	//去重，CSDN里搜的。 
	return;
}
```
但我立马就发现这样做时间复杂度太高，于是还没写完就去交了一发：[record](https://www.luogu.com.cn/record/197840678)。

还好及时止损，要不然我算完直径后才发现 TLE 不得直接破防？

于是我又到题解区翻了一下大佬们的代码，好家伙，没有一个人缩点？仔细看一下，其实不用缩点，在原本求树的直径代码特判：如果 $a_u=a_v$，那么从点 $u$ 到点 $v$ 是不用加距离的。这样就成功实现了把相邻同颜色点看作一个整体。具体代码如下：
```cpp
void dfs(int x,int d){
	//求距离 
	if(dis[x]<=d) return;
	dis[x]=d;
	for(int i=0;i<vt[x].size();i++){
		int w=vt[x][i];
		if(a[w]==a[x]) dfs(w,d);
		else dfs(w,d+1);
		//特判，颜色相同则视为一个点。 
	}
}
```

最后加上读入和输出即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1000020;
bool a[N];
int dis[N];
vector <int> vt[N];
void dfs(int x,int d){ 
	if(dis[x]<=d) return;
	dis[x]=d;
	for(int i=0;i<vt[x].size();i++){
		int w=vt[x][i];
		if(a[w]==a[x]) dfs(w,d);
		else dfs(w,d+1);
		//特判，颜色相同则视为一个点。 
	}
}
int main(){
	int n,bj=0,u,v;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		dis[i]=1e9;
	}
	for(int i=1;i<n;i++){
		cin>>u>>v;
		vt[u].push_back(v),vt[v].push_back(u);
        //使用邻接表
	}
	//这里树的直径用了算两次的思想。 
	dfs(1,1);
	int mx=0,lz=0;
	for(int i=1;i<=n;i++){
		if(mx<dis[i]&&a[i]) lz=i,mx=dis[i];
		dis[i]=1e9;
	}
	//注意起点距离要从1开始 
	dfs(lz,1);
	mx=0;
	for(int i=1;i<=n;i++){
		if(a[i]) mx=max(mx,dis[i]);
		//if(a[i]) 这条语句用来判断是否结束点是黑色的，上同。
		//如果结束点是白色的，那么就不用操作，舍去。
	}
	cout<<(mx+1)/2;//向上取整：a/2向上取整=(a+1)/2 
	return 0;
}
```
本题的主要难点就在于求直径和缩点的思路不好想。但通过第 $2,3$ 个子任务的特殊性质也就简单一些了。

这是本蒟蒻的第 $14$ 篇题解，感谢观看。

---

## 作者：gghack_Nythix (赞：4)

## 前言：

警示后人，数组大小要开够，不然你就会像我一样调一天还不知道错哪里了。

## 分析：

首先你很容易得到一个错误思路：将所有存储消息为 $0$ 的点拿出来按照 $b_i$ 从大到小排序，然后根据 $b_i$ 大小来确定该修改几次，其中 $b_i$ 是与 $i$ 点相连的存储消息需要变成 $1$ 的点的个数。最后你写了一发发现这个做法假完了，来个链就爆掉了。

那么这种时候**重新审题**，发现题意相当于用最少的操作次数将整个树变成规定颜色状态，一次操作是将树上的一个连通块颜色反转。

这种时候很显然可以把同色的点缩成一坨，然后原问题就转换成了 sub3 的做法。

那么 sub3 怎么做呢？我们可以首先将树的最底部的的 $0$ 点去掉，显然他们没用。然后你可以只讨论树的直径的中点的情况，为什么？设中点为 $m$，则一定不存在一个点 $n$ 使得 $\operatorname{dis}\{m,a\}\leq \operatorname{dis}\{n,b\}$ 且 $\operatorname{dis}\{m,c\}\leq \operatorname{dis}\{n,d\}$。其中 $a$ 和 $c$ 是离 $m$ 点最远和次远的点，然后 $c$ 和 $d$ 是离 $n$ 点最远和次远的点。所以说 $m$ 点的操作次数是最少的，因为操作次数 $q$ 一定大于等于上文提及的两个距离的最大值。

然后你确定了只用考虑中点之后，答案就很显然了，就是交替反转的次数，即为 $\left \lceil \frac{len}{2} \right \rceil $，其中 $len$ 为直径长度。

然后就做完了。

讲一下实现：你只需要把相邻且同色的点深度设为一样，然后求出每个点的深度 $d_i$ 后取一个最大的 $d_i$，设他的下标是 $x$，以 $x$ 为根再跑一遍上文的实现就求出了缩完点之后的直径。最后，请**一定要记得开大数组！**

```cpp
# include <bits/stdc++.h>
# define int long long 
# define pb push_back
using namespace std;
const int N = 1e6 + 5;
int n , a[N];
vector <int> g[N];
int d[N];
void dfs (int now , int fa) {
	d[now] = 1;
	if (a[now] == a[fa] && d[fa] != d[now]) d[now] = d[fa];
	else if (a[now] == a[fa] && d[fa] == d[now]) ;
	else if (a[now] != a[fa]) d[now] = d[fa] + 1;
	for (auto x : g[now]) {
		if (x == fa) continue;
		dfs (x , now);
	}
}
bool none;
signed main () {
	ios::sync_with_stdio(false) ,cin.tie(0);
	cin >> n;
	for (int i = 1;i <= n;++i) cin >> a[i] , none |= (a[i] == 1);
	for (int i = 1;i < n;++i) {
		int u , v; cin >> u >> v ,
		g[u].pb (v) , g[v].pb (u);
	}
	if (!none) return cout << "0\n" , 0;
	int id1 = 1;
	dfs (id1 , 0);
	for (int i = 1;i <= n;++i) if (d[i] > d[id1]) id1 = i;
	int id2 = 1;
	dfs (id1 , 0);
	for (int i = 1;i <= n;++i) if (d[i] > d[id2]) id2 = i;
	int ans = d[id2] ;
	return cout << (ans + 1) / 2 << "\n" , 0;
}
```

---

## 作者：Pratty (赞：3)

赛时没有想出来，可惜了。

赛后发现并不是毒瘤，感觉比较中上的一个树上问题，算是一个上位绿。

闲言少叙，梦熊继续。

## 思路

为了方便，我们在下文中将 $0$ 与 $1$ 对调的操作称为**反转**。

模拟一下样例，可以发现，我们可以转化题意为：

一开始有一个权值全为 $0$ 的树，每一次操作将一个树上连续的区间反转，问多少次操作后可以得到目标权值。

考虑两种情况。

- 情况一：$a$ 和 $b$ 需要反转，而 $c$ 在他们的路径上且不需反转，则直接反转 $a$ 与 $b$ 的代价和整条路经反转后单独反转 $c$ 的代价相同，均为 $2$。
- 情况二：$a,b,c$ 需要反转，而 $d$ 在他们的路径中间，则全部反转后单独反转 $d$ 要比直接反转 $a,b,c$ 更优。

以上情况保证 $a,b,c,d$ 互不相交。

根据以上两种情况，我们可以得到结论：

在以上讨论中，$a,b,c,d$ 均为一个**连通块**，但操作一个连通块的代价为 $1$，而又不需要单独讨论每一个连通块的内部，所以我们想到：

缩点！

将每个连通块想象成一个点，最后得到一棵相邻点不同的树，于是我们在这一棵树上展开讨论。

因为我们发现，树上一定存在大量的情况二，故可以想到，树上直径离每个点距离最近，故我们可以在树上直径上找一个点，然后以这个点为根，用来更新其他的点。明显的，这个点就是直径中点。

注意有一些特殊的叶子节点或直径上的点记得分别讨论。

---

## 作者：_wsq_ (赞：2)

首先，一次操作显然是反转树上的一部分联通的寄存器。

注意到子任务 3 是“不存在一对相邻的寄存器希望储存的信息相同”。由于我们可以对一部分联通的寄存器进行整体操作，所以我们可以将颜色相同的一个联通块缩成一个点。这样，我们就只需要解决子任务 3 就可以了。

这时，最外层的白色节点可以先去掉，因为显然操作它们没有意义。

我们抽象一下，就会是下面这个图（虽然我这个图未免有点太过于抽象了）。
![](https://cdn.luogu.com.cn/upload/image_hosting/3ogv1evp.png)
显然，操作次数最少的方案是先将 1 到 5 整体染成黑色，再将 1 到 4 整体染成白色，以此类推，最后将 1 染成黑色。所以，对于新的树，当我们定根了以后，设根节点深度为 $1$，那么答案就是最大深度。而这个答案显然是直径的一半（向上取整），因为如果根不在直径上，则直径两个端点的距深度一定有一个会超过直径的一半，而如果根在直径上，显然最优的方案就是将根放在中间，使得深度平均分配。

代码（我赛时根节点深度为 $0$，所以最后答案加了 $1$）：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 1000005
struct edge{
    int to,next;
}e[maxn<<1],e2[maxn<<1];
int n,a[maxn],u[maxn],v[maxn],h[maxn],tot,id[maxn]={0,1},num=1,col[maxn],deg[maxn],h2[maxn],tot2,dis[maxn],maxd,idm;
void addedge(int x,int y){
    e[++tot].to=y;
    e[tot].next=h[x];
    h[x]=tot;
    return;
}
void addedge2(int x,int y){
    e2[++tot2].to=y;
    e2[tot2].next=h2[x];
    h2[x]=tot2;
    return;
}
void dfs(int x,int fa){
    for(int i=h[x];i;i=e[i].next){
        if(e[i].to==fa){
            continue;
        }
        if(a[x]==a[e[i].to]){
            id[e[i].to]=id[x];
        }
        else{
            id[e[i].to]=++num;
            col[num]=a[e[i].to];
        }
        dfs(e[i].to,x);
    }
    return;
}
void dfs2(int x,int fa){
    if(dis[x]>maxd){
        maxd=dis[x];
        idm=x;
    }
    for(int i=h2[x];i;i=e2[i].next){
        if(e2[i].to==fa){
            continue;
        }
        dis[e2[i].to]=dis[x]+1;
        dfs2(e2[i].to,x);
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        cin>>u[i]>>v[i];
        addedge(u[i],v[i]);
        addedge(v[i],u[i]);
    }
    col[1]=a[1];
    dfs(1,0);
    for(int i=1;i<n;i++){
        if(id[u[i]]!=id[v[i]]){
            deg[id[u[i]]]++;
            deg[id[v[i]]]++;
        }
    }
    for(int i=1;i<n;i++){
        if(id[u[i]]!=id[v[i]]&&(deg[id[u[i]]]>1||col[id[u[i]]])&&(deg[id[v[i]]]>1||col[id[v[i]]])){
            addedge2(id[u[i]],id[v[i]]);
            addedge2(id[v[i]],id[u[i]]);
        }
    }
    if(num==1&&!col[1]){
        cout<<0;
        return 0;
    }
    for(int i=1;i<=num;i++){
        if(deg[i]>1||col[i]){
            dfs2(i,0);
            break;
        }
    }
    dis[idm]=0;
    maxd=0;
    dfs2(idm,0);
    cout<<((maxd+3)>>1);
    return 0;
}
```

---

## 作者：RAND_MAX (赞：1)

下文中我们将 $a_i=0$ 的点称为白色点，否则称为黑色点。

我们先把相邻的同色点缩点，因为这些点显然可以一起操作。这样每个点只会与其异色的点相邻。

考虑将一条链变为目标状态的操作次数，由于相邻点异色，若链结尾为黑点，则需链长减一次操作；否则我们不考虑最末尾的白点，需链长减二次。扩展到树上同理，因为有公共部分的链操作策略相同，公共部分可以一起处理。那么我们只需找到一个点，使树以它为根的情况下最大深度最小，容易想到取直径中点，dfs 计算即可。


```cpp
#include<bits/stdc++.h>
#define int long long
#define gc getchar
//char buf[1<<20],*p1,*p2;
//#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
#define R read()
using namespace std;
int read()
{
	int x=0,f=1;
	char c=gc();
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=gc();}
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+c-48,c=gc();
	return x*f;
}
void write(int x,char xx)
{
	static int st[35],top=0;
	if(x<0){x=-x;putchar('-');}
	do
	{
		st[top++]=x%10,x/=10;
	}while(x);
	while(top) putchar(st[--top]+48);
	putchar(xx);
}
#define N 1000010
int n,a[N],ans,sum,col[N],tot,u,c[N],dep[N];
vector<int>g[N],v[N];
queue<int>q;
void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;
	for(int i:v[x])
	{
		if(i==fa) continue;
		dfs(i,x);
	}
}
signed main()
{
	n=R,q.push(1);
	for(int i=1;i<=n;i++) a[i]=R,ans+=a[i];
	for(int i=1,x,y;i<n;i++) x=R,y=R,g[x].push_back(y),g[y].push_back(x);
	col[1]=++tot,c[col[1]]=a[1];
	while(!q.empty())
	{
		u=q.front(),q.pop();
		for(int i:g[u])
		{
			if(col[i]) continue;
			if(a[i]^a[u]) col[i]=++tot,v[col[i]].push_back(col[u]),v[col[u]].push_back(col[i]),c[col[i]]=a[i];
			else col[i]=col[u];
			q.push(i);
		}
	}
//	cout<<tot<<" ";
//	for(int i=1;i<=tot;i++) if(c[i]) id=i;
	int id=0,di=0;
	dep[0]=-1,dfs(1,0);
	for(int i=1;i<=tot;i++) if(dep[i]>dep[id]) id=i;
	dep[0]=0,dfs(id,0);
	for(int i=1;i<=tot;i++) if(dep[i]>dep[di]) di=i;
	sum=dep[di]+(c[id]&&c[di])-(!c[di]&&!c[id]);
	write(sum>>1,'\n');
 	return 0;
}
```

---

## 作者：lzx111218 (赞：0)

# P11562 【MX-X7-T3】[LSOT-3] 寄存器
[题目传送门](https://www.luogu.com.cn/problem/P11562)
## 思路
可爱图论题。

这题其实挺有意思的，典型的树形结构问题，目标就是通过最少的通电次数将树中所有寄存器的值调整到目标值。每个寄存器最初的值都是 $0$，而通电操作会反转当前节点和与其相连的节点的值。

首先，考虑到树的结构，两个节点之间有且仅有一条路径，这就为我们提供了一个明确的遍历顺序。然后我们就可以使用 **DFS** 来逐步处理每个节点。当我们遍历到某个节点时，如果它的值和目标值不一致，就需要进行通电操作。而每次通电都会改变当前节点的值，还会影响与其相连的子节点，确保每次通电都能最大程度地减少后续的操作。  
~~而不会 TLE。~~

对于每一个节点，检查它当前的值和目标值是否一致。如果不一致，就进行一次通电，接着递归处理它的子节点。通过这种方式，我们可以在遍历过程中不断调整树上各个节点的值，直到最终满足所有节点的目标值即可。  
~~我比赛就 WA 在这了。~~

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll m;
ll a[1000005] = {123456};
vector<ll> g[1000005];

ll M, D;

int main() {
    scanf("%lld", &m);

    bool z = true;
    for (ll i = 1; i <= m; i++) {
        scanf("%lld", &a[i]);
        if (a[i] == 1) z = false;
    }

    if (z) {
        printf("0\n");
        return 0;
    }

    for (ll i = 1; i < m; i++) {
        ll x, y;
        scanf("%lld%lld", &x, &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }

    stack<tuple<ll, ll, ll>> s;
    s.push({1, 0, 0});

    while (!s.empty()) {
        auto [c, p, d] = s.top();
        s.pop();

        if (a[c] != a[p]) d++;
        if (a[c] == 1 && d > D) {
            D = d;
            M = c;
        }

        for (ll n : g[c]) {
            if (n != p) {
                s.push({n, c, d});
            }
        }
    }

    D = 0;
    s.push({M, 0, 0});

    while (!s.empty()) {
        auto [c, p, d] = s.top();
        s.pop();

        if (a[c] != a[p]) d++;
        if (a[c] == 1 && d > D) {
            D = d;
            M = c;
        }

        for (ll n : g[c]) {
            if (n != p) {
                s.push({n, c, d});
            }
        }
    }

    printf("%lld\n", (D + 1) / 2);
    return 0;
}
```

---

