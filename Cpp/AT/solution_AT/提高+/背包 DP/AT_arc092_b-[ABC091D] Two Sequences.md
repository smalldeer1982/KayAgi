# [ABC091D] Two Sequences

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc091/tasks/arc092_b

$ 2 $ つの長さ $ N $ の非負整数列 $ a_1,\ ...,\ a_N,\ b_1,\ ...,\ b_N $ が与えられます。

$ 1\ \leq\ i,\ j\ \leq\ N $ となるように整数 $ i,\ j $ を選ぶ方法は $ N^2 $ 通りありますが，この $ N^2 $ 通りの $ i,\ j $ それぞれについて，$ a_i\ +\ b_j $ を計算し，紙に書き出します。 つまり，紙に $ N^2 $ 個の整数を書きます。

この $ N^2 $ 個の整数のxorを計算してください。

xorの説明

整数 $ c_1,\ c_2,\ ...,\ c_m $ のxor $ X $ は，以下のように定義されます。

- $ X $ を $ 2 $ 進数表記したときの $ 2^k $($ 0\ \leq\ k $, $ k $ は整数)の位の値は，$ c_1,\ c_2,\ ...c_m $ のうち，$ 2 $ 進数表記したときの $ 2^k $ の位の値が $ 1 $ となるものの個数が奇数個ならば $ 1 $，偶数個ならば $ 0 $ となります

例えば，$ 3 $ と $ 5 $ のxorの値は，$ 3 $ の $ 2 $ 進数表記が $ 011 $，$ 5 $ の $ 2 $ 進数表記が $ 101 $ のため，$ 2 $ 進数表記が $ 110 $ の $ 6 $ となります。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ N\ \leq\ 200,000 $
- $ 0\ \leq\ a_i,\ b_i\ <\ 2^{28} $

### Sample Explanation 1

紙には $ 4(1+3),\ 5(1+4),\ 5(2+3),\ 6(2+4) $ の $ 2^2\ =\ 4 $ つの数が書かれます。

## 样例 #1

### 输入

```
2
1 2
3 4```

### 输出

```
2```

## 样例 #2

### 输入

```
6
4 6 0 0 3 3
0 5 6 5 0 3```

### 输出

```
8```

## 样例 #3

### 输入

```
5
1 2 3 4 5
1 2 3 4 5```

### 输出

```
2```

## 样例 #4

### 输入

```
1
0
0```

### 输出

```
0```

# 题解

## 作者：xlsfyc (赞：5)

