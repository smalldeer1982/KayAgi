# [USACO10DEC] Cow Calisthenics G

## 题目描述

Farmer John 为了保持奶牛们的健康，让可怜的奶牛们不停在牧场之间的小路上奔跑。这些奶牛的路径集合可以被表示成一个点集和一些连接两个顶点的双向路，使得每对点之间恰好有一条简单路径。简单的说来， 这些点的布局就是一棵树，且每条边等长，都为 $1$。

对于给定的一个奶牛路径集合，精明的奶牛们会计算出任意点对路径的最大值， 我们称之为这个路径集合的直径。如果直径太大，奶牛们就会拒绝锻炼。

Farmer John 把每个点标记为 $1\cdots V(2\le V\le 10^5)$。为了获得更加短的直径，他可以选择封锁一些已经存在的道路，这样就可以得到更多的路径集合， 从而减小一些路径集合的直径。我们从一棵树开始，Farmer John 可以选择封锁 $S(1\le S\le V-1)$ 条双向路，从而获得 $S+1$个路径集合。

你要做的是计算出最佳的封锁方案，使得他得到的所有路径集合直径的最大值尽可能小。Farmer John 告诉你所有 $V-1$ 条双向道路，每条表述为：顶点 $A_i(1\le A_i\le V)$ 和 $B_i(1\le B_i\le V,A_i\ne B_i)$ 连接。

## 说明/提示

Consider this rather linear cowpath set (a tree with 7 vertices):

1---2---3---4---5---6---7

If FJ can block two paths, he might choose them to make a map like this:

1---2 | 3---4 | 5---6---7 where the longest pathlength is 2, which would be the answer in this case. He can do no better than this.

## 样例 #1

### 输入

```
7 2 
6 7 
3 4 
6 5 
1 2 
3 2 
4 5 
```

### 输出

```
2 
```

# 题解

## 作者：珅肐 (赞：6)

提供简洁的代码

"目前吸氧最优解"

这道题目总体不难

简单题意：将树中的某些边删去后，使各个连通块中最大直径最小

诶，"最大直径最小"，这不是二分吗

于是我们想到，二分直径的最大长度，显然，由于答案合法的单调性，正确性是可以保证的

那么该如何判断是否可以满足呢？

我们设$f[x]$表示"从$x$出发的在$x$子树中路径的最大长度"

