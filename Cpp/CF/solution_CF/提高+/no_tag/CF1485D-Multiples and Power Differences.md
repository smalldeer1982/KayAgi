# Multiples and Power Differences

## 题目描述

You are given a matrix $ a $ consisting of positive integers. It has $ n $ rows and $ m $ columns.

Construct a matrix $ b $ consisting of positive integers. It should have the same size as $ a $ , and the following conditions should be met:

- $ 1 \le b_{i,j} \le 10^6 $ ;
- $ b_{i,j} $ is a multiple of $ a_{i,j} $ ;
- the absolute value of the difference between numbers in any adjacent pair of cells (two cells that share the same side) in $ b $ is equal to $ k^4 $ for some integer $ k \ge 1 $ ( $ k $ is not necessarily the same for all pairs, it is own for each pair).

We can show that the answer always exists.

## 说明/提示

In the first example, the matrix $ a $ can be used as the matrix $ b $ , because the absolute value of the difference between numbers in any adjacent pair of cells is $ 1 = 1^4 $ .

In the third example:

- $ 327 $ is a multiple of $ 3 $ , $ 583 $ is a multiple of $ 11 $ , $ 408 $ is a multiple of $ 12 $ , $ 664 $ is a multiple of $ 8 $ ;
- $ |408 - 327| = 3^4 $ , $ |583 - 327| = 4^4 $ , $ |664 - 408| = 4^4 $ , $ |664 - 583| = 3^4 $ .

## 样例 #1

### 输入

```
2 2
1 2
2 3```

### 输出

```
1 2
2 3```

## 样例 #2

### 输入

```
2 3
16 16 16
16 16 16```

### 输出

```
16 32 48
32 48 64```

## 样例 #3

### 输入

```
2 2
3 11
12 8```

### 输出

```
327 583
408 664```

# 题解

## 作者：dthythxth_Huge_Brain (赞：11)

题目大意：

> 有一个矩阵 $a$，请你构造一个矩阵 $b$，使得：
>- $0<b_{i,j}\le 10^6$
>- $b_{i,j}$ 是 $a_{i,j}$ 的倍数
>- $b$ 中相邻的两个数的差的绝对值可以写成 $k^4(k\in\mathbb{N}^+)$

>$1\le a_{i,j}\le 16$

由于 $a_{i,j}$ 很小，如果想要满足上列条件，我们可以使初始的 $b_{i,j}$ 是 $1,2,3,\dots,16$ 倍数，即 $\operatorname{lcm}(1,2,3,\dots,16)=720720$，但是还需要满足相邻的两个数的差的绝对值可以写成 $k^4(k\in\mathbb{N}^+)$，不难想到，由于 $720720=a_{i,j}\times t(t\in\mathbb{N}^+)$ 那么根据乘法分配律，令 $k=a_{i,j}$，即可得出结论：

$$
\begin{cases}
  & \text{if}(i+j)\equiv1\pmod2\ b_{i,j}=720720 \\
  & \text{else}\ b_{i,j}=720720\pm a_{i,j}^4
\end{cases}
$$

那么按照其模拟即可。

---

## 作者：jun头吉吉 (赞：7)

## 题意
有一个矩阵 $a$ ,请你构造一个矩阵 $b$ ，使得：
- $0<b_{i,j}\le 10^6$
- $b_{i,j}$ 是 $a_{i,j}$ 的倍数
- $b$ 中相邻的两个数的差的绝对值可以写成 $k^4(k\in\mathbb{N}^+)$

$1\le a_{i,j}\le 16$
## 题解
考虑 $\operatorname{lcm}(1,2,3,\ldots,15,16)=720720$ ,而 $720720>16^4$，并且有 $a_{i,j}|(720720-a_{i,j}^4)$

