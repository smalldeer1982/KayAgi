# 题目信息

# Multiple Lamps

## 题目描述

[Kid2Will - Fire Aura](https://soundcloud.com/xgp/kid2will-fire-aura)

⠀



You have $ n $ lamps, numbered from $ 1 $ to $ n $ . Initially, all the lamps are turned off.

You also have $ n $ buttons. The $ i $ -th button toggles all the lamps whose index is a multiple of $ i $ . When a lamp is toggled, if it was off it turns on, and if it was on it turns off.

You have to press some buttons according to the following rules.

- You have to press at least one button.
- You cannot press the same button multiple times.
- You are given $ m $ pairs $ (u_i, v_i) $ . If you press the button $ u_i $ , you also have to press the button $ v_i $ (at any moment, not necessarily after pressing the button $ u_i $ ). Note that, if you press the button $ v_i $ , you don't need to press the button $ u_i $ .

You don't want to waste too much electricity. Find a way to press buttons such that at the end at most $ \lfloor n/5 \rfloor $ lamps are on, or print $ -1 $ if it is impossible.

## 说明/提示

In the first test case, you need to turn at most $ \lfloor 4/5 \rfloor $ lamps on, which means that no lamp can be turned on. You can show that no choice of at least one button turns $ 0 $ lamps on.

In the second test case, you can press buttons $ 3 $ , $ 5 $ , $ 1 $ , $ 2 $ .

- Initially, all the lamps are off;
- after pressing button $ 3 $ , the lamps whose index is a multiple of $ 3 $ (i.e., $ 3 $ ) are toggled, so lamp $ 3 $ is turned on;
- after pressing button $ 5 $ , the lamps whose index is a multiple of $ 5 $ (i.e., $ 5 $ ) are toggled, so lamps $ 3 $ , $ 5 $ are turned on;
- after pressing button $ 1 $ , the lamps whose index is a multiple of $ 1 $ (i.e., $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ ) are toggled, so lamps $ 1 $ , $ 2 $ , $ 4 $ are turned on;
- after pressing button $ 2 $ , the lamps whose index is a multiple of $ 2 $ (i.e., $ 2 $ , $ 4 $ ) are toggled, so lamp $ 1 $ is turned on.

This is valid because

- you pressed at least one button;
- you pressed all the buttons at most once;
- you pressed button $ u_2 = 5 $ , which means that you had to also press button $ v_2 = 1 $ : in fact, button $ 1 $ has been pressed;
- at the end, only lamp $ 1 $ is on.

In the third test case, pressing the buttons $ 8 $ , $ 9 $ , $ 10 $ turns only the lamps $ 8 $ , $ 9 $ , $ 10 $ on.

## 样例 #1

### 输入

```
4
4 0
5 2
4 1
5 1
15 9
7 8
8 9
9 10
10 9
11 1
12 2
13 3
14 4
15 5
5 4
1 2
2 3
3 4
4 5```

### 输出

```
-1
4
3 5 1 2
3
8 9 10
1
5```

# AI分析结果



**唯一算法分类**  
预处理与暴力枚举

---

### **题解思路、算法要点与解决难点**  
**核心思路**  
1. **n≥20时的特殊处理**：按下所有按钮，此时亮灯数为平方数个数，满足⌊n/5⌋要求。  
2. **n≤19的暴力预处理**：枚举所有可能的按钮组合，筛选出亮灯数符合要求的组合，存储备用。  
3. **约束条件检查**：对每个测试用例，遍历预存组合，检查是否满足所有(u,v)依赖关系。  

**算法要点**  
- **位运算优化**：用二进制位表示按钮状态，快速计算亮灯数与约束条件。  
- **预处理剪枝**：提前计算并存储所有合法的按钮组合，减少实时计算量。  
- **约束传递**：若按下u则必须按下v，转化为位掩码的逻辑检查。  

**解决难点**  
1. **亮灯数限制的高效计算**：通过位运算模拟按钮操作，快速筛选合法状态。  
2. **依赖关系的快速验证**：利用位掩码检查(u,v)是否成对出现。  

---

### **题解评分 (≥4星)**  
1. **igAC (5星)**  
   - 思路清晰，预处理合法状态，位运算高效。  
   - 代码简洁，利用`__builtin_popcount`优化亮灯数计算。  
   - 预处理与约束检查分离，实践性强。  

2. **sunkuangzheng (4星)**  
   - 逆向思维：枚举亮灯状态，反推按钮操作。  
   - 剪枝优化，仅枚举最多3盏亮灯的组合。  

3. **naroto2022 (4星)**  
   - 预处理与约束检查分离，逻辑清晰。  
   - 代码注释详细，适合教学。  

---

### **最优思路或技巧提炼**  
1. **平方数性质的应用**：n≥20时，亮灯数为√n，直接输出所有按钮。  
2. **位运算加速**：用二进制位表示按钮状态，快速计算亮灯变化。  
3. **预处理合法状态**：针对小规模n，提前存储所有可能解，减少重复计算。  

---

### **同类型题或类似算法套路**  
- **开关问题**：如[CF1003E](https://codeforces.com/problemset/problem/1003/E)，需枚举操作并验证约束。  
- **依赖约束的枚举**：如[洛谷P2622](https://www.luogu.com.cn/problem/P2622)，利用预处理筛选合法状态。  

---

### **推荐相似知识点题目**  
1. [P1461 海明码](https://www.luogu.com.cn/problem/P1461)  
2. [CF1097B Petr and a Combination Lock](https://codeforces.com/problemset/problem/1097/B)  
3. [P2119 魔法阵](https://www.luogu.com.cn/problem/P2119)  

---

### **个人心得摘录**  
- **预处理的重要性**：小规模数据暴力枚举预处理是解决复杂约束问题的有效手段。  
- **位运算的妙用**：将状态压缩为二进制，显著提升计算效率。  

---

### **可视化与算法演示**  
**核心算法流程**  
1. **按钮操作模拟**：  
   - **颜色标记**：当前按下的按钮（红色），受影响的灯（黄色→绿色/灰色）。  
   - **步进控制**：单步执行按钮操作，展示亮灯变化。  
2. **约束检查**：  
   - **高亮依赖对**：若u按下但v未按下，显示红色警示框。  

**复古游戏化动画效果**  
- **像素风格**：  
  - 按钮为8×8像素块，灯为圆形像素点。  
  - 按下按钮时播放“哔”音效，成功时播放“胜利”音效。  
- **自动演示模式**：  
  - AI自动遍历预存按钮组合，找到第一个合法解后停止。  
  - 显示当前检查的组合编号与剩余可能性。  

**关键代码片段（Canvas动画）**  
```javascript
// 伪代码：绘制按钮与灯状态
function drawState(buttons, lamps) {
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  buttons.forEach((btn, i) => {
    ctx.fillStyle = btn.pressed ? "#FF5555" : "#AAAAAA";
    ctx.fillRect(i * 20, 50, 16, 16); // 绘制按钮
  });
  lamps.forEach((lamp, i) => {
    ctx.fillStyle = lamp.on ? "#55FF55" : "#555555";
    ctx.beginPath();
    ctx.arc(i * 20 + 8, 100, 6, 0, Math.PI * 2);
    ctx.fill();
  });
}
```

---

**总结**  
通过预处理合法状态与位运算优化，结合约束条件验证，高效解决了大规模n与小规模n的不同场景。可视化设计通过复古像素动画与音效，直观展示算法流程与关键状态变化。

---
处理用时：89.73秒