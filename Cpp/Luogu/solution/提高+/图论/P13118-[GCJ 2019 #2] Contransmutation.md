# [GCJ 2019 #2] Contransmutation

## 题目描述

去年，我们曾请你帮忙将昂贵的金属转化为铅。（你无需了解前一道题即可解答本题。）但你们国家的领导人依然贪婪地渴望获得更多的铅！

世界上已知有 $\mathbf{M}$ 种金属；在你的元素周期表上，铅是第 1 号金属。你们国家的领导人要求你利用国库中的金属，尽可能多地制造铅。

对于每种金属（包括铅），你都知道恰好有一种配方，可以消耗 1 克该金属，并各生成 1 克另外两种金属。（关于质量守恒原理，最好不要深究！）注意，第 $i$ 种金属的配方可能会生成第 $i$ 种金属本身作为产物之一。配方不能对部分克数的金属起作用。然而，只要你拥有所需金属的 1 克，你可以任意多次（或不使用）使用每种配方。

如果你做出最优选择，最终最多能获得多少克铅，或者说这个数量是否没有上限？如果没有上限：由于输出可能非常大，我们只要求你输出结果除以质数 $10^9+7$（即 $1000000007$）的余数。

## 说明/提示

**样例解释**

在样例 1 中，你有一个配方可以将 1 克铅变为 1 克铅和 1 克第二种金属，另一个配方可以将 1 克第二种金属变为 1 克铅和 1 克第二种金属。你可以交替使用这两个配方，制造出任意多的两种金属。

样例 2 的配方与样例 1 相同，但你一开始没有任何金属！

样例 3 中，所有配方都无法帮助你制造更多的铅，因此你最终获得的铅不会超过初始拥有的数量。

**数据范围**

- 对所有 $i$，$1 \leq \mathbf{R_{i1}} < \mathbf{R_{i2}} \leq \mathbf{M}$。

**测试点 1（7 分，公开）**

- $1 \leq \mathbf{T} \leq 100$。
- $2 \leq \mathbf{M} \leq 10$。
- $0 \leq \mathbf{G_i} \leq 10$。

**测试点 2（16 分，隐藏）**

- $1 \leq \mathbf{T} \leq 100$。
- $2 \leq \mathbf{M} \leq 100$。
- $0 \leq \mathbf{G_i} \leq 10^9$。

**测试点 3（6 分，隐藏）**

- $1 \leq \mathbf{T} \leq 5$。
- $2 \leq \mathbf{M} \leq 10^5$。
- $0 \leq \mathbf{G_i} \leq 10^9$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2
1 2
1 2
1 0
2
1 2
1 2
0 0
4
2 4
3 4
2 4
2 3
10 10 10 10```

### 输出

```
Case #1: UNBOUNDED
Case #2: 0
Case #3: 10```

# 题解

## 作者：zhuweiqi (赞：0)

我愿称之为神题。就凭这道题的细节程度我认为评紫都不过分。

首先，这题大致的一个思路并不难：先缩点，然后做一遍拓扑排序，如果能够生产无限的金属则标记为 $-1$。所以我们先来解决判无限的问题。

易错点 $1$：认为只要这个强连通分量点数大于一个且这个强连通分量里面有金属原料，则这个强连通分量所有金属都能够无限生产。

原因：假如这个强连通分量是由一个环构成的，我们发现强连通分量内部的金属该生成多少还是只能生成多少，并不能做到无限生产（容易证明这个条件是**充要**的）。但无论如何**其后继节点一定可以无限生产**。

解决方案：可以判断强连通分量内部边数与点数的大小关系，因为每个点原来的两条边中一定有一条是内部边（假设强连通分量大小大于一，等于一后面会说），所有假如一个点的两条边全是内部边，强连通分量必不可能由一个环构成。

易错点 $2$：自环边的处理。

解决方案：若一个点有自环且其是独立的一个强连通分量，则打标记归为上述情况处理。否则，说明其两条边都是内部边，已经被归为了非单环构成的强连通分量处理。

易错点 $3$：有无金属原料的处理。

原因：由于答案需要取模，取模之后金属数量有可能变为 $0$，但实则是有原料的，需要单开一个布尔数组解决。实测数据中真有卡这种情况的。

**数组较多又是多测，所以记得仔细清空。**

Code：（代码稍微丑了点，见谅）


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100002,mod=1e9+7;
vector<int> e[N];
int num=0,tp=0,a[N],sd[N],dfn[N],low[N],s[N],ins[N],siz[N],rd[N],fg[N],dh[N],hav[N];
ll cnt[N];
struct edge{
	int x,y;
}ee[N<<1];
void Tarjan(int x){
	low[x]=dfn[x]=++num;
	s[++tp]=x,ins[x]=1;
	for(auto y:e[x]){
		if(!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(ins[y]) low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]){
		int y;cnt[x]=siz[x]=0;
		while(y=s[tp]){
			sd[y]=x,cnt[x]+=a[y],ins[y]=0,tp--,siz[x]++;
			if(y==x) break;
		}
	}
	return;
}
queue<int> q;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	for(int cas=1;cas<=T;cas++){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			int x,y;
			cin>>x>>y;
			if(i==x || i==y) dh[i]=1;
			e[i].emplace_back(x);
			e[i].emplace_back(y);
			ee[(i<<1)-1].x=ee[i<<1].x=i;
			ee[(i<<1)-1].y=x,ee[i<<1].y=y;
		}
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i);
		for(int i=1;i<=(n<<1);i++) ee[i].x=sd[ee[i].x],ee[i].y=sd[ee[i].y];
		for(int i=1;i<=n;i++) e[i].clear(),rd[i]=0;
		for(int i=1;i<=(n<<1);i++){
			int x=ee[i].x,y=ee[i].y;
			if(x!=y){
				e[x].emplace_back(y);
				rd[y]++;
			}
			else if(i%2==1 && ee[i+1].x==ee[i+1].y) fg[x]=1;
		}
		for(int i=1;i<=n;i++) if(sd[i]==i && !rd[i]) q.push(i);
		while(!q.empty()){
			int x=q.front();q.pop();
			hav[x]=hav[x]|(cnt[x]!=0);
			if(siz[x]>1 && hav[x] && fg[x]) cnt[x]=-1;
			bool unl=0;
			if(hav[x] && (dh[x] || siz[x]>1) || cnt[x]==-1) unl=1;
			if(x==1) break;
			for(auto y:e[x]){
				if(unl) cnt[y]=-1;
				else if(cnt[y]!=-1) cnt[y]=(cnt[x]+cnt[y])%mod;
				if(!--rd[y]) q.push(y);
				hav[y]=hav[y]|hav[x];
			}
		}
		cout<<"Case #"<<cas<<": ";
		if(cnt[1]==-1) cout<<"UNBOUNDED\n";
		else cout<<cnt[1]%mod<<"\n";
		while(!q.empty()) q.pop();
		for(int i=1;i<=n;i++) e[i].clear(),dfn[i]=0,fg[i]=0,dh[i]=0,hav[i]=0;
	}
	return 0;
}
```

---