把整张图黑白染色，黑色为 $720720$，白色为 $720720-a_{i,j}^4$，显然正确
## 代码
```cpp
#include<bits/stdc++.h>
namespace in{
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
	template <typename T>inline void read(T& t){
		t=0;int f=0;char ch=getc();while (!isdigit(ch)){if(ch=='-')f = 1;ch=getc();}
	    while(isdigit(ch)){t=t*10+ch-48;ch = getc();}if(f)t=-t;
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args){read(t);read(args...);}
}
namespace out{
	char buffer[1<<21];int p1=-1;const int p2 = (1<<21)-1;
	inline void flush(){fwrite(buffer,1,p1+1,stdout),p1=-1;}
	inline void putc(const char &x) {if(p1==p2)flush();buffer[++p1]=x;}
	template <typename T>void write(T x) {
		static char buf[15];static int len=-1;if(x>=0){do{buf[++len]=x%10+48,x/=10;}while (x);}else{putc('-');do {buf[++len]=-(x%10)+48,x/=10;}while(x);}
		while (len>=0)putc(buf[len]),--len;
	}
}
using namespace std;
int n,m,a;
signed main(){
	in::read(n,m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			in::read(a),
			out::write(((i+j)&1)?720720:720720-a*a*a*a),
			out::putc(j==m?'\n':' ');
	out::flush();
	return 0;
}
```

---

## 作者：7KByte (赞：4)

肉眼可见 $\rm lcm(a_{i,j})\le10^6$。

所以我们求出所有数的 $\rm lcm$ ，全部填 $\rm lcm$ 可以得到一个所有差为 $0$ 的矩阵。

我们对矩阵黑白染色，相邻格子异色，将所有黑色格子上的数 $+a_{i,j}^4$，即可得到我们想要的矩阵。

本题 $a_{i,j}$ 非常小，很容易让人想偏到枚举所有可能的 $b_{i,j}$ ，但这样过不去。

时空复杂度 $\rm O(nm)$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 505
using namespace std;
int gcd(int x,int y){
	return y?gcd(y,x%y):x;
}
int n,m,a[N][N];
int main(){
	scanf("%d%d",&n,&m);
	int now=1;
	rep(i,1,n)rep(j,1,m)scanf("%d",&a[i][j]),now=now/gcd(now,a[i][j])*a[i][j];
	rep(i,1,n){
		rep(j,1,m)if(1&(i^j))printf("%d ",now);
		else printf("%d ",now+a[i][j]*a[i][j]*a[i][j]*a[i][j]);
		putchar('\n');
	}
	return 0;
}


```

---

## 作者：Ryo_Yamada (赞：3)

对于相邻格这个要求，我们可以想到黑白染色。首先，对每个格子黑白染色。

注意到 $a_i$ 非常小，只有 $16$，对于 $1 \sim 16$ 求 $\text{lcm}$，得到 $720720 < 10^6$。对于每个被染成黑色的格子，我们将其赋值 $720720$。

对于每个被染成白色的格子，它的相邻格全部都是 $720720$，则可以暴力寻找 $\text{abs}\, (b_{i,\,j} - 720720) = k^4$，$k$ 只有 $31$ 种情况，$32^4 > 10^6$。

到这里就结束了，时间复杂度 $O(nm)$。

P.S. 不要用 pow，精度实在太低了，当时被卡了好久，换成 qpow 就过了。。。

$\text{Code}$：

```cpp
int a[505][505];
bool use[505][505];
 
int main() {
	int n, m;
	qread(n, m);
	rep(i, 1, n) rep(j, 1, m) qread(a[i][j]);
	rep(i, 1, n) rep(j, 1, m) use[i][j] = (i + j) & 1;
	rep(i, 1, n) {
		rep(j, 1, m) {
			if(use[i][j]) printf("720720 ");
			else {
				rep(q, 1, 31) {
					int now = qpow(4, q);
					int cha = 720720 - now;
					if(!(cha % a[i][j])) {
						printf("%d ", cha);
						break;
					}
				}
			}
		}
		puts("");
	}
 	return 0;
}
```


---

## 作者：听取MLE声一片 (赞：3)

wqy：基于智商的构造。

给定一个非常奇怪的数字，1 到 16 所有数的最小公倍数 720720，每个数加上这个。

然后是整除还有四次方的问题，我们发现可以对于所有点黑白交错染色，黑色直接把 720720 填上去。对于白色，只需要算 $720720-a_{i,j}^4$ 即可。

关于正确性，因为上面两个数都是 $a_{i,j}$ 的倍数，所以倍数条件满足。又因为是间隔染色，所以保证两个数差的绝对值一定是四次方数。

注意题面是说相邻的，包括上下相邻，所以染色一定要上下行错开。

代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=510; 
const int MAXN=720720;
int n,m,a[N][N],b[N][N];
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[i][j]=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if((i+j)%2==1)
				b[i][j]=MAXN;
			else b[i][j]=MAXN-a[i][j]*a[i][j]*a[i][j]*a[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			cout<<b[i][j]<<' ';
		cout<<endl;
	}
	return 0;
}

```

