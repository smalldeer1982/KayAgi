# [GCJ Farewell Round #3] Evolutionary Algorithms

## 题目描述

Ada 正在为学校的科学项目工作。她研究生物进化，并希望比较不同物种在解决编程竞赛问题时的表现。

共有 $\mathbf{N}$ 个物种，编号为 1 到 $\mathbf{N}$。物种 1 没有直接祖先，其他每个物种都有且仅有一个直接祖先。物种 $x$ 的（直接或间接）祖先是指从 $x$ 出发，通过一次或多次向上追溯直接祖先能到达的任何其他物种 $y$。因此，物种 1 是所有其他物种的（直接或间接）祖先。

通过复杂的遗传模拟，她计算了每个物种在特定编程竞赛中的平均得分 $\mathbf{S}_i$（$i$ 为物种编号）。

Ada 希望在她的展示中呈现一些有趣的三元组。一个有趣的三元组定义为满足以下条件的有序三元组 $(a, b, c)$（$a, b, c$ 为不同物种）：

1. 物种 $b$ 是物种 $a$ 的（直接或间接）祖先。
2. 物种 $b$ **不是**物种 $c$ 的（直接或间接）祖先。
3. 物种 $b$ 的平均得分严格大于 $\mathbf{K}$ 倍 $\max(\mathbf{S}_a, \mathbf{S}_c)$，即 $\mathbf{S}_b \geq \mathbf{K} \times \max(\mathbf{S}_a, \mathbf{S}_c) + 1$。

给定物种得分和祖先关系，编写程序计算所有满足条件的有趣三元组数量。

## 说明/提示

**样例解释**

![](https://cdn.luogu.com.cn/upload/image_hosting/4o5vn91i.png)

在样例 #1 中，唯一满足条件的三元组是 $(5, 3, 4)$。验证如下：
1. 物种 3 是物种 5 的祖先。
2. 物种 3 不是物种 4 的祖先。
3. $\mathbf{S}_3 = 6 \geq 2 \times \max(2, 2) + 1 = 5$（设 $\mathbf{K} = 2$）。

![](https://cdn.luogu.com.cn/upload/image_hosting/vi8pvu68.png)

在样例 #2 中，共有 7 个有趣三元组：
- $(4, 3, 1)$
- $(4, 3, 6)$
- $(4, 7, 1)$
- $(4, 7, 5)$
- $(4, 7, 6)$
- $(5, 3, 1)$
- $(5, 3, 6)$

**限制条件**
- $1 \leq \mathbf{T} \leq 100$。
- $1 \leq \mathbf{K} \leq 10^9$。
- $1 \leq \mathbf{S}_i \leq 10^9$。
- 物种 1 是所有其他物种的祖先。

**测试集 1（7 分，可见判定）**
- $3 \leq \mathbf{N} \leq 1000$。

**测试集 2（16 分，隐藏判定）**
- 最多 30 个测试用例：$3 \leq \mathbf{N} \leq 2 \times 10^5$。
- 其余测试用例：$3 \leq \mathbf{N} \leq 1000$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
5 2
3 3 6 2 2
3 1 1 3
7 3
2 4 7 2 2 1 8
6 1 7 3 1 3```

### 输出

```
Case #1: 1
Case #2: 7```

# 题解

## 作者：_zjzhe (赞：1)

观察一下每一个条件都与 $b$ 有关，考虑枚举 $b$。
发现 $a$ 一定是 $b$ 子树内的点，$c$ 一定是 $b$ 子树外的点。再玩一下条件 3 的式子，$\mathbf{S}_b \geq \mathbf{K} \times \max(\mathbf{S}_a, \mathbf{S}_c) + 1$ 即 $\lfloor\frac{\mathbf{S}_b - 1}{\mathbf{K}}\rfloor \geq \max(\mathbf{S}_a, \mathbf{S}_c)$，只需满足 $\mathbf{S}_a$ 和 $\mathbf{S}_c$ 都不大于 $\lfloor\frac{\mathbf{S}_b - 1}{\mathbf{K}}\rfloor$ 即可。设 
$$ans_{u,0}=\sum\limits_{v\in subtree(u)}[\mathbf{S}_v\le \lfloor\frac{\mathbf{S}_u - 1}{\mathbf{K}}\rfloor]$$
$$ans_{u,1}=\sum\limits_{v\notin subtree(u)}[\mathbf{S}_v\le \lfloor\frac{\mathbf{S}_u - 1}{\mathbf{K}}\rfloor]$$

最终答案就是 $\sum\limits_{i=1}^n ans_{i,0}\times ans_{i,1}$。\
求 $ans$ 可以记录下 `dfn` 序，将子树问题放到序列上，离线下来做二维数点即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
typedef long long ll;
int T,n,k,s[N],dfn[N],dn,low[N],id[N],lsh[N],ct,t;
ll val[N<<1];
vector<int>lk[N];
//y,coef,id,part
vector<array<int,4>>q[N];
void add(int x,int v){
    for(;x<=ct;x+=x&-x)val[x]+=v;
}
ll query(int x){
    ll res=0;
    for(;x;x-=x&-x)res+=val[x];
    return res;
}
void D1(int u){
    dfn[u]=++dn,id[dn]=u;
    for(int v:lk[u])D1(v);
    low[u]=dn;
}
void D2(int u){
    int x=lower_bound(lsh+1,lsh+1+t,(s[u]-1)/k)-lsh;
    q[dfn[u]-1].push_back({x,-1,u,0});
    q[low[u]].push_back({x,1,u,0});
    q[dfn[u]-1].push_back({x,1,u,1});
    q[low[u]].push_back({x,-1,u,1});
    q[n].push_back({x,1,u,1});
    for(int v:lk[u])D2(v);
}
int main(){
    cin>>T;
    for(int c=1;c<=T;c++){
        cin>>n>>k;ct=dn=0;memset(val,0,sizeof(val));
        for(int i=1;i<=n;i++)cin>>s[i],lk[i].clear(),q[i].clear();
        for(int i=1;i<=n;i++)lsh[++ct]=s[i],lsh[++ct]=(s[i]-1)/k;
        sort(lsh+1,lsh+1+ct);
        t=unique(lsh+1,lsh+1+ct)-lsh-1;
        for(int i=2,f;i<=n;i++)cin>>f,lk[f].push_back(i);
        D1(1),D2(1);vector<vector<ll>>ans(n+1,vector<ll>(2,0));
        for(int i=1;i<=n;i++){
            add(lower_bound(lsh+1,lsh+1+t,s[id[i]])-lsh,1);
            for(auto [y,coef,u,part]:q[i])ans[u][part]+=coef*query(y);
        }
        ll res=0;
        for(int i=1;i<=n;i++)res+=ans[i][0]*ans[i][1];
        cout<<"Case #"<<c<<": "<<res<<'\n';
    }

    return 0;
}
```

---

