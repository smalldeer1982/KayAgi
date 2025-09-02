# Edge coloring of bipartite graph

## 题目描述

#### 题意
给你一个无向的二分图。现在将它的每条边染色，使得任意两条相邻（有公共顶点）的边颜色不同。请你计算一种染色方案，使得用到的颜色数量最少。

## 样例 #1

### 输入

```
4 3 5
1 2
2 2
3 2
4 1
4 3
```

### 输出

```
3
1 2 3 1 2
```

# 题解

## 作者：Daidly (赞：27)

### 猜测

点染色判断二分图的方法想必大家都有所耳闻，那么边染色呢？

给出一个二分图，求最小边染色。

当看到**最小边染色**这几个字时，大胆猜测：

> 二分图的最小边染色结果等于点的最大度数。

相邻边颜色不同已经为此做下了铺垫：由于一个点的度数记录的是与这个点相连的边数，而这些边都相邻，不能是同一种颜色，所以猜测二分图的最小边染色结果等于点的最大度数。

### 证明：

设点的最大度数为 $k$，二分图的最小边染色结果为 $ans$。

显然，$ans\geq k$（最大度数为 $k$ 说明最多有 $k$ 条边相邻的情况）。

**考虑构造一种染色方法**：

对于任意一条边 $(u,v)$，设集合为点 $u$ 连边的颜色集为 $C1$，点 $v$ 连边的颜色集为 $C2$。

定义 ${\rm{mex(S)}}$ 为不属于集合 $S$ 的最小正整数。

若 ${\rm{mex(C1)}}={\rm{mex(C2)}}$：

即存在一种颜色使得集合 $C1,C2$ 中都不包含并且最小。

直接用其将 $(u,v)$ 染色。

若 ${\rm{mex(C1)}}\ne{\rm{mex(C2)}}$：

说明在集合 $C2$ 中存在一种颜色等于 ${\rm{mex(C1)}}$。

找出这条边，设为 $(v,w)$，这条边的颜色等于 ${\rm{mex(C1)}}$。

将 $(u,v)$ 强制染上 ${\rm{mex(C1)}}$，此时 $(u,v)$ 与 $(v,w)$ 颜色冲突。

将 $(v,w)$ 的颜色转化为 ${\rm{mex(C2)}}$。

此时 $(u,v)$ 与 $(v,w)$ 颜色不冲突。

但是 $(v,w)$ 可能与 $(w,x)$ 颜色冲突，考虑循环使用如上方法解决。

设从 $(u,v)$ 开始的循环到 $(y,z)$ 结束，即 ${\rm{mex(C1_y)}}={\rm{mex(C2_z)}}$。

此时，从 $(u,v)$ 开始的循环到 $(y,z)$ 结束这个过程就相当于一条链。

由于此图是二分图，所以必定有一条边的两种颜色不冲突。

而其中的 $\max(|C1|_ {\max},|C2|_ {\max})=k=ans$。

构造完毕。

证毕。

发现链的长度最多为 $a+b$，遍历每条边，共 $m$ 条，所以时间复杂度为：$O((a+b)m)$。

- 小结论：简单图最小边染色为 $k\leq ans \leq k+1$。

### 代码

代码中包含讲解：

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
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

const int MAXN=2e3+5;
const int MAXM=1e5+5;
int a,b,m,u[MAXM],v[MAXM],in[MAXN];
int ans,color1,color2,color[MAXN][MAXN];

//color[i][j]=k表示(i,k)这条边的颜色为j

int main(){
	a=read(),b=read(),m=read();
	for(int i=1;i<=m;++i){
		u[i]=read(),v[i]=read();
		v[i]+=a;
        //将v[i]的大小计入总图中
		in[u[i]]++,in[v[i]]++;
        //统计度数
	}
	for(int i=1;i<=a+b;++i){
		ans=max(ans,in[i]);
        //寻找最大度数
	}
	for(int i=1;i<=m;++i){
		color1=1,color2=1;
		while(color[u[i]][color1])++color1;
		while(color[v[i]][color2])++color2;
        //寻找到mex(C1),mex(C2)
		color[u[i]][color1]=v[i];
		color[v[i]][color2]=u[i];
        //标记
		if(color1==color2)continue;
        //若颜色不冲突，则直接染色
		for(int tmp=color2,w=v[i];w;w=color[w][tmp],tmp^=color1^color2){
			swap(color[w][color1],color[w][color2]);
		}
        //通过异或实现color1和color2的交替染色
	}
	print(ans),puts("");
	for(int i=1;i<=m;++i){
		for(int j=1;j<=ans;++j){
			if(color[u[i]][j]==v[i]){
				print(j),printf(" ");
			}
		}
	}
    //匹配输出
	return 0;
}
```

如果你觉得这篇题解讲得还算好的话，可以点个赞支持一下呀，谢谢大家！

---

## 作者：Clever_Jimmy (赞：7)

【CodeForces】CF600F Edge coloring of bipartite graph

### 题意简述：

给定一个点集大小分别为 $a, b$，有 $m$ 条边的二分图，

问将其染成 **任意两相邻边颜色均不同** 最少需要多少种颜色，并输出任意一种方案。

$1 \le a, b \le 10^3$，$1 \le m \le 10^5$。

[题目链接](https://codeforces.com/contest/600/problem/F)

### 解题思路：

边染色一个二分图，最少需要的颜色种数为图中顶点的最大度数。

具体证明可以看 [Story about edge coloring of graph](https://codeforces.com/blog/entry/75431)。

然后我们可以钦定一个点出边的颜色，如果有不符合的就顺着链摸下去修改颜色即可。

时间复杂度为 $O(m(a + b))$。

### 参考代码：


```cpp
#include <bits/stdc++.h>
#define LL long long

