# 题目信息

# Bargain

## 题目描述

Sometimes it is not easy to come to an agreement in a bargain. Right now Sasha and Vova can't come to an agreement: Sasha names a price as high as possible, then Vova wants to remove as many digits from the price as possible. In more details, Sasha names some integer price $ n $ , Vova removes a non-empty substring of (consecutive) digits from the price, the remaining digits close the gap, and the resulting integer is the price.

For example, is Sasha names $ 1213121 $ , Vova can remove the substring $ 1312 $ , and the result is $ 121 $ .

It is allowed for result to contain leading zeros. If Vova removes all digits, the price is considered to be $ 0 $ .

Sasha wants to come up with some constraints so that Vova can't just remove all digits, but he needs some arguments supporting the constraints. To start with, he wants to compute the sum of all possible resulting prices after Vova's move.

Help Sasha to compute this sum. Since the answer can be very large, print it modulo $ 10^9 + 7 $ .

## 说明/提示

Consider the first example.

Vova can choose to remove $ 1 $ , $ 0 $ , $ 7 $ , $ 10 $ , $ 07 $ , or $ 107 $ . The results are $ 07 $ , $ 17 $ , $ 10 $ , $ 7 $ , $ 1 $ , $ 0 $ . Their sum is $ 42 $ .

## 样例 #1

### 输入

```
107```

### 输出

```
42```

## 样例 #2

### 输入

```
100500100500```

### 输出

```
428101984```

# AI分析结果

### 题目翻译
## 讨价还价

### 题目描述
有时候在讨价还价中达成一致并不容易。现在，萨沙（Sasha）和沃瓦（Vova）无法达成一致：萨沙尽可能高地报出一个价格，然后沃瓦想从价格中删除尽可能多的数字。更详细地说，萨沙报出某个整数价格 $n$，沃瓦从价格中删除一个非空的（连续的）数字子串，剩余的数字填补空缺，得到的整数就是最终价格。

例如，如果萨沙报出 $1213121$，沃瓦可以删除子串 $1312$，结果就是 $121$。

允许结果包含前导零。如果沃瓦删除了所有数字，则价格被视为 $0$。

萨沙想提出一些限制条件，使沃瓦不能直接删除所有数字，但他需要一些论据来支持这些限制条件。首先，他想计算沃瓦操作后所有可能的最终价格的总和。

帮助萨沙计算这个总和。由于答案可能非常大，请将其对 $10^9 + 7$ 取模后输出。

### 说明/提示
考虑第一个样例。

沃瓦可以选择删除 $1$、$0$、$7$、$10$、$07$ 或 $107$。结果分别是 $07$、$17$、$10$、$7$、$1$、$0$。它们的和是 $42$。

### 样例 #1
#### 输入
```
107
```
#### 输出
```
42
```

### 样例 #2
#### 输入
```
100500100500
```
#### 输出
```
428101984
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过计算每个数位对最终答案的贡献来求解。具体来说，将删除子串的情况分为删去当前位前面的数、删去当前位后面的数这两种情况进行讨论。
- **思路对比**：不同题解在具体实现细节上有所差异，如计算贡献的方式、循环的顺序等，但整体都是围绕着按位计算贡献展开。
- **算法要点**：主要是利用组合数学的知识计算删除子串的情况数，以及快速幂、差分等技巧来优化计算过程。
- **解决难点**：难点在于准确计算每个数位在不同删除情况下的贡献，以及处理大数取模的问题。

### 题解评分及选择
- **FutaRimeWoawaSete（6赞）**：4星。思路清晰，代码简洁，直接按位分类讨论计算贡献，易于理解。
- **7KByte（5赞）**：4星。将贡献分两次计算，逻辑明确，时间复杂度为 $O(N)$。
- **Werner_Yin（1赞）**：3星。思路详细，但使用差分数组增加了复杂度，代码理解难度稍大。
- **sodak（0赞）**：3星。通过模拟和递推计算贡献，但代码中使用了较多自定义函数，增加了代码复杂度。
- **jerry3128（0赞）**：3星。按位计算贡献，但代码中包含较多输入输出优化和快速幂的实现，核心逻辑不够清晰。

### 所选题解
- **FutaRimeWoawaSete（4星）**：关键亮点是思路清晰，按位分类讨论，代码简洁易懂。
- **7KByte（4星）**：关键亮点是将贡献分两次计算，不重不漏地统计所有情况，时间复杂度低。

### 重点代码
#### FutaRimeWoawaSete 的代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int Len = 1e5 + 5;
const long long mod = 1e9 + 7;
char s[Len + 5];
long long ans,sum,p = 1;
int main()
{
    scanf("%s",s + 1);
    int lens = strlen(s + 1);
    for(int i = lens ; i >= 1 ; i --)
    {
        long long Now = 1LL * i * (i - 1) / 2;
        ans = (ans + p * (s[i] - '0') % mod * Now % mod) % mod;//只删前面 
        ans = (ans + sum * (s[i] - '0') % mod) % mod;//只删后面 
        sum = (sum + (lens - i + 1) * p % mod) % mod;
        p = p * 10 % mod;
    }
    printf("%lld\n",ans);
    return 0;	
}
```
**核心实现思想**：按位从后往前遍历，分别计算只删前面和只删后面时当前位的贡献，累加得到最终结果。

#### 7KByte 的代码
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define int long long 
#define N 100005
#define P 1000000007
using namespace std;
char s[N];int n,ans,c[N],d[N];
signed main(){
    scanf("%s",s+1);
    n=strlen(s+1);
    int sum=0;
    c[0]=d[0]=1;
    rep(i,1,N-5)c[i]=(c[i-1]*10+1)%P,d[i]=d[i-1]*10%P;
    rep(i,1,n-1){
        sum=(sum*10+s[i]-'0')%P;
        ans+=sum*c[n-i-1]%P;
    }
    sum=0;
    pre(i,n,2){
        sum=(sum+(s[i]-'0')*d[n-i])%P;
        ans+=sum*(i-1)%P;
    }
    printf("%lld\n",ans%P);
    return 0;
}
```
**核心实现思想**：分两次计算贡献，第一次顺序枚举删除区间的左端点，计算左端点左边部分的贡献；第二次倒序枚举删除区间的右端点，计算右端点右边部分的贡献。

### 最优关键思路或技巧
- **按位计算贡献**：将问题转化为计算每个数位对最终答案的贡献，简化了问题的复杂度。
- **分类讨论**：将删除子串的情况分为删去当前位前面的数和删去当前位后面的数，分别计算贡献。
- **取模运算**：在计算过程中及时取模，避免大数溢出。

### 可拓展之处
同类型题可以是计算其他数字操作后的结果总和，如删除数字、插入数字等，都可以考虑按位计算贡献的思路。类似算法套路可以应用在组合数学相关的问题中，通过分类讨论和计算组合数来求解。

### 推荐洛谷题目
- [P1088 火星人](https://www.luogu.com.cn/problem/P1088)：涉及排列组合和递推的思想。
- [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：需要运用数学知识和递推来求解。
- [P2671 [NOIP2015 普及组] 求和](https://www.luogu.com.cn/problem/P2671)：通过按位分类讨论和数学计算来求解。

### 个人心得
题解中未包含个人心得。

---
处理用时：50.29秒