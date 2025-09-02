# Edge Weight Assignment

## 题目描述

You have unweighted tree of $ n $ vertices. You have to assign a positive weight to each edge so that the following condition would hold:

- For every two different leaves $ v_{1} $ and $ v_{2} $ of this tree, [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of weights of all edges on the simple path between $ v_{1} $ and $ v_{2} $ has to be equal to $ 0 $ .

Note that you can put very large positive integers (like $ 10^{(10^{10})} $ ).

It's guaranteed that such assignment always exists under given constraints. Now let's define $ f $ as the number of distinct weights in assignment.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338B/eb47baeab358a9bf4d6536421055c2c258904b33.png) In this example, assignment is valid, because bitwise XOR of all edge weights between every pair of leaves is $ 0 $ . $ f $ value is $ 2 $ here, because there are $ 2 $ distinct edge weights( $ 4 $ and $ 5 $ ).![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338B/158a70d1382d5b7e8863700d0f77901af19c305f.png) In this example, assignment is invalid, because bitwise XOR of all edge weights between vertex $ 1 $ and vertex $ 6 $ ( $ 3, 4, 5, 4 $ ) is not $ 0 $ .

What are the minimum and the maximum possible values of $ f $ for the given tree? Find and print both.

## 说明/提示

In the first example, possible assignments for each minimum and maximum are described in picture below. Of course, there are multiple possible assignments for each minimum and maximum.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338B/c4eae7135fc2816569401e9d249b68afcb80223d.png)In the second example, possible assignments for each minimum and maximum are described in picture below. The $ f $ value of valid assignment of this tree is always $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338B/baad69bf823b2a9aa4bb5b201a45aae8769d51f6.png)In the third example, possible assignments for each minimum and maximum are described in picture below. Of course, there are multiple possible assignments for each minimum and maximum.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338B/4ce205cbdc1e4310ee123b92671ae7a1941bacd7.png)

## 样例 #1

### 输入

```
6
1 3
2 3
3 4
4 5
5 6```

### 输出

```
1 4```

## 样例 #2

### 输入

```
6
1 3
2 3
3 4
4 5
4 6```

### 输出

```
3 3```

## 样例 #3

### 输入

```
7
1 2
2 7
3 4
4 7
5 6
6 7```

### 输出

```
1 6```

# 题解

## 作者：Marser (赞：18)

