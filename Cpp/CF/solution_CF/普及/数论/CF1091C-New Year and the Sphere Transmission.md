# New Year and the Sphere Transmission

## 题目描述

There are $ n $ people sitting in a circle, numbered from $ 1 $ to $ n $ in the order in which they are seated. That is, for all $ i $ from $ 1 $ to $ n-1 $ , the people with id $ i $ and $ i+1 $ are adjacent. People with id $ n $ and $ 1 $ are adjacent as well.

The person with id $ 1 $ initially has a ball. He picks a positive integer $ k $ at most $ n $ , and passes the ball to his $ k $ -th neighbour in the direction of increasing ids, that person passes the ball to his $ k $ -th neighbour in the same direction, and so on until the person with the id $ 1 $ gets the ball back. When he gets it back, people do not pass the ball any more.

For instance, if $ n = 6 $ and $ k = 4 $ , the ball is passed in order $ [1, 5, 3, 1] $ .

Consider the set of all people that touched the ball. The fun value of the game is the sum of the ids of people that touched it. In the above example, the fun value would be $ 1 + 5 + 3 = 9 $ .

Find and report the set of possible fun values for all choices of positive integer $ k $ . It can be shown that under the constraints of the problem, the ball always gets back to the $ 1 $ -st player after finitely many steps, and there are no more than $ 10^5 $ possible fun values for given $ n $ .

## 说明/提示

In the first sample, we've already shown that picking $ k = 4 $ yields fun value $ 9 $ , as does $ k = 2 $ . Picking $ k = 6 $ results in fun value of $ 1 $ . For $ k = 3 $ we get fun value $ 5 $ and with $ k = 1 $ or $ k = 5 $ we get $ 21 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1091C/d99b7ec9698661c180178c4296e69ed6a8f083c5.png)In the second sample, the values $ 1 $ , $ 10 $ , $ 28 $ , $ 64 $ and $ 136 $ are achieved for instance for $ k = 16 $ , $ 8 $ , $ 4 $ , $ 10 $ and $ 11 $ , respectively.

## 样例 #1

### 输入

```
6
```

### 输出

```
1 5 9 21
```

## 样例 #2

### 输入

```
16
```

### 输出

```
1 10 28 64 136
```

# 题解

## 作者：一扶苏一 (赞：3)

## Description

有 $n$ 个人围成一个圈，按照顺时针从 $1$ 到 $n$ 编号。第 $1$ 个人会拿到一个球，他指定一个数字 $k$，然后会将球传给他后面顺指针数第 $k$ 个人。再次传到 $1$ 后游戏结束。定义一次游戏的 $ans$ 为所有拿到球的人的编号之和 （$1$ 只算一次）。求所有可能的 $ans$，按照升序输出，保证不超过 $10^5$ 个

## Input

一个整数 $n$

## Output

一行多个整数，代表所有可能的 $ans$。按照是升序输出。

## Hint

$1~\leq~n~\leq~10^9$

## Solution

我们不妨将位置从 $0~\sim~n-1$ 编号。则一个位置 $p$ 会在一次传球中被传到当且仅当 $p~\equiv~xk~\pmod n$，其中 $x~\in~Z^+$。

考虑上面的同余方程，他等价于 $xk~+~yn~=~p$，其中 $x,y~\in~Z^+$。根据裴蜀定理，这个方程有整数解当且仅当 $\gcd(k,n) \mid p$。考虑因为 $k~\in~[1,n]$，所以 $\gcd(k,n)$ 显然与 $n$ 的因数一一对应。于是直接枚举 $n$ 的因数 $s$，则对答案产生贡献的只有 $0,s,2s,3s~\dots~ts$，其中 $t~=~\frac{n}{s}$。这是一个等差数列，直接使用等差数列求和公式可以 $O(1)$ 计算答案。考虑我们位置是从 $0~\sim~n-1$ 编号的，所以每个位置的贡献都少算了 $1$，总共少算了 $t$，最后加上 $t$ 即可。另外因为编号最大的位置 $ts$ 事实上就是 $0$ 号位置，我们对这个位置的贡献算了两遍，减掉第二遍计算的贡献 $n$ 即可。

时间复杂度 $O(\sqrt n)$

## Code

```cpp
#include <cmath>
#include <cstdio>
#include <set>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

ll n;
std::set<ll>ss;

void work(cl);

int main() {
	freopen("1.in", "r", stdin);
	qr(n);
	for (rg int i = 1, sn = sqrt(n); i <= sn; ++i) if (!(n % i)) {
		work(i);
		work(n / i);
	}
	for (std::set<ll>::iterator it = ss.begin(); it != ss.end(); ++it) qw(*it, ' ', true);
	putchar('\n');
	return 0;
}

void work(cl s) {
	ll y = n / s;
	ll ans = (((s + y * s) * y) >> 1) + y - n;
	ss.insert(ans);
}
```



