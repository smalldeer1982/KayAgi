# 坠梦 | Falling into Dream

## 题目背景

神明愚弄凡间，所谓命运，不过是神明掷出的一颗骰子而已。

花朵等不到的蝴蝶，终究成了一分蹊跷的梦，一轮轮再次重启。

神明的提线木偶一次又一次的被扼住脖颈, 以爱的名义，消逝在时间的花海里。

无数的执念背后，都有一个被扭曲的“真理”。
 
 你所承诺的没有出现，彻夜无眠，或许我只是自作主张的，替你爱了一次人间

“最虔诚者只祝祷，不虔诚者才有所求。”

没有过信仰，因为舍命救了一个人，有幸来到了天堂。
 

## 题目描述

给定一棵 $n$ 个结点的无根树，每条边有非负整数边权。结点由 $1 \sim n$ 编号。

对于每一个点对 $(x, y)$，定义 $(x, y)$ 的距离 $\operatorname{dis}(x, y)$ 为 $x,y$ 两点之间唯一简单路径上边权的异或和。

给定两个结点 $x, y$，定义点 $i$ 的价值 $\operatorname{val}_{x, y}(i)$ 为 $(x, i)$ 与 $(y, i)$ 的距离的异或和，即

$$ \operatorname{val}_{x, y}(i) = \operatorname{dis}(x, i) \oplus \operatorname{dis}(y, i) \textsf{。} $$

现在有 $q$ 次询问，每次询问给出四个整数 $x, y, l, r$，求 $\displaystyle \bigoplus_{i = l}^{r} \operatorname{val}_{x, y}(i)$ 的值，即求

$$ \operatorname{val}_{x, y}(l) \oplus \operatorname{val}_{x, y}(l + 1) \oplus \cdots \oplus \operatorname{val}_{x, y}(r - 1) \oplus \operatorname{val}_{x, y}(r) \textsf{。} $$

上述公式中，$\oplus$ 表示二进制按位异或。

## 说明/提示

**【样例解释】**

