# 電報

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2016/tasks/joisc2016_i


给出 $N$ 个点，每个点的出度均为 $1$，给出这 $N$ 个点初始指向的点 $A_i$，和改变这个点指向的目标所需要的价值 $C_i$。

求让所有点强连通的最小花费。

## 说明/提示

$2 \le N \le 10^5, 1 \le A_i \le N, A_i \ne i, 1 \le C_i \le 10^9$

## 样例 #1

### 输入

```
4
2 2
1 4
1 3
3 1```

### 输出

```
4```

## 样例 #2

### 输入

```
4
2 2
1 6
1 3
3 1```

### 输出

```
5```

## 样例 #3

### 输入

```
4
2 2
1 3
4 2
3 3```

### 输出

```
4```

## 样例 #4

### 输入

```
3
2 1
3 1
1 1```

### 输出

```
0```

# 题解

## 作者：lingying (赞：1)

## 题意

给定 $n$ 个点，每个点有且仅有一条出边指向 $A_i$，改变这条出边的指向需要花 $C_i$ 的代价，问把所有点强连通的最小代价。

## 解法

每个点仅有一条出边，又要强联通，那么肯定是一个环。所以我们实质上要把所有点的入度都平衡为 $1$。

一个贪心的想法，我们对于每一个点 $u$，假设 $u$ 有多条入边，那么我们保留所花代价最大的那一条，其余的全部删掉。

但是这样子不能保证删完后是合法的。例如如下一种情况：

```
4
2 3
3 5
4 5
2 5
```

我们发现 $2$ 有两条入边，按照贪心策略应该断开 $1$ 和 $2$ 的这条边，但是我们发现断开过后就不合法了，而必须去断开 $2$ 和 $4$ 的这条边。

所以这个贪心需要再加上一个限制：保持刚才的贪心策略不变，但是我们必须保证对于一个环不能全保留环边，需要断开至少一条环边。当然这里要特判 $n$ 个点本身就是一个环。

具体地，假设 $mx_i$ 表示所有连向 $i$ 的边中代价最大的，$tmx_i$ 表示所有连向 $i$ 且不属于 $i$ 所属环的边中代价最大的。对于一个环我们肯定贪心选择 $mx_i-tmx_i$ 最小的。

时间复杂度为 $O(n)$。

## 代码

```
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1e5+5;
const int inf=0x3f3f3f3f;

int n;
int nxt[N],c[N],mx[N],tmx[N],col[N];
ll ans;
bool mark[N],vis[N];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&nxt[i],&c[i]);
	for(int i=1;i<=n;i++)ans+=c[i];
	for(int i=1;i<=n;i++)mx[nxt[i]]=max(mx[nxt[i]],c[i]);
	for(int i=1;i<=n;i++)if(!col[i])
	{
		int u;
		for(u=i;!col[u];u=nxt[u])col[u]=i;
		if(col[u]==i)
		{
			int cnt=0;
			for(int v=u;!mark[v];v=nxt[v])mark[v]=1,cnt++;;
			if(cnt==n)return putchar('0'),putchar('\n'),0;
		}
	}
	for(int i=1;i<=n;i++)
		if(!mark[i])
			tmx[nxt[i]]=max(tmx[nxt[i]],c[i]);
	for(int i=1;i<=n;i++)ans-=mx[i];
	for(int i=1;i<=n;i++)if(mark[i]&&!vis[i])
	{
		int mn=inf;
		for(int u=i;!vis[u];u=nxt[u])vis[u]=1,mn=min(mn,mx[u]-tmx[u]);
		ans+=mn;
	}
	cout<<ans,putchar('\n');
	return 0;
}
```



---

## 作者：Priestess_SLG (赞：0)

考虑什么时候图合法。很显然，当且仅当图有且仅有一个环构成时图合法。更确切的说，一个图合法当且仅当：

+ 将所有的单向边扩展为双向边后图连通。
+ 图中任意一个点 $u$ 的入度为 $1$。

因此首先特判掉图已经合法的情况，剩下的情况图是一个基环森林，需要将森林中的每一个基环树都经过若干次操作使得该树中所有结点都只保留一条入边。有一个显然的贪心是说对于每一个点记录其入边所有边需要修改的权值，然后对于每一个入度 $>1$ 的点保留边权最大的入边，其余的入边删去。但是这个贪心其实是错的，此时图有可能成为若干个不连通的环。因此考虑在贪心中叠加一个条件：对于每一个环，至少需要更新一条环上的边，使其连向另一个环。

