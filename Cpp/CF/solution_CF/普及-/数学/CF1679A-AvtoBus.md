# AvtoBus

## 题目描述

春天来了，车队的巴士需要更换轮胎。

轮胎有 $n$ 个，巴士有两种，第一种有 $4$ 个轮子，第二种有 $6$ 个。

求车队最少和最多有几辆巴士。

## 样例 #1

### 输入

```
4
4
7
24
998244353998244352```

### 输出

```
1 1
-1
4 6
166374058999707392 249561088499561088```

# 题解

## 作者：Jerrlee✅ (赞：3)

## 题意
你有一些公交车，可以是 $4$ 轮的，也可以是 $6$ 轮的。现在给你轮子总数，求车辆数量可能的最小值和最大值。
## 思路
首先，如果车轮数为奇数，肯定拼会多出至少一个轮子，否则一定可以拼出来。

但当 $n$ 小于 $4$ 时，肯定一辆车也拼不出来。

然后其余情况分类讨论即可。

1. 求最小值，要使车尽量为 $6$ 轮，否则再拆开六轮的车拼出四轮（$n$ 除以 $6$ 余 $2$ 时，拆开一辆六轮车，组成两个 $4$ 轮的，余 $4$ 时可以直接拼出一个 $4$ 轮车）；

2. 求最大值，要使车尽量为 $4$ 轮，否则再拆开四轮的车拼出六轮（$n$ 除以 $4$ 余 $2$ 时，拆开一辆四轮车，组成一辆 $6$ 轮车）。

