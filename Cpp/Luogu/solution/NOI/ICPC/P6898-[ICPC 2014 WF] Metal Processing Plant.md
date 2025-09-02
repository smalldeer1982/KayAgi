# [ICPC 2014 WF] Metal Processing Plant

## 题目描述

Yulia 在叶卡捷琳堡的一家金属加工厂工作。该工厂处理从乌拉尔山脉开采的矿石，从中提取黄铜矿、铂金和黄金等贵金属。每个月，工厂会收到 $n$ 批未加工的矿石。Yulia 需要根据相似性将这些矿石分成两组。然后，每组被送往工厂的两个矿石加工建筑之一。

为了进行这种划分，Yulia 首先为每对矿石 $1 \le i \le n$ 和 $1 \le j \le n$ 计算一个数值距离 $d(i, j)$，距离越小，矿石 $i$ 和 $j$ 越相似。对于矿石的一个子集 $S \subseteq \{ 1, \ldots , n\} $，她定义 $S$ 的差异度 $D$ 为子集中一对矿石之间的最大距离，即，

$$ D(S) = \max _{i, j \in S} d(i, j). $$

然后，Yulia 将矿石划分为两个子集 $A$ 和 $B$，使得它们的差异度之和 $D(A) + D(B)$ 最小。你的任务是帮助她找到这种划分。

## 说明/提示

时间限制：2000 毫秒，内存限制：1048576 kB。

