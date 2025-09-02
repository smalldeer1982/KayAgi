# Increasing by Modulo

## 题目描述

Toad Zitz has an array of integers, each integer is between $ 0 $ and $ m-1 $ inclusive. The integers are $ a_1, a_2, \ldots, a_n $ .

In one operation Zitz can choose an integer $ k $ and $ k $ indices $ i_1, i_2, \ldots, i_k $ such that $ 1 \leq i_1 < i_2 < \ldots < i_k \leq n $ . He should then change $ a_{i_j} $ to $ ((a_{i_j}+1) \bmod m) $ for each chosen integer $ i_j $ . The integer $ m $ is fixed for all operations and indices.

Here $ x \bmod y $ denotes the remainder of the division of $ x $ by $ y $ .

Zitz wants to make his array non-decreasing with the minimum number of such operations. Find this minimum number of operations.

## 说明/提示

In the first example, the array is already non-decreasing, so the answer is $ 0 $ .

In the second example, you can choose $ k=2 $ , $ i_1 = 2 $ , $ i_2 = 5 $ , the array becomes $ [0,0,1,3,3] $ . It is non-decreasing, so the answer is $ 1 $ .

## 样例 #1

### 输入

```
5 3
0 0 0 1 2
```

### 输出

```
0
```

## 样例 #2

### 输入

```
5 7
0 6 1 3 2
```

### 输出

```
1
```

# 题解

## 作者：qwaszx (赞：5)

这题难度显然到不了紫啊...

设$f(x)$表示能否在$x$次操作之内达到要求，显然单调.于是可以二分，二分之后只需要贪心地判断，即每次都尽量让最后面的数最小.现在假设二分的次数是$x$

1. 如果$a[i]<a[i-1]$，那么我们必须使用至少$a[i-1]-a[i]$次来使得非降.并且我们一定希望$a[i]$最小，所以如果可以的话就直接把它变成$a[i-1]$

2. 如果$a[i]>a[i-1]$，那么如果能把它变成$a[i-1]$是最好的，这样需要的次数是$a[i-1]+m-a[i]$.如果变不成就保持原样.

3. 如果$a[i]=a[i-1]$，那么什么都不需要干.

