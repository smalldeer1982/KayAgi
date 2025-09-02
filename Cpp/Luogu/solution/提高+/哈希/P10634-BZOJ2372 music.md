# BZOJ2372 music

## 题目描述

最近 A、B 两国发生了一场战争。dick 作为 A 国的军事总指挥，最近非常头痛于己方的情报问题。因为 B 国最近雇佣了 Easy 这一位密码专家来给他们的所有通讯加密。

Easy 非常喜欢唱歌，于是他决定将所有的信号都变成旋律储存起来，比如说 $11556654433221$ 就可能是一段加过密的音符，我们用一个等长度的序列来表示它，就变成了 $1,1,5,5,6,6,\dots$。为了增加密码的保密性，他把加密的乐谱又调整了一下，把某些音调改变了，将原序列 $A$ 变成 $B$，有 $|A|=|B|$，且对于 $a_i=a_j$ 有 $b_i=b_j$，对于 $a_i<a_j$ 有 $b_i<b_j$，对于 $a_i>a_j$ 有 $b_i>b_j$。例如：`11221` 和 `55775` 就可能代表了同一段音符。

最近，dick 截获了一段信号，这段信号中可能包含了某些重要信息。根据以往的经验，dick 已经知道了某些旋律所代表的意义。于是 dick 想知道，对于一段已知的旋律，能不能判断它是否在这段截获的旋律中出现？如果出现了，能否找出它出现的次数及位置呢？

「任务」判断给定旋律在截获旋律中出现的次数及位置。

## 说明/提示

对于所有数据，保证 $1\leq n \leq 10^5$，$1\leq m \leq 25000$。

## 样例 #1

### 输入

```
9 6 10
5
6
2
10
10
7
3
2
9
1
4
4
3
2
1```

### 输出

```
1
3```

# 题解

## 作者：Zhao_daodao (赞：6)

# 「BZOJ 2372」music

模拟赛 T2，被各位大神爆切。

## Description

给你一个长度为 $n$ 的序列 S，一个长度为 $m$ 的序列 T。序列的数是 $[1,x]$ 之间的正整数。

定义两个长度相等的串**等价**：在这两个串中相对顺序不变。如 `aabcd` 和 `iixyz` 就是等价的。

问在 S 中，有多少个子串跟 T 等价，并按顺序输出。

$1\le n\le 10^5,1\le m\le 25000,1\le x\le 25$。

## Solution

发现字符集大小为一个常数，跟字符串中的小写字母很像。可以考虑一些字符串的做法。

相对顺序不变很不好判断。没有什么 DS 可以维护这种东西。

在 S 中，可能跟 T 等价的子串长度一定为 $m$。所以事实上需要判断的串只有 $O(n)$ 个。

考虑直接暴力统计每一个序列的数的 rk，最后暴力判断。

想到这里差不多就做完了。

---

类似字符串 hash 的做法。记 字符 $x$ 的 hash 值为 $hsh_x$。

因为每一个字符对应的 rk 可能不一样，所以直接每一个字符存一个数。

什么意思呢，如果串是 `abccb`，那么在 `a` 中，就存下 `10000`，`b` 中存 `1001`，`c` 中存 `110`。

最后整一个串的 hash 值就是 $\sum hsh_x \times rk_x$。

从左到右扫，记录当前区间每一个字符的出现次数。出现过就给它一个 rank。每一次都重新扫。

每一次对于每一个 hash 值，$hsh_x\leftarrow hsh_x\times base$。当前位置的 hash 值就额外加 1。

如果要删除一个字符，$hsh_x\leftarrow hsh_x-base^m$。

再以 T 做同样的事情，直接判断 T 的 hash 值和 $\sum hsh_x\times rk_x$ 就可以了。

复杂度 $O((n+m)s)$。

## Code

