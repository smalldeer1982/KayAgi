# Coat of Anticubism

## 题目描述

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF667B/da431a35861ffb0dfb05294a401b5e75bc0d5240.png)As some of you know, cubism is a trend in art, where the problem of constructing volumetrical shape on a plane with a combination of three-dimensional geometric shapes comes to the fore.

A famous sculptor Cicasso, whose self-portrait you can contemplate, hates cubism. He is more impressed by the idea to transmit two-dimensional objects through three-dimensional objects by using his magnificent sculptures. And his new project is connected with this. Cicasso wants to make a coat for the haters of anticubism. To do this, he wants to create a sculpture depicting a well-known geometric primitive — convex polygon.

Cicasso prepared for this a few blanks, which are rods with integer lengths, and now he wants to bring them together. The $ i $ -th rod is a segment of length $ l_{i} $ .

The sculptor plans to make a convex polygon with a nonzero area, using all rods he has as its sides. Each rod should be used as a side to its full length. It is forbidden to cut, break or bend rods. However, two sides may form a straight angle ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF667B/88c61e080ae2c77e20323807b54f172a39161c4f.png).

Cicasso knows that it is impossible to make a convex polygon with a nonzero area out of the rods with the lengths which he had chosen. Cicasso does not want to leave the unused rods, so the sculptor decides to make another rod-blank with an integer length so that his problem is solvable. Of course, he wants to make it as short as possible, because the materials are expensive, and it is improper deed to spend money for nothing.

Help sculptor!

## 说明/提示

In the first example triangle with sides $ {1+1=2,2,1} $ can be formed from a set of lengths $ {1,1,1,2} $ .

In the second example you can make a triangle with lengths $ {20,11,4+3+2+1=10} $ .

## 样例 #1

### 输入

```
3
1 2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
20 4 3 2 1
```

### 输出

```
11
```

# 题解

## 作者：lichenzhen (赞：3)

## 题目大意
给定 $n$ 条不能围成面积非 $0$ 凸多边形的棍子的长度，要求加一条棍子使其能够组成面积非 $0$ 的凸多边形。

## 题目解法
一道数学题，我们知道三角形任意两边之和大于第三边，而三角形就是特殊的凸多边形，所以这个结论可以用在多边形上，只不过要变一下形，可以说是 $n$ 边形的任意 $n-1$ 边之和大于等另外 $1$ 边的长度。

对于这道题，我们只需要构造一条边，使其与另外除最长边长度之和大于最大边即可。

因为要求是最短的，所以就是最长边的长度减去其余边长度之和（此时加上这条边之后最长边等于其余边之和），最后再加上 $1$，就可以满足条件了。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans,maxn;
int main()
{
    cin>>n;
    while(n--){
       cin>>k;
       maxn=max(k,maxn);//找最长边
       ans+=k;
    }
    ans-=maxn;
    cout<<maxn-ans+1;
}
```


---

## 作者：RE_Prince (赞：3)

# CF667B Coat of Anticubism 

[link](https://www.luogu.com.cn/problem/CF667B)

## Sol

题目要求构成一个面积非零的凸多边形，意思是所有短边的长度加起来小于最长边。

其余式子 @N_z_  大佬已经说的很清楚了，我不再叙述了。

先把我的AC代码给大家：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, i, j, k, l, p;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> k;
        l = max(l, k), p += k;
    }
    cout << 2 * l - p + 1;
}
```

这里给大家提供几种找最大值的方法。

### 1.循环查找

代码如上，不解释了

### 2.STL

STL中有一种东西叫 `max_element()` ，这玩意可以帮我们找出数组中最大的元素。

