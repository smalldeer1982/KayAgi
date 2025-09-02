# [ABC328F] Good Set Query

## 题目描述

### 题目内容

给定 $Q$ 个三元组 $(a_1,b_1,d_1),(a_2,b_2,d_2),...,(a_Q,b_Q,d_Q)$ 。

集合 ${1,2,...,Q}$ 的一个子集 $S$ 被定义为**好的子集**，当且仅当存在一个长度为 $N$ 的序列 $(X_1,X_2,...,X_N)$ 满足以下条件：

> 对于所有 $i\in S$ ， $X_{a_i}-X_{b_i}=d_i$ 。

将 $S$ 初始化为空集，对于 $i=1,2,...,Q$ 依次进行以下操作：

> 如果 $S\cup \{i\}$ 是一个好的集合，那么将 $S$ 替换成 $S\cup \{i\}$ 。

以**升序**输出 $S$ 中的所有元素。

## 说明/提示

* 所有输入元素为整数。
* $1\le N,Q\le 2\times 10^5$
* $1\le a_i,b_i\le N$
* $-10^9\le d_i\le 10^9$

## 样例 #1

### 输入

```
3 5
1 2 2
3 2 -3
2 1 -1
3 3 0
1 3 5```

### 输出

```
1 2 4 5```

## 样例 #2

### 输入

```
200000 1
1 1 1```

### 输出

```
```

## 样例 #3

### 输入

```
5 20
4 2 125421359
2 5 -191096267
3 4 -42422908
3 5 -180492387
3 3 174861038
2 3 -82998451
3 4 -134761089
3 1 -57159320
5 2 191096267
2 4 -120557647
4 2 125421359
2 3 142216401
4 5 -96172984
3 5 -108097816
1 5 -50938496
1 2 140157771
5 4 65674908
4 3 35196193
4 4 0
3 4 188711840```

### 输出

```
1 2 3 6 8 9 11 14 15 16 17 19```

# 题解

## 作者：Genius_Star (赞：8)

### 题意：

初始有 $n$ 个未知数 $X_i$。

给定 $q$ 个三元组 $(a_i,b_i,d_i)$。

依次对第 $i = 1,2.\cdots,q$ 个三元组执行以下操作：

- 如果当前可以确认 $X_{a_i}$ 和 $X_{b_i}$ 的大小关系，那么判断 $X_{a_i}-X_{b_i}=d_i$ 是否满足；如果满足，则将 $i$ 加入集合 $S$ 中；否则不用管。

- 如果当前不可以确认 $X_{a_i}$ 和 $X_{b_i}$ 的大小关系，那么钦定 $X_{a_i}-X_{b_i}=d_i$ 满足，将 $i$ 加入集合 $S$ 中。

最后从小到大输出 $S$ 中的元素。

### 思路：

