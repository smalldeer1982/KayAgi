# Moment of Bloom

## 题目描述

她竭尽全力完美地执行人们的最后仪式，并维护世间阴阳的平衡。

胡桃，这位喜欢恶作剧的小家伙，试图用这道图论问题吓唬你！给定一个包含 $n$ 个节点的连通无向图，包含 $m$ 条边。此外还有 $q$ 个查询。每个查询由两个节点 $a$ 和 $b$ 组成。

初始时，图中所有边的权重均为 $0$。对于每个查询，你必须选择一条从 $a$ 开始到 $b$ 结束的简单路径，然后将这条路径上的每条边的权重加 $1$。请判断在处理完所有 $q$ 个查询后，是否可能让图中所有边的权重均为偶数。如果可能，请输出每个查询选择的路径。

如果不可能，请确定需要添加的最少额外查询数量，使得最终可能满足条件。可以证明在给定约束下，这个数值不会超过 $10^{18}$。

简单路径定义为不重复经过任何节点的路径。

边的权重为偶数当且仅当其值能被 $2$ 整除。

## 说明/提示

以下是第一个测试用例的查询示意图（红色对应第一个查询，蓝色对应第二个查询，绿色对应第三个查询）：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1583E/5ff1c34d00f50f49f9af7fee2914509959b9ec36.png) 注意图中每条边要么未被任何查询覆盖，要么被恰好两个查询覆盖。第二个测试用例的图如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1583E/e149de6088d2fe5f3579f58ec01023d45627b5fa.png) 在给定查询下，无法通过路径选择使所有边的权重均为偶数。至少需要添加 $2$ 个新查询才能满足条件。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6 7
2 1
2 3
3 5
1 4
6 1
5 6
4 5
3
1 4
5 1
4 5```

### 输出

```
YES
2
1 4
4
5 3 2 1
5
4 1 2 3 5```

## 样例 #2

### 输入

```
5 7
4 3
4 5
2 1
1 4
1 3
3 5
3 2
4
4 2
3 5
5 1
4 5```

### 输出

```
NO
2```

# 题解

## 作者：Binary_Lee (赞：10)

## [题面传送门](https://www.luogu.com.cn/problem/CF1583E)

### 解决思路

没有思路时可以先手玩样例。

![](https://cdn.luogu.com.cn/upload/image_hosting/2z8otidl.png)

以样例 $1$ 为例，我们把每条路径的顺序重排一下，得到了以下结果：$4\to 1,1\to 5,5\to 4$ 。可以发现，构成了一个环。一个路径环可以使其中每条路径走过 $2$ 次，同时也意味着环上的每个点作为起点或终点出现了 $2$ 次。能否推广到偶数次呢？假设我们给样例 $1$ 加上 $3$ 条路径：$1\to 6,6\to 4,4\to1$，这时 $1,4$ 分别都出现了 $4$ 次。我们只需要再添一个经过 $1,4,5,6$ 的环即可，仍然满足要求。

所以，得出结论：若所有起点终点都出现了偶数次，即满足了题目要求。

然后考虑如何求出路径。因为要求出现次数为 $2$ 的一组点连成的路径构成一个环，所以任意两点之间走的要是同一条路径，树就满足这一条件。所以考虑建出原图的任意生成树，然后跑 $\text{dfs}$ 即可找出路径。具体可以看代码。

那不满足要求怎么办？以样例 $2$ 为例，$1,2,3,5$ 三个点作为起点或终点出现了奇数次。所以，只要在它们之间每两个加一条路径即可，需要添加的路径条数 $=$ 作为起点或终点出现奇数次的点数 $\div 2$。


### AC Code

```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
#define int long long
using namespace std;
int n,m,u,v,q,d[300005],s[300005],t[300005],ans;
vector<int> a[300005],b;
bool fl;
struct DSU{
	int fa[300005];
	void init(int n){
		for(int i=1;i<=n;i++) fa[i]=i;
	}
	int find(int x){
		if(x==fa[x]) return x;
		return fa[x]=find(fa[x]);
	}
	void merge(int x,int y){
		fa[find(x)]=find(y);
	}
	bool query(int x,int y){
		return find(x)==find(y);
	}
}dsu;
void dfs(int x,int fa,int to){
	for(int i=0;i<a[x].size();i++){
		int tmp=a[x][i];  
		if(tmp==fa) continue;
		b.push_back(tmp);  
		if(tmp==to){   //走到了
			fl=1;
			return ;
		}
		dfs(tmp,x,to);
		if(fl) return ;
		b.pop_back();
	}
}
signed main(){
	IOS;TIE;
	cin>>n>>m;
	dsu.init(n);
	for(int i=1;i<=m;i++){
    		cin>>u>>v;
		if(!dsu.query(u,v)){
			dsu.merge(u,v);
			a[u].push_back(v);
			a[v].push_back(u);  //建成一颗树
		}
	}
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>s[i]>>t[i];
		d[s[i]]++,d[t[i]]++;  //作为起点或终点出现次数
	}
	for(int i=1;i<=n;i++) if(d[i]&1) ans++;
	if(ans==0){
		cout<<"YES"<<endl;
		for(int i=1;i<=q;i++){
			b.clear(),fl=0,b.push_back(s[i]);  //b记录路径
			dfs(s[i],0,t[i]);
			cout<<b.size()<<endl;
			for(int j=0;j<b.size();j++) cout<<b[j]<<' ';
			cout<<endl;
		}
	}
	else cout<<"NO"<<endl<<ans/2<<endl;  
	return 0;
}
```


---

## 作者：Alex_Wei (赞：6)

> ### 1586E. [Moment of Bloom](https://codeforces.ml/contest/1586/problem/E)

考察与每个点相邻的所有边被改变的次数之和的奇偶性，不难发现除了两个端点，路径其它节点的奇偶性都不会改变。

那么就做完了吧，直接对于每个点记录成为端点的次数奇偶性，最后求一下是奇数的端点个数除以 $2$ 就是答案，因为一条路径最多也一定可以消灭两个成为端点次数是奇数的节点。

否则对原图求任意生成树，输出方案就是端点之间的简单路径，正确性显然（可以根据叶子结点成为端点次数是偶数推断出其与父节点的边重量一定是偶数归纳证明构造出来的方案一定合法）。时间复杂度 $\mathcal{O}(nq)$。

```cpp
const int N=3e5+5;

