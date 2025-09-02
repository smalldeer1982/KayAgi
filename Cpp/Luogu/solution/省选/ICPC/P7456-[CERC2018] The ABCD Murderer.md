# [CERC2018] The ABCD Murderer

## 题目描述

**译自[ [CERC2018]](https://contest.felk.cvut.cz/18cerc/) [The ABCD Murderer](https://contest.felk.cvut.cz/18cerc/solved/abcd.pdf)**

Oscar 特别喜欢看犯罪电影。他钦佩那些罪犯，因为他们富有创造力。他也想展示他的创造力。但很可惜的是，他没什么经验，也想不出来什么原创伎俩。所以他想从已有的招数中寻找灵感。他一直喜欢看罪犯从报纸上剪下字母，然后用这些字母拼勒索信的桥段。然而 Oscar 根本不想抄袭，所以他自己想了一个这种方法的变体。他觉得把字母一个一个拼成文本既无聊又费时间。所以他决定通过剪下一整个单词的方式拼出自己的勒索信。

Oscar 买来一些主流报纸，这样他几乎就有了无限的单词库。他可以多次剪出任意特定的单词。然而，他还是被报纸中出现的的单词集限制。问题是一些单词根本没在报纸中出现。为了让这项工作更简单，他决定去除勒索信中所有的标点符号和空格并且忽略字母的大小写。他同时允许剪出的单词互相重叠，只需要重叠部分相同。现在 Oscar 想知道他至少要剪下多少次单词才能拼成他想要的勒索信。

## 说明/提示

$1≤L,|s|,∑|a_i|≤3×10^5$

## 样例 #1

### 输入

```
3
aaaaa
a
aa
aaa```

### 输出

```
2```

## 样例 #2

### 输入

```
5
abecedadabra
abec
ab
ceda
dad
ra```

### 输出

```
5```

## 样例 #3

### 输入

```
9
icpcontesticpc
international
collegiate
programming
contest
central
europe
regional
contest
icpc```

### 输出

```
3```

# 题解

## 作者：grass8cow (赞：10)

有一个显然的dp：

令 $f_i$ 表示文本串前 $i$ 位已经覆盖完的最小代价。

若 $s[i,j]$ 是个模式串，显然有 $f_j=\min(f_k+1)(i-1\le k<j)$

多模式串匹配，考虑 AC 自动机。

对于所有模式串建出 ACAS ，易对文本串进行匹配。

由转移方程，求 $f_j$ 时显然想让 $i$ 最小，模式串就尽量大。匹配到的那个点到 $fail$ 根上的所有点里，那些表示某模式串末尾的，就能和它的 $len$ 取 $\max$ 。这个不用每次求，直接预处理实现。

把这个 $i$ 求出来，$dp$ 就随便拿个数据结构实现即可。我用的是反向 $ST$ 表。

my code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;char c[300010],cc[300010];
int ch[300010][26],cn=1,len[300010],fail[300010];
queue<int>q;
void build(){
	for(int i=0;i<26;i++)if(ch[1][i])fail[ch[1][i]]=1,q.push(ch[1][i]);else ch[1][i]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		len[u]=max(len[u],len[fail[u]]);
		for(int i=0;i<26;i++)if(ch[u][i])
			fail[ch[u][i]]=ch[fail[u]][i],q.push(ch[u][i]);
		else ch[u][i]=ch[fail[u]][i];
	}
}
int dp[300010][20];
int ask(int l,int r){
	if(l>r)return 1e9+7;
	int k=log2(r-l+1);
	return min(dp[r][k],dp[l+(1<<k)-1][k]);
}
int main(){
	scanf("%d%s",&n,cc+1);
	for(int i=0;i<n;i++){
		scanf("%s",c);int l=strlen(c),u=1;
		for(int j=0;j<l;j++){
			if(!ch[u][c[j]-'a'])ch[u][c[j]-'a']=++cn;
			u=ch[u][c[j]-'a'];
		}
		len[u]=max(len[u],l);
	}
	build();int le=strlen(cc+1),u=1;
	memset(dp,0x3f,sizeof(dp));dp[0][0]=0;
	for(int i=1;i<=le;i++){
		u=ch[u][cc[i]-'a'];
		dp[i][0]=ask(i-len[u],i-1)+1;
		for(int j=1;j<20;j++){
			if(i-(1<<j)+1<0)break;
			dp[i][j]=min(dp[i][j-1],dp[i-(1<<j-1)][j-1]);
		}
	}
	return printf("%d",dp[le][0]>1e9?-1:dp[le][0]),0;
}
```


---

## 作者：Alex_Wei (赞：7)

> *IX. [P7456 [CERC2018] The ABCD Murderer](https://www.luogu.com.cn/problem/P7456)
>
> 摘自 [常见字符串算法 II](https://www.cnblogs.com/alex-wei/p/Common_String_Theory_Theory_automaton_related.html) Part 1. AC 自动机部分例题 IX。

由于单词可以重叠（否则就不可做了），我们只需求出对于每个位置 $i$，以 $i$ 结尾的最长单词的长度 $L_i$，因为对于**相同的出现位置**，用更短的单词去代替最长单词并不会让答案更优。使用 ACAM 即可求出 $L_i$。

最优化问题考虑 DP：设 $f_i$ 表示拼出 $s[1,i]$ 的最小代价。不难得到转移 $f_i = \min_{j = i - L_i} ^ {i - 1} f_j$。特别的，若 $L_i$ 不存在（即没有单词在 $s$ 中以 $i$ 为结束位置出现）则 $f_i$ 为无穷大。若 $f_n$ 为无穷大则无解。这可以通过线段树解决。

如果不想写线段树，还有一种方法：从后往前 DP。这样，每个位置可以转移到的地方是固定的（$i-L_i\sim i - 1$），所以用小根堆维护，懒惰删除即可。时间复杂度均为线性对数。

```cpp
const int N = 3e5 + 5;
const int S = 26;

