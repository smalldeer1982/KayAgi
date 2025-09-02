# Frequency Problem (Easy Version)

## 题目描述

This is the easy version of the problem. The difference between the versions is in the constraints on the array elements. You can make hacks only if all versions of the problem are solved.

You are given an array $ [a_1, a_2, \dots, a_n] $ .

Your goal is to find the length of the longest subarray of this array such that the most frequent value in it is not unique. In other words, you are looking for a subarray such that if the most frequent value occurs $ f $ times in this subarray, then at least $ 2 $ different values should occur exactly $ f $ times.

An array $ c $ is a subarray of an array $ d $ if $ c $ can be obtained from $ d $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 说明/提示

In the first sample, the subarray $ [1, 1, 2, 2, 3, 3] $ is good, but $ [1, 1, 2, 2, 3, 3, 3] $ isn't: in the latter there are $ 3 $ occurrences of number $ 3 $ , and no other element appears $ 3 $ times.

## 样例 #1

### 输入

```
7
1 1 2 2 3 3 3```

### 输出

```
6```

## 样例 #2

### 输入

```
10
1 1 1 5 4 1 3 1 2 2```

### 输出

```
7```

## 样例 #3

### 输入

```
1
1```

### 输出

```
0```

# 题解

## 作者：duyi (赞：21)

