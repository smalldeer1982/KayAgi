# MST in Modulo Graph

## 题目描述

给定一个包含 $n$ 个顶点的完全图，其中第 $i$ 个顶点的权值为 $p_i$。连接顶点 $x$ 和顶点 $y$ 的边的权重等于 $\operatorname{max}(p_x, p_y) \bmod \operatorname{min}(p_x, p_y)$。

请找出连接图中所有 $n$ 个顶点的 $n - 1$ 条边组成的集合的最小总权重。

## 说明/提示

第一个测试用例中，一种可能的连接方式是选择边 $(1, 2)$、$(1, 4)$、$(1, 5)$、$(2, 3)$。第一条边的权重为 $\operatorname{max}(p_1, p_2) \bmod \operatorname{min}(p_1, p_2)=4 \bmod 3 = 1$，其他所有边的权重均为 $0$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
5
4 3 3 4 4
10
2 10 3 2 9 9 4 6 4 6
12
33 56 48 41 89 73 99 150 55 100 111 130
7
11 45 14 19 19 8 10```

### 输出

```
1
0
44
10```

# 题解

## 作者：do_it_tomorrow (赞：7)

尝试用🍍把这个题目过了，想了一个 $O(n\log n\sqrt{n})$ 的做法然后假了。

显然如果 $k\times p_x\le a\le b< (k+1)\times p_x$，那么显然应该选择 $a$ 而不是 $b$。

对于 $p$ 一样的，我们先把他们合并了，然后在找每一个倍数的区间里最小的就行了。

时间复杂度是一个调和级数，复杂度是 $O(n\log^2n)$。

[Submission #318296985 - Codeforces](https://codeforces.com/contest/2081/submission/318296985)

---

## 作者：_O_v_O_ (赞：6)

这场 div1 D<B<C 啊。

很显然不能 $O(n^2)$ 直接连边，这种题一般得考虑优化连边过程。

我们先把 $p$ 去重排序，然后我们注意到 $p$ 的值域才 $5\times10^5$，那么我们不妨这样连边：枚举 $i$，找到每一个 $k$，在 $p$ 中找到位于 $[p_i\times k,p_i\times (k+1))$ 中最小的数 $y$，设其下标为 $z$，然后在 $i\to z$ 连边权为 $y-p_i\times k$ 的一条边。

为什么这是正确的？我们假设有 $p_i$，$[p_i\times k,p_i\times (k+1))$ 中最小的数为 $b$，还有一个 $p_c>p_b$ 且 $c\in [p_i\times k,p_i\times (k+1))$，我们注意到，如果连 $i\to b$ 和 $b\to c$ 总是比连 $i\to b$ 和 $i\to c$ 好，因为两部分边权分别为 $(p_b-p_i)+(p_c-p_b)$ 和 $(p_b-p_i)+(p_c-p_i)$。得证。

连完边后跑一遍 Kruskal 即可，时间复杂度 $O(V\ln V+n\log n)$，瓶颈在于去重排序和连边。

code：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define fir first
#define sec second.first
#define trd second.second
#define pb push_back
#define piii pair<int,pair<int,int>>

const int N=5e5+5;
int n,p[N],lst[N],nxt[N],pos[N];
int fa[N],cxx[N],V;
vector<piii> v;
bool cmp(piii x,piii y){
	return x.trd<y.trd;
}
int find(int x){
	if(x==fa[x]) return x;
	else return fa[x]=find(fa[x]);
}

signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	int T;cin>>T;while(T--){
		cin>>n;V=n;
		for(int i=1;i<=n;i++){cin>>p[i];cxx[p[i]]=1;V=max(V,p[i]);}
		sort(p+1,p+n+1);n=unique(p+1,p+n+1)-p-1;
		for(int i=1;i<=n;i++) fa[i]=i,pos[p[i]]=i;
		for(int i=1;i<=V;i++){
			if(cxx[i]) lst[i]=i;
			else lst[i]=lst[i-1];
		}
		for(int i=V;i>=1;i--){
			if(cxx[i]) nxt[i]=i;
			else nxt[i]=nxt[i+1];
		}
		v.clear();
		for(int i=1;i<=n;i++){
			for(int k=1;k*p[i]<=V;k++){
				if(cxx[k*p[i]]&&k!=1){
					v.pb({pos[k*p[i]],{i,0}});
					continue;
				}
				int to=0;
				if(nxt[k*p[i]+1]<=(k+1)*p[i]) to=nxt[k*p[i]+1];
				if(!to) continue;
				v.pb({pos[to],{i,to-k*p[i]}});
			}
		}
		sort(v.begin(),v.end(),cmp);
		int ans=0;
		for(auto i:v){
			if(find(i.fir)==find(i.sec)) continue;
			fa[find(i.fir)]=find(i.sec);
			ans+=i.trd;
		}
		cout<<ans<<endl;
		for(int i=1;i<=V;i++) cxx[i]=0,pos[i]=0,lst[i]=nxt[i]=0;
	}
	return 0;
} 

```

