# [AGC040D] Balance Beam

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc040/tasks/agc040_d

$ 1 $ から $ N $ までの番号がついた $ N $ 個の平均台があります． どの平均台の長さも $ 1 $ メートルです． すぬけくんが平均台 $ i $ の上をあるくスピードは $ 1 $ 秒あたり $ 1/A_i $ メートルです． また，りんごさんが平均台 $ i $ の上をあるくスピードは $ 1 $ 秒あたり $ 1/B_i $ メートルです．

すぬけくんとりんごさんが，以下のゲームを行います．

- まず，すぬけくんが $ N $ 個の平均台を好きな順序で横一列に連結し，長さ $ N $ メートルの平均台を作る．
- すぬけくんはこの平均台の左端からスタートする． りんごさんはこの平均台の上で一様ランダムに選ばれた一点からスタートする． $ 2 $ 人は同時にスタートし，平均台の右端を目指して進む。
- すぬけくんの勝利条件は，りんごさんが平均台の右端に到着する前にりんごさんに追いつくことである． つまり，すぬけくんとりんごさんの位置が同じになる瞬間があればすぬけくんの勝ち，そうでないならりんごさんの勝ちである．

すぬけくんが勝率を最大化するように平均台を並べたときの勝率を求めてください．

なお，この問題の答えは有理数になります． そこで，答えを既約分数 $ P/Q $ として表したときの $ P,Q $ を求めてください． ただし，答えが $ 0 $ の時は $ P=0,Q=1 $ としてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ A_i,B_i\ \leq\ 10^9 $
- 入力される値はすべて整数である．

### Sample Explanation 1

平均台 $ 2,1 $ の順に連結するとすぬけくんの勝率は $ 1/4 $ になり，これが最大です．

## 样例 #1

### 输入

```
2
3 2
1 2```

### 输出

```
1 4```

## 样例 #2

### 输入

```
4
1 5
4 7
2 1
8 4```

### 输出

```
1 2```

## 样例 #3

### 输入

```
3
4 1
5 2
6 3```

### 输出

```
0 1```

## 样例 #4

### 输入

```
10
866111664 178537096
705445072 318106937
472381277 579910117
353498483 865935868
383133839 231371336
378371075 681212831
304570952 16537461
955719384 267238505
844917655 218662351
550309930 62731178```

### 输出

```
697461712 2899550585```

# 题解

## 作者：wind_whisper (赞：12)

## 前言
人类智慧，不可思议。
## 解析
考虑画出两个人的 $S-T$ 折线图，那么答案如何表示？  
可以理解成把 $B$ 的图像不断下移，直到与 $A$ 的图像只剩一个交点，此时在 $x$ 轴的截矩就是答案。  

设平移后 $B$ 图像与 $x$ 轴交于 $k$ 点，观察 $k$ 右侧的折线，发现由于 $x$ 轴下方的 $B$ 图像不知道，$B$ 折线最后到达的位置是未知的。    
但是我们可以观察到，$A$ 折线最后必然会到达 $(n,\sum a_i)$ 的位置，并且又由于 $A,B$ 折线有交点，不妨考虑**从 $B$ 折线到交点后转到 $A$ 折线**的这段图像。  
我们肯定要最小化这段的横向距离，那么肯定就要让这段图像的斜率尽可能大，一个显然的斜率上界是 $\max (a_i,b_i)$，并且只要按照 $b_i-a_i$ 降序排序，这个上界就可以取到。  

那么按照 $\max(a_i,b_i)$ 升序排序，考虑枚举 $k$ 点所在的线段 $p$，那么我们必然取得是一段后缀使得 $b_p+\sum_{i=pos}^n\max(a_i,b_i)\ge \sum a_i$，再加上 $p$ 内部的长度即可。  

二分找一下就好了，时间复杂度 $O(n\log n)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define ok debug("line: %d\n",__LINE__)
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

const int N=2e5+100;
int Flag=0;

bool mem1;

int n;

