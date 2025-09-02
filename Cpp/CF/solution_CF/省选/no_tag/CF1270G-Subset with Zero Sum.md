# Subset with Zero Sum

## 题目描述

You are given $ n $ integers $ a_1, a_2, \dots, a_n $ , such that for each $ 1\le i \le n $ holds $ i-n\le a_i\le i-1 $ .

Find some nonempty subset of these integers, whose sum is equal to $ 0 $ . It can be shown that such a subset exists under given constraints. If there are several possible subsets with zero-sum, you can find any of them.

## 说明/提示

In the first example, we get sum is $ a_1 = 0 $ .

In the second example, we get sum is $ a_1 + a_4 + a_3 + a_2 = 0 $ .

## 样例 #1

### 输入

```
2
5
0 1 2 3 4
4
-3 1 1 1
```

### 输出

```
1
1 
4
1 4 3 2 
```

# 题解

## 作者：Early (赞：52)

来证一下 @xht37 dalao 的建图和判断方式。

图上的每个环都对应一个合法的点集 $ S $ 。

为什么呢？

记 $ i $ 向 $ to_i $ 连了边，由建图的方式得 $ to_i=i-a_i $ 。

一旦 $ S $ 形成了环，则 $ \sum_{i\in S}i=\sum_{i\in S}to_i $ 。

即 $ \sum_{i\in S}i=\sum_{i\in S}(i-a_i) $ 。

将等式右边展开得： $ \sum_{i\in S}i=\sum_{i\in S}i-\sum_{i\in S}a_i $ 。

显而易见， $ \sum_{i\in S}a_i=0 $ ，符合题目要求。

---

## 作者：xht (赞：25)

由于 $i - n \le a_i \le i - 1$，所以 $1 \le i - a_i \le n$。

建立一张 $n$ 个点的有向图，对于每个点 $i$，连边 $i \to i - a_i$。

这张图中每个点的出度都为 $1$，因此这张图是一个基环内向森林。

可以发现对于任意一个环，环上的点对应的下标就是我们要找的答案。

```cpp
const int N = 1e6 + 7;
int n, x, t[N], v[N];

inline void solve() {
	rd(n);
	for (int i = 1; i <= n; i++) rd(x), t[i] = i - x, v[i] = 0;
	x = 1;
	while (!v[x]) v[x] = 1, x = t[x];
	vi ans;
	ans.pb(x), x = t[x];
	while (x != ans[0]) ans.pb(x), x = t[x];
	print(ans.size());
	while (ans.size()) print(ans.back(), " \n"[ans.back()==ans[0]]), ans.pop_back();
}

int main() {
	int T;
	rd(T);
	while (T--) solve();
	return 0;
}
```

---

## 作者：_lyx111 (赞：4)

# CF1270G Subset with Zero Sum

