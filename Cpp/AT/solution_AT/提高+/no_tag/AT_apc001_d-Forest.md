# Forest

## 题目描述

[problemUrl]: https://atcoder.jp/contests/apc001/tasks/apc001_d

$ N $ 頂点 $ M $ 辺の森が与えられます。頂点には $ 0 $ から $ N-1 $ の番号がついています。 辺は $ (x_i,y_i) $ の形で与えられます。これは頂点 $ x_i $ と $ y_i $ が辺でつながっていることを意味します。

各頂点 $ i $ には $ a_i $ という値が定まっています。 あなたは与えられた森に辺を追加して連結にしたいです。 辺を追加するときには、まず異なる頂点二つを選択し( $ i $ , $ j $ とする)、 $ i $ と $ j $ の間に辺を張ります。 この時コストが $ a_i+a_j $ かかります。そしてこれ以降，頂点 $ i $ と $ j $ は永遠に選択できなくなります。

森を連結にする最小コストを求めてください。 連結にするのが不可能な場合は`Impossible`と出力してください。

## 说明/提示

### 制約

- $ 1\ <\ =\ N\ <\ =\ 100,000 $
- $ 0\ <\ =\ M\ <\ =\ N-1 $
- $ 1\ <\ =\ a_i\ <\ =\ 10^9 $
- $ 0\ <\ =\ x_i,y_i\ <\ =\ N-1 $
- 与えられるグラフは森
- 入力は全て整数

### Sample Explanation 1

頂点 $ 0 $, $ 5 $ をつなぐとグラフが連結になり，この時かかるコストは $ 1\ +\ 6\ =\ 7 $ です。

### Sample Explanation 2

どのように辺を追加してもグラフを連結にすることはできません。

### Sample Explanation 3

最初からグラフは連結であるので，辺を追加する必要はありません。

## 样例 #1

### 输入

```
7 5
1 2 3 4 5 6 7
3 0
4 0
1 2
1 3
5 6```

### 输出

```
7```

## 样例 #2

### 输入

```
5 0
3 1 4 1 5```

### 输出

```
Impossible```

## 样例 #3

### 输入

```
1 0
5```

### 输出

```
0```

# 题解

## 作者：xukuan (赞：2)

首先这题不知为什么，洛谷比Atcoder少了一组样例：

Sample Input 3
```pascal
1 0
5
```
Sample Output 3
```pascal
0
```

希望管理员加上，谢谢

**思路：并查集+贪心**

用并查集维护连通块，然后贪心

设有tot个连通块，所以要选$2(tot-1)$个点。

在每个联通块里找到一个权值最小的点，剩下的点按权值从小到大排序，选前$tot−2$个。

如果剩下的点不足$tot-2$个，直接Impossible，否则输出答案

注意如果原图已经联通时要直接输出0，这个在没有爬的一组样例里面说明的很明显。~~要不是去了一趟AT我估计不会想到还有这个问题~~

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
#define N 100010
using namespace std;

ll n,m,tot,ans,a[N],father[N],cnt[N];
//tot表示连通块个数
//a表示每个点的权值
//father表示并查集的父节点
//cnt表示连通块i对应的q是哪个
vector<ll> t,q[N];
//t表示前tot个点选完之后剩下的
//q[i]表示第i个连通块里的点的权值

