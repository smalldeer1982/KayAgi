# Kay and Eternity

## 题目描述

Snow Queen told Kay to form a word "eternity" using pieces of ice. Kay is eager to deal with the task, because he will then become free, and Snow Queen will give him all the world and a pair of skates.

Behind the palace of the Snow Queen there is an infinite field consisting of cells. There are $ n $ pieces of ice spread over the field, each piece occupying exactly one cell and no two pieces occupying the same cell. To estimate the difficulty of the task Kay looks at some squares of size $ k×k $ cells, with corners located at the corners of the cells and sides parallel to coordinate axis and counts the number of pieces of the ice inside them.

This method gives an estimation of the difficulty of some part of the field. However, Kay also wants to estimate the total difficulty, so he came up with the following criteria: for each $ x $ ( $ 1<=x<=n $ ) he wants to count the number of squares of size $ k×k $ , such that there are exactly $ x $ pieces of the ice inside.

Please, help Kay estimate the difficulty of the task given by the Snow Queen.

## 样例 #1

### 输入

```
5 3
4 5
4 6
5 5
5 6
7 7
```

### 输出

```
10 8 1 4 0 
```

# 题解

## 作者：ln001 (赞：3)

算法：扫描线。

## 题意
在平面上给定 $n$ 个点，对每个 $x \in [1, n]$ 分别计算包含了**恰好** $x$ 个点的 $k \times k$ 的矩形的个数。

位置 $(x, y)$ 表示从上往下数第 $i$ 行，从左往右数第 $j$ 列的交点。

## 转化
称原题中的矩形为第一类矩形，有一个很巧妙的转化是从统计矩形个数改为统计**每个点的贡献**。

令某个第一类矩形的右下角为 $(x_1, y_1)$，该矩形能包含点 $(x_2, y_2)$ 等价于 $x_2 \leq x_1 \leq x_2 + k$ 且 $y_2 \leq y_1 \leq y_2 + k$。则能使第一类矩形包含该点的**合法矩形右下角**同样构成一个矩形，称此类矩形为第二类矩形。

题意转化为对每个 $x \in [1, n]$ 分别计算有多少个点**恰好**被 $x$ 个 $k \times k$ 的矩形包含。这里的点为第一类矩形的右下角，即所有整数坐标的点，有效点的数量级是 $O(nk^2)$ 的，离散化之后有效点的数量级是 $O(n)$ 的。

## 扫描线
考虑逐行扫描。取出第二类矩形，得到上下边界，当扫到边界时，在左右边界内暴力修改，然后统计答案就可以了。因为有效点不多，暴力修改复杂度是对的。