int L, n, len[N];
int node, ed[N], son[N][S], fa[N];
string t; char s[N];
void ins(string s) {
	int p = 0;
	for(char it : s) {
		if(!son[p][it - 'a']) son[p][it - 'a'] = ++node;
		p = son[p][it - 'a'];
	} cmax(ed[p], s.size());
}
void build() {
	queue <int> q;
	for(int i = 0; i < S; i++) if(son[0][i]) q.push(son[0][i]);
	while(!q.empty()) {
		int t = q.front(); q.pop();
		for(int i = 0; i < S; i++)
			if(son[t][i]) fa[son[t][i]] = son[fa[t]][i], q.push(son[t][i]);
			else son[t][i] = son[fa[t]][i];
		cmax(ed[t], ed[fa[t]]);
	}
}
int main() {
	cin >> L >> s + 1, n = strlen(s + 1);
	for(int i = 1; i <= L; i++) cin >> t, ins(t); build();
	for(int i = 1, p = 0; i <= n; i++) len[i] = ed[p = son[p][s[i] - 'a']];
	priority_queue <pii, vector <pii>, greater <pii>> q; q.push({1, n - len[n]});
	for(int i = n; ; i--) {
		while(!q.empty() && q.top().se >= i) q.pop();
		if(q.empty()) puts("-1"), exit(0);
		int f = q.top().fi, lim = i - 1 - len[i - 1];
		if(i == 1) cout << f << endl, exit(0);
		if(lim < q.top().se) q.push({f + 1, lim}); 
	}
	return flush(), 0;
}
```

---

## 作者：wangyizhi (赞：4)

[**题目传送门**](https://www.luogu.com.cn/problem/P7456)

没有 SA 的题解不是很认可，于是写一发。

## 题目分析

首先把所有串扔一起跑一遍 SA。

考虑对于文本串的一个位置，其**向后**可以匹配到哪。

不难发现，答案就是所有后缀排序后这个位置向前或向后的第一个与这个后缀 $\operatorname{lcp}$ 等于长度的模式串。可以通过单调栈维护。

举个例子：

```markdown
1 :#
2 :#ab#ba#
3 :#ba#
4 :a#           
5 :ab#ab#ba#    +
6 :ab#ba#       <
7 :abab#ab#ba#  +
8 :b#ab#ba#     +
9 :b#ba#
10:ba#          <
11:bab#ab#ba#   +
```

其中 `<` 以模式串开头，`+` 以文本串后缀开头。

从上往下扫：

……

当 `i=5` 时，栈中为空；

当 `i=6` 时，这个后缀入栈；

当 `i=7` 时，当前 $height$ 大于栈顶，无元素出栈。原串位置为 $1$ 的地方可以匹配至 $sa[i]+length[stack[top]]-1=1+2-1=2$；

当 `i=8` 时，当前 $height$ 小于栈顶，意味着当前后缀与前一个模式串的 $\operatorname{lcp}$ 小于其长度，不可能再产生贡献，故出栈。

……

以此类推，反过来再做一遍。

然后就是线段树优化 DP 了 ~~，较为简单，就不写了~~。

（可能说的有些过于抽象了，可以看看代码 qwq）

## Code

```cpp
#include<bits/stdc++.h>
//#include<bits/extc++.h>
using namespace std;
using ll=long long;
using ld=long double;
//#define int ll
using pii=pair<int,int>;
bool Mst;
const int N=1e6+5,inf=1e9;
char s[N];
bool txt[N];
int len[N],sa[N<<1],rk[N<<1],old[N],cnt[N],id[N],he[N];
int st[N],top,pre[N],dp[N],t[N<<2];
inline int ls(int id){return id<<1;}
inline int rs(int id){return id<<1|1;}
inline void push_up(int id){t[id]=min(t[ls(id)],t[rs(id)]);}
void build(int l,int r,int id)
{
	t[id]=inf;
	if(l==r) return;
	int m=(l+r)>>1;
	build(l,m,ls(id)),build(m+1,r,rs(id));
}
void update(int s,int x,int id,int nl,int nr)
{
	if(nl==nr) return t[id]=x,void();
	int m=(nl+nr)>>1;
	if(s<=m) update(s,x,ls(id),nl,m);
	else update(s,x,rs(id),m+1,nr);
	push_up(id);
}
int query(int l,int r,int id,int nl,int nr)
{
	if(l<=nl&&r>=nr) return t[id];
	int m=(nl+nr)>>1,res=inf;
	if(l<=m) res=min(res,query(l,r,ls(id),nl,m));
	if(r>m) res=min(res,query(l,r,rs(id),m+1,nr));
	return res;
}
bool Med;
signed main()
{
//	cerr<<"Memory Size: "<<abs((&Med)-(&Mst))/1024.0/1024<<" MB\n";
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int c,n=0,m=128,p=0,cur=0;
	cin>>c;
	string str;
	cin>>str;
	int l=str.length();
	for(char c:str) s[++n]=c,txt[n]=1; // txt：是否是文本串
	s[++n]='#';
	for(int i=1;i<=c;i++)
	{
		cin>>str;
		len[n+1]=str.length(); // len：是否是模式串开头 并记录长度
		for(char ch:str) s[++n]=ch;
		s[++n]='#';
	}
	for(int i=1;i<=n;i++) cnt[rk[i]=s[i]]++;
	for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
	for(int i=n;i>=1;i--) sa[cnt[rk[i]]--]=i;
	for(int w=1;;w<<=1,m=p)
	{
		p=cur=0;
		memset(cnt,0,sizeof(cnt));
		memcpy(old,rk,sizeof(old));
		for(int i=n-w+1;i<=n;i++) id[++cur]=i;
		for(int i=1;i<=n;i++) if(sa[i]>w) id[++cur]=sa[i]-w;
		for(int i=1;i<=n;i++) cnt[rk[i]]++;
		for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--) sa[cnt[rk[id[i]]]--]=id[i];
		for(int i=1;i<=n;i++)
			if(old[sa[i]]==old[sa[i-1]]&&old[sa[i]+w]==old[sa[i-1]+w]) rk[sa[i]]=p;
			else rk[sa[i]]=++p;
		if(p==n) break;
	}
	for(int i=1,k=0;i<=n;i++,k-=!!k) if(rk[i]!=1)
	{
		int j=sa[rk[i]-1];
		while(i+k<=n&&j+k<=n&&s[i+k]==s[j+k]) k++;
		he[rk[i]]=k;
	} // 以上均为 SA 板子
	for(int i=1;i<=n;i++) pre[i]=i; // dp[i] 可以从 dp[i+1]~dp[pre[i]] 转移过来
	for(int i=1;i<=n;i++)
	{
		while(top&&he[i]<len[sa[st[top]]]) top--; // 若 height<len 则不可能产生贡献
		if(len[sa[i]]) st[++top]=i; // 是模式串就进栈
		else if(txt[sa[i]]) pre[sa[i]]=max(pre[sa[i]],sa[i]+len[sa[st[top]]]); // 注：这里可能和上文讲的有些不同，因为转移时需要再往后一位，所以这里就没减一了
	}
	top=0;
	for(int i=n;i>=1;i--)
	{
		while(top&&he[i+1]<len[sa[st[top]]]) top--; // 注意这里是 i+1，不要写错了
		if(len[sa[i]]) st[++top]=i;
		else if(txt[sa[i]]) pre[sa[i]]=max(pre[sa[i]],sa[i]+len[sa[st[top]]]);
	}
