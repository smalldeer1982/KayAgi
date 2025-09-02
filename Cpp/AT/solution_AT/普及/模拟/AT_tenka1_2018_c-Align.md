# Align

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2018/tasks/tenka1_2018_c

整数が $ N $ 個与えられます。$ i $ 個目の整数は $ A_i $ です。 これらを好きな順に一列に並べるとき、隣り合う要素の差の合計の最大値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力はすべて整数である

### Sample Explanation 1

$ 3,8,1,6,2 $ の順に並べたとき、隣り合う要素の差の合計は $ 21 $ になり、 これが達成できる最大の値です。

## 样例 #1

### 输入

```
5
6
8
1
2
3```

### 输出

```
21```

## 样例 #2

### 输入

```
6
3
1
4
1
5
9```

### 输出

```
25```

## 样例 #3

### 输入

```
3
5
5
1```

### 输出

```
8```

# 题解

## 作者：RioBlu (赞：3)

先写翻译
```
您将得到N个整数，分别是Ai

将$Ai$重新排列得到$Bi$

问|B2-B1|+|B3-B2|+...+|BN-B{N-1}|的最大值是什么（其中|S|的含义是S的绝对值）

```
经过猜想，我认为应该像这样的方法可以得到最大的答案：

奇数：(...+第三大值+第二小值+最大值)+最小值+(第二大值+第三小值+...)(以最小值为数列中心)

偶数：(...+第三大值+第二小值+最大值)+(最小值+第二大值+第三小值+...)(以最小值和最大值为数列中心)

但结果我们发现还会**错**一些

这究竟是为什么呢？我想了许久

___

突然灵光一动，要是有一个数据是这样：$N=3,Ai=1,999,2$

我们用上面这个方法得到的是：$Bi=999,1,2$

但很明显用这个方法的答案是$|1-999|+|2-1|=999$

但极易想到另外一个摆法：$Bi=2,999,1$

这个方法的答案是$|999-2|+|1-999|=1995$

显然$1995>999$

此时只要把奇数的方法改成：(...+第三大值+第二小值+最大值)+最小值+(第二大值+第三小值+...)(以最小值为数列中心)**与**(...+第三大值+第二小值)+最大值+(最小值+第二大值+第三小值+...)(以最大值为数列中心)**的最大值**

贴上一下代码：
```
#include<bits/stdc++.h>
using namespace std;
long long a,b[100005],c[100005],ans,mins,maxs,YN,anss;
int main()
{
	cin>>a;
	for(int s=0;s<a;s++)
	{
		cin>>b[s];
	}
	sort(b,b+a);
	maxs=a-1;
	if(a%2==1)
	{
		c[a/2]=b[0];mins=1,YN=1;
		for(int s=a/2-1,k=a/2+1;s>=0;s--,k++)
		{
			if(YN==1)c[s]=b[maxs--],c[k]=b[maxs--];
			else c[s]=b[mins++],c[k]=b[mins++];
			YN=!YN;
		}
		for(int s=1;s<a;s++)
		{
			ans=ans+abs(c[s]-c[s-1]);
		}
		c[a/2]=b[a-1];mins=0,maxs=a-2,YN=0;
		for(int s=a/2-1,k=a/2+1;s>=0;s--,k++)
		{
			if(YN==1)c[s]=b[maxs--],c[k]=b[maxs--];
			else c[s]=b[mins++],c[k]=b[mins++];
			YN=!YN;
		}
		for(int s=1;s<a;s++)
		{
			anss=anss+abs(c[s]-c[s-1]);
		}
		ans=max(anss,ans);
	}
	else
	{
		for(int s=a/2-1,k=a/2;s>=0;s--,k++)
		{
			if(YN==1)c[s]=b[maxs--],c[k]=b[mins++];
			else c[s]=b[mins++],c[k]=b[maxs--];
			YN=!YN;
		}
		for(int s=1;s<a;s++)
		{
			ans=ans+abs(c[s]-c[s-1]);
		}
	}
	cout<<ans<<endl;
}
```

---

## 作者：qfpjm (赞：1)

# 题解

- 分类讨论的好题，思维量偏中。

- 考虑如何使序列相邻数差最大，显然只有两种排法：

设重排后的序列为 $\{p_i\}$

1. $p_1\leq p_2\geq p_3\dots p_{i-1}\leq p_i\geq p_{i+1}$（小大小大）

1. $p1\geq p_2\leq p_3\dots p_{i-1}\geq p_i\leq p_{i+1}$（大小大小）

- 根据序列长度分为奇数和偶数来讨论。

1. 奇数，其中有两种情况（如上）。

1. 偶数，只有一种，小在先和大在先本质上为同一种情况。

