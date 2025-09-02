# Beautiful Numbers

## 题目描述

### 题意简述

你得到了正整数 $1$ 到 $n$ 的一个排列 $p=[p_1,p_2,···,p_n]$。

我们称数字 $m(1 \leq m \leq n)$ 是美丽的，当且仅当存在两个正整数 $l,r(1\leq l\leq r \leq n)$， 使得 $p_l,p_{l+1},\cdots,p_r$ 是正整数 $1$ 到 $m$ 的一个排列。

对于所有的 $m$，您需要求出其是否是美丽的。

## 样例 #1

### 输入

```
3
6
4 5 1 3 2 6
5
5 3 1 2 4
4
1 4 3 2
```

### 输出

```
101011
11111
1001
```

# 题解

## 作者：_JF_ (赞：1)

## Beautiful Numbers 

思维题吧？

题目大意：给出 $1$ 到 $n$ 的任意一个排列，对于每个 $i$ $(1\le i\le n)$，是否有在这个序列里面有 $1$ 到 $i$ 的任意一个排列。

先考虑这样的做法，显然如果包含 $1$ 到 $i$ 的某一个排列的话，在原序列对应的这一段的下标显然是连续的，考虑用 $set$ 维护 $1$ 到 $i$ 的某一个排列的下标序列。每次插入一个数就判断他的左边和右边的位置差是不是 $1$ 即可。时间复杂度为 $O(n\log n)$。

接下来我们考虑使用双指针，也就是用 $l,r$ 维护 $1$ 到 $i$ 的任意排列的数字中下标最大或者最小的某个数的位置。原因是构成 $[1,i]$ 的任意排列，所以在 $[l,r]$ 中的数必然都要是 $[1,i]$ 的数才可以。

考虑用一个变量 $sum$ 维护 $[l,r]$ 中和 $[1,i]$ 不同的数，分情况讨论：

- 如果当前的数出现的位置超过了 $l$ 或者 $r$，我们就更新 $l$ 或 $r$，同时给 $sum$ 加上跳过的位置，由于 $[1,i-1]$ 的位置我们在以前维护过了，所以跳过的位置必然没有 $[1,i-1]$ 的任何数。

- 如果当前的位置在 $[l,r]$ 之间，那么 $sum$ 减一，原因显然，$[l,r]$ 中多了一个出现 $[1,i]$ 的数字。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
int a[N],t[N];
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n,l,r,lmax,rmax;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i],t[a[i]]=i;
			if(a[i]==1)
				lmax=i,rmax=i;
		}
		int sum=0;
		cout<<1;
		for(int i=2;i<=n;i++)
		{
			if(t[i]>rmax)	sum+=(t[i]-rmax-1),rmax=t[i];
			else if(t[i]<lmax)	sum+=(lmax-t[i]-1),lmax=t[i];
			else sum--;
			if(sum==0)
				cout<<1;
			else
				cout<<0;
		}
		cout<<endl;
	}
}
```


---

## 作者：_maojun_ (赞：1)

个人认为题解区里面题解的实现方法比较的迷惑。

---

其实双指针不用一个个挪动，直接对于新的位置取 $\min$ or $\max$ 即可。

具体地说，如果现在在判断数字 $m$ 是否为美丽，设 $m$ 在 $pos_m$ 位置出现，令 $l\gets\min(l,pos_m),r\gets\max(r,pos_m)$。然后若 $r-l+1=m$ 则 $m$ 是美丽的。

很久以前写的代码。

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;

const int MAXN=2e5+5;
int n,pos[MAXN];
bool ans[MAXN];

void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		pos[x]=i;ans[i]=false;				// 记录 pos[x] 
	}
	ans[1]=true;
	for(int l=pos[1],r=pos[1],i=2;i<=n;i++){
		l=min(l,pos[i]),r=max(r,pos[i]);	// 更新双指针 
		if(r-l+1==i)ans[i]=true;
	}
	for(int i=1;i<=n;i++)printf("%d",ans[i]);
	printf("\n");
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：TPJX (赞：0)

### 题目分析
可以通过跟踪每个数字在排列中的最左和最右出现位置，然后对每个可能的长度 $m$，判断从 $1$ 到 $m$ 的数字是否能形成连续的区间。如果能形成连续的区间，说明这个长度 $m$ 是美丽的。这样可以直接根据区间的起始和结束位置来快速判断每个长度是否符合条件，从而得出每个 $m$ 是否美丽的结果。

这种方法的效率比较高，时间复杂度大约为 $O(n)$，因为每个数只需要更新一次位置，之后只进行一次遍历来检查每个 $m$ 是否是美丽的。这对于大数据量的情况非常适用。
### C++ 代码
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 2e5 + 10;  
int t, n, p[N], l[N], r[N];  

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            l[i] = n + 1;
            r[i] = 0;
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &p[i]);
            l[p[i]] = min(l[p[i]], i);  
            r[p[i]] = max(r[p[i]], i);
        }
        int max_r = 0;
        int min_l = n + 1;
        bool flag = true;
        for (int m = 1; m <= n; ++m) {
            max_r = max(max_r, r[m]);
            min_l = min(min_l, l[m]); 
            if (max_r - min_l + 1 == m) printf("1");
            else printf("0");
        }
        printf("\n");
    }
    return 0;
}

```

