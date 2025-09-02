# 有給休暇（Paid Vacation）

## 题目描述

Joisino 姐姐非常喜欢长假。

现在，已经知道了接下来的 $n$ 天是否是休息日。

Joisino 姐姐可以把最多 $k$ 个非休息日改为休息日。

Joisino 姐姐想知道可能的最长连续休息日的长度。

## 样例 #1

### 输入

```
6 2
1 0 1 0 0 1```

### 输出

```
4```

## 样例 #2

### 输入

```
10 1
1 1 0 0 1 1 1 0 1 1```

### 输出

```
6```

# 题解

## 作者：DFs_YYDS (赞：5)

借鉴了[Ethan812820的题解](https://www.luogu.com.cn/article/yx3xkrp4)，但是代码是我自己写出来的，思路也更清晰一些。
## 题目大意
给你 $n$ 个数，问如何将这 $n$ 个数中的 $k$ 个 $0$ 变成 $1$，使最长的连续一段 $1$ 的数量最多。

## 具体思路
考虑使用双指针。两个分支：  
1. 若还能继续将 $0$ 变为 $1$，即 $k \ne 0$，则尝试将第 $r$ 个数变成 $1$。当然，如果第 $r$ 个数本来就是 $1$，就不需要减少次数。但是如果第 $r$ 个数为 $0$，需要减少次数，要将 $k$ 减一，最后 $r$ 加一，别忘了更新 $ans$。
2. 若不能继续将 $0$ 变为 $1$，即 $k = 0$，则尝试将第 $l$ 个数变回原来的样子，如果第 $l$ 个数原本就是 $1$。$k$ 不变，如果第 $l$ 个数原来是 $0$，要把变化的次数加回去，$k$ 加一，最后 $l$ 加一。

## 完整代码
代码来咯！
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
long long a[100005],sum,ans,l=1,r=0;
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];//读入a[i]。 
	}
	while(r<=n){
		if(sum<=k){//如果变换的次数小于等于k。 
			ans=max(r-l+1,ans);//判断是否需要更新ans。 
			r++;//右指针+1。 
			if(a[r]==0) sum++;//变换的次数+1。 
		}
		else{
			if(a[l]==0) sum--;//变换的次数-1。 
			l++;//左指针+1。 
		}
	}
	cout<<ans;
	return 0;
}
```
时间复杂度 $O(n)$，应该是优于二分的，而且比较好想。  
感谢观看！

---

## 作者：Louis_lxy (赞：3)

# 题目：AT_tkppc2016_c 有給休暇（Paid Vacation）

## 思路

首先看到这道题目，第一眼想到暴力，双重 for 循环枚举判断，统计最大值。但是！看到数据范围 $1 \leq N \leq10^5$，至少是 $O(n~\log_2~n)$ 才有可能过啊！而用前缀和优化过后还是 $O(n^2)$，洛谷评测机跑 $10^8$ 都够呛，$10^{10}$ 根本跑不完啊，绝对 TLE。

那么，我们想一想学过的算法中，哪一种算法可以处理区间呢，答案是双指针，没学过的可以百度或者去b站搜，提供一个个人认为不错的 [文章](https://www.cnblogs.com/luwei0424/p/17810978.html)，或者这个 [视屏](https://www.bilibili.com/video/BV1Gj411a7Jj/?spm_id_from=333.337.search-card.all.click)，这两个都是讲了快慢指针和双向指针的，比较全面，那么为什么双指针是可以过的呢，因为快指针和慢指针都只是走完了全程，没有多走，而且每次都必定会让慢指针移动，所以总的时间复杂度就是 $O(n)$。

既然已经知道了用双指针算法，那么要用那种呢（指快慢指针和双向指针），分析题意，如果我们用快慢指针，判断这个框选的区间内个数是否小于 $k$ 的话，可以发现，是可以实现的（具体方法后面介绍），但是如果用双向指针，一下子就框柱整个区间，可以发现，很难得到最优解（是可以得到一个答案但不一定最优），那么确定了算法，就可以开始具体分析了。

首先，定义一个慢指针 $l$ 一直往前跑，然后定义一个快指针 $r$，至于为什么 $r$ 是快指针是因为我们框定的区间是 $[l,r]$，那么我们当然要找到从 $l$ 开头的最大的区间和啊！记住由于双指针只能框定区间，不能确保最大值，所以要在所有的以 $l$ 为开头的区间中取最大值。

然后，写好模版。

```cpp
while (l < r)
{
	l++;
	while (条件)
		++r;
	maxn = max(maxn, r - l);
}
```

接着，我们来分析一下条件。因为要保证 $[l,r]$ 这个区间的和不能大于 $k$，所以第一个条件是 `sum[r] - sum[l - 1] <= k`（$sum$ 为前缀和数组），然后，我们知道快指针再快也不能飞出去这个数组啊，所以第二个条件是 `r <= n`，只有同时满足这两个条件才能 `++r`。

那么我们就写完了双指针的部分。

```cpp
while (l < r)
{
	l++;
	while (sum[r] - sum[l - 1] <= k && r <= n)
		++r;
	maxn = max(maxn, r - l);
}
```

然后再讲一个细节，读入的时候，记得用异或运算取反，因为要求的是原本不放假的天数而不是放假的天数。

最后再给不了解前缀和的萌新们科普一下这道题怎么用前缀和优化。定义 $sum_i$ 表示前 $i$ 天总共有多少个不放假的天数，那么状态转移方程就是 $sum_i=sum_{i-1}+a_i$，另外 $a$ 数组可以不用开，直接用 bool 变量代替就行了，直接替换到 $a_i$ 的位置就行了，那么求 $[l,r]$ 这个区间内的不放假天数就是 $sum_r - sum_{l-1}$，具体见代码。

## ACCODE

```cpp
#include <iostream>
using namespace std;

