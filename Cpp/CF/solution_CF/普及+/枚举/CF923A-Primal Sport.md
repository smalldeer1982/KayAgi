# Primal Sport

## 题目描述

Alice and Bob begin their day with a quick game. They first choose a starting number $ X_{0}>=3 $ and try to reach one million by the process described below.

Alice goes first and then they take alternating turns. In the $ i $ -th turn, the player whose turn it is selects a prime number smaller than the current number, and announces the smallest multiple of this prime number that is not smaller than the current number.

Formally, he or she selects a prime $ p&lt;X_{i-1} $ and then finds the minimum $ X_{i}>=X_{i-1} $ such that $ p $ divides $ X_{i} $ . Note that if the selected prime $ p $ already divides $ X_{i-1} $ , then the number does not change.

Eve has witnessed the state of the game after two turns. Given $ X_{2} $ , help her determine what is the smallest possible starting number $ X_{0} $ . Note that the players don't necessarily play optimally. You should consider all possible game evolutions.

## 说明/提示

In the first test, the smallest possible starting number is $ X_{0}=6 $ . One possible course of the game is as follows:

- Alice picks prime 5 and announces $ X_{1}=10 $
- Bob picks prime 7 and announces $ X_{2}=14 $ .

In the second case, let $ X_{0}=15 $ .

- Alice picks prime 2 and announces $ X_{1}=16 $
- Bob picks prime 5 and announces $ X_{2}=20 $ .

## 样例 #1

### 输入

```
14
```

### 输出

```
6
```

## 样例 #2

### 输入

```
20
```

### 输出

```
15
```

## 样例 #3

### 输入

```
8192
```

### 输出

```
8191
```

# 题解

## 作者：Blunt_Feeling (赞：3)

## CF923A Primal Sport 题解

这是代码最短的一篇题解。

主要提供一种找最大质因数的更简洁的写法。我们可以遍历 $2\sim X_2$ 中的每一个数，如果一个数不是之前任何一个数的倍数，就证明这个数是一个质数。如果这个数是质数，就可以用它标记掉它的所有倍数，也就是把这个数的所有倍数的最大质因数标记为这个质数。

这样我们就预处理出了 $2\sim X_2$ 中每一个数的最大质因数。

接下来的做法和其他题解差不多。$X_1$ 与 $X_2$ 之间的关系是 $X_2−p+1\le X_1\le X_2$，所以枚举 $X_1$，对于每个 $X_1$ 求 $X_0$ 的最小值，这里不多赘述。