```cpp
#include<bits/stdc++.h>
#define ll unsigned long long
using namespace std;
const int MAXN=1e6+5;
const int base=19260817;
int n,m,s;
int S[MAXN],T[MAXN];
ll fc[MAXN];
int cnt2[27],id2[27],tot2;
int cnt1[27],id[27],tot1;
ll num[27];
inline void add(int x,bool need){num[x]=(num[x]*base+need);}
inline void del(int x){num[x]=(num[x]-fc[m]);}
inline void make_hsh(){tot1=0;for(int i=1;i<=s;i++)if(cnt1[i])id[i]=++tot1;}
inline ll hsh(){
	ll ans=0;
	for(int i=1;i<=s;i++)ans+=num[i]*id[i];
	return ans;
}
ll hsh2;
inline void init(){
	fc[0]=1;
    for(int i=1;i<=max(n,m);i++)fc[i]=fc[i-1]*base;
	for(int i=1;i<=m;i++)cnt2[T[i]]++;
	for(int i=1;i<=s;i++)if(cnt2[i])id2[i]=++tot2;
	for(int i=1;i<=m;i++)hsh2=(hsh2*base+id2[T[i]]);
}
signed main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n>>m>>s;
    for(int i=1;i<=n;i++)cin>>S[i];
    for(int i=1;i<=m;i++)cin>>T[i];
	vector<int>ans;
    init();
	for(int i=1;i<=n;i++){
		for(int x=1;x<=s;x++)add(x,S[i]==x);
		cnt1[S[i]]++;
		if(i>m){del(S[i-m]);cnt1[S[i-m]]--;}
		if(i>=m){
			make_hsh();
			if(hsh()==hsh2)ans.push_back(i);
		}
	}
	cout<<ans.size()<<"\n";
	for(int i:ans)cout<<i-m+1<<"\n";
}
```

---

## 作者：L_zaa_L (赞：5)

首先我们发现有一个范围很特殊，就是 $s\le25$，然后这个范围提醒我们可以枚举，因为两个序列要想是同一段音符，那么肯定有 $a_i=a_j,b_i=b_j\land a_i\not=a_j,b_i\not=b_j$，然后我们可以枚举这些旋律 $x,y$，然后将 $a$ 中所有的 $x$ 设为 $1$，其他的设为 $0$，将 $b$ 中所有的 $y$ 设为 $1$，其他的设为 $0$。然后我们可以将 $b$ 去匹配 $a$，那么能匹配上的位置这两个位置才能满足条件。

记一个 $e_{i,x}=y$ 表示在 $i$ 这个位置开始 $a[i,i+m-1]$ 中 $x$ 旋律和 $y$ 这个旋律是可以对应的（没有就是 $0$），不难发现每个 $e_{i,x}$ 是唯一（除非 $y$ 没在 $b$ 中出现）。

如果一个位置想要满足条件，那么所有在 $a[i,i+m-1]$ 出现过的旋律（判断一个旋律是否出现过可以用前缀和），都要有 $e_{i,x}\not= 0(x\in a[i,i+m-1])$ 并且 $\forall x<y(x,y\in a[i,i+m-1]),e_{x,i}<e_{y,i}$，从小到大枚举出现过的 $x$，看看 $e_{x,i}$ 是不是从小到大就行了。

然后时间复杂度：$O(s^2(n+m))$。

代码：

```cpp
#include<bits/stdc++.h>
//~ #define int long long
#define ls(x) ((x)*2)
#define rs(x) ((x)*2+1)
#define mid ((l+r)>>1)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
using namespace std;
const int N=1e5+5,Mod=998244353;
//typedef __int128_t i128;
//i128 _base=1;
//inline int mol(int x){return x-Mod*(_base*x>>64);}
//inline void Add(int &x,int y){x=mol(x+y+Mod);}
inline int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?-x:x;
}
int n,m,q,p[N];
int a[N],b[N];
int s[N],t[N];
int e[N][26];
inline void KMP(int x,int y){
    int j=0;
    For(i,1,m) p[i]=0;
    p[1]=0;
    for(int i=2;i<=m;++i){
        while(j>0&&t[j+1]!=t[i])j=p[j];
        if(t[i]==t[j+1])++j;
		p[i]=j;
    }
    j=0;
    for(int i=1;i<=n;++i){
        while(j>0&&t[j+1]!=s[i])
			j=p[j];
        if(t[j+1]==s[i])
			++j;
        if(j==m){
            e[i-m+1][x]=y;
			j=p[j];
		}
    }
}
int qzh[N][26];
int ans[N],tot;
signed main(){
	//_base=(_base<<64)/Mod;
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	// ios::sync_with_stdio(false);
	// cin.tie(0); cout.tie(0);
    n=read(),m=read();
    q=read();
    For(i,1,n) a[i]=read();
    For(i,1,n){
        For(j,1,q) qzh[i][j]=qzh[i-1][j];
        qzh[i][a[i]]++;
    }
    For(i,1,m) b[i]=read();
    For(i,1,q){
		bool bk=0;
        For(k,1,n){
            if(a[k]==i) s[k]=1,bk=1;
            else s[k]=0;
        }
        if(!bk) continue;
        For(j,1,q){
			bk=0;
            For(k,1,m){
                if(b[k]==j) t[k]=1,bk=1;
                else t[k]=0;
            }
            if(!bk) continue;
            KMP(i,j);
        }
    }
    For(i,1,n){
		bool flag=0;
		For(t,1,q){
			if(qzh[i+m-1][t]-qzh[i-1][t]>0&&!e[i][t]){
				flag=1;
				break;
			}
		}
		if(flag) continue;
		int p=0;flag=0;
		For(t,1,q){
			if(qzh[i+m-1][t]-qzh[i-1][t]==0) continue;
			int minx=e[i][t];
			if(p>=minx||!e[i][t]){flag=1;break;}
			p=minx;
		}
		if(!flag) ans[++tot]=i;
    }
    printf("%d\n",tot);
    For(i,1,tot) printf("%d\n",ans[i]); 
#ifdef LOCAL
    Debug("\nMy Time: %.3lfms\n", (double)clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}

```

