# Little Girl and Maximum XOR

## 题目描述

A little girl loves problems on bitwise operations very much. Here's one of them.

You are given two integers $ l $ and $ r $ . Let's consider the values of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF276D/e4d673f94fffa65030d2edd227a746e3a121dade.png) for all pairs of integers $ a $ and $ b $ $ (l<=a<=b<=r) $ . Your task is to find the maximum value among all considered ones.

Expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF276D/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) means applying bitwise excluding or operation to integers $ x $ and $ y $ . The given operation exists in all modern programming languages, for example, in languages $ C $ ++ and $ Java $ it is represented as "^", in $ Pascal $ — as «xor».

## 样例 #1

### 输入

```
1 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
8 16
```

### 输出

```
31
```

## 样例 #3

### 输入

```
1 1
```

### 输出

```
0
```

# 题解

## 作者：Piwry (赞：5)

这里再补充说明下代码最短的做法把。

## 解析

其实我觉得这种做法本质就是贪心。

首先从 `long long` 最高位开始向低位比较 $l, r$，从最高位到第一个不同的位置之间的位置（不包含这个不同的位置）是不可能有贡献的：因为如果要产生贡献，就意味着 $a, b$ 有一个数在这位为 $0$，那么那个数一定比 $l$ 小，是**不在范围内**的。

并且我们设答案两个数在这范围内的二进制位也都和 $l, r$ 相同。

对于第一个不同的位置，可以保证此时 $r$ 这位为 $1$，$l$ 这位为 $0$，否则 $l$ 就会小于 $r$。因此我们可以设答案的某个数这位为 $1$，剩下的位（注意高位上面设过了）均为 $0$，可知道这个数一定是**在范围内**的（因为在不同的这位它大于 $l$，于是后面位怎样都保证大于 $l$；而我们将后面位都设为 $0$ 就保证了它一定小于或等于 $r$）。

对于另外一个数，设不同的这位为 $0$，剩下的位都为 $1$，也可知道这个数一定是在范围内的（因为在不同的这位它小于 $r$，于是后面位怎样它也仍小于 $r$；而我们将后面位都设为 $1$ 就保证了它一定大于或等于 $l$）。

&nbsp;

举个例子，我们有 $l=001101101, r=011011010$（二进制），就可以按上面的贪心构造出一组答案 $a=010000000, b=001111111$。

~~（输出大概就不用说了吧（~~

## CODE

（真的超短）

```cpp
#include <cstdio>

int main(){
	long long a, b; scanf("%lld%lld", &a, &b);
	long long p =(1ll<<62);
	while(p && ((a&p) == (b&p))) p >>=1;
	if(p) printf("%lld", (p<<1)-1);
	else putchar('0');
}
```


---

## 作者：da32s1da (赞：5)

我们把$a,b$从大到小相同的二进制位舍去，到第一个不同的位，则答案是**该位代表的值$\times 2-1$**。a,b相同答案是0。

证明如下：
- 舍去相同的二进制位后，设$a$变成$a'$，$b$变成$b'$，不同的位代表的值为$2^k$，则有$a'\lt 2^k \le b'$，所以答案是$2^{k+1}-1$
- a,b相同答案显然。

```
#include<cstdio>
typedef long long LL;
LL a,b,d,BJ;
int main(){
	scanf("%I64d%I64d",&a,&b);
	d=1ll<<60;BJ=1;
	while(BJ&&d){
		while(d>b)d>>=1;
		if(a>=d)a^=d,b^=d;//去掉相同的位
		else BJ=0;
	}
	printf("%I64d\n",(d<<1)-(d>0));
    //这里放到一起输出了
}
```

---

## 作者：Pecco (赞：4)

这题也可以用数位DP，当然肯定比贪心长很多。

