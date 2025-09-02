# [USACO21DEC] Air Cownditioning B

## 题目描述

Farmer John 的 $N$ 头奶牛对他们牛棚的室温非常挑剔。有些奶牛喜欢温度低一些，而有些奶牛则喜欢温度高一些。

Farmer John 的牛棚包含一排 $N$ 个牛栏，编号为 $1 \ldots N$，每个牛栏里有一头牛。 第 $i$ 头奶牛希望她的牛栏中的温度是 $p_i$，而现在她的牛栏中的温度是 $t_i$。为了确保每头奶牛都感到舒适，Farmer John 安装了一个新的空调系统。该系统进行控制的方式非常有趣，他可以向系统发送命令，告诉它将一组连续的牛栏内的温度升高或降低 1 个单位——例如「将牛栏 $5 \ldots 8$ 的温度升高 1 个单位」。一组连续的牛栏最短可以仅包含一个牛栏。

请帮助 Farmer John 求出他需要向新的空调系统发送的命令的最小数量，使得每头奶牛的牛栏都处于其中的奶牛的理想温度。

## 说明/提示

【样例解释】

一组最优的 Farmer John 可以使用的指令如下：

```
初始温度     ：1 2 2 2 1
升高牛棚 2..5：1 3 3 3 2
升高牛棚 2..5：1 4 4 4 3
升高牛棚 2..5：1 5 5 5 4
降低牛棚 3..4：1 5 4 4 4
降低牛棚 3..4：1 5 3 3 4
```

【数据范围】

- 测试点 2-5 满足 $N \leq 100$。
- 测试点 6-8 满足 $N \leq 1000$。
- 测试点 9-10 满足 $N \leq 100,000$
- 测试点 1-6 和 9 中，温度值不超过 $100$
- 测试点 7-8 和 10 中，温度值不超过 $10,000$。


## 样例 #1

### 输入

```
5
1 5 3 3 4
1 2 2 2 1```

### 输出

```
5```

# 题解

## 作者：刘辰雨 (赞：21)

## P7994
在阅读本题解之前，请先思考  [铺设道路](https://www.luogu.com.cn/problem/P5019)。 
之后，本题会更加明了。

### 分析 ： 

此题与 铺设道路 非常相似，唯一的不同在于分为升温，降温两种方式。可以证得，分开加减一定比统一升降，再单独操作步骤来的少，所以此题分成两个两个数组存放，与标准量相减，取绝对值处理。（不是我笼统，真的和铺设道路一模一样）。

其余看代码吧，还有一些处理思想，也在代码里。

##  Code ： 

1，普通 铺设道路 ：

```cpp
#include<iostream>
using namespace std;
long long n , a[100001] , ans;
int main()
{
	cin>>n;
	for( int i = 1 ; i <= n ; i ++ )		cin>>a[i];
	for( int i = 1 ; i <= n ;  i ++ )		if( a[i] > a[i-1])ans += a[i] - a[i-1];
	cout<<ans;
	return 0;
}
```

2,此题：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
long long a[100001] , b[100001];
long long now[100001] , want[100001];
long long ans = 0;
int main()
{
	cin>>n;
	for(int i = 1 ; i<= n ; i++)	cin>>want[i];
	for(int i = 1 ; i<= n ; i++)
	{
		cin>>now[i];
		long long x = want[i] - now[i];
		if(x >= 0)a[i] = x;
		else b[i] = -x;
	}
	for(int i = 1 ; i<= n ; i++)
	{
		if(a[i] > a[i-1])ans += a[i] - a[i-1]; 
	}
	for(int i = 1 ; i<= n ; i++)
	{
		if(b[i] > b[i-1])ans += b[i] - b[i-1];
	}
	cout<<ans;
	return 0;	
} 
```
ps:可以做一些对比。

---

## 作者：清小秋ovo (赞：12)

# USACO 铜组第二题

原题链接: [usaco原题](http://usaco.org/index.php?page=viewproblem2&cpid=1156)

是一道挺有意思的题目。

题目大意是说有一组牛棚，每个牛棚都有一个初始温度和一个理想温度。调节温度的方式为指定一个区间（可以为 $1$），并对区间内的所有牛棚的温度上调一度或者下调一度。**求使所有牛棚达到理想温度所需的最少指令次数。**

## 思路

其实也不难想，首先统计出每个牛棚的初始温度和理想温度的差值，随后根据相邻两个牛棚之间的差值关系计算调整次数。

具体来讲：如果 $d_{i} > d_{i-1}$ 则将差(注意是绝对值)加到  ``ans1``  当中，如果 $d_{i} < d_{i-1} $, 则将差加到 ``ans2``  中，最后答案为 ``max(ans1, ans2)``。

注: 这里的 $d_i$ 表示 第 $i$ 个牛棚的初始温度与理想温度的差。

## 代码

实现起来也很简单
```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef set<int> si;
#define PB push_back

int d[100005];

int n, t;
ll ans1, ans2;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> d[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> t;
        d[i] -= t;
    }
    for (int i = 1; i <= n; i++)
    {
        if (d[i] > d[i - 1])
            ans1 += abs(d[i] - d[i - 1]);
        else
            ans2 += abs(d[i] - d[i - 1]);
    }

    cout << max(ans1, ans2) << endl;
    return 0;
}

