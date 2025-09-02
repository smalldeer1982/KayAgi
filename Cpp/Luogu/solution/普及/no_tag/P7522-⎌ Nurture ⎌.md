# ⎌ Nurture ⎌

## 题目背景

![Nurture](https://mivik.gitee.io/image/nurture_wallpaper.jpg)

> "I realized I shouldn't write music with the expectation that the productivity or achievement will fix my problems, but instead with the hope that my honest expression will move people the way music moves me."
>
> — Robinson in a letter to his fans

## 题目描述

Mivik 正在听 Nurture，但这时教练走了进来，Mivik 便假装自己在做这道题。

你有一个长度为 $n$ 的序列 $v$，你每次可以 **取出** 两个数 $a,b$，并把 $a-b$ 添加到序列中。重复操作直到序列中只剩下一个数，你需要求出这个数的最大值。

~~（结果教练一眼秒了这水题，Mivik 因没事刷水题被批判了一番）~~

## 说明/提示

### 样例解释

样例一：第一步取出 $1,2$，并把 $1-2=-1$ 添加到序列中，此时序列为 $[3,-1]$；然后取出 $3,-1$，将 $3-(-1)=4$ 添加到序列中，此时序列只剩下一个数 $4$。可以证明不存在使剩下的数更大的操作方式。

### 数据范围

对于全部数据，有 $1\le n\le 3\cdot 10^5$，$|v_i|\le 10^9$。

Subtask 1 (15 pts)：保证 $n\le 3$。

Subtask 2 (30 pts)：保证 $v_i\ge0$。

Subtask 3 (55 pts)：无特殊限制。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
4```

## 样例 #2

### 输入

```
4
-4 5 -2 -3```

### 输出

```
14```

## 样例 #3

### 输入

```
8
2 0 2 1 0 4 2 3```

### 输出

```
14```

# 题解

## 作者：Mivik (赞：15)


### Subtask 1

我会枚举！

### Subtask 2

$n=1$ 直接输出 $v_1$。否则我们观察到，最大的剩下的数即为最大的 $n-1$ 个数之和减去最小的一个数。证明如下：

不难发现每个数对答案的贡献只可能是 $-v_i$ 或者 $v_i$。首先最终的数不可能为序列中所有数之和，因为考虑任何时刻序列中的一个数，它必然是由至少一个 $v_i$（正的）再加上一堆可正可负的 $v_j$ 构成的，这个可以简单归纳证明。然后如果最后的数是 $v_1+v_2+\cdots+v_n$ 的话，考虑最后一次操作，必然是将 $v_i$ 减去 $\left(-\sum_{j\ne i}v_j\right)$，但是根据上面我们的结论后面那个数是不可能存在的，构成矛盾。

然后我们构造一种方案得到这个最大的数。很简单：不妨令 $v$ 从小到大有序，我们取出 $v_1,v_2$ 得到 $(v_1-v_2)$，取出 $(v_1-v_2),v_3$ 得到 $(v_1-v_2-v_3)$，以此类推，直到最后得到 $v_1-v_2-\cdots-v_{n-1}$，最后用 $v_n$ 减去这个数就可以得到 $-v_1+v_2+\cdots+v_n$。

### Subtask 3

推广上面的结论：在 $n\ne 1$ 时，对于任意整数 $1\le k<n$，我们都存在一种方案使得最终的数是最大的 $(n-k)$ 个数减去最小的 $k$ 个数。

这里直接构造证明：令 $v$ 从小到大有序，取出 $v_1,v_{k+1}$ 得到 $(v_1-v_{k+1})$，取出 $(v_1-v_{k+1}),v_{k+2}$ 得到 $(v_1-v_{k+1}-v_{k+2})$，重复直到得到 $(v_1-v_{k+1}-v_{k+2}-\cdots-v_{n-1})$，然后用 $v_n$ 减去它得到 $(v_{k+1}+v_{k+2}+\cdots+v_n-v_1)$，最后再用这个数依次减去 $v_2,v_3,\cdots,v_k$ 即可得到 $(v_{k+1}+v_{k+2}+\cdots+v_n-v_1-v_2-\cdots-v_k)$。

于是我们直接对 $v$ 排序。如果全是正数，则输出前 $n-1$ 大的减去最小的；如果全是负数，则输出最大的减去前 $n-1$ 小的；否则直接输出所有数的绝对值之和即可。

[mivik.h](https://mivik.gitee.io/mivik.h) / [代码](https://paste.ubuntu.com/p/rC5fpppKst/)


---

## 作者：Argon_Cube (赞：13)

* **【题目链接】**

[Link:P7522](https://www.luogu.com.cn/problem/P7522)

* **【解题思路】**

本题是一道贪心题。

观察样例，我们发现，想让结果最大，显然要让最后两个数差最大。

所以，我们要想办法拉开最大数与最小数的差距。

显然，一个数减正数会变小，减负数会变大。那些 $0$ 对于答案是不起作用的，随便怎么处理都好。

那么，我们可以让最大的数减负数，最小的减正数，这样可以最大化数列的极差。

显然，除了最大值与最小值外，每个数都能让答案增加这个数的绝对值。

不用排序，只要三个数：最大值，最小值，所有数绝对值总和。

复杂度 $\Theta(n)$，优于目前所有题解的 $\operatorname O(n\log_2 n)$。

哦，对了，数列中只有一个数时要特判。

* **【代码实现】**

```cpp
#include <iostream>
#include <cmath>

using namespace std;

int main(int argc,char* argv[],char* envp[])
{
	long long minn=0x7fffffff,maxn=-minn,tmp,cnt;
	long long sum=0;
	cin>>cnt;
	if(cnt==1)//数列中只有一个数时特判
		return (cin>>tmp,cout<<tmp)&&0;
	while(cnt--)
	{
		cin>>tmp;
		sum+=abs(tmp);
		minn=min(minn,tmp);
		maxn=max(maxn,tmp);
	}
	cout<<(long long)(sum-abs(minn)-abs(maxn)+(maxn-minn));//记得要从总和里减去最大值与最小值！
	return 0;
}
```

---

## 作者：斜揽残箫 (赞：9)

## Description

一个序列中不断取出两个数 $A,B$ 进行 $A - B$，再把 $A - B$ 丢进去，最大化最后剩下的一个数。


## Solution

我们显然要得出一个最大数，一个最小数，使得答案最大。

因为有正数和负数，要分类讨论 ： 

先假设一个由小到大的序列 $A$。

+ 全为非负数

我们可以先排序，用最小的那一只减去除最大的以外的所有数，最后再用最大的减去这个数的，即 ： 

$$
\begin{aligned}
Ans &= A_n - (A_1 - \sum_{i = 2} ^ {n - 1}A_i)\\&=\sum_{i = 2} ^ n - A_1
\end{aligned}
$$

因为现在整个序列全为正数，我们要确保最大，因为大的数字对答案贡献大，不能枚举相邻两项来是答案减小，构造一个负数，来用它减去除最大的以外的全部正数，就可以得到最小的解，再用最大的数减去即可。

+ 全为负数

和全为正数一样，我们可以反过来想，我们能不能用两个最大的数构造一个正数，再用这个数减去其他数，答案是肯定的，即

$$
\begin{aligned}
Ans &= (A_n - A_{n - 1}) - \sum_{i = 1} ^ {n - 2}A_i \\ &= A_n - \sum_{i = 1} ^ {n - 1}A_i
\end{aligned}
$$

证明同上。

+ 数有正有负

我们发现这种情况下，我们完全可以用所有负数减去除最大值以外的所有正数，再用最大数一一减去这些负数。

假设到从 $1 \cdots j$ 为负数，从 $j + 1 \cdots n$ 为正数。

$$
\begin{aligned}
Ans &= A_{n} - (\sum_{i = 1} ^ jA_i - \sum_{i = j + 1} ^ {n - 1}A_i)\\&= \sum_{i = j + 1} ^ nA_i - \sum_{i = 1} ^ j A_i\\&=\sum_{i = 1} ^ n \left|A_i\right
|\end{aligned}
$$

实在看不懂可以自己手膜一下。

还有就是要判断一个数的情况，这种情况下只能输出原数。

## Code
```cpp
#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
const int Maxk = 500010;
int a[Maxk],Ans,n,sum,tot;
inline int read()
{
	int s = 0, f = 0;char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}
int Abs(int x) {return x > 0 ? x : -x;}
signed main()
{
  n = read();
  for(int i = 1;i <= n;i ++) {
    a[i] = read();
    sum += a[i];
    tot += Abs(a[i]);
  }
  if(n == 1) {
    cout << a[1] << endl;
    return 0;
  }
  sort(a + 1,a + n + 1);
  if(a[1] >= 0) Ans = sum - a[1] - a[1];
  else if(a[n] < 0) Ans = a[n] + a[n] - sum;
  else Ans = tot;
  cout << Ans << endl;
  return 0;
}
```


---

## 作者：KSToki (赞：4)

# 题目大意
题面就很简洁了。
# 题目分析
首先我们通过看样例可以发现，将 $a$ 数组排序，答案为：
$$a_n-a_1+\sum_{i=2}^{n-1}|a_i|$$
给出感性的证明：首先一定要有一个数减和一个数被减，自然是拿最大的减最小的。$a_n$ 是个正数就显然了，如果是个负数，必然有一个数的绝对值在做负贡献，而 $a_n$ 绝对值最小。剩下的数如果是负数就直接用 $a_n$ 减，否则先用 $a_1$ 减，就相当于给 $a_n$ 加了这个数，因为 $a_n-(a_1-a_i)=a_n-a_1+a_i$。这样一定是最优的，特判一下 $n=1$ 即可。

严谨的证明：显然这个答案可以实现，方案已经解释了，所以只需证明不存在比上述答案更大的解。分为三种情况：

$a_n>0$ 且 $a_1<0$，上述式子等同于 $\sum_{i=1}^{n}|a_i|$，自然不会更大。

$a_n>0$ 且 $a_1>0$，上述式子等同于 $\sum_{i=1}^{n}|a_i|-2\times a_1$，只需关注后半部分，因为均为正数，$a_x$ 越小越好，所以 $x$ 取 $1$。

$a_n<0$ 且 $a_1<0$，上述式子等同于 $\sum_{i=1}^{n}|a_i|+2\times a_n$，同样只需关注后半部分，因为均为负数数，$|a_x|$ 越小越好，所以 $x$ 取 $n$。

得证。
# 代码
还要记得开 `long long`：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,a[300001];
long long ans;
int main()
{
    cin>>n;
    for(int i=1;i<=n;++i)
       cin>>a[i];
    sort(a+1,a+n+1);
    ans=a[n]-a[1];
    if(n==1)
       ans=a[1];
    for(int i=2;i<n;++i)
       if(a[i]>0)
         ans+=a[i];
       else
         ans-=a[i];
    cout<<ans;
}
```

---

## 作者：闲人 (赞：3)

# 主要是一个巧妙的思路  

[题目传送门](https://www.luogu.com.cn/problem/P7522)

## 题目分析  

- 有一堆数，然后那两个数，让一个去减另一个得到一个新数，然后放在这堆数里  

- 求最后一个数最大。  
- $ 1\le n\le 3\times 10^{5} , \left |v_i  \right | \le 10^{9} $  

## 思路  
首先我们看几个样例：  

3  
1 2 3  
ans $ = $ 4   
  
4  
-4 5 -2 -3  
ans $ = $ 14

8  
2 0 2 1 0 4 2 3  
ans $ = $ 14  
可以发现第二个样例和第三个中ans的值是所有数的绝对值之和，但是第一个样例并非如次。于是我们自己造几个数据：  
6  
1 1 1 1 1 1  
ans $ = $ 4  

6  
-1 1 1 1 1 1  
ans $ = $ 6  

同样是六个数，为什么一个负数的差别使得一个答案是4，另一个是6。  

1. 顺着这个思路我们可以对数列中的正负性分析出一下结论：  

1. 正数 $-$ 负数 可以得到一个最大值。  
1. 负数 $-$ 正数 可以得到一个最小值。  
1. 当且仅当数列中存在异号的数才可以把所有的负数转化成正数从而得到最大值。  
1. 如果数列中只有同号的数则 （1）若全是负数，则把最大值转化成正数，使数列中存在异号情况。（2）若全是正数，则把最小值转化成负数数，使数列中存在异号情况。  
1. 如果只有一个数，输出去就完了。

那么我们的思路就出来了：  

1. 如果异号，则输出所有数绝对值之和。  

1. 如果同号，就输出所有数绝对值之和减两次最大（小）值。  
1. 如果只有一个数，输出去。  

是不是超 ~~简单~~ 。  

## AC代码  

Code：  
```cpp
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

const int N = 1000010;

long long n, v[N];

int main(){
    cin >> n;
    long long num = 0, ans = 0, Min = 1e9 + 1, Max_ = -1e9 - 1;
    for(int i = 0; i < n; i++){
        cin >> v[i];
        if(Max_ < v[i]) Max_ = v[i];				//记录最大值 
        if(v[i] <= 0) {
            num ++;
        }
        if(Min > v[i]) Min = v[i];					//记录最小值 
    }
    if(n == 1) {									//判断只有一个数的情况 
        cout << v[0]; return 0;
    }
    for(int i = 0; i < n; i ++)						//所有数绝对值之和
    {
         ans += abs(v[i]);
    }
   if(num != 0 && num != n){						//如果存在异号 
       cout << ans;
   }
   else {											//如果存在同号 
       if(num == 0) cout << ans - 2 * Min;			
       else cout << ans - abs(2 * Max_);
   }
    return 0;
}
```


## 后记  
只是我唯一做出来的题。  

---

## 作者：_lfxxx_ (赞：3)

**题目传送门：[P7522 ⎌ Nurture ⎌](https://www.luogu.com.cn/problem/P7522#submit)**
### 题意：
有一个长度为 $n$ 的序列 $v$ ，每次可以将两个数 $a$ , $b$ 替换成 $a-b$ 。问当还剩一个数时，最大数是多少。
### 思路：
不难看出，这道题要用贪心解决。因为 $a-b$ 相当于 $a+(-b)$ ，说明这个数列中的 $1$ 个数必变号， $1$ 个数必不变。（ $a-b$ 中的 $a$ 没变， $b$ 变了）（除序列中只有 $1$ 个数外）。

要想使值最大，就要将最小的数变号，最大的变号，其它的去绝对值就好。

**重~~难~~点**：我们不用考虑方案，只需要求出值。因为绝对有一种方案能凑成这样的效果。

我来结合样例说明一下。

```
4
-4 5 -2 -3
```
这里面最小的是 $-4$ ，最大是 $5$ ，其他为 $-2$ 和 $-3$ 。

那么答案就为 $-(-4)+5+|-2|+|-3|$ 即为 $14$ 。

如果序列中只有 $1$ 个数，那么答案就为那个数。

当你理解上面的内容后，这道题就变得十分简单了。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[300001];
int main(){
	int n;
	long long ans=0;
	cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
    if(n!=1){//不是1
	    sort(a+1,a+1+n);//排序为了找到最大数与最小数
	    ans=a[n]-a[1];
	    for(int i=2;i<n;i++)
		    ans+=abs(a[i]);//其他全加上它们的绝对值
    }
    else//是1
        ans=a[1];
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Durancer (赞：3)

### 前言

这是一道比赛题 and 原题（确信，但是我只推出了最终结论的前身。

### 思路

分情况讨论

1、全都是正数

因为是减法操作，那么我们就尽量的使数的贡献全部加进去，如果不可以，那么就使损耗降到最小。

注意看题面这是广义的左右方向。

那么选排序是重点。

我们看序列（升序排列）特别鸣谢 Szt 的数据支持：

$$\langle 1,5,6,10\rangle$$

一开始，我们要是更大的数尽量多的对答案有贡献，所以可以考虑先把小的数的贡献减少，以此来增加大数的贡献，很显然，是减法，那么减到最后一个数之前，我们要尽量是除了最后以外的那些数的减法运算的结果小，因为是减法，所以越小到最后贡献值就更大 （最好是负数，贡献全部）

那么就取 $1,5$，因为要向负数迈进，所以要小数被大数减去。

$$num=1-5=-4$$

至于减到最后一个数之前，一定要是这个数 $num$ 变得更小，那么就直接让 $num$ 被 $a_2…a_{n-1}$ 减去。

最终的出来的是 $num=-10$ 此时 $6$ 的贡献是达到了最大，因为最后要构造最大值，那么最后一次运算一定是大数减小数。

所以有：

$$ans=10-(-10)=20$$ 

可以证明这是最大的。

化成广义的式子就是：

$$ans=a_n-(a_1-a_2-…-a_{n-1})$$

$$ans=-a_1+a_2+……a_{n}=-a_1-a_1+a_1+a_2+…+a_n$$

$$ans=sum-2\times a_1$$

2、全部都是负数

还是按照上面的思路来，这一次是使绝对值大的数贡献的越多，那么就把绝对值最小的两个数都做减法运算。也就是最大的两个数。

因为要是除了这两个数之外的所有数的贡献达到最大，那么肯定是大的减去小的构造一个正数，然后其他的减负运算时就可以全部贡献他的绝对值了。

广义的式子就是：

$$ans=a_n-a_{n-1}-a_{n-2}-…-a_1$$

$$ans=a_n+a_n-a_n-a_{n-1}-…a_1$$

$$ans=-sum+2\times a_n $$

3、其他情况

可以知道，如果出现 $0$ 不管是有正数还是负数，都可以把他们的绝对值全部贡献上去，所以直接是数列绝对值的总和

### 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
#include<map>
#include<cmath>
#define int long long 
using namespace std;
const int N=5e5+9;
int a[N];
int n;
int ans;
bool sun,moon;//正负 
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9')
	{
		if(s=='-')
			f=-1;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=getchar();
	}
	return f*x;
}
signed main()
{
	n=read();
	int tol=0; 
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		if(a[i]<0) moon=true;
		if(a[i]>0) sun=true;
		tol+=abs(a[i]);
	}
	sort(a+1,a+1+n);
	if(n==1) cout<<a[1]<<endl;
	else if(n==2) cout<<max(a[1]-a[2],a[2]-a[1])<<endl;
	else 
	{
		if(sun&&!moon)//全为正
		{
			//cout<<tol<<endl;
			printf("%lld\n",tol-2*a[1]);
			return 0;	
		} 
		if(moon&&!sun)//全为负数
		{
			printf("%lld\n",tol+2*a[n]);
			return 0;
		} 
		else //都有
		{
			printf("%lld\n",tol);
			return 0;
		} 
	}
	return 0;
} 
```



---

## 作者：lcyxds (赞：1)

题目描述：你有一个长度为 $n$ 的序列 $v$，你每次可以 **取出** 两个数 $a,b$，并把 $a-b$ 添加到序列中。重复操作直到序列中只剩下一个数，你需要求出这个数的最大值。

显然这个可以看成序列通过任意排列之后添加减号和小括号所组成的表达式，由于减法不满足交换律和结合律，我们将此表达式转换为所有元素添加符号之后求和。不妨我们将前者叫做**减号表达式**，后者叫做**符号表达式**。两个表达式**等价**当且仅当减号表达式拆开所有括号后所有元素前面的符号与符号表达式中该数的符号一致。

下面我们证明这个结论：一个长度大于1的符号表达式能表示成减号表达式，当且仅当符号表达式中所有元素符号不同。

证明：必要性：当 $n=2$ 时，减号表达式和符号表达式均只有 $v_1-v_2$ 和 $v_2-v_1$ 两种。

$n>2$ 时，减号表达式有三种构成方法：（下文中 $A,B$ 均为长度大于 $1$ 的减号表达式）：

1. $v_i-A$
2. $A-v_i$
3. $A-B$

由于 $A$ 和 $B$ 对应的符号表达式均有不同符号的元素，所以得到的减号表达式对应的符号表达式中也存在不同符号的元素。

充分性：将符号表达式构造为减号表达式即可。具体的，当项数大于 $2$ 时分离出符号不与其他符号全不相同的一项，然后构造成 1 式或 2 式的形式即可。

综上，我们只需要找到一个符号不全相同的符号表达式，使得它的值最大。

先考虑如果不考虑符号不全相同的条件怎么做，将每个数字最大化，也就是取绝对值，答案就是它们的和。

这时只有全为正或者全为负的情况一定违背符号不全相同的性质。对于全正，找出最小的取负；对于全负，找出最大的取正。上述两条应用于一般情况也能得出最优解。

于是，只需要找出最小值和最大值，将其他值绝对值求和加最大值减最小值就是答案了。

```cpp
#include <cstdio>
#include <cmath>
#include <iostream>

using namespace std;
int Read() {
    int res = 0;
    int f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c=='-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        res = res*10+(c^'0');
        c = getchar();
    }
    return res*f;
}
int main() {
    int n = Read();
    if (n==1) {
        printf("%d\n", Read());
        return 0;
    }
    int mini = Read();
    int maxi = Read();
    long long res = 0;
    int cur;
    if (mini > maxi) swap(mini, maxi);
    for (int i = 2; i < n; i++) {
        cur = Read();
        if (cur < mini) swap(cur, mini);
        if (cur > maxi) swap(cur, maxi);
        res+=abs(cur);
    }
    printf("%lld\n", res+maxi-mini);
    return 0;
}
```

时间复杂度：$\Theta(n)$

空间复杂度：$\Theta(1)$

~~要是我放这个题我会数据范围给9e6空间1MB~~

---

## 作者：HSY666 (赞：1)

从题目可知，我们要求最后剩下的两个数的差最大，显然要使剩下的两个数大的尽量大，小的尽量小，所以我们可以在输入数据时就把序列中的最大值 $Max$ 和最小值 $Min$ 先处理出来并记住它们的位置，注意，如果 $Max$ 和 $Min$ 的位置相同，说明这个序列中所有的数均相同，那么就要让 $Min$ 的位置 $q = q + 1$ （或让 $Max$ 的位置 $p = p + 1$ ）。下面就很显然了，遍历一遍序列 $a_1,a_2...a_n$ ，如果遍历到位置 $i$ 是 $Max$ 或 $Min$ 的位置，那就跳过（免得将它们算两遍），如果 $a_i = 0$ ，那它对答案没有贡献，也跳过。接下来如果 $a_i > 0$ ，那么 $Min = Min - a_i$ ，使得 $Min$ 尽量小，同理，如果 $a_i < 0$ ，那么 $Max = Max - a_i$ ，使得 $Max$ 尽量大。最后答案就是 $Max - Min$ ，显然这样答案就是最大的。

注意当 $n=1$ 时要特判，输出 $a_1$ ，~~我就在这卡了一会~~ 。

还要注意数据范围，需要开``long long``。

代码如下：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int n,pMax,qMin;
long long a[300005],maxn=-2e9,minn=2e9;


int main ()
{
	scanf ("%d",&n);
	for (int i=1;i<=n;++i)
	{
		scanf ("%lld",&a[i]);
		if (a[i]>maxn)
		{
			maxn=a[i];
			pMax=i;
		}
		if (a[i]<minn)
		{
			minn=a[i];
			qMin=i;
		}
	}
	if (n==1)
	{
		printf ("%lld\n",a[1]);
		return 0;
	}
	if (pMax==qMin)  ++qMin;
	for (int i=1;i<=n;++i)
	{
		if (i==pMax||i==qMin||!a[i])  continue;
		if (a[i]<0)  maxn-=a[i];
		else  minn-=a[i];
	}
	printf ("%lld\n",maxn-minn);
	return 0;
}
```

双倍经验：[CF1038D Slime](https://www.luogu.com.cn/problem/CF1038D)


---

## 作者：天南星魔芋 (赞：1)

水题？！

------------


可以轻易发现必须有一个数作减数，（没有减数就没法减，不减怎么合成一个）


然后发现合完后必定有一个数正负没有变。（设第一次减法得到 $A-B$，这个式子无论如何运算，$A,B$ 中总会有一个符号为正）


由于 $(A-B)-C=A-B-C$，$A-(B-C)=A-B+C$，所以其余数字正负都可以，因为要最大的，就取绝对值呗。

由于 $A$ 越大 $A-B$ 越大，$B$ 越小 $A-B$ 越大，所以 $A$ 选最大的，$B$ 选最小的。

刚好 $n\le3⋅10^5$ 懒省事我就 sort 了。

还有一个是 $n$ 为 $1$ 时要特判。

$code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,o[3020000],ans=0;
int abss(int x){
	return x<0? -x:x;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%lld",&o[i]);
	}
	if(n==1){
		cout<<o[1]<<endl;
		return 0;
	}
	sort(o+1,o+1+n);
	for(int i=2;i<n;i++){
		ans+=abss(o[i]);
	}
	ans+=o[n]-o[1];
	cout<<ans<<endl;
}
```

记得开 long long！

---

## 作者：Zxsoul (赞：1)

**前言**

先说明我的方法不是结论，可能也就我一个这样做的，只是一个贪心的念想，

（~~众所周知贪心无需证明，大佬可以在评论区大胆的证明我直接膜拜~~

**思路**

首先对于数 $n$ 我们可以操作 $n-1$ 次，换句话说就是可以有 $n-1$ 个负号供我们放在不定个数的一个或多个数上，

不难发现，一次操作都有两种选择

- 在一个没有操作过的数前面加 $-$ 号

- 在曾经操作过即某一次 $a-b$ （$a,b$ 不一定是一个数） 前加 $-$

那么问题就简单多了，有**负数**直接加负号，剩下的负号全部只放在非负数中最小那一个上即可，即使是加上去以后是负数，答案也不会变劣

**注/** 代码没写`read`，（~~反作弊~~

```c
#include <cmath>
#include <cstdio>
#include <iostream>
#define int long long
using namespace std;
const int B = 1e6+10;
int n,a[B],sum;
main()
{
	n=read();
	int s=n-1,flag=0;
	for (int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+1+n);
	int js=0;
	for (int i=1;i<=n;i++)
	{
		if (a[i]<0 && s>0) {a[i]=-a[i],s--;sum+=a[i];js=1;}
		else if (s==0) {flag=i;break;} 
		else if (a[i]>=0) {flag=i;break;}
	}
	int cnt=0;
	if (js==0)
	{
		if (s!=0) sum-=a[flag];
		else sum+=a[flag];
		for (int i=flag+1;i<=n;i++) sum+=a[i];	
	}
	else {for (int i=flag;i<=n;i++) sum+=a[i];}
	printf("%lld",sum);
}
```

---

## 作者：StarryWander (赞：0)

**本题仅需找规律即可。**

1.对于序列中只有一个数字：

**输出即可。**

2.对于序列中只有两个数字：

#### 输出 $\max(a-b,b-a)$ ~~（很好理解，无需解释）~~。

3.对于 $n\geqslant 2$ 的情况：

 $\bullet$ 序列中有**正，负或 0 都有**：
	 
$-3，-2 ,-1 ,0 , 1 ,2 ,3$

这时我们只需要将 $-1$ 减去 $1$ 和 $2$，得到一个正数和若干个负数，这时，我们可以将剩下唯一一个正数减去所有剩下的负数。得到的结果为 $12$。

因此，我们可以得出结论：$ans=$ **所有数的绝对值**。

 $\bullet$ 序列中**全是**正数或负数：
 
 以 $-1，-2，-3，-4，-5，-6$ 为例。
 
 第一步，我们需要挑出两个数字，使它们的差值变成一个正数，因此，我们可以挑选出**绝对值最小**的数做为变成正数的代价，所以我们选取-1。而另外一个数可以随便选。
 
 接下来就变成了第一种情况（序列有正有负），这时我们就可以轻松求出答案了！
 
##  code：
 ```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int main(){
	int n=read(),mn=1e9+10;
	ll sum=0;
	if(n==1){//只有一个数
		cout<<read();
		return 0;
	}
	else if(n==2){//只有两个数
		int a=read(),b=read();
		cout<<max(a-b,b-a);
		return 0;
	}
	bool f=1,z=1;//用来判断是否全是正或负
	for(int i=1;i<=n;i++){
		int x=read();
		if(x>0) f=0;
		if(x<0) z=0;
		mn=min(mn,abs(x));//找出最小的绝对值，备用
		sum+=abs(x);//求出所有数的绝对值
	}
	if(!f&&!z) cout<<sum;//如果正负都有，直接输出绝对值
	else cout<<sum-2*mn;//如果全是正或负，减去2倍最小的绝对值
	return 0;
}

```


---

## 作者：Spouter_27 (赞：0)

分为三种情况（忽略了对结果没影响的零，记正整数个数为$f$）：
- $f=0$，则根据贪心的策略，用最大的负整数依次减去其他的整数，所得的结果为$\sum^n_{i=1}|a_i|+2*max(a)$

- $f=n$：用最小的正整数减去其他$n-2$的整数最后留一个数减去这个数，所得的结果即为$\sum^n_{i=1}a_i-2*min(a)$

- $0<f<n$：先任意选个负整数减去$f-1$正整数，留任意一个正整数减去这个数，最后减去其他的负整数即可。

注意特判$n=1$的情况

时间复杂度$O(n)$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long a[3000001],sum,m;//注意数据范围
int f;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]>=0)
			f++;
   }
	if(n==1)
	{
		cout<<a[1];
		return 0;
	}
	if(f==0)
	{
		m=-1e11;
		for(int i=1;i<=n;i++)
		{
			if(a[i]>=m)	m=a[i];
			sum-=a[i];
		}
		sum+=2*m;//a[i]是负数，注意符号
	}
	 if(f<n&&f>0)
	 	for(int i=1;i<=n;i++)
	 		sum+=abs(a[i]);
	 if(f==n)
	 {
	 	m=1e11;
		for(int i=1;i<=n;i++)
		{
			if(a[i]<m)	m=a[i];
			sum+=a[i];
		}
		sum-=2*m;
	 }
	 cout<<sum;
 } 
```


---

## 作者：Allanljx (赞：0)

## 题意
你有一个长度为 $n$ 的序列 $a$ ，你每次可以取出两个数 $a$ 和 $b$ ，并把 $a-b$ 添加到序列中。重复操作直到序列中只剩下一个数，你需要求出这个数的最大值。
## 思路
首先，看数据范围，发现 $Subtask$  $1$ $(15 pts)$：保证 $n≤3$ 。那么可以先特判一下 $n≤3$ 的情况下的答案。
```cpp
sort(a+1,a+1+n);
if(n==1)//特判
{
	cout<<a[1];
	return 0;
}
if(n==2)//特判
{
	cout<<a[2]-a[1];
	return 0;
}
if(n==3)//特判
{
	cout<<max(a[2]+a[3]-a[1],max(a[2]+a[1]-a[3],max(a[3]+a[1]-a[2],a[3]-a[2]-a[1])));
	return 0;
}
```

------------

然后看第二个数据范围 $Subtask$  $2$ $(30 pts)$：保证 $n$ 为正数。应让剩下的数最大，所以用 $sum$ 记录最小的数减去除了最大的数之外的所有的数，再用最大的数减去这个负数，就可以求到最大值。
```cpp
if(f==-1)
{
	sum=a[1];
	for(int i=2;i<n;i++)//用sum记录最小的数减去所有的除了a[n]的数
	{
		sum-=a[i];
	}
	cout<<a[n]-sum<<endl;//用a[n]减去sum
	return 0;
}
```

------------

接下来处理负数时需要用 `sort` 排序一下然后再找最后一个负数出现的位置
```cpp
sort(a+1,a+1+n);
int sum=0,f=-1;//f记录最后一个负数出现的位置
for(int i=1;i<=n;i++)
{
	if(a[i]<0)
	{
		f=i;
	}		
   	else break;
}
```

------------

有一种情况就是全是负数，这样的话就要用最大的数减去所有其他的负数。
```cpp
if(f==n)//都是负数
{
	sum=a[n];
	for(int i=1;i<n;i++)
	{
		sum-=a[i];
	}
	cout<<sum<<endl;
	return 0;
}
```

------------

最后就要处理既包含负数也包含负数的情况，发现：用最小的负数减去所有的除了最大的数的正数，再用最大的数减去所有的负数即可得到最大值。也就是说将所有的正数加起来再减去所有的负数
```cpp
for(int i=1;i<=f;i++)//减去所有负数
{
	sum-=a[i];
}
for(int i=f+1;i<=n;i++)//加上所有正数
{
	sum+=a[i];
}
cout<<sum<<endl;
```
## 完整代码
```cpp
#include<bits/stdc++.h>
#define int long long //不开 long long 见祖宗 
using namespace std;
int a[300005]; 
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+1+n);//排序 
	if(n==1)//特判 
	{
		cout<<a[1];
		return 0;
	}
	if(n==2)//特判 
	{
		cout<<a[2]-a[1];
		return 0;
	}
	if(n==3)//特判 
	{
		cout<<max(a[2]+a[3]-a[1],max(a[2]+a[1]-a[3],max(a[3]+a[1]-a[2],a[3]-a[2]-a[1])));
		return 0;
	}
	int sum=0,f=-1;
	for(int i=1;i<=n;i++)//寻找最后一个负数出现的位置 
	{
		if(a[i]<0)
		{
			f=i;
		}
		else break;
	}
	if(f==-1)//没有负数 
	{
		sum=a[1];
		for(int i=2;i<n;i++)
		{
			sum-=a[i];
		}
		cout<<a[n]-sum<<endl;
		return 0;
	}
	if(f==n)//全是负数 
	{
		sum=a[n];
		for(int i=1;i<n;i++)
		{
			sum-=a[i];
		}
		cout<<sum<<endl;
		return 0;
	}
	//有正有负 
	for(int i=1;i<=f;i++)
	{
		sum-=a[i];
	}
	for(int i=f+1;i<=n;i++)
	{
		sum+=a[i];
	}
	cout<<sum<<endl;
    return 0;
}
```


---

## 作者：Terraria (赞：0)

## 题目大意

给出 $n$ 个数，每次可以取出两个数 $a,b$，并将 $a-b$ 插入这个数列中。要求最后的一个数尽量大。

## 思路

注：以下内容为了方便，将**负数**定义为小于等于 $0$ 的数。

1. 如果数列中同时有正数、负数：

不妨设有 $k$ 个正数。

很明显，我们可以构造一种方案，选择一个负数减去 $k-1$ 个正数，再用那唯一一个正数减去其余的所有数，最终的答案即为 $\sum_{i=1}^{n}|a_i|$。

2. 如果数列中只有正数：

由于每次插入的是 $a-b$，所以我们应该尽量在数列中构造出负数，每次尽量让负数小，直到最后一个数之后再减去前面所得到的正数。

换句话说，我们可以先排序（从小到大），然后依次用第 $i$ 项减去第 $i+1$ 项（$1 \leq i < n$），用 $a_n$ 减去前面得到的负数。

3. 如果数列中只有负数：

那么我们可以用最大的负数减去其余的所有数，~~不难~~证得这种方案取得的值最大。

接下来就是代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans,sum;
int a[1000009];
bool f0,f1;
signed main(){
	cin>>n;
	if(n==1){
		int k;
		cin>>k;
		cout<<k;
		return 0;
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=abs(a[i]);
		if(a[i]>0) f1=true;
		if(a[i]<=0) f0=true;
	}
	if(f1&&f0){
		cout<<sum<<endl;
		return 0;
	}
	if(f1&&!f0){//如果没有负数
		sort(a+1,a+n+1);
		int ans=a[1];
		for(int i=2;i<n;i++) ans=(ans-a[i]);
		cout<<abs(a[n]-ans);
		return 0;
	}
	if(!f1&&f0){//如果全是负数
		sort(a+1,a+n+1);
		ans=a[n];
		for(int i=1;i<n;i++) ans-=a[i];
		cout<<ans;
	}
}
```


---

## 作者：zmza (赞：0)

思路：分类讨论。

第一步：将数列排序。

第二部：分类讨论：

1. 全是正数。答案为除第一个数外所有的数相加再减去第一个数。
2. 全是负数。答案为除第一个数减去其他所有的数。
3. 有正数和负数。大概就是将正数的最大值算出来，再减去每一个负数。

时间复杂度为$O(n)$

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read()
{
	int i = 0, f = 1;
	char ch;
	for(ch = getchar(); (ch < '0' || ch > '9') && ch != '-'; ch = getchar());
	if(ch == '-')
	{
		f = -1;
		ch = getchar();
	}
	for(; ch >= '0' && ch <= '9'; ch = getchar())
	{
		i = (i << 3) + (i << 1) + (ch ^ 48);
	}
	return i * f;
}
void write(int a,char b = ' ')
{
	if(a < 0)
	{
		putchar('-');
		a = -a;
	}
	if(a == 0)
	{
		putchar('0');
		putchar(b);
		return;
	}
	int sta[100] = {}, cnt = 0;
	while(a)
	{
		cnt++;
		sta[cnt] = a % 10;
		a /= 10;
	}
	while(cnt)
	{
		putchar(sta[cnt] + '0');
		cnt--;
	}
	putchar(b);
}
int a[300005];
signed main()
{
	int n = read();
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	if(n <= 2)//特判。如果只有一个或两个数时，可以直接输出。
	{
		if(n == 1)printf("%lld",a[1]);
		else printf("%lld",max(a[2],a[1]) - min(a[2],a[1]));
	}
	else
	{
		sort(a + 1, a + 1 + n);//排序。
		int kaitou = 0;
		while(a[++kaitou] < 0);//kaitou为正数的开头。
		int ans = 0;
		if (kaitou >= 2)
		{
			for(int i = kaitou; i <= n; i++)ans += a[i];
			if(kaitou >= 3)
			{
				if(kaitou <= n)
				{
					for(int i = 1; i < kaitou; i++)
						ans -= a[i];
				}
				else
				{
					ans += a[kaitou - 1];
					for(int i = 1; i < kaitou - 1; i++)
						ans -= a[i];
				}
			}
			else ans -= a[1];
			printf("%lld", ans);
		}
		else
		{
			ans = a[1];
			for(int i = 2; i < n; i++)ans -= a[i];
			printf("%lld", a[n] - ans);
		}
	}
	return 0;
}
```

---

