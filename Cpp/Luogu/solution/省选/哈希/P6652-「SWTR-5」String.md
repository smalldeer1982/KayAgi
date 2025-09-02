# 「SWTR-5」String

## 题目描述

小 A 有一个字符串 $t$。他可以进行以下操作：切掉 $t$ 的一个前/后缀，满足切掉的前/后缀为**切割后** $t$ 的子串。小 A 想得到字符串 $s$，请问他最少需要进行多少次操作。无解输出 $-1$。

## 说明/提示

「样例说明」

样例 $1$：$\texttt{abbabb}\to \texttt{abba}\to \texttt{bba}\to \texttt{ba}$。方案不唯一。

样例 $2$：$\texttt{fxofoxxooffoxooo}\to\texttt{xofoxxooffoxooo}\to\texttt{foxxooffoxooo}\to\texttt{xooffoxooo}\to\texttt{ffoxooo}\to\texttt{ffoxoo}\to\texttt{ffoxo}\to\texttt{ffox}\to\texttt{fox}$。方案不唯一。

「数据范围与约定」

**本题采用捆绑测试。**

- Subtask 1（1 points）：$s=t$。
- Subtask 2（9 points）：$s$ 仅包含字母 $\texttt{a}$。
- Subtask 3（15 points）：$|t|\leq 100$。
- Subtask 4（17 points）：$|t|\leq 500$。
- Subtask 5（18 points）：$|t|\leq 1.5\times 10^3$。
- Subtask 6（15 points）：$|s|=4$，*数据随机。
- Subtask 7（25 points）：无特殊限制。

对于 $100\%$ 的数据：$1 \leq |s| \leq |t| \leq 5\times 10^3$，字符集 $\in[\texttt{a,z}]$。

*数据随机：$s,t$ 字符均随机，字符集 $\in[\texttt{a,c}]$。

**请注意常数优化。**

---

「题目来源」