---

## 作者：CYZZ (赞：5)

## [P10634 BZOJ2372 music](https://www.luogu.com.cn/problem/P10634)

模拟赛不会的题。

整个过程可以看作 $B$ 在 $A$ 上进行匹配。

考虑如何快速判断 $A$ 的子串 $T$ 是否由 $B$ ”加密“构成。

显然上述情况发生当且仅当 $A$ 与 $T$ 离散化后相同。

于是就有 $O(nm\log m)$ 的做法：

> 将 $B$ 排序并离散化后得到 $B'$。
>
> 对于 $A$ 的每个长度为 $m$ 的子串 $T$，用同样的方式得到 $T'$。
>
> 比较 $B',T'$。

考虑优化。

$O(1)$ 比较两个字符串，首选字符串哈希，考虑设计哈希函数 $f(T)$。

发现值域只有 $25$，显得使用 `std::sort,std::unique` 很蠢，可以用桶排。

在扫的时候维护 $cnt_c$ 表示 $c$ 在 $T=A_{i-m+1\sim i}$ 中的出现次数，$val_c$ 表示 $c$ 在 $T$ 中出现的位置（相当于一个 $m$ 位的二进制数，具体可以用字符串哈希实现）。

然后每次用 $O(25)$ 处理出字母 $c$ 在 $T$ 中的排名 $id_c$，那么 $f(T)=\sum_cid_cval_c$。

比较 $f(T),f(B)$ 即可 $O(1)$ 判断。

单次 $O(|\Sigma|)$，总时间复杂度 $O(n|\Sigma|)$。

---

## 作者：ran_qwq (赞：4)

注意到两个字符串等价相当于离散化后相等，可以先把 $B$ 离散化，再判断 $A$ 每个长度为 $m$ 的子串是否与 $B$ 相等。

问题是如何动态维护每个子串离散化后的结果。考虑求每种字符会变成什么，可以动态维护每种字符个数来求，每个子串重构一遍。

设当前子串是 $[l,r]$。$i$ 离散化后变成 $c_i$，原来的哈希值是 $H$。那么离散化后 $i$ 对哈希的贡献会减去 $(i-c_i)$ 乘上 $\sum\limits_{j=l}^r[a_j=i]B^{r-j}$，其中 $B$ 是哈希的 base。而后面那一坨东西也可以动态维护：后面加一个字符、前面删一个字符、整体往左移一格。

算出所有子串离散化后的哈希值后，和 $B$ 离散化后哈希值比较一下即可。

时间复杂度 $O((n+m)s)$。

