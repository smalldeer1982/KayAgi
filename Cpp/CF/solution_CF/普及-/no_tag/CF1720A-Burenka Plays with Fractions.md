# Burenka Plays with Fractions

## 题目描述

给出两个分数 $ \dfrac{a}{b}$ 和 $\dfrac{c}{d}$ ，你每次操作能够选择其中一个分数的分子或分母，将其乘上任意一个整数（当然不能对分母乘 $0$）。要求求出能够使两个分数相等的最小操作次数。

## 样例 #1

### 输入

```
8
2 1 1 1
6 3 2 1
1 2 2 3
0 1 0 100
0 1 228 179
100 3 25 6
999999999 300000000 666666666 100000000
33 15 0 84```

### 输出

```
1
0
2
0
1
1
1
1```

# 题解

## 作者：liangbowen (赞：12)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1720A)

[更好的阅读体验？](https://liangbowen.blog.luogu.org/solution-cf1720a)

和官方题解稍有不一样。貌似代码更好理解？

## 思路

我们假设 $a$ 乘上 $x$，$b$ 乘上 $y$，就能相等，即 $\dfrac{ax}{by} = \dfrac{c}{d}$。

化简：$axd = byc$。也就是 $x \cdot(ad) = y \cdot (bc)$

也就是 $\dfrac{x}{y} = \dfrac{bc}{ad}$。这个就是比值。

假设 $k = \gcd(bc, ad)$，我们可以得到 $x : y = \dfrac{bc}{k} : \dfrac{ad}{k}$。

不过这样不严谨，因为 $k = 0$ 时是不成立的。我们特判一下 $k = 0$，结果显然为 $0$。

$k \ne 0$ 的情况下，由于 $k$ 是最大公因数，故 $x$ 与 $y$ 可以直接取 $\dfrac{bc}{k}$ 和 $\dfrac{ad}{k}$。

由于 $x = 1$ 相当于分子没有操作，因此不记入操作次数内。$y = 1$ 同理。

进一步地，$ans = [x \ne 1] + [y \ne 1]$。

至此本题就做完了。时间复杂度为 $\gcd$ 的复杂度。

## 完整代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int read()
{
	char op = getchar(); int x = 0, f = 1;
	while (op < 48 || op > 57) {if (op == '-') f = -1; op = getchar();}
	while (48 <= op && op <= 57) x = (x << 1) + (x << 3) + (op ^ 48), op = getchar();
	return x * f;
}
void write(int x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + 48);
}
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x%y);}
void solve()
{
	int a = read(), b = read(), c = read(), d = read();
	LL t1 = 1ll * a * d, t2 = 1ll * b * c, g = gcd(t1, t2); //注意 LL
	if (g == 0) {putchar('0'), endl; return;}  //特判
	t1 /= g, t2 /= g; //如上分析的化简步骤
	write((t1 != 0) + (t2 != 0)), putchar('\n');
}
int main()
{
	int T = read();
	while (T--) solve();
	return 0;
}
```

希望能帮助到大家！

---

## 作者：FFTotoro (赞：7)

题目的目标是让两个分数满足以下条件：

$$\frac{a}{b}=\frac{c}{d}$$

把上面的式子变形一下，得：

$$ad=bc$$

所以，如果开始时给定的 $a,b,c,d$ 都满足 $ad=bc$，那么说明不需要操作；

那如果不满足呢？

为方便处理，不妨设 $ad<bc$。很显然，如果 $bc$ 是 $ad$ 的倍数，可以通过将 $a$ 或 $d$ 乘以 $\frac{bc}{ad}$，一次操作即可满足。否则铁定无法一次完成，需要两次。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long // 记得开 long long，不然你会连样例都过不去
using namespace std;
main(){
    ios::sync_with_stdio(false);
    int t; cin>>t;
    while(t--){
        int a,b,c,d; cin>>a>>b>>c>>d;
        a*=d; b*=c;
        if(a==b)cout<<"0\n";
        else if(b&&a%b==0||a&&b%a==0)cout<<"1\n"; // 如果一个是另一个的倍数
        // 注意，要特判除数是 0！！！
        else cout<<"2\n";
    }
    return 0;
}
```

---

## 作者：TheCliffSwallow (赞：3)

