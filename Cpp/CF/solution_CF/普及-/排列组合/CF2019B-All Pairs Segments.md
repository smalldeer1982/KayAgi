# All Pairs Segments

## 题目描述

你有 $ n $ 个点，这些点位于 $ x $ 轴上，坐标为递增的正整数，分别为 $ x_1 < x_2 < \ldots < x_n $。

对于每对点 $ (i, j) $，其中 $ 1 \leq i < j \leq n $，你将绘制线段 $ [x_i, x_j] $。这些线段是闭合的，即线段 $ [a, b] $ 包含点 $ a, a+1, \ldots, b $。

你有 $ q $ 个查询。在第 $ i $ 个查询中，给定一个正整数 $ k_i $，你需要确定恰好被 $ k_i $ 条线段包含的整点有多少个。

## 样例 #1

### 输入

```
3
2 2
101 200
2 1
6 15
1 2 3 5 6 7
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
5 8
254618033 265675151 461318786 557391198 848083778
6 9 15 10 6 9 4 4294967300```

### 输出

```
0 100 
0 0 0 0 2 0 0 0 3 0 2 0 0 0 0 
291716045 0 0 0 291716045 0 301749698 0```

# 题解

## 作者：SpringFullGarden (赞：7)

## 题意

在数轴上有 $n$ 个点，每两个点形成一个线段。

每次查询，有有几个点恰好被 $k$ 个线段覆盖。

## 思路

观察下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/mo69qjv6.png)

可以发现，以第 $i$ 个点为左端点的线段有 $n - i$ 条，覆盖第 $i$ 个点且不以第 $i$ 个点位左端点的线段有 $(n - i + 1)(i - 1)$ 条（$i$ 左边有 $i - 1$ 个点，每个点能覆盖到第 $i$ 个点的线段有 $n - i + 1$ 条）。

整理得，覆盖了第 $i$ 个点的线段有 $i\cdot (n - i + 1) - 1$ 条。

再考虑点不是给定的点。对于一个点，设它右边的第一个给定点是第 $i$ 个点。发现除了以第 $i$ 个点为左端点的线段以外，覆盖了第 $i$ 个点的线段都覆盖了这个点。所以覆盖了这个点的线段有 $(n - i + 1)(i - 1)$ 条。

枚举 $i(1 \le i \le n)$，算出有几条线段覆盖了第 $i$ 个点。

再枚举 $i(1 < i \le n)$，算出它与前一个点之间的点被几条线段覆盖。

## 代码

