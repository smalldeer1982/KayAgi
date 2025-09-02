# Mikasa

## 题目描述

给出两个整数 $n$ 和 $m$。请你求出序列 $n \oplus 0,n \oplus 1,\dots,n \oplus m$ 的 $\operatorname{MEX}$。此处 $\oplus$ 是位运算[异或](https://baike.baidu.com/item/%E5%BC%82%E6%88%96)。

一个序列的 $\operatorname{MEX}$ 定义为序列中没有出现的最小的非负整数。例如：$\operatorname{MEX}(0,1,2,4)=3$ 和 $\operatorname{MEX}(1,2021)=0$。

## 说明/提示

$1 \leq t \leq 3\times10^4$

$0 \leq n,m \leq 1\times10^9$

在样例的第一组数据中，序列为 $3 \oplus 0, 3 \oplus 1, 3 \oplus 2, 3 \oplus 3, 3 \oplus 4, 3 \oplus 5$ 即 $3, 2, 1, 0, 7, 6$。其中没有出现的最小的非负整数是 $4$，则序列的 $\operatorname{MEX}$ 为 $4$。

在样例的第二组数据中，序列为 $4 \oplus 0,4 \oplus 1,4 \oplus 2,4 \oplus 3,4 \oplus 4,4 \oplus 5,4 \oplus 6$ 即 $4, 5, 6, 7, 0, 1, 2$。其中没有出现的最小的非负整数是 $3$，则序列的 $\operatorname{MEX}$ 为 $3$。

在样例的第三组数据中，序列为 $3 \oplus 0,3 \oplus 1,3 \oplus 2 $ 即 $3, 2, 1$。其中没有出现的最小的非负整数是 $0$，则序列的 $\operatorname{MEX}$ 为 $0$。

## 样例 #1

### 输入

```
5
3 5
4 6
3 2
69 696
123456 654321```

### 输出

```
4
3
0
640
530866```

# 题解

## 作者：Blunt_Feeling (赞：21)

## CF1554C Mikasa 题解

题意是让我们找出最小的一个自然数 $k$，满足 $k\notin \{n\oplus 0,n\oplus 1,\ldots,n\oplus m\}$。这里的 $n$ 和 $m$ 都是 $10^9$ 级别，我们只能通过位来构造，用 $\log$ 的时间复杂度来过这道题。

由于不可能一个一个枚举，所以这道题要用到异或的一些性质。设 $i\in \{0,1,\ldots ,m \}$，与其让 $n$ 去一个一个异或 $i$，不如构造一个答案，让这个答案不属于这个集合。

$$a\oplus b=c$$
$$\Rightarrow a\oplus c=b$$

根据这个性质，为了使 $n\oplus i \ne k$，其实只要构造出一个 $k$，使得 $n\oplus k \notin \{0,1,\ldots ,m \}$，也就是 $n\oplus k \ge m+1$，接下来就是按位进行构造了。

**从高位到低位**一位一位构造，对于第 $i$ 位，我们可以分四种情况讨论：

1. $n$ 第 $i$ 位为 $1$，$(m+1)$ 第 $i$ 位也为 $1$ 时，$k$ 第 $i$ 位赋为 $0$ 就可以了，因为 $1\oplus 0=1$，$\ge m$ 的同位。

2. $n$ 第 $i$ 位为 $1$，$(m+1)$ 第 $i$ 位为 $0$ 时，$k$ 第 $i$ 位赋为 $0$，因为 $1\oplus 0=1$，$>m$ 的同位；但是 $k$ 的之后**所有位**也都得是 $0$ 了。为什么？因为我们构造的 $k$ 要尽可能小。

3. $n$ 第 $i$ 位为 $0$，$(m+1)$ 第 $i$ 位为 $1$ 时，$k$ 第 $i$ 位赋为 $1$，因为 $0\oplus 1=1$，$\ge m$ 的同位。

4. $n$ 第 $i$ 位为 $0$，$(m+1)$ 第 $i$ 位也为 $0$ 时，$k$ 第 $i$ 位赋为 $0$，因为 $0\oplus 0=0$，$\ge m$ 的同位。

### Code
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
int T,n,m,k;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		bool flag=false;
		k=0; m++; //别忘了++
		Rep(i,31,0)
		{
			if(!flag&&(n&(1<<i)||m&(1<<i))) flag=true; //标记表示遍历到了有效位
			if(!flag) continue;
			if(n&(1<<i))
			{
				if(m&(1<<i)) k<<=1; //左移一位表示后面添上一个0
				else
				{
					Rep(j,i,0) k<<=1; //后面几位都是0
					break; //可以输出了
				}
			}
			else
			{
				if(m&(1<<i)) k=(k<<1)|1; //先左移，再或一下，表示后面添上一个1
				else k<<=1; //左移一位表示后面添上一个0
			}
		}
		cout<<k<<endl;
	}
	return 0;
}
```

记得点赞哦~

---

## 作者：_Fontainebleau_ (赞：8)

### 题意

- 给定两个整数 $n,m$。求序列 $n \oplus 0,n\oplus 1,n\oplus 2,n \oplus 3, \cdots,n\oplus m$ 的 $\operatorname{mex}$。

- 多测
。
- $2\le n,m \le 10^9$。

### 分析

设最终答案为 $k$,由异或的性质可知：$n \oplus k > m$。

令 $p=m+1$，即求最小的 $k$，使 $n\oplus k \ge p$。

我们一位一位考虑。 令 $x_i$ 表示 $x$ 在二进制下的第 $i$ 位。

则共有四种情况。

- case 1： $n_i=p_i=1$，此时 $k_i=0$。
- case 2： $n_i=p_i=0$，此时 $k_i=0$ 即可，因为要满足 $\operatorname{mex}$ 的条件。
- case 3： $n_i=0,p_i=1$，此时 $k_i=1$。
- case 4： $n_i=1,p_i=0$，此时 $k_i=0$，注意此时 $n \oplus k$ 一定大于 $ p$，所以我们可以直接 break 掉。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int tc,n,p;
long long ans;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int main()
{
	tc=read();
	while(tc--)
	{
		n=read(),p=read()+1;
		ans=0;
		for(int i=30;i>=0;i--)
		{
			if((n>>i &1)==1&&(p>>i &1)==0)	break;
			if((n>>i &1)==0&&(p>>i &1)==1)	ans|=1<<i;
		}
		printf("%lld\n",ans);	
	}
	
	return 0;
}

```




