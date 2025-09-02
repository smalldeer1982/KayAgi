# Lunar New Year and Number Division

## 题目描述

新年来了，Bob 正被他的家庭作业所为难，他需要完成一个划分数字的作业。

Bob 的作业上有 $n$ 个正整数 $a_1,a_2,{\dots},a_n$，其中 $n$ 为偶数，他要把这些数字进行分组，每组至少两个数字，假设分成了 $m$ 组，第 $j$ 组的数字之和是 $s_j$，Bob 需要最小化 $s_j$ 的平方和，即 $\sum^{m}_{j=1} s_j^2$。

Bob 被这题难住了，你可以帮帮他吗？

## 说明/提示

对于 $100\%$ 的数据，有 $2\leq n\leq 3\times 10^5, 1 \leq a_i \leq 10^4$。

## 样例 #1

### 输入

```
4
8 5 2 3
```

### 输出

```
164
```

## 样例 #2

### 输入

```
6
1 1 1 2 2 2
```

### 输出

```
27
```

# 题解

## 作者：Anguei (赞：4)

题目中保证 $N$ 是偶数，且要求每组分组都至少包含两个元素，这是一个相当大的提示：分出 $\frac{N}{2}$ 组数字，每组数字一最大一最小。

具体证明好像要用重排不等式，我不太会。翻译一下 jlf 老师的官方题解（翻译的可能不太好，见谅)：

> 这个题看起来很简单，证明也很简单。由于 $n$ 是偶数，所以最优分组策略是：最小的与最大的分一个组，第二小的与第二大的分一个组，以此类推。

> 首先，很容易证明这些数字的最佳分组时两两分组，所以证明是作为练习留给读者的。（大佬写证明怎么都这样 /(ㄒoㄒ)/~~

> 第二部分的证明是关于重排不等式的. 考虑排列 ${a_i}$. 假设有 ${b_i}$,${c_i}$ 且 $b_i=c_j$ 当且仅当 $b_j=c_i$. 那么它们的和 $$\frac{1}{2} \sum_{i=1}^{n}\left(b_{i}+c_{i}\right)^{2}$$ 就是 ${a_i}$ 的分组策略之一. 但我们关心的不是 $$\frac{1}{2} \sum_{i=1}^{n}\left(b_{i}^{2}+c_{i}^{2}\right)$$ 我们只想减小 $\sum_{i=1}^{n} b_{i} c_{i}$. 这就直接应用了重排不等式。

> **时间复杂度**: $\mathcal{O}(n \log n)$

```cpp
#define int long long
const int N = 300000 + 5;
int n, s = 0, a[N];

int sqr(int x) { return x * x; }
void solution() {
    n = read(); rep(i, 1, n) a[i] = read();
    std::sort(a + 1, a + n + 1);
    rep(i, 1, n >> 1) s += sqr(a[i] + a[n + 1 - i]);
    println(s);
}
```

---

## 作者：fmj_123 (赞：3)

题意：给定一个$n$个数的序列($n$为偶数) 。将数列组合为若干组。每组的数的个数至少为2。
求每一组数的和平方后，所有组之和的最小值。

思路:

我们很容易想到，排序后，第$i$小与第$i$大两两配对就行了。

**证明**：

A.两两配对更优

因为假设两个数组合起来$(a+b)^2=a^2+2ab+b^2$，相比于$ a^2+b^2$，只会多了个$2ab$的项

如果是三个数组合起来，那么是$(a+b+c)^2 =a^2+b^2+c^2+2ab+2ac+2bc$，会多3个类似$2ab$的项。以此类推。

题目已经说明所有数均大于0，显然我们无法在$a^2$这种项下功夫，所以只要类似$2ab$的项越少，答案就越小。

假设两两组合，所得的这种$2ab$的项是最少的。

Q.E.D

B.小的与大的配对更优

假设$a<b<c<d$，则问题转化为证明$ac+bd - ad-bc\ge0$ 

$ac+bd-ad-bc$

$=(a-b)c + (b-a)d$

$= -(b-a)c + (b-a) d$

$ \because c<d$

$\therefore (b-a)c <(b-a)d$

$\therefore -(b-a)c +(b-a)d >0$

$\therefore ac+bd-ad-bc>0$

Q.E.D.

上代码

