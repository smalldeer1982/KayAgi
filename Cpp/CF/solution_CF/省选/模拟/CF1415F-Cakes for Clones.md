# Cakes for Clones

## 题目描述

You live on a number line. You are initially (at time moment $ t = 0 $ ) located at point $ x = 0 $ . There are $ n $ events of the following type: at time $ t_i $ a small cake appears at coordinate $ x_i $ . To collect this cake, you have to be at this coordinate at this point, otherwise the cake spoils immediately. No two cakes appear at the same time and no two cakes appear at the same coordinate.

You can move with the speed of $ 1 $ length unit per one time unit. Also, at any moment you can create a clone of yourself at the same point where you are located. The clone can't move, but it will collect the cakes appearing at this position for you. The clone disappears when you create another clone. If the new clone is created at time moment $ t $ , the old clone can collect the cakes that appear before or at the time moment $ t $ , and the new clone can collect the cakes that appear at or after time moment $ t $ .

Can you collect all the cakes (by yourself or with the help of clones)?

## 说明/提示

In the first example you should start moving towards $ 5 $ right away, leaving a clone at position $ 1 $ at time moment $ 1 $ , and collecting the cake at position $ 2 $ at time moment $ 2 $ . At time moment $ 5 $ you are at the position $ 5 $ and collect a cake there, your clone collects the last cake at time moment $ 6 $ .

In the second example you have to leave a clone at position $ 0 $ and start moving towards position $ 5 $ . At time moment $ 1 $ the clone collects a cake. At time moment $ 2 $ you should create a new clone at the current position $ 2 $ , it will collect the last cake in future. You will collect the second cake at position $ 5 $ .

In the third example there is no way to collect all cakes.

## 样例 #1

### 输入

```
3
2 2
5 5
6 1```

### 输出

```
YES```

## 样例 #2

### 输入

```
3
1 0
5 5
6 2```

### 输出

```
YES```

## 样例 #3

### 输入

```
3
2 1
5 5
6 0```

### 输出

```
NO```

# 题解

## 作者：KokiNiwa (赞：6)

### 题目概要
一个人初始在 $(0,0)$ ，每次可以向左向右走一格，有 $n$ 个任务 $(t_i,x_i)$ 表示时刻 $t_i$ 他或者他的克隆必须在 $x_i$ 这个位置上。每次他到达一个位置可以消除以前的克隆并新增一个新的在当前位置上的克隆。问是否能够完成所有任务。
### 题解
设 $f_{i,j}$ 表示 $t_i$ 时刻人在 $x_i$ ，现在分身在 $j$ 是否可行。
考虑转移：
+ 如果第 $i-1$ 个任务是用真身完成的。那么直接从 $f_{i-1},j$ 转移即可。很明显有克隆之后更换这样的转移不需要。
+ 如果是克隆完成的第 $i-1$ 个任务，有两种可能：
	+ 克隆是在完成 $1\sim i-2$ 所有任务之后到 $i-1$ 放置的。
    + 克隆是在完成 $1\sim i-2$ 的过程中放置的。$i-2$ 必须通过真身完成（因为克隆得留给 $i-1$）。对应从 $f_{i-2,i-1}$ 转移。

我们发现对于第二条一个转移无法进行。因此考虑增加状态 $g_i$ 表示完成 $1\sim i-1$ 之后到 $i$ 放置克隆的最小时间。那么就可以完成 $f$ 的转移了。怎么完成 $g$ 的转移呢：
+ $i-1$ 是通过克隆完成的
	+ $i-2$ 是通过真身完成的，也就是从 $f_{i-2,i-1}$ 转移。
    + $i-2$ 也是通过克隆完成的，从 $g_{i-1}$ 转移。
+ $i-1$ 是通过真身完成的
	+ 从 $f_{i,j}$ 转移。

有人说这里可能漏了从 $i-1$ 是真身完成但是那时还没有克隆的方案。但这无伤大雅，因为其实这样的方案一定不如 $g_{i-1}$ 更优。

注意在 $g_i>t_i$ 的时候把 $g_i$ 赋值为 $\inf$ 。

