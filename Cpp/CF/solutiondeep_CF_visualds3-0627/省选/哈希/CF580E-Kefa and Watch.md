# 题目信息

# Kefa and Watch

## 题目描述

One day Kefa the parrot was walking down the street as he was on the way home from the restaurant when he saw something glittering by the road. As he came nearer he understood that it was a watch. He decided to take it to the pawnbroker to earn some money.

The pawnbroker said that each watch contains a serial number represented by a string of digits from $ 0 $ to $ 9 $ , and the more quality checks this number passes, the higher is the value of the watch. The check is defined by three positive integers $ l $ , $ r $ and $ d $ . The watches pass a check if a substring of the serial number from $ l $ to $ r $ has period $ d $ . Sometimes the pawnbroker gets distracted and Kefa changes in some substring of the serial number all digits to $ c $ in order to increase profit from the watch.

The seller has a lot of things to do to begin with and with Kefa messing about, he gave you a task: to write a program that determines the value of the watch.

Let us remind you that number $ x $ is called a period of string $ s $ ( $ 1<=x<=|s| $ ), if $ s_{i}=s_{i+x} $ for all $ i $ from 1 to $ |s|-x $ .

## 说明/提示

In the first sample test two checks will be made. In the first one substring "12" is checked on whether or not it has period 1, so the answer is "NO". In the second one substring "88", is checked on whether or not it has period 1, and it has this period, so the answer is "YES".

In the second statement test three checks will be made. The first check processes substring "3493", which doesn't have period 2. Before the second check the string looks as "334334", so the answer to it is "YES". And finally, the third check processes substring "8334", which does not have period 1.

## 样例 #1

### 输入

```
3 1 2
112
2 2 3 1
1 1 3 8
2 1 2 1
```

### 输出

```
NO
YES
```

## 样例 #2

### 输入

```
6 2 3
334934
2 2 5 2
1 4 4 3
2 1 6 3
1 2 3 8
2 3 6 1
```

### 输出

```
NO
YES
NO
```

# AI分析结果



**唯一算法分类**：线段树 + 哈希

---

### **题解思路与核心难点**

#### **核心思路**
1. **周期判定**：判断子串是否满足周期 `d`，等价于比较 `s[l..r-d]` 和 `s[l+d..r]` 是否相等（通过数学归纳法证明）。
2. **哈希加速**：维护字符串的哈希值，通过比较哈希值快速判断两段子串是否相等。
3. **线段树优化**：支持区间覆盖操作，并高效维护哈希值。

#### **关键难点**
- **哈希合并**：合并左右子区间的哈希值时，需考虑左子树的哈希值乘以基数的右子树长度次方，再加上右子树的哈希值。
- **Lazy标记处理**：区间覆盖时需快速计算新哈希值，利用预处理的基数前缀和数组（如 `sp[i] = p^0 + p^1 + ... + p^{i-1}`）。
- **双哈希防碰撞**：部分题解使用双哈希（不同基数和模数）避免哈希冲突。

---

### **题解评分 (≥4星)**

1. **子归 (线段树+哈希) [★★★★★]**  
   - **亮点**：详细推导哈希合并逻辑，预计算前缀和优化覆盖操作，代码结构清晰。  
   - **代码片段**：  
     ```cpp
     kano[x].h = (kano[x<<1].h * Pow[kano[x<<1|1].r - kano[x<<1|1].l + 1] + kano[x<<1|1].h) % mod;
     ```

2. **FriedrichC (线段树+哈希) [★★★★★]**  
   - **亮点**：深入分析哈希维护过程，提供数学证明，代码注释详细。  
   - **核心代码**：  
     ```cpp
     h(p) = (h(p<<1) * pw[r - mid] + h(p<<1|1)) % mod; // 合并哈希
     ```

3. **attack (双哈希+线段树) [★★★★★]**  
   - **亮点**：双哈希提升正确性，代码模块化，支持多种查询优化。  
   - **代码片段**：  
     ```cpp
     Se[0].IntervalQuery(1, l, r - d) == Se[1].IntervalQuery(1, l + d, r); // 双哈希比较
     ```

---

### **最优思路与技巧**

#### **关键技巧**
- **哈希合并公式**：左子树哈希值乘以 `base^右子树长度`，再加右子树哈希值。
- **Lazy标记优化**：区间覆盖时直接计算 `k * sp[len]`，避免逐字符更新。
- **双哈希防碰撞**：使用不同基数和模数组合（如 `base1=1331, mod1=1e9+7` 和 `base2=233, mod2=1e9+9`）。

#### **代码实现核心**
```cpp
// 线段树节点合并哈希值
void pushup(int p) {
    h(p) = (h(p<<1) * pw[r(p<<1|1) - l(p<<1|1) + 1] + h(p<<1|1)) % mod;
}

// 区间覆盖操作
void change(int p, int l, int r, int d) {
    if (l <= l(p) && r >= r(p)) {
        h(p) = d * sp[r(p) - l(p)] % mod; // sp为预处理的基数前缀和
        tag(p) = d;
        return;
    }
    // ... 递归处理子节点
}
```

---

### **同类型题推荐**
1. **P3372** 线段树区间修改与求和（基础线段树）。
2. **P3870** 位运算线段树（区间翻转与查询）。
3. **CF452F** 判定排列是否存在长度为3的等差数列（哈希应用）。

---

### **可视化与动画设计**

#### **动画方案**
1. **线段树结构展示**：用网格表示线段树节点，每个节点显示哈希值和覆盖标记。
2. **覆盖操作动画**：选中区间后，颜色渐变表示覆盖，同时更新哈希值。
3. **周期查询高亮**：比较 `s[l..r-d]` 和 `s[l+d..r]` 时，高亮两个子串区域。

#### **复古像素风格**
- **颜色方案**：8位色系（如绿色表示未覆盖，红色表示覆盖区域）。
- **音效设计**：覆盖时播放“哔”声，查询正确时播放“叮”声，错误时播放“嘟”声。
- **交互控制**：支持步进执行，调节动画速度，展示哈希合并过程。

#### **AI自动演示**
- **自动模式**：展示从初始字符串到多次覆盖和查询的全过程，动态更新哈希值和线段树结构。

---

### **个人心得摘录**
- **调试教训**：Lazy标记初始值需设为-1，避免与0冲突（覆盖值可能为0）。
- **哈希技巧**：预计算 `sp[i]` 可大幅优化覆盖操作的哈希计算效率。
- **思维突破**：周期判定的错位比较法，灵感来源于KMP算法的循环节推导。

---

**可视化示例代码（JS片段）**  
```javascript
// Canvas绘制线段树节点
function drawNode(node, x, y) {
    ctx.fillStyle = node.lazy ? '#FF0000' : '#00FF00'; // 红：覆盖，绿：未覆盖
    ctx.fillRect(x, y, NODE_WIDTH, NODE_HEIGHT);
    ctx.fillText(`Hash: ${node.hash}`, x + 5, y + 15);
}
```

---
处理用时：72.17秒