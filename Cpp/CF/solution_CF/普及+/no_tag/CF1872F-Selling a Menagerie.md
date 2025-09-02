# Selling a Menagerie

## 题目描述

You are the owner of a menagerie consisting of $ n $ animals numbered from $ 1 $ to $ n $ . However, maintaining the menagerie is quite expensive, so you have decided to sell it!

It is known that each animal is afraid of exactly one other animal. More precisely, animal $ i $ is afraid of animal $ a_i $ ( $ a_i \neq i $ ). Also, the cost of each animal is known, for animal $ i $ it is equal to $ c_i $ .

You will sell all your animals in some fixed order. Formally, you will need to choose some permutation $ ^\dagger $ $ p_1, p_2, \ldots, p_n $ , and sell animal $ p_1 $ first, then animal $ p_2 $ , and so on, selling animal $ p_n $ last.

When you sell animal $ i $ , there are two possible outcomes:

- If animal $ a_i $ was sold before animal $ i $ , you receive $ c_i $ money for selling animal $ i $ .
- If animal $ a_i $ was not sold before animal $ i $ , you receive $ 2 \cdot c_i $ money for selling animal $ i $ . (Surprisingly, animals that are currently afraid are more valuable).

Your task is to choose the order of selling the animals in order to maximize the total profit.

For example, if $ a = [3, 4, 4, 1, 3] $ , $ c = [3, 4, 5, 6, 7] $ , and the permutation you choose is $ [4, 2, 5, 1, 3] $ , then:

- The first animal to be sold is animal $ 4 $ . Animal $ a_4 = 1 $ was not sold before, so you receive $ 2 \cdot c_4 = 12 $ money for selling it.
- The second animal to be sold is animal $ 2 $ . Animal $ a_2 = 4 $ was sold before, so you receive $ c_2 = 4 $ money for selling it.
- The third animal to be sold is animal $ 5 $ . Animal $ a_5 = 3 $ was not sold before, so you receive $ 2 \cdot c_5 = 14 $ money for selling it.
- The fourth animal to be sold is animal $ 1 $ . Animal $ a_1 = 3 $ was not sold before, so you receive $ 2 \cdot c_1 = 6 $ money for selling it.
- The fifth animal to be sold is animal $ 3 $ . Animal $ a_3 = 4 $ was sold before, so you receive $ c_3 = 5 $ money for selling it.

Your total profit, with this choice of permutation, is $ 12 + 4 + 14 + 6 + 5 = 41 $ . Note that $ 41 $ is not the maximum possible profit in this example.

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ , but $ 4 $ is present in the array).

## 样例 #1

### 输入

```
8
3
2 3 2
6 6 1
8
2 1 4 3 6 5 8 7
1 2 1 2 2 1 2 1
5
2 1 1 1 1
9 8 1 1 1
2
2 1
1000000000 999999999
7
2 3 2 6 4 4 3
1 2 3 4 5 6 7
5
3 4 4 1 3
3 4 5 6 7
3
2 1 1
1 2 2
4
2 1 4 1
1 1 1 1```

### 输出

```
1 2 3
2 4 5 1 6 3 7 8
3 4 5 1 2
1 2
7 5 1 3 2 6 4
5 3 2 4 1
3 2 1
3 4 1 2```

# 题解

## 作者：BINYU (赞：8)

## 题意

有 $n$ 种动物，每种动物都会害怕另一种动物 $a_i$，你可以以任意顺序依次卖出这 $n$ 种动物，卖出第 $i$ 种动物的收益为 $c_i$，同时如果 $a_i$ 尚未卖出，你将获得额外 $c_i$ 的收益，求收益最大的卖出顺序。

## 思路

首先容易想到，对于不被任何动物害怕的动物，我们可以最先卖出他们，因为他们并不会对卖出其他动物的收益产生影响，而对于剩下来的动物，我们可以重复这个过程，直到不存在任何满足条件的动物。这和拓扑排序的过程是完全一样的。

想到建立一个图，从 $i$ 向 $a_i$ 连一条有向边，点最后可能会形成多个联通块，而且互不影响，而对于本题，因为一个大小为 $k$ 的联通块有且仅有 $k$ 条边，且一个点不可能连出 $2$ 条边，所以一个联通块最终会且只会产生一个环。

考虑为这个环上的动物定顺序，容易想到先删除一个点后，环将变成链，而除了链尾的点，其他点（包括最先删除的点）都会造成两倍的贡献，考虑贪心，将点权最小的点设为链尾的点，那么最先删除的点就是环上连像它的点，它所害怕的点。

对于全图，拓扑排序和找环以及在环上找最小值都是 $O(n)$ 级别的，所以，最终的时间复杂度为 $O(n)$，可过。

---

## 作者：hjqhs (赞：4)

怎么你谷上其他题解写的都那么复杂啊，，，   
记号：如果 $x$ 使 $y$ 害怕，称 $x$ 威慑 $y$。  
设第 $i$ 个动物可以威慑的所有其他动物价格之和 $sum_i$。一个很明显的贪心是先卖掉 $sum_i$ 小的动物。初始时把所有动物都扔进优先队列，每次弹出（即卖掉）队首并标记，然后把威慑他的动物的 $sum$ 值减掉这个动物的价值。然后就做完了。
```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define fv(i,p) for(int i=0;i<p.size();++i)
#define ptc putchar
#define il inline
#define reg register
// #define push_back pb
// #define mp make_pair
// #define eb emplace_back
// #define ret; return 0;
using namespace std;
const int N=100005;
const int MOD=998244353;
const int INF=0x3f3f3f3f;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
int Max(int a,int b){return a>b?a:b;}
int MAX(int a,int b,int c){return Max(a,Max(b,c));}
int Min(int a,int b){return a<b?a:b;}
int MIN(int a,int b,int c){return Min(a,Min(b,c));}
void Swap(int&a,int&b){int tmp=a;a=b;b=tmp;}
void cmin(int&x,int y){if(x>y)x=y;}
void cmax(int&x,int y){if(x<y)x=y;}
int read(){
  int x=0,f=1;
  char ch=getchar();
  while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
  while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
  return x*f;
}
int T,n,a[N],c[N],sum[N];
bool vis[N];
struct node{
  int key,pos;
  friend bool operator>(node x,node y){return x.key>y.key;}
};
priority_queue<node,vector<node>,greater<node>>pq;
void solve(){
  cin>>n;
  memset(vis,0,sizeof(vis));
  memset(sum,0,sizeof(sum));
  rep(i,1,n)cin>>a[i];
  rep(i,1,n)cin>>c[i],sum[a[i]]+=c[i];
  rep(i,1,n)pq.push((node){sum[i],i});
  while(!pq.empty()){
    int u=pq.top().pos;pq.pop();
    if(vis[u])continue;
    vis[u]=1;cout<<u<<' ';
    sum[a[u]]-=c[u];
    pq.push((node){sum[a[u]],a[u]});
  }
  cout<<'\n';
}
signed main(){
  // freopen(,,stdin);
  // freopen(,,stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin>>T;
  while(T--){
    solve();
  }
  return 0;
}
```

