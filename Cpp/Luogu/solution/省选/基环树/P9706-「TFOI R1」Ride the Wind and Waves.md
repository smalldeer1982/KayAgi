# 「TFOI R1」Ride the Wind and Waves

## 题目背景

Z 教授是 C 班的老师。

Z 教授最近发现一个神奇的现象，他的学生竟然都有自己暗恋的对象，但是没有一个人勇于表白。

Z 教授作为过来人，当然懂得每一个学生心里最真实纯真的想法，以及自认为的爱意情愫。Z 教授想起了初恋蕉太狼，他不想让自己的学生在青春年华失去色彩，于是 Z 教授冒着被开除的风险，主动帮助学生表达心意。

然后 Z 教授被开除了。

## 题目描述

有一棵 $n$ 个节点的内向基环树（**保证弱连通**），树上每条边都有一个权值。现有一个特定参数 $k$。

由于基环树是内向的，所以一个点 $x$ 可能会有无法直接到达的节点。但是我们可以翻转树上的一些有向边，这样 $x$ 就可以到达树上每一个节点。如果一个节点 $x$ 需要**至少**翻转 $k$ 条边才能到达 $y$，则称 $y$ 是 $x$ 的乘风破浪点。在翻转了**最少的边**使得 $x$ 可以到达 $y$ 之后，在 $x$ 到 $y$ 的最短路径上，定义 $F(x, y)$ 为**未翻转**的边的权值之和，$R(x, y)$ 为**已翻转**的边的权值之和。

如果 $y$ 是 $x$ 的乘风破浪点，那么有一个值 $G(x, y)$ 表示 $x$ 到 $y$ 的浪涛值，定义 $G(x, y) = F(x, y) \times  R(x,y)$。

请你对于每一个节点 $i$，输出 $\sum G(i, y)$ 的值，其中 $y$ 是 $i$ 的乘风破浪点。

## 说明/提示

#### 样例解释 #1

拿 $3$ 节点的答案为例子，基环树的形状如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/a3ocyi6o.png)

可知 $2,5,6,7$ 为 $3$ 的乘风破浪点，统计答案：

- $G(3, 2) = 6 \times 2 = 12$。

- $G(3, 5) = 6 \times 6 = 36$。

- $G(3, 6) = 9 \times 1 = 9$。

- $G(3, 7) = 6 \times 8 = 48$。

所以 $\sum G(3, j) = 12 + 36 + 9 + 48$，答案为 $105$。

#### 数据范围

**本题采用捆绑测试**。

- Subtask 1（5 points）：$1 \leqslant n \leqslant 10$，**包含特殊性质**。
- Subtask 2（10 points）：$1 \leqslant n \leqslant 5000$，**包含特殊性质**。
- Subtask 3（25 points）：$1 \leqslant n \leqslant 10^5$，**包含特殊性质**。
- Subtask 4（60 points）：$1 \leqslant n \leqslant 10^6$，无特殊限制。

**特殊性质：保证环上节点的个数在 $10^3$ 以内。**

对于所有数据，$1 \leqslant n \leqslant 10^6$，$1 \leqslant k \leqslant 10$，保证答案不会超过 $10^{18}$。

## 样例 #1

### 输入

```
7 1
1 4 3
2 1 2
3 1 6
4 3 4
5 2 4
6 4 1
7 5 2```

### 输出

```
3
5
105
160
9
176
11```

## 样例 #2

### 输入

```
7 1
1 2 3
2 3 2
3 1 2
4 1 3
5 4 2
6 2 1
7 6 4```

### 输出

```
18
32
46
36
48
40
72```

# 题解

## 作者：Supor__Shoep (赞：3)

这里是出题人题解。本题有较多奇怪做法，这里就介绍一下我初步想到的解法。

下文定义 $cnt$ 为基环数上的环的大小。

## Subtask 1:

枚举两个点 $x,y$，通过搜索得到 $x\to y$ 的路径（**保证翻转的边数尽可能小**），记录翻转的边和未翻转的边，然后乘起来就可以得到答案。

