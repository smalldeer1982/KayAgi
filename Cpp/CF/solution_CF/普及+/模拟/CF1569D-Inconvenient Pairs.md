# Inconvenient Pairs

## 题目描述

There is a city that can be represented as a square grid with corner points in $ (0, 0) $ and $ (10^6, 10^6) $ .

The city has $ n $ vertical and $ m $ horizontal streets that goes across the whole city, i. e. the $ i $ -th vertical streets goes from $ (x_i, 0) $ to $ (x_i, 10^6) $ and the $ j $ -th horizontal street goes from $ (0, y_j) $ to $ (10^6, y_j) $ .

All streets are bidirectional. Borders of the city are streets as well.

There are $ k $ persons staying on the streets: the $ p $ -th person at point $ (x_p, y_p) $ (so either $ x_p $ equal to some $ x_i $ or $ y_p $ equal to some $ y_j $ , or both).

Let's say that a pair of persons form an inconvenient pair if the shortest path from one person to another going only by streets is strictly greater than the Manhattan distance between them.

Calculate the number of inconvenient pairs of persons (pairs $ (x, y) $ and $ (y, x) $ are the same pair).

Let's recall that Manhattan distance between points $ (x_1, y_1) $ and $ (x_2, y_2) $ is $ |x_1 - x_2| + |y_1 - y_2| $ .

## 说明/提示

The second test case is pictured below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1569D/d6f9a0633b655a43f906c574ebac3d9bafe5fd65.png)For example, points $ 3 $ and $ 4 $ form an inconvenient pair, since the shortest path between them (shown red and equal to $ 7 $ ) is greater than its Manhattan distance (equal to $ 5 $ ).

Points $ 3 $ and $ 5 $ also form an inconvenient pair: the shortest path equal to $ 1000001 $ (shown green) is greater than the Manhattan distance equal to $ 999999 $ .

But points $ 5 $ and $ 9 $ don't form an inconvenient pair, since the shortest path (shown purple) is equal to its Manhattan distance.

## 样例 #1

### 输入

```
2
2 2 4
0 1000000
0 1000000
1 0
1000000 1
999999 1000000
0 999999
5 4 9
0 1 2 6 1000000
0 4 8 1000000
4 4
2 5
2 2
6 3
1000000 1
3 8
5 8
8 8
6 8```

### 输出

```
2
5```

# 题解

## 作者：GaryH (赞：4)

# CF1569D 题解
**题意**：给一个平面直角坐标系以及若干条平行于 $x$ 轴或 $y$ 轴的直线，再给出若干个在直线上的点，求出两点间直走直线距离大于曼哈顿距离的点对数。

首先我们可以考虑，将在横线上的点与在竖线上的点分开考虑，因为：

- 若是有一个点既在竖线上又在横线上，那么该点到任意点的距离都是曼哈顿距离；

- 而若是有一个点在横线上，还有另一个点在竖线上，那么这两点间的距离也是曼哈顿距离。

这两个性质都很显然，在此我就把证明省略了。

那么我们就只用考虑全在横线上的点两两间的贡献，以及全在竖线上的点两两间的贡献，而实际上两种是等价的。

不妨先考虑横线的情况。

我们发现，若是某两个横线上的点的纵坐标所在位置对应区间中没有任何一条竖线，那么两点想要互相到达，除去两个点在同一条横线上的情况后，就必须要绕一段弯路，而不能直接走曼哈顿距离到达。

故我们只需要考虑对于每一个点的贡献：

对于一个在横线上的点 $(x,y)$ ，若离其最近的两条竖线的纵坐标分别是 $y_l$ , $y_r$ ,则与该点的距离大于曼哈顿距离的点 $(x',y')$ ，都符合如下要求；

$ x' \neq x , y_l<y'<yr $ .

看到这个类似二位偏序的条件，我们肯定可以用主席树实现，但这样会很麻烦。实际上，我们只需要排了序后先加上所有符合纵坐标限制的点对数量，在从中去除掉不符合横坐标限制的点对数量即可。这样实现的复杂度是 $O(NlogN)$ 的，至于具体实现可以看代码。

