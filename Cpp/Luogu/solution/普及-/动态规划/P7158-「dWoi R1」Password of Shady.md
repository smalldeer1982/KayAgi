# 「dWoi R1」Password of Shady

## 题目背景

天海兰太郎被杀后，最原看到图书架后面刷卡器里的尘土并没有消散，陷入了沉思 ……

最原在想，黑幕是如何做到刷卡器的尘土没有消散但是还成功进入了黑幕的房间呢？然后他再次确认了刷卡器，发现了一个密码盘，密码盘下写着一行文字「真正的秘密总是被谎言欺骗，但黑幕不至于欺骗自己」，然后还有一道题，于是最原要用 1min 的时间解出这道题。

## 题目描述

这道题要求最原构造一个 $n$ 位数，并且满足以下两个要求：

- 「强者从不说废话」，代表着这个数没有前导零，$0$ 没有前导零且是一位数。
- 「强者善于成 $k$ 对合作」，代表着这个数的所有数位中有偶数个 $k$，$0$ 是偶数。

最原很快就让入间制作了一个造数器，但是造数器还需要输入有多少个满足要求的数，于是他就求助于了你，因为做造数器已经用了 59.5s，所以他想让你 0.5s 求出有多少个符合要求的数。

答案对 $998\ 244\ 353$ 取模。

## 说明/提示

#### 样例 1 解释

第一组数据，满足要求的数为：

- $0$ 个 $3$，$10\sim 12$，$14 \sim 22$，$24 \sim 29$，$40 \sim 42$，$44 \sim 52$，$54 \sim 62$，$64 \sim 72$，$74 \sim 82$，$84 \sim 92$，$94\sim 99$。
- $2$ 个 $3$，$33$。

第二组数据的样例解释写了 114514 行，但赛前 0.1s 不小心被黑白熊偷走了，书虫来不及补了。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（5 pts）：$n=1$。
- Subtask 2（25 pts）：$n \le 6$。
- Subtask 3（25 pts）：$t \le 100$。
- Subtask 4（45 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n \le 10^5$，$1 \le k \le 9$，$1 \le t \le 10^6$。

---

后续：你用 0.5s 求出了答案，并且答案正确，但是最原将构造出的数输入密码盘发现错误了，所以这件事是一个谎言，最原还要去搜集言弹打学级裁判（

## 样例 #1

### 输入

```
2
2 3
11 4```

### 输出

```
73
842367440```

# 题解

## 作者：一只书虫仔 (赞：33)

