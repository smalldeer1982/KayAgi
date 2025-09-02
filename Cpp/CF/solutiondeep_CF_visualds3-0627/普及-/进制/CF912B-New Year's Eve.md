# 题目信息

# New Year's Eve

## 题目描述

Since Grisha behaved well last year, at New Year's Eve he was visited by Ded Moroz who brought an enormous bag of gifts with him! The bag contains $ n $ sweet candies from the good ol' bakery, each labeled from $ 1 $ to $ n $ corresponding to its tastiness. No two candies have the same tastiness.

The choice of candies has a direct effect on Grisha's happiness. One can assume that he should take the tastiest ones — but no, the holiday magic turns things upside down. It is the xor-sum of tastinesses that matters, not the ordinary sum!

A xor-sum of a sequence of integers $ a_{1},a_{2},...,a_{m} $ is defined as the bitwise XOR of all its elements: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912B/475d3a054d8c211f23a68d652dd85385e5ab9fc9.png), here ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF912B/4298d47c0191af3c0a3103f431751061bc7e2362.png) denotes the bitwise XOR operation; more about bitwise XOR can be found [here.](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)

Ded Moroz warned Grisha he has more houses to visit, so Grisha can take no more than $ k $  candies from the bag. Help Grisha determine the largest xor-sum (largest xor-sum means maximum happiness!) he can obtain.

## 说明/提示

In the first sample case, one optimal answer is $ 1 $ , $ 2 $ and $ 4 $ , giving the xor-sum of $ 7 $ .

In the second sample case, one can, for example, take all six candies and obtain the xor-sum of $ 7 $ .

## 样例 #1

### 输入

```
4 3
```

### 输出

```
7
```

## 样例 #2

### 输入

```
6 6
```

### 输出

```
7
```

# AI分析结果



---

### **唯一算法分类**
位运算

---

### **综合分析与结论**
**题目核心**：在1~n中选最多k个数，使它们的异或和最大。  
**关键结论**：  
- 当`k=1`时，直接选`n`，答案为`n`。  
- 当`k≥2`时，答案总为二进制全1的最大数`S=2^b-1`，其中`b`为`n`的二进制最高位位数。  
**难点解析**：  
1. **位运算性质**：通过异或操作，选两个数可构造全1的二进制数。  
2. **构造方法**：取`n`的最高位`b`，`S=2^b-1`即为可能的最大值。  
3. **可行性证明**：存在两个数`a`和`S-a`（`a≤n`），其异或和为`S`。  

**可视化设计思路**：  
1. **动画演示**：  
   - **步骤1**：输入`n`，展示其二进制形式（如`100`）。  
   - **步骤2**：高亮最高位（如第3位），计算`S=2^3-1=7`。  
   - **步骤3**：动态展示如何通过选`n`和`S-n`得到异或和`S`。  
2. **复古像素风格**：  
   - **颜色方案**：绿色背景（复古终端），白色文本，红色高亮关键位。  
   - **音效**：异或操作时播放8位音效，成功计算时播放胜利音调。  

---

### **题解清单 (≥4星)**
1. **BB2655（5星）**  
   - 清晰推导全1数构造逻辑，代码简洁高效。  
2. **Porsche（4星）**  
   - 直接分解二进制位，实现直观。  
3. **GZY007（4星）**  
   - 循环移位统计位数，代码极简。  

---

### **最优思路提炼**
- **核心技巧**：利用二进制最高位构造全1数。  
- **实现步骤**：  
  1. 特判`k=1`，直接输出`n`。  
  2. 计算`n`的二进制最高位`b`，输出`2^b-1`。  
- **代码片段**：  
  ```cpp
  long long ans = 1;
  while (n >>= 1) ans <<= 1;  // 找最高位
  cout << (ans << 1) - 1;     // 构造全1数
  ```

---

### **类似题目推荐**
1. **洛谷 P2114** [位运算挑战](https://www.luogu.com.cn/problem/P2114)  
2. **洛谷 P1582** [倒水问题](https://www.luogu.com.cn/problem/P1582)  
3. **洛谷 P6102** [异或构造](https://www.luogu.com.cn/problem/P6102)  

---

### **个人心得摘录**
- **BB2655**：强调数据范围需用`long long`，避免溢出。  
- **SoyTony**：通过数学归纳证明全1数的最优性。  

---

### **可视化算法演示**
```javascript
// 伪代码：Canvas绘制n的二进制及全1数构造
function drawBinary(n) {
    let bits = n.toString(2).split('');
    let highestBit = bits.length;
    // 绘制n的二进制位，最高位红色高亮
    bits.forEach((bit, i) => {
        if (i === 0) fill('red'); // 最高位
        else fill('white');
        drawRect(i*10, 0, 10, 10); // 像素方块
    });
    // 绘制全1数S=2^b-1
    let sBits = new Array(highestBit).fill('1').join('');
    drawText(`S = ${sBits} = ${(1 << highestBit) - 1}`, 0, 20);
}
```

---

**总结**：通过位运算快速定位最高位，构造全1数为最优解，时间复杂度`O(log n)`，适用于极大数值范围。

---
处理用时：72.17秒