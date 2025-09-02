# Challenging Cliffs

## 题目描述

You are a game designer and want to make an obstacle course. The player will walk from left to right. You have $ n $ heights of mountains already selected and want to arrange them so that the absolute difference of the heights of the first and last mountains is as small as possible.

In addition, you want to make the game difficult, and since walking uphill or flat is harder than walking downhill, the difficulty of the level will be the number of mountains $ i $ ( $ 1 \leq i < n $ ) such that $ h_i \leq h_{i+1} $ where $ h_i $ is the height of the $ i $ -th mountain. You don't want to waste any of the mountains you modelled, so you have to use all of them.

From all the arrangements that minimize $ |h_1-h_n| $ , find one that is the most difficult. If there are multiple orders that satisfy these requirements, you may find any.

## 说明/提示

In the first test case:

The player begins at height $ 2 $ , next going up to height $ 4 $ increasing the difficulty by $ 1 $ . After that he will go down to height $ 1 $ and the difficulty doesn't change because he is going downhill. Finally the player will go up to height $ 2 $ and the difficulty will increase by $ 1 $ . The absolute difference between the starting height and the end height is equal to $ 0 $ and it's minimal. The difficulty is maximal.

In the second test case:

The player begins at height $ 1 $ , next going up to height $ 3 $ increasing the difficulty by $ 1 $ . The absolute difference between the starting height and the end height is equal to $ 2 $ and it's minimal as they are the only heights. The difficulty is maximal.

## 样例 #1

### 输入

```
2
4
4 2 1 2
2
3 1```

### 输出

```
2 4 1 2 
1 3```

# 题解

## 作者：Fire_flame (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/CF1537C)

# 分析

这道题如果没有绝对值最小的限制的话，直接排序即可:

```cpp
sort(a+1,a+n+1);
```
但是题目有一个首尾相差最小的要求，咋办捏？

其实我们刚刚的思路已经对了一大半了，一个**有序**的数组差值最小无非就是相邻的某两项，假设它们为 $a_i$ 和 $a_{i+1}$。

这个时候我们能把所有的数分成两组：

第一组：$a_1$~$a_{i-1}$

第二组：$a_{i+2}$~$a_n$

把它们这样接上：

$a_i$---第二组---第一组---$a_{i+1}$