- 计算上有些小麻烦，我们列个式子来计算一下。

如 $n = 5$：

序列为 $p_{1\dots 5}$，两种情况：

1. $p_2-p_1+p_2-p_1+p_4-p_3+p_4-p_5=2(p_2+p_4)-p_1-p_5-2p_3$（小大小大）

1. $p_1-p_2+p_3-p_2+p_3-p_4+p_5-p_4=p_1+p_5+2p_3-2(p_2+p_4)$（大小大小）

- 根据上述的计算，我们可以看出一些规律，用序列中较大的一半数见另一半较小的数，在加上或减去一些东西即为答案。

- 加上或减去的东西可以通过模拟算出，即为序列中间的两个，加减的符号自己算算。

- 最后记得开 `long long`。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int n, a[100005];

signed main()
{
	cin >> n;
	for (int i = 1 ; i <= n ; i ++)
	{
		cin >> a[i];
	}
	sort(a + 1, a + 1 + n);
	if (n & 1)
	{
		int summin1, summax1, summin2, summax2;
		summin1 = summax1 = summin2 = summax2 = 0;
		for (int i = 1 ; i <= n / 2 + 1 ; i ++)
		{
			summin1 += a[i];
		}
		for (int i = n / 2 + 2 ; i <= n ; i ++)
		{
			summax1 += a[i];
		}
		for (int i = 1 ; i <= n / 2 ; i ++)
		{
			summin2 += a[i];
		}
		for (int i = n / 2 + 1 ; i <= n ; i ++)
		{
			summax2 += a[i];
		}
		cout << max(2 * summax1 - 2 * summin1 + a[n / 2] + a[n / 2 + 1], 2 * summax2 - 2 * summin2 - a[n / 2 + 1] - a[n / 2 + 2]);
	}
	else
	{
		int summin, summax;
		summin = summax = 0;
		for (int i = 1 ; i <= n / 2 ; i ++)
		{
			summin += a[i];
		}
		for (int i = n / 2 + 1 ; i <= n ; i ++)
		{
			summax += a[i];
		}
		cout << 2 * summax - 2 * summin - a[n / 2 + 1] + a[n / 2];
	}
}
```


---

## 作者：Aix_Eric (赞：0)

### 题意：
任意重排数组使得 $\sum_{i = 1}^{n-1} |a_i - a_{i+1}|$ 最大。

首先将数组从小到大排序。

因为有关绝对值，可以换转化为数轴上的问题。
![](https://www.helloimg.com/i/2025/01/15/6787932e7a754.png)
最长的 $AF$ 一定要选。

- 以 $A$ 为断点， $AE$ 是第二长的。

- 以 $F$ 为断点， $BF$ 是第二长的。

- 取 $AE$ ， $BF$ 中最长的一条。

选完后两端点向前走，变为以 $B$ 为断点和 以 $E$ 为端点。

如果最后连完， 即 $n$ 为偶数， 直接输出。


如果 $n$ 为奇数， 最后剩下三个点， 则选剩下三点中最优的。

复杂度$O(n \log{n})$
### code：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;
const int N = 1e5+5;
int c[N];
ll ans, l, r;
int main(){
    int n; scanf("%d", &n);
    for(int i = 1;i <= n;i++)
        scanf("%d", &c[i]);
    sort(c+1, c+n+1);
    l = 1, r = n;
    ans = c[r] - c[l]; //选最长线段
    while(l < r){
        int l1 = l + 1, r1 = r - 1;
        //次大和次小端点
        if(l1 == r1){ //最后有三个点
            ans += max(c[r] - c[l1], c[r1] - c[l]);
            break;
        } else if(l1 < r1)
            ans += c[r] - c[l1] + c[r1] - c[l];
        else break;
        l = l1, r = r1;
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：liuhaopeng (赞：0)

### Description

任意重排数组 $a$ 使得 $s=\displaystyle\sum_{i=1}^{n-1}|a_i-a_{i+1}|=|a_1-a_2|+|a_2-a_3|+\dots+|a_{n-1}-a_n|$ 最大。

### Solution

先将数组从小到大排序。显然，我们有一种类似贪心的做法：

即将数组变为 $a_1\ \ a_n\ \ a_2\ \ a_{n-1}\ \ a_3\ \ a_{n-2}\dots$，保证 $|a_i-a_{i+1}|\ (i\in[1,n-1])$ 取到最大值。

然而你会发现这样一组数据把你 $\text{hack}$ 掉了：

输入：
> 5 1
> 1 2 6 7 13

正确的输出：（ $a$ 数组重排为 $6\ 1\ 13\ 2\ 7$ 或 $6\ 2\ 13\ 1\ 7$ 或 $7\ 1\ 13\ 2\ 6$ 或 $7\ 2\ 13\ 1\ 6$ ）

> 33

而你的输出：（ $a$ 数组重排为 $1\ 13\ 2\ 7\ 6$ ）

> 29

正确的重排方案有些是重复的（ 即 $1$ 个方案倒序得到了另 $1$ 个方案 ），删去后得：

$a=\{6,1,13,2,7\}$ 或 $a=\{7,1,13,2,6\}$

很显然，这 $2$ 种方案只是首尾元素互换了位置，其余地方没有不同。

那如果我把 $|a_n-a_1|$ 也纳入 $s$ 的计算呢？也就是令 $t=\displaystyle\sum_{i=1}^{n}|a_i-a_{(i\ \text{mod}\ n)+1}|$，那么显然 $s=t-|a_n-a_1|$。

这么看来，你的错误构造的 $t$ 算出来是 $34$，而你也会发现，正确构造算出来的 $t$ 也是 $34$。

再观察这几种构造方案，其实正确方案也就是换做从 $a_1=6$ 或 $a_1=7$ 开始的贪心做法罢了。

那么我们可以 $O(n)$ 地枚举起点，再 $O(n)$ 地扫描，总时间复杂度 $O(n^2)$。还不能通过全部数据。

还能更快吗 ？我们分类讨论：

- $n$ 为奇数时：以 $\text{hack}$ 数据为例子，重排后变为了 $\{a_3,a_1,a_5,a_2,a_4\}$，拆开 $t$ 得

$t=a_3-a_1+a_5-a_1+a_5-a_2+a_4-a_2+a_4-a_3=2(a_5+a_4)-2(a_1+a_2)$

代入 $s=t-|a_4-a_3|$

另一个例子：$a={1,2,3,5,7}$，正确构造方案为 $\{a_2,a_5,a_1,a_4,a_3\}$

同样 $t=a_5-a_2+a_5-a_1+a_4-a_1+a_4-a_3+a_3-a_2=2(a_5+a_4)-2(a_1+a_2)$

代入 $s=t-|a_2-a_3|$

记 $\displaystyle m=\frac{1+n}{2}$，那么 $a_m$ 就是 $a$ 的中位数。

显然 $t=2\displaystyle\sum_{i=m+1}^{n}a_i-2\sum_{i=1}^{m-1}a_i=2(a_{m+1}+a_{m+2}\dots+a_n)-2(a_1+a_2+\dots+a_{m-1})$ 

而 $s=\min(t-|a_{m-1}-a_m|,t-|a_{m+1}-a_m|)$

- $n$ 为偶数的情况类似，不做详细解释。

综上所述，总时间复杂度为 $O(n\log n)$，瓶颈在排序。

### Code

```cpp
const int N = 1e5 + 5;
int n, a[N], minn = INF, maxn = -INF;
cin >> n;
for (int i = 1; i <= n; i++)
    cin >> a[i];
