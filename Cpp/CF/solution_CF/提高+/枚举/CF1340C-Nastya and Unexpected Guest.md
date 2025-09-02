# Nastya and Unexpected Guest

## 题目描述

If the girl doesn't go to Denis, then Denis will go to the girl. Using this rule, the young man left home, bought flowers and went to Nastya.

On the way from Denis's house to the girl's house is a road of $ n $ lines. This road can't be always crossed in one green light. Foreseeing this, the good mayor decided to place safety islands in some parts of the road. Each safety island is located after a line, as well as at the beginning and at the end of the road. Pedestrians can relax on them, gain strength and wait for a green light.

Denis came to the edge of the road exactly at the moment when the green light turned on. The boy knows that the traffic light first lights up $ g $ seconds green, and then $ r $ seconds red, then again $ g $ seconds green and so on.

Formally, the road can be represented as a segment $ [0, n] $ . Initially, Denis is at point $ 0 $ . His task is to get to point $ n $ in the shortest possible time.

He knows many different integers $ d_1, d_2, \ldots, d_m $ , where $ 0 \leq d_i \leq n $ — are the coordinates of points, in which the safety islands are located. Only at one of these points, the boy can be at a time when the red light is on.

Unfortunately, Denis isn't always able to control himself because of the excitement, so some restrictions are imposed:

- He must always move while the green light is on because it's difficult to stand when so beautiful girl is waiting for you. Denis can change his position by $ \pm 1 $ in $ 1 $ second. While doing so, he must always stay inside the segment $ [0, n] $ .
- He can change his direction only on the safety islands (because it is safe). This means that if in the previous second the boy changed his position by $ +1 $ and he walked on a safety island, then he can change his position by $ \pm 1 $ . Otherwise, he can change his position only by $ +1 $ . Similarly, if in the previous second he changed his position by $ -1 $ , on a safety island he can change position by $ \pm         1 $ , and at any other point by $ -1 $ .
- At the moment when the red light is on, the boy must be on one of the safety islands. He can continue moving in any direction when the green light is on.

Denis has crossed the road as soon as his coordinate becomes equal to $ n $ .

This task was not so simple, because it's possible that it is impossible to cross the road. Since Denis has all thoughts about his love, he couldn't solve this problem and asked us to help him. Find the minimal possible time for which he can cross the road according to these rules, or find that it is impossible to do.

## 说明/提示

In the first test, the optimal route is:

- for the first green light, go to $ 7 $ and return to $ 3 $ . In this case, we will change the direction of movement at the point $ 7 $ , which is allowed, since there is a safety island at this point. In the end, we will be at the point of $ 3 $ , where there is also a safety island. The next $ 11 $ seconds we have to wait for the red light.
- for the second green light reaches $ 14 $ . Wait for the red light again.
- for $ 1 $ second go to $ 15 $ . As a result, Denis is at the end of the road.

In total, $ 45 $ seconds are obtained.

In the second test, it is impossible to cross the road according to all the rules.

## 样例 #1

### 输入

```
15 5
0 3 7 14 15
11 11```

### 输出

```
45```

## 样例 #2

### 输入

```
13 4
0 3 7 13
9 9```

### 输出

```
-1```

# 题解

## 作者：Marser (赞：9)

