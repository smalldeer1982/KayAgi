# Manhattan Triangle

## 题目描述

The Manhattan distance between two points $ (x_1, y_1) $ and $ (x_2, y_2) $ is defined as: $ $$$|x_1 - x_2| + |y_1 - y_2|. $ $ </p><p>We call a <span class="tex-font-style-it">Manhattan triangle</span> three points on the plane, the Manhattan distances between each pair of which are equal.</p><p>You are given a set of pairwise distinct points and an <span class="tex-font-style-bf">even</span> integer  $ d $ . Your task is to find any Manhattan triangle, composed of three distinct points from the given set, where the Manhattan distance between any pair of vertices is equal to  $ d$$$.

## 说明/提示

In the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1979E/bbfd233820492f977fbef974993b9a69a436fb4a.png) Points $ A $ , $ B $ , and $ F $ form a Manhattan triangle, the Manhattan distance between each pair of vertices is $ 4 $ . Points $ D $ , $ E $ , and $ F $ can also be the answer.In the third test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1979E/0f533955337f14b26cd93892ca00000567fdf3e5.png) Points $ A $ , $ C $ , and $ E $ form a Manhattan triangle, the Manhattan distance between each pair of vertices is $ 6 $ .In the fourth test case, there are no two points with a Manhattan distance of $ 4 $ , and therefore there is no suitable Manhattan triangle.

## 样例 #1

### 输入

```
6
6 4
3 1
0 0
0 -2
5 -3
3 -5
2 -2
5 4
0 0
0 -2
5 -3
3 -5
2 -2
6 6
3 1
0 0
0 -2
5 -3
3 -5
2 -2
4 4
3 0
0 3
-3 0
0 -3
10 8
2 1
-5 -1
-4 -1
-5 -3
0 1
-2 5
-4 4
-4 2
0 0
-4 1
4 400000
100000 100000
-100000 100000
100000 -100000
-100000 -100000```

### 输出

```
2 6 1
4 3 5
3 5 1
0 0 0
6 1 3
0 0 0```

# 题解

## 作者：ttq012 (赞：10)

首先根据一场 ABC E 题的套路，将曼哈顿距离转化为切比雪夫距离：

+ 若当前点的坐标为 $(x,y)$，则新的点的坐标为 $(x+y,x-y)$。

容易证明这样的转化是正确的。此时 $x$ 和 $y$ 互不影响。

于是问题就变成了：找出三个点的坐标 $(x_1,y_1),(x_2,y_2),(x_3,y_3)$，满足下面的两种情况之一：

+ 有两对点的 $x$ 坐标的距离为 $d$，另外一对点的 $y$ 坐标的距离为 $d$。
+ 有两对点的 $y$ 坐标的距离为 $d$，另外一对点的 $x$ 坐标的距离为 $d$。

此时必须要有两个点的 $x$ 坐标和 $y$ 坐标的值相等。

考虑枚举相同的 $x$ 坐标，那么另外一个没有枚举的点的 $x$ 坐标的值必然为 $x-d$ 或者 $x+d$。

将所有的 $x$ 坐标全部存储到一个 `set` 里。查询的时候枚举 $x$ 坐标，判断 `set` 中是否存在 $x-d$ 或者 $x+d$ 即可。

$y$ 坐标同理。时间复杂度为 $O(n\log n)$。

```cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define em emplace_back
#define F(i,x,y) for(int i=x;i<=y;i++)
#define G(i,x,y) for(int i=x;i>=y;i--)
#define W(G,i,x) for(auto&i:G[x])
#define W_(G,i,j,x) for(auto&[i,j]:G[x])
#define add(x,y) z[x].em(y)
#define add_(x,y) add(x,y),add(y,x)
#define Add(x,y,d) z[x].em(y,d)
#define Add_(x,y,z) Add(x,y,z),Add(y,x,z);
#ifdef int
#define inf (7611257611378358090ll/2)
#else
#define inf 0x3f3f3f3f
#endif
using namespace std;
int ll(int a, int b) {
    return a / __gcd(a, b) * b;
}
const int N = 400100;
struct Point {
    int x, y;
} a[N];
void $() {
    int n, d;
    cin >> n >> d;
    F(i, 1, n) {
        int x, y;
        cin >> x >> y;
        a[i] = {x + y, x - y};
    }
    map<int, set<pair<int, int>>> mp;
    F(i, 1, n) {
        mp[a[i].x].insert({a[i].y, i});
    }
    for (auto &[x, se] : mp) {
        if (mp.count(x + d)) {
            for (auto &[y, id] : se) {
                auto it = se.lower_bound({y + d, 0ll});
                if (it != se.end() && it->first == y + d) {
                    auto it_ = mp[x + d].lower_bound({y, 0ll});
                    if (it_ != mp[x + d].end() && it_->first <= y + d) {
                        cout << id << ' ' << it->second << ' ' << it_->second << '\n';
                        return;
                    }
                }
            }
        }
        if (mp.count(x - d)) {
            for (auto &[y, id] : se) {
                auto it = se.lower_bound({y + d, 0ll});
                if (it != se.end() && it->first == y + d) {
                    auto it_ = mp[x - d].lower_bound({y, 0ll});
                    if (it_ != mp[x - d].end() && it_->first <= y + d) {
                        cout << id << ' ' << it->second << ' ' << it_->second << '\n';
                        return;
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        swap(a[i].x, a[i].y);
    }
    mp.clear();
    F(i, 1, n) {
        mp[a[i].x].insert({a[i].y, i});
    }
    for (auto &[x, se] : mp) {
        if (mp.count(x + d)) {
            for (auto &[y, id] : se) {
                auto it = se.lower_bound({y + d, 0ll});
                if (it != se.end() && it->first == y + d) {
                    auto it_ = mp[x + d].lower_bound({y, 0ll});
                    if (it_ != mp[x + d].end() && it_->first <= y + d) {
                        cout << id << ' ' << it->second << ' ' << it_->second << '\n';
                        return;
                    }
                }
            }
        }
        if (mp.count(x - d)) {
            for (auto &[y, id] : se) {
                auto it = se.lower_bound({y + d, 0ll});
                if (it != se.end() && it->first == y + d) {
                    auto it_ = mp[x - d].lower_bound({y, 0ll});
                    if (it_ != mp[x - d].end() && it_->first <= y + d) {
                        cout << id << ' ' << it->second << ' ' << it_->second << '\n';
                        return;
                    }
                }
            }
        }
    }
    cout << "0 0 0\n";
}
auto main() [[O3]] -> signed {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        $();
    }
}
```