国际大学生程序设计竞赛（ACM-ICPC）世界总决赛 2014。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5
4 5 0 2
1 3 7
2 0
4
```

### 输出

```
4
```

## 样例 #2

### 输入

```
7
1 10 5 5 5 5
5 10 5 5 5
100 100 5 5
10 5 5
98 99
3
```

### 输出

```
15
```

# 题解

## 作者：JoshAlMan (赞：11)

判定性问题比较好做，可以 $O(n^2)$ 做 2-SAT。但这样复杂度是 $O(n^6)$。可以枚举一条最大边，然后二分次大边（固定了最大边以后符合条件次大边的值显然是一个后缀），这样是 $O(n^4 \log n )$，双指针可以把 $\log$ 去掉（然后再乱搞一下可以卡常过此题）

然后的奇偶环优化非常的神仙，考虑从大到小枚举最大边，然后把之前所有边构成的联通块用并查集维护：

* 如果构成了奇环，考虑染色后，必要条件就是在现在的图上边没有相邻的颜色，但此时已经有奇环了，所以必然不可能存在最大边 $< $ 当前边的情况，可以做完一次直接 $\text{break}$
* 如果构成了偶环，那么你考虑要用到这个作为一个集合之内最大值，用到它就说明两端要同色，但这两端又隔奇数个点，所以没法做到这点，理由类似奇环，可以 $\text{continue}$
* 否则二分次大边做一遍

这样只会做 $n \log n$ 次 2-SAT（别忘最大边可以是 $0$），总复杂度是 $O(n ^3 \log n)$ 可以通过。



---

## 作者：xujindong_ (赞：5)

首先可以 $O(n^4)$：枚举两个点集的权值，限制是一些边的两端不能同时出现在某个点集中，可以 2-SAT。

观察性质。枚举较大的一个权值，则边权大于这个权值的边的两端不能出现在同一个集合中。注意到若加入这条边后成环，则可以确定边的状态。若形成奇环，则之后的都不合法，可以退出；若形成偶环，这条边两端不在同一集合，可以跳过。拿个带权并查集维护，此时最多只用枚举最大生成树上的边，然后二分另一个点集的权值，$O(n^3\log n)$。

注意到如果只维护图上的边，可以维护两个指针暴力移动加边删边，每次二分的移动量是 $O(n^2)$ 的。考虑优化 2-SAT，使用比 Tarjan 结构更简单的 Kosaraju，只需要支持快速找下一个未访问的点。用 `bitset` 存邻接矩阵，每次 `i=(g[pos]&~vis)._Find_next(i)`。这样只会遍历 $O(n)$ 个点和边，每次找后继是 $O(\frac nw)$ 的。这样除了一个 $w$，复杂度 $O(n^3+\frac{n^3\log n}w)$，可以视为 $O(n^3)$。

进一步地，我们还可以发现一个剪枝，先求出需要二分的权值后从小往大枚举，二分上界改成 $\min(w,ans-w)$，如果取到上界不合法就不二分。考虑这样为什么快，在不刻意卡的情况下，每个点对应的答案可以视为随机序列，而我们知道前缀最大值的期望个数是 $O(\sum_{i=1}^n \frac 1{n-i+1})=O(\log n)$ 的。此时 2-SAT 的次数来到了 $O(n+\log^2 n)$ 次，$O(n^3+\frac{n^2\log^2n}w)$。如果要保证任意数据都是这个复杂度，将这 $n$ 个点 shuffle 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,f[205],num[405],l,r,st[405],top,cc,ans=0x3f3f3f3f;
bool w[205];
bitset<405>g[405],h[405],vis;
vector<int>q;
struct edge{
  int u,v,w;
  bool operator<(edge a)const{
    return w<a.w;
  }
}e[19905];
int find(int x){
  if(!f[x])return x;
  int y=find(f[x]);
  return w[x]^=w[f[x]],f[x]=y;
}
void dfs1(int pos){
  vis[pos]=1;
  for(int i=(g[pos]&~vis)._Find_first();i<g[pos].size();i=(g[pos]&~vis)._Find_next(i))dfs1(i);
  st[++top]=pos;
}
void dfs2(int pos){
  vis[pos]=1,num[pos]=cc;
  for(int i=(h[pos]&~vis)._Find_first();i<g[pos].size();i=(h[pos]&~vis)._Find_next(i))dfs2(i);
}
bool check(int llim,int rlim){
  vis=top=cc=0;
  while(l<llim)l++,g[e[l].u][n+e[l].v]=g[e[l].v][n+e[l].u]=h[n+e[l].v][e[l].u]=h[n+e[l].u][e[l].v]=0;
  while(l>llim)g[e[l].u][n+e[l].v]=g[e[l].v][n+e[l].u]=h[n+e[l].v][e[l].u]=h[n+e[l].u][e[l].v]=1,l--;
  while(r<rlim)r++,g[n+e[r].u][e[r].v]=g[n+e[r].v][e[r].u]=h[e[r].v][n+e[r].u]=h[e[r].u][n+e[r].v]=0;
  while(r>rlim)g[n+e[r].u][e[r].v]=g[n+e[r].v][e[r].u]=h[e[r].v][n+e[r].u]=h[e[r].u][n+e[r].v]=1,r--;
  for(int i=1;i<=2*n;i++)if(!vis[i])dfs1(i);
  vis=0;
  for(int i=top;i>=1;i--)if(!vis[st[i]])cc++,dfs2(st[i]);
  for(int i=1;i<=n;i++)if(num[i]==num[n+i])return 0;
  return 1;
}
int solve(int x){
  int l=0,r=min(x,(int)(upper_bound(e+1,e+m+1,(edge){0,0,ans-e[x].w})-e-1));
  if(!check(x,r))return 0x3f3f3f3f;
  while(l<r){
    int mid=(l+r)>>1;
    if(check(x,mid))r=mid;
    else l=mid+1;
  }
  return e[x].w+e[l].w;
}
int main(){
  ios::sync_with_stdio(0),cin.tie(0),cin>>n;
  for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)m++,e[m].u=i,e[m].v=j,cin>>e[m].w;
  sort(e+1,e+m+1),l=r=m;
  for(int i=m;i>=0;i--){
    int u=find(e[i].u),v=find(e[i].v);
    if(u==v){
      if(w[e[i].u]^w[e[i].v])continue;
      else{
        q.push_back(i);
        break;
      }
    }
    q.push_back(i),f[v]=u,w[v]=w[e[i].u]^w[e[i].v]^1;
  }
  for(int i=q.size()-1;i>=0&&e[q[i]].w<ans;i--)ans=min(ans,solve(q[i]));
  return cout<<ans<<'\n',0;
}
```

---

## 作者：forest114514 (赞：3)

虽然这应该是一个 $O(n^2\log n+\frac{n^3}{w})$ 的做法，但是因为常数太大了在本题和 $n=2000$ 的随机数据下都被 $O(n^3+\frac{n^3 \log n}{w})$ 打爆了。

枚举 $D(A)\leq x$，显然 $D(A)$ 越小 $D(B)$ 越大，所以只用 check $O(n^2)$ 次 $D(A)\leq x,D(B)\leq y$ 的合法性。

我们相当于知道 $i\in A$ 或者 $i\in B$ 的时候，另外一个 $j$ 是否能再同一个集合内，这样直接 2-SAT 是 $O(n^2)$ 的，于是我们可以做到 $O(n^4)$，但显然过不去。

