# Map

## 题目描述

给你一个 $n\times m$ 的矩形，你需要从中依次选出若干个 $a\times b$ 矩形直至无法再选择，依次选择的矩形满足以下条件：

1. 此矩形不能和之前的矩形重叠。
1. 这个矩形在所有可选矩形中的花费最小。一个矩形的花费为：此矩形的权值和 $-$ 此矩形最小权值 $\times $ 矩形大小。
1. 如果有多个花费最小的矩形，则优先选行坐标最小的，其次选列坐标最小的。

## 样例 #1

### 输入

```
2 2 1 2
1 2
3 5
```

### 输出

```
2
1 1 1
2 1 2
```

## 样例 #2

### 输入

```
4 4 2 2
1 5 3 4
2 7 6 1
1 1 2 2
2 2 1 2
```

### 输出

```
3
3 1 2
3 3 3
1 2 9
```

# 题解

## 作者：Fading (赞：2)

很奇怪的一道题！

看了英文题面然后做错了。。。

英文题面说
$\text{If this position is not unique, he chooses the leftmost one.}$

选择横坐标最小的点。

但是应该优先选纵坐标最小，如果纵坐标相同再选横坐标最小的点。。。

这是为什么呢？？？？？？

好吧正确思路应该比较好想：

先求出以每一个位置为左上角的矩阵的花费，然后使用优先队列或堆，每一次取出花费最小的点就好了。

但是建筑物不可以建在建筑物上（废话！）

所以我们每一次取出点$(pos_x,pos_y),$就给以

$$(max(1,pos_x-a+1),max(1,pos_y-b+1))$$

为左上角的和以

$$(pos_x+a-1,pos_y+b-1)$$

为右下角的矩阵中每一个点都打上一个标记。如果以后从堆中取出的点被打上了标记，就不可以建造了（否则会重叠），直接弹出。（可以画画图想想为什么）

关于打标记，我一开始想的是二维树状数组，但是后来发现每一个点如果按照上述方式操作，最多只会被打上两次标记，所以暴力赋值就可以了。

$AC$后发现不需要用堆，直接排个序就可以了。。。不过仿佛堆还好写一点？？？

你问如何求出每一个子矩阵的花费？

设$M$为矩阵中最小的数，$S$为矩阵中所有数的和，可以发现花费就等于

$$S-(M\times a\times b)$$

