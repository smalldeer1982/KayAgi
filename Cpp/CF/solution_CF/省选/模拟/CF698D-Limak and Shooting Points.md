# Limak and Shooting Points

## 题目描述

Bearland is a dangerous place. Limak can’t travel on foot. Instead, he has $ k $ magic teleportation stones. Each stone can be used at most once. The $ i $ -th stone allows to teleport to a point $ (ax_{i},ay_{i}) $ . Limak can use stones in any order.

There are $ n $ monsters in Bearland. The $ i $ -th of them stands at $ (mx_{i},my_{i}) $ .

The given $ k+n $ points are pairwise distinct.

After each teleportation, Limak can shoot an arrow in some direction. An arrow will hit the first monster in the chosen direction. Then, both an arrow and a monster disappear. It’s dangerous to stay in one place for long, so Limak can shoot only one arrow from one place.

A monster should be afraid if it’s possible that Limak will hit it. How many monsters should be afraid of Limak?

## 说明/提示

In the first sample, there are two stones and four monsters. Stones allow to teleport to points $ (-2,-1) $ and $ (4,5) $ , marked blue in the drawing below. Monsters are at $ (4,2) $ , $ (2,1) $ , $ (4,-1) $ and $ (1,-1) $ , marked red. A monster at $ (4,-1) $ shouldn't be afraid because it's impossible that Limak will hit it with an arrow. Other three monsters can be hit and thus the answer is $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF698D/70ee2c528dc792a1ade2fc595342213b793a806e.png)In the second sample, five monsters should be afraid. Safe monsters are those at $ (300,600) $ , $ (170,340) $ and $ (90,180) $ .

## 样例 #1

### 输入

```
2 4
-2 -1
4 5
4 2
2 1
4 -1
1 -1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 8
10 20
0 0
20 40
300 600
30 60
170 340
50 100
28 56
90 180
-4 -8
-1 -2
```

### 输出

```
5
```

# 题解

## 作者：justin_cao (赞：7)

可以发现，如果我们规定了射击地点射击的顺序，同时规定这次要打死的目标是哪一个，那么这只怪物能不能被打死，是可以直接模拟出来的。

怎么模拟呢？

假设你规定的顺序是$p_1,p_2...p_k$，那么就考虑用$p_1$最后去射死这个怪，那么$p_1$到怪物的路上可能有其他的怪$x_1,x_2...$，那么就考虑用$p_2$去射死$x_1$，那么$p_2$到$x_1$的路上可能也还有其他的怪，那么以此类推。。。这个搜索最多只会进行$k$层（因为射击地点只有$k$个），所以复杂度是$O(k)$的。

那么剩下的就是用点积和叉积预处理$p[i][j]$表示第$i$个射击地点到第$j$个怪的路上的其他怪，然后就直接$k!$判断每一个怪能否被打死即可。

复杂度$O(n\times k!\times k)$。

