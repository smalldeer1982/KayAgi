# Button Lock

## 题目描述

有 $d$ 个按钮，编号从 $0$ 到 $d-1$，在按下一个按钮之后，按钮不会复位。有一个重置键，按下这个重置键之后，所有被按下的按钮都会被复位。现在有一些按钮集合，你需要找到一个最短的操作序列，使得每一个集合表示的被按下的状态在整个过程中都出现过至少一次，求这个序列。

## 样例 #1

### 输入

```
2 2
10
11```

### 输出

```
2
0 1```

## 样例 #2

### 输入

```
3 4
001
111
101
011```

### 输出

```
6
2 0 R 1 2 0```

# 题解

## 作者：Tx_Lcy (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/CF1510B)

## 思路

考虑二分图最大匹配。

$s_i$ 表示第 $i$ 个集合。

我们先建图：$s_i$ 和 $s_j$ 之间有边当且仅当 $s_i$ 是 $s_j$ 的子集。

这显然是个 $\rm DAG$，那么问题转化成：选择若干条路径覆盖此 $\rm DAG$ 的所有点，每条路径的权值是结尾节点的 $\rm popcnt+1$，要求权值最小。

然后我们发现，出现 $s_i$ 这个状态后，我们需要选择一个 $j$，满足 $i,j$ 有边，然后把状态 $s_i$ 改成状态 $s_j$，这样的 $j$ 只能选一个。

这个条件相当于 $i$ 可以跟与 $i$ 有边的 $j$ 中的一个匹配。

如果说 $i$ 没有匹配上，$i$ 就是某条路径的终点。

最优解肯定是拆点二分图最大匹配中的一个，这是显然的，因为如果还能匹配，那么答案一定还能减少。

现在有权值的条件，我们按照权值从大到小排序，然后按照这个顺序进行二分图最大匹配即可。

输出方案可以从每条路径的终点开始暴力跳匹配。

