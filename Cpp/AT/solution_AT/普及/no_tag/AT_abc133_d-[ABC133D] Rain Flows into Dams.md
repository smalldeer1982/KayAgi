# [ABC133D] Rain Flows into Dams

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc133/tasks/abc133_d

円形に $ N $ 個の山が連なっており、時計回りに山 $ 1 $, 山 $ 2 $, $ … $, 山 $ N $ と呼ばれます。$ N $ は**奇数**です。

これらの山の間に $ N $ 個のダムがあり、ダム $ 1 $, ダム $ 2 $, $ … $, ダム $ N $ と呼ばれます。ダム $ i $ ($ 1\ \leq\ i\ \leq\ N $) は山 $ i $ と山 $ i+1 $ の間にあります (山 $ N+1 $ は山 $ 1 $ のことを指します)。

山 $ i $ ($ 1\ \leq\ i\ \leq\ N $) に $ 2x $ リットルの雨が降ると、ダム $ i-1 $ とダム $ i $ にそれぞれ $ x $ リットルずつ水が溜まります (ダム $ 0 $ はダム $ N $ のことを指します)。

ある日、各山に非負の**偶数**リットルの雨が降りました。

その結果、ダム $ i $ ($ 1\ \leq\ i\ \leq\ N $) には合計で $ A_i $ リットルの水が溜まりました。

各山に降った雨の量を求めてください。この問題の制約下では解が一意に定まることが証明できます。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 3\ \leq\ N\ \leq\ 10^5-1 $
- $ N $ は奇数である。
- $ 0\ \leq\ A_i\ \leq\ 10^9 $
- 入力が表す状況は、各山に非負の偶数リットルの雨が降った際に発生しうる。

### Sample Explanation 1

山 $ 1,\ 2,\ 3 $ に降った雨の量をそれぞれ $ 4 $ リットル, $ 0 $ リットル, $ 4 $ リットルとすると以下のように辻褄が合います。 - ダム $ 1 $ には $ \frac{4}{2}\ +\ \frac{0}{2}\ =\ 2 $ リットルの水が溜まります。 - ダム $ 2 $ には $ \frac{0}{2}\ +\ \frac{4}{2}\ =\ 2 $ リットルの水が溜まります。 - ダム $ 3 $ には $ \frac{4}{2}\ +\ \frac{4}{2}\ =\ 4 $ リットルの水が溜まります。

## 样例 #1

### 输入

```
3
2 2 4```

### 输出

```
4 0 4```

## 样例 #2

### 输入

```
5
3 8 7 5 5```

### 输出

```
2 4 12 2 8```

## 样例 #3

### 输入

```
3
1000000000 1000000000 0```

### 输出

```
0 2000000000 0```

# 题解

## 作者：_Above_the_clouds_ (赞：27)

# 思路：
大坝 $a_i$ 的 $2$ 倍就等于第 $i$ 和 第 $i-1$ 座山的降水量。

先假设第 $1$ 座山的降水量为 $0$，用上面所讲的方式依次算出第 $2\sim n$ 座山的降水量。最后，如果第 $n$ 座山和第 $1$ 座山的降水量之和等于第 $n$ 个大坝的水量，直接输出。

否则第 $1$ 座山的降水量就为假设的第 $1$ 座山和第 $n$ 座山的降水量与第 $n$ 个大坝水量的 $2$ 倍的差，再除以 $2$，再算出其他山的降水量，最后输出即可。

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long a[100005],b[100005];
int main(){
	cin>>n;
	for(int i=0;i<n;i++) cin>>a[i];
	b[0]=0;
	for(int i=1;i<n;i++) b[i]=2*a[i-1]-b[i-1];
	if(b[n-1]+b[0]==a[n-1]*2) for(int i=0;i<n;i++) cout<<b[i]<<" ";
	else{
		b[0]=abs(b[n-1]+b[0]-a[n-1]*2)/2;
		for(int i=1;i<n;i++) b[i]=2*a[i-1]-b[i-1];
		for(int i=0;i<n;i++) cout<<b[i]<<" ";
	}
	return 0;
}

