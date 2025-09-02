# 题目信息

# Knapsack

## 题目描述

You have a knapsack with the capacity of $ W $ . There are also $ n $ items, the $ i $ -th one has weight $ w_i $ .

You want to put some of these items into the knapsack in such a way that their total weight $ C $ is at least half of its size, but (obviously) does not exceed it. Formally, $ C $ should satisfy: $ \lceil \frac{W}{2}\rceil \le C \le W $ .

Output the list of items you will put into the knapsack or determine that fulfilling the conditions is impossible.

If there are several possible lists of items satisfying the conditions, you can output any. Note that you don't have to maximize the sum of weights of items in the knapsack.

## 说明/提示

In the first test case, you can take the item of weight $ 3 $ and fill the knapsack just right.

In the second test case, all the items are larger than the knapsack's capacity. Therefore, the answer is $ -1 $ .

In the third test case, you fill the knapsack exactly in half.

## 样例 #1

### 输入

```
3
1 3
3
6 2
19 8 19 69 9 4
7 12
1 1 1 17 1 1 1```

### 输出

```
1
1
-1
6
1 2 3 5 6 7```

# AI分析结果

### 题目内容重写

#### 题目描述

你有一个容量为 $W$ 的背包。还有 $n$ 个物品，第 $i$ 个物品的重量为 $w_i$。

你需要选择一些物品放入背包，使得它们的总重量 $C$ 至少为背包容量的一半，但不超过背包的容量。形式上，$C$ 应满足：$\lceil \frac{W}{2}\rceil \le C \le W$。

输出你将放入背包的物品列表，或者确定无法满足条件。

如果有多个满足条件的物品列表，你可以输出任意一个。注意，你不需要最大化背包中物品的总重量。

#### 说明/提示

在第一个测试用例中，你可以选择重量为 $3$ 的物品，正好填满背包。

在第二个测试用例中，所有物品的重量都超过了背包的容量。因此，答案是 $-1$。

在第三个测试用例中，你正好将背包填满一半。

#### 样例 #1

##### 输入

```
3
1 3
3
6 2
19 8 19 69 9 4
7 12
1 1 1 17 1 1 1
```

##### 输出

```
1
1
-1
6
1 2 3 5 6 7
```

### 算法分类

贪心

### 题解综合分析

该问题的核心是选择一些物品，使得它们的总重量在背包容量的一半到全部容量之间。由于不需要最大化总重量，因此可以采用贪心策略，优先选择重量较大的物品，逐步逼近目标。

### 精选题解

#### 题解1：作者：Tarsal (赞：3)

**星级：4星**

**关键亮点：**
- 采用贪心策略，从大到小选择物品，确保总重量尽可能接近背包容量的一半。
- 代码简洁，逻辑清晰，易于理解。

**核心代码：**
```cpp
sort(e + 1, e + n + 1, cmp);
Rep(i, 1, n) {
    ans += e[i].a;
    if(ans > c) {ans -= e[i].a; continue; }
    p[++ cnt] = e[i].id;
    if(ans >= ceil(1.0 * c / 2)) { pla = i; break;}
}
```

**实现思想：**
- 首先对物品按重量从大到小排序。
- 依次选择物品，如果当前总重量超过背包容量，则跳过该物品。
- 当总重量达到或超过背包容量的一半时，停止选择并输出结果。

#### 题解2：作者：_Wind_Leaves_ShaDow_ (赞：1)

**星级：4星**

**关键亮点：**
- 详细证明了贪心策略的正确性，确保在无法选择大物品时，选择小物品也能满足条件。
- 代码结构清晰，注释详细，便于理解。

**核心代码：**
```cpp
for(int i=1;i<=n;i++){
    sum+=a[i].w;
    if(sum>m){
        sum-=a[i].w;
        continue;
    }
    ans.push_back(a[i].id);
    if(sum>=((m+1)>>1))break;
}
```

**实现思想：**
- 从大到小选择物品，如果当前总重量超过背包容量，则跳过该物品。
- 当总重量达到或超过背包容量的一半时，停止选择并输出结果。

#### 题解3：作者：AFOier (赞：1)

**星级：4星**

**关键亮点：**
- 直接跳过重量超过背包容量的物品，减少不必要的计算。
- 代码简洁，逻辑清晰，易于理解。

**核心代码：**
```cpp
for(int i = 1; i <= n; i++) {
    if(a[i].s >= mid && a[i].s <= w) {
        cout << 1 << endl << a[i].id << endl;
        return;
    }
    if(a[i].s < mid) {
        sum += a[i].s;
        ans[++cnt] = a[i].id;
        if(sum >= mid) {
            cout << cnt << endl;
            for(int i = 1; i <= cnt; i++) cout << ans[i] << ' ';
            cout << endl;
            return;
        }
    }
}
```

**实现思想：**
- 首先检查是否有单个物品满足条件，如果有则直接输出。
- 否则，选择重量小于背包容量一半的物品，逐步累加，直到总重量达到或超过背包容量的一半。

### 最优关键思路

- **贪心策略**：从大到小选择物品，确保总重量尽可能接近背包容量的一半。
- **跳过无效物品**：直接跳过重量超过背包容量的物品，减少不必要的计算。
- **提前终止**：当总重量达到或超过背包容量的一半时，立即停止选择并输出结果。

### 可拓展之处

- **类似问题**：可以扩展到其他背包问题，如0-1背包、完全背包等，采用类似的贪心策略进行优化。
- **动态规划**：如果问题要求最大化总重量，可以采用动态规划的方法进行求解。

### 推荐题目

1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
2. [P1064 金明的预算方案](https://www.luogu.com.cn/problem/P1064)
3. [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)

### 个人心得

- **调试经历**：在实现贪心策略时，需要注意排序的顺序和选择物品的逻辑，确保总重量不会超过背包容量。
- **踩坑教训**：在计算背包容量的一半时，需要使用向上取整，避免遗漏某些情况。
- **顿悟感想**：贪心策略虽然简单，但在某些问题中能够快速找到可行解，特别是在不需要最优解的情况下。

---
处理用时：39.75秒