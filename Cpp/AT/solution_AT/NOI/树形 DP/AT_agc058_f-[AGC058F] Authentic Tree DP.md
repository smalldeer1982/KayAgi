# [AGC058F] Authentic Tree DP

## 题目描述

对于一棵无向树 $t$，定义有理数 $f(t)$ 如下：

- 设 $t$ 的顶点数为 $n$。
- 当 $n=1$ 时：$f(t)=1$。
- 当 $n \geq 2$ 时：
  - 对于 $t$ 的每一条边 $e$，将 $e$ 从 $t$ 中删除后得到的两棵树分别记为 $t_x(e), t_y(e)$（顺序无关）。
  - $f(t) = \left( \sum_{e \in t} f(t_x(e)) \times f(t_y(e)) \right) / n$。

给定一棵有 $N$ 个顶点、顶点编号为 $1$ 到 $N$ 的树 $T$。第 $i$ 条边连接顶点 $A_i$ 和顶点 $B_i$。

请计算 $f(T)$ 的值，并对 $998244353$ 取模。

有理数 $\bmod\ 998244353$ 的定义：在本题的约束下，设所求有理数为最简分数 $\frac{P}{Q}$，可以证明 $Q \not\equiv 0 \pmod{998244353}$。因此，存在唯一的整数 $R$ 满足 $R \times Q \equiv P \pmod{998244353},\ 0 \leq R < 998244353$。请输出这个 $R$。

## 说明/提示

### 限制

- $2 \leq N \leq 5000$
- $1 \leq A_i, B_i \leq N$
- 输入的图保证是一棵树

### 样例解释 1

$f(T) = 1/2$。

### 样例解释 2