### 思路
因为我们可以把两个分子都乘上 $0$，所以可以判断答案肯定不超过 $2$。至于答案是 $0$ 的情况也很好判断，直接相除判断是否相等。因为是只需要将两个分数变成相等的，所以剩下的 $1$ 的情况我们可以通分，如果这个数的分子是另一个数的分子的整数倍，那么一步就可以到位，如果不是，就是 $2$ 步。
### AC Code
```cpp
#include<iostream>
#include<cmath>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<cstring>
#include<string>
#include<stack>
#include<queue> 
#include<deque>
#include<vector> 
#define ll long long
using namespace std;
ll t,a,b,c,d;
ll gcd(ll x,ll y){
	ll q=x,p=y;
	if(q<p)	swap(q,p);
	if(q%p==0)	return p;
	else	return gcd(p,q%p);
}
ll lcm(ll x,ll y){
	return x*y/gcd(x,y);
} 
int main(){
	//ios::sync_with_stdio(false);
	//freopen("test.in","r",stdin);
	//freopen("test.out","w",stdout);
	cin>>t;
	while(t--){
		cin>>a>>b>>c>>d;
		if(a==0&&c!=0||a!=0&&c==0){//有一项分子为0可以先直接输出了
			puts("1");
			continue;
		}
		if(a*1.0/b==c*1.0/d){//相等
			puts("0");
			continue;
		}
		if(a*1.0/b<c*1.0/d)	swap(a,c),swap(b,d);
		a*=lcm(b,d)/b;
		c*=lcm(b,d)/d;//通分
		if(a%c==0){//判断整除
			puts("1");
		}else puts("2");
	}
	return 0;
}
```


---

## 作者：__vector__ (赞：1)

## 题外话
感觉这道题有点降智（应该只是对我来说），就写一篇题解记录一下。  
## 做法  
我们可以这样理解：分母乘上一个数 $x$ ，就代表这个分数除以 $x$；分子乘上一个数 $x$，就代表这个分数乘 $x$。  

我们先假设：  
$\frac{a \cdot x}{b \cdot y} = \frac{c}{d}$  
转化为：  
$\frac{a}{b} \cdot \frac{x}{y} = \frac{c}{d}$  
然后计算得出：  
$\frac{x}{y} = \frac{c}{d} \cdot \frac{b}{a}$  
这样我们就知道了，$\frac{a}{b}$ 分子和分母各乘上多少，才能与 $\frac{c}{d}$ 相等。  

如果 $x = 1$，那么分子不需要作乘法，否则分子需要进行一次乘法。  
同理，如果 $y=1$，那么分母不需要作乘法，否则分母需要进行一次乘法。  

这样就结束了吗？没有。  

分子可能为 $0$。  

如果两个分数的分子中有一个为 $0$，那么只需要将另一个分数的分子乘上 $0$，就行了。  

如果两个分数的分子都为 $0$，那么不需要处理。  
## Code  
```cpp  
#include <bits/stdc++.h>
using namespace std;
namespace Main
{
	typedef long long ll;
	int t;
	ll gcd(ll a,ll b)
	{
		return !b?a:gcd(b,a%b);
	}
	ll lcm(ll a,ll b)
	{
		return a/gcd(a,b)*b;
	}
	void main()
	{
		scanf("%d",&t);
		while(t--)
		{
			ll a,b,c,d;
			scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
			if(a==0&&c!=0)
			{
				printf("1\n");
				continue;
			}
			else if(a!=0&&c==0)
			{
				printf("1\n");
				continue;
			}
			if(a==0&&c==0)
			{
				printf("0\n");
				continue;
			}
			a*=d;
			b*=c;
			ll _gcd=gcd(a,b);
			a/=_gcd;
			b/=_gcd;
			int ans=0;
			if(b>1)ans++;
			if(a>1)ans++;
			printf("%d\n",ans);
		}
	}
}
int main()
{
	Main::main();
	return 0;
}
```

---

## 作者：Aurora_Borealis_ (赞：1)

首先考虑进行一个变型：

如果 

$$\dfrac{a}{b}= \dfrac{c}{d}$$

则一定有

$$\dfrac{a}{b} \div \dfrac{c}{d} =1$$

即