---

## 作者：Wf_yjqd (赞：3)

挺水的题，但场上耗了 $20$ 分钟。

CF Div.3 最近总爱在 F 题出拓扑排序。

------------

显然需要从 $i$ 到 $a_i$ 建边。

考虑无环部分只需按拓扑序卖，就都可以得到 $c_i\times2$。

对于剩下的每个环，贪心地牺牲环上的 $\min{c_i}$。

按 $c_i$ 从大到小卖即可，这样可以保证除了 $\min{c_i}$ 都能 $\times2$。

复杂度 $\operatorname{O}(n\log n)$（排序复杂度）。

------------

代码挺短的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+84;
int T,n,t,a[maxn],c[maxn],du[maxn],ans[maxn],id[maxn],cnt;
bitset<maxn> vis;
queue<int> q;
inline void topsort(){
    for(int i=1;i<=n;i++)
        if(!du[i])
            q.push(i);
    while(!q.empty()){
        t=q.front();
        q.pop();
        ans[++cnt]=t;
        vis[t]=1;
        du[a[t]]--;
        if(!du[a[t]])
            q.push(a[t]);
    }
    return ;
}
inline bool cmp(int x,int y){
    return c[x]<c[y];
}
inline void dfs(int x){
    if(vis[x])
        return ;
    vis[x]=1;
    ans[++cnt]=x;
    dfs(a[x]);
    return ;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            du[i]=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            id[i]=i;
            du[a[i]]++;
        }
        for(int i=1;i<=n;i++)
            scanf("%d",&c[i]);
        vis.reset();
        cnt=0;
        topsort();
        sort(id+1,id+n+1,cmp);
        for(int i=1;i<=n;i++)
            if(!vis[id[i]]){
                vis[id[i]]=1;
                dfs(a[id[i]]);
                ans[++cnt]=id[i];
            }
        for(int i=1;i<=cnt;i++)
            printf("%d ",ans[i]);
        putchar('\n');
    }
    return 0;
}
```


---

## 作者：Special_Tony (赞：2)

[洛谷传送门](/problem/CF1872F) & [CF 传送门](//codeforces.com/problemset/problem/1872/F)
# 思路
我们可以先找到入度为 $0$（即没动物害怕它）的动物，先卖掉这些动物就行了。然后进行拓扑排序，把它们害怕的动物的入度减一，直到大家形成了环后不能继续拓扑排序了就行。剩下每个连通块肯定都是一个环，因为每个点的出度都是 $1$。我们可以利用并查集判连通块。对于每个环，我们只要让代价最小（$c_i$ 最小）的动物最后删掉就行了。剩下的事情就交给 SPJ 了，我们的事情已经结束了。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int t, n, a[100005], b[100005], du[100005], f[100005], x, mini[100005];
queue <int> q;
int find (int x) { //并查集找爹函数，不用讲了吧
	return x == f[x] ? x : f[x] = find (f[x]); //爸爸的爸爸叫什么？爸爸的爸爸叫爸爸
}
int main () {
	cin >> t;
	while (t --) {
		cin >> n;
		for (int i = 1; i <= n; ++ i)
			mini[i] = du[i] = 0, f[i] = i; //多组数据要初始化
		for (int i = 1; i <= n; ++ i)
			cin >> a[i], ++ du[a[i]]; //du[i] 表示有几只动物怕 i
		for (int i = 1; i <= n; ++ i)
			cin >> b[i];
		for (int i = 1; i <= n; ++ i)
			if (! du[i]) //没人怕 i
				q.push (i); //先插进去
		while (! q.empty ()) { //拓扑排序
			x = q.front ();
			q.pop ();
			cout << x << ' ';
			if (! -- du[a[x]])
				q.push (a[x]);
		}
		for (int i = 1; i <= n; ++ i)
			if (du[i]) //还有动物怕它，说明它在一个环内
				f[find (i)] = find (a[i]); //并查集找连通块（环）
		for (int i = 1; i <= n; ++ i)
			if (du[i] && (! mini[find (i)] || b[mini[f[i]]] > b[i])) //找到每个连通块内代价最小的动物
				mini[f[i]] = i;
		for (int i = 1; i <= n; ++ i)
			if (du[i] && i == mini[f[i]]) { //是这个连通块内最小的动物
				for (int j = a[i]; j != i; j = a[j]) //开始遍历环
					cout << j << ' ';
				cout << i << ' '; //别忘了自己
			}
		cout << '\n'; //别忘了换行
	}
	return 0;
}
```

---

## 作者：Defy_HeavenS (赞：1)

## 题意
$T$ 组数据。

要卖出 $n$ 只动物，动物 $i$ 有它害怕的动物 $a_i$，且动物 $i$ 的价钱为 $c_i$。

若买出 $i$ 之前**未卖出** $a_i$，则获得的价格将乘以 $2$，也就是 $2 \times c_i$。

求出卖出顺序。

## 思路
我们可以将害怕与被害怕的关系连成一张有向有环图，比如这个数据：

```
5
2 3 4 5 3
1 2 3 4 5
```

可以画出图为（`-`前为编号，`-`后为价格）：

