# More Cowbell

## 题目描述

Kevin Sun wants to move his precious collection of $ n $ cowbells from Naperthrill to Exeter, where there is actually grass instead of corn. Before moving, he must pack his cowbells into $ k $ boxes of a fixed size. In order to keep his collection safe during transportation, he won't place more than two cowbells into a single box. Since Kevin wishes to minimize expenses, he is curious about the smallest size box he can use to pack his entire collection.

Kevin is a meticulous cowbell collector and knows that the size of his $ i $ -th ( $ 1<=i<=n $ ) cowbell is an integer $ s_{i} $ . In fact, he keeps his cowbells sorted by size, so $ s_{i-1}<=s_{i} $ for any $ i&gt;1 $ . Also an expert packer, Kevin can fit one or two cowbells into a box of size $ s $ if and only if the sum of their sizes does not exceed $ s $ . Given this information, help Kevin determine the smallest $ s $ for which it is possible to put all of his cowbells into $ k $ boxes of size $ s $ .

## 说明/提示

In the first sample, Kevin must pack his two cowbells into the same box.

In the second sample, Kevin can pack together the following sets of cowbells: $ {2,3} $ , $ {5} $ and $ {9} $ .

In the third sample, the optimal solution is $ {3,5} $ and $ {7} $ .

## 样例 #1

### 输入

```
2 1
2 5
```

### 输出

```
7
```

## 样例 #2

### 输入

```
4 3
2 3 5 9
```

### 输出

```
9
```

## 样例 #3

### 输入

```
3 2
3 5 7
```

### 输出

```
8
```

# 题解

## 作者：ChrisWangZi (赞：7)

首先，我们从枚举入手。

枚举 $s$ 从 $1$ 到 $a[n]$ （数组最大值）。

再用贪心法求所需盒子的数量。

（贪心的解法待会儿再讲）

## 但我们发现:**会超时.**
枚举 $O(\max(s[i]))$ ，验证 $O(n)$

~~不超时才怪~~



------------


我们又发现：**这符合二分答案的性质**（线性）

所以，就想到了二分。

二分，我们得先确定左指针和右指针的初始值。
（答案的区间）

答案一定会在 ``a[n]`` (最大的必须得装)和 ``a[n]+a[n-1]`` (不会又比它们更大的物品和)中。

所以，二分的主体就出来了。
```cpp
long long l=a[n],r=a[n]+a[n-1];
while(l<=r){
	long long mid=(l+r)/2;
	if(find(mid)){
			l=mid+1;
	}
	else{
		r=mid-1;
	}
}
cout<<l;
```


------------

接下来，我们看 $check$ 函数。

**贪心法：双指针。**

双指针，就是 $l$ 和 $r$ 两个下标。

先测试当前 $a[l]+a[r]$ 是否小于等于 $mid$ 。

若小于等于，则这两个物品放在一个盒子里；

否则，移动右指针，将右指针放一个盒子。

最后，返回 $ans>k$ (当前尺寸是否合法)。

检验函数：
```cpp
bool find(long long mid){
	int ans=0;
	int l=1,r=n;
	while(l<=r){
		if(a[l]+a[r]<=mid){
			l++;
			r--;
			ans++;
		}
		else{
			r--;
			ans++;
		}
	}
	return ans>k;
}
```
最后的最后，放一下完整的 $AC$ 代码。

$Code$:
```cpp
#include<iostream>
using namespace std;
int a[100005];
int n;
int k;
bool find(long long mid){
	int ans=0;
	int l=1,r=n;
	while(l<=r){
		if(a[l]+a[r]<=mid){
			l++;
			r--;
			ans++;
		}
		else{
			r--;
			ans++;
		}
	}
	return ans>k;
}
int main(){
	cin>>n;
	cin>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	long long l=a[n],r=a[n]+a[n-1];
	while(l<=r){
		long long mid=(l+r)/2;
		if(find(mid)){
			l=mid+1;
		}
		else{
			r=mid-1;
		}
	}
	cout<<l;
	return 0;
}
```

（**这是本蒟蒻第一篇题解，欢迎大家指出我的问题。**）

望管理员能审核通过！

~~点个赞再走呗~~

---

## 作者：Eroded (赞：2)

本蒟蒻第一篇题解，如果写的不好望指出。

这题明显是二分答案，所以本蒟蒻用 $l$ 和 $r$ 来确定二分边界，写一个 check 函数来完成当前枚举的 $l$ 和 $r$ 的中间数 $mid$ 能否完成任务，最后输出 $mid$ 的最小值即可。

