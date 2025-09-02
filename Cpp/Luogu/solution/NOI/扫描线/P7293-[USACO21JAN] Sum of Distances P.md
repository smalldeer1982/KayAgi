# [USACO21JAN] Sum of Distances P

## 题目描述

Bessie 有一些无向连通图 $G_1,G_2,…,G_K$（$2≤K≤5⋅10^4$）。对于每一个 $1≤i≤K$，$G_i$ 有 $N_i$（$N_i≥2$）个编号为 $1…N_i$ 的结点与 $M_i$（$M_i≥N_i−1$）条边。$G_i$ 可能含有自环，但同一对结点之间不会存在多条边。 现在 Elsie 用 $N_1⋅N_2⋯N_K$ 个结点建立了一个新的无向图 $G$，每个结点用一个 $K$ 元组 $(j_1,j_2,…,j_K)$ 标号，其中 $1≤j_i≤N_i$。若对于所有的 $1≤i≤K$，$j_i$ 与 $k_i$ 在 $G_i$ 中连有一条边，则在 $G$ 中结点 $(j_1,j_2,…,j_K)$ 和 $(k_1,k_2,…,k_K)$ 之间连有一条边。 定义 $G$ 中位于同一连通分量的两个结点的 *距离* 为从一个结点到另一个结点的路径上的最小边数。计算 $G$ 中结点 $(1,1,…,1)$ 与所有与其在同一连通分量的结点的距离之和，对 $10^9+7$ 取模。

## 说明/提示

#### 样例 1 解释

$G$ 包含 $2⋅4=8$ 个结点，其中 $4$ 个结点不与结点 $(1,1)$ 连通。有 $2$ 个结点与 $(1,1)$ 的距离为 $1$，$1$ 个结点的距离为 $2$。所以答案为 $2⋅1+1⋅2=4$。 

#### 样例 2 解释

$G$ 包含 $4⋅6⋅7=168$ 个结点，均与结点 $(1,1,1)$ 连通。对于每一个 $i∈[1,7]$，与结点 $(1,1,1)$ 距离为 $i$ 的结点数量为下列数组中的第 $i$ 个元素：$[4,23,28,36,40,24,12]$。

#### 测试点特性

 - 测试点 $3-4$ 满足 $∏N_i≤300$。
 - 测试点 $5-10$ 满足 $∑N_i≤300$。
 - 测试点 $11-20$ 没有额外限制。

供题：Benjamin Qi 

## 样例 #1

### 输入

```
2

2 1
1 2

4 4
1 2
2 3
3 4
4 1```

### 输出

```
4```

## 样例 #2

### 输入

```
3

4 4
1 2
2 3
3 1
3 4

6 5
1 2
2 3
3 4
4 5
5 6

7 7
1 2
2 3
3 4
4 5
5 6
6 7
7 1```

### 输出

```
706```

# 题解

## 作者：panyf (赞：14)

简单的线性做法。

从新图的起点走到 $(a_1,a_2...a_k)$，相当于在 $k$ 张图上同时从 $1$ 走到 $a_i$。

如果某张图比其他图先走到，那么这个点可以任选一条经过它的边反复横跳。

所以只需要保证每张图上从 $1$ 走到 $a_i$ 距离的奇偶性相同。

首先通过 bfs，预处理每张图上 $1$ 到所有点的长度为奇数和偶数的最短路。

记 $ji_i$ 为奇数最短路，$ou_i$ 为偶数最短路，若不存在则为 $\inf$。

则新图的起点到 $(a_1,a_2...a_k)$ 的距离，等于 $\min(\max(ji_{a_i}),\max(ou_{a_i}))$。

这个式子不好处理，通过 $a+b=\min(a,b)+\max(a,b)$，转化为 $\max(ji_{a_i})+\max(ou_{a_i})-\max(\max(ji_{a_i},ou_{a_i}))$。

将三部分分别计算，每次分别记 $w_i=ji_i,ou_i,\max(ji_i,ou_i)$。

考虑对于每个点 $j$，求出 $j\in a_i$，且 $w_j=\max(w_{a_i})$ 的方案数。

发现这样会算重，考虑对于相同的 $w_j$，按所属图的编号为第二关键字比较。

