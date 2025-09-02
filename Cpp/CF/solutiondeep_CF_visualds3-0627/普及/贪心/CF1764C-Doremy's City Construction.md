# 题目信息

# Doremy's City Construction

## 题目描述

Doremy's new city is under construction! The city can be regarded as a simple undirected graph with $ n $ vertices. The $ i $ -th vertex has altitude $ a_i $ . Now Doremy is deciding which pairs of vertices should be connected with edges.

Due to economic reasons, there should be no self-loops or multiple edges in the graph.

Due to safety reasons, there should not be pairwise distinct vertices $ u $ , $ v $ , and $ w $ such that $ a_u \leq a_v \leq a_w $ and the edges $ (u,v) $ and $ (v,w) $ exist.

Under these constraints, Doremy would like to know the maximum possible number of edges in the graph. Can you help her?

Note that the constructed graph is allowed to be disconnected.

## 说明/提示

In the first test case, there can only be at most $ 3 $ edges in the graph. A possible construction is to connect $ (1,3) $ , $ (2,3) $ , $ (3,4) $ . In the picture below the red number above node $ i $ is $ a_i $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764C/664da7a7b39c78efe9a85191f05318cb0a9df4d9.png)

The following list shows all such $ u $ , $ v $ , $ w $ that the edges $ (u,v) $ and $ (v,w) $ exist.

- $ u=1 $ , $ v=3 $ , $ w=2 $ ;
- $ u=1 $ , $ v=3 $ , $ w=4 $ ;
- $ u=2 $ , $ v=3 $ , $ w=1 $ ;
- $ u=2 $ , $ v=3 $ , $ w=4 $ ;
- $ u=4 $ , $ v=3 $ , $ w=1 $ ;
- $ u=4 $ , $ v=3 $ , $ w=2 $ .

Another possible construction is to connect $ (1,4) $ , $ (2,4) $ , $ (3,4) $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764C/7d1fc03a74b1366633e41dc227acef23827c0f69.png)

An unacceptable construction is to connect $ (1,3) $ , $ (2,3) $ , $ (2,4) $ , $ (3,4) $ . Because when $ u=4 $ , $ v=2 $ , $ w=3 $ , $ a_u\le a_v \le a_w $ holds, and the respective edges exist.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764C/02cccee9e8ea3921ef7338c4d1dd72e83e933cbc.png)

## 样例 #1

### 输入

```
4
4
2 2 3 1
6
5 2 3 1 5 2
12
7 2 4 9 1 4 6 3 7 4 2 3
4
1000000 1000000 1000000 1000000```

### 输出

```
3
9
35
2```

# AI分析结果



---

## 题解思路、算法要点与解决难点

### 核心贪心思路
1. **二分图分割策略**  
   - 将排序后的数组分为两部分：左部所有元素 ≤ 右部所有元素，两集合间全连边。
   - 边数最大化为两集合大小的乘积，即 $\max \{\text{左部大小} \times \text{右部大小}\}$。

2. **贪心选择依据**  
   - 排序后，遍历每个可能的分界点（不同元素值的位置），计算该点左侧与右侧的乘积。
   - 数学证明：和一定时，两数差越小乘积越大，故最优分界点通常在排序后的中间位置附近。

3. **特殊处理全相同元素**  
   - 所有元素相等时，每个顶点只能连一条边，答案为 $\lfloor n/2 \rfloor$。

### 解决难点
- **重复元素的处理**：需用 `upper_bound` 或遍历统计每个元素出现的边界，确保分割点两侧无重叠。
- **分界点的快速枚举**：排序后通过二分查找或指针跳跃快速定位不同元素的分界点。

---

## 题解评分 (≥4星)

1. **郑朝曦zzx（⭐️⭐️⭐️⭐️⭐️）**  
   - **亮点**：严格数学推导二分图分割的正确性，代码简洁高效，处理全相同元素的边界情况清晰。
   - **代码可读性**：使用 `upper_bound` 快速定位分割点，逻辑紧凑。

2. **Yuki__S2OO8（⭐️⭐️⭐️⭐️）**  
   - **亮点**：从顶点连边限制出发，直观解释分割策略的必要性，补充了贪心策略的感性理解。
   - **实践性**：通过举例说明为何不能将相同元素分到不同集合。

3. **aimoyudexianyu（⭐️⭐️⭐️⭐️）**  
   - **亮点**：以二分图模型解释问题，图示辅助理解，代码中通过排序和分组统计优化计算。
   - **可视化设计**：附示意图直观展示分割策略。

---

## 最优思路/技巧提炼

1. **排序预处理**：将数组排序后，分割点的枚举转化为对元素值的遍历。
2. **分界点乘积计算**：对每个元素值，计算其最后一次出现位置作为左部大小，剩余为右部。
3. **特判全相同情况**：单独处理避免错误分割。

**关键代码片段**：
```cpp
sort(a, a + n);
for (int i = 0; i < n; ) {
    int j = upper_bound(a, a + n, a[i]) - a;
    ans = max(ans, (ll)j * (n - j));
    i = j;
}
```

---

## 同类型题与算法套路

1. **区间分割最大化乘积**：如将数组分为两部分，使得两部分的差值最小且乘积最大。
2. **二分图最大边数**：如任务分配问题中，两组元素间全连边的最优解。
3. **贪心分治策略**：如加油站问题中选择最佳停靠点。

---

## 推荐题目
1. **P1094 [NOIP2007 普及组] 纪念品分组** - 贪心分组策略。
2. **P1106 删数问题** - 通过贪心选择删除策略。
3. **CF1343C Alternating Subsequence** - 极值点分割策略。

---

## 可视化与算法演示

### 动画设计
1. **排序过程**：展示数组排序后的像素块排列，颜色随值变化。
2. **分界点扫描**：高亮当前分界点，左右部分用不同颜色区分（左蓝右红）。
3. **乘积计算**：实时显示当前分界点对应的边数（左大小 × 右大小），更新最大值。

### 复古游戏化交互
- **像素风格**：元素用8位像素块表示，分界点移动时有“滴答”音效。
- **AI自动模式**：分界点自动从左到右扫描，播放背景音乐，最大值更新时触发上扬音效。
- **关卡积分**：每找到一个更优分界点获得积分，连击奖励加速扫描。

**伪代码示例**：
```javascript
// Canvas绘制排序数组
function drawArray() {
    for (let i = 0; i < n; i++) {
        ctx.fillStyle = (i < splitPos) ? '#3498db' : '#e74c3c';
        ctx.fillRect(i * 10, 0, 8, a[i] * 2);
    }
}
// 自动扫描分界点
function autoScan() {
    let maxEdges = 0;
    for (let pos of splitPositions) {
        playSound('move');
        let edges = pos * (n - pos);
        if (edges > maxEdges) {
            maxEdges = edges;
            playSound('success');
        }
        updateScore(edges);
    }
}
```

---

## 代码实现（核心贪心逻辑）

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> a(n);
        for (auto &x : a) cin >> x;
        sort(a.begin(), a.end());
        ll ans = (a[0] == a.back()) ? n / 2 : 0;
        for (int i = 0; i < n; ) {
            int j = upper_bound(a.begin(), a.end(), a[i]) - a.begin();
            ans = max(ans, (ll)j * (n - j));
            i = j;
        }
        cout << ans << '\n';
    }
    return 0;
}
```

---

**总结**：本题通过排序与分界点枚举实现贪心策略，核心在于将问题转化为二分图边数最大化。可视化设计可通过动态扫描分界点强化理解，复古风格交互增加学习趣味性。

---
处理用时：79.37秒