记得开 `long long`。
## 代码
```cpp
#include<iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        long long n;
        cin>>n;
        if(n==4){cout<<"1 1\n";continue;}
        if(n==6){cout<<"1 1\n";continue;}
        if(n<4||n%2!=0){cout<<"-1\n";continue;}
        if(n%6==0) cout<<n/6<<" ";
        else if(n%6==2) cout<<(n-2)/6+1<<" ";
        else cout<<(n-4)/6+1<<" ";
        if(n%4==0) cout<<n/4<<endl;
        else cout<<(n-2)/4<<endl;
    }
}
```
[AC 记录（洛谷）](https://www.luogu.com.cn/record/75776852)

[AC 记录（CF）](https://codeforces.com/contest/1679/submission/157252959)

---

## 作者：Hooch (赞：1)

### 题目大意

你正在经营一个巴士旅馆，现在来了一个大型巴士旅团，其中的巴士分为两轴和三轴。（也就是 $4$ 个轮子和  $6$ 个轮子）

你要维修这些轮子，你知道轮子数量，现在要求出巴士数量的最小值和最大值。

### 思路

首先我们可以发现若轮子数量（下面记为 $n$）是奇数，那么一定无解，否则有解。

先来考虑最大值，不难发现，最大值其实就是全部是 $4$ 个轮子的车，要分类讨论一下：

1.$n\bmod 4=0$，答案就是 $\frac{n}{4}$。

2.$n\bmod 4=2$，那么就将一辆两轴车变为三轴车就行了，答案仍为 $\frac{n}{4}$。

接着是最小值，最小值直接全是三轴车：

1.$n\bmod 6=0$，答案为 $\frac{n}{6}$

2.$n\bmod 6=2$，将一辆三轴车换成两轴车，并且再来一辆两轴车就行了，答案为 $\frac{n}{6}+1$

3.$n\bmod 6=4$，剩下的 $4$ 个轮胎就来一辆两轴车就行了。

### 代码

```cpp
long long a, t;
signed main(void) {
	ios::sync_with_stdio(false);
	cin >> t; while (t--) {
		cin >> a;
		if (a & 1 || a < 4) {cout << "-1" << endl; continue;}
		long long mi, ma; 
		ma = a / 4;
		mi = a / 6;
		if (a % 6) ++mi;
		cout << mi << ' ' << ma << endl;
	}
}
```



---

## 作者：_Kouki_ (赞：0)

### 题目大意：

有两种公共汽车**四轮和六轮**。   
给你轮子总数，求**最多最少格式多少。**    

### 题目思路：

通过分析明显若 $ n\le3 $ 是一个也装不了。   

假设有 $ x $ 辆四轮， $ y $ 辆六轮。

$ 2 | (4x + 6y)$

所以奇数不行。   
**特别的**，对于**求极值**我们可以从后向前递归，找到答案直接输出。   

### 题目代码：
不懂得注释有解。  

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;

typedef long long ll;

inline ll read(){//快读
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int t;
ll n;
int main()
{
    scanf("%d",&t);//输入
    while(t--){//循环
        n=read();//输入
        if(n%2==1||n<4){//n<4 一辆也不行
        	printf("-1\n");
		} 
        /*
		* 因为4x+6y 的值一定被2整除
		*/
        else{
            ll x=n/6,y=n/4;/*不同的公共汽车*/
            while(x>=0){if((n-x*6)%4==0){printf("%lld ",x+(n-x*6)/4);break;}--x;}
            while(y>=0){if((n-y*4)%6==0){printf("%lld\n",y+(n-y*4)/6);break;}--y;}
			        /*
						从后向前循环，可一步求出最值
					*/
        }
        
    }
    return 0;//完结撒花*★,°*:.☆(￣▽￣)/$:*.°★* 。
}
```

---

## 作者：Jason12 (赞：0)

## 题目：
[传送门](https://www.luogu.com.cn/problem/CF1679A)
## 思路：
  首先排除 $n$ 为奇数，的情况，由于车轮数都为偶数，所以若 $n \bmod 2 = 1$，则输出 $-1$，$n<4$ 的情况也需输出 $-1$，因为一辆车的最少轮子数为 $4$，否则求出车辆数的最大值和最小值。
### 最小值：
  由于 $6 > 4$，所以六轮车越多，车的总数越少，若 $n \bmod 6 = 0$，则车的总数为 $n \div 6$。否则分类讨论：若 $n \bmod 6 = 2$，则可以把一辆六轮车和多出来的两个轮胎合并为两辆四轮车，则车辆数为 $n \div 6 + 1$；若 $n \bmod 6 = 4$，则可以再增加一辆四轮车，车辆总数也为 $n \div 6 + 1$。所以，若 $n \bmod 6 = 0$，输出 $n \div 6$，否则输出 $n \div 6 +1$。
### 最大值：
  由于 $4 < 6$，所以四轮车越多，车的总数越多。还是分类讨论，若 $n \bmod 4 = 0$，则车的总数为 $n \div 4$；若 $n \bmod 4 = 2$，则可以把一辆四轮车和多出来的两个轮胎合并为一辆六轮车，则车的总数仍为 $n \div 4$。所以不管 $n \bmod 4$ 等于 $0$ 还是 $2$，都输出 $n \div 4$。
## 代码：
```cpp
#include <bits/stdc++.h>
  using namespace std;
long long m,n,x,y;//注意开 long long。
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>m;
	while (m--)
	{
		cin>>n;
		if (n&1 || n<4)//若 n 为奇数或 n<4。
		{
			cout<<-1<<endl;
			continue;
		}
		x=n/4;//最大值。
		if (n%6==0) y=n/6;//最小值。
		else y=n/6+1;
		cout<<y<<" "<<x<<endl;//注意先输出最小值再输出最大值。
	}
	return 0;
}


```


---

## 作者：嘿嘿嘿嘿嘿嘿6 (赞：0)

这题只要计算出 4 个轮胎的最大值和 6 个轮胎的最大值，再枚举就行了，还要特判一下无解，具体的看我代码。

```cpp
#include<cstdio>
int main(){
	int t;
	long long n,a,b;
	scanf("%d",&t);
	while(t--){
		scanf("%lld",&n);
		if(n%2==1) printf("-1\n");//特判无解 
		else{
			if(n<4) printf("-1\n");//特判无解 
			else{
				a=n/6;//6个轮胎的车最多多少辆，求最小值 
				b=n/4;//4个轮胎的车最多多少辆，求最大值 
				for(;a>=0;--a){
					if((n-a*6)%4==0){
						printf("%lld ",a+(n-a*6)/4);//倒着枚举，第一个就是答案 
						break;
					}
				}
				for(;b>=0;--b){
					if((n-b*4)%6==0){
						printf("%lld\n",b+(n-b*4)/6);//倒着枚举，第一个就是答案 
						break;
					}
				}
			}
		}
	}
	return 0;
}
```


---

## 作者：linyuhuai (赞：0)

[前往 blog 获得更好的阅读体验](https://by505244.github.io/oi_blogs/2022/05/15/CF1679A%E9%A2%98%E8%A7%A3/)

### 题意简述

给定一个数 $n$ ，求 $4a+6b=n$ 时 $a+b$ 的最小值和最大值（$a,b$ 均为整数），无解时输出 `-1`，共有 $t$ 组数据。
### 解题思路

$4a+6b=n$ 可化简为 $2a+3b=\dfrac{n}{2}$，所以 $n$ 一定是 $2$ 的倍数且 $n\ge4$。

不难发现 $a+b$ 最小时 $a$ 一定最大，$b$ 一定最小，当 $a+b$ 最大时反之。

考虑 $n$ 有如下几种情况：

| $n$ 的情况 | 应对方法 |
| :-----------: | :-----------: |
| $n$ 为 $4$ 的倍数 | 最大值 $\dfrac{n}{4}$ |
| $n$ 为 $6$ 的倍数 | 最小值取 $\dfrac{n}{6}$ |
| $n$ 为 $4x+2$（$x$ 为整数） | 使 $b=1$，将 $n$ 减去 $1\times6$ 得 $(4x+2)-6=4(x-1)$，最大值即为 $\dfrac{n-6}{4}+1=\lfloor\dfrac{n}{4}\rfloor$ |
| $n$ 为 $6x+2$ | 使 $a=2$，减去 $2\times4$ 得 $6x+2-8=6(x-1)$，最小值即为 $\dfrac{n-8}{6}+2=\lfloor\dfrac{n+4}{6}\rfloor$ |  
| $n$ 为 $6x+4$ | 使 $a=1$ ，同上可得最小值为 $\dfrac{n-4}{6}+1$ 在 $n$ 为整数的情况下也可等于 $\lfloor \dfrac{n+4}{6}\rfloor$ |


**不难发现，$n$ 一定满足以上的第 $1,3$ 条之一和第 $2,4,5$ 条之一，其中各对应最大值和最小值，分别是 $\lfloor\dfrac{n}{4}\rfloor$ 和 $\lfloor \dfrac{n+4}{6}\rfloor$。**




```cpp
#include<bits/stdc++.h>

long long max(long long a,long long b){return a>b?a:b;}
long long min(long long a,long long b){return a>b?b:a;}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        long long n;
        scanf("%lld",&n);
        if(n==2||n%2==1){printf("-1\n");continue;}
        printf("%lld %lld\n",(n+4)/6,n/4);
    }
    return 0;
}
```

---

## 作者：小木虫 (赞：0)

### Preface  
一道看似小清新送分题但实际暗藏玄机的奇妙 A 题。
### Problem  
给一个巨大正整数 $n$，问你可以把它拆成若干 4 和 6 的和，最多能拆成多少数字？最少呢？  
### Solution  
4 和 6 有最大公约数 2，先把 2 提出来。于是 $n$ 变成了 $\frac{n}{2}$，拆成 2 和 3。  
这时候我们发现，要是原始的 $n$ 是个奇数或是 2，就没办法拆了，必定无解，于是先特判。  
接下来分类讨论，先讨论尽量小的部分：  
1.现在的 $n$ 要是能被 3 整除，直接先输出 $\frac{n}{3}$。  
2.若 $n$ 除 3 余 1 的话，那么我们将其最后的 3 与 1 拼合变成 4，然后两个 2 就可以拼上去。  
3.要是余 2 的话，直接拼上去一个 2 即可。  

讨论尽量大的部分：  
1.若 $n$ 是偶数，直接输出 $\frac{n}{2}$。  
2.若 $n$ 是奇数，把最后的 2 与 1 拼起来用 3 代替即可。  
code：  
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int T;
ll n;
void init(){
	
}
void solve(){
	cin>>n;
	if(n%2!=0){
		cout<<-1<<endl;
		return;
	}else{
		n/=2;
		if(n==1){
			cout<<-1<<endl;
			return; 
		}
		if(n%3==0){
			cout<<n/3;
		}else{
			if(n%3==2){
				cout<<(n-2)/3+1;
			}
			if(n%3==1){
				cout<<(n-4)/3+2;
			}
		}
		cout<<" ";
		if(n%2==0){
			cout<<n/2;
		}else{
			cout<<(n-3)/2+1;
		}
		cout<<endl;
	}
}
int main(){
	cin>>T;
	while(T--)init(),solve();
	return 0;
}
```


