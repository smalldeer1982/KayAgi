# 「TOCO Round 1」Eternal Star

## 题目背景

「诚挚地祈愿」

「在星辰坠落的那一瞬间」

「水中倒映着两个人的身影」

「交相辉映」

![](https://cdn.luogu.com.cn/upload/image_hosting/7tf5iu0p.png)

## 题目描述

Kuon 想要一棵结点数量尽可能少的树。

她会给每个结点编号为一个正整数，使得相邻结点编号不同并且所有结点的编号和最小。如果存在很多种方案她会选择任意一种。

请你帮忙构造出一棵树使得它在 Kuon 编号后的最大编号一定不小于 $k$。

## 说明/提示

本题给分方式如下：

- 如果构造的树满足要求并且 $1\leq n\leq x$，$1\leq u,v\leq n$ 那么你将获得该测试点的所有分数。
- 否则该测试点你将获得 $0$ 分。

| 测试点编号 | $k$ | $x$ |
| :-: | :-: | :-: |
| $1$ | $1$ | $/$ |
| $2$ | $2$ | $/$ |
| $3$ | $3$ | $10$ |
| $4$ | $3$ | $8$ |
| $5$ | $4$ | $40$ |
| $6$ | $4$ | $34$ |
| $7$ | $5$ | $/$ |
| $8\sim 16$ | $/$ | $/$ |
| $17$ | $10$ | $53808$ |
| $18\sim 19$ | $/$ | $/$ |
| $20$ | $12$ | $519616$ |

对于 $100\%$ 的数据，$1\leq k\leq 12$，$1\leq x\leq 10^6$，每个测试点必定存在一种树的构造方案能获得满分。

## 样例 #1

### 输入

```
2 5```

### 输出

```
5
1 2
2 3
3 4
4 5```

## 样例 #2

### 输入

```
3 20```

### 输出

```
16
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
2 10
2 11
2 12
2 13
2 14
2 15
2 16```

# 题解

## 作者：Lsrh666 (赞：6)

# ${\color{Violet} \mathfrak{description} } $   

构造一棵树使得：
- 要求1：树的大小 $n$ 尽量小。
- 要求2：相邻点的编号不同。
- 要求3：树的最大编号不能小于 $k$。

同时给定 $x$，要求 $n\leq x$。

# ${\color{Violet} \mathfrak{solution} } $   

为了方便维护，不妨设最大值 $x$ 为根。  
发现此时，$x$ 必定有 $1 \sim x-1$ 的儿子。  
证明是显然的，假如没有这些儿子中的任意一个 $x_{sp}$，将 $x$ 换成 $x_{sp}$，可以使树的最大值变成 $x-1$。  
接下来考虑换值，考虑到**要求2**，将根的儿子 $i$ 换成 $i+1$，同时将 $x$ 换成 $i$。  
但是一个 $i$ 是不够的，我们需要 $r-i+1$ 个这样的儿子。  
但是，这样需要的操作次数太多，导致挂到55pts。  
需要优化！  
考虑到 $i=x-1$ 的时候，我们用 $x-1$ 替换掉了 $x$。  
这样，$x$ 就又重复出现了。  
考虑用 $x-2$ 换掉 $x-1$，用 $x-3$ 换掉 $x-2$  
但是 $x-3$ 可以用 $x-1$ 换掉，这样就循环起来了。  
这样能实现减少总节点数的功能。

# ${\color{Violet} \mathfrak{code} } $ 
```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i,j,k) for(int i=j;i<=k;++i)
#define per(i,j,k) for(int i=j;i>=k;--i)
#define epr(i,j) for(int i=head[j];i;i=nxt[i])
using namespace std;

const int MAXN=1e6+10;
int head[MAXN],to[MAXN<<1],nxt[MAXN<<1];
int cnt=0,tot=0;

inline void add(int x,int y){
    to[++cnt]=y,nxt[cnt]=head[x];
    head[x]=cnt;
}
inline int sol(int p,int cur){
    int res=++tot;
    if(p==1) return tot;
    if(res==1) add(res,sol(p-1,1));
    per(i,p-1-(res==1),1) rep(j,1,p-i+1+cur) add(res,sol(i,0));
    return res;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
    int k,x; cin>>k>>x;
    sol(k,0);
    cout<<tot<<'\n';
    rep(i,1,tot) epr(j,i) 
    cout<<i<<' '<<to[j]<<'\n';
	return 0;
}
```

---

## 作者：UID341736 (赞：5)

### 算法一

手玩然后打表输出。

大概能玩到 $n=3$。

### 算法二

考虑钦定 $k$ 为根。

显然 $k$ 必须存在 $1\sim k-1$ 的儿子，否则将 $k$ 换掉会更优。

可以递归解决这些子树，但儿子的数量需要多少呢？

我们依次进行**替换**，假设儿子 $p(p<k)$ 替换 $k$，必须保证替换后权值和**更大**。

因为替换后两个 $p$ 会相邻，所以 $p$ 子树的根我们要换掉。

考虑换成 $p+1$，这样能够在保证不冲突的情况下使得权值和尽量小。

如果存在 $y$ 个 $p$ 儿子，那么可以列出不等式：

$$k+yp<p+y(p+1)$$

解出来 $y>k-p$，至少需要 $k-p+1$ 个儿子。

实际得分 $55$。

### 算法三

感觉这个递归结构很难优化，考虑能否减少儿子数量。

要改变儿子数量就得改变替换成的数。但问题是，改成比 $p$ 小的数不可能比改成 $p+1$ 要优，因为下面至少有两个数会冲突。

但是对于 $p=k-1$ 来说，如果改成了 $k$，**$\boldsymbol k$ 仍旧会在树中出现！**而我们想要的是 $k$ 不出现，所以在这个地方可以进行一个优化。

考虑将 $k-1$ 换成 $k-2$，然后会发现后面的 $k-3$ 又可以换成 $k-1$，回到了与原先相同的情况。这样将第二层 $k-1$ 的子树数量从 $2$ 减少到了 $1$，虽然该子树中第三层每种子树数量均会增加 $1$，但**总体**结点数量会减少。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000005
#define For(i,x,y)for(i=x;i<=(y);i++)
#define Down(i,x,y)for(i=x;i>=(y);i--)
struct node
{
	int next,to;
}e[N];
int head[N],g,cnt,k;
inline void add(int u,int v)
{
	e[++g].to=v;
	e[g].next=head[u];
	head[u]=g;
}
void write(int X)
{
	if(X<0)putchar('-'),X=-X;
	if(X>9)write(X/10);
	putchar(X%10|48);
}
int build(int siz,bool now)
{
	if(siz==1)return++cnt;
	int u=++cnt,i;
	int j;
	if(u==1)add(u,build(siz-1,1));
	Down(i,siz-1-(u==1),1)
	For(j,1,siz-i+1+now)add(u,build(i,0));
	return u;
}
int main()
{
//	freopen("C.in","r",stdin);
//	freopen("C.out","w",stdout);
	int i,j,x;
	cin>>k>>x;
	build(k,0);
	write(cnt);
	putchar('\n');
	For(i,1,cnt)
	for(j=head[i];j;j=e[j].next)
	{
		write(i);
		putchar(' ');
		write(e[j].to);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：DengDuck (赞：3)

我要明确一个事情，我之所以这个节点选择有 $K$ 这么大，是因为我的儿子有 $[1,K-1]$，而且 $x\in [1,K-1]$ 不能把我换掉。

前者的条件比较明确，但是后者这个条件有点模糊。

我们考虑把原先为 $K$ 的点换成 $x(x\in [1,K-1])$，那么这个点就会和原来是 $x$ 的儿子冲突，所以这个儿子会变成 $x+1$。

如果这种儿子有 $t$ 个，那么我们有不等式:

$$
K+tx< x+t(x+1)
$$

解得 $t>K-x$，所以我们的儿子得有 $K-x+1$ 个 $x$。

这样可以跑出 $55$ 分的答案，考虑优化。

整出两个 $K-1$ 大小的树出来，然后让树中的 $K-1$ 相连，由于相邻不相同，所以一个 $K-1$ 会变成 $K$，这样就必然合法了。

这个方案仔细一算其实大大减少了节点数，因为原来 $K$ 大小的树有俩 $K-1$ 大小的树还有一车子大小在 $[1,K-2]$ 之中的树，现在的方案就俩 $K-1$ 大小的树。

---

## 作者：5ab_juruo (赞：3)

做到这个题就想起来 [[CQOI2005]珠宝](https://www.luogu.com.cn/problem/P5765)。

如果要一个节点的权值 $\ge k$，则这个点选 $1\sim k-1$ 的时候花销都应当严格大于选 $k$ 的开销。当根节点尝试选 $x$ 的权值时，对于子树中保证根节点 $\ge x$ 的节点（设有 $cnt$ 个）应该选 $x+1$。此时：

- 如果根节点选 $k$，则总开销为 $k+cnt\cdot x$；
- 如果根节点选 $x$，则总开销为 $x+cnt\cdot (x+1)$；

显然我们应该保证 $k+cnt\cdot x<x+cnt\cdot (x+1)$，所以 $cnt>k-x$。即，保证根节点 $\ge x$ 的子树至少应该有 $k-x+1$ 个。

考虑递归构造，如果要钦定当前树的根节点权值 $\ge k$，则要在根下面挂：

- $k$ 棵子树，保证根节点的权值 $\ge 1$；
- $k-1$ 棵子树，保证根节点的权值 $\ge 2$；
- $k-2$ 棵子树，保证根节点的权值 $\ge 3$；
- $\dots$
- $3$ 棵子树，保证根节点的权值 $\ge k-2$；
- $2$ 棵子树，保证根节点的权值 $\ge k-1$。（\*）

直接这样写只能得到 $55$ 分，注意到题目并不要求我们将根节点的权值设为 $k$，所以将上述构造中的（\*）部分优化。

先按照上述步骤构造（除去最后一步）两棵树，然后再在这两棵树之间连边，显然两边都取不了 $\le k-2$ 的数，且这样显然也比直接构造优秀。打个表，发现上界就是题目中最大的数据范围，直接写就过了。

---

很久以前写的，有点抽象。

```cpp
#include <cstdio>
#define OFF stdout
using namespace std;

int out(int st, int cnt)
{
	int nxt = st + 1;
	for (int i = 1; i < cnt; i++)
	{
		for (int j = i; j <= cnt; j++)
		{
			fprintf(OFF, "%d %d\n", st, nxt);
			nxt = out(nxt, i);
		}
	}

	return nxt;
}

int uu[] = {0, 1, 2, 8, 28, 96, 328, 1120, 3824, 13056, 44576, 152192, 519616};

int main()
{
	int k, x, nnxt = 2, mdd;

	scanf("%d%d", &k, &x);

	if (k == 1)
	{
		puts("1");
		return 0;
	}

	printf("%d\n", uu[k]);

	for (int i = 1; i < k - 1; i++)
		for (int j = i; j <= k; j++)
		{
			fprintf(OFF, "%d %d\n", 1, nnxt);
			nnxt = out(nnxt, i);
		}

	mdd = nnxt, nnxt++;
	fprintf(OFF, "%d %d\n", 1, mdd);
	for (int i = 1; i < k - 1; i++)
		for (int j = i; j <= k; j++)
		{
			fprintf(OFF, "%d %d\n", mdd, nnxt);
			nnxt = out(nnxt, i);
		}

	return 0;
}
```

---

## 作者：bits47 (赞：2)

## [P7393 「TOCO Round 1」Eternal Star](https://www.luogu.com.cn/problem/P7393)
我们设最大值为根。

通常认为，一个点点值要是 $k$，其儿子必定要有 $1\ldots k-1$。

但每个值只有一个显然不够。比如点值为 $i$ 的儿子可以换成 $i+1$，再把 $k$ 换成 $i$。

因此，点值为 $i$ 的点应有 $k-i+1$ 个才能保证不被换。

但是，我们发现，如果 $k$ 和 $k-1$ 互换后 $k$ 仍然会在树中，没有影响。因此，我们可以构造一棵形态对称的树，左右两个根下连接点值为 $1\ldots k-2$ 的子树 $k-i+1$ 棵。

显然，这样的树的节点数小于之前的方案。（$0 \ldots k-2$ 的树各增加了一棵，$k-1$ 的树减少了一棵）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int mx,x,cnt;
vector<int>e[N]; 
int dfs(int k,int ad){
	int u=++cnt;
	if(k==1) return u;
	if(u==1) e[u].push_back(dfs(k-1,1));
	for(int i=1;i<k-(u==1);++i)
		for(int j=k-i+1+ad;j;--j) e[u].push_back(dfs(i,0));
	return u;
}
void op(int u){for(int v:e[u]) printf("%d %d\n",u,v),op(v);}
int main(){
	scanf("%d%d",&mx,&x);
	dfs(mx,0);
	printf("%d\n",cnt);
	op(1);
}
```

附：

通过这道题可以理解 [P4395 [BOI2003] Gem 气垫车](https://www.luogu.com.cn/problem/P4395)、[[CQOI2005]珠宝](https://www.luogu.com.cn/problem/P5765) 的上界。因为不太会算具体值~~（oeis 上也没找到）~~，可以取宽一点的上界，比如 $\log n$。

---

## 作者：Cuiyi_SAI (赞：1)

神仙题。

## $\large{\text{Solution}}$

考虑构造一棵在根节点处取得最大点权 $k$ 且符合要求的树。对于根节点，能够让我们限制它的大小的，**只有其子节点的点权和数量**。因此我们调整子节点的这些信息就可使得根节点满足要求。

需要限制如下：

- 子节点的点权，肯定包含了 $1\cdots k-1$。

    若子节点中没有权值为 $p$ 的，那么让根节点变为 $p$ 则可使得整棵树的最大值变成 $k-1$ 且不会产生矛盾，与我们的期望不符。
- 每种权值对应的子节点有多个。

    若没有这层限制，我们当然可以没有顾虑的使得根节点变为 $p$，而原本权值为 $p$ 的子节点变为 $p+1$，根节点因此变小了（称这一些列操作为 C，下面将会用到）。但是题目中有着 "点权和最小" 这一要求，于是我们可以通过调整各种子节点的数量来规避这种情况。

    具体的，我们设点权为 $p$ 的子节点的个数为 $x$，那么为了保持根节点大小不变，应该有 $k+px<p+(p+1)x$，化简得到 $x>k-p$。

    综上，第 $p$ 种子节点至少要有 $k-p+1$ 个。为了使点数最少，我们取等。 

通过以上方式建立子节点，即可确定一个值为 $k$ 的根节点，对于每棵子树则是子问题，递归处理即可。

该方法实际得分 55pts，错误的原因是建树所使用的节点过多。

### 优化

为了通过此题，我们需要让所用的总结点数更小，也就需要优化以上建树过程。

观察上述思路，貌似无懈可击，但是我们应该注意到特殊的第 $k-1$ 号子节点。若我们对 $k-1$ 节点进行限制二中的替换（即操作 C），那么实际上其实就是根节点 $k$ 和 $k-1$ 对调了一下——$k$ 依旧是整棵树中最大的节点且依旧可以成为根节点，无事发生，这个操作没有直接的影响答案。

也就是说，对调 $k-1$ 和 $k$ 没有我们想得那么严重，我们只需要使得 $k-1$ 下的子节点可以同样限制住 $k$ 即可保证答案。但是根据限制二得到的不等式，我们却建立了**两个** $k-1$ 子节点，这就是一种浪费！

具体的，如果使用这个优化，我们要在原本的 $k-1$ 号子节点下按照对 $k$ 的限制方法，建立编号为 $1\cdots k-2$ 的子树（这是为了让这个位置既能限制 $k-1$ 也能限制 $k$，也就无惧操作 C），然后删掉多余的那棵 $k-1$ 子树。也就是说我们可以**用根为 $1\cdots k-2$ 的这些子树来换掉一棵根为 $k-1$ 的子树**。这显然是值得的，因为后者的大小远大于前者，这么一换总结点数就变小了。

将上述优化具象化，我们建树的方式变为：建立两棵对称的树，将其根连接，使得其左右两个根下的 $1\cdots k-2$ 个子节点能够满足对 $k$ 的限制。

至此，本题结束。

## $\large{\text{Code}}$

实现上有一个细节，就是在递归处理子树的时候不能再使用上文的优化。因为用了优化后建的树的对称性，**其最大值可以在两个根的位置变化**（我们最终答案不关心最大值的位置所以可以使用，但是递归到子树的时候我们有必要做这个限制），这就会导致我们对祖先的限制都失效。因此优化只能在最开始使用。



```cpp
#include <bits/stdc++.h>
using namespace std;
int K,x,n=0,tot;
pair<int,int> ans[1000010];
int solve(int k,int op){
    int u=++n;
    if(k==1) return u;
    if(u==1) ans[++tot]=make_pair(u,solve(k-1,1));
    for(int i=1;i<k-(u==1);i++){
        for(int j=1;j<=k-i+1+op;j++){
            ans[++tot]=make_pair(u,solve(i,0));
        }
    }
    return u;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>K>>x;
    solve(K,0);
    cout<<n<<'\n';
    for(int i=1;i<=tot;i++) 
        cout<<ans[i].first<<' '<<ans[i].second<<'\n';
    return 0;
}
```

---