```cpp
int n,m,k,cnt,b[27],c[27],s[N],t[N]; ull ht,d[27],pw[N],hs[N]; vi v;
void bld() {cnt=0,mst(c,0); for(int i=1;i<=k;i++) cw(b[i],c[i]=++cnt);}
ull gt(int l,int r) {return hs[r]-hs[l-1]*pw[r-l+1];}
ull qry(int x) {ull r=gt(x-m+1,x); for(int i=1;i<=k;i++) r-=d[i]*(i-c[i]); return r;}
void QwQ() {
	n=rd(),m=rd(),k=rd(),pw[0]=1; for(int i=1;i<=n;i++) s[i]=rd(),pw[i]=pw[i-1]*B;
	for(int i=1;i<=m;i++) t[i]=rd(),b[t[i]]++; bld();
	for(int i=1;i<=n;i++) hs[i]=hs[i-1]*B+s[i]; for(int i=1;i<=m;i++) ht=ht*B+c[t[i]];
	mst(b,0); for(int i=1;i<=m;i++) b[s[i]]++; bld();
	for(int i=1;i<=m;i++) d[s[i]]+=pw[m-i]; cw(qry(m)==ht,v.pb(1));
	for(int i=m+1;i<=n;i++) {
		b[s[i-m]]--,b[s[i]]++,bld();
		for(int j=1;j<=k;j++) d[j]*=B; d[s[i-m]]-=pw[m],d[s[i]]++;
		cw(qry(i)==ht,v.pb(i-m+1));
	}
	wr(v.size(),"\n"); for(int x:v) wr(x,"\n");
}
```

---

## 作者：Y204335 (赞：2)

# P10634 BZOJ2372 music

提供一种不使用 hash 的做法。

## 题目大意

**定义**两个长度相等的数组**等价**当且仅当每个元素的**相对位置**相同
，形式化的说：$\forall i,j\in[1,l], a_{i} < a_{j}\wedge b_{i}< b_{j}$ 或 $ a_{i} = a_{j}\wedge b_{i}= b_{j}$ 或 $a_{i} > a_{j}\wedge b_{i}> b_{j}$ 。

给两个数组 $A,B$，问 $A$ 的**子串**中与 $B$ **等价**的有多少个，并给出起始位置。

## 题目分析

直接暴力地进行判断是 $O(n^{3})$，显然无法通过。

仔细观察题目不难发现一个性质：如果一个数组中有一些数字相同，那么在和它等价的数组中，**这些位置也一定是相同的**，并且由于 $s\le 26$，所以可以记录在 $B$ 中有哪些位置相同，并枚举左端点
，判断这些位置是否在 $A$ 中是否相同，之后问题就转化为了**对最多 26 个数字的判断 (只要判断第一次出现时)**，从小到大处理即可。但这样做最坏情况是 $O(n^{2})$ 的，虽然很难卡掉，但还是会 TLE 一个点。

思考刚才的操作，我们先保证在 $B$ 中相同的位置在 $A$ 中也相同，再判断每个数字第一次出现时的位置（这已经保证了之后都满足条件），显然可以发现，第一个步骤会**重复处理很多位置**，可以尝试优化，不难发现第一步很像是一种特殊的匹配，只是匹配方式不是直接相等，而是**上一个与当前位置的数一样的数的位置相同**（~~有点绕~~），这就可以尝试字符串匹配算法，也就是 KMP（严谨点应该叫广义 KMP，但实际上差不多）来解决。