```


---

## 作者：b6e0_ (赞：25)

[题](https://www.luogu.com.cn/problem/AT4764)

**注意：这题保证了 $n$ 是奇数。**

根据题意，设答案为 $b_1,b_2,\cdots b_n$，则可以列出方程：
$$\begin{cases}a_1=\frac{b_1}2+\frac{b_2}2\\a_2=\frac{b_2}2+\frac{b_3}2\\a_3=\frac{b_3}2+\frac{b_4}2\\\cdots\\a_n=\frac{b_n}2+\frac{b_1}2\end{cases}$$
用 $a_i$ 和 $b_{i+1}$ 表示 $b_i$：
$$\begin{cases}b_1=2a_1-b_2\\b_2=2a_2-b_3\\b_3=2a_3-b_4\\\cdots\\b_n=2a_n-b_1\end{cases}$$
消去 $b_2$ 至 $b_n$：
$$b_1=2a_1-2a_2+2a_3-2a_4+\cdots+2a_n-b_1$$
$$b_1=a_1-a_2+a_3-a_4+\cdots+a_n$$
算出 $b_1$ 后，在原方程组上，用 $a_i$ 和 $b_i$ 表示 $b_{i+1}$：
$$\begin{cases}b_2=2a_1-b_1\\b_3=2a_2-b_2\\b_4=2a_3-b_2\\\cdots\\b_n=2a_{n-1}-b_{n-1}\end{cases}$$
将 $b_1$ 代入，计算即可。时间复杂度 $\mathcal O(n)$。代码：
```cpp
#include<bits/stdc++.h>
using namepace std;
long long a[100010];//一定要开long long！
int main()
{
	int n,i;
	long long sum=0;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
		if(i&1)
			sum+=a[i];
		else
			sum-=a[i];
	}
	for(i=1;i<=n;i++)
	{
		cout<<sum<<' ';
		sum=2*a[i]-sum;
	}
	return 0;
}
```

---

## 作者：whx2009 (赞：20)

## 本题思路：
这道题其实就是一个找规律，我们可以知道题目中给出的是最后的积水总量，每一个大坝的集水就是这座大山原本降水量的一半加上后面的一座山降水量的一半。又因为题目中保证了 $n$ 是奇数，那么我们就可以把 $n-1$ 个大坝中偶数加起来，再减去奇数，就可以得到最开头的山降水量的一半减去最后的山降水量的一半，而我们又知道最后一座山加上开头的一座山总数的一半，那么用和差就可以算出最开头的一座山的降水量。最后一座一座带入去算就可以了！
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[100000],b[100000];
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int n,ans=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		ans+=a[i];
	}
	if(ans==0)
	{
		for(int i=1;i<=n;i++) cout<<0<<" ";
	}
	else
	{
		int o=a[1];
		for(int i=2;i<n;i++)
		{
			if(i%2==0)
			o-=a[i];
			else o+=a[i];
		}
		b[1]=o+a[n];
		for(int i=1;i<n;i++)
		{
			b[i+1]=(a[i]-b[i]/2)*2;
		}
		for(int i=1;i<=n;i++) cout<<b[i]<<" "; 
	}
	return 0;
}

```


---

## 作者：_maojun_ (赞：14)

一种奇怪的方法，不过可能差不多。

---

设所求的序列为 $a$。

设 $s_i=\begin{cases}a_1+a_n&i=n\\a_i+a_{i+1}&i<n\end{cases}$，即输入的数据乘 $2$。

观察到

$s_1-s_2+s_3-s_4+...+s_{n-2}-s_{n-1}=a_1+a_2-(a_2+a_3)+(a_3+a_4)-(a_4+a_5)+...+(a_{n-2}+a_{n-1})-(a_{n-1}+a_n)=a_1-a_n$

$s_2-s_3+s_4-s_5+...+s_{n-1}-s_n=a_2+a_3-(a_3+a_4)+(a_4+a_5)-(a_5+a_6)+...+(a_{n-1}+a_n)-(a_n+a_1)=a_2-a_1$

$...$

