# 题目信息

# Amr and The Large Array

## 题目描述

Amr has got a large array of size $ n $ . Amr doesn't like large arrays so he intends to make it smaller.

Amr doesn't care about anything in the array except the beauty of it. The beauty of the array is defined to be the maximum number of times that some number occurs in this array. He wants to choose the smallest subsegment of this array such that the beauty of it will be the same as the original array.

Help Amr by choosing the smallest subsegment possible.

## 说明/提示

A subsegment $ B $ of an array $ A $ from $ l $ to $ r $ is an array of size $ r-l+1 $ where $ B_{i}=A_{l+i-1} $ for all $ 1<=i<=r-l+1 $

## 样例 #1

### 输入

```
5
1 1 2 2 1
```

### 输出

```
1 5```

## 样例 #2

### 输入

```
5
1 2 2 3 1
```

### 输出

```
2 3```

## 样例 #3

### 输入

```
6
1 2 2 1 1 2
```

### 输出

```
1 5```

# AI分析结果



# Amr and The Large Array

## 题目描述

Amr 有一个大小为 $n$ 的数组。Amr 不喜欢大数组，因此他打算将其缩小。

Amr 只关心数组的美丽度。数组的美丽度定义为数组中某个数字出现的最大次数。他希望选择一个原数组的最小子段，使得该子段的美丽度与原数组相同。

请帮助 Amr 选择尽可能小的子段。

## 说明/提示

子段 $B$ 是数组 $A$ 从 $l$ 到 $r$ 的部分，大小为 $r-l+1$，其中 $B_i = A_{l+i-1}$。

## 样例 #1

### 输入

```
5
1 1 2 2 1
```

### 输出

```
1 5
```

## 样例 #2

### 输入

```
5
1 2 2 3 1
```

### 输出

```
2 3
```

## 样例 #3

### 输入

```
6
1 2 2 1 1 2
```

### 输出

```
1 5
```

---

**算法分类**：模拟

---

## 题解分析与结论

### 核心思路
1. **统计关键信息**：遍历数组记录每个数字的首次/末次出现位置及出现次数。
2. **确定最大频次**：找出原数组的最大出现次数。
3. **筛选候选元素**：收集所有出现次数等于最大频次的数字。
4. **计算最短区间**：比较候选元素的首次-末次区间，选择长度最小的。

### 最优题解亮点

#### [作者：_xiaxii](https://www.luogu.com.cn/user/xxxxx) ⭐⭐⭐⭐
- **关键技巧**：初始化左端点数组为极大值，确保首次出现位置正确记录。
- **代码亮点**：
  ```cpp
  memset(l, 0x3f, sizeof(l)); // 左端点初始化为极大值
  for (遍历数组) {
      l[a[i]] = min(l[a[i]], i); // 动态更新左端点
      r[a[i]] = max(r[a[i]], i); // 动态更新右端点
  }
  ```
- **实现优势**：通过数值范围遍历避免重复检查相同元素，逻辑更集中。

#### [作者：KID2695](https://www.luogu.com.cn/user/xxxxx) ⭐⭐⭐⭐
- **关键思路**：在遍历数组时动态更新最优解，减少额外空间。
- **代码亮点**：
  ```cpp
  for (遍历数组元素) {
      if (当前元素频次等于最大值) {
          比较并更新最优区间
      }
  }
  ```
- **效率优势**：时间复杂度严格 O(n)，适合大数值范围场景。

---

## 关键代码实现

### 核心逻辑代码
```cpp
int main() {
    int n, max_cnt = 0;
    cin >> n;
    vector<int> a(n+1);
    unordered_map<int, int> cnt, first, last;
    
    // 统计频次及首尾位置
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (!first.count(a[i])) first[a[i]] = i;
        last[a[i]] = i;
        max_cnt = max(max_cnt, ++cnt[a[i]]);
    }
    
    // 寻找最短区间
    int min_len = n, L = 1, R = n;
    for (auto [num, c] : cnt) {
        if (c == max_cnt && last[num] - first[num] < min_len) {
            min_len = last[num] - first[num];
            L = first[num];
            R = last[num];
        }
    }
    cout << L << " " << R;
}
```

---

## 拓展与关联

### 类似题目推荐
1. [P3405 出现次数最多的数（简单版）](https://www.luogu.com.cn/problem/P3405)
2. [P2034 选择数字（滑动窗口+贪心）](https://www.luogu.com.cn/problem/P2034)
3. [P2343 宝石管理系统（频次统计+区间查询）](https://www.luogu.com.cn/problem/P2343)

### 关键技巧总结
- **频次统计与区间记录**：通过一次遍历同时完成频次统计和位置记录，避免多次扫描。
- **极值初始化技巧**：左端点初始化为极大值确保首次出现正确捕获。
- **哈希表替代数组**：当数值范围较大时，可用哈希表存储各数字的统计信息。

---
处理用时：146.40秒