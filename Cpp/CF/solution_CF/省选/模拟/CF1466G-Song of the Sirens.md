# Song of the Sirens

## 题目描述

Whoso in ignorance draws near to them and hears the Sirens' voice, he nevermore returns.Homer, Odyssey





In the times of Jason and the Argonauts, it was well known that sirens use the sound of their songs to lure sailors into their demise. Yet only a few knew that every time sirens call a sailor by his name, his will weakens, making him more vulnerable.

For the purpose of this problem, both siren songs and names of the sailors will be represented as strings of lowercase English letters. The more times the sailor's name occurs as a contiguous substring of the song, the greater danger he is in.

Jason found out that sirens can sing one of the $ n+1 $ songs, which have the following structure: let $ s_i $ ( $ 0 \leq i \leq n $ ) be the $ i $ -th song and $ t $ be a string of length $ n $ , then for every $ i < n $ : $ s_{i+1} = s_i t_i s_i $ . In other words $ i+1 $ -st song is the concatenation of $ i $ -th song, $ i $ -th letter ( $ 0 $ -indexed) of $ t $ and the $ i $ -th song.

Fortunately, he also knows $ s_0 $ and $ t $ . Jason wonders how many times a sailor's name is mentioned in a particular song. Answer $ q $ queries: given the sailor's name ( $ w $ ) and the index of a song ( $ i $ ) output the number of occurrences of $ w $ in $ s_i $ as a substring. As this number can be quite large, output its remainder modulo $ 10^9+7 $ .

## 说明/提示

In the first example songs of the sirens are as follows:

- Song $ 0 $ : aa
- Song $ 1 $ : aabaa
- Song $ 2 $ : aabaacaabaa
- Song $ 3 $ : aabaacaabaadaabaacaabaa

## 样例 #1

### 输入

```
3 3
aa
bcd
2 aba
3 ca
3 aa```

### 输出

```
2
2
8```

## 样例 #2

### 输入

```
4 5
aba
bbac
1 a
3 baca
3 ab
2 bab
4 aba```

### 输出

```
4
0
14
6
28```

# 题解

## 作者：zhoukangyang (赞：13)