![](https://cdn.luogu.com.cn/upload/image_hosting/iz3ye5y2.png)

### 一条链的情况

因为没有动物害怕 $1$，所以先卖出 $1$ 不会影响其他动物的价钱，于是 $1$ 是第一个被卖出的。而 $1$ 被卖出后 $2$ 就会变为刚才 $1$ 的情况，于是 $2$ 就随着 $1$ 被第二个卖出的。

所以一条链只需要从链头到链尾以此没出即可。

### 一个环的情况

剩下的 $3,4,5$ 这个环可以先卖出一个动物，将其破为链。我们可以预处理出一个损失价值，第一个买损失最小的。损失价值也就是 $c_i$，因为如果 $a_i$ 被卖出，则 $i$ 的价值就会从 $2 \times c_i$ 变为 $c_i$。

可以发现其实也就是先买 $c_i$ 最小的，维护一个优先队列，每次取队首 $k$ 卖掉，将害怕 $k$ 的损失值更改后加入队列。

然后就可以做一条链的情况。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;  
typedef long long LL;
typedef pair<LL,LL> PLL;
int T,n,a[100005],c[100005],st[100005];
LL sum[100005];
priority_queue<PLL,vector<PLL>,greater<PLL> >q;
int main(){
	cin>>T;
	while(T--){
		memset(sum,0,sizeof sum);
		memset(st,0,sizeof st);
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>c[i];
			sum[a[i]]+=c[i];
		}
		for(int i=1;i<=n;i++){
			q.push(make_pair(sum[i],i));
		}
		while(!q.empty()){
			int t=q.top().second;
			q.pop();
			if(st[t]){
				continue;
			}
			st[t]=1;
			cout<<t<<" ";
			sum[a[t]]-=c[t];
			q.push(make_pair(sum[a[t]],a[t]));
		}
		cout<<"\n";
	}
	return 0;
}
```


---

## 作者：One_JuRuo (赞：1)

## 思路

对于每一个动物，我们都尽量让它比它害怕的动物先被卖。

考虑拓扑排序，每次输出出度为 $0$ 的点，然后再删点删边。

但是 $n$ 个点，$n$ 条边，必然存在环，所以只用拓扑排序是不行的。

自然想到 tarjan 缩点，对于环外，就拓扑排序好了，对于一个环，显然无法满足所有的点，所以我们就直接选择值最小的点放最后就好了。

原本我是 tarjan 再去拓扑的，但是调得我脑阔疼，又想到 tarjan 缩点的顺序本来就是反的拓扑序，所以可以边 tarjan 边记录答案，反着记就好。

另外提一句，tarjan 真的难调，一生之敌啊啊啊。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a,v[100005],cdfn,dfn[100005],low[100005],z[100005],top,in_z[100005],minn,p;
int e[200005],ne[200005],h[200005],idx,ans[100005],ccnt;
int tem[200005],tcnt;
inline void add(int a,int b){e[idx]=b,ne[idx]=h[a],h[a]=idx++;}
void dfs(int u)
{
	dfn[u]=low[u]=++cdfn,z[++top]=u,in_z[u]=1;
	for(int i=h[u];i;i=ne[i])
		if(!dfn[e[i]]) dfs(e[i]),low[u]=min(low[u],low[e[i]]);
		else if(in_z[e[i]]) low[u]=min(low[u],dfn[e[i]]);
	if(dfn[u]==low[u])
	{
		tcnt=1,p=1,minn=v[z[top]],tem[1]=z[top],in_z[z[top--]]=0;
		while(z[top+1]!=u)//栈中顺序就是一种遍历顺序
		{
			tem[++tcnt]=z[top];
			if(minn==-1) minn=v[z[top]],p=tcnt;
			else if(minn>v[z[top]]) minn=v[z[top]],p=tcnt;//记录最小值的位置
			in_z[z[top--]]=0;
		}
		for(int i=p;i<=tcnt;++i) ans[++ccnt]=tem[i];
		for(int i=1;i<p;++i) ans[++ccnt]=tem[i];//记录答案
	}
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		ccnt=0,cdfn=0,memset(dfn,0,sizeof(dfn)),memset(low,0,sizeof(low)),memset(h,0,sizeof(h)),idx=1,memset(in_z,0,sizeof(in_z)),top=0;
		scanf("%d",&n);
		for(int i=1;i<=n;++i) scanf("%d",&a),add(i,a);//建边
        for(int i=1;i<=n;++i) scanf("%d",&v[i]);
		for(int i=1;i<=n;++i) if(!dfn[i]) dfs(i);//tarjan
		for(int i=ccnt;i>=1;--i) printf("%d ",ans[i]);puts("");//注意：答案是反着记录的。
	}
}
```

---

## 作者：I_AK_IOI_6645 (赞：0)

# Selling a Menagerie
非常简单的贪心，只需要亿点点想法。

我们设计一个数组 $ s $ ,来存当前对这个动物感到害怕的动物的价值之和，然后把这个数组全部存到一个堆里，每次卖掉堆顶的动物，然后再更新一下重复入堆。
### 代码
~~~
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int vis[N];
int c[N];
int a[N];
int n;
int t;
long long s[N];
priority_queue<pair<long long,int> > q;//first存价值，second存动物下标
int main(){
	cin>>t;
	while(t--){
	    memset(a,0,sizeof a);//不要忘记初始化
	    memset(vis,0,sizeof vis);
	    memset(s,0,sizeof s);
		cin>>n;
		for(int i = 1;i<=n;i++){
			cin>>a[i];
		}
		for(int i = 1;i<=n;i++){
			cin>>c[i];
			s[a[i]] += c[i]; //计算s数组
		}
		for(int i = 1;i<=n;i++){
			q.push({-s[i],i});//因为是默认大根堆，所以要把相反数入堆
		}
		while(q.size()){
			int u = q.top().second;//堆顶出堆
			q.pop();
			if(vis[u])	continue;//确认没有反复卖掉
			vis[u] = 1;//标记
			cout<<u<<" ";//卖掉
			s[a[u]] -= c[u];//更新价格
			q.push({-s[a[u]],a[u]});//再次入堆
		}
		cout<<"\n";	
	}
}
~~~
有不懂的地方在下面问，看到回。

---

## 作者：Mioko_Sakurauchi (赞：0)

## [CF1872F](https://www.luogu.com.cn/problem/CF1872F)

## 题意简述：
你有 $n$ 个物品，你现在要给它们卖出去。已知对于物品 $i$，如果物品 $a_i$ 在出售物品 $i$ 的时候 $a_i$ 还没有被出售，你就会获得 $2\times c_i$ 的收益，否则你只能获得 $c_i$。

## 思路：
看到这道题立马就开始连边了，我们考虑对于每一个点，将它的点权赋值为 $2\times c_i$。图中会有 $k$ 个环，对于每一个环，选出点权最小的，删除它的出边，同时将它的点权赋值为 $c_i$ ，随后 sort  完跑一遍拓扑排序求 ans 即可。

## CODE