```C++
#include<bits/stdc++.h>
using namespace std;
long long n,a[300100],ans;
int main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
	  cin>>a[i];
	sort(a+1,a+1+n);
	for (int i=1;i<=n/2;i++)
	{
		ans+=(a[i]+a[n-i+1])*(a[i]+a[n-i+1]);
	}
	cout<<ans<<endl;
	return 0;
}

```



---

## 作者：_Weslie_ (赞：1)

~~本题应该降橙~~

## [CF1106C题目传送门](https://www.luogu.com.cn/problem/CF1106C)


------------

## 题意简述

给你 $\ n\ $ 个数，求这些数分组后平方和的最小值。

一组至少要有 $\ 2\ $ 个数。

题目保证 $\ n\ $ 是偶数。

## 思路

这个问题我们需要证明一个点：

$1$：一个排好序后的数组，分组后平方和的最小值一定是让 $\ a_i\ $ 和 $\ a_{n-i+1}\ $ 相加。

众所周知，在 $\ a>b\ $ 的情况下， $\ a^2>b^2$。

所以我们让 $\ \forall i,j\ \ \ \ \ i+j\ $ 尽可能的小？

不是的。

因为一个 $\ 1,2,45,99\ $ 的数组，按这种方式答案是 $\ 20735$。

然而，实际的解是 $\ 12209$。

所以，我们让 $\ \forall i,j\ \ \ \ \ i+j\ $ 尽可能平均。

为什么要平均呢？

看这个例子就知道了：

$$47^2+47^2=4418\ \ \ 48^2+46^2=4420$$

再到 $\ (49,45)\ $ 就不用说了，肯定更大。

所以，分成任意组，极差越大，答案越大。

而我们求的是最小，所以我们应该让它平均分。

而为了平均分，我们需要使用时间复杂度为 $\ \operatorname{O}(n \log n)\ $ 的 $\ \operatorname{sort}\ $ 排序。

当然，手打快排，归并等时间复杂度为 $\ \operatorname{O}(n \log n)\ $ 的排序也没有问题，但不能用 $\ \operatorname{O}(n^2)\ $ 的排序，因为会 $\ \text{TLE}$。

最后，还有 $\ \text{O}(n)\ $ 的桶排序代码，可以过 $10^7$。

（正常 $\ \text{sort}\ $ 能过本题 $\ 3×10^5$，但过不了 $\ 10^7$）

## ctjer 最喜欢的代码环节

### AC Code 1：$\text{O}(n\log n)$

```
#include<iostream>
#include<algorithm>
using namespace std;
int a[300001],n;
long long ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n/2;i++){
		ans+=(a[i]+a[n-i+1])*(a[i]+a[n-i+1]);
	}
	cout<<ans;
	return 0;
}
```

### AC Code 2：$\text{O}(n)$

```
#include<iostream>
#include<algorithm>
using namespace std;
int a[300001],x,n,b[10001],p;
long long ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x;
       	b[x]++;
	}
	for(int i=1;i<=10000;i++){
        for(int j=1;j<=b[i];j++){
            a[++p]=i;
        }
    }
    for(int i=1;i<=p/2;i++){
    	ans+=(a[i]+a[n-i+1])*(a[i]+a[n-i+1]);
	}
	cout<<ans;
	return 0;
}
```

感谢各位在评论区 $\ hack\ $ 的大佬们~

---

## 作者：Morax2022 (赞：0)

# Solution
**贪心**

给进来的数，排完序后若分组后要 $(a + b)^2$ 最小，就定然要平均分。

为什么呢？原因很简单，和一定，差小积大，所以要尽量接近，采用平均分。

而最平均的分配自然是 $a_i$ 和 $a_{n-i+1}$ 了。

# AC Code
```c
#include <bits/stdc++.h>
using namespace std;
int a[300001], n;
long long sum = 0;
int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++) {cin >> a[i];}
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n / 2; i++) //共n/2组
	sum += (a[i] + a[n - i + 1]) * (a[i] + a[n - i + 1]);
	//每组最平均的就是i项加n-i+1就是i的对称项 
	cout << sum;
}
```
希望本题解能给大家带来帮助！

---

## 作者：Lacrymabre (赞：0)

题意简述：对于一个数列$s$，将它们构成$\frac{n}{2}$个不同的$m$个组，使得这些组的乘积之和最小。

容易得知，将序列**排序**之后，用两个数进行组合，代价总是小于三个或三个以上的组合，因为三个数之和乘方会比两个数的和多出$2ac+2bc$的这两个项。

