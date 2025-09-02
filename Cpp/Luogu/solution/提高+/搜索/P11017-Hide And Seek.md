# Hide And Seek

## 题目描述

Drifty 在和 hgcnxn 玩躲猫猫。

整个地图有 $n$ 个房间，由 $n-1$ 条走廊连接（保证对于任意的两个房间都能互相抵达）。

对于游戏的每一回合，hgcnxn 先走一步，Drifty 后走一步（特别的，hgcnxn 必须走一步，而 Drifty 可以不动）。

hgcnxn 从编号为 $p$ 的房间开始，任务是要抓到 Drifty，hgcnxn 通过雷达，得知了 Drifty 一开始所在的房间编号 $q$，hgcnxn 会预先设计一条尽可能优的抓捕方案，并按照计划抓捕 Drifty。**但 hgcnxn 并不知道接下来的回合中 Drifty 的位置。**

但是，Drifty 更加狡猾，他提前预知了 hgcnxn 的整个计划，并采用了最优的方案尝试去避开 hgcnxn。但是鉴于地图的原因，Drifty 可能还是会被抓到。

特别的，hgcnxn 并不知道 Drifty 能够提前知道他的整个计划。

现在给你 $n, p, q$ 和地图，问你在 $10^{100}$ 回合内，hgcnxn 是否可能抓到 Drifty。


## 说明/提示

#### 【数据范围】


设 $\sum n$ 表示单个测试点中 $n$ 的和。

对于 $100\%$ 的数据，保证：

- $3\le \sum n\le 2\times 10^5$
- $1\le p,q\le n$
- $1\le T\le 10^3$。

以下是部分分的具体分配：

|$\text{Subtask}$|$\sum n\leq$|分值| 特殊性质 |
|:-:|:-:|:-:|:-:|
|$0$|$2\times 10^5$|$1$| A |
|$1$|$2\times 10^5$|$2$| B |
|$2$|$7$|$3$| 无 |
|$3$|$2\times 10^5$|$9$| C |
|$4$|$2\times 10^5$|$85$| 无 |

- 特殊性质 A：保证所有给定的地图的形态均为一条链。
- 特殊性质 B：保证所有给定的地图的形态均为菊花图（即地图中 $n-1$ 个房间度数为 $1$）。
- 特殊性质 C：保证地图中只存在一个度数为 $3$ 的房间，且其余的房间度数均 $\le 2$。

其中，一个房间的度数被定义为连接该房间的走廊数。

## 样例 #1

### 输入

```
2
3 1 3
1 2
2 3
5 2 4
1 2
1 3
1 4
1 5```

### 输出

```
hgcnxn
hgcnxn```

# 题解

## 作者：ARIS2_0 (赞：5)

（下文简称 Drifty 为 d，hgcnxn 为 h，放心，他们都是我同学，不会在意的……应该吧 ~~（逃）~~）

---

**结论：**

在图中找具有如下结构的节点 $x$ ，我们将这种节点命名为关键点。