然后这题就切了.

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=5e5;
int a[N],n,m,w[N];
int judge(int x)
{
    for(int i=1;i<=n;i++)a[i]=w[i];
    for(int i=1;i<=n;i++)
    {
        if(a[i]<a[i-1])
        {
            if(a[i-1]-a[i]>x)return 0;
            a[i]=a[i-1];
        }
        else
            if(a[i-1]+m-a[i]<=x)a[i]=a[i-1];
    }
    return 1;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",w+i);
    int l=0,r=m,mid;
    while(l<r)
    {
        mid=(l+r)>>1;
        if(judge(mid))r=mid;
        else l=mid+1;
    }
    cout<<l<<endl;
}
```

---

## 作者：⚡小林子⚡ (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1168A)

## 题目大意：

给定一数列 $a$，满足 $0\le a_i\le m - 1$。

定义 $a_i$ 上的一次操作为 $a_i=(a_i + 1)\mod m$。

现想将 $a$ 变成不递减的数列，设 $f_i$ 是在 $a_i$ 上的操作数，求 $(f_i)_{max}$。

## Solution：

首先很显然答案具有单调性：如果 $x$ 次可以成功，$x+1$ 次一定可成功，可写二分答案。

考虑怎么写 check 函数（有一点贪心思想）：

- 开始时将 $a_1$ 变为它能变成的最小值。

- 对于 $a_2$ ~ $a_n$，只需判断是否能变成不小于 $a_{i-1}$ 的数即可，如果无法变则 check 失败。

考场代码写的有些奇怪，判断的是刚好加 mid 时会变成多少，再判断有没有受到取模影响来分类讨论，实际上只需判断变成 $a_{i-1}$ 需要的操作数与 $mid$ 的大小关系，比 mid 大且 $a_i < a_{i-1}$ 就直接失败。

坑......倒也没啥，只要能写出 check 函数就 A 了。

Code：

```cpp
# include<bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
int n, m, a[N], b[N];
inline bool check(int mid) {
	if(mid == m) return 1; // 防止二分到 m 的情况，感觉下面的 check 不适用就直接返回 1 了 
	memcpy(b, a, sizeof a); // 将 a 复制一份以供下面的贪心 
	int tmp = (b[1] + mid) % m, i;
	if(tmp < b[1]) b[1] = 0; // 单独处理 b[1]，能到 0 就到 
	for(i = 2; i <= n; i++) {
		tmp = (b[i] + mid) % m;
		if(tmp < b[i]) { // 受到取模影响 
			if(0 <= b[i - 1] && b[i - 1] <= tmp)
				b[i] = b[i - 1];
			else if(b[i] <= b[i - 1] && b[i - 1] < m)
				b[i] = b[i - 1];
		} // 只要在 [0,tmp] 或 [b[i],m-1] 就可以变成 b[i-1] 
		else {
			if(b[i] <= b[i - 1] && b[i - 1] <= tmp)
				b[i] = b[i - 1];
			else if(tmp < b[i - 1])
				return 0;
		} //未受到影响的区间，只有在 b[i]<b[i-1] 且无法比 b[i-1] 大时才会失败 
	}
	return 1;
}
int main() {
	scanf("%d%d", &n, &m);
	int i;
	for(i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	int l = 0, r = m, mid, ans; // 二分区间为 [0,m) 
	while(l < r) { // 二分求下界板子写法 
		mid = (l + r) >> 1;
		if(check(mid)) ans = r = mid;
		else l = mid + 1; 
	}
	printf("%d", ans);
	return 0;
}
```

------------

### After Solution：

~~考场上 10min 切掉，真的是蓝题吗，感觉还是绿题比较合适。~~

------------

# $\sf{The\,\,End.}$

---

## 作者：TheShadow (赞：1)

# 题面

[CF1168A Increasing by Modulo](https://www.luogu.org/problem/CF1168A)

# Solution

因为要求最小操作次数，我们考虑二分答案。

因为每次都是任选 $k$ 个数，所以我们可以看做是每个数都能操作最多 $k$ 次。

定义 $pre$ 为当前元素的前一个元素

要判定 $mid$ 是否有解，我们有如下策略：

1. 如果能够在加爆之后变为 $pre$ ，那么就让它变成 $pre$ 。
2. 如果不行，且当前元素不小于 $pre$ ，就将 $pre$ 更新为 $val_i$ 。
3. 如果无论怎么都不能使其不小于 $pre$ ，返回 $false$ 。

# Code

```c++
#include<bits/stdc++.h>
#define del(a,i) memset(a,i,sizeof(a))
#define ll long long
#define inl inline
#define il inl void
#define it inl int
#define ill inl ll
#define re register
#define ri re int
#define rl re ll
#define mid ((l+r)>>1)
#define lowbit(x) (x&(-x))
#define INF 0x3f3f3f3f
using namespace std;
template<class T>il read(T &x){
	int f=1;char k=getchar();x=0;
	for(;k>'9'||k<'0';k=getchar()) if(k=='-') f=-1;
	for(;k>='0'&&k<='9';k=getchar()) x=(x<<3)+(x<<1)+k-'0';
	x*=f;
}
template<class T>il _print(T x){
	if(x/10) _print(x/10);
	putchar(x%10+'0');
}
template<class T>il print(T x){
	if(x<0) putchar('-'),x=-x;
	_print(x);
}
ll mul(ll a,ll b,ll mod){long double c=1.;return (a*b-(ll)(c*a*b/mod)*mod)%mod;}
it qpow(int x,int m,int mod){
	int res=1,bas=x%mod;
	while(m){
		if(m&1) res=(1ll*res*bas)%mod;
		bas=(1ll*bas*bas)%mod,m>>=1;
	}
	return res%mod;
}
const int MAXN = 3e5+5;
int n,m,val[MAXN];
it add(int x,int y){return x+y>=m?x+y-m:x+y;}
it check(int lim){
	ri pre=0;
	for(ri i=1;i<=n;++i){
		if(val[i]+lim>=m&&add(val[i],lim)>=pre) continue;
		if(val[i]>=pre){pre=val[i];continue;}
		if(val[i]+lim<pre) return 0;
	}
	return 1;
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(m);
	for(ri i=1;i<=n;++i) read(val[i]);
	ri l=0,r=m;
	while(l<r){
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	print(l);
	return 0;
}
```

# 总结

一般遇到最大值，最小值，最大值最小，最小值最大这一类的问题，我们都可以尝试使用二分法来降低实现的难度。

---

## 作者：dyx131313 (赞：1)

这场cf真的是一言难尽，A题写错下标，B题垃圾题，C题看错题（突然间发现这也是div1的A题）。

不说了，这题我们通过观察发现是对所有数操作次数的最大值。那么也就是可以在次数内最优操作，即是贪心。那么我们如何来确定这个最小次数呢？显然对所有数的最大操作次数不用超过m，因为a[i]<m，最小次数为0。那么这题的做法就呼之欲出了——二分+贪心。


------------

code:
```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<vector>
#include<iostream>
#include<deque>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;

const int n_size=3e5+5;
int n,m,t[n_size],s[n_size];

bool check(int k){
    for(int i=1;i<=n;i++){
        t[i]=s[i];
        if(t[i]>=t[i-1]){
        //如果数本身满足条件
            if(t[i]+k>=m){
                if((t[i]+k)%m>=t[i-1]) t[i]=t[i-1];
                else t[i]=t[i];//需不需要取模，如需要看能不能取到更好的结果，不然不如不加
            }else{
                t[i]=t[i];//加了等于白加，不如不加
            } 
        }else{
            if(t[i]+k>=t[i-1]) t[i]=t[i-1];//能不能凑成合法的
            else return 0; //不合法
        }
    }
    return 1;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&s[i]);
    }
    int l=0,r=m;//边界，最小次数为0，最大次数为取模数
    while(l<r){//左开右闭
        int mid=(l+r)>>1;
        if(check(mid)){
            r=mid;
        }else{
            l=mid+1;
        }
    }
    printf("%d",l);
    return 0;
}
```

蒟蒻题解，大佬不喜勿喷（两题排1200+，溜了溜了）。

---

## 作者：ZLCT (赞：0)

# CF1168A Increasing by Modulo
## 题意
给定一个长度为 $n$ 的序列 $a$ 以及一个正整数 $m$，每次操作可以选若干个数使之在 $\pmod{m}$ 意义下 $+1$。问至少多少次操作可以使序列不下降。
### 一个暴力的答案
我们要使序列不下降，一个直接的思路就是全都变成 $0$，由于每次操作选取的数量是任意的，于是我们最多执行 $\max\limits_{i=1}^{n}\{m-a_i\}$ 次。
### 思路优化
我们根据上面的思路，进一步想到一个元素只要不是操作次数最多的，那么不论操作多少次都不会对结果产生任何影响。所以我们假设最多操作 $p$ 次。\
对于一个 $a_i$，它只有在 $[a_{i-1},m-1]$ 这段区间内才合法，而我们贪心地想一想假设我们这段区间都可以取到，我们一定会取 $a_{i-1}$，因为这样不会对 $a_{i+1}$ 产生额外限制。\
那假如取不到 $a_{i-1}$ 怎么办呢？我们分两种情况。
1. $a_i<a_{i-1}$：这就说明无论如何操作都无法在 $p$ 次操作内合法，这就说明 $p$ 肯定小于最少操作次数。
2. $a_i>a_{i-1}$：这种情况就是我希望绕一圈使 $a_i$ 变成 $a_{i-1}$，但是步数不够，这时候我们保持不动就是最好的，因为我们能取到的合法区间是 $[a_i,m-1]$，取的越小对后面的限制就越少。

下面还剩一个问题：我们怎么知道最多操作次数呢？如果要枚举次数那复杂度就是 $O(nm)$，肯定会爆炸。\
其实在刚才思路过程中已经有所启示，我们对于一个 $p$，如果不合法那答案一定比它大，如果它合法那答案一定比它小。这不就是二分的性质吗？\
还可以换一种理解方法，假设 $k$ 次就可以使序列不下降，那么 $k+1$ 次只需要什么也不干也一定可以使序列合法，所以设 $f(x)$ 表示 $x$ 次操作能 $(1)$ 否 $(0)$ 使序列不下降，那么 $f(x)$ 一定是一个单调不下降函数，从这个角度也是满足二分条件的。\
于是我们就可以二分最少操作次数，通过贪心的思想 $O(n)$ 遍历序列并判断是否合法，总复杂度 $O(n\log n)$。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[300003];
bool check(int x){
    int pre=0;
    for(int i=1;i<=n;++i){
        if(a[i]==pre)continue;
        if(a[i]>pre){
            if(m-a[i]+pre<=x)continue;
            pre=a[i];
        }else{
            if(pre-a[i]>x)return 0;
        }
    }
    return 1;
}
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    int l=0,r=m;
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid)){
            r=mid;
        }else{
            l=mid+1;
        }
    }
    cout<<l<<'\n';
    return 0;
}
```