如果"$f[x]$"加上"$max(f[to])$"大于我们二分的长度，我们就断边。
（$max(f[to]$中除去$f[x]$所到的那个$f[to]$，即最大的两个$f[to]$之和大于二分长度，下文皆是此意）

断哪条？

贪心的想，因为"断边后被断的边再也不会产生影响"，所以我们只需要让留下来的边尽可能的小，就留下$min(f[x]-1,f[to])+1$。

$min(f[x]-1,f[to])$表示儿子的最大路径长度，$+1$表示加上儿子到父亲的边。

判断的正确性：

因为我们从下往上断边，而且是非断不可时才断，又能保证断边时一定留下最优解，所以判断是正确的。

### 完整代码奉上:
```cpp
#include<iostream>
#include<cstdio>
#include<ctype.h>
using namespace std;
inline int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch))f|=ch=='-',ch=getchar();
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?-x:x;
}
struct Edge{
	int next,to;
}edge[200007];
int head[100007],cnt;
int f[100007];
inline void add_edge(int from,int to){
	edge[++cnt].next=head[from];
	edge[cnt].to=to;head[from]=cnt;
}
int t,n,s;//t表示当前删边的个数
void dfs(int x,int fa,int maxl){
	if(t>s)return;//t>s说明不能完成
	int lx=0;//lx表示最大f[to]
	for(int i=head[x];i;i=edge[i].next){
		int to=edge[i].to;if(to==fa)continue;
		dfs(to,x,maxl);
		if(lx+f[to]>maxl)++t,lx=min(lx,f[to]);//如果需要删边，就保留最小值
		else lx=max(lx,f[to]);//否则就更新为最大值
	}
	f[x]=lx+1;
}
inline bool check(int maxl){
	t=0;dfs(1,0,maxl);//注意清空计数器t
	return t<=s;
}
int main(){
	n=read(),s=read();
	for(int i=1;i<n;++i){
		int u=read(),v=read();
		add_edge(u,v),add_edge(v,u);
	}//以上为读入建图
	int l=0,r=n/s;//二分下界显然是0，上界其实只要到(n-s)/s向上取正（已经删去了s条边）。
	while(l<=r){//普通二分
		int mid=l+r>>1;
		if(check(mid))r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",l);//输出答案
	return 0;//好习惯
}
```
对了，最后说一下二分
```cpp
if(check(mid))r=mid-1;
else l=mid+1;
```
很多人一直对此有疑惑

一般有三种，最常见的好像是$if(check(mid))$后记录一下$ans$

这里证明一下我习惯写的

$if(check(mid))$后$r$会$-1$，所以$r$不一定是最终答案

相反，因为在$check$不成立后$l$会$+1$，到最后的极限$l=r$时答案就是正确的


---

## 作者：YitsuHolo (赞：6)

## 为什么没有C++的题解

不如自己写一篇吧

题目中已经说了，要求满足最大值最小，那么很明显是二分，这里就不做过多解释

但是二分完后如何验证

因为需要求的是树的直径，直接记录深度肯定有有问题

既然这样，我们就记录当前点到叶子节点距离的最大值和一个次大值，如果最大+次大 > 那么我们就剪掉最大的边，剪边的次数 +1 ，然后检查是否合理，调整二分区间

### 注意，上面的只是思路，如果你这么做，会变得十分麻烦

简化方法：

dfs的时候和下一层的各个节点的比较一下，如果已经不满足了，就直接将较大的剪掉，保留较小的，如果满足，当前的距离更新为较大的

贴上最优解代码：

```cpp
//请用c++11运行
#pragma GCC optimize (3)
#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("inline")
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAX=400005;
struct node
{
	int to,next;
};
int head[MAX];
node edge[MAX*2];
int len[MAX];
int k,cnt,mid,K;

inline int cmin(int x,int y) { return x<y?x:y; }
inline int cmax(int x,int y) { return x>y?x:y; }

template <typename T = int>
inline void add(T come,T to)
{
	edge[++K]=(node){to,head[come]};
	head[come]=K;
}

template <typename T = int>
inline int read()
{
	register T X=0;
	register char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') X=(X<<3)+(X<<1)+c-'0',c=getchar();
	return X;
}

void dfs(int u,int fa)
{
	if(cnt>k) return ;
	register int now=0;
	for(register int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v==fa)	continue;
		dfs(v,u);
		if(now+len[v]>mid)
		{
			cnt++;	//保留较小的距离
			now=cmin(now,len[v]);
		}
		else
			now=cmax(now,len[v]);	//更新最大值
	}
    //当然要加上自己
	len[u]=now+1;
}

bool check()
{
	cnt=0;
	dfs(1,0);
	return cnt<=k;
}

int main()
{
	register int n,ans;
	scanf("%d%d",&n,&k);
	register int x,y;
	for(register int i=1;i<n;i++)
	{
		x=read();y=read();
		add(x,y);	add(y,x);
	}
	
	register int l=0,r=n/k+10;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check())
		{
			ans=mid;
			r=mid-1;
		}
		else
			l=mid+1;
	}
	printf("%d",ans);
	return 0;
}
```

好像最优解基本全是我们机房的？？？

---

## 作者：Beginner_df016 (赞：4)

简单抽象一下题意就是

去掉n个结点的树上最多m条边，使得剩下的所有路径中最长值最小，求这个最小值。

以这样的问法出现，我们可以考虑二分答案法。

如果使最小值为x的方案存在，则使最小值为x+1的方案必然存在。

不存在同理。

所以很明显这题是具有二分性的。


然后就是如何判断方案的存在性 这里用到树形DP和贪心。

f[u]记录以u为深度最小点的链长度

也就是u到 以u为根的子树中 离它最远的叶子节点的路径长度


遍历过u为根的整棵子树之后，用a数组记录一下u每个的子结点的f[v]

对a从大到小排序，如果两条链长度和大于mid，则将长的一条截断

处理后新得到的最长值也就是f[u]的值

另外，由于dfs序遍历的括号化定理，

当我们处理u为根的子树的时候，已经保证其子结点为根的子树路径长符合要求。


奶牛们多好啊...

一路星移物换，我们没有散....





```cpp
End.
{Beginner_df016}
var i,j,k,n,m,x,y,s,tot,anst,l,r,mid,ans:longint;
      b,head,next:array[0..200007]of longint;
      a,f:array[0..100007]of longint;
procedure add(x,y:longint);
begin
    inc(tot);
    b[tot]:=y;
    next[tot]:=head[x];
    head[x]:=tot;
end;
 procedure qsort(l,r:longint);
 var i,j,m,t:longint;
begin
    i:=l; j:=r;
    m:=a[(l+r) div 2];
    repeat
        while a[i]>m do inc(i);
        while m>a[j] do dec(j);
        if not(i>j) then
           begin t:=a[i]; a[i]:=a[j]; a[j]:=t;
                    inc(i); dec(j); end;
    until i>j;
    if l<j then qsort(l,j);
    if i<r then qsort(i,r);
end;
procedure dfs(u,fa:longint);
var i,v,num:longint;  p:boolean;
begin
    f[u]:=0; p:=false;
    i:=head[u];
    while i<>0 do
        begin
        v:=b[i];
        if v<>fa then
           begin
           p:=true;
           dfs(v,u);
           if f[v]+1>f[u] then f[u]:=f[v]+1;
           end;
        i:=next[i];
        end;
    if not p then begin f[u]:=0; exit; end;
    num:=0;
    i:=head[u];
    while i<>0 do
        begin
        v:=b[i];
        if v<>fa then begin inc(num); a[num]:=f[v]+1; end;
        i:=next[i];
        end;
    qsort(1,num);
        a[num+1]:=0;
    for i:=1 to num do
      if a[i]+a[i+1]>mid then begin inc(anst); a[i]:=0; end;
    qsort(1,num);
    f[u]:=a[1];
end;
function check:boolean;
begin
    anst:=0;
    dfs(1,0);
    if anst>m then exit(false);
    exit(true);
end;
begin
    readln(n,m);
    for i:=1 to n-1 do
       begin
       readln(x,y);
       add(x,y);
       add(y,x);
       end;
    l:=1; r:=n;
    while l<=r do
        begin
        mid:=(l+r)>>1;
        if check then begin ans:=mid; r:=mid-1; end
                      else l:=mid+1;
        end;
    writeln(ans);
end.
```

---

## 作者：VioletIsMyLove (赞：2)

两种方法，一种是从根到儿子，只要求出树的直径，之后每次枚举直径上的点做根节点，刷到叶节点的最短路，每次把最远的去掉就可以了。

还有一种是从叶节点归到根节点，叶节点就是度数为1的节点，其他跟上面一样。

主要见代码，代码~~简单易懂~~。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=100005;
int n,m,cnt,mid,tot,dis[MAXN],F[MAXN],son[2*MAXN],lnk[MAXN],nxt[2*MAXN];
int read(){
	int ret=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-')f=-f;ch=getchar();}
	while (isdigit(ch)) ret=(ret<<3)+(ret<<1)+ch-'0',ch=getchar();
	return ret*f;
}
void add_e(int x,int y){son[++tot]=y;nxt[tot]=lnk[x];lnk[x]=tot;}
void DFS(int x,int fa) {
    for (int j=lnk[x];j;j=nxt[j])
      if (son[j]!=fa) DFS(son[j],x);
    int top=0;F[x]=1;
    for (int j=lnk[x];j;j=nxt[j]) 
      if (son[j]!=fa) dis[++top]=F[son[j]];
    sort(dis+1,dis+1+top);
    for (int i=top;i;i--)
      if (dis[i]+dis[i-1]>mid) cnt++;else {F[x]+=dis[i];break;}
}
bool check(){
    cnt=0;
    DFS(1,0);
    return cnt<=m;
}
int main(){
    n=read(),m=read();
    for (int i=1;i<n;i++) {
        int x=read(),y=read();
        add_e(x,y),add_e(y,x);
    }
    int L=0,R=n-1;
    while (L<=R){
    	mid=(R-L>>1)+L;
        if (check()) R=mid-1;else L=mid+1;
    }
    printf("%d\n",L);
    return 0;
}
```


---

## 作者：chlchl (赞：1)

今天模拟赛第三题，实际上整体还是有难度的，但是题目中会有提示。

## Solution
最大直径最小，显然想到**二分答案**。这是本题最大的突破口。

说说为什么想到二分答案吧。除了这个标准“最大值最小化”之外，还有一个重要的原因：直接树形 DP 无法解决问题，因为**无法动态维护和快速算出删除一条边之后两边的直径**。

二分答案的好处是，我们只需要解决如何检验的问题。此时其实已知的信息会多一个，就是这个最大直径的值。我们的检验可以在**满足以 $x$ 作为最大直径的情况下**，是否可以通过删不超过 $s$ 条边得到。

那么，如何检验 $x$ 是否可以作为最大直径呢？

直径有关问题，想到用一个 $f_u$ 表示在 $u$ 的子树中，从 $u$ 开始向下可以走的最大长度。

那么其实过 $u$ 的最长路径就是两个最大的 $f_v$ 相加再 $+1$（$v$ 是 $u$ 的儿子）。

我们遍历 $u$ 的儿子 $v$ 时，维护一个变量 $mx$ 表示当前除 $v$ 之外已知的 $\max\{f_v+1\}$（因为要加上 $u\rightarrow v$ 那条边）。

那么，当 $f_v+mx>x$ 时，我们就需要删掉一条边了。

删哪条边呢？

显然删的一定是 $u$ 和它其中一个儿子（$mx$ 那个或者 $v$） 的连边，这样可以使 $u$ 的 $mx$ 变得最小。因为 DP 的无后效性，我们只需要考虑当前 $u$ 的情况而不需要考虑删边对它儿子的影响（实际上也没有影响）。

因为对后代无影响，我们贪心地删掉 $\max(mx,f_v)$ 那一侧的那条边，那么 $mx\leftarrow\min(mx,f_v)$。

最后把 $f_u$ 求出来（$=mx$）。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, s, tot, f[N];
int id, head[N << 1], to[N << 1], nxt[N << 1];

void add(int u, int v){
	to[++id] = v;
	nxt[id] = head[u], head[u] = id;
}

void dfs(int u, int fa, int lim){
	int mx = 0;
	for(int i=head[u];i;i=nxt[i]){
		int v = to[i];
		if(v == fa)
			continue;
		dfs(v, u, lim);
		if(f[v] + mx + 1 > lim)
			++tot, mx = min(mx, f[v] + 1);//贪心删边，mx 会等于这两个分支中较小的那个  
		else
			mx = max(mx, f[v] + 1);//注意我 mx 存的是 max(f[v]+1)，这样最后赋值的时候直接就是 =mx
	}
	f[u] = mx; 
}

bool check(int x){
	memset(f, 0, sizeof(f));
	tot = 0;
	dfs(1, 1, x);
	return tot <= s;//断边数量是否小于规定数量 
}

int main(){
	scanf("%d%d", &n, &s);
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	int l = 0, r = n, ans = n;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(check(mid))
			ans = mid, r = mid - 1;
		else
			l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：青鸟_Blue_Bird (赞：1)

二分 + $dp$ 的好题。

首先，要求最大直径最小，我们肯定会想到二分最大直径。 难点就在于怎么 $check$。由于正确性过于显然，二分可行性证明就略了吧。

记录数组 $dp_u$ 表示在 $u$ 号点，其子树中所有点到达 $u$ 号点的最大链长。转移时，考虑其和子树之间的关系。

可以发现，$u$ 号点就类似于一个 $lca$，两个最长的儿子拼起来的最长链就是这棵子树的最大直径。注意，这里的 $dp_v$ 中所存最长链均已保证子树内部合法。

接着考虑子树中直径超过二分的上限怎么办？贪心地想，我们肯定是要断掉最长的那条链，保留次长的。因为这样可以使得我们的总长度尽可能小，从而达到最优次数。
最后，如果必须断边的次数大于上限 $s$, 则不合格，应该调大区间，否则**一定合格**。想一想为什么。（~~题目中不是要求我们断掉 $s$ 条边吗~~）

具体实现看代码： 

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 1000010
const int inf = 2e9; 

template <class T>
inline void read(T& a){
    T x = 0, s = 1;
    char c = getchar();
    while(!isdigit(c)){ if(c == '-') s = -1; c = getchar(); }
    while(isdigit(c)){ x = x * 10 + (c ^ '0'); c = getchar(); }
    a = x * s;
    return ; 
}

struct node{
    int v, next;
} t[N << 1];
int f[N];

int bian = 0;
inline void add(int u, int v){
    t[++bian] = (node){v, f[u]}, f[u] = bian;
    return ; 
}

int n, s;
int dp[N];
int sum = 0;   // 断了多少次 

void dfs(int now, int father, int lim){
    int maxn = 0, minn = inf; 
    for(int i = f[now]; i; i = t[i].next){
        int v = t[i].v;
        if(v == father) continue; 
        dfs(v, now, lim); 
        if(dp[v] + maxn > lim) sum++, maxn = min(maxn, dp[v]);   // 保留最小值
        else maxn = max(maxn, dp[v]);     // 否则更新成最大值
    }
    dp[now] = maxn + 1; 
    return ; 
}

bool check(int lim){
    sum = 0;   // 记得清空 
    dfs(1, 0, lim);
    return sum <= s; 
}

int main(){
    read(n); read(s); 
    for(int i = 1; i < n; i++){
        int x, y;
        read(x), read(y);
        add(x, y); add(y, x); 
    }
    int l = 1, r = n, ans = 0;   // 最多断 n 次 
    while(l <= r){
        int mid = l + r >> 1;
        if(check(mid)) ans = mid, r = mid - 1;
        else l = mid + 1; 
    }
    cout << ans << endl;
    return 0; 
}
```

---

## 作者：jjy2023 (赞：0)

# P3000 [USACO10DEC] Cow Calisthenics G
## Solution：
因为要求最大值，可以通过二分答案来寻找最大值。枚举断掉若干条边后的直径 $mid$，可通过 `dfs` 来求出每个点的直径，枚举断掉 $i$ 条边时的直径是否 $\le mid$ 且此时断掉的边数 $i$ 是否 $\le s$。若满足条件，说明可断掉此点，反之不行。最终输出结果即可。
## Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ans,a[200005],f[200005],cnt=0;
vector<int> v[200005];
void dfs(int num,int now,int fa)
{
	f[now]=0;
	for(int i=0;i<v[now].size();i++)
	{
		if(v[now][i]!=fa) dfs(num,v[now][i],now);
	}
	cnt=0;
	for(int i=0;i<v[now].size();i++)
	{
		if(v[now][i]!=fa) a[++cnt]=f[v[now][i]]+1;
	}
	sort(a+1,a+cnt+1);
	while(cnt>0&&a[cnt]+a[cnt-1]>num) cnt--,ans++;
	f[now]=a[cnt];
}
bool check(int x)
{
	ans=0;
	dfs(x,1,0);
	//cout<<"mid="<<x<<' '<<ans<<' '<<m<<'\n';
	if(ans<=m) return true;
	else return false;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n-1;i++)
	{
		int x,y;
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	int l=1,r=n,tot=n;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(mid)==true) tot=mid,r=mid-1;
		else l=mid+1;
		//cout<<tot<<'\n';
	}
	cout<<tot;
	return 0;	
}
```

---

## 作者：bugaile (赞：0)

题目大意$:$

给你一棵树,你可以在树中删去$s$条使之成为森林,求如何删,能使森林中最大的直径最小.

题面中,二分的特征比较明显,比较容易就可以想到如下方案:

每次二分一个最大直径$mid$,求在删$s$条边的情况下是否可以使之在大直径为$mid$.

关键在于如何$check$.

我们可以贪心的去考虑,对于没一个节点,记录一个$maxdepth$表示该节点向子树方向延伸的最大深度.

对于当前遍历到的节点$u$,我们将其子节点遍历完后,可以将其子节点放入一个容器中,这个容器可以快速查找最大值.

然后每次将最大的两个$v_1,v_2$的$maxdepth$求出两个点的距离,如果大于二分值,就将$maxdepth$更大的那个点与$u$的边删去.

这个可以用一个二叉堆维护,时间复杂度为$O(Nlog^2N)$,算上界这个题没问题,但如果用优先队列不吸氧过不去,这里不得不吐槽一下$STL$常数大...

```cpp
//O(Nlog^2N),吸氧可以过;
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e5+10;