---

## 作者：FiraCode (赞：1)

## 题解思路：
直接构造确实很难，我们不妨这样想：

我们对一个 $n$ 行 $m$ 列的矩阵，对他黑白染色，那么我们发现一个黑点他上下左右都是白点，然后我们想办法让黑点是相同的值。

那么我们就可以取这 $1$ ~ $16$ 的 $\operatorname{lcm}$ 就可以了，因为 $1 \le a_{i,j} \le 16$ 所以他们的 $\operatorname{lcm}$ 就不是很大。

那么黑色的数构造好了，就差白色点的。

那么白色点就可以：
$$a_{i,j} = \operatorname{lcm} - a_{i , j} ^ 4$$

## AC CODE:
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long ll;
int gcd (int a , int b) {
	return b == 0 ? a : gcd (b , a % b);
}
ll res[20];
int main() {
	ll lcm = 1;
	for (int i = 1; i <= 16; ++ i) {//算lcm，也可以算出来以后直接用就可以了
		ll d = gcd (i , lcm);
		lcm = i / d * lcm;
	}
	for (int i = 1; i <= 20; ++ i) {//打表
		ll x = 1ll * i * i * i * i;//i ^ 4
		ll now = lcm + x;
		for (int j = 1; j <= 16; ++ i) 
			if (now % j == 0) 
				res[j] = now;//算白点的值
	}
	int n , m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			int x;
			cin >> x;
			if ((i + j) & 1) cout << lcm << ' ';//如果是黑点，那么就输出lcm
			else cout << res[x] << ' ';//否则就输出白点的值
		}
		cout << endl;//输出换行
	}
	return 0;//完结散花
}
```
码字不易，求赞！

---

## 作者：11D_Beyonder (赞：1)

###  Idea

&emsp;&emsp;$1\le a_{i,j}\le 16$，而 $1\sim 16$ 的最小公倍数只有 $\mathrm{lcm}=720720$，这就给了启发。

&emsp;&emsp;在 $i+j$ 为偶数的位置填 $\mathrm{lcm}$，否则填 $\mathrm{lcm}+a_{i,j}^4$，即符合题意。

### Code

```cpp
/******************************************************************
Copyright: 11D_Beyonder All Rights Reserved
Author: 11D_Beyonder
Problem ID: CF1458D
Date: 2021 Mar. 3rd
Description: Number Theory, Construction
*******************************************************************/
#include<iostream>
using namespace std;
int main(){
	int n,m;
	const int lcm=720720;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int a;
			cin>>a;
			cout<<(((i+j)&1)?lcm+a*a*a*a:lcm)<<(j==m?'\n':' ');
		}
	}
	return 0;
}
```

---

## 作者：fanfansann (赞：1)

## D - Multiples and Power Differences
**Problem D Multiples and Power Differences**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210213135922483.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTY5Nzc3NA==,size_16,color_FFFFFF,t_70)
**Word**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210213115401422.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210213115433650.png)

**Solution**


签到题


先手玩样例

```cpp
1 2 
2 3
···
6 2 
2 6
```
```cpp
16 16 16
16 16 16
···
16 32 16 
32 16 32
```

发现首先要考虑的是位置对应，所以我们按照奇数偶数分开，奇行偶列，奇行奇列，偶行奇列，偶行偶列，使用位运算可以将他们分开：

```cpp
1 ^ 1 = 0    1 ^ 0 = 1
         ↖ ↗
         ↙ ↘
