# The Beatles

## 题目描述

Recently a Golden Circle of Beetlovers was found in Byteland. It is a circle route going through $ n \cdot k $ cities. The cities are numerated from $ 1 $ to $ n \cdot k $ , the distance between the neighboring cities is exactly $ 1 $ km.

Sergey does not like beetles, he loves burgers. Fortunately for him, there are $ n $ fast food restaurants on the circle, they are located in the $ 1 $ -st, the $ (k + 1) $ -st, the $ (2k + 1) $ -st, and so on, the $ ((n-1)k + 1) $ -st cities, i.e. the distance between the neighboring cities with fast food restaurants is $ k $ km.

Sergey began his journey at some city $ s $ and traveled along the circle, making stops at cities each $ l $ km ( $ l > 0 $ ), until he stopped in $ s $ once again. Sergey then forgot numbers $ s $ and $ l $ , but he remembers that the distance from the city $ s $ to the nearest fast food restaurant was $ a $ km, and the distance from the city he stopped at after traveling the first $ l $ km from $ s $ to the nearest fast food restaurant was $ b $ km. Sergey always traveled in the same direction along the circle, but when he calculated distances to the restaurants, he considered both directions.

Now Sergey is interested in two integers. The first integer $ x $ is the minimum number of stops (excluding the first) Sergey could have done before returning to $ s $ . The second integer $ y $ is the maximum number of stops (excluding the first) Sergey could have done before returning to $ s $ .

## 说明/提示

In the first example the restaurants are located in the cities $ 1 $ and $ 4 $ , the initial city $ s $ could be $ 2 $ , $ 3 $ , $ 5 $ , or $ 6 $ . The next city Sergey stopped at could also be at cities $ 2, 3, 5, 6 $ . Let's loop through all possible combinations of these cities. If both $ s $ and the city of the first stop are at the city $ 2 $ (for example, $ l = 6 $ ), then Sergey is at $ s $ after the first stop already, so $ x = 1 $ . In other pairs Sergey needs $ 1, 2, 3 $ , or $ 6 $ stops to return to $ s $ , so $ y = 6 $ .

In the second example Sergey was at cities with fast food restaurant both initially and after the first stop, so $ l $ is $ 2 $ , $ 4 $ , or $ 6 $ . Thus $ x = 1 $ , $ y = 3 $ .

In the third example there is only one restaurant, so the possible locations of $ s $ and the first stop are: $ (6, 8) $ and $ (6, 4) $ . For the first option $ l = 2 $ , for the second $ l = 8 $ . In both cases Sergey needs $ x=y=5 $ stops to go to $ s $ .

## 样例 #1

### 输入

```
2 3
1 1
```

### 输出

```
1 6
```

## 样例 #2

### 输入

```
3 2
0 0
```

### 输出

```
1 3
```

## 样例 #3

### 输入

```
1 10
5 3
```

### 输出

```
5 5
```

# 题解

## 作者：hsfzLZH1 (赞：2)

## 题目大意

有 $n\times k$ 座城市，排列成一个环形 $1-2-...-n\times k-1$ ，按顺序编号为 $1,2,...,n\times k$ ，其中第 $1,k+1,2\times k+1,...,(n-1)\times k+1$ 座城市中有快餐店。

一个人在某座城市中，每次行走他会从一座城市出发，向固定方向经过 $l$ 座城市（方向和 $l$ 事先不知道），你只知道出发城市到最近快餐店的距离 $a$ 和第一次行走到达的城市到最近快餐店的距离 $b$ 。

你需要在所有可能的情况中，找到第一次走回出发城市的最少行走次数和最多行走次数。

$1\le n,k\le 100000,0\le a,b\le \frac k 2$

## 解题思路

我们将编号 $-1$ 改为 $0,1,...,n\times k-1$ ，则环形为 $0-1-...-n\times k-1-0$ ，其中编号为 $0,k,2\times k,...,(n-1)\times k$ 的城市中有快餐店。

我们发现，城市编号为 $bk+t$ 时， $b$ 的取值对题目中给出的信息没有作用，所以我们不妨设 $b=0$ 。

