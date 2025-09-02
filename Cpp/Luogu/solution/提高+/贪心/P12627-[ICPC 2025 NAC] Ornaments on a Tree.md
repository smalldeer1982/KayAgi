# [ICPC 2025 NAC] Ornaments on a Tree

## 题目描述

你正在帮朋友装饰圣诞树！有趣的是，圣诞树上挂装饰品的位置可以用一棵（图论中的）树来表示，树的节点编号为 $1$ 到 $N$，其中节点 $1$ 是树的根，其他节点编号任意。你有无限多个重量为非负整数（包括 $0$）的装饰品，必须在树的每个节点上恰好挂一个装饰品。

不过，朋友对装饰方式有一些限制。首先，他们对某些节点必须挂什么装饰品有严格要求；你只能自由选择其他节点的装饰品。其次，圣诞树的每个区域只能承受一定重量：如果一个节点及其所有直接子节点上的装饰品重量之和超过常数 $K$，整棵树就会倒塌！

在满足上述限制的条件下，朋友想知道树上装饰品的最大可能总重量。你能帮他们找到答案吗？

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5 10
-1 2 3 -1 -1
1 2
1 3
2 4
2 5```

### 输出

```
18```

## 样例 #2

### 输入

```
1 5
-1```

### 输出

```
5```

## 样例 #3

### 输入

```
2 5
5 5
1 2```

### 输出

```
-1```

# 题解

## 作者：fyxblyn (赞：1)

## 题意
给定一颗有 $N$ 个节点的树，其中一些点的点权已经确定，为剩下节点确定一个非负整数点权，使得没有任何节点及其直接子节点点权之和大于 $K$，并使所有节点点权之和最大。

## 思路
记 $sum_i$ 为节点 $i$ 及其所有直接子节点的点权之和。

由于点权可以为 $0$，判断无解时只需要看已经确定点权的点有没有超出限制即可。

显然，处理一个节点的点权时只需考虑它自身（设为 $i$）和其父节点（设为 $fa$），即保证 $sum_i$ 和 $sum_{fa}$ 不超过 $K$，这启发我们由下往上进行处理。

由于需要最大化点权之和，$i$ 的点权自然越大越好，所以我们得到节点 $i$ 的最优点权为：
$$\min(K-sum_i,K-sum_{fa})$$

这保证能在 $i$ 节点处获得局部最优，同时因为 $i$ 与 $fa$ 的父节点无关，这个局部最优即可推广到全局最优。

注意记录已经确定点权的点，并在处理时直接跳过它们。

具体实现可以参考代码。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+5;
struct node
{
    int v,nt;
}e[N];
int head[N],tot;
void add(int u,int v)
{
    e[++tot]={v,head[u]};
    head[u]=tot;
}
int a[N],sum[N],f[N],flag[N];
void dfs1(int u,int fa)
{
    f[u]=fa;
    for(int i=head[u];i;i=e[i].nt)
    {
        int v=e[i].v;
        if(v==fa)continue;
        sum[u]+=a[v];
        dfs1(v,u);
    }
}
int n,m;
void dfs2(int u)
{
    for(int i=head[u];i;i=e[i].nt)
    {
        int v=e[i].v;
        if(v==f[u])continue;
        dfs2(v);
    }
    if(flag[u])return;
    int num=min(m-sum[u],m-sum[f[u]]);
    a[u]+=num,sum[u]+=num,sum[f[u]]+=num;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]==-1)a[i]=0;
        else flag[i]=1;
        sum[i]=a[i];
    }
    for(int i=1,u,v;i<n;i++)
    {
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs1(1,1);
    for(int i=1;i<=n;i++)
    {
        if(sum[i]>m)
        {
            cout<<"-1";
            return 0;
        }
    }
    dfs2(1);
    int ans=0;
    for(int i=1;i<=n;i++)ans+=a[i];
    cout<<ans;
    return 0;
}
```

---

## 作者：liuchuliang666 (赞：0)

对于贪心题，首先大胆搞一个策略：能多放就多放！

事实上这是对的。

我们自下至上处理，对于没被固定的结点，尽可能地塞最大值。

然后如果子节点的权值和超过了，可以直接降掉他的权值，毕竟限制是不超过，调小绝对没问题。

如果调不小，就是无解。

附上丑陋的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int ll
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
constexpr int MAXN = 2e5 + 10;
int n, w[MAXN], a[MAXN], k, ans;
vi e[MAXN];
void dfs(int u, int f)
{
    int p = 0, q = 0; // p: 固定的和，q：非固定的子结点最大和
    for (int v : e[u])
        if (v ^ f)
        {
            dfs(v, u);
            if (~a[v])
                p += a[v];
            else
                q += w[v];
        }
    // 固定的
    if (~a[u]) p += a[u];
    if (p > k) cout << -1, exit(0);
    if (~a[u])
    {
        w[u] = a[u];
        ans += w[u];
        ans -= max(0ll, q + p - k);
    }
    // 没固定
    else
    {
        if (p + q >= k)
            ans -= (p + q - k); // 多了直接减
        else
            ans += (k - p - q), w[u] = k - p - q; // 能放就放
    }
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int u, v, i = 1; i < n; i++) cin >> u >> v, e[u].emplace_back(v), e[v].emplace_back(u);
    dfs(1, 0);
    cout << ans;
    return 0;
}
```

---

