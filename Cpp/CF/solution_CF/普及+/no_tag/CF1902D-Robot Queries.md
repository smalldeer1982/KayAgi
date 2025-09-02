# Robot Queries

## 题目描述

There is an infinite $ 2 $ -dimensional grid. Initially, a robot stands in the point $ (0, 0) $ . The robot can execute four commands:

- U — move from point $ (x, y) $ to $ (x, y + 1) $ ;
- D — move from point $ (x, y) $ to $ (x, y - 1) $ ;
- L — move from point $ (x, y) $ to $ (x - 1, y) $ ;
- R — move from point $ (x, y) $ to $ (x + 1, y) $ .

You are given a sequence of commands $ s $ of length $ n $ . Your task is to answer $ q $ independent queries: given four integers $ x $ , $ y $ , $ l $ and $ r $ ; determine whether the robot visits the point $ (x, y) $ , while executing a sequence $ s $ , but the substring from $ l $ to $ r $ is reversed (i. e. the robot performs commands in order $ s_1 s_2 s_3 \dots s_{l-1} s_r s_{r-1} s_{r-2} \dots s_l s_{r+1} s_{r+2} \dots s_n $ ).

## 说明/提示

In the first query of the first sample, the path of the robot looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1902D/4aac546138020132b74e07749db84bb06a513da8.png)In the second query of the first sample, the path of the robot looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1902D/b189da90dcd98cd79a3624a3015d7f2cf2e922e4.png)In the third query of the first sample, the path of the robot looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1902D/5220422eecc4ff8d70f683171d72758af4ccdbfe.png)

## 样例 #1

### 输入

```
8 3
RDLLUURU
-1 2 1 7
0 0 3 4
0 1 7 8```

### 输出

```
YES
YES
NO```

## 样例 #2

### 输入

```
4 2
RLDU
0 0 2 2
-1 -1 2 3```

### 输出

```
YES
NO```

## 样例 #3

### 输入

```
10 6
DLUDLRULLD
-1 0 1 10
-1 -2 2 5
-4 -2 6 10
-1 0 3 9
0 1 4 7
-3 -1 5 8```

### 输出

```
YES
YES
YES
NO
YES
YES```

# 题解

## 作者：Creeper_l (赞：4)

题意：有一个二维平面直角坐标系，给定一串向某个方向移动 $1$ 个单位的操作。

有 $q$ 个询问，对于每个询问给定 $x,y,l,r$，问如果倒着做 $l$ 到 $r$ 这段区间中的操作，是否会经过 $(x,y)$。

