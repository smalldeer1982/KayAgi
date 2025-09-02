# Timofey and cubes

## 题目描述

Young Timofey has a birthday today! He got kit of $ n $ cubes as a birthday present from his parents. Every cube has a number $ a_{i} $ , which is written on it. Timofey put all the cubes in a row and went to unpack other presents.

In this time, Timofey's elder brother, Dima reordered the cubes using the following rule. Suppose the cubes are numbered from $ 1 $ to $ n $ in their order. Dima performs several steps, on step $ i $ he reverses the segment of cubes from $ i $ -th to $ (n-i+1) $ -th. He does this while $ i<=n-i+1 $ .

After performing the operations Dima went away, being very proud of himself. When Timofey returned to his cubes, he understood that their order was changed. Help Timofey as fast as you can and save the holiday — restore the initial order of the cubes using information of their current location.

## 说明/提示

Consider the first sample.

1. At the begining row was \[ $ 2 $ , $ 3 $ , $ 9 $ , $ 6 $ , $ 7 $ , $ 1 $ , $ 4 $ \].
2. After first operation row was \[ $ 4 $ , $ 1 $ , $ 7 $ , $ 6 $ , $ 9 $ , $ 3 $ , $ 2 $ \].
3. After second operation row was \[ $ 4 $ , $ 3 $ , $ 9 $ , $ 6 $ , $ 7 $ , $ 1 $ , $ 2 $ \].
4. After third operation row was \[ $ 4 $ , $ 3 $ , $ 7 $ , $ 6 $ , $ 9 $ , $ 1 $ , $ 2 $ \].
5. At fourth operation we reverse just middle element, so nothing has changed. The final row is \[ $ 4 $ , $ 3 $ , $ 7 $ , $ 6 $ , $ 9 $ , $ 1 $ , $ 2 $ \]. So the answer for this case is row \[ $ 2 $ , $ 3 $ , $ 9 $ , $ 6 $ , $ 7 $ , $ 1 $ , $ 4 $ \].

## 样例 #1

### 输入

```
7
4 3 7 6 9 1 2
```

### 输出

```
2 3 9 6 7 1 4```

## 样例 #2

### 输入

```
8
6 1 4 2 5 6 9 2
```

### 输出

```
2 1 6 2 5 4 9 6```

# 题解

## 作者：老彩笔 (赞：2)

这道题如果暴力枚举i然后reverse显然是不行的，复杂度最大是O（n^2*logn）

那么我们来找一下规律：

```cpp

1 2 3 4 5 6 

转换完就是:

6 2 4 3 5 1 

```
可以发现只有(1,6),(3,4)交换了

因为(2,5)在 [1,6] 和 [3,4] 中交换了两次

所以交换次数是偶数次的,在最后的序列中是没有交换的

奇数次则交换

观察序列发现做区间是i的又区间是n-i+1
~~题目中也说了~~

这样我们只枚举n/2就行了

最后的复杂度是O(n)的

代码里我多开了一个数组,其实一个就够了,所以如果n是奇数,我就要特判一下:

如果n是奇数,在ans数组里的n/2+1的位置直接放入n/2+1就好了,因为最后的一个区间一定是[n/2+1,n/2+1]

最后空间复杂度也是O(n)的

