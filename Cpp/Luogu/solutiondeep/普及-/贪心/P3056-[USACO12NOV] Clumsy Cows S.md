# 题目信息

# [USACO12NOV] Clumsy Cows S

## 题目描述

Bessie the cow is trying to type a balanced string of parentheses into her new laptop, but she is sufficiently clumsy (due to her large hooves) that she keeps mis-typing characters.  Please help her by computing the minimum number of characters in the string that one must reverse (e.g., changing a left parenthesis to a right parenthesis, or vice versa) so that the string would become balanced.

There are several ways to define what it means for a string of parentheses to be "balanced".  Perhaps the simplest definition is that there must be the same total number of ('s and )'s, and for any prefix of the string, there must be at least as many ('s as )'s.  For example, the following strings are all balanced:

() 
(()) 
()(()()) 

while these are not:

)( 
())( 
((()))) 

给出一个偶数长度的括号序列，问最少修改多少个括号可以使其平衡。


## 说明/提示

The last parenthesis must be toggled, and so must one of the two middle right parentheses.



## 样例 #1

### 输入

```
())( 
```

### 输出

```
2 
```

# AI分析结果



### 综合分析与结论
本题核心在于通过贪心策略模拟括号匹配过程，维护当前未匹配的左括号数量。关键思路是：遇到无法匹配的右括号时反转成左括号，最后处理剩余左括号的反转需求。最优解法时间复杂度为 O(n)，空间复杂度 O(1)。

---

### 精选题解

#### 1. Berlin_Jacor（5星）
**关键亮点**：简洁高效，用变量模拟栈状态，无冗余操作  
**核心思路**：  
- `sum` 变量记录未匹配的左括号数  
- 遇到无法匹配的右括号时反转并计数  
- 最终剩余左括号反转半数  

```cpp
int ans=0, sum=0;
for(;i<lens;++i){
    if(s[i]=='(') sum++;
    else {
        if(sum) sum--;
        else ++ans,++sum;
    }
}
ans += sum>>1; // 位运算优化
```

#### 2. ResidualNight（5星）
**关键亮点**：双解法对比，深入浅出  
**栈解法核心**：显式栈处理，逻辑直观  
**计数法核心**：与 Berlin_Jacor 思路一致，变量代替栈  
**心得**：提出“STL NB”，强调 STL 与模拟方法的效率差异  

```cpp
int ans=0, p=0;
for(char c : s){
    if(c=='(') p++;
    else {
        if(p) p--;
        else ans++, p++;
    }
}
ans += p/2;
```

#### 3. A_Big_Jiong（4星）
**关键亮点**：详细注释，分步处理剩余括号  
**优化点**：最后处理奇偶性的逻辑清晰  
**心得**：提到“楼上的dalao用 (num+1)/2 更巧妙”，体现优化思路转变  

```cpp
for(int i=0;i<ls;i++){
    if(str[i]=='(') num++;
    else if(num==0) ans++, num++;
    else num--;
}
ans += num/2;
if(num%2) ans++;
```

---

### 最优思路总结
1. **模拟栈状态**：用变量（如 `sum`）代替显式栈，记录未匹配的左括号数。
2. **贪心反转**：遇到无法匹配的右括号时立即反转，保证后续前缀合法性。
3. **剩余处理**：剩余左括号需反转半数，利用整数除法特性简化计算。

---

### 拓展与举一反三
- **同类问题**：  
  - 平衡括号最小插入次数（LeetCode 921）  
  - 删除无效括号（LeetCode 301）  
- **推荐题目**：  
  1. 洛谷 P7910 [CSP-J 2021] 插入排序（括号性质应用）  
  2. 洛谷 P5658 [CSP-S 2019] 括号树（树形结构+括号匹配）  
  3. 洛谷 P1944 最长括号匹配（动态规划优化）  

---

### 调试心得摘录
- **A_Big_Jiong**：  
  > “楼上的dalao用的 ans+=(num+1)/2 更加巧妙，我太弱所以没想到”  
  → 体现从分步处理到公式优化的思维转变。  
- **ResidualNight**：  
  > “加减计数法更简单，不用掌握栈”  
  → 强调对问题本质的理解比数据结构更重要。  
- **cellur925**：  
  > “本来76分程序是先判断括号是否匹配，但~~并没有什么必要~~”  
  → 避免过度设计，聚焦核心逻辑的重要性。

---
处理用时：75.13秒