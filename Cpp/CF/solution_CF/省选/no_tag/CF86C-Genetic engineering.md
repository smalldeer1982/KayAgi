# Genetic engineering

## 题目描述

"Multidimensional spaces are completely out of style these days, unlike genetics problems" — thought physicist Woll and changed his subject of study to bioinformatics. Analysing results of sequencing he faced the following problem concerning DNA sequences. We will further think of a DNA sequence as an arbitrary string of uppercase letters "A", "C", "G" and "T" (of course, this is a simplified interpretation).

Let $ w $ be a long DNA sequence and $ s_{1},s_{2},...,s_{m} $ — collection of short DNA sequences. Let us say that the collection filters $ w $ iff $ w $ can be covered with the sequences from the collection. Certainly, substrings corresponding to the different positions of the string may intersect or even cover each other. More formally: denote by $ |w| $ the length of $ w $ , let symbols of $ w $ be numbered from $ 1 $ to $ |w| $ . Then for each position $ i $ in $ w $ there exist pair of indices $ l,r $ ( $ 1<=l<=i<=r<=|w| $ ) such that the substring $ w[l ... r] $ equals one of the elements $ s_{1},s_{2},...,s_{m} $ of the collection.

Woll wants to calculate the number of DNA sequences of a given length filtered by a given collection, but he doesn't know how to deal with it. Help him! Your task is to find the number of different DNA sequences of length $ n $ filtered by the collection $ {s_{i}} $ .

Answer may appear very large, so output it modulo $ 1000000009 $ .

## 说明/提示

In the first sample, a string has to be filtered by "A". Clearly, there is only one such string: "AA".

In the second sample, there exist exactly two different strings satisfying the condition (see the pictures below).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF86C/a2747d198b5b8c3f293a2427e852f84624a28036.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF86C/305d8cf545ebc4a6c53c7d783f927c1d0b9d6efd.png)

## 样例 #1

### 输入

```
2 1
A
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6 2
CAT
TACT
```

### 输出

```
2
```

# 题解

## 作者：whiteqwq (赞：6)

