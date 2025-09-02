# 题目信息

# Two Paths

## 题目描述

As you know, Bob's brother lives in Flatland. In Flatland there are $ n $ cities, connected by $ n-1 $ two-way roads. The cities are numbered from 1 to $ n $ . You can get from one city to another moving along the roads.

The «Two Paths» company, where Bob's brother works, has won a tender to repair two paths in Flatland. A path is a sequence of different cities, connected sequentially by roads. The company is allowed to choose by itself the paths to repair. The only condition they have to meet is that the two paths shouldn't cross (i.e. shouldn't have common cities).

It is known that the profit, the «Two Paths» company will get, equals the product of the lengths of the two paths. Let's consider the length of each road equals 1, and the length of a path equals the amount of roads in it. Find the maximum possible profit for the company.

## 样例 #1

### 输入

```
4
1 2
2 3
3 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
7
1 2
1 3
1 4
1 5
1 6
1 7
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6
1 2
2 3
2 4
5 4
6 4
```

### 输出

```
4
```

# AI分析结果

### 题目重写
# 两条路径

## 题目描述
如你所知，鲍勃的兄弟住在平面国。在平面国中有 $n$ 个城市，由 $n - 1$ 条双向道路连接。城市从1到 $n$ 编号。你可以沿着道路从一个城市到达另一个城市。
鲍勃兄弟工作的“两条路径”公司赢得了一个在平面国修复两条路径的招标。一条路径是由不同城市组成的序列，这些城市通过道路依次连接。该公司可以自行选择要修复的路径。他们必须满足的唯一条件是这两条路径不应交叉（即不应有共同的城市）。
已知“两条路径”公司将获得的利润等于两条路径长度的乘积。假设每条道路的长度为1，路径的长度等于其中道路的数量。求该公司可能获得的最大利润。

## 样例 #1
### 输入
```
4
1 2
2 3
3 4
```
### 输出
```
1
```

## 样例 #2
### 输入
```
7
1 2
1 3
1 4
1 5
1 6
1 7
```
### 输出
```
0
```

## 样例 #3
### 输入
```
6
1 2
2 3
2 4
5 4
6 4
```
### 输出
```
4
```

### 算法分类
搜索

### 综合分析与结论
这些题解的核心思路都是利用数据范围较小（$n \leq 200$）的特点，通过枚举树中的每一条边，将树分成两棵子树，然后分别求这两棵子树的直径，计算其直径乘积并取最大值。主要难点在于理解两条不相交路径与树结构之间的关系，即两条不相交路径必然存在于通过删除某条边而分开的两棵子树中。各题解在实现细节上略有不同，如求树直径的方式、数据结构的选择等。

### 所选的题解
- **作者：lottle1212 (5星)**
    - **关键亮点**：思路清晰，先解读题目，点明是树的直径升级版，随后给出 $O(n^2)$ 的算法思路，即枚举边并对两边子树求直径，代码简洁明了，使用邻接表建边和DFS求树的直径。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mxn = 200;
const ll N = mxn + 10;
ll n, u[N], v[N], head[N], dp[N], cnt, ans, sum, s;
struct Edge { ll nxt, to; } e[N * 2];//邻接表
void add(ll u, ll v) { e[++ cnt] = {head[u], v}, head[u] = cnt; }//邻接表建边
void dfs(ll u, ll pre) {
    dp[u] = 0;
    for(ll i = head[u], v; i; i = e[i].nxt) {
        v = e[i].to;
        if(v == pre) continue;
        dfs(v, u);
        sum = max(sum, dp[u] + dp[v] + 1);
        dp[u] = max(dp[u], dp[v] + 1);
    }
    return ;
}//搜索，求树的直径
signed main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    for(ll i = 1; i < n; ++ i) cin >> u[i] >> v[i], add(u[i], v[i]), add(v[i], u[i]);
    for(ll i = 1; i < n; ++ i) {
        s = 1;
        dfs(u[i], v[i]);//对第一个区块进行搜索
        s *= sum, sum = 0;
        dfs(v[i], u[i]);//对第二个区块进行搜索
        s *= sum, sum = 0;
        ans = max(ans, s);//求最大
    }
    cout << ans;
    return 0;
}
```
    - **核心实现思想**：通过邻接表存储树结构，`dfs`函数在求树直径时，利用`dp`数组记录每个节点出发的最长路径，`sum`记录经过当前节点的最长路径，通过两次`dfs`分别对断开边后的两棵子树求直径并计算乘积更新答案。

- **作者：lenlen (4星)**
    - **关键亮点**：同样清晰阐述思路，强调两条不相交链与树结构的关系，代码注释详细，对求树直径的DP方法进行了详细解释。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
int h[732],cnt=1,dp[732],sum;
struct len{
    int u,v;
}t[732];
struct hl{
    int v,nxt;
}e[1732];
void add(int u,int v)
{
    e[++cnt].v=v,e[cnt].nxt=h[u],h[u]=cnt;
}
int mx(int x,int y){return x>y?x:y;}
void dpp(int x,int fx)//dp求数的直径，还有一种方法是dfs求树的直径
{
    /*
    以i为根的树的直径只可能存在于两种情况之下：
    1.经过i
    2.不经过i
    经过i的最长链显然就是两个离i最远的点之间的链
    不经过i那么肯定在以i的儿子节点为根的子树中，所以遍历子树就可以了
    */
    int mxx=0;dp[x]=0;
    for(int i=h[x],v;i;i=e[i].nxt)
    {
        if((v=e[i].v)==fx) continue;
        dpp(v,x);
        sum=mx(sum,dp[x]+dp[v]+1);//经过x的最长链
        dp[x]=mx(dp[x],dp[v]+1);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;++i) 
    {
        scanf("%d%d",&t[i].u,&t[i].v);
        add(t[i].u,t[i].v),add(t[i].v,t[i].u);
    }
    for(int i=1;i<n;++i)
    {
        int num=0;
        memset(dp,0,sizeof(dp));//记得清0
        dpp(t[i].u,t[i].v);//细节：不用做什么标记，我们把u的父亲设为v，那么u这棵子树就不会遍历到v去了
        num=sum;sum=0;
        dpp(t[i].v,t[i].u);//同上
        ans=mx(ans,num*sum);
        sum=0;
    }
    printf("%d\n",ans);
}
```
    - **核心实现思想**：使用邻接表存储树，`dpp`函数利用DP思想，考虑以当前节点为根的树直径的两种情况（经过当前节点和不经过当前节点），通过遍历子树更新直径相关值，主函数中枚举边断开树并求两棵子树直径乘积更新答案。