![](https://cdn.luogu.com.cn/upload/image_hosting/oew00pa7.png)

输入给出的树如上图所示。对于点对的距离，有

- $\operatorname{dis}(1, 1) = \operatorname{dis}(1, 3) = \operatorname{dis}(2, 2) = \operatorname{dis}(3, 1) = \operatorname{dis}(3, 3) = 0$ 以及
- $\operatorname{dis}(1, 2) = \operatorname{dis}(2, 1) = \operatorname{dis}(2, 3) = \operatorname{dis}(3, 2) = 1$。

第 $1$ 问：$\operatorname{val}_{1, 2}(1) \oplus \operatorname{val}_{1, 2}(2) \oplus \operatorname{val}_{1, 2}(3) = (0 \oplus 1) \oplus (1 \oplus 0) \oplus (0 \oplus 1) = 1 \oplus 1 \oplus 1 = 1$。

第 $2$ 问：$\operatorname{val}_{2, 3}(2) \oplus \operatorname{val}_{2, 3}(3) = (0 \oplus 1) \oplus (1 \oplus 0) = 1 \oplus 1 = 0$。

---

**【数据范围】**

**本题采用捆绑测试。**

| 子任务编号 | $n \le$ | $q \le$ | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| 1 | $100$ | $10$ | 24 |
| 2 | $10^6$ | $10$ | 14 |
| 3 | $100$ | $10^6$ | 14 |
| 4 | $10^6$ | $10^6$ | 48 |

对于 $100\%$ 的数据，保证 $1 \le n, q \le {10}^6$，$1 \le u, v, x, y \le n$，$1 \le l \le r \le n$，$0 \le w < 2^{31}$。

---

**【提示】**

本题最大 I/O 量达到 60 MiB，请注意 I/O 效率。

## 样例 #1

### 输入

```
3 2
1 2 1
2 3 1
1 2 1 3
2 3 2 3
```

### 输出

```
1
0
```

# 题解

## 作者：AC_CSP (赞：9)

有一个显而易见的性质：$\text{dis}(i,j)=\text{dis}(i,k)\oplus \text{dis}(j,k)(i,j,k\in[1,n])$。

下面给出证明：

设 $s$ 为 $i\to k$ 的路径与 $j\to k$ 的路径上第一个重合的点。

$\therefore \text{dis}(i,k)=\text{dis}(i,s)\oplus \text{dis}(s,k),\text{dis}(j,k)=\text{dis}(j,s)\oplus \text{dis}(s,k)$。

$\therefore \text{dis}(i,k)\oplus \text{dis}(j,k)=\text{dis}(i,s)\oplus \text{dis}(s,k)\oplus \text{dis}(j,s)\oplus \text{dis}(s,k)=\text{dis}(i,s)\oplus\text{dis}(j,s)=\text{dis}(i,j)$。

不妨任选一点 $x(1\le x\le n)$ 出发，预处理出所有 $\text{dis}(i,x)(1\le i\le n)$。时间复杂度 $\mathcal{O}(n)$。

现在我们来观察 $\displaystyle\bigoplus\limits_{i=l}^r (\text{dis}(i,x) \oplus \text{dis}(i,y))$。

由上文的性质可得，$\text{dis}(i,x)\oplus\text{dis}(i,y)=\text{dis}(x,y)$。

也就是说，$\displaystyle\bigoplus\limits_{i=l}^r (\text{dis}(i,x) \oplus \text{dis}(i,y))=\displaystyle\bigoplus\limits_{i=l}^r \text{dis}(x,y)$。

又因为 $\text{dis}(x,y)\oplus\text{dis}(x,y)=0$，所以我们讨论 $r-l+1$ 的奇偶性即可。时间复杂度 $\mathcal{O}(q)$。

总时间复杂度 $\mathcal{O}(n+q)$。

### $\text{Code}$：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+7;
struct edge{
	int nxt,v,w;
}e[N<<1];
int h[N],cnt;
inline void add_edge(int u,int v,int w){
	e[++cnt].nxt=h[u],e[cnt].v=v,e[cnt].w=w;
	h[u]=cnt;
}
int n,q;
int x,y,l,r;
int dis[N];
inline int read(){
	int sum=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') sum=(sum<<3)+(sum<<1)+(ch^48),ch=getchar();
	return sum;
}
inline void dfs(int u,int fa){
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].v,w=e[i].w;
		if(v==fa) continue;
		dis[v]=dis[u]^w;
		dfs(v,u);
	}
}
inline void write(int x){
	if(x/10) write(x/10);
	putchar(x%10^48);
}
signed main(){
	//freopen("10.in","r",stdin);
	//freopen("10.out","w",stdout);
	n=read(),q=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		add_edge(u,v,w),add_edge(v,u,w);
	}
	dfs(1,0);
	for(int i=1;i<=q;i++){
		x=read(),y=read(),l=read(),r=read();
		write(r-l+1&1?dis[x]^dis[y]:0),putchar('\n');
	}
	return 0;
}
```


---

## 作者：OIer_Eternity (赞：8)

### 题意简述

- 给定一棵 $n$ 个节点的无根树，边权为非负整数，节点编号 $[1,n]$。
- 对于给定的 $q$ 组询问 $(x,y,l,r)$，求 $\bigoplus_{i=l}^r\Big(dis(x,i)\oplus dis(y,i)\Big)$，其中 $dis(x,y)$ 表示 $x$ 到 $y$ 的唯一简单路径上边的边权异或和。
- $1\le n,q\le10^6$。

### 题目分析

首先考虑如何用 $O(1)$ 的效率求出 $dis(x,y)$，于是我们可以很容易地想到设 $f_i$ 表示节点 $i$ 到根节点的路径上边的边权异或和，则显然 $dis(x,y)=f_x\oplus f_y$。

简单证明一下其正确性：若设 $lca$ 表示 $x$ 与 $y$ 的最近公共祖先，则显然 $dis(x,y)=dis(x,lca)\oplus dis(y,lca)$，那么由于 $a\oplus a=0,a\oplus0=a$，且异或运算满足结合律，则 $dis(x,y)$ 就可以转化为 $f_x\oplus f_{lca}\oplus f_y\oplus f_{lca}$ 即 $dis(x,y)=f_x\oplus f_y$。

则我们只需 $O(n)$ 预处理出 $\{f_n\}$ 即可。

再考虑如何求出答案。
$$
\begin{aligned}
\bigoplus_{i=l}^r\Big(dis(x,i)\oplus dis(y,i)\Big)
&=\bigoplus_{i=l}^r\Big(f_x\oplus f_i\oplus f_y\oplus f_i\Big)\\
&=\bigoplus_{i=l}^r\Big(f_x\oplus f_y\Big)
\end{aligned}
$$
根据异或的性质，若 $r-l+1$ 为偶数，显然答案即为 $0$；否则答案就为 $f_x\oplus f_y$，可以 $O(1)$ 处理每一次询问。

则总效率为 $O(n+q)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,q,head[1000005],ver[2000005],edge[2000005],nxt[2000005],tot,f[1000005];
void add(int u,int v,int w){
    ver[++tot]=v,edge[tot]=w,nxt[tot]=head[u],head[u]=tot;
}
void work(int u,int fa){
    for (int i=head[u];i;i=nxt[i]){
        int v=ver[i],w=edge[i];
        if (v!=fa) f[v]=f[u]^w,work(v,u);
    }
}
int main(){
    scanf("%d%d",&n,&q);
    for (int i=1,u,v,w;i<n;i++) scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
    work(1,0);
    while (q--){
        int x,y,l,r;
        scanf("%d%d%d%d",&x,&y,&l,&r);
        printf("%d\n",(r-l+1)%2==0?0:f[x]^f[y]);
    }
    return 0;
}
```

---

## 作者：aeiouaoeiu (赞：2)

首先我们要知道两个关于按位异或的小结论：$a\oplus b\oplus b=a$ 和 $a\oplus a=0$。

然后我们可以手动模拟一个 $\operatorname{val}_{x,y}(i)$：

