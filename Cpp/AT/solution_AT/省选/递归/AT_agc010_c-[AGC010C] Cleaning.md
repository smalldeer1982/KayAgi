# [AGC010C] Cleaning

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc010/tasks/agc010_c

$ N $ 頂点からなる木があり、頂点には $ 1 $ から $ N $ の番号がついています。 また、$ N-1 $ 本の辺の内、$ i $ 番目の辺は頂点 $ a_i $ と頂点 $ b_i $ を結んでいます。

今、各頂点 $ i $ には $ A_i $ 個の石が置いてあります。 以下の操作を繰り返して、全ての石を取り除くことができるか判定してください。

- 相異なる $ 2 $ つの葉を一組選ぶ。そして、その $ 2 $ 頂点間のパス上にある頂点全てからちょうど $ 1 $ つ石を取り除く。  
   ただし、葉とは木の頂点で次数が $ 1 $ の頂点を指し、選んだ葉自体もパス上の頂点として考える。

石が置かれていない頂点がパス上にあるときは、その操作を行えないことに注意してください。

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 10^5 $
- $ 1\ ≦\ a_i,b_i\ ≦\ N $
- $ 0\ ≦\ A_i\ ≦\ 10^9 $
- 与えられるグラフは木である。

### Sample Explanation 1

以下のようにすれば、すべての石を取り除くことができます。 - 葉として $ 4 $ と $ 5 $ を選ぶ。このとき、$ 4 $ 以外の頂点に石が $ 1 $ 個残る。 - 葉として $ 1 $ と $ 5 $ を選ぶ。このとき、全ての頂点から石がなくなる。

## 样例 #1

### 输入

```
5
1 2 1 1 2
2 4
5 2
3 2
1 3```

### 输出

```
YES```

## 样例 #2

### 输入

```
3
1 2 1
1 2
2 3```

### 输出

```
NO```

## 样例 #3

### 输入

```
6
3 2 2 2 2 2
1 2
2 3
1 4
1 5
4 6```

### 输出

```
YES```

# 题解

## 作者：zhylj (赞：20)

