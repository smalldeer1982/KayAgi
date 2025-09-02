# Card Game Again

## 题目描述

Vova again tries to play some computer card game.

The rules of deck creation in this game are simple. Vova is given an existing deck of $ n $ cards and a magic number $ k $ . The order of the cards in the deck is fixed. Each card has a number written on it; number $ a_{i} $ is written on the $ i $ -th card in the deck.

After receiving the deck and the magic number, Vova removes $ x $ (possibly $ x=0 $ ) cards from the top of the deck, $ y $ (possibly $ y=0 $ ) cards from the bottom of the deck, and the rest of the deck is his new deck (Vova has to leave at least one card in the deck after removing cards). So Vova's new deck actually contains cards $ x+1 $ , $ x+2 $ , ... $ n-y-1 $ , $ n-y $ from the original deck.

Vova's new deck is considered valid iff the product of all numbers written on the cards in his new deck is divisible by $ k $ . So Vova received a deck (possibly not a valid one) and a number $ k $ , and now he wonders, how many ways are there to choose $ x $ and $ y $ so the deck he will get after removing $ x $ cards from the top and $ y $ cards from the bottom is valid?

## 说明/提示

In the first example the possible values of $ x $ and $ y $ are:

1. $ x=0,y=0 $ ;
2. $ x=1,y=0 $ ;
3. $ x=2,y=0 $ ;
4. $ x=0,y=1 $ .

## 样例 #1

### 输入

```
3 4
6 2 8
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 6
9 1 14
```

### 输出

```
1
```

# 题解

## 作者：素质玩家孙1超 (赞：6)

题意：

给定序列, 求多少个区间积被 $k$ 整除。

---

给出一种和已有的一篇题解不同的，实现更加简洁，复杂度优秀的解法。

首先，我们可以找到从 $l$ 开始前缀积被 $k$ 整除的区间 $ [\ l,i\ ]$ ，然后找到其最短能被 $k$ 整除的后缀 $ [\ j,i\ ] $ ，这就是一个极短的有效区间。

可以发现，任意包含 $[\ j,i\ ]$ 的区间都是合法区间，我们直接计算合法区间数，找到一个 $[\j ,i\ ]$ 后，可以把 $l$ 设为 $j+1$ 避免计算重复。

实现细节可以看代码，下面证明其复杂度。

我看到其他网上的题解把其复杂度误解为 $O(n)$ ，其实是不对的。

若所有值都是 $2$ ，然后 $k$ 是 $2$ 的倍数，那么显然复杂度是 $O(n \times \log k)$ 的。

但有些数可能是 $1$ 这样的复杂度又如何呢？

我们可以把枚举 $i$ 使得前缀积被 $k $ 整除的过程当成是用每个 $a_i$ 去消掉 $k$ 的部分因数的过程。

我们每个当前无法消掉 $k$的因数的 $a_i$ 都当成 $1$ 算，那么显然有效区间的非 $1$ 长度不会超过 $\log$ 级别，同样的每一个 $1$ 不会被超过 $\log $ 和区间包含，所以每个 $1$ 自然最多被枚举到 $\log $ 次。


以上，总的时间复杂度是 $O(n \times \log k )$ 的。

---

代码：

```cpp
#define int long long 
const int Maxn=1e5+5;
inline int R()
{
    char c;int res,sign=1;
    while((c=getchar())>'9'||c<'0') if(c=='-') sign=-1;res=c-'0';
    while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';
    return res*sign;
}
int a[Maxn],n,k;
signed main(){
    n=R();k=R();
    int ans=0,now=1,j,l=1;
    for(int i=1;i<=n;++i){
    	a[i]=R();
        now=now*a[i]%k;
        if(!now){
            now=1;
			for(j=i;now*a[j]%k;j--)
			now=now*a[j]%k;
            ans+=(n-i+1)*(j-l+1);
            l=j+1;
        }
    }
    printf("%lld\n",ans);
}
```

