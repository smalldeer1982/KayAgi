# Potion Brewing Class

## 题目描述

Alice's potion making professor gave the following assignment to his students: brew a potion using $ n $ ingredients, such that the proportion of ingredient $ i $ in the final potion is $ r_i > 0 $ (and $ r_1 + r_2 + \cdots + r_n = 1 $ ).

He forgot the recipe, and now all he remembers is a set of $ n-1 $ facts of the form, "ingredients $ i $ and $ j $ should have a ratio of $ x $ to $ y $ " (i.e., if $ a_i $ and $ a_j $ are the amounts of ingredient $ i $ and $ j $ in the potion respectively, then it must hold $ a_i/a_j = x/y $ ), where $ x $ and $ y $ are positive integers. However, it is guaranteed that the set of facts he remembers is sufficient to uniquely determine the original values $ r_i $ .

He decided that he will allow the students to pass the class as long as they submit a potion which satisfies all of the $ n-1 $ requirements (there may be many such satisfactory potions), and contains a positive integer amount of each ingredient.

Find the minimum total amount of ingredients needed to make a potion which passes the class. As the result can be very large, you should print the answer modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the minimum total amount of ingredients is $ 69 $ . In fact, the amounts of ingredients $ 1, 2, 3, 4 $ of a valid potion are $ 16, 12, 9, 32 $ , respectively. The potion is valid because

- Ingredients $ 3 $ and $ 2 $ have a ratio of $ 9 : 12 = 3 : 4 $ ;
- Ingredients $ 1 $ and $ 2 $ have a ratio of $ 16 : 12 = 4 : 3 $ ;
- Ingredients $ 1 $ and $ 4 $ have a ratio of $ 16 : 32 = 2 : 4 $ .

In the second test case, the amounts of ingredients $ 1, 2, 3, 4, 5, 6, 7, 8 $ in the potion that minimizes the total amount of ingredients are $ 60, 60, 24, 48, 32, 60, 45, 30 $ .

## 样例 #1

### 输入

```
3
4
3 2 3 4
1 2 4 3
1 4 2 4
8
5 4 2 3
6 4 5 4
1 3 5 2
6 8 2 1
3 5 3 4
3 2 2 5
6 7 4 3
17
8 7 4 16
9 17 4 5
5 14 13 12
11 1 17 14
6 13 8 9
2 11 3 11
4 17 7 2
17 16 8 6
15 5 1 14
16 7 1 10
12 17 13 10
11 16 7 2
10 11 6 4
13 17 14 6
3 11 15 8
15 6 12 8```

### 输出

```
69
359
573672453```

# 题解

## 作者：max67 (赞：7)

## 前言

~~wssb~~，这场 CF，A 题我 WA 了三次，C 题是 he 别人的，结果被查重了......（虽然说我 he 的那个人掉分了）然后 D 题想了个脑血檀算法，结果回去睡觉 $2$ 分钟否决掉。

第二天补题，D 题想了个 $O(n\sqrt n)$ 算法，想了两个小时终于想到了正解。 E 题考虑了三种算法，想了两个小时，结果答案是最后一种。然后卡常还卡了很久......

~~我怀疑我脑子有问题~~。

update on 20220328：修改了 $\log$ 和 $\operatorname{lcm}$

## 正文

### 题意简述

给你一颗有 $n$ 个点的树，每个点有个点权（设为 $val_i$），每条边有一个数对 $(a,b)$，设其两端分别为 $x$ 和 $y$，则必须满足：$val_x\times a=val_y\times b$。

现在要求所有 $val_i$ 都是整数，要求所有 $val_i$ 的和的最小值（输出答案与 $998244353$ 取模）。

$1\le n\le 2\times 10^5$

$1\le a,b\le n$

### 题解

考虑设 $val_1$ 为基底，则每个 $val_i$ 都可以表示如下形式：$val_i=val_1\times \frac{a_i}{b_i}$，其中 $\gcd(a_i,b_i)=1$。

那么若满足所有 $val_i$ 为整数，则必须满足 $\forall b_i,b_i|val_1$。因为要求 $val_1$ 最小，则最显然的取值为 $\operatorname{lcm} (b_1,b_2.....b_n)$。

因为对于所有比例的数都小于等于 $n$，所以我们求得的 $b_i$ 和 $a_i$ 可能会爆 $\text{long long}$。但因为所有比例的数都小于等于 $n$，所以我们可以用这个数的算术基本定理的形式表示：$p_1^{c_1}\times p_2^{c_2}......p_n^{c_n}$。（$c_1+c_2......+c_n\le \log_2^{n}$，即质因子数是 $\log_2^{n}$ 级别的。）