### 代码
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long LL;
const LL CN=5e3+5,inf=1e9+10;
LL N,x[CN],t[CN];
bool f[CN][CN];
LL g[CN];
LL dis(LL x,LL y){return ((x-y)<0)?(y-x):(x-y);}
void tran_f(LL i,LL j){
	if(i>=3&&f[i-2][i-1]&&t[i]>=max(t[i-1],t[i-2]+dis(x[i-2],x[j]))+dis(x[j],x[i]))
		return f[i][j]=1,void(); // this
	if(f[i-1][j]&&dis(x[i],x[i-1])<=dis(t[i],t[i-1]))return f[i][j]=1,void();
	if(t[i]>=max(t[i-1],dis(x[i-1],x[j])+g[i-1])+dis(x[j],x[i]))
		return f[i][j]=1,void();
}
void tran_g(LL i){
	if(i>=3&&f[i-2][i-1])g[i]=max(t[i-2]+dis(x[i-2],x[i]),t[i-1]); // this
	for(LL j=i;j<=N;++j)if(f[i-1][j])
		g[i]=min(g[i],t[i-1]+dis(x[i-1],x[i]));
	g[i]=min(g[i],max(dis(x[i],x[i-1])+g[i-1],t[i-1]));
	if(g[i]>t[i])g[i]=inf;
}
int main(){
	freopen("f.in","r",stdin);
	freopen("f.out","w",stdout);
	scanf("%lld",&N);
	for(LL i=1;i<=N;++i)scanf("%lld%lld",&t[i],&x[i]);
	g[0]=0;for(LL i=1;i<=N;++i)g[i]=inf;
	f[0][0]=1;
	for(LL i=1;i<=N;++i){
		for(LL j=i+1;j<=N;++j)tran_f(i,j);
		tran_g(i);
	}
	if(g[N]<=t[N]||f[N-1][N])printf("YES\n"); // this
	else printf("NO\n");
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```

---

## 作者：_tourist_ (赞：5)

按时间排序，令$mi[i]$表示当前在第$i$个点，$i-1$及之前所有的点都已经接到或者用分身接到所要用的最短时间（用分身接这个点），$dp[i][j]$表示当前在点$i$，分身留给之后的点$j$是否可行。($j>i$)

然后分情况讨论：

一、分身是留给当前点——那么我们在$mi[i]$的时间放下分身，然后有两种选择：

1.直接到达$i+1$，更新$mi[i+1]$。

2.先往后到达$i+1$后面的点，放下分身，然后再赶回$i+1$，即更新$dp[i+1][j]$

上述两种都要注意一定要等到$i$接到以后才能更新。

二、分身是留给后面的——那么当前在点$i$一定是$t[i]$。

1.分身不是留给$i+1$的，那么只能老老实实等$t[i]$接到以后然后赶到$i+1$，如果可以赶到那么$dp[i+1][j]|=dp[i][j]$

2.分身是留给$i+1$的，再分两种讨论

(1)直接走到$i+2$，更新$i+2$的$mi$。

(2)先冲到$i+2$之后的放下分身，然后再赶回$i+2$。

注意和$i+1$分身接到的时间取$max$。

还有一个注意点，如果一个点最终的$mi[i]$大于了$t[i]$，并不意味着整个不可行，只是不可能存在处于$i$，前面$i-1$个全部搞定了的情况（还可能是分身留给他），直接跳过这一层的转移即可。
```cpp
int _abs(int x){return x<0 ? -x : x;}
int t[N],a[N];
int n,mi[N]; 
bool dp[N][N]; 
bool check(int x,int y){
    return t[y]-t[x]>=_abs(a[x]-a[y]);
}
 
signed main()
{
    n=read();
    for(int i=1;i<=n;i++) t[i]=read(),a[i]=read();
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=n;i++) mi[i]=INF;
    t[0]=0; a[0]=0;
    mi[0]=0;
    for(int i=0;i<n;i++){
        if(mi[i]>t[i]) continue;
        //the clone is in the ith position-mintime(mi) 
        //1.go to the i+1th and put the clone at i+1th position
        checkmin(mi[i+1],max(mi[i]+_abs(a[i]-a[i+1]),t[i]));
        //2.go to another position-j,put the clone,and go back to the i+1th position
        //remember to wait for the ith clone to be used
        for(int j=i+2;j<=n;j++){
            int go=max(t[i],mi[i]+_abs(a[i]-a[j]));
            int back=_abs(a[j]-a[i+1]);
            if(go+back<=t[i+1]) dp[i+1][j]=1;
        }
 
        //the clone is not in the ith position
        //1.the clone is not used for the i+1th
        for(int j=i+2;j<=n;j++) if(check(i,i+1)) dp[i+1][j]|=dp[i][j];
        //2.the clone is for the i+1th
        //2(1):directly goto the i+2th, update the minitime of i+2th(wait for the i+1th)
        if(dp[i][i+1]) checkmin(mi[i+2],max(t[i+1],t[i]+_abs(a[i]-a[i+2])));
        //2(2):go to another position j,and go back to the i+2th
        if(dp[i][i+1]){
            for(int j=i+3;j<=n;j++){
                int go=max(t[i+1],t[i]+_abs(a[i]-a[j]));
                int back=_abs(a[j]-a[i+2]);
                if(go+back<=t[i+2]) dp[i+2][j]=1;
            }
        }
    }
    if(mi[n]<=t[n]||dp[n-1][n]) puts("YES");
    else puts("NO");
    return 0;
}
```

---

## 作者：chenxia25 (赞：2)

dyls nb 嗷，切 2900 的题！~~虽然我也没看题解（咋又装起来了）~~

~~然后我的复杂度好像比 dyls 优~~

---

把这题 A 掉的时候是**假的**热泪盈眶……周天搞了一下午这个题到最后都没调出来，今天竟然一下子就把错误找出来了，感动中国（

交了 22 次，有[提交记录](https://codeforces.ml/submissions/tzcWhoIsYcxsCleverestSon/contest/1415)为证，虽然远抵不上 455D 这个交了 50 次的（

---

~~下面扯正题~~

我们考虑按照时间顺序，每个蛋糕是被本人还是被分身收集了，这样一个 01 序列。考虑对一个 particular 的 01 序列考虑是否能够实现。

我们考虑以时间为横轴，位置为纵轴建直角坐标系，然后就可以画出这个人的行动轨迹。那么这个 01 序列的限制是分 0 和 1：被本人收集那就是行动轨迹必须经过这个点；被分身收集的话，那就是对于每个这样的蛋糕，行动轨迹必须穿过 $y=$ 当前蛋糕位置，并且左端是上一个蛋糕的时间，右端是这个蛋糕的时间，这样一条水平线。注意到本人收集的蛋糕能一定程度上的确定行动轨迹，比较稳定，于是我们以它为阶段考虑。

那么两个相邻的被本人收集蛋糕之间会是什么样的呢。假设至少存在一个分身收集的蛋糕，没有的话后面另说。那么显然最左边后面的都一定是在本阶段内被穿过；而最左边的那个所对应的水平线一定穿过了左端点所在竖直线，也就是说它可能先于或后于左端点被收集。同理，右端点后面第一个也可能先于右端点被收集。这样一来我们可以很自然的想出一个 DP 状态：$dp_{i,0/1}$ 表示考虑到蛋糕 $i$ 且 $i$ 被本人收集，然后 $i+1$ 是否被分身收集且在本阶段内被收集，这种状态是否能做到。

转移的话就直接枚举本阶段左端点 $j$。然后显然需要从 $j\to i$，我们可以预处理出从 $j$ 开始出发到某个地方一连串都是被分身收集，的最小到达时间（贪心就可以了，注意每次需要和水平线左端点取 $\max$）。因为 $j$ 对应状态可能是 $0/1$，所以预处理的时候需要分开考虑是否需要经过 $j+1$。然后也需要根据 $i$ 对应 $0/1$ 判断是否需要经过 $i+1$。这时候注意也要和水平线左端点取 $\max$，这就是导致我调这么长时间的原因。

但这样考虑还不完备，前面遗留了一个问题：本阶段内可能不存在被分身收集的点。这种情况稍微有点麻烦。那么就会出现这种现象：$i+1$ 的水平线会贯穿好几条竖直线，那么前面那些竖直线所对应的右边的被分身收集的点就不再是 $+1$ 了，而要再往后集中到 $i+1$。

不过还是可做的。几经尝试，发现可以枚举 $i+1$ 是在哪两个相邻蛋糕 $j,j+1$ 之间被收集的。又分为两类：
1. 两个蛋糕都是被本人收集。这种情况较简单，因为只能是 $dp_{j,0}$，$j+1$ 本来就不是分身收集的。然后需要 $j\to i+1\to j+1\to i$，$j+1\to i$ 可以区间 DP 预处理；
1. $j$ 是分身收集，$j+1$ 是本人收集。我们考虑再枚举往左数第一个本人收集的位置 $k$，那么 $k\to j$ 之间按照之前说的 DP 转移方式考虑，对后面列式计算是否可以到 $j+1$ 的贡献是一个关于 $k,j$ 的初始时间 DP 值。然后就判 $j\to i+1\to j+1\to i$，老样子。这样子是三方的，然后注意到 $k$ 唯一产生的贡献就是一个只关于 $k,j$ 的东西，于是可以对 $j$ 前缀预处理一下，就变成平方了。

虽然也要分挺多类，但是代码只有 2.5k，不像 dy 有 6k（）。而且这样一个 2900 题，和上面那个 2600 题比起来，已经很幸福了（

**_[code](https://www.luogu.com.cn/paste/2kfbz50e)_**

---

## 作者：duyi (赞：1)

# CF1456D Cakes for Clones

[题目链接](http://codeforces.com/contest/1456/problem/D)

## 本题题解

设 $\text{dp}(i,j) \in\{0,1\}$ 表示按时间顺序考虑了前 $i$ 个蛋糕，当前时间是第 $t_i$ 秒，且你恰好位于位置 $x_i$，你的替身位于位置 $x_j$，这种状态是否可能实现。

发现转移总是把一段连续的位置设为 $1$，所以将第二维按 $x$ 排序后，转移就是一个区间覆盖，可以用差分维护。

确定要覆盖的区间时，可能需要二分查找。故时间复杂度 $\mathcal{O}(n^2\log n)$。

该做法可能需要一些分类讨论。请读者自行完成。

## 参考代码

```cpp
// problem: CF1456D
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