code：
```cpp
#include<bits/stdc++.h>
#define maxn 1010
using namespace std;
typedef long long ll;
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch-'0'<0||ch-'0'>9){if(ch=='-') f=-1;ch=getchar();}
    while(ch-'0'>=0&&ch-'0'<=9){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,K;
struct P{
    ll x,y;
}a[10],b[maxn];
P operator - (P a,P b)
{
    return (P){a.x-b.x,a.y-b.y};
}
ll operator * (P a,P b)
{
    return a.x*b.y-a.y*b.x;
}
ll operator ^ (P a,P b)
{
    return a.x*b.x+a.y*b.y;
}
vector<int>p[10][maxn];
int vis[10],ans,gg[maxn],tot,id[10],tim;
bool check(int x)
{
    tot++;
    if(tot>K)  return false;
    if(!p[id[tot]][x].size())  return gg[x]=tim,true;
    int tmp=tot;
    for(int i=0;i<p[id[tmp]][x].size();i++)
    {
        int to=p[id[tmp]][x][i];
        if(gg[to]!=tim)
          if(!check(to))  return false;
    }
    return gg[x]=tim,true;
}
bool dfs(int x,int to)
{
    if(x>K)
    {
        tim++;tot=0;
        return check(to);
    }
    for(int i=1;i<=K;i++)
    {
        if(!vis[i])
        {
            vis[i]=1;id[x]=i;
            if(dfs(x+1,to))  return true;
            vis[i]=0;
        } 
    }
    return false;
}
int main()
{
    K=read();n=read();
    for(int i=1;i<=K;i++)  a[i].x=read(),a[i].y=read();
    for(int i=1;i<=n;i++)  b[i].x=read(),b[i].y=read();
    for(int i=1;i<=K;i++)
    {
        for(int j=1;j<=n;j++)
        {
            for(int k=1;k<=n;k++)
            {  
                if(j==k)  continue;
                if((a[i]-b[j])*(b[k]-b[j])==0&&((a[i]-b[j])^(b[k]-b[j]))<0)  p[i][k].push_back(j);
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        memset(vis,0,sizeof(vis));
        if(dfs(1,i))  ans++;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：xht (赞：7)

> [CF698D Limak and Shooting Points](https://codeforces.com/contest/698/problem/D)

## 题意

- 平面上有 $k$ 个人和 $n$ 个怪物，每个人手中有一支箭。
- 每支箭可以往任意方向射出，击中这个方向上的第一个怪物后，箭和怪物都会消失。
- 问有多少怪物可能会被击中。
- $k \le 7$，$n \le 10^3$。

## 题解

考虑枚举**某种**射击「顺序」和怪物，然后判断按照这个「顺序」能否击中怪物。

这里的「顺序」指的并不是**射击时间的顺序**（称之为「方案」）。对于一种「方案」，我们如下定义其「顺序」：

> 设这种「方案」为 $p_{1,2,\cdots,c}$，则 $p_c$ 就是最后击中目标怪物的人，之前都是在清理障碍。
>
> 假设障碍为 $x_{1,2,\dots,m}$，则 $p_{1,2,\dots,c-1}$ 可以被分成 $m$ 段，其中第 $i$ 段是清理障碍 $x_i$ 的「方案」。**注意，击中某个怪物可能为多次清理障碍提供便利，因此段可以为空，如果单独把段拿出来也可能无法清理障碍。**
>
> 这种「方案」对应的「顺序」为：
>
> **$p_c$，清理障碍 $x_1$ 的「顺序」，清理障碍 $x_2$ 的「顺序」，$\cdots$，清理障碍 $x_m$ 的「顺序」。**
>
> 其中清理障碍 $x_i$ 的「顺序」是用清理障碍 $x_i$ 的「方案」定义的，因此实际上这个定义是一个递归定义，边界自然是没有障碍的情况。

回到我们的思路：枚举「顺序」和怪物，判断按照这个「顺序」能否击中怪物。

由于每种「方案」都定义了一个「顺序」，因此如果存在击中目标怪物「方案」，我们就一定可以枚举到它定义的「顺序」。

但现在还有两个问题：

1. 我们对「方案」定义了「顺序」，那一个「顺序」是否只唯一的对应了一个「方案」呢？
2. 如果一个「顺序」只唯一的对应了一个「方案」，我们如何通过「顺序」还原「方案」？

其实这两个问题是同一个问题，因为根据还原的过程可以发现一个「顺序」确实唯一的对应了一个「方案」。

下面是还原的过程：

> 假设某种「顺序」为 $q_{1,2,\dots,c}$，则击中目标怪物的人为 $q_1$。
>
> 在 $q_1$ 击中目标怪物的路上，如果有障碍，则障碍为 $x_{1,2,\dots,m}$，击中 $x_1$ 的人为 $q_2$。
>
> 在 $q_2$ 击中 $x_1$ 的路上，如果有障碍，则障碍为 $x_{2,\dots,?}$，击中 $x_2$ 的人为 $q_3$。
>
> 依次类推。
>
> 如果在某个 $q$ 击中某个 $x$ 的路上没有障碍，则回溯，可以发现还原的过程也是递归的。

由于还原的方式唯一，因此一个「顺序」唯一的对应了一个「方案」。

至此，我们算法的主体思路如下：

**枚举「顺序」和怪物，通过还原「顺序」为「方案」的过程判断按照这个「顺序」能否击中怪物。**

考虑时间复杂度，「顺序」的总个数是 $\mathcal O(k!)$ 的......吗？

好像不是，因为「顺序」的长度可能为 $1 \sim k$。

但是通过还原的过程可以发现，我们只用枚举所有长度为 $k$ 的「顺序」，如果这个「顺序」的某个前缀就是一种「方案」，是可以直接被判断出来的。

所以，重来一遍！

考虑时间复杂度，「顺序」的总个数是 $\mathcal O(k!)$ 的，怪物的总个数为 $\mathcal O(n)$，还原的过程复杂度为 $\mathcal O(k)$，总时间复杂度 $\mathcal O(nk!k)$。

## 代码

```cpp
const int N = 1e3 + 7, K = 9;
int k, n, q[K], ans, t;
bool v[N];
pi a[K], b[N];
vi p[K][N], e;

