# [AGC003E] Sequential operations on Sequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc003/tasks/agc003_e

高橋君はお母さんから数列をもらいました。この数列の長さは $ N $ で、$ i(1\ ≦\ i\ ≦\ N) $ 項目の要素は $ i $ です。 高橋君は、この数列に以下の操作を合計で $ Q $ 回行いました。$ i $ 番目の操作は、パラメータ $ q_i $ であらわされ、以下のように行われます。

- いまの数列を無限回繰り返した数列の先頭 $ q_i $ 項をとって、新たな数列とする。

$ Q $ 回の操作後、この数列に $ 1 $ から $ N $ までの各々の数が何回ずつ現れるかを求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 10^5 $
- $ 0\ ≦\ Q\ ≦\ 10^5 $
- $ 1\ ≦\ q_i\ ≦\ 10^{18} $
- 入力はすべて整数である。

### Sample Explanation 1

$ 1 $ 回目の操作で、数列は $ 1,2,3,4,5,1 $ となります。 $ 2 $ 回目の操作で、数列は $ 1,2,3,4 $ となります。 $ 3 $ 回目の操作で、数列は $ 1,2,3,4,1,2,3,4,1,2,3 $ となります。 この数列には $ 1,2,3,4,5 $ がそれぞれ $ 3,3,3,2,0 $ 個含まれているので、上のように出力します。

## 样例 #1

### 输入

```
5 3
6
4
11```

### 输出

```
3
3
3
2
0```

## 样例 #2

### 输入

```
10 10
9
13
18
8
10
10
9
19
22
27```

### 输出

```
7
4
4
3
3
2
2
2
0
0```

# 题解

## 作者：Ebola (赞：17)

这题的思维要求好高啊qwq（可能是因为我太菜

如果后面的一个a比前面小，那前面那些比它大的显然是没有意义的，因此我们可以在读入时维护一个单调栈，使得最后的操作序列单调递增

考虑一个计算第i次操作过程。前面的一大堆都是上一次操作所得答案的若干倍，所以对于一个操作，只要单独处理a\[i\] mod a\[i-1\]那一部分的答案就好了。至于前面那些没用的，就给第i-1个操作加上一个系数，到时候操作它的时候答案乘上这个系数即可

那单独处理的这一部分，做法也是一样的。跳过前面比这一段长度更大的操作，找到第一个小于它长度的a\[t\]，前面一大堆都是第t次操作的若干倍，所以直接给第t次操作加上一个系数，再处理(a\[i\] mod a\[i-1\]) mod a\[t\]即可。就这样不断递归下去，直到没有比它更小的了，此时直接给答案区间\[1, len\]加上当前操作的系数即可（len表示当前区间长度）。区间加法可以用差分实现，最后还原即可

那这个过程显然要倒着来做，要不然你都不知道当前操作的系数是多少

至于复杂度，递归时每次长度模一个数，那层数显然不超过log层。因为要二分找上面说的那个t，所以复杂度两个log

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
namespace IO
{
    const int S=(1<<20)+5;
    char buf[S],*H,*T;
    inline char Get()
    {
        if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
        if(H==T) return -1;return *H++;
    }
    inline LL read()
    {
        LL x=0;char c=Get();
        while(!isdigit(c)) c=Get();
        while(isdigit(c)) x=x*10+c-'0',c=Get();
        return x;
    }
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    template <class I>inline void print(I x)
    {
        if(!x) putc('0');
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
        putc('\n');
    }
}

using namespace IO;
const int N=100010;
int n,m,top=0;
LL a[N],f[N];
LL delta[N];

void solve(LL x,LL y)
{
    if(!x) return;
    int t=upper_bound(a+1,a+1+top,x)-a-1;
    if(!t) delta[1]+=y,delta[x+1]-=y;
    else f[t]+=x/a[t]*y,solve(x%a[t],y);
}

int main()
{
    a[++top]=n=read();m=read();
    for(int i=1;i<=m;i++)
    {
        LL x=read();
        while(x<=a[top]) top--;
        a[++top]=x;
    }
    f[top]=1;
    for(int i=top;i>=2;i--) f[i-1]+=a[i]/a[i-1]*f[i],solve(a[i]%a[i-1],f[i]);
    delta[1]+=f[1];delta[a[1]+1]-=f[1];
    for(int i=1;i<=n;i++) print(delta[i]+=delta[i-1]);
    flush();
    return 0;
}
```



---

## 作者：x义x (赞：10)

显然如果 $A_i>A_{i+1}$ 那么我们可以无视 $i$ 操作，这样预处理一下 $A_i$ 必然单调增。

考虑第 $i$ 次操作。之前的序列会被重复 $\lfloor\dfrac{A_{i}}{A_{i-1}}\rfloor$ 次，再加上一点长度为 $A_{i}\bmod A_{i-1}$（记为 $d$）的边角料。

如果只有不断重复的部分那么很好做，设 $f_i$ 表示结果序列是第 $i$ 次操作完的序列的几倍然后倒推即可。

问题在于边角料，考虑这个边角料到哪里找，是否也是某个东西重复出现。如果有一个 $A_j<d$ 且 $A_{j+1}>d$，那么你会发现 **$A_j$ 和 $d$ 的关系与 $A_{i-1}$ 和 $A_{i}$ 的关系是完全一样的**，都是前者重复出现然后取一个长度为后者的前缀，所以 $d$ 模掉 $A_{j}$ 继续递归就好了。

每次 $d$ 至少减半，然后递归到底的时候就是 1 到 $d$ 区间加，可以差分，这样复杂度就是 $O(n\log ^2 n)$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int N,Q;
ll A[100005];int len;
ll F[100005],c[100005];

void Solve(ll d,ll w){
	int j=upper_bound(A+1,A+len+1,d)-A-1;
	if(!j) c[1]+=w,c[d+1]-=w;
	else F[j]+=d/A[j]*w,Solve(d%A[j],w);
}

int main(){
	scanf("%d%d",&N,&Q);
	A[++len]=N;
	while(Q--){
		ll Ai;scanf("%lld",&Ai);
		while(len&&A[len]>=Ai) len--;
		A[++len]=Ai;
	}
	F[len]=1;
	for(int i=len;i>=2;i--) F[i-1]+=A[i]/A[i-1]*F[i],Solve(A[i]%A[i-1],F[i]);
	c[1]+=F[1];c[A[1]+1]-=F[1];
	for(int i=1;i<=N;i++) printf("%lld\n",c[i]+=c[i-1]);
}
```

---

## 作者：是个汉子 (赞：8)



