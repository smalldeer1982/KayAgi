# 【MX-X8-T3】「TAOI-3」地地爱打卡

## 题目背景

原题链接：<https://oier.team/problems/X8D>。

---

一年前，我在 NOIP 2023 的赛场上，折戟沉沙。

一年后，我从倒下的地方爬起。

THUWC 2025 D1T1，强势狂砍 76 分。

……线段树优化 DP 也太难了。

## 题目描述

小 T 同学非常淡泊于跑步。为了让跑步更加无趣，他决定制作一款叫做《地地爱打卡》的软件，使得用户每地都无法进行跑步打卡。

开发完成后，小 T 同学计划进行试运行，他找了大 Y 同学来帮忙。

这次打卡总共有 $n$ 个节点，编号为 $1 \sim n$，有 $m$ 条连接两个节点的双向道路，**保证图无重边无自环**。大 Y 同学需要从 $s$ 跑到 $t$。

初始时，大 Y 同学的能量值是 $0$。每当大 Y 同学跑过一条道路，小 T 同学就会请他吃一顿饭，使得他的能量值增加 $1$。试运行期间他的**能量值不可以是负数**。

大 Y 同学还有一个快乐值，初始为 $0$，当位于某个节点的时候，大 Y 同学可以让他的快乐值按位异或上他的能量值，同时清空能量值（即，能量值变为 $0$），也可以什么都不做。

现在大 Y 同学想要知道，他是否能够 **最终停留在** 节点 $t$，耗尽所有能量值（即，能量值变为 $0$），并且此时他的快乐值恰好为 $x$？**注意：大 Y 同学到达节点 $\bm t$ 后可以选择不停下而继续移动。**

因为大 Y 同学很爱跑步，所以你要回答 $q$ 组询问，每次询问给出 $s, t, x$，你要告诉大 Y 同学是否能够满足他的要求。

## 说明/提示

**【样例解释 #1】**