根据上述贪心策略模拟即可。时间复杂度为线性。

---

## 作者：RedLycoris (赞：0)

题目意思很清楚不解释。

我们一共有 $n$ 个点，但只有 $n$ 条有向边，还想让这张图强连通，显然是要求我们把这张图变为一个环。

稍微思考一下即可发现，这个题目等价于保留代价最大的那些链，然后删掉剩余的边进行缝缝补补。（因为最后是要变为一个环，换上每个点的入读和出度均为 $1$，如果保留的不是链的形式那么肯定有点出度或者入度大于 $1$，肯定不合法）

回头看看这个图。$n$ 个点，$n$ 条边，是一个基环树的形式。按照套路把环和树分开来看。

对于一个树点，由于要删掉大部分边使得它的入度变为 $1$，我们就可以只保留到它的边权最大的那条边。

由于这张图可能是个基环树森林，我们需要把所有的环也拼接起来，所以说，每个环上至少要断开一个点。

对于一个环，我们令 $mx_i$ 表示点 $i$ 的所有树节点儿子到 $i$ 的那条边上权值的最大值，$sum_i$ 为这些权值的和。令 $val_i$ 表示环上指向 $i$ 的那个点到 $i$ 的这条边的边权。

统计 $cnt$ 为对于一个环 $ring$ 上面的点，满足 $val_i<mx_i$ 的点的个数。

如果这个环的 $cnt > 0$，那么我们想不断白不断（管它是环点还是树点，都只能有一条入边，且断了环边仍是合法的）。

如果这个环的 $cnt=0$，那么为了满足“每个环至少要断开一个点”这个条件，我们就要找到 $val_i-mx_i$ 最小的那个点断开，使得代价最小。

ps. 有一个特例，整张图只有一个大环，且这个大环包括了所有点的时候，它既不需要和其他环拼接，也不需要让其他树点挤进来，所以答案就是 $0$。

Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
using namespace std;
const int mxn=2e5+5;
vector<int>g[mxn];
vector<pair<int,int> >tos[mxn];
int n,a[mxn],c[mxn];
int used[mxn],cused;
int ord[mxn],cord;
int inring[mxn];
int sum[mxn],ma[mxn];
vector<vector<int> >rings;
inline void dfs(int x){
	if(used[x]==cused){//find a ring
		ord[++cord]=x;
		vector<int>ring;
		for(int i=cord-1;i;--i){
			inring[ord[i]]=1;
			ring.push_back(ord[i]);
			if(ord[i]==x)break;
		}
		rings.push_back(ring);
		return;
	}
	if(used[x])return;
	ord[++cord]=x;
	used[x]=cused;
	dfs(a[x]);
	--cord;
}
signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i]>>c[i];
		g[i].push_back(a[i]);
		tos[a[i]].push_back({i,c[i]});
	}
	for(int i=1;i<=n;++i){
		if(!used[i]){
			++cused;
			cord=0;
			dfs(i);
		}
	}
	if(rings.size()==1 and rings[0].size()==n){
		cout<<0<<endl;
		return 0;
	}
	ll ans=0;
	for(int i=1;i<=n;++i){
		if(!inring[i]){
			int mx=0,sm=0;
			for(auto p:tos[i]){
				mx=max(mx,p.second);
				sm+=p.second;
			}
			ans+=sm-mx;
		}
	}
	for(vector<int>ring:rings){
		ll tot=0;
		int cnt=0,tval,delta=0;
		for(int i:ring){
			int mx=0,sm=0;
			for(auto p:tos[i]){
				if(!inring[p.first]){
					mx=max(mx,p.second);
					sm+=p.second;
				}else tval=c[p.first];
			}
			ma[i]=mx;
			sum[i]=sm;
			tot+=sum[i];
			if(tval<mx)++cnt,delta+=mx-tval;
		}
		if(cnt==0){
			ll res=11451491919810;
			for(int i:ring){
				int j=a[i];
				res=min(res,tot-ma[j]+c[i]);
			}
			ans+=res;			
		}else ans+=tot-delta;
	}
	cout<<ans<<endl;
}
```

---

