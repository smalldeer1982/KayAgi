# New Bakery

## 题目描述

### 题意

有一个长度为 $n$ 的数列和两个常数 $a,b$ 以及一个正整数 $k(1 \leq k \leq n)$，数列按以下方式构造：

- 对于前 $k$ 项，第 $i$ 项的值为 $b-i+1$；
- 对于剩下的项，每一项的值都为 $a$。

整数 $k$ 的值由你决定，但你需要保证数列中所有的项均为**非负整数**。在此条件下，你需要求出这个数列的和的最大值。

## 样例 #1

### 输入

```
7
4 4 5
5 5 9
10 10 5
5 5 11
1000000000 1000000000 1000000000
1000000000 1000000000 1
1000 1 1000```

### 输出

```
17
35
100
45
1000000000000000000
1000000000000000000
500500```

# 题解

## 作者：canwen (赞：3)

一眼构造分类讨论，可惜还要用数列求和的一点入门知识，所以来水一发题解。

~~反正我是卡了很多次的。~~

## 题意
$T$ 组数据，有一个长度为 $n$ 的数列和两个常数 $a,b$ 以及一个正整数 $k(1 \leq k \leq n)$，数列按以下方式构造：

- 对于前 $k$ 项，第 $i$ 项的值为 $b-i+1$；
- 对于剩下的项，每一项的值都为 $a$。

整数 $k$ 的值由你决定，但你需要保证数列中所有的项均为**非负整数**。在此条件下，求出这个数列的和的最大值。

## 分析
遇到类似题目只有**两种**情况，且需要求出**最优解**或者**最坏解**的题目，直接列出式子分类讨论。

- 当 $a \ge b$，不需要讨论 $b$ 的出现情况，使用 $a$ 已经是最优解。
- 当 $a < b$，最大的第 $k$ 项只有当大于 $a$ 时且最大的时候才能保证答案最大，值列出式子 $b-k+1 > a$，求出 $k$ 的取值范围 $k < b-a$，即最大 $k = b-a-1$。特别的，如果 $k > n$，则最大只能是 $n$。

由此列出主要代码：
```cpp
if(a>=b) ans=n*a;
else{
	k=min(n,b-a);
	ans+=(n-k)*a;		
	for(int i=1;i<=n;i++) ans+=b-i+1; 
}
cout<<ans<<endl; 
```
很好，现在该解决 TLE 的问题了。

我们从刚刚的答案可得知，这个数列的前 $k$ 项分别是 $b+1-1,b+1-2,b+1-3,\dots,b+1-k$。令 $x=b+1$，则得到 $x-1,x-2,x-3,\dots,x-k$。

~~裸的~~等差数列计算：头项和尾项的和再乘以项数，最后除以 $2$。

由此得到对应的计算式子，
$$(x-1+x-k)\times k\div 2 = (2  x-1-k) \times k\div2$$

带入 $x$ 计算，得，

$$(2 x-1-k) \times k\div2=(2b+2-1-k)\times k\div2=(2 b+1-k)\times k\div2$$

完美解决！
## Code
```cpp
#include<iostream>
using namespace std;
#define ll long long
int main(){
	ll T,n,a,b;//防止爆int 
	cin>>T;
	while(T--){
		cin>>n>>a>>b;
		ll k=min(n,b-a),ans=0;
		if(a>=b) ans=n*a;//a是最优解，无需b参与 
		else{
			k=min(n,b-a);
			ans+=(2*b+1-k)*k/2+(n-k)*a;//刚刚的公式 
		}
		cout<<ans<<endl; //ans~
	}
	return 0;//good habit~
}
```

---

## 作者：wimg6_ (赞：2)

翻了一下大家做法，都好麻烦啊，其实完全没必要所谓的二次函数。

根据题目，我们会发现一块面包的价格要么是 $b-i+1$，要么是 $a$。

直接贪心，对于 $b-i+1\geq a$ 时选择 $b-i+1$，否则选择 $a$，这个正确性是显然的，因为 $b-i+1$ 会随着 $i$ 增加而递减，即对第一个不满足 $b-i+1\geq a$ 的情况的 $i$ 我们会选择 $a$，其后面一定还是会选择 $a$ 而不是 $b-i+1$。