```







---

## 作者：Eason_AC (赞：6)

[Advertisement](https://www.cnblogs.com/Eason-AC/p/15718313.html)

## Content
有两个长度为 $n$ 的数组 $a,b$。每次操作你可以选择一个区间 $[l,r]$，然后将下标在这个区间里面的所有 $b_i$ 加 $1$ 或者减 $1$，求最少需要多少操作才能够使得 $\forall i\in[1,n],a_i=b_i$。

**数据范围：$1\leqslant n\leqslant 10^5$。**
## Solution
首先我们令 $c_i=a_i-b_i$，然后就把这道题目转换成了最少需要多少次操作使得 $\forall i\in[1,n],c_i=0$。然后我们就发现有一道经典的差分题目和这题非常相像，就是洛谷 [P4552](https://www.luogu.com.cn/problem/P4552)。没做那道题目的同学可以先去做做那道题目，然后你就发现这道题目可以随便乱杀了。

我们可以套路地将 $c_i$ 进行一个差分操作，即令 $d_i=c_i-c_{i-1}$，然后就又转化为最少需要多少操作才能够使得 $\forall i\in[1,n],d_i=0$。然后，我们可以统计一下所有 $d_i$ 中正数的和 $sum_1$ 和负数的和的绝对值 $sum_2$，为什么呢？首先我们想想对 $[l,r]$ 进行一次操作之后会对差分数组 $d$ 有什么影响。分析之后不难发现：

- 如果操作为全加 $1$，那么 $d_{l-1}\leftarrow d_{l-1}+1$，$d_r\leftarrow d_r-1$。
- 如果操作为全减 $1$，那么 $d_{l-1}\leftarrow d_{l-1}-1$，$d_r\leftarrow d_r+1$。

然后再分析怎么让所有 $d_i=0$，不难发现，我们首先选择 $d_2,d_3,\dots,d_{n-1}$ 当中的一个正数和一个负数进行若干次操作，等不能执行这种操作之后，再拿一个正数和 $d_n$ 进行操作，或者再拿一个负数和 $d_1$ 进行操作（因为由定义可知，$d_1>0$，$d_n<0$）。然后你就可以发现这样的操作次数为 $\min(sum_1,sum_2)+|sum_1-sum_2|=\max(sum_1,sum_2)$。

于是这道题目就做完了，还弄了个双倍经验，简直美汁汁。
## Code
赛时代码。
```cpp
namespace Solution {
	const int N = 1e5 + 7;
	int n, cur, p[N], cf[N];
	
	iv Main() {
		read(n); F(int, i, 1, n) read(p[i]);
		F(int, i, 1, n) read(cur), p[i] = p[i] - cur;
		F(int, i, 1, n) cf[i] = p[i] - p[i - 1];
		ll sum1 = 0, sum2 = 0;
		F(int, i, 1, n) if(cf[i] > 0) sum1 += cf[i]; else sum2 += -cf[i];
		write(max(sum1, sum2));
		return;
	}
}
```

---

## 作者：Ginger_he (赞：3)

# 题目描述
给定两个有 $n$ 个数的序列 $\left\{p_i\right\}$ 和 $\left\{t_i\right\}$。每次对 $\left\{t_i\right\}$ 进行如下操作：选择一个区间，将区间内的数全部加 $1$ 或减 $1$。求使得所有 $t_i$ 与 $p_i$ 相等的最小操作次数。
# 题解
分别定义 $\left\{a_i\right\}$ 和 $\left\{b_i\right\}$ 为 $\left\{p_i\right\}$ 和 $\left\{t_i\right\}$ 的差分数组，则最后所有 $t_i$ 与 $p_i$ 相等，等价于所有 $b_i$ 和 $a_i$ 相等。  
不难发现，若选择区间 $[l,r]$ 中的数加 $1$，则等价于 $b_l$ 加 $1$，$b_{r+1}$ 减 $1$；若选择区间 $[l,r]$ 中的数减 $1$，则等价于 $b_l$ 减 $1$，$b_{r+1}$ 加 $1$。  
因为要求最小操作次数，所以每次将一个 $b_i>a_i$ 的数减 $1$，$b_i<a_i$ 的数加 $1$。  
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,p[maxn],t[maxn],a[maxn],b[maxn],x,y;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&p[i]);
        a[i]=p[i]-p[i-1];
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&t[i]);
        b[i]=t[i]-t[i-1];
    }
    for(int i=1;i<=n;i++)
    {
        if(b[i]>a[i]) x+=b[i]-a[i];
        else if(b[i]<a[i]) y+=a[i]-b[i];
    }
    printf("%d\n",max(x,y));
    return 0;
}
```

---

## 作者：xkcdjerry (赞：2)

