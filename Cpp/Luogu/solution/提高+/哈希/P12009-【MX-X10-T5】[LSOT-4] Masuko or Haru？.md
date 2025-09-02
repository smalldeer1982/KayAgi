# 【MX-X10-T5】[LSOT-4] Masuko or Haru？

## 题目背景

Shion 作为社团活动后的作业，给 Yotsuba 出了一道数据结构题。

Yotsuba 本来是想用水路查资料的，但是查着查着就去和 Haru 聊天了……

但是还有 1 秒就要到下午 5 点了！Yotsuba 只能去询问 Masuko 这道题怎么做了。

Masuko 当然可以在 1 秒之内解决这道题，她现在想考考你看你能不能 1 秒内解决这道题！

## 题目描述

给你 $n$ 个长度为 $m$ 的 01 串。

区间二元组的定义为满足 $1\le l\le r\le m$ 的二元组 $(l,r)$。

区间集合的定义为区间二元组组成的集合。

定义 01 串 $a$ 关于区间集合 $S$ 的一次变化为任选一个区间二元组 $(l,r)\in S$，$\forall i\in[l,r],a_i\gets a_i\oplus 1$（$\oplus$ 代表二进制按位异或）。

定义 01 串 $a$ 和 $b$ 在区间集合 $S$ 下等价为 $a$ 可以在经过任意次关于 $S$ 的变化后变为 $b$。

刚开始时 $S=\emptyset$。

一共有 $q$ 次操作，每次操作都为插入操作或询问操作。

插入操作为给定一个区间二元组 $(l,r)$，$S\gets S\cup \{(l,r)\}$。

询问操作为给定 $x,y$，你需要判断第 $x$ 个 01 串和第 $y$ 个 01 串是否关于区间集合 $S$ 等价。




## 说明/提示

**【样例解释 #1】**

每个 01 串初始形如：

`10011`，  
`11001`。

- 第一次询问：此时集合 $S$ 为空。两个 01 串显然不同。
- 第二次询问：此时集合 $S$ 为 $\{(2,3)\}$，则第一个串只能变成 `10011` 或 `11111`，无法变得相同，故不等价。
- 第三次询问：此时集合 $S$ 为 $\{(2,3),(3,4)\}$，依次进行 $(2,3)$ 变换和 $(3,4)$ 变换即可变为第二个串。故等价。

**【数据范围】**

**本题采用捆绑测试。**

- 子任务 1（17 分）：$n,m\le 10$，$q\le 20$。
- 子任务 2（14 分）：$l=r$。
- 子任务 3（16 分）：$l=r-1$。
- 子任务 4（13 分）：插入操作不超过 $5000$ 次。
- 子任务 5（21 分）：所有的插入操作在所有的询问操作之前。
- 子任务 6（19 分）：无特殊性质。

对于全部的数据，$1\le q,n,m\le 5\times 10^6$，$n\times m\le 10^7$，$1\le l\le r\le m$，$1\le x,y\le n$，$op\in\{1,2\}$。

## 样例 #1

### 输入

```
2 5 5
1001111001
2 1 2
1 2 3
2 1 2
1 3 4
2 1 2```

### 输出

```
Haru
Haru
Masuko```

## 样例 #2

### 输入

```
10 10 20
1110001000101011110100110000110111001111111110111101001111011111011101000000000111110100010000100110
2 2 1
2 9 6
2 6 10
2 1 1
2 3 2
1 7 9
2 10 10
2 10 4
1 1 7
1 8 8
1 2 3
1 2 7
2 1 9
2 6 1
1 1 3
2 10 7
1 2 4
2 9 1
1 3 7
1 1 5```

### 输出

```
Haru
Haru
Haru
Masuko
Haru
Masuko
Haru
Haru
Haru
Haru
Haru
```

# 题解

## 作者：Xy_top (赞：5)

这题应该有紫了吧，但是不错的一道题。

因为只有 ``01`` 状态，所以这题大概率和奇偶性有关，于是将两串异或，得到对于每一个位置最终的奇偶性要求。题意转化为给定若干个区间，对于一个初始全为 $0$ 的序列，能否通过区间加操作使得最后每一个位置为奇数或者偶数。

还是不好做，区间操作显然可以转成差分，由于只和奇偶性有关，所以对于 $a_l + 1$ 再对于 $a_{r + 1} - 1$ 就是对于两者都 $+1$。对于异或序列也去差分一下，问题转化为双点加以及给定目标序列奇偶性。