考虑化简 $b-i+1\geq a$：

$$b-i+1\geq a$$

$$\Leftrightarrow -i\geq a-b-1$$

$$\Leftrightarrow i\leq b+1-a$$

这样我们就得到 $k=b-a+1$。

答案是 $\sum_{i=1}^k(b-i+1)+(n-k)\times a$，使用等差数列求和公式，得到答案为 $-\dfrac{k\times (k+1)}{2}+k+b\times k+(n-k)\times a$。虽然没有化到最简形式，但是已经可以快速求出并且不溢出了。直接把求得的 $k$ 带入上述公式即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a,b;
int main(){
    scanf("%lld",&t);
    while(t--){
        scanf("%lld%lld%lld",&n,&a,&b);
        long long k=max(0ll,b-a+1);
        if(k>n) k=n;
        printf("%lld\n",-k*(k+1)/2ll+k+b*k+(n-k)*a);
    }
    return 0;
}
```

**更新日志**

修改了一处笔误。

---

## 作者：cute_overmind (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1978B)
### 题目大意
给你 $n$ 个面包，每一个价格为 $a$。

下面进行操作：
- 将其中的 $k$ 个面包降价，其中第 $i$ 个的价格为 $(b-i+1)$。
- 将剩下 $n-k$ 个面包原价出售。

### 题目分析
一道数学题。

设 $W$ 为总利润，那么在降价了 $k$ 个面包后的价格为：
$$W=\frac{k\cdot(2b-k+1)}{2} + a\cdot(n-k)$$

化简一下可以得到：
$$W=-\frac{1}{2}\cdot k^2 +k(b-a+\frac{1}{2}) + a\cdot n $$
易发现，这个很难看的式子貌似是一个二次函数。

因为我们选择的 $k$ 个面包是整数，所以我们只需要保证 $k$ 与 $b-a+\frac{1}{2}$ 尽量接近即可。

代码不贴了。

---

## 作者：一只小菜包 (赞：2)

## 题目分析

很好的数学题。

如果 $b<a$ 则不改价格出售，如果 $b≥a$ 则按 $b$ 的价格出售。

设 $S$ 为总利润，那么在降价了 $k$ 个面包后的价格为：

$$ S = \sum_{i=1}^{k} (b - i + 1) + a \cdot (n - k) $$

经过简单的化简即可化简成以下两个公式：

$$ S = kb - \frac{k^2 - k}{2} + k + an - ak $$

$$ S = -\frac{1}{2}k^2 + \left(b + \frac{1}{2} - a\right)k + an $$

代码就不贴了。

---

## 作者：fangminding (赞：1)

很有意思的一道数学题。

为了求最大值，我们分两步分析，先找出 k 的可行范围，再考虑 k 取不同值时数列和的情况求出最大值。

关于 k 的取值范围，原题面已经给出了条件 $ 0 \le k \le \min(n, b) $，不过还有一个条件：数列每一项为非负数。
经验证，数列最小值取在第 k 项，为 $b-k+1$，当 k 满足题面条件 $ 0 \le k \le \min(n, b) $ 时，数列最小值 $b-k+1$ 总大于 $0$。故条件满足。

接下来要求 k 取什么值使数列和最大。由等差数列求和公式可得数列和为 $\frac{(b+(b-k+1))×k}{2}+(n-k)×a$。化简得关于 k 的二次函数，再用数学方法分讨区间最大值即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
void solve()
{
	int n,a,b;
	cin>>n>>a>>b;
	long double A=-0.5,B=b-a+0.5,C=a*n;
	long double d=-B/2.0/A;
	int d2=floor(d+0.5);
	if(d2<0)cout<<int(C)<<endl;
	else if(d2>min(n,b))cout<<int(A*min(n,b)*min(n,b)+B*min(n,b)+C)<<endl;
	else cout<<int(A*d2*d2+B*d2+C)<<endl;
	return;
}
signed main()
{
	int T;cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：KyleShen1213 (赞：1)

## 题目大意
鲍勃有 $n$ 个面包，原价每个 $a$ 元，他计划将前 $k$ 个面包以新的价格售卖，其中第 $i$ 个面包的售价为 $\left ( b-i+1 \right ) $ 元，你要使鲍勃得到最多的钱。（$k$ 的值由你来确定）

## 题目思路
若 $a\ge b$，肯定不改价格划算。

若 $a< b$,前 $\left ( b-a \right ) $ 个面包肯定改价格后划算，具体的计算公式我在代码里写了，这里就不写了。但要特判如果 $b-a>n$，那么就全都改价格。

## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,a,b,n,ans;
int main()
{
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>n>>a>>b;
		if(a>=b)  ans=a*n;//a>=b，原价 
		else
		{
			if(b-a<=n)  ans=(b-a)*(a+b+1)/2+a*(n-b+a);
			else  ans=(b-n+b+1)*n/2;//特判 
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：fengxiaoyi (赞：1)

首先当 $a\ge b$ 时，$k$ 取 $0$ 即可。

当 $a\lt b$ 时，要想是利润尽可能大，必须满足前 $k$ 天的利润都比 $a$ 大，即要满足 $b-k\ge a$。可以得出 $k$ 最大为 $b-a$，然后计算即可。

还需注意的是，$k$ 需要满足不超过 $\min(n,b)$ 的限制，所以最终 $k=\min\{n,b-a\}$，答案为 $\frac{(b+b-k+1)k}{2}+(n-k)a$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long long n,a,b;
int main(){
	scanf("%d",&t);
	while(t--){
	    scanf("%lld%lld%lld",&n,&a,&b);
		if(a>=b){
			printf("%lld\n",n*a);
			continue;
		}
		long long k=min(n,b-a);
		printf("%lld\n",(b+b-k+1)*k/2+a*(n-k));
	}
	return 0;
}
```