[题目传送门](https://codeforces.com/problemset/problem/1270/G)

~~据说这道题场上 $\texttt{tourist}$ 不会，$\texttt{Benq}$ 也不会，太恐怖了/kk~~

## 分析

转化到图。第 $i$ 个点向第 $i-a_i$ 个点连一条有向边，建出有向图，那么只要在这张图上找到一个环就是原问题的解。

下面做几点说明：

1. 因为 $i-n\le a_i\le i-1$，所以 $1\le i-a_i\le n$，所以第 $i-a_i$ 个点一定存在；

2. 倘若构成环，则对环上的任意一点 $i$ 都有：$i-a_i-a_{i-a_i}-a_{i-a_i-a_{i-a_i}}-\cdots=i$，即 $a_i+a_{i-a_i}+a_{i-a_i-a_{i-a_i}}+\cdots=0$，就是一组解；

### [代码](https://codeforces.com/problemset/submission/1270/192734374)

如果写的有不清楚或不对的地方可以私信我，我会尽量及时修正。

---

## 作者：木xx木大 (赞：4)

[CF1270G Subset with Zero Sum](https://www.luogu.com.cn/problem/CF1270G) 

先化简不等式： $i-n\le a_i≤i-1 \rightarrow  1 \le i-a_i\le n$

记 $to_i=i-a_i$，连边 $i$ 到 $to_i$ 。则这个图中任意一个环都是一个合法的子集。

因为对于环 S，环上点和可以表示为 $\sum_{i\in S}i=\sum_{i\in S} to_i =\sum_{i\in S} i-a_i \rightarrow \sum a_i=0$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int t,n,a[N],to[N];
bool vis[N];
vector<int> ans;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		ans.clear();
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			to[i]=i-a[i];
			vis[i]=0;
		}
		int x=1;
		while(!vis[x])
		{
			vis[x]=1;
			x=to[x];
		}
		ans.push_back(x);
		x=to[x];
		while(x!=ans[0])
		{
			ans.push_back(x);
			x=to[x];
		}
		printf("%d\n",ans.size());
		for(int j=0;j<ans.size();j++)
			printf("%d ",ans[j]);
		printf("\n");	
	}
	return 0;
}
```

---

## 作者：dbxxx (赞：3)

[欢迎您到我的博客查看本文，谢谢！](https://www.cnblogs.com/crab-in-the-northeast/p/cf1270g.html)

普通序列抽数，要求和为 $0$，则只能暴力搜索。

那突破口肯定是 $i - n \le a_i \le i - 1$。变形一下，得到 $1 \le i - a_i \le n$。

尝试对每个 $[1, n]$ 中的 $i$，都从 $i$ 到 $i - a_i$ 连一条有向边。这样会得到一个顶点编号都在 $[1, n]$ 内的有向图。

更具体地，由于每个点出度为 $1$，形成的图一定是内向基环森林。

对于某个环上的所有点 $i$，考虑 $\sum i$，它是环上所有点的编号和。

那对于这个环上所有点 $i$，考虑 $\sum i - a_i$，也就是统计这个环上每个点所指向的点的编号和，发现仍然是这个环上所有点的编号和。

因此 $\sum i = \sum i - a_i$，有 $\sum a_i = 0$，这就找到一组合法解了。

注意答案让输出的是所选数字的下标，而不是值。因此我们只需要在内向基环森林中，随便找一个环，输出它的点编号即可。

```cpp
/*
 * @Author: crab-in-the-northeast 
 * @Date: 2023-06-15 09:12:33 
 * @Last Modified by: crab-in-the-northeast
 * @Last Modified time: 2023-06-15 09:29:03
 */
#include <bits/stdc++.h>
inline int read() {
	int x = 0;
	bool f = true;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-')
			f = false;
	for (; isdigit(ch); ch = getchar())
		x = (x << 1) + (x << 3) + ch - '0';
	return f ? x : (~(x - 1));
}

const int N = (int)1e6 + 5;
int dep[N], to[N];

inline void solve() {
	int n = read();
	dep[1] = 1;
	for (int u = 2; u <= n; ++u)
		dep[u] = 0;
	for (int i = 1; i <= n; ++i)
		to[i] = i - read();
	std :: vector <int> vec = {0};
	for (int u = 1; ; u = to[u]) {
		vec.push_back(u);
		int v = to[u];
		if (dep[v]) {
			printf("%d\n", dep[u] - dep[v] + 1);
			for (int i = dep[v]; i <= dep[u]; ++i)
				printf("%d ", vec[i]);
			puts("");
			return ;
		}
		dep[v] = dep[u] + 1;
	}
}