---

## 作者：skyskyCCC (赞：0)

## 前言。
这道题的描述很清晰，是一个比较基础的暴力优化题。
## 分析。
最暴力的方法，不难想到，对于数 $m$ 可以从 $1$ 到 $m$ 的数的位置枚举一遍，如果最右边的数 $r$ 和最左边的数 $l$ 满足 $r-l+1=m$ 则说明所有数所覆盖的面积刚好是 $m$ 并且不会有其它的数。这样就能直接暴力地解决了。但是我们如果在每一个 $i$ 上都进行一遍查询，在 $t$ 和 $n$ 的数据范围内会超时，所以考虑优化。

我们注意到在求第 $m+1$ 个数的时候，事实上在前面求 $m$ 的过程中的范围可以被 $m+1$ 利用。这意味着，我们在判断第 $m+1$ 个数的时候，我们可以在第 $m$ 个数的基础上进行扩充，仅仅只对 $m+1$ 这个数更新范围，然后在被更新的范围内查看是否合法即可。时间复杂度很显然更优。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int t,n,p[200005];
int tp[200005];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for (int i=1;i<=n;i++){
			cin>>p[i];
			tp[p[i]]=i;//记录下标。 
		}
		int l=tp[1],r=tp[1];
		for (int i=1;i<=n;i++){
			l=min(l,tp[i]);
			r=max(r,tp[i]);
			if(r-l+1==i){
				cout<<"1";
			}
			else cout<<"0";
		}
		cout<<"\n";
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：a1ioua (赞：0)

~~喜提最劣解。~~