const int N = 2e3 + 5;
const int M = 2e5 + 5;

int a, b, m, ans;
int u[M], v[M], deg[N], col[N][N];

int32_t main() {
	scanf("%d %d %d", &a, &b, &m);
	for(int i = 1; i <= m; ++i) {
		scanf("%d %d", &u[i], &v[i]);
		v[i] += a;
		++deg[u[i]], ++deg[v[i]];
	}
	for(int i = 1; i <= a + b; ++i)
		ans = std::max(ans, deg[i]);
	for(int i = 1; i <= m; ++i) {
		int c1, c2;
		for(c1 = 1; c1 <= ans; ++c1) if(!col[u[i]][c1]) break;
		for(c2 = 1; c2 <= ans; ++c2) if(!col[v[i]][c2]) break;
		col[u[i]][c1] = v[i];
		col[v[i]][c2] = u[i];
		if(c1 == c2) continue;
		for(int c0 = c2, x = v[i]; x; x = col[x][c0], c0 ^= c1 ^ c2)
			std::swap(col[x][c1], col[x][c2]);
	}
	printf("%d\n", ans);
	for(int i = 1; i <= m; ++i)
		for(int j = 1; j <= ans; ++j)
			if(col[u[i]][j] == v[i]) {
				printf("%d ", j);
				break;
			}
	return 0;
}
```


---

## 作者：DengDuck (赞：6)

结论是颜色数为最大的点的度数。

必要性是显然的。

对于充分性，考虑构造一种方案。

坚持一个原则，尽量用没用过的颜色里面编号最小的。

每次加边 $(u,v)$，对于这两个点，设没用过的颜色最小为 $C_u,C_v$，严谨来说是 $\operatorname{mex}$。

如果 $C_u=C_v$，那么显然可以直接把这条边的颜色设为 $C_u$。

否则我们把边设为其中的任意一个颜色，假设你设为 $C_u$，那么 $v$ 可能存在一条边 $(v,x)=C_u$，我们考虑把这条边染成 $C_v$，然后有冲突再更新....

这样一直更新就行了。

显然，我们是以 $C_u,C_v,C_u,C_v,C_u,\cdots$ 这样交替染色的，所以不可能有环。

因为二分图有环长度必然是偶数，所以我们染的是 $C_v$，那么前置条件是那是路径的最后一个点 $x$ 存在一条到达 $u$ 的边颜色为 $C_u$，这与 $u$ 原先没有颜色为 $C_u$ 的边矛盾。 

那为啥是最大的点的度数呢？

我们考虑每次相当于 $u,v$ 各自多了一个颜色，其他点的颜色数不变，所以加完边之后恰好每个点的颜色都是度数。

时间复杂度为 $\mathcal O((a+b)m)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2005;
const LL M=2e5+5;
LL A,B,m,ans,c[N][N],du[N],u[M],v[M];
int main()
{
    scanf("%lld%lld%lld",&A,&B,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%lld%lld",&u[i],&v[i]);
        v[i]+=A;
        du[u[i]]++,du[v[i]]++;
    }
    LL ans=0;
    for(int i=1;i<=A+B;i++)ans=max(ans,du[i]);
    printf("%lld\n",ans);
    for(int i=1;i<=m;i++)
    {
        LL mx1=1,mx2=1;
        while(c[u[i]][mx1])++mx1;
        while(c[v[i]][mx2])++mx2;
        c[u[i]][mx1]=v[i],c[v[i]][mx2]=u[i];
        if(mx1==mx2)continue;
        for(LL t=mx2,x=v[i];x;x=c[x][t],t^=mx1^mx2)swap(c[x][mx1],c[x][mx2]);
    }
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=ans;j++)
        {
            if(c[u[i]][j]==v[i])
            {
                printf("%d ",j);
                break;
            }
        }
    }
}
```