struct frac{
  ll x,y;// x/y;
  frac(int X=0,int Y=1){
    int g=__gcd(X,Y);
    x=X/g;
    y=Y/g;
  }
};
bool operator < (const frac &a,const frac &b){
  return (__int128)a.x*b.y<(__int128)b.x*a.y;
}

struct node{
  int a,b;
}p[N];
ll sum[N];

bool mem2;
signed main(){

#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  //debug("mem=%lf\n",abs(&mem2-&mem1)/1024./1024);

  ll sa(0);
  n=read();
  for(int i=1;i<=n;i++){
    p[i].a=read();
    p[i].b=read();
    sa+=p[i].a;
  }
  sort(p+1,p+1+n,[&](node u,node v){return max(u.a,u.b)<max(v.a,v.b);});
  for(int i=1;i<=n;i++) sum[i]=sum[i-1]+max(p[i].a,p[i].b);
  frac ans(0,1);
  for(int i=1;i<=n;i++){
    int st=0,ed=n+1;
    while(st<ed){
      int mid=(st+ed+1)>>1;
      if(sum[n]-sum[mid-1]-(mid<=i)*max(p[i].b,p[i].a)+p[i].b>=sa) st=mid;
      else ed=mid-1;
    }
    if(!st) continue;    
    frac res(sum[n]-sum[st-1]-(st<=i)*max(p[i].b,p[i].a)+p[i].b-sa,p[i].b);
    if(res.x>res.y) continue;
    res.x+=res.y*(st-1-(i<st));
    if(ans<res) ans=res;
  }
  ll g=__gcd(1ll*n,ans.x);
  ans.x/=g;
  ans.y*=n/g;
  printf("%lld %lld\n",ans.x,ans.y);
  return 0;
}