而使用最大的和最小的数进行组合，则比用两个最大的进行组合更优。

假设这个序列都比$a$这个数大，则可以将这个序列描述为

$a+x,a+y,a+t,a+r……$

若是选择两个最大的进行平方，则有$(2a+(t+r))^2+(2a+(x+y))^2$
若是选择一个最大的和一个最小的进行平方，则有$(2a+(x+r))^2+(2a+(t+y))^2$


因为这个数列**单调不递减**，所以总有$x≤y≤t≤r$，所以只需要证明$xr+yt≤tr+xy$,即$sum=xr+yt-tr-xy≤0$。

提取出$sum=t(y-r)+x(r-y)≤0$，显然$y-r≤0,r-y≤0$，所以整体$sum≤0$。

因为$m≤2$，所以无法每组一个一个地分，因为整个数列的每一个数都存在$0≤s_i$，所以也无法在$x^2,y^2$之类这些项来优化值。所以分为$\frac{n}{2}$个二元组，每组使用最大和最小的数组合可以得到最小值。

可以使用堆来维护最大和最小值


代码实现如下：

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;

inline long long read()
{
    ll f=1,s=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=(s<<1)+(s<<3)+ch-'0',ch=getchar();
    return s*f;
}

ll s[5000005];
ll n,len,ans,deletes;

priority_queue<ll>a,b;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i],a.push(s[i]),b.push(-s[i]);
	for(int i=1;i<=n/2;i++){
		ans+=(a.top()-b.top())*(a.top()-b.top());
        a.pop();b.pop();
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：KagurazakaKano (赞：0)

补充一下 Anguei 老师的题解：$$(a+b)^2=a^2+b^2+2ab$$

即答案$$\frac{1}{2} \sum_{i = 1}^{n} (b_i + c_i)^2=\frac{1}{2} \sum_{i = 1}^{n} (b_i^2 + c_i^2+2b_ic_i)$$

又因为 $a^2,b^2$ 在无论 $a,b$ 如何排列的情况下，都是相等的，所以最终影响答案的**只是：**$2ab$ 这一项。

设$z_1, z_2, \dots, z_{\frac{n}{2}}$ 以及 $z_{\frac{n}{2} + 1}, z_{{\frac{n}{2}} + 2}, \dots, z_n$ 分别为原数组分开后的两个单调增的排列。

再设数组 $x$ 为 后半部分的任意一个排列。

那么我们需要的结果$$S=z_1x_1+z_2x_2+\dots+z_{\frac{n}{2}}x_{\frac{n}{2}}\text{ (1)}$$

全排列有 $(\frac{n}{2})!$ 个，显然有最大值和最小值。

考虑 $(1)$ 式，若 $x_1 \neq y_1$（注：这里 $y$ 只是原 $z$ 数组的后半部分，为了书写方便笔者暂时用 $y$ 数组来替代），则显然有某 $x_k =y_1(k > 1), x_1 > x_k$。

那么将 $(1)$ 式中的 $x_1$ 与 $x_k$ 对调，则设
$$S'=z_1x_k + \dots + z_kx_1 + \dots + z_{\frac{n}{2}}x_{\frac{n}{2}}$$

易证 $$S'-S \ge 0 \text{（两式相减提取公因式即可）}$$

类似地，我们可以经过有限步的调整，得到：**原始最小值为反序和**。

**拓展：请读者自行证明：原式最大值为顺序和。（提示：证明方法类似）**

---

## 作者：FP·荷兰猪 (赞：0)

这题看着英文题面好像很难似的，其实就是一道简单的小学数论~~（论学好小学奥数的重要性）~~

由于n是偶数，又可以每组分两个数，故当然是每组两个数，共分n/2组和最小。

然而应该怎么分组呢？

我们可以考虑现将这n个数从小到大排序，复杂度为O(nlogn)。由于要把每组数的平方和相加，所以一定是最大的和最小的一组；次大的和次小的一组......以此类推。剩下的就是模拟了。

~~我绝不会告诉你比赛时这题我规律八成靠猜~~
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin>>n;
    long long a[n+1],i;
    for (i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    sort(a+1,a+n+1);
    long long cnt,ans;
    ans=0;
    for (i=1;i<=n/2;i++)
    {
        cnt=(a[i]+a[n-i+1])*(a[i]+a[n-i+1]);
        ans+=cnt;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