转换题目中的条件，得

$city\equiv \pm a~(mod
~k)$

$city\pm l\equiv \pm b~(mod
~k)$

$l\le n\times k$

由于 $city$ 的值不是我们关心的值，所以我们只考察 $l$ 的值，发现 $l$ 的取值为：

$l\equiv \pm a\pm b~(mod~k)$ 且 $l\le n\times k$

$l$ 在 $mod~k$ 意义下只有 $4$ 种取值，由于 $l\le n\times k$ 所以一共只有 $4\times n$ 种取值，枚举即可。

现在的问题是，知道 $l$ ，找到第一次走回出发城市的行走次数。

设 $\frac {n\times k} l=\frac p q(\gcd(p,q)=1)$ ，则第一次走回出发城市的行走次数为 $p=\frac{n\times k}{\gcd(l,n\times k)}$ 。

时间复杂度 $O(n\log_2 (n\times k))$ 。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll inf=10000000010ll;
ll n,k,a,b,l,minn=inf,maxx=-inf;
ll gcd(ll x,ll y){return (x%y)?gcd(y,x%y):y;}
int main()
{
	scanf("%lld%lld%lld%lld",&n,&k,&a,&b);
	for(l=(a+b)%k;l<=n*k;l+=k)if(l)minn=min(minn,n*k/gcd(l,n*k)),maxx=max(maxx,n*k/gcd(l,n*k));
	for(l=(a-b+k)%k;l<=n*k;l+=k)if(l)minn=min(minn,n*k/gcd(l,n*k)),maxx=max(maxx,n*k/gcd(l,n*k));
	for(l=(-a+b+k)%k;l<=n*k;l+=k)if(l)minn=min(minn,n*k/gcd(l,n*k)),maxx=max(maxx,n*k/gcd(l,n*k));
	for(l=(-a-b+k+k)%k;l<=n*k;l+=k)if(l)minn=min(minn,n*k/gcd(l,n*k)),maxx=max(maxx,n*k/gcd(l,n*k));
	printf("%lld %lld\n",minn,maxx);
	return 0;
}
```

---

## 作者：Tenshi (赞：1)

如果图裂了可以看[这里](https://www.cnblogs.com/Tenshi/p/15425741.html)

## 分析

分类讨论。

我们记出发点为 $s$，走一步后（距离为 $L$）到达的点为 $t$。

我们根据 $s,t$ 的位置分成四种（$2\times2$）情况：

![](https://img2020.cnblogs.com/blog/2185228/202110/2185228-20211019172915373-1122739308.png)

+ $s,t$ 分别在 ①，①，此时 $L = b-a+ik$。

+ $s,t$ 分别在 ①，②，此时 $L = (k-b)-a+ik$。

+ $s,t$ 分别在 ②，①，此时 $L = b-(k-a)+ik$。

+ $s,t$ 分别在 ②，②，此时 $L = (k-b)-(k-a)+ik$。

求出 $L$ 后，我们只需求出当前 $L$ 所对应的圈数 $res$，用 $res$ 更新 $x,y$ 即可。

也就是对于 $uL = vnk$，我们要找到最小的 $u$，这个 $u$ 便是 $res$。

这是经典的 $AX = BY$ 形式的式子，有 $X = \frac{B}{gcd(A, B)}$，故 $res = \frac{nk}{gcd(L, nk)}$

```cpp
#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;

#define endl '\n'
#define debug(x) cerr << #x << ": " << x << endl
#define pb push_back
#define eb emplace_back
#define set0(a) memset(a,0,sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);i++)