---

## 作者：Purslane (赞：4)

# Solution

算是一个经典结论了吧。

把一个二分图 $(V_1,V_2,E)$ 每条边都进行染色，使得所有拥有公共点的两条边颜色都不一样，需要的最小颜色数是 $\max_{u \in V_1 \cup V_2} \{ \deg u \}$。很显然我们不能用更少的颜色实现这一目标。

而这个值能取到，使用构造法证明，顺带把这道题过了。

令 $v = \max_{u \in V_1 \cup V_2} \{ \deg u \}$。

考虑按顺序依次加边。假设我们目前需要确定颜色的边为 $(u_1,u_2)$。

如果 $u_1$ 没有用过的颜色和 $u_2$ 没有用过的颜色有非空交集，可以直接钦定当前这条边的颜色。

否则，假设 $c$ 是 $u_1$ 没有用过的颜色之一。那么考虑把这条边钦定成 $c$（下图中的红色）。那么根据设定，$u_2$ 必定和另一个点 $u_3$ 连了一条颜色为 $c$ 的边。考虑更换这条边的颜色（图中的 $CG$）。我们可以随便再钦定一 $u_2$ 没用过的颜色，比如说是 $d$（下图的黄色）。

> 注意，这时候因为 $u_2$ 连上的边的数量小于 $v$，所以一定能找到这样一个 $d$。

这样会引起一连串连锁反应。不过没关系，我们在图上不断走红黄交错的边。很容易注意到，我们永远不会得到环，因为根据设定，$u_2$ 没有连 $d$ 边。

那我们把这条极长的，红黄交错的路径全部翻转颜色（也就是红变黄，黄变红）即可。是不是很像找增广路？不过不完全一样就是了。

复杂度 $O(nm)$，可以认为是 $O(n^3)$。