```cpp
ll a[200005], b[200005];
map <ll, ll> c;

signed main() {
	for(ll T = rd(); T--; ) {
		ll n = rd(), Q = rd();
		for(ll i = 1; i <= n; i++) a[i] = rd();
		c.clear();
		for(ll i = 1; i <= n; i++) b[i] = (n - i + 1) * i - 1, c[b[i]]++;
		for(ll i = 2; i <= n; i++)
			c[b[i] - (n - i)] += a[i] - a[i - 1] - 1;
		while(Q--) {
			ll x = rd();
			cout << c[x] << ' ';
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：zhangmuning1016 (赞：4)

# [题目传送门](https://www.luogu.com.cn/problem/CF2019B)
# 题意

在数轴上有 $n$ 个点，由小到大给定其坐标 $x_i$，其中 $1\le i\le n$，每个点向其后面的所有点连线。

有 $q$ 次询问，每次输入 $k$，问被 $k$ 条线段覆盖的点有多少个。

# 思路

我们考虑分别计算每个点被多少条线段覆盖，再用 [map](http://oiwiki.com/lang/csl/associative-container/#map) 统计被 $k$ 条线段覆盖的点的个数即可。
对于编号为 $i$ 的点：  
- 当其为线段左端点时，可以连出 $(n−i)$ 条线段，因为它后面有 $(n−i)$ 个点。
- 当其为线段右端点时，可以连出 $(i−1)$ 条线段，因为它前面有 $(i−1)$ 个点。
- 当其在线段中时，可以被 $(i−1)\times (n−i)$ 条线段覆盖，因为它前面的 $(i−1)$ 个点可以向后面的 $(n−i)$ 个点连线。

所以对于编号为 $i$ 的点，共可以被 $(n−i)+(i−1)+(i−1)\times (n−i)$ 条线段覆盖。

由于 $1\le k\le 10^{18}$，所以要开 long long。

---

## 作者：Anins (赞：2)

## [All Pairs Segments](https://www.luogu.com.cn/problem/CF2019B)

### 题意：

在数轴上有 $n$ 个点，由小到大给定其坐标 $x_i$，其中 $i \in [1,n]$，每个点向其后面的所有点连线。

有 $q$ 次询问，每次输入 $k$，问被 $k$ 条线段覆盖的点有多少个。

多组测试数据。

### 思路：

我们考虑分别计算每个点被多少条线段覆盖，再通过 map 统计被 $k$ 条线段覆盖的点的个数即可。

#### 对于编号为 $i$ 的点：
- 当其为线段左端点时，可以连出 $(n-i)$ 条线段，因为它后面有 $(n-i)$ 个点。
- 当其为线段右端点时，可以连出 $(i-1)$ 条线段，因为它前面有 $(i-1)$ 个点。
- 当其在线段中时，可以被 $(i-1) \times (n-i)$ 条线段覆盖，因为它前面的 $(i-1)$ 个点可以向后面的 $(n-i)$ 个点连线。

所以对于编号为 $i$ 的点，共可以被 $(n-i)+(i-1)+(i-1) \times (n-i)$ 条线段覆盖。

#### 对于编号 $i$ 与编号 $i+1$ 之间的点：

它们只能在线段中，可以被 $(i-1) \times (n-i)$ 条线段覆盖。


---


时间复杂度为 $O(\sum n)$，可以通过本题。

### 注意：

由于 $1 \le k \le 10^{18}$，所以要开 long long。

### 代码


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll T, n, q, k;
ll x[100005];
map<ll, ll> m;
signed main() {
	cin >> T;
	while(T--) {
		m.clear();
		cin >> n >> q;
		for(int i=1; i<=n; i++) cin >> x[i];
		for(int i=1; i<=n; i++) {
			m[(n-i)+(i-1)+(i-1)*(n-i)]++; //统计点i答案 
			if(i+1<=n) m[i*(n-i)]+=(x[i+1]-x[i]-1); //统计i与i+1之间答案 
		}
		for(int i=1; i<=q; i++) {
			cin >> k;
			cout << m[k] << " ";
		}
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：Oracynx (赞：1)

## [CF2019B] All Pairs Segments 题解

### 思路分析

翻译后的题意已经很清晰了，不在赘述。

参考下面的图，按照图中的线的颜色进行分组。

![](https://cdn.luogu.com.cn/upload/image_hosting/4wgj0rqx.png)

对于深蓝色线标记的覆盖贡献，显然其的被覆盖的数量为这个点之前的点的数量乘上这个点的编号加上这个点后面的点的个数。

~~上面那么一大段话我也没看懂，所以下面再用公式写一遍。~~

即当前是第 $i$ 个点，显然，其被覆盖的数量为：

$$
(i - 1) \times (n - i + 1) + (n - i)
$$

接着，对于紫色圈出的点的覆盖次数，其为左端点右侧的点的数量乘上左端点的编号。

同样的，给出公式写法，对于介于 $i \sim i + 1$ 之间的区间，其的覆盖次数为：

$$
(n - i) \times i
$$

然后，我就就可以顺理成章地写出代码来了。

### 代码实现

```cpp
#include <cstdio>
#include <map>
constexpr int MaxN = 2e5 + 5;
int n, q;
int p[MaxN];
std::map<long long, int> map;
void solve()
{
    map.clear();
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        map[1ll * (n - i + 1) * (i - 1) + (n - i)]++;
        if (i <= n - 1)
        {
            map[1ll * (n - i) * i] += p[i + 1] - p[i] - 1;
        }
    }
    for (int i = 1; i <= q; i++)
    {
        long long x;
        scanf("%lld", &x);
        printf("%d ", map[x]);
    }
    printf("\n");
}
int main()
{
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}

```

---

## 作者：Super_Cube (赞：1)

# Solution

题意：$n$ 个单增的坐标点，其中每个点都会往后面的所有点之间画一条线段，求被恰好 $x$ 条线段覆盖的点个数。

对于 $a_i$ 这个端点来说，会被覆盖 $i(n-i+1)-1$
 次，对于 $(a_i,a_{i+1})$ 中的点来说，会被覆盖 $i(n-i)$ 次。用 $x$ 反解出 $i$ 计算答案。

# Code

```cpp
#include<bits/stdc++.h>
int a[100005];
int T,n,m,ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;scanf("%d",&a[i++]));
		for(long long x;m--;){
			scanf("%lld",&x);
			ans=0;
			int l,r;
			long long delta=(n+1ll)*(n+1)-4ll*(x+1);
			//i(n-i+1)-1=x
			if(delta>=0&&sqrtl(delta)==(long long)(sqrtl(delta))){
				delta=sqrtl(delta);
				if((n+1&1)==(delta&1)){
					l=((n+1)-delta)/2;r=((n+1)+delta)/2;
					if(1<=l&&l<=n)++ans;
					if(r!=l&&1<=r&&r<=n)++ans;
				}
			}
			delta=1ll*n*n-4ll*x;
			//i(n-i)=x
			if(delta>=0&&sqrtl(delta)==(long long)(sqrtl(delta))){
				delta=sqrtl(delta);
				if((n&1)==(delta&1)){
					l=(n-delta)/2;r=(n+delta)/2;
					if(1<=l&&l<n)ans+=a[l+1]-a[l]-1;
					if(r!=l&&1<=r&&r<n)ans+=a[r+1]-a[r]-1;
				}
			}
			printf("%d ",ans);
		}
		putchar(10);
	}
	return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 题意简述

