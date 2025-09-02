# [COCI 2016/2017 #7] UZASTOPNI

## 题目背景

**本题和 [P1147](https://www.luogu.com.cn/problem/P1147) 的区别仅在于连续自然数和的数据范围和输出格式。**

## 题目描述

求出所有的和为 $N$ 的长度 $\geqslant 2$ 的连续自然数段。

## 说明/提示

**【样例 1 解释】**

$10=1+2+3+4$，可以发现和为 $10$ 的满足要求的连续自然数段有且仅有一个。

**【数据范围】**

对于所有数据，$3\leqslant N\leqslant 10^{10}$。

**【题目来源】**

本题来源自 **_[COCI 2016-2017](https://hsin.hr/coci/archive/2016_2017/) [CONTEST 7](https://hsin.hr/coci/archive/2016_2017/contest7_tasks.pdf) T2 UZASTOPNI_**，按照原题数据配置，满分 $80$ 分。

由 [Eason_AC](https://www.luogu.com.cn/user/112917) 翻译整理提供。

## 样例 #1

### 输入

```
10```

### 输出

```
1 4```

## 样例 #2

### 输入

```
27```

### 输出

```
13 14
8 10
2 7```

# 题解

## 作者：Ginger_he (赞：4)

# 题目描述
求出所有的和为 $N$ 的长度 $\geqslant 2$ 的连续自然数段。
# 题解
设这一段的最小值为 $l$，最大值为 $r$。  
由等差数列求和公式有 $\dfrac{(l+r)(r-l+1)}{2}=N$。  
将 $2$ 乘到右边有 $(l+r)(r-l+1)=2N$。  
对 $2N$ 进行质因数分解，不妨假设 $2N=x\times y(x\geqslant y)$。  
因为 $l$ 和 $r$ 均为正整数，因此 $l+r\geqslant r-l+1$， 
$\begin{cases}l+r=x\\r-l=y-1\end{cases}$  
这时候只需要判断 $x$ 和 $y-1$ 是否相等以及奇偶性是否相同即可。  
时间复杂度 $\Theta(\sqrt{2N})$。  
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,x;
int main()
{
	scanf("%lld",&n);
	if(n==1)
		return 0;//特判
	m=sqrt(n<<=1);
	for(ll i=1;i<=m;i++)//根号枚举因数
	{
		if(n%i)
			continue;
		x=n/i;
		if((x%2)!=(i%2)&&x-i+1!=x+i-1)//符合条件
			printf("%lld %lld\n",x-i+1>>1,x+i-1>>1);
	}
	return 0;
}
```


---

## 作者：苏联小渣 (赞：2)

### 题目大意

求出所有的和为 $N$ 的长度 $\ge 2$ 的连续自然数段。

### 分析

数据范围 $10^{10}$，不可能一一枚举，考虑运用等差数列求和公式。

对于连续正整数 $[l,r]$，其和为

$$N=\frac{(l+r) \times (r-l+1)}{2}$$

化简，得

$$2N=(l+r) \times (r-l+1)$$

这样，我们就只需要枚举 $2N$ 的约数，并且解一个二元一次方程组。具体过程如下：

设 $2N$ 的两个约数为 $x,y$，则满足：

$$\begin{cases}
l+r=x\\

r-l+1=y
\end{cases}
$$

或

$$\begin{cases}
l+r=y\\

r-l+1=x
\end{cases}
$$

我们通过移项、相加等基本操作，即可求出该情况下满足条件的 $l,r$ 值。

**$\bigstar$注意点：**

1、由于求得的 $l,r$ 未必为**整数**，所以需要判断求得的 $l,r$ 值中的一个是否为整数（相加为整数，一个满足另一个一定满足）。我们可以利用以下方法判断是否为整数：

假设有一个数 $c$，为整数当且仅当 `floor(c) == ceil(c)`（向下取整和向上取整相等）

2、由上述方法求得的 $l,r$ 未必为**正数**，所以还要判断是否满足 `l>0 && r>0`；

3、为了避免出错，最后还需要**验算**，利用所求得的 $l,r$，**回代**求出和是否为 $N$。如果满足，就可以输出答案。

4、注意到上述方法求得的 $l,r$ 不一定满足 `l < r`，所以要先输出 `min(l, r)` 再输出 `max(l, r)`。

5、注意要开 `long long`。

6、降序排列，所以应从 $1$ 到 $\sqrt{2N}$ 枚举约数（积一定差大和大【基本不等式】）

总时间复杂度为 $O(\sqrt{2N})$，可以通过。

### Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, x, y;
signed main(){
	scanf ("%lld", &n);
	n *= 2;
	for (int i=2; i<=sqrt(n); i++){
		if (n % i == 0){
			x = i, y = n / i;
			//1
			y --;//移项 
			if (floor((x+y)/2) == ceil((x+y)/2)){
				int l = (x+y) / 2, r = x - l;//求解方程组 
				if (l > 0 && r > 0 && (l + r) * (max(l, r) - min(l, r) + 1) == n) printf ("%lld %lld\n", min(l, r), max(l, r));
			}
			//2
			x = n / i, y = i;
			y --;
			if (floor((x+y)/2) == ceil((x+y)/2)){
				int l = (x+y) / 2, r = x - l;
				if (l > 0 && r > 0 && (l + r) * (max(l, r) - min(l, r) + 1) == n) printf ("%lld %lld\n", min(l, r), max(l, r));
			}
		}
	}
	return 0;
}
```

---

## 作者：V1mnkE (赞：0)

# 分析
~~参考P1147题解即可~~ 本题与[P1147](https://www.luogu.com.cn/problem/P1147)的两点差距在于:

- 数据范围由 $ 2 \leq M \leq 2 \times 10^{6} $ 加大到了 $ 3 \leq M \leq 2 \times 10^{10} $ 。
- 输出顺序由升序改变成了降序。

了解了这些, 我们就可以开始写代码了。

假设 $ M $ 能过被分为连续的 $ i $ 个数的和，这时有两种情况；

① $ i $ 是偶数，此时 (最中间的两个数的和 $ \times i / 2 $ ) $ = M $ ，那么 $ M $ 对这两数的和取余等于 $ 0 $ ；

② $ i $ 是奇数，此时（最中间的数 $ \times i $）$ = M $，那么 $ M $ 对此数取余等于0。

__按以上方法，从 $ i = 2 $ 时开始递增。如果 $ n $ 可以被分为连续的 $ i $ 个数的和：__
 
①这 $ i $ 个数中的最小值不是自然数或者最大值大于 $ M $ （其实会同时出现啦）；此时跳出循环，因为i取更大值的时候依然会超出 $ [0,M] $ 的界限，

②这 $ i $ 个数都是 $ [0,M] $ 之间的自然数；此时将这 $ i $ 个数中的最小值和最大值输出(因为 $ i $ 枚举的是长度, 所以 $ i $ 越小时连续自然数段中的第一个数越大, 相当于自带降序)

# 代码
```cpp
#include<iostream>
#define int long long
using namespace std;

struct id{
	int x,y;
}ss;

signed main(){
	int i,n;
	cin>>n;
	for(i=2;;i++){
		if(i%2==0&&n%(n/i*2+1)==0){
			ss.x=n/i-i/2+1;
			ss.y=n/i+i/2;
			if(ss.x<=0||ss.y>=n)	break;
			cout<<ss.x<<" "<<ss.y<<endl;	
		}
		else if(i%2==1&&n%i==0){
			ss.x=n/i-i/2;
			ss.y=n/i+i/2;
			if(ss.x<=0||ss.y>=n)	break;
			cout<<ss.x<<" "<<ss.y<<endl;
		}
	}
    return 0;
}
```

---

## 作者：FLAMEs_ (赞：0)

一道和[P1147](https://www.luogu.com.cn/problem/P1147)差不多的题。

本题与P1147有两点差距：

1.P1147的数据范围是 $10 \le M \le 2\times10^{6}$ ，而本题数据范围是 $3 \le N \le 10^{10}$ ，故要用long long储存。 ~~（我用的__int128）~~

2.P1147要求**升序**输出，而本题要求**降序**输出。

了解了这些，我们可以开始写代码了。

~~我们只需要 [参考P1147题题解](https://www.luogu.com.cn/problem/solution/P1147) 即可。~~

我们已知的是这个等差数列的和。令该等差数列首项为 $X$ ,末项为 $Y$ 。

则该等差数列和 $tot$ 为：

$tot = \frac{(X+Y)\times(Y-X+1)}{2}$

整理移项，得：

$ 2 \times tot = (X+Y)\times(Y-X+1) $

将 $2*tot$ 分解成 $i$ , $j$ 。

观察等式，发现 $i$ , $j$ 需要为一奇一偶， $X$ , $Y$ 方为正整数。

又因为 $N$ 的分解长度 $len$ 需要 $ \ge 2$ ,所以我们还需要排除掉 $X=Y$ （即 $len=1$ ）的情况。

随后枚举 $i$ , $j$ 即可。

附上我的破代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int __int128
long long m;
int read(){int x=0,f=1;char c=getchar();while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();}while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}return x*f;}
void write(int x){if(x<0){x=-x,putchar(45);}if(x)write(x/10);else return;putchar(x%10+48);}
signed main()
{
    m=read();
    for(int i=2,j;i<=sqrt(2*m);i++)
    if(2*m%i==0&&(i+2*m/i)%2)
    {j=2*m/i;write((j-i+1)/2);cout<<" ";write((j+i-1)/2);printf("\n");}
    return 0;
}
```


---