int main() {
	int T = read();
	while (T--)
		solve();
	return 0;
}
```

---

## 作者：Constant (赞：3)

## 题意:

给你 $n$ 个整数，第 $i$ 个整数满足 $i-n\le a_i\le i-1$ ，从中选出一些

数，不能不选，使得选出的数字和为 $0$ 。

## Solution:

这是一道构造题，把题目给出的条件移项，得到 $1\le i-a_i\le n$ 这个条件，

于是在 $n$ 个点中，每个点都只会有一条出边，于是考虑 $i-a_i$ 与 $i$ 的关

系，可以发现，当$\sum{a_i}=0$ 时，有 $\sum{i}=\sum{i-a_i}$ 成立，于是构

造一个图解决问题，把 $i$ 向 $i-a_i$ 连一条边，最后图中的环显然使得上式成

立，环上的点即为满足要求的一个子集了。

```cpp
#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int f,num,S,T,n,a[N],first[N],v[N*2],nex[N*2],vis[N],s[N],top;
void Add(int s,int e)
{
	nex[++num]=first[s];
	first[s]=num;
	v[num]=e;
}
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
void dfs(int u)
{
	if(f) return;
	for(int i=first[u];i;i=nex[i])
	{
		if(vis[v[i]])
		{
			int pd=0;
			for(int j=1;j<=top;j++) 
			{
				if(s[j]==v[i]) 
				{
					pd=1;
					printf("%d\n",top-j+1);
				}
				if(pd)
				{
				    printf("%d ",s[j]);	
				}
			}	
			f=1;
			return;
		}
		vis[v[i]]=1;
		s[++top]=v[i];
		dfs(v[i]);
		top--;
		if(f) return;
	}
}
int main()
{
    T=read();
    while(T--)
    {
    //	memset(vis,0,sizeof(vis));
   // 	memset(first,0,sizeof(first));
    	num=0;
    	n=read();
    	f=0;
    	for(register int i=1;i<=n;i++)
    	{
    		vis[i]=0;
    		a[i]=read();
    		Add(i,i-a[i]);
    	//	Add(i-a[i],i);
		}
		for(int i=1;i<=n;i++)
		{
			if(!vis[i])
			{
				//cout<<i<<endl;
				vis[i]=1;
				top=0;
			//	f=0;
				s[++top]=i;
				dfs(i);
			}
		} 
		printf("\n");
	}
    return 0;
}
```





---

## 作者：UperFicial (赞：2)

牛逼题。

转化一下不等式可以得到 $1\le i-a_i\le n$，令 $t_i\leftarrow i-a_i$，我们将 $i\to t_i$ 连一条有向边，形成一棵内向基环树，且肯定存在一个环。

考虑环上的点集 $S$ 中每一个元素 $i\in S$，$t_i$ 肯定也在这个点集中，也就是说，$i$ 也可以被表示 $t_j\ (j\in S)$。

那么我们得到等式 $\sum_{i\in S}i=\sum_{i\in S}t_i$，$t_i$ 回代得到 $\sum_{i \in S}i=\sum_{i\in S}i-a_i$，则 $\sum_{i\in S}a_i=0$，由此，点集 $S$ 就是我们想要的答案，时空复杂度 $\Theta(n)$。

[代码](https://codeforces.com/contest/1270/submission/175207769)。

---

## 作者：_Yoimiya_ (赞：2)

[题目传送门。](https://www.luogu.com.cn/problem/CF1270G)

说句题外话，~~我把脑袋塞马桶里都想不出正解是建图~~     

前置知识：
1. 基环树：树加一条边使之成环。  

1. 基环内向树：一个有向图，它构成类似基环树的结构，有一个特点是每个点出度都为 1，并且环外的节点方向指向环内。  

1. 基环内向森林：多个基环内向树。

解题思路：
- 先推个条件，因为 $i - n \leq a_i$，所以 $i - a_i \leq n$。   

- 题目要求找到和为 0 的一个子集（即 $\sum a_i = 0$），那么这个子集满足： $\sum i = \sum i - a_i$。 

- 然后就是神仙建图。建一个有 $n$ 个节点的有向图，把点 $a_i$ 连向 $i - a_i$。可以发现这张图是一个基环内向森林（每个点出度都为 1 且可能有多个基环树）。   

- 建好图后，你会发现图构成环就代表着 $\sum i = \sum i - a_i$，那只用输出环上的点就行了（~~太神奇了~~）。

- 注意，这题卡了流输入输出，要用快读。

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N(1e6+1);
int p(1),t[N],v[N];
inline int read() {
	register int s(0),w(1);char ch(getchar());
	while(ch<'0'||ch>'9') {if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
	return s*w;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int e(read()); 
	while(e--){
		int n(read());
		for(register int i(1),x;i<=n;++i) x=read(),t[i]=i-x,v[i]=0;
		while(!v[p]) v[p]=1,p=t[p];
		vector<int> ans;
		ans.push_back(p),p=t[p];
		while(p!=ans[0]) ans.push_back(p),p=t[p];
		cout<<ans.size()<<'\n';
		for(register int i(0);i<ans.size();++i) cout<<ans[i]<<' ';
		if(e) cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Ephemeroptera (赞：2)

#### 题意：翻译里说得很清楚了。

卡了 $\texttt{tourist}$ 的神题 %%%

### Solution:  
首先如果没有那条奇怪的限制，这个问题将会是一个 $\texttt{NP}$ 问题，所以从这条奇怪的限制下手，考虑将所有与 $i$ 有关的放一边，得到 $1\le i - a_i \le n$ ，也就是说 $i - a_i$ 一定是这一串数里面某个数的下标，考虑当 $\sum a_i=0$ 时，那么 $\sum (i - a_i) = \sum i$ 那么也就说明当一个集合中仅存在下标为 $i$ 与 $i - a_i$ 时可以构造出这样一个集合，那么每一个 $i$ 对 $i - a_i$ 连边，必定构成基环树森林，用 $dfs$ 任意取一个环即可。

**Summary**: 

1.  对于不等式条件的处理，将有用的信息放在一边。
2.  对于仅存在两类的集合向图论中的环的转化。  

贴一个用栈找环的代码。qwq  
```cpp
#include <bits/stdc++.h>


