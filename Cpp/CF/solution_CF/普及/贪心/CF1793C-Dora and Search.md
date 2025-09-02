# Dora and Search

## 题目描述

As you know, the girl Dora is always looking for something. This time she was given a permutation, and she wants to find such a subsegment of it that none of the elements at its ends is either the minimum or the maximum of the entire subsegment. More formally, you are asked to find the numbers $ l $ and $ r $ $ (1 \leq l \leq r \leq n) $ such that $ a_l \neq \min(a_l, a_{l + 1}, \ldots, a_r) $ , $ a_l \neq \max(a_l, a_{l + 1}, \ldots, a_r) $ and $ a_r \neq \min(a_l, a_{l + 1}, \ldots, a_r) $ , $ a_r \neq \max(a_l, a_{l + 1}, \ldots, a_r) $ .

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ occurs twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ , but $ 4 $ is present in the array).

Help Dora find such a subsegment, or tell her that such a subsegment does not exist.

## 说明/提示

In the first and fourth test cases, it can be shown that there are no desired subsegments.

In the second test case, the subsegment $ [1, 4] $ satisfies all the conditions, because $ \max(a_1, a_2, a_3, a_4) = 4, \min(a_1, a_2, a_3, a_4) = 1 $ , as we see, all the conditions are met.

In the third test case, the subsegment $ [2, 6] $ also satisfies all the conditions described.

## 样例 #1

### 输入

```
4
3
1 2 3
4
2 1 4 3
7
1 3 2 4 6 5 7
6
2 3 6 5 4 1```

### 输出

```
-1
1 4
2 6
-1```

# 题解

## 作者：TernaryTree (赞：8)

双指针板子题。

考虑初始指针 $l=1$，$r=n$，$p=1$，$q=n$。$l,r$ 代表当前区间，$p,q$ 代表当前区间最小值最大值。然后判断当前区间符不符合条件，不符合就缩小区间，如果找到一个直接输出，否则最后 $l\gt r$ 就无解，复杂度线性，

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 10;

int t, n;
int a[maxn];
int l, r, mn, mx;

int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        l = mn = 1, r = mx = n;
        while (l <= r) {
            if (a[l] == mn) {
                ++l, ++mn;
            } else if (a[l] == mx) {
                ++l, --mx;
            } else if (a[r] == mn) {
                --r, ++mn;
            } else if (a[r] == mx) {
                --r, --mx;
            } else {
                break;
            }
        }
        if (l > r) puts("-1");
        else cout << l << " " << r << endl;
    }
    return 0;
}
```

---

## 作者：hswfwkj_ (赞：6)

传送门：<https://www.luogu.com.cn/problem/CF1793C>

update：浏览了一下别人的题解感觉都有点复杂了，想尽可能把这篇题解完善一下。

## 思路简述：
请确保自己看懂了题目翻译。

首先有一个误区，就是第一眼（可能只有我）会以为区间长度有单调性，但仔细想想就可以排除。

事实上，这道题存在另一种单调性，那就是随着一个区间逐渐缩短，区间最大值一定单调不升，区间最小值一定单调不降，这个结论是很显然的，但是如何应用到这道题呢？

我们可以考虑，一开始把整个排列全选。那么，如果有一个端点不符合题目的要求，我们不可能通过移动另一个端点来使这个端点符合要求。这个结论可以通过前面引入的结论证明。所以，我们就必须移动不符合要求的端点，直到两个端点都符合要求为止。

因为我们每次删除的是最大值或最小值，因此维护当前的最大最小值也是很方便的，开两个变量记录就行了。因此其他人开 ST 表来维护极值的操作令我无法理解（无贬低之意）。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T, n, a[200005];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while(T--)
	{
		cin >> n;
		for(int i = 1; i <= n; i++) cin >> a[i];
		int l = 1, r = n, maxn = n, minn = 1;
		while(1)
		{
			if(l > r) {cout << -1 << '\n'; goto here;}
			if(a[l] == maxn) {l++, maxn--; continue;}
			if(a[l] == minn) {l++, minn++; continue;}
			if(a[r] == maxn) {r--, maxn--; continue;}
			if(a[r] == minn) {r--, minn++; continue;}           
            /*
            核心部分，挪动端点操作，修改最值
            */
			break;
		}
		cout << l << ' ' << r << '\n';
		here:;
	}
	return 0;
}
```