---

## 作者：stansxt (赞：0)

# 思路
- 这题……感觉挺简单的啊
- 首先能想到二分$m$，判断当前的$mid$是否满足。
- 怎么判断呢？首先观察题目可以发现，由于每次是 __任选k并任选这k个数__ ，于是我们发现对于每个数，它都可以增加$0$至$mid$中任意整数。
- 那么就很显然了，直接贪心即可。我们每次遍历整个数组，用变量$now$来存储当前序列的末尾。要使$a[i]$也不小于$now$，那么我们可以分情况讨论一下：
- 如果$a[i]>now$，那么我们考虑它加上$mid$之后能否取到$now$或更大。如果能，那么我们把它加上$m+now-a[i]$再取模，我们就可以控制$now$不变，这显然是最优的。如果不能，那么由于数列要求不降，我们把它加上多少都不会比不加更优，因此不需要加任何数，直接把$now$更新为$a[i]$即可。
- 如果$a[i]=now$那么显然我们什么都不用做。
- 如果$a[i]<now$，这时候判断$a[i]+mid$是否能够不小于$now$。如果能，那么就加到$now$，如果不能，那么与题目条件矛盾了，直接 __return__ __false__ 即可。
- 最终全部序列都遍历完了仍没有 __return__ __false__，就直接 __return__ __true__ 。
- 注意一下其实我们不关注数组本身，只关注当前的$now$。因此我们不需要开两个数组，一个就够了。
# 代码
```
//CF1168A Increasing by Modulo
//submit 1
//By sxt on 2020.10.5
#include<bits/stdc++.h>
#define rg register int
#define il inline
#define in read()
#define _num(x) (x >= '0' && x <= '9')
#define Mem(x) memset(x, 0, sizeof(x)) 
#define mid (l+r>>1)
#define el else if
#define lowbit(x) (x&(-x))
using namespace std;
const int N = 3e5+3;
il int read(){
	int x=0,f=1;
	char ch=getchar();
	while(!_num(ch)){
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(_num(ch)){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
char f[18];
int pcnt;
il void pint(int x){
	pcnt = 0;
	if(x == 0) putchar('0');
	if(x < 0){
		x = -x;
		putchar('-');
	}
	while(x){
		f[++pcnt] = x % 10 + '0';
		x /= 10;
	}
	while(pcnt) putchar(f[pcnt--]);
}
int n, m, a[N], now, l, r, ans;
il void ckmax(int &x, int y){return (void)(x = x < y ? y : x);}
il bool pd(int xx){
	now = 0;
	for(rg i = 1; i <= n; ++ i)
		if(a[i] > now){if(a[i] + xx - m < now) now = a[i];}
		el(a[i] < now)if(a[i] + xx < now) return false;
	return true;
}
il int check(){
	l = 0, r = m;
	while(l <= r){
		if(pd(mid)) r = mid - 1;
		else l = mid + 1;
	}
	return ++ r;
}
signed main()
{
//	freopen("1.txt", "r", stdin);
	n = in, m = in;
	for(rg i = 1; i <= n; ++ i) a[i] = in;
	pint(check());
	return 0;
}
```

---