ds 题。先预处理出 $sx_i,sy_i$ 表示执行完操作 $i$ 后的位置，如果在 $[l,r]$ 区间外已经经过 $(x,y)$ 了，那么最终也一定会经过。再考虑 $[l,r]$ 区间内，我们会发现，如果正序执行操作时会到达 $(nx,ny)$ 的话，那么倒序执行操作时一定会经过 $(sx_{l-1}+sx_r-nx,sy_{l-1}+sy_r-ny)$。所以只需要查询区间内是否存在一个坐标即可。可以线段树，这里用的离线 vector + map。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef pair <int,int> pii;
map <pii,int> f,s,mp;
const int MAXN = 2e5 + 10;
int n,q,x,y,l,r,sx[MAXN],sy[MAXN],ans[MAXN];
struct Node{int i,l,x,y;};
vector <Node> a[MAXN];
char c[MAXN];
signed main()
{
	cin >> n >> q >> (c + 1);
	for(int i = 1;i <= n;i++)
	{
		sx[i] = sx[i - 1],sy[i] = sy[i - 1];
		if(c[i] == 'R') sx[i]++;
		if(c[i] == 'L') sx[i]--;
		if(c[i] == 'U') sy[i]++;
		if(c[i] == 'D') sy[i]--;
	}
	for(int i = 0;i <= n;i++) f[make_pair(sx[i],sy[i])] = i;
	for(int i = n;i >= 0;i--) s[make_pair(sx[i],sy[i])] = i;
	for(int i = 1;i <= q;i++)
	{
		cin >> x >> y >> l >> r;
		if(f.count(make_pair(x,y)) && f[make_pair(x,y)] >= r) ans[i] = 1;
		if(s.count(make_pair(x,y)) && s[make_pair(x,y)] < l) ans[i] = 1;
		a[r].push_back({i,l,sx[l - 1] + sx[r] - x,sy[l - 1] + sy[r] - y});
	}
	for(int i = 0;i <= n;i++)
	{
		mp[make_pair(sx[i],sy[i])] = i;
		for(int j = 0;j < a[i].size();j++) 
			ans[a[i][j].i] |= mp[make_pair(a[i][j].x,a[i][j].y)] >= a[i][j].l;
	}
	for(int i = 1;i <= q;i++) cout << (ans[i] ? "YES" : "NO") << endl;
	return 0;
} 
```


---

## 作者：CuteChat (赞：3)


大概就是在一个平面上，有一个动点在原点 $(0,0)$，接下来有一串指令，上下左右移动的指令。接下来会选择一个指令区间 $[l,r]$ 翻转，问操作后能不能到达点 $(x,y)$。

首先要清楚一件事情，如果我们选择了一个区间进行翻转，例如 $[l,r]$，那么在翻转前执行到 $(r,n]$ 时和反转后执行到 $[r+1,n]$ 的位置是不会变的，$[1,l)$ 这一段也不受影响。

简单来说一次翻转不可能会影响到 $[1,l) \bigcup (r,n]$ 的答案。

对于不会影响的，问题就变成了这个点在第 $l$ 操作以后，第 $r$ 次操作以后是否会出现，用 `stl` 乱搞即可，具体怎么乱搞之后再说。

而会影响答案的部分怎么办呢，这就要研究翻转操作序列有什么性质了。

我们考虑，如果翻转后在 $i(l\le i\le r)$ 操作后会经过点 $(x,y)$，那么翻转前会经过哪个点呢，只要我们能找到，这就就无需考虑翻转对答案的影响了。

如果我们记 $Px_i$ 表示第 $i$ 次移动后的 $x$ 坐标，$Py_i$ 表示第 $i$ 次移动后的 $y$ 坐标，再记 $D_{i,j}$ 表示从 $i$ 操作执行到 $j$ 操作的坐标，显然就有 $D_{i,j} = (Px_j - Px_{i-1}, Py_j - Py_{j-1})$，于是原问题就变成了找到一个 $i(l\le i\le r)$，满足 $(Px_{l-1} + D_{{i,r}_x}, Py_{l-1} + D_{{i,r}_y})$ 是我们想要找的点。

然后把 $D_{i,j}$ 式带入这个东西，也就是 $(Px_{l-1} + Px_j - Px_{i-1}, Py_{l-1} + Py_j - Py_{j-1}) = (x,y)$，移项，即 $(Px_i, Py_i) = (Px_{l-1} + Px_{r} - x, Py_{l-1} + Py_{r} - y)$。

所以我们得出结论，如果翻转后在 $i(l\le i\le r)$ 操作后会经过点 $(x,y)$，翻转前就会经过 $(Px_{l-1} + Px_{r} - x, Py_{l-1} + Py_{r} - y)$。

接下来就是说说怎么用 `stl` 乱搞的事情了。

可以事先处理出所有的 $Px$ 和 $Py$，然后把所有相同的点扔进 `set` 或什么东西，然后就可以查询了，查询最小时间戳大于 $l$ 的点，如果这个东西小于 $r$，就说明一定存在。

然后就做完了，时间复杂度 $O(n \log n)$。

# 代码

常数过大，注意使用合理的~~数据结构~~ `stl` 进行维护点集。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

int n, q, px[200005], py[200005]; // px, py 在正文中有定义
char s[200005];
int x, y, l, r;

inline long long pid(int x, int y) { // 获取这个点的编号
	return 1919810ll * x + y; // 因为 y 最远只能到 n，114514 不行，1919810 足够了
}

map<long long, vector<int>> pts; // 记录所有点

bool ok(long long pid, int l, int r) { // 检查这个点在 l,r 操作段（不翻转）有没有出现过
	if (pts.find(pid) == pts.end()) return 0;
	auto val = lower_bound(pts[pid].begin(), pts[pid].end(), l); // 找点
	if (val == pts[pid].end()) return 0;
	else return *val <= r; // 判断
}

int main() {
	scanf("%d%d%s", &n, &q, s + 1);
	pts[pid(0, 0)].push_back(0);
	for (int i = 1; i <= n; ++i) { // 按题意模拟，求出 px, py
		px[i] = px[i - 1], py[i] = py[i - 1];
		if (s[i] == 'L') --px[i];
		else if (s[i] == 'R') ++px[i];
		else if (s[i] == 'D') --py[i];
		else if (s[i] == 'U') ++py[i];
		else assert(0);
		pts[pid(px[i], py[i])].push_back(i); // 加入点集
	}
	while (q--) {
		scanf("%d%d%d%d", &x, &y, &l, &r);
		int nx = px[r] + px[l - 1] - x; 
		int ny = py[r] + py[l - 1] - y;
		// 如果反转后会经过 x,y，翻转前就会经过 nx,ny
		bool res = ok(pid(x, y), 0, l - 1) || ok(pid(nx, ny), l, r - 1) || ok(pid(x, y), r, n);
		if (res) puts("YES");
		else puts("NO");
	}
}
```

---

## 作者：Jerrycyx (赞：2)

前缀和 + 二分。

-----

以样例 $1$ 为例，假设翻转的范围是 $[2,5]$，那么翻转前后的操作序列分别为：

