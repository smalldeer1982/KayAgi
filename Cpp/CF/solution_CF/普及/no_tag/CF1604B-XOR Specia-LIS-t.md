# XOR Specia-LIS-t

## 题目描述

给定一个长度为 $n$ 的序列 $a_1,a_2,\dots,a_n$，能否将这个序列分成几段，使每一段的最大上升子序列的长度的异或和等于 $0$。

## 说明/提示

$1\le t\le10^4,2\le n\le10^5,2\le \sum n\le3\times10^5,1\le a_i\le10^9$。

## 样例 #1

### 输入

```
4
7
1 3 4 2 2 1 5
3
1 3 4
5
1 3 2 4 2
4
4 3 2 1```

### 输出

```
YES
NO
YES
YES```

# 题解

## 作者：让风忽悠你 (赞：6)

[原题](https://www.luogu.com.cn/problem/CF1604B)

## 题意

给出一个长度为 $n$ 的序列，要求将其分为几段，使每一段的最长上升子序列的长度的抑或和为 0。

## 做法

不难想到，序列中的每个元素都可以看作一个子段，且此时最长上升子序列就是它本身，所以长度为 1。那么当序列长度为偶数时，必然可以使最长上升子序列的长度的抑或和为 0。

接着考虑长度为奇数的情况，类比长度为偶数的情况，可以想到只需要构建一个长度为 2 的子段，使其无法单调递增，此时子段的最长上升子序列长度就为 1。所以当长度为奇数时，只需要判断是否存在 $a_i \le a_i-1$。

## 代码

```cpp
#include<cstdio>
#include<algorithm>
#define N 100005

using namespace std;

int T,n;
int a[N];

int main(){
	scanf("%d",&T);
	while(T--){
		bool fl=0;
		scanf("%d",&n);
		if(n%2==0) fl=1; // 判断长度奇偶 
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(a[i]<=a[i-1]) fl=1; // 判断是否存在 a[i]<=a[i-1] 
		}  
		if(fl) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```


---

## 作者：Coros_Trusds (赞：2)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15590921.html)

# 题目大意

给出一个长度为 $n$ 的整数序列 $a$，将其划分为 $k$ 个连续子串。

设 $h_1, h_2, h_3...h_k$ 是每个子串的最长上升字序列的长度。

求是否有一种划分方式使得 $h_1 \oplus h_2 \oplus h_3 \oplus ... \oplus h_n = 0$。

有则输出 `YES`；否则输出 `NO`。

# 题目分析

妙题。

$h_1 \oplus h_2 \oplus h_3 \oplus ... \oplus h_n = 0$，可以转化成 $h_1=h_2=\cdots=h_{n-1}=h_n$（也可以转化成其他形式，但这样非常方便）。

当 $n$ 为偶数时，可将每个数单独拎出来，显然符合题目要求，直接输出 `YES`。（此时 $h_1=h_2=\cdots=h_{n-1}=h_n=1$，$h_1\oplus h_2\oplus \cdots \oplus h_n=0$）

当 $n$ 为奇数时，如果发现 $a_{i-1}\ge a_i$，那么如果这两个放一组，这一组必然不会出现长度不等于 $1$ 的最长上升子序列，再把其它数各自分成一组，就转换成了偶数的情况，直接输出 `YES`。

否则说明该序列为严格递增序列，不可能满足要求，输出 `NO`。

# 代码

```cpp
//2021/11/18

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <cstdio>

#include <climits>//need "INT_MAX","INT_MIN"

#include <cstring>

#define enter() putchar(10)

#define debug(c,que) cerr<<#c<<" = "<<c<<que

#define cek(c) puts(c)

#define blow(arr,st,ed,w) for(register int i=(st);i<=(ed);i++)cout<<arr[i]<<w;

#define speed_up() std::ios::sync_with_stdio(false)

#define endl "\n"

namespace Newstd
{
	inline int read()
	{
		char c;
		bool flag=false;
		while((c=getchar())<'0' || c>'9')
		{
		    if(c=='-') flag=true;
		}
		int res=c-'0';
		while((c=getchar())>='0' && c<='9')
		{
		    res=(res<<3)+(res<<1)+c-'0';
		}
		return flag?-res:res;
	}
	inline void print(int x)
	{
		if(x<0)
		{
			putchar('-');x=-x;
		}
		if(x>9)
		{
			print(x/10);
		}
		putchar(x%10+'0');
	}
}

using namespace Newstd;

using namespace std;

const int ma=100005;

int a[ma]; 

int T,n;

inline void init()
{
	memset(a,0,sizeof(a));
}

int main(void)
{
	T=read();
	
	while(T--)
	{
		init();
		
		n=read();
		
		for(register int i=1;i<=n;i++)
		{
			a[i]=read();
		}
		
		if(n%2==0)
		{
			puts("YES");
			
			continue; 
		}
		
		bool mark=false;
		
		for(register int i=1;i<n;i++)
		{
			if(a[i]>=a[i+1])
			{
				mark=true;
				
				break;
			}
		}
		
		if(mark==true)
		{
			puts("YES");
		}
		
		else
		{
			puts("NO");
		}
	}
	
	return 0;
}
```

---

## 作者：xw_qwq (赞：1)

## CF1604B XOR Specia-LIS-t
[题目传送门-洛谷](https://www.luogu.com.cn/problem/CF1604B)

[题目传送门-cf](http://codeforces.com/problemset/problem/1604/B)

### 题目思路
~建议评橙。~

很简单的一道分类讨论的题。

不难发现，当 $n$ 为偶数时，我们可以把数列中所有数全部分开来，可以发现所有子序列的最长上升子序列的长度都为 $1$，且因为 $n$ 为偶数，异或和等于 $0$，成立。

当 $n$ 为奇数时，我们可以尝试找到一个长度为 $2$ 的上升子序列，若可以这题就转化成了偶数情况，成立。
### code

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005];
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n, f = 1;
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		if (!(n % 2)) //偶数
		{
			cout << "YES\n";
			continue;
		}
		for (int i = 2; i <= n; i++)
			if (a[i] <= a[i - 1]) //是否存在上升序列
			{
				cout << "YES\n";
				f = 0;
				break;
			}
		if (f) //判断
			cout << "NO\n";
	}
	return 0;
}
```

---

## 作者：orz_z (赞：1)

### 题目大意

给出一个长度为 $n$ 的整数序列 $a$，将其划分为 $k$ 个连续子串。

设 $h_1, h_2, h_3...h_k$ 是每个子串的最长上升字序列的长度。

求是否有一种划分方式使得 $h_1 \oplus h_2 \oplus h_3 \oplus ... \oplus h_n = 0$。

$t$ 组数据。

对于 $100\%$ 的数据，$1 \leq t \leq 10000$，$2≤n≤10^5$，$1 \le a_i \le 10^9$。

### 解题思路

显然，当 $n$ 为偶数时，每个数都可自分一组，即 $k=n$ 且 $\forall 1 \leq i \leq k,h_i = 1$，满足题意。

当 $n$ 为奇数时，若可以找到一组 $a_{i-1} \geq a_i$ 时，那么可以将 $a_{i-1}$ 和 $a_i$ 分成一组，其他每个数自分一组，此时 $k=n-1$ 为 偶数且 $\forall 1 \leq i \leq k,h_i = 1$，，满足题意。

如果找不到一组 $a_{i-1} \geq a_i$，说明 $a$ 单调递增，那么无论如何都会有奇数个 $h_i$ 为奇数，此时必然无解。

具体见代码。

### CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

int T, n;

int a[100007];

signed main()
{
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d", &n);
		for(int i = 1 ; i <= n; ++i) scanf("%d", &a[i]);
		if(n % 2 == 0)
		{
			puts("YES");
			continue;
		}
		int flag = 0;
		for(int i = 2; i <= n; ++i)
		{
			if(a[i - 1] >= a[i]) flag = 1;
		}
		if(flag)
		{
			puts("YES");
		}
		else
		{
			puts("NO");
		}
	}
	return 0;
}
```