考场上切完这题一发上M，我还是太菜了。  
出来发现Unrated了，心态爆炸。
### 题意
给定数轴上的 $m$ 个关键点 $\{d_i\}$，保证其中包含 $0,n$，需要从 $0$ 走到 $n$。从 $0$ 时刻开始，在接下来的 $g$ 个单位时间内必须不停移动，每个单位时间可以移动一个单位距离。如果你现在在两个关键点之间的线段上，你就只能按照上一步行走的方向继续移动。如果你现在在任意一个关键点上，那么你下一步可以自由选择往左或往右走。当然，你不能移动到 $0$ 的左边或是 $n$ 的右边。  
$g$ 个单位时间结束后，你必须恰好在任意一个关键点上，等待 $r$ 个单位时间再继续移动。接下来，在 $r$ 个单位时间结束后，重新开始 $g$ 个可以继续移动的单位时间，依此循环。  
求按照上述规则，从 $0$ 走到 $n$ 的最短时间。如果无法完成，输出 $-1$。  
$m\le 10^4,~g,r\le 1000$
### 题解
定义完整周期为某一段 $g$ 个单位时间的的可移动时间段加上紧跟其后的 $r$ 个单位时间的不可移动时间段。易知所有完整周期没有本质区别。  
考虑到，如果走到某个 $d_i$ 点时，总共用了 $j$ 秒加上若干个完整周期，显然我们要尽可能少用完整周期。考虑设 $dis_{i,j}$ 为用了不完整的 $j$ 秒与若干个完整周期，从 $d_1=0$ 走到 $d_i$ 所需的最小周期。从每个点可以向相邻的至多两个点转移。考虑往左侧相邻的关键点 $d_{i-1}$ 转移，我们可以写出如下的几种转移：
- 如果 $d_i-d_{i-1}+j<g$，此时还在同一周期内，不需要新增周期，用 $dis_{i,j}$ 更新 $dis_{i-1,d_i-d_{i-1}+j}$；
- 如果 $d_i-d_{i-1}+j=g$，此时恰好走完一个周期的可移动时间段，必须等待 $r$ 个单位时间，新增一个完整周期，用 $dis_{i,j}+1$ 更新 $dis_{i-1,0}$；
- 如果 $d_i-d_{i-1}+j>g$ ，由于 $g$ 结束时必须停在关键点上，这种转移不合法。

如果往右侧相邻关键点转移，讨论也是类似的，这里不再赘述。    
发现转移边只有 $0$ 和 $1$ 两种权值，直接上个 $0/1$ bfs 就完事了。  
最后统计所有的 $dis_{m,j}$ 实际花费的时间，取最小值即可。要注意，如果 $j=0$ 且 $dis_{m,j}>0$ ，应该少算一个 $r$，因为此时不需要再在终点处等待 $r$ 个单位了。  
注意这道题的素质出题人没有将 $\{d_i\}$ 排序，众多神仙惨遭 FST。
### 代码
```cpp
#include<bits/stdc++.h>
#define reg register
typedef long long ll;
using namespace std;
const int MN=1e4+5;
int n,m,G,R,d[MN],dis[MN][1005];
typedef pair<int,int>pii;
deque<pii>q;
int main(){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=m;i++)scanf("%d",d+i);
	sort(d+1,d+1+m);
	scanf("%d%d",&G,&R);
	memset(dis,-1,sizeof(dis));
	dis[1][0]=0;q.push_front(make_pair(1,0));
	while(!q.empty()){
		reg pii v=q.front();q.pop_front();
		if(v.first>1){
			reg int val=d[v.first]-d[v.first-1]+v.second;
			if(val<G){
				if(dis[v.first-1][val]<0){
					dis[v.first-1][val]=dis[v.first][v.second];
					q.push_front(make_pair(v.first-1,val));
				}
			}
			if(val==G){
				if(dis[v.first-1][0]<0){
					dis[v.first-1][0]=dis[v.first][v.second]+1;
					q.push_back(make_pair(v.first-1,0));
				}
			}
		}
		if(v.first<m){
			reg int val=d[v.first+1]-d[v.first]+v.second;
			if(val<G){
				if(dis[v.first+1][val]<0){
					dis[v.first+1][val]=dis[v.first][v.second];
					q.push_front(make_pair(v.first+1,val));
				}
			}
			if(val==G){
				if(dis[v.first+1][0]<0){
					dis[v.first+1][0]=dis[v.first][v.second]+1;
					q.push_back(make_pair(v.first+1,0));
				}
			}
		}
	}
	reg ll Ans=-1,Res;
	for(reg int i=0;i<G;i++){
		if(dis[m][i]<0)continue;
		Res=1ll*dis[m][i]*(G+R)+i;
		if(!i&&dis[m][i])Res-=R;
		if(Ans<0||Ans>Res)Ans=Res;
	}
	printf("%lld\n",Ans);
	return 0;
}
```

---

## 作者：FZzzz (赞：5)

这是个悲伤的故事。

比赛的时候我想出了一个 dijkstra 的做法，然后感觉过不去。

这时有神仙来教育我了，用什么 dj 啊明明是 01bfs 啊。

不对啊 01bfs 也过不去啊？