int s,n,now,cnt,maxdepth[N],depth[N];

int to[N<<1],nex[N<<1],head[N],tt;

inline void add(int x,int y){
	to[++tt]=y,nex[tt]=head[x],head[x]=tt;
	return ;
}

priority_queue<int>Q;

bool dfs(int g,int f){
	priority_queue<int>Q;
	maxdepth[g]=depth[g];
	for(int i=head[g],u;i;i=nex[i]){
		u=to[i];
		if(u==f)
			continue;
		depth[u]=depth[g]+1;
		if(!dfs(u,g))
			return false;//有一个子树不行就整个不行;
		if(maxdepth[u]-depth[g]>now){//优先将距离已经超过now的剪去,减少一点时间消耗;
			++cnt;
			if(cnt>s)
				return false;
			continue;
		}
		Q.push(maxdepth[u]);
	}
	
	if(Q.empty())
		return true;
//		if(g==5&&now==2)
//			cout<<Q.size()<<endl;
	Q.push(depth[g]);//方便处理;
	int last=Q.top();
	Q.pop();
	while(Q.top()+last-depth[g]*2>now){//去除最大的两个算距离;
		++cnt;
		last=Q.top();
		Q.pop();
		if(cnt>s)
			return false;
	}
	
	maxdepth[g]=last;
	
	return true;
}