需要注意的是，这不是计数问题，所以不能用类似于`f(r)-f(l-1)`的方法。可以对上、下界分别设`limit`标记来解决。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll L[64], R[64], cnt, dp[64][2][2];
ll dfs(int pos, int limitl, int limitr)
{
    ll ans = 0;
    if (pos == cnt)
        return 0;
    if (dp[pos][limitl][limitr] != -1)
        return dp[pos][limitl][limitr];
    for (ll u = (limitl ? L[pos] : 0); u <= (limitr ? R[pos] : 1); ++u)
        for (ll v = (limitl ? L[pos] : 0); v <= (limitr ? R[pos] : 1); ++v)
            ans = max(ans, ((u ^ v) << (cnt - pos - 1)) + dfs(pos + 1, limitl && u == L[pos], limitr && v == R[pos]));
    dp[pos][limitl][limitr] = ans;
    return ans;
}
ll f(ll x, ll y)
{
    int cnt1 = 0, cnt2 = 0;
    while (x)
        L[cnt1++] = x & 1, x >>= 1;
    while (y)
        R[cnt2++] = y & 1, y >>= 1;
    cnt = max(cnt1, cnt2);
    reverse(L, L + cnt);
    reverse(R, R + cnt);
    memset(dp, -1, sizeof(dp));
    return dfs(0, true, true);
}
int main()
{
    ios::sync_with_stdio(false);
    ll x, y;
    cin >> x >> y;
    cout << f(x, y) << endl;
    return 0;
}
```

---

## 作者：rui_er (赞：2)

[双倍经验](https://www.luogu.com.cn/problem/SP25844)。

以下用 $\oplus$ 表示异或运算。

先说结论：设 $x=L\oplus R$，则答案为最小的 $2^k-1$ 使得 $2^k-1\ge x$ 即 $2^k > x$。

（一）答案不可能超过 $2^k-1$。

为了让异或后最高位尽量高，我们先取一个最高位最高的数，也就是 $R$，然后再取一个数使得该位尽量为 $0$。

如果 $L$ 的该位为 $0$，符合条件，此时答案最高位与 $x$ 都相同，而 $2^k-1$ 是最高位相同的最大的数，所以答案一定不超过 $2^k-1$。如果 $L$ 的该位为 $1$，则该位异或出来为 $0$，不考虑这一位，去找后面的位也是同理。极端情况是 $L=R$，此时 $x=0$，$2^k-1=0$ 也是没有问题的。

（二）答案可以取到 $2^k-1$。

我们称在二进制下表示 $0$ 或 $2^i$ 的数位为“第 $i$ 位”。

因为 $x=L\oplus R$ 在第 $k-1$ 位为 $1$，说明 $L\sim R$ 之间有一个位置的第 $k-1$ 位发生了变化。而 $L\sim R$ 是连续变化的，每次加一，也就是说必然有一个位置从 $\underbrace{11\cdots 1}_{k-1\ \text{个}}$ 变成了 $1\underbrace{00\cdots 0}_{k-1\ \text{个}}$，显然这两个数的异或为 $2^k-1$。

综上，结论正确。

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=y;x<=z;x++)
#define per(x,y,z) for(ll x=y;x>=z;x--)
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

int main() {
	ll L, R;
	scanf("%lld%lld", &L, &R);
	R ^= L;
	for(ll i=0;;i++) {
		if((1LL << i) > R) {
			printf("%lld\n", (1LL << i) - 1);
			break;
		}
	} 
	return 0;
}
```

---

## 作者：World_Creater (赞：1)

$1700$ 诈骗题。  
我们只需要考虑这么一种情况：设 $x=2^w,y=x-1$ 如果 $l\leq y$ 且 $x\leq r$，则 $x\oplus y$ 一定为一个合法解，**且在只取 $w$ 位二进制作为答案的时候是最优的**。  
那我们只需要从大到小枚举 $w$，发现一种可行的情况就直接输出，否则第 $w$ 位无论怎么取异或值一定为 $0$，直接删掉这一位，枚举下一位。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
signed main()
{
    cin>>l>>r;
    if(l==r)
    {
        cout<<0;
        return 0;
    }
    for(signed w=63;w>=0;w--)
    {
        k=1uLL<<w;
        if(l<k&&k<=r)//找到可行解直接输出。
        {
            cout<<(k^(k-1));
            return 0;
        }
        if(l>=k)
        {
            l^=k;//删除最高位
            r^=k;
        }
    }
}