---

## 作者：szh_AK_all (赞：1)

### 分析
若选择让 $x$ 个包子的价格改变，则根据等差数列，获得的利润为：$f(x)=\frac{(2\times b-x+1)\times x}{2}+(n-x)\times a=-\frac{x^2}{2}+(b+\frac{1}{2}-a)\times x+n\times a$，显然，这个式子可以理解为一个二次函数。那么我们需要求出该二次函数的最大值，将式子改为顶点式得：$f(x)=-\frac{1}{2}\times(x-b-\frac{1}{2}+a)^2+\frac{2\times n\times a+(b+\frac{1}{2}-a)^2}{2}$。

由于 $x$ 必须为整数，所以应当让 $x$ 与 $b+\frac{1}{2}-a$ 接近，那么枚举下 $x$ 的值为 $b+\frac{1}{2}-a$ 附近的数，求出 $f(x)$ 的最大值即可。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int o;

signed main() {
	int t;
	cin >> t;
	while (t--) {
		int n, a, b;
		cin >> n >> a >> b;
		unsigned long long ans = 0;
		int x = max(o, b - a);
		x = min(x, min(n, b));
		for (int i = max(o, x - 2); i <= min(min(n, b), x + 2); i++) {
			unsigned long long tmp = 1uLL * (2 * b - i + 1) * i / 2 + (n - i) * a;
			ans = max(ans, tmp);
		}
		ans = max(ans, 1uLL * n * a);
		cout << ans << endl;
	}
}
```

---

## 作者：Brute_Force (赞：0)

### 思路
分类讨论以下情况：

- 当 $a \ge b$ 时，最优解就是不改价格，根据推导可知最大值是 $n \times a$。
- 当 $a < b$ 时，构造一个等差数列由 $b$ 到 $b+1-k$，这个等差数列的和还需加上 $(n-k)\times a$，简化可得答案为 $\frac{b(b+1-k)k}{2}+(n-k)\times a$。

这就是本题的所以思考及推导过程。
***
### 代码
```cpp
#include<iostream>
#include<stdio.h>
#include<cmath> 
using namespace std;
int main()
{
	long long t,n,a,b,i,k;
	cin>>t;
	for(i=1;i<=t;i++)
	{
		cin>>n>>a>>b;
		k=min(n,b-a);
		if(a>=b) cout<<n*a<<endl;
		else cout<<(b+(b-k+1))*k/2+(n-k)*a<<endl;
	}
	return 0;
}

