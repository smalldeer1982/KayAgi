# [ABC320G] Slot Strategy 2 (Hard)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc320/tasks/abc320_g

> この問題は C 問題の強化版です。リールの個数が $ 3 $ 個から $ N $ 個になり、$ M $ の上限が大きくなっています。

$ N $ 個のリールからなるスロットがあります。  
$ i $ 番目のリールの配列は文字列 $ S_i $ によって表されます。ここで、$ S_i $ は数字のみからなる長さ $ M $ の文字列です。

それぞれのリールには対応するボタンがついています。高橋君は各非負整数 $ t $ について、スロットが回り始めてからちょうど $ t $ 秒後にボタンを $ 1 $ つ選んで押す、または何もしないことができます。  
スロットが回り始めてから $ t $ 秒後に $ i $ 番目のリールに対応するボタンを押すと、$ i $ 番目のリールは $ S_i $ の $ (t\ \bmod\ M)+1 $ 文字目を表示して止まります。  
ただし、$ t\ \bmod\ M $ で $ t $ を $ M $ で割ったあまりを表します。

高橋君は全てのリールを止めた上で、表示されている文字が全て同じであるようにしたいです。  
高橋君が目標を達成できるように全てのリールを止めるまでに、スロットが回り始めてから最小で何秒かかるかを求めてください。  
そのようなことが不可能であればそのことを報告してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ M\ \leq\ 10^5 $
- $ N,M $ は整数
- $ S_i $ は数字のみからなる長さ $ M $ の文字列

### Sample Explanation 1

高橋君は次のようにそれぞれのリールを止めることでスロットが回り始めてから $ 6 $ 秒後にリールに表示される文字を `8` で揃えることができます。 - スロットの回転開始から $ 0 $ 秒後に $ 2 $ 番目のリールに対応するボタンを押します。$ 2 $ 番目のリールは $ S_2 $ の $ (0\ \bmod\ 10)+1=1 $ 文字目である `8` を表示して止まります。 - スロットの回転開始から $ 2 $ 秒後に $ 3 $ 番目のリールに対応するボタンを押します。$ 3 $ 番目のリールは $ S_3 $ の $ (2\ \bmod\ 10)+1=3 $ 文字目である `8` を表示して止まります。 - スロットの回転開始から $ 6 $ 秒後に $ 1 $ 番目のリールに対応するボタンを押します。$ 1 $ 番目のリールは $ S_1 $ の $ (6\ \bmod\ 10)+1=7 $ 文字目である `8` を表示して止まります。 $ 5 $ 秒以下で全てのリールに表示されている文字を揃える方法はないため、$ 6 $ を出力します。

### Sample Explanation 2

全てのリールを止めた上で、表示されている文字を揃える必要がある事に注意してください。

### Sample Explanation 3

表示されている文字が全て同じであるようにリールを止めることはできません。 このとき `-1` を出力してください。

## 样例 #1

### 输入

```
3 10
1937458062
8124690357
2385760149```

### 输出

```
6```

## 样例 #2

### 输入

```
10 20
01234567890123456789
01234567890123456789
01234567890123456789
01234567890123456789
01234567890123456789
01234567890123456789
01234567890123456789
01234567890123456789
01234567890123456789
01234567890123456789```

### 输出

```
90```

## 样例 #3

### 输入

```
5 10
0000000000
1111111111
2222222222
3333333333
4444444444```

### 输出

```
-1```

## 样例 #4

### 输入

```
10 20
14159265358979323846
26433832795028841971
69399375105820974944
59230781640628620899
86280348253421170679
82148086513282306647
09384460955058223172
53594081284811174502
84102701938521105559
64462294895493038196```

### 输出

```
11```

# 题解

## 作者：sunzz3183 (赞：4)

# [ABC320G] Slot Strategy 2 (Hard)题解

## 题意