int n,m,q,cnt,vis[N],fl[N],a[N],b[N];
vint e[N],f[N],cur,ans;
void dfs(int id){
	vis[id]=1;
	for(int it:e[id]){
		if(vis[it])continue;
		f[id].pb(it),f[it].pb(id),dfs(it);
	}
}
void dfs2(int id,int fa,int aim){
	cur.pb(id);
	if(id==aim)return ans=cur,void();
	for(int it:f[id]){
		if(it==fa)continue;
		dfs2(it,id,aim);
	} cur.pop_back();
}
int main(){
    cin>>n>>m;
	for(int i=1;i<=m;i++){
		int a,b; cin>>a>>b;
		e[a].pb(b),e[b].pb(a);
	} dfs(1),cin>>q;
	for(int i=1;i<=q;i++)
		cin>>a[i]>>b[i],fl[a[i]]^=1,fl[b[i]]^=1;
	for(int i=1;i<=n;i++)cnt+=fl[i];
	if(cnt==0){
		puts("YES");
		for(int i=1;i<=q;i++){
			cur.clear(),dfs2(a[i],0,b[i]);
			cout<<ans.size()<<endl;
			for(int it:ans)cout<<it<<" ";
			cout<<endl;
		}
	}
	else puts("NO"),cout<<cnt/2<<endl;
	return 0;
}
```

---

## 作者：Mirasycle (赞：2)

考虑合法的充要性。

首先，最后的图合法的必要条件是每个点所连边的经过次数之和为偶数（最后每条边都是偶数，加在一起也是偶数）。

考虑一条路径可以给路途上的每个点（除了端点）度数都加偶数（一进一出），而端点被加了奇数次。于是统计每个点作为路径端点的次数，如果有点为奇数显然是不行的，于是可以两两配对，最后的答案就是奇点个数除以二。如果每个点的度数都是偶数，我们尝试将必要条件推广至充要，方法是给出构造。如果每个点的度数都是偶数，等价于我们建立一个新图，把每条路径的端点在这张新图中连在一起，然后这张图存在欧拉回路。

那么设给出的路径端点分别是 $(s_i,t_i)$，我们求出欧拉回路之后满足 $t_i=s_{i\bmod n+1}$，于是可以走 $s_1\to t_2 \to t_2\to ...\to t_{n-1}(s_n)$，在 $s_n$ 的位置我们要走到 $t_n=s_1$，我们可以按照来时的路再反着走一遍，这样子就可以保证每条边都经过奇数次了。

上述做法给出了构造因此结论成立。不过我们的构造部分如果按照上述这么写就太麻烦了，考虑求出原图的任意一颗生成树，那么对于一条路径，直接输出两个端点在生成树上的简单路径即可。正确性显然。

  时间复杂度 $O(nq)$。

---

## 作者：Yizhixiaoyun (赞：2)

[本套题所有题解](https://www.luogu.com.cn/blog/yizhixiaoyun/cf1583-ti-xie)

由于笔者水平较弱，所以可能只能一路做到自己做不了的题，不保证能全部写完。

------------

这套题好多构造啊...

首先引出一个结论：对于一个路径，它能改变的节点奇偶性只有两个端点，对于其它节点，该路径都不会对其奇偶性有任何改变。

在这个结论之下，我们要求的数量实际上就是成为端点次数为奇的节点个数 $cnt / 2$。原理显然，一条路径可以连接两个这样的节点，使它们次数变为偶数。

构造方案即求生成树，如果一个叶子节点被连的次数为偶，那么其与父节点的边权一定为偶，直接输出简单路径。

```cpp
#include<bits/stdc++.h>
#define ok puts("YES")
#define no puts("NO")
#define clean fflush(stdout) 
using namespace std;
const int maxn=3e5+5;
int n,m,q;
int u,v;
int cnt;
int a[maxn],b[maxn];
int cnt_num[maxn],ans[maxn];
bool vis[maxn];
int cnt_edge,head[maxn];
int f[maxn],dep[maxn];
struct edge{
	int to,nxt;
}e[maxn<<1];
void add(int u,int v){
	e[++cnt_edge].to=v;
	e[cnt_edge].nxt=head[u];
	head[u]=cnt_edge;
}
void dfs(int u,int fa){
	vis[u]=true;dep[u]=dep[fa]+1;f[u]=fa;
	for(register int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(vis[v]==false) dfs(v,u);
	}
}
inline void init(){
	cin>>n>>m;
	dep[1]=1;
	for(register int i=1;i<=m;++i){
		cin>>u>>v;
		add(u,v);add(v,u);
	}
	cin>>q;
	for(register int i=1;i<=q;++i){
		cin>>a[i]>>b[i];
		cnt_num[a[i]]++;cnt_num[b[i]]++;
	}
}
int main(){
	init();
	for(register int i=1;i<=n;++i){
		if(cnt_num[i]%2==1) cnt++;
	}
	if(cnt!=0){
		no;cnt/=2;cout<<cnt;
		exit(0);
	}
	ok;
	dfs(1,0);
	for(register int i=1;i<=q;++i){
		int l=0,r=n+1;
		while(a[i]!=b[i]){
			if(dep[a[i]]>dep[b[i]]){
				l++;ans[l]=a[i];a[i]=f[a[i]];
			}
			else{
				r--;ans[r]=b[i];b[i]=f[b[i]];
			}
		}
		l++;ans[l]=a[i];
		cout<<l-r+n+1<<endl;
		for(register int j=1;j<=l;++j) cout<<ans[j]<<" ";
		for(register int j=r;j<=n;++j) cout<<ans[j]<<" ";
		cout<<endl;
	}
}
```

---

## 作者：qczrz6v4nhp6u (赞：1)

比官方解法冗杂得多，但是更加直观？

### Solution

转化一下题意：开始所有边权为 $0$，每次操作选定一条 $a\to b$ 的简单路径并将路径上的异或 $1$，求最后能否使所有边权为 $0$。

考虑到这个东西在图上并不好直接做，我们尝试将这个东西转化到树上。

一个很重要的性质：一定存在一种最优方案（即若有解则能构造出解，若无解能用最小步数有解），使得所有被至少一条路径经过的边不构成环。

证明的大体思路是：考虑每个环，显然环被 $0$ 或 $1$ 条路径经过时成立，归纳即可得证。详细证明较为繁琐，此处不再展开。

由以上的性质，我们得到：所有被给定路径经过的边构成森林。我们可以考虑求出原图的任意生成树，每次操作即为将生成树上 $a\to b$ 唯一简单路径上的边异或 $1$。

判定生成树上是否存在权值为 $1$ 的边即可。树上路径异或 $1$ 可以暴力或树上差分做。

然后是无解时计算最小操作数。显然需要操作的边应该是能合并就合并的，于是我们计算能够合并的最大数量，再用总数减去即可。

时间复杂度 $\mathcal O(nq)$。

Fun：本地 IDE 说 `std::vector<int>::size_type` 是 `unsigned long long int`，但 `printf("%llu")` 惨遭 WA on test 1，怎么会是呢。

### Code

抽象，慎阅。

```cpp
#include<bits/stdc++.h>
#define Tp template<typename T>
#define Ts template<typename T,typename... _T>
using namespace std;
using ll=long long;
using ull=unsigned long long;
char buf[1<<20],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=buf+fread(p1=buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
Tp inline void read(T& x){
    x=0;char c=getchar();bool f=0;
    for(;c<48||c>57;c=getchar())c=='-'&&(f=1);
    for(;c>47&&c<58;c=getchar())x=(x<<1)+(x<<3)+(c^48);
    f&&(x=-x);
}
Ts inline void read(T& x,_T&... y){read(x),read(y...);}
Tp inline void assign(T *a,int n,T b){while(n--)*a++=b;}
Tp inline void copy(T *a,T *b,int n){while(n--)*a++=*b++;}
Tp inline void ckmin(T &a,T b){b<a&&(a=b);}
Tp inline void ckmax(T &a,T b){a<b&&(a=b);}
const int N=3e5+5;
int n,m,q,f[N];
int get(int x){return f[x]==x?x:f[x]=get(f[x]);}
void merge(int x,int y){f[get(x)]=get(y);}
struct edge{int x,y,z,pre;}Gr[N<<1];int Grlen,last[N];
void ins(int x,int y,int z=0){Gr[++Grlen]={x,y,z,last[x]},last[x]=Grlen;}
int a[N],b[N],d[N],fa[N],cnt,ans;
void dfs(int x){
	int sum=0;
	for(int k=last[x],y;y=Gr[k].y,k;k=Gr[k].pre)
		if(y!=fa[x]){
			fa[y]=x;
			dfs(y);
			d[x]^=d[y];
			sum+=d[y];
		}
	cnt+=d[x];
	ans+=(sum+d[x])/2;
}
vector<int>ans1,ans2;
int tims[N];
int main(){
	read(n,m);
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1,x,y;i<=m;i++){
		read(x,y);
		if(get(x)==get(y))continue;
		ins(x,y),ins(y,x);
		merge(x,y);
	}
	read(q);
	for(int i=1;i<=q;i++){
		read(a[i],b[i]);
		d[a[i]]^=1,d[b[i]]^=1;
	}
	dfs(1);
	if(cnt){
		puts("NO");
		printf("%d\n",cnt-ans);
	}
	else{
		puts("YES");
		for(int i=1;i<=q;i++){
			assign(tims+1,n,0);
			ans1.clear(),ans2.clear();
			int x,p=0;
			for(x=a[i];x;x=fa[x])++tims[x];
			for(x=b[i];x;x=fa[x])++tims[x];
			for(x=a[i];tims[x]<2;x=fa[x])ans1.emplace_back(x);
			for(x=b[i];tims[x]<2;x=fa[x])ans2.emplace_back(x);
			if(ans1.size())p=fa[*ans1.rbegin()];
			if(ans2.size())p=fa[*ans2.rbegin()];
			reverse(ans2.begin(),ans2.end());
			printf("%d\n",(int)ans1.size()+(int)ans2.size()+(p>0));
			for(auto &o:ans1)printf("%d ",o);
			if(p>0)printf("%d ",p);
			for(auto &o:ans2)printf("%d ",o);
			puts("");
		}
	}
	return 0;
}
```

---

## 作者：vectorwyx (赞：1)

图上构造，要求满足奇偶性。这种题先想生成树一般就赢了。令 $f_v$ 表示 $v$ 作为路径端点的出现次数，$g_v$ 表示 $v$ 连出的边的边权和。

首先，如果存在 $f_v$ 为奇那么一定没有合法的构造方案，这是因为如果 $v$ 不是路径的端点那么每一条经过 $v$ 的路径给 $g_v$ 带来的变化一定是 $+2$，而如果 $v$ 是某条路径的端点，其对于 $g_v$ 的影响是 $+1$，因此如果 $f_v$ 为奇则 $g_v$ 为奇，不符合要求。

其次，如果所有的 $f_v$ 均为偶那么一定存在合法的构造方案。考虑在生成树上构造，每个叶子连向父亲的边的边权一定为偶，然后剥掉叶子。由于 $f_v$ 均为偶，所以 $g_v$ 为偶，所以新产生的叶子连向父亲的边的边权也一定为偶……以此类推，得证。

综上，一张图有合法方案的充要条件是 $f_v$ 均为偶。如果不满足条件，所需要添加的最少路径数为满足 $f_v$ 为奇的 $v$ 的数量除以 $2$。由于一条路径会令两个 $f$ 值加 $1$，因此奇点的个数必为偶，可以整除。

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}
inline void out(int *a,int l,int r){fo(i,l,r) printf("%d ",*(a+i));puts("");}

//记录奇点数量 
//找生成树，记 dep 跳 fa（一遍 dfs 即可）。要先输出路径长度再输出路径上的点 
//预计完成时间：10 min 
//代码完成时间：7 min，输出细节方面：7min 
const int N=3e5+5;
struct Edge{
	int to,next;
}e[N<<1];
int head[N],tot,fa[N],dep[N],a[N],b[N],f[N],n,m,q,vis[N],ans[N];

void connect(int x,int y){
	e[++tot]=(Edge){y,head[x]};
	head[x]=tot;
}

void dfs(int x){
	//printf("dfs(%d,%d)\n",x,fa[x]);
	vis[x]=1;
	for(int i=head[x];i;i=e[i].next){
		int p=e[i].to;
		if(vis[p]) continue;
		dep[p]=dep[x]+1,fa[p]=x;dfs(p);
	}
}

int main(){
	cin>>n>>m;
	fo(i,1,m){
		int x=read(),y=read();
		connect(x,y);
		connect(y,x);
	}cin>>q;
	fo(i,1,q) a[i]=read(),b[i]=read(),f[a[i]]++,f[b[i]]++;
	int rp=0;
	fo(i,1,n) if(f[i]&1) rp++;
	if(rp){
		puts("NO");
		cout<<rp/2;
		return 0;
	}
	puts("YES");
	dep[1]=1;dfs(1);
	fo(i,1,q){
		rp=1;int x=a[i],y=b[i],k;
		while(x!=y){
			if(dep[x]<dep[y]) swap(x,y);
			rp++;x=fa[x];
		}k=x;x=a[i],y=b[i];
		printf("%d\n",rp);
		int id=0;
		while(x!=k){
			ans[++id]=x;
			x=fa[x];
		}id=0;
		while(1){
			ans[rp-id]=y;
			if(y==k) break;
			y=fa[y];id++;
		}out(ans,1,rp);
	}
	return 0;
}

```