### 题意
给定一棵 $n$ 个点的无根树，要求给每条边分配一个**正整数**权值，使得任意两个叶子节点之间路径上的边权异或值为 $0$。求最少要多少种不同权值，以及最多可以使用多少种不同权值。  
这里，填入的边权值可以为任意大。  
$3 \le n\le 10^5$
### 题解
一看过去就感觉是个二合一题，我们先从最少权值入手。  
注意到 $1\oplus 2\oplus 3 = 0$ ，且 $\forall x \in N_{+}~,~x\oplus x=0$。所以，如果树上所有叶子节点之间距离均为偶数，我们直接给所有边赋上相同的权值，偶数个相同数异或起来就消掉了。因此，这样最少只需要一种权值。  
那么，如果树上存在长度为奇数的叶结点间路径呢？  
我们考虑一种构造方法：  
![](https://cdn.luogu.com.cn/upload/image_hosting/9a9cumdw.png)

如图，在 $1$ 号点为根的情况下，我们把到根节点距离为奇数的叶子节点称为奇点，类似定义偶点。若奇点的距离为 $2k+1$，我们从上到下填入 $2k$ 个 $3$ 和一个 $1$ 。若偶点的距离为 $2k$，我们从上到下填入 $2k-1$ 个 $3$ 和一个 $2$。易知这样填数一定满足每条从根到叶子节点的链上异或值为 $1$。  
同样，因为两个叶子节点必然在它们的 LCA 处合并，为了去掉这段贡献，我们需要扣掉两遍从根到 LCA 间的权值，这中间每个权值都被扣掉了两遍，很显然不影响结果。  
由于每个叶子节点连向父亲的边必然只会被它自己经过，因此不会影响到其他叶子节点，这样构造是可行的。  
只用两个数 $x,y$ 构造的话，奇数个数只能表示出 $x$ 或 $y$，根据题设，这样不合法。  
因此，如果树上存在奇数长度的路径，最少只需要三种权值即可。

考虑最大可以使用多少种权值。显然，如果若干个叶子节点父亲相同，这些节点所连边的权值也必须相同。接下来就转化为非叶节点之间的边权问题了。由于所填的数权值可以任意大，我们完全可以用互不相同的权值填满所有非叶节点之间的边。同样，父亲不同的叶结点，所连边的权值也完全可以不同。扣掉这些权值重复的边，就能得出最大可以使用的权值种数了。
### 代码
```cpp
#include<bits/stdc++.h>
#define reg register
using namespace std;
typedef long long ll;
const int MN=1e5+5;
int to[MN<<1],nxt[MN<<1],h[MN],cnt;
inline void ins(int s,int t){
	to[++cnt]=t;nxt[cnt]=h[s];h[s]=cnt;
	to[++cnt]=s;nxt[cnt]=h[t];h[t]=cnt;
}
int n,Ans=1,deg[MN];
bool f[MN][2];
void dfs1(int st,int fa=0){
	if(!nxt[h[st]])f[st][0]=true;
	for(reg int i=h[st];i;i=nxt[i])
		if(to[i]!=fa){
			dfs1(to[i],st);
			if(f[to[i]][0]&&f[st][0])Ans=3;
			if(f[to[i]][1]&&f[st][1])Ans=3;
			f[st][0]|=f[to[i]][1];
			f[st][1]|=f[to[i]][0];
		}
}
void dfs2(int st,int fa=0){
	if(!nxt[h[st]]){
		if(st==1)deg[to[h[st]]]++;
		else{deg[fa]++;return;}
	}
	for(reg int i=h[st];i;i=nxt[i])
		if(to[i]!=fa)dfs2(to[i],st);
}
int main(){
	scanf("%d",&n);
	for(reg int i=1,s,t;i<n;i++)
		scanf("%d%d",&s,&t),ins(s,t);
	dfs1(1);printf("%d ",Ans);
	Ans=n-1;dfs2(1);
	for(reg int i=1;i<=n;i++)
		if(deg[i])Ans-=deg[i]-1;
	printf("%d\n",Ans);
	return 0;
}
```

---

## 作者：too_later (赞：14)

~~第一次考场上做出的 $Div$ $2$ $D$ 题~~

**题意**

- 对于每对叶子结点，保证他们之间的最短路径异或和为 $0$，求出现边权种类个数的最大 / 小值 。

**思路**

设一个度不为1的点做跟。

1. 两叶子 $ u, v$ 最短路径的异或和，也就相当于 $u, v$ 到他们根节点的异或和。因为异或具有自反性（$LCA$ 异或到根节点，根节点再异或回 $LCA$， 结果不变）。

2. 考虑最小值：如果两个叶子结点的深度和全部为偶数的话，那么答案为 $1$（异或的自反性，偶数个 $a$ 异或结果为 0）。如果出现了深度和为奇数的情况，那么要使得路径上两个节点，那么答案为 $3$（有 $b$ ^ $c$ = $a$，易证 $a, b, c$ 互不相等）。

3. 考虑最大值：将最大值初始化为边数，如果一个节点有 $k$ 个儿子为叶子结点，那么显然他们到父亲的权值必须相同。那么最大值减去 $k - 1$。

时间复杂度 $O(n)$。

代码（毒瘤码风勿喷）：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;

vector<int> tr[maxn];
int n, x, y, ans, vis[maxn], dep[maxn];
bool is[2];

int dfs(int u, int fa){
	
	dep[u] = dep[fa] + 1; 
	if(tr[u].size() == 1){
		vis[dep[u]] = 1; //记录叶子结点深度 
		return 1; // 这是叶子结点 
	}
	
	int sum = 0;
	for(int v, i = 0; i < tr[u].size(); i++)
		if((v = tr[u][i]) != fa){
			sum += dfs(v, u); // 记录叶子结点个数 
		}
	
	ans -= max(0, sum - 1); // 步骤3 
	return 0; // 这不是叶子结点 
}

int main(){
	
	scanf("%d", &n); ans = n - 1;// 初始化最大值 
	
	for(int i = 1; i < n; i++)
		scanf("%d%d", &x, &y), tr[x].push_back(y), tr[y].push_back(x);
	
	for(int i = 1; i <= n; i++)
		if(tr[i].size() != 1)
			{ dfs(i, 0); break; } //找到根节点 
	
	for(int i = 1; i <= n; i++)
		if(vis[i])
			is[i & 1] = 1; //查看叶子结点深度奇偶性 
	
	if(is[0] && is[1]) printf("3 "); //深度和为奇数 
	else printf("1 "); // 深度和为偶数 
	printf("%d\n", ans);
	
	return 0;
}
```


---

## 作者：奇米 (赞：10)

## 题解- CF1338B Edge Weight Assignment

[$$\huge\color{blue}\boxed{\color{Violet}\mathfrak{There\ is \ my \ blog}}$$](https://www.luogu.com.cn/blog/wyy2020/)

### **题目意思**

* [Div1 B](https://www.luogu.com.cn/problem/CF1338B)
* 给你一个颗树让你给他上面的点填数字使得任意两个叶子之间的异或和为$0$，问最多/少多少种不同的权值来使得填数字是合法的。
* $n,a_i,b_i\leq 10^5$

### $\mathrm{Sol}$

* 一道结论题
* 最小值很显然就只有$1,3$两种情况（当存在任意两个叶子之间的距离为奇数那么是$3$，因为偶数个相同的数异或为$0$）这个一遍$dfs$就可以了。
* 那么对于最大值，我们有个结论就是把一个节点的叶子节点合并成一个节点然后计算修改过后树边的数量（样例来画个图来看看

![](https://cdn.luogu.com.cn/upload/image_hosting/lk13ajrz.png?x-oss-process=image/resize,m_lfit,h_270,w_525)

* 时间复杂度$O(n)$

### $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int N=1e5+5;

int n,m,zz,in[N],vis[N];
vector<int> G[N];

inline void dfs(int u,int fa,int dep)
{
	if(G[u].size()==1&&dep%2==1) zz=1;
	for ( int i=0;i<G[u].size();i++ )
	{
		int v=G[u][i];
		if(v==fa) continue;
		dfs(v,u,dep+1);
	}
}

int main()
{
	n=read();
	for ( int i=1;i<n;i++ )
	{
		int x,y;
		x=read(),y=read();
		G[x].pb(y);
		G[y].pb(x);
		in[y]++;
	}
	int rt=0;
	for ( int i=1;i<=n;i++ ) if(G[i].size()==1) 
	{
		rt=i;
		break;
	}
	dfs(rt,0,0);
	(zz)?printf("3 "):printf("1 ");
	int mx=n-1;
	for ( int i=1;i<=n;i++ ) 
	{
		int gs=0;
		for ( int j=0;j<G[i].size();j++ )
		{
			int v=G[i][j];
			if(G[v].size()==1) gs++;
		}
		mx-=gs;
		if(gs) mx+=1;
	}
	printf("%d\n",mx);
}

```


---

## 作者：gyh20 (赞：8)

一道有趣的结论题。

先设置一个度不为 $1$ 的点为根。

首先，题目满足的其实就是所有叶子节点到根路径的异或值相同。

考虑最小值，如果所有叶节点到根的路径长度奇偶性相同，那么直接全部填 $1$ 即可，否则，全部选 $1,2,3$ 即可（在没有连接叶节点的边上交错填 $1,2$ 在叶子节点前的边填数使得权值相等即可），所以，答案为 $1$ 或 $3$。

最大值其实也不难，因为我们填的数可以很大，所以对于每一个节点，如果存在到叶节点的路径则到叶节点的路径权值必须相等，其它的可以不等，所以可以树形 DP，记录是否存在叶节点即可，判叶子结点可以直接用度数是否为 $1$。

```
#include<bits/stdc++.h>
using namespace std;
#define re register
inline int read(){
	re int t=0,f=0;re char v=getchar();
	while(v<'0')f|=(v=='-'),v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
} 
int n,m,t,a[100002],mx,ans,cnt,du[200002],rt,dp[200002],num,head[200002];
struct edge{
	int to,next;
}e[200002];
inline void add(re int x,re int y){
	e[++cnt].to=y;
	e[cnt].next=head[x];
	head[x]=cnt;
}
inline int dfs(re int x,re int y,re int z){
	if(du[x]==1){
		ans+=z;
		++num;dp[x]=-1;
		return 1;
	}dp[x]=0;re int nnn=0;
	for(re int i=head[x];i;i=e[i].next){
	if(e[i].to^y){
		

	nnn|=dfs(e[i].to,x,z^1),dp[x]+=dp[e[i].to]+1;}}
	if(nnn)++dp[x];
	return 0;
}
signed main(){
	n=read();
	for(re int i=1,x,y;i<n;++i){
		x=read();y=read();++du[x];++du[y];
		add(x,y);add(y,x);
	}
	for(re int i=1;i<=n;++i)if(du[i]>1)rt=i;
	dfs(rt,rt,1);
	printf("%d %d\n",ans%num?3:1,dp[rt]);
}
```



---

## 作者：Eibon (赞：5)

结论题。

因为看叶子结点，不妨令一个入度不为 $1$ 的点为根。

容易发现，如果叶子节点间距离均为偶数，则最小答案为 $1$。因为一个数异或自己为 $0$。

否则，答案最小为 $3$，因为 $1\bigoplus2=3$。一定能构造出一种方案。可以在路径上设置 $2k$ 个 $1$ ，$1$ 个 $2$，$1$ 个 $3$。

判断距离均为偶数或是存在奇数，只需判断深度为奇数和偶数的点有没有同时出现即可。若出现了，则存在深度为奇数点。

考虑答案最大的情况。令 $ans=n-1$。

因为每个父亲节点相同的叶子节点与它们父亲节点的连边必须相同，所以 $ans$ 要减去父亲节点所连的叶子结点的个数减 $1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
int n,u,v,tot,cnt,s,ans,f1,f2,cnt2;
int head[maxn],ru[maxn],num[maxn],a[maxn];
int dis[maxn],sz[maxn],pa[maxn],num2[maxn];
struct edge
{
	int to,nxt;
};
edge e[maxn<<1];
void add(int u,int v)
{
	e[++tot]={v,head[u]};
	head[u]=tot;
}
void dfs(int u,int fa)
{
	pa[u]=fa;
	dis[u]=dis[fa]+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa){
			continue;
		}
		dfs(v,u);
	}
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<n;i++){
		scanf("%lld%lld",&u,&v);
		add(u,v);add(v,u);
		ru[u]++;
		ru[v]++;
	}
	for(int i=1;i<=n;i++){
		if(ru[i]!=1){
			s=i;
		}
		if(ru[i]==1){
			num[++cnt]=i;
		}
	}
	dis[0]=-1;
	dfs(s,0);
	for(int i=1;i<=cnt;i++){
		if(dis[num[i]]&1){
			f1=1;
		}
		else{
			f2=1;
		}
	}
	if(f1&&f2){
		printf("3 ");
	}
	else{
		printf("1 ");
	}
	for(int i=1;i<=cnt;i++){
		if(!num2[pa[num[i]]]){
			num2[pa[num[i]]]=1;
			a[++cnt2]=pa[num[i]];
		}
		sz[pa[num[i]]]++;
	}
	ans+=n-1;
	for(int i=1;i<=cnt2;i++){
		ans-=sz[a[i]]-1;
	}
	printf("%lld\n",ans);
	return 0;
}
//dyyyyds
```

---

## 作者：ix35 (赞：3)

好玩又清新的题。

首先搞最小值，可以证明一个结论：**答案最小值不超过 $3$。**

我们可以用 $1,2,3$ 三种权值构造一种可能的情形：

考虑自顶向下拓扑排序，维护每个点到根结点的边权异或和 $d_i$。设当前出队的是点 $v$，点 $u$ 是 $v$ 的父亲，如果 $u$ 为根结点则令 $(u,v)$ 边权为 $1$，否则将 $(u,fa_u)$ 和 $(u,v)$ 两条边的边权改成不与原 $(u,fa_u)$ 边权相等的两种权值即可，容易发现新的 $d_v$ 会等于原来的 $d_v$，最终所有叶子的 $d_i=1$，满足条件。

然后考虑一下什么时候答案是 $1$：

考虑将树作为二分图，当且仅当所有叶子都在一部时答案是 $1$，只需检验叶结点深度奇偶性是否一致即可（注意根结点必须是非叶结点，我的做法和官方题解不同）。

我做的时候就直接断言除此之外答案为 $3$ 了，实际上还可以说明一下 $2$ 是不优于 $1$ 的，所以不可能用到 $2$ 种权值。

接下来考虑最大值，这里我用了一个 DP。

设 $dp(i)$ 表示 $i$ 的子树内至少需要几种权值，使得每个叶子到根的权值异或和相等。

转移：

$$dp(i)=\Big(\sum\limits_{j\in Son(i)} dp(j)+[j\notin Leaves]\Big)+[\exists j\in Son(i),\ j\in Leaves] $$

这是因为，所有 $i$ 的子结点种的叶结点 $j$，它们到 $i$ 的权值是相等的，所以只有一种（和式中最后一项），前面的就是任意的（因为通过下面的调整可以使得上面的权值为任意值）。

如果你观察力和题解一样好，你就会发现这个东西可以用 叶结点个数，和叶结点相邻的结点个数，总点数 来表示，不用这样 DP，当然是我没这么聪明了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=100010;
int n,x,y,eg,flg[2],in[MAXN],hd[MAXN],ver[2*MAXN],nx[2*MAXN],dp[MAXN],dep[MAXN],isl[MAXN];
void add_edge (int x,int y) {
	ver[++eg]=y;
	nx[eg]=hd[x];
	hd[x]=eg;
	return;
}
void dfs (int x,int fa) {
	isl[x]=1,dep[x]=dep[fa]+1;
	int res=0,flg2=0;
	for (int i=hd[x];i;i=nx[i]) {
		if (ver[i]==fa) {continue;}
		dfs(ver[i],x);
		isl[x]=0;
		if (isl[ver[i]]) {flg2=1;}
		else {
			dp[x]+=dp[ver[i]]+1;
		}
	}
	dp[x]+=flg2;
	return;
}
int main () {
	scanf("%d",&n);
	for (int i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		add_edge(x,y),add_edge(y,x);
		in[x]++,in[y]++;
	}
	for (int i=1;i<=n;i++) {
		if (in[i]>=2) {
			dfs(i,0);
			for (int j=1;j<=n;j++) {
				if (isl[j]) {flg[dep[j]&1]=1;}
			}
			if (flg[0]^flg[1]) {printf("%d ",1);}
			else {printf("%d ",3);}
			printf("%d\n",dp[i]);
			break;
		}
	}
	return 0;
}
```





