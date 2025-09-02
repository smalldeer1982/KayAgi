# Animals and Puzzle

## 题目描述

猫头鹰 Sonya 将一个 $n\times m$ 的湖拼图给刺猬 Filya，当做他的生日礼物。小伙伴们当即去组装这个拼图，然而有一些部分是空的——在那上面没有图片。  

令有图片部分的贡献为 $1$，没有的为 $0$。对这个拼图编号，行号从上到下为 $1\sim n$ ，列号从左到右为 $1\sim m$ 。  

动物决定继续完成这个拼图，因为它可能更有趣。猫头鹰和刺猬会做出几组询问，每次给出四个整数 $x_1,y_1,x_2,y_2$ ，询问以 $(x_1,y_1)$ 为左上角，$(x_2,y_2)$ 为右下角的区域内，全为 $1$ 的最大正方形的边长。

## 样例 #1

### 输入

```
3 4
1 1 0 1
0 1 1 0
0 1 1 0
5
1 1 2 3
2 1 3 2
3 2 3 4
1 1 3 4
1 2 3 4
```

### 输出

```
1
1
1
2
2
```

# 题解

## 作者：daniEl_lElE (赞：7)

没有整体二分题解，写一发。

首先计算出以每个位置 $(x,y)$ 为左上角最大正方形 $f_{x,y}$。

考虑查询，不难发现可以二分。然而对于每个 $i$ 预处理 $f_{x,y}\geq i$ 的前缀和空间开不下。于是可以想到询问离线整体二分。

每次枚举 $mid$ 计算 $f_{x,y}\geq mid$ 的前缀和，这样做空间是 $O(nm)$，而时间是 $\min(n,m)nm$ 的。仔细分析可以发现带 $\frac{1}{3}$ 常数，直接做即可通过。

细节很少，基本是个整体二分板子。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2,3,"Ofast","inline")
#define int long long
#define double long double
using namespace std;
int a[1005][1005],pre[1005][1005],maxe[1005][1005],ans[1000005],mpre[1005][1005],n,m;
struct qry{
	int a1,a2,b1,b2,pos;
}c[1000005];
vector<qry> vc1,vc2;
void solve(int l,int r,int ql,int qr){
	if(l==r){
		for(int i=ql;i<=qr;i++) ans[c[i].pos]=l-1;
		return ;
	}
	int mid=(l+r)>>1;
	for(int i=1;i<=n-mid+1;i++) for(int j=1;j<=m-mid+1;j++) mpre[i][j]=mpre[i-1][j]+mpre[i][j-1]-mpre[i-1][j-1]+(maxe[i][j]>=mid);
	for(int i=ql;i<=qr;i++){
		int a3=c[i].a2-mid+1,b3=c[i].b2-mid+1;
		if(b3<c[i].b1||a3<c[i].a1) vc1.push_back(c[i]);
		else if(mpre[a3][b3]-mpre[c[i].a1-1][b3]-mpre[a3][c[i].b1-1]+mpre[c[i].a1-1][c[i].b1-1]>0) vc2.push_back(c[i]);
		else vc1.push_back(c[i]);
	}
//	cout<<l<<" "<<r<<" "; 
	int it=ql;
	for(auto v:vc1) c[it++]=v;
	int md=it-1;
	for(auto v:vc2) c[it++]=v;
	vc1.clear(),vc2.clear();
//	cout<<md<<"\n";
	solve(l,mid,ql,md);
	solve(mid+1,r,md+1,qr);
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%lld",&a[i][j]),pre[i][j]=pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1]+a[i][j];
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
		int l=0,r=min(n-i+1,m-j+1);
		while(l<r){
			int mid=(l+r+1)>>1;
			if(pre[i+mid-1][j+mid-1]-pre[i-1][j+mid-1]-pre[i+mid-1][j-1]+pre[i-1][j-1]==mid*mid) l=mid;
			else r=mid-1;
		} 
		maxe[i][j]=l;
//		cout<<l<<" ";
	} 
	int q; scanf("%lld",&q);
	for(int i=1;i<=q;i++) scanf("%lld%lld%lld%lld",&c[i].a1,&c[i].b1,&c[i].a2,&c[i].b2),c[i].pos=i;
	solve(0,min(n,m)+1,1,q);
	for(int i=1;i<=q;i++) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：Pengzt (赞：5)