### Code
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
int x2,x0,a[1000050];
int main()
{
	cin>>x2;
	For(i,2,x2)
		if(!a[i])
			for(int j=i*2;j<=x2;j+=i)
				a[j]=i;
	x0=x2;
	For(i,x2-a[x2]+1,x2) x0=min(x0,i-a[i]+1);
	cout<<x0<<endl;
	return 0;
}
```


---

## 作者：ModestCoder_ (赞：2)

首先发现一个结论：$X_i$的值域为$[X_{i+1}-P+1,X_{i+1}],P$为$X_{i+1}$的最大质因数

预处理每个数是否为质数以及最大质因数，用线筛可完成

然后枚举$X_1$，求针对每个$X_1$的$X_0$的最小值

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 1000010
using namespace std;
int n, flag[maxn], tot, a[maxn], prime[maxn];

int main(){
	scanf("%d", &n);
	flag[1] = 1;
	for (int i = 2; i <= n; ++i){
		if (!flag[i]) prime[++tot] = a[i] = i;
		for (int j = 1; j <= tot && i * prime[j] <= n; ++j){
			flag[i * prime[j]] = 1, a[i * prime[j]] = a[i];
			if (i % prime[j] == 0) break;
		}
	}
	int ans = n;
	for (int i = n - a[n] + 1; i <= n; ++i)
		if (flag[i]) ans = min(ans, i - a[i] + 1);
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：Jasper08 (赞：0)

[简要题意](https://www.luogu.com.cn/discuss/455668)

### 【题目分析】

根据题意有一个重要的结论：$x_i-p_i+1\le x_{i-1}\le x_i$。

证明：题目中已经给出了 $x_{i-1}\leq x_i$，$x_i$ 为 $p_i$ 倍数且最小。若 $x_{i-1}<x_i-p_i+1$ ，则 $x_i-p_i$ 为最小的解，矛盾。因此 $x_i-p_i+1\le x_{i-1}\le x_i$。

所以当 $i=1$ 和 $i=2$ 时，$x_1-p_1+1\le x_0\le x_1$，$x_2-p_2+1\le x_1\le x_2$。 而想要让 $x_0$ 尽可能小，就要让 $x_1$ 尽可能小，$p_1$ 尽可能大。又因为 $p_1$ $|$ $x_1$ ，所以在 $p_1$ 为 $x_1$ 的最大质因数且 $x_1$ 最小时 $x_0$ 有最小值 $x_1-p_1+1$。

同理，找到 $x_2$ 的最大质因数 $p_2$ 后在区间 $[x_2-p_2+1, x_2]$ 中枚举 $x_1$ 求最小值即可。

### 【完整代码】

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

int main() {
	int x2;
	scanf("%d", &x2);
	
	int p2 = 1, t = x2; //找出x2的最大质因数,令其为p2 
	for (int i = 2; i <= t/i; ++i) { //分解x2的质因数
		while (t % i == 0)
			t /= i,	p2 = i;
	}
	if (t > 1)
		p2 = t;
	
	int ans = 1e9;
	for (int x1 = p2*(x2/p2-1)+1; x1 <= x2; ++x1) { //枚举x1 
		int t = x1, p1 = x1;
		for (int i = 2; i <= t/i; ++i) { //求x1的最大质因数p1
			while (t % i == 0)
				t /= i, p1 = i;
		} 
		if (t > 1)
			p1 = t;
		int x0 = x1 - p1 + 1; //根据刚刚推出的公式计算x0的值
		ans = (x0 < 3) ? ans : min(x0, ans); //特判x0<3的情况,此时不满足题目要求
	} 
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Patrickpwq (赞：0)

反推
想象如下图的一个形状
x0
p1 x1
p2 x2
设x2/p2=n
由题意得 x2>= x1 >=(n-1)*p2+1
(n-1)*p2又等于什么？n*p2-p2+1 即 x2-p2+1
因此x1的范围就出来了 即[x2-p2+1] 选的质数越大 就越小 因此贪心 取最大的质数
所以说在线性筛质数的时候还要把所有合数的最大质因子处理出来
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,big[1000005];
int prime[1000005];
bitset <1000005> is;
int cnt=0;
inline void Eulerpick(int n)
{
	
	is[0]=is[1]=1;	//1代表不是 
	for(int i=2;i<=n;i++)
	{
		if(is[i]==0)
		{	
			big[i]=i;
			prime[++cnt]=i;
		}   //没标记到（是素数） 
		for(int j=1;j<=cnt&&i*prime[j]<=n;j++)	//枚举前面所有素数 
		{
			is[i*prime[j]]=1;	//标记前面素数的倍数
			big[i*prime[j]]=big[i];
			if((i%prime[j])==0)	break;	//如果不是最小质因子 就退出 
		}
		
	}
}
int main()
{
	cin>>n;
	Eulerpick(n);
	//cout<<big[n]<<endl;
	int ans=10000000;
	for(int i=n-big[n]+1;i<=n;i++)
	{
		if(is[i]) ans=min(ans,i-big[i]+1);
	//	cout<<i<<" "<<big[i]<<endl;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：king_xbz (赞：0)

大家都在规规矩矩的解题，好像没有像我一样乱搞的吧？！

那我就来发一篇不一样的题解。

首先，三个数间最小公倍数的柿子是：

$\huge lcm=\frac {a×b×c}{gcd(a,b,c)}$

要让三个数之间LCM最大，那必然要使$a×b×c$尽可能的大，同时$gcd(a,b,c)$尽可能的小。

$gcd(a,b,c)$最小的时候也恰好是三个数互质的时候

而$a×b×c$最大的时候必然是这三个数分别为$(n),(n-1),(n-2)$的时候。

我们需要的就是尽可能同时这几种情况的满足。

假如$n\%2=1$，那么此时$(n),(n-1),(n-2)$必互质，所以答案就是这三数之乘积。

否则，我们从高往低枚举即可。

然而，我并不想像别的人那样进行繁琐的数学推导，于是我想到了一个歪招：**迭代加深搜索**。

初始搜索深度为50，阈值为200000，每次**搜完后深度再加上50**，直到**连续200000次**搜索都没有更新答案，证明此时答案**趋于稳定**，退出即可。

代码：

```cpp
#include<bits/stdc++.h>
#define fint register int
#define int long long
#define H 5001
#define N 475894
using namespace std;
int gcd(int a,int b);
signed main()
{
	int n;
	cin>>n;
	if(n<=3)
	{
		if(n==1)
		puts("1");
		else
		if(n==2)
		puts("2");
		else
		if(n==3)
		puts("6");
	}
	else
	if(n&1LL)
	cout<<(n)*(n-1)*(n-2);
	else
	{
		int dep=50,ans=0,lim=0;
		while(1)
		{
			for(fint i=n;i>=max(1LL,n-dep);i--)
			for(fint j=n;j>=max(1LL,n-dep);j--)
			for(fint k=n;k>=max(1LL,n-dep);k--)
			{
				int lcm=i*j/gcd(i,j);
				lcm=lcm*k/gcd(lcm,k);
				if(lcm>ans)
				ans=lcm,lim=0;
				else
				lim++;
				if(lim>=20000)
				goto lb;
			}
			if(n-dep<=0)
			goto lb;
		}
		lb:
		cout<<ans;
	}
	return 0;
}

