# 题目信息

# Binary Palindromes

## 题目描述

A palindrome is a string $ t $ which reads the same backward as forward (formally, $ t[i] = t[|t| + 1 - i] $ for all $ i \in [1, |t|] $ ). Here $ |t| $ denotes the length of a string $ t $ . For example, the strings 010, 1001 and 0 are palindromes.

You have $ n $ binary strings $ s_1, s_2, \dots, s_n $ (each $ s_i $ consists of zeroes and/or ones). You can swap any pair of characters any number of times (possibly, zero). Characters can be either from the same string or from different strings — there are no restrictions.

Formally, in one move you:

- choose four integer numbers $ x, a, y, b $ such that $ 1 \le x, y \le n $ and $ 1 \le a \le |s_x| $ and $ 1 \le b \le |s_y| $ (where $ x $ and $ y $ are string indices and $ a $ and $ b $ are positions in strings $ s_x $ and $ s_y $ respectively),
- swap (exchange) the characters $ s_x[a] $ and $ s_y[b] $ .

What is the maximum number of strings you can make palindromic simultaneously?

## 说明/提示

In the first test case, $ s_1 $ is palindrome, so the answer is $ 1 $ .

In the second test case you can't make all three strings palindromic at the same time, but you can make any pair of strings palindromic. For example, let's make $ s_1 = \text{0110} $ , $ s_2 = \text{111111} $ and $ s_3 = \text{010000} $ .

In the third test case we can make both strings palindromic. For example, $ s_1 = \text{11011} $ and $ s_2 = \text{100001} $ .

In the last test case $ s_2 $ is palindrome and you can make $ s_1 $ palindrome, for example, by swapping $ s_1[2] $ and $ s_1[3] $ .

## 样例 #1

### 输入

```
4
1
0
3
1110
100110
010101
2
11111
000001
2
001
11100111
```

### 输出

```
1
2
2
2
```

# AI分析结果

### 中文题目重写

# 二进制回文串

## 题目描述

回文串是指一个字符串 $ t $ 从前往后读和从后往前读是一样的（形式上，$ t[i] = t[|t| + 1 - i] $ 对于所有的 $ i \in [1, |t|] $）。这里 $ |t| $ 表示字符串 $ t $ 的长度。例如，字符串 010、1001 和 0 都是回文串。

你有 $ n $ 个二进制字符串 $ s_1, s_2, \dots, s_n $（每个 $ s_i $ 由 0 和/或 1 组成）。你可以任意交换任意两个字符任意次数（包括零次）。字符可以来自同一个字符串，也可以来自不同的字符串——没有任何限制。

形式上，在一次操作中你可以：

- 选择四个整数 $ x, a, y, b $，使得 $ 1 \le x, y \le n $ 且 $ 1 \le a \le |s_x| $ 和 $ 1 \le b \le |s_y| $（其中 $ x $ 和 $ y $ 是字符串的索引，$ a $ 和 $ b $ 分别是字符串 $ s_x $ 和 $ s_y $ 中的位置），
- 交换字符 $ s_x[a] $ 和 $ s_y[b] $。

你最多可以同时使多少个字符串成为回文串？

## 说明/提示

在第一个测试用例中，$ s_1 $ 已经是回文串，所以答案是 $ 1 $。

在第二个测试用例中，你不能同时使所有三个字符串成为回文串，但你可以使任意两个字符串成为回文串。例如，让 $ s_1 = \text{0110} $，$ s_2 = \text{111111} $ 和 $ s_3 = \text{010000} $。

在第三个测试用例中，我们可以使两个字符串都成为回文串。例如，$ s_1 = \text{11011} $ 和 $ s_2 = \text{100001} $。

在最后一个测试用例中，$ s_2 $ 已经是回文串，你可以通过交换 $ s_1[2] $ 和 $ s_1[3] $ 使 $ s_1 $ 成为回文串。

## 样例 #1

### 输入

