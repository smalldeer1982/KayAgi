# [ABC284C] Count Connected Components

## 题目描述

给定一个有 $N$ 个顶点、$M$ 条边的简单无向图，顶点编号为 $1$ 到 $N$，边编号为 $1$ 到 $M$。第 $i$ 条边连接顶点 $u_i$ 和顶点 $v_i$。  
请你求出该图中连通分量的个数。

## 说明/提示

### 注释

**简单无向图** 是指没有自环和重边，且边没有方向的图。  
图是**简单**的，意味着图中不包含自环和多重边。

一个图的**子图**是指从原图中选择一些顶点和一些边所构成的图。  
图是**连通**的，意味着图中任意两个顶点都可以通过边相互到达。  
**连通分量**是指连通的子图，且不存在包含它的更大的连通子图。

### 数据范围

- $1 \leq N \leq 100$
- $0 \leq M \leq \frac{N(N-1)}{2}$
- $1 \leq u_i, v_i \leq N$
- 输入保证图为简单图
- 所有输入均为整数

### 样例解释 1

给定的图包含如下 $2$ 个连通分量：  
- 由顶点 $1, 2, 3$ 和边 $1, 2$ 构成的子图  
- 由顶点 $4, 5$ 和边 $3$ 构成的子图  
![](https://img.atcoder.jp/ghi/abc284c_095531536446f41896b10cf15a3e4d158ce081ef1b6fe656788371718b39b3fb.jpg)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 3
1 2
1 3
4 5```

### 输出

```
2```

## 样例 #2

### 输入

```
5 0```

### 输出

```
5```

## 样例 #3

### 输入

```
4 6
1 2
1 3
1 4
2 3
2 4
3 4```

### 输出

```
1```

# 题解

## 作者：NightStriker (赞：6)

简单的爆搜问题。很适合 C 题的难度。

看很多神犇用的是并查集......其实 dfs 可以直接过，无需剪枝。

---

题意：

> 给你一个简单的无向图，有 $n$ 个顶点和  $m$ 条边。边 $i$ 连接顶点 $u_i$ 和顶点 $v_i$。
>
> 找出该图中的联通块个数。

对于这道题，我们可以开个 `vis` 数组来记录访问的节点，然后枚举节点 $i$ 个节点 $j$ 是否联通就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int v[1001][1001];//记录连通路线，默认为 0——即不存在。
bool vis[1001];//访问标记，避免重复计数
int n,m,a,b,ans;
void dfs(int k) {
	vis[k] = 1;//该节点访问过了 
	for(int i = 1; i<=n; i++) {
		if(!vis[i]&&v[k][i]) dfs(i);//如果没访问过并且节点存在就再搜一遍 
	}
}
int main() {
	cin>>n>>m;
	for(int i = 1;i<=m;i++){
		cin>>a>>b;
		v[a][b] = 1;
		v[b][a] = 1;
	}
	for(int i = 1; i<=n; i++) {
		if(!vis[i]) {//如果之前没有被访问过
			dfs(i);
			ans++;
		}
	}
	cout<<ans<<endl;
	return 0;
}

```



---

## 作者：LegendaryGrandmaster (赞：4)

读完题我们可以发现，它让我们求一个简单无向图中有多少个**互不相干**的部分。

如果我们想知道这个，我们就需要知道它们的根节点，而互不相同的根节点的数量即为我们的答案。

求根节点，我们的第一反应应该就是**并查集**。

先依次求出它们的根节点，然后双重循环把他们统一到一个点上，用 map 记录出现的根节点，最终输出即可。

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1001][1001],f[1001],n;
int find(int x)//并查集
{
	if(f[x]==x)return x;
	f[x]=find(f[x]);
	return f[x];
}
map<int,bool>mp;
signed main()
{
	int m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)f[i]=i;
	while(m--){
		int u,v;
		cin>>u>>v;
		a[u][v]=a[v][u]=1;
		int r1=find(u),r2=find(v);
		if(r1!=r2)f[r1]=r2;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(i!=j&&a[i][j]){
				int r1=find(i),r2=find(j);
				if(r1!=r2)f[r1]=r2;
			}
		}
    //将根节点统一
	//for(int i=1;i<=n;i++)cout<<f[i]<<' ';
	for(int i=1;i<=n;i++)mp[f[i]]=1;
	cout<<mp.size();		
}
```

---

## 作者：Hughpig (赞：2)

## 题意

求一张无向图中连通块个数。

## 思路

首先可以想到按照题意模拟，对于每个点 dfs 一下，最后统计个数。由于最多只有 $100$ 个点，这个做法是可以通过的。



但是我们有更好的做法：并查集。

[并查集模板](/problem/P3367)，如果不会建议先去学习了解一下，并查集相关的基础内容此处不在赘述。

此题也可以看成是有 $n$ 个元素，$m$ 次合并操作，求最后的集合数量。可以先令所有元素的父节点都为自己，每次合并就将一个集合的根节点的父节点设为另一个集合的根节点即可，最后一次循环求出**父节点是自己的元素数量**即可（这些元素就是没有被合并的，代表一个连通块）。

## 代码

```cpp
//思路1
#include<bits/stdc++.h>
using namespace std;
vector<int> edge[114];//vector 存图
int n,m,u,v,cnt;
bool vis[114];//记录是否被访问过