sort(a + 1, a + n + 1);
if (n & 1) // n 为奇数
{
    int mid = (1 + n) / 2, ans = 0;
    for (int i = n; i > mid; i--)
        ans += a[i] * 2;
    for (int i = 1; i < mid; i++)
        ans -= a[i] * 2;
    ans -= min(abs(a[mid] - a[mid - 1]), abs(a[mid + 1] - a[mid]));
    cout << ans << endl;
}
else
{
    int mid = n / 2, ans = 0;
    for (int i = n; i > mid; i--)
        ans += a[i] * 2;
    for (int i = 1; i <= mid; i++)
        ans -= a[i] * 2;
    ans -= abs(a[mid + 1] - a[mid]);
    cout << ans << endl;
}
```

这样你就可以获得一份 [最优解](https://www.luogu.com.cn/record/178683737)。

---

## 作者：jiangjiangQwQ (赞：0)

### 题解
对于 $n$ 为偶数的情况相对较简单。容易想到的是最小的和次小的中间夹着最大的，第二小的与第三小的中间夹着次大的以此类推。手玩样例就可以得出这个结论，贪心就行了。因为要使得每个数之间的差较大，假设整个序列已经从小到大排序，其中 $a_n$ 为最大值，要最大化它对答案的贡献，在其两侧插入 $a_1$ 和 $a_2$ 即可，对之后的数也是如此，按顺序插空，最终的答案肯定是最优的。
```cpp
if(n%2==0) {
	int x=1,y=n/2+1;
	for(int i=1; i<=n; i++) {
		if(i&1) b[i]=a[y++];
		else b[i]=a[x++];
	}
	for(int i=2; i<=n; i++) ans+=max(b[i-1],b[i])-min(b[i-1],b[i]);
	cout<<ans;
}
```
对于 $n$ 的奇数的情况，在偶数的情况上进行进一步思考，我们将有序数列中的中位数 $a_x$ 提出，剩下按照偶数的情况排列得到局部最优，全局最优则需要比较 $a_x$ 分别放在头和尾的情况取最大值。
```cpp
b[1]=a[n/2+1];
int x=1,y=(n+1)/2+1;
for(int i=2; i<=n; i++) {
	if(i%2==0) b[i]=a[y++];
	else b[i]=a[x++];
}
int s=2;
if(abs(a[n/2+1]-b[n])>abs(b[2]-a[n/2+1])) b[n+1]=a[n/2+1],s++;
for(int i=s; i<=n-2+s; i++) ans+=max(b[i-1],b[i])-min(b[i-1],b[i]);
cout<<ans;
```


---

## 作者：hmh100211 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_tenka1_2018_c)

# 题意分析：

~~题意很简单，没什么好解释的~~

# 思路：

看到题目里要求~~撅对值~~绝对值，很容易想到把数值放到数轴上用线段长度表示绝对值，那么绝对值最大和就是几段**两两有共端点的线段的长度之和**，然后贪心即可。

那么具体应该怎么贪呢？举个栗子：

![](https://cdn.luogu.com.cn/upload/image_hosting/279s9t6y.png)

首先，最长的线段 $AE$ 是一定要的。

然后分类：

- 以 $A$ 为共端点：除 $AE$ 外，$AD$ 最长。

- 以 $E$ 为共端点：除 $AE$ 外，$BE$ 最长。

再在这两条线段中取较长者 $\max(AD,BE)=BE$。

然后继续分类：

- 以 $B$ 为共端点：除 $BE$ 外，$BD$ 最长。

- 以 $E$ 为共端点：除 $AE,BE$ 外，$CE$ 最长。

再在这两条线段中取较长者 $\max(BD,CE)=BD/CE$。

依此类推$\dots$

可以发现，这很符合递归的性质，写起来也很简单，上代码：

# 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],ans;
void solve(int l,int r){ //递归函数 
	if(l>=r){ //终止条件 
		cout<<ans<<'\n'; //输出 
		return ;
	}
	ans+=a[r]-a[l]; //计算线段长度
	
	//取较长线段并递归 
	if(a[r]-a[l+1]<a[r-1]-a[l]){  
		solve(l,r-1);
	}
	else {
		solve(l+1,r);
	}
}
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>a[i];
	}
	sort(a+1,a+n+1); //排序 
	solve(1,n); //开始递归 
	return 0;
}
```




