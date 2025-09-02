# Galgame

## 题目背景

众所周知，as_lky 喜欢 Galgame。

## 题目描述

as_lky 搞到了很多 Galgame（真的很多！）。一款 Galgame 可以被描述为很多场景（Scene）的结合，它们形成了一棵 **以 1 为根** 的二叉树，每一个结点都是一个场景，一个结点的左儿子和右儿子分别对应在该场景选 A 选项和 B 选项能够到达的场景（可能会到达空场景，即游戏结束），我们称其为 A 场景和 B 场景。

as_lky 如下定义了两个不同的 Galgame 场景哪个更有趣（两款 Galgame 谁更为有趣也就取决于它们的初始场景谁更有趣）：

1. 如果这两个场景能够到达的场景总数（即通过任意选择能够到达的不同场景总数，包括该场景本身）不一样，那么能到达的场景数更多的那个更有趣；
2. 如果这两个场景的 A 场景不一样有趣，那么 A 场景更有趣的场景更有趣；
3. 否则这两个场景谁更有趣完全等价于他们 B 场景谁更有趣。

值得注意的是，空场景能到达的场景数被定义为 0。

![示例](https://cdn.luogu.com.cn/upload/image_hosting/4d2208qd.png)

例如，对于上图给出的例子（若无法正常查看请 `右键 -> 查看图像`），我们这样判定 1 和 7 这两个场景谁更有趣：

- 首先，1 和 7 能到达的场景数都是 6，因此我们首先尝试比较其 A 场景：2 和 8。
- 由于 2 和 8 能到达的场景数不同（分别是 3 和 2），则 2 场景比 8 场景更有趣；继而可以得到 1 场景比 7 场景更有趣。

as_lky 定义两个 Galgame 场景本质相同，当且仅当这两个场景都为空场景，或者它们的 A 场景本质相同且 B 场景本质相同。

as_lky 认为一款 Galgame 的有趣度是所有可能的、本质不同的、不及这款 Galgame 有趣的 Galgame 数量。现在 as_lky 给了你一款 Galgame，请告诉他这款 Galgame 的有趣度是多少。as_lky 觉得这个数字可能有些大，所以他想让你输出这个数字对 $998244353$ 取模的结果。

## 说明/提示

### 样例解释

样例一：下图分别给出了 as_lky 给你的 Galgame（左）和所有四种没有该 Galgame 有趣的 Galgame（右）：（若无法正常查看请 `右键 -> 查看图像`）

![示例](https://cdn.luogu.com.cn/upload/image_hosting/oxer1eac.png)

### 测试点约束

**本题采用捆绑测试。**

对于全部数据，有 $1\le n\le 10^6$，$0\le a_i,b_i\le n$。

每个子任务的具体限制见下表：

| 子任务编号 | 分值 | $n\le$ | 特殊性质 |
|:-:|:-:|:-:|:-:|
| 1 | 10 | $10$ | $\times$ |
| 2 | 20 | $5000$ | $\times$ |
| 3 | 30 | $10^6$ | $\surd$ |
| 4 | 40 | $10^6$ | $\times$ |

特殊性质：保证数据均匀随机生成，即 $n$ 给定时，若所有场景数为 $n$ 的本质不同 Galgame 共有 $S$ 种，则每种本质不同的 Galgame 出现概率均为 $\frac{1}{S}$。

**本题读入量较大，请使用较快的读入方式。**

## 样例 #1

### 输入

```
3
0 2
3 0
0 0
```

### 输出

```
4
```

## 样例 #2

### 输入

```
7
2 3
4 5
6 7
0 0
0 0
0 0
0 0
```

### 输出

```
410
```

## 样例 #3

### 输入

```
9
2 3
4 5
0 0
0 0
6 7
0 0
8 9
0 0
0 0
```

### 输出

```
5206
```

# 题解

## 作者：幻影星坚强 (赞：11)

对于没有其有趣的gal我们可以分成两类——节点个数不同的与节点个数相同的。

对于节点个数小于原树的二叉树，形态显然没有要求，所以就是[卡特兰数](https://baike.baidu.com/item/%E5%8D%A1%E7%89%B9%E5%85%B0%E6%95%B0/6125746?fr=aladdin)。于是我们能 $O(n)$ 求出所有节点个数不同的，没其有趣的gal。

对于节点个数相同的，那么考虑另外两个约束条件，他会先走 $A$ 再走 $B$ ，递归比较两个树的子树大小。在一棵不平衡的子树内，设原树 $A$ 边下的子树大小为 $S$ ，总子树大小为 $n$，那么没其有趣的gal数量就是 $\sum\limits_{i=0}^{S-1}f_i\times f_{n-i-1}$ ，其中 $f$ 代表卡特兰数。而如果前面走 $A$ 边的话剩下 $B$ 边的子树就可以随便放，再乘算上贡献即可。

```cpp
long long ksm(long long x, long long y)
{
	long long m = 1;
	for (; y > 0; y >>= 1)
	{
		if(y & 1)
		m = m * x % MOD;
		x = x * x % MOD;
	}
	return m;
}
long long C(long long x, long long y)
{
	return jc[x] * jcny[y] % MOD * jcny[x - y] % MOD;
}
long long siz[N];
void dfs(int o)
{
	siz[o] = 1;
	if(a[o])
	dfs(a[o]);
	if(b[o])
	dfs(b[o]);
	siz[o] += siz[a[o]] + siz[b[o]];
}
long long ans;
void dfs1(int o, long long mul)
{
	for (int i = 0; i < siz[a[o]]; ++ i)
	{
		(ans += mul * ktl[i] % MOD * ktl[siz[o] - 1 - i] % MOD) %= MOD;
	}//假如在这个节点左右两棵子树不平衡了就算上贡献
    //否则是平衡的，递归处理两个儿子
	if(a[o])
	dfs1(a[o], mul * ktl[siz[b[o]]] % MOD);//如果走A那么就不用考虑B在此刻是否平衡，反正肯定是不平衡的，所以B就可以随便放了
	if(b[o])
	dfs1(b[o], mul);
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i)
	{
		scanf("%d%d", &a[i], &b[i]);
	}
	jc[0] = jcny[0] = 1;
	for (int i = 1; i <= 2 * n; ++ i)
	{
		jc[i] = jc[i - 1] * i % MOD;
		jcny[i] = ksm(jc[i], MOD - 2);
	}
	ktl[0] = 1;
	for (int i = 1; i <= n; ++ i)
	{
		ktl[i] = (C(2 * i, i) - C(2 * i, i - 1) + MOD) % MOD;
	}//计算卡特兰数
	for (int i = 1; i < n; ++ i)
	{
		(ans += ktl[i]) %= MOD;
	}//算个数小于原gal的gal个数
	dfs(1);
	dfs1(1, 1);
	printf("%lld", ans);
}
```

幸运的是，这样做是 $O(n^2)$的。

@8fb8721ffd890897190482c717cea26c（已加密） 神仙提出了启发式合并的思想，我们计算贡献的式子是 $\sum\limits_{i=0}^{S-1}f_i\times f_{n-i-1}$，它是和A的子树的大小有关的，假如B的子树大小比A小通过B转移肯定更优，而事实上没其有趣的gal数量相当于总方案数减至少和其一样有趣的gal数量，那么就可以用 $f_n -\sum\limits_{i=S}^nf_i\times f_{n-i-1}$ 得到该子树的答案，时间复杂度和大部分启发式合并一样为 $O(nlogn)$

```cpp

void dfs1(int o, long long mul)
{
	if(siz[a[o]] <= siz[b[o]] + 1)
	for (int i = 0; i < siz[a[o]]; ++ i)
	{
		(ans += mul * ktl[i] % MOD * ktl[siz[o] - 1 - i] % MOD) %= MOD;
	}
	else
	{
		ans += ktl[siz[o]] * mul;
		for (int i = 0; i <= siz[b[o]]; ++ i)
		{
			(ans += mul * (-(ktl[i] % MOD * ktl[siz[o] - 1 - i] % MOD) + MOD) % MOD) %= MOD;
		}
	}
	if(a[o])
	dfs1(a[o], mul * ktl[siz[b[o]]] % MOD);
	if(b[o])
	dfs1(b[o], mul);
}
```


---

## 作者：Mivik (赞：5)


[欢迎到我的博客查看](https://mivik.gitee.io/2020/solution/mivik-newbie-and-chinos-contest-2020-solution-galgame/)

## Subtask 1

暴力枚举也许能过。

## Subtask 2

记 $f(x)$ 为和 x 这一二叉树结点数相同但更为无趣二叉树数目，则有：

$$
f(x)=f(lson(x))C_{size(rson(x))}+f(rson(x))+\sum_{i=0}^{size(lson(x))-1}C_i C_{size(x)-i-1}
$$

其中 $C_n$ 为卡特兰数。然后我们 $O(n^2)$ 计算即可。

## 满分做法

我们对上面的做法做一个优化：我们先预处理出卡特兰数列的自卷积，然后对于 $size(lson(x))\le size(rson(x))$ 的情况，我们和上面一样暴力算；然后对于 $size(lson(x))>size(rson(x))$ 的情况，我们从预处理出的卷积里面减去多算的部分。然后，注意到卡特兰数列的自卷积等于它本身（偏移了一位），因此我们连卷积都不需要计算了。具体的，设卡特兰数列的生成函数是 $H(x)$，我们有 $H(x)^2\cdot x+1=H(x)$，我们所需要的卡特兰数自卷积 $F(x)=H(x)^2$，那么有 $[x^i]F(x)=[x^i]\left(\frac{H(x)-1}{x}\right)=[x^{i+1}]H(x)$。

这样实际上是对的。我们对每一个点考虑它会对时间复杂度产生多大贡献：自下而上地，如果一个点贡献所在的子树的 $size$ 是我们决定计算的部分，那么整棵树的大小必定大于等于这个点所在子树大小的两倍，也就是说，一个点如果想对时间复杂度产生 $1$ 的贡献，则其所在子树大小至少会增大 2 倍。因此一个点最多对时间复杂度产生 $\log n$ 的贡献，则总时间复杂度最劣为 $O(n\log n)$。

[mivik.h](https://mivik.gitee.io/mivik.h)

[代码](https://paste.ubuntu.com/p/R2s83BNWVg/)


---

## 作者：under_the_time (赞：4)

## 题意

> 规定两棵无标号二叉树（可以为空）比较大小的方式如下：
>
> 1. 相同形态的树大小相同。
> 2. 如果节点个数不同，点数少的更小。
> 3. 否则左子树不同时按照左子树比大小。
> 4. 否则按照右子树比大小。
>
> 给定一棵 $n$ 个节点的二叉树，求有多少棵无标号非空二叉树严格小于它。答案对 $998244353$ 取模。$n\le10^6$。

## 思路

显然所有节点数 $<n$ 的二叉树都是满足条件的，这部分二叉树一共有 $\sum_{i=1}^{n-1}C_i$ 个，其中 $C_i$ 表示卡特兰数第 $i$ 项。而节点数 $>n$ 的二叉树显然都不合法，现在考虑节点数恰好为 $n$ 的所有二叉树。

令原树中 $i$ 的子树大小为 $siz(i)$。先考虑根节点的情况，令根节点为 $u$，左右儿子分别为 $l,r$；那么对于左子树大小 $<siz(l)$ 的二叉树也都是合法的，转化为开头的情况，但是还要算上右儿子的形态种数，于是此时对答案的贡献即为 $\sum^{siz(l)-1}_{i=0}C_i\times C_{siz(u)-i+1}$。然后考虑按照限制递归下去，若递归到左子树就表示以左子树的大小为标准，与右子树的形态无关，于是在左子树中计算得到的答案都要乘上 $C_{siz(r)}$ 的系数；若递归到右子树就表示以右子树的大小为标准，意味着左子树形态已经固定，于是直接递归到右儿子中进行处理即可。

但这样复杂度是 $O(n^2)$ 的，考虑一棵“左偏”的二叉树，即左子树大小级别为 $O(n)$，每次按照左子树大小计算贡献显然会被卡满。于是我们考虑当左子树大小大于右子树时，使用右子树的大小计算答案。对于节点 $u$，以它为根的二叉树一共有 $C_{siz(u)}$ 个，正难则反，比原树小的二叉树相当于总方案数减去不比原树小的二叉树。于是当用右子树的大小计算贡献时，贡献即为 $C_{siz(u)}-\sum^{siz(r)}_{i=0}C_i\times C_{siz(r)-i-1}$。这样我们每一轮贡献至多计算 $siz(u)/2$ 次轮，而随着深度增加子树的大小以对数级别下降，于是总复杂度优化至 $O(n\log n)$。

---

这里额外补充一下卡特兰数，即 $C_i$。它的通项公式为
$$
C_i=\binom {2n}n-\binom {2n}{n-1}
$$
我们考虑一个模型：从 $(0,0)$ 出发，沿着格路向右向上走到 $(n,n)$，在任意时刻 $y$ 坐标始终不大于 $x$ 坐标，求所有的方案数。总方案数即为 $C_n$。其中，$y$ 坐标始终不大于 $x$ 坐标的限制，相当于路径始终不能穿过与 $x=y$ 这条直线。

![](https://cdn.luogu.com.cn/upload/image_hosting/exjk3kn6.png)

其中蓝线为分界线，绿线即为一条合法路径。若不考虑限制，那么总方案数相当于在一共 $2n$ 步中，选出 $n$ 步向上走，剩余 $n$ 步向右走，方案数即为 $\binom{2n}n$。

![](https://cdn.luogu.com.cn/upload/image_hosting/6v7ngrc0.png)

对于图中红色的线即为一条不合法的路径。我们现在令作一条过 $(0,n)$ 斜率为 $1$ 的线（图中天蓝色的线），所有不合法的路径都会与这条斜线接触。我们将不合法路径以天蓝色的线为对称轴作对称图形（图中橙色的线），这样不合法路径的终点变为 $(n-1,n+1)$，这样不合法路径的总方案数为：一共 $2n$ 步中选择 $n-1$ 步向右走，剩余 $n+1$ 步向上走，即 $\binom{2n}{n-1}$。合法路径 = 总路径 - 不合法路径，于是就可以得出 $C_n=\binom{2n}n-\binom{2n}{n-1}$。

它的递推公式为
$$
C_n=[n=0]+\sum_{j=0}^{n-1}C_j\times C_{n-j-1}
$$
我们再考虑一个模型，也是最常用的模型：$n$ 个点无标号二叉树的个数。首先若 $n=0$ 那么空树即为一个答案，否则考虑枚举左子树的大小，用乘法原理和加法原理得出答案。于是就得到了 $C$ 的递推公式。卡特兰数另外的模型还包括：

- $n$ 个顶点的凸多边形进行三角划分的方案数。
- 有一个空栈，进栈 $1,2,\cdots,n$，求出栈序列的个数。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5, P = 998244353; 
int fac[maxn << 1], inv[maxn << 1], n;
int qp(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (1ll * x * x) % P)
        if (y & 1) res = (1ll * res * x) % P;
    return res;
}
void init() {
    fac[0] = 1, inv[0] = 1;
    for (int i = 1; i <= (n << 1); i ++)
        fac[i] = (1ll * fac[i - 1] * i) % P, inv[i] = qp(fac[i], P - 2);
}
int C(int x, int y) {
    if (x < y) return 0;
    int p = (1ll * fac[x] * inv[y]) % P;
    return (1ll * p * inv[x - y]) % P;
}
int Cat(int x) { 
    if (x == 0) return 1;
    return ((C(x << 1, x) - C(x << 1, x - 1)) % P + P) % P; 
}
int siz[maxn], son[maxn][2];
void dfs1(int u) { // 求出子树大小
    if (!u) return ;
    dfs1(son[u][0]), dfs1(son[u][1]);
    siz[u] = 1 + siz[son[u][0]] + siz[son[u][1]];
}
int ans = 0;
void dfs2(int u, int k) { // 统计答案，其中 k 为递归中的系数
    if (!u) return ;
    if (siz[son[u][0]] <= siz[son[u][1]] + 1) // 按照子树大小使用公式计算
        for (int i = 0; i < siz[son[u][0]]; i ++)
            ans = (ans + (1ll * ((1ll * k * Cat(i)) % P) * Cat(siz[u] - i - 1)) % P) % P;
    else {
        int tmp = Cat(siz[u]);
        for (int i = 0; i <= siz[son[u][1]]; i ++)
            tmp = ((tmp - (1ll * Cat(i) * Cat(siz[u] - i - 1)) % P) % P + P) % P;
        // cout << tmp << '\n';
        ans = (ans + (1ll * k * tmp) % P) % P;
    }
    // cout << u << ' ' << ans << ' ' << k << '\n';
    dfs2(son[u][0], (1ll * k * Cat(siz[son[u][1]])) % P), dfs2(son[u][1], k);
}
int main() {
    scanf("%d", &n); init();
    for (int i = 1; i <= n; i ++)
        scanf("%d %d", &son[i][0], &son[i][1]);
    int self = 0;
    for (int i = 1; i < n; i ++) // 注意原题要求非空二叉树，所以答案不能统计空树的情况，故从 i=1 开始枚举。
        self = (1ll * self + Cat(i)) % P;
    dfs1(1), dfs2(1, 1); printf("%d", (1ll * self + 1ll * ans) % P);
    return 0;
}
```

---

## 作者：_Diu_ (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P7118)

**upd on `2022.07.25`：修改了原题解中的 `Latex` 错误。**

## Catalan

熟记卡特兰数的大奆都知道，卡特兰数还有一个性质。

- 性质 1.0：$C_i$ 可以表示节点数为 $i$ 时二叉树构造的方案数。

由此，我们可以很自然的想到 dp。

设 $siz_i$ 表示子树 $i$ 节点个数。

设 $f_i$ 表示比子树 $i$ 更无趣且节点数与子树 $i$ 相同的二叉树个数。

显然，答案就是 $f_1+\sum_{i=1}^{siz_1-1}C_i$。

转移方程也很容易求出来，

当该左儿子节点数量小于原子树左儿子节点个数时，右儿子随便选，

当该左儿子节点数量等于原子树左儿子节点数时，如果原左儿子更有趣，那么右儿子还是可以随便选，否则原右儿子要更有趣。

$f_u=\sum_{i=0}^{siz_{ls}-1}C_iC_{siz_u-i}+f_{ls}C_{siz_{rs}+f_{rs}}$。

然后预处理卡特兰数就可以 $O(n^2)$ 实现了，期望得分： 30pts。

## 优化

观察到上面的转移方程中时间复杂度最高的部分：

令 $w_u\sum_{i=0}^{siz_{ls}-1}C_iC_{siz_u-i}$

如果我们能够有效降低这个部分的时间，就能过掉这一题。

我们发现，这个柿子很像两个东西：一个是下面的性质，还有一个是多项式相乘。

- 性质 2.0：$C_n=\sum_{i=0}^{n-1}C_iC_{n-1-i}$。

那我们不妨设卡特兰数的生成函数为 $C(x)$。

很容易可以得到下面这个柿子：

$C^2(x)=xC(x)+1$。

同时，我们可以用另一种方式来表示出要求的东西。

$w_u=\sum_{i=0}^{siz_u-1}C_iC_{siz_u-i}-\sum_{i=siz_{ls}}^{siz_u-1}C_iC_{siz_u-i}$。

$=C_{siz_u}-\sum_{i=siz_{ls}}^{siz_u-1}C_iC_{siz_u-i}$。

每次在求 $f_u$ 时，在两种方式中选一个时间复杂度最小的就可以了。

最后每一次递归时间复杂度最劣是 $O(\lceil\frac n2\rceil)$。

总时间复杂度为 $O(n\log n)$

## code

具体见代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,p=998244353;
int n,c[N],siz[N],ls[N],rs[N],f[N],ans,rt;
bool fa[N];
int qpow(int x,int y){
    int mul=1;
    for(;y;y>>=1,x=x*x%p)if(y&1)mul=mul*x%p;
    return mul;
}
void dfs(int u){
    siz[u]=1;
    if(ls[u])dfs(ls[u]),siz[u]+=siz[ls[u]];
    if(rs[u])dfs(rs[u]),siz[u]+=siz[rs[u]];
}
void dfs1(int u){
    if(!ls[u]&&!rs[u])return;
    if(ls[u])dfs1(ls[u]);
    if(rs[u])dfs1(rs[u]);
    f[u]=f[ls[u]]*c[siz[rs[u]]]%p+f[rs[u]];
    if(siz[ls[u]]<=siz[rs[u]]){//这里是判断正着扫快还是反着扫快
        for(int i=0;i<siz[ls[u]];i++)f[u]+=c[i]*c[siz[u]-i-1]%p;
        f[u]%=p;
    }else{
        f[u]=f[u]+c[siz[u]];
        for(int i=siz[ls[u]];i<siz[u];i++)f[u]=(f[u]-c[i]*c[siz[u]-i-1]%p+p)%p;
    }
}
inline char nc(){static char buf[1000010],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000010,stdin),p1==p2)?EOF:*p1++;}
//#define nc getchar
inline int read(){register int s=0,w=0;static char ch=nc();for(;!isdigit(ch);)ch=nc();for(;isdigit(ch);){s=(s<<1)+(s<<3)+(ch^48);ch=nc();}return w?-s:s;}
signed main(){
    n=read();
    for(int i=1;i<=n;i++)ls[i]=read(),rs[i]=read(),fa[ls[i]]=fa[rs[i]]=1;
    c[0]=c[1]=1;
    for(int i=2;i<=n;i++)c[i]=c[i-1]*(4*i-2)%p*qpow(i+1,p-2)%p;
    for(int i=1;i<=n;i++)rt=(fa[i]?rt:i);
    dfs(rt);
    dfs1(rt);
    int ans=f[rt];
    for(int i=1;i<n;i++)ans+=c[i];
    ans%=p;
    printf("%lld\n",ans);
}
```

---

## 作者：Linge_Zzzz (赞：1)

分析题目。本题中 $H_n$ 代表卡特兰数。

一个经典结论是 $n$ 个节点的不同二叉树个数是 $H_n$。

首先，若一个二叉树的节点数小于给定的节点数，那么这个二叉树一定劣于给定的二叉树，所以答案要加上 $\sum_{i=1}^{n-1}H_i$。

其次，讨论两棵树节点个数相同的情况。

我们假设判断两棵树哪棵更劣当前判断到了节点 $p$，那么要让当前二叉树比给定二叉树劣，共有两种情况：

- $p$ 的左儿子节点数小于给定树中 $p$ 左儿子的节点数。
- $p$ 的左儿子节点数等于给定树中节点数，转化问题为 $p=rs_p$ 的情况。

计算第一种情况对答案的贡献，枚举左子树节点数有 $\sum_{i=0}^{siz_{ls_p}-1} H_iH_{siz_p-1-i}$。

计算第二种情况对答案的贡献，根据乘法原理，其对右子树的答案会乘上 $H_{siz_{ls_p}}$。

所以我们可以写出如下的 $O(n^2)$ 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
int n,l[N],r[N],ans;
int h[N],inv[N];
void init(int n){
	inv[0]=inv[1]=1;
	for(int i=2;i<=n+1;i++)inv[i]=(-inv[mod%i]*(mod/i)%mod+mod)%mod;
	h[0]=1;
	for(int i=1;i<=n;i++)h[i]=h[i-1]*(4*i-2)%mod*inv[i+1]%mod;
}
int siz[N];
void dfs(int p,int v){
	if(!p)return;
	siz[p]=1;
	dfs(r[p],v);
	dfs(l[p],v*h[siz[r[p]]]%mod);
	siz[p]+=siz[l[p]]+siz[r[p]];
	for(int i=0;i<siz[l[p]];i++)ans=(ans+h[i]*h[siz[p]-1-i]%mod*v%mod)%mod;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>l[i]>>r[i];
	init(n);
	for(int i=1;i<n;i++)ans=(ans+h[i])%mod;
	dfs(1,1);
	cout<<ans<<endl;
	return 0;
}
```

显然过不了，考虑优化。

发现复杂度瓶颈在于计算 $\sum_{i=0}^{siz_{ls_p}-1} H_iH_{siz_p-1-i}$，其与左子树节点数有关，结合二叉树的性质，我们可以使用启发式合并的 Trick。

具体地，我们考虑如何从右子树大小得到这个答案。使用所有的方案数减去当前树比给定树相等或优的方案：$H_{siz_p}-\sum_{i=0}^{siz_{rs_p}}H_iH_{siz_p-1-i}$。

我们比较 $siz_{ls_p}$ 与 $siz_{rs_p}$，选择更小的一个进行计算。

这么做的复杂度是 $O(n\log n)$，复杂度参考启发式合并。一个节点没对复杂度产生一次贡献，所在的子树大小至少增加一倍。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
int n,l[N],r[N],ans;
int h[N],inv[N];
void init(int n){
	inv[0]=inv[1]=1;
	for(int i=2;i<=n+1;i++)inv[i]=(-inv[mod%i]*(mod/i)%mod+mod)%mod;
	h[0]=1;
	for(int i=1;i<=n;i++)h[i]=h[i-1]*(4*i-2)%mod*inv[i+1]%mod;
}
int siz[N];
void dfs(int p,int v){
	if(!p)return;
	siz[p]=1;
	dfs(r[p],v);
	dfs(l[p],v*h[siz[r[p]]]%mod);
	siz[p]+=siz[l[p]]+siz[r[p]];
	if(siz[l[p]]<=siz[r[p]])
		for(int i=0;i<siz[l[p]];i++)ans=(ans+h[i]*h[siz[p]-1-i]%mod*v%mod)%mod;
	else{
		int sum=h[siz[p]];
		for(int i=0;i<=siz[r[p]];i++)sum=(sum-h[i]*h[siz[p]-1-i]%mod)%mod;
		sum=(sum+mod)%mod;
		ans=(ans+sum*v%mod)%mod; 
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>l[i]>>r[i];
	init(n);
	for(int i=1;i<n;i++)ans=(ans+h[i])%mod;
	dfs(1,1);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：bmatrix (赞：1)

[题面](https://www.luogu.com.cn/problem/P7118)

题意很清楚，就不复述了。

不难发现，我们首先要求出场景数小于给定 galgame 的 galgame 数量，于是我们需要求出场景数 $=i$ 的 galgame 数量，设为 $f_i$。

考虑根节点，当 A 场景大小为 $j$ 时，B 场景的大小为 $i-j-1$。枚举每个 $j$，不难得到 $f_i=\sum\limits_{j=0}^{i-1}f_j\times f_{i-j-1}$，显然这就是卡特兰数的递推式。对于卡特兰数我们有通项公式 $f_i=\dfrac{\binom{2i}{i}}{i+1}=\dfrac{(2i)!}{i!\,(i+1)!}$，因此我们可以 $O(n)$ 预处理出每个卡特兰数。

接下来考虑场景数相等的情况，这种情况也可以分为两种：A 场景不同，A 场景相同。

对于 A 场景相同的情况，直接完全交给 B 场景变为子问题即可。

对于 A 场景不同的情况，B 场景可以是任何结构。设 $m$ 为 A 场景的大小，先考虑大小 $<m$ 的，这部分贡献是 $\sum\limits_{j=0}^{m-1}f_j\times f_{n-i-1}$；对于大小 $=m$ 的情况，递归变成子问题，再乘上 B 场景的情况数即可。

尴尬的是这种方法是 $O(n^2)$ 的，无法通过本题。

我们发现瓶颈在于 $\sum\limits_{j=0}^{m-1}f_j\times f_{n-i-1}$，这个东西就是卡特兰数的递推式少了几项。不难发现 $\sum\limits_{j=0}^{m-1}f_j\times f_{n-i-1}=f_n-\sum\limits_{j=0}^{n-m}f_j\times f_{n-i-1}$，于是每个子问题的操作次数都可以控制在 $\left\lceil\dfrac{n}{2}\right\rceil$ 以内（$n$ 为子任务规模），使用启发式合并，时间复杂度降到 $O(n\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define rep(i, s, e) for(int i = s, i##E = e; i <= i##E; ++i)
#define per(i, s, e) for(int i = s, i##E = e; i >= i##E; --i)
#define F first
#define S second
#define int ll
#define gmin(x, y) (x = min(x, y))
#define gmax(x, y) (x = max(x, y))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double f128;
typedef pair<int, int> pii;
constexpr int N = 1e6 + 5, p = 998244353;
int n, frac[N * 2], inv[N * 2], h[N], s[N], sz[N], ans;
pii a[N];
int qp(int a, int b) {
    int res = 1;
    for(; b; b >>= 1, a = a * a % p)
        if(b & 1) res = res * a % p;
    return res; 
}
void init() {
    cin >> n;
    rep(i, 1, n) cin >> a[i].F >> a[i].S;
    frac[0] = 1;
    rep(i, 1, n * 2) frac[i] = frac[i - 1] * i % p; // 预处理阶乘
    inv[n * 2] = qp(frac[n * 2], p - 2);
    per(i, n * 2 - 1, 0) inv[i] = inv[i + 1] * (i + 1) % p; // 预处理阶乘的逆元
    rep(i, 0, n) h[i] = frac[i * 2] * inv[i] % p * inv[i + 1] % p; // 预处理卡特兰数
}
void dfs(int u) { // 预处理子树大小
    sz[u] = 1;
    if(a[u].F) dfs(a[u].F), sz[u] += sz[a[u].F];
    if(a[u].S) dfs(a[u].S), sz[u] += sz[a[u].S];
}
int solve(int u) {
    int ans = 0;
    if(a[u].F) {
        if(sz[a[u].F] <= sz[a[u].S]) { // 启发式合并
            rep(i, 0, sz[a[u].F] - 1)
                (ans += h[i] * h[sz[u] - i - 1]) %= p;
        } 
        else {
            ans = (ans + h[sz[u]]) % p;
            rep(i, 0, sz[a[u].S])
                ans = ((ans - h[i] * h[sz[u] - i - 1]) % p + p) % p;
        }
        (ans += solve(a[u].F) * h[sz[a[u].S]]) %= p; // 递归变成子问题
    }
    if(a[u].S) (ans += solve(a[u].S)) %= p;
    return ans;
}
signed main() {
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
#endif
    init();
    dfs(1);
    rep(i, 1, n - 1) (ans += h[i]) %= p;
    cout << (ans + solve(1)) % p << endl;
    return 0;
}
```



---

## 作者：D2T1 (赞：1)

引理：$n$ 个节点的区分左右儿子的无标号二叉树个数为 $C(n)$（$C(n)$ 为卡特兰数）。

设题目给定二叉树为 $T$，考虑什么样的二叉树能够对答案产生贡献。

- 结点个数 $<n$，这部分答案为 $\sum_{i=1}^{n-1}C(i)$。
- 结点个数 $=n$，两边儿子子树大小也与 $T$ 根节点两边儿子子树大小相同。此时分为两种：
	- 左儿子子树小于 $T$ 根节点左儿子子树，发现这个就是一个子问题，递归求解，方案数要乘上 $C(siz_{Rchild})$。
	- 左儿子子树等于 $T$ 根节点左儿子子树，右儿子子树小于 $T$ 根节点右儿子子树，递归求解。
- 结点个数 $=n$，左儿子子树大小小于 $T$ 根节点左儿子子树大小。设 $T$ 根节点左儿子子树大小为 $p$，右儿子子树大小为 $q$，此时的答案为 $\sum_{i=1}^{p}C(p-i)C(q+i)$。这一部分如果暴力做是可以卡到 $O(n^2)$ 的，考虑优化：
	- 若 $p\leq q$，直接这么算。
	- 否则，我们有 $C(p+q+1)=\sum_{i=0}^{p+q}C(i)C(p+q-i)$，答案为 $C(p+q+1)-\sum_{i=0}^{q}C(p+i)C(q-i)$
	- 发现每次大小至少减半，复杂度降为 $O(n\log n)$。

```cpp
//P7118 
#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 10;
int n, siz[N], a[N], b[N];
typedef long long ll;
const ll P = 998244353;
ll inv[N], C[N], ans;

void dfs(int x){
	siz[x] = 1;
	if(a[x]){
		dfs(a[x]);
		siz[x] += siz[a[x]];
	}
	if(b[x]){
		dfs(b[x]);
		siz[x] += siz[b[x]];
	}
}

ll calc(int x){
	if(!x){
		return 0;
	}
	ll res = (calc(a[x]) * C[siz[b[x]]] + calc(b[x])) % P;
	int p = siz[a[x]], q = siz[b[x]];
	if(p <= q){
		for(int i = 1; i <= p; ++ i){
			res = (res + C[p-i] * C[q+i]) % P;
		}
	} else {
		res = (res + C[p+q+1]) % P;
		for(int i = 0; i <= q; ++ i){
			res = (res - C[p+i] * C[q-i] % P + P) % P;
		}
	}
	return res;
}

int main(){
	inv[1] = C[0] = 1;
	for(int i = 2; i < N; ++ i){
		inv[i] = P - (ll)(P / i) * inv[P%i] % P;
		C[i-1] = C[i-2] * (4*i-6) % P * inv[i] % P;
	}
	scanf("%d", &n);
	for(int i = 1; i <= n; ++ i){
		scanf("%d%d", &a[i], &b[i]);
	}
	dfs(1);
	for(int i = 1; i < n; ++ i){
		ans = (ans + C[i]) % P;
	}
	printf("%lld\n", (ans + calc(1)) % P);
	return 0;
}
```

---

## 作者：jasonliujiahua (赞：0)

# P7118

[题目传送门](https://www.luogu.com.cn/problem/P7118)
## 题目分析：
### Step 1：卡特兰数与二叉树
这里先稍稍说一下卡特兰数的一个应用：$Cat_n$ 可以表示 $n$ 个点构成的二叉树的个数。

#### 证明：
考虑 $n$ 个节点的二叉树的中序遍历，这是一个长度为 $n$ 的序列。显然根在该序列中的位置**决定**了这个二叉树的形态，因此对于每一个位置 $i$ 都考虑节点 $i$ 作为根节点时，$i$ 将这个序列分为了左右两个部分，即左右儿子，这就变成了一个子问题。综上（当然，还有加法原理和乘法原理），$n$ 个点构成的二叉树的个数 $f_n$ 有如下递归式：
$$f_n=\sum_{i=0}^{n} f_i\times f_{n-i-1}$$
同时由 $f_0=1$（由于一颗二叉树的左右儿子可以为空，因此规定空树也是一棵树）可知：$f_n$ 和 $Cat_n$ 的边界和递归式一样，因此 $f_n=Cat_n$。

### Step 2：朴素解法
接下来看这道题。

可以发现若一颗树对答案有贡献，必然是以下三种情况之一：
- 该树结点数小于 $n$，此时贡献为 $\sum_{i=1}^{sz(u)-1} Cat_i$。
- 该树结点数等于 $n$，其左子树小于给出的左子树，此时右子树任意，有两种情况：
	- 左子树大小等于给出左子树，此时贡献为 $f_{ls_u}\times Cat_{sz(rs_u)}$。
	- 左子树大小小于给出左子树，此时贡献为 $\sum_{i=1}^{sz(ls_u)-1} Cat_i\times Cat_{sz_u-i-1}$。
- 该树结点数等于 $n$，其左子树完全等于给出的左子树，此时右子树小于给出右子树，对答案贡献为 $f_{rs_u}$。

这里为了方便转移，将 $f_u$ 定义为：**比以 $u$ 为根的子树小，且大小一样的树的个数**。因此答案就是：
$$f_1+\sum_{i=1}^{n-1} Cat_i$$
综上，有转移方程：
$$f_u=f_{ls_u}\times Cat_{sz(rs_u)}+f_{rs_u}+\sum_{i=0}^{sz(ls_u)-1}Cat_i\times Cat_{sz(u)-i-1}$$

### Step 3：启发式合并
上述转移方程的瓶颈在于 $\sum_{i=0}^{sz(ls_u)}Cat_i\times Cat_{sz(u)-i-1}$，可以考虑启发式合并进行优化。由于
$$\sum_{i=0}^{sz(ls_u)-1}Cat_i\times Cat_{sz(u)-i-1}$$
$$=\sum_{i=0}^{sz(u)}Cat_i\times Cat_{sz(u)-i-1}-\sum_{i=sz(ls_u)}^{sz(u)}Cat_i\times Cat_{sz(u)-i-1}$$
$$=Cat_{sz(u)}-\sum_{i=sz(ls_u)+1}^{sz(u)}Cat_i\times Cat_{sz(u)-i-1}$$
因此每次考虑 $sz(ls_u)$ 和 $sz(u)-sz(ls_u)$ 的大小关系，选取小的那个暴力算即可。

## 参考代码：

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+10,p=998244353;
int n,ans,ls[maxn],rs[maxn],sz[maxn],inv[maxn],cat[maxn],f[maxn];
void init()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>ls[i]>>rs[i];
	for(int i=1;i<=n+1;i++)
	{
		if(i==1) inv[i]=1;
		else inv[i]=(p-p/i)*inv[p%i]%p; 
	}
	cat[0]=1;
	for(int i=1;i<=n;i++) cat[i]=cat[i-1]*(4*i-2)%p*inv[i+1]%p;
	for(int i=1;i<n;i++) ans=(ans+cat[i])%p;
}
void dfs1(int u)
{
	sz[u]=1;
	if(ls[u]) dfs1(ls[u]);
	if(rs[u]) dfs1(rs[u]);
	sz[u]+=sz[ls[u]]+sz[rs[u]];
}
void dfs(int u)
{
	if(ls[u]) dfs(ls[u]);
	if(rs[u]) dfs(rs[u]);
	f[u]=(f[ls[u]]*cat[sz[rs[u]]]%p+f[rs[u]])%p;
	if(sz[ls[u]]*2<sz[u])
		for(int i=0;i<sz[ls[u]];i++) f[u]=(f[u]+cat[i]*cat[sz[u]-i-1]%p)%p;
	else
	{
		f[u]=(f[u]+cat[sz[u]])%p;
		for(int i=sz[ls[u]];i<=sz[u];i++) f[u]=(f[u]-cat[i]*cat[sz[u]-i-1]%p+p)%p;
	}
}
signed main()
{
	init(); 
	dfs1(1);
	dfs(1); 
	cout<<(f[1]+ans)%p;
	return 0;
}
```

---

