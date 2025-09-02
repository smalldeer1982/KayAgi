# Letters and Question Marks

## 题目描述

你有一个字符串 $S$ 和一个字符串数组 $[t_1, t_2, \ldots, t_k]$。每个字符串 $t_i$ 仅包含 `a` 到 `n` 以内的小写字母；$S$ 中仅包含 `a` 到 `n` 以内的小写字母和不超过 $14$ 个问号。

每一个字符串 $t_i$ 有一个整数花费 $c_i$。一个字符串 $T$ 的价值计算公式为 $\displaystyle \sum_{i = 1} ^ k F(T, t_i) \cdot c_i$，其中 $F(T, t_i)$ 表示字符串 $t_i$ 在 $T$ 中的出现次数。举例来说，$F(\texttt{aaabaaa}, \texttt{aa}) = 4$。

你需要用 `a` 到 `n` 以内的小写字母来替换 $S$ 中的问号，每个小写字母只能替换一个位置。请求出所能得到的 $S$ 的最大价值。

## 样例 #1

### 输入

```
4
abc -10
a 1
b 1
c 3
?b?```

### 输出

```
5```

## 样例 #2

### 输入

```
2
a 1
a 1
?```

### 输出

```
2```

## 样例 #3

### 输入

```
3
a 1
b 3
ab 4
ab```

### 输出

```
8```

## 样例 #4

### 输入

```
1
a -1
?????????????```

### 输出

```
0```

## 样例 #5

### 输入

```
1
a -1
??????????????```

### 输出

```
-1```

# 题解

## 作者：AutumnKite (赞：4)

