# 题目信息

# [ARC172C] Election

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc172/tasks/arc172_c

今年の AtCoder 市長選挙には A 候補と B 候補の $ 2 $ 人が立候補し、$ N $ 人の有権者が投票しました。 投票者にはそれぞれ $ 1 $ から $ N $ までの番号が付けられており、投票者 $ i $ $ (1\ \leq\ i\ \leq\ N) $ は $ c_i $ 候補に投票しました。

さて、これから開票作業が行われます。 開票作業では $ 1 $ 票ずつ票が開けられていき、票が開けられるたびに、現時点での開票結果が以下の $ 3 $ つのうちどれであるかが発表されます。

- **結果 A:** 現時点で、A 候補の方が獲得票数が多い。
- **結果 B:** 現時点で、B 候補の方が獲得票数が多い。
- **結果 C:** 現時点で、A 候補と B 候補の獲得票数が同数である。
 
ここで開票の順番にはルールがあり、投票者 $ 1 $ 以外の票は、投票者の番号の小さい順に開票されなければなりません。 (投票者 $ 1 $ の票は好きなタイミングで開票してかまいません)

発表される開票結果の列としてあり得るものが何通りあるかを答えてください。

 開票結果の列とは$ i $ 票目 $ (1\ \leq\ i\ \leq\ N) $ が開けられたタイミングで報告された結果を $ s_i $ (`A`, `B`, `C` のいずれか) とするとき，文字列 $ s_1\ s_2\ \dots\ s_N $ のことを指します。

## 说明/提示

### 制約

- $ N $ は $ 2\ \leq\ N\ \leq\ 1000000 $ を満たす整数
- $ c_1,\ c_2,\ \dots,\ c_N $ は `A` または `B`
 
### Sample Explanation 1

この入力例では、開票が行われる順番として以下の $ 4 $ 通りが考えられます。 - 投票者 $ 1\ \to\ 2\ \to\ 3\ \to\ 4 $ の順に開票が行われる。 - 投票者 $ 2\ \to\ 1\ \to\ 3\ \to\ 4 $ の順に開票が行われる。 - 投票者 $ 2\ \to\ 3\ \to\ 1\ \to\ 4 $ の順に開票が行われる。 - 投票者 $ 2\ \to\ 3\ \to\ 4\ \to\ 1 $ の順に開票が行われる。 開票結果の列は上から順に `AAAC`、`AAAC`、`ACAC`、`ACBC` となるため、開票結果の列としてあり得るものは $ 3 $ 通りです。

### Sample Explanation 2

どのような順序で開票を行っても、開票結果の列は `AAAA` となります。

## 样例 #1

### 输入

```
4

AABB```

### 输出

```
3```

## 样例 #2

### 输入

```
4

AAAA```

### 输出

```
1```

## 样例 #3

### 输入

```
10

BBBAAABBAA```

### 输出

```
5```

## 样例 #4

### 输入

```
172

AABAAAAAABBABAABBBBAABBAAABBABBABABABBAAABAAABAABAABBBBABBBABBABBBBBBBBAAABAAABAAABABBBAABAAAABABBABBABBBBBABAABAABBBABABBAAAABAABABBBABAAAABBBBABBBABBBABAABBBAAAABAAABAAAB```

### 输出

```
24```

# AI分析结果



---

## 算法分类  
前缀和与数学分析

---

## 题解思路与核心难点  

### 核心逻辑  
1. **问题转换**：将投票结果视为数值序列（A=+1，B=-1），统计前缀和的变化情况。
2. **关键观察**：只有当第一个人的投票插入到某个位置时，该位置的前缀和的绝对值 ≤1，才可能改变结果序列。
3. **数学推导**：对每个位置 i，原前缀和 s[i] 的绝对值 ≤1 时，插入第一个人的票可能导致该位置的前缀和符号变化，从而贡献新的结果。

### 解决难点  
- **高效判断插入点的有效性**：直接枚举所有可能的插入位置会导致 O(n²) 复杂度，但通过分析数学条件（|s[i]| ≤1），可将复杂度降至 O(n)。
- **避免重复计数**：仅统计与原结果不同的插入点，通过前缀和的符号变化和绝对值条件过滤无效位置。

---

