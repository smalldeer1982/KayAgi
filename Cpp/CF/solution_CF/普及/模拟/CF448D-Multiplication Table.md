# Multiplication Table

## 题目描述

Bizon the Champion isn't just charming, he also is very smart.

While some of us were learning the multiplication table, Bizon the Champion had fun in his own manner. Bizon the Champion painted an $ n×m $ multiplication table, where the element on the intersection of the $ i $ -th row and $ j $ -th column equals $ i·j $ (the rows and columns of the table are numbered starting from 1). Then he was asked: what number in the table is the $ k $ -th largest number? Bizon the Champion always answered correctly and immediately. Can you repeat his success?

Consider the given multiplication table. If you write out all $ n·m $ numbers from the table in the non-decreasing order, then the $ k $ -th number you write out is called the $ k $ -th largest number.

## 说明/提示

A $ 2×3 $ multiplication table looks like this:

`<br></br>1 2 3<br></br>2 4 6<br></br><br></br>`

## 样例 #1

### 输入

```
2 2 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 3 4
```

### 输出

```
3
```

## 样例 #3

### 输入

```
1 10 5
```

### 输出

```
5
```

# 题解

## 作者：Mxfg (赞：14)

# 本蒟蒻第一次发题解
### 先把题意翻译一下：给定两个数组 (a和b)，a有n个元素，b有m个元素，有另一个数组 (c)，长度为nm，元素是a和b中所有元素的乘积（可重复），求c数组的的k大数
#### 这题显然可以暴力（拿不到全分）
**可以考虑更高效算法,因为是一张$n*m$的表，所以的到乘积是按大小依次放入表中的，每一个表中的值，都肯定能被行数整除，商则是列数，而列数小于等于这个商的值都小于等于此数**

| 1 | 2 | 2 |
| -----------: | -----------: | -----------: |
| 3| 4| $n*m=6$ |
**所以满足单调性，同时答案在一个区间内，可用二分答案求解**
# 附代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,k;
bool check(long long x)
{
	long long sum=0;
	for(int i=1;i<=n;i++){
		sum+=min(m,x/i);//记录此时答案前面每行有几个数小于等于它（但不能超过最大列数），自己用表模拟，
	}
	return sum>=k;
}
int main()
{
    scanf("%lld %lld %lld",&n,&m,&k);
    long long pow=n*m;
    long long l=1,r=pow;
    while(l<r){
		long long mid=(l+r)>>1;
		if(check(mid))r=mid;
		else l=mid+1;
    }
    printf("%lld",l);
}
```


---

## 作者：yu__xuan (赞：9)

### 题目

[CF448D Multiplication Table](https://www.luogu.org/problem/CF448D)

### 思路

二分答案。这个矩阵的每一排都是递增的，所以二分$ans$，去计算有多少个数等于$ans$，有多少个数小于$ans$，如果小于$ans$的数不多于$k-1$个并且小于等于$ans$的数不少于$k$个，那么当前$ans$就是答案。

Q：如何计算小于$ans$的数的个数？

A：

$$\sum_{i=1}^{n}min(\lfloor \frac{ans-1}{i} \rfloor,m)$$

Q：如何计算等于$ans$的数的个数？

A：当$i|ans$并且$ans/i$小于$m$时个数加一。

###$Code$
```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cstdio>
#define ll long long
using namespace std;
ll n,m,k;
inline void read(ll &T){
	ll x=0;bool f=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=!f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	T=f?-x:x;
}
inline void write(ll x){
	if(x<0) putchar('-'),write(-x);
	else{
		if(x/10) write(x/10);
		putchar(x%10+'0');
	}
}

int main(){
	read(n),read(m),read(k);
	ll l=1,r=n*m;
	while(l<=r){
		ll mid=(l+r)>>1,sum=0,tmp=0;
		for(int i=1;i<=n;++i){
			sum+=min((mid-1)/i,m);
			if(mid%i==0&&mid/i<=m) tmp++;
		}
		if(sum<=k-1&&sum+tmp>=k){
			write(mid);
			return 0;
		}
		if(sum+tmp<=k-1) l=mid+1;
		else r=mid-1;
	}
	return 0;
}
```

---

## 作者：iiawaKL (赞：5)

蒟蒻写题解啦！！！


这是本蒟蒻第一次写题解(⊙o⊙)… 

话不多说，先开始讲思路 首先，根据数据很大，我第一个想到的思路就是：二分。 我们可以二分出答案，每次再用一个函数检查一下答案对不对。

有欠缺的地方还请大佬们多多指教哦!(⊙o⊙)…

代码见下->

```
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n,m,k;
bool check(long long x){
	ll sum=0;
	for(int i=1;i<=n;i++)sum+=min(m,x/i);
	return sum<k;
}
int main(){
	cin>>n>>m>>k;
	ll l=1,r=n*m+1;
	while(l<r){
		ll mid=(l+r)/2;
		if(check(mid))l=mid+1;
		else r=mid;
	}
	cout<<l<<endl;
	return 0;
}
```


---

## 作者：pengrui (赞：3)

## 本人的第一篇题解

此题使用two-pointers算法+二分答案

二分答案(ans ∈ [1,nm])
定义st指针,ed指针(不是c++中的int *)

st -> 1

ed -> m

cnt = 0

只要st * ed > mid,ed--

若st * ed <= mid,st++,cnt += ed(表示比mid小的数有多少个)

返回 cnt >= k即可

## 代码

```cpp
#include<iostream>
typedef long long ll; 

using namespace std;

ll n,m,k,l,r,mid;
ll check(ll g)
{
    ll st = 1,ed = m,cnt = 0;
    while(st <= n && ed >= 1)
    {
        if(st * ed > g)
            ed--;
        else
        {
            cnt += ed;
            st++;
        }
    }
    //cout << g << ' ' << cnt + 1 << endl;
    return cnt >= k;
}

int main()
{
    cin >> n >> m >> k;
    l = 1,r = n * m;
    while(l < r)
    {
        mid = (l + r) / 2;
        if(check(mid)) 
            r = mid;
        else
            l = mid + 1;
    }
    cout << l << endl;
}
```




---

