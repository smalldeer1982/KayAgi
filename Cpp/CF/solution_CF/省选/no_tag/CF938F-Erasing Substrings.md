# Erasing Substrings

## 题目描述

You are given a string $ s $ , initially consisting of $ n $ lowercase Latin letters. After that, you perform $ k $ operations with it, where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938F/c757249d7b8bdc7808476dd4f682a6142a6f6a1c.png). During $ i $ -th operation you must erase some substring of length exactly $ 2^{i-1} $ from $ s $ .

Print the lexicographically minimal string you may obtain after performing $ k $ such operations.

## 说明/提示

Possible operations in examples:

1. adcbca ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938F/5a518872d8942914aef6c33d251688a64a8d6d74.png) adcba ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938F/5a518872d8942914aef6c33d251688a64a8d6d74.png) aba;
2. abacabadabacaba ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938F/5a518872d8942914aef6c33d251688a64a8d6d74.png) abcabadabacaba ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938F/5a518872d8942914aef6c33d251688a64a8d6d74.png) aabadabacaba ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938F/5a518872d8942914aef6c33d251688a64a8d6d74.png) aabacaba.

## 样例 #1

### 输入

```
adcbca
```

### 输出

```
aba
```

## 样例 #2

### 输入

```
abacabadabacaba
```

### 输出

```
aabacaba
```

# 题解

## 作者：chenxia25 (赞：3)