---

## 作者：vvauted (赞：1)

## Description

给出长为 $n$ 的序列 $a$，求是否可以将其分成若干个子段使得每段的最长上升子序列长度的异或和为 $0$。

## Solution

我们把每个 $a_i$ 单独分一段，那么每一段 $a_i$ 的最长上升子序列长度都为 $1$，如果 $n$ 为偶数，偶数个 $1$ 异或起来肯定为 $0$；对于 $n$ 为奇数的情况，我们尝试把一对 $a_i,a_{i+1}$ 合并到一段，使得 $a_i\ge a_{i-1}$ ，这样的一段最长上升子序列长度还是为 $1$，那么 $n-1$ 个 $1$ 异或起来则也为 $0$。当然，如果无法找出这样一段则不能完成要求。

## Code
```
#include <stdio.h>
#define Maxn 100005
 
int a[Maxn], n, t, tag;
 
int main() {
	scanf("%d", &t);
	while(t --) { 
		tag = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; ++ i) scanf("%d", &a[i]);
		if(!(n & 1)) { //判断是否为偶数
			printf("YES\n");
		} else {
			for(int i = 1; i < n; ++ i) if(a[i] >= a[i + 1]) tag = 1; // 判断是否有逆序段
			if(tag) printf("YES\n");
			else printf("NO\n");
		}
	}
}
```