![](https://cdn.luogu.com.cn/upload/image_hosting/fjgrn1xp.png)

严谨地，满足以下条件的为关键点 $p$：

- $p$ 的入度不小于 $3$

- 与 $p$ 相连的节点中，至少有 $3$ 个节点的入度不小于 $2$。

对图跑一遍 BFS，得到 $d_i$ 与 $h_i$，分别代表 d 到点 $i$ 的距离与 h 到点 $i$ 的距离。最后，**对于图中的每一个关键点，若有任何一个关键点 $p$ 满足 $d_p< h_p-1$ ，输出 `Drifty`，否则输出 `hgcnxn`。**

---

下面给出证明。过程可能会有一点冗长而且不严谨，但相信我，我能把你讲懂，应该比[官方题解](https://www.luogu.com/article/9eo29t09)好一点……吧？

---

**证明：**

让我们先理解题意。因为 h 的目标仅仅是捉到 d，并且还没有时间限制，所以 h 的最优方案一定是把整个图全跑一遍。那么，如果 d 能赢，他一定有方法和 h 玩“套圈子”。而本题给定的又是无向无环图，所以，我们要找到一个 d 可以与 h 玩“套圈子”的子图。那么，我们现在来开始寻找这个子图。

首先，子图显然不可能是一条链，这样 h 肯定能捉到 d；其次，子图如果是以下这种结构，也是不可能的：

![](https://cdn.luogu.com.cn/upload/image_hosting/ork9m005.png)

对于这样的结构，h 可以先到一号节点，然后按  
`1->2->3->2->4->5->4->6->7->6->8->9->8->10`  
的顺序搜，也总能找到 d。

那么，回收开头，开始证明：

**对于图中的每一个关键点，若有任何一个关键点 $p$ 满足 $d_p< h_p-1$ ，输出 `Drifty`，否则输出 `hgcnxn`。**

以这张图为例子说明：

![](https://cdn.luogu.com.cn/upload/image_hosting/iy99dhtz.png)

假设 h 在 1 号节点，d 在 3 号节点。此时，对于关键点 3 号节点，$h_3=2$，$d_3=0$。

显然，h 想要捉到 d，他一定要进入 4 号或 6 号节点，由于两者是等价的，不妨设 h 进入了 4 号节点。此时，h 有三种选择：

1. 走进 5 号节点，即选择 `1->2->3->4->5` 的路线。此时，d 可以选择 `3->6->6->6->3` 的路线，可以发现，此时 h 在 5 号节点，d 在 3 号节点，两人可以进行无数次这样的行动，即 h 永远也捉不到 d；

2. 回马枪杀回 3 号节点，然后在 2、3、4、6 号节点之间乱逛。显然，d 只要藏在 1、5、7 号节点之中的任意一个即可。

3. 回马枪杀回 3 号节点，然后在 2、3、4、6 号节点之间乱逛一阵之后，回到 1、5、7 号节点之中的任意一个节点，这里假设 h 回到的是 1 号节点。对于这种情况，d 可以选择 `3->6->7` 的路线，然后在 7 号节点躲无数个回合，直到 h 走 `3->2->1` 路线的时候，走 `7->6->3` 的路线，就又回到了开始的状态！

以上是 $d_p< h_p-1$ 的情况。然而，如果不满足这个条件呢？

考虑以下状态：h 在 1 号节点，d 在 6 号节点，此时 $h_3=2$，$d_3=1$。当 h 选择 `1->2->3->6->7` 的路线时，可以发现，d 必然会被 h 抓住。

综上，得：

**对于图中的每一个关键点，若有任何一个关键点 $p$ 满足 $d_p< h_p-1$ ，输出 `Drifty`，否则输出 `hgcnxn`。**

---

证明完毕，撒花！~~（bushi）~~

下面给出代码：

---

**代码：**


```cpp
#include<bits/stdc++.h>//赛时AC代码，可能有点丑，见谅
using namespace std;
const int maxn=2e5+10;
vector<int>v[maxn];bool b[maxn];//vector存图
queue<int>q;int dist_carry[maxn],dist_be_carried[maxn];
//dist_carry对应h，dist_be_carried对应d;
int n;
void bfs(int s,int a[]){//bfs搜距离
	memset(b,0,sizeof(b));
	memset(a,-1,sizeof(a));
	while(!q.empty())q.pop();
	b[s]=1;q.push(s);a[s]=0;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=0;i<v[x].size();i++){
			int y=v[x][i];
			if(!b[y]){
				b[y]=1;a[y]=a[x]+1;q.push(y);
			}
		}
	}
}
bool istysan(int x){//判断节点x是否为关键点
	if(v[x].size()>2){
		int ans=0;
		for(int i=0;i<v[x].size();i++){
			if(v[v[x][i]].size()>1)ans++;
		}
		if(ans>2)return 1;
	}return 0;
}
bool canrunout(int carry,int be_carried){//判断d能否让h捉不到
	for(int i=1;i<=n;i++){
		if(istysan(i)){
			if(dist_be_carried[i]+1<dist_carry[i])return 1;
		}
	}return 0;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while(t--){
		int carry,be_carried;cin>>n>>carry>>be_carried;
		for(int i=1;i<=n;i++)v[i].clear();
		for(int i=1;i<n;i++){
			int p,q;cin>>p>>q;v[p].push_back(q);v[q].push_back(p);
		}bfs(carry,dist_carry);bfs(be_carried,dist_be_carried);
		if(canrunout(carry,be_carried))cout<<"Drifty\n";
		else cout<<"hgcnxn\n";
	}
	return 0;
}
```

---

**后言：** 有什么问题可以在评论区友好讨论

---

## 作者：c_y_y (赞：4)

# Hide And Seek 官方题解
称一棵树中的子图为**牵制地点**，当且仅当 hgcnxn 和 Drifty只在该子图中走动，且 hgcnxn 无法在有限步抓到 Drifty。  
事实上，Drifty 想不要被 hgcnxn 抓住，必须要找到合适的牵制地点。  
故第一步，我们需要找到牵制地点的共同特点。

以下称“节点”为房间。

---
>推论 1：一条链不存在牵制地点。  
形式化的，设 $V$ 为一个树的点集，则对于 $\forall i \in V$，均有节点 $i$ 的度数 $\le 2$，则该图不存在牵制地点。

事实上，hgcnxn 只需往 Drifty 所在的地方走就可以了。由于没有岔路，Drifty 必败。

由推论 1 可以得出，**一棵树中存在牵制地点的必要条件是，该图中存在度数 $\ge 3$ 的点**。

考虑到这种点是特殊点，故定义一棵树中度数 $\ge 3$ 的节点称为该树的**小根**。小根并不唯一。

---
以下表示的“图”默认为一棵树的子图。
> 推论 2：设图中一个小根的度数为 $n$。若以其为该图的根，$n$个儿子中有 $\ge n-2$ 个为叶子节点，则该小根及其儿子构成的子图不是牵制地点。

先证明 $n$ 个儿子全部为叶子结点的情况。

在某一回合，不妨设 hgcnxn 站在小根，Drifty 在某个叶子节点上。  
那么，在下一回合中，hgcnxn 出于最优计划，会走向一个未被搜查过的节点，如果该节点里面有 Drifry ，游戏就结束了。否则对于 Drifty 来说：

- 走到小根。此时轮到 hgcnxn，他立刻回到小根，游戏结束。
- 原地静止，hgcnxn 会依个搜查每一个叶子节点。总会有一次找到 Drifty，游戏结束。

故 Drifty 在这种情况下必败。  
称与小根距离为 $1$ 的叶子节点为**危险节点**。Drifty 肯定不希望自己走到危险节点（就算 hgcnxn 离 Drifty 很远，Drifty 也肯定不会待在危险节点等待被抓）。故在后续中，可以**忽视所有的危险节点**。

进一步，若把这些危险节点忽视后，至多只有 $2$ 个儿子，那么该情况就是一条局部的链。由推论 1，该图不是牵制地点。

---
总结推论 1 和推论 2，一棵树的子图为牵制地点的必要条件是：

1. 该子图拥有至少一个小根。
2. 该子图的某一个小根中，至少有**三个儿子**不是叶子节点。

根据上面的结论，得出**最小单位的牵制地点**如下（其中橙色为小根）。
![](https://cdn.luogu.com.cn/upload/image_hosting/kqfwp6a4.png)
接下来证明该图是牵制地点即可。

由推论 2，不妨设 Drifty 在黄色点，hgcnxn 在小根。由于 Drifty 知道全部的抓捕计划，故他会待在 hgcnxn 下一回合不会抓捕的黄色点。  
出于最优的抓捕计划，hgcnxn 必须要走到黄色地点（否则 Drifty 就可以一直待在黄色点）。

又由于 Drifty 知道全部的抓捕计划，故他知道 hgcnxn 在哪一回合走到黄色点。

不妨那一回合下，hgcnxn 的抓捕方案为 $X \to 1 \to A \to 1 \to X \to 2 \to B \to 2 \to X$。
![](https://cdn.luogu.com.cn/upload/image_hosting/vxu7c6i9.png)
那么，Drifty 就有方案 $B \to 2 \to X \to 3 \to C \to 3 \to X \to 1 \to A$。不会被抓住。  
**此操作相当于每次 Drifty 都会躲在 hgcnxn 这次和下次均不会到达的黄点。** 证毕。

---
证明了最小单位的牵制地点，难道就完了吗？

不！

Drifty 必须比 hgcnxn 更先到小根，且 Drifty 到小根时，hgcnxn 与他距离至少为 $2$（想一想为什么）。

代码还是比较容易实现的，每组数据先进行 dfs 操作，得出两人到每个点的距离。一棵树中可能存在多个牵制地点，对于这些点，我们可以用 $O(n)$ 的方法判断出图中的小根，然后枚举每一个小根，判断距离就行了。

```
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e5 + 7;
constexpr int hgcnxn = 1, Drifty = 0;
vector <int> g[N];
bitset <N> tag;
int d[2][N];
auto clear_g = [](size_t n) {
	for (int i=0; i<=n; i++) g[i].clear();
	tag = 0;
	memset (d, 0, sizeof(d));
};
auto get_struct = [](int n) {
	for (int i=1; i<=n; i++) {
		int siz = g[i].size();
		if (siz >= 3) {
			int tot = 0;
			for (int v : g[i])
				if (g[v].size() > 1) tot ++;
			if (tot >= 3) tag[i] = 1;
		}
	}
};
void dfs(int u, int fa, int s, const int k) {
	d[k][u] = s;
	for (auto v : g[u]) {
		if (v == fa) continue;
		dfs (v, u, s + 1, k);
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	int T; cin >> T;
	for (int n, p, q; T--; ) {
		cin >> n >> p >> q;
		clear_g (n);
		for (int i=1, u, v; i<n; i++) 
			cin >> u >> v, g[u].push_back(v), g[v].push_back(u);
		get_struct (n);
		dfs (q, 0, 0, Drifty), dfs (p, 0, 0, hgcnxn);
		bool f = false;
		for (int i=1; i<=n; i++) 
			if (tag[i]) {
				int ans = INT_MAX;
				for (int v : g[i]) ans = min(ans, d[hgcnxn][v]);
				if (ans > d[Drifty][i]) {f=true; break;}
			} 
		if (f) cout << "Drifty\n";
		else cout << "hgcnxn\n";
	}
	return 0;
}
```

---

## 作者：JuRuoOIer (赞：3)

# 题解 P11017 Hide And Seek

前排提示：本题为**结论题**。本篇题解旨在阐明本人是怎么想到的，并给出一个（自认为）比较易懂的证明。

本文中称 hgcnxn 为“抓的”，Drifty 为“跑的”。

另：尽管写得不少，思维可能还是不太连贯，如果有我没讲明白的地方，欢迎在评论区或者私信问我~

### 分析思路

看上去题意很绕，各种知道不知道的。但比较通俗地理解一下，其实就是抓的只要无法同时顾及跑的可能出现所有的位置，跑的就一定不会被抓住。

这种题的特殊性质通常是能够引领思路的。因此我们先来考虑这些性质。

#### 性质 A（链）

由于抓的知道跑的的初始位置，所以抓的只要往那个位置走就能把跑的逼死，此时抓的必胜。

#### 性质 B（菊花）

仍然是由于抓的知道跑的的初始位置，因此抓的开局上根节点（如果已经在了直接到下一步）再往跑的的所在方向走，跑的就跑不掉。

#### 性质 C（菊花套链，花蕊度数为 $3$）

这时情况多了起来。不要慌，耐心地进行分讨就好。

先不妨设每条链都很长但长度有限。这里称靠近“花蕊”的方向为“上”，反方向为“下”。
- 当抓的和跑的在同一条链上时，明显可以分两种情况：
  - 如果抓的在跑的上面，抓的直接往下就可以把跑的逼死；
  - 否则抓的跑到花蕊之后无法确定跑的会往哪条链跑，由题意（抓的无法兼顾所有跑的可能出现的位置时跑的一定不被抓住）跑的一定不会被抓住。
- 当抓的和跑的不在同一条链上时，凭空想的话不是很好想，但实际上可以跟上面的情况进行类比，或者从最终的结果出发，来得到两种情况：
  - 如果跑的可能先抓的一步以上到花蕊，那同样由题意跑的一定不会被抓，因为跑的可以根据抓的到达花蕊后往哪个方向走来决定到底要不要提前跑到花蕊去另一条链；
  - 否则抓的先到达花蕊，由于知道了跑的的初始位置而跑的不可能到达其他的链，因此跑的所在的链可以唯一确定，故跑的会被逼死。

综合上述情况，**跑的能够胜利，当且仅当跑的可能先抓的一步（不含）以上到达花蕊**。

但是我们这里的前提是每条链足够长，现在考虑链很短的情况。
- 四个点的菊花图：在菊花图的性质中考虑过了，抓的必胜。
- 一条链很长，另两条链只延伸一个点：抓的先走到长链的另一端（即不是菊花花蕊的一端）
  - 先往上走到根节点，这时跑的已经被逼到两个一个点的链中的一个了；
  - 进一个一个点的链再出来，此时跑的不管能不能都不敢上根节点，因为否则下回合直接秒；
  - 同理进另外一个一个点的链再出来，这样就能把跑的逼死。
  - 如图：![](https://cdn.luogu.com.cn/upload/image_hosting/30gp0h4s.png)
- 两条链很长，另一条链只延伸一个点：类似于上面的情况，先从一条长链远离花蕊的一端走到根节点，然后进一个点的链再出来（和刚才一样，此时跑的无法换链）最后再下另一条长链。如图：![](https://cdn.luogu.com.cn/upload/image_hosting/sb8pb7yn.png)

综上，性质 C 中“花蕊”所连的三条链都必须“很长”，跑的才能赢。现在我们需要“很长”的定义。

刚才我们说，长度为 $1$ 的链不行，是因为抓的到链底再上来的期间，跑的不能从一条链到达另一条链。所以我们试试长度为 $2$ 的链。

![](https://cdn.luogu.com.cn/upload/image_hosting/t5flj5b2.png)

我们发现，此时当抓的下到链底时，跑的可以趁此机会换到另一条链。也就是说，刚才的“很长”其实就是**长度大于等于 $2$。**

到这里，我们自然而然地猜想到：
>如果图中存在一个和上图结构相同的子图，且跑的能先于抓的到达该子图的“花蕊”处，则会出现上图中的情形，跑的必胜；否则抓的必胜。

然后我们发现，证明其充分性就是上图，证必要性就是我们刚才证明某条链长度为 $1$ 不行的过程。所以说，这个结论是正确的。

枚举每个点及其每条出边，如果存在至少三条出边，满足该边另一端的点度数大于等于 $2$，即至少还连了另外一个点，则该点为刚才所说的“花蕊”，判断 $p$ 和 $q$ 哪个点到该点更近，如果 $q$ 到该点的距离比 $p$ 到该点的距离小 $2$ 及以上，则跑的必胜；如果所有的这种点都不满足距离关系，则抓的必胜。

距离可以通过遍历进行预处理，每条边最多只会被枚举两次，所以时间复杂度 $O(m)$。

### 代码

```cpp
ll t,n,p,q,u,v,lp[200010],lq[200010];
//lp[i] 和 lq[i] 分别表示从 p 和从 q 到 i 的最短距离
vector<ll> a[200010]; 
void dfs(ll now,ll dep,ll lst,ll op){//遍历求出 lp 和 lq 数组
	if(op)lq[now]=dep;
	else lp[now]=dep;
	for(int i=0;i<a[now].size();i++){
		if(a[now][i]!=lst){
			dfs(a[now][i],dep+1,now,op);
		}
	}
}
bool check(ll now){//判断是否为满足要求的点
	ll tot=0;
	for(int i=0;i<a[now].size();i++){
		if(a[a[now][i]].size()>1)tot++;
		if(tot>2)return true;
	}
	return false;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>n>>p>>q;
		for(int i=1;i<=n;i++){
			a[i].clear();//记得清空
		}
		for(int i=1;i<n;i++){
			cin>>u>>v;
			a[u].push_back(v);
			a[v].push_back(u);
		}
		dfs(p,0,-1,0);//预处理距离
		dfs(q,0,-1,1);
		bool flg=0;
		for(int i=1;i<=n;i++){
			if(check(i)&&lp[i]>lq[i]+1){//存在一个符合条件的点跑的就必胜
				flg=1;
				break; 
			}
		}
		if(flg)cout<<"Drifty\n";
		else cout<<"hgcnxn\n";
	}
	return 0;
}
```

---

## 作者：Aventurine_stone (赞：1)

## 1. 题目分析
做这道题，我们只需要知道在什么情况下逃脱者能无限次躲避追捕者，再加上一些特殊判断就可以了。
## 2. 题目做法
题目的部分分给了我们提示。自己手动模拟一下便知道，在一条链上和一张菊花图上，逃脱者必定会被抓到。  
我们姑且将我们要找的能使逃脱者无限次躲过追捕者的子图称为安全子图。  
首先，一条链上是绝对不会有任何安全子图的。  
然后再让我们看看下面这张图。  
![](https://cdn.luogu.com.cn/upload/image_hosting/tt1db4fq.png)  
在这张图中，追捕者不管从哪里出发，只要经过一个点，若他旁边有叶子节点，他谨慎起见，一定会走进此叶子节点然后再回来，如果在此期间逃脱者想要绕后，走到追捕者已经搜索过的点上，那么一定会被返回的追捕者抓住。所以逃脱者必定被抓，故菊花图也必被抓。  
综上，逃脱者一定不会躲到叶子节点去，而且安全子图中必须要有分叉。那么我们就可以想到下面这张图。  
![](https://cdn.luogu.com.cn/upload/image_hosting/viudmrm4.png)  
可以看到，在这个图中，追捕者若已安排了抓捕路线，不管他怎么走，那么逃脱者都可以无限次躲避追捕者。那么我们只需要找到每个这种安全子图的 $1$ 点就行了。  
还有一点是，逃脱者要比追捕者提前 $2$ 步到达 $1$ 点，否则因为追捕者先走，逃脱者就已经被抓了。
## 3. 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200010,M=400010;
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
int head[N],ne[M],e[M],idx;
inline void add(int x,int y)
{
	ne[++idx]=head[x];
	head[x]=idx;
	e[idx]=y;
}
int T,n,a,b;
int d[N],dd[N],t;
int dish[N],disd[N];
queue<int>qh,qd;
bool safe,p;
bool ask()
{
	if(a==b)
		return 1;
	qh.push(a),qd.push(b);
	for(int i=1;i<=n;i++)	
		dish[i]=disd[i]=0;
	dish[a]=1,disd[b]=1;
	while(!qh.empty())
	{
		t=qh.front();
		qh.pop();
		for(int i=head[t];i;i=ne[i])
		{
			int c=e[i];
			if(!dish[c])
			{
				dish[c]=dish[t]+1;
				qh.push(c);
			}
		}
	}
	while(!qd.empty())
	{ 
		t=qd.front();
		qd.pop();
		for(int i=head[t];i;i=ne[i])
		{
			int c=e[i];
			if(!disd[c])
			{
				disd[c]=disd[t]+1;
				qd.push(c);
			}
		}
	}
	for(int i=1;i<=n;i++)
		if(dd[i]>2&&disd[i]<dish[i]-1)
			return 0;
	return 1;
}
int x,y;
int main()
{
	T=read();
	while(T--)
	{
		n=read(),a=read(),b=read();
		for(int i=1;i<=n;i++)
			head[i]=d[i]=dd[i]=0;//记得清空 
		idx=0;
		for(int i=1;i<n;i++)
		{
			x=read(),y=read();
			add(x,y),add(y,x);
			d[x]++,d[y]++;
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=head[i];j;j=ne[j])
			{
				int c=e[j];
				if(d[c]>1)
					dd[i]++;
			}
		}
		if(ask())
			printf("hgcnxn\n");
		else
			printf("Drifty\n");
	}
	return 0;
}
```

---

## 作者：wdsjl (赞：0)

# P11017题解
_首先说明一下这是一道非常好的特殊结论得部分分从而推正解的题目我们先从特殊性质着手_ 
## 特殊性质分析
### 特殊性质 A：

保证所有给定的地图的形态均为一条链。

显而易见一条链的情况下藏的人是肯定会被抓的毕竟是可以一条路走到头。

那我们不难想到当一个点的度数大于 $2$，是不是藏的人就可以通过这个点拉扯一下呢再看特殊数据 B。

### 特殊性质 B：

保证所有给定的地图的形态均为菊花图。

在这种情况下有一个房间与另外所有房间相连，可以说能选择的路变得很多，但是发现还是不行，为什么能准确的来说就是虽然路的条数变多了，但是每条路太短，还是不够拉扯。

### 特殊性质 C：

保证地图中只存在一个度数为 $3$ 的房间，且其余的房间度数均 $\le 2$ 。

这种情况就比较接近普遍情况了，有一个可以供中转的点，并且，每条路有可能够长。

## 思路整理

我们发现不被抓到要有如下条件：

1. 有一个度数大于等于 $3$ 的点。
2. 并且躲的人能在抓的人之前来到这个点。
3. ~~与这个点相连的长度大于等于 $2$ 的路至少有 $3$ 条。~~（思考一下这条怎么错了）

![](https://cdn.luogu.com.cn/upload/image_hosting/wruqdcu3.png)

是的按照以上条件可能出现这种看上去满足长度大于等于 $2$ 的路至少有 $3$ 条，事实上都是与一个点相连的 $3$ 条还是会被抓到。

![](https://cdn.luogu.com.cn/upload/image_hosting/g11x8ffg.png)

所以正确的应该为枚举与这个点的邻点如果度数大于等于 $2$ 的数量大于等于 $3$ 则满足条件。

## 代码思路
所以我们代码的思路就是：

1. 从 $p$ 和 $q$ 搜求到达各个点的距离。
2. 枚举每个点如果该点满足上述条件则打上标记。
3. 再次枚举如果能先于抓的人赶到有标记的点则不会被抓到。
4. 如果枚举完没有满足则会被抓到。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 7;
constexpr int hgcnxn = 1, Drifty = 0;

vector <int> g[N];
bitset <N> tag;
int d[2][N];

auto cl = [](size_t n) {
	for (int i=0; i<=n; i++) g[i].clear();
	tag = 0;
	memset (d, 0, sizeof(d));
};

auto get_tag = [](int n) {
	for (int i=1; i<=n; i++) {
		int siz = g[i].size();
		if (siz >= 3) {
			int tot = 0;
			for (int v : g[i])
				if (g[v].size() > 1) tot ++;
			if (tot >= 3) tag[i] = 1;
		}
	}
};
void dfs(int u, int fa, int s, const int k) {
	d[k][u] = s;
	for (auto v : g[u]) {
		if (v == fa) continue;
		dfs (v, u, s + 1, k);
	}
}
int main() {
	int T; cin >> T;
	for (int n, p, q; T--; ) {
		cin >> n >> p >> q;
		cl (n);
		for (int i=1, u, v; i<n; i++) 
			cin >> u >> v, g[u].push_back(v), g[v].push_back(u);
		get_tag (n);
		dfs (q, 0, 0, Drifty);
		dfs (p, 0, 0, hgcnxn);
		bool f = false;
		for (int i=1; i<=n; i++) 
			if (tag[i]) {
				int res = 0x7f7f7f7f;
				for (int v : g[i]) res = min(res, d[hgcnxn][v]);
				if (res > d[Drifty][i]){
				f=true;
				break;
			}
		} 
		if(f)cout<<"Drifty\n";
		else cout <<"hgcnxn\n";
	}
	return 0;
}
```

---

