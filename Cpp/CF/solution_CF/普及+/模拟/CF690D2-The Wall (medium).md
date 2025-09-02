# The Wall (medium)

## 题目描述

Heidi the Cow is aghast: cracks in the northern Wall? Zombies gathering outside, forming groups, preparing their assault? This must not happen! Quickly, she fetches her HC $ ^{2} $ (Handbook of Crazy Constructions) and looks for the right chapter:

How to build a wall:

1. Take a set of bricks.
2. Select one of the possible wall designs. Computing the number of possible designs is left as an exercise to the reader.
3. Place bricks on top of each other, according to the chosen design.

This seems easy enough. But Heidi is a Coding Cow, not a Constructing Cow. Her mind keeps coming back to point 2b. Despite the imminent danger of a zombie onslaught, she wonders just how many possible walls she could build with up to $ n $ bricks.

A wall is a set of wall segments as defined in the easy version. How many different walls can be constructed such that the wall consists of at least $ 1 $ and at most $ n $ bricks? Two walls are different if there exist a column $ c $ and a row $ r $ such that one wall has a brick in this spot, and the other does not.

Along with $ n $ , you will be given $ C $ , the width of the wall (as defined in the easy version). Return the number of different walls modulo $ 10^{6}+3 $ .

## 说明/提示

The number $ 10^{6}+3 $ is prime.

In the second sample case, the five walls are:

```
<pre class="verbatim"><br></br>            B        B<br></br>B., .B, BB, B., and .B<br></br>
```

In the third sample case, the nine walls are the five as in the second sample case and in addition the following four:

```
<pre class="verbatim"><br></br>B    B<br></br>B    B  B        B<br></br>B., .B, BB, and BB<br></br>
```

## 样例 #1

### 输入

```
5 1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
2 2
```

### 输出

```
5
```

## 样例 #3

### 输入

```
3 2
```

### 输出

```
9
```

## 样例 #4

### 输入

```
11 5
```

### 输出

```
4367
```

## 样例 #5

### 输入

```
37 63
```

### 输出

```
230574
```

# 题解

## 作者：_ZHONGZIJIE0608_ (赞：1)

**题意简述**

求 $x_1+x_2+x_3+\cdots+x_c=k,k \in [1,n]$ 的所有非负整数解的个数。

**算法分析**

不妨设一个变量 $x_{c+1}$，使得 $x_1+x_2+x_3+\cdots+x_c+x_{c+1}=n,x_{c+1}<n$。

考虑到全部为 $0$ 的情况不合法，根据插板法，答案为 ${{n+C+1-1}\choose{C+1-1}}-1={{n+C}\choose{C}}-1$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
const int p=1e6+3;
int farc[N];
inline int Pow(int a,int b,int p){int s=1ll;while(b){if(b&1ll)s=s*a%p;a=a*a%p;b>>=1ll;}return s%p;}
inline int C(int n,int m,int p){if(m>n)return 0;return farc[n]*Pow(farc[m],p-2ll,p)%p*Pow(farc[n-m],p-2ll,p)%p;}
inline int Lucas(int n,int m,int p){if(!m)return 1ll;return 1ll*Lucas(n/p,m/p,p)*C(n%p,m%p,p)%p;}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	int n,m;cin>>n>>m;farc[0]=1;
	for(int i=1;i<=p;++i)farc[i]=(farc[i-1]*i)%p;
	cout<<(Lucas(n+m,m,p)-1+p)%p<<'\n';
	return 0;
}

```


---

## 作者：lfxxx (赞：1)

题意等价于把至多 $n$ 个相同的球放入 $C$ 个不同的盒子，可以不放，但是不能一个球都不放，求方案数。

首先考虑放入 $C+1$ 个盒子，再把最后一个丢掉，那么就需要把 $n$ 个球放完。

然后考虑放 $n+C+1$ 个球放入 $C+1$ 个盒子中，必须放，最后每个盒子丢掉一个球，等价于原问题。

那么答案就是 ${n+C \choose C}-1$。最后减 $1$ 是因为不能一个球都不放。



---

## 作者：minecraft_herobrine (赞：1)

### 题意

现在你有 $n$ 个砖和一个宽度为 $C$ 的场地。你可以想象成这个场地是一个高度无限，宽度为 $C$ 的矩形。

每个砖占据一个位置，这个位置记作'B'，没有砖块的地方记作 '.'

问最后可以摆出多少种不同的形状（'.'和'B'只要排列的不同就算不同方案），方案数 $\mod 1e6+3$

### 题解

设 $C(n,m),(n>m)$ 表示从 $n$ 个不同物品中取出 $m$ 个物品的组合数，比如 $C(4,2)=2$

如果把这个矩形分解成 $C$ 列，我们可以发现问题被转换成了：

有 $C$ 个自然数 $a_1,a_2,a_3,...,a_C$ ，对于任意的 $a_i$，$0\le a_i\le n$，你可以自由安排它们的值，但要求所有数的和恰好等于 $n$，问有多少种情况来安排这些数的值。

是不是有那味儿了？

按照这个转换后的题意继续转换：

有 $C$ 个盒子，$n$ 个球，你现在需要把所有球装进盒子里，允许盒子为空，盒子容积无限。问有多少种装球的方案。

这个问题可以用排列组合来解决

把所有球排成一排，用插板法需要插 $C$ 个板，允许板相邻。但这个方法有一个问题就是你无法确定这些板会有几个板撞在一起，以及板会在哪里相邻。如果这样说就可以用组合数直接计数了:

把球和板看成一个东西，排成一排，显然有 $n+C$ 个东西。你现在要选出 $C$ 个东西把它变成板，剩下的都变成球，问有多少种选法

这样不就简单了，直接 $C(n+C,C)$ 就是答案了

注意 $C(n,m)=\frac{n!}{m!\times(n-m)!}$，由于有除法，所以取模时需要用到逆元，这个用费马小定理+快速幂就能解决啦

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod=1e6+3;
ll qpow(ll base,ll p)
{
	ll res=1;
	while(p>0)
	{
		if(p&1) res=(res*base)%mod;
		base=(base*base)%mod;
		p>>=1;
	}
	return res;
}
ll C(ll n,ll m)
{
	m=min(m,n-m);
	ll a=1,b=1,i;
	for(i=1;i<=m;i++)
	{
		a=a*i%mod;
		b=b*(n+1-i)%mod;
	}
	a=qpow(a,mod-2);
	return (a*b)%mod;
}
int main()
{
	ll n,m;
	scanf("%lld %lld",&n,&m);
	printf("%lld",(C(n+m,m)+mod-1)%mod);
	return 0;
}
```