---

## 作者：kanglr1013 (赞：2)

## MST in Modulo Graph

[双倍经验](https://www.luogu.com.cn/problem/P7789)

### 题意

给定一个包含 $n$ 个顶点的完全图，其中第 $i$ 个顶点的权重为 $p_i$。连接顶点 $x$ 和顶点 $y$ 的边的权重等于 $\operatorname{max}(p_x, p_y) \bmod \operatorname{min}(p_x, p_y)$。

请找到一组 $n - 1$ 条边，使得这组边能够连接所有 $n$ 个顶点，并且这组边的总权重最小。

### 思路

由于边数是 $\mathcal{O}(n^2)$ 级别的，我们不能直接进行连边跑 Kruskal。不难发现，其实在图中很多边是不必要或者一定不优的，我们考虑从减少连边的角度入手。

首先，对于权值相同的节点，我们可以将它们全部缩成一个点（因为两两连边代价是 0，不会产生贡献）再来考虑。假设当前枚举的点权值为 $x$，那么与它相连的边的权值一定在 $0 \sim x - 1$ 的范围内，我们考虑将其他点分成几个区间：$[x, 2x], [2x, 3x], \dots, [(k - 1)x, kx]$，其中 $\displaystyle k = \lfloor \frac{\max p_i}{x} \rfloor$。对于每一个区间，我们只向**点权最小**的那一个点连边。证明一下，如果存在 $x < y < z < 2x$，其中 $y, z$ 均指点权，那么 $x \to y, y \to z$ 一定比 $x \to y, x \to z$ 优，至于 $y \to z$ 的边，我们会在枚举 $y$ 时操作。

这样，边的数量减少到的 $\mathcal{O}(n \log n)$ 级别。再跑一个 Kruskal，总复杂度 $\mathcal{O}(n \log^2 n)$。

[My Submission](https://codeforces.com/contest/2081/submission/310972916).

---

## 作者：Priestess_SLG (赞：2)

感觉这场题质量很高的说，但是 unr 了（

考虑对于三个数 $x,y,z$，若其满足 $x\le y\le z<2x$，且现在需要组合这三个点，则此时组合 $(x,y),(y,z)$ 一定不会比组合 $(x,y),(x,z)$ 差。

因此这个题就做完了。对于每一个 $i$ 枚举其 $j$ 倍然后找到所有在 $[a_ij,a_i(j+1))$ 之间的点中最小的值和其连边，此时边数是调和级数的。直接暴力建图跑 Kruskal 时间复杂度为 $O(n\log^2n)$ 可以通过。

[代码](https://codeforces.com/contest/2081/submission/311525872)。

---

## 作者：_Kamisato_Ayaka_ (赞：1)

## Statement

有一个 $n$ 个点的完全图，每个点有权值 $p_i$，连接 $(u,v)$ 的边权值为 $\max(p_u,p_v) \bmod \min(p_u,p_v)$。

求最小生成树上边权和。

## Solution

想使用 Kruskal 但你发现边数 $n^2$，显然需要优化。

当 $p_u = p_v$ 时 $(u,v)$ 这条边无贡献，权值为 $0$，也就是说我们需要将这类相同权值的点缩点，也就是对点权离散化。

假设我们当前点权 $p_x$，假设它与 $p_y$ 连边且 $p_x < p_y$，边权就是 $0 \sim p_x - 1$ 中的某数，这样看来我们要考虑的点权就是 $[kx, (k + 1)x], k\in [1,\lfloor{\frac{\max{p_i}}{p_x}}\rfloor]$ 这样的区间，即枚举 $p_x$ 的正整数倍去找与之匹配的点。

每次从每个区间最小的点依次连严格大于它的点连边，即对于 $a < b < c < 2a$，我们连的边一定是 $(a,b),(b,c)$ 而不是 $(a,b),(a,c)$，后者不优。

边数就来到了 $\log n$ 级别，再用 Kruskal 就是 $O(n\log^2 n)$，开了三秒是跑得过的。

## Code

[Submission](https://codeforces.com/contest/2081/submission/310992493)

---

