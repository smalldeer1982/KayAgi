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
本题的核心是模拟括号匹配过程，通过计数或栈结构统计需反转的括号数。所有题解均围绕以下两个核心思路展开：
1. **计数模拟栈**：用变量记录未匹配的左括号数，遇到无法匹配的右括号时立即反转，空间优化至O(1)。
2. **显式栈结构**：用栈存储未匹配的左括号，逻辑直观但空间略高。

最优解法为计数模拟法，时间复杂度O(n)，空间O(1)，代码简洁且高效。

---

### 高星题解推荐（≥4星）

#### 1. 作者：Berlin_Jacor（5星）
**关键亮点**：极简计数模拟，代码仅15行。用`sum`模拟栈大小，处理右括号时动态反转，最终剩余左括号直接取半。
```cpp
int ans,sum,i;
string s;
int main(){
    cin>>s;
    for(;i<s.size();++i){
        if(s[i]=='(') sum++;
        else{
            if(sum) sum--;
            else ans++, sum++; // 反转右括号为左括号
        }
    }
    ans += sum>>1; // 剩余左括号取半
    cout<<ans;
}
```

#### 2. 作者：A_Big_Jiong（5星）
**关键亮点**：详细注释与逻辑推导，用`num`记录未匹配括号数。处理剩余括号时巧妙处理奇偶性。
```cpp
for(int i=0;i<ls;i++){
    if(str[i]=='(') num++;
    else if(num==0) { ans++; num++; } // 反转右括号
    else num--;
}
ans += num/2; // 处理剩余左括号
if(num%2) ans++;
```

#### 3. 作者：ResidualNight（5星）
**亮点**：双解对比（栈与计数法），深入浅出。提供两种实现思路，适合不同基础读者。
```cpp
// 计数法
int ans=0, p=0;
for(char c : s){
    if(c=='(') p++;
    else p>0 ? p-- : (ans++, p++);
}
ans += p/2;
```

---

### 关键思路与技巧
1. **计数模拟栈**：用变量替代显式栈，空间优化至O(1)。
2. **动态反转策略**：遇到无法匹配的右括号时立即反转，避免二次遍历。
3. **剩余括号处理**：剩余左括号数目需反转半数，奇偶性特殊处理。

---

### 同类题目推荐
1. [P1944] 最长括号匹配（简单括号扩展）
2. [P2115] 平衡的括号（加强版，需处理多种括号）
3. [CF5C] Longest Regular Bracket Sequence（求最长合法子串）

---

### 题解中的个人心得摘录
- **A_Big_Jiong**：原题解提到“楼上的dalao用`ans+=(num+1)/2`更巧妙”，体现对代码优化的思考过程。
- **ResidualNight**：结尾调侃题目背景“尽是扯淡”，反映解题后对题面的幽默反思。
- **cellur925**：提到“橙人做橙题会不会掉蓝啊”，体现对题目难度分级的自嘲式思考。

---
处理用时：54.53秒