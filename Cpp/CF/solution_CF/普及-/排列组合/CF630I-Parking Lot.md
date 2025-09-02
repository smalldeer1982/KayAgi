# Parking Lot

## 题目描述

停车场共有 $2n-2$ 个停车位。共有 $4$ 种品牌的汽车，每种汽车的数量都远大于停车位的数量。

该公司首席执行官认为，如果停车场有 **恰好** $n$ 个连续汽车的品牌相同，则停车场会更漂亮。

给定n的值，问有多少的方案使停车场满足条件。

## 样例 #1

### 输入

```
3
```

### 输出

```
24```

# 题解

## 作者：Ryo_Yamada (赞：7)

组合数学大水题。感觉蓝题有点过了。

因为只有 $2n-2$ 个位置，而要求的是恰好 $n$ 个连续的同样的车，所以不会出现两个连续 $n$ 个同样的车。

所以只需要抉择 $n$ 个同样的车的位置，然后使其左右与其不相同，其它地方随便选就可以。

注意考虑在最左边和最右边的情况。

答案就是 $24 \times 4^{n-3} + 36\times(n-3)\times 4^{n-4}$。

如果写快速幂，记得判 $n=3$，否则可能死循环。



---

## 作者：EnofTaiPeople (赞：4)

这是一道地道的数学题，考察了组合的加法原理、乘法原理，以及快速幂。

AC 时间：5 分钟。

1. 加法原理：完成一个工程可以有 $n$ 类办法，$a_i$，$i\in[1,n] \cap Z$代表第 $i$ 类方法的数目。那么完成这件事共有 $S=a_1+a_2+...+a_n$ 种不同的方法。

2. 乘法原理：完成一个工程可以有 $n$ 个步骤，$a_i$，$i\in[1,n] \cap Z$代表第 $i$ 个步骤的不同方法数目。那么完成这件事共有 $S=a_1\times a_2\times ...\times a_n$ 种不同的方法。