有 $n$ 个长度为 $m$ 的数字字符串，对于一个时刻 $t$，你可以什么也不做，也可以选择一个没有被选择过的字符串，然后使他暂停在第 $(t\bmod M)+1$ 个字符。现在希望所有字符串选择的字符相同，问最大的 $t$ 是多少。

$1\leq N\leq 100,1\leq M\leq 10^5,S_i\in \{0,1,\dots,9\}$

## 分析

首先枚举最后相同的字符是啥，设为 $num$。

然后每个字符串只会对应一个时刻，同样，每个时刻只会对应一个字符串，所以我们可以把字符串放左边，时刻放右边，然后二分图最大匹配。

至于最大的 $t$ 可以通过二分来缩减右边时刻的点每次二分图。

由于右边的点实际上很少，所以先把边都统计上，每种状态最多 $n$ 条边，所以二分图匹配是 $O(n^3)$ 级别的。然后标记和匹配数组直接用 `map` 维护，$size$ 最多为 $n$，$log$ 一下就是常数级的。

时间复杂度 $O(num\times n^3\log_2(nm))$。~~什么，还是太高？别忘了这是 `ATcoder`。~~

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    char ch=getchar();int x=0;bool f=1;
    while(ch<'0'||'9'<ch){if(ch=='-')f=0;ch=getchar();}
    while('0'<=ch&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return f?x:-x;
}
const int N=102,M=1e5+2,inf=0x3f3f3f3f;
int n,m,ans=inf,a[N];
char s[M];
vector<int>v[10][N];
map<int,bool>use;
map<int,int>match;
bool dfs(int u,int num,int maxa){
    for(int t:v[num][u])
        for(int r=t;r<=maxa;r+=m)
            if(use.find(r)==use.end()){
                use[r]=1;
                if(match.find(r)==match.end()||dfs(match[r],num,maxa)){
                    match[r]=u;
                    return 1;
                }
            }
    return 0;
}
bool check(int num,int maxa){
    int sum=0;
    match.clear();
    for(int i=1;i<=n;i++){
        use.clear();
        if(dfs(i,num,maxa))sum++;
    }
    return sum==n;
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    n=read();m=read();
    for(int i=1;i<=n;i++){
        scanf("%s",s);
        for(int j=0;j<m;j++)
            if(v[s[j]-'0'][i].size()<n)
                v[s[j]-'0'][i].push_back(j);
    }
    for(int num=0;num<10;num++){
        int l=0,r=n*m,res=n*m;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(num,mid))r=mid-1,res=mid;
            else l=mid+1;
        }
        if(check(num,res))ans=min(ans,res);
    }
    printf("%lld\n",ans==inf?-1:ans);
    return 0;
}
```


---

## 作者：iiiiiyang (赞：3)

[神秘的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17708856.html)

[题目链接](https://www.luogu.com.cn/problem/AT_abc320_g)

首先枚举要使得机子都呈现一个数字 $d$，单独考虑。将问题抽象为二分图匹配，对于每台机子它有若干个时刻可以呈现数字 $d$，将机子视为左部点，时刻视为右部点，合法的充要条件是 $n$ 个机子都能匹配到一个时刻，即最大匹配数为 $n$。记 $f_{d,i}$ 表示数字 $d$ 在第 $i$ 个串中出现的位置集合，那么根据鸽巢原理，$\sum_{i = 1}^n {|f_{d,i}|} \leq n$，更多的位置实际上是没有用的，可以直接舍掉。对于时刻集合大小不足 $n$ 的情况，需要对已有集合内元素增加 $m$ 的时间将集合补到 $n$。事实上并不需要二分答案，因为有用的时刻也是只有这么 $n$ 个，可以直接存边的时候顺便记录时间集合，从小到大枚举即可，然后就是跑匈牙利，看什么时候能够合法。于是做到 $\mathcal O(dn^4)$，实际要比 $\log$ 快的。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define int long long
#define eb emplace_back
#define pb pop_back
#define ins insert
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define power(x) ((x)*(x))
using namespace std;

namespace FastIO
{
    template<typename T=int> inline T read()
    {
        T s=0,w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        return s*w;
    }
    template<typename T> inline void read(T &s)
    {
        s=0; int w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        s=s*w;
    }
    template<typename T,typename... Args> inline void read(T &x,Args &...args)
    {
        read(x),read(args...);
    }
    template<typename T> inline void write(T x,char ch)
    {
        if(x<0) x=-x,putchar('-');
        static char stk[25]; int top=0;
        do {stk[top++]=x%10+'0',x/=10;} while(x);
        while(top) putchar(stk[--top]);
        if(ch!='~') putchar(ch);
        return;
    }
}
using namespace FastIO;

namespace MTool
{   
    #define TA template<typename T,typename... Args>
    #define TT template<typename T>
    static const int Mod=998244353;
    TT inline void Swp(T &a,T &b) {T t=a;a=b;b=t;}
    TT inline void cmax(T &a,T b) {a=max(a,b);}
    TT inline void cmin(T &a,T b) {a=min(a,b);}
    TA inline void cmax(T &a,T b,Args... args) {a=max({a,b,args...});}
    TA inline void cmin(T &a,T b,Args... args) {a=min({a,b,args...});}
    TT inline void Madd(T &a,T b) {a=a+b>=Mod?a+b-Mod:a+b;}
    TT inline void Mdel(T &a,T b) {a=a-b<0?a-b+Mod:a-b;}
    TT inline void Mmul(T &a,T b) {a=a*b%Mod;}
    TT inline void Mmod(T &a) {a=(a%Mod+Mod)%Mod;}
    TT inline T Cadd(T a,T b) {return a+b>=Mod?a+b-Mod:a+b;}
    TT inline T Cdel(T a,T b) {return a-b<0?a-b+Mod:a-b;}
    TT inline T Cmul(T a,T b) {return a*b%Mod;}
    TT inline T Cmod(T a) {return (a%Mod+Mod)%Mod;}
    TA inline void Madd(T &a,T b,Args... args) {Madd(a,Cadd(b,args...));}
    TA inline void Mdel(T &a,T b,Args... args) {Mdel(a,Cadd(b,args...));}
    TA inline void Mmul(T &a,T b,Args... args) {Mmul(a,Cmul(b,args...));}
    TA inline T Cadd(T a,T b,Args... args) {return Cadd(Cadd(a,b),args...);}
    TA inline T Cdel(T a,T b,Args... args) {return Cdel(Cdel(a,b),args...);}
    TA inline T Cmul(T a,T b,Args... args) {return Cmul(Cmul(a,b),args...);}
    TT inline T qpow(T a,T b) {int res=1; while(b) {if(b&1) Mmul(res,a); Mmul(a,a); b>>=1;} return res;}
    TT inline T qmul(T a,T b) {int res=0; while(b) {if(b&1) Madd(res,a); Madd(a,a); b>>=1;} return res;}
    TT inline T spow(T a,T b) {int res=1; while(b) {if(b&1) res=qmul(res,a); a=qmul(a,a); b>>=1;} return res;}
    TT inline void exgcd(T A,T B,T &X,T &Y) {if(!B) return X=1,Y=0,void(); exgcd(B,A%B,Y,X),Y-=X*(A/B);}
    TT inline T Ginv(T x) {T A=0,B=0; exgcd(x,Mod,A,B); return Cmod(A);}
    #undef TT
    #undef TA
}
using namespace MTool;

inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    return;
}

bool Mbe;

namespace LgxTpre
{
    static const int MAX=100010;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    
    int n,m,ans,done,fl;
    int vis[101],match[101];
    char s[MAX];
    vector<int> F[10][101];
    map<int,vector<int>> G;
    #define siz(x) ((int)(x).size())
    
    inline void lmy_forever()
    {
    	read(n,m),ans=INF;
    	for(int i=0;i<n;++i) {scanf("%s",s); for(int j=0;j<m;++j) if(siz(F[s[j]-'0'][i])<n) F[s[j]-'0'][i].eb(j);}
		for(int d=0;d<=9;++d)
		{
			done=0,fl=0,fill(match,match+n,-1),G.clear();
			for(int i=0;i<n;++i) {if(F[d][i].empty()) {fl=1; break;} for(int j=0;j<n;++j) G[F[d][i][j%siz(F[d][i])]+j/siz(F[d][i])*m].eb(i);}
			if(fl) continue;
			for(auto [x,_]:G)
			{
				auto dfs=[&](auto dfs,int now)->bool
				{
					for(auto to:G[now]) if(!vis[to]) {vis[to]=1; if(!~match[to]||dfs(dfs,match[to])) return match[to]=now,1;}
					return 0;
				};
				fill(vis,vis+n,0),done+=dfs(dfs,x);
				if(done==n) {cmin(ans,x); break;}
			}
		}
		write(ans==INF?-1:ans,'\n');
	}
}

bool Med;

signed main()
{
//  file();
    fprintf(stderr,"%.3lf MB\n",abs(&Med-&Mbe)/1048576.0);
    int Tbe=clock();
    LgxTpre::lmy_forever();
    int Ted=clock();
    cerr<<1e3*(Ted-Tbe)/CLOCKS_PER_SEC<<" ms\n";
    return (0-0);
}
```

