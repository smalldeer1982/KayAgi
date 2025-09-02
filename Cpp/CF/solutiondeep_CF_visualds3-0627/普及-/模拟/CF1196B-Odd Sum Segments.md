# 题目信息

# Odd Sum Segments

## 题目描述

You are given an array $ a $ consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ . You want to split it into exactly $ k $ non-empty non-intersecting subsegments such that each subsegment has odd sum (i. e. for each subsegment, the sum of all elements that belong to this subsegment is odd). It is impossible to rearrange (shuffle) the elements of a given array. Each of the $ n $ elements of the array $ a $ must belong to exactly one of the $ k $ subsegments.

Let's see some examples of dividing the array of length $ 5 $ into $ 3 $ subsegments (not necessarily with odd sums): $ [1, 2, 3, 4, 5] $ is the initial array, then all possible ways to divide it into $ 3 $ non-empty non-intersecting subsegments are described below:

- $ [1], [2], [3, 4, 5] $ ;
- $ [1], [2, 3], [4, 5] $ ;
- $ [1], [2, 3, 4], [5] $ ;
- $ [1, 2], [3], [4, 5] $ ;
- $ [1, 2], [3, 4], [5] $ ;
- $ [1, 2, 3], [4], [5] $ .

Of course, it can be impossible to divide the initial array into exactly $ k $ subsegments in such a way that each of them will have odd sum of elements. In this case print "NO". Otherwise, print "YES" and any possible division of the array. See the output format for the detailed explanation.

You have to answer $ q $ independent queries.

## 样例 #1

### 输入

```
3
5 3
7 18 3 14 1
5 4
1 2 3 4 5
6 2
1 2 8 4 10 2
```

### 输出

```
YES
1 3 5
NO
NO
```

# AI分析结果



# Odd Sum Segments 题解分析

## 算法分类
数学分析（奇偶性判断）

---

## 题解思路与难点对比

### 核心思路
所有题解均基于以下数学性质：
1. 每个子段必须有奇数个奇数（因为奇数个奇数之和为奇数）
2.总奇数数必须 ≥ k，且奇数数与k的奇偶性相同（即奇数数 - k 是偶数）

### 关键步骤对比
1. **HoshizoraZ（贪心法）**  
   - 使用前缀和找分割点
   - 每次遇到奇数段立即分割
   - 最后验证剩余段是否为奇数

2. **__shadow__（数学法）**  
   - 统计所有奇数的位置
   - 直接判断总奇数数是否满足条件
   - 输出前k-1个奇数的位置，最后段强制到末尾

3. **xh001/xukuan（优化数学法）**  
   - 使用位运算优化奇偶判断
   - 更简洁的条件表达式

### 解决难点
1. 正确推导总奇数数的条件（奇偶性匹配）
2. 确保最后段的奇数数也为奇数
3. 处理边界条件（如n的位置强制包含）

---

## 题解评分（≥4星）

1. **__shadow__（★★★★★）**  
   - 思路最直观，代码最简洁
   - 时间复杂度O(n)，空间优化好
   ```cpp
   if (sum < k || (sum - k) % 2 != 0) {
       printf("NO\n");
       continue;
   }
   ```

2. **xh001（★★★★★）**  
   - 位运算优化奇偶判断
   - 使用数组缓存奇数位置
   ```cpp
   if(x%2==1) a[++cnt]=i;
   ```

3. **HoshizoraZ（★★★★☆）**  
   - 贪心策略有教学意义
   - 需要处理前缀和验证
   ```cpp
   if((sum[i] - sum[last]) & 1){
       ans[++cnt] = i;
       last = i;
   }
   ```

---

## 最优思路提炼
**关键技巧**：
1. **奇偶性定律**：利用奇+奇=偶、奇+偶=奇的性质
2. **数学优化**：直接统计奇数数代替遍历分割
3. **位置缓存**：记录所有奇数位置快速输出分割点

**实现要点**：
1. 统计奇数总数，验证条件 `cnt ≥ k && (cnt - k) % 2 == 0`
2. 输出前k-1个奇数的位置，最后段强制到数组末尾

---

## 同类题目推荐
1. CF1513B - AND Sequences（位运算性质）
2. P1146 硬币翻转（奇偶性操作）
3. P1630 求和（奇偶性分组）

---

## 可视化设计

### 动画方案
1. **像素风格显示**  
   - 奇数用黄色方块，偶数用蓝色方块
   - 分割线用红色竖条表示

2. **关键帧演示**  
   ```javascript
   // 示例伪代码
   function drawFrame() {
       ctx.fillStyle = isOdd ? '#FFD700' : '#1E90FF';
       if (index === splitPoint) ctx.fillStyle = '#FF0000';
   }
   ```

3. **音效提示**  
   - 正确时播放8-bit胜利音效（440Hz方波）
   - 错误时播放短促低音（220Hz）

---

## 核心代码实现
```cpp
// __shadow__ 的优化版本
#include <bits/stdc++.h>
using namespace std;

int main() {
    int Q, n, k, t, sum;
    int a[200010];
    scanf("%d", &Q);
    while (Q--) {
        sum = 0;
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &t);
            if (t % 2) a[++sum] = i;
        }
        if (sum >= k && (sum - k) % 2 == 0) {
            printf("YES\n");
            for (int i = 1; i < k; ++i) printf("%d ", a[i]);
            printf("%d\n", n);
        } else {
            printf("NO\n");
        }
    }
    return 0;
}
```

---

## 总结
本题关键在于发现奇数数量的奇偶规律。最优解法通过数学分析将时间复杂度优化到O(n)，且代码实现简洁。贪心解法虽正确但实现稍复杂。掌握奇偶性定律是解决此类问题的关键。

---
处理用时：180.23秒