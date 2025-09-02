# 题目信息

# Romantic Glasses

## 题目描述

Iulia has $ n $ glasses arranged in a line. The $ i $ -th glass has $ a_i $ units of juice in it. Iulia drinks only from odd-numbered glasses, while her date drinks only from even-numbered glasses.

To impress her date, Iulia wants to find a contiguous subarray of these glasses such that both Iulia and her date will have the same amount of juice in total if only the glasses in this subarray are considered. Please help her to do that.

More formally, find out if there exists two indices $ l $ , $ r $ such that $ 1 \leq l \leq r \leq n $ , and $ a_l + a_{l + 2} + a_{l + 4} + \dots + a_{r} = a_{l + 1} + a_{l + 3} + \dots + a_{r-1} $ if $ l $ and $ r $ have the same parity and $ a_l + a_{l + 2} + a_{l + 4} + \dots + a_{r - 1} = a_{l + 1} + a_{l + 3} + \dots + a_{r} $ otherwise.

## 说明/提示

In the first test case, Iulia can pick $ l=1 $ and $ r=3 $ . Then she drinks $ a_1+a_3=1+2=3 $ units and her date drinks $ a_2=3 $ units of juice.

In the second test case, Iulia can pick $ l=2 $ and $ r=5 $ . Then she drinks $ a_3+a_5=1+1=2 $ units and her date drinks $ a_2+a_4=1+1=2 $ units of juice.

In the third test case no such contiguous subarray works.

In the fourth test case, Iulia can pick $ l=2 $ and $ r=8 $ . Then she drinks $ a_3+a_5+a_7=11+1+1=13 $ units and her date drinks $ a_2+a_4+a_6+a_8=2+4+5+2=13 $ units of juice.

## 样例 #1

### 输入

```
6
3
1 3 2
6
1 1 1 1 1 1
10
1 6 9 8 55 3 14 2 7 2
8
1 2 11 4 1 5 1 2
6
2 6 1 5 7 8
9
2 5 10 4 4 9 6 7 8```

### 输出

```
YES
YES
NO
YES
NO
YES```

# AI分析结果



### 中文题目重写
# 浪漫的杯子

## 题目描述

Iulia 有 $n$ 个杯子排成一列，第 $i$ 个杯子里有 $a_i$ 单位的果汁。Iulia 只喝奇数位置的杯子，而她的约会对象只喝偶数位置的杯子。

为了给约会对象留下深刻印象，Iulia 想要找到一个连续的子数组，使得在这个子数组范围内，两人喝到的果汁总量相同。请帮助她实现这个目标。

形式化地，需要判断是否存在两个下标 $l$ 和 $r$（$1 \leq l \leq r \leq n$），满足：
- 若 $l$ 和 $r$ 奇偶性相同，则奇数位置杯子的果汁总和等于偶数位置杯子的果汁总和（即 $a_l + a_{l+2} + \dots + a_r = a_{l+1} + a_{l+3} + \dots + a_{r-1}$）
- 若 $l$ 和 $r$ 奇偶性不同，则奇数位置杯子的总和等于偶数位置杯子的总和（即 $a_l + a_{l+2} + \dots + a_{r-1} = a_{l+1} + a_{l+3} + \dots + a_r$）

## 说明/提示
（样例说明与原始内容一致，此处省略）

---

### 题解分析与结论

#### 核心算法思路
所有题解均基于**前缀和+哈希表**的核心思想：
1. **奇偶位置差值转化**：将奇数位置数值视为正，偶数位置视为负（或相反），构造新的差值序列
2. **前缀和哈希检测**：维护前缀和，若两个位置前缀和相同，则中间子数组差值为零，即满足条件
3. **哈希表优化查询**：使用 `set/map` 存储历史前缀和，实现 $O(1)$ 时间的重复检测

#### 关键实现技巧
1. **初始哈希表插入0**：处理从第一个元素开始的合法子数组
2. **实时计算替代预存数组**：无需存储完整前缀和数组，空间优化至 $O(n)$
3. **奇偶位置合并处理**：通过奇偶性判断直接累加，无需分开存储两个数组

---

### 优质题解推荐

#### 1. 作者：WsW_（★★★★★）
**核心亮点**：
- 最简洁的实现，直接使用 `set` 存储差值
- 巧妙利用奇偶性计算索引，代码行数最少
- 时间复杂度 $O(n \log n)$，空间优化良好

**关键代码**：
```cpp
set<ll> s;
ll sum[2] = {0};
for(int i=1; i<=n; i++){
    sum[i&1] += a[i]; // 根据奇偶性累加
    if(s.count(sum[1]-sum[0])) return YES;
    s.insert(sum[1]-sum[0]);
}
```

#### 2. 作者：ThySecret（★★★★☆）
**核心亮点**：
- 将奇数位置数值取反构造新序列
- 转化为经典子数组和为0问题，思路直观
- 强调多测初始化注意事项，代码鲁棒性强

**调试心得**：
> "映射表必须 clear！即使找到答案也要继续读入剩余数据，否则后续测试会错位"

**关键代码**：
```cpp
int x = 0;
map<int, bool> mark{{0, true}};
for(int i=1; i<=n; i++){
    x += (i%2 ? -a[i] : a[i]); // 构造差值序列
    if(mark[x]) return YES;
    mark[x] = true;
}
```

#### 3. 作者：DrAlfred（★★★★☆）
**核心亮点**：
- 严格数学公式推导，展现完整变形过程
- 使用pair维护奇偶和，便于理解差值概念
- 代码包含详细注释，可读性极佳

**实现亮点**：
```cpp
long long x = 0, y = 0; // x:奇数位和, y:偶数位和
set<long long> S{0};
for(int i=1; i<=n; i++){
    (i&1 ? x : y) += a[i];
    if(S.count(x - y)) return YES;
    S.insert(x - y);
}
```

---

### 拓展训练
1. **前缀和+哈希表**：[P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
2. **差值转化技巧**：[P3143 前缀后缀最大值](https://www.luogu.com.cn/problem/P3143)
3. **子数组特殊性质**：[CF1598C Delete Two Elements](https://codeforces.com/problemset/problem/1598/C)

---

### 总结心得
1. **初始化陷阱**：多位作者强调必须预先插入 `sum[0] = 0`
2. **输入处理教训**：找到答案后仍需完整读入当前测试数据
3. **类型选择**：使用 `long long` 避免溢出，实测中 `int` 会导致WA
4. **容器选择**：`unordered_map` 可能被卡，优先使用 `map/set`

---
处理用时：49.02秒