于是只需要将所有点按 $w_j$ 为第一关键字，图的编号为第二关键字排序，因为值域是点数级别，所以这部分复杂度是线性。

然后按顺序依次加入每个点，加入属于图 $k$ 的点 $j$ 时的方案数，就是除 $k$ 以外所有图已经被加入的点的个数的乘积。

预处理乘法逆元可以 $O(1)$ 加点。

总复杂度线性。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+3,P=1e9+7;
basic_string<int>v[3][N+1];
int iv[N],a[N],o,u;
void in(){
	int n,m,i,j;
	basic_string<int>ji,ou;
	vector<basic_string<int>>g;
	queue<int>q;
	scanf("%d%d",&n,&m),ji.assign(n+1,N),ou.assign(n+1,N),g.resize(n+1);
	while(m--)scanf("%d%d",&i,&j),g[i]+=j,g[j]+=i;
	q.push(1),ou[1]=0;
	while(q.size()){//bfs
		i=q.front(),q.pop();
		if(i>n){
			i-=n;
			for(int j:g[i])if(ou[j]==N)ou[j]=ji[i]+1,q.push(j);
		}else for(int j:g[i])if(ji[j]==N)ji[j]=ou[i]+1,q.push(j+n);
	}
	for(i=1;i<=n;++i)v[0][ji[i]]+=u,v[1][ou[i]]+=u,v[2][max(ji[i],ou[i])]+=u;
}
int get(basic_string<int>*v){
	int i,s=0,t=1,c=0;
	for(i=0,memset(a,0,N*4);i<N;++i)for(int j:v[i]){//加点
		if(a[j])t=t*1ll*iv[a[j]]%P;else ++c;
		if(c==o)s=(s+t*1ll*i)%P;
		t=t*1ll*(++a[j])%P;
	}
	return s;
}
int main(){
	for(iv[1]=1,u=2;u<N;++u)iv[u]=(P-P/u)*1ll*iv[P%u]%P;//预处理逆元
	for(scanf("%d",&o),u=1;u<=o;++u)in();
	printf("%d",((get(v[0])+get(v[1])-get(v[2]))%P+P)%P);
	return 0;
}
```


---

## 作者：DrBit (赞：6)

[题目链接](https://www.luogu.com.cn/problem/P7293)

~~做这道题前请先确保自己理解了这个鬼畜的建图方式。~~

手模样例之后我们模糊地意识到一个新图中一个点到 $1$ 号点的距离大概和原图的最短路有什么关联。

发现 $\prod\limits N_i$ 大得离谱之后更能确定这题是根据原图的信息得出答案。

分析性质:

从 $(1,1,1, \dots ,1)$ 走到$(j_1,j_2,j_3, \dots ,j_K)$可以看做在第一个图上从 $1$ 走到 $j_1$，同时在第二个图上从 $1$ 走到 $j_2$……，在第 $K$ 个图上从 $1$ 走到 $j_K$。

如果在第 $i$ 号图上已经走到了 $j_i$ 这个点，那么就可以在附近随意找一条边反复横跳，等其他图走到对应点（结合样例感性理解一下）。而等其他点的过程中一次跳 $2$ 步，所以只有奇偶性相同的距离才可以互相“等”。在这里我们求出在每个图 $i$ 中 $1$ 号点到 $j_i$ 号点的奇数最短距离和偶数最短距离，记为 $odd_{j_i}$ 和 $even_{j_i}$，则一个点 $(j_1,j_2,j_3, \dots ,j_K)$ 到 $1$ 号点的距离就是$\min(\max (odd_{j_i}), \max(even_{j_i}))$。 其中 $\min$ 运算不是很好处理，容斥一下把式子转换成 $\max (odd_{j_i})+ max(even_{j_i}) -max(max(odd_{j_i},even_{j_i}))$。

考虑一下怎么求这个 $\max$ 的式子。枚举一个节点 $j_i$，计算有多少种取法使得 $j_i$ 的对应值最大，显然方案数就是其他图里面对应值小于 $j_i$ 的节点的个数乘积。事先记录一下每个值对应的元素位置，用一棵线段树维护每个图中剩余节点个数以及区间乘积。从大到小枚举最大值 $k$，对于对应值为 $k$ 的每一个节点 $i$，它的贡献就是和 $i$ 不在一个图中的节点数目，计算完之后将节点 $i$ 删掉，可以感性认识到这种计数方法是正确的。

复杂度 $O(N \log N)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define ls (x << 1)
#define rs ((x << 1) | 1)
#define int long long
using namespace std;
const int MAXN = 4e5 + 50;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;
int dis[MAXN][2], lib[MAXN][2];
vector<int> pos[MAXN];
vector<int> g[MAXN];
int T, N[MAXN], M[MAXN], sum[MAXN], bel[MAXN], cnt[MAXN];
struct node
{
    int a, b;
    node(){}
    node(int x, int y)
    {
        a = x;
        b = y;
    }
};
queue<node> q;
struct SegT
{
    int val[MAXN * 4];
    void clear()
    {
        memset(val, 0, sizeof(val));
    }
    void update(int x, int l, int r, int t, int v)
    {
        if (l == r)
        {
            val[x] += v;
            val[x] %= mod;
            return;
        }
        int mid = (l + r) >> 1;
        if (t <= mid)
            update(ls, l, mid, t, v);
        else
            update(rs, mid + 1, r, t, v);
        val[x] = val[ls] * val[rs] % mod;
    }
    int query(int x, int l, int r, int tl, int tr)
    {
        if (tl > r || tr < l)
            return 1;
        if(tl <= l && tr >= r)
            return val[x];
        int mid = (l + r) >> 1;
        return query(ls, l, mid, tl, tr) * query(rs, mid + 1, r, tl, tr) % mod;
    }
} SegT;
int solve(int typ)
{
    int maxn = 0;
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= sum[T]; ++i)
    {
        int t = -1;
        if (typ & 1)
            t = max(t, lib[i][0]);
        if (typ & 2)
            t = max(t, lib[i][1]);
        if (t == INF)
            continue;
        cnt[bel[i]]++;
        pos[t].push_back(i);
        maxn = max(maxn, t);
    }
    SegT.clear();
    for (int i = 1; i <= T; ++i)
        SegT.update(1, 1, T, i, cnt[i]);
    int res = 0;
    for (int i = maxn; i >= 1; --i)
    {
        int siz = pos[i].size();
        for (int j = 0; j < siz; ++j)
        {
            int t = pos[i][j];
            res += i * SegT.query(1, 1, T, 1, bel[t] - 1) % mod * SegT.query(1, 1, T, bel[t] + 1, T) % mod;
            res %= mod;
            SegT.update(1, 1, T, bel[t], -1);
        }
    }
    for (int i = 1; i <= maxn; ++i)
        pos[i].clear();
    return res;
}
signed main()
{
    scanf("%lld", &T);
    for (int x = 1; x <= T; ++x)
    {
        scanf("%lld%lld", &N[x], &M[x]);
        sum[x] = sum[x - 1] + N[x];
        for (int i = 1; i <= N[x]; ++i)
            g[i].clear();
        for (int i = 1; i <= M[x]; ++i)
        {
            int u, v;
            scanf("%lld%lld", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        memset(dis, 0x3f, sizeof(dis));
        dis[1][0] = 0;
        q.push(node(1, 0));
        while (!q.empty())
        {
            node t = q.front();
            q.pop();
            int siz = g[t.a].size();
            for (int i = 0; i < siz; ++i)
            {
                int v = g[t.a][i];
                if (dis[v][!t.b] > dis[t.a][t.b] + 1)
                {
                    dis[v][!t.b] = dis[t.a][t.b] + 1;
                    q.push(node(v, !t.b));
                }
            }
        }
        for (int i = 1; i <= N[x]; ++i)
            for (int j = 0; j <= 1; ++j)
                lib[sum[x - 1] + i][j] = dis[i][j];
        for (int i = sum[x - 1] + 1; i <= sum[x]; ++i)
            bel[i] = x;
    }
    // cout << solve(1) << " " << solve(2) << " " << solve(3) << endl;
    printf("%lld\n", (solve(1) + solve(2) - solve(3) + mod) % mod);
    return 0;
}
```


