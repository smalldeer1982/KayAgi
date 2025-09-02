# Pipeline

## 题目描述

Vova, the Ultimate Thule new shaman, wants to build a pipeline. As there are exactly $ n $ houses in Ultimate Thule, Vova wants the city to have exactly $ n $ pipes, each such pipe should be connected to the water supply. A pipe can be connected to the water supply if there's water flowing out of it. Initially Vova has only one pipe with flowing water. Besides, Vova has several splitters.

A splitter is a construction that consists of one input (it can be connected to a water pipe) and $ x $ output pipes. When a splitter is connected to a water pipe, water flows from each output pipe. You can assume that the output pipes are ordinary pipes. For example, you can connect water supply to such pipe if there's water flowing out from it. At most one splitter can be connected to any water pipe.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF287B/d347ad4c15760876dd4efdb4df653ce9dd1bfe47.png)The figure shows a $ 4 $ -output splitterVova has one splitter of each kind: with $ 2 $ , $ 3 $ , $ 4 $ , ..., $ k $ outputs. Help Vova use the minimum number of splitters to build the required pipeline or otherwise state that it's impossible.

Vova needs the pipeline to have exactly $ n $ pipes with flowing out water. Note that some of those pipes can be the output pipes of the splitters.

## 样例 #1

### 输入

```
4 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 5
```

### 输出

```
1
```

## 样例 #3

### 输入

```
8 4
```

### 输出

```
-1
```

# 题解

## 作者：_lxy_ (赞：4)

