# Polycarp's problems

## 题目描述

Polycarp是一名资深Codehorces程序比赛参赛者。现在他想成为一位出题人。

他给协调者发去n个题目。每个题目都有它的品质，第i个问题的品质是ai(ai可以是正数，负数或0)。题目被设计成各种难度，但难度与其品质没有任何关系。

现在协调者的心情是q。在读完一个题目后，他的心情会随题目的品质而改变。也就是说当协调者读完一道品质为i的题目时，他的心情值要加上i。协调者总是从最简单的题目开始阅读，一直读到最难的题目，而想要改变这些题目的阅读顺序是不可能的。

如果协调者的心情达到了负数那么他会立刻停止阅读并且丢掉这些题。

现在Polycarp要从他的题目中移除题目以保证协调者的心情始终不会掉到负数同时移除的题目数最少。Polycarp不知道协调者现在的心情是多少，但他会猜测m次“协调者的初始心情为bi”。

对于每一个猜测，求出最少的移除题目数。

## 样例 #1

### 输入

```
6 3
8 -5 -4 1 -7 4
0 7 3
```

### 输出

```
2
0
1
```

# 题解

## 作者：TopCarry (赞：21)

**提供一篇贪心的题解**。

## 题意转化：

&emsp;&emsp;每次给定$a[0]$,求要删去几个数使得$a$的任意位置前缀和不为负数。

## Solution：

&emsp;&emsp;首先我们考虑前缀和的本质，就是一个个正数努力去抵消负数的过程，并且一个整数只能抵消下标在自己之后的负数。

&emsp;&emsp;我们再次思考，每个正数会去抵消哪些负数，**它一定会先消绝对值较小的**，因为最后我们不管手动删去负的多的还是负的少的，代价都是$1$。

&emsp;&emsp;那么我们只要从后往前扫一遍，用堆来使得每个正数按最优策略消去尽量多的负数，剩下的就是要留给$a[0]$来消去的。

&emsp;&emsp;然后我们对没消完的负数做个前缀和，每次二分查找$a[0]$能把剩下的抵消到哪里，剩下还是不能消去的就是我们要花代价手动消去的。

&emsp;&emsp;这样复杂度就是$O(nlogn+mlogn)$

&emsp;&emsp;当时写的时候没看见$n<=750$，就当成$n<=1e5$来做了。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define gc getchar()
inline ll read(){
	register ll x(0),f(1);register char c(gc);
	while(c>'9'||c<'0')f=c=='-'?-1:1,c=gc;
	while(c>='0'&&c<='9')x=x*10+c-48,c=gc;
	return f*x;
}
priority_queue<ll>q;
const int N=210000;
ll a[N],n,m,pre[N],cnt;
int main(){
	n=read();m=read();
	register int i;
	for(i=1;i<=n;i++)a[i]=read();
	for(i=n;i>=1;i--){
		if(a[i]<0){
			q.push(a[i]);
		}
		else{
			while(!q.empty()&&a[i]>=0){
				a[i]+=q.top();q.pop();
			}
			if(a[i]<0)q.push(a[i]);
		}
	}
	while(!q.empty()){
		pre[++cnt]=q.top();q.pop();
	}
	for(i=1;i<=cnt;i++)pre[i]=-pre[i]+pre[i-1];
	while(m--){
		ll x=read();
		cout<<(cnt-(upper_bound(pre+1,pre+1+cnt,x)-pre)+1)<<'\n';
	}
}
```


---

## 作者：Ynoi (赞：8)

如果只是一组询问，大家肯定能想到dp的做法

$f[i][j]$表示前$i$道题，保留$j$道后最大的心情值

那么$f[0][0]=q$,$f[i][j] = max(f[i-1][j-1]+a[i],f[i-1][j])$

但是这样是$n^2$的，再乘上询问次数$m$，肯定超时。而且在$q$值修改的时候也不好维护

怎么办？


## 正难则反

我们换一种dp方法

定义$f[i][j]$为在$i$~$n$中保留$j$道题，所需要的最小心情值

则$min(f[i+1][j],max(0,f[i+1][j-1]-a[i]))$

解释一下这个方程

$f[i][j]$有两种决策

第一种：第$i$道题目不取，需要的最小心情值不变$f[i][j] = f[i+1][j]$

第二中：第$i$道题目取，则需要最小心情值为$f[i][j] = f[i+1][j-1] - a[i]$,但又得保证心情值不低于$0$,所以要对0取max

最后我们在$f[1][x]$上枚举（或二分）就行了qwq

```
#include<bits/stdc++.h>
using namespace std;