枚举是 $O(n^2)$，找路径在最坏情况下是 $O(n)$，因此总时间复杂度约为 $O(n^3)$。

**期望得分：$5pts$**

## Subtask 2:

枚举每一个点依次算答案。

我们从枚举的点 $x$ 开始进行搜索，并时刻记录两个乘数的值。当搜索到了基环树的环时，我们只能按照有向边的方向走，如果你反着走，就没有保证翻转了最少的边。

遍历完整棵树，把所有答案累加到 $x$ 的答案上面。时间复杂度 $O(n^2)$。

**期望得分：$5pts+10pts=15pts$**

## Subtask 3:

这个做法和正解已经非常接近了！！！！！

剖析一下基环树的结构，我们可以将其理解为**一个环以及以环上节点为根的许多棵树形成的集合**。为了方便表示，**树**表示以环上节点为根的树，**基环树**才表示整个集合。因此尝试分类讨论：

- **环上节点**：我们发现任意两个环上节点并不会互相产生代价，也就是说只有树上的某些节点会对环上节点产生代价。考虑预处理出每一棵树中，离根节点至少 $k$ 条边的所有点到根节点的**距离之和**。设一棵树 $T$ 中的距离之和为 $w_0$，某个环上节点 $x$ 到 $T$ 的根节点的距离为 $w_1$，则 $T$ 带给 $x$ 的答案的代价就是 $w_0\times w_1$。因此环上节点的答案就可以用 $O(cnt^2)$ 求了。

- **不同树上的节点**：如果两个节点在不同的树中，那么它们两个可能会产生代价。不难发现这里的思路与上一种情况类似，设一棵树为 $T$，$T$ 的根节点答案为 $w_0$，考虑从根节点向下进行搜索（注意是在**反图**上面搜索），每次深度增加一个边权 $val$ 的时候，只有**未翻转的边权之和**在发生改变，**已翻转的边权之和**是不会变的，因此树上节点的答案可以根据其父亲节点的答案推来，并且 $\Delta=\Delta val\times D$，其中 $D$ 表示**已翻转的边权之和**，是非常好求的。

- **同一棵树上节点**：这是一部分人容易忽略的一种情况。我们可以通过枚举 $x$ 来计算 **$x$ 对其它节点的影响代价**。首先我们发现单个枚举 $x$ 肯定不行，于是我们将枚举的 $x$ 换一个含义，它代表的是以 $x$ 为根的子树。我们找到 $x$ 向上的 $k$ 级祖先 $y$，如果找不到，则说明 $x$ 不会给同一棵树中的节点带来代价，那么整棵子树也就不能带来完整的代价。否则，$x\to y$ 的路径就相当于**已翻转的边权之和**，如下图所示，$k=1$，红色部分表示枚举的子树，而蓝色的部分就是这棵子树送出代价的范围。

	现在我们要将 $x$ 的子树中所有节点的答案传到其它节点。设 $x$ 的 $k$ 级祖先为 $y$，记 $R$ 表示 $x$ 中所有节点到 $y$ 的距离之和，$dis_i$ 表示 $i$ 到根节点的距离，则对于蓝色部分的所有节点 $p$，答案增加 $R\times (dis_p-dis_y)$，把式子拆开变成 $R\times dis_p-R\times dis_y$。这里的 $dis_p$ 取自于蓝色部分，而不属于红色部分，考虑用**差分**维护 $\sum R$ 和 $\sum R\times dis_y$。最后计算答案的时候从根开始，向下将差分值进行累加即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/m0bva2wj.png)

计算环上的答案时，我们采用了 $O(cnt^2)$ 的枚举法，计算树上答案时，我们采用了 $O(nk)$ 的差分法，两者并列，时间复杂度 $O(\max\{nk,cnt^2\})$。

**期望得分：$5pts+10pts+25pts=40pts$** 



## Subtask 4:

