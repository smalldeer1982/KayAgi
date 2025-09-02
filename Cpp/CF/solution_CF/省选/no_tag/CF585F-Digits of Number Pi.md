# Digits of Number Pi

## 题目描述

Vasily has recently learned about the amazing properties of number $ π $ . In one of the articles it has been hypothesized that, whatever the sequence of numbers we have, in some position, this sequence is found among the digits of number $ π $ . Thus, if you take, for example, the epic novel "War and Peace" of famous Russian author Leo Tolstoy, and encode it with numbers, then we will find the novel among the characters of number $ π $ .

Vasily was absolutely delighted with this, because it means that all the books, songs and programs have already been written and encoded in the digits of $ π $ . Vasily is, of course, a bit wary that this is only a hypothesis and it hasn't been proved, so he decided to check it out.

To do this, Vasily downloaded from the Internet the archive with the sequence of digits of number $ π $ , starting with a certain position, and began to check the different strings of digits on the presence in the downloaded archive. Vasily quickly found short strings of digits, but each time he took a longer string, it turned out that it is not in the archive. Vasily came up with a definition that a string of length $ d $ is a half-occurrence if it contains a substring of length of at least ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF585F/cb7b717ebd73c919034f7aa2697aede2fa62dd31.png), which occurs in the archive.

To complete the investigation, Vasily took $ 2 $ large numbers $ x,y $ ( $ x<=y $ ) with the same number of digits and now he wants to find the number of numbers in the interval from $ x $ to $ y $ , which are half-occurrences in the archive. Help Vasily calculate this value modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
02
10
19
```

### 输出

```
2
```

## 样例 #2

### 输入

```
023456789
10
19
```

### 输出

```
9
```

## 样例 #3

### 输入

```
31415926535
10
29
```

### 输出

```
20
```

# 题解

## 作者：lhm_ (赞：7)

考虑用数位 $DP$ 来统计数字串个数，用 $SAM$ 来实现子串的匹配。

设状态 $f(pos,cur,lenth,lim,flag)$，表示数位的位数，在 $SAM$ 上的节点，匹配的长度，是否有最高位限制，是否已经满足要求。

在 $dfs$ 转移时，若当前节点能接着匹配枚举到的字符，就直接转移，若不能，则在 $Parent$ 树上向上跳，直到能接着匹配，转移过程中判断是否满足条件即可。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 2010
#define maxd 55
#define mod 1000000007
using namespace std;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,d,tot=1,las=1,root=1,cnt;
int fa[maxn],len[maxn],ch[maxn][12],num[maxn],f[maxd][maxn][maxd][2][2];
char s[maxn],a[maxn],b[maxn];
void insert(int c)
{
	int p=las,np=las=++tot;
	len[np]=len[p]+1;
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
	    	len[nq]=len[p]+1,fa[nq]=fa[q],fa[np]=fa[q]=nq;
	    	while(ch[p][c]==q) ch[p][c]=nq,p=fa[p];
	    }
    }
}
int dp(int pos,int cur,int lenth,bool lim,bool flag)
{
    if(pos==cnt+1) return flag;
    if(f[pos][cur][lenth][lim][flag]!=-1) return f[pos][cur][lenth][lim][flag];
    int v=0,ma=9;
    if(lim) ma=num[pos];
    for(int c=0;c<=ma;++c)
    {
        if(flag) v=(v+dp(pos+1,cur,lenth,lim&&c==ma,1))%mod;
        else
        {
            int p=cur;
            if(ch[p][c]) v=(v+dp(pos+1,ch[p][c],lenth+1,lim&&c==ma,lenth+1>=d/2))%mod;
            else
            {
                while(p&&!ch[p][c]) p=fa[p];
		        if(p) v=(v+dp(pos+1,ch[p][c],len[p]+1,lim&&c==ma,len[p]+1>=d/2))%mod;
		        else v=(v+dp(pos+1,root,0,lim&&c==ma,0))%mod;
            }
        }
    }
    return f[pos][cur][lenth][lim][flag]=v;
}
int solve(char *s)
{
    cnt=strlen(s+1),memset(f,-1,sizeof(f));
    for(int i=1;i<=cnt;++i) num[i]=s[i]-'0';
    return dp(1,root,0,1,0);
}
int main()
{
    scanf("%s%s%s",s+1,a+1,b+1),n=strlen(s+1),d=cnt=strlen(a+1),a[cnt--]--;
    for(int i=1;i<=n;++i) insert(s[i]-'0');
    while(a[cnt]-'0'==-1) a[cnt]--,a[cnt--]=9+'0';
    printf("%d",(solve(b)-solve(a)+mod)%mod);
    return 0;
}
```

---

## 作者：xht (赞：6)