#define MAXN 1005 
#define int long long
#define INF (int)0x3f3f3f3f*(int)0x3f3f3f3f

int n,m;
int a[MAXN];
int f[MAXN][MAXN];

void rd()
{
	cin >> n >> m;
	memset(f,0x3f,sizeof(f));
	f[n+1][0] = 0;
	for(int i = 1; i <= n; i ++)
		cin >> a[i];
	for(int i = n; i >= 1; i --)
	{
		for(int j = 1; j <= n-i+1; j ++)
			f[i][j] = min(f[i+1][j],max((int)0,f[i+1][j-1]-a[i]));
		f[i][0] = 0;
	}
}

signed main()
{
	rd();
	for(int i = 1; i <= m; i ++)
	{
		int b,ans = 0;
		cin >> b;
		for(int j = n; j >= 0; j --)
		{
			if(f[1][j] <= b) {
				cout<<n-j<<"\n";
				break;
			}
		}
	 } 
	return 0;
}
```

---

## 作者：Pengzt (赞：3)

> [CF727F](https://www.luogu.com.cn/problem/CF727F)

> [2023 做题记录](https://www.cnblogs.com/Pengzt/p/2023-hao-ti-ji-lu.html)

#### Problem

给定一个长为 $n$ 的数列 $a$。$m$ 次询问，每次给出 $a_0$ 的值，求至少删去多少个数使任意位置的前缀和 $\ge 0$。

$n\le 750,m\le 2\times 10^5,|a_i|\le 10^9,0\le b_i\le 10^{15}$

存在 $\mathcal{O}((n+m)\log n)$ 的做法。

#### Sol

虽然这道题的 dp 是比较显然的，贪心做法却比较妙。

先说 dp。如果只有一次询问的话，令 $f_{i}$ 表示使前 $i$ 个数满足条件的最小操作次数，但这样转移还需要查询区间最值，而且比较难以优化到多次查询。正难则反，考虑从后面 dp。但是要这个 dp 不能受到 $b$ 的影响，不妨设 $f_{i,j}$ 表示后 $i$ 个数，保留 $j$ 个的最小的 $s_k$。则有转移：$f_{i,j}=\min(f_{i+1,j},\max(0,f_{i+1,j-1}-a_i))$。

然后在 $f_{1,i}$ 上二分即可。时间复杂度：$\mathcal{O}(n^2+m\log n)$。没有 dp 的代码。

然后说一下贪心的做法。就是有一个贪心就是用一个正数去消多个负数，然后最后剩下的消不掉的就由 $a_0$ 去消，最后剩下的负数个数就是操作次数，这样显然是错的，就是在一个整数后面接一个极小（绝对值大）的负数，然后再接一个极大的正数，最后都是极大（绝对值小）的负数。

考虑怎么解决掉这个问题，发现是因为前面的决策后面就考虑不到了，所以就不能局部贪心了，所以倒过来就行了。然后用堆维护并在查询时二分即可做到 $\mathcal{O}((n+m)\log n)$。

#### Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 755;
int n, m;
ll a[N], tp, sum[N];
priority_queue <int> q;

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = n; i; i--) {
		if (a[i] < 0) q.push(a[i]);
		else {
			while (!q.empty() && a[i] >= 0) {
				a[i] += q.top();
				q.pop();
			}
			if (a[i] < 0) q.push(a[i]);
		}
	}
	while (!q.empty()) {
		sum[++tp] = -q.top();
		q.pop();
	}
	for (int i = 1; i <= tp; i++) sum[i] += sum[i - 1];
	while (m--) {
		ll x;
		scanf("%lld", &x);
		int res;
		if (x >= sum[tp]) res = 0;
		else res = tp - (upper_bound(sum + 1, sum + tp + 1, x) - sum) + 1;
		printf("%d\n", res);
	}
	return 0;
}
```


