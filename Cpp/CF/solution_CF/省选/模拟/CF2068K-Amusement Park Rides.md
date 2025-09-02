# Amusement Park Rides

## 题目描述

Ivan、Dmitrii 和 Pjotr 正在一个有 $n$ 个游乐设施的游乐园庆祝 Ivan 的生日。第 $i$ 个设施会在每分钟 $a_i, 2a_i, 3a_i, \dots$（即每隔 $a_i$ 分钟）运行一次。

每分钟，三位朋友可以选择一起乘坐一个可用的设施或等待。由于设施运行时间极短，他们可以在下一分钟立即乘坐其他设施。他们可以按任意顺序乘坐设施。

他们希望在享用生日蛋糕前体验所有设施各一次。求他们完成所有 $n$ 个设施的最早时间。

## 说明/提示

第一个测试用例中，三人可以在第 $i$ 分钟乘坐第 $i$ 个设施。由于共有 $4$ 个设施，总时间为 $4$ 分钟。

第三个测试用例中，三人按顺序在第 $1, 2, 3, 4, 6, 8$ 分钟乘坐设施，总时间为 $8$ 分钟。可以证明无法更早完成。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
4
1 2 3 4
4
1 1 1 1
6
1 2 1 2 2 2```

### 输出

```
4
4
8```

# 题解

## 作者：happybob (赞：2)

考虑一个暴力的模型：首先将 $a_i$ 相等的点缩一起，假设有 $q_i$ 个 $a=p_i$，连边 $S \rightarrow i$，容量为 $q_i$。另外，对于每个时刻 $i > 0$，建立点 $t_i$，对于所有 $p_j \mid i$，连边 $j \rightarrow t_i$，容量为 $1$，另外连边 $t_i \rightarrow T$，容量为 $1$。可以发现在 $i$ 时刻内有解当且仅当只保留 $t_1,t_2,\cdots,t_i$ 这些点和对应的边后最大流为 $n$。

直接加虚点的复杂度和答案大小有关，无法通过。

注意到我们可以只建立部分虚点，具体地，每次取最小的需要建立虚点的时刻 $i$，加入点 $t_i$ 后判断最大流是否增加。若增加，将 $i + p_j$ 也设为需要建立虚点的时刻，其中 $p_j \mid i$。不难证明这样做的正确性。

可以证明复杂度为 $O(n^2\log n)$。

---

## 作者：Da_Vinci (赞：0)

朴素的思路就是将每个 $a_i$ 作为一个二分图的左部点，将时间作为右部点，逐个加入时间，当存在完美匹配（即使用最大流求解二分图匹配时流量为 $n$）的时候输出最后一个加入的时间作为答案，因为时间的值域很大，复杂度显然爆炸。

发现我们加入的那些代表时间的点很多都是没有用的，如果找到一种方法使得加入的右部点的数量在可接受的范围内，就可以通过。

先使用一个桶来统计 $a_1,a_2,\cdots,a_n$ 中出现的不同值，记为 $p_1,p_2,\cdots,p_n$，以及它们在 $a_1,a_2,\cdots,a_n$ 中各自出现的次数 $q_1,q_2,\cdots,q_n$。建立只有 $S,T$ 和左部点的流，对于 $\forall i\in[1,k]$ 从 $S$ 向 $i$ 连一条流量为 $q_i$ 的边。

接下来使用一个 `std::map<ll,std::set<int> >` 来维护要加入的右部点的值，以及这个右部点所可以连接的左部点。具体方法如下：

- 初始时对于 $\forall i\in[1,k]$，将 $(p_i,\{i\})$ 插入 `std::map` 中，代表值为 $p_i$ 的右部点可以与左部点 $i$ 相连。
- 然后重复如下过程直到流量为 $n$：
- 取出 `std::map` 中 `key` 最小的键值对，记为 $(x,s_x)$ 并且用 $x$ 来更新答案。
- 新建一个右部点 $v_x$ 代表 $x$，并将 $v_x$ 和 $T$，集合 $s_x$ 中的左部点和 $v_x$ 都连上流量为 $1$ 的边。
- 尝试扩展最大流，如果加入 $v_x$ 之后最大流增大了，就把 $\forall y\in s_x$ 插入到 $s_{x+p_y}$ 中。
- 最后删除键值对 $(x,s_x)$。

像这样操作，加入的右部点的数量就是 $O(n\log n)$ 级别的，显著优化了复杂度，总复杂度 $O(n^2\log n)$。

参考实现：

```cpp
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
#define il inline
#define ll long long
#define lll __int128
#define ull unsigned long long
#define ld long double
#define db double
#define gc getchar();
#define pc(x) putchar(x)
#define O(x) cout<<x<<'\n';
#define adde(x,y) emplace_back(make_pair(x,y))
#define ep emplace
#define eb emplace_back
#define mp make_pair

