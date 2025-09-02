# 题目信息

# Lord of the Values

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1523B/98f109d71d38cfa25029619d650ed4d2b886de82.png)While trading on his favorite exchange trader William realized that he found a vulnerability. Using this vulnerability he could change the values of certain internal variables to his advantage. To play around he decided to change the values of all internal variables from $ a_1, a_2, \ldots, a_n $ to $ -a_1, -a_2, \ldots, -a_n $ . For some unknown reason, the number of service variables is always an even number.

William understands that with his every action he attracts more and more attention from the exchange's security team, so the number of his actions must not exceed $ 5\,000 $ and after every operation no variable can have an absolute value greater than $ 10^{18} $ . William can perform actions of two types for two chosen variables with indices $ i $ and $ j $ , where $ i < j $ :

1. Perform assignment $ a_i = a_i + a_j $
2. Perform assignment $ a_j = a_j - a_i $

 William wants you to develop a strategy that will get all the internal variables to the desired values.

## 说明/提示

For the first sample test case one possible sequence of operations is as follows:

1. "2 1 2". Values of variables after performing the operation: \[1, 0, 1, 1\]
2. "2 1 2". Values of variables after performing the operation: \[1, -1, 1, 1\]
3. "2 1 3". Values of variables after performing the operation: \[1, -1, 0, 1\]
4. "2 1 3". Values of variables after performing the operation: \[1, -1, -1, 1\]
5. "2 1 4". Values of variables after performing the operation: \[1, -1, -1, 0\]
6. "2 1 4". Values of variables after performing the operation: \[1, -1, -1, -1\]
7. "1 1 2". Values of variables after performing the operation: \[0, -1, -1, -1\]
8. "1 1 2". Values of variables after performing the operation: \[-1, -1, -1, -1\]

For the second sample test case one possible sequence of operations is as follows:

1. "2 1 4". Values of variables after performing the operation: \[4, 3, 1, -2\]
2. "1 2 4". Values of variables after performing the operation: \[4, 1, 1, -2\]
3. "1 2 4". Values of variables after performing the operation: \[4, -1, 1, -2\]
4. "1 2 4". Values of variables after performing the operation: \[4, -3, 1, -2\]
5. "1 3 4". Values of variables after performing the operation: \[4, -3, -1, -2\]
6. "1 1 2". Values of variables after performing the operation: \[1, -3, -1, -2\]
7. "1 1 2". Values of variables after performing the operation: \[-2, -3, -1, -2\]
8. "1 1 4". Values of variables after performing the operation: \[-4, -3, -1, -2\]

## 样例 #1

### 输入

```
2
4
1 1 1 1
4
4 3 1 2```

### 输出

```
8
2 1 2
2 1 2
2 1 3
2 1 3
2 1 4
2 1 4
1 1 2
1 1 2
8
2 1 4
1 2 4
1 2 4
1 2 4
1 3 4
1 1 2
1 1 2
1 1 4```

# AI分析结果

### 题目内容重写

# 价值之主

## 题目描述

在交易过程中，交易员William发现了一个漏洞。利用这个漏洞，他可以改变某些内部变量的值以获取优势。为了试验，他决定将所有内部变量的值从 $a_1, a_2, \ldots, a_n$ 变为 $-a_1, -a_2, \ldots, -a_n$。由于某些未知原因，服务变量的数量总是偶数。

William明白，他的每一个操作都会引起交易所安全团队的更多注意，因此他的操作次数不能超过 $5\,000$ 次，并且在每次操作后，任何变量的绝对值都不能超过 $10^{18}$。William可以对两个选定的变量进行以下两种操作，其中 $i < j$：

1. 执行赋值 $a_i = a_i + a_j$
2. 执行赋值 $a_j = a_j - a_i$

William希望你制定一个策略，将所有内部变量变为目标值。

## 说明/提示

对于第一个样例测试用例，一个可能的操作序列如下：

1. "2 1 2"。操作后的变量值：\[1, 0, 1, 1\]
2. "2 1 2"。操作后的变量值：\[1, -1, 1, 1\]
3. "2 1 3"。操作后的变量值：\[1, -1, 0, 1\]
4. "2 1 3"。操作后的变量值：\[1, -1, -1, 1\]
5. "2 1 4"。操作后的变量值：\[1, -1, -1, 0\]
6. "2 1 4"。操作后的变量值：\[1, -1, -1, -1\]
7. "1 1 2"。操作后的变量值：\[0, -1, -1, -1\]
8. "1 1 2"。操作后的变量值：\[-1, -1, -1, -1\]

对于第二个样例测试用例，一个可能的操作序列如下：

1. "2 1 4"。操作后的变量值：\[4, 3, 1, -2\]
2. "1 2 4"。操作后的变量值：\[4, 1, 1, -2\]
3. "1 2 4"。操作后的变量值：\[4, -1, 1, -2\]
4. "1 2 4"。操作后的变量值：\[4, -3, 1, -2\]
5. "1 3 4"。操作后的变量值：\[4, -3, -1, -2\]
6. "1 1 2"。操作后的变量值：\[1, -3, -1, -2\]
7. "1 1 2"。操作后的变量值：\[-2, -3, -1, -2\]
8. "1 1 4"。操作后的变量值：\[-4, -3, -1, -2\]

## 样例 #1

