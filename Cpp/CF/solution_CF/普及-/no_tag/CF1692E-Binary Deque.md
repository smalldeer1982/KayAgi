# Binary Deque

## 题目描述

Slavic has an array of length $ n $ consisting only of zeroes and ones. In one operation, he removes either the first or the last element of the array.

What is the minimum number of operations Slavic has to perform such that the total sum of the array is equal to $ s $ after performing all the operations? In case the sum $ s $ can't be obtained after any amount of operations, you should output -1.

## 说明/提示

In the first test case, the sum of the whole array is $ 1 $ from the beginning, so we don't have to make any operations.

In the second test case, the sum of the array is $ 2 $ and we want it to be equal to $ 1 $ , so we should remove the first element. The array turns into $ [1, 0] $ , which has a sum equal to $ 1 $ .

In the third test case, the sum of the array is $ 5 $ and we need it to be $ 3 $ . We can obtain such a sum by removing the first two elements and the last element, doing a total of three operations. The array turns into $ [0, 1, 1, 1, 0, 0] $ , which has a sum equal to $ 3 $ .

## 样例 #1

### 输入

```
7
3 1
1 0 0
3 1
1 1 0
9 3
0 1 0 1 1 1 0 0 1
6 4
1 1 1 1 1 1
5 1
0 0 1 1 0
16 2
1 1 0 0 1 0 0 1 1 0 0 0 0 0 1 1
6 3
1 0 1 0 0 0```

### 输出

```
0
1
3
2
2
7
-1```

# 题解

## 作者：Dream_weavers (赞：6)

## 思路

比较简单的贪心题，可以来练手。

可以把题变一下，求序列中和为 $s$ 的最长子序列。

用数组 $loc$ 维护序列中每个 $1$ 的位置，$loc_i=j$ 即代表第 $i$ 个 $1$ 在序列中是第 $j$ 个数的位置。$l,r$ 分别代表左指针和右指针，初始值为 $l\gets1,r\gets s$，这个从 $loc_l$ 到 $loc_r$ 的子序列的和肯定是 $s$（~~废话~~）。为了让子序列最长，就要分别向左、向右找连续最多的 $0$ 添加到子序列中，求出整个子序列的长度。

然后循环让 $l,r$ 分别 $+1$，找出最长子序列的长度，用 $n$ 减去长度得到答案。

特别地，如果序列总和还不到 $s$，那就直接输出 $-1$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5; 
int loc[N],n,s,t,tot,x,ans;
void solve(){
	memset(loc,0,sizeof(loc));
	tot=0,ans=0;
	scanf("%d%d",&n,&s);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		if(x)loc[++tot]=i;
	}
	loc[0]=0,loc[tot+1]=n+1;
	if(tot<s){
		puts("-1");
		return;
	}
	for(int l=1,r=s;r<=tot;l++,r++){
		int sum=loc[r]-loc[l]+1;
		sum+=(loc[l]-loc[l-1]-1);
		sum+=(loc[r+1]-loc[r]-1);	
		ans=max(ans,sum);	
	}
	printf("%d\n",n-ans);
} 
int main(){
	scanf("%d",&t);
	while(t--)solve();
	return 0;
}

```

---

## 作者：cyrxdzj (赞：5)

### 一、思路

显然，如果数组本身的和就小于 $s$，那是肯定无解的。

维护 $l,r,sum$ 这几个变量。其中，$l,r$ 分别代表左/右指针，初始值均为一。$sum$ 代表从 $l$ 到 $r$ 之和，初始值为 $a_1$。

接下来，不断进行以下判断：

1. $sum=s$，此时更新答案，并将右指针右移。

2. $sum<s$，此时右指针右移以尽可能使 $sum$ 增大。

3. $sum>s$，此时左指针右移以尽可能使 $sum$ 减小。

直到某个指针越界为止。

### 二、代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int t;
int n,s;
int a[200005];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&s);
		int l=1,r=1;
		int ans=0x3fffffff;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
		}
		int sum=0;
		for(int i=1;i<=n;i++)
		{
			sum+=a[i];
		}
		if(sum<s)//数组之和小于s
		{
			printf("-1\n");
			continue;
		}
		sum=a[1];
		while(l<=n&&r<=n)
		{
			if(sum==s)
			{
				ans=min(l-1+n-r,ans);
				r++;
				sum+=a[r];
			}
			else if(sum>s)
			{
				sum-=a[l];
				l++;
			}
			else
			{
				r++;
				sum+=a[r];
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

```