$S$可以用二维前缀和求出，$M$用单调队列[就可以预处理出来](https://www.luogu.org/problemnew/show/P2216)。

这样就可以$AC$了

我的实现非常奇怪，代码如下：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ffd(x) memset(x,0,sizeof(x))
using namespace std;
int a,b,n,m,xmin[1004][1004],cnt,ymin[1004][1004],hmin,tmin,dlmin[1004];
ll ans[1000003][3],aa[1004][1004];
struct sum{
	ll sum[1222][1222];
	void init(int n,int m){
		for (int i=1;i<=n;i++){
			for (int j=1;j<=m;j++){
				sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+aa[i][j];
			}
		}
	}
	inline ll query(int nn,int mm,int n,int m){
		return sum[n][m]-sum[nn-1][m]-sum[n][mm-1]+sum[nn-1][mm-1];
	}
}S;
inline void check(int pos){
    while (hmin<=tmin&&dlmin[hmin]<=pos) hmin++;
}
inline void addmin(int z,int xx){
    while (hmin<=tmin&&aa[z][dlmin[tmin]]>aa[z][xx]) tmin--;
    dlmin[++tmin]=xx;
}
inline ll read(){
    ll x=0;char ch=getchar();ll f=1;
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return x*f;
}
priority_queue<pair<ll,pair<ll,ll> > > dl;
//实现采用优先队列+pair，主要是因为比较懒
//我们要小根堆，所以我把里面所有的数都存了负值
bool vis[1201][1201];
int main(){
    scanf("%d%d%d%d",&n,&m,&a,&b);
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            aa[i][j]=read();
        }
    }
    for (int i=1;i<=n
    ;i++){
        hmin=1;tmin=0;ffd(dlmin);
        for (int j=1;j<=m;j++){
            addmin(i,j);
            if (j>=b){
                check(j-b);
                xmin[i][j-b+1]=aa[i][dlmin[hmin]];
            }
        }
    }
    for (int j=1;j<=m-b+1;j++){
        hmin=1;tmin=0;ffd(dlmin);
        for (int i=1;i<=n;i++){
            while (hmin<=tmin&&xmin[dlmin[tmin]][j]>xmin[i][j]) tmin--;
            dlmin[++tmin]=i;
            if (i>=a){
                while (hmin<=tmin&&dlmin[hmin]<=i-a) hmin++;
                ymin[i-a+1][j]=xmin[dlmin[hmin]][j];
            }
        }
    }//前面全都是单调队列求最小值，不会的可以点上个链接
    S.init(n,m);
    for (int i=1;i<=n-a+1;i++){
    	for (int j=1;j<=m-b+1;j++){
    		//cout<<(S.query(i,j,i+a-1,j+b-1)-1LL*a*b*ymin[i][j])<<" "<<i<<" "<<j<<endl;
    		dl.push(make_pair(-(S.query(i,j,i+a-1,j+b-1)-1LL*a*b*ymin[i][j]),make_pair(-i,-j)));
//我们要小根堆，所以我把里面所有的数都存了负值
		}
	}
	while (!dl.empty()){
		ll ANS=-dl.top().first,posx=-dl.top().second.first,posy=-dl.top().second.second;
		dl.pop();
		if (vis[posx][posy]) continue;
		ans[++cnt][0]=ANS,ans[cnt][1]=posx,ans[cnt][2]=posy;
		for (int i=max(1LL,posx-a+1);i<=posx+a-1;i++){
			for (int j=max(1LL,posy-b+1);j<=posy+b-1;j++){
				vis[i][j]=1;//打标记
			}	
		}
	}
	printf("%d\n",cnt);
	for (int i=1;i<=cnt;i++){
		printf("%lld %lld %lld\n",ans[i][1],ans[i][2],ans[i][0]);
	}
}
```


---

## 作者：szh_AK_all (赞：1)

在 duel 中通过了此题。

注意到 $n,m$ 的范围仅为 $1000$，那么我们可以将所有 $a\times b$ 的矩形都找出来并求其权值，然后按照题意贪心的选矩形即可。

下面令 $c_{i,j}$ 表示第 $i$ 行第 $j$ 列的权值。

每个矩形的权值分为**此矩形的权值和**、**此矩形最小权值**与**此矩形的大小**三部分，而矩形的权值和可以用二维前缀和来做，矩形的大小即为 $a\times b$，而对于计算矩形的最小权值不难想到用单调队列来做。

具体的，我们可以先对于每对 $i,j$，求出 $p1_{i,j}=\min_{l=j}^{j+b-1} c_{i,l}$，再对于每对 $i,j$，求出 $p2_{i,j}=\min_{l=i}^{i+a-1} p1_{l,j}$，则 $p2_{i,j}$ 即为 $\min_{l=i}^{i+a-1}\min_{r=j}^{j+b-1}c_{l,r}$，也就是以 $(i,j)$ 为左上角的矩阵的最小权值。

在贪心选取矩阵时，我们还得注意当前矩阵是否与之前选取的矩阵重叠，一个直观的想法是每选取一个矩阵就标记其包含的所有点，而判断一个矩阵是否与之前选取的矩阵重叠时，可以看该矩阵包含的所有点中是否有被标记过的，写法如下：

```cpp
for (int i = 1; i <= cnt; i++) {
		int x = s[i].x, y = s[i].y, sum = s[i].sum;
		int f = 0;
		for (int nx = x; nx <= x + a - 1; nx++)
			for (int ny = y; ny <= y + b - 1; ny++)
				if (vis[nx][ny]) {
					f = 1;
					break;
				}
		if (f)
			continue;
		an[++da] = nod(x, y, sum);
		for (int nx = x; nx <= x + a - 1; nx++)
			for (int ny = y; ny <= y + b - 1; ny++)
				vis[nx][ny] = 1;
}
```

然而这样会超时，因为其复杂度无法得到保证，此时，可以考虑使用树状数组来优化标记、查询操作，当然也有一种更好的写法，也就是在标记时不是将当前矩阵内的点进行标记，而是将所有可能与这个矩阵重叠的矩阵的左上角的点进行标记，这样在判断一个矩阵是否与之前选取的矩阵重叠时只需要判断这个矩阵的左上角是否被标记过；而在标记操作的复杂度显然不超过 $O(nm)$，因为每个点至多被标记一次。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int cnt, da, c[1005][1005], q[1005][1005], p1[1005][1005], p2[1005][1005], st[1005], vis[1005][1005];

struct node {
	int x, y, sum;
	node(int aa = 0, int bb = 0, int cc = 0) {
		x = aa;
		y = bb;
		sum = cc;
	}
	friend bool operator<(node l, node r) {
		if (l.sum != r.sum)
			return l.sum < r.sum;
		if (l.x != r.x)
			return l.x < r.x;
		return l.y < r.y;
	}
} s[1000005];

struct nod {
	int x, y, ans;
	nod(int aa = 0, int bb = 0, int cc = 0) {
		x = aa;
		y = bb;
		ans = cc;
	}
} an[1000005];

signed main() {
	int n, m, a, b;
	cin >> n >> m >> a >> b;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> c[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			q[i][j] = q[i - 1][j] + q[i][j - 1] - q[i - 1][j - 1] + c[i][j];
	for (int i = 1; i <= n; i++) {
		int h = 1, t = 0;
		for (int j = 1; j <= m; j++) {
			while (h <= t && c[i][st[t]] > c[i][j])
				t--;
			st[++t] = j;
			while (j - st[h] >= b)
				h++;
			if (j - b + 1 > 0)
				p1[i][j - b + 1] = c[i][st[h]];
		}
	}
	for (int i = 1; i <= m; i++) {
		int h = 1, t = 0;
		for (int j = 1; j <= n; j++) {
			while (h <= t && p1[st[t]][i] > p1[j][i])
				t--;
			st[++t] = j;
			while (j - st[h] >= a)
				h++;
			if (j - a + 1 > 0)
				p2[j - a + 1][i] = p1[st[h]][i];
		}
	}
	for (int i = 1; i + a - 1 <= n; i++)
		for (int j = 1; j + b - 1 <= m; j++) {
			int x = i + a - 1, y = j + b - 1;
			s[++cnt] = node(i, j, q[x][y] - q[i - 1][y] - q[x][j - 1] + q[i - 1][j - 1] - a * b * p2[i][j]);
		}
	sort(s + 1, s + cnt + 1);
	for (int i = 1; i <= cnt; i++) {
		int x = s[i].x, y = s[i].y, sum = s[i].sum;
		int f = 0;
		for (int nx = x; nx <= x; nx++)
			for (int ny = y; ny <= y; ny++)
				if (vis[nx][ny]) {
					f = 1;
					break;
				}
		if (f)
			continue;
		an[++da] = nod(x, y, sum);
		for (int nx = max(x - a + 1, 1LL); nx <= x + a - 1; nx++)
			for (int ny = max(y - b + 1, 1LL); ny <= y + b - 1; ny++)
				vis[nx][ny] = 1;
	}
	cout << da << "\n";
	for (int i = 1; i <= da; i++)
		cout << an[i].x << " " << an[i].y << " " << an[i].ans << "\n";
}
```