---

## 作者：xcms (赞：0)

# CF1978B New Bakery 题解

首先如果 $b\le a$，就是原来的价格，也就是 $a\times n$。

如果 $a < b$，那只有在 $b-i+1 > a$ 的时候，我们才会考虑更换价格，而题目中的 $k$ 就是公式当中的 $i$。等式左边的最小值是 $a+1$，所以 $b-i=a$，$i=k=b-a$。

所以我们就可以的到了一个等差数列：$b,(b-1),(b-2),......,(b-k+1)$。所以这个求和方法是 $\frac{(b+(b-k+1))×k}{2}$。这样，就可以知道改变价格的总价。

然后我们求出不该变价格的总价，首先单价为 $a$，数量为 $n-k$，总价为 $(n-k)×a$。

把他们相加是：$\frac{(b+(b-k+1))×k}{2}+(n-k)×a$。

这道题要注意的坑点是：$k$ 可能会大于 $n$，所以要进行特判。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a,b;
signed main(){
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	cin>>t;
	while(t--){
		cin>>n>>a>>b;
		int k=min(n,b-a);
		if(a>=b)cout<<n*a<<"\n";
		else cout<<(b+(b-k+1))*k/2+(n-k)*a<<"\n";
	}
	return 0;
}
```

---

## 作者：HsNu1ly7_ (赞：0)

## 思路

如果 $b<a$ 则按原价出售，如果 $b\ge a$ 则按 $b$ 的价格出售。

可以发现如果降价，利润的计算公式是一个等差数列：
$$
\frac{k(b + b - k + 1) }{2} + a( n - k )
$$

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
void solve (){
	int n , a , b ;
	cin >> n >> a >> b ;
	int k = min ( b - a , n ) ;
	if ( b < a ){
		cout << n * a << '\n' ;
	}else{
		cout << ( b + b - k + 1 ) * k / 2 + ( n - k ) * a << '\n' ;
	}
	return ;
}
signed main (){
	ios::sync_with_stdio(0) ;
	cin.tie(0) ;
	cout.tie(0) ;
	int _ ;
	cin >> _ ;
	while ( _-- ){
		solve () ;
	}
	return 0 ;
}
```

---

## 作者：zhangxiaohan007 (赞：0)

## 思路
由题可得，我们要让收益最大化，很显然我们修改后 $k$ 个包子的价格是要大于 $a$ 的，所以很显然，价格只能在 $a+1$ 到 $b$ 的区间内，又因为要让价格尽量大，所以 $k$ 就是 $n$ 和 $a-b$ 之间取最小值，然后用等差数列求和公式算出那 $k$ 个包子的价格再加上剩下 $n-k$ 个包子的价格即可算出答案。还有别忘了开 ``long long``。

---

## 作者：linjinkun (赞：0)

这么大数据范围，肯定是个数学题。

很容易发现我们如果选择了一个 $k$，那么这 $k$ 个包子的价钱总合就是 $\sum_{i = 1}^b - \sum_{i = 1}^{b-k}$，也就是 $(b+1) \times b \div 2 - (b-k+1) \times (b-k) \div 2$，那么我们发现我们一定要让这 $k$ 个包子每个包子的价格都应该比 $a$ 大。于是我们只能选 $a+1 \sim b$ 这些价格的包子，所以最多只能选 $b-a$ 个包子，而选少了的话又会不是最优解，所以我们要选 $k = \min(b-a,n)$，因为 $b-a$ 有可能大于 $n$，那么这道题就做完了。

