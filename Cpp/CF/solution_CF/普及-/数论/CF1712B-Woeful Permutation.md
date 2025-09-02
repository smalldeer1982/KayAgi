# Woeful Permutation

## 题目描述

I wonder, does the falling rain



Forever yearn for it's disdain?

Effluvium of the Mind



You are given a positive integer $ n $ .

Find any permutation $ p $ of length $ n $ such that the sum $ \operatorname{lcm}(1,p_1) + \operatorname{lcm}(2, p_2) + \ldots + \operatorname{lcm}(n, p_n) $ is as large as possible.

Here $ \operatorname{lcm}(x, y) $ denotes the [least common multiple (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple) of integers $ x $ and $ y $ .

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

For $ n = 1 $ , there is only one permutation, so the answer is $ [1] $ .

For $ n = 2 $ , there are two permutations:

- $ [1, 2] $ — the sum is $ \operatorname{lcm}(1,1) + \operatorname{lcm}(2, 2) = 1 + 2 = 3 $ .
- $ [2, 1] $ — the sum is $ \operatorname{lcm}(1,2) + \operatorname{lcm}(2, 1) = 2 + 2 = 4 $ .

## 样例 #1

### 输入

```
2
1
2```

### 输出

```
1 
2 1```

# 题解

## 作者：Dregen_Yor (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/CF1712B)。

# 题目简介

- 给定一个正整数 $n$，构造一个数列 $p$，使 $1$ 到 $n$ 中每一个数都出现且只出现 $1$ 次。

- 求最大的 $\sum\limits_{i=1}^n\operatorname{lcm}(i, p_i)$，并输出取得最大值时的数列。

# 思路

基础知识：$\operatorname{lcm}(a,b)=\dfrac{a\times b}{\operatorname{gcd}(a,b)}$。

$\operatorname{gcd}(a,a+1)=1$。

如果想让结果尽可能的大，需要让分母尽可能的小，分子尽可能的大。根据上面两个知识，我们可以得到相邻两项的 LCM 即为他们的乘积，根据贪心的思想，我们从后往前遍历，将相邻两项的位置互换，这样每次都会使相对较大的两个数相乘，使最终的结果最大，其中如果 $n$ 是奇数，$1$ 的位置不变即可。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n;
int main() {
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		if(n&1){
			putchar('1');
			putchar(' ');
			for(int i=2;i<=n;i+=2){
				printf("%d %d ",i+1,i);
			}
			putchar('\n');
		}
		else{
			for(int i=1;i<=n;i+=2){
				printf("%d %d ",i+1,i);
			}
			putchar('\n');
		}
	}
	return 0;
} 
```


---

## 作者：lilong (赞：2)

### 题意
构造一个 $n$ 的排列 $p$，使得 $ \sum\limits_{i=1}^n \operatorname{lcm}(i,p_i)$ 最大。

### 分析

首先要知道，$\operatorname{lcm}$ 是求两数的最小公倍数。因此，我们把思考方向引向公约数与公倍数。先回顾一下这条等式，对于任意的正整数 $m$ 和 $n$ 都有

$$\gcd(m,n) \times \operatorname{lcm}(m,n)=m \times n$$

移项得

$$\operatorname{lcm}(m,n)= \dfrac {m \times n}{\gcd(m,n)}$$

既然要使等式的左边尽可能大，那么右边的分母自然越小越好（最小为 $1$）。存在一种情况，使得 $\gcd(m,n)=1$，即我们常说的**互质**。回顾一下互质的定义：若 $m$ 和 $n$ 为两个相邻的正整数，则有 $\gcd(m,n)=1$。因此我们就要使题目中的 $i$ 和 $p_i$ 互质，使得分母变为 $1$（最小的数）。

那么这题做法就很显然了：设 $i$ 为奇数，则 $i+1$ 为偶数，令 $p_i=i+1$，$p_{i+1}=i$，则 $\gcd(i,p_i)=1$，$\gcd(i+1,p_{i+1})=1$，满足条件。特别地，当 $n$ 为奇数时，我们直接令 $p_1=1$，其余情况从 $2$ 开始，也满足条件，避免了剩下一个数的情况。

代码见下：
```
#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		if(n&1)
		{
			cout<<1<<' ';
			for(int i=2;i<=n;i++)
				if(i&1^1)//等价于 i%2==0
					cout<<i+1<<' ';
				else
					cout<<i-1<<' ';
		}
		else
		{
			for(int i=1;i<=n;i++)
				if(i&1)
					cout<<i+1<<' ';
				else
					cout<<i-1<<' ';
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：RAVE_LOVEo_O (赞：1)

一道构造题，花了我整整 $20$ 分钟才对

接下来讲一下思路：

为了求 $i,p$ 的最小公倍数，大家应该知道，什么样的情况下两个数的最小公倍数最大。就是 $i,p$ 互质的情况下，因为它们两个如果互质的话，最小公倍数就是它们的乘积.当然了，相邻的两个自然数互质（当然不包括 $0$ ）。~~小学知识~~

接下来开始构造，我们考虑两种情况：

1. $n$ 是偶数，我们可以把这个序列分成 $\dfrac{n}{2}$ 组，每组两个数，为了使它们互质，输出的时候把这两个数的调换一下就行了。这样能够使每个 $i,p$ 都互质
1. $n$ 是奇数，这时候，我们会发现会多出一个数，可以把这个序列转化成 $1$ 和一个长度为 $n-1$ 的序列，这样就比较好做了

上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,i,n;//定义变量
int main()
{
   cin>>t;
   while(t--)
   {
      cin>>n;//输入
      if(n%2){//如果是奇数
         cout<<"1 ";//先输出 1
         for(i=3;i<=n;i+=2)cout<<i<<' '<<i-1<<' ';//把剩下的当作偶数序列去做
      }
      else for(i=2;i<=n;i+=2)cout<<i<<' '<<i-1<<' ';// n 是偶数很好处理
      puts("");//快速换行
   }
   return 0;
}
```


---

## 作者：Epi4any (赞：1)

#### 构造题
构造思路：**贪心**

不难发现，如果我们想让这些最小公倍数的和最大，我们就需要尽量让原数列和新数列对应位置上的数尽量互质。

经过枚举手推 $n$ 分别为 $1,2,3,4,5$ 的情况，我们可以找到一个规律：把 $n$ 和 $n-1$ 交换，把 $n-2$ 和 $n-3$ 交换等等，依次类推**每次交换最大的两个数，直到没有数可以交换或者剩下一个 $1$**。然后生成的这个数列就是我们要求的最佳序列。

代码：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

int t, n;
int a[100005];

int main() {
	t = read();
	while (t--) {
		n = read();
		for (int i = 1; i <= n; i++) a[i] = i;
		for (int i = n; i >= 2; i -= 2) swap(a[i], a[i - 1]);
		for (int i = 1; i <= n; i++) cout << a[i] << " ";
		cout << endl;
	}
	return 0;
}
//结尾警告：理解思路，杜绝抄袭
```

---

## 作者：BotDand (赞：1)

# $\text{Problems}$

构造一个长度为 $n$ 的数列 $a$，满足对于 $1\le i\le n$ 有 $1\le a_{i}\le n$ 且任意两个数不相等。

求这个数列使得 $\sum_{i=1}^{k}\text{lcm}(i,a_{i})$ 最大。

# $\text{Answer}$

不难想到使 $\sum_{i=1}^{k}\text{lcm}(i,a_{i})$ 最大，就要满足对于 $1\le i \le n$ 都有 $\text{lcm}(i,a_{i})=i\times a_{i}$。

又可以考虑到对于任意 $x$ 都有 $\text{lcm}(x,x\pm 1)=x\times (x\pm 1)$。

对于一个 $i$，它所对应的 $a_{i}$ 可以是 $i\pm 1$。

因为 $\text{lcm}(1,1)=1$，所以在 $n$ 为奇数时，将 $a_{1}$ 设为 $1$，其余 $a_{2}$ 到 $a_{n}$ 分别设为 $i\pm 1$。

所以有如下构造：

如果 $n$ 是偶数，则构造排列 $2,1,4,3\dots n,n-1$。

如果 $n$ 是奇数，则构造排列 $1,3,2,5,4\dots n,n-1$。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
void work()
{
    cin>>n;
    if(n%2==1)
    {
        cout<<"1 ";
        for(int i=2;i<=n;i+=2) cout<<i+1<<" "<<i<<" ";
    }
    else
    {
        for(int i=1;i<=n;i+=2) cout<<i+1<<" "<<i<<" ";
    }
    puts("");
}
int main()
{
    cin>>t;
    while(t--) work();
    return 0;
}
```


---

## 作者：zfx_VeXl6 (赞：1)

### 题目大意

多组数据。

每组数据给定一个整数 $n$ $(1\le n\le10^5)$，求一个 $1$ 到 $n$ 的排列 $p$，使 $\sum\limits_{i=1}^n\mathrm{lcm}(i,p_i)$ 最大。

### 题解

对 $n$ 进行分类讨论。

当 $n\bmod 2=1$ 时，$p_1=1$，$p_i=\begin{cases}i+1&i\bmod2=0\\i-1&i\bmod2=1\end{cases}$，

当 $n\bmod 2=0$ 时，$p_i=\begin{cases}i+1&i\bmod2=1\\i-1&i\bmod2=0\end{cases}$，

可以证明以上结论正确。

### 代码
```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int t,n;
    int main()
    {
        scanf("%d",&t);
        while(t--)
        {
            scanf("%d",&n);
            if(n&1)
            {
                cout<<1<<' ';
                for(int i=2;i<=n;i++)
                    if(i&1)
                        cout<<i-1<<' ';
                    else
                        cout<<i+1<<' ';
            }
            else
                for(int i=1;i<=n;i++)
                    if(i&1)
                        cout<<i+1<<' ';
                    else
                        cout<<i-1<<' ';
            cout<<'\n';
        }
        return 0;
    }
```

---

## 作者：YYHDoggy (赞：1)

## 题意简述

给定正整数 $n$，求一个 $1$ 到 $n$ 的排列，使得 $\sum_{i=1}^n{\operatorname{lcm}(i,p_i)}$ 最大。

## Solution

众所周知，$\operatorname{lcm}(x,y)=\dfrac{ab}{\gcd (x,y)}$。

为了使单个 $\operatorname{lcm}$ 值最大，主要有两种方向：

- 减小 $\gcd$ 的值（极端情况则是使 $(x,y)$ 互素）
- 增大 $a \cdot b$ 的值

从前者角度思考，不难想到相邻两个数一定是互素的。

> 还是补充一下解释吧，明白的同学略过即可     
> （这里不采用严格证明，仅为了方便理解）    
> 辗转相除法的公式是 $\gcd(x,y) = \gcd(y,x \bmod y)$     
> 可得 $\gcd(x+1,x) = \gcd (1,x) = 1$

如果要构造一个第 $i$ 个数均与 $i$ 互素的排列的话，可能会想到把所有数字的位置都向后位移一个单位，比如：

```
1,2,3 -> 2,3,1
1,2,3,4 -> 4,1,2,3
```

但是这样得出的解并不是最优的，因为没有考虑 $a \cdot b$ 可以最大化。

从这种排列方式来看，最后一个数对答案的贡献仅为 $n$，而第一个数分配到了 $n$，对答案的贡献也仅为 $n$。

如果要使最大的两个数乘积最大，应该将最后两个数分别设为 $n$ 和 $n-1$。以此类推，每两个数进行交换显然最优，同时也保证了除 $1$ 以外所有元素与 $i$ 均互素。

因此，应该两两交换元素，在 $n$ 为奇数时忽略 $1$ 即可。仅从首末项考虑，在 $n$ 为奇数的情况下，将首项设为 $1$ 相比设为 $n$ 损失的贡献为 $n-1$，而从末项上多出的贡献为 $n(n-1)-n = (n-1)^2$，而其余项的贡献也没有变得更劣，显然这样做更优。

下面是 AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t,n;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        if(n%2==1){
            //首项设为1，后面相邻项两两交换
            printf("1 ");
            for(int i=2;i<=n;i+=2){
                printf("%d %d ",i+1,i);
            }
        }
        else{
            //直接两两交换即可
            for(int i=1;i<=n;i+=2){
                printf("%d %d ",i+1,i);
            }
        }
        printf("\n");
    }
return 0;}
```

---

## 作者：GI录像机 (赞：0)

## 思路：

因为要求最小公倍数，所以我们想到要尽可能选两个互质的数配对，这样能最大化收益。

我们配对时应该让大数和大数配对，小数和小数配对，证明如下：

当 $a<b<c<d$ 时，
显然 $a(c - b) < d(c - b)$

去括号得 $ab - ac > cd - bd$

所以 $ab + cd > ac + bd$

其它几种配对方式可以用同样的方法证明是不如此种方式优的。

运用上面想到的两个结论，就能得出构造方案：

若 $n$ 为奇数，排列应为 $1, 3, 2, 5, 4\cdots$

若 $n$ 为偶数，排列应为 $2, 1, 4, 3, 5\cdots$

## 代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 2e5 + 10, MOD = 1e9 + 7, INF = 0x3f3f3f3f;
int t = read(), n;
signed main() {
	while (t--) {
		n = read();
		if(n & 1){
			write(1);
			putchar(' ');
		}
		for (int i = -11 + 4 - 5 + 14; i <= n; i += -11 + 4 - 5 + 14) {
			if (n & 1){
				write(i + 1);
				putchar(' ');
				write(i);
				putchar(' ');
			} else {
				write(i);
				putchar(' ');
				write(i - 1);
				putchar(' ');
			}
		}
		putchar('\n');
	}
	return 0;
}

```


---

## 作者：封禁用户 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1712B)
## [博客查看食用更佳！](https://www.luogu.com.cn/blog/673601/)

# 本题思路
~~通过打表~~ 我们可以发现，构造一个序列使得：

- 如果 $n$ 为偶数，则序列中当 $i$ 为奇数时，$a_i=2 \times i$；当 $i$ 为偶数时，$a_i=a_{i-1}-1$。这样构造能使序列值最大，最后值为 $1 \times 2+3 \times 4 \cdots (n-1) \times n$。

- 如果 $n$ 为奇数，类似地，将 $a_1$ 设为 $1$，以后当 $i$ 为奇数时，$a_i=(i-1)$；当 $i$ 为偶数时，$a_i=a_{i+1}+1$。这样构造能使序列值最大，最后值为 $1+2 \times 3+4 \times 5 \cdots (n-1) \times n$。

## 推导过程
我们希望最大，于是我们尽量要使 $\gcd(a_i,i)=1$。

考虑到这是一个排列，我们容易想到 $\gcd(i+1,i)=1,\gcd(i,i+1)=1$（注意这两个柿子的含义不一样，一个指第 $i$ 个位置的取值，一个是第 $i+1$ 个位置的取值），所以就想到了上述构造（~~当然我比赛时是直接暴力打表找规律的~~）。

## 代码
你们期待的 $\text{AC}$ 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=110;
inline int read(){
	int x=0;
	short f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline int lcm(int x,int y){
	return max(x,y)/__gcd(x,y)*min(x,y);
}
int t,n,k;
int ans[N];
signed main(){
	t=read();
	while(t--){
		n=read();
		if(n%2==0){
			for(int i=1;i<=n;i++){
				if(i&1)cout<<i+1<<" ";
				else cout<<i-1<<" ";
			}
			cout<<endl;
		}else{
			cout<<1<<" ";
			for(int i=2;i<=n;i++){
				if(i&1)cout<<i-1<<" ";
				else cout<<i+1<<" ";
			}
			cout<<endl;
		}//构造
	}
	return 0;
}
```


---

## 作者：sgl654321 (赞：0)

### 题目大意
- 给定一个整数 $n$，要求你构造一个长度为 $n$ 的排列 $a$，使得 $\operatorname{lcm}(1,a_1)+\operatorname{lcm}(2,a_2)+\cdots+\operatorname{lcm}(n,a_n)$ 的值最大。
- 其中 $\operatorname{lcm}(x,y)$ 表示 $x$ 和 $y$ 的最小公倍数。

### 解题思路
本题的重点实际上就只有一句话：**相邻的两个正整数一定互质**。对于两个正整数 $n$ 和 $n-1$，他们的最小公倍数就是 $n\times (n-1)$。

因为一个长度为 $n$ 的排列需要出现 $[1,n]$ 中所有自然数各一次，所以我们容易想到如下构造方法：

- 若 $n$ 为偶数，则让排列 $a$ 为 $[2,1,4,3,6,5,\cdots,n,n-1]$。就是把相邻的两个数交换。

- 若 $n$ 为奇数，则让排列 $a$ 为 $[1,3,2,5,4,7,6,\cdots,n,n-1]$。就是除去 $a_1$，把相邻的两个数交换。

为什么这样可以使 $\operatorname{lcm}(1,a_1)+\operatorname{lcm}(2,a_2)+\cdots+\operatorname{lcm}(n,a_n)$ 的值最大呢？因为我们这样做可以使所有的 $a_i$ 和 $i$ 互质，而且最后的 $\operatorname{lcm}(a_{n-1},n-1)$ 和 $\operatorname{lcm}(a_n,n)$ 的值都是 $n\times (n-1)$，非常大。可以在证明，这样的构造方法可以使原式的值最大。

知道了构造方法之后，这题就迎刃而解啦！

### 参考代码
注意本题有多组数据。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,k,a[10000],ans;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		if(n%2==0){
			for(int i=1;i<=n;i++)
				if(i%2==1)cout<<i+1<<" ";
				else cout<<i-1<<" ";
			cout<<endl;
			continue;
		} 
		cout<<1<<" ";
		for(int i=2;i<=n;i++)
			if(i%2==0)cout<<i+1<<" ";
			else cout<<i-1<<" ";
		cout<<endl;
	} 
	return 0;
} 
```


---

## 作者：Jeremiahy (赞：0)

### 题意

构造一个长度为 $n$ 的排列 $p$，使得 $ \operatorname{lcm}(1,p_1) + \operatorname{lcm}(2, p_2) + \ldots + \operatorname{lcm}(n, p_n) $ 最大。

## 分析

首先有一个结论：相邻的两个数互质。而两个互质的数的最小公倍数自然是最大的了。所以我们想到交换相邻项，使得它们互质。

具体实现上，当长度 $n$ 为偶数时，就交换 $1$ 和 $2$，$3$ 和 $4$，以此类推；当长度 $n$ 为奇数时，$1$ 不变，交换 $2$ 和 $3$，$4$ 和 $5$，以此类推。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
signed main() {
	cin >> t;
	while (t--) {
		cin >> n;
		if (n & 1) {//n 为奇数
			cout << 1 << ' ';// 1
			for (register int i = 2; i <= n; i += 2) // 交换
				cout << i + 1 << ' ' << i << ' ';
		}
		else
			for (register int i = 1; i <= n; i += 2)
				cout << i + 1 << ' ' << i << ' ';
		puts("");
	}
	return 0;
}
```