```


---

## 作者：Caro23333 (赞：7)

一个比较简单的性质是，对于固定的排列方法，使得 Alice 能抓到 Bob 的起始点范围是一段从 $0$ 开始的连续区间，所以只要设法最大化区间右端点，也就是 Alice 恰好能抓到 Bob 时，Bob 的起始位置。

可以比较自然地想到借助图像来解决问题。设所有 $a_i$ 的和为 $s_a$ ，所有 $b_i$ 的和为 $s_b$，再建立 Alice 和 Bob 的“位移 - 时间”图，那么应该形成两条从 $(0,0)$ 开始到 $(n,s_a)$ 或者 $(n,s_b)$ 的折线，每条折线由 $n$ 条小线段组成。考虑将 Bob 的折线纵向平移，使得它处在**如果再往下移就和 Alice 没有交点**的临界位置，设此时 Bob 的折线与 $x$ 轴交点为 $(k,0)$ ，则只要设法最大化 $k$ 即可。

然后考虑这样一条折线：从 $(k,0)$ 开始，沿着 Bob 的折线往上走，直到与 Alice 的折线相交之后，便沿着 Alice 的折线走。不难发现无论排列方式如何，这条折线总结束于一个定点 $(n,s_a)$。我们枚举 $(k,0)$ 所在的石板编号 $p$ ，所以只要最大化 $p$ 右侧折线的增长速度，即可让 $(k,0)$ 尽量靠近 $(n,0)$ 。

如何最大化？一个平凡的观察是，这条折线在石板 $i$ 内的增长速度不超过 $\max(a_i,b_i)$ ：这启示我们将 $\max(a_i,b_i)$ 尽量大的石板优先放在 $p$ 的右侧。

于是，将所有石板按照 $\max(a_i,b_i)$ 排序，再通过二分取出尽量短的一段后缀使得 $\max(a_i,b_i)$ 的后缀和 $\ge s_a-b_p$，那么这一段后缀的石板就应当被排到 $p$ 的右侧。

但是在这里，有一个问题：这个后缀和是一个增长速度的上界，但它一定能被取到么？答案是肯定的：只要将后缀中的石板按照 $a_i-b_i$ 从小到达摆放即可。这保证了这一做法的正确性。

这样可以计算出在 $p$ 后面最少有多少块石板，以及此时 $p$ 内部还有多少在 $(k,0)$ 右侧（简单一次函数计算），进一步计算出 $(k,0)$ 的具体值，对所有 $1$ ~ $n$ 的 $p$ 取 $\max$ 即可。

时间复杂度 $O(n\log n)$ 。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define int long long

using namespace std;
typedef long long ll;
const int MAXN = 100005;
inline int readint()
{
	int res = 0, f = 1;
	char c = 0;
	while(!isdigit(c))
	{
		c = getchar();
		if(c=='-')
			f = -1;
	}
	while(isdigit(c))
		res = res*10+c-'0', c = getchar();
	return res*f;
}
int n;
pii s[MAXN],t[MAXN];
ll ansp = 1<<30, ansq = 1;
inline void getMin(ll x, ll y)
{
	if((__int128)x*ansq<(__int128)y*ansp)
		ansp = x, ansq = y; 
}
ll pre[MAXN],sum;
inline ll calc(int x, int mid)
{
	int val = max(s[x].fi,s[x].se);
	return t[mid].fi<=val?pre[mid]-val:pre[mid];
}
inline int binSearch(int x)
{
	int left = 1, right = n, res = -1, mid;
	while(left<=right)
	{
		mid = (left+right)>>1;
		if(calc(x,mid)>=sum-s[x].se)
			res = mid, right = mid-1;
		else
		    left = mid+1;
	}
	return res;
}
inline ll gcd(ll a, ll b)
    { return b?gcd(b,a%b):a; }

signed main()
{
	n = readint();
	for(int i = 1; i<=n; i++)
	{
		s[i].fi = readint(), s[i].se = readint();
		t[i].fi = max(s[i].fi,s[i].se), t[i].se = i;
		sum += s[i].fi;
	}
	sort(t+1,t+n+1), reverse(t+1,t+n+1);
	for(int i = 1; i<=n; i++)
		pre[i] = pre[i-1]+t[i].fi;
	for(int i = 1; i<=n; i++)
	{
		int res = binSearch(i);
		if(res<0)
			continue;
		ll val = sum-calc(i,res);
		if(t[res].fi<=max(s[i].fi,s[i].se))
			res--;
		if(val<0)
			continue;
		getMin(1ll*res*s[i].se+val,s[i].se);
	}
	ansq *= n, ansp = ansq-ansp;
	if(ansp<=0)
    {
		cout << 0 << " " << 1 << endl;
		return 0;
	}
	ll g = gcd(ansp,ansq);
	cout << ansp/g << " " << ansq/g << endl;
	return 0;
}

```


---

## 作者：zhylj (赞：4)

## 题目

有两个人 A, B 以及 $N$ 个长度为 $1$ 的平衡木依次排列，第 $i$ 个平衡木 A, B 通过的速度为 $\dfrac 1{A_i},\dfrac 1{B_i}$，A 可以随意重排平衡木，然后 B 等概率随机出现在这条石板上的任意位置（未必是整点），两人同时向右走，最大化 A 在 B 到达之前与 B 相遇的概率。

$1\le N\le 10^5$，$1\le A_i, B_i\le 10^9$。

## 分析

考虑怎么计算一个固定排列的相遇概率，注意到必然是某个前缀相遇，而后缀不相遇。若不相遇，那么 B 永远在 A 前面，则 B 通过所有平衡木的时间都要早于 A，记 B 领先 A 的距离**本来需要花费 B 的时间**为 $x$，则即相当于对任意 $i$，满足：
$$
\sum_{j=1}^i B_j - x\le \sum_{j=1}^i A_j\implies x\ge \max_{i=0}^N\left(\sum_{j=1}^i(B_j-A_j)\right)
$$
记 $d_i = B_i-A_i$，则相当于求 $d_i$ 前缀和的最大值即为 $x$，考虑这个 $x$ 对应的概率，那么就是寻找 B 从 $0$ 位置出发经过 $x$ 时刻到达的位置，即找到最大的 $k$ 使得 $\sum_{i\lt k} B_i\le x$，答案为 $\dfrac kn + \dfrac {x-\sum_{i\lt k}B_i}{nB_k}$。

