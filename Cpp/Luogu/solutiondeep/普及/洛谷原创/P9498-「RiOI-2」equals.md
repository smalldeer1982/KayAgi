# 题目信息

# 「RiOI-2」equals

## 题目背景

在小树上坐落着一个幻想的城堡。这里是 E 国的领地，而小 E，则是 E 国之王。

为了打造一个完美的 E 国，他需要明辨是非，走向正义。

但是，他似乎有些太理想了。有时并没有一个完美的准则。是黑是白，谁能分辨？

## 题目描述

给定一棵 $n$ 个结点，以 $1$ 为根的树，定义一个结点的深度 $d_i$ 表示它到根结点的简单路径上的结点个数。

你需要给每个结点黑白染色，满足黑色结点的深度和等于白色结点的深度和。设 $c_i = \{0, 1\}$ 分别代表编号为 $i$ 的结点为黑色或白色，那么这即 $\displaystyle\sum_{c_i=0}d_i=\sum_{c_i=1}d_i$。

若无解，仅输出一行一个整数 $-1$。

## 说明/提示

### 样例解释

对于第一组数据，每个结点的深度分别是 $d=[1,2,2,3,3,3]$。黑色结点的深度和为 $d_1+d_5+d_6=1+3+3=7$，白色结点的深度和为 $d_2+d_3+d_4=2+2+3=7$。它们相等，所以样例输出是正确的。可能的正确输出包括但不限于样例输出、`0 1 1 0 0 1`，`1 0 0 1 0 1` 等。

### 数据规模与约定

**本题采用捆绑测试。**

| $\rm Subtask$ | 分值 | $n\le $ | 特殊性质 |
| :-----------: | :--: | :-----: | :------: |
| $0$ | $5$ | $20$ | / |
| $1$ | $15$ | $500$ | / |
| $2$ | $20$ | $5\times 10^3$ | / |
| $3$ | $10$ | / | $n$ 为偶数 |
| $4$ | $5$ | / | 树为菊花图（不保证根为菊花中心） |
| $5$ | $5$ | / | 树为一条链（不保证根为链的端点） |
| $6$ | $40$ | / | / |

斜杠表示这一栏无特殊限制。

对于 $100\%$ 的数据，$1\le n\le 10^6$，$1\le u_i,v_i\le n$，输入数据构成一棵树。

## 样例 #1

### 输入

```
6
1 2
1 3
2 4
2 5
2 6```

### 输出

```
0 1 1 1 0 0```

## 样例 #2

### 输入

```
5
1 2
1 3
2 4
2 5```

### 输出

```
-1```

# AI分析结果

• **综合分析与结论**：这些题解的核心思路围绕判断树节点深度和的奇偶性，以及利用树深度序列的连续性进行贪心构造染色方案。对于深度和为奇数的情况，所有题解都认为无解。在处理深度和为偶数的情况时，大部分题解采用贪心策略，从大到小或从小到大遍历排序后的深度序列，通过调整选取的节点使两组深度和相等。部分题解还针对特殊子任务给出了特定解法。从质量上看，部分题解思路清晰、代码可读性较好且有一定优化，部分题解在思路阐述或代码规范上存在不足。

• **所选的题解**：
  - **作者：TernaryTree (5星)**
    - **关键亮点**：对每个子任务都有详细分析，给出了爆搜、记忆化搜索、背包等基础解法，针对不同特殊性质的子任务有独特思路，如菊花图和链的分类讨论，对通用情况提出从后往前分组的贪心策略并给出严谨正确性证明，提供了dfs和bfs两种实现方式且分析复杂度。
    - **重点代码 - dfs实现**：
```cpp
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second

using namespace std;

const int maxn = 1e6 + 10;

int n, tot, cur, flag;
vector<int> g[maxn];
pair<int, int> dep[maxn];
int c[maxn];

void dfs(int u, int fa) {
    dep[u] = make_pair(dep[fa].fs + 1, u);
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v!= fa) dfs(v, u);
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1, u, v; i <= n - 1; i++) {
        cin >> u >> v;
        g[u].push_back(v), g[v].push_back(u);
    }
    dfs(1, 0);
    if (n & 1) ++n, flag = true;
    sort(dep + 1, dep + 1 + n);
    for (int i = 1; i <= n; i++) tot += dep[i].fs;
    if (tot & 1) return (puts("-1"), 0);
    for (int i = 1; i <= n; i += 2) {
        if (dep[i].fs == dep[i + 1].fs) c[dep[i].sc] = 0, c[dep[i + 1].sc] = 1;
        else c[dep[i].sc] = cur == -1, c[dep[i + 1].sc] =!c[dep[i].sc], cur = cur!= 0? 0 : -1;
    }
    for (int i = 1; i <= n - flag; i++) cout << c[i] << " ";
    return 0;
}
```
核心实现思想：先通过dfs获取每个节点深度，若节点数为奇数则虚拟增加一个节点，对深度序列排序后，根据深度对节点分组染色，通过维护偏移量保证最终黑色和白色深度和相等。
  - **作者：ys_kylin__ (4星)**
    - **关键亮点**：先阐述暴力做法，然后点明树深度序列连续性这一关键性质，基于此提出先求和判断奇偶性，再贪心构造染色方案的思路，代码实现简洁明了。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