---

## 作者：老莽莽穿一切 (赞：3)

[更好的阅读体验](https://www.cnblogs.com/LaoMang-no-blog/p/16189295.html)

---

[**你谷 link**](https://www.luogu.com.cn/problem/P7293)

这个题也太妙了，考场根本一点头绪没有。

给定一些图，求这些图的张量积中 $(1,1,\cdots,1)$ 到所有点的最短路和。

首先我们发现这个张量积上的最短路有什么特点，我们可以考虑将所有图分开考虑，每一张图分开做，加入从 $(1,1,\cdots,1)$ 到 $(a_1,a_2,\cdots,a_K)$，可以看成分别从 $1$ 到 $a_1$，$1$ 到 $a_2$，$\cdots$，$1$ 到 $a_K$，同时到达。

我们发现图是无向图，所以可以通过在一条边反复走来达到等待的目的，所以就只和最短路长度的奇偶性相关。

考虑算出每张图上每个点的奇偶最短路，设第 $i$ 张图中 $1$ 到 $j$ 的长度为奇数的最短路长度为 $\text{odd}_{i,j}$，长度为偶数为 $\text{even}_{i,j}$，那么 $(1,1,\cdots,1)$ 到 $(a_1,a_2,\cdots,a_K)$ 的最短路长度为 $\min\{\max_{i=1}^K\{\text{odd}_{i,a_i}\},\max_{i=1}^K\{\text{even}_{i,a_i}\}\}$，这个东西是 $\min$ 套 $\max$，并不是很好处理，所以考虑进行一步转化，将 $
\min$ 展开成 $\max$，最后我们就是要求这样一个式子：

$$
\sum_{1\le a_i\le n_i}\max_{i=1}^K\{\text{odd}_{i,a_i}\}+\max_{i=1}^K\{\text{even}_{i,a_i}\}-\max_{i=1}^K\{\text{odd}_{i,a_i},\text{even}_{i,a_i}\}
$$

发现可以把三个式子分开来算，这样形式是一样的，最后就是要算这样一个东西：

$$
\sum_{1\le a_i\le n_i}\max_{i=1}^K\{V_{i,a_i}\}
$$

考虑这个 $V$ 的范围只有 $n$，所以可以统计 $\max_{i=1}^K\{V_{i,a_i}\}=x$ 的 $(a_1,a_2,\cdots,a_n)$ 的数量。

然后再考虑这个新的式子怎么算，其实也不难，因为求得是 $\max$，又是计数，可以考虑两两合并，这样就只要考虑相邻两项，算以下式子：

$$
F_k=\sum_{\max\{i,j\}=k}A_iB_j
$$

其中 $A_x$，$B_x$ 分别代表待合并的两个数组中满足 $\max_{i=1}^K\{V_{i,a_i}\}=x$ 的数量，$F_x$ 同理，不过是合并结果。

这个式子很像卷积，但显然不是正常的多项式卷积或是位运算卷积之类的，所以肯定不是什么 FFT 或者 FWT 之类的。

这个可以形象地称为 $\max$ 卷积的东西算起来相对 FFT 或者 FWT 更简单地多，但我们可以思考做一种类似 FFT 中 DFT 和 IDFT 的变换来使其成为一种线性变换，发现这个东西可以用一种非常简单的办法，就是直接前缀和，逆变换就是直接再差分回来就好了，读者可以手模一下，具体原理可以看下面这张图：

![](https://s2.loli.net/2022/04/25/JD23HaL9j8zqgWM.png)

这里黑色的格子表示两个要合并的数组，红线表示待求值最顶层要算的，红线和蓝线的和正好是前缀和的积，而蓝线也是前缀和的积，做差分就能得到答案。

这样整道题就做完了，但还有一个细节。

两个数组和合并是 $\mathcal O\left(\text{len}\right)$ 的，如果直接将所有数组合并时间复杂度会退化成 $\mathcal O\left(Kn\right)$，会被卡掉，怎样优化呢？其实直接将数组按长度从小到大合并就好了，这样时间复杂度就是 $\mathcal O\left(\sum n\right)$，是可过的。

[**c++ 代码**](https://www.cnblogs.com/LaoMang-no-blog/p/16189295.html)

---

## 作者：Lynkcat (赞：3)

提供一个无脑的 $O(n \log n)$ 的做法。

考虑对于每张图的每个点跑出奇偶最短路，相当于对于每张图选出一个点，设第 $k$ 张图选出的点是 $p_k$。答案即为 $\sum \min(\max(\text{OddDis}_{p_i}),\max(\text{EvenDis}_{p_i})$。

分类讨论一下，我们设选出的点的 $\text{EvenDis}$ 最小值位置为 $p$，为了不算重我们把贡献算在最靠左的点上，那么答案就相当于它前面的图只能选 $\text{EvenDis}_i< \text{EvenDis}_p$ 的点，后面的图只能选  $\text{EvenDis}_i\leq  \text{EvenDis}_p$ 的点，并且要满足选的点 $\max\text{OddDis}>\text{EvenDis}_p$。考虑容斥一下，先算没有 $\text{OddDis}$ 的方案数，然后减去 $\max\text{OddDis}<\text{EvenDis}_p$ 的方案数，然后限制就分别变成了 $\max(\text{OddDis}_i,\text{EvenDis}_i)<  \text{EvenDis}_p$ 和 $\max(\text{OddDis}_i,\text{EvenDis}_i)\leq  \text{EvenDis}_p$。直接做 $\max$ 卷积即可。这里采用了线段树维护的方法，时间复杂度 $O(n \log n)$。注意反过来也要做一遍。

[代码有点长，放这儿了](https://www.luogu.com.cn/paste/raf3mlvm)。

---

## 作者：Anonymely (赞：1)

首先要先看懂那个新图是怎么建的，其实就是新图上走一步等于在每个图上各走一步。

由于是无向图，所以可以往前一步往后一步使得步数 $+2$，不难想到对于奇偶分开讨论。

具体的，对于第 $i$ 个图上的 $j$ 点，它的奇偶最短路分别为 $d_{i,j,0/1}$，对于选择方案 $S$，答案即为 $\min (\max d_{s,0}, \max d_{s,1})$。

有 $\min$ 和 $\max$ 很烦，如果要暴力记录必须记录具体值，所以考虑类似期望的贡献计算，$\sum_i i*f(i)=\sum_j \sum_{i \ge j} f(i)$，即考虑上面的式子大于 $k$ 的方案，这样就转化为 $01$ 序列，此时暴力记录最大值，同时拿线段树维护即可。

一点小细节是对于走不到的距离会导致这一维直接不能选，也就是都不能选奇数或偶数，所以记录状态应该是 $0/1/2$ 表示无 $1$，有 $1$，不能选。

[submission](https://www.luogu.com.cn/record/176397811)

---

## 作者：Disjoint_cat (赞：1)

这怎么是个黑题啊。模拟赛赛时做法甚至题解区一篇都没有~~虽然复杂度有点小大~~。

首先在大图上走相当于每个图上各走一步。

对于一个结点序列，考虑它的最小步数。因为可以通过反复横跳来捏造 $2$ 步，所以考虑分奇偶性讨论。

每个图 $i$ 分别 bfs 出 $1$ 到所有 $j$，走过步数是奇数/偶数的距离，记为 $d_{i,0/1,j}$。那么对于奇数/偶数，距离分别取最大值即可。那么最小的步数就是奇偶步数的最小值。

即，如果分别选取了 $g_1,g_2,\ldots,g_k$，则距离为：

$$\min_{p=0}^1\max_{i=1}^kd_{i,p,g_i}$$

但是这玩意一个 $\min$ 一个 $\max$，不好处理。

考虑以下事实：（简单拆一下贡献即可证明。）

$$\sum_{i}i\cdot f_i=\sum_{i}\sum_{j\ge i}f_j$$

那么可以转化为对每个 $i$ 求出距离 $\ge i$ 的 $g$ 的个数再求和。这时序列就变成了 $01$ 序列，合法的要求就是奇偶数两边都有 $1$。

考虑扫描线，把 $i$ 从小到大扫，那么就只有把某个 $1$ 变成 $0$ 的操作了，然后要维护两边都有 $1$ 的方案数。

对于一堆序列，可以记 $f_{00,01,10,11}$ 表示奇数、偶数分别有/没有 $1$ 的方案数。容易发现合并直接暴力或卷积就行了。

所以线段树维护一下就求完了。（最后记得把走不到的状态的多余贡献减掉）

时间复杂度为 $\Theta(k\log k+\sum(n+m))$，虽然带了或卷积的 $16$ 的常数但是只跑了 $\texttt{124ms}$ 一点也不卡常。

[submission](https://www.luogu.com.cn/record/170896325)

---

## 作者：Undead2008 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P7293)

提供一个和现有题解均不同的做法。

首先从 $(1,1,\dots,1)$ 走到 $(a_1,a_2,\dots,a_K)$ 的最短距离为 $D$ 等价于在 $G_1$ 中存在一条长度为 $D$ 的从 $1$ 到 $a_1$ 的路径，在 $G_2$ 中存在一条长度为 $D$ 的从 $1$ 到 $a_2$ 的路径，依此类推，且不存在满足上述条件的 $D'\le D$。

设对于 $G_i$ 的 $j$ 号节点，由 $G_i$ 的 $1$ 号节点到它的经过奇数条边的最短路为 $a_{i,j}$，经过偶数条边的最短路为 $b_{i,j}$。则答案为

$$\sum_{i_1\in G_1}\sum_{i_2\in G_2}\dots\sum_{i_K\in G_K}\min(\max_{1\le j\le K}a_{j,i_j},\max_{1\le j\le K}b_{j,i_j})$$

发现外面的 $\min$ 和里面的 $\max$ 结合起来不好直接维护，考虑到 $\min(a,b)=a+b-\max(a,b)$，可以把 $\min$ 拆掉变成这个样子：

$$\sum_{i_1\in G_1}\dots\sum_{i_K\in G_K}\max_{1\le j\le K}a_{j,i_j}+\sum_{i_1\in G_1}\dots\sum_{i_K\in G_K}\max_{1\le j\le K}b_{j,i_j}-\sum_{i_1\in G_1}\dots\sum_{i_K\in G_K}\max(\max_{1\le j\le K}a_{j,i_j},\max_{1\le j\le K}b_{j,i_j})$$

发现整个问题被拆成了三个一模一样的子问题，这些子问题看起来像多重背包的形式，考虑使用 dp 求解其中的一个：

设 $f_{i,j}$ 为考虑了 $i$ 张图，$a$ 的最大值为 $j$ 的方案数，则对于第 $i$ 张图的 $k$ 号节点有转移方程：

$$f_{i,\max(a_{i,k},j)} \leftarrow f_{i,\max(a_{i,k},j)}+f_{i-1,j}$$

虽然这个状态数是 $O(mK)$ 的，但是可以用一个数组 $f$ 从 $G_1$ 一直扫描线到 $G_K$，这样就可以做到线性。

时间复杂度线性对数，因为有最短路。把最短路换成 bfs 就可以线性了。为了保证时间复杂度，在扫描之前必须按照图的大小从小到大排序，~~但是因为数据非常垃圾即使不排序也能过~~。

[代码](https://www.luogu.com.cn/paste/llear5lc)

---

## 作者：Xttttr (赞：0)

[传送门](https://www.luogu.com.cn/problem/P7293) [更好的阅读体验](https://www.cnblogs.com/Xttttr/p/17959957)

思路：提供一个不太一样的容斥做法。

首先容易发现答案只和每个点到 1 号点的奇偶最短路有关，可以先 $O(n)$ 求出来。

然后考虑枚举距离 $d$，计算有多少个 K 元组的距离为 $d$。不妨设 $d$ 为奇数，那么条件就是：
1. 每个点的奇最短路的最大值为 $d$；
2. 存在一个点的偶最短路 $>d$。

考虑怎么快速维护。对于每一张图，我们求出能到走到的奇偶最短路的最大值 $maxd$。

我们把图分成两部分，一部分是 $maxd<d$，另一部分是 $maxd\ge d$。

对于第一部分，不存在满足第一个条件的点，而且对于所有 $maxd<d$ 的 $d$，这张图的满足第二个条件的点数量不会变，贡献很好维护。

对于第二部分，我们遍历所有满足条件的图，维护 $f[0/1][0/1]$ 表示是否满足第一个条件，是否满足第二个条件的方案数。我们需要知道对于每一张图，有多少个点满足奇最短路的为 $d$，有多少个点满足奇最短路的不超过 $d$，有多少个点满足奇最短路不超过 $d$ 且偶最短路 $>d$，这些信息都可以 $O(n+maxd)$ 求出。最终转移是一个或卷积。这一部分复杂度是 $\sum maxd=O(\sum n)$ 的。

总复杂度 $O(n)$。

代码：
```cpp
int K;
int p1[N<<1],p2[N<<1];
struct Graph{
    int n,m,cnt,maxn;
    vector<int>h,ver,nxt,dis[2],t,d,c,pre;
    inline void add_edge(int x,int y){cnt++;ver[cnt]=y;nxt[cnt]=h[x];h[x]=cnt;}
    inline void init(){
        n=read(),m=read();
        h.resize(n+1),ver.resize(2*m+1),nxt.resize(2*m+1),dis[0].resize(n+1),dis[1].resize(n+1);
        for(int i=1;i<=n;i++)dis[0][i]=dis[1][i]=mod;
        for(int i=1;i<=m;i++){
            int x=read(),y=read();
            add_edge(x,y),add_edge(y,x);
        }
        queue<int>q;
        dis[0][1]=0;
        q.push(2);
        while(!q.empty()){
            int x=q.front()>>1,k=q.front()&1;
            q.pop();
            for(int i=h[x];i;i=nxt[i]){
                int y=ver[i];
                if(dis[k^1][y]>dis[k][x]+1){
                    dis[k^1][y]=dis[k][x]+1;
                    q.push((y<<1)|(k^1));
                }
            }
        }
        for(int i=1;i<=n;i++){
            if(dis[0][i]!=mod)maxn=max(maxn,dis[0][i]);
            if(dis[1][i]!=mod)maxn=max(maxn,dis[1][i]);
        }
        t.resize(maxn+1),d.resize(maxn+1),c.resize(maxn+3),pre.resize(maxn+1);
        for(int i=1;i<=n;i++){
            if(dis[0][i]<dis[1][i]){
                d[dis[0][i]]++;
                c[dis[0][i]]++;
                if(dis[1][i]!=mod)c[dis[1][i]+1]--;
            }
            if(dis[1][i]<dis[0][i]){
                d[dis[1][i]]++;
                c[dis[1][i]]++;
                if(dis[0][i]!=mod)c[dis[0][i]+1]--;
            }
            if(dis[0][i]!=mod)t[dis[0][i]]++;
            if(dis[1][i]!=mod)t[dis[1][i]]++;
        }
        for(int i=0;i<=maxn;i++){
            pre[i]=t[i];
            if(i>1)pre[i]+=pre[i-2];
        }
        for(int i=2;i<=maxn+2;i++)c[i]+=c[i-2];
        p1[maxn+2]=1ll*p1[maxn+2]*pre[maxn]%mod;
        p2[maxn+2]=1ll*p2[maxn+2]*dec(pre[maxn],c[maxn+2])%mod;
        p1[maxn+1]=1ll*p1[maxn+1]*(maxn?pre[maxn-1]:0)%mod;
        p2[maxn+1]=1ll*p2[maxn+1]*dec(maxn?pre[maxn-1]:0,c[maxn+1])%mod;
    }
}G[N];
vector<int>hav[N],q;
int maxd;
int f[4],g[4],a[4],ans;
int main(){
    K=read();
    for(int i=0;i<=200003;i++)p1[i]=p2[i]=1;
    for(int i=1;i<=K;i++){
        G[i].init();
        hav[G[i].maxn].push_back(i);
        maxd=max(maxd,G[i].maxn);
    }
    for(int i=2;i<=maxd;i++)p1[i]=1ll*p1[i]*p1[i-2]%mod,p2[i]=1ll*p2[i]*p2[i-2]%mod;
    for(int i=maxd;i;i--){
        for(auto j:hav[i])q.push_back(j);
        memset(f,0,sizeof(f)),memset(g,0,sizeof(g));
        g[0]=p2[i];g[1]=dec(p1[i],p2[i]);
        for(auto j:q){
            a[0]=G[j].pre[i]-G[j].t[i]-G[j].c[i]+G[j].d[i],a[1]=G[j].c[i]-G[j].d[i],a[2]=G[j].t[i]-G[j].d[i],a[3]=G[j].d[i];
            memset(f,0,sizeof(f));
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++)add(f[i|j],1ll*g[i]*a[j]%mod);
            }
            swap(f,g);
        }
        add(ans,1ll*g[3]*i%mod);
    }
    cout<<ans<<endl;
    return 0;
}
```

---