> [CF585F Digits of Number Pi](https://codeforc.es/contest/585/problem/F)

## 题意

- 给定长度为 $n$ 的数字串 $s$ 和长度为 $d$ 的不含前导零的数字串 $x,y(x \le y)$。
- 求**存在长度至少为 $\left\lfloor\frac{d}{2}\right\rfloor$ 的子串是 $s$ 的子串**的数字串 $t \in [x,y]$ 的数量。
- $n \le 10^3$，$d \le 50$。

## 题解

把 $s$ 所有长度为 $\left\lfloor\frac{d}{2}\right\rfloor$ 的子串拿出来建 AC 自动机，然后数位 dp 即可。

设 $f[i][j][1/0]$ 表示考虑到第 $i$ 位，在 AC 自动机的 $j$ 节点，是否 $(1/0)$ 有上界限制时的方案数，预处理出 $p[i][1/0]$ 为第 $i \sim d$ 位是否 $(1/0)$ 有上界限制时的方案数。

初始时 $f[0][1][1] = 1$。

枚举下一位的数字 $k$，设 $j\to k$ 为 AC 自动机中 $j$ 节点的第 $k$ 个儿子，设限制数字为 $c$。

- 任意时刻有 $f[i][j][0] \to f[i+1][j\to k][0]$；
- 若 $k < c$，则 $f[i][j][1] \to f[i+1][j\to k][0]$；
- 若 $k=c$，则 $f[i][j][1] \to f[i+1][j\to k][1]$；

最后用乘法原理将每种方案的 $f,p$ 相乘即可，时间复杂度 $\mathcal O(10nd^2)$。

## 代码

```cpp
const int N = 1e3 + 7, D = 53, K = 11;
int n, d, trie[N*D][K], ed[N*D], fail[N*D], tot = 1;
char s[N], a[D], b[D];
modint p[N][2], f[D][N*D][2];

inline void build() {
	int m = d / 2;
	for (int i = 1; i + m - 1 <= n; i++) {
		int p = 1;
		for (int j = i, k = 1; k <= m; j++, k++) {
			int c = s[j] - '0';
			if (!trie[p][c]) trie[p][c] = ++tot;
			p = trie[p][c];
		}
		ed[p] = 1;
	}
	queue< int > q;
	for (int i = 0; i < 10; i++)
		if (trie[1][i]) fail[trie[1][i]] = 1, q.push(trie[1][i]);
		else trie[1][i] = 1;
	while (q.size()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < 10; i++)
			if (trie[x][i]) fail[trie[x][i]] = trie[fail[x]][i], q.push(trie[x][i]);
			else trie[x][i] = trie[fail[x]][i];
	}
}

inline modint calc(char *t) {
	p[d+1][0] = p[d+1][1] = 1;
	for (int i = d; i; i--) p[i][0] = p[i+1][0] * 10, p[i][1] = (t[i] - '0') * p[i+1][0] + p[i+1][1];
	modint ans = 0;
	for (int i = 1; i <= d; i++)
		for (int j = 1; j <= tot; j++)
			for (int k = 0; k < 2; k++)
				f[i][j][k] = 0;
	f[0][1][1] = 1;
	for (int i = 0; i < d; i++)
		for (int j = 1; j <= tot; j++)
			if (!ed[j])
				for (int k = 0; k < 10; k++) {
					int o = trie[j][k];
					f[i+1][o][0] += f[i][j][0];
					if (k < t[i+1] - '0') f[i+1][o][0] += f[i][j][1];
					if (k == t[i+1] - '0') f[i+1][o][1] += f[i][j][1];
				}
	for (int i = 1; i <= d; i++)
		for (int j = 1; j <= tot; j++)
			if (ed[j]) ans += f[i][j][0] * p[i+1][0] + f[i][j][1] * p[i+1][1];
	return ans;
}

int main() {
	rds(s, n), rds(a, d), rds(b, d), build();
	int k = d;
	while (a[k] == '0') a[k--] = '9';
	--a[k];
	print(calc(b) - calc(a));
	return 0;
}
```

---

## 作者：Hoks (赞：5)

## 前言
比较好玩的 ACAM+dp，但是我感觉 CF 评高了吧，$3200$ 不至于，洛谷评个紫挺合理的。

有关串串可见：[串串博客](https://www.luogu.com.cn/article/dv6dig1o)。
## 思路分析
这个题目还是有点诈骗的，题目里强调突出了 **长度至少为 $\left\lfloor\frac{d}{2}\right\rfloor$**，这玩意显然是个诈骗。

因为长度大于 $\left\lfloor\frac{d}{2}\right\rfloor$ 的都符合了，那把符合的这一段再取一段长度为 $\left\lfloor\frac{d}{2}\right\rfloor$ 的，显然也是符合的。

那么题意就变成了：
> - 求**存在长度为 $\left\lfloor\frac{d}{2}\right\rfloor$ 的子串是 $s$ 的子串**的数字串 $t \in [x,y]$ 的数量。
> - $n\le10^3,d\le50$。

不难发现题意中的模式串就是字符串 $s$ 所有长度为 $\left\lfloor\frac{d}{2}\right\rfloor$ 的子串，直接 $n^2$ 枚举插入 ACAM。

接着无脑建出 Fail 树，考虑怎么处理剩下的东西。

数字数数问题，想到什么？

数位 dp！

考虑设计 dp 状态：$dp_{i,j,0/1}$ 表示填到第 $i$ 位，在 ACAM 的状态 $j$ 上**有/无**上限。

那么就可以得到状态转移方程式，假设我们枚举的字符为 $c$。
$$dp_{i+1,\delta(j,c),0}=dp_{i,j,0}$$
$$dp_{i+1.\delta(j,c),1}=dp_{i,j,0},s_{i+1}<c$$
$$dp_{i+1.\delta(j,c),1}=dp_{i,j,1},s_{i+1}=c$$
把转移式子全部加下就行了。

但这样就行了吗？

转化后的题意中，我们求的是有模式串为子串的数字串个数，那么长度不到 $d$ 的数字串便可以在后面随意添加数字。

也就是每一项都要乘上一个系数，这个系数递推也非常简单了。
$$op_{i+1,0}=op_{i,0}\times10$$
$$op_{i+1.1}=op_{i,0}\times s_i+op_{i,1}$$
记得倒序枚举，乘的时候下标 $+1$ 即可。

**Tips：数位 dp 经典差分的时候别忘了给左端点 $-1$，当心减出负数。**
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=50010,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n,d,op[N][2],dp[55][N][2];char s[N],a[N],b[N];
struct ACAM
{
	struct node{int nxt,ed,v[26];}t[N];int tot=0;
	inline void insert(char s[],int n,int st)
	{
		int u=0;
		for(int i=st;i<=st+n-1;i++){if(!t[u].v[s[i]-'0']) t[u].v[s[i]-'0']=++tot;u=t[u].v[s[i]-'0'];}
		t[u].ed=1;
	}
	inline void build()
	{
		queue<int>q;
		for(int i=0;i<10;i++) if(t[0].v[i]) t[t[0].v[i]].nxt=0,q.push(t[0].v[i]);
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=0;i<10;i++)
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
        while(!isdigit(fc)&&fc!=-1){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)&&fc!=-1) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        if(fc==-1) exit(0);return x*t;
    }
    inline void print(int x)
    {
        if(x<0) putchar('-'),x=-x;
        if(x>9) print(x/10);
        putchar(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline int calc(char s[])
{
	op[d+1][0]=op[d+1][1]=1;int ans=0;memset(dp,0,sizeof dp);dp[0][0][1]=1;
	for(int i=d;i>=1;i--) op[i][0]=op[i+1][0]*10%mod,op[i][1]=(op[i+1][0]*(s[i]-'0')+op[i+1][1])%mod;
	for(int i=0;i<d;i++)
		for(int j=0;j<=ac.tot;j++)
			if(!ac.t[j].ed)
				for(int k=0;k<10;k++)
				{
					int v=ac.t[j].v[k];
					dp[i+1][v][0]=(dp[i+1][v][0]+dp[i][j][0])%mod;
					if(k<s[i+1]-'0') dp[i+1][v][0]=(dp[i+1][v][0]+dp[i][j][1])%mod;
					if(k==s[i+1]-'0') dp[i+1][v][1]=(dp[i+1][v][1]+dp[i][j][1])%mod;
				}
	for(int i=1;i<=d;i++)
		for(int j=0;j<=ac.tot;j++)
			if(ac.t[j].ed) ans=(ans+dp[i][j][0]*op[i+1][0]%mod+dp[i][j][1]*op[i+1][1]%mod)%mod;
	return ans;
}
signed main()
{
    rd(s,n);rd(a,d);d=0;rd(b,d);int m=d/2;
	for(int i=1;i+m-1<=n;i++) ac.insert(s,m,i);
	ac.build();int k=d;while(a[k]=='0') a[k--]='9';a[k]--;
	print(((calc(b)-calc(a))%mod+mod)%mod);
	return 0;
}
```

---

## 作者：灵梦 (赞：4)

这道题比较普遍的做法是对 $s$ 所有长度为 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 的子串建立 AC 自动机，然后在上面跑数位 DP。但我首先想到的解法是下面的后缀自动机做法。

题意可以转化为求与 $s$ 的**最长公共子串**长度不小于 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 的数字串个数。考虑 SAM 求 LCS 的方法，每加入一个字符往上跳 $parent$，直到有这个字符的出边为止，同时更新最长公共后缀长度。用数位 DP 模拟这个过程，除了当前确定了前几位、是否有上 / 下界限制这些必要的状态外，还需要记录当前串在 SAM 的哪个节点上，以及当前最长公共后缀长度。为了判断是否合法，再加一维 0/1 状态表示当前的最长公共子串是否在 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 以上。

现在考虑转移，即加入一个字符。可以尝试直接跳 $parent$，我交了一次居然过了，，但这样的复杂度可能没有保障。不过因为 $n$ 比较小，可以 $O(n^2)$ 预处理转移，所以问题也不大。总复杂度为 $O(10(n^2+nd^2))$。

---

## 作者：绝顶我为峰 (赞：3)

虚假的 *3200?

真实的 *2300!

把 $s$ 的所有后缀建一个 AC 自动机，对每个点求出深度之后，一个串的匹配可以看做在 AC 自动机上走，这个串出现了长度不小于 $\lfloor\frac d2\rfloor$ 的 $s$ 的子串当且仅当行走的路径上经过了深度大于等于 $\lfloor\frac d2\rfloor$ 的点。

接下来是数字范围的限制，套路地差分一下转化为 $[1,y]$ 的答案减掉 $[1,x-1]$ 的答案，然后这种数字上界的限制自然想到数位 dp。

记 $dp_{i,0/1,0/1,j}$ 表示填了前 $i$ 位，当前前缀是否顶上界，是否已经经过了深度大于 $\lfloor\frac d2\rfloor$ 的点，当前位于 AC 自动机上 $j$ 号点的方案数。

转移的时候直接枚举下一位填什么，沿着 AC 自动机上的边走过去即可。

时间复杂度 $O(n^2d)$，可以滚动数组优化掉第一维状态。

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<string>
#include<cstring>
using namespace std;
const int mod=1000000007;
int n,m,tot,ch[500001][11],fail[500001],dep[500001],dp[2][2][2][500001],now;
string s,a,b;
inline int Mod(int x)
{
    return x>=mod? x-mod:x;
}
inline void insert(int x)
{
    int node=0;
    for(int i=x;i<=n;++i)
    {
        if(!ch[node][s[i]-'0'])
        {
            ch[node][s[i]-'0']=++tot;
            dep[tot]=dep[node]+1;
        }
        node=ch[node][s[i]-'0'];
    }
}
inline void getfail()
{
    queue<int> q;
    for(int i=0;i<10;++i)
        if(ch[0][i])
            q.emplace(ch[0][i]);
    while(!q.empty())
    {
        int k=q.front();
        q.pop();
        for(int i=0;i<10;++i)
            if(ch[k][i])
            {
                fail[ch[k][i]]=ch[fail[k]][i];
                q.emplace(ch[k][i]);
            }
            else
                ch[k][i]=ch[fail[k]][i];
    }
}
inline int solve(string str)
{
    memset(dp,0,sizeof dp);
    now=0;
    dp[0][1][0][0]=1;
    for(int i=1;i<=m;++i)
    {
        int lim=str[i]-'0';
        now^=1;
        memset(dp[now],0,sizeof dp[now]);
        for(int j=0;j<2;++j)
            for(int k=0;k<2;++k)
                for(int p=0;p<=tot;++p)
                    if(dp[now^1][j][k][p])
                        for(int g=0;g<=(j? lim:9);++g)
                            dp[now][j&&g==lim][k||dep[ch[p][g]]>=(m>>1)][ch[p][g]]=Mod(dp[now][j&&g==lim][k||dep[ch[p][g]]>=(m>>1)][ch[p][g]]+dp[now^1][j][k][p]);
    }
    int res=0;
    for(int i=0;i<2;++i)
        for(int j=0;j<=tot;++j)
            res=Mod(res+dp[now][i][1][j]);
    return res;
}
int main()
{
    cin>>s>>a>>b;
    n=s.length();
    m=a.length();
    s=" "+s;
    a=" "+a;
    b=" "+b;
    --a[m];
    for(int i=m;i>=1&a[i]<'0';--i)
    {
        a[i]='9';
        --a[i-1];
    }
    for(int i=1;i<=n;++i)
        insert(i);
    getfail();
    cout<<Mod(solve(b)-solve(a)+mod)<<'\n';
    return 0;
}
```

---

## 作者：wcyQwQ (赞：3)


[题目传送门](https://www.luogu.com.cn/problem/CF585F)

[可能更好的阅读体验](https://chenyu-w.github.io/2022/07/18/CF585F%20Digits%20of%20Number%20Pi/)

## 前言

FOI2022 上 lh 大佬课堂例题上唯一一道会打的黑题，顺便水一发记忆化搜索的题解。

### 前置芝士

ACAM，数位 DP

## 分析

看到这是个判断子串的问题，首先考虑建出 ACAM，然后我们考虑把那些字符串插入 ACAM 中。

观察到如果说存在大于 $\lfloor\frac{d}{2}\rfloor$ 的子串为 $s$ 的子串，那么一定存在长度等于 $\lfloor\frac{d}{2}\rfloor$ 的子串为 $s$ 的子串，所以我们只需把 $s$ 的所有长度为 $\lfloor\frac{d}{2}\rfloor$ 的子串插入 ACAM 即可，然后非常套路地维护一个 $ed$ 值记录一下这个节点是否为某个子串的结尾，在建 ACAM 的时候通过 $fail$ 指针转移。

然后考虑数位 DP，我们用 $f[pos][p][0/1]$ 表示还剩 $pos$ 位，走到了 ACAM 的节点 $p$，当前是否包含给定子串的方案数，然后我们直接套数位 DP 模板即可。

## 代码

```c++
#include <bits/stdc++.h>

using namespace std;
const int N = 1e3 + 10, M = 55, mod = 1e9 + 7;
int t[N * M][10], ed[N * M], fail[N * M], idx;
char s[N], l[N], r[N];
int a[N];
int f[M][N * M][2];
int d;

inline void insert()
{
	int len = strlen(s + 1);
	for (int i = 1; i + d - 1 <= len; i++)
	{
		int p = 0;
		for (int j = i; j <= i + d - 1; j++)
		{
			int c = s[j] - '0';
			if (!t[p][c]) t[p][c] = ++idx;
			p = t[p][c];
		}
		ed[p] = 1;
	}
}

inline void build()
{
	queue<int> q;
	for (int i = 0; i < 10; i++)
		if (t[0][i])
			q.push(t[0][i]);
	while (q.size())
	{
		int p = q.front();
		q.pop();
		for (int i = 0; i < 10; i++)
		{
			int c = t[p][i];
			if (!c) t[p][i] = t[fail[p]][i];
			else
			{
				fail[c] = t[fail[p]][i];
				ed[c] |= ed[fail[c]];
				q.push(c); 
			}
		}
	}
}

inline int dfs(int pos, int p, bool lead, bool lim, bool st)
{
	if (!pos) return st && !lead;
	if (!lead && !lim && ~f[pos][p][st]) return f[pos][p][st];
	int res = 0;
	int up = lim ? a[pos] : 9;
	for (int i = 0; i <= up; i++)
		res = (res + dfs(pos - 1, (lead && !i) ? 0 : t[p][i], lead && !i, lim && i == up, lead && !i ? 0 : st | ed[t[p][i]])) % mod;
	if (!lead && !lim) f[pos][p][st] = res;
	return res;
}

inline int solve()
{
	memset(f, -1, sizeof f);
	int len = strlen(l + 1);
	for (int i = 1; i <= len; i++)
		a[len - i + 1] = l[i] - '0';
	int tmp = 1;
	while (a[tmp] == 0) a[tmp++] = 9;
	a[tmp]--;
	int r1 = dfs(len, 0, 1, 1, 0);
	for (int i = 1; i <= len; i++)
		a[len - i + 1] = r[i] - '0';
	int r2 = dfs(len, 0, 1, 1, 0);
	return (r2 - r1 + mod) % mod;
}

int main()
{
	scanf("%s%s%s", s + 1, l + 1, r + 1);
	d = strlen(l + 1) / 2;
	insert();
	build();
	printf("%d", solve());
	return 0;
}
```





---

## 作者：WrongAnswer_90 (赞：2)

[CF585F Digits of Number Pi](https://www.luogu.com.cn/problem/CF585F)

[更好的阅读体验](https://www.cnblogs.com/WrongAnswer90-home/p/17765571.html)

观察数据范围，考虑数位 DP。

首先把长串中 $len\geq\lfloor \frac{d}{2}\rfloor$ 的串提出来，塞进一个 trie 里，然后建立 ACAM，然后直接 DP 就行了。

设 $f_{i,j,0/1,0/1,0/1}$ 表示当前在 trie 图上走了 j 步到达了第 i 个节点，是否已经出现子串，是否满足低位限制，是否满足高位限制，枚举 $k$ 表示第 $j$ 个字符是什么，然后在 AC 自动机上跑。第三个 $0/1$ 在走到一个结束点后就一定是 $1$，第四个维度选了一个大于 $x$ 串当前位的字符后变成 $1$，第五个维度也是同理，细节比较多，但是实在是没有任何思维含量。详细的转移方程见代码。

```cpp
inline void Madd(int&x,int y){x+y>=MOD?x=x+y-MOD:x=x+y;}
int n,d,ans,f[2][500001][2][2][2];
char s[1001],t1[1001],t2[1001];
namespace ACAM
{
	int end[500001],trie[500001][10],fail[500001],cnt=1;
	queue<int> q;
	inline void build()
	{
		for(int i=0;i<10;++i)trie[0][i]=1;
		for(int i=1;i+d/2-1<=n;++i)
		{
			int now=1;
			for(int j=i;j<=min(n,i+d/2-1);++j)
			{
				if(!trie[now][s[j]-'0'])trie[now][s[j]-'0']=++cnt;
				now=trie[now][s[j]-'0'];
				if(j>=i+d/2-1)end[now]=1;
			}
		}
		q.e(1);
		while(!q.empty())
		{
			int now=q.front();q.pop();
			for(int i=0;i<10;++i)
			{
				if(trie[now][i])fail[trie[now][i]]=trie[fail[now]][i],q.e(trie[now][i]);
				else trie[now][i]=trie[fail[now]][i];
			}
		}
	}
}
using namespace ACAM;
#define g f[pre][trie[i][k]]
#define nw f[now][i]
inline void mian()
{
	scanf("%s%s%s",s+1,t1+1,t2+1),ans=0,n=strlen(s+1),d=strlen(t1+1);
	for(int i=1;i<=d;++i)t1[i]-='0',t2[i]-='0';
	build(),f[1][1][0][0][0]=1;int now=0,pre=1;
	for(int j=0;j<d;++j)
	{
		now^=1,pre^=1,memset(f[pre],0,sizeof(f[pre]));
		for(int i=1;i<=cnt;++i)
		{
			for(int k=0;k<10;++k)
			{
				int is=end[trie[i][k]];
				if(k<t1[j+1])
				{
					if(k<t2[j+1])
					{
						Madd(g[is|0][1][1],nw[0][1][0]),Madd(g[is|0][1][1],nw[0][1][1]);
						Madd(g[is|1][1][1],nw[1][1][0]),Madd(g[is|1][1][1],nw[1][1][1]);
					}
					else if(k==t2[j+1])
					{
						Madd(g[is|0][1][0],nw[0][1][0]),Madd(g[is|0][1][1],nw[0][1][1]);
						Madd(g[is|1][1][0],nw[1][1][0]),Madd(g[is|1][1][1],nw[1][1][1]);
					}
					else
					{
						Madd(g[is|0][1][1],nw[0][1][1]),Madd(g[is|1][1][1],nw[1][1][1]);
					}
				}
				else if(k==t1[j+1])
				{
					if(k<t2[j+1])
					{
						Madd(g[is|0][0][1],nw[0][0][0]),Madd(g[is|0][0][1],nw[0][0][1]);
						Madd(g[is|0][1][1],nw[0][1][0]),Madd(g[is|0][1][1],nw[0][1][1]);
						Madd(g[is|1][0][1],nw[1][0][0]),Madd(g[is|1][0][1],nw[1][0][1]);
						Madd(g[is|1][1][1],nw[1][1][0]),Madd(g[is|1][1][1],nw[1][1][1]);
					}
					else if(k==t2[j+1])
					{
						Madd(g[is|0][0][0],nw[0][0][0]),Madd(g[is|0][0][1],nw[0][0][1]);
						Madd(g[is|0][1][0],nw[0][1][0]),Madd(g[is|0][1][1],nw[0][1][1]);
						Madd(g[is|1][0][0],nw[1][0][0]),Madd(g[is|1][0][1],nw[1][0][1]);
						Madd(g[is|1][1][0],nw[1][1][0]),Madd(g[is|1][1][1],nw[1][1][1]);
					}
					else
					{
						Madd(g[is|0][0][1],nw[0][0][1]),Madd(g[is|0][1][1],nw[0][1][1]);
						Madd(g[is|1][0][1],nw[1][0][1]),Madd(g[is|1][1][1],nw[1][1][1]);
					}
				}
				else
				{
					if(k<t2[j+1])
					{
						Madd(g[is|0][1][1],nw[0][0][0]),Madd(g[is|0][1][1],nw[0][0][1]);
						Madd(g[is|0][1][1],nw[0][1][0]),Madd(g[is|0][1][1],nw[0][1][1]);
						Madd(g[is|1][1][1],nw[1][0][0]),Madd(g[is|1][1][1],nw[1][0][1]);
						Madd(g[is|1][1][1],nw[1][1][0]),Madd(g[is|1][1][1],nw[1][1][1]);
					}
					else if(k==t2[j+1])
					{
						Madd(g[is|0][1][0],nw[0][0][0]),Madd(g[is|0][1][0],nw[0][1][0]);
						Madd(g[is|0][1][1],nw[0][0][1]),Madd(g[is|0][1][1],nw[0][1][1]);
						Madd(g[is|1][1][0],nw[1][0][0]),Madd(g[is|1][1][0],nw[1][1][0]);
						Madd(g[is|1][1][1],nw[1][0][1]),Madd(g[is|1][1][1],nw[1][1][1]);
					}
					else
					{
						Madd(g[is|0][1][1],nw[0][0][1]),Madd(g[is|0][1][1],nw[0][1][1]);
						Madd(g[is|1][1][1],nw[1][0][1]),Madd(g[is|1][1][1],nw[1][1][1]);
					}
				}
			}
		}
	}
	for(int i=1;i<=cnt;++i)
	{
		Madd(ans,f[pre][i][1][0][0]),Madd(ans,f[pre][i][1][0][1]);
		Madd(ans,f[pre][i][1][1][0]),Madd(ans,f[pre][i][1][1][1]);
	}
	write(ans);
}
```

---

## 作者：zombie462 (赞：2)

$AC$自动机板子+数位$dp$即可

题意概要：

定义长度为$d$的字符串$T$为字符串$S$的半匹配串，当且仅当$T$内存在长度至少为$\lfloor \frac{d}{2}\rfloor$的子串，使得其为$S$的子串。

给出一个字符串$S$，两个长度都为$d$的十进制整数字符串$x$和$y$，求区间$[x,y]$中有多少个数字字符串是$S$的半匹配串。

输入的第一行为$S$，第二行为$x$，第三行为$y$。$x$和$y$不含前导零。

数据保证$1\leq|S|\leq$，$2\leq d\leq 50$。

请将答案对$10^9+7$取模。

$AC$自动机来处理匹配串。

数位$dp$来实现数字区间内的转化和推导。

实现见代码：

```
#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define N 33333
#define mod 1000000007
LL DP[2][N][2];
int E[N],tot=0,tt;
char C[1111];
char A[55],B[55];
int n;
struct AC_Automaton{ //AC自动机模板，几乎没有更改，所以不解释
	int trans[N][10],fail[N],cur=0;
	int q[N],head,tail;
	void build_trie(){
  		int m=strlen(C+1),l=n/2;
  		for (int i=1;i+l-1<=m;i++){
    		int p=0;
    		for (int j=i;j<=i+l-1;j++){
    			int k=C[j]-'0';
    			if (!trans[p][k]) trans[p][k]=++cur;
    			p=trans[p][k];
        	}
        	E[++tot]=p;
    	}	
	}
	void AC_build(){
    	head=tail=0;
    	for (int i=0;i<10;i++)
        	if (trans[0][i])
            	q[tail++]=trans[0][i];
    	while (head<tail){
        	int u=q[head++];
        	for (int i=0;i<10;i++){
            	if (trans[u][i]){
                	int son=trans[u][i],p=fail[u];   
                	son=trans[u][i];
                	while (p && !trans[p][i]) p=fail[p];
                	fail[son]=trans[p][i];   
                	q[tail++]=son;
            	}
        	}
    	}
	}
}AC;
LL Dightal_DP(char* c){ //数位DP部分 
    memset(DP,0,sizeof(DP));
    int pp=0;tt=0;
    int now=0,last=1;
    for (int i=1;i<=n;i++){
        swap(now,last);
        memset(DP[now],0,sizeof(DP[now]));
        for (int j=0;j<=AC.cur;j++){ //递推核心部分
            for (int k=0;k<10;k++){
                int p=j;
                while (!AC.trans[p][k] && p) p=AC.fail[p];
                p=AC.trans[p][k];
                DP[now][p][0]+=DP[last][j][0];
                if (DP[now][p][0]>=mod) DP[now][p][0]-=mod;
                DP[now][p][1]+=DP[last][j][1];
                if (DP[now][p][1]>=mod) DP[now][p][1]-=mod;
            }
        }
        for (int k=0;k<c[i]-'0';k++){ //继续寻找下一个匹配串
            int p=pp;
            while (!AC.trans[p][k] && p) p=AC.fail[p];
            p=AC.trans[p][k];
            DP[now][p][tt]++;
            if (DP[now][p][tt]>=mod) DP[now][p][tt]-=mod;
        }
        int k=c[i]-'0'; //当前节点是pp,如果不能往k儿子走,就往fail跳 
        while (!AC.trans[pp][k] && pp) pp=AC.fail[pp]; //跳出循环时,要么找到了一个有k儿子的后缀节点,要么跳回了根节点
		pp=AC.trans[pp][k];
		for (int j=1;j<=tot;j++){
            DP[now][E[j]][1]+=DP[now][E[j]][0];
            DP[now][E[j]][0]=0;
            if (DP[now][E[j]][1]>=mod) DP[now][E[j]][1]-=mod;
            if (E[j]==pp) tt=1;
        }
    }
    LL ret=tt;
    for (int i=0;i<=AC.cur;i++){
        ret+=DP[now][i][1];
        if (ret>=mod) ret-=mod;
    }
    return ret;
}
int main(){
    scanf("%s",C+1); //读入
    scanf("%s",A+1);
    scanf("%s",B+1); 
    n=strlen(A+1);
    AC.build_trie(); //建出AC自动机
    AC.AC_build();
    LL ans=Dightal_DP(B)-Dightal_DP(A);
    ans+=tt;
    if (ans<0) ans+=mod;
    cout<<ans<<endl; //输出
    return 0;
}
```

---

## 作者：约瑟夫用脑玩 (赞：1)

我看题解的 SAM 复杂度不太行，这里提供一个复杂度没问题的，同样是用数位 DP 来统计数字串个数，用 SAM 来实现子串的匹配。

设 $f_{p,i,j,f1,f2}$ 表示当前 DP 到第 $p$ 位，在 SAM 上 $i$ 这个节点，当前长度为 $j$，下界是否解除 $f1\in\left\{0,1\right\}$，上界是否解除 $f2\in\left\{0,1\right\}$，有多少串还未满足 $\ge\lfloor\dfrac{d}{2}\rfloor$。

根据上下界枚举接下来可以选的数字，通过预处理直接转移到 SAM 下一个节点，如果满足了 $\ge\lfloor\dfrac{d}{2}\rfloor$ 就直接累进答案。

状态 $O(nd^2)$，转移 $O(\text{字符集大小})$。

和第一篇题解的主要区别应该在于转移的时候他是暴力 $O(n)$ 跳，我预处理了直接 $O(1)$ 找，其他的应该都是常数问题，如非递归，状态少一半。

这里预处理可以简单做到 $O(n* \text{字符集大小})$，不是瓶颈，这样看 $n$ 多个 0 暴力跳应该就无了。

[代码](https://www.luogu.com.cn/paste/wsu06njp)

---

## 作者：lkytxdy (赞：0)

AC 自动机 + 数位 DP

> 给出一个数字串 $s$，和两个长度为 $d$ 的不含前导零的数字串 $l,r$。
>
> 求有多少 $x\in[l,r]$ 的数字串 $x$，存在长度 $\geq\lfloor\frac d 2\rfloor$ 的子串在 $s$ 中出现过。对 $10^9+7$ 取模。
>
> $1\leq |s|\leq 10^3$，$l\leq r$，$2\leq d\leq 50$。

难度虚高。

对 $s$ 所有长度为 $\lfloor\frac d 2\rfloor$ 的子串建立 AC 自动机。

设 $f_{i,p,0/1,0/1}$ 表示填了 $x$ 的 $i$ 个字符，跑到 AC 自动机上的节点 $p$，是否匹配过 $s$ 某个 $\lfloor\frac d 2\rfloor$ 的子串，是否顶到上界，此时的方案数即可。

```cpp
//lkytxdy
#include<bits/stdc++.h>
using namespace std;
const int N=2.5e4+5,mod=1e9+7;
int n,d,a[N],tot=1,ch[N][10],fail[N],vis[N],f[55][N][2];
char s[N],l[N],r[N];
queue<int>q;
void getfail(){
	fill(ch[0],ch[0]+10,1),q.push(1);
	while(q.size()){
		int x=q.front(),y; vis[x]|=vis[fail[x]],q.pop();
		for(int i=0;i<10;i++){
			if((y=ch[x][i])) fail[y]=ch[fail[x]][i],q.push(y);
			else ch[x][i]=ch[fail[x]][i];
		}
	}
}
int dfs(int i,int p,bool ok,bool lim){
	if(i>d) return ok;
	if(!lim&&~f[i][p][ok]) return f[i][p][ok];
	int end=lim?a[i]:9,ans=0;
	for(int j=0;j<=end;j++)
		ans=(ans+dfs(i+1,ch[p][j],ok|vis[ch[p][j]],lim&&j==end))%mod;
	if(!lim) f[i][p][ok]=ans;
	return ans;
}
int calc(char *s){
	for(int i=1;i<=d;i++) a[i]=s[i]-'0';
	return dfs(1,1,0,1);
}
signed main(){
	scanf("%s%s%s",s+1,l+1,r+1),n=strlen(s+1),d=strlen(l+1);
	for(int i=1;i<=n-d/2+1;i++){
		int p=1,k;
		for(int j=i;j<=i+d/2-1;j++){
			if(!ch[p][k=s[j]-'0']) ch[p][k]=++tot;
			p=ch[p][k];
		}
		vis[p]=1;
	}
	getfail();
	for(int i=d;i>=1;i--) if(l[i]!='0'){
		for(int j=i+1;j<=d;j++) l[j]='9';
		l[i]--; break;
	}
	memset(f,-1,sizeof(f));
	printf("%d\n",(calc(r)-calc(l)+mod)%mod);
	return 0;
} 
```





---

## 作者：Caicz (赞：0)

### 前言

又是zzy讲课，果然zzy讲课就算是字符串专题也涵盖了dp呢

### 题意

给定长度为 n 的数字串 s 和长度为 d 的不含前导零的数字串 $x,y(x\le y)$
求**存在长度至少为** $\left\lfloor\frac{d}{2}\right\rfloor$ **的子串是 s 的子串**的数字串 $t \in [x,y]$ 的数量。
$n \le 10^3$，$d \le 50$，答案对 $10^9+7$ 取模。

### 题解

首先是一个暴力的思路，对于所有长度为 $\left\lfloor\frac{d}{2}\right\rfloor$ 的 s 的子串，建一个AC自动机，建好后，对所有 $t \in [x,y]$ 跑 AC自动机统计答案

考虑到 $x,y$ 的范围，容易想到数位DP，对于 $t \in [x,y]$ ，可以差分处理

考虑我们需要记录的值：

**当前数字是第几位**

**当前数字是什么**

**我们当前走到AC自动机的哪个结点**

**当前状态是否已经合法**

同时为了合法的转移，我们还需要记录**是否达到瓶颈( 即之前的位数都与边界值相等)**
，所以我们得到了状态 $f[i][k][ft1][now][ft2]$ 

此时我们空间复杂度为 $O(40\times d^2n)$ 估算一下空间大小，难以接受，考虑滚动数组

于是最终我们得到的状态转移方程为
$$
\begin{cases}
f[k][1][v][end[v]|ft]+=f[j][1][u][ft]\quad(k=x[i],j=x[i-1])\\
f[k][0][v][end[v]|ft]+=f[j][1][u][ft]\quad(k<x[i],j=x[i-1])\\
f[k][0][v][end[v]|ft]+=f[j][0][u][ft]
\end{cases}
$$
通过转移方程，我们需要枚举 
**当前的位数**

**当前的数字**

**之前的数字**

**之前走到了哪个结点**

**当前的状态（合法/不合法）**

时间复杂度 $O(200\times d^2n)$ 但有许多无用情况会被枚举，这些情况我们可以通过判断跳过，时间上远达不到此上界
$$
\large\color{grey}{\text{Talk is cheap , show you the code}}
$$


#### 代码

```cpp
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<cstring>
#include<time.h>
#include<math.h>
#include<queue>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn=50005;
const int inf=0x3f3f3f3f;
const int p=1e9+7;
char s[maxn];
char tmp[maxn];
struct node
{
	int ch[10],pos,fail;
}tr[maxn];
int n,d,tot,a[maxn],b[maxn],rt=0;
ll ans,f[10][2][maxn][2],g[10][2][maxn][2];
queue<int>q;

inline void insert(int st)
{
	int u=rt;
	for(register int i=st;i<st+d/2;++i)
	{
		int c=s[i]-'0';
		if(!tr[u].ch[c])tr[u].ch[c]=++tot;
		u=tr[u].ch[c];
	}
	tr[u].pos=true;
}

inline void get_fail(void)
{
	for(register int i=0;i<10;++i)if(tr[rt].ch[i])q.push(tr[rt].ch[i]);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(register int i=0;i<10;++i)
			if(tr[u].ch[i])
				tr[tr[u].ch[i]].fail=tr[tr[u].fail].ch[i],q.push(tr[u].ch[i]);
			else
				tr[u].ch[i]=tr[tr[u].fail].ch[i];
	}
}

signed main(void)
{
	cin>>s;
	cin>>tmp;
	n=strlen(s),d=strlen(tmp);
	for(register int i=0;i<d;++i)a[i]=tmp[i]-'0';
	cin>>tmp;
	for(register int i=0;i<d;++i)b[i]=tmp[i]-'0';
	--a[d-1];
	for(register int i=d-1;i>0;--i)
		if(a[i]<0)a[i]=a[i]+10,--a[i-1];
	for(register int i=0;i<n;++i)
	{
		if(i+d/2>n)break;
		insert(i);
	}
	get_fail();
	for(register int i=0;i<b[0];++i)g[i][0][tr[rt].ch[i]][tr[tr[rt].ch[i]].pos]=1;
	g[b[0]][1][tr[rt].ch[b[0]]][tr[tr[rt].ch[b[0]]].pos]=1;
	for(register int i=1;i<d;++i)
	{
		for(register int u=0;u<=tot;++u)
			for(register int j=0;j<10;++j)
			{
				if(!g[j][1][u][1]&&!g[j][1][u][0]&&!g[j][0][u][0]&&!g[j][0][u][1])continue;
				for(register int k=0;k<10;++k)
				{
					int v=tr[u].ch[k];
					for(register int ft=0;ft<2;++ft)
					{
						if(j==b[i-1]&&k==b[i]) (f[k][1][v][tr[v].pos|ft]+=g[j][1][u][ft])%=p;
						else if(k<b[i]&&j==b[i-1]) (f[k][0][v][tr[v].pos|ft]+=g[j][1][u][ft])%=p;
						(f[k][0][v][tr[v].pos|ft]+=g[j][0][u][ft])%=p;
					}
				}		
			}		
		for(register int u=0;u<=tot;++u)
			for(register int k=0;k<10;++k)
			{
				g[k][0][u][1]=f[k][0][u][1];
				g[k][1][u][1]=f[k][1][u][1];
				g[k][0][u][0]=f[k][0][u][0];
				g[k][1][u][0]=f[k][1][u][0];
				if(i==d-1)(ans+=f[k][0][u][1]+f[k][1][u][1])%=p;
				f[k][0][u][1]=f[k][1][u][1]=f[k][0][u][0]=f[k][1][u][0]=0;
			}
	}
	memset(g,0,sizeof g);
	int gft=false;
	for(register int i=0;i<d;++i)if(a[i]>0)gft=true;
	if(gft)
	{
		for(register int i=0;i<a[0];++i)g[i][0][tr[rt].ch[i]][tr[tr[rt].ch[i]].pos]=-1;
		g[a[0]][1][tr[rt].ch[a[0]]][tr[tr[rt].ch[a[0]]].pos]=-1;
		for(register int i=1;i<d;++i)
		{
			for(register int u=0;u<=tot;++u)
				for(register int j=0;j<10;++j)
				{
					if(!g[j][1][u][1]&&!g[j][1][u][0]&&!g[j][0][u][0]&&!g[j][0][u][1])continue;
					for(register int k=0;k<10;++k)
					{
						int v=tr[u].ch[k];
						for(register int ft=0;ft<2;++ft)
						{
							if(j==a[i-1]&&k==a[i]) (f[k][1][v][tr[v].pos|ft]+=g[j][1][u][ft])%=p;
							else if(k<a[i]&&j==a[i-1]) (f[k][0][v][tr[v].pos|ft]+=g[j][1][u][ft])%=p;
							(f[k][0][v][tr[v].pos|ft]+=g[j][0][u][ft])%=p;
						}
					}
				}			
			for(register int u=0;u<=tot;++u)
				for(register int k=0;k<10;++k)
				{
					g[k][0][u][1]=f[k][0][u][1];
					g[k][1][u][1]=f[k][1][u][1];
					g[k][0][u][0]=f[k][0][u][0];
					g[k][1][u][0]=f[k][1][u][0];
					if(i==d-1)ans=(ans+f[k][0][u][1]+f[k][1][u][1]+p)%p;
					f[k][0][u][1]=f[k][1][u][1]=f[k][0][u][0]=f[k][1][u][0]=0;
				}
		}
	}
	cout<<ans<<endl;
}

```



---

