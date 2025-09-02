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
本题需在指数级复杂度下求解最优分组，核心挑战在于高效剪枝和状态表示。题解主要分为四类：迭代加深搜索（IDDFS）、状态压缩DP、模拟退火和剪枝暴搜。最优解法集中在状态压缩DP与剪枝暴搜，其核心思路为通过预处理排序、状态压缩优化空间，以及高效剪枝策略。

---

### 高星题解推荐（评分≥4星）

#### 1. 作者：哥你挺6啊（★★★★☆）
**关键亮点**：
- **贪心排序优化**：将奶牛按重量降序排列，优先处理大体积元素，显著减少无效分支。
- **最优性剪枝**：`if(cnt>=ans)return;` 及时终止劣于当前最优解的路径。
- **代码简洁高效**：仅30行实现，118ms通过，优于多数复杂算法。

**代码核心**：
```cpp
void dfs(int x,int cnt){
    if(x==n+1) ans=min(ans,cnt);
    if(cnt>=ans)return; //剪枝
    for(int i=1;i<=x-tot;i++){ //枚举可放置的组
        if(b[i]>=c[x]){
            b[i]-=c[x];
            dfs(x+1,cnt);
            b[i]+=c[x];
        }
    }
}
```

#### 2. 作者：shadowice1984（★★★★☆）
**关键亮点**：
- **状态压缩DP**：用二维状态`d[i][j]`表示i组电梯+j的已选集合，记录剩余容量。
- **滚动更新策略**：通过位运算枚举子集，动态更新最优解。
- **严格数学证明**：确保状态转移的正确性，避免后效性。

**核心状态转移**：
```cpp
for(int k=0;k<n;k++){ //枚举新牛
    if(j&(1<<k)) continue;
    if(d[i][j]+w[k]<=m) //放入当前组
        d[i][j|(1<<k)] = min(d[i][j|(1<<k)], d[i][j]+w[k]);
    else //新开一组
        d[i+1][j|(1<<k)] = min(d[i+1][j|(1<<k)], w[k]);
}
```

#### 3. 作者：mzq667（★★★★☆）
**关键亮点**：
- **迭代加深框架**：从小到大枚举电梯数量，避免盲目深度搜索。
- **剪枝策略**：奶牛i只能放入前i个电梯，避免重复计算对称状态。
- **即时终止**：找到首个可行解立即退出，节省计算时间。

**核心逻辑**：
```cpp
bool dfs(int x, int num){ //x:当前奶牛，num:电梯数上限
    for(int i=1; i<=num; i++){ //枚举电梯
        if(v[i]+c[x]<=W){
            v[i] += c[x];
            if(x==n) return true; //所有牛已分配
            if(dfs(x+1, num)) return true;
            v[i] -= c[x];
        }
    }
    return false;
}
```

---

### 关键思路总结
1. **贪心预处理**：降序排列大幅提升搜索效率，优先处理大元素减少分支。
2. **状态压缩**：用二进制位表示已选集合，适用于n≤18的场景。
3. **剪枝策略**：最优性剪枝（当前解劣于已知最优）、对称性剪枝（避免重复状态）。
4. **分层枚举**：IDDFS逐步增加电梯数，结合可行性剪枝快速收敛。

---

### 相似题目推荐
1. **P1120 小木棍** - 剪枝暴搜经典题，需处理分组与剪枝。
2. **P2324 [SCOI2005] 骑士精神** - IDDFS与状态压缩结合。
3. **P1171 售货员的难题** - 状态压缩DP处理旅行商问题。

---
处理用时：74.88秒