代码如下:

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()//快读 
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10-48+ch;ch=getchar();}
	return x*f;
}
int n;
int a[200005];
int ans[200005],cnt;
int main()
{
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n/2;i++)
	{
		if(i%2==1)
		{
			ans[i]=a[n-i+1];
			ans[n-i+1]=a[i];
		}
		else
		{
			ans[i]=a[i];
			ans[n-i+1]=a[n-i+1];
		}
	}
	if(n%2==1)
		ans[n/2+1]=a[n/2+1];
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<' ';
	return 0;
}
```







---

## 作者：Noby_Glds (赞：0)

### 思路：
其实这道题在输入的时候就可以生成答案数列。

拿样例 $2$ 来说：$\texttt{6 1 4 2 5 6 9 2}$

把它从中间劈开，前面就是 $\texttt{6 1 4 2}$，叫第一部分，后面是 $\texttt{5 6 9 2}$，叫第二部分。

找规律就可以发现，在第一部分中，正数序号是奇数的，就要反转，在第二部分中，倒数序号是奇数的，就要反转。

我们可以把这些要反转的数直接输入到它反转之后的位置上去。

设它原来的位置是 $i$，那么它反转后的位置就是 $n-i+1$。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		if(min(i,n-i+1)%2==1) cin>>a[n-i+1];
		else cin>>a[i];
	}
	for(int i=1;i<=n;i++) cout<<a[i]<<" ";
    return 0;
}
```


---

## 作者：joy2010WonderMaker (赞：0)

### 题目大意

有一个数组，里面有 $n$ 个数，是 $a_1,a_2,a_3...a_n$，将$i$ 和 $n-i+1$ 区间里的所有数翻转，求原数组。

### 题目分析

因为样例，发现如果 $i$ $mod$ 2=0，那么对应的 $a_i$ 就等于 $a_{n-i+1}$，只需要交换这两个数即可。那么也就意味着我们不用将 $i$ 从 1 枚举到 $n$，只需要枚举到 $2i\le n$ 就可以了。

### 代码

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int a[200005];
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n/2;i=i+2)swap(a[i],a[n-i+1]);
    for(int i=1;i<=n;i++)printf("%d ",a[i]);
    return 0;
}
```


---

## 作者：zplqwq (赞：0)

**题目分析**：

题目大意：

- 有一个长度为 $n$ 序列 $a_1$,$a_2$,$a_3$...$a_n$，对于这个序列，只要  $i\leqslant n-i+1$，那么就将在 $i$ 和 $n-i+1$ 之间的所有数反转。现在已知反转后的序列，求反转前的序列。

做法分析：

不难发现，当 $i$ 为偶数时，对应的 $a_i$ 交换了 $2$ 次。因此可以得到，当 $i$ 为偶数时，$a_i=a_{n-i+1}$ 。因此我们只需要枚举 $i$ $(i =1,2i\leq n)$ , 然后交换$a_i$ 与 $a_{n-i+1}$ 即可。

代码就不放了。

---

## 作者：ForeverCC (赞：0)

枚举样例后不难发现当 $i\bmod2=0$ 时，$a_i$的值被交换了两次，所以能得出以下规律：

$a_i=a_{n-i+1}$ $(i\bmod2=0)$

所以我们就可以只枚举 $i\bmod2=0$ 的情况，得出以下代码：

```cpp
#include<iostream>
using namespace std;
int n,a[200005];