vector <int> ve[1000005];//vector存图
int ans[1000005];
int n;
struct node {
    int num,id;
}d[1000005];
void dfs(int x,int ftr) {//将深度构建
    for(int i=0;i<ve[x].size();i++) {
        int v=ve[x][i];
        if(v==ftr) continue;
        d[v].num=d[x].num+1;
        dfs(v,x);
    }
}
bool cmp(node x,node y) {
    return x.num<y.num;
}
signed main() {
    scanf("%lld",&n);
    for(int i=1;i<n;i++) {
        int u,v;
        scanf("%lld%lld",&u,&v);
        ve[u].push_back(v);
        ve[v].push_back(u);
        d[i].id=i;
    }
    d[n].id=n;
    d[1].num=1;
    dfs(1,-114);
    int sum=0,sum2=0;
    for(int i=1;i<=n;i++) {
        sum+=d[i].num;
    }
    if(sum%2==1) {
        printf("-1");//必为无解
        return 0;
    }
    sort(d+1,d+n+1,cmp);
    for(int i=n;i;i--) {
        if(sum2+d[i].num<sum/2) {//满足条件直接染色
            sum2+=d[i].num;
            ans[d[i].id]=1;
        }
        else {
            for(int j=i;j;j--) {//向下查找
                if(sum2+d[j].num==sum/2) {
                    ans[d[j].id]=1;
                    break;
                }
            }
            for(int j=1;j<=n;j++) printf("%lld ",ans[j]);
            return 0;
        }
    }
    return 0;
}
```
核心实现思想：dfs获取深度，排序后从大到小贪心遍历深度序列，若当前深度加入后不超过总和一半则染色，否则查找合适深度染色。
  - **作者：sane1981 (4星)**
    - **关键亮点**：解读题目清晰，快速将问题转化为挑选数使和为深度总和一半的问题，提出贪心策略并给出详细证明，代码简洁，注释清晰。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#include<vector>
using namespace std;
int n,a,b;
long long need;
vector <int> e[1000005];
int ans[1000005];
struct point{
    int deep,id;
}c[1000005];
bool cmp(point x,point y){
    return x.deep<y.deep;
}
void dfs(int u,int fa){
    c[u].deep=c[fa].deep+1;
    c[u].id=u;
    for(int i=0;i<e[u].size();i++){
        int v=e[u].size();
        if(v==fa) continue;
        dfs(v,u);
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&a,&b);
        e[a].push_back(b);
        e[b].push_back(a);
    }
    dfs(1,0);
    sort(c+1,c+n+1,cmp);
    for(int i=1;i<=n;i++) need+=(long long)c[i].deep;
    if(need&1){
        printf("-1\n");
        return 0;
    }
    long long cut=0,temp=0;
    for(int i=1;i<=n;i++){
        temp+=(long long)c[i].deep;
        ans[c[i].id]=1;
        if(temp>=need/2){
            cut=temp-need/2;
            break;
        }
    }
    for(int i=1;i<=n;i++)
        if(cut==(long long)c[i].deep){
            ans[c[i].id]=0;
            break;
        }
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    printf("\n");
    return 0;
}
```
核心实现思想：dfs求深度，排序后从小到大贪心累加深度，找到第一个超过总和一半的位置，减去超出部分对应的深度节点。

• **最优关键思路或技巧**：利用树深度序列的连续性和单调性是解决本题的关键。通过对深度序列排序，从大到小或从小到大贪心选取节点，能有效构造出满足条件的染色方案。同时，先判断深度总和的奇偶性可快速排除无解情况。

• **可拓展思路**：此类题目属于树结构上的组合优化问题，类似套路包括利用树的特殊性质（如深度、层次、子树结构等）进行贪心、动态规划等。同类型题可考虑改变树的约束条件、目标函数（如改为最大化或最小化某种差值）等。

• **推荐题目**：
  - [P1273 有线电视网](https://www.luogu.com.cn/problem/P1273)：树上的背包问题，结合树结构与背包思想。
  - [P2014 选课](https://www.luogu.com.cn/problem/P2014)：依赖关系的树形动态规划，与本题利用树结构特点解题类似。
  - [P3177 [HAOI2015]树上染色](https://www.luogu.com.cn/problem/P3177)：树结构上的染色优化问题，考察对树性质的运用和动态规划技巧。

• **个人心得摘录**：众多题解中多次强调“不开long long见祖宗”，表明在处理数据时要注意数据范围，避免因数据类型导致错误。 

---
处理用时：54.01秒