---

## 作者：yanshenshizu (赞：3)

## 一些~~鲜花~~
   当初与机房大佬一块做这道题，机房大佬表面上心不在焉，实际上很快他就想出来了 **orz** ,并且对本篇题解指出了许多不足。
   
   这里贴出链接:[大佬主页](https://www.luogu.com.cn/user/439405#main)    
## 思路  
* 首先看到integers like $10^{10^{10}}$这个描述，我们就知道这道题就和数字本身没有关系，因此这道题是一道规律题(构造时贪心{算是吧}])。  

那既然是找规律了我们就先找最小时的规律:   

![](https://cdn.luogu.com.cn/upload/image_hosting/yo4olr1a.png)  

此时度数>1的点数有过单数，所以全部填同一个数肯定无法满足题意，因而我们只能乖乖的填上1,2,3,这三种数    

![](https://cdn.luogu.com.cn/upload/image_hosting/wyf8zjqe.png)  

 当度数>1的点数没有过单数时，就可以疯狂填1了~~上上上!!!~~    
  
于是你就可以找到一个叶子节点遍历，算出除叶子节点外的点的深度，查找是否存在下一个点为叶子的dep为单数的点，如果存在就````printf("3 ");````否则就
````printf("1 ");````
   
* 然后我们来找最大的规律：   

我们考虑贪心的填，尽量让每条边都不同，在度数>1的点上这显然可行~~毕竟10的...次方~~,计算一下度数>1的点的个数，减一就是边数了（du2-1）;  
  
在度数==1的叶子节点上，同一个父亲下的叶子只能填同一个,so，定义一个sum，遍历度数>1的点，如果他有叶子儿子就让sum++；  
  
最后du2+sum就是最终结果。
##  到了喜闻乐见的代码环节了  
* AC code:(不要抄袭哦，自己写出来才是真正的锻炼)   
````c++
#include<bits/stdc++.h>
using namespace std;
int du[100005];//存度数
int n;
int from[100005<<1],tot;//链式前向星存图
struct  node
{
    int to,bian;
}tu[100005<<1];
void add(int u,int v)
{
    int now=++tot;
    tu[now].bian=v;
    tu[now].to=from[u];
    from[u]=now;
}
int du1,du2;//du1没用，du2就是度数>1的点数
int s;//找出一个叶子当根方便遍历
bool three;//判断最小时是一还是三
void dfs_min(int x,int f,int dep)
{
    for(int i=from[x];i;i=tu[i].to)
    {
        int v=tu[i].bian;
        if(v==f)continue;//不能又搜回父节点
        if(du[v]>1)//如果搜到的是非叶子节点，接着往下搜，让dep++
        {
            dfs_min(v,x,dep+1);
        }
        else if(du[v]==1)
        {
            if(dep%2==0&&dep>0)//如果下一个点是叶子节点并且dep为双数（即边数为单数),
            {//就结束搜索，直接认为会输出三
                three=1;
                return ;
            }
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
        du[u]++;du[v]++;
    }
    for(int i=1;i<=n;i++)
    {
        if(du[i]==1)du1++,s=i;//找出叶子节点当根
        else du2++;//找出非叶子节点个数
    }
    dfs_min(s,s,0);//搜最小情况
    if(three)
    {
        printf("3 ");
    }
    else printf("1 ");
    int tmp=0;
    for(int i=1;i<=n;i++)
    {
        if(du[i]>1)
        {
            int tt=0;
            for(int j=from[i];j;j=tu[j].to)
            {
                int v=tu[j].bian;
                if(du[v]==1)tt++;
            }
            if(tt)tmp++;//如果非叶子节点的有叶子儿子，加入计数中
        }
    }
    printf("%d",du2-1+tmp);//du2记得减一，因为求得是边数。
    return 0;
}
````

---

## 作者：liuzr156 (赞：2)

dp 没想到，所以就用了纯搜索过了此题。

首先研究样例，我们可以发现：最少权值（以下简称最小值）要么是 $1$ 要么是 $3$。

理由：要求满足叶子之间的路径长度可以分为两种，一种是长度为奇数，一种是长度为偶数。对于距离长度为偶数的两个叶子，我们直接让其间都为同一个数即可；对于距离长度为奇数的两个叶子，我们在将其中 $3$ 条边的权值令为 $x$，$y$，$z$，并且保证 $x\oplus y\oplus z = 0$，然后剩下的要给权值的边数就变成了偶数条，然后再全都给 $x$，$y$，$z$ 中的其中之一即可。

为什么一定是最少的呢？首先距离为偶数很显然最小只能是 $1$。那么对于距离为奇数，首先最小值一定不能是 $1$。那么我们假设最小值可以为 $2$，权值有 $a$ 个 $x$，$b$ 个 $y$，且 $a+b=$ 两个叶子间的距离。如果 $a$ 为奇数，$b$ 为偶数，则 $a$ 个 $x$ 异或的结果为 $x$，$b$ 个 $y$ 异或的结果为 $0$，再异或起来就是 $x$，不行。当 $a$ 为偶数，$b$ 为奇数时同理，故假设不成立，所以两个叶子距离为奇数时最小值只能是 $3$。

所以我们的第一个答案就出来了：当有两个叶子之间的距离为奇数时为 $3$，否则为 $1$。

接下来是最多权值（以下简称最大值）。手画几个例子后可以很容易地发现这个最大值最大为 $n-1$，最小为 $1$。然后可以尝试画一下图，对于一条链，长度为 $1$ 时无解（数据范围保证没有），长度为 $2$ 时最大值为 $1$，长度为 $3$ 时最大值为 $3$，长度为 $4$ 时最大值为 $4$，长度为 $5$ 时最大值为 $5$……以此类推我们可以发现只有在长度为 $2$ 时会使得最大值减少。接下来我们把树上每两个叶子之间的类路径想象成一条链，对于每个链，情况就和上面举的例子一样，所以我们只需要计算有几个叶子之间距离为 $2$，然后在 $n-1$ 上面减去即可。

对于最小值计算部分 $O(n^2)$ 的实现很显然。但是必须要 $O(n)$，所以我们可以先找一个非叶子节点作为根，然后计算每个节点到根的距离，对于任意两个叶子之间的距离就变成两个点到根的距离，当两个点到根的距离奇偶性相同时两叶子距离即为偶数。所以我们先计算再一个个判断即可。

对于最大值计算部分，我们先把叶子存起来，然后对每个叶子进行 dfs 找距离为 $2$ 且是叶子的节点，然后奇数减去即可。记得要判断重复问题以及一点剪枝，不然可能退化成 $O(n^2)$。

总体时间复杂度 $O(n)$，虽然常数比较大但是还是可以通过。

```cpp
#include <bits/stdc++.h>

#define LL long long

using namespace std;
const int N = 1e5 + 10 , INF = 0x3f3f3f3f;
inline LL read(){
	   LL x = 0 , f = 1 ; char ch = getchar();
	   while (ch < '0'||ch > '9'){if (ch == '-') f = -1 ; ch = getchar();}
	   while (ch >= '0'&&ch <= '9'){x = x * 10 + ch - 48 ; ch = getchar();}
	   return x * f;
}
void write(LL x){
    if(x < 0)
        putchar('-'),x = -x;
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
int h[N] , e[N<<1] , nex[N<<1] , idx;
int leaf[N];
void add(int a , int b){
	e[++idx] = b;
	nex[idx] = h[a];
	h[a] = idx;
}
int dis[N];
void dfs1(int u , int fa){
	for(int i = h[u];i ;i = nex[i]){
		int v = e[i];
		if(v == fa) continue ;
		dis[v] = dis[u] + 1;
		dfs1(v , u);
	}
}
bool vis[N];
int dfs2(int u , int dis){
	if(dis == 2)
		return (leaf[u] == 1);	
	int sum = 0;
	for(int i = h[u];i ;i = nex[i]){
		int v = e[i];
		if(vis[v]) continue ;
		vis[v] = 1;
		int x = dfs2(v , dis + 1);
		sum += x;
		if(!x || dis + 1 != 2) vis[v] = 0;
	}
	return sum;
}
signed main(){
	int n = read();
	for(int i = 1;i < n;i ++)
	{
		int a = read() , b = read();
		add(a , b)  ,add(b , a);
		leaf[a] ++  , leaf[b] ++;
	}
	int root;
	vector<int> a;
	for(int i = 1;i <= n;i ++){
		if(leaf[i] != 1)
			root = i;
		else
			a.push_back(i);
	}
	dfs1(root , 0);
	bool f1 = 0 , f2 = 0;
	for(int i = 1;i <= n;i ++){
		if(leaf[i] != 1) continue ;
		if(dis[i] % 2) f1 = 1;
		else f2 = 1;
		if(f1 && f2) break ;
	}
	int ans1 = (f1 && f2) ? 3 : 1 , ans2 = n - 1;
	for(auto i : a){
		if(vis[i]) continue ;// 一定要加，不然会 TLE
		vis[i] = 1;
		int x = dfs2(i , 0);
		ans2 -= x;
	}
	cout << ans1  << " " << ans2 ;
	return 0;
}

```


---

## 作者：老咸鱼了 (赞：2)

题目大意：给你一棵树，问你任意两个叶子节点之间的简单路劲的异或和为0，求最少能有几种不同的边权和最多能有几种不同边权。

乍一看题目好像很复杂，要我们求这个任意两个的异或和为0，但是题目只要我们求最多和最少的两种数量有多少并没有要我们实现这个操作。

对于最少的情况：

我们只要判断能不能让所有边权相，相等的话也就是任意两叶子节点之间的简单路劲长度一定是偶数，我们只需要判断根节点到叶子节点的深度对2取模是否都是奇数或者是否都是偶数就行了。

对于最多的情况：
首先我们可以得出，叶子节点如果具有相同的父亲，那么他们的边权一定给相同，否则异或和不可能是0，然后注意题目说了一句话Note that you can put very large positive integers (like 10^(10^10))你可以让这个边权想有多大就有多大，构建的话就是只要让每两个叶子节点的最近公共祖先的左边的异或和等于右边的异或和就行了，可以得到结论这样构造出来的一定满足任意两点之间的简单路径异或和是0，所以最多有多少不同的边权我们只要减去有多少个叶子节点有相同的父亲，减去重复的就行了。

code：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1555555;
inline ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;c=getchar();
	}
	while(c>='0'&&c<='9'){
		s=(s<<1)+(s<<3)+(c^48);c=getchar();
	}
	return f*s;
}
vector<int>q[N];
int n,ji,ou,ans;
int vis[N];
void dfs(int u,int fa,int deep){
	if(q[u].size()==1){
		if(deep%2==1)ji=1;
		else ou=1;
		ans-=vis[q[u][0]];
		vis[q[u][0]]=1;
	}
	for(int i=0;i<q[u].size();i++){
		int t=q[u][i];if(t==fa)continue;
		dfs(t,u,deep+1);
	}
}
int main(){
	n=read(),ans=n-1;
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		q[x].push_back(y);
		q[y].push_back(x);
	}
	dfs(1,1,1);
	cout<<(ji&&ou?3:1)<<" "<<ans<<endl;
	return 0;
}