---

## 作者：Leasier (赞：5)

题目显然是求一个最小的 $x$，使 $n \operatorname{xor} x > m$。

当 $n > m$，显然答案为 $0$；否则设 $k = m + 1$，$a_i$ 表示 $a$ 在二进制表示下的第 $i$ 位，将原式转换为 $n \operatorname{xor} x \geq k$。

1. 当 $n_i < k_i$

直接令 $x_i = 1$ 即可。

2. 当 $n_i = k_i$

直接令 $x_i = 0$ 即可。

3. 当 $n_i > k_i$

显然已经满足条件，直接 break 即可。

代码：
```cpp
#include <stdio.h>
#include <math.h>

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int n, m, ans = 0;
		scanf("%d %d", &n, &m);
		if (n > m){
			printf("0\n");
			continue;
		}
		m++;
		for (int j = log2(m); j >= 0; j--){
			int x = n >> j & 1, y = m >> j & 1;
			if (x < y){
				ans |= 1 << j;
			} else if (x > y){
				break;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：hytallenxu (赞：1)

## 前言
挺 trick 的 CF 思维题，*1800。

## 正文
题目大意应该还是非常好理解的。

我们来转换一波条件。

首先要注意到异或的一个性质：

$$n \oplus k = x$$

可以推导出

$$n \oplus x = k$$

我们用这个性质直接把题意转换为：**找出最小的非负整数 $k$，使得 $n \oplus k \ge m+1$**。

这个我们可以拆位，从高往低贪心来做。

具体来说，比较 $n,m$ 的每个二进制位，假如在第 $i$ 位**有且仅有**一个 $1$ 的话，就将答案加上 $2^i$，并将 $n$ 加上 $2^i$，直至 $n \ge m$。


## Code
```cpp
#include <bits/stdc++.h>
#ifdef LOCAL
	#include "debug.h"