和 [[ABC087D] People on a Line](https://www.luogu.com.cn/problem/AT_arc090_b) 很像，几乎一模一样。

很明显，是一个带权并查集的板子。

先简要说一下带权并查集，不仅要记 $fa_i$ 表示 $i$ 点的祖先，还要记一个 $dis_i$ 表示距离祖先的距离。

可以在路径压缩的时候进行维护距离：

```cpp
ll Find(ll x){
    if(fa[x]!=x){
        ll t=fa[x];
        fa[x]=Find(fa[x]);
        dis[x]+=dis[t];
    }
    return fa[x];
}
```

那么对于每次的关系 $(a_i,b_i,d_i)$，如果 $a_i,b_i$ 在同一个集合中（即祖先相同），那么说明在以前两者有了大小关系。

判断这个关系式子就只需要看 $dis_{a_i} - dis_{b_i} = d_i$ 即可。

如果不满足，则不用管，否则肯定是满足条件或者当前 $a_i$ 和 $b_i$ 没有任何关系，那么我们可以进行合并。

合并时，先找到两点的祖先，设 $x$ 为 $a_i$ 的祖先，$y$ 为 $b_i$ 的祖先，先将 $fa_x=y$，然后需要更新一下距离：

$$dis_x=z+dis_{b_i}-dis_{a_i}$$

这个画一个图就可以理解，这里不详细讲了。

时间复杂度：$O(n \log n)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=200200;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,q,x,y,z,cnt=0;
ll p[N],fa[N],dis[N];
ll Find(ll x){
    if(fa[x]!=x){
        ll t=fa[x];
        fa[x]=Find(fa[x]);
        dis[x]+=dis[t];
    }
    return fa[x];
}
int main(){
	n=read(),q=read();
    for(int i=1;i<=n;i++)
      fa[i]=i;
	for(int i=1;i<=q;i++){
		x=read(),y=read(),z=read();
		ll a=Find(x),b=Find(y);
		if(!(a==b&&dis[x]-dis[y]!=z)){
			p[++cnt]=i;
			fa[a]=b;
			dis[a]=z+dis[y]-dis[x];
		}
	}
	for(int i=1;i<=cnt;i++){
		write(p[i]);
		putchar(' ');
	}
	return 0;
}
```


---

## 作者：liuhl_weifang (赞：5)

~~赛时切了，写篇题解纪念一下。~~

先看一个例子：

$$
\begin{cases}
a-b=4\\
b-c=5
\end{cases}
$$

可得 $a-c=9$。

所以我们考虑维护一个边带权并查集，他到根的距离 $w_i$ 表示 $X_{i}-X_{root}=w_i$。对于每次询问 $(a,b,d)$，如果 $a$ 和 $b$ 在同一个集合里，那么：

$$
\begin{cases} X_a-X_{root}=w_a\\X_b-X_{root}=w_b\\X_a-X_b=w_a-w_b \end{cases}
$$

直接判断 $d$ 和 $w_a-w_b$ 是否相等即可。

下文中 $Root_i$ 表示 $i$ 所在集合的根节点。若 $a$ 和 $b$ 不在同一个集合里，那我们就要合并 $a$ 和 $b$ 的集合，并将 $Root_{a}$ 变成 $Root_{b}$ 的儿子。那 $Root_{b}-Root_{a}$ 应为多少呢？

$$
\begin{cases}
Root_b-Root_a=x\\
w_a+x-w_b=d\\
x=d+w_b-w_a
\end{cases}
$$

所以要建一条边权为 $d+w_b-w_a$ 的边。

![](https://cdn.luogu.com.cn/upload/image_hosting/mwtw63le.png)

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,q;
int p[200010];
int w[200010];
vector<int> ans;

int find(int x)
{
	if(p[x]!=x)
	{
		int k = find(p[x]);
		w[x] += w[p[x]];
		p[x] = k;
	}
	return p[x];
}

signed main()
{
	cin >> n >> q;
	for (int i=1;i<=n;i++)
	{
		p[i] = i;
		w[i] = 0;
	}
	for (int i=1;i<=q;i++)
	{
		int u,v,c;
		cin >> u >> v >> c;
		if(find(u)!=find(v))
		{
			int k = c+w[v]-w[u];
			int g = find(u);
			p[find(u)] = find(v);
			w[g] = k;
			ans.push_back(i);
		}
		else
		{
			if(w[u]-w[v]==c)
			{
				ans.push_back(i);
			}
		}
	}
	for (auto i : ans) cout << i << " ";
	return 0;
}
```

---

## 作者：WaterSun (赞：4)

# 思路

带权并查集模板。

如果对于一个三元组 $(a,b,c)$ 如果它能够添加到 $S$ 中一定满足如下条件中的一条：

1. $X_a,X_b$ 满足其中有一个是「不确定」的。在这里 $X_i$「不确定」指 $X_i$ 没有与其它的任意 $X_j$ 有关系 。

2. $X_a,X_b$ 有间接或直接的关系，但是能计算出 $X_a - X_b = c$。

发现此类问题很像并查集维护的过程，于是用带权并查集维护每一个点到根节点的权值和 $val_i$。

发现 $val_i$ 表示的就是 $X_i - X_r$，其中 $r$ 表示的就是 $i$ 所在并查集的根节点。

然后对于第一种情况是很好处理的，对于第二种情况，只需计算 $val_a - val_b$ 与 $c$ 的关系即可。

# code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 2e5 + 10,M = 4e5 + 10;
int n,m;
int f[N],val[N];
vector<int> v;

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline int find(int x){
	if (f[x] != x){
		int pf = f[x];
		f[x] = find(f[x]);
		val[x] += val[pf];
	}
	return f[x];
}

inline bool merge(int a,int b,int c){
	int x = find(a),y = find(b);
	if (x != y){
		f[x] = y;
		val[x] = val[b] - val[a] + c;
		return true;
	}
	else return (val[a] - val[b] == c);
}

signed main(){
	n = read();
	m = read();
	for (re int i = 1;i <= n;i++) f[i] = i;
	for (re int i = 1;i <= m;i++){
		int a,b,c;
		a = read();
		b = read();
		c = read();
		if (merge(a,b,c)) v.push_back(i);
	}
	for (auto u:v) printf("%lld ",u);
	return 0;
}
```

---

## 作者：caoshuchen (赞：3)

# [[ABC328F] Good Set Query](https://www.luogu.com.cn/problem/AT_abc328_f)

## 前言

这是我第一次 ABC 比赛做 $6$ 题，希望大家能给我一些鼓励与支持。

## 思路

看到这题，首先想到这说的是相对大小，那我们可以空想一个数轴，那么这个 $d_i$ 就是两点的相对位置。

然后你在赛时应该做的便是制造与分析数据，依此我们发现：

> 如果 $a_i$ 与 $b_i$ 之前没有任何条约限制，那我们肯定可以让 $S+\{i\}$ 是好的。
>
> 如果 $a_i$ 与 $b_i$ 在之前就已经有制约了，那我们就直接查看两个数的相对位置是否等于 $d_i$，如果等于，那说明以前的制约正好与现在的制约相同，所以可以让 $S+\{i\}$ 是好的，否则不可。

我们不难看出，判断是否有制约，可以用并查集判断，而查询已有制约可以通过查询 $a_i$ 与其根节点的相对大小 $d_{a_i}$，以及 $b_i$ 与其根节点的相对大小 $d_{b_i}$ 来得知。

## 细节

这道题的细节是有的。

### 壹

压缩路径时，应该先进行访问父节点，然后再对存相对大小的数组进行操作，我用的父节点数组名是 $p$，存与根的相对大小的数组名是 $s$，则我的代码如下

```c++
int find(int x) {//求根节点
	if (p[x] == x)
		return x;//自己就是根
	int rt = find(p[x]);//先找到根
	s[x] += s[p[x]];
	//此时s[p[x]]是已经等于了它与rt的偏移量（相对大小）
	//而s[x]现在存的是它与p[x]的偏移量而不是与rt的
	//所以加和即可
	p[x] = rt;
	return rt;
}
```

### 贰

在合并的时候，我们要把 $a_i$ 所在子树连向 $b_i$ 的。而我们应该是将 $\operatorname{find}(a_i)$ 与 $\operatorname{find}(b_i)$ 相连，但是由于我觉得太难算了，所以我选择把 $\operatorname{find}(a_i)$ 与 $b_i$ 相连，但注意，一定是要让 $\operatorname{find}(a_i)$ 与其他相连，不然树就断了。

此时我们需要修改 $s_{\operatorname{find}(a_i)}$。我们只知道 $\begin{cases}
X_{a_i}-X_{b_i}=d_i & ①\\
X_{\operatorname{find}(a_i)}-X_{a_i}=s_{a_i} & ②
\end{cases}$ 则我们用 $①-②$ 得 $X_{\operatorname{find}(a_i)}-X_{b_i}=d_i-s_{a_i}$。因此代码如下：

```c++
void unn(int x, int y, long long d) {
	int px = find(x);
	p[px] = y;
	s[px] = d - s[x];
}
```

### 叁

查询约束时，我们可以知道 $\begin{cases}
X_{a_i}-X_{rt}=s_{a_i} & ①\\
X_{b_i}-X_{rt}=s_{b_i} & ②
\end{cases}$ 则我们用 $①-②$ 得 $X_{a_i}-X_{b_i}=s_{a_i}-s_{b_i}$，所以我们查询 $s_{a_i}$ 和 $s_{b_i}$ 然后做差即可求出其约束。

### 肆

$\color{Red}\mathbf{注意，我们是在\ find\ 函数里进行对\ p\ 和\ s\ 数组更新的，所以要保证所有访问\ p\ 和\ s\ 之前，有调用过\ find。}$

## Code

```c++
#include <bits/stdc++.h>
using namespace std;

struct DSU {
	vector<long long> p, s;
	DSU(){};
	DSU(int n) {
		p = vector<long long>(n + 5, 0);
		s = vector<long long>(n + 5, 0);
		for (int i = 1; i <= n; i++)
			p[i] = i, s[i] = 0;
	}
	int find(int x) {
		if (p[x] == x)
			return x;
		int rt = find(p[x]);
		s[x] += s[p[x]];
		p[x] = rt;
		return rt;
	}
	void unn(int x, int y, long long d) {
		int px = find(x);
		p[px] = y;
		s[px] = d - s[x];
	}
} D;

int n, q;
bool f[200005];

int main() {
	cin >> n >> q;
	D = DSU(n);
	for (int i = 1, a, b, d; i <= q; i++) {
		cin >> a >> b >> d;
		if (D.find(a) != D.find(b))
			D.unn(a, b, d), f[i] = true;
		else {
			if (D.s[a] - D.s[b] == d)
				f[i] = true;
		}
	}
	for (int i = 1; i <= q; i++)
		if (f[i])
			cout << i << " ";
	cout << endl;
	return 0;
}
```

---

## 作者：Creeper_l (赞：1)

复习了一下边带权并查集板子。

设 $d_{x}$ 表示当前点到它所在连通块根节点的距离。

合并点 $x$ 和点 $y$ 所在两个连通块时需要更新 $d$。因为将 $x$ 点所在连通块的根节点的父亲节点设为了 $y$ 点所在连通块的根节点，所以有 $x \to y \to Find(y)=x \to Find(x) \to Find(y)$，更新 $d_{Find(x)}=d_{y}+z-d_{x}$，其中 $z$ 是 $x$ 点到 $y$ 点的距离。

路径压缩的时候也需要更新 $d$，直接将 $d_{x}$ 加上 $d_{fa_{x}}$ 即可。

$i$ 可以被加入集合 $S$，当且仅当当前的 $x$ 和 $y$ 不在一个连通块或者 $x$ 到 $y$ 的距离为 $z$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f
#define inf_db 127
#define ls id << 1
#define rs id << 1 | 1
#define re register
#define endl '\n'
typedef pair <int,int> pii;
const int MAXN = 2e5 + 10;
int n,q,x,y,z,d[MAXN],fa[MAXN],ans[MAXN],cnt;
inline int Find(int x)
{
	if(x == fa[x]) return x;
	int f = fa[x];
	fa[x] = Find(fa[x]),d[x] += d[f];
	return fa[x];
}
signed main()
{
	cin >> n >> q;
	for(int i = 1;i <= n;i++) fa[i] = i;
	for(int i = 1;i <= q;i++)
	{
		cin >> x >> y >> z;
		int fx = Find(x),fy = Find(y);
		if(fx != fy)
			fa[fx] = fy,d[fx] = d[y] - d[x] + z,ans[++cnt] = i;
		else if(d[x] - d[y] == z) 
			fa[fx] = fy,d[fx] = d[y] - d[x] + z,ans[++cnt] = i;
	}
	for(int i = 1;i <= cnt;i++) cout << ans[i] << " ";
	return 0;
}

```


---

## 作者：CQ_Bob (赞：1)

## 分析

考虑并查集。

对于 $a_i,b_i,d_i$，若 $a_i,b_i$ 在之前的满足要求的操作中，$a_i,b_i$ 不在同一个集合里，则在之前 $X_{a_i},X_{b_i}$ 的相对差值是可以任意改变的。令 $k=X_{a_i}-X_{b_i}$，则我们需要将 $a_i$ 所在集合中所有元素的值增加 $d_i-k$。然后将 $a_i,b_i$ 所在集合合并。

很显然，对于将集合中所有元素增加一定值再与另一个集合合并的操作，可以按秩合并修改两个集合中包含元素数量少的那个。这个暴力处理即可。

同理，在 $a_i,b_i$ 在同一个集合里时，由于其相对差值已经确定，只需要看 $X_{a_i}-X_{b_i}$ 是否与 $d$ 相等。

## 代码

[Link](https://atcoder.jp/contests/abc328/submissions/47547845).

---

## 作者：SSER_ZRQ (赞：0)

当时做的时候脑子短路了，没想到带权并查集，于是搞了一个启发式合并。

维护一个森林，每个节点存它在这棵树内的各种信息。

于是就可以把操作分为两类：

1. 如果 $a_i$ 与 $b_i$ 在不同的树，则合并这两棵树，暴力修改其中一棵树的信息。
2. 如果 $a_i$ 与 $b_i$ 在同一棵树内，则查询 $a_i$ 与 $b_i$ 的**距离**是否等于 $d_i$。

距离的定义：设 $fa$ 为 $x$，$y$ 的最近公共祖先，距离为 $dis_{fa,x}-dis_{fa,y}$。

运用带权 LCA，每次第二类操作的复杂度为 $O(\log n)$，考虑如何优化第一类操作。

采用启发式合并的思想，每次只暴力重构较小的那棵树。

第一类操作的总复杂度降为 $O(n \log^2 n)$。

总复杂度为 $O(n \log^2 n)$。

``` cpp
int find(int x){
	if(FA[x]==x) return x;
	return FA[x]=find(FA[x]);
}
void rebuild(int x,int y,int z){
	fa[x][0]=y,dep[x]=dep[y]+1;
	dis[x][0]=z;
	for(int i=1;i<20;i++){
		fa[x][i]=fa[fa[x][i-1]][i-1];
		dis[x][i]=dis[x][i-1]+dis[fa[x][i-1]][i-1];
	}
	for(auto t:d[x]){
		if(t.first==y) continue;
		rebuild(t.first,x,t.second);
	}
}
int DIS(int x,int y){
	if(x==y) return 0;
	int ans=0;
	for(int i=19;i>=0;i--){
		if(dep[fa[x][i]]>=dep[y]){
			ans+=dis[x][i];
			x=fa[x][i];
		}
	}
	if(x==y) return ans;
	for(int i=19;i>=0;i--){
		if(fa[x][i]==fa[y][i]) continue;
		ans+=dis[x][i],ans-=dis[y][i];
		x=fa[x][i],y=fa[y][i];
	}
	return ans+dis[x][0]-dis[y][0];
}
void merge(int x,int y,int z){
	int fx=find(x),fy=find(y);
	FA[fx]=fy,sz[fy]+=sz[fx];
	d[y].push_back(make_pair(x,z));
	d[x].push_back(make_pair(y,-z));
	rebuild(x,y,z);
}
void work(){
	n=read(),m=read();
	init();//初始化各数组 
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		int fx=find(x),fy=find(y); 
		if(fx!=fy){
			if(sz[fx]>sz[fy]) swap(x,y),z=-z;
			merge(x,y,z);
			printf("%lld ",i);
		}
		else{
			if(dep[x]<dep[y]) swap(x,y),z=-z;
			if(DIS(x,y)==z) printf("%lld ",i);
		}
	}
}
```
------------

后记：既然 $DIS_{x,y}=dis_{fa,x}-dis_{fa,y}$，那么 $DIS_{x,y}=dis_{root,x}-dis_{root,y}$（因为重复的路可以抵消）。

不难发现，当路径可以抵消时，这就是带权并查集！



---

## 作者：WilliamFranklin (赞：0)

一道非常水的 F 题。

### 主要思路

第一眼，图论题。

第二眼，才看出是个并查集。

首先，我们很容易发现，就是在判断或加入 $X_{a_i}$ 与 $X_{b_i}$ 之间的数量关系，所以第一反应就是连一条有向边，边权为 $d_i$。

进一步，我们发现这东西完全可以用并查集完成，这里用的仅有路径压缩，具体过程如下：

我们建立一个并查集必备数组 $fa$，以及一个权值数组 $w$。其中 $w_j$ 表示与 $fa_j$ 的差值是多少。。

然后考虑每一个操作 $i$。

首先，要判断一下 $a_i$ 和 $b_i$ 是否在同一棵并查集树，也就是因为这里先路径压缩的一遍，我们就可以保证 $fa_{a_i}$ 与 $fa_{b_i}$ 都是它们所在的并查集树的根了。如果在同一棵树上，就直接判断一下 $w_{a_i}$ 减 $w_{b_i}$ 是否等于 $d_i$，如果等于，就说明这个集合可以加入答案。如果不是在同一棵树上的话，我们就考虑如何将两棵并查集树合并。想让这两棵树合并，就必须在两棵树的根上找关系。设 $a_i$ 所在树的根的值为 $x$，$b_i$ 所在树的根的值为 $y$，那么可得 $x + w_{a_i} - (y + w_{b_i}) = d_i$，化一下，$x - y = d_i + w_{b_i} - w_{a_i}$。所以直接按照式子合并即可。

也许还有一些地方说的不够清楚，看下代码吧。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); TI--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 2e5 + 5;
int fa[N];
long long w[N];
int find(int x) {
	if (fa[x] == x) return x;
	int p = find(fa[x]);
	w[x] += w[fa[x]];
	fa[x] = p;
	return fa[x];
}
void U(int a, int b, long long d) {
	int x = find(a), y = find(b);
	w[y] = w[a] - d - w[b];
	fa[y] = x;
}
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++) fa[i] = i, w[i] = 0;
	for (int i = 1; i <= q; i++) {
		int a, b;
		long long d;
		cin >> a >> b >> d;
		if (find(a) != find(b)) {
			cout << i << ' ';
			U(a, b, d);
		} else {
			if (w[a] - w[b] == d) {
				cout << i << ' ';
			}
		}
	}
	return 0;
} 
```

### 谢谢观看

---

## 作者：未来姚班zyl (赞：0)

## 题目大意

给你 $m$ 组关系，第 $i$ 组要求 $X_{a_i}-X_{b_i}=d_i$。你需要维护一个集合 $S$，从 $1$ 到 $m$ 操作，如果加入当前关系之后仍存在满足要求的序列 $X$，则加入当前关系，否则什么都不做。

## 题目分析

显然要把关系当成边来建图，用深度表示与根节点的差值。

对于当前加入的关系，有两种情况，第一种，两点在不同的连通块，则加入一条边权为 $d_i$ ，由 $a_i$ 指向 $b_i$ 的边，顺便建立一个反边，边权也相反，这描绘了两个点的差值。随后更新根节点和距离。否则，直接判断两点的距离之差是否等于 $d_i$。

这样就延伸了两个均可以通过的做法。

第一种是在线带权并查集（这里感谢 [Katyusha_01](https://www.luogu.com.cn/user/533742) 的思路）。当然这也是很多人赛时的做法。

第二种方法是离线建森林。然后对于需要判断的关系直接在森林上判断即可。

第一种方法的代码：

```cpp
//by Katyusha_01
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int a[200011],b[200011],d[200011];
int fa[200011],dis[200011],siz[200011];
pair<int,int> find(int x)
{
	if(x == fa[x]) return {x,0};
	pair<int,int> res = find(fa[x]);
	res.second += dis[x];
	return res;
}
vector<int> ans;
inline void Insert(int i)
{
	int x = a[i],y = b[i];
	pair<int,int> fx = find(x),fy = find(y);
	if(fx.first == fy.first)
	{
		if(fx.second - fy.second != d[i]) return;
		ans.push_back(i);
		return;
	}
	int ya = fx.second - d[i];
	ya -= fy.second;
	x = fx.first,y = fy.first;
	if(siz[x] < siz[y])
		swap(x,y),ya = -ya;
	dis[y] = ya,fa[y] = x,siz[x] += siz[y];
	ans.push_back(i);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n >> m;
	for(int i = 1;i <= n;i++) fa[i] = i,dis[i] = 0,siz[i] = 1;
	for(int i = 1;i <= m;i++)
	{
		cin >> a[i] >> b[i] >> d[i];
		Insert(i);
	}
	for(auto i:ans) cout << i << " ";
	return 0;
}
```

第二种方法的代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =3e5+5,M=1e6+5,inf=(1LL<<31)-1;
const ll llf=1e18,mod=998244353,bas=131;
const ui base=13331;
const double eps=1e-7;
using namespace std;
int n,m;
int a[N],b[N],d[N];
int dis[N];
int f[N],del[N];
inline int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}
bool vis[N],is[N];
int h[N],to[N<<1],nxt[N<<1],w[N<<1],cnt;
inline void add(int a,int b,int c){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt,w[cnt]=c;
}
inline void dfs(int x){
	vis[x]=1;
	e(x)if(!vis[y])dis[y]=dis[x]+w[i],dfs(y);
}
signed main(){
	n=read(),m=read();
	rep(i,1,m)a[i]=read(),b[i]=read(),d[i]=read(),dis[i]=llf;
	rep(i,1,n)f[i]=i,vis[i]=0;
	rep(i,1,m){
		int l=find(a[i]),r=find(b[i]);
		if(l==r)continue;
		is[i]=1;
		f[l]=r;
		add(a[i],b[i],d[i]),add(b[i],a[i],-d[i]);
	}
	rep(i,1,n)if(!vis[i])dfs(i);
	rep(i,1,m)if(!is[i]){
		if(dis[a[i]]+d[i]==dis[b[i]])is[i]=1;
	}
	rep(i,1,m)if(is[i])cout <<i<< ' ';
	return 0;
}
```