---

## 作者：xiazha (赞：3)

## 思路: DP
我们将 $f[i][j]$ 定义为在 $i\sim n$ 中保留 $j$ 道题，所需要的最小心情值，则动态转移方程就是： $\min(f[i+1][j],\max(0,f[i+1][j-1]-a[i])$

因为 $f[i][j]$ 要么不保留第 $i$ 道题，要么保留，

而前者就是继承上一步的最小心情值 $f[i+1][j]$,

后者则需要更新最小心情值，也就是上一步取 $j-1$ 个的最小心情值减去第 $i$ 道题的品质 $a[i]$，所以得到状态 $f[i+1][j-1]-a[i]$。但是与此同时我们还得要让最小心情值不小于 $0$，所以要对 $f[i+1][j-1]-a[i]$ 和 $0$ 取 $\max$。

最后，我们再从 $n\sim 0$ 枚举保留的题数，找到第一个大于等于 $b_i$ 的 $f[i][j]$，然后输出 $n-i$ 就行了。因为我们是从 $n\sim 0$ 进行枚举的，所以第一个符合要求的答案一定就是最少的移除题目数。

时间复杂度 $O(nm)$。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[757],f[757][757],x;
signed main()
{
	memset(f,0x3f,sizeof(f));
	cin>>n>>m;
	for(int i=1;i<=n+1;i++) f[i][0]=0;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=n;i>=1;i--)
		for(int j=1;j<=n-i+1;j++)
			f[i][j]=min(f[i+1][j],max((int)0,f[i+1][j-1]-a[i]));
	for(int i=1;i<=m;i++)
	{
		cin>>x;
		for(int j=n;j>=0;j--)
			if(f[1][j]<=x)
			{
				cout<<n-j<<"\n";
				break;
			}
	}
	return 0;
}
```

最后的最后，还有一个~~良心~~提示 ：不开 ```long long``` 见祖宗

---

## 作者：Swirl (赞：1)

[link](https://www.luogu.com.cn/problem/CF727F)。

贪心做法。

---

本题贪心做法的实质就是用整数尽量多地抵消该整数后面的负数。

如果正着做，没有办法考虑全该数后面的所有负数，所以倒着做。

例如当前遍历到了 $50$，此时序列如下：
$$
\dots,50,-50,-10,-20
$$
易得我们 $50$ 应该抵消的是 $-10,-20$，而不是前面的 $-50$，因为我们要使删除的数越少越好。

但是剩下的 $50 - 10 - 20 = 20$ 也不能空着，抵消一部分的剩下的 $-50$ 即可。

最终得到：
$$
\dots, -30
$$
发现上述操作可以用堆来维护，具体维护方法见代码。

---

- 时间复杂度：$\mathcal O ((n + m) \log  n)$，瓶颈在于堆和二分。
- 空间复杂度：略。

---

代码：

```cpp
// 加强版：n,m <= 1000000 代码
#include <bits/stdc++.h>
#define int long long
#define pii pair<int, int>
using namespace std;

const int N = 1e6 + 5;