#else
	#define debug(...) 42
#endif
#define mkp make_pair
#define pb emplace_back
#define endl "\n"
using namespace std;
using ll = long long;
int n,m,t,cnt=0;
constexpr int maxn=1e5+10;

signed main(){
	cin.tie(nullptr)->sync_with_stdio(0);
	cin>>t;
	while(t--){
		int k=0;
		cin>>n>>m;
		m++;
		for(int i=30;i>=0 && n<m;i--){
			if((n>>i)&1 && (m>>i)&1) continue;
			if((n>>i)&1 || (m>>i)&1) k|=(1<<i),n|=(1<<i);
		}
		cout<<k<<endl;
	}
	return 0;
}
```

---

## 作者：wuzihe (赞：1)

本蒟蒻的第一篇题解，如果有什么不足，请dalao轻喷。。。
### 题意
[题目传送门](https://www.luogu.com.cn/problem/CF1554C)

给出两个数 $n$ 和 $m$，求出最小的整数 $p$，使得 $p$ $\notin$ { $n \oplus 1,\ n \oplus 2,\ n \oplus 3,\ \cdots,\ n \oplus m$ } 。

### 思路

#### 异或
先思考这道题之前，还不如先思考这道题目所要用的符号 $\oplus$ 有什么性质。

其中，$\oplus$ 的意思为：两个数在**二进制**状态下，各个数位对齐，位数不够就在前面补零，若两个数位相同就得 $1$，不同就得 $0$。

比如：$12 \oplus 5 = $，列个竖式

$\ \ \ \ 1\ 1\ 0\ 0$

$\oplus\ 0\ 1\ 0\ 1$

$= 1\ 0\ 0\ 1$

$=9$

所以 $12 \oplus 5 = 9$，我们再举个例子：$12 \oplus 9 = $，不难得出答案为 $5$。

因此，我们发现异或的一个性质 $a \oplus b = c$，也可以转换为 $a \oplus c = b$。

#### 解题

经过上面的推导，再看看题目，发现在程序中花括号中的数据可能会毫无规律，而且花括号中都有 $n$，于是我们考虑将式子转换为：$n \oplus p$ $\notin$  { $1,\ 2,\ 3,\ ···,\ m$ }

所以题目就可以转化为求一个最小的整数 $p$，使得 $ n \oplus p > m $。

当然，如果枚举出 $p$，时间肯定承受不了，所以只能构造出 $p$。

##### 分类讨论 ：
- $n_i = m_i = 0$，$p_i = 0$，因为 $p$ 要最小，如果 $p_i = 1$，虽然也能满足 $n \oplus p > m$，但是 $p$ 不是最小的。
- $n_i = 0, m_i = 1$，$p_i = 1$，同上。
-  $n_i = 1, m_i = 0$，$p_i = 0$, 且后面全为零，因为这个数为已经大于 $m_i$ 的这一位了，后面的不管再怎么小也能满足题目要求。
- $n_i = m_i = 1$，$p_i = 0$，同 $1$。

### Code

```
#include <cstdio>
#include <iostream>
using namespace std;

int n, m;

void Main() {
	cin >> n >> m;
	m++;
	int p = 0;
	for (int i = 30; i >= 0; i--) {
		if (((1 & (n >> i)) == 0) && ((1 & (m >> i)) == 1)) p = (1 << i) | p;
		if (((1 & (n >> i)) == 1) && ((1 & (m >> i)) == 0)) break;
	}
	cout << p << endl;
}

