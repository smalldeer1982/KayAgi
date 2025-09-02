# Recover Polygon (hard)

## 题目描述

僵尸们发现了僵尸感染程度检测器，并设法破坏了它！现在，检测它们主巢穴的形状对 Heidi 来说将是一个真正的挑战。和以前一样，巢穴可以用网格上的严格凸多边形来表示。多边形的每个顶点都占据网格上的一个点。然而，受损的僵尸感染程度检查器只能判断每个单元格的僵尸感染程度是否在以下集合中：$\{1,2,3\}$。换句话说，Heidi 知道所有位置僵尸感染程度不为 $0$ 和 $4$。

有了这些信息，Heidi 还想知道巢穴的准确形状，以便对僵尸带来的下一场浩劫。请帮帮她吧！

## 样例 #1

### 输入

```
8 19
2 3 2 4 2 5 3 3 3 5 4 3 4 5 4 6 5 2 5 3 5 6 6 2 6 3 6 4 6 5 6 6 6 7 7 6 7 7
5 8
2 2 2 3 2 4 3 2 3 4 4 2 4 3 4 4
0 0
```

### 输出

```
4
2 3
2 4
6 6
5 2
4
2 2
2 3
3 3
3 2
```

# 题解

## 作者：zesqwq (赞：1)

感谢 [__Seniorious__](https://www.luogu.com.cn/user/333119) 提供的帮助。

要求凸包？就求凸包！

我们发现，当一个点四周都不是 $0$ 时，这个点就在凸包内部，反之没有。

我们还发现，如果一个点四周的方格都是 $4$ 时，这个点就一定不在凸包边上。

如何判断一个格子是否 $>0$？题目给定的格子一定包含凸包的上下边界，看一个点是否在上边界之下，下边界之上即可。

把这些点提取出来，个数是 $O(m)$ 的，求一次凸包即可，复杂度 $O(m \log m)$。

```cpp
const int N = 1e5 + 10;
int n, m;
vector<pair<int, int> > now, used;
int st[N], top;
bool vis[N];
vector<int> t[N];
inline int query(int x, int y) {
    if (!t[x].size()) return 0;
    if (!vis[x]) st[++top] = x, sort(t[x].begin(), t[x].end()), vis[x] = 1;
    return y >= t[x][0] && y <= t[x].back();
}
inline void work() {
    Poly c;
    top = 0;
    clear(used), clear(now);
    for (int i = 1, x, y; i <= m; i++) {
        read(x, y), used.emplace_back(x, y);
        now.emplace_back(x, y), t[x].push_back(y);
        if (x > 1) now.emplace_back(x - 1, y);
        if (y > 1) now.emplace_back(x, y - 1);
        if (x > 1 && y > 1) now.emplace_back(x - 1, y - 1); 
    }
    sort(now.begin(), now.end()), now.erase(unique(now.begin(), now.end()), now.end());
    for (auto [x, y] : now) if (x < n && y < n) {
        if (query(x, y) && query(x + 1, y) && query(x, y + 1) && query(x + 1, y + 1)) c.push_back({x, y});
    }
    c = convexhull(c);
    println(c.size());
    int st = 0;
    for (int i = 0; i < c.size(); i++)
        if (c[i].x < c[st].x)
            st = i;
        else if (c[i].x == c[st].x && c[i].y < c[st].y)
            st = i;
    for (int i = st; i < c.size(); i++) println(c[i].x, c[i].y);
    for (int i = 0; i < st; i++) println(c[i].x, c[i].y);
    for (auto [a, b] : used) clear(t[a]);
    while (top) vis[::st[top--]] = 0;
}
int main() {
    while (read(n, m), n) work();
    return 0;
}
```

---

## 作者：wosile (赞：0)

和人 duel 到这道题，第一眼看题以为是直接求凸包，然后发现需要看 B1/B2 的背景。其实还是求凸包啊。

记输入的格子集合为 $B$。

发现我们几乎没法直接确定哪些点是顶点，所以考虑求出一个点集 $S$，使得所有多边形的顶点都在 $S$ 中，并且 $S$ 中的所有点都在多边形上或多边形内。

只需要把输入的每个格子的最靠内的点加入 $S$ 即可。但是怎么判断哪个顶点最靠内呢？

首先，判断一个格子 $(x,y)$ 是 $4$ 还是 $0$ 很简单，我们可以对于 $x_0$ 记录 $B$ 中所有的 $x=x_0$ 的点的 $\max y$ 和 $\min y$。如果 $\min y <y < \max y$，那么这个格子的值就是 $4$。

如果一个格子 $(x,y)\in B$，它相邻的四个格子中有两个在 $B$ 中，另两个的值为 $0$，并且相邻的两个在 $B$ 中的格子有一个公共顶点，我们就把这个公共顶点加入 $S$。显然这个公共顶点一定在多边形内部，进一步观察后容易证明，多边形的每个顶点一定都可以表示成这样的一个公共顶点。

求 $S$ 的凸包即可。注意输出顺序。

时间复杂度 $O((n+m)\log m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
set<pair<int,int>>s; 
vector<int>v[100005];
int x[200005],y[200005];
int get(int tx,int ty){
	if(v[tx].empty())return 0;
	if(s.find({tx,ty})!=s.end())return 1;
	if(ty<v[tx][0] || ty>v[tx][v[tx].size()-1])return 0;
	return 2;
}
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
pair<int,int>p[200005];
int mx,my;
typedef long long ll;
bool cmp(pair<int,int>a,pair<int,int>b){
	ll tmp=1LL*(a.first-mx)*(b.second-my)-1LL*(b.first-mx)*(a.second-my);
	if(tmp!=0)return tmp>0;
	return a.first<b.first;
}
int st[200005];
bool check(int a,int b,int c){
	return 1LL*(p[c].second-p[b].second)*(p[b].first-p[a].first)<=1LL*(p[b].second-p[a].second)*(p[c].first-p[b].first);
}
int main(){
	while(true){
		int n,m;
		scanf("%d%d",&n,&m);
		if(n==0 && m==0)break;
		
		for(int i=1;i<=m;i++)scanf("%d%d",&x[i],&y[i]);
		for(int i=1;i<=n;i++)v[i].clear();
		for(int i=1;i<=m;i++)v[x[i]].push_back(y[i]);
		for(int i=1;i<=n;i++)sort(v[i].begin(),v[i].end());
		s.clear();
		for(int i=1;i<=m;i++)s.insert({x[i],y[i]});
		int cnt=0;
		for(int i=1;i<=m;i++){
			int cnt0=0,cnt1=0;
			int qx=0,qy=0;
			for(int d=0;d<4;d++){
				int tmp=get(x[i]+dx[d],y[i]+dy[d]);
				if(tmp==0)cnt0++;
				if(tmp==1){
					cnt1++;
					if(d==0)qx--;
					if(d==2)qy--;
				}
			}
			if(cnt0==2 && cnt1==2)p[++cnt]={x[i]+qx,y[i]+qy};
		}
		// 以上是找备选点
		// 以下是求凸包 
		sort(p+1,p+cnt+1);
		cnt=unique(p+1,p+cnt+1)-1-p;
		mx=p[1].first,my=p[1].second;
		sort(p+2,p+cnt+1,cmp);
		int top=0;
		for(int i=1;i<=cnt;i++){
			while(top>1 && check(st[top-1],st[top],i))top--;
			st[++top]=i;
		}
		int bid=1;
		for(int i=1;i<=top;i++)if(p[st[i]]<p[st[bid]])bid=i;
		printf("%d\n",top);
		int qwq=top;
		while(qwq--){
			printf("%d %d\n",p[st[bid]].first,p[st[bid]].second);
			if(bid==1)bid=top;
			else bid--;
		}
	}
	return 0;
	//quod erat demonstrandum
}
```

---

