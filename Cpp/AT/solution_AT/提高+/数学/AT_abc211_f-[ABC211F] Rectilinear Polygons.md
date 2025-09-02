# [ABC211F] Rectilinear Polygons

## 题目描述

## 题目大意

给出平面的 $N$ 个简单多边形，对于每个多边形，其每一条边都平行于 $X$ 轴或 $Y$ 轴，每一个角都为 $90$ 度或 $270$ 度，如图所示。

现在有 $Q$ 次询问，每次给出一个有序整数对 $(X,Y)$ ，求点 $(X+0.5,Y+0.5)$ 被多少个多边形覆盖。

![](https://img.atcoder.jp/ghi/5fccf008dddd93f10ebfc7f13d04a0e0.png)

## 说明/提示

- $1\le N \le 10^5$

- $4\le M_i \le 10^5$
- $\forall M_i,i\isin [1,N],M_i$ 为偶数
- $\sum M_i\le 4\times 10^5$
- $0\le x_{i,j},X_i,y_{i,j},Y_i \le 10^5$
- $1\le Q \le 10^5$
- 对于 $j=1,3,5... M_i-1$ ，都有 $x_{i,j}=x_{i,j+1}$ 
- 对于 $j=2,4,6... M_i$ ，都有 $y_{i,j}=y_{i,j+1}$ （特殊的, $y_{i,M_i}=y_{1,1}$ ）
- 对于任意一个给出多边形，没有重合的顶点。即若 $k \not= j$ ，则 $(x_{i,j},y_{i,j}) \not= (x_{i,k},y_{i,k})$
- 输入的所有数据均为整数。

## 样例 #1

### 输入

```
3
4
1 2 1 4 3 4 3 2
4
2 5 2 3 5 3 5 5
4
5 6 5 5 3 5 3 6
3
1 4
2 3
4 5```

### 输出

```
0
2
1```

## 样例 #2

### 输入

```
2
4
12 3 12 5 0 5 0 3
12
1 1 1 9 10 9 10 0 4 0 4 6 6 6 6 2 8 2 8 7 2 7 2 1
4
2 6
4 4
6 3
1 8```

### 输出

```
0
2
1
1```

# 题解

## 作者：gesong (赞：7)

题目传送门：[[ABC211F] Rectilinear Polygons](https://www.luogu.com.cn/problem/AT_abc211_f)。
# 思路

考虑**扫描线**。

首先将题目中所有的点 $(x,y)$ 变成 $(x+1,y+1)$ 方便处理。

考虑如果只有一个多边形：假设这个多边形每一条竖线的长度为 $[l_i,r_i]$，那么可以将每一条竖线和询问按照 $x$ 轴排序，在竖线交替进入时将 $[l_i,r_{i-1}]$ 进行加一或减一的操作，如下图，其中红线代表加一，蓝线代表减一，可以发现按照多边形的输入顺序从 $x,y$ 双关键字最小的点开始，按顺序（如果到尾，从头开始）将每一个点赋成 $(-1)^{k+1}$，其中 $k$ 表示枚举了的点的个数，这时枚举输入顺序的每两个点，这时这条竖线的权值即为 $y$ 轴小的点负赋的权值，这时查询即为这个点 $y$ 的位置的权值，用一个支持区间加，单点查询的树状数组或线段树即可，至于为什么是 $[l_i,r_{i-1}]$ 请看下文。

考虑有多个多边形：按照一个多边形的方法处理每一个多边形即可。

考虑查询 $(x+0.5,y+0.5)$ 的细节：

由于我们在真实处理时是按照 $(x,y)$ 处理的，因此要考虑一些细节。

1. 排序时应该**先操作在查询**，因为查询的点 $x$ 轴加了 $0.5$，所以这些操作无法影响这个点。
2. 修改的区间为 $[l_i,r_{i-1}]$，因为查询的点 $y$ 轴加了 $0.5$，因此当 $y=r_i$ 时这个区间不能影响到这个点，所以区间为 $[l_i,r_{i-1}]$。

![](https://cdn.luogu.com.cn/upload/image_hosting/w4wr7e9r.png)
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define lowbit(x) x&-x
using namespace std;
const int N=4e5+10;
pii aa[N];
int anss[N],c[N],w[N];
inline void add(int i,int x){
	for (;i<N;i+=lowbit(i)) c[i]+=x;
}
inline int get(int i){
	int ans=0;
	for (;i;i-=lowbit(i)) ans+=c[i];
	return ans;
}
inline void change(int l,int r,int x){
	if (l>r) return ;
	add(l,x),add(r+1,-x);
}
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
struct nord{
	int op,x,y1,y2,w;
	bool operator <(const nord &xx){
		if (x==xx.x) return op<xx.op;
		return x<xx.x;
	}
}a[N]; 
main(){
	int n=read();
	int cnt=0;
	for (int T=1;T<=n;T++){
		int m=read();
		for (int i=1;i<=m;i++) aa[i]=aa[i+m]={read()+1,read()+1};
		pii ans={1e18,1e18};
		int k;
		for (int i=1;i<=m;i++)
			if (aa[i]<ans) ans=aa[i],k=i;
		int wl=1;
		for (int i=k;i<=k+m-1;i++) w[i>m?i-m:i]=wl,wl=-wl;
		for (int i=1;i<=m;i+=2)
			a[++cnt]={0,aa[i].first,aa[i].second,aa[i+1].second,aa[i].second<aa[i+1].second?w[i]:w[i+1]};
	}
	for (int i=1;i<=cnt;i++)
		if (a[i].y1>a[i].y2) swap(a[i].y1,a[i].y2);
	int q=read();
	for (int i=1;i<=q;i++){
		int x=read()+1,y=read()+1;
		a[++cnt]={1,x,y,i,0};
	}
	sort(a+1,a+cnt+1);
	for (int i=1;i<=cnt;i++)
		if (a[i].op) anss[a[i].y2]=get(a[i].y1);
		else change(a[i].y1,a[i].y2-1,a[i].w);
	for (int i=1;i<=q;i++) printf("%lld\n",anss[i]);
    return 0;
}
// NOIP 2024 RP++
// NOIP 2024 RP++
// NOIP 2024 RP++
// NOIP 2024 RP++
// NOIP 2024 RP++
```

---

## 作者：xiaoPanda (赞：3)

## ABC211F - Rectilinear Polygons(*2350)
### Problem
在平面内有 $n$ 个简单的多边形，每条边平行 $x$ 轴或 $y$ 轴，按顺序给出每个点的坐标，多边形可以互相重叠，给出 $q$ 个询问，每个询问求点 $(x+0.5,y+0.5)$ 在几个多边形内。

### Solution 
先只看平行于 $y$ 轴的直线，那么题目就可以转化为在 $1$ 到 $max$ 内，每次都有一些区间内点被打上标记，问第 $x$ 个点被打了多少标记。

那么直接用树状数组维护即可。

但有一些区域虽然左右两边都有多边形的边，但在多边形外边，因此还需要处理一下边是否在多边形内（如下图）。

![image](https://img2022.cnblogs.com/blog/2306782/202207/2306782-20220707214307228-1921307916.png)

在上图中，如果只看直线 $x=1,x=2,x=4,x=6$，区间 $1,2,3$ 都位于两条边之间，但区间 $2$ 不在大多边形内。

观察可以发现，从左到右靠近 $y$ 轴的边分成的区间内，第 $2i$ 个区间不在该多边形内，第 $2i+1$ 个区间在该多边形内。

题目中说每条边都是按顺序读入的，所以只要找到最靠近 $y$ 轴的边，它和它读入的下一条边组成的区间即为第 $1$ 个区间，它读入的下一条边和它读入的后两条边组成的区间即为第 $2$ 个区间······以此类推。

那么在树状数组中要打标记的区间就求出来了。

然后对于同一列的询问一起给出答案，注意从左到右，因为之前的标记仍有影响。

举个例子（还是上图，只看大多边形）：

当第一列时，当前状态：`0 1 1 1 1 1 1 1 1 0 0 0...`（注意此时第 $i$ 个数指第 $i$ 行的标记，$i$ 从 $0$ 开始）此时相当于区间 $[1,8]$ （注意到第 $9$ 个点即 $(1.5,9.5)$ 不属于多边形内）加 $1$，树状数组实现时要把区间加转化为单点加，用差分解决，即第 $1$ 个点加 $1$，第 $8+1=9$ 个点减 $1$。

当第二列时，当前状态：`0 0 0 0 0 0 0 1 1 0 0 0...`此时相当于区间 $[1,6]$ （注意区间 $[0,6]$ 不属于多边形内，这是第偶数条平行 $y$ 轴的边）减 $1$，即第 $1$ 个点减 $1$，第 $6+1=7$ 个点加 $1$。

查询时把单点查询转化成区间查询，例如点 $(2,7)$ ，就相当于在第二列时查询区间 $[0,7]$ 的和，为 $1$ ，所以点 $(2.5,7.5)$ 在 $1$ 个多边形内。

还有一点点细节，树状数组下标必须不为 $0$ ，所以读入时对于所有的坐标直接加 $1$ 就可以了（当然上面的题解没有）。

其他的细节具体见代码。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define int long long
#define mp make_pair
#define pb push_back
#define lowbit(x) x&-x
const int N=1e5+7;
int n,q,k;
int bit[N],ans[N];
pair<int,int>a[N];
vector<pair<int,int> >cor[N],qu[N];
void update(int x,int k) 
{
	for(int i=x;i<N;i+=lowbit(i)) 
	bit[i]+=k;
}
int query(int x) 
{ 
	int tot=0;
	for(int i=x;i;i-=lowbit(i))
	tot+=bit[i];
	return tot;
}//树状数组基本操作
main() 
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) 
	{
		scanf("%lld",&k);
		int mn=0; 
		for(int j=0;j<k;j++) 
		{
			int x,y; 
			scanf("%lld%lld",&x,&y);x++,y++;
			a[j]=mp(x,y);
			if(a[j]<a[mn])mn=j;//找到离y轴最近的线段（的一个端点）
		}
        int now=1;
        for(int j=0;j<k;j++) 
		{
			int w=mn+j;//从左至右依次把这些区间分成在多边形内和不在多边形内
        	cor[a[w%k].ft].pb(mp(a[w%k].sd,now));//如果在那么当前点的标记为1，否则为-1
        	now=-now; 
		}
	}
	scanf("%lld",&q);
	for(int i=1;i<=q;i++)
	{
		int x,y; 
		scanf("%lld%lld",&x,&y);x++,y++;
	    qu[x].pb(mp(y,i));
	}
	for(int i=1;i<N;i++) {//从左至右依次求出答案
		for(auto it:cor[i]) {
			int x=it.ft,y=it.sd;
			update(x,y);//注意应该先修改在查询
		} 
		for(auto it:qu[i]) {
			int x=it.ft,y=it.sd;
			ans[y]=query(x);//记录答案
		}
	}
	for(int i=1;i<=q;i++) 
	printf("%lld\n",ans[i]); 
	return 0;
}
```

---

## 作者：2020luke (赞：2)

# [[ABC211F] Rectilinear Polygons](https://www.luogu.com.cn/problem/AT_abc211_f) 题解

思路什么的上一篇题解已经写的非常明白了，这里只是提供一个补充 & 另一个实现的方法。

## 思路解析

先说结论：扫描线。顾名思义，扫描线的本质就是用一条线沿着 $x$ 或 $y$ 轴扫过去，每碰到一条边就记录一下加边后是面积是增加还是减少，然后用树状数组或线段树统计。由于我们并不需要知道整张图所有的位置的值，我们就只需要求出来扫描线所在的那一行 or 列每一个点的值即可。

这里就不过多解释，如果没有学过扫描线建议去做一下[模板题](https://www.luogu.com.cn/problem/P5490)，推荐看第一篇题解。

接下来就是本题的重点，该如何把不规则图形存下来。如下图，我们先把图上的竖边找出来，同时给点的顺序标一个号。

![](https://cdn.luogu.com.cn/upload/image_hosting/eik8r2g3.png)

可见四条边中左边三条的权值都是增加的，只有右边一条是减少的。我们寻找边上的两点和权值的关系，可以发现，由于是点顺序输入的，所以每一条正边权的边的两点中编号较小的点 $y$ 值也是更小的，而每一条边的两点中编号较小的点的编号一定是奇数。因此我们可以给每一条边都判断两点编号的大小来决定是用正边权还是负边权。

## 实现

我们根据以上所说的方式存好每一条边，然后将边按 $x$ 的值排序，满足扫描线的性质。对于询问我们将询问离线下来，同样按 $x$ 排序，这样我们在进行加边之前判断当前扫描线是否已经处理了所有 $x$ 小于当前询问的 $x$ 的边，若已经处理完就更新答案。

接下来有几点注意事项。

- 题目中的输入点的顺序不一定满足我们想要的输入顺序，所以我们需要自己找到一个在 $x$ 最小的情况下 $y$ 也最小的点做编号为 $1$ 的点。
- 由于我们只需要知道一个点被覆盖的次数，所以可以将模板中的线段树换成树状数组区修单查。
- 由于我们需要先把当前 $x$ 轴上的边加完再统计询问，所以我们要在所有边的最后加上一个 $x=\inf,val=0$ 的边，这样就能防止最后有几个点没有处理到。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = 1e5;
int n, m, xx[N], yy[N], tv[N], q, c[N], ans[N];
struct side {
	int x, ya, yb, val;
};
struct point {
	int x, ya, yb; 
};
struct query {
	int x, y, p;
};
void add(int x, int y) {
	for(; x <= M; x += (x & -x)) {
		c[x] += y;
	}
}
int ask(int x) {
	int sum = 0;
	for(; x > 0; x -= (x & -x)) {
		sum += c[x];
	}
	return sum;
}
int main() {
	cin >> n;
	vector<side> v;
	for(int i = 1; i <= n; i++) {
		cin >> m;
		for(int i = 0; i < m; i++) {
			cin >> xx[i] >> yy[i];
			xx[i]++; yy[i]++;
		}
		int p = 0;
		for(int i = 0; i < m; i++) {
			if(xx[i] == xx[p] && yy[i] < yy[p]) p = i;	//找到起始点，注意 y 轴也要判
			else if(xx[i] < xx[p]) p = i;
		}
		int val = 1;
		for(int i = 0; i < m; i++) {
			int w = (i + p) % m;
			tv[w] = val;	//给点加权
			val = -val;
		}
		for(int i = 0; i < m; i += 2) {	//判断
			if(yy[i] < yy[i + 1]) v.push_back({xx[i], yy[i], yy[i + 1], tv[i]});
			else v.push_back({xx[i], yy[i + 1], yy[i], tv[i + 1]});
		}
	}
	sort(v.begin(), v.end(), [](side x, side y) {	//按 x 排序
		if(x.x != y.x) return x.x < y.x;
		else return x.ya < y.ya;
	});
	v.push_back({M + 1, 1, 1, 0});	//避免结尾有点没判
	vector<query> que;
	cin >> q;
	for(int i = 1; i <= q; i++) {
		cin >> xx[i] >> yy[i];
		xx[i]++; yy[i]++;
		que.push_back({xx[i], yy[i], i});	//离线
	}
	sort(que.begin(), que.end(), [](query x, query y) {	//排序
		if(x.x != y.x) return x.x < y.x;
		else return x.y < y.y;
	});
	int pos = 0;
	for(auto it : v) {
		int x = it.x, ya = it.ya, yb = it.yb, val = it.val;
		for(; que[pos].x < x && pos < (int)que.size(); pos++) {
			ans[que[pos].p] = ask(que[pos].y);	//若已经操作完则更新
		}
		add(ya, val); add(yb, -val);	//加权
	}
	for(int i = 1; i <= q; i++) cout << ans[i] << '\n';
	return 0;
}
```

---

## 作者：mojoege (赞：1)

## 分析
扫描线？下面的操作都可以自己模拟一下，好理解。

先将问题简化一下，判断这个点在多少个矩形之内？这样只需要给每一条竖着的边打上一个标记，用树状数组维护一下就好。

这种不规则的也差不多，难就难在如何给每个点打上标记 和 如何维护纵坐标。这里用到一个很巧妙的标记技巧，用 $1$ 和 $-1$ 轮流标记这些点，再加上题目给的按**一横一竖**的方式输入这些边，这样就能做到分辨后面的点属于图形内……吗？不对，如果图形是下面这种，然后第一次标记的点是 $(2,1)$，模拟一下发现 $x=1$ 到 $x=2$ 之间的点是不在图形内的，而 $x=2$ 右边的点是在图形内的，显然是不对的。考虑第一次标记最左边的边，这样似乎就避免了这个问题。

![img](https://img.atcoder.jp/ghi/1c97f791a2aadcf5637b1f10736fb820.png)

为什么能避免？那还得说如何标记一条边。善良的题面又给我们了**点是按顺序输入的**，那么我们可以规定一条竖着的边是由**横坐标、下面的点的纵坐标、上面的点的纵坐标和往后是不是在图形内**，最后这个标记我们统一使用这条边下面那个点的标记，因为是轮流标记加上有顺序而且它还得是一个**封闭图形**，所以必定是一条边标记为 $1$，与之相邻的边标记为 $-1$。

然后 sort 一下，把所有边从左到右排一遍，处理查询的时候也是从左到右排一遍，这样方便我们使用**双指针**。这里按照上面矩形的思路，构造一个树状数组，存的是什么呢？肯定是纵坐标上的值。很好理解，存横坐标没有意义（直接前缀和）而纵坐标上每条边到哪里我们又不知道，所以存纵坐标。细节上，双指针很好实现，对于每一条边我们都要挪动查询的点的横坐标，挪到最后一个在这条边左边的点，记录答案。

对于查询答案，直接看当前节点纵坐标的值加起来。那更新呢？我们有个朴素的想法，开两维，第一维对应一个横坐标。这样肯定是不行的，再看回前面竖着的边的性质——一个为正一个为负，那就可以直接在纵坐标上加上这条边的标记（相当于前缀和），而这个标记肯定会在下一条边的时候清理掉不在矩形内的部分，而没清理掉的会继续前缀和往后走。

代码细节，在处理坐标的时候可以集体加一，把 $(0,0)$ 挪到 $(1,1)$ 上；询问要离线处理，记得打上 $id$。 

## 代码
```cpp
#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

int n, m, q;
int xx[100005], yy[100005], w[100005], ans[100005], c[100005];
struct side{
    int x, ya, yb, val;
};
struct que{
    int x, y, id;
};
vector<side> v;
vector<que> v1;

bool cmp(side x, side y){
    if (x.x == y.x) return x.ya < y.ya;
    return x.x < y.x;
}

bool cmp1(que x, que y){
    if (x.x == y.x) return x.y < y.y;
    else return x.x < y.x;
}

int lowbit(int x){
    return x & -x;
}

void update(int x, int k){
    while (x <= 1e5) c[x] += k, x += lowbit(x);
}

int query(int x){
    int res = 0;
    while (x) res += c[x], x -= lowbit(x);
    return res;
}

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> m;
        int minx = 0;
        for (int j = 0; j < m; j++){
            cin >> xx[j] >> yy[j];
            xx[j]++, yy[j]++;//好操作，往后往上挪一个
            if (make_pair(xx[j], yy[j]) < make_pair(xx[minx], yy[minx])) minx = j;//最左边就保证了这条边往右一定在图形内
        }
        int val = 1;
        for (int j = 0; j < m; j++){
            int tmp = (j + minx) % m;//要保证取轮流标，不然相邻两条边的性质就没了
            w[tmp] = val, val = -val;//轮流标记是正还是负
        }
        for (int j = 0; j < m; j += 2){
            if (yy[j] < yy[j + 1]) v.push_back((side){xx[j], yy[j], yy[j + 1], w[j]});
            else v.push_back((side){xx[j], yy[j + 1], yy[j], w[j + 1]});//push下面那个点的标记
        }
    }
    sort(v.begin(), v.end(), cmp);
    v.push_back((side){(int)1e5 + 1, 1, 1, 0});
    cin >> q;
    for (int i = 1; i <= q; i++){
        cin >> xx[i] >> yy[i];
        xx[i]++, yy[i]++;
        v1.push_back((que){xx[i], yy[i], i});//离线操作，记录下id
    }
    sort(v1.begin(), v1.end(), cmp1);
    int pos = 0;
    for (int i = 0; i < v.size(); i++){
        int x = v[i].x, ya = v[i].ya, yb = v[i].yb, val = v[i].val;
        for (; v1[pos].x < x && pos < v1.size(); pos++) ans[v1[pos].id] = query(v1[pos].y);//直接查询
        update(ya, val), update(yb, -val);//直接在纵坐标上更新，相邻两个点标记相反
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << endl;
    return 0;
}
```

---

## 作者：majoego (赞：0)

这一看，哎呀，不是扫描线板子吗！！

显然就是，但是我们不用写臭长的线段树，只需要写树状数组即可。

难点在于这一道题它的每一个形状都不一定是一个四边形，所以比较麻烦，我们需要对这个图形的每一个顶点打标记（差分）即可。

我们可以找到最接近 $y$ 轴的那个点开始，然后逐渐往后遍历每一个点，这必定是一个是 $1$ 一个是 $-1$ 这样间隔排序的，所以开一个 $tmp$ 记录他是 $1$ 还是 $-1$。

我们可以记录下每一个 $x$ 坐标下 $y$ 有多少个点，将它放到一个 vector 里。我们将问题离线下来，对于每一个 $x$ 都对应一起处理，对于他们的 $y$ 直接用树状数组维护即可，~~如果你想用 Seg 也可以~~。

最后我们再把答案依次输出即可。

[link](https://atcoder.jp/contests/abc211/submissions/51904783)。

---