#define pbset(typ) tree< typ ,null_type,std::less< typ >, __gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>
#define pbmap(typ1,typ2) tree< typ1 , typ2 ,std::less< typ1 >, __gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>

namespace constant_warrior{
	template<typename T> inline void fr(T& num){
		num=0;short sign=1;char ch=std::getchar();
		while(ch<'0'||ch>'9'){
			if(ch=='-')sign=-1;
			ch=std::getchar();
		}
		while(ch>='0'&&ch<='9')num=num*10+ch-'0',ch=getchar();
		num=num*sign;
	}
	template<typename T>inline void fw(T x){
		if(x<0)std::putchar('-'),x=-x;
		if(x>9)fw(x/10);
		std::putchar(x%10+'0');
	}
	template<typename T>inline const T& maxf(const T& a,const T& b){
		if(a>b)return a;
		return b;
	}
	template<typename T>inline const T& minf(const T& a,const T& b){
		if(a>b)return b;
		return a;
	}
	template<typename T>inline void swapf(T& a,T& b){
		a^=b^=a^=b;
	}
	template<typename T, typename... Args> inline void fr(T &x, Args&... args) {
		fr(x);
		fr(args...);
	}
}
using namespace constant_warrior;
const int N=1<<14,M=1048576,K=1024,inf=0x3f3f3f3f;
int n,a[N],s,t;
map<int,int> tong;
int p[N],q[N],tot,vc;
struct edge{
	int to,wt,nxt;
}e[M];
int head[N],d[N],now[N],cnt=1;
inline void add(int x,int y,int z){
	e[++cnt]=(edge){y,z,head[x]},head[x]=cnt;
	e[++cnt]=(edge){x,0,head[y]},head[y]=cnt;
}
inline bool bfs(){
	queue<int> q;
	memset(d,0,sizeof d);
	q.emplace(s);
	d[s]=1,now[s]=head[s];
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=head[x];i;i=e[i].nxt){
			if(e[i].wt&&!d[e[i].to]){
				q.emplace(e[i].to);
				now[e[i].to]=head[e[i].to];
				d[e[i].to]=d[x]+1;
				if(e[i].to==t)return 1;
			}
		}
	}
	return 0;
}
inline int dinic(int x,int flow){
	if(x==t)return flow;
	int rest=flow,k,i;
	for(i=now[x];i&&rest;i=e[i].nxt){
		now[x]=i;
		if(e[i].wt&&d[e[i].to]==d[x]+1){
			k=dinic(e[i].to,min(rest,e[i].wt));
			if(!k)d[e[i].to]=0;
			e[i].wt-=k,e[i^1].wt+=k,rest-=k;
		}
	}
	return flow-rest;
}
inline int maxflow(){
	int flow=0,res=0;
	while(bfs()){
		while(flow=dinic(s,inf)){
			res+=flow;
		}
	}
	return res;
}
map<ll,set<ll> > ms;
#define mi map<ll,set<ll> >::iterator

void solve(){
	fr(n),vc=n;
	s=++vc,t=++vc;
	for(int i=1;i<=n;i++){
		fr(a[i]);
		tong[a[i]]++;
	}
	for(auto [i,j]:tong){
		p[++tot]=i;
		q[tot]=j;
		add(s,tot,q[tot]);
		ms[p[tot]].emplace(tot);
	}
	tong.clear();
	int fl=0;
	ll res=0;
	while(fl<n){
		mi i=ms.begin();
//		cerr<<i->first<<'\n';
		res=max(res,i->first);
		add(++vc,t,1);
		for(auto j:i->second){
			add(j,vc,1);
		}
		int f=maxflow();
		if(f){
			fl+=f;
			for(auto j:i->second){
				ms[i->first+p[j]].emplace(j);
			}
		}
		ms.erase(i);
	}
//	cerr<<"R: ";
	fw(res),pc('\n');
	for(int i=1;i<=vc;i++)head[i]=now[i]=0;
	ms.clear();
	tot=vc=0,cnt=1;
}
int main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	int T=1;cin>>T;
	while(T-->0)solve();
}
```

---

