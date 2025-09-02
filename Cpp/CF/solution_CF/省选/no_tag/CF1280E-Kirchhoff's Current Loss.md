# Kirchhoff's Current Loss

## 题目描述

Your friend Kirchhoff is shocked with the current state of electronics design.

"Ohmygosh! Watt is wrong with the field? All these circuits are inefficient! There's so much capacity for improvement. The electrical engineers must not conduct their classes very well. It's absolutely revolting" he said.

The negativity just keeps flowing out of him, but even after complaining so many times he still hasn't lepton the chance to directly change anything.

"These circuits have too much total resistance. Wire they designed this way? It's just causing a massive loss of resistors! Their entire field could conserve so much money if they just maximized the potential of their designs. Why can't they just try alternative ideas?"

The frequency of his protests about the electrical engineering department hertz your soul, so you have decided to take charge and help them yourself. You plan to create a program that will optimize the circuits while keeping the same circuit layout and maintaining the same effective resistance.

A circuit has two endpoints, and is associated with a certain constant, $ R $ , called its effective resistance.

The circuits we'll consider will be formed from individual resistors joined together in series or in parallel, forming more complex circuits. The following image illustrates combining circuits in series or parallel.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1280E/28f2a272e8afd0f2565ec77a5e038d7431f9ecf6.png)According to your friend Kirchhoff, the effective resistance can be calculated quite easily when joining circuits this way:

- When joining $ k $ circuits in series with effective resistances $ R_1, R_2, \ldots, R_k $ , the effective resistance $ R $ of the resulting circuit is the sum $ $$$R = R_1 + R_2 + \ldots + R_k. $ $ <p> </p></li><li> When joining  $ k $  circuits in <span class="tex-font-style-underline">parallel</span> with effective resistances  $ R\_1, R\_2, \\ldots, R\_k $ , the effective resistance  $ R $  of the resulting circuit is found by solving for  $ R $  in  $ $ \frac{1}{R} = \frac{1}{R_1} + \frac{1}{R_2} + \ldots + \frac{1}{R_k}, $ $  <span class="tex-font-style-underline">assuming all  $ R\_i > 0 $ </span>; if at least one  $ R\_i = 0 $ , then the effective resistance of the whole circuit is simply  $ R = 0 $ . </li></ul><p>Circuits will be represented by strings. Individual resistors are represented by an asterisk, "<span class="tex-font-style-tt">*</span>". For more complex circuits, suppose  $ s\_1, s\_2, \\ldots, s\_k $  represent  $ k \\ge 2 $  circuits. Then:</p><ul> <li> "<span class="tex-font-style-tt">( $ s\_1 $  S  $ s\_2 $  S  $ \\ldots $  S  $ s\_k $ )</span>" represents their <span class="tex-font-style-underline">series</span> circuit; </li><li> "<span class="tex-font-style-tt">( $ s\_1 $  P  $ s\_2 $  P  $ \\ldots $  P  $ s\_k $ )</span>" represents their <span class="tex-font-style-underline">parallel</span> circuit. </li></ul><p>For example, "<span class="tex-font-style-tt">(* P (* S *) P *)</span>" represents the following circuit:</p><center> <img class="tex-graphics" src="//espresso.codeforces.com/20aa87fefe6adf3989884422c259a4596d9e48d4.png" style="max-width: 100.0%;max-height: 100.0%;" /> </center><p>Given a circuit, your task is to assign the resistances of the individual resistors such that they satisfy the following requirements:</p><ul> <li> Each individual resistor has a <span class="tex-font-style-underline">nonnegative integer</span> resistance value; </li><li> The effective resistance of the whole circuit is  $ r $ ; </li><li> The sum of the resistances of the individual resistors is minimized. </li></ul><p>If there are  $ n $  individual resistors, then you need to output the list  $ r\_1, r\_2, \\ldots, r\_n $  ( $ 0 \\le r\_i $ , and  $ r\_i $  is an integer), where  $ r\_i $  is the resistance assigned to the  $ i $ -th individual resistor that appears in the input (from left to right). If it is impossible to accomplish the task, you must say so as well.</p><p>If it is possible, then it is guaranteed that the minimum sum of resistances is at most  $ 10^{18}$$$.