$$\dfrac{ac}{bd}= 1$$

也就是说，只要使 $ad=bc$，两个分数就相等。 

接下来的结论就很好想了：

如果 $ad=bc$ 答案为 $0$。

如果 $\gcd(ad,bc)=\min(ad,bc)$（倍数情况）,答案为 $1$。

剩下的情况答案就为 $2$。

需要注意的是，$a,c$ 中只有一个为 $0$ 时，答案为 $1$。 

---

## 作者：Dream_weavers (赞：1)

## 题意

给出两个分数 $\dfrac{a}{b},\dfrac{c}{d}$。每次操作可以选择一个分数的分子或分母乘以任何数（分母不能乘以 $0$）。求使两个分数相等最少要操作几次。

## 思路

很明显不管是什么分数，答案都是 $0$ 或 $1$ 或 $2$。

把分数化成最简，如果分数相等，答案为 $0$。

如果两个分数之商是整数，答案为 $1$。分数之商指的是大除以小，可以通分比较。换句话说，如果通分后 $a$ 是 $c$ 的倍数或 $c$ 是 $a$ 的倍数，答案为 $1$。

否则答案为 $2$。

特别地，如果 $a$ 或 $c$ 中有 $0$，那要最先考虑，防止后面求 $\gcd$ 时 RE。


------------

代码又臭又长，就不放了。/kk