---

## 作者：断清秋 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1692E)

题意：给定一个只有 $0$ 和 $1$ 的序列，每次可以从最左端或者最右端删除一个数，求最少删多少次能使整个序列的和为 $s$，无解输出 $-1$。

显然就是要使删后序列有 $s$ 个 $1$，这样需要删除的 $1$ 的数量是唯一确定的，于是直接预处理第 $i$ 个 $1$ 在序列中的位置 $pos_i$，然后暴力枚举前面要删多少个 $i$，直接 $O(1)$ 计算前后位置即可。

时间复杂度 $O(n)$。

---

## 作者：Hooch (赞：2)

### 题目大意

给出 $n$ 个数，每个数为 $0$ 或 $1$。你可以选择从两边删数，求至少删几个数才可以使剩下的数总和为 $s$ 。

如果不能达到 $s$ ，则输出 `-1` 。

### 基本思路

无解的情况很好判，若不删数都没法到 $s$ 个，那么一定无解。

然后我们想有解的情况该如何删数。

我们发现我们删完数后剩下的一定是一段连续的区间 $[l,r]$。那么我们就可以把问题转化成**选取一段最长的，和为 $s$ 的区间 $[l,r]$**。

那么我们处理出前缀和 $sum_i$，只需要在知晓 $[l,r]$ 的情况下 $O(1)$ 判断就行了。

但是这道题不允许暴力枚举 $[l,r]$，我们考虑优化。

很显然，$sum_i$ 是一个单调不严格上升的序列。我们可以在上面二分。

于是我们枚举起点 $l$，然后二分查找到值为 $sum_{l-1}+s$ 的 $sum_r$ 即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int s[200005]; 
main() {
    int t; cin >> t; while (t--) {
        int n, k; cin >> n >> k;
        for (int i = 1; i <= n; ++i) {int x; cin >> x; s[i] = s[i - 1] + x;}
        if (k > s[n]) {cout << -1 << endl; continue;}
        int p = -0x3f3f3f3f, L, R;
        for (int i = 1; i <= n; ++i) {
            int l = i, r = n, ans = 0;
            while (l < r)  {
                int mid = l + r + 1 >> 1;
                if (s[mid] - s[i - 1] <= k) l = mid;
                else r = mid - 1;
            }
            if (!l) continue;
            ans = l - i + 1;
            p = max(p, ans);
        }
        cout << (p == -0x3f3f3f3f ? -1 : (n - p)) << endl;
    }
}
```

---

## 作者：苏联小渣 (赞：2)

考虑枚举开头点，记作 $l$，那么此时我们需要找到与之对应的结尾点，记作 $r$，满足 $S[l,r]=s$（即 $[l,r]$ 的区间和）。这一部分内容可以使用一个简单的前缀和实现。具体实现方法为，由于每个点取值只有 $0,1$，那么对于每个前缀和 $S_i$，我们标记出 $S_i$ 最早出现的位置（这个位置一定有 $a_i=1$），这个标记位置的数组记作 $D$。那么对于开头点 $l$，结尾点就是 $D_{S_{l-1}+s}$（由前缀和简单推导可以发现）。那么这个 $[l,r]$ 就是满足题意的了。

可是我们发现，$l$ 左边，$r$ 右边可能有前缀 / 后缀的 $0$，而这些 $0$ 是不必删去的，因为要删去的数字尽可能少。所以我们要预处理出每一个点左边**最长连续 $0$ 的个数**（记作 $x$）和右边**最长连续 $0$ 的个数**（记作 $y$），最终答案就是 $n-(r-l+1)-(x_l+y_r)$。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int t, n, s, p, ans, a[200010], d[200010];
int f[200010], g[200010], k[200010];
int main(){
	scanf ("%d", &t);
	while (t --){
		ans = 1e9 + 7, p = 0;
		memset(d, 0, sizeof(d));
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		memset(k, 0, sizeof(k));
		scanf ("%d%d", &n, &s);
		for (int i=1; i<=n; i++){
			scanf ("%d", &a[i]);
			p += a[i];
		}
		if (p < s){
			puts ("-1");
			continue;
		}
		if (p == s){
			puts ("0");
			continue;
		}
		for (int i=2; i<=n; i++){
			if (a[i-1] == 0) g[i] = g[i-1] + 1;
			else g[i] = 0;
		}
		for (int i=n-1; i>=1; i--){
			if (a[i+1] == 0) k[i] = k[i+1] + 1;
			else k[i] = 0;
		}
		for (int i=1; i<=n; i++){
			f[i] = f[i-1] + a[i];
			if (a[i] == 1) d[f[i]] = i;
		}
		for (int i=1; i<=n; i++){
			int pos = d[s+f[i-1]];
			ans = min(ans, n-(pos-i+1)-k[pos]-g[i]);
		}
		printf ("%d\n", ans);
	}
	return 0;
}

```

