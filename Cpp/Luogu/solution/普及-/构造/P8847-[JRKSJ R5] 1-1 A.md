# [JRKSJ R5] 1-1 A

## 题目背景

本题是 1-1 的较易版本，较难版本为 [1-1 B](https://www.luogu.com.cn/problem/P8848)。

## 题目描述

给出一个序列 $a$，$\forall i\in [1,n],a_i\in \{1,-1\}$。

你可以将序列任意重排，需最小化重排后序列的最大子段和。

## 说明/提示

最大子段和的定义：序列中一段区间的和的最大值。即 $\max_{1\le l\le r\le n} \sum_{i=l}^r a_i$。

本题使用 $\text{Special Judge}$，只要你的输出满足题意即可通过。

**本题输入输出文件较大，请使用恰当的输入输出方式。**

### 数据规模
本题采用捆绑测试。

| $\text{Subtask}$ | $n\le$ | $\text{Score}$ |
| :----------: | :----------: | :----------: |
| $1$ | $10$ | $40$ |
| $2$ | $10^6$ | $60$ |

对于 $100\%$ 的数据，$1\le n\le 10^6$，$a_i\in \{1,-1\}$。

## 样例 #1

### 输入

```
4
1 1 -1 -1```

### 输出

```
1 -1 -1 1```

# 题解

## 作者：U_star (赞：13)

[P8847 [JRKSJ R5] 1-1 A](https://www.luogu.com.cn/problem/P8847)

普通思路：枚举所有可能，然后每次求出最大子段和。可通过 $\operatorname{40pts}$ 的数据。

如果想要AC，时间复杂度就需要控制在 $\operatorname{O(nlogn)}$ 之内。

注意此题有一个特殊性质：$a_i$ 只能为 $1$ 或 $-1$。也就是说，给出的序列中只有 $1$ 或 $-1$。

根据本题的特殊性，我们可以分类讨论以下三种情况：

1. $-1$ 的数量大于 $1$ 的数量

这时我们就可以把 $-1$ 和 $1$ 配对放在一起，大概就是像下面这样：
$$1,-1,1,-1,1,-1......$$
然后将多余的 $-1$ 放在序列的末尾。考虑这种排列的最大子段和：

- 根据贪心策略，最后多余的 $-1$ 一定不会选。
- 只选择一个数时，选择一个 $1$ 为最优。
- 选择多个数时，由于 $-1$ 和 $1$ 相邻，所以相邻的两数会互相抵消，导致最后不会剩下数或者只会剩下一个数，其实相当于是选择一个数的情况。

所以这种方法最大子段和为 $1$。

可以证明，只要数列中有 $1$，无论如何重排，最大子段和都至少为 $1$，因为可以只选择一个 $1$。因此，这种排列是最优解。

2. $-1$ 的数量等于 $1$ 的数量

这种情况类似于上面的情况，也是将 $-1$ 和 $1$ 配对，最大子段和也为 $1$。

3. $-1$ 的数量小于 $1$ 的数量

仍然将 $-1$ 和 $1$ 配对（注意！一定要把 $-1$ 放在后面），然后将多余的 $1$ 放在序列的末尾。

这种排列的最大子段和为 $x$（$x$ 为 $1$ 的数量减去 $-1$ 的数量），因为后面多余的 $1$ 一定要选，而前面的无论如何选择都一定会互相抵消。

证明：由于可以选择整个序列，所以无论怎么重排，最大子段和必然不小于 $x$。因此，这种排列是最优解。

至于为什么要把 $-1$ 放在后面？因为最后面的全都是 $1$，也就是说把 $1$ 放后面会使最大子段和增加 $1$。

AC Code：
```cpp
#include<bits/stdc++.h> 
using namespace std;
int a,v1,v2;
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		if(a==1)
		v1++;
		else
		v2++;
	}
	if(v2==v1)
	{
		for(int i=1;i<=n;i++)
		{
			if(i%2)
			cout<<1<<" ";
			else
			cout<<-1<<" ";
		}
	}
	else if(v2>v1)
	{
		for(int i=1;i<=v1*2;i++)
		{
			if(i%2)
			cout<<1<<" ";
			else
			cout<<-1<<" ";
		}
		for(int i=1;i<=n-v1*2;i++)
		cout<<-1<<" ";
	}
	else
	{
		for(int i=1;i<=v2*2;i++)
		{
			if(i%2)
			cout<<1<<" ";
			else
			cout<<-1<<" ";
		}
		for(int i=1;i<=n-v2*2;i++)
		cout<<1<<" ";
	}
	return 0;
}
```
时间复杂度：$\operatorname{O(n)}$。

---

## 作者：Xy_top (赞：5)

看到这种让最大和最小我第一个想到的就是二分了！~~虽然不是最优解~~

我们循序渐进，最后再来讲优化啊。

二分最大和最小非常简单，重点是如何构造？

我们可以一边构造一边算，先来回想一下求最大子段和的过程。

如果加上当前的数小于 $0$ 了，那么就清零，否则就加上当前的数。

这样，我们每一次循环就可以得到以当前数为结尾的最大子段和了！

构造也十分简单，我们先考虑填 $1$，发现下一个再填 $1$ 最大子段和就会超出我们二分的答案，那么填 $-1$。

时间复杂度为 $O(n\log n)$。

配一个代码：

```cpp
#include <iostream>
using namespace std;
int n, suma, sumb, tmpa, tmpb;
int l, r, mid, x;
int a[1000010], ans[1000010];
bool check (int x)
{
	int sum = 0;
	tmpa = suma;
	tmpb = sumb;
	for (int i = 1; i <= n; i ++)
	{
		if (sum < x)
		{
			if (tmpa == 0)
			{
				for (int j = i; j <= n; j ++) ans[j] = -1;
				return true;
			}
			else
			{
				tmpa --;
				ans[i] = 1;
				sum ++;
			}
		}
		else
		{
			if (tmpb == 0)
			{
				for (int j = i; j <= n; j ++) ans[j] = 1;
				if (sum + n - i + 1 <= x) return true;
				return false;
			}
			tmpb --;
			ans[i] = -1;
			sum --;
			if (sum < 0) sum = 0;
		}
	}
	return true;
}
int main()
{
	ios::sync_with_stdio(false);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i ++)
	{
		scanf ("%d", &x);
		if (x == 1) suma ++;
		else sumb ++;
	}
	l = 1;
	r = suma;
	if (sumb == n)
	{
		for (int i = 1; i <= n; i ++) cout << "-1" << " ";
		return 0;
	}
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check (mid) ) r = mid - 1;
		else l = mid + 1;
	}
	for (int i = 1; i <= n; i ++) cout << ans[i] << " ";
	return 0;
}
```

实在是有亿点点长啊。接着我们就来优化二分，把它优化成 $O(n)$。

先来看一下用这个方法构造出的数组肯定是对的，构造出的数组是什么形式呢？

假如说我们二分的答案是 $mid$，那么前 $mid$ 个数肯定都是 $1$，

第 $mid+1$ 个数就是 $-1$ (不然最大子段和超出 $mid$)，

然后我们发现，又可以填 $1$ 了，就再填，如此往复，就是 $1,-1$ 轮流。

找完了数组的形式，再来想一想答案的末尾是个什么数？ $n - mid$ 如果是 $2$ 的倍数，那么是 $1$，否则是 $-1$。

假设我们现在构造最小最大子段和为 $mid$ 不难发现，其中 $1,-1$ 交错的串一共有 $\lfloor\frac{n-mid}{2}\rfloor$ 个，$-1$ 就也有 $\lfloor\frac{n-mid}{2}\rfloor$ 个。

我们现在想让 $mid$ 尽可能小，而 $-1$ 又不超出限制，那就是解一个方程，

我们知道 $-1$ 的个数，假设 $-1$ 有 $x$ 个，就知道了 $\lfloor\frac{n-mid}{2}\rfloor$，

然后得到 $mid=n-2\times x$ 或 $mid=n-2\times x + 1$ 是另一个解，$mid$ 取 $n-2\times x$ 较小， 然后就可以构造了。

代码我就不放了，大家自己去研究研究吧。

---

## 作者：Vct14 (赞：2)

### 题目

[题目传送门](https://www.luogu.com.cn/problem/P8847)

- 给定一个仅由 $1$ 和 $-1$ 构成的序列 $a$，求 $\max_{1\le l\le r\le n} \sum_{i=l}^r a_i$。
- $1\le n\le 10^6$，$a_i\in \{1,-1\}$。
- 本题使用 $\text{Special Judge}$，只要输出满足题意即可通过。

### 思路

因为可以将序列任意重排，所以可以不考虑输入的顺序，只需统计 $1$ 和 $-1$ 各出现了多少次。

若 $-1$ 出现了 $m$ 次，$1$ 出现了 $o$ 次。

因为 $1+(-1)=0$，即可以互相抵消，所以我们可以一个 $1$，一个 $-1$ 这样输出，当其中一个输出完之后，把另一个也输出完即可。

例：

$\underline{1\ \ {-1}}\ \ \underline{1\ \ {-1}}\ \ -1\ \ -1$

我们可以先轮流输出 $\min(m,o)$ 个 $1$ 和 $-1$，再求出多的是哪一个（$1$ 还是 $-1$），最后输出 $|m-o|$ 个多的数。

### 代码

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    int m=0,o=0;//m:minus one，存储 -1 的数量；o 存储 1 的数量
    for(int i=1; i<=n; i++){
        int a;
        cin>>a;
        if(a==-1) m++;
        else o++;
    }
    for(int i=1; i<=min(m,o); i++) printf("1 -1 ");//先轮流输出 min(m,o) 个 1 和 -1，把少的输出完
    int k=(m>=o)?-1:1;//求出多的是 -1 还是 1
    for(int i=1; i<=abs(m-o); i++) printf("%d ",k);//输出 |m-o| 个多的数
    return 0;
}
```


---

## 作者：pxb0801 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P8847)

-------------
## 1.分析：

这题和前一题一样，都是构造题，~~所以本蒟蒻都调了很长时间~~。

首先需要明确一点，只要序列中有 $1$，无论怎么排列，最大子段和最小都是 $1$。

如果 $1$ 的个数没有 $-1$ 的多，则最大子段和一定为 $1$，构造如下：

$$1,-1,1,-1,\cdots,1,-1,-1,\cdots,-1$$

如果 $1$ 的个数比 $-1$ 的多，则最大子段和至少是所有数加在一起，我们也有方法使最大子段和就会所有数加在一起的和。构造如下：

$$1,-1,1,-1,\cdots,1,-1,1,1,\cdots,1$$

---------------
## 2.AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt1,cnt2;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		if(~x) cnt1++;//cnt1存1的个数
		else cnt2++;//cnt2存-1的个数
	}
	if(cnt1>cnt2){//1的个数比-1多
		for(int i=1;i<=cnt2;i++){
			printf("1 -1 ");//前面是1,-1交替
		}
		for(int i=cnt2+1;i<=cnt1;i++){
			printf("1 ");//最后全部输出1
		}
	}
	else{
		for(int i=1;i<=cnt1;i++){
			printf("1 -1 ");
		}
		for(int i=cnt1+1;i<=cnt2;i++){
			printf("-1 ");//最后全部输出-1
		}
	}
	return 0;
}
```

---

## 作者：Eleveslaine (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P8847)

[博客食用](https://www.luogu.com.cn/blog/fbi-blogs/solution-p8847)

## 题意

将仅有 $1,-1$ 的序列 $a$ 任意重排，使得最大子段和最小。

## 分析

因为可以**任意重排**，所以没有必要考虑原来的顺序，故序列 $a$ 可以看作 $x$ 个 $1$，$y$ 个 $-1$ 构成的可重复集。

考虑怎样让最大子段和最小。可以分两种情况：

1. 当 $x \le y$ 时。这种情况比较简单，例如 $2$ 个 $1$ 和 $3$ 个 $-1$（即 $x=2,y=3$）。可以这样排列：
$$\underline{1\;-\!1}\;\underline{1\;-\!1}\;-\!1$$

这里下划线部分输出了 $2$ 组 $1\;-\!1$，即输出 $x$ 组 $1\;-\!1$。  
剩下的 $(y-x)$ 个 $-1$ 全部输出到最后即可。

正确性证明：

任意组连续的 $1\;-\!1$ 最大子段和显然为 $1$（即仅选取一个 $1$）。而剩下的 $(y-x)$ 个 $-1$ 的最大子段和为 $0$（即不选），所以整个序列的最大子段和为 $1$。只要这个序列有一个 $1$，那么最大子段和一定 $>1$，达到了最小化最大子段和的目的。

---

2. 当 $x>y$ 时，例如 $3$ 个 $1$ 和 $2$ 个 $-1$（即 $x=3,y=2$）。可以这样排列：
$$\underline{1\;-\!1}\;\underline{1\;-\!1}\;1$$

下划线部分输出了 $2$ 组 $1\;-\!1$，即输出 $y$ 组 $1\;-\!1$。   
剩下的 $(x-y)$ 个 $1$ 全部输出到最后即可。

正确性证明：

$y$ 组连续的 $1\;-\!1$ 最大子段和为 $1$，剩下的 $(x-y)$ 个 $1$ 最大子段和为 $x-y \ge 1$，则生成的整个序列的最大子段和为 $\max(1,x-y)=x-y$。

显然原序列的最大子段和最小值就是 $x-y$，即全选，所以这种方法可以生成最小的最大子段和。（感谢出题人 @[cyffff](https://www.luogu.com.cn/user/365127) 的[帮助](https://www.luogu.com.cn/discuss/530866)）

---

当 $x>y$ 时，一个疑点就是将 $y$ 个 $-1$ 距离平均地放进 $x$ 个 $1$ 中，这也是我的第一种思路。（记作方法二，上面的记作方法一）  
例如，当 $x=5,y=3$ 时，两种方法产生的序列如下：

$$\underline{1\;1\;-\!1}\;\underline{1\;1\;-\!1}\;1\;-\!1\quad(\text{Idea }1)$$
$$\underline{1\;-\!1}\;\underline{1\;-\!1}\;\underline{1\;-\!1}\;1\;1\quad(\text{Idea }2)$$


显然它们两个最大子段和分别为 $3,2$（分别选取 $1,1,-1,1,1,-1,1$ 和 $1,1$）。所以按照方法一构造序列的最大子段和最小。

## 程序

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int tmp;
// 1,-1 的个数
int x,y;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i) // 统计 x,y
    {
        scanf("%d",&tmp);
        if(tmp==1)
            ++x;
        else
            ++y;
    }
    if(x<=y)
    {
        for(int i=1;i<=x;++i)
        {
            printf("1 -1 ");
        }
        for(int i=1;i<=y-x;++i)
        {
            printf("-1 ");
        }
    }
    else
    {
        for(int i=1;i<=y;++i)
        {
            printf("1 -1 ");
        }
        for(int i=1;i<=x-y;++i)
        {
            printf("1 ");
        }
    }
    return 0;
}
```

---

## 作者：李卓衡001 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P8847)

题目大意
-
将一个仅有$ \ {1,-1}\ $的序列 $ a $ 重新排列，使得重新排列后的序列的最大子段和最小。

思路
-
设有 $ x $ 个$ \ {1}\ $， $ y $ 个$ \ {-1}\ $。

- 如果 $ x $ $ \geq $ $ y $ ，先将$ \ {1}\ $与$ \ {-1}\ $交替输出 $ y $ 次，再输出 $ x-y $ 个$ \ {1}\ $。

- 如果 $ x $ $ < $ $ y $ ，先将$ \ {-1}\ $与$ \ {1}\ $交替输出 $ x $ 次，再输出 $ y-x $ 个$ \ {-1}\ $。

满分代码：
-
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000000+10;
int n,cnt1=0,cnt2=0,a[maxn];//cnt1用来统计1的个数，cnt2用来统计-1的个数
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i]==1) cnt1++;
		else cnt2++;
	}
	if(cnt1>=cnt2){
		for(int i=1;i<=cnt2;i++) cout<<1<<" "<<-1<<" ";
		for(int i=1;i<=cnt1-cnt2;i++) cout<<1<<" ";
	}
	else {
		for(int i=1;i<=cnt1;i++) cout<<-1<<" "<<1<<" ";
		for(int i=1;i<=cnt2-cnt1;i++) cout<<-1<<" ";
	}
	return 0;
}
```

---

## 作者：what_can_I_do (赞：1)

[传送门](https://www.luogu.com.cn/problem/P8847)

其实这里的最大子段和就是原序列所有的数相加的和，或者说就是数字 $1$ 比 $-1$ 多几个。

那么我们已经知道了这一个条件，就可以在前面先全输出 $1$ 和 $-1$，让它们互相两两抵消为 $0$，最后再把剩下的数全输出就行了。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,one=0,zero=0,x;
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		if(x==-1) zero++;else one++;
	}
	while(zero&&one) cout<<"1 -1 ",zero--,one--;
	if(one) for(register int i=1;i<=one;i++) cout<<"1 ";
	else for(register int i=1;i<=zero;i++) cout<<"-1 ";
	return 0;
}
```

---

## 作者：幻想繁星 (赞：0)

# 1、题意
给你一个由 $1$ 和 $-1$ 构成的数列，将其重构，使最大子段和最小。

# 2、分析
首先，只要数列里含有 $1$ 那么最大子段和最小为 $1$，所以我们考虑下面两种情况：  
- $-1$ 的个数多于等于 $1$，那么我们只要用 $-1$ 将 $1$ 全部隔开，然后将所有多余的 $-1$ 排在数列尾即可，此时最大子段和为 $1$。  
$$\{1,-1,1,-1,1,\dots,1,-1,-1,-1,-1\}$$
- $1$ 的个数多于 $-1$，那么我们为了防止多个 $1$ 在一起使最大子段和大，那么我们尽量用 $-1$ 去将 $1$ 隔开使全前缀和为 $0$，多余的 $1$ 全部排在数列尾即可，此时最大子段和为 $1$ 的个数减去 $-1$ 的个数的差。
$$\{1,-1,1,-1,1,\dots,1,-1,1,1,1,1\}$$

# 3、代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,a,z=0,f=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		if(a>0)
			z++;//统计1的个数 
		else
			f++;//统计-1的个数 
	}
	if(z<=f)//-1比1多 
	{
		for(int i=1;i<=z;i++)
			cout<<"1 -1 ";
		for(int i=1;i<=f-z;i++)
			cout<<"-1 ";
	}
	else//1比-1多 
	{
		for(int i=1;i<=f;i++)
			cout<<"1 -1 ";
		for(int i=1;i<=z-f;i++)
			cout<<"1 ";
	}
	return 0;
}

```


---

## 作者：Elairin176 (赞：0)

究极水题。     
[传送门](https://www.luogu.com.cn/problem/P8847)     
我们知道，$1+(-1)=0$。    
因为这两个数字互相抵消，所以我们先一对一对地输出。    
这里要注意一个点：一定要先输出 $1$，如果把 $1$ 放到后面会出错。因为如果后面的全是 $1$，最大子段和就无法最小化。      
最后我们输出剩下的 $-1$ 或 $1$ 即可。   
CODE：   
```cpp
#include <iostream>
using namespace std;
int n,z,f,x;
int main(void){
	scanf("%d",&n);
	while(n--){
		scanf("%d",&x);
		if(x==1){//统计数字个数
			z++;
		}else{
			f++;
		}
	}
	while(z&&f){//首先输出1 -1
		printf("1 -1 ");
		z--;
		f--;
	}
	while(f--){//这里先负再正，也可以先正再负。
		printf("-1 ");
	}
	while(z--){
		printf("1 ");
	}
}
```


---

## 作者：AKPC (赞：0)

### 题意
桌上有 $n$ 张标有数字的牌，输出怎么排列使得标的数字的最大子段和最小。
### 对于本题的思路
对于本题，很简单，因为 $a_i$ 只可能是 $1$ 或者 $-1$，而且最大子段和至少为这 $n$ 个数的和，所以我们可以分类讨论（这里设 $1,-1$ 分别出现 $x,y$ 次）：

- 如果 $x=y$，输出 $1$ 与 $-1$ 的操作交错进行 $\dfrac {n}{2}$ 次即可。

- 如果 $x<y$，输出 $1$ 与 $-1$ 的操作交错进行 $x$ 次，然后输出 $y-x$ 个 $-1$ 即可。

- 如果 $x>y$，输出 $1$ 与 $-1$ 的操作交错进行 $y$ 次，然后输出 $x-y$ 个 $1$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a,cnt1,cnt2;
int main(){
	cin>>n;
	for (int i=0;i<n;i++){
		cin>>a;
		a==1?cnt1++:cnt2++;
	}
    if (cnt1==cnt2) for (int i=0;i<n/2;i++) cout<<"1 -1 ";
    else if (cnt1<cnt2){
        for (int i=0;i<cnt1;i++) cout<<"1 -1 ";
        for (int i=0;i<cnt2-cnt1;i++) cout<<"-1 ";
    }
    else{
        for (int i=0;i<cnt2;i++) cout<<"1 -1 ";
        for (int i=0;i<cnt1-cnt2;i++) cout<<"1 ";
    }
	return 0;
}
```


---