---

## 作者：Rushroom (赞：1)

卡常垃圾题。

### 做法

简单。

先对于每个 $(i,j)$，处理出 $(i,j),(i,j+1)\dots (i,j+b-1)$ 的 $\min$ 和 $\operatorname{sum}$。这个可以用单调队列，也可以像我一样用 `std::set` 带一个 $\log$ 解决。

然后对于每个 $(i,j)$，处理出以它为左上角的 $a\cdot b$ 的矩形的 $\min$ 和 $\operatorname{sum}$。处理方式同上。

对于所有矩形排序，注意权值相等时，还要比较坐标。然后按照从小到大顺序考虑是否能选。假设我们现在选了以 $(i,j)$ 为左上角的矩形，那么如果一个矩形的左上角 $(i_0,j_0)$ 满足 $i-a+1\le i_0 \le i+a-1$ 且 $j-b+1 \le j_0 \le j+b-1$，那么这个矩阵就被排除掉了。

这样做复杂度是不会超的，因为最多只能选 $\frac{nm}{ab}$ 个矩形，每个用 $O(ab)$ 的时间判断，所以总的复杂度是 $O(nm)$ 的。

### 卡常

本人认为这题 2500 主要在于卡常。

$nm$ 只有 $10^6$，但是还是会被卡。

实在没办法可以试试把 `endl` 改成 `'\n'`。

如果你只 TLE#38，可以对于 $a=b=1$ 的情况特判：直接按照 $(i,j)$ 的升序输出，每个代价都是 $0$（因为只有一格）。

为啥 `scanf/printf` 过不了啊（挠头

###Code

