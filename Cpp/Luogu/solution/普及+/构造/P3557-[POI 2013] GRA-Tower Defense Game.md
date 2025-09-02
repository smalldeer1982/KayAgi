# [POI 2013] GRA-Tower Defense Game

## 题目描述

Bytie is playing the computer game Tower Defense.

His aim is to construct guard towers, so that they protect all of his domain.

There are multiple towns in Bytie's domain, some of which are linked by  bidirectional roads.

If Bytie erects a guard tower in a city, then the tower protects its city and  all the cities directly linked with it by roads.

Just as Bytie was pondering over the placement of guard towers in his domain,  his elder sister Bytea entered the room.  She glanced at the map displayed on  the screen, and after a moment exclaimed:

"Oi, what is there to think about, clearly $k$ towers suffice!".

Angered by his sister spoiling the fun, Bytie showed his sister the door,  and began wondering what to do next.

Pride will not let him construct more than $k$ towers.

He has an up his sleeve though:

he can research a technology that will allow him to construct improved guard towers.

An improved guard tower protects not only the town it was erected in and its  immediate neighbors but also the towns that are further away.

Formally, an improved guard tower built in the town $u$ protects the town $v$ if either of the following holds:

- $u=v$;

- there is a direct road from $u$ to $v$;

- or there is such a town $w$ that there are direct roads from $u$ to $w$ and from $w$ to $v$.

Of course, Bytie still strives to erect at most $k$ towers,  but he has no qualms about making these the improved guard towers.

有一个n个点m条边的图，每条边距离是1，已知用k个攻击距离为1的塔可以打到整个地图，让构造一个方案使得用小于等于k个攻击距离为2的塔打到整个地图


## 说明/提示

有一个n个点m条边的图，每条边距离是1，已知用k个攻击距离为1的塔可以打到整个地图，让构造一个方案使得用小于等于k个攻击距离为2的塔打到整个地图


## 样例 #1

### 输入

```
9 8 3
1 2
2 3
3 4
1 4
3 5
4 6
7 8
8 9
```

### 输出

```
3
1 5 7 
```

# 题解

## 作者：EXODUS (赞：14)

# Part 1：前言
感觉最近做构造题做上瘾了。/kk

# Part 2：正文
## 题目存在，开始思考。
看一眼题面，~~立刻想到暴力搜索~~。

>数据范围 $n\leq 5\times 10^5,m\leq 10^6$

这似乎提示我们这题有特殊性质使得可以 $O(n)$ 解决问题。

接下来我们把“打到”称为覆盖到，一个点如果能被打到，则说这个点是“被覆盖”的，且 $dis(x,y)$ 表示 $(x,y)$ 间的最短路。

~~随手画几个例子手模 / 看一眼样例~~ 仔细观察似乎可以发现，选择任何未被覆盖一个点向外拓展，覆盖离它距离不超过 $2$ 的点，然后再次重复上述过程，直到所有点都被覆盖一定是一组可行解。

比如对于样例，有如下解释：

第一次选择点 $1$，$1$ 号点未被覆盖，开始向外拓展，拓展到 $2,3,4,6$。

第二次选择点 $5$，无事发生。

第三次选择点 $7$，拓展到 $8,9$。

此时所有点都被覆盖，程序结束，答案也就是样例里的 $1,5,7$。

## 理论存在，证明开始。

首先考虑我们每次放下的塔在哪个地方。

我们设一开始在用攻击距离为 $1$ 的塔覆盖全图时覆盖的点的位置是 $p_1,p_2,p_3,...,p_k$ ， 当前选的点是 $x$ 。

如果 $x$ 存在于 $p_1,p_2,...,p_k$ 中，那么一定不比原方案劣（即选的塔数不会更多），因为覆盖距离变大了。