$$
\large
\begin{aligned}
\tt R\textcolor{#5B9DD5}{DLLUU}RU\\
\tt R\textcolor{#FF0000}{UULLD}RU
\end{aligned}
$$

（其中蓝色表示翻转前序列，红色表示翻转后序列。）

上面的操作序列可以转化为下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/87be29ug.png)

观察发现（你也可以自己多测几组例子），翻转一段操作序列实际上就是将这一段操作路径旋转 $180\degree$。因为**查询点在翻转路径上等价于它的翻转点在原路径上**（旋转中心是路径的起点与终点的中点），所以我们无需真的将路径翻转（铁定超时）。

所以我们将每次查询的操作序列（设翻转区间为 $[l,r]$）分为三部分：翻转路径前的正常路径操作序列 $[0,l-1]$，被翻转的路径操作序列 $[l,r]$，翻转路径后的正常路径操作序列 $[r,n]$，查询点在任意一段上面都可以输出 `YES`。（因为翻转前后路径位移总和不变，所以三段路径一定连续）

判断在查询点（或它的翻转点）是否在规定时间段内被路径经过，可以记录每一个点每一次被经过的时刻，设规定时间段为 $[s,t]$，二分查找（可以用 `lower_bound`）第一个大于等于 $s$ 的时间点是否存在且小于等于 $t$，即可判断该点是否在规定时间段内被路径经过。

```cpp
#include<cstdio>
#include<map>
#include<vector>
using namespace std;

const int N=2e5+5;
int n,q; char op[N];
pair<int,int> sum[N];
map<pair<int,int>,vector<int>> vst;

int check(int l,int r,int x,int y)
{
	vector<int> &v=vst[{x,y}];
	auto it=lower_bound(v.begin(),v.end(),l);
	if(it==v.end()) return false;
	else return *it<=r;
}
int main()
{
	scanf("%d%d%s",&n,&q,op+1);
	vst[{0,0}].push_back(0);
	for(int i=1;i<=n;i++)
	{
		sum[i]=sum[i-1];
		if(op[i]=='U') sum[i].second++;
		if(op[i]=='D') sum[i].second--;
		if(op[i]=='L') sum[i].first--;
		if(op[i]=='R') sum[i].first++;
		vst[sum[i]].push_back(i);
	}
	for(int i=1;i<=q;i++)
	{
		int x,y,l,r; scanf("%d%d%d%d",&x,&y,&l,&r);
		int rx=sum[l-1].first+sum[r].first-x;
		int ry=sum[l-1].second+sum[r].second-y;
		if(check(0,l-1,x,y)||check(l,r,rx,ry)||check(r,n,x,y)) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：_RainCappuccino_ (赞：2)

> $\mathtt{TAGS}$：莫队仙人，参上！

不难发现，翻转序列后 $[1, l - 1]$ 和 $[r + 1, n]$ 到的点与原序列一致。

然后 $r \sim l$ 这段操作记 $\Delta x_i, \Delta y_i$ 表示执行了 $r \sim r - i + 1$ 这段操作后的坐标偏移量，显然，可以用后缀和，转化为 $suf_{r - i + 1} - suf_{r + 1}$。

而只需要判断 $[l, r]$ 中存不存在坐标偏移量等于到 $l - 1$ 时的坐标与目标位置的偏移量。

转化一下就为 $suf_{x, i} = suf_{x, r + 1} + \Delta x(l \le i \le r)$ 且 $suf_{y, i} = suf_{y, r + 1} + \Delta y (l \le i \le r)$ 同时成立的 $i$ 存不存在。

所以可以将 $suf_{x, i}$ 和 $suf_{y, i}$ 存在一个 set 中，然后用莫队将操作离线，排序，暴力维护每个查询的 set 即可。

然后答案还可能是 $[1, l -1 ]$ 或 $[r + 1, n]$ 中的，所以双指针维护一下就行。

时间复杂度 $O(n \log n \sqrt{n})$，将 map 换成 unordered_map 可以优化掉一个 $O(\log n)$，注意 unordered_map 不能存 pair，用哈希转化一下，弄成 int 即可，稍微加个快读就能过。

```cpp
#include <bits/stdc++.h>
using namespace std;
#ifdef ONLINE_JUDGE
char buf[1 << 23] , * p1 = buf , * p2 = buf , obuf[1 << 23] , * O = obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
#define endl '\n'
inline int read() {
    int x = 0 , f = 1;char ch = getchar();
    while (!isdigit(ch)) { if (ch == '-') f = -1;ch = getchar(); }
    while (isdigit(ch)) x = x * 10 + (ch ^ 48) , ch = getchar();
    return x * f;
}
#define int long long
const int N = 2e5;
int n , q;
char ch[N + 10];
int dx[N + 10] , dy[N + 10];
int sumx[N + 10] , sumy[N + 10];
int prex[N + 10] , prey[N + 10];
int bel[N + 10];
struct que {
    int x , y , l , r , id;
}a[N + 10];
bool cmp(que x , que y) {
    if (bel[x.l] ^ bel[y.l]) return bel[x.l] < bel[y.l];
    if (bel[x.l] & 1) return x.r < y.r;
    return x.r > y.r;
}
int cntx[N * 3 + 10] , cnty[N * 3 + 10];
unordered_map<int , int> mp;
int v[N + 10];
#define add(id) (mp[v[id]] ++)
#define del(id) (mp[v[id]]--)
int ans[N + 10];
set<pair<int , int> > s;
vector<int> g1[N + 10] , g2[N + 10];

signed main() {
    ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0);
    n = read() , q = read();
    int len = 500;
    for (int i = 1; i <= n; i++) {
        ch[i] = getchar();
        if (ch[i] == 'U') dy[i] = 1;
        else if (ch[i] == 'L') dx[i] = -1;
        else if (ch[i] == 'R') dx[i] = 1;
        else dy[i] = -1;
        bel[i] = (i - 1) / len + 1;
    }
    for (int i = n; i >= 1; i--) sumx[i] = sumx[i + 1] + dx[i] , sumy[i] = sumy[i + 1] + dy[i] , v[i] = sumx[i] * N + sumy[i];
    for (int i = 1; i <= n; i++) prex[i] = prex[i - 1] + dx[i] , prey[i] = prey[i - 1] + dy[i];
    for (int i = 1; i <= q; i++) {
        a[i].x = read() , a[i].y = read() , a[i].l = read() , a[i].r = read();
        g1[a[i].l].push_back(i) , g2[a[i].r].push_back(i);
        a[i].id = i;
    }
    s.insert({ 0, 0 });
    for (int i = 1; i <= n; i++) {
        for (auto id : g1[i]) {
            ans[id] |= s.count({ a[id].x, a[id].y });
        }
        s.insert({ prex[i], prey[i] });
    }
    s.clear();
    for (int i = n; i >= 1; i--) {
        for (auto id : g2[i]) {
            ans[id] |= s.count({ a[id].x, a[id].y });
        }
        s.insert({ prex[i], prey[i] });
    }
    sort(a + 1 , a + 1 + q , cmp);
    int l = 1 , r = 0;
    for (int i = 1; i <= q; i++) {
        int ql = a[i].l , qr = a[i].r , x = a[i].x , y = a[i].y;
        x = x - prex[ql - 1] , y = y - prey[ql - 1];
        while (l < ql) del(l++);
        while (l > ql) add(--l);
        while (r < qr) add(++r);
        while (r > qr) del(r--);
        ans[a[i].id] |= (mp[(x + sumx[qr + 1]) * N + y + sumy[qr + 1]] > 0);
    }
    for (int i = 1; i <= q; i++) {
        if (ans[i]) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}

```

---

## 作者：紊莫 (赞：2)

这是一篇莫队题解。

---

首先，离线询问，对于答案在**非翻转段**内出现的情况，我们可以线性正反扫一遍统计即可。

重点考察答案在 $[l,r]$ 内出现的情况，那么一定是从 $l-1$ 次操作后的坐标开始，每次加上一个变化量，求是否存在要求的 $(x,y)$。

设 $l-1$ 次操作后的坐标为 $(a,b)$，转化一下就是求是否存在变化量为 $(x-a,y-b)$ 的位置。

这个问题比较好解决，我们记录一下后缀变化量为 $(sx_i,sy_i)$，那么实际上就是求 $[l,r]$ 中是否存在后缀变化量为 $(x-a+sx_{r+1},y-b+sy_{r+1})$。

直接对这些询问再次离线使用莫队即可。

行文至此，此题已解。但是，你可能会 TLE on #13。

这里是一些卡常技巧（zyz 不在只能独自卡常悲）：

1. 奇偶优化莫队。
2. 不要反复清空，多开几个数组。
3. 如果必要，使用 ``cc_hash_table`` 代替 ``map``。  
4. 块长在 $500$ 左右为佳。
5. 尝试快读和火车头。

下面给出我的实现，较繁琐，期待你更好的实现。

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
// #define int long long

#define F(i, a, b) for (int i = (a); i <= (b); i++)
#define dF(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
using namespace __gnu_pbds;
inline int rd(){
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9'){
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9'){
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

typedef long long ll;
typedef pair<int, int> Pair;

const int N = 400005, dx[] = {0, 0, -1, 1}, dy[] = {1, -1, 0, 0}, B = 500, A = 2e5;
int n, m, x[N], y[N], _x[N], _y[N], ans[N], sx[N], sy[N];
char s[N];
inline int ty(char c) {
    if(c == 'U') return 0;
    if(c == 'D') return 1;
    if(c == 'L') return 2;
    if(c == 'R') return 3;
}
struct query{
    int id, x, y, l, r;
}q[N], qq[N];
int bl[N];
vector<int> q1[N], q2[N];
cc_hash_table<int, int> mp[N], mm[N];
void solve(){
    n = rd(), m = rd();
    scanf("%s", s + 1);
    F(i, 1, n) {
        int nx = dx[ty(s[i])], ny = dy[ty(s[i])];
        x[i] = x[i - 1] + nx, y[i] = y[i - 1] + ny;
        bl[i] = (i - 1) / B + 1;
    }
    dF(i, n, 1) {
        int nx = -dx[ty(s[i])], ny = -dy[ty(s[i])];
        sx[i] = sx[i + 1] - nx, sy[i] = sy[i + 1] - ny;
    }
    F(i, 1, m) {
        int xx = rd(), yy = rd(), l = rd(), r = rd();
        q[i] = {i, xx, yy, l, r};
        q1[l].push_back(i);
        q2[r].push_back(i);
    }
    mp[A][0] = 1;
    F(i, 1, n) {
        for(auto j:q1[i]) 
            ans[j] |= mp[q[j].x + A][q[j].y] > 0;
        mp[x[i] + A][y[i]] = 1;
    }
    F(i, 1, n) {
        mp[x[i] + A][y[i]] = 0;
    }
    mp[A][0] = 0, mp[x[n] + A][y[n]] = 1;
    dF(i, n - 1, 1) {
        for(auto j:q2[i])
            ans[j] |= mp[q[j].x + A][q[j].y] > 0;
        mp[x[i] + A][y[i]] = 1;
    }
    
    F(i, 1, m) {
        int nx = x[q[i].l - 1], ny = y[q[i].l - 1];
        int a = q[i].x - nx, b = q[i].y - ny;
        qq[i] = {i, a + sx[q[i].r + 1], b + sy[q[i].r + 1], q[i].l, q[i].r};
    }
    sort(qq + 1, qq + m + 1, [](query a, query b){
        if(bl[a.l] ^ bl[b.l]) return a.l < b.l;
        else return (bl[a.l] & 1) ? a.r < b.r : a.r > b.r;
    });
    int l = 1, r = 0;
    F(i, 1, m) {
        int L = qq[i].l, R = qq[i].r;
        while(l > L) --l, mm[sx[l] + A][sy[l]] ++;
        while(r < R) ++r, mm[sx[r] + A][sy[r]] ++;
        while(l < L) mm[sx[l] + A][sy[l]] --, l++;
        while(r > R) mm[sx[r] + A][sy[r]] --, r--;
        ans[qq[i].id] |= mm[qq[i].x + A][qq[i].y] > 0;
    }
    F(i, 1, m) {
        if(ans[i]) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
}
signed main(){
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    // ios_base::sync_with_stdio(0);
    // cin.tie(0), cout.tie(0);
    solve();
    return 0;
}

```

---

## 作者：YBaggio (赞：1)

# 题意
有一个无限的 $2$ 维网格。一开始，机器人站在 $(0, 0)$ 点。机器人可以执行四条指令：

- U：从点 $(x, y)$ 移动到 $(x, y + 1)$ ；
- D：从点 $(x, y)$ 移动到 $(x, y - 1)$ ；
- L：从点 $(x, y)$ 移动到 $(x - 1, y)$ ；
- R：从点 $(x, y)$ 移动到 $(x + 1, y)$ 。

给你一串长度为 $n$ 的命令 $s$ 。您的任务是回答 $q$ **独立的**查询：给定四个整数 $x$ 、 $y$ 、 $l$ 和 $r$ ；判断机器人在执行命令序列 $s$ 时是否访问了点 $(x, y)$ ，但 $l$ 到 $r$ 的子串是相反的（即机器人执行命令的顺序是 $s_1 s_2 s_3 \dots s_{l-1} s_r s_{r-1} s_{r-2} \dots s_l s_{r+1} s_{r+2} \dots s_n$ ）。
# 题解
每次查询，机器人的路径分为三个部分：
1. $[1, l - 1]$；
2. $[l, r - 1]$；
3. $[r, n]$。

我们可以开个 map，记录下每个点分别在第几步之后到达，于是第一三部分就很容易做掉了。

对于第二部分，我们设 $a_i $ 为原操作序列走完 $i$ 步后的位置，设翻转后中第 $k$ 步走完后到达 $(x, y)$（$l \le k < r$），则有 $a_r - a_k$ 为走完 $l - 1$ 步后产生的偏移量（第 $r$ 步走到第 $k$ 步和 $k$ 步走到 $r$ 步产生的总偏移量是相同的），所以 $a_l + a_r - a_k = (x, y)$。移项得到 $a_l + a_r - (x, y) = a_k$，于是我们可以在 map 里找到点 $a_l + a_r - (x, y)$，然后看有无 $k$ 使得第 $k$ 步走完后到达点 $a_l + a_r - (x, y)$ 且满足 $l \le k < r$。

```cpp
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;
int n, q;
pair <int, int> a[200010];
string s;
map <pair <int, int>, vector <int>> p;
bool find (pair <int, int> x, int l, int r) {
  if (p.find (x) == p.end ()) return false;
  auto id = lower_bound (p[x].begin (), p[x].end (), l);
  return (id != p[x].end () && *id <= r);
} //查询 a[l~r]中有无点x 
int main () {
  ios::sync_with_stdio (false);
  cin.tie (0);
  cin >> n >> q;
  cin >> s; s = ' ' + s;
  p[{0, 0}].push_back (0);
  a[0] = {0, 0};
  for (int x = 0, y = 0, i = 1; i <= n; i++) {
    x += (s[i] == 'R') - (s[i] == 'L');
    y += (s[i] == 'U') - (s[i] == 'D');
    a[i] = {x, y};
    p[{x, y}].push_back (i);
  }
  while (q--) {
    int x, y, l, r;
    cin >> x >> y >> l >> r;
    bool flag = false;
    flag |= find ({x, y}, 0, l - 1);
    flag |= find ({x, y}, r, n);
    flag |= find ({a[r].first + a[l - 1].first - x, a[r].second + a[l - 1].second - y}, l, r - 1);
    cout << (flag ? "YES" : "NO") << '\n';
  }
  return 0;
}
```

---

## 作者：Xy_top (赞：1)

分块大法好，万物皆可分块！！！

看了一下好像还没有人发，于是我先来水分块做法。

首先，如果不是在 $[l,r]$ 内到达的询问可以直接预处理。

那么在 $[l,r]$ 内到达的可以怎么做呢？考虑分块，首先倒着循环，使用 ``unordered_map`` 记录形如 ${x,y}$ 的对子，分别表示块内到某个位置 $x$ 的增加量和 $y$ 的增加量。（可能为负）

因为一个块内的增加量的绝对值是 $\sqrt{n}$ 级别的，于是哈希函数可以设置为 $x\times \sqrt{n}+y$，本文取 $x\times 500 + y$。

查询的时候维护当前的点 ${x_0,y_0}$，找块中有没有 ${x-x_0,y-y_0}$，这是 $O(1)$ 的，然后跳到下一个块，块外暴力。

总时间复杂度 $O(n\sqrt{n} + q\sqrt {n})$。

---

## 作者：rainbow_cat (赞：0)

首先我们考虑翻转一段操作后的结果：  
假设机器人现在在 $(1,-2)$，反转的操作为 `RDLLLUURD`，则图像为：
![](https://cdn.luogu.com.cn/upload/image_hosting/g15vbc20.png)   
其中红色为原路线，蓝色为改变后的的路线。   
我们发现新路线是原路线绕开头与结尾的中间点旋转 $180\degree$ 后的图像，知道这个后就很好做了。  
最开始我们使用 `map<pair<int,int>,int>mp` 对每个点进行离散化。再使用 `vector<int>a[200010]` 其中 $a_i$ 存放了第 $i$ 号点出现在第几次操作之后。    
接着我们处理每一次查询，如果 $(x,y)$ 出现在非翻转区间或翻转 $180\degree$ 的 $(nx,ny)$ 出现在翻转区间中则答案为 `YES` 否则为 `NO`。    
这里判断一个点是否出现在一个区间中使用二分。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,x,y,l,r,idx,px[200010],py[200010];
char c;
map<pair<int,int>,int>mp;
vector<int>a[200010];
bool check(int st,int ed,int val)
{
	int pos=lower_bound(a[val].begin(),a[val].end(),st)-a[val].begin();
	if(st<=a[val][pos]&&a[val][pos]<=ed)return 1;
	return 0;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	mp[{0,0}]=++idx;
	a[idx].push_back(0);
	for(int i=1;i<=n;i++)
	{
		cin>>c;
		px[i]=px[i-1],py[i]=py[i-1];
		if(c=='U')py[i]++;
		if(c=='D')py[i]--;
		if(c=='R')px[i]++;
		if(c=='L')px[i]--;
		if(!mp[{px[i],py[i]}])mp[{px[i],py[i]}]=++idx;
		a[mp[{px[i],py[i]}]].push_back(i);
	}
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y>>l>>r;
		int nx=px[l-1]+px[r]-x,ny=py[l-1]+py[r]-y;
		bool flag=0;
		if(mp[{x,y}]&&(check(0,l-1,mp[{x,y}])||check(r,n,mp[{x,y}])))flag=1;
		else if(mp[{nx,ny}]&&check(l,r,mp[{nx,ny}]))flag=1;
		if(flag)cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}

```

---

## 作者：liuhl_weifang (赞：0)

### 题目链接

[link](https://www.luogu.com.cn/problem/CF1902D)

### 解题思路

首先这个点如果在 $l$ 之前或者 $r$ 之后被经过了，那就直接输出 `YES`。否则我们要考虑是否在反转过的区间里出现过。

我们把字符序列做两遍，一遍正着做，一遍倒着做，记录下做完每一步后所处的坐标。

在这里我们使用“坐标平移”，从 $(x_a,y_a)$ 能否走到 $(x_b,y_b)$，坐标平移后相当于从 $(x_c,y_c)$ 能否走到 $((x_b-x_a)+x_c,(y_b-y_a)+y_c)$。

处理询问时也一样，令 $(x_{l-1},y_{l-1})$ 表示**正着做**到 $l-1$ 时所处的坐标，$(x_{r+1},y_{r+1})$ 表示**倒着做**到 $r+1$ 时所处的坐标；从 $(x_{l-1},y_{l-1})$ 执行翻转的 $[l,r]$ 能否到达 $(x_e,y_e)$，相当于从 $(x_{r+1},y_{r+1})$ 继续**倒着做**到 $l$，中间有没有经过 $(x_e-x_{l-1}+x_{r+1},y_e-y_{l-1}+y_{r+1})$。这个东西预处理就好啦！

`Here is the code:`

```cpp
#include <bits/stdc++.h>
#define int long long
#define FAST ios::sync_with_stdio(false);cin.tie(0)
using namespace std;
set<int> prv[200010];//正着做
set<int> suf[200010];//倒着做
map<pair<int,int>,int> mp;
int n,q,idx;
char a[200010];
pair<int,int> p[200010],s[200010];

void solve(){
	cin >> n >> q;
	for (int i=1;i<=n;i++){
		cin >> a[i];
		p[i] = p[i-1];
		if(a[i]=='U') p[i].second++;
		else if(a[i]=='D') p[i].second--;
		else if(a[i]=='L') p[i].first--;
		else p[i].first++;
		if(mp.find(p[i])==mp.end()) mp[p[i]] = ++idx;
		prv[mp[p[i]]].insert(i);
	}
	for (int i=n;i>=1;i--){
		s[i] = s[i+1];
		if(a[i]=='U') s[i].second++;
		else if(a[i]=='D') s[i].second--;
		else if(a[i]=='L') s[i].first--;
		else s[i].first++;
		if(mp.find(s[i])==mp.end()) mp[s[i]] = ++idx;
		suf[mp[s[i]]].insert(i);
	}
	for (int i=1;i<=q;i++){
		int l,r;
		pair<int,int> pos;
		cin >> pos.first >> pos.second >> l >> r;
		if(pos.first==0&&pos.second==0) puts("YES");
		else if(!prv[mp[pos]].empty()&&(*prv[mp[pos]].begin()<l||*prv[mp[pos]].rbegin()>r)) puts("YES");
		else{
			pos.first = pos.first-p[l-1].first+s[r+1].first;
			pos.second = pos.second-p[l-1].second+s[r+1].second;
			if(!suf[mp[pos]].empty()&&*suf[mp[pos]].rbegin()>=l&&*suf[mp[pos]].lower_bound(l)<=r) puts("YES");
			else puts("NO");
		}
	}
	return;
}

signed main()
{
	int t;
	t = 1;
	while(t--) solve();
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

感觉比较有意思的一道题。

考虑不翻转怎么做，记录每一个点是否到达。

记走完 $i$ 步之后的位置是 $a_i$（$a_i$ 是一个二维的结构体）。

那么，翻转 $l,r$ 前后，$a_0,a_1,\dots,a_{l-1},a_r,a_{r+1},\dots,a_n$ 是不变的。

把每一个走到的点用 map 映射成 $x$，然后记录有哪几步走到了 $x$，放到 vector 里。

如果这个 $(x,y)$ 对应的 vector 里有 $i$ 使得 $1\le i<l$ 或者 $i\ge r$，那么显然可行。

下面考虑翻转的部分。

先上图。

![](https://cdn.luogu.com.cn/upload/image_hosting/wrxa6hzu.png)

发现是和 $a_{l-1}$ 和 $a_r$ 的中点中心对称的。

所以我们可以得到 $(x,y)$ 在这一部分对称回去的对称点 $(X,Y)$。

```cpp
X = a[r].x + a[l - 1].x - x;
Y = a[r].y + a[l - 1].y - y;
```

这一个部分需要 $(X,Y)$ 在 $l\sim r-1$ 步走到。（其实 $l\sim r$）是一样的，因为 $a_r=a_r'$。

这里有一个小插曲，我开始还以为是关于连线对称，然后推了好久的式子（~~还错了一次~~），浪费了很多的时间，导致 VP 的时候没有看 F 题。

注意在求有没有小于等于 $l-1$ 或者大于等于 $r$ 的时候，可以直接排序后用第一项和最后一项，查找 $(X,Y)$ 的时候需要二分，不然会 TLE（喜提罚时+1）。

[code](https://codeforces.com/contest/1902/submission/237308849)

---

## 作者：wosile (赞：0)

VP 这场被 Div2.D 卡爆了。这不是最优解，只是纪念一下我的愚蠢思路。

显然这个题目第一眼看起来就很简单，但是这个 *1900 我调了一个小时。

做法非常直接：首先预处理原序列走前 $i$ 步后到了 $(p_i,q_i)$。对于每个询问，先判断是否会在 $[l,r]$ 之外走到 $(x,y)$。

接下来考虑 $[l,r]$ 之内是否会经过 $(x,y)$。

大力上线段树，直接维护每个操作区间的 $(\Delta x, \Delta y)$ 总和和假设起始点为 $(0,0)$，倒序操作这个区间会经过的点。可以在每一个节点上用哈希表维护经过的结点，我用了 `std::set`。

询问的时候，不方便像普通的线段树一样写 `query`（考虑询问位置的变换脑子晕乎乎的），所以我们可以先拆出这个 `query` 在线段树上需要使用的所有 $O(\log n)$ 个区间，再倒着暴力做就行。

时间复杂度取决于实现，$O(n\log n)$ 或 $O(n\log^2n)$。

```cpp
// Problem: D. Robot Queries
// Contest: Codeforces - Educational Codeforces Round 159 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1902/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define eps 1e-8
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
int n,Q;
char op[200005];
set<pair<int,int> >s[800005];
int dx[800005],dy[800005];
map<pair<int,int>,int>mxv,mnv;
namespace IO{
	int read(){
		int x=0,c=getchar(),f=1;
		while(c<'0' || c>'9'){
			if(c=='-')f=-1;
			c=getchar();
		}
		while(c>='0' && c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return f==1?x:-x;
	}
	void write(int x){
		if(x<0){
			putchar('-');
			write(-x);
			return;
		}
		if(x>9)write(x/10);
		putchar(x%10+48);
	}
	void write(int x,char div){
		write(x);
		putchar(div);
	}
	void write(const char *s){
		int pos=0;
		while(s[pos])putchar(s[pos++]);
	}
}
using namespace IO;
void build(int l,int r,int x){
	if(l==r){
		if(op[l]=='R'){
			s[x].insert({1,0});
			dx[x]=1,dy[x]=0;
		}
		if(op[l]=='L'){ 
			s[x].insert({-1,0});
			dx[x]=-1,dy[x]=0;
		}
		if(op[l]=='U'){
			s[x].insert({0,1});
			dx[x]=0,dy[x]=1;
		}
		if(op[l]=='D'){
			s[x].insert({0,-1});
			dx[x]=0,dy[x]=-1;
		}
		return;
	}
	int mid=(l+r)/2;
	build(l,mid,x<<1);
	build(mid+1,r,x<<1|1);
	dx[x]=dx[x<<1]+dx[x<<1|1];
	dy[x]=dy[x<<1]+dy[x<<1|1];
	for(auto p:s[x<<1])s[x].insert({p.first+dx[x<<1|1],p.second+dy[x<<1|1]});
	for(auto p:s[x<<1|1])s[x].insert(p);
}
vector<int>v;
void query(int l,int r,int x,int L,int R){
	if(L<=l && r<=R){
		v.push_back(x);
		//拆询问区间
		return;
	}
	int mid=(l+r)/2;
	if(R>mid)query(mid+1,r,x<<1|1,L,R);
	if(L<=mid)query(l,mid,x<<1,L,R);
}
int px[200005],py[200005];
int main(){
	n=read();
	Q=read();
	scanf("%s",op+1);
	int cx=0,cy=0;
	mnv[{0,0}]=0;
	for(int i=1;i<=n;i++){
		if(op[i]=='R')cx++;
		if(op[i]=='L')cx--;
		if(op[i]=='U')cy++;
		if(op[i]=='D')cy--;
		if(mnv.find({cx,cy})==mnv.end())mnv[{cx,cy}]=i;
		mxv[{cx,cy}]=i;
		px[i]=cx,py[i]=cy;
	}
	build(1,n,1);
	while(Q--){
		int x,y,l,r;
		scanf("%d%d%d%d",&x,&y,&l,&r);
		if((mnv.find({x,y})!=mnv.end() && mnv[{x,y}]<l) || (mxv.find({x,y})!=mxv.end() && mxv[{x,y}]>r)){
			write("YES\n");
			continue;
		}
		v.clear();
		query(1,n,1,l,r);
		cx=px[l-1],cy=py[l-1];
		int fl=0;
		for(int p:v){
			//暴力倒着处理每个节点
			if(s[p].find({x-cx,y-cy})!=s[p].end())fl=1;
			cx+=dx[p];
			cy+=dy[p];
		}
		if(fl)write("YES\n");
		else write("NO\n");
	}
	return 0;
}
//quod erat demonstrandum
```

---