---

## 作者：LCat90 (赞：3)

## 题外话

在问题 C 中，我们通过枚举三行中每个字符的位置，$n^3$ 暴力地求解了答案。

而在 Hard Version 中，$3$ 被换成了 $n$。这意味着暴力的做法一定不行。需要想一种巧妙的算法。

其实之前 ABC 有过类似的题，也是矩阵操作之类的。因为变量之间各种约束，最终都转换成了二分图/网络流问题。算是一个 Trick 吧。

-----------------

## Solution

首先我们确定最终的那个数字 $d$，然后二分时间上限 $t$，接下来难点在判断。

想到这其实已经不难了。对于每一行，所有 $c$ 值为 $d$ 的在时间 $[0,t]$ 内都满足条件。而最终只需要满足一个条件即可。于是建立一个二分图，图上有两类点：每一行和时间。每一行连向满足条件的时间，但是这样可能时间点会很多。我们考虑每个点只连接 $n$ 个时间点，因为可以证明这样是符合的。于是最终的时间点数降到了 $n^2$。

最后判断能否匹配完即可。

时间复杂度为 $O(n^3d\log (nm))$。

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 2e6 + 5, M = 2e6 + 5, inf = 1e9;
int n, m, k, ans = 1e9, S, T,  d[N] = {};
int cnt = 1, head[N], nxt[M], To[M], fl[M], cost[M];
bool vis[M];
vector <int> G[1005][1005];
void add(int x, int y, int z) { 
	nxt[++cnt] = head[x], To[cnt] = y, fl[cnt] = z, head[x] = cnt;
	nxt[++cnt] = head[y], To[cnt] = x, fl[cnt] = 0, head[y] = cnt;
}
namespace Flow {
	int maxflow = 0, aug[N] = {}, fa[N] = {}, now[N]; 
	bool bfs() {
		memset(d, 0, sizeof d);
		memset(aug, 0, sizeof aug);
		memset(vis, 0, sizeof vis);
		queue <int> q;
		q.push(S);
		vis[S] = 1; aug[S] = inf, now[S] = head[S], d[S] = 1; 
		while(!q.empty()) {
			int p = q.front();
			q.pop();
			if(p == T) return 1;
			for(int i = head[p];i;i = nxt[i]) {
				int to = To[i], val = fl[i];
				if(val <= 0 or vis[to]) continue ;
				vis[to] = 1, fa[to] = i, aug[to] = min(aug[p], val);
				d[to] = d[p] + 1, now[to] = head[to];
				q.push(to);
			}
		}
		return 0;
	}
	int dinic(int x, int flow) {
		if(x == T) return flow;
		int rest = flow;
		for(int i = now[x];i and rest;i = nxt[i]) {
			now[x] = i; int to = To[i], val = fl[i];
			if(val > 0 and d[to] == d[x] + 1) {
				int c = dinic(to, min(val, rest));
				if(!c) d[to] = 0;
				fl[i] -= c;
				fl[i ^ 1] += c;
				rest -= c;
			} 
		}
		return flow - rest;
	}
	int Dinic() {
		int flow = 0; maxflow = 0;
		while(bfs()) while(flow = dinic(S, inf)) maxflow += flow;
		return maxflow;
	}
} ;
char c[105][100005]; 
bool check(int x, int dgt) {
	memset(head, -1, sizeof head); 
	map <int, int> id; id.clear();
	cnt = 1;
	S = 0; 
	for(int i = 1;i <= n; ++i) add(S, i, 1);
	int sum = 0;
	for(int i = 1;i <= n; ++i) {
		int tmp = 0;
		for(auto j : G[i][dgt]) {
			if(tmp >= n) break ;
			for(int t = j;t <= x;t += m) {
				if(tmp >= n) break ;
				tmp ++;
				if(!id[t]) id[t] = ++sum;
				add(i, n + id[t], 1); 
			}
		}
	}
//	cout << x << ' ' << dgt << " " << sum << "\n"; 
	T = n + sum + 1;	
	for(int i = 1;i <= sum; ++i) add(n + i, T, 1);
	return Flow :: Dinic() == n;
}
signed main() {
	cin >> n >> m;
	for(int i = 1;i <= n; ++i) scanf("%s", c[i] + 1);
	for(int i = 1;i <= n; ++i) 
		for(int j = 1;j <= m; ++j) G[i][c[i][j] - '0'].pb(j); 
//	for(int i = 0;i <= 9; ++i) cout << i << ' ' << check(11, i) << "\n";
	for(int i = 0;i <= 9; ++i) {
		int l = 1, r = n * m;
		while(l < r) {
			int mid = l + r >> 1;
			if(check(mid, i)) r = mid;
			else l = mid + 1;
		}
		if(!check(l, i)) continue ;
//		cout << i << " " << l << '\n';
		ans = min(ans, l);
	}
	cout << (ans == 1e9 ? -1 : ans - 1);
	return 0;
}
```

---

## 作者：SoyTony (赞：2)

考虑二分答案，区间在 $[0,nm)$，对于每个数 $d$，建左部点为 $i\in[1,n]$，右部点为 $j\in[0,mid]$ 的二分图，当第 $i$ 个轮可以在 $j$ 时刻显示 $d$ 时连边。

这样复杂度过高，注意到左部点数量较少，根据 Hall 定理，要求 $|T|\le |N_G(T)|$，那么每个左部点只连前 $n$ 条边就能保证存在完美匹配。

这样点数和边数只有 $O(n^2)$，二分直接二分右部点的一个前缀即可。

提交记录：[Submission - AtCoder](https://atcoder.jp/contests/abc320/submissions/45656108)

---

## 作者：Pekac (赞：2)

[ABC320G](https://www.luogu.com.cn/problem/AT_abc320_g)

直接做不是很好做，考虑用二分将其转化为判断可行性的问题。

发现每个字符串都会对应一个唯一的时间，每个时间最多也只对应一个字符串，这启发我们将字符串与时间连边，然后跑二分图的最大匹配。这样的总点数是 $\mathcal{O}(nm)$ 的，无法通过。但是每一种字符中只有前 $n$ 个是有用的，因为这样一定会比后面的更优。

实现时，可以先枚举最后相同的字符，用 vector 存下该字符在字符串 $i$ 中的前 $n$ 个位置，然后再跑最大匹配。如果使用匈牙利，单次的 check 显然是 $\mathcal{O}(n^3)$。

为保证程序的效率，可记录下每次 vis 数组变化的位置。而 match 数组可直接使用 umap 代替。

时间复杂度：$\mathcal{O}(|\Sigma|n^3\log n)$，其中 $|\Sigma|$ 为字符集的大小。

[评测记录](https://www.luogu.com.cn/record/125395236)

---

## 作者：Unnamed114514 (赞：1)

首先容易想到的是枚举是哪个字符。

我们令 $a$ 为周期数，$b$ 最后一个达到第 $a$ 个周期的位置是 $b$，那么答案就是 $(a-1)m+b$。

因为 $b<m$，那么显然具有优先决定性的一方是 $a$。

所以我们先二分求出 $a$，得到 $a$ 之后在这个 $a$ 基础上二分 $b$。

乍一看，这个做法的时间复杂度是 $O(\Delta n^2m\log m)$，$\Delta$ 是字符集的大小，即 $10$，似乎过不去。

于是我们有如下优化。

- 容易发现其实一个字符只有前 $n$ 个字符会造成贡献，所以 $O(m)$ 可以压缩到 $O(n^2)$。

- 最优性剪枝，通俗地说，就是新二分得到的 $\{a,b\}$ 必须严格小于原来的 $\{a,b\}$，这样可以限制二分上界。

- 然后就是对于同一个枚举的字符，图是一样的，所以只需要改边权就行了。

时间复杂度变成了 $O(\Delta n^4\log m)$，但是显然跑不满，所以过了，最慢点 595ms。

[link](https://atcoder.jp/contests/abc320/submissions/52242586)

---

## 作者：BINYU (赞：1)

## 题意

给定 $n$ 个长度为 $m$ 的字符串 $s_i$（字符集为 $0$ ~ $9$），在每一个时刻，你可以固定一个未固定的字符串，之后其他所有未固定的字符串，将向前循环移位一位，求让所有字符串固定且第一位相等的最小时刻。

## 思路

容易想到对于 $0$ ~ $9$ 分开来算，最后取 $\min$。

如果有一个字符串不包含当前数字，当前情况一定无解，下讨论有解的情况：

发现对于每一个字符串，选择一个时刻固定实质上就是“匹配一个时刻”（不能重复选择时刻，不能遗漏任何字符串）。如果把字符串抽象成一个左部点，时刻抽象成一个右部点，第 $j$ 时刻 $s_{i,1}$ 为当前数字看做左部点 $i$ 向右部点 $j$ 连一条边，当前问题就变为：求至少需要前多少个右部点，才能使当前二分图最大匹配为 $n$。

因为我们容易求一个二分图的最大匹配数，而一个二分图的最大匹配数肯定是随着右部点的增加单调非降的，所以可以考虑二分，在匹配时，只需跳过所有编号大于 $mid$ 的右部点，不去走它即可，也可以暴力重构整个图。

因为题目中的最大时刻是没有限制的，我们需要人为地定一个上限，在保证答案正确的同时尽量优化时空复杂度，考虑对于一个左部点，最坏情况是它能连得前 $n-1$ 个右部点都被匹配了，且无法移动（对于匈牙利算法），那么它只能连第 $n$ 个点，所以，对于这个问题的每一张图，共有 $n$ 个左部点，至多 $n^2$ 个右部点，$n^2$ 条边就能保证有解，二分时的上界取 $n \times m$ 即可。

最坏情况：
```
100 100000
22222....22220
11111....11110
11111....11110
11111....11110
....
```

对于每条边，我们可以先预处理出第 $i$ 个字符串前 $n$ 次 $s_{i,1}$ 为当前数字的时刻是多少，建图时离散化即可，预处理时可以先枚举当前数字，然后扫一遍整个字符串，不足 $n$ 个的情况可以通过前面的计算得到，时间复杂度是 $O(n(n+m))$，常数为 $10$

使用网络流（Dinic）跑一次二分图最大匹配时间复杂度是 $O(n^2 \sqrt n )$，匈牙利算法 $O(n^3)$，总时间复杂度为 $O(n^2 \sqrt n \log nm + nm)$ 或 $O(n^3 \log nm + nm)$，常数均为 $10$，可过。

---

## 作者：Jryno1 (赞：1)

#### 题意：

给定 $n$ 个长度为 $m$ 的字符串，其中只有 $0-9$ 的数字。从第 $0$ 个时刻开始，每个时刻可选择**一个**没有被选择过的字符串，如果一个字符串在 $T$ 时刻固定，之后这个字符串会显示第 $(T\bmod m)+1$ 个字符。求最短在第多少个时刻之前，可以让每一个字符串都显示出数字，并且显示的数字都一样，可能无解。

$n\le100$，$m\le10^5$

#### Sol：

假设固定结果数字是 $num$，问题可以转化成：每一个字符串可以在若干个时刻被固定，求最早的时刻能够把每个字符串都固定。

具体分析：“若干个时刻”范围是 $\mathcal{O}(nm)$ 的，显然最劣的情况是所有时间都叠在一起。而求最早的时刻可以考虑二分答案，之后判断是否可行即可。

这个问题显然是一个二分图匹配问题，将每个字符串看作左部点，时间点看作右部点，每次固定时间上限和数字 $num$ 之后，可以找到字符串连接的时间节点，判断这个图匹配情况即可。

然而节点数量是 $\mathcal{O}(nm)$，边数只会更多，行不通。考虑是否真的对于每个字符串都需要找到 $\mathcal{O}(nm)$ 个点。实际上不需要，因为左边只需要匹配 $n$ 个点，因此对于每个点只需要考虑连出去的前 $n$ 条边即可（因为这样可以保证可以找到一个之前没有用过的时刻点），因此实际上可以做到点数和边数都是 $\mathcal{O}(n^2)$ 级别的，之后匹配即可（代码里写的是 dinic）。

[ATcoder 提交记录](https://atcoder.jp/contests/abc320/submissions/45687178)

---

## 作者：cqbzlzm (赞：0)

### Description

有 $n$ 个转轴，每个转轴有 $m$ 转，第 $t$ 秒第 $i$ 个转轴显示第 $t\%m+1$ 转。每秒钟你可以选择**最多**一个转轴并使它停止转动，求最少多少时间可以使所有转轴都停下并且显示同样的字符。

**数据范围：**$n\leq 10^2,m\leq 10^5$。

### Solution

先枚举剩下的字符。由 "**每秒最多选择一个转轴**" 和 "**所有转轴停止转动显示同一字符**"，想到二分图的最大匹配。我们可以把所有时刻当做左部点，把转轴当做右部点，于是枚举时间进行匹配。

但是这样做时间会爆，原因在于有很多没用的时间（左部点）。我们考虑对于一个转轴来说，只有字符等于最终字符的位置有用，且这样的位置最多出现 $n$ 次转轴就会停止。

这样每个转轴会贡献 $n$ 个有用的时间点，一共 $n^2$ 个左部点， $n$ 个右部点，总复杂度 $n^3$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100, MAXM = 200000;
int n, m;
vector<int> G[MAXM + 5];
int match[MAXN + 5];
bool vis[MAXN + 5];
bool dfs(int u){
	for (int v : G[u]) {
		if (vis[v]) continue;
		vis[v] = 1;
		if (match[v] == -1 || dfs(match[v])) {
			match[v] = u;
			return 1;
		}
	}
	return 0;
}
char s[MAXN + 5][MAXM + 5];
char get(int i, int t) {
	return s[i][t % m + 1];
}
vector<int> vec[MAXN + 5][12];
int tt[MAXM + 5];
int main() {
	
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++)
    	scanf("%s", s[i] + 1);
    for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
			vec[i][s[i][j] - 48].push_back(j);

    int ans = INT_MAX;
    for (char ch = '0'; ch <= '9'; ch ++) {
    	for (int i = 0; i <= 200000; i ++)
    		vector<int>().swap(G[i]);
    	unordered_map<int, int> mp; 
    	set<int> tim;
    	bool flag = 1;
    	for (int i = 1; i <= n; i ++) {
    		if (vec[i][ch - 48].size() == 0) flag =0 ;
		}	
		if (flag == 0) continue;
		for (int i = 1; i <= n; i ++) {
    		int t = 0, p = 0;
    		while (t <= n) {
    			t += vec[i][ch - 48].size();
    			for (int v : vec[i][ch - 48]) tim.insert(p * m + v - 1); //将所有有用的时间节点存到tim中
    			p ++;
			}
		}
		
		int I = 0;
		for (int v : tim) { //给有用的时间节点编号
			I ++;
			mp[v] = I;
			tt[I] = v;
		}
		
    	for (int i = 1; i <= n; i ++) {
    		int t = 0, p = 0;
    		while (t <= n) {
    			t += vec[i][ch - 48].size();
    			for (int v : vec[i][ch - 48])
    				G[mp[p * m + v - 1]].push_back(i); //监督
    			p ++;
			}
		}
    	memset(match, -1, sizeof(match));
		int cnt = 0;
		for (int i = 1; i <= I; i ++) {
			memset(vis, 0, sizeof(vis));
	        if(dfs(i)) { //匹配
	        	cnt ++; 
	        	if (cnt == n) {
	        		ans = min(ans, tt[i]); 
	        		break;
				}
	        }
		}
	}
	if (ans == INT_MAX) ans = -1;
    printf("%d", ans);
	return 0;
}
```