[Sweet Round 05](https://www.luogu.com.cn/contest/28195) E。    
idea & solution：[Isaunoya](https://www.luogu.com.cn/user/96580) & [Alex_Wei](https://www.luogu.com.cn/user/123294)。

## 样例 #1

### 输入

```
abbabb
ba```

### 输出

```
3```

## 样例 #2

### 输入

```
fxofoxxooffoxooo
fox```

### 输出

```
8```

## 样例 #3

### 输入

```
abcdefghijklmnopq
rstuvwxyzz```

### 输出

```
-1```

## 样例 #4

### 输入

```
ycxcy
cxy```

### 输出

```
-1```

# 题解

## 作者：Alex_Wei (赞：6)

> [题面传送门](https://www.luogu.com.cn/problem/P6652)。

> 题意简述：给定两个字符串 $s,t$。每次可以切除 $t$ 的一个前/后缀并保证其为切割后的 $t$ 的子串。求得到 $s$ 的最少操作数或给出无解。

题目可以理解为：每次操作将 $s$ 的一个子串拼在其前/后。求得到 $t$ 的最少操作数。

---

一些约定：

设 $m=|s|,n=|t|$。设区间 $[l,r]$ 为 $t$ 的第 $l$ 位至第 $r$ 位字符组成的字符串。

- 如何判断无解：如果 $s$ 没有在 $t$ 中出现，**或者** $t$ 出现了 $s$ 没有的字母，即无解。可以 $O(n^2)$ 暴力判断，也可以 $O(n)$ KMP 求解。std 使用 $O(n^2)$ 暴力判断。

---

Subtask $1$：$s=t$。

输出 $0$ 即可。

Subtask $2$：$s$ 仅包含小写字母 $\texttt{a}$。

先判断是否无解，否则答案为最小的满足 $m\times 2^c\geq n$ 成立的整数 $c$。

Subtask $3$：$n\leq 100$。

区间 DP。设 $f_{i,j}$ 为 $s$ 扩展到区间 $[l,r]$ 的最少步数。转移时枚举粘贴字符串的长度，暴力匹配。枚举 $l,r:O(n^2)$，转移枚举长度 $:O(n)$，暴力匹配 $:O(n)$。时间复杂度 $O(n^4)$，常数极小。

Subtask $4$：$n\leq 500$。

将暴力匹配改成字符串哈希即可做到 $O(1)$ 匹配。总时间复杂度 $O(n^3)$，常数较小。

如果实现精细 + 极小常数，$O(n^4)$ 也许可以暴力艹过去。

Subtask $5$：$n\leq 1.5\times 10^3$。

验题人 @[chenxia25](https://www.luogu.com.cn/user/138400) 给出的算法时间复杂度为 $n^2\log n$。这里放上他的原话（有删减）：

“如果已经算出了 $f_{l,r}$，考虑它能影响哪些更大的区间的 $f$ 值。显然只能从两端扩展。”

“以往左为例，能扩展到 $l'$（能影响 $f_{l',r}$）当且仅当 $[l',l-1]$ 是 $[l,r]$ 的子串。那么所有 $l'$ 显然构成区间。”

“用 $z$ 算法算出 $t$ 中两两点的 LCS，区间 RMQ 即可得到最小的 $l'$，然后线段树区间更新维护。”

“还有一个小小的优化方法可以把它弄成 BIT。”

这里给出他的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
int lowbit(int x){return x&-x;}
const int N=1500,M=1500;
int n,m;
char a[N+5],b[M+5];
int cov[N+1][M+1];
int lcP[N+1][M+1],Lcs[M+1][M+1];
int s;
char c[N+M+6];
void con(char s1[],int p1,int l1,char s2[],int p2,int l2){
	s=0;
	for(int i=p1;i<=l1;i++)c[++s]=s1[i];
	c[++s]='!';
	for(int i=p2;i<=l2;i++)c[++s]=s2[i];
}
int z[N+M+2];
void z_init(){
	z[1]=s;
	int zl=0,zr=0;
	for(int i=2;i<=s;i++)
		if(zr<i){
			z[i]=0;
			while(i+z[i]<=s&&c[i+z[i]]==c[1+z[i]])z[i]++;
			if(z[i])zl=i,zr=i+z[i]-1;
		}
		else if(i+z[i-zl+1]<=zr)z[i]=z[i-zl+1];
		else{
			z[i]=zr-i+1;
			while(i+z[i]<=s&&c[i+z[i]]==c[1+z[i]])z[i]++;
			zl=i;zr=i+z[i]-1;
		}
}
struct bitree{
	int val[M+2],mn[M+1];
	void init(){memset(val,0x3f,sizeof(val));memset(mn,0x3f,sizeof(mn));}
	void chkmn(int x,int v){
		if(v>=val[x])return;
		val[x]=v;
		while(x<=m)mn[x]=min(mn[x],v),x+=lowbit(x);
	}
	int Mn(int x){
		int res=inf;
		while(x)res=min(res,mn[x]),x-=lowbit(x);
		return res;
	}
}bit[M+1],bitr[M+1];
int lft[M+1][M+1],rit[M+1][M+1];
int dp[M+1][M+1];
int main(){
	cin>>b+1>>a+1;
	n=strlen(a+1);m=strlen(b+1);
	con(a,1,n,b,1,m);z_init();
	for(int i=1;i<=m;i++)if(z[n+1+i]==n)cov[i][i+n-1]=true;
	for(int i=1;i<=m;i++){
		con(b,i,m,b,1,m);z_init();
		for(int j=1;j<=m;j++)lcP[i][j]=z[m-i+1+1+j];
	}
	reverse(b+1,b+m+1);
	for(int i=1;i<=m;i++){
		con(b,i,m,b,1,m);z_init();
		for(int j=1;j<=m;j++)Lcs[m-i+1][m-j+1]=z[m-i+1+1+j];
	}
	for(int i=1;i<=m;i++)bit[i].init(),bitr[i].init();
	for(int i=m;i;i--)for(int j=i;j<=m;j++){
		dp[i][j]=cov[i][j]?0:min(bit[j].Mn(i),bitr[i].Mn(m-j+1));
		bit[j].chkmn(i-(lft[i][j]=max(lft[i][j-1],min(Lcs[j][i-1],j-i+1))),dp[i][j]+1);
		bitr[i].chkmn(m-(j+(rit[i][j]=max(rit[i+1][j],min(lcP[i][j+1],j-i+1))))+1,dp[i][j]+1);
	}
	cout<<(dp[1][m]==inf?-1:dp[1][m]);
	return 0;
}
```

Subtask $6$：$|s|=4$，数据随机。

留给乱搞。

Subtask $7$：$n\leq 5\times 10^3$。

不妨换个思路，设 $f_{l,r}$ 为区间 $[l,r]$ 往左边（即头部）能粘贴的子串长度最大值，$g_{l,r}$ 为区间 $[l,r]$ 往右边（即尾部）能粘贴的子串长度最大值。

如果求出了 $f$ 和 $g$，我们可以通过一遍 BFS 求出答案。BFS 具体实现方法见代码，这里不再赘述。

- 如何预处理 $f,g$？

   回忆一下 $f,g$ 的定义：区间 $[l,r]$ 往左/右能粘贴的子串长度最大值。如果认真思考，就能发现 $f_{l,r}$ 一定不小于 $f_{l,r-1}(l<r)$，因为区间 $[l,r-1]$ 能往左粘贴的子串，区间 $[l,r]$ 也一定能做到，其长度就具有单调性。$g$ 同理。合理运用单调性和字符串哈希，就能在 $O(n^2)$ 的时间内计算 $f,g$。

预处理 $f,g$ 时间复杂度 $O(n^2)$，BFS 时间复杂度 $O(n^2)$。时间复杂度 $O(n^2)$。

- 应评论区补充一点：不难发现每次扩展的长度越大越好。感性理解一下，类似上面 $f_{l,r}$ 一样，区间 $[l,r]$ 能够扩展的长度一定不小于 $[l+1,r]$ 或 $[l,r-1]$。

- 另外也可以直接 DP 求答案，按照区间长度从小到大扩展即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ull unsigned long long
#define int short
#define pii pair <int,int>
#define fi first
#define se second

const int N=5e3+5;
const int bs=131;

ull hs[N],pw[N];
ull cal(int l,int r){return hs[r]-hs[l-1]*pw[r-l+1];}

string s,t;
int f[N][N],g[N][N],dp[N][N],n;
queue <pii> q;

signed main(){
	cin>>t>>s,n=t.size(); if(s==t)puts("0"),exit(0);
	
	pw[0]=1; for(int i=1;i<=n;i++)pw[i]=pw[i-1]*bs;
	for(int i=0;i<n;i++)hs[i+1]=hs[i]*bs+(t[i]-'a');
	
	for(int i=1;i<=n;i++){
		int tmp=1;
		for(int j=i;j<=n;j++){
			while(tmp<i&&j-tmp+1>=i&&cal(i-tmp,i-1)==cal(j-tmp+1,j))tmp++;
			f[i][j]=tmp-1;
		} tmp=1;
		for(int j=i;j;j--){
			while(i+tmp<=n&&j+tmp-1<=i&&cal(j,j+tmp-1)==cal(i+1,i+tmp))tmp++;
			g[j][i]=tmp-1;
		}
	}
	
	int pos=t.find(s); if(pos==-1)puts("-1"),exit(0);
	while(pos!=-1)q.push({pos+1,pos+s.size()}),pos=t.find(s,pos+1);
	while(!q.empty()){
		int l=q.front().fi,r=q.front().se,dl=f[l][r],dr=g[l][r],d=dp[l][r]; q.pop(); 
		if(dl!=0){l-=dl; if(!dp[l][r])dp[l][r]=d+1,q.push({l,r}); l+=dl;}
		if(dr!=0){r+=dr; if(!dp[l][r])dp[l][r]=d+1,q.push({l,r}); r-=dr;}
	}
	cout<<(dp[1][n]?dp[1][n]:-1)<<endl; 
	return 0;
}
```

---

## 作者：HC20050615 (赞：1)

# 题意分析
本题可以等价为将一个字符串 $s$ 前后不断添加其子串,求使之变为 $t$ 的最小操作步数。

# 解题思路
首先，我们可以感觉到每次添加的字串最长时，所需步数会最少。若某一次没有添加最长的字串，其往后可以添加的子串一定不长于本次添加最长字串往后可添加的字串长，答案必然不优。（~~还是感性理解，感觉不太好说明~~）

然后，我们就想要求每次能最长扩展多长。我们令 $f_{i,j}$ 表示 $t_{i,j}$ 往左最远可以扩展多长，我们考虑如何转移：

1. 由上一段我们可知 $f_{i,j} \ge f_{i,j-1}$。

2. 若要使 $f_{i,j}>f_{i,j-1}$，所添加的子串一定为 $s_{i,j}$ 的后缀。因为非后缀的子串在 $f_{i,1\sim j-1}$，一定被尝试过扩展了，由于左端点未改变，其能扩展的最远距离没有变化。于是，我们可以从子串长度为 $f_{i,j}$ 开始暴力枚举，利用字符串哈希来判断字串相等。由于我们的字串长度只会增加不会减少，故时间复杂度为 $O(n^2)$ 。

同理，我们可以预处理出 $g_{i,j}$ 表示 $t_{i,j}$ 往右最远可以扩展多长。

接着，我们可以使用DP或bfs来求出答案。这里使用的是bfs。我们先利用字符串哈希暴力匹配 $t$，并将匹配到的位置丢进队列，每次扩展即可。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
int n,m;
int Hash[3][5001];
int has[3];
int base=29;
int mod1=1145141;
int mod2=998244353;
int f[5001][5001];
int g[5001][5001];
int p[3][5001];
inline bool judge(int x1,int y1,int x2,int y2)
{
	return (Hash[1][y1]-(long long)Hash[1][x1-1]*p[1][y1-x1+1]%mod1+mod1)%mod1==(Hash[1][y2]-(long long)Hash[1][x2-1]*p[1][y2-x2+1]%mod1+mod1)%mod1&&(Hash[2][y1]-(long long)Hash[2][x1-1]*p[2][y1-x1+1]%mod2+mod2)%mod2==(Hash[2][y2]-(long long)Hash[2][x2-1]*p[2][y2-x2+1]%mod2+mod2)%mod2;
}
struct State{
	int x,y;
	int cnt;
};
bool vis[5001][5001];
queue<State>q;
int main()
{
	p[1][0]=1;
	p[2][0]=1;
	for(int i=1;i<=5000;i++)
	{
		p[1][i]=(long long)p[1][i-1]*base%mod1;
		p[2][i]=(long long)p[2][i-1]*base%mod2;
	}
	cin>>s>>t;
	n=s.length();
	m=t.length();
	s=" "+s;
	t=" "+t;
	for(int i=1;i<=n;i++)
	{
		Hash[1][i]=((long long)Hash[1][i-1]*base+s[i]-'a'+1)%mod1;
		Hash[2][i]=((long long)Hash[2][i-1]*base+s[i]-'a'+1)%mod2;
	}
	for(int i=1;i<=m;i++)
	{
		has[1]=((long long)has[1]*base+t[i]-'a'+1)%mod1;
		has[2]=((long long)has[2]*base+t[i]-'a'+1)%mod2;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			f[i][j]=f[i][j-1];
			if(judge(j-f[i][j],j,i-f[i][j]-1,i-1))
			{
				int x=j-f[i][j],y=i-f[i][j]-1;
				while(y>=1&&x>=i&&s[x]==s[y])
				{
					f[i][j]=j-x+1;
					x--;
					y--;
				}
			}
		}
		for(int j=i;j>=1;j--)
		{
			g[j][i]=g[j+1][i];
			if(judge(j,j+g[j][i],i+1,i+g[j][i]+1))
			{
				int x=j+g[j][i],y=i+g[j][i]+1;
				while(y<=n&&x<=i&&s[x]==s[y])
				{
					g[j][i]=x-j+1;
					x++;
					y++;
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		int j=i+m-1;
		if((Hash[1][j]-(long long)Hash[1][i-1]*p[1][j-i+1]%mod1+mod1)%mod1==has[1]&&(Hash[2][j]-(long long)Hash[2][i-1]*p[2][j-i+1]%mod2+mod2)%mod2==has[2])
		{
			q.push(State{i,j,0});
		}
	}
	int ans=0x7fffffff;
	while(!q.empty())
	{
		State t=q.front();
		q.pop();
		//cout<<t.x<<" "<<t.y<<endl;
		if(t.x==1&&t.y==n)
		{
			ans=min(ans,t.cnt);
		}
		if(f[t.x][t.y])
		{
			if(!vis[t.x-f[t.x][t.y]][t.y])
			{
				vis[t.x-f[t.x][t.y]][t.y]=1;
				q.push(State{t.x-f[t.x][t.y],t.y,t.cnt+1});
			}
		}
		if(g[t.x][t.y])
		{
			if(!vis[t.x][t.y+g[t.x][t.y]])
			{
				vis[t.x][t.y+g[t.x][t.y]]=1;
				q.push(State{t.x,t.y+g[t.x][t.y],t.cnt+1});
			}	
		}
	}
	if(ans==0x7fffffff)
	{
		cout<<-1<<endl;
	}
	else
	{
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Reunite (赞：0)

考虑先预处理两个数组 $a_{l,r},b_{l,r}$ 分别表示 $t_{[l,r]}$ 在 $r$ 之后和在 $l$ 之前最近的出现位置，对于当前截取的子串 $[l,r]$，就可以 $O(1)$ 判断 $[l,i]/[i,r]$ 是否可以截断。

有一个显然的区间 dp，设 $f_{l,r}$ 为截取得到 $t_{[l,r]}$ 的最小次数，每次暴力枚举下一次断点转移，这是 $O(n^3)$ 的，但是我们注意到每次的最小次数变化量为 $1$，所以把 dp 扬了，换成 bfs，这样我们的复杂度就是状态数的 $O(n^2)$ 了。

显然不行啊，bfs 枚举下一个状态还是 $O(n^3)$ 的，但是我们发现有大量状态被重复遍历了，考虑用并查集把所有已达状态缩起来，保证每个状态至多只会被访问到一次，复杂度就正确了。

考虑预处理怎么做，直接扫，维护前后缀哈希值即可，但是常数很大。我们可以按照 $len$ 的顺序枚举，这样就可以把哈希表中的元素个数降到 $O(n)$，速度也可以大大提升。然后发现空间爆了，把 $\text{int}$ 换成 $\text{short}$ 就好。最后复杂度是 $O(n^2)$，我跑的很极限。


```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define mod 9191891
#define ll unsigned long long
using namespace std;

int n,m,cnt;
ll hs[5005];
ll bin[5005];
char t[5005];
char s[5005];
short a[5005][5005];
short b[5005][5005];
short f[5005][5005];
short h[9191891];
struct node{ll h;int v,nxt;}edge[5005];
struct DSU{
	short fa[5005];
	inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
}L[5005],R[5005];
queue <pair <int,int>> q;

inline ll get(int l,int r){return hs[r]-hs[l-1]*bin[r-l+1];}

inline int Find(ll x){
	for(int i=h[x%mod];i;i=edge[i].nxt)
		if(edge[i].h==x) return i;
	return 0;
}

inline void add(ll x,int k){
	int xx=Find(x);
	if(xx) edge[xx].v=k;
	else{
		edge[++cnt]={x,k,h[x%mod]};
		h[x%mod]=cnt;
	}
	return ;
}

inline void upd(int l,int r,int x){
	f[l][r]=x;
	R[r].fa[l]=l+1;
	L[l].fa[r]=r-1;
	q.push({l,r});
	return ;
}

signed main(){
	// freopen("qwq.in","r",stdin);
	scanf("%s",t+1);
	scanf("%s",s+1);
	n=strlen(t+1),m=strlen(s+1);
	ll hh=0;
	for(int i=1;i<=m;i++) hh=hh*131+s[i];
	bin[0]=1;
	for(int i=1;i<=n;i++) bin[i]=bin[i-1]*131,hs[i]=hs[i-1]*131+t[i];
	for(int len=1;len<=n;len++){
		for(int i=n-len+1;i>=len;i--){
			int v=Find(get(i-len+1,i));
			if(v) a[i-len+1][i]=edge[v].v;
			add(get(i,i+len-1),i+len-1);
		}
		while(cnt) h[edge[cnt].h%mod]=0,cnt--;
		for(int i=len;i<=n-len+1;i++){
			int v=Find(get(i,i+len-1));
			if(v) b[i][i+len-1]=edge[v].v;
			add(get(i-len+1,i),i-len+1);
		}
		while(cnt) h[edge[cnt].h%mod]=0,cnt--;
	}
	q.push({1,n});
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++) R[i].fa[j]=j;
		for(int j=i;j<=n;j++) L[i].fa[j]=j;
	}
	memset(f,-1,sizeof(f));
	f[1][n]=0;
	while(!q.empty()){
		int l=q.front().first,r=q.front().second;
		q.pop();
		if(r-l+1<=m) continue;
		int u;
		u=R[r].Find(l+1);
		while(u<=r&&a[l][u-1]&&a[l][u-1]<=r){
			upd(u,r,f[l][r]+1);
			u=R[r].Find(u+1);
		}
		u=L[l].Find(r-1);
		while(u>=l&&b[u+1][r]&&b[u+1][r]>=l){
			upd(l,u,f[l][r]+1);
			u=L[l].Find(u-1);
		}
	}
	short ans=1e4;
	for(int i=1;i+m-1<=n;i++) if(get(i,i+m-1)==hh) ans=min(ans,f[i][i+m-1]);
	printf("%hd\n",ans==1e4?-1:ans);

	return 0;
}

```

---