---

## 作者：DerrickLo (赞：0)

首先如果我们对每个 $a_i$ 和 $b_i$ 连一条边。

然后我们判断每一条边可不可加：

- 如果可加，那么就意味着加入这条边后未出现环，或者加入这条边后这个环的边权和是 $0$，注意这个边权是有向的，反向的边权也是正向的边权的相反数。

那么我们求出这个图编号尽量靠前的生成树，换句话说，从小到大枚举 $i$，如果 连 $a_i$ 与 $b_i$ 并未构成环，那么就加上这条边。

接着我们将每条树边重定边权，如果是由深度大的节点连向深度小的节点则边权取反，反之不变。

然后对于每一条非树边 $(a_i,b_i,w_i)$，在树上必然有一条从 $a_i$ 到 $b_i$ 的路径，设 $a_i$ 与 $b_i$ 的最近公共祖先是 $f$，则这条路径一定是 $a_i\rightarrow f \rightarrow b_i$ 的，且前半段一直在往上走，后半段在往下走。

那么求出树上 $a_i$ 到 $f$ 的距离 $x$，$b_i$ 到 $f$ 的距离 $y$，判断一下 $x-y+w_i$ 是否等于 $0$ 即可。

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,q,a[200005],b[200005],d[200005],f[200005],cnt,sz[200005],top[200005],son[200005],dep[200005],fa[200005],sum[200005],vl[200005],vis[200005],viss[200005];
vector<int> ve[200005];
vector<pair<int,int>>ve2[200005];
struct edge{
	int u,v,w;
}ee[200005];
int find(int x){
	return(f[x]==x)?x:f[x]=find(f[x]);
}
void dfs1(int u,int fat,int de){
	sz[u]=1,fa[u]=fat,dep[u]=de;
	for(int v:ve[u]){
		if(v==fa[u])continue;
		dfs1(v,u,de+1);
		sz[u]+=sz[v];
		if(sz[v]>sz[son[u]])son[u]=v;
	}
}
void dfs(int u){
	viss[u]=1;
	if(u!=1)sum[u]=sum[fa[u]]+vl[u];
	for(int v:ve[u]){
		if(v==fa[u])continue;
		dfs(v);
	}
}
void dfs2(int u,int tp){
	top[u]=tp;
	if(!son[u])return;
	dfs2(son[u],tp);
	for(int v:ve[u]){
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
int lca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		u=fa[top[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	return v;
}
signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=q;i++)cin>>ee[i].u>>ee[i].v>>ee[i].w;
	for(int i=1;i<=q;i++){
		if(cnt==n-1)break;
		int fx=find(ee[i].u),fy=find(ee[i].v);
		if(fx==fy)continue;
		cnt++,vis[i]=1,f[fx]=fy;
		ve[ee[i].u].emplace_back(ee[i].v),ve[ee[i].v].emplace_back(ee[i].u);
	}
	for(int i=1;i<=n;i++)if(!fa[i])dfs1(i,-1,1);
	for(int i=1;i<=q;i++)if(vis[i]){
		if(dep[ee[i].u]<dep[ee[i].v])vl[ee[i].v]=ee[i].w;
		else vl[ee[i].u]=-ee[i].w;
	}
	for(int i=1;i<=n;i++)if(!viss[i])dfs(i);
	for(int i=1;i<=n;i++)if(!top[i])dfs2(i,i);
	for(int i=1;i<=q;i++){
		if(vis[i])cout<<i<<' ';
		else if(ee[i].u==ee[i].v){
			if(ee[i].w==0)cout<<i<<' ';
		}
		else{
			int ff=lca(ee[i].u,ee[i].v),aa=sum[ee[i].u]-sum[ff],bb=sum[ee[i].v]-sum[ff];
			if(aa-bb+ee[i].w==0)cout<<i<<' ';
		}
	}
	return 0;
}
```

---

## 作者：lhyuu (赞：0)

我们设 $i$ 号节点的点权为 $f_i$，考虑构想一个图论模型。考虑连接 $a_i,b_i$。

不难发现，若连通块中一个点权已知，则其余点的点权可以推出来。现在我们考虑一个连通块 $S$，不妨设置一个根，则其它点可以由根的点权推出。倘若有根 $i\in S$，对于其余的点 $j\in S$ 满足 $f_j=f_i+w_j$，其中 $w_j$ 表示 $j$ 与根的差值。

那么我们考虑连接 $a,b$ 时，分以下两种情况：

- $a,b$ 同属一个连通块，则我们需要判断我们操作的合法性，即 $f_a-f_b=d$。则判断 $f_a-d=f_b$ 的合法性即可判断能否连这条边。

- $a,b$ 不属于同意个连通块，则我们显然可以连边，我们考虑连接两个连通块，并寻找一个新的根。设 $a,b$ 所在连通块的根分别为 $x,y$ 让我们罗列一下联通 $a,b$ 的式子：

$f_b=f_a-d$，则 $f_x+w_a-d=f_y+w_b$，由于 $f_x,f_y$ 是由我们设定的，我们要的只是一个相对大小，于是我们考虑修改 $f_x$ ,使得等式成立。

移项得 $f_x=f_y+w_b+d-w_a$，代换即可。

回到原本的式子：$f_a=f_x+w_a$，那我们修改了 $f_x$，原本以 $x$ 为根的连通块点权也会改变。如何维护？考虑启发式合并暴力维护，将对于连通块中的所有点 $i$ 的点权 $f_i$ 加上 $f_x$ 改变的差值即可。

```cpp
#include<bits/stdc++.h>
#define pii pair<int, int>
#define mpr make_pair
#define x first
#define y second
#define up(i, a, b) for(int i = a; i <= (int)b; ++i)
#define dn(i, a, b) for(int i = a; i >= (int)b; --i)
#define vc vector
#define pb push_back
#define itset set< int >::iterator
#define lowbit(x) (x & -x)
#define int long long

using namespace std;

const int MN = 2e5 + 5;

int n, Q;
int w[MN], vis[MN], fa[MN], sz[MN];
int find(int x){
	if(x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
void con(int x, int y){
	x = find(x), y = find(y);
	fa[x] = y;
	sz[y] += sz[x];
}
vc<int> v[MN];
vc<int> ans;

signed main(){
	scanf("%lld%lld", &n, &Q);
	up(i, 1, n){
		fa[i] = i, sz[i] = 1; v[i].pb(i);
	}
	up(T, 1, Q){
		int x, y, z; scanf("%lld%lld%lld", &x, &y, &z);
		if(find(x) == find(y)){
			if(w[x] - w[y] == z) ans.pb(T);
			continue;
		}
		else{
			ans.pb(T);
			if(sz[find(x)] < sz[find(y)]) swap(x, y), z = -z;
			int add = w[find(x)] + w[x] - z - w[y] - w[find(y)];
			for(int g : v[find(y)]){
				w[g] += add;
				v[find(x)].pb(g);
			}
			v[find(y)].clear();
			con(y, x);
		}
	}
	for(int y : ans) printf("%lld ", y);

	return 0;
}

```


---

## 作者：cancan123456 (赞：0)

如果你做过 [P4079 [SDOI2016] 齿轮](https://www.luogu.com.cn/problem/P4079)，很容易想到带权并查集。

对每个 $X_i$ 建一个点 $i$，我们考虑并查集，除了维护 $\rm fa$ 数组之外，我们还维护 $\rm w$，满足 $\rm w_i=X_{fa_i}-X_i$，容易在路径压缩时更新 $\rm w$ 数组。

考虑处理添加一个约束判断是否合法，如果 $\rm a,b$ 已经连通，那么路径压缩一下就可以得到 $\rm X_{root}-X_a$ 与 $\rm X_{root}-X_b$，那么合法就需要满足：

$$\rm X_a-X_b=(X_{root}-X_b)-(X_{root}-X_a)=d$$

如果 $\rm a,b$ 不连通，那么我们令 $\rm root_a=fa_a,root_b=fa_b$ 为 $a,b$ 连通块的根节点，然后令 $\rm fa_{root_a}=root_b$ 且

$$\rm w_{root_a}=X_{root_b}-X_{root_a}=(X_{root_b}-X_b)-(X_{root_a}-X_a)-(X_a-X_b)=w_b-w_a-d$$

时间复杂度 $O(q\log_{1+q/n}n)$，可以通过此题。

```cpp
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 200005;
int fa[N];
ll w[N];
int find(int x) {
	if (fa[x] == x) {
		return x;
	} else {
		int fx = find(fa[x]);
		w[x] = w[fa[x]] + w[x];
		fa[x] = fx;
		return fx;
	}
}
int main() {
	int n, q;
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++) {
		fa[i] = i;
	}
	for (int a, b, root_a, root_b, i = 1; i <= q; i++) {
		ll d;
		scanf("%d %d %lld", &a, &b, &d);
		root_a = find(a);
		root_b = find(b);
		if (root_a == root_b) {
			if (w[b] - w[a] == d) {
				printf("%d ", i);
			}
		} else {
			fa[root_a] = root_b;
			w[root_a] = w[b] - w[a] - d;
			printf("%d ", i);
		}
	}
	return 0;
}
```

---

## 作者：DengDuck (赞：0)

差不多得了，F 题出个并查集板子有意思吗？

考虑初中数学，我们都知道有大量未知数的时候考虑统一单位，这里也是，考虑把数量关系转换成所有未知数对于一个未知数的数量关系。

进一步想到把数量关系转化成边，$(x,y,w)$ 的一条边表示 $X_x-X_y=w$，然后利用并查集路径压缩即可。

考虑一个限制条件的两个未知数是两个已经在树上相连的，那么其本身的数量关系是可以推导出来的，推出来之后看看和这个新的限制是否相同即可。

还有一点需要注意的是，对于一个新加的关系，由于我们实际加边是对于两个未知数的根节点，所以要先推算出根节点之间的数量关系。


```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2e5+5;
LL n,m,x,y,z,fa[N],to[N];
LL find(LL x)
{
	if(fa[x]==x)return x;
	LL t=find(fa[x]);
	to[x]+=to[fa[x]];
	return fa[x]=t;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y>>z;
		LL fx=find(x),fy=find(y);
		if(fx!=fy)
		{
			fa[fx]=fy,to[fx]=z-to[x]+to[y];
			cout<<i<<' ';
		}
		else 
		{
			if(z!=to[x]-to[y])continue;
			cout<<i<<' ';
		}
	}
}
```

---

## 作者：liangbowen (赞：0)

[blog](https://www.cnblogs.com/liangbowen/p/17826840.html)。提供一个普通并查集 + 启发式合并做法。

---

考虑直接维护 $X_i$。对于 $X_u-X_v=w$，分四种情况。

+ $X_u,X_v$ 都没被维护过。直接钦定 $X_u\gets w,X_v\gets0$，以后再改。
+ $X_u$ 没被维护过，$X_v$ 被维护过。显然 $X_u\gets X_v+w$。
+ $X_v$ 没被维护过，$X_u$ 被维护过。显然 $X_v\gets X_u-w$。
+ $X_u$ 与 $X_v$ 都被维护过。将每次合法操作视作连边 $(u,v)$，这里实际上有两种情况。
  + $u,v$ 在同一个连通块内。如果 $X_u-X_v=w$ 那么是合法的。
  + $u,v$ 不在同一个连通块内。其实这是必定合法的，本质是 $X_v\gets X_u+w$，只不过 $v$ 所在的连通块的**所有元素的值已经被钦定过了**。直接暴力修改 $v$ 所在的连通块 的 $X_i$ 值。（$\#$）

上述做法是 $O(qn)$ 的，瓶颈在 $\#$ 处的暴力修改。将暴力修改替换为启发式合并即为 $O(q\log n)$。

[code](https://atcoder.jp/contests/abc328/submissions/47518466)，时间复杂度 $O(q\log n)$。


---

## 作者：osfly (赞：0)

### some interesting things

赛时傻逼按秩合并的时候没更新 `siz`。

### 正文

可以考虑将 $a,b$ 看作节点，$x_a,x_b$ 看作 $a,b$ 的点权。

那么对于每一个三元组，我们可以看作将 $a$ 与 $b$ 连边。

显然，初始的时候有 $n$ 个节点，也就是 $n$ 个连通块。

此时有两种情况：

1. $a$ 与 $b$ 已经在同一个连通块。直接判断点权是否满足要求即可。

2. $a$ 与 $b$ 不在同一个连通块内。

	为了方便叙述，下文中 $A$ 表示 $a$ 所在的连通块，$B$ 表示 $b$ 所在的连通块。

	那么显然，对于当前局面，我们可以通过调整 $A$ 中的每一个节点的点权或者调整 $B$ 的每一个节点的点权从而使得 $x_a-x_b=d$。考虑到两个连通块合并，我们可以使用并查集维护，注意要按秩合并，否则复杂度会爆炸。
    
	具体的，如果 $A$ 的大小大于 $B$ 的大小，我们可以将 $B$ 合并到 $A$ 中去，并对原来 $B$ 中的每一个节点加上 $(x_a-d)-x_b$。
    
 	反之，将 $A$ 合并到 $B$ 中去，并对原来 $A$ 中的每一个节点加上 $(x_b+d)-x_a$。
    
	可以发现这样的合并方式一定能满足 $S$ 之前所有的三元组的要求。
    
```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int N=2e5+10;

int n,q;
ll x[N];
int f[N];
int s[N],cnt;
int siz[N];

struct edge
{
	int u,v,nxt;
}e[N<<1];
int head[N],tot;
void add(int u,int v)
{
	e[++tot]=edge{u,v,head[u]};
	head[u]=tot;
}

void dfs(int u,int fa,ll num,int rt)
{
	siz[rt]++;
	x[u]+=num;
	f[u]=rt;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa) continue;
		dfs(v,u,num,rt);
	}
}