```


---

## 作者：UncleSam_Died (赞：1)

### 解题思路
一种不需要树形 dp 的做法。

因为是一颗无根树，所以我们不妨以重心为根。

首先考虑边权最少的情况。可以发现这个时候对于任意两个叶子节点，我们可以分别考虑其到根节点的路径，这样对于求其路径的异或值是没有影响的，但是在这种情况下我们可以很方便的讨论其路径的奇偶性。令 $d(x,y)$ 表示从 $x$ 到 $y$ 的深度之差，$root$ 表示根节点，那么对于任意两个叶子节点 $u$ 和 $v$，情况如下：
- $d(u,root)$ 为奇，$d(v,root)$ 为奇，那么可以构造两条相同的路径使得其中边权均为相同的数，此时需要 $1$ 种异或值；
- $d(u,root)$ 为偶，$d(v,root)$ 为奇，那么这个时候可以构造其中 $u$ 到 $root$ 的路径上有两种边权，不妨设它们为 $w_1$ 和 $w_2$，且其中一种边权出现一次，剩下的均为另一种边权，同时，我们把 $v$ 到 $root$ 的路径上的边全部赋为 $w_1\oplus w_2$，这种情况下，我们最少使用 $3$ 种权值；
- $d(u,root)$ 为奇，$d(v,root)$ 为偶，同上；
- $d(u,root)$ 为偶，$d(v,root)$ 为偶，同样可以将 $u$ 到 $root$ 的路径上的边和 $v$ 到 $root$ 上的边全部赋为同一种权值，这时使用 $1$ 种权值。

接下来考虑边权最多的情况。不难发现，拥有同一个父亲节点的叶子节点，它们到父亲节点的边权一定是相同的，那么我们可以考虑合并这些叶子节点。合并后观察可以得出，因为边权可以为任意正整数，那么一定存在一种构造方案使得任意两个叶子节点之间路径的异或值为 $0$ 且合并后剩余的每条边的边权均不相同。

综上所述，本题解题步骤如下：
- 计算出重心，当然也可以选择其他不是叶子节点的点作为根节点；
- 计算所有叶子节点到根节点的距离，此时的距离等于两点之间的深度差的绝对值；
- 判断所有距离的奇偶性，若所有距离的奇偶性相同，那么最小值为 $1$，否则为 $3$；
- 因为合并后一个节点最多连向一个叶子节点，那么我们剩余的边数即为 $\displaystyle n-1-\sum_{i=1}^n (cnt_{leaves} -1)$，在计算距离的时候顺便判断计算一下即可。

### AC 代码
```cpp
#include<stdio.h>
#include<vector>
#include<algorithm>
#define N 100005
#define inf 2e9+7
int n;
std::vector<int> edge[N];
int root=1,sum;
int maxt[N],size[N];
inline void FindRoot(int u,int fa){
    size[u]=1;
    for(auto v:edge[u]){
        if(v==fa) continue;
        FindRoot(v,u);
        size[u]+=size[v];
        if(size[v]>maxt[u])
            maxt[u]=size[v];
    }if(sum-size[u]>maxt[u])
        maxt[u]=sum-size[u];
    if(maxt[u]<maxt[root])
        root=u;
}
int depth[N],lea[N],cnt,tot[N];
inline void dfs(int u,int fa){
    bool isLeavf=true;
    for(auto v:edge[u]){
        if(v==fa) continue;
        depth[v]=depth[u]+1;
        dfs(v,u);isLeavf=false;
    }if(isLeavf){
        lea[++cnt]=u;
        ++tot[fa];
    }
}
signed main(){
    scanf("%d",&n);int u,v;
    for(register int i=1;i<n;++i){
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }sum=n;maxt[root]=inf;
    FindRoot(1,0);dfs(root,0);
    int odd=0,eve=0,maxt=0,sema=0;
    for(register int i=1;i<=cnt;++i){
        if(depth[lea[i]]&1)
            ++odd;
        else ++eve;
    }if(!odd||!eve)
        putchar('1');
    else putchar('3');
    putchar(' ');int sub=0;
    for(register int i=1;i<=n;++i)
        sub+=tot[i]?tot[i]-1:0;
    printf("%d",n-1-sub);
}
```

---

## 作者：Prophesy_One (赞：1)

#### 题意：

给定一棵 $n$ 个点的无根树，要求给每条边分配一个正整数权值，使得任意两个叶子节点之间路径上的边权异或值 $0$。求最少和最多可以使用多少种不同权值。

这里，填入的边权值可以为任意大。

#### 分析：

首先考虑最少使用多少种权值。

当两个叶子距离为偶数时，我们可以全部使用一种权值。

若存在两个叶子距离为奇数，显然有 $1 \oplus 2=3$，故我们可以用 $1,2,3$ 拼凑出一条路径。

举个例子：

距离 $dis=3$ 时，存在 $1 \oplus 2 \oplus 3=0$；

$dis=5$ 时，存在 $1 \oplus 3 \oplus 2 \oplus 1 \oplus 1=0$；

$dis=2n+1$ 时，存在 $1 \oplus 2 \oplus 3 \oplus 1 \oplus 1 \dots \oplus 1=0$，此处后面为 $2n-2$ 个 $1$，最终结果仍为 $0$。

然后考虑最多使用多少种权值。

首先当 $k$ 个叶子的父亲为同一个时，它们到父亲的距离必须相等，即这 $k$ 条边一共对答案产生了 $1$ 的贡献。

对于其他普遍情况如何构造路径使权值种数最多呢？观看样例我们不难发现，我们可以使用 $2^0,2^1,2^2,\dots,2^n,2^{n+1}-1$ 构成一组路径，即两个父亲不同的叶子经过 $k$ 条边时，可以使用 $k$ 种权值，对答案的贡献为 $k$。

故答案 $Ans=$ 总边数 $- \sum[u$ 的所有儿子均为叶子，设共有 $num$ 个儿子 $](num-1)$。

#### 代码：
```cpp