inline void read(int &x) {
    int s=0;x=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

#define int long long

int x, y;
int n, k, a, b;

int gcd(int a, int b){
	return b? gcd(b, a%b): a;
}

void get(int L){
	if(L<0) L+=n*k;
	int res=n*k/gcd(L, n*k);
	x=max(x, res), y=min(y, res);
}

signed main(){
	cin>>n>>k>>a>>b;
	x=0, y=ll_INF;
	rep(i,0,n-1){
		int L;
		L=b-a+i*k;
		get(L);
		L=(k-b)-a+i*k;
		get(L);
		L=b-(k-a)+i*k;
		get(L);
		L=(k-b)-(k-a)+i*k;
		get(L);
	} 	
	
	cout<<y<<' '<<x<<endl;
	
	return 0;
}
```



---

## 作者：Piwry (赞：1)

写这道题时往 exgcd 方向推了好久...结果实际上和 exgcd 没啥关系（数论快忘光了 \kk）

## 题意

有 $n\cdot k$ 个城市围成一个环，相邻城市间的路程（边权）为 $1$ km

在第 $1,1+k,1+2k,\cdots, 1+(n-1)k$ 个城市处有关键点

一开始从编号为 $s$ 的城市出发，每次向右走 $l$ km，直到重新走回 $s$

现不给出 $s, l$，而是给出 $s$ 和 $s+l$ 分别距离最近的关键点的距离 $a, b$

问最少、最多走几次才能回到 $s$

（luogu 翻译里那个 $l\leq n\cdot k$ 题面中貌似并没给出）

## 解析

显然 $a, b$ 只可能有四种情况：

![ab](https://cdn.luogu.com.cn/upload/image_hosting/vrsvkwt6.png)

（注意 `情况一` $a, b$ 之前可能只隔**一个**关键点；`情况二`、`情况三`、`情况四` $a, b$ 之间也可能**不隔**关键点）

我们先只考虑 `情况一`（其它情况是差不多的）

显然只需找到最小的（正整数）$x$ 满足 $x(a+tk+b)\equiv 0\pmod {nk}$（其中 $(a+tk+b)$ 就是 $l$）

我们把这个式子写为 $x(a+tk+b)=y(nk)$，其中 $y$ 是一个正整数

先不管 $t$。固定 $t$（$l$），考虑怎么求出最小的 $x$ 值

首先应当有 $\gcd(x, y)=1$，否则我们可以将 $x, y$ 均除 gcd，从而得到更小的 $y$

再观察式子，可以发现其实就有 $x(a+tk+b)=y(nk)=\text{lcm}(x(a+tk+b), y(nk))$

证明可以考虑 lcm 的定义（其实是我不太会解释 \kk）。且此时 $x, y$ **都是**满足等式最小的正整数 $x, y$

接着可以发现大于 $nk$ 的 $(a+tk+b)$ 没有意义；因为此时的 $l$ 实际上就是 $(a+tk+b)\mod {nk}=((a+(t-n)k+b)+nk)\mod {nk}$，而这个值之前已经遍历过了

于是只需枚举 $t$（$l$），遍历所有情况即可。总复杂度约 $O(n\log n)$

## CODE

```cpp
#include <cstdio>
#include <iostream>
#define ll long long
using std::min;
using std::max;

ll gcd(ll a, ll b){
//	if(a == 0 || b == 0)
//		return 1;
	while(b ^=a ^=b ^=a %=b) ;
	return a;
}

int main(){
	ll n, k, a, b;
	scanf("%lld%lld%lld%lld", &n, &k, &a, &b);
	ll mn =0x7f7f7f7f7f7f7f7f, mx =-0x7f7f7f7f7f7f7f7f;
	ll start_l[4];
	start_l[0] =a+b, start_l[1] =(k-b)-a;/*情况一，情况二*/
	start_l[2] =(-a)+b, start_l[3] =a+(-b);/*情况三，情况四*/
	for(int i =0; i < 4; ++i)
		for(ll l =start_l[i]; l <= n*k; l +=k){/*因为每次加 k，l 超过 n*k 后取值一定循环*/
			if(l <= 0)
				continue;
			/*xl = y(nk)*/
		//	ll Lcm =l/gcd(l, n*k)*n*k;/*炸 ll*/
		//	ll x =Lcm/l;
			ll x =n*k/gcd(l, n*k);
			mn =min(mn, x);
			mx =max(mx, x);
		}
	printf("%lld %lld", mn, mx);
}
```

---

## 作者：Wander_E (赞：0)

# The Beatles 题解
### 题意
有 $n \times k$ 个城市排成一个环，其中编号形如 $1 + xk$ 的城市有麦当劳。Sergey 从编号为 $s$ 的城市（下称 S 城）出发，每次移动 $l$ 个城市，但是他忘了 $s$ 和 $l$，他只记得离 S 城最近的麦当劳距离 S 城 $a$ 个城市，当他第一次移动后离他最近的麦当劳距离为 $b$，求他最少 / 多走多少次回到 S 城。
### 思路
这是一道数学题。

由题可知：
$$ \begin{cases} 
s \equiv \pm a \pmod p\\
s + l\equiv \pm b\pmod p
\end{cases}$$
分四类讨论 $l$，又因为 $l \le n k$ 所以枚举 $4n$ 次即可。

设首次到达所需移动次数为 $x$ 则：
$$x = \frac{n k}{\gcd(l, nk)}$$

答案即为 $\min x$ 和 $\max x$。
### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, k, a, b;
int maxn = -1, minn = 0x3f3f3f3f3f3f3f3f;

signed main()
{
	cin >> n >> k >> a >> b;
	for(int i = (a + b) % k; i <= n * k; i += k)
	{
		maxn = max(maxn, (n * k) / __gcd(i, n * k));
		minn = min(minn, (n * k) / __gcd(i, n * k));
	}
	for(int i = (a + k - b) % k; i <= n * k; i += k)
	{
		maxn = max(maxn, (n * k) / __gcd(i, n * k));
		minn = min(minn, (n * k) / __gcd(i, n * k));
	}
	for(int i = (k - a + b) % k; i <= n * k; i += k)
	{
		maxn = max(maxn, (n * k) / __gcd(i, n * k));
		minn = min(minn, (n * k) / __gcd(i, n * k));
	}
	for(int i = (k - a + k - b) % k; i <= n * k; i += k)
	{
		maxn = max(maxn, (n * k) / __gcd(i, n * k));
		minn = min(minn, (n * k) / __gcd(i, n * k));
	}
	cout << minn << ' ' << maxn << endl;
	return 0;
}

```

---

## 作者：xiaohuang (赞：0)

[更好的阅读体验](https://xiaohuang888.github.io/2019/09/02/%E3%80%8E%E9%A2%98%E8%A7%A3%E3%80%8FCodeforces1142A%20The%20Beatles/)

### Solution

我们根据题目的$a, b, k$计算出$l$的$4$种可能：

1. $a + b$

2. $k - a + b$

3. $k + a - b$

4. $k - a - b$

每走一步的答案就是$\frac{n \times k}{\gcd(n \times k, step)}$。

然后枚举找个最大的与最小的就可以了。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

typedef long long LL;
const LL INF = 1e18;
LL n, k, a, b, step;
int main() {
    scanf("%lld%lld%lld%lld", &n, &k, &a, &b);
    LL Max = -INF, Min = INF;
    step = fabs(a + b);//第1种情况
    while (step <= n * k) {//枚举步数
        if (step) {
            Max = max(Max, n * k / __gcd(n * k, step));
            Min = min(Min, n * k / __gcd(n * k, step));
        }
        step += k;
    }
    step = fabs(k - a + b);//第2种情况
    while (step <= n * k) {//枚举步数
        if (step) {
            Max = max(Max, n * k / __gcd(n * k, step));
            Min = min(Min, n * k / __gcd(n * k, step));
        }
        step += k;
    }
    step = fabs(k - b + a);//第3种情况
    while (step <= n * k) {//枚举步数
        if (step) {
            Max = max(Max, n * k / __gcd(n * k, step));
            Min = min(Min, n * k / __gcd(n * k, step));
        }
        step += k;
    }
    step = fabs(k - a - b);//第4种情况
    while (step <= n * k) {//枚举步数
        if (step) {
            Max = max(Max, n * k / __gcd(n * k, step));
            Min = min(Min, n * k / __gcd(n * k, step));
        }
        step += k;
    }
    printf("%lld %lld\n", Min, Max);
    return 0;
}
```

---

