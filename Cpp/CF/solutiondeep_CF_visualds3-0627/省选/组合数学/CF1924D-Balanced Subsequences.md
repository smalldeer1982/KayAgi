# 题目信息

# Balanced Subsequences

## 题目描述

A sequence of brackets is called balanced if one can turn it into a valid math expression by adding characters '+' and '1'. For example, sequences '(())()', '()', and '(()(()))' are balanced, while ')(', '(()', and '(()))(' are not.

A subsequence is a sequence that can be derived from the given sequence by deleting zero or more elements without changing the order of the remaining elements.

You are given three integers $ n $ , $ m $ and $ k $ . Find the number of sequences consisting of $ n $ '(' and $ m $ ')', such that the longest balanced subsequence is of length $ 2 \cdot k $ . Since the answer can be large calculate it modulo $ 1\,000\,000\,007 $ ( $ 10^9 + 7 $ ).

## 说明/提示

For the first test case "()()", "(())" are the $ 2 $ sequences

For the second test case no sequence is possible.

For the third test case ")((()", ")(()(", ")()((", "())((" are the $ 4 $ sequences.

## 样例 #1

### 输入

```
3
2 2 2
3 2 3
3 2 1```

### 输出

```
2
0
4```

# AI分析结果



---

## 唯一算法分类  
**组合数学（卡特兰数变形与反射原理）**

---

## 综合分析与结论  

### 核心思路与解决难点  
所有题解的核心都基于以下观察：  
1. **最长平衡子序列与折线模型**：将括号序列转化为从 (0,0) 到 (n+m,n-m) 的折线，左括号对应向上移动，右括号对应向下移动。最长平衡子序列长度 2k 等价于折线最低点纵坐标为 k-m。  
2. **反射原理与容斥**：利用路径反射技术，将最低点限制转化为组合数差。答案为 $\binom{n+m}{k} - \binom{n+m}{k-1}$，即所有最低点不超过 k-m 的路径数减去最低点不超过 (k-1)-m 的路径数。  
3. **边界处理**：当 k > min(n,m) 时无解，直接返回 0。

### 可视化设计思路  
1. **折线路径动画**：  
   - **路径绘制**：用像素风格绘制从 (0,0) 到 (n+m,n-m) 的折线，红色表示左括号，蓝色表示右括号。  
   - **最低点高亮**：当折线触达 y=k-m 时，触发黄色闪光特效，并播放“滴”音效。  
   - **反射过程**：点击按钮后，将最后一次触达 y=k-m 后的路径关于该直线反射，用虚线显示新路径，终点变为 (n+m,2k-n-m)。  
2. **交互控制**：  
   - **步进模式**：允许逐字符添加括号，观察折线变化。  
   - **参数调节**：拖动滑块调整 n/m/k，实时更新路径与答案。  
3. **复古像素风格**：  
   - **8位音效**：路径触碰边界时播放 8-bit 音效，成功计算答案时播放经典 FC 过关音效。  
   - **网格背景**：Canvas 绘制 16x16 像素网格，路径用 2x2 像素方块表示。

---

## 题解清单 (≥4星)  

### 1. UnyieldingTrilobite（★★★★★）  
- **关键亮点**：  
  - 直接给出反射原理的数学推导，代码简洁（仅需组合数差）。  
  - 正确性证明清晰，引用卡特兰数变形模型。  
- **代码片段**：  
  ```cpp
  cout << (C(n + m, k) - C(n + m, k - 1)).val() << '\n';
  ```

### 2. OrezTsim（★★★★☆）  
- **关键亮点**：  
  - 预处理组合数模板，代码可读性高。  
  - 明确边界条件判断，适合快速实现。  
- **代码片段**：  
  ```cpp
  if(k>n||k>m) return cout<<"0\n",void();
  cout<<Mod(C[n+m][k],P-C[n+m][k-1])<<"\n";
  ```

### 3. EthanOI（★★★★☆）  
- **关键亮点**：  
  - 用赌徒模型生动解释路径意义，辅助理解。  
  - 详细注释双射构造过程，适合数学背景较弱者。  
- **个人心得**：  
  > “希望这次能过了” 体现调试时的忐忑，增强真实感。

---

## 最优思路与代码实现  

### 核心代码（Python 反射原理实现）  
```python
MOD = 10**9+7
max_n = 4000
C = [[0]*(max_n+1) for _ in range(max_n+1)]
for i in range(max_n+1):
    C[i][0] = 1
    for j in range(1, i+1):
        C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD

def solve(n, m, k):
    if k > min(n, m):
        return 0
    return (C[n+m][k] - C[n+m][k-1]) % MOD
```

### 关键技巧  
1. **预处理组合数**：O(n²) 预计算所有组合数，实现 O(1) 查询。  
2. **容斥公式**：用 $\binom{n+m}{k} - \binom{n+m}{k-1}$ 直接计算严格最低点。  

---

## 同类型题与算法套路  

### 类似问题特征  
- **路径限制问题**：如不穿过某条直线、不触碰边界等。  
- **卡特兰数变形**：合法括号序列计数、栈操作序列计数。  

### 推荐题目  
1. **P1641 [SCOI2010] 生成字符串**（组合数容斥）  
2. **P3200 [HNOI2009] 有趣的数列**（卡特兰数应用）  
3. **P1869 [蓝桥杯 2017 国 AC] 括号序列**（最长合法子序列变种）  

---

## 可视化与复古游戏化设计  

### Canvas 动画核心逻辑  
```javascript
function drawPath(n, m, k) {
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  let x = 0, y = 0;
  let minY = 0;
  for (let i = 0; i < n + m; i++) {
    // 模拟路径生成，红色方块为左括号，蓝色为右括号
    if (i < n) { y++; ctx.fillStyle = '#FF0000'; } 
    else { y--; ctx.fillStyle = '#0000FF'; }
    ctx.fillRect(x * 16, (canvas.height - y * 16), 16, 16);
    x++;
    if (y < minY) minY = y;
  }
  // 高亮最低点
  if (minY === k - m) {
    ctx.fillStyle = '#FFFF00';
    ctx.fillRect((x-1)*16, (canvas.height - minY*16), 16, 16);
    playSound('success'); // 触发音效
  }
}
```

### 复古音效设计  
- **路径触碰最低点**：8-bit “滴”声（Web Audio 合成方波）。  
- **答案正确**：FC 马里奥吃到金币音效（预设音频文件）。  

---

## 个人心得摘录  
> “场上看到这玩意直接傻了。不止在一个地方见过这个形式。” —— 体现对经典模型的敏感度，强调反射原理的普适性。

---
处理用时：71.51秒