---

## 作者：woshishei (赞：2)

很容易发现$\{f_k | k\text{是}n\text{的约数}\}$就是答案。

例如$n=30$，则$f_1,f_2,f_3,f_5,f_6,f_{10},f_{15},f_{30}$就是最后的结果，其他数，例如$f_{24}$，就和$f_6$的结果是一样的。

所以可以枚举$n$的约数，再通过等差数列求和公式就能得出答案。

时间复杂度：$O(\sqrt{n}+t)$，其中$t$为答案总数。

**代码：**362ms, 792KB

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
int n,cnt=0;
ll ans[100010];//记得开long long
int main()
{
	scanf("%d",&n);
	for(int i=1;i*i<=n;i++)//枚举约数
	{
		if(n%i!=0)continue;
		ans[++cnt]=(ll)(1+n-i+1)*(n/i)/2;//等差数列求和f(i)
		if(i*i==n)continue;
		ans[++cnt]=(ll)(1+n-n/i+1)*i/2;//再求一次f(n/i)
	}
	sort(ans+1,ans+cnt+1);//记得是从小到大输出
	for(int i=1;i<=cnt;i++)
    	if(ans[i]!=ans[i-1])//去重
			printf("%I64d ",ans[i]);
	return 0;
}
```
吐槽：

- 数据保证不超过$10^5$个解，但是好像没有数超过$10^5$个因数……
- 最近恶意评分不是一件小事了。


---

## 作者：lahlah (赞：2)

题目链接：https://www.luogu.org/problemnew/show/CF1091C


-------------------------分鸽-------------------------------------------------------------------------------------------

这题的题意就是$n$个人围成一圈，从第一个人开始，每次可以往后跳$k$步$(1<= k <= n)$最后跳回第一个人那里, 对于每个k把它经过的人的编号加起来，假设为$f_{k}$, 把$f_{k}$排序后去重然后输出。

-------------------------分鸽$\times 2$-------------------------------------------------------------------------------------------

我们观察样例解释，$k = 1$ 和 $k = 5$ 的图，发现值是一样的，观察或推理一下可以发现$gcd(1, n)$ 和 $gcd(5, n)$ 是相同的，$k = 2$ 和 $k = 4$ 同理，所以我们只需要把$n$的约数求出来，因为是每次加$k$的，所以直接算一下等差序列就行了

时间复杂度$O$ $($ 约数个数$)$ 

$code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, ans[4000005], sz;
void check(long long x){
	 ans[++ sz] = (1 + n - x + 1) * n / x / 2; //算等差序列，1+n-x为末项， 1为首项， 项数为n / x
}
int main(){
	scanf("%I64d", &n);
	for(int i = 1; i * i <= n; i ++){
		if(n % i == 0){//求约数
			check(i);
			if(i * i != n)check(n / i);
		}
	}
	sort(ans + 1, ans + 1 + sz); //记得要排序
	for(int i = 1; i <= sz; i ++) printf("%I64d ", ans[i]);
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：1)

## 思路

首先通过观察题目我们可以发现，这道题跳的步数一定是 n 的因数。因为只是单纯的求和，不考虑实际的步长，我们把 **后文的“步长”定义为相邻的两个能走到的位置之差。**

那么显然步长和步数的积等于 $n$。因此我们枚举一下步长，只要它能被 $n$ 整除，它一定会出现不同的步长，否则它一定能乘上一个数 $k$ 等于 $n$，一定会被算过，所以没有必要考虑。

因此每次枚举 $1$ 到 $\sqrt{n}$。如果 $i$ 能整除 $n$，那么就有一对因数：$i$ 和 $\frac{n}{i}$。那么只需要算出这两种情况的和就行了。观察易发现这其实就是个等差数列。对于因数 $x$ 的求和，我们已知首项为 $1$，公差为 $x$，项数为 $\frac{n}{x}$，那么末项就能求出来，再用求和公式算一下就完成了。

因为 $n$ 的因数数量不超过 $2 \times \sqrt{n}$，所以数组不用开太大。最后去重输出就做完了。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[200005]; // 因为 n 的因数不超过 2*sqrt(n) 所以开这么大就够了。 
signed main()
{
	int n; scanf("%lld",&n);
	
	int tot=0;
	for(int i=1;i*i<=n;i++)
		if(n%i==0)
		{
			int sx=1,xs=n/i,gc=i; // sx: 首项； xs: 项数； gc: 公差； mx:末项； 
			int mx=sx+(xs-1)*gc; // 末项 = 首项 + （项数 - 1） * 公差
			a[++tot]=(sx+mx)*xs/2; // 和 = （首项 + 末项） * 项数 / 2 
			
			// 上面是 i 的情况，下面是 n/i  的情况，因为 n 因数成对；由于最后需要去重，就不考虑 i*i = n 的时候会算两遍了。 
			
			sx=1,xs=i,gc=n/i;
			mx=sx+(xs-1)*gc;
			a[++tot]=(sx+mx)*xs/2;
		}
	 
	sort(a+1,a+1+tot);
	int m=unique(a+1,a+1+tot)-a-1; // 排序 + 去重 
	
	for(int i=1;i<=m;i++)
		printf("%lld ",a[i]);
	return 0;
}
```