---

## 作者：冷却心 (赞：0)

千纱伊织领证了甜甜甜 /jy /打call。

先考虑如果有解怎么构造。我们任取一颗生成树，可以证明每组点在树上的简单路径即为一组解。证明：因为有解，所以任取一组合法解，把这组解内的非树边全部替换成等效的连接非树边左右两端的一组树边，这样就得到了全部都是树上路径的解。

然后考虑判断是否有解以及最小加边数。结论：一组点对存在解当且仅当能构造出一组路径使得每个点相邻的边经过次数的总和为偶数。必要性显然，充分性证明：如果后面构造出的路径恰好已经满足每条边是偶数了那么显然已经合法。否则权值奇数的路径一定可以被剖分成若干个环，于是我们可以把一些路径在环上的部分变成环上的补集，这样就能使得每条边权值都是偶数，得到合法解。

所以我们不需要考察每条边的经过次数而是每个点的相邻边经过次数总和。注意到一条路径会改变后者的奇偶性的位置只有路径开头和结尾。所以我们统计每个点作为路径端点的次数，如果没有奇数次的点那么就存在解。否则我们把这些点两两配对新建路径就做完了，答案是奇数点个数的一半。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 3e5 + 10;
int n, m, Q, cnt[N]; vector<int> G[N];
pair<int, int> e[N];
bool vis[N]; vector<int> tr[N];
void DFS0(int u, int f) {
	vis[u] = 1;
	if (f) tr[u].push_back(f), tr[f].push_back(u);
	for (int v : G[u]) if (!vis[v]) DFS0(v, u);
}
int tmp[N], T; bool flag = false;
void DFS1(int u, int f, int d) {
	if (flag) return ;
	tmp[d] = u;
	if (T == u) {
		cout << d << "\n"; flag = true;
		for (int i = 1; i <= d; i ++) cout << tmp[i] << " \n"[i == d];
		return ;
	}
	for (int v : tr[u]) if (v != f) DFS1(v, u, d + 1);
}