我们只需要修改 KMP 判断两个字符相同的代码，就可以实现我们需要的效果，只要在最大公共前后缀为 $m$ 时，像原来一样判断每个数第一次出现的位置即可，复杂度为 $O(ns)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, m, nxt[N][27], s, nxt2[N][27], km[N], km2[N], x[27], a[N], b[N];
vector<int> ans;
int read()
{
    char ch = getchar();
    int f = 0;
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        f = f * 10 + ch - '0', ch = getchar();
    return f;
}
void write(int p)
{
    if (p > 9)
        write(p / 10);
    putchar(p % 10 + '0');
}
void cl()
{
    n = read();
    m = read();
    s = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    for (int i = 1; i <= m; i++)
        b[i] = read();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= s; j++) {
            nxt[i][j] = x[j];
        }
        x[a[i]] = i;
    }
    memset(x, 0, sizeof(x));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= s; j++) {
            nxt2[i][j] = x[j];
        }
        x[b[i]] = i;
    }
    for (int i = 2; i <= m; i++) { // 这里直接把两个数组分开跑KMP
        int nw = km[i - 1];
        while (nw && (nxt2[i][b[i]] >= i - (nw + 1) + 1 ? nxt2[i][b[i]] - (i - (nw + 1)) : 0) != nxt2[nw + 1][b[nw + 1]])
            nw = km[nw]; // 这里的代码比较绕，可以结合KMP的普通代码以及样例来理解，简而言之其实就是判断上一个为该数字的位置是否相同
        if ((nxt2[i][b[i]] >= i - (nw + 1) + 1 ? nxt2[i][b[i]] - (i - (nw + 1)) : 0) == nxt2[nw + 1][b[nw + 1]])
            nw++;
        km[i] = nw;
    }
    for (int i = 1; i <= n; i++) {
        int nw = km2[i - 1];
        while (nw == m || (nw && ((nxt[i][a[i]] >= i - (nw + 1) + 1 ? nxt[i][a[i]] - (i - (nw + 1)) : 0) != nxt2[nw + 1][b[nw + 1]])))
            nw = km[nw];
        if ((nxt[i][a[i]] >= i - (nw + 1) + 1 ? nxt[i][a[i]] - (i - (nw + 1)) : 0) == nxt2[nw + 1][b[nw + 1]])
            nw++;
        km2[i] = nw;
        if (nw == m) { // 判断每个数第一次出现的位置
            int k = 1, lst = 0;
            for (int j = 1; j <= s; j++) {
                if (!x[j])
                    continue;
                if (lst && a[x[lst] + i - m] >= a[x[j] + i - m]) {
                    k = 0;
                    break;
                }
                lst = j;
            }
            if (k) {
                ans.push_back(i - m + 1);
            }
        }
    }
}
int main()
{
    cl();
    write(ans.size());
    putchar('\n');
    for (auto i : ans)
        write(i), putchar('\n');
    return 0;
}
```

---

## 作者：WRuperD (赞：2)

随机来发一篇题解。

考虑去哈希每一个数后面有多少个数比它要大。正确性比较显然。每一次动态维护即可。注意到值域非常小，所以可以单次暴力 $O(s)$ 地做。

一个细节是：可能存在多个数相等的情况。这样我们不论是哈希大于等于这个数的个数还是严格大于这个数的个数都会出错。

所以你两种一起做一起判断是否同时满足条件即可。

[code](https://hydro.ac/d/bzoj/record/66f5057816a565e997ce6985)

---

## 作者：qnqfff (赞：1)

### 思路

容易发现两个旋律 $A,B$ 等价的条件相当于 $\forall i \sum\limits_{j=1}^{n}[a_j<a_i]=\sum\limits_{j=1}^{n}[b_j<b_i]$，即每个位置在序列中的排名相同。

考虑哈希维护，每次加一个数，先算出他自己的排名，再在原序列中把大于他的加一，因为值域很小，所以直接开个桶记录一下即可，删除一个数也是类似的。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
const int B=31,mod=1e9+7;
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n,m,s,pw[100010],T,cnt[26],sum[26],a[100010],b[100010];
signed main(){
	n=read();m=read();s=read();for(int i=1;i<=n;i++) a[i]=read();for(int i=1;i<=m;i++) b[i]=read();
	pw[0]=1;for(int i=1;i<=m;i++) pw[i]=pw[i-1]*B%mod;
	for(int i=1;i<=m;i++){
		cnt[b[i]]++;for(int i=1;i<=s;i++) (sum[i]*=B)%=mod;sum[b[i]]++;
		(T*=B)%=mod;for(int j=1;j<b[i];j++) (T+=cnt[j])%=mod;for(int j=b[i]+1;j<=s;j++){(T+=sum[j])%=mod;}
	}memset(cnt,0,sizeof(cnt));memset(sum,0,sizeof(sum));
	int res=0;for(int i=1;i<=m;i++){
		cnt[a[i]]++;for(int i=1;i<=s;i++) (sum[i]*=B)%=mod;sum[a[i]]++;
		(res*=B)%=mod;for(int j=1;j<a[i];j++) (res+=cnt[j])%=mod;for(int j=a[i]+1;j<=s;j++){(res+=sum[j])%=mod;}
	}
	auto del=[&](int x){
		(sum[a[x]]-=pw[m-1]-mod)%=mod;cnt[a[x]]--;for(int i=a[x]+1;i<=s;i++) (res-=sum[i]-mod)%=mod;
		int rk=0;for(int i=1;i<a[x];i++) rk+=cnt[i];(res-=rk*pw[m-1]%mod-mod)%=mod;
	};
	auto add=[&](int x){
		cnt[a[x]]++;for(int i=1;i<=s;i++) (sum[i]*=B)%=mod;sum[a[x]]++;
		(res*=B)%=mod;for(int j=1;j<a[x];j++) (res+=cnt[j])%=mod;for(int j=a[x]+1;j<=s;j++){(res+=sum[j])%=mod;}
	};
	vector<int>ans;if(!(res^T)) ans.push_back(1);
	for(int i=2;i+m-1<=n;i++){del(i-1);add(i+m-1);if(!(res^T)) ans.push_back(i);}cout<<ans.size()<<'\n';for(auto i:ans) cout<<i<<'\n';
	return 0;
}
```