可以发现 $d_i=\begin{cases}a_1-a_n&i=1\\a_i-a_{i-1}&i>1\end{cases}=s_i-s_{i+1}+s_{i+2}-s_{i+3}+...$ 且遇到 $n$ 就变回 $1$。

那么可以一遍递推把 $d$ 求出来。

所以 $a_i=\begin{cases}\dfrac{s_n+d_1}2&i=1\\a_{i-1}+d_i&i>1\end{cases}$，一遍前缀和即可。

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;

typedef long long ll;
const int MAXN=1e5+5;
int n;ll s[MAXN],d[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&s[i]),s[i]<<=1;
	int l=1,r=n-1;ll now=0;
	for(int i=1;i<n;i++)	// 先预处理 d[1]
		if(i&1)now+=s[i];
		else now-=s[i];
	d[1]=(now+s[n])>>1;
	for(l++;l<=n;l++){		// 递推求出 d[2],d[3],...,d[n]
		r=r%n+1;
		now-=s[l-1];now=-now;
		now-=s[r];
		d[l]=now;
	}
	printf("%lld",d[1]);
	for(int i=2;i<=n;i++)	// 一遍前缀和
		d[i]+=d[i-1],printf(" %lld",d[i]);
	printf("\n");
	return 0;
}
```

---

## 作者：_7Mr (赞：13)

# 思路
因为下的雨量和水坝的积水量是相等的，所以我们设每个水坝的积水量是 $a_i$，每个山下的雨量是 $x_i$，那么我们就有 $a_i + \dots + a_n = x_i + \dots + x_n $。我们设这个和为 $S$。

又根据题意，我们可知 $\frac{x_i+x_{i+1}}{2}=a_i$ 我们将此式子变形可得 $x_i+x_{i+1}=2 \times a_i$。此时，我们只要推出其中一个 $x_i$ 就能知道所有的 $x_i$ 的值了。那么，我们就计算 $x_1$ 的值。

根据以上我们推出的式子可知，$x_1=S-x_2-x_3- \dots -x_n=S-2 \times (a_2+a_4+ \dots +a_{n-1})$，那么这个时候我们已经算出 $x_1$ 的值了，就可以算出剩下的 $x_i$。
# ACcode
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF INT_MAX
using namespace std;
const int maxn=1e5+5;
int n;
int a[maxn],x[maxn];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	int sum=0;
	for(int i=1;i<=n;i++) sum+=a[i];//求和S
	for(int i=2;i<=n-1;i+=2) sum-=2*a[i];//计算x1的值
	x[1]=sum; 
	for(int i=1;i<n;i++) x[i+1]=2*a[i]-x[i];//算出剩下的xi
	for(int i=1;i<=n;i++) cout<<x[i]<<" ";//输出答案
	return 0;
}
```

---

## 作者：watcher_YBH (赞：13)