```cpp

#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
int c[maxn],dep[maxn],id[maxn],neid[maxn];
int ans[maxn],cnt;
int t,n;
bool vis[maxn];
queue<int> q;
void toposort()
{
	for(int i=1;i<=n;i++)
	{
		if(!dep[i])
		{
			q.push(i);
		}
	}
	while(!q.empty())
	{
		int op=q.front();
		q.pop();
		ans[++cnt]=op;
		dep[neid[op]]--;
		vis[op]=1;
		if(!dep[neid[op]])
		{
			q.push(neid[op]);
		}
	}
	return ;
}
bool cmp(int a,int b)
{
	return c[a]<c[b];
}
void fa(int x)
{
	if(vis[x]) return ;
	vis[x]=1;
	ans[++cnt]=x;
	fa(neid[x]);
	return ;
}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		cnt=0;
		for(int i=1;i<=n;i++)
		{
			vis[i]=0;
			neid[i]=0;
			c[i]=0;
			dep[i]=0;
			id[i]=i;
		}
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			neid[i]=x;
			dep[x]++;
		}
		for(int i=1;i<=n;i++)
		{
			cin>>c[i];
		}
		toposort();
		sort(id+1,id+1+n,cmp);
		for(int i=1;i<=n;i++)
		{
			if(!vis[id[i]])
			{
				vis[id[i]]=1;
				fa(neid[id[i]]);
				ans[++cnt]=id[i];
			}
		}
		for(int i=1;i<=cnt;i++)
		{
			cout<<ans[i]<<" ";
		}
		cout<<endl;
	}
}

---

## 作者：封禁用户 (赞：0)

[更好的阅读体验](https://www.doittomorrow.xyz/post/selling-a-menagerie-de-ti-jie/)
# 题面大意
动物园里有 $n$ 个动物，第 $i$ 个动物害怕第 $a_i$ 个动物，第 $i$ 个动物价值 $c_i$ 元。现在我要将这些动物全部卖掉。显然，卖掉的动物编号可以构成一个排列 $p$。

考虑卖掉这些动物时：
1. 若 $a_i$ 在 $i$ 还没有卖掉之前就被卖掉了，现在卖掉 $i$，可以获得 $c_i$ 元；
2. 若 $a_i$ 在 $i$ 还没有卖掉之前没被卖掉，现在卖掉 $i$，可以获得 $2·c_i$ 元；

构造并输出赚钱最多的动物卖出顺序。
# 思路
显而易见，题目可以转化为图论进行解决。

将第 $i$ 个点向 $a_i$ 连一条无向边，构成一个 $n$ 个点 $n$ 条边的基环树森林。

如果并没有其他的动物害怕第 $i$ 只动物，那么将第 $i$ 只动物卖出后并不会因为缺少了自己害怕的动物而减少价值。反映在图中即是将没有入度的点依次卖出，就是跑一次拓扑序。

因为这个图是一个基环树森林，所以在将所有的入度为 $0$ 的点全部删除之后剩下的节点必然满足对于任意的 $x$ 与 $y$ 有且仅有一条边将他们链接。

我们可以贪心的考虑删除掉环中的那一个点。

假设节点 $i$ 害怕的动物为 $a_i$，其价格为 $c_i$，这个环内的节点为 $s$，那么肯定有一个动物会因为自己害怕的动物已经卖出而变得便宜，不放假设变便宜的动物为 $x$。

这个环的价值就为 $\sum_{i\in s}( 2\times c_i)-c_x$。因为 $\sum_{i\in s}( 2\times c_i)$ 是一个定值，所以要使价值最大化就应该使 $c_x$ 尽可能的小。如果提前卖掉的动物为为 $m$ 那么 $x=a_m$，所以提前删除的点 $m$ 应该使 $s_{a_m}$ 最小。

在每一次将环内的一个点卖出后，剩下的节点就可以通过拓扑序的方式依次删除。

注意，因为这是一个基环树森林，所以可能存在多个环。

# AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,du[N],s[N];
vector<int> v[N];
queue<int> qq;
bool vis[N];
struct node{
	int x,v;
	friend bool operator < (const node a,const node b){
		return a.v>b.v;
	}
};
priority_queue<node>q;
void solve(){
	cin>>n;
	int cnt=0;
	for(int i=1;i<=n;i++){
		v[i].clear();
		du[i]=0;
		vis[i]=0;
		s[i]=0;
	}
	while(!q.empty()){
		q.pop();
	}
	for(int i=1,x;i<=n;i++){
		cin>>x;
		du[x]++;
		v[i].push_back(x);
	}
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	for(int i=1;i<=n;i++){
		if(du[i]==0){
			qq.push(i);
			cnt++;
			vis[i]=1;
			cout<<i<<" ";
		}
	}
	while(!qq.empty()){
		int x=qq.front();
		qq.pop();
		for(int i:v[x]){
			du[i]--;
			if(du[i]==0){
				cout<<i<<" ";
				qq.push(i);
				vis[i]=1;
				cnt++;
			}
		}
	}
	if(cnt==n){
		return;
	}
	for(int i=1;i<=n;i++){
		if(vis[i]){
			continue;
		}
		int p=0;
		while(vis[v[i][p]]) p++;
		
		q.push({v[i][p],s[i]});
	}
	while(cnt<n){
		while(vis[q.top().x]) q.pop();
		qq.push(q.top().x);
		cnt++;
		vis[q.top().x]=1;
		cout<<q.top().x<<" ";
		while(!qq.empty()){
			int x=qq.front();
			qq.pop();
			for(int i:v[x]){
				du[i]--;
				if(du[i]==0&&!vis[i]){
					cout<<i<<" ";
					qq.push(i);
					cnt++;
					vis[i]=1;
				}
			}
		}
	}cout<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
要卖动物，每个动物都有要害怕的动物 $a_i$，如果 $i$ 害怕的那个还没被卖，这只动物就能卖 $2\times
c_i$ 元。否则只能卖 $c_i$ 元。

让你构造一个卖的最贵的顺序。
## 大体思路
既然又害怕的动物在能卖更多的钱，那么没有动物害怕的动物先卖掉不会更差，其他的我们可以维护一个优先队列，处理我们如果先卖掉这个动物会损失多少，把损失少的先卖掉。

卖掉一个之后，在队列里的害怕他的不用变，我们只需要再加进去一个 $sum_{a_t}-c_{a_t}$ 由于小根堆性质，这个正确的、价钱小的一定会比错误的那个先出队，我们记录一个 $vis$ 记录一下是否出队过即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[100005],c[100005],sum[100005];
priority_queue<pair<long long,long long>,vector<pair<long long,long long>>,greater<pair<long long,long long>>> q;
bool vis[100005];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){//初始化 
			sum[i]=0;
			vis[i]=0;
		}
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>c[i];
			sum[a[i]]+=c[i];//把害怕的动物的那个加成加进去 
		}
		for(int i=1;i<=n;i++){
			q.push({sum[i],i});//先把所有的都入队 
		}
		while(!q.empty()){
			int x=q.top().second;
			q.pop();
			if(vis[x]){//已经卖掉了 
				continue ;
			}
			vis[x]=1;//标记已经出过队了 
			cout<<x<<" ";//此时是最优的，直接输出 
			sum[a[x]]-=c[x];
			q.push({sum[a[x]],a[x]});//更改后进入小根堆 
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：zhu_wen (赞：0)

## F. Selling a Menagerie

先进行拓扑排序，将没有入度的点全部卖掉。

我们怎么处理环呢？最后经过拓扑排序后，最多只会剩下一个环或者剩下一些零散的环。

对于一个环，维护一个最小值，将环上的全部以 $2$ 倍价值卖出，最后再卖出最小值的那个点，即可。

### 代码

```cpp
int _, n;
int ind[N];
int a[N], c[N];
bool vis[N];
int minn = 1e9, id, j;
vector< int > ans;
void tp()
{
    queue< int > q;
    fup(i, 1, n)
    {
        if(!ind[i])
        {
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int u = q.front();
        ans.eb(u);
        vis[u] = 1;
        q.pop();
        if(!(--ind[a[u]]))
        {
            q.push(a[u]);
        }
    }
}
void dfs(int u)
{
    if(vis[u]) return ;
    vis[u] = 1;
    j = a[u];
    if(minn > c[j]) minn = c[j], id = j;
    dfs(j);
}
void solve()
{
    ans.clear();
    fin >> n;
    fup(i, 1, n)    vis[i] = 0, ind[i] = 0;
    fup(i, 1, n)    fin >> a[i], ind[a[i]]++;
    fup(i, 1, n)    fin >> c[i];
    tp();
    fup(i, 1, n)
    {
        if(!vis[i])
        {
            minn = c[i];
            id = i;
            dfs(i);
            int x = a[id];
            do
            {
                ans.eb(x);
                x = a[x];
            } while(x != a[id]);
        }
    }
    for (auto i : ans)
    {
        fout << i << ' ';
    }
    fout << '\n';
}
```

---

## 作者：run_away (赞：0)

## 题意

有 $n$ 种动物，第 $i$ 只动物有且只有一个害怕的动物 $a_i$ 和价值 $c_i$。现在把所有的动物都卖出去，若 $a_i$ 在 $i$ 前面卖出去，将获得 $c_i$ 的收益；否则将多获得 $c_i$ 的收益。构造一种使收益最大的卖出顺序。

## 思路

这题很明显是图，显然对于每一个动物 $i$，先卖 $a_i$ 比先卖 $i$ 更优。

可以从 $i$ 向 $a_i$ 连边，然后跑一遍拓扑，一边遍历一边输出当前节点。

但是，因为每个点都有一条出边，图中肯定会有一个环，拓扑后还剩下环内的节点没有考虑。

对于环内的点，先删去任何一个点都会影响后续的点，所以找到价值最小的点，从它开始删。

拓扑 $O(n)$，遍历环 $O(n)$，总时间复杂度 $O(n)$。

## Code(无坑)

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define read(x) scanf("%lld",&x)
const ll maxn=100005;
ll t,n,a[maxn],c[maxn],du[maxn],pre[maxn],mn[maxn];
vector<ll>h;
inline ll find(ll x){return x==pre[x]?x:pre[x]=find(pre[x]);}
inline void solve(){
	read(n);
	for(ll i=1;i<=n;++i)pre[i]=i,du[i]=mn[i]=0;
	for(ll i=1;i<=n;++i)read(a[i]),++du[a[i]];
	for(ll i=1;i<=n;++i)read(c[i]);
	queue<ll>p;
	for(ll i=1;i<=n;++i)if(!du[i])p.push(i);
	while(!p.empty()){
		ll u=p.front();p.pop();
		printf("%lld ",u);
		if(!--du[a[u]])p.push(a[u]);
	}
	for(ll i=1;i<=n;++i){
		if(du[i]){
			pre[find(i)]=find(a[i]);
		}
	}
	for(ll i=1;i<=n;++i){
		if(du[i]&&(mn[find(i)]==0||c[mn[pre[i]]]>c[i])){
			mn[pre[i]]=i;
		}
	}
	for(ll i=1;i<=n;++i){
		if(du[i]&&mn[pre[i]]==i){
			for(ll j=a[i];j!=i;j=a[j]){
				printf("%lld ",j);
			}
			printf("%lld ",i);
		}
	}
	puts("");
}
signed main(){
	read(t);
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

## 思路

考虑连边，然后可以很快的想到能不能让他们全部的价值变成最大，发现我们可以优先把形状类似一条链的关系的动物卖出去，收益达到最大。

然后考虑最后的图形是什么，因为一个动物只有一个怕的动物，所以最后如果剩下了 $n$ 个动物就只会有 $n$ 条边，因为把链去掉了，所以就是一个环了，然后可以找环上价值最低的动物卖掉最后价值变成最大。

现在再来看思考的步骤，发现就是对一个基环树森林找环上的最小值就好了。

## 代码

```cpp
#include <bits/stdc++.h>

#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define per(i, l, r) for (int i = (r); i >= (l); i--)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
using namespace std;
const int maxn = 1000000;
int du[maxn], vis[maxn], c[maxn], f[maxn], a[maxn], id[maxn];
vector<int> v[maxn], e[maxn];
int F(int x) {
	return x == f[x] ? x : f[x] = F(f[x]);
}
void solve() {
	int n;
	cin >> n;
	rep(i, 1, n) {
		du[i] = 0;
		vis[i] = 0;
		id[i] = 0;
		f[i] = i;
		a[i] = 0;
		c[i] = 0;
	}
	rep(i, 1, n) {
		cin >> a[i];
		du[a[i]]++;
	}
	rep(i, 1, n) {
		cin >> c[i];
	}
	queue<int> q;
	rep(i, 1, n) {
		if (du[i] == 0) {
			q.push(i);
		}
	}
	while (q.size()) {
		int t =  q.front();
		q.pop();
		vis[t] = 1;
		cout << t << " ";
		if (--du[a[t]] == 0) {
			q.push(a[t]);
		}
	}
	rep(i, 1, n) {
		if (vis[i] == 0) {
			f[F(i)] = F(a[i]);
		}
	}
	rep(i, 1, n) {
		if (vis[i] == 0 && (!id[F(i)] || c[id[F(i)]] > c[i])) {
			id[F(i)] = i;
		}
	}
	rep(i, 1, n) {
		if (vis[i] == 0 && i == id[F(i)]) {
			for (int now = a[i]; now != i; now = a[now]) {
				cout << now << " ";
			}
			cout << i << " ";
		}
	}
	cout << "\n";
}
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);

	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：wdgm4 (赞：0)