---

## 作者：Cure_Wing (赞：0)

[AT_tenka1_2018_c Align](https://www.luogu.com.cn/problem/AT_tenka1_2018_c)

### 解法

首先看到绝对值，又是一维的，所以想到把绝对值转化为点与点的距离。

比如第一个样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/9t9hunj4.png)

此时那一串绝对值的加和就变为了依次选择的点的相邻点的距离和。

可以贪心的想，为了使答案最大，$AE$（最长线段）是一定要选的。

然后容易想到让 $A$ 连次右的 $D$，让 $E$ 连次左的 $B$（连次长线段）。

因为如果 $A$ 连 $D$ 再连 $B$，因为 $BD\le BE$，所以答案一定不优。

最后如果恰好连完（即 $n$ 为偶数，第二个样例)，那么不用多加处理，可以直接结束。

但是如果面对第一个样例的情况，只剩 $B,C,D$ 三点，那么只要选 $BC,BD$ 中较优的那个就可以了（本例中为 $BD$）。

这样子就确定了本题的写法，先对数组排序，再按上述方法选点即可。

时间复杂度 $O(n\log_2n)$。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
// #include<ctime>
using std::cin;using std::cout;
constexpr int N=100005;
long long n,a[N],ans,l,r;
signed main(){
 	freopen("a.in","r",stdin);
 	freopen("a.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;++i) cin>>a[i];
    std::sort(a+1,a+n+1);//先对数组排序。
    ans=a[n]-a[1];//最长线段是一定要选的。
    l=1;r=n;
    while(l<r){
        int l1=l+1,r1=r-1;//连次长线段。
        if(l1==r1){ans+=std::max(a[r]-a[l1],a[r1]-a[l]);break;//只剩三点，那么只要选那相邻两条线段中较优的那个就可以了}
        else if(l1<r1) ans+=a[r]-a[l1]+a[r1]-a[l];//最后如果恰好连完，那么不用多加处理，可以直接结束。
        else break;
        l=l1;r=r1;
    }
    cout<<ans;
    // std::cerr<<1.0*clock()/CLOCKS_PER_SEC<<"(s)";
    return 0;
}
```

---

