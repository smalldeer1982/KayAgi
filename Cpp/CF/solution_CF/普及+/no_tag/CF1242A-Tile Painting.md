# Tile Painting

## 题目描述

### 题意简述

有一条由 $n$ 块瓷砖拼成的长度为 $n$ 的路。

对于两块瓷砖 $i,j$，如果 $ |i-j| > 1 $ 且 $n$ $\text{mod}$ $|i-j|=0$ ，那么它们的颜色必须相同。

求出最多可以使用多少不同颜色的瓷砖，并且满足上述要求。

## 样例 #1

### 输入

```
4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
```

### 输出

```
5
```

# 题解

## 作者：XY_cpp (赞：6)

case 1：$n=p^k$ ,跳的最小步长为$p$,所以答案为$p$

证明: 考虑剩余系是$[0,p-1]$,那么最多能涂$n$个颜色.

case 2: $n!=p^k$,答案为$1$

可能我太菜了,看不懂$CRT$的证明,但是我想到一种简单的.

证明: 

因为 $n!=p^k$

所以必然有两个质因数$a,b$,满足$gcd(a,b)=1$

设$ax+by=m$|$x,y$表示前进的步数,$m$表示到达的格点号

因为$gcd(a,b)=1$

所以, 对于$\forall m\in [1,n]$

$\exists x,y$满足$ax+by=m$

综上 若$n!=p^k$,答案为$1$