```cpp
/* Code by FGgirl */
/* ♥ FGgirl loves Frank ♥ */
#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define forr(i,a,n) for(int i=a;i<=n;++i)
#define rep(i,n) forr(i,0,n-1)
#define repp(i,n) forr(i,1,n)
#define pb push_back
#define mp make_pair
#define init(a,i) memset(a,i,sizeof(a))
#define fi first
#define se second
#define mod 1000000007
#define MOD 998244353
#define MAXN 0x3f3f3f3f
int T_, case_;
int n, m, a, b;
ll h[1010][1010];
ll mn0[1010][1010], mn[1010][1010], sum0[1010][1010], sum[1010][1010];
vector<pair<int, int>>v, ans;
bool cmp(pair<int, int>x, pair<int, int>y) {
    ll c1 = sum[x.fi][x.se] - mn[x.fi][x.se] * a * b, c2 = sum[y.fi][y.se] - mn[y.fi][y.se] * a * b;
    if (c1 != c2)return c1 < c2;
    if (x.fi != y.fi)return x.fi < y.fi;
    return x.se < y.se;
}
bool f[1010][1010];
int x, y;
multiset<ll>s;
void solve() {
    cin >> n >> m >> a >> b;
    rep(i, n)rep(j, m)cin >> h[i][j];
    // if (a == 1 && b == 1) {
        // cout << n * m << '\n';
        // rep(i, n)rep(j, m)cout << i + 1 << ' ' << j + 1 << ' ' << 0 << '\n';
        // return;
    // }
    rep(i, n) {
        rep(j, b)sum0[i][0] += h[i][j];
        forr(j, 1, m - b) sum0[i][j] = sum0[i][j - 1] - h[i][j - 1] + h[i][j + b - 1];
        s.clear();
        rep(j, b)s.insert(h[i][j]);
        mn0[i][0] = *s.begin();
        forr(j, 1, m - b) {
            s.erase(s.find(h[i][j - 1]));
            s.insert(h[i][j + b - 1]);
            mn0[i][j] = *s.begin();
        }
    }
    rep(j, m - b + 1) {
        rep(i, a)sum[0][j] += sum0[i][j];
        forr(i, 1, n - a) sum[i][j] = sum[i - 1][j] - sum0[i - 1][j] + sum0[i + a - 1][j];
        s.clear();
        rep(i, a)s.insert(mn0[i][j]);
        mn[0][j] = *s.begin();
        forr(i, 1, n - a) {
            s.erase(s.find(mn0[i - 1][j]));
            s.insert(mn0[i + a - 1][j]);
            mn[i][j] = *s.begin();
        }
    }
    rep(i, n - a + 1)rep(j, m - b + 1)v.pb(mp(i, j));
    sort(v.begin(), v.end(), cmp);
    rep(i, v.size()) {
        x = v[i].fi, y = v[i].se;
        if (f[x][y])continue;
        ans.pb(mp(x, y));
        forr(xx, x - a + 1, x + a - 1)forr(yy, y - b + 1, y + b - 1) {
            if (xx >= 0 && xx < n && yy >= 0 && yy < m) {
                f[xx][yy] = 1;
            }
        }
    }
    cout << ans.size() << '\n';
    rep(i, ans.size()) {
        x = ans[i].fi, y = ans[i].se;
        cout << x + 1 << ' ' << y + 1 << ' ' << sum[x][y] - mn[x][y] * a * b << '\n';
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    T_ = 1;

    for (case_ = 1;case_ <= T_;case_++)solve();
    return 0;
}
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2500}$
---
取格子的顺序应该是从上往下，从左往右。

---
### 解题思路：

造房子的格子是固定的，所以直接预处理出以每一个位置为左上角的代价，排序并按照顺序往下取就行了，注意在取完进行覆盖，不要重复取到同一个位置。

对于代价的计算分为两个部分，总和和最小值。总和直接用二维前缀和就能做出来了，最小值则相对复杂一点。

考虑先对每一个位置用单调栈处理出当前位置到这个位置右边 $b$ 个位置上的最小值，然后在对处理之后的数组再进行类似的操作，也就是用单调栈处理出这个位置在第一次处理过的数组下的下面的 $a$ 个位置的的最小值，这样也就处理出了右下 $a\times b$ 范围之内的最小值。

排序的复杂度是 $O(nm\log(nm))$ 的。

最后是覆盖的问题，如果直接覆盖和查询复杂度爆炸，然后可以用数据结构优化一下（线段树或者树状数组应该都可以），但是很麻烦。考虑再次利用矩阵固定的性质，直接将所有的不能再次作为左上角的点全都覆盖为 $1$，更具体地，位置是 $([x-a+1,x+a-1],[y-a+1,y+a-1])$，这样只要取到能直接判断，而且每一个点最多被覆盖和查询各一次，这一步的复杂度是 $O(nm)$ 的。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
struct str{
	int x,y,sum;
	bool operator <(str a){
		if(sum==a.sum){
			if(x==a.x)return y<a.y;
			return x<a.x;
		}
		return sum<a.sum;
	}
}p[1005*1005],ans[1005*1005];
int n,m,a,b,h[1005][1005],l,r,q[1005],x[1005][1005],y[1005][1005],sum[1005][1005],cnt,book[1005][1005],tot;
signed main(){
	scanf("%I64d%I64d%I64d%I64d",&n,&m,&a,&b);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	scanf("%I64d",&h[i][j]);
	for(int i=1;i<=n;i++){
		l=1;r=0;
		for(int j=1;j<=m;j++){
			while(h[i][q[r]]>h[i][j]&&r>=l)r--;
			q[++r]=j;if(j-q[l]>=b)l++;
			if(j>=b)x[i][j-b+1]=h[i][q[l]];
		}
	}
	for(int j=1;j<=m;j++){
		l=1;r=0;
		for(int i=1;i<=n;i++){
			while(x[q[r]][j]>x[i][j]&&r>=l)r--;
			q[++r]=i;if(i-q[l]>=a)l++;
			if(i>=a)y[i-a+1][j]=x[q[l]][j];
		}
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+h[i][j];
	
	for(int i=1;i<=n-a+1;i++)
	for(int j=1;j<=m-b+1;j++){
		p[++cnt].x=i;p[cnt].y=j;
		p[cnt].sum=sum[i+a-1][j+b-1]-sum[i-1][j+b-1]-sum[i+a-1][j-1]+sum[i-1][j-1]-(a*b)*y[i][j];
	}
	sort(p+1,p+cnt+1);
	for(int I=1;I<=cnt;I++){
		if(book[p[I].x][p[I].y]==1)continue;
		ans[++tot]=p[I];
		for(int i=max(1ll,p[I].x-a+1);i<=min(n,p[I].x+a-1);i++)
		for(int j=max(1ll,p[I].y-b+1);j<=min(m,p[I].y+b-1);j++)
		book[i][j]=1;
	}
	printf("%I64d\n",tot);
	for(int i=1;i<=tot;i++){		
		printf("%I64d %I64d %I64d\n",ans[i].x,ans[i].y,ans[i].sum);
	}
	return 0;
}
```


---

## 作者：chenxia25 (赞：1)

>### [洛谷题目页面传送门](https://www.luogu.org/problem/CF15D) & [CodeForces题目页面传送门](https://codeforces.com/contest/15/problem/D)

>题意见洛谷里的翻译。（注意翻译里有错误，应该是优先选上面的矩阵，在同一行的优先选左边的矩阵）

~~这题一看就会做啊~~

（以下设大矩阵是$n\times m$，小矩阵是$n0\times m0$，第$i$行第$j$列高度为$a_{i,j}$）

不难想到可以预处理出二维前缀和数组$Sum$，后面就可以$\mathrm{O}(1)$求出一个小矩阵的和；然后跑$2$遍单调队列，第$1$次求出$\forall i\in[1,n],\forall j\in[1,m-m0+1],mn1_{i,j}=\min\limits_{k=j}^{j+m0-1}\{a_{i,k}\}$，第二次求出$\forall i\in[1,n-n0+1],\forall j\in[1,m-m0+1],mn2_{i,j}=\min\limits_{k=i}^{k+n0-1}\left\{\min\limits_{o=j}^{j+m0-1}\{a_{k,o}\}\right\}=\min\limits_{k=i}^{k+n0-1}\{mn1_{k,j}\}$。那么一个左上角在$(i,j)$的小矩阵的花费~~显然~~是$Sum_{i+n0-1,j+m0-1}-Sum_{i-1,j+m0-1}-Sum_{i+n0-1,j-1}+Sum_{i-1,j-1}-n0\times m0\times mn2_{i,j}$了。然后把所有小矩阵排个序，从头到尾扫一遍，如果一个小矩阵中有已经被标记的格子了，就不选；否则就选，并且把它所覆盖的格子都标记一下。但这样会TLE。~~不难想到，~~判一个小矩阵有没有被标记过的格子，只需要判四个角就可以了，这样判的时间总共就是$\mathrm{O}(nm)$了；而每个格子最多会被标记一次，所以标记总共也是$\mathrm{O}(nm)$，这样就不会TLE了。~~（或者你用树状数组、线段树或其他一些更高级的数据结构我也不拦你）~~