1e7 肯定过得去啊你在想什么啊。

那空间开不下啊？

1e7 的空间才几十 G 吧肯定开的下啊，你需要重学时空复杂度吧。

然后我恍然大悟赶快 rush，结果要交的时候比赛就结束了……

所以我就痛失上分。

~~然而幸好没交上去因为我没对 $d$ 值排序。~~

------------
说了一大堆废话，下面是题解。

设 $(i,j)$ 为一个节点，表示到了第 $i$ 个点，绿灯过去了 $j$ 秒。

然后转移的话就是如果走过去刚好到红灯，就走过去，代价为 $1$ 表示一个周期。

如果走过去还没到红灯，那就是直接走，代价为 $0$。

01bfs 即可。

然后 01bfs 的话就是对于代价为 $0$ 的话就加到队列前面，反之加到后面，大概思想就是到了一个点直接把它所有的能直接到的点遍历完。

然后最后枚举最后到了哪个点就行了。

下面的代码由于是赛时 rush 的，很丑。
```cpp
#include<algorithm>
#include<queue>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxm=1e4+5,maxg=1e3+5;
int n,m,d[maxm],g,r;
int dis[maxm][maxg];
bool vis[maxm][maxg];
typedef pair<int,int> pii;
void bfs(){
	deque<pii> dq;
	dq.push_back(pii(0,0));
	dis[0][0]=0;
	vis[0][0]=1;
	while(!dq.empty()){
		pii u=dq.front();
		dq.pop_front();
		if(u.first>0){
			if(u.second+d[u.first]-d[u.first-1]<g){
				if(!vis[u.first-1][u.second+d[u.first]-d[u.first-1]]){
					dis[u.first-1][u.second+d[u.first]-d[u.first-1]]=dis[u.first][u.second];
					vis[u.first-1][u.second+d[u.first]-d[u.first-1]]=1;
					dq.push_front(pii(u.first-1,u.second+d[u.first]-d[u.first-1]));
				}
			}
			else if(u.second+d[u.first]-d[u.first-1]==g){
				if(!vis[u.first-1][0]){
					dis[u.first-1][0]=dis[u.first][u.second]+1;
					vis[u.first-1][0]=1;
					dq.push_back(pii(u.first-1,0));
				}
			}
		}
		if(u.first<m-2){
			if(u.second+d[u.first+1]-d[u.first]<g){
				if(!vis[u.first+1][u.second+d[u.first+1]-d[u.first]]){
					dis[u.first+1][u.second+d[u.first+1]-d[u.first]]=dis[u.first][u.second];
					vis[u.first+1][u.second+d[u.first+1]-d[u.first]]=1;
					dq.push_front(pii(u.first+1,u.second+d[u.first+1]-d[u.first]));
				}
			}
			else if(u.second+d[u.first+1]-d[u.first]==g){
				if(!vis[u.first+1][0]){
					dis[u.first+1][0]=dis[u.first][u.second]+1;
					vis[u.first+1][0]=1;
					dq.push_back(pii(u.first+1,0));
				}
			}
		}
	}
}
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	m=readint();
	for(int i=0;i<m;i++) d[i]=readint();
	sort(d,d+m);
	g=readint();
	r=readint();
	bfs();
	int ans=2e9;
	for(int i=0;i<m-1;i++) if(vis[i][0]&&d[m-1]-d[i]<=g)
		ans=min(ans,dis[i][0]*(r+g)+d[m-1]-d[i]);
	if(ans<2e9) printf("%d\n",ans);
	else printf("-1\n");
	return 0;
}
```
据说这样做麻烦了？不知道有啥简单方法。

---

## 作者：juicyyou (赞：4)

# CF1340C Nastya and Unexpected Guest
## 题目大意：
你有 $m$ 个在一条直线上的岛屿，你每秒可以移动 1 个单位长度并且你必须每时每刻都在移动中。在时间上，每 $g$ 秒过后，都会有一段长度为 $r$ 秒的红灯，在红灯阶段，你不可以移动并且你必须待在一座岛屿上。请问最少需要多少时间才能从第一个岛屿到达第 $m$ 个岛屿。
## 解法：
首先，我们用 $dp_{i, j}$表示距离上一次绿灯开始已经了$j$ 分钟，并且目前位于第 $i$ 个安全岛上时，总共最少经过了多少个绿灯红灯的循环，那么我们易得：
当$j + t_{i + 1} - t_{i} < g$ 时, 有：
$$dp_{i + 1, j + t(i + 1) - t(i - 1)} = dp_{i, j}$$

