# Cirno's Perfect Bitmasks Classroom

## 题目描述

> 就算是很简单的问题，她一定也答不上来。——《东方求闻史纪》   

琪露诺的完美位运算教室开始了！    
琪露诺给了她的学生一个正整数 $x$，作为作业题，她的学生需要找到一个满足以下两个条件的，最小的正整数 $y$。
- $x \operatorname{and} y>0$     
- $x \operatorname{xor} y>0$ 

这里的 $\operatorname{and}$ 和 $\operatorname{xor}$ 都是位运算。      
她的学生米斯蒂娅对这个问题束手无策，请你来帮帮她。

## 样例 #1

### 输入

```
7
1
2
5
9
16
114514
1000000```

### 输出

```
3
3
1
1
17
2
64```

# 题解

## 作者：Failure_Terminator (赞：4)

## Solution

题意可以转化成以下内容：

给定一个正整数 $x$，求一个在二进制表示形式下与 $x$ 至少有一位不同，至少有一位相同为 1 的正整数 $y$。

可以知道，$y$ 的大小至少为 $\operatorname{lowbit}{(n)}$。

关于 $\operatorname {lowbit}$ 运算，可以看下面的代码注释。

确定了范围之后，我们只需要一个一个向后推，找到合适的输出即可。

另外还有一种对于每次操作都可以达到 $O(1)$ 的方法，请参考[这里](https://codeforces.com/blog/entry/103493)或楼下。

## AC Code

这里采用第一种方法。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
int lowbit(int x){return x&(-x);}
int main()
{
	cin>>T;
	while(T--){
		scanf("%d",&n);
		int t=lowbit(n);
		while(!(t^n && t&n)) t++;
		printf("%d\n",t);
	}
	return 0;
}
```

### 代码注释：lowbit运算

这个函数可以求出正整数 $x$ 的二进制表达式中最低位的 $1$ 所对应的值。

假设一个数 $x$ 的二进制最低位的 $1$ 在从右往左数的第 $k$ 位，那么它的 $\operatorname {lowbit}$ 值就是 $2^{k-1}$。

$\operatorname {lowbit}$ 函数推导过程：

$$\operatorname{lowbit}(n) = n\ \&\ (\sim n + 1) = n\ \& (-n) $$

By **haimo**

---

## 作者：708151_qwq (赞：3)

[题面传送门](https://www.luogu.com.cn/problem/CF1688A)

# 题意简述

给定一个正整数 $x$，求满足下列条件的最小的 $y$。

* $x$ $\text{and}$ $y>0$

* $x$ $\text{xor}$ $y>0$

# Solution

$\text{and}$ 为按位与运算，$\text{xor}$ 为按位异或运算。

通过这两种运算的性质，易知 $x$ 和 $y$ 在二进制表示法下最少有一位相同（与）、最少有一位不同（异或）。

如果 $x$ $=1$，则对应的 $y$ 最小为 $3$。

`if(x==1) y=3;`

如果 $x \geq 2$：

1. 如 $x$ 为奇数，则对应的 $y$ 最小为 $2$。

1. 如 $x$ 为偶数，则：

***
* 若 $x$ 在二进制下每位上 $1$ 的个数大于 $1$，说明 $y=\text{lowbit}(x)$ 与 $x$ 至少有一位不同，且此时 $y$ 最小。

* 若 $x$ 在二进制下每位上 $1$ 的个数等于 $1$，说明 $y=\text{lowbit}(x)$ 与 $x$ 完全相同，为了让他们不同，末位改成 $1$ 就可以了。
***

**分割线内的内容 By [$\texttt{chenjunxiu}$](/user/419144) 奆佬。~~蒟蒻太蒻了，想不出来~~**

# AC Code

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
long long lowbit(long long x) {return x&(-x);}
int main() {
	int n; scanf("%d",&n);
	for(int i=0; i<n; i++) {
		long long x; scanf("%lld",&x);
		if(x==1) printf("3\n");
		if(x%2==1&&x!=1) printf("1\n");
		if(x%2==0) {
			if(lowbit(x)==x) printf("%lld\n",x+1);
			else printf("%lld\n",lowbit(x));
		}
	}
	return 0;
}
```
By 2022.6.10 蒟蒻的第七篇题解

---

## 作者：Southern_Dynasty (赞：2)

分类讨论。

当 $x=1$ 时，输出 $3$ 就行了。

如果这个数的二进制位只有一个 $1$，输出 $n+1$ 即可（因为其不是 $1$，说明它在二进制位下的 $1$ 不是最右边的，这时只需要加一就可以同时保证**与**和**异或**都大于 $0$）。

用 `__builtin_popcount(x)` 来求出 $x$ 在二进制位下 $1$ 的个数。

那么如果 $x$ 在二进制位下至少有两个 $1$，输出 $\text{lowbit(x)}$ 就行了。

代码：

```cpp
#include<bits/stdc++.h>
#define gt getchar
#define pt putchar
#define y1 y233
//#define int long long
typedef long long ll;
//typedef __int128 lll;
typedef unsigned long long ull;
using namespace std;
#define endl "\n"
#define lowbit(x) x&-x
struct FastIO{
	static const int SIZE=1<<14;
	inline char gc(){
		static char buf[SIZE],*begin=buf,*end=buf;
		return begin==end&&(end=(begin=buf)+fread(buf,1,SIZE,stdin),begin==end)?EOF:*begin++;
	}
	inline int read(){
    	int x=0,f=1;char ch=gt();
    	while(!isdigit(ch)){if(ch=='-')f=-1;ch=gt();}
    	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=gt();}
		return x*f;
	}
	inline void print(ll x){
    	if(x<0)pt('-'),x=-x;
    	if(x>9)print(x/10);
    	pt(x%10+48);
	}
	inline void println(ll x){
		print(x);
		pt('\n');
	}
}io;
#define read io.read
#define print io.print
#define println io.println
#define gc io.gc
int T,x;
signed main(){
	T=read();
	while(T--){
		x=read();
		if(x==1){println(3);continue;}
		if(__builtin_popcount(x)==1)println(x+1);
		else println(lowbit(x));
	}
	return 0;
}
```


---

## 作者：linyuhuai (赞：1)



[题目传送门](https://codeforces.com/contest/1688/problem/A) & [前往 blog 获得更好的阅读体验](https://by505244.github.io/oi_blogs/2022/06/04/CF1688A%E9%A2%98%E8%A7%A3/)

### 题意：

给定 $x$，找出满足

$$x\ \texttt{and}\ y>0$$ 
$$x\ \texttt{xor}\ y>0$$ 

的最小正整数 $y$。


------------


### 思路：

- $x\ \texttt{and}\ y>0$ 显然是 $(x)_2$ 和 $(y)_2$ 在二进制下至少有一位相同。

- $x\ \texttt{xor}\ y>0$ 显然是 $(x)_2$ 和 $(y)_2$ 在二进制下至少有一位不同。

考虑到 $y$ 的值要最小，那么不难发现 $(y)_2$ 与 $(x)_2$ 在相同的的位数仅有 $1$ 位且为 $(x)_2$ 最低位。

在前面分析的基础上，再来看第二个条件。$(x)_2$ 中最低位的 $1$ 与 $(y)_2$ 中最低位的 $1$ 相同并抵消，但如果 $(x)_2$ 中有不止一个 $1$，那么与 $(y)_2$ 就至少有 $1$ 位不同，满足第二个条件。反之，就将其加上 $1$，使其至少有 $1$ 位不同。（**特别的，当 $x=1$ 时，$y=3$**）

```cpp
void solve(){
    int n;
    scanf("%d",&n);
    if(n==1){
        printf("3\n");
        return;
    }
    int maxn=0,minn=-1;
    for(int i=0;i<=31;i++){
        int a=n>>i;
        if(a&1){
            maxn=i;
            if(minn==-1)minn=i;
        }
    }
    if(maxn!=minn)printf("%d\n",1<<minn);
    else printf("%d\n",(1<<minn)+1);
}
```

---

## 作者：luckydrawbox (赞：1)

## 题意

给出一个正整数 $x$，求出一个最小的正整数 $y$，使得 $x\text{ and }y>0$ 且 $x\text{ xor }y>0$。

## 分析

根据按位与和按位异或的性质，题目的两个条件可以理解为 $x,y$ 在二进制表示下至少有一位相同 $(\text{and})$，至少有一位不同 $(\text{xor})$。

显然最小的正整数为 $1$，我们从 $1$ 的角度出发，可以发现以下两个性质：

- 若 $x=1$，根据样例可以得到 $y$ 最小为 $11_{(2)}$。
- 若 $x$ 为大于 $1$ 的奇数，$y$ 最小为 $1_{(2)}$，因为此时 $y$ 末尾必与 $x$ 相同且其他位有不同的。

然后考虑 $x$ 为偶数时的解法。

为了让 $y$ 尽可能小，我们让它与 $x$ 重合的那位尽可能小，易知 $x$ 二进制的最低位为 $\text{lowbit}(x)=\texttt{x\&-x}$，那么：

- 若 $x$ 在二进制下每位上 $1$ 的个数大于 $1$，说明 $y=\text{lowbit}(x)$ 与 $x$ 至少有一位不同，且此时 $y$ 最小。
- 若 $x$ 在二进制下每位上 $1$ 的个数等于 $1$，说明 $y=\text{lowbit}(x)$ 与 $x$ 完全相同，为了让他们不同，末位改成 $1$ 就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int t;
int main(){
	t=read();
	while(t--){
		ll n=read();
		if(n==1)
			puts("3");
		else if(n&1)
			puts("1");
		else{
			if((n&-n)==n)
				write(n+1);
			else
				write(n&-n);
			puts("");
		}
	}
	return 0;
}
```

---

## 作者：yinhy09 (赞：0)

第一次打夜间 CF 比赛，正赶上 Wdoi 超级良心思维场。本人 CF newbie 都差点过掉 D，差点就上绿了 qwq

话不多说，开始讲题：

## 思维讲解：

本题首先如果 $n=1$ 或者 $n=2$，那么输出 $3$。

其次，如果这个数的二进制位只有一个 $1$，那么就不可能有两位使得 and 和 xor 的值都不为零。所以我们就需要在前面再加一位，也就是变成 $n+1$。

如果不只有一个 $1$，那么只需要输出他的最低位 $1$ 即可。

## qwq~AC CODE：

```cpp
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _rep(i,a,b) for(int i=(a);i<(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define _per(i,a,b) for(int i=(a);i>(b);i--)
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define endl printf("\n")
ll read()
{
	char c;
	ll x=0;
	int f=1;
	c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
void write(ll x)
{
	if(x>9)write(x/10);
	putchar(x%10+'0');
	return;
}
ll T,n,ans,tot;
ll a(ll n)
{
	ll sum=0;
	while(n)
	{
		sum+=n%2;
		n>>=1;
	}
	return sum;
}
int main(){
	T=read();
	while(T--)
	{
		tot=1,ans=0;
		n=read();
		if(n==1||n==2)
		{
			printf("3\n");
			continue; 
		} 
		if(a(n)==1)
		{
			printf("%lld\n",n+1);
		}
		else
		{
			printf("%lld\n",(n&(-n)));
		}
	}
	return 0;
}
//Author:yinhy09,luogu user-id:575320
//Date:2022.6.3
//question ID:Codeforces1688A
```


---

## 作者：SUNCHAOYI (赞：0)

首先暴力肯定是不行的，对于一个 $x=2^k$ 的数一定会被卡到超时。

由于题目寻找最小的数 $y$ 符合 $x \ \mathrm{and}\ y > 0$ 且 $x\ \mathrm{xor}\ y > 0$，不难想到先用 $\mathrm{lowbit}$ 找到符合 $x\ \mathrm{xor}\ y > 0$ 的 $y$。发现只要 $x ≠ y$，显然也满足前者的条件。值得注意的是，当 $x = 1$ 时的答案比较特殊，因此特判即可。

因此，我们分为三类考虑，得到最终的代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int t,n,m;
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	t = read ();
	while (t--)
	{
		n = read ();
		if (n == 1)
		{
			printf ("3\n");
			continue;
		}
		m = n & (-n);
		if (m == n) ++m;
		printf ("%d\n",m);
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}

```

---

## 作者：Daniel2020 (赞：0)

### 题目大意:

给一个正整数 $x$ ，求 $y_{min}$ 使 $x \operatorname{and} y > 0$ 且 $x \operatorname{xor} y>0$ 。

$\operatorname{and}$ 和 $\operatorname{xor}$ 都是位运算。

### 解题思路:

既然题目与位运算有关，那么不妨将 $x$ 用二进制表示。

首先我们考虑如何满足条件 $x \operatorname{and} y > 0$ 。

根据与运算的定义，$x$ 和 $y$ 的二进制表示中至少需要有同一位为 $1$ ，所以 $y$ 至少为 $\text{lowbit}(x)$ （ $x$ 的二进制表示中最低位的 $1$ 表示的值）时，才可以满足此条件。

那么 $y$ 有没有可能更大呢？这时就需要分类讨论了。

1.	$x$ 的二进制表示中有多个 $1$ ：

因为此时 $y = \text{lowbit}(x)$ 时，即使其他位上都填 $0$ ，$x \operatorname{xor} y$ 也会因为 $x$ 的其它位上有 $1$ 而大于 $0$ ，所以此时 $y_{min} = \text{lowbit}(x)$ 。

如 $x = 10$ 时，$y_{min} = \text{lowbit}(x) = 2$ 。

```
Example #1：
x = 10 -> 1010
y = 2  -> 0010
x&y = 0010 , x^y = 1000
```

2.	$x$ 的二进制表示中只有一个 $1$ ，且 $x \neq 1$ ：

此时我们需要在其它位上填 $1$ ，使 $x \operatorname{xor} y > 0$ 。

因为 $x$ 可以表示为 $x = 2^k (k \in N^{* })$ ，显然 $x$ 的二进制表示的最低位为 $0$ ，所以在最低位上填 $1$ 最优，即 $y_{min} = \text{lowbit}(x)+1$ 。 

如 $x = 8$ 时，$y_{min} = \text{lowbit}(x)+1 = 8+1 = 9$ 。

```
Example #2：
x = 8 -> 1000
y = 9 -> 1001
x&y = 1000 , x^y = 0001
```

3.	$x = 1$ ：

此时 $x$ 的二进制表示的最低位已经为 $1$ ，特判可知 $y_{min} = 3$ 。

请各位神犇自行推导，以便更好理解此题。

### AC 代码:

```cpp
#include<bits/stdc++.h>
#define f(x) (x&(-x)) /*lowbit(x)*/ 
using namespace std;
int n,t;
int main()
{
	scanf("%d",&t);
	for(;t;--t)
	{
		scanf("%d",&n);
		printf("%d\n",f(n)+!(n-f(n))+!(n-1));
		/*x = 1 时，y 恰好等于 lowbit(x)+1+1*/
	} 
   	return 0;
} 
```

---

## 作者：Noby_Glds (赞：0)

### 思路：
我们可以把 $x$ 分为两种情况。

$1$，换成二进制形式后只有一个 $1$。
```latex
十进制：8  二进制：00001000
```
$2$，换成二进制形式后有多个 $1$。
```latex
十进制：5  二进制：00000101
```
#### 第一种情况：
这种数归纳起来就是 $2$ 的整数次方和 $1$。

对于前者，加 $1$ 输出就行了。

但对于 $1$，这是个特殊情况，$2$ 是不符合条件的，得输出 $3$。
#### 第二种情况：
因为这种数化为二进制至少有两个 $1$，所以我们找到这个数的 lowbit，输出它就行了。
### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x;
int lowbit(int x){return x&-x;}
signed main(){
	cin>>n;
	while(n--){
		cin>>x;
		if(x==1) cout<<"3\n";
		else if(lowbit(x)==x) cout<<lowbit(x)+1<<endl;
		else cout<<lowbit(x)<<endl;
	}
	return 0;
} 
```


---

