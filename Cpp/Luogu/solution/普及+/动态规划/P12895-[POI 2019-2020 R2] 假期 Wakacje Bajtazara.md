# [POI 2019/2020 R2] 假期 Wakacje Bajtazara

## 题目背景

翻译来自于 [LibreOJ](https://loj.ac/p/4844)。

## 题目描述

**题目译自 [XXVII Olimpiada Informatyczna – II etap](https://sio2.mimuw.edu.pl/c/oi27-2/dashboard/) [Wakacje Bajtazara](https://szkopul.edu.pl/problemset/problem/pXcijJbDyC_jRAjkoxBH9sCO/statement/)**

众所周知，Bajtazar 是一个非常忙碌的人，他从不畏惧字节王国中的任何生活挑战。不过，他终于决定给自己放个假，于是前往比特王国度假。比特王国中有 $n$ 座城市，通过 $n-1$ 条双向道路连接，确保任意两座城市之间都可以通行。Bajtazar 不想连续两天待在同一座城市，但他也不喜欢长途跋涉，所以每天晚上他计划只通过一条道路前往邻近城市。他为每座城市设定了吸引力系数，用来衡量游览这座城市的愉悦程度。当然，他希望度过一个尽可能愉快的假期。

然而，Bajtazar 就是 Bajtazar，他总是喜欢将愉快与实用相结合。这次假期也不例外，他打算利用假期时间开始撰写回忆录。具体来说，他计划在假期中每隔一天游览城市，其余日子用来写作。

他希望规划一个长度为 $2k-1$ 天的假期，其中在 $k$ 个奇数日游览城市，在 $k-1$ 个偶数日写作回忆录。游览过的城市的吸引力系数总和必须尽可能大，同时他不想重复游览同一座城市。不过，在写作的日子，他并不介意待在之前已经去过的城市。请你帮助他规划一个最愉快的假期。

## 说明/提示

**样例 1 解释**

下图展示了比特王国的道路网络示意图。Bajtazar 将游览城市 $3$、$1$、$4$ 和 $7$，这些城市的吸引力系数总和为 $5+3+4+1=13$。

![](https://cdn.luogu.com.cn/upload/image_hosting/hb2mrr0b.png)

**附加样例**

1. 该样例满足四座城市连成一条路径，每座城市的吸引力系数均为 $1$。
2. 该样例满足七座城市构成一棵满二叉树，每座城市的吸引力系数等于其所在深度（根节点深度为 $1$）。
3. 该样例满足一千座城市，每座城市（除了城市 $1$）都与城市 $1$ 直接相连，每座城市的吸引力系数均为 $1$。
4. 该样例满足一百万座城市连成一条路径，每座城市的吸引力系数为 $1$、$2$ 或 $3$。

详细子任务附加限制及分值如下表所示。

如果你的程序正确输出了第一行（即 $W$），但其他行不正确，可以获得该测试点 $40\%$ 的分数。

| 子任务 | 附加限制 | 分值 |
| :---: | :--: | :---: |
| $1$      | $n \leq 1000$，所有 $w_{i}=1$ | $20$   |
| $2$      | $n \leq 1000$         | $10$   |
| $3$      | 所有 $w_{i}=1$        | $40$   |
| $4$      | 无附加限制            | $30$   |

## 样例 #1

### 输入

```
8
3 8 5 4 1 2 1 1
1 2
2 3
2 4
5 4
4 6
7 6
8 7
```

### 输出

```
13
4
3 2 1 2 4 6 7```

# 题解

## 作者：sunkuangzheng (赞：2)

容易发现将树黑白染色后，可以游览的城市颜色相同，因此首先枚举黑白，将另一种颜色点权全部设置为 $0$。

分析我们能走的点的形态，不难发现其实是“毛毛虫”状物，即一条链和到这条链距离为 $1$ 的点。

求解最大权毛毛虫是经典套路，首先记一个点 $u$ 相邻所有点权值和（包括自己）为 $f_u$，则一条路径的 $f_u$ 全部相加后，链中间每个点算了 $3$ 次，端点算了两次。因此记 $g_u = f_u - 2a_u$，路径权值即为 $a_u + a_v + \sum f_x$，类似树的直径求解 DP 即可（注意这里有负权点，可能无法使用两遍 dfs），注意需要钦定直径两端的颜色是我们选择的。


最后输出方案是简单的，按顺序遍历直径输出旁边的点即可。复杂度线性。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 21.06.2025 14:37:44
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 1e6+5;
using namespace std;
int T,n,a[N],u,v,c[N],w[N],fa[N]; vector<int> g[N]; ll f[N];
pair<ll,int> dp[N]; ll W; int du,dv;
void dfs1(int u,int f){
    c[u] = c[f] ^ 1,fa[u] = f;
    for(int v : g[u]) if(v != f) dfs1(v,u);
}void dfs2(int u){
    if(w[u]) dp[u] = {w[u] + f[u],u}; else dp[u] = {-1e18,0}; 
    for(int v : g[u]) if(v != fa[u]){
        dfs2(v);
        if(dp[u].first + dp[v].first > W)
            W = dp[u].first + dp[v].first,
            du = dp[u].second,dv = dp[v].second;
        dp[u] = max(dp[u],{dp[v].first + f[u],dp[v].second}); 
    }
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n;
    for(int i = 1;i <= n;i ++) cin >> a[i];
    for(int i = 1;i < n;i ++) cin >> u >> v,g[u].push_back(v),g[v].push_back(u);
    if(n <= 2){
        cout << *max_element(a+1,a+n+1) << "\n";
        cout << "1\n";
        cout << max_element(a+1,a+n+1) - a << "\n";
        return 0;
    }dfs1(1,0);
    for(int co : {0,1}){
        for(int i = 1;i <= n;i ++) w[i] = (c[i] == co) * a[i];
        for(int i = 1;i <= n;i ++){
            f[i] = -w[i];
            for(int j : g[i]) f[i] += w[j]; 
        }dfs2(1);
        // debug(W,du,dv);
        // printarr(1,n,f);
    }dfs1(du,0);
    vector<int> p;
    cout << W << "\n";
    while(dv) p.push_back(dv),dv = fa[dv];
    // if(p.size() % 2 == 0) p.pop_back();
    assert(p.size() & 1); 
    vector<int> as;
    for(int i = 0;i < p.size();i ++){
        as.push_back(p[i]);
        if(!(i & 1)) continue;
        else{
            for(int v : g[p[i]]) if(v != p[i-1] && v != p[i+1])
                as.push_back(v),as.push_back(p[i]);
        }
    }//if(as.size() % 2 == 0) as.pop_back();
    assert(as.size() % 2 == 1);
    cout << (as.size() + 1) / 2 << "\n";
    for(int v : as) cout << v << " ";
    cout << "\n";
}
```

---