## 最优思路提炼  
**关键技巧**：  
1. **符号判断法**：将第一个人的票归一化为 A（通过反转所有票的符号），简化问题。
2. **前缀和筛选**：预处理前缀和数组，仅检查满足 |s[i]| ≤1 的位置，统计可能改变结果的情况数。  
3. **线性时间复杂度**：通过一次遍历完成所有条件判断，无需复杂数据结构。

---

## 题解评分（≥4星）  
1. **Register_int（5星）**  
   - 思路清晰，代码简洁高效（O(n) 时间复杂度）。  
   - 核心逻辑通过符号归一化和前缀和筛选快速统计结果，代码仅需 10 行。  
2. **rui_er（4星）**  
   - 提出相邻顺序差异的判断方法，逻辑简洁。  
   - 代码短小精悍，但需理解前缀和符号变化的数学本质。  
3. **Ivan422（4星）**  
   - 模拟交换过程并统计差异，思路直观。  
   - 代码通过前缀和直接判断变化，复杂度为 O(n)，但需要倒序遍历。

---

## 核心代码实现  
```cpp
// 核心逻辑（Register_int 题解）
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 10;

int n, a[MAXN], ans; char s[MAXN];

int main() {
    scanf("%d%s", &n, s + 1), ans = 1;
    if (s[1] == 'B') { // 符号归一化（转为处理A的情况）
        for (int i = 1; i <= n; i++) 
            s[i] = (s[i] == 'A') ? 'B' : 'A';
    }
    // 计算前缀和数组
    for (int i = 1; i <= n; i++) 
        a[i] = a[i-1] + (s[i] == 'A' ? 1 : -1);
    // 统计可能改变结果的位置
    for (int i = 2; i <= n; i++) 
        if (s[i] == 'B' && abs(a[i]) <= 1) ans++;
    printf("%d", ans);
}
```

---

## 同类型题与套路  
**相似问题特征**：  
- 动态插入元素影响前缀状态  
- 统计不同状态序列的数量  

**推荐题目**：  
1. [LeetCode 325. 和等于 k 的最长子数组长度](https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/)  
   - 前缀和 + 哈希表记录状态  
2. [CF 1526C2. Potions (Hard Version)](https://codeforces.com/problemset/problem/1526/C2)  
   - 前缀和 + 贪心选择  
3. [洛谷 P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)  
   - 前缀和动态维护极值  

---

## 可视化设计  
### 动画方案  
1. **折线图动态绘制**：  
   - 绘制前缀和折线图，初始不包含第一个人的票。  
   - 插入第一个人的票时，折线在特定位置（|s[i]| ≤1）发生突变，高亮该点。  
2. **颜色标记**：  
   - 红色：当前检查的位置 i，满足 |s[i]| ≤1。  
   - 绿色：已确认贡献新结果的位置。  
3. **音效提示**：  
   - 插入有效位置时播放“叮”声，无效位置播放“嘟”声。  

### 复古像素风格  
1. **8位像素化界面**：  
   - 使用 16 色调色板，折线图以像素方块表示。  
   - 背景为灰色网格，折线颜色渐变（绿→蓝→红）。  
2. **Canvas 绘制**：  
   ```javascript
   function drawLine(ctx, points) {
       ctx.beginPath();
       ctx.moveTo(0, 200 - points[0] * 20); // 缩放坐标
       points.forEach((val, idx) => {
           ctx.lineTo(idx * 10, 200 - val * 20);
       });
       ctx.strokeStyle = '#00FF00'; // 像素绿
       ctx.stroke();
   }
   ```
3. **音效触发**：  
   ```javascript
   function playSound(type) {
       const audioCtx = new AudioContext();
       const oscillator = audioCtx.createOscillator();
       oscillator.type = 'square'; // 8位方波音效
       oscillator.frequency.setValueAtTime(type === 'valid' ? 440 : 220, audioCtx.currentTime);
       oscillator.connect(audioCtx.destination);
       oscillator.start();
       oscillator.stop(audioCtx.currentTime + 0.1);
   }
   ```

---

## 总结  
本题通过数学分析将复杂插入问题转换为前缀和的符号判断，核心在于利用绝对值条件和符号归一化简化计算。可视化设计结合折线图和复古音效，可直观展示算法动态过程，适合教学演示。

---
处理用时：75.89秒