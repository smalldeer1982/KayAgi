# 题目信息

# Factorials and Powers of Two

## 题目描述

A number is called powerful if it is a power of two or a factorial. In other words, the number $ m $ is powerful if there exists a non-negative integer $ d $ such that $ m=2^d $ or $ m=d! $ , where $ d!=1\cdot 2\cdot \ldots \cdot d $ (in particular, $ 0! = 1 $ ). For example $ 1 $ , $ 4 $ , and $ 6 $ are powerful numbers, because $ 1=1! $ , $ 4=2^2 $ , and $ 6=3! $ but $ 7 $ , $ 10 $ , or $ 18 $ are not.

You are given a positive integer $ n $ . Find the minimum number $ k $ such that $ n $ can be represented as the sum of $ k $ distinct powerful numbers, or say that there is no such $ k $ .

## 说明/提示

In the first test case, $ 7 $ can be represented as $ 7=1+6 $ , where $ 1 $ and $ 6 $ are powerful numbers. Because $ 7 $ is not a powerful number, we know that the minimum possible value of $ k $ in this case is $ k=2 $ .

In the second test case, a possible way to represent $ 11 $ as the sum of three powerful numbers is $ 11=1+4+6 $ . We can show that there is no way to represent $ 11 $ as the sum of two or less powerful numbers.

In the third test case, $ 240 $ can be represented as $ 240=24+32+64+120 $ . Observe that $ 240=120+120 $ is not a valid representation, because the powerful numbers have to be distinct.

In the fourth test case, $ 17179869184=2^{34} $ , so $ 17179869184 $ is a powerful number and the minimum $ k $ in this case is $ k=1 $ .

## 样例 #1

### 输入

```
4
7
11
240
17179869184```

### 输出

```
2
3
4
1```

# AI分析结果

【题目内容】
# 阶乘与2的幂

## 题目描述

一个数被称为“强数”，如果它是2的幂或某个数的阶乘。换句话说，数$m$是强数，当且仅当存在一个非负整数$d$，使得$m=2^d$或$m=d!$，其中$d!=1\cdot 2\cdot \ldots \cdot d$（特别地，$0! = 1$）。例如，$1$、$4$和$6$是强数，因为$1=1!$，$4=2^2$，$6=3!$，但$7$、$10$或$18$不是。

给定一个正整数$n$，找到最小的$k$，使得$n$可以表示为$k$个**互不相同**的强数的和，或者说明这样的$k$不存在。

## 说明/提示

在第一个测试用例中，$7$可以表示为$7=1+6$，其中$1$和$6$是强数。因为$7$本身不是强数，所以在这种情况下，$k$的最小可能值是$k=2$。

在第二个测试用例中，$11$可以表示为$11=1+4+6$。我们可以证明，$11$不能用两个或更少的强数表示。

在第三个测试用例中，$240$可以表示为$240=24+32+64+120$。注意，$240=120+120$不是有效的表示，因为强数必须互不相同。

在第四个测试用例中，$17179869184=2^{34}$，所以$17179869184$是强数，$k$的最小值是$k=1$。

## 样例 #1

### 输入

```
4
7
11
240
17179869184```

### 输出

```
2
3
4
1```

【算法分类】
搜索

【题解分析与结论】
该题的核心在于如何高效地找到将$n$表示为$k$个互不相同的强数（2的幂或阶乘）的最小$k$。由于$n$的范围较大（$1 \leq n \leq 10^{12}$），直接暴力搜索不可行。题解中普遍采用预处理阶乘数，然后通过深度优先搜索（DFS）或状态压缩枚举阶乘的选择，最后用二进制拆分处理剩余部分。

【评分较高的题解】

1. **作者：Eason_AC (赞：8)**
   - **星级：5星**
   - **关键亮点：**
     - 预处理阶乘数，利用DFS枚举阶乘的选择。
     - 使用`__builtin_popcountll()`函数快速计算二进制中1的个数。
     - 代码结构清晰，逻辑严谨。
   - **核心代码：**
     ```cpp
     void dfs(int x, int cnt, long long rest) {
         if(x > m) {
             ans = min(ans, cnt + __builtin_popcountll(rest));
             return;
         }
         if(rest - fac[x] >= 0 && cnt + 1 < ans)
             dfs(x + 1, cnt + 1, rest - fac[x]);
         dfs(x + 1, cnt, rest);
     }
     ```

2. **作者：Duramente (赞：4)**
   - **星级：4星**
   - **关键亮点：**
     - 采用状态压缩枚举阶乘的选择，减少搜索空间。
     - 通过二进制拆分处理剩余部分，思路清晰。
   - **核心代码：**
     ```cpp
     rep(msk,1<<15){
         int y=x;
         rep(i,15){
             if((msk>>i)&1)y-=fac[i+1];
         }
         if(y>=0){
             ans=min(ans,cnt(y)+cnt(msk));
         }
     }
     ```

3. **作者：Composite_Function (赞：3)**
   - **星级：4星**
   - **关键亮点：**
     - 通过DFS枚举阶乘的选择，结合二进制拆分处理剩余部分。
     - 代码简洁，逻辑清晰。
   - **核心代码：**
     ```cpp
     long long dfs(long long pos,long long val,long long tmp){
         if(val<0) return INT_MAX;
         else if(pos==15+1){
             long long ans=0;
             while(val>0){
                 if(val&1) ans++;
                 val>>=1;
             }
             return ans+tmp;
         }
         else return min(dfs(pos+1,val,tmp),dfs(pos+1,val-num[pos],tmp+1));
     }
     ```

【最优关键思路】
1. **预处理阶乘数**：由于$15! > 10^{12}$，阶乘数只有14个，预处理后可以大大减少搜索空间。
2. **DFS或状态压缩枚举**：通过DFS或状态压缩枚举阶乘的选择，确保不重复使用阶乘。
3. **二进制拆分处理剩余部分**：将剩余部分用二进制拆分，计算其二进制中1的个数，即为所需2的幂的个数。

【可拓展之处】
类似的问题可以扩展到其他类型的数的组合，例如斐波那契数列、平方数等。通过预处理和搜索策略，可以高效解决这类问题。

【推荐题目】
1. [P1463 [POI2001] 阶乘问题](https://www.luogu.com.cn/problem/P1463)
2. [P1464 [POI2001] 阶乘问题 II](https://www.luogu.com.cn/problem/P1464)
3. [P1465 [POI2001] 阶乘问题 III](https://www.luogu.com.cn/problem/P1465)

---
处理用时：32.96秒