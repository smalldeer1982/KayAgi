# 题目信息

# Phone Numbers

## 题目描述

And where the are the phone numbers?

You are given a string $ s $ consisting of lowercase English letters and an integer $ k $ . Find the lexicographically smallest string $ t $ of length $ k $ , such that its set of letters is a subset of the set of letters of $ s $ and $ s $ is lexicographically smaller than $ t $ .

It's guaranteed that the answer exists.

Note that the set of letters is a set, not a multiset. For example, the set of letters of abadaba is $ {a,b,d} $ .

String $ p $ is lexicographically smaller than string $ q $ , if $ p $ is a prefix of $ q $ , is not equal to $ q $ or there exists $ i $ , such that $ p_{i}<q_{i} $ and for all $ j<i $ it is satisfied that $ p_{j}=q_{j} $ . For example, abc is lexicographically smaller than abcd , abd is lexicographically smaller than abec, afa is not lexicographically smaller than ab and a is not lexicographically smaller than a.

## 说明/提示

In the first example the list of strings $ t $ of length 3, such that the set of letters of $ t $ is a subset of letters of $ s $ is as follows: aaa, aab, aac, aba, abb, abc, aca, acb, $ ... $ . Among them, those are lexicographically greater than abc: aca, acb, $ ... $ . Out of those the lexicographically smallest is aca.

## 样例 #1

### 输入

```
3 3
abc
```

### 输出

```
aca
```

## 样例 #2

### 输入

```
3 2
abc
```

### 输出

```
ac
```

## 样例 #3

### 输入

```
3 3
ayy
```

### 输出

```
yaa
```

## 样例 #4

### 输入

```
2 3
ba
```

### 输出

```
baa
```

# AI分析结果



---

**唯一算法分类**  
贪心算法  

---

**综合分析与结论**  

### 核心思路  
1. **分类处理**：根据输入字符串长度 `n` 和目标长度 `k` 的关系分为三种情况：
   - **n < k**：直接补最小字符（保证字典序最小）
   - **n ≥ k**：从后往前找到第一个可替换字符，替换为更大字符，后续补最小字符
2. **贪心策略**：在保证字典序大于原字符串的前提下，每一步选择最小的可行字符。

### 关键难点  
1. **替换位置的确定**：如何找到第一个可以替换的位置，使得替换后的字符串字典序最小。
2. **字符替换逻辑**：在排序后的字符集中快速找到比当前字符大的最小字符。

### 可视化设计要点  
- **动画流程**：  
  - **初始化**：将原字符串 `s` 显示为像素方块，每个字符对应不同颜色。  
  - **替换阶段**：从右向左扫描，高亮当前扫描位置（如红色闪烁），右侧字符显示为灰色。  
  - **候选字符选择**：弹出排序后的字符列表，高亮第一个比当前字符大的选项（绿色框），替换后右侧字符变为最小字符（统一蓝色）。  
- **音效设计**：  
  - **扫描移动**：播放“滴”声。  
  - **成功替换**：播放上扬音调。  
  - **填充最小字符**：连续短促音效。  
- **复古风格**：采用 8-bit 像素字体，背景为深色网格，字符方块使用经典 FC 调色板（红、绿、蓝、黄）。

---

**题解清单 (≥4星)**  

1. **yaolibo (5星)**  
   - **亮点**：分类清晰，代码结构化，覆盖所有边界情况（如样例4中 `n=2, k=3`）。  
   - **关键代码**：  
     ```cpp
     for (i = k; i >= 1; i--) { // 从后往前扫描
         for (j = 1; j <= n; j++) 
             if (t[j] <= s[i]) break;
         if (j != 1) { // 找到可替换字符
             s[i] = t[j-1]; 
             break;
         }
     }
     ```

2. **codeLJH114514 (4星)**  
   - **亮点**：利用 `upper_bound` 快速查找替换字符，代码简洁。  
   - **关键代码**：  
     ```cpp
     sort(r.begin(), r.end());
     s[i] = *upper_bound(r.begin(), r.end(), s[i]);
     for (int j = i + 1; j < k; j++) s[j] = mi;
     ```

3. **封禁用户 (4星)**  
   - **亮点**：通过后缀和判断后续字符是否全为最大值，避免无效替换。  
   - **关键代码**：  
     ```cpp
     if (b[i+1] == k-i) { // 后续字符全为最大值
         printf("%c", *s.upper_bound(c[i]-'a')+'a');
         for (j=i+1; j<=k; j++) printf("%c", mi+'a');
     }
     ```

---

**最优思路或技巧提炼**  
1. **字符排序预处理**：将原字符串字符排序（从大到小），便于快速查找替换字符。  
2. **逆向扫描替换**：从后往前找到第一个可替换位置，确保字典序增量最小。  
3. **最小字符填充**：替换位置后的所有字符填充为最小字符，保证整体字典序最小。  

---

**同类型题或类似算法套路**  
- **Next Permutation**：通过修改部分字符生成字典序更大的最小字符串。  
- **Lexicographical Order**：处理字典序相关的构造问题，常见于字符串排序和生成。  

---

**推荐题目**  
1. [CF 977F - Consecutive Subsequence](https://codeforces.com/problemset/problem/977/F)  
2. [LeetCode 31 - Next Permutation](https://leetcode.com/problems/next-permutation/)  
3. [洛谷 P1090 - 合并果子](https://www.luogu.com.cn/problem/P1090)  

---

**个人心得摘录**  
- **调试教训**：处理 `n = k` 时，需确保替换后的后续字符全部置为最小，否则会漏掉更优解（如样例1中的 `aca` 而非 `acc`）。  
- **优化顿悟**：排序预处理可大幅减少字符查找的时间复杂度。  

---

**可视化与算法演示**  
```javascript
// 伪代码示例：Canvas 绘制贪心替换过程
function drawStep(pos, replacedChar, minChar) {
    ctx.fillStyle = "#000"; // 黑色背景
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    // 绘制原字符串
    for (let i = 0; i < s.length; i++) {
        ctx.fillStyle = (i === pos) ? "#FF0000" : "#FFFFFF"; // 高亮替换位置
        ctx.fillText(s[i], i * 16, 32);
    }
    // 替换后绘制
    if (replacedChar) {
        ctx.fillStyle = "#00FF00"; // 绿色表示替换字符
        ctx.fillText(replacedChar, pos * 16, 32);
        // 填充最小字符
        for (let i = pos + 1; i < k; i++) {
            ctx.fillStyle = "#0000FF"; // 蓝色
            ctx.fillText(minChar, i * 16, 32);
        }
    }
}
```

---

**完整代码参考**  
```cpp
// yaolibo 的完整代码（核心逻辑）
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
char s[N], t[N];
int n, k;

int main() {
    scanf("%d%d%s", &n, &k, s + 1);
    for (int i = 1; i <= n; i++) t[i] = s[i];
    sort(t + 1, t + 1 + n, greater<char>());
    
    if (n < k) {
        printf("%s", s + 1);
        for (int i = n + 1; i <= k; i++) putchar(t[n]);
    } else {
        int pos = 0;
        for (int i = k; i >= 1; i--) {
            int j = 1;
            while (j <= n && t[j] > s[i]) j++;
            if (j != 1) {
                s[i] = t[j-1];
                pos = i;
                break;
            }
        }
        for (int i = 1; i <= pos; i++) putchar(s[i]);
        for (int i = pos + 1; i <= k; i++) putchar(t[n]);
    }
    return 0;
}
```

---
处理用时：89.37秒