[洛谷传送门](https://www.luogu.com.cn/problem/AT2005)	[AT传送门](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/2005)

### Solution

这种题对我来说——思维难度太高了吧（；´д｀）ゞ

首先我们要处理一下 $q$ 。

发现当 $q_i\geq q_{i+1}$ 时， $q_i$ 这个操作就没用了，所以要拿单调栈先搞出来一个单调递增的 $q$ 序列。

---

我 们 往 下 走。

转化一下：对于第 $i$ 次操作，序列 $A_i$ 是由之前的 $\lfloor \dfrac {q_i} {q_{i-1}}\rfloor$ 个 $A_{i-1}$ 和一个长度为 $q_i\%q_{i-1}$ 的前缀 $B$ 拼接起来的。

那么可以看作 $A_i$ 能**拆**成 $\lfloor \dfrac {q_i} {q_{i-1}}\rfloor$ 个 $A_{i-1}$ 和一个长度为 $q_i\%q_{i-1}$ 的前缀 $B$，其中的 $A_{i-1}$ 我们可以选择继续递归进行处理，需要着重考虑那个前缀。

既然 $A_i$ 能**拆**，那么 $B$ 也能(￣▽￣)"

我们选择二分找到一个 $q_j$ ，使得 $q_j<|B|,q_{j+1}>|B|$ ，将拆出的 $A_j$ 的数量加入 $num_j$，剩余部分继续拆分，最后可以得到一个 $A_1$ 的前缀，那么直接将 $cnt[1\cdots |B'|]$ 全部加上 $num_i$ （其中 $num_i$ 为 $A_i$ 在 $A_{Q}$ 能拆出的数量）。

优化：我们不能每次都 $O(|B|)$ 累加答案，所以这时候**差分数组**出现了。

时间复杂度是 $O(n\log^2 n)$ ，因为每次 $B$ 都减少至少一半。

### Code

```c++
#include<bits/stdc++.h>
#define ll long long

using namespace std;
const int N=1e5+10;
int n,Q,tot;
ll q[N],num[N],c[N];

void solve(ll d,ll w){
    int j=lower_bound(q+1,q+tot+1,d)-q-1;
    if(!j) c[1]+=w,c[d+1]-=w;
    else num[j]+=d/q[j]*w,solve(d%q[j],w);
}

int main(){
    scanf("%d%d",&n,&Q);
    q[++tot]=n;
    while(Q--){
        ll a; scanf("%lld",&a);
        while(tot&&q[tot]>=a) tot--;
        q[++tot]=a;
    }
    num[tot]=1;
    for(int i=tot;i>=2;i--) num[i-1]+=q[i]/q[i-1]*num[i],solve(q[i]%q[i-1],num[i]);
    c[1]+=num[1]; c[q[1]+1]-=num[1];
    for(int i=1;i<=n;i++) printf("%lld\n",c[i]+=c[i-1]);
    return 0;
}
```



---

## 作者：CYJian (赞：8)

## AGC003E

这题应该算是看到了就会一半的题目。

首先第一眼发现：如果前一次操作的区间长度大于后一次，那么前一次的操作可以扔掉。

注意到这个东西具有传递性，那么可以直接用单调栈弄出真正有用的操作序列 $A$。

搞出一个长度单调递增的操作序列之后，我们可以考虑倒推：第 $i$ 次操作相当于重复 $\left\lfloor \frac{A_i}{A_{i-1}} \right\rfloor$ 次 $i-1$ 次操作后的序列，然后再追加第 $i-1$ 次操作后的序列的前 $A_i \bmod A_{i-1}$ 项。我们考虑每次追加的时候存在取模操作，而每次取模的时候被取模值至少减少一半，那么如果我们每次二分一个最大的小于取模值的 $A_j$ 出来，然后继续操作，复杂度就是 $O(\log^2 n)$ 的。然后考虑每次重复前一次操作，相当于对于每一个操作，我们都要算一次一直往前取模的影响。那么总复杂度就是 $O(n \log^2 n)$ 的。

注意到如果取模后取模值 $x$ 小于 $A_1$，那么就会对前 $x$ 个数都有贡献。多次区间加然后一次询问，这样的问题我们通常都用差分解决。

${\rm Code}$：

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int __SIZE = 1 << 18;
char ibuf[__SIZE], *iS, *iT;

#define ge (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
#define ri read_int()
#define rl read_ll()
#define FILE(s) freopen(s"in", "r", stdin), freopen(s"out", "w", stdout)

template<typename T>
inline void read(T &x) {
	char ch, t = 0; x = 0;
	while(!isdigit(ch = ge)) t |= ch == '-';
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = ge;
	x = t ? -x : x;
}
inline int read_int() { int x; return read(x), x; }
inline ll read_ll() { ll x; return read(x), x; }

template<typename T>
inline void chkmin(T&a, T b) { a = a < b ? a : b; }

const int MAXN = 100010;

int top;
ll a[MAXN];
ll c[MAXN];
ll tim[MAXN];

inline void solve(int p, ll x, ll t) {
	tim[p] += t * (x / a[p]), x %= a[p];
	p = upper_bound(a + 1, a + 1 + p, x) - a;
	if(p == 1) c[1] += t, c[x + 1] -= t;
	else solve(p - 1, x, t);
}

int main() {
#ifdef LOCAL
	FILE("");
#endif

	int n = ri, q = ri;

	a[++top] = n;
	for(int i = 1; i <= q; i++) {
		ll x = rl;
		while(a[top] >= x && top) --top;
		a[++top] = x;
	}

	tim[top] = 1;
	for(int i = top; i > 1; i--)
		solve(i - 1, a[i], tim[i]);

	for(int i = 1; i <= a[1]; i++)
		c[i] += c[i - 1];

	for(int i = 1; i <= a[1]; i++)
		printf("%lld\n", c[i] + tim[1]);
	n -= a[1];
	while(n--) puts("0");
	return 0;
}
```

---

## 作者：zythonc (赞：6)

## 前言

说实话评分过分了，这题顶多紫  
然后笔者较弱，代码比别的题解长QAQ

## 题目分析

首先要声明的是，你只要被套路过很多次，然后牢记“正难则反”这四个字，本题就已经解决了

事实上，我们发现如果第一步先扩充，第二步再缩小，那么我们可以直接删掉第一步  
正确性显然，利用单调栈维护即可

设我们已经用单调栈维护完毕，第 $i$ 次操作后的长度为 $l_i$

- 第 $i$ 次的长度比第 $i-1$ 次的小  
那么就相当于先算一遍 $1\sim l_{i-1}$ 中每个次数出现的次数，然后再算一遍 $1\sim l_i\bmod l_{i-1}$ 中每个次数出现的次数

- 第 $i$ 次的长度比第 $i-1$ 次的大  
那么 $(l_{i-1},l_i]$ 中肯定有前 $l_{i-1}$ 个数的 $k$ 次重复，于是我们将前 $l_{i-1}$ 个数增加一个系数 $k$，表示要被算几次  
然后对后 $l_i\bmod l_{i-1}$ 个数（称为取模之后要进行计算的数）进行递归

情况一其实是情况二的特例

假设现在考虑到第 $i$ 个数，考虑到不属于取模之后要进行计算的位置的数肯定被增加了系数，递归的时候即解决

于是，现在的问题变成了，如何计算后 $l_i\bmod l_{i-1}$ 个数，设共有 $num$ 个数

考虑到这些东西肯定也是某个比其 $num$ 小的区间的重复，于是我们二分一下找到区间，然后用情况二讨论一下

对于前面的数，增加系数，后面的数递归求解

顺带一提，增加系数是区间加法，但是查询只有最后统计时的一次，利用差分即可

## 代码实现

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 1000001
#define M 5001
#define INF 9223372036854775806
#define Kafuu return
#define Chino 0
#define C const
#define U unsigned
#define fx(l,n) inline l n
#define set(l,n,ty,len) memset(l,n,sizeof(ty)*len)
#define cpy(f,t,ty,len) memcpy(t,f,sizeof(ty)*len)
#define int long long
using namespace std;
fx(int,gi)(){
	char c=getchar();int s=0,f=1;
	while(c>'9'||c<'0'){
		if(c=='-') f=-f;
		c=getchar();
	}
	while(c<='9'&&c>='0') s=(s<<3)+(s<<1)+(c-'0'),c=getchar();
	return s*f;
}
int n,q,qu[N],minn=INF,eend[N],num,pl,cf[N],bf,add[N],bf2;
fx(void,sim)(int r,int now,int sum){//处理取模之后要进行计算的数
	if(!now){
		cf[1]+=sum,cf[r+1]-=sum;
		return;
	}
	bf=r%eend[now];
	add[now]+=r/eend[now]*sum;
	if(bf) sim(bf,upper_bound(eend+1,eend+num+1,bf)-eend-1,sum);
}
fx(void,solve)(int r,int now){
	if(!now){
		cf[1]+=add[now+1],cf[r+1]-=add[now+1];
		return;
	}
	bf=r%eend[now];
	add[now]+=r/eend[now]*add[now+1];
	if(bf) sim(bf,upper_bound(eend+1,eend+num+1,bf)-eend-1,add[now+1]);
	solve(eend[now],now-1);
}
signed main(){
	n=gi(),q=gi();
	if(!q){
		for(int i=1;i<=n;i++) printf("1\n");
		Kafuu Chino;
	}
	for(int i=1;i<=q;i++){
		qu[i]=gi();
		if(qu[i]<=minn) minn=qu[i],pl=i;
	}
	if(minn>n) eend[++num]=n;
	eend[++num]=minn;
	for(int i=pl+1;i<=q;i++){
		while(qu[i]<=eend[num]) num-=1;
		eend[++num]=qu[i];
	}
	add[num]=1;
	solve(eend[num],num-1);
	for(int i=1;i<=eend[1];i++) printf("%lld\n",bf2+=cf[i]);
	for(int i=eend[1]+1;i<=n;i++) printf("0\n");
}
```



---

## 作者：Xy_top (赞：5)

神仙题，感觉大家讲的都不太详细，我会把我自己思考的过程一步步写出来。

初看这题时感觉没什么思路，所以随便算了点东西。很容易发现如果对于一个 $i$，$q_i\geq q_{i+1}$，那么 $q_i$ 就没有意义，每次把元素放进来时先把头部比它大的都弹走，再把它放进去，设处理完的 $size$ 为 $cnt$。

然后就是这道题的精髓所在了！很容易就可以发现 $q_i+1$ 的串是 $q_i$ 串的弱循环。所以就可以弄一个 ``solve`` 函数，``solve (x, y)`` 意思是处理第 $q$ 个串循环 $y$ 遍的贡献。运行 ``solve (cnt, 1)`` 就可以了，但是 ``solve`` 函数怎么设计呢？

以下设 $q_i=len_i$

前面的循环节可以用 ``solve (cnt - 1, len[cnt] / len[cnt - 1])`` 处理，但是后面多余的呢？

这时我们发现需要改变 ``solve`` 函数了，设 ``solve (x, y)`` 处理前 $x$ 个字符循环 $y$ 次的贡献。

转移首先要找到第一个 $t$，使得 $len[t] < x$，前面的部分仍然是循环，``solve (len[t], x / len[t])`` 就解决了，后面还有 $x$ $\bmod$ $len[t]$ 个剩余的，这些只循环 ``1`` 次，``solve (x % len[t], 1)`` 就可以了。

另外，注意下边界问题，如果 $x\leq n$ 了，那么前 $x$ 个字符就是 $1\cdots x$，这些的出现次数都 $+1$，用差分维护就行。

分析一下时间复杂度，$T(x)= x + T(x - 1) + T (\frac{x}{2})=x^2$，考虑优化。

时间主要用在了 $x$ 和 $T(x-1)$ 上，第一个用二分可以 $\log_n$。关于第二个，``solve`` 函数都是 ``solve (len[t], x / len[t])`` 的形式，第一个参数也就 $n$ 种。因此，我们用一个桶 $f$，$f[t]$ 统计的是 $1$ 到 $len[t]$ 个字符循环的次数。最后再把 $f$ 中的一起统计一下就行。

现在的 ``solve`` 函数就成了这样：
```cpp
void solve (int x, int y) {
	if (x <= n) {
		d[1] += y;
		d[x + 1] -= y;
		return;
   }
   int t = lower_bound (len + 1, len + cnt + 1, x) - len - 1;
   f[t] += x / a[t] * y;
   solve (x % a[t], y);
}
```

结束后，我们倒序循环一下。$f[i]$ 拆成 $f[i - 1] * \lfloor\frac{len[i]}{len[i - 1]}\rfloor + len[i] $ $\bmod$ $len[i - 1]$，前面的加到 $f[i-1]$ 上，后面的继续用 ``solve`` 函数。（即 ``solve (len[i] % len[i - 1], f[i])`` ）。

此题的 $q_i$ 也可能小于 $n$，所以遇到这种情况，我们把 $n$ 设为最小的 $q_i$，输出时 $>n$ 的输出 $0$ 即可。

这样，时间复杂度降到了 $n\log^2 n$，另外注意开长整型和特判 $q=0$ 的情况。

少量注释的代码：
```cpp
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
int n, q, cnt;
int a[100005], d[100005], f[100005];
void solve (int x, int y) {//求解前 x 个字符的贡献乘上 y 
	if (x <= n) {
		d[1] += y;
		d[x + 1] -= y;
		return;
	}
	int t = lower_bound (a + 1, a + cnt + 1, x) - a - 1;
	f[t] += x / a[t] * y;//其实是前 a[t] 个字符乘上 x / a[t] 加上剩余的。 
	solve (x % a[t], y);
}
signed main () {
	int x, z;
	cin >> n >> q;
	if (q == 0) {
		for (int i = 1; i <= n; i ++) cout << 1 << "\n";
		return 0;
	}
	z = n;
	a[++ cnt] = n;
	for (int i = 1; i <= q; i ++) {
		cin >> x;
		n = min (n, x);
		while (cnt != 0 && a[cnt] >= x) -- cnt;
		a[++ cnt] = x;
	}
	solve (x, 1);
	for (int i = cnt; i >= 2; i --) {
		f[i - 1] += a[i] / a[i - 1] * f[i];
		solve (a[i] % a[i - 1], f[i]);
	}
	d[1] += f[1];
	d[n + 1] -= f[1];
	for (int i = 1; i <= n; i ++) {
		d[i] += d[i - 1];
		cout << d[i] << "\n";
	}
	for (int i = n + 1; i <= z; i ++) cout << 0 << "\n";
	return 0;
}
```

---

## 作者：陈刀仔 (赞：3)

**首先要筛去无用操作，这我为啥想不到嘞 /kel 。**

如果 $a[i]\geq a[i+1]$ ，那么 $a[i]$ 肯定没有用，所以一开始我们拿 $a$ 跑个单调栈。

然后考虑扩展的结果，就是把上一次的结果复制几遍然后再加上一些边角料。

**边角料很难做啊，先考虑没有边角料该是什么情况，我们就把复制次数乘起来，得到 $a[1]$ 总共被复制了多少次就做完了。**

正着做怎么都处理不了这个边角料，我们考虑反着拆解。

我们的最终目标是把拆解成一大堆形如 $1\cdots x$ 的段来统计答案，这样的段只有 $O(Q)$ 种，其中又可以细分为 $a[1]$ 和其它复制过程中产生的边角料。

我们不需要一步到位，于是我们从后往前枚举当前最大的模式串 $a[i]$ ，把 $a[i]$ 的复制次数分配到更小的 $a[j]$ 和其它的边角料上面去。

考虑拆解后 $a[i]$ 会变成什么样子，肯定是 $\{a[p[1]],a[p[2]],\cdots,a[p[t]],tail\}$ （$tail$是一段边角料），其中这个序列单调不增，**我们递归实现这个过程，每次把当前剩余串拿出来，找到被它包含的最长子模式串 $a[j]$ ，用 $a[j]$ 分解 $tmp$ ，计算给 $a[j]$ 的贡献再递归下去。最终只剩下一块边角料前缀了，直接贡献给最终答案。**

这么做一次的复杂度是 $O(\log n)$ 的，**因为每次我们都会把 $len(tmp)$ 对一个比它小的值取模，这样至少会让 $len(tmp)$ 减半。**

所以我们就在这个过程中记录模式串 $a[i]$ 当前接到的贡献次数 $F[i]$ 就好了，最终就全部贡献要么被预先加上去了，要么存在了 $F[1]$ 里面。

---

## 作者：Cx114514 (赞：2)

### 题目链接：[[AGC003E] Sequential operations on Sequence](https://www.luogu.com.cn/problem/AT_agc003_e)
一道非常有思维含量的题目。

首先摒除无用操作：若 $q_{i-1} >q_{i}$，则可以把操作序列中的 $q_{i-1}$ 删去。这样，操作序列变成了一个单调递增的序列。

考虑每一个操作后的序列长什么样：

对于每个一次操作 $i$，其操作后的序列一定形如：**$\left \lfloor \frac{q_{i}}{q_{i-1}} \right \rfloor $ 个长度操作 $i-1$ 形成的序列** $+$ **$1$ 个操作 $i-1$ 形成的序列的前 $q_i \bmod q_{i-1}$ 个元素**。

前面一段是重复的，只需要令 $f_{i}$ 表示操作 $i$ 形成的串在最终答案中重复了几次。易得转移：$f_i=\left \lfloor \frac{q_{i+1}}{q_{i}} \right \rfloor\times f_{i+1}$。

接下来考虑多余的部分如何计算。

设 $w_{i}$ 表示第 $i$ 次操作后多余部分的长度。

每次找到一个最大的 $q_{j}$ 使得 $q_{j} \le w_{i}$，则多余部分形如：**$\left \lfloor \frac{w_{i}}{q_{j}} \right \rfloor $ 个长度操作 $j$ 形成的序列** $+$ **$1$ 个操作 $j$ 形成的序列的前 $w_i \bmod q_{j}$ 个元素**。

这样问题 $i$ 又转化为了子问题 $j$，递归即可。

$\forall k\le w$，$w \bmod k< \left \lceil \frac{w}{2} \right \rceil$

证明如下：

若 $k\le \left \lceil \frac{w}{2} \right \rceil$，则 $w \bmod k < \left \lceil \frac{w}{2} \right \rceil$（余数小于除数）。

若 $\left \lceil \frac{w}{2} \right \rceil<k\le w$，则 $w \bmod k=w-k$，而 $w-k<\left \lceil \frac{w}{2} \right \rceil$。

据此结论，可保证每次递归次数为 $O\left(\log V\right)$。

每次递归都要二分查找一个最大的 $q_{j}$ 使得 $q_{j} \le w_{i}$，故时间复杂度为 $O\left(n\log n\log V\right)$。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, Q, q[100005], s[100005], top, d[100005], f[100005];

void solve(int x, int y)
{
	int t = upper_bound(s + 1, s + top + 1, x) - s - 1;
	if (!t)
	{
		d[1] += y;
		d[x + 1] -= y;
		return;
	}
	f[t] += (x / s[t]) * y;
	solve(x % s[t], y);
}

signed main()
{
	cin >> n >> Q;
	q[1] = n;
	Q++;
	for (int i = 2; i <= Q; i++)
		cin >> q[i];
	for (int i = 1; i <= Q; i++)
	{
		while (s[top] > q[i]) top--;
		s[++top] = q[i];
	}
	f[top] = 1;
	for (int i = top; i >= 2; i--)
	{
		solve(s[i] % s[i - 1], f[i]);
		f[i - 1] += (s[i] / s[i - 1]) * f[i];
	}
	d[1] += f[1];
	d[s[1] + 1] -= f[1];
	for (int i = 1; i <= n; i++)
	{
		d[i] += d[i - 1];
		cout << d[i] << endl;
	}
	return 0;
}
```

---

## 作者：_i_i_ (赞：2)

[AGC003E - AtCoder](https://atcoder.jp/contests/agc003/tasks/agc003_e)

[AGC003E - Luogu](https://www.luogu.com.cn/problem/AT2005)

> 一开始有一个长度为 $n$ 的数列，元素为 $1\sim n$，有 $m$ 次操作。
每次操作有个 $q_i$，代表将原数列复制粘贴 $\infty$ 次，然后保留前 $q_i$ 位。
求最后每个元素各有多少个。
$1\leq n,m\leq 10^5,1\leq q_i\leq 10^{18}$。
> 

思维题。

首先排除模拟，然后我们发现如果有一个操作将数列拉长了，然后又有一个操作吧数列长度减回去了，那么中间的操作不算是吧。

所以一开始就可以维护个单调上升性。

然后我们设 $k_i$ 代表将第 $i$ 次操作后数组总共复制出来了多少完整的块。

显然 $k_i=\lfloor\frac{q_i}{q_{i-1}}\rfloor$。那么显然第 $i$ 次操作的答案首先得有第 $i-1$ 次答案的 $k_i$ 倍才对。

但是我们漏数了后边无法整除的贡献！但是这部分贡献好像是第 $i-1$ 次操作后数列的某个前缀……

此时我们发现这是一个分治问题，假设有一个操作 $p$ 使得第 $p-1$ 次操作后数列长度 $<x$ 且第 $p$ 次操作后长度 $\geq x$（$q$ 可以使用强大的 lower bound $O(\log_2 m)$ 求解），由于我们之前保证了单调上升性，因此第 $p$ 次操作后数列的前 $x$ 项正是我们漏掉的贡献。

因此我们可以在此临时魔改一下第 $p$ 次操作，然后继续递归下去，直到 $p=0$，这时直接差分。

我们倒推一下，累计每次操作后的数列的贡献，将贡献由上述方法推给之前的数列就行。

由于每次分治都会使长度减半，因此分治复杂度 $O(\log_2\max q\log_2 m)$，时间复杂度 $O(n\log_2\max q\log_2 m)$，常数极小可以通过。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
long long f[100005], d[100005], q[100005]; int n, m;
void sol(long long x, long long val) {
	int p = lower_bound(q + 1, q + 1 + m, x) - q - 1;
	if (p == 0) d[1] += val, d[x + 1] -= val;
	else {
		long long k = x / q[p];
		f[p] += k * val; sol(x % q[p], val);
	}
}
int main() {
	scanf("%d %d", &n, &m); int mm = 1; q[1] = n;
	for (int i = 1; i <= m; i++) {
		long long x; scanf("%lld", &x);
		while (mm && q[mm] >= x) mm--;
		q[++mm] = x;
	}
	m = mm; f[m] = 1;
	for (int i = m; i; i--) sol(q[i], f[i]);
	for (int i = 1; i <= n; i++) printf("%lld\n", d[i] += d[i - 1]);
	return 0;
}
```

---

## 作者：Kubic (赞：2)

算是 AGC E 里面比较简单的了。

如果你在看到这句话的时候思考时间没有超过 $30min$，建议上移鼠标并关掉此页面。

下面是正经题解：

首先容易观察到一个性质：如果 $q_i\ge q_{i+1}$，那么 $q_i$ 就没有用了。

因此可以先把 $q$ 缩为一个单调递增的序列。

考虑如何计算答案。

设 $f_{i,j}$ 为操作到第 $i$ 次时取前 $j$ 个数所组成的答案序列。

那么容易得到转移：

$$f_{i,j}=\lfloor\dfrac{j}{a_k}\rfloor f_{k,a_k}+f_{k,j\mod a_k}$$

我们只想要有效转移，那么每次找到 $k<i$ 且 $a_k\le j$ 的最大 $k$ 转移即可。

此时设 $g_i=f_{i,a_i}$，我们要求的即为 $g_m$。

可以发现，我们考虑对于每一个 $i$ 如何用一些 $k<i$ 的 $g_k$ 之和来表示。

那么使用之前的转移方程直接递归下去即可做到这一点。最终可能会递归到一个 $j\le q_1$ 的情况，如果出现这种情况使用 $h_j$ 特殊地记录一下即可。

分析按照这样的策略每一个 $g_i$ 会被拆出多少个。

初始时 $j=a_i$，每递归一层，$j\leftarrow j\mod a_k$。而 $j\mod a_k\le\min\{a_k-1,j-a_k\}\le\lfloor\dfrac{j}{2}\rfloor$。因此递归层数只有 $\log a_i$。

也就是说，我们现在可以用不超过 $\log a_i$ 个 $g_k$ 与 $h_j$ 表示 $g_i$。

但是直接做依然是 $O(n^2\log a)$ 的，考虑转化做法。

可以从后往前倒着推，用 $w_i$ 表示 $g_i$ 的贡献次数。初始 $g_m=1$，按照之前的过程从后往前推。最终推到每一个 $h_j$ 的贡献。总复杂度将为 $O(n\log a)$。

代码实现与题解中的字母差异较大，请谨慎食用 qaq：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 100005
#define ll long long
int n,m,tp;ll a[N],f[N],z[N];
int find(int x,ll y) {return upper_bound(a+1,a+x+1,y)-a-1;}
void slv(int x,ll y,ll w)
{
	int t=find(x-1,y);if(!t) {z[y]+=w;return;}
	f[t]+=y/a[t]*w;ll r=y%a[t];if(!r) return;slv(t,r,w);
}
int main()
{
	scanf("%d %d",&n,&m);a[++tp]=n;
	for(int i=1;i<=m;++i)
	{
		ll x;scanf("%lld",&x);
		while(tp && x<=a[tp]) --tp;a[++tp]=x;
	}f[tp]=1;for(int i=tp;i;--i) slv(i,a[i],f[i]);
	for(int i=n;i;--i) z[i]+=z[i+1];
	for(int i=1;i<=n;++i) printf("%lld\n",z[i]);return 0;
}
```

---

## 作者：xwmwr (赞：2)

最后还是看了题解。

首先用单调栈把操作序列变成单调递增的（证明去掉一个相邻逆序对中的大数不会对答案产生影响）。

后面的内容想出来是几天之后了……

我描述不太清楚， 这里仅给出大体思路：



题目的目标就是要维护一个答案数组 $\tt ans[i]$， 其中 $\tt ans[i]$ 表示所有操作操作完之后 $\tt i$ 的数量 。

为了表达清楚那么一点点，现在在这里定义两种与序列相关的运算（设有一数列 $\tt q$）：

1. 数乘， $\tt k*q, \ k\in\Bbb N_+$ ，表示将 $\tt q$ 复制 $\tt k$ 次拼接起来
2. 答案数组加上数列 $\tt q$， $\tt ans += q$， 表示对于 $\tt \forall i\in[1,|q|]$， 让 $\tt ans[q_i]$ 加上 $\tt 1$



设操作总数为 $\tt Q$， 设第 $\tt i$ 次操作后的数列为 $\tt S_i$。

那么题目要求的就是要进行 $\tt ans += S_Q$ 之后输出整个 $\tt ans$ 数组。

显然， $\tt S_i$ 可以被分解为若干段 $\tt S_{i-1}$ 和一段 $\tt S_i\mod S_{i-1}$ （描述不精确， 感性理解下）

那么 $\tt ans += S_i$ 就相当于先后进行 $\tt ans += \lfloor\frac{|S_i|}{|S_{i-1}|} \rfloor*S_{i-1}$， $\tt ans += S_i\mod S_{i-1}$ 。

注意到这个  $\tt ans += S_i\mod S_{i-1}$ 的操作也是可以像刚才那样分解， 套一个二分， 分解完只需要 $\tt O(log^2)$ 的时间。

整个算法的总体思路就是把 “给答案数组加上一个较晚的数列” 不断拆成 “给答案数组加上若干个不一定相同的较早的数列”。



```cpp
#include<bits/stdc++.h>
using namespace std;
const int MN = 100003;

int n,q,tp;// tp means top
long long a[MN]; //操作数组

long long times[MN], ans[MN];
// times[i] 存储第i次操作后的数组被加了多少次
// 注意这个最后只会用到 times[1]

void divide(long long len, long long timeS) { // 把给 “ans数组加上第 id 次操作后的序列的长度为 len 的前缀 timeS 次” 分解
    int j = upper_bound(a+1,a+tp+1,len) - a - 1;
    if(!j) ans[1]+=timeS, ans[len+1]-=timeS;
    else {
        times[j] += (len/a[j]) * timeS;
        divide(len%a[j], timeS);
    }
}

int main() {
    scanf("%d%d", &n,&q);
    a[++tp] = (long long)n;//方便亿点点
    for(int i=1;i<=q;++i) {
        long long x;
        scanf("%lld",&x);
        while(tp && a[tp]>=x) --tp;
        a[++tp] = x;
    }
    
    times[tp] = 1ll; //题目就是要求把 ans 数组加上一个最终数列
    for(int i=tp;i>1;--i) {
        times[i-1] += (a[i]/a[i-1])*times[i]; //把 前面的部分 分解成 S[i-1], S[i] 表示第 i 次操作后的数列
        divide(a[i]%a[i-1],times[i]); //把后面剩下的 S[i] mod S[i-1] 分解
    }
    ans[1] += times[1];
    ans[a[1]+1] -= times[1];
    for(int i=2;i<=n;++i) ans[i] += ans[i-1];
    for(int i=1;i<=n;++i) cout << ans[i] << '\n';
    return 0;
}
```


---

## 作者：Mirasycle (赞：1)

首先需要排除无用的 $a_i$，直接单调栈处理出来一个递增的序列即可。

由于不是动态询问，而是最后再统计，所以我们应该思考一下贡献法之类的而不是数据结构维护。

设 $b_i$ 为第 $i$ 次操作之后的序列，那么 $b_i$ 就是由 $b_{i-1}$ 复制了 $\lfloor\dfrac{a_i}{a_{i-1}}\rfloor$ 次之后，加上了零散块前 $a_i\bmod a_{i-1}$ 个位置。对于第一类贡献好处理，但是第二类有点难办，这里的方法特别巧妙，直接把贡献放到前面去。对于 $a_i\bmod a_{i-1}$ 的部分其实在前面就已经成型了，也就是在 $a_j<a_i\bmod a_{i-1}$ 的时候就已经确定了前 $a_j$ 个，还需要再继续在 $j+1$ 处算 $(a_i\bmod a_{i-1}) \bmod a_j$ 的贡献，继续递归计算即可。贡献可以用差分标记一下。

发现每次取模数量大小至少变成之前的 $\dfrac{1}{2}$，所以单次递归次数是 $\log$ 级别的，配合上二分就是 $2\log $，因此时间复杂度是 $O(n\log^2n)$。

---

## 作者：WeLikeStudying (赞：1)

- ``不知乘月几人归,落月摇情满江树。``

**[题意](https://www.luogu.com.cn/problem/AT2005)**
- 一开始有一个数列，每一次都让数列自己循环延伸到一个长度，求最后数列中每个数的出现次数。

**分析**
- 设 $f(i,j)$ 为第 $i$ 次操作后形成的数列前 $j$ 个数形成的每个数出现次数，很容易通过图形自相似的性质得到 $O(n^3)$ 的做法，当然，这是极其不优的。
- 你发现一个数被取模要么不变，要么至少减半，所以你设计了一个从后往前推的方法，每次用 $\text{map}$ 存储你需要的数和贡献数，然后每次从大到小取模。
- 你发现不成功的取模是 $O(n)$ 次的，所以成功的取模次数是数对数的总和的 $O(n\log w)$，总复杂度为 $O(n\log n\log w )$，[代码](https://www.luogu.com.cn/paste/0rbdsbys)。

---

## 作者：PosVII (赞：1)

**前言**

------------

不错的思维题，与 [P6791](https://gugeblog.blog.luogu.org/p6791-snoi2020-qu-dan-zi-ti-xie) 中我的做法相似。

**思路**

------------

不难知道若一个数后面出现了比它更小的数它就失效了，所以数组可以处理。

不难想到递归加差分，差分记录数字的出现，递归寻找数字。

而当其递归到可以直接差分或者不需递归时退出。

首先就是找到当前位置所属于的操作，我们可以将当前位置分为多个更小的操作再加剩下的数字继续递归。

同样不难想到我们可以在递归中加入一个参数记录该操作要重复的次数，可以优化较多时间。可是还是会 TLE。

思考有什么东西会重复，我们的每一轮操作会出现多次，会被分开递归，那么就对于每一轮操作一轮一轮向下递归，拿个数组存储操作出现次数即可。

**code**

------------

```
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int n,m,cnt;
long long arr[MAXN],q[MAXN],num[MAXN],p[MAXN];
void dfs(long long dep,long long sum) { 
	if(dep==0) return;
	int idx=upper_bound(q+1,q+1+m,dep)-q-1;
	if(idx==0) {
		num[1]+=sum,num[dep+1]-=sum;
		return;
	}
	p[idx]+=(dep/q[idx])*sum;
	dep%=q[idx];
	dfs(dep,sum);
}
int main() {
	scanf("%d %d",&n,&m);
	++m,arr[1]=n;
	for(int i=2;i<=m;++i) scanf("%lld",&arr[i]);
	for(int i=m;i>=1;--i) {
		if(!cnt||arr[i]<q[cnt]) q[++cnt]=arr[i];
	}
	for(int i=1;i<cnt-i+1;++i) swap(q[i],q[cnt-i+1]);
	m=cnt,p[m]=1;
	for(int i=m;i>1;--i) {
		if(p[i]) {
			p[i-1]+=(q[i]/q[i-1])*p[i];
			dfs(q[i]%q[i-1],p[i]);
		}
	} 
	num[1]+=p[1],num[q[1]+1]-=p[1];
	for(int i=1;i<=n;++i) {
		num[i]+=num[i-1];
		printf("%lld\n",num[i]);
	}
	return 0;
} 
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc003_e)

**题目大意**

> 给定序列 $a$，初始 $a=[1,2,\dots,n]$，$q$ 次操作，每次操作给定 $s$，将 $a$ 变成 $a^\infty[1,s]$，求最终每种元素出现次数。
>
> 数据范围：$n,q\le 10^5,s\le 10^{18}$。

**思路分析**

对于相邻的两次操作 $x,y$，如果 $x>y$ 那么操作 $x$ 没有意义，最终有效的操作是递增的单调栈上元素。

设最终的操作为 $s_1\sim s_m$，查询 $a[1,x]$ 可以找到第一个 $s_i<x$，分成 $\lfloor x/s_i\rfloor$ 个 $a[1,s_i]$ 和 $1$ 个 $a[1,x\bmod s_i]$。

停止递归时 $x<a_i$，此时 $1\sim x$ 各出现一次，维护这个 $a[1,x]$ 在答案中出现了几次，然后只需对 $1\sim x$ 出现次数前缀加。

暴力模拟，用 `map` 把本质相同操作合并，此时会访问 $s_1\sim s_n$，以及若干 $x\bmod s_i$，容易发现每次 $x\gets x\bmod s_i$ 至少减半，因此这些点只会访问 $\mathcal O(n\log V)$ 个。

时间复杂度 $\mathcal O(n\log V\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e5+5;
int n=1,N,q;
ll a[MAXN],s[MAXN];
signed main() {
	scanf("%lld%d",&a[1],&q),N=a[1];
	for(int i=1;i<=q;++i) {
		ll x; scanf("%lld",&x);
		while(n&&a[n]>=x) --n;
		a[++n]=x;
	}
	map <ll,ll> o;
	o[a[n]]=1;
	while(o.size()) {
		ll x=o.rbegin()->first,k=o.rbegin()->second;
		o.erase(--o.end());
		if(x<=a[1]) s[x]+=k;
		else {
			int i=lower_bound(a+1,a+n+1,x)-a-1;
			o[a[i]]+=(x/a[i])*k;
			if(x%a[i]) o[x%a[i]]+=k;
		}
	}
	for(int i=N;i>=1;--i) s[i]+=s[i+1];
	for(int i=1;i<=N;++i) printf("%lld\n",s[i]);
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

如果 $a_i \ge a_{i+1}$，我们认为 $a_i$ 是没用的，删掉就好了。接下来有 $a_i < a_{i+1}$ 对 $\forall 1 \le i < q$ 都成立。

这题有点像某年 CSP 的函数调用。设 $cnt_k$ 为，第 $k$ 次操作的结果在最终序列中出现的次数。

从后往前扫，可以把 $cnt_{i+1} \times \lfloor \dfrac{a_{i+1}}{a_i} \rfloor$ 加到 $cnt_i$ 中去。

这样还剩下长度为 $a_{i+1} \bmod a_i$，数量为 $cnt_{i+1}$ 的边角料。

使用二分，找到 $j$ 使得 $a_j \le a_{i+1} \bmod a_i < a_{j+1}$。这时候发现 $cnt_j$ 要加上 $cnt_{i+1} \times \lfloor \dfrac{a_{i+1} \bmod a_i}{a_j} \rfloor$，并且转换为 $cnt_{i+1}$ 个长度为 $(a_{i+1} \bmod a_i) \bmod a_{j}$ 的边角料。

一个数对比他小的数取模，至少减小一半。因此复杂度为 $O(n \log A \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
int n,q,m,a[MAXN],ans[MAXN],mul[MAXN];
void solve(int u,int ad) {
	if(!u) return ;
	int pos=upper_bound(a+1,a+m+1,u)-a-1;
	if(pos==0) return ans[1]+=ad,ans[u+1]-=ad,void();
	mul[pos]+=u/a[pos]*ad,solve(u%a[pos],ad);
	return ;	
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q,a[++m]=n;
	ffor(i,1,q) {
		int len;
		cin>>len;
		while(len<=a[m]) m--;
		a[++m]=len;
	}
	mul[m]=1;
	roff(i,m,2) {
		mul[i-1]+=mul[i]*(a[i]/a[i-1]);
		solve(a[i]%a[i-1],mul[i]);
	}
	ffor(i,1,n) ans[i]+=ans[i-1];
	ffor(i,1,a[1]) ans[i]+=mul[1];
	ffor(i,1,n) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：D2T1 (赞：0)

写了个奇怪的做法，以为会 T 结果过了。

首先用单调栈处理出有效的操作，个数设为 $m$，然后从后往前考虑。

维护一个集合，集合内一个元素 $(i,j)$ 表示数组中 $[1,i]$ 的数在后面会出现 $j$ 次。设 $cnt_i$ 表示第 $i$ 个操作后形成的序列在后面的操作中又会重复几次。初始 $cnt_m = 1$。

遍历 $k$ 从 $m$ 到 $2$，首先处理集合中第一维在 $q_{k-1}$ 到 $q_{k}$ 之间的数，集合内每一项会对 $cnt_{k-1}$ 贡献若干倍，然后可能还有一段多余的，继续插入到集合中。最后考虑 $cnt_k$ 对 $cnt_{k-1}$ 的贡献，和上面的类似。具体贡献方式可以看代码。

```cpp
const int N = 1e5 + 10;
int n, Q, c;
ll q[N], cnt[N], ans[N];

set<ll> s;
map<ll, ll> mp;

ll mx(){
	if(s.empty()){
		return -1;
	}
	auto i = s.end();
	return *(--i);
}
void dmx(){
	auto i = s.end();
	-- i;
	s.erase(i);
}

void solve(){
	read(n, Q);
	q[++c] = n;
	for(int i = 1; i <= Q; ++ i){
		ll t;
		read(t);
		while(c && q[c] >= t){
			-- c;
		}
		q[++c] = t;
	}
	cnt[c] = 1;
	for(int i = c; i >= 1; -- i){
		ll t = mx();
		while(t >= q[i]){
			cnt[i] += mp[t] * (t / q[i]);
			ll tmp = mp[t];
			mp[t] = 0;
			t %= q[i];
			mp[t] += tmp;
			s.insert(t);
			dmx();
			t = mx();
		}
		if(i == 1){
			break;
		}
		cnt[i-1] += cnt[i] * (q[i] / q[i-1]);
		q[i] %= q[i-1];
		mp[q[i]] += cnt[i];
		s.insert(q[i]);
	}
	ans[1] += cnt[1];
	ans[q[1]+1] -= cnt[1];
	for(int i = 1; i < n; ++ i){
		ans[1] += mp[i];
		ans[i+1] -= mp[i];
	}
	for(int i = 1; i <= n; ++ i){
		ans[i] += ans[i-1];
		println(ans[i]);
	}
}
```

显然这个做法是对的，但是复杂度不知道是什么。

容易发现复杂度瓶颈在于集合内数的插入与删除。考虑往集合里插入了一个 $i$，它被取出来时可能会变成 $i\bmod q_x$ 又插入集合；然后被取出来时会变成 $i\bmod q_x\bmod q_y$，以此类推。可以发现，若 $q_y\leq \frac 12 q_x$，$i'\leq q_y\leq \frac i2$，复杂度是对的；否则 $i$ 会减掉 $q_y$，至少减掉 $\frac 12$，复杂度也是对的。

所以大概复杂度是 $O(n\log n\log V)$，然后就过了。

---

## 作者：ducati (赞：0)

## Description

[传送门](https://www.luogu.com.cn/problem/AT_agc003_e)

## Solution

容易发现，若 $Q_i>Q_{i+1}(1 \le i < N)$，则删去 $Q_i$ 不影响答案。仅保留 $Q$ 各后缀严格最小值，得到递增数列。

为方便叙述，令 $P_i$ 表示执行前 $i$ 次操作后的序列。考虑 $\text{dp}$，令 $f_{i,j}$ 表示，$j$ 在 $P_i$ 中的出现次数。

考虑如何转移。令 $t=\left \lfloor \frac {A_i} {A_{i-1}} \right \rfloor$，则 $P_i$ 由 $t$ 个 $P_{i-1}$ 和 $P_{i-1}$ 长度为 $A_i \bmod A_{i-1}$ 的前缀拼接而成。将 $f_{i,j}$ 初始化为 $t \times f_{i-1,j}$。接着找到 $A$ 中首个满足 $A_p \le A_i \bmod t$ 的位置 $p$，再将 $f_{i,j}$ 加上 $\left \lfloor \frac {A_i \bmod t} {A_p} \right \rfloor \times f_{p,j}$，并接着递归下去。特别的，若不存在这样的 $p$，则将 $f_i$ 的对应前缀加 $1$ 并结束递归。

容易发现，每递归一次 $A$ 至少减半，因此递归总次数是 $O(Q \log V)$ 的，其中 $V$ 是值域。但每次找 $p$ 需要二分，且要同时维护 $N$ 个 $j$，总复杂度 $O(Q \log^2 V + QN \log V)$，无法通过。

考虑优化。注意到以下性质 ：
- 转移系数与 $j$ 无关。
- 我们只关心 $f_{Q,1},f_{Q,2},\cdots,f_{Q,N}$。

考虑所有形如 $\lceil$ $\forall j \in [1,n]$，将 $f_{i,j}$ 加上 $kf_{p,j}$ $\rfloor$ 的转移，连一条 $p$ 到 $i$ 的，边权 $=k$ 的边，构成一张 DAG。那么，将 $f_{i,1},f_{i,2},\cdots,f_{i,L}$ 加一的边界情况，能对 $ans_1,ans_2,\cdots,ans_L$ 产生贡献，而这个贡献是 $i$ 到 $n$ 所有路径边权乘积之和 $g_i$。

那么，我们对 DAG 进行隐式的拓扑排序，递推出所有的 $g$，使用差分维护对答案的贡献即可。时间复杂度 $O(Q \log^2 V)$。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
#define inf 1000000000000000007
using namespace std;
const int N=1e5+5;

int read(){
	int s=0,w=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if(ch=='-')w=-w;ch=getchar();}
	while (ch>='0'&&ch<='9') {s=(s<<1)+(s<<3)+(ch^'0');ch=getchar();}
	return s*w;
}
int n,m,q,a[N],b[N],w[N],g[N],ok[N];
void dfs(int val,int gv){
	int p=upper_bound(b+1,b+m+1,val)-b-1;
	if (!p)  w[val]+=gv;
	else{
		g[p]+=gv*(val/b[p]),val%=b[p];
		if (val)  dfs(val,gv);
	}
}
signed main(){
	n=a[0]=read(),q=read();
	for (int i=1;i<=q;i++)  a[i]=read();
	for (int i=q,mn=inf;~i;i--){
		if (a[i]<mn)  mn=a[i],ok[i]=1;
	}
	for (int i=0;i<=q;i++){
		if (ok[i])  b[++m]=a[i];
	}
	g[m]=1;
	for (int i=m;i>1;i--)  g[i-1]+=(b[i]/b[i-1])*g[i],dfs(b[i]%b[i-1],g[i]);
	w[b[1]]+=g[1];
	for (int i=n;i;i--)  w[i]+=w[i+1];
	for (int i=1;i<=n;i++)  printf("%lld\n",w[i]);
	return 0;
}
```


---

## 作者：翼德天尊 (赞：0)

E 正解跟场上想的很像。

首先注意到如果对于两个相邻的操作 $q_i$ 和 $q_{i+1}$，$q_i>q_{i+1}$，那么 $q_i$ 对于答案其实是无贡献的，完全可以被 $q_{i+1}$ 完美替代。

所以我们可以先用单调栈处理出一个单调递增的 $q$ 数组，再考虑怎么做。

设最终变成的序列为 $a$，对于单调递增数组的 $q_i$ 和 $q_{i+1}$，设 $q_{i+1}=rq_i+s$，$r,s\in N$，则 $[a_{q_{i}+1},a_{q_{i+1}}]$ 这一段的对于答案贡献显然是和 $r\times[a_{1},a_{q_i}]+[a_{1},a_{s}]$ 相同的。

这个性质就很有意思了。

如果我们已经处理完了 $[1,i]$ 询问的贡献，在处理 $q_{i+1}$ 时，我们好像就可以将所有答案乘上 $r$，再加上$[a_1,a_s]$ 的贡献。

$[a_1,a_s]$ 的贡献又该怎么求？可以再考虑向前找到一个 $j$ 使得 $q_j<a_s$，且 $q_{j+1}\ge a_s$ ，再取模、向前递归。

这样做复杂度显然是对的，因为每次取模之后我们的余数必定至少减半，所以递归的时间复杂度只有 $\log$，找 $j$ 需要二分，也是一个 $\log$。一共只有两只 $\log$，十分优秀。

不过我们发现如果这样做的话，我们很难在递归过程中快速计算贡献——这些贡献是复杂的，数据结构很难维护它们。不过我们注意到后面的询问用到的是前面的答案，将前面的贡献加到后面困难，那我们可以尝试将后面的询问挂在前面啊！

考虑倒序处理询问，每次询问向前不断递归，将子询问挂在前面的 $q$ 上，作一个类似于离线差分的操作，最后统计答案即可。

> **tips：正着做不好转移，就可以考虑倒着做向前挂询问。**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
#define st set<node>::iterator
const int N=1e5+5;
int n,q,a[N],stot,s[N],ans[N];
int read(){
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
} 
void solve(int x,int r,int g){
	int l=1,pos=0;
	while (l<=r){
		int mid=l+r>>1;
		if (a[mid]<x) l=mid+1,pos=mid;
		else r=mid-1;
	}
	if (pos==0){
		ans[x]+=g;
		return;
	}
	int z=x/a[pos]*g;
	s[pos]+=z;
	solve(x%a[pos],pos,g);
}
signed main(){
	n=read(),q=read();
	a[++stot]=n;
	for (int i=1;i<=q;i++){
		int x=read();
		while (stot&&x<=a[stot]) --stot;
		a[++stot]=x;
	}
	s[stot]=1;
	for (int i=stot;i>=1;i--){
		solve(a[i],i-1,s[i]);
	}
	for (int i=n-1;i>=1;i--)
		ans[i]+=ans[i+1];
	for (int i=1;i<=n;i++)
		cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：太阳起晚了呢 (赞：0)

# 解

首先可以发现，有用的序列一定是单调上升的，所以首先可以用一个单调栈对原序列操作一下子。
从后往前考虑（因为我们知道最后序列的长度一定是操作序列最后一个元素的值）

记当前考虑的这个元素是第 $i$ 个，前面一个是第 $i-1$ 个，假设 $q_i \geq q_{i-1}$ 那么答案序列的形式会是有 $\left\lfloor\dfrac{q_i}{q_{i-1}}\right\rfloor$ 个 $q_{i-1}$ 操作后的结果加上一些尾巴。

假设每次操作都没有上述的这种尾巴，那么可以直接一直统计到开头，计算有多少个第一个操作元素的循环，当作一个系数直接乘上去就好了，那考虑这个尾巴怎么处理。

对于这多出来的一小部分 长度 $q_i - \left\lfloor\dfrac{q_i}{q_{i-1}}\right\rfloor \times q_{i-1} $ 记作 $l$ ，那么我们发现，只需要在 $[1,i-1]$ 内向左找到第一个比 $l $ 小的元素 $q_k$ 发现这里 $l$ 和 $q_k$ 的关系实际上和 $q_i$ 和 $q_{i-1}$ 的关系是一样的，递归处理就可以了。

最后这一切都会归结到序列开头那个元素，需要特判一下，如果还有剩余就直接加到答案里。

那么这个区间加，求所有单点和的问题可以用差分去做

代码

```cpp
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
int n,Q;
const int maxn=1e5+19;
int q[maxn],a[maxn],p,b[maxn];
int f[maxn];
void sec(int left,int tim)
{
	//if(!left) return ;
	int po=upper_bound(a+1,a+p+1,left)-a-1;
	if(!po) b[1]+=tim,b[left+1]-=tim; 
	else f[po]+=left/a[po]*tim,sec(left%a[po],tim);
}
signed main()
{
	scanf("%lld%lld",&n,&Q);
	for(int i=1;i<=Q;i++) scanf("%lld",&q[i]);
	p=0;
	a[++p]=n;
	for(int i=1;i<=Q;i++)
	{
		while(p>0 && q[i]<=a[p]) p--;
		a[++p]=q[i];
	}
	//for(int i=1;i<=p;i++) cout<<a[i]<<' ';
	f[p]=1;
	//cout<<p<<endl;
	for(int i=p;i>=2;i--)
	{
		f[i-1]+=a[i]/a[i-1]*f[i];
		sec(a[i]%a[i-1],f[i]);
	}
	b[1]+=f[1];b[a[1]+1]-=f[1];
	for(int i=1;i<=n;i++)
		printf("%lld\n",b[i]+=b[i-1]);
	return 0;
}

```


---

## 作者：ImmortalWatcher (赞：0)

- 对于较难处理的递归操作，可以直接当成子问题重新考虑。

对于这道题，比较容易想到的是如果后面的 $q$ 比前面的小，那么之前的修改一定都没用。

所以我们可以处理出真正有用的操作序列，有 $q$ 单调的性质。

然后考虑每一次操作实际上就是上一个串重复若干次再加上一段散串。

然后我们可以发现这段散串实际上也是可以由前面的某个字符串不断重复再加上一段散串得到的，最后一定能完整拼完。

所以对于重复的那一段，我们直接计数。对于散串，可以递归当做子问题继续处理，处理到没有更小的串分割它的时候就直接计算这个串的贡献，是一段区间加法，可以通过差分实现。

```cpp
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
int n,q,a[100010],cnt[100010],f[100010],top,x;
void calc(int x,int y)
{
    if (!x) return;
    int t=upper_bound(a+1,a+top+1,x)-a-1;
    if (!t) cnt[1]+=y,cnt[x+1]-=y;
    else f[t]+=x/a[t]*y,calc(x%a[t],y);
}
signed main()
{
    scanf("%lld%lld",&n,&q);
    a[++top]=n;
    for (int i=1;i<=q;i++)
    {
        scanf("%lld",&x);
        while (x<=a[top]) top--;
        a[++top]=x;
    }
    f[top]=1;
    for (int i=top;i>=2;i--)
        f[i-1]+=a[i]/a[i-1]*f[i],calc(a[i]%a[i-1],f[i]);
    cnt[1]+=f[1];cnt[a[1]+1]-=f[1];
    for (int i=1;i<=n;i++)
        cnt[i]+=cnt[i-1];
    for (int i=1;i<=n;i++)
        printf("%lld\n",cnt[i]);
    return 0;
}
```


---

## 作者：win114514 (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Al-lA/p/17639681.html)。

神仙思维题，那我的评价是太妙了。

### 思路

我们发现正的十分难以维护这个过程。

考虑可以倒着进行这个操作。

容易发现对于整块，我们找到在前面第一个小于它的 $a_i$。

然后就会有一个贡献的转移，$f_i=f_{now}\times \frac{a_{now}}{a_i}$。

至于散块，我们发现可以通过这样的递归继续处理。

即，$\text{solve}(a_{now}\bmod a_i)$。

至于转移的时候还有一些系数上的问题，仔细处理一下即可。

最后使用差分进行区间加的操作。

答案再算一遍前缀和即可。

### Code

[AC记录](https://atcoder.jp/contests/agc003/submissions/44674750)。

---

## 作者：约瑟夫用脑玩 (赞：0)

比较神奇的一道题，看了一眼就有一点可做的感觉，典型的 AGC 风格。

~~当我状态好的时候才有概率独立想出做法。~~

给出一种清晰的思路，可能更好理解，起码我看现有题解都看不懂。

首先对于 $q_i\ge q_{i+1}$，去除 $q_i$，随便做一下。

于是有了条件 $\forall q_i<q_{i+1}$，将最后的数组分段，令第 $i$ 段包含 $S_i=[q_{i-1}+1,q_i]$，长度为 $d_i=q_i-q_{i-1}$，不妨令 $q_0=0$。

于是对于一个位置 $p$ 我们可以用它处于哪个段的哪个位置来表示，即存在唯一的 $x,y$，使得 $p\in S_x,y\in[1,d_x],p=q_{x-1}+y$，不妨用 $(x,y)$ 来表示这样的 $p$。

反之用 $P(x,y)=p$ 在最终数组的位置，每个位置 $(x,y)$ 对答案数组 $ans$ 都有一个贡献，不妨令为 $W(x,y)$，$W(p)$ 也表示同样的含义。

注意这里的 $W$ 是将贡献累进答案数组的一个过程而不是一个数组，毕竟我们不可能一直带着一个数组进行运算，而只是考虑贡献。

容易发现 $W(1,k),k\in[1,d_1]$ 是简单的，就是 $\forall i\in[1,k],ans_i\to ans_i+1$，而最后我们要求的是 $W(n,d_n)$ 后的答案数组。

于是考虑递归处理出 $W(x,y)$ 的贡献，将递归下一层设为 $W(x',y')$，令 $b=\lfloor \frac{y}{q_{x-1}}\rfloor,r=y\bmod q_{x-1}$：

由数组的构造过程可以发现出现了多段重复的 $(x-1,d_{x-1})$，直接贡献 $(b+1)\times W(x-1,d_{x-1})$。
  
除此之外贡献了一次 $W(r)$，简单实现就是直接二分找到对应的位置 $P(x',y')=r$，然后递归调用 $W(x',y')$ 即可。

考虑复杂度，令 $(x,d_x)$ 为“标记位置”，先考虑非“标记位置”：

由 $P(x,y)\to P(x',y')$，有 $(b+1)q_{x-1}+r\ge q_{x-1}+r> 2r\to r$，故位置每次必定减半。

而当 $P(x,y)\le d_1$ 时直接贡献到答案数组，结束，将递归调用的复杂度在第一次非“标记位置”就考虑进去，后面就不算其调用次数。

调用一次非标记的 $W(x,y)$ 会递归 $\log$ 次，带来 $O(\log^2)$ 的复杂度。（注意转移时有二分）

再考虑“标记位置”：

类似搜索的记忆化，每次将 $(b+1)W(x-1,d_{x-1})$ 累计到 $x-1$ 上再一起计算，即 $b+1\to tot_{x-1}$，只需一次调用 $tot_{x-1}W(x-1,d_{x-1})$。

而调用一次 $W(x-1,d_{x-1})$ 最多带来一次非“标记位置”，即调用“标记位置”与非“标记位置”（只考虑第一次而不考虑递归次数）总次数为 $n$。

总复杂度 $O(n\times\log^2)$，~~其实很好写但~~代码还是鸽了。

正文结束，下文是对进一步复杂度的思考，~~可能是错的~~。

------------

起因：这里怎么有篇 $\log$ 的题解，艹这难道不是 $\log^2$ 的？

发现递归过程的位置只会越来越小，我们希望只用一个单调的指针而不是二分来找出所有的转移位置，这能做到吗？

同时发现第一次调用的 $W(n,d_n)$ 也是“标记位置”，也就是说所有的非“标记位置”只会由“标记位置”引出。

于是我们只丢入 $n$ 个标记位置，用某个不知名的数据结构维护当前最靠后的位置到了哪里，再用一个指针在 $q$ 上单调移动。

指针部分是没有问题的，但是最靠后的位置我们需要支持这样的东西：查询最大值，减小键值。

除了将 $\log n$ 的复杂度改为 $\log_wV$ 以外我没有更多想法，其中 $V$ 是值域。

---