在 $O(\max\{nk,cnt^2\})$ 的做法中，我们发现如果 $cnt$ 很大，那么还是会超时，而树上差分的方法是 $O(nk)$，可以继续采用。所以我们只需要优化环上的答案就行了。

不难发现环上每一个节点的答案之间都有一些联系，考虑设计一个**动态规划**求解。

设 $dp_i$ 表示**环上节点** $i$ 的答案，这种状态下没有办法进行初始化，因此**先暴力枚举出任意一个点的答案**。设 $D_i$ 表示以环上节点 $i$ 为根的树中深度大于 $k$ 的节点到 $i$ 的距离之和（$i$ 的深度为 $1$）。

给一个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/swgbxuwm.png)

假如我们枚举的是 $1$ 号点，得到了答案 $dp_1$，红色线条对应的就是 $1$ 号点的答案所统计到的范围，而它本身不需要被计算，因为其中一个乘数变成了 $0$。按照顺序，现在我们要计算 $dp_2$，蓝色线条对应的是 $2$ 号点的答案应该统计到的范围。不难观察到它们都有一段重复的范围，即 $[2,6]$，除去不会被计算到的 $2$ 号点本身，区间范围 $[3,6]$ 的 $\sum D_i$ 是重复的，因此 $2$ 不必再枚举这一段的乘数。设 $dis(i,j)$ 表示 $i\to j$ 的距离（距离是指**走有向边的距离**），我们可以列出两者答案的式子：

$$dp_1=\sum _{j=2} ^6 dis(1,j)\times D_j$$

$$dp_2=(\sum _{j=3}^6 dis(2,j)\times D_j)+dis(2,1)\times D_1$$

根据上图可以发现 $dis(1,j)-dis(2,j)$ 正是边 $(1,2)$ 的边权，则：

$$\begin{aligned}
dp_2&=(\sum_{j=3}^6 (dis(1,j)-dis(1,2))\times D_j)+dis(2,1)\times D_1 \\
&=(\sum_{j=3}^6 dis(1,j)\times D_j)-dis(1,2)\times (\sum_{j=3}^6 D_j)+dis(2,1)\times D_1\\
&=dp_1-dis(1,2)\times D_2-dis(1,2) \times(\sum_{j=3}^6 D_j)+dis(2,1)\times D_1\\
&=dp_1-dis(1,2)\times (\sum_{j=2}^6 D_j)+dis(2,1)\times D_1
\end{aligned}$$

由于 $D_j$ 的值不变，所以我们可以提前预处理 $sum=\sum _{j=1}^{cnt} D_j$，同时还可以预处理出一个**前缀和**，方便计算 $dis$。设 $pre$ 表示环上节点 $i$ 的上一个环上节点，则：

$$dp_i=dp_{pre}-dis(pre,i)\times (sum-D_{pre})+dis(i,pre)\times D_{pre}$$

差分 $O(nk)$，动态规划 $O(cnt)$，时间复杂度 $O(nk)$。

**期望得分：$5pts+10pts+25pts+60pts=100pts$**