对了，这题非常的卡常。我第一次交，T了。然后加了个快读，还是T了。然后把所有`int`改成`register int`，还是T了。最后我发现，原来计算一个小矩阵的花费虽然$\mathrm{O}(1)$，但是常数略大，而我却把它放在`sort`的`cmp`里计算，等于在扩大计算花费的常数~~（众所周知，快排里一个元素可能和多个元素比较）~~。于是我事先计算所有小矩阵的花费，然后存下来，`cmp`的时候直接调用，然后就AC了。

下面贴上蒟蒻~~又长又丑的~~代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define mp make_pair
#define X first
#define Y second
#define ri register int//呵呵 
void read(int &x){//快读 
	x=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
}
const int N=1000,M=1000;
int n,m/*大矩阵的尺寸*/,n0,m0/*小矩阵的尺寸*/;
int a[N+1][M+1];//高度 
int Sum[N+1][M+1];//二维前缀和 
int q[N],head,tail;//单调队列 
int mn1[N+1][M+1]/*一维最小值*/,mn2[N+1][M+1]/*二维最小值*/;
vector<pair<int,int> > ord;//小矩阵访问顺序 
int cst[N+1][M+1];//小矩阵的花费 
int calc_cst(int x,int y){//计算左上角在(x,y)的小矩阵的花费 
	return Sum[x+n0-1][y+m0-1]-Sum[x-1][y+m0-1]-Sum[x+n0-1][y-1]+Sum[x-1][y-1]-n0*m0*mn2[x][y];
}
bool cmp(pair<int,int> x,pair<int,int> y){//排序方式，以花费为第一关键字从小到大、行数为第二关键字从小到大、列数为第三关键字从小到大排序 
	return cst[x.X][x.Y]!=cst[y.X][y.Y]?cst[x.X][x.Y]<cst[y.X][y.Y]:x.X!=y.X?x.X<y.X:x.Y<y.Y;
}
bool vis[N+1][M+1];//标记 
signed main(){
//	freopen("C:\\Users\\chenx\\OneDrive\\桌面\\data.in","r",stdin);
	read(n);read(m);read(n0);read(m0);
	for(ri i=1;i<=n;i++)for(ri j=1;j<=m;j++){
		read(a[i][j]);
		Sum[i][j]=Sum[i-1][j]+Sum[i][j-1]-Sum[i-1][j-1]+a[i][j];//预处理二维前缀和 
	}
	for(ri i=1;i<=n;i++){//第一次单调队列，算mn1 
		head=tail=0;
		for(ri j=1;j<m0;j++){
			while(head<tail&&a[i][q[tail-1]]>=a[i][j])tail--;
			q[tail++]=j;
		}
		for(ri j=1;j+m0-1<=m;j++){
			while(head<tail&&q[head]<j)head++;
			while(head<tail&&a[i][q[tail-1]]>=a[i][j+m0-1])tail--;
			q[tail++]=j+m0-1;
			mn1[i][j]=a[i][q[head]];
		}
	}
//	for(ri i=1;i<=n;i++){for(ri j=1;j+m0-1<=m;j++)cout<<mn1[i][j]<<" ";puts("");}puts("");
	for(ri j=1;j+m0-1<=m;j++){//第二次单调队列，算mn2 
		head=tail=0;
		for(ri i=1;i<n0;i++){
			while(head<tail&&mn1[q[tail-1]][j]>=mn1[i][j])tail--;
			q[tail++]=i;
		}
		for(ri i=1;i+n0-1<=n;i++){
			while(head<tail&&q[head]<i)head++;
			while(head<tail&&mn1[q[tail-1]][j]>=mn1[i+n0-1][j])tail--;
			q[tail++]=i+n0-1;
			mn2[i][j]=mn1[q[head]][j];
		}
	}
//	for(ri i=1;i+n0-1<=n;i++){for(ri j=1;j+m0-1<=m;j++)cout<<mn2[i][j]<<" ";puts("");} 
	for(ri i=1;i+n0-1<=n;i++)for(ri j=1;j+m0-1<=m;j++)cst[i][j]=calc_cst(i,j)/*存花费*/,ord.pb(mp(i,j));
	sort(ord.begin(),ord.end(),cmp);//排序 
	vector<pair<int,int> > ans;//答案序列 
	for(ri i=0;i<ord.size();i++){
		int x=ord[i].X,y=ord[i].Y;
		if(vis[x][y]||vis[x][y+m0-1]||vis[x+n0-1][y]||vis[x+n0-1][y+m0-1])continue;//判四个角 
		ans.pb(ord[i]);//放到答案序列里 
		for(ri j=x;j<=x+n0-1;j++)for(ri k=y;k<=y+m0-1;k++)vis[j][k]=true;//标记 
	}
	cout<<ans.size()<<"\n";//输出选的小矩阵的个数 
	for(ri i=0;i<ans.size();i++)printf("%lld %lld %lld\n",ans[i].X,ans[i].Y,cst[ans[i].X][ans[i].Y]);//输出选的小矩阵 
	return 0;
}
```

---

## 作者：01bit (赞：0)

神金卡常题。

子矩阵的和可以用预处理 $O(mn)$ 的二维前缀和解决。

子矩阵的最小值可以通过单调队列解决：

1. 预处理出一个点和在同一行的后面 $b-1$ 个点的最小值，时间 $O(mn)$。
2. 再通过前者预处理出每个子矩阵的最小值，时间 $O(mn)$。

再将所有子矩阵扔进序列里排序，然后逐一判断并选择，时间 $O(mn\log(mn))$。

选中一个子矩阵时暴力将覆盖的点标记即可，时间 $O(mn)$。（因为选中的子矩阵不会互相覆盖）

注意要卡卡常，比如将 `endl` 换为 `"\n"`。


```cpp
#include <algorithm>
#include <iostream>
using namespace std;
using ll = long long;
const ll N = 1000 + 5;
ll n, m, a, b, la = 0, lb = 0;
ll mat[N][N], sum[N][N], mn1[N][N], mn2[N][N];
struct Node {
    ll x, y, val;
};
Node sub[N * N];
ll id[N * N], tp = 0, ans[N * N], cnt = 0;
bool cmp(int x, int y) {
    if (sub[x].val == sub[y].val)
        return sub[x].x == sub[y].x ? sub[x].y < sub[y].y : sub[x].x < sub[y].x;
    return sub[x].val < sub[y].val;
}
bool ok[N][N];
void init0() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m >> a >> b;
    for (ll i = 1; i <= n; i++)
        for (ll j = 1; j <= m; j++)
            cin >> mat[i][j];
    for (ll i = n; i >= 1; i--)
        for (ll j = m; j >= 1; j--)
            sum[i][j] =
                mat[i][j] + sum[i + 1][j] + sum[i][j + 1] - sum[i + 1][j + 1];
}
void init1() {
    ll q[N], hd = 0, tl = -1;
    for (ll i = 1; i <= n; i++) {
        hd = 0, tl = -1;
        for (ll j = 1; j <= b; j++) {
            while (hd <= tl && mat[i][q[tl]] >= mat[i][j])
                tl--;
            q[++tl] = j;
        }
        mn1[i][1] = mat[i][q[hd]];
        for (ll j = 2; j + b - 1 <= m; j++) {
            while (hd <= tl && q[hd] < j)
                hd++;
            while (hd <= tl && mat[i][q[tl]] >= mat[i][j + b - 1])
                tl--;
            q[++tl] = j + b - 1;
            mn1[i][j] = mat[i][q[hd]];
        }
    }
}
void init2() {
    ll q[N], hd = 0, tl = -1;
    for (ll j = 1; j + b - 1 <= m; j++) {
        hd = 0, tl = -1;
        for (ll i = 1; i <= a; i++) {
            while (hd <= tl && mn1[q[tl]][j] >= mn1[i][j])
                tl--;
            q[++tl] = i;
        }
        mn2[1][j] = mn1[q[hd]][j];
        for (ll i = 2; i + a - 1 <= n; i++) {
            while (hd <= tl && q[hd] < i)
                hd++;
            while (hd <= tl && mn1[q[tl]][j] >= mn1[i + a - 1][j])
                tl--;
            q[++tl] = i + a - 1;
            mn2[i][j] = mn1[q[hd]][j];
        }
    }
}
int main() {
    init0();
    init1();
    init2();
    for (ll x = 1; x + a - 1 <= n; x++)
        for (ll y = 1; y + b - 1 <= m; y++) {
            ll s =
                sum[x][y] - sum[x + a][y] - sum[x][y + b] + sum[x + a][y + b];
            ll mn = mn2[x][y];
            id[tp] = tp;
            sub[tp].x = x;
            sub[tp].y = y;
            sub[tp++].val = s - mn * a * b;
        }
    sort(id, id + tp, cmp);
    for (ll i = 0; i < tp; i++) {
        if (!ok[sub[id[i]].x][sub[id[i]].y]) {
            ans[cnt++] = id[i];
            for (ll x = max(1LL, sub[id[i]].x - a + 1);
                 x <= n && x < sub[id[i]].x + a; x++)
                for (ll y = max(1LL, sub[id[i]].y - b + 1);
                     y <= m && y < sub[id[i]].y + b; y++)
                    ok[x][y] = true;
        }
    }
    cout << cnt << "\n";
    for (ll i = 0; i < cnt; i++)
        cout << sub[ans[i]].x << " " << sub[ans[i]].y << " " << sub[ans[i]].val
             << "\n";
    return 0;
}
```

---

## 作者：happybob (赞：0)

考虑到 $n, m \leq 1000$，所以直接模拟是可行的。

一开始，预处理出以每个点为左上角的 $a \times b$ 的矩形的答案。矩形和显然可以二维前缀和，最小值可以 ST 表配合 `multiset` 做到一只 $\log$，也可以单调队列把 $\log$ 优化掉。

每次选择最小的答案，把这个矩阵能影响的点删掉，循环做即可。

比较卡常，建议使用手写懒惰删除堆代替 `multiset`。

```cpp
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int n, m, a, b;