![](https://s11.ax1x.com/2024/01/19/pFE8YMd.png)

脑筋急转弯：如果是把二分图的点染色，让每条边连的两个点颜色不同怎么办？~~答案是 $2$（当然不考虑有一半是空集的情况。）~~

代码（非递归找环版）：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1000+10,MAXM=1e5+10;
int n1,n2,m,lst,degl[MAXN],degr[MAXN],x[MAXM],y[MAXM],res[MAXM],id[MAXN][MAXN],tl[MAXN][MAXN],tr[MAXN][MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n1>>n2>>m;
	ffor(i,1,m) cin>>x[i]>>y[i],id[x[i]][y[i]]=i,degl[x[i]]++,degr[y[i]]++;
	lst=max(*max_element(degl+1,degl+n1+1),*max_element(degr+1,degr+n2+1));
	ffor(i,1,m) {
		int u1=x[i],u2=y[i],flg=0;
		ffor(j,1,lst) if(tl[u1][j]+tr[u2][j]==0) flg=j;
		if(flg) tl[u1][flg]=u2,tr[u2][flg]=u1;
		else {
			int flg1=0,flg2=0;
			ffor(j,1,lst) if(tl[u1][j]==0) flg1=j;
			ffor(j,1,lst) if(tr[u2][j]==0) flg2=j;	
			vector<int> cl,cr;
			int pos=u2;
			while(pos) {
				cr.push_back(pos);
				if(tr[pos][flg1]) {
					cl.push_back(tr[pos][flg1]);
					pos=tl[tr[pos][flg1]][flg2];
				}
				else break ;
			}
			for(auto id:cl) swap(tl[id][flg1],tl[id][flg2]);
			for(auto id:cr) swap(tr[id][flg1],tr[id][flg2]);
			tl[u1][flg1]=u2,tr[u2][flg1]=u1;
		}
	}
	ffor(i,1,n1) ffor(j,1,lst) res[id[i][tl[i][j]]]=j;
	cout<<lst<<'\n';
	ffor(i,1,m) cout<<res[i]<<' ';
	return 0;
}
```

---

## 作者：ganpig (赞：2)

构造思路参考其他题解，但实现还可以更优雅（

其实没必要统计度数的，直接在染色过程中记下用过的最大数值即可。

可以用 `std::find_if` 来找 $\operatorname{mex}$，`std::logical_not` 即逻辑非（`!`），遇到 $0$ 值返回 `true`。

### $\text{Code}$

```cpp
#include <bits/stdc++.h>
int main() {
    int a, b, m;
    std::cin >> a >> b >> m;
    std::vector<std::pair<int, int>> e(m);
    std::vector<std::vector<int>> to(a + b + 1, std::vector<int>(std::max(a, b) + 1));
    int ans = 0;
    for (auto &[u, v] : e) {
        std::cin >> u >> v, v += a;
        int c1 = std::find_if(to[u].begin() + 1, to[u].end(), std::logical_not()) - to[u].begin(),
            c2 = std::find_if(to[v].begin() + 1, to[v].end(), std::logical_not()) - to[v].begin();
        to[u][c1] = v, to[v][c2] = u, ans = std::max({ans, c1, c2});
        if (c1 != c2)
            for (int x = v, c = c2; x; x = to[x][c], c ^= c1 ^ c2)
                std::swap(to[x][c1], to[x][c2]);
    }
    std::cout << ans << '\n';
    for (auto [u, v] : e)
        std::cout << std::find(to[u].begin(), to[u].end(), v) - to[u].begin() << ' ';
}
```

---

## 作者：251Sec (赞：1)

分享无脑选手神人做法。

注意到答案不小于最大度数 $d$，猜测这就是答案，那么怎么构造呢。

最坏情况是每个点度数都是 $d$，一般的情况都可以补全到这种情况：只需要把两边点数补到相等，然后补一些边使得度数正确即可。可以有重边。

现在问题变成把一个正则二分图划分成 $d$ 组完美匹配。这是经典问题：如果 $d$ 为偶数，可以找一组欧拉回路，然后递归到两个 $\frac{d}{2}$ 的问题。如果 $d$ 为奇数，那么每次随机一个点出发随机游走找增广路，可以证明这样会在 $O(nd+n\log n)$ 的复杂度内找到一组匹配。总复杂度就是 $O(nd \log d + nd \log n)$，不超过 $O(n^2 \log n)$。

我使用该做法，在代码长度约为别人 $3$ 倍且运行时间约为别人 $6$ 倍的情况下通过了此题，可喜可贺。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int a, b, n, m;
struct Edge {
	int v, id;
	bool operator==(const Edge &b) const {
		return v == b.v && id == b.id;
	}
};
vector<Edge> e[2005];
struct EDat {
	int u, v, id;
};
EDat eP[1000005];
int epC;
int deg[2005], maxD, iC, cur[2005];
int pL[1000005], p[2005], pC;
bool vis[1000005];
void EDFS(vector<Edge> *e, int u) {
	for (int &i = cur[u]; i < e[u].size(); ) {
		auto ed = e[u][i++];
		if (vis[ed.id]) continue;
		vis[ed.id] = true;
		EDFS(e, ed.v);
		eP[++epC] = { ed.v, u, ed.id };
	}
}
mt19937 eng(363415);
int st[2005], top, mat[2005];
int cC, ans[100005];
void Solve(vector<Edge> *e) {
	if (e[1].size() & 1) {
		for (int i = 1; i <= n; i++) p[i] = i;
		for (int i = 1; i <= n * 2; i++) vis[i] = mat[i] = 0;
		shuffle(p + 1, p + n + 1, eng);
		for (int i = 1; i <= n; i++) {
			int u = p[i]; st[++top] = u;
			while (u) {
				int v;
				do v = e[u][eng() % e[u].size()].v; while (v == mat[u]);
				while (vis[v]) vis[st[top--]] = false;
				vis[st[++top] = v] = true;
				st[++top] = u = mat[v];
			}
			top--;
			for (int j = top; j; j -= 2) {
				int a = st[j], b = st[j - 1];
				mat[a] = b; mat[b] = a;
			}
			while (top) vis[st[top--]] = false;
		}
		cC++;
		for (int u = 1; u <= n; u++) {
			int v = mat[u], id = -1;
			for (auto [v, i] : e[u]) {
				if (v == mat[u]) {
					id = i; break;
				}
			}
			if (id <= m) ans[id] = cC;
			e[u].erase(find(e[u].begin(), e[u].end(), (Edge){ v, id }));
			e[v].erase(find(e[v].begin(), e[v].end(), (Edge){ u, id }));
		}
	}
	if (e[1].empty()) return;
	for (int i = 1; i <= n * 2; i++) cur[i] = 0;
	vector<Edge> eL[2005], eR[2005];
	for (int s = 1; s <= n * 2; s++) {
		if (cur[s] < e[s].size()) EDFS(e, s);
	}
	for (int i = 1; i <= n * 2; i++) {
		eL[i].reserve(e[1].size() / 2);
		eR[i].reserve(e[1].size() / 2);
	}
	for (int i = 1; i <= epC; i++) {
		auto [u, v, id] = eP[i];
		vis[id] = false;
		if (u <= n) eL[u].push_back({ v, id }), eL[v].push_back({ u, id });
		else eR[u].push_back({ v, id }), eR[v].push_back({ u, id });
	}
	epC = 0;
	Solve(eL), Solve(eR);
}
int main() {
	scanf("%d%d%d", &a, &b, &m), n = max(a, b);
	for (int i = 1, u, v; i <= m; i++) {
		scanf("%d%d", &u, &v);
		e[u].push_back({ v + n, i });
		deg[u]++, deg[v + n]++;
	}
	iC = m;
	for (int i = 1; i <= n * 2; i++) maxD = max(maxD, deg[i]);
	printf("%d\n", maxD);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= maxD - deg[i]; j++) pL[++pC] = i;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= maxD - deg[i + n]; j++) {
			e[pL[pC--]].push_back({ i + n, ++iC });
		}
	}
	for (int u = 1; u <= n; u++) {
		for (auto [v, id] : e[u]) e[v].push_back({ u, id });
	}
	Solve(e);
	for (int i = 1; i <= m; i++) printf("%d ", ans[i]);
	return 0;
}
```

---

## 作者：OrinLoong (赞：1)

## CFP600F 二分图边染色 学习笔记
[Luogu Link](https://www.luogu.com.cn/problem/CF600F)

### 前言
题如其名，二分图边染色板子。

这种板子怎么洛谷才过了这么点人？

本题解基本借鉴[这篇题解](https://www.luogu.com.cn/article/wv6kqcyn)。

### 题意简介
给定一个简单无向二分图。现在将其每一条边染色，使得任意两条有公共顶点的边颜色不同。问最少需要多少种颜色，并给出一种染色方案。

### 做法解析
是啊，最少需要多少种颜色呢？

首先下界显然是所有点中的最大度数。接下来我们构造一种必定能取到下界的方案。

对于边 $(u,v)$，设 $u$ 作为端点的边的颜色集合为 $C_1$，设 $v$ 作为端点的边的颜色集合为 $C_2$。

此处 $\text{mex}(S)$ 定义为集合中不存在的最小正整数。设 $cc1=\text{mex}(C_1),cc2=\text{mex}(C_2)$。

如果 $cc1=cc2$ 即存在一种颜色使得 $C_1,C_2$ 中都不包含且最小，那直接染上去就行了。

如果 $cc1\neq cc2$，我们还是强制把这条边染成 $cc1$，但是这样做的话，$v$ 可能有两条边都是 $cc1$ 的颜色。设此时另一条颜色为 $cc1$ 的边为 $(v,w)$，我们把它染成 $cc2$。这样的话 $v$ 也合法了，但是 $w$ 有可能又不合法了，设此时另一条颜色为 $cc2$ 的边为 $(w,x)$，则我们把它染成 $cc1$……这个过程是可以递归下去的。

![pEdrm6g.md.png](https://s21.ax1x.com/2025/03/18/pEdrm6g.md.png)

正确性？我们这样交替染色，不可能有环——因为二分图上环长必为偶数，如果有环的话我们成环的最后一条边肯定染的是 $cc2$，其前置条件是成环的最后一个点 $f$ 存在一条到 $u$ 的边颜色 $cc1$，这与 $u$ 一开始没有颜色为 $cc1$ 的边矛盾。

然后因为不可能有环，所以一次染色复杂度为 $O(n)$。总复杂度 $O(nm)\le O(n^3)$。

### 代码实现
想清楚就很好写。绿题难度。
```cpp
#include <bits/stdc++.h>
using namespace std;
using namespace obasic;
const int MaxN=2e3+5,MaxM=1e5+5;
int A,B,M,N,X,Y,deg[MaxN],ans;
struct edge{int u,v;}E[MaxM];int col[MaxN][MaxN];
void addudge(int u,int v,int id){E[id]={u,v},deg[u]++,deg[v]++;}
int main(){
    readi(A),readi(B),readi(M),N=A+B;
    for(int i=1;i<=M;i++)readi(X),readi(Y),addudge(X,Y+A,i);
    for(int i=1;i<=N;i++)maxxer(ans,deg[i]);
    for(int i=1,cc1,cc2;i<=M;i++){
        auto [u,v]=E[i];cc1=cc2=1;
        while(col[u][cc1])cc1++;
        while(col[v][cc2])cc2++;
        col[u][cc1]=v,col[v][cc2]=u;
        if(cc1==cc2)continue;
        for(int tmp=cc2,w=v,cx=cc1^cc2;w;){
            swap(col[w][cc1],col[w][cc2]);
            w=col[w][tmp],tmp^=cx;
        }
    }
    writi(ans),puts("");
    for(int i=1;i<=M;i++){
        auto [u,v]=E[i];
        for(int j=1;j<=ans;j++){
            if(col[u][j]==v){writi(j),putchar(' ');break;}
        }
    }
    return 0;
}
```

### 反思总结
板子，记。

---

## 作者：Liuxizai (赞：1)

[My Blog](https://liuxizai.ac.cn/archives/solutions-2024-1.html)

一个结论是，无向简单图边染色所需的最少颜色数为 $d$ 或 $d+1$，其中 $d$ 为图中点的最大度数。

特别的，在二分图中，所需最少颜色数为 $d$。

我们按某个顺序给边染色。设当前考虑到边 $(u,v)$，若 $[1,d]$ 中存在 $u,v$ 均未使用过的颜色，则直接将 $(u,v)$ 染上该颜色。否则由于 $u,v$ 都存在未使用过的颜色，一定有 $c_1,c_2$，其中 $c_1$ 未被 $u$ 使用过而被 $v$ 使用过，$c_2$ 则反之。考虑将 $(u,v)$ 染成 $c_1$，此时产生了冲突，我们考虑将与 $v$ 相邻的被染成 $c_1$ 的边的颜色改为 $c_2$，此时还可能产生新的冲突，我们不断进行修改即可。这条 $c_1,c_2$ 的交替路径总会终止，因为这条路径不可能走回到已经走过的点上，这一点结合原图是二分图的性质很容易证明。

使用上述算法染色即可，总复杂度为 $O(m(a+b))$。

[Submission #240294476](https://codeforces.com/contest/600/submission/240294476)

---

## 作者：shao0320 (赞：1)

手玩样例，不难发现最大染色数量是度数最大的点的度数。

于是想到一个简单的构造，从一个点出发染色，染完整个联通块

然后你会发现交上去之后$47$个点你过了$45$个，被卡了。

感性理解一下就是，你随便染色很有可能到某一条边的时候，这两边的点有没用过的颜色，但是这两边未用的颜色的交集是空集。

而另一种构造方法，参考匈牙利算法，可以有效解决这个问题。

匈牙利算法是找一条边试图找到匹配，然后我们思考一个问题，如果我们每次都寻找两个节点中最小的未用过的颜色，设为$c1,c2$。那么当$c1=c2$时，是绝对没有任何问题的，但当$c1\neq c2$时，我们还是想要让$c1=c2$的，那么避免夜长梦多，我们呢就强行让$c1=c2$，然后让原来从右部节点伸出来的颜色$c1$的边断掉，再连另外一条颜色为$c2$的边，递归下去，$c2$和$c1$交替进行，以保证每个点用过的颜色都是从$1-c$。

代码：

``` cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 1005
#include<map>
#include<cstdlib>
#include<algorithm>
#include<ctime>
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int A,B,m,c,f[2][N][N],de[N*5],u[N*105],v[N*105];
void dfs(int a,int b,int x,int y,int now,int pre)
{
	int to=f[b][y][now];
	f[a][x][now]=y;
	f[b][y][now]=x;
	if(!to)
	{
		f[b][y][pre]=0;
		return;
	}
	dfs(b,a,y,to,pre,now);
}
int main()
{
	A=read();B=read();m=read();
	for(int i=1;i<=m;i++)
	{
		u[i]=read();
		v[i]=read();
		de[u[i]]++;de[v[i]+A]++;
	}
	for(int i=1;i<=m;i++)
	{
		int c1=1,c2=1;
		while(f[0][u[i]][c1])c1++;
		while(f[1][v[i]][c2])c2++;
		if(c1==c2)
		{
			f[0][u[i]][c1]=v[i];
			f[1][v[i]][c1]=u[i];
			continue;
		}
		dfs(0,1,u[i],v[i],c1,c2);
	}
	for(int i=1;i<=A+B;i++)c=max(c,de[i]);
	printf("%d\n",c);
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=c;j++)
		{
			if(f[0][u[i]][j]==v[i])
			{
				printf("%d ",j);
				break;
			}
		}
	}
	return 0;
}
```



---

## 作者：baka24 (赞：0)

模拟赛考了，不会，于是学了。

考虑答案下界是多少，显然一个点所有出边颜色不能相同，所以可以得到一个 $\max \deg(i)$ 的下界。

下通过构造来达到此下界。

以任意的顺序向图中加入边，设边 $i$ 为 $(u,v)$。那么对于点 $u$ 和点 $v$，可以分别得到这两个点上已有颜色的 $\mathrm{mex}$，设其为 $m_u$ 和 $m_v$，则对于这条边，我们暂时将其染成 $\min(m_u,m_v)$。

不妨假设 $m_u<m_v$，则此时 $i$ 边一定与 $v$ 上颜色为 $m_u$ 的边 $j$ 冲突了。于是考虑调整 $j$ 的颜色，将其调整为 $m_v$，再设 $j$ 为 $(v,k)$，则 $j$ 便有可能与 $k$ 上颜色为 $m_v$ 的点冲突，那么继续调整下去就可以了。

此时我们会调整一条链的颜色，链上的颜色会全部反转。由于这张图是一张二分图，所以肯定不会出现奇环，也就不会出现调整到自己的情况。

考虑加入一条边对颜色总数造成的影响。当 $m_u,m_v$ 均非当前最大 $\mathrm{mex}$ 时，加入一条边显然不影响答案。当 $m_u$ 或 $m_v$ 为当前最大 $\mathrm{mex}$ 时，答案会加一，而这样的边最多有 $\max \deg(u,v)$ 条，所以最后答案为 $\max \deg(i)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2010,N=100010;
int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();return x*f;}
int n,m,mt[MAXN][MAXN];
struct side{int u,v;}s[N];
int col[N];
int qry(int x){
    int it=1;
    while(mt[it][x])it++;
    return it;
}
void dfs(int id,int x,int y){
    int u=s[id].u,v=s[id].v,ID=0;
    if(mt[col[id]][u]==id)ID=mt[x][u],mt[col[id]][u]=0;
    else ID=mt[x][v],mt[col[id]][v]=0;
    mt[x][u]=mt[x][v]=id;
    col[id]=x;
    if(ID)dfs(ID,y,x);
}
void sol(int u,int v,int id){
    int x=qry(u),y=qry(v),ID=0;
    if(x<y)ID=mt[x][v],col[id]=x;
    else ID=mt[y][u],col[id]=y;
    mt[col[id]][u]=mt[col[id]][v]=id;
    if(ID)dfs(ID,x^y^col[id],col[id]);
}
void slv(){
    int x=read(),y=read();n=x+y;
    m=read();
    for(int i=1;i<=m;i++)s[i].u=read(),s[i].v=read()+x;
    for(int i=1;i<=m;i++)sol(s[i].u,s[i].v,i);
    int ans=0;
    for(int i=1;i<=m;i++)ans=max(ans,col[i]);
    printf("%lld\n",ans);
    for(int i=1;i<=m;i++)printf("%lld ",col[i]);
}
signed main(){
    freopen("1.in","r",stdin);freopen("1.out","w",stdout);
    slv();
    return 0;
}
```

---

## 作者：tanzexiaodezhonghao (赞：0)

# 思路
可以发现是一个有由 $k$ 条边组成得点集大小为 $n$ 和 $m$ 的二分图，我们要给他染色。那么染色种类最少是顶点的最大度数。

我的方法是先确定一个点的颜色，然后顺着遍历并改颜色就行了。由于长度最长为 $n+m$，$k$ 条边 $k$ 次遍历，所以复杂度为 $O((n+m)\times k)$。

[AC记录](https://codeforces.com/problemset/submission/600/291562205)
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define zhouxi2022HZO ios::sync_with_stdio(0);cin.tie(0);
const int N=114514,M=5145;
int n,m,k,color[M][M],u[N],v[N],t[N],maxans;
int XOR(int x,int y){return x ^ y;}
signed main(){
    zhouxi2022HZO;
	cin>>n>>m>>k;int zx=n+m;
	for(int i=1;i<=k;i++){
		cin>>u[i]>>v[i];
		v[i]+=n;
		t[u[i]]++;
        t[v[i]]++;
	}
	for(int i=1;i<=zx;i++) maxans=max(maxans,t[i]);
	for(int i=1;i<=k;i++){
		int x=1,y=1;
		while(color[u[i]][x])x++;
		while(color[v[i]][y])y++;
		color[u[i]][x]=v[i];
		color[v[i]][y]=u[i];
		if(x==y)continue;
		for(int j=y,l=v[i];l;l=color[l][j],j^=XOR(x,y)){
			swap(color[l][x],color[l][y]);
		}
	}
	cout<<maxans<<"\n";
	for(int i=1;i<=k;i++){
		for(int j=1;j<=maxans;j++){
			if(color[u[i]][j]==v[i]){
				cout<<j<<" ";
			}
		}
	}
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：0)

此题为二分图的最小边着色问题。

## 定义

首先定义无向图的边着色。

> 对无向图 $G$ 的边着色，要求相邻的边涂不同种颜色。
> 
> 若 $G$ 是 $k$ - 边可着色的，但不是 $\left(k - 1\right)$ - 边可着色的，则称 $k$ 是 $G$ 的边色数。记为 $\chi^{\prime}\left(G\right)$。

## Vizing 定理

若 $G$ 是简单图，那么有 $\Delta \left(G\right) \le \chi^{\prime}\left(G\right) \le \Delta \left(G\right) + 1$。

若 $G$ 是二分图，那么有 $\chi^{\prime}\left(G\right) = \Delta \left(G\right)$。

其中 $\Delta \left(G\right)$ 为 $G$ 的最大度数。

对于简单图的最优边染色方案仍然是 NP-hard 的，因此我们主要考虑 $G$ 为二分图的情况。

该定理存在两种证明方法，下面依次给出。

### 对 $\Delta G$ 进行归纳

- 对于 $D = 0$ 的情况，上述定理成立。

- 对于 $D > 0$ 的情况，我们考虑将二分图 $G$ 划分为一组匹配 $M$ 和子图 $G \setminus M$。且 $\Delta \left(G \setminus M\right) = \Delta \left(G\right) - 1$。

    首先，若该图左右部节点个数不相同，那么通过添加度数为 $0$ 的虚拟节点使得其左右部节点个数相同。接下来若其存在度数不为 $\Delta \left(G\right)$ 的节点，在该图中添加虚拟边使得满足所有节点度数均为 $\Delta \left(G\right)$，由于二分图左右两侧节点个数和度数之和均相同，因此一定可以成功构造。进而我们得到了一个正则二分图 $G^{\prime}$。

    下面我们证明对于任意 $k$ - 正则二分图，一定存在完美匹配，进而可以证明 $G^{\prime}$ 存在完美匹配。对于任意 $k$ - 正则二分图，设其左部点集合为 $L$，右部点集合为 $R$。那么我们假设其不存在完美匹配，根据 Hall 定理，一定存在一个集合 $S \subseteq L$ 满足 $\left\lvert N\left(S\right) \right\rvert < \left\lvert S \right\rvert$。同时我们可以得到 $S$ 和 $N\left(S\right)$ 之间存在 $k \times \left\lvert S \right\rvert$ 条边，而与 $N \left(S\right)$ 相接的边的数量一定不超过 $k \times \left\lvert N\left(S\right) \right\rvert$，矛盾。进而可以证明对于任意 $k$ - 正则二分图，一定存在完美匹配。

    设 $M^{\prime}$ 为 $G^{\prime}$ 的一组完美匹配，接下来我们删除 $M^{\prime}$ 的虚拟边以得到 $G$ 的匹配 $M$。由于度数为 $\Delta \left(G\right)$ 的节点一定没有虚拟边与之相连，因此对于这些节点，一定有一条与之相连的节点在匹配 $M$ 中，因此可以得出 $\Delta \left(G \setminus M\right) = \Delta \left(G\right) - 1$。

因此我们证明了对于二分图 $G$ 有 $\chi^{\prime}\left(G\right) = \Delta \left(G\right)$。可以发现上述证明过程中并没有要求二分图 $G$ 是联通的或者没有重边，因此在有重边或图不联通的情况下上述证明仍然成立。


### 构造性证明

考虑按某种顺序在二分图中依次加边，在加边的过程中维护最小边染色，通过证明一定可以完成构造来证明定理成立。

在加入边 $\left(x, y\right)$ 的时候，我们分别找到对于 $x$ 和 $y$ 找到与其相连的边集中最小的没有出现过的颜色，记为 $l_x, l_y$，此时颜色编号一定不超过 $\Delta \left(G\right)$。

若 $l_x = l_y$，那么将边 $\left(x, y\right)$ 的颜色设为 $l_x$ 即可。

否则假设 $l_x < l_y$，那么我们尝试找到一条从 $y$ 开始，颜色为 $l_x, l_y$ 交替出现的增广路。接下来我们将增广路上的边的颜色依次反转，具体的，若颜色为 $l_x$ 那么将其设为 $l_y$，若颜色为 $l_y$ 那么将其设为 $l_x$。

根据二分图的性质，若 $x$ 在增广路中当且仅当存在一条其与某个右部点连接的，颜色为 $l_x$ 的边，这与 $l_x$ 是与 $x$ 相连的边集中最小的没有出现过的颜色矛盾，进而其一定不在增广路中。因此我们可以在翻转增广路之后直接将边 $\left(x, y\right)$ 的颜色设为 $l_x$。

---

对于本题，直接使用上述构造性证明的方法构造即可。

---