**code:**

```

const int N(3e5+10);

typedef pair < int , int > pii ;
 
int n,m,k;
 
int xline[N];
int yline[N];
 
inline void work(){
//只给出了处理单组数据的函数，写的时候需要加上多组数据
	vector < pii > x , y ;
	n=read(),m=read(),k=read();
	int cntx[n+10]={},cnty[m+10]={};
	rep(i,0,n-1)xline[i]=read();
	rep(i,0,m-1)yline[i]=read();
	rep(i,0,k-1){
		int px=read(),py=read();
		bool fx=binary_search(xline,xline+n,px);
		bool fy=binary_search(yline,yline+m,py);
		if(fx&&fy)continue;
		if(fx){
			int pos=lower_bound(yline,yline+m,py)-yline-1;
			cnty[pos]++,x.pb(mp(px,pos));
		}else{
			int pos=lower_bound(xline,xline+n,px)-xline-1;
			cntx[pos]++,y.pb(mp(py,pos));
		}
	} long long res=0;
	rep(i,0,n-1)res+=1ll*(cntx[i]-1)*cntx[i]/2;
	rep(i,0,m-1)res+=1ll*(cnty[i]-1)*cnty[i]/2;
	for(auto p:{x,y}){
		sort(p.begin(),p.end());
		for(int l=0,r;l<(int)(p.size());l=r){
		    for(r=l;r<(int)(p.size())&&p[l]==p[r];r++);
		    res-=1ll*(r-l)*(r-l-1)/2;
		}
		
	} cout<<res<<endl;
}

```

---

## 作者：ran_qwq (赞：2)

和人 duel 到这道题，傻逼题还做三十分钟，退役吧。

两点 $p,q$ 不方便的充要条件是满足以下两条的任一条：

- 假设垂直于 $x$ 轴的线段所在直线将平面划分成 $n+1$ 个部分，则：
  - $p,q$ 不在这些线段上。
  - $p,q$ 在同一区域内。
  - $p,q$ 也不在同一垂直于 $y$ 轴的线段上。
- 假设垂直于 $y$ 轴的线段所在直线将平面划分成 $m+1$ 个部分，则：
  - $p,q$ 不在这些线段上。
  - $p,q$ 在同一区域内。
  - $p,q$ 也不在同一垂直于 $x$ 轴的线段上。

两种情况对称，只考虑第一种。

对于一个区域，假设区域内每条垂直于 $y$ 轴的线段各有 $b_1,b_2,\dots,b_m$ 个点，则答案为

$$\binom{\sum b_i}2-\sum\binom{b_i}2$$

用双指针找一个区域和区域内一条线段的点即可。

```cpp
int n,m,k,x[N],y[N]; pii p[N],q[N]; ll ans;
void QwQ() {
	n=rd(),m=rd(),k=rd(),ans=0;
	for(int i=1;i<=n;i++) x[i]=rd();
	for(int i=1;i<=m;i++) y[i]=rd();
	for(int i=1;i<=k;i++) p[i]=q[i]={rd(),rd()};
	sort(p+1,p+1+k),sort(q+1,q+1+k,[&](pii x,pii y) {return pii{x.sec,x.fir}<pii{y.sec,y.fir};});
	for(int i=2,l=1,r=1;i<=n;i++) {
		while(l<=k&&p[l].fir==x[i-1]) l++;
		r=l; while(r<=k&&p[r].fir<x[i]) r++;
		sort(p+l,p+r,[&](pii x,pii y) {return x.sec<y.sec;});
		for(int j=l,cnt=0;j<=r;j++)
			if(j!=r&&(j==l||p[j].sec==p[j-1].sec)) cnt++;
			else ans-=1ll*cnt*(cnt-1)/2,cnt=1;
		ans+=1ll*(r-l)*(r-l-1)/2,l=r;
	}
	for(int i=2,l=1,r=1;i<=m;i++) {
		while(l<=k&&q[l].sec==y[i-1]) l++;
		r=l; while(r<=k&&q[r].sec<y[i]) r++;
		sort(q+l,q+r,[&](pii x,pii y) {return x.fir<y.fir;});
		for(int j=l,cnt=0;j<=r;j++)
			if(j!=r&&(j==l||q[j].fir==q[j-1].fir)) cnt++;
			else ans-=1ll*cnt*(cnt-1)/2,cnt=1;
		ans+=1ll*(r-l)*(r-l-1)/2,l=r;
	}
	wrll(ans,"\n");
}
```

