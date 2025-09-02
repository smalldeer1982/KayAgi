# Hats

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=242&page=show_problem&problem=3175

[PDF](https://uva.onlinejudge.org/external/120/p12024.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA12024/25a75cc3aa1181e89f3439302a46c65776fbdd03.png)

## 样例 #1

### 输入

```
3
2
3
4```

### 输出

```
1/2
2/6
9/24```

# 题解

## 作者：__Kyw666__ (赞：2)

## 题意解释
$n$ 个人都有一顶帽子，求每个人的帽子都不在自己头上的概率。  

## 思路分析
很明显，这题要用到[错排](https://baike.baidu.com/item/%E9%94%99%E6%8E%92%E5%85%AC%E5%BC%8F/10978508?fr=ge_ala)。  
下面直接放出错排公式：
$$\begin{aligned} 
D(n) &= n! \times[\frac{(-1)^2}{2!} + \dots + \frac{(-1)^{n-1}}{(n-1)!} + \frac{(-1)^n}{n!}]\\
&=(n-1)(D_{n-1} + D_{n-2})
\end{aligned}
$$
还有一个全排列公式：
$$\begin{aligned} 
F(n) &= n\times (n-1) \times \dots \times 2 \times 1\\
&=n!
\end{aligned}
$$
最后，错排公式得出的结果做分子，全排列公式得出的结果做分母，就可以了。  
结果不用化简，直接输出就行。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll T,n,d[20];
ll f1(ll x)//错位 
{
	if(x==1) return 0;
	if(x==2) return 1;
	d[x]=(x-1)*(d[x-1]+d[x-2]);//公式 
	
	if(x==n) return d[x];
	else return f1(x+1); 
}
ll f2(ll x)//全排列 
{
	ll ans=1;
	while(x)
	{
		ans*=x;
		x--;
	}
	return ans;
}
int main()
{
	cin>>T;
	while(T--)
	{
		d[1]=0,d[2]=1;//一定要初始化 
		cin>>n;
		printf("%lld/%lld\n",f1(n),f2(n));//输出格式 
	}
	return 0;
 } 
```

结束！

---

## 作者：Rainbow_Sky (赞：1)

## 大致题意

每人一顶帽子，求每个人的帽子的不在自己脑袋上的概率。

## 思路

这是一道错排的模板题。我们可以通过分子、分母两方面来分析。

### 分子

由于求不在自己头上的概率，故用错排。错排即为错开的排序，令数字不再原来的地方：$D_n=(n-1)\times(D_{n-1}+D_{n-2})$ 其中 $D_1=0,D_2=1$。

#### 证明

其实证明也不难。我们可以假设共有 $n$ 个元素，先随意选出一个，设之为 $a$，那么不在自己位子上，共有 $n-1$ 种选择方式。之后选择一个 $b$，这时有了两种情况。

1. $b$ 恰好在 $a$ 的位置上，那么就对剩下的 $(n-2)$ 个元素进行错排，方案数为 $D_{n-2}$。

2. $b$ 不在 $a$ 的位置上，那么就还有 $n-1$ 个位置，可供选择，为 $D_{n-1}$。

最后，根据加法原理与乘法原理，可得 $D_n=(n-1)\times(D_{n-1}+D_{n-2})$。

------------

### 分母

分母就是 $n$ 的全排列，即 $A_n^n$，也就是 $n!$。

这样，就完美的 AC 了。

## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000+10;
const int MAXM=100000+10;
const int INF=100000;
int a[MAXM],b[MAXM];
void yuchuli()
{
	for(int i=2;i<=12;++i)
	{
		a[i]=(i-1)*(a[i-2]+a[i-1]);
	}
	for(int i=2;i<=12;++i)
	{
		b[i]=b[i-1]*i;
	}
}
int main()
{
	a[0]=1;
	b[1]=1;
	yuchuli();
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		cout<<a[x]<<"/"<<b[x]<<endl;
	}
}
```

---

## 作者：DashZhanghanxu (赞：0)

# 题意
$n$ 个人都有一顶帽子，求每个人的帽子都不在自己头上的概率。
# 解析
看到都不在三字，明显错排问题。

根据公式：
$$
D(n)=(n - 1)(D(n - 1)+D(n - 2))
$$
可知，$n$ 个人帽子都不在自己头上的概率为：
$$
 \frac{D(n)}{n!}
$$
等量代换后得：
$$
\frac{(n - 1)(D(n - 1)+D(n - 2))}{n!}
$$
所以，仅需求出上述公式答案即可。

```python
#阶乘
def jc(n):
    result = 1
    for i in range(1, n + 1):
        result *= i
    return result

#错排数
def cps(n):
    if n == 1:
        return 0
    if n == 2:
        return 1
    dp = [0] * (n + 1)
    dp[1] = 0
    dp[2] = 1
    for i in range(3, n + 1):
        dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2])
    return dp[n]


t = int(input())

for _ in range(t):
    n = int(input())
    d = cps(n)
    f = jc(n)
    print(f"{d}/{f}")
```

---

## 作者：dear_deer_land (赞：0)

## 题意

每个人一顶帽子，求每个人的帽子的不在自己脑袋上的概率。

## 思路 && 解法

错排问题，经典的小学奥数。

设 $D(x)$ 表示有 $x$ 个元素的错排问题。

我们先把第 $n$ 个元素放在随机一给位置，设其为 $k$，则共有 $n-1$ 种方法。

此时，我们再去放第 $k$ 个元素，此时：

- 把它放到位置 $n$，那么，对于剩下的 $n-1$ 个元素，由于第 $k$ 个元素放到了位置 $n$，剩下 $n-2$ 个元素就有 $D(n-2)$ 种做法。
- 第 $k$ 个元素不把它放到位置 $n$，这时，对于这 $n-1$ 个元素，有 $D(n-1)$ 种做法。
  
所以可以得到 $D(x)=(x-1)(D(x-1)+D(x-2))$

分母不用说了吧，就是 $n$ 的全排列。

根据此公式递归即可。

---

## 作者：huanglihuan (赞：0)

### 思路

经典的错排问题，关于本题分子可以参考信封问题，这里就不在多讲，给出公式 $M_n=(n−1)×(M_{n−1}+M_{n−2})$，而一共的排列数就是分母即 $(n+1)!$，搞定。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T,n,M [13],Q [13];
void jc ()
{
    M [2] = Q [0] = 1;
    for (int i = 1;i < 13;i ++)
    {
        if (i >= 3) M [i] = (i - 1) * (M [i - 1] + M [i - 2]);
        Q [i] = Q [i - 1] * i;
    }
}
signed main ()
{
    jc ();
    cin >> T;
    while (T --)
    {
        cin >> n;
        cout << M [n] << '/' << Q [n] << '\n';
    }
    return 0;
}
```

---

## 作者：SSqwq_ (赞：0)

## 题意

求 $n$ 个人都不选择对应帽子的概率。

## 分析

一个 trival 的观察：分母即为长度为 $n$ 的总排列数，即 $n$ 的阶乘。

考虑分子，本题题意等价于求 $n$ 个数都不在自己对应位置的排列数量，即**错排问题**。

先说结论：令 $D_n$ 表示长度为 $n$ 的错排个数，则有：

$$D_n=(n-1)(D_{n-2}+D_{n-1})$$

证明：

在长度为 $n$ 的排列 $p$ 中任选两数 $a_i,a_j$，分类讨论：

- 若 $a_i=j$，则等价于对剩下 $n-2$ 个元素进行错排，即 $D_{n-2}$。

- 否则，原式等价于对包括 $a_i$ 在内的 $n-1$ 个元素进行错排，即 $D_{n-1}$。

显然选中 $a_i,a_j$ 一共有 $n-1$ 个方案，根据排列组合基本原理，原式得证。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,D[13],R[13];
void work(){
    cin>>n;
    cout<<D[n]<<"/"<<R[n]<<"\n";
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>T;
    D[2]=1;
    R[0]=1;
    for(int i=1;i<=13;++i){
        if(i>=3)D[i]=(i-1)*(D[i-1]+D[i-2]);
        R[i]=R[i-1]*i;
    }
    while(T--){
        work();
    }
    return 0;
}
```

---

## 作者：Mx_sky (赞：0)

[题目传送门。](https://www.luogu.com.cn/problem/UVA12024)

## 题意翻译

有 $n$ 个人，每个人都有一顶属于自己的帽子，求所有人都戴错帽子的几率。

## 解题过程
### 分子：

很明显的错排问题，直接套公式即可（不懂错排问题的看[百度百科](https://baike.baidu.com/item/%E9%94%99%E6%8E%92%E9%97%AE%E9%A2%98/3849290?fr=aladdin)）：

 $$D(n)=(n-1)\times(D(n-2)+D(n-1))$$
 
其中 $D(1)=0$，$D(2)=1$。

### 分母：

显然，分母就是总的方案数，总的方案数怎么求呢？其实就可以看成是全排列问题，很明显的，有 $n!$ 种排列。

证明（此题可以看成全排列问题）：

$n$ 个元素被分成 $k$ 类，每类的个数分别是 $n_1,n_2,...n_k$ 这 $n$ 个元素的全排列数为 $n!\div (n_1!\times n_2!\times ...\times n_k!)$。$k$ 类元素，每类的个数无限，从中取出 $m$ 个元素的组合数为 $C(m+k-1,m)$，但是此时仅仅是被分成了 $1$ 类，所以全排列数是 $n!\div1!=n!$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+5;
#define ll long long
int n,d[15],T;
int f(int x)    //错排问题公式
{
	if(x==n)return (x-1)*(d[x-1]+d[x-2]);
	else{
		d[x]=(x-1)*(d[x-1]+d[x-2]);
		return f(x+1); 
	} 
}
int jc(int x)    //求方案数，大佬可以改成递归式
{
	int res=1;
	for(int i=1;i<=x;i++) res*=i;
	return res;
}
int main(){
	cin>>T;
	while(T--)
	{
		d[1]=0,d[2]=1;    //初始化
        cin>>n;
        if(n<=2) cout<<d[n]<<"/"<<jc(n)<<endl;
        else cout<<f(3)<<"/"<<jc(n)<<endl;
	}
    return 0;
}
```

```

---

## 作者：Fleeing_loser (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA12024)

一道错排的题，直接套错排公式就可以了（当然还有阶乘，总体这题就是考察递归）。

错排公式：$D(n)=(n-1)[D(n-2)+D(n-1)]$，注意递归的边界 $D(1)=0$ 和 $D(2) =1$ 就行了。

阶乘的递推式就不写了~~这东西有手就行~~。

下面看一下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int x1[20];
int x2[20];
void js()
{
	for(int i=2;i<=12;++i)
	{
		x1[i]=(i-1)*(x1[i-2]+x1[i-1]);
	}
	for(int i=2;i<=12;++i)
	{
		x2[i]=x2[i-1]*i;//阶乘的递推式
	}
}
int main()
{
    x1[0]=1;//注意递推边界,因为n大于等于2，所以直接从2开始推
    x2[1]=1;
    js();
    int a,n;
    cin>>n;
    for(int i=1;i<=n;++i)
    {
    	cin>>a;
    	cout<<x1[a]<<"/"<<x2[a]<<endl;
    }
    return 0;
}
```

---

## 作者：charleshe (赞：0)

错排板子题。

容易发现，输入 $n$ 以后，输出的分数对应的分子是 $n$ 的错排数，分母是 $n$ 的阶乘。[不知道啥是错排数的出门右拐度娘请。](https://baike.baidu.com/item/%E9%94%99%E6%8E%92%E5%85%AC%E5%BC%8F/10978508)

注意输出，可以发现得到的分数不用约分，而求错排数和阶乘则可以用递推实现。

知道了这些，代码就好写了。

```cpp
#include <iostream>
using namespace std;
int d[13]={1,0,0,0,0,0,0,0,0,0,0,0,0};
int h[13]={0,1,0,0,0,0,0,0,0,0,0,0,0};
void init(){
	for(int i=2;i<=12;i++) d[i]=(i-1)*(d[i-1]+d[i-2]);//利用错排公式求错排数。
	for(int i=2;i<=12;i++) h[i]=h[i-1]*i;//利用阶乘的性质写递推。
}
int main(){
	init();
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		cout<<d[n]<<"/"<<h[n]<<endl;//直接输出，无需约分。
	}
	return 0; 
}
```


---

