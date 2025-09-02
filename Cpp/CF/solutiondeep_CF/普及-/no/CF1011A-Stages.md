# 题目信息

# Stages

## 题目描述

Natasha is going to fly to Mars. She needs to build a rocket, which consists of several stages in some order. Each of the stages is defined by a lowercase Latin letter. This way, the rocket can be described by the string — concatenation of letters, which correspond to the stages.

There are $ n $ stages available. The rocket must contain exactly $ k $ of them. Stages in the rocket should be ordered by their weight. So, after the stage with some letter can go only stage with a letter, which is at least two positions after in the alphabet (skipping one letter in between, or even more). For example, after letter 'c' can't go letters 'a', 'b', 'c' and 'd', but can go letters 'e', 'f', ..., 'z'.

For the rocket to fly as far as possible, its weight should be minimal. The weight of the rocket is equal to the sum of the weights of its stages. The weight of the stage is the number of its letter in the alphabet. For example, the stage 'a 'weighs one ton,' b 'weighs two tons, and' z' — $ 26 $ tons.

Build the rocket with the minimal weight or determine, that it is impossible to build a rocket at all. Each stage can be used at most once.

## 说明/提示

In the first example, the following rockets satisfy the condition:

- "adx" (weight is $ 1+4+24=29 $ );
- "ady" (weight is $ 1+4+25=30 $ );
- "bdx" (weight is $ 2+4+24=30 $ );
- "bdy" (weight is $ 2+4+25=31 $ ).

Rocket "adx" has the minimal weight, so the answer is $ 29 $ .

In the second example, target rocket is "belo". Its weight is $ 2+5+12+15=34 $ .

In the third example, $ n=k=2 $ , so the rocket must have both stages: 'a' and 'b'. This rocket doesn't satisfy the condition, because these letters are adjacent in the alphabet. Answer is -1.

## 样例 #1

### 输入

```
5 3
xyabd
```

### 输出

```
29```

## 样例 #2

### 输入

```
7 4
problem
```

### 输出

```
34```

## 样例 #3

### 输入

```
2 2
ab
```

### 输出

```
-1```

## 样例 #4

### 输入

```
12 1
abaabbaaabbb
```

### 输出

```
1```

# AI分析结果



# Stages

## 题目描述

娜塔莎要造火箭飞往火星。火箭由多个阶段组成，每个阶段用一个小写字母表示。火箭的字符串描述即为各阶段字母的拼接。

现有 $n$ 个可用阶段，需从中选择恰好 $k$ 个组成火箭。各阶段必须按字母序排列，且相邻阶段字母在字母表中至少间隔两个位置（例如 'c' 后只能接 'e' 及之后的字母）。火箭的重量为各阶段字母对应的数值之和（a=1，b=2，…，z=26）。求最小重量，若无法构建则输出 -1。

## 算法分类
贪心

---

## 题解综合分析

题目核心为贪心策略：排序后，优先选取尽可能小的字母，并确保相邻字母间隔≥2。关键点包括：
1. **排序预处理**：将字符按字母序排序，确保选择顺序的局部最优
2. **间隔判断**：维护前一个选中的字符，保证后续字符满足间距要求
3. **去重处理**：同一字母多次出现时仅保留第一个可用位置

以下为评分较高的题解：

---

### 小闸蟹的题解（4星）
**亮点**：代码简洁，逻辑清晰，处理边界条件完善  
**核心思路**：
- 先取排序后的第一个字符
- 遍历剩余字符，若当前字符与前一个选中的字符差>1则选中
- 实时检查是否选够k个字符

```cpp
std::sort(Str.begin(), Str.end());
int Ans = Str[0] - 'a' + 1; 
char Pre = Str[0];
for (int i = 1; i < n; ++i) {
    if (Str[i] - Pre > 1) {
        Ans += Str[i] - 'a' + 1;
        Pre = Str[i];
        if (--k == 0) break;
    }
}
```

---

### oimaster的题解（4星）
**亮点**：使用vector动态记录合法字符，逻辑模块化  
**核心思路**：
- 将字符转换为数值并排序
- 遍历时维护`last`记录最后选中的数值
- 使用vector存储所有符合条件的字符，最后检查数量

```cpp
sort(a+1, a+n+1);
vector<int> v;
int last = -1;
for (int i=1; i<=n; ++i) {
    if (a[i] >= last+2) {
        v.push_back(a[i]);
        last = a[i];
    }
}
if (v.size() >= k) sum += accumulate(v.begin(), v.begin()+k, 0);
```

---

### Yang_OIer的题解（4星）
**亮点**：显式处理字符去重，代码可读性高  
**核心思路**：
- 将字符转换为数值后排序
- 遍历时跳过不满足间隔的字符
- 使用vector存储合法选择，直接取前k个求和

```cpp
sort(a+1, a+n+1);
vector<int> v;
int last = -1;
for (int i=1; i<=n; ++i) {
    if (a[i] >= last+2) {
        v.push_back(a[i]);
        last = a[i];
    }
}
if (v.size() < k) cout << -1;
else cout << accumulate(v.begin(), v.begin()+k, 0);
```

---

## 最优思路总结
1. **排序预处理**：将输入字符按字母序排序，确保优先选择较小字符
2. **贪心选择**：从第一个字符开始，每次选择满足间隔的最小可用字符
3. **集合维护**：动态记录已选字符，保证后续选择始终符合规则
4. **边界处理**：及时检查是否选够k个字符，避免无效遍历

## 拓展建议
类似贪心问题可关注：
1. **间隔选择**：如[CF1029C](https://codeforces.com/problemset/problem/1029/C)（选取区间避免重叠）
2. **字典序优化**：如[P1090 合并果子](https://www.luogu.com.cn/problem/P1090)（优先队列优化）
3. **离散化处理**：如[P1908 逆序对](https://www.luogu.com.cn/problem/P1908)（树状数组维护）

## 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)（贪心+优先队列）
2. [P1233 木棍加工](https://www.luogu.com.cn/problem/P1233)（二维贪心+偏序）
3. [CF1029C Maximal Intersection](https://codeforces.com/problemset/problem/1029/C)（区间选择优化）

---
处理用时：230.92秒