最坏情况图中有 $2^d$ 个点，$3^d$ 条边，时间复杂度 $\mathcal O(6^d)$。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
int const N=1e4+10;
int a[N],g[N],matched[N],vis[N],id[N];
vector<int>b[N];
bool Hungary(int x,int co){
	for (auto v:b[x]){
		if (vis[v]==co) continue;
		vis[v]=co;
		if (!matched[v] || Hungary(matched[v],co))
			return matched[v]=x,1;
	}
	return 0;
}
void solve(){
	int n,k;cin>>n>>k;
	for (int i=1;i<=k;++i){
		string s;cin>>s;
		for (int j=0;j<n;++j)
			if (s[j]=='1') a[i]+=1<<j,++g[i];
	}
	for (int i=1;i<=k;++i)
		for (int j=1;j<=k;++j)
			if (i!=j && (a[i]&a[j])==a[i]) b[i].push_back(j);
	for (int i=1;i<=k;++i)
		sort(b[i].begin(),b[i].end(),[&](int x,int y){return g[x]>g[y];});
	int ans=-1,idx=0;
	vector<int>res;
	for (int i=1;i<=k;++i) id[i]=i;
	sort(id+1,id+k+1,[&](int x,int y){return g[x]>g[y];});
	for (int i=1;i<=k;++i)
		if (!Hungary(id[i],++idx)) res.push_back(id[i]),ans+=g[id[i]]+1;
	cout<<ans<<'\n';
	for (auto i:res){
		int x=i;vector<int>g;
		while (x) g.push_back(a[x]),x=matched[x];
		reverse(g.begin(),g.end());
		int la=0;
		for (auto i:g){
			for (int k=0;k<n;++k)
				if ((la^i)>>k&1) cout<<k<<' ',--ans;
			la=i;
		}
		if (ans) cout<<"R ",--ans;
	}
	cout<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t=1;
	// cin>>t;
	while (t--) solve();
	cerr<<"Running Time: "<<(double)clock()/CLOCKS_PER_SEC<<" s\n";
	return 0;
}
```

---

## 作者：xtx1092515503 (赞：3)

考虑若两个串 $s_i$ 与 $s_j$，有 $s_i\subset s_j$（指 $s_i$ 的 $1$ 位是 $s_j$ 的 $1$ 位的子集），则显然 $s_i$ 可以通过加边加成 $s_j$。我们对所有此种 $i,j$ 对，连一条从 $i$ 到 $j$ 的有向边。显然，边数最多是子集数，也即 $O(3^n)$ 级别的，可以建出。

考虑初始答案为所有串都暴力建出，即为 $\sum|s_i|$。我们可以用某个 $s_i$ 去匹配任一包含它的 $j$，这样子就可以在 $s_i$ 的基础上建出 $s_j$，也就是说总费用减少了 $|s_i|$。又因为包含关系必是DAG，故我们会发现这是一个DAG上最大路径覆盖问题。

考虑用网络流解决。设 $(x,y,z,c)$ 表示一条从 $x$ 到 $y$ 流量为 $z$ 费用为 $c$ 的边。于是我们拆点，对于原图中一条边 $(i,j)$，连边 $(i,j',1,-|s_i|)$，其中 $j'$ 表示 $j$ 的出点。同时，对于所有 $i$，连边 $(S,i,1,|s_i|)$ 与 $(i',T,1,0)$。同时，为了表示一条路径的终点享受不到优惠同时还要多花一次来重置状态，所以连边 $(i,T,1,1)$。这样子跑最小费用最大流就得到了答案（别忘了减一，因为最后一次不用重置）。方案可以直接由残量网络构造得出。

点数最大为 $2^n=1024$，边数最大为 $3^n=59049$，可以通过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[2010],res,nex[2010],las[2010];
char s[20];
namespace MCMF{
	const int N=3000,M=2000000;
	int head[N],cnt,dis[N],fr[N],id[N],S,T,cost;
	struct node{
		int to,next,val,cost;
	}edge[M];
	void ae(int u,int v,int w,int c){
		edge[cnt].cost=c,edge[cnt].next=head[u],edge[cnt].to=v,edge[cnt].val=w,head[u]=cnt++;
		edge[cnt].cost=-c,edge[cnt].next=head[v],edge[cnt].to=u,edge[cnt].val=0,head[v]=cnt++;
	}
	queue<int>q;
	bool in[N];
	bool SPFA(){
		memset(dis,0x3f,sizeof(dis)),dis[S]=0,q.push(S),in[S]=true;
		while(!q.empty()){
			int x=q.front();q.pop(),in[x]=false;
	//		printf("%d\n",x);
			for(int i=head[x];i!=-1;i=edge[i].next){
				if(!edge[i].val)continue;
				if(dis[edge[i].to]>dis[x]+edge[i].cost){
					dis[edge[i].to]=dis[x]+edge[i].cost,fr[edge[i].to]=x,id[edge[i].to]=i;
					if(!in[edge[i].to])in[edge[i].to]=true,q.push(edge[i].to);
				}
			}
		}
		if(dis[T]==dis[0])return false;
		int x=T,mn=0x3f3f3f3f;
		while(x!=S)mn=min(mn,edge[id[x]].val),x=fr[x];
		cost+=dis[T]*mn,x=T;
		while(x!=S)edge[id[x]].val-=mn,edge[id[x]^1].val+=mn,x=fr[x];
		return true;
	}
}
using namespace MCMF;
vector<int>v;
int main(){
	scanf("%d%d",&n,&m),memset(head,-1,sizeof(head)),S=2*m+1,T=2*m+2;
	for(int i=1;i<=m;i++){
		scanf("%s",s);
		for(int j=0;j<n;j++)if(s[j]=='1')a[i]+=(1<<j),res++;
		ae(S,i,1,__builtin_popcount(a[i])),ae(i+m,T,1,0),ae(i,T,1,1);
	}
	for(int i=1;i<=m;i++)for(int j=1;j<=m;j++){
		if(i==j)continue;
		if((a[i]&a[j])==a[j])ae(j,m+i,1,-__builtin_popcount(a[j]));
	}
	while(SPFA());
	for(int i=1;i<=m;i++)for(int j=head[i];j!=-1;j=edge[j].next)if(!edge[j].val&&edge[j].to!=S&&edge[j].to!=T)nex[i]=edge[j].to-m,las[edge[j].to-m]=i;
	for(int i=1;i<=m;i++){
//		printf("%d %d\n",nex[i],las[i]);
		if(las[i])continue;
		for(int j=i;j;j=nex[j])for(int k=0;k<n;k++)if((a[j]^a[las[j]])&(1<<k))v.push_back(k);
		v.push_back(-1);
	}
	printf("%d\n",cost-1);
	v.pop_back();
	for(auto i:v)putchar(i>=0?'0'+i:'R'),putchar(' ');putchar('\n');
	return 0;
}
```