#include<cstdio>
using namespace std;
const int N=1e5+5;
struct edge
{
	int next,to;
}e[N<<1];
int n,cnt,ans1,ans2,in[N],dep[N],ind[N],lvson[N];
bool dis[N][2];
//这里第二维0/1表示当前点与叶结点的距离为偶数/奇数 
int read()
{
	int res,f=1;
	char ch;
	while((ch=getchar())<'0'||ch>'9')
	if(ch=='-')
	f=-1;
	res=ch^48;
	while((ch=getchar())>='0'&&ch<='9')
	res=(res<<1)+(res<<3)+(ch^48);
	return res*f;
}
void add(int x,int y)
{
	e[++cnt].next=in[x];
	e[cnt].to=y;
	ind[x]++;
	in[x]=cnt;
}
void dfs(int u,int f)
{
	int i,v;
	if(ind[u]==1)
	{
		dis[u][0]=1;
		if(u==1)
		lvson[e[in[u]].to]++;
		else
		lvson[f]++;
	}
	dep[u]=dep[f]+1;
	for(i=in[u];i;i=e[i].next)
	{
		v=e[i].to;
		if(v==f)
		continue;
		dfs(v,u);
		dis[u][0]|=dis[v][1];dis[u][1]|=dis[v][0];
		if((dis[u][0]&&dis[v][0])||(dis[u][1]&&dis[v][1]))
		ans1=3;//判断是否存在两叶子距离为奇数 
	}
}
int main()
{
	int i,x,y;
	n=read();
	for(i=1;i<=n-1;i++)
	{
		x=read();y=read();
		add(x,y);add(y,x);
	}
	ans1=1;ans2=n-1;
	dfs(1,0);
	for(i=1;i<=n;i++)
	if(lvson[i])
	ans2-=lvson[i]-1;
	printf("%d %d",ans1,ans2);
	return 0;
}
```

---

## 作者：_Kenma_ (赞：0)

# CF1338B 解题报告

## 前言

聪明题。

## 思路分析

首先是二合一。

考虑对最大和最小分别进行构造。

可以钦定任意一个非叶子节点作为根，那么我们只需要保证从根节点到任何一个叶子节点的边的异或和相等就行。

### 最小值

发现如果所有叶子节点的深度奇偶性相同，可以直接把所有边都赋为 $1$。

否则，可以在每一条从根到叶子节点的边依次赋值为 $1,2,1,2,\cdots$，每条在叶子节点正上方的边赋值为 $2$ 或 $3$。这样可以用 $3$ 种权值解决。

### 最大值

比最小值困难一些。

考虑因为权值是正无穷，所以除了一定相等的边，其他的边权一定可以不相同。

不难发现，如果两个叶子节点有相同的父亲，那么它们正上方的边，边权一定相等。否则，它们的边权一定可以不相等。

然后做完了。

总体复杂度为 $O(n)$。

## 代码实现

```cpp