int n, m, a[N], b[N], tot;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	priority_queue<int> q;
	for (int i = n; i >= 1; i--) {
		if (a[i] < 0) {
			q.push(a[i]);
		} else {
			while (q.size() && a[i] >= 0) {
				a[i] += q.top();
				q.pop();
			}
			if (a[i] < 0) {
				q.push(a[i]);
			}
		}
	}
	while (q.size()) {
		b[++tot] = -q.top();
		q.pop();
	}
	for (int i = 1; i <= tot; i++) {
		b[i] += b[i - 1];
	}
	for (int i = 1; i <= m; i++) {
		int x;
		cin >> x;
		if (x >= b[tot]) {
			cout << "0\n";
			continue;
		}
		int t = upper_bound(b + 1, b + tot, x) - b - 1;
		cout << tot - t << "\n";
	}
	return 0;
}
```

---

## 作者：一扶苏一 (赞：1)

## Analysis

设 $f(i,j)$ 表示第 $i \sim n$ 道题，丢掉了 $j$ 道时，在第 $i$ 道前所需要的最小初始心情。

枚举第 $i$ 道题留或不留，从 $f(i + 1,j - 1)$ 和 $f(i + 1, j)$ 转移：

$$f(i,j) = \min\{f(i + 1, j - 1), \max\{0, f(i + 1, j) - a_i\}\}$$

对第二项转移的解释：如果保留第 $i$ 题，假设 $a_i < 0$，那么初始心情要加上 $-a_i$ 才能在看第 $i + 1$ 题前达到所需的最小心情 $f(i + 1, j)$；假设 $a_i \geq 0$，那么看过第 $i$ 题心情会增加 $a_i$，则看 $a_i$ 前需求的心情自然减小了 $a_i$。综合起来就是 $f(i + 1, j) - a_i$。

注意任何时刻心情必须非负，所以所需最小心情为负是没有意义的，简单来说，假如不取 max，$f$ 值为 $0$ 的状态不该从 $f$ 值为 $-2$ 的状态转移。因为如果走这个转移，说明看完第 $i$ 道题后心情达到了 $-2$，是不合法的。

显然 $f(i, \cdot )$ 是单调的。所以对每组询问，二分出最小 $j$ 使得 $f(1, j) \leq b_i$ 即可。但事实上每次暴力 $O(n)$ 找 $j$ 也能过。

## Code

```cpp
#include <iostream>
#include <algorithm>

const int maxn = 800;
const int maxm = 200005;

int n, q;
int a[maxn];
long long f[maxn][maxn];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> q;
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  f[n][0] = std::max(0, -a[n]);
  f[n][1] = 0;
  for (int i = n - 1; i; --i) {
    for (int j = 1; j <= n - i + 1; ++j) {
      f[i][j] = std::min(f[i + 1][j - 1], std::max(0ll, f[i + 1][j] - a[i]));
    }
    f[i][0] = std::max(0ll, f[i + 1][0] - a[i]);
  }

  for (long long x; q; --q) {
    std::cin >> x;
    for (int i = 0; i <= n; ++i) if (f[1][i] <= x) {
      std::cout << i << '\n';
      break;
    }
  }
}
```

---

## 作者：lkjzyd20 (赞：0)

### 题意

给定一个长为 $n$ 的数列 $a$。$m$ 次询问，每次给出 $a_0$ 的值，求至少删去多少个数使任意位置的前缀和不为负数。

### 思路

设 $f_{i,j}$表示前 $i$ 个数，保留 $j$ 个数后的最大数。

则可得

$$
 f_{i,j} = \min(f_{i + 1,j}, \max(0,f_{i+1,j-1}-a_i))
$$

$f_{i,j}$ 有两种选择

+ 选择第 $i$ 个数不取，则
   $$f_{i,j} = f_{i+1,j}$$
+ 选择第 $i$ 个数取，则
   $$f_{i,j} = f_{i+1,j-1}-a_i$$
但我们还得要让前缀和不为负数，所以要对 $0$ 取 $\max$。

最后，我们再倒序枚举 $f_{1,x}$， 然后输出 $n-i$ 即可。

### 代码如下

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define rep(i, l, r) for(int i = l; i <= r; ++ i)
#define per(i, r, l) for(int i = r; i >= l; -- i)
const int N = 200010, M = 2010;
int a[N];
int f[M][M];
int n, m, x;
main() 
{
    scanf("%lld%lld", &n, &m);
    rep(i, 1, n) scanf("%lld", &a[i]);
	memset(f, 0x3f, sizeof f);
	f[n + 1][0] = 0;
    per(i, n, 1) 
    {   
        rep(j, 1, n - i + 1)
		    f[i][j] = min(f[i + 1][j], max(0ll, f[i + 1][j - 1] - a[i]));
		f[i][0] = 0;
    }
	for(; m; -- m)
    {
        scanf("%lld", &x);
        per(j, n, 0)
			if(f[1][j] <= x) 
            {
                printf("%lld\n", n - j);
				break;
			}
	}
}
```

