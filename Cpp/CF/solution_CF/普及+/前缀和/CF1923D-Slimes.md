# Slimes

## 题目描述

There are $ n $ slimes placed in a line. The slimes are numbered from $ 1 $ to $ n $ in order from left to right. The size of the $ i $ -th slime is $ a_i $ .

Every second, the following happens: exactly one slime eats one of its neighbors and increases its size by the eaten neighbor's size. A slime can eat its neighbor only if it is strictly bigger than this neighbor. If there is no slime which is strictly bigger than one of its neighbors, the process ends.

For example, suppose $ n = 5 $ , $ a = [2, 2, 3, 1, 4] $ . The process can go as follows:

- first, the $ 3 $ -rd slime eats the $ 2 $ -nd slime. The size of the $ 3 $ -rd slime becomes $ 5 $ , the $ 2 $ -nd slime is eaten.
- then, the $ 3 $ -rd slime eats the $ 1 $ -st slime (they are neighbors since the $ 2 $ -nd slime is already eaten). The size of the $ 3 $ -rd slime becomes $ 7 $ , the $ 1 $ -st slime is eaten.
- then, the $ 5 $ -th slime eats the $ 4 $ -th slime. The size of the $ 5 $ -th slime becomes $ 5 $ , the $ 4 $ -th slime is eaten.
- then, the $ 3 $ -rd slime eats the $ 5 $ -th slime (they are neighbors since the $ 4 $ -th slime is already eaten). The size of the $ 3 $ -rd slime becomes $ 12 $ , the $ 5 $ -th slime is eaten.

For each slime, calculate the minimum number of seconds it takes for this slime to be eaten by another slime (among all possible ways the process can go), or report that it is impossible.

## 样例 #1

### 输入

```
4
4
3 2 4 2
3
1 2 3
5
2 2 3 1 1
7
4 2 3 6 1 1 8```

### 输出

```
2 1 2 1 
1 1 -1 
2 1 -1 1 2 
2 1 1 3 1 1 4```

# 题解

## 作者：Luzhuoyuan (赞：14)