# 前言

为了验证我还没有 AFO，来水题解。QWQ

# 正文

由于我是废物，我只会 tarjan + 拓扑排序。

显然，单独来说第 $i$ 只动物在 $a_i$ 被卖掉之前卖掉最优，那我们可以将 $i$ 和 $a_i$ 之间连上一条单向边，如果没有环出现的话，可以直接用拓扑排序将入度为零的直接输出。再来考虑环的情况，我只想到了 tarjan 缩点，对于单独一个环来说，它肯定是像下图那样：

![](https://cdn.luogu.com.cn/upload/image_hosting/ozqumomi.png)

用黑色笔圈出来的是那个环，蓝色点是我们假定的那个 $c_i$ 最小的点 `from`，我们可以发现，在这个环中的答案输出顺序就像红色线的顺序，而根据黄色的字（环中节点在 tarjan 栈里的遍历顺序）可以找到大致的输出顺序：

```cpp
for(int i=from-1;i>=1;i--) ans[sum].push_back(last[i]);
for(int i=num;i>=from;i--) ans[sum].push_back(last[i]);
```

这样就可以进行缩点，然后在拓扑就可以了。

# code

```cpp
#include<bits/stdc++.h>
#define XD 114514
#define MAXN 200010
using namespace std;
int t,n,a[MAXN],c[MAXN];
struct QWQ{
	int to,next;
} e[MAXN],e2[MAXN];
int head1[MAXN],cnt1;
void edd1(int u,int v){
	cnt1++;
	e[cnt1].to=v;
	e[cnt1].next=head1[u];
	head1[u]=cnt1;
}
int head2[MAXN],cnt2;
void edd2(int u,int v){
	cnt2++;
	e2[cnt2].to=v;
	e2[cnt2].next=head2[u];
	head2[u]=cnt2;
}
int dfn[MAXN],low[MAXN],deep,st[MAXN],stlen;
bool vis[MAXN];
int color[MAXN],sum,last[MAXN];
vector<int> ans[MAXN];
void tarjan(int x){//缩点
	deep++;dfn[x]=deep;low[x]=deep;
	stlen++;st[stlen]=x;vis[x]=true;
	for(int i=head1[x];i;i=e[i].next){
		if(!dfn[e[i].to]){
			tarjan(e[i].to);
			low[x]=min(low[x],low[e[i].to]);
		}else if(vis[e[i].to]) low[x]=min(low[x],low[e[i].to]);
	}
	if(low[x]==dfn[x]){
		sum++;
		color[x]=sum;
		vis[x]=false;
		int minn=c[x],from=1,num=1;
		last[num]=x;
		while(st[stlen]!=x){
			num++;
			color[st[stlen]]=sum;
			vis[st[stlen]]=false;
			last[num]=st[stlen];
			if(minn>c[st[stlen]]) from=num,minn=c[st[stlen]];
			stlen--;
		}
		stlen--;
		//下面这两行画图解释。
		for(int i=from-1;i>=1;i--) ans[sum].push_back(last[i]);
		for(int i=num;i>=from;i--) ans[sum].push_back(last[i]);
	}
}
int in[MAXN];
void bfs(){//拓扑排序
	for(int i=1;i<=n;i++){//建边
		if(color[i]!=color[a[i]]){
			edd2(color[i],color[a[i]]);
			in[color[a[i]]]++;
		}
	}
	queue<int> q;
	for(int i=1;i<=sum;i++) if(!in[i]) q.push(i);
	while(!q.empty()){
		int nem=q.front();q.pop();
		for(int i=0;i<ans[nem].size();i++) cout<<ans[nem][i]<<" ";
		for(int i=head2[nem];i;i=e2[i].next){
			in[e2[i].to]--;
			if(!in[e2[i].to]){
				q.push(e2[i].to);
			}
		}
	}
	cout<<"\n";
}
void inlt(){//多测清空
	for(int i=1;i<=sum;i++) ans[i].clear();
	for(int i=1;i<=n;i++) head1[i]=head2[i]=in[i]=dfn[i]=low[i]=vis[i]=0;
	cnt1=cnt2=0;
	sum=deep=0;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		inlt();
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];edd1(i,a[i]);
		} 
		for(int i=1;i<=n;i++) cin>>c[i];
		for(int i=1;i<=n;i++){
			if(!dfn[i]) tarjan(i);
		} 
		bfs();
	}
	return 0;
}
```


---

## 作者：liuzhongrui (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1872F)

## 思路
我们可以观察一下，如果在某个时刻存在一种动物 $i$，使得没有其他动物害怕它（即不存在索引 $a_j = i$），那么最优的策略是~~残忍地~~卖掉这种动物。

让我们迭代地出售这样的动物，只要它们存在。在出售动物 $i$ 后，我们还必须检查动物 $a_i$ 是否也成为了无人害怕的动物，如果是的话，将其添加到待售列表。

当我们出售所有这样的动物时，我们需要注意，当这种动物被卖完时，即这种动物不存在了，此时 $a_i$ 将形成一个排列，因为每种动物必定会被至少一种其他动物害怕。

排列由形如 $i \to a_i \to a_{a_i} \to \ldots \to i$ 的循环组成。

显然，对于每个循环，我们必须独立解决问题，然后以任意顺序组合答案。请注意，如果按循环的顺序出售动物，我们将只为最后出售的动物获得单一支付。

与此同时，在任何情况下都不可能为所有动物获得双重支付，循环中最后出售的动物将始终以单一支付出售。

因此，最优的策略是按循环的顺序出售所有动物，以确保成本最低的动物最后出售。

## Code

~~丑陋的~~代码奉上。

```cpp
#include<bits/stdc++.h>
using namespace std;  
#define PII pair<long long ,long long>
const int N=1e5+10;
int n;
int a[N],c[N],st[N];
long long sum[N];
priority_queue<PII,vector<PII> ,greater<PII > > q;
int main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--){
		memset(sum,0,sizeof sum);
		memset(st,0,sizeof st);
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>c[i];
			sum[a[i]]+=c[i];
		}
		for(int i=1;i<=n;i++){
			q.push(make_pair(sum[i],i));
		}
		while(!q.empty()){
			int t=q.top().second;
			q.pop();
			if(st[t]){
				continue;
			}
			st[t]=1;
			cout<<t<<" ";
			sum[a[t]]-=c[t];
			q.push(make_pair(sum[a[t]],a[t]));
		}
		cout<<endl;
	}
	return 0;
}

```


---

## 作者：Lily_White (赞：0)

## 思路
建图，从 $i$ 向 $a_i$ 连一条边。这种连边的方法让人想到树，结合 $n$ 个点 $n$ 条边可以联想到基环树（虽然这个图未必连通，但每一个连通分量仍然符合这个条件）。因此想到先找环，再对每个结点上挂在外面的树分别解决。这也是此类基环树问题的一个通用解决方法。

对于挂在外面的部分，只需要按照层次从下往上卖出即可。这样能保证所有结点都在自己的父亲结点之前被卖出。这一个部分可以对环上的每一个点进行一次 BFS 来获得正确的顺序。

对于环上的部分。绕着环转一圈的过程中，有且只有一个结点会出现“在自己的父亲之后被卖出”的情况。为了让答案最大，只需要让这个结点是权值最小的即可。

## 代码
```cpp
#define repn(i, n) for (int i = 1; i <= (int)n; i++)
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define eprintf(...) { fprintf(stderr, __VA_ARGS__); fflush(stderr); }
const int N = 100010;
vector<int> g[N];
int a[N], c[N], n;
int dfn[N], fa[N], cur;
vector<int> cyc;
int incyc[N];
int indeg[N];
vector<int> comp;
bool vis[N];
void cleanup() {
    rep(i, n + 1) {
        g[i].clear();
        fa[i] = a[i] = c[i] = 0;
        dfn[i] = 0;
        incyc[i] = 0;
        vis[i] = 0;
        indeg[i] = 0;
    }
    cyc.clear();
}
void dfs(int u) {
	dfn[u] = ++cur;
	comp.push_back(u);
	for (auto v: g[u]) {
		if (v == fa[u]) continue;
		if (dfn[v]) {
			if (dfn[v] < dfn[u]) continue;
			cyc.push_back(v);
			for (; v != u; v = fa[v]) cyc.push_back(fa[v]);
		} else {
			fa[v] = u;
			dfs(v);
		}
	}
}
void solve(int x) {

    eprintf("comp:");
    for (auto u: comp) {
        eprintf("%d ", u);
        incyc[u] = false;
    }
    eprintf("\n cyc:");
    for (auto u: cyc) {
        eprintf("%d ", u);
        incyc[u] = true;
    }
    eprintf("\n");
    for (auto u: comp) {
        vector<int> answer;
        // 从 u 开始 BFS，我们就能正确地定出父子顺序，保证子在父前
        if (incyc[u]) {
            queue<int> q;
            q.push(u);
            while (!q.empty()) {
                int t = q.front();
                q.pop();
                for (auto v: g[t]) {
                    if (!incyc[v] && !vis[v]) {
                        vis[v] = true;
                        q.push(v);
                        answer.push_back(v);
                    }
                }
            }
            reverse(answer.begin(), answer.end());
            for (auto x: answer) {
                cout << x << ' ';
            }
        }
    }
 //   cout << " | ";
    if (a[cyc[1]] == cyc[0]) {
        reverse(cyc.begin(), cyc.end());
    }
    int minv = INF, minp = 0;
    rep(i, cyc.size()) {
        if (c[cyc[i]] < minv) {
            minv = c[cyc[i]];
            minp = i;
        }
    }
    int cur = minp;
    rep(i, cyc.size()) {
        cur++; cur %= cyc.size();
        cout << cyc[cur] << ' ';
    }
}
void Main() {
    eprintf("===\n");
    rd(n);
    cleanup();
    repn(i, n) {
        rd(a[i]);
        g[i].push_back(a[i]);
        indeg[a[i]]++;
        g[a[i]].push_back(i);
    }
    repn(i, n) rd(c[i]);
    repn(i, n) {
        if (!dfn[i]) {
    //        cout << "||";
            comp.clear();
            cyc.clear();
            cur = 0;
            dfs(i);
            solve(i);
        }
    }
    cout << endl;
}
```

---

## 作者：Daniel_yao (赞：0)

## Problem
动物园里有 $n$ 个动物，第 $i$ 个动物害怕第 $a_i$ 个动物，第 $i$ 个动物价值 $c_i$ 元。现在我要将这些动物全部卖掉。显然，卖掉的动物编号可以构成一个排列 $p$。

考虑卖掉这些动物时：
1. 若 $a_i$ 在 $i$ 还没有卖掉之前就被卖掉了，现在卖掉 $i$，可以获得 $c_i$ 元；
2. 若 $a_i$ 在 $i$ 还没有卖掉之前没被卖掉，现在卖掉 $i$，可以获得 $2·c_i$ 元；

求最多能赚多少钱。
## Solve
首先，对于动物 $i$ 来说，肯定希望它害怕动物 $a_i$ 没有被卖掉。这样可以卖一个好价钱。

反过来想：如果一个动物没有任何其他的动物怕它，那么现在卖掉这个动物之后所得到的贡献肯定不劣。因为它的存在不会影响到其他动物卖出所得的贡献。

如果把“害怕”看成一种连边关系，那么问题就很好解决了。

连边之后，会出现没有构成环的点，和构成环的点。没有构成环的点的卖出顺序随意，上文已经解释过了（没有构成环的点的存在不会影响到其他动物卖出所得的贡献）。不过要注意的是，每一条链上的点或导出子树上的点要按顺序选，不过其都会被选中。

而构成环的点的卖出顺序至关重要，换句话说，起点和终点的所在位置非常关键。起点肯定是要选择 $c_i$ 最小的点，让损失尽可能的小。然后按顺序选择，卖出即可。

由于每一个点只会被遍历一次，时间复杂度 $O(Tn)$。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long
#define H 19260817
#define rint register int
#define For(i,l,r) for(rint i=l;i<=r;++i)
#define FOR(i,r,l) for(rint i=r;i>=l;--i)
#define MOD 1000003
#define mod 1000000007
#define inf 1e10

using namespace std;

namespace Read {
  template <typename T>
  inline void read(T &x) {
    x=0;T f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x*=f;
  }
  template <typename T, typename... Args>
  inline void read(T &t, Args&... args) {
    read(t), read(args...);
  }
}

using namespace Read;

void print(int x){
  if(x<0){putchar('-');x=-x;}
  if(x>9){print(x/10);putchar(x%10+'0');}
  else putchar(x+'0');
  return;
}

const int N = 1e5 + 10; 

int T, n, a[N], d[N], c[N], ans, Ans[N], len;

bool vis[N];

void solve() {
  memset(vis, 0, sizeof vis); 
  ans = len = 0;
  read(n);
  For(i,1,n) read(a[i]), d[a[i]]++;
  For(i,1,n) read(c[i]);
  bool f = 1;
  while(f) {
    f = 0;
    For(i,1,n) {
      if(!d[i] && !vis[i]) Ans[++len] = i, d[a[i]]--, vis[i] = 1, f = 1;
    }
  }
  For(i,1,n) {
    if(d[i]) {
      int x = i, mn = inf, en, st;
      while(!vis[x]) {
        vis[x] = 1;
        if(mn > c[x]) {
          mn = c[x];
          st = a[x];
          en = x;
        }
        d[a[x]]--;
        x = a[x];
      }
      while(st != en) {
        Ans[++len] = st;
        st = a[st];
      }
      Ans[++len] = en;
    }
  }
  For(i,1,len) cout << Ans[i] << ' ';
  cout << '\n';
}

signed main() {
  read(T);
  For(i,1,T) {
    solve();
  }
  return 0;
}
```

---

## 作者：滑不拉稽 (赞：0)

建图，对每个 $a_i$ 连边 $i\rightarrow a_i$，那么当走过一条边 $u\rightarrow v $  时，若 $v$ 此前未被遍历过，那么与 $v$ 相连的边均未被遍历，此时的贡献是 $2\times c[u]$；反之若 $v$ 此前已被遍历，那么贡献为 $c[u]$。

若是这样，那么依照拓扑排序的顺序是最优的，但这张图有环。

利用 tarjan 算法将图缩点成 DAG，则每个点的权值有两种情况：

1. 对于一个环，总权值为其中权值最小的点的权值 $+$ 其余点的权值 $\times 2$。
2. 否则，单点权值与原来相同。

到此，用大根堆跑拓扑排序，依次取出元素：遇到第一种情况要先将最小权值点连出的边对应的顶点存入答案，再将环上的点依次存入答案；否则直接存入答案。

场上没注意到一个环中的最小权值点会有多个，喜提 3WA。

```c++
#include <bits/stdc++.h>
using namespace std;
#define fre(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout)
#define int long long
#define double long double
#define inf 0x3fffffffffffffff
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return f==1?x:-x;
}
inline void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int modp = 998244353;


