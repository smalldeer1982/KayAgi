# Ela's Fitness and the Luxury Number

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737B/4125e6582413ec975c7a146ffd0b0032ff15910a.png)While working at DTL, Ela is very aware of her physical and mental health. She started to practice various sports, such as Archery, Yoga, and Football.Since she started engaging in sports activities, Ela switches to trying a new sport on days she considers being "Luxury" days. She counts the days since she started these activities, in which the day she starts is numbered as day $ 1 $ . A "Luxury" day is the day in which the number of this day is a luxurious number.

An integer $ x $ is called a luxurious number if it is divisible by $ {\lfloor \sqrt{x} \rfloor} $ .

Here $ \lfloor r \rfloor $ denotes the "floor" of a real number $ r $ . In other words, it's the largest integer not greater than $ r $ .

For example: $ 8 $ , $ 56 $ , $ 100 $ are luxurious numbers, since $ 8 $ is divisible by $ \lfloor \sqrt{8} \rfloor = \lfloor 2.8284 \rfloor = 2 $ , $ 56 $ is divisible $ \lfloor \sqrt{56} \rfloor = \lfloor 7.4833 \rfloor = 7 $ , and $ 100 $ is divisible by $ \lfloor \sqrt{100} \rfloor = \lfloor 10 \rfloor = 10 $ , respectively. On the other hand $ 5 $ , $ 40 $ are not, since $ 5 $ are not divisible by $ \lfloor \sqrt{5} \rfloor = \lfloor 2.2361 \rfloor = 2 $ , and $ 40 $ are not divisible by $ \lfloor \sqrt{40} \rfloor = \lfloor 6.3246 \rfloor = 6 $ .

Being a friend of Ela, you want to engage in these fitness activities with her to keep her and yourself accompanied (and have fun together, of course). Between day $ l $ and day $ r $ , you want to know how many times she changes the activities.

## 说明/提示

In the first test case, $ 5 $ luxury numbers in range $ [8, 19] $ are: $ 8, 9, 12, 15, 16 $ .

## 样例 #1

### 输入

```
5
8 19
8 20
119 121
1 100000000000000000
1234567891011 1000000000000000000```

### 输出

```
5
6
2
948683296
2996666667```

# 题解

## 作者：with_no_signal (赞：8)

# 题意简述

给定 $l,r$ 询问有多少 $x$ $(l\leq x \leq r)$ 满足 $\lfloor \sqrt x \rfloor \mid x$。

## 思路
注意到数据范围  $1\leq l \leq r \leq 10^{18}$，猜测肯定有 $O(1)$ 的做法。

容易想到 $(x+1)^2=x^2+2 \cdot x+1$，$(x+1)^2-x^2=2\cdot x+1$ **即： $x^2$ 和 $(x+1)^2$ 之间有两个整数是 $x$ 的整数倍。**

计算出 $l\dots r$ 中完全平方数的数量，注意边界情况再做增减即可。

注意数据范围，直接使用

