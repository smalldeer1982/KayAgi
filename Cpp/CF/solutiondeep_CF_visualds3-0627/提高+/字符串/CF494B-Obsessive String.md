# 题目信息

# Obsessive String

## 题目描述

给定两个字符串 $s$ 和 $t$。定义一种合法的截取方案为，在字符串 $s$ 中截取若干（大于 $0$）个互不相交的子串，满足 $t$ 是每个这些子串的子串。

请你输出总方案数模 $10^9 + 7$ 的值。

## 说明/提示

保证 $1 \leq |s|, |t| \leq 10^5$，字符串中只包含小写拉丁字母。

## 样例 #1

### 输入

```
ababa
aba
```

### 输出

```
5
```

## 样例 #2

### 输入

```
welcometoroundtwohundredandeightytwo
d
```

### 输出

```
274201
```

## 样例 #3

### 输入

```
ddd
d
```

### 输出

```
12
```

# AI分析结果



## **算法分类**  
动态规划（DP） + 字符串匹配（KMP/哈希）

---

## **综合分析与结论**  
### 核心思路  
1. **字符串预处理**：通过 KMP 或哈希快速找到所有包含 $t$ 的子串区间，标记每个位置 $i$ 对应的最远合法起点 $d[i]$（即最后一个包含 $t$ 的子串的左端点）。  
2. **动态规划优化**：定义 $dp[i]$ 表示以 $i$ 结尾的合法方案数。通过前缀和优化，将转移复杂度从 $O(n^2)$ 降为 $O(n)$。  
3. **数学变换**：利用前缀和数组 $f$（$\sum dp$）和 $ss$（$\sum i \cdot dp$），将转移公式拆解为 $dp[i] = d[i] \cdot f[d[i]-1] - ss[d[i]-1]$。  

### 解决难点  
- **快速匹配**：通过 KMP/哈希快速找到所有包含 $t$ 的子串，避免暴力匹配的 $O(nm)$ 复杂度。  
- **转移优化**：将原始 $O(n^2)$ 的枚举起点和前缀的嵌套循环，转化为前缀和的线性计算。  

### 可视化设计  
- **动画展示**：  
  1. **字符串扫描**：高亮当前处理的字符 $i$，标红 $d[i]$ 对应的起点范围。  
  2. **DP 状态更新**：动态显示 $dp[i]$ 的计算过程，如 $d[i] \cdot f[d[i]-1]$（蓝色区域）减去 $ss[d[i]-1]$（红色区域）。  
  3. **前缀和同步**：实时更新 $f$ 和 $ss$ 数组的数值变化，用颜色渐变表示增长趋势。  
- **复古风格**：以 8-bit 像素风格绘制字符串和状态数组，关键操作用“哔”音效提示，背景音乐为低比特循环旋律。  

---

## **题解清单 (≥4星)**  
1. **RainFestival (★★★★★)**  
   - **亮点**：完整推导 DP 优化过程，代码简洁高效，使用 KMP 预处理。  
   - **代码片段**：  
     ```cpp  
     dp[i] = (1ll * d[i] * f[d[i]-1] % mod - ss[d[i]-1] + mod) % mod;  
     ```  
2. **Mav11Young (★★★★☆)**  
   - **亮点**：哈希替代 KMP，引入双前缀和优化，代码可读性强。  
   - **代码片段**：  
     ```cpp  
     dp[i] = (i-m+1 + sum2[i-m]) % P;  
     ```  
3. **木xx木大 (★★★★☆)**  
   - **亮点**：详细解释状态转移逻辑，代码注释清晰，适合新手理解。  

---

## **最优思路提炼**  
1. **预处理关键点**：对每个位置 $i$ 找到最近包含 $t$ 的子串起点 $d[i]$。  
2. **前缀和优化**：维护 $\sum dp$ 和 $\sum i \cdot dp$，将转移公式转化为线性组合。  
3. **边界处理**：初始条件 $dp[0] = 1$，最终答案取 $\sum dp - 1$（排除空方案）。  

---

## **同类型题与套路**  
- **通用套路**：动态规划结合前缀和优化，用于处理区间覆盖、不重叠子序列计数问题。  
- **类似题目**：  
  1. [CF1132F Clear the String](https://codeforces.com/problemset/problem/1132/F)：区间 DP 删除连续子串。  
  2. [LeetCode 139 Word Break](https://leetcode.com/problems/word-break/)：字符串分割为合法子串。  

---

## **推荐相似题目**  
1. **P3375**：KMP 模板题。  
2. **P2679**：子串计数，需处理不重叠条件。  
3. **P4051**：后缀数组与字符串匹配结合。  

---

## **个人心得摘录**  
> “在转移中发现枚举左端点的区间是连续的，立刻想到前缀和的前缀和，这是优化的关键。” —— Mav11Young  

---

## **代码实现（核心逻辑）**  
```cpp  
#include <cstdio>  
#include <cstring>  
#define mod 1000000007  
char s[100005], t[100005];  
int n, m, p[100005], s_flag[100005], d[100005], dp[100005], f[100005], ss[100005];  

void preprocess() {  
    // KMP 预处理匹配位置  
    int j = 0;  
    for (int i = 2; i <= m; i++) {  
        while (j && t[j+1] != t[i]) j = p[j];  
        if (t[j+1] == t[i]) j++;  
        p[i] = j;  
    }  
    j = 0;  
    for (int i = 1; i <= n; i++) {  
        while (j && t[j+1] != s[i]) j = p[j];  
        if (t[j+1] == s[i]) j++;  
        if (j == m) s_flag[i] = 1, j = p[j];  
    }  
    // 计算 d[i]  
    for (int i = 1; i <= n; i++)  
        d[i] = s_flag[i] ? (i - m + 1) : d[i-1];  
}  

int main() {  
    scanf("%s%s", s+1, t+1);  
    n = strlen(s+1), m = strlen(t+1);  
    preprocess();  
    dp[0] = 1; f[0] = 1;  
    for (int i = 1; i <= n; i++) {  
        if (d[i]) {  
            dp[i] = (1LL * d[i] * f[d[i]-1] - ss[d[i]-1] + mod) % mod;  
        }  
        f[i] = (f[i-1] + dp[i]) % mod;  
        ss[i] = (ss[i-1] + 1LL * dp[i] * i) % mod;  
    }  
    printf("%d\n", (f[n] - 1 + mod) % mod);  
    return 0;  
}  
```  

---

## **可视化方案（伪代码）**  
```javascript  
// 初始化 Canvas 和音效  
const canvas = initCanvas();  
const beep = loadSound('8bit-beep.wav');  
let i = 0, d = [], dp = [], f = [1], ss = [0];  

function animateStep() {  
    if (i > n) return;  
    // 高亮当前字符 i 和 d[i]  
    highlightChar(i, 'green');  
    highlightRange(1, d[i], 'blue');  
    // 计算 dp[i]  
    if (d[i] > 0) {  
        dp[i] = (d[i] * f[d[i]-1] - ss[d[i]-1]) % mod;  
        playSound(beep);  
    }  
    // 更新前缀和  
    f[i] = f[i-1] + dp[i];  
    ss[i] = ss[i-1] + i * dp[i];  
    // 绘制数值变化  
    drawArray('dp', dp);  
    drawArray('f', f);  
    i++;  
    requestAnimationFrame(animateStep);  
}  
```

---
处理用时：95.27秒