---

## 作者：Drind (赞：0)

写了俩小时，有点无语。

## 题目解析

给定一个老虎机，每个时刻可以选其中一个转盘停下，问所有转盘的数字一样至少需要几个时刻。

我们先枚举最后成为的那个数字，然后发现每个转盘对应的停下时间均不一致，所以可以直接当成二分图进行匹配。

具体的，我们把每个时刻当成一个点，如果这个时刻有我们先前钦定的数字，我们就把他和这个转盘连边。然后套一个二分答案就行了。

根据 hall 定理，每个点最多只需要连 $n$ 条边，所以二分上界可以设为 $nm$。

这个二分图最多有 $n^2$ 个点和 $n^2$ 条边，单次匹配复杂度就是 $O(n^3)$。

总复杂度 $O(n^3\log \left(nm\right))$， $n$ 很小完全能过。

最大流板子省略，代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;

string s[110];
int n,m;

vector<int>a[110][11];

int vis[110];
bool check(int num,int r){
	f.init(); memset(vis,0,sizeof vis);
	
	for(int i=1;i<=n;i++) f.adde(f.s,i,1);
	unordered_map<int,int>mp; int res=n;
	for(int i=1;i<=n;i++){
		int t=0;
		for(auto j:a[i][num]){
			if(t>=n) break;
			for(int k=j;k<=r;k+=m){
				if(!mp[k]) mp[k]=++res;
				f.adde(i,mp[k],1);
				t++; if(t>=n) break;
			}
		}
	}
	
	for(int i=n+1;i<=res;i++) f.adde(i,f.t,1);
	
	int ans=f.dinic();
	if(ans==n) return true;
	else return false;
}

int pos[10][N];

inline void fake_main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	
	for(int i=1;i<=n;i++){
		for(int j=0;j<m;j++){
			a[i][s[i][j]-'0'].push_back(j+1);
		}
	}
	
	int mn=1e15;
	for(int i=0;i<=9;i++){
		int l=n,r=n*m,ans=1e15;
		
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(i,mid)){
				r=mid-1,ans=mid;
			}else l=mid+1;
		}
		
		if(ans==1e15) continue;
		mn=min(mn,ans-1);
	}
	if(mn==1e15){
		cout<<"-1\n";
	}else cout<<mn<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}

```

---

