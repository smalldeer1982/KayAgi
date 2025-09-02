# [USACO12NOV] Balanced Trees G

## 题目描述

Fascinated by his experience with balanced parentheses so far, Farmer John is curious if you can help him solve one final problem.  As it turns out, FJ's farm is in the shape of a giant tree of N pastures (1 <= N <= 40,000), each of which he has labeled with either ( or ).  For example:

'('--'('--')'--'('--')' 

|         |

')'       ')'--'('--'(' 

|              |

')'            '('--')'--')'--')'--'(' 

Recall that since his farm is a tree, this means that certain pairs of pastures are connected by corridors so that there is one unique path between any given pair of pastures.  FJ believes that some of these paths represent balanced strings of parentheses.  In particular, he would like to know, among all such balanced strings represented by paths through the tree, what is the maximum nesting depth one can find.  The nesting depth of a balanced string of parentheses is the maximum, over all prefixes of the string, of the excess number of ('s within the prefix.  For example, the string ()()() has nesting depth 1, but the string ((()))() has nesting depth 3, as we can see clearly if we count excess ('s for every prefix of the string: 

((()))() 

12321010

For the example farm above, the deepest string is ((())) with a depth of 3, and can be obtained by taking the path from A to B below:

```cpp
'('--'('--')'--'('--')' 
|         | 
')'       ')'--'('--'(' < A 
|              | 
')'            '('--')'--')'--')'--'(' 
^C                            ^B 
```
Note that this is different than the longest balanced string; for instance (())(()), starting at A and ending at C, has length 8.

Your task is to output the nesting depth of the deepest balanced path in the tree.

给出一棵树，每个结点上有一个括号。问在所有括号平衡的路径中，最大嵌套层数为多少。


## 说明/提示

This is the example from the problem description, with the following node labels:

1'('--4'('--6')'--7'('--8')' 

|     |

2')'  5')'--9'('--10'(' 

|           |

3')'       11'('--12')'--13')'--14')'--15'(' 



## 样例 #1

### 输入

```
15 
1 
2 
1 
4 
4 
6 
7 
5 
9 
9 
11 
12 
13 
14 
( 
) 
) 
( 
) 
) 
( 
) 
( 
( 
( 
) 
) 
) 
( 
```

### 输出

```
3 
```

# 题解

## 作者：一念之间、、 (赞：10)

题意：求合法的括号序列使嵌套最多

首先对于树上路径求方案的问题可以考虑点分治，我们考虑一个合法的括号序列应该是怎么样的，把`(`看作`+1` `)`看作`-1`对于一个合法的括号我们可以发现他的任意前缀和都是大于0的所以，最多嵌套个数就是括号序列前缀的最大值。

考虑如何拼接两条路径，我们可以拆成以下两条路径![](https://cdn.luogu.com.cn/upload/image_hosting/01czhu9a.png)


发现红色路径+蓝色路径和为0，所以对于枚举到蓝色路径求答案的时候我们可以知道红色路径的和。

首先红色路径合法直接判断前缀min大于0即可

考虑蓝色路径什么时候合法，发现蓝色到重心的前缀和的最小值（`r_min`）+红色权值(`-sum`)大于等于0，因为`r_min`恒小于`sum`所以要求`r_min=sum`

考虑答案的产生，一定是在蓝色部分，红色部分，所以对于处理的红色部分，我们开一个桶记录每个红色和的最大值，蓝色部分在`dfs`的时候记录

整理一下我们需要记录5个东西：到重心最小值（蓝合法），到重心最大值（蓝答案），到当前枚举点最小值（红合法），到当前枚举点最大值（红答案），到重心和（更新上面几个值）。

下面是代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int read()
{
	char c;
	int w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	int ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}
int n;
const int xx=4e4+5;
struct node
{
	int next,to;
}e[xx<<1];
int cnt;
int h[xx];
int val[xx];
void add(int x,int y)
{
	cnt++;
	e[cnt].next=h[x];
	e[cnt].to=y;
	h[x]=cnt;
}
int tot,cur,size[xx],maxx[xx],vis[xx];
void findc(int x,int y)
{
	size[x]=1;maxx[x]=0;
	for(int i=h[x];i;i=e[i].next)
	{
		if(e[i].to==y||vis[e[i].to])continue;
		findc(e[i].to,x);
		size[x]+=size[e[i].to];
		maxx[x]=max(maxx[x],size[e[i].to]);
	}
	maxx[x]=max(maxx[x],tot-size[x]);
	if(!cur||maxx[x]<maxx[cur])cur=x;
}
int t_n[xx],ans;
vector<int>v;
void clear()
{
	for(int i=0;i<v.size();i++)t_n[v[i]]=-1;
	v.clear();
}
void get(int x,int y,int r_min,int r_max,int n_min,int n_max,int sum,int op)
{
	sum+=val[x];
	n_max+=val[x];
	n_min+=val[x];
	r_min=min(r_min,sum);
	r_max=max(r_max,sum);
	n_max=max(n_max,0);
	n_min=min(n_min,0);
	if(!op)
	{
		if(r_min==sum)//r_min最小是0，所以sum一定<=0 
		{
			if(t_n[-sum]!=-1)//有红色部分才行 
			{
				ans=max(ans,-sum+r_max);
				ans=max(ans,t_n[-sum]);
			}
		}
	}
	else 
	{
		if(n_min>=0)//红色前缀大于0 
		{
			if(t_n[sum]==-1)v.push_back(sum);
			t_n[sum]=max(t_n[sum],n_max);
		}
	}
	for(int i=h[x];i;i=e[i].next)
	{
		if(e[i].to==y||vis[e[i].to])continue;
		get(e[i].to,x,r_min,r_max,n_min,n_max,sum,op);
	}
}
int sss=0;
void dfz(int x,int y)
{
	assert(sss<2000);
	if(tot==1)return;
	cur=0;findc(x,y);
	x=cur;findc(x,y);//调整size 
	vis[x]=1;
	if(val[x]==1)t_n[1]=1,v.push_back(1);//直下 
	vector<int>v;
	for(int i=h[x];i;i=e[i].next)
	{
		if(e[i].to==y||vis[e[i].to])continue;
		v.push_back(e[i].to);
		get(e[i].to,x,0,0,0,0,0,0);//求答案 
		get(e[i].to,x,min(0,val[x]),max(0,val[x]),min(0,val[x]),max(0,val[x]),val[x],1);
	}
	ans=max(ans,t_n[0]);//直上 
	clear();
	for(int i=v.size()-1;i>=0;i--)
	{
		get(v[i],x,0,0,0,0,0,0);//求答案 
		get(v[i],x,min(0,val[x]),max(0,val[x]),min(0,val[x]),max(0,val[x]),val[x],1);
	}
	clear();
	for(int i=h[x];i;i=e[i].next)
	{
		if(e[i].to==y||vis[e[i].to])continue;
		tot=size[e[i].to];
		sss++;
		dfz(e[i].to,x);
		sss--;
	}
}
signed main(){
	memset(t_n,-1,sizeof(t_n));
	n=read();
	for(int i=2;i<=n;i++)
	{
		int a=read();
		add(a,i);
		add(i,a);
	}
	for(int i=1;i<=n;i++)
	{
		char c;while((c=getchar())!='('&&c!=')');
		if(c=='(')val[i]=1;
		else val[i]=-1;
	}
	tot=n;
	dfz(1,0);
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：___balalida___ (赞：9)

~~人生中第一次写洛谷题解。~~

是一道板子+细节题，如果想要调试的可以去最下方获得 Hack 数据。

### 题目大意

给你一个括号树，求匹配括号中的最大嵌套。

### 题解

最大嵌套是非常经典的。

对于一个括号序列，每个 `(` 看作 `+1`，每个 `)` 看作 `-1`，那么最大嵌套就是这个括号序列的前缀最大值。

这是一个路径统计问题，可以选用的工具有点分治、dsu on tree 以及线段树合并，此题使用点分治。

每次考虑经过分治重心的路径，一定可以拆成左边的一段以及右边的一段。

那么所谓“最大前缀和”在这条链上体现的就是“左边链的最大前缀和”与“右边链的最大前缀和加上左边的和”。（可以理解成线段树的经典套路。）

因为对于每一个根到另外一个节点的路径不分左右，也就是前后缀无法区分，那么我们就定向：**从根到各个节点**。

好，那么我们的任务就明确了：在统计每个子树时，记录每一条**根到节点的链**的后缀最大值（供给左边的链，下称左链），以及前缀最大值（共给右链）。

我们的思路时：在 dfs 过程中统计每种链作为左链或者右链的贡献（即最大值）。

就这样开始了，问题也来了。

一些定义：

**Warning：建议在自己画括号折线图+理解。**

`ldis`:表示当前这条链以左端点作为基准点，右端点的位置（可能为负）。

`rdis`:表示当前这条链以右端点作为基准点，左端点的位置（可能为负）。

`lmx`:表示当前这条链的最大**后缀**。

`rmx`:表示当前这条链（包括根节点）的最大**前缀**。

`lmn`:表示当前这条链以左端点作为基准点，最低点的位置。

`rmn`:表示当前这条链以右端点作为基准点，最低点的位置。

**第一个细节：根节点**

这是个简单的问题，直接默认根节点给右链，也就是在dfs的初始值设定时放上根节点，而作为左链的时候不变

**第二个细节：判断是否合法**

其实点分治的核心也在于此：开一个桶 $b_i$，表示左链失配括号个数为 $i$ 的最大前缀和。

那么每次使用一条右链来和左链匹配，那么答案用 $\max(b[ldis_i],ldis_i+rmx_j)$ 更新。

那么如果左链或右链甚至自己都不合法了怎么办？

交给 dfs！

**第三个细节：dfs怎么写**

好问题。 lmn 和 rmn 会发挥用场了。

显然，只有在他们都 =0 的时候（为什么不是大于等于?）才成立。

那么在 dfs 的过程中记录每一条合适做左链和右链的 mx 与 dis 即可。

那么儿子的转移时比较显然的，不说了。

不过注意在转移 rmx 的时候注意不是和 0 取 max ，因为此时表示的时儿子的状态，并非父亲的。

### 代码

```cpp
void Grt(ll u,ll fa){
	sz[u]=1;ll mx=0;
	go(u)if(v!=fa&&!vis[v])Grt(v,u),sz[u]+=sz[v],mx=max(mx,sz[v]);
	mx=max(mx,TRsz-sz[u]);
	if(mx<szRT)szRT=mx,RT=u;
}
void dfs(ll u,ll fa,ll ldis,ll rdis,ll lmx,ll rmx,ll lmn,ll rmn){
	if(lmn>=0)tmp1[++kkk1]=ldis,tmpp1[kkk1]=lmx;
	if(rmn>=0)tmp2[++kkk2]=rdis,tmpp2[kkk2]=rmx;
	go(u)if(!vis[v]&&v!=fa)dfs(v,u,ldis+a[v],rdis-a[v],max(lmx+a[v],a[v]),max(rmx,-rdis+a[v]),min(lmn+a[v],0ll),min(rmn-a[v],0ll));
}
void calc(ll u){
	kkk1=0;kkk2=0;
	vector<ll>son;
	go(u)if(!vis[v]){
		son.push_back(v);
		ll lst1=kkk1,lst2=kkk2;
		dfs(v,0,a[v],-a[u]-a[v],a[v],max(max(a[u],a[u]+a[v]),0ll),min(a[v],0ll),min(-a[u]-a[v],0ll));
		rep(j,lst2+1,kkk2)if(viss[tmp2[j]])ans=max(ans,max(bl[tmp2[j]],tmp2[j]+tmpp2[j]));
		rep(j,lst1+1,kkk1)bl[tmp1[j]]=max(bl[tmp1[j]],tmpp1[j]),viss[tmp1[j]]=1;
	}
	if(a[u]==-1)ans=max(ans,bl[1]);
	else rep(i,1,kkk2)if(tmp2[i]==0)ans=max(ans,tmpp2[i]);
	rep(i,1,kkk1)bl[tmp1[i]]=0,viss[tmp1[i]]=0;
	kkk1=0;kkk2=0;
	for(ll i=son.size()-1;i>=0;i--){
		ll v=son[i];
		ll lst1=kkk1,lst2=kkk2;
		dfs(v,0,a[v],-a[u]-a[v],a[v],max(max(a[u],a[u]+a[v]),0ll),min(a[v],0ll),min(-a[u]-a[v],0ll));
		rep(j,lst2+1,kkk2)if(viss[tmp2[j]])ans=max(ans,max(bl[tmp2[j]],tmp2[j]+tmpp2[j]));
		rep(j,lst1+1,kkk1)bl[tmp1[j]]=max(bl[tmp1[j]],tmpp1[j]),viss[tmp1[j]]=1;
	}
	if(a[u]==-1)ans=max(ans,bl[1]);
	else rep(i,1,kkk2)if(tmp2[i]==0)ans=max(ans,tmpp2[i]);
	rep(i,1,kkk1)bl[tmp1[i]]=0,viss[tmp1[i]]=0;
}
void solve(ll u){
	vis[u]=1;calc(u);
	go(u)if(!vis[v]){
		szRT=inf;TRsz=sz[v];Grt(v,0);solve(RT);
	}
}
int main(){
	n=read();rep(i,2,n)x=read(),add(i,x),add(x,i);
	rep(i,1,n)a[i]=(get()=='('?1:-1);
	szRT=inf;TRsz=n;Grt(1,0);solve(RT);
	writeln(ans);
}
```
### [Hacks](https://www.luogu.com.cn/paste/4dve91d4)

祝大家做题调题愉快。

---

## 作者：oisdoaiu (赞：5)

*tag:点分治，括号序列*

---
~~怎么两篇题解都没了，我来补一篇~~

这种树上路径问题很容易想到是点分治，考虑如何计算两条路径拼起来的答案。

首先一定是(...(...(...(...这样一条路径和...)...)...)这样一条路径拼起来，然后因为是求 $\max$，所以求出两边的最大深度再取 $\max$ 就行了。这里以左边为例。

---
假设当前是一条合法路径，那么当前的答案就是处理括号序列时用的那个栈的历史最大值，所以在dfs的时候拿个`mx`变量记录一下。

如果当前是一个“(”，而且栈为空，就要把`mx`变量加一，然后可以忽略掉这个“(”【因为拼起来的路径是合法的，这里就可以默认右边有一个“)”把它匹配掉了】。

比如说当前是“(”，父亲到重心是“()(())”，`mx`为 $2$，由于右边路径一定有一个“)”与当前的“(”匹配，所以两段路径拼起来是“( ()(()) ... )”。

相当于中间那部分括号的深度整体+1，所以让`mx+1`就行。

对于右边路径的处理也是类似的，可以结合代码理解一下：
```cpp
/*
up为括号序列栈顶
mxup为历史最大值
cntl为多余出来的，需要用右边的")"去匹配的"("
*/
if(a[x]=='(') val[x].up++;
else val[x].up--;
val[x].mxup = max(val[x].mxup,-val[x].up);
if(val[x].up>0)
    val[x].cntl++,
    val[x].mxup++,
    val[x].up = 0;
```

然后可以用一个桶去记录最大值，以 `cntl/cntr` 为下标。

---
注意一些小细节

- 在dfs的时候最好令一边包含重心，另一边不包含重心

- 不要漏了到重心的本身就合法的链
- 在拼路径的时候要判断是否存在对应的路径

---
```cpp
#include<bits/stdc++.h>
using namespace std;

template<typename T>
inline void Read(T &n){
	char ch; bool flag=0;
	while(!isdigit(ch=getchar()))if(ch=='-')flag=1;
	for(n=ch^48;isdigit(ch=getchar());n=((n<<1)+(n<<3)+(ch^48)));
	if(flag)n=-n;
}

enum{
    MAXN = 40005
};

int n;

struct _{
    int nxt, to;
    _(int nxt=0, int to=0):nxt(nxt),to(to){}
}edge[MAXN<<1];
int fst[MAXN], tot;

inline void Add_Edge(int f, int t){
    edge[++tot] = _(fst[f], t); fst[f] = tot;
    edge[++tot] = _(fst[t], f); fst[t] = tot;
}

char a[MAXN];

inline void upd(int &x, int y){x = max(x,y);}

int sz[MAXN], Size, Weight, Center;
char vis[MAXN], Vis[MAXN];
void Get_Center(int x){
    vis[x] = true;
    sz[x] = 1;
    int w=0;
    for(register int u=fst[x]; u; u=edge[u].nxt){
        int v=edge[u].to;
        if(vis[v] or Vis[v]) continue;
        Get_Center(v);
        sz[x] += sz[v];
        upd(w,sz[v]);
    }   
    upd(w,Size-sz[x]);
    if(w < Weight)
        Weight = w, Center = x;
    vis[x] = false;
}

struct ele{int mxup, mxdown, up, down, cntl, cntr;}val[MAXN];

int q[MAXN], top;
int mxl[MAXN], mxr[MAXN];
void dfs(int x){
    vis[x] = true; q[++top] = x; sz[x] = 1;

    if(a[x]=='(') val[x].up++; else val[x].up--;
    upd(val[x].mxup,-val[x].up);
    if(val[x].up>0)
        val[x].cntl++,
        val[x].mxup++,
        val[x].up = 0;

    if(a[x]=='(') val[x].down++; else val[x].down--;
    upd(val[x].mxdown,val[x].down);
    if(val[x].down<0)
        val[x].cntr++,
        val[x].mxdown++,
        val[x].down = 0;

    for(register int u=fst[x]; u; u=edge[u].nxt){
        int v=edge[u].to;
        if(vis[v] or Vis[v]) continue;
        val[v] = val[x]; dfs(v);
        sz[x] += sz[v];
    }
    vis[x] = false;
}

int ans, dep;
void solve(int x){
    Weight = Size; Get_Center(x); x = Center; Vis[x] = true;

    ele base = (ele){0,0,0,0,0,0};
    if(a[x]=='(') base.cntl = 1; else base.up = -1; base.mxup = 1;
    if(!base.up) mxl[base.cntl] = base.mxup;
    mxr[0] = 0;

    int prv; top = 0;
    int ml=0, mr=0;
    for(register int u=fst[x]; u; u=edge[u].nxt){
        int v=edge[u].to;
        if(Vis[v]) continue;
        val[v] = base; prv = top+1;
        dfs(v);
        for(register int i=prv; i<=top; i++){
            ele cur = val[q[i]];
            upd(ml,cur.cntl); upd(mr,cur.cntr);
            if(!cur.up and ~mxr[cur.cntl]) upd(ans,max(mxr[cur.cntl],cur.mxup));
            if(!cur.down and ~mxl[cur.cntr]) upd(ans,max(mxl[cur.cntr],cur.mxdown));
        }
        for(register int i=prv; i<=top; i++){
            ele cur = val[q[i]];
            if(!cur.up) upd(mxl[cur.cntl],cur.mxup);
            if(!cur.down) upd(mxr[cur.cntr],cur.mxdown);
        }
    }
    fill(mxl,mxl+ml+1,-1); fill(mxr,mxr+mr+1,-1);

    for(register int u=fst[x]; u; u=edge[u].nxt){
        int v=edge[u].to;
        if(Vis[v]) continue;
        Size = sz[v]; solve(v);
    }
}

char tmp[10];

int main(){
    freopen("1.in","r",stdin);
	freopen("2.out","w",stdout);
    // double tt=clock();
    Read(n);
    for(register int i=2; i<=n; i++){
        int fa; scanf("%d",&fa);
        Add_Edge(i,fa);
    }
    memset(mxl,-1,sizeof mxl);
    memset(mxr,-1,sizeof mxr);
    for(register int i=1; i<=n; i++) scanf("%s",tmp), a[i] = tmp[0];
    Size = n; solve(1);
    cout<<ans<<endl;
    // printf("%.6lf\n",(clock()-tt)/CLOCKS_PER_SEC);
    return 0;
}
```

---

## 作者：Leap_Frog (赞：4)

### P.S.
upd on May 3th: 增加了两个字符  
[由于 command_block 神仙好像犯了点小错误，所以他的神仙题解被撤了【悲】](https://www.luogu.com.cn/discuss/show/312924)  
其实我觉得他原来写地挺好的，至少应该比我好。![](//xn--9zr.tk/wq)  
现在负起叉人er的责任来补一篇题解。  
**这篇博客的代码部分参考了 command_block 神仙的代码。**  
真·越调分越低  
![](https://cdn.luogu.com.cn/upload/image_hosting/7tts19pb.png)

### Description.
定义一个括号序列的权值为它的最大嵌套层数。  
给定一棵树，树上每个结点有一个括号。  
问每条链中合法括号序列的最大权值。  

### Solution.
关于树上链的问题，基本上都是点分、边分这种算法。  
考虑点分，我们需要考虑在一个分治中心的答案。  
很显然，一条路由向上的和向下的两部分组成。  
而对于可能作为答案一半的一条向上的路径，如果存在一个 `)`，肯定有一个 `(` 和它匹配。  
我们把它们都消掉，这样向上路径最后只剩下一些 `(`。  
同理，向下路径最后只剩下 `)`，且数量和向上路径的相同。  
我们可以开桶记录每一条路径作为向上路径时最后有多少 `(`，而对每条作为向下路径时查询桶里树的最大值。  
然后主要点分治部分就结束了。  

同时，我们考虑怎么计算答案。  
有一个很基本的结论，就是一个括号序列的最大嵌套次数是把 `(` 当作 1 把 `)` 当作 -1 后前缀和的最大值。  
那么我们从中间把这个括号序列拆成两段后，可以转化成左段后缀最大值和右段前缀最大值加上左边的和。  
然后就可以 $O(1)$ 统计答案。  
然后这题就做完了，总复杂度 $O(n\log n)$。  

### Attantion.
注意要统计仅仅是一条链的情况，command_block 神仙就是没有考虑这种情况。  
注意清空时不能 `memset` 否则复杂度会退化成 $O(n^2)$，~~结果只 TLE 两个点~~  
不知道这篇题解是否有错误，如果有欢迎来 Hack。![](//xn--9zr.tk/wq)  

### Coding.
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
#define ri register int
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}/*}}}*/
const int N=100005;struct edge{int to,nxt;}e[N<<1];int et,head[N],rs=0;
int n,sz[N],mnd,rt,tp,nmp[N],md[N],d[N],sn[N],snt;char a[N],st[N],v[N];
inline void adde(int x,int y) {e[++et]=(edge){y,head[x]},head[x]=et;}
inline void init(int x,int fa)
{//init the size of subtree
	sz[x]=1;for(int i=head[x];i;i=e[i].nxt)
		if(!v[e[i].to]&&e[i].to!=fa) init(e[i].to,x),sz[x]+=sz[e[i].to];
}
inline void getrt(int x,int fa,int tot)
{//find the root
	int mx=tot-sz[x];for(int i=head[x];i;i=e[i].nxt)
		if(!v[e[i].to]&&e[i].to!=fa) mx=max(mx,sz[e[i].to]),getrt(e[i].to,x,tot);
	if(mx<=mnd) mnd=mx,rt=x;
}
inline void dfs2(int x,int fa)
{//find the up path
	char fg=0;st[++tp]=a[x],d[x]=d[fa]+(a[x]?1:-1);
	if(!a[x]) fg=1;else if(tp>1&&!st[tp-1]) ----tp;else fg=1;
	md[x]=max(md[fa],-d[x]);if(!tp||st[tp]) nmp[tp]=max(nmp[tp],md[x]+tp);
	for(int i=head[x];i;i=e[i].nxt) if(e[i].to!=fa&&!v[e[i].to]) dfs2(e[i].to,x);
	if(fg) tp--;else st[++tp]=0;
}
inline void dfs1(int x,int fa)
{//find the down path
	char fg=0;st[++tp]=a[x],d[x]=d[fa]+(a[x]?1:-1);
	if(a[x]) fg=1;else if(tp>1&&st[tp-1]) ----tp;else fg=1;
	md[x]=max(md[fa],d[x]);if((!tp||!st[tp])&&nmp[tp]>=0) rs=max(rs,max(nmp[tp],md[x]+tp));
	for(int i=head[x];i;i=e[i].nxt) if(e[i].to!=fa&&!v[e[i].to]) dfs1(e[i].to,x);
	if(fg) tp--;else st[++tp]=1;
}
inline void calc(int x)
{//calc when x is the center.
	snt=0,nmp[0]=0;for(int i=1;i<=sz[x];i++) nmp[i]=-1e9-5;
	for(int i=head[x];i;i=e[i].nxt) if(!v[e[i].to])
	{
		sn[++snt]=e[i].to,st[tp=1]=a[x],md[x]=d[x]=a[x]?1:-1;
		dfs1(e[i].to,x),tp=md[x]=d[x]=0,dfs2(e[i].to,x),rs=max(rs,nmp[0]);
	}
	nmp[0]=0;for(int i=1;i<=sz[x];i++) nmp[i]=-1e9-5;
	for(;snt;snt--)
	{
		st[tp=1]=a[x],md[x]=d[x]=a[x]?1:-1;
		dfs1(sn[snt],x),tp=md[x]=d[x]=0,dfs2(sn[snt],x),rs=max(rs,nmp[0]);
	}
}
inline void solve(int x)
{
	v[x]=1,calc(x),init(x,0);for(int i=head[x];i;i=e[i].nxt)
		if(!v[e[i].to]) mnd=1e9,getrt(e[i].to,x,sz[e[i].to]),solve(rt);
}
int main()
{
	read(n);for(int i=2,f;i<=n;i++) read(f),adde(i,f),adde(f,i);
	for(int i=1;i<=n;i++) scanf("%s",a+i),a[i]^=41;
	return mnd=1e9,init(1,0),getrt(1,0,n),solve(rt),printf("%d\n",rs),0;
}
```

---

## 作者：__ycx2010__ (赞：2)

## 题目描述

给定一棵树，每个节点上有括号，求树的平衡路径中的最大嵌套层数。

## 分析

把左括号当成 $1$，右括号当成 $-1$。

于是我们发现一个括号序列的最大嵌套层数就等于它的最大前缀和。

使用点分治，我们需要维护的是路径是否合法以及最大前缀和。

判断路径是否合法可以直接用括号匹配，最大前缀和则是需要每一条路径上和的最大值以及最大前缀和的最大值。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 40010;
int n, ans;
int h[N], e[N * 2], ne[N * 2], idx;
int a[N], t[N][2];
bool vis[N];
vector<int> v, s;

void add(int a, int b) {
	e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

int qsiz(int u, int fa) {
	int sz = 1;
	for (int i = h[u]; ~i; i = ne[i]) {
		int j = e[i];
		if (j == fa || vis[j]) continue;
		sz += qsiz(j, u);
	}
	return sz;
}

int dfs(int u, int fa, int al, int &de) {
	int sz = 1, mx = 0;
	for (int i = h[u]; ~i; i = ne[i]) {
		int j = e[i];
		if (j == fa || vis[j]) continue;
		int tmp = dfs(j, u, al, de);
		sz += tmp, mx = max(mx, tmp);
	}
	if (al - sz <= al / 2 && mx <= al / 2) de = u;
	return sz;
}

void dfs2(int u, int fa, int lv, int rv, int nw, int mxp) {
	if (lv == 0) {
		ans = max(ans, max(t[rv][0] + mxp, t[rv][1]));
	}
	for (int i = h[u]; ~i; i = ne[i]) {
		int j = e[i];
		if (j == fa || vis[j]) continue;
		if (a[j]) {
			dfs2(j, u, lv + 1, rv, nw + 1, max(mxp, nw + 1));
		} else {
			if (lv > 0) dfs2(j, u, lv - 1, rv, nw - 1, mxp);
			else dfs2(j, u, lv, rv + 1, nw - 1, mxp);
		}
	}
}

void dfs3(int u, int fa, int lv, int rv, int nw, int mxp) {
	if (rv == 0) t[lv][0] = max(t[lv][0], nw), t[lv][1] = max(t[lv][1], mxp), v.push_back(lv);
	for (int i = h[u]; ~i; i = ne[i]) {
		int j = e[i];
		if (j == fa || vis[j]) continue;
		if (a[j]) {
			if (rv > 0) dfs3(j, u, lv, rv - 1, nw + 1, mxp + 1);
			else dfs3(j, u, lv + 1, rv, nw + 1, mxp + 1);
		} else dfs3(j, u, lv, rv + 1, nw - 1, max(0, mxp - 1));
	}	
}

void calc(int u) {
	if (a[u]) t[1][0] = t[1][1] = 1, v.push_back(1);
	for (int i = h[u]; ~i; i = ne[i]) {
		int j = e[i];
		if (vis[j]) continue;
		s.push_back(j);
		int xx = a[j] ? 1 : -1, yy = a[u] ? 1 : -1;
		dfs2(j, u, a[j], a[j] ^ 1, xx, max(xx, 0));
		int ll = 0, rr = 0;
		if (a[u]) ll ++ ;
		else rr ++ ;
		if (a[j]) {
			if (rr) rr -- ;
			else ll ++ ;
		} else {
			rr ++ ;
		}
		dfs3(j, u, ll, rr, xx + yy, max(0, max(xx, xx + yy)));
	}
	ans = max(ans, t[0][1]);
	for (int i : v) t[i][0] = t[i][1] = -2e9;
	while (v.size()) v.pop_back();
	if (a[u]) t[1][0] = t[1][1] = 1, v.push_back(1);
	reverse(s.begin(), s.end());
	for (int j : s) {
		int xx = a[j] ? 1 : -1, yy = a[u] ? 1 : -1;
		dfs2(j, u, a[j], a[j] ^ 1, xx, max(xx, 0));
		int ll = 0, rr = 0;
		if (a[u]) ll ++ ;
		else rr ++ ;
		if (a[j]) {
			if (rr) rr -- ;
			else ll ++ ;
		} else {
			rr ++ ;
		}
		dfs3(j, u, ll, rr, xx + yy, max(0, max(xx, xx + yy)));
	}
	while (s.size()) s.pop_back();
	for (int i : v) t[i][0] = t[i][1] = -2e9;
	while (v.size()) v.pop_back();
	vis[u] = true;
	for (int i = h[u]; ~i; i = ne[i]) {
		int j = e[i];
		if (vis[j]) continue;
		int dd;
		dfs(j, u, qsiz(j, u), dd);
		calc(dd);
	}
}

int main() {
	scanf("%d", &n);
	memset(h, -1, sizeof h);
	memset(t, 0x8f, sizeof t);
	for (int i = 2, p; i <= n; i ++ ) scanf("%d", &p), add(p, i), add(i, p);
	for (int i = 1; i <= n; i ++ ) {
		char c;
		cin >> c;
		if (c == '(') a[i] = 1;
		else a[i] = 0;
	}
	int dd;
	dfs(1, -1, n, dd);
	calc(dd);
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：ppip (赞：2)

[题目传送门](/problem/P3060)

$\Theta(n)$ 做法，来自[官方题解](http://usaco.org/current/data/sol_btree.html)。

对于点 $i$，如果 $i$ 上是左括号，我们令 $a_i=1$，否则 $a_i=-1$。

先考虑序列上选子串的问题。

现在，设 $f_n$ 表示 $\sum_{i=1}^na_i$。很明显，区间 $[a,b]$ 是合法的，当且仅当 $f_{a-1}=f_b=\min\{f_x|x\in [a-1,b]\}$。次数，答案为 $\max\{f_x|x\in[a,b]\}-f_{a-1}$。

我们枚举 $x$ 计算贡献。对于每个下标 $x$，我们想要找到它在一个合法子串中能达到的最大答案。有一个结论：首先令 $g=\max(\min\{f_y|y\in[0,z)\}, \min\{f_y|y\in[z,n]\})$，其中 $f_0=0$。一定存在一对 $a,b$ 使得 $g=f_a=f_b=\min\{f_y|y\in[a,b]\}$，那么 $x$ 贡献的答案就是 $f_x-g$。注意此处对应的合法串为 $(a,b]$。具体来说，$a$ 是 $x$ 左边离它最近的 $f_a=g$，$b$ 则是右边最近的。

因为 $f$ 相邻两项差的绝对值为 $1$，所以左右两侧一定都包含这个值（在上面的表达式里，$x$ 一侧的最小值 $ < g$ 由于变化量为 $1$，$z$ 和最小值中间一定经过 $g$）。同时 $[a,b]$ 中不可能有 $<g$ 的值，否则在达到这个更小的值之前，一定会先遇到 $g$。于是我们就证明了结论。

为了在树上做这个问题，我们进行一个转化：对于一个点 $x$，它的贡献为它结尾的一个子串的最大权值和，和它下一个数开头的一个子串的最小权值和的相反数，取更小的那个。证明类似上面。这里的值指 $a$。

搬到树上就是，我们枚举一个点和它的下一个点（即，记无向边为两条有向边，然后枚举每条边），设为 $u,v$，答案就是 $u$ 开头的不经过 $v$ 的、点权和最大的一条路径，和 $v$ 开头的不经过 $u$ 的、边权和最小的一条路径的相反数，这两个取较小值。

现在问题转化为了，求每个点不经过相邻的另外一个点的权值和最大/最小路径。这个可以换根 DP 求。

时空复杂度均为 $\Theta(n)$，十分优秀。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define all(awa) awa.begin(),awa.end()
constexpr int N{40000};
// 后缀：[m]最大值，[n]最小值，前缀：[f]子树内，[g]子树外
int fm[N+5],fn[N+5],gm[N+5],gn[N+5],fa[N+5],a[N+5];
vector<int> e[N+5];
void solve(int u) {
    for (auto v:e[u]) {
        solve(v);
        fm[u]=max(fm[u],fm[v]);
        fn[u]=min(fn[u],fn[v]);
    }
    fm[u]+=a[u];fn[u]+=a[u];
}
void sulve(int u) {
    gm[u]+=a[u];gn[u]+=a[u];
    for (auto v:e[u]) gm[v]=max(a[u],gm[u]),gn[v]=min(a[u],gn[u]);
    if (e[u].size()>1) {
        int mx{0},mt{0},mn{0},mp{0};
        for (auto v:e[u]) {
            if (fm[v]>mx) mt=mx,mx=fm[v];
            else mt=max(mt,fm[v]);
            if (fn[v]<mn) mp=mn,mn=fn[v];
            else mp=min(mp,fn[v]);
        }
        for (auto v:e[u]) {
            gm[v]=max(gm[v],(fm[v]==mx?mt:mx)+a[u]);
            gn[v]=min(gn[v],(fn[v]==mn?mp:mn)+a[u]);
        }
    }
    for (auto v:e[u]) sulve(v);
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;cin>>n;
    for (int i{2};i<=n;++i) {
        cin>>fa[i];
        e[fa[i]].push_back(i);
    }
    for (int i{1};i<=n;++i) {
        char c;while (isspace(c=getchar()));
        a[i]=(c=='('?1:-1);
    }
    solve(1);
    sulve(1);
    int ans{0};
    for (int i{2};i<=n;++i) ans=max({ans,min(fm[i],a[i]-gn[i]),min(-fn[i],gm[i]-a[i])});
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：chenxia25 (赞：2)

精神污染题。。。不过要是用结构体写就还好。

括号平衡显然可以代数化，就把 `(` 当 $1$​ 把 `)` 当 $-1$​​​。考虑点分治，需要计算连通块中每个点到重心、以及重心到每个点的代数和、最小 / 最大前缀和等等信息，可以使用结构体很轻松地更新。如下代码给出了括号序列接上一段括号序列的更新方法：

```cpp
struct Tuple{
	int sum,mx,mn;
	Tuple(int x=0,int y=0,int z=0){sum=x,mx=y,mn=z;}
	friend Tuple operator+(Tuple x,Tuple y){return Tuple(x.sum+y.sum,max(x.mx,x.sum+y.mx),min(x.mn,x.sum+y.mn));}
};
```

然后求最大值不能一阶差分，只能动态更新。考虑当前子树内所有点与之前子树的所有点进行匹配，的所有路径之和。我们先考虑前面的点到当前点这个方向怎么做。枚举当前点 $y$，构成合法括号串当且仅当 $sum_x+sum_y=0$ 且 $\min(mn_x,sum_x+mn_y)\geq 0$。根据前者，由于我们已经知道 $sum_y$，那么唯一的合法 $sum_x$ 可以很轻松解出来，这样 $sum_x$ 也是常数了。对后者，min 的右元是常数可以直接判，左元的话，说明 $x$ 入选必须满足 $mn_x\geq 0$。考虑更新的值 $\max(mx_x,sum_x+mx_y)$，右元是常数，最大化左元的话，容易知道我们只需要对所有 $sum_x=v$ 的 $x$ 求最大的 $mx_x$ 即可，用桶维护即可。

考虑反方向路径？不想分类讨论了，我们可以把重心的儿子序列反过来 CV 一遍就行了。总复杂度线对。

---

## 作者：Betrayer_of_love (赞：1)

## 题目：

 **[题目传送门](https://www.luogu.com.cn/problem/P3060)**


给出一棵树，每个节点一个括号，可能左也可能右，求树上一条合法括号路径的最大嵌套层数。


## 分析：

很容易想到点分治，那么现在问题变成如何拼接路径。

由于这样的路径左右顺序会有影响，于是考虑分开处理，也就是拿两个东西分别记从这里出发，和在这里结束两类路径。

然后维护合法性其实就是很简单，分成两截内部和公共的，内部的直接在枚举路径的时候判断就好了，然后公共的就相当于可以对每一个值开一个桶，储存外面需要的答案即可。

那么外面需要的答案是什么呢？

考虑一个已知合法的括号序列怎么求最大嵌套层数，我们可以发现其实这就是括号栈内数量的历史最大值，于是我们在找路径的时候记录一下就好了。

拼接就是取两个历史最值的最值就好了。

剩下的都很好维护了。

## CODE：


```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
	x=0;bool f=false;char ch=getchar();
	while(!isdigit(ch)){f|=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	x=f?-x:x;
	return ;
} 
template <typename T>
inline void write(T x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10^48);
	return ;
}
#define ll long long
const int N=2e5+5;
int n,head[N],nex[N],to[N],idx;
int siz[N],FMax,Root,Size;
int q[N],top,a[N],Max1[N],Max2[N],Ans;
bool vis[N];
char op[5];
inline void add(int u,int v){
	nex[++idx]=head[u];
	to[idx]=v;
	head[u]=idx;
	return ;
}
void GetRoot(int x,int fa){
	siz[x]=1;int Max=0;
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(y==fa||vis[y]) continue;
		GetRoot(y,x);siz[x]+=siz[y];
		Max=max(Max,siz[y]);
	}
	Max=max(Max,Size-siz[x]);
	if(Max<=FMax) FMax=Max,Root=x;
	return ;
}
struct Path{int Max1,Max2,Len1,Len2,cnt1,cnt2;}val[N];
void GetPath(int x,int fa){
	q[++top]=x;
	val[x].Len1+=a[x];
	val[x].Max1=max(val[x].Max1,-val[x].Len1);
	if(val[x].Len1>0) val[x].cnt1++,val[x].Max1++,val[x].Len1=0;
	val[x].Len2+=a[x];
	val[x].Max2=max(val[x].Max2,val[x].Len2);
	if(val[x].Len2<0) val[x].cnt2++,val[x].Max2++,val[x].Len2=0;
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(vis[y]||y==fa) continue;
		val[y]=val[x];GetPath(y,x);
	}
	return ;
}
void DFS(int x,int fa){
	FMax=Size;GetRoot(x,fa);x=Root;vis[x]=true;
	Path now=(Path){0,0,0,0,0,0};
	if(a[x]==1) now.cnt1=1;
	else now.Len1=-1;
	now.Max1=1;
	if(!now.Len1) Max1[now.cnt1]=now.Max1;
	int Cnt1,Cnt2;
	Max2[0]=top=Cnt1=Cnt2=0; 
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(vis[y]) continue;
		val[y]=now;int tmp=top+1;
		GetPath(y,x);
		for(int i=tmp;i<=top;i++){
			Path res=val[q[i]];
			Cnt1=max(Cnt1,res.cnt1),Cnt2=max(Cnt2,res.cnt2);
			if(!res.Len1 && ~Max2[res.cnt1]) Ans=max(Ans,max(Max2[res.cnt1],res.Max1));
            if(!res.Len2 && ~Max1[res.cnt2]) Ans=max(Ans,max(Max1[res.cnt2],res.Max2));
        }
        for(int i=tmp;i<=top;i++){
            Path res=val[q[i]];
            if(!res.Len1) Max1[res.cnt1]=max(Max1[res.cnt1],res.Max1);
            if(!res.Len2) Max2[res.cnt2]=max(Max2[res.cnt2],res.Max2);
        }
	}
	for(int i=0;i<=Cnt1;i++) Max1[i]=-1;
	for(int i=0;i<=Cnt2;i++) Max2[i]=-1;
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(y==fa||vis[y]) continue;
		Size=siz[y],DFS(y,x);
	}
	return ;
}
signed main(){
	read(n);
	for(int i=2;i<=n;i++){
		int x;read(x);
		add(x,i),add(i,x);
	}
	memset(Max1,-1,sizeof(Max1));
	memset(Max2,-1,sizeof(Max2));
	for(int i=1;i<=n;i++) scanf("%s",op),a[i]=(op[0]=='('?1:-1);
	Size=n,DFS(1,0);
	write(Ans);
	return 0;
}

```

---

## 作者：eEfiuys (赞：1)

#### P3060 [USACO12NOV] Balanced Trees G 题解 by aqx_AK_xyf

Update: 修复了加粗的渲染问题。

**这是一个 $O(n)$ 的超好写做法。**

我们先考虑序列上的问题：一个括号序列，求子段嵌套层数最大值。

如果我们把左括号看作 $1$，右括号看作 $-1$，那嵌套层数就是该子段的前缀和最大值。

后文所述子段、前缀、后缀均包括空串。

设 $l$ 表示某子段中左括号个数，$r$ 表示某子段中右括号个数。

定义“左准合法序列”为：对于任意前缀，都有 $l \ge r$ 的括号序列；相应地，定义“右准合法序列”为：对于任意后缀，都有 $r \ge l$ 的括号序列。

设 $f_i$ 表示以 $i$ 结尾的所有串中 $l-r$ 的最大值，$g_i$ 表示以 $i$ 开始的所有串中 $r-l$ 的最大值（$f_0=g_{n+1}=0$）。

**引理 1：**$f_i$ 所对应的串，一定是“左准合法序列”。

证明：如果不是，则删掉这个 $l<r$ 的前缀能让 $f_i$ 变大。

同理，$g_i$ 所对应的串，一定是“右准合法序列”。

**引理 2**：对于任意整数 $0 \le x \le f_i$，总存在一段以 $i$ 结尾的后缀 $s$，使得 $l-r=x$，且 $s$ 是“左准合法序列”。

证明：设 $t$ 是从 $i$ 开始往前添加括号，第一次有 $l-r=x$ 时（即最短）的后缀。显然 $t$ 一定存在，因为 $l-r$ 在这个过程中不会跳过某个值。而 $t$ 也一定是“左准合法序列”，理由如下：假设它不是“左准合法序列”，则找到某 $r>l$ 的前缀，删掉后的 $t'$ 有 $l-r>x$，那么从空串变成 $t'$ 的过程中就有更早的 $l-r=x$，于是 $t$ 不是最短的，矛盾，原命题得证。

对于 $g_i$ 同理。

**引理 3**：设 $t_1$ 为“左准合法序列”，$t_2$ 为“右准合法序列”，把 $t_1$ 和 $t_2$ 拼起来得到的 $t$ 有 $l=r$，则 $t$ 为合法括号序列。

证明：假设 $t$ 存在某前缀使得 $r>l$。若它是 $t_1$ 的前缀，矛盾。否则，剩余的后缀是 $t_2$ 的后缀，且 $l>r$，矛盾。

**引理 4**：对于所有包含 $i$ 的合法括号序列 $s$，设其以 $i$ 结尾的一段前缀的 $l-r=x$，则 $x$ 的最大值为 $\min(f_i,g_{i+1})$。

证明：由定义得，$x \le f_i$。由于合法括号序列有 $l=r$，因此 $x \le g_{i+1}$。不妨 $f_i \le g_{i+1}$。设 $f_i$ 对应的串为 $t_1$。由引理 1 得，$t_1$ 是“左准合法序列”。由引理 2 得，存在以 $i+1$ 开始的串 $t_2$，满足 $t_2$ 的 $r-l$ 等于 $f_i$。由引理 $3$ 得，把 $t_1$ 和 $t_2$ 拼起来就得到了一个合法括号序列，因此 $x$ 能取到 $f_i$。

于是答案就是 $\max_{i=0}^n\min(f_i,g_{i+1})$。至于 $f$ 和 $g$，扫两遍就好了。

对于树上的问题，“以 $i$ 结尾”和“以 $i$ 开始”就相当于，以 $i$ 为端点，子树内和子树外。由于树上的序列没有方向，因此子树内和子树外都要求 $l-r$ 和 $r-l$ 的最大值。这个可以先 dfs 一遍求子树内，再 dfs 一遍求子树外。

**Code**

```cpp
void MAX(int &a,int b){a=max(a,b);}
int n,rt,ans;
char s[N];
vector<int>g[N];
int imxr[N],imxl[N],omxr[N],omxl[N];
void dfs1(int u,int fa){
    for(int v:g[u]){
        if(v==fa)continue;
        dfs1(v,u);
        MAX(imxr[u],imxr[v]),MAX(imxl[u],imxl[v]);
    }
    if(s[u]=='(')imxr[u]--,imxl[u]++;
    else imxl[u]--,imxr[u]++;
    MAX(imxr[u],0),MAX(imxl[u],0);
}
void dfs2(int u,int fa){
    int mxr=0,mxl=0;
    for(int v:g[u]){
        if(v==fa)continue;
        omxr[v]=omxr[u],omxl[v]=omxl[u];
        MAX(omxr[v],mxr),MAX(omxl[v],mxl);
        MAX(mxr,imxr[v]),MAX(mxl,imxl[v]);
    }
    reverse(g[u].begin(),g[u].end());
    mxr=0,mxl=0;
    for(int v:g[u]){
        if(v==fa)continue;
        MAX(omxr[v],mxr),MAX(omxl[v],mxl);
        MAX(mxr,imxr[v]),MAX(mxl,imxl[v]);
    }
    reverse(g[u].begin(),g[u].end());
    for(int v:g[u]){
        if(v==fa)continue;
        if(s[u]=='(')omxr[v]--,omxl[v]++;
        else omxl[v]--,omxr[v]++;
        dfs2(v,u);
    }
}
void solve(){
    cin>>n;
    for(int i=2,fa;i<=n;i++)cin>>fa,g[fa].push_back(i);
    for(int i=1;i<=n;i++)cin>>s[i];
    dfs1(1,0),dfs2(1,0);
    for(int i=1;i<=n;i++){
        MAX(ans,min(imxl[i],omxr[i]));
        MAX(ans,min(omxl[i],imxr[i]));
    }
    cout<<ans<<'\n';
}
```

---

## 作者：complete_binary_tree (赞：1)

**本文章包含：**

- **解题思路**

- **优化**

- **究极~~老六~~卡时**

这题卡了蒟蒻好久。感觉比模式字符串都难。~~**卡了我3天~~

首先，看到这题，我们很容易就想到点分治。那点分治怎么做呢？

我们假设点分治的根为 $rt$。那么如果一个合法的括号序列经过了根节点，那么它就可以分为左半边和右半边。

并且，这题也像模式字符串一样，**$<u,v>$ 和 $<v,u>$ 是不同的**（可以自己推一推，发现组成的括号序列不一样）。

于是，我们就像模式字符串一样，维护括号的前缀和后缀。如果前缀/后缀合法，我们就分别存在桶中。在查询时只要根据前/后缀找对应的后/前缀即可。

但是，出现了很多问题：

1. 什么时候合法？

对于前缀，我们认为 **当左括号有剩余时**，前缀合法。

例如 $(,(()((),((())((),()(()$ 是合法的。而 $),()),)()(())$ 不是合法的。

后缀类似，是 **当右括号有剩余时** 合法。

但是，你肯能会问：$()(()$ 好像是由两组括号拼起来的，这对吗？

对的。因为左边那组括号不会影响答案。

2. 怎么维护最大嵌套括号层数？

定义最大嵌套层数为：**合法** 的前/后缀 **匹配的括号序列** 中最深的嵌套层数。

在这条括号序列的寻找路径上，前缀的最大嵌套层数就是 **曾经栈中右括号最多的个数**。

同理，后缀最大嵌套层数就是 **曾经栈中左括号最多的个数**。

所以，我们在更新的时候要跟一个栈喽？

其实没必要。把左括号当成 $1$，右括号当成 $-1$，此时只需要加减就可以知道栈中的情况了。

---

然后，我们就可以开始更新了。将需要的东西（除了桶）以外全都塞到点分治中作为参数下传。

然后，当合法时，让 ```bowl[多余的括号数] = max(bowl_pre[],最大括号嵌套个数)```（实际上需要两个桶，分别存前/后缀，为了方便演示，我只写了一个桶）。

在寻找答案的时候，直接查找桶中是否存在合法对应前/后缀即可。即 ```ans = max(ans, max(bowl[多余的括号数], 现在的最大括号嵌套个数) + 多余的括号数```，其中 ```bowl[多余的括号数]``` 就相当于另一边的最大括号嵌套个数。注意 **前缀对应后缀，后缀对应前缀**。

一些细节：

- 需要另外开一个桶来判断 ```bowl[多余的括号数]``` 是否被更新过。如果没被更新，那么就不能用它更新答案。

- 记得清空上述的桶！！！

- 判断好根节点归哪边管。

- 最后，~~不要像我一样写错变量名，毕竟这题细节还蛮多的。~~

时间复杂度 $O(n\log n)$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 40005;

//int mx_pre[N]; //前缀括号最长
//int mx_suf[N]; //后缀括号最长
int bowl_pre[N]; //前缀括号最长
int bowl_suf[N]; //后缀括号最长
bool bool_pre[N];
bool bool_suf[N];
//以上都是匹配的括号

int mxzs[N]; //最大子树
int jds[N]; //root 为根子树大小
char kh[N]; //存括号
bool vis[N];
int ans;
vector<int> e[N];

queue<int> q; //找子树

void find_zx(int u, int fa){
	q.push(u);
	jds[u] = 1, mxzs[u] = 0;
	int L = e[u].size();
	for(int i = 0; i < L; ++i){
		int v = e[u][i];
		if(vis[v] || v == fa) continue;
		find_zx(v, u);
		jds[u] += jds[v], mxzs[u] = max(mxzs[u], jds[v]);
	}
	return ;
}

void find_pre(int u, int fa, int _stack, int mx_pre, int mx_suf){
	//stack 中 ( = +1, ) = -1.
	//前缀括号最长：((((((，也就是 > 0 统计，< 0 更新答案
	//后缀反之
	if(kh[u] == '('){ //前缀括号更新，后缀统计答案
		_stack++;
		mx_pre = max(mx_pre, _stack);
		if(_stack >= 0 && bool_suf[_stack]){
			ans = max(ans, max(mx_suf, bowl_suf[_stack]) + _stack);
		}
	}
	else{
		_stack--;
		mx_suf = max(mx_suf, -_stack);
		if(_stack <= 0 && bool_pre[-_stack]){
			ans = max(ans, max(mx_pre, bowl_pre[-_stack]) - _stack);
		}
	}
	int L = e[u].size();
	for(int i = 0; i < L; ++i){
		int v = e[u][i];
		if(fa == v || vis[v]) continue;
		find_pre(v, u, _stack, mx_pre, mx_suf);
	}
	return ;
}

void find_suf(int u, int fa, int _stack, int mx_pre, int mx_suf){
	//stack 中 ( = +1, ) = -1.
	//前缀括号最长：((((((，也就是 > 0 统计，< 0 更新 bowl
	//后缀反之
	if(kh[u] == '('){
		_stack++;
		mx_pre = max(mx_pre, _stack);
		if(_stack >= 0){
			bool_pre[_stack] = 1;
			bowl_pre[_stack] = max(mx_suf, bowl_pre[_stack]);
		}
	}
	else{
		_stack--;
		mx_suf = max(mx_suf, -_stack);
		if(_stack <= 0){
			bool_suf[-_stack] = 1;
			bowl_suf[-_stack] = max(bowl_suf[-_stack], mx_pre);
		}
	}
	int L = e[u].size();
	for(int i = 0; i < L; ++i){
		int v = e[u][i];
		if(fa == v || vis[v]) continue;
		find_suf(v, u, _stack, mx_pre, mx_suf);
	}
	return ;
}

void dfz(int root){
	find_zx(root, 0);
	int all = jds[root];
	while(!q.empty()){
		int u = q.front();
		q.pop();
		mxzs[u] = max(mxzs[u], all - jds[u]);
		if(mxzs[u] < mxzs[root]) root = u;
	}

	int L = e[root].size();
	for(int i = 0; i < L; ++i){
		int v = e[root][i];
		if(vis[v]) continue;
		if(kh[root] == '(')
			find_pre(v, root, 1, 1, 0);
		else
			find_pre(v, root, -1, 0, 1);
		find_suf(v, root, 0, 0, 0);
	}
	vis[root] = 1;
	memset(bowl_pre, 0, sizeof bowl_pre);
	memset(bowl_suf, 0, sizeof bowl_suf);
	memset(bool_pre, 0, sizeof bool_pre);
	memset(bool_suf, 0, sizeof bool_suf);
	for(int i = 0; i < L; ++i){
		int v = e[root][i];
		if(vis[v]) continue;
		dfz(v);
	}
	return ;
}

int n;

int main(){
//	freopen("std.in", "r", stdin);
//	freopen("ans.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 2; i <= n; ++i){
		int v;
		scanf("%d", &v);
		e[i].push_back(v), e[v].push_back(i);
	}
	for(int i = 1; i <= n; ++i) cin >> kh[i];
	dfz(1);
	printf("%d", ans);
	return 0;
}
```

**如何卡时？**

我们发现，这份代码跑了 $3\text{s}+$，明显很慢。

这很大一部分是 ```memset``` 的锅。

所以，我们把更新 ```bowl``` 的数用队列存储起来，在最后再统一将其赋值为 $0$。这样就得到了很大的优化。

还有，如果子树的大小小于 $2\times ans$，可以不搜，节省时间。

Code：$\text{157ms/6.17MB}$

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 40005;

//int mx_pre[N]; //前缀括号最长
//int mx_suf[N]; //后缀括号最长
int bowl_pre[N]; //前缀括号最长
int bowl_suf[N]; //后缀括号最长
bool bool_pre[N];
bool bool_suf[N];
//以上都是匹配的括号

int mxzs[N]; //最大子树
int jds[N]; //root 为根子树大小
char kh[N]; //存括号
bool vis[N];
queue<int> _pre;
queue<int> _suf;
int ans, n;
vector<int> e[N];

queue<int> q; //找子树

void find_zx(int u, int fa){
	q.push(u);
	jds[u] = 1, mxzs[u] = 0;
	int L = e[u].size();
	for(int i = 0; i < L; ++i){
		int v = e[u][i];
		if(vis[v] || v == fa) continue;
		find_zx(v, u);
		jds[u] += jds[v], mxzs[u] = max(mxzs[u], jds[v]);
	}
	return ;
}

void find_pre(int u, int fa, int _stack, int mx_pre, int mx_suf){
	//stack 中 ( = +1, ) = -1.
	//前缀括号最长：((((((，也就是 > 0 统计，< 0 更新答案
	//后缀反之
	if(kh[u] == '('){ //前缀括号更新，后缀统计答案
		_stack++;
		mx_pre = max(mx_pre, _stack);
		if(_stack >= 0 && bool_suf[_stack]){
			ans = max(ans, max(mx_suf, bowl_suf[_stack]) + _stack);
		}
	}
	else{
		_stack--;
		mx_suf = max(mx_suf, -_stack);
		if(_stack <= 0 && bool_pre[-_stack]){
			ans = max(ans, max(mx_pre, bowl_pre[-_stack]) - _stack);
		}
	}
	int L = e[u].size();
	for(int i = 0; i < L; ++i){
		int v = e[u][i];
		if(fa == v || vis[v]) continue;
		find_pre(v, u, _stack, mx_pre, mx_suf);
	}
	return ;
}

void find_suf(int u, int fa, int _stack, int mx_pre, int mx_suf){
	//stack 中 ( = +1, ) = -1.
	//前缀括号最长：((((((，也就是 > 0 统计，< 0 更新 bowl
	//后缀反之
	if(kh[u] == '('){
		_stack++;
		mx_pre = max(mx_pre, _stack);
		if(_stack >= 0){
			if(!bool_pre[_stack]) _pre.push(_stack);
			bool_pre[_stack] = 1;
			bowl_pre[_stack] = max(mx_suf, bowl_pre[_stack]);
		}
	}
	else{
		_stack--;
		mx_suf = max(mx_suf, -_stack);
		if(_stack <= 0){
			if(!bool_suf[-_stack]) _suf.push(-_stack);
			bool_suf[-_stack] = 1;
			bowl_suf[-_stack] = max(bowl_suf[-_stack], mx_pre);
		}
	}
	int L = e[u].size();
	for(int i = 0; i < L; ++i){
		int v = e[u][i];
		if(fa == v || vis[v]) continue;
		find_suf(v, u, _stack, mx_pre, mx_suf);
	}
	return ;
}

void dfz(int root){
	find_zx(root, 0);
	int all = jds[root];
	while(!q.empty()){
		int u = q.front();
		q.pop();
		mxzs[u] = max(mxzs[u], all - jds[u]);
		if(mxzs[u] < mxzs[root]) root = u;
	}

	int L = e[root].size();
	for(int i = 0; i < L; ++i){
		int v = e[root][i];
		if(vis[v]) continue;
		if(kh[root] == '(')
			find_pre(v, root, 1, 1, 0);
		else
			find_pre(v, root, -1, 0, 1);
		find_suf(v, root, 0, 0, 0);
	}
	vis[root] = 1;
	while(!_pre.empty()){ //队列清空
		int u = _pre.front();
		_pre.pop();
		bowl_pre[u] = bool_pre[u] = 0;
	}
	while(!_suf.empty()){ //队列清空
		int u = _suf.front();
		_suf.pop();
		bowl_suf[u] = bool_suf[u] = 0;
	}
	for(int i = 0; i < L; ++i){
		int v = e[root][i];
		if(jds[v] <= ans * 2) continue; //剪枝
		if(vis[v]) continue;
		dfz(v);
	}
	return ;
}

int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9'){
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * f;
}



int main(){
	n = read();
	for(int i = 2; i <= n; ++i){
		int v;
		v = read();
		e[i].push_back(v), e[v].push_back(i);
	}
	for(int i = 1; i <= n; ++i){
		char ch = getchar();
		while(ch != '(' && ch != ')') ch = getchar();
		kh[i] = ch;
		//cin >> kh[i];
	}

	dfz(1);
	printf("%d", ans);
	return 0;
}
```

然后，在一些离谱的剪枝和 [大佬的究极快读](https://blog.csdn.net/qq_36297813/article/details/87874335) ~~这快读竟然不能读字符，我自己加的~~ 下，我成功卡到了 [$\text{131ms}$](https://www.luogu.com.cn/record/148841364)。~~最优解第三好耶~~

---

## 作者：Nazq (赞：0)

树上路径考虑点分治。

答案是合法括号序列的最大前缀和。
类似于[这题](https://www.luogu.com.cn/problem/P5306)的思路，将 `(` 视作 $1$、`)` 视作 $-1$。

记 $w(i)$ 为 $i$ 到 $rt$ 的点权之和，$j$ 为该点到 $rt$ 的点。

对于当前重心 $rt$。

$A$：考虑刻画任意到 $rt$ 的合法的 $u$。

则需要满足任意前缀点权和都不小于 $0$，即 $w(u) - w(j) \ge 0$ 且 $w(u) \ge 0$，有 $w(u) \ge \max \{ \max w(j), 0 \}$。

$B$：任意从 $rt$ 到 $v$。

也需要满足任意前缀点权和都不小于 $0$，即 $-w(v) + w(j) \ge 0$，且 $w(v) \le 0$（因为会匹配成合法序列，所以可以知道和这条路径匹配的 $u$ 一定有 $-w(v)$ 个 `(` 没有匹配。），有 $-w(v) + \min \{ \min w(j), 0 \} \ge 0$。

对于这种类似 $x$ 与唯一的 $y$ 匹配的问题，考虑用桶 $judge$ 存储 $A$ 的贡献。

考虑存 $A$（反过来同理），对于每个合法的 $v$，贡献是 $\max \{ judge(-w(v)), -w(v) + \max w_j\}$。

细节

1. 根节点要划给 $A, B$ 其一，避免重复。
2. 对于左边的贡献是前缀最大值，转化为总的减去后缀最小值。
3. 只存 $A$，用 $B$ 来统计贡献，可以发现有些情况我们是统计不到的。为简化过程，我们可以正、倒序遍历儿子来更新答案。
4. 对于一条一端为 $rt$ 的链的贡献，我们要单独处理。
5. $rt$ 如果有贡献要存桶里。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=40005;
struct Edge{ int to,nxt; }e[N<<1];
int head[N],len;
void Insert(const int &u,const int &v){
	e[++len]={v,head[u]};
	head[u]=len;
}
int n,a[N],ans;
int rt,sum,maxp[N],siz[N];
bool vis[N];
void Getrt(int u,int prt){
	siz[u]=1,maxp[u]=0;
	for(int i=head[u],v;i;i=e[i].nxt){
		v=e[i].to;
		if(vis[v]||v==prt)continue;
		Getrt(v,u);
		siz[u]+=siz[v];
		maxp[u]=max(maxp[u],siz[v]);
	}
	maxp[u]=max(maxp[u],sum-siz[u]);
	if(maxp[rt]>maxp[u])rt=u;
}
int tA,tB;
int w[N],w2[N],judge[N],tmp[N];
pair<int,int> A[N],B[N];
void Getdis(int u,int prt,int Max,int Min,int _Max,int _Min){
	if(w[u]>=Max)
		A[++tA]=make_pair(w[u],Min);
	// printf("%d %d %d\n",u,w2[u],_Min);
	if(w2[u]<=0&&-w2[u]+_Min>=0)
		B[++tB]=make_pair(w2[u],_Max);
	for(int i=head[u],v;i;i=e[i].nxt){
		v=e[i].to;
		if(vis[v]||v==prt)continue;
		w[v]=w[u]+a[v];
		w2[v]=w2[u]+a[v];
		Getdis(v,u,max(Max,w[v]),min(Min,w[v]),max(_Max,w2[v]),min(_Min,w2[v]));
	}
}
int st[N],top;
void Calc(int u){
	int cnt=0;top=0;
	if(a[u]==1)
		judge[1]=1;
	w[u]=a[u];
	w2[u]=0;
	for(int i=head[u],v;i;i=e[i].nxt){
		v=e[i].to;
		if(vis[v])continue;
		st[++top]=v;
		tA=tB=0;
		w[v]=w[u]+a[v];
		w2[v]=a[v];
		Getdis(v,u,max({w[u],w[v],0}),min({w[u],w[v],0}),max(w2[v],0),min(w2[v],0));
		for(int j=1;j<=tB;++j)
			if(judge[-B[j].first]!=-1e9)
				ans=max(ans,max(judge[-B[j].first],-B[j].first+B[j].second));
		for(int j=1;j<=tA;++j)
			judge[A[j].first]=max(judge[A[j].first],A[j].first-A[j].second),tmp[++cnt]=A[j].first;
	}
	ans=max(ans,judge[0]);
	for(int i=1;i<=cnt;++i)
		judge[tmp[i]]=-1e9;
	if(a[u]==1)
		judge[1]=1;
	cnt=0;
	while(top){
		int v=st[top--];
		tA=tB=0;
		// w[v]=w[u]+a[v];
		// w2[v]=a[v];
		Getdis(v,u,max({w[u],w[v],0}),min({w[u],w[v],0}),max(w2[v],0),min(w2[v],0));
		for(int j=1;j<=tB;++j)
			if(judge[-B[j].first]!=-1e9)
				ans=max(ans,max(judge[-B[j].first],-B[j].first+B[j].second));
		for(int j=1;j<=tA;++j){
			judge[A[j].first]=max(judge[A[j].first],A[j].first-A[j].second),tmp[++cnt]=A[j].first;
		}
	}
	for(int i=1;i<=cnt;++i)
		judge[tmp[i]]=-1e9;
	if(a[u]==1)
		judge[1]=-1e9;
}
void Divide(int u){
	vis[u]=1;
	Calc(u);
	for(int i=head[u],v;i;i=e[i].nxt){
		v=e[i].to;
		if(vis[v])continue;
		rt=0;
		maxp[0]=sum=siz[v];
		Getrt(v,u);
		Divide(rt);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=2;i<=n;++i){
		int fa;
		scanf("%d",&fa);
		Insert(fa,i);
		Insert(i,fa);
	}
	for(int i=1;i<=n;++i){
		char x;
		scanf(" %c",&x);
		if(x=='(')a[i]=1;
		else a[i]=-1;
	}
	rt=0;
	maxp[rt]=sum=n;
	for(int i=0;i<=n;++i)
		judge[i]=-1e9;
	Getrt(1,0);
	// printf("rt = %d\n",rt);
	Divide(rt);
	printf("%lld\n",ans);
	return 0;
}
```

---