---

## 作者：XL4453 (赞：1)

### 解题思路：

首先发现如果序列的长度为偶数，那么一定有解。直接将每一个数字都拆下来就行了。

否则就需要考虑是否可能有将某两个放在一起而使得贡献还是  $1$，显然只需要判断一下是否存在一个 $a_{i}\le a_{i-1}$ 就行了。

若有，自然就能够造出一组解，但反之，是否一定无解呢？

---
由于不存在任何一组的 $a_{i}\le a_{i-1}$ 这也就说明整个 $a$ 数组是单调增的。

由此，可以知道，如果取一个长度为 $k$ 的区间，那么这个区间的贡献直接就是 $k$。

到这里，这个问题就显然了，由于 $n$ 为奇数，所以 $n$ 转成二进制后最后一位一定为 1，所以就不存在方案使得划分后和为 $n$ 的同时最后一位的异或为 $0$。


---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int T,n,a[100005];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		if(n%2==0){
			printf("YES\n");
			continue;
		}
		int flag=1;
		for(int i=1;i<=n;i++){
			if(a[i-1]>=a[i]){
				printf("YES\n");
				flag=0;
				break;
			}
		}
		if(flag)printf("NO\n");
	}
	return 0;
}
```


---

## 作者：naroto2022 (赞：0)

# CF1604B 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/CF1604B)

### 题意

给定一个长度为 $n$ 的数组 $a$，将 $a$ 分成若干段，问是否有一种分段的方法使得每一段的最大上升子序列的长度的异或和为 $0$。

有多组数据。

### 前置知识

1. 位运算，知道异或算法相同为假，不同为真，理解并能够运用 $1\oplus 1=0$。
2. 数学归纳法（证明思路的时候会用到）。

### 思路（做法）

1. 当 $n$ 为偶数时，显然只需将 $a$ 分成 $n$ 段，每一段一个数字即可。这样每一段的最大上升子序列的长度为 $1$，且有偶数个段，因为 $1\oplus 1=0$，所以最终得到的结果也必为 $0$。
2. 当 $n$ 为奇数时，如果还是像上面这种简单粗暴的方法来构造的话，结果必定为 $1$（因为 $n$ 为奇数）。所以就想到，要是有一个 $i(i\in[1,n-1])$，使得 $a_i\leqslant a_{i+1}$，的话，则把 $a_i,a_{i+1}$ 放在一组，其余的一个数一组，这样的话，$a_i,a_{i+1}$ 这一组的最大上升子序列的长度为 $1$，总共有偶数个 $1$ 异或，则结果为 $1$。若不存在这样的 $i$，则无解。

### 思路正确性的证明

其实，上面的输出 `YES` 的方法不多说，不懂的话再看看题目，现在要证明为什么不存在 $i(i\in[1,n-1])$ 使得 $a_i\leqslant a_{i+1}$ 的话就无解。

首先，我们知道，要是不存在这样的 $i$，则 $a$ 为一个上升序列，所以不管怎么分段，分的那一段最大上升子序列的长度必定就为那一段的长度，那么就有以下证明：

#### 引理：若有正整数 $a,b$，则 $a\oplus b$ 的结果的奇偶性与 $a+b$ 的结果的奇偶性相同。

引理证明：

设 $a,b$ 在二进制表达下的最后一位分别为 $a',b'(a',b'\in\{0,1\})$，则有以下两种情况：

1. $a'=b'$，则由异或的运算规则，$a\oplus b$ 的结果为偶数，又由加法的运算规则，$a+b$ 的结果也为偶数。所以两者奇偶性相同。
2. $a'\neq b'$，则由异或的运算规则，$a\oplus b$ 的结果为奇数，又由加法的运算规则，$a+b$ 的结果也为奇数。所以两者奇偶性相同。

综上，$a\oplus b$ 的结果的奇偶性与 $a+b$ 的结果的奇偶性相同。

证毕。

回到证明思路的正确性，咱们设每一段的最大上升子序列的长度为 $b$ 数组，一共分成了 $m$ 段。则 $b_1+b_2+b_3+\cdots+b_m=n$ 且为奇数。

由引理，$b_1\oplus b_2$ 奇偶性与 $b_1+b_2$ 相同。

同理，$(b_1\oplus b_2)\oplus b_3$ 奇偶性与 $(b_1+b_2)+b_3$ 相同。（把 $b_1+b_2$ 看成一个整体。）

由数学归纳法得，$b_1\oplus b_2\oplus b_3\oplus \cdots\oplus b_n$ 奇偶性与 $b_1+b_2+b_3+\cdots+b_m$ 相同。

所以，$b_1\oplus b_2\oplus b_3\oplus \cdots\oplus b_n$ 为奇数。

而 $0$ 为偶数，所以这种情况必定输出 `NO`。

证毕。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
long long T,n,a[100005];
bool flag;
int main(){
	scanf("%lld",&T);//多组数据 
	while(T--){
		flag=false;//初始化 
		scanf("%lld",&n);
		if(n%2==0) flag=true;//直接可以 
		for(int i=0; i<n; i++){
			scanf("%lld",&a[i]);
			if(i&&a[i]<=a[i-1]) flag=true;//这也是可以的 
		}
		if(flag) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
} 
```

