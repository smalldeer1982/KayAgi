# 题目信息

# [AGC057A] Antichain of Integer Strings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc057/tasks/agc057_a

正整数からなる集合 $ A $ は次の条件を満たすとき、**良い集合**であるといいます。

- 任意の相異なる $ 2 $ 要素 $ a,\ b\ \in\ A $ に対して、$ a $ を $ 10 $ 進法表記した文字列は、$ b $ を $ 10 $ 進法表記した文字列の部分文字列**ではない**。
 
 部分文字列とは？ 部分文字列とは連続する部分列のことを指します。例えば `1`, `12`, `23` は `123` の部分文字列ですが、`21` や `13` は `123` の部分文字列ではありません。 正整数 $ L,\ R $ が与えられます。$ L $ 以上 $ R $ 以下の整数からなる良い集合 $ A $ の要素数の最大値を求めてください。

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- $ 1\leq\ T\leq\ 10^4 $
- $ 1\leq\ L\leq\ R\leq\ 10^{9} $

### Sample Explanation 1

はじめの $ 2 $ つのテストケースについて、例えば次の $ A $ が要素数が最大であるような良い集合となります。 - $ 1 $ つめのテストケース：$ A=\{3,4,5,6,7,8\} $. - $ 2 $ つめのテストケース：$ A=\{3,4,6,8,9,10,11,12,15,17\} $.

## 样例 #1

### 输入

```
3

3 8

3 18

1 1000```

### 输出

```
6

10

900```

# AI分析结果

### 题目内容重写

【题目描述】

正整数集合 $A$ 满足以下条件时，称为**好的集合**：

- 对于任意两个不同的元素 $a, b \in A$，$a$ 的十进制表示字符串不是 $b$ 的十进制表示字符串的子串。

子串是指连续的子序列。例如，`1`、`12`、`23` 是 `123` 的子串，但 `21` 和 `13` 不是 `123` 的子串。

给定正整数 $L$ 和 $R$，求在 $L$ 到 $R$ 之间的整数中，构成好的集合 $A$ 的最大元素数。

有 $T$ 个测试用例，每个测试用例需要输出答案。

### 题解分析与结论

#### 题解对比与评分

1. **QianRan_GG (4星)**
   - **关键亮点**：通过贪心策略，从大数开始考虑，避免小数成为大数的子串。详细讨论了 $l$ 和 $r$ 位数相同和不同时的处理方式，特别是当 $r$ 的最高位为1时的特殊情况。
   - **代码实现**：预处理了10的幂次方，快速计算位数，代码结构清晰，逻辑严谨。
   - **个人心得**：无。

2. **zhangxy__hp (4星)**
   - **关键亮点**：引入了函数 $f(x)$ 表示最小的大于 $x$ 的 $y$，使得 $x$ 是 $y$ 的子串。通过二分查找确定满足条件的集合，思路新颖且高效。
   - **代码实现**：使用了二分查找，代码简洁，逻辑清晰。
   - **个人心得**：无。

3. **MurataHimeko (3星)**
   - **关键亮点**：直接选择位数最多的数，避免了子串问题。讨论了 $l$ 和 $r$ 位数相同和不同时的处理方式，但代码实现较为复杂。
   - **代码实现**：代码逻辑较为复杂，处理边界情况时不够简洁。
   - **个人心得**：无。

4. **SMTwy (3星)**
   - **关键亮点**：从大数开始选择，避免了小数成为大数的子串。讨论了 $r$ 的最高位为1时的特殊情况，但代码实现较为复杂。
   - **代码实现**：代码逻辑较为复杂，处理边界情况时不够简洁。
   - **个人心得**：无。

#### 最优关键思路与技巧

- **贪心策略**：从大数开始选择，避免小数成为大数的子串。
- **二分查找**：通过二分查找确定满足条件的集合，提高效率。
- **预处理**：预处理10的幂次方，快速计算位数，优化代码实现。

#### 可拓展之处

- **类似问题**：可以扩展到其他进制或更复杂的字符串匹配问题。
- **算法套路**：贪心策略和二分查找在其他最大化或最小化问题中也有广泛应用。

#### 推荐题目

1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

### 所选高星题解

#### QianRan_GG (4星)

```cpp
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
int lg[15]; // 用于快速求出n位的最小数即10的n - 1次方
signed main()
{
	int t; scanf("%lld", &t);
	//预处理
	lg[1] = 1;
	for(int i = 2; i <= 12; ++ i)
		lg[i] = lg[i - 1] * 10;
	for(int i = 1; i <= t; ++ i)
	{
		int l, r;
		scanf("%lld%lld", &l, &r);
		int x = l, y = r, s1 = 0, s2 = 0; //s1是l的位数，s2是r的位数
		//求出位数
		while(x) s1 ++ , x /= 10;
		while(y) s2 ++ , y /= 10;
		if(s1 == s2) printf("%lld\n", r - l + 1); //位数相同时
		else
		{
			if(r / lg[s2] == 1) printf("%lld\n", r - max(r % lg[s2], max(r / 10, l - 1)));
			//r最高位是1时                              后s2 - 1位   前s2 - 1 位  l的值
			else printf("%lld\n", r - lg[s2] + 1);
		}
	}
}
```

#### zhangxy__hp (4星)

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline
#define read(x){\
	char ch;\
	int fu=1;\
	while(!isdigit(ch=getchar()))\
		fu-=(ch=='-')<<1;\
	x=ch&15;\
	while(isdigit(ch=getchar()))\
		x=(x<<1)+(x<<3)+(ch&15);\
	x*=fu;\
}
#define int ll
using namespace std;
namespace asbt{
namespace cplx{bool begin;}
const int pw10[]={
1,
10,
100,
1000,
10000,
100000,
1000000,
10000000,
100000000,
1000000000,
10000000000,
100000000000};
il int len(int x){
	int res=0;
	do{
		res++,x/=10;
	}while(x);
	return res;
}
il int f(int x){
	return min(x*10,x+pw10[len(x)]);
}
namespace cplx{
	bool end;
	il double usdmem(){return (&begin-&end)/1048576.0;}
}
signed main(){
	int T;
	read(T);
	while(T--){
		int l,r,L,R;
		read(l)read(r);
		L=l,R=r;
		while(l<r){
			int mid=(l+r)>>1;
			if(f(mid)>R){
				r=mid;
			}
			else{
				l=mid+1;
			}
		}
		printf("%d\n",R-l+1);
	}
	return 0;
}
}
signed main(){return asbt::main();}
```

---
处理用时：50.85秒