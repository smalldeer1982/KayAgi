# Thwarting Demonstrations

## 题目描述

It is dark times in Berland. Berlyand opposition, funded from a neighboring state, has organized a demonstration in Berland capital Bertown. Through the work of intelligence we know that the demonstrations are planned to last for $ k $ days.

Fortunately, Berland has a special police unit, which can save the country. It has exactly $ n $ soldiers numbered from $ 1 $ to $ n $ . Berland general, the commander of the detachment, must schedule the detachment's work in these difficult $ k $ days. In each of these days, the general must send a certain number of police officers to disperse riots. Since the detachment is large and the general is not very smart, he can only select a set of all soldiers numbered from $ l $ to $ r $ , inclusive, where $ l $ and $ r $ are selected arbitrarily.

Now the general has exactly two problems. First, he cannot send the same group twice — then soldiers get bored and they rebel. Second, not all soldiers are equally reliable. Every soldier has a reliability of $ a_{i} $ . The reliability of the detachment is counted as the sum of reliabilities of soldiers in it. The reliability of a single soldier can be negative, then when you include him in the detachment, he will only spoil things. The general is distinguished by his great greed and shortsightedness, so each day he sends to the dissolution the most reliable group of soldiers possible (that is, of all the groups that have not been sent yet).

The Berland Government has decided to know what would be the minimum reliability of the detachment, sent to disperse the demonstrations during these $ k $ days. The general himself can not cope with such a difficult task. Help him to not embarrass himself in front of his superiors!

## 样例 #1

### 输入

```
3 4
1 4 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 6
2 -1 2 -1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
8 10
1 -2 3 -4 5 -6 7 -8
```

### 输出

```
2
```

# 题解

## 作者：_segmenttree (赞：0)

## 思路

看到这些第 $k$ 大的，我们自然考虑二分。接下来问题转换成快速求出所有大于等于 $x$ 的区间，由于区间是连续的，其实就是求两个前缀和使其差大于等于 $x$ 。对于每一个 $i$ ，我们就加所有小于等于 $s[i]-x$ 的个数和他自己吗，然后再将他加入。这个操作其实就是单点修改，区间求和，用线段树或树状数组解决。数据范围比较大，离散化一下就好了

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a[100010],b[100010],t[100010],c[100010],m;
int lb(int x) {
	return x&(-x);
}
void tj(int x,int z) {
	while(x<=m) {
		t[x]+=z;
		x+=lb(x);
	}
}
int qh(int x) {
	int sum=0;
	while(x) {
		sum+=t[x];
		x-=lb(x);
	}
	return sum;
}
bool check(int x) {
	int sum=0;
	for(int i=1;i<=n;i++) 
		if(c[i]>=x) sum++;  
	for(int i=1;i<=n;i++) {
		int jl=upper_bound(a+1,a+m+1,c[i]-x)-a-1;
		sum+=qh(jl);
		tj(b[i],1);
	}
	memset(t,0,sizeof(t));
	return sum>=k;
}
signed main() {
	cin>>n>>k;
	for(int i=1;i<=n;i++) {
	    scanf("%lld",&a[i]);
	    a[i]+=a[i-1];
		c[i]=a[i];
	}
	sort(a+1,a+n+1);
	m=unique(a+1,a+n+1)-a-1;
	for(int i=1;i<=n;i++) 
	    b[i]=lower_bound(a+1,a+m+1,c[i])-a;
	int l=-1e15,r=1e15,ans;
	while(l<=r) {
		int mid=(l+r)/2;
		if(check(mid)) l=mid+1,ans=mid;
		else r=mid-1;
	} 
	cout<<ans;
	return 0;
}

```

---

## 作者：johnsmith0x3f (赞：0)

## 0x00 [Outline](https://codeforces.com/problemset/problem/191/E)

给定 $\{ a_n \} \ (n \leqslant 10^5)$ 和 $k \ (\leqslant \frac {n(n+1)} 2)$，求 $a$ 序列所有子区间和的第 $k$ 大值。

## 0x01

不难想到二分答案，判断是否为第 $k$ 大值。

枚举值为 $x$，则需求不小于 $x$ 的区间和个数，考虑转化为求两前缀和之差，对某个前缀和 $sum$，我们要求出不小于 $sum+x$ 的前缀和个数，排序后二分或树状数组均可实现。

## 0x02 Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int read(){
	int x = 0, f = 1; char c = getchar();
	while(isdigit(c)^1) f &= (c!=45), c = getchar();
	while(isdigit(c)) x = (x<<1) + (x<<3) + (c^48), c = getchar();
	return f ? x : -x;
}

const int maxn = 100005;
int n, m, k, ans, a[maxn], c[maxn], rev[maxn], sum[maxn];

inline void modify(int p, int x){
	for(int i=p; i<=m; i+=(i&-i)) c[i] += x;
}

inline int query(int p){
	int res = 0;
	for(int i=p; i; i-=(i&-i)) res += c[i];
	return res;
}

bool check(int x){
	int tot = 0;
	for(int i=1; i<=n; ++i) tot += sum[i] >= x;
	for(int i=1; i<=n; ++i) tot += query(upper_bound(a+1, a+m+1, sum[i]-x)-a-1), modify(rev[i], 1);
	for(int i=1; i<=n; ++i) c[i] = 0;
	return tot >= k;
}

signed main(){
#ifndef ONLINE_JUDGE
	freopen("test.in", "r", stdin);
#endif
	n = read(), k = read();
	for(int i=1; i<=n; ++i) a[i] = a[i-1] + read(), sum[i] = a[i];
	sort(a+1, a+n+1); m = unique(a+1, a+n+1) - a - 1;
	for(int i=1; i<=n; ++i) rev[i] = lower_bound(a+1, a+m+1, sum[i]) - a;
	for(int l=-1e18, r=1e18, mid=(l+r)/2; l<=r; mid=(l+r)/2){
		if(check(mid)) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