---

## 作者：1234567890sjx (赞：0)

这种题目显然是贪心。

首先~~种上几个太阳~~不删除数字，如果到一个时候是负数，那么就一直删除当前最小的数字直到当前位置的和变成非负数为止。

直接用 `multiset` 贪心，时间复杂度是 $O(mn\log n)$ 的，卡卡常之后不知道能不能过。

所以这里介绍一种一定能卡过去的算法。

容易发现，对于 $i$ 位置的正数 $a_i$ 和 $j$ 位置的负数 $a_j$，如果 $i<j$，那么 $a_i$ 可以抵消（消掉）$a_j$，如果 $i>j$ 则不能。

考虑把所有的数倒着插入。

如果 $a_i>0$，那么就把在她后面（就是已经枚举到且没有被消去的数）抵消或者消掉。如果 $a_i=0$ 那么跳过不管，如果 $a_i<0$ 那么就等待被消掉。

到最后如果剩下的数都是正数那么就不需要移除任何题目。

否则对于每一个初始的心态 $q$，先把她看作是最前面的正数然后做一遍处理，如果剩下了正数或者什么也没有剩下那么就不需要移除任何题目，否则剩下的就得移除掉题目。

鉴于 $n$ 很小，所以对于每一个初始的心态 $q$ 直接暴力枚举得到 $q$ 最多可以抵消多少个多少个一开始无法抵消掉的负数即可。

应该用正数抵消哪一些负数？由于手动删除负数和负数的大小无关，只和负数的数量有关，所以一定是选取更大的负数（绝对值更小的负数）和正数进行抵消。

时间复杂度是 $O(nm)$ 的，应该很好跑。

upd：查看了第一篇题解之后发现询问是可以二分的，但是反正直接枚举也是能过的，所以就不改了。

---

## 作者：hzoi_liuchang (赞：0)

## 分析

暴力的做法是从前往后扫，遇到不合法的时候就从前面找一个最小的减掉

正解需要倒着考虑

维护一个 $multiset$

如果遇到一个负数直接扔到 $multiset$ 里

如果遇到一个正数，那么我们肯定想让它抵消掉尽可能多的负数，直到它变成零

最后把剩下的负数做一个前缀和，二分查找即可

## 代码

```c++
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<set>
#define rg register
const int maxn=1e6+5;
int n,m,a[maxn],cnt,tp;
long long beg,sum[maxn];
std::multiset<int> s;
#define sit std::multiset<int>::iterator
int main(){
	scanf("%d%d",&n,&m);
	for(rg int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(rg int i=n;i>=1;i--){
        if(a[i]<0) s.insert(-a[i]);
        else {
            while(!s.empty()){
                rg int tmp=*s.begin();
                s.erase(s.begin());
                if(a[i]>=tmp) a[i]-=tmp;
                else {
                    s.insert(tmp-a[i]);
                    break;
                }
            }
        }
    }
    for(rg sit it=s.begin();it!=s.end();++it) sum[++tp]=*it;
    for(rg int i=1;i<=tp;i++) sum[i]+=sum[i-1];
	for(rg int i=1;i<=m;i++){
		scanf("%lld",&beg);
        if(beg>=sum[tp]) cnt=0;
        else cnt=tp-(std::upper_bound(sum+1,sum+1+tp,beg)-sum)+1;
		printf("%d\n",cnt);
	}
	return 0;
}
```


---