---

## 作者：ywy_c_asm (赞：2)

这题其实不需要枚举子集建图啊……~~为什么官方题解也是这个啊……~~

我先说说我一开始的假的建图：把所有01串当成普通点，对每个关键状态$i$，向$T$连流量为1费用为0的边（这样是为了保证最大流经过了所有关键状态）。对于所有的$0...2^d-1$，枚举自身为0的位，把这位填成1后连流量无限费用为1的边，表示按了一位。并且让它们都向0连流量无限费用为1的边，表示按了Reset。最后让$S$向0连流量无限的边，表示初始状态。

然后这样建图后你发现连样例都过不去。因为我们把关键状态向$T$连了边，第一次到达这个关键状态后，流就会流到$T$，但是实际上我们还是可以在这个关键状态基础上继续进行操作的，就只能从$S$重新引一个流流到这，会产生额外的费用。

为了解决上面的问题，我们需要发现两个比较显然的性质：

**1.所有关键状态一定都能被到达。**

**2.Reset一定是在第一次到达某个关键状态后按的。**

关键状态必须要向$T$连边，那么该如何解决“继续操作”的问题呢？根据性质1，反正我迟早都要到达某个关键状态，那么我可以把第一次到达关键状态之后的继续操作，视作**与其无关**的一个新的开始。具体点说，就是我对每个关键状态$i$都建立一个副本$i'$，让它连和$i$一样的出边（除了$T$以外），让$S$直接向$i'$连流量为1（因为这仅用于第一次到达该关键状态）费用为0的边。这样，$i'$是不是被流，就和$i$是不是被到达过没有任何直接关系了，因为$i$一定会被到达过。

至于Reset的问题可以采用类似的解决方法，因为它和副本点一样，都是在第一次到达某个关键状态后的。我让$S$向0连两条边，一条流量为1费用为0，表示最初的状态，一条流量无限费用为1，表示再次从0开始需要按Reset。

于是这样建的图的点数是$O(2^d)$，边数$O(d2^d)$。

至于方案的构造，我们可以通过残量网络，推断出对于哪个01串按了哪一位，可以建一个新的普通有向图$G$，在$G$中互相连边表示01串之间的转移。而Reset，根据性质2，如果某个关键状态的副本点未被经过，那么我们在第一次到达这个关键状态后一定没有继续进行操作。这就有两种情况：①它是终止状态，这仅有一个。②它按了Reset。那么我们不妨假设它们都是②，让它们向0连表示Reset的边。然后对$G$求一条从0开始的欧拉路即可，显然，最后经过的一条边一定是Reset边，这是多走的，删掉即可。