# 思路：
[[题目]](https://www.luogu.com.cn/problem/AT_abc133_d)

假设有 $5$ 座大山，它们分别为 $a,b,c,d,e$。

根据题目意思，我们表示出每个大坝的存水量，$(\frac{a}{2}+\frac{b}{2}),(\frac{b}{2}+\frac{c}{2}),(\frac{c}{2}+\frac{d}{2}),(\frac{d}{2}+\frac{e}{2}),(\frac{e}{2}+\frac{a}{2}),$

我们可以观察到，将所有大坝的总存水量 $-$ 编号为偶数的大坝的总存水量 $\times 2$，就可以求出大山 $a$ 的存水量。

得到 $a$ 后，$b$ 就为：大坝 $1$ 的存水量 $-\frac{a}{2}$ 的差再 $\times 2$。然后，再通过 $b$ 求出 $c$……依次求解。

# 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define max(a,b) ((a>b)?a:b)
#define min(a,b) ((a<b)?a:b)
using namespace std;
const int MAX = 1e5+5;
int n,ans,ans_;
int a[MAX],b[MAX];
int main(){
	cin>>n;
	for(int i = 1; i<=n; i++){
		cin>>a[i]; ans += a[i];//总和
		if(i%2 == 0) ans_ += a[i];//偶数位的总和
	}
	b[1] = ans-ans_*2;//求出第一座大山
	for(int i = 2; i<=n; i++)//依次求解剩下的
		b[i] = (a[i-1]-b[i-1]/2)*2;
	b[n] = (a[n]-b[1]/2)*2;//最后一座特殊处理
	for(int i = 1; i<=n; i++)//输出
		cout<<b[i]<<" ";
	return 0;
}
```

---

## 作者：cppcppcpp3 (赞：12)

## Problem

给出 $n$ （$3 \le n \le 10^5-1$ 且 $n$ 为奇数）个数 $x_1$，$x_2$，...，$x_n$，求解一组数 $a$，满足以下方程组：

$a_1+a_2=2 \times x_1$

$a_2+a_3=2 \times x_2$

$\cdots $

$a_{n-1}+a_n=2 \times x_{n-1}$

$a_n+a_1=2 \times x_n$

可以证明，存在且仅存在一组解。


------------


## Solution

简单的解方程。

将等式两边加起来，得到 $2 \times (a_1+a_2+ \cdots +a_n)=2 \times (x_1+x_2+ \cdots +x_n)$，即 $a_1+a_2+ \cdots +a_n=x_1+x_2+ \cdots +x_n$。

然后我们求解 $a_n$。显然，$a_1+a_2+ \cdots +a_{n-1}=2 \times (x_1+x_3+ \cdots +x_{n-2})$。

两式相减就可以得到 $a_n$。之后 $a_{n-1}=2 \times x_{n-1}-a_n$，一步步向前推即可。

复杂度 $O(n)$，代码很短。

```cpp
#include<bits/stdc++.h>
#define il inline
#define int long long
using namespace std;
const int N=1e5+5;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return x*f;
}

int n,x[N],s,t,a[N];

main(){
	n=wrd();
	for(int i=1;i<=n;++i) s+=(x[i]=wrd());
	for(int i=1;i<=n-2;i+=2) t+=2*x[i]; //a[1]到a[n-1]的和。
	a[n]=s-t;
	for(int i=n-1;i>=1;--i) a[i]=2*x[i]-a[i+1];
	for(int i=1;i<=n;++i) printf("%lld ",a[i]);
	return 0;
}
```

---

## 作者：_Flame_ (赞：12)

## 思路

遇到这种题可以先考虑从题目给的式子入手。

设每座山水量为 $ans_i$，每座水坝水量为 $a_i$，由题意可得有两种情况：

- $n \neq i$ 时 $a_i=\frac {ans_i}{2}+\frac {ans_{i+1}}{2}$。

- $n=i$ 时 $a_i=\frac {ans_i}{2}+\frac {ans_{1}}{2}$。

可以发现，联立所有式子后，我们可以化简解方程求出 

$ans_1=a_1-a_2+a_3-a_4+ \cdot\cdot\cdot+a_{n-1}-a_n$。

带入解方程：

$ans_i=(\frac {a_i}{2}-\frac {b_{i-1}}{2})\times 2$。

最后输出即可。

## Code

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;

static char buf[1000000],*p1=buf,*p2=buf;

inline int read(){
	char c=getchar();
	int res=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res*f;
}

inline void write(int x){
	static char buf[20];
	static int len=-1;
	if(x<0){
		putchar('-');
		x=-x;
	}
	do{
		buf[++len]=x%10;
		x/=10;
	}
	while(x);
	while(len>=0){
		putchar(buf[len--]+48);
	}
}

const int maxn=100010;
const int maxm=1e10;
const int mod=1e9+7;

int n;
int a[maxn],ans[maxn];

void solve(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(i&1) ans[1]+=a[i];
		else ans[1]-=a[i];
	}
	for(int i=2;i<=n;i++){
		ans[i]=2*a[i-1]-ans[i-1];
	}
	for(int i=1;i<=n;i++){
		printf("%lld ",ans[i]);
	}
	return ;
}

signed main(){
	int T=1;
	while(T--){
		solve();
	}
	return 0;
}

```

---

## 作者：Swirl (赞：12)

# 思路简述

**本题是一道数学题，重在推导**。

不妨定义数组 $a$ 和 $b$ ，分别代表输入数组和输出数组。

根据题意可以写出方程：