如果 $x$ 不存在于 $p_1,p_2,...,p_k$ 中，那么此时一定存在一个 $i$，满足 $dis(p_i,x)=1$，那么我们视作在离 $x$ 距离为 $1$ 的位置上都放上一个覆盖距离为 $1$ 的塔，此时也一定不比原方案劣，因为放下的“塔数”变多了。

由于我们每次建塔的位置 $x$ 都与所有已经建塔的位置 $t1,t2,...,t_l$ 满足 $\min(dis(x,t1),dis(x,t2),...,dis(x,t_l))\ge 2$，所以每个新建的塔至少会覆盖到一座原来存在于 $p_1,p_2,...,p_k$ 的塔，即一定不需要超过 $k$ 座塔就能覆盖到所有的 $p_i$ 。

综上，~~塔可以随便放在一个没有被覆盖到地方~~ 结论成立。
## 结论成立，实践开始
开写代码。

# Part 3：代码
```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
typedef long long ll;
il int read(){
	int ans=0,flag=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flag=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flag;
}
const int N=5e5+7,M=1e6+7;
struct edge{
	int to,nxt;
}e[M<<1];
int head[N];
int cnt;
int n,m,k;

void add_edge(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}

int tot;
int ans[N];
bool vis[N];

void dfs(int now,int stp){
	//printf("(%d,%d)\n",now,stp);
	vis[now]=1;
	if(stp==2)return;
	for(int i=head[now];i;i=e[i].nxt){
		dfs(e[i].to,stp+1);
	}
}

int main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add_edge(u,v);
		add_edge(v,u);
	}
	//for(int i=1;i<=2*m;i++){
	//	printf("%d %d\n",e[i].to,e[i].nxt);
	//}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			ans[++tot]=i;
			dfs(i,0);
		}
	}
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++){
		printf("%d ",ans[i]);
	}
	return 0;
}
```
# Part 4：后文
做完这道题，真的想了很久。

用最大胆的思考和最严谨的证明，以及几乎是最简洁的代码做出一道题，也许就是构造题的魅力所在，也许就是我们如此沉迷于构造题和思维题的原因。

点赞再走呗（破坏氛围，逃~

---

## 作者：CG__HeavenHealer (赞：5)

前几天上课讲的一道~~乱搞~~构造题，借此总结一下

其实说构造题乱搞毫不过分，有的时候自己都不相信自己的结论竟然是对的，可是它就是正解。所以，做 OI 题要开阔思路，不要思维定势。

就像这道题：在乱搞之前大家的想法应该会很复杂，像什么树形DP、贪心、二分可能都想一遍——毕竟这可是道蓝题。然而，这道题的解法简单的不能再简单——

### 解法

结论：**只要先随便定一个点，往外扩展，被扩展到的点不再放箭塔，就是一组解**

证明：先证存在性：我们假设不存在一种合法方案，那么就说明即使一共有 $k$ 个攻击范围为 $2$ 的箭塔，且它们很分散（没有箭塔在其他箭塔的覆盖范围），覆盖范围最大，也无法覆盖整张图。由上面的限制可知这几个塔的分布一定是最优状态（覆盖面积尽可能广）。所以对应的原覆盖方案一定也是最优的。但在最优情况下，射程为 $2$ 的箭塔都不能全覆盖，射程为 $1$ 的箭塔就更不能了，与题干描述的升级之前一定存在合法方案矛盾，所以一定存在合法方案。

而为什么随便选点就行了呢？

由题中描述可知，每个点只有两种状态：被覆盖或这个点就是箭塔。如果这个点是箭塔，它还放箭塔的话一定不会比原方案劣：因为能覆盖的点一定大于等于原来覆盖的；而如果它是被覆盖的点的话，与它距离为 $1$ 的点一定有一座箭塔，这个点放箭塔也能覆盖到原来箭塔的覆盖范围。

综上，结论成立。

看到这，屏幕前的您可能会大喊：~~这也算蓝题？？！！~~

可是话又说回来，又有几个人艺高人胆大，敢于尝试呢？