[勇敢向前进，前进有奖品！](https://www.cnblogs.com/dysyn1314/p/14007922.html)

# CF1446D1, D2 Frequency Problem

## 题目大意

[题目链接](https://codeforces.com/contest/1446/problem/D2)

有一个长度为 $n$ 的序列 $a_1,a_2,\dots ,a_n$。

我们定义一个子段（连续子序列）是好的，当且仅当其中出现次数最多的元素不唯一。

请求出，最长的、好的子段的长度。

数据范围：$1\leq n\leq 2\times10^5$。对于 D1，$1\leq a_i\leq \min(n,100)$，对于 D2，$1\leq a_i\leq n$。

## 本题题解

### D1

如果原序列里，出现次数最多的数不唯一，则答案就是 $n$。否则，考虑那个唯一的、出现次数最多的元素，记为 $x$。

发现，最长的、好的子段（也就是答案），有个必要条件是：$x$ 是其中出现次数最多的元素之一。

证明：考虑一个好的子段 $[l,r]$，如果 $x$ 不是其中出现次数最多的元素。那么，我们依次考虑 $[l-1,r]$, $[l-2,r]$, ... ..., $[1,r]$, $[1,r+1]$, $[1,r+2]$, ... ..., $[1,n]$。因为 $x$ 的数量每次最多增加 $1$ 个，且它是整个序列里出现次数最多的元素。那么总有某一步后，$x$ 和序列里其他出现最多的元素一样多。

我们枚举，答案的子段里，和 $x$ 出现次数一样多的元素是谁，记为 $y$。问题转化为，对一组数值 $(x,y)$ 计算答案。

我们可以忽略数列里除 $x$, $y$ 外的其他数。问题进一步转化为：求一个最长的子段，满足 $x$, $y$ 的出现次数一样多。

把数列里的 $x$ 看做 $1$，$y$ 看做 $-1$，其他数看做 $0$。得到一个序列 $b$。那么，我们要求最长的、和为 $0$ 的子段长度。做前缀和，令 $\text{sum}_i=\sum_{j=1}^{i}b_j$。问题相当于找两个位置 $0\leq l < r\leq n$，满足 $\text{sum}_r = \text{sum}_l$。对每个 $\text{sum}$ 值 $v$（$[-n,n]$，共 $2n+1$ 个值）记录它最早的出现位置。然后枚举 $r$，并更新答案即可。

有读者可能对“忽略数列里除 $x$, $y$ 外的其他数”这一做法心存疑虑。因为有可能，我们找到的序列里，存在一个其他数值 $z$，出现次数多于 $x,y$。但是，基于以下两点：

1. 存在这样 "$z$" 的子段，长度一定小于答案。证明：我们按和上面同样的方法，向两边扩展一下，直到 $x$ 和 $z$ 出现次数相等。得到的序列仍然满足：存在两个数 $(x,z)$ 出现次数相等，且新的子段长度比原来长。所以只要存在这样的 "$z$"，我们就扩展一下，最终一定能得到没有 "$z$" 的，也就是以 $x$ 为出现次数最多的数的子段，且长度一定严格大于原来的子段。
2. 答案的子段，一定会被考虑到。因为只要满足 $x$, $y$ 出现次数相等，就会被考虑到。

我们用这种方法，求出的就是答案。

时间复杂度 $O(n\times\text{maxa})=O(n\times 100)$。可以通过 D1。

### D2

考虑答案序列里，出现次数最多的数，的出现次数。如果出现次数 $>\sqrt{n}$，则满足条件的数值只有不超过 $\sqrt{n}$ 个，我们套用 D1 的做法，时间复杂度 $O(n\sqrt{n})$。

如果出现最多的数，出现次数 $\leq \sqrt{n}$，我们枚举这个出现次数，记为 $t$。然后做 two pointers。

具体来说，枚举区间的右端点 $r$。对每个 $r$，记最小的，使得 $[l,r]$ 内所有数出现次数都 $\leq t$ 的 $l$ 为 $L_r$。容易发现，对于 $r=1,2,\dots,n$，$L_r$ 单调不降。并且，在当前的 $t$ 下，对一个 $r$ 来说，如果 $[L_r,r]$ 不是好的子段（出现次数为 $t$ 的数值，不到 $2$ 个），那么其他 $[l,r]$ ($L_r<l\leq r$) 也不可能是。因为出现次数为 $t$ 的数值，只会更少。

所以，随着我们从小到大枚举 $r$，只需要用一个变量来记录当前的 $L_r$。同时用数组维护一下，当前每个数的出现次数，以及**每个出现次数**的出现次数。就能确定，当前的 $[L_r,r]$ 是否是好的区间。具体可以见代码。这个 two pointers 的过程是 $O(n)$ 的。因为有 $\sqrt{n}$ 个 $t$，所以这部分的时间复杂度也是 $O(n\sqrt{n})$。

总时间复杂度 $O(n\sqrt{n})$。

## 总结

本题首先需要一个结论。通过观察、分析题目性质，是可以想到的。

然后需要一个技巧：把一个普通序列，转化为只含 $0$, $1$, $-1$ 的序列。这样就把复制的、出现次数的关系，转化为了简单的数值关系。这个技巧，在一些经典的，二分中位数的题里也有用到（把 $> \text{mid}$ 的视为 $1$，$\leq \text{mid}$ 的视为 $-1$）。

在 D2 里，想到根号分治以后，应该就不是太难了。

## 参考代码(both D1 & D2)


[我要开飞机！！！我要当经理！！！](https://www.cnblogs.com/dysyn1314/p/14007922.html)


---

## 作者：Felix72 (赞：3)

这题是结论题。放个结论：最优的区间里的众数，一定有一个是全局众数。

为什么呢？因为如果你当前的答案区间里出现最多的不是全局众数，那么一定可以通过扩展这个区间变成一个更大的合法区间，理由是反正全局众数出现最多次，扩展过程中其他数字出现再多也不会比最后全局众数出现的次数大。

这样，这题就可以枚举第二个众数，再从左往右扫一遍用一个数组记录状态即可。注意每个区间并不需要单独判断合法性，因为如果有一个数出现的次数比你枚举的的数字和全局众数出现的次数都多，那这个区间肯定不是最优的，用它更新不影响答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
int n, a[N], tong[N], pre, f[N * 2], ans;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> a[i];
	for(int i = 1; i <= n; ++i)
	{
		tong[a[i]]++;
		if(tong[a[i]] > tong[pre]) pre = a[i];
	}
	for(int i = 1; i <= 100; ++i)
	{
		if(i == pre) continue;
		int now = n;
		memset(f, -1, sizeof(f));
		f[n] = 0;
		for(int j = 1; j <= n; ++j)
		{
			if(a[j] == pre) ++now;
			if(a[j] == i) --now;
			if(f[now] == -1) f[now] = j;
			else ans = max(ans, j - f[now]);
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：whiteqwq (赞：3)

[CF1446D1 Frequency Problem (Easy Version)](https://www.luogu.com.cn/problem/CF1446D1)&[CF1446D2 Frequency Problem (Hard Version)](https://www.luogu.com.cn/problem/CF1446D2)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1758352)

## 题意
- 给定一个长度为$n$的序列，定义好的序列为众数不唯一的序列，求最长的好的连续子序列。
- 数据范围：$1\leqslant n\leqslant 2\times 10^5$，$1\leqslant a_i\leqslant n$，对于Easy Version，$a_i\leqslant 100$。

## 分析
首先有一个结论：**最长的众数不唯一的子序列一定包含整个序列的众数**。

反证法：设整个序列的众数为$x$，如果这个子序列中众数不含有$x$，那么我们尝试每次给这个子序列扩展一个位置（如果扩展不了那么众数一定含有这个$x$），因为$x$为整个序列的众数，每一次扩展会最多让$x$增加$1$，所以总有一个时间$x$的数量会等于当前序列众数的数量，此时这个序列满足条件，且它一定优于原来的序列。

有了这个结论，我们先求得整个序列的众数$x$，如果众数不唯一，那么答案就是$n$，否则我们继续分析：

先考虑Easy Version，因为$a_i$的值域为$[1,100]$，所以我们直接枚举这个众数（设为$y$），然后重构一个新序列$b$：

- 当$a_i=x$时，$b_i=1$；
- 当$a_i=y$时，$b_i=-1$；
- 否则，$b_i=0$。

对于一个满足条件的序列，**它的$x$出现次数与$y$的出现次数一定相等**，因此我们可以统计所有$b$之和为$0$的序列进答案。

但是这里有一个疑问：如果在某一个区间中存在一个数$z$，出现次数比$x$和$y$均多，那这样的序列是否合法？

还是可以用上面的那种扩展的方法，发现一定存在一个更长的序列众数为$x,z$，且比刚才的序列更优，因此刚刚的序列被统计了也不会对最终答案造成影响。

这样我们就用$O(maxa\times n)$的复杂度解决了Easy Version。

对于Hard Version，观察数据范围，我们可以考虑进行根号分治。

设定一个阈值$S$，对于出现次数大于$S$的数字，它的个数一定不会超过$\frac{n}{S}$，因此我们可以用一个$\text{vector}$存下所有出现次数大于$S$的数字，然后用Easy Version的方法暴力统计答案，时间复杂度$O(n\sqrt{n})$。

然后，对于出现次数小于等于$S$的数字，我们很显然可以**枚举这个出现次数**（设为$i$），然后对于整个序列做一遍$\text{two pointer}$，里面**维护所有数的出现次数**和**出现次数的出现次数**，只要出现次数$i$的出现次数大于等于$2$，我们就统计这个答案。这样我们可以用$O(n\sqrt{n})$的复杂度解决问题。

时间复杂度：$O(n\sqrt{n})$。

## 代码
Easy Version:
```
#include<stdio.h>
#define inf 1000000000
const int maxn=200005,maxk=105;
int n,maxx,cnt,ans;
int a[maxn],tot[maxk],sum[maxn],t[maxn*2];
inline int min(int a,int b){
	return a<b? a:b;
}
inline int max(int a,int b){
	return a>b? a:b;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		tot[a[i]]++;
	}
	for(int i=1;i<=100;i++){
		if(tot[i]==maxx)
			cnt++;
		if(tot[i]>maxx)
			cnt=1,maxx=tot[i];
	}
	if(cnt>1){
		printf("%d\n",n);
		return 0;
	}
	for(int i=1;i<=100;i++)
		if(tot[i]==maxx){
			maxx=i;
			break;
		}
	for(int i=1;i<=100;i++){
		for(int j=1;j<=n;j++)
			sum[j]=sum[j-1]+(a[j]==i? -1:(a[j]==maxx? 1:0));
		for(int j=-n;j<=n;j++)
			t[n+j]=inf;
		for(int j=1;j<=n;j++){
			ans=max(ans,j-t[n+sum[j]]+1);
			t[n+sum[j-1]]=min(t[n+sum[j-1]],j);
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

Hard Version
```
#include<stdio.h>
#include<math.h>
#include<vector>
#define inf 1000000000
using namespace std;
const int maxn=200005,maxt=505;
int n,maxx,cnt,ans,S,val;
int a[maxn],tot[maxn],sum[maxn],t[maxn*2],cnt1[maxn],cnt2[maxn];
vector<int>v;
inline void modify(int x,int v){
	cnt2[cnt1[x]]--;
	cnt1[x]+=v;
	cnt2[cnt1[x]]++;
}
int main(){
	scanf("%d",&n),S=sqrt(n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		tot[a[i]]++;
	}
	for(int i=1;i<=n;i++){
		if(tot[i]==maxx)
			cnt++;
		if(tot[i]>maxx)
			cnt=1,maxx=tot[i];
	}
	if(cnt>1){
		printf("%d\n",n);
		return 0;
	}
	for(int i=1;i<=n;i++){
		if(tot[i]==maxx)
			val=i;
		else if(tot[i]>S)		
			v.push_back(i);
	}
	for(int i=0;i<v.size();i++){
		int k=v[i];
		for(int j=1;j<=n;j++)
			sum[j]=sum[j-1]+(a[j]==k? -1:(a[j]==val? 1:0));
		for(int j=-n;j<=n;j++)
			t[n+j]=inf;
		for(int j=1;j<=n;j++){
			ans=max(ans,j-t[n+sum[j]]+1);
			t[n+sum[j-1]]=min(t[n+sum[j-1]],j);
		}
	}
	for(int i=1;i<=S;i++){
		for(int j=1;j<=n;j++)
			cnt1[j]=cnt2[j]=0;
		int l=1,r=0;
		while(r<n){
			r++,modify(a[r],1);
			while(cnt1[a[r]]>i)
				modify(a[l],-1),l++;
			if(cnt2[i]>=2)
				ans=max(ans,r-l+1);
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Flan (赞：2)

> 给你一个长度为 $n$ 的序列 $a_i$，求一个最长的子段，满足该段中出现次数最多的数不止一个。


分享一个奇怪的二分做法。

设当前判定的答案为 $len$，某段区间内 $i$ 的出现次数为 $c_i$。则以 $r$ 为结尾的某个长度不小于 $len$ 的区间满足条件，当且仅当：

- $[r - len +1, r]$ 的出现次数最多的数出现了 $f$ 次。记该数为 $x$。
- $\exists i\in[1,r-len+1]$ 使得 $[i,r]$ 内存在另一个数 $y$，满足对于 $[i,r]$  有 $c_y\ge c_x$。

我们只关心对于所有的区间 $[i,r]$ 和所有数 $y\neq x$，$c_y-c_x$ 的最大值。若这个最大值非负，则可以判定 $len$ 成立。

做一个前缀和数组 $s$，则上述条件可以转换为 $s(r,y)-s(r,x)-\min\limits_{i=1}^{r-len+1}(s(i-1,y)-s(i-1,x))\ge 0$。其中 $s(i-1,y)-s(i-1,x)$ 的最小值很容易维护，只需要逐个枚举 $y$，判定不等式成立性即可。

时间复杂度 $O(na\log n)$。

```cpp
#include <bits/stdc++.h>
const int MAXN = 2e5 + 19;
int n, a[MAXN], s[MAXN][101], min[101][101];
bool check(int len){
    memset(min, 0, sizeof min);
	for(int i = len; i <= n; ++i){
		for(int j = 1; j <= 100; ++j)
			min[j][a[i - len]] = std::min(min[j][a[i - len]], s[i - len][j] - s[i - len][a[i - len]]);
		int mx = std::max_element(s[i] + 1, s[i] + 101) - s[i];
		for(int j = 1; j <= 100; ++j)
			if(j != mx && s[i][j] - min[j][mx] >= s[i][mx])
				return 1;
	}
	return 0;
}
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i){
		scanf("%d", a + i),	++s[i][a[i]];
		for(int j = 1; j <= 100; ++j)
			s[i][j] += s[i - 1][j];
	}
	for(int i = 1; i <= 100; ++i)
		if(s[n][i] == n)
		    return puts("0"), 0;
	int l = 2, r = n;
	while(l < r){
		int mid = (l + r + 1) >> 1;
		check(mid) ? l = mid : r = mid - 1;
	}
	printf("%d\n", l);
	return 0;
}
```

---

## 作者：SunsetSamsara (赞：1)

## 题意

给定 $a_1,a_2,\cdots,a_n$，求最长的满足区间众数有至少两种的区间长度。如果不存在这样的区间，输出 $0$。

## 分析

### D1

首先，如果原序列可以成为答案，就取 $n$ 为最终结果。而对于其它的情况，答案序列的众数就只有一种，记为 $x$

然后，这里有一个结论：

+ 答案序列的多个众数中**一定包含** $x$。

证明：

对于一个好的序列的下标区间 $[l,r]$，如果 $x$ 不是其中出现次数最多的元素。那么，我们依次考虑原序列中的 $[l - 1, r], [l - 2, r], \cdots, [1, r], [1, r + 1], \cdots, [1, n]$ 这 $n + l - r$ 个下标区间。因为 $x$ 的数量在两个相邻区间中最多增加 $1$ 个，又因为它是整个序列里的众数，所以总有某一步后，$x$ 和答案区间中的其他众数的出现次数一样多。

接下来枚举可能成为与 $x$ 不同的众数 $y$，将问题转化成找到一个最长的、$x$ 与 $y$ 个数相同的子段。于是将 $x$ 堪为 $1$，$y$ 看为 $-1$，求前缀和，找到最远相同前缀和即可。

现在的时间复杂度是 $\Theta(100n)$，可过 D1

### D2

考虑 $x$ 的出现次数 $k$，并对 $k$ 进行根号分治：

1. $k \ge \sqrt n$

可能成为 $y$ 的数少于 $\sqrt n$ 个，使用 D1 做法，时间复杂度 $\Theta(n \sqrt n)$

2. $k \le \sqrt n$

枚举区间内 $x$ 出现次数 $k$ 与答案区间右端点 $r$，对于每一个 $r$，记录最小的使得 $[l,r]$ 内所有数出现次数都 $\le k$ 的 $l$。显然，随着 $r$ 的增加，$l$ 单调递增。维护每个数的出现次数，直接双指针维护即可，复杂度 $\Theta(n\sqrt n)$

## 代码

出于简洁考虑，只放 D2 代码

```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <math.h>
#define lld long long
#define cst(x) const x
#define cref(x) const x&
#define reg(x) register x
using namespace std;
#ifdef ONLINE_JUDGE
#define getchar() getchar_unlocked()
#define putchar(ch) putchar_unlocked(ch)
#endif
cst(int) prec=6;
template<class T>inline void writeInt(reg(T)x){x=(x<0?(putchar('-'),-x):x);reg(char)c=0;static char s[50];do{s[++c]=x%10,x/=10;}while(x);for(reg(int)i=c;i;--i)putchar(s[i]^48);}
template<class T>inline void readInt(reg(T&)x){x=0;reg(T)fl=1;reg(char)ch;for(;(ch=getchar(),ch=='-'&&(fl=-1),ch)<48||ch>57;);for(x=ch&15;(ch=getchar())>=48&&ch<=57;x=(x<<3)+(x<<1)+(ch&15));x*=fl;}
template<class T>inline void writeFloat(reg(T)x){x=(x<0?(putchar('-'),-x):x);reg(T)cpy=x,add=0.5;for(reg(int)i=prec;i;--i)add/=10;writeInt((lld)(cpy+=add)),putchar('.'),cpy-=(lld)cpy;for(reg(int)i=prec;i;--i)putchar((int)(cpy=(cpy-(int)cpy)*10)+'0');}
template<class T>inline void readFloat(reg(T&)x){x=0;reg(char)ch;reg(T)fl=1,val=0.1;for(;(ch=getchar(),ch=='-'&&(fl=-1),ch)<48||ch>57;);for(x=ch&15;((ch=getchar())>=48&&ch<=57);)x=x*10+(ch&15);if(ch=='.')for(;((ch=getchar())>=48&&ch<=57);val/=10)x+=(ch&15)*val;x*=fl;}
inline void writeStr(reg(cst(char*))str){for(reg(cst(char*))p=str;*p;++p)putchar(*p);}
inline void readStr(reg(char*)str){reg(char*)p=str;for(;(*p=getchar())!=' '&&*p!='\n'&&~*p;++p);*p=0;}

const int N = 200010, M = 450;
static int n, a[N], ans;
static int sum[N], pre[N << 1];
static int cnt[N];
int main() {
	readInt(n);
	for (reg(int) i = 1; i <= n; ++ i) readInt(a[i]), ++ cnt[a[i]];
	reg(int) sq = sqrt(n), mxval = 1;
	for (reg(int) i = 2; i <= n; ++ i)
		if (cnt[a[i]] > cnt[mxval]) mxval = a[i];
	for (reg(int) i = 1; i <= n; ++ i)
		if (a[i] != mxval && cnt[a[i]] == cnt[mxval]) {
			writeInt(n);
			return 0;
		}
	// k >= sqrt(n)
	for (reg(int) y = 1, i; y <= n; ++ y)
		if (cnt[y] >= sq && y != mxval) {
			memset(pre, 0, sizeof(pre));
			for (i = 1; i <= n; ++ i) {
				sum[i] = sum[i - 1] + (a[i] == mxval ? 1 : (a[i] == y ? -1 : 0));
				if (!pre[sum[i] + N] && sum[i]) pre[sum[i] + N] = i;
				else ans = max(ans, i - pre[sum[i] + N]);
			}
		}
	// k < sqrt(n)
	for (reg(int) c = 1, ccnt, l, r; c <= sq; ++ c)
		for (memset(cnt, 0, sizeof(cnt)), l = r = 1, ccnt = 0; r <= n; ++ r) {
			if ((++ cnt[a[r]]) == c) ++ ccnt;
			for (; l <= r && cnt[a[r]] > c; (cnt[a[l]] == c) && (-- ccnt), -- cnt[a[l ++]]);
			if (ccnt >= 2) ans = max(ans, r - l + 1);
		}
	writeInt(ans);
}
```

---

## 作者：qfpjm (赞：0)

# 题解

- 题意十分好理解，这里就不再赘述。

- 首先，我们必须要知道一个结论：**最长的众数不唯一的子序列一定包含整个序列的众数**。证明的话题解区有很多，而且很好理解，这里就不再证明了。

- 那么我们可以将问题转化为：**求最长的子序列，其中至少有一个众数有与整个序列的众数在子序列中的出现次数相同**。虽然可能有些难理解，但是这是这题的重点，理解了这个，后面的就是写实现方法而已了。

- 讲一下实现方法：首先肯定是求出众数，然后判断一下是否有多个。如果没有，那么就枚举一下另一个众数，然后算最长的子序列即可。

- 求最长子序列，因为在这个子序列中，**整个序列的众数**和**枚举的众数**出现次数应该是一样的，那么我们可以把这个整个序列中的数分为三类：等于**整个序列的众数**的数、等于**枚举的众数**的数、其它数，分别用 $1,-1,0$ 赋值，那么最后要统计的是**最长的和为 $0$ 的子序列**。

- 时间复杂度：$O( \max {a_i}\times n)$。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, a[200005], tot[105], pre[200005], mp[400005];

int main()
{
	cin >> n;
	for (int i = 1 ; i <= n ; i ++)
	{
		cin >> a[i];
		tot[a[i]] ++;
	}
	int cnt = 0, maxtot = 0;
	for (int i = 1 ; i <= 100 ; i ++)
	{
		if (tot[i] == maxtot)
		{
			cnt ++;
		}
		else if (tot[i] > maxtot)
		{
			cnt = 1;
			maxtot = tot[i];
		}
	}
	if (cnt > 1)
	{
		cout << n;
		return 0;
	}
	int maxa = 0;
	for (int i = 1 ; i <= 100 ; i ++)
	{
		if (tot[i] == maxtot)
		{
			maxa = i;
			break;
		}
	}
	int ans = 0;
	for (int i = 1 ; i <= 100 ; i ++)
	{
		for (int j = 1 ; j <= n ; j ++)
		{
			pre[j] = pre[j - 1] + (a[j] == i ? -1 : (a[j] == maxa ? 1 : 0));
		}
		for (int j = -n ; j <= n ; j ++)
		{
			mp[n + j] = 1000000000;
		}
		for (int j = 1 ; j <= n ; j ++)
		{
			ans = max(ans, j - mp[n + pre[j]] + 1);
			mp[n + pre[j - 1]] = min(mp[n + pre[j - 1]], j);
		}
	}
	cout << ans;
}
```


---

## 作者：UKE_Automation (赞：0)

### G CF1446D Frequency Problem

[$\text{Easy Version}$](https://codeforces.com/problemset/problem/1446/D1)，[$\text{Hard Version}$](https://codeforces.com/problemset/problem/1446/D2)

首先先排除全局众数有两个的情况，然后需要观察出一个比较强的性质：一定存在一种最优答案区间，满足区间内有一个众数是全局众数。

> 证明考虑反证，如果最优答案区间不包含全局众数，则我们可以考虑扩展这个区间。令该区间中除全局众数外众数的出现次数为 $a$，该区间中众数的出现次数是 $b$，初始时有 $a>b$，而当区间扩展到全局时又有 $a<b$，所以中间必存在一个状态满足 $a=b$，此时这个解比刚刚的解更优，矛盾。

有了这个性质我们不难想到去枚举另一个众数 $x$，我们现在需要找到一个区间满足全局众数和 $x$ 出现次数相等。不难想到给全局众数的位置上赋值 $1$，$x$ 位置上赋值 $-1$，则根据前缀和即可判断出最长的区间。不必担心这个区间中有出现次数更多的数，因为这样一定是更优解。这样做的复杂度是 $O(nV)$ 的，可以通过简单版。

考虑到在本题中有一个关系：数字的出现次数 $\times$ 出现次数为该次数的数字个数 $\le n$，所以考虑根号分治。对于出现次数 $>\sqrt n$ 的数字，个数不超过 $\sqrt n$，此时利用刚才的方法做，复杂度 $O(n\sqrt n)$；而对于出现次数 $\le \sqrt n$ 的数字，考虑枚举出现次数，开桶用双指针维护合法区间即可。复杂度依然是 $O(n\sqrt n)$ 的。

综上我们可以在 $O(n\sqrt n)$ 的复杂度内解决这个问题。

```cpp
#include <bits/stdc++.h>
#define il inline

using namespace std;

const int Maxn = 2e5 + 5;
const int Inf = 2e9;
template <typename T> il void chkmax(T &x, T y) {x = (x >= y ? x : y);}
template <typename T> il void chkmin(T &x, T y) {x = (x <= y ? x : y);}
template <typename T>
il void read(T &x) {
	x = 0; char ch = getchar(); bool flg = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) flg = (ch == '-');
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	flg ? x = -x : 0;
}
template <typename T>
il void write(T x, bool typ = 1) {
	static short Stk[50], Top = 0;
	x < 0 ? putchar('-'), x = -x : 0;
	do Stk[++Top] = x % 10, x /= 10; while(x);
	while(Top) putchar(Stk[Top--] | 48);
	typ ? putchar('\n') : putchar(' ');
}
il void IOS() {ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);}
il void File() {freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);}
bool Beg;

int n, a[Maxn];
int cnt[Maxn], num;
int val[Maxn], sum[Maxn], pos[Maxn << 1];
int t[Maxn];

int mx;
void add(int x) {
	t[cnt[a[x]]]--;
	cnt[a[x]]++; 
	t[cnt[a[x]]]++;
	if(cnt[a[x]] > mx) mx++;
}

void del(int x) {
	t[cnt[a[x]]]--;
	cnt[a[x]]--; 
	t[cnt[a[x]]]++;
	if(!t[mx]) mx--;
}

bool End;
il void Usd() {cerr << (&Beg - &End) / 1024.0 / 1024.0 << "MB " << (double)clock() * 1000.0 / CLOCKS_PER_SEC << "ms\n"; }
int main() {
	read(n);
	for(int i = 1; i <= n; i++) {
		read(a[i]);
		cnt[a[i]]++;
		if(cnt[a[i]] > cnt[num]) num = a[i];
	}
	int tot = 0;
	for(int i = 1; i <= n; i++) {
		if(cnt[i] == cnt[num]) tot++;
	}
	if(tot >= 2) {write(n); return 0;}
    int B = sqrt(n);
    for(int i = 1; i <= n; i++) if(a[i] == num) val[i] = 1;
    int ans = 0;
	for(int i = 1; i <= n; i++) {
		if(cnt[i] <= B) continue ;
		for(int j = 1; j <= n; j++) {
			if(a[j] == i) val[j] = -1;
			else if(a[j] == num) val[j] = 1;
			else val[j] = 0;
			sum[j] = sum[j - 1] + val[j];
		}
		for(int j = 0; j <= (n << 1); j++) pos[j] = Inf;
		for(int j = 0; j <= n; j++) {
			if(pos[sum[j] + n] == Inf) pos[sum[j] + n] = j;
			else chkmax(ans, j - pos[sum[j] + n]);
		}
	} 
	for(int i = 1; i <= B; i++) {
		for(int j = 1; j <= n; j++) cnt[j] = t[j] = 0; mx = 0;
		for(int r = 1, l = 1; r <= n; r++) {
			add(r);
			while(mx > i) del(l++);
			if(mx == i && t[mx] >= 2) chkmax(ans, r - l + 1);
		}
	}
	write(ans);
	Usd();
	return 0;
}
```

---

## 作者：freoepn (赞：0)

注意到一定存在一个最优区间是的整个序列的众数 $x$ 是该区间的众数(否则可以往两边拓展获得更优区间)，对于出现次数 $> \sqrt{n}$ 的元素 $y$ ，可以用前缀和维护出 $x$ 和 $y$ 共同出现的最大区间，这样的 $y$ 顶多有 $\sqrt{n}$ 个，否则枚举 $x$ 在区间中的出现次数 $z$ ，用双指针维护有 $z$ 个 $x$ 的区间，判断是否区间中有出现次数大于 $z$ 的元素即可



```cpp
#include <bits/stdc++.h>
using namespace std;
const int kMaxN = 200005, sq = 450;
int a[kMaxN];
int t[kMaxN];
int n;
int sum[kMaxN];
int p[2 * kMaxN];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0),cout.tie(0);
  cin >> n;
  int maxn = 0;
  vector<int> v;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    t[a[i]]++;
    if (t[a[i]] > maxn) {
      maxn = t[a[i]];
      v.clear();
      v.push_back(a[i]);
    } else if (t[a[i]] == maxn) {
      v.push_back(a[i]);
    }
  }
  if (v.size() > 1) {
    cout << n;
    return 0;
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (i != v[0] && t[i] >= sq) {
      for (int j = 0; j <= 2 * n + 1; j++) {
        p[j] = -1;
      }
      for (int j = 1; j <= n; j++) {
        if (a[j] == v[0]) {
          sum[j] = 1;
        } else if (a[j] == i) {
          sum[j] = -1;
        } else {
          sum[j] = 0;
        }
        sum[j] += sum[j - 1];
      }
      p[n] = 0;
      for (int j = 1; j <= n; j++) {
        if (p[sum[j] + n] == -1) {
          p[sum[j] + n] = j;
        } else {
          ans = max(ans, j - p[sum[j] + n]);
        }
      }
    }
  }
  for (int i = 1; i < sq; i++) {
    int p = 1;
    int sum = 0, e = 0;
    for (int j = 0; j <= n; j++) {
      t[j] = 0;
    }
    for (int r = 1; r <= n; r++) {
      if (a[r] == v[0]) {
        sum++;
      } else {
        t[a[r]]++;
        if (t[a[r]] == i) {
          e++;
        }
      }
      while (sum > i) {
        if (a[p] == v[0]) {
          sum--;
        } else {
          t[a[p]]--;
          if (t[a[p]] == i - 1) {
            e--;
          }
        }
        p++;
      }
      if (sum == i && e >= 1) {
        ans = max(ans, r - p + 1);
      }
    }
  }
  cout <<ans;
  return 0;
}
```

---

## 作者：TonyYin (赞：0)

[更好的阅读体验](https://www.tonyyin.top/2021/12/cf1446d2/)

直接传D2的题解上来了。

**D1做法参考：$\operatorname{C} > \sqrt{n}$ 的情况，第二种情况对解决D1没有帮助。**

这种做法在D1中，时间复杂度为 $\mathcal{O}(n\times \operatorname{maxa})$.

## 题意

给出一个序列 $a_1, a_2\cdots, a_n$，求最长的子段，使得其中有至少两个出现次数最多的元素。

输出子段的长度，$1\leq n\leq 2\times 10^5$.

## 题解

#### 引理及证明

> 众数：一个序列中出现次数最多的数，可以有多个。

首先有一个关于众数的结论：**答案子段的众数集合，一定包含原序列的众数。**

可以通过**反证法**来证明：

记 $x$ 是原序列的众数，**假设存在**子段 $a_l, a_{l+1}, \cdots, a_r$ 是题目所求的最长子段，且子段的众数不包含 $x$.

根据众数的定义，在 $a_{[1, l-1]}$ 和 $a_{[r+1, n]}$ 中一定还包含 $x$。不妨设左侧包含 $x$，即 $\exists a_p=x, p\in[1, l-1]$.

**考虑将子段 $a_{[l, r]}$ 向两侧扩展，把 $a_p$ 包含进去**，这样使子段长度变大，下面说明一定存在方案可以包含 $a_p$.

把 $a_{[l, r]}$ 扩展为 $a_{[p,r]}$ 后，

- 若其众数的出现次数**不变**，则 $a_{[p,r]}$ 即为更优答案。
- 若其众数的出现次数**增加**，那么我们继续扩展，使更多的 $x$ 被包含进去。由于 $x$ 是整个序列中出现次数最多的数，所以把 $x$ 一个一个加进去，最后就变成了上面的情况，可以满足条件。

因此，我们总可以找到一个比 $a_{[l,r]}$ 更优的答案，**假设不成立**。

所以结论成立。

#### 思路

先找到序列 $a$ 的众数 $x$，若存在多个众数，则答案为 $n$.

对答案中**众数的出现次数**进行根号分治，分别采用不同的方法处理。

设 $\operatorname{C}$ 为**答案子段的众数的出现次数**，$x,y$ 表示答案子段的众数，$\operatorname{cnt_i}$ 为值 $i$ 在序列 $a$ 中的出现次数。

下面进行分类讨论。

#### $\operatorname{C} > \sqrt{n}$ 的情况

由于答案子段一定包含众数 $x$，且 $\operatorname{C}>\sqrt{n}$，所以 $y$ 也满足 $\operatorname{cnt}_y>\sqrt{n}$.

显然，满足这个条件的 $y$ 最多有 $\sqrt{n}$ 个，考虑枚举 $y$。

只需在 $\mathcal{O}(n)$ 的复杂度内**求出：以 $(x,y)$ 作为众数的最大子段长度**。

此时问题只与 $x,y$ 这两个值有关，需要用到一个常见套路，**让 $x$ 的权值为 $1$，$y$ 的权值为 $-1$，其余为 $0$**.

只需在新序列中找：数值和为 $0$ 的最长子段。

对新数列维护前缀和 $s_i$，子段 $[l,r]$ 的数值和为 $0$ 等价于：$s_r=s_{l-1}$，只需记录每个 $s_i$ 的最早出现位置即可。

```cpp
// 1. 答案区间中众数的出现次数 > sqrt(n)，枚举所有可行的数值check
for(int i = 1; i <= n; i++) if(cnt[i] >= Sqrt && i != mxval) {
    memset(L, 0, sizeof(L)); L[0 + N] = 0;
    for(int j = 1; j <= n; j++) {
        s[j] = s[j - 1] + (a[j] == mxval ? 1 : (a[j] == i ? -1 : 0));
        if(!L[s[j] + N] && s[j]) L[s[j] + N] = j; //注意这里下标可能为负，所以要都加上N
        else ans = max(ans, j - L[s[j] + N]);
    }
}

```

注意 $s_i\in[-n, n]$，记录最早出现位置的数组，下标需要整体 $i\leftarrow i+n$.

#### $\operatorname{C} \leq \sqrt{n}$ 的情况

考虑枚举 $\operatorname{C}$，只需在 $\mathcal{O}(n)$ 的复杂度内**求出：众数出现次数为 $\operatorname{C}$ 的最大子段**。

这可以用**双指针**解决，**细节有点多**。

```cpp
// 2. 答案区间中众数的出现次数 <= sqrt(n)，枚举所有可行的答案，双指针判断是否合法
for(int C = 1; C <= Sqrt; C++) {
    memset(cnt, 0, sizeof(cnt));
    for(int l = 1, r = 1, C_cnt = 0; r <= n; r++) {
        cnt[a[r]]++; if(cnt[a[r]] == C) C_cnt++;
        while(l <= r && cnt[a[r]] > C) {
            if(cnt[a[l]] == C) C_cnt--;
            cnt[a[l++]]--;
        }
        if(C_cnt >= 2) ans = max(ans, r - l + 1);
    }
}
```

在上面的代码中，$\operatorname{C_{cnt}}$ 代表出现次数为 $\operatorname{C}$ 的数的个数，动态维护桶。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 10, N = 2e5;
int n, a[MAXN], ans;
int L[MAXN << 1], s[MAXN]; //情况一，L[i]为前缀和i第一次出现的下标，s[i]为前缀和
int cnt[MAXN]; //情况2，对于目前的尺取区间，cnt是对a[]的桶
int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	int Sqrt = (int)(sqrt(n));
	for(int i = 1; i <= n; i++) cin >> a[i], cnt[a[i]]++;
	int mxcnt = 0, mxval = -1;
	for(int i = 1; i <= n; i++) {
		if(cnt[a[i]] > mxcnt) mxcnt = cnt[a[i]], mxval = a[i];
		else if(cnt[a[i]] == mxcnt && a[i] != mxval) mxval = n + 1;
	}
	if(mxval == n + 1) { cout << n << endl; return 0; } //若众数有俩，直接输出n
//	1. 答案区间中众数的出现次数 > sqrt(n)，枚举所有可行的数值check
	for(int i = 1; i <= n; i++) if(cnt[i] >= Sqrt && i != mxval) {
		memset(L, 0, sizeof(L)); L[0 + N] = 0;
		for(int j = 1; j <= n; j++) {
			s[j] = s[j - 1] + (a[j] == mxval ? 1 : (a[j] == i ? -1 : 0));
			if(!L[s[j] + N] && s[j]) L[s[j] + N] = j; //注意这里下标可能为负，所以要都加上N
			else ans = max(ans, j - L[s[j] + N]);
		}
	}
//	2. 答案区间中众数的出现次数 <= sqrt(n)，枚举所有可行的答案，双指针判断是否合法
	for(int C = 1; C <= Sqrt; C++) {
		memset(cnt, 0, sizeof(cnt));
		for(int l = 1, r = 1, C_cnt = 0; r <= n; r++) {
			cnt[a[r]]++; if(cnt[a[r]] == C) C_cnt++;
			while(l <= r && cnt[a[r]] > C) {
				if(cnt[a[l]] == C) C_cnt--;
				cnt[a[l++]]--;
			}
			if(C_cnt >= 2) ans = max(ans, r - l + 1);
		}
	}
	cout << ans << endl;
	return 0;
}
```



---