而当$j + t_{i + 1} - t_{i} = g$时，有：
$$dp_{i + 1, j + t(i + 1) - t(i)} = dp_{i, j} + 1$$

当其为 $i - 1$ 时亦同理。

那么这个题就是一个裸的 01-BFS 了。

那最终的答案就是：

$$\min\limits_{0 \le i < g}\{dp_{n, i} \times (g + r) + i - r \times \left[i = 0\right]\}$$

**注意，当 $i$ 为 $0$ 的时侯，需要减去一个 $r$ ！！！**

下面是我的 Code ：
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<stack>
#include<vector>
#include<map>
#include<queue>
#include<cmath>
#include<set>
#include<cstdlib>
#include<cctype>
#include<ctime>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll maxn = 1e4 + 5;
const ll maxm = 1e3 + 5;
template<class T>
inline T qread(T &IEE){
	register T x = 0, f = 1;
	register char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -f;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return IEE = x * f;
}
template<class T>
inline void qwrite(T a){
	if(!a){
		putchar('0');
		return ;
	}
 	if(a < 0){
		putchar('-');
		a = -a;
	}
	if(a > 9) qwrite(a / 10);
	putchar(a % 10 + 48);
	return ;
}
template<class T>
inline T ab(T a){
	return (a > 0) ? a : -a;
}
template<class T>
inline void swa(T &a, T &b){
	a ^= b ^= a ^= b;
	return ;
}
ll ans, v, tmp, dis, u, r, g, m, n;
ll a[maxn];
ll dp[maxn][maxm];
struct node{
	ll id, val;
	node(ll dd = 0, ll vv = 0){
		id = dd;
		val = vv;
	}
};
deque<node> q;
int main(){
	cin >> n >> m;
	for(int i = 1;i <= m;i++){
		cin >> a[i];
	}
	cin >> g >> r;
//	qread(g);
//	qread(r);
	sort(a + 1, a + m + 1);
	memset(dp, -1, sizeof(dp));
	q.push_front(node(1, 0));
	dp[1][0] = 0;
	ans = 0x3f3f3f3f;
	while(!q.empty()){ // 01-BFS
		node fr = q.front();
		q.pop_front();
		v = fr.val, u = fr.id;
		if(u == m){
			if(v == 0){
				ans = min(ans, dp[m][v] * (g + r) - r);
			} else {
				ans = min(ans, dp[m][v] * (g + r) + v);
			}
			continue;
		}
		dis = a[u + 1] - a[u];
		if(v + dis < g && dp[u + 1][v + dis] == -1){
			dp[u + 1][v + dis] = dp[u][v];
			q.push_front(node(u + 1, v + dis));
		} 
		if(v + dis == g && dp[u + 1][0] == -1){
			dp[u + 1][0] = dp[u][v] + 1;
			q.push_back(node(u + 1, 0));
		}
		if(u >= 1){
			dis = a[u] - a[u - 1];
			if(v + dis < g && dp[u - 1][v + dis] == -1){
				dp[u - 1][v + dis] = dp[u][v];
				q.push_front(node(u - 1, v + dis));
			} 
			if(v + dis == g && dp[u - 1][0] == -1){
				dp[u - 1][0] = dp[u][v] + 1;
				q.push_back(node(u - 1, 0));
			}
		}
	}
	if(ans == 0x3f3f3f3f){
		puts("-1");
		return 0;
	}
	cout << ans << endl;
	return 0;
}