0 ^ 1 = 1    0 ^ 0 = 0
```

解决了位置放置的问题，再来思考如何求矩阵 $b$。

首先每一个 $b_{i,j}$ 必须是  $a_{i,j}$ 的倍数，并且 $b_{i,j}\le 10^6$，

首先乱搞肯定不行，$b$ 种的每一个数都有要求，必须和相邻的格子差值的绝对值为 $k^4$ ，但是 $k$ 仅需大于 $1$ 即可，没有其他的要求，啥都行，而 $1\le a_{i,j}\le 16$ 所以这就给我们了一个提示， $k$ 的取值根据当前的 $a$ 来决定。

所以我们必须要同时满足：

首先必须是 $a$ 的倍数，然后差值还必须是 $k^4$。

因为要的是差值，我们不好控制这个差值，只有当一个数是固定的，这样我们将另一个数加上 $k^4$ ，这样我们就可以控制这个差值了，再结合上面我们分析样例，发现确实有一些数是可以不变的，所以我们考虑有没有一个数一定是 $a_{i,j}$ 的倍数？而 $b$ 还有限制 ， $b_{i,j}\le 10^6$，需要尽量的小，还要一定是全部的倍数 —— 最小公倍数LCM。其实关键在于 $1\le a_{i,j}\le 16$，给定一个很小的小范围， $b$ 也有范围，这些都是提示呀各位。我们计算发现 $1$ ~ $16$ 的 $LCM=720720\le 10^6$，这样还满足了一定是 $a_{i,j}$ 的倍数，而且还是一个固定的值，这样我们就可以控制两个数的差值，完美！

最后如何控制差值，我们仅需根据最开始奇偶分类，$1$ 为 $LCM$ 。$0$ 呢，想要 $1$ 和$0$ 的差值是 $k^4$ ，而 $k$ 任意，所以我们取 $0$ 位置上的 $a_{i,j}$ 即可，$0$ 的值就是 $LCM+(a_{i,j})^4$。


**Code**


```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>
using namespace std;
typedef long long ll;
typedef int itn;
typedef pair<int, int> PII;
const int N = 3e4 + 7, M = 6e6 + 7, mod = 1e9 + 7;
const ll INF = 1e18 + 7;

int lcm(itn a, int b)
{
    return a / __gcd(a, b) * b;
}
itn n, m, x;
itn main()
{
    scanf("%d%d", &n, &m);
    int LCM = 1;
    for(int i = 1; i <= 16; ++ i) {
        LCM = lcm(LCM, i);
    }
    for(int i = 1; i <= n; ++ i) {
        for(int j = 1; j <= m; ++ j) {
            scanf("%d", &x);
            if(((i ^ j) & 1) == 0)//其实无所谓
                printf("%d ", LCM);
            else printf("%d ", LCM + x * x * x * x);
        }
        puts("");
    }
    return 0;
}
```


---

## 作者：封禁用户 (赞：0)

### 较为简单的构造题   
###### ~~样例有点思路误导~~
我们可以发现， $\operatorname{lcm}(1,2,3,......,16)=720720 $。    
而 $720720<10^{6}$ 的，所以可以黑白染色。  
因为这样保证正确性因为上面两个数都是 $a_{i,j}$ 
 的倍数，所以倍数条件满足。    
而且是间隔染色，所以保证 $\lvert a_{i1,j1}-a_{i2,j2} \rvert$ 一定是四次方数。  
我们填黑块为 $720720$ 白块为 $720720-a_{i,j}^{4}$。    
#### AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int lcm(int x,int y){ return x/__gcd(x,y)*y; }
int n,m,a[505][505],b[505][505],maxval=720720;
int main(){
	scanf("%d%d",&n,&m);
	for (register int i=1;i<=n;i++)
		for (register int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if((i+j)%2==1) b[i][j]=maxval;
			else b[i][j]=maxval-a[i][j]*a[i][j]*a[i][j]*a[i][j];
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++)
			printf("%d ",b[i][j]);
		puts("");
	} return 0;
}
```

---

## 作者：Plozia (赞：0)