[CF86C Genetic engineering](https://www.luogu.com.cn/problem/CF86C)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1769451)

## 题意
- 给定$n$个由ATCG组成的字符串，求构造一个长度为$m$的字符串，使得所有字符串可以通过匹配覆盖整个新字符串，求方案总数。
- $1\leqslant n\leqslant 10,1\leqslant m\leqslant 10^3$，给出的串长不超过$10$，对$10^9+7$取模。

## 分析
一道较套路的AC自动机dp题，但我没想出来/kk。

考虑先对所有给出的字符串建出AC自动机。

套路地设状态$f_{i,j}$为在AC自动机上匹配到了位置$j$，且已经用了$i$个字符的方案总数。

我们发现在AC自动机上转移边分为trie树上原有的转移边和AC自动机添加的转移边，考虑直接在上面dp，可以正常进行trie树边的转移，对于AC自动机的转移，我们能转移当且仅当当前结点是一个字符串结束位置。

上面的转移方式乍一看好像没错，因为转移AC自动机添加的转移边时需要跳fail边，变成原来匹配串的后缀，因此会让一些没有覆盖的点无法覆盖。

但是我们考虑一种情况：先通过trie树上的匹配到了一个结束位置$x$，然后往下跳一次trie树边，并跳一次AC自动机添加的转移边，最后再跳一次到了另一个位置较深的结束位置。

这样这个结束位置的长度足以覆盖前面没有覆盖的内容，这种方式仍然是合法的。

也就是说，**我们跳fail边时，可能去除的前缀已经覆盖过了**，因此这样的状态是不能转移的。

考虑另一种状态设计方式：$f_{i,j,k}$表示在AC自动机上匹配到了位置$k$，用了$i$个字符，且后$j$个字符还没有覆盖的方案数。

我们定义一个辅助数组$len_x$，表示到了AC自动机上的位置$x$，以$x$为结尾的最长字符串长度为多少。

这样的转移也非常清晰：我们当前的状态为$i,j,k$，通过AC自动机的转移边（无论是trie树边还是AC自动机新添加的转移边）转移到了点$x$，那么我们有：

- 当$len_x>j$时，$f_{i,j,k}\rightarrow f_{i+1,0,x}$
- 否则，$f_{i,j,k}\rightarrow f_{i+1,j+1,x}$

时间复杂度：$O(nm|S|)$。

## 代码
```
#include<stdio.h>
#include<iostream>
#include<queue>
using namespace std;
const int maxn=105,maxk=4,maxl=12,mod=1000000009,maxm=1005;
int n,m,tot,ans,maxlen;
int chd[maxn][maxk],fail[maxn],f[maxm][maxl][maxn],dep[maxn],len[maxn];
string s;
queue<int>q;
inline int get(char c){
	return c=='A'? 0:(c=='C'? 1:(c=='G'? 2:3));
}
void insert(string s){
	int now=1;
	for(int i=0;i<s.size();now=chd[now][get(s[i])],i++)
		if(chd[now][get(s[i])]==0)
			chd[now][get(s[i])]=++tot,dep[tot]=dep[now]+1;
	len[now]=dep[now];
}
void getfail(){
	while(!q.empty())
		q.pop();
	for(int i=0;i<=3;i++){
		if(chd[1][i])
			q.push(chd[1][i]),fail[chd[1][i]]=1;
		else chd[1][i]=1;
	}
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=0;i<=3;i++){
			if(chd[x][i])
				q.push(chd[x][i]),fail[chd[x][i]]=chd[fail[x]][i];
			else chd[x][i]=chd[fail[x]][i];
		}
		len[x]=max(len[x],len[fail[x]]);
	}
}
void dp(){
	f[0][0][1]=1;
	for(int i=0;i<m;i++)
		for(int j=0;j<=maxlen;j++)
			for(int k=1;k<=tot;k++)
				if(f[i][j][k])
					for(int p=0;p<=3;p++){
						int x=chd[k][p];
						if(len[x]>j)
							f[i+1][0][x]=(f[i+1][0][x]+f[i][j][k])%mod;
						else f[i+1][j+1][x]=(f[i+1][j+1][x]+f[i][j][k])%mod;
					}
}
int main(){
	tot=1;
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++){
		cin>>s,maxlen=max(maxlen,(int)s.size());
		insert(s);
	}
	getfail();
	dp();
	for(int i=1;i<=tot;i++)
		ans=(ans+f[m][0][i])%mod;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：chen_qian (赞：4)

首先我们来考虑当我们已知一种方案满足题意要求，我们如何在 AC 自动机上匹配其每个位置 $i$ 所对应的是哪个串。显然是在 trie 树上遍历，对于遍历到的每一个节点 $x$ 在 fail 树上找祖先，看能不能找到一个是字符串集 $S$ 中的字符串的结尾节点，如果找到了这样一个节点，这个节点对应字符串是 $s$。那么其可以覆盖 $x-|s|\dots x$ 这个区间上的节点。所以当我们判断字符串前 $x$ 个是否被完全覆盖时，我们只需要知道这前 $x$ 个的后缀有多长是没有被覆盖的，然后我们再与当前匹配到的完整的字符串的长度作比较。加入匹配到的字符串太短，无法完全覆盖整个后缀，那么就不能选它。

所以我们就可以定义 $f_{i,j,k}$ 表示我们现在需要匹配的是前 $i$ 个字符，并且这个字符串的后缀状态是 trie 树上的 $k$， $i$ 个字符的长度为 $j$ 的后缀没有被覆盖。

对于现在的 $k$ 节点，如果他是其是一个字符串的结尾，那么他可以使用它本身的代表的字符串来尝试覆盖 $j$ 的长度，但对于更一般的情况，对于任意节点 $k$，我们还可以使用其对应的 fail 指针指向的节点。假如指向的节点是一个字符串的结尾，那么我们可以尝试使用指向节点对应的字符串来尝试来覆盖。对于两种情况都兼备的节点，取更长的一个即可，我们把这个长度记为 $len_x$。然后在 insert 和 build 的时候处理一下即可。对于现在的状态 $f_{i,j,k}$ 假设我们枚举出我们走到 $x$ 节点 (其实，这就是决策，第 $i+1$ 位填什么，先枚举出来再考虑是否可行）。

那么我们可以给出以下状态转移

- $len_x \ge k+1\ $ $ f_{i,j,k} \Rightarrow f_{i+1,0,x}$

- $len_x < k+1\ $ $ f_{i,j,k} \Rightarrow f_{i+1,j+1,x}$

那么就有

$$\boxed{ans=\sum\limits_{i=0}^{tot}f_{n,0,i}}$$

代码有所参考

```cpp
#include<bits/stdc++.h>
#define mod 1000000009
#define N 15
using namespace std;
int get(char c){
	return c=='A'? 0:(c=='C'? 1:(c=='G'? 2:3));
}
int n,m,dep[N*100],len[1500],ch[N*100][26],fail[N*100],tot,mlen=0;
char s[N];
int f[N*100][N][N*100];
void insert(char *s){
	int slen=strlen(s);
	mlen=max(mlen,slen);
	int x=0;
	for(int i=0;i<slen;i++){
		int k=get(s[i]);
		if(!ch[x][k]){
			ch[x][k]=++tot;
			dep[tot]=dep[x]+1;
		}
		x=ch[x][k];
	}
	len[x]=dep[x];
}
void build(){
	queue<int> q;
	for(int i=0;i<=3;i++){
		if(ch[0][i]) q.push(ch[0][i]);
	}
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=0;i<=3;i++){
			if(ch[x][i]) fail[ch[x][i]]=ch[fail[x]][i],q.push(ch[x][i]);
			else ch[x][i]=ch[fail[x]][i];
		}
		len[x]=max(len[x],len[fail[x]]);
	}
}
void dp(){
	f[0][0][0]=1;
	for(int i=0;i<n;i++){
		for(int j=0;j<=mlen;j++){
			for(int k=0;k<=tot;k++){
				if(f[i][j][k]){
					for(int p=0;p<=3;p++){
						int x=ch[k][p];
						if(len[x]>j)f[i+1][0][x]=(f[i+1][0][x]+f[i][j][k])%mod;
						else f[i+1][j+1][x]=(f[i+1][j+1][x]+f[i][j][k])%mod;
					}
				}
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%s",s);
		insert(s);
	}
	build();
	dp();
	int ans=0;
	for(int i=0;i<=tot;i++) ans=(ans+f[n][0][i])%mod;
	printf("%d",ans);
	return 0;
}
```





---

## 作者：九思 (赞：4)

前置知识[AC自动机](https://www.luogu.com.cn/problem/P3808)  

推荐博客[<1>](https://blog.csdn.net/weixin_30633405/article/details/98803470) [<2>](http://www.mamicode.com/info-detail-1920297.html)(吐槽一下这题很偏僻本来写的人就少，题解我也不怎么看得懂~~可能是因为我太蒻了QAQ~~)  

前面两位状态的设置是套路：$dp[i][j]$为前$i$位在$j$号节点上的总方案数（这题推荐用数组，用指针也随便啦）。但这样肯定不够。

AC自动机有这样一个特性:节点拥有当前串所有后缀的信息,并可以沿着fail指针寻找其后缀。  

我们**走fail时**会使当前子串*剩余0~len-1长度未被覆盖后缀*的状态都转移到最深的点上，而转移之后我们丢失了当前状态的已经匹配的长度的信息，所以此时**新增一维状态**表示**当前串还剩多少没有匹配**（不知道到底有多少所以这一维从0枚举到最长子串的长度~~其实就是10~~），转移过去后在这个树下面可能会有匹配的项。匹配上就转移到0，否则转移到未匹配+1（这里的转移规则和定义并不一样，是为了判断合法性）。

**使用刷表法（%Imakf orz）**

可能到这里还是有人一脸蒙逼（跟我一样），但是画个图什么的仔细推敲推敲还是有戏的。


```
#include<bits/stdc++.h>
#define int long long
#define f(i,a,b) for(register int i=a;i<=b;++i)
using namespace std;
const int mod =1e9+9;
const int N = 1024;
int dp[N][N][11],n,m,len,son[N][4],val[N],fail[N],sz,root,mx;
void add(int &x,int y) {x=((x+y%mod)%mod+mod)%mod;}
int idx(char c) {return c=='T'?3:c=='G'?2:c=='C';}
int newnode() {son[sz][0]=0;son[sz][1]=0;
son[sz][2]=0;son[sz][3]=0;val[sz]=0;return sz++;}
void insert(char *s,int len) {
	int u=0;
	f(i,0,len-1) {
		int v=idx(s[i]);
		if(!son[u][v]) son[u][v]=newnode();
		u=son[u][v];
	} val[u]=max(val[u],len);
}
void build() {
	queue<int> q;
	f(i,0,3) if(!son[root][i]) son[root][i]=root;
		else fail[son[root][i]]=root,q.push(son[root][i]);
	while(!q.empty()) {
		int u=q.front();q.pop();
		f(i,0,3) {
			int &v=son[u][i];
			if(!v) v=son[fail[u]][i];
			else fail[v]=son[fail[u]][i],q.push(v),
				val[v]=max(val[v],val[fail[v]]);
		}
	}
}

void DP() {
	dp[0][0][0]=1;
	f(i,0,n-1) f(j,0,sz-1) f(k,0,mx) {
		int v=dp[i][j][k];
	 	if(v) {
			//printf ( "dp[%d][%d][%d] = %d\n" , i , j , k , dp[i][j][k] );
			f(p,0,3) {
				int now=son[j][p];
				add(dp[i+1][now][(val[now]>k?0:k+(k!=mx))],v);
			}
		}
	}
	int ans=0;
	f(i,0,sz-1) add(ans,dp[n][i][0]);
	printf("%d\n",ans);
	//f(i,0,sz) cout<<val[i]<<"\n";
}
char str[12];
signed main() {
	root=newnode();
	cin>>n>>m;
	f(i,1,m) scanf("%s",str),len=strlen(str),
		mx=max(mx,len),insert(str,len);
	build();
	DP();
}
```

---

## 作者：too_later (赞：1)

这种萌萌题是不是该评蓝？谷民们你们说是不是？

[lnk](https://www.luogu.com.cn/problem/CF86C)

### 题目大意：

我们定义一个 DNA 序列为仅有 `ATCG` 四个字母的字符串。

给出 $m$ 个 DNA 序列模式串 $s_i$，每个长度均不超过 $10$ ，我们定义一个 DNA 序列 w 是好的，当且仅当对于 w 的每一个位置 $i$ ，都存在至少一个模式串 $s_j$，使得 $w_{[l...r]} = s_j$（ $w_{[l...r]}$ 表示一个原字符串的一个子串），其中 $1 \le l \le i \le r \le w$（ $|w|$ 为 DNA 序列 w 的长度） 。

请你计算出所有长度为 S 的好的 $DNA$ 序列的个数。

答案对 $1000000009$ 取模。

$n,m\le 10,|S|\le 1000$。

### Sol.

首先多模串匹配很容易想到 AC 自动机。

然后就显然是 DP 了，再开一维记录当前没被匹配的后缀长度。

每次匹配肯定是一个后缀，那么如果当前这个后缀要比没匹配的长的话，那么说明可以匹配。否则不行（后缀不能完全包含），那就将后缀长度 +1 往下走。

设 $dp_{i,j,k}$ 表示 AC 自动机上第 $i$ 个点， 匹配到第 $j$ 位，有 $k$ 位未被匹配。

$dp_{i,j,k}\to dp_{v,j+1,0}(len_{v}>j) $

$dp_{i,j,k}\to dp_{v,j+1,k+1}(len_v\le j)$

$len_v$ 可以用 fail 求出。

然后就做完了。

时间复杂度 $O(4nm|S|)$

### Code：

```cpp
#include<bits/stdc++.h>
#define I inline
#define RI register int
#define rep(i,a,b) for(RI i=a;i<=b;++i)
#define dow(i,a,b) for(RI i=a;i>=b;--i)
using namespace std;
const int N=1005,mo=1e9+9;
int ch[N][26],n,m,ans,cnt,fail[N],len[N],dp[N][N][13];
char c[15];
I int add(int a,int b){ return a+b>=mo?a+b-mo:a+b; }
I int sub(int a,int b){ return a-b<0?a-b+mo:a-b; }
I int mul(int a,int b){ return 1ll*a*b%mo; }
I int Hash(char c){
	if(c=='A') return 0;
	if(c=='C') return 1;
	if(c=='T') return 2;
	return 3;
}
I void ins(char *c,int l){
	RI now=0;rep(i,1,l) {
		if(!ch[now][Hash(c[i])]) ch[now][Hash(c[i])]=++cnt;
		now=ch[now][Hash(c[i])];
	} len[now]=l;
}
I void build(){
	queue<int> q;
	rep(i,0,25) if(ch[0][i]) q.push(ch[0][i]);
	while(!q.empty()){
		RI u=q.front();q.pop();
		rep(i,0,3)
			if(ch[u][i]) fail[ch[u][i]]=ch[fail[u]][i],q.push(ch[u][i]);
			else ch[u][i]=ch[fail[u]][i];
		len[u]=max(len[u],len[fail[u]]);
	}
}
I void DP(){
	dp[0][0][0]=1;
	rep(j,0,m-1) rep(i,0,cnt) rep(k,0,10) if(dp[i][j][k]) rep(l,0,3) 
		if(len[ch[i][l]]>k) dp[ch[i][l]][j+1][0]=add(dp[ch[i][l]][j+1][0],dp[i][j][k]);
		else dp[ch[i][l]][j+1][k+1]=add(dp[ch[i][l]][j+1][k+1],dp[i][j][k]);			
}
int main(){
	scanf("%d%d",&m,&n);
	rep(i,1,n) scanf("%s",c+1),ins(c,strlen(c+1));
	build(),DP();rep(i,0,cnt) ans=add(ans,dp[i][m][0]);
	return printf("%d\n",ans),0;
}
```

---

## 作者：OldDriverTree (赞：0)

# Solution

首先对所有串建出 AC 自动机。

有一个比较显然的 DP 状态：设 $f_{i,j,k}$ 表示考虑 $w$ 的前 $i$ 个字符，当前在 AC 自动机上走到了 $j$，$1\sim k$ 这些位置都已经满足条件的方案数。

为了方便转移，先对于 AC 自动机上的每个点预处理一下 fail 树上这个点到根的路径上的模式串的最大长度，转移枚举下一个字符填什么就行了。

但是这样做的时间复杂度为 $O(n^2\sum\vert s_i\vert)$，大概是过不了的，考虑优化一下状态，注意到如果 $i-k>\max\vert s_i\vert$，那么一定是不合法的，把状态 $f_{i,j,k}$ 中 $k$ 的含义变为 $1\sim i-k$ 已经满足条件的方案数，此时 $k$ 就只需要枚举到 $\max\vert s_i\vert$，时间复杂度变为 $O(n\sum\vert s_i\vert\max\vert s_i\vert)$，此时可以通过。

# Code
```
//when you use vector or deque,pay attention to the size of it.
//by OldDirverTree
#include<bits/stdc++.h>
//#include<atcoder/all>
#define P pair<int,int>
#define int long long
#define mid (l+r>>1)
using namespace std;
//using namespace atcoder;
const int N=1001,M=101,K=11,mod=1e9+9;
struct node { int son[4],fail,len; }T[M];
int n,m,tot,ans,f[N][M][K];

int qwq(char c) {
	if (c=='A') return 0;
	if (c=='T') return 1;
	if (c=='C') return 2;
	return 3;
}
void insert(string s)
{
	int rt=0;
	for (char c:s) {
		int &p=T[rt].son[qwq(c)];
		if (!p) p=++tot; rt=p;
	}
	T[rt].len=s.size();
}
void build()
{
	queue<int> q; for (int i=0;i<4;i++)
	if (T[0].son[i]) q.push(T[0].son[i]);
	while (!q.empty() ) {
		int u=q.front(); q.pop();
		T[u].len=max(T[u].len,T[T[u].fail].len); for (int i=0;i<4;i++)
		if (T[u].son[i]) T[T[u].son[i] ].fail=T[T[u].fail].son[i],
		q.push(T[u].son[i]); else T[u].son[i]=T[T[u].fail].son[i];
	}
}
main()
{
	cin.tie(0),cin>>n>>m;
	while (m--) { string s; cin>>s,insert(s); }
	build(),f[0][0][0]=1;
	for (int i=0;i<n;i++)
		for (int j=0;j<=tot;j++)
			for (int k=0;k<10;k++)
				for (int l=0;l<4;l++)
					if (T[T[j].son[l] ].len>k) f[i+1][T[j].son[l] ][0]=(f[i+1][T[j].son[l] ][0]+f[i][j][k])%mod;
					else f[i+1][T[j].son[l] ][k+1]=(f[i+1][T[j].son[l] ][k+1]+f[i][j][k])%mod;
	
	for (int i=0;i<=tot;i++)
	ans=(ans+f[n][i][0])%mod;
	return !printf("%lld",ans);
}
```

---

## 作者：Kingna (赞：0)

AC 自动机优化 dp。

题目大意：用给定的 $m$ 个字符串覆盖长度为 $n$ 的空字符串，问有多少种方案。

首先发现字符串可以相交，那么可以这么定义状态：$dp_{i,j,k}$ 表示已经覆盖了前 $i$ 个空字符，当前走到了 AC 自动机的第 $j$ 个节点，有 $k$ 个字符没有找到可以匹配的字符串的方案数。

在 AC 自动机上处理出：$len_i$ 表示第 $i$ 个节点结尾的最长的字符串长度。具体：$len_i=\max{\{len_i,len_{fail_{i}}}\}$。

转移：

```c++
if (len[trie[j][l]] > k) dp[i + 1][trie[j][l]][0] = dp[i + 1][trie[j][l]][0] + dp[i][j][k]; // 存在字符串可以覆盖掉之前不能匹配的字符
else  dp[i + 1][trie[j][l]][k + 1] = dp[i + 1][trie[j][l]][k + 1] + dp[i][j][k];
```

完整代码：

```cpp
const int N = 1005, mod = 1e9 + 9;
int n, m, trie[N][26], fail[N], tot, len[N], dp[N][N][12];
char a[N];

signed main() {
	cin >> n >> m;
	_for(i, 1, m) {
		cin >> (a + 1);
		int lena = strlen(a + 1), u = 0;
		_for(j, 1, lena) {
			int c = a[j] - 'A';
			if (!trie[u][c]) trie[u][c] = ++tot;
			u = trie[u][c];
		}
		len[u] = lena;
	}
	queue<int> q;
	_for(i, 0, 25) if (trie[0][i]) q.push(trie[0][i]);
	while (q.size()) {
		int u = q.front(); q.pop();
		_for(i, 0, 25) {
			if (trie[u][i]) {
				fail[trie[u][i]] = trie[fail[u]][i];
				len[trie[u][i]] = max(len[trie[u][i]], len[fail[trie[u][i]]]);
				q.push(trie[u][i]);
			}
			else trie[u][i] = trie[fail[u]][i];
		}
	}
	dp[0][0][0] = 1;
	_for(i, 0, n - 1) {
		_for(j, 0, tot) {
			_for(k, 0, 10) {
				if (!dp[i][j][k]) continue;
				_for(l, 0, 25) {
					if (len[trie[j][l]] > k) dp[i + 1][trie[j][l]][0] = (dp[i + 1][trie[j][l]][0] + dp[i][j][k]) % mod;
					else  dp[i + 1][trie[j][l]][k + 1] = (dp[i + 1][trie[j][l]][k + 1] + dp[i][j][k]) % mod;
				}
			}
		}
	}
	int res = 0;
	_for(i, 0, tot) res = (res + dp[n][i][0]) % mod;
	cout << res << endl;
}
```

---

## 作者：Graphcity (赞：0)

简单的 AC 自动机上 DP 题。

先对题目条件做一步转化：所有在文本串中的匹配段能够覆盖整个文本串。考虑将每次匹配的贡献放到最后一个位置。

建出 AC 自动机后，设 $f_{i,j,k}$ 为此时在 AC 自动机上第 $i$ 个结点，文本串长度为 $j$，且后 $k$ 个字符未被匹配的方案数。初始状态 $f_{0,0,0}=1$，答案为 $\sum_i f_{i,n,0}$。

预处理出自动机上每个结点所能够匹配的最大长度 $siz_i$。利用刷表法，枚举接下来填的后一个字符 $c$ 转移：

- $f_{i,j,k}\to f_{i\to c,j+1,0}$，此时 $siz_{i\to c}>k$，也就是说所有之前未被匹配的字符都在这一次被匹配掉了。

- $f_{i,j,k}\to f_{i\to c,j+1,k+1}$，此时 $siz_{i\to c}\le k$，也就是说以当前的匹配长度还不足以匹配完，与其在这里匹配，不如等到后面一起搞定。

**注意模数为 $10^9+9$**。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e3,Maxk=100,Mod=1e9+9;

int n,m,f[Maxk+5][Maxn+5][11]; char str[Maxn+5];
int t[Maxn+5][4],siz[Maxn+5];
int fail[Maxn+5],chk[Maxn+5],tot;
queue<int> q;

inline int Get(char ch)
{
    if(ch=='A') return 0;
    if(ch=='G') return 1;
    if(ch=='C') return 2;
    if(ch=='T') return 3;
}
inline void Insert()
{
    int l=strlen(str+1),p=0;
    For(i,1,l)
    {
        int x=Get(str[i]);
        if(!t[p][x]) t[p][x]=++tot;
        p=t[p][x];
    }
    chk[p]=l;
}
inline void Build()
{
    For(i,0,3) if(t[0][i]) q.push(t[0][i]);
    while(!q.empty())
    {
        int x=q.front(); q.pop();
        For(i,0,3)
        {
            if(t[x][i]) fail[t[x][i]]=t[fail[x]][i],q.push(t[x][i]);
            else t[x][i]=t[fail[x]][i];
        }
    }
}

int main()
{
    scanf("%d%d",&m,&n);
    For(i,1,n) scanf("%s",str+1),Insert();
    Build();
    For(i,0,tot)
    {
        int now=i;
        while(now) siz[i]=max(siz[i],chk[now]),now=fail[now];
    }
    f[0][0][0]=1;
    For(j,1,m) For(i,0,tot) For(k,0,10) if(f[i][j-1][k])
    {
        int res=f[i][j-1][k];
        For(l,0,3)
        {
            int x=t[i][l];
            if(siz[x]>k) f[x][j][0]=(f[x][j][0]+res)%Mod;
            else if(k<10) f[x][j][k+1]=(f[x][j][k+1]+res)%Mod;
        }
    }
    int ans=0;
    For(i,0,tot) ans=(ans+f[i][m][0])%Mod;
    printf("%d\n",ans);
    return 0;
}
```

---

