# LCS2 - Longest Common Substring II

## 题目描述

题面描述
给定一些字符串，求出它们的最长公共子串

## 样例 #1

### 输入

```
alsdfkjfjkdsal
fdjskalajfkdsla
aaaajfaaaa```

### 输出

```
2```

# 题解

## 作者：Kelin (赞：28)

### 题意

求$n$个串的$LCS$

---

### 题解

考虑怎么求两个串的$LCS$,也就是[$[Spoj1811]$](https://www.luogu.org/problemnew/show/SP1811)

先对其中一个串建立$SAM$,令$x=1,len=0$(我的$SAM$从$1$开始)

然后对于第二个字符串$s$我们一位一位考虑

根据$SAM$的性质

$1.$如果$x$有$s_i$这个儿子,我们可以直接跳下去,然后$len++$

$2.$否则让$x$不断在$parent$树上跳,直到$x$有$s_i$这个儿子为止,同时$len=Len(x)+1$,然后$x$再跳下去

$3.$如果$x$跳出$SAM$了那就令$x=1,len=0$重新开始

因为$Len(LCS)\le n$,每次在$parent$树上跳长度就会变小,所以最多会跳$Len(LCS)$次,所以复杂度是$O(n)$的

$Hint:$写的时候可以吧$1,2$种情况合并一下

那么多个串呢?

还是对第一个串建$SAM$,然后一个一个串处理

在处理每一个串的时候记录一下在每个节点最大匹配长度

然后因为有很多串,所以要再记录一下上面的东西的最小值,才是对所有串匹配长度

然后注意到一个能点被匹配,那么他在$parent$树上的祖先都能被匹配到

所以对于每一个点,要对他子树的答案取$max$,然后还有对自己的长度取$min$

不然的话这个点的最长匹配答案可能就会出错,然后影响全局的最小值,从而影响答案

试一下下面这组数据

```
dccccacdcbdbbbadbaa
cdcdbadaaabeddbddae
abdbecbddceaebacaca
debabcaccbbceccdcadd
```

```
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
const int N=2.5e5+5,M=2*N;
typedef int arr[N];
struct SAM{
    int las,T,fa[M],len[M],ch[M][26];
    inline void init(){las=T=1;}
    inline void ins(int c){
        int p=las,np;fa[las=np=++T]=1,len[T]=len[p]+1;
        for(;p&&!ch[p][c];p=fa[p])ch[p][c]=np;
        if(p){
            int q=ch[p][c],nq;
            if(len[p]+1==len[q])fa[np]=q;
            else{
                fa[nq=++T]=fa[q],len[T]=len[p]+1;memcpy(ch[nq],ch[q],4*26);
                for(fa[q]=fa[np]=nq;ch[p][c]==q;p=fa[p])ch[p][c]=nq;
            }
        }
    }
    int c[M],b[M];
    inline void sort(){
        fp(i,1,T)++c[len[i]];
        fp(i,1,T)c[i]+=c[i-1];
        fp(i,1,T)b[c[len[i]]--]=i;
    }
    int mx[M],mi[M];
    inline void work(char*s){
        int l=0,x=1,v;
        fp(i,0,strlen(s)-1){
            v=s[i]-'a';while(x&&!ch[x][v])x=fa[x],l=len[x];
            if(x)++l,x=ch[x][v],cmax(mx[x],l);else x=1,l=0;
        }
        fd(i,T,1){
            int u=b[i],f=fa[u];
            cmax(mx[f],min(mx[u],len[f]));
            cmin(mi[u],mx[u]);mx[u]=0;
        }
    }
}p;
int ans;char s[N];
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
    scanf("%s",s);p.init();
    fp(i,0,strlen(s)-1)p.ins(s[i]-'a');
    memset(p.mi,63,sizeof p.mi);p.sort();
    while(~scanf("%s",s))p.work(s);
    fp(i,1,p.T)cmax(ans,p.mi[i]);
    printf("%d",ans);
return 0;
}
```

最近发现数组版的$SAM$比结构体版快好多,难道因为每个$node$里面还嵌套了数组么$qwq$

---

## 作者：HenryHuang (赞：24)

# SP1812 LCS2 - Longest Common Substring II

题目大意：给定 $n(n \le 10)$ 个字符串，求最长公共子串长度。

这里提供一种使用 SA 的做法。

首先将给定的所有字符串连在一起串成一个字符串，字符串之间用题目限定字符集之外的字符分隔开，我们称这个字符串为 $s$。

我们求出其 $\texttt{height}$ 数组，那么问题实际上转化为：在 $\texttt{height}$ 数组上找连续的一段，使得这一段包含来自给定的每个字符串的至少一个后缀，设这样的第 $i$ 个区间为 $[l_i,r_i]$ ，则最后的答案为 $\min_{l_i< x \le r_i}{\texttt{height}_i}$。

首先不考虑计算答案，只考虑计算区间的话，这是一个非常经典的问题，直接使用 $\texttt{two-pointer}$ 即可以在 $O(n)$ 的时间复杂度内求出所有这样的区间。具体做法就用一个数组表示来自第 $i$ 个字符串的后缀出现了几次，动态更新即可。

接下来考虑计算答案，这同样是一个经典问题，类比「滑动窗口」，我们可以维护一个单调队列，随着 $\texttt{two-pointer}$ 过程中区间的扩张与收缩对单调队列进行更新即可。时间复杂度为 $O(n)$。

综上，总时间复杂度为 $O(nlog_2n)$。瓶颈在于构造后缀数组，如果使用线性构造方法可以做到 $O(n)$。

以下是代码：

```cpp
/*---Author:HenryHuang---*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=1.2e6+5;
char s[maxn];
int sa[maxn],rk[maxn],tp[maxn],cnt[maxn];
int n,m,N;
int height[maxn],h[maxn];
int vis[maxn],col[maxn],ok;
inline void sort(){
	memset(cnt,0,sizeof (int)*(m+1));
	for(int i=1;i<=n;++i) ++cnt[rk[i]];
	for(int i=1;i<=m;++i) cnt[i]+=cnt[i-1];
	for(int i=n;i>=1;--i) sa[cnt[rk[tp[i]]]--]=tp[i];
}//基数排序 
int L[20],R[20];
void add(int x){
	if(col[x]==0) return ;
	++vis[col[x]];
	if(vis[col[x]]==1) ++ok;
}
void del(int x){
	if(col[x]==0) return ;
	--vis[col[x]];
	if(!vis[col[x]]) --ok;
}//two-pointer更新 
int main(){
	while(cin>>(s+n+1)){
		++N;
		L[N]=n+1;
		n+=strlen(s+n+1);
		R[N]=n;
		s[++n]=N+'0';
	}
	m='z';
	for(int i=1;i<=n;++i) rk[i]=s[i]-'0'+1,tp[i]=i;
	sort();
	for(int w=1,p=0;p<n;m=p,w<<=1){
		p=0;
		for(int i=n;i>n-w;--i) tp[++p]=i;
		for(int i=1;i<=n;++i) if(sa[i]>w) tp[++p]=sa[i]-w;
		sort();swap(tp,rk);
		rk[sa[1]]=p=1;
		for(int i=2;i<=n;++i)
			rk[sa[i]]=(tp[sa[i-1]]==tp[sa[i]]&&tp[sa[i-1]+w]==tp[sa[i]+w])?p:++p;
	}
	for(int i=1;i<=n;++i) rk[sa[i]]=i;
	int k=0;
	for(int i=1;i<=n;++i){
		if(rk[i]==1) continue;
		if(k) --k;
		int j=sa[rk[i]-1];
		while(i+k<=n&&j+k<=n&&s[i+k]==s[j+k]) ++k;
		height[rk[i]]=k;
	}//求height 
	for(int i=1;i<=N;++i){
		for(int j=L[i];j<=R[i];++j)
			col[rk[j]]=i;
		;
	}
	deque<int>q;
	int l=1,ans=0;
	add(1);
	for(int r=2;r<=n;++r){
		while(!q.empty()&&height[q.back()]>=height[r]) q.pop_back();
		q.emplace_back(r);
		add(r);
		if(ok==N){
			while(ok==N&&l<r) del(l),++l;
			--l,add(l);
		}
		while(!q.empty()&&q.front()<=l) q.pop_front();//注意这里是等于，区间内第一个位置的height大小我们不关心 
		if(ok==N) ans=max(ans,height[q.front()]);
	}//求解答案 
	cout<<ans<<'\n';
	return 0;
}
```





 

---

## 作者：KokiNiwa (赞：9)

[更好阅读体验](https://www.cnblogs.com/skiceanAKacniu/)
# 题目概述
求$n$个字符串的最长公共子串。$n\le 10$。
# 题解
对于最短字符串建立`SAM`。
考虑将其他字符串放到这个`SAM`上匹配，并记录`mx[i]`表示以`i`为结尾的字符串最长匹配长度。
从根开始向后匹配。如果自动机上可以向后匹配字符，就走一条转一边，转移到下一个结点；否则跳`parent`树，知道存在这个字符的转移边为止。
如果永远没有，那么从根开始重新匹配。每匹配到一个节点，就更新`mx[i]`。
匹配完再对于每一个`mx[fa[i]]`从`mx[i]`更新。这是因为一个节点的`par`必然在他的儿子中出现，但却有可能没有匹配到`par`这个节点。
容易证明这样每个结点都有最长匹配值。
再记录`mn[i]`表示`i`结点在每一个字符串中的最长匹配长度的最小值。
那么所有结点的`mn[i]`就是答案。
> 注：之所以选取最短字符串建立`SAM`是因为每次匹配后都要遍历整个`SAM`并更新`SAM`每个节点的`mx`值，如果不选取最短串有可能复杂度并不是$\mathcal O(\sum s_i)$的*
# 代码
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e5 + 5, NODE = 2 * N;
int n, len[11], mnId, mx[NODE];
char str[11][N];
struct SAM {
	int ch[NODE][26], len[NODE], fa[NODE], mx[NODE], las, t, buc[N], od[NODE], mn[NODE];
	SAM() { las = t = 1; }
	void ins(int c) {
		int p = las, np;
		fa[las = np = ++t] = 1;
		len[t] = len[p] + 1;
		for (; p && !ch[p][c]; p = fa[p])
			ch[p][c] = np;
		if (p) {
			int q = ch[p][c], nq;
			if (len[p] + 1 == len[q])
				fa[np] = q;
			else {
				fa[nq = ++t] = fa[q];
				len[t] = len[p] + 1;
				memcpy(ch[nq], ch[q], sizeof(ch[nq]));
				for (fa[np] = fa[q] = nq; ch[p][c] == q; p = fa[p])
					ch[p][c] = nq;
			}
		}
	}
	void init(int le) {
		for (int i = 1; i <= t; ++i)
			++buc[len[i]];
		for (int i = 1; i <= le; ++i) //这里 n并不是字符串长度... 
			buc[i] += buc[i - 1];
		for (int i = 1; i <= t; ++i)
			od[buc[len[i]]--] = i;
		for (int i = 1; i <= t; ++i)
			mn[i] = 0x3f3f3f3f;
	}
	void calc(char *s, int n) {
		int now = 1, l = 0;
		for (int i = 1; i <= t; ++i)
			mx[i] = 0;
		for (int i = 1; i <= n; ++i) {
			while (now && !ch[now][s[i] - 'a'])
				now = fa[now], l = len[now];
			if (now) {
				now = ch[now][s[i] - 'a'];
				mx[now] = max(mx[now], ++l);
			} else {
				now = 1;
				l = 0;
			}
		}
		for (int i = 1; i <= t; ++i) {
			mx[fa[od[i]]] = min(max(mx[fa[od[i]]], mx[od[i]]), len[fa[od[i]]]);
			mn[od[i]] = min(mn[od[i]], mx[od[i]]);
		}
	}
} sam;
int main() {
	mnId = 1;
	while (~scanf("%s", str[++n] + 1)) {
		len[n] = strlen(str[n] + 1);
		if (len[mnId] > len[n])
			mnId = n;
	}
	--n;
	for (int i = 1; i <= len[mnId]; ++i)
		sam.ins(str[mnId][i] - 'a');
	sam.init(len[mnId]);
	for (int i = 1; i <= n; ++i)
		if (i != mnId)
			sam.calc(str[i], len[i]);
	int ans = 0;
	for (int i = 1; i <= sam.t; ++i)
		ans = max(ans, sam.mn[i]);
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Refined_heart (赞：6)

$\text{Suffix Tree:}$我来啦我来啦

[$\color{purple}{\text{Refinedheart's blog}}$](https://www.cnblogs.com/h-lka/p/13194778.html)

$\text{Solution:}$

题目要求求好几个串串的$\text{LCS.}$

由于串串的数量并不多，所以我们把它们塞到一个$\text{Suffix Tree}$里面，中间加上分隔符号。

那么答案就是最深的且它的子树中具有所有分节符的非叶子节点。

至于分节符数量和种类，用前缀和即可。

介于$\text{Suffix Tree}$压缩的性质，菜鸡笔者还不太清楚一边插入一边维护的方法，求指教。

前缀和维护的原理：由于最前面的绝对先出现，所以从第一个枚举到最后一个，看看这个区间中是不是有这个串串的分节符。如果有，跳出即可。因为它所代表的后缀只属于这一个串串。

至于如何判断这些分节符是不是都有，用了状压。$\text{1<<i}$表示第$i$个分节符有没有，统计的时候用或运算即可。

话说$\text{Fread}$可以读入这种非固定数量的字符咩？

```cpp
#include<bits/stdc++.h>
#include<ctime>
using namespace std;
const int MAXN=2e6+10;
char Z[20][100001];
int n,val[MAXN],ans,M,tot,num;
int sum[20][MAXN];
const int inf=(1<<30);
struct SuffixTree {
	int link[MAXN],ch[MAXN][50],now,rem,n;
	int start[MAXN],len[MAXN],tail,s[MAXN];
	SuffixTree() {
		tail=now=1;
		rem=n=0;
		len[0]=inf;
	}
	inline int build(int a,int b) {
		link[++tail]=1;
		start[tail]=a;
		len[tail]=b;
		return tail;
	}
	void Extend(int x) {
		s[++n]=x;
		++rem;
		for(int last=1; rem;) {
			while(rem>len[ch[now][s[n-rem+1]]])
				rem-=len[now=ch[now][s[n-rem+1]]];
			int &v=ch[now][s[n-rem+1]];
			int c=s[start[v]+rem-1];
			if(!v||x==c) {
				link[last]=now;
				last=now;
				if(!v)v=build(n,inf);
				else break;
			} else {
				int u=build(start[v],rem-1);
				ch[u][c]=v;
				ch[u][x]=build(n,inf);
				start[v]+=rem-1;
				len[v]-=rem-1;
				link[last]=v=u;
				last=u;
			}
			if(now==1)--rem;
			else now=link[now];
		}
	}
} T;
void predfs(int u,int dep) {
	if(dep>=inf) {
		int L=T.start[u];
		int R=L+T.len[u]-1;
		R=min(R,T.n);
		for(int i=1;i<=num;++i){
			if(sum[i][R]-sum[i][L-1]){
				val[u]|=(1<<i);
				break;
			}
		}
		return;
	}
	for(int i=0; i<=25+num; ++i) {
		if(T.ch[u][i]) {
			predfs(T.ch[u][i],dep+T.len[T.ch[u][i]]);
			val[u]|=val[T.ch[u][i]];
		}
	}
	if(val[u]==M)ans=max(ans,dep);
}
int main() {
	while(scanf("%s",Z[++num]+1)!=EOF);
	num--;
	int G='0';int len=strlen(Z[1]+1);
	Z[1][++len]=(char)G;
	for(int i=2;i<=num;++i){
		G++;
		int L=strlen(Z[i]+1);
		for(int j=1;j<=L;++j)Z[1][++len]=Z[i][j];
		Z[1][++len]=(char)G;
	}
	for(int i=1;i<=num;++i)M+=(1<<i);
	for(int i=1;i<=len;++i){
		if(Z[1][i]>='a')T.Extend(Z[1][i]-'a');
		else T.Extend(Z[1][i]-'0'+1+25);
	}
	for(int i=1;i<=len;++i){
		
		for(int j=1;j<=num;++j)sum[j][i]=sum[j][i-1];
		if(T.s[i]>25){
			int V=T.s[i]-25;
			sum[V][i]++;
		}
	}
	predfs(1,0);
	cout<<ans<<endl;
	return 0;
}
```
注意，分节符不要超过$\text{ASCII}$表的范围，不然喜提$RE.$

---

## 作者：lhm_ (赞：6)

对于本题这样的多字符串的子串匹配问题，其实用广义后缀自动机就可以很好的解决，感觉会比普通的后缀自动机做法方便一些。

首先记录出每个节点被多少个字符串更新，也就是记录每个节点有多少个字符串能到达它，可以通过在$Parent$树上求子树和处理出。

若所有字符串都能到达一个节点，也就是该节点所对应的串为所有字符串的子串，那么该节点是一个合法的转移状态。

那么就可以直接拿这些字符串中的任意一个字符串在自动机上匹配，就像[LCS - Longest Common Substring](https://www.luogu.com.cn/problem/SP1811)一样，只向合法状态转移，记录当前匹配出的最长公共子串的最大长度即可。

实现细节看代码吧。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 2000010
using namespace std;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,las,tot=1,root=1,num,ans;
int fa[maxn],len[maxn],ch[maxn][30],siz[maxn][12];
char s[maxn];
struct edge
{
    int to,nxt;
}e[maxn];
int head[maxn],edge_cnt;
void add(int from,int to)
{
    e[++edge_cnt]=(edge){to,head[from]};
    head[from]=edge_cnt;
}
void insert(int c,int id)
{
    int p=las,np=las=++tot;
    len[np]=len[p]+1,siz[np][id]++;
    while(p&&!ch[p][c]) ch[p][c]=np,p=fa[p];
    if(!p) fa[np]=root;
    else
    {
        int q=ch[p][c];
        if(len[q]==len[p]+1) fa[np]=q;
        else
        {
            int nq=++tot;
            memcpy(ch[nq],ch[q],sizeof(ch[q]));
            len[nq]=len[p]+1,fa[nq]=fa[q],fa[q]=fa[np]=nq;
            while(ch[p][c]==q) ch[p][c]=nq,p=fa[p];
        }
    }
}
void dfs(int x)
{
    for(int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        dfs(y);
        for(int id=1;id<=num;++id)
            siz[x][id]+=siz[y][id];
    }
}
bool check(int p)
{
    if(!p) return false;
    for(int i=1;i<=num;++i)
        if(!siz[p][i])
            return false;
    return true;
}
void work()
{
    for(int i=2;i<=tot;++i) add(fa[i],i);
    dfs(root);
    int p=root,l=0;
    for(int i=1;i<=n;++i)
    {
        int c=s[i]-'a';
        if(check(ch[p][c])) l++,p=ch[p][c];
        else
        {
            while(p&&!check(ch[p][c])) p=fa[p];
            if(p) l=len[p]+1,p=ch[p][c];
            else l=0,p=root;
        }
        ans=max(ans,l);
    }
}
int main()
{
    while(scanf("%s",s+1)!=EOF)
	{
		n=strlen(s+1),las=root,num++;
		for(int i=1;i<=n;++i) insert(s[i]-'a',num);
	}
    work(),printf("%d\n",ans);
    return 0;
}
```

---

## 作者：jiazhaopeng (赞：5)

本文主要是对[lhm大佬的题解](https://www.luogu.com.cn/blog/lhm126/solution-sp1812)的一些优化。

毕竟是多串的问题，写广义后缀自动机要更方便些。首先建出广义后缀自动机。然后记录下每个节点有多少个字符串能到达它。如果一个节点可以被所有字符串到达，那么**这个节点的 $len$ 可以更新答案。**

为什么每个节点的 $len$ 都可以更新答案呢？因为如果一个字符串能够到达这个节点（含通过跳 $fa$，即 $suffix~link$，可以到达），那么这个字符串中一定含有这个节点存储（即能到达这个节点）的最长的子串。因为如果不包含的话，我们会新建一个节点，然后把答案更新到那里去。对于单串的后缀自动机很好理解，其实多串也一样。

我的广义后缀自动机的建法可能和大佬的不太一样，但是应该不会影响吧？

$Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <string>
#define N 2001000
template<typename T> inline void read(T &x) {
	x = 0; char c = getchar(); bool flag = false;
	while (!isdigit(c)) {if (c == '-') flag = true; c = getchar(); }
	while (isdigit(c)) {x = (x << 1) + (x << 3) + (c ^ 48); c = getchar(); }
	if (flag)	x = -x;
}
using namespace std;
char s[N];
int son[N][26], fa[N], len[N], tot = 1;
int id;
bool siz[N][13];//只需要知道有没有经过即可，不需要知道经过几次 。不过不重要 
inline int ins(int c, int lst) {//建广义SAM 
	if (son[lst][id] && len[son[lst][id]] == len[lst] + 1)
		return siz[son[lst][id]][id] = true, son[lst][id];
	int np = ++tot, p = lst;
	len[np] = len[p] + 1; siz[np][id] = true;
	while (p && !son[p][c])	son[p][c] = np, p = fa[p];
	if (!p)	return fa[np] = 1, np;
	int q = son[p][c];
	if (len[q] == len[p] + 1)	return fa[np] = q, np;
	bool flag = p == lst;
	int nq = ++tot;
	if (flag)	siz[np][id] = false, siz[nq][id] = true;
	len[nq] = len[p] + 1;
	fa[nq] = fa[q], fa[q] = fa[np] = nq;
	memcpy(son[nq], son[q], sizeof(son[q]));
	while (p && son[p][c] == q)	son[p][c] = nq, p = fa[p];
	return flag ? nq : np;
}

int ans;
int Id[N], bin[N];
inline void Sort() {//按len排序 
	for (register int i = 1; i <= tot; ++i)	bin[len[i]]++;
	for (register int i = 1; i <= tot; ++i)	bin[i] += bin[i - 1];
	for (register int i = tot; i; --i)	Id[bin[len[i]]--] = i;
}
inline void get_siz() {//更新siz并统计答案 
	for (register int i = tot; i; --i) {
		int p = Id[i];
		bool flag = true;
		for (register int j = 1; j <= id; ++j) {
			siz[fa[p]][j] |= siz[p][j];
			if (!siz[p][j])	flag = false;
		}
		if (flag)	ans = max(ans, len[p]);
	}
}
int main() {
	while (scanf("%s", s + 1) != EOF) {
		int lst = 1, n = strlen(s + 1);
		id++;
		for (register int i = 1; i <= n; ++i) {
			int c = s[i] - 'a';
			lst = ins(c, lst);
		}
	}
	Sort();
	get_siz();
	printf("%d\n", ans);
	return 0;
}
/*
alsdfkjfjkdsal
fdjskalajfkdsla
aaaajfaaaa
//2
*/
```

---

## 作者：DengDuck (赞：3)

比较套路的题，其实二分完全是可以的，卡卡常跑得飞快。

首先拼接成一个字符串，中间放特殊符号是显然的。

套路是二分，然后变成判断是否存在满足条件的长度为 $k$ 的子串。

由于需要满足长度为 $k$，我们就可以以 $height$ 的值将后缀分组，如果存在 $height(i)<k$ 就断开，$i$ 往后作为一个新的组。

这样可以保证组内任意两个后缀的最长公共前缀长度至少为 $k$，所以我们考虑是否存在组满足条件即可，对于这题，我们只需要保证每个字符串都有对应的后缀在组内。 

时间复杂度为 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL int
using namespace std;
const LL N=2e6+5;
LL T,n,L[N],R[N],sa[N],rk[N],h[N],b[N],tmp[N],tmp2[N],m=200,hav[12];
char s[N],a[N];
bool pd(LL x)
{
	for(int i=1;i<=n;i++)
	{
		if(h[i]<x)
		{
			LL flg=1;
			for(int j=1;j<=T;j++)
			{
				if(!hav[j])
				{
					flg=0;
					break;
				}
			}for(int i=1;i<=T;i++)hav[i]=0;
			if(flg)return 1;
			
		}
		for(int j=1;j<=T;j++)
		{
			if(L[j]<=sa[i]&&sa[i]<=R[j])
			{
				hav[j]=1;
				break;
			}			
		}
	}
	LL flg=1;
	for(int j=1;j<=T;j++)
	{
		if(!hav[j])
		{
			flg=0;
			break;
		}
	}for(int i=1;i<=T;i++)hav[i]=0;
	if(flg)return 1;
	
	return 0;
}
int main()
{
	
	while(~scanf("%s",s+1))
	{
		
		L[++T]=n+1,R[T]=n+strlen(s+1);
		for(int j=L[T];j<=R[T];j++)a[j]=s[j-L[T]+1];
		n=R[T]+1;
		a[n]='#'+T-1;
	}
	for(int i=1;i<=n;i++)b[rk[i]=a[i]]++;
	for(int i=1;i<=m;i++)b[i]+=b[i-1];
	for(int i=n;i>=1;i--)sa[b[rk[i]]--]=i;
	LL t=0;
	for(int i=1;i<=n;i++)tmp[i]=rk[i];
	for(int i=1;i<=n;i++)
	{
		if(tmp[sa[i]]==tmp[sa[i-1]])rk[sa[i]]=t;
		else rk[sa[i]]=++t;
	}
	m=t;
	for(LL l=1;l<n;l<<=1)
	{
		LL t=0;
		for(int i=n-l+1;i<=n;i++)tmp[++t]=i;
		for(int i=1;i<=n;i++)if(sa[i]>l)tmp[++t]=sa[i]-l;
		for(int i=1;i<=m;i++)b[i]=0;
		for(int i=1;i<=n;i++)++b[tmp2[i]=rk[tmp[i]]];
		for(int i=1;i<=m;i++)b[i]+=b[i-1];
		for(int i=n;i>=1;i--)sa[b[tmp2[i]]--]=tmp[i];
		for(int i=1;i<=n;i++)tmp[i]=rk[i];
		t=0;
		for(int i=1;i<=n;i++)
		{
			if(tmp[sa[i]]==tmp[sa[i-1]]&&tmp[sa[i]+l]==tmp[sa[i-1]+l])rk[sa[i]]=t;
			else rk[sa[i]]=++t;
		}
		
		m=t;
		if(m==n)break;
	}
	t=0;
	for(int i=1;i<=n;i++)
	{
		if(rk[i]==1)continue;
		if(t)t--;
		while(a[i+t]==a[sa[rk[i]-1]+t])t++;
		h[rk[i]]=t;
		
	}
	LL l=1,r=n,ans=0;
	while(l<=r)
	{
		LL mid=(l+r)/2;
		if(pd(mid))ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d",ans);
}
```

---

## 作者：crashed (赞：3)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/SP1812)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我们想要建立一个只包含多个串的公共子串的后缀自动机。最简单地，先建立一个串的后缀自动机。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后考虑如何进行扩展。在两个串的情况下，我们可以直接把另一个串放到后缀自动机上面跑，中途得到答案。在多个串的情况下显然就不会这么简单了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑每一个串都放到后缀自动机上面跑一跑。对于每一个点，我们就可以存下来它在当前这个串中以它结尾的串的最大长度。一次遍历之后，答案就是这些最大长度中间的最大值。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;要都是公共的情况，只需要每次遍历完之后，将每个点每次的最大长度取最小值（对于每一个点，$s_1$遍历出来最大长度为$a$，$s_2$为$b$，$a>b$的话，$b$肯定是$a$的子串，也就既是$s_1$也是$s_2$的子串）之后，总体再取最大值即可。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;需要注意的是，如果一个串的得到的最大长度比它父亲的在后缀自动机上的最大长度长，那么就要更新父亲的得到的最大长度（它的父亲是它的后缀）。这个可以在每次遍历结束后用一次拓扑序$+dp$更新完成。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;在两个串的时候不用这么做是因为，如果不能更新，就不能更新，如果可以更新也没有什么意义（答案不会更大）。
# 代码
```cpp
#include <cstdio>
#include <cstring>

const int MAXN = 100005;

const int MAXCNT = 15;

template<typename _T>
void read( _T &x )
{
	x = 0; char s = getchar();int f = 1;
	while( s < '0' || '9' < s ) { f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + s - '0', s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ) { putchar( '-' ), x = -x; }
	if( 9 < x ) { write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

int seq[MAXN << 1], cnt[MAXN << 1];
char str[MAXCNT][MAXN];
int l[MAXCNT];
int ch[MAXN << 1][26], fa[MAXN << 1], mx[MAXN << 1], nmx[MAXN << 1], mn[MAXN << 1];
int K, rt, tot, lst;

void copy( const int a, const int b ) { fa[a] = fa[b], mx[a] = mx[b], memcpy( ch[a], ch[b], sizeof ch[b] ); }

void expand( const char c )
{
	int x = c - 'a', p = lst, cur = ++ tot;
	mx[cur] = mx[lst] + 1, lst = cur;
	while( p && ! ch[p][x] ) ch[p][x] = cur, p = fa[p];
	if( ! p ) { fa[cur] = rt; return ; }
	int q = ch[p][x];
	if( mx[q] == mx[p] + 1 ) { fa[cur] = q; return ; }
	int nq = ++ tot; copy( nq, q );
	mx[nq] = mx[p] + 1, fa[cur] = fa[q] = nq;
	while( p && ch[p][x] == q ) ch[p][x] = nq, p = fa[p];
}

void topo()
{
	for( int i = 1 ; i <= tot ; i ++ ) cnt[mx[i]] ++;
	for( int i = 1 ; i <= tot ; i ++ ) cnt[i] += cnt[i - 1];
	for( int i = tot ; i ; i -- ) seq[cnt[mx[i]] --] = i;
}

//基排得到拓扑序

int main()
{
	while( ~ scanf( "%s", str[++ K] + 1 ) ) l[K] = strlen( str[K] + 1 ); K --;
	rt = lst = ++ tot;
	for( int i = 1 ; i <= l[1] ; i ++ ) expand( str[1][i] );
	for( int i = 1 ; i <= tot ; i ++ ) mn[i] = mx[i];  //一个点的公共的最大长度不会超过后缀自动机上面的最大长度
	topo();
	int p, len, x;
	for( int j = 2 ; j <= K ; j ++ )
	{
		len = 0, p = rt;
		for( int i = 1 ; i <= l[j] ; i ++ )
		{
			x = str[j][i] - 'a';
			while( p && ! ch[p][x] ) p = fa[p], len = mx[p];
			if( p ) len ++, p = ch[p][x], nmx[p] = MAX( nmx[p], len );
			else len = 0, p = rt;
		}
		for( int i = tot, np ; i ; i -- )
		{
			np = seq[i]; if( fa[np] ) nmx[fa[np]] = MAX( nmx[fa[np]], MIN( mx[fa[np]], nmx[np] ) );    //对父亲更新
			mn[np] = MIN( mn[np], nmx[np] ), nmx[np] = 0;  //记得nmx要清零
		}
	}
	int res = 0;
	for( int i = 1 ; i <= tot ; i ++ ) res = MAX( res, mn[i] );  //全局取max得到答案
	write( res ), putchar( '\n' ); 
	return 0;
}
```

---

## 作者：wzj423 (赞：3)

之前，在两个串的LCS问题中，我们通过在一个串的SAM上跑另外一个串来统计每个节点能匹配的最大值来计算LCS，而多个串的问题中,我们需要另外的附加维护来计算LCS.

事实上,每一个节点在两串问题中仅仅维护了当前节点能够匹配的最大值,但实际上这些值是能够归并的,对于一个节点x有效的答案对于fa[x]同样有效.对于多个串统计的时候,因为要进行每个串的计算结果之间的比较,我们就需要按照parent树进一步维护.

一般而言,我们需要维护两个量:
mxv (maxvalue) 储存每一个节点在匹配某一个串时候的最大值
mnv (minvalue) 储存每一个节点在匹配之前所有串时候的总的最小值

每一次计算的时候,我们清空mxv,按照1811的方式(两串)更新mxv,之后再一边按照parent树自下而上更新,一边更新mnv

```c
for topo_seq
	x->fa[x] 	(mxv)
    x->x 		(mxv->mnv)

```

```cpp
#include <bits/stdc++.h>
const int MAXN=250010;
using namespace std;
//defs-----------------------------------------
char s[MAXN];int N;
//sam===========================================
int ch[MAXN*2][26],fa[MAXN*2],l[MAXN*2],last=1,cnt=1;
int sz[MAXN*2];
void ins(int c) {
    int p=last,np=++cnt;
    last=np;l[np]=l[p]+1;
    for(;p && !ch[p][c];p=fa[p]) ch[p][c]=np;
    if(!p)  fa[np]=1;
    else {
        int q=ch[p][c];
        if(l[q]==l[p]+1) fa[np]=q;
        else {
            int nq=++cnt; l[nq]=l[p]+1;
            memcpy(ch[nq],ch[q],sizeof (ch[q]));
            fa[nq]=fa[q]; fa[q]=fa[np]=nq;
            for(;ch[p][c]==q;p=fa[p]) ch[p][c]=nq;
        }
    }
    sz[np]=1;
}
int tax[MAXN],b[MAXN];
void Rsort() {
    for(int i=1;i<=cnt;++i) tax[i]=0;
    for(int i=1;i<=cnt;++i) tax[l[i]]++;
    for(int i=1;i<=cnt;++i) tax[i]+=tax[i-1];
    for(int i=1;i<=cnt;++i) b[ tax[l[i]]-- ] = i;
}
void cmx(int &a,int b) {
    if(a<b) a=b;
}
void cmn(int &a,int b) {
    if(a>b) a=b;
}
int mxv[MAXN];//储存每一个节点在匹配某一个串时候的最大值
int mnv[MAXN];//储存每一个节点在匹配之前所有串时候的总的最小值
/*
    一个节点的答案要更新为parent树内子树的答案
    否则如果parent子树之内有两个节点在不同串匹配时分别取到最大值
    不更新到父节点就会出错
*/
void cal() {
    int x=1,val=0,c;
    for(int i=0;i<N;++i) {
        c=s[i]-'a';
        while(x&&!ch[x][c]) x=fa[x],val=l[x];
        if(x) ++val,x=ch[x][c],cmx(mxv[x],val);
        else x=1,val=0;
    }
    for(int i=cnt;i>=1;--i) {
        int x=b[i],f=fa[x];
        //printf("x=%d,f=%d\n",x,f);
        cmx(mxv[f],min(mxv[x],l[f]) );//向上更新
        cmn(mnv[x],mxv[x]);
        mxv[x]=0;
    }
}
//main-------------------------------------------
int main() {
    freopen("in/1812.in","r",stdin);
    scanf("%s",s);N=strlen(s);
    for(int i=0;i<N;++i) ins(s[i]-'a');
    memset(mnv,0x3f,sizeof mnv);
    int enc=0;
    Rsort();
    while(true) {
        s[0]=s[1]=0;
        scanf("%s",s);N=strlen(s);
        if(N==0) break;
        ++enc;
        cal();
    }
    int ans=0;
    for(int i=1;i<=cnt;++i) {
        cmx(ans,mnv[i]);
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：chihik (赞：2)


我们可以思考一下如何用$\text{SAM}$求两个串的最长公共子串[点这里](https://www.luogu.com.cn/blog/deng-feng-chui-lai/solution-sp1811)。

多个字符串匹配也很简单，对于每个节点记录每个字符串能匹配的最大值的最小值。

求最大值就是求两个串的最长公共子串，只不过需要给父节点更新，每次取最小值就得到答案。

只不过为了保证先更新儿子，再更新父亲，我们需要用拓扑序实现。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define INF 0x3f3f3f3f

const int MAXN = 2 * 100000 , MAXC = 26;
struct Suffix_Automaton {
	int Size , Last , Root , Maxlen[ MAXN + 5 ];
	int Trans[ MAXN + 5 ][ MAXC + 5 ] , Link[ MAXN + 5 ];
	int Max[ MAXN + 5 ] , Min[ MAXN + 5 ];	
	int Sortlen[ MAXN + 5 ] , tot[ MAXN + 5 ];
	
	Suffix_Automaton( ) { Root = Size = Last = 1; }
	
	void Copy( int u , int v ) {
		for( int i = 1 ; i <= MAXC ; i ++ )
			Trans[ u ][ i ] = Trans[ v ][ i ];
	}
	void Extend( int chr ) {
		int Newnode = ++ Size , u = Last;
		Maxlen[ Newnode ] = Maxlen[ u ] + 1;
		
		for( ; u && !Trans[ u ][ chr ] ; u = Link[ u ] )
			Trans[ u ][ chr ] = Newnode;
		
		if( !u ) Link[ Newnode ] = Root;
		else {
			int v = Trans[ u ][ chr ];
			
			if( Maxlen[ v ] == Maxlen[ u ] + 1 ) Link[ Newnode ] = v;
			else {
				int w = ++ Size;
				Copy( w , v ); Maxlen[ w ] = Maxlen[ u ] + 1;
				for( ; u && Trans[ u ][ chr ] == v ; u = Link[ u ] ) Trans[ u ][ chr ] = w;
				Link[ w ] = Link[ v ];
				Link[ v ] = Link[ Newnode ] = w;
			}
		}
		Last = Newnode;
	}
	
	void Sort( ) {
		for( int i = 1 ; i <= Size ; i ++ ) tot[ Maxlen[ i ] ] ++;
		for( int i = 1 ; i <= Size ; i ++ ) tot[ i ] += tot[ i - 1 ];
		for( int i = 1 ; i <= Size ; i ++ ) Sortlen[ tot[ Maxlen[ i ] ] -- ] = i;
	}
	void Build( char *str ) {
		int len = strlen( str );
		for( int i = 0 ; i < len ; i ++ )
			Extend( str[ i ] - 'a' + 1 );
		Sort( );
		for( int i = 1 ; i <= Size ; i ++ ) Min[ i ] = INF;
	}

	void Work( char *str ) {
		int len = strlen( str );
		int u = Root , cnt = 0;
		for( int i = 0 ; i < len ; i ++ ) {
			int ch = str[ i ] - 'a' + 1;
			for( ; u && !Trans[ u ][ ch ] ; u = Link[ u ] ) cnt = Maxlen[ Link[ u ] ]; 
			if( u ) {
				u = Trans[ u ][ ch ];
				Max[ u ] = max( Max[ u ] , ++ cnt );
			}
			else	
				u = Root , cnt = 0;
		}
		
		for( int i = Size ; i >= 1 ; i -- ) {
			int u = Sortlen[ i ] , Fa = Link[ u ];
			Max[ Fa ] = max( Max[ Fa ] , min( Maxlen[ Fa ] , Max[ u ] ) );
			Min[ u ] = min( Min[ u ] , Max[ u ] ); Max[ u ] = 0;
		}
	}
}SAM;

int n , Ans;
char str[ 11 ][ MAXN + 5 ];
int main( ) {
	for( n = 1 ; ~scanf("%s",str[ n ]) ; n ++ ); n --;
	SAM.Build( str[ 1 ] ); 
	for( int i = 2 ; i <= n ; i ++ ) SAM.Work( str[ i ] );
	
	for( int i = 1 ; i <= SAM.Size ; i ++ )
		Ans = max( Ans , SAM.Min[ i ] );
	printf("%d",Ans);
	return 0;
}
```


---

## 作者：Jμdge (赞：2)

一个人的遭遇： 这题用了 map  于是一直 T

所以写 **这题** SAM 不要用 map 


# problem

题目没什么特别的，就是多串 lcs 


# noteskey

就是对第一个串建个 SAM ，然后别的串在上面跑，更新一个点结尾的最长 lcs 

然后每次别忘清空 mx 数组就好了

# code

```
//by Judge
#include<cstdio>
#include<cstring>
#include<iostream>
#define fp(i,a,b) for(int i=(a),I=(b)+1;i<I;++i)
#define fd(i,a,b) for(int i=(a),I=(b)-1;i>I;--i)
#define ll long long
using namespace std;
const int M=2.5e5+3;
typedef int arr[M];
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
inline int Min(int a,int b){return a<b?a:b;}
inline bool cmax(int& a,int b){return a<b?a=b,1:0;}
inline bool cmin(int& a,int b){return a>b?a=b,1:0;}
inline bool reads(string& s){ char c=getchar();
	for(;!isalpha(c);c=getchar()) if(c==EOF) return 0;
	for(;isalpha(c);c=getchar()) s+=c; return 1;
} int n,ans; char s[M];
struct SAM { int las,cnt; SAM() { las=cnt=1; }
	int to[M][26]; arr c,sa,fa,len,mn,mx;
	inline void insert(int c){
		int p=las,np=++cnt; las=np,len[np]=len[p]+1;
		for(;p&&!to[p][c];p=fa[p]) to[p][c]=np;
		if(!p) return fa[np]=1,void(); int q=to[p][c];
		if(len[q]==len[p]+1) return fa[np]=q,void();
		int nq=++cnt; fa[nq]=fa[q],fa[q]=fa[np]=nq;
		len[nq]=len[p]+1,memcpy(to[nq],to[q],sizeof to[q]);
		for(;p&&to[p][c]==q;p=fa[p]) to[p][c]=nq;
	}
	inline void calc() {
		fp(i,1,cnt) ++c[len[i]];
		fp(i,1,cnt) c[i]+=c[i-1];
		fp(i,1,cnt) sa[c[len[i]]--]=i;
		memset(mn,0x3f,cnt+3<<2);
	}
	inline void update(int n){
		int p=1,l=0,c;
		fp(i,0,n-1){ c=s[i]-'a';
			for(;p&&!to[p][c];) p=fa[p],l=len[p];
			if(p) ++l,p=to[p][c],cmax(mx[p],l);
			else p=1,l=0;
		}
		fd(i,cnt,1){ int p=sa[i];
			cmax(mx[fa[p]],Min(mx[p],len[fa[p]]));
			cmin(mn[p],mx[p]),mx[p]=0;
		}
	}
}p;
int main(){ scanf("%s",s),n=strlen(s);
	fp(i,0,n-1) p.insert(s[i]-'a'); p.calc();
	while(~scanf("%s",s)) n=strlen(s),p.update(n);
	fp(i,1,p.cnt) cmax(ans,p.mn[i]);
	printf("%d\n",ans); return 0;
}
```






# more

安利多倍经验：

[求两个串的 lcs 的](https://www.luogu.org/problemnew/show/SP1811)

[大概做法类似的](https://www.luogu.org/problemnew/show/P2463)

[改改多组数据就好了](https://www.luogu.org/problemnew/show/SP10570)


---

## 作者：温词 (赞：1)

### 安利一下自己的博客 https://www.cnblogs.com/wenci/p/10433227.html
#### 题意：n个字符串(n<=10)求最长公共子串的长度前置技能点：https://www.cnblogs.com/wenci/p/10432932.html （两个字符串求最长公共子串的长度）既然知道了两个串的最长公共子串怎么求那我们延伸一下，考虑两个变量，maxx表示在当前拿上来匹配得这个串在每个节点为终点时最长匹配的长度minn表示在之前所有串上匹配完，到当前节点最长匹配的长度先解释一下拓扑序的基数排序
```cpp
inline void radix_sort(){
    int i,j,k;
    for(i=1;i<=tot;i++){
        tong[node[i].len]++;
    }//开桶记录长度
    for(i=1;i<=tot;i++){
        tong[i]+=tong[i-1]; 
    }//表示当前长度能排到多少名
    for(i=1;i<=tot;i++){
        id[tong[node[i].len]--]=i;//重新排序后的数值
    } 
}
```
#### 每一个串重新匹配的操作
```cpp
inline bool work(){
    if(scanf("%s",s)==EOF) return false;
    int p=1,len=0;int i,j,k;
    for(i=1;i<=tot;i++){
        node[i].maxx=0;
    }//把当前串的最大匹配清零
    int l1=strlen(s);
    for(i=0;i<l1;i++){
        int now=s[i]-'a'+1; 
        if(node[p].ch[now]){
            p=node[p].ch[now];len++;
        }
        else{
            while(p&&!node[p].ch[now]){
                p=node[p].fa;
            }
            if(!p){
                p=1;len=0;
            }
            else{
                len=node[p].len+1;p=node[p].ch[now];
            }
        }//以上都和两个串匹配操作一样
        node[p].maxx=max(node[p].maxx,len);//这里更新一下当前串的最大匹配
    }
    for(i=tot;i;i--){//按照倒拓扑序，要优先修改儿子节点更新父亲节点
        int t=id[i];//基数排序后的序号
        node[t].minn=min(node[t].minn,node[t].maxx);//更新当前节点的最大匹配
        if(node[t].maxx>=node[t].len&&node[t].fa){//如果当前节点是满匹配的，那么删去结尾最后一个，也是满匹配的
            node[node[t].fa].maxx=node[node[t].fa].len;//把父亲节点的匹配也更新了
        }
    }
    return true;
}
```
#### 最后贴整篇代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
inline int read(){
    int w=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        w=(w<<3)+(w<<1)+ch-48;
        ch=getchar();
    }
    return w*f;
}
int n,m,lst=1,tot=1;
long long size[2000010],sum[2000010];
struct Node{
    int ch[30],len,fa,maxx,minn;
}node[2000010];
bool flag;
inline void extend(int now){
    int p=lst;tot++;lst=tot;int np=tot;
    node[np].len=node[p].len+1;
    while(p&&!node[p].ch[now]){
        node[p].ch[now]=np;
        p=node[p].fa;
    }
    if(!p) node[np].fa = 1;
    else{
        int q = node[p].ch[now];
        if(node[q].len == node[p].len + 1){
            node[np].fa = q;
        }
        else{
            int nq=++tot;node[nq]=node[q];
            node[nq].len=node[p].len+1;
            node[np].fa=node[q].fa=nq;
            while(p&&node[p].ch[now] == q){
                node[p].ch[now]=nq;
                p=node[p].fa;
            }
        }
    }
}
int tong[2000010],id[2000010],ans;
char s[2000010];
inline void radix_sort(){
    int i,j,k;
    for(i=1;i<=tot;i++){
        tong[node[i].len]++;
    }
    for(i=1;i<=tot;i++){
        tong[i]+=tong[i-1]; 
    }
    for(i=1;i<=tot;i++){
        id[tong[node[i].len]--]=i;
    } 
}
inline bool work(){
    if(scanf("%s",s)==EOF) return false;
    int p=1,len=0;int i,j,k;
    for(i=1;i<=tot;i++){
        node[i].maxx=0;
    }
    int l1=strlen(s);
    for(i=0;i<l1;i++){
        int now=s[i]-'a'+1; 
        if(node[p].ch[now]){
            p=node[p].ch[now];len++;
        }
        else{
            while(p&&!node[p].ch[now]){
                p=node[p].fa;
            }
            if(!p){
                p=1;len=0;
            }
            else{
                len=node[p].len+1;p=node[p].ch[now];
            }
        }
        node[p].maxx=max(node[p].maxx,len);
    }
    for(i=tot;i;i--){
        int t=id[i];
        node[t].minn=min(node[t].minn,node[t].maxx);
        if(node[t].maxx>=node[t].len&&node[t].fa){
            node[node[t].fa].maxx=node[node[t].fa].len;
        }
    }
    return true;
}
int main(){
    scanf("%s",s);int i,j,k;
    int l=strlen(s);
    for(i=0;i<=l;i++){
        extend(s[i]-'a'+1);
    }
    radix_sort();
    for(i=1;i<=tot;i++){
        node[i].minn=node[i].len;
    }
    while(work());
    for(i=1;i<=tot;i++){
        ans=max(ans,node[i].minn);
    }
    cout<<ans<<endl;
    return 0;
}
```


---

