# 题目信息

# Tokitsukaze and Good 01-String (hard version)

## 题目描述

This is the hard version of the problem. The only difference between the two versions is that the harder version asks additionally for a minimum number of subsegments.

Tokitsukaze has a binary string $ s $ of length $ n $ , consisting only of zeros and ones, $ n $ is even.

Now Tokitsukaze divides $ s $ into the minimum number of contiguous subsegments, and for each subsegment, all bits in each subsegment are the same. After that, $ s $ is considered good if the lengths of all subsegments are even.

For example, if $ s $ is "11001111", it will be divided into "11", "00" and "1111". Their lengths are $ 2 $ , $ 2 $ , $ 4 $ respectively, which are all even numbers, so "11001111" is good. Another example, if $ s $ is "1110011000", it will be divided into "111", "00", "11" and "000", and their lengths are $ 3 $ , $ 2 $ , $ 2 $ , $ 3 $ . Obviously, "1110011000" is not good.

Tokitsukaze wants to make $ s $ good by changing the values of some positions in $ s $ . Specifically, she can perform the operation any number of times: change the value of $ s_i $ to '0' or '1' ( $ 1 \leq i \leq n $ ). Can you tell her the minimum number of operations to make $ s $ good? Meanwhile, she also wants to know the minimum number of subsegments that $ s $ can be divided into among all solutions with the minimum number of operations.

## 说明/提示

In the first test case, one of the ways to make $ s $ good is the following.

Change $ s_3 $ , $ s_6 $ and $ s_7 $ to '0', after that $ s $ becomes "1100000000", it can be divided into "11" and "00000000", which lengths are $ 2 $ and $ 8 $ respectively, the number of subsegments of it is $ 2 $ . There are other ways to operate $ 3 $ times to make $ s $ good, such as "1111110000", "1100001100", "1111001100", the number of subsegments of them are $ 2 $ , $ 4 $ , $ 4 $ respectively. It's easy to find that the minimum number of subsegments among all solutions with the minimum number of operations is $ 2 $ .

In the second, third and fourth test cases, $ s $ is good initially, so no operation is required.

## 样例 #1

### 输入

```
5
10
1110011000
8
11001111
2
00
2
11
6
100110```

### 输出

```
3 2
0 3
0 1
0 1
3 1```

# AI分析结果



### 综合分析与结论

**题目核心**：将二进制字符串分割为若干偶数长度的连续子段，求最少修改次数及对应的最少子段数。  
**关键难点**：在保证最少操作次数的同时，动态调整颜色选择以最小化分割段数。

**贪心策略**：
1. **第一问**：统计每两个字符不同的组数（必须修改）。
2. **第二问**：基于无需修改的相邻同色组，统计其颜色变化次数（去重相邻重复颜色后的数目），若无则设为1。

**可视化设计**：
- **像素风格**：以8位像素块表示每两个字符的组，绿色表示无需修改，红色表示需修改。
- **动态合并**：修改后的块颜色自动与相邻段同色，动画显示段合并效果。
- **音效提示**：修改时播放“滴”声，段合并时播放“叮”声，错误操作触发短促警报音。
- **AI演示**：自动按最优策略修改并合并，用户可单步观察决策过程。

---

### 题解清单（≥4星）

1. **jasonliujiahua（4星）**  
   **亮点**：简洁高效，直接统计每对字符的差异，通过颜色序列去重处理段数。  
   **代码可读性**：高，逻辑清晰。

2. **Tx_Lcy（4星）**  
   **亮点**：提供贪心和DP两种解法，贪心法动态调整颜色选择，DP法状态转移明确。  
   **代码可读性**：中等，适合进阶学习。

3. **tallnut（4星）**  
   **亮点**：使用`vector`存储同色组，去重后直接计数，逻辑直观。  
   **代码可读性**：高，适合快速实现。

---

### 最优思路提炼

**核心贪心逻辑**：
```cpp
int ans1 = 0, ans2 = 1;
vector<int> colors;
for (int i = 0; i < n; i += 2) {
    if (s[i] != s[i+1]) ans1++; // 第一问
    else colors.push_back(s[i] - '0'); // 记录同色组颜色
}
// 去重相邻重复颜色，统计段数
for (int i = 1; i < colors.size(); ++i) {
    if (colors[i] != colors[i-1]) ans2++;
}
if (colors.empty()) ans2 = 1; // 特判全修改情况
```

---

### 同类型题与算法套路

**常见套路**：  
- **分段处理**：将序列拆分为固定长度的块（如每两位）。  
- **颜色合并**：动态调整颜色以最小化相邻差异（如区间染色问题）。  

**推荐题目**：  
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)（贪心选择最小代价）  
2. [P1233 木棍加工](https://www.luogu.com.cn/problem/P1233)（贪心排序后处理）  
3. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)（贪心删除策略）  

---

### 个人心得摘录

- **顿悟**：原问题可转化为对每两个字符的独立处理，无需考虑跨组影响。  
- **调试教训**：全修改情况需特判段数为1，而非直接取`vector`长度。  

---

### 可视化与算法演示

**核心动画逻辑**：
1. **初始分块**：将字符串显示为像素块，红/绿色标识需修改/无需修改的组。  
2. **修改过程**：点击红色块切换颜色，自动合并相邻同色段，实时更新操作次数和段数。  
3. **自动模式**：AI按最优策略逐步修改，高亮当前决策块，显示合并后的颜色流向。  

**复古游戏化设计**：
- **像素绘制**：使用Canvas绘制16x16像素块，复古调色板（#00FF00绿、#FF0000红）。  
- **音效触发**：修改时播放8-bit“滴”声，段合并时播放“叮”声，错误操作触发警报音。  
- **积分系统**：每正确合并一段得10分，连击额外加分，错误操作扣分。

```html
<!-- 示例：Canvas绘制像素块 -->
<canvas id="pixelCanvas"></canvas>
<script>
function drawBlock(ctx, x, y, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x * 20, y * 20, 18, 18);
}
// 初始化与动画循环略...
</script>
```

---

### 代码实现（贪心解法）

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; string s;
        cin >> n >> s;
        int ops = 0, segments = 0;
        vector<int> colors;
        
        for (int i = 0; i < n; i += 2) {
            if (s[i] != s[i+1]) ops++;
            else colors.push_back(s[i] - '0');
        }
        
        if (colors.empty()) segments = 1;
        else {
            segments = 1;
            for (int i = 1; i < colors.size(); ++i) {
                if (colors[i] != colors[i-1]) segments++;
            }
        }
        cout << ops << " " << segments << endl;
    }
    return 0;
}
```

**代码解释**：  
- 遍历每对字符，统计操作次数和同色组颜色。  
- 去重相邻颜色计算段数，全修改时强制段数为1。

---
处理用时：126.59秒