代码展示

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=105;
int n;
vector<int>a;
void init()
{
    for(int i=2;i*i<=n;i++)
        if(n%i==0)
        {
            a.push_back(i);
            while(n%i==0) n/=i;
        }
    if(n!=1) a.push_back(n);
    sort(a.begin(),a.end());
}
signed main()
{
    cin>>n;
    init();
    if(a.size()==1) printf("%lld\n",a.front());
    else if(a.empty()) printf("%lld\n",n);
    else puts("1");
    return 0;
}
```

---

## 作者：lsr1409111459 (赞：5)

#### 1 题目描述（[传送门](https://www.luogu.com.cn/problem/CF1242A)）

##### 1.1 题目大意

你要粉刷从你的房子到你的大门的小路。

小路共有 $n$ 个瓷砖，标号为 $1$ 到 $n$ ，你将用一些颜色粉刷它们。

要满足：如果两个瓷砖的序号是 $i$ 和 $j$ ，有 $|i-j|>1$ 且 $n\ mod\ |i-j|=0$ ，则这两个瓷砖要粉刷一样的颜色。

##### 1.2 输入格式

一行一个整数 $n(1\leq n \leq 10^{12})$ ，表示路的长度。

##### 1.3 输出格式

一行一个整数，表示能用到的满足题意的最多的颜色数量。

#### 2 解题思路

最开始想到了二分答案，但check过程时间复杂度是很高的（甚至可以到      $O(n)$ ），这对于本题这种 $n$ 很大的情况是不可取的。

其实这是一道数学题。我们考虑 $n\ mod\ |i-j|=0$ ，其实如果找出的 $n$ 的因子，那么问题就迎刃而解了。再进一步考虑，如果 $n=8$ ，那么因子有  $1,2,4,8$ ，但其实如果想满足 $n\ mod\ |i-j|=0$ 的话， $|i-j|$ 只能是  $2$ ，因为其包含 $|i-j|=4$ 的情况。换句话说，如果 $|i-j|=4$ 的话，我们是不能用 $4$种 颜色的，因为模 $4$ 等于 $0$ 的数模 $2$ 也一定等于    $0$ 。

因此，我们只需要找质因数。再考虑如果一个数有多个质因数的情况。假设    $n$ 有质因数 $p_1,p_2$ ，那么其实要考虑的是 $ap_1+bp_2$ 能组合出来的数字。可以证明两个质数的线性组合是可以组合出任意数的（[证明参考](https://blog.csdn.net/weixin_33871366/article/details/93725878)）。

两条重要定理：两个互质数的线性组合等于 $1$ 必定有解。两个质数一定互质。（可以组合成裴蜀定理的一部分）

回归问题，如果 $n$ 有两个质因子，那么它们可以组合使得任意两个瓷砖都要颜色相同。

总结一下：

（1）如果 $n$ 本身是质数，那么最大颜色数就是 $n$ 。

（2）如果 $n$ 是合数且 $n$ 有且仅有一个质因子，那么最大颜色数就是这个质因子。

（3）如果 $n$ 是合数但 $n$ 有两个及以上质因子，那么最大颜色数为 $1$ 。

最后我们考虑如何找质因子，一种办法是先找出所有的质数然后挨个枚举是否是 $n$ 的质因子。但是 $n$ 本身很大，而且如果 $n$ 等于 $2$ 和一个超大质数相乘的话，那筛出的别的质数就都没有用了。所以我们直接对 $n$ 进行拆分。

#### 3 解题代码

```cpp
#include <iostream>
#include <cmath>
using namespace std;
long long n;
long long p[5000010],cnt;
int main()
{
    cin>>n;
    long long ans=n;
    for(long long i=2;i<=sqrt(n);i++)//很朴素的拆质因数，i从2枚举到根号n
    {
        if(n%i==0)
        {
            p[++cnt]=i;
            while(n%i==0)n/=i;//用尽可能多的质因子拆n，比如2拆8可以拆3次
        }
        if(n<i)break;
    }
    if(n>1)p[++cnt]=n;
    if(cnt==1)printf("%lld\n",p[1]);//这里cnt==1包含n本身就是质数的情况
    else printf("1\n");
    return 0;
}
```

#### 4 解题心得

数论数论数论，冲NOIP的时候就一直搞不明白的东西。或许现在还只能搞懂gcd相关。什么中国剩余定理费马小定理等等等等，数论还是要学的。这次的裴蜀定理也只是考场上觉得是这么回事儿，要是真证明自己也还是啥都不会。数论还是要搞的。

---

## 作者：nytyq (赞：1)

## 思路

这是一道数学题。

下面定义 $\text{Prime}$ 为素数集。

如果满足 $|i-j|>1$ 且 $n$ $\text{mod}$ $|i-j|=0$，则考虑到对 $n$ 质因子分解。

如果对于两个素数 $p,q$，则一定 $px+qy=1$ 的整数解 $(x,y)$，意思是两个素数任意组合即可达成目标。

考虑分 $3$ 种情况：

1. 如果 $n$ 本身是一个素数，则答案为 $n$。
2. 如果 $n$ 适合数且只有一个质因子 $p$，则答案为 $p$。
3. 如果 $n$ 是合数且 $n=p \times q \times k$，其中 $p,q \in \text{Prime} $ 且 $P \nmid k(P \in Prime)$，则答案为 $1$。

代码在 [here](https://www.luogu.com.cn/paste/xc2twgyw)。

---

## 作者：Milky_Cat (赞：1)

感觉这题一点也不复杂啊 qwq。

公理：任意两个不相同的素数互质。

推论：若 $n$ 存在两个不相同的素因数 $x,y$，则 $n \geq xy$。

由推论和裴蜀定理知，$ax+by=c$ 这个不定方程有整数解当且仅当 $\gcd(x,y) \mid c$。这告诉我们对于两个素因数 $x,y$，经过组合可以推得任意两个瓷砖的颜色都两两相等。于是答案为 $1$。

剩下的情况，注意到 $n$ 只存在一个素因数 $x$，$x$ 把瓷砖划分成了 $x$ 份（根据余数），所以答案为 $x$。

这就做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
vector<long long> vec;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n;
	long long tmpn = n;
	for (long long i = 2; i * i <= tmpn; i++){
		if (tmpn % i == 0){
			vec.push_back(i);
			while (tmpn % i == 0)
				tmpn /= i;
		}
	}
	if (tmpn != 1)
		vec.push_back(tmpn);
	if (vec.size() == 1)
		cout << vec[0];
	else
		cout << 1; 
	return 0;
}
```

---

## 作者：Otue (赞：1)

这道题随便举几个例子就能做了：

当 $n=9$ 时：$3$ 都为 $9$ 的一个非 $1$ 因子，我们最多可把 $1,4,7$ 分为第一种颜色，$2,5,8$ 分为第二种颜色，$3,6,9$ 分为第三种颜色。