$f(T) = 1/3$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
1 2```

### 输出

```
499122177```

## 样例 #2

### 输入

```
3
1 2
2 3```

### 输出

```
332748118```

## 样例 #3

### 输入

```
4
1 2
2 3
3 4```

### 输出

```
103983787```

## 样例 #4

### 输入

```
10
4 5
1 9
6 1
8 4
5 9
4 7
3 10
5 2
4 3```

### 输出

```
462781191```

# 题解

## 作者：良心WA题人 (赞：11)

被震撼到了。非常好人类智慧题，使我大小为 $-1$ 的点疯狂旋转。

## 思路

注意到，如果将 $\dfrac{1}{n}$ 换成 $\dfrac{1}{n-1}$，则首先 $n=1$ 时答案为 $1$，根据数学归纳法可以得到 $n$ 为任意值都是 $1$。而这个结论是基于边数为 $n-1$ 的。这个的组合意义为：对于每一部分，随机删除一条边并分成两个部分**分别**删除，最终将整个图删成 $n$ 个独立点的概率。

可是这个题不是 $\dfrac{1}{n-1}$。我们尝试加点东西，显然这个图是不能随便乱加东西的，这会导致很多性质变得不同。

既然我们改变不了数量，那我们就让它从删边改成删点不就是 $\dfrac{1}{n}$ 的系数了吗！于是，我们可以给每条边加一个点（以后称为边点），这样就是每次删除一个点了。于是组合意义变成了每次随机删除一个点，将树变成两个部分**分别**删除，最终将整棵树删完的概率（显然也是 $1$）。可惜的是，点数变成了 $2\times n-1$，点数变化了，这不是我们想要的结果。需要注意的是，我们钦定了分别删除两个部分，也就是钦定了顺序，所以原来树上的点和新加的点的删除顺序不会影响答案。

这个时候厉害的来了，我们给每个边点连 $-1$ 个点，这样点数就是 $n$ 了。如果不好理解，可以看作在模 $P$ 意义下连 $P-1$ 个点。因为它的组合意义所以可以看作是等价的。

于是我们解决了 $\dfrac{1}{n}$ 的问题。现在可以将这个题看作概率问题了。但是我们会在删除边点的同时删除原来树上的点，这个很让人头疼，因为我们如果删除了原树上的边，但此时周围的边点没有删，那么就相当于在原问题上删除了一点，这是不合理的。

于是，我们需要钦定所有边点的删除顺序先于周围的所有点，这样每次删除的时候所有分出来的树的大小都与原来树上对应部分的大小模 $P$ 意义下相等。那么原问题就变成了随机删除一个点，最后所有边点删除先于周围所有点的概率。

我们给这个顺序建立拓补图，发现有的限制是儿子先于父亲，有的限制是父亲先于儿子，很不好算。考虑容斥，钦定每个儿子先于父亲的限制变成父亲先于儿子或者不限制，这下所有边的方向就相同了。

令 $f_{i,j}$ 表示点 $i$ 所属子树钦定有边的外向树大小为 $j$ 时满足要求的概率，若当前点是原树上的点，则每个儿子必然都是边点，要么选择删掉，方案为 $f_{u,i}=f_{u,i}\times \sum_{j=1}^{siz_v} f_{v,j}$，要么选择变成上到下，方案为 $f_{u,i+j}=f_{u,i+j}-f_{u,i}\times f_{v,j}$。因为你钦定了一条边反向，所以要乘上容斥系数 $-1$。如果是边点，则每条限制都是向下的，则 $f_{u,i+j}=f_{u,i+j}+f_{u,i}\times f_{v,j}$（注意此时并没有反向一个限制所以不用乘容斥系数 $-1$）。

最后，每个点在外向树内必然是第一个被删除的，即 $f_{u,i}=f_{u,i}\times \dfrac{1}{i}$。

可是每个边点还有 $P-1$ 个额外点，所以边点的转移是困难的。需要注意的是，当前边点加上这些点 $siz$ 为 $0$，且这些的 dp 值都是 $f_{u,1}=1$。而每个边点只会连接一个原树上的儿子。所以这个边点最终的值就是对于那个唯一原树上的儿子，$f_{u,i}=f_{v,i}\times \dfrac{1}{i}$。

根据容斥，最终答案为 $\sum_{i=1}^{n}f_{1,i}$。

使用树形背包的合并方式（即只卷到 $siz$ 大小）是 $O(n^2)$ 的。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=5004,P=998244353;
vector<int>g[NN];
int f[NN][NN],siz[NN],inv[NN];
void dfs(int u,int fa)
{
	f[u][1]=1;
	siz[u]=1;
	for(auto v:g[u])
	{
		if(v==fa)
			continue;
		dfs(v,u);
		for(int i=siz[u];i;i--)
		{
			int res=0;
			for(int j=1;j<=siz[v];j++)
			{
				f[u][i+j]=(f[u][i+j]-1ll*f[u][i]*f[v][j]%P*inv[j]%P+P)%P;
				res=(res+1ll*f[v][j]*inv[j]%P)%P;
			}
			f[u][i]=1ll*f[u][i]*res%P;
		}
		siz[u]+=siz[v];
	}
	for(int i=1;i<=siz[u];i++)
		f[u][i]=1ll*f[u][i]*inv[i]%P;
}
int main()
{
	int n;
	scanf("%d",&n);
	inv[1]=1;
	for(int i=2;i<=n;i++)
		inv[i]=1ll*(P-P/i)*inv[P%i]%P;
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,0);
	int res=0;
	for(int i=1;i<=n;i++)
		res=(res+f[1][i])%P;
	printf("%d",res);
	return 0;
}
```

---

## 作者：kkio (赞：5)

看了好久，所以我来写一下。

这个式子直接做肯定是没法做的，我们考虑转换成组合意义，$\dfrac{1}{n}$ 的存在提示我们转换成概率。由于每次是选一条边，边的个数是 $n - 1$，概率理应是 $\dfrac{1}{n-1}$ 的，必须加点东西。加边补全的方式不可行，它可能会重复计算自己，想一想很复杂。

此时有一个人类智慧想法：我们把所有边新建一个点，称为**边点** $e$，每个边再带一个大小为 $-1$ 的辅助点，在模意义下就是加一个大小为 $P - 1$ 的点。那么总点数就是 $n$ 了。

此时我们定义这个新树为 $T^{\prime}$，那么答案就是：$T^{\prime}$ 的点排列满足**对于所有边点，其出现位置都比其相邻点小**的概率。证明就是，对于一个子树，你把求上述概率的式子（每次删除一个边点，分成若干子树求概率）列出来，可以发现跟原题式子是完全一样的。