放个[记录](https://www.luogu.com.cn/record/84352165)就行了。


---

## 作者：RoyWu1207 (赞：1)

## 题目大意

有两个分数 $\dfrac{a}{b}$ 和 $\dfrac{c}{d}$，每次选择 $a,b,c,d$ 中的任何一个数，将其乘上任何一个整数，求使两分数相等的操作的最小值。

## 分析

看着这两个分数，我忽然想起了什么。

小学知识：若 $\dfrac{a}{b} = \dfrac{c}{d}$，那么 $ad = bc$。

于是，目的就变成了使 $ad = bc$ 这个式子相等。

分类讨论。

- 第一种情况：$ad = bc$，最小操作数为 $0$。

- 第二种情况：$ad$ 是 $bc$ 的倍数或 $bc$ 是 $ad$ 的倍数，将小的一边乘上多少倍即可，最小操作数为 $1$。

- 第三种情况：啥都不是，那就只能将 $ad$ 和 $bc$ 分别乘到它们的最小公倍数，最小操作数为 $2$。

**PS：记得特判 $a = 0$ 或 $c = 0$。**

## **AC Code：**

```cpp
#include <iostream>

using namespace std;

int main() {
	int t; cin >> t;
	while (t--) {
		unsigned long long a, b, c, d;
		cin >> a >> b >> c >> d;
		if (a * d == b * c)
			cout << 0 << endl;
		else if (a == 0 || c == 0)
			cout << 1 << endl;
		else if (a * d % (b * c) == 0 || b * c % (a * d) == 0)
			cout << 1 << endl;
		else
			cout << 2 << endl;
	} return 0;
} 
```

谢谢大家！如果有什么写的不好的欢迎指出！

---

## 作者：hayzxjr (赞：0)

题目来源：[Codeforces Round #815 (Div. 2)](https://codeforces.com/contest/1720/problem/A)

洛谷题面：[link](https://www.luogu.com.cn/problem/CF1720A)

### 题意简述

给出两个分数 $\dfrac{a}{b}$ 和 $\dfrac{c}{d}$，每次操作只能将其中一个分数的分子和分母乘上一个数，并要求分数始终有意义。求出能够使两分数相等的最小操作数最小操作数。

### 题目分析

1. 既然操作对象是随意的，那么我们可以根据**等式的性质**直接看成只对其中一个数进行操作。

2. 其中将分子乘上 $x$ 可看成将分数乘上 $\dfrac{x}{1}$，将分母乘上 $y$ 可看成将分数乘上 $\dfrac{1}{y}$。

3. 那么就很明确了，题目即可转化为求 $k$ 满足 $k\dfrac{a}{b}=\dfrac{c}{d}$。

注意实现细节：

1. 注意数据范围，记得开 `long long`。

2. 求出 $k$ 时不能直接相除，避免精度问题，可转化成 $ka \times d = c\times b$。

下面考虑操作数求法：

> 当两个分数有一个数为 $0$ 时，可直接将另一个数变成 $0$。

> 当 $k$ 的分子或分母为 $0$ 时，只需要一次操作。

> 否则，$k$ 为形式为 $\dfrac{x}{y}$，$x$ 和 $y$ 不等于 $1$ 和 $0$ 时，则可以进行两次操作，分别乘上 $\dfrac{x}{1}$ 和 $\dfrac{1}{y}$ 即可

题外话：最好的解决方法是将两个分数变成 $0$。

### 代码实现

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t, a, b, c, d;
int main(){
	scanf("%lld", &t);
	while(t--){
		scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
		ll x = a * d, y = b * c; 
		if(x == y) printf("0\n");
		else if(x == 0 || y == 0) printf("1\n");
		else if(x % y == 0 || y % x == 0) printf("1\n");
		else printf("2\n");
	}
	return 0;
}
```

---

## 作者：紊莫 (赞：0)

赛时一发 AC，hack 了不少没开 ``long long`` 的人。

## 分析

我们发现对于任意两个分数，他们的操作数至多为 $2$，即将分子同时乘 $0$。  

我们希望知道的是什么时候操作数为 $0$，什么时候为 $1$，这样就能推出剩下的情况都为 $2$。  

首先，显然的，当两个分数完全相等时操作数为 $0$。特别的，当分子都为 $0$ 时，两者也相等。  
而为了判断两者是否相等，需要先约分一下。  
但为了避免和 $0$ 取最大公约数时的情况，对于分子都为 $0$ 的情况，需要在输入后首先判断。  

其次，对于操作数为 $1$ 的情况，我们发现当两个分数中有且仅有一者为 $0$ 时，答案为 $1$。  
然后你可能会想到一个纯粹的做法，去判断分子分母直接能否整除，可惜这样的做法时错误的。  
例如这组数据：  
```
100 3 25 6
```  
明显是将 $25\times8$，答案为 $1$，但是上述的错误做法却得到了 $2$ 的错误答案。  

为此，我们的方法是判断交叉相乘的两个积能否整除。  
证明显然，此处略过。

至此问题已经解决，其余情况答案均为 $2$。  

## 代码

仅放出主函数部分。  

```cpp
signed main()
{
    int T=read();
	while(T--)
	{
		int a=read(),b=read(),c=read(),d=read(),ans=0;
		if(a==0&&c==0){
			puts("0");continue;
		}
		//约分操作
		int g=__gcd(a,b);
		a/=g,b/=g;
		g=__gcd(c,d);
		c/=g,d/=g;
		if((a==c&&b==d)){
			puts("0");continue;
		}if(a==0||c==0){
			puts("1");continue;
		}
		int x=a*d,y=b*c;
		if(x<y)swap(x,y);
		if(x%y==0){
			puts("1");continue;
		}
		puts("2");
	}
    return 0;
}
```




---

## 作者：ztlh (赞：0)

# Solution

显然，答案不会超过 $2$（可以给分数乘上万能的 $0$，题面提示了我这一点）。先将两个分数通分。

- 若 $a = 0$ 且 $c = 0$，输出 $0$ 即可（其实可以并入第三行）。

- 否则，若 $a = 0$ 或 $c = 0$，输出 $1$。

- 否则，若 $a = c$，输出 $0$。

- 否则，若 $a$ 是 $c$ 的**约数**或**倍数**，输出 $1$。

- 否则输出 $2$。

代码：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
ll a,b,c,d;
ll g;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
		if(!a&&!c){
			printf("0\n");
			continue;
		}
		if(!a||!c){
			printf("1\n");
			continue;
		}
		g=b/__gcd(b,d)*d;
		a*=g/b; b=g;
		c*=g/d; d=g;
		if(a==c) printf("0\n");
		else if(a/c*c==a||c/a*a==c) printf("1\n");
		else printf("2\n");
	}
	return 0;
}
```

---

## 作者：zeekliu (赞：0)

通过观察，我们发现答案只会在 $\texttt{0-2} $ 之间。

$ \frac{a}{b} $ 和 $ \frac{c}{d} $ 至多仅会改变一次分子或分母。

因为两个分数要相等的前提是十字交叉（暂且这么称呼吧）的结果相等，形式化的说，就是题目里 $ a \times d = b \times c $ 。

我们不妨设 $ p = a \times d $，$ q = b \times c $。

下面来分析情况：

**1. 若 $ p=0 $ 或 $ q=0 $ ：**

如果，$ p=q=0 $，那么就不需要操作了，输出 $ 0 $ 。

如果，$ p=0\ $ 且 $\ q \neq 0\ $ 或 $\ p \neq 0\ $ 且 $\ q=0 $，那就将那个不等于 $ 0 $ 的分数的分子乘 $ 0 $ 即可，输出 $ 1 $ 。

**2. 若 $ p \neq 0\ $ 且 $\ q \neq 0 $ ：**

如果，$ p=q $，那么就不需要改变其他了，输出 $ 0 $ 。

如果，$ q\ |\ p\ $ 或 $ p\ |\ q\ $ ，则将小的数乘上相应的数即可，输出 $ 1 $ 。

否则，两个分数都需要变化，输出 $ 2 $ 。

所以，下面看代码：

```cpp
//CF1720A 22-08-19
#include <bits/stdc++.h>
using namespace std;

int main() 
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int _; cin>>_;
	while (_--)
	{
		long long a,b,c,d; cin>>a>>b>>c>>d;
		long long p=a*d,q=b*c;
		if (p==0 && q==0) {cout<<"0"<<endl;continue;}
		else if ((p==0 && q!=0) || (p!=0 && q==0)) {cout<<"1"<<endl;continue;}
		if (p==q) cout<<"0"<<endl;
		else if ((p>q && p%q==0) || (q>p && q%p==0)) cout<<"1"<<endl;
		else cout<<"2"<<endl;
	}
	return 0;
}
```

### 警钟长鸣

开 ```long long```，不然见祖宗（~~祖坟~~）！

很可惜，由于某谷 RMJ 出现了不可避免的问题，所以提交到了 CF 上，CF 上 ```Accepted```。

---

## 作者：cachejtt (赞：0)

## 题意
给你两个分数 $\dfrac{a}{b}$ 和 $\dfrac{c}{d}$，每次操作，你可以选择 $a,b,c,d$ 中的一个，将其乘上任意数。问你最少经过多少次操作，可以使两个分数相等。

## 思路
首先，操作次数肯定不超过 $2$ 次。因为我们可以 $a\gets a\times 0,c\gets c\times 0$。即将分子都变成 $0$。

考虑若当前分数相等，则答案为 $0$。那么，怎么判断两个分数是否相等的？考虑若 $\dfrac{a}{b}=\dfrac{c}{d}$ 则 $a\times d=b\times c$ 即可。

然后，若其中一个分数为 $0$，则答案为 $1$。因为我们可以将非 $0$ 的那个分数的分子乘上 $0$。这里无需考虑两个分子都为 $0$ 的状况，因为若两个分子都为 $0$，则会被第一步判定为两个分数相等。

其次，若一个分数是另一个的倍数，则答案为 $1$。不妨设 $\dfrac{a}{b}=k\times \dfrac{c}{d}$，则 $a\times d=k\times b\times c$。即 $(a\times d)\bmod (b\times c)=0$，另一边同理。此时只需对小的那个分数分子乘上 $k$ 即可。

否则，答案为 $2$。因为不可能在一次操作内使得两个分数相等。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long
using namespace std;
int t=1,n1,m1,n2,m2,ans;
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n1>>m1>>n2>>m2;
    ans=0;
    if(n1*m2==m1*n2){
      cout<<0<<endl;
      continue;
    }
    if(n1==0 || n2==0){
      cout<<1<<endl;
      continue;
    }
    if((n1*m2)%(n2*m1)==0 || (n2*m1)%(n1*m2)==0){
      cout<<1<<endl;
      continue;
    }
    cout<<2<<endl;
    continue;
  }
  return 0;
}
```

---

## 作者：sandwave114514 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1720A)

题目大意

给你四个数 $a,b,c,d$ ，让你通过乘一个数，让 $a \div b$   和 $c \div d$ 相等。

解题思路
 
我们可以知道，如果它们乘起来的值本来就相等，那我们就输出 `0`   ,如果它们乘起来有一个的值是 `0` ，我们就输出   `1` ，如果它们乘起来有一个是另一个的倍数，也输出  `1` ，如果都不满足，就输出 `2` 。

代码如下

```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
long long read(){
	long long x=0,sgn=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')sgn=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch&15);ch=getchar();}
	return x*sgn;
}//快读 
void write(long long n,bool p){
	if(n<0){putchar('-');n=-n;}
	if(n==0){if(p)putchar('0');return;}
	write(n/10,0);putchar(n%10+'0');
}//快写 
long long t,a,b,c,d,aa,bb;
int main(){
    t=read();
    while(t--){//多组数据 
    	a=read();b=read();c=read();d=read();
    	aa=a*d;bb=b*c;
    	if(aa==bb)cout<<"0"<<endl;
    	else if(aa==0||bb==0||aa%bb==0||bb%aa==0)cout<<"1"<<endl;
    	else cout<<"2"<<endl;
	}
	return 0;//完结撒花 
}
```


---

## 作者：tZEROちゃん (赞：0)

可以发现答案必定小于 $2$。

我们设原来两个分数是 $\dfrac{a}{b}$ 和 $\dfrac{c}{d}$，那么将第一个分数乘上 $bc$ 变成 $\dfrac{abc}{b} =ac$，第二个分数乘上 $ad$ 变成 $\dfrac{acd}{d} = ac$。

那么考虑什么时候是 $0$ 次操作，显然是不用改，也就是说本来就相等。

然后我们注意到当一个数是另一个数的倍数的时候，就可以 $1$ 次操作内完成。

其他情况就是 $2$ 次。

[参考代码](https://www.luogu.com.cn/paste/ksgdqeku)。

---

## 作者：Galois_Field_1048576 (赞：0)

分类讨论。  
当 $\dfrac ab=\dfrac cd$ 时：操作次数为 $0$；  

当 $\min(a,c)=0$ 时：只要把 $\max(a,c) \gets 0\max(a,c)$ 就可以了，操作次数为 $1$；

当 $\dfrac ab \div \dfrac cd \in \mathbb N$ 时，可以直接 $c \gets c \times \dfrac ab \div \dfrac cd$，操作次数为 $1$；  

当 $\dfrac cd \div \dfrac ab \in \mathbb N$ 时，可以直接 $a \gets a \times \dfrac cd \div \dfrac ab$，操作次数为 $1$；  

否则，将其化为最简分数，乘到第一个数的分子分母上，操作次数为 $2$。


代码（语言：Python；去掉了导入的函数和 `read()` 函数）
```python
T, = read()
for _ in range(T):
    a, b, c, d = read()
    if 0 in [a, b, c, d]:
        print(2-[a, c].count(0))
        continue
    A = a*d
    B = b*c
    G = gcd(A, B)
    A //= G
    B //= G
#    print(A, B)
    print(2-[A, B].count(1))
```


---

## 作者：cst_123 (赞：0)

### - [传送门](https://www.luogu.com.cn/problem/CF1720A)

------------

### 题意

$T$ 组数据，给你 $a$，$b$，$c$，$d$ 四个数，你一次可以取任意一个的自然数与四个数中的一个数相乘，最终使 $\frac{a}{b}$ 和 $\frac{c}{d}$ 相等。问你最少要多少次操作。

### 思路

可以转换成 $a \times d=b \times c$，我们分步讨论。

- 若是四个数相等，那就是 $0$ 步了。

- 若是 $a$ 和 $c$ 中有一个是 $0$，那么 $a \times d$ 和 $b \times c$ 中一个为 $0$。这时可以将另一个中的一个数乘 $0$，这样也就相等了，要 $1$ 步。

- 之后就再判断 $a \times d$ 或 $b \times c$ 是否是另外的数的倍数，若有其中有一个符合，就只需 $1$ 步就行了。

- 剩下的就只能是 $2$ 步了。

### 代码

```cpp
now1=max(a*d,c*b);
now2=min(a*d,b*c);
if((a*d)==(b*c)){
	printf("0\n");continue;
}
if(a==0||c==0){
	printf("1\n");continue;
}
if(now1%now2==0){
	printf("1\n");continue;
}
else{
	printf("2\n");continue;
} 
```

---