using namespace std;
const int N = 1e6 + 10;
int vis[N],first[N],nex[N],v[N],num = 0;
int a[N];
int times;
int cnt = 0;
int ans[N],stu[N],tot;
bool sol = false;
int n,m;
inline void add(int x,int y) {
	v[++num] = y;
	nex[num] = first[x];
	first[x] = num;
}
inline void dfs(int u) {
	vis[u] = true;
	stu[++tot] = u;
	for(int i = first[u];i != -1;i = nex[i]) {
		if(!vis[v[i]]) {
			dfs(v[i]);
		} else {
			sol = true;
			while(v[i] != stu[tot]) {
				ans[++cnt] = stu[tot];
				tot--;
			}
			ans[++cnt] = stu[tot];
			return ;
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> times;
	while(times--) {
		cnt = 0;
		cin >> n;
		num = 0,sol = false;
		for(int i = 1;i <= n;i++) {
			cin >> a[i];
			first[i] = -1;
			vis[i] = 0;
		}
		for(int i = 1;i <= n;i++) {
			add(i,i - a[i]);
		}
		for(int i = 1;i <= n;i++) {
			tot = 0;
			if(!vis[i]) dfs(i);
			if(sol) break;
		}
		cout << cnt << '\n';
		for(int i = 1;i <= cnt;i++) {
			cout << ans[i] << ' ';
		}
		cout << '\n';
	}
	
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

观察：

- $a_i \in [i - n , i - 1]$

- $i - a_i \in [1 , n]$

将每个点 $i$ 向 $i - a_i$ 连边，由于 $n$ 个点连出 $n$ 条有向边，则可以发现该图是一个奇环树森林。

令边的权值为两个点的节点标号差，发现其等于 $a_i$。则环上所有点的 $a_i$ 之和等价于边权值之和。

由于一个点绕环走一遍又回到本身，我们可以看成环游一遍一个值是不会变的，自然边的权值和为 $0$，可推导出 $\sum a_i = 0$。

所以随便拿个环输出就可以了，时间复杂度线性。

```cpp
/*
[1-n,0],[2-n,1],......[0,n-1]
!!!
i - ai \in [1,n]
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e6 + 5;
int n,m,a[Len],to[Len];
inline int read() {
    char ch = getchar();
    int x = 0, f = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline void write(int x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
bool vis[Len];
int tim;vector<int> Print; 
void Rec(int x,int fd)
{
	if(fd == x) tim ++;
	if(tim == 2) return;
	Print.push_back(x);
	Rec(to[x] , fd);
}
void dfs(int x)
{
	vis[x] = 1;
	if(vis[to[x]]) 
	{
		Rec(to[x] , to[x]);
		return;
	}
	dfs(to[x]);
}
int main()
{
	int T;T = read();
	while(T --)
	{
		n = read();
		for(int i = 1 ; i <= n ; i ++) 
		{
			a[i] = read();
			to[i] = (i - a[i]);
		}
		tim = 0;vector<int> fk;swap(fk , Print);
		dfs(1);
		printf("%d\n",Print.size());
		for(int i = 0 ; i < Print.size() ; i ++) printf("%d ",Print[i]);puts("");
		for(int i = 1 ; i <= n ; i ++) vis[i] = a[i] = to[i] = 0;
	}
	return 0;
}
```

---

## 作者：Alkaid_Star (赞：1)

### 题目大意

> 给你 $n$ 个整数 $a_1,a_2 \dots a_n$，第 $i$ 个整数 $a_i$ 满足 $i-n \le a_i \le i-1$。
>
> 找到这些整数的一个非空子集，使得它们的和为 $0$。如果有多个子集满足条件，输出任意一个。
>
> $1 \le n \le 10^6$。

### 解题思路

首先我们发现这个题最特殊的地方就是 $i-n \le a_i \le i-1$ 这个条件，考虑从这里下手。

对这个式子变个形吧：$-n \le a_i-i \le 1$，也就是 $1 \le i-a_i \le n$。

还是不好看，题目的限制和 $a$ 有关，我们把 $a$ 拎出来。假设 $i-a_i=j$，那么 $a_i=i-j$ 且 $j \in [1,n]$。

题目说要让 $\sum a_i=0$，那么也就是 $\sum i-j=0$。我们发现 $i$ 和 $j$ 的范围都是 $[1,n]$，因而可以考虑两两进行抵消，这个式子的第二项去消下个式子的第一项，这样最后首尾相消，形成的就是一个环。

既然想到换了，可以进而考虑建图。我们考虑建立对每个 $i$ 建立一条 $i \to j$ 的有向边，表示编号 $i$ 的式子可以抵消一个 $i$ ，但又需要 $j$ 去抵消自己产生的影响。

每个点连一条边，那么在这样一张图中就会有 $n$ 个点和 $n$ 条边，一定会出现环。由上面的推断可知，这个环上的点的 $i$ 和 $j$ 互相消掉了，就是和为 $0$ 的点，直接拓扑排序找出环即可。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)){ if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)){ x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}
const int N=1000005;

