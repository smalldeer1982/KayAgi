# Sanae and Giant Robot

## 题目描述

> 果然是那个吗！因为其实用性而无法被实现的！只能出现于憧憬中的，二足步行巨大机器人！——东风谷早苗，《东方非想天则》

早苗制造了一台巨大的机器人——非想天则，但是这个机器人出了一些故障。更糟糕的是，早苗不知道如何将其停止运行，因而早苗只能在机器人运行的时候对其修复。

非想天则的状态可以用一个正整数数列 $n$ 来表示。非想天则现在处于状态 $a_1,a_2,\dots a_n$，而早苗希望将其变为 $b_1,b_2,\dots,b_n$。

作为一位优秀的女子高中生，早苗非常了解复制粘贴的艺术。她有 $m$ 个可供选择的区间，在每一次操作中，早苗可以把序列 $b$ 中的一个可选择的区间对应位置地复制粘贴到序列 $a$ 中，前提是要求序列 $a$ 的每个数字的总和不变。形式化地来讲，早苗可以选择一个区间 $[l,r]$，执行操作 $a_i \leftarrow b_i (l \leq i \leq r)$，当且仅当 $\sum \limits_{i=1}^n a_i$ 不变。

请你判断早苗能否通过若干次这样的操作，将非想天则的状态由序列 $a$ 转化为序列 $b$。

## 样例 #1

### 输入

```
2
5 2
1 5 4 2 3
3 2 5 4 1
1 3
2 5
5 2
1 5 4 2 3
3 2 4 5 1
1 2
2 4```

### 输出

```
YES
NO```

# 题解

## 作者：周子衡 (赞：22)

考虑设 $c_i=a_i-b_i$。原题的操作相当于：当某个 $[l_i,r_i]$ 满足 $\sum_{j=l_i}^{r_i}c_j=0$ 时，可以将 $c_{l_i\sim r_i}$ 全部清零；目标则变成让 $c_i$ 全部清零。

初看起来仍然有些无从下手。观察到条件 $\sum_{j=l_i}^{r_i}c_j=0$ 是一个连续子段和的形式，可以去试着构造前缀和 $s_i=\sum_{j=1}^ic_j$。此时操作变为：当某个 $s_{l_i-1}=s_{r_i}$ 时，可以将 $s_{l_i\sim r_i}$ 全部赋值为 $s_{r_i}$；目标仍是让 $s$ 全部清零。

可以注意到，当 $s_{l_i-1}=s_{r_i}\neq 0$ 时，执行这个操作是不优的，我们只应该在 $s_{l_i-1}=s_{r_i}=0$ 时进行操作。证明较为直观，读者可以稍微暂停一下，仔细想想这个过程。

接下来的事情就简单了：我们每次找一对 $s_{l_i-1}=s_{r_i}=0$，然后将 $s_{l_i\sim r_i}$ 全部清零，直到不能执行操作为止。如果最终 $s$ 全 $0$ 则输出 `YES`，否则输出 `NO`。

考虑怎样快速维护上面的过程。一种做法是：用一个 `set` / 线段树维护所有还不是 $0$ 的位置，每次区间清 $0$ 时提取区间里剩下的非 $0$ 位置，并考虑它们能否扩展新区间。每个区间只会被考虑 $2$ 次，这样即可做到 $O((n+m)\log n)$ 的时间复杂度。

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<set>

using namespace std;

typedef set<int>::iterator IT;
long long a[300000],b[300000],c[300000],s[300000];
vector<int> ed[300000];