int c[N][N];
long long sum[N][N];

struct Node
{
	int x, y;
	long long w;
	Node(int _x, int _y, long long _w): x(_x), y(_y), w(_w){}
	Node() = default;
	bool operator<(const Node& xx) const
	{
		if (w != xx.w) return w > xx.w;
		if (x != xx.x) return x > xx.x;
		return y > xx.y;
	}
	bool operator==(const Node& g) const
	{
		return x == g.w && y == g.y && w == g.w;
	}
};

class Mymultiset
{
public:
	priority_queue<Node> q1, q2;
	void ins(Node x)
	{
		q1.push(x);
	}
	void del(Node x)
	{
		q2.push(x);
	}
	int sz()
	{
		return q1.size() - q2.size();
	}
	Node Top()
	{
		while (q2.size() && q1.top() == q2.top()) q1.pop(), q2.pop();
		return q1.top();
	}
	void Pop()
	{
		while (q2.size() && q1.top() == q2.top()) q1.pop(), q2.pop();
		q1.pop();
	}
};

Mymultiset mt;

int LG2[N];

class ST
{
public:
	int f[11][N];
	void Init(int *c)
	{
		memset(f, 0x3f, sizeof f);
		for (int i = 1; i <= m; i++) f[0][i] = c[i];
		for (int j = 1; j <= LG2[m]; j++)
		{
			for (int i = 1; i + (1 << j) - 1 <= m; i++)
			{
				f[j][i] = min(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);
			}
		}
	}
	int query(int l, int r)
	{
		int p = LG2[r - l + 1];
		return min(f[p][l], f[p][r - (1 << p) + 1]);
	}
}s[N];