check 函数是一个贪心，定义两个指针 $l$ 和 $r$ （注意与上文的 $l$ 和 $r$ 不同）指向数组的头和尾和一个变量 $s$ 记录需要的箱子数，让 $r$ 从后往前搜索，判断每次搜索到的 $r$ 与 $l$ 所在的值加起来是否小于当前的 $mid$ ，如果是则让 $l$ 指向下一个元素，无论是不是都要将 $s$ 加 $1$ ，最后判断 $s$ 和 $k$ 的大小，如果 $s \geqslant k$ 则这次任务完成。

时间复杂度 $O(n\log 2000001)$ ，即 $O(n)$ ，对于这道题绰绰有余。

我的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100100],k,n,ans;
bool check(int x){
	int l = 1,s = 0;
	for(int r = n;l <= r;r--){
		if(l < r && a[l] + a[r] <= x){//l和r如果相等，l也不用加1
			l++;
			s++;
		}
		else s++;
	}
	if(s <= k) return 1;
	return 0;
}
int main(){
	cin>>n>>k;
	for(int i = 1;i <= n;i++){
		cin>>a[i]; 
	}
	int l = a[n],r = 2000001;//r不能太大
	while(l < r){//二分查找
		int mid = (l + r) / 2;
		if(check(mid)){//判断
			ans = mid;
			r = mid;//这里r不能为mid-1而要为mid
		}
		else l = mid + 1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Ruizll (赞：1)

### 这道题是一道典型的二分
   整体思路：先不管有几个盒子，将左端点设置成整个数组中最大的内个数，将右端点设置成整个数组所有数的和，将值传入用来计算盒子数的函数判断是否符合我们有的盒子数，如果符合返回值，与中间值进行二分，最后输出就完成了

## 就是这么简单，上代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 1e5 + 10;

LL a[N];
LL sum;//数组数总和
LL n, m;
int check(LL mid){
    int cnt = 0;//需要的盒子数
    int s = 0, e = n - 1; 
    while(s <= e){
        if(e != s && a[e] + a[s] <= mid){
            cnt++;
            s++;
            e--;
        } else {
            cnt++;
            e--;
        }
    }//计算所需盒子数
    return cnt;
}

int main()
{

    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        sum += a[i];
    }
    LL l = a[ n - 1], r = sum;
    while(l <= r){
        LL mid = (l + r) / 2;
        if(m >= check(mid)){
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }//经典二分
    cout << l << endl;
    return 0;
}
```


---

## 作者：Fearliciz (赞：1)

其实这题可以不用二分答案做。

#### 解题思路：

1. 用一个数组存储牛铃的尺寸。

2. 当 $n \le k$ 时，长度为 $n$。

3. 当 $n > k$ 时，将多出来的 $k-n$ 牛铃和前面的 $n$ 个配对，取最大值即可

注意：因为下标从 $1$ 开始，所以结束下标时 $k-n+1$ 开始。

所以代码写起来就很简单了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001];
int main()
{
   	int n, k;
   	cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int minn = a[n];
    for (int i = 1; i <= n - k + 1; i++) minn = max(minn, a[i] + a[(n - k + 1) * 2 - i - 1]); //这个地方很巧妙，减去 i 去重。
    cout << minn;
    return 0;
}
```


---

## 作者：chlchl (赞：1)

## 注意

此题被人加了 hack 数据，好多题解代码是错的，这份题解保证正确（因为我是在加了数据之后过的）。

## 题目意思
题目翻译说的很清楚，大家先去看题，不要着急看题解。

这里只补充一个点：

``只要牛铃的大小不超过盒子大小 s ，他可以把 1 个或者 2 个牛铃塞进大小刚好为 s 的盒子里。``

注意，不是每个牛铃大小不超过 $s$ 就行，而是**总大小**！

## 算法及思路
本题为一道~~毒瘤的~~经典的**二分 + 贪心**题。

贪心算法应该不用我讲，基本上约等于暴力（可以理解为**有策略和经过脑子思考的暴力**）。

至于二分，可以[点这](https://www.luogu.com.cn/blog/hugocaicai/solution-p7766)看看算法介绍及实现。

废话不多说，开始这道题的思路讲解。

思路
------------
在讲思路前，大家需**对贪心和二分有基础的了解**（这里我默认大家都会这两种算法了，不会看上面）。

首先，**主要算法是二分**。直接通过**二分枚举 $s$ 的大小**（后面代码为 $ans$）。
- 左边界 $l$ 应该为**输入的最后一个元素**（即代码里的 $a_n$）。因为如果小于 $a_n$，**那 $a_n$ 就装不下任何一个箱子**。再小，也要有个界限。
- 右边界 $r$ 应该为**无限大**，这里我设成了 $10^9$，如果 $r$ 不够大，可能导致**有部分答案枚举不到，造满江红的情况**。
- 每次用 check 函数检查后，如果该答案符合条件，则更新 $ans$。
- 最后输出 $ans$ 即可。

以上不是重点，重要的地方在**贪心**，它用在了 check 函数里，**这也是 hack 数据的毒瘤之处。**

对于贪心，为了让**盒子总数尽量小**，应该让**两个牛铃的箱子数量尽量多**，这个是一定正确的。

我一开始的思路是**直接用最大的跟最小的匹配，次大的跟次小的匹配**……以此类推，最后看看**箱子数量是否大于当前枚举到的盒子数量**，小于等于返回 $1$，否则返回 $0$。

这个代码打出来，你只能对 $2$ 个点。

我们来看样例 $3$：
```
输入：
3 2
3 5 7
输出：8
```
如果按照刚刚的思路，输出结果应该是 $10$。

到底错在了哪里？

题目解释已经给出来了，**最佳搭配应该是 $(3,5)$，$(7)$，并不是$(3,7)$，$(5)$。**

所以，正确的思路应该是：如果**当前最大和最小的匹配不上**，应该让**最大的那个单独放一个箱子**（因为如果**最小的跟最大的都超了，其他跟最大肯定也超了**）。

你以为这道题到这就结束了？

看看题目数据：$1\leq n \leq 2⋅k\leq 100000$。所以，需要 $O(n)$ 的复杂度。

先定义一个**左指针和一个右指针**。如果两个牛铃匹配成功，则**左指针   $+1$，右指针 $-1$。**如果超过箱子容量，则右指针 $-1$。当**左指针等于右指针**时，证明所有牛铃全部匹配成功，判断箱子数量即可。

其他细节，代码里大家自己看吧。

## 一些小坑
1. 最后输出既不是 $l$，也不是 $r$，而是 $ans$。
2. check 函数如果 $O(n^2)$，你就会 Time Limit Enough（时间“充裕”），简称 TLE。
3. 注意上面思路部分提到的毒瘤。

## 代码
代码仅供参考。珍爱生命，远离抄袭。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 100000 + 10;
int n, k, l, r, ans, mid, a[N];

bool check(int x){
	int l = 1, r = n, cnt = 0;
	//l, r左右指针，cnt箱子个数 
	while(l <= r){
		if(x >= a[l] + a[r] && l != r){
			l++, r--, cnt++;//匹配成功 
		}else if(x < a[l] + a[r] && l != r){
			r--, cnt++;//匹配不上，把较大的放进箱子里（不用判断，r一定不小于l） 
		}else if(l == r){
			l++, cnt++;//特判一下，细心的童鞋发现了，这其实是最后一个了（l <= r） 
		}
	}
	if(cnt > k)	return false;//如果大于了，返回错误 
	return true;//否则返回正确 
}

int main(){
	cin >> n >> k;
	for(int i=1;i<=n;i++)	cin >> a[i];
	l = a[n], r = 1e9;//因为输入保证序列不下降，所以a[n]一定是最大的 
	while(l <= r){
		mid = (l + r) / 2;//枚举箱子大小 
		if(check(mid)){
			ans = mid;//更新答案 
			r = mid - 1;//考虑能不能再小点 
		}
		else	 l = mid + 1;//太小了，大点 
	}//二分过程不解释，不懂的点上面链接 
	cout << ans << endl;
	return 0;//成功hack掉hack数据 
}
```
本篇题解到此结束，如果对你有帮助，别忘了点个赞哦！

---

## 作者：xu222ux (赞：0)

# [More Cowbell](https://www.luogu.com.cn/problem/CF604B)

## 解法

不知道为什么大家都用二分。我的思路是贪心。

会发现一个整数整个数组的长度如果小于 $2\times k$，那么我就可以单拿出一个箱子来装目前最大的。重复以上动作直到 $2\times k\le$ 数组长度。

其余的呢？

最大的和最小的相加。

第二大的和第二小的相加。

......

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int a[100005];
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    int ans=a[n];
    for(;n>=1;n--){
        if(k*2>n)k--;
        else break;
    }
    for(int i=1;i<=n/2;i++){
        ans=max(ans,a[i]+a[n-i+1]);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：ACtheQ (赞：0)

本题是一道非常模板的二分题。

二分答案模板：

```
while(l<=r)
{
	int mid=(l+r)>>1;
	if(check(mid,x,k))
   {
		r=mid-1;
		ans=mid;
	}
	else l=mid+1;
}
cout<<ans<<endl;

```

那我们来研究下 `check` 函数。

如果，它这个箱子能够装两个牛铃，就让最小的和最大的装进去。

否则，让最大的装。

```c++
	while(l<=r)
	{
		if(a[r]>x) return false;
		if(a[l]+a[r]<=x)
		{
			l++;
			r--;
			ans++;
		}
		else
		{
			r--;
			ans++;
		}
	}
```
如果，它一个都装不进去，那肯定是错的。

如果满足 $ans>k$ 说明不够，要更大的箱子。

否则，可能会存在更小的。

所以答案是 $l$。

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5; 
int a[N];
int n,k;
bool check(int x)
{
	int ans=0;
	int l=1,r=n;
	while(l<=r)
	{
		if(a[r]>x) return false;
		if(a[l]+a[r]<=x)
		{
			l++;
			r--;
			ans++;
		}
		else
		{
			r--;
			ans++;
		}
	}
	return ans>k;
}
signed main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    int l=a[n],r=a[n]+a[n-1];
    while(l<=r)
    {
        int mid=(l+r)/2;
		if(check(mid)) l=mid+1;
		else r=mid-1;
    }
    cout<<l;
    return 0;
}
```

---

## 作者：王熙文 (赞：0)

### 思路：

这道题我用了两种方法做：

* $\text{Solution} \ 1$：

  考虑二分，二分最小的 $s$，`check` 函数里面就是[这道题](https://hdnoip.com/problem/P1728)了。`check` 函数的写法：若当前每个盒子的容量为 $w$，定义两个指针 $l,r$，最开始 $l=1,r=n$。循环，如果 $l \lt r$ 就执行。如果 $a_l+a_r \le w$，说明它们可以配对，将 $l \gets l+1,r \gets r-1$；否则 $a_r$ 只能自己放到一个盒子里，$r \gets r-1$。每一次需要的盒子个数都加一。当退出循环，还有一个牛铃的时候（$l = r$），就需要将个数再加一，否则不用加。最后判断一下使用的个数是否小于等于 $k$ 就行了。

  注意：二分答案最初的 $l$ 应为数组中最大的值，$r$ 应为数组的总和。

* $\text{Solution} \ 2$：

  设 $m$ 为需要两两配对的对数，那么 $k-m$ 则是单个放到盒子里的个数。可以列出以下方程：$2 \times m + (k-m) = n$。解得 $m=n-k$。所以一共有 $2 \times m = 2 \times (n-k)$ 个数是需要两两配对的，剩下的数单放到一个盒子里。显然先让小的数两两配对，让大的数放到单个盒子。两两配对的最优解是这样的：$a_1$ 和 $a_{2 \times (n-k)}$，$a_2$ 和 $a_{2 \times (n-k)-1}$，$a_3$ 和 $a_{2 \times (n-k)-2}$，等等，直到 $a_{n-k}$ 和 $a_{n-k+1}$。那么可以枚举这些配对需要的容量，求最大值就可以了。

  注意：单个盒子也有可能容量是最大的，所以最开始（还没有循环配对更新）的最大值应为 $a_n$。



### 参考代码：

* $\text{Solution} \ 1$：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,k;

int a[100010];

bool check(int x)
{
	int l=1,r=n,cnt=0;
	while(l<r)
	{
		if(a[l]+a[r]<=x) ++l,--r;
		else
		{
			if(a[r]>x) return 0;
			--r;
		}
		++cnt;
	}
	if(l==r)
	{
		if(a[l]>x) return 0;
		++cnt;
	}
	return cnt<=k;
}

signed main()
{
	scanf("%lld%lld",&n,&k);
	int l=1,r=0,ans,mid;
	for(int i=1; i<=n; ++i)
	{
		scanf("%lld",&a[i]);
		r+=a[i];
	}
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(mid))
		{
			r=mid-1;
			ans=mid;
		}
		else l=mid+1;
	}
	printf("%lld",ans);
	return 0;
}
```

* $\text{Solution} \ 2$：

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[100010];

signed main()
{
	int n,k,ans=0;
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	ans=a[n];
	for(int i=1; i<=n-k; ++i) ans=max(ans,a[i]+a[2*(n-k)-i+1]);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：NSOI (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF604B)

这道题蛮简单的，居然没人写题解……

# 分析

这道题是一个明显的二分答案，枚举 $l,r(l≤r)$ ,然后定义一个函数 check，用于检查每一个 l,r 是否能把所有的牛玲装进去。

check 函数其实是一个贪心，枚举 $i,j(1≤i≤n$ 且 $n≥j≥i≥1)$ 尽量使得最大和最小的牛玲放在一起。

代码：
```c
#include<bits/stdc++.h>
using namespace std;
const int MAXN=105;
int n,a[MAXN],big,k,ans,b[MAXN];
bool check(int l){
	memset(b,0,sizeof(b));
	int cnt=0,sum=0;
	for(int i=1;i<=n;i++){
		for(int j=n;j>=1;j--){
			if(sum>k)break;
			if(cnt==n)return true;
			if(l>=a[i]+a[j]&&i!=j)sum++,cnt+=2;
			else if(l>=a[i]&&i==j)sum++,cnt++;
		}
	}
	return false;
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		big=max(big,a[i]);
	}
	int l=big,r=1000001,mid;
	while(l<r){
		mid=(l+r)/2;
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}else l=mid+1;
	}
	printf("%d",ans);
	return 0;
}
```


---