#include<bits/stdc++.h>
using namespace std;
int n,x,y,rt,ans;
int head[200005],nxt[400005],target[400005],tot;
void add(int x,int y){
	tot++;
	nxt[tot]=head[x];
	head[x]=tot;
	target[tot]=y;
} 
int dep[200005],f[200005],cnt[200005];
bool vis[200005],flag1,flag2;
void dfs(int x,int fa){
	for(int i=head[x];i;i=nxt[i]){
		int y=target[i];
		if(y==fa) continue;
		dep[y]=dep[x]+1;
		f[y]=x;
		dfs(y,x);
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>x>>y;
		add(x,y);
		add(y,x);
		cnt[x]++;
		cnt[y]++;
	}
	for(int i=1;i<=n;i++){
		if(cnt[i]!=1) rt=i;
	}
	dfs(rt,0);
	ans=n-1;
	for(int i=1;i<=n;i++){
		if(cnt[i]==1){
			if(dep[i]&1) flag1=true;
		    else flag2=true;
		}
	}
	for(int i=1;i<=n;i++){
		if(cnt[i]==1){
			if(vis[f[i]]) ans--;
			vis[f[i]]=1;
		}
	}
	if(flag1 && flag2) cout<<3<<' ';
	else cout<<1<<' ';
	cout<<ans;
	return 0;
}

```

没什么细节。

---

## 作者：Kketchup (赞：0)

## CF1338B Edge Weight Assignment 题解

[题目传送门](https://codeforces.com/problemset/problem/1338/B)

突然发现的题，感觉有点意思，写写博客总结一下。

### 【题目描述】

给定一棵 $n$ 个点的无根树，要求给每条边分配一个**正整数**权值（可以任意大），使得任意两个叶子节点之间路径上的边权异或值为 $0$。求最少要多少种不同权值，以及最多可以使用多少种不同权值。$n\le 10^5$。

### 【题目解析】

下面分成两问探讨。

#### Question #1

我们要让所用权值最少，首先想到的是 $x\oplus x=0$。我们发现，若两个叶节点 $u,v$ 满足路径上边数是偶数，那么就可以只用一种权值让异或为 $0$。

那么我们想想边数为奇数的情况。因为 $2$ 个不同的权值异或后一定不为 $0$，所以考虑 $3$ 个，发现可行。即一定存在全不相等的 $a,b,c$ 使得 $a\oplus b\oplus c=0$，这一点很好理解。那么就可以把路径变为 $x+3$ 的形式，前面的 $x$ 是非负偶数，可以用一种权值铺满。

所以我们可以对于每个叶子计算到根路径长度奇偶性，偶数用一种权值，奇数变成 $x+3$ 的形式。因为两个叶子 $u,v$ 路径在 $\operatorname{LCA}$ 处汇合，所以直接用到根路径异或上对答案没有影响。

所以我们证明了：**如果叶子之间路径长度全是偶数，答案为 $1$，否则为 $3$。**

#### Question #2

想想最多怎么做。容易发现的是，一个点的儿子中是叶子的儿子到这个点的那条边权值一定全都相等，这样它们两两之间才满足条件。而那些中间的边可以任意赋值，反正一定可以通过构造使异或和为 $0$。

也就是对于一个点 $u$，答案要减掉其**叶子儿子个数减一**。

---

注意，因为无根树条件，要选择一个度数大于 $1$ 的点作为根。时空复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,ans;
int d[N];
bool leaf[N],st[2];
vector<int> e[N];
int dfs(int u,int fa){
    d[u]=d[fa]+1;
    if(e[u].size()==1){
        leaf[u]=1;
        return 1;
    }
    int res=0;
    for(int v:e[u]){
        if(v==fa) continue;
        res+=dfs(v,u);
    }
    ans-=max(0,res-1);
    return 0;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    ans=n-1;
    for(int i=1,x,y;i<n;++i){
        cin>>x>>y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    int root=-1;
    for(int i=1;i<=n,root==-1;++i) if(e[i].size()!=1) root=i;
    dfs(root,0);
    for(int i=1;i<=n;++i) if(leaf[i]) st[d[i]&1]=1;
    if(st[0]&&st[1]) cout<<3<<' ';
    else cout<<1<<' ';
    cout<<ans<<endl;
    return 0;
}
```