3. 快速幂：顾名思义，即快速地取幂，参照[快速幂模板](https://www.luogu.com.cn/problem/P1226)。参考代码：
```cpp
typedef long long ll;
ll quick_pow(ll a,ll b){
	if(a==0)return 0;
	if(a==1||b==0)return 1;
	ll t=quick_pow(a,b/2);
	t*=t;if(b%2)t*=a;
	return t;
}
```

首先，由题意可知，假设这连续的 $n$ 辆汽车从第 $a$ 辆到第 $a+n-1$ 辆，那么，设这 $n$ 辆汽车品牌为 $type$，有 3 种可能，第 $a-1$ 辆和第 $a+n$ 辆的品牌不能是 $type$，故共有 $4\times3\times3\times4^{(n-4)}$种方案

如果就这样提交，就会喜得 WA 的好成绩啦！

原因如下：
1. 当 $n<4$ 时，快速幂无法计算正确答案，需要特判。代码如下：
```cpp
switch(n){
		case 1:printf("0\n");return 0;
		case 2:printf("4\n");return 0;
		case 3:printf("24\n");return 0;
		default:break;
	}
```
2. 当 $a=1$ 或 $a=n-1$ 时，都有一边不需要乘三，同时，乘的四也要多一个。

综上，$n>3$ 时，总方案数为 $4\times3\times4^{n-3}\times2+4\times3\times3\times4^{n-4}\times(n-3)$

AC 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll quick_pow(ll a,ll b){
	if(a==0)return 0;
	if(a==1||b==0)return 1;
	ll t=quick_pow(a,b/2);
	t*=t;if(b%2)t*=a;
	return t;
}
int main(){
	ll n,t,ans=0;scanf("%lld",&n);
	switch(n){
		case 1:printf("0\n");return 0;
		case 2:printf("4\n");return 0;
		case 3:printf("24\n");return 0;
		default:break;
	}
	t=quick_pow(4,n-4);ans=4*3*t*4*2;
	ans+=4*3*3*t*(n-3);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Grisses (赞：2)

[题面](https://www.luogu.com.cn/problem/CF630I)

一道水题，~~很符合题目的颜色~~。

对于连续的 $n$ 辆车，在 $2n-2$ 个车位里共有 $(2n-2)-n+1=n-1$ 种放置方法。其中有两种是靠边的，为了保持连续的只有 $n$ 个，我们在与连续的块相邻的车位只能放置另外 $3$ 种车，而其他 $n-3$ 个车位可以放任意车（显然不会再有连续的 $n$ 辆车了）。一共是 $2\times3\times4^{n-3}$ 种放置方法。对于另一种情况，有两个车位只能放置 $3$ 种车，其他则可以放全部的 $4$ 种，一共 $(n-3)\times3^2\times4^{n-4}$ 种。加起来乘 $4$ 就可以了。（每一种车都可以成为连续的那一种车）。

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n;
  long long ans;
  long long int fpow(long long int a,long long int b){
      long long int res=1;
      if(b<0)return 0;//特判
      while(b){
          if(b&1)res*=a;
          a*=a;
          b>>=1;
      }
      return res;
  }
  signed main()
  {
      scanf("%d",&n);
      ans=2LL*3*fpow(4LL,n-3)+(n-3)*9LL*fpow(4LL,n-4);
      printf("%lld",ans*4);	
      return 0;
  }
```

---

## 作者：Binary_Search_Tree (赞：2)

### [题目传送门](https://www.luogu.org/problem/CF630I)

因为总共有$(2n-2)$个停车位，所以不用考虑两个以上连续段的情况。

所以本题就很简单了。

枚举连续段的位置，分为两种情况：

1.若恰好在停车场的最左边或最右边，

则根据乘法原理，连续段的品牌共4种，连续段旁边的车子品牌不能与之相同，

所以答案为$4*3*4^{n-3}$

2.若在停车场中间某个位置(设连续段为$i$到$i+n-1$)

则答案与第一种情况类似，为$4*3*3*4^{i-1}*4^{n-2-i}$

所以就愉快地结束了。

代码：

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
int n;
unsigned long long ans;//防止爆int
int read(){//快读
	char c=getchar();int ans=0;
	while (c<'0'||c>'9') c=getchar();
	while (c>='0'&&c<='9') ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans;
}
void write(unsigned long long x){//快输
	if (x<10) putchar(x^48);
	else write(x/10),putchar((x%10)^48);
	return;
}
int main(){
	n=read();
	ans+=24*(1ull<<((n-3)<<1));//第一种情况
	for (register int i=2;i<n-1;i++)
            ans+=36*1ull*(1ull<<((i-2)<<1))*(1ull<<((n-2-i)<<1));//第二种情况
	write(ans);
	return 0;
}
```

---

## 作者：XL4453 (赞：1)

### 解题思路：

简单数数题，简单的乘法原理和加法原理就行了。

可以强制规定某一个范围内为某一种颜色的车，这个范围左右的不能是相同颜色，然后其他的随便排就行。

由于相同颜色车放在最左右两边时，又一边没有车可以放，所以单独考虑。

---
### 公式推导：

先考虑在中间的情况：

根据乘法原理，第一次可以选择固定颜色的的车有 $4$ 种可能情况。

考虑起点，那么这些车可能的排列位置有 $n-3$ 种。

题目要求是恰好，所以左右可以放的只有 $3$ 种。方案是 $9$ 种。

其他位置随便放，可以选择的位置一共有：$n-4$ 个。算成方案就是：$4^{n-4}$。

这种情况下一共有：$36\times (n-3)\times 4^{n-4}$ 种方案。


---
然后考虑在两边的情况，相对简单：

一个位置不能放相同的，可行的方案是 $3$ 种。

一共有：$n-3$ 个位置放可以任意放，也就是：$4^{n-3}$ 种方案。

相同的颜色一共有：$4$ 种。

左右两边，还要乘以 $2$。

这样一共是：$24\times 4^{n-3}$。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
int pow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans*=a;
		a*=a;
		b=b>>1;
	}
	return ans;
}
int n;
signed main(){
	scanf("%I64d",&n);
	int ans=24*pow(4,n-3)+36*(n-3)*pow(4ll,max(0ll,n-4));
	printf("%I64d",ans);
	return 0;
}
```


---

## 作者：MuYC (赞：1)

#### 前言

这道题属于比较简单的组合数学（算，吧

你可能需要前置知识：乘法原理

#### 思路：

因为序列长度一共$2*n - 2$，显然不需要考虑会出现两段不相邻的长度为$n$的具有相同车种的情况。

考虑两种特殊情况：

+ $n = 1$的时候，没有车位，输出$0$
+ $n = 2$的时候，有$2$个车位，轻松的知道是$4$种

然后就是$n >= 3$的情况。

首先我们发现，在$2*n - 2$的序列中取一段连续的长度为$n$的子序列共有$n-1$种方法。

因为"有**恰好**n个连续汽车的品牌相同"

题目可以抽象为序列染色。

所以取的连续这一段的左右两边不能跟这一段的车的品牌相同，所以取到的长度为$n$的段的左右两边是其余$3$种里面任意取一种，也就是这种情况:

[![DVGgSI.md.png](https://s3.ax1x.com/2020/11/17/DVGgSI.md.png)](https://imgchr.com/i/DVGgSI)

旁边的格子显然不能是蓝色。不然就不满足长度为$n$了，然后除了这两个，其他剩下的格子都可以是四个颜色中的任意一个。

在$2*n - 2$的序列中取一段连续的长度为$n$的子序列的$n-1$种方法中有两种情况:

[![DVG2lt.png](https://s3.ax1x.com/2020/11/17/DVG2lt.png)](https://imgchr.com/i/DVG2lt)

[![DVGR6P.png](https://s3.ax1x.com/2020/11/17/DVGR6P.png)](https://imgchr.com/i/DVGR6P)

这两种情况只能涂三个颜色的只有一个格子，特殊考虑。

答案计算就是:

有注解版：

$sum_1$(涂色段在中央的情况，即不在边界) = $(n - 3)$(取长度为$n$的序列的方案，而且不出现在边缘的情况) *$4$(每次长度为$n$的序列可以是四种颜色中的任意一个) * ($3 * 3$)(旁边两个格子只能取$3$种) * $pow(4,2 * n - 2 - (n + 2))$(剩下的格子可以任意涂四种颜色)

$sum_2$(涂色段在边缘) = $2$(在左边以及在右边两种情况) * $4(每种情况4种颜色)$ * $3$(旁边一个格子只能涂三种) * pow(4,n - 3)(其余涂四种)

$sum_1$ = $(n - 3) * 4 * 3 * 3 * pow(4,n-4)$

$sum_2$ = $2 * 4 * 3 * pow(4,n - 3)$

$Ans = $ $sum_1 + sum_2$

答案就是两种情况之和。

这道题代码跟上面说的没啥差别，因为是数学题嘛。。。没啥代码难度，分类讨论即可

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
signed main()
{
	int n ;
	cin >> n;
	if(n == 1){cout << 0;return 0;}
	if(n == 2){cout << 4 << endl;return 0;}
	int Ans = 0;
	Ans += 2 * 4 * 3 * pow(4,n - 3);
	Ans += 4 * ( n - 3 ) * 3 * 3 * pow(4,n-4);
	cout << Ans;
	return 0;
}
```

---

## 作者：haozinojc (赞：1)

本题应该是一道**组合数学**了。

### 思路：

因为车位数为 $2 \cdot n - 2$，所以不考虑多个连续。

所以就有了三种情况：


1. 对于连续的在中间有 $n-3$ 种方式，共四种车形。

2. 如果出现在两侧，共有 $3^{2}$ 种取法。

3. 没要求随便停，直接可以组合。

于是就有了以下式子：$24\times4^{n-3}+(9\cdot n-27)\times4^{n-3}$。

化简一下，得：$(9\cdot n-3)\times4^{n-3}$。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int power(int a,int b){
	int res=1;
	while(b){
		if(b&1)res*=a;
		b>>=1;
		a*=a;
	}
	return res;
}
signed main(){
	cin>>n;
	cout<<power(4,n-3)*(9*n-3);
	return 0;
}
```


---

## 作者：dxrS (赞：1)

### Update

2022.8.10 更改错别字（中 $\rightarrow$ 种）
***
首先可以确定一个长度为 $n$ 的区间 $[l,r]$，那么这个区间一共有 $4$ 种选择，因为是**恰好** $n$ 个，所以 $l-1$ 和 $r+1$ 就是 $3$ 个选择。

剩下 $n-4$ 个位置可以选择任意的车，就是 $4^{n-4}$，所以答案就是 $4\times3\times3\times4^{n-4}=3^2\times4^{n-3}$。

特别地，在边上（$l=1\text{或}r=2n-2$）的时候，会有一边越界，也就是说，有一个 $3$ 会变成 $4$，答案会变成 $3\times4^{n-2}$。

$l$ 右边界：$l+n-1\le2n-2\rightarrow l\le n-1$。

所以 $l\in[1,n-1]$，答案就是 $(n-3)\times3^2\times4^{n-3}+2\times3\times4^{n-2}$，时间复杂度 $O(\log n)$。

---

## 作者：幽界の冥神 (赞：1)

[题目传送法阵](https://www.luogu.org/problem/CF630I)

根据[Binary_Search_Tree](https://www.luogu.org/blog/U40985/solution-cf630i)巨佬的题解，我们显然可以知道答案，但能不能优化下呢？？

#### 根据巨佬的回复 ~~显然可以~~

那么如何实现？？?

我们看这个式子：$4*3*3*4^{i-1}*4^{n-2-i}$

这是在中间的情况，其中$i∈[2, n - 2]$即类似的式子有$n - 4$个，这就是我们优化的方向：

$4*3*3*4^{i-1}*4^{n-2-i} $

$= 36 * 4^{i-1}*4^{n-2-i}$

$=36 * 4 ^ {(i - 1) + (n - 2 - i)}$ 

$= 36 * 4 ^ {n - 3}$

与$i$无瓜，所以：

$Ans_1 = 12 * 4 ^ {n - 3}$

$Ans_2 = 36 * 4 ^ {n - 3}$

$Ans = 2 * Ans_1 + (n - 4) * Ans_2$

简短的代码：

```cpp
#include <cstdio>
#include <cstring>
#include <queue>
#include <cmath>
#include <algorithm>
#include <iostream>

#define LL long long

using namespace std;

int n;
LL ans = 0;

int main ()
{
	cin >> n;
	ans += 24 * (1ull << ((n - 3) << 1)) + 36 * (n - 3) * 1ll * (1ll << ((n - 4) << 1));
	cout << ans << endl;
	return 0;
}

```

觉得还行点个赞再走吧

---

## 作者：Smg18 (赞：0)

这是一道组合数学题罢。

因为车位数为 $2 \cdot n - 2$，所以不考虑多个连续。

- 对于连续的在中间有 $n-3$ 种方式，共四种车形。

- 如果好巧不巧的出现在了两侧，共有 $3^{2}$ 种取法。

- 没了，其他没要求随便停，直接可以组合。

所以把三个和在一起得到最后结果为:

$$(9 \cdot n - 27) \times 4^{n-3}+24 \times 4^{n-3}$$

要化简，老是幂运算太久了会超时。

所以结果化简为 :

$$(9 \cdot n - 3) \times 4^{n-3}$$

代码记得加快速幂！

```cpp
ll qq(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1)ans*=a;
		a*=a;
		b=b>>1;
	}
	return ans;
}
```

记得特判避免出现负数！

但是题目说了 $n \geq 3$ 所以这个判断无关紧要，严谨可以加！~~这题没有某毒瘤比赛毒瘤数据毒瘤~~。 

```
#include<bits/stdc++.h>
#define ll long long
#define Test ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
const int N=1e5+10,NN=1e4+10;
ll n,m,k,len,T;
ll minn=INT_MAX,maxn=0;
char c[N];
ll arr[N];
ll qq(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1)ans*=a;
		a*=a;
		b=b>>1;
	}
	return ans;
}
int main(){
	cin>>n;
	if(n==1){
		cout<<0;
		return 0;
	} 
	if(n==2){//特判
		cout<<4;
		return 0;
	}
	cout<<qq(4, n - 3) * (9 * n - 3);

	return 0;
}