bool check(){
	cnt=0;
	depth[1]=0;
	return dfs(1,0);
}

int main(){
	
	cin>>n>>s;
	
	int x,y;
	
	for(int i=1;i<n;++i)
		cin>>x>>y,
		add(x,y),
		add(y,x);
	
	int l=1,r=n-1;
	
	while(l<r){
		int mid=l+r>>1;
		now=mid;
		if(check())
			r=mid;
		else
			l=mid+1;
	}
	
	cout<<l<<endl;
	return 0;
}

```

但后来又思考了一下:

对于当前子节点$v$,它只会之前节点中最大的进行比较.

同时,如果当前节点与之前节点中最大的那个相比距离大于$mid$,则当前节点一定是到目前为止$maxdepth$最大两个节点之一(此处不包括已经由于被删边而与$u$不连通的点)。

如果距离大于$mid$,只需要将当前为止最大值和当前点$v$的$maxdepth$中较小的一个作为新的最大深度即可,因为既然你一定要删除一条边,肯定将$maxdepth$大的删去要更优秀一些.

而如果距离小于$mid$,就必须取$max$,因为你并没有删去一条边.

这样可以不用二叉堆维护,时间上少了一个$logN$(而且还是把$STL$里的省去了),那么就可以轻松通过测试了.

``` cpp
//O(NlogN);
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e5+10;