---

## 作者：TernaryTree (赞：1)

欲远顶针，鉴定为：绕了 C 型弯。

对点分类，无非就三种点：在 $x=k$（竖着的）上的，在 $y=k$（横着的）上的，或者都在的，即交点。

先考虑第三种点，显然它不可能作为“欲远”路径上的一个端点。

一个“欲远”路径的两个端点一定属于同一类点。

并且对于两个同类端点，他们中间不存在不同类型的一条线是横穿在中间的，这样会形成 Z 字型。注意同类型的线是可行的。结合样例图片解释：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1569D/d6f9a0633b655a43f906c574ebac3d9bafe5fd65.png)

图中 $2$ 和 $4$ 是同一类点，都在竖线上，但是中间有一个横线穿过了，所以 $2$ 和 $4$ 不构成欲远路径。

而对于 $3,5$，虽然中间有一条 $4$ 所在的竖线横贯了，但是类型相同，所以就不管了。

容易总结出对于一种类型的点，我们以最上端的线为第一关键字，以自己的当前类型坐标为第二关键字，排序一下，可以分成若干块，每块的每条同类型切下来的线上有 $\{c_i\}$ 个，则这一块答案就是

$$\sum_{i=1}^n\sum_{j=i+1}^n c_ic_j=\dfrac{(\sum\limits_{i=1}^nc_i)^2-\sum\limits_{i=1}^nc_i^2}{2}$$

对于两种欲远路径分开算，每种暴力分块即可。

这个题比较不容易讲清楚，要读者多手玩然后顶针一下，结合代码理解。

你谷博客怎么炸了。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 1e6 + 10;

struct point {
	int x, y, r;
};

int t, n, m, k, ans;
int x[maxn], y[maxn];
map<int, bool> bx, by;
point cx[maxn], cy[maxn];
int dx, dy;