int main() {
	int T;
	for (cin >> T; T; T--) Main();
    return 0;
}
```

---

## 作者：123zbk (赞：1)

转移题意。

设最后的答案为 $ans$。所以 $ans\notin \{n\operatorname{xor}0,n\operatorname{xor}1,n\operatorname{xor}2, \cdots ,n\operatorname{xor} m \}$。根据 $a\operatorname{xor} b=c$ 则 $a\operatorname{xor} c=b$ 的结论，$n\operatorname{xor} ans \notin\{0,1,2, \cdots ,m \}$。所以本题就是要求一个 $ans$，使得 $n\operatorname{xor} ans \ge m+1$。

然后思考怎么求。因为 $n,m \le 10^9$，所以只能用 $\log$ 级别的，从高位到低位一位一位构造。一共四种情况。

- $n$ 的第 $i$ 位为 $0$, $m+1$ 的第 $i$ 位为 $1$，那么 $ans$ 的第 $i$ 位为 $1$。

- $n$ 的第 $i$ 位为 $0$, $m+1$ 的第 $i$ 位为 $0$，那么 $ans$ 的第 $i$ 位为 $0$，此时当前位置和 $m$ 相同。

- $n$ 的第 $i$ 位为 $1$，$m+1$ 的第 $i$ 位为 $1$，那么 $ans$ 的第 $i$ 位为 $0$，此时当前位置也和 $m$ 相同。

- $n$ 的第 $i$ 位为 $1$，$m+1$ 的第 $i$ 位为 $0$，那么 $ans$ 的第 $i$ 位为 $0$。此时当前位置大于 $m$，所以后面的所有位置全部是 $0$ 即可。一定可以保证在 $ans$ 最小的情况下使其大于 $m$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T,n,m,ans;
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&m);
		m++;
		ans=0;
		for(int i=30;i>=0;i--)
		{
			if((n>>i&1)==0&&(m>>i&1)==1)
			{
				ans|=(1<<i);
			}
			if((n>>i&1)==1&&(m>>i&1)==0)
			{
				break;
			}
		}	
		printf("%lld\n",ans);
	}	
	return 0;
} 
```

---

## 作者：xh39 (赞：1)

注：请先学习异或相关知识。本题解若看不懂，建议看一下代码。

本题解的代码实现比其它题解更简单(未压行 $252B$)。(实际上借鉴了其它题解)

题意：求最小自然数 $ans$，对于 $0<=i<=m$ 的 $i$ 都满足 $ans≠n\kern{3pt}xor\kern{3pt}i$。(xor 为异或运算)

**将等式两边同时异或 $n$**，可以将 $ans≠n\kern{3pt}xor\kern{3pt}i$ 转换为  $ans\kern{3pt}xor\kern{3pt}n≠i$ 。

因为 $0<=i<=m$ 且所有数都是自然数，所以 $ans\kern{3pt}xor\kern{3pt}n>=m+1$。

那么现在想要找到 $ans$，需要把它们进行拆位，对于每一位，分开考虑。下表标注了当 $n$ 与 $m+1$ 在该二进制位为 $0/1$ 时 $ans$ 的取值。

|n|0|0|1|1|
| -----------: | -----------: | -----------: | -----------: | -----------: |
|$m+1$|$0$|$1$|$0$|$1$|
|$ans$|$0/1$|$1$|$0/1$|$0$|

由于想让 $ans$ 尽可能地小，所以当 $n=0,m+1=0$ 时 $ans=0$ 。

观察上表，只有当 $n=0,m+1=1$ 时，$ans=1$，其余情况下 $ans=0$。$3$ 种情况取 $0$，只有 $1$ 种情况取 $1$，使我们想到了与运算。又发现当 $n=0$，所以 $n$ 要反转。即最后的答案是 ```(~n)^(m+1)```。

但是,还有一种情况没考虑。

当 $n=1,m+1=0$ 时，由于 $n\kern{3pt}xor\kern{3pt}ans$ 在这一位已经大了，在后面无论 $ans$ 的二进制位如何都不会影响大于的性质了。所以**后面的所有位都取 0**。

这其实也简单，找到最大的一位满足上述条件。于是把 $m+1$ 取反后做与运算得到一个新数。再找这个新数的最大位即可。关于找最大位，这里直接暴力枚举。也可以直接使用 cmath 中的 ```log2``` 函数。

