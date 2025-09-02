# [USACO23DEC] Candy Cane Feast B

## 题目描述

Farmer John 的奶牛对甜食情有独钟，它们尤其喜欢吃糖果棒。FJ 共有 $N$ 头奶牛，每头奶牛都有一个特定的初始高度。他想要喂它们 $M$ 根糖果棒，每根糖果棒的高度也各不相同（$1 \le N,M \le 2\cdot 10^5$）。

FJ 计划按照输入给出的顺序，逐一喂给奶牛们糖果棒。然后，奶牛们会按照输入给出的顺序一个接一个地排队，走向糖果棒，每头奶牛最多吃到与它高度相同的部分（因为它们够不到更高的地方）。即使奶牛吃掉了糖果棒的底部，糖果棒也在最初悬挂的地方保持不动，并不会被降低到地面。如果糖果棒的底部已经高于某头奶牛的高度，那么这头奶牛在它的回合中可能什么也吃不到。每头奶牛轮流吃过后，它们的身高会增加它们吃掉的糖果棒的单位数量，然后农夫约翰挂上下一根糖果棒，奶牛们再次重复这个过程（第一头奶牛再次成为第一个开始吃下一根糖果棒的）。

## 说明/提示

### 样例解释 1

第一根糖果棒高度为 $6$ 单位。

- 第一头奶牛吃掉了第一根糖果棒直至高度 $3$ 的部分，之后第一根糖果棒剩余高度 $[3,6]$ 的部分。
- 第二头奶牛不够高，无法吃掉第一根糖果棒的任何剩余部分。
- 第三头奶牛额外吃掉了第一根糖果棒的两个单位。第一根糖果棒的剩余高度 $[5,6]$ 的部分未被吃掉。

接下来，每头奶牛根据它吃掉的数量增长，所以奶牛的高度变为 $[3+3, 2+0, 5+2]=[6, 2, 7]$。

第二根糖果棒高度为 $1$ 单位，被第一头奶牛全部吃掉。

### 测试点性质

- 测试点 $2-10$ 满足 $N,M \le 10^3$。
- 测试点 $11-14$ 没有额外限制。


## 样例 #1

### 输入

```
3 2
3 2 5
6 1```

### 输出

```
7
2
7```

# 题解

## 作者：Expert_Dream (赞：9)

[博客园](https://www.cnblogs.com/gsczl71/p/17909469.html)。

首先我们知道，对于 $a_1$ 每一次是最先吃糖果的。所以必然有两个情况：
- 全部给他吃了。
- 吃了一些。

首先情况一，我们可以直接特判掉。

剩下情况二，吃了一些没吃完代表：**吃了自己的高度**，相当于身高 $\times 2$。于是我们只需要进行 $\log 10^9$ 次。然后后面直接 $O(n)$ 暴力。时间复杂度 $O(n \log 10^9)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
#define int long long
int n,m;
int a[N],b[N];
void solve(){
	cin >> n >> m;
	for(int i = 1;i <= n;i++)
		cin >> a[i];
	for(int i = 1;i <= m;i++)
		cin >> b[i];
	
	
	for(int i = 1;i <= m;i++){
		if(b[i] <= a[1]){
			a[1]+=b[i];
			continue;
		} 
		int tmp = 1;
		for(int j = 1;j <= n;j++)
			if(a[j] >= tmp && tmp <= b[i]){
				int t=a[j]+1;
				a[j] += min(a[j]-tmp+1,b[i]-tmp+1);
				tmp = t;
			}
	}
	
	for(int i = 1;i <= n;i++)
		cout<<a[i]<<endl;
	
}

signed main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	solve();
	return 0;
}

