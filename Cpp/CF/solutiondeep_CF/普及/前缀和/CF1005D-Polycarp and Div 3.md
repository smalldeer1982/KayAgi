# 题目信息

# Polycarp and Div 3

## 题目描述

Polycarp likes numbers that are divisible by 3.

He has a huge number $ s $ . Polycarp wants to cut from it the maximum number of numbers that are divisible by $ 3 $ . To do this, he makes an arbitrary number of vertical cuts between pairs of adjacent digits. As a result, after $ m $ such cuts, there will be $ m+1 $ parts in total. Polycarp analyzes each of the obtained numbers and finds the number of those that are divisible by $ 3 $ .

For example, if the original number is $ s=3121 $ , then Polycarp can cut it into three parts with two cuts: $ 3|1|21 $ . As a result, he will get two numbers that are divisible by $ 3 $ .

Polycarp can make an arbitrary number of vertical cuts, where each cut is made between a pair of adjacent digits. The resulting numbers cannot contain extra leading zeroes (that is, the number can begin with 0 if and only if this number is exactly one character '0'). For example, 007, 01 and 00099 are not valid numbers, but 90, 0 and 10001 are valid.

What is the maximum number of numbers divisible by $ 3 $ that Polycarp can obtain?

## 说明/提示

In the first example, an example set of optimal cuts on the number is 3|1|21.

In the second example, you do not need to make any cuts. The specified number 6 forms one number that is divisible by $ 3 $ .

In the third example, cuts must be made between each pair of digits. As a result, Polycarp gets one digit 1 and $ 33 $ digits 0. Each of the $ 33 $ digits 0 forms a number that is divisible by $ 3 $ .

In the fourth example, an example set of optimal cuts is 2|0|1|9|201|81. The numbers $ 0 $ , $ 9 $ , $ 201 $ and $ 81 $ are divisible by $ 3 $ .

## 样例 #1

### 输入

```
3121
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
```

### 输出

```
1
```

## 样例 #3

### 输入

```
1000000000000000000000000000000000
```

### 输出

```
33
```

## 样例 #4

### 输入

```
201920181
```

### 输出

```
4
```

# AI分析结果

### 题目重写

#### 题目描述

Polycarp喜欢能被3整除的数字。

他有一个非常大的数字$s$。Polycarp希望从中切割出尽可能多的能被3整除的数字。为此，他可以在任意相邻数字之间进行任意次数的垂直切割。最终，经过$m$次切割后，将得到$m+1$个部分。Polycarp会分析每个得到的数字，并统计其中能被3整除的数字的个数。

例如，如果原始数字是$s=3121$，那么Polycarp可以通过两次切割将其分成三部分：$3|1|21$。结果，他将得到两个能被3整除的数字。

Polycarp可以进行任意次数的垂直切割，每次切割都在一对相邻数字之间进行。得到的数字不能包含多余的前导零（即，数字可以以0开头，当且仅当该数字恰好是一个字符'0'）。例如，007、01和00099不是有效的数字，但90、0和10001是有效的。

Polycarp最多能得到多少个能被3整除的数字？

#### 说明/提示

在第一个样例中，最优切割方式为3|1|21。

在第二个样例中，不需要进行任何切割。数字6本身就是一个能被3整除的数字。

在第三个样例中，必须在每对相邻数字之间进行切割。结果，Polycarp得到一个数字1和33个数字0。每个数字0都是一个能被3整除的数字。

在第四个样例中，最优切割方式为2|0|1|9|201|81。数字$0$、$9$、$201$和$81$都能被3整除。

#### 样例 #1

##### 输入

```
3121
```

##### 输出

```
2
```

#### 样例 #2

##### 输入

```
6
```

##### 输出

```
1
```

#### 样例 #3

##### 输入

```
1000000000000000000000000000000000
```

##### 输出

```
33
```

#### 样例 #4

##### 输入

```
201920181
```

##### 输出

```
4
```

### 题解分析与结论

#### 综合分析

本题的核心目标是通过切割数字字符串，得到尽可能多的能被3整除的子串。题解中主要采用了贪心和动态规划两种思路。

1. **贪心思路**：通过遍历字符串，累加数字的和，当满足某些条件（如累加和能被3整除、当前数字能被3整除、或累加的数字个数达到3个）时，进行切割并重置累加和。这种思路的时间复杂度为O(n)，较为高效。

2. **动态规划思路**：通过定义状态$f_i$表示前$i$个字符最多能划分出多少个能被3整除的子串，并利用前缀和进行优化。通过观察，发现任何长度大于等于3的子串中必定存在一个能被3整除的子串，因此可以将转移范围缩小到最近的3个位置，从而将时间复杂度从O(n^2)优化到O(n)。