inline ll read(){//读入优化
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

ll searchfather(ll v){//并查集
	if(father[v]==v) return father[v];
	return father[v]=searchfather(father[v]);
}

int main(){
	n=read(); m=read();
	for(ll i=1; i<=n; i++){
		a[i]=read();
		father[i]=i;
	}
	while(m--){
		ll x=read()+1,y=read()+1;
		ll f1=searchfather(x),f2=searchfather(y);
		if(father[f1]!=f2) father[f1]=f2;
	}
	for(ll i=1; i<=n; i++){
		father[i]=searchfather(i);
		if(!cnt[father[i]]) cnt[father[i]]=++tot;//当前连通块没有被统计
		q[cnt[father[i]]].push_back(a[i]);//加入权值
	}
	if(tot==1) return printf("0\n")&0;//图已经联通了
	for(ll i=1; i<=tot; i++) sort(q[i].begin(),q[i].end());//排序
	for(ll i=1; i<=tot; i++) ans+=q[i][0];//取走第一个
	for(ll i=1; i<=tot; i++){
		for(ll j=1; j<q[i].size(); j++) t.push_back(q[i][j]);//从第二个开始往后取
	}
	sort(t.begin(),t.end());
	if(t.size()<tot-2) return printf("Impossible\n")&0;//不够
	for(ll i=0; i<tot-2; i++) ans+=t[i];
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：yanxu_cn (赞：1)

一个比较缝合的简单题。

## 需要知道的前置芝士
并查集。

## 做法
先使用并查集分析这个森林。对于每一棵树，我们先选择其中开销最小的点，因为每棵树至少得选一个。然后在再在剩下的点当中选择开销最小的 $k$ 个点。我们设有 $n$ 棵树，那么至少要选 $n-2$ 个其他的结点。如果剩下的结点数都不足 $n-2$ 个了，那么无解。

## 代码
```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/tag_and_trait.hpp>
#define int long long
using namespace std;
using namespace __gnu_pbds;
tree<int,tree<pair<int,int>,null_type,less<pair<int,int>>,rb_tree_tag,tree_order_statistics_node_update>,less<int>,rb_tree_tag>mp;
constexpr int maxn=100007;
vector<int>vc;
int a[maxn];
#define imp ("Impossible\n")
struct dsu
{
	private:
	vector<int>fa;
	public:
	dsu(int n)
	{
		fa.reserve(n+7);
		for(int i=0;i<=n;i++)
		fa.push_back(i);
	}
	int find(int x)
	{
		if(fa[x]==x)return x;
		return fa[x]=find(fa[x]);
	}
	inline void merge(int x,int y)
	{
		fa[find(y)]=find(x);
	}
};
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n,m,u,v,ans=0;
	cin>>n>>m;
	dsu d(n);
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	for(int i=0;i<m;i++)
	{
		cin>>u>>v;
		d.merge(u,v);
	}
	for(int i=0;i<n;i++)
	{
		mp[d.find(i)].insert({a[i],i});
	}
	for(auto i:mp)
	{
		ans+=i.second.find_by_order(0)->first;
		i.second.erase(i.second.find_by_order(0));
		for(auto j:i.second)
		{
			vc.push_back(j.first);
		}
	}
	if(mp.size()==1)
	{
		cout<<0<<'\n';
		exit(0);
	}
	if(vc.size()<mp.size()-2)
	{
		cout<<imp;
		exit((signed)0);
	}
	sort(vc.begin(),vc.end());
	for(int i=0;i<mp.size()-2;i++)
	ans+=vc[i];
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：hhoppitree (赞：0)

#### 题意简述

给定一片由 $N$ 个点和 $M$ 条边组成的森林 $G$，每个点有点权，其中第 $i$ 个点的点权为 $a_i$，现在需要加上若干条边，其中连接第 $i$ 个点与第 $j$ 个点的花费为 $a_i+a_j$，任意新加的两条边之间不能有公共端点，求将这片森林连通的最小花费或输出无法联通这片森林。

对于全部数据，$N\le10^5$。

#### 题目解法

显然可以**把贡献拆到点权**上去，记第 $i$ 个点被计入了答案 $c_i\small(c_i\in\{0,1\})$ 次，则最终花费即为 $\sum\limits_{i=1}^{N}a_ic_i$，这指导着我们**考虑一个给定的 $\boldsymbol c$ 是否可行**，因为对于相同的 $c$，所对应的花费是一样的。

我们显然有 $\sum\limits_{i=1}^{N}c_i=2(N-1-M)$ 且对于每个连通块，其中所有的点的 $c_i$ 的和不为 $0$，我们猜测**其为充要条件**。

实际上，这相当于给定一棵有 $N$ 个点的树每个点的度数，保证每个点的度数 $d_i$ 均为正整数且总和为 $2(N-1)$，可以通过数学归纳法来证明对任意满足以上条件的 $d$，均存在一种方案将它们连成一棵树：

- 当 $N\le2$，原命题显然成立；
- 当 $N=x-1$ 存在方案时，下面来证明 $N=x$ 时一定有解： 
  由于 $\sum\limits_{i=1}^{N}d_i=N-1$ 且 $d$ 均为正整数，所以必然存在 $d_i=1$ 以及 $d_j>1$，将 $i$ 与 $j$ 连边，则原命题转化为 $N=x-1$ 时的命题，故对于任意正整数 $N$ 以及 $d$，均存在一种方案将它们连成一棵树。

所以可以采用**贪心**的方法，先将每个连通块内最小的 $a_i$ 选出来，把这些点去掉后选取剩余数中最小的 $N-2$ 个 $a_i$ 即可（如果不足那么输出无解），时间复杂度 $\mathcal{O}(n\log n)$。

#### 总结

将边权转化为点权对花费的贡献，再对花费相同的方案进行简化处理，然后大胆猜想充要条件，最后贪心计算即可。

---

## 作者：PCCP (赞：0)

## 思路

考虑到我们的权值是两点点权相加的形式，所以可知我们到底怎么连边不重要，只要每一个连通块都有点被选上，那这个连通块就一定被连通了。

但是题目要求一个点只能选一次，由于把 $ cnt $ 个连通块需要 $ cnt-1 $ 条边，那就要 $ 2\times cnt -2 $ 个不同点，如果没有那么多点，就无解。

有解的话，先取每个连通块最小的点。剩下 $ cnt-2 $ 个点从余下的点里取最优的即可。

## 代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<stack>
#include<list>
#include<set>
using namespace std;
typedef pair<int,int> PII;
const int N=1e5+10;
int n,m,a[N],fa[N],blocnt;
int he[N],ne[N<<1],to[N<<1],tot=1;
long long ans;
bool st[N];
void addedge(int x,int y){
	to[++tot]=y;
	ne[tot]=he[x];
	he[x]=tot;
}
priority_queue<int,vector<int>,greater<int> > q;
vector<int> blo[N];
int find(int x){
	if(x==fa[x]){
		return x;
	}
	return fa[x]=find(fa[x]);
}
void unify(int x,int y){
	fa[find(y)]=find(x);
}
void dfs1(int x,int f,int r){
	blo[r].push_back(a[x]);
	st[x]=true;
	unify(r,x);
	for(int i=he[x];i;i=ne[i]){
		int v=to[i];
		if(v==f){
			continue;
		}
		dfs1(v,x,r);
	}
}
int main(){
//	freopen("sample5.in","r",stdin);
//	freopen("T1.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		fa[i]=i;
	}
	int x,y;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		++x,++y;
		addedge(x,y);
		addedge(y,x);
	}
	for(int i=1;i<=n;i++){
		if(!st[i]){
			dfs1(i,0,i);
			++blocnt;
		}
	}
	if(n<(blocnt<<1)-2){
		puts("Impossible");
		return 0;
	}
	if(blocnt==1){
		puts("0");
		return 0;
	}
	for(int i=1;i<=n;i++){
		st[i]=false;
	}
	vector<int>::iterator it;
	for(int i=1;i<=n;i++){
		x=find(i);
		if(!st[x]){
			st[x]=true;
			sort(blo[x].begin(),blo[i].end());
			it=blo[i].begin();
			ans+=*it;
			++it;
			for(it;it!=blo[i].end();it++){
				q.push(*it);
			}
		}
	}
	for(int i=1;i<=blocnt-2;i++){
		ans+=q.top();
		q.pop();
	}
	printf("%lld\n",ans);
}
```


---

## 作者：jiangbojun (赞：0)

# Forest

直接贪心。

设有k个联通块。

由于每个点只能选一次，所有的联通块形成一个树，所以一共要选$2(k-1)$个点

在每个联通块里找到一个权值最小的点，共k个点，以保证最终每个块都被选了。

剩下的点从小到大排序，选前$k-2$个。

---