```

[记录。](https://codeforces.com/problemset/submission/630/204909880)

---

## 作者：CSPJ10pts (赞：0)

## 题意：

停车场共有 $2n-2$ 个停车位。共有 $4$ 种品牌的汽车，每种汽车的数量都远大于停车位的数量。

该公司首席执行官认为，如果停车场有**恰好** $n$ 个连续汽车的品牌相同，则停车场会更漂亮。

给定 $n (3\leq n\leq 30)$ 的值，问有多少的方案使停车场满足条件。

## 分析

小学组合数学，蓝有一点过。我们把每个恰好 $n$ 个连续汽车的品牌相同的车看成一辆巨型的车。首先因为总共停车位也才 $2n-2$ 个，所以我们只会得到一辆巨型车。其次，这辆巨型车有 $n-1$ 个位置选择，其中 $2$ 个在两边，$n-3$ 在中间，于是我们分情况讨论：

+ 当这辆巨型车停在中间时，共有 $n-3$ 个位子可供选择。它两边的车不可以和它的品牌一样，所以它两边的车有 $3 \times 3 = 9$ 个不同的情况，对于和它不相邻的车，有 $4^{n-4}$ 种排列。最后考虑这辆巨型车的品牌，有 $4$ 种可能，所以当这辆巨型车停在中间时共有 $4 \times 9 \times (n-3) \times 4^{n-4} = 36 \times (n-3) \times 4^{n-4}$ 种排列。

+ 当这辆巨型车停在两边时，共有 $2$ 个位子可供选择。它两边的车也不可以和它的品牌一样，所以它两边的车有 $3$ 个不同的情况。对于和它不相邻的车，有 $4^{n-3}$ 种排列。这辆巨型车的品牌也有 $4$ 种可能，所以当这辆巨型车停在两边时共有 $2 \times 3 \times 4 \times 4^{n-3} = 24 \times 4^{n-3}$ 种排列。

综上，总共有 $24 \times 4^{n-3} + 36 \times (n-3) \times 4^{n-4}$ 种排列方法。

## 代码

这道题在输出方面还是有点坑的，像我推出结论后想都不想就用 $\tt{pow}$ 的人会惊奇的发现第 6 个点红了。为什么？因为当 $n$ 较大时，$\tt{pow}$ 会用科学计数法来表示答案。所以我们就用不带取模快速幂吧。最后，记得开 long long。

```
#include <iostream>
#include <cmath>
using namespace std;
long long n;
long long qpow (long long x, long long y) {
	long long ans = 1;
	while (y > 0) {
		if (y & 1) ans *= x;
		x *= x;
		y >>= 1;
	}
	return ans;
}
int main() {
    cin >> n;
    cout << 24 * qpow(4, n - 3) + 36 * (n - 3) * qpow(4, n - 4) << endl;
    return 0;
}
```

[直接用 $\tt{pow}$ 的死相](https://www.luogu.com.cn/record/103606424)

[通过记录](https://www.luogu.com.cn/record/103606647)

---

## 作者：TachibanaKanade (赞：0)

来个最短解。

考虑到车位数为 $2n-2$，故不用考虑出现多个连续段的情况。

分连续段在中间或在头尾两种情况。

首先是连续段在中间的情况。显然取这样的连续段共有 $(n-3)$ 种方式，共 $4$ 种车型。而对于连续段两侧的车位，其车型不能与连续段相同，共 $3^2$ 种取法。剩下的车位随便停都行，共 $4^{2n-2-n-2}$种方式。

化简，得 $sum_1=(n-3)\times 4\times 3^2\times 4^{2n-2-n-2}=36\times (n-3)\times 4^{n-4}=(9n-27)\times 4^{n-3}$.

对于连续段在两侧的情况，与连续段相邻的一个车位不能与之车型相同，类比上可得

$sum_2=4\times 4^{n-3}\times 3\times 2=24\times 4^{n-3}$.

从而

$sum=sum_1+sum_2=(9n-3)\times 4^{n-3}$.

最后直接输出即可。

注意特判 $n=1$ 和 $n=2$ 的情况。

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    int n; cin >> n;
    if (n == 1) return !printf("0\n");
    if (n == 2) return !printf("4\n");
    cout << (int)(pow(4, n - 3) * (int)(9 * n - 3)) << endl;
}
```