struct Edge{
	int vet,nxt;
}e[N<<1];

int n,edge=0,head[N];
int a[N],deg[N];
bool vis[N];
vector <int> cir;
queue <int> Q;

void addedge(int x,int y){
	e[++edge].vet=y;
	e[edge].nxt=head[x];
	head[x]=edge;
}

void Topsort(){
	while (!Q.empty()) Q.pop();
	for (int i=1;i<=n;++i) vis[i]=false;
	for (int i=1;i<=n;++i)
		if (deg[i]==0) Q.push(i);
	while (!Q.empty()){
		int x=Q.front(); Q.pop();
		vis[x]=true;
		for (int i=head[x];i;i=e[i].nxt){
			int v=e[i].vet;
			if (--deg[v]==0) Q.push(v);
		}
	}
}

int main(){
	//freopen("CF1270G.in","r",stdin);
	//freopen("CF1270G.out","w",stdout);
	int T=read();
	while (T--){
		n=read(); edge=0;
		for (int i=1;i<=n;++i) head[i]=0,deg[i]=0;
		for (int i=1;i<=n;++i) a[i]=read();
		for (int i=1;i<=n;++i){
			int j=i-a[i];
			addedge(i,j);
			++deg[j];
		}
		Topsort(); cir.clear();
		for (int i=1;i<=n;++i)
			if (!vis[i]) cir.push_back(i);
        // 上面我加入了所有在环上的点（可能加入了多个环），
        // 这样写不会影响正确性，反正不管多少个 0 加起来总和都是 0 。
		printf("%d\n",(signed)(cir.size()));
		for (auto it : cir) printf("%d ",it);
		printf("\n");
	}
	return 0;
}
```



---

## 作者：Acc_Robin (赞：1)

# CF1270G Subset with Zero Sum 题解

链接：[洛谷](https://www.luogu.com.cn/problem/CF1270G) [CodeForces](http://codeforces.com/problemset/problem/1270/G)

[更高更妙的观看角度](https://accrobin.github.io/2021/10/29/solver/CF1270GSubsetwithZeroSum/)

## 题意

给定 $n$ 个数 $a_1,a_2,\cdots,a_n$ ，对 $\forall 1\le i\le n$ 满足 $i-n\le a_i\le i-1$，找出一个非空子集使得子集元素和为 $0$。

$1\le n\le 10^6$

## 题解

这道题唯一的切入点就是 $i-n\le a_i\le i-1$，观察到两边都有 $i$，不妨化简一下：
$$
i-n\le a_i\le i-1
$$

$$
-n\le a_i-i\le -1
$$

$$
1\le i-a_i\le n\tag{1}
$$

假设答案集合为 $S$，那么我们所要做的就是使
$$
\sum_{i\in S}ai=0
$$
为了强行利用上面得出的式 $(1)$，我们给两边取负并配凑一下，得到
$$
\sum_{i\in S}i-a_i=\sum_{i\in S}i\tag2
$$
现在推导遇到了障碍：如何合理地利用不等式？

不妨数图结合，对所有 $i$ 连边 $i\to i-a_i$，那么此时形成了一棵内向基环森林，一定存在至少一个环，我们所要做的就是找出其中的一个环即可。

为什么是环？环上每一条边的起点 / 终点都恰好被统计一次，也即我们得出的式 $(2)$。式 $(2)$ 中左边的部分就是终点，右边的部分就是起点。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
 const int N=1e6+9;
 int b[N],f[N],z[N];
 void work(){
  int n,i,x,c=1;
  for(cin>>n,i=1;i<=n;++i)cin>>x,f[i]=i-x,b[i]=0;
  for(x=1;!b[x];x=f[x])b[x]=1;
  for(*z=x,x=f[x];x!=*z;x=f[x])z[c++]=x;
  for(cout<<c<<'\n',i=0;i<c;++i)cout<<z[i]<<' ';
 }
}
int main(){
 ios::sync_with_stdio(0),cin.tie(0);
 int T;for(cin>>T;T--;cout<<'\n')Acc::work();
}
```