void solve()
{
	int n=read();
	vector<int> a(n+1),h(n+1);
	for(int i=1;i<=n;++i) {
		a[i]=read();
	}
	for(int i=1;i<=n;++i) {
		h[i]=read();
	}
	vector<vector<int>> adj(n+1);
	for(int i=1;i<=n;++i) {
		adj[i].push_back(a[i]);
	}

	vector<int> dfn(n+1),low(n+1),stack_(n+1),c(n+1);
	vector<bool> vis(n+1);
	vector<vector<array<int,2>>> scc(n+1);
	int tim=0,top=0,cnt=0;
	function<void(int)> tarjan = [&](int x) {
		dfn[x]=low[x]=++tim;
		vis[x]=true;
		stack_[++top]=x;
		for(auto y:adj[x]) {
			if(!dfn[y]) {
				tarjan(y);
				low[x]=min(low[x],low[y]);
			} else if(vis[y]) {
				low[x]=min(low[x],dfn[y]);
			}
		}
		if(dfn[x]==low[x]) {
			int now;++cnt;
			do{
				now=stack_[top--];
				vis[now]=false;
				c[now]=cnt;
				scc[cnt].push_back({h[now],now});
			}while(x!=now);
		}
	};
	vector<int> rd(n+1);
	vector<vector<int>> Adj(n+1);
	auto shrinkPoint = [&]() {
		for(int x=1;x<=n;++x)
			for(auto y:adj[x]) {
				if(c[x]==c[y]) continue;
				Adj[c[x]].push_back(c[y]);
				rd[c[y]]++;
			}
	};
	
	for(int i=1;i<=n;++i)
		if(!dfn[i]) tarjan(i);
	shrinkPoint();

	vector<int> val(cnt+1,0);
	vector<int> pos(n+1,0);
	for(int i=1;i<=cnt;++i) {
		if(scc[i].size()==1) {
			val[i]+=scc[i][0][0]*2;
		} else {
			int min_ele=inf;
			for(int j=0;j<scc[i].size();++j) {
				if(scc[i][j][0]<min_ele) {
					min_ele=scc[i][j][0];
					pos[i]=j;
				} 
			}
			for(int j=0;j<scc[i].size();++j) {
				if(j!=pos[i]) {
					val[i]+=scc[i][j][0]*2;
				} 
			}
			val[i]+=min_ele;
		}
	}

	priority_queue<pair<int,int>> q;
	for(int i=1;i<=cnt;++i) {
		if(!rd[i]) {
			q.push({val[i],i});
		}
	}

	vector<int> ans;
	while(!q.empty()) {
		auto [__,x]=q.top();
		q.pop();
		if(scc[x].size()==1) {
			ans.push_back(scc[x][0][1]);
		} else {
			int nowpos=pos[x];
			for(int i=0;i<scc[x].size();++i) {
				nowpos--;
				if(nowpos<0) {
					nowpos=scc[x].size()-1;
				}
				ans.push_back(scc[x][nowpos][1]);
			}
		}
		for(auto y:Adj[x]) {
			if(--rd[y]==0) {
				q.push({val[y],y});
			}
		}
	}
	for(auto i:ans) {
		printf("%lld ",i);
	}
	puts("");
	
}