void dfs(int qwq)//dfs
{
	vis[qwq]=1;
	for(int i=0;i<edge[qwq].size();i++)
	{
		if(!vis[edge[qwq][i]]) dfs(edge[qwq][i]);
	}
}

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    while(m--)//连边
    {
    	cin>>u>>v;
    	edge[u].push_back(v);
    	edge[v].push_back(u);
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i]) dfs(i),cnt++;//如果未访问过，访问并增加答案
	}
	cout<<cnt<<'\n';
	return 0;
}
```

```cpp
//思路2
#include<bits/stdc++.h>
using namespace std;

int n,m,f[1145],ans;

int fd(int x)
{
	if(x==f[x]) return x;
	return f[x]=fd(f[x]);
}

void meg(int a,int b)
{
	f[fd(a)]=fd(b);
}

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)f[i]=i;
    cin>>m;
    while(m--)
    {
    	int a,b;
    	cin>>a>>b;
    	meg(a,b);
	}
	for(int i=1;i<=n;i++)
	{
		if(f[i]==i) ans++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Jasper08 (赞：2)

看到要求连通块的数量，考虑用并查集。初始时 $p_i=i$，即每个节点的父亲都是自己。连接一条边 $(u,v)$ 相当于合并点 $u$ 和点 $v$ 所在的集合，令 $p_{find(u)}=find(v)$ 即可。

最后，我们统计出有多少个节点的父亲是自己，即 $p_i=i$ 的节点数量 $cnt$。$cnt$ 即为连通块个数。

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int N = 110;

int n, m, p[N];

int find(int x) {
    if (p[x] != x) return find(p[x]);
    return p[x];
}

void merge(int x, int y) {
    p[find(x)] = find(y);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) p[i] = i;

    while (m -- ) {
        int u, v; scanf("%d%d", &u, &v);
        merge(u, v);
    }

    int cnt = n;
    for (int i = 1; i <= n; ++i) {
        if (p[i] != i)
            cnt --;
    }
    printf("%d\n", cnt);
    system("pause");
    return 0;
}
```

---

## 作者：zzx0102 (赞：1)

既然要求联通块，本蒟蒻最先想到的是并查集。

我们要求的是有几个联通块。

在并查集中，对于一个联通块，一定有且仅有其中一个 $u$，满足 $rt_u=u$。

所以在连完之后，就查找存在多少个 $i$，满足 $rt_i=i$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 110;
int n, m, rt[N]; int find(int x) {return rt[x] == x ? x : rt[x] = find(rt[x]);}
int main() {
	cin >> n >> m; for(int i = 1; i <= n; i++) rt[i] = i;
	while(m--) {
		int a, b;
		scanf("%d%d", &a, &b);
		rt[find(b)] = find(a);
	}
	int ans = 0; for(int i = 1; i <= n; i++) if(find(i) == i) ans++; cout << ans;
	return 0;
}
```

遇见题解勿抄袭，棕名封号两行泪。

---

## 作者：expnoi (赞：1)

这题是经典的求连通块数量问题。

可以用路径压缩并查集维护每个连通块。

在我们使用并查集得到每个连通块集合的根后，显然有多少个根就有多少个连通块。

我们可以用一个桶记录不同的根的数量，从而求出连通块数量。