int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
		scanf("%d",&a[i]);
	for(int i=1; i<=n/2; i+=2)
		swap(a[i],a[n-i+1]);
	for(int i=1; i<=n; i++)
		printf("%d ",a[i]);
	return 0;
}
```


---

## 作者：CaiXY06 (赞：0)

观察样例我们会发现 $a_{i}(i$ $mod$ $2=0)$ 会保持不变， $a_{i}(i$ $mod$ $2=1)$ 会与 $a_{n-i+1}$ 交换位置。

原因是 $a_{i}(i$ $mod$ $2=0)$ 进行了偶数次交换，每两次交换相互抵消，相当于啥都没做，而 $a_{i}(i$ $mod$ $2=1)$ 在两两抵消的前提下又多进行了一次交换。

综上所述，我们只要直接枚举 $i(i$ $mod$ $2=1,2i\leq n)$ 交换 $a_{i}$ 和 $a_{n-i+1}$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200010];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n/2;i+=2)swap(a[i],a[n-i+1]);//交换
	for(int i=1;i<=n;i++)printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
有一个序列 $a_1,a_2,a_3,...,a_n$，对于 $i\in[1,n]$，只要 $i\leqslant n-i+1$，就把闭区间 $[i,n-i+1]$ 内的所有数翻转。现在给定你翻转后的序列，求原来的序列。

**数据范围：$1\leqslant n\leqslant 2\times 10^5,-10^9\leqslant a_i\leqslant 10^9$。**
## Solution
做这题之前，我们来看这个序列的规律：

首先拿出一个序列 $[2,6,8,4,1,5,7]$，明显地，此时，$n=7$。

1. $1\leqslant n-1+1$，所以将闭区间 $[1,n]$ 内的所有数翻转，变成了 $[7,5,1,4,8,6,2]$。
2. $2\leqslant n-2+1$，所以将闭区间 $[2,n-1]$ 内的所有数翻转，变成了 $[7,6,8,4,1,5,2]$。
3. $3\leqslant n-3+1$，所以将闭区间 $[3,n-2]$ 内的所有数翻转，变成了 $[7,6,1,4,8,5,2]$。
4. $4\leqslant n-4+1$，所以将闭区间 $[4,n-3]$ 内的所有数翻转，当然原序列是不变的。

我们发现：当偶数位上的数经过翻转后，它又返回到了原来的位置，而奇数位 $j$ 上的数经过翻转变到了 $n-j+1$ 的位置。所以，我们可以将对于 $i\in[1,n]$，只要 $i\leqslant n-i+1$ 并且 $i\equiv 1\pmod2$，就调换位置 $i$ 和位置 $n-i+1$ 上的数，最后可以得到我们想要的答案。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

int n, a[200007];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)	scanf("%d", &a[i]);
	for(int i = 1, j = n; i <= ceil(n / 2.0); i++, j--)
		if(i % 2)	swap(a[i], a[j]);
	for(int i = 1; i <= n; ++i)	printf("%d ", a[i]);
}
```

---

## 作者：oneman233 (赞：0)

~~这题我做的时候还是黄题~~

先说题意，给定一个数列，对所有的正整数i，不断逆转[i,n-i+1]这一段，直到i>n-i+1

实际上想通了就很简单，**每个数字的交换次数是确定的**。

比如首尾两个数字，他们被交换了一次，最后的结果就会倒转，而第二个和倒数第二个数字则被交换了两次，最后的结果则不会改变。

**用一个cnt变量记录一下交换次数，如果为奇数则交换它们，否则不交换。**

而且“交换”是可逆的，意味着如果交换（原序列）=现序列，那么交换（现序列）=原序列

~~顺便题面的翻译也是我交的~~

以下为AC代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int a[200005];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>a[i];
    int cnt=1;
    for(int i=1;i<=n-i+1;i++){
        if(cnt&1)
            swap(a[i],a[n-i+1]);
        cnt++;
    }
    for(int i=1;i<=n;++i)
        cout<<a[i]<<" ";
    return 0;
}

```


---

## 作者：AdzearDisjudge (赞：0)

根据题意枚举i暴力交换即可。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,n) for(register int i=a;i<=n;++i)
#define per(i,a,n) for(register int i=a;i>=n;--i)
#define mem(a) memset(a,0,sizeof(a))
#define elif else if
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
inline ll read()
{
    ll f=1,x=0;
    char ch;
    do
    {
        ch=getchar();
        if(ch=='-')
        f=-1;
    }
    while(ch<'0'||ch>'9');
    do
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    while(ch>='0'&&ch<='9');
    return f*x;
}
ll a[200001],n,s;
int main()
{
    cin>>n;
    for(ll i=1;i<=n;++i)
    cin>>a[i];
    for(ll i=1;i<=n/2;i+=2)
    {
        s=a[i];
        a[i]=a[n-i+1];
        a[n-i+1]=s;
    }
    for(ll i=1;i<n;++i)
    cout<<a[i]<<' ';
    cout<<a[n];
    return 0;
}
```

---