int n, k, sum[100001], maxn, l, r = 1;//sum是前缀和数组，sum[i]表示1~i天有多少天是不放假的
bool tmp;//输入用

int main()
{
	cin >> n >> k;
	for (int i = 1; i <= n; ++i)
		cin >> tmp, tmp ^= 1, sum[i] = sum[i - 1] + (int)tmp;//记得对输入数据用异或取反！
	while (l < r)//双指针模版，思路已经讲的很清楚了吧
	{
		l++;
		while (sum[r] - sum[l - 1] <= k && r <= n)
			++r;
		maxn = max(maxn, r - l);//取最大值
	}
	cout << maxn;
}
```

---

## 作者：2018g20 (赞：2)

## [传送门](https://www.luogu.com.cn/problem/AT_tkppc2016_c)

### 题意大概：
将一串有 $n$ 个 $0$ 或 $1$ 的数组中任意 $k$ 个 $0$ 改成 $1$ ，求出最长连续的 $1$ 串的长度。

### 思路：
由于求的是连续性子串长度，所以想到尺取。

先用前缀和累计 $0$ 的个数，每次让左指针前进一个数，再维护区间内 $0$ 个数始终为 $k$ 个，因为维护完的区间是符合题意的，所以比较取最大值。

### 代码：
```cpp
#include<iostream>
using namespace std;
int n,k,l,r=1,maxx;
int a[100003];
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		a[i]^=1;//将0改成1
		a[i]+=a[i-1];//前缀和
	}
	while(l<=n&&r<=n)
	{
		l++;//前进
		while(a[r]-a[l-1]<=k&&r<=n) r++;//要点1，2
		maxx=max(maxx,r-l);
	}
	cout<<maxx;
}
```

### 补充：
要点1：因为在 `a[r]-a[l-1]<=k` 中的 `=` 所以会导致循环结束时， `a[r]-a[l-1]` 是要大于 `k`的，且刚好比预想值大 $1$ ，那么区间长度就是 `(r-1)-l+1` ,即 `r-l` .

要点2：如果 `while` 中是 `r<n`  的话，在循环结束时，`r` 不会超过 `n` 的，上面说过， `r` 是要比预想直大 $1$ 的，所以当区间结尾在最后一个时答案就会少 $1$ ，加上 `=` 是刚刚好的。

---

## 作者：Kvaratskhelia (赞：2)

**题目大意**

有一个长为 $n$ ，只有 $0$ 和 $1$ 的数组，问将 $k$ 个 $0$ 修改成 $1$ 后，最长的连续 $1$ 的长度是多少。

**分析**

观察这个 $n$ 是小于十万的，而且是属于连续性问题，所以可以想到二分。

考虑二分最长的连续长度，假设当前所二分的长度为 $x$ ，我们只需要找到一个长度为 $x$ 的区间，使得这个区间中 $1$ 的数量加上 $k$ 大于等于 $x$ 就说明 $x$ 符合条件了。具体写出来就是要满足：

$$\sum_{i=k}^{k+x-1}a_i + k \geq m \quad (1\leq k \leq n-x+1) $$

对于 $a_i$ 的和，可以考虑用前缀和维护。

时间复杂度 $\mathcal{O}(n\log n)$ ，可以通过本题。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,l,r,mid,s[233333],a[233332],x;
int check(int k)
{
	for(int i=1;i<=n-k+1;i++)
		if(s[i+k-1]-s[i-1]+m>=k) return 1;
	return 0;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		s[i]=s[i-1]+x;
	} 
	l=0;r=n+1;
	while(l+1<r)
	{
		mid=(l+r)/2;
		if(check(mid)) l=mid;
		else r=mid;
	}
	cout<<l;
	return 0;
}
```