在数轴上有 $n$ 个点，每两个点形成一个线段。问：每次查询，有有几个点恰好被 $k$ 个线段覆盖。

### 题目分析

可以使用 `map` 统计这几条线段被覆盖的点即可。

我们只需要枚举每一个点。如果该点为左端点或右端点，往前或后连出 $i$ 个线段标记至 `map`。

### 代码实现

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
void read ();
const ll MAXN = 1e5 + 10;
ll T, n, Q, shu[MAXN], k;
void read () {
	cin >> n >> Q;
	for (ll i = 1; i <= n; i ++) cin >> shu[i];
	shu[n + 1] = shu[n] + 1;
	map <ll, ll> mapp;
	for (ll i = 1; i <= n; i ++) {
		mapp[(i - 1) * (n - i) + n - 1] ++;
		mapp[i * (n - i)] += shu[i + 1] - shu[i] - 1;
	}
	while (Q --) {
		cin >> k;
		cout << mapp[k] << ' ';
	}
	cout << endl;
} 
int main () {
	cin >> T;
	while (T --) read ();
	return 0;
}
```

---

## 作者：__bjxx0201__ (赞：0)

## 题面意思

从小到大有 $n$ 个数字，分布在 $x$ 轴上。它们都是从小到大排列的。

现在在每一个点后面画一条线段，求被 $x$ 条线段覆盖的数字的个数。

总共有 $t$ 个测试样例，$1\le t \le 10^4$。

## 思路

[题目传送门](https://www.luogu.com.cn/problem/CF2019B)

首先，这题搜索太暴力，还会超时。这里推荐使用 map。用它统计这几条线段被覆盖的点即可。

用 map 时，我们只需要枚举每一个点。如果该点为左端点或右端点，往前或后连出 $i$ 个线段标记至 map。

最后注意一个点：$1\le k \le 10^{18}$，需要使用 long long。

---

## 作者：Talkative (赞：0)

水题，才 1200。


题目分析：题目要求我们处理一组点在数轴上的线段覆盖问题。具体来说，给定 $ n $ 个点，这些点的坐标是递增的正整数 $ x_1 < x_2 < \ldots < x_n $。对于每对点 $ (i, j) $，其中 $ 1 \leq i < j \leq n $，我们绘制线段 $ [x_i, x_j] $。这些线段是闭合的，即线段 $ [a, b] $ 包含点 $ a, a+1, \ldots, b $。我们需要回答 $ q $ 个查询，每个查询给定一个正整数 $ k_i $，要求确定恰好被 $ k_i $ 条线段包含的整点有多少个。

思路：一步步走，具体见下。

覆盖：对于每对点 $ (i, j) $，线段 $ [x_i, x_j] $ 包含从 $ x_i $ 到 $ x_j $ 的所有整点。每个点 $ x_i $ 会被所有包含它的线段覆盖。

查询：对于每个查询 $ k_i $，我们需要统计有多少个点恰好被 $ k_i $ 条线段覆盖。由于线段的数量是 $ O(n^2) $ 的，直接暴力计算会超时。

优化：可以利用组合数学的方法，预处理每个点被覆盖的次数对于每个点 $ x_i $，计算它被多少条线段覆盖。具体来说，点 $ x_i $ 被覆盖的次数是所有包含它的线段的数量。由于线段是闭合的，点 $ x_i $ 被覆盖的次数可以通过计算它左边和右边的点的数量来确定。

---

## 作者：qfy123 (赞：0)

# CF2019B
[CF 传送门](https://codeforces.com/problemset/problem/2019/B)
## Preface
警示后人：打 CF 线上公开赛一定一定要**看准时间**，不然的话……
## Solution
考虑分别对端点、以及不包含端点的其他点计算贡献。
1. 对于一个线段的端点而言，考虑它能被多少个线段覆盖。显然，是它与它右边的点和它与它左边的点配对，减去它与自身配对的方案数。那根据乘法原理，对于端点 $i$，它能被 $i \times (n - i + 1) - 1$ 个线段覆盖。
2. 对于一个去掉两个端点的线段内的点而言，假设现在考虑到了第 $i$ 个线段，则它的左边有 $i$ 个端点，右边有 $n - i$ 个端点，还是乘法原理，这些点能被 $i \times(n - i)$ 个线段覆盖。

统计答案时，用 map 来存一下即可。记得开 long long。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long 
#define ull unsigned long long
#define ri register int
#define rep(i,j,k) for(ri i=(j);i<=(k);++i) 
#define per(i,j,k) for(ri i=(j);i>=(k);--i)
#define repl(i,j,k,l) for(ri i=(j);(k);i=(l))
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define pc(x) putchar(x)
#define fir first
#define se second 
#define MP pair<int,int>
#define PB push_back
using namespace std;
char BUFFER[100000],*P1(0),*P2(0);
#define gtc() (P1 == P2 && (P2 = (P1 = BUFFER) + fread(BUFFER,1,100000,stdin), P1 == P2) ? EOF : *P1++)
inline int R(){
    int x;char c;bool f = 0;
	while((c = gtc()) < '0') if(c == '-') f = 1;
	x = c ^ '0';
	while((c = gtc()) >= '0') x = (x << 3) + (x << 1) + (c ^ '0');
	return f?(~x + 1):x;
}
inline void O(int x){
    if(x < 0) pc('-'),x = -x;
    if(x < 10) pc(x + '0');
    else O(x / 10),pc(x % 10 + '0');
}
inline void out(int x,int type){
	if(type == 1) O(x),pc(' ');
	if(type == 2) O(x),pc('\n');
	if(type == 3) O(x);
}
inline void OI(){
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
const int N = 1e5 + 10;
int T,n,q,a[N];
map<int,int> ma;
signed main(){
	T = R();
	while(T--){
		n = R(), q = R();
		ma.clear();
		rep(i,1,n) a[i] = R();
		rep(i,1,n) ma[i * (n - i + 1) - 1] += 1;
    //对于第 i 个端点而言，会被 i * (n - i + 1) - 1 条线段覆盖。
		rep(i,1,n - 1) ma[i * (n - i)] += a[i + 1] - a[i] - 1;
    // 第 i 个线段内会有 a[i + 1] - a[i] - 1 个点。
		rep(i,1,q){
			int x = R();
			out(ma[x], 1);
		}
		pc('\n');
	}
	return 0;
}
```