[ `max_element()` 函数讲解](https://zhuanlan.zhihu.com/p/435905136)

这个库函数虽然也是 $\mathcal O(n)$ 的复杂度，但比循环快多了。

得出核心代码如下：

```cpp
for (int i = 1; i <= n; i++) cin >> a[i], p += a[i];
int maxx = max_element(a + 1, a + n + 1) - a - 1;
cout << (maxx << 1) - p + 1;
```

### 3.排序

一个简简单单的 `sort` 排序，不讲了。

好了，这篇题解就结束了。

---

## 作者：szh_AK_all (赞：1)

[没看题的人可以先走这里](https://www.luogu.com.cn/problem/CF667B)

## 题意
给出 $n$ 个数，要用这 $n$ 个数组成一个多边形（凸边形，也就是我们日常所见的三角形、正方形等），但由于这 $n$ 个数不能构成完整的多边形，所以，我们要再给出一个数，令这 $n+1$ 个数可以组成多边形。

## 思路
就拿三角形来说吧，如果三角形的任意两边之和都大于另一边，那么，这就是一个完整的三角形。其实，我们不用判断完所有的边，只需要判断最大的边是否小于其余两边之和就行了。因为：如果最大的边小于其余两边之和，那么，非最大边肯定也小于其余两边之和（非最大边肯定小于最大边）。三角形可以这样判断，而多边形类同。
# Code
```c
#include<iostream>
using namespace std;
int main()
{
    long long ans=0,tmp=0;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        long long x;
        cin>>x;
        if(x>ans)//用打擂台的方式记录最大值
            ans=x;
        tmp+=x;
    }
    tmp-=ans;//注意，计算完总和后要减掉最大值
    long long k=ans-tmp+1;
    if(k<0)
    k=0;
    cout<<k;
}
```
[在这里看效果更佳](https://www.luogu.com.cn/blog/jdsndjknddb/solution-cf667b)

---

## 作者：nj_peak (赞：1)

###### 一道纯纯的数学题！！！
# 题目
给你 $a$ 条不能围成面积（凸多边形）的棍子的长度，要求你再加上一条使得 $a+1$ 条棍子能组成一个面积非零的凸多边形。
## 思路
一道纯纯的数学题，只要你掌握了这道题的“精髓”就可以正确了！

我们都知道，三角形任意两边之和大于第三边，然而三角形也算一个凸多边形。所以这个结论也可以运用在凸多边形上！但是我们要注意一下细节，最后得出结论：对于任意的凸多边形中的 $a-1$ 条边之和，永远比另外一条边要大！
## 代码
```cpp
#include<bits/stdc++.h>//万能头，省时间。 
using namespace std;
#define int long long 
int a,b,ans,amax;
signed main()
{
    scanf("%lld",&a);//scanf比cin更快哦。 
    for(int i=1;i<=a;++i)
	{
       scanf("lld",&b);
       amax=max(b,amax);//amax=max(b,amax);表示找出b和max中最大的部分，就是找出最长边。 
       ans+=b;
    }
    ans-=amax;
    printf("%lld\n",amax-ans+1);//printf比cout更快哦。
}
```

---

## 作者：Eazin_star (赞：0)

## 思路
众所周知，三角形有个很重要的结论，两边之和大于第三边。而三角形也是一个凸多边形，所以由此可得一个新的结论，凸多边形的 $a-1$ 之和一定比另外一条边大！那我们就可以写出代码了。

## 代码
```
#include <bits/stdc++.h>
using namespace std;

int a, sum, maxn;

int main() {
	cin >> a;
	for (int i = 1; i <= n; i++) {
		int b;
		cin >> b;
		maxn = max(maxn, b);
		sum += b;
	}	
	sum -= maxn;
	cout << maxn-sum+1 << endl;
	return 0;
}
```


---

## 作者：xcv_ (赞：0)


## 题意
给出 $n$ 个数,要用这 $n$ 个数组成一个多边形（凸边形），但由于这 $n$ 个数不能构成完整的多边形因此，我们要给出一个数，令这 $n +1$ 个数可以组成多边形。

## 思路
三角形任意两边之和大于第三边，然而三角形也算一个凸多边形。所以这个结论也可以运用在凸多边形上！但是我们要注意一下细节，最后得出结论：对于任意的凸多边形中的 $a-1$ 条边之和，永远比另外一条边要大。
```cpp
#include<bits/stdc++.h>

using namespace std;

int n, a, maxn, ans;

int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a;
		maxn = max(a, maxn); // maxn = max(maxn, a); 求出n 个数中的最大值 就是找出最长边 
		ans += a;
	}
	cout << 2 * maxn - ans + 1;
	return 0;
}
```


---

## 作者：Terry2011 (赞：0)

# 题目分析
这道题目涉及到了多边形的性质，小学的时候我们学过三角形任意两边之和大于第三边。多边形也如此，即一个 $n$ 边形，任意 $n-1$ 条边之和大于第 $n$ 条边。这样就简单了，我们在输入的同时找到最大的边长，然后用一个计时器记录每一条边之和。最后，用计数器中的数减去最大数，就是最极端情况下的 $n-1$ 条边之和。因为题目保证一定无法构成一个面积非零的凸多边形，所以，计数器中的数一定小于等于最大的数。我们用最大的数减去计数器中的数，最后加上 $1$ 就是答案了。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,s[10050],ans=0,ma=-1e9;
	cin>>a;
	for(int i=1;i<=a;i++){
		cin>>s[i];
		ma=max(ma,s[i]);
		ans+=s[i];
	}
	ans-=ma;
	cout<<ma-ans+1;
	return 0;
}
```

---

## 作者：N_z_ (赞：0)

## 思路
题目保证了给出的长度做不出一个凸多边形。

那么就是说最长边大于等于其余边之和。

那么我们可以构造一条边，让加上这条边之后最长边小于其余边之和。

因为要最小，所以就是加上这条边使最长边等于其余边之和$-1$。

即
$$\begin{aligned}
	a_{\max}&=\sum_{i=1}^na_i-a_{\max}+a_{add}-1\\
   a_{add}&=2* a_{\max}-\sum_{i=1}^na_i+1
\end{aligned}$$

读入时处理即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int ma=0,s=0;
    for(int x=1,y;x<=n;x++)
    cin>>y,ma=max(ma,y),s+=y;
    cout<<2*ma-s+1;
}
```

---

