# Cube Problem

## 题目描述

Yaroslav, Andrey and Roman love playing cubes. Sometimes they get together and play cubes for hours and hours!

Today they got together again and they are playing cubes. Yaroslav took unit cubes and composed them into an $ a×a×a $ cube, Andrey made a $ b×b×b $ cube and Roman made a $ c×c×c $ cube. After that the game was finished and the guys left. But later, Vitaly entered the room. He saw the cubes and wanted to make a cube as well. But what size should the cube be? Of course it should be a large cube with the side of length $ a+b+c $ . Besides, Vitaly decided to decompose the cubes built by Yaroslav, Andrey and Roman and compose his own large cube out of them. However, it turned out that the unit cubes he got from destroying the three cubes just weren't enough to make a large cube. We know that Vitaly was short of exactly $ n $ cubes. Vitaly got upset, demolished everything and left. As he was leaving, he met Petya and told him that there had been three cubes in the room and that he needed another $ n $ unit cubes to make his own large cube.

Petya entered the room and saw the messily scattered cubes. He wanted to make it neat and orderly again. But he only knows that there had been three cubes, made of small unit cubes and that Vitaly needed $ n $ more unit cubes to make a large one! Help Petya understand, how many ways of sizes $ a $ , $ b $ , $ c $ are there to restore Yaroslav's, Andrey's and Roman's cubes.

## 样例 #1

### 输入

```
24
```

### 输出

```
1
```

## 样例 #2

### 输入

```
648
```

### 输出

```
7
```

## 样例 #3

### 输入

```
5
```

### 输出

```
0
```

## 样例 #4

### 输入

```
93163582512000
```

### 输出

```
39090
```

# 题解

## 作者：jianhe (赞：4)

### 前言：
推式子题。

### 思路：
#### 转化题意：
首先拆掉题目中的式子，得：$(a+b+c)^3-a^3-b^3-c^3=3(a+b)(b+c)(c+a)$。

换元法，令 $x \leftarrow a+b,y \leftarrow b+c,z \leftarrow c+a$。

则题目转化为：求 $3xyz=n$ 的正整数解个数。

#### 细节考虑：

先特判掉 $n$ 不是 $3$ 的倍数的情况。

考虑细节：要保证 $a,b,c$ 为正整数。


钦定 $x \le y \le z$。

我们有：