inline bool pd(pi x, pi y, pi z) {
	if (y == z) return 0;
	if (z.fi < min(x.fi, y.fi) || z.fi > max(x.fi, y.fi)) return 0;
	if (z.se < min(x.se, y.se) || z.se > max(x.se, y.se)) return 0;
	return 1ll * (y.se - x.se) * (z.fi - x.fi) == 1ll * (z.se - x.se) * (y.fi - x.fi);
}

bool dfs(int x) {
	if (t > k) return 0;
	for (int y : p[q[t]][x])
		if (!v[y]) {
			++t;
			if (!dfs(y)) return 0;
		}
	return e.pb(x), v[x] = 1;
}

int main() {
	rd(k), rd(n);
	for (int i = 1; i <= k; i++) rd(a[i].fi), rd(a[i].se); 
	for (int i = 1; i <= n; i++) rd(b[i].fi), rd(b[i].se);
	for (int i = 1; i <= k; i++)
		for (int j = 1; j <= n; j++)
			for (int o = 1; o <= n; o++)
				if (pd(a[i], b[j], b[o])) {
					p[i][j].pb(o);
					if ((int)p[i][j].size() == k) break;
				}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= k; j++) q[j] = j;
		do {
			while (e.size()) v[e.back()] = 0, e.pop_back();
			t = 1;
			if (dfs(i)) {
				++ans;
				break;
			}
		} while (next_permutation(q + 1, q + k + 1));
	}
	print(ans);
	return 0;
}
```

---

## 作者：小粉兔 (赞：4)

我们单独对每个目标 $i$ 考虑它是否能被射击到，然后求和即可得到答案。

考虑一个射击到目标 $i$ 的顺序，它的最后一发子弹会击中目标，而之前的子弹都是在清理障碍。

设最后一发子弹是从射击点 $j$ 射向目标 $i$ 的，把路径上的障碍一一列出。

则枚举一个障碍 $x$，使用另一个射击点 $y$ 把这个障碍击中。

则我们称从 $y$ 射击击中障碍的“目的”是为了给 $j \to i$ “清障”，然后连一条从 $y$ 到 $j$ 的有向边。

从 $y$ 射向 $x$ 的路径上可能还有障碍，这样下去把所有的“目的”链连出来。

容易发现“目的”关系连成了一棵 DAG（这是因为某一次“清障”可能会让两个或更多的未来的射击受益）。

但是如果我们为目标排个序，优先考虑优先级更大的目标，则这个 DAG 可以看成一棵有序树。

也就是说同一个节点下的子树，排在前面的子树可以影响排在后面的（前面的“清障”会对未来产生影响）。

那么我们枚举这棵树的 DFS 序，然后每次令 DFS 序的第一个数击中要求目标，然后递归考虑障碍即可。

递归层数最多为 $k$ 层，所以时间复杂度为 $\mathcal O (n \cdot k! \cdot k)$。

要注意的是障碍的判断，如果用极角序排序的话要注意精度，我使用 `double` 和 `atan2` 被出题人卡精度了。

时间复杂度为 $\mathcal O (n \cdot k! \cdot k)$，[评测链接](https://codeforces.com/contest/698/submission/72421569)。

---

## 作者：PNNNN (赞：3)

### 思路：

#### step 1.
注意数据范围
> $k \le 7$，$n \le 10^3$ 

看到 $k$ 十分小，考虑枚举射箭的顺序。

#### step 2.
对于怪物 $x$ 能否被射中，我们枚举射箭的顺序，看能否射中。对于一个射箭的顺序 $a_1,a_2, \dots a_n$，我们钦定 $a_1$ 为最终射中 $x$ 的人。假设 $a_1$ 与 $x$ 的这条线段中存在其他的怪物，则需将这些怪物也全部射中。而这些怪物要想被射中可能也需先射中另外一些怪物。因此考虑递归，并按照当前枚举的顺序射箭即可。
```cpp
inline bool shoot(int now){//注意这个函数的时间复杂度最高为O(k)
	cur++;int res=1;//cur表示当前枚举的顺序中已经到第cur个人射箭了，也就是lst[cur]
	if(cur>k)return false;//若需要射箭的人大于k个则当前的射箭顺序不合法
	for(int nxt:to[lst[cur]][now]){
		if(vis[nxt])continue;//注意要给已经被射中的怪物打上标记，避免被重复射中
		tmp.push_back(nxt),vis[nxt]=1,res&=shoot(nxt);//先射中当前射箭的人与要被射的怪物之间的怪物
		if(!res)return false;
	}return res;
}