int main()
{
	int TT=0;scanf("%d",&TT);
	while(TT--)
	{
		int n=0,m=0;scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++)scanf("%lld",&b[i]);
		for(int i=1;i<=n;i++)c[i]=a[i]-b[i];
		for(int i=1;i<=n;i++)s[i]=s[i-1]+c[i];
		
		queue<int> q;set<int> S;
		for(int i=0;i<=n;i++)if(s[i])S.insert(i);else q.push(i);
		
		for(int i=1,l=0,r=0;i<=m;i++)
		{
			scanf("%d%d",&l,&r);ed[l-1].push_back(r),ed[r].push_back(l-1);
		}
		
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=0;i<ed[u].size();i++)
			{
				if(s[ed[u][i]])continue;
				int l=min(ed[u][i],u),r=max(ed[u][i],u);
				IT it=S.lower_bound(l);
				while(it!=S.end()&&*(it)<=r)
				{
					int p=*it;s[p]=0;q.push(p);
					IT f=it;it++;S.erase(f);
				}
			}
		}
		puts(S.empty()?"YES":"NO");
		for(int i=0;i<=n;i++)ed[i].clear(); // 第一次这里写成 i = 1...n 然后 WA on test 4
	}
}
```

**后记**

挺有意思的题，感觉是整场里最有意思的题。后面的几个题要么有些钻牛角尖，要么太常规了。个人见解，欢迎交流。

---

## 作者：GaryH (赞：9)

## CF1687C 题解

记 $c_i=\sum\limits_{j = 1}^ia_j-b_j$，则操作区间 $[l,r]$ 可以执行，当且仅当 $c_r=c_{l-1}$，而操作后会把所有 $c_i( \forall i\in[l, r] )$ 覆盖成 $c_{l-1}$，那问题就是能否将 $c$ 数组全部变成 $0$。

考虑建一张下标从 $0$ 到 $n$ 的有向图，其中 $j$ 到 $i$ 有边，当且仅当存在一个给定的操作区间 $[l,r]$ 满足 $l=i<j \le r$，那问题就转化为，询问这张图中的每个点 $u$，是否都可以到达一个满足 $c_i=0$ 的点 $i$。

那么考虑从每个 $c_i=0$ 的点 $i$ 开始 `BFS`，则遍历到的点总数为 $n+1$ 等价于问题有解，那么直接暴力 `BFS` 的复杂度是 $O(nm)$ 的。因为每个点理论上只会被遍历一次，所以复杂度瓶颈在于大量地枚举不必要的出边。

考虑减少不必要的枚举。发现某条边的枚举是不必要的，当且仅当其指向的点已被遍历过。所以，如果我们跳过对这些边的枚举，那么复杂度就是对的。故我们用 `set` 维护当前所有未遍历到的点，而因为出边指向的点一定是一段区间，故每次从 `set` 中取出该区间中任意一个未被遍历过的点，并从 `set` 中删去该该点，即可实现高效的遍历。容易发现，这样的复杂度是 $O(n\log n)$ 的，就足以通过此题了。

代码比较好写，就不放了，想看的点[链接](https://codeforces.com/contest/1687/submission/159514790)。

---

## 作者：cwfxlh (赞：8)

# [CF1687C](https://www.luogu.com.cn/problem/CF1687C)  

看到这道题后，一个很明显的突破口就是从这个区间执行的限制入手。将 $[l,r]$ 的 $a_i$ 全部替换成 $b_i$ 后，要保持 $a$ 数组和不变，那么意思就是 $\sum_{i=l}^ra_i=\sum_{i=l}^rb_i$，将一边换过去就变成 $\sum_{i=l}^r(a_i-b_i)=0$。   

我们不妨令 $c_i=a_i-b_i$，$pre_i=\sum_{j=1}^ic_j$，那么最后的目标就是将 $pre$ 的 $[0,n]$ 全部推平成 $0$，对于一种区间选择 $[l,r]$，如果 $pre_{l-1}=pre_r$，则可以将其中间所有 $pre$ 全部推平成 $pre_{l-1}$。   

这时我们发现一个重要性质，因为操作是推平，而最后的目标是推平为 $0$，所以只有 $pre_{l-1}=pre_r=0$，我们才可以进行推平操作，否则一定不优。并且我们发现，推平为 $0$ 的这个操作不在乎操作顺序，所以问题就变成了每次随便找一个满足 $pre_{l-1}=pre_r=0$ 的区间，将其推平，问能否将 $[0,n]$ 推完。     

于是我们用 set 维护一下两端非零区间与一段非零区间，每次推平的时候查询更新就可以了，复杂度 $O(n\log n)$，本人实现写得很烂，跑了 $997ms$。    

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,a[500003],b[500003],pre[500003],l,r;
struct Seg{
	int st;
	int ed;
}P[500003];
int q[500003],totq,zt[500003],k1,k2,k3;
set<pair<int,int> >rem;
set<pair<int,int> >r2;
pair<int,int>bl1;
int stk[500003][2],tot;
vector<pair<int,int> >v;
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++)scanf("%lld",&b[i]);
		for(int i=2;i<=n+1;i++)pre[i]=pre[i-1]+a[i-1]-b[i-1];
		totq=0;
		rem.clear();
		r2.clear();
		for(int i=1;i<=m;i++){
			scanf("%lld%lld",&P[i].st,&P[i].ed);
			P[i].ed++;
			if(pre[P[i].st]==0&&pre[P[i].ed]==0){
				q[++totq]=i;
				zt[i]=2;
				continue;
			}
			if(pre[P[i].st]!=0&&pre[P[i].ed]!=0){
				rem.insert(make_pair(P[i].st,i));
				rem.insert(make_pair(P[i].ed,i));
				zt[i]=0;
				continue;
			}
			zt[i]=1;
			if(pre[P[i].st]!=0)r2.insert(make_pair(P[i].st,i));
			else r2.insert(make_pair(P[i].ed,i));
		}
		for(int i=1;i<=totq;i++){
			bl1.first=P[q[i]].st;
			bl1.second=0;
			tot=0;
			for(set<pair<int,int> >::iterator j=r2.lower_bound(bl1);j!=r2.end();j++){
				k1=(*j).first;
				k2=(*j).second;
				if(k1>P[q[i]].ed)break;
				q[++totq]=k2;
				zt[q[totq]]=2;
				stk[++tot][0]=k1;
				stk[tot][1]=k2;
			}
			for(int j=1;j<=tot;j++)r2.erase(make_pair(stk[j][0],stk[j][1]));
			bl1.first=P[q[i]].st;
			bl1.second=0;
			tot=0;
			for(set<pair<int,int> >::iterator j=rem.lower_bound(bl1);j!=rem.end();j++){
				k1=(*j).first;
				k2=(*j).second;
				if(k1>P[q[i]].ed)break;
				stk[++tot][0]=k1;
				stk[tot][1]=k2;
				if(zt[k2]!=0)continue;
				if(P[k2].st>=P[q[i]].st&&P[k2].ed<=P[q[i]].ed){
					zt[k2]=2;
					continue;
				}
				zt[k2]=1;
				if(P[k2].ed>P[q[i]].ed)r2.insert(make_pair(P[k2].ed,k2));
				else r2.insert(make_pair(P[k2].st,k2));
			}
			for(int j=1;j<=tot;j++)rem.erase(make_pair(stk[j][0],stk[j][1]));
		}
		v.clear();
		v.shrink_to_fit();
		for(int i=1;i<=n+1;i++){
			if(pre[i]==0)v.emplace_back(make_pair(i,i));
		}
		for(int i=1;i<=m;i++){
			if(zt[i]==2)v.emplace_back(make_pair(P[i].st,P[i].ed));
		}
		sort(v.begin(),v.end());
		if(v.size()==0){
			puts("NO");
			continue;
		}
		l=v[0].first;
		r=v[0].second;
		for(int i=1;i<v.size();i++){
			if(v[i].first<=r+1)r=max(r,v[i].second);
		}
		if(l==1&&r==n+1)puts("YES");
		else puts("NO");
	}
	return 0;
}
```