int gcd(int a,int b)
{
	if(b==0)
	return a;
	return gcd(b,a%b);
}
```



---

## 作者：cbyybccbyybc (赞：0)

### 前言
这道题在考场上当个T3，当场懵逼，没有推出公式，回来想一想发现其实很简单
### 题意
自己看题吧，解释起来比较麻烦。。。
### Solution
乍一看题意很难懂，看起来像是变态找规律题，其实，暴力枚举也可以过。

先观察$X1$和$X2$的关系。

易知$X2-P+1\le X1\le X2$

那么我们就可以枚举每一个$X1$，由于$X1-PP+1\le X0 \le X1$，所以$X1$必须为合数，用线性筛筛出所有的素数，用$a$数组表示$i$的最大质因数。

用$mark$判断一下是否是素数，$ans=min(ans,i-a[i]+1)$
### 代码
```
#include<bits/stdc++.h>
using namespace std;
const int MAX=1000010;
bool mark[MAX];
int arr[MAX];
int n;
int a[MAX];
int main()
{
	int n;
	cin>>n;
	int cur=0;
    for(int i=2;i<=n;i++){
        if(mark[i]==false) arr[++cur]=a[i]=i;
        for(int j=1;j<=cur&&i*arr[j]<=n;j++){
            mark[i*arr[j]]=true;
            a[i*arr[j]]=a[i];
            if(i%arr[j]==0) break;
        }
    }
    int ans=n;
	for(int i=n-a[n]+1;i<=n;i++)
		if(mark[i]) 
			ans=min(ans,i-a[i]+1);
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：大菜鸡fks (赞：0)

穷举x1，x0肯定是x1-pri+1

pri为x1的最大质因子

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=1e5+5,INF=1e9;
int n,pri[N],tot,ans;
bool mark[N];
inline void init(){
	n=read();
}
inline void pre(){
	for (int i=2;i<N;i++){
		if (!mark[i]) pri[++tot]=i;
		for (int j=1;j<=tot&&i*pri[j]<N;j++) {
			mark[i*pri[j]]=1;
			if (i%pri[j]==0) break;
		}
	}
}
inline int Get(int x){
	int X=x,tmp;
	for (int i=1;i<=tot&&pri[i]*pri[i]<=X;i++){
		while (x%pri[i]==0) {
			x/=pri[i];
			tmp=pri[i];
		}
	}
	if (x!=1) tmp=x;
	return tmp;
}
inline void solve(){
	pre();
	int now=Get(n); ans=INF;
	for (int i=n-now+1;i<=n;i++){
		int tmp=i-Get(i)+1;
		if (tmp>=3) ans=min(ans,tmp);
	}
	writeln(ans);
}
int main(){
	init();
	solve();
	return 0;
}
```

---

