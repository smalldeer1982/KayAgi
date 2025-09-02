# 题目信息

# Treasure

## 题目描述

Malek has recently found a treasure map. While he was looking for a treasure he found a locked door. There was a string $ s $ written on the door consisting of characters '(', ')' and '\#'. Below there was a manual on how to open the door. After spending a long time Malek managed to decode the manual and found out that the goal is to replace each '\#' with one or more ')' characters so that the final string becomes beautiful.

Below there was also written that a string is called beautiful if for each $ i $ ( $ 1<=i<=|s| $ ) there are no more ')' characters than '(' characters among the first $ i $ characters of $ s $ and also the total number of '(' characters is equal to the total number of ')' characters.

Help Malek open the door by telling him for each '\#' character how many ')' characters he must replace it with.

## 说明/提示

 $ |s| $ denotes the length of the string $ s $ .

## 样例 #1

### 输入

```
(((#)((#)
```

### 输出

```
1
2
```

## 样例 #2

### 输入

```
()((#((#(#()
```

### 输出

```
2
2
1```

## 样例 #3

### 输入

```
#
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
(#)
```

### 输出

```
-1
```

# AI分析结果



### 中文重写题目
#### 题目名称：宝藏

**题目描述**  
Malek 最近发现了一张藏宝图。在寻宝过程中，他找到一扇锁住的门，门上写着一个由字符 '(', ')' 和 '#' 组成的字符串 $s$。门下方有一本开启手册，经破解后发现目标是将每个 '#' 替换为一个或多个 ')'，使得最终字符串满足以下条件：  
1. 对于每个位置 $i$（$1 \leq i \leq |s|$），前 $i$ 个字符中 ')' 的数量不超过 '(' 的数量；  
2. 整个字符串中 '(' 和 ')' 的总数量相等。  

请帮助 Malek 确定每个 '#' 需要替换为多少个 ')'。  

**输入输出样例**  
样例1输入：`(((#)((#)` → 输出：`1 2`  
样例2输入：`()((#((#(#()` → 输出：`2 2 1`  
样例3输入：`#` → 输出：`-1`  

---

### 算法分类  
**贪心**

---

### 题解对比与最优思路  

#### 题解共性分析  
1. **核心策略**：将前 $k-1$ 个 `#` 替换为 1 个 `)`，最后一个 `#` 替换为剩余未匹配的左括号数 $+1$。  
2. **合法性验证**：需两次遍历验证：  
   - 第一次遍历计算括号平衡并预分配 `#` 的替换值；  
   - 第二次遍历模拟替换后的字符串，确保每个前缀的括号平衡。  
3. **难点处理**：  
   - 处理 `#` 替换后可能出现的中间括号失衡（如 `(#)(` 型错误）；  
   - 验证最后一个 `#` 替换后的总括号数是否相等。  

#### 高星题解推荐  
1. **xiaoxiaoxia（4星）**  
   **亮点**：  
   - 清晰的两阶段验证（预分配+模拟替换验证）；  
   - 处理了替换后中间可能出现的非法情况（如 `cn < ans[k]` 时判负）。  
   **关键代码**：  
   ```cpp  
   // 预分配阶段  
   for(int i=0;i<n;i++) {  
       if(s[i]=='(') a++;  
       else if(s[i]==')') a--;  
       else if(s[i]=='#') ans[++k]=1, a--;  
       if(a<0) flag=0;  
   }  
   ans[k] += a;  // 最后一个#补足剩余左括号  
   // 二次验证阶段  
   for(int i=0;i<n;i++) {  
       if(s[i]=='#') a -= ans[++t];  
       if(a<0) flag=0;  
   }  
   ```

2. **lby_commandBlock（4星）**  
   **亮点**：  
   - 单独处理最后一个 `#` 后的括号平衡（如 `pipei` 变量验证）；  
   - 代码结构简洁，逻辑清晰。  
   **关键代码**：  
   ```cpp  
   // 计算最后一个#后的括号平衡  
   for (int i=back+1; i<=n; i++) {  
       if(s[i]=='(') pipei++;  
       else if(pipei>0) pipei--;  
   }  
   if(pipei>0) { /* 判负 */ }  
   ```

3. **wrongaaa（4星）**  
   **亮点**：  
   - 通过两次独立遍历确保合法性；  
   - 处理了替换后可能出现的中间负平衡（如 `sum < 0` 立即判负）。  
   **关键代码**：  
   ```cpp  
   // 预处理阶段  
   for(int i=0; i<len; i++) {  
       if(s[i]=='#') put[++point]=1, sum--;  
   }  
   put[point] += sum;  // 最后一个#补足  
   // 二次验证阶段  
   for(int i=0; i<len; i++) {  
       if(s[i]=='#') sum -= put[++t];  
       if(sum<0) { /* 判负 */ }  
   }  
   ```

---

### 最优思路总结  
1. **贪心分配**：前 $k-1$ 个 `#` 固定为 1 个 `)`，最后一个 `#` 承担剩余未匹配的左括号数。  
2. **二次验证**：必须模拟替换后的字符串，验证每个前缀的括号平衡。  
3. **边界处理**：  
   - 总左括号数需严格大于 `#` 数量（否则无解）；  
   - 最后一个 `#` 替换后需保证其替换值 $\geq 1$。  

---

### 相似题目推荐  
1. [P7914 括号匹配（CSP-J 2021）](https://www.luogu.com.cn/problem/P7914)  
2. [P1944 最长前缀匹配](https://www.luogu.com.cn/problem/P1944)  
3. [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)  

---

### 题解中的调试经验  
1. **二次验证必要性**（来自 wrongaaa）：  
   > 错误原因在于仅计算总数而未检查中间状态，如 `((#)())#(` 的错位情况。  
   **总结**：必须通过模拟替换后的字符串逐字符验证，不能仅依赖总数相等。  

2. **中间负平衡处理**（来自 xiaoxiaoxia）：  
   > 在替换 `#` 时立即检查 `a < ans[k]`，避免后续无法回溯的非法状态。  
   **总结**：贪心操作中需实时验证局部约束条件。

---
处理用时：72.39秒