[AT3943 [ARC092B] Two Sequences](https://www.luogu.com.cn/problem/AT3943)

提供一个这题与大多人不一样的题解。

**题解**

首先引入一个很显然的东西：

对于一个正整数 $x$，若 $x \mod 2^k \geq 2^{k-1}$，则它二进制的第 $k$ 位是 $0$，否则是 $1$。（这个自证不难，因为取后面的 $k$ 位，转换为十进制要比 $k-1$ 位大才能为 $1$。）

于是就可以依题意按位分拆啦。

在最外层枚举 $k$，然后用两个备用数组存原数组对 $2^k$ 取模的值，命名为 $a$ 和 $b$。然后求有多少组 $(i,j)$ 使得 $a_i+b_j \mod 2^k \geq2^{k-1}$ 。若有奇数组，则答案的二进制的这一位是 $1$，否则是 $0$。

理由也很简单，通过上面的引理，然后又对这一位上进行异或操作，偶数次 $1$ 就没了，否则就剩个 $1$。

问题来了，如何求有多少组 $(i,j)$ 使得 $a_i+b_j \mod 2^k \geq2^{k-1}$？

首先题目中的异或操作满足交换律。所以可以考虑将 $a,b$ 排序，甚至可以去个重。

排序后就可以想到二分了，设 $a_i$ 为主元，枚举之，每个分为以下两种情况：

- 若 $a_i \lt 2^{k-1}$，则发现 $b_j$ 需满足 $2^{k-1}-a_i \leq b_j \leq2^k-a_i-1$；

- 若 $a_i \geq 2^{k-1}$，则发现 $b_j$ 需满足 $b_j \leq 2^{k}-a_i-1$ 且 $b_j \geq 2^k+2^{k-1}-a_i$。为了方便后面的处理，可以转换成是 $b_j$ 需不满足 $2^{k}-a_i \leq b_j \leq 2^k+2^{k-1}-a_i-1$。

以上结论需要推理，在此省略，赛时手推了挺久的。

接下来就可以愉快地二分左右端点啦。设两端点为 $l$ 和 $r$，第一种情况的个数即为 $r-l+1$，而第二种的个数是 $n-(r-l+1)$。

在这里需注意以下，有可能出现无满足条件的 $b_j$。考虑初始化 $l$ 和 $r$ 为 $\tt INF$。若二分结束后两值中有任意一个仍等于 $\tt INF$，意为二分不到结果。

当这种情况发生时：

- 对于情况一，总数不变。

- 对于情况二，总数直接加 $n$。（因无不满足条件的值）

至此，本题被完美解决。

**代码**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int INF=0x3f3f3f3f;
int n,a1[200001]={0},b1[200001]={0},a[200001]={0},b[200001]={0},p=1,ans=0;
signed main(){
//  freopen("sample5.in","r",stdin);
//  freopen("sc.in","r",stdin);
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a1[i]);
    for(int i=1;i<=n;i++) scanf("%lld",&b1[i]);
    for(int k=1;k<=29;k++){
        p<<=1;
        for(int i=1;i<=n;i++) a[i]=a1[i]%p,b[i]=b1[i]%p;
        sort(a+1,a+n+1),sort(b+1,b+n+1);
        int cnt=0;
        for(int i=1;i<=n;i++){
            int ansl=INF,ansr=INF;
            if(a[i]<p/2){
                int x=p/2-a[i],y=p-a[i]-1,l=1,r=n;
                while(l<=r){
                    int mid=(l+r)>>1;
                    if(b[mid]>=x) ansl=mid,r=mid-1;
                    else l=mid+1;
                }
                l=1,r=n;
                while(l<=r){
                    int mid=(l+r)>>1;
                    if(b[mid]<=y) ansr=mid,l=mid+1;
                    else r=mid-1;
                }
                if(ansl!=INF && ansr!=INF) cnt+=ansr-ansl+1;
            }else{
                int x=p-a[i],y=p+p/2-a[i]-1,l=1,r=n;
                while(l<=r){
                    int mid=(l+r)>>1;
                    if(b[mid]>=x) ansl=mid,r=mid-1;
                    else l=mid+1;
                }
                l=1,r=n;
                while(l<=r){
                    int mid=(l+r)>>1;
                    if(b[mid]<=y) ansr=mid,l=mid+1;
                    else r=mid-1;
                }
                if(ansl==INF || ansr==INF) cnt+=n; 
                else cnt+=(n-(ansr-ansl+1));
            }
        }
        ans+=(cnt%2==1)*(p/2);
    }
    printf("%lld",ans);
    return 0;
}
```

**时间复杂度**

里面枚举和二分 $\mathcal O(n \log n)$，外面再套个分拆，所以 $\mathcal O(n \log^2 n)$。


---

## 作者：Krimson (赞：2)

非常显然的一点,应该把每一位都单独计算。可以发现高位的值不会影响低位的值,不妨从高位向低位做  
假设现在做到了第$i$位  
对于$a_j$,设其在$mod\ 2^i$意义下为$x$  
如果$a_j$的第$i$位为$1$,那么可以对其产生贡献的$b$有两类:  

1. 其第$i$位为$0$,且$y$(即$b\ mod\ 2^i)$满足$x+y<2^i$  
2. 其第$i$位为$1$,且$y$满足$x+y \geq2^i$  

可以将$b_j$的第$i$位是否为$1$分别加入到$vec_{b,0}$和$vec_{b,1}$当中,等价于去求$vec_{b,0}$中小于$2^i-x$的元素个数和$vec_{b,0}$中大于等于$2^i-x$的元素个数  
对于$a_j$的第$i$位为$0$的时候也可以同上面这种形式分类讨论  
实际上可以发现两边的指针都是单调的,可以使用一个双指针,不过复杂度瓶颈不在这边,对于理论复杂度并没有优化,直接用lower_bound就行了  
时间复杂度$O(nlognlogv)$  


 _**Code**_  
------------
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
#define ui unsigned int
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il int read(char *s){
    int len=0;
    register char ch=getchar();
    while(ch==' '||ch=='\n') ch=getchar();
    while(ch!=' '&&ch!='\n'&&ch!=EOF) s[++len]=ch,ch=getchar();
    return len;
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il ll max(const ll &a,const ll &b){return a>b?a:b;}
il ll min(const ll &a,const ll &b){return a<b?a:b;}
int n;
const int MAXN=2e5+7;
ll a[MAXN],b[MAXN],x[MAXN],y[MAXN],bit[64],base[64],ans;
vector<ll> veca[2],vecb[2];
il ll low(vector<ll> &vec,ll v){
    return lower_bound(vec.begin(),vec.end(),v)-vec.begin();
}
il ll lar(vector<ll> &vec,ll v){
    return vec.end()-upper_bound(vec.begin(),vec.end(),v);
}
int main(){
    n=read();
    for(ri i=1;i<=n;++i) a[i]=read();    
    for(ri i=1;i<=n;++i) b[i]=read();    
    base[0]=1;
    for(ri i=1;i<30;++i) base[i]=base[i-1]<<1;
    for(ri i=28;~i;--i){
        veca[0].clear(),veca[1].clear();
        vecb[0].clear(),vecb[1].clear();
        for(ri j=1;j<=n;++j){
            veca[(bool)(a[j]&base[i])].push_back(a[j]&(base[i]-1));
            vecb[(bool)(b[j]&base[i])].push_back(b[j]&(base[i]-1));
        }
        sort(veca[0].begin(),veca[0].end()),sort(veca[1].begin(),veca[1].end());
        sort(vecb[0].begin(),vecb[0].end()),sort(vecb[1].begin(),vecb[1].end());
        for(ri j=0;j<veca[0].size();++j){
            ll res=0;
            res+=lar(vecb[0],base[i]-veca[0][j]-1);
            res+=low(vecb[1],base[i]-veca[0][j]);
            bit[i]^=res&1;
        }
        for(ri j=0;j<veca[1].size();++j){
            ll res=0;
            res+=lar(vecb[1],base[i]-veca[1][j]-1);
            res+=low(vecb[0],base[i]-veca[1][j]);
            bit[i]^=res&1;
        }
        ans+=bit[i]*base[i];
    }
    print(ans);
    return 0;
}
```