完结撒花！希望读到这里的朋友们都有收获。

---

## 作者：Libra_ (赞：0)

比较好玩且不难（~~所以来水个题解~~）。

## 题目：[CF1338B](https://www.luogu.com.cn/problem/CF1338B)

给一颗树的边赋值，使得任意两叶子节点间路径的异或和为 $0$。

## 分析:

1. 对于最小的不同权值数：

如果两叶子节点间的路径长度为偶数，那么全放同一个数即可；如果是奇数，（经过观察与思考发现）最少需要三种数。

2. 对于最大的不同权值数：

因为：
> Note that you can put very large positive integers (like $10^{10^{10}}$).

所以数可以随便选。

则对于一条长度不小于 $3$ 的路径，我们必然可以选一些不同的数，使它的异或和为 $0$。对于长度为 $2$ 的路径，我们必须放两个一样的数。

## 代码：

* 对于找两叶子节点的路径，一般的思路是找 LCA，但由于本题我们只需要知道奇偶性，所以我们只用判断两叶子节点到根节点距离之和的奇偶性即可。（两叶子节点的 LCA 到根节点的距离算了两次，不影响奇偶性）

### [我的代码](https://www.luogu.com.cn/paste/05fgb7ax)



---

## 作者：double_wings (赞：0)

## 题意
任意两个叶子节点直接的路径异或值为 $0$，让你构造一种方案，给每条边赋值，问最少需要几种权值，最多可以有几种权值。
## 分析
对于最小值的情况，如果任意两点的路径边数都为偶数，我们可以通过把每条边赋为同一个值使得符合题意，如果有一条路径的边数为奇数，我们则需要用三种不同的权值使得异或值为 $0$（手玩一下就能推出来），考虑随便定一个度数不为 $1$ 的点为根，然后遍历整棵树求出每个叶子节点的深度，如果深度同为奇数或者同为偶数，答案为 $1$，反之为 $3$。

对于最大值的情况，我们可以让所有度数不为 $1$ 的点之间的边权值不同，对于一个节点的子节点有多个都是叶子节点，这些叶子节点直接的与父亲连边的权值必须相同，因为这部分叶子节点两两之间只有两条边，所以权值必须一样，然后给随便一个叶子节点与父亲之间的边赋值，其他的叶子节点与父亲节点的边的权值也就固定了，答案就是度数不为 $1$ 的节点减一加上度数不为 $1$ 的节点的子节点是叶子节点的个数。然后考虑正确性，想象一下三个节点的 LCA 为同一个节点，那么这三个叶子节点到 LCA 的异或值都相等，所以通过固定一个节点求出另外两个节点，另外两个节点之间的路径异或值也为 $0$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
//#define mid ((l+r)>>1)
//#define len (r-l+1)
//#define rs p<<1|1
//#define ls p<<1
//#define int long long
constexpr int inf=1e9+7;
constexpr int mod=998244353;
//constexpr ll inf=1e18+7;
constexpr int N=100005;
int n;
int d[N];
bool vis[N];
int dep[N];
int tot,head[N];
struct node
{
    int to,nxt;
}e[N<<1];

void add(int u,int v)
{
    e[++tot].to=v;
    e[tot].nxt=head[u];
    head[u]=tot;
}

void dfs(int x,int f)
{
    dep[x]=dep[f]+1;
    for(int i=head[x];i;i=e[i].nxt)
    {
        int v=e[i].to;
        if(v==f)continue;
        dfs(v,x);
    }
}