```

---

## 作者：xiaoshumiao (赞：6)

$\text{Update on 2023.12.27}$：补充了复杂度证明。

[题目传送门](https://www.luogu.com.cn/problem/P9974)

## 前言

第一次打 USACO，发篇题解纪念一下吧。

当然如果你看得懂英文的话你也可以看[官方题解](http://www.usaco.org/current/data/sol_prob1_bronze_dec23.html)，可能写的更清楚。

## 分析

这是一道标准的模拟。

我们记录每个糖果棒的下端位置 $s_i$ 和上端位置 $e_i$。初始时所有的 $s_i$ 都为 $0$。

当每一头奶牛走向糖果棒时，如果 $a_i<s_i$，则该奶牛吃不到糖果棒。跳过。

否则，分情况讨论：

- 如果它没有吃完糖果棒，也就是 $a_i<e_i$，则它会长 $a_i-s_i$ 个单位高度，同时把 $s_i$ 更新为 $a_i$。

- 否则，它吃完了糖果棒，即 $a_i \ge s_i$，则它会长 $e_i-s_i$ 个单位高度，同时把 $s_i$ 更新为 $e_i$。

基于上述讲解，我们可以得到以下代码：
```cpp
#include<cstdio>
using namespace std;
const int MAXN=200005,MAXM=200005;
long long a[MAXN];
struct Candy {
  int s,e;
}b[MAXM];
int main() {
  int n,m;
  scanf("%d %d",&n,&m);
  for(int i=1;i<=n;i++)
    scanf("%lld",&a[i]);
  for(int i=1;i<=m;i++) {
  	scanf("%d",&b[i].e);
  	b[i].s=0;
  }
  for(int i=1;i<=m;i++) {
  	for(int j=1;j<=n;j++) {
  	  if(a[j]>b[i].s&&b[i].s!=b[i].e) {//注意，这里要判断一根糖果棒有没有被吃完。
  	  	int t=b[i].s;
  	  	if(a[j]>b[i].e) {
  	  	  b[i].s=b[i].e;
  	  	  a[j]+=b[i].e-t;
  	  	}
  	  	else {
  	  	  b[i].s=a[j];
		  a[j]+=a[j]-t;
  	  	}
  	  }
  	}
  }
  for(int i=1;i<=n;i++)
    printf("%lld\n",a[i]);
  return 0;
}
```
此代码的时间复杂度为 $\Theta(n \times m)$，[无法通过](https://www.luogu.com.cn/record/140880013) $1 \le n,m \le 2 \times 10^5$ 的数据。

一个简单但又很有效果的优化是：当一根糖果棒被吃完时，我们就可以 `break`，没必要再做下去了。

这样为什么是对的呢？应为对于一根糖果棒，它有以下两种状况：

1. 全被 $1$ 号牛吃了。

2. 没有全被 $1$ 号牛吃完。

每出现一次二号情况，$1$ 号牛的身高就会翻一倍。而糖果最高也只有 $10^9$，所以最多出现 $\log 10^9=30$ 次二号情况后就全是一号情况了。而一号情况的复杂度是 $\Theta(1)$ 的，所以这个复杂度是对的。

代码如下：
```cpp
#include<cstdio>
using namespace std;
const int MAXN=200005,MAXM=200005;
long long a[MAXN];
struct Candy {
  int s,e;
}b[MAXM];
int main() {
  int n,m;
  scanf("%d %d",&n,&m);
  for(int i=1;i<=n;i++)
    scanf("%lld",&a[i]);
  for(int i=1;i<=m;i++) {
  	scanf("%d",&b[i].e);
  	b[i].s=0;
  }
  for(int i=1;i<=m;i++) {
  	for(int j=1;j<=n;j++) {
  	  if(b[i].s==b[i].e)//如果一根糖果棒已经被吃完，我们可以提前 break。
  	    break;
  	  if(a[j]>b[i].s) {
  	  	int t=b[i].s;
  	  	if(a[j]>b[i].e) {
  	  	  b[i].s=b[i].e;
  	  	  a[j]+=b[i].e-t;
  	  	}
  	  	else {
  	  	  b[i].s=a[j];
		  a[j]+=a[j]-t;
  	  	}
  	  }
  	}
  }
  for(int i=1;i<=n;i++)
    printf("%lld\n",a[i]);
  return 0;
}
```
然后，就可以愉快的 [AC](https://www.luogu.com.cn/record/140881031) 啦！

---

## 作者：Loser_Syx (赞：5)

过来证个结论。

以奶牛 $a_1$ 为例，由于每个糖果对他来说永远都是第一个吃到的，所以对于 $a_1$ 只有两个选择：

- 一口吃完，后面的牛不参与吃糖，复杂度 $O(1)$。
- 没有一口吃完，留给后面的牛吃一点，复杂度 $O(n)$。

发现每触发一次选择二 $a_1 = a_1 \times 2$，而糖最长只有 $10^9$ 且 $a_i \geq 1$，故保证了一定次数内（$\leq \log 10^9$）的选择二后奶牛 $a_1$ 选择的一定只会是选择一。

故暴力有正确性，代码易得。

---

## 作者：_sh1kong_ (赞：4)

[In Luogu](https://www.luogu.com.cn/problem/P9974)

很简单的一道题，赛时 $5$ 分钟过了，但是看不懂大家的做法，来贡献一篇题解。

### Solution
对于每一根糖，用变量 $last$ 来记录当前吃到最高的高度，然后对于每一头奶牛，更新高度及 $last$ 即可。$\mathcal{O}(nm)$，显然需要优化。

那么如何优化呢？很容易想到当这根糖已经被吃完后，后面的奶牛就不需要吃了，此时退出循环即可。

是的，加上这个小优化后，问题便得到了解决。

[这个](https://www.luogu.com.cn/record/list?pid=P9974&orderBy=1&status=&page=1)做法甚至跑的很快。

```cpp
void solve()
{	
	n = re, m = re;
	for (int i = 1; i <= n; i ++ ) cow[i] = re;
	for (int i = 1; i <= m; i ++ ) candy[i] = re;
	for (int i = 1; i <= m; i ++ )
	{
		int last = 0;
		for (int j = 1; j <= n; j ++ )
		{
			if (cow[j] >= candy[i]) {cow[j] += candy[i] - last;break;}//优化
			if (cow[j] >= last) 
			{
				int t = cow[j];
				cow[j] += (cow[j] - last), last = t; //暴力更新
			}
		}
	} 
	for (int i = 1; i <= n; i ++ ) cout << cow[i] << '\n';
}
```

---

## 作者：wanglexi (赞：2)

题目传送门：[link](https://www.luogu.com.cn/problem/P9974)。

第一眼看题目，没思路。

多看一眼题目，没思路。

没思路就先打暴力。

### 【解法】

枚举 $M$ 糖果棒，让 $N$ 头奶牛分别去吃，并记录糖果棒**被吃的部分的最高处**，并把吃掉的数量加到奶牛的高度上。

写出代码提交：通过了！

乍一眼，这个思路最坏的时间复杂度是 $O(nm)$。怎么能通过 $N,M$ 最大是 $2\cdot10^5$ 的点？

其实，每根糖果棒可以按第一头牛吃它的情况分成两种情况：

1. 第一头牛没吃光这根糖果棒，那么第一头牛吃的是和自己高度相同的部分，它的高度翻倍了。这种情况的糖果棒最多有 $\log 2^{64}=64$ 个，每根这种情况的糖果棒最多要让 $n$ 头牛来吃。
2. 第一头牛吃光了这根糖果棒。这种情况的糖果棒最多有 $m$ 根，每根这种情况的糖果棒只会让 $1$ 头牛来吃。

综合起来，这种思路的时间复杂度其实是 $O(n\log h+m)$，其中 $h$ 表示奶牛的最终高度的上限。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m;
ll a[200005],b;//a:奶牛的高度 b:糖果棒的高度
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	while(m--){
		cin>>b;
		ll j=0;//j:这根糖果棍被吃的部分的最高处
		for(ll i=1;i<=n&&j<b;i++){//没到最后一头牛而且没吃完
			ll nai=a[i]+max(min(a[i]-j,b-j),0ll),nj=max(j,a[i]);
			//因为算新的a[i]和j需要用到旧的对方，所以需要先记录，再覆盖
			//a[i]-j:奶牛比糖果棍被吃的部分的最高处高的高度
			//b-j:糖果棍剩余的高度
			//min(a[i]-j,b-j):奶牛能吃的部分
			//max(min(a[i]-j,b-j),0ll):实际上吃的部分，避免吃空气
			a[i]=nai,j=nj;
		}
	}
	for(int i=1;i<=n;i++)cout<<a[i]<<"\n"; 
	return 0;
}
```