剩下的优化需要暂时脱离 2-SAT 思考，感觉优化形式上和校园旅行差不多，不过本题不是这么明显。

不妨认为 $D(A)\geq D(B)$，我们枚举 $D(A)=X$，显然对于 $dis(i,j)>X$ 就不能有连边，我们把 $dis(i,j)>X$ 的点对两两连一条边，显然我们需要划分成两个集合使得两个集合内两两没有连边，显然这是一个二分图，我们每一次新增一些边判断是否二分图可以带权并查集维护，容易做到 $O(n^2)$。

然后此时显然我们对于这个二分图只用按时间保留一个生成森林中的边，就能传递能否再一个集合的信息了，显然只用保留最小生成森林中的边。

注意到我们此时就只用考虑 $O(n)$ 个有效的 $D(A)$，然后再考虑 $D(B)$ 就可以二分答案只用做 $O(n\log n)$ 次 2-SAT，可以做到 $O(n^3\log n)$，已经可以通过本题了。

对于一个 $D(A)$，我们考虑在二分的时候暴力维护对应的图，注意到只用修改 $O(n^2)$ 次图，然后跑 $O(\log n)$ 次 2-SAT，使用 bitset 优化 Kosaraju 的话可以做到 $O(n^3+\frac{n^3\log n}{w})$，可以认为是 $O(n^3)$。

还能再优化，显然 $D(A)$ 越大合法的最小的 $D(B)$ 也就越小，考虑整体二分套二分，我们每次可以二分找出的 $D(A)\leq S_{mid}$ 时可以找到的最小的合法的 $D(B)$，然后递归成子问题，此时限制的值域区间也会缩减。

这样我们调用 2-SAT 的次数是 $T(m,n)=T(X,\frac{n}{2})+T(m-X,\frac{n}{2})+O(\log m)$，直觉告诉我们 $X$ 均分才能卡满，于是可以认为调用次数是 $T(n^2,n)=2T(\frac{n^2}{2},\frac{n}{2})+O(\log n^2)=O(n)$ 的，于是 2-SAT 的部分时间复杂度为 $O(\frac{n^3}{w})$。

然后考虑移动值域限制的时候边的修改次数，每一层二分的修改次数是二分长度规模的，而且我们移动值域可以借鉴决策单调性分治也是值域长度的，于是我们还是可以得到 $T(m,n)=T(X,\frac{n}{2})+T(m-X,\frac{n}{2})+O(m+n)$， 这样可以粗略估计 $T(n^2,n)=O(n^2\log n)$，于是我们只用修改 $O(n^2\log n)$ 次边。

最后我们就能做到 $O(n^2\log n+\frac{n^3}{w})$ 了，应该没有假吧，如果假了请指出一下谢谢。

注意特判只有一个集合的情况，显然答案就是最大边权。

code：

