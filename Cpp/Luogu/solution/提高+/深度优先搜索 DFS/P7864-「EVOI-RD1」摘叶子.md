# 「EVOI-RD1」摘叶子

## 题目描述

某日，小 A 和小 B 在一起开心地玩着游戏。

他们找了一棵以 $1$ 节点为根节点的树，很显然，作为一棵树，总有一个或好多个叶子节点。小 A 和小 B 玩的是回合制游戏。

每次小 A 或小 B 可以选择**任意数量**的叶子节点，将其从树中摘下（每次只能摘叶子节点，每次摘的数量不限制，但**不能不摘**，更不能摘的数量超过本来叶子节点的数量）。

很显然，把一些叶子摘下后，他们的父亲节点有可能会成为新的叶子节点，这时，这些新成为叶子节点的原父亲节点也变得可以被摘取了。

现在，小 A 先摘，小 B 再摘，往复循环。把 $1$ 号节点摘下的人获胜。我们知道，小 A 和小 B 总会按最优方式进行游戏，问谁会取得胜利。

## 说明/提示

本题数据随机，只要简单分析一下性质，就很好骗分，因此本题采用**捆绑测试**。

对于 $40\%$ 的数据：$1 \leq n \leq 100$。

对于 $100\%$ 的数据：$1 \leq n \leq 10^6$，$1 \leq T \leq 10$。

本题时空限制（尤其是空间）均非常宽松，不卡常，不毒瘤，请放心食用。

## 样例 #1

### 输入

```
2
3
1 1
4
1 2 3
```

### 输出

```
1
0
```

# 题解

## 作者：Avocadooo (赞：13)

# 正经教学

### 1.题目类型判断

有两个~~帅哥~~人，他们都需要运用最优策略以获得胜利。

每个人可以在一回合内摘叶子节点。

很明显，这是一道关于树的叶子节点的博弈论题目。


### 2.基本思路
结论1：若当前存在一棵树 $ S $，那么在树 $ S $ 上的任意一非叶子节点上添加一个子节点，生成一棵新的树 $ S' $，那么 $ S' $ 对于先手一定为必胜态。

证明： 