---

## 作者：GYHL (赞：1)

### 题目大意


一个有 $n$ 个数字的数串只有 $0$ 和 $1$，能把任意 $k$ 个 $0$ 变为 $1$，求最多有几个连续的 $1$。


### 思路


利用**前缀和**，就可知道某段到某段有几个是 $0$ 的数，再枚举左端点和右端点，可最大为 $100000$，太大了，会超时，就可以用一个变量作为左端点，枚举右端点，如果这一段 $0$ 的个数超过 $k$，这一段就不符合要求，就移动左端点，缩小这一段的长度，统计符合条件的最大值。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[100005],x,s,t,ma,l,sum;//ma是答案,l是左端点,sum是左端点到右端点的距离
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>t;
        a[i]=a[i-1];
        if(t==0) a[i]++;//前缀和统计0的个数
    }
    for(int i=1;i<=n;i++){
        if(a[i]-a[l]<=k)
        {
            sum++;//如符合条件,距离加1,因为右端点一直在变
            ma=max(ma,sum);
        }
        else
        {
            ma=max(ma,sum),l++;//如不符合条件,左端点往后移
        }
     }
      
    cout<<ma;
    return 0;
}
```


时间复杂度：$O(n)$。

---

## 作者：_Epsilon_ (赞：0)

## 题目整理：
第一行输入 $n,k(1≤n≤10^5,1≤k≤10^5)$，$k$ 是可以将 $k$ 及以下个 $0$ 改成 $1$。

第二行输入 $n$ 个数字，都是 $0$ 或者 $1$（可以理解为布尔值）。

输出一个数字，表示在改变后最长连着的 $1$ 的个数。

## 分析：

首先，这个数据直接模拟的话时间复杂度是 $O(n\times k)$ 的复杂度，在极端数据是过不了的。

#### so?

## 解法1

我们知道，前缀和可以统计前面所有某个东西的个数，我们就可以 前缀和 预处理后再去枚举。



#### 前缀和 输入预处理部分代码：
```cpp
cin>>n>>k>>a;
if(a==0)
{
	s[1]=1; 
}
for(int i=2;i<=n;i++)
{
	cin>>a;
	s[i]=s[i-1];
	if(a==0) 
	{
		s[i]++;
	}
}
```

理想复杂度：$O(n)$。
## 解法2

我们知道，二分是一种可以把时间复杂度降低为 $O(\log n)$ 的算法。二分里面还有一种分支叫二分答案，可以用二分的思想去枚举具 **有一定特性** 的答案。


####  二分答案 部分代码：

```cpp
l=0;
r=n+1;
while(l<=r)//开始二分 
{
	m=(l+r)/2;
	f=0;//初始化 
	for(int i=m;i<=n;i++)
	{
		if(s[i]-s[i-m]<=k)//符合条件就改变值，且退出循环 
		{
			ans=m;
			l=m+1;
			f=1;
			break;
		}
	}
	if(f==0)//刚才没符合条件的情况
	{
		r=m-1;
	}
}
```
理想复杂度：$O(n \log n)$。

## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;//按照数据范围去选择数组长度，其实也可以在下面手动写 
bool a,f;//单次输入足够了，存数据可以用前缀和省出时间；f只是个标记 
int n,k,s[N],l,r,m,ans;//n，k见题目，s数组是前缀和，l,r和m是后面二分用的，ans是存的答案 
int main()
{
	cin>>n>>k>>a;
	if(!a)//为0时 
	{
		s[1]=1; 
	}
	for(int i=2;i<=n;i++)
	{
		std::cin>>a;//听说标准化输入速度和scanf一样 
		s[i]=s[i-1];//先转过来 
		if(!a)//为0时 
		{
			s[i]++;
		}
	}//预处理完毕！！！ 
	l=0;
	r=n+1;
	while(l<=r)//开始二分 
	{
		m=(l+r)/2;
		f=0;//初始化 
		for(int i=m;i<=n;i++)
		{
			if(s[i]-s[i-m]<=k)//符合条件就改变值，且退出循环 
			{
				ans=m;
				l=m+1;
				f=1;
				break;
			}
		}
		if(f==0)//刚才没符合条件的情况
		{
			r=m-1;
		}
	}
	cout<<ans<<endl;//输出答案 
	return 0;
}
```
# 吐槽时刻
~~好像 二分答案 我搞了个反向优化~~。