时间复杂度(单组数据)：$O(\log_{2}(n+m))$。
```cpp
#include<iostream>
using namespace std;
int fyr(int a){
	int ykb;
	for(ykb=1;ykb<=a;ykb<<=1){}
	return ~(ykb-1); //需要减1取反,因为是要丢弃后面的位,而不是保留,所以后面都将与上0然后被丢弃。
}
int main(){
	int t,i,n,m;
	cin>>t;
	for(i=0;i<t;i++){
		scanf("%d %d",&n,&m);
		cout<<((~n)&(m+1)&(fyr(n&~(m+1))))<<endl;
	}
	return 0;
}
```
其它优化：可以考虑用找最大位二分求解。做到单组数据复杂度  $O(\log_{2}^{2}(n+m))$。

但是这里没必要，因为 $n+m<=2\times 10^{9}$，$\log_{2}(n+m)=31$，$\log_{2}^{2}(n+m)=5$。二分查找常数大一些，其实优化作用较小，还增加了代码难度，在不需要卡常的时候完全没必要。

---

## 作者：Zimse (赞：1)

一道比较有趣的贪心题 QAQ

找 $0$ 到 $m$ 中所有数和 $n$ 的异或值中，最小的没有出现过的数字。

把问题转换一下，找到最小的非负整数 $x$ ，使 $n \bigoplus x > m$ 。

从二进制高位到地位考虑 ， $x_i$ 表示 $x$ 在二进制下第 $i$ 位。

判断每一位时，如果 $n_i=1$ 且 $m_i=1$ ，那么设 $x_i=0$ 。

如果 $n_i=1$ 且 $m_i=0$ ，那么设 $x_i=0$ ,此时已经满足 $n \bigoplus x > m$ ，为了让 $x$ 最小, $x$ 的其他位全设为 $0$ 即可。

如果 $n_i=0$ 且 $m_i=0$ ，那么设 $x_i=0$ 。

如果 $n_i=0$ 且 $m_i=1$ ，那么设 $x_i=1$ 。

此时如果 $n \bigoplus x = m$ ，我们再从低位向高位考虑一边 。

找到最低位使 $n_i=0$ 且 $m_i=0$ 然后设 $x_i=1$ ，后面全修改为零 (修改完第 $i$ 位后面不管多少都满足 $n \bigoplus x > m$)。

一些特殊的地方注意一下特判就可以了。

------------

Code

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>

#define int long long
#define ull unsigned long long

using namespace std;

int read(){int qrx=0,qry=1;char qrc=getchar();
while(qrc<'0'||qrc>'9'){qrc=getchar();if(qrc=='-'){qry=-1,qrc=getchar();break;}}
while(qrc>='0'&&qrc<='9')qrx=qrx*10+qrc-'0',qrc=getchar();return qrx*qry;}

const int N=1e2+7,Mod=998244353,INF=1e9+7;
int T,n,m,b[100];