signed main()
{
	int T=read();
	while(T--) {
		solve();
		fflush(stdout);
	}
	return 0;
}
```



---

## 作者：BHDwuyulun (赞：0)

## 题意
动物园里有 $n$ 个动物，第 $i$ 个动物害怕第 $a_i$ 个动物，第 $i$ 个动物价值 $c_i$ 元。现在我要将这些动物全部卖掉。显然，卖掉的动物编号可以构成一个排列 $p$。
## 思路
考虑卖掉这些动物时：
1. 若 $a_i$ 在 $i$ 还没有卖掉之前就被卖掉了，现在卖掉 $i$，可以获得 $c_i$ 元；
2. 若 $a_i$ 在 $i$ 还没有卖掉之前没被卖掉，现在卖掉 $i$，可以获得 $2·c_i$ 元；

构造并输出赚钱最多的动物卖出顺序。

思路：贪心，假设第 $x$ 个动物可以吃掉的动物价格总和为 $sum$，优先卖掉 $sum$ 小的动物。

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define bug printf("---OK---")
#define pa printf("A: ")
#define pr printf("\n")
#define pi acos(-1.0)
using namespace std;
const ll N=1e5+5;
ll n;
ll a[N],sum[N],c[N];
//价格sum 
priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll> > > q;
bool st[N];
void slove(){
	//假设第x个动物可以吃掉的动物价格总和为sum，优先卖掉sum小的动物 
	memset(a,0,sizeof a);memset(c,0,sizeof c);memset(st,0,sizeof st);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>c[i];
		sum[a[i]]+=c[i];
	}
	for(int i=1;i<=n;i++){
		q.push(make_pair(sum[i],i));
	}
	while(!q.empty()){
		int t=q.top().second;
		q.pop();
		if(st[t]){
			continue;
		}
		st[t]=1;
		cout<<t<<" ";
		sum[a[t]]-=c[t];
		q.push(make_pair(sum[a[t]],a[t]));
	}
}
int main(){
	int t;
	cin>>t;
	while(t--){
		slove();pr;
	} 
	return 0;
}
```

---