---

## 作者：Sharing666 (赞：1)

一位位拆开来算。对于每一位 $i$，把数组 $a$ 和 $b$ 中高于 $i$ 位的位去掉。

容易发现，当且仅当 $2^i\leq a_j+b_k<2^{i+1}$ 或 $2^i+2^{i+1}\leq a_j+b_k$ 时，$a_j+b_k$ 的第 $i$ 位为 $1$。

用双指针分别计算 $a_j+b_k<2^i$、$a_j+b_k<2^{i+1}$、$a_j+b_k<2^{i+2}$ 的个数，容斥一下即可。

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#define Hibiki namespace
#define Wataru std
using Hibiki Wataru;

int n,a[200002],b[200002];

bool cmp(int x,int y) {
	return x>y;
}

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	int ans=0;
	for(int i=28;i>=0;i--) {
		for(int j=1;j<=n;j++) a[j]%=(1<<i+1),b[j]%=(1<<i+1);
		sort(a+1,a+n+1,cmp);
		sort(b+1,b+n+1);
		int cnt1=1,cnt2=1,cnt3=1,sum=0;
		for(int j=1;j<=n;j++) {
			while(cnt1<=n && a[j]+b[cnt1]<(1<<i)) cnt1++;
			while(cnt2<=n && a[j]+b[cnt2]<(2<<i)) cnt2++;
			while(cnt3<=n && a[j]+b[cnt3]<(3<<i)) cnt3++;
			sum+=cnt2-cnt1+n-cnt3+1;
		}
		if(sum%2) ans+=(1<<i);
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：zhaoyp (赞：1)

# Description

> 给定长度为 $n$ 的两串序列 $a,b$。求 $a,b$ 两序列各任取一数相加形成的 $n^2$ 个和的 $\operatorname{xor}$ 和。

# Solution
考虑第 $k$ 位的贡献，为了防止更高数位的影响，先将 $2n$ 个数对 $2^{k+1}$ 取模，接下来讨论都在模意义下进行。

若 $a_i + b_j$ 的第 $k$ 位为 $1$，则有 $a_i + b_j \in [2^k,2\times 2^k-1] \cup [3\times 2^k,4\times 2^k - 1]$。

枚举 $a_i$，为题就转成了求满足条件的 $b_j  \in [2^k-a_i,2\times 2^k-1-a_i] \cup [3\times 2^k-a_i,4\times 2^k - 1-a_i]$ 的个数。

把 $b$ 排序后二分查找即可。

时间复杂度 $O(n \log n \log A)$。

# code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
int n,a[maxn],b[maxn],c[maxn],d[maxn],ans;
int main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n;i++)
		scanf("%d",&a[i]);
	for(int i = 1;i <= n;i++)
		scanf("%d",&b[i]);
	for(int k = 0;k <= 28;k++)
	{
		long long cnt = 0;
		for(int i = 1;i <= n;i++)
			c[i] = (a[i] & ((1 << (k + 1)) - 1)),d[i] = (b[i] & ((1 << (k + 1)) - 1));
		sort(c + 1,c + 1 + n);
		sort(d + 1,d + 1 + n);
		for(int i = 1;i <= n;i++)
		{
			int l = (1 << k) - c[i],r = 2 * (1 << k) - 1 - c[i];
			cnt += upper_bound(d + 1,d + 1 + n,r) - lower_bound(d + 1,d + 1 + n,l);
			l += (1 << (k + 1)),r += (1 << (k + 1));
			cnt += upper_bound(d + 1,d + 1 + n,r) - lower_bound(d + 1,d + 1 + n,l);
		}
		if(cnt & 1)
			ans |= (1 << k);
	}
	cout << ans;
	return 0 ;
}
```

---

## 作者：orz_z (赞：1)

### [ARC092B] Two Sequences

细节超多，开始找不到任何数据结构维护。

考虑比较暴力的做法。

对答案每一位分别考虑，设当前考虑到第 $i$ 位。

计算所有数模 $2^{i + 1}$ 的余数，并升序排序使其满足单调性。(以下都按余数讨论)

若对于一个数 $a$，有数 $b$ 满足 $(a+b)\bmod 2^{i+1}\geq 2^i$，则 $a,b$ 原数之和第 $i$ 位为 $1$。

那么对于每个 $a_i$ 分类讨论：

* 若 $a_i \le 2^{i-1}$，则答案在 $[2^i-a,2^{i+1}-a-1]$ 范围内，二分统计个数即可。
* 否则即 $a_i>2^{i-1}$，则答案在 $[0,2^{i+1}-a-1] \cup [2^{i+1}+2^i-a,2^{i+1}-1]$ 范围内，二分统计个数即可（两区间不交）。

对于每一位的总个数判断奇偶性添加贡献即可。

时间复杂度 $\mathcal O(n\log n\log V)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long
typedef long long ll;

#define ha putchar(' ')
#define he putchar('\n')

inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * f;
}

inline void write(int x)
{
	if(x < 0)
	{
		putchar('-');
		x = -x;
	}
	if(x > 9)
		write(x / 10);
	putchar(x % 10 + 48);
}

const int _ = 2e5 + 10;

int n, a[_], b[_], c[_], d[_], ans;

signed main()
{
	//	a[1] = 1, a[2] = 2;
	//	cout << upper_bound(a + 1, a + 2 + 1, 3) - a;
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= n; ++i) b[i] = read();
	for(int x = 30; x >= 0; --x)
	{
		int nw = 1 << x, t = 0;
		for(int i = 1; i <= n; ++i) c[i] = a[i] % (nw << 1);
		for(int i = 1; i <= n; ++i) d[i] = b[i] % (nw << 1);
		sort(c + 1, c + n + 1), sort(d + 1, d + n + 1);
		for(int i = 1; i <= n; ++i)
		{
			if(c[i] <= nw)
			{
				// [2^i-a,2^{i+1}-a-1]
				int ps1 = upper_bound(d + 1, d + n + 1, (nw << 1) - c[i] - 1) - d - 1;
				int ps2 = lower_bound(d + 1, d + n + 1, nw - c[i]) - d - 1;
				t += ps1 - ps2;
			}
			else
			{
				// [2^{i+1}+2^i-a,2^{i+1}-1]
				// [0,2^{i+1}-a-1]
				int ps1 = upper_bound(d + 1, d + n + 1, (nw << 1) - 1) - d - 1;
				int ps2 = lower_bound(d + 1, d + n + 1, (nw << 1) + nw - c[i]) - d - 1;
				t += ps1 - ps2;
				ps1 = upper_bound(d + 1, d + n + 1, (nw << 1) - c[i] - 1) - d - 1;
				ps2 = lower_bound(d + 1, d + n + 1, 0) - d - 1;
				t += ps1 - ps2;
			}
		}
		//		cout << nw << ": " << t <<"\n";
		if(t & 1) ans |= nw;
	}
	write(ans), he;
	return 0;
}

/*

*/
```