接下来考虑如何最大化这个概率，考虑贡献最大前缀和的位置 $p$，注意到 $d_i=B_i-A_i\le B_i$，即有 $\sum_{i\le j} d_i\le \sum_{i\le j} B_i$ 对任意 $i$ 成立，而又有 $\sum_{i\le p} d_i\ge \sum _{i\lt k} B_i$，那么就可以得到 $p\ge k$，而在 $k$ 后面的数的顺序只会影响最大前缀和，而不会影响 $k$ 的位置，那我们当然是希望最大前缀和尽可能大，也就是将 $d_i\ge 0$ 的排在前面，$d_i\lt 0$ 的排在后面，于是可以得到一个重要观察：**最大前缀和等于所有正的 $d_i$ 之和加上位置 $\le k$ 的 $d_i$ 之和。**

由于答案的式子中 $\dfrac {x-\sum_{i\lt k}B_i}{nB_k}$ 不会超过 $\dfrac 1n$，所以我们希望先最大化 $k$，再最大化剩下的部分。

考虑一个数如果放在 $k$ 前面，对 $\mathrm {res}=x-\sum_{i\lt k} B_i$ 的影响是什么？初始令 $\mathrm {res}$ 为所有正数之和，那么一个正数（正数意为 $d_i$ 为正，下同）产生的影响即为 $-B_i$，一个负数会使得最大前缀和减少 $-d_i$ 且也为带来 $-B_i$ 的影响。于是要确定最小的 $k$，只需贪心给所有平衡木按 $d_i[d_i\le 0] - B_i$ 排序，然后从大到小一个个加进 $\mathrm {res}$ 中，直到某次加入会导致 $\mathrm {res}\lt 0$ 则不再加入。

接下来考虑如何确定剩余部分，枚举在 $k$ 位置处放置的平衡木，那么在前面的仍然是从大到小贪心放。预处理排完序后贡献的前缀和，那么只需要找到前 $k-1$ 大，这要么为前 $k-1$ 大，要么为前 $k$ 大减去已经被钦定放在 $k$ 位置的平衡木的贡献，从所有可能合法的答案中选取一个最优解即为本题的答案。

时间复杂度 $\mathcal O(N\log N)$，瓶颈在于排序。

```cpp
#define fi first
#define se second
#define mkp std::make_pair
typedef long long ll;
typedef std::pair <ll, ll> pii;
const int N = 1e5 + 5;

ll Gcd(ll a, ll b) { return b ? Gcd(b, a % b) : a; }
void D(pii &x) { ll g = Gcd(x.fi, x.se); x.fi /= g; x.se /= g; }

struct Beam {
	int A, B, d;
} B[N];
int n; ll s[N];

int main() {
	ll mx = 0;
	rd(n);
	for(int i = 1; i <= n; ++i) {
		rd(B[i].A, B[i].B);
		B[i].d = B[i].B - B[i].A;
	}
	for(int i = 1; i <= n; ++i)
		if(B[i].d >= 0) {
			mx += B[i].d;
			B[i].d = 0;
		}
	pii ans = mkp(0, 1);
	std::sort(B + 1, B + n + 1,
		[&](const Beam &x, const Beam &y) {
			return x.d - x.B > y.d - y.B;
		}
	);
	int cnt = 0;
	for(int i = 1; i <= n; ++i) {
		s[i] = s[i - 1] + B[i].d - B[i].B;
		if(mx + s[i] >= 0) ++cnt;
	}
	for(int i = 1; i <= n; ++i) {
		ll res_s = i <= cnt ? s[cnt + 1] - (B[i].d - B[i].B) : s[cnt];
		if(mx + res_s + B[i].d >= 0) {
			pii cur = mkp(mx + res_s + B[i].d, B[i].B);
			if(ans.fi * cur.se < ans.se * cur.fi)
				ans = cur;
		}
	}
	ans.fi += cnt * ans.se; ans.se *= n;
	D(ans);
	printf("%lld %lld\n", ans.fi, ans.se);
	return 0;
}
```

---

