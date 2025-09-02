# [ARC077E] guruguru

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc077/tasks/arc077_c

snuke 君は明るさを $ m $ 段階に切り替えられる照明を買いに来ました。 この照明の 明るさは $ 1 $ 以上 $ m $ 以下の整数で表され、 リモコンに付いた $ 2 $ 種類のボタンで明るさを切り替えます。

$ 1 $ つめのボタンは「順送り」ボタンで、 明るさを $ 1 $ 増やすことができます。ただし、ボタンを押す前の明るさが最大の $ m $ である場合には、 明るさは $ 1 $ になります。

$ 2 $ つめのボタンは「お気に入り」ボタンで、 購入時に決めたお気に入りの明るさ $ x $ に切り替えることが出来ます。

snuke 君はお気に入りの明るさ $ x $ を、できるだけ効率的に明るさが切り替えられるように設定しようと考えました。 snuke 君は今後 $ n-1 $ 回明るさを切り替える予定で、$ i $ 回目には明るさ $ a_i $ から 明るさ $ a_{i+1} $ に切り替えようと計画しています。 最初、明るさは $ a_1 $ です。 ボタンを押す回数の合計が最小になるようにお気に入りの明るさ $ x $ を決めた時の ボタンを押す回数を求めて下さい。

## 说明/提示

### 制約

- $ 2\ \leq\ n,m\ \leq\ 10^5 $
- $ 1\ \leq\ a_i\leq\ m $
- $ a_i\ \neq\ a_{i+1} $
- $ n,m,a_i $ は整数である。

### Sample Explanation 1

お気に入りの明るさを $ 1,2,3,4,5,6 $ のそれぞれに設定したときのボタンを押す最小回数はそれぞれ $ 8,9,7,5,6,9 $ 回です。 よって、お気に入りの明るさを $ 4 $ に設定したときにボタンを押す回数の合計を最小に出来ます。 お気に入りの明るさを $ 4 $ に設定したときの切り替え方は以下のとおりです。 - $ 1 $ 回目には、お気に入りボタンを $ 1 $ 回押した後、順送りボタンを $ 1 $ 回押します。 - $ 2 $ 回目には、順送りボタンを $ 2 $ 回押します。 - $ 3 $ 回目には、お気に入りボタンを $ 1 $ 回押します。

## 样例 #1

### 输入

```
4 6
1 5 1 4```

### 输出

```
5```

## 样例 #2

### 输入

```
10 10
10 9 8 7 6 5 4 3 2 1```

### 输出

```
45```

# 题解

## 作者：sky_of_war (赞：10)

对于从$a$走到$b$来说

 - 若选择的$x=a $或$ a+1$，那么不会使步数减少

 - 若选择的$x=a+2$，会使步数减少$1$

 - 若选择的$x=a+3$，会使步数减少$2$

问题就变成了给区间$[l,r]$加首项为$1$，公差为$1$的等差数列

也就是给位置$l $的元素加$1$，位置$l+1$的元素加$2$，位置$l+2$的元素加$3$……位置$r$的元素加$r-l+1$

令$\text{cnt}[l]$加$1$,$\text{cnt}[r+1]$减$r-l+1+1$，$\text{cnt}[r+2]$减$r-l+1$

对$\rm cnt$做一遍前缀和，得到差分数组

再做一遍前缀和，可以得到本身的值

这个被称为二阶差分

两遍前缀和后的$\rm cnt$数组就是把位置选在$x$，会使原本的步数减少多少

取最大的一个，总步数减它就是答案

时间复杂度$O(n)$

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 1e5 + 10;
int n, m, first[MAXN], tot, d[MAXN], s, t;