---

## 作者：UncleSam_Died (赞：1)

提供一种非正解做法，看正解的可以跳过了。

我们发现数据范围其实并不大，考虑直接暴力计算。但是显然这样会 TLE，这个时候加上火车头和快读，就可以大力跑过去了。如果仍然 TLE，把语言换成 C++20 就可以了。

代码很短，大部分的是读入优化，而且跑得飞快。

AC 代码：

```cpp
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<math.h>
#include<cstdio>
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<valarray>
#include<algorithm>
#define N 200005
template<typename type>
inline void read(type &x){
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag^=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    flag?x=-x:0;
}
template<typename type>
inline void write(type x,bool flag=1){
    x<0?x=-x,putchar('-'):0;static short Stack[50],top(0);
    do Stack[++top]=x%10,x/=10;while(x);
    while(top) putchar(Stack[top--]|48);
    flag?putchar('\n'):putchar(' ');
}
int n,a[N],b[N],ans;
signed main(){ read(n);
    for(int i=1;i<=n;++i)
        read(a[i]);
    for(int i=1;i<=n;++i)
        read(b[i]);
    for(int i=1;i<=n;++i)
    for(int j=1;j<=n;++j)
        ans^=(a[i]+b[j]);
    write(ans);
}
```

---

## 作者：rizynvu (赞：0)