### 输入

```
2
4
1 1 1 1
4
4 3 1 2```

### 输出

```
8
2 1 2
2 1 2
2 1 3
2 1 3
2 1 4
2 1 4
1 1 2
1 1 2
8
2 1 4
1 2 4
1 2 4
1 2 4
1 3 4
1 1 2
1 1 2
1 1 4```

### 算法分类
构造

### 题解分析与结论

本题的核心在于通过有限的操作次数将数组中的所有元素变为其相反数。由于题目保证 $n$ 是偶数，因此可以将数组中的元素两两配对，通过一系列操作将每对元素变为其相反数。各题解的思路基本一致，都是通过固定的操作序列（如1,2,1,1,2,1）来实现目标。

### 高星题解

#### 题解1：Froranzen (4星)
- **关键亮点**：提出了一个固定的6步操作序列，确保每对元素变为相反数，操作次数为 $3n$，符合题目要求。
- **代码实现**：通过循环对每对元素执行固定的6步操作。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
#define max_(a, b) a > b ? a : b
#define min_(a, b) a < b ? a : b
#define rep(i, f, t) for(register int i(f); i <= t; ++i)
#define per(i, f, t) for(register int i(t); i >= f; --i)
typedef long long ll;

int t, n;
int val[1003];

int main () {
    read(t);
    while(t--) {
        read(n);
        rep(i, 1, n) read(val[i]);
        int ans = n*3;
        outn(ans);
        for(int i(1); i <= n; i += 2) {
            rep(j, 1, 6) {
                if(j & 1) {
                    out(2), out(i), outn(i+1);
                }
                else out(1), out(i), outn(i+1);
            }
        }
    }
}
```

#### 题解2：cmll02 (4星)
- **关键亮点**：同样提出了一个固定的6步操作序列，代码简洁明了。
- **代码实现**：通过循环对每对元素执行固定的6步操作。

```cpp
#include <stdio.h>
#include <string.h> 
#include <algorithm>
#include <queue>
#define od(x) printf("%d",x)
#define odb(x) printf("%d ",x)
#define odl(x) printf("%d\n",x)
#define odp(x,y) printf("%d %d\n",x,y)
#define ol(x) puts("")
#define old(x) printf("%lld",x)
#define oldb(x) printf("%lld ",x)
#define oldl(x) printf("%lld\n",x)
#define oldp(x,y) printf("%lld %lld\n",x,y)

signed main() {
    int T=read();
    while(T--) {
        int n=read();
        for(int i=0;i<n;i++)read();
        printf("%d\n",n*3);
        for(int i=1;i<=n;i+=2) {
            printf("1 %d %d\n",i,i+1);
            printf("2 %d %d\n",i,i+1);
            printf("1 %d %d\n",i,i+1);
            printf("1 %d %d\n",i,i+1);
            printf("2 %d %d\n",i,i+1);
            printf("1 %d %d\n",i,i+1);
        }
    }
    return 0;
}
```

#### 题解3：AK_400 (4星)
- **关键亮点**：详细描述了每步操作后变量的变化，帮助理解操作序列的原理。
- **代码实现**：通过循环对每对元素执行固定的6步操作。

```cpp
// Problem: B. Lord of the Values
// Contest: Codeforces - Deltix Round, Spring 2021 (open for everyone, rated, Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/1523/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <stdio.h>
#include <string.h> 
#include <algorithm>
#include <queue>
#define od(x) printf("%d",x)
#define odb(x) printf("%d ",x)
#define odl(x) printf("%d\n",x)
#define odp(x,y) printf("%d %d\n",x,y)
#define ol(x) puts("")
#define old(x) printf("%lld",x)
#define oldb(x) printf("%lld ",x)
#define oldl(x) printf("%lld\n",x)
#define oldp(x,y) printf("%lld %lld\n",x,y)
//#define int long long
inline int read()
{
	int num=0,f=1;char c=getchar();
	while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
	while(c>47&&c<58)num=num*10+(c^48),c=getchar();
	return num*f;
}
inline int re1d()
{
	char c=getchar();
	while(c<48||c>49)c=getchar();
	return c&1;
}
inline int min(int a,int b){return a>b?b:a;}
inline int max(int a,int b){return a<b?b:a;}
signed main()
{
	int T=read();
	while(T--)
	{
		int n=read();
		for(int i=0;i<n;i++)read();
		printf("%d\n",n*3);
		for(int i=1;i<=n;i+=2)
		{
			printf("1 %d %d\n",i,i+1);
			printf("2 %d %d\n",i,i+1);
			printf("1 %d %d\n",i,i+1);
			printf("1 %d %d\n",i,i+1);
			printf("2 %d %d\n",i,i+1);
			printf("1 %d %d\n",i,i+1);
		}
	}
	return 0;
}
```

### 最优关键思路或技巧
- **固定操作序列**：通过固定的6步操作序列（如1,2,1,1,2,1）将每对元素变为相反数，确保操作次数在限制范围内。
- **分组处理**：将数组中的元素两两配对，分别处理每对元素，简化问题。

### 可拓展之处
- **类似问题**：可以考虑如何处理奇数个元素的情况，或者如何在不改变元素绝对值的情况下进行其他类型的操作。

### 推荐题目
1. [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)
2. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
3. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)

---
处理用时：78.98秒