int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) f[i]=i,siz[i]=1;
	for(int i=1;i<=q;i++)
	{
		int a,b;
		ll d;
		scanf("%d%d%lld",&a,&b,&d);
		int fa=f[a],fb=f[b];
		if(fa!=fb)
		{
			add(fa,fb),add(fb,fa);
			if(siz[fa]>siz[fb]) f[fb]=fa,dfs(fb,fa,(x[a]-d)-x[b],fa); 
			else f[fa]=fb,dfs(fa,fb,(x[b]+d)-x[a],fb);
			s[++cnt]=i;
		}
		else if(x[a]-x[b]==d) s[++cnt]=i;
	}
	for(int i=1;i<=cnt;i++) printf("%d ",s[i]);
	return 0;
}
```

与本题运用了相似的思想的题目：[P3302 森林](https://www.luogu.com.cn/problem/P3302)。

---

## 作者：LCat90 (赞：0)

本质上是在图中加很多边，然后如果遇到重边（或者环），判断他们权值是否相等。

还是要记录一个 $a$ 数组表示当前联通块中，某一个值为 $0$，其他位置的值（相对）。

然后我们用并查集维护，同时考虑启发式合并暴力修改 $a$。

或者使用带权并查集。

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, m, siz[N], fa[N], a[N];
vector <int> G[N];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void update(int x, int y) {
	for(int to : G[x]) update(to, y);
	a[x] += y;
}
signed main() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
    for(int Q = 1, x, y, z;Q <= m; ++Q) {
		scanf("%lld %lld %lld", &x, &y, &z);
    	int p = find(x), q = find(y);
    	if(p == q) {
    		if(a[x] - a[y] == z) printf("%lld ", Q);
    		continue;
		}
		if(siz[p] >= siz[q]) swap(p, q), swap(x, y), z = -z; // 启发式合并 
		update(p, z + a[y] - a[x]);
		fa[p] = q, siz[q] += siz[p];
		G[q].pb(p);
		printf("%lld ", Q);
	}
    return 0;
}
```

