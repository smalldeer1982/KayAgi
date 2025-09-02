# [ARC154A] Swap Digit

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc154/tasks/arc154_a

先頭の桁が $ 0 $ でない $ N $ 桁の正整数 $ A,B $ が与えられます。

あなたは、以下の操作を好きな回数（$ 0 $ 回でもよい）繰り返すことができます。

- $ 0\ \le\ i\ \le\ N-1 $ を満たす整数 $ i $ を選び、$ A,B $ の $ 10^{i} $ の位の数字を交換する。
 
操作を終えたときの $ A\ \times\ B $ の最小値を $ 998244353 $ で割ったあまりを求めてください。

$ A\ \times\ B $ を $ 998244353 $ で割ったあまりの最小値を求めるのではないことに注意してください。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 200000 $
- $ A,B $ は先頭の桁が $ 0 $ でない $ N $ 桁の正整数
 
### Sample Explanation 1

以下のように $ 1 $ 回操作を行うと $ A\ \times\ B $ を $ 276 $ にすることが出来ます。 - $ i=0 $ を選び、$ A,B $ の $ 1 $ の位の数字を交換する。$ A=12,B=23 $ となる。 $ A\ \times\ B $ を $ 275 $ 以下にすることは出来ないので、答えは $ 276 $ です。

### Sample Explanation 2

$ 998244353 $ で割ったあまりを求めてください。

## 样例 #1

### 输入

```
2
13
22```

### 输出

```
276```

## 样例 #2

### 输入

```
8
20220122
21002300```

### 输出

```
54558365```

# 题解

## 作者：Register_int (赞：3)

两数的和相等，那么两数相差越大，乘积越小。问题转化为最大化两数之差，将每位较大的数位换到 $A$ 中，较小的数位换到 $B$ 中即可。

# AC 代码
```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int MAXN = 2e5 + 10;
const int mod = 998244353;
 
int n; char a[MAXN], b[MAXN];
 
ll x, y;
 
int main() {
	scanf("%d%s%s", &n, a, b);
	for (int i = 0; i < n; i++) if (a[i] < b[i]) swap(a[i], b[i]);
	for (int i = 0; i < n; i++) x = (x * 10 + a[i] - '0') % mod, y = (y * 10 + b[i] - '0') % mod;
	printf("%lld", x * y % mod);
}
```

---

## 作者：Iniaugoty (赞：1)

小学数学题，但我想用一些奇奇怪怪的方法来讲述。

直接上结论（摘自之前某位大佬的题解）：

> 两数的和相等，那么两数相差越大，乘积越小。问题转化为最大化两数之差。

现给出证明。

***

### 命题 1： $A,B$ 两数和不变 

令 $A=\displaystyle\sum_{i=1}^n a_i\times10^{i-1}$，$B=\displaystyle\sum_{i=1}^n b_i\times10^{i-1}$，其中 $a_i,b_i$ 分别为 $A,B$ 两数从右往左第 $i$ 位上的数字，

则有 $A+B= \displaystyle\sum_{i=1}^n(a_i+b_i)\times10^{i-1}$。

由加法交换律知，$a_i+b_i=b_i+a_i$，

故交换 $A,B$ 某几位上的数，即交换某几对 $a_{i},b_{i}$，$A+B$ 的值不变。

原命题得证。

***

### 命题 2：两数和不变，差越大，乘积越小

设两个数的和为常数 $s$，差为变量 $x$，

则一个数为 $\displaystyle\frac{s+x}{2}$，另一数为 $\displaystyle\frac{s-x}{2}$。

设两数的乘积为函数 $\displaystyle\operatorname{f}(x)=(\frac{s+x}{2})(\frac{s-x}{2})$，

化简得 $\displaystyle\operatorname{f}(x)=\frac{s^2-x^2}{4}$。