这是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int s=0,w=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			w=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		s=(s<<3)+(s<<1)+(c^48);
		c=getchar();
	}
	return s*w;
}
inline void print(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>=10)
		print(x/10);
	putchar(x%10+'0');
	return;
}
int n,x,y,fa[100100],cnt[100100];
inline int get(int x){
	return fa[x]==x?x:fa[x]=get(fa[x]);
}
int main()
{
	n=read();
	int m=read();
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		x=read(),y=read();
		fa[get(x)]=get(y);
	}
	int c=0;
	for(int i=1;i<=n;i++)
	{
		if(cnt[get(i)])continue;
		cnt[get(i)]=1;
		++c;
	}
	print(c);
}
```

---

## 作者：Hell0_W0rld (赞：1)

## C
+ [link](https://atcoder.jp/contests/abc284/tasks/abc284_c)
+ 难度：入门。
+ *193。

题目求无向图连通块数量。用并查集维护即可，顺便统计连通块个数。每次合并只要是不同集答案 $-1$。初始为 $n$。复杂度 $O(N)$。
```cpp
ll id[109];
ll cnt;
ll rt(ll x){
	if(id[x]==x)return x;
	return id[x]=rt(id[x]);
}
void mg(ll a,ll b){
	ll ra=rt(a),rb=rt(b);
	if(ra==rb)return;
	id[ra]=rb,cnt--;
}
int main(){
	ll n,m,u,v;cin>>n>>m;
	rep(i,1,n)id[i]=i;cnt=n;
	while(m--){
		cin>>u>>v;mg(u,v);
	}
	cout<<cnt<<endl; 
	return 0;
}
```

---

## 作者：code_hyx (赞：0)

这场 abc 算近几场中最水的一场了，可惜我那天上课没打，错失了一次上大分的机会。  
这题要求图的联通块的个数，很明显可以用并查集做，从第一条边开始，逐个合并就行了，最后看有几个节点没有父节点（也就是根），就是联通块的数量了。  
关于并查集的详解，可以参考[这篇文章](https://blog.csdn.net/LWR_Shadow/article/details/124873281)。  
代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,k,tot=0;
int fa[100005];
int r[100005];
void makeset(int x)
{
    for(int i=1;i<=x;i++)
	{
        fa[i]=i;
        r[i]=1; 
    }
} 
int _find(int x)
{
    if(fa[x]==x)return x;
    else return fa[x]=_find(fa[x]);
}   
void _union(int x,int y)
{
    fa[y]=x;
    r[x]+=r[y];  
}  
int main()
{
	int maxx=0;
    cin>>n>>k; 
    makeset(n);
    while(k--)
	{
        int a,b;
        cin>>a>>b;
        int x=_find(a),y=_find(b);
        if(x!=y)_union(x,y);
    }    
    for(int i=1;i<=n;i++)
	{
		if(fa[i]==i)tot++;
	}
	cout<<tot;
    return 0;
}
```


---

## 作者：紊莫 (赞：0)

## Part 0 题意简述  

给一个图，求其中连通块个数。

## Part 1 思路  

非常裸的连通块划分，用一个数组记录每个点有没有访问过，如果没有，则从其开始，把与之相连的点都标记一下，同时答案加一即可。  

## Part 2 参考代码  

仅供参考。  

```cpp
//Author: Velvet on Luogu(uid=443675)
#include <bits/stdc++.h>
#define mkpr make_pair
#define fi first
#define se second
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define dF(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
using namespace __gnu_cxx;
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if (x < 0) x = ~x + 1, putchar('-');if (x > 9) write(x / 10);putchar(x % 10 + '0');}
inline void writeln(int x){write(x);putchar('\n');}
inline void writesp(int x){write(x);putchar(' ');}
inline int lowbit(int x) {return x&(-x);}
typedef pair<int,int> Pair;
const int N=105;
int n,m,vis[N],ans;
vector<int> p[N];
void dfs(int now){
	vis[now]=1;
	for(auto i:p[now])
		if(!vis[i]) dfs(i);
}
int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n>>m;
	F(i,1,m){
		int u,v;cin>>u>>v;
		p[u].push_back(v);p[v].push_back(u);
	}
	F(i,1,n)if(!vis[i])ans++,dfs(i);
	cout<<ans;
    return 0;
}
```


---

## 作者：Lyu_echo (赞：0)

## 题意

给定 $n$ 个节点 $m$ 条边的无向图。求连通块个数。

## 解题思路

图论基础模板题。

使用 DFS 解题。

枚举每一个节点：

- 若该节点未被访问，即为未在已知的连通块中。累加连通块个数，并从该节点开始访问所有可以被访问且未被事先访问的节点。

