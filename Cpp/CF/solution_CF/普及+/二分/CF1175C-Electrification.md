# Electrification

## 题目描述

At first, there was a legend related to the name of the problem, but now it's just a formal statement.

You are given $ n $ points $ a_1, a_2, \dots, a_n $ on the $ OX $ axis. Now you are asked to find such an integer point $ x $ on $ OX $ axis that $ f_k(x) $ is minimal possible.

The function $ f_k(x) $ can be described in the following way:

- form a list of distances $ d_1, d_2, \dots, d_n $ where $ d_i = |a_i - x| $ (distance between $ a_i $ and $ x $ );
- sort list $ d $ in non-descending order;
- take $ d_{k + 1} $ as a result.

If there are multiple optimal answers you can print any of them.

## 样例 #1

### 输入

```
3
3 2
1 2 5
2 1
1 1000000000
1 0
4
```

### 输出

```
3
500000000
4
```

# 题解

## 作者：wanghaoyu120104 (赞：6)

# CF1175C 电气化
 **[题目传送门](https://www.luogu.com.cn/problem/CF1175C)**

 _~~**本人的第一篇题解**~~_ 。

 ## 题目大意
 有 $ n $ 个数 $ a_n $，寻找一个数 $ x $，使得第 $ k+1 $ 小的 $ \left | a_i-x \right | $ 最小。

 ## 思路

 根据 ~~小学二年级的~~ 知识我们知道， $ \left | a_i-x \right | $ 代表着 $ a_i $ 到 $ x $ 的距离，题目就变成了**寻找离 $ x $ 最近的第 $ k+1 $ 个点**。

 枚举每一个数作为第 $ k+1 $ 小的数所产生的答案，如同其它大佬们的题解一样，对于任意的一个 $ x $，离 $ x $ 最近的 $ k+1 $ 个点一定对应原来的 $ a $ 的一段区间。而第 $ k+1 $ 远的一定是这个区间的左端点或者右端点。

 这里我枚举的是左端点，那么离 $ x $ 最近的 $ k+1 $ 个点就是 $ a_{i-k},a_{i-k+1},…,a_i $，为了 $ a_i $ 和 $ a_{i-k} $ 离 $ x $ 更近，我们要把 $ x $ 放在中间，也就是左端点+区间长度的一半。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int t,n,k;
int a[N];
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n>>k;
        for(int i=1;i<=n;i++) cin>>a[i];
        int mi=INT_MAX,ans=0;
        for(int i=1;i<=n-k;i++)//枚举左端点
        {
            if(mi>a[i+k]-a[i])
            {
                mi=a[i+k]-a[i];//更新区间长度
                ans=a[i]+mi/2;//位置在现在区间的中点，也就是左端点+区间长度的一半
            }
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```

谢谢观看

---

## 作者：Leaper_lyc (赞：2)

~~本蒟蒻太蒟了，看了半个小时才发现其中的性质。~~

### 重要性质
前 $k$ 小的点是连续的区间。

若已经知道最长区间的长度，那么对于一个区间 $[L, R]$ 合法，当且仅当 $a_r-a_l\le length\times2$。

发现这个 $length$ 的取值有单调性，所以我们考虑二分答案，判断过程就是用上面所说的方法。

这样就做完啦，时间复杂度 $O(n\log V)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

inline void read(int &x) {
	x = 0; int f = 1; char ch = getchar();
	for (; ch < 48 || ch > 57; ch = getchar()) if (ch == '-') f = -1;
	for (; ch > 47 && ch < 58; ch = getchar())
		x = (x << 1) + (x << 3) + (ch ^ 48);
    x = x * f;
}

int T, n, k, ans;
int a[200005];

bool check(int mid) {
	int r = 1, len = 0;
	for (int l = 1; l <= n; l++) {
		while (r <= n && a[r] - a[l] <= (mid << 1)) r++;
		len = max(len, r - l);
		if (r - l > k) ans = ((a[r - 1] + a[l]) >> 1);
	}
	if (len > k) return true;
	return false;
}

void work() {
	read(n); read(k);
	for (int i = 1; i <= n; i++) read(a[i]);
	int L = 0, R = 1e9, Mid, Ans = 1e9;
	while (L <= R) {
		Mid = (L + R) >> 1;
		if (check(Mid)) Ans = Mid, R = Mid - 1;
		else L = Mid + 1;
	}
	check(Ans);
	printf("%d\n", ans);
}

signed main() {
	read(T);
	while (T--) work();
}
```

~~可爱妹子求赞。~~

---

## 作者：Zekrom (赞：2)

1.$-x$后最小的一段一定是连续的   
2. 即找$a[i+k]-a[i]$（注意有k+1个数）最小的的中位数，即$a[i]+mid(a[i],a[k+1])$,用小根堆维护一下即可，区间长度最短可以使k+1数最短   
上代码   
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#define inf 0x3f3f3f3f
#define N 200010
using namespace std;
int T,n,k,a[N];
inline int read(){
	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return x*f;
}
struct node{
	int x,y;
	node(int t1,int t2){x=t1,y=t2;}
	bool operator <(const node &s1)const{return x>s1.x;}
};
int main(){
	T=read();
	while(T--){
		n=read();k=read();
		priority_queue<node>q;
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=1;i+k<=n;i++){
			q.push(node(a[i+k]-a[i],a[i]+((a[i+k]-a[i])/2)));
		}
		printf("%d\n",q.top().y);
	}
	return 0;
}

```


---

## 作者：cosf (赞：1)

不知道为什么这么多人写二分。明明一道 $O(n)$ 好题。

## 思路

大致就是枚举每一个数作为第 $k + 1$ 小的数所产生的答案。

显然，对于任意的一个 $x$，离 $x$ 最近的 $k + 1$ 个点一定对应原来的 $a$ 的一段区间。而第 $k + 1$ 远的一定是这个区间的左端点或者右端点。

这里讲一下左端点的情况，另一种类似。

假设离 $x$ 近的那些点是 $a_{i - k}, a_{i - k + 1}, \dots, a_i$，其中第 $k + 1$ 远的是 $a_i$。

那么，因为 $a_{i - k}$ 要离 $x$ 更近，所以 $x \le \frac{a_{i - k} + a_i}{2}$。此时为了使 $x$ 离 $a_i$ 最近，$x$ 取 $\lfloor\frac{a_{i - k} + a_i}{2}\rfloor$ 即可。

把每一个 $a_i$ 作为第 $k + 1$ 近的答案取一个 $\min$ 就做完了。

## 代码

[提交记录](https://codeforces.com/contest/1175/submission/253337587)

---

## 作者：米奇 (赞：1)

## 二分

比赛时有考虑二分，但发现不知如何求那个点，也不知到如何判断是否满足条件。

后来问了谢神后才明白，距离前k小的点一定是一段连续的区间

然后就好做了，直接O(n)扫过所以点，如果l-r这个区间符合条件即a[r]-a[l]<=mid*2

找到最长的区间，如果区间长度>=mid说明符合条件。

## 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int T,n,m,wz,ans,a[N];
int pd(int mid)
{
	int r=1,res=0;
	for(int i=1;i<=n;i++)
	{
		while(r<=n&&a[r]-a[i]<=mid*2)r++;
		res=max(res,r-i);
		if(r-i>=m+1)wz=(a[i]+a[r-1])/2;
	}
	if(res>=m+1)return 1;
	else return 0;
}
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		int l=0,r=1e9,ans=1e9;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(pd(mid))ans=mid,r=mid-1;
			else l=mid+1;
		}
		pd(ans);
		printf("%d\n",wz);
	}
	return 0;
}
```

---

## 作者：SamuelXuch (赞：0)

这题真的需要二分吗。。。完全可以用 $O(n)$ 的算法。

正如其他题解所言，对于一个点 $x$ ，使得距离为前 $k$ 小的点一定位于一段连续的区间内，中间不包括任何其他点。

因此我们要找的就是最短的包含连续 $k+1$ 个点的区间，直接扫一遍就行了。最后将 $x$ 放到最短的区间的中点就是答案。

AC Code ，不用快读抢了最优解（156ms）：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+7;
int t,n,k,a[maxn],ans,pos;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        ans=1e9+1,pos=0;
        for(int i=1;i<=n-k;i++){ //枚举左端点
            if(ans>a[i+k]-a[i]){
                ans=a[i+k]-a[i]; //更新区间长度
                pos=a[i]+ans/2; //位置在现在区间的中点，故用左端点+区间长度的一半
            }
        }
        printf("%d\n",pos);
    }
}
```
抄题解可耻哦。

---

## 作者：rickyxrc (赞：0)

本文章遵守知识共享协议 CC-BY-NC-SA，同步发表于洛谷题解区，转载时须在文章的任一位置附上原文链接和作者署名（rickyxrc）。推荐在[我的个人博客](https://blog.rickyxrc.cc)阅读。

## 题面大意

给定一组点，要求你找到一个点，最小化这个点和其他点第 $k+1$ 短的距离。

## 解题思路

这道题我们需要发现一个性质：所有 $k+1$ 个对答案造成贡献的点是连续的。

所以我们考虑选择一个由点 $i$ 到点 $i+k$ 共 $k+1$ 个点构成的区间，此时我们将我们需要找到的点放在区间中即可。

扫一遍，使用优先队列记录最小值，复杂度 $O(n \log n)$。

```cpp
#include <stdio.h>
#include <queue>

typedef long long i64;
const i64 mod = 1, maxn = 400007;
i64 n, T, li[maxn], k;

std::priority_queue<std::pair<i64, i64>> qu;

int main()
{
    scanf("%lld", &T);
    while (T--)
    {
        qu = std::priority_queue<std::pair<i64, i64>>();
        scanf("%lld%lld", &n, &k);
        for (int i = 1; i <= n; i++)
            scanf("%lld", li + i);

        for (int i = 1; i + k <= n; i++)
            qu.push({li[i + k] - li[i], li[i] + (li[i + k] - li[i]) / 2});

        while (qu.size() != 1)
            qu.pop();
        printf("%lld\n", qu.top().second);
    }
    return 0;
}
```


---