$$
a_i=\frac{b_i}{2}+\frac{b_{i + 1}}{2}
$$

特别的，对于 $i=n$ 存在特例：

$$
a_n=\frac{b_n}{2}+\frac{b_1}{2}
$$

将公式中的 $\frac{1}{2}$ 系数消掉：

$$
2 \times a_i=b_i+b_{i+1}
$$
$$
2 \times a_n=b_n+b_1
$$

将 $b_i$ 项移到等式左边，将 $2 \times a_i$ 项移到等式右边，并稍做变更：
$$
b_i=2 \times a_i-b_{i+1}
$$
$$
b_n=2 \times a_n-b_{1}
$$

此时只需要求出 $b$ 数组中的任意一项即可，此时我们不妨求出第 $1$ 项：
$$
b_1=2\times a_1-b_2
$$
我们可以将 $b_2$ 项代入进 $b_1$ 项中， $b_3$ 项代入进 $b_2$ 项中……

最后直到带入到第 $n$ 项：

$$
b_1=2 \times a_1-2\times a_2+2\times a_3…2\times a_n - b_1
$$

化简一下：

$$
b_1=\sum_{i=1}^{n}a_i\times (-1)^{i+1}
$$

最后根据刚刚求出的公式，写出代码即可。

思路部分完结。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll n;
ll a[100005];
ll b[100005];