bool vis[N][N];

signed main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	for (int i = 2; i < N; i++) LG2[i] = LG2[i / 2] + 1;
	cin >> n >> m >> a >> b;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++) 
		{
			cin >> c[i][j];
			sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + c[i][j];
		}
		s[i].Init(c[i]);
	}
	vector<Node> res;
	for (int j = 1; j <= m - b + 1; j++)
	{
		multiset<int> sts;
		for (int i = 1; i <= a; i++) sts.insert(s[i].query(j, j + b - 1));
		for (int i = 1; i <= n - a + 1; i++)
		{
			long long su = sum[i + a - 1][j + b - 1] - sum[i + a - 1][j - 1] - sum[i - 1][j + b - 1] + sum[i - 1][j - 1];
			mt.ins(Node(i, j, su - 1LL * (*sts.begin()) * a * b));
			sts.erase(sts.find(s[i].query(j, j + b - 1)));
			if (i + a <= n) sts.insert(s[i + a].query(j, j + b - 1));
		}
	}
	while (mt.sz())
	{
		auto u = mt.Top();
		mt.Pop();
		if (vis[u.x][u.y]) continue;
		vis[u.x][u.y] = 1;
		res.emplace_back(u);
		for (int i = max(1, u.x - a + 1); i <= u.x + a - 1; i++)
		{
			for (int j = max(1, u.y - b + 1); j <= u.y + b - 1; j++) vis[i][j] = 1;
		}
	}
	cout << res.size() << "\n";
	for (auto &[x, y, z] : res)
	{
		cout << x << " " << y << " " << z << "\n";
	}
	return 0; 
}
```


---

## 作者：hegm (赞：0)

一道简单题。

考虑维护出每个 $a\times b$ 大小的矩阵的权值和以及最小权值。

前者比较简单，直接二维前缀和即可，后者可以使用单调队列一维一维的做。

那么现在每一个矩阵的花费我们都知晓了，如何处理不重叠的情况哪？

有一个非常简单的方法，对于一个矩形，考虑他的四个角是否被覆盖过即可，因为所有的矩阵大小都一样，因此重叠的矩阵一定会至少经过四个角中的一个。

因此对于矩阵的左上角为 $(x,y)$ 只需要考虑 $(x,y)(x+a-1,y)(x,y+b-1)(x+a-1,y+b-1)$ 这四个点就好。

所以直接对所有矩阵排序，然后一个个检查，如果合法，那么加入答案中，然后把它的所有节点打上覆盖标记即可。

复杂度 $O(nm)$。

### CODE

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int a,b,m,n,mp[N][N],sum[N][N],mn[N][N],sp[N][N],cnt,num,id[N*N];
bool vis[N][N];
deque<int> q;
struct mat
{
	int x,y,w;
	bool operator < (mat b)
	{
		if(w==b.w&&x==b.x)return y<b.y;
		if(w==b.w)return x<b.x;
		return w<b.w;
	}
}s[N*N];
signed main()
{
	n=read();m=read();a=read();b=read();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		mp[i][j]=read();
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		sum[i][j]=sum[i-1][j]+sum[i][j-1]+mp[i][j]-sum[i-1][j-1];
	}
	for(int i=1;i<=n;i++)
	{
		while(q.size())q.pop_back();q.push_back(1);mn[i][1]=mp[i][1];
		for(int j=2;j<=m;j++)
		{
			while(q.size()&&j-q.front()>=b)q.pop_front();
			while(q.size()&&mp[i][q.back()]>=mp[i][j])q.pop_back();
			q.push_back(j);mn[i][j]=mp[i][q.front()];
		}
	}
	for(int i=1;i<=m;i++)
	{
		while(q.size())q.pop_back();q.push_back(1);sp[1][i]=mn[1][i];
		for(int j=2;j<=n;j++)
		{
			while(q.size()&&j-q.front()>=a)q.pop_front();
			while(q.size()&&mn[q.back()][i]>=mn[j][i])q.pop_back();
			q.push_back(j);sp[j][i]=mn[q.front()][i];
		}
	}
	for(int i=a;i<=n;i++)
	{
		for(int j=b;j<=m;j++)
		s[++cnt]={i,j,sum[i][j]-sum[i-a][j]-sum[i][j-b]+sum[i-a][j-b]-a*b*sp[i][j]};
	}
	sort(s+1,s+1+cnt);
	for(int i=1,x,y;i<=cnt;i++)
	{
		x=s[i].x;y=s[i].y;
		if(vis[x][y]||vis[x-a+1][y]||vis[x][y-b+1]||vis[x-a+1][y-b+1])continue;
		num++;id[num]=i;
		for(int k1=0;k1<a;k1++)
		{
			for(int k2=0;k2<b;k2++)
			vis[x-k1][y-k2]=1;
		}
	}
	cout<<num<<"\n";
	for(int i=1;i<=num;i++)cout<<s[id[i]].x-a+1<<" "<<s[id[i]].y-b+1<<" "<<s[id[i]].w<<"\n";
	return 0;
}

```