---

## 作者：Morpheuse (赞：0)

可以把轮胎两个看为一组.

轮胎为奇数个显然不行.

- 车辆最多，则尽可能是四轮车.

- 车辆最少，则尽可能是六轮车.

设组数为 $k$.

最多辆数为 $\lfloor\frac{k}{2}\rfloor$.

$k \equiv 1 (mod\ 3)$ 和 $k \equiv 2 (mod\ 3)$ 时

可以分别把一辆和两辆六轮车拆开 与多余的轮胎配对使得轮胎刚好用完.

这种情况下答案均为 $\lfloor\frac{k}{3}\rfloor + 1$.

整除 $3$ 时直接除就好了.

注意特判.

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 200010
#define int long long
typedef pair<int , int> p;
int T,n;
int a[maxn],b[maxn];
priority_queue<p , vector<p> , greater<p> > q;
priority_queue<p> Q;
signed main()
{
	scanf("%lld", &T);
	while(T --)
	{
		scanf("%lld", &n);
		int a1,a2,ans1,ans2;
		if(n & 1 || n <= 3)
		{
			printf("-1\n");
			continue;
		}
		int k = n / 2;
		ans1 = k / 2;
		if(k % 3 == 1 || k % 3 == 2)
			ans2 = k / 3 + 1;
		else
			ans2 = k / 3;
		printf("%lld %lld\n", ans2,ans1);
	}
}
```

---

## 作者：ttq012 (赞：0)

分类讨论。

如果 $n$ 是奇数，那么一定无解。

如果 $n = 2$ 或者 $n = 0$，那么一定无解。

如果 $n = 4$，那么最多和最少都只有一辆车。

否则，如果 $n$ 对 $6$ 取模为 $0$，那么最少的车辆数量就是 $\frac{n}{6}$，否则容易发现只有 $n\bmod 6 = 2$ 和 $n\bmod 6 = 4$ 两种情况。可以发现不管哪种情况，答案都是 $\lfloor\frac{n}{6}\rfloor + 1$。上述的三种情况中车辆数最多都是需要 $\lfloor\frac{n}{4}\rfloor$ 辆车辆的。

```cpp
#include <bits/stdc++.h>