Links:[[to Codeforces]](https://codeforces.com/contest/1923/problem/D) [[to Luogu]](https://www.luogu.com.cn/problem/CF1923D)

### 题意简述

有 $n$ 只史莱姆，编号为 $1\sim n$，第 $i$ 只史莱姆的大小为 $a_i$。

每秒钟内下述事件会发生恰好一次：恰好一只史莱姆吃掉它旁边的史莱姆，且其大小会增大，增大值为被吃掉的史莱姆的大小。一只史莱姆能吃掉另一只当且仅当其大小严格大于被吃的史莱姆的大小。若不存在一只史莱姆的大小严格大于另一只，过程结束。

对于每只史莱姆，求出使得它被吃掉需要经过的最短时间。若它不可能被吃掉，输出 `-1`。每个测试点 $t$ 组测试用例。

$$1\le t\le 10^4;1\le n,\sum n\le 3\cdot 10^5;1\le a_i\le 10^9$$

### 思路

首先容易发现，如果一段连续的史莱姆的大小不全相等，那么一定能找到一种方案把这一坨全都合起来。具体方法是每次选“大小最大且相邻的史莱姆中有大小小于它的史莱姆”的史莱姆，然后让它吃掉旁边比它小的，就能合并了。

那么我们考虑预处理大小的前缀和和后缀和，然后每次二分出当前史莱姆往左、右走最短的总大小严格大于当前史莱姆的一段史莱姆，然后长度取个最小值就好了，如果它左边的总和和右边的总和都小于它，那么就是 `-1`。

但是如果一段史莱姆大小都相等，那么它们肯定合不起来，必须得找个不相等的才行。比如 `1 2 2 2 3`，要吃掉最后一个必须把前面四个全合起来。所以我们再预处理 $l_i,r_i$ 表示史莱姆 $i$ 往左、右走多少才能找到大小不等于 $a_i$ 的史莱姆。计算答案时要对 $l_i+1$ 或 $r_i+1$ 取 $\max$。如果左边全相等、右边全相等，那么也是无解的。

记得特判相邻史莱姆直接能吃掉它的情况。时间复杂度 $O(n\log n)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5,INF=1e18;
int T,n,a[N],l[N],r[N],pr[N],su[N];
inline int read(){
	int x=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x;
}
signed main(){
	T=read();
	while(T--){
		n=read();su[n+1]=a[n+1]=0;for(int i=1;i<=n;i++)a[i]=read();
		for(int i=1;i<=n;i++)l[i]=(a[i]==a[i-1]?l[i-1]+1:1),pr[i]=pr[i-1]+a[i];
		for(int i=n;i>=1;i--)r[i]=(a[i]==a[i+1]?r[i+1]+1:1),su[i]=su[i+1]+a[i];
		for(int i=1;i<=n;i++){
			int ans=INF;
			if(a[i-1]>a[i]||a[i+1]>a[i]){printf("1 ");continue;}
			if(pr[i-1]>a[i]&&l[i-1]<i-1)//注意后缀和单调递减的 lower_bound 写法
				ans=max(l[i-1]+1,i-(lower_bound(su+1,su+1+n,su[i]+a[i],greater<int>())-su-1));
			if(su[i+1]>a[i]&&r[i+1]<n-i)
				ans=min(ans,max(r[i+1]+1,(upper_bound(pr+1,pr+1+n,pr[i]+a[i])-pr)-i));
			printf("%lld ",ans==INF?-1ll:ans);
		}
		puts("");
	}
	return 0;
}
```
（逃

---

## 作者：elbissoPtImaerD (赞：4)

考虑枚举 $i$，下面求解 $ans_i$。

首先一个观察是一定存在最优方案使得史莱姆只往一个方向吃。

其次：如果 $(i,r)$ 的史莱姆能合并后吃掉 $i$，则 $(i,r]$ 的亦可以。另一侧同理。

下面只考虑从右往左吃的情况，另一侧同理。

二分，每次判断 $\sum\limits_{j=i+1}^{mid} a_j \le a_i$ 即可。

注意判断相等大小和不够大无法吃掉的情况。

[$\color{green}{\checkmark}$](https://codeforces.com/contest/1923/submission/249013194)

---

## 作者：kczw (赞：2)

# 题意t
共 $t(1\le t\le10^4)$ 组数据。

对于每组数据，给定一个长 $n(1\le n\le3\times10^5,\sum n\le3\times10^5)$ 的序列 $a$，对于序列中相邻且不同的两个数，可以由大数合并小数，合并结果为两者之和。

问对于序列中每个数，最少多少从次合并可以让其**被**合并，若不可**被**合并，输出 `-1`。
# 思路
首先不难明白若序列中一段的数皆相等，则此段不可合并，否则一定可以全部合并为一个数。

然后，我这里简述的题意提到了一个字，**被**，这意味有数与此数相邻且比其大。

综合上述分析，可以初步得出一个思路，我们查找与须被合并数相邻且区间和最小但大于这个数的可以合并的区间，然后根据查找到的区间长度可以得出答案。

但是问题来了，怎么查找呢？这里可以用二分枚举端点，因为这个区间须保证与须被合并数相邻，所以有一个端点已经确定（对于某一方向，共两个方向），所以只用枚举一个端点。

这里需要注意，枚举时需要判断区间是否合法，关于区间和的判断可以用前缀和，但是如果判断这段区间是否全是同一个数呢？

我们先维护一个数组 $c$，令 $c_i=|a_i-a_{i-1}|$，然后再维护其前缀和。然后对于一个区间求 $c$ 的和，如果为 $0$，就说明每每相邻两数差都为 $0$，这意味着什么便不用多说了。

总结一下。解法为，对于每个数，二分查找合法区间，根据区间长度出答案（答案就是区间长度，原因很简单，不过多赘述）。
# 代码
```cpp
#import"bits/stdc++.h"
using namespace std;
const int N=3e5+5;
long long t,n,a[N],pre[N],c[N];
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		for(long long i=1;i<=n;i++){			
			scanf("%lld",&a[i]);
			pre[i]=pre[i-1]+a[i];
			c[i]=c[i-1]+abs(a[i]-a[i-1]);
		}
		for(long long i=1,l,r;i<=n;i++){
			if((a[i-1]>a[i]&&i!=1)||(a[i+1]>a[i]&&i!=n)){
				printf("1 ");
				continue;
			}
			long long ans=0x3f3f3f3f;
			if(i-1&&pre[i-1]>a[i]){
				l=1;r=i-1;
				while(l<=r){
					long long mid=l+r>>1ll;
					if(pre[i-1]-pre[mid-1]<=a[i]||(c[i-1]-c[mid]==0&&i-1!=mid))r=mid-1;
					else{
						ans=min(ans,i-mid);
						l=mid+1;
					}
				}
			}
			if(i-n&&pre[n]-pre[i]>a[i]){
				l=i+1;r=n;
				while(l<=r){
					long long mid=l+r>>1ll;
					if(pre[mid]-pre[i]<=a[i]||(c[mid]-c[i+1]==0&&i+1!=mid))l=mid+1;
					else{
						ans=min(ans,mid-i);
						r=mid-1;
					}
				}
			}
			if(ans==0x3f3f3f3f)printf("-1 ");
			else printf("%lld ",ans);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：2huk (赞：2)

[特判少了](https://www.luogu.com.cn/discuss/782560)，没有场切/kk

拜谢 @[sunkuangzheng](/user/679936)。

## Solution

有 $n$ 只怪兽排成一排，第 $i$ 只怪兽的血量为 $a_i$。

每秒钟都会有一只怪兽吃掉它旁边的且血量比它小的怪兽，小怪兽没了，大怪兽的血量变为两只怪兽的血量之和。

对于每个 $i = (1, 2, 3, \dots, n)$，求第 $i$ 只怪兽最少需要几秒被吃掉。

## Solution

首先我们可以将“怪兽吃怪兽”的过程转化：

- 如果有两个怪兽 $i$ 和 $i + 1$ 满足 $a_i \ne a_{i + 1}$，那么我们可以将这两个怪兽合并成一个血量为 $a_i + a_{i + 1}$ 的怪兽。

这样不难发现，最终合并出来的一个怪兽，在最初的位置上，一定是连续的。

所以我们考虑第 $i$ 个怪兽最少需要几步被合并。假如答案为 $j$，那么一定是由最初的怪兽 $i-j \sim i-1$ 或者 $i + 1 \sim i + j$ 合并而来的。

同时注意到，如果 $j$ 个怪兽能吃掉怪兽 $i$，那么 $j + 1$ 个怪兽也一定能吃掉怪兽 $i$。这意味着答案有单调性，所以我们二分 $j$。

问题来到了判断 $i - j \sim i - 1$（$i+1\sim i+j$ 同理）这些怪兽能否通过合并成一个怪兽之后，把 $i$ 合并起来。

首先，一个最简单的想法就是判断区间内所有 $a$ 的和是否大于 $a_i$。因为将一段区间的怪兽合并成一只怪兽后，它的血量是原来怪兽的和。

但是会有一个问题，就是假如区间内不存在一个位置 $x$ 使得 $a_x \ne a_{x + 1}$，那么这个区间也是不合法的。因为你的第一次合并就无法进行。所以需要判断区间内的数字是否全部相同。

同时，即使区间内的元素全部相同，那么是否这个区间一定不合法呢？

有一种特殊情况，就是当这个相同的值本身就大于 $a_i$，那么第一步我们可以将最边上的怪兽和 $i$ 合并。所以还需要特判这种情况。

## Code

<https://codeforces.com/contest/1923/submission/247984795>

---

## 作者：AKPC (赞：2)

很板的题，Div2 的 D 中比较水的一道。

首先要明白一个结论：因为只能有大的吃小的（相等的不能互吃）所以对于一些史莱姆如果他们全都是一样大的那么无法开展这个吃的过程。

$n^2$ 做法：

对于一个点 $i$，如果 $i$ 的左、右边已经有比他大的史莱姆，答案直接为 $1$（不特判代码容易出锅），否则，我们先假设只有 $i$ 左边的史莱姆可以把它吃掉，那么找到左端点第一个不与第 $i+1$ 个史莱姆大小相同的史莱姆的位置 $r$，从 $r$ 起不断减小这个指针，如果 $\sum_{j=r}^{i-1}a_j$ 的总和比 $a_i$ 要大，把 $i$ 的答案设为 $i-r$ 即可。

其中求 $a$ 的某一段的总和可以前缀和，同时使用类似的方法找到 $i$ 右边的 $r'$，$i$ 的答案取 $\min\{i-r,r'-i\}$ 即可。

$n\log n$ 做法：

二分两个 $r,r'$ 的位置，同样前缀和处理一下即可。

用 $ls_i$ 统计第一个在 $i$ 左边的且 $a_{ls_i}$ 不与 $a_i$ 相等的位置，$rs_i$ 记录其右边的位置。

这里贴一下找 $r$ 的位置的代码。

```cpp
int sqz(int x,int k){
	if (qz[x-1]<=k) return 0;
	if (a[x-1]>a[x]) return x-1;
	int l=1,r=ls[x-1]-(ls[x-1]!=x-1);
	if (l>r) return 0;
	while (l<r){
		int mid=(l+r+1)>>1;
		if (qz[x-1]-qz[mid-1]<=k) r=mid-1;
		else l=mid;
	}
	return l;
}
```

---

## 作者：Locix_Elaina_Celome (赞：1)

# [CF1923D Slimes](https://www.luogu.com.cn/problem/CF1923D) 题解
## 题意

> 有 $n$ 个史莱姆，一个史莱姆可以花一个时刻吃掉相邻的一个**严格小于**自己的史莱姆并将自己的大小增加吃掉的大小。问每个史莱姆最快多久被吃掉。

## 题解

对于一个史莱姆 $i$，很明显时被其相邻的一个区间 $[j,i)$ 或 $(i,j]$ 的所有史莱姆合并起来吃掉。考虑这个区间能吃 $i$ 的条件。

首先这个区间的总和 $> a_i$，并且可以合并，即不是全部相同。而这个区间吃掉 $i$ 的时间就是这个区间的长度。

发现这个东西具有单调性，所以二分再加上某种数据结构维护一下即可。我用的 ST 表。

## 代码

```cpp

using namespace std;
#include<bits/stdc++.h>
//#include<cstdio>
//#include<cstring>
//#include<string>
//#include<iostream>
//#include<utility>
//#include<algorithm>
#define MAX(x,y) (x<y?y:x)
#define MIN(x,y) (x<y?x:y)
#define ABS(x) (x<0?-x:x)
#define lb(x) ((x)&(-(x)))
#define N 1000005
#define LL long long
#define LD long double
#define int LL
//#define double LD
#define P 1000000007
#ifdef _WIN32
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#elif _WINDOWS_
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#else
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif
constexpr double EPS=(1e-9);
#ifdef int
constexpr int INF=1211081101201201140;
#else
constexpr int INF=1145141919;
#endif
template<typename T>T Max(T x,T y){return MAX(x,y);}
template<typename T>T Min(T x,T y){return MIN(x,y);}
template<typename T>T Abs(T x){return ABS(x);}
template<typename T>void Swap(T&x,T&y){x^=y^=x^=y;}
template<typename T>T Gcd(T x,T y){while(y^=x^=y^=x%=y);return x;}
template<typename T>
T qp(T a,T b){T sum=1;
while(b){if(b&1)sum=(sum*a)%P;a=(a*a)%P;b>>=1;}return sum;}
template<typename T>
void read(T&x){
x=0;char c=getchar();/*T fl=1;*/
while(c<'0'||c>'9'){/*if(c == '-')fl=-1;*/c=getchar();}
while('/'<c&&c<':'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}/*x*=fl;*/}
template<typename T>
void write(T x){if(x<0){x=-x;putchar('-');}
if(x>9){write(x/10);}putchar(x%10|48);}
int n;
int sm[N];
int a[N];
int st[N][25];
int lg[N];
void ST(){
	for(int i=1;i<=n;i++)st[i][0]=a[i];
	for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int j=1;j<=20;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			int x=st[i][j-1],y=st[i+(1<<(j-1))][j-1];
			st[i][j]=(x==y?x:(int)0);
		}
	}
}
int ask(int l,int r){
	if(r<l)return 1;
	int x=st[l][lg[r-l+1]],y=st[r-(1<<lg[r-l+1])+1][lg[r-l+1]];
	if(l==r)return 0;
	return (x==y?x:(int)0);
}
#undef int
int main(){
#define int LL
	int T;
	read(T);
	while(T--){
		read(n);
		for(int i=0;i<=n+2;i++)sm[i]=a[i]=0; 
		for(int i=1;i<=n;i++){
			read(a[i]);
			sm[i]=sm[i-1]+a[i];
		}
		ST();
		for(int i=1;i<=n;i++){
			int l,r;
			int x=INF;
			if(i!=1){
				l=1,r=i-1;
				while(l<r){
					int mid=(l+r+1)>>1;
					int num=ask(mid,i-1);
					if(num>a[i])num=0;
					if(num==0&&sm[i-1]-sm[mid-1]>a[i])l=mid;
					else r=mid-1;
				}
				int num=ask(l,i-1);
				if(num>a[i])num=0;
				if(l&&num==0&&sm[i-1]-sm[l-1]>a[i])x=i-l;
			}
			if(i!=n){
				l=i+1,r=n;
				while(l<r){
					int mid=(l+r)>>1;
					int num=ask(i+1,mid);
					if(num>a[i])num=0;
					if(num==0&&sm[mid]-sm[i]>a[i])r=mid;
					else l=mid+1;
				}
				int num=ask(i+1,l);
				if(num>a[i])num=0;
				if(l<=n&&num==0&&sm[l]-sm[i]>a[i])
					x=Min(x,l-i);
			}
			write((x==INF?-1:x));
			putchar(' ');
		}
		puts("");
	}
	return 0;
}

``````

---

## 作者：ATZdhjeb (赞：1)

### 题目大意

给你 $n$ 个排成一列的史莱姆（？），第 $i$ 个的大小为 $a_i$，每一轮中你可以让某一个史莱姆吞掉它相邻两个史莱姆中的一个，前提是它自己的大小严格大于被吞掉的那个。吞掉之后被吞的史莱姆消失，吞的史莱姆大小变成它俩原本大小之和，现在问你对于每一个史莱姆，最少第几轮可以让它被吞掉。

数据范围：

$1\le \sum n\le3\times10^5$。

$1\le a_i\le 10^9$。

$1\le T\le 10^4$。

### 简要分析

首先，一段区间的史莱姆可以合并成一个的充要条件是这段区间里的 $a_i$ 至少有两个不同的取值，证明显然。而考虑对于史莱姆 $i$ 而言，它要么是被左边的某个史莱姆吞掉的，要么是右边，这两种情况可以分开算。我们接下来只讨论左边的情况。

一个位于 $i$ 左边的史莱姆想要吞掉 $i$，那么它必须吞掉它与 $i$ 之间的所有史莱姆，同时还有可能需要吞掉它左边的一些史莱姆，我们发现这个过程可以看作是把 $i$ 左边一段区间的史莱姆合并成了一个（具体哪一个我们不关心），所以自然考虑扫描线，扫到 $i$ 的时候对所有 $j\in[1,i-1]$ 维护区间 $[j,i-1]$ 的一些信息。

我们需要维护什么呢？发现想让 $[j,i - 1]$ 合并出来的史莱姆吞掉 $i$，要满足：

1. $\sum\limits_{k=j}^{i-1}a_k>a_i$。

2. 区间 $[j,i - 1]$ 是可以合并的。

第一项显然是好维护的，可以直接在前缀和上二分出一个最大的 $t$，满足 $\sum\limits_{k=t}^{i-1}a_k>a_i$，然后只需要找出最大的 $j\le t$，使得 $[j,i-1]$ 是可合并的。

我们令 $f_j = 1$ 表示 $[j,i-1]$ 是可合并的，$f_j=0$ 反之。那么考虑新加入一个 $j$ 的时候，它前面不可合并的必然是一段 $a$ 相等的连续段，那么若 $a_j$ 也等于前面的 $a$，那么我们什么都干不了；否则我们可以暴力地把前面一段不可合并的都标记为可合并的。因为扫描线的过程中每个点最多从不可合并变得可合并一次，所以均摊复杂度是对的。然后查询的时候找最后面的一个 $1$ 即可。

那么，我们需要的就是一个数据结构来维护 $f$，要求支持单点修改，找区间最后一个 $1$，显然线段树符合要求。

时间复杂度 $O(n\log n)$，我猜不是正解，但是反正能过。

### 代码实现

~~这玩意其实不用看，赛场上脑子不清醒写得又臭又长。~~

注意实现的时候需要特殊处理 $j = i - 1$ 的情况，此时我们是否将 $[j,i-1]$ 视为不可合并的应取决于 $a_i$ 是否和 $a_j$ 相等。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define mp make_pair
#define pii pair<int,int>
#define cpx complex<double>
#define INF 0x3f3f3f3f
#define mod 998244353
#define rep(i,a,b) for (int (i) = (a); (i) <= (b); ++(i))
#define per(i,a,b) for (int (i) = (a); (i) >= (b); --(i))

using namespace std;

inline int input() {
	int x = 0,f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c <= '9' && c >= '0') {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}

inline char get() {
	char c = getchar();
	while (isspace(c)) c = getchar();
	return c;
}

const double PI = acos(-1);

int T,n,a[300010],tree[1200010],ans[300010],c[300010],q[300010];
ll sum[300010];
vector<int> vec[300010];

struct Data {
	int idx;
	int val;
	
	Data(int a = 0,int b = 0) {
		val = a;
		idx = b;
	}
	
	bool operator < (Data b) const {
		return val < b.val;
	}
}b[300010];

int get_left(int u) {
	return u << 1;
}

int get_right(int u) {
	return u << 1 | 1;
}

void push_up(int u) {
	tree[u] = tree[get_left(u)] + tree[get_right(u)];
}

void update(int u,int l,int r,int x,int k) {
	if (l == r) {
		tree[u] = k;
		return;
	}
	if (x <= (l + r) / 2) update(get_left(u),l,(l + r) / 2,x,k);
	else update(get_right(u),(l + r) / 2 + 1,r,x,k);
	push_up(u);
}

int queryr(int u,int l,int r,int x,int y) {
	if (x <= l && r <= y) {
		if (tree[u] == 0) return -1;
		if (l == r) return l;
		int temp = queryr(get_right(u),(l + r) / 2 + 1,r,x,y);
		if (~temp) return temp;
		return queryr(get_left(u),l,(l + r) / 2,x,y);
	}
	int temp = -1;
	if (y > (l + r) / 2) temp = queryr(get_right(u),(l + r) / 2 + 1,r,x,y);
	if (~temp) return temp;
	if (x <= (l + r) / 2) temp = queryr(get_left(u),l,(l + r) / 2,x,y);
	return temp;
}

int queryl(int u,int l,int r,int x,int y) {
	if (x <= l && r <= y) {
		if (tree[u] == 0) return -1;
		if (l == r) return l;
		int temp = queryl(get_left(u),l,(l + r) / 2,x,y);
		if (~temp) return temp;
		return queryl(get_right(u),(l + r) / 2 + 1,r,x,y);
	}
	int temp = -1;
	if (x <= (l + r) / 2) temp = queryl(get_left(u),l,(l + r) / 2,x,y);
	if (~temp) return temp;
	if (y > (l + r) / 2) temp = queryl(get_right(u),(l + r) / 2 + 1,r,x,y);
	return temp;
}

int findr(int x) {
	int lans = 1,rans = x - 1;
	while (lans <= rans) {
		int mid = (lans + rans) / 2;
		if (sum[x - 1] - sum[mid - 1] <= a[x]) rans = mid - 1;
		else lans = mid + 1;
	}
	return rans;
}

int findl(int x) {
	int lans = x + 1,rans = n;
	while (lans <= rans) {
		int mid = (lans + rans) / 2;
		if (sum[mid] - sum[x] <= a[x]) lans = mid + 1;
		else rans = mid - 1;
	}
	return lans;
}

void create(int u,int l,int r) {
	tree[u] = 0;
	if (l == r) return;
	create(get_left(u),l,(l + r) / 2);
	create(get_right(u),(l + r) / 2 + 1,r);
}

void solve() {
	n = input();
	rep (i,1,n) {
		sum[i] = sum[i - 1] + (a[i] = input());
		b[i] = Data(a[i],i);
		vec[i] = vector<int>();
	}
	sort(b + 1,b + n + 1);
	int maxa = 0;
	rep (i,1,n) {
		if (b[i].val != b[i - 1].val) ++maxa;
		c[b[i].idx] = maxa;
	}
	create(1,1,n);
	rep (i,1,n) ans[i] = INF;
	int front = 1,rear = 0;
	rep (i,1,n) {
		int temp = findr(i);
		if (temp) {
			temp = queryr(1,1,n,1,temp);
			if (~temp) ans[i] = min(ans[i],i - temp);
		}
		while (front <= rear) {
			int k = front;
			if (q[k] != c[i]) {
				for (int j : vec[q[k]]) update(1,1,n,j,1);
				vec[q[k]] = vector<int>();
				++front;
			} else break;
		}
		while (front <= rear) {
			int k = rear;
			if (q[k] != c[i]) {
				for (int j : vec[q[k]]) update(1,1,n,j,1);
				vec[q[k]] = vector<int>();
				++front;
			} else break;
		}
		if (c[i] != c[i + 1]) update(1,1,n,i,1);
		else {
			vec[c[i]].push_back(i);
			bool f = true;
			rep (k,front,rear) if (q[k] == c[i]) f = false; 
			if (f) q[++rear] = c[i];
		}
	}
	rep (i,1,n) vec[i] = vector<int>();
	front = 1;
	rear = 0;
	create(1,1,n);
	per (i,n,1) {
		int temp = findl(i);
		if (temp <= n) {
			temp = queryl(1,1,n,temp,n);
			if (~temp) ans[i] = min(ans[i],temp - i);
		}
		while (front <= rear) {
			int k = front;
			if (q[k] != c[i]) {
				for (int j : vec[q[k]]) update(1,1,n,j,1);
				vec[q[k]] = vector<int>();
				++front;
			} else break;
		}
		while (front <= rear) {
			int k = rear;
			if (q[k] != c[i]) {
				for (int j : vec[q[k]]) update(1,1,n,j,1);
				vec[q[k]] = vector<int>();
				++front;
			} else break;
		}
		if (c[i] != c[i - 1]) update(1,1,n,i,1);
		else {
			vec[c[i]].push_back(i);
			bool f = true;
			rep (k,front,rear) if (q[k] == c[i]) f = false; 
			if (f) q[++rear] = c[i];
		}
	}
	rep (i,1,n) if (ans[i] == INF) printf("%d ",-1);else printf("%d ",ans[i]);
	puts("");
}

int main() {
	T = input();
	while (T--) solve();
	return 0;
}
```

---

## 作者：AtomAlpaca (赞：0)

感觉比较好玩的一道题。

## 题意

有一排史莱姆，一个史莱姆能吃掉相邻的史莱姆当且仅当它的大小严格大于和它相邻的史莱姆。一个史莱姆吃掉另一个史莱姆后大小会加上被吃掉的史莱姆大小。求每个史莱姆最少经过多少次操作才能被吃掉。

## 题解

我们考虑一个史莱姆被吃掉的最优方案一定是把它前面或后面一段史莱姆合并成一个严格大于它草史莱姆然后把它吃掉。因为显然只有这些操作是有用的。

不难发现一段连续的史莱姆不能被合并成一个当且仅当这一段史莱姆大小都相等。否则一定有一个最大的史莱姆和一个比它小的史莱姆相邻，吃掉它之后就产生了一个严格大于其余史莱姆的史莱姆。

于是我们可以在前后分别二分这个连续段的长度。检查区间和只需要前缀和一下。检查一段大小是否都相等可以维护区间最大最小值看是否相等，但还有一个方法是考虑在 st 表合并两个区间的过程中，新的区间全相等当且仅当这两个区间分别全相等且两个区间中的元素也相等。这样可以剩下一倍常数。

整体复杂度 $O(n \log n)$。

## 代码
``` c++
#include <bits/stdc++.h>

typedef long long ll;
const int MAX = 3e5 + 5;

ll n, T;
ll a[MAX], p[MAX];
bool st[25][MAX];

void build()
{
  for (int i = 1; i <= n; ++i) { st[0][i] = true; }
  for (int i = 1; (1 << i) <= n; ++i)
  {
    for (int j = 1; j + (1 << i) - 1 <= n; ++j)
    {
      st[i][j] = st[i - 1][j] and st[i - 1][j + (1 << (i - 1))] and a[j] == a[j + (1 << i) - 1];
    }
  }
}

bool qry(int l, int r)
{
  if (l == r) { return true; }
  int lg = log2(r - l + 1);
  return !(st[lg][l] and st[lg][r - (1 << lg) + 1] and a[l] == a[r]);
}

int search(int x)
{
  if (x != 1 and a[x - 1] > a[x]) { return 1; }
  if (x != n and a[x + 1] > a[x]) { return 1; }
  int l = 1, r = x - 1, ans = n + 1;
  while (l <= r)
  {
    int mid = l + ((r - l) >> 1);
    if (p[x - 1] - p[mid - 1] > a[x] and qry(mid, x - 1)) { ans = std::min(ans, x - mid); l = mid + 1; }
    else { r = mid - 1; }
  }
  l = x + 1, r = n;
  while (l <= r)
  {
    int mid = l + ((r - l) >> 1);
    if (p[mid] - p[x] > a[x] and qry(x + 1, mid)) { ans = std::min(ans, mid - x); r = mid - 1; }
    else { l = mid + 1; }
  }
  return ans == n + 1 ? -1 : ans;
}

void solve()
{
  scanf("%lld", &n);
  for (int i = 1; i <= n; ++i) { scanf("%lld", &a[i]); p[i] = a[i]; p[i] += p[i - 1]; }
  build();
  for (int i = 1; i <= n; ++i) { printf("%d ", search(i)); }
  printf("\n");
}

int main() { scanf("%lld", &T); while (T--) { solve(); } }
```

---

## 作者：I_will_AKIOI (赞：0)

### 题目大意

有 $n$ 个史莱姆，大小分别为 $a_i$。每次一个史莱姆若比相邻的史莱姆大，则可以吃掉他。同时大小也会增加吃掉的史莱姆的大小。请问第 $1\sim n$ 个史莱姆最快会在什么时候被吃掉。

在一个区间内，若史莱姆大小互不相等，肯定可以全部吃掉，变成一个大史莱姆。具体操作就是最大的史莱姆依次把小的吃掉，所以顺序问题是不用担心的。

于是可以想到二分，二分 $i$ 的左右两侧，找到大小总和大于 $a_i$ 的，最近的史莱姆，接着两个取最小值。这里求解区间内的和，可以使用前缀和维护。但是这里有个坑点：**若区间内是全部相等的，就没办法吃掉了**。我当时被这点卡住了，导致无法场切。不过赛后能做出 D 也不错了。

某位谷民在群里提供的 hack 数据：

输入：

```
1
5
2 2 2 2 1
```

输出：

```
4 3 2 -1 1
```

因此，我们二分时还需要判断区间内是否相等，不符合则排除这个区间。

判断一个区间是否相等，我们使用树状数组或线段树未免有些大炮轰蚊子，我们可以像[这道题](https://www.luogu.com.cn/problem/CF1927D)一样，记录这个点**属于的相同区间的起点**，然后判断他们的区间起点是否相同。例如，刚才 hack 数据的 $1\sim4$ 的区间起点为 $1$，$5$ 的区间起点为 $5$。

代码如下：

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,a[300005],sum[300005],f[300005];
int left(int p)//左边满足要求的点
{
  int l=0,r=p-1,mid,ans=-1;
  while(l<r)
  {
    mid=l+r+1>>1;
    if(sum[p-1]-sum[mid-1]<=a[p]||f[p-1]==f[mid]&&a[mid]<=a[p]) r=mid-1;//区间和能否吃掉当前史莱姆，且区间内互不相同
    else l=ans=mid;
  }
  return ans;
}
int right(int p)//右边满足要求的点
{
  int l=p+1,r=n+1,mid,ans=-1;
  while(l<r)
  {
    mid=l+r>>1;
    if(sum[mid]-sum[p]<=a[p]||f[p+1]==f[mid]&&a[mid]<=a[p]) l=mid+1;
    else r=ans=mid;
  }
  return ans;
}
void solve()
{
  int last=0; 
  cin>>n;
  for(int i=1;i<=n;i++)//前缀和
  {
    cin>>a[i];
    sum[i]=sum[i-1]+a[i];
  }
  for(int i=1;i<=n;i++)//相同区间起点
  {
    if(a[i]==a[last]) f[i]=last;
    else f[i]=i,last=i;
  }
  for(int i=1;i<=n;i++)
  {
    int x=left(i),y=right(i);
    if(x==-1&&y==-1) cout<<-1<<" ";
    else if(x>-1&&y>-1) cout<<min(i-x,y-i)<<" ";
    else if(x==-1) cout<<y-i<<" ";
    else cout<<i-x<<" ";
    //对两边的点分类讨论
  }
  cout<<"\n";
  return;
}
signed main()
{
  ios::sync_with_stdio(false);
  int t;
  cin>>t;
  while(t--) solve();
  return 0;
}
```

---

## 作者：aeiouaoeiu (赞：0)

**Key Observation**：$a$ 吃 $b$ 与 $b$ 吃 $a$ 是等价的。

于是吃就变成了合并。对于一个数 $x$，我们分别考虑它的左边和右边。

以左边为例，此时问题变成了找最小的 $y$，使得 $\sum_{y\le i<x}a_i>a_x$，转成前缀和后显然可以通过二分在 $\mathcal{O}(\log n)$ 时间内完成。

但是还要注意合并时两个数不能相等。

于是我们预处理所有极长相等区间，如果求出来的 $y$ 不为 $x-1$ 且与 $x-1$ 在同一个极长相等区间内，就要把 $y$ 调为区间左端的前驱。

右边同理。

[code](https://codeforces.com/contest/1923/submission/248033041)。

---

## 作者：Wei_Han (赞：0)

## 题目大意
有一排 $n$ 个黏液，每个黏液每次都只能花费 $1$ 单位时间吃掉严格比它小的邻居，求每个粘液被吃掉的最小时间，如果无解报告 $-1$。
## Solution
显而易见，对于第 $i$ 个粘液，想让它被吃掉，需要让左边或者右边粘液大于它，那么我们只需要找到它的左右粘液最少需要吃到哪一个位置就行了，左右粘液的总和可以前缀后缀和预处理，又因为前缀和是一定单调递增的，直接二分即可。

二分时也需要注意一个问题，如果当前二分的区间内全是同一个数，那么是不能相互之间吃的，也就是不合法（可以参考样例三），注意预处理二分的左右范围即可，也就是找到左右**第一个连续区间**的末尾，当做左右端点再二分，就可以避免这个问题。

二分时注意再处理一些细节，时间复杂度 $O(n\log n)$。
## Code
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define pr printf("\n")
#define pp printf(" ")
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; i ++ )
#define Fo(a,i,b) for(ll i = a ; i >= b ;-- i  )
using namespace std;
typedef long long ll;
typedef double db;
const int N=5e5+5;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
ll t,n,a[N],fac[N],pre[N],l1[N],r1[N];
int main(){
	read(t);
	while(t--){
		read(n);
		fo(0,i,n+1) a[i]=0;
		fo(0,i,n+1) fac[i]=pre[i]=0,l1[i]=r1[i]=0;
		fo(1,i,n) read(a[i]),fac[i]=fac[i-1]+a[i];
		Fo(n,i,1) pre[i]=pre[i+1]+a[i];
		ll last=1,nw=0,la=1;
		l1[1]=1,r1[n]=n;
		fo(1,i,n){l1[i+1]=la;if(a[i]!=a[i+1]) la=i+1;}
		last=n,nw=0,la=n;
		Fo(n,i,1){r1[i-1]=la;if(a[i]!=a[i-1]) la=i-1;}
		fo(1,i,n){
			ll minn=INF,l,r;
			l=1,r=l1[i]-1;
			minn=a[i-1]>a[i]?1:minn,minn=a[i+1]>a[i]?1:minn; 
			if(l==r) minn=min(minn,pre[r]-pre[i]>a[i]?i-r:minn);
			else if(l<r){
				while(l<r){
					ll mid=(l+r+1)>>1;
					if(pre[mid]-pre[i]>a[i]) l=mid;
					else r=mid-1;
				}
				if(pre[l]-pre[i]>a[i]) minn=min(minn,abs(i-l));
			}
			l=r1[i]+1,r=n;
			if(l==r){minn=min(minn,fac[l]-fac[i]>a[i]?l-i:minn);}
			else if(l<r){
				while(l<r){
					ll mid=l+r>>1;
					if(fac[mid]-fac[i]>a[i]) r=mid;
					else l=mid+1;
				}
				if(fac[r]-fac[i]>a[i]) minn=min(minn,abs(i-r));	
			}
			wr(minn==INF?-1:minn),pp;
		}
		pr;
	}
	return 0;
}
``````

---

## 作者：cosf (赞：0)

## [CF1923D](https://www.luogu.com.cn/problem/CF1923D)

我们可以考虑将问题分为两部分：

- 当前史莱姆被左边的吃掉。
- 当前史莱姆被右边的吃掉。

两部分显然是一样的，这里只考虑左边。

如果 $a_{i - 1} > a_i$，那显然一次就能吃掉了。

那么，反之，如果它能被吃掉，一定存在一个 $j < i$，满足 $\sum_{k=j}^{i - 1}a_k > a_i$，并且 $a_j \dots a_{i - 1}$ 能够被合并成一个。

显然，如果 $a_j \dots a_{i-1}$ 全部相同是合并不了的。反之，如果有但凡一个不同的，就吃得掉。

证明？只要让当前最大的并且能吃的吃东西就可以了。

所以我们维护一个 $a_{pre_i}$ 表示 $a_i$ 往前第一个和 $a_i$ 不同的 $a$ 即可。

然后我们考虑怎么判断 $\sum_{k=j}^{i - 1}a_k > a_i$。

先做前缀和 $s_i = \sum_{j=1}^i$，然后就相当于求最大的 $j$ 使得 $s_{i - 1} - s_{j - 1} \gt a_i$。

因为 $j + 1$ 是不符合的，所以有 $s_{i - 1} - s_{j} \le a_i$，即 $s_j \ge s_{i - 1} - a_i$。直接 lower_bound。

当然，我们要先把 $s_{i-1} \le a_i$ 这种怎么都不可能吃掉的情况判掉。

## [AC Record](https://codeforces.com/contest/1923/submission/247965409)

---

## 作者：linyuhuai (赞：0)

[更好的阅读体验](https://by505244.github.io/oi_blogs/2024/03/01/CF1923D/)

### 题意

有 $n$ 个史莱姆。第 $i$ 个史莱姆的大小为 $a_i$。

对于每个时刻，恰好有一个史莱姆吃掉其相邻的另一个更小（相等不行）的史莱姆，并将自己的大小增加被吃掉的史莱姆的大小。

对于每个史莱姆，计算它被其他史莱姆吃掉所需的最短时间（不能被吃则输出 `-1`）。

多测。

### sol

对 $1$ 到 $n$ 的每个史莱姆进行一次遍历。

设当前遍历到的史莱姆为 $x$。


若要吞并 $x$ 号史莱姆，则需找到 $i(i\not=x)$ 满足：

$$
\left\{ 
    \begin{aligned}
    \exists k_1,k_2\in[i,x),a_{k_1}\not=a_{k_2}  \texttt{and}
    \sum_{k=i}^{x-1}a_k> a_x(i<x)\cr 
    \exists k_1,k_2\in(x,i],a_{k_1}\not=a_{k_2}  \texttt{and}
    \sum_{k=x+1}^{i}a_k>a_x 
    (i>x)
    \end{aligned}
\right.
$$

为了方便起见，下文默认 $i<x$。

考虑判断 $i$ 是否满足以上条件。

为了判断 
$\exists k_1,k_2\in[i,x),a_{k_1}\not=a_{k_2}$ 
这个条件，我们将每一个具有相同数字的块进行打上编号。判断是否 $i$ 符合只需要判断 $i$ 所在的块的编号和 $x$ 是否相同即可。

对于后半部分
$\sum_{k=i}^{x-1}a_k> a_x$ 
可用前缀和进行解决。记 $s_k=\sum_{j=1}^ka_k$，判断 $i$ 是否符合条件只需要判断 $s_{x-1}-s_{i-1}$ 是否大于 $a_x$ 即可。
 
显然上述过程经过预处理后判断 $i$ 是否合法的时间复杂度为 $\mathcal{O}(1)$ 的。

接下来考虑如何找到 $i$。

对于 $i^{'}<i$，若 $i$ 满足上述条件，则 $i^{'}$ 一定也满足。所以答案是具有单调性的。便可以二分查找 $i$。

查找结束后记得对 $i$ 判断一下条件，不满足则输出 `-1`。

对于 $i>x$ 的情况同理。

时间复杂度 $\mathcal{O}(Tn\log n)$。

---

