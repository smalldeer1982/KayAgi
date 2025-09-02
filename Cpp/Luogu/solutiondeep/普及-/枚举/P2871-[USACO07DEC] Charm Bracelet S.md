# 题目信息

# [USACO07DEC] Charm Bracelet S

## 题目描述

Bessie has gone to the mall's jewelry store and spies a charm bracelet. Of course, she'd like to fill it with the best charms possible from the N (1 ≤ N ≤ 3,402) available charms. Each charm i in the supplied list has a weight Wi (1 ≤ Wi ≤ 400), a 'desirability' factor Di (1 ≤ Di ≤ 100), and can be used at most once. Bessie can only support a charm bracelet whose weight is no more than M (1 ≤ M ≤ 12,880).

Given that weight limit as a constraint and a list of the charms with their weights and desirability rating, deduce the maximum possible sum of ratings.

有 $N$ 件物品和一个容量为 $M$ 的背包。第 $i$ 件物品的重量是 $W_i$，价值是 $D_i$。求解将哪些物品装入背包可使这些物品的重量总和不超过背包容量，且价值总和最大。

## 样例 #1

### 输入

```
4 6
1 4
2 6
3 12
2 7```

### 输出

```
23```

# AI分析结果

### 综合分析与结论
这些题解均围绕经典的0 - 1背包问题展开。大部分题解采用一维数组优化空间，避免二维数组可能出现的MLE问题。核心思路是通过状态转移方程 `f[j] = max(f[j], f[j - w[i]] + v[i])` 来更新背包在不同容量下的最大价值。部分题解还使用了滚动数组、在线读入等优化技巧。

### 评分较高的题解
1. **作者：wxwyx（5星）**
    - **关键亮点**：思路清晰，代码简洁，对一维数组的使用和状态转移方程的解释明确，适合初学者理解。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int w[3410],v[3410];  //w数组存重量，v数组存价值（魅力值）
int f[13000];
int main()
{
    int n,m;   //m是最大重量
    cin>>n>>m;     //与采药输入顺序相反
    for(int i=1;i<=n;i++)
        cin>>w[i]>>v[i];  //输入好像没什么好说的。
    for(int i=1;i<=n;i++)
    {
        for(int j=m;j>=w[i];j--)   //从后向前找不会有其它影响
        {
            f[j]=max(f[j-w[i]]+v[i],f[j]);   //最基本的状态转移方程
        }
    }
    cout<<f[m]<<endl;
    return 0;
}
```
    - **核心思想**：通过两层循环，外层遍历物品，内层从背包最大容量开始递减到当前物品重量，不断更新 `f[j]` 为放入或不放入当前物品的最大价值。

2. **作者：theHermit（4星）**
    - **关键亮点**：不仅给出一维数组解法，还详细介绍了二维数组结合滚动数组的解法，对状态转移方程的推导和内存优化解释清晰。
    - **核心代码**：
```cpp
for(int i=1;i<=N;i++){
    for(int j=M;j>=1;j--){
        if(j>=C[i])
            V[i%2][j]=max(V[(i-1)%2][j],V[(i-1)%2][j-C[i]]+W[i]);
        //j-C[i]为：拿2之后剩余的重量，然后除此之外的最大值
        else
            V[i%2][j]=V[(i-1)%2][j];
    }
}
cout<<V[N%2][M];
```
    - **核心思想**：利用滚动数组，通过 `i % 2` 循环使用两行数组，根据背包容量和物品重量更新最大价值。

3. **作者：Right（4星）**
    - **关键亮点**：在一维数组优化的基础上，进一步将存储物品重量和价值的数组变为变量，节省内存和时间。
    - **核心代码**：
```cpp
#include <stdio.h>
#define max(a,b) (a>b?a:b)
int n,m,i,j,c,w,f[12880];
int main()
{
    for (scanf("%d%d",&n,&m),i=1; i<=n; ++i)
        for (scanf("%d%d",&c,&w),j=m; j>=c; --j) f[j]=max(f[j],f[j-c]+w);
    printf("%d",f[m]);
}
```
    - **核心思想**：在输入物品重量和价值时直接进行状态转移，避免使用数组存储所有物品信息。

### 最优关键思路或技巧
- **空间优化**：使用一维数组或滚动数组代替二维数组，减少内存开销。
- **在线读入**：在输入物品信息时直接进行状态转移，节省数组空间。

### 可拓展之处
同类型题如完全背包问题（每个物品可无限次选取）、多重背包问题（每个物品有固定数量），解题思路类似，但状态转移方程和循环条件有所不同。

### 推荐题目
1. [P1048 采药](https://www.luogu.org/problem/P1048)：经典的0 - 1背包问题，与本题类似。
2. [P1616 疯狂的采药](https://www.luogu.org/problem/P1616)：完全背包问题，可加深对背包问题的理解。
3. [P1776 宝物筛选](https://www.luogu.org/problem/P1776)：多重背包问题，需要对状态转移方程进行适当调整。

### 个人心得摘录与总结
- **wxwyx**：理解零一背包很有成就感，认为一维数组更好理解。
- **不存在之人**：基本原理理解后自己写代码，写完不自信但最终正确，强调参考《背包九讲》学习。
- **lijiahao2017**：做了三次才AC，提醒注意数据范围，避免被坑。

这些心得提醒学习者要深入理解原理，多实践，注意细节，同时可以借助优秀的学习资料辅助学习。 

---
处理用时：30.76秒