struct edge { int from, v, w; } e[20 * MAXN];
struct Node
{
	int x, d;
	bool operator <(const Node &b)const
	{
		return d > b.d;
	}
}cyc;
priority_queue<Node> q;
inline void insert(int u, int v, int w)
{
	tot++; e[tot].v = v; e[tot].w = w; e[tot].from = first[u]; first[u] = tot;
}
int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (register int i = 1; i <= n; i++)
		for (register int j = 0; j <= 9; j++)insert(i, ((i - 1) * 10 + j) % n + 1, j);
	for (register int j = 1; j <= 9; j++) insert(0, j + 1, j);
	s = 0; t = 1;
	memset(d, 0x3f, sizeof d);
	d[s] = 0; q.push((Node) { s, d[s] });
	while (!q.empty())
	{
		cyc = q.top(); q.pop();
		if (cyc.d != d[cyc.x])continue;
		register int x = cyc.x;
		for (register int i = first[x]; i; i = e[i].from)
			if (d[e[i].v] > d[x] + e[i].w)
			{
				d[e[i].v] = d[x] + e[i].w;
				q.push((Node) { e[i].v, d[e[i].v] });
			}
	}
	return cout << d[t], 0;
}
```

---

## 作者：Ebola (赞：6)


可以将给定的数列看作若干个线段$[a_i,a_{i+1}]$，若设定点在这个线段内（模意义下），则相当于可以从$a_i$跳到设定点，然后再走到$a_{i+1}$

于是我们可以将所有线段按左端点排序，然后枚举设定点的位置。对于枚举到的位置，将包含它的线段全部加入即可。这相当于一个扫描线的过程，扫到一个点，将左端点位于该位置的线段全部加入，右端点位于该位置的线段全部删除。然后维护一个当前答案以及当前加入的线段数量即可

```cpp
#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

typedef long long LL;
const int N=100010;
struct Seg{int l,r,extra;} seg[N<<1];
vector<Seg> R[N];
int n,m,a[N],tot=0;