当 $n=15$ 时，$3,5$ 都为 $15$ 的因子。我们先考虑 $3$，那么 $1,4,7,10,13$ 为第一组颜色，$2,5,8,11,14$ 为第二组颜色，$3,6,9,12,15$ 为第三组颜色。再考虑 $5$，结果发现 $1,6$ 时不同颜色，不合法！那么我们可知道：这三组的颜色必须全部相同，否则 $5$ 分出的 $(1,6),(2,7),\dots,(10,15)$ 会和这三组颜色矛盾。

为啥 $n=9$ 就不会出现矛盾？

这是因为当 $n$ 为 $p^k$ 的形式时，对于第一个因子 $p$，我们可分为 $p$ 组不同颜色。对于第二个因子 $p^2$，可以发现它和这 $p$ 组完全兼容，$p^3,p^4,\dots,p^k$ 都是同样的道理。

否则，我们就只能染一种颜色了。

### 代码
```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 3e5 + 5;

int n;
vector<int> v;

signed main() {
	cin >> n;
	for (int i = 2; i <= n / i; i++) {
		if (n % i == 0) {
			v.push_back(i);
			while (n % i == 0) n /= i;
		}
	}
	if (n > 1) v.push_back(n);
	if (v.size() == 1) cout << v[0] << endl;
	else puts("1");
} 
```
祝大家学习愉快！

---

## 作者：chlchl (赞：1)

小破题因为 ``%lld`` 写成 ``%d`` 挂了两次，好啊。

~~比较没~~有意思的数学题。

## Solution
显然 $|i-j|$ 是 $n$ 的非 $1$ 因数时，$i$ 和 $j$ 的颜色均需相同。

但是，比如 $n=4$，它有 $4$ 和 $2$，此时答案肯定是 $2$，因为其包含 $4$。

又比如 $n=10$，它有 $2$ 和 $5$，此时答案肯定是 $1$，因为如果答案是 $2$，第一个格子和第六个格子的颜色肯定不同（而它们的差又刚好是 $5$）。

所以猜到结论：
- $n$ 只有一个质因数时可以输出该质因数，这个证明平凡；
- $n$ 是质数，颜色总数可以是 $n$；
- 其他情况（有大于一个质因数）都只能是 $1$。

接下来考虑证明。

#### 证明
我们的证明只有一个目标：证明当质因数个数 $>1$ 时只能输出 $1$。

假设现在有两个质数 $a,b$，且 $n$ 同时是这两个质数的倍数。

我们把这 $n$ 个格子，分别每隔 $a$ 个、$b$ 个涂上颜色，涂成两个不同的颜色序列 $A,B$。那么，第一个 $A_i,B_i$ 都涂上了颜色的 $i$ 一定是 $\text{lcm}(a,b)$，如下图所示（下图 $a=2,b=3$）。

