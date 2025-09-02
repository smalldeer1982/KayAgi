# 题目信息

# [USACO10FEB] Chocolate Buying S

## 题目描述

Bessie and the herd love chocolate so Farmer John is buying them some.

The Bovine Chocolate Store features $N (1 \le N \le 100,000)$ kinds of chocolate in essentially unlimited quantities.  Each type i of chocolate has price $P_i (1 \le P_i \le 10^{18})$ per piece and there are $C_i (1 \le C_i \le 10^{18})$ cows that want that type of chocolate.

Farmer John has a budget of $B (1 \le B \le 10^{18})$ that he can spend on chocolates for the cows. What is the maximum number of cows that he can satisfy?  All cows only want one type of chocolate, and will be satisfied only by that type.

Consider an example where FJ has $50$ to spend on $5$ different types of chocolate. A total of eleven cows have various chocolate preferences:

|Chocolate\_Type|Per\_Chocolate\_Cost|Cows\_preferring\_this\_type| 
|:-----------:|:-----------:|:-----------:|
|$1$|$5$|$3$|
|$2$|$1$|$1$|
|$3$|$10$|$4$|
|$4$|$7$|$2$|
|$5$|$60$|$1$|

Obviously, FJ can't purchase chocolate type $5$, since he doesn't have enough money. Even if it cost only $50$, it's a counterproductive purchase since only one cow would be satisfied.

Looking at the chocolates start at the less expensive ones, he can purchase $1$ chocolate of type $2$ for $1 \times 1$ leaving $50-1=49$, then purchase $3$ chocolate of type $1$ for $3 \times 5$ leaving $49-15=34$, then  purchase $2$ chocolate of type $4$ for $2 \times 7$ leaving $34-14=20$, then  purchase $2$ chocolate of type $3$ for $2 \times 10$ leaving $20-20=0$.

He would thus satisfy $1 + 3 + 2 + 2 = 8$ cows. 

## 样例 #1

### 输入

```
5 50 
5 3 
1 1 
10 4 
7 2 
60 1 
```

### 输出

```
8 
```

# AI分析结果



---

### **题解思路、算法要点与解决难点**

#### **核心贪心思路**
1. **策略推导**：最优解为优先购买价格最低的巧克力，尽可能多地满足对应奶牛，剩余资金再处理次低价，以此类推。  
   - **正确性证明**：若存在更优解，其中某个高价巧克力被优先选择，则替换为等量低价巧克力可满足更多奶牛，矛盾。

2. **实现关键**：  
   - **排序**：将巧克力按价格升序排列。  
   - **遍历选择**：对每种巧克力，若预算足够买完所有对应奶牛，则全买；否则用剩余预算尽可能买，结束计算。

#### **解决难点**
- **数据范围**：需使用 `unsigned long long` 避免溢出（如 `1e18` 级别运算）。  
- **贪心验证**：需理解为何排序后逐步处理能保证全局最优，而非动态规划或背包问题。

---

### **题解评分 (≥4星)**

| 作者          | 评分 | 亮点与不足 |
|---------------|------|------------|
| K0stlin       | ⭐⭐⭐⭐ | 代码简洁，逻辑清晰，处理溢出得当。但注释较少。 |
| llzzxx712     | ⭐⭐⭐⭐ | 注释详细，适合新手，变量命名规范。但未处理价格相同的情况（不影响正确性）。 |
| wisdom_grass  | ⭐⭐⭐⭐ | 结合STL容器与pair，代码现代，附带调试心得。 |

---

### **最优思路与技巧提炼**

#### **核心代码片段**
```cpp
struct Chocolate { 
    unsigned long long price, cows; 
};
sort(chocolates.begin(), chocolates.end(), [](auto& a, auto& b) {
    return a.price < b.price; // 按价格升序排序
});

unsigned long long max_cows = 0, budget = B;
for (auto& choco : chocolates) {
    if (budget >= choco.price * choco.cows) { // 全买
        max_cows += choco.cows;
        budget -= choco.price * choco.cows;
    } else { // 部分买
        max_cows += budget / choco.price;
        break;
    }
}
```

#### **关键技巧**
- **排序策略**：价格低者优先，确保每一步选择局部最优。  
- **溢出防御**：使用`unsigned long long`并优先处理乘法溢出风险（题设保证总花费≤`1e18`）。  

---

### **同类型题与算法套路**

#### **通用贪心思路**
- **最小成本覆盖**：优先选择单位成本最低的资源（如本题、混合牛奶问题）。  
- **区间调度**：选择结束时间最早的任务以最大化数量。  
- **性价比排序**：背包问题中按价值/重量比降序选择（部分背包问题）。

#### **推荐题目**
1. **P1208 [USACO1.3]混合牛奶**：按单价升序购买。  
2. **P1090 [NOIP2004 提高组] 合并果子**：小根堆贪心选择最小两堆。  
3. **P2240 部分背包问题**：按性价比排序取物品。

---

### **个人心得摘录**

- **标签误导**：ViXpop指出原题标签为动态规划，实际需用贪心，强调自主分析的重要性。  
- **数据陷阱**：Dr_殇因未用`long long`导致多次提交失败，提醒注意数据范围。  

---

### **可视化与算法演示设计**

#### **动画方案**
1. **像素风格界面**：  
   - 巧克力列表以8位像素块展示，价格与数量显示在右侧。  
   - 当前选中巧克力高亮为绿色，预算条红色递减。  

2. **贪心过程演示**：  
   - **步骤1**：排序动画，巧克力块按价格从左到右排列。  
   - **步骤2**：逐个购买，显示预算扣除与奶牛数累加，购买时播放“金币消耗”音效。  
   - **步骤3**：预算不足时触发“断裂”音效，结束动画。  

3. **交互功能**：  
   - **速度控制**：滑动条调节动画速度（0.5x~3x）。  
   - **AI自动模式**：自动执行贪心策略，模拟快速决策。  

#### **代码片段（Canvas绘制）**
```javascript
function drawChocolates() {
    chocolates.forEach((choco, idx) => {
        ctx.fillStyle = idx === currentIndex ? '#00FF00' : '#FFFFFF';
        ctx.fillRect(50 + idx * 60, 100, 50, 30); // 绘制巧克力块
        ctx.fillText(`$${choco.price}`, 55 + idx * 60, 120);
    });
}
```

---

### **总结**
本题通过排序+贪心策略实现高效求解，重点在于理解局部最优推导全局最优的正确性。可视化设计通过复古像素风格与交互式动画，直观呈现贪心决策过程，帮助学习者巩固策略思维。

---
处理用时：69.01秒