标程：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 5;
int head[MAXN], nxt[MAXN], to[MAXN], val[MAXN], tot;
void add(int x, int y, int z) {
    to[++tot] = y;
    val[tot] = z;
    nxt[tot] = head[x];
    head[x] = tot;
}
vector<pair<int, int> > v[MAXN];
int n, k;
void read(int &x) {
    x = 0;
    short flag = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            flag = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    x *= flag;
}
long long D[MAXN];
int vv[MAXN], vis[MAXN], stk[MAXN], cnt;
int dfs1(int x) {//找环 
    if (vv[x] == 1) {
        vv[x] = 2, vis[x] = 1, stk[++cnt] = x;
        return 1;
    }
    vv[x] = 1;
    for (int i = head[x]; i; i = nxt[i]) {
        if (dfs1(to[i])) {
            if (vv[x] != 2) {
                vis[x] = 1, stk[++cnt] = x;
                return 1;
            }
            return 0;
        }
    }
    return 0;
}
int now, len[MAXN];
void dfs(int x, int dep, long long sum) {
    if (dep >= k)
        D[now] += sum;//更新 D[i] 的值 
    for (int i = 0; i < len[x]; i++) {
        if (vis[v[x][i].first])
            continue;
        dfs(v[x][i].first, dep + 1, sum + v[x][i].second);
    }
}
long long res[MAXN], dis[MAXN];
int temp[MAXN];
long long Dis[MAXN];
long long sum;
void dfs2(int x) {
    for (int i = 0; i < len[x]; i++) {
        if (vis[v[x][i].first])
            continue;
        res[v[x][i].first] = res[x] + sum * v[x][i].second, Dis[v[x][i].first] = Dis[x] + v[x][i].second;
        dfs2(v[x][i].first);
    }
}
int Get(int x, int dep) {//求 x 的 dep 级祖先 
    int rsum = dep;
    while (rsum--) {
        if (vis[x])
            return -1;
        x = to[head[x]];
    }
    return x;
}
long long sumup[MAXN], siz[MAXN];//sumup[i] 表示 i 的子树中所有点到 i 的距离之和，siz[i] 表示子树大小 
long long cf1[MAXN], cf2[MAXN];//分别维护 R 和 R * dis[y] 的和 
void dfs3(int x) {
    siz[x] = 1;
    for (int i = 0; i < len[x]; i++) {
        if (vis[v[x][i].first])
            continue;
        dfs3(v[x][i].first);
        siz[x] += siz[v[x][i].first], sumup[x] += 1ll * siz[v[x][i].first] * v[x][i].second + sumup[v[x][i].first];
    }
    int ancestor2 = Get(x, k - 1), ancestor = Get(ancestor2, 1);
    if (ancestor == -1)
        return;
    long long rsum = siz[x] * (Dis[x] - Dis[ancestor]) + sumup[x];//求出 R 
    cf1[ancestor] += rsum, cf1[ancestor2] -= rsum;//差分 
    cf2[ancestor] += rsum * Dis[ancestor], cf2[ancestor2] -= rsum * Dis[ancestor];
}
void dfs_down(int x) {//向下累加差分值并统计答案 
    for (int i = 0; i < len[x]; i++) {
        if (vis[v[x][i].first])
            continue;
        cf1[v[x][i].first] += cf1[x], cf2[v[x][i].first] += cf2[x];
        dfs_down(v[x][i].first);
    }
    res[x] += Dis[x] * cf1[x] - cf2[x];
}
int main() {
    read(n), read(k); 
    for (int i = 1; i <= n; i++) {
        int x, y, z;
        read(x), read(y), read(z);
        add(x, y, z), v[y].emplace_back(x, z);
        len[y]++;
    }
    dfs1(1);
    for (int i = 2; i <= cnt; i++) temp[i] = stk[i];
    for (int i = 2; i <= cnt; i++) stk[i] = temp[cnt - i + 2];//处理完之后，stk[i] 就表示第 i 个环上节点 
    for (int i = 1; i <= cnt; i++) now = i, dfs(stk[i], 0, 0);//求出 D[i] 
    for (int i = 2; i <= cnt; i++) dis[i] = dis[i - 1] + val[head[stk[i - 1]]];//预处理前缀和 
    dis[cnt + 1] = dis[cnt] + val[head[stk[cnt]]];
    for (int i = 2; i <= cnt; i++) sum += D[i], res[stk[1]] += dis[i] * D[i];//预处理 D[i] 的和，并暴力枚举第一个点的答案 
    for (int i = 2; i <= cnt; i++) {
    	int wx = val[head[stk[i - 1]]];
    	res[stk[i]] = res[stk[i - 1]] + (dis[cnt + 1] - wx) * D[i - 1] - sum * wx;//转移 
        sum -= D[i], sum += D[i - 1];
    }
    sum += D[cnt];
    for (int i = 1; i <= cnt; i++) sum -= D[i], dfs2(stk[i]), sum += D[i];//向树上传递答案 
    for (int i = 1; i <= cnt; i++) dfs3(stk[i]);//处理在同一棵树上的两个节点之间的答案 
    for (int i = 1; i <= cnt; i++) dfs_down(stk[i]);//统计答案 
    for (int i = 1; i <= n; i++)	printf("%lld\n", res[i]);
    return 0;
}
```

---

## 作者：Graphcity (赞：2)

非常好题目，使我的 Bitaro 旋转。

假设环上有 $m$ 个点，人为地规定一个起点。设从起点开始环上的点依次为 $h_{1\cdots m}$。分三类情况讨论：

- **$x,y$ 在删除环后的同一个树中**

尝试枚举 $LCA(x,y)=a$，此时要求 $a\to y$ 之间的边数 $\ge k$。

我们设 $f_{x,i},g_{x,i}$ 为 $x$ 的子树中到 $x$ 的最短路径边数 $=i$ 时的点数 / 长度之和。（如果边数 $>k$，则统计到 $f_{x,k}/g_{x,k}$ 中）如果 $x$ 在 $a$ 的儿子 $i$ 的子树中，那么 $a$ 的另一个儿子 $j$ 造成的贡献就是
$$
(dep_x-dep_a)(g_{j,k}+g_{j,k-1}\times val_j)
$$
其中 $val_x$ 为边 $x\to fa_x$ 的边权。注意到贡献式可以拆成 $k\times dep_x+b$ 的形式，对于每个 $x$ 可以维护对应的 $k_x$ 和 $b_x$，需要支持 $k,b$ 的子树加，树上前缀和即可。

时间复杂度 $O(n)$。

- **$x\to y$ 的最短路径不经过边 $h_m\to h_1$**

假设 $x$ 在 $h_i$ 的子树中，考虑 $h_j\ (j>i)$ 对 $x$ 的贡献。设 $sum_i$ 为 $h_1\to h_i$ 的路径长度，此时的贡献式为：
$$
(dep_x-sum_i+sum_j)g_{j,k}
$$
同样的，还是维护成 $k\times (dep_x-sum_i)+b$ 的形式。对于 $j$，能够贡献的点是环上的一段前缀。差分一下就可以解决了。

时间复杂度 $O(n)$。

- **$x\to y$ 的最短路径经过边 $h_m\to h_1$**

设 $num_i$ 为 $h_i\to h_1$ 的路径长度，考虑 $h_j(j<i)$ 对 $x$ 的贡献：
$$
(dep_x+num_i+sum_j)g_{j,k}
$$
跟之前两类情况一样，简单维护一下即可。时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e6;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,K,chk[Maxn+5],h[Maxn+5],s;
int f[Maxn+5][11],siz[Maxn+5];
ll g[Maxn+5][11],ans[Maxn+5],val[Maxn+5];
ll K1[Maxn+5],B1[Maxn+5],dis[Maxn+5],num[Maxn+5];
ll K2[Maxn+5],B2[Maxn+5];
vector<pair<int,int>> v[Maxn+5],w[Maxn+5];

inline void Topo()
{
    static int deg[Maxn+5]; queue<int> q;
    For(i,1,n) deg[i]=w[i].size();
    For(i,1,n) if(!deg[i]) q.push(i);
    while(!q.empty())
    {
        int x=q.front(); q.pop();
        for(auto [y,z]:v[x]) if(--deg[y]==0) q.push(y);
    }
    For(i,1,n) if(deg[i])
    {
        for(int j=i;!chk[j];j=v[j].front().first) h[++s]=j,chk[j]=1;
        break;
    }
}
inline void dfs(int x)
{
    f[x][0]=siz[x]=1; ll s1=0,s2=0;
    for(auto [y,z]:w[x]) if(!chk[y])
    {
        dis[y]=dis[x]+z,dfs(y),siz[x]+=siz[y];
        For(i,0,K) f[x][min(K,i+1)]+=f[y][i];
        For(i,0,K) g[x][min(K,i+1)]+=g[y][i]+1ll*f[y][i]*z;
    }
    for(auto [y,z]:w[x]) if(!chk[y])
    {
        ll res=g[x][K]-((g[y][K]+g[y][K-1])+1ll*(f[y][K]+f[y][K-1])*z);
        K1[y]+=res,B1[y]-=res*dis[x];
    }
}
inline void dfs1(int x)
{
    ans[x]=1ll*dis[x]*K1[x]+B1[x];
    for(auto [y,z]:w[x]) if(!chk[y]) K1[y]+=K1[x],B1[y]+=B1[x],dfs1(y);
}
inline void dfs2(int x)
{
    ans[x]+=1ll*(dis[x]-val[x])*K1[x]+B1[x];
    for(auto [y,z]:w[x]) if(!chk[y])
        K1[y]=K1[x],B1[y]=B1[x],val[y]=val[x],dfs2(y);
}
inline void dfs3(int x)
{
    ans[x]+=1ll*(dis[x]+num[x])*K2[x]+B2[x];
    for(auto [y,z]:w[x]) if(!chk[y])
        K2[y]=K2[x],B2[y]=B2[x],num[y]=num[x],dfs3(y);
}
inline void Work1()
{
    memset(K1,0,sizeof(K1)),memset(B1,0,sizeof(B1));
    For(id,1,s-1) {int x=h[id]; val[h[id+1]]=v[x].front().second;}
    For(id,1,s) val[h[id]]+=val[h[id-1]];
    For(id,1,s-1)
    {
        int x=h[id],y=h[id+1];
        K1[x]=g[y][K],B1[x]=1ll*val[y]*g[y][K];
    }
    Rof(id,s,1) {int x=h[id],y=h[id+1]; K1[x]+=K1[y],B1[x]+=B1[y];}
    For(id,1,s) dfs2(h[id]);
}
inline void Work2()
{
    memset(K1,0,sizeof(K1)),memset(B1,0,sizeof(B1));
    Rof(id,s,1) {int x=h[id]; num[x]=v[x].front().second;}
    Rof(id,s,1) num[h[id]]+=num[h[id+1]];
    For(id,1,s) {int x=h[id]; K1[x]=g[x][K],B1[x]=1ll*g[x][K]*val[x];}
    For(id,1,s) {int x=h[id],y=h[id-1]; K1[x]+=K1[y],B1[x]+=B1[y];}
    For(id,2,s) {int x=h[id],y=h[id-1]; K2[x]=K1[y],B2[x]=B1[y];}
    For(id,1,s) dfs3(h[id]);
}

int main()
{
    n=read(),K=read();
    For(i,1,n)
    {
        int a=read(),b=read(),c=read();
        v[a].emplace_back(b,c),w[b].emplace_back(a,c);
    }
    Topo(); For(i,1,s) dfs(h[i]),dfs1(h[i]);
    Work1(),Work2();
    For(i,1,n) printf("%lld\n",ans[i]);
    return 0;
}
```