using namespace std;

char s[2323][2323];

void solve() {
    long long n, ans = 0x3f3f3f3f3f3f3f3f;
    cin >> n;
    if (n & 1LL)
        cout << "-1\n";
    else if (n == 2 || n == 0)
        cout << "-1\n";
    else if (n == 4)
        cout << "1 1\n";
    else {
        if (n % 6 == 0)
            cout << n / 6 << ' ';
        else
            cout << (n + 4) / 6 << ' ';
        cout << n / 4 << '\n';
    }
}

signed main() {
    int T;
    cin >> T;
    while (T --)
        solve();
}

```


---

## 作者：windflower (赞：0)

简要题意：
>有四轮车和六轮车，告诉你轮子的总数 `n`，最少可能有几辆车，最多可能有几辆车？

其实就是求满足 $4x+6y=n$ 的满足 $x+y$ 取到最大值和最小值的非负整数解。

一眼拓展欧几里得，一顿操作猛如虎，A 了
```cpp
#include<bits/stdc++.h>
using namespace std;
long long ex_gcd(long long a,long long b,long long &x,long long &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	long long d=ex_gcd(b,a%b,x,y);
	long long t=x;
	x=y;
	y=t-(a/b)*y;
	return d;
}
long long solve(long long a,long long b,long long n) {
	long long x,y;
	long long d=ex_gcd(a,b,x,y);
	if(n%d!=0) return -1;
	x=x*n/d;
	long long t=b/d;
	if(t<0) t=-t;
	return (x%t+t)%t; 
}
long long t,n,ans1,ans2;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		ans1=solve(4,6,n);
		ans2=solve(6,4,n);
		if(ans1<0||ans2<0||n%2||ans1*4>n||ans2*6>n)printf("-1\n");else
		printf("%lld %lld\n",ans1+(n-ans1*4)/6,ans2+(n-ans2*6)/4);
	}
	return 0;
}
```

我还在想怎么第一题就用这么复杂的东西了。  
后来看了眼官方题解，发现自己做繁了。对于奇数的 `n` 肯定不满足要求。考虑 $n\div2$，若 $n\div2$ 是偶数，则全为四轮车时 $x+y$ 取到最小，否则一辆六轮车、其余全四轮车时 $x+y$ 取到最小。同理也可以简易地判断出何时最大。  
这个思路就不附代码了，应该大家随手就能写出来吧。

---

## 作者：Anguei (赞：0)


## 题意

有两种类型的公交车，第一种车需要 4 个轮子，另一种需要 6 个轮子。

现在给你 $n$ 个轮子，要求**恰好**装到 $m$ 辆公交车上。问 $m$ 的最小值和最大值。

## 分析

首先考虑无解情况：
- 如果给定的轮子不足 $4$ 个，则一辆车都装不好，无解。
- 如果给的轮子数量是奇数，则无论如何都不能**恰好地**装上车。

其余情况：方程 $4x + 6y = 2k \ (k \geq 2)$ **一定有正整数解**。其中 $x+y = m$。

要让 $x$ 取最小值，就让尽可能让每辆车消耗 $6$ 个轮子；反之，要取最大值，就尽可能多的让每辆车装 $4$ 个轮子。

## 代码

```cpp
void solution() {
  ll n;
  read(n);
  if (n < 4) return print(-1);
  if (n & 1) return print(-1);
  if (n % 6 == 0 && n % 4 == 0) return print(n / 6, n / 4);
  ll y = n / 4;
  ll x = n / 6 + int(n % 6 != 0);
  return print(x, y);
}
```

---

## 作者：hyc1026 (赞：0)

### 题意：

给你正整数代表轮胎的数量，现在有四轮车和六轮车，问这个数量的轮胎至少可以组成几辆车，最多可以组成几辆车？其中轮胎必须全用完，无法用完输出 $-1$。

### 思路：

显而易见，如果轮胎数量是奇数或者小于四，那么不可能用完。

在车最少的情况下，要六轮车越多越好。不难发现：

- 当轮胎数模 $6$ 余 $0$ 时，有 $\dfrac{n}{6}$ 辆六轮车为最小。

- 当轮胎数模 $6$ 余 $2$ 时，有 $\left[\dfrac{n}{6}\right]-1$ 辆六轮车和 $2$ 辆四轮车为最小。

- 当轮胎数模 $6$ 余 $4$ 时，有 $\left[\dfrac{n}{6}\right]$ 辆六轮车和 $1$ 辆四轮车为最小。

综上，当轮胎数能被 $6$ 整除时，至少有 $\dfrac{n}{6}$ 辆车。否则至少有 $\left[\dfrac{n}{6}\right]+1$ 辆车。

在车最多的情况下，要四轮车越多越好。不难发现：

- 当轮胎数模 $4$ 余 $0$ 时，有 $\dfrac{n}{4}$ 辆四轮车为最大。

- 否则有 $\left[\dfrac{n}{4}\right]-1$ 辆四轮车和 $1$ 辆六轮车。

综上，无论什么情况，最多都只有 $\left[\dfrac{n}{4}\right]$ 辆车。

我们可以写出代码，注意数据范围（不开 long long 见祖宗）：

### AC Code:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int T;
    cin >> T;
    while(T--)
    {
        int n;
        cin >> n;
        if(n % 2 == 1 || n == 2)
        {
            cout << -1 << endl;
            continue;
        }
        if(n % 6 == 0) cout << n / 6 << " ";
        else cout << n / 6 + 1 << " ";
        cout << n / 4 << endl;
    }
    return 0;
}
```