#define root 1,1,l+1	
	build(1,l+1,1),update(l+1,0,root);
	for(int i=l;i>=1;i--) update(i,dp[i]=query(i,pre[i],root)+1,root);
	cout<<(dp[1]>=inf?-1:dp[1])<<"\n";
	return 0;
}
```

---

## 作者：Hoks (赞：4)

## 前言
比较简单的 ACAM 题，有关串串的可以见[学习笔记](https://www.luogu.com.cn/article/dv6dig1o)喵。
## 思路分析
题意比较清楚了，不再赘述。

发现题目是个多模匹配，果断想到 ACAM。

接着考虑怎么得到最少需要的单词数。

想到 dp，考虑设计 $dp_i$ 表示覆盖前 $i$ 位文本串的最小代价。

那么可以得到一个很朴素的方程式：

$$dp_i=\min(dp_j+1),(k-1\le j<i)$$

其中转移条件为文本串的 $[k,i]$ 是个模式串。

考虑下这玩意就是区间取 $\max$，所以可以扔个数据结构优化下，比如 ST 表，线段树。

然后整理一遍思路：把文本串扔 ACAM 上跑，然后对于每个跑到的节点 $i$，最小的 $k$ 满足 $[k,i]$ 是个模式串。

发现这个 $k$ 不太好找，考虑处理出 $i$ 的最长后缀模式串长度 $ed_i$，然后直接 $k=i-ed_i+1$。

这个 $ed_i$ 也就非常好处理了，插入的时候尾节点标记下，建 fail 指针的时候再和 fail 指针的 $ed$ 取个 $\max$ 就行了。

这样就完美完成本题了。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=300010,INF=0x3f3f3f3f3f3f3f3f,lim=20;
int n,l,m,dp[N][lim];char s[N],t[N];
struct ACAM
{
	struct node{int nxt,v[26],ed;}t[N];int tot=0;
	inline void insert(char s[],int n,int id)
	{
		int u=0;
		for(int i=1;i<=n;i++){if(!t[u].v[s[i]-'a']) t[u].v[s[i]-'a']=++tot;u=t[u].v[s[i]-'a'];}
		t[u].ed=max(t[u].ed,n);
	}
	inline void build()
	{
		queue<int>q;
		for(int i=0;i<26;i++) if(t[0].v[i]) t[t[0].v[i]].nxt=0,q.push(t[0].v[i]);
		while(!q.empty())
		{
			int u=q.front();q.pop();t[u].ed=max(t[u].ed,t[t[u].nxt].ed);
			for(int i=0;i<26;i++)
				if(t[u].v[i]) t[t[u].v[i]].nxt=t[t[u].nxt].v[i],q.push(t[u].v[i]);
				else t[u].v[i]=t[t[u].nxt].v[i];
		}
	}
}ac;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void print(int x)
    {
        if(x<0) putchar('-'),x=-x;
        if(x>9) print(x/10);
        putchar(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;//美妙Clion封装的实时模板。
int query(int l,int r)
{
	if(l>r)return INF;
	int k=log2(r-l+1);
	return min(dp[r][k],dp[l+(1<<k)-1][k]);
}
signed main()
{
	n=read(),rd(s,l);
	for(int i=1;i<=n;i++) m=0,rd(t,m),ac.insert(t,m,i);
	ac.build();int u=0;memset(dp,0x3f,sizeof dp);dp[0][0]=0;
	for(int i=1;i<=l;i++)
	{
		u=ac.t[u].v[s[i]-'a'];dp[i][0]=query(i-ac.t[u].ed,i-1)+1;
		for(int j=1;j<lim;j++)
		{
			if(i-(1<<j)+1<0) break;
			dp[i][j]=min(dp[i][j-1],dp[i-(1<<j-1)][j-1]);
		}
	}
	print(dp[l][0]>=INF?-1:dp[l][0]);
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：4)

**P7456**题解，读题需谨慎。


---------------------------------------------------------------

考虑直接建立 AC 自动机，寻找每个后缀结尾能匹配的最长单词。

这个可以通过建立 AC 自动机后用 fail 指针跑拓扑排序处理，由于在模板题里面就出现过这个套路就不细讲了。

接着我们对于每个位置 $i$ 得到一个可以进行拼接状态转移的位置 $[l_i , i - 1]$。

直接 dp 答案，记 $dp_i$ 表示结尾位置为 $i$ 的文本串需要至少多少个单词拼接，每次就从可以转移的位置找到 $dp_i$ 最小的点进行转移就好了。

观察到 dp 数组不一定具有单调性，开个线段树辅助一下转移就好了。

时间复杂度 $O(26\sum |a_i| + |S| \log S)$，注意特判 $-1$。

```
/*
询问文本串被最少几个单词组成
哦我是 SB。 
*/ 
#include "bits/stdc++.h"
using namespace std;
const int Len = 3e5 + 5;
int n,m,trie[Len][27],cnt,fail[Len],sum[Len],dp[Len],L[Len],vis[Len],head[Len],Cnt,in[Len];
char s[Len],S[Len];
struct node
{
	int next,to;
}edge[Len << 1];
void add(int from,int to)
{
	edge[++ Cnt].to = to;
	edge[Cnt].next = head[from];
	head[from] = Cnt;
}
void insert(char s[])
{
	int rt = 0;int sz = strlen(s + 1);
	for(int i = 1 ; i <= sz ; i ++)
	{
		int ind = s[i] - 'a';
		if(!trie[rt][ind]) trie[rt][ind] = ++ cnt;
		rt = trie[rt][ind];
	}
	sum[rt] = max(sum[rt] , sz);
}
void Build_Fail()
{
	queue<int> q;while(!q.empty()) q.pop();
	int rt = 0;
	for(int i = 0 ; i < 26 ; i ++) 
	{
		if(trie[rt][i])
		{
			fail[trie[rt][i]] = 0;
			q.push(trie[rt][i]);
		}
	}
	while(!q.empty())
	{
		int p = q.front();q.pop();
		for(int i = 0 ; i < 26 ; i ++)
		{
			if(trie[p][i])
			{
				fail[trie[p][i]] = trie[fail[p]][i];
				add(fail[trie[p][i]] , trie[p][i]);
				in[trie[p][i]] ++;
				q.push(trie[p][i]);
			}
			else trie[p][i] = trie[fail[p]][i];
		}
	}
	for(int i = 1 ; i <= cnt ; i ++) if(!in[i]) q.push(i);
	while(!q.empty())
	{
		int p = q.front();q.pop();
		for(int e = head[p] ; e ; e = edge[e].next)
		{
			int to = edge[e].to;
			in[to] --;
			if(!in[to]) q.push(to);
			sum[to] = max(sum[to] , sum[p]); 
		}
	}
	//for(int i = 1 ; i <= cnt ; i ++) printf("%d %d\n",i,sum[i]);
}
#define ls(p) p << 1
#define rs(p) p << 1 | 1
int minn[Len << 2];
void push_up(int x){minn[x] = min(minn[ls(x)] , minn[rs(x)]);}
void build(int p,int l,int r)
{
	minn[p] = 1e9;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid);
	build(rs(p) , mid + 1 , r);
}
void upd(int p,int l,int r,int idx)
{
	if(l == r) 
	{
		minn[p] = dp[l];
		return;
	}
	int mid = (l + r) >> 1;
	if(idx <= mid) upd(ls(p) , l , mid , idx);
	else upd(rs(p) , mid + 1 , r , idx);
	push_up(p); 
}
int qry(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r) return minn[p];
	int mid = (l + r) >> 1 , res = 1e9;
	if(nl <= mid) res = min(res , qry(ls(p) , l , mid , nl , nr));
	if(nr > mid) res = min(res , qry(rs(p) , mid + 1 , r , nl , nr));
	return res;
}
inline void Qry(char s[])
{
	int sz = strlen(s + 1) , rt = 0;
	for(int i = 1 ; i <= sz ; i ++) dp[i] = 1e9;
	for(int i = 1 ; i <= sz ; i ++)
	{
		int ind = s[i] - 'a';
		rt = trie[rt][ind];
		L[i] = max(0 , i - sum[rt]);
		//printf("%d %d\n",L[i],i);
	} 
	build(1 , 0 , sz);
	dp[0] = 0;upd(1 , 0 , sz , 0);
	for(int i = 1 ; i <= sz ; i ++) 
	{
		if(L[i] <= i - 1) dp[i] = qry(1 , 0 , sz , L[i] , i - 1) + 1;
		upd(1 , 0 , sz , i);
	}
	if(dp[sz] >= 1e9) dp[sz] = -1;
	printf("%d\n",dp[sz]);
}
int main()
{
	scanf("%d",&n);
	scanf("%s",S + 1);
	for(int i = 1 ; i <= n ; i ++)
	{
		scanf("%s",s + 1);
		insert(s);
	}
	Build_Fail();
	Qry(S);
	return 0;
}
```

---

## 作者：huangleyi0129 (赞：1)

ACAM 部分显然。

对每个点贪心，必然选长度最大的串。

设 $f_i=i-maxlen$。

倒着扫，考虑当前的覆盖区间 $[u,n]$（初始为 $[f_n,n]$），贪心地从中选出 $f_i$ 最小的（具体地，扫一遍即可，见代码）。

设 $u= \min f_i$。

如果 $v < u$，则更新 $u$ 为 $v$。

否则无解，贪心正确性显然。

注意特判 $f_n=n$。

时间复杂度 $O(n)$，目前最优解。

~~码风比较丑~~


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300005,S=26;
int trie[N][S],fail[N],f[N],is[N],n,m,k,ans=1;
char s[N],t[N];
void init()
{
	queue<int>q{};
	q.emplace(0);
	int u;
	while(!q.empty())
	{
		u=q.front(),is[u]=max(is[u],is[fail[u]]),q.pop();
		for(int i=0;i<26;++i)
			if(!trie[u][i])
				trie[u][i]=trie[fail[u]][i];
			else
				fail[trie[u][i]]=u==0?0:trie[fail[u]][i],q.emplace(trie[u][i]);
	}
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>m>>s+1,n=strlen(s+1);
	int len,u,v;
	for(int i=1;i<=m;++i)
	{
		cin>>t+1,len=strlen(t+1);
		u=0;
		for(int j=1;j<=len;++j)
		{
			if(!trie[u][t[j]-'a'])
				trie[u][t[j]-'a']=++k;
			u=trie[u][t[j]-'a'];
		}
		is[u]=len;
	}
	init();
	u=0;
	for(int i=1;i<=n;++i)
	{
		u=trie[u][s[i]-'a'];
		f[i]=i-is[u];
	}
	u=v=f[n];
	if(f[n]==n)
	{
		cout<<"-1";
		return 0;
	}
	for(int i=n-1;i>=1;--i)
	{
		v=min(v,f[i]);
		if(i==u)
		{
			if(v>=u)
			{
				cout<<"-1";
				return 0;
			}
			u=v,++ans;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：mike05 (赞：1)

## 题目大意
有一个字符串 $s$ 和 $L$ 个字符串 $t_{1,2 \dots L}$。

求至少要多少个 $t$ 中的字符串才可以拼成 $s$，可以重合。

## 做法

首先，我们可以发现：对于第 $i$ 个位置，假如有一个集合 $S$ 满足 $S$ 内每一个元素 $S_x$ 到 $i$ 都可以从 $t$ 中找到**完全**相同的字符串。我们发现我们可以就选择 $S$ 中最小的元素，这样构成的答案一定不劣。

我们可以用 ACAM 来处理每一个 $t$ 并且求出 $s$ 每一个位置上最长在 $t$ 中出现过的后缀长度，记为 $pre_i$。

我们考虑用 dp 来做这道题。

我们记 $f_i$ 表示 $s$ 中从 $1$ 到 $i$ 至少需要多少个 $t$ 中的字符串来表达。初始化定义 $f_0 = 0$。

$$
f_i = \begin{cases} \min\limits_{j = i- pre_i}^{i - 1}f_j+1,pre_i \neq 0\\\inf ,pre_i = 0\end{cases}
$$

可以使用线段树维护。需要维护区间最小值，并且支持单点修改。

```cpp
const int N = 3e5 + 10, inf = 1e9;
int n, T;
char str[N], s[N];
int q[N], ne[N], tag[N], pre[N], f[N];
struct acam
{
    int tr[N][26], idx;
    void insert()
    {
        int p = 0, u = strlen(str);
        for (int i = 0; str[i]; i ++ )
        {
            int t = str[i] - 'a';
            if (!tr[p][t]) tr[p][t] = ++ idx;
            p = tr[p][t];
        }
        tag[p] = max(tag[p], u);
    }
    void build()
    {
        int hh = 0, tt = -1;
        for (int i = 0; i < 26; i ++ )
            if (tr[0][i]) q[ ++ tt] = tr[0][i];
        while (hh <= tt)
        {
            int t = q[hh ++ ];
            for (int i = 0; i < 26; i ++ )
            {
                int p = tr[t][i];
                if (!p) tr[t][i] = tr[ne[t]][i];
                else
                {
                    ne[p] = tr[ne[t]][i];
                    q[ ++ tt] = p;
                }
            }
            tag[t] = max(tag[t], tag[ne[t]]);
        }
    }
}acam;
struct Node
{
    int l, r, mn;
};
struct SEGTree
{
    Node tr[N << 2];
    #define ls (u << 1)
    #define rs (u << 1 | 1)
    void pushup(int u) { tr[u].mn = min(tr[ls].mn, tr[rs].mn); }
    void build(int u, int l, int r)
    {
        tr[u] = {l, r, inf};
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(ls, l, mid); build(rs, mid + 1, r);
    }
    void modify(int u, int p, int x)
    {
        if (tr[u].l == tr[u].r) return tr[u].mn = min(tr[u].mn, x), void();
        int mid = (tr[u].l + tr[u].r) >> 1;
        if (p <= mid) modify(ls, p, x);
        else modify(rs,p, x);
        pushup(u);
    }
    int query(int u, int l, int r)
    {
        if (l <= tr[u].l && r >= tr[u].r) return tr[u].mn;
        int mid = (tr[u].l + tr[u].r) >> 1, res = inf;
        if (l <= mid) res = min(res, query(ls, l, r));
        if (r > mid) res = min(res, query(rs, l, r));
        return res;
    }
}seg;
int main()
{
    cin >> T >> (s + 1); n = strlen(s + 1);
    while (T -- )
    {
        cin >> str;
        acam.insert();
    }
    acam.build();
    int p = 0;
    for (int i = 1; i <= n; i ++ ) pre[i] = tag[p = acam.tr[p][s[i] - 'a']];
    seg.build(1, 1, n + 1); seg.modify(1, 1, 0);
    for (int i = 1; i <= n; i ++ )
    {
        if (pre[i] != 0)
        {
            int l = i - pre[i] + 1, r = i;
            f[i] = seg.query(1, l, r) + 1;
            f[i] = min(f[i], inf);
            if (f[i] != inf) seg.modify(1, i + 1, f[i]);
        }
        else f[i] = inf;
    }
    if (f[n] == inf) f[n] = -1;
    cout << f[n] << "\n";
    return 0;
}
```

---

## 作者：Zhddd_ (赞：1)

题意：给定 $n$ 个模式串和一个文本串，问要拼成文本串最少需要几个模式串。其中模式串可重叠。

设 $f_i$ 为拼成文本串前 $i$ 位所需要的模式串个数最小值。

对于文本串的前 $i$ 位组成的前缀，如果有很多模式串与这个前缀的后缀相匹配，那么选其中长度最大的一定更优，设其中长度最大的模式串的长度为 $L$，那么可以列出状态转移方程：

$$f_i \gets \min (f_j) + 1$$

其中 $j$ 满足 $i - L\le j\le i - 1$。

一开始，如果前 $i$ 位能被一个模式串直接表示出来，$f_i \gets 1$，否则 $f_i \gets inf$。最后，如果 $f_{slen} > slen$（其中 $slen$ 为文本串的长度），说明运算过程中有 $inf$ 的参与，即不可能通过已有的模式串表达出来。

现在要解决的问题是 $L$ 怎么求与 $f_i$ 怎么维护。前者将模式串建成 AC 自动机，可以直接求得，后者因为要支持单点修改和区间查询最小值，所以可以使用线段树。

时间复杂度：$O(n\log n)$。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 3e5 + 10, INF = 3e5 + 10;
int n, idx, dep[N], tr[N][26], len[N], q[N], ne[N];
char s[N], str[N];
// s 为文本串，str 为模式串，tr 为 Trie 树，segtr 为线段树。
struct Node{
	int l, r, minn;
} segtr[N * 4];
void insert() {
	int p = 0;
	for (int i = 0; str[i]; i++) {
		int u = str[i] - 'a';
		if (!tr[p][u]) tr[p][u] = ++idx, dep[idx] = dep[p] + 1;
		p = tr[p][u];
	} 
	len[p] = dep[p];
} 
void buildTrie() {
	int hh = 0, tt = -1;
	for (int i = 0; i < 26; i++) {
		if (tr[0][i]) q[++tt] = tr[0][i];
	}
	while (hh <= tt) {
		int p = q[hh++];
		for (int i = 0; i < 26; i++) {
			int u = tr[p][i];
			if (!u) tr[p][i] = tr[ne[p]][i];
			else {
				ne[u] = tr[ne[p]][i];
				q[++tt] = u;
			}
		} 
		len[p] = max(len[ne[p]], len[p]);
	}
}
void pushup(int u) {
	segtr[u].minn = min(segtr[u << 1].minn, segtr[u << 1 | 1].minn);
}
void buildSegtree(int u, int l, int r) {
	segtr[u] = {l, r, INF};
	if (l != r) {
		int mid = (l + r) >> 1;
		buildSegtree(u << 1, l, mid);
		buildSegtree(u << 1 | 1, mid + 1, r);
		pushup(u);
	}
}
void modify(int u, int x, int k) {
	if (segtr[u].l == segtr[u].r && segtr[u].l == x) segtr[u].minn = k;
	else {
		int mid = (segtr[u].l + segtr[u].r) >> 1;
		if (x <= mid) modify(u << 1, x, k);
		else modify(u << 1 | 1, x, k);
		pushup(u);
	}
}
int query(int u, int l, int r) {
	if (l <= segtr[u].l && segtr[u].r <= r) return segtr[u].minn;
	int mid = (segtr[u].l + segtr[u].r) >> 1, res = INF;
	if (l <= mid) res = min(res, query(u << 1, l, r));
	if (r > mid) res = min(res, query(u << 1 | 1, l, r));
	return res;
}
int main() {
	scanf("%d%s", &n, s + 1);
	for (int i = 0; i < n; i++) {
		scanf("%s", str);
		insert();
	}
	buildTrie();
	buildSegtree(1, 1, (int)strlen(s + 1));
	for (int i = 1, j = 0; s[i]; i++) {
		int u = s[i] - 'a';
		j = tr[j][u];
		int t;
		if (i - len[j] >= 1) t = query(1, i - len[j], i - 1) + 1;
		else t = 1;
		modify(1, i, t);
	}
	int ans = query(1, (int)strlen(s + 1), (int)strlen(s + 1));
	if (ans > (int)strlen(s + 1)) printf("-1");
	else printf("%d", ans);
	return 0;
} 
```

