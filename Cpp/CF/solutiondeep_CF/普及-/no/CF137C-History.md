# 题目信息

# History

## 题目描述

Polycarpus likes studying at school a lot and he is always diligent about his homework. Polycarpus has never had any problems with natural sciences as his great-great-grandfather was the great physicist Seinstein. On the other hand though, Polycarpus has never had an easy time with history.

Everybody knows that the World history encompasses exactly $ n $ events: the $ i $ -th event had continued from the year $ a_{i} $ to the year $ b_{i} $ inclusive ( $ a_{i}&lt;b_{i} $ ). Polycarpus easily learned the dates when each of $ n $ events started and ended (Polycarpus inherited excellent memory from his great-great-granddad). But the teacher gave him a more complicated task: Polycaprus should know when all events began and ended and he should also find out for each event whether it includes another event. Polycarpus' teacher thinks that an event $ j $ includes an event $ i $ if $ a_{j}&lt;a_{i} $ and $ b_{i}&lt;b_{j} $ . Your task is simpler: find the number of events that are included in some other event.

## 说明/提示

In the first example the fifth event is contained in the fourth. Similarly, the fourth event is contained in the third, the third — in the second and the second — in the first.

In the second example all events except the first one are contained in the first.

In the third example only one event, so the answer is 0.

## 样例 #1

### 输入

```
5
1 10
2 9
3 8
4 7
5 6
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
1 100
2 50
51 99
52 98
10 60
```

### 输出

```
4
```

## 样例 #3

### 输入

```
1
1 1000000000
```

### 输出

```
0
```

# AI分析结果



# 中文翻译
## 题目描述

Polycarpus 非常喜欢学习，尤其擅长自然科学，但历史总让他头疼。世界历史共有 $n$ 个事件，第 $i$ 个事件从 $a_i$ 年持续到 $b_i$ 年（$a_i < b_i$）。Polycarpus 需要统计有多少个事件被其他事件完全包含（即存在事件 $j$ 满足 $a_j < a_i$ 且 $b_i < b_j$）。

## 输入格式
输入第一行为整数 $n$，表示事件个数。接下来 $n$ 行每行两个整数 $a_i, b_i$，表示事件的起止年份。

## 输出格式
输出被其他事件包含的事件个数。

## 样例
### 样例输入 1
```
5
1 10
2 9
3 8
4 7
5 6
```
### 样例输出 1
```
4
```

---

**算法分类**：排序

---

## 题解分析与结论

### 核心思路
所有题解均采用排序后贪心的策略：
1. **按开始时间升序排序**，确保后续事件的开始时间不小于之前的。
2. **维护最大右端点**：遍历时记录当前遇到的最大右端点。若当前事件的右端点小于该值，则说明其被某个前序事件包含。

### 难点与对比
- **排序方式**：需保证事件按开始时间升序排序，处理右端点时只需比较是否小于当前最大值。
- **初始值处理**：需正确初始化最大右端点（应为第一个事件的右端点），但部分题解初始化为 0，可能导致负数年份事件误判。
- **正确性隐患**：当存在事件的开始时间相同或右端点小于初始值时，部分题解代码可能错误计数，但原题测试数据可能未覆盖这些情况。

---

## 精选题解

### 题解作者：Zhai0915（4 星）
**关键亮点**：
- 代码简洁，使用 `pair` 存储事件，默认排序后直接遍历。
- 逻辑清晰，线性时间完成统计。

**核心代码**：
```cpp
sort(s, s + n);
int last = 0, ans = 0;
for (int i = 0; i < n; i++) {
    if (s[i].second < last) ans++;
    else last = s[i].second;
}
```

### 题解作者：LBYYSM_123（4 星）
**关键亮点**：
- 使用 `pair` 默认排序，代码简洁高效。
- 循环从 1 开始（索引 1 存储数据），但未初始化变量导致潜在风险。

**核心代码**：
```cpp
sort(s + 1, s + n + 1);
int last = 0, ans = 0;
for (int i = 1; i <= n; i++) {
    if (s[i].second < last) ans++;
    else last = s[i].second;
}
```

### 题解作者：Air_Color5（4 星）
**关键亮点**：
- 提供两种存储方式（`pair` 和 `map`），思路清晰。
- 明确指出排序后只需比较右端点。

**核心代码**：
```cpp
sort(v.begin(), v.end());
int RightMax = 0, res = 0;
for (auto &e : v) {
    if (e.second < RightMax) res++;
    else RightMax = e.second;
}
```

---

## 最优思路总结
1. **排序预处理**：按开始时间升序、结束时间降序排序，确保后续事件不会因开始时间相同而误判。
2. **贪心维护**：遍历时记录最大右端点，若当前事件右端点小于该值则计数。
3. **初始值修正**：应将初始最大右端点设为第一个事件的右端点，避免负数年份错误。

---

## 相似题目推荐
1. [P1102 覆盖点统计](https://www.luogu.com.cn/problem/P1102)（区间覆盖）
2. [P1719 最大矩形面积](https://www.luogu.com.cn/problem/P1719)（排序与贪心）
3. [P3143 钻石收集者](https://www.luogu.com.cn/problem/P3143)（滑动窗口与排序）

---

## 调试心得摘录
- **初始值陷阱**：`last` 初始化为 0 在负数年份场景下会导致错误，应初始化为第一个事件的右端点。
- **排序细节**：开始时间相同的事件需按结束时间降序排列，避免后续事件被误判包含。

---
处理用时：358.11秒