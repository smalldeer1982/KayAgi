# [ARC177F] Two Airlines

## 题目描述

在 AtCoder 国，有一排共 $L+1$ 个岛屿，从西至东依次编号为 $0$ 到 $L$。这些岛通过航空线路连接，每条连接线双向可通。对于每个 $1 \leq i \leq L$，岛屿 $i-1$ 和岛屿 $i$ 由一条线路连接。每一条航空路线都由 A 公司或 J 公司运营，具体来说，连接岛屿 $i-1$ 和岛屿 $i$ 的线路属于 $S_i$ 公司。

![ ](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc177_f/ec43c2a273b93f82a4a10274bb14dc9581c8ab88.png)

这个国家有 $N$ 位居民，他们被编号为 $1$ 到 $N$。每位居民目前分别位于岛屿 $X_i$ 上。

每位居民都持有一张某个公司的优惠券。具体来说，居民 $i$ 拿着的是 $C_i$ 公司的优惠券。他们可以免费搭乘优惠券对应公司的航班任意次，而搭乘其他公司航班时，每次需要支付 $1$ 枚硬币。

我们的目标是把位于岛屿 $0$ 的宝藏运送到首都岛屿 $L$。为了实现这一目标，请计算最少需要支付多少枚硬币。

请注意，宝藏可以在居民之间转交，但优惠券不允许转让。

## 说明/提示

### 条件限制

- $1 \leq L \leq 6 \times 10^4$
- $1 \leq N \leq 6 \times 10^4$
- $S_i\ (1 \leq i \leq L)$ 是 `A` 或 `J`
- $0 \leq X_i \leq L\ (1 \leq i \leq N)$
- $C_i\ (1 \leq i \leq N)$ 是 `A` 或 `J`
- $L, N, X_i$ 是整数

### 示例解释

下面的操作可使宝藏被运送到岛屿 $4$，总共只需花费 $2$ 枚硬币：

1. 居民 $1$ 从岛 $3$ 移到岛 $2$。因为不是优惠券适用的公司航班，所以花费 $1$ 枚硬币。
2. 居民 $1$ 从岛 $2$ 到岛 $1$，在这个过程中无需支付，因为这是他拥有优惠券的公司路线。
3. 居民 $1$ 从岛 $1$ 到岛 $0$，免费，因为使用的是优惠券航班。
4. 居民 $1$ 拿起宝藏。
5. 居民 $1$ 带着宝藏，从岛 $0$ 移动到岛 $1$，依旧免费。
6. 居民 $1$ 把宝藏交给居民 $2$。
7. 居民 $2$ 带着宝藏，从岛 $1$ 到岛 $2$，这条航线不适用他的优惠券，花费 $1$ 枚硬币。
8. 居民 $2$ 继续从岛 $2$ 到岛 $3$，免费，因为使用了他公司的航班。
9. 最后，居民 $2$ 从岛 $3$ 到岛 $4$，依旧免费。