[Code](https://vjudge.net/solution/55713527/bspfGjckOesv34FLsg1X)

---

## 作者：duyi (赞：2)

# CF685D Kay and Eternity

考虑用矩形的右上角来代表每个 $k\times k$ 的矩形。

对每个点 $(x,y)$，考虑它能被哪些 $k\times k$ 矩形包含。$k\times k $ 矩形的右上角，必须位于，以 $(x, y)$ 为左下角，以 $(x + k - 1, y + k - 1)$ 为右上角的矩形区域内。

于是每个点 $(x_i,y_i)$ 都对应这样一个矩形区域。

问题转化为：给你 $n$ 个矩形区域，求被覆盖 $1,2,\dots n$ 次的坐标数量（整数坐标）。

考虑**扫描线**。

对一个矩形区域，取出其左右边界，得到 $(x_l,y_l,y_r, 1)$，$(x_r + 1, y_l,y_r, -1)$，这两个四元组。最后的 $1$ 或 $-1$，表示对 $[y_l,y_r]$ 这段区域的覆盖次数，是增加了还是减少了。把这 $2n$ 个四元组按横坐标排序。

考虑如何加入一个四元组并更新答案呢？注意到 $k$ 非常小，也就是 $y_r - y_l + 1 = k\leq 300$。所以可以暴力枚举 $[y_l, y_r]$ 中每个纵坐标，更新它被覆盖的次数，同时更新答案。

因为 $y$ 值很大，需要先离散化。

时间复杂度 $\mathcal{O}(nk)$。

参考代码：

```cpp
// problem:
#include <bits/stdc++.h>
using namespace std;

#define mk make_pair
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
		if (S == T) return '\n';
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
} ztr;
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
} cin;
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
} cout;
} // namespace Fastio
#define cin Fastio :: cin
#define cout Fastio :: cout
#define endl Fastio :: endl
/* --------------- fast io --------------- */ // end

const int MAXN = 1e5;

int n, K, cnt, cnt_val;
ll vals[MAXN * 2 + 5];

struct Event {
	ll x, l, r;
	int t;
	Event() {}
	Event(ll _x, ll _l, ll _r, int _t) {
		x = _x;
		l = _l;
		r = _r;
		t = _t;
	}
} event[MAXN * 2 + 5];

bool cmp(Event lhs, Event rhs) { return lhs.x < rhs.x; }

int c[MAXN * 2 + 5];
ll ans[MAXN + 5];


ll lenx;

void modify(int p, int v) {
	ll len = vals[p + 1] - vals[p];
	ans[c[p]] -= len * lenx;
	c[p] += v;
	assert(c[p] >= 0);
	assert(c[p] <= n);
	ans[c[p]] += len * lenx;
}

int main() {
	cin >> n >> K;
	for (int i = 1; i <= n; ++i) {
		ll x, y;
		cin >> x >> y;
		event[++cnt] = Event(x, y, y + K - 1, 1);
		event[++cnt] = Event(x + K, y, y + K - 1, -1);
		
		vals[++cnt_val] = y;
		vals[++cnt_val] = y + K;
	}
	
	sort(event + 1, event + cnt + 1, cmp);
	
	sort(vals + 1, vals + cnt_val + 1);
	cnt_val = unique(vals + 1, vals + cnt_val + 1) - (vals + 1);
	
	for (int i = 1; i <= cnt; ++i) {
		int j = i;
		while (j + 1 <= cnt && event[j + 1].x == event[i].x)
			++j;
		lenx = event[cnt].x - event[j].x;
		for (int k = i; k <= j; ++k) {
			int l = lower_bound(vals + 1, vals + cnt_val + 1, event[k].l) - vals;
			int r = lower_bound(vals + 1, vals + cnt_val + 1, event[k].r + 1) - vals;
			
			assert(r - l <= K);
			for (int p = l; p < r; ++p) {
				modify(p, event[k].t);
			}
		}
		i = j;
	}
	for (int i = 1; i <= n; ++i) {
		cout << ans[i] << " \n"[i == n];
	}
	return 0;
}
```



---

## 作者：Natori (赞：0)

>[CF685D Kay and Eternity](https://www.luogu.com.cn/problem/CF685D)

经过转化之后就基本上是扫描线板题。

------------
直接统计正方形数是不好做的。我们考虑一个点被正方形包含，等价于以这个点为右上角的正方形包含原来正方形的左下角。我们可以钦定所有正方形的边长都是 $m$，所以这样做显然是正确的。

那么原问题可以被转化成：给定 $n$ 个正方形，两角 $(x_i,y_i),(x_i-m+1,y_i-m+1)$，求有多少整点（即坐标均为整数）被覆盖了 $1,2,\cdots,n$ 次。记录 $ans_i$ 表示被覆盖 $i$ 次的点有多少个，考虑扫描线，求出到当前横坐标时，每个纵坐标被覆盖的次数，累加即可。

注意要将纵坐标和纵坐标减去 $m$ 之后的值一起离散化。同时 $m$ 很小，所以直接暴力枚举纵坐标，时间复杂度 $\mathcal{O}(nm)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
bool Mbegin;
void File_Work(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
}
typedef long long LL;
const int N=1e5*2+8;
int n,m,lsh[N],lshcnt;
struct Option{
	int x,y,val;
	friend bool operator <(Option a,Option b){
		if(a.x!=b.x)
			return a.x<b.x;
		if(a.y!=b.y)
			return a.y<b.y;
		return a.val>b.val;
	}
}ops[N];
int lasx[N],cnt[N];
LL ans[N];
bool Mend;
int main(){
//	File_Work();
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cerr<<fixed<<setprecision(3)<<(&Mbegin-&Mend)/1048576.0<<" MB\n\n\n";
	cin>>n>>m;
	int nn=n*2;
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		ops[i]={x-m,y,1};
		ops[i+n]={x,y,-1};
		lsh[++lshcnt]=y-m;
		lsh[++lshcnt]=y;
	}
	sort(ops+1,ops+nn+1);
	sort(lsh+1,lsh+lshcnt+1);
	lshcnt=unique(lsh+1,lsh+lshcnt+1)-lsh-1;
	for(int i=1;i<=nn;i++){
		int l=lower_bound(lsh+1,lsh+lshcnt+1,ops[i].y-m)-lsh+1;
		int r=lower_bound(lsh+1,lsh+lshcnt+1,ops[i].y)-lsh;
		for(int j=l;j<=r;j++){
			ans[cnt[j]]+=1ll*(ops[i].x-lasx[j])*(lsh[j]-lsh[j-1]);
			lasx[j]=ops[i].x;
			cnt[j]+=ops[i].val;
		}
	}
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<' ';
	cerr<<"\n\n\n"<<fixed<<setprecision(0)<<1e3*clock()/CLOCKS_PER_SEC<<" ms";
	return 0;
}
```

---