signed main(){
	T=read();
	b[0]=1;
	for(int i=1;i<=50;i++)b[i]=b[i-1]<<1ll;
	while(T--){
		n=read(),m=read();
		if(m<n){
			printf("0\n");
			continue;
		}
		int s=0,y=0;
		for(int i=40;i>=0;i--){
			if((m&b[i])&&(!(n&b[i])))s|=b[i];
			if((!(m&b[i]))&&(n&b[i])){
				y=1;
				break;
			}
		}
		if(!y){
			for(int i=0;i<=40;i++){
				if((!(m&b[i]))&&(!(n&b[i]))){
					s|=b[i],y=1;
					break;
				}
				else if(s&b[i])s-=b[i];
			}
		}
		
		printf("%lld\n",s);
	}
	return 0;
}
```


---

## 作者：cszhpdx (赞：0)

不懂构造捏。

我们转化一下题目的条件，容易发现，$[0,k]\subseteq\{n \oplus x~|~x\in[0,m]\}$ 的充要条件是 $\max\limits_{0\le i\le k}\{n\oplus i\}\le m$。

充分性必要性都可以根据异或的性质 $n \oplus x=i \iff n \oplus i=x$ 轻松证明。

容易想到可以二分 $k$，计算 $\max\limits_{0\le i\le k}\{n\oplus i\}$，但是发现这个东西并不好算。

换个思路，考虑倍增，假设我们已经求得 $\max\limits_{0\le i\le ima}\{n\oplus i\}$，求 $\max\limits_{0\le i\le ima+2^t}\{n\oplus i\}(2^t<ima)$，如果不大于 $m$ 就使 $ima\leftarrow ima+2^t$ 酱紫。

所以我们只需要求 $\max\limits_{ima\le i\le ima+2^t}\{n\oplus i\}$，容易发现 $ima\le i<ima+2^t$ 其实就是要求 $i$ 前面若干位固定下来是 $ima$，后面 $t$ 位随意设置，这时最大值是显然的。然后再单独算一下 $i=ima+2^t$ 的情况就行了

最后就是记得判断 $m<n$ 的情况就没了。

`code:`
```cpp
#include<bits/stdc++.h>
#define mem(a, x) memset(a, x, sizeof(a))
#define rps(i, b, e) for(int i=(b);i<=(e);i++)
#define prs(i, e, b) for(int i=(e);i>=(b);i--)
#define rpg(i, g, x) for(int i=g.head[x];i;i=g.e[i].nxt)
#define opf(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)
using namespace std;

namespace cszhpdx {
template<class T>
inline void read(T &x) {
	x=0;
	bool f=false;
	char c=getchar();
	while(!isdigit(c))f|=(c=='-'), c=getchar();
	while(isdigit(c))x=x*10+(c-'0'), c=getchar();
	if(f)x=-x;
}
typedef long long LL;
LL n, m;
void work() {
    read(n), read(m);
    if(m<n) {
        puts("0");return;
    }
    LL ima=0, mx=n;
    prs(i, 60, 0) {
        LL o=(1ll<<i);
        //p=max{n^x | x\in (ima,ima+o]}
        LL p=max((n^(ima+o)), (((n>>i)<<i)^ima)+(o-1));
        if(max(p, mx)<=m)mx=max(p, mx), ima+=o;
    }
    printf("%lld\n", ima+1);
}
int main() {
    int T;read(T);
    while(T--)work();
	return 0;
}
}
int main() {
	return cszhpdx::main();
}
```

---

## 作者：wind_whisper (赞：0)

## Description
给出 $n$ 和 $m$，求 $\operatorname{mex}(n\oplus0,n\oplus1,...,n\oplus m)$.
## Solution
题意可以转化为求一个最小的 $x$，使得 $n \oplus x \ge m$.  
容易想到按位贪心，分情况逐位讨论：  
1. 若 $n$ 的当前位是 $1$，则 $x$ 的当前位填 $0$.
2. 若 $n$ 的当前位是 $0$，如果 $m$ 的当前位是 $1$ 或后面的位全是 $1$，则 $x$ 的当前位是 $1$，否则填 $0$.
3. 任何时候，只要 $x\oplus n$ 的当前位是 $1$，且 $m$ 的当前位是 $0$，则可直接跳出循环.

细节上，注意一下 $0$ 的特判即可.
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2e5+100;
const int mod=51061;
const double eps=1e-9;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}


int n,m;
int a[50],b[50],x,y;
ll mi[50],res;

int main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  mi[0]=1;
  for(int i=1;i<=31;i++) mi[i]=mi[i-1]<<1;
  int T=read();
  while(T--){
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    n=read();m=read();
    if(n&&!m){
      printf("0\n");continue;
    }
    int w=n;x=y=-1;
    while(w){
      a[++x]=w&1;w>>=1;
    }
    w=m;
    while(w){
      b[++y]=w&1;w>>=1;
    }
    int mx=max(x,y)+1;res=0;
    for(int k=mx;k>=0;k--){
      if(a[k]){
	if(!b[k]) break;
      }
      else{
	if(b[k]||(m&(mi[k]-1))==mi[k]-1){
	  res+=mi[k];
	  if(!b[k]) break;
	}
      }
    }
    printf("%lld\n",res);
  }
  return 0;
}

```


---