---

## 作者：AZYDLL (赞：0)

## 思路

首先尝试进行粗略一点的匹配：对于数列 $s$ 与 $t~(|s|=|t|)$，有 $\forall i,j \in [1,|s|],s_i=s_j \land t_i=t_j$ 或 $s_i \neq s_j \land t_i \neq t_j$。显然可以用 KMP 进行此类匹配，即将常规 KMP 中判断两个字符是否相等的操作变为判断它们的上次出现的位置是否相等。

完成上述定义的匹配后，只要再判断两数列相同位置的数排名一样。可记录下 $t$ 中每个旋律最后一次出现的位置，然后从小到大比较 $s$ 中相同位置的旋律是否满足同样的大小关系即可。

## 代码

~~不知为何成了暂时的最优解。~~

```cpp
#include<bits/stdc++.h>
#define MAXN 100005
#define MAXW 35

using namespace std;
namespace FastIO
{
	inline string _rs()
	{
		string str="";
		int ch=getchar();
		while(ch==' ' || ch=='\n' || ch=='\r') ch=getchar();
		while(ch!=' ' && ch!='\n' && ch!='\r' && ch!=EOF){
			str.push_back(ch);
			ch=getchar();
		}
		return str;
	}
	inline void _ws(string a,char b)
	{
		int len=a.size();
		for(int i=0;i<len;i++) putchar(a[i]);
		putchar(b);
		return ;
	}
	inline int _r()
	{
		int flag=1,ans=0,ch=getchar();
		while((ch<'0' || ch>'9') && ch!=EOF){
			if(ch=='-') flag=-1;
			ch=getchar();
		}
		while(ch>='0' && ch<='9'){
			ans=(ans<<1)+(ans<<3)+(ch^48);
			ch=getchar();
		}
		return flag*ans;
	}
	inline void _w(int a,char b)
	{
		if(a<0) a=-a,putchar('-');
		int sta[22],top=0;
		do{
			sta[top++]=a%10;
			a/=10;
		}while(a);
		while(top) putchar(sta[--top]+48);
		putchar(b);
		return ;
	}
}
using namespace FastIO;

int n,m,s,A[MAXN],B[MAXN],lstA[MAXN],lstB[MAXN],p[MAXW],kmp[MAXN],ans[MAXN],cnt;

int main()
{
	n=_r(),m=_r(),s=_r();
	for(int i=1;i<=n;i++) A[i]=_r();
	for(int i=1;i<=m;i++) B[i]=_r();
	for(int i=1;i<=n;i++) lstA[i]=p[A[i]],p[A[i]]=i;
	memset(p,0,sizeof(p));
	for(int i=1;i<=m;i++) lstB[i]=p[B[i]],p[B[i]]=i;
	
	for(int i=2;i<=m;i++){
		kmp[i]=kmp[i-1];
		while(kmp[i] && max(lstB[i]-i+kmp[i]+1,0)!=lstB[kmp[i]+1]) kmp[i]=kmp[kmp[i]];
		if(max(lstB[i]-i+kmp[i]+1,0)==lstB[kmp[i]+1]) kmp[i]++;
	}
	for(int i=1,j=0;i<=n;i++){
		while(j && (j==m || max(lstA[i]-i+j+1,0)!=lstB[j+1])) j=kmp[j];
		if(max(lstA[i]-i+j+1,0)==lstB[j+1]) j++;
		if(j==m){
			int flag=1,lst=0;
			for(int j=1;j<=s;j++){
				if(p[j]==0) continue;
				if(lst && A[i-m+p[lst]]>=A[i-m+p[j]]){
					flag=0;
					break;
				}
				lst=j;
			}
			if(flag) ans[++cnt]=i-m+1;
		}
	}
	
	_w(cnt,'\n');
	for(int i=1;i<=cnt;i++) _w(ans[i],'\n');
	return 0;
}
```

---

## 作者：NATO (赞：0)

你说得对，但是为什么要动脑把题目转化成离散化呢？

#### 思路浅析：