[更好的阅读体验](https://www.cnblogs.com/zkyJuruo/p/14215618.html)

$\tt SAM$ 学傻了，看到子串，直接把 $\tt Hash$ 解决的问题用 $\tt SAM$ 做了，于是成功没调出来 $100+$ 行的代码。

让 $s_{l, r}$ 表示 $s$ 的第 $l$ 个字符到第 $r$ 个字符形成的串，$len(s)$  表示 $s$ 的字符串长度。

考虑对于一个串 $s_i$ 对 $w$ 的贡献，要么是从 $s_{i - 1}$ 中得到的，要么是从跨越 $t_i$ 的子串中得到的。

跨越 $t_i$ 的贡献就是 $s_{len(s) - len(w) + 2 , len(s)} t_i s_{1, len(w) - 1}$ 中 $w$ 出现的次数。这个可以 $hash$ 解决。

设在 $s_i$ 中跨越 $t_i$ 的贡献是 $g_i$ (特别的，在 $s_0$ 中就是整个串的贡献)，那么答案就是 $\sum\limits_{i = 0}^{d} 2^{d - i} g_i$

于是只要暴力这样做 + $hash$，就得到了一个 $\sum len(w_i) \times k_i$ 的算法。

然后考虑有很多重复的计算：如果 $s_i$ 和 $s_j$ 长度都比 $w$ 长度大，而且 $t_i = t_j$，那么他们跨越 $t_i$ 的贡献是相同的！

那么可以考虑先计算前几个 $s_i$ 对 $w$ 的贡献直到 $s_i$ 的长度大于 $w$，然后后面贡献，对于每一个字符的答案是一样的，按照最开始的哈希方法处理以下即可。

显然这个哈希也可以用 $\tt KMP$ 来代替。

代码还是很好写的。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define L(i, j, k) for(int i = (j), i##E = (k); i <= i##E; i++) 
#define R(i, j, k) for(int i = (j), i##E = (k); i >= i##E; i--) 
#define ll long long 
#define db double
#define mkp make_pair 
const int N = 2e6 + 7;
const int tN = 1e5 + 7;
const int mod = 1e9 + 7; 
const int p = 1019260817;
const int G = 19491001;
const int inv2 = (mod + 1) / 2;
int n, Q, has[N], Len, sPow[N];
void Init(string s) { Len = s.size(); L(i, 1, Len) has[i] = (has[i - 1] + 1ll * (s[i - 1] - 'a' + 1) * sPow[i] % p) % p; }
int d[tN];
string g[tN], s[23], ms, t, now;
int calc(int x) {
	int nowlen = g[x].size(), Hs = 0, res = 0;
	L(i, 1, nowlen) (Hs += 1ll * (g[x][i - 1] - 'a' + 1) * sPow[i] % p) %= p;
	L(i, 0, Len - nowlen) res += (has[i + nowlen] - has[i] + p) % p == 1ll * Hs * sPow[i] % p;
	return res;
}
int tmp, maxn;
int Pow[N], iPow[N], ans[tN];
int qz[tN][26];
int main() {
	ios::sync_with_stdio(false);
        cin.tie(0),cout.tie(0);
	cin >> n >> Q;
	cin >> s[0] >> t;
	Pow[0] = iPow[0] = sPow[0] = 1;
	L(i, 1, n) Pow[i] = Pow[i - 1] * 2 % mod, iPow[i] = 1ll * iPow[i - 1] * inv2 % mod;
	L(i, 1, 2000001) sPow[i] = 1ll * sPow[i - 1] * G % p;
	L(i, 1, Q) cin >> d[i] >> g[i], maxn = max(maxn, (int)g[i].size());
	now = s[0], Init(s[0]);
	L(i, 1, Q) (ans[i] += 1ll * Pow[d[i]] * calc(i) % mod) %= mod;
	int tmp = 0;
	while(1) {
		if((int)s[tmp].size() > maxn) break;
		L(i, 1, Q) if(d[i] > tmp) {
			ms.clear(); 
			int tlen = min((int)s[tmp].size(), (int)g[i].size() - 1);
			L(_i, (int)s[tmp].size() - tlen, (int)s[tmp].size() - 1) ms.push_back(s[tmp][_i]);
			ms.push_back(t[tmp]);
			L(_i, 0, tlen - 1) ms.push_back(s[tmp][_i]);
			Init(ms);
			(ans[i] += 1ll * Pow[d[i] - tmp - 1] % mod * calc(i) % mod) %= mod;
		}
		s[tmp + 1] = s[tmp] + t[tmp] + s[tmp], ++tmp; 
	}
	// 计算了前 tmp 位
	L(i, 1, n) {
		L(j, 0, 25) qz[i][j] = qz[i - 1][j];
		(qz[i][t[i - 1] - 'a'] += iPow[i]) %= mod;
	}
	int Len = now.size();
	L(i, 1, Q) {
		if(d[i] <= tmp) continue;
		int orz = g[i].size() - 1;
		L(j, 0, 25) { 
			ms.clear();
			L(_i, (int)s[tmp].size() - orz, (int)s[tmp].size() - 1) ms.push_back(s[tmp][_i]);
			ms.push_back(j + 'a');
			L(_i, 0, orz - 1) ms.push_back(s[tmp][_i]);
			Init(ms);
			(ans[i] += 1ll * (qz[d[i]][j] - qz[tmp][j] + mod) % mod * Pow[d[i]] % mod * calc(i) % mod) %= mod; 
		}
	}
	L(i, 1, Q) printf("%d\n", ans[i]); 
	return 0;
}
```

---

## 作者：zjjws (赞：7)

$\texttt{data-2021-01-03}$

更正式子错误，同时增加了一些细节。

---

考场上挂于 F，没看 G，说实话自己会写的题没看到真的非常可惜。

这道题并不算是难，如果说做过 CF177G 这道题的话，基本可以一眼秒。

---

**注：以下的前缀后缀均指保留水手名字的长度位。**

前面的思路是和 CF177G 一样的，考虑当 **歌** 的长度大于等于 **水手名字** 长度之后，再进行变换不会改变歌的 **前缀后缀**。

这有什么用呢？假设当前歌为 $S$，水手名字为 $N$（$|S|\ge |N|$），歌的前缀为 $S_1$，后缀为 $S_2$，中间新添加的字母为 $x$。定义 $F_S$ 表示 $S$ 串中 $N$ 的出现次数，那么有：

$$\begin{cases} F_S\to 2F_{S}+F_{S_2+x+S_1}\\ S\to S+x+S \end{cases}$$

**注：字符串加法为拼接。**

会发现 $S_1$ 和 $S_2$ 不变，每次变换就等于乘二然后加一个和 $x$ 有关的数值，而因为 $x$ 只有 $26$ 种可能，所以可以用正确的复杂度处理出来，可设函数 $g_x=F_{S_2+x+S_1}$。

然后第一次 **长度大于等于** $|N|$ 的串 $S$ 的贡献（**答案初值**） 可以 Hash 暴力计算。

我们现在以这个暴力处理出来的串当做初始的 $S_0$（第 $0$ 首歌），以便之后的式子描述。

那么假设我们现在要求的是第 $m$ 首歌（新标号）的 $F$ 值。 


然后考虑答案计算的式子，直接暴力拆开，得到的是每一项乘上一个 $2$ 的幂次的形式：

$$F_{S_0}\cdot 2^{m}+\sum_{i=1}^m g_{t_i}\cdot 2^{m-i}$$

再提取一次公因式，除 **答案初值** 以外，可以将不同的 $g_x$ 提取出来，得到这样一个东西：

$$F_{S_0}\cdot 2^{m}+(\sum_{i=a}^z g_{i} \cdot(\sum 2^{k_i}))$$

后面那个东西就是若干个 $2$ 的幂次的和，因为不太好用式子写，所以简单地表示一下。

后面这个东西依然是可以预处理的，当然预处理的是提取了一个 $2^{-p},p\in[0,n]$ 次的结果，这部分没理解可以看代码，是运用前缀和的思想，把每首歌的 **序号和贡献** 塞入 **这首歌的中间连接字母**。

代码的答案计算部分写得比较密集（指一堆函数嵌套），可能观感并不佳，不过这道题思路有了代码 ~~有手就行~~ 自己实现并非难事。

```cpp
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>
#define LL long long
using namespace std;
inline int rin()
{
    int s=0;
    bool bj=false;
    char c=getchar();
    for(;(c>'9'||c<'0')&&c!='-';c=getchar());
    if(c=='-')bj=true,c=getchar();
    for(;c>='0'&&c<='9';c=getchar())s=(s<<1)+(s<<3)+(c^'0');
    if(bj)s=-s;
    return s;
}

const int N=1e5+3;
const int S=1e6+3;
const int M=1e9+7;

inline int prpr(int x,int y){return 1LL*x*y%M;}
inline int ksm(int x,int y){int ans=1;for(;y;y>>=1){if(y&1)ans=prpr(ans,x);x=prpr(x,x);}return ans;}

int n,q;
string t;
string s[22];
inline void Read()
{
    n=rin();q=rin();
    cin>>s[0];
    cin>>t;
    return;
}

const int Mod=19260817;
const int K=37;

int sl[S<<1];
inline int Hash_add(int x,int y){return (x+y)%Mod;}
inline int Hash_prpr(int x,int y){return 1LL*x*y%Mod;}
inline int Hash_check(int *a,int l,int r){return (l>r)?(0):((a[r]-Hash_prpr(a[l-1],sl[r-l+1])+Mod)%Mod);}

int pro[N];
int inv[N];

struct gyq
{
    vector<int>num;
    vector<int>add;
    inline void push(int num_,int val_)
    {
        num.push_back(num_);
        if(add.empty())add.push_back(val_);
        else add.push_back((add.back()+val_)%M);
        return;
    }
    inline int cheak(int ed)
    {
        int l=0,r=num.size()-1;
        int ans=0;
        for(;l<=r;)
        {
            int mid=(l+r)>>1;
            if(num[mid]<=ed)ans=add[mid],l=mid+1;
            else r=mid-1;
        }
        return ans;
    }
}d[26];
inline void init()
{
    Read();
    for(int i=1;s[i-1].length()<1e6;i++)s[i]=s[i-1]+t[i-1]+s[i-1];

    sl[0]=1;
    for(int i=1;i<(S<<1);i++)sl[i]=Hash_prpr(sl[i-1],K);
    
    pro[0]=inv[0]=1;
    for(int i=1;i<=n;i++)pro[i]=prpr(pro[i-1],2);
    inv[n]=ksm(pro[n],M-2);
    for(int i=n-1;i>=1;i--)inv[i]=prpr(inv[i+1],2);

    for(int i=1;i<=n;i++)d[t[i-1]-'a'].push(i,pro[n-i]);
    return;
}

string Alpha;
int lens;
int num;
int L;

int Beta[S];
int Zeta[S<<1];
int Gamma[26];

LL ans;
inline int work()
{
    memset(Gamma,0,sizeof(Gamma));
    int i,j,k;
    num=rin();
    cin>>Alpha;
    lens=Alpha.length();
    for(i=0;s[i].length()<lens&&i<num;i++);if(s[i].length()<lens)return 0;
    for(j=1;j<=lens;j++)Beta[j]=Hash_add(Hash_prpr(Beta[j-1],K),Alpha[j-1]-'a'+1);
    for(j=1,L=s[i].length(),ans=0;j<=L;j++)
    {
        Zeta[j]=Hash_add(Hash_prpr(Zeta[j-1],K),s[i][j-1]-'a'+1);
        if(j>=lens&&Hash_check(Zeta,j-lens+1,j)==Beta[lens])ans++;
    }
    for(k=1;k<=lens;k++)Gamma[Alpha[k-1]-'a']+=(Hash_add(Hash_prpr(Hash_add(Hash_prpr(Hash_check(Zeta,L-k+2,L),K),Alpha[k-1]-'a'+1),sl[lens-k]),Zeta[lens-k])==Beta[lens]);
    ans=prpr(ans,ksm(2,num-i));
    for(k=0;k<26;k++)ans=(ans+prpr(Gamma[k],prpr(d[k].cheak(num)-d[k].cheak(i),inv[n-num])))%M;
    return (ans%M+M)%M;
}

int main()
{
    init();
    for(;q;q--)printf("%d\n",work());
    return 0;
}
```





---

## 作者：Iniaugoty (赞：4)

### [CF1466G Song of the Sirens](/problem/CF1466G)

NOIP 模拟赛 T3 出了这个的改编题，然后我把预处理的东西放进询问里做了 $q$ 遍，然后 TLE 100 挂到 40。所以我必须要写这篇题解，并且警示后人，OI 赛制大样例不一定足够大，一定要测一测极限数据下的时空。

我们先从 $\vert w \vert = 1$ 的情况考虑。

记 $f(i, ch)$ 表示 $s _ i$ 中字符 $ch$ 出现的次数。

考虑做一个递推，显然有

$$f(i + 1, ch) = \begin {cases}
2 f(i, ch) + 1 & (t _ {i + 1} = ch) \\
2 f(i, ch) & (t _ {i + 1} \neq ch)
\end{cases}$$

然后做一个拆贡献，大致是将字符挂在“分隔符”（即 $t _ i$）上计算次数，不难得到

$$f(i, ch) = 2 ^ {i} f(0, ch) + \sum _ {j = 1} ^ {i} 2 ^ {i - j} [t _ j = ch]$$

上式分为两部分，一个是字符直接出现在 $s _ 0$ 中的次数，一个是作为“分隔符”出现的次数。

对每种字符预处理一个前（后）缀和状物，可以做到 $O(n \Sigma + \sum \vert w \vert)$。

然后考虑将这个做法扩展到 $\vert w \vert > 1$ 的情况。

试着求出 $w$ 在 $s _ 0$ 中直接出现的次数，并且找到某种不重不漏的将 $w$ 挂在“分隔符”上的方法，然后就可以仿照上式求出答案。

首先钦定 $\vert s _ 0 \vert \ge \vert w \vert$。

对于前者，$w$ 在 $s _ 0$ 中的出现次数，可以直接 KMP 或者 hash 匹配出来。

对于后者，注意到 $s _ k$ 是形如 $s _ 0 t _ a s _ 0 t _ b s _ 0 t _ c s _ 0 \dots$ 的。也就是说，如果 $w$ 出现在 $s _ k$ 中并且不直接出现在 $s _ 0$ 中，应当形如 $\operatorname {suf} (s _ 0) + ch + \operatorname {pre} (s _ 0)$。其中 $\operatorname {suf} (s _ 0)$ 和 $\operatorname {pre} (s _ 0)$ 分别表示 $s _ 0$ 的一个后缀和一个前缀，$ch$ 是某个“分隔符”。

于是我们可以枚举 $w _ i$，以 $w _ i$ 为“分隔符”，判断是否合法（hash 判定子串是否相等即可）并且求出 $w _ i$ 作为“分隔符”出现的次数（仿照上面那个式子）。

那如果 $\vert s _ 0 \vert < \vert w \vert$ ，考虑暴力模拟出一个最小的 $i$ 使得 $\vert s _ i \vert \ge \vert w \vert$，然后以 $s _ i$ 为 $s _ 0$ 做上面的东西。这样的话，之前的那个前（后）缀和需要做一个类似字符串 hash 的差分。

时间复杂度依然是 $O(n \Sigma + \sum \vert w \vert)$。

注意特判 $\vert s _ k \vert < \vert w \vert$ 无解的情况，不然会 TLE #9。

[code](https://codeforces.com/contest/1466/submission/280458426)，是从模拟赛改编题改过来的，所以可能变量名和题面有点不吻合。

注意数组大小要认真开哦，不然你会喜提好几发 WA 或 TLE 或 MLE。

---

## 作者：Alex_Wei (赞：3)

> [题目传送门](https://www.luogu.com.cn/problem/CF1466G)

> 题意简述：给出 $n,s_0,t\ (n=|t|)$，定义 $s_i=s_{i-1}+t_i+s_{i-1}$。多次询问给出 $k,m$，求 $m$ 在 $s_k$ 中的出现次数。记 $L=\sum |m|$，则 $L\leq 10^6$。

[在我的 cnblogs 中查看](https://www.cnblogs.com/alex-wei/p/CF1466G.html)。

Goodbye 2020 的 G。~~我当时怎么没做出来呢？~~

---

key observation：若 $|m|\leq|s_i|$，那么答案可以分成两部分计算：
- 一部分是 $m$ 完整地出现在 $s_k$ 中的次数。那么根据 $s$ 的定义，设 $m$ 在 $s_i$ 中出现了 $f(m,s_i)$ 次，则 $m$ 在 $s_k$ 中出现了 $2^{k-i}f(m,s_i)$ 次。这一点是显然的。
- 另一部分是 $m$ 中有一个字符被 $t_{i+1},t_{i+2},\cdots,t_k$ 的某个字符匹配，剩下来的前缀出现在 $s_i$ 的后缀，后缀出现在 $s_i$ 的前缀的次数之和。考虑 $t$ 的**某个位置 $p\ (i<p\leq k)$ 上的字符** $t_p$ 在 $s_k$ 中被复制的次数**（只考虑该位置 $p$，而不考虑与 $t_p$ 相同的其它位置上的字符）**，根据 $s$ 的定义，它被复制了 $2^{k-p}$ 次。枚举 $m$ 中被匹配的位置 $j$ 和 $t[i+1:k]$ 中与 $m_j$ 匹配的位置 $p$，则贡献可以写成 $\sum_{j=1}^{|m|}\sum_{p=i+1}^k2^{k-p}[m[1:j-1]=s_i[|s_i|-j+1:|s_i|]\land m_j=t_p\land m[j+1:r]=s_i[1:r-j]]$。将其改写为 $\sum_{j=1}^{|m|}[m[1:j-1]=s_i[|s_i|-j+1:|s_i|]\land m[j+1:r]=s_i[1:r-j]]\sum_{p=i+1}^k2^{k-p}[m_j=t_p]$。注意到后面这坨东西在 $i,k$ 确定的情况下，对于相同的 $m_j$ 给出的答案是相同的。因为 $m_j$ 的取值只有 $26$ 种，那么预处理出来即可。
- 怎么预处理？注意到相同的 $t_p$ 对于不同的 $i,k$ 贡献可能不同，很讨厌。将其写为 $\dfrac{\sum_{p=i+1}^n2^{n-p}[m_j=t_p]-\sum_{p=k+1}^n2^{n-p}[m_j=t_p]}{2^{n-k}}$，那么对于每个字符 $c$，预处理出 $g(c,i)=\sum_{p=i+1}^n2^{n-p}[t_p=c]$ 与 $2$ 的幂的逆元，就可以 $\mathcal{O}(1)$ 计算上式（$\dfrac{g(m_j,i+1)-g(m_j,k+1)}{2^{n-k}}$）。即对于每个字符 $c$ 和字符串编号 $i$，预处理出**在 $t[i+1:n]$ 中所有与 $c$ 相等的 $t_p$ 在 $s_n$ 中被复制的次数**，就可以快速计算**在 $t[i+1:k]$ 中所有与 $c$ 相等的 $t_p$ 在 $s_k$ 中被复制的次数。**

思路 1：找到一个最小的 $pos$ 使得 $|s_{pos}|\geq \max(|m|)$（如果不存在则为 $n$）。对于每一个 $j\in[0,pos]$，建出 $s_j$ 的后缀数组，然后处理所有 $k=j$ 的询问（若 $j=pos$ 则处理所有 $k\geq j$ 的询问）即可（SA 的主要作用是求出 $m$ 在 $s_i$ 中的出现次数）。判断 $m,s$ 的前缀后缀是否相等需要用哈希。时间复杂度 $\mathcal{O}(L\log L)$。常数较大 ~~（而且我还写挂了）~~。

思路 2：在上面的思路中，对于一个询问，我们主要关注的是它的 $k$。这样在求出现次数的时候必须使用后缀数据结构，（因为如果有很多 $k$ 都很大而 $|m|$ 很小的询问，同时有一个 $|m|$ 很大的询问，那么直接哈希判断的复杂度可以达到 $qL$），比较麻烦。但是注意到对于那些 $|m|$ 很小的询问，我们没有必要让它与 $s_{pos}$ 匹配，直接找到一个**最小**的 $i$ 满足 $|s_i|\geq |m|$，让它与 $s_i$ 匹配就好了。如果 $i>k$ 则显然没有出现（因为 $|s_k|<|m|$）。这样求出现次数就可以直接哈希或者 KMP 了，查询的时间复杂度可以降为 $\mathcal{O}(L)$。总时间复杂度即为 $\mathcal{O}(n|\Sigma|+L)$。

```cpp
/*
	Powered by C++11.
	Author : Alex_Wei.
*/

#pragma GCC optimize(3)

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair <int,int>;

#define fi first
#define se second
#define mpi make_pair
#define pb emplace_back
#define mcpy(x,y) memcpy(x,y,sizeof(y))

const int L=2e6+5;
const int N=1e5+5;
const int mod=1e9+7;

void add(ll &x,int y){
	x+=y; if(x>=mod)x-=mod;
}

ull hs1[L],hs2[L],p[L];
ull q1(int l,int r){
	return hs1[r]-hs1[l-1]*p[r-l+1];
} ull q2(int l,int r){
	return hs2[r]-hs2[l-1]*p[r-l+1];
}

int n,q,len,mxlen;
ll f[N][26],pw[N],iv[N],ans[N];
char s[L],t[N];
string qs[N];
vector <pii> qu[L];

int main(){
	scanf("%d%d%s%s",&n,&q,s+1,t+1),pw[0]=p[0]=iv[0]=1;
	for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%mod,iv[i]=iv[i-1]*(mod+1>>1)%mod;
	for(int i=1;i<L;i++)p[i]=p[i-1]*131;
	for(int i=n;i;i--){
		for(int j=0;j<26;j++)f[i][j]=f[i+1][j];
		add(f[i][t[i]-'a'],pw[n-i]);
	} for(int i=1;i<=q;i++){
		int id; cin>>id>>qs[i],mxlen=max(mxlen,(int)qs[i].size());
		qu[qs[i].size()].pb(mpi(i,id));
	} int pre=0,pos=0; len=strlen(s+1);
	while(1){
		for(int i=1;i<=len;i++)hs1[i]=hs1[i-1]*131+s[i];
		for(int l=pre+1;l<=len;l++)for(pii it:qu[l]){
			string t=qs[it.fi]; int id=it.fi,k=it.se,slen=t.size();
			if(k<pos)continue;
			for(int i=1;i<=slen;i++)hs2[i]=hs2[i-1]*131+t[i-1];
			ull ap=0,hs=hs2[slen];
			for(int i=slen;i<=len;i++)ap+=q1(i-slen+1,i)==hs;
			ans[id]=ap*pw[k-pos]%mod;
			for(int i=1;i<=slen;i++){
				int l=i-1,r=slen-i,it=t[i-1]-'a';
				if(q1(len-l+1,len)==q2(1,l)&&q1(1,r)==q2(slen-r+1,slen))
					add(ans[id],(f[pos+1][it]-f[k+1][it]+mod)*iv[n-k]%mod);
			}
		} if(len>=mxlen)break;
		for(int i=1;i<=len;i++)s[len+i+1]=s[i];
		s[len+1]=t[++pos],pre=len,len=(len<<1)+1; 
	} for(int i=1;i<=q;i++)cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：OMG_wc (赞：2)

前置知识：用 KMP 算法求文本串 $T$ 中模式串 $S$ 出现的次数。



首先需要把贡献分类：设 $e$ 为 $s$ 中等于 $w$ 的某个子串，若 $e$ 包含的最后一个 $t$ 中字符为 $t_i$，那么我们把 $e$ 这个贡献记进 $g_i$ 里。

注意特殊情况 $g_0$ 表示 $e$ 中不含 $t$ 的字符，而其他情况一定只有唯一一个最后的字符 $t_i$，因为有两个的话中间就包含 $t_{i+1}$ 了。

最后要算的答案就是 $\sum\limits_{i=0}^{k} g_i$ ，这个暴力算的话就是：

每个 $s_i$ 在最终 $s_k$ 中一共出现了 $2^{k-i}$ 次，要算经过 $t_i$ 的贡献，只要取 $s_{i-1}$ 的后 $|w|-1$ 个字符拼接 $t_i$ 再拼接 $s_{i-1}$ 的前 $|w|-1$ 个字符作为文本串进行KMP，计算 $w$ 出现次数。

但暴力把 $s$ 完全展开是不行的....观察发现，当 $s$ 增长到一定规模后，之后的任意两个 $t_i$ 不可能同时出现在 $w$ 里。



具体而言，当 $s_{i-1}+1\ge w$ 时，所有满足 $j\in[i,k]$ 的 $t_j$ 都不可能同时出现在一个 $w$ 里，即后续的 $t_j$ 不会不会影响彼此，那么同样的字母就会有同样的贡献了（除了次数权值外）。

可以把此时的 $s_{i-1}$ 看成一个整体，记为字符串 $P$ 。

那么后续只要在 $P+t_j+P$ 这个字符串里找经过 $t_j$ 的 $w$ 即可，再乘上系数  $2^{k-j}$ （即 $t_j$ 出现的次数）。

必须得经过 $t_j$，因此只要 $P$ 的后 $|w|-1$ 个字符拼接 $t_j$ 再拼接$P$ 的前 $|w|-1$ 个字符组成的字符串 作为文本串进行 KMP 来计算  $w$ 出现次数。

字符集只有 $26$ 个字母，所以需要计算 $26$ 种情况。然后需要对每个字母进行预处理，分别计算 $2^{-j}$ 的前缀和。现在要算 $j\in [i,k]$ ，差分一下即，最后乘上一个公共系数 $2^k$ 。

总时间复杂度 $O(26\times(n+\sum w))$，代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const LL inv = (mod + 1) / 2;
const int N = 1000005;

int f[N];
void init(string s) {
    f[0] = 0;
    for (int i = 1, j = 0; i < s.size(); i++) {
        while (j > 0 && s[i] != s[j]) j = f[j - 1];
        if (s[i] == s[j]) j++;
        f[i] = j;
    }
}
int cal(string t, string s) {
    int res = 0;
    for (int i = 0, j = 0; i < t.size(); i++) {
        while (j > 0 && t[i] != s[j]) j = f[j - 1];
        if (t[i] == s[j]) j++;
        if (j == s.size()) {
            res++;
            j = f[j - 1];
        }
    }
    return res;
}
LL b[26][N];
LL two[N];
string t;
vector<string> s(1);
int main() {
    int n, q;
    cin >> n >> q >> s[0] >> t;
    t.insert(0, 1, '#');
    for (int i = 1; s[i - 1].size() < 1e6; i++) {
        s.push_back(s[i - 1] + t[i] + s[i - 1]);
    }

    for (int i = 0; i < 26; i++) {
        LL rp = 1;
        for (int j = 1; j <= n; j++) {
            rp = rp * inv % mod;
            b[i][j] = (b[i][j - 1] + (t[j] == 'a' + i ? rp : 0)) % mod;
        }
    }
    two[0] = 1;
    for (int i = 1; i <= n; i++) two[i] = two[i - 1] * 2 % mod;
    while (q--) {
        int k;
        string w;
        cin >> k >> w;
        init(w);
        LL ans = 0;
        for (int i = 0; i <= k; i++) {
            if (i > 0 && s[i - 1].size() + 1 >= w.size()) {
                for (int j = 0; j < 26; j++) {
                    string now = s[i - 1].substr(s[i - 1].size() - w.size() + 1) + (char)(j + 'a') +
                                 s[i - 1].substr(0, w.size() - 1);
                    ans += (b[j][k] - b[j][i - 1]) * cal(now, w) % mod * two[k] % mod;
                }
                break;
            }
            if (s[i].size() >= w.size()) ans += cal(s[i], w) * two[k - i] % mod;
        }
        ans = (ans % mod + mod) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}
```





---

## 作者：Hoks (赞：0)

## 前言
能不能别再看错题了。

广告：[『从入门到入土』串串学习笔记](https://www.luogu.com.cn/article/dv6dig1o)。
## 思路分析
注意题目里的每次只是一个字符。

我们先考虑下暴力怎么做。

对于一个字符串 $s_i$，我们考虑计算他的贡献：
1. 在 $s_{i-1}$ 里出现了，那么就是 $s_{i-1}$ 的贡献乘二。
2. 跨越了 $t_{i-1}$。

对于 $2$，我们直接把中间那段提取出来直接 KMP 计算就行了。

复杂度 $O(n\sum|w|)$。

考虑优化。

我们知道 $s_i$ 的长度增长是指数级的，所以我们从这点下手。

我们发现，对于 $s_j,s_k(j<k,s_{j-1}>|w|)$，如果 $t_{j-1}=t_{k-1}$，那么他们 $2$ 的答案是一样的。

因为你可以直接从 $s_k$ 中间提取出一段 $s_j$，因为 $s_j$ 长度已经是 $|w|$ 的两倍了，所以不可能跨越过到达另一个 $t$ 的位置。

那么我们对于前面的几个串暴力处理出来，找到第一个 $j$ 直接数后面就行了。

复杂度 $O(|S|(n+\sum |w|))$，其中 $|S|$ 是字符集大小。
## 代码

```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
using namespace std;
const int N=4e6+10,V=1e6,M=22,K=1e5+10,INF=1e18,p=13331,mod=1e9+7;
int n,m,l[K],nxt[N];char s[M][N],t[N],st[N],cur[N];
long long op[K],a[27][K],inv=(mod+1)/2;
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
    inline void print(long long x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
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
namespace KMP
{
	inline void kmp(char s[],int n,int nxt[])
	{
		for(int i=2,j=0;i<=n;i++)
		{
			while(j&&s[i]!=s[j+1]) j=nxt[j];
			if(s[i]==s[j+1]) j++;nxt[i]=j;
		}
	}
	inline int findstr(int n,int m,char s1[],char s2[],int nxt[])
	{
		int j=0,res=0;
		for(int i=1;i<=n;i++)
		{
			while(j&&s2[j+1]!=s1[i]) j=nxt[j];
			if(s2[j+1]==s1[i]) j++;
			if(j==m) res++,j=nxt[j];
		}return res;
	}
}
using namespace KMP;
inline void solve()
{
    read();m=read();rd(s[0],l[0]);rd(t,n);
	for(int i=op[0]=1;i<=n;i++) op[i]=op[i-1]*2%mod;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=l[i-1];j++) s[i][++l[i]]=s[i-1][j];
        s[i][++l[i]]=t[i];
        for(int j=1;j<=l[i-1];j++) s[i][++l[i]]=s[i-1][j];
        if(l[i-1]>V) break;
    }
	for(int i=0;i<26;i++)
	{
		long long s=inv;
		for(int j=1;j<=n;j++) a[i][j]=(a[i][j-1]+(t[j]=='a'+i?s:0))%mod,s=s*inv%mod;
	}
	for(int p=1,k,ll;p<=m;p++)
	{
		k=read();ll=0;rd(st,ll);kmp(st,ll,nxt);long long ans=0;
		for(int i=0;i<=k;i++)
		{
			if(i&&l[i-1]+1>=ll)
			{
				for(int j=0;j<26;j++)
				{
					int r=0;for(int q=l[i-1]-ll+2;q<=l[i-1];q++) cur[++r]=s[i-1][q];
					cur[++r]='a'+j;for(int q=1;q<ll;q++) cur[++r]=s[i-1][q];
					ans=(ans+(a[j][k]-a[j][i-1]+mod)%mod*findstr(r,ll,cur,st,nxt)%mod*op[k]%mod)%mod;
				}break;
			}
			if(l[i]>=ll) ans=(ans+findstr(l[i],ll,s[i],st,nxt)*op[k-i]%mod)%mod;
		}print(ans%mod);put('\n');
	}
}
signed main()
{
    int T=1;
    // T=read();
    while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：幽云蓝 (赞：0)

考虑 $|s_0|$ 很小，而 $s_i$ 的形态类似于 $s_0t_xs_0t_ys_0\dots$ 这样，所以我们暴力从询问串中把 $s_0$ 相关元素剔除，问题就等价于只有 $t$ 串了。

考虑在一个长度为 $x$ ($x\ge 2$) 的连续区间中，至少有 $\lfloor\frac{x}{2}\rfloor$ 项为 $t_1$，我们把它们剔除。接下来是 $t_2$，$t_3$，直到我们把整个串删空，此时记上一次我们剔除的为 $t_i$，这个连续区间的出现次数即为 $2^{k-i}$。

注意到当连续区间长度为 $1$ 时复杂度会退化，我们使用一个前缀和数组进行预处理即可。时间复杂度为 $O(\sum w_i|s|\log w_i)$，可以通过。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;

const long long MOD = 1000000007;

string s, t;
long long k;
string w;
vector < char > v;
long long ans = 0;
long long pw[100010];
long long invpw[100010];
long long cnt[100010][26];
int n, q;

long long qpow(long long a, long long b){
	long long ans = 1;
	while (b){
		if (b & 1) ans = (ans * a) % MOD;
		a = (a * a) % MOD;
		b >>= 1; 
	}
	return ans;
}

bool gtv(int st){
	for (int i = 0; i < w.size(); i++){
		int x = (i - st + s.size() + 1) % (s.size() + 1);
		if (!x){
			v.push_back(w[i]);
		}
		else{
			if (w[i] != s[x - 1]){
				return false;
			}
		}
	}
	return true;
}

void slv(int now, vector < char > vt){
	if (vt.size() == 0 || vt.size() == 1){
		if (vt.size() == 1){
			if (!now) return;
			ans = (ans + (cnt[k - now][vt[0] - 'a'] + MOD - cnt[k][vt[0] - 'a']) * invpw[n - k] % MOD) % MOD;
		}
		else ans = (ans + pw[now]) % MOD;
		return;
	}
	else{
		if (!now) return;
		vector < char > v1, v2;
		v1.clear();
		v2.clear();
		int ok1 = 1, ok2 = 1;
		for (int i = 0; i < vt.size(); i++){
			if (i % 2 == 0){
				if (ok2) v2.push_back(vt[i]);
				if (vt[i] != t[k - now]) ok1 = 0;
			}
			else{
				if (ok1) v1.push_back(vt[i]);
				if (vt[i] != t[k - now]) ok2 = 0;	
			}
		}
		if (ok1) slv(now - 1, v1);
		if (ok2) slv(now - 1, v2);
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	cin >> s >> t;
	pw[0] = 1;
	for (int i = 1; i <= n; i++) pw[i] = (pw[i - 1] * 2) % MOD;
	invpw[0] = 1;
	invpw[1] = qpow(2, MOD - 2);
	for (int i = 2; i <= n; i++) invpw[i] = (invpw[i - 1] * invpw[1]) % MOD;
	for (int i = n - 1; i >= 0; i--){
		for (int j = 0; j < 26; j++) cnt[i][j] = (cnt[i][j] + cnt[i + 1][j]) % MOD;
		cnt[i][t[i] - 'a'] += pw[n - i - 1];
		cnt[i][t[i] - 'a'] %= MOD;	
	}
	for (int i = 1; i <= q; i++){
		ans = 0;
		cin >> k >> w;
		for (int i = 0; i <= s.size(); i++){
			v.clear();
			if (gtv(i)) slv(k, v);
		}
		cout << ans << endl;
	}
	return 0;
}

```


---