我们把这个点的大小关系从大到小连边，可以连出这样的图：

![P1](https://cdn.luogu.com.cn/upload/image_hosting/u6k97ue1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

（黑色点是边点，蓝色点是大小为 $-1$ 的点）

这个东西的边方向不统一，考虑容斥。将所有向上的边改成向下或没有边，容斥系数就是改成向下的边的数量。

树形背包，设 $f_{u,i}$ 为考虑 $u$ 子树以 $u$ 为根，其外向树大小为 $i$ 满足条件的概率。

两种情况，第一种是将边改下。

![P2](https://cdn.luogu.com.cn/upload/image_hosting/0uwkrij5.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

你要乘上指向的边点作为根的概率 $\dfrac{1}{j}$ 和容斥系数 $-1$。$j$ 是你枚举的 $v$ 外向树大小，用树形背包转移。

然后是删掉的情况。

![P3](https://cdn.luogu.com.cn/upload/image_hosting/v3rxep38.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

同样乘上 $\dfrac{1}{j}$。

最后还要乘上 $u$ 概率 $\dfrac{1}{i}$。

最后答案相当于 $\sum_{i = 1}^{n}{f_{1,i}}$。

upd：之前说过一个，若我们去掉 $\frac{1}{n}$ 会是什么，它是错的，但是我觉得他是问题转化之后，非边点之间无区别的方案数，不知道对不对。求高手指点。



---

## 作者：EuphoricStar (赞：4)

人生中第一道 AtCoder 问号题。

设 $P = 998244353$。

注意到 $f(T)$ 的定义式中，$\frac{1}{n}$ 大概是启示我们转成概率去做。发现若把 $\frac{1}{n}$ 换成 $\frac{1}{n - 1}$ 答案就是 $1$，所以 $\frac{1}{n}$ 大概是要转成点数之类的。

考虑把边转成点，若原树存在边 $(u, v)$，就新建点 $p$，断开 $(u, v)$，连边 $(u, p), (p, v)$，称 $p$ 点为**边点**。但是这样点数就变成 $2n - 1$ 了。

但是！考虑再挂 $P - 1$ 个叶子到 $p$ 下面，点数就变成 $n + (n - 1) \times P$。模意义下 $\frac{1}{n} \equiv \frac{1}{n + (n - 1)P} \pmod P$。

我们可以把原问题转化成在新树上的这个问题：

> 随机生成一个排列 $p_{1 \sim n + (n - 1)P}$，求所有**边点**的 $p$ 值大于其所有邻居的 $p$ 值的概率。

证明大概就是考虑不断取树上的最大值，取 $n - 1$ 次，每次取边点的概率在模意义下等于 $\frac{1}{n}$，转移式也与原题相同。

考虑给树上的边定向，从小连到大，那么就是要求每条边的起点都是边点的概率。像这样（图来自 [kkio](https://www.luogu.com.cn/blog/CCsblog/solution-at-agc058-f)）：

![](https://cdn.luogu.com.cn/upload/image_hosting/u6k97ue1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

随便定一个根。发现有些 $p \to u$ 的边从下连到上看起来不顺眼，考虑容斥。那么所有下连到上的边可以选择上连到下或者下连到上（断掉）。设有 $k$ 条原本是下连到上的边，容斥系数为 $(-1)^k$。

那么我们可以设 $f_{u, i}$ 表示，$u$ 的子树中以 $u$ 为根的外向树大小模 $P$ 意义下等于 $i$，容斥系数乘概率之和。

对于一个边点 $p$，在它原树上对应的边 $(u, v)$ 上统计贡献。

考虑若边 $(u, p)$ 从上到下，那 $v$ 子树中以 $v$ 为根的的外向树可以直接接到 $u$ 下面，直接树形背包合并，$f_{u, i + j} \gets -f'_{u, i} \times \frac{f_{v, j}}{j}$。乘 $\frac{1}{j}$ 是计入边点作为外向树的根的概率，乘 $-1$ 是计入容斥系数。若边 $(u, p)$ 断开，那么 $f_{u, i} \gets f'_{u, i} \times \sum\limits_{j = 1}^{sz_v} \frac{f_{v, j}}{j}$。最后还要 $f_{u, i} \gets \frac{f_{u, i}}{i}$，表示 $u$ 点作为外向树的根的概率。

时间复杂度 $O(n^2)$。

[code](https://atcoder.jp/contests/agc058/submissions/45522757)

---

## 作者：隔壁泞2的如心 (赞：2)

推一半的时候发现好像能把这题转化成我的某道投哪哪鸽的题的形式，当时特别激动，觉得这次题解得好好整个活——但是发现假了。

首先这个式子看着很难受，因为它枚举了 $n-1$ 条边，但分母竟然是 $n$。如果这个分母是 $n-1$，那么答案恒为 $1$，所以分母为 $n$ 时答案会更小。

这样，我们就可以把所求函数转化为“对这个树进行一系列操作，每次操作有 $\frac{1}{n}$ 的概率失败，不然就会把树分为两棵，求成功把树分为叶子的概率”。现在只要构造出容易统计的操作即可。

我们发现，随便找一个根，把树转化为有根树很有前途。这样我们每次操作就是在所有非单点树里随机选一个点，选到根节点就失败，不然就把所选节点到父节点的边断掉。但还是有一点问题，就是“所有非单点树里的点”数量会变化，这就导致概率的分母会很难处理。

然后，经过各种各样的尝试，我们可以得到下面这个操作方案。

- 准备一个 $n$ 面骰子，重复掷骰，掷到 $i$ 就标记一次有根树的节点 $i$，直到每个节点都被标记了至少两次。最开始根节点已被标记了一次。

- 求最后每个节点的第二次被标记晚于其所有儿子节点的第一次被标记的概率。

可以发现这个概率和答案是相同的。求这个概率就可以简单地容斥了，钦定一些父子满足父节点的两次标记都早于儿子节点的第一次标记，只保留被钦定的边，整棵树就被分成了多个互不干扰的树，而每棵树满足钦定条件的概率则是 $\prod_i \dfrac{1}{siz_i^2}$（$siz_i$ 为节点 $i$ 包含自身的子树大小），用树上背包就可以直接解决了！

当然，要记得最开始根节点已被标记了一次，所以对根节点要特殊处理（


```cpp
int dp[6100][6100],n,siz[6100];
vector<int> l[6100];
void fake_tree_dp(int now,int fa){
    siz[now]=1;
    dp[now][1]=1;
    for(auto to:l[now]){
        if(to==fa)continue;
        fake_tree_dp(to,now);
        for(int i=siz[now];i>=1;i--){
            for(int j=1;j<=siz[to];j++)add(dp[now][i+j],dp[now][i]*dp[to][j]%mod);
            dp[now][i]=dp[now][i]*dp[to][0]%mod;
        }
        siz[now]+=siz[to];
    }
    //printf("%lld:",now);for(int i=1;i<=siz[now];i++)printf("%lld ",dp[now][i]);printf("\n");
    if(now==1)return;
    for(int i=1;i<=siz[now];i++){
        dp[now][i]=dp[now][i]*inv[i]%mod*inv[i]%mod;
        add(dp[now][0],dp[now][i]);
        dp[now][i]*=mod-1;dp[now][i]%=mod;
    }
}
signed main(){
    fac[0]=1;for(int i=1;i<=FSIZ-1;i++)fac[i]=fac[i-1]*i%mod;
    ifac[FSIZ-1]=qpow(fac[FSIZ-1],mod-2);for(int i=FSIZ-1;i>=1;i--)ifac[i-1]=ifac[i]*i%mod;
    inv[0]=0;for(int i=1;i<=FSIZ-1;i++)inv[i]=ifac[i]*fac[i-1]%mod;
    scanf("%lld",&n);
    for(int i=1;i<n;i++){
        int in1,in2;
        scanf("%lld%lld",&in1,&in2);
        l[in1].push_back(in2);
        l[in2].push_back(in1);
    }
    fake_tree_dp(1,0);
    int ans=0;
    for(int i=1;i<=n;i++)add(ans,dp[1][i]*inv[i]%mod);
    printf("%lld",ans);
} 
```

记不清是在什么时候了，我想了这道题好久，之后放学走到地铁站的路上，一边喝着桃桃蜜柚一边研究如何处理“所有非单点树里的点”数量的变化，然后不会。

说实话这种题做不出来是真的闹心，影响一天的心情。而能不能做出来其实很多时候也是凭运气。长期做 AGC 题的人往往——后面忘了。而对我而言，对这道题的挑战跨过了太长时间，成功和失败的界限也模糊了。但是，把这题做出来不管咋说都肯定是很让人高兴的！

所以我建议不要以过题为目的看 AGC 题，会做当然好，不会就放置；也没必要因为浪费时间而影响心态，也许过后这反倒成了美好的回忆。

---

## 作者：takanashi_mifuru (赞：1)

下面 $P$ 表示的是本题模数。

首先是一个不太能观察出来的观察，那就是这个贡献看起来很鬼畜，我们要想办法把他变得不鬼畜一点，这个看着很像概率的形式，但是边只有 $n-1$ 条，他的系数却是 $\frac{1}{n}$。

那我们考虑把系数换成 $\frac{1}{n-1}$ 试试看，然后发现权值固定为 $1$，因为相当于是每次随机一条边删掉之后最后变成 $n$ 个孤点的期望。

但是系数肯定没法换，而通过加边凑系数感觉看着就不太能做，考虑把删边转化成删点。

考虑把边换成点，点数不对可以通过加很多叶子直到取模后的值为 $n$ 为止（这个就是怎么方便怎么来，因为反正他也不给任何贡献，只是用来平衡总点数的）。

这个时候我们的系数就全对了，那么按照这样删，每次给的贡献必然就是 $1$，于是这个题就转变为求解删除的方案数了。

考虑删除的方案数，显然因为我们加了点加了边，这个时候谈及要删除点，就不一定能删的合法，但是直接判定一些点不被删除，我们的最根本的系数又无从保证，所以我们考虑刻画一下合法的方案长什么样子。

首先最根本的就是边点必须比他连接的两个树点先删除，这是为什么呢，因为这些点本来就只是来凑数的，一个树点只有成为孤立点的时候才可以被删除（因为这个时候删除并不存在分裂联通块的贡献，而且对于边点分裂联通块之后的贡献肯定也要依赖树点传播），所以最后写出来就是边点指向其连接的两个树点之后求有向树拓扑序计数。

至于我们添加的平衡点，考虑他的贡献肯定是像树点那样计算，但是有问题，他的贡献不够单一，但是他又有这么多个，那怎么办呢？

考虑还是把他拆成模意义下相等，把 $P-1$ 个节点挂到这个边点上面，这样的话转移就可以做了，因为边点和这个转移点合在一起为 $P$ 个点，贡献正好没了，总点数也是保持不变，所以这是这个题必须把平衡点挂在边点上的原因，就是为了把平衡点的贡献消除。

然后考虑有向树拓扑序计数怎么做，首先是外向树，考虑对于每个子树形成的子序列，根节点放在任意一个位置都是一种方案，但是我们显然只想让他放在子序列的第一个，所以要除以这个子序列的长度，也就是子树的大小。

搬到这个题上怎么做呢，考虑容斥掉内向边，要么当外向边要么就消失，然后这样的话就需要维护当前联通块的点数（相当于是维护子树大小），这部分可以树上背包。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int P=998244353;
int n;
vector<int> ljb[5005];
int dp[5005][5005];
int f[5005];
int siz[5005];
int inv[5005];
int power(int x,int y=P-2){
    if(y==0)return 1;
    int tmp=power(x,y>>1);
    if(y&1)return tmp*tmp%P*x%P;
    return tmp*tmp%P;
}
void getdp(int cur,int fa){
    dp[cur][1]=1;
    siz[cur]=1;
    for(int i=0;i<ljb[cur].size();i++){
        int v=ljb[cur][i];
        if(v==fa)continue;
        getdp(v,cur);
    }
    for(int i=0;i<ljb[cur].size();i++){
        int v=ljb[cur][i];
        if(v==fa)continue;
        for(int j=1;j<=siz[cur]+siz[v];j++){
            f[j]=0;
        }
        for(int j1=1;j1<=siz[cur];j1++){
            for(int j2=1;j2<=siz[v];j2++){
                f[j1+j2]-=dp[cur][j1]*dp[v][j2]%P*inv[j2]%P;
                if(f[j1+j2]<0)f[j1+j2]+=P;
                f[j1]+=dp[cur][j1]*dp[v][j2]%P*inv[j2]%P;
                if(f[j1]>=P)f[j1]-=P;
            }
        }
        for(int j=1;j<=siz[cur]+siz[v];j++)dp[cur][j]=f[j];
        siz[cur]+=siz[v];
    }
    for(int j=1;j<=siz[cur];j++)dp[cur][j]=dp[cur][j]*inv[j]%P;
    return;
}
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)inv[i]=power(i);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%lld%lld",&u,&v);
        ljb[u].push_back(v);
        ljb[v].push_back(u);
    }
    getdp(1,0);
    int ans=0;
    for(int i=1;i<=n;i++){
        ans+=dp[1][i];
        if(ans>=P)ans-=P;
    }
    printf("%lld\n",ans);
    return 0;
}
/*

*/
```

---

## 作者：DaiRuiChen007 (赞：1)

# AGC058F 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_agc058_f)

**题目大意**

> 对于一棵 $n$ 个点的树 $T$，定义 $f(T)$ 为：
>
> - 若 $n=1$ 则 $f(T)=1$。
> - 否则对于所有 $e\in T$，设 $T_{e,1},T_{e,2}$ 为切掉这条边形成的两棵子树，那么 $f(T)=\dfrac 1n\sum_e f(T_{e,1})\times f(T_{e,2})$。
>
> 给定 $T$，求 $f(T)\bmod P$ 的值。
>
> 数据范围：$n\le 5000$。

**思路分析**

看到这个模型，考虑编一个组合意义：在每条边中间插一个点，那么 $f(T)$ 就是随机排列每个点的标号，使得新加入的点标号都大于其邻居的方案数。

那么 $f(T)$ 的定义相当于枚举最大值所在的位置，但是我们会发现此时的分母为 $\dfrac 1{2n-1}$，我们需要调整，不妨给加入的每个点下面挂 $P-1$ 个点，那么在模意义下分母为 $\dfrac 1n$。

然后我们可以考虑容斥，把边大于其父亲的限制容斥，那么所有的限制都形如儿子小于父亲，所有事件都独立，只要维护每个点为根的连通块大小即可。

转移时类似树形背包，动态枚举每条边断不断即可。

时间复杂度 $\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=5005,MOD=998244353;
vector <int> G[MAXN];
ll ksm(ll a,ll b=MOD-2,ll p=MOD) {
	ll ret=1;
	for(;b;a=a*a%p,b>>=1) if(b&1) ret=ret*a%p;
	return ret;
}
int siz[MAXN];
ll dp[MAXN][MAXN],f[MAXN],inv[MAXN];
void dfs(int u,int fa) {
	siz[u]=1,dp[u][1]=1;
	for(int v:G[u]) if(v^fa) {
		dfs(v,u);
		for(int i=1;i<=siz[v];++i) dp[v][i]=dp[v][i]*inv[i]%MOD*inv[i]%MOD;
		memset(f,0,sizeof(f));
		for(int i=1;i<=siz[v];++i) {
			for(int j=1;j<=siz[u];++j) {
				f[i+j]=(f[i+j]+MOD-dp[v][i]*dp[u][j]%MOD)%MOD;
				f[j]=(f[j]+dp[v][i]*dp[u][j])%MOD;
			}
		}
		siz[u]+=siz[v],swap(dp[u],f);
	}
}
signed main() {
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) inv[i]=ksm(i);
	for(int i=1,u,v;i<n;++i) scanf("%d%d",&u,&v),G[u].push_back(v),G[v].push_back(u);
	dfs(1,0);
	ll ans=0;
	for(int i=1;i<=n;++i) ans=(ans+inv[i]*dp[1][i])%MOD;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：ducati (赞：1)

## Description

[传送门](https://www.luogu.com.cn/problem/AT_agc058_f)

## Solution

考虑赋予 $f(T)$ 组合意义。

转移式中，我们枚举了边 $e \in T$，将贡献求和并除以 $n$。可以想到将 $f(T)$ 设为某条件被满足的概率，边带权，$e$ 对应权值最小的边。然而，边数是 $n-1$ 而非 $n$，转移系数应是 $\frac {1} {n-1}$ 而非 $\frac {1} {n}$，组合意义并不吻合转移式。

考虑在每条边 $u-v$ 的中间加一个虚点 $p$，删去 $u-v$ 并加入 $u-p,v-p$；点带权，$e$ 对应虚点权值最小的边。然而，点数是 $(n-1)+n$，与 $\frac 1 n$ 的系数仍不吻合。考虑这样的操作：对每个虚点 $p$，新建 $998244352$ 个点，将它们全部连向 $p$。这样一来，模意义下点数就是 $n$ 了。

---

综上所述，我们将问题转化为：给定一棵树，在每条边中间加一个虚点，有 $998244352$ 个叶子连向该点。设共有 $k$ 个点，你需要将这 $k$ 个点随机排列，求虚点排在其各邻居前的概率。

考虑容斥。对于虚点 $p$，设其父亲为 $fa_p$，我们将 $p$ 排在 $fa_p$ 前的限制，拆成 $\lceil$ $fa_p$ 排在 $p$ 前 $\rfloor$ 和 $\lceil$ 无限制 $\rfloor$。这样一来，有若干条形如 $\lceil$ $fa_u$ 要排在 $u$ 前面 $\rfloor$ 的限制，若在新图中连一条 $fa_u$ 到 $u$ 的边，则组成了若干棵外向树，节点 $u$ 的贡献是 $u$ 在新图中的子树大小 $sz_u$ 的倒数。

那么，我们只需在原树上跑树形背包即可：令 $f_{u,s}$ 表示，看了以 $u$ 为根的子树，$sz_u \equiv s \pmod {998244353}$ 的概率。转移是平凡的。

时间复杂度 $O(n^2)$。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
#define eb emplace_back
using namespace std;
const int N=5e3+5,mod=998244353;

int read(){
	int s=0,w=1;char ch=getchar();
	while (ch<'0'||ch>'9') {if(ch=='-')w=-w;ch=getchar();}
	while (ch>='0'&&ch<='9') {s=(s<<1)+(s<<3)+(ch^'0');ch=getchar();}
	return s*w;
}
int n,ans,sz[N],f[N][N],g[N],inv[N],coef[N]; vector<int> GA[N];
inline int gmod(int x){return x%=mod,(x<0)?(x+mod):x;}
void dfs(int u,int F){
	f[u][sz[u]=1]=1;
	for (int v:GA[u])if(v^F){
		int sum=0; dfs(v,u);
		for (int i=1;i<=sz[v];i++)  sum+=f[v][i];
		for (int i=1;i<=sz[u];i++){
			for (int j=1;j<=sz[v];j++)  (g[i+j]+=f[u][i]*f[v][j])%=mod;
		}
		sum%=mod,sz[u]+=sz[v];
		for (int i=1;i<=sz[u];i++)  f[u][i]=gmod(f[u][i]*sum-g[i]),g[i]=0;
	}
	if (F) {for(int i=1;i<=sz[u];i++)(f[u][i]*=coef[i])%=mod;}
	else {for (int i=1;i<=sz[u];i++)(ans+=f[u][i]*inv[i])%=mod;}
}
signed main(){
	n=read(),inv[1]=1;
	for (int i=2;i<=n;i++)  inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for (int i=1;i<=n;i++)  coef[i]=(inv[i]*inv[i])%mod;
	for (int i=1,u,v;i<n;i++)  u=read(),v=read(),GA[u].eb(v),GA[v].eb(u);
	return dfs(1,0),cout<<ans,0;
}
```


---