---

## 作者：ztlh (赞：0)

**题意**：求一个长度为 $n$ 的排列 $p$ 使得 $\operatorname{lcm}(1,p_1) +\operatorname{lcm}(2,p_2) + ... +\operatorname{lcm}(n,p_n)$ 最大。

**我的做法**：考虑 $\gcd(x,x+1) = 1$，可知 $\operatorname{lcm}(x,x+1) = x \times (x+1)$。

根据排序不等式（$\text{正序} \leq \text{乱序} \leq \text{逆序}$），易证以下方法最优。

按 $n$ 的奇偶性讨论：

- 若 $n$ 为奇数，则令 $p_1 = 1$，$p_i = i \otimes 1$（其中 $\otimes$ 为异或）。

- 若 $n$ 为偶数，则令 $p_i = i + 1$（$i$ 为奇数）， $p_i = i - 1$（$i$ 为偶数）

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		if(n&1){
			printf("1");
			for(int i=2;i<=n;i++)
				printf(" %d",i^1);
			printf("\n");
		}
		else{
			for(int i=1;i<=n;i++)
				printf("%d ",(i&1?(i+1):(i-1)));
			printf("\n");
		}
	}
	return 0;
} 
```

---

## 作者：happy_dengziyue (赞：0)

### 1 视频题解

![](bilibili:BV1DS4y1s7yL)

### 2 思路

我们可以发现，$\operatorname{lcm}(i,p_i)$ 最好为 $i\times p_i$。我们就可以尽力争取这个目标。

我们可以构建一个图，连的边都是 $i\to p_i$。可以发现，如果满足上述条件，除了 $p_1$ 可能等于 $1$ 以外，其他的环都至少包含 $2$ 个点。

对于一个环，设这个环有 $k$ 个点，依次为 $x_1,x_2,...x_k$。这个环能产生的权值就是 $\sum_{i=1}^{k-1}(x_i\times x_{i+1})+x_k\times x_1$。设为 $w$。

并且我们可以发现，$(x_1^2+x_2^2+...+x_k^2)-w=\dfrac{\sum_{i=1}^{k-1}(x_i-x_{i+1})^2+(x_k-x_1)^2}{2}\ge\max_{i=1}^{k}(x_i)-\min_{i=1}^{k}(x_i)$。所以我们要最小化每个环的 $\max_{i=1}^{k}x_i-\min_{i=1}^{k}x_i$ 的和（设为 $s$）。

我们可以发现：

+ 当 $n$ 为奇数时：

    $s=\begin{cases}\dfrac{n-1}{2}(p_1=1)\\\dfrac{n+1}{2}(p_1>1)\end{cases}$，显然前者更优。

    那么我们就输出 $1,3,2,5,4,...,n,n-1$。

+ 当 $n$ 为偶数时：

    $s=\dfrac{n}{2}$ 是最优的。

    那么我们就输出 $2,1,4,3,...,n,n-1$。
    
事实上，这题的证明过程是非常复杂的。猜到规律就好了。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int t;
int n;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1712B_1.in","r",stdin);
	freopen("CF1712B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		if(n&1){
			printf("1 ");
			for(int i=2;i<=n;i+=2)printf("%d %d ",i+1,i);
		}
		else{
			for(int i=1;i<=n;i+=2)printf("%d %d ",i+1,i);
		}
		printf("\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/83727145)

By **dengziyue**

---

## 作者：Foofish (赞：0)

## 题意

找出最优的一个 $[1,n]$ 的全排列，使得 $\sum\limits_{i=1}^n\text{lcm}(i,a_i)$ 最大。

## 思路

考虑到对于相邻的两个数，他们互质。

并且显然将两个互质的更大的数放在一起，答案会更优。因为是乘积。根据排序不等式可以知道这一点。

这样的话我们去从高到低的交换两个相邻的数，如果是奇数个 $1$ 就剩下来。偶数个刚好满足。

```cpp
#include <bits/stdc++.h>
#define debug puts("I love Newhanser forever!!!!!");
template <typename T>inline void read(T& t){t=0; register char ch=getchar(); register int fflag=1;while(!('0'<=ch&&ch<='9')) {if(ch=='-') fflag=-1;ch=getchar();}while(('0'<=ch&&ch<='9')){t=t*10+ch-'0'; ch=getchar();} t*=fflag;}
template <typename T,typename... Args> inline void read(T& t, Args&... args) {read(t);read(args...);}
using namespace std;
const int N=100086, inf=0x3f3f3f3f;

