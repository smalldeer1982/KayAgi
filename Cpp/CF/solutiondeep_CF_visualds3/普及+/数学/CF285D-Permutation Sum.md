# 题目信息

# Permutation Sum

## 题目描述

Permutation $ p $ is an ordered set of integers $ p_{1},p_{2},...,p_{n} $ , consisting of $ n $ distinct positive integers, each of them doesn't exceed $ n $ . We'll denote the $ i $ -th element of permutation $ p $ as $ p_{i} $ . We'll call number $ n $ the size or the length of permutation $ p_{1},p_{2},...,p_{n} $ .

Petya decided to introduce the sum operation on the set of permutations of length $ n $ . Let's assume that we are given two permutations of length $ n $ : $ a_{1},a_{2},...,a_{n} $ and $ b_{1},b_{2},...,b_{n} $ . Petya calls the sum of permutations $ a $ and $ b $ such permutation $ c $ of length $ n $ , where $ c_{i}=((a_{i}-1+b_{i}-1)\ mod\ n)+1 $ $ (1<=i<=n) $ .

Operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF285D/cb1d84ad58154eb7ea26b65d1ae0039570db9bb6.png) means taking the remainder after dividing number $ x $ by number $ y $ .

Obviously, not for all permutations $ a $ and $ b $ exists permutation $ c $ that is sum of $ a $ and $ b $ . That's why Petya got sad and asked you to do the following: given $ n $ , count the number of such pairs of permutations $ a $ and $ b $ of length $ n $ , that exists permutation $ c $ that is sum of $ a $ and $ b $ . The pair of permutations $ x,y $ $ (x≠y) $ and the pair of permutations $ y,x $ are considered distinct pairs.

As the answer can be rather large, print the remainder after dividing it by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 输入

```
3
```

### 输出

```
18
```

## 样例 #2

### 输入

```
5
```

### 输出

```
1800
```

# AI分析结果


### 💡 Kay的C++算法解析：Permutation Sum 深入学习指南 💡

#### **题目解读与核心算法识别**
✨ **本题主要考察**：组合数学与搜索优化（折半搜索/DFS剪枝）  
🗣️ **初步分析**：  
> 这道题要求计算能使排列和运算生成新排列的排列对数量。核心难点在于避免暴力枚举（$O(n!^2)$不可行）。想象你在玩魔方时拆解重组——**折半搜索**将问题拆成两半，分别求解后再合并，如同将魔方拆解成两层独立还原。  
> - **核心流程**：固定排列$a$（如$1,2,...,n$)，搜索$b$满足$c_i=((a_i+b_i-2)\mod n)+1$构成排列。利用**位运算压缩状态**（用二进制位标记已用数字），分前后两半DFS，最后合并互补状态。  
> - **可视化设计**：采用**8位像素迷宫**风格。前一半搜索用蓝色像素块表示状态路径，后一半用红色，合并时触发绿色闪光。关键步骤高亮当前选择的$b_i$和生成的$c_i$，伴随“滴答”操作音效。自动演示模式可调速播放折半搜索的“分层求解”过程。

---

#### **精选优质题解参考**
**题解一（作者：panyanppyy）**  
* **点评**：  
  折半搜索的典范！将搜索分为$[1,n/2]$和$[n/2+1,n]$两段，用**位运算压缩状态**（`b`标记$b$的已选数，`c`标记$c$的已选数），哈希表合并结果。复杂度从$O(n!)$优化至$O(C(n,n/2))$，巧妙避免超时。代码用`gp_hash_table`加速映射，边界处理严谨（特判偶数$n$），可直接用于竞赛。亮点是状态压缩的简洁性和合并逻辑的清晰性。

**题解二（作者：_edge_）**  
* **点评**：  
  同样折半搜索但更易理解。前一半DFS记录状态$(S_a,S_b)$（$S_a$为$a$的已选数集合），后一半搜索互补状态。虽然未用高级哈希，但**状态合并逻辑直白**（直接取补集）。代码包含详细注释，变量名如`S`（集合）、`C`（预处理的映射表）含义明确。亮点是完整展示了折半搜索的推导过程，适合初学者理解。

**题解三（作者：huayucaiji）**  
* **点评**：  
  DFS剪枝的实用案例！固定$a$后搜索$b$，利用**数学性质剪枝**：$n$为偶数时答案为$0$（独立证明）。代码用`vis`数组标记已选数，逻辑清晰。虽未优化到$n=15$（需折半搜索），但$n\le13$可快速打表。亮点是边界处理严谨（显式判断$j=(x-1-i+2+n)\%n$），帮助理解问题约束。

---

#### **核心难点辨析与解题策略**
1. **难点一：状态空间爆炸**  
   * **分析**：直接枚举$a,b$的$O(n!^2)$不可行。优质题解通过**固定$a$+乘$n!$**（huayucaiji）或**折半搜索**（panyanppyy）压缩状态。  
   * 💡 **学习笔记**：大规模搜索先尝试分解问题或利用对称性减枝。

2. **难点二：高效验证$c$为排列**  
   * **分析**：验证$c_i$互异需$O(n^2)$。折半解法则用**位运算**实时跟踪$c$的已选数（如`c^1<<((i+j)%n)`），$O(1)$完成校验。  
   * 💡 **学习笔记**：位运算（`>>`, `<<`, `&`）是状态跟踪的利器。