/* --------------- fast io --------------- */ // begin
namespace Fread {
const int SIZE = 1 << 21;
char buf[SIZE], *S, *T;
inline char getchar() {
	if (S == T) {
		T = (S = buf) + fread(buf, 1, SIZE, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
} // namespace Fread
namespace Fwrite {
const int SIZE = 1 << 21;
char buf[SIZE], *S = buf, *T = buf + SIZE;
inline void flush() {
	fwrite(buf, 1, S - buf, stdout);
	S = buf;
}
inline void putchar(char c) {
	*S++ = c;
	if (S == T) flush();
}
struct NTR {
	~ NTR() { flush(); }
}ztr;
} // namespace Fwrite
#ifdef ONLINE_JUDGE
	#define getchar Fread :: getchar
	#define putchar Fwrite :: putchar
#endif
namespace Fastio {
struct Reader {
	template<typename T>
	Reader& operator >> (T& x) {
		char c = getchar();
		T f = 1;
		while (c < '0' || c > '9') {
			if (c == '-') f = -1;
			c = getchar();
		}
		x = 0;
		while (c >= '0' && c <= '9') {
			x = x * 10 + (c - '0');
			c = getchar();
		}
		x *= f;
		return *this;
	}
	Reader& operator >> (char& c) {
		c = getchar();
		while (c == '\n' || c == ' ') c = getchar();
		return *this;
	}
	Reader& operator >> (char* str) {
		int len = 0;
		char c = getchar();
		while (c == '\n' || c == ' ') c = getchar();
		while (c != '\n' && c != ' ') {
			str[len++] = c;
			c = getchar();
		}
		str[len] = '\0';
		return *this;
	}
	Reader(){}
}cin;
const char endl = '\n';
struct Writer {
	template<typename T>
	Writer& operator << (T x) {
		if (x == 0) { putchar('0'); return *this; }
		if (x < 0) { putchar('-'); x = -x; }
		static int sta[45];
		int top = 0;
		while (x) { sta[++top] = x % 10; x /= 10; }
		while (top) { putchar(sta[top] + '0'); --top; }
		return *this;
	}
	Writer& operator << (char c) {
		putchar(c);
		return *this;
	}
	Writer& operator << (char* str) {
		int cur = 0;
		while (str[cur]) putchar(str[cur++]);
		return *this;
	}
	Writer& operator << (const char* str) {
		int cur = 0;
		while (str[cur]) putchar(str[cur++]);
		return *this;
	}
	Writer(){}
}cout;
} // namespace Fastio
#define cin Fastio :: cin
#define cout Fastio :: cout
#define endl Fastio :: endl
/* --------------- fast io --------------- */ // end

const int MAXN = 5000;
int n;
bool dp[MAXN + 5][MAXN + 5];

struct Event {
	int t, x, id;
};
Event a[MAXN + 5], b[MAXN + 5];
bool cmp_t(Event e1, Event e2) { return e1.t < e2.t; }
bool cmp_x(Event e1, Event e2) { return e1.x < e2.x; }

int xs[MAXN + 5], t_to_x[MAXN + 5];

struct StaticRangeCover {
	int c[MAXN + 5];
	void range_cover(int l, int r) {
		assert(l <= r);
		c[l]++;
		c[r + 1]--;
	}
	void getres(bool* res) {
		for (int i = 1; i <= n; ++i) {
			c[i] += c[i - 1];
			res[i] = (c[i] > 0);
		}
	}
	void clear() {
		memset(c, 0, sizeof(c));
	}
	StaticRangeCover() {}
};
StaticRangeCover T[MAXN + 5];

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i].t >> a[i].x;
	}
	sort(a + 1, a + n + 1, cmp_t);
	for (int i = 1; i <= n; ++i) {
		a[i].id = i;
		b[i] = a[i];
	}
	sort(b + 1, b + n + 1, cmp_x);
	for (int i = 1; i <= n; ++i) {
		t_to_x[b[i].id] = i;
		xs[i] = b[i].x;
	}
	
