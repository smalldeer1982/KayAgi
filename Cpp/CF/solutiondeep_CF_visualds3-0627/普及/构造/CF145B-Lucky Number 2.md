# 题目信息

# Lucky Number 2

## 题目描述

Petya loves lucky numbers very much. Everybody knows that lucky numbers are positive integers whose decimal record contains only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

Petya loves long lucky numbers very much. He is interested in the minimum lucky number $ d $ that meets some condition. Let $ cnt(x) $ be the number of occurrences of number $ x $ in number $ d $ as a substring. For example, if $ d=747747 $ , then $ cnt(4)=2 $ , $ cnt(7)=4 $ , $ cnt(47)=2 $ , $ cnt(74)=2 $ . Petya wants the following condition to fulfil simultaneously: $ cnt(4)=a_{1} $ , $ cnt(7)=a_{2} $ , $ cnt(47)=a_{3} $ , $ cnt(74)=a_{4} $ . Petya is not interested in the occurrences of other numbers. Help him cope with this task.

## 样例 #1

### 输入

```
2 2 1 1
```

### 输出

```
4774
```

## 样例 #2

### 输入

```
4 7 3 1
```

### 输出

```
-1
```

# AI分析结果



---

### 算法分类  
**构造型问题**  

---

### 题解思路与解决难点  
#### 核心思路  
1. **骨架构造**：47 和 74 的交替结构决定整体框架。  
   - 若 `a3 > a4`，骨架为 `4747...`（以 4 开头）。  
   - 若 `a4 > a3`，骨架为 `7474...`（以 7 开头）。  
   - 若 `a3 = a4`，需尝试两种可能的起始字符以验证合法性。  
2. **填充剩余字符**：将多余的 4 和 7 插入不影响已有子串的位置，确保字典序最小。  
   - 剩余 4 插入第一个 4 后，剩余 7 插入最后一个 7 后。  

#### 解决难点  
- **合法性验证**：需满足 `a1 >= max(a3, a4)` 且 `a2 >= max(a3, a4)`，且 `|a3 - a4| ≤ 1`。  
- **最小字典序构造**：剩余字符的插入位置需精心选择，避免生成冗余子串。  

---

### 题解评分 (≥4星)  
1. **Sayori 题解（4星）**  
   - 亮点：清晰的条件判断，两次构造（以 4/7 开头）覆盖所有可能。  
   - 代码简洁，填充逻辑直观。  
2. **pikabi 题解（3星）**  
   - 思路完整但代码冗余，多次跳转（`goto`）影响可读性。  
   - 使用 `vector` 分段存储字符，实现较复杂。  

---

### 最优思路提炼  
1. **骨架验证**：通过 `a3` 和 `a4` 的差值确定起始字符，确保交替结构合法。  
2. **剩余字符插入**：  
   - 多余 4 插入第一个 4 后（不影响后续子串）。  
   - 多余 7 插入最后一个 7 后（避免生成新 74）。  
3. **两次构造法**：当 `a3 = a4` 时，需分别尝试以 4 或 7 开头的骨架。  

---

### 相似题目推荐  
1. **CF3D Least Cost Bracket Sequence**（构造括号序列）  
2. **LeetCode 767. Reorganize String**（重构字符串）  
3. **洛谷 P1090 [NOIP2004 提高组] 合并果子**（构造最优队列）  

---

### 可视化设计  
#### 动画演示方案  
1. **骨架构造**：  
   - **像素风格**：4 和 7 交替出现，用绿色（4）和红色（7）方块表示。  
   - **步进控制**：每添加一个字符，显示当前 `cnt(47)` 和 `cnt(74)` 的变化。  
2. **填充剩余字符**：  
   - **高亮插入位置**：在第一个 4 后插入黄色闪烁方块（4），在末尾插入蓝色闪烁方块（7）。  
3. **音效与交互**：  
   - **成功音效**：8-bit 风格胜利音效。  
   - **失败提示**：播放短促“错误”音效并显示红色警告。  

#### 核心代码片段（Sayori 题解填充逻辑）  
```cpp  
// 构造以4开头的骨架  
ans[cnt = 1] = 4; x--;  
while(z > 0 || w > 0) {  
    ans[++cnt] = fl == 0 ? 7 : 4;  
    if(fl == 0) z--, y--;  
    else w--, x--;  
    fl ^= 1;  
}  
// 填充剩余4和7  
printf("4");  
for(int i = 1; i <= x; ++i) printf("4");  
// 输出骨架剩余部分...  
```  

---

### 总结  
本题需结合构造与贪心，重点在于合法骨架的验证与剩余字符的最小化插入。通过两次构造和条件剪枝，可高效解决复杂约束问题。

---
处理用时：72.85秒