![](https://cdn.luogu.com.cn/upload/image_hosting/q4jfnwyt.png?x-oss-process=image/resize,m_lfit,h_400,w_500)

因为 $a,b$ 互质，所以 $\text{lcm}(a,b)=a\times b$。

这就出现问题了，以 $A$ 为例，它涂色的第 $b$ 个格子才与 $B$ 的对应格子相符，那么它前 $b-1$ 个涂色的格子就对不上 $B$ 中涂色的格子了。

而这些涂色的格子，正是我们题目中说到的要求“涂的颜色相同”的格子。

所以得出结论，如果 $n$ 具有 $\ge 2$ 个质因数，此时如果涂多种颜色，那么必定出现“涂色错位”的情况，也必定出现无法同时满足两个要求。

简单地证明过后，代码就呼之欲出了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n;
vector<int> ys;

main(){
	cin >> n;
	for(int i=2;i*i<=n;i++){
		if(n % i == 0)
			ys.push_back(i);
		while(n % i == 0)
			n /= i;
	}
	if(n > 1)
		ys.push_back(n);
	if(ys.size() == 0)
		printf("%lld\n", n);
	else if(ys.size() == 1)
		printf("%lld\n", ys[0]);
	else
		printf("1\n");
	return 0;
}
```


---

## 作者：K_yuxiang_rose (赞：0)

为了方便，这里瓷砖的下标都是从 $0$ 开始。

当 $n$ 是质数时，通过分析可知每个瓷砖都可以涂上不同颜色，因为 $n$ 的因数只有 $1$ 和 $n$ 而题目要求两个瓷砖的距离不能等于 $1$ 并且不存在两个瓷砖的距离等于 $n$。

当 $n$ 不是质数并且只有一个质因数 $x$ 时，答案就是 $x$，因为对于瓷砖 $0$ 到瓷砖 $x-1$ 都可以涂成不同颜色并且满足条件。

当 $n$ 有两个及以上不是 $n$ 的质因数时，我们设它的两个质因数为 $x$ 和 $y$，先以只有一个质因数时的情况一样，从 $0$ 到 $x-1$ 构造不同颜色，后面的瓷砖按照题目要求构造。我们再尝试加入 $y$，发现怎么构造都无法使它们满足条件。为什么呢？

一堆需要满足颜色相同的瓷砖为：

$0,y,2y,3y,4y,\dots$

它们对 $x$ 取模后为：

$0,y\bmod x,2y\bmod x,3y\bmod x,4y\bmod x,\dots$

因为 $x$ 和 $y$ 互质，所以不存在不同的非负整数 $k_1$ 和 $k_2$ 使得 $k_1y\equiv k_2y \pmod x$ 并且 $k_1y,k_2y<xy$。

也就是说，这一堆数中可以选出一些数组成 $0$ 到 $x-1$ 的全排列。这时回到我们之前构造的有 $x$ 种不同颜色的情况，这些组成 $0$ 到 $x-1$ 的全排列的数就相当于连接了这 $x$ 种颜色，使这些颜色必须相同。所以，当 $n$ 有两个及以上不是 $n$ 的质因数时，这些所有的瓷砖的颜色都必须相同。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<int> v;
signed main()
{
	int n;
	cin>>n;
	for(int i=2;i*i<=n;i++)
	{
		if(n%i==0)
		{
			v.push_back(i);
			while(n%i==0) n/=i;
		}
	}
	if(n!=1) v.push_back(n);//这里是防止循环退出质因数还没被算尽的情况
	if(v.size()==1) cout<<v[0];
	else if(!v.size()) cout<<n;
	else cout<<1;
	return 0;
}
```

AC记录：
![](https://cdn.luogu.com.cn/upload/image_hosting/dtdtaeg3.png)

---

## 作者：梧桐灯 (赞：0)

萌新第一次打Div1~~结果直接掉蓝嘤嘤嘤~~

A还是十分友好的。

一个数只有两个因子，那不就是质数嘛。

所以首先考虑质因数分解。

如果它只有一个质因子，那么答案就是这个质因子的大小，这个是显然成立的。设这个质因子为x，我们可以把这个数分为1,x+1,2x+1; 2, x+2,2x+2 ……， x-1,2x-1...因为它只有一个质因子，所以这显然是成立的。

如果它有多个质因子。那么这些质因子一定互质（显然），所以我们只能涂一个颜色。这个在草稿纸上画一画就能够证出来。

代码：
```
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
const int N = 37;
ll n, p[N];
int v;
 
inline int zs (const ll x) {
	for (register int y = 2; 1ll * y * y <= x; ++y) {
		if (!(x % y)) return 0;
	}
	return 1;
}
 
int main () {
	cin >> n;
	if (zs (n)) {
		cout << n << '\n';
		return 0;
	}
	for (register int i = 2; 1ll * i * i <= n; ++i) {
		if (!(n % i)) {
			p[++v] = i;
			while (!(n % i)) n /= i;
		}
	}
	if (n > 1) p[++v] = n;
	if (v == 1) cout << p[1] << '\n';
	else puts ("1");
	return 0;
}
```
说句闲话：

当我锁了这道题hack别人程序时，发现我居然没有考虑1！后来发现自己质数也没有考虑1，所以我相当于把1当作质数输出了……嗯幸好是对的QwQ


---

