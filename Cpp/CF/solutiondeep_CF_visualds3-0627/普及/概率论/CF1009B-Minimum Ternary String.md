# 题目信息

# Minimum Ternary String

## 题目描述

给定一个由 '0', '1', '2' 组成的字符串  $S$ 。可以交换相邻'0', '1'或'1', '2'的位置（例如：'12' - '21'  $\;$  '01' - '10'）请输出原字符串经过任意转换后字典序最小的字符串。原字符串长度不超过  $10^5$ 。

## 样例 #1

### 输入

```
100210
```

### 输出

```
001120
```

## 样例 #2

### 输入

```
11222121
```

### 输出

```
11112222
```

## 样例 #3

### 输入

```
20
```

### 输出

```
20
```

# AI分析结果



**唯一算法分类**  
贪心算法  

---

**综合分析与结论**  
本题的核心在于利用字符交换规则，将可自由移动的 '1' 放置到最优位置。由于 '0' 和 '2' 的相对顺序无法改变，解题思路为：  
1. 提取所有非 '1' 字符，保留其原始顺序。  
2. 找到第一个 '2' 的位置，将所有 '1' 插入其前方；若无 '2'，'1' 放在所有字符末尾。  

**可视化设计思路**  
1. **动画演示**：  
   - 初始字符串分解为两个部分：静态的 `0/2` 序列和动态的 `1` 集合。  
   - 高亮第一个 `2` 的位置，动态将所有 `1` 移动到此处。  
   - 若没有 `2`，`1` 移动到末尾。  
2. **像素风格**：  
   - 用绿色表示 `0`，黄色表示 `1`，红色表示 `2`。  
   - 关键操作时触发 8-bit 音效（如移动时的短促音效，完成时的成功音效）。  
3. **交互控制**：  
   - 步进按钮观察 `1` 的移动过程，速度调节控制动画节奏。  

---

**题解清单 (≥4星)**  
1. **Fearliciz (5星)**  
   - **亮点**：直接遍历原字符串，实时构造结果，避免插入操作，时间复杂度 O(n)。  
   - **代码简洁性**：仅需一次遍历和条件判断，逻辑清晰。  

2. **小闸蟹 (4星)**  
   - **亮点**：通过统计 `0` 和 `2` 的数量分情况处理，代码结构清晰。  
   - **可读性**：明确特判无 `2` 的情况，注释详细。  

3. **HPXXZYY (4星)**  
   - **亮点**：使用 STL 函数 `find` 和 `insert`，代码简短。  
   - **优化点**：避免显式构造中间字符串，直接输出结果。  

---

**最优思路或技巧提炼**  
1. **贪心核心**：利用 `1` 可自由移动的特性，将其集中在第一个 `2` 前。  
2. **高效构造结果**：直接拼接字符串各部分（如先输出 `0` 序列，再插入 `1`，最后处理剩余字符），避免高复杂度的插入操作。  

---

**同类型题或类似算法套路**  
- **交换限制下的字典序优化**：如 [LeetCode 670. Maximum Swap](https://leetcode.com/problems/maximum-swap/)，通过分析可交换的字符范围，贪心选择最优位置。  
- **字符分组处理**：如将可移动字符分离后重新插入，类似 [CF 1430E. String Reversal](https://codeforces.com/problemset/problem/1430/E)。  

---

**推荐相似题目**  
1. [CF 1009B. Minimum Ternary String](https://codeforces.com/problemset/problem/1009/B)（本题）  
2. [CF 1430E. String Reversal](https://codeforces.com/problemset/problem/1430/E)（字符逆序与交换限制）  
3. [LeetCode 670. Maximum Swap](https://leetcode.com/problems/maximum-swap/)（单次交换最大化字典序）  

---

**代码实现示例（Fearliciz 的核心逻辑）**  
```cpp
#include<bits/stdc++.h>
using namespace std;
string c; bool flag=1; 
int main() {
    cin>>c; int cnt1=0;
    for(char ch : c) if(ch=='1') cnt1++;
    for(char ch : c) {
        if(ch=='1') continue;
        if(ch=='2' && flag) {
            while(cnt1--) cout<<'1'; // 插入所有 '1'
            cout<<'2'; flag=0;
        } else cout<<ch;
    }
    if(flag) while(cnt1--) cout<<'1'; // 处理无 '2' 的情况
}
```

---

**个人心得摘录**  
- **shurongwang 的教训**：字符串频繁插入导致 O(n²) 时间，需避免在循环中操作容器。  
- **Fearliciz 的优化**：直接遍历输出，无需额外存储，降低空间复杂度。  

---

**可视化与算法演示**  
```javascript
// 伪代码：Canvas 绘制核心逻辑
function drawAnimation(str) {
    let ctx = canvas.getContext('2d');
    let parts = { zeros: [], ones: [], twos: [] };
    // 分解字符串
    for (let c of str) {
        if (c === '1') parts.ones.push(c);
        else if (c === '0') parts.zeros.push(c);
        else parts.twos.push(c);
    }
    // 动态绘制：先画 zeros，找到第一个 two 插入 ones
    let x = 0;
    parts.zeros.concat(parts.twos).forEach((char, i) => {
        if (char === '2' && !firstTwoPos) {
            drawAllOnes(x); // 高亮插入位置
            firstTwoPos = x;
        }
        drawChar(char, x);
        x += CHAR_WIDTH;
    });
    if (!firstTwoPos) drawAllOnes(x); // 无 '2' 的情况
}
```  
- **颜色标记**：`0`（绿）、`1`（黄）、`2`（红），插入位置用闪烁边框高亮。  
- **音效触发**：插入 `1` 时播放“收集金币”音效，完成时播放“胜利”音效。

---
处理用时：153.72秒