![](https://cdn.luogu.com.cn/upload/image_hosting/zxxf3qro.png)

$$\color{Orange}\sf dWoi\ Round\ 1\ B\  Password\ of\ Shady$$

#### Description

> 求有多少个 $n$ 位无前导零的数满足所有数位中有偶数个 $k$。       
> $1 \le n \le 10^5$，$1 \le k \le 9$，$1 \le t \le 10^6$

#### Subtask 1

约束条件：$n=1$。

一位数只有 $0 \sim 9$，$1 \le k \le 9$，所以肯定输出 $9$。

#### Subtask 2

约束条件：$n \le 6$。

留给了爆搜或者写挂没开 long long 的正解。

~~然后发现暴力貌似是 $\mathcal O(t9^n)$ 或者 $\mathcal O(t+9^n)$ 的~~

#### Subtask 3

约束条件：$t \le 10^5$。

考虑动态规划。

对于一个满足要求的 $i$ 位数，可以由一个不满足要求的 $i-1$ 位数加上一位 $k$ 或者由一个满足要求的 $i-1$ 位数加上一位除了 $k$ 之外的数位得来，同理，对于一个不满足要求的 $i$ 位数，可以由一个满足要求的 $i$ 位数加上一位 $k$ 或者由一个不满足要求的 $i-1$ 位数加上一位除了 $k$ 之外的数得来。

因此我们可以开两个数组 $f[i],g[i]$，$f[i]$ 构造满足要求的 $i$ 位数，$g[i]$ 构造不满足要求的 $i$ 位数，按照我们上面分析的，转移方程也就出来了：

$$f[i]=f[i-1] \times 9+g[i-1]$$
$$g[i]=g[i-1] \times 9+f[i-1]$$

对于初值，注意特判 $0$，$f[1]=8,g[1]=1$。

另外，$n=1$ 时也要特判。

然后你就得到了 $\mathcal O(tn)$ 的优秀解法，~~但并 A 不了~~。

你也可以尝试矩阵快速幂，听 lgd 说是 $\mathcal O(t \log n)$，~~但好像也 A 不了。~~

#### Subtask 4

考虑初始化，把 $1 \sim 10^5$ 的答案提前初始化到输出 $ans[i]$ 里，然后每次循环输入 $n$ 直接输出 $ans[n]$ 即可。

然后你就得到了 $\mathcal  O(t+n)$ 的优秀 AC 做法。

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

unsigned long long f[100005];
unsigned long long g[100005];

int main () {
    int t;
    scanf("%d", &t);
    f[1] = 8, g[1] = 1;
    for (int i = 2; i <= 100000; i++) {
        f[i] = f[i - 1] * 9 + g[i - 1];
		g[i] = g[i - 1] * 9 + f[i - 1];
        f[i] %= 998244353;
        g[i] %= 998244353;
    }
    while (t--) {
        int n, k;
        scanf("%d%d", &n, &k);
        if (n == 1) {
            puts("9");
            continue;
        }
        printf("%llu\n", f[n] % 998244353);
        continue;
    }
    return 0;
}
```

---

## 作者：SSerxhs (赞：9)

~~dp 是啥，完全不会啊~~

不妨设 $f(n)$ 表示允许前导 $0$ 的 $n$ 位数答案，套路容斥 $ans=f(n)-f(n-1)$ 

又显然 $f(n)=\sum\limits_{2|i\land i\ge0}^n\tbinom{n}{i}9^{n-i}$ 

表示选择了 $i$ 个 $k$ 的情况

那么考虑

$(9+1)^n=\sum\limits_{i=0}^n\tbinom{n}{i}9^{n-i}$

$(9-1)^n=\sum\limits_{i=0}^n\tbinom{n}{i}(-1)^i 9^{n-i}$

两式相加易得 $f(n)=\dfrac{10^n+8^n}{2}$
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int p=998244353;
const int N=1e6+2,inv2=p+1>>1;
int c,fh;
inline void read(int &x)
{
	c=getchar();fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
int t,n,i,j,x;
int mi[N],mii[N];
int cal(int x)
{
	return (ll)(mi[x]+mii[x])*inv2%p;
}
int main()
{
	mi[0]=mii[0]=1;
	for (i=1;i<N;i++) mi[i]=(ll)mi[i-1]*10%p,mii[i]=(ll)mii[i-1]*8%p;
	read(t);
	while (t--)
	{
		read(n);read(x);
		printf("%d\n",n==1?9:(cal(n)-cal(n-1)+p)%p);
	}
}
```

---

## 作者：WsW_ (赞：4)

双倍经验：[SP6172 OAE - OAE](https://www.luogu.com.cn/problem/SP6172)  
正题：  
递推式： $f[i]=f[i-1]\times9+g[i-1]$ ， $g[i]=g[i-1]\times9+f[i-1]$ 。  
为什么呢？因为在上一个答案中，任意添加0至9中除 $k$ 任意一个数都会产生一种新答案，所以 $f[i-1]\times9$ ，但是对上一个无效答案添加一个 $k$ 就会有产生一组有效答案，所以要 $+g[i-1]$ 。  
而对于无效答案，任意添加0至9中除 $k$ 任意一个数都会产生一种新的无效答案，所以 $g[i-1]\times9$ ，但是对上一个答案添加一个 $k$ 就会有产生一组无效答案，所以要 $+f[i-1]$ 。  
你可能会发现这题解和我[这题的题解](https://www.luogu.com.cn/problem/SP6172)基本一样，毕竟……双倍经验吗！
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,t,len=2,f[1000004],g[1000006];
signed main(){
	f[1]=8;//8种答案
	g[1]=1;//有1个无效答案
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		if(!(n-1)){
			puts("9");
			continue;
		}
		if(f[n])printf("%d\n",f[n]);//如果以前存过，就输出
		else{//不然就更新数组找答案。
			for(;len<=n;len++){
				f[len]=(f[len-1]*9+g[len-1])%998244353;
				g[len]=(g[len-1]*9+f[len-1])%998244353;
			}
			printf("%d\n",f[n]);
		}
	} 
	return 0;
}
```

---

## 作者：卷王 (赞：2)

比较有意思的一题。

## 题目大意

求没有前导 $0$ 且有偶数个 $k$ 的 $n$ 位数的数量。（题意很简单是不是？）

## 思路

**核心算法：** 动态规划

我们设 $ok_i$ 是满足题目要求的 $i$ 位数，$no_i$ 是不满足题目要求的 $i$ 位数。

橙题的转移都是很简单的，我们慢慢寻找两个数组的关系。
（请读者仔细思考）

经过简单的分析，可以得出 $ok_i=(ok_{i-1}×9+no_{i-1})$，$no_i=(no_{i-1}×9+ok_{i-1})$，正好是反着的。

这样 dp 就被我们如此简单的解决了。

初始化挺好写，见代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mod 998244353
int T, n, k;
ll ok[100007], no[100007];
inline int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
int main()
{
	T = read();
	ok[1] = 8; no[1] = 1;
	for(int i = 2; i <= 100000; i++)
	{
		ok[i] = (ok[i - 1] * 9 + no[i - 1]) % mod;
		no[i] = (no[i - 1] * 9 + ok[i - 1]) % mod;
	}
	while(T--)
	{
		n = read(), k = read();
		if(n == 1) { printf("9\n"); continue; }
		printf("%ld\n", ok[n]);
	}
	return 0;
}
```

---

## 作者：_lfxxx_ (赞：2)

**题目传送门：[P7158 「dWoi R1」Password of Shady](https://www.luogu.com.cn/problem/P7158)**
### 前言：
这题可以说是比较经典的 DP 初步题目了。~~当然也可以用数学方法。~~
### 思路：
因为 $1-9$ 这几个数字其实都一样，所以 $k$ 没卵用。

令 $f_{0,i}$ 表示 $n$ 位数时有偶数个 $k$ 的方案数， $f_{1,i}$ 表示 $n$ 位数时有奇数个 $k$ 的方案数。

那么可以得到
$$f_{0,i}\gets f_{0,i-1}\times9+f_{1,i-1}$$
$$f_{1,i}\gets f_{1,i-1}\times9+f_{0,i-1}$$
（保持奇偶性不变只需加上不等于 $k$ 的数，共 $9$ 个。若变化，则只能加上 $k$ 这一个数）

其中， $f_{0,1}=8,f_{1,1}=1$ 。（首位不能为 $0$ ，所以是 $8$）

当 $n=1$ 时，则答案为 $9$ 。（首位可以为 $0$ ，因为就是 $1$ 位数）

否则，答案为 $f_{0,n}$ 。
### 注意事项：
要使用输入输出较快的方法并且开 `long long` 。
### 代码：
因为要调用答案很多遍，所以提前算好。
```cpp
#include<cstdio>
int f[2][100005];
const int mod=998244353;
int main(){
	f[0][1]=8;f[1][1]=1;
	for(int i=2;i<=100000;i++){
		f[0][i]=(f[0][i-1]*9+f[1][i-1])%mod;	
		f[1][i]=(f[1][i-1]*9+f[0][i-1])%mod;
	}
	int t,n,k;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		if(n==1)
			puts("9");
		else
			printf("%d\n",f[0][n]);
	}
	return 0;
}
```
### 后记：
`2021-07-04` ：修改多处笔误。

---

## 作者：LikAzusa_ (赞：1)

## 题目描述：

题目要求构造 $n$ 位数，其中没有前导零（ $0$ 没有前导零而且是一位数）。这个数中含有偶数个 $k$ （ $0$ 是偶数）。求出符合要求的 $n$ 位数的数量。

## 思路：

本题我们考虑DP。

设 $f1[i]$ 为 $i$ 位数中满足要求的数的数量， $f2[i]$ 为 $i$ 位数中不满足要求的数的数量。

则转移方程为 $f1[i]=f1[i-1]*9+f2[i]$ 和 $f2[i]=f2[i-1]*9+f1[i]$ 。

看到这里，相信很多人就要问了：

#### 为什么呢？？

对于一个满足了要求的 $i$ 位数，是不是可以由一个满足要求的 $i-1$ 位数后加上一位0~9之中除了 $k$ 的任何一个数，或者由一个不满足要求的 $i-1$ 位数后加上一位 $k$ 构成。对于前者，0~9中十个数，去掉 $k$ 还剩九个，因此由原来满足要求的 $i-1$ 位数构成满足要求的 $i$ 位数就有 $f1[i-1]*9$ 个；对于后者，因为原来不满足要求，加上一位 $k$ 就可满足要求，因此由原来不满足要求的 $i-1$ 位数构成满足要求的 $i$ 位数就有 $f2[i-1]$ 个。

综上所述， $f1[i]=f1[i-1]*9+f2[i-1]$ 。

而对于一个不满足要求的 $i$ 位数，可以由一个不满足要求的 $i-1$ 位数后加上一位0~9之中除了 $k$ 的任何一个数，或者由一个满足要求的 $i-1$ 位数后加上一位 $k$ 构成。由原来不满足要求的 $i-1$ 位数构成不满足要求的 $i$ 位数就有 $f2[i-1]*9$ 个；由原来满足要求的 $i-1$ 位数构成不满足要求的 $i$ 位数就有 $f1[i-1]$ 个。

综上所述， $f2[i]=f2[i-1]*9+f1[i-1]$ 。

初始化： 

$f1[1]=8$ （因为数字中不能有前导零，所以转移时要把 $0$ 去掉，不能出现 $01$ 、 $02$ 等情况；同时要把 $k$ 去掉，因为奇数个 $k$ 是不满足要求的）
    
$f2[1]=1$ （这一个数为 $k$ ）


### 但是！！

我们要特判 $1$ 位数的情况，满足要求的有0~9十个数中去除 $k$ 一个数就是9个数，因此当输入的 $n$ 为 $1$ 时，直接输出 $9$ 就可以了。

### 注意：

每次转移后都对 $998244353$ 取模。

先读入再进行DP的时间复杂度是 $O(tn)$ ，~~A不了~~。

所以我们要先处理出 $1e5$ 的数据，后面读入后直接输出就行了。

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read() {
	int x=0;
	int f=1;
	char c=getchar();
	while(c<'0' || c>'9') {
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9') {
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}//快读

const int maxn=1e5+5;
const int mod=998244353;//mod直接定义为常数
int n,k;
int t;
long long f1[maxn];
long long f2[maxn]; 

int main()
{
	t=read();
	f1[1]=8;f2[1]=1;//初始化
	for(int i=2;i<=100005;i++)//预处理
	{
		f1[i]=(f1[i-1]*9+f2[i-1])%mod;
		f2[i]=(f2[i-1]*9+f1[i-1])%mod;
	}
	for(int i=1;i<=t;i++)
	{
		n=read();k=read();
		if(n==1)//特判1的情况
		{
			cout << "9" << '\n';
			continue;
		}
		printf("%lld\n",f1[n]%mod);
	}
	return 0;
}

```

如有不足之处，请大家指出。
### 希望管理大大放行！！！

---

## 作者：houpingze (赞：1)

~~看看这个sb麻烦但是易懂的题解吧~~

定义

$f_{i,j,1}$表示i位数中含有偶数个$j$的数

$f_{i,j,0}$表示i位数中含有奇数个$j$的数

一个含有偶数个j的i位数，可以分为以下两种情况产生：
1.  一个含有偶数个$j$的$i-1$位数 $*9$（$*9$是因为除了j这个数字不能放，其他都可以放） 
2.  一个含有奇数个$j$的$i-1$位数的末尾加上$j$  
                
一个含有奇数个j的i位数，可以分为以下两种情况产生：
1.  一个含有奇数个$j$的$i-1$位数 $*9$（$*9$是因为除了j这个数字不能放，其他都可以放） 
2.  一个含有偶数个$j$的$i-1$位数的末尾加上$j$  
                
追求效率，预处理一下即可

```cpp

#include<bits/stdc++.h>
#define reg register int
#define INF (1<<30)
#define mod 998244353
using namespace std;
int read(){
	int res=0,fs=1; char c=getchar();
	while(!(c>='0' && c<='9')){ if(c=='-')fs=-1; c=getchar(); }
	while(c>='0' && c<='9')res=res*10+c-'0',c=getchar();
	return res*fs;
}
void print(int x){
    if(x<0) { putchar('-'); x=-x;}
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
int n,cnt,m,a[5010],ans,tmp,k,t;
long long f[114514][12][3];  
/*
f[i][j][k]表示i位数中含有偶数个j的数 ,k=1
f[i][j][k]表示i位数中含有奇数个j的数 ,k=0

*/
int main() { 
	f[1][1][1]=8,f[1][2][1]=8,f[1][3][1]=8,f[1][0][1]=8,f[1][4][1]=8,f[1][5][1]=8,f[1][6][1]=8,f[1][7][1]=8,f[1][8][1]=8,f[1][9][1]=8;
	f[1][1][0]=1,f[1][2][0]=1,f[1][3][0]=1,f[1][0][0]=1,f[1][4][0]=1,f[1][5][0]=1,f[1][6][0]=1,f[1][7][0]=1,f[1][8][0]=1,f[1][9][0]=1;
	for(int i=2;i<=114514;i++){
		for(int j=0;j<=9;j++){ 
			f[i][j][1]=f[i-1][j][1]*9+f[i-1][j][0];
			f[i][j][0]=f[i-1][j][0]*9+f[i-1][j][1];
			f[i][j][1]%=mod;
			f[i][j][0]%=mod;
			/*
			一个含有偶数个j的i位数，可以分为以下两种情况产生：
				1.  一个含有偶数个j的i-1位数 *9（*9是因为除了j这个数字不能放，其他都可以放） 
				2.  一个含有奇数个j的i-1位数的末尾加上j   
    		一个含有奇数个j的i位数，可以分为以下两种情况产生：
				1.  一个含有奇数个j的i-1位数 *9（*9是因为除了j这个数字不能放，其他都可以放） 
				2.  一个含有偶数个j的i-1位数的末尾加上j   
			*/ 
        
		}
	}
	cin>>t;
	while(t--){
		n=read(),k=read();
		if(n==1) cout<<9<<'\n';
		else cout<<f[n][k][1]<<'\n';
		//注意，endl比'\n'要慢很多倍，是很多！
	}
    return 0;
}
```

---

## 作者：nzcnnr (赞：0)

## 思路
总体上看下来，这道题不能用爆搜（ $1\le n\le 10^5$ ），所以说，可行的方法就是 dp。又注意到，以任何一个数字为 $k$ 都是等价的，所以说这道题的答案与 $k$ 无关，接下来的问题就是转移方程了。
## 转移方程
我们建立两个数组 $dp1$ 和 $dp2$ 我们用第一个数组存储在第 $i$ 位上符合要求的数的个数，用第二个数组存储不符合要求的数目。而对于在 $i+1$ 位上的所有数，我们可以理解为是在第 $i$ 位的数后加入一个数字得到的，所以说 $i+1$ 位上的符合要求的数必定是由第 $i$ 位的符合要求的数与一个不为 $k$ 的数字组成的所有数和在第 $i$ 位上符合要求的数与 $k$ 组成的，同理也可以得到 $dp2$ 的转移方程。

$$\mathit{dp1}_{i}=\mathit{dp1}_{i-1}\times 9+\mathit{dp2}_{i-1}$$

$$\mathit{dp2}_{i}=\mathit{dp2}_{i-1}\times 9+\mathit{dp1}_{i-1}$$

同时在 $n=1$ 时要注意特判，直接输出 $9$。

接下来就是代码实现的过程了。（记得不要忘了取模）
## Code
```c
#include <stdio.h>
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	long long dp1[114519],dp2[114519];//数组必须要开的比n的最大值大
	dp1[1]=8,dp2[1]=1;
	for(int i=1;i<=114514;i++){//循环次数只要超过10的五次方即可
		dp1[i]+=dp2[i-1];
		dp1[i]+=dp1[i-1]*9;
		dp1[i]%=998244353;
		dp2[i]+=dp2[i-1]*9;
		dp2[i]+=dp1[i-1];
		dp2[i]%=998244353;
	}
	for(int i=1;i<=t;i++){
		int n,k;
		scanf("%d%d",&n,&k);
		if(n==1){
			printf("9\n");
			continue;
		}//特判
		printf("%d\n",dp1[n]);	
	}
	return 0;	
} 
```

---

## 作者：p924874163 (赞：0)

# 分析
定义 $f_{i,j}$ 来表示当前符合条件的方案数，$f_{1,i}$ 表示有 $i$ 位数时偶数个 $k$ 的方案数，$f_{0,i}$ 则表示有 $i$ 位数时奇数个 $k$ 的方案数。

由题意可知，最终答案就是 $f_{1,n}$。

而状态转移方程就是 $f_{0,i}=(f_{0,i-1}\times9+f_{1,i-1})\bmod998244353$，有 $i$ 位数并且有奇数个 $k$ 的方案数就可以由有 $i-1$ 位数且有偶数个 $k$ 的方案数乘上除掉 $k$ 的 $8$ 个数。

同理可得 $f_{1,i}=(f_{1,i-1}\times9+f_{0,i-1})\bmod998244353$。

注意一定要开`long long`，不然会WA。

状态转移方程出来后，就可以开始写了。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[3][200000],n,t,k;
const int mod=998244353;
int main()
{
	scanf("%lld",&t);
	f[1][1]=8;
	f[0][1]=1;
	for(int i=2;i<=2e5;i++)
		f[0][i]=(f[0][i-1]*9+f[1][i-1])%mod,f[1][i]=(f[1][i-1]*9+f[0][i-1])%mod;
	while(t--)
	{
		scanf("%lld%lld",&n,&k);
		if(n==1)	//当只有一位数时，需要特判。
			cout<<9<<"\n";
		else cout<<f[1][n]<<"\n";	
	}
	return 0;
}

```

---

## 作者：happybob (赞：0)

传送门：[P7158](https://www.luogu.com.cn/problem/P7158)

本题考虑动态规划，很明显我们需要一个 $O(n)$ 左右的动态规划。

首先我们可以对数进行分析，假设有 $\overline{abcd}$，那么对于第 $5$ 位，有 $9$ 种方法，就是 $0$ 到 $9$ 中少去掉一个 $k$，假设 $\overline{abcd}$ 已经有 $w_4$ 种成立方法，有 $p_4$ 种不成立方法，那么 $w_5$ 应该是 $9 \times w_4 + p_4$，也就是说每一种成立的方法拓展出 $9$ 种新的，那种不成立的（假设为 $\overline{qwer}$），那么加上一个 $k$ 就有 $\overline{qwer \,\,\,k}$，只有 $1$ 种。

假设常量 $L = 998244353$，有转移方程：

$\Large w_i = \begin{cases} 8 & i = 1 \\ (w_{i-1} \times 9+ p_{i - 1}) \bmod L& i \ge 2 \end{cases}$

$\Large p_i = \begin{cases} 1 & i = 1 \\ (p_{i-1} \times 9+ w_{i - 1})\bmod L & i \ge 2 \end{cases}$

另外，这道题与 $k$ 的值无关，也就是说对于一个确定的 $n$，无论 $k$ 取何值，答案一样。

代码（注意要加预处理）：

```cpp
#include <cstdio>
#include <cstring>
using namespace std;

#define int long long
const int N = 1e5 + 5, MOD = 998244353;
int ok[N], no[N];

signed main()
{
	ok[1] = 8;
	no[1] = 1;
	for (int i = 2; i <= 1e5; i++)
	{
		ok[i] = (ok[i - 1] * 9 + no[i - 1]) % MOD;
		no[i] = (no[i - 1] * 9 + ok[i - 1]) % MOD;
	}
	int t;
	scanf("%lld", &t);
	while (t--)
	{
		int n, k;
		scanf("%lld %lld", &n, &k);
		if (n == 1)
		{
			printf("9\n");
			continue;
		}
		printf("%lld\n", ok[n]);
	}
	return 0;
}
```


---