---

## 作者：Kevin090228 (赞：1)

### P7456 [CERC2018] The ABCD Murderer

> 给定一个文本串 $S$ 和一些串 $a_i$，你需要用一些 $a_i$ 拼成文本串 $S$，每个 $a_i$ 可以使用多次。相邻两个串可以重合，前提是它们重合部分相等。求最少需要多少个串，同一个串使用多次按照次数计算。

我们考虑 DP 状态 $f(i)$ 表示铺满前 $i$ 个字符最少需要用到多少个串。有两种转移：$f(i)\rightarrow f(i-1)$，和当 $S[i+1\cdots j]$ 是某个模式串时，$f(i)\rightarrow f(j)$。这时我们只需要求出 $S$ 中哪些区间是模式串然后建图跑最短路即可。但是图的大小是 $O(n^2)$ 级别的，考虑优化建图。

首先，我们注意到，若从 $i$ 点开始可以匹配多个不同的模式串，则匹配最长的那个一定是更优的。从 $i$ 点开始不太好做，我们可以将整个串反转然后用 AC 自动机跑多模匹配。

为什么这样做是正确的呢？我们有如下引理：

**引理：当一个结尾字符有多个可能匹配的模式串时，AC 自动机会匹配最长的一个。**

这样我们就把图转化成了 $O(n)$ 级别的，使用 01BFS 求解最短路即可。