---

## 作者：zjyqwq (赞：1)

### CF1692E Binary Deque题解


------------
#### 题意简述

有多组数据。

每组数据给出 $n$ 个数，每个数为 $0$ 或 $1$。你可以选择从两边删数，求至少删几个数才可以使剩下的数总和为 $s$。

如果不能达到 $s$，则输出 $-1$。



------------
#### 解题思路

举个例子：

$n=9$,$s=3$:
 ![](https://cdn.luogu.com.cn/upload/image_hosting/f2mra98t.png)
 
我们可以这样取：

![](https://cdn.luogu.com.cn/upload/image_hosting/sd5r21a3.png)

我们可以发现，取一个值只需要考虑前端删除几个数与后端删除几个数就可以了。比如这里，就是前端删除 $2$ 个数，后端删除 $1$ 个数。

到这里，题目变成了：

需要取总和为 $\sum\limits_{i=1}^na_i -s$ 的几个数，必须是部分连续的前端与后端，求最少取几个数。

我们设前端取总和为 $x$ 的连续的数最少为 $m_x$ 个，后端取总和为 $x$ 的连续的数最少为 $m1_x$ 个，则我们可以写出一段 $O(n)$ 的核心代码：

```cpp
for(int i=0;i<=b[n]-s;i++){
	ans=min(ans,m[i]+m1[sum-s-i]);
}
```

其中 $i$ 枚举前端取总和为 $i$ 的数，$sum$ 为 $\sum\limits_{i=1}^na_i$。

现在我们需要考虑 $m$ 与 $m1$ 如何处理。

此处较为简单，只是有一个细节，

看图：

![](https://cdn.luogu.com.cn/upload/image_hosting/r5eyocum.png)

我们可以发现：同样箭头所指的两个位置，之所以 $m_1$ 取前一个，是因为        $a_3$ 为 $0$，取了没价值。

我再略讲一下我的思路：取前缀和与后缀和，前缀和倒着放，后缀和正着放，就可以处理了。

什么叫前缀和倒着放呢？

如果正着放，前缀和数组为 $b$：

```cpp
for(int i=1;i<=n;i++){
	m[b[i]]=i;
}
```
就不可避免的出现上述问题，$m_1$ 被赋值成 $3$，所以我们应该倒着放：

```cpp
for(int i=n;i>=1;i--){
	m[b[i]]=i;
}
```

这样在 $i=2$ 时把 $m_1$ 的值从 $3$ 重新变成了 $2$。

后缀和同理。

------------
### 代码参考：
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace zjy {
#define int long long
#define p_ putchar(' ')
#define pn putchar('\n')
#define pc(x) putchar(x)
#define mk make_pair
#define pr(x) cout<<x
#define fi first
#define se second
#define Up(x,n,m) for(int x=n;x<=m;x++)
#define Down(x,n,m) for(int x=m;x>=n;x--)
    inline int read() {
        int s=0,w=1;
        char ch=getchar();
        while(ch<'0'||ch>'9') {
            if(ch=='-')
                w=-1;
            ch=getchar();
        }
        while(ch>='0'&&ch<='9')
            s=s*10+ch-'0',ch=getchar();
        return s*w;
    }
    inline void write(int x) {
        if(x < 0) {
            putchar('-');
            write(-x);
            return;
        }
        if(x >= 10) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace zjy;
int T,n,s,ans,a[200005],b[200005],c[200005],m[200005],m1[2000005];
signed main() {
	T=read();
	while(T--){
		n=read();s=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
			b[i]=b[i-1]+a[i];
		}
		for(int i=n;i>=1;i--){
			c[i]=c[i+1]+a[i];
			m[b[i]]=i;
		}
		for(int i=1;i<=n;i++){
			m1[c[i]]=n-i+1;
		}
		m[0]=m1[0]=0;
		ans=INT_MAX;
		for(int i=0;i<=b[n]-s;i++){
			ans=min(ans,m[i]+m1[b[n]-s-i]);
		}
		if(b[n]<s)ans=-1;
		if(b[n]==s)ans=0;
		write(ans);pn;
		for(int i=1;i<=n;i++)b[i]=c[i]=0;
	}
}
```


------------

PS: 
- $b_n$ 相当于 $\sum\limits_{i=1}^na_i$ 。
- 一定要记得前、后缀和数组清空。

---

## 作者：__vector__ (赞：0)

## 题目翻译  
给你一个 $n$ 个元素且只包含 $1$ 或 $0$ 两种元素的序列 $a$，以及一个正整数 $s$。  
在一次操作中，你可以删掉第一个元素或最后的元素。  
求使得剩下元素总和等于 $s$ 的最小操作次数。  
## 思路  
考虑到只能在首尾删元素，可以将问题转化为：  
在数列 $a$ 中选择一个区间 $[l,r]$，使得 $\sum_l^r a_i = s$，并且这个区间必须是满足条件的区间中最长的。  
### 暴力思路  
显然可以暴力枚举每一个区间，前缀和 $O(1)$ 判断当前区间总和是否为 $s$，然后更新答案。  
复杂度 $O(n^2)$。  
### 优化  
首先设数列第 $i$ 个元素的前缀和是 $qzh_i$。  
枚举左端点的部分不太好优化，那就优化选择右端点的部分。  
显然，固定了左端点 $l$ 后，右端点 $r$ 的前缀和值 $qzh_r$ 也就固定了。可以将其算出来，等于 $qzh_{l-1} + s$。  
而前缀和数组是升序的！  
也就是说可以用 lower_bound，$O(\log n)$ 把右端点求出来。  
但是要注意，lower_bound 求出来的右端点 $r$，是第一个满足要求的 $r$，而因为要求区间最长，我们需要的是最后一个满足要求的 $r$，所以还要做一些处理。  
算出 $a_r$ 后面有多少个元素 $0$，设有 $sum$ 个，将 $r$ 跳到 $r+sum - 1$，也就是这些 $0$ 元素的最后一个。  
这道题就做完了。  
复杂度 $O(n \log n)$。  
### 代码：  
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Main
{
	const int maxn=2e5+5;
	int t,n,s;
	int a[maxn];
	int qzh[maxn];//前缀和
	int len[maxn];
    //len[i] 代表第 i 个元素开始有多少个相邻的相同元素
	void main()
	{
		scanf("%d",&t);
		while(t--)
		{
			scanf("%d%d",&n,&s);
			for(int i=1;i<=n;i++)
			{
				scanf("%d",&a[i]);
				qzh[i]=qzh[i-1]+a[i];
			}
			for(int i=n;i>=1;i--)
			{
				if(i==n)
				{
					len[i]=1;
					continue;
				}
				if(a[i]==a[i+1])len[i]=len[i+1]+1;
				else len[i]=1;
			}
			if(qzh[n]<s)
			{
				printf("-1\n");
				continue;
			}
			int maxlen=0;
			for(int l=1;l<=n;l++)
			{
				int r=lower_bound(qzh+l,qzh+n+1,s+qzh[l-1])-qzh;
				if(a[r+1]==0&&r<n)r=r+1+len[r+1]-1;
				if(r==n+1)
				{
					continue;
				}
				maxlen=max(maxlen,r-l+1);
			}
			printf("%d\n",n-maxlen);
		}
	}
}
int main()
{
	Main::main();
	return 0;
}
```

---