[CF713D](https://www.luogu.com.cn/problem/CF713D)

有一个相当暴力的 $\mathcal{O}(nmt)$ 的做法是显然的，即对所有点求出以其为右下角的最大的全为 $1$ 的正方形的边长，记为 $f_{i,j}$。然后枚举询问的矩形中的点的 $f$ 的值，和边界判一下后的 $\max$ 就是答案了。

但是这样不好直接维护，由于矩形边界，并不能对 $f$ 取 $\max$。考虑转化为判定性问题，使用二分即可转化为求 $(x_1,y_1)$ 到 $(x_2-mid+1,y_2-mid+1)$ 的 $f$ 的极值是否大于等于 $mid$ 即可。由于查询已经带 $\log$ 了，使用 $\mathcal{O}(n\log^2n)-\mathcal{O}(1)$ 的二维 ST 表即可。

代码：
```cpp
const int N = 1e3 + 10;
int n, m, Q, tot;
int a[N][N], log_2[N], f[11][11][N][N];

int qry(int xa, int ya, int xb, int yb) {
	int k1 = log_2[xb - xa + 1], k2 = log_2[yb - ya + 1];
	return max(f[k1][k2][xa][ya], max(max(f[k1][k2][xb - (1 << k1) + 1][ya], f[k1][k2][xa][yb - (1 << k2) + 1]), f[k1][k2][xb - (1 << k1) + 1][yb - (1 << k2) + 1]));
}

int main() {
	ios
	cin >> n >> m;
	for (int i = 2; i <= max(n, m); i++) log_2[i] = log_2[i >> 1] + 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> a[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (a[i][j])
				f[0][0][i][j] = min(min(f[0][0][i - 1][j], f[0][0][i][j - 1]), f[0][0][i - 1][j - 1]) + 1;
	for (int k = 1; k <= 10; k++)
		for (int i = 1; i <= n - (1 << k) + 1; i++)
			for (int j = 1; j <= m; j++)
				f[k][0][i][j] = max(f[k - 1][0][i][j], f[k - 1][0][i + (1 << (k - 1))][j]);
	for (int k = 1; k <= 10; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m - (1 << k) + 1; j++)
				f[0][k][i][j] = max(f[0][k - 1][i][j], f[0][k - 1][i][j + (1 << (k - 1))]);
	for (int k1 = 1; k1 <= 10; k1++)
		for (int k2 = 1; k2 <= 10; k2++)
			for (int i = 1; i <= n - (1 << k1) + 1; i++)
				for (int j = 1; j <= m - (1 << k2) + 1; j++)
					f[k1][k2][i][j] = max(f[k1][k2 - 1][i][j], f[k1][k2 - 1][i][j + (1 << (k2 - 1))]);
	cin >> Q;
	while (Q--) {
		int xa, ya, xb, yb;
		cin >> xa >> ya >> xb >> yb;
		int l = 1, r = min(xb - xa + 1, yb - ya + 1);
		while (l <= r) {
			 int mid = (l + r) >> 1;
			 if (qry(xa + mid - 1, ya + mid - 1, xb, yb) >= mid) l = mid + 1;
			 else r = mid - 1;
		}
		cout << r << "\n";
	}
	return 0;
}
```

---

## 作者：Creeper_l (赞：1)

原题链接：[CF713D](https://www.luogu.com.cn/problem/CF713D)

题意：给定一个 $n\times m$ 的地图 $a$，$a_{i}$ 为 $0$ 或 $1$。有 $t$ 次询问，每次询问给定一个矩形，求出这个矩形中最大的由 $1$ 构成的正方形的边长是多少。

首先考虑预处理出 $d_{i,j}$ 表示以 $(i,j)$ 为左上角的最大正方形边长是多少。

对于每一次询问可以二分一个 $mid$，判断 $mid$ 是否可行就相当于是查询 $d$ 的一个二维区间中的最大值，如果这个最大值大于等于 $mid$ 说明可行，否则不可行，注意如果这个二维区间的长宽的最小值比 $mid$ 小的话，那么肯定不可行。而二维区间 $\max$ 直接用二维 ST 表维护即可，时间复杂度 $O(n^{2} \log ^{2}n+t \log n)$。

预处理 $d$ 数组可以用 $O(n^{2} \log n)$ 的二分或者 $O(n^{2})$ 的 dp。

```cpp
#include<bits/stdc++.h>
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
		while (c == ' ' || c == '\n') c = getchar();
		return *this;
	}
	Reader& operator >> (char* str) {
		int len = 0;
		char c = getchar();
		while (c == ' ' || c == '\n') c = getchar();
		while (c != ' ' && c != '\n' && c != '\r') { // \r\n in windows
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
using namespace std;
#define re register
const int MAXN = 1e3 + 1;
int n,m,sum[MAXN][MAXN],t,x,y,p,q;
bool a[MAXN][MAXN];
short d[MAXN][MAXN],st[MAXN][MAXN][11][11];
inline bool check(int X,int Y,int len)
{
	re int P = X + len - 1,Q = Y + len - 1;
	if(sum[P][Q] - sum[P][Y - 1] - sum[X - 1][Q] + sum[X - 1][Y - 1] == len * len) return true;
	else return false;
}
inline bool solve(int mid)
{
	re int P = p - mid + 1,Q = q - mid + 1;//(x,y),(P,Q)
	int f = __lg(P - x + 1),l = __lg(Q - y + 1);
	if(P < x || Q < y) return false;
	int mx = max(max(st[x][y][f][l],st[P - (1 << f) + 1][y][f][l]),max(st[x][Q - (1 << l) + 1][f][l],st[P - (1 << f) + 1][Q - (1 << l) + 1][f][l]));
//	cout << "x = " << x << " y = " << y << " P = " << P << " Q = " << Q << " " << "max = " << mx << " mid = " << mid<<" f = " << f << " l = " << l << endl;
	if(mx >= mid) return true;
	else return false;
}
signed main()
{
	cin >> n >> m;
	for(int i = 1;i <= n;i++) for(int j = 1;j <= m;j++) cin >> a[i][j];
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
		{
			re int l = 1,r = min(n - i + 1,m - j + 1);
			while(l <= r)
			{
				int mid = (l + r) >> 1;
				if(check(i,j,mid)) d[i][j] = mid,l = mid + 1;
				else r = mid - 1;
			}
			st[i][j][0][0] = d[i][j];
		}
	for(int i = 0;i <= __lg(n) + 1;i++)
		for(int j = 0;j <= __lg(m) + 1;j++)
		{
			if(i == 0 && j == 0) continue;
			for(int s = 1;s <= (n - (1 << i) + 1);s++)
				for(int e = 1;e <= (m - (1 << j) + 1);e++)
				{
//					if(s + (1 << i) > n || e + (1 << j) > m) continue;
					if(i != 0) st[s][e][i][j] = max(st[s][e][i - 1][j],st[s + (1 << i - 1)][e][i - 1][j]);
					else st[s][e][i][j] = max(st[s][e][i][j - 1],st[s][e + (1 << j - 1)][i][j - 1]);
//					cout << s << " " << e << " " << s + (1 << i) - 1 << " " << e + (1 << j) - 1 << " " << st[s][e][i][j] << endl;
				}
		}
	cin >> t;
	while(t--)
	{
		cin >> x >> y >> p >> q;
		int l = 0,r = max(n,m),ans = 0;
		while(l <= r)
		{
			int mid = (l + r) >> 1;
			if(solve(mid) == true) ans = mid,l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
/*
3 4
1 1 0 1
0 1 1 0
0 1 1 0
5
1 1 2 3
2 1 3 2
3 2 3 4
1 1 3 4
1 2 3 4
*/

```


---

## 作者：BINYU (赞：1)

## 题意

给一个 $01$ 矩阵，多次求在给定区间内最大的全 $1$ 正方形边长。

## 思路

容易想到二分：

先预处理出以每个位置为右下角的最大合法正方形的边长 $mx_{i,j}$，然后对于每个询问，我们二分边长 $mid$，设当前询问的区间左上角为 $(x_1,y_1)$，右下角为 $(x_2,y_2)$，则能取到 $mid$ **当且仅当** 在以 $(x_1+mid-1,y_1+mid-1)$ 为 $(x_2,y_2)$ 对角的矩形中有 $mx_{i,j}$ 不小于 $mid$ 的位置。

于是就可以用二维 ST 表。时间复杂度 $O(n^2\log^2n+t\log n)$（假设 $n$ 与 $m$ 同级）空间复杂度 $O(n^2\log^2n+t)$。

还有另一种思路：整体二分。

我们将所有询问一起处理，对于当前的 $mid$，把 $mx \ge mid$ 的位置看成 $1$，否则为 $0$，一个询问能取到 $mid$ **当且仅当** 在以 $(x_1+mid-1,y_1+mid-1)$ 为 $(x_2,y_2)$ 对角的矩形中有 $1$，可以使用前缀和优化，时间复杂度 $O(n^3 + t\log n)$（假设 $n$ 与 $m$ 同级），但是每次我们需要处理新值的区间只有 $(mid,mid)$ 至 $(n,m)$，所以常数比较小，也可以过。空间复杂度 $O(n^2+t)$。

---

## 作者：SJH__qwq (赞：0)

就当是二维 RMQ 的板子了。

考虑首先预处理出 $a_{i,j}$ 表示 $(i,j)$ 为左上角，那么正方形的边长最大可以是多少。

然后对这个东西跑一边二维 RMQ 求子矩阵的 `max`，二分一下答案，判断是否可行即可。判定直接用二维 RMQ 即可。

时间复杂度为 $O(n^2\log^2n)$。又卡常又卡空。

---

