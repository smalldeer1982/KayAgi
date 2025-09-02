# Tavas and Karafs

## 题目描述

问题描述
有无限个食品排成一排，其中第 i 个食品的体积 si 为 A + ( i - 1 ) * B 。 每一次，你最多可以同时吃 M 个食品，并使这 M 个食品的体积都减少 1 ，体积为 0 表示该食品被吃掉。

现在有 n 个询问，每个询问包含三个整数 L ， T ， M ，表示从第 L 个食品开始往右边吃，每次最多吃 M 个食品（ 可以是不连续的 M 个），最多吃 T 次，求一个最大的R ( L ≤ R ) ，使得第 L 个到第 R 个食品都被吃掉（必须是连续的）。

## 样例 #1

### 输入

```
2 1 4
1 5 3
3 3 10
7 10 2
6 4 8
```

### 输出

```
4
-1
8
-1
```

## 样例 #2

### 输入

```
1 5 2
1 5 10
2 7 4
```

### 输出

```
1
2
```

# 题解

## 作者：Haworthia (赞：3)

虐红题狂魔的第一篇题解……

~~话说这题貌似是水题~~，只是题目完全不可读。

这题我们第一眼就能看出要用二分。~~因为是我们学校二分专题里的题~~

仔细读题~~（看题解）~~我们可以发现两点：

1、max( A(l)+ A(l+1)+...+A(ans))<=t，即A(ans)<=t。

如何理解呢？总共吃t次，每个食物最多被吃的次数也就是t，又因为A(l)~A(ans)中A(ans)最大，最大的若被吃成0，小一些，排在前面的就肯定吃成0了。

2、A(l)+ A(l+1)+...+A(ans)<=t*m。

若把A(l)~A(ans)全部吃成0，则肯定至少吃了A(l)~A(ans)的体积之和。求体积之和我们可以用等差数列求和公式。

根据这两条我们可以进行二分。二分中down是最小值，就是l自己。up是最大值，关于up的取值，由第一点规律可知，如果我们设up为第x项,则up的最大值，由等差数列通项公式可得a+b*(x-1)。

所以有a+b*(x-1)<=t,即x<=(t-a)/b+1，即up的取值。

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
typedef long long ll;
ll a,b,n,s,t,m;
ll z(int x)//本题涉及的l、down、up均指的是数列中的第几项，所以用这个函数把它们转换成该项的值 
{
	return a+b*(x-1);
}
int main()
{
	scanf("%lld%lld%lld",&a,&b,&n);
	while(n--)
	{
		scanf("%lld%lld%lld",&l,&t,&m);
		if(z(l)>t)//如果第 l项自己的值都大于t，说明吃t次后连体积最小的食物都吃不完，输出-1 
		{
			printf("%d\n",-1);
			continue;
		}
		ll down=l,up=(t-a)/b+1,mid;
		while(down<=up)//二分常规操作 
		{
			mid=down+up>>1;//大神们说位运算要快一丢丢 
			if((z(s)+z(mid))*(mid-s+1)/2<=t*m)//等差数列求和公式：（首项+末项）*项数/2 
				down=mid+1;
			else
				up=mid-1;
		}
		printf("%lld\n",down-1);
	}
    return 0;
}