接下来考虑怎么求 $b_i$ 和 $c_i$。为了方便表示，我们用两条有向边代替无向边，边的权值为 $\frac{t_1}{v_1}$，边的两端为 $x,y$，表示 $val_x\times \frac{t_1}{v_1}=y$。

考虑他们在树上的位置。

[![qnGHwn.png](https://s1.ax1x.com/2022/03/21/qnGHwn.png)](https://imgtu.com/i/qnGHwn)


（pass：反向边未画出，字母（如 $a$）表示边（如 $(1,2)$ ）的分数。）

对于父节点 $x$ 和子节点为 $y$，设边权为 $z$，则有 $val_x\times z=val_y$。考虑不断递归下去，则 $\frac{a_y}{b_y}$ 为这个节点到根节点的路径上的分数的乘积。

因为每个数的质因子是 $\log_2^{n}$ 级别的，考虑构造一条链，那么 $b_n$ 拥有的质因子的数量最多为 $n\log_2^{n}$ 个，则总共拥有的质因子数大约为为 $n^2\log_2^{n}$ 个，显然空间会爆炸。

不妨换一种方法，我们不单独列出每个 $\frac{a_i}{b_i}$。我们在这颗树上用 $dfs$ 遍历，开一个数组记录当前节点到根节点的分母乘积的分解。那么每遍历到一个新的节点时，就把他的分解塞入数组中动态更新答案即可（因为求的是每个节点的值的分母的 $\operatorname{lcm}$，所以你可以在插入时暴力记录个数的最大值，因为 $\operatorname{lcm}(p_1^{c_1},p_1^{c_2})=p_1^{\max(c_1,c_2)} $。）

（如果你像我一样傻的话，你可能会用启发式合并找答案，不过这是完全没有必要的。考虑每遍历完一个新的子树，便删去这个子树的贡献即可。）

不过注意一个要点，也要考虑分子和分母的约分，这怎么办呢？我们把分子也分解插入到数组里。如果有负数，代表当前的分母没有这个因数，不用取。否则代表分母与分子约分后的结果。因为求的是每个节点的 $\operatorname{lcm}$，所以还是可以暴力取最大值。

考虑知道 $val_1$ 之后的情况，由于 $val_1\times \frac{a_i}{b_i}= val_i$ 在模意义下也成立，所以 $val_1$ 和 $\frac{a_i}{b_i}$ 都可以取模。

### 代码实现

* 预处理，我们设 $pre_i$ 表示 $i$ 与他最小的质因子相除的结果。因为欧拉筛：

```cpp
void Prepare(int n)
{
    pre[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!vis[i])p[++tot]=i,pre[i]=1;
        for(int j=1;j<=tot&&p[j]*i<=n;j++)
        {
            vis[i*p[j]]=1;pre[i*p[j]]=i;
            if(i%p[j]==0)break;
        }
    } 
}
```
* 中的 $i\times p[j]$ 的最小质因子是 $p[j]$，所以可以用欧拉筛转移。

其他就没有什么注意的了。

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define int long long 
#define pb push_back
using namespace std;
const int N=3e5+1e3,mod=998244353;
int power(int x,int y,int t=1){for(;y;y>>=1,x=x*x%mod)if(y&1)t=t*x%mod;return t;}
int inv(int x){return power(x%mod,mod-2);}
int gcd(int x,int y){return !y?x:gcd(y,x%y);}
int lcm(int x,int y){return x/gcd(x,y)*y;}

int p[N],tot,pre[N],vis[N];
void Prepare(int n)
{
    pre[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!vis[i])p[++tot]=i,pre[i]=1;
        for(int j=1;j<=tot&&p[j]*i<=n;j++)
        {
            vis[i*p[j]]=1;pre[i*p[j]]=i;
            if(i%p[j]==0)break;
        }
    } 
}
int val[N],ans[N];
//ans[i] 表示因数 i 的最大值，val[i] 表示当前因数 i 的个数
void add(int x){for(;x!=1;x=pre[x])ans[x/pre[x]]=max(ans[x/pre[x]],++val[x/pre[x]]);}
void del(int x){for(;x!=1;x=pre[x])val[x/pre[x]]--;}

vector<pair<int,pii> >g[N];
int v1[N];
//v1[i] 即题解中的 val[i]
void dfs1(int x,int fa)
{
    for(auto t:g[x])
    {
        int y=t.fi;pii z=t.se;
        if(y==fa)continue;
        add(z.se);del(z.fi);dfs1(y,x);del(z.se);add(z.fi);
    }
}
void dfs2(int x,int fa)
{
    for(auto t:g[x])
    {
        int y=t.fi;pii z=t.se;
        if(y==fa)continue;
        v1[y]=v1[x]*z.fi%mod*inv(z.se)%mod;
        dfs2(y,x);
    }
}
signed main()
{
    Prepare(N-100);
    int _;scanf("%lld",&_);
    while(_--)
    {
        int n;
        scanf("%lld",&n);
        for(int i=1;i<=n;i++)val[i]=ans[i]=0,v1[i]=1,g[i].clear();
        for(int i=1,x,y,a,b;i<n;i++)
        {
            scanf("%lld%lld%lld%lld",&x,&y,&a,&b);
            int d=gcd(a,b);a/=d;b/=d;
            g[x].pb({y,{b,a}});g[y].pb({x,{a,b}}); 
        }
        dfs1(1,0);
        for(int i=1;i<=n;i++)v1[1]=v1[1]*power(i,ans[i])%mod;
        dfs2(1,0);
        int res=0;
        for(int i=1;i<=n;i++)res=(res+v1[i])%mod;
        printf("%lld\n",res);
    }
    return 0;
}
```

## 后记

我麻了。

---

## 作者：Argon_Cube (赞：5)

这几次的 $\rm D$ 的难点好像只有码量大一些（其实也就 $\rm 2KB$）？

* **【题目链接】**

[Link:CF1654D](https://www.luogu.com.cn/problem/CF1654D)

* **【题目翻译】**

有一个长为 $n$ 的**正整数**序列 $a$，$a$ 中的数事先全部未知。给定 $n-1$ 个条件，第 $i$ 个条件形如 $\dfrac{a_i}{a_j}=\dfrac{x}{y}$。问题是，在满足这 $n-1$ 个条件的情况下，所有 $n$ 个数的和最小是多少？

答案对 $998244353$ 取模。

多组数据，数据满足：

$1\leq t\leq 10^4$，$1\leq \sum n\leq 2\times 10^5$，每个条件中 $i\neq j$ 且 $1\leq x,y\leq n$。输入只包含整数。

并且，设 $a$ 中的数之和为 $s$，则这 $n-1$ 个条件可以保证即使不使所有数的和最小化，$\dfrac s{a_i}$ 也唯一且大于 $0$。

* **【解题思路】**

我们可以把 $a_i$ 看作编号为 $i$ 的点，这 $n-1$ 个条件相当于在 $i$ 号点与 $j$ 号点之间连边。具体怎么连边，我们待会再讲。

1. 将每个条件视作一条无向边（忽略 $x,y$），连出来的一定是一棵树。

证明很简单。假如连出来的图不连通就无法让 $\dfrac s{a_i}$ 唯一。$n$ 个点 $n-1$ 条边，这不就是树吗？

2. 只要确定了一个数，其它的数即可确定。

显然只要确定了一个数，就可以沿着边推出其他数。

3. 其中一个数取到最小值等价于所有数的和最小。

可以知道，任意选定一个数，其它每一个数都与这个数成正比例关系。

现在我们的任务，就变成了让其中一个数最小化。我们就让 $a_1$ 最小化吧。

然后对于每一个询问，我们在 $i,j$ 间连**两条单向边**。对于从 $i$ 连到 $j$ 的边，我们让这条边的权值为 $\dfrac{a_j}{a_i}$，这是条件给出的定值。从 $j$ 到 $i$ 的边权值同理为 $\dfrac{a_i}{a_j}$。每一条边的权值意义是，终点的值是起点的多少倍。

注意，存分数要存分子和分母，而不是直接存浮点数，本题对于所有分数都是这么处理的。

然后，我们以 $1$ 为这棵树的根，做一遍 DFS。然后在遍历的过程中，我们就可以得到 $\dfrac{a_i}{a_1}$。显然，我们要让每一个 $a_i$ 都为整数，也就是说，设 $\dfrac{a_i}{a_1}=\dfrac cd$，其中后者是最简分数，有 $d|a_1$。

怎么算出 $a_1$？每遍历到一个点，就将分子分母质因数分解，算出要让这个点为整数，$a_1$ 中的每个质因子最少要多少个。然后对于每个质数取最大值，最后乘起来即可得到 $a_1$。

最后做一遍 DFS，递推出每个点的答案即可。这里不用质因数分解了，直接算分数在模意义下的值然后乘上去就行。

* **【代码实现】**

```cpp
#include <iostream>
#include <array>

using namespace std;

long long fast_pow(long long base,long long exp,long long moder)
{
    long long result;
    for(result=1;exp;exp&1?result=result*base%moder:true,base=base*base%moder,exp>>=1);
    return result;
}
inline long long inv(long long num,long long prime)
{
    return fast_pow(num,prime-2,prime);
}

struct edge
{
	int to,next,den,num;
};

array<int,200001> cnt,max_cnt,head;
array<edge,400000> edges;
int edgecnt;

inline void addedge(int from,int to,int num,int den)
{
	edges[++edgecnt]={to,head[from],den,num};
	head[from]=edgecnt;
}

void DFS_count(int root,int father)
{
	for(int i=head[root];i;i=edges[i].next)
	{
		if(edges[i].to==father)
			continue;
		int num=edges[i].num,den=edges[i].den;
		for(int i=2;i*i<=num;i++)
			while(num%i==0)
				--cnt[i],num/=i;
		if(num>1)
			--cnt[num];
		for(int i=2;i*i<=den;i++)
			while(den%i==0)
				++cnt[i],max_cnt[i]=max(max_cnt[i],cnt[i]),den/=i;
		if(den>1)
			++cnt[den],max_cnt[den]=max(max_cnt[den],cnt[den]);
		DFS_count(edges[i].to,root);
		num=edges[i].num,den=edges[i].den;
		for(int i=2;i*i<=num;i++)
			while(num%i==0)
				++cnt[i],num/=i;
		if(num>1)
			++cnt[num];
		for(int i=2;i*i<=den;i++)
			while(den%i==0)
				--cnt[i],den/=i;
		if(den>1)
			--cnt[den];
	}
}

long long DFS_sum(int root,int father,long long inital)
{
	long long total=inital;
	for(int i=head[root];i;i=edges[i].next)
	{
		if(edges[i].to==father)
			continue;
		total=(total+DFS_sum(edges[i].to,root,inital*edges[i].num%998244353*inv(edges[i].den,998244353)%998244353))%998244353;
	}
	return total;
}

int main(int argc,char *argv[],char *envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testcnt;
	cin>>testcnt;
	while(testcnt--)
	{
		edgecnt=0;
		int ncnt;
		cin>>ncnt;
		for(int i=0;i<=ncnt;i++)
			max_cnt[i]=cnt[i]=head[i]=0;
		for(int i=1;i<ncnt;i++)
		{
			int from,to,num,den;
			cin>>from>>to>>num>>den;
			addedge(from,to,den,num);
			addedge(to,from,num,den);
		}
		DFS_count(1,0);
		long long inital=1;
		for(int i=1;i<=ncnt;i++)
			if(max_cnt[i])
				inital=inital*fast_pow(i,max_cnt[i],998244353)%998244353;
		cout<<DFS_sum(1,0,inital)<<'\n';
	}
 	return 0;
}
 
```

---

## 作者：I_am_Accepted (赞：1)

### Preface

场上正解 FST 了……现在重写了，代码较短。

### Analysis

发现这个取模 $998,244,353$ 和 $\gcd$ 无法同时进行。

我们先设 $a_1=1$，然后通过题目所给的条件 DFS 得出每个药剂的量 $a_i=2^{c_{i,1}}3^{c_{i,2}}5^{c_{i,3}}7^{c_{i,4}}\dots $ **注意 $c_{i,j}$ 可为负**。

我们需要给所有的 $a_i$ **同时乘上一个数**使得每一个 $c_{i,j}$ 都**不为负数**。（其实就是通分）

所以，在 DFS 时**带模求出** $a_1,a_2,\dots,a_n$，同时**维护当前节点（药剂）的** $\{c\}$，并记录 $d_j=-\min_{i=1}^nc_{i,j}$。

由于带模乘法具有**分配律**，最终结果即为

$$\left(\sum\limits_{i=1}^{n}a_i\right)\cdot2^{d_1}\cdot3^{d_2}\cdot5^{d_3}\cdot7^{d_4}\cdot\dots$$

对 $998,244,353$ 的模数。

时间 $O(n+\sum\limits_{(x,y)\in E}\Omega(x)+\Omega(y))$

其中 $\Omega$ 表示[素因数个数函数](https://baike.baidu.com/item/%E7%B4%A0%E5%9B%A0%E6%95%B0%E4%B8%AA%E6%95%B0%E5%87%BD%E6%95%B0/18898050)，$x,y$ 为输入的**比值**。

### Detail

要**线性筛**素数预处理，同时求出每个数的最小素因数以便于分解。

当然，由于要计算有关模意义下比率的 $a_i$，我们要预处理**阶乘和阶乘的逆元**，以便 $O(1)$ 求逆元。

### Code

[就是挺短的，快来看我](https://codeforces.com/contest/1654/submission/151329693)

---