---

## 作者：xd244 (赞：0)

简单双指针模板题。

**双指针**（Two Pointer）又称**尺取**。是一种优化算法，具体就是用 $l$ 和 $r$ 两个指针来表示数列两端。

这道题思路很简单，跟之前有一道统计最短字符串的题很类似，用一个变量 $\text{cnt}$ 表示修改几次，那么可以分类讨论：（输入的数组用 $a$ 表示）

1.$\text{cnt}\leq k$ 时，将 $a_r$ 增加 $1$，同时 $\text{cnt}$ 也增加 $1$。

2.$\text{cnt}>k$ 时，需要减少修改次数，所以 $l$ 需要增加，同时当 $a_l$ 在刚才变成 $1$ 过后，将 $a_l$ 修改为 $0$ 并且 $\text{cnt}$ 减少 $1$。

所以代码如下：
```cpp
#include<iostream>
using namespace std;
int main(){
    int n,k,a[100010]={},l=1,r=0,cnt=0,ans=0;cin>>n>>k;//cnt 表示修改次数，ans 为答案
    for(int c=1;c<=n;c++)cin>>a[c];//输入
    while(r<=n){
        if(cnt<=k){//情况 1
            ans=max(r-l+1,ans);
            if(a[r+1]==0)cnt++;//判断
            r++;
        }else{//情况 2
            if(a[l]==0)cnt--;//判断
            l++;
        }
    }cout<<ans<<"\n";//换行
}
```
#### 后记
借鉴了[这篇题解](https://www.luogu.com.cn/article/76vf7lih)，但是思路是自己想的，此外（敲警钟）自己还在情况 2 的判断中写成了 ```cnt++;```，还有 $a_{r+1}$ 不要写成 $a_r$ 这些细节。（在这里没了3次）

---

## 作者：Melo_DDD (赞：0)

T 了无数次，终于 A 了，这题二分细节还是很多的。

# 题目大意

略。

# 题目实现

看题一眼想到前缀和，为什么？让我细细道来：

众所周知，前缀和数组 $sum_i = \sum_{j = 1}^{i} a_j = a_1 + a_2 + ... + a_i$，此时我们用它存前 $i$ 项 $0$ 的个数。

那么对于区间 $[l,r]$：$\sum_{l}^{r} a_i = \sum_{1}^{r} - \sum_{1}^{l - 1} = sum_r - sum_{l - 1}$，用前缀和求非常方便。

前缀和代码：

```cpp

#define rep(i ,m ,n) for (int i = (m) ;i <= (n) ;i ++)
rep (i ,1 ,n) {
        bool x ;
        cin >> x ;
        if (! x) {
			sum[i] = sum[i - 1] + 1 ;
			goto kafka__ ;
		}
        sum[i] = sum[i - 1] ;
        kafka__ :
        		;
    }
```

可以发现题意描述具有单调性，满足二分条件，所以二分。

二分什么呢？二分当前长度是否满足题意：

```cpp
inline bool kafka (int x) {
    rep (i ,1 ,n - x + 1) {
        if (sum[i + x - 1] - sum[i - 1] <= k) return 1 ;
    }
    return 0 ;
}
```

对于第 i 项，我们考虑 $[i,i + x - 1]$ 这个区间是否满足题意（而这个区间的长度正好是我们要二分的数），如果区间内的 $0$ 小于等于 $k$ 个，那么 Joisino 学姐就可以把它变成连续的 $1$ 串，我们继续向大枚举（因为答案要最大值），否则向小枚举。

二分的循环：

```cpp
int l = 0 ,r = n ;
    while (l < r) {
        int mid = l + r + 1 >> 1 ;
        if (kafka (mid)){
            l = mid ;
			goto kafka_ ;
        }
        r = mid - 1 ;
        kafka_ :
                ;
    }
```

其中坑点不少（至少我是都踩遍了）：

- $l$ 和 $r$ 的赋值：$l$ 赋为最少天数 $0$，万不可赋值为 $1$，因为全 $0$ 串也是可能的。$r$ 赋最大值 $n$。

- 循环条件 $l < r$，因为 $l = r$ 时无意义。

- $mid$ 赋值为 $l + r + 1 \div 2 $，不加 $1$ 会 T 飞，因为不加的话 $l$ 会一直小于 $r$，只是无限趋近于它，会死循环。

# 上代码（高清无注释）：

```cpp
#include <bits/stdc++.h>
#define rep(i ,m ,n) for (int i = (m) ;i <= (n) ;i ++)
#define IOS ios :: sync_with_stdio (false) ,cin.tie (0) ,cout.tie (0)
using namespace std ;
const int N = 1e5 + 7 ;
int n ,k ,sum[N] ;
inline bool kafka (int x) { //卡妈\se\se\se
    rep (i ,1 ,n - x + 1) {
        if (sum[i + x - 1] - sum[i - 1] <= k) return 1 ;
    }
    return 0 ;
}
int main () {
    IOS ;
    cin >> n >> k ;
    rep (i ,1 ,n) {
        bool x ;
        cin >> x ;
        if (! x) {
			sum[i] = sum[i - 1] + 1 ;
			goto kafka__ ;
		}
        sum[i] = sum[i - 1] ;
        kafka__ :
        		;
    }
    int l = 0 ,r = n ;
    while (l < r) {
        int mid = l + r + 1 >> 1 ;
        if (kafka (mid)){
            l = mid ;
			goto kafka_ ;
        }
        r = mid - 1 ;
        kafka_ :
                ;
    }
    cout << l << '\n' ;
    return 0 ;
}
```

---

## 作者：Li_Yichen (赞：0)

看到最长连续的区间，能够修改，想到二分答案。二分区间的长度，如果把区间的长度记为 $len$ ，那么只要在长度为 $len$ 的区间内，修改后能把区间全部变为一即可。

如果能修改 $k$ 次，区间内一的数量为 $num$ ，二分的区间长度为 $mid$ ，那么形式化的讲，只要 $num + k >= mid$ 即为合法。

求区间内一的数量，想到用前缀和优化，代码如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt[100005],a[100005];
int n,k;
int check(int mid){
	for(int i=mid;i<=n;i++){
		if(cnt[i] - cnt[i-mid] + k >= mid) return 1;
	}
	return 0;
}
int main(){
	cin >> n >> k;
	for(int i=1;i<=n;i++){
		cin >> a[i];
	}
	for(int i=1;i<=n;i++){
		cnt[i] = cnt[i-1] + a[i];
	}
	int l=0,r=1e9;
	while(l <= r){
		int mid = (l+r)/2;
		if(check(mid)) l = mid+1;
		else r = mid-1;
	}
	cout << l-1;
	return 0;
}

```

---

## 作者：PDAST (赞：0)

## 一道非常经典的二分
这道题我遇到了三次，你们就说是不是经典吧。
## 题目大意
Joisino 姐姐想要度长假，已知后面 $n$ 天是否能休假，现在，她能使 $k$ 天不能休假的日子能休假，问她最长能连续修多少天的假。
## 主要思路
由于数据可能比较大（~~他没给~~），用暴力枚举起始位置、长度，再统计的方法大概率会 TLE，所以可以考虑使用前缀和，但是还有可能会爆，这时，动用你那聪明的小脑瓜想一想，哎，可以二分！！！于是乎我们可以二分，然后暴力枚举起始位置来判断不就行了！
## code
[AC记录](https://www.luogu.com.cn/record/150686194)

你应该不会抄的吧 QwQ，变量名是 pig 哦。
```cpp
#include<bits/stdc++.h>
using namespace std;
int pig[100001],n,k,sum[100001];//pig是为了纪念一下这出现题
bool check(int len) {
	for(int i=len; i<=n; i++)
	{
		if(sum[i]-sum[i-len]<=k)
		return 1;
	}
	return 0; 
}
int main() {
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++) {
		scanf("%d",&pig[i]);
		pig[i]=!pig[i];
		sum[i]=sum[i-1]+pig[i];
	}
	int left=0,right=n;
	while(left<right) {
		int mid=(left+right+1)>>1;
		if(check(mid))left=mid;
		else right=mid-1;
	}
	printf("%d",left);
}
```

---

## 作者：PineappleSummer (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_tkppc2016_c) 

看到要求最大值，考虑二分答案，答案区间是 $1\sim n$。

如何 check：枚举每一段长度为 $x$ 的区间，判断这一段区间中 $1$ 的个数加上 $k$ 是否大于等于 $x$，如果是，说明 $x$ 这个长度可行，否则说明这个长度不可行。计算区间中 $1$ 的个数可以用前缀和得到。

**注意：二分时 $mid$ 应等于 $(l+r+1)\div2$，否则会陷入循环中。**

check 代码：
```cpp
bool check(int x)
{
	for(int i=x;i<=n;i++)
		if(sum[i]-sum[i-x]+k>=x) return 1;
	return 0;
}
```
时间复杂度 $O(n\log n)$。

[完整代码](https://atcoder.jp/contests/tkppc2/submissions/50872734)

---

## 作者：Ethan812820 (赞：0)

## 形式化题意
给定一个长度为 $N$ 且只含 $0$ 或 $1$ 的序列，可以把其中的 $K$ 个 $0$ 改为 $1$ ，求修改后最多的连续 $1$ 的个数。  
换句话说，就是求这个序列中最长的最多含有 $K$ 个 $0$ 的子段的长度。
## 思路
题目规定 $1 \le N \le 10^5$，暴力枚举会超时。我们可以用尺取法，时间复杂度为 $O(n)$。  
定义指针 $l$ 和 $r$，进行以下操作：  
1. $l \gets 1$，$r \gets 0$。
2. 设 $sum$ 为 $[l,r]$ 中 $0$ 的个数，如果 $sum \le K$ 的话，$r \gets r+1$，否则 $l \gets l+1$。重复执行此操作，直到 $r > N$。
3. 输出执行操作2时最大的 $r-l+1$ 的值。

对于求 $[l,r]$ 中 $0$ 的个数，我们可以定义一个变量，初始值为 $0$ 并随着指针的移动而改变。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[100005];
signed main(){
	int n,k;
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++){
    	scanf("%lld",&a[i]);
	}
	int l=1,r=0,sum=0,ans=0;//sum表示[l,r]中0的个数，ans表示答案。
	while(r<=n){
		if(sum<=k){
			ans=max(r-l+1,ans);
			r++;
			sum+=(a[r]==0);
		}
		else{
			sum-=(a[l]==0);
			l++;
		}
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：CQ_Bob (赞：0)

## 分析

二分答案。

我们可以统计一个前缀和，记录前面 $0$ 的个数。如果我们二分到一个答案 $y$，在任意一个长度为 $y$ 的两个端点 $l,r$，有：$s_r-s_{l-1} \le x$，则表示这个区间所需要填的数不超过 $x$，即答案可能是 $y$。（$r=l+y-1$）

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
const int N=1e6+10;
int a[N],s[N];//s[i]:1~i中0的个数
int ans;
int check(int x){
	for(int i=x;i<=n;i++){
		if(s[i]-s[i-x]<=m){
			return 1;
		}
	}
	return 0;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s[i]=s[i-1]+(a[i]==0?1:0);
	}
	int l=0,r=1145141919810;
	while(l<=r){
		int mid=l+r>>1;//二分的答案
		if(check(mid)){//可行 
			ans=mid,l=mid+1;
		}
		else{
			r=mid-1;
		}
	}
	return cout<<ans,0;
}
```