code:

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 2100
using namespace std;
namespace ywy{
	typedef struct _b{
		int dest;int nxt;int len;int c;
	}bian;bian memchi[100000];
	int gn=2,heads[N],mincol[N],bv[N],que[100000],dis[N],gj[N],pre[N];
	inline void add(int s,int t,int l,int c){
		memchi[gn].dest=t;memchi[gn].len=l;memchi[gn].c=c;memchi[gn].nxt=heads[s];heads[s]=gn;gn++;	
	}
	inline int spfa(int s,int t){
		memset(dis,0x3f,sizeof(dis));
		int head=0,tail=1;
		mincol[que[0]=s]=1234567890;
		dis[s]=0;
		while(head<tail){
			int me=que[head++]; bv[me]=0;
			for(int i=heads[me];i;i=memchi[i].nxt){
				if(!memchi[i].c)continue;
				if(dis[me]+memchi[i].len<dis[memchi[i].dest]){
					dis[memchi[i].dest]=dis[me]+memchi[i].len;
					pre[memchi[i].dest]=i;
					mincol[memchi[i].dest]=min(mincol[me],memchi[i].c);
					if(!bv[memchi[i].dest])bv[que[tail++]=memchi[i].dest]=1;
				}
			}
		}
		if(dis[t]==dis[0]) return(dis[0]);
		int ans=dis[t]*mincol[t],cur=t;
		while(cur!=s){
			int me=pre[cur];memchi[me].c-=mincol[t];memchi[me^1].c+=mincol[t];cur=memchi[me^1].dest;
		}
		return ans;
	}
	namespace euler{
		typedef struct _b{
			int dest;int nxt;char c;int vis;
		}bian;bian memchi[100001];int gn=1,heads[N];
		inline void add(int s,int t,char c){
			memchi[gn].dest=t;memchi[gn].c=c;memchi[gn].nxt=heads[s];heads[s]=gn;gn++;	
		}
		void solve(int pt,vector<char> &vec){
			for(int i=heads[pt];i;i=memchi[i].nxt){
				if(memchi[i].vis) continue;
				memchi[i].vis=1;
				solve(memchi[i].dest,vec);
				vec.push_back(memchi[i].c);	
			}
		}
	}
	void ywymain(){
		int d,n; cin>>d>>n;
		int cnt=0;
		for(int i=1;i<=n;i++){
			char str[12]; cin>>str;
			int x=0;
			for(int j=0;j<d;j++)x=x*2+str[j]-'0';
			if(!x)continue;
			gj[x]=1; cnt++;
		}
		if(!cnt){
			cout<<0<<endl; return;	
		}
		int s=(1<<d)*2+1,t=s+1;
		add(s,1,0,1); add(1,s,0,0);
		add(s,1,1,1234567890); add(1,s,-1,0);
		for(int i=0;i<(1<<d);i++){
			if(gj[i]){
				add(s,i+1,0,1); add(i+1,s,0,0);
				add(i+(1<<d)+1,t,0,1); add(t,i+(1<<d)+1,0,0);
			}	
			for(int j=0;j<d;j++){
				if(!(i&(1<<j))){
					add(i+1,i+(1<<j)+(1<<d)+1,1,1234567890);
					add(i+(1<<j)+(1<<d)+1,i+1,-1,0);
					add(i+(1<<d)+1,i+(1<<j)+(1<<d)+1,1,1234567890);
					add(i+(1<<j)+(1<<d)+1,i+(1<<d)+1,-1,0);
				}
			}
		}
		int ans=0;
		while(1){
			int x=spfa(s,t);
			if(x==0x3f3f3f3f)break;
			ans+=x;	
		}
		for(int i=0;i<(1<<d);i++){
			if(gj[i]){
				for(int j=heads[i+1];j;j=memchi[j].nxt){
					if(memchi[j].dest==s&&!memchi[j].c){
						euler::add(i,0,'R'); break;	
					}
				}
			}
			for(int j=heads[i+1];j;j=memchi[j].nxt){
				if((j&1)||memchi[j].dest==t||memchi[j].dest==s) continue;
				char op;
				for(int k=0;k<d;k++){
					if(!(i&(1<<k))&&((memchi[j].dest-(1<<d)-1)&(1<<k))) op=d-k-1+'0';	
				}
				for(int k=0;k<memchi[j^1].c;k++) euler::add(i,memchi[j].dest-(1<<d)-1,op);	
			}
			for(int j=heads[i+(1<<d)+1];j;j=memchi[j].nxt){
				if((j&1)||memchi[j].dest==t||memchi[j].dest==s) continue;
				char op;
				for(int k=0;k<d;k++){
					if(!(i&(1<<k))&&((memchi[j].dest-(1<<d)-1)&(1<<k))) op=d-k-1+'0';	
				}
				for(int k=0;k<memchi[j^1].c;k++) euler::add(i,memchi[j].dest-(1<<d)-1,op);	
			}
			
		}
		vector<char> vec;
		euler::solve(0,vec);
		cout<<vec.size()-1<<endl;
		for(int i=(int)vec.size()-1;i>=1;i--) cout<<vec[i]<<" ";
	}
}
int main(){
	ywy::ywymain();
	return 0;	
}
```

---

## 作者：Drind (赞：0)

## 题目解析

每次可以使二进制数任意一位变成1，或者把二进制数清零。问需要至少多少次操作能出现所有给定状态？

我们考虑把每个状态看成一个点，这样就变成了一张有向无环图，于是我们在这张图上跑最小费用可行流即可。注意这题是有源汇的（每个点都可以到汇点），对于需要达成的状态，拆点把下界设成 1 即可。

输出方案稍微有点复杂。我们发现如果在原来的图上，只需要贪心地走有流量的边，并且每次减一，得到的绝对是对的（因为每次从这个点出发走不同的边没有先后关系，先走哪儿没有区别）。考虑上下界网络流的建图方式，就是先流满下界再在残余网络上修改，所以我们只需要把下界加回原图即可。

省略费用流板子如下。

```cpp
int d[N];
queue<int>q;

