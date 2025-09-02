# [ABC309E] Family and Insurance

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc309/tasks/abc309_e

人 $ 1 $、人 $ 2 $、$ \ldots $、人 $ N $ からなる家系があります。$ i\geq\ 2 $ に対し、人 $ i $ の親は人 $ p_i $ です。

この家系の人たちは $ M $ 回保険に加入しました。$ i=1,2,\ldots,M $ に対し、$ i $ 番目の保険の加入者は人 $ x_i $ で、本人及びその $ y_i $ 代先までの子たちが補償対象者です。

$ 1 $ 個以上の保険の補償対象者になっている人が何人いるかを求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 3\ \times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 3\ \times\ 10^5 $
- $ 1\ \leq\ p_i\ \leq\ i-1 $
- $ 1\ \leq\ x_i\ \leq\ N $
- $ 1\ \leq\ y_i\ \leq\ 3\ \times\ 10^5 $
- 入力はすべて整数
 
### Sample Explanation 1

$ 1 $ 番目の保険について、人 $ 1 $ の $ 1 $ 代先の子たちは人 $ 2 $ と人 $ 4 $ なので人 $ 1,2,4 $ が補償対象者です。 $ 2 $ 番目の保険について、人 $ 1 $ の $ 1 $ 代先の子たちは人 $ 2 $ と人 $ 4 $、$ 2 $ 代先の子は人 $ 3 $ なので人 $ 1,2,3,4 $ が補償対象者です。 $ 3 $ 番目の保険について、人 $ 4 $ の $ 1,2,3 $ 代先の子は存在しないので人 $ 4 $ が補償対象者です。 以上より、$ 1 $ 個以上の保険の補償対象者になっている人は人 $ 1,2,3,4 $ の $ 4 $ 人です。

## 样例 #1

### 输入

```
7 3
1 2 1 3 3 3
1 1
1 2
4 3```

### 输出

```
4```

## 样例 #2

### 输入

```
10 10
1 1 3 1 2 3 3 5 7
2 1
5 1
4 3
6 3
2 1
7 3
9 2
1 2
6 2
8 1```

### 输出

```
10```

# 题解

## 作者：DengDuck (赞：6)

考虑设 $f_x$ 表示 $x$ 可以向下传几级的保险，若为 $0$，则自己有保险，若为 $-1$ 则无保险。

我们初始化把标记打好之后考虑下传，尝试用 $f_x-1$ 来更新 $x$ 的儿子，边做边遍历统计即可。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2e6+5;
LL n,m,x,y,f[N],ans;
vector<LL>v[N];
void dfs(LL x)
{
	if(f[x]!=-1)ans++;
	for(LL i:v[x])
	{
		f[i]=max(f[i],f[x]-1);
		dfs(i);
	}
}
int main()
{
	scanf("%lld%lld",&n,&m);
	f[1]=-1;
	for(int i=2;i<=n;i++)
	{
		f[i]=-1;
		scanf("%lld",&x);
		v[x].push_back(i);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld",&x,&y);
		f[x]=max(f[x],y);
	}
	dfs(1);
	printf("%lld",ans);
}
```

---

## 作者：Loser_Syx (赞：6)

用树解决。  
题目中的 $p_i$ 是 $i$ 的祖先可以抽象成为：$p_i$ 到 $i$ 有一条有向边，然后我们再对于每个点，判断其是否被遍历到了，如果没有的话进行树的 dfs，权值就是最大的 $y_i$，每次向下遍历时权值减一，然后对于每个点的 $y_i$ 取 $\max$。

此外，此题的 $y_i$ 需要加一，因为他自己也能受益，而且 $x_i$ 会重复，选取最大的 $y_i$ 便可。

[代码](https://atcoder.jp/contests/abc309/submissions/43385521)

---

## 作者：ケロシ (赞：2)

## 题意
有一个家庭，用一颗有 $n$ 个结点的有根树表示。   
有 $m$ 个人买了保险，第 $x_i$ 人买了第 $i$ 份保险，并能继承子女 $y_i$ 代，求有多少人有保险。
## 解题思路
考虑 dfs 遍历整颗树。   
其中定义 $f_i$ 为第 $i$ 个人的保险还能继承几代数量加一，如果 $f_i$ 为零，则没有保险。  
随后对于每一个保险记录用 $f_{x_i}=\max(f_{x_i},y_i+1)$ 记录。
然后在树上 dfs，每次更新那份保险能继承更久，   
设 $v$ 的父亲为 $u$，即为 $f_v=\max(f_v,f_u-1)$。   
最后累计哪些人 $f_i > 0$ 即可。  
代码在[这里](https://atcoder.jp/contests/abc309/submissions/43361588)


---

## 作者：small_john (赞：1)

## 思路

简单的深搜题。

我们知道，如果每次买保险单独处理是不行的，我们就采用一种离线算法。

对于每个点 $x$，如果他买了保险，最大的继承数量为 $y$，就记 $a_x=y$。

在深搜的时候，设 $x$ 当前还能继承 $y$，则维护 $y = \max\{y,a_x\}$ 即可。

时间复杂度是 $O(n)$，可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5+5;
int n,m,a[N],ans,head[N],to[N],nxt[N],cnt;
bool vis[N];
void add(int x,int y)
{
	to[++cnt] = y;
	nxt[cnt] = head[x];
	head[x] = cnt;
}
void dfs(int x,int y)
{
	y = max(y,a[x]);
	if(y>0)
	{
		if(!vis[x]) ans++;
		vis[x] = 1;
	}
	for(int i = head[x];i;i=nxt[i])
		dfs(to[i],y-1);
}
int main()
{
	cin>>n>>m;
	for(int i = 2,x;i<=n;i++)
		cin>>x,add(x,i);
	for(int i = 1,x,y;i<=m;i++)
		cin>>x>>y,a[x] = max(a[x],y+1);
	dfs(1,a[1]);
	cout<<ans;
	return 0;
}
```

