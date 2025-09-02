# [USACO11JAN] Bottleneck G

## 题目描述

WC正在召集奶牛,他的农场有一个包含 ***N*** 块农田的网络，编号为 **1 -- N** ，每个农场里有 $C_i$ 头牛。农场被 **N-1**  条 **单向** 边链接,（每个农场有通向$P_i$的路） 保证从任何点可以到达1号点。WC想让所有奶牛集中到1号农场。 

**时间是离散的** 奶牛可以在1单位时间里走过任意多条道路，但是每条路有一个容纳上限 *$M_i$*  并且奶牛不会离开1号农场(农场没有容量上限) 

### 每一个单位时间，奶牛可以选择如下几种行动 
1. 留在当前的农场
2. 经过几条道路，向1号农场移动（需要满足$M_i$）

WC想要知道有多少牛可以在某个特定的时刻到达1号农场，
他有一张列着 ***K*** 个时间（分别为$T_i$)的单子
，他想知道在每个$T_i$, 采用最优策略在$T_i$结束最多能有多少牛到1号农场

## 说明/提示

$1 \le N \le  10^5$

$1 \le C_i \le  10^9$

$0 \le M_i \le 10^9$

$1 \le P_i \le N$

$1 \le K \le 10^4$

$1 \le T_i \le 10^9$

## 样例 #1

### 输入

```
4 1 
1 1 5 
2 12 7 
3 12 3 
5 
```

### 输出

```
25 
```

# 题解

## 作者：bztMinamoto (赞：19)