## 作者：苹果蓝17 (赞：1)

容易发现若 Ringo 的起始点为 $x$ 时 Snuke 能够追上 Ringo，则起始点为 $y(y<x)$ 时也能。故使 Snuke 获胜的起始点一定是一段前缀。

下面设 $a_t,b_t$ 分别表示点 $t$ 所在的整段的 $A$ 值与 $B$ 值。

考虑起始点为 $x$，Snuke 在 $y$ 处追上 Ringo。则需要满足：

$$-\int_0^x a_t dt+\int_x^y(b_t-a_t) dt \geq 0$$

显然 $y$ 所在的整段 $k$ 一定满足 $A_k<B_k$，故 $\lceil y \rceil$ 也一定满足条件，故不妨设 $y$ 为整点。

假设 $x$ 只能为整点（即求答案向下取整的值），那么问题相当于在所有整段中选出两个不交的集合 $S_1,S_2$ 满足 $s=-\sum_{i \in S_1} A_i+\sum_{i \in S_2} (B_i-A_i) \geq 0$，最大化 $|S_1|$。可以设计这样一个算法：

+ 对于每个整段 $k$，先将其放入 $S_2$ 或者丢掉，再赋权值 $c_k$ 表示将其改为放入 $S_1$ 新增的**代价**（即让 $s$ 减少多少）。

    + 若 $A_k \geq B_k$，则先将 $k$ 选入 $S_2$ 中使 $s$ 获得 $B_k-A_k$ 的值，$c_k=B_k$。
    + 若 $A_k > B_k$，则先将其丢掉，$c_k=A_k$。

+ 将所有 $c_k$ 从小到大排序，若当前 $s \geq c_k$ 则选入并令 $s \leftarrow s-c_k$，否则报告答案退出。

对于原问题，枚举选择一个整段 $k$ 作为 $x$ 所在的整段。设 $p=x-\lfloor x \rfloor=\{x\}$，那么其对 $s$ 的贡献为 $-pA_k+(1-p)(B_k-A_k)$。

令初始 $s=B_k-A_k$，对剩下的 $n-1$ 个整段进行上述算法，即可计算通过得到 $p$ 以及答案。对所有 $k$ 的答案取 $\max$ 即可。

预处理前缀和后可以二分优化算法的第二步，时间复杂度 $O(n \log n)$。

注意分数比较时可能会爆 $\text{long long}$。

#### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=1e5+5;
long long n,alc,s[N];

struct abc{
	long long a,b,w;
}p[N];
bool operator <(abc X,abc Y){
	return X.w<Y.w;
}
struct frac{
	long long x,y;
};
bool operator <(frac X,frac Y){
	return (__int128)X.x*(__int128)Y.y<(__int128)X.y*(__int128)Y.x;
}
frac max(frac X,frac Y){
	return (X<Y)?Y:X;
}
frac ans={0,1};

