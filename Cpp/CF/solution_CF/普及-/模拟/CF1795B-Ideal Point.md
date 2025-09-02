# Ideal Point

## 题目描述

You are given $ n $ one-dimensional segments (each segment is denoted by two integers — its endpoints).

Let's define the function $ f(x) $ as the number of segments covering point $ x $ (a segment covers the point $ x $ if $ l \le x \le r $ , where $ l $ is the left endpoint and $ r $ is the right endpoint of the segment).

An integer point $ x $ is called ideal if it belongs to more segments than any other integer point, i. e. $ f(y) < f(x) $ is true for any other integer point $ y $ .

You are given an integer $ k $ . Your task is to determine whether it is possible to remove some (possibly zero) segments, so that the given point $ k $ becomes ideal.

## 说明/提示

In the first example, the point $ 3 $ is already ideal (it is covered by three segments), so you don't have to delete anything.

In the fourth example, you can delete everything except the segment $ [5, 5] $ .

## 样例 #1

### 输入

```
4
4 3
1 3
7 9
2 5
3 6
2 9
1 4
3 7
1 3
2 4
3 5
1 4
6 7
5 5```

### 输出

```
YES
NO
NO
YES```

# 题解

## 作者：qifan_maker (赞：1)

### 题目链接
[洛谷](https://www.luogu.com.cn/problem/CF1795B)

[Codeforces](https://codeforces.com/contest/1795/problem/B)
### 题意分析
给定 $n$ 条线段，要求使点 $k$ 被包含的次数最多，问能否去掉 $n$ 条线段中的任意线段，使得点 $k$ 被包含的次数最多。
### 题目解法
有一种有趣的方法，

假设有一个线段包含 $k$，但是由于这个线段中不止 $k$ 一个点，每一个点都被包括了一次，所以没法使得 $k$ 被包括得最多。

很容易想到，想要让 $k$ 被包括得最多，就要用第二个线段来再包括 $k$ 一次，但是想要包括 $k$ 又必须包括从 $k$ 到线段边缘这一段中的点，所以 $k$ 必须在这线段的边缘，也就是说这两个线段必须是 $[l,k]$ 和 $[k,r]$。

只要有两条线段为 $[l,k]$ 和 $[k,r]$，我们就可以删除其他的线段，由于除了点 $k$ 之外的其他点只被包含了 $1$ 次，而点 $k$ 却被包含 $2$ 次，所以答案为 `YES`。

假设只有 $[l,k]$ 的线段，没有 $[k,r]$ 的线段，或者只有 $[k,r]$ 的线段，没有 $[l,k]$ 的线段，亦或者每个线段的 $l$ 和 $r$ 都不为 $k$，那么点 $k$ 相邻几个点的值将会与 $k$ 相同，不能保证点 $k$ 是最大的，所以答案为 `NO`。

由于 $l_i \le k_i$，$l_i$ 是有可能等于 $k_i$ 的，所以我们需要考虑一种特殊情况：$[k,k]$，我们可以只选择线段 $[k,k]$，其他的删除，所以答案为 `YES`。

整合一下以上结论，我们可以发现只要所有的线段中有 $l$ 和 $r$ 等于 $k$，答案就为 `YES`，否则答案为 `NO`。

也就是我们只需要遍历 $n$ 个线段，如果有一个线段的 $l$ 或 $r$ 等于 $k$，就标记起来，如果全部遍历完后，$l$ 和 $r$ 都被标记过，那么答案为 `YES`，否则答案为 `NO`。

时间复杂度 $\mathcal{O}(n)$。
### [AC](https://www.luogu.com.cn/record/103379150) Code
```cpp
/*
题目编号：
B. Ideal Point
思路：
无
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
    while (t--){
    	int n,k;
    	cin >> n >> k;
		bool f1,f2;
    	f1 = f2 = false;
    	for (int i=1;i<=n;i++){
    		int l,r;
    		cin >> l >> r;
    		if (l == k){
    			f1 = true;
			}
    		if (r == k){
    			f2 = true;
			}
		}
		if (f1 and f2){
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
	return 0;
}
```

---

## 作者：Ray1 (赞：1)

显然地，不覆盖点 $k$ 的线段都删除，覆盖点 $k$ 的线段都保留。

考虑维护一条线段 $[L,R]$ 表示被覆盖次数最多的线段，每加入一条线段 $[l_i,r_i]$ 就跟 $[L,R]$ 取相交部分，最后判断 $L=R=k$ 是否成立即可。

```cpp
bool check(){
	int L=1,R=50;
	for(int i=1;i<=n;i++){
		cin>>l>>r;
		if(l<=k&&k<=r)L=max(L,l),R=min(R,r);
	}
	return L==R;
}
```

---

## 作者：loser_seele (赞：1)

首先删除所有不包含 $ k $ 的点，这显然不会使得答案更劣。如果删除后没有线段则直接无解。

考虑所有剩下的线段，则 $ f(k)=n $，剩下的就是检查是否只有 $ k $ 被所有线段包含。直接求出所有线段的交集，然后判断交集大小是否为 $ 1 $ 即可。

时间复杂度线性，可以通过。

[提交记录](https://codeforces.com/contest/1795/submission/194052670)

---

## 作者：ztlh (赞：1)

# Solution 1

这是我的赛时思路。

可以发现，如果一个区间对 $k$ 没有贡献，放入后一定会使答案变劣。

因此，统计所有对 $k$ 有贡献的区间的贡献，最后遍历判断即可。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 100005
using namespace std;
int T,n,k;
int cnt[55];
bool flag;
int main(){
	scanf("%d",&T);
	while(T--){
		memset(cnt,0,sizeof(cnt));
		scanf("%d%d",&n,&k);
		for(int i=1,l,r;i<=n;i++){
			scanf("%d%d",&l,&r);
			if(l<=k&&k<=r)
				for(int j=l;j<=r;j++) cnt[j]++;
		}
		flag=1;
		for(int i=1;i<=50;i++)
        if(cnt[i]>=cnt[k]&&i!=k) flag=0;
		if(flag) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

# Solution 2

这种思路更为简单，大多数选手用的应该是这种。

记录两个变量 $L$ 和 $R$，表示区间 $[ L , R ]$ 中的答案均与 $k$ 相等。

对于每次的区间 $[ l_i , r_i ]$，若 $l_i \leq k \leq r_i$，则令：

- $L = max (L , l_i)$

- $R = min (R , r_i)$

只要最终区间长为 $1$（即 $L = R$）即可。

赛时没想到，代码不放了。

---

## 作者：ダ月 (赞：0)

### 题意分析：

给定 $n$ 条线段，可以选择其中一些线段进行覆盖。要求第 $k$ 个位置覆盖的线段条数大于其他位置，问存不存在一种方案，使得条件满足。

### 题目分析：

我们考虑贪心，选择一些对 $k$ 有贡献的线段加入。然后统计每个点的数值。若存在一个点覆盖的线段条数大于等于 $k$ 位置上覆盖的线段条数，就输出 ```NO```。否则输出 ```YES```。

我为了方便，在加入线段时用了差分，事实上不用差分也行。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int n,k;
int T;
const int N=60;
int a[N];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		memset(a,0,sizeof(a));
		for(int i=1;i<=n;i++){
			int x,y;scanf("%d%d",&x,&y);
			if(y>=k&&x<=k) a[x]++,a[y+1]--;
		}
		for(int i=1;i<=50;i++) a[i]+=a[i-1];
		bool flag=false;
		for(int i=1;i<=50;i++)
			if(i!=k&&a[i]>=a[k]){
				flag=true;
				break;
			}
		if(!flag) puts("YES");
		else puts("NO");
	}return 0;
}
```

时间复杂度：$O(\sum n)$。

---

## 作者：ttq012 (赞：0)

容易发现，一个区间只有在包含 $m$ 这个点的时候，才会是有用的区间。

那么读入的时候，如果一个区间 $[l_i,r_i]$ 满足 $l_i\le m\le r_i$，那么这个区间是有用的，否则是无用的。

然后差分一下，计算出每一个点的 $f$ 的值。

然后判断有没有的点的 $f$ 的值 $\ge f(m)$ 即可。

时间复杂度 $O(n)$。

~~数据范围怎么这么小~~

[Code](https://www.luogu.com.cn/paste/a0johh12)

---

## 作者：liujy_ (赞：0)

 满足条件当且仅当一条线段仅包含点 $k$ 或者两条线段的交只包含点 $k$。  
 如果不满足上述两个条件，一定会有至少一个点上的线段的覆盖数量与 $k$ 相等。   
 枚举线段即可。  
 ```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int N=2e5+5;
int t,n,k;
struct node{
	int l,r;
	bool operator < (node a)const{
		if(l==a.l)return r<a.r;
		return l<a.l;
	}
}a[N];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);bool p=0;
		for(int i=1;i<=n;i++){
			scanf("%d%d",&a[i].l,&a[i].r);
			if(a[i].l==a[i].r&&a[i].l==k)p=1;
		}
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				if(max(a[i].l,a[j].l)==min(a[i].r,a[j].r)&&max(a[i].l,a[j].l)==k)p=1;
		if(p)printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}

```


---