![](https://cdn.luogu.com.cn/upload/image_hosting/c7zgmfgy.png)

不难发现，从 $i$ 到 $\operatorname{lca}(x,y)$ 的路径的边权都被异或了两次，说明这段路径上所有的边权都对 $\operatorname{val}_{x,y}(i)$ 没有任何影响，也就是说，我们有：$\operatorname{val}_{x,y}(i)=\operatorname{dis}(x,y)$。（不知道 $\operatorname{lca}$ 是什么可以看[这里](https://oi-wiki.org/graph/lca/)）

接下来问题转化为如何求 $\operatorname{dis}(x,y)$。

我们可以求出一个数组 $f_i$，表示 $\operatorname{dis}(1,i)$，与上面类似，我们可以通过求 $\operatorname{dis}(1,x)\oplus\operatorname{dis}(1,y)=f_x\oplus f_y$ 来得到 $\operatorname{dis}(x,y)$，而 $f$ 数组可以通过一次 dfs 在以 $\mathcal{O}(n)$ 的复杂度内得出。

至于题目要求求出的 $\bigoplus^r_{i=l}\operatorname{val}_{x,y}(i)$ 我们通过上文可以得到它可以转化为 $\bigoplus^r_{i=l}\operatorname{dis}(x,y)$，即 $\bigoplus^r_{i=l}f_x\oplus f_y$，由 $a\oplus a=0$ 可知，该式的结果有两种可能：

- 当 ${r-l+1} \operatorname{mod} 2=0$，即异或了偶数次时，由于每一个 $\operatorname{dis}(x,y)$ 都两两消去，所以答案为 $0$。

- 当 ${r-l+1} \operatorname{mod} 2=1$，即异或了奇数次时，由于仍有一个 $\operatorname{dis}(x,y)$ 未被消去，所以答案为 $f_x\oplus f_y$。

两种情况均可在 $\mathcal{O}(1)$ 时间内求出，总复杂度 $\mathcal{O}(n+q)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2000005;
struct Edge{
	int u,v,w,next;
}edge[maxn];
int n,q,head[maxn],cnt,f[maxn];
void dfs(int u,int fa){
	int v;
	for(int i=head[u];i;i=edge[i].next){
		v=edge[i].v;
		if(v==fa) continue;
		f[v]=f[u]^edge[i].w;
		dfs(v,u);
	}
}
void add(int u,int v,int w){
	edge[++cnt].u=u;
	edge[cnt].v=v;
	edge[cnt].w=w;
	edge[cnt].next=head[u];
	head[u]=cnt;
}
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>q;
	int u,v,w;
	for(int i=1;i<n;i++){
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	dfs(1,0);
	int x,y,l,r;
	while(q--){
		cin>>x>>y>>l>>r;
		if((r-l+1)%2==0) cout<<0<<endl;
		else cout<<(f[x]^f[y])<<endl;
	}
	return 0;
}
```


---

## 作者：aCssen (赞：2)

### Solution
异或运算有以下性质：
+ $a \oplus a=0$。
+ $a \oplus 0=a$

根据异或运算的定义，上述性质显然成立。

本题的求解可以分为三部分。
#### Part 1
求 $\operatorname{dis}(x, y)$。

设 $f_k$ 表示 由点 $1$ 到点 $k$ 的简单路径的异或和，显然该路径唯一。

则 $\operatorname{dis}(x, y)=f_x \oplus f_y$ 。

证明：因为 $a\oplus a=0$，所以 $x$ 和 $y$ 到根的路径的重合部分的异或和都被两两消去变为 $0$，所以剩下的部分就是 $x$ 到 $y$ 之间唯一异或和
#### part 2
求 $\operatorname{val}_{x, y}(i)$。

根据上部分的讨论，将求 $\operatorname{val}_{x, y}(i)$ 的式子拆开，也就是 

$\operatorname{val}_{x, y}(i) = \operatorname{dis}(x, i) \oplus \operatorname{dis}(y, i)$

$=(f_x \oplus f_i) \oplus (f_y \oplus f_i)=f_x \oplus f_i \oplus f_y \oplus f_i=f_x \oplus f_y$。

也就是说，**$\operatorname{val}_{x, y}(i)$ 的取值与 $i$ 无关。**
#### part 3
求 $\displaystyle \bigoplus_{i = l}^{r} \operatorname{val}_{x, y}(i)$ 。

根据上部分的讨论，$\operatorname{val}_{x, y}(i)$ 的取值与 $i$ 无关，所以该式的本质就是求 $(f_x \oplus f_y)$ 自我异或 $r-l+1$ 次的结果。 

因为 $a \oplus a=0$，所以如果 $r-l+1$ 是偶数，则该式的值为 $0$，否则，因为 $a \oplus 0=a$，答案就是 $\operatorname{val}_{x, y}(i)$ 也就是 $f_x \oplus f_y$。

#### 总结
综上，我们只需要对整棵树做一次 dfs，求出每个点的 $f$ 值，对于询问，判断 $r-l+1$ 的奇偶性，若果是奇数输出 $f_x \oplus f_y$，否则输出 $0$ 即可,时间复杂度 $\mathcal{O}(n+q)$

### 实现细节

+ 因为是无根树，所以选哪个点当根 dfs 都可以
+ 也因为是无根树，所以要建双向边，前向星数组要开 $2$ 倍。
+ 因为是无根树树，所以只需要标记当前节点的父亲就可以，没必要再开一个 `vis` 数组。
+ 询问的输入顺序为 $x,y,l,r$。

### 代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=1e6+5;
int head[maxn],edge[maxn<<1],ver[maxn<<1],nxt[maxn<<1],dis[maxn],tot,n,q;
void add_edge(int u,int v,int w){
    edge[++tot]=v;
    ver[tot]=w;
    nxt[tot]=head[u];
    head[u]=tot;
}
void dfs(int x,int fa){
    for(int i=head[x];i;i=nxt[i]){
        int y=edge[i],z=ver[i];
        if(y==fa) continue;
        dis[y]=dis[x]^z;
        dfs(y,x);
    }
}
inline int read(){
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return x;
}
int main(){
    n=read(),q=read();
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    dfs(1,1);
    while(q--){
        int l,r,x,y;
        x=read(),y=read(),l=read(),r=read();
        int len=r-l+1;
        if(len&1) printf("%d\n",dis[x]^dis[y]);
        else printf("0\n");
    }
    return 0;
}
```


---

## 作者：WsW_ (赞：1)

很常见的一个 trick。  
[P2420 让我们异或吧](https://www.luogu.com.cn/problem/P2420)  
[P8200 [传智杯 #4 决赛] 生活在树上](https://www.luogu.com.cn/problem/P8200)

---
### 思路
随便找个节点当做根，以下将结点 $1$ 当做根。  

由于异或满足交换律和结合律，所以  
$$\operatorname{dis}(x,y)=\operatorname{dis}(x,\operatorname{lca}(x,y))\oplus\operatorname{dis}(\operatorname{lca}(x,y),y)$$  

由于同一个数异或两遍，相当于没有进行任何操作，所以  
$$\operatorname{dis}(x,y)=\operatorname{dis}(x,\operatorname{lca}(x,y))\oplus\operatorname{dis}(\operatorname{lca}(x,y),y)\oplus\operatorname{dis}(\operatorname{lca}(x,y),1)\oplus\operatorname{dis}(\operatorname{lca}(x,y),1)$$  

再用交换律和结合律把后面两个相同的分别和前面两个结合起来，得到
$$\operatorname{dis}(x,y)=\operatorname{dis}(x,1)\oplus\operatorname{dis}(y,1)$$  

同理可得
$$\operatorname{dis}(x,y)=\operatorname{dis}(x,i)\oplus\operatorname{dis}(y,i)$$  

简单来说，就是
$$\forall i,\operatorname{val}_{x,y}(i)=\operatorname{dis}(x,y)$$

所以要求的结果就是 $r-l+1$ 个 $\operatorname{dis}(x,y)$ 异或在一起。  
还是由于同一个数异或两遍，相当于没有进行任何操作，所以当 $r-l+1$ 为奇数的时候，结果就是 $\operatorname{dis}(x,y)$；否则结果为 $0$。  

开始一个 dfs 预处理所有的 $\operatorname{dis}(1,i)$ 即可。  

时间复杂度 $O(n+q)$。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int to,w;
};
int n,q;
int u,v,w;
int x,y,l,r;
vector<node>edg[1000003];
int dis[1000003];//dis[i]表示1~i路径上的异或积
bool vis[1000003];

void dfs(int p){
	vis[p]=1;
	for(int i=0;i<edg[p].size();i++){
		int to=edg[p][i].to;
		if(!vis[to]){
			dis[to]=dis[p]^edg[p][i].w;
			dfs(to);
		}
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n-1;i++){
		cin>>u>>v>>w;
		edg[u].push_back({v,w});
		edg[v].push_back({u,w});
	}
	dfs(1);
	
	while(q--){
		cin>>x>>y>>l>>r;
		if((r-l+1)&1)cout<<(dis[x]^dis[y])<<'\n';
		else cout<<"0\n";
	}
	
	return 0;
}
```

---
### 评分
典得不能再典。最后面的式子有点思考，所以给 $4$ 分。

---

## 作者：mc123456 (赞：1)

## 分析

异或有一个很优美的性质，就是 $x \oplus x = 0$。

所以对于树上任意一条简单路径的异或和，其等于树上任意一个点到该路径两端点异或距离之和。

所以对于任意 $x, y, l, r$ 可以化简所求式子：

$$
\bigoplus_{i = l}^{r}{\mathrm{val}_{x, y}(i)} = \bigoplus_{i = l}^{r}{\mathrm{dis}(x, y)}
$$

又由于异或的性质，可以再对式子化简：

$$
\bigoplus_{i = l}^{r}{\mathrm{dis}(x, y)} = ((r - l + 1) \bmod 2) \cdot \mathrm{dis}(x, y)
$$

再由异或的性质：

$$
((r - l + 1) \bmod 2) \cdot \mathrm{dis}(x, y) = ((r - l + 1) \bmod 2) \cdot (\mathrm{dis}(1, x) \oplus \mathrm{dis}(1, y))
$$

所以我们只要求出 $1$ 节点到所有节点的异或距离即可，每次询问答案就是 $((r - l + 1) \bmod 2) \cdot (\mathrm{dis}(1, x) \oplus \mathrm{dis}(1, y))$。

时间复杂度 $O(n + q)$。

## 代码

不卡常，直接用 `vector` 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 1e6 + 10;

int n, q;
vector<pair<int, int>> g[N];
int dis[N];

void dfs(int x, int f)
{
    for (auto pr : g[x])
    {
        int y = pr.first, w = pr.second;
        if (y == f)
            continue;
        dis[y] = dis[x] ^ w;
        dfs(y, x);
    }
}

signed main()
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
    cin >> n >> q;
    for (int i = 1, u, v, w; i < n; i++)
        cin >> u >> v >> w, g[u].push_back({v, w}), g[v].push_back({u, w});
    dfs(1, 0);
    while (q--)
    {
        int x, y, l, r;
        cin >> x >> y >> l >> r;
        cout << ((r - l + 1) & 1) * (dis[x] ^ dis[y]) << endl;
    }
}
```

---

## 作者：Binaerbaka (赞：0)

## 题目
对于一个无根树，求出对于 $(x,y)$ 点对，$l$ 到 $r$ 的权值异或和。

## 分析

一眼考虑最近公共祖先，但是在手玩数据之后可以发现。

- 对于每对 $(x,y)$ 结点的其中的异或和相当于两点到最近公共祖先的异或和。

- 由于异或的特殊性，自身与自身操作等于零，所以当路径上的长度为偶数时异或和等于零。

## 过程

先建树，之后对树预处理出来当前结点边权对父亲结点的异或值。

最后判断 $l-r+1$ 是否是偶数，是的话就为零，不是的话直接输出两点异或值相异或的结果即可。

## STD
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e7+5;
int head[maxn],to[maxn],nt[maxn],w[maxn],tot;
int n,q;
int f[maxn];
void add(int x,int y,int z){
	to[++tot]=y;
	w[tot]=z;
	nt[tot]=head[x];
	head[x]=tot;
}
void dfs(int x,int fa){
	for(int i=head[x];i;i=nt[i]){
		int u=to[i];
		if(u==fa)continue;
		f[u]=f[x]^w[i];
		dfs(u,x);
	}
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<n;i++){
		int x,y,z;
		cin>>x>>y>>z;
		add(x,y,z);
		add(y,x,z);
	}
	dfs(1,0);
	while(q--){
		int x,y,l,r;
		cin>>x>>y>>l>>r;
		cout<<((r-l+1)&1?f[x]^f[y]:0)<<"\n";
	}
	return 0;
} 
```




---

## 作者：ncwzdlsd (赞：0)

预处理每个点到根节点的路径异或和 $s_i$。有 $\text{dis}(x,y)=\text{dis}(x,\text{LCA})\oplus\text{dis}(\text{LCA},y)$，由于从 LCA 到根节点的路径是重合的，异或和为 $0$ 不影响答案，所以有 $\text{dis}(x,y)=s_x\oplus s_y$。

于是有 $\text{val}_{x,y}(i)=\text{dis}(x,i)\oplus\text{dis}(y,i)=s_x\oplus s_i\oplus s_i\oplus s_y=s_x\oplus s_y$。

要求 $\bigoplus_{i=l}^r\text{val}_{x,y}(i)=\bigoplus_{i=l}^r(s_x\oplus s_y)$，该式的答案与 $r-l+1$ 的奇偶性有关，若为偶数，则异或和为 $0$；否则为 $s_x\oplus s_y$。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=1e6+5;
int head[maxn],cnt,s[maxn];
struct edge{int to,nxt,w;}e[maxn*2];

void add(int x,int y,int z){e[++cnt]={y,head[x],z},head[x]=cnt;}

void dfs(int x,int fa)
{
    for(int i=head[x];i;i=e[i].nxt)
    {
        if(e[i].to==fa) continue;
        s[e[i].to]=s[x]^e[i].w;
        dfs(e[i].to,x);
    }
}

int main()
{
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n,q;cin>>n>>q;
    for(int i=1,u,v,w;i<n;i++) cin>>u>>v>>w,add(u,v,w),add(v,u,w);
    dfs(1,0);
    while(q--)
    {
        int x,y,l,r;cin>>x>>y>>l>>r;
        if((r-l+1)%2) cout<<(s[x]^s[y])<<'\n';
        else cout<<"0\n";
    }   
    return 0;
}
```

---

## 作者：qzhwlzy (赞：0)

### 题目大意

给定一棵 $n$ 个节点的树，边有边权。定义 $\operatorname{dis}(x,y)$ 为节点 $x$ 和节点 $y$ 间简单路径的边权异或和。

$q$ 次询问，每次给定 $x,y,l,r$，求 $\bigoplus\limits_{i=l}^r(\operatorname{dis}(x,i)\oplus\operatorname{dis}(y,i))$ 的值。

### 思路

解决这题有一个至关重要的结论：

$$
\operatorname{dis}(x,i)\oplus\operatorname{dis}(y,i) = \operatorname{dis}(x,y)
$$

证明如下：

由于异或有 $x\oplus x = 0$ 的性质，那么 $(x,i)$ 和 $(y,i)$ 路径上重复的边可以删掉。那么，我们可以分类讨论：分别假设 $i$ 在 $x$ 的子树里、$y$ 的子树里、其余位置，如下图都可以发现有上述结论。

![](https://cdn.luogu.com.cn/upload/image_hosting/w9nfvvqs.png)

---

于是这题要求的式子就可以看作是 $\bigoplus\limits_{i=l}^r \operatorname{dis}(x,y)$，而由于 $x\oplus x = 0$ 的性质，这个式子在 $r-l+1$ 是偶数的时候恒为 $0$，在 $r-l+1$ 是奇数时为 $\operatorname{dis}(x,y)$。

考虑如何求 $\operatorname{dis}(x,y)$。根据上面的结论，有 $\operatorname{dis}(x,y) = \operatorname{dis}(1,x)\oplus \operatorname{dis}(1,y)$。则我们可以预处理出所有 $d_i = \operatorname{dis}(1,i)$ 即可。预处理使用一遍 DFS 即可。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#define maxn 1000005
using namespace std;
int n,q,u,v,w,x,y,l,r,d[maxn]; struct edge{int to,nex,dis;}g[maxn*2]; int head[maxn],cnt=0;
void add(int from,int to,int dis){g[++cnt]=(edge){to,head[from],dis}; head[from]=cnt;}
void dfs(int p,int fa)
	{ for(int i=head[p];i;i=g[i].nex) if(g[i].to!=fa) d[g[i].to]=d[p]^g[i].dis,dfs(g[i].to,p); }
int main(){
	scanf("%d%d",&n,&q); for(int i=1;i<n;i++) scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
	dfs(1,0); while(q--){
		scanf("%d%d%d%d",&x,&y,&l,&r);
		printf("%d\n",((r-l+1)%2)*(d[x]^d[y]));
	} return 0;
}
```

---

## 作者：xhabc66 (赞：0)

# 思路
先证明一个引理：$ \operatorname{val}_{x, y}(i) = \operatorname{dis}(x, y) (x,y,i∈[1,n])$。

给出证明：
- 若 $i$ 在 $x,y$ 的简单路径上，引理显然成立。
- 若 $i$ **不在** $x,y$ 的简单路径上：

设 $ \operatorname{lca}_{k}(x,y)$ 为**以 $k$ 为根**时 $x,y$ 的 LCA（即最近公共祖先），则
$$ \operatorname{val}_{x, y}(i) =\operatorname{dis}(x, i) \oplus \operatorname{dis}(y, i)$$
$$\operatorname{dis}(x, i) \oplus \operatorname{dis}(y, i)=\operatorname{dis}(x, \operatorname{lca}_{k}(x,y)) \oplus \operatorname{dis}(y, \operatorname{lca}_{k}(x,y))\oplus\operatorname{dis}(\operatorname{lca}_{k}(x,y), i) \oplus \operatorname{dis}(\operatorname{lca}_{k}(x,y), i)$$
（为避免 $\LaTeX$ 太长只能这样了）

由于 $ \operatorname{lca}_{k}(x,y)$ 肯定在 $x,y$ 的简单路径上，且 $x\oplus x=0$，所以
$$\operatorname{dis}(x, \operatorname{lca}_{k}(x,y)) \oplus \operatorname{dis}(y, \operatorname{lca}_{k}(x,y))\oplus\operatorname{dis}(\operatorname{lca}_{k}(x,y), i) \oplus \operatorname{dis}(\operatorname{lca}_{k}(x,y), i)=\operatorname{dis}(x,y)$$
（为避免 $\LaTeX$ 太长只能这样了）

引理得证。

根据这个引理，则 
$$\displaystyle \bigoplus_{i = l}^{r} \operatorname{val}_{x, y}(i)=\displaystyle \bigoplus_{i = l}^{r} \operatorname{dis}(x,y)=\displaystyle \bigoplus_{i = l}^{r} \operatorname{dis}(1,x)+\operatorname{dis}(1,y)$$
那么只需要预处理 $\operatorname{dis}(1,i)$ 即可，每组询问再判断 $r-l+1$ 奇偶即可。时间复杂度 $O(n+q)$。
# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;

vector<pair<int,int> > bian[1000000+10];
int dis[1000000+10];

void dfs(int s,int fa,int w)//求dis(1,i)
{
	dis[s]=w;
	for(auto v:bian[s])
	{
		if(v.first!=fa)dfs(v.first,s,w^v.second);
	}
}

int main()
{ios::sync_with_stdio(0);
	int n,q;
	cin>>n>>q;
	for(int i=1;i<n;i++)
	{
		int s,t,w;
		cin>>s>>t>>w;
		bian[s].push_back(make_pair(t,w));
		bian[t].push_back(make_pair(s,w));
	}
	dfs(1,0,0);
	int s,t,l,r;
	while(q--)
	{
		cin>>s>>t>>l>>r;
		if((r-l)&1)cout<<"0\n";
		else cout<<(dis[s]^dis[t])<<endl;
	}
}
```

---

## 作者：Convergent_Series (赞：0)

证明： $\operatorname{dis}(x, i) \oplus \operatorname{dis}(y, i)=\operatorname{dis}(x, y)$ 。

设 $k\to i$ 为 $x\to i$ 和 $y\to i$ 两条路径的重合部分：

$\begin{aligned}
\operatorname{dis}(x, i) \oplus \operatorname{dis}(y, i)&=\operatorname{dis}(x, k)\oplus\operatorname{dis}(k,i)\oplus\operatorname{dis}(y,k)\oplus\operatorname{dis}(k,i)\\
&=\operatorname{dis}(x, k) \oplus \operatorname{dis}(y, k)\\
&=\operatorname{dis}(x, y)\\
\end{aligned}$

---

化简所求式子：

$\begin{aligned}
\displaystyle \bigoplus_{i = l}^{r} \operatorname{val}_{x, y}(i)&=\displaystyle \bigoplus_{i = l}^{r} \operatorname{dis}(x, i) \oplus \operatorname{dis}(y, i) \\
&=\displaystyle \bigoplus_{i = l}^{r} \operatorname{dis}(x, y)
\end{aligned}$

当 $r-l+1\equiv0(\bmod 2)$ 时 ， 由于 $\operatorname{dis}(x, y)\oplus\operatorname{dis}(x, y)=0$ ，所以 $\displaystyle \bigoplus_{i = l}^{r} \operatorname{dis}(x, y)=0$ 。

当 $r-l+1\equiv1(\bmod 2)$ 时， 

$\begin{aligned}
\displaystyle \bigoplus_{i = l}^{r} \operatorname{dis}(x, y)&=\displaystyle \bigoplus_{i = l}^{r-1} \operatorname{dis}(x, y)\oplus\operatorname{dis}(x, y)\\
&=0\oplus \operatorname{dis}(x,y)\\
&=\operatorname{dis}(x, y)\\
&=\operatorname{dis}(x, 1)\oplus\operatorname{dis}(y,1)\\
\end{aligned}$

使用 dfs 预处理出每个点与点 $1$ 的距离，询问时调取即可。

代码：
```cpp
#include<bits/stdc++.h> 
using namespace std;
int read(){
	int a=0,f=1;char ch;ch=getchar();
	while(!((ch>='0'&&ch<='9')||ch=='-')) ch=getchar();
	if(ch=='-') f=-1,ch=getchar();
	while(ch>='0'&&ch<='9') a=(a<<3)+(a<<1)+ch-'0',ch=getchar();
	a*=f;return a;
} 
void write(int a){
	int num[100]={0},top=0;
	if(a<0) putchar('-'),a=-a;
	if(a==0){ putchar('0');return;}
	while(a) num[++top]=a%10,a/=10;
	while(top) putchar(num[top--]+'0');
}
//快读快写
struct edge{int to,ne,w;}e[2000010];
int cnt=0,fi[1000010],dis[1000010];
//使用链式前向星存储
int n,q;
void add(int u,int v,int z){
	cnt++;
	e[cnt].to=v;e[cnt].ne=fi[u];
	fi[u]=cnt;e[cnt].w=z;
}//连边
void dfs(int x,int fa){
	int i;
	for(i=fi[x];i;i=e[i].ne){
		if(e[i].to==fa) continue;//跳过父结点
		dis[e[i].to]=dis[x]^e[i].w;//计算距离
		dfs(e[i].to,x);
	}
} 
int main(){
	int i,tu,tv,tw,x,y,l,r,ans;
	n=read();q=read();
	for(i=1;i<n;i++){
		tu=read();tv=read();tw=read();
		add(tu,tv,tw);add(tv,tu,tw);
     		//无根树，连双向边
	}
	dfs(1,0);//预处理
	for(i=1;i<=q;i++){
		x=read();y=read();l=read();r=read();
		if((r-l+1)&1) ans=dis[x]^dis[y];
		else ans=0;
     		//判断奇偶
		write(ans);putchar('\n');
	}
	return 0;
} 
```

---

## 作者：Zi_Gao (赞：0)



## 0x00 $\mathcal{O}(n^3)$ 预处理 $\mathcal{O}(n)$ 查询

这种大量查询的题目很容易想到的是预处理出来每一对 $\operatorname{dis}(x, y)$ 。这样在查询的时候就可以 $O(n)$ 查询出来，并且求出答案。具体实现可以这样做：由于“ $\operatorname{dis}(x, y)$ 为 $x,y$ 两点之间唯一简单路径上边权的异或和。”很显然的是，对这个无根树选定一个根节点，这条简单路径还是原来的简单路径，那么 $O(1)$ 求出 $x,y$ 的 lca 节点，暴力跑一遍路径进行计算即可。

## 0x01 $\mathcal{O}(n^2)$ 预处理 $\mathcal{O}(n)$ 查询

对于 0x00 部分的算法，可以进行优化，首先预处理把每一个对 $\operatorname{dis}(x, y)$ 时间复杂度不会变化，那么 $\mathcal{O}(1)$ 求出 $x,y$ 的 lca 节点后，希望可以 $\mathcal{O}(1)$ 求出 $\operatorname{dis}(x, y)$ ，考虑这里 $\operatorname{dis}(x, y)$ 若不是“路径上边权的异或和”而是“路径上边权的和”，可以使用树上前缀和，那么异或和也可以采用这样的方法，处理出每一个节点到根节点的异或和，参见下面一个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/5s0q5m5u.png)

对于 $\operatorname{dis}(4, 5)$ 已知  $\operatorname{dis}(1, 4) = 1 \oplus 3$ 和 $\operatorname{dis}(1, 5) = 1 \oplus 4$ 这两个信息重复的部分即为 $\operatorname{dis}(1, 2) = 1$ ，但是由于异或的自反性质，直接讲这两部分异或起来就去除了 $\operatorname{dis}(1, 2) = 1$ 这部分，即为 $\operatorname{dis}(1, 5) \oplus \operatorname{dis}(1, 2) = 3 \oplus 4 \oplus 1 \oplus 1 = 3 \oplus 4$ 。那么就可以做到 “$\mathcal{O}(n^2)$ 预处理 $\mathcal{O}(n)$ 查询” 。

## 0x02 $\mathcal{O}(n)$ 预处理 $\mathcal{O}(1)$ 查询

刚才的算法打开了一个很好的思路就是利用了异或的自反性，希望还可以利用更多这样的性质，这时整体考虑

$$
\operatorname{val}_{x, y}(i) = \operatorname{dis}(x, i) \oplus \operatorname{dis}(y, i)\\ = \operatorname{dis}(x, 1) \oplus \operatorname{dis}(i, 1) \oplus \operatorname{dis}(y, 1) \oplus \operatorname{dis}(i, 1) \\ = \operatorname{dis}(x, 1) \oplus \operatorname{dis}(y, 1)
$$

可以发现 $ \operatorname{val}_{x, y}(i) $ 和 $i$ 没关系，那么对于 $\displaystyle \bigoplus_{i = l}^{r} \operatorname{val}_{x, y}(i)$ 也就是 $\displaystyle \bigoplus_{i = l}^{r} \operatorname{dis}(x, 1) \oplus \operatorname{dis}(y, 1) $ ，相当于自己和自己异或了 $r-l+1$ 次，更具自反性质得到 $r-l+1\bmod 2 = 1$ 时为 $\operatorname{dis}(x, 1) \oplus \operatorname{dis}(y, 1) $ ，否则为 $0$ 。


```cpp
#include <cstdio>
#include <algorithm>
#include <queue>
#define _min(a,b) ((a)<(b)?(a):(b))
#define _max(a,b) ((a)>(b)?(a):(b))
struct edge{
	int to,nxt,w;
	edge(){
		nxt=-1;
		return;
	} 
}tree[1000010<<1];
int tot,head[1000010];
long long V_pre[1000010];

void addEdge(int u,int v,int w){
	tree[tot].nxt=head[u];
    tree[tot].w=w;
	tree[tot].to=v;
	head[u]=tot;
	++tot;
	return;
}

int read(){
	long long x=0;char f=0,c=getchar();
	while(c<'0'||'9'<c) f|=(c=='-'),c=getchar();
	while('0'<=c&&c<='9') x=(x<<1)+(x<<3)+(c&15),c=getchar();
	return f?-x:x; 
}

void dfs(int u,int p,int w){
	V_pre[u]=V_pre[p]^w;
	for(int i=head[u];~i;i=tree[i].nxt){
		if(tree[i].to!=p)
			dfs(tree[i].to,u,tree[i].w);
	}
}

int main(){
	register int i,u,v,w,x,y,l,r;
    register long long ans;
	int n=read();
	int Q=read();

    for(i=1;i<=n;++i) head[i]=-1;

	for(i=1;i<n;++i){
		u=read();
		v=read();
        w=read();
		addEdge(u,v,w);
		addEdge(v,u,w);
	}

	dfs(1,1,0);

	for(i=0;i<Q;++i){
		x=read();
        y=read();
        l=read();
        r=read();
        ans=(((r-l+1)&1)?(V_pre[x]^V_pre[y]):0);
        printf("%lld",ans);
        putchar('\n');
	}

	return 0;
}
```

---

## 作者：LCat90 (赞：0)

根据树上差分，定义 $d_i$ 表示 $i$ 到根节点的距离异或和，则 $x$ 到 $y$ 的距离异或和为 $d_x ⨁ d_y$。

所以 $\text{val}_{x,y}(i)=(d_x ⨁ d_i)⨁(d_y ⨁ d_i)$

于是，首先我们可以用 $O(n)$ 搜索搞到数组 $d$。

---------

### $O(n^3+q)$

设 $a_{x,y,i}$ 表示 $⨁_{j=1}^i \text{val}_{x,y}(j)$。

先确定 $x$ 和 $y$，再从 $1$ 到 $n$ 枚举 $i$，根据前缀的性质可得 $a_{x,y,i}=a_{x,y,i-1}⨁\text{val}_{x,y}(i)$。

预处理出 $a$，时空均为 $O(n^3)$。

对于查询，根据容斥可推出答案为 $a_{x,y,r} ⨁ a_{x,y,l-1}$，所以查询是 $O(1)$ 的。

总共 $O(n^3+q)$。

-----------

### $O(nq)$

上个算法的思路是预处理出答案，此做法则是直接暴力。

对于每次查询，在 $[l,r]$ 中枚举，按照题意将答案算出来。

------------

### $O(n+q)$

我们回到最初的式子：

$$\text{val}_{x,y}(i)=(d_x ⨁ d_i)⨁(d_y ⨁ d_i)$$

$$\therefore\text{val}_{x,y}(i)=d_x ⨁d_y⨁ d_i ⨁ d_i$$

根据异或的性质：$a ⨁ a = 0$，可得：

$$\therefore\text{val}_{x,y}(i)=d_x ⨁d_y$$

惊喜地发现，答案与 $i$ 没有任何关系！

于是答案变成了：

$$⨁_{i=1}^{r-l+1}(d_x⨁d_y)$$

$$=⨁_{i=1}^{r-l+1}d_x ⨁_{i=1}^{r-l+1}d_y$$

即，同一个数异或多次得到的答案。

有如下性质：

+ 数 $a$ 自己异或自己**偶数次**，答案为 $0$。
+ 数 $a$ 自己异或自己**奇数次**，答案为 $a$。

所以查询就可以 $O(1)$ 勒！我们只需要判断 $r-l+1$ 的奇偶即可，若为偶，答案为 $0$；若为奇，答案为 $d_x⨁d_y$。

加上预处理时间为 $O(n+q)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 5;
int n, q, d[N];
struct node {
	int id, w;
};
vector <node> G[N];
void dfs(int x, int fa) { 
	for(int i = 0;i < G[x].size(); ++i) {
		int to = G[x][i].id;
		if(fa == to) continue;
		d[to] = d[x] ^ G[x][i].w;
		dfs(to, x);
	}
}
int main() {
	cin >> n >> q;
	for(int i = 1, a, b, c;i < n; ++i) {
		scanf("%d %d %d", &a, &b, &c);
		G[a].push_back((node){b, c});
		G[b].push_back((node){a, c});
	} 
	dfs(1, 0);
	while(q--) {
		int x, y, l, r;
		scanf("%d %d %d %d", &x, &y, &l, &r);
		if((r - l + 1) & 1) printf("%d\n", d[x] ^ d[y]);
		else puts("0");
	}
	return 0;
}
```

---

