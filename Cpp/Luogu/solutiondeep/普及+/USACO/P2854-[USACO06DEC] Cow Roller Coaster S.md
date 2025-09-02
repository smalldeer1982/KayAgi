# 题目信息

# [USACO06DEC] Cow Roller Coaster S

## 题目描述

有 $n$ 条线段，每条线段只能放在数轴上的一个特定位置，并且第 $i$ 根线段有如下几个属性：$X_i$（该线段放在数轴上的起点），$W_i$（该线段长度），$F_i$（你若使用该线段你能获得的价值），$C_i$（你若使用该线段你所需要的费用）。现在让你从中选出一些线段，使得这些线段能够铺满数轴上的区间 $[0,L]$ 且线段必须首尾相接（也就是不能重叠，也不能空缺），并且所花费用和不超过 $B$，同时要使你收获的价值尽量大，请你找到这个方案。

## 样例 #1

### 输入

```
5 6 10
0 2 20 6
2 3 5 6
0 1 2 1
1 1 1 3
1 2 5 4
3 2 10 2```

### 输出

```
17```

# AI分析结果

### 综合分析与结论
这些题解主要围绕动态规划（DP）和搜索算法来解决该问题。多数题解采用DP方法，将其视为背包问题的变种，通过定义二维状态数组 `f[i][j]` 表示在坐标 `i` 处花费成本 `j` 时的最大乐趣值，利用状态转移方程进行求解。部分题解使用搜索算法，如深度优先搜索（DFS），并通过剪枝和记忆化来优化。

### 所选题解
- 作者：糪眾脦颰罷（4星）
  - 关键亮点：思路清晰，对状态数组 `f[i][j]` 的定义和状态转移方程的解释明确，代码实现简洁易懂，使用结构体存储轨道信息并排序，方便DP过程。
  - 个人心得：提到题目中无解输出 -1 这点未翻译出来，提醒读者注意细节。
- 作者：linyinuo2008（4星）
  - 关键亮点：对题意和算法理解阐述详细，强调了DP中状态转移的条件和01背包的重点，代码注释丰富，还添加了小优化，如判断是否有起点为0的钢轨。
  - 个人心得：表明自己是看着题解打的，做完后写题解加深理解，体现了学习的过程。
- 作者：Genevieve_xiao（4星）
  - 关键亮点：做法区别于其他题解，按右端点排序，使用两个数组 `f[i]` 和 `g[i]` 分别存储最大价值和最小花费，状态转移逻辑清晰。
  - 个人心得：思路来源于大佬，体现了学习借鉴的过程。

### 重点代码及核心实现思想
#### 糪眾脦颰罷的题解
```cpp
int l,n,b,f[1001][1001],ans=-1;
struct FT{
    int st;
    int ed;
    int f;
    int v;
};
FT p[100001];
bool cmp(FT a1,FT a2){
    return a1.st<a2.st;
}
// ...
sort(p+1,p+1+n,cmp);
f[0][0]=0;
for(int i=1;i<=n;i++){
    for(int j=0;j<=b-p[i].v;j++){
        if(f[p[i].st][j]!=-1)
            f[p[i].ed][j+p[i].v]=max(f[p[i].ed][j+p[i].v],f[p[i].st][j]+p[i].f);
    }
}
for(int i=0;i<=b;i++)
    ans=max(ans,f[l][i]);
```
核心思想：先对轨道按起点排序，初始化 `f[0][0] = 0`，当 `f[p[i].st][j]` 不为 -1 时进行状态转移，最后找出 `f[l][i]` 中的最大值。

#### linyinuo2008的题解
```cpp
const int NR=10005;
const int MR=1005;
const int INF=0x7f7f7f;
struct comp
{
    int start,end,fun,cost;
}a[NR];
int l,n,b,ans;
int f[MR][MR];
bool cmp(struct comp u,struct comp v){
    return u.start<v.start;
}
// ...
sort(a+1,a+n+1,cmp);
if(a[1].start!=0){
    cout<<-1;
    return 0;
}
f[0][0]=0;
for(int i=1;i<=n;i++){
    for(int j=b;j>=a[i].cost;j--){
        if(f[a[i].start][j-a[i].cost]!=(-INF)){
            f[a[i].end][j]=max(f[a[i].end][j],f[a[i].start][j-a[i].cost]+a[i].fun);
        }
    }
}
ans=-INF;
for(int i=0;i<=b;i++){
    ans=max(ans,f[l][i]);
}
if(ans==-INF) cout<<-1;
else cout<<ans;
```
核心思想：按起点排序，判断是否有起点为0的钢轨，初始化 `f[0][0] = 0`，当 `f[a[i].start][j-a[i].cost]` 不为负无穷时进行状态转移，最后找出 `f[l][i]` 中的最大值，若为负无穷则输出 -1。

#### Genevieve_xiao的题解
```cpp
int l,n,m,f[N],g[N];
struct node{
    int st,len,w,c,ed;
}e[N];
bool cmp(node x,node y){
    return x.ed<y.ed;
}
// ...
sort(e+1,e+1+n,cmp);
memset(f,-0x3f,sizeof f);
memset(g, 0x3f,sizeof g);
f[0]=0;g[0]=0;
for(int i=1;i<=n;i++){
    if(g[e[i].st]+e[i].c>m) continue;
    if(f[e[i].ed]<f[e[i].st]+e[i].w){
        f[e[i].ed]=f[e[i].st]+e[i].w;
        g[e[i].ed]=g[e[i].st]+e[i].c;
    }
    else if(f[e[i].ed]==f[e[i].st]+e[i].w){
        g[e[i].ed]=min(g[e[i].ed],g[e[i].st]+e[i].c);
    }
}
if(f[l]>0) printf("%d",f[l]);
else printf("-1");
```
核心思想：按右端点排序，初始化 `f[0] = 0` 和 `g[0] = 0`，排除不合法状态，若使用木板能获得更优价值则更新 `f` 和 `g`，价值相同时取最小花费，最后判断 `f[l]` 是否有合法解。

### 最优关键思路或技巧
- **状态定义**：使用二维数组 `f[i][j]` 表示在位置 `i` 花费成本 `j` 时的最大乐趣值，清晰地描述了问题的状态。
- **排序优化**：对轨道按起点或终点排序，方便DP过程，保证状态转移的正确性。
- **可行性判断**：将状态数组初始化为 -1 或负无穷，通过判断状态是否为 -1 或负无穷来确定该状态是否可达，避免不合法的状态转移。

### 可拓展之处
同类型题或类似算法套路：
- 多维背包问题：在本题基础上增加更多的限制条件，如增加时间、空间等维度的限制。
- 区间覆盖问题：要求用若干区间覆盖一个大区间，同时满足其他条件，如最小化成本、最大化价值等。

### 推荐题目
- P1507 NASA的食物计划（二维背包问题）
- P2871 手链Charm Bracelet（01背包裸题）
- P1853 投资的最大效益（背包问题变种）

---
处理用时：53.44秒