```cpp
bool _ST;
const int N=205;
int n,a[N][N],ans;
int fa[N],w[N];
int getf(int x){
	if(x==fa[x]) return x;
	int p=getf(fa[x]);
	w[x]^=w[fa[x]];
	return fa[x]=p;
}

bitset<N*2> e[N*2],g[N*2],vis;
int st[N*2],top,col[N*2],cc;
void dfs1(int x){
    vis[x]=1;
    for(int y=((~vis)&e[x])._Find_first();y<vis.size();y=((~vis)&e[x])._Find_next(y)) dfs1(y);
    st[++top]=x;
}
void dfs2(int x){
    col[x]=cc,vis[x]=1;
    for(int y=((~vis)&g[x])._Find_first();y<vis.size();y=((~vis)&g[x])._Find_next(y)) dfs2(y);
}
int c[N*N],ct;
vector<pii> opt[N*N],buk;
pii s[N*N];
int cl,cr,tot;
bool check(int val,int qmid){
     while(cl&&a[s[cl].fi][s[cl].sc]>val){
        e[s[cl].fi][s[cl].sc+n]=e[s[cl].sc][s[cl].fi+n]=1;
        g[s[cl].sc+n][s[cl].fi]=g[s[cl].fi+n][s[cl].sc]=1;
        --cl;
    }
    while(cl<tot&&a[s[cl+1].fi][s[cl+1].sc]<=val){
        ++cl;
        e[s[cl].fi][s[cl].sc+n]=e[s[cl].sc][s[cl].fi+n]=0;
        g[s[cl].sc+n][s[cl].fi]=g[s[cl].fi+n][s[cl].sc]=0;
    }
    while(cr&&a[s[cr].fi][s[cr].sc]>qmid){
        e[s[cr].fi+n][s[cr].sc]=e[s[cr].sc+n][s[cr].fi]=1;
        g[s[cr].sc][s[cr].fi+n]=g[s[cr].fi][s[cr].sc+n]=1;
        --cr;
    }
    while(cr<tot&&a[s[cr+1].fi][s[cr+1].sc]<=qmid){
        ++cr;
        e[s[cr].fi+n][s[cr].sc]=e[s[cr].sc+n][s[cr].fi]=0;
        g[s[cr].sc][s[cr].fi+n]=g[s[cr].fi][s[cr].sc+n]=0;
    }

   	top=0,vis.reset();
    rep(i,1,n*2) if(!vis[i]) dfs1(i);
    vis.reset();
    per(i,top,1) if(!vis[st[i]]) cc=st[i],dfs2(st[i]);
    
    rep(i,1,n) if(col[i]==col[i+n]) return false;
    return true;
}
void divide(int l,int r,int L,int R){
    if(l>r||L>R) return;
    int mid=l+r>>1,val=a[buk[mid].fi][buk[mid].sc];

    int ql=L,qr=R;
    while(ql<qr){
        int qmid=ql+qr>>1;
        if(check(val,qmid)) qr=qmid;
        else ql=qmid+1;
    }
    if(check(val,ql)) ans=min(ans,c[val]+c[ql]);

    divide(l,mid-1,ql,R);
    divide(mid+1,r,L,ql);
}
bool _ED;
signed main(){
	fprintf(stderr,"%.20lf MB\n",(&_ST-&_ED)/1048576.0);
	//ios::sync_with_stdio(false);
	//cin.tie(0);cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
    read(n);
    c[++ct]=0;
    rep(i,1,n) rep(j,i+1,n) read(a[i][j]),c[++ct]=a[i][j];
    sort(c+1,c+1+ct),ct=unique(c+1,c+1+ct)-c-1,ans=c[ct];
    
    rep(i,1,n) rep(j,i+1,n) a[i][j]=a[j][i]=lower_bound(c+1,c+1+ct,a[i][j])-c,opt[a[i][j]].pb({i,j}),s[++tot]={i,j};
    
    sort(s+1,s+1+tot,[&](pii x,pii y){return a[x.fi][x.sc]<a[y.fi][y.sc];});
    rep(i,1,n) fa[i]=i;

    bool fl=1;
    per(i,ct,1){

        for(auto j:opt[i]){
            int u=j.fi,v=j.sc;
            int fu=getf(u),fv=getf(v);
            if(fu==fv){
                if(w[u]==w[v]){buk.pb(j),fl=0;break;}
                continue;
            }
            buk.pb(j);
            w[fu]=w[u]^w[v]^1,fa[fu]=fv;
        }
        if(!fl) break;
    }
    if(fl) buk.pb({0,0});
    cl=cr=tot;
    reverse(buk.begin(),buk.end());
    divide(0,buk.size()-1,1,ct);
    write(ans,'\n');
	fprintf(stderr,"%.4lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	return 0;
}
```

---

## 作者：hzoi_liuchang (赞：1)

## 分析
把人抽象成节点，那么人和人之间的边权就是它们的矛盾值，

这种两个限制的问题肯定要把限制变成一个。

所以我们把边权从大到小排序，

枚举每一条边，强制左边的集合必须选这条边并且这条边的价值是最大的。

对于所有边权比这条边小的边，我们最后肯定可以都把它们放到左边的集合中，

所以需要考虑的只是边权比这条边大的边如何放。

我们把所有边权比这条边大的边拉出来进行奇偶染色，

如果出现了奇环肯定无解，而且之后也一定无解，直接 $break$ 就行了，

否则我们肯定要把这些点分成两部分，一部分给左边的集合，一部分给右边的集合。

如果两个点在同一个联通块中并且染色相同，那么就必须划分到一个集合中。

对于和当前边的左右端点在一个联通块中并且染色相同的点，强制放到左边的集合中，

而且要满足右边的集合价值最小。

这个问题我也没有什么好的做法，直接跑一个 $dfs$ 就行了，

