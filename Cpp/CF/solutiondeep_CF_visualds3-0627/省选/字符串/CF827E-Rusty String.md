# 题目信息

# Rusty String

## 题目描述

Grigory loves strings. Recently he found a metal strip on a loft. The strip had length $ n $ and consisted of letters "V" and "K". Unfortunately, rust has eaten some of the letters so that it's now impossible to understand which letter was written.

Grigory couldn't understand for a long time what these letters remind him of, so he became interested in the following question: if we put a letter "V" or "K" on each unreadable position, which values can the period of the resulting string be equal to?

A period of a string is such an integer $ d $ from $ 1 $ to the length of the string that if we put the string shifted by $ d $ positions to the right on itself, then all overlapping letters coincide. For example, $ 3 $ and $ 5 $ are periods of "VKKVK".

## 说明/提示

In the first test case from example we can obtain, for example, "VKKVK", which has periods $ 3 $ and $ 5 $ .

In the second test case we can obtain "VVVVVV" which has all periods from $ 1 $ to $ 6 $ .

In the third test case string "KVKV" has periods $ 2 $ and $ 4 $ , and string "KVKK" has periods $ 3 $ and $ 4 $ .

## 样例 #1

### 输入

```
3
 
5
V??VK
 
6
??????
 
4
?VK?
```

### 输出

```
2
3 5
6
1 2 3 4 5 6
3
2 3 4
```

# AI分析结果



---

## **算法分类**
**FFT/NTT 字符串匹配**

---

## **题解思路与核心难点**

### **核心思路**
1. **问题转化**：将周期判断转化为字符串匹配问题，使用FFT/NTT高效计算可能匹配的位置。
2. **多项式建模**：将字符映射为多项式系数（如 `V→1`, `K→2`, `?→0`），构造三次多项式卷积以检测冲突。
3. **因数筛除**：对候选周期进行因数遍历，排除因 `?` 替换不一致导致的非法周期。

### **关键步骤**
1. **字符映射与多项式构造**：
   - 对原字符串和翻转后的字符串分别构造多项式。
   - 计算三次多项式卷积：$a^3b + ab^3 - 2a^2b^2$，通过FFT/NTT加速。
2. **候选周期筛选**：
   - 若卷积结果为0，说明该位移可能为合法周期。
3. **因数合法性检查**：
   - 若某周期的因数存在非法情况，则自身也非法。

### **解决难点**
- **通配符与未知符差异**：`?` 需统一替换为同一字符，而非通配符的任意匹配。
- **高效因数检查**：通过遍历因数排除非法候选，避免暴力枚举。

---

## **题解评分 (≥4星)**
1. **tzc_wk (5星)**  
   - **亮点**：完整推导三次多项式卷积，引入因数筛除优化，代码清晰。
2. **shadowice1984 (4星)**  
   - **亮点**：分离处理V/K的卷积，逻辑简洁，NTT实现高效。
3. **辰星凌 (4星)**  
   - **亮点**：详细注释与代码分块，适合教学，多次NTT优化。

---

## **最优思路与技巧**
1. **三次多项式卷积**：通过展开 $(a-b)^2ab$ 捕捉冲突，避免直接比较字符。
2. **因数筛除优化**：  
   ```cpp
   for(int j=2*i; j<=n; j+=i) 
       if(非法[j]) 非法[i] = true;
   ```
3. **字符映射简化**：`V→1, K→2, ?→0`，避免复杂分支判断。

---

## **同类题目推荐**
1. **P4173**：带通配符的字符串匹配，FFT经典应用。
2. **CF528D**：模糊字符串匹配，扩展字符集处理。
3. **P3723**：字符串循环移位匹配，FFT优化。

---

## **可视化与算法演示**
### **核心步骤动画**
1. **字符转换与多项式构造**  
   - **颜色标记**：`V`（红色）、`K`（蓝色）、`?`（灰色），展示多项式系数映射。
2. **FFT卷积计算**  
   - **动画效果**：多项式逐项相乘，FFT变换后高亮非零项，标识冲突位置。
3. **因数筛除过程**  
   - **网格遍历**：每个候选周期用方块表示，非法因数路径标红，合法路径标绿。

### **复古像素风格设计**
- **Canvas 绘制**：  
  ```javascript
  // 伪代码：绘制候选周期方块
  ctx.fillStyle = '#8B8BEF'; // 合法周期色
  if (非法[d]) ctx.fillStyle = '#FF5555'; // 非法色
  ctx.fillRect(x, y, 16, 16);
  ```
- **音效触发**：  
  - **合法周期**：8-bit 成功音效（上升音阶）。
  - **非法周期**：短促“错误”音效。

### **交互演示**
- **步进控制**：拖动滑块调整FFT计算速度。
- **自动模式**：AI自动执行卷积与筛除，类似“贪吃蛇”路径展示。

---

## **代码实现（核心片段）**
```cpp
// 三次多项式卷积计算（tzc_wk）
for (int i=0; i<len; i++) {
    a[i] = comp(pt1[i]*pt1[i]*pt1[i], 0);
    b[i] = comp(pt2[i], 0);
}
FFT(a,1); FFT(b,1);
for (int i=0; i<len; i++) p[i] = a[i] * b[i];
// 合并其他项（ab³ - 2a²b²）
```

---

## **总结**
通过FFT/NTT高效计算字符串冲突，结合因数筛除优化，准确处理 `?` 替换的约束。可视化设计通过像素动画与音效增强理解，适合教学与交互学习。

---
处理用时：68.20秒