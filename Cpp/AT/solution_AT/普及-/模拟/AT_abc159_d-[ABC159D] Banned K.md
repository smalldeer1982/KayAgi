# [ABC159D] Banned K

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc159/tasks/abc159_d

ボールが $ N $ 個あり、 $ i $ 番目のボールには整数 $ A_i $ が書かれています。  
 $ k=1,2,...,N $ に対して以下の問題を解いて、答えをそれぞれ出力してください。

- $ k $ 番目のボールを除いた $ N-1 $ 個のボールから、書かれている整数が等しいような異なる $ 2 $ つのボールを選び出す方法の数を求めてください。選ぶ順序は考慮しません。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ N $
- 入力はすべて整数である。

### Sample Explanation 1

例えば $ k=1 $ のとき、残りのボールに書かれている数はそれぞれ $ {1,2,1,2} $ です。 この中から書かれている数が等しいような異なる $ 2 $ つのボールを選び出す方法は $ 2 $ 通りあります。 したがって、 $ k=1 $ に対する問題の答えは $ 2 $ です。

### Sample Explanation 2

どの $ 2 $ つのボールを選び出しても、書かれている数は等しくありません。

### Sample Explanation 3

どの $ 2 $ つのボールを選び出しても、書かれている数が等しいです。

## 样例 #1

### 输入

```
5
1 1 2 1 2```

### 输出

```
2
2
3
2
3```

## 样例 #2

### 输入

```
4
1 2 3 4```

### 输出

```
0
0
0
0```

## 样例 #3

### 输入

```
5
3 3 3 3 3```

### 输出

```
6
6
6
6
6```

## 样例 #4

### 输入

```
8
1 2 1 4 2 1 4 1```

### 输出

```
5
7
5
7
7
5
7
5```

# 题解

## 作者：想不好名字 (赞：2)

hello，大家好。本蒟蒻又来发题解了，谢谢大家看我的题解


———————————————————————————— 手动分隔符

   分析题意，如果有i个相同数的话，就会有（i-1）×i / 2组相同的数；如果(i-1)个相同的数，那么就会有（i-1）×（i-2）/2组相同的数，二者相减，发现少了一个数，能找到相同数的队数就会少(i-1)个
 
------------

```c
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long int n,t;
long long int ans=0; //注意long long
long long int a[1000010],b[1000010];
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;++i) 
	{
		scanf("%lld",&a[i]); 
		b[a[i]]++;//装桶
	}
	for(int i=1;i<=n;++i)
	{
		ans+=(b[i]-1)*b[i]/2; // 计算本应出现的对数
	}
	for(int i=1;i<=n;++i)
	{
		printf("%lld",ans-b[a[i]]+1);	//减去a[i]后的对数
		cout<<endl;
	}
   return 0；//完结撒花
}
```
## 管理员哥哥求过审


---

## 作者：_JF_ (赞：2)

## AT4816 [ABC159D] Banned K

题目大意：

给一个长度为 $n$ 的序列，问每次删去 $a[i]$ 后，有多少对两两相等的数。

思路：

用一个 $sum$ 表示一共有几对相同的数字，即先用一个桶保存每一个数的出现次数，然后用**全排列公式**算出总地情况即可。最后在减一下就可以了。

所以该部分的代码为：


```cpp
	for(int i=0;i<=n;i++)
	{
		if(t[i]>0)
		{
			sum+=(t[i]-1)*t[i]/2;
			b[i]=t[i]-1;
		}
	}
```
值得注意，$i$ 应该 $0$ 开始，为什么自己想一想。

这就是代码主体部分啦，剩下的请自行补齐。（就输入输出的部分....）。


---

## 作者：w33z8kqrqk8zzzx33 (赞：2)

首先，可以统计一下每一个颜色在多少个球里面出现，设为 $C_i$.

如果是从所有球选择，那答案就是每一个颜色有多少对球之和，或者

