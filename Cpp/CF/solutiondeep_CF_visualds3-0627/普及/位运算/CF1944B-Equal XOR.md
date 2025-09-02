# 题目信息

# Equal XOR

## 题目描述

You are given an array $ a $ of length $ 2n $ , consisting of each integer from $ 1 $ to $ n $ exactly twice.

You are also given an integer $ k $ ( $ 1 \leq k \leq \lfloor \frac{n}{2} \rfloor  $ ).

You need to find two arrays $ l $ and $ r $ each of length $ \mathbf{2k} $ such that:

- $ l $ is a subset $ ^\dagger $ of $ [a_1, a_2, \ldots a_n] $
- $ r $ is a subset of $ [a_{n+1}, a_{n+2}, \ldots a_{2n}] $
- [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of elements of $ l $ is equal to the bitwise XOR of elements of $ r $ ; in other words, $ l_1 \oplus l_2 \oplus \ldots \oplus l_{2k} = r_1 \oplus r_2 \oplus \ldots \oplus r_{2k} $

It can be proved that at least one pair of $ l $ and $ r $ always exists. If there are multiple solutions, you may output any one of them.

 $ ^\dagger $ A sequence $ x $ is a subset of a sequence $ y $ if $ x $ can be obtained by deleting several (possibly none or all) elements of $ y $ and rearranging the elements in any order. For example, $ [3,1,2,1] $ , $ [1, 2, 3] $ , $ [1, 1] $ and $ [3, 2] $ are subsets of $ [1, 1, 2, 3] $ but $ [4] $ and $ [2, 2] $ are not subsets of $ [1, 1, 2, 3] $ .

## 说明/提示

In the first test case, we choose $ l=[2,1] $ and $ r=[2,1] $ . $ [2, 1] $ is a subset of $ [a_1, a_2] $ and $ [2, 1] $ is a subset of $ [a_3, a_4] $ , and $ 2 \oplus 1 = 2 \oplus 1 = 3 $ .

In the second test case, $ 6 \oplus 4 = 1 \oplus 3 = 2 $ .

## 样例 #1

### 输入

```
4
2 1
1 2 2 1
6 1
6 4 2 1 2 3 1 6 3 5 5 4
4 1
1 2 3 4 1 2 3 4
6 2
5 1 3 3 5 1 2 6 4 6 4 2```

### 输出

```
2 1
2 1
6 4
1 3
1 2
1 2
5 1 3 3
6 4 2 4```

# AI分析结果



**唯一算法分类**  
构造算法（基于异或性质）

---

**综合分析与结论**  
**核心思路**：  
利用异或的自反性（x^x=0）构造等值异或和。关键步骤：  
1. **处理双次出现数**：在前/后半各选出现两次的数，每对贡献0异或值。  
2. **补充单次出现数**：若数量不足，成对加入两边各出现一次的数，同步影响异或和。  

**难点解决**：  
- **对称构造**：确保两边数量平衡，利用两半出现次数互补的特性（前半出现两次的数数量等于后半的）。  
- **动态填充**：先填满双次数的贡献，剩余用单次数补齐，确保异或和同步变化。  

**可视化设计**：  
- **动画演示**：  
  - **步骤1**：高亮前/后半的成对元素，显示选入数组（绿色），异或和显示为0。  
  - **步骤2**：若未填满，高亮单次元素（黄色），同步加入两边数组，异或和同步变化。  
- **交互功能**：支持步进控制，查看每步选数后的异或和变化。  
- **复古风格**：用8位像素风绘制数组分块，音效提示成对选中（“哔”声）和补充选中（“叮”声）。  

---

**题解清单 (≥4星)**  
1. **jiangchen1234 (5星)**  
   - **亮点**：逻辑清晰，分阶段处理双次数和单次数，代码结构简洁。  
   - **关键代码**：  
     ```cpp  
     // 处理双次数  
     F(i,1,n) if(mp1[a[i]]==2) ans1[len1]=a[i];  
     // 补充单次数  
     F(i,1,n) if(mp1[a[i]]==1) ans1[len1]=ans2[len2]=a[i];  
     ```  
2. **Blikewsr (4星)**  
   - **亮点**：利用数组统计代替map，提升效率，注释详细。  
   - **关键代码**：  
     ```cpp  
     for(int i=1;v[0][i]==2;...); // 填充双次数  
     if(cnt<2k) add_single_pairs(); // 补充单次数  
     ```  
3. **Shadow_T (4星)**  
   - **亮点**：明确分类讨论，直接构造异或序列，逻辑直观。  
   - **关键代码**：  
     ```cpp  
     vector<int> ansa, ansb;  
     if(mp1[i]==2) ansa.push_back(i); // 双次数填充  
     if(mp1[i]==1) ansa.push_back(i); ansb.push_back(i); // 单次同步  
     ```  

---

**最优思路提炼**  
**关键技巧**：  
- **异或归零**：优先选成对相同数，使异或和为0。  
- **对称填充**：单次数成对加入，保证两边异或同步变化。  
- **动态调整**：先填满双次数贡献，剩余用单次数补足。  

**代码实现思想**：  
```cpp  
// 统计前/后半出现次数  
map<int,int> mp1, mp2;  
// 填充双次数  
for (int x : 前半数组) if (mp1[x] == 2) 加入两次到l;  
// 补充单次数  
while (l.size < 2k) 取一个前后各出现一次的数，同步加入l和r;  
```  

---

**同类型题与算法套路**  
- **通用解法**：利用异或性质构造对称解，适用于需要等值操作的场景。  
- **类似题目**：  
  1. CF1365D Solve the Maze（异或路径构造）  
  2. P1469 找筷子（异或找唯一数）  
  3. CF1840C Ski Resort（利用异或性质的最优选择）  

---

**推荐洛谷题目**  
1. P1469 找筷子（异或性质基础）  
2. P1734 最大约数和（异或与约数结合）  
3. CF1879D Sum of XOR Functions（异或前缀和应用）  

---

**个人心得摘录**  
- **调试教训**：未处理单次数奇偶性会导致数组越界（需确保成对加入）。  
- **顿悟点**：发现两半双次数数量对称后，构造过程变得清晰。  

---

**可视化与算法演示**  
**动画方案**：  
1. **分块显示**：Canvas绘制前后半数组，颜色区分双次数（绿）和单次数（黄）。  
2. **操作高亮**：选中元素时闪烁边框，显示当前异或和数值。  
3. **音效触发**：  
   - 成对选中时播放“哔”声（Web Audio模拟8-bit音效）。  
   - 补充单次数时播放“叮”声。  
4. **自动演示**：按步骤执行构造过程，支持暂停/步进。  

**复古风格设计**：  
- **调色板**：16色FC风格，绿（#00FF00）、黄（#FFFF00）、红（#FF0000）。  
- **Canvas绘制**：网格布局，元素用8x8像素块表示，移动时添加残影效果。  

**交互功能**：  
- **速度控制**：滑动条调节动画速度（0.5x~2x）。  
- **关卡模式**：分步完成构造，每步解锁得分（如成对选中+10，补充+5）。  

--- 

**代码片段（复古动画JS）**  
```javascript  
// Canvas绘制示例  
function drawPixel(x, y, color) {  
  ctx.fillStyle = color;  
  ctx.fillRect(x*10, y*10, 8, 8);  
}  
// 播放音效  
function playBeep() {  
  const osc = audioCtx.createOscillator();  
  osc.frequency.setValueAtTime(800, audioCtx.currentTime);  
  osc.connect(audioCtx.destination);  
  osc.start(); osc.stop(0.1);  
}  
```  

通过上述设计，学习者可直观理解构造过程，并在交互中掌握异或性质的应用。

---
处理用时：82.92秒