### 题意
有 $n$ 个客户，一个水源和 $k-1$ 个分离器，第 $i$ 个分离器能将 $1$ 股水流分离成 $i+1$ 股水流，问最少使用多少个分离器能使 $n$ 个客户都通水。如果不能就输出 $-1$ 。
### 分析
首先看到数据范围的时候，能够想到应该是 $\log_{2}k$ 的时间复杂度，并且通水的客户数随分离器数量的增加而增加，因此想到可以用二分枚举分离器的数量，判断是否能给 $n$  个客户通水，得到答案。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k,ans; // 注意开long long
int check(ll mid)
{
    ll x=(2*k-(mid-1))*mid/2-mid+1; // 1个分离成k股水的分离器能使水的股数增加(k-1)
    return x>=n;
}
int main()
{
    scanf("%lld%lld",&n,&k);
    if(n==1) // 这里要特判一下，如果只有1个客户，那么不需要分离器
    {
        printf("0\n");
        return 0;
    }
    ans=-1;
    ll l=1,r=k-1;
    while(l<=r) // 二分
    {
        ll mid=(l+r)/2;
        int flag=check(mid);
        if(flag) // 符合条件，能给n个客户通水
        {
            ans=mid; // 更新答案
            r=mid-1; // 看看能不能用更少的分离器
        }
        else l=mid+1; // 只能使用更多的分离器
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：AKPC (赞：2)

### 简要题意
这里把原题化简了一下。

有一个数 $n$，开始的时候先给 $n$ 减去 $1$（因为在起初你已经有了一根主水管），给定一些操作，每次可以让 $n$ 减去 $1\sim (k-1)$ 里的任意一个数（因为接上一个分离器需要先耗费一个管道），但是一个数只能减一次，这样的操作最多执行 $k-1$ 次。求问最少多少个操作可以让 $n\leq0$。
### 思路
本题 $1\leq n\leq 10^{18}$，而显然答案具有**单调性**，考虑**二分**操作的个数，然后 `check` 判断。

然后就是 `check` 的写法了。考虑**贪心**，虽然操作说的是减去 $2\sim k$ 的任意一个数，但是显然先减去大数会更优，所以题目转化为第 $i$ 次操作将 $n$ 减去 $k-i$。

然后就是快速求出每次减去值的和了。小学的等差数列求和公式直接套用就行了。如果下面这个值 $\geq n$ 也就可以达成条件了。

$$\displaystyle\sum_{i=1}^{mid}(k-i)=\dfrac{[(k-1)+(k-mid)]\times mid}{2}$$

贪心 `check` 的复杂度是 $\text O(1)$ 的，乘上前面二分的复杂度即 $\text O(\log n)$，这显然可以通过 $n\leq10^{18}$ 的数据了。

注意特判，在二分之前，求这个值，也就是所有操作加起来能够减多少。如果给 $n$ 减去这个和不能让 $n\leq0$，那么直接输出 $-1$ 表示无解。

$$\displaystyle\sum_{i=1}^{k-1}(k-i)=\dfrac{k(k-1)}{2}$$
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,k,l,r;
signed main(){
	cin>>n>>k,l=0,r=k-1;
	if (k*(k-1)/2<--n){
		cout<<-1;
		return 0;
	}
	while (l<r){
		int mid=(l+r)/2;
		if ((k-1+k-mid)*mid/2>=n) r=mid;
		else l=mid+1;
	}
	cout<<l;
	return 0;
}
```


---

## 作者：静谧幽蓝 (赞：2)

### 题意

有 $m$ 个水管，第 $i$ 个水管需要花费 $1$ 个接口，增加 $i$ 个接口，现在你有 $1$ 个接口，求需要多少个水管才能使接口数为 $n$。

### 解法

#### 1.二分

题意转换过来就是有 $m-1$ 个水管，第 $i$ 个水管可以增加 $i$ 个接口。

由于在 CF 上时限为 **400ms**，所以考虑二分答案，判断是否合法的时候贪心，假设二分到 $k$，则贪心取最大的 $k$ 个水管，如果接口数大于 $n$，则合法。

注意判断所有接口接上都不够总数的情况。

复杂度 $O(\log m)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long

int n,m;

bool check(int x)
{
    int temp=((m-1)+(m-x))*(x)/2;
    return temp>=n;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    /* Code */
    cin>>n>>m;
    if(n>m*(m-1)/2+1)
    {
        cout<<"-1\n";
        return 0;
    }
    n--;
    int l=0,r=m;
    while(l<r)
    {
        int mid=(l+r)>>1;
        if(check(mid))
            r=mid;
        else
            l=mid+1;
    }
    cout<<l<<'\n';
    return 0;
}
```

#### 2.爆算等式

根据上面的等式，我们假设要接上 $k$ 个水管，可以列出这么一个等式：

$$\frac{((m-1)+(m-k))k}{2}+1=n$$

其中 $m$ 代表水管个数，$n$ 代表接口总数。

简化得到：

$$-k^{2}+\left(2m-1\right)k+2\left(1-n\right)=0$$

他的判别式 $\Delta=(2m-1)^2-4\times(-1)\times2(1-n)=(2m-1)^2+8(1-n)$ 在 $n>\dfrac{1}{2}m\left(m-1\right)+\dfrac{9}{8}$  时为负，无实根。

根据二次方程求根公式，我们可以得到：

$$x=\frac{-\left(2m-1\right)\pm\sqrt{\left(2m-1\right)^{2}+8\left(1-n\right)}}{-2}$$

上面这个式子在 $(1-n)>0$ 时有一个负根，但是题目中写了 $n\ge 1$，所以这个方程没有负根，于是我们只要取较小的一个根就可以了。

注意上取整后再输出。

复杂度 $O(1)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

long double n,m;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    /* Code */
    cin>>n>>m;
    if(n>m*(m-1)/2.00+9.00/8.00)
    {
        cout<<"-1\n";
        return 0;
    }
    long double root1=(-(2*m-1.00)-sqrtl((2*m-1)*(2*m-1)+8*(1-n)))/(-2.00);
    long double root2=(-(2*m-1.00)+sqrtl((2*m-1)*(2*m-1)+8*(1-n)))/(-2.00);
    cout<<(long long)(ceill(min(root1,root2)))<<'\n';
    return 0;
}
```

---

## 作者：Fa1thful (赞：2)

### 1.题意：
有一个水源，有 $k-1$ 个疏通器，每个疏通器有它的编号加一个疏通管道，以及一个入口。入口可以连接水源或者其他疏通器的疏通管道，疏通管道的作用是将水划分成管道个数份流出。


![](https://cdn.luogu.com.cn/upload/image_hosting/iz5lewgd.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

问最少用多少个疏通器可以将水源划分成 $n$ 份流出。
### 2.分析：
首先看到数据范围，这道题的正解肯定只能用 $O(1)$ 或者$O(logk)$，但是我们需要寻找多少个疏通管道，所以肯定跟k有关，所以就用 $logk$。然后 $logk$ 的枚举疏通器个数办法只有二分，所以这道题我们用二分来做。

但是二分虽然简单，$check$ 好似需要用 $mid$ 层循环来检查是否可以分成 $n$ 份水，所以我必须要用一个 $O(1)$ 的办法来检查。

二分是一个逐渐接近正确答案的过程，所以我们只需要考虑哪几种情况应该要向哪个方向寻找正确答案即可，这里我分出了三种情况：

(1).最大值比 $n$ 小。

(2).最小值比 $n$ 小且最大值比 $n$ 大。

(3).最小值比 $n$ 大。

注：最大值最小值指用 $mid$ 个疏通器最多或最少能将水源分成多少份。

那么这些情况分别该如何解决呢？

(1).最大值比 $n$ 小：说明疏通器个数太少了，增加疏通器。

(2).最小值比 $n$ 小且最大值比 $n$ 大：一定可以通过把疏通管道多的疏通器分到最小值或者把疏通管道少的疏通器分到最大值里来平衡出 $n$ 。

(3).最小值比 $n$ 大：说明疏通器个数太多了，减少疏通器。

现在二分思路很清晰了，下面见代码。
### 3.代码
```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;
long long n, k;
int check(int x)
{
    if ((k - x + 1 + k) * x / 2 - x + 1 >= n && (1 + x) * x / 2 + 1 <= n) return 1;//最小值小于n，最大值大于n 
    if ((k - x + 1 + k) * x / 2 - x + 1 <= n) return 2;//最大值小于n 
    if ((1 + x) * x / 2 + 1 >= n) return 0;//最小值大于n 
}
signed main()
{
	scanf("%lld%lld", &n, &k);
	long long l = 1;
	long long r = k;
	long long ans = -1;
	if (n == 1)  //如果n等于一则不需要任何疏通器，而且不会被记录ans 
	{
		cout << 0 << endl;  //提前特判输出0 
		return 0;
	}
	while (l <= r)
	{
		long long mid = (l + r) / 2; //二分模板 
		if (check(mid) == 1) //如果最小值小于n，最大值大于n 
		{
			ans = mid;   //一定可以通过将最大的里面调到最小的或最小的里面调到最大的来达到n，记录答案 
			r = mid - 1; //看看能不能用更少的疏通器 
		}
		else if (check(mid) == 2) l = mid + 1;  //疏通器少了 
		else if (check(mid) == 0) r = mid - 1;  //疏通器多了 
	}
	printf("%lld\n", ans);
	return 0;
}
```
附：
#### 最大值最小值如何用O(1)公式求出？
因为 $mid$ 个疏通器最大的情况是从 $k$ 递减到 $mid$ 。最小的情况是从 $2$ 递增到 $mid$ ，所以只需要用等差数列求和公式计算即可。


---

## 作者：Speech_less (赞：1)

# CF287B Pipeline 题解
## 题目大意
现在有 $k-1$ 个接口，第 $k$ 个接口可以分出 $k+1$ 根水管，问：当需要 $x$ 根水管时，最少需要多少个接口？

## 解析
其实本题就只是一个简单的二分答案模板，只要推出使用 $mid$ 个接口时，可以分出水管的个数 $x$ ，即 $x$ 关于 $mid$ 的函数，这道题就很简单了。可以简单地推导出：

$$x=\frac{(2 \times k - mid + 1) \times mid}{2} - mid + 1$$

在写二分的内容时记得要使用 $ans$ 来存 $mid$ 的值，不然会被 hack 掉。

------------

## AC 代码上交
```cpp
#include<bits/stdc++.h>
#define lld long long
using namespace std;
int main(){
	lld n,k,sum=0;
	cin>>n>>k;
	if(n==1){
		cout<<0<<endl;
		return 0;
	}
	lld l=1,r=k-1,mid,ans=-1;
	while(l<=r){
		mid=(l+r)/2;
		lld md=(2*k-mid+1)*mid/2-mid+1;
		if(md>=n) ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}

```

------------

\*注：切记勿抄袭，抄袭马上变棕名。

---

## 作者：foryou_ (赞：1)

我们知道，能通水的客户随着分离器的增加而增加，即**答案具有单调性**。

于是可以很自然地想到二分分离器的数量 $x$，取 $k$ 个分离器中**编号最大**的 $x$ 个，贪心地检验是否能够让 $n$ 个客户均通水。

关于 `check` 函数的设计：

- 编号最大的 $x$ 个管子的编号分别为 $k-x \sim k-1$；

- 因此它们**增加的水流数**也是 $k-x \sim k-1$；

- 根据等差数列求和的知识，我们可知它们总共增加的水流数为 $(k-x+k-1) \times x \div 2$；

- 于是，若上式 $\ge n$，则进入左区间，反之进入右区间。这便完成了 `check` 函数的设计。

关于特判：

- 根据上面的分析，我们知道，若将 $k$ 个分离器都用上，则它们**总共的水流数**为 $(k-1) \times k \div 2 + 1$。

- 因此，若上式 $< n$，即将 $k$ 个分离器都用上仍无法满足 $n$ 个客户，则直接输出 `-1`。

注意事项：

- 记得开 `long long`；

- 为了方便处理，输入 $n$ 后要将 $n \gets n-1$。

时间复杂度为 $O(\log k)$。

代码十分好写，故不再展示了。

---

## 作者：啊吧怪 (赞：0)

### 题意

有一条水流， $k-1$ 个分离器，第 $i$ 个分离器可以增加 $i$ 条水流，求用最少的分离器将其分成 $n$ 条水流。

### 解析

显然先用编号大的分离器更优，但是由于 $k \le 10^9$，所以考虑用更优的二分法，二分所需分离器数量。

若二分值为 $mid$ 用等差数列的知识可得总水流数为

$$\dfrac{[(k-1)+(k-mid)] \times mid}{2}$$

同时特判一下答案为 $-1$ 的情况即可，时间复杂度为 $O(\log k)$。

### 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,k,l,r;
int main()
{
	cin>>n>>k;
	n--;
	if(k*(k-1)/2<n)
	{
		cout<<-1;
		return 0;
	}
	r=k-1;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if((k-1+k-mid)*mid/2>=n) r=mid;
		else l=mid+1;
	}
	cout<<l;
	return 0;
}
```


---