$$R=\sum_{i=1}^N\binom{C_i}{2}$$

对与一个球，答案就是 $R$ 减去有多少对球使得它是对里的一个球。明显一个球在 $C_{A_i}-1$ 个对里面包括，所以对第 i 球的答案就是 $R-(C_{A_i}-1)$。

主要代码：

```cpp
int cnt[200005];
int aray[200005];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    ll ans = 0;
	int n; gi(n);
	rep(i, n) {
		gi(aray[i]);
		cnt[aray[i]]++;
	}
	rep1(i, n) ans += 1ll*cnt[i]*(cnt[i]-1)/2;
	rep(i, n) {
		print(ans - (cnt[aray[i]]-1)); pc('\n');
	}
}

```

---

## 作者：wyb0412 (赞：1)

先给个传送门吧：[Banned K](https://atcoder.jp/contests/abc159/tasks/abc159_d)

好了，接下来切入正题。
先看看数据，N<=2*10^5，只能**一重循环**
那怎么循环呢？让我们分析分析。

这道题本蒟蒻认为是一道**思维题**，现在我要开始表演了。

抛开输入输出不说，本题肯定得先记录每个数出现的次数，本蒟蒻当时为了偷懒与谨慎，直接在输入时做完了，见下：
```cpp
for(i=1;i<=n;i++){
	cin>>a[i];
	c[a[i]]++;
}
```
各位不要担心，i已经在主函数外定义过了。

接下来是最精华部分，也就是**思维部分**

```cpp
for(i=1;i<=n;i++)
ans+=(ll)(c[i]-1)*c[i]/2;
     
for(i=1;i<=n;i++)
cout<<ans-(ll)(c[a[i]]-1)<<endl;
```
接下来解释一下。

第一个循环，相信大家都能看出来，就是一个**排列组合**，从(n-1)个数里选2个，也就是C(n-1,2)；

第二个循环，也没什么好讲的，扣除第k个数，那么还剩下(c[a[i]]-1)个数，再用ans减一下就好啦！

以下是本蒟蒻在AT上的AC代码：
（本蒟蒻提交了4次后才AC）
```cpp
#include<bits/stdc++.h>  //万能头文件
using namespace std;
typedef long long ll;  //宏定义，为了偷懒
const int M=200005;  //宏定义，为了偷懒，too
ll n,i,ans;
int a[M],c[M];

int main(){
	cin>>n;  //输入
	
    for(i=1;i<=n;i++){
        cin>>a[i];
        c[a[i]]++;  //输入并记录出现个数
    }
    
    for(i=1;i<=n;i++)
    ans+=(ll)(c[i]-1)*c[i]/2;  
    //注意此处要用(ll)，否则会超出int范围
    for(i=1;i<=n;i++)
    cout<<ans-(ll)(c[a[i]]-1)<<endl;
    //同上，输出
    return 0;
}
```
本文到此结束，欢迎各位大犇交流指正！！


---

## 作者：Micnation_AFO (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT4816)


**题目大意：**
>给定一个数列，让你求删去每一个 $A_k$（$1 \leq k \leq n$）后，整个数列分别有多少对两两相同的个数。

众所周知，排列数的公式为：

$$C_m^n = \dfrac{n!}{m!(n - m)!}$$

那么，在本题中，很显然有 $m = 2$，则要求的答案就是 $\dfrac{n!}{2(n - 2)!}$，也就是 $\dfrac{n \times (n-1)}{2}$。

可以先计算出整个数列一共有多少对数列，再计算出删去每个数字会减少多少对，最后拿前者减去后者即可。

**AC Code：**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define maxn 200005
int n, sum;
int a[maxn], t[maxn], u[maxn];

int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') { f = (f == '-' ? -1 : f); ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return x * f;
}