![](https://cdn.luogu.com.cn/upload/image_hosting/66uc1bzt.png)

如图，对于第一组询问，大 Y 同学从节点 $1$ 出发，经过一条道路到达节点 $2$，此时他的能量值为 $1$。他再进行一次操作，此时能量值变为 $0$，快乐值变为 $1$，满足条件。

对于第二组询问，可以说明不存在合法的方案。

**【数据范围】**

**本题采用捆绑测试。**

- 子任务 1（22 分）：$\max(n, m, q, x) \leq 50$。
- 子任务 2（22 分）：$m = n - 1$ 且图连通。
- 子任务 3（24 分）：$x \leq 1$。
- 子任务 4（32 分）：无特殊限制。

对于所有数据，保证 $2 \leq n \leq 2\times 10^5$，$0 \leq m \leq 3\times 10^5$，$1 \leq q \leq 2\times 10^5$，$1 \leq s, t, u, v \leq n$，$0 \leq x \leq 10^9$，保证给出的无向图无重边无自环。

## 样例 #1

### 输入

```
7 6 4
2 4
5 6
1 2
3 5
3 6
7 1
1 2 1
1 6 3
5 3 5
2 7 7```

### 输出

```
tribool
expand
tribool
expand
```

## 样例 #2

### 输入

```
5 4 4
1 2
2 3
3 4
4 5
1 2 1
1 5 3
5 3 2
1 1 1
```

### 输出

```
tribool
expand
tribool
expand
```

# 题解

## 作者：szh_AK_all (赞：12)

~~特判有点恶心。~~

## 分析
结论：如果 $x$ 和路径长度的奇偶性相同或是在 $s,t$ 所在联通快中含有一个奇环则合法。

证明：因为可以在一条路上来回走，所以可以将快乐值凑到 $x$，由于一个数异或偶数个 $1$ 还是这个数本身，所以最终的能量值也可以凑到 $0$。又因为奇数长度的环可以改变路径长度的奇偶性，所以如果图中有奇环那么一定合法。

做两遍 dfs 即可，第一遍 dfs 判断连通性，第二遍 dfs 找奇环，注意特判孤立点。

```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int>g[200005];
int shu[200005], vis[200005], cnt;
int vi[200005], dis[200005], ji[200005];

void dfs(int x) {
	if (vis[x])
		return;
	vis[x] = 1;
	for (int y : g[x]) {
		shu[y] = cnt;
		dfs(y);
	}
}

void df(int x, int fa) {
	vi[x] = 1;
	for (int y : g[x]) {
		if (y == fa)
			continue;
		if (!vi[y])
			dis[y] = dis[x] + 1, df(y, x);
		else if (abs(dis[x] - dis[y]) % 2 == 0)
			ji[shu[x]] = 1;
	}
}

int main() {
	int n, m, q;
	cin >> n >> m >> q;
	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for (int i = 1; i <= n; i++)
		if (!vis[i])
			shu[i] = ++cnt, dfs(i), df(i, 0);
	while (q--) {
		int s, t, x;
		cin >> s >> t >> x;
		if (shu[s] != shu[t])
			cout << "expand";
		else if (s == t && g[s].size() == 0 && x != 0)
			cout << "expand";
		else {
			if (abs(dis[s] - dis[t]) % 2 == x % 2 || ji[shu[s]])
				cout << "tribool";
			else
				cout << "expand";
		}
		cout << "\n";
	}
}
```

---

## 作者：LinkCatTree (赞：5)

前言：赛后改了一下秒过，难受。

首先我们发现其实答案只与 $x$ 的奇偶性相关，因为只要在一条边上来回跑即可获得任意 $2$ 的正整数次幂的能量值，这样通过异或即可改变除了最低位以外的任意一位，使之于 $x$ 相同。

（接下来我们只考虑 $s$ 和 $t$ 连通的情况，否则显然 `expand`）

我们考虑 $x$ 对奇偶性的影响，显然当且仅当 $s$ 与 $t$ 之间存在一条路径使之边数与 $x$ 奇偶性相同时能够满足要求。那么问题变成了判断 $s$ 与 $t$ 之间是否存在奇数或偶数条边的路径。

我们可以对于图中（一个联通块内的）点进行 $01$ 标号，如果某个点的标号产生冲突说明该图内存在奇数条边的环，那么这样子我们就可以通过这个环产生任意奇偶性的路径。

> 具体构造方案：
>
> ![](https://cdn.luogu.com.cn/upload/image_hosting/f72riaoj.png)
>
> 首先肯定存在一条从 $s$ 到 $t$ 的路径（灰色），如果这条路径的奇偶性与 $x$ 相同那么没问题。
>
> 如果奇偶性不同，那么不妨先清空能量值，假设此时快乐值奇偶性为 $h$。接着从 $t$ 走到奇环上（黄色），再次清空能量值。然后绕着奇环跑一圈（黑色）、清空能量值，然后再重新跑回 $t$ 点（蓝色）、清空能量值，由于黄、蓝色路径其实是同一条，异或了两次就抵消了，此时快乐值奇偶性并变为 $h \oplus 1$，奇偶性变得与 $x$ 相同。

如果 $01$ 标号并未冲突，说明图中无奇环，$s$ 到 $t$ 的所有路径奇偶性都一致且可通过 $01$ 标号算出。我们再根据奇偶性与 $x$ 对比即可得到答案。

于是我们得到了[代码](https://www.luogu.com.cn/paste/2ok071da)。加上去发现怎么只有 46 分？

回去看我们的思考过程。注意到：“**因为只要在一条边上来回跑即可获得任意 $2$ 的正整数次幂的能量值**”。如果 $s$ 与 $t$ 相同且联通块内没有其它点怎么办？我们就没法通过在某条边上反复跑来改变高兴值。此时只要 $x$ 非零就无法满足要求。

经过修改（就加了四行），我们得到最终代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read() {
    int x=0,ch=getchar(),minus=0;
    for(;ch<'0'||ch>'9';ch=getchar()) minus|=(ch=='-');
    for(;ch>='0'&&ch<='9';ch=getchar()) x=x*10+(ch^48);
    return minus?-x:x;
}

typedef long long ll;
const int N=2e5+5;
int n,m,q,col[N],p[N],num;
vector<int> edge[N];
bool flag[N];

inline void dfs(int u) {
    col[u]=num;
    for(auto v:edge[u]) {
        if(!p[v]) p[v]=3-p[u];
        if(p[v]==p[u]) flag[num]=true;
        if(!col[v]) dfs(v);
    }
    return ;
}

int main() {
    n=read(),m=read(),q=read();
    while(m--) {
        int u=read(),v=read();
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for(int i=1;i<=n;i++)
        if(!col[i]) p[i]=1,++num,dfs(i);
    while(q--) {
        int s=read(),t=read(),x=read();
        if(col[s]!=col[t]) {
            printf("expand\n");
            continue ;
        }
        if(s==t&&x&&!edge[s].size()) { // 改动的地方
            printf("expand\n");
            continue ;
        }
        if((x&1)&&!flag[col[s]]&&p[s]==p[t]) {
            printf("expand\n");
            continue ;
        }
        if(!(x&1)&&!flag[col[s]]&&p[s]!=p[t]) {
            printf("expand\n");
            continue ;
        }
        printf("tribool\n");
    }
    return 0;
}
```

同时祝审核大大和各位读者们新春快乐。

---

## 作者：ty_mxzhn (赞：3)

天天爱打卡，地地爱打卡，人人爱打卡。

注意到你其实可以反复横跳，因为计算方式是异或所以除了最低位都能消去。

问题变成给你两个点问你两个点存不存在一条长度为奇数或偶数的路径。

考虑把一个点拆成两个点，然后形如 $(u,v)$ 的边我们连 $u$ 到 $v+n$ 和 $v$ 到 $u+n$ 两条双向边。

这样子我们只需要判定对应的两个点是不是同一个连通块里的就行，不难想到并查集。时间复杂度 $O(n \alpha( n))$。

其实你可以深搜染色的，所以可以做到 $O(n)$。

但是交上去发现不对。其实有个 corner case 就是孤立点并且 $s=t$，判一下过了。

---

## 作者：chenxi2009 (赞：3)

## 思路
发现我们可以通过从一个点走到另一个点再走回来使得能量加二，这使得我们可以给能量值几乎随意地加上任意的偶数，所以**基本上**只需要关心 $x$ 的奇偶性。\
**绝大多数情况下**只要我满足了到达 $t$ 后操作完的时候，当前快乐值和目标值对 $2$ 同余就行了，不相同的部分来回走几趟再异或即可达成。

问题转变为从 $s$ 到 $t$ 是否存在一条长度为奇数/偶数的路径。为了方便先讨论图连通的情况。

考虑找一个源点，记录每个点是否可以从源点出发经过长度为奇数/偶数的路径抵达，这个过程搜索即可。

（如果不便理解可以想象成把一个点拆成两个变成分层图，边 $(u,v)$ 变成连接上层的 $u$ 和下层的 $v$，以及连接上层的 $v$ 和下层的 $u$ 的两条边，这样一层的点只能由同层的源点走偶数步到达，异层的源点走奇数步到达，判断可达性即可）

由于图连通，所以 $s$ 和 $t$ 之间的一切路径都可以从中穿插一条走向源点再回来的路，换句话说他们之间的路径都是可以被钦定为是经过源点的，如果源点到他们俩存在奇偶性相同的路径，它们之间就有长度为偶数的路径（把源点到它俩的路拼起来），如果存在奇偶性不同的路径就有长度为奇数的路径。

加上个并查集，把每一个连通分量都做一遍上述的操作就行了。

这么做只有 46 分，还有一种特殊情况是 $s=t$ 且 $s$ 所在连通块大小为 $1$，这时不能做文首所述的“走过去走回来无限刷能量”的操作，所以此时只有 $x=0$ 是可以满足的。

时间复杂度 $O(n+\alpha(m+q))$，其中 $\alpha(x)$ 为反阿克曼函数。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q,u,v,f[300000],s,t,x,sz[300000]; 
bool d[300000][2];
vector<int>e[300000];
queue<pair<int,int>>que;
int find(int x){
	return x == f[x] ? x : f[x] = find(f[x]);
}
int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i = 1;i <= n;i ++) f[i] = i,sz[i] = 1;//记录大小方便特判
	for(int i = 1;i <= m;i ++){
		scanf("%d%d",&u,&v);
		if(find(u) != find(v)) sz[f[u]] += sz[f[v]],f[f[v]] = f[u];
		e[u].push_back(v),e[v].push_back(u);
	}
	for(int i = 1;i <= n;i ++){
		if(f[i] == i){//每个并查集做一次搜索，这里采用的是广搜
			d[i][0] = true;
			que.push({i,0});//前一个数表示某点，后一个数表示路径长度奇偶性
			while(que.size()){
				int u = que.front().first,s = que.front().second;
				que.pop();
				for(auto v : e[u]) if(!d[v][s ^ 1]) d[v][s ^ 1] = true,que.push({v,s ^ 1});//此点此奇偶性可达，入队
			}
		}
	}
	for(int i = 1;i <= q;i ++){
		scanf("%d%d%d",&s,&t,&x);
		if(find(s) != find(t) || sz[f[s]] == 1 && x){
			printf("expand\n");
			continue;
		}
		if(d[s][0] && d[t][x & 1] || d[s][1] && d[t][!(x & 1)]) printf("tribool\n");
		else printf("expand\n");
	}
	return 0;
} 
```

---

## 作者：A_small_WA (赞：2)

赛时没特判喜提 $22$ pts。

由子任务 $3$ 加上推理能得出一个结论：对于 $s,t$ 两个点，如果它们之间有一条长度为奇数的路径，那么可以得到任意一个为奇数的快乐值；反之如果它们之间有一条长度为偶数的路径，那么可以得到任意一个为偶数的快乐值。

基于这个结论，我们可以利用并查集，将所有点的位置用奇偶区分开来，用一个虚拟点 $i+n$ 表示与点 $i$ 奇偶相反的点。具体实现思路见[这里](https://www.luogu.com.cn/problem/P10734)的题解。Tips:感觉最近好多题都能用这种思路做（比如[这个](https://www.luogu.com.cn/problem/P11640)）。

以上思路可以通过子任务 $2$。

除此之外，对于一个可能的有环图，要进行如下判断：

- 注意特判对于两个不在同一个连通块内的点，无论目标快乐值为多少，都无法满足，可以再开一个并查集判断。
- 发现如果一个连通块内有一个奇环（环：从某个点出发，不重复地经过一些边，重新回到这个点的环；奇环：经过奇数条边的环），那么这个连通块里的任意两点之间都可以达到任意快乐值。证明如下：对于连通块内的任意两点 $s,t$ 若它们之间有一条长度为奇数的路径，则可以通过走若干遍奇环使路径长度变为偶数；反之，若它们之间有一条长度为偶数的路径，则可以通过走若干遍奇环使路径长度变为奇数。这里我判断奇环用了一个 `dfs` $+$ 两个 `vector` $+$ 一个 `vis` 数组。大概思路是从任意点出发，不走回头路，每经过一个点就把它放到 `vector` 里，如果能经过一个点两次，那就构成一个环。通过迭代器寻找这个经过两次的点第一次出现的位置，来判断换的长度是奇数还是偶数。具体代码如下：
```cpp
void dfs(int x,int fa){
	//vt装经过的点，vt1装整个连通块的点。 
	if(vis[x]){
		//flag=0时表示没有环，flag=1时表示有奇环，
		//flag=2时表示只有偶环。 
		if(flag==1) return;
		it=find(vt.begin(),vt.end(),x);
		//寻找第一次出现的位置 
		if((vt.end()-it)%2==1) flag=1;
		else flag=2;
		return;
	}
	vis[x]=1;
	vt.push_back(x),vt1.push_back(x);
	for(int i=0;i<eg[x].size();i++){
		if(eg[x][i]==fa) continue;
		//不走回头路 
		dfs(eg[x][i],x);
	}
	vt.erase(vt.end()-1);
	//回溯时记得把这个点从 vector 里删掉 
}
 ```
- 还有最折磨人的部分：当 $s=t$ 时，若 $s$ 点是一个孤立的点（即没有任何连边），则只有 $x=0$ 时才能满足条件。

最后奉上代码和一组数据供调试：
[Link](https://www.luogu.com.cn/paste/nfrww73f)

这是本蒟蒻的第 $16$ 篇题解，感谢观看。

---

## 作者：251Sec (赞：1)

### 题意简述

有一张无向图，你有两个变量 $a,b$，初始都是 $0$。每次经过一条边会使得 $a$ 增加一，当你位于一个点的时候可以令 $b$ 异或上 $a$ 然后把 $a$ 变成 $0$，也可以什么都不做。多次询问，每次给定 $(s,t,x)$ 能否从 $s$ 走到 $t$ 使得最终 $a$ 为 $0$ 且 $b$ 为 $x$。允许经过重复边，到达终点之后可以继续走。

$2 \leq n \leq 2\times 10^5$，$0 \leq m \leq 3\times 10^5$，$1 \leq q \leq 2\times 10^5$，$1 \leq s, t \leq n$，$0 \leq x \leq 10^9$，保证给出的无向图无重边无自环。

### 解法

实际上我们可以说明，特判 $s=t$ 且 $s$ 是孤立点的情况，剩下的情况存在方案当且仅当存在一条 $s$ 到 $t$ 的经过边数和 $x$ 奇偶性相同的途径。

充分性：先从 $s$ 任意走一条经过边数和 $x$ 奇偶性相同的途径，设它的长度为 $w$，那么我们把 $b$ 异或上 $w$，而 $w \oplus x$ 是一个偶数，由于连通块大小至少为 $2$ 我们不妨直接在一条边上反复移动，即可构造出长度为 $w \oplus x$ 的从 $t$ 到 $t$ 的途径。再让 $b$ 异或上它就得到了合法方案。

必要性：考虑经过的所有边，无论中间如何选择操作，最终得到的 $b$ 的奇偶性一定与途径长度相同。这是因为在 $\bmod 2$ 意义下考虑，异或和加法的效果是一致的。

接下来问题变成了判定是否存在一条 $s$ 到 $t$ 的经过边数和 $x$ 奇偶性相同的途径。

先判掉二者不连通的情况，考虑 $s$ 和 $t$ 所在的连通块，如果这个连通块是个二分图，那么连接二者的途径长度奇偶性是唯一确定的，可以任意找一棵生成树求二者树上距离。

如果连通块不是二分图，那么任意考虑一条 $s$ 到 $t$ 的路径，如果它的奇偶性不对，只需要走到任意一个奇环绕一圈然后回来即可改变长度奇偶性，因此一定有解。

---

## 作者：Getaway_Car_follower (赞：1)

首先 $s$ 和 $t$ 肯定在同一个连通块内。

假如 $x$ 与快乐值有着相同的奇偶性，我们注意到我们可以来回走一条边以不停令能量值 $+2$，这样肯定可以达成目标。

那么我们需要知道 $s$ 和 $t$ 之间是否存在一条长度与 $x$ 有相同奇偶性的路径。

那么我们对 $s$ 和 $t$ 所在的子图黑白染色，若这个子图存在奇环，那么肯定可以，因为可以先走到奇环上以改变简单路径长度的奇偶性。

然后如果没有奇环那么肯定是二分图，在一个连通的二分图中，同色的两点只存在偶数长度路径，异色的两点只存在奇数长度路径。那么直接判断两点是否同色即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define Yes "tribool"
#define No "expand"

const int N=2e5+6;
int n,m,q,colo[N],bel[N],ret[N],cnt;
vector<int> e[N];
bool dfs(int x,int y){
	bel[x]=y;
	bool fg=0;
	for(int i:e[x]){
		if(colo[i]){
			if(colo[i]==colo[x]){
				fg=1;
			}
		}
		else{
			colo[i]=colo[x]^3;
			fg|=dfs(i,y);
		}
	}
	return fg;
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m>>q;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		if(!colo[i]){
			colo[i]=1;
			cnt++;
			ret[cnt]=dfs(i,cnt);
		}
	}
	while(q--){
		int s,t,x;cin>>s>>t>>x;
		if(s==t&&e[s].empty()){
			if(x==0) cout<<Yes<<endl;
			else cout<<No<<endl;
		}
		else if(bel[s]!=bel[t]) cout<<No<<endl;
		else if(ret[bel[s]]) cout<<Yes<<endl;
		else if(x%2==0){
			if(colo[s]==colo[t]) cout<<Yes<<endl;
			else cout<<No<<endl;
		}
		else{
			if(colo[s]==colo[t]) cout<<No<<endl;
			else cout<<Yes<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Targanzqq (赞：1)

主要算法：二分图及相关性质。

### 思路：
正难则反，我们首先考虑什么情况不成立。

首先异或可以带来两个性质：一个是与 $0$ 异或的结果是本身，一个是与自身异或的结果是 $0$。并且我们可以将一段长度为偶数的路径（或折返）合并或展开，并通过这两个性质使得我们按照一条路径从 $x$ 到 $t$ 所经过的边数可以通过加上或减去任意**偶数**来成为 $x$。换句话说，这条路径需要满足与 $x$ 的奇偶性相同。

有人可能会问：那如果分成很多段异或会怎么样？其实我们如果把一个数拆成很多数，这些数异或和的奇偶性和原数是相同的，因为这个数被拆成的数中 $m$ 个奇数，那当 $m$ 是奇数时，这个数是奇数，异或和是奇数；当 $m$ 是偶数时，这个数是偶数，异或和是偶数。因此不会改变奇偶性。

我们考虑一个性质：既然需要满足奇偶性相同，我们就考虑如何转变奇偶性。在这里不难想到奇环，如果在奇环上跑一遍，那么回到开始跑的那个点时，奇偶性就可以转变。因此如果一个连通块存在奇环，我们就可以到奇环上去跑一边来改变奇偶性。

问题转化为判断是否有奇环。还是正难则反，我们不难想到，没有奇环的图一定是二分图，而我们可以通过二分图判定的方式来判断有没有奇环，而这种判定方式有个好处，就是能让我们知道，没有奇环的情况下路径长度的奇偶性，可以说两全其美（一个绿题竟然可以出的如此巧妙！）。直接搜索一遍，然后判二分图即可。

最后梳理一下不合法的情况：

- 两点不连通。
- 两点在二分图上并且在一个集合内，$x$ 是奇数。
- 两点在二分图上且不在一个集合内，$x$ 是偶数。

还有最重要的一点，耽误了我整整 $1$ 小时：

- 如果这个点单独构成一个连通块，且 $x$ 不等于 $0$。

除了这些以外，其余情况均合法。这样我们就把这道题做完了，时间复杂度 $O(n+m+q)$。

### 源代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,m,q; 
vector<int> g[200005];
int f[200005],vis[200005],r[200005],fl[200005];
//fl用来判定**不是**二分图的连通块 

void dfs(int rt,int u,int fa){
	r[u]=rt;vis[u]=1;
    for(auto i:g[u]){
    	if(i==fa)continue;
    	if(f[i]!=-1&&f[i]%2==f[u]%2)fl[rt]=1;
		f[i]=f[u]^1;
		if(!vis[i])dfs(rt,i,u);
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		int u,v;cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i=1;i<=n;i++)f[i]=-1;
	for(int i=1;i<=n;i++){
		if(!vis[i])f[i]=0,dfs(i,i,0);
	}
	//cout<<fl[1];
	for(int i=1;i<=q;i++){
		int u,v,x;cin>>u>>v>>x;
	    if(r[u]!=r[v])cout<<"expand";
	    else if(r[u]==r[v]&&!fl[r[u]]){
	    	if(x%2==0&&f[u]!=f[v])cout<<"expand";
	    	else if(x%2==1&&f[u]==f[v])cout<<"expand";
	    	else if(g[u].size()==0&&x!=0)cout<<"expand";
	    	else cout<<"tribool";
		}
		else cout<<"tribool";
		cout<<"\n";
	}
}
/*
考虑不合法的情况：
1.两点不连通
2.两点联通：由于x可以加或减去任意偶数
所以我们只考虑x的奇偶性，如果不存在与x奇偶性相同的路径
那么就无解。因此只要图中有奇环，就可以改变路径长度
所以，如果原图是一个二分图，那么你就无法改变
然后我们就可以根据二分图所在集合来判断奇偶性 
*/
```

---

## 作者：aeiouaoeiu (赞：0)

路径相关，$n$ 很大，给每个起点都处理是困难的，于是从可重路径入手。

发现重复在一条边上绕，每绕一次可以有 $2$ 能量值。通过走到 $t$，再不断绕与 $t$ 相连的一条边，一定可以凑出 $x$ 二进制下除了最小一位外的其他部分。

现在关键在于如何判断能否凑出 $x\bmod 2$。若要凑出 $1$，异或上的能量值必须要有奇数个奇数，故路径总长必须是奇数。$0$ 同理，路径总长必须是偶数。

如何判断 $s$ 到 $t$ 的路径长度可以为奇数还是偶数？考虑黑白染色。若 $s,t$ 所在连通块不能被黑白染色，则一定存在奇环，此时可以通过绕奇环来控制路径长度的奇偶性，一定合法；否则，若 $s,t$ 颜色不同，只能走出长度为奇数的路径，反之亦然。一遍 dfs 即可对连通块进行黑白染色。

注意特判 $s,t$ 不在同一连通块，$s=t$ 且 $s$ 为孤立点这两种情况。

时间复杂度：$\mathcal{O}(n)$。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define mp make_pair 
#define pob pop_back
using namespace std;
typedef long long ll;
const ll maxn=200007,ee=1e18;
ll n,m,q,vis[maxn],vv[maxn],v2[maxn];
vector<ll> edge[maxn];
struct Dsu{
	ll fa[maxn],siz[maxn];
	void init(ll n){iota(fa+1,fa+1+n,1),fill(siz+1,siz+1+n,1);}
	ll fid(ll x){for(;x!=fa[x];x=fa[x]=fa[fa[x]]); return x;}
	void merge(ll x,ll y){
		ll fx=fid(x),fy=fid(y); if(fx==fy) return;
		if(siz[fx]>siz[fy]) swap(fx,fy); fa[fx]=fy,siz[fy]+=siz[fx],siz[fx]=0;
	}
}dsu;
void dfs(ll u){
	vv[u]=1;
	for(auto v:edge[u]){
		if(vv[v]) continue;
		vis[v]=vis[u]^1,dfs(v);
	}
}
string solve(ll s,ll t,ll x){
	if(s==t&&dsu.siz[dsu.fid(s)]==1&&x!=0) return "expand";
	if(dsu.fid(s)!=dsu.fid(t)) return "expand";
	if(v2[dsu.fid(s)]) return "tribool";
	if((vis[s]^vis[t])==(x&1)) return "tribool";
	return "expand";
}
int main(void){
	//freopen("data.in","r",stdin); 
	//freopen("data.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m>>q; dsu.init(n);
	for(int i=1,u,v;i<=m;i++) cin>>u>>v,edge[u].pb(v),edge[v].pb(u),dsu.merge(u,v);
	for(int i=1;i<=n;i++)if(dsu.fid(i)==i) dfs(i);
	for(ll u=1;u<=n;u++)for(auto v:edge[u])if(vis[u]==vis[v]) v2[dsu.fid(u)]=1;
	for(ll i=1,s,t,x;i<=q;i++){
		cin>>s>>t>>x;
		cout<<solve(s,t,x)<<"\n";
	}
	return 0;
}
```

---

## 作者：Manki23333333 (赞：0)

#### 思考（初步考虑）

注意到如果有一条边，就可以来回刷贡献。

如果重复走，就可以让快乐值异或上任意偶数。

所以我们就可以走 $2^1$ 次，$2^2$ 次，$2^3$ 次……

异或起来就可以凑出任意偶数。

但是 $2^0$ 走不了，因为你走一次还要回来啊，而我们是来回刷贡献，都不在终点还刷什么啊。

所以我们考虑什么情况下可以走出奇数，什么情况下可以走出偶数，以及什么情况下可以走出奇数也可以走出偶数。

#### 思考（形成逻辑）

首先，如果 $s, t$ 甚至不在一个联通块，甚至都不可能走过去，当然不可以。

然后我们就可以把目光放到同处于的这个连通块上了。因为连通块外的东西对答案没有影响，所以在这里我们把图看做一个连通的。

现在要看，这个图是否有奇环。有奇环的话，只需要跑一边就可以改变答案的奇偶性，所以无论 $x$  是多少，我们都可以凑出来。而判断奇环可以考虑染色二分图。

如果没有，我们应该看 $s$ 到 $t$ 是否有奇数长度的路径。我们已经知道，这个图确实是二分图，那每个节点都有自己唯一的颜色，就可以考虑 $s$ 和 $t$ 的染色情况。如果颜色不一样，说明仅有一条奇数路径。如果颜色一样，那就是有若干条偶数路径。此时我们再判断一下路径奇偶性是否和 $x$ 的奇偶性一致，这道题就，完成，了，吗？

> #### 思考（初步考虑）
> 注意到如果有一条边，就可以来回刷贡献。

我们的推论是建立在有一条边的基础上，如果甚至没有这条边，也就是这个点是孤岛，我们就无法刷出偶数贡献。此时当且仅当 $x = 0$ 的时候才有解。

#### 代码

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int n, m, q, u, v, k;

vector <int> G [200005];
vector <int> L [200005];

int col [200005], fa [200005], cycle [200005], siz [200005];

int find (int x) {
	return x == fa [x] ? x : (fa [x] = find (fa [x]));
}

void merge (int x, int y) {
	int fx = find (x), fy = find (y);
	
	siz [fy] += fx;
	fa [fx] = fy;
}

bool is2 (int u, int color) {
	col [u] = color;
	for (int i = 0 ; i < G [u]. size () ; i ++) {
		int to = G [u] [i];
		
		if (!col [to]) {
			if (!is2 (to, 3 - color)) {
				return false;
			}
		}
		
		if (col [to] == col [u]) {
			return false;
		}
	}
	
	return true;
}

void Turn () {
	cin >> n >> m >> q;
	
	for (int i = 1 ; i <= n ; i ++) {
		fa [i] = i;
		siz [i] = 1;
	}
	
	for (int i = 1 ; i <= m ; i ++) {
		cin >> u >> v;
		
		G [u]. push_back (v);
		G [v]. push_back (u);
		merge (u, v);
	}
	
	for (int i = 1 ; i <= n ; i ++) {
		L [find (i)]. push_back (i);
	}
	
	for (int i = 1 ; i <= n ; i ++) {
		for (int j = 0 ; j < L [i]. size () ; j ++) {
			if (!col [L [i] [j]]) {
				if (!is2 (L [i] [j], 1)) {
					cycle [i] = 1;
					break;
				}
			}
		}
	}
	
//	for (int i = 1 ; i <= n ; i ++) {
//		cout << find (i) << ", " << col [i] << ", " << cycle [find (i)] << endl;
//	}
	
	while (q --) {
		cin >> u >> v >> k;
		
		if (find (u) != find (v)) {
			cout << "expand\n";
			continue;
		}
		
		if (siz [find (u)] == 1) {
			if (k == 0) {
				cout << "tribool\n";
				continue;
			}
			
			cout << "expand\n";
			continue;
		}
		
		k %= 2;
		
		if (cycle [find (u)]) {
			cout << "tribool\n";
			continue;
		}
		
		if (col [u] != col [v] && k == 1) {
			cout << "tribool\n";
			continue;
		}
		
		if (col [u] == col [v] && k == 0) {
			cout << "tribool\n";
			continue;
		}
		
		cout << "expand\n";
	}
}

signed main () {
	int T = 1;
//	cin >> T;
	
	while (T --) {
		Turn ();
	}
	
	return 0;
}
```

---

## 作者：wmrqwq (赞：0)

# 题目链接

[【MX-X8-T3】「TAOI-3」地地爱打卡 (*1700)](https://www.luogu.com.cn/problem/P11644)

# 解题思路

真不难吧，只是一个简单分讨，注意到这是一个无向图，因此我们特判以下几种情况：

- 若 $s,t$ 不在一个连通块中，则点 $s$ 一定不能到达点 $t$，输出 `expand`，这个部分可以简单使用并查集维护。

- 若 $s = t$，且 $s$ 所在的连通块大小为 $1$，且 $x = 0$，则此情况一定合法，不移动即可，输出 `tribool`。

- 若 $s = t$，且 $s$ 所在的连通块大小为 $1$，且 $x \neq 0$，则此情况一定不合法，因为你无法移动，输出 `expand`。

此时，特判完这些情况，$s$ 可以到达 $t$，且连通块的大小一定大于 $1$，基于这个性质，我们发现此时点 $s$ 可以无限游走，点 $s$ 能到达 $t$ 且异或和为 $x$ 当前仅当：

- 若 $x$ 为奇数，则 $s$ 到 $t$ 的路程有至少 $1$ 条长度也为奇数。

- 若 $x$ 为偶数，则 $s$ 到 $t$ 的路程有至少 $1$ 条长度也为偶数。

那么我们只需要将这个图黑白染色一下就可以解决了，证明显然，在此不再赘述，时间复杂度为 $O(n \log n + q \log n)$。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define ll long long
#define cll const ll
#define forl(i,a,b) for(re ll (i)=(a);i<=(b);(i)++)
#define forr(i,a,b) for(re ll (i)=(a);i>=(b);(i)--)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
ll _t_;
ll n,m,k;
ll x,y,z;
vector<ll>G[1000100];
ll id[1000010];
ll sz[1000010];
ll col[1000010][2];
ll find(ll x)
{
    if(id[x]==x)
        return x;
    return id[x]=find(id[x]);
}
void merge(ll x,ll y)
{
    x=find(x),y=find(y);
    if(x!=y)
    {
        if(sz[x]>sz[y])
            swap(x,y);
        id[x]=y;
        sz[y]+=sz[x];
        sz[x]=0;
    }
}
void Dfs(ll x,ll y)
{
    for(auto i:G[x])
        if(!col[i][y^1])
            col[i][y^1]=1,
            Dfs(i,y^1);
}
void solve()
{
    cin>>n>>m>>k;
    forl(i,1,n)
        sz[i]=1,
        id[i]=i;
    forl(i,1,m)
        cin>>x>>y,
        G[x].pb(y),
        G[y].pb(x),
        merge(x,y);
    forl(i,1,n)
        if(!col[i][0] && !col[i][1])
            col[i][0]=1,
            Dfs(i,0);
    forl(_,1,k)
    {
        cin>>x>>y>>z;
        if(x==y)
        {
            if(z%2)
            {
                if(col[x][0]+col[x][1]==2)
                    cout<<"tribool\n";
                else
                    cout<<"expand\n";
            }
            else if(z && sz[find(x)]==1)
                cout<<"expand\n";
            else
                cout<<"tribool\n";
            continue;
        }
        else if(find(x)!=find(y))
        {
            cout<<"expand\n";
            continue;
        }
        else if(sz[find(x)]==1)
            while(1);
        else if(z%2)
        {
            if(col[x][0]+col[y][1]==2 || col[x][1]+col[y][0]==2)
                cout<<"tribool\n";
            else
                cout<<"expand\n";
        }
        else
        {
            if(col[x][0]+col[y][0]==2 || col[x][1]+col[y][1]==2)
                cout<<"tribool\n";
            else
                cout<<"expand\n";
        }
    }
}
int main()
{
    IOS;
    _t_=1;
    while(_t_--)
        solve();
    QwQ;
}
```

---

## 作者：_Kenma_ (赞：0)

## 前言

诈骗题。

## 思路分析

首先异或啥的别看了，是假的。

考虑如果要求异或值为 $x$，如果我们能得到的路径长度为 $k$，考虑：

- $x \le k$，那么可以将 $k-x$ 的部分分成两半抵消；

- $x>k$，那么可以从 $s$ 出发走到任意一个点再沿反边返回，每次增加 $2$ 的路径长度。

所以，只需要保证 $x$ 和 $k$ 的奇偶性相同就行了。

那么直接做就行了。

- 如果 $s$ 和 $t$ 不连通，没戏；

- 如果 $s$ 和 $t$ 所在的连通块是二分图，那么看 $s$ 和 $t$ 是否同色，判断两点之间路径的奇偶性；

- 如果 $s$ 和 $t$ 所在的连通块不是二分图，那么两点之间一定同时存在奇偶路径。

除此之外，还需要特判 $s=t$ 的情况。

使用并查集和二分图染色实现，总体复杂度 $O(n\alpha(n))$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q,x,y,k,flag;
int head[200005],nxt[600005],target[600005],tot;
void add(int x,int y){
	tot++;
	nxt[tot]=head[x];
	head[x]=tot;
	target[tot]=y;
}
int fa[200005],col[200005],siz[200005];
void init(){
	for(int i=1;i<=n;i++){
		fa[i]=i;
		col[i]=2;
		siz[i]=1;
	}
}
int find(int x){
	if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	x=find(x);
	y=find(y);
	if(x==y) return;
	fa[x]=y;
	siz[y]+=siz[x];
}
void dfs1(int x){
	for(int i=head[x];i;i=nxt[i]){
		int y=target[i];
		if(col[y]==2){
			col[y]=(!col[x]);
			dfs1(y);
		}else if(col[x]==col[y]) flag=true;
	}
}
void dfs2(int x){
	col[x]=-1;
	for(int i=head[x];i;i=nxt[i]){
		int y=target[i];
		if(col[y]==-1) continue;
		dfs2(y);
	}
}
signed main(){
	cin>>n>>m>>q;
	init();
	for(int i=1;i<=m;i++){
		cin>>x>>y;
		add(x,y);
		add(y,x);
		merge(x,y);
	} 
	for(int i=1;i<=n;i++){
		if(col[i]==2){
			flag=false;
			col[i]=0;
			dfs1(i);
			if(flag) dfs2(i);
		}
		
	}
	for(int i=1;i<=q;i++){
		cin>>x>>y>>k;
		if(find(x)!=find(y)){
			cout<<"expand"<<'\n';
		}else{
			if(x==y && siz[find(x)]==1){
				if(k) cout<<"expand"<<'\n';
				else cout<<"tribool"<<'\n';
			}else{
				if(col[x]==-1){
					cout<<"tribool"<<'\n';
				}else{
					if((k&1) && (col[x]!=col[y])){
						cout<<"tribool"<<'\n';
					}else if(!(k&1) && (col[x]==col[y])){
						cout<<"tribool"<<'\n';
					}else{
						cout<<"expand"<<'\n';
					}
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：_zuoqingyuan (赞：0)

# 思路分析

首先，若 $s,t$ 不在同一连通块，一定无法做到。下文假设 $s,t$ 在同一连通块

假设 $s,t$ 所在联通块大小大于 $1$（伏笔）。这样我们就可以在 $s$ 与其他点连接的一条边上来回走，先把快乐值攒够 $x$。

若 $x$ 为奇数，则来回走动后必然不在 $s$，此时想要有解则需要 $s,t$ 之间存在长为奇数的路径（走一步异或一步）。若 $x$ 为偶数，则需要 $s,t$ 之间存在长为偶数的路径（走一步异或一步）。

显然，若 $s,t$ 所在联通块存在奇环，则 $s,t$ 之间同时有长为奇数和偶数的路径。因为我们可以先到达 $t$，然后再从 $t$ 走到奇环上一点 $u$，绕奇环一圈后到 $u$，再回到 $t$，此时路径长度奇偶性一定发生变化。

若 $s,t$ 所在联通块内不存在奇环，则 $s,t$ 之间路径长度奇偶性唯一，可以二分图染色判断。

好的：若 $s,t$ 所在联通块大小等于 $1$ 呢？此时 $s=t$，若 $x\ne 0$ 则无解。

其他情况可以转化为上面所说的思路。

# Code

联通块用并查集搞，奇环判定用二分图染色，时间复杂度 $O(n+q)$。


```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N=3e5+10;
int n,m,q,ver[N],to[N<<1],nxt[N<<1],idx,f[N],col[N],type[N],siz[N];
void add(int x,int y){
    to[++idx]=y,nxt[idx]=ver[x],ver[x]=idx;
}
int found(int x){
    return f[x]==x?x:f[x]=found(f[x]);
}
bool dfs(int x,int c){
    col[x]=c;
    for(int i=ver[x];i;i=nxt[i]){
        int y=to[i];
        if(!col[y]&&dfs(y,3-c))return 1;
        else if(col[y]==col[x])return 1;
    }
    return 0;
}
int main(){
    scanf("%d %d %d",&n,&m,&q);
    for(int i=1;i<=n;i++)f[i]=i,siz[i]=1;
    for(int i=1,u,v;i<=m;i++){
        scanf("%d %d",&u,&v);
        add(u,v),add(v,u);
        u=found(u),v=found(v);
        if(u!=v)f[u]=v,siz[v]+=siz[u];
    }
    for(int i=1;i<=n;i++)if(i==found(i))type[i]=dfs(i,1);
    int s,t,x;
    while(q--){
        scanf("%d %d %d",&s,&t,&x);
        if(found(s)!=found(t))printf("expand\n");
        else{
            if(type[found(s)])printf("tribool\n");
            else if(siz[found(s)]==1&&x>0)printf("expand\n");
            else if((x&1)==(col[s]==col[t]))printf("expand\n");
            else printf("tribool\n");
        }
    }
    return 0;
}
```

如有错误，请指出。

---

## 作者：_lmh_ (赞：0)

我们要让最后的异或值 $=x$ 且恰好用尽所有步数，所以假设我们走了 $L$ 步，则我们需要将 $L$ 拆成几个正整数使得它们的异或值为 $x$。下文记异或运算为 $\oplus$。

$x\oplus y\le x+y$，所以 $L\ge x$（否则不论怎么拆都凑不出这个值）。而 $x\oplus y\equiv x+y\pmod 2$，所以 $L\equiv x\pmod 2$。

而 $L\ge x$ 且 $L\equiv x\pmod 2$ 时其必定满足条件——$L>x$ 时，将其拆成 $x+\frac{L-x}{2}+\frac{L-x}{2}$ 即可。$L=x$ 的情况是显然的。

特判掉 $s=t$ 且 $s$ 没有出边的情况，现在来构造路径。$L\ge x$ 的条件是容易满足的——在一条边上来回走即可。而 $L\equiv x\pmod 2$ 的条件更加复杂。只有在连通块上存在奇环时才能反转路径的奇偶性，否则这条路径的奇偶性固定，可以黑白染色求出。

一次 dfs 即可求出所有必要的信息，时间复杂度 $O(n)$。参考代码是一个比较蠢的单 $\log$ 的实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=200007;
ll n,m,q,s,t,x,fa[N],vis[N],col[N],odd[N];
vector<ll> to[N];
int getfa(int x){return x==fa[x]?x:fa[x]=getfa(fa[x]);}
void dfs(int u){
	vis[u]=1;
	for (auto v:to[u]){
		if (vis[v]) odd[getfa(u)]|=(col[u]==col[v]);
		else{
			col[v]=col[u]^1;dfs(v);
		}
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m>>q;
	for (int i=1;i<=n;++i) fa[i]=i;
	for (int u,v,i=1;i<=m;++i){
		cin>>u>>v;
		to[u].emplace_back(v);to[v].emplace_back(u);
		fa[getfa(u)]=getfa(v);
	}
	for (int i=1;i<=n;++i) if (fa[i]==i) dfs(i);
	while(q--){
		cin>>s>>t>>x;
		if (getfa(s)!=getfa(t)){cout<<"expand\n";continue;}
		if (s==t&&to[s].size()==0){
			cout<<(x==0?"tribool\n":"expand\n");continue;
		}
		cout<<(odd[getfa(s)]||(x&1)==(col[s]^col[t])?"tribool\n":"expand\n");
	}
	return 0;
}
```

---

## 作者：Lele_Programmer (赞：0)

# P11644 题解

## 思路

题目说了那么多，就是想询问能否将一条从 $u$ 到 $v$ 的路径的长度分成若干段，使得每一段的长度异或起来等于 $x$。

把 $x$ 每个数位拆出来，从低位到高位依次表示长度为 $1,2,4,8,16,32,\cdots$ 的段，对应的位为 $0$ 则表示对应长度的段出现偶数次，$1$ 则表示奇数次。

长度为 $k$ 的段出现偶数次，能够形成的长度为 $0,2k,4k,6k,\cdots$，即 $2k$ 的倍数；出现奇数次，能够形成的长度为 $k,3k,5k,7k,\cdots$，可以看成是 $2k-k,4k-k,6k-k,8k-k,\cdots$，即 $2k$ 的倍数减去 $k$。

上面，$2k$ 的倍数，即 $2$ 的若干次方的倍数，而对于奇数，减去的 $k$ 的和是固定的，这个固定值就是 $x$。

不难发现，我们目的就是确定是否能够构造一条从 $u$ 到 $v$ 的路径，使得这条路径的长度可以表示成 $(\sum\limits_{i=1}^k a_i 2^{p_i}) - x$，并且 $p_i$ 两两不同。

有一个很显然的就是前面那一坨 $\sum$ 的值可以表示任意一个偶数，那么，由 $x$ 的奇偶性，决定路径长的奇偶性。

如果 $u,v$ 所在的连通块里出现长度为奇数的环，那么在这个环里绕一圈，奇偶性就可以变换，长度为偶数则不行。

所以如果 $u,v$ 在同一个连通块内并且存在奇数长的环，则一定有解；如果不存在，则两点之间的每一条路径长的奇偶性相同，只需求出任意一条，若奇偶性与上面那个式子的奇偶性相同，则有解，否则无解；如果 $u,v$ 不在同一个连通块，则显然无解；如果 $u=v$，且单独一个点作为一个连通块，若 $x=0$ 则有解，否则无解。

要求出同一连通块内两点之间的距离，可以对每一个连通块建一棵生成树，用最近公共祖先来计算即可，这样单次查询的时间复杂度可以做到 $\mathcal{O}(\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define TIMESTAMP cerr<<fixed<<setprecision(3)<<clock()*1.0/CLOCKS_PER_SEC<<"s"<<endl;
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define rint register int
#define LL long long
#define i32 signed
#define i64 long long
#define i128 __int128
#define u32 unsigned
#define u64 unsigned long long
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<double,double> pdd;

namespace IO {
    template<typename T> inline void read(T& x) {
        int s=1; char c=getchar(); x=0;
        while (!isdigit(c)) { if (c=='-') s=-1; c=getchar(); }
        while (isdigit(c)) x=x*10+(c-'0'),c=getchar();
        x*=s;
    }
    inline void readstr(string& x) {
        x.clear(); char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x.push_back(c),c=getchar();
    }
    inline void readstr(char* x) {
        int idx=0; char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x[++idx]=c,c=getchar();
    }
    template<typename T> inline void write(T x) {
        if (x<0) putchar('-'),x=-x;
        if (x/10) write(x/10);
        putchar('0'+(x%10));
    }
    template<typename T> inline void writesp(T x) { write(x); putchar(' '); }
    template<typename T> inline void writeln(T x) { write(x); putchar(10); }
};

using namespace IO;

const int N=200005;
const int M=600005;
const int K=35;

int n,m,q;
int e[M],ne[M],h[N],tot;
int p[N];
int layer[N];
int tag[N];
bool flag[N];
int f[N][K];
int sz[N];

void add(int a,int b) {
    e[tot]=b,ne[tot]=h[a],h[a]=tot++;
}

int find(int x) {
    if (p[x]==x) return p[x];
    else return p[x]=find(p[x]);
}

bool dfs(int u,int dep) {
    layer[u]=dep;
    bool ok=false;
    _graph(i,u) {
        if (~tag[e[i]] && tag[e[i]]==tag[u]) ok=true;
        else if (!~tag[e[i]]) {
            tag[e[i]]=(tag[u]^1);
            if (dfs(e[i],dep+1)) ok=true;
            f[e[i]][0]=u;
            _rep(j,1,K-1) f[e[i]][j]=f[f[e[i]][j-1]][j-1];
        }
    }
    return ok;
}

int lca(int a,int b) {
    if (a==b) return a;
    if (layer[a]<layer[b]) swap(a,b);
    _rrep(i,K-1,0) if (layer[f[a][i]]>=layer[b]) a=f[a][i];
    if (a==b) return a;
    _rrep(i,K-1,0) if (f[a][i]!=f[b][i]) a=f[a][i],b=f[b][i];
    return f[a][0];
}

int main() {
    memset(h,-1,sizeof(h));
    memset(tag,-1,sizeof(tag));
    read(n),read(m),read(q);
    _rep(i,1,n) p[i]=i;
    while (m--) {
        int a,b;
        read(a),read(b);
        add(a,b); add(b,a);
        p[find(a)]=find(b);
    }
    _rep(i,1,n) {
        if (!~tag[i]) {
            tag[i]=0;
            flag[find(i)]=dfs(i,1);
        }
        sz[find(i)]++;
    }
    // printf("flag: "); _rep(i,1,n) printf("%d ",flag[find(i)]); putchar(10);
    // printf("layer: "); _rep(i,1,n) printf("%d ",layer[i]); putchar(10);
    while (q--) {
        int s,t,x;
        read(s),read(t),read(x);
        if (s==t && sz[find(s)]==1) {
            if (x) puts("expand");
            else puts("tribool");
            continue;
        }
        if (find(s)!=find(t)) puts("expand");
        else if (flag[find(s)]) puts("tribool");
        else {
            int g=lca(s,t);
            int dis=layer[s]-layer[g]+layer[t]-layer[g];
            dis+=x;
            if (dis&1) puts("expand");
            else puts("tribool");
        }
    }
    return 0;
}
```

---

## 作者：BMnya (赞：0)

先特判掉孤点和不连通的情况。

对于一次询问 $(s,t,x)$，如果能找到一条从 $s$ 到 $t$ 的长为 $k$ 的路径，且 $k$ 与 $x$ 奇偶性相同，那么就有解，反之无解。

因为如果存在这样的 $k$，就可以先走到 $t$，让快乐值为 $k$ 并清空能量值，再在 $t$ 和 $t$ 的某相邻点之间反复移动，直到新的能量值累计为 $k\oplus x$（是个偶数），再异或上之前的快乐值就可以得到 $x$。

如果不存在这样的 $k$，由于 $a\oplus b$ 与 $a+b$ 奇偶性相同，说明找不到一条从 $s$ 到 $t$ 的若干段路径使其异或和与 $x$ 奇偶性相同，也就不可能得到 $x$。

考虑如何判断：如果 $(s,t)$ 之间的所有路径长度奇偶性都相同，那么说明图一定是二分图，就可以对图进行黑白染色（相邻点颜色不同），反之则不行。

所以可以对原图的每个连通块尝试黑白染色：如果可行标记每个点的颜色，根据两点颜色可以判断出两点间路径奇偶性，再判断其与 $x$ 奇偶性是否相同得到解是否存在；如果不可行说明该连通块内任意两点存在任意奇偶性的路径，即对于任意 $x$ 总是有解。

---

```cpp
struct DSU{
    vector<int> fa,siz; int n;
    void init(int _n){
        n=_n,fa=siz=vector<int>(n+1);
        iota(fa.begin()+1,fa.end(),1),fill(siz.begin()+1,siz.end(),1);
    }
    int getf(int x){return x==fa[x]?x:fa[x]=getf(fa[x]);}
    void merge(int x,int y){
        x=getf(x),y=getf(y);
        if(x!=y){
            if(siz[x]>siz[y]) swap(x,y);
            siz[y]+=siz[x],fa[x]=y;
        }
    }
    bool linked(int x,int y){return getf(x)==getf(y);}
}dsu;

const int N=2e5+10;
int n,m,q,col[N],flag;

vector<int> G[N];

void draw(int x){
    for(int y:G[x])
        if(col[x]==col[y]) flag=1;
        else if(!col[y]) col[y]=3-col[x],draw(y);
}
void mark(int x){
    col[x]=-1;
    for(int y:G[x]) if(col[y]!=-1) mark(y);
}

inline void solve(){
    n=read(),m=read(),q=read(),dsu.init(n);
    for(int u,v;m;--m){
        u=read(),v=read();
        G[u].emplace_back(v),G[v].emplace_back(u),dsu.merge(u,v);
    }
    for(int i=1;i<=n;++i) if(!col[i]){
        flag=0,col[i]=1,draw(i); // 尝试黑白染色。
        if(flag) mark(i);        // 无法黑白染色，标记块中所有点。
    }
    for(int u,v,w;q;--q){
        u=read(),v=read(),w=read();
        if(u==v&&dsu.siz[dsu.getf(u)]==1){
            if(!w) puts("tribool"); else puts("expand"); // 孤点。
        }
        else if(!dsu.linked(u,v)) puts("expand"); // 不连通。
        else if(col[u]==-1) puts("tribool"); // 无法黑白染色的块内总是合法。
        else if((col[u]!=col[v])==(w&1)) puts("tribool"); // 否则根据奇偶性判断是否合法。
        else puts("expand");
    }
}
```

---