inline bool check(int id){//枚举射箭的顺序，now表示当前已经枚举完了第now个射箭的人
	if(now==k){
		for(int i:tmp)vis[i]=0;//注意不能直接memset清空，时间会超限
		tmp.clear(),cur=0;return shoot(id);
	}int res=0;
	for(int i=1;i<=k;i++){
		if(v[i])continue;
		v[i]=1,lst[++now]=i;//lst存射箭的顺序
		res|=check(id),v[i]=0,now--;
	}return res;
}
```
时间复杂度为 $O(k \times k!)$

#### step 3.
可以将一个人想要射中一个怪物时需要先射中的怪物提前预处理出来，降低递归的时间复杂度。可以进行 $O(k \times n^2)$ 的枚举。

```cpp
inline bool rana(point A,point B,point C){//判断C在不在线段AB上
	if(A.x>B.x)swap(A,B);
	if(!(C.x>=A.x&&C.x<=B.x))return false;
	if(A.x==B.x){//这种情况需要特判
		if(A.y>B.y)swap(A,B);return A.y<=C.y&&C.y<=B.y;
	}else{
		return (A.y-B.y)*(A.x-C.x)==(A.y-C.y)*(A.x-B.x);//判断斜率是否相等，为了避免精度缺失所以使用了乘法
	}
}

for(int i=1;i<=k;i++){
	for(int j=1;j<=n;j++){
		for(int p=1;p<=n;p++){
			if(j==p)continue;
			if(rana(a[i],b[j],b[p])){
				to[i][j].push_back(p);
			}
		}
	}
}
```

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int k,n,ans,v[15],vis[1005],lst[15],now,cur;

vector <int> to[15][1005],tmp;

struct point{int x,y;};

point a[15],b[1005];

inline bool rana(point A,point B,point C){
	if(A.x>B.x)swap(A,B);
	if(!(C.x>=A.x&&C.x<=B.x))return false;
	if(A.x==B.x){
		if(A.y>B.y)swap(A,B);return A.y<=C.y&&C.y<=B.y;
	}else{
		return (A.y-B.y)*(A.x-C.x)==(A.y-C.y)*(A.x-B.x);
	}
}

inline bool shoot(int now){//注意这个函数的时间复杂度最高为O(k)
	cur++;int res=1;//cur表示当前枚举的顺序中已经到第cur个人射箭了，也就是lst[cur]
	if(cur>k)return false;//若需要射箭的人大于k个则当前的射箭顺序不合法
	for(int nxt:to[lst[cur]][now]){
		if(vis[nxt])continue;//注意要给已经被射中的怪物打上标记，避免被重复射中
		tmp.push_back(nxt),vis[nxt]=1,res&=shoot(nxt);//要先射中处于当前射箭的人与要被射的怪物的线段上的怪物
		if(!res)return false;
	}return res;
}

inline bool check(int id){//枚举射箭的顺序，now表示当前已经枚举完了第now个射箭的人
	if(now==k){
		for(int i:tmp)vis[i]=0;//注意不能直接memset清空，时间会超限
		tmp.clear(),cur=0;return shoot(id);
	}int res=0;
	for(int i=1;i<=k;i++){
		if(v[i])continue;
		v[i]=1,lst[++now]=i;//lst存射箭的顺序
		res|=check(id),v[i]=0,now--;
	}return res;
}

inline int read(){
	register int x(0),t(0);
	static char ch=getchar();
	while(!isdigit(ch)){t|=(ch=='-'),ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return t?-x:x;
}

signed main(){
	k=read(),n=read();
	for(int i=1;i<=k;i++){
		a[i]={read(),read()};
	}
	for(int i=1;i<=n;i++){
		b[i]={read(),read()};
	}
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n;j++){
			for(int p=1;p<=n;p++){
				if(j==p)continue;
				if(rana(a[i],b[j],b[p])){
					to[i][j].push_back(p);
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		ans+=check(i);
	}
	cout<<ans;
	return 0;
}
```
总时间复杂度为 $O(n \times k \times k!)$

---

## 作者：TheShuMo (赞：1)

## Limak and Shooting Points
#### 题面

