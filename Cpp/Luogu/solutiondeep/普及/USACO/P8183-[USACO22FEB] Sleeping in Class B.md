# 题目信息

# [USACO22FEB] Sleeping in Class B

## 题目描述

奶牛 Bessie 最近很高兴能够重返线下课堂！不幸的是，她的老师 Farmer John 讲课非常无聊，因此她经常在课堂上睡着。  
Farmer John 注意到 Bessie 在课堂上没有专心听讲。他让班上的另一位学生 Elsie 记录 Bessie 在每节课上睡着的次数。总共有 $N$ 节课（$1 \leq N \leq 10^5$），Elsie 记录到 Bessie 在第 $i$ 节课上睡着了 $a_i$ 次（$0 \leq a_i \leq 10^6$）。所有课程中 Bessie 睡着的总次数不超过 $10^6$。

Elsie 对 Bessie 感到非常竞争，她希望让 Farmer John 觉得 Bessie 在每节课上睡着的次数是一致的——让问题看起来完全是 Bessie 的错，而与 Farmer John 有时无聊的讲课无关。Elsie 修改记录的唯一方式是将两节相邻的课合并。例如，如果 $a = [1,2,3,4,5]$，那么如果 Elsie 合并第二和第三节课，记录将变为 $[1,5,4,5]$。

请帮助 Elsie 计算她需要对记录进行的最少修改次数，以使记录中的所有数字相等。

## 说明/提示

对于第一个测试用例，Elsie 可以通过 3 次修改将记录改为全为 $3$：
```
   1 2 3 1 1 1
-> 3 3 1 1 1
-> 3 3 2 1
-> 3 3 3
```

对于第二个测试用例，Elsie 可以通过 2 次修改将记录改为全为 $7$：
```
   2 2 3
-> 2 5
-> 7
```

对于最后一个测试用例，Elsie 不需要进行任何操作，因为记录已经由相同的数字组成。

## 样例 #1

### 输入

```
3
6
1 2 3 1 1 1
3
2 2 3
5
0 0 0 0 0```

### 输出

```
3
2
0```

# AI分析结果



### 综合分析与结论

本题核心在于利用总和不变的性质，通过枚举总和的因数确定目标段值，并验证能否分割成对应段数。最优解法需逆序枚举因数以快速找到最大可行段数，时间复杂度为 O(n * 因数个数)。题解中普遍采用这一思路，但部分实现存在边界条件处理或枚举顺序错误。

---

### 高星题解推荐

#### 1. 作者：Zirnc（5星）
**关键亮点**  
- 逆序枚举段数，直接利用原数组长度递减遍历，快速找到最大可行段数。  
- 代码简洁高效，逻辑清晰，无冗余步骤。  
- 时间复杂度严格符合题目要求。

**核心代码实现思路**  
```cpp
for (int i = n; i >= 1; i--) { // 逆序枚举段数
  if (sum % i != 0) continue;
  int target = sum / i;
  int cur = 0;
  bool valid = true;
  for (int j = 0; j < n; j++) {
    cur += a[j];
    if (cur > target) { valid = false; break; }
    else if (cur == target) cur = 0;
  }
  if (valid) return n - i; // 找到解
}
```

#### 2. 作者：lnwhl（4星）
**关键亮点**  
- 与 Zirnc 思路一致，代码结构相似，变量命名略有不同。  
- 添加了详细的注释，增强了可读性。  

**核心代码片段**  
```cpp
for (int j = n; j >= 1; j--) { // 逆序枚举段数
  if (sum % j != 0) continue;
  int sumT = sum / j;
  int pre = 0;
  bool ok = true;
  for (int k = 1; k <= n; k++) {
    pre += a[k];
    if (pre > sumT) { ok = false; break; }
    else if (pre == sumT) pre = 0;
  }
  if (ok) return n - j;
}
```

---

### 最优思路总结
1. **因数枚举**：总和的所有因数均需考虑，最终目标值为总和除以段数。  
2. **逆序验证**：从大到小枚举段数，确保首次找到的解对应最少操作次数。  
3. **贪心分割**：遍历数组累加，严格匹配目标值，避免超限。

---

### 举一反三
- **类似题目**  
  - [CF1462D - Add to Neighbour and Remove](https://codeforces.com/problemset/problem/1462/D)（同模型）  
  - [P3143 [USACO16OPEN] Diamond Collector S](https://www.luogu.com.cn/problem/P3143)（分段最值问题）  
  - [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)（连续子数组和问题）  

---

### 调试心得摘录
- **江户川コナン**：在特判数组全等时代码存在越界风险（`a[i+1]` 当 `i=n` 时越界），需注意循环边界。  
- **oddy**：错误地从小到大枚举因数，导致无法优先找到最大段数，解法逻辑错误。  
- **Dr_Gilbert**：从数组最大值开始枚举，可能漏掉更小的合法因数，需覆盖全部可能。

---
处理用时：99.19秒