int s,n,now,cnt,maxdepth[N],depth[N];

int to[N<<1],nex[N<<1],head[N],tt;

inline void add(int x,int y){
	to[++tt]=y,nex[tt]=head[x],head[x]=tt;
	return ;
}

bool dfs(int g,int f){
	maxdepth[g]=depth[g];
	for(int i=head[g],u;i;i=nex[i]){
		u=to[i];
		if(u==f)
			continue;
		depth[u]=depth[g]+1;
		if(!dfs(u,g))
			return false;
		if(maxdepth[u]+maxdepth[g]-depth[g]*2>now){
			++cnt;
			if(cnt>s)
				return false;
			maxdepth[g]=min(maxdepth[g],maxdepth[u]);//如果一定要删,删去深度较深的显然更优秀;
			continue;
		}
		maxdepth[g]=max(maxdepth[g],maxdepth[u]);//不删就必须取max;
	}
	return true;
}

bool check(){
	cnt=0;
	depth[1]=0;
	return dfs(1,0);
}

int main(){
	
	cin>>n>>s;
	
	int x,y;
	
	for(int i=1;i<n;++i)
		cin>>x>>y,
		add(x,y),
		add(y,x);
	
	int l=1,r=n-1;
	
	while(l<r){
		int mid=l+r>>1;
		now=mid;
		if(check())
			r=mid;
		else
			l=mid+1;
	}
	
	cout<<l<<endl;
	return 0;
}

```

---