- 平面上有 $k$ 个人和 $n$ 个怪物，每个人手中有一支箭。
- 每支箭可以往任意方向射出，击中这个方向上的第一个怪物后，箭和怪物都会消失。
- 问有多少怪物可能会被击中。
- $k \le 7$，$n \le 10^3$。
#### 分析
说实话这道题挺建议去看英文题面的，题目里给了一个 `order`，即顺序，这个就是这道题的关键所在。

由于 $k \le 7$，$n \le 10^3$ 的数据范围。启发我们寻找复杂度较高的算法来解决。
	问有多少怪物可能会被击中。
要解决这个问题，也就是对于每个怪物，检验以最优策略按顺序传送后去打击它，能否打中。找到最优策略是一个非常复杂？的问题，但是在时间范围内，我们可以枚举传送的顺序 $O(k!)$，最大不超过 $5040$。然后对于一个怪物根据这个顺序进行 `check`。

有了这个思路，`check` 其实就不难写了，设枚举出来的顺序为 $l$，$l_i$ 为第 $i,i\in [1,k]$ 个，钦定 $l_1$ 为对当前的目标 `goal` 打出最后一枪的传送石，那么预处理出每个石头的位置到每个怪物中间的障碍“”点，其它传送石的目标就是打掉这些障碍怪物。那么递归下去，对第 $i$ 个传送石到目标点中的障碍，用 $i+1$ 到 $i+x$ 来清理，再用 $i+x+1$ 来清理剩下的……
`check` 代码大致如下。
```cpp
bool chek(int to){
    if(tot == k) return false;
    int x = l[++tot];
    for(auto v : a[x][to]){
        if(vis[v.id]) continue;
        vis[v.id] = 1;
        bool as = chek(v.id);
        if(!as) return false;
    }return true;
}
```
整体只需要加上预处理 `a` 数组和枚举顺序即可。其中 `a[x][to]` 表示第 $x$ 个传送石到第 $to$ 个点的障碍点数目，预处理 $O(kn^2)$，总时间复杂度 $O(k!nk+kn^2)$，能过。
#### 代码
```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int _ = 1020;
struct Node{int x,y,id;};
struct Line{int k,b;};
vector<Node> a[8][_];
Node p[_],_k[20];
bool online(Node p1, Node p2, Node p3){
    if(((p3.y - p1.y)*(p2.x-p1.x) == (p2.y-p1.y)*(p3.x-p1.x)) and 
    ((((p2.x >= p1.x and p2.x <= p3.x and p2.y >= p1.y and p2.y <= p3.y) 
    || (p2.x <= p1.x and p2.x >= p3.x and p2.y <= p1.y and p2.y >= p3.y))
    || (p2.x <= p1.x and p2.x >= p3.x and p2.y >= p1.y and p2.y <= p3.y))
    || (p2.x >= p1.x and p2.x <= p3.x and p2.y <= p1.y and p2.y >= p3.y))){
        return 1;
    }return 0;
}
bool pd(Node a, Node b){
    if(a.x < b.x) return 1;
    return 0;
}bool cmp1(Node a, Node b){
    return a.x < b.x;
}bool cmp2(Node a, Node b){
    return a.x > b.x;
}
int vis[_];
int k, n, tot, to;
int sx[10], l[10];
void cl(){
    for(int i = 1; i <= k; i++) l[i] = i;
}
bool chek(int to){
    if(tot == k) return false;
    int x = l[++tot];
    for(auto v : a[x][to]){
        if(vis[v.id]) continue;
        vis[v.id] = 1;
        bool as = chek(v.id);
        if(!as) return false;
    }return true;
}
int main(){
    cin >> k >> n;
    for(int i = 1; i <= k; i++)cin >> _k[i].x >> _k[i].y;
    for(int i = 1; i <= n; i++)cin >> p[i].x >> p[i].y,p[i].id = i;
    for(int i = 1; i <= k; i++)
        for(int j = 1; j <= n; j++){
            for(int l = 1; l <= n; l++){
                if(l == j)continue;
                if(online(_k[i],p[l],p[j])){
                    a[i][j].pb(p[l]);
                }
            }
        }
    for(int i = 1; i <= k; i++)
        for(int j = 1; j <= n; j++){
            if(pd(_k[i],p[j]) and !a[i][j].empty()){
                sort(a[i][j].begin(),a[i][j].end(),cmp1);
            }else if(!a[i][j].empty()){
                sort(a[i][j].begin(),a[i][j].end(),cmp2);
            }
        }
    int ans = 0;
    for(int i = 1; i <= n; i++){
        tot = 0;cl();
        do{
            tot = 0;
            memset(vis,0,sizeof vis);
            vis[i] = 1;
            if(chek(i)) {ans ++; break;}
        }while(next_permutation(l+1,l+1+k));
    }
    cout << ans << endl;
}
```

