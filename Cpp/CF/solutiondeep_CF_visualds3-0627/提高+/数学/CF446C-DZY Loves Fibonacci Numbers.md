# 题目信息

# DZY Loves Fibonacci Numbers

## 题目描述

In mathematical terms, the sequence $ F_{n} $ of Fibonacci numbers is defined by the recurrence relation

 $ F_{1}=1; F_{2}=1; F_{n}=F_{n-1}+F_{n-2} (n>2). $ DZY loves Fibonacci numbers very much. Today DZY gives you an array consisting of $ n $ integers: $ a_{1},a_{2},...,a_{n} $ . Moreover, there are $ m $ queries, each query has one of the two types:

1. Format of the query " $ 1\ l\ r $ ". In reply to the query, you need to add $ F_{i-l+1} $ to each element $ a_{i} $ , where $ l<=i<=r $ .
2. Format of the query " $ 2\ l\ r $ ". In reply to the query you should output the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF446C/9b1c73158dd7a4166f7d8fde16bb75f36899bc0e.png) modulo $ 1000000009 (10^{9}+9) $ .

Help DZY reply to all the queries.

## 说明/提示

After the first query, $ a=[2,3,5,7] $ .

For the second query, $ sum=2+3+5+7=17 $ .

After the third query, $ a=[2,4,6,9] $ .

For the fourth query, $ sum=2+4+6=12 $ .

## 样例 #1

### 输入

```
4 4
1 2 3 4
1 1 4
2 1 4
1 2 4
2 1 3
```

### 输出

```
17
12
```

# AI分析结果



### 唯一算法分类  
**数论**

---

### 综合分析与结论  
**核心难点**：斐波那契数列的区间增量难以直接维护，需数学推导找到可累加的标记形式。  
**关键公式**：  
1. **斐波那契分解性质**：  
   $$\text{当修改区间 }[l, r]\text{ 时，每个位置 }x\text{ 的增量 }F_{x-l+1}=F_{-l+1}F_{x+1}+F_{-l}F_x$$  
2. **广义斐波那契和公式**：  
   $$\sum_{i=1}^n F_i = F_{n+2} - F_2$$  
**可视化设计**：  
- **动画流程**：线段树节点显示两个标记 `add1` 和 `add2`，下传时用颜色区分左/右子区间的系数调整。  
- **复古像素风格**：用 8-bit 网格表示线段树结构，标记下传时触发“方块闪烁 + 音效”。  
- **公式推导演示**：步进式展示斐波那契分解公式的推导过程，高亮关键变量。

---

### 题解清单 (≥4星)  
1. **AThousandSuns（5星）**  
   - **亮点**：利用斐波那契的线性分解性质，将增量拆解为两个可累加标记，代码简洁高效。  
   - **关键代码**：  
     ```cpp  
     update(1,1,n,l,r,rfib[l-1],rfib[l]);  
     // rfib[i] = (-1)^{i} * fib[i] 的模处理  
     ```  
2. **Treaker（5星）**  
   - **亮点**：维护广义斐波那契前两项作为标记，标记合并时直接相加，推导清晰。  
   - **关键代码**：  
     ```cpp  
     void add(ll a, ll b) {  
         tag = (tag + a) % mod;  
         sum = (sum + a * f[len] + b * (f[len+1] - 1)) % mod;  
     }  
     ```  
3. **xiaohuang（4星）**  
   - **亮点**：通过数学归纳法证明斐波那契和公式，代码逻辑清晰。  
   - **关键公式**：  
     $$\sum_{i=1}^n F_i = F_{n+2} - F_2$$  

---

### 最优思路或技巧提炼  
1. **线性分解标记**：将斐波那契增量拆解为两个固定系数，使线段树标记可累加。  
2. **广义斐波那契性质**：利用首项和次项的线性组合表示任意位置的斐波那契值。  
3. **二次剩余优化**：在模意义下预处理斐波那契数列的逆元或负下标值。

---

### 同类型题或类似算法套路  
- **通用思路**：区间修改含递推数列时，需数学推导找到可线性分解的标记形式。  
- **常见技巧**：  
  1. 利用数列递推式构造矩阵乘法（如广义斐波那契）。  
  2. 预处理负下标或逆元应对模运算。  

---

### 推荐相似题目  
1. P5171（区间加等差数列求和）  
2. P1474（斐波那契模意义下的矩阵优化）  
3. P3758（广义斐波那契与线段树结合）

---

### 个人心得摘录  
- **AThousandSuns**：通过斐波那契数列的负下标性质推导分解公式，避免复杂的前缀和计算。  
- **Treaker**：调试时发现右区间标记需重新计算首项，最终通过递推公式解决。  

---

### 可视化与算法演示  
```javascript  
// 伪代码：线段树标记下传动画  
class PixelTree {  
  constructor() {  
    this.canvas = document.createElement('canvas');  
    this.ctx = this.canvas.getContext('2d');  
    this.nodes = []; // 线段树节点像素坐标  
  }  

  drawNode(x, y, add1, add2) {  
    // 绘制 16x16 像素块，颜色根据标记值变化  
    this.ctx.fillStyle = `hsl(${add1 * 50}, 70%, 50%)`;  
    this.ctx.fillRect(x, y, 16, 16);  
    // 触发音效  
    playSound('blip', 100 + add2 * 10);  
  }  

  animatePushdown(node) {  
    // 标记下传时左右子节点颜色渐变  
    this.drawNode(node.x, node.y, 0, 0); // 清空父节点  
    this.drawNode(node.left.x, node.left.y, node.add1, node.add2);  
    // 计算右子节点新标记并绘制  
    let newAdd1 = calcNewAdd(node.add1, node.add2, node.left.len);  
    this.drawNode(node.right.x, node.right.y, newAdd1, ...);  
  }  
}  
```  
**交互设计**：  
- **步进控制**：按空格键单步执行标记下传。  
- **自动模式**：AI 按最优路径自动完成区间修改。  
- **音效**：每个标记更新触发 8-bit 音效，背景音乐为低循环芯片曲。

---

### 代码实现片段  
**AThousandSuns 的核心逻辑**：  
```cpp  
// 预处理负下标斐波那契值  
rfib[i] = (i&1) ? fib[i] : mod - fib[i];  

// 更新线段树标记  
void update(int o, int l, int r, int ql, int qr, int a1, int a2) {  
    if (ql <= l && r <= qr) {  
        add1[o] += a1;  
        add2[o] += a2;  
        sum[o] += (pre[r+1] - pre[l]) * a1 + (pre[r] - pre[l-1]) * a2;  
        return;  
    }  
    pushdown(o, l, r);  
    // ...递归更新子节点  
}  
```

---
处理用时：71.13秒