	dp[0][0] = 1;
	for (int i = 0; i < n; ++i) {
		T[i].getres(dp[i]);
		
		bool flag = 0;
		for (int j = 0; j <= n; ++j) if (dp[i][j]) { flag = 1; break; }
		if (!flag) continue;
		
		if (i + 1 <= n && a[i + 1].t - a[i].t >= abs(a[i + 1].x - a[i].x)) {
			for (int j = 1; j <= n; ++j)
				if (dp[i][j])
					T[i + 1].range_cover(j, j);
			
			int l, r;
			l = t_to_x[i];
			r = t_to_x[i + 1];
			if (i == 0) {
				if (a[1].x >= 0) {
					l = lob(xs + 1, xs + n + 1, 0) - xs;
				} else {
					l = upb(xs + 1, xs + n + 1, 0) - xs - 1;
				}
			}
			
			if (l > r)
				swap(l, r);
			T[i + 1].range_cover(l, r);
			
			int t_rest = a[i + 1].t - (a[i].t + abs(a[i + 1].x - a[i].x));
			t_rest /= 2;
			l = lob(xs + 1, xs + n + 1, a[i + 1].x - t_rest) - xs;
			r = upb(xs + 1, xs + n + 1, a[i + 1].x + t_rest) - xs - 1;
			T[i + 1].range_cover(l, r);
			l = lob(xs + 1, xs + n + 1, a[i].x - t_rest) - xs;
			r = upb(xs + 1, xs + n + 1, a[i].x + t_rest) - xs - 1;
			if (l <= r)
				T[i + 1].range_cover(l, r);
		}
		
		if (i + 2 <= n && a[i + 2].t - a[i].t >= abs(a[i + 2].x - a[i].x) && dp[i][t_to_x[i + 1]]) {
			int l, r;
			if (a[i].x < a[i + 2].x) {
				l = lob(xs + 1, xs + n + 1, min(a[i].x + (a[i + 1].t - a[i].t), a[i + 2].x)) - xs;
				r = t_to_x[i + 2];
				
				T[i + 2].range_cover(l, r);
			} else {
				l = t_to_x[i + 2];
				r = upb(xs + 1, xs + n + 1, max(a[i].x - (a[i + 1].t - a[i].t), a[i + 2].x)) - xs - 1;
				
				T[i + 2].range_cover(l, r);
			}
			
			int t_rest = a[i + 2].t - (a[i].t + abs(a[i + 2].x - a[i].x));
			int tt;
			tt = min(t_rest / 2, a[i + 2].t - a[i + 1].t);
			l = lob(xs + 1, xs + n + 1, a[i + 2].x - tt) - xs;
			r = upb(xs + 1, xs + n + 1, a[i + 2].x + tt) - xs - 1;
			T[i + 2].range_cover(l, r);
			
			tt = min(t_rest / 2, t_rest - (a[i + 1].t - a[i].t));
			if (tt >= 0) {
				l = lob(xs + 1, xs + n + 1, a[i].x - tt) - xs;
				r = upb(xs + 1, xs + n + 1, a[i].x + tt) - xs - 1;
				T[i + 2].range_cover(l, r);
			}
		}
		
		int t = a[i].t;
		int j;
		for (j = i + 2; j <= n; ++j) {
			// insert: j - 1
			
			int newt = max(a[j - 2].t, t + abs(a[j - 1].x - a[j - 2].x));
			// t 是可以离开 j - 2 的最小时间
			// newt 是可以离开 j - 1 的最小时间
			if (j == i + 3 && dp[i][t_to_x[i + 1]]) {
				ckmin(newt, max(a[i + 1].t, a[i].t + abs(a[j - 1].x - a[i].x)));
			}
			if (newt >= a[j - 1].t) {
				break;
			}
			
			t = newt; // 可以离开 j - 1 的最小时间
			int t_rest = a[j].t - (t + abs(a[j].x - a[j - 1].x));
			if (t_rest >= 0) {
				int tt, l, r;
				tt = min(t_rest / 2, a[j].t - a[j - 1].t);
				l = lob(xs + 1, xs + n + 1, a[j].x - tt) - xs;
				r = upb(xs + 1, xs + n + 1, a[j].x + tt) - xs - 1;
				T[j].range_cover(l, r);
				
				tt = min(t_rest / 2, t_rest - (a[j - 1].t - t));
				if (tt >= 0) {
					l = lob(xs + 1, xs + n + 1, a[j - 1].x - tt) - xs;
					r = upb(xs + 1, xs + n + 1, a[j - 1].x + tt) - xs - 1;
					T[j].range_cover(l, r);
				}
				
				tt = min(a[j - 1].t, a[j].t - abs(a[j].x - a[j - 1].x));
				if (a[j - 1].x < a[j].x) {
					l = lob(xs + 1, xs + n + 1, min(a[j - 1].x + (a[j - 1].t - tt), a[j].x)) - xs;
					r = t_to_x[j];
					
					T[j].range_cover(l, r);
				} else {
					l = t_to_x[j];
					r = upb(xs + 1, xs + n + 1, max(a[j - 1].x - (a[j - 1].t - tt), a[j].x)) - xs - 1;
					
					T[j].range_cover(l, r);
				}
			}
		}
		
		if (j >= i + 3 || !dp[i][t_to_x[i + 1]])
			continue;
		t = a[i].t;
		for (int j = i + 3; j <= n; ++j) {
			// insert: j - 1
			
			int newt = max(a[j - 2].t, t + abs(a[j - 1].x - a[(j == i + 3) ? i : j - 2].x));
			// t 是可以离开 j - 2 的最小时间
			// newt 是可以离开 j - 1 的最小时间
			if (newt >= a[j - 1].t) {
				break;
			}
			
			t = newt; // 可以离开 j - 1 的最小时间
			int t_rest = a[j].t - (t + abs(a[j].x - a[j - 1].x));
			if (t_rest >= 0) {
				int tt;
				tt = min(t_rest / 2, a[j].t - a[j - 1].t);
				int l, r;
				l = lob(xs + 1, xs + n + 1, a[j].x - tt) - xs;
				r = upb(xs + 1, xs + n + 1, a[j].x + tt) - xs - 1;
				T[j].range_cover(l, r);
				
				tt = min(t_rest / 2, t_rest - (a[j - 1].t - t));
				if (tt >= 0) {
					l = lob(xs + 1, xs + n + 1, a[j - 1].x - tt) - xs;
					r = upb(xs + 1, xs + n + 1, a[j - 1].x + tt) - xs - 1;
					T[j].range_cover(l, r);
				}
				
				tt = min(a[j - 1].t, a[j].t - abs(a[j].x - a[j - 1].x));
				if (a[j - 1].x < a[j].x) {
					l = lob(xs + 1, xs + n + 1, min(a[j - 1].x + (a[j - 1].t - tt), a[j].x)) - xs;
					r = t_to_x[j];
					
					T[j].range_cover(l, r);
				} else {
					l = t_to_x[j];
					r = upb(xs + 1, xs + n + 1, max(a[j - 1].x - (a[j - 1].t - tt), a[j].x)) - xs - 1;
					
					T[j].range_cover(l, r);
				}
			}
		}
	}
	
	T[n].getres(dp[n]);
	bool ans = 0;
	for (int i = 1; i <= n; ++i) ans |= dp[n][i];
	if (n > 1) {
		ans |= dp[n - 1][t_to_x[n]];
	}
	cout << (ans ? "YES" : "NO") << endl;
	return 0;
}
```







---