**请注意，要开 ```long long```。**

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
signed main()
{
	int t;
	scanf("%lld",&t);
	while(t--)
	{
		int n,a,b;
		scanf("%lld %lld %lld",&n,&a,&b);
		if(b<a)//如果这种情况一定全部按原价卖
		{
			printf("%lld\n",a*n);
			continue;
		}
		int k = min(b-a,n);//上面说的
		printf("%lld\n",(b+1)*b/2-(b-k+1)*(b-k)/2+(n-k)*a);//等差数列求和公式的运用，上面也说过
	}
	return 0;
}
```

---

## 作者：sea_bird (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1978B)。

# 题目大意

有一批面包打折，可以按原价出售也可以按折扣出售~~怎么比原价贵~~折扣的意思就是给定第一个面包的价钱，后面的面包每个售价是第一个的售价减去此时面包在那一批的序列号，求最大利润。

# 解题思路

什么时候是最大利润？就是看每个面包按折扣卖的贵还是按原价卖的贵，但我们不需要一个一个的去判断，我们只需要在一开始判断一下是否第一个面包的售价就比原价低（用折扣时）如果是就整个来按原价出售（第一个面包就比原价低，后面的也会一样）如果更高就享受折扣，我直接一个模拟，用一个循环来计算按折扣最多能卖多少，再加上剩下的折扣比原价低的~~就结束了~~然后就时间超限了。

```
for(long long i=1;i<=min(n,b-a);i++){
			sum+=b-i+1;
		}
		n-=min(n,b-a);
		sum+=n*a;
```

很显然这个方法行不通，即使是加上快读以后依然时间超限，那么按照原有的思路用直接计算来取代循环。因为价格为等差数列，找到在不低于原价的情况下的最高价和最低价（可能等于原价）再用**高斯求和公式**来计算，最后我优化了代码。

# Code

```
#include<bits/stdc++.h>
using namespace std;
long long ans(long long n,long long a,long long b){//注意数据范围
	if(b-a>0){//判断第一个的价格是否大于原价
		long long sum=0,x;
		if((b-a+1)>=n){//当折扣价大于原价期间，面包售罄
			x=b-n+1;//求出最低价
			sum=(b+x)*n/2;//高斯求和公式
		} 
		else{
			x=b-(b-a)+1;
			sum=(b+x)*(b-a)/2;
			sum+=(n-(b-a))*a;//折扣之外的按原价出售
		}
		return sum;
	}
	else{//判断第一个的价格是否不大于原价
		return n*a;
	}
} 
int main(){
	long long t;
	long long n,a,b;
	cin>>t;
	for(long long i=1;i<=t;i++){
		cin>>n>>a>>b;
		cout<<ans(n,a,b)<<endl;
	}
	return 0;
}
```

## 总结

那么这道题就做出来了，我在做的时候首先是因为函数中没开 `long long` 而错，接着便是时间超限了，写这类题目还是要注意一些。

---

## 作者：GeYang (赞：0)

# 题意

有 $n$ 个面包，每个卖 $a$ 元，其中 $k$ 个降价出售，第 $i$ 个售价为 $(b-i+1)$ 的同时将剩下的原价出售，求最大收款。

# 分析

如果 $a \ge b$ 还要使得到的钱最多，那么不能降价出售。

如果 $a < b$ 还要使得到的钱最多，那就直接求降价出售部分的钱加上原价出售部分的钱。降价部分的总价是一个等差数列。

等差数列求和公式如下，其中 $x$ 表示首项且 $y$ 表示末项且 $z$ 表示项数且 $S$ 表示总和。

$$S=\frac{(x+y)\times z}{2}$$

带入求值即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a,b,k;
void solve()
{
	cin>>n>>a>>b;
	if(a>=b)
	{
		cout<<n*a<<endl;
	}
	else
	{
		k=min(n,b-a);
		cout<<(b-1+1+b-k+1)*k/2+a*(n-k)<<endl;
	}
}
int main()
{
	cin>>t;
	while(t--)
	{
		solve();
	} 
}
```

---

## 作者：SpringFullGarden (赞：0)

## 题意

给定 $n, a, b$，求 $\max \limits_{x = 0}^{min(n, b)} \sum \limits_{i = 1} ^ x(b - i + 1)+ a(n - x)$

## 思路

数学题。

化简，得 $\max \limits_{x = 0}^{min(n, b)} - \frac{1}{2} x ^ 2 + (b - a + \frac{1}{2}) x + a \cdot n$。

