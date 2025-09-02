# Non-square Equation

## 题目描述

让我们看看如下等式：

$x^2+s(x)×x-n=0$ ，其中$x$ ，$n$ 是正整数，$s(x)$ 是函数，相当于求十进制中$x$ 的位数之和。

给出一个整数$n$ ，找到$x$ 的最小正整数根，或确定没有这样的根。

## 说明/提示

在第一组数据中，$x=1$ 是最小根。因为$s(1)=1$ 且$1^2+1×1-2=0$ 

在第二组数据中，$x=10$ 是最小根。因为$s(10)=1+0=1$ 且$10^2+1×10-110=0$ 

在第三组数据中，方程无根。

感谢@二元长天笑 提供的翻译

## 样例 #1

### 输入

```
2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
110
```

### 输出

```
10
```

## 样例 #3

### 输入

```
4
```

### 输出

```
-1
```

# 题解

## 作者：BurningEnderDragon (赞：6)

[题目链接：CF233B Non-square Equation](https://www.luogu.com.cn/problem/CF233B)

$x^2 + s(x) \times x - n = 0$ 经过等式变换后可得 $x \times ( x + s(x) ) = n$。

题目要求 $x$ 为正整数，且 $s(x)$ 为正整数，所以 $x < ( x + s(x) )$。

显然，$x \le \sqrt{n}$，$( x + s(x) ) \ge \sqrt{n}$，即 $\sqrt{n} - s(x) \le x \le \sqrt{n}$。

因为 $x < \sqrt{n}$，且 $1 \le n \le 10^{18}$，即 $1 \le x < \sqrt{n} \le 10^9$，

所以 $1 \le s(x) \le 81$。（当 $x = 999,999,999$ 时，$s(x)=81$）

综上所述，$\sqrt{n} - 81 \le x \le \sqrt{n}$。

只需要在 $\left[ \max(1,\sqrt{n} - 81),\sqrt{n} \right]$ 内从小到大枚举 $x$，判断是否为合法的解即可。如果在该区间内没有合法解，则该方程无合法解。

**注意数据范围！**

完整代码如下：

```cpp
#include <iostream>
#include <cmath>

using namespace std;

long long s(long long x)
{
	long long ans=0;
	while(x)
	{
		ans+=(x%10);
		x/=10;
	}
	return ans;
}

long long check(const long long x)
{
	return x*x+s(x)*x;
}

long long n,x;

int main()
{
	cin>>n;
	for(int i=max(sqrt(n)-81,1);i<=sqrt(n);++i)
	{
		if(check(i)==n)
		{
			cout<<i<<endl;
			return 0;
		}
	}
	cout<<-1<<endl;
	return 0;
}
```

---

## 作者：lrx___ (赞：4)

**题意简述**

定义 $\operatorname{s}(x)$ 为 $x$ 各数位上的和。给定整数 $n$，求出最小的 $x$ 使 $x^2+x \times \operatorname{s}(x)-n=0$。如果没有就输出 `-1`。

**思路**

$N$ 很大，不能直接枚举。

将式子变形，得到：

$x^2+x \times \operatorname{s}(x)-n=0$

$x^2+x \times \operatorname{s}(x)=n$

$x \times (\operatorname{s}(x)+x)=n$

因为 $\operatorname{s}(x)>0$，所以 $x<\operatorname{s}(x)$。所以 $x<\sqrt{n}$。

因为 $n<10^{18}$，所以 $x<10^9$。

所以当 $x=999,999,999$ 时 $\operatorname{s}(x)=81$，为最大值。

所以 $x$ 一定位于 $[\sqrt{n}-81,\sqrt{n}]$ 中。直接枚举即可。

**代码**

```python
n=int(input())
for i in range(max(int(n**0.5-81),1),int(n**0.5+1)):
  if i*(i+sum(map(int,list(str(i)))))==n:
    print(i)
    exit()
print(-1)

# 代码解释

# n**0.5 为根号n，是float类型
# str(i)可以将i转换为字符串类型
# list(s)可以将字符串s转换为列表类型，每个字符为一个元素
# map(int,l)可以将l中的每个元素都执行一遍int()函数，将每个字符转为整数类型
# sum(l)可以将l中的元素求和
# exit()可以直接结束程序
```

---

## 作者：lbh666 (赞：1)

## 题目大意
给定一个 $x^2 + s(x) \times x - n = 0$ 和 $n$，求最小的 $x$ 的值。

其中，$s(x)$ 表示十进制中 $x$ 每个位上的和。

如果找不到这样的 $x$，就输出 $-1$。

## 思路
不妨拆一下。

$$ x \times x + s(x) \times x - n =0 $$

合并同类项和移项。

$$ x \times (x + s(x)) = n $$

这里的 $x \le \sqrt{n}$，因为如果 $x > \sqrt{n}$，那么 $(x + s(x)) \ge x$，相乘一定大于 $n$。

再来看，根据 $x \le \sqrt{n}$，所以 $(x + s(x)) \ge \sqrt{n}$，所以我们可以得到以下不等式。

$$ x \le \sqrt{n} \le (x + s(x)) $$

把不等式右边的 $\sqrt{n} \le (x + s(x))$ 拎出来，将不等式两边同时减 $s(x)$，得到 $(\sqrt{n} -  s(x)) \le x$，跟上面的整合一下，就成了：

$$ (\sqrt{n} - s(x)) \le x \le \sqrt{n} $$

$s(x)$ 最大只能是 $81$，因为:

$$ x \le \sqrt{n} $$

$$ n \le 10^{18} $$

$$ \sqrt{10^{18}} = 10^9 $$

$$ x \le 10^9 $$

$x$ 最大是由 $9$ 个 $9$ 组成的 $9$ 位数，加起来是 $81$，故 $s(x)$ 最大是 $81$。

既然 $s(x)$ 最大是 $81$，我们就代入上面的式子，得：

$$ (\sqrt{n} - 81) \le x \le \sqrt{n} $$

### 分析
- 讲了这么多，来分析一下怎么写程序。

- 我们暴力会超时，只能用上面的方法来做。

- 我们已经把 $x$ 取值区间的范围锁定了，是由 $\sqrt{n} - 81$ 到 $\sqrt{n}$，另外还要判断 $\sqrt{n} - 81$ 是否变成负数了，如果有，就从 $1$ 开始枚举。

- 上一条思路可以说成从 $\max(1,(\sqrt{n} - 81))$ 枚举到 $\sqrt{n}$。

- 最坏只要枚举 $81$ 次，不超时，每次判断是否合法，如果合法，跳出循环去输出，如果没找到，输出 $-1$ 即可。

## AC Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll n,x,ans;
bool flag=0;

ll wh(ll n){ //计算各个位上的和 
	ll tot=0;
	while(n){
		tot+=n%10;
		n/=10;
	}
	return tot;
}

bool pd(ll x){ //判断每个x是否合法 
	if(x*x+wh(x)*x==n)return 1;
	return 0;
}

int main(){
	scanf("%lld",&n);
	for(int i=max(1,(int)(sqrt(n)-81));i<=sqrt(n);++i){//枚举 
		if(pd(i)){//如果合法，保存答案，跳出循环 
			flag=1;
			ans=i;
			break;
		}
	}
	if(flag)printf("%lld",ans);//找到了，输出 
	else printf("-1");//没找到，输出-1 
	return 0;
}
```

---

## 作者：Luo_gu_ykc (赞：1)

~~楼顶dalao已经讲得很详细了，我就来做做补充吧~~
## 题目大意

$x ^ 2 + s(x) \times x - n = 0$

$s(x)$ 指的是 $x$ 的各位数之和。

给定 $n$；

求 $x$ 的最小值。

## 思路

解方程为 $x \cdot (x + s(x)) = n$

$\because x$ 最大也只有 $\sqrt{n}$；

$\therefore x$ 最大也只有 $10 ^ 9$；

$\therefore 1 ≤ s(x) ≤ 81$；

设答案为 $x$；

$\therefore \max(\sqrt{n} - 81) ≤ x ≤ \sqrt{n}$ 

最终思路：暴力枚举 $x$ 的值即可(因为只会执行 $81$ 次，所以不会超时)。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long // 不开 long long 见祖宗
int n;
int s(int x){
	int sum = 0;
	while(x){
		sum += x % 10;
		x /= 10;
	}
	return sum; // 各位数之和
}
signed main(){
	cin >> n;
	for(int i = max((double)sqrt(n) - 81, (double)1); i <= sqrt(n); i++){	
		if((i * i) + s(i) * i == n){ // 找到了
			cout << i;
			return 0; // 直接结束
		}
	}
	cout << "-1"; // 无解
	return 0;
}
```
辛苦写的题解，管理大大，求过！！！

---

## 作者：Flokirie (赞：1)

讲一个和楼下不大一样的思路。   
首先，显然有$1\leq s(x)\leq 81$，我们得出了几个结论：    
设$x_0$是方程的最小解，那么：
1.  $x_0<\sqrt n$。否则，原方程即为$x(x+s(x))=n$，显然左边大于右边，矛盾。
2.  $x_0>\sqrt n-81$。否则，由于$x_0+s(x_0)<\sqrt n$，代入原方程，左边小于右边，矛盾。

所以，我们只需要在$[\sqrt n-81,\sqrt n]$内进行枚举即可。   
上代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

long long s(long long x){
	long long ret=0;
	while(x){
		ret+=x%10;
		x/=10;
	}
	return ret;
}

int main(){
	long long n;
	cin>>n;
	for (long long i=max(1ll,(long long)(sqrt(n)-100));i<=sqrt(n);i++){
		if (i*i+i*s(i)==n) {
			cout<<i;
			return 0;
		}
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：_WF_ (赞：0)

## 阅读题意
我们可知：

$$ x^2 + s(x) \times x - n = 0 $$

化简可得：

$$ x^2 + s(x) \times x = n $$

$$ x + s(x)  = \displaystyle\frac{n}{x} $$

 $$∵ 0 \le s(x) $$

 $$ ∴ x^2 \le n $$
 
即：
 $$ x \le \sqrt{n} $$

 $$ ∵ n \le 10^{18} $$
 
 $$ ∴ x \le 10^{9} , 0 \le s(x)\le 81 $$
 
  $$ ∴  n - 81^2 \le x^2 \le n $$
  $$ ∴  \sqrt{ n } - 81  \le x \le \sqrt{n} $$
  
因此我们应枚举 $ [ \max( 1 , \sqrt{ n } - 81),\sqrt{ n }] $ 区间内的 $ x $ 值。
## 代码（贴

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
int wei_and(long long k)
{
	int ans=0;
	while(k>0)
	{
		ans+=k%10;k=k/10;
	}
	return ans;
}//各位相加之和
int main()
{
	long long n;
	cin>>n;
	long long k=1;
	if(sqrt(n)-81>1)k=sqrt(n)-81;
	for(long long i=k;i<=sqrt(n);i++)
	{
		if(i*i+wei_and(i)*i==n )
		{
			cout<<i<<endl;
			return 0;
		}
	}
	cout<<-1<<endl;
}
```


---

## 作者：xxxalq (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF233B) & [CF链接](https://codeforces.com/problemset/problem/233/B)

## 思路分析：

题目翻译清晰明了，在这里不过多赘述。

看到这种求函数极值的题，蒟蒻的我先想到二分，只可惜我太蒟蒻了，因为这道题的答案根本不单调。所以就只能枚举，当然不是枚举所有可能，只枚举可行区间，请看下面推导过程。

由题得：

$$x^{2}+s(x)x-n=0$$

因式分解，提取公因数 $x$ 得：

$$x(s(x)+x)-n=0$$

根据等式的基本性质，移项得：

$$x(s(x)+x)=n$$

$$\because x>0$$

$$\therefore s(x)+x>x$$

$$\therefore x<\sqrt{n}<s(x)+x$$

$$\therefore \sqrt{n}-s(x)<x<\sqrt{n}$$

$$\because 1\le n\le 10^{18}$$

$$\therefore 1\le x\le \sqrt{n}\le10^9$$

当 $x=10^9$ 时，$s(x)$ 有最大值 $81$。

所以，$x$ 的枚举范围最终确定在 $\sqrt{n}-81<x<\sqrt{n}$，这道题得枚举时间复杂度就在常数级别，$s$ 函数的时间复杂度为 $O(n)$，最终时间复杂度 $O(n)$。

然后这道题唯一的难点就在于求解 $s$ 函数，对于一个正整数 $x$，可以先通过 $x\mod10$ 求得其最后一位，然后再让 $x/=10$ ，循环上述操作知道 $x=0$。

## 代码：

```cpp
#include<iostream>
#include<cmath>
#define ll long long
using namespace std;
ll n;//注意数据范围
int f(int x){//s函数
	int ans=0;//记录答案
	//求x各数位之和
	while(x){
		ans+=x%10;
		x/=10;
	}
	return ans;
}
int main(){
	cin>>n;
	//注意枚举范围,右端点向上取整防止错过正确答案，注意括号太多不要多写少写
	for(int i=max(1LL,(ll)(sqrt(n)-81));i<=(ll)(ceil(sqrt(n)));i++){
		if(i*(i+f(i))==n){
			cout<<i<<endl;//如果合法输出答案
			return 0;
		}
	}
	cout<<-1<<endl;//如果不合法输出-1
	return 0;
}
```


---

## 作者：HuZHUNZHUN (赞：0)

根据题意：

$x^2+S(x)\cdot x-n=0$；

代入求根公式有：

$x=\dfrac{\sqrt{4n+S(x)^2}-S(x)}{2}$；

根据数据范围：

$0<1\le S(x)\le9\times18<200$；

于是就可以得到：

$\sqrt{10000+n}-100\le x\le n$ 也就是 $x$ 的范围。

在这个范围内暴力枚举就完事了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int S(int n)
{
	int ans=0;
	while(n!=0)
	{
		ans+=n%10;
		n/=10;
	}
	return ans;
}
signed main()
{
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i=floor(sqrt(10000+n))-100;i<=ceil(sqrt(n));i++)
	{
		//cout<<i<<endl;
		if(i*i+S(i)*i==n)
		{
			cout<<i<<endl;
			return 0;
		}
	}
	cout<<-1<<endl;
	return 0;
}
```

---

## 作者：_Clown_ (赞：0)

# 概述
|题号|难度|$AC$时间及记录|
| :----: | :----: | :----: |
|$\texttt{CF233B}$|$\texttt{洛谷难度:普及-}$|[$\texttt{On 2021/04/28}$](https://www.luogu.com.cn/record/50052169)|
# 解析
这道题目题目意思不难理解，

当我们看到数据范围，

就明白不能硬做。

稍加思考，就知道数字和一定很小，

也就是说对答案影响不大。

那我们不妨就只枚举接近 $N$ 的数字。![jk](https://cdn.luogu.com.cn/upload/pic/62234.png)

别的题解都证明了在 $81$ 以内就能过了。

-----
用了一个叫 **stringstream** 的东西，

顺便提一下吧。

就是说随意地将字符串和整形转换，

其他类型能不能换我不知道欸。

[参考](https://blog.csdn.net/liitdar/article/details/82598039)
```cpp
/*
Author:Xsmyy
Problem:CF233B
Date:2021/04/28
*/
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
long long N;
inline long long F(int X)
{
	register stringstream Room;
	register string S;
	Room<<X;
	Room>>S;
	register int i;
	register long long Ret=0;
	for(i=0;i<S.size();i++)Ret+=(int)(S[i]-'0');
	return Ret;
}
int main(void)
{
	BetterIO;
	#ifndef ONLINE_JUDGE
	freopen("SampleIN.in","r",stdin);
	#else
	#endif
	register long long X;
	cin>>N;
	for(X=sqrt(N)-81;X<=sqrt(N)+81;X++)if(X*X+F(X)*X==N)cout<<X<<endl,exit(0);
	cout<<-1<<endl;
	return 0;
}
···

---

## 作者：yzx72424 (赞：0)

显然，直接暴搜1-1e9是会超时的，T爆了

然后我们考虑到x<1e9,∴x_max=999999999.

∴sx_max=81

这样就好了，枚举sx 1-81即可，对于每个sx解方程算出x

再用x解除误差更小的sx验证方程是否成立

如果成立直接输出

```
#include<bits/stdc++.h> 
using namespace std;
long long s_x(long long sx1){
    long long sx2=0;
    while(sx1){
        sx2+=sx1%10;
        sx1/=10;
    }
    return sx2;
}
int main(){	    
        long long x,ans,n,sx;
        scanf("%lld",&n);
        for(long long i=1;i<=82;i++){
            x=sqrt(i*i/4+n)-i/2; 
            sx=s_x(x);
            if(x*x+sx*x-n==0){printf("%lld",x);return 0;} 
        }
        printf("-1");
    
    return 0;
}

```

---