![ ](https://img.atcoder.jp/arc177/362e9b56e8e71232a449db9eee2897d8.png)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4 3
AAJJ
3 A
1 J
1 J```

### 输出

```
2```

## 样例 #2

### 输入

```
8 3
JJAAJJAJ
2 A
6 A
8 J```

### 输出

```
6```

## 样例 #3

### 输入

```
8 6
JJAAJJAJ
2 A
6 A
8 J
8 J
8 J
8 J```

### 输出

```
4```

# 题解

## 作者：WrongAnswer_90 (赞：1)

# [My Blogs](https://www.cnblogs.com/WrongAnswer90/p/18377096)

### [[ARC177F] Two Airlines](https://www.luogu.com.cn/problem/AT_arc177_f)

有点魔怔的题。

一个基本的观察是如果当前某个人 $A$ 拿着盒子走到了位置 $i$，那位置小于 $i$ 的人一定永远没用了。如果之后要用到前面的人 $B$，就应当让 $B$ 拿着盒子走到 $i$ 而不是让 $A$，这样 $A$ 待在原来的位置，代价一定不会更劣。

再手玩一下，可以发现每次的过程都是：某个人 $A$ 拿起盒子，走到某个地方。然后后面来了一个和 $A$ 颜色不一样的人（或者是本身就在这个地方的人），走到了 $A$ 现在的位置，然后带着箱子走了，此时 $A$ 也已经没有用了。

进一步的，“后面来人”的这个过程，对于每种颜色内部，一定是先用坐标尽量小的人来。这个结论不难用调整法证明。

而最优解一定能用上述过程刻画出来。所以可以设 $f_{i,j,k,0/1}$ 表示当前盒子在 $i$，被 $0/1$ 颜色的人拿着，$i$ 后面的 $j$ 个颜色为 $0$ 的人已经用过了（此时在 $<i$ 的位置），$k$ 个颜色为 $1$ 的人已经用过了。转移 $\mathcal O(1)$，状态数和复杂度都是 $\mathcal O(n^3)$ 的。

接下来的一个想法观察性质，能不能简化一维状态什么的，但是好像不太好做。除此之外比较自然地，可以感受到 $j,k$ 都不会太大，设成 $20$ 左右，交上去就直接过了。下面证明 $j,k$ 都只需要取到 $\log n$。

直观感受一下，“后面来人”的原因一定是，$i$ 后面有一段比较长的和当前拿着箱子的颜色不同的路。

![image.png](https://s2.loli.net/2024/08/23/2CBy1quWGZ7rEmS.png)

红色和蓝色的块分别表示序列上红色和蓝色的连续位置。红色段里面不一定全部都是红色，蓝色段里也不一定全是蓝色。红色和蓝色的线条表示人走过的路程。$a_i$ 表示这个蓝色段里面有多少个蓝色格子。

称除去搬运盒子过程中造成的代价为“额外代价”。因为第二条红色线条走到他的目标位置（第二个红块）额外花费了 $\sum_{j\geq 2}a_j$ 的代价，所以 $a_1>\sum_{j\geq 2}a_j$，否则可以让第一个人直接走到第二个红色段：

![image.png](https://s2.loli.net/2024/08/23/8cn96l3V7LRhGbd.png)

这样一定不劣。后面的同理，$a_i>\sum_{j>i}a_j$，所以最多 $\log$ 轮之后 $a_i$ 就要超出值域了。所以 $j,k$ 的维度都只需要开到 $20$。预处理一下还是能做到 $\mathcal O(1)$ 转移。总复杂度 $\mathcal O(n\log^2 n)$。

```cpp
int n,m,f[60010][21][21][2],nex[2][60010][21],t[60010][2],a[60010][2];
char s[60010];
vi ve[2];
inline void mian()
{
    read(n,m),read(s);int x,ans=INF;char ch;
    while(m--)read(x),read(ch),t[x][ch=='A']++,ve[ch=='A'].eb(x);
    for(int i=1;i<=n;++i)a[i][0]=a[i-1][0],a[i][1]=a[i-1][1],++a[i][s[i]=='A'];
    sort(ve[0].begin(),ve[0].end()),sort(ve[1].begin(),ve[1].end());
    for(int k=0;k<2;++k)for(int i=0;i<=n;++i)
    {
        int p=lower_bound(ve[k].begin(),ve[k].end(),i)-ve[k].begin();
        for(int j=1;j<=20;++j)
        if(p+j-1<(int)ve[k].size())nex[k][i][j]=ve[k][p+j-1];
        else nex[k][i][j]=-1;
    }
    memset(f,127,sizeof(f));
    if(nex[0][0][1]!=-1)f[0][1][0][0]=a[nex[0][0][1]][1];
    if(nex[1][0][1]!=-1)f[0][0][1][1]=a[nex[1][0][1]][0];
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<=20;++j)for(int k=0;k<=20;++k)
        {
            if(j<20&&nex[0][i][j+1]!=-1)Mmin(f[i][j+1][k][0],f[i][j][k][1]+a[nex[0][i][j+1]][1]-a[i][1]);
            if(k<20&&nex[1][i][k+1]!=-1)Mmin(f[i][j][k+1][1],f[i][j][k][0]+a[nex[1][i][k+1]][0]-a[i][0]);
        }
        for(int j=0;j<=20;++j)for(int k=0;k<=20;++k)for(int l=0;l<2;++l)
        Mmin(f[i+1][max(0ll,j-t[i][0])][max(0ll,k-t[i][1])][l],f[i][j][k][l]+(l!=(s[i+1]=='A')));
    }
    for(int i=0;i<=20;++i)for(int j=0;j<=20;++j)for(int k=0;k<2;++k)Mmin(ans,f[n][i][j][k]);
    write(ans);
}
```

---

## 作者：qiuzx (赞：1)

假设某种颜色的人初始位置依次为 $x_1,\cdots,x_k$，则必然存在一种最优方案使得在任意时刻他们的相对位置关系不变。这意味着对于某种颜色，如果我们知道某个时刻在物品前面的有多少个人，那么可以立刻知道具体是哪些人在前面哪些人在后面。于是可以有一个暴力的 dp，$dp_{i,j,k,0/1}$ 表示当前物品在位置 $i$，前面两种颜色的人分别有 $j$ 个和 $k$ 个，当前持有物品的人颜色为 $0/1$ 的答案。转移是容易的。

那么这个 dp 应该如何优化呢？其实这个问题是有一些很直观的贪心做法的，但可惜它们都不太对。不过这个思想仍然是值得借鉴的，我们可以从这一点入手去优化 dp。具体来说，显然我们只会把后面的人往前移，而不可能把一个前面的人移到物品的右侧，所以若初始时 $i$ 前面有 $j_0$ 个 $0$，那么必然有 $j\ge j_0$，$k$​ 也是同理。

另一方面，我们也不会将太多的人移到物品的左侧，因为这样移动的目的只是为了去交接物品，但如果移得太多，那么在后面所需要花费的代价会远远超过前面节省的代价。具体地，假设我们将 $k$ 个颜色 $0$ 的人移动到了物品前面，而他们中间通过颜色 $1$ 交换的部分分别有 $c_1,\cdots,c_k$ 条 $0$ 的边，则必然有 $c_1\ge c_2+\cdots+c_k$，否则将第二个人删掉，只会多出 $c_1$ 的代价，但是会减少 $c_2+\cdots+c_k$ 的代价。因此每向前一个人 $c_i$ 必然翻倍，所以显然有 $k\le \log n$。

这样就直接将 dp 的后两维的取值范围缩小到了 $O(\log n)$ 中，于是直接 dp 即可，复杂度 $O(n\log^2n)$。

[代码](https://atcoder.jp/contests/arc177/submissions/53456039)

---

## 作者：Larunatrecy (赞：0)

我们先想一下传递的过程时什么样的，一定是要么从当前宝箱位置右边找第一个某种颜色的人过来，或者让上一次走某种颜色的边的人从左边走过来。

不管怎样，显然任何时刻每种颜色的人的相对顺序不会改变，那么我们可以设计一个暴力的 dp：

$f_{i,j,k,0/1,0/1}$ 表示当前在点 $i$，当前宝箱左边两种颜色的人分别有 $j,k$ 个，当前点上每种颜色的人有没有，因为相对顺序不变，所以我们可以直接通过状态知道 $i$ 右边第一个某种颜色的点的位置。

转移分为两步：先从右边找人到当前点上（可以是 $0$ 个或 $1$ 个），然后在选择当前点上两种颜色的点是否要走过这条边（至少有一种颜色要走）。

设前 $i$ 个位置两种颜色初始各有 $j_0,k_0$ 个，那么任意时刻一定 $j\geq j_0,k\geq k_0$，因为我们只有右边的人过来。

注意到我们不会从右边过来太多人，因为每次走时，如果从右边来人更优，那说明当前段的长度大于之前走过的距离，也就是说段的总长度翻倍，那么最多只会有 $O(\log n)$ 个人过来，我们只需要记录 $j-j_0,k-k_0$ 即可，复杂度 $O(n\log^2n)$。

```cpp
#pragma GCC optimize("O2,O3,Ofast,inline,unroll-loops")
#pragma GCC target("avx2,sse4")
#include<bits/stdc++.h>
using namespace std;
template <typename T>inline void read(T &x)
{
    x=0;char c=getchar();bool f=0;
    for(;c<'0'||c>'9';c=getchar())f|=(c=='-');
    for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c-'0');
    x=(f?-x:x);
}
const int N = 6e4+7;
typedef long long LL;
int L,n;
char s[N];
int a[N],col[N],pos[N];
int seq[2][N],pre[2][N],cnt[2],sum[2][N];
LL dp[2][50][50][2][2];
void ckmin(LL &x,LL v){x=min(x,v);}
inline int jump(int c,int x,int i)
{
    int p=seq[c][x];
    return sum[c^1][p]-sum[c^1][i];
}
int main()
{
    read(L);read(n);
    scanf("%s",s+1);
    for(int i=1;i<=L;i++)a[i]=(s[i]=='J');
    for(int i=1;i<=L;i++)
    {
        sum[0][i]=(a[i]==0);
        sum[1][i]=(a[i]==1);
        if(i)
        {
            sum[0][i]+=sum[0][i-1];
            sum[1][i]+=sum[1][i-1];
        }
    }
    for(int i=1;i<=n;i++)
    {
        read(pos[i]);
        scanf("%s",s+1);
        col[i]=(s[1]=='J');
        seq[col[i]][++cnt[col[i]]]=pos[i];
        pre[col[i]][pos[i]]++;
    }
    sort(seq[0]+1,seq[0]+cnt[0]+1);
    sort(seq[1]+1,seq[1]+cnt[1]+1);
    for(int i=1;i<=L;i++)pre[0][i]+=pre[0][i-1],pre[1][i]+=pre[1][i-1];
    memset(dp,0x3f,sizeof(dp));
    int lim=18;
    LL inf= dp[0][0][0][0][0];
    dp[0][0][0][min(pre[0][0],1)][min(pre[1][0],1)]=0;
    int cur=0;
    for(int i=0;i<L;i++)
    {
        int d0=(pre[0][i+1]-pre[0][i]);
        int d1=(pre[1][i+1]-pre[1][i]);
        int t=a[i+1];


        int nxt=(cur^1);
        for(int j=0;j<=lim&&j<=cnt[0]-pre[0][i];j++)
        for(int k=0;k<=lim&&k<=cnt[1]-pre[1][i];k++)
        for(int c=0;c<=1;c++)
        for(int d=0;d<=1;d++)
        if(dp[cur][j][k][c][d]!=inf)
        {
            LL W=dp[cur][j][k][c][d];
            //printf("[%d,%d,%d,%d,%d]=%lld\n",i,pre[0][i]+j,pre[1][i]+k,c,d,W);
            for(int C=0;C<=1-c;C++)
            for(int D=0;D<=1-d;D++)
            {
                LL w=W;
                if(C==1)
                {
                    int x=pre[0][i]+j+1;
                    if(x>cnt[0])continue;
                    w+=jump(0,x,i);
                }
                if(D==1)
                {
                    int x=pre[1][i]+k+1;
                    if(x>cnt[1])continue;
                    w+=jump(1,x,i);
                }
                ckmin(dp[nxt][j+C][k+D][c+C][d+D],w);
            }
            dp[cur][j][k][c][d]=inf;
        }
        cur=nxt;
        nxt=(cur^1);
        for(int j=0;j<=lim&&j<=cnt[0]-pre[0][i];j++)
        for(int k=0;k<=lim&&k<=cnt[1]-pre[1][i];k++)
        for(int c=0;c<=1;c++)
        for(int d=0;d<=1;d++)
        if(dp[cur][j][k][c][d]!=inf)
        {
            LL W=dp[cur][j][k][c][d];
            //延续
            int nj=max(pre[0][i]+j,pre[0][i+1])-pre[0][i+1];
            int nk=max(pre[1][i]+k,pre[1][i+1])-pre[1][i+1];
            if(nj>lim||nk>lim)continue;
            for(int C=0;C<=c;C++)
            for(int D=0;D<=d;D++)
            if(C||D)
            {
                int nC=C|(pre[0][i]+j<pre[0][i+1]);
                int nD=D|(pre[1][i]+k<pre[1][i+1]);
                ckmin(dp[nxt][nj][nk][nC][nD],W+C*(t!=0)+D*(t!=1));
            }
            dp[cur][j][k][c][d]=inf;
        }
        cur=nxt;
    }
    LL ans=inf;
    ans=min(ans,dp[cur][0][0][0][1]);
    ans=min(ans,dp[cur][0][0][1][0]);
    ans=min(ans,dp[cur][0][0][1][1]);
    cout<<ans<<endl;
    cerr<<ans<<endl;
    return 0;
}
```

---

