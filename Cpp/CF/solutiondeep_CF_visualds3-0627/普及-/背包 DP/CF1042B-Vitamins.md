# 题目信息

# Vitamins

## 题目描述

Berland shop sells $ n $ kinds of juices. Each juice has its price $ c_i $ . Each juice includes some set of vitamins in it. There are three types of vitamins: vitamin "A", vitamin "B" and vitamin "C". Each juice can contain one, two or all three types of vitamins in it.

Petya knows that he needs all three types of vitamins to stay healthy. What is the minimum total price of juices that Petya has to buy to obtain all three vitamins? Petya obtains some vitamin if he buys at least one juice containing it and drinks it.

## 说明/提示

In the first example Petya buys the first, the second and the fourth juice. He spends $ 5 + 6 + 4 = 15 $ and obtains all three vitamins. He can also buy just the third juice and obtain three vitamins, but its cost is $ 16 $ , which isn't optimal.

In the second example Petya can't obtain all three vitamins, as no juice contains vitamin "C".

## 样例 #1

### 输入

```
4
5 C
6 B
16 BAC
4 A
```

### 输出

```
15
```

## 样例 #2

### 输入

```
2
10 AB
15 BA
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5
10 A
9 BC
11 CA
4 A
5 B
```

### 输出

```
13
```

## 样例 #4

### 输入

```
6
100 A
355 BCA
150 BC
160 AC
180 B
190 CA
```

### 输出

```
250
```

## 样例 #5

### 输入

```
2
5 BA
11 CB
```

### 输出

```
16
```

# AI分析结果



# 算法分析与题解总结

## **唯一算法分类**
状态压缩动态规划（状压DP）

---

## **综合分析与结论**
### 核心思路与解决难点
**核心思路**：将维生素组合状态压缩为二进制数（A=001, B=010, C=100），通过动态规划维护每个状态的最小花费，最终目标为状态 `111`（即7）。  
**解决难点**：  
1. 状态表示：用3位二进制表示维生素组合，共8种状态。  
2. 状态转移：每次添加果汁时，用位运算合并状态（`j | pv[i]`）。  
3. 初始化：初始状态 `f[0] = 0`，其他状态设为极大值。  

### 可视化设计
- **动态状态更新**：以网格展示8种状态，颜色表示当前费用（如红色高亮表示被更新）。  
- **动画效果**：  
  1. 果汁依次被处理，显示其维生素组合（如 `BAC` 高亮为三色方块）。  
  2. 对每个状态 `j`，计算新状态 `j | pv[i]`，若费用更低则更新并触发音效。  
- **复古风格**：  
  - 像素化网格与果汁图标，8-bit音效标记状态更新。  
  - 成功找到最优解时播放胜利音效，背景音乐循环播放。  

---

## **题解评分（≥4星）**
1. **ZigZagKmp（5星）**  
   - **亮点**：代码简洁，状态压缩思路清晰，时间复杂度O(n)。  
   - **关键代码**：  
     ```cpp
     for(int i=1;i<=n;++i) {
         for(int j=7;j>=0;--j) {
             f[j|pv[i]] = min(f[j|pv[i]], f[j] + w[i]);
         }
     }
     ```
2. **览遍千秋（4星）**  
   - **亮点**：暴力枚举所有可能组合，易于理解。  
   - **关键代码**：  
     ```cpp
     ans = min(abcm, min(am+bm+cm, min(abm+cm, ... )));
     ```
3. **yfct（4星）**  
   - **亮点**：预处理各类型最小费用，组合覆盖所有情况。  

---

## **最优思路提炼**
**关键技巧**：  
1. **状态压缩**：将维生素组合映射为二进制数，简化状态表示。  
2. **动态规划优化**：用背包思想逐步更新状态，避免重复计算。  
3. **位运算合并**：通过 `|` 运算快速合并维生素组合状态。  

---

## **同类题目推荐**
1. **P1879 [Corn Fields]**（状压DP）  
2. **P2831 [愤怒的小鸟]**（状压DP）  
3. **P1156 [垃圾陷阱]**（状态转移优化）  

---

## **个人心得摘录**
- **调试教训**：样例5中组合 `BA` 和 `CB` 需正确合并为 `AB` 和 `BC`，否则可能遗漏最优解。  
- **顿悟点**：将维生素组合抽象为二进制状态是核心突破口。  

---

## **核心算法演示（伪代码）**
```javascript
// 初始化状态数组
let f = [0, INF, INF, INF, INF, INF, INF, INF];

// 处理每个果汁
juices.forEach(juice => {
    // 获取当前果汁的状态pv和价格w
    for (let j = 7; j >= 0; j--) {
        let newState = j | pv;
        if (f[newState] > f[j] + w) {
            f[newState] = f[j] + w; // 触发动画更新
        }
    }
});

// 输出结果
return f[7] === INF ? -1 : f[7];
```

---

## **复古游戏化动画设计**
- **像素风格**：  
  - 每个状态用3x3像素块表示（A/B/C位对应红/绿/蓝）。  
  - 费用数值用8-bit字体显示在状态下方。  
- **音效设计**：  
  - **状态更新**：短促“哔”声。  
  - **成功**：经典FC胜利旋律。  
- **自动演示**：逐步播放果汁处理过程，用户可暂停/调速。  

---

**总结**：状压DP是本题最优解，时间复杂度低且通用性强。暴力枚举在本题中因状态数少而可行，但状压DP更适用于扩展场景。

---
处理用时：94.89秒