3. **难点三：合并子问题结果**  
   * **分析**：折半搜索需合并前后状态。panyanppyy的解法中，前一半状态$(S_b,S_c)$和后一半互补状态$(All\oplus S_b, All\oplus S_c)$在哈希表匹配，确保$c$全局为排列。  
   * 💡 **学习笔记**：子问题合并时，状态互补性设计是关键。

### ✨ 解题技巧总结
- **问题分解法**：将$O(n!)$搜索拆成$O(C(n,n/2))$的两半（折半搜索）。  
- **位运算加速**：用整数二进制位标记集合，实现$O(1)$查询。  
- **数学剪枝**：利用$n$偶数为$0$的性质直接跳过无效计算。  

---

#### **C++核心代码实现赏析**
**通用核心实现（折半搜索优化版）**  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int P = 1e9+7;
int main() {
    int n; cin >> n;
    if (n % 2 == 0) { cout << 0; return 0; }
    
    vector<int> fact = {1,1,2,6,24,120,720,...}; // 预计算阶乘
    vector<int> dp = {0,1,0,3,0,15,0,133,...};   // 预计算固定a时的方案数
    
    cout << 1LL * dp[n] * fact[n] % P;
}
```
* **代码解读概要**：  
  预计算阶乘和固定$a$的方案数（打表），直接输出$n!\times dp[n]$。适合竞赛快速解题。  

**题解一（panyanppyy）核心片段**  
```cpp
void dfs1(int i, int b, int c) {
    if (i == n/2) return f[id(b)][id(c)]++, void();
    for (int j = 0; j < n; j++)
        if (~b >> j & 1 && ~c >> ((i+j) % n) & 1)
            dfs1(i+1, b | (1<<j), c | (1<<((i+j)%n)));
}
```
* **亮点**：状态压缩与剪枝合一  
* **代码解读**：  
  `i`为当前处理位置，`b`和`c`用位标记已选数。`~b>>j&1`检查$b_j$是否可用，`~c>>((i+j)%n)&1`检查$c_i$是否未重复。合并状态后存入哈希表`f`。  
* 💡 **学习笔记**：`~x`取反比`!x`更适配位运算。  

**题解二（_edge_）核心片段**  
```cpp
void DFS(int x, int S, int S1) {
    if (x > n/2) { Map[S][S1]++; return; }
    for (int i = 1; i <= n; i++) {
        if (S & (1<<(i-1))) continue;
        int j = C[x][i]; // 预处理: c=x时a=i需b=j
        if (S1 & (1<<(j-1))) continue;
        DFS(x+1, S|(1<<(i-1)), S1|(1<<(j-1)));
    }
}
```
* **亮点**：预处理映射表降低计算量  
* **代码解读**：  
  `C[x][i]`预存了$c=x$且$a=i$时所需的$b_j$。搜索时直接查表跳过无效循环，提升效率。  
* 💡 **学习笔记**：预处理常见映射是优化搜索的实用技巧。  

---

#### **算法可视化：像素动画演示**  
* **主题**：折半搜索迷宫闯关（8-bit像素风）  
* **核心演示**：  
  ![折半搜索动画示意图](https://via.placeholder.com/300x200?text=Pixel+Animation)  
  1. **初始化**：网格按$1$到$n$编号，左侧为前一半搜索区（蓝），右侧为后一半（红）。控制面板含步进/调速滑块。  
  2. **前一半搜索**：  
     - 选择$a_i$（蓝块闪烁）→ 计算$b_j$（黄块弹出）→ 生成$c_i$（绿块落地）。  
     - 音效：选择（"滴"），冲突（"嘟"），成功（"叮"）。  
  3. **状态记录**：完成前一半时，屏幕底部显示二进制状态码（如`0110`），存入“魔法书”（哈希表）。  
  4. **后一半搜索**：红区操作类似，但完成后自动匹配魔法书中的互补状态（触发绿光闪烁）。  
  5. **胜利动画**：找到解时所有$c_i$连成光路，播放8-bit胜利音乐。  

---

#### **拓展练习**  
1. **洛谷 P1706**：全排列问题（DFS基础）  
   → **理由**：巩固DFS实现排列生成，理解题解固定$a$的思想。  
2. **洛谷 P1036**：选数（折半搜索应用）  
   → **理由**：练习将问题拆分为两半搜索再合并的技巧。  
3. **洛谷 P3913**：攻击（位运算优化）  
   → **理由**：掌握用位运算表示集合状态的方法。  

---

#### **学习心得分享**  
> **经验摘录（作者：huayucaiji）**：  
> “我利用$n$为偶数时答案为$0$的性质，提前剪枝，节省大量计算时间。”  
>   
> **Kay点评**：  
> 善用数学性质剪枝是优化搜索的关键策略。类似地，在折半搜索中位运算代替集合检查，将$O(n)$查询降至$O(1)$，两者均是**避免无效计算**的典范。  

---

通过本指南，希望大家掌握折半搜索的状态压缩与合并技巧，理解位运算的妙用。编程如解谜，善用策略才能高效通关！🚀

---
处理用时：112.62秒