---

## 作者：rnf5114 (赞：0)

这一题的难点主要在于分析暴力代码时间复杂度的正确性。

首先根据题意描述可知,如果某一头奶牛吃了甘蔗糖，那么在它之后只要身高不高于它的奶牛是永远也吃不到甘蔗糖了，所以我们这里可以使用链表来维护所剩奶牛的编号。

下面我们来看中间的模拟操作，面对第 $ i $ 颗甘蔗糖，会出现一下三种情况：

1. 这头奶牛吃光了这颗甘蔗糖。

2. 这头奶牛吃了自己身高的长度的甘蔗糖。

3. 这头奶牛吃不到甘蔗糖。

对于第三种可能，上面已经讨论过了应该做什么操作。对于第一种可能，那么我们可以直接把下一根甘蔗糖换上来了，同时更新当前的奶牛身高。对于第二种可能，那么我们要更新奶牛高度和甘蔗糖的底部高度。

# 随后就是重点

容易发现，如果当前奶牛的高度可以吃完整根甘蔗，那么循环次数就会大大减少，所以我们只需要证明使奶牛的高度变得比所有甘蔗糖高并不需要很多次运行即可。

容易发现，当一头奶牛吃了某颗甘蔗后，它的身高之多会乘以 $ 2 $，所以大致就可以估算出其实只需要大约只需 $\log X$ 次即可得到我们想要的一头极高的奶牛。（$ X $ 定义为最高的甘蔗糖高度）