$$ \left\{
\begin{aligned}
x & =  a+b \\
y & =  b+c \\
z & =  c+a
\end{aligned}
\right.
$$

三式相加，得 $x+y+z=2a+2b+2c$。

即 $\frac{x+y+z}{2}=a+b+c$。

令 $T \leftarrow \frac{x+y+z}{2}$，可得：

$$ \left\{
\begin{aligned}
a & =  T-y \\
b & =  T-z \\
c & =  T-x
\end{aligned}
\right.
$$


可以发现，$a,b,c$ 为正整数当且仅当 $T$ 为正整数且 $T>z$。

#### 统计答案：
观察数据范围，$1 \le n \le 10^{14}$，开三次方后约为 $46416$，因此考虑枚举 $x$ 和 $y$ 来统计答案。

由于我们钦定了 $x \le y \le z$，所以在统计答案时要加上 $a,b,c$ 的排列组合。讨论 $a,b,c$ 的大小关系，若三个都相同则加上 $1$，若其中两个相同加上 $3$，否则加上 $6$。

于是有类似下面的代码（会超时）：

```cpp
for(ll x=1;x*x*x<=n;x++)
		if(!(n%x))
			for(ll y=x,z,T;x*y*y<=n;y++){
				z=n/x/y;T=(x+y+z)>>1;
				if(x*y*z!=n||T<=z||((x+y+z)&1)) continue;
				if(x==y&&y==z) ans++;//这里x和y的大小关系等价于a和b的大小关系
				else if(x==y||y==z) ans+=3;//若x==z则x==y==z
				else ans+=6;
			}
```

#### 优化复杂度：
这样跑得飞慢，实测样例四 $n=93163582512000$ 跑了 $10.6$ 秒。

我们发现，程序会遍历到许多 $T \le z$ 的无用状态。

能不能优化呢？

##### 法一：
可以倒着枚举 $y$，$T \le z$ 时直接 `break`。

##### 法二：
有（这里的 $n$ 是除过 $3$ 之后的）

$$ \left\{
\begin{aligned}
xyz & =n \\
\frac{x+y+z}{2} & \ge z 
\end{aligned}
\right.
$$

转化为：

$$ \left\{
\begin{aligned}
z & = \frac{n}{xy} \\
\frac{x+y+z}{2} & \ge z 
\end{aligned}
\right.
$$

将上式代入下式，得 $x+y>\frac{n}{x+y}$。

两边同乘 $x+y$，并将 $y$ 看为主元，得 $x \times y^2 + x^2 \times y - n > 0$。

由于 $y \le x$，舍去小的一部分，解得 $y > \frac{-x^2+\sqrt{x^4+4nx}}{2x}$。

带入代码即可。

### 代码：
#### 法一：
```cpp
//by classmate (shorter than mine)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n,ans;
signed main()
{
	scanf("%lld",&n);
	if(n%3ll){ printf("0\n"); return 0; } n/=3ll;
	for(ll i=2ll;i*i*i<=n;++i) if(n%i==0){
		ll sq=floor(sqrt((double)n/(double)i));
		for(ll j=sq;j>=i;j--) if((n/i)%j==0){
			ll k=n/i/j;if(i+j<=k) break;
			if(j>k||((i+j+k)&1)) continue;
			if(i==j&&j==k) ans++;
			else if(i==j||j==k||i==k) ans+=3ll;
			else ans+=6ll;
		}
	}printf("%lld\n",ans);
	return 0;
}
```

#### 法二：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,ans;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	if(n%3){cout<<0;return 0;}
	n/=3;
	for(ll x=1;x*x*x<=n;x++)
		if(!(n%x))
			for(ll y=max(x,(ll)((-x*x+sqrt(x*x*x*x+4*n*x))/2/x)),z,T;x*y*y<=n;y++){
				z=n/x/y;T=(x+y+z)>>1;
				if(x*y*z!=n||T<=z||((x+y+z)&1)) continue;
				if(x==y&&y==z) ans++;//这里x和y的大小关系等价于a和b的大小关系
				else if(x==y||y==z) ans+=3;
				else ans+=6;
			}
	cout<<ans;
	return 0;
}

```

---

## 作者：minecraft_herobrine (赞：1)

UPD:修正了①式中 $3a^c$ 的错误

----

化简一下这里的式子：

$(a+b+c)^3$

$=[(a+b)+c]^3$

$=(a+b)^3+3(a+b)^2c+3(a+b)c^2+c^3$

乘开按降幂排序，得

$a^3+b^3+c^3+3a^2b+3ab^2+3b^2c+3bc^2+3ac^2+3ac^2+6abc$············①

因为题目要求的是 $(a+b+c)^3-a^3-b^3-c^3$，所以我们在①中去掉 $a^3,b^3,c^3$，得到

$3a^2b+3ab^2+3b^2c+3bc^2+3ac^2+3ac^2+6abc$

分解因式，得到

$3(a+b)(b+c)(a+c)$

也就是说，题目让我们求三元三次不定方程 $3(a+b)(b+c)(a+c)=n$ 有多少个不同的解 $a,b,c$ 

设 $a+b=x\ ,\ b+c=y\ ,\ a+c=z$

则就是求 $3xyz=n$ 的 $x,y,z$ 个数

设 $a\le b\le c$，则 $x\le y\le z$

然后就分别枚举 $x,y,z$ 就好了，并且你可以改变 $x,y,z$ 值的顺序来得到多个解

举个例子，有一个合法解是 $x=11,y=45,z=14$ ，则你可以变换这个顺序来得到 $6$ 个解。但当$x=19,y=19,z=810$ ,有两个数相等，那此时只能靠换顺序得到 $3$ 个解了。而 $x=24,y=24,z=24$ 三个数相同的情况根本无法换顺序，只有一个解。

所以我们得到统计答案的方法：

当枚举出的 $xyz$ 都不相等时，$res+6$

如果其中两个数相等，则 $res+3$

三个数都相等 $res$ 就只能 $+1$ 了

一些具体细节看代码吧

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	ll n,m,i,j;
	scanf("%lld",&n);
	if(n%3!=0)//因为要求的是 3xyz=n ，所以要求n必须能被3整除，如果不满足就只能输出0了
	{
		printf("0");
		return 0;
	}
	n/=3;//
	ll lim3=(ll)(pow(n*1.0,1.0/3)+0.5),res=0;
	//因为x*y*z是一个三次单项式，所以每个数不能超过n的三次方根
	for(i=1;i<=lim3;i++)
	{
		if(n%i!=0) continue;
		ll y2=n/i;
		ll lim2=(ll)(sqrt(y2)+0.5);//y*z是一个二次单项式，所以对剩下的数取平方根
		for(j=lim2;j>=i;j--)//j实际上枚举的是y
		{
			if(y2%j!=0) continue;//不能整除就跳过
			ll z=y2/j;//z的值就能直接计算出来了
			if(i+j<=z) break;
			if((i+z-j)&1) continue;
			ll b=(i+z-j)/2,a=i-b,c=z-b;
			if(a<=0 || c<=0) continue;//不允许有非正数
			if(a==b)
			{
				if(b==c) res++;//abc都相等
				else res+=3;//ab相等，但不和c相等
			}
			else
			{
				if(b==c || a==c) res+=3;//ab中有一个数和c相等
				else res+=6;//abc全不相等
			}
		}
	}
	printf("%lld",res);
	return 0;
}
```

---

## 作者：Argon_Cube (赞：0)

一般来说，像这样多项式方程对解计数一般都是考虑因式分解然后就可以枚举因数。

随便找个因式分解器得到

$$(a+b+c)^3-a^3-b^3-c^3=3(a+b)(b+c)(c+a)$$

然后令 $x=a+b,y=b+c,z=c+a$，可以发现 $x,y,z$ 均为 $\frac n3$ 的因数且每组 $(x,y,z)$ 最多对应一个 $(a,b,c)$，同时

$$
\begin{cases}
2a=x+z-y\\
2b=x+y-z\\
2c=y+z-x\\
\end{cases}
$$

可以发现上面三个式子奇偶性都跟 $x+y+z$ 相同，也就是只要 $x+y+z$ 是偶数，并且长为 $x,y,z$ 的线段能组成三角形就是一组解。

看起来很难对这两个条件快速计数对吧，但是 $d_{\max}(10^{14})=17280$，所以我们可以直接暴力枚举 $x,y$ 然后就是 $\mathrm O(\sqrt n+d^2(n))$。

注意要枚举无序三元组这样常数会除以 $6$ 不然过不去，并且小心可能的乘法溢出。

Tip：不想用一堆`if`判断枚举到的无序三元组会造成多少贡献？你可以简短的写成 `ans+=6/(1+(x==y)+(y==z)+(z==x))`。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <array>

using namespace std;

vector<long long> divis;

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	long long n;
	cin>>n;
	if(n%3)
		return cout<<0,0;
	n/=3;
	for(long long i=1;i*i<=n;i++)
		if(!(n%i))
		{
			if(i*i!=n)
				divis.push_back(i);
			divis.push_back(n/i);
		}
	sort(divis.begin(),divis.end());
	int answer=0;
	for(long long i:divis)
		for(int j=0;j<divis.size()&&divis[j]<=i&&n/divis[j]/i;j++)
		{
			long long y=divis[j],z=n/i/divis[j];
			if(z<i)
				break;
			if(!(n%(y*i))&&!(i+y+z&1)&&max(i,max(y,z))*2<i+y+z)
				answer+=6/((i==y)+(y==z)+(i==z)+1);
		}
	cout<<answer;
	return 0;
}

```

---