signed main() {
	ios::sync_with_stdio(0);
	cin >> t;
	while (t--) {
		cin >> n >> m >> k;
		bx.clear(), by.clear();
		dx = dy = ans = 0;
		for (int i = 1; i <= n; i++) cin >> x[i], bx[x[i]] = 1;
		for (int i = 1; i <= m; i++) cin >> y[i], by[y[i]] = 1;
		for (int i = 1, x, y; i <= k; i++) {
			cin >> x >> y;
			if (bx.count(x) && by.count(y)) continue;
			if (bx.count(x)) cx[++dx] = {x, y};
			if (by.count(y)) cy[++dy] = {x, y};
		}
		sort(x + 1, x + 1 + n);
		sort(y + 1, y + 1 + m);
		for (int i = 1; i <= dx; i++) cx[i].r = lower_bound(y + 1, y + 1 + m, cx[i].y) - y;
		for (int i = 1; i <= dy; i++) cy[i].r = lower_bound(x + 1, x + 1 + n, cy[i].x) - x;
		sort(cx + 1, cx + 1 + dx, [] (point u, point v) {
			int p = u.r;
			int q = v.r;
			if (p == q) return u.x < v.x;
			else return p < q;
		});
		sort(cy + 1, cy + 1 + dy, [] (point u, point v) {
			int p = u.r;
			int q = v.r;
			if (p == q) return u.y < v.y;
			else return p < q;
		});
		int cur = 1;
		for (int i = 2; i <= m; i++) {
			int s = y[i - 1], e = y[i];
			int last = cur;
			while (cur <= dx && cx[cur].y < e) ++cur;
			int p = last;
			int sum = 0;
			for (int j = last + 1; j < cur; j++) {
				if (cx[j].x != cx[j - 1].x) sum += (j - p) * (j - p), p = j;
			}
			sum += (cur - p) * (cur - p);
			ans += ((last - cur) * (last - cur) - sum) / 2;
		}
		cur = 1;
		for (int i = 2; i <= n; i++) {
			int s = x[i - 1], e = x[i];
			int last = cur;
			while (cur <= dy && cy[cur].x < e) ++cur;
			int p = last;
			int sum = 0;
			for (int j = last + 1; j < cur; j++) {
				if (cy[j].y != cy[j - 1].y) sum += (j - p) * (j - p), p = j;
			}
			sum += (cur - p) * (cur - p);
			ans += ((last - cur) * (last - cur) - sum) / 2;
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：Daidly (赞：1)

赛时调了 1h......

总的来说，这道题是一道结论+模拟题，模拟有点恶心。

先说结论：

若两个点在对边且不在顶点上，即为 an inconvenient pair。

详细的说：

- 若有一点在 $x$ 且 $y$ 上，则不是。

- 若两点都在 $x$ 上，若两个点的上边第一条 $y$ 和下边第一条 $y$ 相同，则是，例如 $(3,4),(4,5),(3,5)$。

- 若两点都在 $y$ 上，若两个点的左边第一条 $x$ 和右边第一条 $x$ 相同，则是，例如 $(6,7),(1,7)$。

但是，有一个小缺陷，例如 $(6,7)$，满足以上条件，但不是，因为它们在同一个 $y$ 上，互相不产生贡献，但是可以对别的 $y$ 上的点产生贡献。

![](https://espresso.codeforces.com/d4825d4e4f7a25b94148de004d8ad84cd243f9cb.png)

那么，开始模拟！

有两种方式：

- 枚举点 $k$。

- 枚举边 $n+m$。

CF 的官方题解似乎是枚举点，但是我选择枚举边，因为枚举边比枚举点快一点点。

先把点分成两部分：

- $x$ 上的。

- $y$ 上的。

既在 $x$ 上也在 $y$ 上的直接扔掉。

接下来对 $x$ 和 $y$ 上的进行处理，只说 $x$ 上的，$y$ 上的差不多。

用一个指针枚举 $x$ 上的点，开个数组记录重复的，统计答案时减去即可。

最后别忘了多测清空。

不懂的可以结合代码理解：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

inline void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int MAXN=2e5+5,MAXK=3e5+5,MAX=1e6+5;
int t,n,m,k,xx,yy,x[MAXN],y[MAXN],numx,numy,ans,tmp,cnt,l;
struct node{
	int x,y;
}px[MAXK],py[MAXK];
bool fx[MAX],fy[MAX];
int gx[MAX],gy[MAX];

bool cmpx(node a,node b){
	if(a.y==b.y)return a.x<b.x;
	return a.y<b.y;
}

bool cmpy(node a,node b){
	if(a.x==b.x)return a.y<b.y;
	return a.x<b.x;
}

signed main(){
	t=read();
	while(t--){
		ans=numx=numy=0;
		for(int i=1;i<=n;++i)fx[x[i]]=0;
		for(int i=1;i<=m;++i)fy[y[i]]=0;
		n=read(),m=read(),k=read();
		for(int i=1;i<=n;++i)x[i]=read(),fx[x[i]]=1;
		for(int i=1;i<=m;++i)y[i]=read(),fy[y[i]]=1;
		for(int i=1;i<=k;++i){
			xx=read(),yy=read();
			if(!fx[xx]||!fy[yy]){
				if(fx[xx])px[++numx].x=xx,px[numx].y=yy;
				else py[++numy].x=xx,py[numy].y=yy;
			}
		}
		//处理在x上的
		sort(px+1,px+numx+1,cmpx);
		//在x上，枚举y进行比较
		l=0;
		for(int i=1;i<=m;++i){
			tmp=l+1,cnt=0;
			while(tmp<=numx&&px[tmp].y<y[i]){
				ans+=(cnt-gx[px[tmp].x]);
				gx[px[tmp].x]++;
				tmp++,cnt++;
			}
			tmp--;
			for(int i=l+1;i<=tmp;++i)gx[px[i].x]=0;
			l=tmp;
		}
		//处理在y上的
		sort(py+1,py+numy+1,cmpy);
		//在y上，枚举x进行比较 
		l=0;
		for(int i=1;i<=n;++i){
			tmp=l+1,cnt=0;
			while(tmp<=numy&&py[tmp].x<x[i]){
				ans+=(cnt-gy[py[tmp].y]);
				gy[py[tmp].y]++;
				tmp++,cnt++;
			}
			tmp--;
			for(int i=l+1;i<=tmp;++i)gy[py[i].y]=0;
			l=tmp;
		}
		print(ans),puts("");
	}
	return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

独一档做法，调了两天，终于过了（这种超大网格题我的做法总是很奇怪）。

前方共 $114514 - 114500$ 个二分。

## 思路

显然，当点 $i$ 和点 $j$ 之间的最短路径是“C”型的时候，距离会大于曼哈顿距离。

我们可以把点分 $3$ 类讨论。

- 平行于 $x$ 轴的道路和平行于 $y$ 轴的道路都经过：显然，这个点无法与其他任何点产生贡献。

- 没有平行于 $x$ 轴的道路经过：显然，这邻近两条 $x$ 轴道路之间且不在自己这条 $y$ 轴的点都可以产生贡献，如第二个样例中的 $4$ 和 $3,5$。

- 没有平行于 $y$ 轴的道路经过：同理。

正难则反，我们可以将所有点减去没有产生贡献的点，剩下的就是可以产生贡献的点。

以第二个样例中的点 $6$ 为例，点 $4$ 有平行于 $y$ 轴的路线经过，邻近的两条平行于 $x$ 轴的路线为第 $3$ 条和第 $4$ 条。

没有贡献的点一种是在左邻近的线左边（这里有点 $2,3$），一种是在右邻近的线右边（这里有点 $4,5,8,9$），还有一种是两条邻近线之间所有在它经过的线上面的点（这里有点 $6,7$），共 $8$ 个点，所以有一个点能与点 $6$ 产生贡献。

显然每一对贡献都会被算两次，所以答案要除以 $2$。

## 实现

显然，没有贡献的点的前两种可以直接大力前缀和计算。

前缀和一种是直接对于每个点进行操作，时间复杂度是 $O(Ts)$，其中 $s$ 是值域，大小是 $10^6$，直接 T 飞了。

另一种是对每一个人进行操作，代码如下：


```cpp
for (int i = 1 ; i <= k ; i++){
	b[i] = a[i];
	c[i] = a[i];
}
sort (b + 1,b + k + 1,cmp1);
sort (c + 1,c + k + 1,cmp2);
int Lst = 0,z1 = 0,z2 = 0;
sum1[0] = t1[0];
for (int i = 1 ; i <= k ; i++){ // x 轴上的前缀和
	if (Lst == b[i].x) continue;
	sum1[b[i].x] = sum1[Lst] + t1[b[i].x];
	lst1[b[i].x] = Lst; // 记录前驱，作用见下
	Lst = b[i].x;
	z1 = b[i].x;
}
Lst = 0;
sum2[0] = t2[0];
for (int i = 1 ; i <= k ; i++){ // y 轴上的前缀和
	if (Lst == c[i].y) continue;
	sum2[c[i].y] = sum2[Lst] + t2[c[i].y];
	lst2[c[i].y] = Lst;
	Lst = c[i].y;
	z2 = c[i].y;
}
```

接下来考虑第三种，显然，一条 $x$ 轴上的两端点之间的点数量可以大力二分。

注意 Corner Case。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 3e5 + 10;
const int M = 1e6 + 10;
const int mod = 1e9 + 7;
const int S = 1e6; 
int T,n,m,k;
int x[N],y[N];
int t1[M],t2[M];
bool vis1[M],vis2[M];
struct node{
	int x,y;
};
node a[N],b[N],c[N];
map <int,int> sum1,sum2,lst1,lst2;
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
int left_bound1 (int L,int R,int x){
	int ret = -1;
	while (L <= R){
		int mid = (L + R) >> 1;
		if (y[mid] < x){
			ret = mid;
			L = mid + 1;
		}else{
			R = mid - 1;
		}
	}
	return ret;
}
int right_bound1 (int L,int R,int x){
	int ret = -1;
	while (L <= R){
		int mid = (L + R) >> 1;
		if (y[mid] > x){
			ret = mid;
			R = mid - 1;
		}else{
			L = mid + 1;
		}
	}
	return ret;
}
int left_bound2 (int L,int R,int xx){
	int ret = -1;
	while (L <= R){
		int mid = (L + R) >> 1;
		if (x[mid] < xx){
			ret = mid;
			L = mid + 1;
		}else{
			R = mid - 1;
		}
	}
	return ret;
}
int right_bound2 (int L,int R,int xx){
	int ret = -1;
	while (L <= R){
		int mid = (L + R) >> 1;
		if (x[mid] > xx){
			ret = mid;
			R = mid - 1;
		}else{
			L = mid + 1;
		}
	}
	return ret;
}
bool cmp1 (node a,node b){
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}
bool cmp2 (node a,node b){
	if (a.y != b.y) return a.y < b.y;
	return a.x < b.x;
}
int get_l (int xx,int ll,int rr){
	int L = 1,R = k;
	int idl,idr,LL,RR;
	while (L <= R){
		int mid = (L + R) >> 1;
		if (b[mid].x < xx){
			L = mid + 1;
		}else{
			idl = mid;
			R = mid - 1;
		}
	}
	L = 1; R = k;
	while (L <= R){
		int mid = (L + R) >> 1;
		if (b[mid].x <= xx){
			L = mid + 1;
			idr = mid;
		}else{
			R = mid - 1;
		}
	}
	L = idl; R = idr;
	while (L <= R){
		int mid = (L + R) >> 1;
		if (b[mid].y < ll){
			L = mid + 1;
		}else{
			LL = mid;
			R = mid - 1;
		}
	} 
	L = idl; R = idr;
	while (L <= R){
		int mid = (L + R) >> 1;
		if (b[mid].y > rr){
			R = mid - 1;
		}else{
			RR = mid;
			L = mid + 1;
		}
	} 
	return (RR - LL + 1);
}
int get_r (int xx,int ll,int rr){
	int L = 1,R = k;
	int idl,idr,LL,RR;
	while (L <= R){
		int mid = (L + R) >> 1;
		if (c[mid].y < xx){
			L = mid + 1;
		}else{
			idl = mid;
			R = mid - 1;
		}
	}
	L = 1; R = k;
	while (L <= R){
		int mid = (L + R) >> 1;
		if (c[mid].y <= xx){
			L = mid + 1;
			idr = mid;
		}else{
			R = mid - 1;
		}
	}
	L = idl; R = idr;
	while (L <= R){
		int mid = (L + R) >> 1;
		if (c[mid].x < ll){
			L = mid + 1;
		}else{
			LL = mid;
			R = mid - 1;
		}
	} 
	L = idl; R = idr;
	while (L <= R){
		int mid = (L + R) >> 1;
		if (c[mid].x > rr){
			R = mid - 1;
		}else{
			RR = mid;
			L = mid + 1;
		}
	} 
	return (RR - LL + 1);
}
int bs1 (int ff){
	int L = 1,R = k,id = 1;
	while (L <= R){
		int mid = (L + R) >> 1;
		if (b[mid].x <= ff){
			L = mid + 1;
			id = mid;
		}else{
			R = mid - 1;
		}
	}
	return b[id].x;
}
int bs2 (int ff){
	int L = 1,R = k,id = 1;
	while (L <= R){
		int mid = (L + R) >> 1;
		if (c[mid].y <= ff){
			L = mid + 1;
			id = mid;
		}else{
			R = mid - 1;
		}
	}
	return c[id].y;
}
void solve(){
	sum1.clear(); sum2.clear();
	lst1.clear(); lst2.clear();
	cin >> n >> m >> k;
	for (int i = 1 ; i <= n ; i++){
		cin >> x[i];
		vis1[x[i]] = 1;
	}
	for (int i = 1 ; i <= m ; i++){
		cin >> y[i];
		vis2[y[i]] = 1;
	}
	for (int i = 1 ; i <= k ; i++){
		cin >> a[i].x >> a[i].y;
		t1[a[i].x]++;
		t2[a[i].y]++;
	}
	for (int i = 1 ; i <= k ; i++){
		b[i] = a[i];
		c[i] = a[i];
	}
	sort (b + 1,b + k + 1,cmp1);
	sort (c + 1,c + k + 1,cmp2);
	int Lst = 0,z1 = 0,z2 = 0;
	sum1[0] = t1[0];
	for (int i = 1 ; i <= k ; i++){
		if (Lst == b[i].x) continue;
		sum1[b[i].x] = sum1[Lst] + t1[b[i].x];
		lst1[b[i].x] = Lst;
		Lst = b[i].x;
		z1 = b[i].x;
	}
	Lst = 0;
	sum2[0] = t2[0];
	for (int i = 1 ; i <= k ; i++){
		if (Lst == c[i].y) continue;
		sum2[c[i].y] = sum2[Lst] + t2[c[i].y];
		lst2[c[i].y] = Lst;
		Lst = c[i].y;
		z2 = c[i].y;
	}
	int ans = 0;
	for (int i = 1 ; i <= k ; i++){
		if (vis1[a[i].x] && vis2[a[i].y]) continue;
		if (vis1[a[i].x]){
			int idl = left_bound1(1,m,a[i].y); // 左邻近
			int idr = right_bound1(1,m,a[i].y); // 右邻近
			int z = 0;
			z += sum2[min(y[idl],bs2(y[idl]))]; // 第一部分
			int bb = bs2(y[idr]); // 因为 y 轴上不一定有人，所以二分找出最近的那个人
			if (bb == y[idr]) bb = lst2[y[idr]]; // 如果相等就继续找前驱
			z += sum2[z2] - sum2[bb];
			z += get_l(a[i].x,y[idl] + 1,y[idr] - 1); // 第三部分
			ans += (k - z); // 计算贡献
		}else{
			int idl = left_bound2(1,n,a[i].x);
			int idr = right_bound2(1,n,a[i].x);
			int z = 0;
			z += sum1[min(x[idl],bs1(x[idl]))];
			int bb = bs1(x[idr]);
			if (bb == x[idr]) bb = lst1[x[idr]];
			z += sum1[z1] - sum1[bb];
			z += get_r(a[i].y,x[idl] + 1,x[idr] - 1);
			ans += (k - z);
		}
	}
	ans /= 2;
	cout << ans << endl;
	for (int i = 1 ; i <= n ; i++) vis1[x[i]] = 0;
	for (int i = 1 ; i <= m ; i++) vis2[y[i]] = 0;
	for (int i = 1 ; i <= k ; i++) t1[a[i].x] = t2[a[i].y] = 0;
}
signed main(){
	close();
	T = 1;
	cin >> T;    
	while (T--) solve();
	return 0;
}
```

---

## 作者：Graphcity (赞：0)

我们发现，如果一条路径需要绕 “C” 型弯，那么它的长度就大于起点与终点的曼哈顿距离。分三种情况考虑：

- 当点在横纵直线的交界处时

显然从这个点到任何点都不需要走 “C” 型弯，路径长度等于曼哈顿距离，所以不能造成任何贡献。

- 当点被夹在 $y=y_1$ 和 $y=y_2\ (y_1<y_2)$ 两条直线之间时

对于纵坐标大于等于 $y_2$ 或者纵坐标小于等于 $y_1$ 的点，也不需要绕 “C” 型弯，而所有需要绕 “C” 型弯的点都被这两条直线夹住，所以这个点的贡献为所有纵坐标大于 $y_1$ 且小于 $y_2$ 的点的个数减一（它自己不能算在贡献之中）。

- 当点被夹在 $x=x_1$ 和 $x=x_2\ (x_1<x_2)$ 两条直线之间时

跟上面一种情况同理，点的贡献为所有横坐标大于 $x_1$ 且小于 $x_2$ 的点的个数减一。

由于一个点必然被一条横向的直线或一条纵向的直线穿过，三个部分的贡献不会重复，直接加起来就可以得到答案。

统计时（这里以第二种情况为例），将每个点的纵坐标从小到大排序，利用 set 维护夹住它的两条直线，再用平衡树统计这两条直线之间的点的个数即可。~~当然你也可以直接用数学方法解决~~

**注意在每组数据做完之后清空 set 和平衡树**。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
#define Fo(i,a,b) for(int i=(a);i<(b);++i)
#define Ro(i,a,b) for(int i=(a);i>(b);--i)
using namespace std;
const int Maxn=3e5;

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(ch>'9' || ch<'0')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int T,n,m,k;
int Xl[Maxn+5],Yl[Maxn+5];
struct Point{int X,Y;} p[Maxn+5];
set<int> st,st2;
inline int cmp1(Point a,Point b) {return a.X<b.X;}
inline int cmp2(Point a,Point b) {return a.Y<b.Y;}

int rt,tot;
struct Node{int l,r,val,key,siz;} t[Maxn+5];
#define ls(x) t[x].l
#define rs(x) t[x].r

inline void Update(int x) {t[x].siz=t[ls(x)].siz+t[rs(x)].siz+1;}
inline int Newnode(int x)
{
	t[++tot]=(Node){0,0,x,rand(),1};
	return tot;
}
inline void Split(int now,int val,int &x,int &y)
{
	if(now==0) {x=y=0; return;}
	if(t[now].val<=val) x=now,Split(rs(now),val,rs(now),y);
	else y=now,Split(ls(now),val,x,ls(now));
	Update(now);
}
inline int Merge(int x,int y)
{
	if(x*y==0) return x+y;
	else if(t[x].key<=t[y].key) {rs(x)=Merge(rs(x),y),Update(x); return x;}
	else {ls(y)=Merge(x,ls(y)),Update(y); return y;}
}
inline void Insert(int x)
{
	int a,b; x=Newnode(x),Split(rt,t[x].val,a,b);
	rt=Merge(Merge(a,x),b);
}

int main()
{
    T=read();
    while(T--)
    {
        ll ans=0;
        n=read(),m=read(),k=read();
        For(i,1,n) Xl[i]=read();
        For(i,1,m) Yl[i]=read();
        For(i,1,k) p[i].X=read(),p[i].Y=read();
        
        For(i,0,tot) t[i]=(Node){0,0,0,0,0};
        st.clear(),st2.clear(),rt=tot=0;
        For(i,1,m) st.insert(Yl[i]),st2.insert(-Yl[i]);
        int pre=k; sort(p+1,p+k+1,cmp1);
        Rof(i,k,1)
        {
            if(p[i].X!=p[i+1].X && i!=k)
            {
                For(j,i+1,pre) Insert(p[j].Y);
                pre=i;
            }
            int low=-(*st2.lower_bound(-p[i].Y))+1,hgh=(*st.lower_bound(p[i].Y))-1;
            if(low>hgh) continue;
            int a,b,c; Split(rt,low-1,a,b),Split(b,hgh,b,c);
            ans=ans+1ll*t[b].siz,rt=Merge(a,Merge(b,c));
        }

        For(i,0,tot) t[i]=(Node){0,0,0,0,0};
        st.clear(),st2.clear(),rt=tot=0;
        For(i,1,n) st.insert(Xl[i]),st2.insert(-Xl[i]);
        pre=k; sort(p+1,p+k+1,cmp2);
        Rof(i,k,1)
        {
            if(p[i].Y!=p[i+1].Y && i!=k)
            {
                For(j,i+1,pre) Insert(p[j].X);
                pre=i;
            }
            int low=-(*st2.lower_bound(-p[i].X))+1,hgh=(*st.lower_bound(p[i].X))-1;
            if(low>hgh) continue;
            int a,b,c; Split(rt,low-1,a,b),Split(b,hgh,b,c);
            ans=ans+1ll*t[b].siz,rt=Merge(a,Merge(b,c));
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