对 $\operatorname{f}(x)$ 在区间 $(0,s)$ 上求导，得 $\operatorname{f'}(x)=-\displaystyle\frac{x}{2}$。

$\because$ 在区间 $(0,s)$ 上，$\operatorname{f'}(x)<0$，

$\therefore$ 在区间 $(0,s)$ 上，$\operatorname{f}(x)$ 单调减，

即两数和不变，差越大，乘积越小。

原命题得证。

***

### 最大化两数之差

这里考虑贪心，让一个数更大，另一数更小，只需要把某一位上大的数换给 $A$，小的换给 $B$ 即可（反过来也行）。

***

### 代码

如下：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int n,a,b;
string A,B;
signed main(){
	scanf("%lld",&n);
	cin>>A>>B;
	for(int i=0;i<n;i++){
		if(A[i]<B[i])
			swap(A[i],B[i]);
		a=(a*10+A[i]-'0')%mod;
		b=(b*10+B[i]-'0')%mod;
	}
	printf("%lld",a*b%mod);
	return 0;
}
```

---

## 作者：lwx20211103 (赞：0)

## 题目分析

首先我们注意到关键词，“最小化乘积”，“交换任意位”，我们可以知道这题的大概思路：贪心。而交换任意位，则说明两个数的和永远不变。而要最小化乘积，这就很好办了。这个命题反过来就是**当两个数字差最小时，乘积最大**。

这个问题证明一下。大佬可以跳到后面。


------------


首先我们设这两个数字的和为 $p$，其中一个数字为 $x$，那么我们就可以得到一个 $y$ 关于 $x$ 的函数: 

$$y = x(p - x)$$

即可得：

$$y = -x^2 + px$$

这个时候，我们可以观察到这个二次函数，因为二次项为负数，所以开口向上，存在最大值。根据二次函数的顶点公式，我们可以得到这个函数的顶点为：

$$(\frac{p}{2},\frac{p^2}{4})$$

也就是当 $x = \dfrac{p}{2}$ 时，这两个数字恰好相等，差为 $0$，乘积最大。


------------

现在回到问题，让两个数字乘积最小，就是让两个数字差最大，怎么样使两个数字差最大呢？就是遍历数字的每一位数，如果第二个数字的那一位比第一个数字大，就交换数位。有点类似于冒泡排序。这样处理完数字，就可以直接乘并且取模了。

## 代码区

用 `Python` 实现，`C++` 的楼下的大佬有，至于那个乘起来，可以像快读一样边乘边取模。

```python
n = int(input())
a = int(input())
b = int(input())
s1 = str(a)
s2 = str(b)
s1 = list(s1) #转换为列表方便操作
s2 = list(s2)
for i in range(0, n):
    if s1[i] <= s2[i]:
        temp = s1[i]
        s1[i] = s2[i]
        s2[i] = temp
        
s1 = int(''.join(s1))
s2 = int(''.join(s2))
print(s1 * s2 % 998244353)

```


---

## 作者：Daidly (赞：0)

# 题意

给定两个长度为 $n$ 的十进制数 $a,b$ 并保证首位非零，可以交换任意次 $a,b$ 任意位上的数字，求 $a\times b$ 的最大值，将结果对 $998244353$ 取模。

# 题解

显然让 $a,b$ 差值最大即可，乍一看高精度乘法（显然复杂度爆掉），冷静一下发现还有取模，对每一位拆开取模再乘起来即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long 

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int N=2e5+5,mod=998244353;
int n,a[N],b[N];
char c;

signed main(){
	n=read();
	for(int i=1;i<=n;++i){
		cin>>c;a[i]=(int)(c-'0');
	}
	for(int i=1;i<=n;++i){
		cin>>c;b[i]=(int)(c-'0');
	}
	for(int i=1;i<=n;++i){
		if(b[i]>a[i])swap(a[i],b[i]);
	}
	int tmp=1,A=0,B=0;
	for(int i=n;i>=1;--i){
		A=(A+a[i]*tmp%mod)%mod;
		tmp=tmp*10ll%mod;
	}
	tmp=1;
	for(int i=n;i>=1;--i){
		B=(B+b[i]*tmp%mod)%mod;
		tmp=tmp*10ll%mod;
	}
	print(A*B%mod);
	return 0;
}

```

---

## 作者：Crazyouth (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_arc154_a)
***
**题意简述**

给定正整数 $n$ 与两个 $n$ 位数，分别是 $A$ 和 $B$。你可以交换两个数的第 $i$ （$1\le i\le n$）个数字，使它们乘积最小，次数不限，求这个乘积。
***
**分析**

易发现，无论怎么交换数字，两数的和一定不变。根据**和一定差小积大**（见`补充`），我们可以尽量让第一个数大，而第二个数小，从而使乘积小。所以，我们对每个 $i$，如果 $A_i<B_i$，那么交换两数字。

另外，由于要取模的缘故，我们的程序框架应当是先处理 $A,B$（这里由于数太大，应当使用 string 结构），然后转为整形，最后相乘并取模。

转为整形时的取模可以每次转一个数字，然后取模，能保证转换完成后的数字是被取模后的。

最后相乘即可。
***

**AC Code**

```
#include <iostream>
#include <string>
using namespace std;
const long long MOD=998244353;
int main()
{
	long long n,x,y;//一定要用 long long!!!
	string s1,s2;
	cin>>n>>s1>>s2;
	for(int i=0;i<n;i++)
	{
		if(s1[i]<s2[i]) swap(s1[i],s2[i]);//交换
	}
   	x=s1[0]-'0';//从这里开始转为整形
   	y=s2[0]-'0';
	for(int i=1;i<n;i++)
	{
		x=x*10%MOD+(s1[i]-'0');
		y=y*10%MOD+(s2[i]-'0');
		x%=MOD;
		y%=MOD;
	}
    cout<<x*y%MOD;//最后也要有一次取模
	return 0;
}
```


***
**补充：对和一定差小积大的证明**

~~虽然这是小奥的，但还是说一下并给出证明。~~ 懂的可以不看。

命题如下：有正有理数 $a,b,c,d(a \ge b,c> d)$，满足 $a+b=c+d$ 且 $a-b<c-d$。求证 $ab>cd$。
 
证：由于 $a+b=c+d$ 且 $a-b<c-d$，所以 $m=a-\frac{x}{2}<n=c-\frac{x}{2}$。$ab=(\frac{x}{2}+m)(\frac{x}{2}-m)=\frac{x^2}{4}-m^2$，同理 $cd=\frac{x^2}{4}-n^2$。因为 $m,n>0$ 且 $m<n$，所以 $m^2<n^2$，所以 $ab=\frac{x^2}{4}-m^2>cd=\frac{x^2}{4}-n^2$。

---