可以看成是一个开口朝下的二次函数，设 $A = -\frac{1}{2}, B = (b - a + \frac{1}{2}), C = a \cdot n$，则对称轴为 $-\frac{B}{2A}$。

因为 $x$ 是整数，且要使结果最大，所以 $x = \left \lfloor -\frac{B}{2A} \right \rfloor$。

特别地，因为 $0 \le x \le \min(n, b)$，所以当 $-\frac{B}{2A} > \min(n, b)$ 时，$x = \min(n, b)$；当 $-\frac{B}{2A} < 0$ 时，$x = 0$。

最后答案为 $Ax^2 + Bx + C$。

## 代码

```cpp
ll n = rd(), a = rd(), b = rd();
long double A = -0.5, B = b - a + 0.5;
ll C = a * n, x = -B / 2.0 / A;
if(x > min(n, b)) x = min(n, b);
if(x < 0) x = 0;
ll ans = A * x * x + B * x + C ;
cout << ans << '\n';
```

---

## 作者：Special_Tony (赞：0)

# 思路
显然，每个馒头会使用较高的价格卖出，所以在 $b-i+1=a$ 以前，即 $i=\max(\min(b-a,n),0)$ 前，此时 $b-i+1>b-(b-a)+1=a+1>a$，第一种方案较贵可以使用，就使用 $b-i+1$ 卖掉，否则就使用较贵的第二种方案用 $a$ 元一个的价格卖掉。设 $t=\max(\min(b-a),0)$，则总和 $=b+(b-1)+(b-2)+\dots+(b-t+1)+(n-t)\times a=\frac{t(b+b-t+1)}2+(n-t)\times a$。

[Code](https://codeforces.com/contest/1978/submission/265984488)。

---

## 作者：linch (赞：0)

## 题意
给定三个整数 $n,a,b$，Bob 有 $n$ 个面包，原售价是 $a$ 元每个，他将前 $k$ 个面包以新的价格售卖，其中第 $i$ 个面包的价格是 $(b-i+1)$ 元，$k$ 的值由你决定，可以是 $0$ 至 $n$ 之间的任意整数，请你求最大能得到的钱。

## 分析
若 $a\ge b$，由于改价后这 $k$ 个面包售价均不大于 $b$，那么肯定是不改价划算，答案为 $n\times a$。

否则，易得前 $(b-a)$ 个面包的价格一定大于原售价，使用改价后价格出售。可用等差数列求和公式求出总价。剩余 $(n-b+a)$ 个面包按原售价出售即可，表达式如下：

$$
(a+b+1) \times (b-a) \div 2 + a \times (n-b+a)
$$

注意要特判：如果 $b-a > n$，那么运用求和公式计算时的 $b-a$ 需改为 $n$，此时可化简公式为

$$
(b-n+1+b) \times n \div 2
$$

注：为了方便理解，表达式均未化到最简。

## 代码
根据上一部分模拟即可。
```cpp
#include<iostream>
#include<cmath>
using namespace std;
unsigned long long t,a,b,n;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>a>>b;
		if(a>=b){//上述第一种情况。
			cout<<a*n<<endl;
		}
		else{//上述第二种情况。
			if(b-a>n){//特判。
				cout<<(b-n+1+b)*n/2<<endl;
			}
			else cout<<(a+b+1)*(b-a)/2+a*(n-b+a)<<endl;
		}
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/163496159)

---

## 作者：xu_zhihao (赞：0)

### 题目理解

* 简单数学好题，和等差数列差不多。思路就是如果 $a\le b$，就将序列替换，替换长度为 $n$ 与 $b-a$ 取小值。

### AC 代码：

```cpp

#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		long long n,a,b;
		cin>>n>>a>>b;
		long long k=min(n,b);
		long long sum=n*a;
		if(b>=a)sum+=((b-a)+max(b-a-k+1,1ll))*(min((b-a),k))/2;
		//10 1 10
		//10 9 8 7 6 5 4 3 2
		cout<<sum<<endl;
	}
}
```

---