```
4
1
0
3
1110
100110
010101
2
11111
000001
2
001
11100111
```

### 输出

```
1
2
2
2
```

### 算法分类
贪心

### 题解分析与结论

本题的核心在于通过交换字符使得尽可能多的字符串成为回文串。由于字符可以任意交换，因此问题转化为如何合理分配字符以满足回文串的条件。主要思路是统计所有字符串中1的总数以及奇数长度字符串的个数，然后根据这些信息判断最多可以形成多少个回文串。

### 所选题解

1. **作者：zhanghapi (赞：4)**
   - **星级：4**
   - **关键亮点：**
     - 通过分类讨论，明确指出了奇数长度和偶数长度字符串在形成回文串时的不同条件。
     - 代码简洁，逻辑清晰，直接统计1的总数和奇数长度字符串的个数，最后根据条件输出结果。
   - **个人心得：**
     - 通过分类讨论，发现奇数长度字符串可以容纳任意数量的1，而偶数长度字符串必须容纳偶数个1，这一发现是解题的关键。

   ```cpp
   #include<cstdio>
   #include<cstring> 
   #include<iostream>
   using namespace std;
   const int maxn=60;
   int q,n;
   char c[maxn];
   int main()
   {
       scanf("%d",&q);
       while(q--)
       {
           scanf("%d",&n);
           int tot=0,sum=0;
           for(int i=1;i<=n;i++){
               cin>>c;
               int l=strlen(c);
               if(l%2) sum++;
               for(int j=0;j<l;j++)
                   if(c[j]=='1') tot++;
           }
           if(tot%2==1){
               if(sum>=1) printf("%d\n",n);
               else printf("%d\n",n-1); 
           }
           else printf("%d\n",n);
       }
       return 0;
   }
   ```

2. **作者：_GW_ (赞：1)**
   - **星级：4**
   - **关键亮点：**
     - 同样通过分类讨论，明确了偶数长度字符串必须由偶数个1组成，而奇数长度字符串则没有限制。
     - 代码结构清晰，统计了1的总数和偶数长度字符串的个数，最后根据条件输出结果。
   - **个人心得：**
     - 通过观察发现，偶数长度字符串必须由偶数个1组成，这一发现是解题的关键。

   ```cpp
   #include  <bits/stdc++.h>
   using namespace std;
   const int N=55;
   int val,n,m,T,res,num;
   string a[N],s;
   int main()
   {
       cin>>T;
       while(T--)
       {
           cin>>n;
           res=num=0;
           for(int i=1;i<=n;i++)
           {
               cin>>a[i];
               if(a[i].size()%2==0)
               {
                   res++;
               }
               for(int j=0;j<a[i].size();j++)
               {
                   if(a[i][j]=='1')
                   {
                       num++;
                   }
               }
           }
           if(num%2==1)
           {
               if(res==n) cout<<n-1<<endl;
               else cout<<n<<endl;
           }
           else
           {
               cout<<n<<endl;
           }
       }
       return 0;
   }
   ```

### 最优关键思路或技巧

- **分类讨论：** 根据字符串长度的奇偶性，分别讨论形成回文串的条件。奇数长度字符串可以容纳任意数量的1，而偶数长度字符串必须容纳偶数个1。
- **统计与判断：** 统计所有字符串中1的总数和奇数长度字符串的个数，根据这些信息判断最多可以形成多少个回文串。

### 可拓展之处

- **类似问题：** 类似的问题可以扩展到其他字符集或更复杂的回文串条件，例如允许某些字符不匹配或允许插入/删除字符。
- **算法套路：** 这种通过统计和分类讨论来解决问题的思路，可以应用于其他需要满足特定条件的字符串处理问题。

### 推荐题目

1. [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)
2. [P1435 [IOI2000]回文字符串](https://www.luogu.com.cn/problem/P1435)
3. [P1042 [NOIP2003 普及组] 乒乓球](https://www.luogu.com.cn/problem/P1042)

---
处理用时：50.67秒