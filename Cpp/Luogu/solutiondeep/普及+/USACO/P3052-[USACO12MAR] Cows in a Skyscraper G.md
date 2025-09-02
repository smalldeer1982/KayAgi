# 题目信息

# [USACO12MAR] Cows in a Skyscraper G

## 题目描述

A little known fact about Bessie and friends is that they love stair climbing races.  A better known fact is that cows really don't like going down stairs.  So after the cows finish racing to the top of their favorite skyscraper, they had a problem.  Refusing to climb back down using the stairs, the cows are forced to use the elevator in order to get back to the ground floor.

The elevator has a maximum weight capacity of W (1 <= W <= 100,000,000) pounds and cow i weighs C\_i (1 <= C\_i <= W) pounds.  Please help Bessie figure out how to get all the N (1 <= N <= 18) of the cows to the ground floor using the least number of elevator rides.  The sum of the weights of the cows on each elevator ride must be no larger than W.


## 说明/提示

There are four cows weighing 5, 6, 3, and 7 pounds.  The elevator has a maximum weight capacity of 10 pounds.


We can put the cow weighing 3 on the same elevator as any other cow but the other three cows are too heavy to be combined.  For the solution above, elevator ride 1 involves cow #1 and #3, elevator ride 2 involves cow #2, and elevator ride 3 involves cow #4.  Several other solutions are possible for this input.


## 样例 #1

### 输入

```
4 10 
5 
6 
3 
7 
```

### 输出

```
3 ```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何将一定数量的奶牛用最少的电梯运送下去展开，使用了多种算法，包括迭代加深搜索、状态压缩动态规划、模拟退火、深搜、贪心等。迭代加深搜索通过枚举车厢数，递归尝试将奶牛放入合适车厢；状态压缩动态规划用二进制数表示奶牛选择状态，通过状态转移求解；模拟退火则是随机打乱序列，结合贪心或 DP 计算答案。

### 所选题解
- **作者：mzq667（5星）**
    - **关键亮点**：思路清晰，通过迭代加深搜索，结合剪枝优化，代码简洁易读。
    - **核心代码**：
```cpp
bool dfs(int x, int num){//x为奶牛号， num为车厢数
    for (int i = 1; i <= x && i <= num; ++i)//for车厢号，看奶牛能被放进哪个车厢
        if(v[i] + c[x] <= m){
            v[i] += c[x];
            if(x == n) return 1;
            if(dfs(x+1, num)) return 1;
            v[i] -= c[x];
        }
    return 0;
}
```
    - **核心思想**：递归遍历车厢号，尝试将当前奶牛放入合适车厢，若能放完所有奶牛则返回成功。
- **作者：shadowice1984（5星）**
    - **关键亮点**：使用状态压缩动态规划，详细解释了状态定义和转移过程，对后效性问题处理得当。
    - **核心代码**：
```cpp
for(int i=0;i<=n;i++)
{
    for(int j=0;j<=up-1;j++)//存在性dp
    {
        if(d[i][j]!=0x3f3f3f3f)//如果存在
        {
            for(int k=0;k<n;k++)//枚举k
            {
                if((j&(1<<k))!=0)continue;//如果属于jcontinue掉
                if(d[i][j]+w[k]<=m)
                {
                    d[i][j|(1<<k)]=min(d[i][j|(1<<k)],d[i][j]+w[k]);
                }
                else
                {
                    d[i+1][j|(1<<k)]=min(d[i][j|(1<<k)],w[k]);
                }
            }
        }
    }
}
```
    - **核心思想**：枚举电梯数量和奶牛选择状态，若状态存在则枚举未选奶牛，根据重量判断转移到当前电梯或新开电梯。
- **作者：qingfengwuhui（4星）**
    - **关键亮点**：从深搜开始，逐步优化，详细展示了剪枝过程，思路清晰，适合初学者。
    - **核心代码**：
```cpp
void dfs(int x, int y){//表示当前要放的奶牛序号为 x且当前有y组 
    if(x == n + 1)
    {
        ans = min(ans, y);
        return;
    }
    if(y >= ans)return;
    a[y + 1] = w[x];
    dfs(x + 1, y + 1);
    a[y + 1] = 0;
    for(int i = 1;i <= y;i ++)
    if(a[i] + w[x] <= W){
        a[i] += w[x];
        dfs(x + 1, y);
        a[i] -= w[x];
    }
    return ;
}
```
    - **核心思想**：对于每头奶牛，尝试放入已有组或新开一组，通过剪枝避免无效搜索。

### 最优关键思路或技巧
- **状态压缩**：利用二进制数表示奶牛选择状态，有效处理组合问题，降低时间复杂度。
- **剪枝优化**：如迭代加深搜索中，剪去不必要的车厢枚举；深搜中，当当前方案数大于已求出的最小方案数时直接返回。
- **贪心策略**：将奶牛按重量从大到小排序，优先处理重量大的奶牛，减少搜索空间。

### 拓展思路
同类型题可关注物品分组、资源分配问题，类似算法套路有迭代加深搜索、状态压缩动态规划、模拟退火等。可用于解决如背包问题变种、任务调度问题等。

### 推荐题目
- P1896 [SCOI2005]互不侵犯：状态压缩动态规划经典题，通过二进制表示每行状态进行状态转移。
- P2704 [NOI2001] 炮兵阵地：同样是状态压缩动态规划，需要考虑更多状态约束。
- P1064 [NOIP2006 提高组] 金明的预算方案：分组背包问题，可使用迭代加深搜索或动态规划求解。

### 个人心得摘录与总结
- **作者：哥你挺6啊**：提到状压方法较难想，裸搜结合剪枝也能高效解决问题，说明在面对难题时，基础算法结合优化也能有好的效果。
- **作者：Floatiy**：指出贪心在本题中部分情况错误，但结合排序和退火能提高正确率，强调了算法结合的重要性。
- **作者：U121570**：分享了深搜过程中遇到 TLE 和 WA 的调试经历，通过不断调整贪心思路最终 AC，体现了调试和优化的重要性。 

---
处理用时：38.69秒