**[Portal]( https://www.luogu.com.cn/problem/CF938F )**

考虑状压 DP。

我们考虑 $dp_{i,j}$ 表示到考虑到第 $i$ 个字符，第 $i$ 个字符必须选，当前还剩 bitmask $j$ 里的长度没被删除时所能剩下的字典序最小的字符串。那么不难发现，一个 $dp$ 元素的空间是 $\mathrm O(n)$ 的。然后转移的话，朴素的就考虑枚举当前第 $i$ 个字符与上一个字符的距离，这样就是四方的总复杂度，很显然吃不消。

有两个地方可以优化，一个是 $dp$ 元素的储存空间，存一个字符串的 DP 我还是真没见过；另一个是转移。

一开始想了个假的：正着不行我们倒着 DP，即考虑后缀。这样子我们只需要转移的时候看最左边字符最小的转移对象即可（？），然后最后从前往后路径还原，刚好符合字典序的贪心。事实上当时我脑子坏掉了，这个想法 sb 到家了。错误点很明显，就是显然有可能有左边字符最小且相同的两个转移对象的存在，这时候我们就要比下一位，如果还是相等就还要比下一位，如此还是要存整个串。况且细想起来，两种都是将当前要求的 DP 值拆成当前字符和去掉当前字符得到的前 / 后缀，因为当前字符固定，所以比前 / 后缀大小，本质上是一样的，本该无法优化。

正解是这样处理的：考虑到字典序的特性：如果两个转移对象，它们如果不相同，那么当前字符就没有任何比较的意义，因为两个转移对象就可以直接决定它们的大小，不像求和啥的位置靠后的贡献还能稍微贡献点力量，字典序是找到第一个不相同的地方后面就卵用没有了。所以说最终要求最小串，就得在从前往后决策的过程中每一步都要是当前最好的。于是我们 dark 以将 DP 值定义成 `bool`，表示是否可以剩下当前长度中的最优决策。

考虑转移，那么就还是依然枚举上一位的位置，其中有 `true` 是先决条件。因为不仅要前面最小，当前位也要最小。于是我们稍微改变一下 DP 顺序，在剩下串长度上面迭代，找出本层中 `true` 的最小当前位，然后所有等于最小当前位的就是真正的 `true` 了。最后路径还原显然是可以的，不过既然我们基于剩下串长度迭代了，那可以更简单地直接按顺序输出当前的最小当前位。至此，时间复杂度三方。

插一嘴晚上交那么多遍的那个错误：对于有些 $i,j$ 虽然可能的确可以剩下当前最优决策，但是它终究是构不成最终完整的串的，因为后面空间不足，这种是不能算的，不然就可能导致到后面整个 DP 数组没有一个达到最优决策的。然后又发现，空间足的也就一定足，这是确定下来的，那么我们可以直接不考虑那些空间不足的。就这说明有些时候 DP 不能只考虑当前考虑到的地方，有些后效性无伤大雅的能简单处理就处理掉了。

然后考虑如何优化转移。注意到对于每个 $i$ 的 $j$ 们，都完整地构成 $0\sim 2^{\lfloor\log_2n\rfloor}-1$，于是异常显然地可以枚举子集做到 $\mathrm O\!\left(3^{\log_2n}n\right)$，不过这样还是过不去。注意到我们每次枚举了距离，而这可能是多个单个 $2$ 的幂的混合物，我们枚举这个混合物干嘛呢？DP 想要优化当然是把阶段、状态能拆就拆啦，多拆来实现指数降多项式。于是我们可以将 DP 定义变一下，不一定要当前字符一定选了。于是每次就要么当前位选，要么枚举最后一段被删除的纯净物，这样就只需要枚举纯净物，就把复杂度降下来了。

复杂度平方对数，常数小跑得飞快。

（我咋写了这么长啊？？？）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=5000;
int n,m;
char a[N+5];
int dp[N+1][N+1];
int main(){
//	freopen("a.in","r",stdin);
	cin>>a+1;
	n=strlen(a+1);
	m=log2(n);
	for(int i=0;i<1<<m;i++)dp[i][i]=true;
	for(int i=1;i<=n-(1<<m)+1;i++){
		int mn=inf;
		for(int j=i;j<i+(1<<m);j++)if(dp[j-1][j-i])mn=min(mn,int(a[j]));
		for(int j=i;j<i+(1<<m);j++)dp[j][j-i]=dp[j-1][j-i]&&a[j]==mn;
		for(int j=i;j<i+(1<<m);j++)
			for(int k=0;k<m;k++)if(j-i&1<<k)
				dp[j][j-i]|=dp[j-(1<<k)][j-i^1<<k];
		putchar(mn);
	}
	return 0;
}
```



---

## 作者：GS128 (赞：1)

有一种 $O(n^2)$ 的解法。

从头以此考虑每一位能填的最小字母，设 $f_{i,j}$ 表示考虑到答案第 $i$ 位，使用过的操作集合为 $j$ 时能否取到字典序最小值，显然第一维能滚掉（下以 $f_i$ 表示 $f_{x,i}$）。

考虑转移，$i,j$ 两维能唯一确认当前位置字符，我们枚举操作集 $S$，$f_{i,S}=1$ 当且仅当 $\exists x$，$f_{i-1,x}=1$，$x$ 为 $S$ 的子集。

现在主要问题是如何快速得到是否存在 $x$ 满足（可以取到字典序最小）条件。我们设 $sum_i$ 表示当前 $i$ 的子集有多少满足条件，则关于 $x$ 的限制可表示为 $sum_S\not=0$。

当 $f$ 有更改时，我们直接暴力维护 $sum$，但这样同一个 $f_i$ 可能被操作多次，时间复杂度退化。

我们再开一个辅助数组 $tag$ 表示有多少次用 $i$ 更新 $sum$ 被跳过了。当 $f_i$ 由 $0$ 改为 $1$ 时，若此时 $sum_i\not=0$ 则说明此时 $i$ 能产生更新的集合都已经合法了，这次更新不会有实质作用，跳过，$tag_i+1$。

当 $f_i$ 由 $1$ 改为 $0$ 时，若 $tag_i\not=0$ 则 $tag_i-1$，跳过此次更新。若在更新过程中使某 $f_j$ 减至 $0$，需用 $tag_j$ 更新 $sum$。

可以证明，对于任意集合 $i$，其最多只会更新 $sum$ 两次，时间复杂度为 $O(n^2)$。

~~代码模拟赛场上写的，有亿点丑。空行懒得删了。~~

``` cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const ll MOD=998244353;
const ll INF=0x3f3f3f3f3f3f3f3f;

inline ll read()
{
	ll res=0, f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') res=res*10+c-'0', c=getchar();
	return res*f;
}

inline ll qpow(ll x,ll y)
{
	ll res=1;
	while(y)
	{
		if(y&1) res=(res*x)%MOD;
		y>>=1;
		x=(x*x)%MOD;
	}
	return res;
}

const int N=17500;

string s;
int n, K, KK;
int ans[N];

int sum[N];
bool f[N], g[N];

int tag[N];

void init()
{
	cin>>s;
	n=s.size();
	for(int i=0;i<n;i++) s[i]-='a';
	K=1;
	while((1<<K)<=n) K++;
	K--, KK=(1<<K);
	
	return ;
}

void update(int x,int k)
{
	if(k==-1)
	{
		if(tag[x])
		{
			tag[x]--;
			return ;
		}
	}
	if(k==1&&sum[x])
	{
		tag[x]++;
		return ;
	}
	for(int i=0;i<KK;i++)
	{
		if((i&x)==x) sum[i]+=k;
		if(sum[i]==0&&tag[i])
		{
			update(i,tag[i]);
			tag[i]=0;
		}
	}
	return ;
}

void solve()
{
	update(0,1);
	f[0]=1;
	
	int ppp=n-(1<<K)+1;
	int now;
	
	vector<int> t;
	
	for(int i=0;i<ppp;i++)
	{
		for(int j=0;j<KK;j++) g[j]=0;
		t.clear();
		now=26;
		
		for(int j=0;j<KK;j++)
		{
			if(sum[j])
			{
				if(s[i+j]<now)
				{
					now=s[i+j];
					t.clear();
					t.push_back(j);
				}
				else if(s[i+j]==now) t.push_back(j);
			}
		}
		
		for(int j=0;j<t.size();j++) g[t[j]]=1;
		
		ans[i]=now;
		
		for(int j=0;j<KK;j++)
		{
			if(f[j]&&!g[j]) update(j,-1);
			if(g[j]&&!f[j]) update(j,1);
			f[j]=g[j];
		}
	}
	
	for(int i=0;i<ppp;i++) putchar(ans[i]+'a');
	return ;
}

int main()
{
	init();
	solve();
	
	return 0;
}
```

---

## 作者：Graphcity (赞：1)

首先删除的子串位置一定不重叠，如果有重叠则可以通过调整达到一样的效果。

设 $f_{i,j}$ 表示目前最后一个保留的字符为 $i$，共删除了 $j$ 个字符是否是一组最小字典序方案。

注意到任意一个数都能唯一地被二进制所表示，所以 $f_{i,j}$ 同样还体现了「每次删的长度分别是什么」和「共保留了多少字符」这两个信息。

我们按照保留的字符数量从小往大进行递推。

转移则为 $f_{i,i-k}\to f_{j,j-(k+1)}$，要求 $i-k$ 和 $j-i-1$ 与为零。最后仅保留最终字符最小的 $f$ 值。这样是 $O(n^3)$ 的，考虑优化。

发现 $(i-k)+(j-i-1)=j-(k+1)$，于是所给条件其实就是 $i-k$ 与 $j-(k+1)$ 与值为零。那我们统一进行转移，对所有保留字符数为 $k$ 的 $f$ 做超集最小值的转化（可以通过 SOS DP 实现），就可以直接转移到保留字符数为 $k+1$ 的 $f$。

输出方案很简单，传统做法是求前驱，这里可以发现每一次保留的字符都相同，可以直接输出。时间复杂度 $O(n^2\log n)$。跑的很快。

```cpp
#include<bits/stdc++.h>
#define pop(x) __builtin_popcount(x)
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=5e3;

int n,m,lim; char s[Maxn+5];
int pre[Maxn+5][Maxn+5];
bool chk[Maxn+5][Maxn+5];

int main()
{
    scanf("%s",s+1),n=strlen(s+1);
    For(i,0,20) if((1<<i)<=n) m=i; lim=(1<<m)-1;
    if(m==0) {printf("%s\n",s+1); return 0;}
    chk[0][0]=1;
    int q=n-lim; For(_,0,q-1)
    {
        int p=Maxn; static int g[Maxn+5],id[Maxn+5]; memset(g,0,sizeof(g));
        For(i,_,n) if(chk[i][i-_]) g[i-_]=1,id[i-_]=i;
        For(i,0,lim) if(g[i]) For(j,0,m-1) if(!(i&(1<<j)))
            g[i|(1<<j)]=1,id[i|(1<<j)]=id[i];
        For(i,_+1,n) if(g[i-_-1]) p=min(p,(int)s[i]);
        For(i,_+1,n) if(g[i-_-1] && s[i]==p)
            chk[i][i-_-1]=1,pre[i][i-_-1]=id[i-_-1];
    }
    int mn=Maxn,p;
    For(i,q,n) if(chk[i][i-q]) mn=min(mn,(int)s[i]);
    For(i,q,n) if(chk[i][i-q] && mn==s[i]) {p=i; break;}
    vector<char> ans;
    Rof(i,q,1) ans.push_back(s[p]),p=pre[p][p-i];
    reverse(ans.begin(),ans.end());
    for(auto i:ans) putchar(i); putchar('\n');
    return 0;
}
```

---

## 作者：TLE_Automat (赞：1)

## 一. 题意：

给定一个长度为 $n$ 的小写字母字符串，令 $k = \lfloor \log_2n \rfloor$ 。

要求进行 $k$ 次操作（从 $1$ 开始编号），第 $i$ 次操作擦除任意一个长度为 $2^{i-1}$ 的子串，然后剩下的部分连接成一个新的串。

求 $k$ 次操作结束后，留下的字典序最小的字符串。

**数据范围：** $1\le n \le 5000$ 。

## 二. 做法：

一些小吐槽：神仙喵喵题。

### 1. 暴力：

注意到我们只有 $2^0 , 2^1 , 2^2 , \cdots , 2^{k-1}$ 这 $k$ 种删除方法，总共的删除次数是 $\log_2 n $ 的级别，所以我们有一个显然的状压 $\text{dp}$ 。

设 $dp_{i,S}$ 表示长度 $i$ 的前缀，如果 $S$ 的第 $i$ 位是 $1$ 就删掉一段长度为 $2^{i-1}$ 的子串，所能得到的字典序最小的字符串。

转移也比较显然，枚举 $i,S$ ，然后枚举 $x$ ，表示下一次删除一个长度为 $2^x$ 的子串，这样就可以从 ```dp[i][S]``` 转移到 ```dp[i+1][S|(1<<x)]``` ，再顺便更新一下 ```dp[i+1][S]```，即可完成转移。

这样的枚举 $i$ 的复杂度是 $O(n)$ ，枚举 $S$ 的时间复杂度是 $O(2^{\log n }) = O(n)$ ，枚举 $x$ 的时间复杂度是 $O(\log n)$ ，但我们更新 $\text{dp}$ 数组的时候还需要 $O(n)$ 比较字符串的字典序大小，这样的总时间复杂度是 $O(n^3\log n)$ ，空间复杂度也高到了 $O(n^3)$ ，时空复杂度都无法承受。

### 2. 在暴力的基础上的一些观察：

我们发现这个暴力 $\text{dp}$ 非常难受，因为 $\text{dp}$ 的一个元素里存了整整一个字符串，这直接让我们的时空复杂度都增加了一个 $O(n)$ ，我们考虑如何减少 $\text{dp}$ 中存的信息。

考虑 $\text{dp}_{x_1 , S_1}$ 和 $\text{dp}_{x_2 , S_2}$  ，令 $len_1$ 表示 $S_1$ 中所表示的删除的总长度，$len2$ 表示 $S_2$ 中所表示的删除的总长度，我们发现如果 $x_1-len_1 = x_2-len_2$ 并且 $\text{dp}_{x_1 , S_1} < \text{dp}_{x_2 , S_2}$（注意 $\text{dp}$ 中存的是一个字符串），这说明 $\text{dp}_{x_2 , S_2}$ 转移的后继状态肯定更劣，因为它前面的字典序已经比 $\text{dp}_{x_1,S_1}$ 更大了，所以这个状态存的字符串就没什么意义了。

### 3. 在观察基础上得到的正解：

根据以上观察，假设我们已经有了**答案字符串** $t$ ，我们发现若只有满足 $\text{dp}_{x,S} = t[1\cdots x-len]$ 的 $\text{dp}$ 状态才有用（$len$ 的意义如 ```2.``` 中所述）。

所以我们改一下 $\text{dp}$ 状态，把 $\text{dp}_{x,S}$ 改成能否等于 $t[1\cdots x-len]$ 的 $\text{bool}$ 值，这样我们可以进行一个贪心，假设我们确定了前 $i-1$ 个位置为最优解，当前要确定第 $i$ 个位置的字符，那么直接把能转移到这个状态的且 $\text{dp}$ 值为 $1$ 的位置进行更新即可。







---

## 作者：foreverlasting (赞：1)

[同步发表在我的博客里哦](https://foreverlasting1202.github.io/)

动态规划。

这题还是比较容易想到的。考虑到删除的先后顺序没有差别，那我们就考虑状压。$dp[i][S]$表示剩下$i$个字符，删除长度的状态为$S$（即删除了哪些长度）是否合法。然后每次枚举要删除哪个长度就可以了。

code:
```cpp
//2019.2.24 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int N=5e3+10;
namespace MAIN{
    char str[N];
    bool dp[N];
    int n,s;
    inline void MAIN(){
        scanf("%s",str+1),n=strlen(str+1),s=log2(n);
        memset(dp,1,sizeof(dp));
        for(res i=1,len=n-(1<<s)+1;i<=len;i++){
            char ch='z';
            for(res S=0;S<(1<<s);S++)
                if(dp[S])for(res k=0;k<s;k++)dp[S|(1<<k)]=1;
            for(res S=0;S<(1<<s);S++)if(dp[S])ch=min(ch,str[i+S]);
            for(res S=0;S<(1<<s);S++)dp[S]&=(str[i+S]==ch);
            putchar(ch);
        }
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：piggy123 (赞：0)

现有题解有些不牛，写点显而易见的做法。

对于字典序最优化问题，我们考虑逐位贪心。具体地，我们肯定是先最小化第一位，然后在确定第一位的前提下最小化第二位，以此类推。

我们考虑一个删除序列怎样是合法的：所有被删除的段长度或起来是全集，并且两两与起来无交。必要性显然，充分性显然包含不优于分离。

这也告诉我们，$dp_{i,j}$ 表示以 $j$ 结尾，当前匹配到第 $i$ 位是否可行，我们就已经知道了当前长度或起来为 $S=j-i$，所以我们就不需要额外状压 $S$ 了。转移可以枚举新的 $j'$，算出新的 $S'=j'-i'$，我们注意到一个 $S$ 能够转移到 $S'$ 当且仅当 $S$ 是 $S'$ 的子集。直接高位前缀和优化即可。

复杂度 $\Theta(n^2\log n)$。

---

## 作者：daniEl_lElE (赞：0)

考虑 $dp_{i,j}$ 表示考虑 $[1,i]$ 子串，在其中删去了总长为 $j$ 的子串时，$dp_{i,j}$ 在所有长度为 $i-j$ 的 $dp_{x,x-(i-j)}$ 中是第几小的。

考虑按照 $(i-j)$ 逐层转移，有两种转移方式：

* 不影响 $(i-j)$，若 $2^k\operatorname{and}j=0$，转移到 $dp_{i+2^k,j+2^k}$。
* 将 $(i-j)$ 增加 $1$，转移到 $dp_{i+1,j}$。

将第二类的所有 $dp_{i+1,j}$ 放在一起类似 SA 转移即可。

对于每个位置记录一个前序状态（$i,j$ 同时减 $2^k$ 或 $i$ 减去 $1$），方便输出答案。

总复杂度 $O(n^2(\log n+|\Sigma|))$，常数很小，可以通过。

```cpp
#include <bits/stdc++.h>
using namespace std;
int frm[5005][5005],dp[5005][5005];
pair<int,int> tmp[5005];
vector<int> vc[5005][26];
signed main(){
	string s; cin>>s; int n=s.size(); s=" "+s;
	int t=1,k=0;
	while(t*2<=n) t*=2,k++;
	for(int i=0;i<(1<<k);i++){
		frm[i][i]=-2;
		dp[i][i]=1;
	}
	for(int diff=1;diff<=n-(1<<k)+1;diff++){
		for(int i=diff,j=0;j<(1<<k);i++,j++){
			tmp[i]=make_pair(dp[i-1][j],s[i]-'a');
			frm[i][j]=-1; 
			for(int l=0;l<k;l++) if((j>>l)&1) if(tmp[i-(1<<l)]<tmp[i]) tmp[i]=min(tmp[i],tmp[i-(1<<l)]),frm[i][j]=(1<<l);
			vc[tmp[i].first][tmp[i].second].push_back(i);
		}
		int cnt=0;
		for(int i=1;i<=(1<<k);i++){
			for(int j=0;j<26;j++){
				if(vc[i][j].size()) cnt++;
				for(auto v:vc[i][j]){
					dp[v][v-diff]=cnt;
				}
			}
		}
		for(int i=diff,j=0;j<(1<<k);i++,j++){
//			cout<<dp[i][j]<<" ";
			vc[tmp[i].first][tmp[i].second].clear();
		}
//		cout<<"\n";
	}
	int nowx=n,nowy=(1<<k)-1;
	vector<char> tmp;
	while(frm[nowx][nowy]!=-2){
		if(frm[nowx][nowy]==-1){
			tmp.push_back(s[nowx]);
			nowx--;
		}
		else{
			int tp=frm[nowx][nowy];
			nowx-=tp,nowy-=tp;
		}
	}
	reverse(tmp.begin(),tmp.end());
	for(auto v:tmp) cout<<v; 
	return 0;
}
```

---

## 作者：_Cheems (赞：0)

首先删去的长度不相交，否则一定可以拆成不相交的。

然后有暴力，$f_{i,j}$ 表示前缀 $i$ 删去集合为 $j$ 时，最小字典序（存一个串）。没啥好说的，就注意 $j$ 恰好是当前删去元素个数。复杂度 $O(n^4)$。

考虑优化。看到字典序，就能想到一定要让其前缀尽可能小。于是对于所有长度相同的答案串，只保留字典序最小的即可。

现在 $f$ 只可能是字典序最小或者空串。干脆用 `bool` 表示，$=1$ 表示取到最小。

然后理所应当地更改枚举顺序，最外层枚举答案串长度。

我们先找到当前第 $p$ 位最小可取的元素 $mi$，然后转移。直接枚举子集复杂度太高，可以拆成两部分。

具体地，先转移第 $i$ 位为 $mi$ 的 $f_{i,j}$，条件是 $f_{i-1,i-j}=1$ 且 $S_i=mi$。再考虑删去元素，即 $f_{i,j}\to f_{i+2^k,i+2^k-j}$。

复杂度 $O(n^2\log n)$。

此题的启示：对于字典序 $\rm dp$，可考虑贪心地使每一位最小，从而缩小状态、优化转移。
#### 代码
注意代码实现中，不仅需保证每一位取得最小，还需使其有解。

如何判断呢？设当前删去元素集合为 $A$，总集为 $S$，则 $A\le S$ 时，必有 $A$ 和 $S-A$ 的与值为 $0$，即它们不会删去同一种 $2^k$。

换句话说，满足 $A\le S$ 就有解，写代码时加入这句话即可。

码量极其友好。
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 5e3 + 5;
int n, m, M;
char c[N];
bool f[N][N];

signed main(){
	scanf("%s", c + 1), n = strlen(c + 1), m = log2(n), M = (1 << m) - 1;
	for(int i = 0; i <= n; ++i) f[i][i] = true;
	for(int i = 1; i <= n - M; ++i){ 
		char mi = 'z'; 
		for(int j = i - 1; j - i + 1 <= M; ++j) if(f[j][j - i + 1]) mi = min(mi, c[j + 1]); 
		for(int j = i; j - i <= M; ++j) f[j][j - i] = f[j - 1][j - i] & (c[j] == mi); 
		for(int j = i; j - i <= M; ++j)
			for(int k = 0; k < m && j + (1 << k) - i <= M; ++k)
				if(!(((j - i) >> k) & 1)) f[j + (1 << k)][j + (1 << k) - i] |= f[j][j - i];
		putchar(mi);
	}
	return 0;
}
```

---

## 作者：xuantianhao (赞：0)

# [Erasing Substrings](https://www.luogu.com.cn/problem/CF938F) 

一个神奇的想法是设 $f_{i,j}$ 表示在位置 $[1,i]$ 中，我们删去了长度为 $2^k(k\in j)$ 的一些串，所能得到的最小字典序。使用二分加哈希可以做到 $O(n^2\log^2 n)$，无法承受。

发现对于状态 $f_{i,j}$，它已经确定了 $i-j$ 位的串，因为所有 $\in j$ 的 $2^k$ 之和就是 $j$；而依据字典序的性质，只有这 $i-j$ 位所表示的字典序最小的那些状态，才会成为最终的答案。当然，前提是状态 $f_{i,j}$ 合法，即剩下的部分中可以安放下尚未被删去的串。

于是我们就可以考虑直接令 $f_{i,j}$ 表示在所有长度为 $i-j$ 的串中，它是否是字典序最小的串之一；然后，就可以按照 $i-j$ 递增的顺序进行 DP。你自然可以倒着复原出路径，但是更好的方法是在 DP 第 $i-j$ 位的时候，当我们找出了这位最小能填入什么字符后，直接输出。

下面我们考虑转移。一种情况是 $f_{i,j}\rightarrow f_{i+1,j}$ ，此时是第 $i+1$ 位被保留下来，因此这个转移的前提是第 $i+1$ 位上可以填入最小的字符；

还有一种情况就是第 $i+1$ 位被删去，于是我们枚举 $k\notin j$，直接转移即可。

注意到代码实现与此处描述有一些区别，描述中的递推式是刷表法，而代码中的递推式是填表法；同时，代码中的 DP 顺序上文已经提到，$i-j$ 递增的顺序。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e3+100;
int n,m,all;
bool f[N][N];
char s[N];
int main(){
    scanf("%s",s+1);
	n=strlen(s+1);
    while((2<<m)<=n) m++;
	all=(1<<m);
    for(int i=0;i<all;i++) f[i][i]=1;
    for(int i=1;i<=n-all+1;i++){
        char lim=127;
        for(int j=i;j<i+all;j++) if(f[j-1][j-i]) lim=min(lim,s[j]);
        putchar(lim);
        for(int j=i;j<i+all;j++) f[j][j-i]=(f[j-1][j-i]&&(s[j]==lim));
        for(int j=i;j<i+all;j++){
			for(int k=0;k<m;k++){
				if((j-i)&(1<<k)) f[j][j-i]|=f[j-(1<<k)][j-i-(1<<k)];
			}
		}
    }
    return 0;
} 
```

---

