# 题目信息

# [USACO11OPEN] Mowing the Lawn G

## 题目描述

在一年前赢得了小镇的最佳草坪比赛后，Farmer John 变得很懒，再也没有修剪过草坪。现在，新一轮的最佳草坪比赛又开始了，Farmer John 希望能够再次夺冠。

然而，Farmer John 的草坪非常脏乱，因此，Farmer John 只能够让他的奶牛来完成这项工作。Farmer John 有 $N$（$1\le N\le 10^5$）只排成一排的奶牛，编号为 $1\ldots N$。每只奶牛的效率是不同的，奶牛 $i$ 的效率为 $E_i$（$0\le E_i\le 10^9$）。

靠近的奶牛们很熟悉，因此，如果 Farmer John安排超过 $K$ 只连续的奶牛，那么，这些奶牛就会罢工去开派对 :)。因此，现在 Farmer John 需要你的帮助，计算 FJ 可以得到的最大效率，并且该方案中没有连续的超过 $K$ 只奶牛。

## 样例 #1

### 输入

```
5 2
1
2
3
4
5
```

### 输出

```
12
```

# AI分析结果



### 综合分析与结论
本题核心是动态规划结合单调队列优化，解决连续区间限制下的最值问题。所有题解均围绕以下核心思路展开：
1. **状态定义**：多数采用 `dp[i]` 表示前i头奶牛的最大效率，或逆推定义 `dp[i]` 为不选第i头的最小损失。
2. **方程变形**：通过前缀和分离变量，转化为滑动窗口最大值问题。
3. **单调队列优化**：维护 `dp[j] - sum[j]` 的最值，将复杂度从O(nk)优化至O(n)。

关键技巧：状态方程的变形技巧、边界条件处理、long long类型防溢出。

---

### 精选题解与亮点分析
#### 1. Koakuma（Solution Three） ⭐⭐⭐⭐⭐
**亮点**：逆推思维巧妙，将问题转化为最小损失，避免复杂状态转移。通过虚点处理边界，代码简洁高效。
```cpp
// 核心代码片段
deque<node> q;
q.push_back({0,0});
for(int i=1; i<=n; ++i) {
    while(!q.empty() && i - q.front().t > k + 1) q.pop_front();
    dp[i] = q.front().v + a[i];
    while(!q.empty() && dp[i] < q.back().v) q.pop_back();
    q.push_back({i,dp[i]});
}
```

#### 2. thmyl ⭐⭐⭐⭐
**亮点**：最简洁的顺推实现，直接维护`dp[j-1]-sum[j]`的最大值。代码高度精简，适合快速理解单调队列应用。
```cpp
// 关键转移方程
long long que(int i){
    d[i]=f[i-1]-sum[i];
    while(head<=tail&&d[q[tail]]<d[i]) tail--;
    q[++tail]=i;
    while(head<=tail&&q[head]<i-m) head++;
    return d[q[head]];
}
```

#### 3. EarthGiao ⭐⭐⭐⭐
**亮点**：逆向思维清晰，通过不选点间距离约束简化问题。队列维护时机明确，适合教学。
```cpp
// 核心维护逻辑
while(!q.empty() && i - q.front().t > k + 1) q.pop_front();
dp[i] = q.front().v + a[i];
while(!q.empty() && dp[i] < q.back().v) q.pop_back();
```

---

### 关键思路总结
1. **逆向转化**：求最小损失代替最大效率，简化状态转移。
2. **前缀和分离**：将方程变形为 `max(f[j]-sum[j]) + sum[i]`，分离出可维护项。
3. **队列维护原则**：新元素比队尾优时弹出队尾，保证队列单调性。

---

### 拓展练习
1. **滑动窗口最值**：[P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. **环形区间DP**：[P2627 环状最大子段和](https://www.luogu.com.cn/problem/P1121)
3. **多维单调队列**：[P2216 理想的正方形](https://www.luogu.com.cn/problem/P2216)

---

### 调试经验摘录
- **初始状态处理**：BeyondStars强调初始化队列需包含虚点0，否则前k项无法正确处理。
- **long long陷阱**：多篇题解提醒sum可能超过int范围，必须全程使用long long。
- **队列维护顺序**：quest_2指出需先弹出越界元素再计算当前值，否则会引入非法状态。

---
处理用时：51.97秒