接下来这一步有点困难，需要一些直觉。由于这道题只和奇偶性有关，所以我们将上述得到的若干组 $[l, r + 1]$ 连边。对于一个连通块内，如果想要改变此连通块内偶数个节点的奇偶性，那么是可行的，否则不可行，证明可行可以构造一种万能的方案。

也就是说异或序列的一位如果为 ``1`` 代表需要改变奇偶性，为 ``0`` 代表不需要。那么所有连通块内需要改变奇偶性的节点个数必须都是偶数。换而言之，我们用来异或的两个串如果在每个连通块内需要改变奇偶性的节点的个数的奇偶性相同，那么答案是 ``Yes``，而先异或后差分与先差分后异或是等价的，于是这步转化显然正确。并且解决了将两个串异或起来会超时的问题。

于是我们发现本题需要用到并查集来合并连通块，最后一步的难点在于如果维护上面的那个东西。

通过 [P8026](https://www.luogu.com.cn/problem/P8026) 的套路，我们可以给每一个连通块赋一个随机的权值，一个串的权值就是连通块权值的和，连通块需满足在这个连通块内需要改变奇偶性的节点个数为奇数。如果两个串的权值和相同，那么这两个串大概率可以互相转化。

还有一些细节，在询问那里，看代码：


```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, m, q;
char s[10000005];
int fa[10000005], val[10000005], vall[10000005];
bool f[10000005], ff[10000005];
mt19937 mr (20090426);
int find (int x) {
	if (fa[x] == x) return x;
	return fa[x] = find (fa[x]);
}
void solve () {
	For (i, 1, 10000001) fa[i] = i;
	For (i, 1, 10000001) val[i] = mr () % 1000000000;
	scanf ("%lld%lld%lld%s", &n, &m, &q, s + 1);
	For (i, 1, n) {
		int k = (i - 1) * m;
		if (s[k + 1] == '1') {
			f[k + 1] = 1;
			vall[i] += val[1];
		}
		foR (j, m, 2) if (s[k + j] != s[k + j - 1]) {
			f[k + j] = 1;
			vall[i] += val[j];
		}
	}/*11010   10101   01111*/
	while (q --) {
		int op, x, y;
		scanf ("%lld%lld%lld", &op, &x, &y);
		if (op == 1) {
			++ y;
			int fx = find (x), fy = find (y), tt = mr () % 1000000000;
			if (fx != fy) {
				For (i, 1, n) {
					bool f1, f2;
					if (fx != m + 1) f1 = f[(i - 1) * m + fx];
					else f1 = ff[i];
					if (fy != m + 1) f2 = f[(i - 1) * m + fy];
					else f2 = ff[i];
					vall[i] -= f1 * val[fx] + f2 * val[fy];
					f2 ^= f1;
					if (f2) vall[i] += tt;
					if (fy != m + 1) f[(i - 1) * m + fy] = f2;
					else ff[i] = f2;
				}
				fa[fx] = fy;
				val[fy] = tt;
			}
		} else {
			if (vall[x] == vall[y] || abs (vall[x] - vall[y]) == val[find (m + 1)]) printf ("Masuko\n");
			else printf ("Haru\n");
		}
	}
}
signed main () {
	int _ = 1;
//	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：良心WA题人 (赞：3)

先不考虑修改操作。首先区间的变化有点难受，考虑差分一下变成两个点反转。问题转化为了可以同时反转某两个点，问两个串能否一样。

因为异或操作是可逆的，所以将能一次操作完成一样的两个状态两两连边后，是一个无向图，问题等价于判两个是否在一个连通块内。所以可以将问题转化为判两个串是否可以同时转化为一个连通块内有特征的字符串。不妨令这个有特征的字符串为可以到达的最小的字符串。

对于这样的一次变化两个的操作，一个普遍的套路是将变化的两个位置连边建一个图，问题转化为每个点有一个权值，每次可以选择一条边反转连接的两个点的权值。发现对于图上任意一条路径，如果同时对这条路径进上的所有边进行反转操作，只会反转起点和终点。从高位到低位考虑，如果当前位能够通过一些操作使得只修改了低位不修改高位后变成 $0$ 则会产生修改。根据前面的分析，只要当前点所处的连通块内有编号比它大的点则一定可以产生修改，否则当前点的权值确定。

可以发现，带上修改操作之后，也就是可以合并两个连通块。对于较小的一个连通块最大值可以进行变化。连通块的合并考虑并查集即可。如果只对产生了合并的修改操作对每个串进行修改，则修改数是 $O(n\times m)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace fastio
{
    const int bufl=1<<20;
    const double base1[16]={1,1e-1,1e-2,1e-3,1e-4,1e-5,1e-6,1e-7,1e-8,1e-9,1e-10,1e-11,1e-12,1e-13,1e-14,1e-15};
    const double base2[16]={1,1e1,1e2,1e3,1e4,1e5,1e6,1e7,1e8,1e9,1e10,1e11,1e12,1e13,1e14,1e15};
    struct IN{
        FILE *IT;char ibuf[bufl],*is=ibuf,*it=ibuf;
        IN(){IT=stdin;}IN(char *a){IT=fopen(a,"r");}
        inline char getChar(){if(is==it){it=(is=ibuf)+fread(ibuf,1,bufl,IT);if(is==it)return EOF;}return *is++;}
        template<typename Temp>inline void getInt(Temp &a){a=0;int b=0,c=getChar();while(c<48||c>57)b^=(c==45),c=getChar();while(c>=48&&c<=57)a=(a<<1)+(a<<3)+c-48,c=getChar();if(b)a=-a;}
        template<typename Temp>inline void getDouble(Temp &a){a=0;int b=0,c=getChar(),d=0;__int128 e=0,f=0;while(c<48||c>57)b^=(c==45),c=getChar();while(c>=48&&c<=57)e=(e<<1)+(e<<3)+c-48,c=getChar();if(c==46){c=getChar();while(c>=48&&c<=57)d++,f=(f<<1)+(f<<3)+c-48,c=getChar();}a=e+base1[d]*f;if(b)a=-a;}
        IN& operator>>(char &a){a=getChar();return *this;}
        IN& operator>>(char *a){do{*a=getChar();}while(*a<=32);while(*a>32)*++a=getChar();*a=0;return *this;}
        IN& operator>>(string &a){char b=getChar();while(b<=32)b=getChar();while(b>32)a+=b,b=getChar();return *this;}
        IN& operator>>(int &a){getInt(a);return *this;}
        IN& operator>>(long long &a){getInt(a);return *this;}
        IN& operator>>(unsigned long long &a){getInt(a);return *this;}
        IN& operator>>(__int128 &a){getInt(a);return *this;}
        IN& operator>>(float &a){getDouble(a);return *this;}
        IN& operator>>(double &a){getDouble(a);return *this;}
        IN& operator>>(long double &a){getDouble(a);return *this;}
    };
    struct OUT{
        FILE *IT;char obuf[bufl],*os=obuf,*ot=obuf+bufl;int Eps;long double Acc;
        OUT(){IT=stdout,Eps=6,Acc=1e-6;}OUT(char *a){IT=fopen(a,"w"),Eps=6,Acc=1e-6;}
        inline void ChangEps(int x=6){Eps=x;}
        inline void flush(){fwrite(obuf,1,os-obuf,IT);os=obuf;}
        inline void putChar(int a){*os++=a;if(os==ot)flush();}
        template<typename Temp>inline void putInt(Temp a){if(a<0){putChar(45);a=-a;}if(a<10){putChar(a+48);return;}putInt(a/10);putChar(a%10+48);}
        template<typename Temp>inline void putLeading(Temp a,int b){if(!b)return;putLeading(a/10,b-1);putChar(a%10+48);}
        template<typename Temp>inline void putDouble(Temp a){if(a<0){putChar(45);a=-a;}__int128 b=a;putInt(b);a-=b;a*=base2[Eps];b=a+Acc;putChar(46);putLeading(b,Eps);}
        OUT& operator<<(char a){putChar(a);return *this;}
        OUT& operator<<(char *a){while(*a>32)putChar(*a++);return *this;}
        OUT& operator<<(string a){for(auto c:a)putChar(c);return *this;}
        OUT& operator<<(int a){putInt(a);return *this;}
        OUT& operator<<(long long a){putInt(a);return *this;}
        OUT& operator<<(unsigned long long a){putInt(a);return *this;}
        OUT& operator<<(__int128 a){putInt(a);return *this;}
        OUT& operator<<(float a){putDouble(a);return *this;}
        OUT& operator<<(double a){putDouble(a);return *this;}
        OUT& operator<<(long double a){putDouble(a);return *this;}
        ~OUT(){flush();}
    };
}
using fastio::IN;
using fastio::OUT;
IN fin;
OUT fout;
typedef unsigned long long ull;
const int NN=1e7+4,P=131;
char s[NN];
int fa[NN],n,m;
ull hsh[NN],pk[NN];
int get(int x,int y)
{
	return (x-1)*m+y;
}
int find(int u)
{
	return fa[u]==u?u:fa[u]=find(fa[u]);
}
void rev(int id,int p)
{
	int x=get(id,p);
	hsh[id]-=pk[p-1]*s[x];
	if(s[x]=='1')
		s[x]='0';
	else
		s[x]='1';
	hsh[id]+=pk[p-1]*s[x];
}
int main()
{
	int q;
	fin>>n>>m>>q>>s+1;
	for(int i=1;i<=n;i++)
	{
		for(int j=m;j>1;j--)
		{
			s[get(i,j)]=s[get(i,j)]==s[get(i,j-1)]?'0':'1';
			hsh[i]=hsh[i]*P+s[get(i,j)];
		}
		hsh[i]=hsh[i]*P+s[get(i,1)];
	}
	pk[0]=1;
	for(int i=1;i<=m+1;i++)
	{
		fa[i]=i;
		pk[i]=pk[i-1]*P;
	}
	while(q--)
	{
		int opt;
		fin>>opt;
		if(opt==1)
		{
			int l,r;
			fin>>l>>r;
			r++;
			l=find(l),r=find(r);
			if(l!=r)
			{
				if(l>r)
					swap(l,r);
				fa[l]=r;
				for(int i=1;i<=n;i++)
					if(s[get(i,l)]=='1')
					{
						rev(i,l);
						if(r<=m)
							rev(i,r);
					}
			}
		}
		else
		{
			int x,y;
			fin>>x>>y;
			fout<<(hsh[x]==hsh[y]?"Masuko":"Haru")<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：dream10 (赞：0)

### Hint 1

将 01 序列做差分，长度变为 $m+1$，区间修改变为两个单点修改。

$01101\rightarrowtail 011011$

### Hint 2

如果位置视为点，将一对单点修改视为一条边，那么一个联通块里任意两个点都可以同时异或（找到路径，每条边异或）。

### Solution

对于修改，使用数据结构维护联通性。

对于询问，将两个串的差分序列异或起来，发现就是每个联通块里面的异或和是 $0$。

然而这不好做，但是发现联通性最多改变 $m$ 次，每次可以对每个串进行维护。具体的维护方式就是找一个代表员记录联通块的异或和，然后询问比较哈希值。

```
#include<bits/stdc++.h>
using namespace std;
template<typename T>
void read(T &a){
    #define gc getchar()
    char c;a=0;int f=1;
    while(!isdigit(c=gc))if(c=='-')f=-1;
    do a=a*10+c-'0';
    while(isdigit(c=gc));
    a*=f;
}
template<typename T>
void write(T a){
    if(a<0)putchar('-'),a=-a;
    if(a>=10)write(a/10);
    putchar('0'+a%10);
}
char GC(){
    char c=getchar();
    while(c<=32)c=getchar();
    return c;
}
template<typename T>
void chmin(T &x,T y){if(x>y)x=y;}
template<typename T>
void chmax(T &x,T y){if(x<y)x=y;}
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef pair<int,int> PII;
typedef pair<ll,int> PLI;
typedef __int128 lll;
mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

int n,m,q;
const int MAXN=5000010;
const int MAXS=15000010;
char _s[MAXS];
char& s(const int &i,const int &j){return _s[(i-1)*m+j];}
int ufa[MAXS];
int gf(const int &x){return ufa[x]==x?x:ufa[x]=gf(ufa[x]);}
ull hsh[MAXN],pw[MAXN];
void merge(int id,int x,int y){
    if(s(id,x)=='1'){
        hsh[id]-=pw[x];
        s(id,x)='0';
        if(y<=m){
            if(s(id,y)=='0'){
                s(id,y)='1';
                hsh[id]+=pw[y];
            }else{
                s(id,y)='0';
                hsh[id]-=pw[y];
            }
        }
    }
}
signed main(){
    pw[0]=1;pw[1]=97;
    for(int i=2;i<=5000000;++i)pw[i]=pw[i-1]*pw[1];
    cin>>n>>m>>q;
    scanf("%s",_s+1);
    for(int i=1;i<=m+1;++i)ufa[i]=i;
    for(int i=1;i<=n;++i){
        for(int j=m;j>=2;--j)
            s(i,j)='0'+(s(i,j)!=s(i,j-1));
        for(int j=1;j<=m;++j)
            if(s(i,j)=='1')
                hsh[i]+=pw[j];
    }
    int op,x,y;
    while(q--){ 
        read(op);read(x),read(y);
        if(op==1){
            y++;
            x=gf(x),y=gf(y);
            if(x>y)swap(x,y);
            if(x!=y){
                for(int i=1;i<=n;++i)
                    merge(i,x,y);
                ufa[x]=y;
            }
        }else{
            if(hsh[x]==hsh[y])puts("Masuko");
            else puts("Haru");
        }
    }
    return 0;
}
```

---

## 作者：modfish_ (赞：0)

## 思路
考虑先对原来的 $n$ 个序列差分，这样区间 $(l,r)$ 异或转化为两个单点 $(l,r+1)$ 异或。

假定当前插入了一对新的单点异或 $(x,y)$，且存在另一个单点异或 $(x,z)$，那么不难发现：$(x,y)$ 等价于 $(y,z)$。同理，若存在另一个单点异或 $(w,y)$，那么 $(x,y)$ 等价于 $(w,x)$。

意思就是说，如果插入的 $(x,y)$ 中的 $x$ 或 $y$ 已经作为单点异或对中的一个出现过了，那么可以将其换成另一个。

我们希望达成这种性质：对于每一个位置 $x$，它至多在单点异或对中出现两次，且一次作为较大值出现，一次作为较小值出现。

这样的话，我们可以把每一个单点异或对的较小值向较大值连边，最终将形成一个树形结构。容易发现，我们可以任意地操控这个树上的除根以外的任意一个点的点权，只要从叶子开始向上层层贪心考虑即可。

这样的话，不妨将每一个序列的除根以外的这些位置都变成 $0$，这样，两个序列等价当且仅当此时它们完全相等。

至于插入时如何维护这个树状结构，可以视作一开始每个点自成一树。每次加入一个单点异或对 $(x,y)$ 时，若它们中有一个不是根（设为 $x$），根据前面推得的理论，这个单点异或对等效于 $(fa_x,y)$，其中 $fa_x$ 是 $x$ 在树上的父亲。对 $y$ 同理，于是这两个节点在树上无论怎么跳来跳去，结果都是等价的。

不妨令它们都跳到树根，若它们在同一棵树上，说明它等价于 $(r,r)$，显然是无效的。否则，它等价于 $(r_x,r_y)$，把其中较小的向较大的连边，即可得到新树。顺带把每个序列中较小的（设为 $r_x$）所在的位置变成 $0$ 即可。

使用并查集维护树的形态，哈希判断是否等价，复杂度为 $O(q\alpha(n)+nm)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll __int128

using namespace std;

const int maxn = 5e6 + 5;
const ll p = (ll)1e18 + 3, bas = 1331;

char s[maxn << 1];
int fa[maxn], sz[maxn], rt[maxn];
ll hsh[maxn], bp[maxn];

inline int find(int x){
    if(fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}
inline void merge(int x, int y){
    if(x == y) return;
    if(sz[x] < sz[y]) swap(x, y);
    fa[y] = x, sz[x] += sz[y], rt[x] |= rt[y];
}
inline int read(){
    int x = 0;
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    return x;
}

int main(){
    int n = read(), m = read(), q = read();
    scanf("%s", s + 1);
    bp[0] = 1;
    for(int i = 1; i <= m + 1; ++ i) fa[i] = i, sz[i] = 0, rt[i] = i, bp[i] = bp[i - 1] * bas % p;
    for(int i = 1; i <= n; ++ i){
        for(int j = m; j > 1; -- j) if(j > 1) s[(i - 1) * m + j] = s[(i - 1) * m + j] == s[(i - 1) * m + j - 1] ? '0' : '1';
        hsh[i] = 0;
        for(int j = 1; j <= m; ++ j) hsh[i] = (hsh[i] * bas % p + s[(i - 1) * m + j]) % p;
    }
    while(q --){
        int op = read(), l = read(), r = read();
        if(op == 1){
            l = find(l), r = find(r + 1);
            if(l == r) continue;
            if(rt[l] > rt[r]) swap(l, r);
            int x = rt[l], y = rt[r];
            rt[l] = 0, merge(l, r);
            for(int i = 1; i <= n; ++ i){
                if(s[(i - 1) * m + x] == '1'){
                    hsh[i] = (hsh[i] + p - bp[m - x] * s[(i - 1) * m + x] % p) % p;
                    s[(i - 1) * m + x] = '0';
                    hsh[i] = (hsh[i] + bp[m - x] * s[(i - 1) * m + x] % p) % p;
                    if(y <= m){
                        hsh[i] = (hsh[i] + p - bp[m - y] * s[(i - 1) * m + y] % p) % p;
                        s[(i - 1) * m + y] = s[(i - 1) * m + y] == '1' ? '0' : '1';
                        hsh[i] = (hsh[i] + bp[m - y] * s[(i - 1) * m + y] % p) % p;
                    }
                }
            }
        }else{
            printf(hsh[l] == hsh[r] ? "Masuko\n" : "Haru\n");
        }
    }
    return 0;
}
```

---

