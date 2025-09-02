# 题目信息

# Compatible Numbers

## 题目描述

Two integers $ x $ and $ y $ are compatible, if the result of their bitwise "AND" equals zero, that is, $ a $ $ & $ $ b=0 $ . For example, numbers $ 90 $ $ (1011010_{2}) $ and $ 36 $ $ (100100_{2}) $ are compatible, as $ 1011010_{2} $ $ & $ $ 100100_{2}=0_{2} $ , and numbers $ 3 $ $ (11_{2}) $ and $ 6 $ $ (110_{2}) $ are not compatible, as $ 11_{2} $ $ & $ $ 110_{2}=10_{2} $ .

You are given an array of integers $ a_{1},a_{2},...,a_{n} $ . Your task is to find the following for each array element: is this element compatible with some other element from the given array? If the answer to this question is positive, then you also should find any suitable element.

## 样例 #1

### 输入

```
2
90 36
```

### 输出

```
36 90```

## 样例 #2

### 输入

```
4
3 6 3 6
```

### 输出

```
-1 -1 -1 -1```

## 样例 #3

### 输入

```
5
10 6 9 8 2
```

### 输出

```
-1 8 2 2 8```

# AI分析结果



0. **题目中文重写**

# 相容数

## 题目描述

两个整数 $x$ 和 $y$ 被称为相容的，当且仅当它们的按位与运算结果为 $0$，即 $x \& y = 0$。例如，数值 $90$（二进制表示为 $1011010_2$）与 $36$（$100100_2$）相容，因为 $1011010_2 \& 100100_2 = 0_2$；而数值 $3$（$11_2$）和 $6$（$110_2$）不相容，因为 $11_2 \& 110_2 = 10_2$。

给定一个包含 $n$ 个整数的数组 $a_1,a_2,...,a_n$，你的任务是：对数组中的每个元素，判断该元素是否与数组中其他某个元素相容。如果存在这样的元素，请输出任意一个符合条件的元素；否则输出 $-1$。

---

1. **唯一算法分类**  
线性DP

---

2. **综合分析与结论**

### 核心思路与算法要点
- **问题转化**：将相容条件转化为二进制补集问题，即寻找满足 $a_j \subseteq (\sim a_i)$ 的元素
- **状态设计**：建立状态数组 $f[mask]$ 表示能覆盖 $mask$ 二进制子集的任一元素
- **高维前缀和**：通过位运算逐层处理，实现覆盖所有子集的状态转移

### 解决难点
- **子集枚举优化**：直接枚举子集的时间复杂度为 $O(3^n)$，通过高维前缀和优化至 $O(n \cdot 2^n)$
- **状态转移方程**：$f[mask] = f[mask \oplus (1<<i)]$，当 $mask$ 的第 $i$ 位为 1 时进行状态继承
- **补集处理**：使用位掩码 $(1<<22)-1$ 进行安全取反操作，避免符号位干扰

### 可视化设计思路
- **动画演示**：展示22位掩码的逐层更新过程，用不同颜色标记当前处理的位
- **像素风格**：每个状态用16x16像素方块表示，激活状态时播放8-bit音效
- **交互控制**：支持单步执行查看每层位运算对状态数组的影响

---

3. **题解清单（≥4星）**

### ███ Watcher（5星）
- **核心亮点**：最简洁的高维前缀和实现，直接处理补集查询
- **关键代码**：
```cpp
for(int i=0;i<=21;i++)
    for(int j=0;j<(1<<22);j++)
        if((j&(1<<i))&&f[j^(1<<i)]) f[j]=f[j^(1<<i)];
```

### ███ Prurite（4.5星）
- **核心亮点**：逆向递推思路清晰，详细解释状态转移逻辑
- **个人心得**："从大往小更新，通过或运算逐步补全1的位，这种逆向思维非常巧妙"

### ███ Mooncrying（4星）
- **核心亮点**：新手友好，通过实例解释子集关系
- **优化技巧**：使用异或代替取反操作，避免符号位问题

---

4. **最优思路提炼**

**关键技巧矩阵**：
```text
| 技巧维度        | 实现要点                             |
|----------------|------------------------------------|
| 二进制处理      | 利用补集的子集性质进行相容判断         |
| 状态压缩        | 用mask表示所有可能的二进制组合         |
| 高效状态转移    | 高维前缀和实现O(n*2^n)的子集覆盖       |
| 安全位运算      | 使用(1<<22)-1作为掩码避免符号位干扰    |
| 逆向思维        | 从全1状态逐步递推，确保最优解覆盖      |
```

---

5. **同类型题目推荐**

- **CF165E**（本题）：二进制相容数查询
- **CF449D**：高维前缀和进阶应用
- **CF1326F2**：位掩码与状态压缩DP
- **AT_arc098_c**：子集覆盖与贡献计算

---

6. **核心代码实现**

**Watcher题解优化版**：
```cpp
const int MAXM = 1<<22;
int f[MAXM];

void preprocess() {
    // 初始化原始数据
    for(int x : a) f[x] = x;
    
    // 高维前缀和更新
    for(int bit=0; bit<22; bit++)
        for(int mask=0; mask<MAXM; mask++)
            if(mask & (1<<bit))
                if(f[mask^(1<<bit)])
                    f[mask] = f[mask^(1<<bit)];
}

int query(int x) {
    int target = (MAXM-1) ^ x;
    return f[target] ? f[target] : -1;
}
```

---

7. **可视化方案**

### 8-bit风格动态演示
```javascript
// 伪代码示例
class DPPixel {
    constructor(canvas) {
        this.grid = new Uint8Array(22*22); // 22位掩码可视化
        this.ctx = canvas.getContext('2d');
        this.playSound = (freq) => { /* Web Audio API实现 */ };
    }

    updateBit(bit) {
        // 绘制当前处理的位
        for(let y=0; y<=bit; y++) {
            for(let x=0; x<(1<<22); x++) {
                if(x & (1<<bit)) {
                    let color = this.f[x] ? 0x00FF00 : 0xFF0000;
                    this.drawPixel(x, y, color);
                }
            }
            this.playSound(440 + bit*100); // 音效反馈
            await sleep(50); // 控制动画速度
        }
    }
}
```

**交互特性**：
- 方向键控制动画速度（←减速，→加速）
- 空格键单步执行位更新
- ESC键重置演示
- 成功匹配时播放《超级马里奥》金币音效

---

8. **举一反三训练**

1. **基础练习**  
   - 洛谷P2114《位运算》
   - 洛谷P2396《yyy loves Maths IV》

2. **进阶挑战**  
   - Codeforces 449D《Jzzhu and Apples》
   - AtCoder ARC100E《Or Plus Max》

3. **思维拓展**  
   - LeetCode 982《Triples with Bitwise AND Equal To Zero》
   - HackerRank《AND Product》

---
处理用时：71.79秒