---

## 作者：zhuweiqi (赞：1)

这道题我们可以用两个双端队列做，队列 $q$ 用来表示 $a_l$ 至 $a_r$ 中所有的数（$l$ 和 $r$ 不一定满足条件），队列 $book$ 用来记录队列 $q$ 里的每个元素所对应的原来的下标，$l$ 是 $book$ 的队首元素，$r$ 是 $book$ 的队尾元素，两个队列的长度应始终保持一致。由于 $a$ 是一个排列，所以我们可以用两个变量来记录当前队列 $q$ 里的最小值和最大值，如果当队列 $q$ 的队首元素是最小值或最大值时，就让它和队列 $book$ 的队首元素同时出队，因为当 $l$ 是 $book$ 的队首元素时，$l$ 和 $r$ 肯定不满足条件，如果当队列 $q$ 的队尾元素是最小值或最大值时亦是如此，另外，如果出队的元素是最小值，那么最小值就需要加一，如果出队的元素是最大值，那么最大值就需要减一，而且可以证明，因为 $a$ 是个排列，所以新的最小值和最大值一定是新的队列 $q$ 里的最小值和最大值。最后，如果队列空了，就输出 $-1$，否则就说明当前的 $l$ 和 $r$ 一定满足条件，输出它们即可，上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
deque<int> q,book;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n,x;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&x);
			q.push_back(x);
			book.push_back(i);
		}
		int mins=1,maxs=n;
		while(q.size()){
			int flag=0;
			if(q.size() && q.front()==mins){
				mins++;
				q.pop_front();
				book.pop_front();
				flag=1;
			}
			else if(q.size() && q.front()==maxs){
				maxs--;
				q.pop_front();
				book.pop_front();
				flag=1;
			}
			if(q.size() && q.back()==mins){
				mins++;
				q.pop_back();
				book.pop_back();
				flag=1;
			}
			else if(q.size() && q.back()==maxs){
				maxs--;
				q.pop_back();
				book.pop_back();
				flag=1;
			}
			if(flag==0) break;
		}
		if(q.size()) printf("%d %d\n",book.front(),book.back());
		else printf("%d\n",-1);
		while(q.size()){
			q.pop_front();
			book.pop_front();
		}
	}
	return 0;
}
```

---

## 作者：zac2010 (赞：1)

我们先考虑怎么判断一个位置 $i$ 是否可以作为一个合法区间的右端点：不合法的区间个数小于 $i$ 这个值。

具体的，假设 $lmi_i$ 为 $i$ 左边第一个小于他的位置，且 $lmx_i$ 为 $i$ 左边第一个大于他的位置。那么 $i$ 作为右端点，其中 $\min(lmi_i, lmx_i)+1$ 直到 $i$ 作为左端点，都是不合法的区间（因为 $i$ 位置是最值）。再往左，也就是 $1$ 到 $\min(lmi_i, lmx_i)$ 作为左端点的，答案取决于左端点是否是最值。那么左端点要成为区间最大值，当且仅当是 $lmx_i$ 以及 $lmx_{lmx_i}$ 等等以此类推。那么左端点要成为区间最小值，也同理，当且仅当是 $lmi_i$ 以及 $lmi_{lmi_i}$ 等等以此类推。

而由于只要左端点不是 $i$ 这个位置，就不可能既为最大值又为最小值，所以我们只要求出有多少左端点为到 $i$ 这段区间的最大值，多少左端点为最小值即可。求出了一种可行方案的右端点 $i$ 之后，只要暴力从 $i$ 往左扫一遍找出合法的左端点即可。

上述的 $lmi_i$ 和 $rmi_i$ 用单调栈求解，由于要求出左边有多少个作为最大值或最小值的左端点，本来我们要暴力跳，但是我们可以用倍增优化。

时间复杂度 $O(n \log n)$ 级别，主要为倍增的时间复杂度。

[代码](https://codeforces.com/contest/1793/submission/193429748)。

---

## 作者：lizhous (赞：1)

[洛谷](https://www.luogu.com.cn/problem/CF1793C)

[CF](http://codeforces.com/problemset/problem/1793/C)

作为 div.2 的 C 还是有一定难度的。~~可能是我想难了~~
## 分析
根据数据范围，可以看出需要 $O(n)$ 解决问题，但一般寻找合法区间的题需要枚举其中一个端点。我们发现直接寻找不太现实，考虑预处理。

方便分析，我们称区间最大值和最小值为极值。我们称把两个限制拆开，分为首项不是极值和尾项不是极值。这里只讨论首项，尾项只需要反过来处理即可。

因为不涉及删数，所以若 $l$ 的值不是区间 $[l,r]$ 的极值，则 $l$ 必然不是 $[l,r+1]$ 的极值。我们只需要对于每个 $l$ 预处理出最小的 $r$ 使得 $l$ 不是 $[l,r]$ 的极值，就可以轻松求得答案。方便说明，左端点和右端点的预处理的结果存在数组 $lto$ 和 $rto$

不是极值，则必然存在至少一个数大于 $l$ 且至少一个数小于 $l$。这个使用单调栈即可。

最后的匹配，处理出数组 $mar_l$ 为 $\min\limits^{l}_{i=1}lto_i$，然后枚举右端点 $r$，若 $mar_{rto_r}\le r$，则有答案，输出即可。没找到就无解。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define int long long
using namespace std;
int T,n,m,a[200001],len,st[200001],lmi[200001],lma[200001],rmi[200001],rma[200001];
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&n);
		for(int i=1;i<=n;i++) //输入 
		{
			scanf("%lld",&a[i]);
		}
		len=0;
		//单调栈四个 
		for(int i=1;i<=n;i++)
		{
			while(len&&a[st[len]]<a[i]) len--;
			lma[i]=st[len];
			st[++len]=i;
		}
		len=0;
		for(int i=1;i<=n;i++)
		{
			while(len&&a[st[len]]>a[i]) len--;
			lmi[i]=st[len];
			st[++len]=i;
		}
		len=0;
		for(int i=n;i>=1;i--)
		{
			while(len&&a[st[len]]>a[i]) len--;
			rmi[i]=st[len];
			if(rmi[i]<i) rmi[i]=n;
			st[++len]=i;
		}
		len=0;
		for(int i=n;i>=1;i--)
		{
			while(len&&a[st[len]]<a[i]) len--;
			rma[i]=st[len];
			if(rma[i]<i) rmi[i]=n;
			st[++len]=i;
		}
		bool flag=false;
		rma[0]=n+1;
		for(int i=1;i<=n;i++)
		{
			lmi[i]=min(lmi[i],lma[i])-1; //右端点向左的预处理结果 
			rmi[i]=max(rmi[i],rma[i])+1; //左端点向右的预处理结果
			if(rma[i-1]<rmi[i]) //因为要记录最小值的具体位置，所以用if判断 
			{
				rma[i]=rma[i-1]; //存值 
				lma[i]=lma[i-1]; //存位置 
			}
			else
			{
				rma[i]=rmi[i];
				lma[i]=i;
			}
			if(rma[max(lmi[i],0ll)]<=i) //小于的话就是合法 
			{
				cout<<lma[max(lmi[i],0ll)]<<' '<<i<<endl; //输出即可 
				flag=true;
				break;
			}
		}
		if(!flag) //无解 
		{
			printf("-1\n");
		}
	}
}
```