- 若该节点已被访问，即为已在已知的连通块中。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int>G[110]; //使用 邻接表 存图
bool vis[110]; //标记节点是否被访问
void dfs(int u){
    vis[u]=true;
    for (auto &v : G[u]) if(!vis [v]) dfs (v); //遍历所有可以访问且未被访问的节点
    return ;
}
int main () {
    int n, m, ans=0;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v); //邻接表建图
        G[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis [i]){
            dfs (i);
            ans++;
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：Escapism (赞：0)

新年第一场 ``ABC``！~~但是我赛场上没 ``AC`` 这题......~~

[``ATC`` 上的原题](https://atcoder.jp/contests/abc284/tasks/abc284_c)

# 题意

给定一张 $n$ 个顶点 $m$ 条边的无向图，求其中有几张连通子图。

# 思路

并查集。如果需要的话可以看[ ``wiki`` 上的介绍](https://oi-wiki.org/ds/dsu/) 和 [模板题](https://www.luogu.com.cn/problem/P3367)。

在这里也简短介绍一下。假如你遇到了这样的一道题：

- 有 $n$ 个人和 $m$ 条关系，存在关系的人属于同一个团队。问有几个团队。

很容易想到用数组维护每个团队里的人，但是会遇到这种情况：

- 已有的信息表明 $1,2,3$ 号属于一个团队，$4,5$ 号属于一个团队，于是分别放入一个数组中

- 然而又有一条信息 $4,5$ 属于一个团队，然后就要被迫合并 $1,2,3$ 的数组和 $4,5$ 的数组。

这样高的复杂度显然是不能接受的，因此维护团队时要用一种更高效的结构——树结构。

## 并查集

并查集就是一种运用了树结构的数据结构，呈现为一个森林。

森林中的每一个树结构都表示一个团队，这棵树的根节点就是这个团队的队长。

初始时，由于没有任何关系，我们可以将每一个人都理解成一个团队。

**合并**

当要合并两个团队时，我们就找出两个团队的队长，然后将其中一位队长设为另外一位的“上级”。

那么为什么要找出队长再合并呢？

如果找出队长来合并，就仍然可以通过上级的关系找出队长。反之，就会出现一个人有两个上级的神奇情况。

因为每个人初始都是队长，因此上级关系是从头到尾都存在的。

**查询**

由于特殊的合并方法，属于同一个团队的人必然拥有同一个队长，而我们也可以通过上级关系找出队长。

所以如果需要查询两个人是不是同一个团队的，只需要判断他们有没有同一个队长就行。

----

回归本题。

题目是以图论的方式来呈现的。但是所谓的“边”其实就是一条关系，表明边的两个顶点属于同一个团队。

然后题目要求我们找有几张连通子图，其实就是找有几个团队。由于每个团队的队长是唯一的，所以只需要找有几个不同的队长就行。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
 
int n,m,z,x,y,fa[10005]; //fa 存当前的队长
map<int,bool> MP;
struct Edge{ 
    int u,v;
} p[10005];//存边
int find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}
int main(){
    cin>>n>>m;
    for(int i = 1;i <= n;i++) fa[i] = i;//初始队长
    for (int i = 1;i <= m;i++){ 
        cin>>p[i].v>>p[i].u;
        int a = find(p[i].v),b = find(p[i].u);//存队长
        fa[a] = b; //合并团队
    }
    int cnt = 0;
    for (int i = 1;i <= n;i++){ //找有几个不同的队长
        cnt += !(MP[find(i)]);
        MP[find(i)] = true;
    }
    cout<<cnt;
    return 0;
}
```
**补充**

细心的读者可能会发现，查询时 $fa$ 数组**未必**存的是队长，有时候仅仅是一个普通的并非队长的上级。

可以模拟一遍样例 $1$，就会发现最终 $fa_1$ 存储的是 $2$，而并非队长 $3$。

这是因为输入时我们仅仅改变了队长 $i$ 的 $fa_i$，而他的下级并没有被改变，就会出现一些滞后。

但是这其实并不影响查询。因为合并两个团队以后，成为了下级的队长的 $fa$ 就不会再改变了，因为不会再用于合并。

并非队长的 $fa$ 就只会在找队长时被访问，而找到的上级又会访问上级的上级，最终找到队长。

查询时不需要更新所有数据，这也是并查集比普通数组高效的原因之一。

---

讲的可能不太好，可以去看模板题的题解。

---