![p3.png](https://i.loli.net/2020/04/07/eLTF543ywQcNgdx.png)

选取一个度数大于 $1$ 的点为根（当然 $n=2$ 的时候要特判一下），设 $f_u$ 代表从某个点可以向上拓展的路径数量（显然叶子节点的 $f_u$ 都为 $a_u$），设 $s_u = \sum_{v\in u.{\operatorname {son}}} f_v$，也就是从孩子能拓展上来的路径条数。

这些路径有两种情况：1. 合并成一个点；2. 继续往上拓展。

后者的数量显然为 $f_u$，前者的数量为 $\dfrac {s_u-f_u}2$ （每两条合并成一个）。

前者每两条可以清除一个石头，后者每一条可以清除一个石头，所以有：

$$a_u = \frac {s_u-f_u}{2}+f_u = \frac {s_u + f_u}{2}$$

就有：

$$f_u = 2a_u - s_u$$

可以发现这些都是定值，所以直接 DFS 一遍，判断每个 $f_u$ 是否有 $0\le f_u \le a_u$，$\max f_v$ 是否小于等于 $a_u$ 即可。至于“$\max f_v \le a_u$ ”这个条件是怎么来的，类似于[这样一个问题](http://zhylj.cc/2020/04/07/47/#more)：

> 有一个长度为 $n$ 的正整数数列 $a$，每次取两个数 $-1$，试构造一个方案使得整个数列为 $0$ 或说明不可行。
>
> **结论**
>
> $\sum a_i$ 为偶数且最大的数小于等于 $\sum a_i$ 的一半就行，方法是每次取出两个最大的数 $-1$，再放回。
>
> **证明**
>
> 必要性显然。
>
> 充分性证明：
>
> - $n=2$ 的时候显然成立。
> - $n > 2$ 的时候，不断进行操作，直到出现第一个 $0$ 为止，由于最大的数不超过总和的一半，此情况必然出现。由于 $n - 1$ 的情况成立，所以 $n$ 的时候成立，证毕。

不过需要注意的是，这两个问题的不同之处在于这个问题的“总和”会减去 $f_u$，即有：

$$\max f_v \le \frac{s_u - f_u}2 = \frac{s_u-(s_u - 2a_u)}2 = a_u$$

就是上面所说的条件。

---

## 作者：litble (赞：5)

[戳我＝￣ω￣＝](https://blog.csdn.net/litble/article/details/83183748)

这个里面的花，我们在所有的叶子节点$i$中放$a_i$个小精灵。每一次所有小精灵都会往父亲飞，当一群小精灵聚集在$x$这个节点时，从不同儿子节点飞上来的小精灵可以选择组成一对“好朋友”，并且以后不再往父亲走。接着小精灵们会开始捡石头，一对“好朋友”只会捡走一个石头，单身的小精灵每人捡走一个石头，石头必须被捡完，所以组成多少对朋友就是固定的。然后没有找到朋友的小精灵会继续往父亲节点飞。问是否所有小精灵都能找到朋友并且所有石头都要被捡完。

那么会前文已说，从每个节点继续往上飞的小精灵数是固定的，所以每个节点处组成朋友的小精灵对数也是固定的，重点在求出最多可以组成多少对朋友，判断能不能达成石头恰好被捡完这个目标。

那么这个找朋友的过程怎么进行呢？我们让从同一个儿子节点飞上来的小精灵暂时站在一艘船上，由于只有不同船上的小精灵可以组队，所以有精灵的船越多越有利。所以我们每次选择两艘小精灵数最多的船，让它们上面各一个小精灵组成一对，然后她们两个下船，以此类推。

于是我们发现最多能组的队数只有两种情况，一种是有一艘船上的小精灵特别多，多到别的船都空了这艘船上还有很多小精灵单身。一种是我们这么操作着操作着所有船上的小精灵数越来越多接近，最后几乎所有的小精灵都有了朋友，但是如果总精灵数是奇数，那必然有一个小精灵找不到朋友。

最多组的队数与想要石头恰好被捡完应该组的队数比较即可判断。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define RI register int
int read() {
	int q=0;char ch=' ';
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') q=q*10+ch-'0',ch=getchar();
	return q;
}
typedef long long LL;
const int N=100005;
int n,tot,h[N],ne[N<<1],to[N<<1],du[N];
LL a[N],f[N];
void add(int x,int y) {to[++tot]=y,ne[tot]=h[x],h[x]=tot;}
void dfs(int x,int las) {
	if(du[x]==1) {f[x]=a[x];return;}
	LL orzabs=0,p,mx=0;
	for(RI i=h[x];i;i=ne[i]) {
		if(to[i]==las) continue;
		dfs(to[i],x),f[x]+=f[to[i]],mx=max(mx,f[to[i]]);
	}
	if(mx>f[x]-mx) p=f[x]-mx;
	else p=f[x]/2;
	if(f[x]<a[x]) {puts("NO");exit(0);}
	if(f[x]-a[x]>p) {puts("NO");exit(0);}
	f[x]-=(f[x]-a[x])*2LL;
}
int main()
{
	int x,y;
	n=read();
	for(RI i=1;i<=n;++i) a[i]=read();
	if(n==2) {
		if(a[1]==a[2]) puts("YES");
		else puts("NO");
		return 0;
	}
	for(RI i=1;i<n;++i)
		x=read(),y=read(),add(x,y),add(y,x),++du[x],++du[y];
	for(RI i=1;i<=n;++i) if(du[i]>1) {
		dfs(i,0);
		if(f[i]) puts("NO");
		else puts("YES");
		return 0;
	}
	return 0;
}
```

---

## 作者：Infiltrator (赞：4)

[$\Large\color{#FFBBFF}\textit{Tian-Xing's blog}$](https://Tian-Xing.github.io)

------------

# Description

[传送门](https://atcoder.jp/contests/agc010/tasks/agc010_c)

------------

# Solution

考虑对于每个点处理它的所有儿子，它的所有儿子连上来的路径要不就是在当前子树内两两匹配，要不就是继续连到该点的父亲。

如果在子树内匹配，儿子两个儿子的石子数量减一，该节点的石子数量减一；对于连上去的，某个儿子的石子数量减一，该节点的石子数量减一。

所以设某节点处理完子树之后还要往父亲连$f_x$条路径，有$y$条路径在它的子树内互相匹配，它的子树内一共有$sum$条路径，它本身权值为$a_x$，那么有

$$y \times 2 + f_x = sum$$

$$y + f_x = a_x$$

解得

$$ y = sum - a_x, f_x = sum - 2 \times y$$

首先连上去的路径个数肯定不能超过它本身的权值$a_x$，即$f_x <= a_x$；也不能是负数，即$f_x >= 0$。

其次它的子树内部最多的两两互相匹配的路径个数要比需要的两两匹配的路径条数多，而这个最大值就是$max(\frac{sum}{2}, sum - max_{f_v})$，首先两两匹配最多就是$\frac{sum}{2}$，其次每个点不能和自己匹配所以还要和$sum - max_{f_v}$取较小值。

注意$f_{root}$必须是零，因为根节点不能向上再传递了。

注意到$n = 2$两个点都是叶子节点要特判。

------------

# Code

```cpp
/*
    _______                       ________                        _______
   / _____ \                     / ______ \                      / _____ \
  / /     \_\  _     __     _   / /      \ \   _     __     _   / /     \_\
 | |          | |   |  |   | | | |        | | | |   |  |   | | | |
 | |          | |   |  |   | | | |     __ | | | |   |  |   | | | |
 | |       __ \  \  |  |  /  / | |     \ \| | \  \  |  |  /  / | |       __
  \ \_____/ /  \  \/ /\ \/  /   \ \_____\  /   \  \/ /\ \/  /   \ \_____/ /
   \_______/    \___/  \___/     \______/\__\   \___/  \___/     \_______/
*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 1e5;

int head[N + 50], num, a[N + 50], f[N + 50], n, root, in[N + 50], flag = 1;

struct Node{
	int next, to;
} edge[N * 2 + 50];

void Addedge(int u, int v){
	edge[++num] = (Node){head[u], v};
	head[u] = num;
	return;
}

void Dfs(int x, int fa){
	if (in[x] == 1) { f[x] = a[x]; return; }
	int sum = 0, maxx = 0;
	for (int i = head[x]; i && flag; i = edge[i].next){
		int v = edge[i].to;
		if (v == fa) continue;
		Dfs(v, x);
		sum += f[v]; maxx = max(maxx, f[v]);
	} 
	if (!flag) return;
	int y = sum - a[x];
	f[x] = sum - y * 2;
	if (f[x] > a[x]) { flag = 0; return; }
	if (min(sum / 2, sum - maxx) < y) { flag = 0; return; }
	if (x == root && f[x] != 0) { flag = 0; return; } 
}

void Read(int &x)
{
	x = 0; int p = 0; char st = getchar();
	while (st < '0' || st > '9') p = (st == '-'), st = getchar();
	while (st >= '0' && st <= '9') x = (x << 1) + (x << 3) + st - '0', st = getchar();
	x = p ? -x : x;
	return;
}

int main()
{
	Read(n);
	for (int i = 1; i <= n; i++) Read(a[i]);
	if (n == 2){
		if (a[1] == a[2]) puts("YES");
		else puts("NO");
		return 0;
	}
	for (int i = 1, u, v; i <= n - 1; i++) Read(u), Read(v), Addedge(u, v), Addedge(v, u), in[u]++, in[v]++;
	for (int i = 1; i <= n; i++) if (in[i] > 1) { root = i; break; }
	Dfs(root, 0);
	puts(!flag ? "NO" : "YES");
	return 0;
}
```

---

## 作者：zhendelan (赞：2)

算是比较简单的一类题了吧。

不难发现在非叶节点$u$的决策是固定的，假设子树$v$中要伸上来的次数为$st_v$。  

那么有两种，一种是在子树$u$内解决，只消耗$1$的$u$石子，否则消耗$2$。  

设有$x$对在$u$内解决，那么$a_u = \sum_{v\in u} st_v -x$  。

要伸上去的就是$\sum_{v\in u}st_v - 2x = 2a_u-\sum_{v\in u}st_v$。

过程中判断一下是否合法就可以了。

值得注意的是要判断$x$的最大值。  

这恰与[[ZJOI2018]历史](https://www.luogu.com.cn/problem/P4338)一模一样。  

$x_{max} = \min(\sum st_v/2 , \sum st_v-st_{max})$  

分类讨论一下$st_{max}$最大值就可以证明。  

要注意选一个根不是叶子，不然上面的说法都不成立。   

而$n=2$时都是叶子，要特判掉。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define debug(x) cout<<#x<<':'<<x<<endl
int n;
const int N = 1e5+20;
ll st[N],t[N];
int rd[N],cnt;
vector<int> G[N];
void dfs(int u,int pre)
{
	for(int v:G[u])if(v!=pre)dfs(v,u);
	cnt=0;
	ll sum=0,mx=0;
	for(int v:G[u])if(v!=pre)t[++cnt]=st[v],mx=max(mx,st[v]),sum+=st[v];
	if(!cnt)return;
	ll res=0;
	res = min(sum/2,sum-mx);
	if(sum-res>st[u]||sum < st[u])
	{
		puts("NO");
		exit(0);
	}
	st[u] = 2*st[u]-sum;	
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&st[i]);
	if(n==2)
	{
		printf(st[1]==st[2]?"YES":"NO");
		return 0;
	}
	for(int i=1,x,y;i<n;i++)
		scanf("%d%d",&x,&y),rd[x]++,rd[y]++,
		G[x].push_back(y),G[y].push_back(x);
	int rt=1;
	for(int i=1;i<=n;i++)
		if(rd[i]!=1)rt=i;
	dfs(rt,0);
	if(st[rt]) printf("NO\n");
	else printf("YES\n");
	return 0;
}
/*
4
3 2 2 2 
1 2
1 3
1 4

*/
```





---

## 作者：Star_Cried (赞：2)

## AT2304 Cleaning

### 题意

一个树上每个节点有一些石子，每次只能选取两个叶子节点并将路径间的所有点上的石子数量减1，问是否能将所有石子取完。

### 思路

设 $f_x$ 表示从 $x$ 节点向上的路径条数，$s_x$ 为子节点的 $f$ 值的和，则有：

$$
a_x=\frac{s_x-f_x}{2}+f_x$$
$$f_x=2a_x-s_x
$$

我们只需要保证以下条件即可：

* 从子节点传上来的路径条数的最大值小于等于该点石头个数；
* 向上传的路径条数不为负且小于等于该点石头数。

也就是说，在合法条件下，我们令能在子树内匹配的路径数尽量多，然后向上传路径。

可以证明，在满足上面两个条件下，总能构造出一种合法方案使这个点合法。

其他条件：

* 子叶节点的 $f_x=a_x$；

* 根节点不能为子节点；
* 若根节点的 $f$ 值不为0，判定为无解。

### 实现

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cstring>
#include<cmath>
using namespace std;
inline int read(){
	int w=0,x=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=x*10+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	const int maxn=1e5+10;
	int n,a[maxn],root;
	int ecnt,head[maxn],to[maxn<<1],nxt[maxn<<1],in[maxn],f[maxn];
	inline void addedge(int a,int b){
		to[++ecnt]=b,nxt[ecnt]=head[a],head[a]=ecnt;in[a]++;
		to[++ecnt]=a,nxt[ecnt]=head[b],head[b]=ecnt;in[b]++;
	}
	void dfs(int x,int fa){
		f[x]=in[x]==1?a[x]:(a[x]<<1);
		for(int i=head[x];i;i=nxt[i]){
			int u=to[i];
			if(u==fa)continue;
			dfs(u,x);
			f[x]-=f[u];
			if(f[u]>a[x]) puts("NO"),exit(0);
		}
		if(f[x]>a[x] or f[x]<0) puts("NO"),exit(0);
	}
	inline void work(){
		n=read();
		for(int i=1;i<=n;i++) a[i]=read();
		for(int i=1;i<n;i++) addedge(read(),read());
		if(n==2) return puts(a[1]==a[2]?"YES":"NO"),void();
		for(int i=1;i<=n;i++) if(in[i]!=1){root=i;break;}
		dfs(root,0);
		puts(f[root]?"NO":"YES");
	}
}
signed main(){
	star::work();
	return 0;
}
```



---

## 作者：Kinandra (赞：2)

标签: dfs

任意决定一个度数不为 $1$ 的节点作为根节点($n=2$ 时特判). 设 $up_u$ 表示点 $u$ 向上延伸的路径有多少条, $sum_u=\sum_vup_v$, 其中 $v$ 为 $u$ 的儿子, 则有:

* 对于叶子节点 $a_u=up_u$;
*  对于非叶子节点 $a_u=up_u+\frac{sum_u-up_u}{2}=\frac{sum_u+up_u}{2}$ .

对于每个点我们需要满足 $0\leqslant up_u\leqslant a[u]$, 且 $up_v$ 的最大值不大于 $a[u]$ , dfs 计算并判断就好了.

时间复杂度 $\mathcal O(n)$.

```cpp
#include <bits/stdc++.h>
using namespace std;
int read();

int n, root;
int a[200005], up[200005];
vector<int> e[200005];
void add(int f, int t) { e[f].push_back(t), e[t].push_back(f); }
void dfs(int u, int fa) {
    if (e[u].size() == 1) return up[u] = a[u], void();
    int mx = 0, sum = 0;
    for (int i = 0, v; i < e[u].size(); ++i)
        if ((v = e[u][i]) != fa) dfs(v, u), sum += up[v], mx = max(mx, up[v]);
    up[u] = 2 * a[u] - sum;
    if (up[u] < 0 || up[u] > a[u] || a[u] < mx) puts("NO"), exit(0);
}

int main() {
    n = read();
    for (int i = 1; i <= n; ++i) a[i] = read();
    if (n == 2) return puts(a[1] == a[2] ? "YES" : "NO"), 0;
    for (int i = 1, u, v; i < n; ++i) u = read(), v = read(), add(u, v);
    for (int i = 1; i <= n; ++i)
        if (e[i].size() > 1) root = i;
    dfs(root, 0), puts(up[root] ? "NO" : "YES");
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
```


---

## 作者：syzf2222 (赞：2)

观察过程，发现其实把题意简化成这样：

- 找一个入度不为 $1$ 的根

- 叶子节点往上传它的权值

- 非叶子节点自己消掉一些，剩下的往上传。

考虑一类暴力的 $dp$，设 $f_{i,j}$ 为可不可能在节点 $i$ 处传 $j$ 个上去。

大力猜想这样的取值是一个区间，同时也不难证明其正确性。

设 $L_i,R_i$ 为节点 $i$ 的上下界，显然 $0\le L_i\le R_i\le a_i$

设 $tl=\sum L_{son},tr=\sum R_{son}$，设 $x$ 为向上传的节点个数。

显然向上传 $x$ 个，就要在本地消掉 $a_i-x$ 个，于是 $tl\le x+2(a_i-x)\le tr$

所以 $L_i=2a_i-tr,R_i=2a_i-tl$

感觉很对？交一发，对得差不多了。考虑一下细节。

发现其实不一定能匹配到 $a_i-x$ 个的，也就是 $x$ 有一个下界。

考虑到加一个数总数减匹配数不降，故直接取 $L_{son}$ 算最大匹配即可。

若 $mx\ge \frac{tl}{2}$，则最大匹配为 $tl-mx$，否则就是 $\frac{tl}{2}$

做完了，代码如下：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
const int mod=1e9+7;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int n,m,a[maxn],rd[maxn];
int beg[maxn],nex[maxn<<1],to[maxn<<1],e;
inline void add(int x,int y){
	e++;nex[e]=beg[x];beg[x]=e;to[e]=y;
	e++;nex[e]=beg[y];beg[y]=e;to[e]=x;
}
int L[maxn],R[maxn];
inline void dfs(int x,int fa){
	//printf("start on #%d\n",x);
	int tl=0,tr=0,mx=0;
	for(int i=beg[x];i;i=nex[i]){
		int t=to[i];
		if(t==fa)continue;
		dfs(t,x);mx=max(mx,L[t]);
		tl+=L[t];tr+=R[t];
	}
	int pp=0;if(mx>=tl/2)pp=tl-mx;else pp=tl/2;
	L[x]=2*a[x]-tr;R[x]=2*a[x]-tl;
	if(!tl&&!tr)L[x]=R[x]=a[x];L[x]=max(a[x]-pp,L[x]);
	L[x]=max(0ll,L[x]);R[x]=min(a[x],R[x]);
	//printf("on num #%d: [%d , %d]\n",x,L[x],R[x]);
	if(L[x]>R[x]){puts("NO");exit(0);}
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	int x,y;
	for(int i=1;i<n;i++){
		x=read(),y=read();
		add(x,y);
		rd[x]++,rd[y]++;
	}
	if(n==2)return puts(a[1]==a[2]?"YES":"NO")&0;
	int rt=0;
	for(int i=1;i<=n;i++)
		if(rd[i]>1)rt=i;
	dfs(rt,0);
	puts(L[rt]==0?"YES":"NO");
    return 0;
}
```

深深地感到自己的弱小。

---

## 作者：封禁用户 (赞：1)

首先，对于 $n = 2$ 的情况可以直接特判。对于 $n > 2$ 的情况，我们钦定一个度数大于 $2$ 的点为根。

由于是树上链加，所以考虑差分。那么对于一次操作，即可转化为两个叶子节点 $+1$，$lca$ 和 $lca$ 父节点处 $-1$。

设 $d_u$ 表示节点 $u$ 的差分值，$c_u$ 表示节点 $u$ 需要作为 $lca$ 操作几次，$f_u$ 表示 $u$ 子树内叶子节点仍然可以增加的值。

对于叶子节点显然 $c_u = 0, \ f_u = a_u$。

对于非叶子节点的 $c_u$ 有 $c_u = -d_u - \sum_{v \in son_v} c_v$, 因为对于 $u$ 本身原本需要减去的值为 $-d_u$，但是它作为 $lca$ 的父亲被减去的值为 $\sum_{v \in son_v} c_v$。
对于非叶子节点的 $f_u$ 有 $f_u = (\sum_{v \in son_u}f_v) - 2c_u$。

现在考虑如何判定是否存在解。

首先需要满足对于所有的 $u$，都有 $c_u \geq 0$ 即操作次数非负，这个显然。

其次需要满足 $f_{root} = 0$，即所有的叶子的值都被加完。

最后重点需要考虑的是对于点 $u$ 如何选择子树内的点进行两两配出 $c_u$ 对。
容易发现，若一个操作的 $lca$ 是 $u$，那么选择的两个叶子一定在 $u$ 的两个不同儿子的子树内。那么当前点的 $c_u$ 能被满足当且仅当 $c_u \leq \min\{f_u - \max_{v \in son_u}\{f_v\}, \frac{f_u}{2}\}$。

**证明：**
设 $maxv = \max_{v \in son_u}\{f_v\}$，如果 $maxv > \frac{f_u}{2}$，那么显然只能够取到 $f_u - maxv$。否则，类比 WC2023 T2，将子树内的叶子放在序列上，第 $i$ 次取 $i$ 和 $\frac{f_u}{2} + i$ 配对即可。显然总对数不可能超过 $\frac{f_u}{2}$。

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read() {
	int res = 0, f = 1; char ch;
	while((ch = getchar()) && (ch < '0' || ch > '9') && ch != '-');
	(ch == '-') ? f = -1 : res = ch - '0';
	while((ch = getchar()) && ch >= '0' && ch <= '9') res = (res << 3) + (res << 1) + ch - '0';
	return res * f;
}

const int MAXN = 1e5 + 5;

int rt, n, a[MAXN], du[MAXN], d[MAXN], c[MAXN], f[MAXN];
int tot, hd[MAXN], to[MAXN << 1], nt[MAXN << 1];

inline void add(int x, int y) {
	++du[x]; ++du[y];
	to[++tot] = y, nt[tot] = hd[x], hd[x] = tot;
	to[++tot] = x, nt[tot] = hd[y], hd[y] = tot;
}

void dfs(int now, int fa) {
	d[now] = a[now];
	if(du[now] == 1) return f[now] = a[now], void();
	for(int i = hd[now]; i; i = nt[i])
	 if(to[i] != fa) d[now] -= a[to[i]], dfs(to[i], now), c[now] -= c[to[i]];
	c[now] -= d[now];
	if(c[now] < 0) { puts("NO"); exit(0); }
	int sum = 0, mx = 0;
	for(int i = hd[now]; i; i = nt[i])
	 if(to[i] != fa) sum += f[to[i]], mx = max(mx, f[to[i]]);
	int lim = min(sum / 2, sum - mx);
	if(lim < c[now]) { puts("NO"); exit(0); }
	f[now] = sum - 2 * c[now];
}

int main() {
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	if(n == 2) return puts((a[1] == a[2]) ? "YES" : "NO"), 0;
	for(int i = 1, x, y; i < n; i++) {
		x = read(); y = read();
		add(x, y);
	}
	int rt = 1;
	for(int i = 1; i <= n; i++)
	 if(du[i] > 1) { rt = i; break; }
	dfs(rt, 0);
	puts(f[rt] == 0 ? "YES" : "NO");
	return 0;
}
```

---

## 作者：Celtic (赞：1)

简单题。

首先选一个不是叶子的点做根 dfs。设 $f_i$ 表示每个点的子树内最后会剩下多少条到根的链，容易发现方案是唯一的。所以我们可以设 $mx$ 表示 $u$ 的儿子最大 $f_i$，$sum$ 表示儿子 $f_i$ 的和。

考虑把两条链合并会消耗两个 $sum$ 和一个 $a_u$。因为最终的 $f_u$ 一定是 $sum=a_u$，所以合并次数 $k=sum-a_u$，$f_u=a_u-k=2a_u-sum$。如果 $sum<a_u$ 或者 $2a_u<sum$ 显然是无解的。考虑最大的合并次数，若 $2mx>sum$，那么合并肯定是把其他的子树和 $mx$ 所在子树合并，合并次数为 $sum-mx$。若 $2mx<sum$，那么可以证明合并次数一定为 $\frac{sum}{2}$，判一下 $k$ 是否 $\le$ 这个合并次数就行了。
复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define N 2001001
#define MAX 3505
using namespace std;
typedef long long ll;
typedef double db;
const ll mod=998244353,inf=1e18;
inline void read(ll &ret)
{
	ret=0;char c=getchar();bool pd=false;
	while(!isdigit(c)){pd|=c=='-';c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
	ret=pd?-ret:ret;
	return;
}
ll n,a[N],x,y,du[N],f[N];
vector<ll>v[N];
inline void dfs(ll ver,ll fa)
{
	f[ver]=0;
	ll res=0;
	if(du[ver]==1)
	{
		f[ver]=a[ver];
		return;
	}
	ll maxn=0;
	for(int i=0;i<v[ver].size();i++)
	{
		ll to=v[ver][i];
		if(to==fa)
			continue;
		dfs(to,ver);
		res+=f[to];
		maxn=max(maxn,f[to]);
	}
	if(a[ver]*2<res||res<a[ver])
	{
		puts("NO");
		exit(0);
	}
	ll tmp=res-a[ver];
	if(maxn>res/2)
	{
		if(tmp>res-maxn)
		{
			puts("NO");
			exit(0);
		}
	}
	else
	{
		if(tmp>res/2)
		{
			puts("NO");
			exit(0);
		}
	}
	f[ver]=2*a[ver]-res;
	return;
}
signed main()
{
	read(n);
	for(int i=1;i<=n;i++)
		read(a[i]);
	if(n==2)
	{
		puts(a[1]==a[2]?"YES":"NO");
		exit(0);
	}
	ll rt=0;
	for(int i=1;i<n;i++)
	{
		read(x);
		read(y);
		v[x].push_back(y);
		v[y].push_back(x);
		du[x]++,du[y]++;
	}
	for(int i=1;i<=n;i++)
		if(du[i]>1)
			rt=i;
	dfs(rt,0);
	puts(f[rt]==0?"YES":"NO");
	exit(0);
}```

---

## 作者：elijahqi (赞：0)

那么怎么搞 
我们可以知道最初我们可以考虑如果一个树根的子节点加起来，也比我这个根要小显然是不可以的。如果比我要大，就有可能可行。如果我们直接合并的话可能存在错误样例，即：根为3，而子树分别为1和8，那么显然子树之间互相连边最大只有1条边。所以分析一波我们应该求出这个子树最大可以自己连多少边，然后如果还有剩余那么就是他们和外面的点连的边了。难在我们如何处理，最大能自连多少边，显然可以得到个结论，就是：当子树中最大的那个小于等于剩下的所有的话 就最多可以互相连完  （奇数还会剩1），否则的话最多只有剩余的边数可以自己解决。

为什么呢？考虑一个递归的过程：假设这个结论成立，那么我们每回都要求找一个最大找一个在剩余里最大的然后给他们。

 那么好，这个过程相当于不断动态平衡的给最大值那一块，和剩余的一块删值，所以递归下去发现可以满足条件，我们删不完的情况一定是诸如 0 2的条件无法删掉，所以并不会出现 （口胡

所以我们每次找一下最大值，然后进行上述比较即可，然后新维护的点的值就是我底下多的部分-根权值 （这部分一定要自连 ）然后减去就是我的出边，我要和其他连的边了。

```
#include<cstdio>
#include<algorithm>
#define N 110000
using namespace std;
inline char gc(){
	static char now[1<<16],*T,*S;
	if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
	return *S++;
}
inline int read(){
	int x=0;char ch=gc();
	while (ch<'0'||ch>'9') ch=gc();
	while (ch<='9'&&ch>='0'){x=x*10+ch-'0';ch=gc();}
	return x;
}
struct node{
	int y,next;
}data[N<<1];
struct node1{
	int dep,id;
}vect[N];
int h[N],fa[N],n,in[N],a[N],num;
void dfs(int x){
	for (int i=h[x];i;i=data[i].next){
		int y=data[i].y;if (fa[x]==y) continue;fa[y]=x;
		vect[y].dep=vect[x].dep+1;vect[y].id=y;
		if (in[y]==1) vect[y].dep=0;dfs(y);
	}
}
inline bool cmp(node1 a,node1 b){return a.dep>b.dep;}
int main(){
	//freopen("cleaning.in","r",stdin);
	n=read();
	for (int i=1;i<=n;++i) a[i]=read();
	if (n==2){if (a[1]==a[2]) printf("YES");else printf("NO");return 0;}
	for (int i=1;i<n;++i){
		int x=read(),y=read();
		data[++num].y=y;data[num].next=h[x];h[x]=num;in[y]++;
		data[++num].y=x;data[num].next=h[y];h[y]=num;in[x]++;
	}int root=1;while (in[root]==1) ++root;
	vect[root].dep=1;vect[root].id=root;dfs(root);
	sort(vect+1,vect+n+1,cmp);int op=1;
	//for (int i=1;i<=n;++i) printf("%d %d\n",vect[i].dep,vect[i].id);
	while (vect[op].dep!=0){
		int x=vect[op++].id;long long ans1=0;int max1=0,child=0,childn=0;
		for (int i=h[x];i;i=data[i].next){
			int y=data[i].y;if (fa[x]==y) continue;
			ans1+=a[y];max1=max(max1,a[y]);child++;
		}if (a[x]>ans1){printf("NO");return 0;}
		if (child==1) if (ans1!=a[x]){printf("NO");return 0;}
		long long rest=ans1-max1;
		if (rest>=max1){
			if (ans1-a[x]>(ans1>>1)){printf("NO");return 0;}else a[x]-=ans1-a[x];
		}else{
			if (ans1-a[x]>rest){printf("NO");return 0;}else a[x]-=ans1-a[x];
		}
	}
	if (a[root]==0) printf("YES");else printf("NO");
	return 0;
}
```

---

## 作者：kiritokazuto (赞：0)

- 奶奶的，这个小题，~~巧滴很(四声)~~。

> 我们设当前子树的根节点为 $rt$，它有的石子数为 $a_{rt}$，子树总共需要抵消的石子数之和为 $sum$ (也就是所有子树的 $size$ 和)，子树中石子数最多的一个的石子数为 $Max$，子树内部相互抵消的次数为 $x$ (即不同子树两两组队，抵消)。

- 考虑两种抵消情况对 $rt$ 的影响：
  - 子树内部相互抵消：
    - 每次 $sum - 2$，$a_{rt} - 1$。
  - 子树内和外部抵消：
    - 每次 $sum - 1$，$a_{rt} - 1$。
- 首先如果我的 $sum$ 直接就 比我的 $a_{rt}$ 大，显然不行。
- 我们想让当前子树可以消完，那么我子树里还需要消除的次数必须和我还需的次数相等，如果多则会把我干成负的，少我就把他们干成负的，显然不行。
- 所以我们可以解一个方程 $sum - 2 \times x = a_{rt} - x$，得出： 

$$ sum - a_{rt} = x $$

- 所以我(既是我的，也是我子树的)剩下的所需要的次数为： 

$$  a_{rt} - x = 2 \times a_{rt} - sum $$

- 当然，这里我们还需要考虑一种非法情况：如果我有一颗特别大的子树，那么我其他的子树每一个人都和他消一次是最优的，所以除去自己的石子，它还应该被消  $sum - Max$ 次，所以它最终剩下：

$$ Max - (sum - Max) = 2 \times Max - sum $$

- 个石子(当然，这个的值有可能是负的)。那么我们需要判断一下，我根节点现在还需要消除的次数应该是要比它多的，否则是不行的，会有负数，所以这个题就干完了。
- 当然，对于两个点的情况可以特判一下，我的根应该选一个度数大于 $1$ 的节点，以及最终我的 `size[rt] = 0` 是必须的。
- 之后就 ``dfs`` 一遍统计答案就行。



```cpp


#include <bits/stdc++.h>
#define LL long long
#define Re register int
#define LD double
#define mes(x, y) memset(x, y, sizeof(x))
#define cpt(x, y) memcpy(x, y, sizeof(x))
#define fuc(x, y) inline x y
#define fr(x, y, z)for(Re x = y; x <= z; x ++)
#define fp(x, y, z)for(Re x = y; x >= z; x --)
#define delfr(x, y, z)for(Re x = y; x < z; x ++)
#define delfp(x, y, z)for(Re x = y; x > z; x --)
#define frein(x) freopen(#x ".in", "r", stdin)
#define freout(x) freopen(#x ".out", "w", stdout)
#define ki putchar('\n')
#define fk putchar(' ')
#define WMX aiaiaiai~~
#define pr(x, y) pair<x, y>
#define mk(x, y) make_pair(x, y)
#define pb(x) push_back(x)
#define re(x) return x
#define sec second
#define fst first
using namespace std;
namespace kiritokazuto{
    auto read = [](){
        LL x = 0;
        int f = 1;
        char c;
        while (!isdigit(c = getchar())){ if (c == '-')f = -1; }
        do{ x = (x << 1) + (x << 3) + (c ^ 48); } while (isdigit(c = getchar()));
        return x * f;
    };
    template  <typename T> fuc(void, write)(T x){
        if (x < 0)putchar('-'), x = -x;
        if (x > 9)write(x / 10); putchar(x % 10 | '0');
    }
}

using namespace kiritokazuto;

const int maxn = 2e5 + 100, Mod = 1e9 + 7;
const LL Inf = 2147483647;



int n;
vector <int> wmx[maxn];
int sz[maxn], son[maxn];
int a[maxn];
int rt = 1;
fuc(bool, dfs)(int x, int pre) {
    if(wmx[x].size() == 1)return sz[x] = a[x], 1;
    for(auto to : wmx[x]) {
        if(to != pre) {
            if(!dfs(to, x))re(0);
            sz[x] += sz[to];
            if(!son[x] || sz[son[x]] < sz[to])son[x] = to;
        }
    }
    if(sz[x] < a[x])re(0);
    int tmp = (sz[son[x]] * 2) - sz[x];
    sz[x] = (a[x] * 2) - sz[x];
    return sz[x] >= max(tmp, 0);

} 
signed main() {  
    n =read();
    fr(i, 1, n)a[i] = read();
    delfr(i, 1, n) {
        int x = read(), y = read();
        wmx[x].pb(y);
        wmx[y].pb(x);
    }
    while(wmx[rt].size() == 1)rt++;
    if(rt == n + 1) {
        (a[1] == a[2]) ? puts("YES") : puts("NO");
        re(0);
    }
    (dfs(rt, 0) && sz[rt] == 0 ? puts("YES") : puts("NO"));
} 



```

---