int T=1,n,a[N];

int main(){
    read(T);
    while(T--){
        read(n);
        for(int i=1;i<=n;++i) a[i]=i;
        for(int i=n;i>=1+(n&1);i-=2)
            swap(a[i],a[i-1]);
        for(int i=1;i<=n;++i) cout<<a[i]<<' ';
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：BorisDimitri (赞：0)

## 题意
求一个长度为 $n$ 的排列 $a$，使得 $\operatorname{lcm}(1,a_1)+\operatorname{lcm}(2,a_2)+\cdots+\operatorname{lcm}(n,a_n)$ 最大。

## 思路
对于 $n$ 为奇数的情况，最后答案为 $1,3,2,5,4,7,6 \cdots,n,n-1$。

对于 $n$ 为奇数的情况，最后答案为 $2,1,4,3,6,5 \cdots ,n, n-1$。

**Proof**：
> 由于 $\operatorname{lcm}(x,y) = \frac{x \times y}{\gcd(x,y)}$，所以当 $x,y$ 互质的时候最优。
>
> 我们发现，一个数和最小(或大)的比它大(或者小)的且与它互质的数求 $\operatorname{lcm}$ 时，是最优的。
>
> 那为什么不去和更大的且与它互质的数求 $ \operatorname{lcm}$ 呢？
>
> 设原来的配对为 $\frac{x_1 \times y_1}{1} + \frac{x_2 \times y_2}{1} (x_1 \le y_1 \le x_2 \le y_2)$，交换成 $\frac{x_1 \times y_2}{1} + \frac{x_2 \times y_1}{1}$ 的话会导致答案偏小。


## Code
```cpp
const int N = 1e5 + 10;
int a[N];
void solve()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) a[i] = i;
	if(n % 2 == 1) for(int i=2;i<n;i+=2) swap(a[i],a[i+1]);
	if(n % 2 == 0) for(int i=1;i<=n;i+=2) swap(a[i],a[i+1]);
	
	for(int i=1;i<=n;i++) cout<<a[i]<<' ';
	cout<<endl;
}
```

---

