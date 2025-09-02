# 题目信息

# Bit Flipping

## 题目描述

You are given a binary string of length $ n $ . You have exactly $ k $ moves. In one move, you must select a single bit. The state of all bits except that bit will get flipped ( $ 0 $ becomes $ 1 $ , $ 1 $ becomes $ 0 $ ). You need to output the lexicographically largest string that you can get after using all $ k $ moves. Also, output the number of times you will select each bit. If there are multiple ways to do this, you may output any of them.

A binary string $ a $ is lexicographically larger than a binary string $ b $ of the same length, if and only if the following holds:

- in the first position where $ a $ and $ b $ differ, the string $ a $ contains a $ 1 $ , and the string $ b $ contains a $ 0 $ .

## 说明/提示

Here is the explanation for the first testcase. Each step shows how the binary string changes in a move.

- Choose bit $ 1 $ : $ \color{red}{\underline{1}00001} \rightarrow \color{red}{\underline{1}}\color{blue}{11110} $ .
- Choose bit $ 4 $ : $ \color{red}{111\underline{1}10} \rightarrow \color{blue}{000}\color{red}{\underline{1}}\color{blue}{01} $ .
- Choose bit $ 4 $ : $ \color{red}{000\underline{1}01} \rightarrow \color{blue}{111}\color{red}{\underline{1}}\color{blue}{10} $ .

 The final string is $ 111110 $ and this is the lexicographically largest string we can get.

## 样例 #1

### 输入

```
6
6 3
100001
6 4
100011
6 0
000000
6 1
111001
6 11
101100
6 12
001110```

### 输出

```
111110
1 0 0 2 0 0 
111110
0 1 1 1 0 1 
000000
0 0 0 0 0 0 
100110
1 0 0 0 0 0 
111111
1 2 1 3 0 4 
111110
1 1 4 2 0 4```

# AI分析结果



---

### 综合分析与结论  
**核心贪心策略**：优先将高位变为1，利用奇偶性处理剩余操作次数，剩余操作全放在最后一位。  
**难点**：每次操作影响其他位，需动态维护奇偶性状态。  
**解决方案**：通过预处理k的奇偶性，遍历时根据当前位值和剩余k决定是否操作，剩余次数分配给末尾。  

---

### 题解清单 (4星及以上)  
1. **World_Creater (4.5星)**  
   - **亮点**：预处理奇数k的思路清晰，通过优先翻转第一个1确保高位连续1最多，代码简洁。  
2. **Tx_Lcy (4星)**  
   - **亮点**：动态判断每一位是否需要操作，逻辑严谨，适合不同数据分布。  
3. **Wsy_flying_forever (4星)**  
   - **亮点**：维护`flag`变量跟踪奇偶性状态，实现高效，适合大规模数据。  

---

### 最优思路提炼  
1. **奇偶预处理**：若k为奇数，优先翻转第一个1（或末尾0），使剩余k为偶数。  
2. **高位优先**：从左到右遍历，将0变为1（需剩余k奇偶性满足条件）。  
3. **末尾处理**：剩余操作全放在最后一位，最小化对字典序影响。  

**关键代码片段**（World_Creater版）：
```cpp
if (k&1) {
    // 预处理：翻转第一个1或末尾0
}
for (int i=0; i<n && k>0; i++) {
    if (s[i] == '0' && k%2 == 0) {
        ans[i]++; k--; // 将0变为1
    }
}
ans[n-1] += k; // 剩余操作给末尾
```

---

### 同类型题与算法套路  
- **常见场景**：高位优先贪心（如字典序最大）、奇偶性影响决策、位操作问题。  
- **相似题目**：  
  1. **CF1380C**：贪心选择最小分组。  
  2. **P1090**：合并果子（优先队列贪心）。  
  3. **CF1365D**：矩阵路径存在性（结合贪心与BFS）。  

---

### 推荐洛谷题目  
1. **P1090**（合并果子） - 贪心+优先队列。  
2. **CF1385D**（01字符串分割） - 分治+贪心。  
3. **P2114**（位运算最大值） - 位贪心。  

---

### 个人心得摘录  
- **World_Creater**：*“将两次操作合并为一次，简化问题”* → 奇偶性转换是核心突破口。  
- **Tx_Lcy**：*“必须消耗一次操作保持高位为1”* → 动态决策避免字典序损失。  

---

### 可视化与算法演示设计  
**动画方案**：  
1. **像素风格界面**：  
   - 使用8位像素字体显示二进制字符串，当前处理位高亮为红色，末尾位闪烁提示。  
   - 每次操作后，其他位翻转动画（0→1为绿色闪光，1→0为灰色渐隐）。  
2. **交互逻辑**：  
   - **自动模式**：AI逐步执行贪心选择，速度可调。  
   - **手动模式**：点击任意位触发操作，实时显示k的奇偶性状态。  
3. **音效设计**：  
   - 正确选择高位时播放上升音阶，错误操作（如浪费k）则低沉提示音。  
   - 背景音乐为8位循环旋律，增强复古感。  

**关键JS伪代码**：  
```javascript
function animateStep(bitIndex) {
    highlightBit(bitIndex); // 高亮当前位
    playSound('select');    // 选择音效
    flipOthers();           // 翻转其他位动画
    updateKDisplay();       // 更新剩余k
}
```

---

### 代码实现  
**World_Creater完整代码**：  
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int ans[200005];
int main() {
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k >> s;
        // ...（预处理与贪心逻辑）
        cout << s << "\n";
        for (int i=0; i<n; i++) cout << ans[i] << " ";
    }
}
```

---

**总结**：优先处理高位、奇偶性转换、末尾处理是本题三大核心策略，结合动态奇偶判断与贪心选择，可在O(n)时间高效求解。

---
处理用时：97.59秒