---

## 作者：zesqwq (赞：0)

乘风破浪点太长了，下文用幽默点代替。

我们对每个点 $i$ 考虑，对于它的幽默点 $y$，我们发现有两种情况：

想象将环删去，那么如果 $i, y$ 不在同一个子树上，那就很幽默了。

因为 $i$ 跳到环上的边都不用反转，环上的边也不用，因此对于一个子树，$\sum R(i, y)$ 是固定的，我们可以破环为链之后处理出他到链头距离，距离的前缀和，以及每个点子树中有多少个幽默点满足距离 $\ge k$，还有该信息的前缀和，处理出来之后问题还是好解决的。

同一个子树内部怎么做？


我们还是考虑 $\sum G(x, y) = \sum G(fa_x, y) + w(x, fa_x) \Delta_x$。

现在考虑如何计算 $\Delta_x$，我们发现一个点父亲的 **有贡献的** 幽默点一点是该节点 **有贡献的** 幽默点的子集，因为 $k \ge 1$ 且有贡献得存在 $f(i, y)$，因此 $\Delta_x = \Delta_{fa_x} + ?$。

恰好 $k$ 怎么算？我们发现 $k$ 级祖先有贡献但是 $k - 1$ 级祖先不该有，$k$ 级位置 $\text{tag}1$ 加，$k - 1$ 级位置 $\text{tag}2$ 减即可。