```

---

## 作者：yangmuguang (赞：1)

### 前言
这道题的所有题解都是二分，所以我来一篇数学做法的题解。
### 题意
有一个无限序列 $a$，它由 $2$ 个参数决定：$A$ 和 $B$。对于任意 $i$，满足 $a_i=A+b\times(i-1)$。定义一次 $m$-操作为在数列中选取不大于 $m$ 个非 $0$ 数，让它们的值都减 $1$。让它们你要处理 $n$ 个询问，每个询问由 $3$ 个数 $l,t,m$ 构成，表示询问最大的 $r$，使得从 $l$ 到 $r$ 的子段可以在 $t$ 次 $m$-操作后全部清零。不存在的话输出 $-1$。
$1\le n\le 10^5,1\le A,B,l,t,m\le 10^6$
### 解法
先证明一个命题：一个序列可以在 $t$ 次 $m$-操作内可以被完全清除当且仅当序列中最大值不超过 $t$ 且序列中所有数之和不超过 $m\times t$。

证明：显而易见，若序列可以被清除，它一定满足这些条件。所以现在假设有一个满足这些性质的数列，给出一种清掉它的方式。首先，这个数列中值为 $t$ 的数一定不超过 $m$ 个，不然违背条件。所以，我们把最大的 $m$ 项减去 $1$，如果不到 $m$ 项能减则减去能减的最多的数。这样，还剩下 $t-1$ 次操作，而最大值最多为 $t-1$，且不会超过 $m$ 个。（如果超过的话原数列所有项之和至少为 $(m+1)(t-1)+m>m\times t$，矛盾）。这样做了 $t$ 次操作后，最大值为 $0$。证毕。

我们可以应用这个命题，把问题转化为：求出最大的 $r$，使得 $a_r\le t$ 且 $\sum_{i=l}^r a_i\le m\times t$。

由于 $a$ 是一个等差数列，可以将 $a_r$ 转化为 $A+Br-B$，将 $\sum_{i=l}^ra_i$ 转化为 $(Bl+Br+2A-2B)(r-l+1)\div2$。

得出关于 $r$ 的一元二次不等式组：
$$
\begin{cases} A+Br-B\le t \\ (Bl+Br+2A-2B)(r-l+1)\div2\le mt\end{cases}
$$
解不等式组得
$$
\frac{-2A+B-\sqrt{\Delta}}{2B}\le r\le \min(\frac{-2A+B+\sqrt{\Delta}}{2B},\frac{t-a+b}{b})
$$
其中
$$
\Delta=(2A-B)^2+8Bmt-4B(Bl+2A-2B)(1-l)
$$
然后按照它打就行了，记得要开 double，如果解出来的最大的 $r$ 比 $l$ 还小，要输出 $-1$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define faster ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0)
ll n;
double a,b;
int main()
{
	faster;
	cin>>a>>b>>n;
	while (n--)
	{
		double l,t,m;
		cin>>l>>t>>m;
		double delta=(2.0*a-b)*(2.0*a-b)+8.0*m*t*b-4.0*b*(b*l+2.0*a-2.0*b)*(1.0-l);
		ll res1=(-2.0*a+b+sqrt(delta))/2.0/b;
		ll res2=(ll)((t-a+b)/(b));
		ll res=min(res1,res2);
		if (res<l){cout<<"-1\n";continue;}
		cout<<res<<"\n";
	}
    return 0;
}

---

## 作者：XL4453 (赞：0)

### 解题思路：

本题有一个很明显的单调性，如果对于某一个位置不能吃掉所有的，那么在这个位置之后的所有的位置也都不能。

那么就考虑二分右端点的位置，然后对其进行判断。

但直接判断是线性复杂度的，无法接受，所以考虑对其进行优化。

发现如果有一段区间可以被吃完当且仅当这一段区间的食物总量不比可以吃掉的食物总量多，且最高食物不比所吃的食物次数多。

所以可以直接 $O(1)$ 判断，总复杂度为 $O(nlogn)$。

代码实现的时候，可以将右端点直接定位到吃的次数不大于最高食物的位置，这样判断时会方便一些。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
long long v[2000006],n,a,b,l,r,y,z;
int main(){
	scanf("%lld%lld%lld",&a,&b,&n);
	for(long long i=1;i<=2e6;i++)
	v[i]=a+(i-1)*b,v[i]+=v[i-1];
	for(long long i=1;i<=n;i++){
		scanf("%lld%lld%lld",&l,&y,&z);
		long long L=l,ans=-1;
		r=(y-a)/b+1;
		while(l<=r){
			long long mid=(l+r)>>1;
			if(v[mid]-v[L-1]<=y*z){
				ans=mid;
				l=mid+1;
			}
			else r=mid-1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：李至擎 (赞：0)

[点我看题](https://www.luogu.com.cn/problem/CF535C)

其实，这个题根本不需要那么麻烦，只要用一个前缀和来判断就好了。

因为这道题看起来比较棘手，没有什么可行的思路，只好枚举；但是普通的枚举又一定会超时，所以，我们想到了二分。

前置芝士：详见这篇[讲二分的文章](https://oi-wiki.org/basic/binary/)，此处就不再赘述。

思路：二分答案（吃的区间），用贪心检验是否可行。

方法（以一次二分为例）：

- $1.$ 二分枚举答案的值；

- $2.$ 计算在此范围内是否能吃完；

- $3.$ 根据上一步结果修改取值范围，并记录答案。

细节：

- 本题数据过大，需要开 $long$ $long$ 进行记录。

代码：

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL a,b,n,s[1000005],L,m,t;//a、b、n、L、m和t如题意，s是前缀和
LL check(LL x)//判断是否可行 
{
	LL p=s[x]-s[L-1];//计算区间总体积 
	return p<=m*t;//判断能否吃完 
}
int main()
{
	scanf("%lld%lld%lld",&a,&b,&n);//输入 
	for(LL i=1;i<=1000000;i++)
	{
		int num=a+(i-1)*b;//根据题目给的公式计算体积 
		s[i]=s[i-1]+num;//前缀和 
	}
	for(LL i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld",&L,&t,&m);
		LL l=L,r=(t-a)/b+1,ans=-1;//l、r是右端点的值的左右取值范围，ans记录下二分的答案 
		while(l<=r)//标准二分 
		{
			LL mid=l+((r-l)>>1);//防溢出 
			if(check(mid))//如果能吃完 
			{
				ans=mid;//记录答案 
				l=mid+1;//往更大的范围找 
			}
			else//反之不行 
			{
				r=mid-1;//往更小的范围找 
			}
		}
		printf("%lld\n",ans);//输出答案 
	}
	return 0;
}
```

---

## 作者：冰夜king (赞：0)

#### 由于此题只有一篇题解，而那位大佬的等差数列求和公式本蒟蒻又看不懂，在经历了一个下午的奋斗，本蒟蒻终于想出了一个神奇的方法——贪心+二分。
详细的注释在代码中——
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,l,r,m,t,g,ans,s,w,n,i;
long long p(int x)
{
	return a+b*(x-1);
}
int main()
{
	cin>>a>>b>>n;
	while(n--)
	{
		scanf("%lld%lld%lld",&w,&t,&g);
		if(p(w)>t)
		{
			printf("-1\n");
			continue;
		}
		l=w;
		r=(t-a)/b+1;
		while(l<=r)
		{
			m=(l+r)>>1;
			s=a*(m-w+1);
			//s=p(w)+...+p(m)=a+b*(w-1)+...+a+b*(m-1)
			//s=a*(m-w+1)+b*((w-1)+...+(m-1)) 
			s+=((m+w-2)*(m-w+1))/2*b;
			if(s<=t*g)ans=m,l=m+1;
			//当 前一个苹果吃完后就可以从后一个苹果开始吃，用最优策略可以做到不浪费任何一次吃苹果的机会 
			else r=m-1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