int main() {
	cin >> n;
	for (ll i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (ll i = 1; i <= n; i++) { //根据公式求出b[1]
		b[1] += pow(-1, i + 1) * a[i]; //巧妙利用-1次方的特性
	}
	for (ll i = 2; i <= n; i++) {
		b[i] = 2 * a[i - 1] - b[i - 1]; //利用公式转移
	}
	for (ll i = 1; i <= n; i++) {
		cout << b[i] << " ";
	}
	return 0;
}
```

---

## 作者：Yashajin_Ai (赞：12)

### 思路
这道题难点在于如何推式子，与推出来后如何处理式子，我们拿 $a_1,b_1,b_2$ 举个例子来推式子。

由题意可得 $a_1 = \dfrac{b_1}{2} +  \dfrac{b_2}{2}$，实施化简可得 $2 \times a_1 = b_1 + b_2$，再把 $i$ 代入式子就相当于 $2 \times a_i = b_i + b_{i+1}$，我们其实只用算出 $b_1$ 我们这道题就解决了，这是我们将每一个 $a_i$ 预处理一下，每一个都先乘二，这是我们在将奇数位上的和减去偶数位上的和就能算出 $b_1$ 的值了，因为预处理了，所以我们就知晓 $b_{i+1} = a_i - b_i$，最后输出即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long num=0,qwq=0,bwb=0;
int main(){
	int n;
	cin>>n;
	long long a[100001],b[100001];
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}		
	for(int i=1;i<=n;i++){
		a[i]*=2;
	}
	for(int i=1;i<=n;i+=2){
		qwq+=a[i];
	}
	for(int i=2;i<=n;i+=2){
		bwb+=a[i];
	}
	b[1]=(qwq-bwb)/2;
	for(int i=1;i<=n;i++){
		b[i+1]=a[i]-b[i];
		cout<<b[i]<<" ";	
	}
}
```

---

## 作者：_Extroversion (赞：11)

[传送门](https://www.luogu.com.cn/problem/AT_abc133_d)

## 题目分析

设第 $i$ 座山的降水量为 $x_i$，根据题意，不难得出如下方程组：

### $\begin{cases}\frac{x_1+x_2}{2}=a_1\\\frac{x_2+x_3}{2}=a_2\\\frac{x_3+x_4}{2}=a_3\\\cdot\cdot\cdot\\\frac{x_n+x_1}{2}=a_n\end{cases}$

这种方程组求解可以 Gauss 消元，但 $n\leq10^5-1$，明显跑不动。

------------

观察到每个方程只有两个未知数，且每个未知数均出现在两个方程中。也就是说，我们只要求出一个未知数，就能仅通过带入求出其他未知数。

我们将每个未知数用其他未知数表示，并尝试消元：

### $\begin{cases}x_1=2a_1-x_2\\x_2=2a_2-x_3\\x_3=2a_3-x_4\\\cdot\cdot\cdot\\x_n=2a_n-x_1\end{cases}$

将 $2$ 式带入 $1$ 式中的 $x_2$，可以消去 $x_2$，产生 $x_3$，再将 $3$ 式带入产生的 $x_3$。以此类推，我们最终能得到 $x_1=2a_1+\cdot\cdot\cdot\pm x_1$。

若最后一项 $x_1$ 系数为正，我们会得到一个不含有未知数的等式，这是无用的。

再次仔细阅读题面，**题目保证 $n$ 为奇数**，所以最后一项系数为负，即 $x_1=2a_1-2a_2+2a_3-\cdot\cdot\cdot+2a_n-x_1$。解这个含参方程，我们得到：

$x_1=a_1-a_2+a_3-\cdot\cdot\cdot+a_n$。

带入上面的方程组，本题即得到解决。

## Code：
$a_i$ 很大，$ans$ 会超出 `long long` 范围，需注意。
```cpp
#include<cstdio>
#include<cmath>
using namespace std;
int n;
long long a[100010],ans; 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		//ans+=a[i]*(((i&1)<<1)-1);
		//上面是不用选择语句的写法，不建议使用 
		if(i&1)ans+=a[i];
		else ans-=a[i]; 
	}
	for(int i=1;i<=n;i++){
		printf("%lld ",ans);
		ans=(a[i]<<1)-ans;//逐个带入求出所有未知数 
	}
	printf("\n");
	return 0;
}

```


---

## 作者：hhh_778899 (赞：11)

## 思路
 
- 我们设每座山的降水量分别为 $m_1,m_2,...,m_N$，每个水坝的雨量分别为 $d_1,d_2,...,d_N$。

- 则由题意得：

$$\begin{cases}d_1=0.5m_1+0.5m_2\\d_2=0.5m_2+0.5m_3\\...\\d_N=0.5m_N+0.5m_1\end{cases}$$

- 由于我们要求的是 $m_1,m_2,...,m_N$，所以我们把上面的方程组化简一下，得到：

$$\begin{cases}m_1=2d_1-m_2\\m_2=2d_2-m_3\\...\\m_N=2d_N-m_1\end{cases}$$

$$\implies m_1=2d_1-2d_2+2d_3-2d_4+...+2d_N-m_1$$

$$\implies m_1=d_1-d_2+d_3-d_4+...+d_N$$

- 再将方程组化简，得：

$$\begin{cases}m_2=2d_1-m_1\\m_3=2d_2-m_2\\...\\m_N=2d_{N-1}-m_{N-1}\end{cases}$$

- 所以，只要我们算出 $m_1$，就可以代入并求出每一项的值，这个题到这里就算结束了。

## 代码

```cpp
#include <iostream>
#define ll long long//记得开long long
#define maxn 100005
using namespace std;

ll a[maxn];
ll N;
ll ans;

int main()
{
	cin>>N;
	for(ll i=1;i<=N;i++)
	{
		cin>>a[i];
		if(i%2==1) ans+=a[i];
		else ans-=a[i];
	}
	for(ll i=1;i<=N;i++)
	{
		cout<<ans<<" ";
		ans=2*a[i]-ans;
	}
	return 0;
}
```


---

## 作者：zhanghao233 (赞：11)

# [题目](https://www.luogu.com.cn/problem/AT_abc133_d)大意

* 在 $n$ 且 $n$ 是奇数个环形围起 $moun$ 中有 $n$ 个水库，水库在 $moun_i$ 和 $moun_i+1$ 中间，编号为 $ba_i$

* 当有雨水降落在山上时，均分在山左右两边的水库中

* 给出所有水库的水量，求所有山的降水

# 思路

## #1
直接方程思想

设 $moun_i$ 的右降水量为 $x$ ，利用山左右两边的蓄水量相等的条件，绕着山群推出的 $moun_i$ 的左降水量

```cpp
int ele=a[x];
for(int i=x+1>n?1:x+1; i!=x; i+1>n?i=1:i++)
	ele=a[i]-ele;
```

## #2优化

当我们绕着山群推的 $moun_i$ 的左降水量时，我们会遇到已经推过的山降水，可以用这个已知的山降水量推出 $moun_i$ 的降水量

```cpp
int ele=a[x],f=0;//f是方程中代表ele-x还是ele+x
for(int i=x+1>n?1:x+1; i!=x; i+1>n?i=1:i++){
	ele=a[i]-ele,f=!f;
   
	if(moun[i+1]){
		//x=(moun-2ele)/2 ele+x
		if(f)
			return moun[x]=moun[i+1]-2*ele;
		//x=(2ele-moun)/2 ele-x
		else
			return moun[x]=2*ele-moun[i+1];
	}
}
```


## #3优化

不妨扩大2优化的思想，先用暴力方程推出 $moun_1$ 在以此推出 $moun_2$,然后以此类推。例：$moun_2 = 2(ba_2-moun_1/2) = 2ba_2-moun_1$

```cpp
for(int i=1;i<n;i++){
	moun=ba[i]*2-moun;
	printf("%lld ",moun);
}
```


---

## 作者：WuMin4 (赞：11)

# 思路

其实就是一道数学题。

设每座山的水量为 $ans_i$，大坝的水量为 $w_i$，则根据题意可以得到以下方程：

$$\begin{cases}w_i=\frac{ans_i+ans_{i+1}}{2}&i<n\\w_i=\frac{ans_i+ans_1}{2}&i=n\end{cases}$$

所以只要求出任意一个 $ans$ 就可以求出剩余的 $ans$，这里我选择求 $ans_1$ 的值。

将所有 $w_i$ 加起来可以得到：
$$w_1+w_2+\cdots+w_n=ans_1+ans_2+\cdots+ans_n$$

将所有 $i$ 为奇数的 $w_i$ 加起来可以得到：
$$ w_1+w_3+\cdots+w_n=\frac{2ans_1+ans_2+\cdots+ans_n}{2}$$

于是将第二个式子的两倍与第一个式子相减便可以得到 $ans_1$。

剩下的 $ans$ 就一个一个推就行了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],tot,tot2;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		tot+=a[i];
		if(i%2==1) tot2+=a[i];
	}
	tot2=tot2*2-tot;
	cout<<tot2<<" ";
	a[0]=tot2;
	for(int i=1;i<=n-1;i++){
		a[i]=a[i]*2-a[i-1];
		cout<<a[i]<<" ";
	}
	return 0;
}