// char buf[1<<21],*p1,*p2;
// #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();return x*f;}
void wt(long long x,char ch=0){if(x<0) putchar('-'),wt(-x);else{if(x>=10) wt(x/10);putchar(x%10+'0');}if(ch) putchar(ch);return;}
signed main(){
    //freopen("in.in","r",stdin);
    //freopen("ot.out","w",stdout);
    cin.tie(0);
    cout.tie(0);
    //最小值是1或者3  显然
    //最大值对于三叉的 由一个叶子节点可以确定另外两个
    //这三个叶子节点到LCA都是一样的
    n=read();
    for(int i=1;i<n;++i)
    {
        int u=read(),v=read();
        add(u,v);
        add(v,u);
        d[u]++;
        d[v]++;
    }
    for(int i=1;i<=n;++i)
    {
        if(d[i]!=1)
        {
            dfs(i,0);
            break;
        }
    }
    int biao=-1;
    int b=0;
    for(int i=1;i<=n;++i)
    {
        if(d[i]==1)
        {
            if(!~biao)
            {
                if(dep[i]&1)
                {
                    biao=1;
                }
                else biao=0;
                continue;
            }
            if(biao)
            {
                if(!(dep[i]&1))
                {
                    wt(3,' ');
                    b=1;
                    break;
                }
            }
            else 
            {
                if(dep[i]&1)
                {
                    wt(3,' ');
                    b=1;
                    break;
                }
            }
        }
    }
    if(!b)wt(1,' ');
    int ans=0;
    for(int i=1;i<=n;++i)
    {
        if(d[i]!=1)
        {
            ans++;
            for(int j=head[i];j;j=e[j].nxt)
            {
                int v=e[j].to;
                if(d[v]==1)
                {
                    ans++;
                    break;
                }
            }
        }
    }
    wt(ans-1);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
```

---

## 作者：ZZZZZZZF (赞：0)

### 思路：
推结论

1. 最小值只能是 $1$ 或 $3$。
2. 最大值为同一父节点的叶节点合并后的边数。

感觉带 xor 的题都要推些小结论。

#### 结论 $1$:

显然，当任意叶节点间距离均为偶数时可以给所有边赋相同的值，即最少情况数为 $1$ 种。

当出现距离为奇数的叶节点对时，考虑将两条边的权值合并。

例：

```cpp
//偶数情况:
1 ^ 1 ^ 1 ^ 1 ^ 1 ^ 1 = 0

//奇数情况把中间两个 1 合并为一个数
1 ^ 1 ^ 11 ^ 10 ^ 10 = 0

```
可以发现，每次首尾各补一个  $1$ 和 $10$ 即可覆盖所有奇数情况。

这就解释了为什么用 $123$ 可以满足所有情况。

至此，$1$ 种和 $3$ 种是可行的。

既然是求最少情况数，那 $2$ 种行不行呢？

要使异或和为 $0$，每一位上都要有偶数个 $1$，设 $ab$ 为要填入的数，因为总边数为奇，所以 $ab$ 的数量奇偶性必然相反，那么异或之后就会剩下单个 $a$ 或者 $b$ 无法消掉。

#### 结论 $2$：

考虑没有任何限制的情况，最多种类数与边数相等。

显然，多个父节点相同的叶子节点之间只有两条边，所以边权应该相同，要在结果中扣掉重叶子的贡献。

而距离更远的两个叶子间可以构造出完全不同的值满足异或和为 $0$。

### Code：
```cpp
#include<bits/stdc++.h>
#define N 100010

int tt,n,m,r,f1,f0,minAns,maxAns;

//eNum 出边数量  jP是否距离根距离为奇
int head[N],eNum[N],jP[N],vis[N];

struct edge{
    int v,next;
}e[N*2];

void add(int u,int v){
    e[++tt].next = head[u];
    e[tt].v = v;
    head[u] = tt;
    return;
}

void dfs(int num,int cnt){
    vis[num] = 1;
    if(eNum[num] == 1){
        if(cnt%2 == 1)
            jP[num] = 1,f1 = 1;
        else
            jP[num] = 0,f0 = 1;
    }
    for(int i = head[num];i;i = e[i].next){
        int v = e[i].v;
        if(!vis[v])
            dfs(v,cnt+1);
    }
    return;
}

int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++)
        jP[i] = -1;
    
    m = n-1;
    for(int i = 1,u,v;i<=m;i++){
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
        eNum[u]++;
        eNum[v]++;
    }

    for(int i = 1;i<=n;i++)
        if(eNum[i]!=1){
            r = i;
            break;
        }
    
    dfs(r,0);

		//如果全为奇点可以通过换根转化为偶点
    if(f1 == 1 && f0 ==1) minAns = 3;
    else minAns = 1;

    int edgeNum = m;
    for(int u = 1,cnt = 0;u<=n;u++,cnt = 0){

        for(int i = head[u];i;i = e[i].next)
            if(eNum[e[i].v] == 1)//统计叶子节点数量
                cnt++;
        
        if(cnt>=2)
            edgeNum-=(cnt-1);

    }

    maxAns = edgeNum;
    printf("%d %d",minAns,maxAns);

    return 0;
}
```

---

## 作者：NaN_HQJ2007_NaN (赞：0)

小清新思维题。

先找一个不是叶子的节点，令它为根。

那么当且仅当，对于每一个非叶子节点，它包含的叶子节点到它的异或路径相等时，才满足题目要求。

考虑第一问，显然如果每个叶子的深度奇偶性相同，可以全填一样的数字，答案为 $1$。反之为 $3$（可以在一条链上试一试）。

对于第二问，定义 $f_i$ 表示子树 $i$ 最多能填多少种边权，转移方程如下。

$$f_{i}=\left(\sum\limits_{j\in \operatorname{son}(i)\land j\notin leaves}f_j+1\right)+[\exists j\in\operatorname{son}(i),j\in leaves]$$

简单理解就是，如果儿子中有叶子，那么每个叶子所连边的权值相等，其他的随便填。

复杂度 $O(n)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,dep[N],f[N],lv[N];
vector<int>adj[N];
void dfs(int u,int lst){
  dep[u]=dep[lst]+1;
  if(lv[u])return;
  bool fg=0;
  for(int i=0;i<adj[u].size();++i){
    int v=adj[u][i];if(v==lst)continue;
    dfs(v,u);
    if(lv[v])fg=1;
    else f[u]+=f[v]+1;
  }
  f[u]+=fg;
}
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n;
  for(int i=1;i<n;++i){
    int u,v;cin>>u>>v;
    adj[u].push_back(v);adj[v].push_back(u);
  }
  int rt;
  for(int i=1;i<=n;++i){
    if(adj[i].size()==1)lv[i]=1;
    else rt=i;
  }
  dep[0]=-1;
  dfs(rt,0);
  int cnt=0,cnt2=0;
  for(int i=1;i<=n;++i){
    if(adj[i].size()>1)continue;
    if(dep[i]&1)++cnt;
    else ++cnt2;
  }
  if(cnt&&cnt2)cout<<3<<" ";
  else cout<<1<<" ";
  cout<<f[rt]<<endl;
  return 0;
}

```


---

## 作者：devout (赞：0)

这题作为一个猜结论的题还是挺好的（大雾

先考虑最大值

观察3个样例的解释我们可以发现，对于任意两个叶子节点，如果他们的父亲节点相同，那么这两个点和他们的父亲的边权必须相同，因为两条边想异或成$0$必须相同

然后我们大胆的猜测其他的都不用管，每条边权值都不同，~~手玩之后发现确实是这样所以他是对的~~

大概原因就是因为数可以无限大...

考虑最小值~~感觉最小值更简单~~

观察样例$1,3$，为什么最小值是$1$呢？

因为任意两个叶子节点之间不存在一条边数为奇数的路径，而偶数个$1$异或起来一定是$0$，也就是说，如果任意两个叶子节点之间没有奇数长度的路径，我们一定可以只用$1$让他满足条件

观察样例$2$，最小是是$3$

因为两个叶子节点之间存在奇数长度的路径，我们需要把它拆分成$2k+1$条边，我们让每两条相邻的边异或的结果是$1$，选出这样的$2k$条边，最后异或下来是$1$,然后$1$和$1$异或下来就是$0$了，也就是说我们需要把边拆成$1-2-3-2-3$这样的。

构造方法也很简单，让根（深度为$1$）和深度为$2$的点之间的边是$1$，剩下的$2,3$交错就可以了

也就是说，如果存在奇数长度路径，我们一定可以只用$1,2,3$让他满足条件

考虑实现，对于最小值只需要判断是否存在奇数长度路径，我们可以先任意选一个不是叶子节点的节点当根，然后如果每个叶子节点的深度的奇偶性都相同，那么就没有奇数长度路径，输出$1$，否则输出$3$

最大值可以使用一个非常好想的树形$dp$来实现

我们可以用$dp_u$表示以$u$为根节点的子树中，最多能有多少不同的权值，那么转移方程就是

$$dp_u=\sum_{v}^{v\in son(u),v\  is\ not\ leaf} dp_v+1 $$


然后如果$u$的儿子中有叶子节点，需要$dp_u+1$

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=1e5+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n,rt;
int head[N],cnt;
int dep[N],f[N],du[N];
bool isleaf[N],visodd,viseven;

struct Edge{
    int to,next;
}e[N<<1];

void add(int x,int y){
    e[++cnt]=(Edge){y,head[x]},head[x]=cnt;
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    int lfcnt=0;
    RepG(i,u){
        int v=e[i].to;
        if(v==fa)continue;
        if(isleaf[v]){lfcnt++,dep[v]=dep[u]+1;continue;}
        dfs(v,u);
        f[u]+=f[v]+1;
    }
    if(lfcnt)f[u]++;
}

int main()
{
    memset(head,-1,sizeof(head));
    read(n);
    Rep(i,1,n-1){
        int x,y;
        read(x),read(y);
        add(x,y),add(y,x);
        du[x]++,du[y]++;
    }
    Rep(i,1,n)if(du[i]>1){rt=i;break;}
    Rep(i,1,n)if(du[i]==1)isleaf[i]=true;
    dfs(rt,0);
    Rep(i,1,n)
        if(isleaf[i]){
            if(dep[i]&1)visodd=true;
            else viseven=true;
        }
    if(visodd&&viseven)printf("3 ");
    else printf("1 ");
    printf("%d\n",f[rt]);
    return 0;
}
```


---