## 说明/提示

The following illustrates the third sample case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1280E/852e127bec4be806dc910057e8c7ff02af314dbc.png)Here, the sum of the resistances of the individual resistors is $ 2 + 1 + 1 = 4 $ , which can be shown to be the minimum. Note that there may be other assignments that achieve this minimum.

## 样例 #1

### 输入

```
3
5 *
1 (* S *)
1 (* P (* S *))
```

### 输出

```
REVOLTING 5
REVOLTING 1 0
REVOLTING 2 1 1
```

# 题解

## 作者：Caro23333 (赞：4)

来水题解啦！

首先假设我们已经完成了输入处理的部分......

首先我们不难发现一个简单的结论：

考虑一个电阻网络$G$，不妨设当$G$的等效电阻为$x$时$G$中电阻总和的最小值为$f_G(x)$，则存在仅与$G$相关的常数$k_G$，使得$f_G(x)=xk_G$。

电阻网络可以递归地理解：一个电阻网络$G$是由$m$个子电阻网络$G_1,G_2,\dots G_m$直接并联或串联组成的。首先考虑如何求出$k_G$：

令$x$为$G$的等效电阻，$x_1,x_2,x_3,\dots x_m$分别为$G_1,G_2,\dots G_m$的等效电阻，$S=\sum f_{G_i}(x_i)=\sum x_ik_{G_i}$。
- 若$G$由串联组成，
则有$x=\sum x_i$。不妨令$k_{G_1}\le k_{G_2}\le\dots\le k_{G_m}$，则取$x_1=x,x_2=x_3=\dots=x_m=0$时$S$取最小值$xk_{G_1}$, 即$k_G=k_{G_1}$。由调整法显然可证。

- 若$G$由并联组成，
则有$\frac{1}{x}=\sum \frac{1}{x_i}$。考虑如下转化：
$$S=x(\sum \frac{1}{x_i})(\sum x_ik_{G_i})$$

再由柯西不等式有：
$$x(\sum \frac{1}{x_i})(\sum x_ik_{G_i})\ge x(\sum \sqrt{k_{G_i}})^2$$

即，$k_G=(\sum \sqrt{k_{G_i}})^2$。

由柯西不等式的取等条件，上述不等式取等号当且仅当：存在$\lambda\in\mathbb{R}$，使得对于所有$i$，$\sqrt{x_ik_{G_i}}=\frac{\lambda}{\sqrt{x_i}}$。这意味着，对所有$i$，$x_i\propto \frac{1}{\sqrt{k_{G_i}}}$。

又由$S=x(\sum \sqrt{k_{G_i}})^2$，最终我们不难得到：
$$x_i=\frac{x\sum \sqrt{k_{G_i}}}{\sqrt{k_{G_i}}}$$

这样，对于$G$的所有子电阻网络$G'$，递归地计算出$k_{G'}$，再根据上述不等式的取等条件构造出每一个电阻对应的电阻。

可以用long double储存变量，最后设定$eps$来判断是否每个电阻的阻值都是整数即可。如果WA了可以调调$eps$的值。、