---

## 作者：kkxacj (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc309_e)

#### 前言

百度翻译误人子弟。

#### 思路

不难发现，如果我们将每个保险都处理了的话，有很多人会多次便利，就会浪费时间，假设如果执行到当前位置后还能再延续 $w$ 代，而当前位置本来可以延续 $z$ 代，如果 $w \ge z$，直接执行当前的，以后到当前位置就不用执行了（因为执行完当前的一定能覆盖它执行后覆盖的人），否则执行以后的，现在先不管。




```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,p[400010],x,y,v[500010],v1[500010],ans;
vector<int>kk[500010];
inline int read(){//快读，但不影响
	int f=1,x=0;char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while('0'<=s&&s<='9'){x=(x<<1)+(x<<3)+s-48;s=getchar();}
	return x*f;
}
inline void dfs(int s,int ww)
{
	for(int i = 0;i < kk[s].size();i++)
	{	
		if(ww > v[kk[s][i]]) 
		{
			v[kk[s][i]] = 1;
			if(ww > 1) dfs(kk[s][i],ww - 1);	
		}
	}
	return;
}
int main()
{
	n = read(); m = read();
	for(int i = 2;i <= n;++i) p[i] = read(),kk[p[i]].push_back(i);
	for(int i = 1;i <= m;++i)
	{
		x = read();y = read();
		v[x] = max(v[x],y); v1[x] = 1;
	} 
	for(int i = 1;i <= n;++i) if(v[i] && v1[i]) dfs(i,v[i]);//i 买了保险，开始延续
	for(int i = 1;i <= n;++i) if(v[i]) ans++;
	cout << ans;
    return 0;
}

```


---

## 作者：zhangjiting (赞：1)

## 思路

如果对于每个保险都跑一遍 dfs 的话，一定会超时。

我们发现，其实只用跑一次 $y_i$ 最大的就可以了。

我们先每个人最大的 $y_i$ 算出来，再进行一遍从根节点开始的 dfs 就可以了。

时间复杂度为 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int head[300005],nxt[300005],to[300005],tot,ans,fa[300005],d[300005];
void dfs(int s,int m){
	m=max(m,d[s]);
	if(m>0) ans++;
	for(int i=head[s];i!=0;i=nxt[i]) dfs(to[i],m-1);
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=2;i<=n;i++){
		cin>>fa[i];
		to[++tot]=i;
		nxt[tot]=head[fa[i]];
		head[fa[i]]=tot;
	}
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		y++;
		d[x]=max(d[x],y);
	}
	dfs(1,0);
	cout<<ans;
	return 0;
}