---

## 作者：loser_seele (赞：1)

双指针好题。

首先可以检查整个序列是否满足条件，是则直接输出。

接下来考虑不符合条件的情况，即有一个端点为最值，那么这个端点不可能出现在任何合法区间，因为它将一直会是最值。

于是从整个序列开始不断缩小区间，缩小的过程中判一下端点是否满足条件，如果两个条件都满足则输出，否则继续缩小区间。正确性上面已经提到。

再套一个 ST 表查询区间最值即可，时间复杂度 $ \mathcal{O}(n\log{n}) $，因为原数组是排列所以应该还有更优秀的实现，但是懒。

[提交记录](https://codeforces.com/problemset/submission/1793/193404601)

---

## 作者：aeiouaoeiu (赞：0)

### 题意

给你一个长度为 $n$ 的排列 $a_1,a_2,\ldots,a_n$，要求找出一对数 $l,r$，使 $a_l,a_{l+1},\ldots,a_r$ 的最大最小值均不为 $a_l,a_r$，没有输出 $-1$。

### 解法

双指针+RMQ。

我们可以用两个数 $x,y$ 表示当前检查的区间(初始为 $[1,n]$)，那么就有四种情况：

- 区间 $[x,y]$ 最大最小值都为 $a_x,a_y$，即都在两端：此时保留 $a_x,a_y$ 都是不可以的，所以 $x\to x+1$，$y\to y-1$，即将区间缩小至不包括 $a_x,a_y$。

- 最大最小值中有一个为 $a_x$，$a_y$ 不为最大最小值：此时保留 $a_x$ 是不可以的，所以 $x\to x+1$，即将区间缩小至不包括 $a_x$。

- 最大最小值中有一个为 $a_y$，$a_x$ 不为最大最小值：此时保留 $a_y$ 是不可以的，所以 $y\to y-1$，即将区间缩小至不包括 $a_y$。

- 最大最小值都不为 $a_x,a_y$，即都不在两端：此时区间 $[x,y]$ 合法，输出 $x,y$ 即可。

如果检查到 $y > x$ 了，那么明显已经不可以了，输出 $-1$。

为什么这样可行呢？

因为我们是从 $[1,n]$ 开始判断的，当我们判断到 $[x,y]$ 时，比它大的区间都已经排除掉了，不然我们就不会判断 $[x,y]$ 了，所以我们无法通过扩大区间来寻找合法的答案。

最后是区间最大最小值的问题。

本蒟蒻不会用类似桶的方法，所以用了 ST 表。

时间复杂度：ST 表初始化 $\mathcal{O}(n\log n)$，查找区间 $\mathcal{O}(n)$，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=200005;
ll t,n,a[maxn],p[maxn][20],p2[maxn][20],log_2[maxn];
void build(void){ //ST 表维护最大最小值 
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i<=n+1-(1<<j);i++) p[i][j]=0,p2[i][j]=114514191919810ll;
	}
	for(int i=1;i<=n;i++) p[i][0]=p2[i][0]=a[i];
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i<=n+1-(1<<j);i++){
			p[i][j]=max(p[i][j-1],p[i+(1<<(j-1))][j-1]);
			p2[i][j]=min(p2[i][j-1],p2[i+(1<<(j-1))][j-1]);
		}
	}
}
ll query(ll l,ll r){
	ll k=log_2[r-l+1];
	return max(p[l][k],p[r-(1<<k)+1][k]);
}
ll query2(ll l,ll r){
	ll k=log_2[r-l+1];
	return min(p2[l][k],p2[r-(1<<k)+1][k]);
}
int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>t;
    log_2[0]=-1;
    for(int i=1;i<=maxn-4;i++) log_2[i]=((i&(i-1))?(log_2[i-1]):(log_2[i-1]+1)); //预处理 log2(x) 的值 
    while(t--){
    	cin>>n;
    	for(int i=1;i<=n;i++) cin>>a[i];
		build();
		ll l=1,r=n,minx,maxx;
		bool fir,sec,flag=0;
		while(l<=r){
			maxx=query(l,r),minx=query2(l,r);
			fir=((a[l]==maxx)||(a[l]==minx)); //a[l] 为最大最小值之一 
			sec=((a[r]==maxx)||(a[r]==minx)); //a[r] 为最大最小值之一 
			if(fir&&sec) l++,r--;
			else if(fir) l++;
			else if(sec) r--;
			else{ //合法 
				flag=1;
				cout<<l<<" "<<r<<"\n";
				break;
			}
		}
		if(!flag) cout<<"-1\n";
	}
    return 0;
}
```


---