$$ \large\text{----------- THE END -----------}$$

$$ \text{ thanks for reading.}$$

---

## 作者：_ayaka_ (赞：0)

### 思路

先考虑暴力枚举，肯定炸。

仔细观察会发现有些路线是重复的，那我们肯定要省略掉重复路线从而大大优化时间。

我们可以发现每次经过的点是固定的，即 $1,1+1k,1+2k,1+3k\  ...\ 1+xk$（已省略 $\bmod\ n$），而 $xk\mid n$。而假如两个 $k$ 在求解后所得的 $x$ 相等，就说明他们跳了同样的次数，那他们就是相等的。

那 $x$ 又等于多少呢？既然 $xk\mid n$，那么我们就可以知道 $x=\frac{n}{\gcd(k,n)}$。而 $n$ 又是固定的，所以我们只需要求出所有 $k$ 是 $n$ 的因子的路线就求出了所有 $\gcd(k,n)$ 不同，也就是 $x$ 不同的路线了！

顺便提一嘴，因为所有的路线中的 $k$ 都是 $n$ 的因子，所以没有任何路线会出现跨过 $n$ 的情况，所以我们可以用等差数列求解。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, ans[100005], cnt;
signed main() {
	cin >> n;
	for (int i = 1; i * i <= n; i ++) {
		if (n % i != 0) continue;
		ans[++ cnt] = (1 + n - i + 1) * n / i / 2;//等差数列：首项(1)*末项(n-i+1)*项数(n/i)/2 
		if (i * i != n) ans[++ cnt] = (1 + n - n / i + 1) * i / 2;//同时求出k=n/i的答案 
	}
	sort(ans + 1, ans + cnt + 1);
	for (int i = 1; i <= cnt; i ++) cout << ans[i] << " ";
	return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
数学题。
## 分析。
最暴力的方法是直接枚举 $n$ 次，显然超时。

由题意，当 $k=i$ 时与 $k=n-i$ 时答案是相同的，考虑缩小数据范围。这里简单说下原因，因为显然当 $k=i$ 时与 $k=n-i$ 时只不过是传到的人的顺序颠倒了。此时我们可以减少一半的循环，但是循环 $5\times10^8$ 仍然会超时。

但是我们通过对于这一特殊样例的分析，我们不难发现，传球的人的编号依次为 $1,1+k,1+k\times 2\ldots$ 的数列，即为后一项比前一项大 $k$ 的等差数列。

那就是说，我们只要找到 $k$ 就可以了。我们发现，当 $k\bmod n\neq 0$ 时，一定经过所有人且只经过一次。所以也就是说，只要取模后不为 $0$ 则一定与之前的答案有一样的，否则就是一个新的答案。

代码如下，仅供参考：
```
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
long long n;
long long ans,tot,a[1000005];
void init(int n2){
	for (int i=int(sqrt(n2));i>0;i--){
		if(!(n%i)){
			a[++tot]=i;
			a[++tot]=n2/i;
		}
	}
}
int main(){
	cin>>n;
	init(n);
	sort(a+1,a+tot+1);
	for (int i=tot;i>0;i--){
		if(a[i]==a[i+1]){
		    continue;
		}//去重。 
		ans=(1+(n+1-a[i]))*(n/a[i])/2;
		cout<<ans<<" ";
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Trimsteanima (赞：0)

题意：遍历长度为n的一个环，输出k从1到n的遍历的点的和的所有值。

n为质数时，答案只有1和n的m倍；k前后对称，可以想到通过枚举n的因数，得到k的最小值，惊讶的发现和是等比数列！

所以复杂度为$O(\sqrt{n})$
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
vector<ll> a;
inline ll Calc(ll x) {
    return 1ll*(n/x-1)*(n/x)/2*x+n/x;
}
int main()
{
　　 scanf("%I64d",&n);
    for (ll i=1;i*i<=n;i++)
        if (n%i==0) {
            a.push_back(Calc(i));
        a.push_back(Calc(n/i));
    }
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    for (int i=0;i<a.size();i++)
        printf("%I64d ",a[i]);
    return 0;
}
```

---

## 作者：little_sun (赞：0)

# 题解 CF1091C 【New Year and the Sphere Transmission】

这个C真烧脑qwq

可以发现每一次选的数的个数都是$n$的约数

枚举所有约数，计算答案即可（等差数列求和好评！）

```cpp
#include <bits/stdc++.h>
#define ll long long
std::vector<ll> v, ans;
void prime(ll n)
{
    for (int i = 1; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            v.push_back(i);
            if (i * i != n)
            {
                v.push_back(n / i);
            }
        }
    }
}
std::map<ll, int> m;
int main()
{
    ll n;
    scanf("%I64d", &n);
    prime(n);
    for (int i = 0; i < v.size(); i++)
    {
        m[v[i]] = 1;
    }
    for(std::map<ll, int>::iterator it = m.begin(); it != m.end(); it++)
    {
        ll x = n / it->first;
        ans.push_back((1 + (x * (it->first - 1) + 1)) * (it->first) / 2);
    }
    std::sort(ans.begin(), ans.end());
    for(int i = 0; i < ans.size(); i++)
        printf("%I64d\n", ans[i]);
    return 0;
}
```

---

## 作者：zsc2003 (赞：0)

### CF1091C 2018.12.30

#### 题目大意:

读入一个正整数$n$

接下来从小向大输出所有的答案(去重)

对于答案：

从$1$~$n$枚举$k$

每次从$1$开始顺时针跳$k$格，并把编号加起来

直到第二次到$1$为止

答案就是所有的编号和

#### 思路

用$O(\sqrt n)$的时间复杂度枚举$gcd$

因为每次跳k步的话

能够到的点为$1,1+k,1+2k,1+3k...$

所以是正确的

找到$k$后就可以通过数学计算$O(1)$的计算出答案

详细细节见代码

注意一定要开$long \ long$!!!

现场不少人因为$long \ long$被$hack$掉了...

下面附上代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()//读入优化
{
    int r,s=0,c;
    for(;!isdigit(c=getchar());s=c);
    for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
    return s^45?r:-r;
}
int n,tot;
ll sum,x;
ll f[1100000];//一定要开long long
int main()
{
    n=read();
    int t=sqrt(n);
    for(int i=1;i<=t;i++)
    {
        if(!(n%i))
        {
            x=n/i;
            sum=x*(x-1)*(ll)i;
            sum>>=1;
            sum+=x;
            f[++tot]=sum;
            if(i*i!=n)	
            {
                x=n/(n/i);
                sum=x*(x-1)*(ll)(n/i);
                sum>>=1;
                sum+=x;
                f[++tot]=sum;
                
            }
        }
    }
    sort(f+1,f+1+tot);
    for(int i=1;i<=tot;i++)	
        printf("%I64d ",f[i]);//codeforces输出long long要用%I64d
    return 0;
}
```

---

## 作者：fmj_123 (赞：0)

题目大意：
有$n$个人坐成一个环，其中第$i$人与第$i+1$人相邻（第$1$个人与第$n$个人相邻）。

现在编号为1的人的手上有一个球，他可以选择一个数$k$($1 \le k \le n$)。表示每次传给在他后面的第$k$个人。当球重新回到编号为$1$的人时游戏结束。

定义一次游戏的$fun$值为球传到的每个人的编号之和。请从小到大输出所有可能的$fun$值。

---
首先，我们看$n$的范围,$n \le 10^9$，显然模拟$n$次是不行的。我们要想办法优化。

- 优化方案 A

我们发现 ，$k=i$时与$k=n-i$时的$fun$值是相同的，所以我们可以缩成$n/2$次模拟，但对于这题来说，显然不够。

- 优化方案 B

请自行手玩$k=2$与$K=3$时的情况

通过手玩，我们可以发现，如果$k$ $mod$ $n$不为0时，答案一定为$1+2+3+...+n$。也就是说，当$k$是$n$的约数时，才会有新答案。

所以我们可以枚举约数，当$k$是$n$的约数时，我们才进行计算。通过这个方法，模拟次数大大减少。然而，还是会TLE。

- 优化方案 C

在B的基础上，我们再考虑从模拟下功夫优化。

我们可以发现，我们经过的点的编号是一个等差数列。利用小学学过的公式，我们就可以快速求和。至此，我们成功通过此题。

贴代码

```
#include<bits/stdc++.h>
using namespace std;
long long n,ys[1000000],num;
int main()
{
	cin>>n;
	for (int i=int(sqrt(n));i>0;i--)
	{
		if (!(n%i)) 
		{
		    ys[++num]=i;
			ys[++num]=n/i; 
		} 
	}//预处理约数
	sort(ys+1,ys+num+1);
	for (int i=num;i>0;i--)
	{
		if (ys[i]==ys[i+1]) continue;
		bool flag=true;long long ans=0;
		ans=(1+(n+1-ys[i]))*(n/ys[i])/2;//求出答案
		cout<<ans<<" ";
	}
	return 0;
}
```

---