```cpp
sqrt(l)
```
会掉精度，需要使用
```cpp
sqrtl(l)
```
即可避免精度问题。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
int a,b;
int ans;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		ans=0;
		cin>>a>>b;
		int sa=sqrtl(a),sb=sqrtl(b);
		ans+=3*(sb-sa-1);
		sa*=sa;
		sb*=sb;
		if(sb<=b)ans++;
		if(sb+sqrtl(sb)<=b)ans++;
		if(sb+2*sqrtl(sb)<=b)ans++;
		if(sa>=a)ans++;
		if(sa+sqrtl(sa)>=a)ans++;
		if(sa+2*sqrtl(sa)>=a)ans++;
		cout<<ans<<"\n";
	}
	return 0;
}
```


---

## 作者：ACtheQ (赞：4)

这道题很简单，来写篇题解。

可以转换为 $1 \sim r$ 有多少个完全平方数，减去 $1 \sim l$ 有多少个完全平方数。

```c++
int t;
cin>>t;
while(t--)
{	
	int l,r;
	cin>>l>>r;
	cout<<solve(r)-solve(l-1)<<endl;
}
```

接下来看 `solve` 函数：

`int solve(int n)`

首先求出 $ \lfloor \sqrt{n} \rfloor$，由于直接使用 `sqrt` 函数回掉精度，可以考虑下面的代码。

```c++
int k=sqrt(n)+2;
while(k*k>n) k--;
```

那么答案就是 $(k-1) \times 3 +1$。

特殊情况 $k \times (k+1) \le n$ 那么答案加 $1$。

特殊情况 $k \times (k+2) \le n$ 那么答案再加 $1$。

完整代码：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
int solve(int n)
{
	if(n<=0) return 0;
	int k=sqrt(n)+2;
	while(k*k>n) k--;
	int res=(k-1)*3+1;
	if(k*(k+1)<=n) res++;
	if(k*(k+2)<=n) res++;
	return res;	
} 
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int l,r;
		cin>>l>>r;
		cout<<solve(r)-solve(l-1)<<endl;
	}
	return 0;
}

````

---

## 作者：xu222ux (赞：2)

# [你谷题目](https://www.luogu.com.cn/problem/CF1737B)

## 思路

看到题一下子我就发现正解一定是 $O(1)$ 的。

然后我就开始找规律，很快发现每两个完全平方数之间都有三个“奢侈数”。

所以规律就找到啦！这里给一下证明:

因为 $(x+1)^2=x^2+2\times x+1$，所以 $[x^2,(x+1)^2)$ 区间内就有 $x^2$ 、$x^2+x$ 和 $x^2+2\times x$ 这三个数是“奢侈数”。

最后，答案就是区间 $[1,r]$ 的“奢侈数”个数减去区间 $[1,l-1]$ 的“奢侈数”个数。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
long long l,r;
int main(){
	cin>>t;
	while(t--){
		cin>>l>>r;
		long long ll=sqrt(l);
		long long rr=sqrt(r);
		if(rr==ll){
			long long ans=0;
			if(l==ll*ll)ans++;
			if(l<=ll*(ll+1)&&r>=ll*(ll+1))ans++;
			if(l<=ll*(ll+2)&&r>=ll*(ll+2))ans++;
			cout<<ans<<endl;
			continue;
		}
		long long ans=max(rr-ll-1,(long long)0)*3;
		long long s=((ll+1)*(ll+1)-l-1)/ll+1;
		long long z=(r-rr*rr)/rr+1;
		cout<</*l<<' '<<r<<' '<<ll<<' '<<rr<<' '<<ans<<' '<<s<<' '<<z<<' '<<*/ans+s+z<<endl;
	}
	return 0;
}
```

---

## 作者：DragonForge (赞：1)

# 题解：CF1737B Ela's Fitness and the Luxury Number


注：如果是数竞还不错的 OIer，这道题其实并不是很难。


---

## 正题
### 思路
毕竟是一道求区间中满足要求数的多少的题，一般来说是不能每一次输入都搜索一遍的，这样的时间复杂度一定是不优的。因此考虑通项阶与前缀和。
### 公式推导
求有多少个 `x` 满足 $\lfloor\sqrt x\rfloor \mid x$ 且 $x \in \left[l,r\right]$。学过数竞的肯定会知道一个定理：
> 相邻两个完全平方数间没有完全平方数。

这其实并不是废话，这里注意到 $\left(x+1\right)^2 - x^2 = 2 \cdot x + 1$，所以**在 $x^2$ 和 $\left(x+1\right)^2$ 之间有 2 个 $x$ 的倍数**。于是这道题就成了判断 $\left[l,r\right]$ 中有几个完全平方数。

但是要特殊判断一下最后 2 个数，因为会有可能取不到被多算了。
### 细节（重点）
很多选手做题不看数据范围，但是我认为数据范围很重要，比如说这道题的 $1 \le l \le r \le 10^{18}$，这个数明显需要开 `long long`，而且 `sqrt()` 需要用 `sqrtl()` 替换，提高精度。
### end
其他的题解的代码已经很优秀了，这里我就不出示代码了。但是还是要提醒大家做题要多多审题，尤其时数据范围！

---

## 作者：Erotate (赞：1)

### 题意：
每次给出 $l,r$，求满足

1. $l \leq x \leq r$
2. $\left\lfloor\ \sqrt{x} \right\rfloor ∣x$

的 $x$ 的数量。

### Solution：
显然，如果一个数 $x$ 能表示成 $k^2$ 的形式（$k$ 为整数），并且 $l \leq x \leq r$，那 $x$ 就一定符合要求。

然后我们发现对于在 $[k^2-2 \times k + 2,k^2-1]$ 的数里，只有 $k^2-1,k^2-k$ 这两个数符合要求，在这个范围内，只有这两个数被 $k-1$ 整除（因为是向下取整，所以是 $k-1$）。

