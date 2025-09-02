# [GCJ 2022 Finals] Schrödinger and Pavlov

## 题目描述

_本题目中所有故事、名称、角色和情节均为虚构。如有雷同，纯属巧合。_

1935 年，两位诺贝尔奖得主的会面产生了惊人的结果。著名物理学家**薛定谔**邀请著名生理学家**巴甫洛夫**参观他的"猫在箱子里"的实验。巴甫洛夫带着他的狗一同前来以继续自己的研究，两者的实验相结合产生了有趣的现象。

薛定谔有一排 $\mathbf{N}$ 个箱子。某些箱子中肯定有一只猫，某些箱子肯定没有猫，还有些箱子可能有也可能没有猫。每个箱子只能容纳一只猫。每个箱子还配备了一个特殊的**量子隧道**，允许箱子里的猫移动到另一个特定的箱子（前提是目标箱子是空的）。隧道的运作是单向的。

猫通常很安静，除非受到惊吓才会使用隧道。当一位不速之客按响门铃时，巴甫洛夫的狗立即兴奋起来，开始边跑边叫。狗从 1 号箱子开始，一直跑到 $\mathbf{N}$ 号箱子。当它经过一个有猫的箱子时，会惊吓到里面的猫。受惊的猫会检查可用的隧道：如果目标箱子是空的，就会通过隧道逃跑；如果目标箱子已被占据，猫就会留在原地。同一只猫可能会被多次惊吓（如果它移动到了狗还未经过的箱子），每次受惊时都会以相同的方式检查隧道（但每次只能使用新位置的隧道）。

![](https://cdn.luogu.com.cn/upload/image_hosting/xcqaev9m.png)

当狗最终停在最后一个箱子旁时，巴甫洛夫问薛定谔最后一个箱子里是否有猫。薛定谔（不出所料）回答说他不知道。巴甫洛夫意识到，答案取决于那些未知箱子中是否有猫。由于有 $k$ 个未知箱子，共有 $2^k$ 种可能的**初始配置**（每种对应未知箱子状态的一种组合）。巴甫洛夫建议他们应该计算有多少种初始配置会导致最后一个箱子里有猫。你需要重现这个计算过程。由于结果可能非常大，只需输出其对质数 $10^9 + 7$（1000000007）取模的值。

*在本题描述过程中，没有猫、狗或诺贝尔奖得主受到伤害。*

## 说明/提示

**样例解释**

样例 #1 的情况如题目描述所示。4 种可能的初始配置中，只有 `CC.C` 会导致最后一个箱子最终有猫。

样例 #2 中，由于没有隧道通向最后一个箱子，只有当最后一个箱子初始有猫时才可能最终有猫。经分析共有 2 种符合条件的配置。

样例 #3 中，要使最后一个箱子最终有猫，必须满足：5 号箱子初始有猫，且至少还有一个其他箱子有猫。符合条件的配置共有 $2^4 - 1 = 15$ 种。

样例 #4 中，对于所有 $2^k$ 种可能的初始配置，最后一个箱子最终都会有猫。

**限制条件**

- $1 \leq \mathbf{T} \leq 1234$
- $\mathbf{S}$ 的长度等于 $\mathbf{N}$
- $\mathbf{S}$ 的每个字符是大写的 'c'、'.' 或 '?'
- $1 \leq \mathbf{B}_i \leq \mathbf{N}$ 且 $\mathbf{B}_i \neq i$（所有 $i$）

**测试集 1（8 分，可见判定）**

- $1 \leq \mathbf{N} \leq 100$
- $i - 5 \leq \mathbf{B}_i \leq i + 5$（所有隧道都连接到附近的箱子）

**测试集 2（42 分，隐藏判定）**

- $1 \leq \mathbf{N} \leq 5000$

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
4
??.C
2 3 1 3
4
????
2 3 1 3
6
?.????
6 6 6 6 6 5
34
????????????????????????????????CC
2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 33```

### 输出

```
Case #1: 1
Case #2: 2
Case #3: 15
Case #4: 294967268```

# 题解

## 作者：Jorisy (赞：1)

下文用「节点」代替题目中的「箱子」。

算方案数有点小困难，我们考虑算概率。

设节点 $i$ 有猫的概率为 $p_i$。

那么答案的方案数也就是 $p_n\cdot 2^{c_{\texttt?}}$，其中 $c_{\texttt?}$ 是未知是否有猫的节点数。

由于原图中每个节点都恰好有一条出边，所以这是一个内向基环树森林。那么显然不和 $n$ 连通的点都不用管。考虑剩下的这一棵内向基环树要怎么处理。

如果是一棵内向树，那这是简单的，我们可以直接模拟一下猫的移动情况，并更新每个节点有猫的概率。假如目前在节点 $i$，它连向的边是 $a_i$，那么
节点 $i$ 仍然有猫的概率被更新为 $p_i\cdot p_{a_i}$，而节点 $a_i$ 的概率就被更新为 $p_i+p_{a_i}-p_i\cdot p_{a_i}$。

但是我们现在多了一条边。我们可以直接枚举这条边两侧的节点是否有猫的情况，即枚举这两个点有猫的概率是 $1$ 还是 $0$，然后我们对应地更新即可。

```cpp
#include<bits/stdc++.h>
#define N 5005
#define ll long long
#define mod 1000000007
using namespace std;

struct dsuni{
    int fa[N];
    void init(int n){iota(fa+1,fa+n+1,1);}
    int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
    bool merge(int u,int v)
    {
        u=find(u);
        v=find(v);
        if(u==v) return 0;
        fa[v]=u;
        return 1;
    }
}dsu;
vector<int>vec;
string s;
int n,nxt[N];
ll p[N],ans;

void sol()
{
    cin>>n>>s;
    s=' '+s;
    ans=0;
    vec.clear();
    dsu.init(n);
    for(int i=1;i<=n;i++)
    {
        cin>>nxt[i];
        dsu.merge(i,nxt[i]);
    }
    for(int i=n;i;i--)
    {
        if(dsu.find(i)^dsu.find(n)) continue;
        vec.push_back(i);
    }
    dsu.init(n);
    int cyc;
    for(auto i:vec)
    {
        if(dsu.merge(i,nxt[i])) continue;
        cyc=i;
        break;
    }
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
        {
            for(int k=1;k<=n;k++) p[k]=s[k]=='.'?0:s[k]=='C'?1:(mod+1>>1);
            ll s;
            for(int k=1;k<=n;k++)
            {
                if(k==cyc)
                {
                    s=((i?p[k]:mod+1-p[k])*(j?p[nxt[k]]:mod+1-p[nxt[k]]))%mod;
                    p[k]=i;
                    p[nxt[k]]=j;
                }
                ll x=p[k],y=p[nxt[k]];
                p[k]=x*y%mod;
                p[nxt[k]]=(x+y-p[k]+mod)%mod;
            }
            (ans+=s*p[n]%mod)%=mod;
        }
    }
    for(int i=1;i<=n;i++) (ans*=s[i]=='?'?2:1)%=mod;
    static int cas=0;
    cout<<"Case #"<<++cas<<": "<<ans<<'\n';
}

int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--) sol();
    return 0;
}
```

---