---

## 作者：e的x次幂 (赞：0)

### 1.前置芝士：
乘法原理、加法原理。



### 2.思路

#### case 1
![](https://cdn.luogu.com.cn/upload/image_hosting/9hcci1gs.png)
用到乘法原理，以下是选出连续 $n$ 个的步骤：

$\quad$ $\quad$ 1. 从左端和右端中选择一端；

$\quad$ $\quad$ 2. 从 $4$ 个车品牌中选择一个作为连续部分的品牌；

$\quad$ $\quad$ 3. 和连续部分挨着的（图中蓝色部分）不能再选连续部分的品牌了，所以只有 $4-1 = 3$ 个品牌可选；

$\quad$ $\quad$ 4. 黑色部分，每一个都有 $4$ 种选择，一共 $2n-2-n-1 = n-3$ 个空；

$\quad$ 以上四个步骤选择方法个数分别是 $2, 4, 3, 4^{n-3}$，所以一共方案数为 $2 \times 4 \times 3 \times 4^{n-3}$ ，如果您有强迫症请自行化简（

#### case 2 
![](https://cdn.luogu.com.cn/upload/image_hosting/9jz1xl4d.png)
以下是选出连续 $n$ 个的步骤：

$\quad$ $\quad$ 1. 从 $4$ 个车品牌中选择一个作为连续部分的品牌。连续部分是一个长度为 $n$ 滑动窗口，个数为 $n-3$（减去**case 1**中 $2$ 种靠边的情况）；

$\quad$ $\quad$ 2. 和连续部分挨着的（图中蓝色部分）不能再选连续部分的品牌了，所以只有 $4-1 = 3$ 个品牌可选；

$\quad$ $\quad$ 3. 黑色部分，每一个都有 $4$ 种选择，一共 $2n-2-n-2 = n-4$ 个空；

$\quad$ 以上四个步骤选择方法个数分别是 $4(n-3), 3 \times 3, 4^{n-4}$，所以一共方案数为 $4(n-3) \times 3 \times 3 \times 4^{n-4}$。

### 代码
```cpp
#include <iostream>
#include <cmath>
using namespace std;

typedef long long LL;

LL calc(LL n) {
	if(n == 1) return 0;
	if(n == 2) return 4;
	
	LL x = 2*4*3*pow(4, n-3);
	LL y = 4*(n-3)*3*3*pow(4, n-4);
	return x+y;
}

int main() {
	LL n;
	cin>>n;
	cout<<calc(n);
	return 0;
}
```


---