第一眼看到就认出来是 [P1969 积木大赛](https://www.luogu.com.cn/problem/P1969) 的变形了，显然只有初温和末温的差才有意义所以做差 $f_i=p_i-t_i$，然后就是 P1969 的板子了：（由于有 $+1$ 和 $-1$ 所以正负不用考虑直接背原来的结论即可）

对于任意 $i$：

* 假如 $f_i<f_{i+1}$，即左边的比右边的温度低，当温度满足左面时，右边的还差一些，那么 $ans$ `+=` 温度差。
* 假如 $f_i \geqslant f_{i+1}$，即左边的温度比右边的高，当温度满足左面时，右边的也一定满足了，所以 $ans$ 不变。

小细节：由于总体去掉某个温度仍然需要扣除，所以要在 $f$ 两边补 0。

祭上蒟蒻的 10 行代码：
```c++
#include <cstdio>
int n,x,a[100010],ans;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=n;i++) scanf("%d",&x), a[i]-=x;
    for(int i=1;i<=n+1;i++) ans+=a[i]>a[i-1]:a[i]-a[i-1]:0;
    printf("%d",ans);
}
```

---

## 作者：CANTORSORT (赞：2)

在完成这一题之前，

你可以先完成 [这道题](https://www.luogu.com.cn/problem/P1969)。

这题本质上，其实是使用一个 **区间修改操作**，以 **最少的修改次数** 将序列 $t$ 修改成序列 $p$。

我们可以定义一个 **一维数组** $differ$，其初始化值为
$$
differ_i=p_i-t_i\space(1\le i\le n)
$$
显然，

$differ_i$ 的值有正有负，而我们的目标就是使每一个 $differ_i=0$。所以，要避免 **负数的减少** 和 **正数的增加**。

我们将数组 $differ$ 分成若干段，使每一段中的 $differ_i$ **非负** 或 **非正**。

令 **非负子串** 减少以及令 **非正子串** 增加，

这就是我们要完成的 **操作**。

时间复杂度为 $O(n)$。

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,p[100005],t[100005],differ[100005],ans;
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",p+i);
	for(int i=1;i<=n;i++)
		scanf("%lld",t+i),differ[i]=p[i]-t[i];
	for(int i=0;i<=n;i++)
		ans+=abs(differ[i]-differ[i+1]);
	printf("%lld",ans>>1);
	return 0;
}
```
[提交记录](https://www.luogu.com.cn/record/65721836)

---

## 作者：rzh123 (赞：1)

# P7994 题解  

题目链接：[P7994 \[USACO21DEC\] Air Cownditioning B](https://www.luogu.com.cn/problem/P7994)  

这题看着难，其实比 [T1](https://www.luogu.com.cn/problem/P7993) 简单多了。  

首先，为了方便，可以先预处理出每一个 $p_i$ 与 $t_i$ 之间的差（有正有负），这题的目标就是把这些差值都变成 $0$。  

题解中以处理**正数**的方法为例，处理负数的方法类似。  

**打暴力！** 用贪心的思路，如果有一段连续的正数，一次就可以让它们都减 $1$，统计减了多少次，每次循环一遍，直到差值中没有正数。  

这个只能得 $90$ 分，需要优化。  

仔细想想暴力的过程，可以发现有很多不必要的操作。  

比如：  
```plain
6
100 101 101 100 100 100
0 0 0 0 0 0
```  

一眼就知道需要 $101$ 次操作，但是暴力程序会整个扫 $101$ 遍，从 $1$ 一个一个加到 $101$，可见它有多慢。   

为了防止这种情况，在遇到一段连续正数 $\left\{x_i,x_{i+1},\cdots ,x_{j-1},x_j\right\}$ 时，给这一段整体减 $\min_{k=i}^{j} x_k$，即其中的最小值，这样上面的数据只需要扫 $2$ 遍。  

然后，就 AC 了这道题。  

AC 代码：  

```cpp
#include <cstdio>
#include <cstring>
#define N 100007
#define gc getchar()
typedef long long unsigned llu;
int n,p[N],t[N],x[N],y[N];
llu s;
llu c;
int f,ff;
int imn(int _,int __){
	return _<__?_:__;
}
int imx(int _,int __){
	return _>__?_:__;
}
int read(){
	int t=0;
	char c=gc;
	while(c<'0'||c>'9') c=gc;
	while(c>='0'&&c<='9') t=10*t+(c^48),c=gc;
	return t;
}
void asdf(){
	while(1){
		c=0;
		for(int i=0;i<=n;++i){
			if(x[i]<=0&&x[i+1]>0){
				f=i+1;
				ff=x[i+1];
			}
			if(x[i]>0){
				ff=imn(ff,x[i]);
				if(x[i+1]<=0){
					c+=ff;
					for(int j=f;j<=i;++j){
						x[j]-=ff;
					}
				}
			}
		}
		if(c==0){
			break;
		}
		s+=c;
	}
}
int main(){
	n=read();
	for(int i=1;i<=n;++i){
		p[i]=read();
	}
	for(int i=1;i<=n;++i){
		t[i]=read();
		x[i]=p[i]-t[i];
	}
	asdf();
	for(int i=1;i<=n;++i){
		x[i]=-x[i];
	}
	asdf();
	printf("%llu",s);
	return 0;
}
```  

[AC 记录](https://www.luogu.com.cn/record/65702154)

---