---

## 作者：RemiliaScar1et (赞：1)

# CF1270G Subset with Zero Sum

[$link$](https://www.luogu.com.cn/problem/CF1270G)

这题太神仙了。

首先我们要对限制条件 $i-n\le a_i\le i-1$ 变形，得到 $1\le i-a_i\le n$。

我们要让 $\sum_{i\in S} a_i=0$，就是让 $\sum_{i\in S}i-a_i=\sum_{i\in S}i$。

由于 $i-a_i\in[1,n]$，我们相当于要选出一堆 $i$，让它们变成 $i-a_i$ 之后和还是不变，有点原地转圈的感觉。

考虑让 $i$ 向 $i-a_i$ 连单向边，如果图中有一个环，我们选环上所有的点，那么它们不管怎么变换，求和的总是那几个数，这样的方案一定合法。

考虑到这是一个 $n$ 点 $n$ 边的图，一定存在环；而且题目只让求任意一个方案，所以我们直接搜环即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=2e6+10;

int arr[N];
int ver[N],ans[N],res=0;
int root;
bool vis[N];

void dfs(int x)//找环并返回环的根
{
	if(vis[x])
	{
		root=x;
		return ;
	}
	vis[x]=1;
	dfs(ver[x]);
}
void dfs2(int x)
{
	ans[++res]=x;
	if(ver[x]==root) return ;
	dfs2(ver[x]);
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		res=0;
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&arr[i]); vis[i]=0;
			ver[i]=i-arr[i];
		}
		dfs(1);
		dfs2(root);
		printf("%d\n",res);
		for(int i=1;i<=res;i++) printf("%d ",ans[i]);
		printf("\n");
	}
	return 0;
}
```

~~据说这题狙了 tourist%%%(害怕~~

---