(1) 如果开始是必胜态。因为我们是通过一个非叶子节点添加点 Extra ，可知 Extra 也是一个叶子节点，先手根据必胜态所取点加上 Extra ，留给对方的同样是必败态。
![](https://z3.ax1x.com/2021/09/16/4mdfqs.png)
![](https://z3.ax1x.com/2021/09/16/4mwT0A.png)

(2) 如果开始是必败态，利用非叶子节点增加一个点 Extra ，且第一次直接选择 Extra，那么必败态就送给对面了~~对面很喜欢~~。

![](https://z3.ax1x.com/2021/09/16/4mRAaD.png)

![](https://z3.ax1x.com/2021/09/16/4mREIe.png)

结论2：若树 $ U $ 存在任意一个叶子节点不是“**孤独的叶子**”（便于理解,自己取的名字 ~~（作者觉得这个名字很美妙）~~） **(即该叶子节点的父亲节点的子节点为叶子节点的数量  $  \geq 2 $ )** ，则树 $ U $ 对于先手必胜。

证明：

题目条件 $ n \geq 1 $ 可知树 $ S \neq \varnothing $，所以 $ S $ 中至少存在一个节点为叶子节点；

我们把非“**孤独的叶子**”的一个节点的父亲的其它子节点的其中一个看作结论1证明中的 Extra ，无论去掉 Extra 后的树 $ U' $ 为必胜态还是必败态；


根据结论1，加上了 Extra 的树 $ U $ 一定为必胜态。~~欧耶！！！~~

这是一个例子：

原始树是这个样子；
![](https://z3.ax1x.com/2021/09/16/4mqLlT.png)

我们把点5看为 Extra ；

![](https://z3.ax1x.com/2021/09/16/4mLUNn.png)

此时不管下图是否为必胜或者必败，加上 Extra 的树一定是必胜态（结论1）。

![](https://z3.ax1x.com/2021/09/16/4mOE80.png)

(2) 若不存在一个叶子结点父亲有多于一个儿子，考虑每个叶子（含）到深度最大的儿子个数多于1的祖先（不含）之间的点数。若所有的这些数都是偶数，那么后手必胜，因为后手可以模仿先手直到存在一个叶子结点父亲有多于一个儿子（也就是某个叶子到深度最大的儿子个数多于1的祖先只剩1的距离了），从而达到必胜态。否则先手必胜，因为先手可以一步转换为后手必胜状态。

（这位作者很懒，什么也没有画）

### 3.std代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int fa[1000005];
vector<int> leaves;
int du[1000005],Ks[1000005];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n,x;
		scanf("%d",&n);
		leaves.clear();
		for(int i=1;i<=n;i++)
		{
			Ks[i]=du[i]=0;
		}
		for(int i=2;i<=n;i++)
		{
			scanf("%d",&x);
			fa[i]=x;
			du[x]++;
			Ks[x]++;
		}
		for(int i=1;i<=n;i++)
			if(du[i]==0) leaves.push_back(i);
		bool flag=0;
		for(vector<int>::iterator it=leaves.begin();it!=leaves.end();it++)
		{
			int v=*it;
			int father=fa[v];
			if(Ks[father]>=2)
			{
				flag=1;
				break;
			}
			int cnt=1;
			while(Ks[fa[v]]==1)
			{
				cnt++;
				v=fa[v];
			}
			if(cnt&1)
			{
				flag=1;
				break;
			}
		}
		if(flag) printf("1\n");
		else printf("0\n");
	}
	return 0;
}
```

---

## 作者：一E孤行 (赞：11)

## 这是是《摘叶子》的官方题解。

### Q&A

**Q：** 读到题目，很显然能发现是先手后手，那这是什么？

**A：** 妈妈我知道，是博弈论！！！

**Q：** /jk 那这个题毒瘤吗？

**A：** 并不，请放心食用（其实就是道思维题，不需要博弈论基础）

### 题目分析

对于 Subtask1，$n \leq 100$，直接暴力乱搞就能过，下面对于 Subtask2 进行讲解。

**情况一：** 首先我们考虑一个叶子节点 $x$，$x$ 的父亲节点 $p_x$ 如果有不止一个儿子，那么删除 $x$ 后，$p_x$ 依旧不会成为新的叶子节点。

我们令当前可以删除的节点集合为 $S$，那么删除 $x$ 的操作等于把 $x$ 从 $S$ 中去掉，但不向其中再加入新的节点。

考虑删除 $x$ 的新状态，如果那个状态是先手必败的，那么当前操作删除 $x$ 就可以让先手获胜。

否则新状态是先手必胜的，在新状态下再删除 $S$ 的一个子集 $T$ 就可以当前先手输掉游戏（注意，子集 $T$ 中的点和 $x$ 点一样，是叶子并且其父亲有至少 $2$ 个儿子），可以发现在原来的状态其实是可以在删除 $x$ 的同时删除 $T$，达到当前先手的胜利。

所以只要有这样的叶子节点存在，就一定是先手必胜。

**情况二：** 对于不存在这样的叶子节点的情况。设 $f_x$ 表示从 $x$ 节点开始，走 $f_x$ 条边可以到达一个祖先节点，满足这个祖先节点有至少 $2$ 个儿子节点。很显然 $f_x \ge 2$。

先假设所有的 $f_x=2$，那么不管删除哪个节点 $x$，都会导致 $p_x$ 为新的叶子，且 $f_x=1$，对应了前面的先手必胜。

剩下的就是 $f_x\ge3$ 的情况，只要把所有 $f_x=3$ 的 叶子节点删除，就可以回到 $f_x=2$ 的情况，以此类推。

所以进行归纳：如果所有的叶子节点 $f_x$ 都为偶数，说明先手必败，否则，先手必胜。

最后进行总结：我们设 $0$ 号节点的叶子数量为 $\texttt{inf}$ ，一号节点的父亲为 $0$。这样我们可以进行 $2$ 遍 dfs，一遍求子树 $size$，一遍求 $f$。

对于子树 $size\ge2$ 的节点，我们把他的节点的 $f_x$ 设为 $0$，否则设为 $f_x=f_{p_x}+1$，最后只要一遍扫描判断所有叶子节点的 $f_x$ 是否为偶数，如果一个有一个为奇数，就是先手必胜，如果一个奇数没有，就是先手必输。（可以画图考虑一下，这样可以解决一条链的情况，因为一条链的时候，$f_1=1$）。

那么第一种情况不用判断吗？不用。我们考虑：如果有一个叶子节点他的父亲的子树大小大于等于 $2$ ，对应第一种情况，那么说明 该叶子节点 $x$ 的 $f_x=1$ ，是奇数，所以先手必胜。你细品。

### Code

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<iostream>
#include<cstring>
#include<ctime>
using namespace std;
#define maxn 2000005
struct aaa{
    int to,next;
}a[maxn];
int head[maxn],siz[maxn],tot,fa[maxn],f[maxn];
void add(int x,int y)
{
    a[tot].to=y;
    a[tot].next=head[x];
    head[x]=tot++;
}
void dfs(int u)
{
    for(int i=head[u];i!=-1;i=a[i].next)
    {
        int v=a[i].to;
        siz[u]++;
        dfs(v);
    }
}
void dfs1(int u)
{
    if(siz[u]>=2)
        f[u]=0;
    else
        f[u]=f[fa[u]]+1;
    for(int i=head[u];i!=-1;i=a[i].next)
        dfs1(a[i].to);
}
int main()
{
    clock_t c1=clock();
#ifdef LOCAL
    freopen("tree5.in","r",stdin);
    freopen("tree5.out","w",stdout);
#endif
    //==========================================
     int T,n;
     scanf("%d",&T);
     while(T--)
     {
         tot=0;
         memset(head,-1,sizeof(head));
         memset(siz,0,sizeof(siz));
         scanf("%d",&n);
         for(int i=2;i<=n;i++)
         {
             scanf("%d",&fa[i]);
             add(fa[i],i);
         }
         if(n==1)
         {
             printf("1\n");
             continue;
         }
         dfs(1);
         dfs1(1);
         bool flag=false;
         for(int i=2;i<=n;i++)
             if(siz[i]==0)
                 if(f[i]%2)
                 {
                     flag=true;
                     break;
                 }
         printf("%d\n",flag);
     }
    //=========================================
end:
    cerr<<"Tmie Used:"<<clock()-c1<<"ms"<<endl;
    return 0;
}

```

---

## 作者：XYQ_102 (赞：1)

## 思路
**对于这种没有明显结论的博弈论题，我们先处理出特殊情况。**
- 情况 $1$：树是一条链，那么链的长度如果是偶数的话先手必败，是奇数则先手必胜。 

我们可以对情况 $1$ 进行拓展，假如根节点上连接了很多链，这时该如何判断呢？对于先手来说，我们通过适当的拿取一些叶子，使得所有的链条的长度都是偶数，这样下一次对手不管怎么拿，我们每次都和对手拿一样，这样的话对于对手来说一定都是偶数的局面，因此如果所有的链的长度存在奇数时，先手必胜；如果所有链长度为偶数，那么后手必胜。
- 情况 $2$：存在一个父节点，该节点存在多个叶子节点。

最特殊的是菊花图的形式，根节点上有很多个叶子节点。显然，如果叶子节点的数量为 $1$，那么先手必须拿走这个节点，因此先手必败。否则，叶子节点的数量大于 $1$，那么先手可以把叶子节点拿到只剩下一个，那么就把必败的局面传给对方，因此先手必胜。推广到一半情况，即使不是菊花图，将根节点当成树的一部分结构。该结构一定是 $PN$ 状态其中一种，如果是 $P$ 状态，我们直接将该叶子节点全部拿完，如果是 $N$ 状态，我们就剩一个该叶子节点。对于该局面来说，先手拥有操控权。
- 一般情况：情况 $1$ 和情况 $2$ 结合起来。

对于所有的情况 $2$，先手都可以操纵。也就是说，情况2就是一种必胜态。如果树在刚开始就满足情况 $2$，那么先手必胜。否则一定存在若干个链条使得所有叶子节点都没有兄弟。这样的话我们需要判断的链条的长度，也就是从该叶子节点出发到达的第一个不是只有一个子节点的父节点，也就是直到一种情况 $2$ 出现。因此我们计算出所有链条的长度，如果存在奇数，先手必胜；如果全是偶数，则后手必胜。

时间复杂度 $\Theta(n)$。
## 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
#define int long long
const int N = 2e6 + 10;
int d[N], fa[N], n;
int depth[N];

void solve()
{
    cin >> n;
    if(n == 1) 
    {
        puts("1");
        return ;
    }
    for(int i = 1 ; i <= n ; i ++ ) d[i] = 0, fa[i] = 0;
    fa[1] = 0;
    for(int i = 2 ; i <= n ; i ++ )
    {
        int p; cin >> p;
        fa[i] = p;
        d[p] ++ ;
    }
    
    for(int i = 1 ; i <= n ; i ++ )
    {
        if(d[i]) continue;
        if(d[fa[i]] > 1) 
        {
            puts("1");
            return ;
        }
    }
    
    for(int i = 1 ; i <= n ; i ++ )
    {
        if(d[i]) continue;
        int father = fa[i];
        int t = 0;
        while(d[father] == 1) father = fa[father], t ++ ;
        t ++ ;
        if(t & 1) 
        {
            puts("1");
            return ;
        }
    }
    puts("0");
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    int T = 1;
    cin >> T;
    while(T --) solve();
    return 0;
}
```

---

## 作者：Pentiment (赞：0)

首先考虑菊花图的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/8wqy61rd.png)

如果只剩 $1$ 个叶节点，那么当前只能摘掉它，后手就能摘下根节点，因此先手必输；否则先手可以摘掉其余的叶节点，只留下 $1$​ 个，这样先手必胜。

再考虑一般情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/7pgulycm.png)

如果要使儿子数大于 $1$ 的节点成为叶节点的父亲，则一定会将它到叶节点的链全部摘除，只留下它的儿子。因此，对于每个叶节点，我们计算它爬到一个儿子数大于 $1$​ 的节点的最小边数。游戏交替进行，因此如果其值为奇数，则说明先手一定能造出必胜情况，先手必胜。如果每个叶节点的值都是偶数，说明先手无法造出必胜情况，先手必败。

数据随机生成，因此我们可以直接暴力爬树。

```cpp
#include <bits/stdc++.h>
using namespace std;
void read(int &a) { a = 0; char c = getchar(); while (c < '0' || c > '9') c = getchar(); while (c >= '0' && c <= '9') a = a * 10 - '0' + c, c = getchar(); }
const int N = 1000005;
int T, n, fa[N], deg[N], f, p, q;
int main() {
	read(T);
	while (T--) {
		read(n);
		memset(deg, 0, (n + 1) * sizeof(int));
		for (int i = 2; i <= n; i++) read(fa[i]), deg[fa[i]]++;
		f = 0;
		for (int i = 1; i <= n; i++) {
			if (deg[i]) continue;
			p = i, q = 1;
			while (deg[fa[p]] == 1) q++, p = fa[p];
			if (q & 1) { f = 1; break; }
		}
		printf("%d\n", f);
	}
}
```

---

## 作者：BigSmall_En (赞：0)

## [LG7864 「EVOI-RD1」摘叶子](https://www.luogu.com.cn/problem/P7864)

### 性质分析

对于最简单的情况，一条链，容易得出链长为奇数时先手必胜，否则必败。

对于一类简单的情况，即除了根节点都是叶子节点且数量大于 $2$ 。如图

```
  1      1
 / \    /|\
2   3  2 3 4
```

先手必胜，因为可以删除成一条长为 $2$ 的链到达先手必败的状态。

拓展到更为复杂的情况，如图，即有至少一个子树满足除了子树根节点都是叶子节点且数量大于 $2$ 时

```
     父亲节点
    /       \
   /         x
  /         /|\\\\
另外的子树们 a b c....
```

此时先手必胜。假如“父亲节点”$+$“另外的子树们”$+$ $x$ 点的情况为必败，那么先手删除 $x$ 的所有子节点即可保证必胜。假如其他节点的情况为必胜，那么删除除 $a$ 点外的所有 $x$ 的子节点即可保证必胜。

注意此处的删除操作时针对x的子树而言的。对于另外的子树，先后手当然也能同时进行操作，这里不做讨论（因为已经先假设时必胜或必败了）。

这启发我们谁能先得到这样的子树谁就获胜。同时也告诉我们只需考虑这棵树最底层的分叉。（此处的 "最底层" 是对于每个叶子节点的第一个有多个儿子的祖先，而不是根据树的绝对深度定义）

### 具体策略

假设叶子节点到第一个有多个儿子的祖先的距离为 $dis$ 。假如这棵树有 $m$ 个叶子节点，问题就转化成了：

> 给定 $m(m\geq 2)$ 个正整数 $dis_1,dis_2,\dots,dis_m$ ，每人每次可以对大于 $0$ 的任意数量的数 $-1$ 每个数最多减到 $0$ 。能决定操作次数奇偶性的人获胜。

可以得到，当 $dis_i$ 全为偶数的时候，后手必胜。策略为先手若取 $k$ 个数，则后手取 $(m-k)$ 个数（如果 $k=m$ 则取 $m$ 个数） 。到最后能得到一个全为 $2$ 的序列。这时如若要使操作次数为偶数，那么先手取 $t$ 个数，则后手取 $t$ 个数，直到序列全 $0$ 。如若使操作次数为奇数，那么先手取 $m$ 个数，后手取 $m-1$ 个数；先手取 $k$ 个数，后手取那 $k$ 个数中的 $k-1$ 个，最后会使先手取最后一个数。

假如 $dis_i$ 有奇数的话，则先手必胜，因为先手取掉所有的奇数就能得到全为偶数的情况。

### 代码实现

求 $dis$ 的话搜索就行了。$cnt$ 记录节点的儿子数。

```cpp
void dfs(int u){
	if(cnt[u]>=2)dis[u]=0;
	for(int i=e1.head[u];i;i=e1.enxt[i]){
		int v=e1.to[i];
		dis[v]=dis[u]+1;
		dfs(v);
	}
}
```

判断的话也很简单

```cpp
bool flag=0;
for(int i=1;i<=n;++i)
    if(!cnt[i]&&(dis[i]&1))
    {flag=1;break;}
printf("%d\n",flag);
```

但是上面所说的还有一种情况疏漏，如果树是一条链该如何处理呢？

只需要将根节点的 $dis$ 设为 $1$ 就行了。这样判断叶子节点奇偶性也是一样的了。

完整代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
const int N=1000006,M=1000006;
struct Edge{
	int enxt[M],head[N],to[M],ent;
	inline void addline(int u,int v){
		to[++ent]=v;
		enxt[ent]=head[u];
		head[u]=ent;
	}
	inline void clear(){
		memset(head,0,sizeof(head));
		ent=0;
	}
}e1;
int n,cnt[N],dis[N];
void dfs(int u){
	if(cnt[u]>=2)dis[u]=0;
	for(int i=e1.head[u];i;i=e1.enxt[i]){
		int v=e1.to[i];
		dis[v]=dis[u]+1;
		dfs(v);
	}
}
inline void init(){
	e1.clear();
	for(int i=1;i<=n;++i)cnt[i]=0;
}
int main(){
	int T=read();
	while(T--){
		n=read();
		init();
		for(int i=2;i<=n;++i){
			int x=read();
			e1.addline(x,i);
			++cnt[x];
		}
		dis[1]=1;dfs(1);
		bool flag=0;
		for(int i=1;i<=n;++i)
			if(!cnt[i]&&(dis[i]&1))
				{flag=1;break;}
		printf("%d\n",flag);
	}
	return 0;
}
```

---