---

## 作者：allenchoi (赞：0)

## 科技：  
并查集，启发式合并  
## 思路：
首先，我们可以把一条限制看成一条边。  
那么，对于每一个连通块，我们随意选择一棵生成树，随意选择一个点作根，用 $dis_i$ 表示在树边上根到 $i$ 的距离。  
这样，每一组限制可以转化成 $dis_{a_i}-dis_{b_{i}}=d_i$。  
我们得出了一个 $O(n^2)$ 的算法：  
新加入一个限制时，若两端属于同一连通块（并查集判断），则 $O(1)$ 快速判断是否合法；  
若两端不属于一个连通块，则 $O(n)$ 重构整个图的 $dis$ 数组和并查集数组。  
考虑优化：注意到其中一块树的结构可以是不变的，我们可以将其中一点直接放到另一点的子树中。  
那么，每次令点数多的一块不变，暴力重构点数小的一块的 $dis$ 数组和并查集数组（即启发式合并），于是时间复杂度降到 $O(n\log n)$。  
## 代码：  
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n,q,tot = 1,f[N],siz[N],head[N],to[N << 1],val[N << 1],nxt[N << 1];
ll dis[N];
vector <int> ans;
void add_(int x,int y,int c)
{
	tot++;
	to[tot] = y,val[tot] = c;
	nxt[tot] = head[x],head[x] = tot;
}
int find(int x){return f[x] == x ? x : f[x] = find(f[x]);}
void dfs(int x,int fa,int d)
{
	f[x] = f[fa],dis[x] = dis[fa] + d;
	for(int i = head[x],y;i;i = nxt[i])
	{
		if((y = to[i]) == fa) continue;
		dfs(y,x,val[i]);
	}
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i = 1;i <= n;i++) f[i] = i,siz[i] = 1;
	for(int i = 1,a,b,d;i <= q;i++)
	{
		scanf("%d%d%d",&a,&b,&d);
		int fx = find(a),fy = find(b);
		if(fx == fy)
		{
			if(dis[a] - dis[b] == d) ans.push_back(i);
			continue;
		}
		if(siz[fx] > siz[fy]) swap(fx,fy),swap(a,b),d = -d;
		siz[fy] += siz[fx];
		add_(a,b,-d),add_(b,a,d);
		dfs(a,b,d);
		ans.push_back(i);
	}
	for(int i = 0;i < ans.size();i++) printf("%d ",ans[i]);
	printf("\n");
	return 0;
}
```

---

## 作者：FReQuenter (赞：0)

我们考虑出现关系的时候直接暴力修改 $X$ 数组。

多次修改之间如果修改的 $X_a$ 和 $X_b$ 没有交集，那么就不用管它，直接改就行了。

如果修改的两个 $X_a$ 和 $X_b$ 已经属于一个团伙就可以直接判断。

当修改出现交集的时候就需要合并了。

我们直接把较小的一团 $X_a$ 合并到较大的一团 $X_b$ 里面去。具体操作是这样的：先记录 $X_a$ 和 $X_b$ 距离差值 $d$ 还差多少，然后给所有和 $X_a$ 之前有关系的 $X_i$ 全部加上这个差值。

我们每次只把大小较小的一团合并到较大的一团里，就可以把复杂度维持在 $O(n\log n)$。这种合并方式称为启发式合并。[复杂度证明](https://www.baidu.com/s?tn=48021271_hao_pg&wd=%E5%90%AF%E5%8F%91%E5%BC%8F%E5%90%88%E5%B9%B6%E7%9A%84%E5%A4%8D%E6%9D%82%E5%BA%A6%E8%AF%81%E6%98%8E&ie=UTF-8)。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q,x[200005],p[200005];
vector<int> v[200005];
void merge(int a,int b,int val){
	bool f=0;
	if(v[p[a]].size()>v[p[b]].size()) swap(a,b),f=1;
	int fa=p[a],fb=p[b];
	int diff=x[b]+val-x[a];
	if(f) diff=x[a]+val-x[b];
	for(auto nx:v[fa]){
		if(!f) x[nx]+=diff;
		else x[nx]-=diff;
		v[fb].push_back(nx),p[nx]=fb;
	}
	v[fa].clear();
}
signed main(){
	vector<int> ans;
	cin>>n>>q;
	for(int i=1;i<=n;i++) v[i].push_back(i),p[i]=i;
	for(int i=1;i<=q;i++){
		int a,b,d;
		cin>>a>>b>>d;
		int fa=p[a],fb=p[b];
		if(fa==fb){
			if(x[a]-x[b]!=d) continue;
			else ans.push_back(i);
		}
		else{
			ans.push_back(i);
			merge(a,b,d);
		}
	}
	for(auto nx:ans) cout<<nx<<' ';
}
```

