# [PA 2019] Podatki drogowe

## 题目描述

给定一棵 $n$ 个点的无根树，点的编号为 $1$ 到 $n$，边的边权均为 $n$ 的正整数次幂。
定义 $u$ 到 $v$ 的距离 $\operatorname{d(u,v)}$ 为 $u$ 和 $v$ 在树上的简单路径经过的边的边权之和。

给定 $k$，请在 $\dfrac{n\times (n-1)}{2}$ 个 $\operatorname{d(u,v)}(1\le u<v\le n)$ 中找到第 $k$ 小的值。

## 说明/提示

对于 $100\%$ 的数据，$2\le n\le 2.5\times 10^4$，$1\le k\le \dfrac{n*(n-1)}{2}$。


----



### 样例解释：

所有的 $d$ 排序后依次为： $5,5,25,30,125,130,130,135,150,155$。

## 样例 #1

### 输入

```
5 8
1 2 1
3 1 3
3 4 1
5 3 2```

### 输出

```
135```

# 题解

## 作者：一粒夸克 (赞：9)


既然没有题解那我就发一篇吧


这题是三道题的结合体：[CF464E The Classic Problem](https://www.luogu.com.cn/problem/CF464E)、[洛谷 P4178 Tree](https://www.luogu.com.cn/problem/P4178)、[S2oj 55. 小芈](https://sjzezoj.com/problem/55)

可以发现，由于图中只有 $n-1$ 条边，若边权为 $n^z$ ，相加时是不会发生进位的。

因此我们比较两条路径时，只需依次比较每个数字出现的个数即可。

可以用主席树维护哈希值，把单次比较的复杂度优化到 $O(\log n)$。

考虑二分答案。

我们先进行一次边分治，预处理出所有的“半条路径”，然后排序。

这样一来，对于左边的一条路径，右边和它相加后权值在当前区间内的路径会在一个区间内。

因此，我们可以对于每个左边的路径维护可以和它匹配的右路径的区间，不必维护所有的路径对，并且可以双指针在 $O(n\log^2n)$ （含 $O(\log n)$ 的比较和 $O(\log\ n)$ 的边分治）的时间复杂度内算出一条路径在当前路径集合中的排名。

考虑到边权很大，而路径只有 $n^2$ 条，我们可以去二分路径。

由于我们不好直接找出当前路径集合的中位数，我们可以随机选出一条路径来当作中位数。

因为不同路径的长度有可能相同，我们不能等集合大小为 1 了再停止二分，我们可以人为设定一个二分次数，50~60 最好。 

总时间复杂度 $O(n\log^3n)$

**code：**

目前同时是洛谷和 LOJ 的 rank1

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,lim;long long k;
vector<int> rt1[400005],rt2[400005];
namespace Main{
	int le[10000005],ri[10000005],siz[10000005],cnt;
	unsigned long long tree[10000005],val[100005];
	int insert(int loc,int y,int l=1,int r=n){
		if(loc<l||loc>r)return y;
		int i=++cnt;tree[i]=tree[y]+val[loc];siz[i]=siz[y]+1;
		if(l!=r){
	    	int mid=(l+r)>>1;
    		le[i]=insert(loc,le[y],l,mid);ri[i]=insert(loc,ri[y],mid+1,r);
 		}
		return i;
	}
	inline bool cmp(int a,int b,int c,int d){
		int l=1,r=n;
		while(l!=r){
			int mid=(l+r)>>1;
			if(tree[ri[a]]+tree[ri[b]]!=tree[ri[c]]+tree[ri[d]]){
				l=mid+1;
				a=ri[a];b=ri[b];c=ri[c];d=ri[d];
			}else {
				r=mid;
				a=le[a];b=le[b];c=le[c];d=le[d];
			}
		}
		return siz[a]+siz[b]<siz[c]+siz[d];
	}
	inline bool ccmp(int x,int y){
		return cmp(x,0,y,0);
	}
	vector<int> L[400005],R[400005],pos[400005];
	struct node{
		int x,y;
		node(int _x,int _y){
			x=_x;y=_y;
		}
		inline bool operator <(const node &b)const{
			return cmp(x,y,b.x,b.y);
		}
	};
	long long ans,base=1;
	const long long md=1e9+7;
	void Get(int x,int y,int l=1,int r=n){
		if(l==r){
			base=base*n%md;ans=(ans+(siz[x]+siz[y])*base)%md;
			return ;
		}
		int mid=(l+r)>>1;
		Get(le[x],le[y],l,mid);Get(ri[x],ri[y],mid+1,r);
	}
	inline void main(){
		long long all=0;
		for(int i=1;i<=lim;i++){
			L[i].resize(rt1[i].size());R[i].resize(rt1[i].size());pos[i].resize(rt1[i].size());
			for(auto &it:R[i])it=rt2[i].size()-1;all+=1ll*rt1[i].size()*rt2[i].size();
		}
		node mid(0,0);
		for(int t=1;t<=60;t++){
			long long rk=abs(1ll*rand()*rand()+rand())%all+1;
			for(int i=1;rk&&i<=lim;i++){
				for(int j=0;j<rt1[i].size();j++){
					int tmp=R[i][j]-L[i][j]+1;
					if(tmp>=rk){
						mid=node(rt1[i][j],rt2[i][L[i][j]+rk-1]);
						rk=0;break;
					}else rk-=tmp;
				}
			}
			long long tmp=0;
			for(int i=1;i<=lim;i++){
				int r=rt2[i].size()-1;
				for(int j=0;j<rt1[i].size();j++){
					r=min(r,R[i][j]);
					while(r>=L[i][j]&&mid<node(rt1[i][j],rt2[i][r]))r--;
					pos[i][j]=r;tmp+=r-L[i][j]+1;
				}
			}
			if(k==tmp)break;
			else if(k<tmp){
				all=tmp;
				for(int i=1;i<=lim;i++){
					for(int j=0;j<rt1[i].size();j++)R[i][j]=pos[i][j];
				}
			}else {
				k-=tmp;all-=tmp;
				for(int i=1;i<=lim;i++){
					for(int j=0;j<rt1[i].size();j++)L[i][j]=pos[i][j]+1;
				}
			}
		}
		Get(mid.x,mid.y);
		printf("%lld",ans);
	}
}
namespace Init{
	int ver[400005],ne[400005],head[200005],cnt=1,val[400005];
	inline void link(int x,int y,int v){
		ver[++cnt]=y;
     	ne[cnt]=head[x];
		head[x]=cnt;val[cnt]=v;
	}
	vector<pair<int,int> > son[100005];
	int las[100005];
	void init(int x,int fi){
		for(auto it:son[x]){
			int u=it.first;if(u==fi)continue;
			init(u,x);
			if(!las[x])link(x,u,it.second),link(u,x,it.second),las[x]=x;
			else {
				link(las[x],++m,0);link(m,las[x],0);las[x]=m;
				link(las[x],u,it.second);link(u,las[x],it.second);
			}
		}
	}
	int siz[200005],mxp[200005],root;
	bool vis[400005];
	void findrt(int x,int fi,int tot){
		siz[x]=1;
		for(int i=head[x];i;i=ne[i]){
			int u=ver[i];if(vis[i]||u==fi)continue;
			findrt(u,x,tot);siz[x]+=siz[u];mxp[i>>1]=max(tot-siz[u],siz[u]);
			if(mxp[root]>mxp[i>>1])root=(i>>1);
		}
	}
	int rt[200005];
	vector<int> vec;
	void dfs(int x,int fi){
		if(x<=n)vec.push_back(rt[x]);
		siz[x]=1;
		for(int i=head[x];i;i=ne[i]){
			int u=ver[i];
			if(vis[i]||u==fi)continue;
			rt[u]=Main::insert(val[i],rt[x]);
			dfs(u,x);siz[x]+=siz[u];
		}
	}
	void solve(int x,int tot){
		mxp[root=0]=m;findrt(x,x,tot);
		if(!root)return ;vis[root<<1]=vis[root<<1|1]=1;
		int L=ver[root<<1],R=ver[root<<1|1];++lim;
		rt[L]=0;vec.clear();dfs(L,R);
		sort(vec.begin(),vec.end(),Main::ccmp);swap(rt1[lim],vec);
		rt[R]=Main::insert(val[root<<1],0);vec.clear();dfs(R,L);
		sort(vec.begin(),vec.end(),Main::ccmp);swap(rt2[lim],vec);
		solve(L,siz[L]);solve(R,siz[R]);
	}
	inline void main(){
		for(int i=1;i<=n;i++)Main::val[i]=1ll*rand()*rand()*rand()+1ll*rand()*rand()+rand();
		for(int i=1;i<n;i++){
			int x,y,v;
			scanf("%d%d%d",&x,&y,&v);
			son[x].push_back(make_pair(y,v));
			son[y].push_back(make_pair(x,v));
		}m=n;
		init(1,1);solve(1,m);
	}
}
int main(){
	scanf("%d%lld",&n,&k);
	Init::main();
	Main::main();

	return 0;
}
```






---

## 作者：_SeeleVollerei_ (赞：2)

口胡了一下，懒得写了。

考虑每个路径用一棵线段树表示，每个结点存哈希值，比较操作是 $O(\log n)$ 的 。

第 $k$ 小显然二分答案，然后路径点分处理。

点分本质是枚举 LCA ，然后弄出每个点到 LCA 之间的值，每次选两条路径合并。

合并的时候考虑把两个集合排序，然后显然可以双指针，每次判断加起来是否小于二分的 mid 去移动指针，然后直接统计。

发现直接二分答案复杂度多带个 $O(n)$ ，考虑随机二分路径，每次二分相当于随机找一个长度在 $l,r$ 之间的路径，这个可以在点分的时候顺便随机一下，复杂度期望 $O(\log n)$ 。

总复杂度为 $O(n\log^3n)$ 。

upd on 2022.07.16：还是写了，过了。

实现上的启发：实际情况等到二分到 $l=r$ 的话花费的时间太久了，所以我们可以钦定一个二分次数。

然后这个二分次数会影响 WA 或 TLE ，所以这里我选择卡时。

实际代码长度只有 6.2k 。

放个代码，毕竟是成就感（

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<set>
#include<deque>
#include<ctime>
using namespace std;
typedef long long LL;
const int N=5e4+5;
const int Mod=1e9+7;
int n;
LL k;
int power[N];
int sum[N<<10],lc[N<<10],rc[N<<10],tot,cnt[N<<10];
int Head[N],Ver[N<<1],Nxt[N<<1],cnt_edge=-1,Val[N<<1];
double st;
inline int Read(){
	char ch;
	int f=1;
	while((ch=getchar())<'0'||ch>'9')
		if(ch=='-') f=-1;
	int x=ch^48;
	while((ch=getchar())>='0'&&ch<='9')
		x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
inline void print(const int x){
	if(x>=10) print(x/10);
	putchar(x%10+48);
	return ;
}
inline void Print(const int x,const char ch='\n'){
	if(x<0){
		putchar('-');
		print(-x);
	}
	else print(x);
	putchar(ch);
	return ;
}
inline void add(int&x,const int y){
	x+=y;
	if(x>=Mod) x-=Mod;
	return ;
}
inline void sub(int&x,const int y){
	x-=y;
	if(x<0) x+=Mod;
	return ;
}
inline void Add(const int u,const int v,const int value){
	++cnt_edge;
	Ver[cnt_edge]=v;
	Val[cnt_edge]=value;
	Nxt[cnt_edge]=Head[u];
	Head[u]=cnt_edge;
	return ;
}
inline void Add_Edge(const int u,const int v,const int value){
	Add(u,v,value);
	Add(v,u,value);
	return ;
}
inline void Init(){
	st=time(0);
	memset(Head,-1,sizeof(Head));
	n=Read();
	scanf("%lld",&k);
	for(int i=1;i<n;i++){
		int u=Read();
		int v=Read();
		int value=Read();
		Add_Edge(u,v,value);
	}
	power[0]=1;
	for(int i=1;i<=n+1;i++)
		power[i]=1ll*power[i-1]*n%Mod;
	return ;
}
inline void Add_Edge(const int u,const int v){
	++cnt_edge;
	Ver[cnt_edge]=v;
	Nxt[cnt_edge]=Head[u];
	Head[u]=cnt_edge;
	return ;
}
inline void Add(int&u,const int v,const int ll,const int rr,const int p){
	u=++tot;
	sum[u]=sum[v];
	add(sum[u],power[p]);
	cnt[u]=cnt[v]+1;
	if(ll==rr) return ;
	int mid=ll+rr>>1;
	if(mid>=p){
		Add(lc[u],lc[v],ll,mid,p);
		rc[u]=rc[v];
	}
	else{
		lc[u]=lc[v];
		Add(rc[u],rc[v],mid+1,rr,p);
	}
	return ;
}
inline bool Small(const int u,const int v,const int ll,const int rr){
	if(ll==rr) return cnt[u]<cnt[v];
	int mid=ll+rr>>1;
	if(sum[rc[u]]!=sum[rc[v]]) return Small(rc[u],rc[v],mid+1,rr);
	return Small(lc[u],lc[v],ll,mid);
}
inline bool Small2(const int u1,const int u2,const int v,const int ll,const int rr){
	if(ll==rr) return cnt[u1]+cnt[u2]<cnt[v];
	int mid=ll+rr>>1;
	int sr=(sum[rc[u1]]+sum[rc[u2]])%Mod;
	if(sr!=sum[rc[v]]) return Small2(rc[u1],rc[u2],rc[v],mid+1,rr);
	return Small2(lc[u1],lc[u2],lc[v],ll,mid);
}
struct Node{
	int uu,inr,sgt;
	Node(){uu=inr=sgt=0;return ;}
};
vector<Node>in[N];
bool vis[N];
int siz[N],root,mn;
inline int Max(const int x,const int y){
	return x>y?x:y;
}
inline int Min(const int x,const int y){
	return x<y?x:y;
}
inline void FindRoot(const int u,const int fa,const int all){
	siz[u]=1;
	int mx=-1;
	for(int i=Head[u];i!=-1;i=Nxt[i]){
		int v=Ver[i];
		if(v==fa||vis[v]) continue ;
		FindRoot(v,u,all);
		siz[u]+=siz[v];
		mx=Max(mx,siz[v]);
	}
	mx=Max(mx,all-siz[u]);
	if(mn>mx){
		mn=mx;
		root=u;
	}
	return ;
}
inline void Calc(const int u,const int fa,const int fasgt,const int p,const int fr,const int frall){
	Node u1;
	u1.uu=u,u1.inr=fr;
	Add(u1.sgt,fasgt,1,n+1,p);
	in[frall].push_back(u1);
	for(int i=Head[u];i!=-1;i=Nxt[i]){
		int v=Ver[i];
		if(v==fa||vis[v]) continue ;
		Calc(v,u,u1.sgt,Val[i],fr,frall);
	}
	return ;
}
inline bool Cmp(const Node x,const Node y){
	return Small(x.sgt,y.sgt,1,n+1);
}
inline void Dfs(const int u){
	Node u1;
	u1.uu=u,u1.inr=u;
	in[u].push_back(u1);
	for(int i=Head[u];i!=-1;i=Nxt[i]){
		int v=Ver[i];
		if(vis[v]) continue ;
		Calc(v,u,0,Val[i],v,u);
	}
	sort(in[u].begin(),in[u].end(),Cmp);
	vis[u]=1;
	for(int i=Head[u];i!=-1;i=Nxt[i]){
		int v=Ver[i];
		if(vis[v]) continue ;
		root=-1,mn=n+1;
		FindRoot(v,0,siz[v]);
		Dfs(root);
	}
	return ;
}
inline void Init_Tree(){
	root=-1,mn=n+1;
	FindRoot(1,0,n);
	Dfs(root);
	return ;
}
int cntt[N];
inline bool Check(const int mid){
	LL ss=0;
	for(int i=1;i<=n;i++){
		int j1=0;
		for(int j=in[i].size()-1;j>=0;j--){
			while(j1<in[i].size()&&Small2(in[i][j].sgt,in[i][j1].sgt,mid,1,n+1)){
				cntt[in[i][j1].inr]++;
				j1++;
			}
			ss+=j1-cntt[in[i][j].inr];
		}
		for(int j=0;j<in[i].size();j++)
			cntt[in[i][j].inr]=0;
	}
	return ss/2<k;
}
inline int Merge(const int u,const int v,const int ll,const int rr){
	if(!u||!v) return u+v;
	int now=++tot;
	sum[now]=(sum[u]+sum[v])%Mod;
	cnt[now]=cnt[u]+cnt[v];
	if(ll<rr){
		int mid=ll+rr>>1;
		lc[now]=Merge(lc[u],lc[v],ll,mid);
		rc[now]=Merge(rc[u],rc[v],mid+1,rr);
	}
	return now;
}
inline int Random(const int ll,const int rr){
	return 1ll*rand()*rand()%(rr-ll+1)+ll;
}
int u_rand[N<<5],v_rand[N<<5],cnt_rand,fr_rand[N<<5];
set<int>s;
deque<int>q[N];
inline int Find(const int ll,const int rr){
	cnt_rand=0;
	for(int i=1;i<=n;i++){
		int l=0,r=0;
		for(int j=in[i].size()-1;j>=0;j--){
			while(r<in[i].size()&&Small2(in[i][j].sgt,in[i][r].sgt,rr,1,n+1)){
				if(!cntt[in[i][r].inr]) s.insert(in[i][r].inr);
				cntt[in[i][r].inr]++;
				q[in[i][r].inr].push_back(r);
				r++;
			}
			while(l<in[i].size()&&Small2(in[i][j].sgt,in[i][l].sgt,ll,1,n+1)){
				cntt[in[i][l].inr]--;
				if(!cntt[in[i][l].inr]) s.erase(in[i][l].inr);
				if(q[in[i][l].inr].size()) q[in[i][l].inr].pop_front();
				l++;
			}
			if(l==r) continue ;
			if(!s.size()) continue ;
			if(s.size()==1&&*s.begin()==in[i][j].inr) continue ;
			set<int>::iterator it=s.begin();
			if(*it==in[i][j].inr) it=--s.end();
			int inr1=*it;
			++cnt_rand;
			fr_rand[cnt_rand]=i;
			u_rand[cnt_rand]=j;
			int rd=Random(0,q[inr1].size()-1);
			v_rand[cnt_rand]=q[inr1][rd];
		}
		for(int j=0;j<in[i].size();j++){
			cntt[in[i][j].inr]=0;
			q[in[i][j].inr].clear();
		}
		s.clear();
	}
	int rd=Random(1,cnt_rand);
	int fr=fr_rand[rd];
	int i1=u_rand[rd],i2=v_rand[rd];
	int ge=Merge(in[fr][i1].sgt,in[fr][i2].sgt,1,n+1);
	return ge;
}
inline void Solve(){
	Init_Tree();
	int ll=0,rr=0;
	Add(rr,0,1,n+1,n+1);
	while(time(0)-st<=5.2){
		int mid=Find(ll,rr);
		if(Check(mid)) ll=mid;
		else rr=mid;
		if(sum[ll]==sum[rr]) break ;
	}
	int ans=Find(ll,rr);
	return Print(sum[ans]);
}
int main(){
	Init();
	Solve();
	return 0;
}
```

---

## 作者：qiuzx (赞：0)

将边权看作 $n$ 进制数，则边权相加不会产生进位，因此只需要对位相加并比较字典序即可。现在假如固定一个 $w$，如何求出有多少对点的距离不超过 $w$？考虑点分治，则我们在一层分治的时候使用主席树维护每个点到根的距离，然后将所有点的深度排序。比较两个点的距离可以使用哈希维护每个点的距离，然后二分 $\text{lcp}$ 比较大小。在主席树上二分，单次比较复杂度 $O(\log n)$，所以排序总复杂度 $O(\log^2n)$。接着可以使用 two pointers 求出每个点有多少个能与它距离不超过 $w$ 的点。最后还要去除同一子树内的贡献，和上面方法一样。所以单次判定可以做到 $O(\log^3n)$ 的复杂度。

这样就可以考虑随机二分，由于在 check 的时候我们天然维护出了每个点能配对的点个数以及它们的范围，所以把所有这些范围拿出来在里面随机选一对点，考察这两个点之间的距离的排名。这样期望 check 的次数是 $O(\log n^2)$ 的，复杂度 $O(n\log^4n)$，不能通过。但注意到每次在点分治的时候排序是没有必要的，因为二分的值只影响最后 two pointers 的部分。所以可以在一开始先做一次点分治排好序并把主席树保留，check 的时候直接扫一遍即可。复杂度 $O(n\log^3n)$，空间复杂度 $O(n\log^2n)$。

[代码](https://loj.ac/s/2171389)

---