```

上述算法的复杂度即为 $\mathcal O(mg)$，可以通过此题。

---

## 作者：intel_core (赞：2)

第一眼看到这个题的时候， $n\le 10^6 , m\le 10^4$ ，而且不到安全点不能调头，所以不用管非安全点的那些点。

又看到 $g,r \le 10^3$ ，也就是说 $O((g+r)m)$ 的算法可以接受。

这引导我们想到可以用 $p_{i,j}$ 表示在一个绿灯周期内的第 $j$ 秒到达安全点 $i$ 时最少经过了多少个红灯周期。

计算 $\{p\}$ 的过程本质上是动态规划，很明显满足最优子结构，无后效性，所以这个做法是正确的。

这样我们直接在相邻安全点之间跑转移，实现本质上是 `01BFS`，复杂度 $O((g+r)m)$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e4+10;
const int MR=1e3+10;
int n,m,d[NR],t1,t2;

#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define pf push_front
deque<pii>q;
int p[NR][MR];

void upd1(pii x){
	if(x.fi==1)return;
	if(x.se+d[x.fi]-d[x.fi-1]<t1){
		if(p[x.fi-1][x.se+d[x.fi]-d[x.fi-1]]>p[x.fi][x.se])
			p[x.fi-1][x.se+d[x.fi]-d[x.fi-1]]=p[x.fi][x.se],q.pf(mkp(x.fi-1,x.se+d[x.fi]-d[x.fi-1]));
	}
	if(x.se+d[x.fi]-d[x.fi-1]==t1){
		if(p[x.fi-1][0]>p[x.fi][x.se]+1)
			p[x.fi-1][0]=p[x.fi][x.se]+1,q.pb(mkp(x.fi-1,0));
	}
}
void upd2(pii x){
	if(x.fi==m)return;
	if(x.se-d[x.fi]+d[x.fi+1]<t1){
		if(p[x.fi+1][x.se-d[x.fi]+d[x.fi+1]]>p[x.fi][x.se])
			p[x.fi+1][x.se-d[x.fi]+d[x.fi+1]]=p[x.fi][x.se],q.pf(mkp(x.fi+1,x.se-d[x.fi]+d[x.fi+1]));
	}
	if(x.se-d[x.fi]+d[x.fi+1]==t1){
		if(p[x.fi+1][0]>p[x.fi][x.se]+1)
			p[x.fi+1][0]=p[x.fi][x.se]+1,q.pb(mkp(x.fi+1,0));
	}
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>d[i];
	cin>>t1>>t2;
	sort(d+1,d+1+m);
	memset(p,999999,sizeof(p));
	p[1][0]=0;q.pb(mkp(1,0));
	while(!q.empty()){
		pii x=q.front();q.pop_front();
		upd1(x);upd2(x);
	}
	ll ans=1ll*(t1+t2)*(p[m][0]-1)+t1;
	for(int i=1;i<t1;i++)ans=min(ans,1ll*(t1+t2)*p[m][i]+i);
	if(ans>1e9)puts("-1");
	else cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Zyh_AKer (赞：1)

## CF1340C
### 题目大意
在 $[0, n]$ 的范围内有 $m$ 个安全岛，从 $0$ 号路口出发，每秒可以从 $u$ 号路口走到 $u+1$ 或 $u-1$ 号路口，**注意，他只能在安全岛上改变方向。**  
有一个红绿灯，绿灯时间为 $g$ 秒，红灯时间为 $r$ 秒，在绿灯的时候必须移动，在红灯时间内必须在某个安全岛停留。出发的时候红绿灯刚从红灯变为绿灯。  
求从 $0$ 走到 $n$ 的最少花费时间。   
$1 \le n \le 10^6,1 \le g,r \le 10^3,1 \le m \le 10^4。$  
### 标签
动态规划 DP，01-BFS。
### 题解
设 $dis_{i,j}$ 表示在第 $i$ 个安全岛上，距离上一个绿灯已经过去了 $j$ 秒最少有多少个红绿灯周期，则：  
$j+d_{i+1}-d_i<g$ 并没有走完一个周期，$dis_{i+1,j+d_{i+1}-d_i} \gets dis_{i,j}$；  
$j+d_{i+1}-d_i=g$ 刚好走完一个周期，周期数 $+1$，$j=0$，$dis_{i+1,0} \gets dis_{i,j}+1$;  
$j+d_{i+1}-d_i>g$ 走完了一个周期还是没有走到，则无法在安全岛上等红灯，无法转移。  
那么这个就是 01-BFS 了。  
时间复杂度：$O(mg)$  
**需要注意两点：**   
**1. 因为 $d$ 是无序的，所以要对 $d$ 进行排序**  ~~这一点坑了我很久~~ 。  
**2. 在统计答案时如果 $j=0$，需要 $-r$**。   
说了这么多，现在来看看My Code
```cpp
# include <bits/stdc++.h>
#define int long long
using namespace std;
using pii = pair <int, int>;
const int N = 1e4 + 10;
const int M = 1e3 + 10;
const int INF = 1e18;
int n, m;
int d[N];
int g, r;
int dis[N][M];
deque <pii> dq;
int ans = INF;
signed main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i ++)
    {
        cin >> d[i];
    }
    cin >> g >> r;
    fill(dis[0], dis[m + 2], INF);
    sort(d + 1, d + 1 + m);
    dis[1][0] = 0;
    dq.push_back({1, 0});
    while (!dq.empty())
    {
        int u = dq.front().first;
        int w = dq.front().second;
        dq.pop_front();
        if (u == m)
        {
            ans = min(ans, dis[u][w] * (g + r) + w - r * (w == 0));
            continue;
        }
        if (u < m)
        {
            int len = d[u + 1] - d[u];
            if (len + w < g && dis[u + 1][len + w] > dis[u][w])
            {
                dis[u + 1][len + w] = dis[u][w];
                dq.push_front({u + 1, len + w});
            }
            else if (len + w == g && dis[u + 1][0] > dis[u][w] + 1)
            {
                dis[u + 1][0] = dis[u][w] + 1;
                dq.push_back({u + 1, 0});
            } 
        }
        if (u > 1)
        {
            int len = d[u] - d[u - 1];
            if (len + w < g && dis[u - 1][len + w] > dis[u][w])
            {
                dis[u - 1][len + w] = dis[u][w];
                dq.push_front({u - 1, len + w});
            }
            else if (len + w == g && dis[u - 1][0] > dis[u][w] + 1)
            {
                dis[u - 1][0] = dis[u][w] + 1;
                dq.push_back({u - 1, 0});
            } 
        }
    }
    cout << (ans == INF ? -1 : ans);
    return 0;
}