---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc328_f)
### 题解
水题，并查集模板题，具体题目自己去搜吧。

题目不重复了，讲一下注意点：

- 题目中给的是 $d_l-d_r=c$，但我们维护的是 $d_r-d_l=-c$ 需要反转。
- 注意 $l>r$ 时**不需要反转**，因为涉及到并查集的性质，改变合并的顺序可以有效改变操作的顺序。

### 代码
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <map>
#include <set>
#define x first
#define y second
#define pb push_back
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = cin.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = cin.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = cin.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
const int N = 200010;
int n,q;
int p[N];
LL d[N];
int find (int x) {
	if (p[x] != x) {
		int rx = find (p[x]);
		d[x] += d[p[x]];
		p[x] = rx;
	}
	return p[x];
}
int main () {
	cin >> n >> q;
	for (int i = 0;i <= n;i++) p[i] = i;
	vector <int> ans;
	for (int i = 1;i <= q;i++) {
		int l,r,c;
		cin >> l >> r >> c;
		c = -c;
		int x = find (l),y = find (r);
		if (x != y || d[l] - d[r] == c) {
			if (x != y) p[x] = y,d[x] = c + d[r] - d[l];
/*
ps:下面的是便于理解d[x]=c+d[r]-d[l]画的图。
        d[x]
       x->y
       ^  ^
 d[l] |    | d[r]
       l->r
         c
*/
			ans.push_back (i);
		}
	}
	for (int x : ans) cout << x << ' ';
	cout << endl;
	return 0;
}
```

---

## 作者：Redshift_Shine (赞：0)

# [Good Set Query](https://www.luogu.com.cn/problem/AT_abc328_f)

本题具象化题意如下：

> 对于一个长度为 $N$ 且初始值未知的数组 $X$，进行 $M$ 次形如 $a_i,b_i,d_i$ 的操作，意义为：如果 $X_{a_i}$ 与 $X_{b_i}$ 的数值关系尚不确定或可以根据前面的关系推导出 $X_{a_i}-X_{b_i}=d_i$ ，则输出 $i$ 且加入这个条件。

由于此题保证 $N\le 2\times 10^5$ ，所以可以使用权值并查集+启发式合并完成此题。

维护一个长度同样为 $N$ 的数组 $V$ ，且每个元素的初始值均为 $0$ 。我们使用这个数组维护**满足目前给出的所有条件的其中一种解**。

具体来说，对于每次形如 $a,b,d$ 的操作，我们首先检查 $x$ 与 $y$ 的数值关系是否确定（即 $a$ 与 $b$ 是否在同一连通块内）。

如果数值关系已经确定，那么我们可以直接检查 $V_{a}-V_{b}=d$ 的正确性，因为我们保证 $V$ 一定满足在这个操作之前所有被加入 $S$ 的操作。

否则，同样因为 $V$ 满足前面给出的所有条件，我们可以直接修改 $a$ 所在的连通块或 $b$ 所在的连通块中的所有 $V$ 值，使其满足 $V_a-V_b=d$ 。

**注意：** 由于直接修改可能会被特殊数据卡到 $O(N^2)$ ，我们需要修改两个连通块中较小的一个。

随后，将 $a$ 与 $b$ 所在连通块合并，并且在 $a$ 与 $b$ 之间连边。连边是为了快速遍历连通块中所有元素。

以下进行两个证明：

1. 最终获得的图一定是一个森林。

由于我们仅在 $a$ 与 $b$ 不在同一个连通块中时连边，所以保证了不管何时同一连通块中的两点均有唯一路径，或每个大小为 $v$ 的连通块内都仅有 $(v-1)$ 条边。

2. 时间复杂度为 $O(Q\log N)$ 。

根据一次操作的性质易得消耗最多操作次数的方式用权值并查集中的连通块大小表示如下：

$$
1,1,1,1,1,1,1,1\\
2,2,2,2\\
4,4\\
8
$$

在此情况下，每**层**合并的平均操作次数约为 $\lfloor\frac{N}{2}\rfloor$ ，且层数为 $\lfloor\log N\rfloor$ ，由于 $N$ 与 $Q$ 同阶，则时间复杂度为 $O(QC\log N)$ ，其中常数 $C=\frac{1}{2}$ 。

---

## 作者：technopolis_2085 (赞：0)

带权并查集。

设 $sum_i$ 表示题目中 $X_i$ 的值，设 $fa_i$ 表示 $i$ 的父节点。

然后对于每一个要求：

如果 $a$ 和 $b$ 不在同一个并查集中，则合并两个并查集然后更新 $sum$ 数组。

否则，当它们在同一并查集中，判断 $sum_a$ 和 $sum_b$ 的差。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=2e5+10;
int fa[maxn];
int sum[maxn];

int find(int x){
	if (fa[x]==x) return fa[x];
	int temp=find(fa[x]);
	sum[x]+=sum[fa[x]];
	fa[x]=temp;
	return fa[x];
} 

signed main(){
	int n,q;
	scanf("%lld%lld",&n,&q);
	
	for (int i=1;i<=n;i++){
		fa[i]=i; sum[i]=0;
	}
	
	for (int i=1;i<=q;i++){
		int a,b,x;
		scanf("%lld%lld%lld",&a,&b,&x);
		if (a==b){
			if (x==0) printf("%lld ",i);
			continue;
		}
		
		if (find(a)!=find(b)){
			int ta=find(a),tb=find(b);
			fa[tb]=ta;
			sum[tb]=x+sum[a]-sum[b];
			printf("%lld ",i);
		}else{
			if (sum[a]+x==sum[b]) printf("%lld ",i);
		}
	}
	return 0;
}
```


---