#### 最优关键思路

- **贪心策略**：在遍历字符串时，通过累加和判断是否满足切割条件，尽可能多地切割出能被3整除的子串。这种方法简单高效，适合处理大规模数据。
  
- **动态规划优化**：通过前缀和和状态转移，结合数学结论（任何长度大于等于3的子串中必定存在一个能被3整除的子串），将转移范围缩小到最近的3个位置，显著降低了时间复杂度。

#### 推荐题解

1. **SUPERLWR的贪心解法**（评分：4星）
   - **关键亮点**：通过简单的累加和判断，实现了高效的切割策略，代码简洁易懂。
   - **代码实现**：
     ```cpp
     #include<bits/stdc++.h>
     using namespace std;
     int main() {
         string str;
         cin>>str;
         int len=str.size(),cnt=0,pre=0,ans=0;
         for(int i=0;i<len;i++) {
             pre+=str[i]-'0';
             cnt++;
             if(cnt==3||pre%3==0||(str[i]-'0')%3==0) {
                 ans++;
                 pre=0;
                 cnt=0;
             }
         }
         cout<<ans;
         return 0;
     }
     ```

2. **Diaоsi的动态规划解法**（评分：4星）
   - **关键亮点**：通过数学结论优化了动态规划的转移范围，将时间复杂度从O(n^2)降低到O(n)。
   - **代码实现**：
     ```cpp
     #include<bits/stdc++.h>
     using namespace std;
     const int N=200010,M=2000010,INF=0x3f3f3f3f;
     int n,a[N],f[N],sum[N];
     inline int Max(int x,int y){return x>y?x:y;}
     inline int Min(int x,int y){return x<y?x:y;}
     inline void Swap(int &x,int &y){x^=y^=x^=y;}
     string s;
     int main(){
         cin>>s;
         n=s.size();
         for(int i=1;i<=n;i++)
             a[i]=(int)(s[i-1]-'0'),sum[i]=sum[i-1]+a[i];
         for(int i=1;i<=n;i++)
             for(int j=i;j>=Max(1,i-2);j--)
                 f[i]=Max(f[i],f[j-1]+((sum[i]-sum[j-1])%3==0?1:0));
         printf("%d\n",f[n]);
         return 0;
     }
     ```

3. **wutiruo的动态规划解法**（评分：4星）
   - **关键亮点**：通过前缀和和状态转移，结合数学结论，实现了高效的动态规划解法。
   - **代码实现**：
     ```cpp
     #include<iostream>
     using namespace std;
     int dp[200001],maxv[3]={0,-1,-1};
     int main(){
         string s;
         cin>>s;
         int n=s.size(),r=0;
         s=' '+s;
         for(int i=1;i<=n;i++){
             r=(r+s[i]-48)%3;
             dp[i]=dp[i-1];
             if(maxv[r]!=-1)
                 dp[i]=max(dp[i],dp[maxv[r]]+1);
             maxv[r]=i;
         }
         cout<<dp[n];
         return 0;
     }
     ```

### 扩展思路与推荐题目

#### 扩展思路

- **贪心策略的应用**：在处理字符串或序列问题时，贪心策略常常能够提供高效的解决方案，尤其是在需要最大化或最小化某些条件时。
  
- **动态规划的优化**：通过数学结论或观察，可以优化动态规划的转移范围，从而降低时间复杂度。这在处理大规模数据时尤为重要。

#### 推荐题目

1. **洛谷P1045 最大子段和**（题号：P1045）
   - **考察知识点**：贪心、动态规划
   - **题目链接**：[P1045](https://www.luogu.com.cn/problem/P1045)

2. **洛谷P1216 数字三角形**（题号：P1216）
   - **考察知识点**：动态规划
   - **题目链接**：[P1216](https://www.luogu.com.cn/problem/P1216)

3. **洛谷P1090 合并果子**（题号：P1090）
   - **考察知识点**：贪心、优先队列
   - **题目链接**：[P1090](https://www.luogu.com.cn/problem/P1090)

### 个人心得总结

- **调试经历**：在实现贪心策略时，需要注意边界条件的处理，如最后一个数字是否满足切割条件。
  
- **踩坑教训**：在动态规划中，转移范围的优化需要基于严格的数学证明，否则可能导致错误的结果。

- **顿悟感想**：贪心和动态规划的结合往往能够提供高效的解决方案，尤其是在处理大规模数据时，优化转移范围是关键。

---
处理用时：56.55秒