细节上，个人建议在输入字符串的每个单独的*前后加入(和），处理时细节会略少。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
#define inf (1ll<<62)
#define eps 1e-6

using namespace std;
typedef long long ll;
typedef long double ld;
const int MAXN = 1000005;
char str[MAXN];
int n,tr,num[MAXN],pi[MAXN],stack[MAXN],nxt[MAXN],top,cnt;
ll rat[MAXN];
ld ans[MAXN];
bool check;
inline ll solve(int l, int r)
{
	if(r-l==2)
	    return 1;
	bool now = str[pi[l+1]+1]=='S';
	vector<ll> tmp;
	int pos = l+1;
	while(pos!=r)
	{
		rat[pos] = solve(pos,pi[pos]);
        tmp.push_back(rat[pos]);
	    pos = nxt[pi[pos]+1];
	}
	ll sum = 0, mina = inf;
	for(int i = 0; i<tmp.size(); i++)
	    sum += floor(sqrt(tmp[i])), mina = min(mina,tmp[i]);
	return now?mina:(sum*sum);
}
inline void construct(int l, int r, ld rr)
{
	if(rr<eps&&rr>-eps)
	    return;
	if(r-l==2)
	{
	    ans[num[l+1]] = rr;
	    return;
	}
	bool now = str[pi[l+1]+1]=='S';
	int pos = l+1;
	vector<ll> tmp;
	while(pos!=r)
	{
        tmp.push_back(pos);
        pos = nxt[pi[pos]+1];
    }
    ll sum = 0, mina = inf, minpos = 0;
    for(int i = 0; i<tmp.size(); i++)
    {
        sum += floor(sqrt(rat[tmp[i]]));
        if(rat[tmp[i]]<mina)
            mina = rat[tmp[i]], minpos = tmp[i];
	}
	if(now)
	{
        for(int i = 0; i<tmp.size(); i++)
            construct(tmp[i],pi[tmp[i]],rr*(tmp[i]==minpos));
    }
	else
        for(int i = 0; i<tmp.size(); i++)
            construct(tmp[i],pi[tmp[i]],rr*sum/floor(sqrt(rat[tmp[i]])));
}

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        scanf("%d",&tr);	
        char c = 0;
        n = cnt = 0;
		while(1)
	    {
	        c = getchar();
	        if(c=='\r'||c=='\n')
	            break;
	        if(c==' ')
	            continue;
	        if(c=='*')
			    str[++cnt] = '(', str[++cnt] = c, str[++cnt] = ')';
			else
			    str[++cnt] = c;
		}
		for(int i = 1; i<=cnt; i++)
		{
	        if(str[i]=='(')
			    stack[++top] = i;
			if(str[i]==')')
			    pi[stack[top--]] = i;
			if(str[i]=='*')
			    num[i] = ++n;
		}
		nxt[cnt+1] = cnt+1;
		for(int i = cnt; i>=1; i--)
		    nxt[i] = (str[i]==')'||str[i]=='(')?i:nxt[i+1];
		check = true;
		solve(1,cnt), construct(1,cnt,tr);
		for(int i = 1; i<=n; i++)
		{
	        ll tmp = (ll)(ans[i]+0.5);
	        if(ans[i]<tmp-eps||ans[i]>tmp+eps)
	            check = false;
		}
		if(check)
		{
		    printf("REVOLTING ");
		    for(int i = 1; i<=n; i++)
	            printf("%lld ",(ll)(ans[i]+eps));
	        printf("\n");
		}
		else
		    printf("LOSS\n");
		for(int i = 1; i<=n; i++)
		    ans[i] = 0;
	}  
	return 0;
}
```


---

## 作者：critnos (赞：1)

初中物理难度233

考虑一个 $n$ 个电阻并联的结构，若要让其阻值为 $R$ 且和最小，很容易猜测得每个电阻阻值为 $nR$。

证明如下：

归纳。$n=1$ 时成立。

$n>1$ 时，设一个电阻的阻值为 $r$，其余的阻值之和应为 $\dfrac {rR(n-1)^2} {r-R}$，和为 $\dfrac {rR(n-1)^2} {r-R}+r$ 即 

设 $t=r-R$，则为

$$R(n+1)^2+\dfrac {R^2(n-1)^2} t+t+R$$

很明显 $t$ 取 $R(n-1)$ 时上式最小，即当 $r=nR$ 时电阻总和最小。证毕。

然后很明显每个电路都等效于一个上述结构，用归纳的思想就是：

* 如果将若干个上述电路并联，显然等价于一个大的上述电路
* 如果将若干个上述电路串联，一个规模为 $n$ 的上述电路代价为 $n^2R$，显然只保留最小的那个就行

括号匹配。

---

## 作者：Mr_Wu (赞：1)

我们先将每个电阻的阻值的限制扩大到**非负实数**。

那么此时就容易证明答案 $f(R)$ 是关于 $R$ 的线性函数，即存在 $c$ 使得 $f(R)=cR$。

所以对于一个串联电阻，它相当于限定 $R=\sum R_i$，求 $\sum c_iR_i$ 的最小值。那我们肯定会选择 $c_i$ 最小的 $i$ 让它承担所有的电阻。所以我们这里得出的结论是串联电阻时会选择其中一块承担所有电阻，其它的地方都是 $0$。

因此，最后的最优解一定可以等效成都是并联的电阻。而我们发现并联的形式只与 $R_i^{-1}$ 有关，简单推导一下就可以发现这可以看成所有电阻都并联在一起。那么此时就是 $R^{-1}=\sum R_i^{-1}$，求 $\sum R_i$ 的最小值，由柯西不等式容易得到 $R_i$ 是全部相等的，且等于参与计算的电阻数。**我们注意到此时 $R_i$ 都是非负整数**。

所以做一个树形 DP 就好了，时间复杂度 $O(n)$。

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
#include<set>
#include<queue>
using namespace std;

typedef long long ll;
const int MAXN=5e5+5;

template<typename T> void chkmax(T& x,T y){if(y>x)x=y;}
template<typename T> void chkmin(T& x,T y){if(y<x)x=y;}

int T,R,stk[MAXN],slen,Tlen,typ[MAXN];
struct node{int v,next;}E[MAXN];int head[MAXN],Elen;
void add(int u,int v){
	++Elen,E[Elen].v=v,E[Elen].next=head[u],head[u]=Elen;
}
int siz[MAXN],wson[MAXN];
void dfs(int u){
	if(typ[u]==-2){
		wson[u]=0;
		for(int i=head[u];i;i=E[i].next){
			dfs(E[i].v);
			if(!wson[u]||siz[E[i].v]<siz[wson[u]])wson[u]=E[i].v;
		}
		siz[u]=siz[wson[u]];
	}else if(typ[u]==-3){
		siz[u]=0;
		for(int i=head[u];i;i=E[i].next)dfs(E[i].v),siz[u]+=siz[E[i].v];
	}else siz[u]=1;
}
void dfs2(int u,bool flag){
	if(typ[u]==0)printf(" %lld",flag?1ll*siz[Tlen]*R:0);
	else if(typ[u]==-2)for(int i=head[u];i;i=E[i].next)dfs2(E[i].v,flag&(E[i].v==wson[u]));
	else for(int i=head[u];i;i=E[i].next)dfs2(E[i].v,flag);
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&R);
		slen=0;Tlen=0;
		char c;
		do{
			c=getchar();
			if(c=='(')stk[++slen]=-1;
			else if(c=='*')stk[++slen]=++Tlen;
			else if(c=='S')stk[++slen]=-2;
			else if(c=='P')stk[++slen]=-3;
			else if(c==')'){
				int tp=0;vector<int> V;
				while(stk[slen]!=-1){
					if(stk[slen]>0)V.push_back(stk[slen]);
					else tp=stk[slen];
					--slen;
				}
				++Tlen;for(int i=0;i<V.size();++i)add(Tlen,V[i]);
				typ[Tlen]=tp;
				--slen,stk[++slen]=Tlen;
			}else continue;
		}while(c!='\n'&&c!=EOF);
		dfs(Tlen);
		printf("REVOLTING");
		dfs2(Tlen,1);
		putchar('\n');
		Elen=0;for(int i=1;i<=Tlen;++i)head[i]=typ[i]=0;
	}
	return 0;
}
```