---

## 作者：绝顶我为峰 (赞：4)

套路题。

看到 $\sum a_i=\sum b_i$ 这样的条件，很自然地想到对两个序列做前缀和。

这样有解的判定是平凡的，我们不断操作可以操作的区间，最后如果 $\forall 0\leq i\leq n$，都有 $a'_i=b'_i$，则有解。

记前缀和后的数组为 $a',b'$，首先可以操作的条件转化为 $a_{r_i}-a_{l_i-1}=b_{r_i}-b_{l_i-1}$，然后我们将 $b[l_i,\cdots,r]$ 赋值给 $a[l_i,\cdots,r]$ 并重新计算 $a'$。这样还是不可做，但注意到我们目标是尽可能让更多的 $a'_i=b'_i$，这样我们才有可能有新的可以操作的区间。如果 $a'_{l_i-1}\neq b'_{r_i-1},a'_{r_i}\neq b'_{r_i}$ 那么我们操作这个区间之后区间内任意位置都不可能有 $a'_i=b'_i$，也就是说我们没有让任何一个点变为合法，所以这样的操作是没有意义的。因此只有在 $a'_{l_i-1}=b'_{l_i-1},a'_{r_i}=b'_{r_i}$ 的时候我们才会进行操作。

那么题意转化为对于每个区间 $[l_i,r_i]$，当 $a'_{l_i-1}=b'_{l_i-1}$ 且 $a'_{r_i}=b'_{r_i}$ 时，对于所有 $j\in[l_i-1,r_i]$，可以令 $a'_j=b'_j$，最后判断是否 $a'=b'$。