```

---

## 作者：small_john (赞：10)

## 思路

其实很简单。

设 $b$ 为答案数组，由题可得：

$$\begin{cases}a_1=\frac{b_1+b_2}{2}\\a_2=\frac{b_2+b_3}{2}\\\cdots\\a_n=\frac{b_n+b_1}{2}\\\end{cases}$$

化简，得：

$$\begin{cases}b_1+b_2=2\times a_1\\b_2+b_3=2\times a_2\\\cdots\\b_n+b_1=2\times a_n\end{cases}$$

把 $1\sim n-1$ 的式子左右两边加起来，由于 $n$ 是奇数，则有：

$$b_1-b_n=2\times a_1-2\times a_2+\cdots-2\times a_{n-1}$$

上式与第 $n$ 个式子相加，得：

$$2\times b_1=2\times a_1-2\times a_2+\cdots+2\times a_n$$

$$\therefore b_1=a_1-a_2+\cdots+a_n$$

推出 $b_1$ 后，可以推出 $b_2\sim b_n$（$b_i = 2\times a_{i-1}-b_{i-1}$）。

输出即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long//不开long long不见祖宗
using namespace std;
const int N = 1e5+5;
int n,a[N],b[N];
signed main()
{
	cin>>n;
	for(int i = 1;i<=n;i++)
		cin>>a[i];
	for(int i = 1;i<=n;i++)
		if(i%2) b[1]+=a[i];
		else b[1]-=a[i];
	cout<<b[1]<<' ';
	for(int i = 2;i<=n;i++)
		cout<<(b[i] = 2*a[i-1]-b[i-1])<<' ';
	return 0;
}
```

---

