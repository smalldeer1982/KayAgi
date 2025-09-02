# Number of Pairs

## 题目描述

给出一个由整数组成的数组 $a$，求一对整数 $(i, j)$（$1 \le i < j \le n$）满足 $l \le a_i + a_j \le r$ 的数量。

## 样例 #1

### 输入

```
4
3 4 7
5 1 2
5 5 8
5 1 2 4 3
4 100 1000
1 1 1 1
5 9 13
2 5 5 1 1```

### 输出

```
2
7
0
1```

# 题解

## 作者：王大神——A001 (赞：6)

[传送门](https://www.luogu.com.cn/problem/CF1538C)
### 题目大意

给一个数列和 $l$，$r$ 两个数，问在序列中的两个数的和有多少个在 $[l,r]$ 的区间中。

------------

### 思路
首先，我们要对这个序列从小到大排序。然后思考，我们从序列最小的数开始遍历，从最大的数开始逆着遍历，两者加和如果小于等于 $r$ 开始计数，这样我们的右边界就处理好了。

接着是左边界，我们刚刚计数记的是小于等于 $r$ 的数的个数，其中包括了小于 $l$ 的数量，所以我们可以再计一次，计小于 $l$ 的数量，这次计的数要减掉，因为他们不符合题意。

------------

### 细节优化
遍历的时候因为是两个数的加和，在考虑边界的时候要注意 $l<r$，当加和时左右边界相遇时可以直接跳出循环。

**注意：**

在计右边边界时，要加上计的数。在计左边界时，要减去计的数。

------------

### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm> 
#include<cmath>
using namespace std;
int t,n;//t组数据 n个元素 
int a_a[200001];//存储元素 
int l,r;//左右边界 
void get_ans(){
	long long ans=0;//结果 
	for(int i=0,j=n-1;i<j;i++){//右边界遍历 
		while(i<j&&a_a[i]+a_a[j]>r)j--;//寻找加和小于r的右边界 
		if(j-i<0)break;//跳出循环 
		ans+=j-i;
	}
	for(int i=0,j=n-1;i<j;i++){//左边界遍历 
		while(i<j&&a_a[i]+a_a[j]>=l)j--;
		if(j-i<0)break;
		ans-=j-i;
	}
	cout<<ans<<endl;//输出结果 
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d %d %d",&n,&l,&r);
		for(int i=0;i<n;i++)scanf("%d",&a_a[i]);
		sort(a_a,a_a+n);//从小到大排序 
		get_ans();
	}
	return 0; 
}
```


---

## 作者：Aehnuwx (赞：4)

暴力的思路显然是枚举所有的 $(i,j)$

但 $O(n^2)$ 的复杂度显然不能接受

考虑优化

先对 $a$ 数组升序排序

顺序枚举 $i$

找到满足 $a_i+a_{l_0}\ge l$ 的最小 $l_0$ 与满足 $a_i+a_{r_0}\le r$ 的最大 $r_0$

显然 $\forall j\in [l_0,r_0],(i,j)$ 为一组合法数对

则答案加上 $r_0-l_0+1$ 即可

时间复杂度即优化为 $O(n\log n)$

代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<climits>

using namespace std;

#define ll long long
const int maxn=200005;
int a[maxn];

int main(){
  int t=1; scanf("%d",&t);
  while(t--){
  	int n,l,r;
  	scanf("%d%d%d",&n,&l,&r);
  	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
  	sort(a+1,a+n+1);
  	a[n+1]=INT_MAX;
  	ll ans=0;
  	for(int i=1;i<=n;i++){
  		int l0=lower_bound(a+i+1,a+n+2,l-a[i])-a;
  		int r0=upper_bound(a+i+1,a+n+2,r-a[i])-a;
  		r0--;
  		if(l0>r0) continue;
  		ans+=r0-l0+1;
  		//printf("%lld ",ans);
  	}
  	printf("%lld\n",ans);
  }
  return 0;
}

```



---

## 作者：LinkZelda (赞：3)

- **题意**：

$t$ 组询问，每次给定一个长度为 $n$ 的序列 $a$，和两个数 $l,r$ ，求满足 $1\leq i<j\leq n,l\leq a_i+a_j \leq r$ 的数对 $(i,j)$ 的个数。

$t\leq 10^4,n\leq 2\times 10^5,a_i\leq 10^9,\sum n\leq 2\times 10^5,l,r\leq 10^9$。

- **做法**：

考虑转化问题，对于每个 $a_i$，实际上要求的是 $j>i,l-a_i\leq a_j\leq r-a_i$ 的个数。那么其实这个个数可以差分为 $\leq r-a_i$ 的数的个数减去 $< l-a_i$ 的个数。