---

## 作者：Tachibana27 (赞：0)

可以说是很水的**二分**题了，这篇题解还是将详细一点送给萌新。


------------

可以发现答案是具有单调性的。所以想到很显然的做法：二分。

二分的难点在于 $\operatorname {check}$。

$\operatorname {check}$ 函数需要查询是否有一段区间 $0$ 的个数小于或等于 $k$，换言之，是否有一段区间 $1$ 的个数大于或等于 $k$。这里可以考虑用**前缀和**进行优化，可以将暴力扫一遍 $\operatorname {check}$ 函数 $O(N^2)$ 的时间复杂度降到 $O(N)$。程序整体复杂度 $O(N\log N)$，在可接受范围内。

code:

```cpp
int n,k;
int a[100086];
bool check(int mid){
	for(int i=mid;i<=n;i++)
		if(a[i]-a[i-mid]>=mid-k)//表示这一段区间内1的个数小于k
			return true;
	return false;
}
int main(){
	std::cin>>n>>k;
	for(int i=1;i<=n;i++){
		int x;
		std::cin>>x;
		a[i]=a[i-1]+x;
	}//前缀和
	int l=1;
	int r=n;
	while(l<r){
		int mid=(l+r+1)>>1;//这里必须+1，否则会陷入死循环
		if(check(mid))
			l=mid;
		else
			r=mid-1;
	}//常规二分
	std::cout<<l;
	return 0;//撒花
}
```

---