算的时候就是 $\text{tag}1_{fa_x} - \text{tag}2_x$。

$\ge k$ 怎么算？我们可以恰好 $k$ 做完后转变为子树和。

然后直接做就完了。

实现上记录了 $\sum dep$ 和 $siz$ 做树上差分。

$k$ 小要感恩出题人不需要你求 $k$ 级祖先，心怀感恩。

时间复杂度 $O(nk)$。

```cpp
const int N = 1e6 + 10;
#define int __int128
#define ll __int128
int n, k, fac[N], fa[N], st[N], top;
bool vis[N];
ll dep[N], len[N], f[N], dis[N], disx[N], disy[N], fx[N];
ll k1[N], k2[N], v3[N];
int siza[N], sizb[N];
vector<int> vec[N];
ll dfs(int u) {
    ll ans = dep[u] >= k ? len[u] : 0;
    for (int v : vec[u])
        if (!vis[v]) dep[v] = dep[u] + 1, len[v] = len[u] + fac[v], ans += dfs(v);
    return ans;
}
ll ans[N], res[N];
void dfsx(int u, ll val) {
    for (int v : vec[u]) if (!vis[v]) {
        res[v] = res[u] + fac[v] * val;
        dfsx(v, val);
    }
}
inline int kth(int u, int k) {
    while (k--) u = fa[u];
    return u;
}
void calc(int u) {
    if (dep[u] >= k) {
        ++siza[kth(u, k)];
        ++sizb[kth(u, k - 1)];
        k1[kth(u, k)] += len[u];
        k2[kth(u, k - 1)] += len[u];
    }
    for (int v : vec[u])
        if (!vis[v]) calc(v);
}
ll v2[N];
void at(int u) {
    for (int v : vec[u])
        if (!vis[v]) {
            at(v), k1[u] += k1[v], k2[u] += k2[v], siza[u] += siza[v], sizb[u] += sizb[v];
        }
}
void dp(int u) {
    if (!vis[u]) v2[u] += ((k1[fa[u]] - k2[u]) - (siza[fa[u]] - sizb[u]) * len[fa[u]]), v3[u] += v2[u] * fac[u], res[u] += v3[u];
    for (int v : vec[u]) if (!vis[v]) { v2[v] = v2[u], v3[v] = v3[u], dp(v); }
}
signed main() {
    read(n, k);
    for (int i = 1; i <= n; i++) {
        int u, v, w;
        read(u, v, w), fa[u] = v, vec[v].push_back(u), fac[u] = w;
    }
    int c = 1;
    while (!vis[fa[c]]) vis[c] = 1, c = fa[c];
    int pc = c;
    memset(vis, 0, sizeof(vis));
    for (; fa[c] != pc; c = fa[c]) vis[st[++top] = c] = 1;
    vis[st[++top] = c] = 1;
    ll sum = 0;
    for (int i = 1; i <= top; i++) sum += f[i] = dfs(st[i]);
    for (int i = 2; i <= top; i++) dis[i] = dis[i - 1] + fac[st[i - 1]];
    for (int i = 1; i <= top; i++) disx[i] = disx[i - 1] + dis[i], disy[i] = disy[i - 1] + dis[i] * f[i], fx[i] = fx[i - 1] + f[i];
    for (int i = 1; i <= top; i++) {
        res[st[i]] = (disy[top] - disy[i]) - (fx[top] - fx[i]) * (dis[i]);
        res[st[i]] += (dis[top] - dis[i] + fac[st[top]]) * fx[i - 1] + disy[i - 1];
        dfsx(st[i], fx[top] - f[i]);
    }
    for (int i = 1; i <= top; i++) {
        calc(st[i]), at(st[i]), dp(st[i]);
    }
    for (int i = 1; i <= n; i++) println(res[i]);
    return 0;
}
```

---