---

## 作者：Dilute (赞：0)

[$$\huge\texttt{在本人blog食用更佳}$$](https://dilute.xyz/2019/05/08/Solutions/Solution-CF15D/)


## $set$瞎搞

首先非常显然，一个矩形$(x1, y1, x2, y2)$的代价就是$\displaystyle\sum_{i = x1}^{x2}\sum_{j = y1}^{y2} h[i][j] - \min_{x1 \le i \le x2, y1 \le j \le y2} h[i][j]$，我们用$f[i][j]$表示以$(i, j)$为左上角的矩形的代价。即矩形$(i, j, i + a - 1, j + b - 1)$的代价。

我们首先考虑如何求出$f[i][j]$。

前面的求和可以一个二维前缀和简单解决，关键在于后面的$\min$。

我们对每行都建一个$st$表，考虑我们把当前我们要求的区间里的$h[i][j]$都丢进一个$set$中。

我们考虑每次把矩形往下移动。

发现其实对于每一行，只有它的在范围内的最小值才有贡献，所$set$中只需要放每行的最小值（可以用$st$表快速查询）。

我们再考虑如下图所示。

![](https://dilute.xyz/images/3.png)

然后如果我们要从蓝色矩形移动到黑色矩形，那么我们只需要在$set$中删去灰色部分的最小值，再加入浅蓝色部分的最小值即可。

求出了$f[i][j]$之后就可以按题意模拟了w

每次我们可以找出$f[i][j]$的最小值，这个排遍序轻松解决（~~我之前作死用set被卡常了~~）然后给所有因为这个矩形被取到了导致不能取的打上标记，这样子时间复杂度是正确的，最多只会被取到$\frac{n m}{ab}$个矩形，然后每次打标记是$O(a * b)$的，最后复杂度就是$O(\frac{n m}{a b} a b) = O(n m)$的。

复杂度$O(n m \log n)$，轻微卡常w

## 代码

```cpp
#include<bits/stdc++.h>

#define ll long long
#define INF 2147483647

int inp(){
    char c = getchar();
    while(c < '0' || c > '9')
        c = getchar();
    int sum = 0;
    while(c >= '0' && c <= '9'){
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return sum;
}

int f[1010][1010][12];
std::multiset<ll> s2;
int ans1[1000010], ans2[1000010], h[1010][1010];
ll ans3[1000010], sum[1010][1010], val[1010][1010];
bool used[1010][1010];
std::pair<int, int> s[1000010];

ll query(int x, int l, int r){
    int lg = log2(r - l + 1);
    return std::min(f[x][l][lg], f[x][r - (1 << lg) + 1][lg]);
}

bool cmp(std::pair<int, int> a, std::pair<int, int> b){
    if(val[a.first][a.second] == val[b.first][b.second])
        return a < b;
    return val[a.first][a.second] < val[b.first][b.second];
}

int main(){
    int n = inp();
    int m = inp();
    int a = inp();
    int b = inp();
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            f[i][j][0] = h[i][j] = inp();
    for(int i = 1; i <= n; i++)
        for(int u = 1; u <= 10; u++)
            for(int j = 1; j <= m; j++)
                if(j + (1 << u) - 1 <= m)
                    f[i][j][u] = std::min(f[i][j][u - 1], f[i][j + (1 << (u - 1))][u - 1]);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + h[i][j];
    for(int j = 1; j <= m - b + 1; j++){
        s2.clear();
        for(int i = 1; i <= a; i++)
            s2.insert(query(i, j, j + b - 1));
        for(int i = 1; i <= n - a + 1; i++){
            val[i][j] = sum[i + a - 1][j + b - 1] + sum[i - 1][j - 1] - sum[i + a - 1][j - 1] - sum[i - 1][j + b - 1] - (*(s2.begin())) * (a * b);
            s2.erase(s2.find(query(i, j, j + b - 1)));
            if(i + a <= n)
                s2.insert(query(i + a, j, j + b - 1));
        }
    }
    int cc = 0;
    for(int i = 1; i <= n - a + 1; i++)
        for(int j = 1; j <= m - b + 1; j++)
            s[++cc] = std::make_pair(i, j);
    std::sort(s + 1, s + cc + 1, cmp);
    int cnt = 0;
    for(int u = 1; u <= cc; u++){
        if(used[s[u].first][s[u].second])
            continue;
        cnt++;
        ans1[cnt] = s[u].first;
        ans2[cnt] = s[u].second;
        ans3[cnt] = val[s[u].first][s[u].second];
        for(int i = ans1[cnt] - a + 1; i <= ans1[cnt] + a - 1; i++)
            for(int j = ans2[cnt] - b + 1; j <= ans2[cnt] + b - 1; j++)
                if(i > 0 && j > 0 && !used[i][j] && i <= n - a + 1 && j <= m - b + 1)
                    used[i][j] = true;
    }
    printf("%d\n", cnt);
    for(int i = 1; i <= cnt; i++)
        printf("%d %d %I64d\n", ans1[i], ans2[i], ans3[i]);
}
```



---