代码就省略了，毕竟只是个纯模拟题。

---

## 作者：Adchory (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9974)。

## 思路

首先考虑暴力怎么做。

假设第 $i$ 头奶牛的高度为 $a_i$，第 $i$ 个糖果的长度为 $b_i$。

现在准备吃糖果（其高度为 $S$）的奶牛为 $i$，上一次吃到糖果的奶牛为 $lst$，这只奶牛能吃到糖果当且仅当 $i>lst$，它能吃到的糖果长度为 $\min(a_i-a_{lst},S-a_{lst})$，这样做是 $O(nm)$ 的。

我们只需加入一个优化，假如上次奶牛已经把糖果都吃完了，那么之后的奶牛一定不能吃到糖果，可以直接 `break` 掉。

由于奶牛的高度是指数级增长的，所以时间复杂度为 $O(n\log V)$，$V$ 是 $a_i$ 值域。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll Maxn=2e5+7;
ll n,m,a[Maxn],b[Maxn],c[Maxn],cnt,maxx; 

int main(){
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(ll i=1;i<=m;i++) scanf("%lld",&b[i]);
	
	for(ll i=1;i<=m;i++){
		ll S=b[i];
		ll lst=0;
		for(ll j=1;j<=n;j++){
			if(a[j]>=S){
				a[j]+=max(0ll,S-lst);
				break;
			}
			if(S>=a[j]&&a[j]>lst){
				ll x=(a[j]-lst);
				lst=a[j];
				a[j]+=x;
			}
			
		}
	}
	for(ll i=1;i<=n;i++) printf("%lld\n",a[i]);
	
	return 0;
}
```


---

## 作者：Night_sea_64 (赞：0)

暴力很好打，不说了，贴个代码：

```cpp
#include<iostream>
using namespace std;
int n,m;
long long a[200010];
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=m;i++)
    {
        int x,down=0;
        cin>>x;
        for(int j=1;j<=n;j++)
        {
            int k=max(0ll,min(a[j],(long long)x)-down);
            down+=k,a[j]+=k;
        }
    }
    for(int i=1;i<=n;i++)cout<<a[i]<<endl;
    return 0;
}
```

但是就这么简单的暴力能对 10 个点。

接下来可以造几组小数据分析一下，发现 1 号牛非常关键，它很容易就吃到糖了。而且如果它吃成了最高的，那么接下来后面的牛都没得吃了。所以我们针对 1 号牛的状态来分析一下。

每颗糖可以分成两类：

1. 1 号牛吃完别人还能吃。
2. 1 号牛吃完别人就没份了。

对于 2 号情况，复杂度是 $O(1)$ 的。而对于 1 号情况，1 号牛的身高一定变成了原来的 2 倍。这个 2 倍的增长十分快，1 号牛只要翻 30 次就能比 $10^9$，也就是糖的最大高度还高了。达到这种情况后接下来就一定是 2 号情况。

所以 1 号情况最多只有 30 次。对于这些情况我们暴力枚举也不会超时。总时间复杂度为 $O(n\log w)$，其中 $w$ 为糖果高度。

怎么写呢？只需要在糖吃完后及时跳出就行了。只需在暴力上加一行：

```cpp
if(down==x)break;
```

完整代码：

```cpp
#include<iostream>
using namespace std;
int n,m;
long long a[200010];
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=m;i++)
    {
        int x,down=0;
        cin>>x;
        for(int j=1;j<=n;j++)
        {
            int k=max(0ll,min(a[j],(long long)x)-down);
            down+=k,a[j]+=k;
            if(down==x)break;
        }
    }
    for(int i=1;i<=n;i++)cout<<a[i]<<endl;
    return 0;
}
```

---

## 作者：strcmp (赞：0)

赛时差点没秒。

------------

假设我们只关心 $a_1$ 的增长。

我们发现，每次要么 $b_i \le a_1$，此时 $a_1 \leftarrow a_1 + b_i$，之后 $b_i$ 不会产生贡献。

要么 $b_i > a_1$，此时 $a_1$ 倍增，$b_i$ 会在后面产生贡献。

什么意思呢，$b_i > a_1$ 时我们暴力算贡献的次数不会超过 $\Theta(\log v)$ 次，$v$ 为值域，本题为 $10^9$。

那么每次 $b_i \le a_1$ 直接计算对 $a_1$ 的贡献退出，否则暴力算贡献即可。

时间复杂度 $\Theta(n \log v)$，可以通过。

赛时转了一个差分才看出来，还维护了 $a$ 的单调性，代码凑合着看吧。

```cpp
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long int ll;
using pll = pair<int, ll>;
const int maxn = 4e5 + 10;
const ll mod = 998244353LL;
const ll inf = 1145141919810LL;
int n, m; ll a[maxn], b[maxn], c[maxn], d[maxn];
pll f[maxn], g[maxn]; ll ans[maxn]; int N = 0;
inline void del() {
	ll mx = 0; int p = 0;
	for (int i = 1; i <= n; i++) {
		if (f[i].y > mx) g[++p] = f[i];
		mx = max(mx, f[i].y);
	}
	for (int i = 1; i <= p; i++) f[i] = g[i]; n = p;
}
int main() {
	scanf("%d%d", &n, &m); N = n;
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]), f[i].x = i, f[i].y = a[i], ans[i] = a[i];
	for (int i = 1; i <= m; i++) scanf("%lld", &b[i]);
	for (int o = 1; o <= m; o++) {
		ll w = b[o], now = 0;
		if (w <= f[1].y) { ans[f[1].x] += w; f[1].y += w; continue; } del();
		for (int i = 1; i <= n; i++) {
			if (f[i].y < now) continue;
			ll k = min(f[i].y - now, w - now);
			f[i].y += k; ans[f[i].x] += k; now += k;
			if (now > w) break;
		}
	}
	for (int i = 1; i <= N; i++) printf("%lld\n", ans[i]);
	return 0;
}
```

---