int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1, u, v; i <= m; i ++) cin >> u >> v, G[u].push_back(v), G[v].push_back(u);
	cin >> Q;
	for (int i = 1, u, v; i <= Q; i ++) cin >> u >> v, cnt[u] ++, cnt[v] ++, e[i] = {u, v};
	int c = 0;
	for (int i = 1; i <= n; i ++) c += (cnt[i] & 1);
	if (c) { cout << "NO\n" << c / 2 << "\n"; return 0; }
	cout << "YES\n"; DFS0(1, 0);
	for (int i = 1; i <= Q; i ++) {
		flag = false; T = e[i].second; DFS1(e[i].first, 0, 1);
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1583E 题解



## 思路分析

考虑一个点周围的边覆盖次数的综合，对于一条 $a\to b$ 的路径，其在路径中间的贡献为 $2$，而在路径两边的贡献为 $1$。

因此我们记录 $d_v$ 为 $v$ 在 $q$ 对 $(a_i,b_i)$ 中出现的次数并考虑 $d_v\bmod 2$ 的值，显然如果 $d_v\bmod 2=1$ 无解。

考虑所有 $d_v$ 均为偶数的情况，注意到如下观察：

> 观察：
>
> 在保证所有 $d_v$ 都是偶数的情况下，任取一棵原图的生成树，对于所有 $(a_i,b_i)$ 取 $a_i\to b_i$ 的树上简单路径，此时构造满足题目要求 。
>
> 对树的大小进行归纳：
>
> 考虑树的任意一个叶子 $u$，由于 $2\mid d_u$，注意到此时根据构造有 $w(u,fa_u)=d_u\equiv0\pmod 2$，因此我们可以删去 $u$ 到其父亲的边。
>
> 所以此时我们把从 $u$ 出发的 $d_u$ 条路径扔到 $fa_u$ 上，即令 $d_{fa_u}\gets d_{fa_u}+d_u$，此时由于 $2\mid d_{fa_u},2|d_{u}$，因此新的 $d_{fa_u}$ 仍然是偶数。
>
> 然后我们在树中删除节点 $u$ 和边 $(u,fa_u)$，此时得到的新树的一个合法的解也对应原树的一个合法的解，然后在新树上运用归纳假设即可证明原命题。

所以求出图中的一棵生成树然后对于每个询问用朴素算法求 LCA 并且输出路径即可。

时间复杂度 $\Theta(nq)$。

## 代码呈现

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int MAXN=3e5+1;
vector <int> G[MAXN],T[MAXN]; 
bool vis[MAXN];
int dep[MAXN],fa[MAXN],deg[MAXN];
inline void dfs(int p) {
	vis[p]=true;
	for(int v:G[p]) {
		if(!vis[v]) {
			dep[v]=dep[p]+1,fa[v]=p;
			T[p].push_back(v);
			dfs(v);
		}
	}
}
inline int LCA(int u,int v) {
	if(u==v) return u;
	return dep[u]>dep[v]?LCA(fa[u],v):LCA(u,fa[v]);
}
inline vector<int> path(int u,int v) {
	int x=LCA(u,v);
	vector <int> c1,c2,pt;
	for(int p=u;p!=x;p=fa[p]) c1.push_back(p);
	for(int p=v;p!=x;p=fa[p]) c2.push_back(p);
	reverse(c2.begin(),c2.end());
	for(int i:c1) pt.push_back(i);
	pt.push_back(x);
	for(int i:c2) pt.push_back(i);
	return pt;
}
int st[MAXN],ed[MAXN];
signed main() {
	int n,m,q,cnt=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1);
	scanf("%d",&q);
	for(int i=1;i<=q;++i) {
		scanf("%d%d",&st[i],&ed[i]);
		++deg[st[i]],++deg[ed[i]];
	}
	for(int i=1;i<=n;++i) if(deg[i]%2!=0) ++cnt;
	if(cnt>0) printf("NO\n%d\n",cnt/2);
	else {
		puts("YES");
		for(int i=1;i<=q;++i) {
			vector <int> ans=path(st[i],ed[i]);
			printf("%d\n",(int)ans.size());
			for(int j:ans) printf("%d ",j);
			puts("");
		}
	}
	return 0;
}
```



---