```

---

## 作者：ZigZagKmp (赞：1)

本文同步发表于我的[cnblog](https://www.cnblogs.com/ZigZagKmp/p/13749280.html)

本场题解见[此](https://www.luogu.com.cn/blog/ZigZagKmp/codeforces-1340-solution)
## CF1340C
### 题意简述
在$[0,n]$范围内有$m$个安全岛，保证 $0,n$ 两个整点是安全岛。

从 $0$ 出发，每秒钟可以从 $x$ 移动到 $x−1$ 或 $x+1$，注意只能在安全岛改变移动方向。

有一个红绿灯，绿灯时间为 $g$ 秒，红灯时间为 $r$ 秒。在绿灯时间内必须移动，在红灯时间内必须在某个安全岛停留。出发时红绿灯刚从红灯变为绿灯。

求从 $0$ 到 $n$ 的最短时间。

$1\le n\le 10^6,1\le g,r\le 10^3,1\le m\le 10^4$。
### 算法标签
dp 01bfs
### 算法分析
我们称一次绿灯和一次红灯为一个周期，则走到$n$应当是若干个完整周期和1个不完整周期。

设 $dp(x,i)$ 表示从 $0$ 走到 $x$ 所需要的最少周期个数。

分类讨论从一个安全岛到另一个安全岛的可能情况，不难发现只需要考虑相邻安全岛的转移情况即可覆盖所有的状态。

设两个**相邻**的安全岛 $x,y$ ，距离为 $w$ ，现在要从 $x$ 转移到 $y$，下面讨论对于一个不完整周期的时间 $i$ 的转移（即 $dp(x,i)$ 到 $dp(y,?)$ 的转移）。

- $i+w<m$ 仍然在同一个周期内，周期数不变，$dp(y,i+w)<-dp(x,i)$；
- $i+w=m$ 这时一个周期结束，周期数+1且不完整周期为 $0$ ，$dp(y,0)<-dp(x,i)+1$；
- $i+w>m$ 由题意知，这时如果从 $x$ 转移到 $y$ 中间会有红灯，且无法在安全岛停留，故无法转移。

观察这个转移，发现转移方向是双向的，因此转移带环。带环dp的最优化问题一般看作最短路，本题因为转移权值为 $0/1$ ，可以使用 ``01bfs`` 。

时间复杂度 $O(mg)$ 。
### 代码实现
注意恰好走完一个周期不需要再等红灯。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 10005
#define maxm 1005
#define inf 0x3f3f3f3f
#define LL long long
#define mod 1000000007
#define local
void file(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}
template <typename Tp>void read(Tp &x){
	x=0;int fh=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}x*=fh;
}
int N,n,m,R;
int a[maxn];
int dp[maxn][maxm];
struct node{
	int id,tm;
};
deque<node>q;
void bfs(){
	memset(dp,0x3f,sizeof(dp));
	dp[1][0]=0;q.push_back((node){1,0});
	while(!q.empty()){
		int x=q.front().id,t=q.front().tm;q.pop_front();
		if(x>1){
			int y=x-1,w=a[x]-a[x-1];
			if(t+w==m){
				if(dp[y][0]>dp[x][t]+1){
					dp[y][0]=dp[x][t]+1;
					q.push_back((node){y,0});
				}
			}
			if(t+w<m){
				if(dp[y][t+w]>dp[x][t]){
					dp[y][t+w]=dp[x][t];
					q.push_front((node){y,t+w});
				}
			}
		}
		if(x<n){
			int y=x+1,w=a[x+1]-a[x];
			if(t+w==m){
				if(dp[y][0]>dp[x][t]+1){
					dp[y][0]=dp[x][t]+1;
					q.push_back((node){y,0});
				}
			}
			if(t+w<m){
				if(dp[y][t+w]>dp[x][t]){
					dp[y][t+w]=dp[x][t];
					q.push_front((node){y,t+w});
				}
			}
		}
	}
}
signed main(){
	read(N);read(n);
	for(int i=1;i<=n;++i)read(a[i]);
	read(m);read(R);
	sort(a+1,a+n+1);
	bfs();
	int mn=inf;
	for(int i=0;i<=m;++i){
		if(dp[n][i]==inf)continue;
		int tmp=dp[n][i]*(m+R)+i;
		if(i==0)tmp-=R;
		mn=min(mn,tmp);
	}
	if(mn==inf)puts("-1");
	else printf("%d\n",mn);
	return 0;
}

```