强行维护所有偏序关系，容易想到使用哈希压缩信息，考虑如何压缩偏序关系的信息。对于 $t$ 的一组偏序关系 $i,j$，我们首先考虑如何体现位置的独特性，首先 $base^{i+j}$ 这样的东西显然是会重的，于是考虑用两个不同的 $base$ 之积表示，即 $base^i\times {base_2}^j$，这是不会重的，对于 $>,=,<$ 三种偏序关系，可以对应乘上 ${base_3}^2,base_3,1$ 来进行区分。

从前往后扫 $t$ 计算上述哈希，发现加一个字符需要维护 $0,1,...,25$ 每个数的所有出现位置的 $base_2$ 的哈希，整体乘上一个 $base_2$ 即可变成到当前位置的次方，同时给之前的哈希值乘上 $base$ 以维护 $base^i$，然后按 $0,1,...,25$ 与当前数的大小关系加上哈希值即可。

得到 $t$ 的哈希值后扫 $s$，加数同上，为了长度为 $m$ 需要支持删最后一个字符，发现需要维护 $0,1,...,25$ 每个数的所有出现位置的 $base$ 的哈希，同上维护即可，按哈希压缩的方式减去它与其它位置偏序关系的贡献即可，建议配合代码实践理解。

时间复杂度 $O(vn)$，其中 $v$ 是值域，为 $26$。

##### 参考代码：


```cpp
#include<bits/stdc++.h>
#define ll long long
#define un unsigned
using namespace std;
ll n,m;
ll s[1000005],t[1000005];
un ll bs=19260817;
un ll bs2=19260803;
un ll bs3=218479;
un ll cnt[26],cot[26];
ll ans[1000005];
un ll qpow(un ll a,ll b)
{
	un ll res=1;
	while(b)
	{
		if(b&1)res=res*a;
		a=a*a;b>>=1;
	}
	return res;
}
int main()
{
//	freopen("youran.in","r",stdin);
//	freopen("youran.out","w",stdout);
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	ll nu;
	cin>>n>>m>>nu;
	for(ll i=1;i<=n;++i)cin>>s[i];
	for(ll i=1;i<=m;++i)cin>>t[i];
	if(n<m)
	{
		cout<<0;return 0;
	}
	un ll tv=0;
	for(ll i=m;i>=1;--i)
	{
		for(ll j=0;j<26;++j)cnt[j]*=bs3;
		un ll now=0;
		for(ll j=0;j<t[i];++j)now+=cnt[j];now*=bs2;
		now+=cnt[t[i]];now*=bs2;
		for(ll j=t[i]+1;j<26;++j)now+=cnt[j];
		tv=(tv*bs*bs3+now);
		++cnt[t[i]];
	}
	memset(cnt,0,sizeof(cnt));
	un ll sv=0;
	for(ll i=n;i>=n-m+1;--i)
	{
		for(ll j=0;j<26;++j)cnt[j]*=bs3,cot[j]*=bs;
		un ll now=0;
		for(ll j=0;j<s[i];++j)now+=cnt[j];now*=bs2;
		now+=cnt[s[i]];now*=bs2;
		for(ll j=s[i]+1;j<26;++j)now+=cnt[j];
		sv=(sv*bs*bs3+now);
		++cnt[s[i]];++cot[s[i]];
	}
	ll res=0;
	if(sv==tv)ans[++res]=n-m+1;
	un ll mul=qpow(bs3,m-1),mul2=qpow(bs,m-1);
	for(ll i=n-m;i>=1;--i)
	{
		ll del=i+m;
		cnt[s[del]]-=mul;cot[s[del]]-=mul2;
		for(ll j=0;j<s[del];++j)sv-=cot[j]*mul;
		sv-=bs2*cot[s[del]]*mul;
		for(ll j=s[del]+1;j<26;++j)sv-=cot[j]*mul*bs2*bs2;//减去当前最后一个字符的贡献
		for(ll j=0;j<26;++j)cnt[j]*=bs3,cot[j]*=bs;
		un ll now=0;
		for(ll j=0;j<s[i];++j)now+=cnt[j];now*=bs2;
		now+=cnt[s[i]];now*=bs2;
		for(ll j=s[i]+1;j<26;++j)now+=cnt[j];
		sv=(sv*bs*bs3+now);
		++cnt[s[i]];++cot[s[i]];
		if(sv==tv)ans[++res]=i;
	}
	cout<<res<<'\n';
	for(ll i=res;i;--i)cout<<ans[i]<<'\n';
}//考虑哈希将字符条件压起来
//怎么减去一个字符的贡献？ 
//hash 杀之！ 
```

---