[题目传送门](https://codeforces.com/contest/1327/problem/G)

### 题解

事实上这个题还是非常简单的。（别问我为什么现场没过

首先可以对所有模式串建个 AC 自动机，每个点的权值就是这个点在 $fail$ 树上到根路径上所有点对应的字符串的权值和。

如果字符串 $s$ 已经全部确定，那么我们只要把 $s$ 在这个自动机上跑一遍，把经过节点的点权累加即可。

但是现在 $s$ 有若干个字符不确定。我们考虑对于 $s$ 的每段确定的极大子串，以及 AC 自动机上的点 $u$，预处理从 $u$ 开始，按照这段子串跑，最终跑到的点以及沿路经过的点权和。

然后我们就可以 DP 了。记 $f_{S,u}$ 表示当前问号的位置用了 $S$ 这些字符，跑到自动机上的节点 $u$ 时，最大的权值和。

转移只需要枚举下一个问号填的字符即可。

记 $n$ 为字符串 $s$ 的长度，$m$ 为模式串的长度之和，$c$ 为字符集大小，则复杂度为 $O(nm+2^cmc)$，可以通过本题。

### 代码

```cpp
const long long INF = 0x3f3f3f3f3f3f3f3fll;
const int N = 1005, C = 14;
int n;
char t[N], s[400005];
std::pair<int, long long> go[N][C + 1];
int bitcnt[1 << C];
long long f[1 << C][N];
struct AC_Automaton{
	int rt, cnt, trans[N][C], fail[N];
	long long w[N];
	int new_node(){
		int u = cnt++;
		w[u] = 0, fail[u] = -1;
		for (register int i = 0; i < C; ++i) trans[u][i] = -1;
		return u;
	}
	void init(){
		cnt = 0, rt = new_node();
	}
	void insert(const std::vector<int> &s, long long _w){
		int u = rt;
		for (register int i = 0; i < (int)s.size(); ++i){
			if (trans[u][s[i]] == -1) trans[u][s[i]] = new_node();
			u = trans[u][s[i]];
		}
		w[u] += _w;
	}
	void build(){
		std::vector<int> Q;
		fail[rt] = -1;
		for (register int i = 0; i < C; ++i)
			if (~trans[rt][i]) Q.push_back(trans[rt][i]), fail[trans[rt][i]] = rt;
			else trans[rt][i] = rt;
		for (register int i = 0; i < (int)Q.size(); ++i){
			int u = Q[i];
			w[u] += w[fail[u]];
			for (register int j = 0; j < C; ++j)
				if (~trans[u][j]) Q.push_back(trans[u][j]), fail[trans[u][j]] = trans[fail[u]][j];
				else trans[u][j] = trans[fail[u]][j];
		}
	}
	std::pair<int, long long> run(int u, const std::vector<int> &s){
		long long sum = 0;
		for (register int i = 0; i < (int)s.size(); ++i)
			u = trans[u][s[i]], sum += w[u];
		return {u, sum};
	}
}A;
int main(){
#ifdef AT_HOME
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	read(n);
	A.init();
	for (register int i = 0; i < n; ++i){
		int m = reads(t), w;
		std::vector<int> tmp;
		read(w);
		for (register int j = 0; j < m; ++j) tmp.push_back(t[j] - 'a');
		A.insert(tmp, w);
	}
	A.build();
	int len = reads(s);
	std::vector<int> tmp;
	int cnt = 0;
	for (register int i = 0; i <= len; ++i)
		if (i == len || s[i] == '?'){
			for (register int j = 0; j < A.cnt; ++j)
				go[j][cnt] = A.run(j, tmp);
			tmp.clear(), ++cnt;
		}
		else tmp.push_back(s[i] - 'a');
	bitcnt[0] = 0;
	for (register int i = 1; i < (1 << C); ++i)
		bitcnt[i] = bitcnt[i >> 1] + (i & 1);
	for (register int i = 0; i < (1 << C); ++i)
		for (register int j = 0; j < A.cnt; ++j)
			f[i][j] = -INF;
	f[0][go[A.rt][0].first] = go[A.rt][0].second;
	long long ans = -INF;
	for (register int S = 0; S < (1 << C); ++S){
		int k = bitcnt[S] + 1;
		if (k == cnt){
			for (register int u = 0; u < A.cnt; ++u)
				ans = std::max(ans, f[S][u]);
		}
		if (k >= cnt) continue;
		for (register int u = 0; u < A.cnt; ++u)
			if (f[S][u] != -INF){
				for (register int i = 0; i < C; ++i)
					if (!(S >> i & 1)){
						int v = A.trans[u][i];
						int S_ = S | (1 << i), u_ = go[v][k].first;
						f[S_][u_] = std::max(f[S_][u_], f[S][u] + A.w[v] + go[v][k].second);
					}
			}
	}
	print(ans);
}
```

我还是太菜了 /kk


---

## 作者：AlanSP (赞：2)


[**题意**](https://www.luogu.com.cn/problem/CF1327G)


AC自动机好题。

考虑不带问号的情况。

问题转化为给定确定的串S，在字符串集合中的价值最大化。

我们可以对集合T建立AC自动机。

注意到自动机的节点数不超过1000个，所以我们可以在每个节点上跑一遍串。

即统计每个节点作为S开始所得到的价值，最后取max即可。

---

带问号的情况，可以看作问号把串S分成最多15段。可以将每一段用栈提取出来。

每个子段都可以用上面的方法统计最大价值，复杂度  $O(|S|*k)$。

记 $g[i][j]$ **表示从i号节点开始，第j个子段的最大价值。**

同时记录 $pos[i][j]$ **表示 $g[i][j]$ 的终止节点。**

暴力枚举问号的取值复杂度  $ O(t^{14})$，其中t表示问号的个数。

这显然无法接受。

所以可以采取在AC自动机上DP的方式。

又考虑到问号的个数不超过14个，并且不能重复，可以直接状压。

状压当前第i位的字符有没有被用过。

---

**设 $f[S][j]$ 表示当前考虑过的问号所用字符集合为S，且到达了j号节点的最大价值。**

由于我们记录了终止节点，所以考虑它能转移到哪些后继。
$$
f[S][j]=\max\{f[S_1][u]+g[u][k]\}
$$
其中 $j=pos[u][k],S=S_1\cup \{s[j]\}$，k为当前考虑的子段编号，子段标号=问号数+1。

最后达到已有的子段数时，对每个节点的f取max输出即可。

还有一些细节问题，具体见注释吧qwq。

---

### Code:

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<utility>
#include<algorithm>
using namespace std;
#define int long long
const int N=1009,INF=0x3f3f3f3f3f3f;
struct AC_auto
{
	int ch[14];
	int end,fail;
} AC[400009];
int n,m,x,ans=-INF,cnt,num,f[(1<<14)+9][N];
int stk[400009],top,g[N][18],pos[N][18];//g[i][j]表示第j个子段，从i个节点出发的最大价值,pos表示位置
char ch[400009];

inline void build(char *s,int c)
{
	int now=0,len=strlen(s+1);
	for(int i=1;i<=len;i++)
	{
		if(!AC[now].ch[s[i]-'a']) AC[now].ch[s[i]-'a']=++cnt;
		now=AC[now].ch[s[i]-'a'];
	}
	AC[now].end+=c;
}

inline void build_fail()
{
	queue<int> Q;
	for(int i=0;i<14;i++)
	{
		if(AC[0].ch[i])
			Q.push(AC[0].ch[i]);
	}
	int now=0;
	while (!Q.empty())
	{
		int u=Q.front();Q.pop();
		AC[u].end+=AC[AC[u].fail].end;
		for(int i=0;i<14;i++)
		{
			if(AC[u].ch[i])
			{
				AC[AC[u].ch[i]].fail=AC[AC[u].fail].ch[i];
				Q.push(AC[u].ch[i]);
			}
			else AC[u].ch[i]=AC[AC[u].fail].ch[i];
		}
	}
	
}

inline int calc(int u,int x)
{
	int res=0,bu=u;
	for(int i=1;i<=top;i++)
	{
		u=AC[u].ch[stk[i]];
		res+=AC[u].end;
	}
	pos[bu][x]=u;
	return res;
}

inline int get(int x)
{
	int res=0;
	while(x)
    {
   		if(x&1)
        	res++;
        x>>=1;
    }
	return res;
}

signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",ch+1);
		scanf("%lld",&x);
		build(ch,x);
	}
	build_fail();
	scanf("%s",ch+1);
	int len=strlen(ch+1);
	for(int i=1;i<=len+1;i++)
	{
		if(ch[i]=='?'||i==len+1)//注意要把所有字符考虑完整
		{
			for(int j=0;j<=cnt;j++)
				g[j][num]=calc(j,num);
			top=0;num++;
		}
		else stk[++top]=ch[i]-'a';
	}
	memset(f,-INF,sizeof f);
	ans=-INF;
	f[0][pos[0][0]]=g[0][0];
	for(int S=0;S<(1<<14);S++)
	{
		int k=get(S)+1;//为子段个数
		if(k>num) continue;
		if(k==num)
		{
			for(int i=0;i<=cnt;i++)
				ans=max(ans,f[S][i]);
			continue;
		}
		for(int i=0;i<=cnt;i++)
			for(int j=0;j<14;j++)
				if(!((1<<j)&S))
				{
					int u=AC[i].ch[j],S1=S|(1<<j),v=pos[u][k];
					f[S1][v]=max(f[S1][v],f[S][i]+AC[u].end+g[u][k]);
					//这里我并没有统计u自己的贡献。
				}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：1saunoya (赞：2)

~~憨批题，怎么我CF的时候就做不出这个题啊啊啊啊啊啊啊~~

### 题意:

给你 $k$，$k$个串 $t_i$ 以及价值 $c_i$($\sum |t_i| \leq 10^3$)，然后给你一个串 $s$($|s|\leq 4 \times 10^5$)，$s$ 中最多包含 $14$ 个 $?$，字符集是 $14$，每个 $?$ 不能取到相同字符，对于每一种填充字符的方式，求最大的$\sum F(s,t_i) \times c_i$

### sol:

~~ACAutoMaton 傻子题。~~

考虑到 AC 自动机如果把 $ed_{fa_i}$ 信息加到 $ed_i$ 上，那么 $ed_i$ 就是 $i$ 节点对应的字符串包含的所有子串的信息。
我们考虑到最多有 $14$ 个 $?$，所以这个玩意最多被分成了 $14$ 段。那么显然我们可以直接计算对于每个节点 $j$ 在第 $i$ 段会变成 AC 自动机上的哪个节点 $nxt_{j,i}$，以及计算$j$ 走过第 $i$ 段的贡献 $sum_{j,i} = \sum ed_p$，然后就可以 $dp$ 了。

```cpp
// clang-format off
// powered by c++11
// by Isaunoya
#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i=(x);i<=(y);++i)
#define Rep(i,x,y) for(register int i=(x);i>=(y);--i)
using namespace std;using db=double;using ll=long long;
using uint=unsigned int;using ull=unsigned long long;
using pii=pair<int,int>;
#define Tp template
#define fir first
#define sec second
Tp<class T>void cmax(T&x,const T&y){if(x<y)x=y;}Tp<class T>void cmin(T&x,const T&y){if(x>y)x=y;}
#define all(v) v.begin(),v.end()
#define sz(v) ((int)v.size())
#define pb emplace_back
Tp<class T>void sort(vector<T>&v){sort(all(v));}Tp<class T>void reverse(vector<T>&v){reverse(all(v));}
Tp<class T>void unique(vector<T>&v){sort(all(v)),v.erase(unique(all(v)),v.end());}inline void reverse(string&s){reverse(s.begin(),s.end());}
const int SZ=1<<23|233;
struct FILEIN{char qwq[SZ],*S=qwq,*T=qwq,ch;
#ifdef __WIN64
#define GETC getchar
#else
inline char GETC(){return(S==T)&&(T=(S=qwq)+fread(qwq,1,SZ,stdin),S==T)?EOF:*S++;}
#endif
inline FILEIN&operator>>(char&c){while(isspace(c=GETC()));return*this;}inline FILEIN&operator>>(string&s){s.clear();while(isspace(ch=GETC()));if(!~ch)return*this;s=ch;while(!isspace(ch=GETC())&&~ch)s+=ch;return*this;}
inline FILEIN&operator>>(char*str){char*cur=str;while(*cur)*cur++=0;cur=str;while(isspace(ch=GETC()));if(!~ch)return*this;*cur=ch;while(!isspace(ch=GETC())&&~ch)*++cur=ch;*++cur=0;return*this;}
Tp<class T>inline void read(T&x){bool f=0;while((ch=GETC())<48&&~ch)f^=(ch==45);x=~ch?(ch^48):0;while((ch=GETC())>47)x=x*10+(ch^48);x=f?-x:x;}
inline FILEIN&operator>>(int&x){return read(x),*this;}inline FILEIN&operator>>(ll&x){return read(x),*this;}inline FILEIN&operator>>(uint&x){return read(x),*this;}inline FILEIN&operator>>(ull&x){return read(x),*this;}
inline FILEIN&operator>>(double&x){read(x);bool f=x<0;x=f?-x:x;if(ch^'.')return*this;double d=0.1;while((ch=GETC())>47)x+=d*(ch^48),d*=.1;return x=f?-x:x,*this;}
}in;
struct FILEOUT{const static int LIMIT=1<<22;char quq[SZ],ST[233];int sz,O,pw[233];
FILEOUT(){set(7);rep(i,pw[0]=1,9)pw[i]=pw[i-1]*10;}~FILEOUT(){flush();}
inline void flush(){fwrite(quq,1,O,stdout),fflush(stdout),O=0;}
inline FILEOUT&operator<<(char c){return quq[O++]=c,*this;}inline FILEOUT&operator<<(string str){if(O>LIMIT)flush();for(char c:str)quq[O++]=c;return*this;}
inline FILEOUT&operator<<(char*str){if(O>LIMIT)flush();char*cur=str;while(*cur)quq[O++]=(*cur++);return*this;}
Tp<class T>void write(T x){if(O>LIMIT)flush();if(x<0){quq[O++]=45;x=-x;}do{ST[++sz]=x%10^48;x/=10;}while(x);while(sz)quq[O++]=ST[sz--];}
inline FILEOUT&operator<<(int x){return write(x),*this;}inline FILEOUT&operator<<(ll x){return write(x),*this;}inline FILEOUT&operator<<(uint x){return write(x),*this;}inline FILEOUT&operator<<(ull x){return write(x),*this;}
int len,lft,rig;void set(int l){len=l;}inline FILEOUT&operator<<(double x){bool f=x<0;x=f?-x:x,lft=x,rig=1.*(x-lft)*pw[len];return write(f?-lft:lft),quq[O++]='.',write(rig),*this;}
}out;
#define int long long
struct Math{
vector<int>fac,inv;int mod;
void set(int n,int Mod){fac.resize(n+1),inv.resize(n+1),mod=Mod;rep(i,fac[0]=1,n)fac[i]=fac[i-1]*i%mod;inv[n]=qpow(fac[n],mod-2);Rep(i,n-1,0)inv[i]=inv[i+1]*(i+1)%mod;}
int qpow(int x,int y){int ans=1;for(;y;y>>=1,x=x*x%mod)if(y&1)ans=ans*x%mod;return ans;}int C(int n,int m){if(n<0||m<0||n<m)return 0;return fac[n]*inv[m]%mod*inv[n-m]%mod;}
int gcd(int x,int y){return!y?x:gcd(y,x%y);}int lcm(int x,int y){return x*y/gcd(x,y);}
}math;
// clang-format on

const int maxn = 1e3 + 31;
const int maxm = 4e5 + 54;
char t[maxn];
char s[maxm];
int ans = -1e18;
struct acautomaton {
  int cnt;
  int ch[maxn][14], fail[maxn], ed[maxn];
  acautomaton() { cnt = 1; }

  void ins(char* s, int val) {
    char* cur = s;
    int p = 1;
    while (*cur) {
      int c = (*cur++) - 'a';
      if (!ch[p][c]) ch[p][c] = ++cnt;
      p = ch[p][c];
    }
    ed[p] += val;
  }

  void build() {
    queue<int> q;
    rep(i, 0, 13) if (ch[1][i]) fail[ch[1][i]] = 1, q.push(ch[1][i]);
    else ch[1][i] = 1;
    while (q.size()) {
      int u = q.front();
      q.pop();
      rep(i, 0, 13) {
        if (ch[u][i]) {
          fail[ch[u][i]] = ch[fail[u]][i];
          ed[ch[u][i]] += ed[fail[ch[u][i]]];
          q.push(ch[u][i]);
        } else {
          ch[u][i] = ch[fail[u]][i];
        }
      }
    }
  }

  int pos[16], tot = 0;
  int nxt[maxn][16], sum[maxn][16];
  int dp[maxn][1 << 14 | 233];

  void solve(char* s) {
    int len = strlen(s);
    for (int i = 0; i < len; i++)
      if (s[i] == '?') pos[++tot] = i;
    pos[0] = -1;
    pos[tot + 1] = len;
    rep(i, 0, tot) {
      rep(j, 1, cnt) {
        int p = j;
        rep(k, pos[i] + 1, pos[i + 1] - 1) {
          p = ch[p][s[k] - 'a'];
          sum[j][i] += ed[p];
        }
        nxt[j][i] = p;
      }
    }

    rep(i, 1, cnt) rep(j, 0, (1 << 14)) dp[i][j] = -1e18;
    dp[nxt[1][0]][0] = sum[1][0];

    auto count = [&](int x) {
      int c = 0;
      while (x) x ^= x & -x, c++;
      return c;
    };

    rep(i, 0, (1 << 14) - 1) {
      int v = count(i);
      if (v >= tot) continue;
      rep(j, 1, cnt) {
        rep(k, 0, 13) {
          if (i & (1 << k)) continue;
          cmax(dp[nxt[ch[j][k]][v + 1]][i ^ (1 << k)], dp[j][i] + sum[ch[j][k]][v + 1] + ed[ch[j][k]]);
        }
      }
    }

    rep(i, 0, (1 << 14) - 1) {
      if (count(i) ^ tot) continue;
      rep(j, 1, cnt) cmax(ans, dp[j][i]);
    }
  }
} acam;

signed main() {
  // code begin.
  int _;
  in >> _;
  while (_--) {
    int val;
    in >> t >> val, acam.ins(t, val);
  }
  acam.build(), in >> s, acam.solve(s);
  out << ans << '\n';
  return 0;
  // code end.
}
```

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
你有一个字符串 $S$ 和一个字符串数组 $[t_1, t_2, \ldots, t_k]$.  
串 $t_i$ 仅包含 $a$ 和 $n$ 的小写字母；$S$ 中仅包含 $a$ 到 $n$ 以内的小写字母和不超过 $14$ 个问号.

每一个字符串 $t_i$ 有一个整数花费 $c_i$.一个字符串 $T$ 的价值计算公式为 $\displaystyle \sum_{i = 1} ^ k F(T, t_i) \cdot c_i$，其中 $F(T, t_i)$   
表示字符串 $t_i$ 在 $T$ 中的出现次数。举例来说，$F(\texttt{aaabaaa}, \texttt{aa}) = 4$.

你需要用 $a$ 到 $n$ 以内的小写字母来替换 $S$ 中的问号，每个小写字母只能替换一个位置。请求出所能得到的 $S$ 的最大价值.
## $\text{Solution}$
不难想到 AC 自动机.  
设计 $dp_{s,i}$ 表示字母选取状态为 $s$ ，在自动机跑到 $i$ 结点，的最大价值.  
由于问号极其稀疏，预处理出每个结点 $x$ 从上一个问号到下一个问号在 AC 自动机上走到的位置和获得的价值，直接转移即可.  
时间复杂度 $O(14\times 2^{14}\sum|s|)$.

---

## 作者：NaCN (赞：0)


给$t$个总长度不超过$T$的字符串$t$，每个字符串有对应的代价$c_i$

给一个$S$,里面包含$k$个问号$?$，不重复地填$a-l，14$个字符，问最后形成的字符串大价值=$\sum (t)出现的次数*c_i$

$k\leq 14,T\leq 10^3,S\leq 4\times10^5$
<!--more-->
如果都是完整的直接$AC$自动机跑步一遍就好了。考虑到不重复,用$2^{14}$当每个字符产生的状态。

$dp[i][j][mask]$搜到$s[i]$,在$AC$自动机第$k$个结点,字符使用状态$mask$。显然复杂度很高。
+ 考虑没有问号的时候，$mask$不改变，枚举所有$j$在$AC$自动机,就可不用转移$mask$。
+ 转移$mask$的时候只转移二进制数量=之前问号数量

这样复杂度就变成$O(T\times S+k\times T\times(C_{k}^0+C_{k}^1+...C_{k}^{k-1}))=O(k2^{k}T+TS)$
<details>
  <summary>代码</summary>

```c++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
const int N = 2e3 + 10;
const int mod = 1e9 + 7;
const int M = 1 << 14;
const int _M = 4e5 + 10;
const ll inf = 1e18;
const int N_AC = 2e3, M_AC = 14;
struct AC
{
    int ch[M_AC], fail;
} tri[N_AC];
ll val[N_AC];
int tcnt, root;
int creat()
{
    val[++tcnt] = 0;
    tri[tcnt].fail = 0;
    memset(tri[tcnt].ch, 0, sizeof(tri[tcnt].ch));
    return tcnt;
}

void insert(char *t, ll w)
{
    int tmp = root;
    int len = strlen(t);
    for (int i = 0; i < len; i++)
    {
        int k = t[i] - 'a';
        if (!tri[tmp].ch[k])
            tri[tmp].ch[k] = creat();
        tmp = tri[tmp].ch[k];
    }
    val[tmp] += w;
}
void get_AC()
{
    queue<int> q;
    for (int i = 0; i < M_AC; i++)
        if (tri[root].ch[i])
        {
            int k = tri[root].ch[i];
            tri[k].fail = root;
            q.push(k);
        }
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        val[x] += val[tri[x].fail];
        for (int i = 0; i < M_AC; i++)
        {
            int k = tri[x].ch[i];
            if (k)
            {
                tri[k].fail = tri[tri[x].fail].ch[i];
                q.push(k);
            }
            else
            {
                tri[x].ch[i] = tri[tri[x].fail].ch[i];
            }
        }
    }
}
int n;
char s[_M];

ll dp[N_AC][M];
int pos[N_AC];
ll w[N_AC];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        char t[N_AC];
        ll w;
        scanf("%s%lld", t, &w);
        insert(t, w);
    }
    get_AC();

    scanf("%s", s + 1);

    int len = strlen(s + 1);
    for (int i = 0; i <= tcnt; i++)
        for (int j = 0; j < M; j++)
            dp[i][j] = -inf;
    dp[0][0] = 0;
    for (int p = 0; p <= tcnt; p++)
    {
        pos[p] = p;
        w[p] = 0;
    }
    int cnt = 0;
    for (int i = 1; i <= len; i++)
    {
        // cout << "---" << endl;
        if (s[i] == '?')
        {

            for (int p = 0; p <= tcnt; p++)
                for (int j = 0; j < M; j++)
                    if (dp[p][j] != -inf && __builtin_popcount(j) == cnt)
                    {
                        //cout << p << " " << j << " " << __builtin_popcount(j) << endl;
                        for (int t = 0; t < M_AC; t++)
                            if (!(j & (1 << t)))
                            {

                                int ts = j | (1 << t);
                                int ng = tri[pos[p]].ch[t];

                                dp[ng][ts] = max(dp[ng][ts], dp[p][j] + w[p] + val[ng]);
                            }
                    }
            cnt++;
            for (int p = 0; p <= tcnt; p++)
            {
                pos[p] = p;
                w[p] = 0;
            }
        }
        else
        {
            for (int p = 0; p <= tcnt; p++)
            {
                pos[p] = tri[pos[p]].ch[s[i] - 'a'];
                w[p] += val[pos[p]];
            }
        }
    }
    ll ans = -inf;
    for (int p = 0; p <= tcnt; p++)
        for (int j = 0; j < M; j++)
            if (dp[p][j] != -inf && __builtin_popcount(j) == cnt)
                ans = max(ans, dp[p][j] + w[p]);

    printf("%lld\n", ans);
}
```
</details>
 


---

## 作者：一扶苏一 (赞：0)

## 【AC 自动机，DP】CF1327G Letters and Question Marks

### Analysis

对所有的 $t$ 建出 AC 自动机，考虑 $s$ 的某一位匹配到自动机上某个节点 $u$ 时，这一位产生的贡献就是 $u$ 在 fail 树上的祖先的 $c$ 值和。

考虑 DP。设 $f_{u, S}$ 是用了集合 $S$ 内的字符替换 `?`，当前匹配到了树上的节点 $u$ 的最大价值。

对于两个问号之间的字符，可以直接在自动机上转移，用 $O(|s||t|)$ 的复杂度处理出每个极长的连续字母串在自动机的每个节点上开始转移，最终会转移到哪个节点，沿途累加了多少价值。

在每个是问号的位置，枚举这一位用了什么转移即可。

时间复杂度 $O(|s||t| + 2^w |t| w)$，其中 $w$ 代表字符集大小。

### Code

```cpp
namespace Fusu {

const int maxt = 14;
const int maxh = 1005;
const int maxn = 400005;
const int maxs = (1 << maxt) + 5;
const ll INF = 0x3f3f3f3f3f3f3f3fll;

void Init();
void Calc();
void Build();


void Main() {
  Init();
  Build();
  Calc();
}

int n;
char s[maxn];

struct Node {
  ll v;
  Node *trans[maxt], *fail;
  std::vector<Node*> fson;
};
Node Mem[maxn], *pool = Mem + 1, *rot = Mem;

void Init() {
  qr(n);
  for (int i = 1, len; i <= n; ++i) {
    len = qrs(s + 1);
    auto u = rot;
    for (int j = 1, k = s[j] - 'a'; j <= len; k = s[++j] - 'a') {
      u = u->trans[k] ? u->trans[k] : (u->trans[k] = pool++);
    }
    qr(len);
    u->v += len;
  }
}

void dfs(Node *const u) {
  for (auto v : u->fson) {
    v->v += u->v;
    dfs(v);
  }
}

std::queue<Node*> Q;
void Build() {
  for (auto &v : rot->trans) if (v != nullptr) {
    v->fail = rot;
    Q.push(v);
  } else {
    v = rot;
  }
  for (Node *u, *v; !Q.empty(); Q.pop()) {
    u = Q.front(); v = u->fail;
    v->fson.push_back(u);
    for (int i = 0; i < maxt; ++i) if (u->trans[i]) {
      u->trans[i]->fail = v->trans[i];
      Q.push(u->trans[i]);
    } else {
      u->trans[i] = v->trans[i];
    }
  }
  dfs(rot);
}

std::vector<std::pair<int, int> > rng;
ll f[maxh][maxs];
std::vector<int> sta[maxt];

inline int countbit(int x) { int ret = 0; while (x) { ++ret; x &= x - 1; } return ret; }

void Calc() {
  int nn = qrs(s + 1);
  int tn = pool - Mem;
  rng.push_back({0, 0});
  int jk = 1;
  for (int i = 1; i <= nn; ++i) if (s[i] == '?') {
    rng.push_back({jk, i});
    jk = i + 1;
  }
  n = rng.size();
  int upc = (1 << 14) - 1;
  for (int i = 0; i <= upc; ++i) {
    sta[countbit(i)].push_back(i);
  }
  memset(f, -0x3f, sizeof f);
  f[0][0] = 0;
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < tn; ++j) {
      ll tv = 0;
      auto u = Mem + j;
      for (int k = rng[i].first; k < rng[i].second; ++k) {
        u = u->trans[s[k] - 'a'];
        tv += u->v;
      }
      for (auto s : sta[i - 1]) {
        for (int k = 0, ss = 1 << k; k < maxt; ss = 1 << ++k) if ((s & ss) == 0) {
          int pp = u->trans[k] - Mem;
          f[pp][s | ss] = std::max(f[pp][s | ss], f[j][s] + tv + u->trans[k]->v);
        }
      }
    }
  }
  ll ans = -INF;
  for (int i = 0; i < tn; ++i) {
    ll tv = 0;
    auto u = Mem + i;
    for (int k = jk; k <= nn; ++k) {
      u = u->trans[s[k] - 'a'];
      tv += u->v;
    }
    for (auto s : sta[n - 1]) {
      ans = std::max(ans, f[i][s] + tv);
    }
  }
  qw(ans, '\n');
}

} // namespace Fusu
```

---