---

## 作者：Autumn_Rain (赞：0)

建议评橙/黄。vp 时因为下标没转 long long 被卡了好一会。

考虑手推一下每两个点之间的区间被覆盖了几次。用 map 记录一下出现这么多次的点有几个，注意端点的处理方式，最后输出即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
const int N=1e5+10;
#define ll long long
int n,q;
ll x[N],k;
void solve(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>x[i];
	}
	x[n+1]=x[n]+1;
	map<ll,ll>m;
	for(int i=1;i<=n;i++){
		m[(ll)(i-1)*(n-i)+n-1]++;
		m[(ll)i*(n-i)]+=x[i+1]-x[i]-1;
	}
	while(q--){
		cin>>k;
		cout<<m[k]<<" ";
	}
	cout<<"\n";
} 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)solve();
	return 0;
}



```

---

## 作者：furina_yyds (赞：0)

## 题意
有 $T$ 组数据，对于每组数据，给定两个数 $n,q$，接下来一行，$n$ 个整数 $a_1,a_2\ldots a_n$，对于任意的 $i, j(1\le i, j\le n)$，$a_i$ 和 $a_j$ 之间都有一条线段。下面一行，$q$ 个整数 $k_1,k_2\ldots k_n$，你需要回答 $k_i(1 \le i \le q)$ 会被多少条线段覆盖。
## 思路
定义一个 $t$ 数组，$t_i$ 表示点 $i$ 会被多少条线段覆盖，对于每条线段，我们将 $a_l,a_{l+1}\ldots a_r$ 都加 $1$。但如果暴力加的话会超时，这时我们要使用一种方法，叫做[差分](https://baike.baidu.com/item/%E5%B7%AE%E5%88%86/10349967?fr=ge_ala)。这样，我们就可以在 $O(n^2+k)$ 的时间复杂度内做出来了。
## 注意
**十年 OI 一场梦，不开 long long 见祖宗。**

**多测不清空，WA 两行泪。**

---