- **作者：Mistybranch (4星)**
    - **关键亮点**：用样例详细解释思路，先说明两条不重叠路径与子树及子树直径的关系，再给出枚举删边求子树直径相乘的具体代码实现。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, maxL, ans;
vector<int> g[409];
int Search (int u, int fa) {
    int v, l1 = 0, l2 = 0, answ = 0;
    for (int i = 0; i < g[u].size(); i++) {
        v = g[u][i];
        if (v == fa) {
            continue;
        }
        answ = max(answ, Search(v, u));
        if (maxL > l1) {
            l2 = l1;
            l1 = maxL;
        } 
        else {
            l2 = max(l2, maxL);
        }
    }
    answ = max(answ, l1 + l2);
    maxL = l1 + 1;
    return answ;
}
int main () {
    int u, v, d1, d2;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < g[i].size(); j++) {
            d1 = Search(g[i][j], i);
            d2 = Search(i, g[i][j]);
            ans = max(ans, d1 * d2);
        }
    }
    printf("%d\n", ans);
    return 0;
}
```
    - **核心实现思想**：使用`vector`存储树结构，`Search`函数通过递归搜索计算树的直径，在搜索过程中记录每个节点出发的最长和次长路径以计算直径，主函数枚举每条边断开树后分别求两棵子树直径并计算乘积更新答案。

### 最优关键思路或技巧
利用树的结构特性，将求两条不相交路径长度乘积最大值问题转化为枚举边将树分成两棵子树，再分别求子树直径的问题。在实现上，使用邻接表或`vector`存储树结构，通过DFS或DP方法高效求树的直径。

### 同类型题或类似算法套路拓展
此类题目通常围绕树结构展开，核心是理解树的各种性质以及路径与树结构的关系。类似套路包括对树进行各种操作（如删边、加点等）后求特定路径或子树相关的值，一般可以通过搜索、DP等方法解决。

### 洛谷推荐题目
- **P1352 没有上司的舞会**：同样是树结构上的DP问题，通过分析节点与子节点的关系来进行状态转移，与本题分析树结构与路径关系有相似之处。
- **P2015 二叉苹果树**：在二叉树上进行操作，通过删除边来满足一定条件下求最优值，和本题通过删边处理树结构类似。
- **P3398 仓鼠找sugar**：涉及树的路径、LCA（最近公共祖先）等知识，与本题对树路径的分析以及路径间关系判断有一定关联。

### 个人心得摘录与总结
- **作者：Kendrick_Z**：一开始想了假的贪心算法（跑树的直径后标记直径上的点，再跑次长路径），发现错误。强调要注意数据范围，由于 $n$ 较小，平方级算法可行。同时提到每次求直径要清空相关数据，否则容易出错。总结了调试过程中的教训，提醒注意算法正确性和数据初始化。 

---
处理用时：110.14秒