void dfs2(int u,int f){//输出方案
	q.push(u);
	for(int i=head[u];~i;i=edge[i].nxt){
		if(i%2==1) continue;//不走反边，只走正边
		int v=edge[i].to; 
		if(v==t) continue;//注意别流到新建汇点去了
		if(v==f) continue;
		if(edge[i^1].flow){//贪心地流，注意反边才是这条边流过的流量，正边是残余流量
			edge[i^1].flow--; dfs2(v,u);
		}
	}
}

int st[N],to[N];
queue<int>ans;

inline void fake_main(){
	memset(head,-1,sizeof head);
	int n,m; cin>>n>>m; s=N-1,t=s-1;
	int ss=t-1; int tt=ss-1;
	for(int i=1;i<=m;i++){
		string s; cin>>s;
		int tmp=0; for(int j=0;j<s.size();j++) tmp*=2,tmp+=s[j]-'0';
		d[tmp*2]++; d[tmp*2+1]--; st[tmp]=1; to[i]=tmp;//存下来有下界的边是谁
	}
	adde(ss,0,inf,0);
	for(int i=0;i<(1<<n);i++){
		adde(i*2+1,tt,inf,1);
		if(st[i]==1) st[i]=cnt+1;
		adde(i*2,i*2+1,inf,0);
		for(int j=0;j<n;j++){
			if(i&(1<<j)) continue;
			adde(i*2+1,(i|(1<<j))*2,inf,1);//加边
		}
	}
	for(int i=1;i<(1<<(n+1));i++){//上下界网络流的补全流量边
		if(d[i]<0) adde(s,i,-d[i],0);
		if(d[i]>0) adde(i,t,d[i],0);
	}
	adde(tt,ss,inf,0);
	mcmf();
	cout<<mncos-1<<"\n";
	for(int i=1;i<=m;i++){//下界加回边中，注意这里也是加在反边上
		edge[st[to[i]]^1].flow++;
	}
	dfs2(ss,-10086);//统计答案
	int pre=q.front(); q.pop();
	while(!q.empty()){ 
		int tmp=q.front(); q.pop();
		if(pre==(tmp^1)){//如果是拆点中间的边，不输出
			pre=tmp; continue;
		}else{
			if(pre==ss){//如果回到原图源点，不输出
				pre=tmp; continue;
			}
			if(tmp==tt){//如果走到汇点，也就是清零了，注意这里的 9999999 在下文等于字符 R
					ans.push(9999999);
			}
			else{//统计答案，这里的最高位相当于原来的第 0 位所以要取反
				ans.push((n-1)-log2((tmp/2)^((pre-1)/2)));
			}
		}
		pre=tmp;
	}
	
	
	while(!ans.empty()){//输出答案，最后一个 R 不用输出（所以前面的 mncos 要减去 1）
		int tmp=ans.front(); ans.pop(); if(tmp==9999999&&!ans.empty()){
			cout<<"R ";
		}
		if(tmp<9999999) cout<<tmp<<" ";
	}
}

signed main(){fake_main();}
```

---