那么我们，只需要找出 $l$ 到 $r$ 里平方数的数量，然后在判断一下边界即可。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,l,r;
int getr(int x){
	int L=1,R=1e9,res;
	while(L<=R){
		int mid=L+R>>1;
		if(mid*mid<=x){
			res=mid;
			L=mid+1;
		}else R=mid-1;
	}
	return res;
}
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&l,&r);
		int a=getr(l),b=getr(r),ans;
		if(a*a!=l) a++;
		ans=(b-a+1)*3;
		if(a*(a-1)<l) ans--;
		if(a*a-1<l) ans--;
		if(b*(b+1)<=r) ans++;
		if((b+1)*(b+1)-1<=r) ans++;
		printf("%lld\n",ans);
	}
	return 0;
}
```

### 后记
这里用二分求解是因为 C++ 提供的 STL 函数似乎精度不够，导致 WA 了好几次。

---

## 作者：Fu_Da_Ying (赞：0)

## [原题链接](https://www.luogu.com.cn/problem/CF1737B)
## 题意：

$t$ 组询问，给定 $l$,$r$ 询问有多少 $x$ 满足 $l\leq x \leq r$ 且满足 $\lfloor \sqrt x \rfloor $ 为 $x$ 的因数。

## 思路：

先看数据范围，$1 \le t \le 10^5$ 且 $1 \le l \le r \le 10^{18}$ ，暴力会超时，所以时间复杂度考虑能否达到 $O(t)$，即每次询问可以尝试 $O(1)$

可以先从 $[1,3]$ 找，发现有 $4$ 个满足，为 $1,2,3$

规律不明显，再从 $[2^2,3^2-1]$ 找。（如下图）

![](https://cdn.luogu.com.cn/upload/image_hosting/stsrs2ik.png)

容易发现在 $[x^2,(x+1)^2-1]$ 中 ($x$ 为正整数)，会有 $3$ 个数满足，为 $x^2,x(x+1),(x+1)^2-1,(x+1)^2$。

证明：先把 $(x+1)^2-1$ 化简为 $x(x+2)$，满足要求，此外，还有 $x^2$ 和 $x(x+1)$ 符合，即在 $[x^2,(x+1)^2-1]$ 中，会有 $3$ 个数满足，为 $x^2,x(x+1),(x+1)^2-1,(x+1)^2$。

有了结论，就可以做了，$[l,r]$ 的区间就为 $[1,r]$ 的区间减去 $[1,l-1]$ 的区间。

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,l,r,suml,sumr,sqrttl,sqrttr;
//suml,sumr分别代表区间[1,l-1],[1,r]满足floor(sqrt(x))为x的因数x的个数
//sqrttl,sqrttr分别代表sqrt(l-1),sqrt(r);
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&l,&r);
		sqrttl=sqrt(l-1);
		sqrttr=sqrt(r);
		suml=sqrttl*3;
		sumr=sqrttr*3;//一个完全平方数有3个满足
		if((sqrttl+2)*sqrttl==l-1){//处理当l-1为(sqrttl+2)sqrttl时,会多2种情况 
			suml+=2;
		}else if((sqrttl+1)*sqrttl<=l-1){//处理当l-1不大于(sqrttl+1)sqrttl,会多1种情况 
			suml++;
		}
		if((sqrttr+2)*sqrttr==r){
			sumr+=2;
		}else if((sqrttr+1)*sqrttr<=r){
			sumr++;
		}//同上
		printf("%lld\n",sumr-suml); 
	} 
	return 0;
}
```

### [AC 记录](https://www.luogu.com.cn/record/168610827)

---

## 作者：liuyuanpei (赞：0)

本题暴力明显超时，所以猜测是直接计算得到结果。

我们可以用样例找规律：
 
第一个：$ l=8，r=19 $ 时，奢侈数有 ` 8 9 12 15 16 `

第二个：$ l=8，r=20 $ 时，奢侈数有 ` 8 9 12 15 16 20 `

第三个：$ l=119，r=121 $ 时，奢侈数有 ` 120 121 `

可以发现，在相邻两个平方数间只有三个奢侈数。

那么我们不难给出证明：

在 $x^2$ 到 $ (x+1)^2 $ 间，$ \lfloor\ \sqrt n\ \rfloor\ $ 均为 $x$，而因为 $ (x+1)^2 = x^2 + 2x + 1 $，所以 $x^2$ 到 $ (x+1)^2 $ 间是 $x$ 倍数的只有 $x^2$，$x^2+x$，$ x^2+2x $ 三个数。

CODE：