---

## 作者：ny_jerry2 (赞：0)

## 前言
一道很好的 dp + 最短路/01-bfs 练习题。

## 思路
看到最优性问题，应该快速想到 dp。  

首先可以发现：我们只用去枚举安全岛，不用把所有路口都枚举一次。为什么？

1. 开始和结尾都保证是安全岛。
2. 能否移动的条件只和是不是安全岛有关。
3. 安全岛之间的移动距离显然可以算出来。

因此，只需要枚举安全岛就够了。

我最开始想 $f_{i,j}$ 表示能否时间刚好为 $j$ 时到达安全岛 $i$。显然，时空都不可以过。考虑优化。

因为红绿灯实际上是一个周期。显然，周期轮数越少越好，而我们也可以根据周期轮数计算出时间。

因此，设 $f_{i,j}$ 表示到了第 $i$ 个安全岛，且在变成绿灯后的第 $j$ 秒经过的最少周期轮数。

转移（以向左移动为例）：

设到下一个安全岛的距离为 $w$。

- $j+w >g$  
  显然不合法，到了中间某一个非安全岛路口会停下。
  
- $j+w=g$  

$$
f_{i-1,0}=\min(f_{i-1,0},f_{i,j}+1)
$$

- $j+w<g$

$$
f_{i-1,j+w}=\min(f_{i-1,j+w},f_{i,j})
$$

因为是左右移动，所以用最短路处理。考虑到边权只有 0 和 1，用更方便的 01-bfs。

初始化：$f_{1,0} = 0$。
答案：

$$
\min_{0 \le i < g} f_{m,i} \times (g+r) +i
$$

注意：$i=0$ 时要减去 $r$。因为此时实际上它是刚好撞上红灯，也就是只经历半个周期。