---

## 作者：_O_v_O_ (赞：0)

诈骗。

首先，当 $n$ 为偶数时，我们可以把 $a$ 中每个数切成一段，这样，$a$ 中每一段长度都为 $1$，其 $\operatorname{LIS}$ 长度也为 $1$，而偶数个相同的数的异或和为 $0$。

当 $n$ 为奇数时，我们可以找到一个 $i$，满足 $a_{i-1}>a_i$，把 $a_i$ 和 $a_{i+1}$ 分在一起，其它的还是每个数切成一段，仍能分成偶数段且每段 $\operatorname{LIS}$ 长度为 $1$.

否则，无解。

---

## 作者：智子 (赞：0)

## 题意

给出一个长度为 $n$ 的整数序列 $a_1, a_2, a_3...a_n$，将其划分为 $k$ 个连续子串，$h_1, h_2, h_3...h_k$ 则是每个子串的最长上升字序列的长度。求是否有一种划分方式使得 $h$ 的异或和 $h_1 \oplus h_2 \oplus h_3  \oplus ... \oplus h_n = 0$。

## 思路

如果 $n$ 是偶数，那么我们可以将原序列 $a$ 划分为 $n$ 个子序列，每个子序列的长度为 1，$h_i = 1$，异或和当然为 0。

如果 $n$ 是奇数，那么我们可以找到一个 $a_{i - 1} \geq a_i$，将其合并为一个子序列，总共有偶数段，也满足$h_i = 1$，异或和也为 0。如果找不到 $a_{i - 1} \geq a_i$，说明这个序列单调递增，此时无解，因为无论如何都肯定会有奇数个 $h_i$ 为奇数（整数的奇偶性）。

## 代码

```cpp
#include<cstdio>
using namespace std;

const int MAXN = 100000 + 5;

int a[MAXN];
int n;

int main() {
    int T;

    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        if(n % 2 == 0) {
            printf("YES\n");
            continue;
        }
        bool flag = false;
        for(int i = 2; i <= n; i++) {
            if(a[i - 1] >= a[i]) {
                flag = true;
                break;
            }
        }
        if(flag) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}
```

---

## 作者：Shunpower (赞：0)

考场上想出了近似做法，可惜没有实现出来。

## 题意

有 $t$ 组数据，每组都是一个有 $n$ 个元素的序列 $a$，考虑将此序列分割成若干段。假设第 $i$ 段的 LIS（最长上升子序列）长度为 $h_i$，请问是否有一种分割方式使得 $h_1 \oplus h_2\oplus\dots$ 的值为 $0$？

数据范围 $1\leqslant t\leqslant10000$，$2\leqslant n\leqslant10^5$，所有 $n$ 之和不超过 $3\cdot 10^5$。

## 思路

肯定不能每次暴力分割，所以考虑 LIS 的性质。

- 一个单调不升序列的 LIS 一定是 $1$。
- 一个元素的序列的 LIS 一定是 $1$。

再很容易想到，一堆 $1$ 异或起来，答案不是 $1$ 就是 $0$。偶数个 $1$ 异或，答案就是 $0$；奇数个 $1$ 异或，答案是 $1$，再来一个 $1$ 答案就能变成 $0$。

所以对于 $n\bmod 2=0$ 的情况一定有解（每个元素单独成一段），而对于 $n\bmod 2=1$ 的情况，考虑把两个元素合为一段，剩下的元素还是单独成段。若合起来的两个元素刚好构成一个单调不升序列就有解，否则无解。

## 代码

数学题的好处就是想清楚了代码很精简。

```
//solve 函数的主体
cin>>n;
for(int i=1;i<=n;i++){
	cin>>a[i];
}
if(n%2==0){//偶数元素一定有解
	puts("YES");
	return;
}
else{
	for(int i=2;i<=n;i++){
		if(a[i-1]>=a[i]){//判断是否可以组成单调不升序列
			puts("YES");//有两个元素能组成就有解
			return;
		}
	}
	puts("NO");//如果组成不了单调不升序列就没有解
	return;
}
```

## AC 记录

[AC 链接](https://codeforces.com/contest/1604/submission/134230535)

---