考虑怎样维护这个过程。首先对每个区间维护两个标记分别表示左右端点是否已经相等。在每个点维护自己的端点集合，类似 bfs，用一个队列维护可以操作的线段，每次取出队头，覆盖所有区间内的点，对所有覆盖的端点标记，如果当前区间的两个端点均已经被标记且这个区间未被操作就将区间加入队列，这样是 $O(nm)$ 的。

考虑优化，显然每个位置我们只应该更新一次，多余的更新是没有意义的。使用并查集维护从当前点向后第一个未被覆盖的点的位置即可，复杂度 $O((n+m)\log n)$。

注意此处并查集不能按秩合并。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
int t,n,m,cnt,bin[200005];
bool vis[200005][2];
long long a[200005],b[200005];
int pos[200005][2];
vector<int> v[200005];
queue<int> q;
inline int read()
{
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x;
}
inline int anc(int k)
{
    if(!bin[k])
        return k;
    return bin[k]=anc(bin[k]);
}
inline void solve(int x)
{
    for(auto i:v[x])
    {
        int id=i<=m? i:i-m;
        if(!vis[id][i>m])
        {
            vis[id][i>m]=1;
            if(vis[id][i<=m])
                q.emplace(id);
        }
    }
}
int main()
{
    t=read();
    while(t--)
    {
        cnt=0;
        n=read()+1,m=read();
        for(int i=2;i<=n;++i)
            a[i]=a[i-1]+read();
        for(int i=2;i<=n;++i)
            b[i]=b[i-1]+read();
        for(int i=1;i<=n+1;++i)
        {
            bin[i]=0;
            v[i].clear();
        }
        for(int i=1;i<=m;++i)
        {
            pos[i][0]=read(),pos[i][1]=read()+1;
            vis[i][0]=vis[i][1]=0;
            v[pos[i][0]].emplace_back(i);
            v[pos[i][1]].emplace_back(i+m);
        }
        while(!q.empty())
            q.pop();
        for(int i=1;i<=n;++i)
            if(a[i]==b[i])
            {
                solve(i);
                bin[i]=anc(i+1);
                ++cnt;
            }
        while(!q.empty())
        {
            int k=q.front();
            q.pop();
            for(int i=anc(pos[k][0]);i<=pos[k][1];i=anc(i+1))
            {
                solve(i);
                bin[i]=i+1;
                ++cnt;
            }
        }
        cout<<(cnt>=n? "YES":"NO")<<'\n';
    }
    return 0;
}
```

---

## 作者：I_am_Accepted (赞：3)

首先将 $a_i$ 减去 $b_i$，这样就转化为 $b$ 序列全零的问题了，也就是说：

* * *

给一些区间，当区间内和为 $0$ 的时候可以将区间所有数全部置为 $0$，求是否可以将整个序列全部变为 $0$。

* * *

但是这样还是不好搞，因为区间之间的操作顺序影响结果。

由于是区间和之类的问题，我们想到前缀和。

设 $a$ 的前缀和序列为 $c_0(=0),c_1,c_2,\dots,c_n$，则问题转化为：

* * *

给一些区间 $(l,r]$（左开右闭），当 $c_l=c_r$ 的时候可以将区间内所有 $c_i$ 全部置为 $c_l(=c_r)$，求是否可以将整个序列全部变为 $0$。

* * *

我们发现若 $c_l=c_r\ne 0$，这样操作的话是没有意义的，因为操作完后不会新增 $c$ 序列中的 $0$。

紧接着，发现这些区间设为 $0$ 的操作顺序是无关的。

所以我们存一个队列，表示当前有哪些区间的 $c_l=c_r=0$，我们依次操作，然后判断是否有新增的这样的区间，把她们加进队列。

具体地，对每一个位置开 vector 表示这个位置有哪些区间的端点。同时开序列上的并查集，可以 $O(\alpha(n))$ 跳过连续的 $0$ 区间。由于每一个位置变为 $0$ 后不会再变回非 $0$，所以时间复杂度是 $O(m+n\alpha(n))$。

最后判断一下 $c$ 是否全零即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define file(s) fin(s".in");fout(s".out")
#define cerr cerr<<'_'
#define debug cerr<<"Passed line #"<<__LINE__<<endl
template<typename T>T ov(T x){cerr<<"Value: "<<x<<endl;return x;}
#define ll long long
const ll mod=1000000007;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
inline void mad(ll &a,ll b){a=(a+b)%mod;while(a<0)a+=mod;}
inline void mmu(ll &a,ll b){a=a*b%mod;while(a<0)a+=mod;}
#define inv(a) pw(a,mod-2)
#define int long long
#define N 200010

int n,m,a[N],cnt[N],f[N],R[N];
pair<int,int> b[N];
queue<int> q; 
vector<int> id[N];
inline int gf(int x){return f[x]==x?x:f[x]=gf(f[x]);}
void work(){
	cin>>n>>m;
	For(i,1,n) cin>>a[i];
	int x,y,lim;
	For(i,1,n){
		cin>>x;
		a[i]-=x;
	}
	For(i,1,n) a[i]+=a[i-1];
	For(i,1,m) cin>>b[i].fir>>b[i].sec;
	For(i,1,m) b[i].fir--;
	For(i,1,m) cnt[i]=(a[b[i].fir]!=0)+(a[b[i].sec]!=0);
	For(i,0,n) id[i].clear();
	For(i,1,m) id[b[i].fir].pb(i);
	For(i,1,m) id[b[i].sec].pb(i);
	For(i,1,m) if(!cnt[i]) q.push(i);
	For(i,0,n)
		if(a[i]) f[i]=i;
		else f[i]=i+1;
	f[n+1]=n+1;
	while(!q.empty()){
		x=q.front();
		q.pop();
		y=gf(b[x].fir);
		lim=b[x].sec;
		while(y<=lim){
			for(int i:id[y]){
				cnt[i]--;
				if(!cnt[i]) q.push(i);
			}
			f[y]=y+1;
			y=gf(y+1);
		}
	}
	cout<<(gf(0)==n+1?"YES":"NO")<<endl;
}
signed main(){IOS;
	int T;cin>>T;
	while(T--)work();
return 0;}
```