signed main() {
    n = read();
    for (int i = 1; i <= n; ++i) a[i] = read(), t[a[i]]++;
    for (int i = 1; i <= n; i++) {
        int x = t[i] * (t[i] - 1) / 2, y = (t[i] - 1) * (t[i] - 2) / 2;
        sum += x, u[i] = x - y;
    }
    for (int i = 1; i <= n; i++) cout << sum - u[a[i]] << endl;
    return 0;
}
```







---

## 作者：159号程序员 (赞：0)

~~第159场怎么能没有159呢？~~

排列组合+桶的思想

排列$\tiny(Arrangement/Permutation)$组合$\tiny(Combination)$的算法：

$$A_n^m = \dfrac{n!}{(n-m)!}$$

$$C_n^m = \dfrac{A_n^m}{A_m^m} = \dfrac{n!}{m!(n-m)!}$$

如何证明呢？

推导：把 $n$ 个不同的数任选 $m$ 个排序，按**乘法原理**分步执行：

取第一个：$n$ 种取法

取第二个：$(n-1)$ 种取法；

取第三个：$(n-2)$ 种取法；

$\cdots\cdots$

取第 $m$ 个：$(n-m+1)$ 种取法。

总数：$n!$

剩下的 $m$~$n$：$(n-m)!$

使用除法去掉剩下的部分即可，得出上式。

证明组合的公式，首先拆解求排列的过程：
1. 先从 $n$ 个球中取出 $m$ 个来，不排序，为组合数问题 $C_n^m$。

2. 将取出来的 $m$ 个球排序，为排列数问题 $A_n^m$。

根据乘法原理，$A_n^m = C_n^mA_m^m$，换元后得到上式。

---

回到题目中，首先，观察数据范围：$n \le 2 \times 10 ^ 5$，使用 $O(n)$ 复杂度解题。

1. 求组出两个相等的数的组数，即 $C_{n-1}^2$。可用桶的思想优化复杂度。

2. 由于题目要求计算结果时不包含 $a_k$，少了一个元素，所以还剩下 `book[a[k]-1]` 个数，再用 $sum$ 减掉必须选 $a_k$ 的方案数即可。

_AC Code_

```cpp
#include<bits/stdc++.h>
using namespace std;

long long a[1000005], book[1000005], sum, n; //输入、桶数组、方案数、数组长度
int main()
{
    cin >> n;
	for(int i = 0; i < n; i++) //读入并加入桶
	{
	    cin >> a[i];
	    book[a[i]]++;
	}
	for(int i = 1; i <= n; i++) if(book[i]) sum += book[i] * (book[i] - 1) / 2; // 此处循环枚举的是数，不是下标，所以必须从 1 开始，到 n 结束
	for(int i = 0; i < n; i++) cout << sum - (book[a[i]] - 1) << endl;  //统计并输出答案
	return 0;
}
```

提示：注意数组大小，本题需要开 long long。

---

## 作者：xiezihan (赞：0)

没有**C语言**的，来一篇



------------

此题思维题，代码不难，看思维

大概就是：用桶装起来所有的个数，然后再减掉就OK了



------------


上代码

```c
#include<stdio.h>
long long a[200005],t[200005],b[200005];
int main()
{
	long long n,sum=0;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		t[a[i]]++;
	} 
	for(int i=0;i<=n;i++)
	{
		if(t[i]>0)
		{
			sum+=(t[i]-1)*t[i]/2;
			b[i]=t[i]-1;
		}
	}
	for(int i=1;i<=n;i++)printf("%lld\n",sum-b[a[i]]);
	return 0;
}