## 代码
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
int n,m;
int green,red;
const int N=1e4+10;
int d[N];
int dist[N][1010];
struct node{
	int u,tim;
};
void bfs(){
	memset(dist,0x3f,sizeof dist);
	dist[1][0]=0;
	deque<node> q;
	q.push_back({1,0});
	while(q.size()){
		node t=q.front();
		q.pop_front();
		int u=t.u,tim=t.tim;
		if(u>1){
			int ne=u-1,w=d[u]-d[ne];
			if(tim+w==green&&dist[ne][0]>dist[u][tim]+1){
				dist[ne][0]=dist[u][tim]+1;
				q.push_back({ne,0});
			}else if(tim+w<green&&dist[ne][tim+w]>dist[u][tim]){
				dist[ne][tim+w]=dist[u][tim];
				q.push_front({ne,tim+w});
			}
		}
		if(u<m){
			int ne=u+1,w=d[ne]-d[u];
			if(tim+w==green&&dist[ne][0]>dist[u][tim]+1){
				dist[ne][0]=dist[u][tim]+1;
				q.push_back({ne,0});
			}else if(tim+w<green&&dist[ne][tim+w]>dist[u][tim]){
				dist[ne][tim+w]=dist[u][tim];
				q.push_front({ne,tim+w});
			}
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		scanf("%d",&d[i]);
	}
	sort(d+1,d+m+1);
	cin>>green>>red;
	bfs();
	int ans=0x3f3f3f3f;
	for(int i=0;i<green;i++){
		if(dist[m][i]==0x3f3f3f3f){
			continue;
		}
		ans=min(ans,dist[m][i]*(green+red)+i-(i==0)*red);
	}
	if(ans==0x3f3f3f3f){
		cout<<-1;
	}else{
		cout<<ans;
	}
}
```

---

## 作者：SnowTrace (赞：0)

惯性思维惯性有点大了。

WC2023 我就是被这种惯性创似的。我一直在想能不能直接维护出任意两点间的可达性，然后想了一年还是不知道怎么做。

----

我们只需要把这样走路的一个过程拆分成若干段相邻关键点之间的边，然后在上面做最短路即可。也就是我们设 $dis_{i,j}$ 表示走到第 $i$ 个点时恰好到了这个周期的第 $j$ 秒时最小的周期数，每次往两边转移，显然没有后效性，具体用双端队列实现。

需要特判的是如果走到终点的时候恰好走完一整个周期，那其实可以少等一个红灯，也就是答案减去 $r$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int d[10005];
int g,r;
int dis[10005][1005];
signed main(){
	cin >> n >> m;
	for(int i =1;i<=m;i++)cin >> d[i];
	sort(d+1,d+1+m);cin >> g >> r;
	memset(dis,63,sizeof(dis));dis[1][0] = 0;
	deque<pair<int,int> >q;q.push_front({1,0});int cnt =0 ;
	while(!q.empty()){
		int id = q.front().first,t = q.front().second;q.pop_front();
		if(id!=1){
			int dd = t+d[id]-d[id-1];
			if(dd>g);
			else if(dd==g){
				if(dis[id-1][0]>dis[id][t]+1){
					dis[id-1][0] = dis[id][t]+1;
					q.push_back({id-1,0});
				}
			}else{
				if(dis[id-1][dd]>dis[id][t]){
					dis[id-1][dd] = dis[id][t];
					q.push_front({id-1,dd});
				}
			}
		}if(id!=m){
			int dd = t+d[id+1]-d[id];
			if(dd>g);
			else if(dd==g){
				if(dis[id+1][0]>dis[id][t]+1){
					dis[id+1][0] = dis[id][t]+1;
					q.push_back({id+1,0});
				}
			}else{
				if(dis[id+1][dd]>dis[id][t]){
					dis[id+1][dd] = dis[id][t];
					q.push_front({id+1,dd});
				}
			}
		}
	}int ans = 10000000005,pos =0;
	for(int i =0;i<g;i++){
		if(dis[m][i]<=n and dis[m][i]*(g+r)+i-r*(i == 0)<ans){
			ans = dis[m][i]*(g+r)+i-r*(i == 0),pos = i;
		}
	}if(ans == 10000000005){
		cout << -1 << endl;return 0;
	}cout << ans << endl;
	
}/*
如果能处理可达性的话就做完了。
处理不了。怎么办呢。
把 GF 写出来就能做到 O(nmpolylog)，不是。
直接跑最短路。 
*/
```

---