---

## 作者：dayz_break404 (赞：2)

思考可以复制的条件区间和相等如何处理，想到记 $x_i=a_i-b_i$，并做 $x$ 的前缀和 $c$。显然问题转化为当可以修改的区间 $[l,r]$ 满足 $c_{l-1}=c_r$ 时，区间可以被全部覆盖成 $a_{l-1}$，问是否可以将序列全部赋值为 $0$。

当然也可以理解成将两个序列分成若干个极小块，使得每个块内两个序列的和相等，区间可以覆盖当且仅当区间左端点和一个极小块的左端点重合，右端点和一个极小块的右端点重合。

考虑如何动态维护这个过程，对于一个可以操作的区间，当两端为 $0$ 时才可以操作。可以将其抽象成一个有向图拓扑的过程，先将 $c_i$ 为 $0$ 的加入队列，遍历与其相关的区间，当区间被遍历两次便可以被触发，将这个范围之内的点加入队列。set 维护没有变成 $0$ 的 $c_i$ 即可，时间复杂度 $O(n\log n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*f;
}
bool mbs;
const int maxn=2e5+20;
#define ll long long
#define pai pair<ll,ll>
#define fir first
#define sec second
pai rec[maxn];
ll t,n,m,a[maxn],idx,b[maxn],c[maxn],cnt[maxn];
vector<ll> e[maxn];
queue<ll> q;
set<ll> s;
inline void solve(){
	n=read(),m=read(),s.clear();
	s.insert(0);
	e[0].clear();
	for(int i=1;i<=n;i++) a[i]=read(),s.insert(i),e[i].clear();
	for(int i=1;i<=n;i++) b[i]=read();
	for(int i=1;i<=n;i++) c[i]=c[i-1]+a[i]-b[i];
	for(int i=1;i<=m;i++) rec[i]={read(),read()},e[rec[i].fir-1].push_back(i),e[rec[i].sec].push_back(i),cnt[i]=2;
	for(int i=0;i<=n;i++) if(!c[i]) q.push(i),s.erase(i);
	while(!q.empty()){
		ll u=q.front();
		q.pop();
		for(int now:e[u]){
			cnt[now]--;
			if(!cnt[now]){
				auto it1=s.lower_bound(rec[now].fir),it2=s.upper_bound(rec[now].sec);
				for(auto it=it1;it!=it2;it++) q.push(*it);
				s.erase(it1,it2);
			}
		}
	}
	printf(s.size()?"NO\n":"YES\n");
}
bool mbt;
int main(){
//	cout<<(&mbs-&mbt)/1024.0/1024.0<<endl;
	t=read();
	while(t--) solve();
	return 0;
}
```

---

## 作者：lsj2009 (赞：1)

难度 $2500$。

> <https://codeforces.com/contest/1687/problem/C>。

聪明题。

看到 $\sum\limits_{i=l}^r a_i=\sum\limits_{i=l}^r b_i$，考虑作差和前缀和：

- 由 $\sum\limits_{i=l}^r a_i=\sum\limits_{i=l}^r b_i$ 得 $\sum\limits_{i=l}^r a_i-b_i=0$，记 $s_k=\sum\limits_{i=l}^k a_i-b_i$，则原条件等价于 $s_{l-1}=s_r$。

再把 $b_i\gets a_i$ 的操作放在 $s_i$ 上，得到 $\forall i\in[l,r] a_i-b_i=0$，即 $s_{l-1}=s_l=\cdots=s_r$。

再回顾最后题目要求的条件，等价于 $s_i$ 全零。

那么我们将问题转换为为如下：

> 给定序列 $\{s_n\}$ 和 $m$ 个区间 $[l_i,r_i]$。
>
> 每次可以选择一个区间满足 $s_l=s_r$，则令 $s_{l\sim r}\gets s_l$。
>
> 求是否能通过若干次操作使得 $\{s_n\}$ 全 $0$。

这里的 $l_i$ 为原来的 $l_i-1$。

首先选择区间操作时，如果 $s_l=s_r\neq 0$ 必然不优，因为你最终还是要把 $s_l\sim s_r$ 全赋为 $0$。

则我们考虑实现这么一个算法：每次拉出来一个满足 $s_l=s_r=0$ 的区间，然后令 $s_{l\sim r}\gets 0$，然后把操作后满足条件的区间给丢到一个序列里，由于值为 $0$ 的位置不需要再赋一遍 $0$，所以我们考虑开一个并查集维护一下，由于每个位置都只赋值一遍，且每个区间都只遍历两遍（左端点更新为 $0$ 时判断右端点是否为 $0$，右端点更新为 $0$ 时判断左端点是否为 $0$）、使用一遍，然后我们再开一个 ``set`` 动态删满足条件的区间，所以最终复杂度为 $\Theta(n\alpha(n)+m\log m)$。

---

## 作者：SmileMask (赞：0)

构造 $S_i=\sum_{k=1}^i a_k-b_k$，则原操作变为：

- 若 $S_{l_i-1}=S_{r_i}$，则可操作 $S_{l_i-1}=S_{l_i}=\dots=S_{r_i}$。

条件变为若干操作后是否能将 $S$ 全置为 0。

显然，让 $S_{l_i-1}=S_{r_i}\neq 0$ 的覆盖进行一定是不优的，考虑只操作 $S_{l_i-1}=S_r=0$ 的覆盖。

如何维护？我们不妨将能进行操作的覆盖先加入队列中，每次取队首，从左端点 $pos$ 开始跳，每次跳到下一个 $S$ 不为 0 的位置，直到 $pos>r$。

对于不为 0 的位置，此刻修改为 0，我们考虑将操作挂在两个端点上，如果此时两个端点都为 0，则加入队列中。

跳的过程可以用类似白雪皑皑的并查集维护，总复杂度 $O(m\alpha(n))$。

---

## 作者：封禁用户 (赞：0)

令两数组差的前缀和 $s_n=\sum^n_{i=1}(a_i-b_i)$，则操作等价于

- 若 $s_{l-r}=s_r$，将 $s$ 的 $[l-1,r]$ 段置为 $s_r$。

问题等价于能否使 $s$ 变为全 $0$。

这时问题已经很清晰了，我们倒序考虑操作，不难得到如下结论：

- 一次 $s_{l-1}=s_r≠0$ 的操作是毫无意义的，也就是操作总有 $s_{l-1}=s_r=0$。
- 那么，既然所有操作都要端点为 $0$ 时才能操作，且最终的目标也是全 $0$，只要一次操作可以进行，立即进行总是最优的。且已经执行该操作后，不会需要再次执行。

考虑如何模拟这个过程。我们很容易想到类似拓扑排序的模型，将每条线段置为 $0$ 时，对每个被置为 $0$ 的点，判断其出边对应的操作是否可以执行了即可。进行所有操作后，判断 $s$ 数组是否已经为全 $0$ 即可。

每个点只会被置零一次。可以使用 ```set``` 维护尚未被置零的点，或者使用并查集甚至链表等其他手段保证正确复杂度。时间复杂度 $O(n\log n+m$ 或 $O(n\alpha(n)+m)$ 或 $O(n+m)$。

```cpp
#define int i64
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++) { s[i] = s[i - 1] + a[i] - b[i]; }
    vector<pair<int, int>> op;
    queue<int> q;
    vector<vector<int>> adj(n + 1);
    set<int> nz;
    for (int i = 1; i <= n; i++) {
        if (s[i]) nz.insert(i);
    }
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l--;
        op.push_back({l, r});
        if (!s[l] && !s[r]) { q.push(i); }
        if (s[l]) adj[l].push_back(i);
        if (s[r]) adj[r].push_back(i);
    }
    while (q.size()) {
        int id = q.front();
        q.pop();
        auto [l, r] = op[id];
        for (auto it = nz.lower_bound(l); it != nz.end() && *it <= r;
             it = nz.erase(it)) {
            int x = *it;
            s[x] = 0;
            for (int u : adj[x]) {
                auto [l, r] = op[u];
                if (!s[l] && !s[r]) q.push(u);
            }
        }
    }
    if (ranges::count(s, 0) != (i64)s.size()) cout << "No\n";
    else cout << "Yes\n";
}
#undef int
 
```


---

