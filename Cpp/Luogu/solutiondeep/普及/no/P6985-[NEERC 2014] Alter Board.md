# 题目信息

# [NEERC 2014] Alter Board

## 题目描述

Little Dima gave his little brother Petya interactive chess board of size $n \times m$ as a present. There are many awesome features of this board but one is Petya's favorite. He can choose any rectangle formed by board squares and perform an inversion. Every white cell in the inverted rectangle becomes black and every black one becomes white.

In the initial state the board is colored in chess style, namely every cell is either black or white and every two cells that share a side have different colors. Little Petya wants to perform several inversions described above to turn all cells into the same color. He is impatient, so he asks you to provide him with instructions to do it with the minimal number of inversions.

## 说明/提示

Time limit: 1 s, Memory limit: 256 MB. 

spj provider:@[shenyouran](/user/137367).

## 样例 #1

### 输入

```
2 2
```

### 输出

```
2
1 1 1 1
2 2 2 2
```

# AI分析结果



### 算法分类
构造

---

### 题解分析与结论
所有题解均基于棋盘奇偶性质构造最优解：  
1. **核心思路**：翻转所有偶数行使行同色，再翻转所有偶数列使全局同色  
2. **数学优化**：当行数或列数为奇数时，选择翻转偶数行/列可减少操作次数（$\lfloor n/2 \rfloor + \lfloor m/2 \rfloor$）  
3. **关键证明**：任何其他翻转策略都无法更少次数达成全同色，因每次翻转必须覆盖所有未同色区域  

---

### 优质题解推荐
#### 1. 作者：indream（★★★★☆）
**关键亮点**：  
- 通过棋盘变换图示直观展示操作效果  
- 明确解释选择偶数行/列的内在数学优势  
- 代码简洁高效（时间复杂度 O(n+m)）

**核心代码**：
```cpp
for(int i=2;i<=n;i+=2) // 翻转偶数行
    cout<<i<<" 1 "<<i<<' '<<m<<'\n';
for(int i=2;i<=m;i+=2) // 翻转偶数列
    cout<<"1 "<<i<<' '<<n<<' '<<i<<'\n';
```

---

#### 2. 作者：Clarinet（★★★★☆）
**关键亮点**：  
- 附棋盘变换示意图增强理解  
- 对比奇偶行列翻转次数差异  
- 包含调试心路历程，强调构造思路的关键性

**代码亮点**：  
- 变量命名清晰，操作范围明确  
- 严格遵循行优先再列的操作顺序  

---

#### 3. 作者：yzm0325（★★★★☆）
**核心技巧**：  
- 用 $4 \times 8$ 矩阵分步图示演示翻转效果  
- 强调「副作用最小」的贪心原则  
- 代码无冗余操作，直接输出全局翻转区域  

---

### 最优思路总结
**关键构造技巧**：  
1. **奇偶性质利用**：利用棋盘天然的黑白交替特性，通过两次全局翻转消除颜色差异  
2. **最值证明方法**：当且仅当翻转偶数行/列时，$\lfloor n/2 \rfloor + \lfloor m/2 \rfloor$ 是最小不可优化值  
3. **全局翻转策略**：每次操作覆盖最大可能的同色区域（整行/整列）  

---

### 同类题目推荐
1. [P1005 矩阵取数游戏](https://www.luogu.com.cn/problem/P1005) - 棋盘操作中的贪心策略  
2. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219) - 棋盘类构造问题  
3. [P1969 积木大赛](https://www.luogu.com.cn/problem/P1969) - 差分思想与构造性操作  

---

### 调试心得摘录
**Clarinet**：  
> "这题在洛谷数据修正前提交记录多达4页，最终发现必须严格遵循先翻行再翻列的构造顺序才能通过"  
**启示**：构造类问题需严格验证操作顺序的合理性，有时看似等价的不同顺序可能导致结果差异

---
处理用时：54.48秒