---

## 作者：sunzz3183 (赞：4)

# CF1979E Manhattan Triangle 题解

## 闲话

这场咋都是观察样例题。。

## 题意

从图上给定的点中找三个点，使得任意两点的曼哈顿距离为 $D$。

## 分析

我们令 $d=\frac{D}{2} $，距离都为曼哈段距离（诸如 $|AB|$ 也是曼哈段距离），方便后面讲解。

我们考虑一个**曼哈顿距离外心** $F$，使得这个外心到其他顶点的距离为 $d$。

这样我们就从枚举三个点转换到了枚举一个点，但是这样做仍然很麻烦，需要维护一个圆，继续考虑性质。

我们把样例画下来（推荐一个网站：[链接](https://www.geogebra.org/calculator)），然后自己随便构造几组，发现一定有两个点（设为 $A,B$），使得 $AF\perp  BF$，且 $AF,BF$，各自平行于 $x$ 轴和 $y$ 轴，然后另外一个点（设为 $E$）一定在一条线段上。具象化如图所示：

![](https://pic.imgdb.cn/item/66641d0e5e6d1bfa05675c69.gif)

至于证明，当 $A,B$ 点确定时，$E$ 点一定在一条斜率为 $1$ 或 $-1$ 的线段很好想。然后是关于 $A,B$ 点，可以想象一下，如果 $A$ 向左移那就一定不会满足 $|AB|=|AF|+|BF|$，向上下移动，就不会满足 $|AB|=D$，向右移动 $E$ 就只等在 $D$ 点，只是转了一下方向，而 $A,B$ 更不可能一起移动，会使得  $EF=d$ 满足，但是 $|AE|=|BE|=d$ 的条件不满足。

上述都是赛时的想法，详细的证明可以看一下楼下的题解，用到了旋转 $45$ 度，将曼哈段距离转化成切比雪夫距离的方法。

然后进入正题，枚举重心，然后暴力判断 $A,B$ 位置，最后 $E$ 点只要用 `set` 分别维护斜率 $1,-1$ 的直线的截距，然后二分查找一下就行。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
inline int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||'9'<c){if(c=='-')f=-1;c=getchar();}
    while('0'<=c&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
    return x*f;
}
const int N=2e5+2,nxt[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
int n,x[N],y[N],d;
map<pii,int>mp;
set<pii>st0[N<<1],st1[N<<1];
vector<pii>vt;
inline int get0(int x,int y){
    return y-x+200000;
}
inline int get1(int x,int y){
    return x+y;
}
void Main(){
    for(int i=1;i<=n;i++)
        st0[get0(x[i],y[i])].clear(),
        st1[get1(x[i],y[i])].clear();
    mp.clear();vt.clear();
    n=read();d=read()>>1;
    for(int i=1;i<=n;i++){
        x[i]=read()+100000;y[i]=read()+100000;
        mp[{x[i],y[i]}]=i;
        st0[get0(x[i],y[i])].insert({x[i],i});
        st1[get1(x[i],y[i])].insert({x[i],i});
        for(int j=0;j<4;j++)
            vt.push_back({x[i]+nxt[j][0]*d,y[i]+nxt[j][1]*d});
    }
    for(pii tt:vt){
        int x=tt.first,y=tt.second;
        vector<int>ans;
        if(mp.count({x-d,y}))ans.push_back(mp[{x-d,y}]);
        if(mp.count({x,y-d}))ans.push_back(mp[{x,y-d}]);
        if(get1(x+d,y)>=N<<1||get1(x+d,y)<0)continue;
        auto tmp=st1[get1(x+d,y)].lower_bound({x,0});
        if(tmp!=st1[get1(x+d,y)].end()&&(tmp->first)<=x+d)ans.push_back(tmp->second);
        if(ans.size()>=3){
            for(auto j:ans)printf("%lld ",j);
            puts("");return;
        }
    }
    for(pii tt:vt){
        int x=tt.first,y=tt.second;
        vector<int>ans;
        if(mp.count({x+d,y}))ans.push_back(mp[{x+d,y}]);
        if(mp.count({x,y+d}))ans.push_back(mp[{x,y+d}]);
        if(get1(x-d,y)>=N<<1||get1(x-d,y)<0)continue;
        auto tmp=st1[get1(x-d,y)].lower_bound({x-d,0});
        if(tmp!=st1[get1(x-d,y)].end()&&(tmp->first)<=x)ans.push_back(tmp->second);
        if(ans.size()>=3){
            for(auto j:ans)printf("%lld ",j);
            puts("");return;
        }
    }
    for(pii tt:vt){
        int x=tt.first,y=tt.second;
        vector<int>ans;
        if(mp.count({x-d,y}))ans.push_back(mp[{x-d,y}]);
        if(mp.count({x,y+d}))ans.push_back(mp[{x,y+d}]);
        if(get0(x+d,y)>=N<<1||get0(x+d,y)<0)continue;
        auto tmp=st0[get0(x+d,y)].lower_bound({x,0});
        if(tmp!=st0[get0(x+d,y)].end()&&(tmp->first)<=x+d)ans.push_back(tmp->second);
        if(ans.size()>=3){
            for(auto j:ans)printf("%lld ",j);
            puts("");return;
        }
    }
    for(pii tt:vt){
        int x=tt.first,y=tt.second;
        vector<int>ans;
        if(mp.count({x+d,y}))ans.push_back(mp[{x+d,y}]);
        if(mp.count({x,y-d}))ans.push_back(mp[{x,y-d}]);
        if(get0(x-d,y)>=N<<1||get1(x-d,y)<0)continue;
        auto tmp=st0[get0(x-d,y)].lower_bound({x-d,0});
        if(tmp!=st0[get0(x-d,y)].end()&&(tmp->first)<=x)ans.push_back(tmp->second);
        if(ans.size()>=3){
            for(auto j:ans)printf("%lld ",j);
            puts("");return;
        }
    }
    puts("0 0 0");
    return;
}
signed main(){
    int T=read();
    while(T--)Main();
    return 0;
}
```

---

## 作者：huangrenheluogu (赞：3)

不~~会~~用切比雪夫距离题。

手玩可以发现，和 $(x,y)$ 的 Manhattan 距离为 $d$ 的点构成一个以 $(x,y)$ 为中心菱形。

![](https://cdn.luogu.com.cn/upload/image_hosting/bfn1vhad.png)

考虑一个点 $(x_0,y_0)$ 作为中心点，只考虑 $x\ge x_0,y\ge x_0$ 的点（就是 Line1），画画图可以发现其余情况是可以通过旋转得到的。

可以把点按照 $x+y$ 排序，然后装到 set 里，对于每一条线，找到两个 Manhattan 距离为 $d$ 的点，判断是否存在符合条件的点作为中心点。

这里可能有一个问题，解一定可以表示成中心点 + 边缘一条线段的形式吗？

考虑 Line1 和 Line3 的点距离为 $2d$，我们只需要考虑相邻两条线的距离，可以通过旋转转到 Line1 和 Line2 的情况。

不妨两个点满足 $x_1\le x_0,y_1\ge y_0,x_2\ge x_0,y_2\ge y_0$。

记 $a=x_0-x_1,b=x_2-x_0$，可以得到 $|a-b|+(a+b)=d$，拆一个绝对值可以得到：$0\le a\le \dfrac{d}{2},b=\dfrac{d}{2}$ 或 $a=\dfrac{d}{2},0\le b\le \dfrac{d}{2}$。发现满足 $a=\dfrac{d}{2}$ 或者 $b=\dfrac{d}{2}$，右在类似上面菱形的线上了。

可以通过旋转，代码很好实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, V = 4e5 + 5, ad = 1e5, maxn = 2e5;
int T, n, d, A, B, C, tmp;
struct node{
    int x, y, id;
    inline void calc(){
        int nx = y, ny = maxn - x;
        x = nx, y = ny;
    }
}a[N];
inline bool operator < (node x, node y){
    return x.x < y.x;
}
inline bool cmp(node x, node y){
    if(x.x + x.y == y.x + y.y) return x.x < y.x;
    return x.x + x.y < y.x + y.y;
}
set<node> s[V];
inline bool check(){
    sort(a + 1, a + n + 1, cmp);
    for(int i = 1; i <= n; i++){
        s[a[i].x + a[i].y].insert(a[i]);
    }
    for(int i = 1, j = 1; i <= n; i++){
        if(j < i) j = i;
        while(j < n && a[j + 1].x + a[j + 1].y == a[i].x + a[i].y && a[j + 1].x - a[i].x <= d / 2) j++;
        if(a[j].x - a[i].x == d / 2){
            tmp = a[i].x + a[i].y - d;
            if(tmp < 0) continue ;
            auto it = s[tmp].lower_bound((node){a[j].x - d, 0, 0});
            if(it == s[tmp].end()){
                continue ;
            }
            if((*it).x <= a[i].x){
                A = a[i].id, B = a[j].id, C = (*it).id;
                return 1;
            }
        }
    }
    for(int i = 1; i <= n; i++){
        s[a[i].x + a[i].y].clear();
    }
    return 0;
}
inline void solve(){
    A = B = C = 0;
    int TT = 4;
    while(TT--){
        if(check()) return ;
        for(int i = 1; i <= n; i++) a[i].calc();
    }
}
int main(){
    // freopen("data.in", "r", stdin);
    // freopen("code.out", "w", stdout);
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &d);
        for(int i = 1; i <= n; i++){
            scanf("%d%d", &a[i].x, &a[i].y);
            a[i].id = i;
            a[i].x += ad, a[i].y += ad;
        }
        solve();
        printf("%d %d %d\n", A, B, C);
        for(int i = 1; i <= n; i++) s[a[i].x + a[i].y].clear();
    }
    return 0;
}
```

---

## 作者：Mashu77 (赞：3)

给定平面上 $n$ 个点，曼哈顿距离为 $|x_i-x_j|+|y_i-y_j|$，找出三个点使得两两距离都是 $d$，其中 $d$ 是偶数。

往偏序想你就甲烷了，思考一些更简单的东西，一个套路是先尝试固定一个点，然后找另外两个点，不难发现合法的范围类似一个菱形，第三个点则是两个菱形的焦点。

注意到一个简化的性质：必然有两个点使得 $|x_i-x_j|=|y_i-y_j|$，然后你把这样的数对称作斜线，那么你只要考虑一个点右上方是否有这样的斜线就行，但是要每次反转坐标轴，这样可以减少讨论，每次反转而不是讨论。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

#define N 400000

int i,j,k,n,m,t,x[N+50],y[N+50],yes;
tuple<int,int,int> ans;

void mn(){
	if(yes)return;
	map<int,map<int,int> > mp;
	for(i=1;i<=n;i++){
		mp[x[i]][y[i]]=i;
	}
	for(i=1;i<=n;i++)if(mp[x[i]].count(y[i]+m)){
		for(auto d:{-m,m}){
			if(mp.count(x[i]+d)){
				auto it=mp[x[i]+d].lower_bound(y[i]);
				if(it==mp[x[i]+d].end())continue;
				auto [pos,id]=*it;
				if(pos<=y[i]+m){
					yes=1;
					ans={i,mp[x[i]][y[i]+m],id};
					return;
				}
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m;
		yes=0; ans={0,0,0};
		for(i=1;i<=n;i++){
			cin>>j>>k;
			x[i]=j+k; y[i]=j-k;
		}
		for(int T=1;T<=4;T++){
			
            mn();
			for(i=1;i<=n;i++)y[i]=-y[i];
			if(T==2){
				for(i=1;i<=n;i++)swap(x[i],y[i]);
			}
		}
		auto [i,j,k]=ans;
		cout<<i<<' '<<j<<' '<<k<<'\n';
	}
}

---

## 作者：Fimlty (赞：3)

- **题意**

给定 $n,d$ 以及 $n$ 个点 $(x_i,y_i)$ ，询问是否存在 $(i,j,k)$ 使得点 $i,j,k$ 两两之间的曼哈顿距离均为 $d$ 。

- **Solution**

~~算是一种纯 DS 的写法。~~

手搓几组样例发现，满足条件的三个点中，必然存在两个点使得 $|x_i - x_j| = |y_i - y_j|$ 。既然这样，可以枚举每一个点，找到另外一个点满足上述条件。可能性只有 $4$ 种。

但是实际上只枚举下面两种就能覆盖所有可能性。

![](https://cdn.luogu.com.cn/upload/image_hosting/lsteiu7c.png)

用第一种做例子，考虑合法的第三个点在哪里。
我们可以分别画出与 $(x,y)$ 和 $(x+d/2,y-d/2)$ 曼哈顿为 $d$ 的点组成的直线。

![](https://cdn.luogu.com.cn/upload/image_hosting/po821r3w.png)

红色线段是满足条件的点集，绿色直线是其所在直线。

~~怎么找到一个合法点呢？暴力！~~

当然直接暴力是不可取的，但是可以对每一条直线（可以理解为每一种 $x+y$ 的取值）用 set 维护上面存在的点，然后使用 lower_bound 找到纵坐标大于等于 $y$ 的最小的 $y_0$ 。若这样的 $y_0$ 已经超出了红色线段（即 $y_0>y+d/2$ ）那么当前枚举的情况无解。

需要注意的是，满足条件的点集在黑色线段下方还有一条，由于本质相同，不再赘述。

至于另外一种从右上到左下的情况，同样可以维护每一条直线上的点，只不过直线的编号要改成 $y-x$。

- **实现细节（Code）**

献上代码

```cpp
#include<iostream>
#include<map>
#include<set>
using namespace std;
int t, n, d;
void solve() {
	cin >> n >> d;
	map<pair<int, int>, int>id;
	map<int, set<int>>a, b;
	set<pair<int, int>>c;
	for (int x, y, i = 1; i <= n; i++)
		cin >> x >> y, a[x + y].insert(y), b[y - x].insert(y), c.insert({ x, y }), id[{x, y}] = i;
	for (auto [x, y] : c) {
		if (c.count({ x + d / 2, y - d / 2 })) {
			int p = x + d / 2, q = y - d / 2, k1 = x + y + d, k2 = x + y - d;
			auto it1 = a[k1].lower_bound(q + d / 2), it2 = a[k2].lower_bound(q - d / 2);
			if (it1 != a[k1].end() && *it1 <= y + d / 2) {
				cout << id[{x, y}] << ' ' << id[{p, q}] << ' ' << id[{k1 - (*it1), * it1}] << '\n';
				return;
			}
			if (it2 != a[k2].end() && *it2 <= y - d / 2) {
				cout << id[{x, y}] << ' ' << id[{p, q}] << ' ' << id[{k2 - (*it2), * it2}] << '\n';
				return;
			}
		}
		if (c.count({ x - d / 2, y - d / 2 })) {
			int p = x - d / 2, q = y - d / 2, k1 = y - x + d, k2 = y - x - d;
			auto it1 = b[k1].lower_bound(q + d / 2), it2 = b[k2].lower_bound(q - d / 2);
			if (it1 != b[k1].end() && *it1 <= y + d / 2) {
				cout << id[{x, y}] << ' ' << id[{p, q}] << ' ' << id[{(*it1) - k1, * it1}] << '\n';
				return;
			}
			if (it2 != b[k2].end() && *it2 <= y - d / 2) {
				cout << id[{x, y}] << ' ' << id[{p, q}] << ' ' << id[{(*it2) - k2, * it2}] << '\n';
				return;
			}
		}
	}
	cout << 0 << ' ' << 0 << ' ' << 0 << '\n';
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> t;
	while (t--) {
		solve();
	}
}
```

输入时，储存点的信息，加入到所在的两种直线的 set 中，注意题目要求输出编号，因此再开一个 map 存编号。

然后枚举每个点，分别做两种大情况，再分别判断上下两条线段上是否存在合法点，注意不存在要输出 0 0 0 。

---

## 作者：TTpandaS (赞：1)

首先旋转，将曼哈顿距离转化为切比雪夫距离。

然后考虑可能成为答案的三个点 $(x_1,y_1),(x_2,y_2),(x_3,y_3)$，满足切比雪夫距离两两为 $d$ 的条件为 $x_1=x_2 \wedge y_1+d=y_2 \wedge x_3=x_1 \pm d \wedge y_1 \leq y_3 \leq y_2$ 或 $y_1=y_2 \wedge x_1+d=x_2 \wedge y_3=y_1 \pm d \wedge x_1 \leq x_3 \leq x_2$。

首先考虑第一种情况。将 $x$ 作为第一关键字从小到大排， $y$ 作为第二关键字从小到大排。然后枚举 $(x_2,y_2)$，找到 $x=x_2$ 的区间，二分出 $(x1,y1)$ 位置，再二分找到 $x=x_2 \pm d$ 的区间，再在里面二分出 $(x_3,y_3)$ 的位置。

第二种情况同理。

一共打了 $8$ 个二分，代码较长，码风较丑。

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  const int N=2e5+5;
  int T;
  int n,d;
  struct node{
      int x,y,id;
  }a[N];
  bool cmp1(node x,node y){
      if(x.x==y.x){
          return x.y<y.y;
      }
      return x.x<y.x;	
  }
  bool cmp2(node x,node y){
      if(x.y==y.y){
          return x.x<y.x;
      }
      return x.y<y.y;	
  }
  signed main(){
      scanf("%d",&T);
      while(T--){
          scanf("%d %d",&n,&d);
          for(int i=1,x,y;i<=n;i++){
              scanf("%d %d",&x,&y);
              a[i].x=x+y,a[i].y=x-y;
              a[i].id=i;
          }
          sort(a+1,a+n+1,cmp1);
          int lst=1;
          bool flag=0;
          for(int i=2;i<=n;i++){
              if(a[i].x!=a[i-1].x){
                  lst=i;
                  continue;
              }
              int l=lst,r=i,res=i;
              while(l<=r){
                  int mid=(l+r)>>1;
                  if(a[mid].y<=a[i].y-d){
                      l=mid+1;
                      res=mid;
                  }
                  else{
                      r=mid-1;
                  }
              }
              if(a[res].y+d==a[i].y){
                  l=1,r=n;
                  int R=i;
                  while(l<=r){
                      int mid=(l+r)>>1;
                      if(a[mid].x<=a[i].x-d){
                          l=mid+1;
                          R=mid;
                      }
                      else{
                          r=mid-1;
                      }
                  }
                  if(a[R].x==a[i].x-d){
                      l=1,r=n;
                      int L=i;
                      while(l<=r){
                          int mid=(l+r)>>1;
                          if(a[mid].x>=a[i].x-d){
                              r=mid-1;
                              L=mid;
                          }
                          else{
                              l=mid+1;
                          }
                      }
                      l=L,r=R;
                      int res1=L;
                      while(l<=r){
                          int mid=(l+r)>>1;
                          if(a[mid].y>=a[i].y-d){
                              r=mid-1;
                              res1=mid;
                          }
                          else{
                              l=mid+1;
                          }
                      }
                      if(a[res1].y>=a[i].y-d&&a[res1].y<=a[i].y){
                          printf("%d %d %d\n",a[i].id,a[res].id,a[res1].id);
                          flag=1;
                          break;						
                      }
                  }
                  l=1,r=n,R=i;
                  while(l<=r){
                      int mid=(l+r)>>1;
                      if(a[mid].x<=a[i].x+d){
                          l=mid+1;
                          R=mid;
                      }
                      else{
                          r=mid-1;
                      }
                  }
                  if(a[R].x==a[i].x+d){
                      l=1,r=n;
                      int L=i;
                      while(l<=r){
                          int mid=(l+r)>>1;
                          if(a[mid].x>=a[i].x+d){
                              r=mid-1;
                              L=mid;
                          }
                          else{
                              l=mid+1;
                          }
                      }
                      l=L,r=R;
                      int res1=L;
                      while(l<=r){
                          int mid=(l+r)>>1;
                          if(a[mid].y>=a[i].y-d){
                              r=mid-1;
                              res1=mid;
                          }
                          else{
                              l=mid+1;
                          }
                      }
                      if(a[res1].y>=a[i].y-d&&a[res1].y<=a[i].y){
                          printf("%d %d %d\n",a[i].id,a[res].id,a[res1].id);
                          flag=1;
                          break;						
                      }
                  }				
              }
          }
          if(flag){
              continue;
          }
          sort(a+1,a+n+1,cmp2);
          lst=1;
          for(int i=2;i<=n;i++){
              if(a[i].y!=a[i-1].y){
                  lst=i;
                  continue;
              }
              int l=lst,r=i,res=i;
              while(l<=r){
                  int mid=(l+r)>>1;
                  if(a[mid].x<=a[i].x-d){
                      l=mid+1;
                      res=mid;
                  }
                  else{
                      r=mid-1;
                  }
              }
              if(a[res].x+d==a[i].x){
                  l=1,r=n;
                  int R=i;
                  while(l<=r){
                      int mid=(l+r)>>1;
                      if(a[mid].y<=a[i].y-d){
                          l=mid+1;
                          R=mid;
                      }
                      else{
                          r=mid-1;
                      }
                  }
                  if(a[R].y==a[i].y-d){
                      l=1,r=n;
                      int L=i;
                      while(l<=r){
                          int mid=(l+r)>>1;
                          if(a[mid].y>=a[i].y-d){
                              r=mid-1;
                              L=mid;
                          }
                          else{
                              l=mid+1;
                          }
                      }
                      l=L,r=R;
                      int res1=L;
                      while(l<=r){
                          int mid=(l+r)>>1;
                          if(a[mid].x>=a[i].x-d){
                              r=mid-1;
                              res1=mid;
                          }
                          else{
                              l=mid+1;
                          }
                      }
                      if(a[res1].x>=a[i].x-d&&a[res1].x<=a[i].x){
                          printf("%d %d %d\n",a[i].id,a[res].id,a[res1].id);
                          flag=1;
                          break;						
                      }
                  }
                  l=1,r=n,R=i;
                  while(l<=r){
                      int mid=(l+r)>>1;
                      if(a[mid].y<=a[i].y+d){
                          l=mid+1;
                          R=mid;
                      }
                      else{
                          r=mid-1;
                      }
                  }
                  if(a[R].y==a[i].y+d){
                      l=1,r=n;
                      int L=i;
                      while(l<=r){
                          int mid=(l+r)>>1;
                          if(a[mid].y>=a[i].y+d){
                              r=mid-1;
                              L=mid;
                          }
                          else{
                              l=mid+1;
                          }
                      }
                      l=L,r=R;
                      int res1=L;
                      while(l<=r){
                          int mid=(l+r)>>1;
                          if(a[mid].x>=a[i].x-d){
                              r=mid-1;
                              res1=mid;
                          }
                          else{
                              l=mid+1;
                          }
                      }
                      if(a[res1].x>=a[i].x-d&&a[res1].x<=a[i].x){
                          printf("%d %d %d\n",a[i].id,a[res].id,a[res1].id);
                          flag=1;
                          break;						
                      }
                  }				
              }
          }
          if(!flag){
              puts("0 0 0");
          }
      } 
      return 0;
  }
```

---

## 作者：喵仔牛奶 (赞：0)

## Solution

先转切比雪夫。

讨论取到 $\max$ 的是 $x$ 坐标还是 $y$ 坐标，可以发现不可能三个都取同一个坐标。因此，一定是两个取 $x$ 一个取 $y$，或者两个取 $y$ 一个取 $x$。

考虑两个取 $x$ 一个取 $y$，另一种情况交换 $x,y$ 再跑一遍即可。

设 $(A,B),(B,C)$ 两对取了 $x$ 坐标，那么不可能 $x_B=x_A-d,x_C=x_A+d$， 不然 $B,C$ 距离有 $2d$。因此有 $x_B=x_C$。

钦定 $y_B<y_C$，枚举 $B$，此时可以知道 $C=(x_B,y_B+d)$。那么合法的 $A$ 条件就是 $\lvert x_A-x_B\rvert =d\land y_A\in[x_B,x_C]$。用 set 维护 $s_i$ 表示 $x_j=i$ 的点 $j$ 的 $y_j$ 的集合，枚举 $x_A=x_B-d$ 还是 $x_A=x_B+d$，在 set 里二分看看有没有即可。

代码比较短。

## Code

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5;
	int n, d, x, y, A, B, C, a[N], b[N];
	map<int, set<int>> mp; map<pii, int> id;
	int main() {
		cin >> n >> d, A = B = C = 0;
		REP(i, 1, n) {
			cin >> x >> y;
			a[i] = x + y, b[i] = x - y;
		}
		REP(t, 0, 3) {
			int dx = (t & 1 ? -d : d);
			REP(i, 1, n)
				mp[a[i]].insert(b[i]), id[{a[i], b[i]}] = i;
			for (auto &[x, s] : mp) {
				if (!mp.count(x + dx)) continue;
				auto &t = mp[x + dx];
				for (int y : s) {
					if (!s.count(y + d)) continue;
					auto it = t.lower_bound(y);
					if (it == t.end() || *it > y + d) continue;
					A = id[{x, y}], B = id[{x, y + d}], C = id[{x + dx, *it}]; break;
				}
			}
			mp.clear(), id.clear();
			if (A > 0) break;
			if (t == 1) REP(i, 1, n) swap(a[i], b[i]);
		}
		cout << A << ' ' << B << ' ' << C << '\n'; 
		return 0;
	}
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	int T = 1; cin >> T;
	while (T --) Milkcat::main();
	return 0;
}
```

---

## 作者：快斗游鹿 (赞：0)

首先观察满足条件的三个点会长什么样。由于距离一个点曼哈顿距离相等的点一定会形成菱形，假设我们已经确定了点 $A,B$（假设 $B$ 在 $A$ 右下方，在左下方同理），那么可以得到下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/q3d9e0xt.png)

图中所标的 $C_1,C_2$ 是两种可能的第三点位置。容易发现至少存在一条过其中两点的直线斜率为 $1$ 或 $-1$。且剩下的一点到该直线水平距离为 $d$。

上述信息已经足以解决问题。下面只考虑 $B$ 在 $A$ 右下方，且 $C$ 在 $A$ 右上方的情况，剩下情况同理。

先枚举点 $A$，那么自然可以确定出一个唯一的 $C$。使用 set 维护每条斜率为 $1$ 的直线，直观地感受一下，$B$ 点是可以在一定范围内移动的，具体地，设 $A$ 坐标为 $(x,y)$，则有 $C$ 坐标为 $(x+\dfrac{d}{2},y+\dfrac{d}{2})$。由于 $A,C$ 一定要在 $B$ 的菱形上，所以可以得到 $B$ 的 $x$ 坐标取值范围为 $[x+\dfrac{d}{2},x]$。在 set 上做二分即可。

实现上可能和上文略有不同。


```cpp
#include<bits/stdc++.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <math.h>
#include <cstdio>
#define int long long
using namespace std;
const int inf=1e18;
struct Mod{
    int m,p;
    void init(int pp){m=((__int128)1<<64)/pp;p=pp;}
    int operator ()(int x){
        return x-((__int128(x)*m)>>64)*p;//0~2mod-1
    }
}mo;
bool M1;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void ckmx(int &x,int y){x=max(x,y);}
void ckmi(int &x,int y){x=min(x,y);}
const int N=2e6+5;
struct Node{
    int x,y;
}a[N];
int n,d;
bool flag;
set<pair<int,int> >s[N];
void work(){
    for(int i=1;i<=n;i++)a[i].x+=2e5,a[i].y+=2e5;
    for(int i=1;i<=n;i++){
        s[a[i].x+a[i].y].clear();
        s[a[i].x+a[i].y+d].clear();
        if(a[i].x+a[i].y-d>=0)s[a[i].x+a[i].y-d].clear();
    }
    for(int i=1;i<=n;i++)s[a[i].x+a[i].y].insert({a[i].x,i});
    for(int i=1;i<=n;i++){
        int w=a[i].x+a[i].y;
        auto x=s[w].lower_bound({a[i].x+d/2,-1});
        if(x!=s[w].end()&&x->first==a[i].x+d/2){
            auto y=s[w+d].lower_bound({a[i].x+d/2,-1});
            if(y!=s[w+d].end()&&y->first<=a[i].x+d){
                cout<<i<<" "<<x->second<<" "<<y->second<<'\n';flag=1;return;
            }
            if(a[i].x+a[i].y-d<0)continue;
            y=s[w-d].lower_bound({a[i].x-d/2,-1});
            if(y!=s[w-d].end()&&y->first<=a[i].x){
                cout<<i<<" "<<x->second<<" "<<y->second<<'\n';flag=1;return;
            }
        }
    }
    for(int i=1;i<=n;i++)a[i].x-=2e5,a[i].y-=2e5;
}
void  solve(){flag=0;
    n=read();d=read();
    for(int i=1;i<=n;i++)a[i].x=read(),a[i].y=read();
    work();
    if(flag)return;
    for(int i=1;i<=n;i++)a[i].x=-a[i].x;//另一种情况
    work();
    if(flag)return;
    puts("0 0 0");
}
bool M2;
signed main(){
    freopen("data.in","r",stdin);
    //ios::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
    int T;T=read();while(T--)solve();
    cerr<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC<<"s"<<endl;
    cerr<<"Memory:"<<(&M1-&M2)/1024/1024<<"MB"<<endl;
    return 0;
}

```

---

## 作者：Ghosty_Neutrino (赞：0)

## 题意
给定 $n$ 个点，找出三个点使得这三个点两两之间的曼哈顿距离为偶数 $d$。
## 分析
举个例子，与一个点的曼哈顿距离为斜 $45$ 度的正方形。

设这个点坐标为 $(x,y)$。

考虑另外两个点可能在哪些位置：

如果另外两个点在正方形的同一条边上，那么这两个点的横纵坐标的差的绝对值一定都等于 $d \div 2$，即满足 $|x_1-x_2|=d \div 2$，$|y_1-y_2|=d \div 2$。

如果不在同一条边上，那么一定有一个点与 $(x,y)$ 满足 $|x_1-x|=d \div 2$，$|y_1-y|=d \div 2$。

也就是说如果可以找到三个点满足两两之间的曼哈顿距离为偶数 $d$，那么这三个点中一定存在两个点满足 $|x_1-x_2|=d \div 2$，$|y_1-y_2|=d \div 2$。

那么做法就很简单了，枚举其中一个点，判断是否存在另一个点满足 $|x_1-x_2|=d \div 2$，$|y_1-y_2|=d \div 2$。这个可以用 map 判断，然后就是找到一个在这两个点的正方形的交集上的点，交集其实就是两条线段，可以预处理排序后用二分判断。

---

## 作者：allqpsi (赞：0)

### 前置知识：切比雪夫距离。

CF 老套路：将曼哈顿距离转为切比雪夫距离。我们将所有的点转换为 $(x+y+200000+d,x-y+200000+d)$ 后面加的数是为方便储存。

这时我们来看三个点要满足什么样的性质才满足曼哈顿距离都为 $d$，分别设三个点坐标为 $(x_{1},y_{1})$，$(x_{2},y_{2})$，$(x_{3},y_{3})$。

假如三个数均是 $\operatorname{abs}( x_{i}-x_{j})$ 大于 $\operatorname{abs}( y_{i}-y_{j})$，此时我们发现若 $x_{1}-x_{2},x_{2}-x_{3}$ 均为正数，那两个式子相加便得到 $x_{1}-x_{3}=2 \times d$ 显然不成立，符号反之亦然。而若两个式子符号相异，那两个式子相加便得到 $x_{1}-x_{3}=0$ 也不成立。得出结论性质为：两对点 $x$ 相减得 $d$ 并一对点 $y$ 相减得 $d$ 或两对点 $y$ 相减得 $d$ 并一对点 $x$ 相减得 $d$。

我们发现，将 $x,y$ 反过来便使两个性质相同，所以只需考虑一种关系即可。

再次推论，发现对于一对点 $y$ 相减得 $d$ 中的两个点 $x$ 必相同，不然若 $x$ 不同，它们必相差 $2 \times d$ 而此时 $x$ 相减大于 $y$ 相减。

此时得出思路：我们将每个点按 $x$ 插到一个桶内，然后枚举 $x$ 相同的点，若能找到 $y$ 相差 $d$ 地两个点，找到 $x$ 与其相差 $d$ 的一个点，判断是否符合大于另外的切比雪夫相差。然后将 $x,y$ 反过来，再做一遍。

代码有点长，但很多部分可以复制粘贴。

#### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define set(ai) memset(ai,0,sizeof(ai));
#define fset(ai) memset(ai,127,sizeof(ai));
#define hset(ai) memset(ai,63,sizeof(ai));
#define rep(i,s,t) for(int i=s;i<=t;i++)
#define frep(i,s,t) for(int i=s;i>=t;i--)
#define rep1(i,s,t) for(int i=s;i<t;i++)
#define frep1(i,s,t) for(int i=s;i>t;i--)
#define srt(ai,n) sort(ai+1,ai+n+1)
#define csrt(ai,n,cmp) sort(ai+1,ai+n+1,cmp)
#define pb push_back
#define ppb pop_back
using namespace std;
const int N=2e5+5;
int t,xi[N],yi[N],n,d,ls;
struct node{
	int x,y,id;
}vi[N];
int f1[N*5],a,b;
vector<int>f2[N*5];
bool isit=0;
bool cmp(node a,node b){return a.x<b.x;}
bool cmp2(node a,node b){return a.y<b.y;}
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>d,isit=0;
		rep(i,1,n)cin>>xi[i]>>yi[i],a=xi[i],xi[i]=xi[i]+yi[i]+200000+d,yi[i]=a-yi[i]+200000+d,vi[i]=node{xi[i],yi[i],i};
		rep(i,1,n)f2[xi[i]].pb(i);
		csrt(vi,n,cmp);
		ls=1;
		rep(i,1,n){
			if(isit)break;
			if(i==1){
				f1[vi[i].y]=vi[i].id;continue;
			}
			if(vi[i].x!=vi[i-1].x){
				rep(j,ls,i-1)f1[vi[j].y]=0;
				ls=i,f1[vi[i].y]=vi[i].id;continue;
			}
			if(f1[vi[i].y-d]){
				rep1(j,0,f2[vi[i].x-d].size())
					if(abs((b=yi[(a=f2[vi[i].x-d][j])])-vi[i].y+d)<=d&&abs(b-vi[i].y)<=d){
						cout<<vi[i].id<<" "<<f1[vi[i].y-d]<<" "<<a<<endl,isit=1;break;
					}
				if(isit)break;
				rep1(j,0,f2[vi[i].x+d].size())
					if(abs((b=yi[(a=f2[vi[i].x+d][j])])-vi[i].y+d)<=d&&abs(b-vi[i].y)<=d){
						cout<<vi[i].id<<" "<<f1[vi[i].y-d]<<" "<<a<<endl,isit=1;break;
					}
			}
			if(isit)break;
			if(f1[vi[i].y+d]){
				rep1(j,0,f2[vi[i].x-d].size())
					if(abs((b=yi[(a=f2[vi[i].x-d][j])])-vi[i].y-d)<=d&&abs(b-vi[i].y)<=d){
						cout<<vi[i].id<<" "<<f1[vi[i].y+d]<<" "<<a<<endl,isit=1;break;
					}
				if(isit)break;
				rep1(j,0,f2[vi[i].x+d].size())
					if(abs((b=yi[(a=f2[vi[i].x+d][j])])-vi[i].y-d)<=d&&abs(b-vi[i].y)<=d){
						cout<<vi[i].id<<" "<<f1[vi[i].y+d]<<" "<<a<<endl,isit=1;break;
					}
			}
			f1[vi[i].y]=vi[i].id;
		}rep(j,ls,n)f1[vi[j].y]=0;
		rep(i,1,n)swap(xi[i],yi[i]),swap(vi[i].x,vi[i].y);
		rep(i,1,n)f2[yi[i]].clear();
		rep(i,1,n)f2[xi[i]].pb(i);
		csrt(vi,n,cmp);
		ls=1;
		rep(i,1,n){
			if(isit)break;
			if(i==1){
				f1[vi[i].y]=vi[i].id;continue;
			}
			if(vi[i].x!=vi[i-1].x){
				rep(j,ls,i-1)f1[vi[j].y]=0;
				ls=i,f1[vi[i].y]=vi[i].id;continue;
			}
			if(f1[vi[i].y-d]){
				rep1(j,0,f2[vi[i].x-d].size())
					if(abs((b=yi[(a=f2[vi[i].x-d][j])])-vi[i].y+d)<=d&&abs(b-vi[i].y)<=d){
						cout<<vi[i].id<<" "<<f1[vi[i].y-d]<<" "<<a<<endl,isit=1;break;
					}
				if(isit)break;
				rep1(j,0,f2[vi[i].x+d].size())
					if(abs((b=yi[(a=f2[vi[i].x+d][j])])-vi[i].y+d)<=d&&abs(b-vi[i].y)<=d){
						cout<<vi[i].id<<" "<<f1[vi[i].y-d]<<" "<<a<<endl,isit=1;break;
					}
			}
			if(isit)break;
			if(f1[vi[i].y+d]){
				if(!f2[vi[i].x-d].empty())
					rep1(j,0,f2[vi[i].x-d].size())
						if(abs((b=yi[(a=f2[vi[i].x-d][j])])-vi[i].y-d)<=d&&abs(b-vi[i].y)<=d){
							cout<<vi[i].id<<" "<<f1[vi[i].y+d]<<" "<<a<<endl,isit=1;break;
						}
				if(isit)break;
				if(!f2[vi[i].x+d].empty())
					rep1(j,0,f2[vi[i].x+d].size())
						if(abs((b=yi[(a=f2[vi[i].x+d][j])])-vi[i].y-d)<=d&&abs(b-vi[i].y)<=d){
							cout<<vi[i].id<<" "<<f1[vi[i].y+d]<<" "<<a<<endl,isit=1;break;
						}
			}
			f1[vi[i].y]=vi[i].id;
		}rep(j,ls,n)f1[vi[j].y]=0;
		rep(i,1,n)f2[xi[i]].clear();
		if(!isit)cout<<"0 0 0"<<endl;
	}
}

```

---

