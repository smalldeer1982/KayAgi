# 题目信息

# Row GCD

## 题目描述

You are given two positive integer sequences $ a_1, \ldots, a_n $ and $ b_1, \ldots, b_m $ . For each $ j = 1, \ldots, m $ find the greatest common divisor of $ a_1 + b_j, \ldots, a_n + b_j $ .

## 样例 #1

### 输入

```
4 4
1 25 121 169
1 2 7 23```

### 输出

```
2 3 8 24```

# AI分析结果

【题目内容（中文重写）】
# 行最大公约数

## 题目描述
给定两个正整数序列 $ a_1, \ldots, a_n $ 和 $ b_1, \ldots, b_m $ 。对于每个 $ j = 1, \ldots, m $ ，求出 $ a_1 + b_j, \ldots, a_n + b_j $ 的最大公约数。

## 样例 #1

### 输入
```
4 4
1 25 121 169
1 2 7 23
```

### 输出
```
2 3 8 24
```

【算法分类】数学

【综合分析与结论】
这些题解的核心思路都是利用最大公约数的性质 $\gcd(x,y)=\gcd(x,y - x)$ 对 $\gcd(a_1 + b_j, \ldots, a_n + b_j)$ 进行转化。通过将相邻两项相减消去 $b_j$，得到 $\gcd(a_1 + b_j,a_2 - a_1,a_3 - a_2,\ldots,a_n - a_{n - 1})$，然后预处理出 $a_2 - a_1,a_3 - a_2,\ldots,a_n - a_{n - 1}$ 的最大公约数，对于每个 $b_j$ 只需计算其与 $a_1 + b_j$ 的最大公约数即可。

各题解的主要区别在于代码实现细节，如输入输出方式、gcd 函数的实现方式、对特殊情况（$n = 1$）的处理等。

【所选的题解】
- 作者：dead_X (赞：7)，4星。关键亮点：思路简洁明了，代码实现简洁，对特殊情况处理得当。
- 作者：wgyhm (赞：5)，4星。关键亮点：思路清晰，对公式的推导过程详细，代码注释丰富。
- 作者：Warriors_Cat (赞：2)，4星。关键亮点：思路清晰，对时间复杂度进行了分析，代码结构清晰。

【重点代码】
以 dead_X 的题解为例，核心实现思想：先对 $a$ 数组排序，然后计算相邻元素差值的最大公约数 $t$，对于每个 $b_j$，计算 $a_1 + b_j$ 与 $t$ 的最大公约数并输出。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[1000003],b[1000003];
signed main()
{
	int n=read(),m=read();
	for(int i=1; i<=n; i++) a[i]=read();
	if(n==1)
	{
		for(int x;m--;) x=read(),printf("%lld ",x+a[1]);
		return 0;
	}
	sort(a+1,a+n+1);
	int t=a[2]-a[1];
	for(int i=3; i<=n; i++) t=__gcd(t,a[i]-a[i-1]);
	for(int x;m--;) x=read(),printf("%lld ",__gcd(x+a[1],t));
	return 0;
}
```

【关键思路或技巧】
- 利用最大公约数的性质 $\gcd(x,y)=\gcd(x,y - x)$ 对问题进行转化，将复杂的计算转化为预处理和简单的计算。
- 对特殊情况（$n = 1$）进行单独处理，避免出现错误。

【拓展思路】
同类型题目可能会有更多的变化，例如序列元素为负数、序列长度更大等，但核心思路仍然是利用最大公约数的性质进行转化。类似的算法套路还可以应用于其他需要求多个数的最大公约数的问题中。

【推荐题目】
1. [P1072  Hankson的趣味题](https://www.luogu.com.cn/problem/P1072)
2. [P2152 SDOI2009  SuperGCD](https://www.luogu.com.cn/problem/P2152)
3. [P1579 哥德巴赫猜想（升级版）](https://www.luogu.com.cn/problem/P1579)

【个人心得】
- ZCETHAN：考场上看到 $10^{18}$ 就吓坏了，其实题目很简单，只是坑多。要注意先将 $a$ 从大到小排序，特判 $n = 1$ 和前面的一坨 gcd = 0 的情况，0 不要参与 gcd 的运算，小心 nan。 总结：遇到大数不要慌张，要仔细分析题目，注意特殊情况和边界条件。

---
处理用时：35.96秒