[我的博客](https://www.cnblogs.com/rizynvu/p/18281712)。

首先根据 $\operatorname{xor}$，就想到拆成二进制的 $a_{i, w}, b_{i, w}$ 来处理。

类似竖式加法，考虑把得到的结果 $c_{w}$ 分为 $a_{i, w} + b_{j, w} + x$，其中 $x$ 就是上一位的进位。  
进一步的，发现对于总的 $c_{w}$，$a_{i, w}, b_{j, w}$ 肯定都在这个位置加了 $n$ 次，相当于是固定的。  
于是就只需要考虑上一位往这一位进位多少次即可。

然后考虑如果 $w$ 位向 $w + 1$ 位进位有什么条件。  
手玩一下能整理出来以下条件：  
1. 存在 $p(p\le w)$，$a_{i, p} = b_{j, p} = 1$，相当于首先要有进位。
2. $\forall x\in (p, w]$，$a_{i, x} + b_{j, x} = 1$，相当于这个进位在向前传递。

对于条件 2，因为 $a_{i, x} + b_{j, x} = 1$，就相当于是 $a_{i, x} \operatorname{xor} b_{j, x} = 1$，那么就说明 $(p, w]$ 这些位 $a_i, b_j$ 异或起来得到的就是 $\operatorname{lim} = \sum\limits_{i = p + 1}^w 2^i$。  
那么就可以反过来用 $\operatorname{lim}\operatorname{xor} a_i$ 去计数 $b_j$ 了。

时间复杂度 $\mathcal{O}(n\log^2 V)$，$V$ 为值域。

计数的时候需要用个 *Hash*，常数有点大，需要卡卡常。

```cpp
#include<bits/extc++.h>
const int maxn = 2e5 + 10, logV = 28;
int a[maxn][logV], b[maxn][logV];
int av[maxn], bv[maxn];
int c[logV + 1];
int main() {
   int n; scanf("%d", &n);
   for (int i = 1, x; i <= n; i++) {
      scanf("%d", &x);
      for (int w = 0; w < logV; w++) a[i][w] = x & (1 << w);
   }
   for (int i = 1, x; i <= n; i++) {
      scanf("%d", &x);
      for (int w = 0; w < logV; w++) b[i][w] = x & (1 << w);
   }
   for (int i = 1; i <= n; i++)
      for (int w = 0; w < logV; w++) c[w] ^= (a[i][w] && (n & 1)) << w;
   for (int i = 1; i <= n; i++)
      for (int w = 0; w < logV; w++) c[w] ^= (b[i][w] && (n & 1)) << w;
   std::unordered_map<int, int> mp;
   for (int j = 0; j < logV; j++) {
      memset(av, 0, sizeof(av)), memset(bv, 0, sizeof(bv));
      std::vector<int> A, B;
      for (int i = 1; i <= n; i++)
         if (a[i][j]) A.push_back(i);
      for (int i = 1; i <= n; i++)
         if (b[i][j]) B.push_back(i);
      c[j + 1] ^= ((A.size() & 1) && (B.size() & 1)) << j + 1;
      int lim = 0;
      for (int k = j + 1; k < logV; k++) {
         lim |= 1 << k;
         mp.clear();
         for (int i : A) mp[lim ^ (av[i] |= a[i][k])] ^= 1;
         int tot = 0;
         for (int i : B) tot ^= mp[bv[i] |= b[i][k]];
         c[k + 1] ^= tot << k + 1;
      }
   }
   int ans = 0;
   for (int i = 0; i <= logV; i++) ans += c[i];
   printf("%d\n", ans);
   return 0;
}
```

---

## 作者：ttq012 (赞：0)

看到 $\tt{xor}$，显然考虑拆位。

考虑将所有数中 $>i$ 位的数全部删去。此时若对于 $j$，$k$ 满足 $2^i\le a_j+b_k<2^{i+1}$ 或者 $2^{i+1}+2^i\le a_j+b_k<2^{i+2}$，则 $j$，$k$ 对答案的第 $i$ 位贡献了 $2^i$。

考虑枚举 $j$，计算出所有在范围内的 $k$。使用一个双指针滑动即可。时间复杂度为 $O(n\log W)$，其中 $W$ 是数位数量。

---

## 作者：qfpjm (赞：0)

- 建议评紫。

# 题解

- 由于是 `xor` 运算，所以我们用二进制逐位考虑。当 $A_i+B_j$ 的第 $k$ 位为 $1$ 时，那么这个 $1$ 只可能时**进位**或**两个位置都是 $1$ 但进位后还是 $1$** 所得来的。

- 我们可以通过一些小小的计算可以得出，$A_i+B_i$ 满足不等式：$2^k\leq A_i+B_j<2^{k+1}$ 或 $3 \times 2^k\leq A_i+B_j<4 \times 2^k$。

- 实现的话，我们可以先对 $A_i,B_i$ 取模 $2^{k+1}$，已消除其它位对其的影响。然后枚举 $A_i$，求 $B_j$ 的范围。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, a[200005], b[200005], ans;

bool cmp(int x, int y)
{
	return x > y;
}

int main()
{
	cin >> n;
	for (int i = 1 ; i <= n ; i ++)
	{
		cin >> a[i];
	}
	for (int i = 1 ; i <= n ; i ++)
	{
		cin >> b[i];
	}
	for (int w = 28 ; w >= 0 ; w --)
	{
		for (int i = 1 ; i <= n ; i ++)
		{
			a[i] %= (1 << (w + 1));
			b[i] %= (1 << (w + 1));
		}
		sort(a + 1, a + 1 + n, cmp);
		sort(b + 1, b + 1 + n);
		int r1, r2, r3, cnt = 0;
		r1 = r2 = r3 = 1;
		for (int i = 1 ; i <= n ; i ++)
		{
			while (r1 <= n && a[i] + b[r1] < (1 << w))
			{
				r1 ++;
			}
			while (r2 <= n && a[i] + b[r2] < (2 << w))
			{
				r2 ++;
			}
			while (r3 <= n && a[i] + b[r3] < (3 << w))
			{
				r3 ++;
			}
			cnt += r2 - r1 + n - r3 + 1;
		}
		ans += (cnt % 2) ? (1 << w) : 0;
	}
	cout << ans;
}
```


---

## 作者：Zhl2010 (赞：0)

## 题目描述
有 $n$ 个 $k$ 种颜色的点，选出一个长度尽量短的区间，使得每种颜色的点都在区间内出现。
## 思路
不是正解，但是能过。

先用这个优化：
```cpp
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
```

然后可以用快读，增加输入速度。

最后打一个暴力（不优化是  `O(100000000)`，肯定 `TLE`），就是双重 `for` 循环，枚举每一个数，用 `^` 运算算出答案，跟双指针差不多，只不过很简单。

如果过不了，用 `c++20`。

## 代码
```cpp
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200010],b[200010],ans=0;
long long kd(){
	long long a=0;
	char c;
	c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c)){
		a=(10*a+c-'0');
		c=getchar();
	}
	return a;
}
signed main(){//^
	cin>>n;
	for(int z=1;z<=n;z++){
		a[z]=kd();
	}
	for(int z=1;z<=n;z++){
		b[z]=kd();
	}
	for(int z=1;z<=n;z++){
		for(int x=1;x<=n;x++){
			ans^=(a[z]+b[x]);
		}
	}
	cout<<ans;
	return 0;
}
```

---