---

## 作者：_liuyi_ (赞：1)

# 思路
直接暴力枚举 $l,r$，然后判断显然是 $O(n^2)$ 的会超时，我们考虑怎么优化。
对于这种枚举区间题，我们一般考虑先枚举一个端点，然后快速找出另一个合法的端点。我们先枚举一个 $l$，然后怎么找合法的 $r$ 呢，首先这题有一个显然的性质，如果一个区间 $\left [l,r  \right ]$ 是 $k$ 的倍数，那么所有包含它的区间 $\left [l',r'  \right ] $ 也一定是 $k$ 的倍数，因为我们已经固定了一个端点，所以另一个合法端点它具有单调性，所以我们考虑二分 $r$。如何快速判断一个区间是不是 $k$ 的倍数，我们可以对 $k$ 和 $a_i$ 质因数分解，然后前缀和快速判断，有关的质因子个数是不是大于等于 $k$ 的，或者你写个线段树也可以。时间复杂度 $O(n \log n \log k+\sqrt{k})$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define fi first
#define se second
#define pb push_back
#define mem(a,x) memset(a,x,sizeof(a))
#define all(x) x.begin(),x.end()
#define lisan(x) {sort(all(x));x.erase(unique(all(x)),x.end());}
#define SZ(x) ((int)((x).size()))
#define debug(x) cout<<#x<<"="<<x<<"\n";
#define ti (db)((db)clock() / CLOCKS_PER_SEC)
typedef long long ll;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
typedef vector<int> VI;
typedef vector<vector<int>> VII;
typedef vector<ll> VL;
typedef vector<vector<ll>> VLL;
typedef unsigned long long ull;
typedef double db;
template<typename T> inline void cmax(T &a,const T b){if(a<b) a=b;}
template<typename T> inline void cmin(T &a,const T b){if(a>b) a=b;}
template<typename T> inline T gcd(T a,T b){return b?gcd(b,a%b):a;}
template<typename T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}
constexpr int N=1e5+10,M=200;
constexpr int mod=1e9+7;
//constexpr int mod=998244353;
int l,r,n,a[N],k,pos[N],pre[N][M],cnt,num,val[N];
ll ans;
map<int,int> id;
inline void init(){
	rep(i,2,sqrt(k)){
		if(k%i==0&&id.count(i)==0) id[i]=++cnt;
		int now=id[i];
		val[now]=i;
		while(k%i==0){
			k/=i;
			pos[now]++;
		}
	}
	if(k!=1){
		if(id.count(k)==0) id[k]=++cnt;
		pos[id[k]]++;
		val[id[k]]=k;
	}
	num=cnt;
	rep(i,1,n){
		rep(now,1,num){
			pre[i][now]+=pre[i-1][now];
			while(a[i]%val[now]==0) pre[i][now]++,a[i]/=val[now];
		}
	}
}
inline bool check(int L,int R){
	rep(i,1,num) if(pre[R][i]-pre[L-1][i]<pos[i]) return true;
	return false;
}
inline void solve(){
	scanf("%d%d",&n,&k);
	rep(i,1,n) scanf("%d",&a[i]);
	init();	
	rep(i,1,n){
		l=i-1;r=n+1;
		while(l+1<r){
			int mid=(l+r)/2;
			if(check(i,mid)) l=mid;
			else r=mid;
		}
		ans+=n-r+1;
	}
	printf("%lld",ans);
}
int main(){
    int T=1;
    //scanf("%d",&T);
    while(T--) solve();
}
```


---

## 作者：Night_Bringer (赞：1)

# 前言
[博客园](https://www.cnblogs.com/C202202chenkelin/p/14893063.html)

[题目链接：CodeForces](https://codeforces.com/problemset/problem/818/E)
# 题意
给定 $n$ 个数 $a_1$ ~ $a_n$ ，与 $k$ 。问有多少个区间 $[l,r]$ 的积能被 $k$ 整除。

两个区间不同当且仅当 $l$ 不同或 $r$ 不同。
# 思路
可以枚举左端点，然后去找满足条件的右端点。

首先将 $k$ 分解质因数。

可以发现， $a_i$ 分解质因数后，只有和有 $k$ 相同的质因数才有用，否则对于答案是没有贡献的。那么就可以将有用的质因数给用桶给统计起来。

再将这些桶进行前缀和。可以在 $O(\log n)$ 的时间复杂度内求出所有的对整除影响的质数有多少。

在这个区间内，若对于每个质数的个数均大于 $k$ 分解后对应质数的个数，则代表这个区间可以整数 $k$ 。

那么只要枚举左区间，都可以二分出右区间。

因为一个数 $b$ 最多只有 $\log b$ 个质因子，所以总的时间复杂度为 $O(n\log n\log k+\sqrt k)$
# Code
```cpp
#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;
namespace Quick_Function {
	template <typename Temp> void Read(Temp &x) {
		x = 0; char ch = getchar(); bool op = 0;
		while(ch < '0' || ch > '9') { if(ch == '-') op = 1; ch = getchar(); }
		while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
		if(op) x = -x;
	}
	template <typename T, typename... Args> void Read(T &t, Args &... args) { Read(t); Read(args...); }
	template <typename Temp> Temp Max(Temp x, Temp y) { return x > y ? x : y; }
	template <typename Temp> Temp Min(Temp x, Temp y) { return x < y ? x : y; }
	template <typename Temp> Temp Abs(Temp x) { return x < 0 ? (-x) : x; }
	template <typename Temp> void Swap(Temp &x, Temp &y) { x ^= y ^= x ^= y; }
}
using namespace Quick_Function;
#define int long long
#define mkp(x, y) make_pair(x, y)
const int MAXN = 1e5 + 5;
vector<pair<int, int> > vec;
int a[MAXN], n, k;
int cnt[MAXN][50], ans;
bool Check(int l, int r) {
	for(int i = 0; i < vec.size(); i++)
		if(cnt[r][i] - cnt[l - 1][i] < vec[i].second) return 0;
	return 1;
}
signed main() {
	Read(n, k); a[n + 1] = k;
	for(int i = 1; i <= n; i++) Read(a[i]);
	for(int i = 2; i <= sqrt(k); i++) {
		if(k % i == 0) vec.push_back(mkp(i, 0));
		while(k % i == 0) { k /= i; vec[vec.size() - 1].second++; }
	}
	if(k != 1) vec.push_back(mkp(k, 1));
	for(int i = 1; i <= n + 1; i++) {
		int tmp = a[i];
		for(int j = 0; j < vec.size(); j++) {
			cnt[i][j] = cnt[i - 1][j];
			while(tmp % vec[j].first == 0) { tmp /= vec[j].first; cnt[i][j]++; }
		}
	}
	for(int i = 1; i <= n; i++) { 
		int l = i, r = n + 1;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(Check(i, mid)) r = mid;
			else l = mid + 1;
		}
		ans += n - l + 1;
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：minecraft_herobrine (赞：1)

# 原作者：@素质玩家孙1超


这个题解差不多就是把原来第一篇题解的思路详细的说一下吧

这个题的大意是说把一个数列的左侧和右侧各删掉一些数，左边删 $l$ 个，右边删 $r$ 个，保留中间一个连续的段，要求这个连续的段必须能被 $k$ 整除，问有多少种删法。$(l,r)$ 是一个有序数对，只要顺序不同或是有某个数不同就算一个新的删法（样例1就能看出来）。

假设有一个区间 $(l_0,r_0)$ 中间的所有数乘积能被 $k$ 整除，则对于一个区间 $(l_1,r_1)$ 且 $l_1<l_0,r_1>r_0$的一切区间，里面所有数的乘积一定都能被 $k$ 整除。················①

因为当 $m$ 可以被 $k$ 整除时，$m\times t$ 也能被 $k$ 整除

结论①在下文中就叫它**小区间满足要求，包含这个小区间的所有大区间也一定满足要求**

我们现在先要挑出所有的“最小合法区间”，意思就是这个区间是合法的，但是里面无法再找出任何一个合法的子区间

举个例子：
```
7 12
5 2 2 3 5 4 3
```

这里的 $[2,2,3],[3,5,4]$ 和 $[4,3]$ 就是“最小合法区间”

从 $1\to n$ 进行前缀乘积，每次模 $k$，只要遇到一个合法区间，也就是（前缀乘积变量）$=0$，这时候从这个点立刻回头，从后往前找出这个区间的左端点。找出的区间一定就是个“最小合法区间”。因为最左侧的右端点和最右侧的左端点形成的区间肯定是最短的。

也就是说现在必须留下的区间就是刚刚找到的区间，就假设是 $(l_0,r_0)$（注意这里 $(l_0,r_0)$ 和①中的不一样）。

那这样你可以在 $l_0$ 前边删掉 $0$ 到 $(l_0-1)$ 个数，而在 $r_0$ 后边删掉 $0$ 到 $n-r_0$ 个数。根据乘法原理，答案应该累加 $l_0*(n-r_0+1)$。

当开始搜下一个新的区间时候，应当把起始点重置为 $l_0+1$，因为要避免重复的情况

还是前面那个例子，$[2,2,3],[3,5,4]$ 两个区间的 $3$ 重叠了，为了避免出现重复计算 $[2,2,3,5,4]$ ，所以要将搜下一个最小合法区间的起始点重置为上一个区间的左端点 $+1$。

后边就如法炮制就行了

代码和第一篇题解差不多……就不放了吧

---

## 作者：UperFicial (赞：0)

模拟赛小丑玲珑地挂在这道题上了。

来一篇题解区没有的线段树题解。

题意：给定 $n$ 个数，求有多少个区间的积是 $k$ 的倍数。

一个显然的想法，枚举左端点 $l$ 并固定，考虑合法的右端点 $r$ 有什么性质。

对于最小的合法的 $r_{min}$，它右边的端点也就可以随便选了。

所以说，$[r_{min}+1,n]$ 这段区间里，一定会被分成两段连续的区间，不合法区间，合法区间。

考虑二分 $r_{min}$ 的值，那么直接套用前缀积来判断行不行呢？

答案是否定的。在求前缀积的过程必须对 $k$ 的取模，但是求中间一段的积时需要用到除法。这就不满足模运算的运算法则了。

那么我们如何判断一个区间是否是 $k$ 的倍数呢？

考虑线段树，我们记录区间积模 $k$ 的值，如果某一段区间的答案为 $0$，那么这段区间便是合法的。

放一下代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<climits>
#include<queue>
#include<vector>
using namespace std;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0' or ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' and ch<='9')s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}
const int INF=1e9+10;
typedef long long ll;
inline int Max(int x,int y){return x>y?x:y;}
inline int Min(int x,int y){return x<y?x:y;}
inline void Swap(int&x,int&y){x^=y;y^=x;x^=y;}
inline int Abs(int x){return x>0?x:-x;}
const int MAXN(1e5+10);
int n,a[MAXN],k;
typedef pair<int,int> P;
P b[MAXN];
int tot;
ll cnt;
struct Segment_Tree
{
	int tree[MAXN*4];
	inline int lc(int p){return p<<1;}
	inline int rc(int p){return p<<1|1;}
	inline void push_up(int u)
	{
		tree[u]=(1ll*tree[lc(u)]*tree[rc(u)])%k;
		return;
	}
	inline void build(int u,int l,int r)
	{
		if(l==r)
		{
			tree[u]=a[l]%k;
			return;
		}
		int mid=(l+r)>>1;
		build(lc(u),l,mid);
		build(rc(u),mid+1,r);
		push_up(u);
		return;
	}
	inline int query(int u,int l,int r,int ln,int rn)
	{
		if(ln<=l&&r<=rn) return tree[u];
		int res(1);
		int mid=(l+r)>>1;
		if(ln<=mid) res=(1ll*res*query(lc(u),l,mid,ln,rn))%k;
		if(rn>mid) res=(1ll*res*query(rc(u),mid+1,r,ln,rn))%k;
		return res;
	}
};
Segment_Tree seg;
int main()
{
	n=read(),k=read();
	for(register int i=1;i<=n;i++) a[i]=read();
	seg.build(1,1,n); 
	for(register int i=1;i<=n;i++)
	{
		int l=i,r=n,res=-1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(seg.query(1,1,n,i,mid)==0) res=mid,r=mid-1;
			else l=mid+1;
		}
		if(res!=-1) cnt=cnt+(ll)(n-res+1);
	}
	printf("%lld\n",cnt);
	return 0;
}
```

---

## 作者：orz_z (赞：0)

### 题目大意

给定长为 $n$ 的数列 $a$，求有多少对 $(x,y)$ 满足 $k$ 是 $\prod\limits_{i=x}^{i+y\le n}a_i$ 的约数。

### 解题思路

##### 做法一

我会 **二分** ！！！

枚举左端点，然后去找满足条件的右端点。

首先将 $k$ 分解质因数。

可以发现， $a_i$ 分解质因数后，只有和有 $k$ 相同的质因数可以选上，否则对于答案是没有贡献的。

那么就可以将有用的质因数的个数用前缀和维护起来。

可以在 $O(\log n)$ 的时间复杂度内求出所有的对整除影响的质数有多少。

在这个区间内，若对于每个质数的个数均大于等于 $k$ 分解后对应质数的个数，则代表这个区间可以整除 $k$。

时间复杂度为 $O(n\log n\log k+\sqrt k)$。

**CODE**

```cpp
#include <bits/stdc++.h>

