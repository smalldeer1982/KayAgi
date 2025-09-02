# Paper task

## 题目描述

Alex was programming while Valentina (his toddler daughter) got there and started asking many questions about the round brackets (or parenthesis) in the code. He explained her a bit and when she got it he gave her a task in order to finish his code on time.

For the purpose of this problem we consider only strings consisting of opening and closing round brackets, that is characters '(' and ')'.

The sequence of brackets is called correct if:

1. it's empty;
2. it's a correct sequence of brackets, enclosed in a pair of opening and closing brackets;
3. it's a concatenation of two correct sequences of brackets.

For example, the sequences "()()" and "((()))(())" are correct, while ")(()", "(((((" and "())" are not.

Alex took a piece of paper, wrote a string $ s $ consisting of brackets and asked Valentina to count the number of distinct non-empty substrings of $ s $ that are correct sequences of brackets. In other words, her task is to count the number of non-empty correct sequences of brackets that occur in a string $ s $ as a substring (don't mix up with subsequences).

When Valentina finished the task, Alex noticed he doesn't know the answer. Help him don't loose face in front of Valentina and solve the problem!

## 说明/提示

In the first sample, there are $ 5 $ distinct substrings we should count: "()", "()()", "()()()", "()()()()" and "()()()()()".

In the second sample, there are $ 3 $ distinct substrings we should count: "()", "(())" and "(())()".

## 样例 #1

### 输入

```
10
()()()()()
```

### 输出

```
5
```

## 样例 #2

### 输入

```
7
)(())()
```

### 输出

```
3
```

# 题解

## 作者：command_block (赞：11)

**题意** ： 本质不同的合法括号子串计数。

$n\leq 5\times10^5$ ,时限$\texttt{3s}$。

------------

- 回忆括号序列合法的充要条件：

  将 $($ 设为 $-1$ ， $)$ 设为 $1$。
  
  括号序列 $A$ 合法，当且仅当 $A$ 的权值和为 $0$ 且后缀和均非负。
  
先建立 $\rm SAM$。

对于每个节点，只需要求出任意一个 $edp$ ，设为 $t$。

那么该节点代表着从 $t$ 结尾的，开头在某区间 $[l,r]$ 区间内的所有串。

我们要计数这些串中有几个是合法的。

首先解决“后缀和均非负”这个约束。由于起始点固定，不难发现起始点越靠前越有可能违反这个约束。

所以，满足约束的起始点是一个区间。怎样求出这个区间呢？

设原串的权值数组为 $A$ ,后缀和为 $S$。

$\sum A[l,r]\geq 0\Longleftrightarrow S[l]\geq S[r+1]$ 。

使用 $ST$ 表维护,二分并查看区间最小值。

还需要满足区间和为 $0$。

$\sum A[l,r]=0\Longleftrightarrow S[r+1]=S[l]$ 。

变成区间数 $c=S[r+1]$ 的个数，使用 `vector` 配合二分即可。

复杂度 $O(n\log n)$。

```cpp
#include<algorithm>
#include<cstdio>
#include<vector>
#define ll long long
#define pb push_back
#define MaxN 500500
using namespace std;
struct Node
{int t[2],f,len,ed;}
a[MaxN<<1];
int tn,las;
void add(int c)
{
  int p=las,np=++tn;las=np;
  a[np].len=a[p].len+1;
  for (;p&&!a[p].t[c];p=a[p].f)a[p].t[c]=np;
  if (!p)a[np].f=1;
  else {
    int v=a[p].t[c];
    if (a[v].len==a[p].len+1)a[np].f=v;
    else {
      int nv=++tn;a[nv]=a[v];
      a[nv].len=a[p].len+1;
      for (;p&&a[p].t[c]==v;p=a[p].f)a[p].t[c]=nv;
      a[np].f=a[v].f=nv;
    }
  }
}
vector<int> p[MaxN<<1],g[MaxN<<1];
int n,t[20][MaxN],lg2[MaxN],s[MaxN];
int qry(int l,int r){
  int k=lg2[r-l+1];
  return min(t[k][l],t[k][r-(1<<k)+1]);
}
ll ans=0;
void dfs(int u)
{
  for (int i=0;i<g[u].size();i++){
    dfs(g[u][i]);
    a[u].ed=a[g[u][i]].ed;
  }
  int ed=a[u].ed,
      l=ed-a[u].len+1,sr=ed-a[a[u].f].len,mid,r=sr+1;
  while(l<r){
    mid=(l+r)>>1;
    if (qry(mid,ed)>=s[ed+1])r=mid;
    else l=mid+1;
  }
  ans+=
    upper_bound(p[n+s[ed+1]].begin(),p[n+s[ed+1]].end(),sr)-
    lower_bound(p[n+s[ed+1]].begin(),p[n+s[ed+1]].end(),r)
  ;
}
char str[MaxN];
int main()
{
  scanf("%d%s",&n,str+1);
  for (int i=n;i;i--)
    t[0][i]=s[i]=s[i+1]+((str[i]=='(' ? -1 : 1));
  for (int i=1;i<=n+1;i++)
    p[n+s[i]].pb(i);
  for (int i=2;i<=n;i++)lg2[i]=lg2[i>>1]+1;
  for (int j=1;(1<<j)<=n;j++)
    for (int i=1;i<=n;i++)
      t[j][i]=min(t[j-1][i],t[j-1][i+(1<<j-1)]);
  las=tn=1;
  for (int i=1;i<=n;i++)add(str[i]-'(');
  for (int i=1,p=1;i<=n;i++)
  	a[p=a[p].t[str[i]-'(']].ed=i;
  for (int i=2;i<=tn;i++)g[a[i].f].pb(i);
  dfs(1);
  printf("%lld\n",ans);
  return 0;
}
```


---

## 作者：juicyyou (赞：8)

# CF653F Paper task

来一发 SA 的题解（（

首先，我们知道实际上此题就是要求本质不同的合法括号子串的数量。

既然如此，不妨先不考虑本质不同这个条件，关注合法括号子串这个问题。

我们令 ```(``` 的权值是 1，```)``` 的权值是 -1。令 $d_j = \sum\limits_{i = 1}^j v_i$，其中 $v_i$ 表示第 $i$ 个字符的权值。

那我们先列出合法括号串的条件：

1. 在串内的任意一个位置，在它前面 ```(``` 的数量大于等于 ```)``` 的数量。
2. 串首的字符是 ```(```。
3. 整个串 ```(``` 的数量等于 ```)``` 的数量。

把这些条件转化可以得到：

1. $\forall i, d_i \ge d_1 - 1$
2. $s_1 = $ ```'('``` 
3. $d_n = d_1 - 1$

于是只需要在 $d$ 上建立 ST表，并对每个位置进行二分就能得到一个 $R_i$ 表示使得子串 $s_{i\cdots r}$ 为合法子串的最远的 $r$。那怎么统计有多少个以 $i$ 为左边界的合法括号子串呢？我们只需要求出 $i \cdots R_i$ 里有多少个 $d_j = d_i - 1$ 的点即可。这个问题可以给每个 $d_i$ 的值开一个存下标的 ```vector``` 进行二分求得。

然后我们要考虑的就是本质不同这个限制，但实际上也很简单。考虑最简单的本质不同子串的做法，求出 ```SA``` 和 ```height``` 两个数组之后求 $sa_i $ 和 $sa_{i - 1}$ 有多少最长公共合法括号前缀即可。这个可以用前面的方法轻松求得。最后用总数减去就行了。

下面是我的 Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 5e5 + 5;
const ll maxv = 5e5;
// again
ll n;
char s[maxn];
ll sa[maxn << 1], rk[maxn << 1], cnt[maxn];
ll tmp[maxn], x[maxn], y[maxn];
void getsa(){
	memset(cnt, 0, sizeof(cnt));
	for(int i = 1;i <= n;i++) rk[i] = s[i], cnt[rk[i]]++;
	for(int i = 1;i <= maxv;i++) cnt[i] += cnt[i - 1];
	for(int i = n;i >= 1;i--) sa[cnt[rk[i]]--] = i;
	for(int w = 1;w <= n;w <<= 1){
		ll p = 0;
		for(int i = n;i >= n - w + 1;i--) tmp[++p] = i;
		for(int i = 1;i <= n;i++){
			if(sa[i] > w) tmp[++p] = sa[i] - w;
			x[i] = rk[i], y[i] = rk[i + w];
		}
		memset(cnt, 0, sizeof(cnt));
		for(int i = 1;i <= n;i++) cnt[rk[tmp[i]]]++;
		for(int i = 1;i <= maxv;i++) cnt[i] += cnt[i - 1];
		for(int i = n;i >= 1;i--) sa[cnt[rk[tmp[i]]]--] = tmp[i];
		ll num = 1; rk[sa[1]] = 1;
		for(int i = 2;i <= n;i++){
			rk[sa[i]] = num;
			if(x[sa[i]] != x[sa[i - 1]] || y[sa[i]] !=
			y[sa[i - 1]]){
				rk[sa[i]] = ++num;
			}
		}
	}
	return ;
}
ll hei[maxn];
void gethei(){
	ll lth = 0;
	for(int i = 1;i <= n;i++){
		if(lth) lth--;
		if(rk[i] > 1){
			while(i + lth <= n && sa[rk[i] - 1] + lth <= n 
			&& s[i + lth] == s[sa[rk[i] - 1] + lth]) lth++;
 		}
 		hei[rk[i]] = lth;
	}
	return ;
}
ll d[maxn];
ll st[maxn][21], lg[maxn];
void getst(){
	for(int i = 1;i <= n;i++) st[i][0] = d[i];
	for(int i = 1;(1 << i) <= n;i++){
		for(int j = 1;j <= n - (1 << i) + 1;j++){
			st[j][i] = min(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
		}
	}
	for(int i = 1;i <= n;i++){
		lg[i] = lg[i - 1] + ((1 << (lg[i - 1] + 1)) == i);
	}
	return ;
}
ll rmq(ll l, ll r){
	ll len = lg[r - l + 1];
	return min(st[l][len], st[r - (1 << len) + 1][len]);
}
vector<ll> v[maxn << 1];
ll que(ll l, ll r, ll val){
	val += maxv;
	ll L = lower_bound(v[val].begin(), v[val].end(), l) - 
	v[val].begin();
	ll R = upper_bound(v[val].begin(), v[val].end(), r) -
	v[val].begin() - 1;
	if(L > R || L == v[val].size()) return 0;
	return R - L + 1;
}
ll sid[maxn];
ll cntans;
int main(){
	scanf("%lld", &n);
	scanf("%s", s + 1);
	getsa(); gethei();
	for(int i = 1;i <= n;i++){
		if(s[i] == '('){
			d[i] = d[i - 1] + 1;
		} else {
			d[i] = d[i - 1] - 1;
			v[d[i] + maxv].push_back(i);
		}
	}
	getst();
	for(int i = 1;i <= n;i++){
		ll l = i, r = n, ans = 0;
		while(l <= r){
			ll mid = (l + r) >> 1;
			if(rmq(i, mid) < d[i] - 1){
				r = mid - 1;
			} else {
				ans = mid;
				l = mid + 1;
			}
		}
		sid[i] = ans;
		if(s[i] == '(') cntans += que(i, sid[i], d[i] -  1);
	}
	for(int i = 2;i <= n;i++){
		if(s[sa[i]] == ')') break;
		ll R = min(sa[i] + hei[i] - 1, sid[sa[i]]);
		cntans -= que(sa[i], R, d[sa[i]] - 1);
	}
	cout << cntans << endl;
	return 0;
}
```

上述算法的复杂度为 $\mathcal O(n \log n)$，可以通过此题。

---

## 作者：Hoks (赞：2)

## 前言
比较有意思/思维提升的 SA 题。

可惜我卡在第一步卡死了，做完了回来看还是很好玩的。

广告：[『从入门到入土』串串学习笔记](https://www.luogu.com.cn/article/dv6dig1o)。
## 思路分析
首先发现这个串串题很独特的地方就在于它的字符串为括号匹配。

这个限制条件就导致很不好做，所以首先考虑把这个条件转化掉。

考虑令 `(` 权值为 $1$，`)` 权值为 $-1$，处理出原串的前缀和 $a$ 数组。

那么一段括号序列 $l,r$ 是合法括号序列的充要条件即为：

- $s_l=$`(`

- $\forall i\in[l,r],a_i\ge a_l-1$

- $a_r=a_l-1$

原因就是将合法括号序列的特性：以左括号开头，左右括号数相等，任意时刻左括号数量都不小于右括号数量用式子表示了出来。

接着考虑怎么快速求出所有符合条件的括号序列。

不难发现前两个条件比较容易符合，先固定住左端点 $l$。

接着考虑能取到的最右端点 $R$ 具有单调性，考虑二分。

对于快速查询一段区间的最小值，考虑使用 ST 表。

这样就可以求出每个左端点 $l$ 对应的最右端点 $R$。

接着考虑满足第 $3$ 个条件：

考虑开 $n$ 个 `vector` 存下每种值的出现位置，查询时到对应的 `vector` 中查询即可。

接着考虑怎么处理题目中本质不同这个问题。

考虑使用 SA，把 LCP 部分的答案去掉即可。

具体实现时注意 $a_i$ 可能为负数，要整体加上偏移量扔 `vector` 里。

以及当心查询时存在合法括号序列数为 $0$ 的情况。
## 代码
```cpp
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=5e5+10,mod=1e9+7,INF=0x3f3f3f3f3f3f3f3f;
int n,m,ans,a[N],id[N];char s[N];vector<int>e[N<<1];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c=='('||c==')'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
namespace SA
{
    const int ST=127;
    int sa[N],rk[N],old[N],c[N],h[N];
    inline void get_SA()
    {
        m=ST;
        for(int i=1;i<=n;i++) ++c[rk[i]=s[i]];
        for(int i=2;i<=m;i++) c[i]+=c[i-1];
        for(int i=n;i>=1;i--) sa[c[rk[i]]--]=i;
        for(int k=1;k<=n;k<<=1)
        {
            int tot=0;
            for(int i=n-k+1;i<=n;i++) old[++tot]=i;
            for(int i=1;i<=n;i++) if (sa[i]>k) old[++tot]=sa[i]-k;
            for(int i=1;i<=m;i++) c[i]=0;
            for(int i=1;i<=n;i++) c[rk[i]]++;
            for(int i=2;i<=m;i++) c[i]+=c[i-1];
            for(int i=n;i>=1;--i) sa[c[rk[old[i]]]--]=old[i],old[i]=0;
            swap(rk,old);rk[sa[1]]=1;tot=1;
            for(int i=2;i<=n;i++) rk[sa[i]]=(old[sa[i]]==old[sa[i-1]]&&old[sa[i]+k]==old[sa[i-1]+k])?tot:++tot;
            if(tot==n) break;m=tot;
        }
        for(int i=1,k=0,j;i<=n;i++)
        {
            if(k) --k;j=sa[rk[i]-1];
            while(s[i+k]==s[j+k]) k++;
            h[rk[i]]=k;
        }
    }
}
using namespace SA;
struct ST
{
    int st[20][N];
    inline void get_ST(int a[])
    {
        for(int i=1;i<=n;i++) st[0][i]=a[i];
        for(int j=1;j<=19;j++)
            for(int i=1;i+(1<<j)-1<=n;i++)
                st[j][i]=min(st[j-1][i],st[j-1][i+(1<<j-1)]);
    }
    inline int get(int l,int r){int k=log2(r-l);l++;return min(st[k][l],st[k][r-(1<<k)+1]);}
}st;
inline int solve(int l,int r,int x)
{
    int L=lower_bound(e[x].begin(),e[x].end(),l)-e[x].begin();
    int R=upper_bound(e[x].begin(),e[x].end(),r)-e[x].begin()-1;
    return (L>R||L==e[x].size())?0:R-L+1;
}
signed main()
{
    read();rd(s,n);get_SA();
    for(int i=1;i<=n;i++)
        if(s[i]=='(') a[i]=a[i-1]+1;
        else a[i]=a[i-1]-1,e[a[i]+N].emplace_back(i);
    st.get_ST(a);
    for(int i=1;i<=n;i++)
    {
        int l=i,r=n;
        while(l<=r)
            if(st.get(i,mid)<a[i]-1) r=mid-1;
            else id[i]=mid,l=mid+1;
        if(s[i]=='(') ans+=solve(i,id[i],a[i]-1+N);
    }
    for(int i=2;i<=n;i++)
    {
        if(s[sa[i]]==')') break;
        ans-=solve(sa[i],min(sa[i]+h[i]-1,id[sa[i]]),a[sa[i]]-1+N);
    }print(ans);
    genshin:;flush();return 0;
}
```

---

## 作者：zzxLLL (赞：2)

题意：给定一个仅包含左右括号的字符串，求其中合法的括号子串**种数**。

一眼看上去没思路，先从简单的问题看起。

---

如何判断一个[括号序列](https://oi-wiki.org/topic/bracket/)是合法的？

将左括号变成 $1$，右括号变成 $-1$，然后得到前缀和数组 $pre$。如果 $pre$ 中没有负数说明括号序列合法。

---

怎么求合法的括号子串**个数**？

考虑枚举左端点 $L$，然后找其最远**可能**对应的右端点 $R$，即不出现右括号个数大于左括号个数的情况。

怎么找？上面的结论可以转化一下：对于合法括号子串 $S[l \cdots r]$ 

1.$S_l$ 为 ``(``

2.$\forall i \in [l , r] , pre_i - pre_l \ge -1$，即 $\min\limits_{i \in [l , r]}{pre_i} - pre_l \ge -1$

3.$pre_r - pre_l = -1$

可以对 $pre$ 数组维护一个 ST 表，通过第二条性质二分查询其右端点，再在左右端点之间寻找 $pre_x = pre_l - 1$ 的 $x$ 的个数即可。

于是问题转化为给定区间内有多少个数等于某给定值。于是你想到了[这题](https://www.luogu.com.cn/problem/P5048)，并想到可以对于每一个值开一个vector。

```cpp
vector<int>v[M<<1];
#define lwb(t,x) lower_bound(v[t].begin(),v[t].end(),x)
#define upb(t,x) upper_bound(v[t].begin(),v[t].end(),x)
int query(int l,int r,int val){ // [l,r] 中 val 的出现次数 
	return upb(val+M,r)-lwb(val+M,l);
}
```

$v_t$ 存储的是所有等于 $t$ 的数的下标，单调递增。$t$ 可能为负怎么办？查询时给每个 $t$ 加上 $5 \times 10^5$ 即可。

---

然而题目要求的是**种数**，怎么办？

上面会得出来很多相同的字符串，我们现在要做的是**去重**。

如何去重？全部算完再一个个去重太麻烦，考虑在计算时就不算重复的情况。这个时候你想到了[字符串去重的板子](https://www.luogu.com.cn/problem/P2408)，于是使用[后缀数组](https://oi-wiki.org/string/sa/)。

考虑每个后缀对答案的贡献。对于排名为 $i$ 的后缀，它的前 $height_i$ 个字符已经被前 $i-1$ 个后缀计算过了，所以真正新增的字符串的**右端点**在 $[sa_i + height_i , n]$ 中。

要求新增的字符串对答案的贡献。结合上面枚举左端点 $L$ 找右端点 $R$ 的做法可知：令 $r_i$ 为 $sa_i$ 作为左端点时找到的最远右端点，那么排名为 $i$ 的后缀的贡献为 $[sa_i + height_i , r_i]$ 中值为 $pre_{sa_i} - 1$ 的数的个数。将贡献累加即可。

---

时间复杂度 $O(n \log{n})$，这题也没什么细节，十分好写。

```cpp
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int M=5e5+10;

int len,pre[M],st[M][21];
char str[M];
int query(int l,int r){
	int k=log2(r-l+1);
	return min(st[l][k],st[r-(1<<k)+1][k]);
}

int x[M],y[M],sa[M],buc[M],ht[M];
void SA(){
	int tot=127;
	for(int i=1;i<=len;i++) buc[x[i]=str[i]]++;
	for(int i=2;i<=tot;i++) buc[i]+=buc[i-1];
	for(int i=len;i>=1;i--) sa[buc[x[i]]--]=i;
	
	for(int k=1;k<=len;k<<=1){
		int cur=0;
		for(int i=len-k+1;i<=len;i++) y[++cur]=i;
		for(int i=1;i<=len;i++)
			if(sa[i]>k) y[++cur]=sa[i]-k;
		
		for(int i=1;i<=tot;i++) buc[i]=0;
		for(int i=1;i<=len;i++) buc[x[i]]++;
		for(int i=2;i<=tot;i++) buc[i]+=buc[i-1];
		for(int i=len;i>=1;i--) sa[buc[x[y[i]]]--]=y[i];
		
		swap(x,y),x[sa[1]]=cur=1;
		for(int i=2;i<=len;i++)
			if(y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]) x[sa[i]]=cur;
			else x[sa[i]]=++cur;
		if(cur==len) break;
		tot=cur;
	}
}
void getheight(){
	for(int i=1,cur=0;i<=len;i++){
		if(x[i]==0) continue;
		if(cur) cur--;
		while(str[i+cur]==str[sa[x[i]-1]+cur]) cur++;
		ht[x[i]]=cur;
	}
}

vector<int>v[M<<1];
#define lwb(t,x) lower_bound(v[t].begin(),v[t].end(),x)
#define upb(t,x) upper_bound(v[t].begin(),v[t].end(),x)
int query(int l,int r,int val){ // [l,r] 中 val 的出现次数 
	return upb(val+M,r)-lwb(val+M,l);
}

int find_r(int p){
	int lb=p,rb=len,ans=p;
	while(lb<=rb){
		int mid=(lb+rb)>>1;
		if(query(p,mid)-pre[p]>=-1) ans=mid,lb=mid+1;
		else rb=mid-1;
	}
	return ans;
}

int main(){
	scanf("%d",&len);
	scanf(" %s",str+1);
	
	for(int i=1;i<=len;i++)
		st[i][0]=pre[i]=pre[i-1]+(str[i]=='('?1:-1);
	for(int j=1;j<21;j++)
		for(int i=1;i+(1<<j)-1<=len;i++)
			st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	
	SA(),getheight();
	for(int i=1;i<=len;i++) v[pre[i]+M].push_back(i);
	
	long long ans=0;
	for(int i=1,L,R;i<=len;i++){
		if(str[sa[i]]==')') break;
		L=sa[i]+ht[i],R=find_r(sa[i]);
		if(L<=R) ans+=query(L,R,pre[sa[i]]-1);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：lzqy_ (赞：2)

线性做法，但因为哈希大常数所以并没有最优解rk1（

~~题解里好像还没有线性的做法欸，好！~~
 
先建括号树，大致建立方法如下：

- 找到极大的形如 `(S)` 的合法括号序列，将外层的 `()` 提出来作为父节点 $x$。此时序列被拆分成若干个状态仍然是 `(S)` 的子问题，这些子问题就是子节点，继续向下递归。

- 相当于一个节点支配一个形如 `(S)` 的区间 $[l,r]$，子节点是对于 $[l+1,r-1]$ 的子问题拆分。

建了括号树的好处是，能拼接在一起形成新括号序列的节点，父节点一定相同。

所以我们求出每一个节点哈希值，然后将每个节点的子节点哈希值顺次相连，这样我们对于每一个节点都得到了一个以哈希值作为字符集的字符串。

那么问题就变成给出 $k$ 个字符串，求不同子串个数。

广义 SAM 板子。但直接用特殊字符隔开后在普通 SAM 的 DAG 上 dp 即可。

难写的地方在于 SAM 的字符集范围很大。

（当然也可以牺牲一只 $\log$ 用 map 写，这样就简单很多）

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
#define mp make_pair
#define il inline
using namespace std;
const int mod=1e7+7;
const int maxn=1000010;
const int NN=maxn<<2;
struct Node{
	int len,fa;
}a[NN];
struct EEdge{
	pair<ull,int>v;
	int w,to;
}ee[NN<<1];
int ru[NN],n,N; 
int hhead[mod],eecnt;
int F(pair<ull,int>x){
//	printf("F : %d %lld : ",x.second,x.first);
	int val=((x.first%mod)*n+x.second)%mod;
//	printf("%d\n",val);
	for(int i=hhead[val];i;i=ee[i].to)
		if(ee[i].v==x) return ee[i].w;
	return 0; 
}
void I(pair<ull,int>x,int w){
//	printf("I : %d %lld : ",x.second,x.first);
	int val=((x.first%mod)*n+x.second)%mod;
//	printf("%d\n",val); 
	ee[++eecnt].v=x,ee[eecnt].w=w,ee[eecnt].to=hhead[val],hhead[val]=eecnt;
}
struct Edge{
	ull w;
	int v,to;
}e[NN<<1];
int head[NN],ecnt;
void add(int u,int v,ull w){
//	printf("[[[[[[[[[[]]]]]]]%d->%d %lld\n",u,v,w);
	e[++ecnt].v=v,e[ecnt].w=w;
	e[ecnt].to=head[u],head[u]=ecnt;
	I(mp(w,u),ecnt);
}
int cnt=1,Ed=1;
void Insert(ull c){
//	printf("!!!!!%lld\n",c);
	int t=Ed,x=Ed=++cnt,nt=0;a[x].len=a[t].len+1;
	for(;t&&!nt;t=a[t].fa,nt=e[F(mp(c,t))].v) add(t,x,c);
	if(!t){a[x].fa=1;return ;}
	if(a[t].len+1==a[nt].len){a[x].fa=nt;return ;}
	int nx=++cnt;a[nx].len=a[t].len+1;
	a[nx].fa=a[nt].fa,a[nt].fa=a[x].fa=nx;
//	a[nx].ch=a[nt].ch;
	for(int i=head[nt];i;i=e[i].to)
		add(nx,e[i].v,e[i].w);
	for(;e[F(mp(c,t))].v==nt;t=a[t].fa) e[F(mp(c,t))].v=nx; 
}
int els[maxn],st[maxn],top;
ull Ha[maxn],Pa[maxn];
ull f[NN],ans;
char c[maxn];
vector<ull>v[maxn];
ull H(int l,int r){return Ha[r]-Ha[l-1]*Pa[r-l+1];}
void Solve(int l,int r){
	int id=++N;
	for(int i=l+1;i<r;i++)
		if(els[i]){
			Solve(i,els[i]),v[id].push_back(H(i,els[i]));
			i=els[i];	
		}
}
queue<int>q;
void topo_sort(){
	q.push(1),f[1]=1;
	int t;
	while(!q.empty()){
		t=q.front(),q.pop();
		for(int i=head[t];i;i=e[i].to){
			ru[e[i].v]--;
			if(e[i].w) f[e[i].v]+=f[t];
			if(!ru[e[i].v]) q.push(e[i].v);
		}
	}
	for(int i=2;i<=cnt;i++) ans+=f[i];
}
int main(){
	scanf("%d%s",&n,c+1),Pa[0]=1;
	for(int i=1;i<=n;i++)
		Ha[i]=Ha[i-1]*3+(c[i]=='(')+1,Pa[i]=Pa[i-1]*3llu;
	for(int i=1;i<=n;i++)
		if(c[i]=='(') st[++top]=i;
		else if(top) els[st[top]]=i,els[i]=st[top],top--;
	for(int i=1,id=++N;i<=n;i++)
		if(els[i]) v[id].push_back(H(i,els[i])),Solve(i,els[i]),i=els[i];
		else id=++N;
	for(int i=1;i<=N;i++){
		if(v[i].empty()) continue; 
		for(int j=0;j<v[i].size();j++)
			Insert(v[i][j]);
		Insert(0);
	}
	for(int i=1;i<=cnt;i++)
		for(int j=head[i];j;j=e[j].to) 
			ru[e[j].v]++;
	topo_sort(),printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Durant_Lee (赞：2)

[欢迎来我的blog逛逛~](https://blog.csdn.net/Dream_Lolita/article/details/88010611)

【题目】

给定一个括号串，问有多少种不同的合法括号子串。$n\leq 5\times 10^5$

【解题思路】

首先我们将左括号看作$1$，右括号看作$-1$，肯定要处理出一个前缀和数组。
如果不考虑重复，那么我们不妨考虑求以每个位置开头的合法子串个数，即对于每个位置$i$，我们需要求有多少个
$$i<j\leq n,\text{s.t.} s_j=s_{i-1},\forall i\leq k \leq j ,s_k\geq s_{i-1}$$

这个问题我们可以先处理出每种前缀和的所有位置，并通过$\text{RMQ}$维护区间最小值，然后在之前处理出的位置数组中二分判断最大可选的$j$在哪个位置即可。

现在要求去重，我们可以求出$height$数组，然后$j$的可选范围就是
$$sa_i+height_i+1\leq j\leq n$$

除此之外的做法都是一样的。

复杂度$O(n\log n)$

【参考代码】
```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;

typedef long long ll;
const int N=1e6+10,M=500001;

namespace SA
{
	int sa[N],rk[N],hi[N];
	int wa[N],wb[N],wx[N],wy[N];
	bool cmp(int *r,int a,int b,int l){return r[a]==r[b] && r[a+l]==r[b+l];}
	void getsa(int *r,int n,int m)
	{
		int *x=wa,*y=wb,*t,i,j,p;
		for(i=0;i<m;++i) wx[i]=0;
		for(i=0;i<n;++i) wx[x[i]=r[i]]++;
		for(i=1;i<m;++i) wx[i]+=wx[i-1];
		for(i=n-1;~i;--i) sa[--wx[x[i]]]=i;
		for(j=1,p=0;p<n;j<<=1,m=p)
		{
			for(p=0,i=n-j;i<n;++i) y[p++]=i;
			for(i=0;i<n;++i) if(sa[i]>=j) y[p++]=sa[i]-j; 
			for(i=0;i<m;++i) wx[i]=0;
			for(i=0;i<n;++i) wx[wy[i]=x[y[i]]]++;
			for(i=1;i<m;++i) wx[i]+=wx[i-1];
			for(i=n-1;~i;--i) sa[--wx[wy[i]]]=y[i];
			for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;++i)
				x[sa[i]]=cmp(y,sa[i],sa[i-1],j)?p-1:p++;
		} 
	}
	void getheight(int *r,int n)
	{
		int i,j,k=0;
		for(i=1;i<=n;++i) rk[sa[i]]=i;
		for(i=0;i<n;hi[rk[i++]]=k)
			for(k?--k:0,j=sa[rk[i]-1];r[i+k]==r[j+k];++k);
	}
	void adjust(int n)
	{
		for(int i=n;i;--i) ++sa[i],rk[i]=rk[i-1];
		sa[0]=rk[0]=0;
	}
	void output(int n)
	{
		for(int i=0;i<=n;++i) printf("%d ",sa[i]); puts("");
		for(int i=0;i<=n;++i) printf("%d ",rk[i]); puts("");
		for(int i=0;i<=n;++i) printf("%d ",hi[i]); puts("");
	}
	void buildsa(int *r,int n,int m)
	{
		getsa(r,n+1,m);getheight(r,n);adjust(n);
	}
}
using namespace SA;

namespace DreamLolita
{
	ll ans;
	int n,s[N],Log[N],fc[25],h[20][N],sum[N];
	char ch[N];
	vector<int>vec[N];
	void initrmq(int n)
	{
		for(int i=n;i;--i) s[i]=s[i-1],sum[i]=sum[i-1]; s[0]=0;sum[0]=M;
		for(int i=1;i<=n;++i) vec[sum[i]].pb(i);

		fc[0]=1;for(int i=1;i<22;++i)fc[i]=fc[i-1]<<1;
		for(int i=2;i<=n;++i) Log[i]=Log[i>>1]+1;
		for(int i=1;i<=n;++i) h[0][i]=sum[i];
		for(int j=1;j<20;++j) for(int i=1;i+fc[j]-1<=n;++i)
			h[j][i]=min(h[j-1][i],h[j-1][i+fc[j-1]]); 
	}
	int query(int l,int r)
	{
		if(l>r) swap(l,r);
		int t=Log[r-l+1];
		return min(h[t][l],h[t][r-fc[t]+1]);
	}
	void solution()
	{
		scanf("%d%s",&n,ch);
		for(int i=0;i<n;++i) ch[i]=='('?(s[i]=sum[i]=1):(s[i]=2,sum[i]=-1);
		for(int i=1;i<n;++i) sum[i]+=sum[i-1];
		for(int i=0;i<n;++i) sum[i]+=M;
		buildsa(s,n,N);initrmq(n);

		for(int i=1;i<=n;++i)
		{
			int x=sa[i];
			if(s[x]==2) continue;
			int l=x+hi[i],r=n,res=l-1;
			while(l<=r)
			{
				int mid=(l+r)>>1;
				if(query(x,mid)>=sum[x-1]) l=mid+1,res=mid;
				else r=mid-1;
			}

			int t=sum[x-1];
			ans+=upper_bound(vec[t].begin(),vec[t].end(),res)-lower_bound(vec[t].begin(),vec[t].end(),x+hi[i]);
		}//wrong because x+hi[i]->res
		printf("%lld\n",ans);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("CF653F.in","r",stdin);
	freopen("CF653F.out","w",stdout);
#endif
	DreamLolita::solution();
	return 0;
}
```



---

## 作者：yyyyxh (赞：1)

似乎还没有 SAM + 线段树的做法呢。

这里如果不要求子串本质不同，那么就是一个简单的计数。一个结论：如果考虑每一次在当前的字符串后面不断地加字符，那么从未出现过的串的右端点是当前的 $n$ ，左端点一定是一个前缀。我们可以利用 SAM 的在线性求出这一个前缀的右端点，即当前的 $n-len[link[last]]$ （就是 [生成魔咒](https://www.luogu.com.cn/problem/P4070) 这道题的做法）。

求出这一个前缀之后，我们还需要考虑以当前的右端点往左扩展的合法括号串数，把 `(` 看成 -1 ，`)` 看成 1 ，那么这要求后缀和数组的一个后缀全部非负，且当前后缀和是 0 。

我们用线段树维护后缀和数组，每一次线段树上二分出最靠右的后缀和为负的位置，合法的左端点一定在这个点右边。现在合法的左端点是一个区间，只需要数出这个区间里有多少个 0 就是答案了。

区间数数难有单 $\log$ 做法，考虑一个前刚不久在模拟考时遇到的 trick ，由于当前合法左端点区间的最小值非负，维护最小值与最小值个数，就可以数出 0 的个数了。

## Code
```cpp
#include <cstdio>
using namespace std;
const int N=1000003;
int n,cnt,last;
char s[N];
struct sta{
	int mn,cnt;
	sta(int M=0,int C=0):mn(M),cnt(C){}
	friend sta operator+(const sta x,const sta y){
		if(x.mn<y.mn) return x;
		if(x.mn>y.mn) return y;
		return sta(x.mn,x.cnt+y.cnt);
	}
};
int tr[N][2],len[N],link[N];
void extend(int c){
	int cur=++cnt,p=last;
	len[cur]=len[last]+1;last=cur;
	while(p&&!tr[p][c]) tr[p][c]=cur,p=link[p];
	if(!p) {link[cur]=1;return;}
	int q=tr[p][c];
	if(len[q]==len[p]+1) {link[cur]=q;return;}
	int clone=++cnt;
	link[clone]=link[q];len[clone]=len[p]+1;
	tr[clone][0]=tr[q][0];tr[clone][1]=tr[q][1];
	link[cur]=link[q]=clone;
	while(p&&tr[p][c]==q) tr[p][c]=clone,p=link[p];
}
sta sg[N<<2];
int tg[N<<2];
void build(int p,int l,int r){
	if(l==r) {sg[p]=sta(0,1);return;}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	sg[p]=sg[p<<1]+sg[p<<1|1];
}
void pushdown(int p){
	if(tg[p]){
		sg[p<<1].mn+=tg[p];
		sg[p<<1|1].mn+=tg[p];
		tg[p<<1]+=tg[p];
		tg[p<<1|1]+=tg[p];
		tg[p]=0;
	}
}
sta query(int L,int R,int p,int l,int r){
	if(L>R) return sta();
	if(L<=l&&r<=R) return sg[p];
	int mid=(l+r)>>1;
	pushdown(p);
	if(R<=mid) return query(L,R,p<<1,l,mid);
	if(L>mid) return query(L,R,p<<1|1,mid+1,r);
	return query(L,R,p<<1,l,mid)+query(L,R,p<<1|1,mid+1,r);
}
void modify(int R,int v,int p,int l,int r){
	if(r<=R) {sg[p].mn+=v;tg[p]+=v;return;}
	int mid=(l+r)>>1;
	pushdown(p);
	modify(R,v,p<<1,l,mid);
	if(R>mid) modify(R,v,p<<1|1,mid+1,r);
	sg[p]=sg[p<<1]+sg[p<<1|1];
}
int locate(int p,int l,int r){
	if(sg[p].mn>=0) return 0;
	if(l==r) return l;
	pushdown(p);
	int mid=(l+r)>>1;
   	if(sg[p<<1|1].mn<0) return locate(p<<1|1,mid+1,r);
   	return locate(p<<1,l,mid);
}
int main(){
	scanf("%d",&n);
	scanf("%s",s+1);
	cnt=last=1;build(1,1,n);
	long long res=0;
	for(int i=1;i<=n;++i){
		if(s[i]=='(') extend(0),modify(i,-1,1,1,n);
		else extend(1),modify(i,1,1,1,n);
		sta tmp=query(locate(1,1,n)+1,i-len[link[last]],1,1,n);
		if(!tmp.mn) res+=tmp.cnt;
	}
	printf("%lld\n",res);
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

考虑问题只是在“请求出有多少种不同的子串”问题上套了个合法括号串，不妨还是从 SA 的角度思考问题。                

不难发现，我们只要算出所有的合法括号串后减去重复的括号串就是答案。

继续套路。用后缀排序获得 $height$ 数组，尝试减去排序后相邻的后缀相同的前缀内算重的括号串，问题转化成了快速计算固定一个左端点 $l$，右端点范围在 $[l,r]$ 之内的合法括号串数量。              

考虑 $O(n)$ 判断一个字符串是否是合法括号串时，我们只需要维护每个位置的右括号数量是否严格大于等于左括号数量以及首位置是否是左括号，总的左右括号数量是否相等即可。               

对 ```(``` 赋值为 $1$，对 ```)``` 赋值为 $-1$，令每个位置的权值为 $v_i$，$sum_i = \sum_{j = 1} ^ i v_j$，假设计算区间 $[l,r]$ 的字符串则上述条件可以表示为：

- $j \in [l,r],sum_j - sum_l \geq -1$

- $s_l = '('$

- $sum_r = sum_l - 1$

对于第二个条件可以在 $l$ 被确定下来时解决，比较简单。

对于第一个条件，不难发现当 $r$ 在向右扩展时存在一个满足条件的临界位置，二分出来即可。

对于第三个条件，可以转化为求一个区间内为一个值的个数，在离线后可以用 vector 上二分维护。

至此做到了时间复杂度 $O(n \log n)$。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e6 + 5 , Inf = 1e9;
int Minn = Inf,n,m,d[Len],cnt[Len],rk[Len],sa[Len],odrk[Len],gx[Len],id[Len],p,ht[Len];
int RR[Len];
bool cmp(int x,int y,int w){return odrk[x] == odrk[y] && odrk[x + w] == odrk[y + w];}
char s[Len];
int st[21][Len],lg[Len];
void init()
{
	for(int i = 2 ; i <= n ; i ++) lg[i] = lg[i >> 1] + 1;
	for(int i = 1 ; i <= n ; i ++) st[0][i] = d[i];
	for(int i = 1 ; (1 << i) <= n ; i ++) for(int j = 1 ; j + (1 << i) - 1 <= n ; j ++) st[i][j] = min(st[i - 1][j] , st[i - 1][j + (1 << (i - 1))]);
}
inline int Min(int l,int r)
{
	int k = lg[r - l + 1];
	return min(st[k][l] , st[k][r - (1 << k) + 1]);
}
vector<int> v[Len];
inline int Get(int l,int r,int W)
{
	int L = lower_bound(v[W].begin(), v[W].end() , l) - v[W].begin();
	int R = upper_bound(v[W].begin(), v[W].end() , r) - v[W].begin() - 1;
	//printf("%d %d %d %d %d\n",l,r,L,R,W);
	if(L > R || L == v[W].size()) return 0;
	return R - L + 1;
}
int main()
{
	scanf("%d",&n);
	scanf("%s",s + 1);
	for(int i = 1 ; i <= n ; i ++) 
	{
		d[i] = d[i - 1] + (s[i] == '(' ? 1 : -1);
		Minn = min(Minn , d[i]);
		//printf("%d %d\n",i,d[i]);	
	}
	Minn --;
	for(int i = 1 ; i <= n ; i ++) v[d[i] - Minn].push_back(i);
	for(int i = 1 ; i <= n ; i ++) v[d[i] - Minn].push_back(Inf); 
	init();
	long long ans = 0;
	for(int i = 1 ; i <= n ; i ++) 
	{
		if(s[i] == ')') RR[i] = 0;
		else
		{
			int l = i + 1 , r = n , anss = 0;
			while(l <= r)
			{
				int mid = (l + r) >> 1;
				if(Min(l , mid) >= d[i] - 1) anss = mid , l = mid + 1;
				else r = mid - 1;
			}
			RR[i] = anss;
			//printf("%d %d\n",i,RR[i]);
			ans += Get(i , anss , d[i] - 1 - Minn);
		} 
	}
	m = max(n , 300);
	for(int i = 1 ; i <= n ; i ++) ++ cnt[rk[i] = s[i]];
	for(int i = 1 ; i <= m ; i ++) cnt[i] += cnt[i - 1];
	for(int i = n ; i >= 1 ; i --) sa[cnt[rk[i]] --] = i;
	for(int w = 1 ; ; w <<= 1 , m = p)
	{
		p = 0;
		for(int i = n ; i > n - w ; i --) id[++ p] = i;
		for(int i = 1 ; i <= n ; i ++) if(sa[i] > w) id[++ p] = sa[i] - w;
		memset(cnt , 0 , sizeof cnt);
		for(int i = 1 ; i <= n ; i ++) ++ cnt[gx[i] = rk[id[i]]];
		for(int i = 1 ; i <= m ; i ++) cnt[i] += cnt[i - 1];
		for(int i = n ; i >= 1 ; i --) sa[cnt[gx[i]] --] = id[i];
		memcpy(odrk , rk , sizeof (rk));
		p = 0;
		for(int i = 1 ; i <= n ; i ++) rk[sa[i]] = cmp(sa[i - 1] , sa[i] , w) ? p : ++ p;
		if(p == n)
		{
			for(int i = 1 ; i <= n ; i ++) rk[sa[i]] = i;
			break; 
		}
	}
	for(int i = 1 , len = 0 ; i <= n ; i ++) 
	{
		if(rk[i] == 1) continue;
		if(len) len --;
		while(s[i + len] == s[sa[rk[i] - 1] + len]) len ++;
		ht[rk[i]] = len;
	}
	for(int i = 2 ; i <= n ; i ++)
	{
		if(s[sa[i]] == ')') continue;
		int GetR = min(RR[sa[i]] , sa[i] + ht[i] - 1);
		ans -= Get(sa[i] , GetR , d[sa[i]] - 1 - Minn);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：qiyue7 (赞：1)

给一个SAM做法 

不需要去考虑什么乱七八糟的东西，直接从括号序列的定义开始做起，考虑在线添加每一个括号时新增加的本质不同的子串数对总答案的贡献，画个图分类讨论一下就可以知道产生新贡献的位点需要满足什么条件

这里map记录的是最早左括号的起始位点 ， 需要注意的是这里每一个左位点都相当于单独分开一层进行计数，所以开了50w个map计数。

具体分类讨论看核心代码 

代码现在洛谷rk1（感觉上个手写栈什么的应该cf rk前3问题不大。。。1A就懒得卡常随便写了。。。 

主要代码：

```cpp
map<int, int> pre[N]; 
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m, u,v;
    cin >> n ;
    string s;
    cin >> s;
    stack<int> st;
    EXSAM part;
    part.init();
    int S = s.size();
    long long ans=0;
    int sum  = 0;
    for (int i = 0; i < s.size()+10; ++i)
        pre[i][0] = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] == '(')
        {
            part.Insert(0);
            st.push(i+1);
        }
        else
        {
            part.Insert(1);
            if (!st.empty())
            {
                int k = st.top(),cur;
                st.pop();
                if (st.empty())
                    cur = 0;
                else
                    cur = st.top();
                auto p = pre[cur].end();
                p--;
                pre[cur][k] = p->second + 1;
                int kk = part.last->pre->step;
                auto it = pre[cur].lower_bound(i + 2 - kk);
                it--;
                ans += it->second;
            }
            else
                pre[0].clear(),pre[0][0]=0;
        }
    }
    cout << ans << '\n';
    return 0;
}
```


---

## 作者：Gmt丶FFF (赞：0)

无脑子 SAM 做法。

我们在从左往右依次把每个字符串插入 SAM，每一次我们得到本质不同的后缀即为 $len_i-len_{fa_i}$ 个，而且这些本质不同的字符串长度即在 $len_i$ 与 $len_{fa_i}+1$ 之间，因为右端点相同且长度连续，所以代表了左端点属于一段区间 $[l,r]$。

那么我们在这一段区间找到合法的左端点使得子串合法，若设 $($ 为 $-1$，$)$ 为 $1$，那么我们要保证区间的所有后缀非负，若设 $pre_i$ 为 $i$ 的前缀和，那么我们相当于要求对于一个子串 $[x,y]$ 保证 $pre_y-\max(pre_i)\ge 0(i\in[x,y])$。

由于 $pre_y$ 固定，那么相当于求最小的 $i\in[l,r]$ 使得后缀最大值小于等于一个定值，这个做法很多，在线可以用线段树上二分，二分加上一个数据结构，或是离线下来 st 表加二分等，这里选择一个好写的二分加树状数组。

那么我们找到了合法的 $i$ 以后，所有在 $[i,y]$ 中的后缀子串一定都满足了上述条件，所以我们只需要判断左括号与右括号是否相等即可，若将每个点赋值为其前缀值，那么我们相当于求满足 $pre_j=pre_y(j\in[i,y])$ 条件下 $j$ 的个数，那么相当于求区间等于一个数的个数。

这个方法仍然很多，因为可以离线的情况下，我们选择离线下来，并将每个询问进行差分，然后统计一个数的个数直接用桶，最后扫描线扫一次即可，复杂度线性且代码短。

但由于之前第一个判断复杂度过高，为 $O(n\log^2_2 n)$，所以总复杂度也为 $O(n\log_2^2 n)$。

但实际上，这个跑的比大部分 $O(n\log n)$ 都快，甚至冲上了最优解榜二，可见树状数组是有多优秀。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#define ll long long
using namespace std;
const int N=1e6+5;
char s[N];
int n,cnt,f[N],h[N];
int vis[N];
struct node
{
	int link,len,son[2],num;
}a[N];
struct node2
{
	int x,k;
};
vector<node2>g[N];
inline int calc(char ch)
{
	if(ch=='(')return 0;
	return 1;
}
inline int lowbit(int x)
{
	return x&(-x);
}
void update(int x,int k)
{
	while(x)
	{
		f[x]=max(f[x],k);
		x-=lowbit(x);
	}
}
int query(int x)
{
	int sum=-2e9;
	while(x<=n)
	{
		sum=max(sum,f[x]);
		x+=lowbit(x);
	}
	return sum;
}
signed main()
{
	scanf("%d",&n);
	scanf("%s",s+1);
	int last=0,sum=0;
	ll res=0;
	a[0].link=-1;
	memset(f,-0x3f,sizeof(f));
	for(int i=1;i<=n;i++)
	{
		int p=last,x=++cnt;
		a[x].len=i;
		a[x].num=1;
		while(p!=-1&&!a[p].son[calc(s[i])])a[p].son[calc(s[i])]=x,p=a[p].link;
		if(p==-1)a[x].link=0;
		else
		{
			int q=a[p].son[calc(s[i])];
			if(a[p].len+1==a[q].len)a[x].link=q;
			else
			{
				int t=++cnt;
				a[t]=a[q];
				a[t].len=a[p].len+1;
				a[t].num=0;
				while(p!=-1&&a[p].son[calc(s[i])]==q)a[p].son[calc(s[i])]=t,p=a[p].link;
				a[x].link=a[q].link=t;
			}
		}
		last=x;
		if(s[i]=='(')sum--,update(i,sum);
		else
		{
			sum++;
			update(i,sum);
			int l=1,r=i-a[a[x].link].len,p=r;
//			cout<<i<<" "<<query(2)<<"\n";
			while(l<r)
			{
				int mid=(l+r)>>1;
				if(sum-query(mid)>=0)r=mid;
				else l=mid+1;
			}
			
			g[l-1].push_back({sum,-1});
			g[p-1].push_back({sum,1});
//			cout<<l<<" "<<p<<endl;
		}
		h[i]=sum;
	}
	vis[0]++;
	for(int i=1;i<=n;i++)
	{
		vis[h[i]]++;
		int len=g[i].size();
		for(int j=0;j<len;j++)res+=g[i][j].k*vis[g[i][j].x];
	}
	printf("%lld",res);
	return 0;
}
```


---

## 作者：Terac (赞：0)

这个题适合练习 SAM。

本质不同的子串有两种想法。一种是哈希，这里哈希很难判断括号串是否合法。还有一种是后缀数据结构，所以可以先用 SAM 将本质不同的子串搞出来。对于 SAM 上一个节点，就是一个以 $r$ 为结尾，$l$ 在一个区间内的所有子串。现在只用判断这些串是否都合法即可。

这不是难点。考虑从后往前看，遇到一个 `)` 就使 $sum_i=sum_{i+1}+1$，遇到一个 `(` 就使 $sum_i=sum_{i+1}-1$。这样一个子串 $s[l,\cdots,r]$ 合法当且仅当 $\forall i\in[l,r],sum_i\ge sum_{r+1}$ 且 $sum_l=sum_{r+1}$。那么我们预处理出 $pre_i$ 表示左边离 $i$ 最近的满足 $sum_j$ 值小于 $sum_i$ 的 $j$，查询时直接求左端点与 $pre_{r+1}$ 取 $\max$ 后的区间最小值和最小值出现次数即可，线段树维护。

时间复杂度 $O(n \log n)$。

---

## 作者：清烛 (赞：0)

来个比较好理解而且常数小（洛谷上暂时是最优解）的做法（线段树 + SAM，单 $\log$，无需二分）。

题意：问本质不同的合法括号子串数量，$n\le 5\times 10^5$。

看到本质不同子串考虑使用 SAM，然而合法括号子串是一个不太好处理的点。

那么不妨考虑在线添加右括号的时候，处理以 $S[i]$ 结尾的本质不同合法括号子串数量，同时我们用栈维护一下括号树，栈的元素个数即为当前树的深度。

根据 SAM 的性质和[这道题](https://www.luogu.com.cn/problem/P4070)，我们可以知道添加 $S[i]$ 后新增的本质不同子串数量为 $\operatorname{len}(u) - \operatorname{len}(\operatorname{link}(u))$，并且其右端点都是 $i$，左端点 $l$ 是连续的一段：$[1, \operatorname{len}(u) - \operatorname{len}(\operatorname{link}(u))]$。

那么我们考虑是否能维护在 $[1, \operatorname{len}(u) - \operatorname{len}(\operatorname{link}(u))]$ 内有多少合法的左括号呢？答案是肯定的。我们可以对于括号树的每个深度（即栈的每个 `top` 值）开一个线段树来进行存储对应深度内，某个区间有多少个左括号。

但是仅仅同一个深度这个限制可能是有问题的的，考虑串 $S = \texttt{(())(())}$，会发现与 $S[7]$ 相同深度的左括号有两个：$S[2]$ 和 $S[6]$，但很明显 $S[2]$ 不能作为合法的左括号。

究其原因，实际上是比 $S[7]$ 浅一层的括号中，有一个 $S[5]$ 卡住了使得其不能往左延伸，所以我们找到了一个更紧的下界，可以发现只要对应的左括号在更浅一层的左括号的右侧的话，其一定是合法的。

但是还需要注意特判一下右括号过多的情况，例如 $\texttt{())))()}$ 的时候，超出限制的右括号也会成为一个不能往左延伸的下界。

如果还有不明白的可以参考代码：

```cpp
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using ll = long long;
const int maxn = 5e5 + 5;
char s[maxn];

struct SAM {
    int ch[2], fa, len;
} sam[maxn << 1];
int n, stk[maxn], top, las = 1, totSAM = 1;

struct Node {
    int ch[2];
    ll sum;
} t[maxn * 60];
int tot, rt[maxn];

#define ls(u) t[u].ch[0]
#define rs(u) t[u].ch[1]
#define M ((i + j) >> 1)

void insert(int &k, int i, int j, int x) {
    if (!k) k = ++tot;
    ++t[k].sum;
    if (i == j) return;
    if (x <= M) insert(ls(k), i, M, x);
    else insert(rs(k), M + 1, j, x);
    return;
}

int query(int k, int i, int j, int x, int y) {
    if (!k || x > y) return 0;
    if (x <= i && y >= j) return t[k].sum;
    int ret = 0;
    if (x <= M) ret += query(ls(k), i, M, x, y);
    if (y > M) ret += query(rs(k), M + 1, j, x, y);
    return ret;
}

ll ans;

void extend(int id) {
    int cur = ++totSAM, c = s[id] - '(';
    sam[cur].len = sam[las].len + 1;
    int p = las;
    while (p && !sam[p].ch[c]) sam[p].ch[c] = cur, p = sam[p].fa;
    if (!p) sam[cur].fa = 1;
    else {
        int q = sam[p].ch[c];
        if (sam[q].len == sam[p].len + 1) sam[cur].fa = q;
        else {
            int clone = ++totSAM;
            sam[clone] = sam[q];
            sam[clone].len = sam[p].len + 1;
            while (p && sam[p].ch[c] == q) sam[p].ch[c] = clone, p = sam[p].fa;
            sam[q].fa = sam[cur].fa = clone;
        }
    }
    las = cur;
    if (!c) {
        stk[++top] = id; // 左括号即插入
        insert(rt[top], 1, n, id);
    } else {
        if (!top) { // 右括号过多，判下界
            stk[0] = id;
            return;
        }
        int l = max(1, stk[top - 1]); // 找到下界
        ans += query(rt[top--], 1, n, l, id - sam[sam[cur].fa].len); // id 其实就是 sam[cur].len
    }
    return;
}

int main() {
    scanf("%d", &n);
    scanf("%s", s + 1);
    FOR(i, 1, n) extend(i);
    printf("%lld\n", ans);
    return 0;
}
```

---