---

## 作者：清尘 (赞：1)

[My Blog](https://www.cnblogs.com/whx666/p/607-div1.html#e)

对于一个形态固定的电阻网络，设 $g(R)$ 表示电路阻值为 $R$ 时各个电阻阻值和的最小值。把这个带括号的序列对应到树上，要求的就是根节点的 $g$ 函数关系式。更进一步，不难发现 $g$ 其实是一个正比例函数，设 $f(x)$ 为节点 $x$ 处的 $g$ 函数系数。如果没有整数的限制，考虑如何求得 $f$。

1、如果 $x$ 节点的儿子是串联关系，显然，最优的办法是把所有的电阻都加在 $f$ 最小的那个儿子上，其他放空。**即 $f_x=min(f_y)$**

2、如果是串联，列出两个式子，$\frac{1}{R_x}=\sum\frac{1}{R_y}，sum=\sum f_yR_y，y\in son(x)$，由第一个式子可得 $R_x\sum\frac{1}{R_y}=1$，联想到“1”的妙用，把这个东西放入第二个式子：$sum=R_x\sum\frac{1}{R_y}\sum f_yR_y=R_x\sum(\frac{1}{\sqrt{R_y}})^2\sum \sqrt{f_yR_y}^2$。套用柯西不等式的取等条件，当取值最小时有 $\frac{1}{\sqrt{f_yR_y^2}}=m$（$m$ 为定值）。那么 $\frac{1}{R_y}\propto \sqrt{f_y}$，而 $\sum\frac{1}{R_y}$ 为定值，那么 $\frac{1}{R_y}$ 按照比例分配。可得 $R_y=R_x\frac{\sum\sqrt{f_z}}{\sqrt{f_y}}$。**带入可得 $\sqrt{f_x}=\sum\sqrt{f_y}$**

再回来看整数的限制

1、对于叶子节点有 $f_x=1$，是完全平方数

2、对于第一种转移，如果 $f_y$ 全是完全平方数那么 $f_x$ 也一定是

3、对于第二种转移，$f_y$ 是完全平方数，$\sqrt{f_y}$ 是整数，$\sqrt{f_x}$ 是整数，$f_x$ 依然是一个完全平方数

那么，整数的限制作废了

计算具体阻值的时候可以按照构造方法往里面带，更简洁的做法：情况 $1$ 的构造方法意味着多个串联的电阻中只会选一个。根据电路分析的基础知识可以发现，最后选出的电阻都可以看作并联关系，那么看一下有几个电阻用到就可以直接算了

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
void read (int &x) {
    char ch = getchar(); x = 0; while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
} const int N = 2e5 + 5, M = 5e5 + 5;
int n, dfn, st[N], tag[N], to[N], f[N], vis[N], id[N];
char a[M]; vector<int> g[N];
#define pb push_back
void build () {
    int num = 0, tp = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] == '(') {
            g[++num].clear();
            if (tp) g[st[tp]].pb (num);
            st[++tp] = num;
            to[num] = vis[num] = f[num] = 0;
        } else if (a[i] == '*') {
            g[++num].clear();
            if (tp) g[st[tp]].pb (num);
            to[num] = vis[num] = f[num] = 0;
        }
        else if (a[i] == 'S') tag[st[tp]] = 0;
        else if (a[i] == 'P') tag[st[tp]] = 1;
        else if (a[i] == ')') --tp;
    }
}
void dfs (int u) {
    if (!g[u].size()) { f[u] = 1, id[u] = ++dfn; return; }
    for (int v : g[u]) dfs (v);
    if (tag[u] == 0) { // 串联直接找系数最小的
        int mn = 0;
        for (int v : g[u]) if (f[mn] > f[v]) mn = v;
        to[u] = mn, f[u] = f[mn];
    } else { // 串联直接加和
        for (int v : g[u]) f[u] += f[v];
    }
} int cnt;
void getcnt (int u) {
    if (!g[u].size()) { vis[id[u]] = 1, ++cnt; return; }
    if (!tag[u] && to[u]) getcnt (to[u]);
    else for (int v : g[u]) getcnt (v);
}
signed main() {
    int T; read (T);
    while (T--) {
        int R; scanf ("%lld", &R);
        cin.getline (a, 5e5); n = strlen (a + 1);
        build (); f[0] = 2e9;
        dfn = 0, dfs (1);
        cnt = 0; getcnt (1);
        printf ("REVOLTING ");
        for (int i = 1; i <= dfn; ++i)
            printf ("%lld ", vis[i] ? cnt * R : 0ll);
        putchar ('\n');
    }
    return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

对于每一对括号（或 `*`），考虑至少让 $r_x$ 增加多少才能使得这对括号两端的阻值增加 $1$，设其为 $rmin_i$。

对于串联电路，阻值等于其所有分叉开来的其他子电路阻值之和。要使这里阻值为 $1$，就要让 $rmin_x$ 的系数之和到 $1$。显然取 $rmin_x$ 最小的 $x$ 系数为 $1$ 最优。即 $rmin_i=\min rmin_x$。此时，这一段串联电路等价于单个 $rmin_x$ 最小位置 $x$ 的子电路。进行若干次等价后，会等价成一个并联电路（或并联电路套串联电路，最外层一定是并联电路）。

对于并联电路，阻值等于其所有分叉开来的其他子电路阻值倒数和的倒数。由于每一部分都是并联电路，将多个并联电路并联起来可以等价于将这些并联电路的所有组成部分全部并联到一起。从底层依次拆并联电路，串联电路，即可发现最后整个电路的最优状态可以被等价为多个单个电阻并联在一起。

此时，显然给每个电阻 $r$ 的阻值可以使得总阻值为 $r$ 且电阻阻值和最小。

于是在括号树上 dfs 一遍计算 $rmin_x$ 后逐层进入构造即可。总复杂度 $O(|S|)$，$|S|$ 为字符串长度。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define lowbit(i) (i&(-i))
using namespace std;
string s,t;
int tor[1000005],tol[1000005],stk[1000005],top;
map<pair<int,int>,pair<int,int>> mp;
int solve(int l,int r){
	if(l==r){
		return 1;
	}
	vector<pair<int,int>> vc;
	int tp=0;
	for(int i=l;i<=r;i++){
		if(t[i]=='('){
			vc.push_back(make_pair(i+1,tor[i]-1));
			i=tor[i];
		}
		else if(t[i]=='*'){
			vc.push_back(make_pair(i,i));
		}
		else{
			if(t[i]=='S') tp=0;
			else tp=1;
		}
	}
	if(tp==0){
		int ans=1e9;
		for(auto v:vc){
			int p=solve(v.first,v.second);
			if(p<ans){
				ans=p;
				mp[make_pair(l,r)]=v;
			}
		}
		return ans;
	}
	else{
		int ans=0;
		for(auto v:vc){
			int p=solve(v.first,v.second);
			ans+=p;
		}
		return ans;
	}
}
void print(int l,int r,int val){
	if(l==r){
		cout<<val<<" ";
		return ;
	}
//	cout<<l<<" "<<r<<" "<<mp[make_pair(l,r)].first<<" "<<mp[make_pair(l,r)].second<<"\n";
	vector<pair<int,int>> vc;
	int tp=0;
	for(int i=l;i<=r;i++){
		if(t[i]=='('){
			vc.push_back(make_pair(i+1,tor[i]-1));
			i=tor[i];
		}
		else if(t[i]=='*'){
			vc.push_back(make_pair(i,i));
		}
		else{
			if(t[i]=='S') tp=0;
			else tp=1;
		}
	}
	if(tp==0){
		for(auto v:vc){
			if(v==mp[make_pair(l,r)]){
				print(v.first,v.second,val);
			}
			else{
				print(v.first,v.second,0);
			}
		}
	}
	else{
		for(auto v:vc){
			print(v.first,v.second,val);
		}
	}
}
signed main(){
	int T; cin>>T;
	while(T--){
		int r; cin>>r;
		t="";
		int nowb=0;
		while(1){
			cin>>s;
			t+=s;
			for(int i=0;i<s.size();i++){
				if(s[i]=='(') nowb++;
				else if(s[i]==')') nowb--;
			}
			if(nowb==0) break;
		}
		if(t[0]=='(') t=t.substr(1,t.size()-2);
		int n=t.size(); t=" "+t;
		for(int i=1;i<=n;i++){
			if(t[i]=='(') stk[++top]=i;
			else if(t[i]==')'){
				tol[i]=stk[top];
				tor[stk[top]]=i;
				top--;
			}
		}
		int ans=solve(1,n);
		cout<<"REVOLTING ";
		print(1,n,r*ans);
		cout<<"\n";
	}
	return 0;
}
```

---