```

---

## 作者：奇米 (赞：1)

## 题解 - $\mathrm{CF276D}$

### **题目意思**

* [题目传送门](https://www.luogu.com.cn/problem/CF276D)

* 给你一个区间$[l,r]$，求$max(a\ xor\ b) ,l\leq a\leq b\leq r$

### $\mathrm{Sol}$

* **贪心+位运算**

* 我们首先考虑异或的性质，即二进位不同才能产生贡献。

* 那么我们就有了个很简单的想法就是在**保持上下界**的情况从高位向低位取（即强制让某些位不同）。

* 还有的就是细节问题，具体看代码。

### $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
#define For(i,a,b) for ( int i=(a);i<=(b);i++ )
#define Dow(i,b,a) for ( int i=(b);i>=(a);i-- )
#define GO(i,x) for ( int i=head[x];i;i=e[i].nex )
#define mem(x,s) memset(x,s,sizeof(x))
#define cpy(x,s) memcpy(x,s,sizeof(x))
#define YES return puts("YES"),0
#define NO return puts("NO"),0
#define GG return puts("0"),0
#define pb push_back
#define int long long 
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int mod=1e9+7;
const int mo=998244353;
const int N=1e5+5;

int a,b,bit[66],Bit[66],ans,all;

signed main()
{
	a=read();
	b=read();
	if(a==b) GG;
	if(a>b) swap(a,b);
	Dow(i,63,0) 
		if((b>>i)&1ll) bit[i]=1;
	Dow(i,63,0) 
		if((a>>i)&1ll) Bit[i]=1; 
	int flg=0,OK=0;
  	//OK保证满足下界，flg保证满足上界
	Dow(i,63,0) 
	{
		if(Bit[i]&&!OK)
		{
			if(all) ans+=(1ll<<i);
			continue;
		}
		if(!bit[i]&&all) 
			ans+=(1ll<<i),OK=1;
		if(bit[i])
		{
			if(!Bit[i]) all=1,ans+=(1ll<<i);
			if(Bit[i]) ans+=(1ll<<i);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```





---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/16063611.html)

# 题目大意

在区间 $[l,r]$ 中找出两个数 $a,b(a\le b)$,使得 $a\oplus b$ 达到最大。

# 题目分析

这是一道贪心题。

一下简称十进制数 $k$ 在二进制下表示为 $k_2$。

我们先找到 $r_2$ 第一个与 $l_2$ 不同的位置（即 $r_2$ 的某一位为 $1$，$l_2$ 的这一位为 $0$）。设答案的 $a_2$ 这一位为 $1$，剩下的都是 $0$。这样可以保证 $a$ 一定大于等于 $l$，小于等于 $r$。另一个 $b$ 呢，设这一位为 $0$，剩下的都是 $1$，也满足条件。

设第一个满足条件的位数是 $k$，那么最后的答案就是 $2^{k+1}-1$。

也就是 $1111\dots1111$，共有 $k$ 个 $1$。

# 代码

```cpp
//2022/3/8
//2022/3/26
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#define int long long
#define enter() putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : -(x))
const int mod = 1e9 + 7;
inline int MOD(int x) {
	while (x < 0) x += mod;
	while (x >= mod) x -= mod;
	return x;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
using namespace std;

int l,r;
#undef int
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	#define int long long
	l = read(),r = read();
	int p = (1ll << 62);
	while (p && (l & p) == (r & p)) p >>= 1ll;
	if (p) printf("%lld\n",(p << 1ll) - 1);
	else puts("0");

	return 0;
}
```

---

## 作者：aRenBigFather (赞：0)

贡献一个超级麻烦的写法...

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxbit = 66;
typedef unsigned long long ull;
ull a,b;
int abit[maxbit],bbit[maxbit],ans[maxbit];
int lena = 0,lenb = 0;
void getbit(int &len,int _a[],ull val){
    len = 0;
    memset(_a,0,sizeof _a);
    for(int i=1;i<maxbit-1;i++){
        if(val & (1ll << (i-1))){
            _a[i] = 1;
            len = max(len,i);
        }
    }
}
int main(){
    cin >> a >> b;
    memset(ans,0,sizeof ans);
    if(a == b){
        puts("0");
        return 0;
    }else if(a > b) swap(a,b);
    getbit(lena,abit,a);
    getbit(lenb,bbit,b);
    bool aflag = true,bflag = true;
    for(int i=lenb;i>=1;i--){
        if(i > lena){
            ans[i] = 1;
            continue;
        }
        if(!aflag && !bflag){
            ans[i] = 1;
            continue;
        }
        if(abit[i] == bbit[i] && abit[i]){
            if(b - (1ll<<(i-1)) > a){
                ans[i] = 1;
                bflag = false; //b[i]后面位数可以任取了
            }
        }else if(abit[i] == bbit[i] && !abit[i]){
            if(a + (1ll<<(i-1)) < b){
                ans[i] = 1;
                aflag = false; //a[i]后面位数可以任取了
            }
        }else if(!abit[i] && bbit[i]){
            ans[i] = 1;
            aflag = bflag = false; //互相取反,i后面都可以任取了
        }else{
            ans[i] = 1;
        }
    }
    ull fans = 0;
    for(int i=1;i<=lenb;i++){
        fans += ans[i] * (1ll << (i-1));
    }
    cout << fans << endl;
    return 0;
}
```

---