---

## 作者：Cynops (赞：0)

## Sol

题意就是求 $x_1 + x_2 + x_3 + \cdots + x_c = k,k\in [1,n]$ 的所有非负整数解的个数。

考虑虚拟一个变量 $x_{c+1}$，方程变为：$x_1 + x_2 + x_3 + \cdots + x_{c+1} = n,x_{c+1} < n$

答案即为：

$${{n + C + 1 - 1}\choose {C + 1-1}} -1 = {{n + C} \choose {C}} - 1$$

```cpp
#include<bits/stdc++.h> 
using namespace std;
#define int long long

const int N = 1e6 + 5, p = 1e6 + 3;

int n,m;
int fac[N];
int Qpow(int x,int y){
	int ans = 1;
	while(y){
		if(y & 1) ans = ans * x % p;
		x = x * x % p;
		y >>= 1;
	}
	return ans;
}
int Cal(int n,int m){
	return fac[n] * Qpow(fac[n - m],p-2) % p * Qpow(fac[m],p-2) % p;
}
signed main(){
	cin.tie(0) -> ios::sync_with_stdio(0);
	int n,c;
	cin >> n >> c;
	fac[0] = 1;
	for(int i = 1;i <= n + c;i ++)
		fac[i] = fac[i - 1] * i % p;
	cout << (Cal(n + c,c) + p - 1) % p;
	return 0;
}
```


---

## 作者：ant2010 (赞：0)

## 题意概括
题目中告诉我们有 $n$ 块砖，$C$ 个位置摆放这些砖块。

需要注意的是：**不需要摆放所有的砖**。

## 分析
我们不妨枚举一个 $k$ 表示摆放了多少块砖。

那么问题转化为求不定方程：
$$x_1+x_2+x_3+\cdots +x_C=k\left(\forall i,x_i\ge0\right)$$
做一下变形：
$$(x_1+1)+(x_2+1)+(x_3+1)+\cdots+(x_C+1)=C+k\left(\forall i,x_i\ge1\right)$$

我们想象有 $C+k$ 个球，中间有 $C+k-1$ 个空隙，在其中插入 $C-1$ 块板，则被板隔出的每个区域中球的个数都会对应一个 $x_i$。

所以上面的不定方程解的个数为 $C_{C+k-1}^{C-1}$。

那么原问题的答案就为：
$$\sum_{k=0}^n C_{C+k-1}^{C-1}$$

预处理阶乘，可做到 $O(n\log q)$ 的复杂度，其中 $q$ 为模数 $10^6+3$，可以通过此题。

## 优化
我们还可以做到更低的复杂度。

将上面的式子写成如下形式：
$$\begin{aligned}
&C_{C-1}^{C-1}+C_{C}^{C-1}+C_{C+1}^{C-1}+\cdots +C_{C+n-1}^{C-1}\\
=&C_{C}^{C}+C_{C}^{C-1}+C_{C+1}^{C-1}+\cdots +C_{C+n-1}^{C-1}\\
=&C_{C+1}^{C}+C_{C+1}^{C-1}+C_{C+2}^{C-1}+\cdots +C_{C+n-1}^{C-1}\\
=&C_{C+2}^{C}+C_{C+2}^{C-1}+\cdots +C_{C+n-1}^{C-1}\\
=&C_{C+n}^C
\end{aligned}$$

求组合数即可。

**update：当 $x_1=x_2=x_3=\cdots=x_C=0$ 时不合法，所以最终需减去 $1$。**
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int const M=1e6+3;
int const maxn=7e5+5;
ll jc[maxn];
int qpow(ll x,int y){
	ll res=1;
	while(y){
		if(y&1)res=res*x%M;
		x=x*x%M;
		y>>=1;
	}
	return res;
}
int main(){
	int n,c;
	scanf("%d%d",&n,&c);
	n+=c;
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%M;
	printf("%lld",jc[n]*qpow(jc[c],M-2)%M*qpow(jc[n-c],M-2)%M-1);
}
```

---