打广告->[这里](https://www.cnblogs.com/bztMinamoto/p/9622691.html)

感觉这题的思路还是挺不错的。然而为啥全网就一个题解而且只有代码……然后我只好看着代码理解了好久……

题意就是有一棵树，每一个节点向他父亲节点连边，且有一个容量表示每一秒可以经过的牛的数量，每一个点有一堆牛，在满足容量限制的情况下可以不断往祖先跳直到跳到1节点。然后问你在保证总时间最短的情况下第$t$秒1节点有多少头牛

首先，不难发现一个贪心，就是如果向父亲的边能够流满的时候，流满一定比不流满优

那么我们令每一条边都强制流满，然后对每个点记录一个值$pass[i]$，值为它能向父亲流的最大的流量减去它的儿子们向它流的最大流量，不难发现它代表如果每条边都流满之后每秒能有多少头牛离开这个点向祖先去。

那么我们设每一个节点开始时牛的个数为$cow[i]$，那么，$cow[i]/pass[i]$就代表这一个节点的所有牛都走光所需要的时间

那么令$t=cow[i]/pass[i]$，当时间小于等于$t$的时候，我们需要考虑这一个点还剩下多少头牛。当时间大于$t$的时候，我们已经不需要再考虑这个点还剩下多少头牛了，因为可以在满流之后让它所有的牛都到它的父亲那里去。那么，我们可以把它和它的父亲看做同一个点，牛的数量为两个点之和，$pass[fa[i]]$也是两个点之和（它和父亲之间的那条边的流量因为父亲减一次它加一次已经抵消了），然后再对这个点记录一个新的$t$就好了。这个可以用一个并查集维护

那么，我们对询问按时间排序。当询问的时间大于当前$t$的时候，我们把所有$t$小于等于询问的时间的点全都和它的父亲给并起来。当询问的时间小于等于当前$t$时，答案就是$cow[1]+pass[1]*$询问的时间（$cow[1]$代表所有已经被缩到这一个点的总的牛的数量，然后1点的pass肯定是负数，所以减去就相当于加上这个点的儿子的点全都满流向它流，在询问的这段时间里能流多少）

然后总不可能维护时间轴……所以开个优先队列把所有点的$t$给扔进去就好了，反正就这些点的$t$有用

讲的应该还蛮清楚的吧……
```
// luogu-judger-enable-o2
//minamoto
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline ll read(){
    #define num ch-'0'
    char ch;bool flag=0;ll res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
inline void print(ll x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]='\n';
}
const int N=100005;
struct query{ll t,res;int id;}ask[N];
inline bool cmp1(query x,query y){return x.t<y.t;}
inline bool cmp2(query x,query y){return x.id<y.id;}
struct node{
    ll t;int x;node(){}
    node(ll t,int x):t(t),x(x){}
    inline bool operator <(const node &b)const
    {return t>b.t;}
};
priority_queue<node> q;
int fa[N],f[N],lim[N];ll cow[N],pass[N];
int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
int n,m;
int main(){
//	freopen("testdata.in","r",stdin);
    n=read(),m=read();
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=2;i<=n;++i)
    f[i]=read(),cow[i]=read(),lim[i]=read(),pass[f[i]]-=lim[i],pass[i]+=lim[i];
    for(int i=1;i<=m;++i)
    ask[i].t=read(),ask[i].id=i;
    sort(ask+1,ask+1+m,cmp1);
    for(int i=2;i<=n;++i)
    if(pass[i]>0)
    q.push(node(cow[i]/pass[i],i));
    int l=1,x,tp;
    while(!q.empty()&&l<=m){
        while(l<=m&&ask[l].t<=q.top().t)
        ask[l].res=cow[1]-pass[1]*ask[l].t,++l;
        if(fa[q.top().x]!=q.top().x){q.pop();continue;}
        x=q.top().x,tp=find(f[x]),cow[tp]+=cow[x];
        pass[tp]+=pass[x],fa[x]=tp;
        if(pass[tp]>0) q.push(node(cow[tp]/pass[tp],tp));
        q.pop();
    }
    sort(ask+1,ask+1+m,cmp2);
    for(int i=1;i<=m;++i) print(ask[i].res);
    Ot();
    return 0;
}
```

---

## 作者：Little09 (赞：6)



### 题意

给定一棵大小为 $n$，根为 $1$ 的树，第 $i$ 个节点上有 $C_i$ 个人，每个人都往根节点上跑，但是每条边有容量，第 $i$ 条边在 $1s$ 内只能有 $M_i$ 个人通过。一个人可以通过很多条边。$q$ 次询问，每次问 $t_i$ 时有多少人到达根节点。

$1\le n,q\le 5\times 10^5$，$1\le C_i,M_i,t_i \le 10^9$。

------------


### 思路

首先肯定是每条边能满就满，尽可能往上走。

对于一个节点 $u$，我们可以考虑它一般情况下，会往父亲节点送一些人，也会从儿子节点收到人。这样的情况是在 $u$ 和它的儿子都充分有人的时候。我们算出每个点人数减少的速度 $S_i$，即向上送人速度与送来人速度的差。

定义 $Time_i=\lfloor\dfrac{C_i}{S_i}\rfloor$，可见 $Time$ 值最小的点一定先送完人。设此点为 $u$，容易发现此点之后只是一个中转站，送来的人直接往上送，于是我们可以把 $u$ 和它的父亲 $F_u$ 合并为一个点。

所以我们每次取出 $Time$ 最小的点，通过并查集维护联通关系和 $C$ 与 $S$ 的转移即可。

对于询问 $t$，我们只要 $t$ 时处于哪一阶段，答案显然是当时的 $C_1-S_1*t$。

代码很容易实现。

---

## 作者：Inui_Sana (赞：2)

来一个无脑线段树合并做法。

考虑记前 $t$ 秒有 $f_u(t)$ 头牛能通过 $u$ 点到父亲的边。则有：

$$f_u(t)=\min(m_ut,\sum_{v\in son_u}f_v(t))$$

并且有个显然的结论：$m_ut\ge\sum_{v\in son_u}f_v(t)$ 的 $t$ 是一段前缀。然后可以二分出分界点，考虑怎么处理 $f_u$。

发现分界点后面的是一个分段函数，前面则是 $f_u(t)=m_ut$ 这个一次函数，所以可考虑将这个函数用线段树维护，维护每个点的 $k,b$。需要支持区间加一次函数，区间赋 $0$，以及合并。总复杂度 $O(n\log^2 V)$。

但是金钩爷 @dieselhuang 发现这是凸的，故可以 $O(n\log V)$ 也是线段树合并解决。/bx

code：

```cpp
bool Mbe;
int n,m,k=1e9,sum,rt[N],a[N],c[N];
int tot,head[N];
struct node{
	int to,nxt;
}e[N];
il void add(int u,int v){
	e[++tot]={v,head[u]},head[u]=tot;
}
struct SGT{
	int cur,ls[M],rs[M];
	ll tr[M][2];
	il void reset(int o,ll x,ll y){
		tr[o][0]+=x,tr[o][1]+=y;
	}
	il void pushdown(int o){
		if(!tr[o][0]&&!tr[o][1]){
			return;
		}
		if(!ls[o]){
			ls[o]=++cur;
		sum++;
		}
		if(!rs[o]){
			rs[o]=++cur;
		sum++;
		}
		reset(ls[o],tr[o][0],tr[o][1]);
		reset(rs[o],tr[o][0],tr[o][1]);
		tr[o][0]=tr[o][1]=0;
	}
	void merge(int l,int r,int &o,int u){
		if(!o||!u){
			o|=u;
			return;
		}
		tr[o][0]+=tr[u][0],tr[o][1]+=tr[u][1];
		int mid=(l+r)>>1;
		merge(l,mid,ls[o],ls[u]);
		merge(mid+1,r,rs[o],rs[u]);
	}
	ll query(int l,int r,int o,int x){
		if(l==r){
			return 1ll*tr[o][1]*x+tr[o][0];
		}
		int mid=(l+r)>>1;
		if(x<=mid){
			if(ls[o]){
				pushdown(o);
				return query(l,mid,ls[o],x);
			}
			return 1ll*tr[o][1]*x+tr[o][0];
		}
		if(rs[o]){
			pushdown(o);
			return query(mid+1,r,rs[o],x);
		}
		return 1ll*tr[o][1]*x+tr[o][0];
	}
	void updateA(int l,int r,int &o,int x,int y,int a,int b){
		if(x>y)return;
		if(!o){
			o=++cur;
		}
		if(l>=x&&r<=y){
			reset(o,a,b);
			return;
		}
		pushdown(o);
		int mid=(l+r)>>1;
		if(x<=mid){
			updateA(l,mid,ls[o],x,y,a,b);
		}
		if(y>mid){
			updateA(mid+1,r,rs[o],x,y,a,b);
		}
	}
	void updateR(int l,int r,int &o,int x,int y){
		if(x>y)return;
		if(!o){
			return;
		}
		if(l>=x&&r<=y){
			o=0;
			return;
		}
		pushdown(o);
		int mid=(l+r)>>1;
		if(x<=mid){
			updateR(l,mid,ls[o],x,y);
		}
		if(y>mid){
			updateR(mid+1,r,rs[o],x,y);
		}
	}
}T;
void dfs(int u,int f){
	go(i,u){
		int v=e[i].to;
		dfs(v,u);
		T.merge(1,k,rt[u],rt[v]);
	}
	if(u==1){
		return;
	}
	int l=1,r=k,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(c[u]+T.query(1,k,rt[u],mid)>=1ll*a[u]*mid){
			l=(ans=mid)+1;
		}else{
			r=mid-1;
		}
	}
	T.updateR(1,k,rt[u],1,ans);
	T.updateA(1,k,rt[u],1,ans,0,a[u]);
	T.updateA(1,k,rt[u],ans+1,k,c[u],0);
}
void Yorushika(){
	scanf("%d%d",&n,&m);
	rep(i,2,n){
		int u=read();c[i]=read(),a[i]=read();
		add(u,i);
	}
	dfs(1,0);
	rep(i,1,m){
		int x=read();
		write(T.query(1,k,rt[1],x)),pc('\n');
	}
}
bool Med;
signed main(){
	cerr<<(&Mbe-&Med)/1048576.0;
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：Daniel1234 (赞：1)

# 题意

一棵树，每个节点有一定数量的奶牛，每单位时间每条边限制流量，奶牛单位时间内可以移动多步，求一定时间内能到达根的最多的奶牛个数，多组询问。

# 思路

提供一个新思路。~~其实是看不懂前面题解。~~

考虑贪心，对每个点记录一个数组，第 $i$ 项表示第 $i$ 个单位时间能到父亲的奶牛个数。

发现变化最多只有子树大小个，可以使用**差分数组**记录。

这里我使用的是 `map`，考虑如何合并。

普通的合并复杂度太高，不可接受，所以要用**启发式合并**。

从左到右遍历两个 `map`，判断有多少时间这个点是满流的。

方便起见，我们从流量容量中最小的边开始做起。

每次可以直接走到这条边且最小容量大于这条边的容量的点记录奶牛的个数和，算出 `map`，然后与那些在子树中的 `map` 合并，合并完后删除其他 `map`，仅保留这条边的 `map`。

最后就是算前缀数组，询问时二分暴力，这个不再说了。

时间复杂度 $\mathcal{O}(n\log^2 n\ + q\log n)$。

# code
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, k;
int fa[100005], c[100005], m[100005];
map<int, int> mp[100005];//每个点的差分map
vector<int>t[100005];//存树
int use[100005];//是否已经用过
int sum;
vector<int>bh;//编号
void dfs(int o){
    if(use[o]){
        bh.emplace_back(o);
        return;
    }
    sum += c[o];
    for(auto to : t[o]){
        dfs(to);
    }
    use[o] = 1;
}
pair<int, int> pre[100005];//mp[nwin[1]]的前缀（二分用）
int tot;
int nwin[100005];//i对应的map现在在哪儿（因为要启发式合并）
void merge(int i, int j, int mx){//要把mp[j]合并到mp[i],且最大值为mx
    int pr = 1;//之前一个起始点
    int v = mp[i][1] + mp[j][1];//现在的值
    auto it = mp[i].begin(), it_ = mp[j].begin();//两个指针
    int duo = 0;//=多
    while(1){
        int px = it->second;
        int py = it_->second;
        it++, it_++;
        int nwfr, data;//nowfirst&增量
        if((it->first) > (it_->first)){
            nwfr = it_->first;
            data = (it_->second);
            it--;
        }else if((it->first) == (it_->first)){
            nwfr = it_->first;
            data = (it->second) + (it_->second);
        }else{
            nwfr = it->first;
            data = (it->second);
            it_--;
        }
        //⬆哪个小先走哪个
        //⬇change
        if(v >= mx){
            duo += (nwfr - pr) * (v - mx);
            pr = nwfr;
            v += data;
        }else{
            if(duo / (nwfr - pr) >= (mx - v)){
                duo -= (mx - v) * (nwfr - pr);
                pr = nwfr;
                v += data;
            }else{
                int enman = pr + duo / (mx - v) - 1;
                int num = 0;
                for(auto &[a, b]:mp[i]){
                    if(a <= enman + 1)b = 0, num++;
                    else{
                        break;
                    }
                }
                while(num--){
                    mp[i].erase(mp[i].begin());
                }
                mp[i][1] += mx;
                mp[i][enman+1] -= mx;
                mp[i][enman+1] += v + duo % (mx - v);
                mp[i][enman+2] -= v + duo % (mx - v);
                mp[i][enman+2] += v;
                for(auto &[a, b]:mp[j]){
                    if(a > enman + 1){
                        mp[i][a] += b;
                    }
                }
                return;
            }
        }
    }
}
int get(int tim){//二分算答案
    if(tim > pre[tot].first)return pre[tot].second;
    int l = 0, r = tot, ans;
    while(l <= r){
        int mid = l+r>>1;
        if(tim <= pre[mid].first){
            r = mid - 1;
        }else{
            ans = mid;
            l = mid + 1;
        }
    }
    return pre[ans].second + (pre[ans + 1].second - pre[ans].second) / (pre[ans + 1].first - pre[ans].first) * (tim - pre[ans].first);
}
signed main(){ 
    cin >> n >> k;
    set<pair<int, int> >st;
    for(int i = 2; i <= n; i++){
        nwin[i] = i;
        scanf("%lld%lld%lld", &fa[i], &c[i], &m[i]);
        t[fa[i]].emplace_back(i);
        st.insert(make_pair(m[i], i));//按m从小到大排序
    }
    for(auto [aaa, i] : st){
        if(use[i])continue;
        sum = 0;
        bh.clear();
        dfs(i);
        if(!m[i]){
            mp[i][1] += 0;
            mp[i][1e10] += 0;
            continue;
        }
        mp[i][1] += m[i];
        mp[i][sum / m[i] + 1] -= m[i];
        mp[i][sum / m[i] + 1] += sum % m[i];
        mp[i][sum / m[i] + 2] -= sum % m[i];
        mp[i][1e10] += 0;
        for(auto to : bh){
            if(mp[nwin[i]].size() > mp[nwin[to]].size())merge(nwin[i], nwin[to], m[i]);
            else merge(nwin[to], nwin[i], m[i]), swap(nwin[i], nwin[to]);
            map<int, int> mpp;
            swap(mpp, mp[nwin[to]]);
        }
    }
    nwin[1] = nwin[t[1][0]];
    int op = 1;
    for(auto i : t[1]){//合并到root
        if(op){
            op = 0;
            continue;
        }
        if(mp[nwin[1]].size() > mp[nwin[i]].size())merge(nwin[1], nwin[i], 1e18);
        else merge(nwin[i], nwin[1], 1e18), swap(nwin[1], nwin[i]);
        map<int, int>mpp;
        swap(mpp, mp[nwin[i]]);
    }
    int pr = mp[nwin[1]][1];
    int prd = 1;
    for(auto [x, y] : mp[nwin[1]]){//预处理前缀
        if(x == 1)continue;
        pre[++tot] = make_pair(x - 1, (x - prd) * (pr));
        pre[tot].second += pre[tot - 1].second;
        pr += y;
        prd = x;
    }
    while(k--){
        int ti;
        scanf("%lld", &ti);
        printf("%lld\n", get(ti));
    }
    return 0;
}
```


---