------------
我们可以采用 [双指针（two-pointer）](https://zhuanlan.zhihu.com/p/71643340) 的 “对撞指针”（说是“对撞”，其实越扩展越远，只是分在这一类） 来解决此问题。

起初让 $l,r$ 都定义为最先出现的 $1$ 的位置。对于每一个 $m$，我们可以定义双指针 $l,r$，然后 $l$ 向左移动，$r$ 向右移动，直到超出范围。

一些不用顾虑的东西：由于 $[1,n]$ 的每个数都只会出现 1 次，所以：$i$ 的 $l,r$ 可以从 $i-1$ 的 $l,r$ 扩展而来，所以 $l,r$ 都定义为最先出现的 $1$ 的位置在最开始时算一次就行。
```c
#include <stdio.h>
int t, n, p[200005];
signed solve() {
    scanf("%d", &t);
	while (t--) {
	    scanf("%d", &n);
	    for (int i = 1; i <= n; i++) scanf("%d", p + i);
	    int l, r;
	    for (int i = 1; i <= n; i++)
	        if (p[i] == 1) { l = r = i; break; }
	        printf("1");//m = 1 时显然成立。
	    for (int i = 2; i <= n; i++) {
	        while(l > 1 && p[l - 1] <= i) l--;
            while(r < n && p[r + 1] <= i) r++;
            printf("%d", r - l + 1 == i);//因为题目要求输出 01 序列，所以我们可以偷一个小懒。
	    }
	    putchar('\n');
	}
	return 0;
}
signed main() { return solve(); }
```

---

## 作者：Eason_AC (赞：0)

## Content
给定一个 $1\sim n$ 的排列，请求出对于 $1\leqslant m\leqslant n$，是否存在一个区间满足这个区间是一个 $1\sim m$ 的排列。

**数据范围：$1\leqslant n,\sum n\leqslant 2\times 10^5$。**
## Solution
看到本题的唯一一篇主席树+二分的题解里面并没有说最巧妙的方法是什么，那我就来给大家讲讲吧qwq。

对于每一个 $m$，我们不妨弄个双指针 $l,r$，然后从 $1$ 的位置开始将 $l$ 向左移动，将 $r$ 向右移动，直到碰到某个位置上的数 $>m$ 为止，这样可以保证这个区间的最大值是 $1$，最小值是 $m$，然后只需要判断是否有 $r-l+1=m$，即区间长度是 $m$ 即可。
## Code
```cpp
int a[200007];

int main() {
    MT {
        int n = Rint;
        F(int, i, 1, n) a[i] = Rint;
        int l, r;
        F(int, i, 1, n) if(a[i] == 1) {l = r = i; break;}
        printf("1");
        F(int, i, 2, n) {
            while(l > 1 && a[l - 1] <= i) l--;
            while(r < n && a[r + 1] <= i) r++;
            write(r - l + 1 == i);
        }
        puts("");
    }
}
```

---

## 作者：kma_093 (赞：0)

~~水题无人系列，赶紧水一发~~

不是最巧妙的做法，但是比较好想qwq

---

## 题意

给一个长度为$n$的排列$P$，求对于$1$ 到 $n$中的每个数$m$，是否能找到一段长度为$m$的区间使得区间内的数是一个$1$到$m$的排列。

输出一个$01$串，其中第$i$位表示是否能找到一段长度为$i$的区间使得区间内的数是一个$1 - i$的排列

$n \leq 2e5$

## 分析

对于某个数，如果能找到一段区间使它合法，那么这个区间一定是唯一且连续的

考虑从小到大对于每个数，查找它的位置，并维护当前所找到的位置的最小值和最大值，即维护一下当前区间的左端点和右端点

当这个区间连续时，即$Max - Min + 1 = m$时，当前$m$是合法的

于是现在变成了在一个无序的排列上查找一个数的位置，主席树+二分即可

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() {
	int cnt = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {if (c == '-') f = -f; c = getchar();}
	while (isdigit(c)) {cnt = (cnt << 3) + (cnt << 1) + (c ^ 48); c = getchar();}
	return cnt * f;
}
const int N = 200000 + 10;
int T, n, a[N], L, R, p;
int cur, rt[N], ls[N * 20], rs[N * 20], val[N * 20];
void modify(int &x, int l, int r, int lst, int pos) {
	x = ++cur;
	ls[x] = ls[lst], rs[x] = rs[lst], val[x] = val[lst] + 1;
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (pos <= mid) modify(ls[x], l, mid, ls[lst], pos);
	else modify(rs[x], mid + 1, r, rs[lst], pos);
}
int query(int x, int l, int r, int pos) {
	if (!x) return 0; if (l == r) return val[x];
	int mid = (l + r) >> 1;
	if (pos <= mid) return query(ls[x], l, mid, pos);
	else return query(rs[x], mid + 1, r, pos);
}
void clear() {
	for (register int i = 1; i <= cur; ++i) ls[i] = rs[i] = val[i] = 0;
	memset(rt, 0, sizeof rt);
	cur = 0; L = n + 1, R = 0;
}
int binary(int d) {
	int l = 1, r = n;
	int mid = (l + r) >> 1;
	while (l < r) {
		if (!query(rt[mid], 1, n, d)) l = mid + 1;
		else r = mid;
		mid = (l + r) >> 1;
	} return l;
}
int main() {
//	freopen("1.in", "r", stdin);
	T = read();
	while (T--) {
		n = read();
		clear();
		for (register int i = 1; i <= n; ++i) a[i] = read(), modify(rt[i], 1, n, rt[i - 1], a[i]);
		for (register int i = 1; i <= n; ++i) {
			p = binary(i);
			if (p < L) L = p;
			if (p > R) R = p;
			if (R - L + 1 == i) printf("1"); else printf("0");
		} puts("");
	}
	return 0;
}
```

---