using namespace std;

inline int read()
{
    char c = getchar();
    int x = 0, f = 1;
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        x = x * 10 + c - '0', c = getchar();
    return x * f;
}

#define int long long

#define mk(x, y) make_pair(x, y)

const int MAXN = 1e5 + 5;

vector<pair<int, int>> vec;

int a[MAXN], n, k;

int cnt[MAXN][50], ans;

bool Check(int l, int r)
{
    for (int i = 0; i < vec.size(); i++)
        if (cnt[r][i] - cnt[l - 1][i] < vec[i].second)
            return 0;
    return 1;
}

signed main()
{
    n = read(), k = read();
    a[n + 1] = k;
    for (int i = 1; i <= n; i++)
        a[i] = read();
    for (int i = 2; i * i <= k; i++)
    {
        if (k % i == 0)
            vec.push_back(mk(i, 0));
        while (k % i == 0)
        {
            k /= i;
            vec[vec.size() - 1].second++;
        }
    }
    if (k != 1)
        vec.push_back(mk(k, 1));
    for (int i = 1; i <= n + 1; i++)
    {
        int tmp = a[i];
        for (int j = 0; j < vec.size(); j++)
        {
            cnt[i][j] = cnt[i - 1][j];
            while (tmp % vec[j].first == 0)
            {
                tmp /= vec[j].first;
                cnt[i][j]++;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        int l = i, r = n + 1, as = 0;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (Check(i, mid))
                r = mid - 1, as = mid;
            else
                l = mid + 1;
        }
        ans += n - as + 1;
    }
    printf("%lld\n", ans);
    return 0;
}
```



##### 做法二

我会乱推！！！

显然，如果有一个区间 $[l,r]$ 中间的所有数乘积能被 $k$ 整除，则对于一个 $a \leq l,b \leq r$ 的一切区间 $[a,b]$，里面所有数的乘积一定都能被 $k$ 整除。

那么我们只需要找出所有的 **最小合法区间** 即可。

从 $1\to n$ 进行前缀乘积，每次模上 $k$，只要遇到一个合法区间，也就是前缀乘积为 $0$，这时候从这个点立刻回头，从后往前找出这个区间的左端点，找到的区间肯定是最短的。

另外，要避免重复的情况，当开始搜下一个新的区间时候，应当把起始点重置为之前找到的右端点 $+1$。

时间复杂度 $\mathcal O(n \log k )$。 

### CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int _ = 1e5 + 5;

inline int read()
{
    char c = getchar();
    int x = 0, f = 1;
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        x = x * 10 + c - '0', c = getchar();
    return x * f;
}

int n, k;

int a[_];

int now = 1, l = 1, r;

int ans;

signed main()
{
    n = read();
    k = read();
    for (int i = 1; i <= n; ++i)
    {
        a[i] = read();
        now = now * a[i] % k;
        if (!now)
        {
            now = 1;
            for (r = i; now * a[r] % k; r--)
                now = now * a[r] % k;
            ans += (n - i + 1) * (r - l + 1);
            l = r + 1;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：shurongwang (赞：0)

// 将 $k$ 分解质因数, 表示为 $\prod_{i=1}^{m}p_i^{e_i}$

// 将 $a$ 中每个数也质因数分解, 不过只要分解 $p_1$ 到 $p_m$ 的数即可.

// `two pointers` 维护 $l\cdots r$ 之间的 $p_1\cdots p_m$ 的指数和, 并累加答案即可.
```cpp
#include <bits/stdc++.h>

#define null               ""
#define endl               '\n'
#define all(dat)           dat.begin(), dat.end()
#define over(msg)          cout << msg << endl, exit(0);
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fr, to)    for (int i = fr; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

int n, k, a[100005];
num ans;
vector<int> p;
map<int, int> s, cur, dat[100005];

int inline read() {
    int res = 0;
    char c = getchar();
    for (; !isdigit(c); c = getchar());
    for (; isdigit(c); res *= 10, res += c ^ 48, c = getchar());
    return res;
}

// 对 k 分解质因数.
void inline init(int a) {
    for (int i = 2; i * i <= a; ++i) {
        if (a % i)  continue;
        int q = 0;
        p.push_back(i);
        while (a % i == 0) {
            a /= i;
            ++q;
        }
        s[i] = q;
    }
    if (a > 1) {
        p.push_back(a);
        s[a] = 1;
    }
}

// 对 a[id] 关于 p1 ... pm 分解质因数.
void inline fact(int id) {
    int a = ::a[id];
    for (int p : p) {
        if (a % p)  continue;
        int q = 0;
        while (a % p == 0) {
            a /= p;
            ++q;
        }
        dat[id][p] = q;
    }
}

// 加上当前数字的关于 p1 ... pm 的指数和.
void inline ins(int id) {
    foreach (it, dat[id]) {
        cur[it->first] += it->second;
    }
}

// 减去当前数字的关于 p1 ... pm 的指数和.
void inline del(int id) {
    foreach (it, dat[id]) {
        cur[it->first] -= it->second;
    }
}

// 判断当前维护的区间能否整除 k.
bool inline chk() {
    for (int p : ::p) {
        if (cur[p] < s[p])  return 0;
    }
    return 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    n = read();
    k = read();
    init(k);
    cont (i, n) {
        a[i] = read();
        fact(i);
    }
    for (int l = 1, r = 1; l <= n; ++l) {
        // two pointers 维护区间 [l, r) 使得 [l, r), (r > l, r 的位置越小越好) 的乘积可以整除 k.
        del(l - 1);
        while (r <= n && !chk()) {
            ins(r);
            ++r;
        }
        r = max(r, l + 1);
        // 累加答案.
        ans += chk() * (n - r + 2);
    }
    cout << ans << endl;
}
```


---

