# 题目信息

# Lucky Permutation Triple

## 题目描述

Bike is interested in permutations. A permutation of length $ n $ is an integer sequence such that each integer from 0 to $ (n-1) $ appears exactly once in it. For example, $ [0,2,1] $ is a permutation of length 3 while both $ [0,2,2] $ and $ [1,2,3] $ is not.

A permutation triple of permutations of length $ n $ $ (a,b,c) $ is called a Lucky Permutation Triple if and only if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/bd0aa9c2cfa6e7dfc9681d8813c19703f16dbc42.png). The sign $ a_{i} $ denotes the $ i $ -th element of permutation $ a $ . The modular equality described above denotes that the remainders after dividing $ a_{i}+b_{i} $ by $ n $ and dividing $ c_{i} $ by $ n $ are equal.

Now, he has an integer $ n $ and wants to find a Lucky Permutation Triple. Could you please help him?

## 说明/提示

In Sample 1, the permutation triple $ ([1,4,3,2,0],[1,0,2,4,3],[2,4,0,1,3]) $ is Lucky Permutation Triple, as following holds:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/6124807a627fcd49ae8fab0d91c9fa90239af12b.png);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/598c5f3180986ca384de6df51e7cb84d8ea4e757.png);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/66b44a153ea212b6a13d195278ac6715ce383457.png);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/dd4f61ae15bc4151613d0da9fe47b466aa949e1e.png);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/0ea0fc069d3b3e3451d396fd4b6ef6f3d9456398.png).

In Sample 2, you can easily notice that no lucky permutation triple exists.

## 样例 #1

### 输入

```
5
```

### 输出

```
1 4 3 2 0
1 0 2 4 3
2 4 0 1 3
```

## 样例 #2

### 输入

```
2
```

### 输出

```
-1
```

# AI分析结果



**唯一算法分类**：数学构造法

---

### **题解思路与核心难点**
- **核心思路**：当且仅当 `n` 为奇数时存在解。构造前两个排列为 `0~n-1` 的升序，第三个排列为 `2i mod n`。  
- **证明关键**：  
  - **奇数**：`2i mod n` 生成唯一且覆盖 `0~n-1` 的所有元素。  
  - **偶数**：存在重复余数（如 `i` 和 `i+n/2` 的 `2i mod n` 相等），无法构成排列。  
- **难点突破**：通过数学推导发现 `2i mod n` 的排列性质，并验证构造的正确性。

---

### **题解评分 (≥4星)**
1. **GreenMelon (5星)**  
   - 思路清晰，直接给出数学证明与简洁代码。  
   - 代码可读性强，时间复杂度 O(n)，空间 O(1)。  

2. **Red_Dawn (4星)**  
   - 明确解释 `i*2 mod n` 的构造逻辑。  
   - 代码简洁，但缺少对构造方法的数学证明。  

3. **DL_Lingkong (4星)**  
   - 详细证明偶数无解的逻辑，代码结构清晰。  
   - 使用位运算优化奇偶判断，提升效率。  

---

### **最优思路提炼**
- **数学构造**：直接利用 `a[i] = i`, `b[i] = i`, `c[i] = (2i) % n`，保证 `c` 的唯一性。  
- **奇偶判断**：仅需判断 `n` 的奇偶性，避免复杂计算。  
- **时间复杂度**：O(n)，无法优化。  

---

### **同类型题与算法套路**
- **类似题目**：构造满足特定模运算条件的排列（如 `a[i] ≡ b[i] + c[i]`）。  
- **通用解法**：分析数学性质，利用等差/对称序列覆盖模空间。  

---

### **推荐题目**
1. [CF1188B] Count Pairs - 模运算与计数。  
2. [CF1452D] Radio Towers - 构造与奇偶性分析。  
3. [Luogu P1356] 数列的整除性 - 模运算性质应用。  

---

### **个人心得摘录**
- **Red_Dawn**：注意 `i` 从 0 开始，避免下标错误。  
- **DL_Lingkong**：用位运算优化奇偶判断，提升代码简洁性。  

---

### **可视化算法演示**
**核心逻辑动画设计**：  
1. **动态表格**：展示三列数组 `a`, `b`, `c` 的生成过程。  
   - **高亮当前 `i`**：用黄色标记当前计算的行。  
   - **颜色区分**：`a`（蓝色）、`b`（绿色）、`c`（红色）。  
2. **奇偶验证**：  
   - **偶数**：展示 `i` 和 `i+n/2` 导致 `c` 重复。  
   - **奇数**：动态画出 `2i mod n` 的覆盖路径。  
3. **复古像素风格**：  
   - **8位音效**：计算时播放“滴”声，完成时播放胜利音效。  
   - **Canvas 网格**：每个元素以像素块显示，背景音乐循环播放 FC 风格旋律。  

```html
<!-- 示例代码片段（可视化核心逻辑） -->
<script>
function drawStep(i, n) {
  // 绘制第i行：a[i]=i, b[i]=i, c[i]=(2i)%n
  ctx.fillStyle = "#FF0"; // 当前行高亮
  ctx.fillRect(0, i*20, 300, 20);
  // 绘制各列数值（伪代码）
  drawText(`i=${i}`, 10, i*20 + 15);
  drawText(`a=${i}`, 60, i*20 + 15);
  drawText(`b=${i}`, 110, i*20 + 15);
  drawText(`c=${(2*i)%n}`, 160, i*20 + 15);
}
</script>
```

---

**结论**：通过数学构造与奇偶性分析，快速判断并生成解，时间复杂度最优。可视化设计聚焦于动态验证构造过程的正确性。

---
处理用时：103.57秒