```


---

## 作者：yuheng_wang080904 (赞：0)

## 题意

有一个家庭，用一棵 $n(1\le n\le 3\times 10^5)$ 个节点的树来表示。有 $m(1\le m\le 3\times 10^5)$ 个人买了保险，$x_i$ 买的第 $i$ 份保险能够继承 $y_i$ 代，问该家庭有多少人有保险。

## 思路

题解区全是 ``dfs``，我来发一篇 ``bfs`` 写的。

先将树建出来，我们要用的是每个节点的儿子。对于第 $i$ 份保险，共对 $y_i+1$ 代产生作用，每个人手上的保险取最长的记为 $g_i$。在 ``bfs`` 的过程中，一个人 $i$  的保险更新为 $\max(g_i,g_{fa}-1)$，若为 $0$，则无保险；反之则有。

## 代码

```cpp
ll n,m,fa[300005],g[300005],cnt;
vector<int>son[300005];
int main(){
    cin>>n>>m;
    for(int i=2;i<=n;i++)cin>>fa[i];
    for(int i=2;i<=n;i++)son[fa[i]].pb(i);
    for(int i=1;i<=m;i++){
	ll x,y;
	cin>>x>>y;
	g[x]=max(g[x],y+1);
    }
    queue<int>q;
    q.push(1);
    while(!q.empty()){
	int a=q.front();
	q.pop();
	if(g[a])cnt++;
	for(auto i:son[a]){
	    q.push(i);
	    g[i]=max(g[i],g[a]-1);
	}			
    }
    cout<<cnt<<endl;
    return 0;
}
```


---

## 作者：封禁用户 (赞：0)

## 分析

根据包含关系，如果一个人买了一个可以传 $a$ 代的保险后再买了一个可以传 $b$ 代的保险，那么这个人能传的代数就是 $\max(a,b)$。而一个能传 $x$ 代的保险，在第 $i$ 代之后就相当于第 $i$ 代所对应的这个人有一个可以传 $x-i$ 代的保险。

用上面的思路，我们可以遍历每一个人，一旦这个人还能传下去，我们就把下面那个人能传的代数更新，并标记这个人有保险。最后统计有保险的人数之和即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,int>
#define x first
#define y second
const int N=2e6+10;
int n,m;
int ne[N],e[N],h[N],idx;
void add(int a,int b){
	ne[idx]=h[a],e[idx]=b,h[a]=idx++;
}
int cnt[N];
bool vis[N];
int kk[N];//有没有保险
void dfs(int now,int fa,int k){
	vis[now]=1;
	if(k==0){
		return ;
	}
	kk[now]=1;
	for(int i=h[now];~i;i=ne[i]){
		int j=e[i];
		cnt[j]=max(cnt[j],cnt[now]-1);//取最广的
		dfs(j,now,cnt[j]);
	}
}
signed main(){
	memset(h,-1,sizeof(h));
	cin>>n>>m;
	for(int i=2;i<=n;i++){
		int x;cin>>x;
		add(x,i);
	}
	for(int i=1;i<=m;i++){
		int x,y;cin>>x>>y;
		cnt[x]=max(cnt[x],y+1);
		//可能传0代，所以我们把这个人本身也看做1代
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]&&cnt[i]!=0){
			dfs(i,-1,cnt[i]);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(kk[i]){
			ans++;
		}
	}
	return cout<<ans,0;
}
```


---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc309_e)    
一眼。
## 题意
有 $n$ 个人，第 $i(i≥2)$ 个人的亲属是 $p_i$。     
这些人买了 $m$ 个保险，第 $i$ 份保险是 $x_i$ 买的，它可以使 $x_i$ 自己和它的下 $y_i$ 代受到保险。   
问你最后又多少人受到了保险。    
## 解法
先考虑朴素做法，即对每一个保险都跑一次 dfs。   
这种做法最坏明显为 $O(n^2)$，无法通过。     
我们发现，如果同样的人买了许多保险，那么我们的朴素做法就多算了很多步，实际上，我们只需要把 $y_i$ 最大的跑一次即可。    
那么我们仿照线段树上懒标记的思想，先把第 $i$ 个人的最大 $y_i$ 找出来，之后再进行一遍以根为起点的 dfs 即可。      
dfs 时我们要记录当前结点上，保险还对下多少代有效。   
时间复杂度为 $O(n)$，可以通过。       
[CODE](https://www.luogu.com.cn/paste/a5clltfq)

---