代码实现很简单，直接DFS遍历即可。

### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ri register int
const int N = 1e6 + 10;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-') f = -1;
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return f * x;
}
struct Edge {
    int to, nxt;
} e[N << 1];
int head[N], cnt;
inline void add(int u, int v) {
    e[++cnt].to = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
bool vis[N];
vector<int> ans;
void dfs(int u, int fa, int dep) {
    vis[u] = true;
    if (dep >= 2) return;
    for (ri i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == fa) continue;
        dfs(v, u, dep + 1);
    }
}
signed main() {
    int n = read(), m = read(), k = read();
    while (m--) {
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
    for (ri i = 1; i <= n; i++) {
        if (vis[i]) continue;
        dfs(i, 0, 0);
        ans.push_back(i);
    }
    printf("%lld\n", ans.size());
    for (ri i = 0; i < ans.size(); i++) printf("%lld ", ans[i]);
    return 0;
}
```



---

## 作者：违规用户名U56916 (赞：4)

这题我觉得思路很奇特

感觉这题很奇怪（这个k是个什么玩意~~好像没有用~~）

仔细想想，其实题目对这个图已经有了约束

即每个点距离为**1**的点中肯定有一个之前题目所提到的攻击距离为**1**的塔

就保证了我们不断去枚举没有被攻击到的点（新的塔中）就可以得到正确的答案（可以仔细想想）

然后注意到这个

![](https://cdn.luogu.com.cn/upload/pic/40601.png)

special judge太棒了

所以这只是一个枚举题

AC代码

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
int fr[500010],to[2000010],nex[2000010],tl;
void add(int x,int y){
    to[++tl]=y;nex[tl]=fr[x];fr[x]=tl;
}
bool vis[500010];
int ans[500010];
int n,m,k,x,y;
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        add(x,y);add(y,x);
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            ans[++ans[0]]=i;
            vis[i]=true;
            for(int j=fr[i];j;j=nex[j]){
                vis[to[j]]=true;
                for(int k=fr[to[j]];k;k=nex[k]) vis[to[k]]=true;
            }
        }
    }
    printf("%d\n",ans[0]);
    for(int i=1;i<=ans[0];i++) printf("%d ",ans[i]);
    return 0;
}
```

我见证了这道题由灰变黄，我的灰题AC啊( ⊙ o ⊙ )啊！

---

## 作者：Alex_Wei (赞：3)

> *[P3557 [POI2013]GRA-Tower Defense Game](https://www.luogu.com.cn/problem/P3557)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

挺有意思的一道题目。考虑枚举每个点，如果没有被覆盖，那就直接在这个地方建座塔，然后把所有覆盖到的点删掉。正确性是因为存在大小小于 $k$ 的点覆盖集，因此每个点至少与一个点覆盖集中的点相连，在每个点建塔都能覆盖到与所有与该点相连的点覆盖集中的点所能覆盖的点，故贪心正确。

同时，一个点最多仅会作为一次与某座塔距离为 $1$ 的点（因为在此之后所有相邻点都被打上了标记，自然不会再作为塔），遍历其所有出边打标记。故时间复杂度线性。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read() {
	int x = 0; char s = getchar();
	while(!isdigit(s)) s = getchar();
	while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
	return x;
}

const int N = 1e6 + 5;
int n, m, k, ans, id[N], vis[N], cnt, hd[N], nxt[N << 1], to[N << 1];
void add(int u, int v) {nxt[++cnt] = hd[u], hd[u] = cnt, to[cnt] = v;}
int main() {
	cin >> n >> m >> k;
	for(int i = 1, u, v; i <= m; i++) add(u = read(), v = read()), add(v, u);
	for(int i = 1; i <= n; i++) if(!vis[i]) {
		id[++ans] = i, vis[i] = 1;
		for(int j = hd[i]; j; j = nxt[j]) {
			vis[to[j]] = 1;
			for(int k = hd[to[j]]; k; k = nxt[k]) vis[to[k]] = 1;
		}
	} cout << ans << endl;
	for(int i = 1; i <= ans; i++) cout << id[i] << " ";
	return 0;
}
```

---

## 作者：Katsura_Hinagiku (赞：2)

因为原图保证k个攻击距离为1的箭塔可以覆盖，所以使用攻击距离为2的箭塔时，只需要在不在攻击范围内的点建立箭塔就可以了

O - O - O

三个点连成的一条链，使用攻击距离为1的箭塔时，需要将箭塔建立在中间的点上，但使用攻击距离为2的箭塔时，放在左右也可以

（~~意会一下就是这种感觉~~）
```cpp
#include<bits/stdc++.h>
using namespace std;
int head[500005],pnt[2000005],nxt[2000005],E=0;//前向星建图，边权为1，就不用记录了 
bool vis[500005];//能否被攻击到 
int n,m,k,cnt=0;
int ans[500005];//记录答案 
void add_edge(int a,int b)
{
	pnt[E]=b;
	nxt[E]=head[a];
	head[a]=E++;
}
void init()
{
	memset(head,-1,sizeof(head));
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
}
void solve()
{
	for(int i=1;i<=n;++i)
	{
		if(!vis[i])//不在攻击范围内，就建一个新箭塔 
		{
			vis[i]=1;
			ans[++cnt]=i;
			for(int j=head[i];j!=-1;j=nxt[j])
			{
				int v=pnt[j];
				vis[v]=1;
				for(int k=head[v];k!=-1;k=nxt[k])
				{
					int vv=pnt[k];
					vis[vv]=1;
				}
			}//标记在攻击范围内的点 
		}
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;++i)
	{
		printf("%d ",ans[i]);
	}
}
int main()
{
	init();
	solve();
	return 0;
}
```

~~所以为什么是蓝题~~

---

## 作者：kczno1 (赞：2)

关键是原来可以用距离为1的打完，现在改成用距离为2的，变成了两倍。

于是我们只要选择了一个没有被打到的点，那么他距离1之内一定有个老的塔。选择他之后，他的范围就包括了老的范围。

不断选择更新即可。


---

## 作者：ycy1124 (赞：1)

### 题意
很清楚，这里不多讲。
### 思路
首先发现，对于所有炮台攻击距离为一的方案中，每一个炮台一定会有一个距离它小于等于 $2$ 的另一个炮台。根据这个，进一步推出每个点要么是炮台，要么旁边距离为一的点中有一个炮台。

接下来考虑攻击距离为 $2$ 的炮台。你会发现在一个点放置一个攻击距离为 $2$ 的炮台就等同于在所有距离它小于等于 $1$ 的点上放置一个攻击距离为 $1$ 的炮台。于是我们每次选择一个不能被打到的点，根据前面的结论，在他小于等于 $1$ 的某个点要有一个攻击距离为 $1$ 的炮台，而我们这个操作一定可以使那个点等价于放了一个攻击距离为 $1$ 的炮台，所以最终一定能打到所有的点。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>ans,a[500005];
int n,m,k;
bool bj[500005];
inline void dfs(int p,int f,int w){
    bj[p]=1;
    if(w==2){
        return;
    }
    for(auto it:a[p]){
        if(it==f){
            continue;
        }
        dfs(it,p,w+1);
    }
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(!bj[i]){
            ans.push_back(i);
            dfs(i,0,0);
        }
    }
    cout<<ans.size()<<'\n';
    for(auto it:ans){
        cout<<it<<' ';
    }
    return 0;
}
```
[AC 记录。](https://www.luogu.com.cn/record/198750592)

---

## 作者：moosssi (赞：1)

这道题其实思路很简单，直接枚举每个点，判断当前点是否已被覆盖，若没有，则选定当前节点，更新答案，并把与距当前点距离小于等于 $2$ 的点打上标记表示可以到达。

原理大概是，对于每个点，因为满足距离小于等于 $1$ 的情况，那么一个点，在

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int head[N],ver[N*2],net[N*2],tot;
int n,m,k,ans[N],cnt;
bool vis[N],st[N][3];
void add(int a,int b){
	net[++tot]=head[a];
	head[a]=tot;
	ver[tot]=b;
}
void dfs(int x,int fa,int deep){
	st[x][deep]=1;//类似记搜的优化，除去多余的遍历，不加会T一个点 
	vis[x]=1;
	for(int i=head[x];i;i=net[i]){
		int v=ver[i];
		if(v==fa)continue;
		if(st[v][deep+1])continue;
		if(deep<=1)dfs(v,x,deep+1);//只递归两层 
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		add(b,a);
		add(a,b);
	}
	for(int i=1;i<=n;i++){
		if(vis[i])continue;//已经被标记，直接跳过 
		dfs(i,0,0);//标记与之距离小于等于二的点 
		ans[++cnt]=i;
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++){
		printf("%d ",ans[i]);
	}
	return 0;
}
```
第一种情况时，要么被选，要么相邻的一个点被选，那么在第二种情况下，选中当前点，不论这个点在第一种情况时是前者还是后者，都可以达到之前的效果，并且更优，所以可以直接枚举，不用考虑 $k$ 。



---

## 作者：DYYqwq (赞：0)

暴力。若这个点还没有覆盖，就放置一个塔，否则就继续枚举。

这必然是对的。因为题目给的 $k$ 是攻击范围为 $1$ 的，他都能覆盖完整，于是攻击范围更广的也必然可以。

分析一下时间复杂度，发现每个点只会被经历 $O(1)$ 次，于是总共时间复杂度为 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int to , nxt;
}e[1000010];
int n , m , k , tot , head[500010] , cnt = 0 , ans[500010];
bool flag[500010];
void add(int u , int v)
{
	++ tot;
	e[tot].to = v;
	e[tot].nxt = head[u];
	head[u] = tot;
}
void dfs(int u , int num)
{
	flag[u] = 1;
	if(num == 2) return;
	for(int i = head[u] ; i != 0 ; i = e[i].nxt)
	{
		int v = e[i].to;
		dfs(v , num + 1);
	}
}
int main()
{
	scanf("%d%d%d" , &n , &m , &k);
	for(int i = 1 , u , v ; i <= m ; i ++)
	{
		scanf("%d%d" , &u , &v);
		add(u , v) , add(v , u);
	}
	for(int i = 1 ; i <= n ; i ++)
	{
		if(flag[i]) continue;
		dfs(i , 0);
		ans[++ cnt] = i;
	}
	printf("%d\n" , cnt);
	for(int i = 1 ; i <= cnt ; i ++) printf("%d " , ans[i]);
	return 0;
}
```

---

## 作者：Melo_DDD (赞：0)

挺有意思的题。

第一感觉可能是直接去找原图中的 $k$ 个攻击距离为 $1$ 的塔然后直接输出即可。是正确的，但是我不会。

考虑将原图中所有的点分类讨论。显然分为放了塔的和没有放塔的，其中没有放塔的可以发现一定和最近的塔的距离只有 $1$。

考虑把攻击距离为 $2$ 的塔放在这两类点上分别会发生什么。如果原先这个点已经放了塔，可以发现他的覆盖面积在升级之后一定会变大。对于如果没有放塔，仍然可以看出，原来距离他最近的那个塔覆盖的所有的点他仍然能够覆盖。

可以发现，我们无论把塔放在那里，和原来相比一定不劣。于是我们每次找到一个**没有被覆盖**的点，放上升级之后的塔即可。

每次更新被覆盖的点，带上剪枝更靠谱。

### code


```cpp
int main () {
	read (n ,m ,k) ;
	f (i ,1 ,m ,1) {
		int a ,b ; read (a ,b) ;
		add (a ,b) ,add (b ,a) ;
	}

	f (i ,1 ,n ,1) 
		if (! vis[i])
			ans.emplace_back (i) ,dfs (i ,0 ,0) ;

	std :: cout << ans.size () << '\n' ;

	for (auto i : ans) 
		std :: cout << i <<  ' ' ; puts ("") ;
	return 0 ;
}

inline void dfs (int cur ,int fa ,int dis) {
	vis[cur] = hr[cur][dis] = true ; // 如果当前点 dis 相同的时候已经被遍历到，之后遍历的点一定会和之前完全相同，不需要再遍历
	if (dis == 2) return ;
	for (int i = head[cur] ; i ; i = e[i].nxt) {
		int nex = e[i].to ;
		if (hr[nex][dis + 1] || nex == fa) continue ;
		dfs (nex ,cur ,dis + 1) ;
	}
}
```

---

## 作者：Purslane (赞：0)

# Solution

每次取出一个没有被覆盖的点，在上面放上防御塔即可。

如果存在一种方案放了 $k+1$ 及以上个防御塔，显然最小点覆盖会大于 $k$，矛盾。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e5+10;
int n,m,k,cov[MAXN];
vector<int> G[MAXN],ans;
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	ffor(i,1,m) {
		int u,v;
		cin>>u>>v,G[u].push_back(v),G[v].push_back(u);	
	}
	ffor(i,1,n) if(!cov[i]) {
		ans.push_back(i),cov[i]=1;
		for(auto v:G[i]) if(cov[v]!=1) {
			cov[v]=1;
			for(auto w:G[v]) cov[w]=2;
		}
	}
	cout<<ans.size()<<'\n';
	for(auto id:ans) cout<<id<<' ';
	return 0;
}
```

---

## 作者：syr1125 (赞：0)

## -0x3f 扯淡
蛮喜欢这道题的。

求管理员打回的话留个姓名，方便沟通。
## 0x01 分析
先分析题目：

意思已经很清楚了，不解释。

第一眼看到这道题，想到的就是：因为不需要最优，所以说直接求出范围为 $1$ 的塔覆盖整张图的方案，那么将这些塔变成范围为 $2$ 的塔显然不会更劣，因为所有普通塔能覆盖到的地方，升级塔都能覆盖到。

然后我就被打脸了，我反正没有想到这样的一种解法，只好再去找其他思路。

我们观察样例，发现这个样例中的方案是这样构造的：

1. 先选择 $1$ 这个节点，把它选中，把所有能覆盖到的节点标记上，以后不选了
1. 按这样的顺序又选了 $5$，这时无事发生
1. 如法炮制，选择点 $7$，所有的点都被选中了，结束。

也就是说，这是一种通过每次选择编号最小的一个**未覆盖**节点进行覆盖操作，直到整张图被覆盖的构造方法。

这时我们就会有一个想法：这样的方式是不是正解的构造方式呢？~~是的~~

## 0x02 证明

先说明一件事，我们主角~~万能~~的姐姐说的话一定是对的，也就是说，$k$ 座普通塔已经够了。

现在，我们证明，按样例的方式构造一定是不劣于 $k$ 座普通塔的方案的。

那么首先，把升级塔放在原普通塔的位置一定是不劣的。（开头也讲过）

现在只需要考虑升级塔放在其他位置的情况了，可以发现，一定会有一个原方案中的普通塔覆盖这个位置（因为原来的方案已经覆盖了整个图），那么其实这种方案也是不劣的，参考下面这张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/ys3n3yb1.png)

没看懂的话也可以看文字解释：我们先找到原方案中覆盖升级塔的普通塔，我们以升级塔为中心做 dfs，那么第一步一定会走到原普通塔，那么此时再走一步肯定可以走到原普通塔能覆盖到的所有位置，所以这样的方案是不劣的。

## 0x03 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, k;
vector<int> a[500005], ans; // a用来存图（邻接表），ans用来存答案 
int vis[500005]; // 有没有被覆盖到 

void dfs(int now, int step)
{
	if (step == 2) return;
	for (int i = 0; i < a[now].size(); i ++)
	{
		/*
		这里是重点，我来解释一下。
		你肯定会问，为什么不加一行被遍历过的就不遍历。
		其实想一想就会发现，有时第一步被遍历过时，第二步没被遍历，所以说不能加，加了会喜提70。 
		*/ 
		vis[a[now][i]] = 1;
		dfs(a[now][i], step + 1);
	}
}

int main()
{
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i ++)
	{
		int x, y;
		cin >> x >> y;
		a[x].push_back(y), a[y].push_back(x); //双向边（如果用链式前向星记得双倍空间） 
	}
	
	for (int i = 1; i <= n; i ++)
	{
		if (!vis[i])
		{
			vis[i] = 1; //记得标记 
			dfs(i, 0);
			ans.push_back(i);
		}
	}
	
	cout << ans.size() << "\n";
	for (int i = 0; i < ans.size(); i ++) cout << ans[i] << " ";
	return 0;
}

```

---

## 作者：Helloworldwuyuze (赞：0)

# P3557 题解

## Des

给定一张无向图，其中有 $n$ 个点 $m$ 条边，保证存在一个长度为 $k$ 的序列 $p_k$ 使得标记 $p_k$ 即 $p_k$ 一步能够到达的地方之后，所有的点都被标记。现在要求标记两步之内能够到达的点，求一种构造的方法使得所有点被标记。

## Sol

首先摆出结论：

> 对于一张图，我们计 `vis[x]` 表示节点 $x$ 的标记情况。每一次更新的时候，我们找到一个 $x$ 使得 `vis[x]==false`，然后标记所有 $x$ 两步之内能够到达的点，最后统计一下我们进行了多少次操作即可。

下面我们来 **证明这个 ~~显而易见~~** 的结论：

首先，对于原图，我们知道，对于任意一个点 $x$，总存在 $i\in [1,k]$ 使得 $\operatorname{dis}(x,p_i)=1$ 或 $x=p_i$。

- 如果 $\operatorname{dis}(x,p_i)=1$，则我们在这里标记一定会在距离为 $1$ 的地方标记到 $p_i$，进而标记 $p_i$ 原来标记到的点。这样显然不劣。
- 如果 $x=p_i$，那么同样地，$x$ 可以标记到 $p_i$ 原来标记得到和一些原来标记不到的点，因此也是不劣的。

又，对于每一个新标记的点，至少会覆盖到一个 $p_i$ 使得之后不需要再标记。因此新的标记的点的数量总不超过 $k$。

于是我们就可以遍历 $1-n$，遇到没有标记的就标记一下。但是注意要遍历所有的两个距离之内能够到达的点，否则可能会因为标记卡住了而无法继续标记新的节点。

但这样复杂度为什么是对的呢？

我们考虑对于一个点标记点 $p_i$，之后 $p_i$ 和 $p_i$ 一步能够到达的点会遍历一次所有的边。而它们周围一步能够到达的点都已经都标记完了，下一次再遍历到它们一定是距离标记点 $2$ 时。这时就不需要再遍历它们的边了。因此，每个点的边只会被遍历一次，这就保证了复杂度的正确性。

## Code

```cpp
int n, m, k, st[N];
vector<int> ans, g[N];
bool vis[N];

void dfs(int x, int st){
	vis[x] = true;
	if(st == 2)	return ;
	for(int y:g[x])	dfs(y, st+1);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1,x,y;i<=m;++i)	cin>>x>>y, g[x].pb(y), g[y].pb(x);
	for(int i=1;i<=n;++i)
		if(!vis[i])	ans.pb(i), dfs(i, 0);
	cout<<ans.size()<<endl;
	for(int x:ans)	cout<<x<<" ";
	cout<<endl;
	return 0;
}
```

---