```

[AC记录](https://www.luogu.com.cn/record/42100218)


---

## 作者：chenxia25 (赞：0)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/AT4816) & [AtCoder题目页面传送门](https://atcoder.jp/contests/abc159/tasks/abc159_d)

>给定$n$个整数，第$i$个数为$a_i$。求$\forall i\in[1,n]$，不能选$a_i$的情况下，有多少种不同的选$2$个相等的数的方案。

>$n\in\left[3,2\times10^5\right],a_i\in[1,n]$。

由于$a_i\in[1,n]$，所以我们可以直接把数们放进桶里，$buc_i=\sum\limits_{j=1}^n[a_j=i]$。这样，$\forall i\in[1,n]$，$i$的答案显然是$\sum\limits_{j=1}^n\dfrac{(buc_j-[a_i=j])(buc_j-[a_i=j]-1)}2$。但这样时间复杂度显然是$\mathrm O\!\left(n^2\right)$。于是考虑先算出不带“不能选某数”的限制时的答案$ans=\sum\limits_{i=1}^n\dfrac{buc_i(buc_i-1)}2$，$\mathrm O(n)$，然后$\forall i\in[1,n]$，从$ans$里减去必须选$a_i$时的方案数，答案为$ans-(buc_{a_i}-1)$。时间复杂度$\mathrm O(n)$。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=200000;
int n;
int a[N+1];
int buc[N+1];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],buc[a[i]]++/*装进桶*/;
	int ans=0;
	for(int i=1;i<=n;i++)ans+=buc[i]*(buc[i]-1)/2;//不带限制时的答案 
	for(int i=1;i<=n;i++)cout<<ans-(buc[a[i]]-1)<<"\n";
	return 0;
}
```

---

## 作者：ctq1999 (赞：0)

给定一个长为 $N$ 的数组 $[a_1, a_2, \dots ,a_n]$ 。求出分别去掉 $a_k$ 后，有多少种取出两个相等的数的方式。

每次输出暴力统计，时间复杂度 $O(n ^ 2)$，无法通过本题。

考虑预处理。

$a_i$ 的最大值为 $2\times10^5$ 。所以可以新建一个大小为$2\times10^5$ 的数组 $cnt[]$，统计每一个数的个数。则不取出任何数，取出两个相等的数的方式为 
$$\sum_{i=1}^{2\times10^5}  \frac{cnt[i] \times (cnt[i]-1)}{2}$$

对于个数 $a_k$ ，它产生的贡献为 $cnt[a_k] - 1$ 。所以每次输出时只要减去即可。

时间复杂度 $O(n)$ 。

```cpp
#include <bits/stdc++.h>

#define MAXN 200010
#define ll long long
#define mod 1000000007

using namespace std;

int n, tot;
ll ans;

int a[MAXN];
int c[MAXN];

string s;

int main() {
        int t;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
                scanf("%d", &a[i]);
                c[a[i]]++;
        }
        for (int i = 1; i <= n; i++) {
                ans += (ll)(c[i] - 1) * c[i] / 2;
        }
        for (int i = 1; i <= n; i++) {
                cout << ans - (ll)(c[a[i]] - 1) << endl;
        }
        return 0;
}
```

---

## 作者：1n1c5c5z (赞：0)

## 题意
共有$n$个数的数组，对于每个$1 \leq k \leq n$,输出除去第$k$个数后，在数组中任意选两个数，使其相等的方法数。
  
## Solution
先用桶处理出对于数组中每种数值的个数。  
先预处理出不除去数时每个$1 \leq k \leq n$在数组中任意选两个数，使其相等的方法数$a$。  
在遍历一遍数组，输出$a$减去$a_i$的个数$-1$。
## Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200001],b[200001];
int main()
{
	int n;
  	long long tot=0;
	memset(b,0,sizeof(b));
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		b[a[i]]++;//入桶
	}
   	for(int i=1;i<=n;i++)
   	{
      	tot+=b[i]*(b[i]-1ll)/2ll;//计算每个数值的组合数Cn2
    }
	for(int i=0;i<n;i++)
    {
      	cout<<(tot-b[a[i]]+1ll)<<endl;//输出刨去一个数后的影响(-b[a[i]+1)
    }
	return 0;
}

```
PS:注意开`long long`

---

