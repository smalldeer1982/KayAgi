# 题目信息

# Begginer's Zelda

## 题目描述

You are given a tree $ ^{\dagger} $ . In one zelda-operation you can do follows:

- Choose two vertices of the tree $ u $ and $ v $ ;
- Compress all the vertices on the path from $ u $ to $ v $ into one vertex. In other words, all the vertices on path from $ u $ to $ v $ will be erased from the tree, a new vertex $ w $ will be created. Then every vertex $ s $ that had an edge to some vertex on the path from $ u $ to $ v $ will have an edge to the vertex $ w $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1905B/c3222ff4e4569cd9f8a56d2650b8f98bd69be3cf.png) Illustration of a zelda-operation performed for vertices $ 1 $ and $ 5 $ .Determine the minimum number of zelda-operations required for the tree to have only one vertex.

 $ ^{\dagger} $ A tree is a connected acyclic undirected graph.

## 说明/提示

In the first test case, it's enough to perform one zelda-operation for vertices $ 2 $ and $ 4 $ .

In the second test case, we can perform the following zelda-operations:

1. $ u = 2, v = 1 $ . Let the resulting added vertex be labeled as $ w = 10 $ ;
2. $ u = 4, v = 9 $ . Let the resulting added vertex be labeled as $ w = 11 $ ;
3. $ u = 8, v = 10 $ . After this operation, the tree consists of a single vertex.

## 样例 #1

### 输入

```
4
4
1 2
1 3
3 4
9
3 1
3 5
3 2
5 6
6 7
7 8
7 9
6 4
7
1 2
1 3
2 4
4 5
3 6
2 7
6
1 2
1 3
1 4
4 5
2 6```

### 输出

```
1
3
2
2```

# AI分析结果

### 题目内容（中文重写）
# 新手塞尔达

## 题目描述
给定一棵树 $ ^{\dagger} $。在一次塞尔达操作中，你可以执行以下操作：
- 选择树中的两个顶点 $ u $ 和 $ v $；
- 将从 $ u $ 到 $ v $ 路径上的所有顶点压缩为一个顶点。换句话说，从 $ u $ 到 $ v $ 路径上的所有顶点将从树中删除，并创建一个新的顶点 $ w $。然后，每个与从 $ u $ 到 $ v $ 路径上的某个顶点有边相连的顶点 $ s $，都将与顶点 $ w $ 有边相连。

![对顶点 $ 1 $ 和 $ 5 $ 执行塞尔达操作的图示](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1905B/c3222ff4e4569cd9f8a56d2650b8f98bd69be3cf.png)

确定将树压缩为只有一个顶点所需的最少塞尔达操作次数。

$ ^{\dagger} $ 树是一个连通的无环无向图。

## 说明/提示
在第一个测试用例中，对顶点 $ 2 $ 和 $ 4 $ 执行一次塞尔达操作就足够了。

在第二个测试用例中，我们可以执行以下塞尔达操作：
1. $ u = 2, v = 1 $。设得到的新增顶点标记为 $ w = 10 $；
2. $ u = 4, v = 9 $。设得到的新增顶点标记为 $ w = 11 $；
3. $ u = 8, v = 10 $。在这次操作之后，树就只包含一个顶点了。

## 样例 #1
### 输入
```
4
4
1 2
1 3
3 4
9
3 1
3 5
3 2
5 6
6 7
7 8
7 9
6 4
7
1 2
1 3
2 4
4 5
3 6
2 7
6
1 2
1 3
1 4
4 5
2 6
```

### 输出
```
1
3
2
2
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心策略，即每次操作尽量覆盖更多的叶子节点。要点在于发现一条链最多覆盖 $2$ 个叶子节点，设叶子节点个数为 $cnt$，则答案为 $\lceil \frac{cnt}{2} \rceil$。解决的难点在于证明该贪心策略的正确性，即要说明按照此策略操作能以最少次数将树缩为一个点。

### 所选题解
- **作者：__little__Cabbage__ (4星)**
    - **关键亮点**：思路清晰，详细证明了贪心策略的正确性，代码简洁规范。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
//#define int long long
#define il inline
using namespace std;

const int MAXN=1e5+5;
int n,deg[MAXN];

il void solve()
{
    cin>>n;
    for(int i=1;i<=n;++i) deg[i]=0;
    int _u,_v;
    for(int i=1;i<=n-1;++i) cin>>_u>>_v,++deg[_u],++deg[_v];

    int cnt=0;
    for(int i=1;i<=n;++i) if(deg[i]==1) ++cnt;

    cout<<((cnt+1)>>1)<<'\n';
}

signed main()
{
    ios::sync_with_stdio(0);
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin>>T;
    while(T--)
        solve();
    return 0;
}
```
    - **核心实现思想**：先统计每个节点的度数，度数为 $1$ 的节点即为叶子节点，统计叶子节点个数 $cnt$，最后输出 $\lceil \frac{cnt}{2} \rceil$。

- **作者：wmrqwq (4星)**
    - **关键亮点**：思路简洁明了，代码风格统一，注释丰富。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) x&-x
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
long long t,n,u,v,sum[1000010],ans,a[1000010];
int main()
{
    IOS;
    cin>>t;
    while(t--)
    {
        cin>>n;
        ans=0;
        forl(i,1,n)
            sum[i]=0;
        forl(i,1,n-1)
            cin>>u>>v,sum[u]++,sum[v]++,a[u]=v,a[v]=u;
        forl(i,1,n)
            if(sum[i]==1)
                ans++;
        cout<<(ans+1)/2<<endl;
    }
    QwQ;
}
```
    - **核心实现思想**：同样是先统计每个节点的度数，找出叶子节点个数，最后计算并输出答案。

- **作者：xiaoxiongbinggan (4星)**
    - **关键亮点**：思路清晰，对贪心策略的解释通俗易懂，代码简洁。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int T;
int n;
int u,v;
int f[100000];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        memset(f,0,sizeof f);
        for(int i=1;i<n;i++){
            cin>>u>>v;   
            f[u]++;
            f[v]++;
        }
        int ans=0; 
        for(int i=1;i<=n;i++){
            if(f[i]==1){
                ans++;
            }
        }
        cout<<(ans+1)/2<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：统计节点度数，确定叶子节点个数，计算并输出 $\lceil \frac{cnt}{2} \rceil$。

### 最优关键思路或技巧
- **思维方式**：采用贪心策略，每次操作尽量覆盖更多的叶子节点，通过分析叶子节点的覆盖情况得出结论。
- **代码实现技巧**：通过统计节点的度数来确定叶子节点，避免了复杂的图遍历操作。

### 可拓展之处
同类型题目可能会对操作规则进行变化，例如改变合并的条件或增加其他限制，但核心思路可能还是围绕贪心策略，通过分析关键元素（如叶子节点）来找到最优解。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：同样是贪心策略，每次选择最小的两个元素合并。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：贪心算法，按照接水时间从小到大排序。
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：贪心策略，优先选择单位价值高的物品。

### 个人心得摘录与总结
- **Miracle_1024**：开始用了 `memset` 归零，因为 $N$ 开太大一直 TLE。总结：在使用 `memset` 时要注意数组大小，避免因不必要的操作导致超时。 

---
处理用时：50.34秒