宣传博客 $\to$ [link](https://blog.csdn.net/BWzhuzehao/article/details/118185547)

一道思维题。

---------

首先题目上有 $1 \leq b_{i,j} \leq 16$，而要求 $b_{i,j} \mid a_{i,j}$，因此我们可以求一下 $[1,16]$ 内所有整数的 $\operatorname{lcm}$：

$$\operatorname{lcm}(1,2,...,16)=720720<1000000$$

因此我们可以考虑对要求的 $a_{i,j}$ 做一个黑白染色（就类似于国际象棋的棋盘），黑色格子旁边全是白色格子，白色格子旁边全是黑色格子。

对于所有黑色格子，直接填上 720720 就好，对于白色格子，可以考虑暴力枚举差值 $k^4$，然后判断结果是否能够整除 $b_{i,j}$。

由于 $32^4>1000000$，因此复杂度为 $O(31nm)$。

Code：[Github CodeBase-of-Plozia CF1485D Multiples and Power Differences.cpp](https://github.com/Plozia/CodeBase-of-Plozia/blob/main/Codeforces%20%E5%88%B7%E9%A2%98%E5%90%88%E9%9B%86/CF1485D%20Multiples%20and%20Power%20Differences.cpp)

```cpp
/*
========= Plozia =========
    Author:Plozia
    Problem:CF1485D Multiples and Power Differences
    Date:2021/6/22
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 500 + 5;
int n, m, a[MAXN][MAXN], b[MAXN][MAXN], k[MAXN];

int Read()
{
    int sum = 0, fh = 1; char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
    return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

int main()
{
    n = Read(), m = Read();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            a[i][j] = Read();
    for (int i = 1; i <= 31; ++i) k[i] = i * i * i * i;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            if ((i + j) & 1)
            {
                for (int l = 1; l <= 31; ++l)
                {
                    int tmp = 720720 - k[l];
                    if (tmp % a[i][j] == 0) { b[i][j] = tmp; break ; }
                }
            }
            else b[i][j] = 720720;
        }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j) printf("%d ", b[i][j]);
        printf("\n");
    }
    return 0;
}
```

---

## 作者：Little09 (赞：0)

这是一道构造题。这题我在场上想了好久，想什么数论方法……结果这场比赛就这么被我打烂了。

考虑到 $lcm(1,2,3,...,16)=720720<10^6$，所以肯定要利用这个性质。

做法很简单，把图黑白染色，对于一个格子原来的值为 $x$，黑色格子放入 $720720$（因为 $720720$ 必定是 $x$ 的倍数），白色格子放入 $720720-x^4$ （因为 $720720-x^4$ 也必定是 $x$ 的倍数）就行了。

代码简单易懂。

```
	n=read(),m=read();
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			int x=read();
			if ((i+j)%2==0) cout << "720720 ";
			else cout << 720720-x*x*x*x << " ";
		}
		cout << endl;
	}
```


---

## 作者：wgyhm (赞：0)

## D. Multiples and Power Differences

### 题意

给你个 $n$ 行 $m$ 列的矩阵 $a$，构造一个相同大小的矩阵 $b$ 满足：

* $b_{i,j}\le 10^6$
* $b_{i,j}$ 是 $a_{i,j}$ 的倍数。
* $b_{i,j}$ 和四个相邻位置的差的绝对值**分别**等于**非零整数**的四次方。

其中 $1\le a_{i,j}\le 16$

### 题解

有种做人类智慧题的感觉。不过应该是我太菜了。

一个个分析条件。

对于第一个和第二个条件和 $1\le a_{i,j}\le 16$ 时，设 $K=lcm(1,2,3,...,16)=720720$。

再像二分图一样，如果 $i+j$ 为偶数，则 $b_{i,j}=K$，反之 $b_{i,j}=K+(a_{i,j})^4$。

显然是正确的。 

### Code

```cpp
int n,m;
signed main(){
    rg int i,j,x;
    read(n);read(m);
    for (i=1;i<=n;i++,putchar('\n'))
        for (j=1;j<=m;j++)
            read(x),printf("%d ",(i+j)%2?720720:720720+x*x*x*x);
	return 0;
}
```

---