复杂度肯定是不对的，但是跑得比正解还快，貌似也卡不住。
## 代码
``` cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
#define rg register
inline int read(){
	rg int x=0,fh=1;
	rg char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*fh;
}
const int maxn=255;
int n,a[maxn][maxn],ans=0x7f7f7f7f,tot,nans;
struct asd{
	int zb,yb,val;
	asd(){}
	asd(rg int aa,rg int bb,rg int cc){
		zb=aa,yb=bb,val=cc;
	}
}b[maxn*maxn];
bool cmp(rg asd aa,rg asd bb){
	return aa.val>bb.val;
}
std::vector<int> g[maxn],tmp1[maxn],tmp2[maxn];
int cnt,shuyu[maxn],col[maxn],sta[maxn],tp,nid;
bool vis[maxn],haha,jud[maxn];
void dfs(rg int now,rg int ncol){
	col[now]=ncol;
	shuyu[now]=cnt;
	for(rg int i=0;i<g[now].size();i++){
		if(!col[g[now][i]]){
			dfs(g[now][i],3-ncol);
		} else {
			if(col[now]==col[g[now][i]]) haha=1;
		}
	}
}
void dfs2(rg int now,rg int mans){
	if(mans>=nans) return;
	if(mans+b[nid].val>=ans) return;
	if(now>cnt){
		nans=std::min(nans,mans);
		return;
	}
	rg int tmp=mans;
	for(rg int i=0;i<tmp1[now].size();i++){
		sta[++tp]=tmp1[now][i];
		for(rg int j=1;j<tp;j++){
			tmp=std::max(tmp,std::max(a[sta[tp]][sta[j]],a[sta[j]][sta[tp]]));
		}
	}
	dfs2(now+1,tmp);
	for(rg int i=0;i<tmp1[now].size();i++) tp--;
	if(!jud[now]){
		tmp=mans;
		for(rg int i=0;i<tmp2[now].size();i++){
			sta[++tp]=tmp2[now][i];
			for(rg int j=1;j<tp;j++){
				tmp=std::max(tmp,std::max(a[sta[tp]][sta[j]],a[sta[j]][sta[tp]]));
			}
		}
		dfs2(now+1,tmp);
		for(rg int i=0;i<tmp2[now].size();i++) tp--;
	}
}
int main(){
	while(scanf("%d",&n)!=EOF){
		ans=0x7f7f7f7f,haha=0,tot=0;
		for(rg int i=1;i<=n;i++){
			for(rg int j=i+1;j<=n;j++){
				a[i][j]=read();
				b[++tot]=asd(i,j,a[i][j]);
			}
		}
		for(rg int i=1;i<=n;i++) vis[i]=0,g[i].clear();
		if(n==2){
			printf("0\n");
			continue;
		}
		std::sort(b+1,b+tot+1,cmp);
		rg int aa,bb;
		for(rg int i=1;i<=tot;i++){
			for(rg int j=1;j<=n;j++) jud[j]=0,shuyu[j]=0,col[j]=0,tmp1[j].clear(),tmp2[j].clear();
			cnt=0,nid=i;
			if(b[i].val<b[i-1].val){
				for(rg int j=i-1;j>=1;j--){
					if(b[j].val!=b[i-1].val) break;
					aa=b[j].zb,bb=b[j].yb;
					g[aa].push_back(bb),g[bb].push_back(aa);
					vis[aa]=vis[bb]=1;
				}
			}
			for(rg int j=1;j<=n;j++){
				if(vis[j] && !shuyu[j]){
					cnt++;
					dfs(j,2);
				}
			}
			if(haha) break;
			if(shuyu[b[i].zb]==shuyu[b[i].yb] && col[b[i].zb]!=col[b[i].yb]) continue;
			for(rg int j=1;j<=n;j++){
				if(vis[j]){
					if(shuyu[b[i].zb]==shuyu[j]){
						if(col[b[i].zb]!=col[j]){
							tmp1[shuyu[j]].push_back(j);
							jud[shuyu[j]]=1;
						}
					} else if(shuyu[b[i].yb]==shuyu[j]){
						if(col[b[i].yb]!=col[j]){
							tmp1[shuyu[j]].push_back(j);
							jud[shuyu[j]]=1;
						}
					} else {
						if(col[j]&1) tmp1[shuyu[j]].push_back(j);
						else tmp2[shuyu[j]].push_back(j);
					}
				}
			}
			nans=0x3f3f3f3f,tp=0;
			dfs2(1,0);
			ans=std::min(ans,nans+b[i].val);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