---

## 作者：VenusM1nT (赞：1)

非常有趣的一道题。因为题面问的是多少怪“可能”被击中，所以只需要对于每个怪分别考虑它可不可能被击中就好了。假定当前考虑第 $b_1$ 个怪，第 $a_1$ 个人击杀了这个怪，但 $a_1\to b_1$ 的路径上可能有若干个怪，比如有 $b_2$ 怪，那么就需要其他人来杀死这个怪，假定 $a_2$ 击杀了 $b_2$，但 $a_2\to b_2$ 的路径上可能有 $b_3$ 怪，那么就需要 $a_3$ 来击杀这个怪……以此类推无限~~套娃~~递推，跑个 Dfs 就可以了。排列方式 $k!$ 种，分别 $k$ 个人，$n$ 个怪，复杂度 $\text{O}(k!\times nk)$。  
以上是主做法，这里提一嘴怎么判断 $a_i \to b_j$ 打不打得到，考虑两个怪 $B=(x_1,y_1),C=(x_2,y_2)$，一个人 $A=(x_3,y_3)$，假设 $A\to B$，无脑做法就是计算斜率 $k=\frac{\Delta y}{\Delta x}$ 然后列方程，但其实还有一种方法，考虑向量 $\overrightarrow{AB},\overrightarrow{AC}$，若有 $\overrightarrow{AB}\times\overrightarrow{AC}=0$，则 $A,B,C$ 共线，此时还有一种可能就是 $C$ 不在 $A,B$ 之间，于是考虑向量 $\overrightarrow{CA},\overrightarrow{CB}$，若 $\overrightarrow{CA}\cdot\overrightarrow{CB}<0$，此时 $\theta=\pi$，$C$ 必然在 $A,B$ 之间。这样做避免了精度损失而且简洁。
```cpp
#include<bits/stdc++.h>
#define N 1000
#define K 7
#define reg register
#define inl inline
#define int long long
using namespace std;
struct Vec
{
	int x,y;
	friend Vec operator - (const Vec &a,const Vec &b)
	{
		return ((Vec){a.x-b.x,a.y-b.y});
	}
	friend int operator * (const Vec &a,const Vec &b)
	{
		return a.x*b.x+a.y*b.y;
	}
	friend int operator ^ (const Vec &a,const Vec &b)
	{
		return a.x*b.y-a.y*b.x;
	}
}a[K+5],b[N+5];
vector <int> t[K+5][N+5];
int k,n,idx,tot,id[K+5],c[N+5];
bool vis[K+5];
inl bool Check(reg int x)
{
	if((++tot)>k) return 0;
	if(t[id[tot]][x].empty())
	{
		c[x]=idx;
		return 1;
	}
	reg int tmp=tot;
	for(auto v : t[id[tmp]][x])
	{
		if(c[v]!=idx)
		{
			if(!Check(v)) return 0;
		}
	}
	c[x]=idx;
	return 1;
}
bool Dfs(reg int u,reg int v)
{
	if(u>k)
	{
		idx++;
		tot=0;
		return Check(v);
	}
	for(reg int i=1;i<=k;i++)
	{
		if(!vis[i])
		{
			vis[i]=1;
			id[u]=i;
			if(Dfs(u+1,v)) return 1;
			vis[i]=0;
		}
	}
	return 0;
}
signed main()
{
	scanf("%lld %lld",&k,&n);
	for(reg int i=1;i<=k;i++) scanf("%lld %lld",&a[i].x,&a[i].y);
	for(reg int i=1;i<=n;i++) scanf("%lld %lld",&b[i].x,&b[i].y);
	for(reg int i=1;i<=k;i++)
	{
		for(reg int j=1;j<=n;j++)
		{
			for(reg int l=1;l<=n;l++)
			{
				if(j==l) continue;
				if(!((a[i]-b[j])^(b[l]-b[j])) && (a[i]-b[j])*(b[l]-b[j])<0) t[i][l].push_back(j);
			}
		}
	}
	reg int ans=0;
	for(reg int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		if(Dfs(1,i)) ans++;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

