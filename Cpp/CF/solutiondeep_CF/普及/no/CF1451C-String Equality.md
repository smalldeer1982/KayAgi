# 题目信息

# String Equality

## 题目描述

Ashish has two strings $ a $ and $ b $ , each of length $ n $ , and an integer $ k $ . The strings only contain lowercase English letters.

He wants to convert string $ a $ into string $ b $ by performing some (possibly zero) operations on $ a $ .

In one move, he can either

- choose an index $ i $ ( $ 1 \leq i\leq n-1 $ ) and swap $ a_i $ and $ a_{i+1} $ , or
- choose an index $ i $ ( $ 1 \leq i \leq n-k+1 $ ) and if $ a_i, a_{i+1}, \ldots, a_{i+k-1} $ are all equal to some character $ c $ ( $ c \neq $ 'z'), replace each one with the next character $ (c+1) $ , that is, 'a' is replaced by 'b', 'b' is replaced by 'c' and so on.

Note that he can perform any number of operations, and the operations can only be performed on string $ a $ .

Help Ashish determine if it is possible to convert string $ a $ into $ b $ after performing some (possibly zero) operations on it.

## 说明/提示

In the first test case it can be shown that it is impossible to convert $ a $ into $ b $ .

In the second test case,

"abba" $ \xrightarrow{\text{inc}} $ "acca" $ \xrightarrow{\text{inc}} $ $ \ldots $ $ \xrightarrow{\text{inc}} $ "azza".

Here "swap" denotes an operation of the first type, and "inc" denotes an operation of the second type.

In the fourth test case,

"aaabba" $ \xrightarrow{\text{swap}} $ "aaabab" $ \xrightarrow{\text{swap}} $ "aaaabb" $ \xrightarrow{\text{inc}} $ $ \ldots $ $ \xrightarrow{\text{inc}} $ "ddaabb" $ \xrightarrow{\text{inc}} $ $ \ldots $ $ \xrightarrow{\text{inc}} $ "ddddbb" $ \xrightarrow{\text{inc}} $ $ \ldots $ $ \xrightarrow{\text{inc}} $ "ddddcc".

## 样例 #1

### 输入

```
4
3 3
abc
bcd
4 2
abba
azza
2 1
zz
aa
6 2
aaabba
ddddcc```

### 输出

```
No
Yes
No
Yes```

# AI分析结果

【题目内容】
# 字符串相等

## 题目描述

Ashish有两个字符串 $a$ 和 $b$，长度均为 $n$，以及一个整数 $k$。字符串仅包含小写英文字母。

他希望通过在 $a$ 上执行一些（可能为零）操作，将字符串 $a$ 转换为字符串 $b$。

在一次操作中，他可以选择：

- 选择一个索引 $i$（$1 \leq i \leq n-1$），并交换 $a_i$ 和 $a_{i+1}$，或者
- 选择一个索引 $i$（$1 \leq i \leq n-k+1$），如果 $a_i, a_{i+1}, \ldots, a_{i+k-1}$ 都等于某个字符 $c$（$c \neq$ 'z'），则将每个字符替换为下一个字符 $（c+1）$，即 'a' 替换为 'b'，'b' 替换为 'c'，依此类推。

注意，他可以执行任意数量的操作，且操作只能在字符串 $a$ 上执行。

帮助Ashish确定是否可以通过执行一些（可能为零）操作将字符串 $a$ 转换为 $b$。

## 说明/提示

在第一个测试用例中，可以证明无法将 $a$ 转换为 $b$。

在第二个测试用例中，

"abba" $ \xrightarrow{\text{inc}} $ "acca" $ \xrightarrow{\text{inc}} $ $ \ldots $ $ \xrightarrow{\text{inc}} $ "azza".

这里 "swap" 表示第一种操作，"inc" 表示第二种操作。

在第四个测试用例中，

"aaabba" $ \xrightarrow{\text{swap}} $ "aaabab" $ \xrightarrow{\text{swap}} $ "aaaabb" $ \xrightarrow{\text{inc}} $ $ \ldots $ $ \xrightarrow{\text{inc}} $ "ddaabb" $ \xrightarrow{\text{inc}} $ $ \ldots $ $ \xrightarrow{\text{inc}} $ "ddddbb" $ \xrightarrow{\text{inc}} $ $ \ldots $ $ \xrightarrow{\text{inc}} $ "ddddcc".

## 样例 #1

### 输入

```
4
3 3
abc
bcd
4 2
abba
azza
2 1
zz
aa
6 2
aaabba
ddddcc```

### 输出

```
No
Yes
No
Yes```

【算法分类】  
贪心

【题解分析与结论】  
本题的核心在于通过贪心策略判断是否可以通过交换和字符递增操作将字符串 $a$ 转换为 $b$。由于交换操作可以任意调整字符顺序，因此我们只需关注字符的出现次数。而字符递增操作则要求连续的 $k$ 个相同字符才能进行递增变换。因此，问题的关键在于统计每个字符的出现次数，并判断是否可以通过递增操作将 $a$ 中的字符转换为 $b$ 中的字符。

【评分较高的题解】

1. **作者：Miko35 (5星)**  
   **关键亮点**：  
   - 通过统计字符出现次数，从字母 `a` 开始逐步匹配，确保每次多余的字符都能通过递增操作转换为下一个字符。
   - 代码简洁，逻辑清晰，直接通过线性遍历解决问题。

   **核心代码**：
   ```cpp
   for(int i=0;i<26;i++){
       if(cnta[i]>=cntb[i]){
           int c=cnta[i]-cntb[i];
           if(c%k!=0){
               puts("No");
               goto tag;
           }
           else{
               cnta[i]=cntb[i];
               cnta[i+1]+=c;
           }
       }
       else{
           puts("No");
           goto tag;
       }
   }
   puts("Yes");
   tag:;
   ```

2. **作者：henrytb (4星)**  
   **关键亮点**：  
   - 从字母 `z` 向 `a` 倒序遍历，确保字符只能递增而不能递减。
   - 通过差值判断是否可以通过递增操作匹配字符。

   **核心代码**：
   ```cpp
   per(i,25,0) {
       now-=aa[i];
       if(now<0||aa[i]%k!=0) {flg=0;break;}
   }
   if(flg) puts("Yes");
   else puts("No");
   ```

3. **作者：_hxh (4星)**  
   **关键亮点**：  
   - 通过桶排序统计字符出现次数，确保每次多余的字符都能通过递增操作转换为下一个字符。
   - 代码结构清晰，逻辑严谨。

   **核心代码**：
   ```cpp
   for(int i=1;i<=26;i++){
       if(a[i]>=b[i]){
           if((a[i]-b[i])%k){
               cout<<"No"<<endl;
               flag=0;
               break;
           }
           else{
               a[i+1]+=a[i]-b[i];
           }
       }
       else{
           cout<<"No"<<endl;
           flag=0;
           break;
       }
   }
   ```

【最优关键思路】  
通过统计字符出现次数，从字母 `a` 开始逐步匹配，确保每次多余的字符都能通过递增操作转换为下一个字符。这种方法既保证了字符的顺序无关性，又确保了递增操作的可行性。

【可拓展之处】  
类似的问题可以扩展到其他字符变换操作，如字符递减、字符替换等。此外，可以结合其他算法如动态规划或搜索来解决更复杂的字符串变换问题。

【推荐题目】  
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)  
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)  
3. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)

---
处理用时：43.39秒