int main(){
	cin>>n;
	for(long long i=1;i<=n;i++){
		long long a,b; scanf("%lld%lld",&a,&b);
		alc+=max(0ll,b-a);
		p[i]=(abc){a,b,max(a,b)};
	}
	sort(p+1,p+n+1);
	for(long long i=1;i<=n+1;i++) s[i]=s[i-1]+p[i].w;
	
	for(long long i=1;i<=n;i++){
		long long ns=alc-max(0ll,p[i].b-p[i].a)+p[i].b-p[i].a;//除掉 i 后初始的 s 
		long long l=0,r=n,tot=0;
		while(l<=r){
			long long mid=(l+r)>>1;
			long long num=mid-(i<=mid),sum=s[mid]-(i<=mid)*p[i].w;
			if(ns-sum>=0) tot=mid,l=mid+1;
			else r=mid-1;
		}
		
		long long num=tot-(i<=tot),sum=s[tot]-(i<=tot)*p[i].w;
		long long x=ns-sum;
		if(x<=p[i].b) ans=max(ans,(frac){num*p[i].b+x,p[i].b});//p<=1
	}
	ans.y*=n;
	long long g=__gcd(ans.x,ans.y);
	cout<<ans.x/g<<" "<<ans.y/g;
}
```

---

## 作者：DCH233 (赞：0)

颇有难度的一道题。

首先思考我们的手上有什么武器可以使用。发现如果石板的排列确定下来，那么合法的 B 一定是形如 $[0, x)$ 的一段区间。我们只需令 $x$ 最大即可。同时，显然可以认为终点一定在整点上。题目中很为难我们的一点是位置并不是离散的，所以自然想到图像。但是我没想到图像，所以只好先假装位置是离散的看一下有什么做法。

考虑寻找充要条件，假设 B 从 $x$ 点，在 $y$ 点被逮住，那么充要条件是：

$$
\sum_{i \le y} A_i \le \sum_{x < i \le y} B_i
$$

考虑分离 $x, y$ 这两个变量。变为 $\sum_{i \le x} A_i + \sum_{x < i \le y} (A_i - B_i) \le 0$

好了，现在把排列丢掉，问题转化为划分两个不交的集合 $S, T$ 使得

$$
s = \sum_{i \in S} A_i + \sum_{i \in T} (A_i - B_i) \le 0
$$

最大化 $|S|$。

这样就有一个简单的贪心做法了：注意到 $A_i$ 一定是正的，而 $A_i - B_i$ 可能是负的，所以初始把所有会使 $s$ 减小的 $i$ 划分入 $T$，然后贪心选代价最小的加入 $S$，直到不能选为止。

现在回到原问题，自然想到枚举分界点然后转化成上面的问题。怎么做呢？注意到由于终点一定是整点，所以分界点这一段必然要么处于 B 左侧，要么在 B 和终点中间。去掉这一段，我们希望选择尽可能多的整点，所以初始时先令 $s$ 尽可能的小，然后在通过二分优化贪心地过程，最后单独算这个散段的最值就行了。什么叫令 $s$ 尽可能的小呢？就是不管怎样都先加上一个当前段的 $A_i - B_i$，由于 $i$ 要么出现在 $S$ 中要么出现在 $T$ 中，所以这个做法是正确的。

```cpp
const int N = 1e5 + 10;

struct Frac {
  LL x, y;
  void check() {
    LL d = __gcd(x, y);
    x /= d, y /= d;
  }
  bool operator < (const Frac &rhs) const {
    return (__int128)x * rhs.y < (__int128)rhs.x * y;
  }
};

int n;
LL a[N], b[N];
struct item {
  int id;
  LL c;
}c[N];
int p[N];
LL pre[N];

int main() {
  read(n);
  for(int i = 1; i <= n; ++i)
    read(a[i], b[i]);
  LL sum = 0;
  for(int i = 1; i <= n; ++i) {
    c[i].id = i;
    if(b[i] >= a[i]) {
      sum += b[i] - a[i];
      c[i].c = -b[i];
    } else {
      c[i].c = -a[i];
    }
  }
  sort(c + 1, c + n + 1, [](item x, item y) {
    return x.c > y.c;
  });
  for(int i = 1; i <= n; ++i)
    p[c[i].id] = i, pre[i] = pre[i - 1] + c[i].c;
  Frac ans = {0, 1};
  for(int i = 1; i <= n; ++i) {
    LL s = sum;
    if(b[i] < a[i]) s += b[i] - a[i];
    int pos = 0;
    for(int l = 1, r = n; l <= r; ) {
      int mid = (l + r) / 2;
      LL sum = pre[mid] - (mid >= p[i]) * c[p[i]].c;
      if(s + sum >= 0) pos = mid, l = mid + 1;
      else r = mid - 1;
    }
    LL sum = s + (pre[pos] - (pos >= p[i]) * c[p[i]].c);
    Frac res;
    res = (Frac){(pos - (pos >= p[i])) * b[i] + min(sum, b[i]), b[i]};
    if(res.x < 0) continue;
    res.check();
    if(ans < res) ans = res;
  }
  ans.y *= n;
  ans.check();
  printf("%lld %lld\n",ans.x,ans.y);
}
```


---