所以我们要实现一个数据结构支持插入，删除，查询全局内 $<k$ 的数的个数。这里我采用了 `fhq treap` 来实现，具体参见代码。时间复杂度为 $O(n\log n)$。

- [代码](https://www.luogu.com.cn/paste/u4wwn4j1)

---

## 作者：Wuyanru (赞：3)

[题目](https://www.luogu.com.cn/problem/CF1538C)

题目大意：给出 $ t $ 组数据，每组数据给定一个含有 $ n $ 个数的正整数序列 $ a $ 以及 $ l $ 和 $ r $ 两个数字，求有多少个 $ \left(i,j\right) $ 满足 $ 1\le i < j \le n $ 和 $ l\le a_i+a_j\le r $,输出值。

如果暴力枚举 $ i $ 和 $ j $ 两个数，时间复杂度为 $ \Theta\left(tn^2\right) $,显然会超时。

下面考虑正解。

我们可以先将 $ a $ 进行排序，让它变为单调非降的序列。

如果这样，那么对于每一个 $ i $,满足的 $ j $ 肯定是连续的一段，二分确定这个区间的左端点与右端点即可，时间复杂度为 $ \Theta\left(tn\log_2^n\right) $。

然而也有几个细节：

1.  如果有 $ i $ 满足 $ l\le2\times a_i\le r $,那么就会重复计算一次答案，所以应该在二分以前将这种答案减去；

2.  如果有 $ \left(i,j\right) $ 满足题目的条件，那么计算答案时也会将 $ \left(j,i\right) $ 计算一次，所以在输出时要将答案除以 $ 2 $；

3.  `十年OI一场空，不开 long long 见祖宗`。

AC 代码：

```
#include<algorithm>
#include<cstdio>
using namespace std;
int a[200001];
int n,t,l,r;
int cal2(int ans) {
	if(ans+a[1]>r)
		return n+1;
	int num=0;
	for(int i=1048576; i; i>>=1)
		if(i+num<=n&&a[i+num]+ans<l)
			num+=i;
	return num+1;
}
int cal1(int ans) {
	if(ans+a[n]<l)
		return 0;
	int num=0;
	for(int i=1048576; i; i>>=1)
		if(num+i<=n&&a[num+i]+ans<=r)
			num+=i;
	return num;
}
int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d%d%d",&n,&l,&r);
		long long ans=0;
		for(int i=1; i<=n; i++) {
			scanf("%d",a+i);
			if(l<=a[i]*2&&a[i]*2<=r)
				ans--;
		}
		sort(a+1,a+n+1);
		for(int i=1; i<=n; i++)
			ans+=max(cal1(a[i])-cal2(a[i])+1,0);
		printf("%lld\n",ans/2);
	}
	return 0;
}
```

感谢观看！

---

## 作者：lalaji2010 (赞：1)

# CF1538C

## 分析

首先，我们考虑暴力求解。我们可以暴力枚举 $i$ 和 $j$，并将其与 $l$ 
和 $r$ 进行比较得出答案。时间复杂度：$O(n^2)$。

再考虑优化，我们知道，优化枚举的最好办法就是**二分**，又因为这道题只需要保证找到的 $i \neq j$，所以我们二分所需要的单调性可以通过排序来实现。

排好序后，二分找到当前 $i$ 所对应的下标最小的可行的 $j$ 和下标最大的可行的 $j$，则找到的两个下标区间内的元素，均能与 $i$ 完成配对。

最后，根据分析计数即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int q,n,s,t,a[200005];
int main(){
	cin>>q;
	while(q--){
		long long ans=0;//不开long long见祖宗 
		cin>>n>>s>>t;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		sort(a+1,a+1+n);
		for(int i=1;i<n;i++){//1 2 3 4 5  5~8
			int l=i,r=n,mid,ansl,ansr;
			while(l<r){
				mid=(l+r)>>1;
				//cout<<mid<<"  ";
				if(a[i]+a[mid]>=s){
					r=mid;
				}else{
					l=mid+1;
				}
			}
			ansl=l;
			l=i,r=n;
			while(l<r){
				mid=(l+r+1)>>1;
				//cout<<mid<<" ";
				if(a[i]+a[mid]<=t){
					l=mid;
				}else{
					r=mid-1;
				}
			}
			ansr=l;
			//cout<<ansl<<" "<<ansr<<"\n";
			if(ansl==i){
				ansl++;
			}
			if(ansl>=ansr&&(a[i]+a[ansr]<s||a[i]+a[ansl]>t)){
				continue;
			}
			ans+=ansr-ansl+1;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：123hh2 (赞：1)

--->[传送门](https://www.luogu.com.cn/problem/CF1538C)

### 前言
~~蒟蒻又来水题解啦~~

这道题原先交的时候 UKE 了，自己也没再重写一遍，今天刚好看到了，所以就来写一发

---

### 题目大意

多测，每次给你 $n(n \le 2 \times 10^5)$，$l$，$r$，以及长度为 $n$ 的序列 $a$，让我们求一对整数 $(i,j)(1 \le i < j \le n)$，使得 $l \le a_i + a_j \le r$ 

---
### 思路

上来先打一个暴力，即依次枚举所有可能的 $(i,j)$ 组合，然后符合条件的就让答案 +1。这样子的做法肯定是对的但 $O(n^2 t)$ 肯定跑不过去的，于是我们考虑一下如何优化一下暴力算法

**优化一**

既然我们要枚举 $(i,j)$，我们可以考虑用 sort 将数组排列成一个单调递增的数组，这样当我们枚举的时候，碰到 $i+j > r$ 的时候就可以退出了。但根据个人实践表明，还是过不去

**优化二**

考虑到我们既然已经将数组搞成一个有序的了，所以我们可以用二分来搞

我们需要找两个端点值，使得这个区间内的所有数都符合要求，那么我们只需要将两个端点值的差值 +1 加到答案里，然后这里二分的时候偷个懒用了 STL 里的 upper_bound 和 lower_bound，所以在计算的时候，我们只需要将两端点差值加到答案里就好了。

要是你不清楚他们怎么用，可以 [戳这里](https://blog.csdn.net/qq_40160605/article/details/80150252)

---

### 代码
这个代码长度非常好哇 [888B](https://www.luogu.com.cn/record/51998321)
```cpp
#include<bits/stdc++.h>
#define int long long
#define in inline
#define ri register
#define _123hh2 0
using namespace std;
in int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
in void write(int x)
{
    if(x<0) {x=-x;putchar('-');}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int maxn=2e5+1;
int awa[maxn];
signed main()
{
    cin.tie(NULL);cout.tie(NULL);
    int t=read();//多测 
    while(t--)
    {
    	int n=read(),l=read(),r=read(),ans=0;
    	for(ri int i=1;i<=n;i++) awa[i]=read();
    	sort(awa+1,awa+1+n);
    	for(ri int i=1;i<=n;i++)
    	{
    		int ls=lower_bound(awa+1+i,awa+1+n,l-awa[i])-awa;
    		int rs=upper_bound(awa+1+i,awa+1+n,r-awa[i])-awa;
    		ans+=rs-ls;
		}
		write(ans);puts("");
	}
    return _123hh2;
}
```


---

## 作者：luojien (赞：0)

## 题目分析

这是一个很简单的数学题，就是通过 `lower_bound` 和 `upper_bound` 过滤出相加之后在 $[l, r]$ 之间的数组区间，再通过 $end-begin+1$ 的方式算出长度并加到 $ans$ 中。

一定要开 `long long`！一定要开 `long long`！

## 的代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e5 + 5;
int a[N];
int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int n, l, r;
		cin >> n >> l >> r;
		for(int i = 1; i <= n; i++)
		{
			cin >> a[i];
		}
		a[n + 1] = 2e9;
		sort(a + 1, a + n + 1);
		long long ans = 0;
		for(int i = 1; i <= n; i++)
		{
			int x = lower_bound(a + 1 + i, a + n + 2, (l - a[i])) - a;
			int y = upper_bound(a + 1 + i, a + n + 2, (r - a[i])) - a;
			y--;
			if(x > y) continue;
			ans += (long long)(y - x + 1);
		}
		cout << ans << endl; 
	}
	return 0;
}
```

---

## 作者：nyC20 (赞：0)

# 思路
暴力算法肯定会超时，所以此处不考虑。很显然这道题要优化，我首先想到的是排序加剪枝：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, l, r, ans, a[200003];
int main() {
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&l,&r);
		ans=0;
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		sort(a+1,a+1+n);
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				if(a[i]+a[j]>=l&&a[i]+a[j]<=r)ans++;
				if(a[i]+a[j]>r||a[i]+a[n]<l)break;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```
然后在第四个点超时了。

于是想到二分，对于每一个 $i$，分别二分找到 $a_i$ 作为左右端点时另一边端点的最远位置，然后用两个值相减，累加答案即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long t, n, l, r, ans, a[200003], l_, r_;
int main() {
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld%lld",&n,&l,&r);
		ans=0;
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		sort(a+1,a+1+n);
		a[n+1]=0x3f3f3f3f;
		for(int i=1;i<=n;i++){
			l_=lower_bound(a+i+1,a+n+2,l-a[i])-a;
  			r_=upper_bound(a+i+1,a+n+2,r-a[i])-a;
  			if(l_>r_)continue;
  			ans+=r_-l_;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