这样就能解决了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
int t;
int a[MAXN];
int main(){
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		int h=1e9;
		int k;
		for(int i=1;i<n;i++){
			if(h>a[i+1]-a[i]){
				h=a[i+1]-a[i];
				k=i;
			}
		}
		//printf("%d %d\n",h,k);
		printf("%d ",a[k]);
		for(int i=k+2;i<=n;i++)printf("%d ",a[i]);
		for(int i=1;i<k;i++)printf("%d ",a[i]);
		printf("%d",a[k+1]);
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Sharing666 (赞：4)

## 题意

给你一个序列，求满足以下条件的排列：

**条件 1**：序列首项和末项的差值的绝对值最小。

**条件 2**：满足条件 1 下，序列中满足 $a_i<a_{i+1}$ 的项数最大。

**条件 3**：满足条件 1、2 下，序列的字典序最小。

## 思路

因为输入时的排列顺序对答案并没有影响，所以可以先排个序。

条件 1 很好想，直接取差最小的相邻两项。假设是 $a_i$ 和 $a_{i+1}$ 吧。

然后开始考虑条件 2。

最好的情况是从首项到末项一直上升，但这是不可能的，因为**首项和末项取了相邻两项**。

于是我们只好退而求其次，考虑只在中间断开一次，两边单调上升。

容易想到可以把排序后的序列以 $a_i$ 和 $a_{i+1}$ 为分界线分成两部分，只有 $a_1$ 和 $a_n$ 断开了，其他都保持单调上升。

![](https://cdn.luogu.com.cn/upload/image_hosting/j4gvcvx7.png)

然后我们发现调换 $a_{i+1}$ 和 $a_i$ 的位置后依然满足条件 2，而且字典序更小。

![](https://cdn.luogu.com.cn/upload/image_hosting/44hcrveq.png)

~~但是我不会证明这样为什么字典序最小~~

上代码。

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

int t,n,a[20002];

int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		int l,r,minn=2147483647;
		for(int i=1;i<n;i++) 
			if(a[i+1]-a[i]<minn) l=i,r=i+1,minn=a[r]-a[l];
		printf("%d ",a[l]);
		for(int i=r+1;i<=n;i++) printf("%d ",a[i]);
		for(int i=1;i<l;i++) printf("%d ",a[i]);
		printf("%d\n",a[r]);
	}
	return 0;
}
```


---

## 作者：xuanyuan_Niubi (赞：3)

# 题意描述
有 $ t $ 组数据，每组给定长度 $ n $ 和这个数组 $ h_i $ 。要求将这个数组重新排列，使 $ |h_n-h_1| $ 最小且满足 $ h_i\le h_{i+1} $ 的 $ i $ 的个数最多。

输出满足条件的重新排列后的数组。

$ 1 \le t \le ,2 \le n \le 2 \cdot 10^5 ,1 \le h_i \le 10^9 $ 且保证所有 $ n $ 的和不超过 $ 2 \cdot 10^5 $ 。
# 思路分析
因为题目要求是使 $ |h_n-h_1| $ 最小，所有可以将相差最小的两个数排在首和尾，且一定不会有比这更优的方案，且一定是可以这样放的。

将相差最小的两个数放在首尾后，就需要考虑中间怎么放才可以使满足 $ h_i \le h_{i+1} $ 的 $ i $ 最多。若重新排列后的数组单调上升不就可以了吗？

于是将原数组从小到大排序，找到 $ h_i-h_{i-1} $ 最小的 $ i $ 令为 $ pos $。先输出 $ h_{pos} $ 到 $ h_n $ ，再输出 $ h_1 $ 到 $ h_{pos-1} $。因为中间的数本来就是排过序的，所以一定不会比最优的更劣。

那就举个例子：若排序后是 
$$ 1,2,3,3,5 $$
找到差最小的， $ pos= 4 $ ，所以最后就是：
$$ 3,5,1,2,3 $$
确实没有更优的了。

但是注意特判下 $ n=2 $ 的情况。 $ n=2 $ 的情况就先输小的再输出大的。
# 代码
```cpp
#include<map>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;
const int M=2e5+5;
inline ll read(){
	char c=getchar();ll x=0,f=1;
	for(;c<'0'||c>'9';c=getchar())if(c=='-')f=0;
	for(;c<'0'||c>'9';c=getchar())if(c=='-')f=0;
	for(;c<='9'&&c>='0';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return f?x:-x;
}
inline int min(int a,int b){return a<b?a:b;}
int main(){
	int T=read();
	while(T--){
		int n=read(),a[M],imin=0x3f3f3f3f,pos=0;
		for(int i=1;i<=n;i++)a[i]=read();
		sort(a+1,a+1+n);
		if(n==2){
			printf("%d %d\n",a[1],a[2]);continue;
		}
		for(int i=2;i<=n;i++)if(a[i]-a[i-1]<imin)imin=a[i]-a[i-1],pos=i;
		for(int i=pos;i<=n;i++)printf("%d ",a[i]);
		for(int i=1;i<pos;i++)printf("%d ",a[i]);puts("");
	}
	return 0;
}
```


---

## 作者：lrmlrm_ (赞：2)

# 题意
  有$ t $组数据，每组里有长度为 $ n $ 的 $ h $ 数组。你要重新排列 $ h $ 数组，在满足 $ \left\vert h_1 - h_n \right\vert $ 最小的前提下，让满足 $ h_i \leq h_{i+1} \left ( 1 \leq i < n \right ) $ 的 $ i $ 尽量多，输出排列后的数组。 
  $ \left( 1 \leq t \leq 100,2 \leq n \leq 2⋅10^5 , 1 \leq h_i \leq 10^9 , \text{保证所有} n \text{的和}\leq 2⋅10^5  \right) $
# 思路
  由于题目要让 $\left\vert h_1 - h_n \right\vert $ 最小，所以我们要先排序，找到差值最小的两个数，从后面那个数的位置 $ k $ 开始输出，输出完 $ h_n $ 后就再从 $ h_1 $ 开始输出到 $ h_{k-1} $ 就可以了。
  
  $ \color{Red} \left( \text{注意：当} n = 2 \text{时，只需输出排序后的}h\text{数组} \right) $
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,mi,k;
int a[200010];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		mi=2100000000,k=0;
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		if(n==2){
			printf("%d %d\n",a[1],a[2]);
			continue;
		}
		for(int i=1;i<n;i++)
			mi=min(a[i+1]-a[i],mi);
		for(int i=1;i<n;i++)
			if(mi==a[i+1]-a[i])
				k=i;
		for(int i=k+1;i<=n;i++)
			printf("%d ",a[i]);
		for(int i=1;i<=k;i++)
			printf("%d ",a[i]);
		printf("\n");
	}
	return 0;
}
//^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^
```


---

## 作者：pomelo_nene (赞：1)

给定一个长为 $n$ 的数列 $h$，排列成 $a$ 后，在满足 $|a_1-a_n|$ 最小的情况下使 $\sum_{i=1}^{n-1} [a_i \leq a_{i+1}]$ 最大。给出一个合法解。

我们从小到大排序，就可以找到 $|a_1-a_n|$ 的最小值 $p$。那么找到在排序后的 $h$ 中的一个索引 $k$，使得 $h_{k+1}-h_{k}=p$。那么我们可以确定 $a_1$ 为 $h_k$，$a_n$ 为 $h_{k+1}$（注意到有 $n=2$ 的情况）。要使 $\sum_{i=1}^{n-1} [a_i \leq a_{i+1}]$ 最大，我们的目标是让下坡尽量的少。有一个显然的构造方法可以使得只有一个下坡，即，输出 $h_{k-1},h_{k+1}\cdots ,h_n,h_1, \cdots ,h_{k-2},h_k$。这样就可以满足只有一个下坡（特殊的，在 $n=2$ 的情况下没有）。

代码由上面的思路整理可得。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,h[200005];
int main(){
	scanf("%d",&T);
	while(T-->0)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;++i)	scanf("%d",&h[i]);
		sort(h+1,h+1+n);
		int minn=1e9+5;
		for(int i=2;i<=n;++i)	minn=min(minn,h[i]-h[i-1]);
		for(int i=2;i<=n;++i)
		{
			if(minn==h[i]-h[i-1])
			{
				printf("%d ",h[i-1]);
				for(int j=i+1;j<=n;++j)	printf("%d ",h[j]);
				for(int j=1;j<i-1;++j)	printf("%d ",h[j]);
				printf("%d",h[i]);
				puts("");
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：qfpjm (赞：0)

模拟赛这道题写炸了，写个题解散散心。

# 题解

- 先排序，找两个绝对值最相近的数，小一点的结果的开头，大一点的放结果的结尾。

- 然后贪心。剩下的数，大于结果开头的数按从小到大的顺序排在结果的开头后，在剩下的数排在这些数的结尾和结果的结尾之间。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int T, a[1000005];

int main()
{
	cin >> T;
	while (T --)
	{
		int n;
		scanf("%d", &n);
		for (int i = 1 ; i <= n ; i ++)
		{
			scanf("%d", &a[i]);
		}
		sort(a + 1, a + 1 + n);
		int anss1 = -1, anss2 = -1, minn = 1e9 + 1, idx1 = 0, idx2  = 0;
		for (int i = 2 ; i <= n ; i ++)
		{
			if (a[i] - a[i - 1] < minn)
			{
				anss1 = a[i - 1];
				anss2 = a[i];
				minn = a[i] - a[i - 1];
				idx1 = i - 1;
				idx2 = i;
			}
		}
		printf("%d ", anss1);
		for (int i = idx2 + 1 ; i <= n ; i ++)
		{
			printf("%d ", a[i]);
		}
		for (int i = 1 ; i < idx1 ; i ++)
		{
			printf("%d ", a[i]);
		}
		printf("%d\n", anss2);
	}
}
```


---

## 作者：Cripple_Abyss (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1537C)

## Description 
- 给定一个有 $n$ 个正整数的数列。

- 求一种排列第一个数与最后一个数绝对值最小且满足 $a_i>a_{i-1} (i>1)$ $i$ 的个数最多。

## Solution
- 这题很容易想到贪心算法。

- 先将给定数组从小到大排序，并找到 $st$ ( $st$ 为 $\min(a_i-a_{i-1})$ 的下标 $i$ )。

- 将剩下的数放进一个优先队列（小根堆），每次输出不重复的堆顶元素，直至优先队列为空。

## Code 
```cpp
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
inline void in(ll &x) {
	x=0;
	ll f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	x*=f;
}
inline void out(ll x) {
	if (x<0) putchar('-'),x=-x;
	if (x>9) out(x/10);
	putchar(x%10+'0');
}
const ll N=2e5+5;
ll T,n,a[N],la,st,_,ans,cnt;
priority_queue <ll,vector<ll>, greater<ll> >q1;
priority_queue <ll,vector<ll>, greater<ll> >q2;
int main() {
	in(T);
	while (T--) {
		in(n);
		for (ll i=1; i<=n; ++i) in(a[i]);
		sort(a+1,a+n+1);
		_=1e9+5;
		for (ll i=1; i<n; ++i)
			if (_>(a[i+1]-a[i]))
				_=a[i+1]-a[i],st=i;
		out(a[st]),putchar(' ');
		cnt=0;
		for (ll i=st+2; i<=n; ++i)
			if (a[i]!=a[i-1]) {
				out(a[i]),putchar(' ');
				a[i]=-1;
				cnt++;
			}
		ans=a[st+1];
		a[st]=a[st+1]=-1;
		for (ll i=1; i<=n; ++i) q1.push(a[i]);
		q1.pop();
		q1.pop();
		while (cnt--&&!q1.empty()) q1.pop();
		while (q1.size()+q2.size()) {
			la=-1;
			while (!q2.empty()) q1.push(q2.top()),q2.pop();
			if (q1.top()==la) q2.push(q1.top()),q1.pop();
			else {
				la=q1.top();
				out(la),putchar(' ');
				q1.pop();
			}
		}
		out(ans);
		putchar('\n');
	}
	return 0;
}


```

---

## 作者：_jimmywang_ (赞：0)


很明显这题分为两个部分：高度差最小、上升最多。

所以一个一个看：

### 1.高度差最小

首先，前后两山高度绝对值最小时，这两座山的高度必定在高度数组排好序后的数组内 **相邻**。

简单地说就是先将 $h$ 排序，得到新数组 $g$，$\min(h_1-h_n)=\min(g_i-g_{i-1})$。

然后遍历一遍找到最小值，再来一遍开始处理。

### 2.上升最多

对于 $g$ 数组内相邻且差最小的两个数，我们有两种方式来组合其他的山。

![](https://cdn.luogu.com.cn/upload/image_hosting/wbyhr4j9.png)

设数组 $c$，$c_1=0,c_i=\sum_{j=2}^{i}[g_j>g_{j-1}]$

这样计算法一的贡献为
$$c_{i-2}+c_n-c_i+[g_{i+1}>g_{i-1}]+[g_{i}>g_{i-2}]$$

法二的贡献为
$$c_{i-2}+c_n-c_i+[g_{i+1}>g_{i}]+[g_{i-1}>g_{i-2}]$$

然后就可以更新答案了！

代码：
~~~
// Problem: C. Challenging Cliffs
// Contest: Codeforces - Codeforces Round #726 (Div. 2)
// URL: https://codeforces.ml/contest/1537/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Author: tooler!
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll rd() {
	ll x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
#define d rd()
#define pb push_back
ll t,n;
ll a[200010],c[200010];
int main(){
	t=d;
	while(t--){
		ll n=d;
		f(i,1,n)a[i]=d;
		sort(a+1,a+n+1);
		ll mn=1e12,mx=-1,pos,m;
		f(i,2,n)c[i]=c[i-1]+(a[i]>a[i-1]),mn=min(mn,a[i]-a[i-1]);
		f(i,2,n)if(a[i]-a[i-1]==mn){
			ll x=c[i-2]+c[n]-c[i]+(a[i+1]>a[i-1])+(a[i]>a[i-2]);
			ll y=c[i-2]+c[n]-c[i]+(a[i+1]>a[i])+(a[i-1]>a[i-2]);
			if(mx<x)mx=x,pos=i,m=1;
			if(mx<y)mx=y,pos=i,m=2;
		}
		if(m==1){cout<<a[pos-1]<<" ";f(i,pos+1,n)cout<<a[i]<<" ";f(i,1,pos-2)cout<<a[i]<<" ";cout<<a[pos]<<endl;}
		if(m==2){cout<<a[pos]<<" ";f(i,pos+1,n)cout<<a[i]<<" ";f(i,1,pos-2)cout<<a[i]<<" ";cout<<a[pos-1]<<endl;}
	}
	return 0;
}
~~~

---