```cpp
# include <iostream>
# include <cmath>
# include <cstring>
# include <string>
# include <algorithm>
# include <stack>
# include <queue>
# include <vector>
# include <set>
# include <map>
using namespace std;
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio (false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
	cin >>t;
	while (t--){
		long long l,r,ans=0;
		cin >>l>>r;
		long long x=sqrt(l),y=sqrt(r);
		if (x==y){
			if (l<=x*x&&x*x<=r) ans++;
			if (l<=x*x+x&&x*x+x<=r) ans++;
			if (l<=x*x+2*x&&x*x+2*x<=r) ans++;
			cout <<ans<<endl;
			continue;
		}
		ans+=max(y-x-1,0ll)*3;
		ans+=((x+1)*(x+1)-l-1)/x+1;
		ans+=(r-y*y)/y+1;
		cout <<ans<<endl;
	} 
    return 0;
}

```


---

## 作者：孤芒星河233 (赞：0)

## CF1737B Ela's Fitness and the Luxury Number

[洛谷题面](https://www.luogu.com.cn/problem/CF1737B)
[CF题面](https://www.luogu.com.cn/problem/CF1737B)

- **题意**
  
  有 $T$ 组数据。每组数据给出两个正整数 $l,r$，求出
  $$
  \sum_{x\in[l,r],x\in \mathbb{Z}}{[\lfloor\sqrt x\rfloor\mid x]}
  $$

  数据范围：$1\leq T\leq 10^4,1\leq l\leq r\leq 10^{16}$

- **思路**

  这种题只需要求出 $[1,r]$ 与 $[1,l-1]$ 中满足情况的差值，也就是说，我们只需要知道如何求 $[1,x],x\in\mathbb{Z}$ 中满足条件的数。
  
  首先我们可以想，若设正整数 $x$，那么对于所有正整数 $y\in [x^2,(x+1)^2)$，满足 $\lfloor\sqrt y\rfloor=x$。那么我们只需要知道 $[x^2,(x+1)^2)$ 中有几个数能被 $x$ 整除，可以通过求这个区间的大小。也就是

  $$(x+1)^2-x^2=2x+1$$

  然后再加上 $x^2$ 的情况，也就是说在 $[x^2,(x+1)^2)$ 中，有 $3$ 个数可以被 $x$ 整除。这题到这里基本就结束了。

- **代码**

  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  #define ll long long

  int T;
  ll l,r;

  int main(){
      cin>>T;
      while(T--){
          scanf("%lld%lld",&l,&r);
          l--;
          ll x=sqrt(l),y=sqrt(r),sl,sr;
          sl=3*(x-1)+1,sr=3*(y-1)+1;
          if(x*x!=l) sl+=((l-x*x)/x);
          if(y*y!=r) sr+=((r-y*y)/y);
          if(l==0) sl=0;//特判一下
          printf("%lld\n",sr-sl);
      }
      return 0;
  }
  ```

---

## 作者：AzureMist (赞：0)

### 铺垫
在左开右闭区间 $[x^2,(x+1)^2)$ 当中有多少个 $x$ 的倍数？

因为 $(x+1)^2=x^2+2x+1$，所以 $x^2$、$x^2+x$ 和 $x^2+2x$ 都是符合要求的数，共有 $3$ 个。

---
这道题就是有多个这种左开右闭区间。

$\tt{e.g.}$ 当 $l=7,r=40$ 时：

$[9,16)$ 中有 $3$ 个，$[16,25)$ 中有 $3$，$[25,36)$ 中也有 $3$ 个。然后 $[7,9)$ 中有 $1$ 个，$[36,40)$ 中有 $1$ 个，总共 $11$ 个。

AC Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,l,r,cnt,sql,sqr,i,j;
int main()
{
	cin>>t;
	for(i=1;i<=t;i++)
	{
		bool lcge=false,rcge=false;//别问我这个rcge是怎么来的
		cin>>l>>r;
		sql=(ll)(sqrtl(l));//用sqrt会被爆精度
		sqr=(ll)(sqrtl(r));
		if(sql*sql<l) sql+=1,lcge=true;//否则就多算了一个不完整的这种区间进去
		cnt=(sqr-sql)*3;//套用公式
		if(lcge)
		{
			if(l!=1)//否则会除以0
			{
				j=(l/(sql-1))*(sql-1);
				if(j<l) j+=sql-1;
				if(!j) j=1;//前后呼应
				for(;j<sql*sql;j+=sql-1) cnt++;//（卡常）枚举左边不完整的部分
			}
		}
		for(j=sqr*sqr;j<=r;j+=sqr) cnt++;//（卡常）枚举右边不完整的部分
		cout<<cnt<<endl;
		cnt=0;//多测很糟糕
	}
	return 0;
}
```

---