时间复杂度 $O(n)$。

---

## 作者：Lgx_Q (赞：1)

# 题意

给出字符串 $S$ 和 $n$ 个单词 $s_1,...,s_n$，每个单词可以用无数次，问至少用多少个单词才能组成 $S$，单词组合时相同部分可以重叠。

---

第一眼看，发现是 $n$ 个字符串匹配，立刻想到 AC 自动机。

先建立一棵 AC 自动机。

设 $f[i]$ 为组成了 $S$ 的前 $i$ 个字符时所用的最少单词个数。

考虑最右边的单词，转移子问题。

若有多个单词满足条件，选择最长的那个，求最长可以在 BFS 的时候顺便求出。

设选择的单词长度为 $len$，那么转移为

$$f[i]=\min_{j=i-len}^{j<i}\{f[j]\}+1$$

这玩意直接用线段树优化即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+10;
int n,m,tree[maxn][26],tot=1,en[maxn],q[maxn],l,r,mn[maxn*4],f[maxn],fail[maxn];
char s[maxn],ss[maxn];
bool tofail[maxn];
void insert()
{
	int p=1,len=strlen(ss+1);
	for(int i=1;i<=len;i++)
	{
		int v=ss[i]-'a';
		if(!tree[p][v])
		{
			tree[p][v]=++tot;
		}
		p=tree[p][v];
	}
	en[p]=len;
}
void bfs()
{
	l=1;
	for(int i=0;i<26;i++)
	{
		if(tree[1][i])
		{
			q[++r]=tree[1][i];
			fail[tree[1][i]]=1;
		}
		else tree[1][i]=1;
	}
	while(l<=r)
	{
		int u=q[l++];
		for(int i=0;i<26;i++)
		{
			if(tree[u][i])
			{
				fail[tree[u][i]]=tree[fail[u]][i];
				en[tree[u][i]]=max(en[tree[u][i]],en[fail[tree[u][i]]]);
				q[++r]=tree[u][i];
			}
			else tree[u][i]=tree[fail[u]][i];
		}
	}
}
void modify(int p,int l,int r,int x,int v)
{
	if(l==r)
	{
		mn[p]=v;
		return;
	}
	int mid=l+r>>1;
	if(x<=mid) modify(p<<1,l,mid,x,v);
	else modify(p<<1|1,mid+1,r,x,v);
	mn[p]=min(mn[p<<1],mn[p<<1|1]);
}
int query(int p,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr) return mn[p];
	if(qr<l||r<ql) return 0x3f3f3f3f;
	int mid=l+r>>1;
	return min(query(p<<1,l,mid,ql,qr),query(p<<1|1,mid+1,r,ql,qr));
}
void solve()
{
	int p=1;
	modify(1,0,m,0,0);
	for(int i=1;i<=m;i++)
	{
		int v=s[i]-'a';
		p=tree[p][v];
		int tmp=en[p];
		f[i]=query(1,0,m,i-tmp,i-1)+1;
		modify(1,0,m,i,f[i]);
	}
}
int main()
{
	scanf("%d%s",&n,s+1);
	m=strlen(s+1);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",ss+1);
		insert();
	}
	bfs();
	memset(mn,0x3f,sizeof mn);
	solve();
	if(f[m]>=0x3f3f3f3f) f[m]=-1;
	printf("%d\n",f[m]);
	return 0;
}
```

---