---

## 作者：sandwave114514 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1679A)

题目大意

有两种公交车，一种有 $4$ 个轮子，一种有 $6$ 个轮子。已知轮子的总数 $x$，求公交车数量的最小值和最大值，如果求不出，输出 $-1$ 。

解题思路

显然，如果 $x$ 小于 $4$ 或是奇数，那就输出 $-1$ 。那怎么求最小值呢?
求最小值，我们肯定多选 $6$ 个轮子的，再选 $4$ 个轮子的。最大值就多选
 $4$ 个轮子的，再选 $6$ 个轮子的。

代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
long long read(){
	long long x=0,sgn=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')sgn=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch&15);ch=getchar();}
	return x*sgn;
}//快读
long long t,n;
int main(){
    t=read();
    while(t--){
        n=read();
        if(n<4||n%2==1){//判断n是否大于4和等于偶数，不然就输出-1
            cout<<"-1"<<endl;
            continue;
        }
        if(n%6==0)cout<<n/6<<" ";//利用c++中long long向下取整的特性
        else cout<<n/6+1<<" ";
        cout<<n/4<<endl;
    }
    return 0; 
}
```


---

## 作者：BetaCutS (赞：0)

## 题目描述

有两种巴士，一种有 $4$ 个轮子，一种有 $6$ 个轮子。已知轮子的总数 $x$，求巴士数量的最小值和最大值。

## 算法

首先，如果 $x$ 小于 $4$ 或为奇数，那么不可能，输出 $-1$。

### 最小值

尽量选择 $6$ 个轮子的巴士，分类讨论：

如果 $6 \mid x$，那么所有巴士都是 $6$ 个轮子的，输出 $x \div 6$。

如果 $x \equiv 2(mod\space6)$，那么除了 $8$ 个轮子属于 $4$ 个轮子的巴士，其他巴士都是 $6$ 个轮子的，输出 $(x-8)\div6 + 2$。

如果 $x \equiv 4(mod\space6)$，那么除了 $4$ 个轮子属于 $4$ 个轮子的巴士，其他巴士都是 $6$ 个轮子的，输出 $(x-4)\div6 + 1$。

### 最大值

尽量选择 $4$ 个轮子的巴士，还是分类讨论：

如果 $4 \mid x$，那么所有巴士都是 $4$ 个轮子的，输出 $x \div 4$。

如果 $x \equiv 2(mod\space4)$，那么除了 $6$ 个轮子属于 $6$ 个轮子的巴士，其他巴士都是 $4$ 个轮子的，输出 $(x-6)\div4 + 1$。

## 代码

```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<queue>
#include<string>
#include<vector>
#define int long long
using namespace std;
const int INF=0x3f3f3f3f;
const int N=1e5+10;
const double eps=1e-5;
int read()
{
	char ch=getchar();
	int x=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48,ch=getchar();}
	return x*f;
}
int T;
signed main()
{
	T=read();
	while(T--)
	{
		int n=read();
		if(n<4||n%2)
		{
			puts("-1");
			continue;
		}
		if(n%6==0)
			printf("%lld ",n/6);
		else//利用C++long long除法向下取整的特性，可以直接写成这样，下面的n/4也是
			printf("%lld ",n/6+1);
		printf("%lld\n",n/4);
	}
	return 0;
}

```


---

## 作者：Withers (赞：0)

[题目传送门](https://codeforces.com/contest/1679/problem/A)
# 题目大意
给出一个整数 $n$，对满足 $4x+6y=n$ 的 $x,y$，求 $x+y$ 的最大值和最小值，若无解则输出-1
# 思路
我们要使得 $x+y$ 最大，那么就要让 $x$ 尽量大，最小就要让 $y$ 尽量小 ，然后再根据 $n$ 的余数情况适当调整，细节见代码
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,u,v,w,x,y,z,t;
//char s[200010];
int a[200010];
void read()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		long long l;
		scanf("%lld",&l);
		if(l%2!=0||l<=2) 
		{
			printf("-1\n");
			continue;
		}//奇数或者小于等于2，必然无解
		long long maxx=l/4,minn=l/6;//先假设全部取4/6
  		//如果是模4余2的话，就把一个4换成6，无需改变
		if(l%6==2||l%6==4) minn++;
  		//模6余2，那么就把6换成2个4
  		//模6余4，那么就再加一个4
  		//两种情况总数都是加一个
		printf("%lld %lld\n",minn,maxx);
	}
 } 
```


---