int main()
{
    int cross=0,p=1;
    LL ans=INT64_MAX,cur=0;
    n=read();m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<n;i++)
        if(a[i]<a[i+1])
        {
            seg[++tot]={a[i],a[i+1],0};
            R[a[i+1]].push_back(seg[tot]);
            cur+=a[i+1]-a[i];
        }
        else
        {
            seg[++tot]={a[i],m,0};
            R[m].push_back(seg[tot]);
            seg[++tot]={0,a[i+1],m-a[i]};  //模意义下，[a[i],m]也在该线段左边，算入额外长度
            R[a[i+1]].push_back(seg[tot]);
            cur+=a[i+1]+m-a[i];
        }
    sort(seg+1,seg+1+tot,[](Seg a,Seg b){return a.l<b.l;});
    for(int i=0;i<=m;i++)
    {
        cur-=cross;  //所有已加入的线段都可以往右多跳一步了
        ans=min(ans,cur);
        for(Seg s : R[i])
        {
            cur+=s.extra+i-s.l-1;  //删除线段
            cross--;  //维护线段数量
        }
        while(p<=tot&&seg[p].l<=i)
        {
            Seg s=seg[p];
            cur-=s.extra+i-s.l-1;  //加入线段
            cross++;p++;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```





---

## 作者：MaxBlazeResFire (赞：4)

### 大家好，我非常喜欢暴力数据结构，于是我只用桶和前缀和通过了这道题。

预处理 $8$ 种桶与其前缀和，求答案的式子分类讨论。

$\displaystyle B_1(x)=\sum_{i=2}^n[a_{i-1}<a_i][a_{i-1}=x]a_{i-1}$

$\displaystyle B_2(x)=\sum_{i=2}^n[a_{i-1}<a_i][a_{i-1}=x]$

$\displaystyle B_3(x)=\sum_{i=2}^n[a_{i-1}<a_i][a_i=x]a_{i-1}$

$\displaystyle B_4(x)=\sum_{i=2}^n[a_{i-1}<a_i][a_i=x]$

$\displaystyle B_5(x)=\sum_{i=2}^n[a_{i-1}>a_i][a_{i-1}=x]a_{i-1}$

$\displaystyle B_6(x)=\sum_{i=2}^n[a_{i-1}>a_i][a_{i-1}=x]$

$\displaystyle B_7(x)=\sum_{i=2}^n[a_{i-1}>a_i][a_i=x]a_{i-1}$

$\displaystyle B_8(x)=\sum_{i=2}^n[a_{i-1}>a_i][a_i=x]$

$\displaystyle C_i(x)=\sum_{j=1}^xB_i(j)$

$\displaystyle ans(X)=\begin{cases}
a_i-a_{i-1},X\leq a_{i-1}<a_i\\
a_i-a_{i-1},a_{i-1}<a_i<X\\
a_i-X+1,a_{i-1}<X\leq a_i\\
a_i-X+1,X\leq a_i<a_{i-1}\\
a_i+M-X+1,a_i<a_{i-1}<X\\
a_i+M-a_{i-1},a_i<X\leq a_{i-1}
\end{cases}$

$\displaystyle=\left(\sum_{i=2}^n[a_{i-1}<a_i](a_i-a_{i-1})+[a_i<a_{i-1}](a_i+M)\right)+Part_1-Part_2+Part_3+Part_4$

$\displaystyle Part_1=\sum_{i=2}^n[a_{i-1}<X\leq a_i](a_{i-1}-X+1)=C_1(X-1)-C_3(X-1)+(1-X)(C_2(X-1)-C_4(X-1))$

$\displaystyle Part_2=\sum_{i=2}^n[a_i<X\leq a_{i-1}]a_{i-1}=\left(C_5(M)-C_5(X-1)\right)-(C_7(M)-C_7(X-1))$

$\displaystyle Part_3=\sum_{i=2}^n[a_i<a_{i-1}<X](1-X)=C_6(X-1)\times(1-X)$

$\displaystyle Part_4=\sum_{i=2}^n[X\leq a_i<a_{i-1}](1-X-M)=\left(C_8(M)-C_8(X-1)\right)\times(1-M-X)$

$\displaystyle Ans=\min_{i=1}^M\{ans(i)\}$.

时间复杂度 $O(n)$.

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200005

int n,m,a[MAXN] = {0},mp[MAXN] = {0},Mp[MAXN] = {0},ma[MAXN] = {0},Ma[MAXN] = {0},Sp[MAXN] = {0},Sp2[MAXN] = {0};
int pre1[MAXN] = {0},pre2[MAXN] = {0},pre3[MAXN] = {0},pre4[MAXN] = {0},pre5[MAXN] = {0},pre6[MAXN] = {0},pre7[MAXN] = {0},pre8[MAXN] = {0};

inline int chk( int X ){
	int Ans = 0;
	Ans += pre1[X - 1] + ( 1 - X ) * pre2[X - 1] - ( pre3[X - 1] + ( 1 - X ) * pre4[X - 1] );
	Ans += -( pre5[m] - pre5[X - 1] ) + ( pre7[m] - pre7[X - 1] );
	Ans += pre6[X - 1] * ( 1 - X );
	Ans += ( pre8[m] - pre8[X - 1] ) * ( 1 - m - X );
	return Ans;
}

signed main(){
	scanf("%lld%lld",&n,&m);
	for( int i = 1 ; i <= n ; i ++ ) scanf("%lld",&a[i]);
	for( int i = 2 ; i <= n ; i ++ ){
		if( a[i - 1] < a[i] ) mp[a[i - 1]] ++,Ma[a[i]] ++,Sp[a[i]] += a[i - 1];
		else Mp[a[i - 1]] ++,ma[a[i]] ++,Sp2[a[i]] += a[i - 1];
 	}
 	for( int i = 1 ; i <= m ; i ++ ){
 		pre1[i] = pre1[i - 1] + i * mp[i];
 		pre2[i] = pre2[i - 1] + mp[i];
 		pre3[i] = pre3[i - 1] + Sp[i];
 		pre4[i] = pre4[i - 1] + Ma[i];
 		pre5[i] = pre5[i - 1] + i * Mp[i];
 		pre6[i] = pre6[i - 1] + Mp[i];
 		pre7[i] = pre7[i - 1] + Sp2[i];
 		pre8[i] = pre8[i - 1] + ma[i];
 	}
	int Ans = 1e18;
	for( int X = 1 ; X <= m ; X ++ ) Ans = min( Ans , chk( X ) );
	for( int i = 2 ; i <= n ; i ++ ){
		if( a[i] > a[i - 1] ) Ans += a[i] - a[i - 1];
		else Ans += a[i] + m;
	}
	printf("%lld\n",Ans);
	return 0;
}
```

---

## 作者：EityDawn (赞：2)

## 思路

提供一种思维难度不高，分块暴力艹的题解。

分析一下发现，$x$ 可以减少操作次数的无非就三种情况

1. $a_{i-1}<x\le a_{i}$，此时减少 $x-a_{i-1}-1$ 步操作。
2. $a_{i-1}>a_i$ 且 $x>a_{i-1}$，此时减少 $x-a_{i-1}-1$ 步操作。
3. $a_{i-1}>a_i$ 且 $x\le a_{i}$，此时减少 $m-a_{i-1}+x-1$ 步操作。

我们把 $a_{i-1}<a_i$ 和 $a_{i-1}>a_{i}$ 的点对分成两类。

对于第 $2$ 种和第 $3$ 种情况，无非就是全局询问第二类满足 $a_{i-1}<x$ 的 $a_{i-1}$ 的个数和和，以及第二类中满足 $x\le a_i \le m$ 的 $a_{i}$ 的个数和相对应的 $a_{i-1}$ 的和。如果记满足关系的个数为 $c$，$a_{i-1}$ 的和为 $sum$，那么第 $2$ 种情况对答案贡献为 $c_2\times (x-1)+sum_2$，第 $3$ 类就是 $c_3\times (m+x-1)+sum_3$。

因为询问的跟值域有关，我们可以用值域分块来简单维护个数与和。

而对于第 $1$ 种情况，$a_{i-1}<x\le a_{i}$，可以认为是二维偏序关系，套路是按照 $a_{i-1}$ 排序搞掉第一维，二分出第二维的询问区间，询问区间内 $a_i\in[x,m]$ 的个数与对应的 $a_{i-1}$ 的和，很容易想到用教主的魔法的套路，分块+二分，块内前缀和来维护。

复杂度分析默认 $n,m$ 同阶。

第 $2$ 类和第 $3$ 类情况复杂度是 $O(n\sqrt n)$ 的，第 $1$ 类情况是 $O(n\log n+n\sqrt n\log{(\sqrt n)})$，综上来看复杂度为 $O(n\sqrt n \log n)$ 的，被 $O(n)$ 正解爆踩。 

### code

```cpp
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<climits>
#include<ctime>
#include<cctype>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define int long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 Int;
template<class T>
inline void read(T &x)
{
    x=0;short w=1;
    char c=getchar();
    while(c<'0'||c>'9')
    {
        if(c=='-') w=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
        x=(x<<3)+(x<<1)+c-'0',c=getchar();
    x=x*w;
}
inline void read(char &x)
{
    x=getchar();
    while(isspace(x))
        x=getchar();
    return;
}
inline void read(char *x)
{
    char c=getchar();
    while(isspace(c)) c=getchar();
    while(!isspace(c)&&~c)
        *(x++)=c,c=getchar();
    *x=0;
}
inline void read(string &x)
{
    char c=getchar();x.clear();
    while(isspace(c)) c=getchar();
    while(!isspace(c)&&~c)
        x.push_back(c),c=getchar();
}
inline void read(double &x)
{
    x=0;short w=1;
    char c=getchar();
    while(c<'0'||c>'9')
    {
        if(c=='-') w=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
        x=x*10+c-'0',c=getchar();
    if(c=='.')
    {
        c=getchar();double f=0.1;
        while(c>='0'&&c<='9')
        {
            x+=(c-'0')*f,f*=0.1;
            c=getchar();
        }
    }
    x=x*w;
}
template<class T>
inline void write(T x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10^'0');
}
inline void write(char c){putchar(c);}
inline void write(string x){for(auto c:x) putchar(c);}
inline void write(char *x){while(*x) putchar(*(x++));}
inline void write(const char *x){while(*x) putchar(*(x++));}
inline void write(double x){printf("%.6lf",x);}
template<class type,class ...T>
inline void read(type &x,T&...y){read(x),read(y...);}
template<class type,class ...T>
inline void write(type x,T ...y){write(x),write(y...);}
const int N=1e5+10,M=350,V=1e5;
int n,m,a[N];
pair<int,int>b[N];
int c[N],d[N];
int fi[N],se[N];
int t=0,k=0;
int Be[N],L[M],R[M],h=0;
int Pos[N],l[N],r[N];
int U[N],id[N],B=0,Cpy[N];
ll Sum[N];
void build(int n)
{
	if(!n) return; 
    int len=sqrt(n);B=(n/len)+bool(n%len);
    for(int i=1;i<=n;i++)
    {
        Pos[i]=(i-1)/len+1;
        if(!l[Pos[i]]) l[Pos[i]]=i;
        r[Pos[i]]=i;
    }
    for(int i=1;i<=B;i++)
    {
        for(int j=l[i];j<=r[i];j++) U[j]=se[j],id[j]=j;
        sort(id+l[i],id+r[i]+1,[&](int x,int y){return U[x]<U[y];});
        for(int j=l[i];j<=r[i];j++) Cpy[j]=U[id[j]];
        for(int j=l[i];j<=r[i];j++) U[j]=Cpy[j];
        Sum[l[i]]=fi[id[l[i]]];
        for(int j=l[i]+1;j<=r[i];j++) Sum[j]=Sum[j-1]+fi[id[j]];
    }
    return;
}
inline ll querySum(int p,int q,int x)
{
	if(p>q) return 0;
    ll res=0;
    if(Pos[p]==Pos[q]){
        for(int i=p;i<=q;i++)
            res+=(se[i]>=x)*fi[i];
    }
    else{
        for(int i=p;i<=r[Pos[p]];i++)
            res+=(se[i]>=x)*fi[i];
        for(int i=l[Pos[q]];i<=q;i++)
            res+=(se[i]>=x)*fi[i];
        for(int i=Pos[p]+1;i<=Pos[q]-1;i++)
        {
            int pos=lower_bound(U+l[i],U+r[i]+1,x)-(U+1);
            if(pos<l[i]) res+=Sum[r[i]];
            else res+=Sum[r[i]]-Sum[pos];
        }
    }
    return res;
}
inline ll queryCnt(int p,int q,int x)
{
	if(p>q) return 0;
    ll res=0;
    if(Pos[p]==Pos[q]){
        for(int i=p;i<=q;i++)
            res+=(se[i]>=x);
    }
    else{
        for(int i=p;i<=r[Pos[p]];i++)
            res+=(se[i]>=x);
        for(int i=l[Pos[q]];i<=q;i++)
            res+=(se[i]>=x);
        for(int i=Pos[p]+1;i<=Pos[q]-1;i++)
            res+=r[i]-(lower_bound(U+l[i],U+r[i]+1,x)-(U+1));
    }
    return res;
}
void build()
{
    int len=sqrt(m);h=(m/len)+bool(m%len);
    for(int i=1;i<=m;i++)
    {
        Be[i]=(i-1)/len+1;
        if(!L[Be[i]]) L[Be[i]]=i;
        R[Be[i]]=i;
    }
    return;
}
struct Block{
    int C[N],Val[N];
    ll Sum[M],Cnt[M];
    Block()
    {
        memset(C,0,sizeof(C));
        memset(Val,0,sizeof(Val));
        memset(Sum,0,sizeof(Sum));
        memset(Cnt,0,sizeof(Cnt));
    }
    void build(int n,int a[],int b[])
    {
        for(int j=1;j<=n;j++)
        {
            ++C[a[j]],Val[a[j]]+=b[j];
            ++Cnt[Be[a[j]]],Sum[Be[a[j]]]+=b[j];
        }
    }
    inline ll querySum(int x)
    {
        ll res=0;
        for(int i=1;i<Be[x];i++)    
            res+=Sum[i];
        for(int i=L[Be[x]];i<=x;i++)
            res+=Val[i];
        return res;
    }
    inline ll queryCnt(int x)
    {
        ll res=0;
        for(int i=1;i<Be[x];i++)    
            res+=Cnt[i];
        for(int i=L[Be[x]];i<=x;i++)
            res+=C[i];
        return res;
    }
}C,D;
inline ll query(int x)
{
    ll Sum=0;int pos=0;
    pos=lower_bound(fi+1,fi+1+k,x)-(fi+1);
    Sum+=(x-1)*queryCnt(1,pos,x)-querySum(1,pos,x);
    Sum+=(x-1)*C.queryCnt(x-1)-C.querySum(x-1);
    Sum+=(m+x-1)*(D.queryCnt(m)-D.queryCnt(x-1))-(D.querySum(m)-D.querySum(x-1));
    return Sum;
}
signed main()
{
    read(n,m);
    for(int i=1;i<=n;i++) read(a[i]);
    ll Ans=0;build(); 
    for(int i=2;i<=n;i++)
    	if(a[i]>=a[i-1]) Ans+=a[i]-a[i-1];
    	else Ans+=m-a[i-1]+a[i];
    for(int i=2;i<=n;i++)
        if(a[i]>a[i-1]) b[++k]=make_pair(a[i-1],a[i]);
        else if(a[i]<a[i-1]) c[++t]=a[i-1],d[t]=a[i];
    sort(b+1,b+1+k);C.build(t,c,c),D.build(t,d,c);
    for(int i=1;i<=k;i++)
        fi[i]=b[i].first,se[i]=b[i].second;
    build(k);
    ll Sum=Ans;
    for(int x=1;x<=m;x++)
    	Sum=min(Sum,Ans-query(x));
    write(Sum);
    return 0;
}
```

---

## 作者：fade_away (赞：2)

# ARC077E - guruguru
[安利博客](https://blog.csdn.net/xmr_pursue_dreams/article/details/111874178)
## Solution
考虑每一次改动对于每一个$x$的影响。

设我们要从$a$变到$b$。
当$a->x->b$时，该次对$x$的贡献为$D_{a,b}-D_{a,x}+1$，即一个公差为$-1$的递减序列，差分维护$c_i,d_i$分别表示当前位置新增的序列个数和这个位置新增序列的$a$的贡献，从前往后递推即可。

当$a->b->x$时，该次对$x$的贡献为$D_{a,b}$，即一个定值，直接类似前缀和地差分即可。

时间复杂度$O(n)$。

具体实现过程中可以把差分数组扩展两倍，然后算$i$的贡献和时加上$i+m$的贡献，这样会方便很多。

## Code
```cpp
ll s[MAXN],c1[MAXN],d1[MAXN],d2[MAXN],a[MAXN];
signed main()
{
	int n=read(),m=read();
	for (int i=1;i<=n;i++) a[i]=read();
	for (int i=1,l,r,t;i<n;i++)
	{
		l=a[i]+1,r=(a[i]>a[i+1]?a[i+1]+m:a[i+1])+2,t=r-l;
		d1[l]+=t,c1[l]++,c1[r]--;
		l=(a[i]>a[i+1]?a[i]:a[i]+m),r=a[i+1];
		d2[r+1]+=t-1,d2[l+1]-=t-1;
	}
	ll num=0,sum=0,ans=loo;
	for (int i=1;i<=m*2;i++) num+=c1[i],sum+=d1[i]-num+d2[i],s[i]=sum;
	for (int i=1;i<=m;i++) upmin(ans,s[i]+s[i+m]);
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Leasier (赞：2)

前置芝士：[差分](https://oi-wiki.org/basic/prefix-sum/#_6)

显然，如果我们枚举 $x$，然后再求出对应的答案的时间复杂度较高，难以承受。

正难则反，考虑每个相邻的 $a_i, a_{i + 1}$ 对每个 $x$ 减少次数的贡献。

显然需要分情况讨论。

1. 当 $a_i < a_{i + 1}$

显然，此时只会对 $a_i + 2$ ~ $a_{i + 1}$ 产生贡献为 $1$ ~ $a_{i + 1} - a_i - 1$。

2. 当 $a_i \geq a_{i + 1}$

显然，此时只会对 $1$ ~ $a_{i + 1}$ 和 $a_i + 2$ ~ $m$ 产生贡献为 $1$ ~ $m + a_{i + 1} - a_i - 1$。

由于只需要在统计结果时查询一次，每次修改只需要二次差分。

统计答案时，对差分数组进行二次前缀和后就是把位置选在 $x$，会减少多少步。所以取其中的最大值，将没有二操作时的总步数减去它即可。。时间复杂度为 $O(n)$。

**重点：这道题告诉我们，不仅可以考虑使用某种算法在允许的时间复杂度内动态维护每种情况的答案；还可以考虑答案的来源，以便于考虑每个部分对每种情况的答案的贡献。**

代码：
```cpp
#include <stdio.h>

typedef long long ll;

int a[100007];
ll diff2[100007], diff1[7][100007], b[100007];

inline ll max(ll a, ll b){
	return a > b ? a : b;
}

int main(){
	int n, m;
	ll p = 0, q = 0;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	for (int i = 1; i < n; i++){
		p += ((a[i + 1] - a[i]) % m + m) % m;
	}
	for (int i = 1; i < n; i++){
		int x = a[i], y = a[i + 1];
		diff2[x + 2]++;
		diff2[y + 1]--;
		if (x < y){
			diff1[2][y + 1] -= y - x - 1;
		} else {
			diff2[1] += m - x;
			diff2[2] += x - m + 1;
			diff1[2][y + 1] -= m + y - x - 1;
		}
	}
	for (int i = 1; i <= m; i++){
		diff1[1][i] = diff1[1][i - 1] + diff2[i];
	}
	for (int i = 1; i <= m; i++){
		b[i] = b[i - 1] + diff1[1][i] + diff1[2][i];
		q = max(q, b[i]);
	}
	printf("%lld", p - q);
	return 0;
}
```

---

## 作者：Nangu (赞：1)

## Subtack 1
暴力枚举每个 $X$，算出结果即可。
## Subtack 2
考虑对前面的方法进行优化。

我们可以发现，对于从 $a_i$ 走到 $a_{i+1}$ 来说，如果 $X=a_i+1$，那么步数不会有任何变化；如果 $X=a_i+2$， 那么步数会减少 $1$。以此类推，当 $X=a_{i+1}$ 时，步数会减少 $a_{i+1}-a_i-1$。

但直接这么暴力复杂度仍是 $O(nm)$，显然还是过不去。因此，我们想到，可以利用二阶差分来优化此过程。

对于由 $a_i$ 走到 $a_{i+1}$ 来说，令 $l=a_i+2$，$r=a_{i+1}$，$s_l\gets s_l+1$, $s_{r+1}\gets s_{r+1}-(r-l+2)
$，$s_{r+2}\gets s_{r+2}+(r-l+1)$，最后做两遍前缀和即可。
时间复杂度 $O(n+m)$，可以通过此题。

## Code
```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MAXN=2e5+7;

int n, m, a[MAXN], s[MAXN<<1], sum, ans=9e18;

inline int read()
{
	int x=0; bool f=0; char c;
	while(!isdigit(c=getchar())) if(c=='-') f=1;
	do x=(x<<1)+(x<<3)+(c&15); while(isdigit(c=getchar()));
	return f?-x:x;
}

signed main()
{
	n=read(), m=read();
	for(int i=1; i<=n; i++){
		a[i]=read();
		if(i==1) continue;
		int l=a[i-1], r=a[i-1]>a[i]?a[i]+m:a[i];
		sum+=r-l;
		if(l+2<=r) l+=2, s[l]+=1, s[r+1]-=r-l+1+1, s[r+2]+=r-l+1;
	}
	for(int i=2; i<=m*2; i++) s[i]+=s[i-1];
	for(int i=2; i<=m*2; i++) s[i]+=s[i-1];
	for(int i=1; i<=m; i++) 
		ans=min(ans, sum-s[i]-s[i+m]);
	cout<<ans;
	return 0;
}

---

## 作者：lkjzyd20 (赞：0)

### 思路
先考虑最简单的情况，从 $a_i$ 到 $a_{i+1}$，并且 $a_{i+1}>a_i$，例如从位置 $3$ 到位置 $8$。易知如果没有红色的按钮的话，就只能使用黑色按钮。则按 $a_{i+1}-a_i$ 次，就可以从 $a_i$ 档到 $a_{i+1}$ 档。

如果有红色按钮，可以一步跳到 $x$ 位置，则假如 $x$ 设置在其中间位置，只需按 $a_{i+1}-x+1$ 次即可完成任务。那么可以将每个 $a_i$ 和 $a_{i+1}$ 看成一条线段，只要 $x$ 设置在线段上，这次操作就有相应的次数减少 $x-a_i-1$ 次，$x$ 在线段外即对当前操作无影响。

注意到这个影响量 $x-a_i-1$ 由两部分组成，其中 $x$ 是个变化的量，$a_i+1$ 是个稳定的量。将后者提取出来，设 $b$ 数组将线段上区间为 $[a_{i-1}+1,a_i]$ 这一段，都加上权值 $a_i+1$（这个权值是今后算最终结果时要减去的部分），同时设 $c$ 数组为在同样线段上各个值 $+1$，表示 $x$ 这个位置就能减少次数，最后遍历一下就能知道 $x$ 设置在位置 $i$ 能减少的总次数了。

上述操作用差分数组解决，时间复杂度 $O(n)$。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
#define rep(i, l, r) for(int i = l; i <= r; ++ i)
#define per(i, r, l) for(int i = r; i >= l; -- i)

const int N = 1e5 + 10, INF = 0x3f3f3f3f3f3f3f3f;
int n, m, a[N], ans = INF, c[N], b[N];
void check(int s, int t)
{
    b[1] += t - s; 
    b[t + 1] -= s + 1;
    b[s + 1] += s + 1;
    ++ c[t + 1]; 
    -- c[s + 1];
    if(t <= s) b[1] += 1 + s, b[t + 1] += m, -- c[1];
}
main()
{
    scanf("%lld %lld", &n, &m);
    rep(i, 1, n) scanf("%lld", &a[i]);
    rep(i, 1, n - 1) check(a[i], a[i + 1]);
    rep(i, 1, m)
	{
		c[i] += c[i - 1];
        b[i] += b[i - 1];
		ans = min(ans, c[i] * i + b[i]);
	}
	printf("%lld", ans);
}
```

---

## 作者：Halberd_Cease (赞：0)

提供不同的办法。

对于 $1<i\le n$，我们称从 $a_{i-1}\to a_i$ 的过程为一个变换。

显然，对于某一个变换，一定是 $X$ 在一段区间内时，通过变为 $X$，再操作 $a_i-X$ 次得到答案，剩下的区间，则直接从 $a_{i-1}$ 转移至 $a_i$。

讨论一下，通过 $X$ 转移更优的区间是 $(a_{i-1}+1,a_i+1)$。

考虑将区间首尾丢进数组里，做扫描线。

枚举 $X=1,2,\dots,m$，如果 $X$ 进了一个转移的区间，在当次是不会有贡献的，到出区间之前，由于 $X$ 每次 $+1$，这个操作的代价也会不断 $-1$，直到出区间后，恢复原来的代价 $a_{i}-a_{i-1}$。

我们考虑维护 $X$ 在多少个区间里面，以及当前的代价，就可以 $O(1)$ 计算当前 $X$ 的答案，由于只会出入的一个操作区间各一次，因此总复杂度为 $O(n+m)$。

注意，调整至 $X$ 也需要一次代价。

[submission](https://atcoder.jp/contests/arc077/submissions/51432627)

---

## 作者：__Hacheylight__ (赞：0)

自己做的时候并没有采取数据结构去维护信息，我使用的是扫描线

首先先对给的 $a$ 数组的暴力路线记录，排序一下

然后如果某一条路线的 $x < i$ 的话这个时候 $i$ 这个 $botton$ 就能够对答案更优

所以我们可以使用扫描线算法

顺序枚举每一个点作为 $favorite~botton$，同时顺序枚举每一条路径

对于那些过期的路径我们可以通过堆把他删掉

需要把 $\inf$ 开大，设 $2e18$ 会 $wa$ ，应该 $9e18$ 左右

```cpp
// 省去头文件
int n, m ;
int a[N] ;
ll ans = linf, now ;

signed main() {
	scanf("%d%d", &n, &m) ;
	rep(i, 0, n - 1) scanf("%d", &a[i]), a[i]-- ;
	vector <pii> e ;
	rep(i, 1, n - 1) {
		if (a[i - 1] < a[i]) e.pb(mp(a[i - 1], a[i])) ;
		else e.pb(mp(a[i - 1] - m, a[i])) ;
		now += (a[i] - a[i - 1] + m) % m ; // 先把所有的暴力跑的结果加入
	}
	rep(i, 0, n - 1) e.pb(mp(e[i].fi + m,  e[i].se + m)) ;
	sort(all(e)) ; // 先 fi 再 se
//	loop(it, e) cout << it->fi << " " << it->se << endl ;
	pq <pii> Q ;
	int id = 0 ;
	rep(x, 0, m - 1) { // 扫描线
		now -= siz(Q) ;
		while (id < 2 * n - 2 && e[id].fi < x) { // 考虑对于每个在 x ~ e[id].se 的范围内
			Q.push(mp(-e[id].se, e[id].se - e[id].fi)) ;
			now += e[id].se - x + 1 ;
			now -= e[id].se - e[id].fi ;
			id++ ;
		}
		chmin(ans, now) ;
		while (!Q.empty() && -Q.top().fi == x) {
			now += Q.top().se - 1 ; // 把所有的结果返回
			Q.pop() ;
		}
	}
	printf("%lld\n", ans) ;
	return 0 ;
}
```

---

