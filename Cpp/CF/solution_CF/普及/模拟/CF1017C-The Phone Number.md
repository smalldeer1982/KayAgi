# The Phone Number

## 题目描述

Mrs. Smith is trying to contact her husband, John Smith, but she forgot the secret phone number!

The only thing Mrs. Smith remembered was that any permutation of $ n $ can be a secret phone number. Only those permutations that minimize secret value might be the phone of her husband.

The sequence of $ n $ integers is called a permutation if it contains all integers from $ 1 $ to $ n $ exactly once.

The secret value of a phone number is defined as the sum of the length of the longest increasing subsequence (LIS) and length of the longest decreasing subsequence (LDS).

A subsequence $ a_{i_1}, a_{i_2}, \ldots, a_{i_k} $ where $ 1\leq i_1 < i_2 < \ldots < i_k\leq n $ is called increasing if $ a_{i_1} < a_{i_2} < a_{i_3} < \ldots < a_{i_k} $ . If $ a_{i_1} > a_{i_2} > a_{i_3} > \ldots > a_{i_k} $ , a subsequence is called decreasing. An increasing/decreasing subsequence is called longest if it has maximum length among all increasing/decreasing subsequences.

For example, if there is a permutation $ [6, 4, 1, 7, 2, 3, 5] $ , LIS of this permutation will be $ [1, 2, 3, 5] $ , so the length of LIS is equal to $ 4 $ . LDS can be $ [6, 4, 1] $ , $ [6, 4, 2] $ , or $ [6, 4, 3] $ , so the length of LDS is $ 3 $ .

Note, the lengths of LIS and LDS can be different.

So please help Mrs. Smith to find a permutation that gives a minimum sum of lengths of LIS and LDS.

## 说明/提示

In the first sample, you can build a permutation $ [3, 4, 1, 2] $ . LIS is $ [3, 4] $ (or $ [1, 2] $ ), so the length of LIS is equal to $ 2 $ . LDS can be ony of $ [3, 1] $ , $ [4, 2] $ , $ [3, 2] $ , or $ [4, 1] $ . The length of LDS is also equal to $ 2 $ . The sum is equal to $ 4 $ . Note that $ [3, 4, 1, 2] $ is not the only permutation that is valid.

In the second sample, you can build a permutation $ [2, 1] $ . LIS is $ [1] $ (or $ [2] $ ), so the length of LIS is equal to $ 1 $ . LDS is $ [2, 1] $ , so the length of LDS is equal to $ 2 $ . The sum is equal to $ 3 $ . Note that permutation $ [1, 2] $ is also valid.

## 样例 #1

### 输入

```
4
```

### 输出

```
3 4 1 2
```

## 样例 #2

### 输入

```
2
```

### 输出

```
2 1
```

# 题解

## 作者：FxorG (赞：7)

可以想到 这题最优应该是分成多个块 块内升序 块外降序

类似于

4 5 2 3 1 这种

那么 关键就是块长了

很显然设块长为 $x$ 则有 $ \frac{n}{x}$个LDS $x$个LIS

那么显然 $x$ 取 $\sqrt{n}$ 时 LIS+LDS最小

若取 $ \sqrt{n} +1$ 最好 

则  $ \sqrt{n}+1+ \frac{n}{ \sqrt{n}+1}$ 显然大于 $\sqrt{n}+ \frac{n}{\sqrt{n}}$ 

综上 块长取 $ \sqrt{n}$ 最优

代码较简单 

```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

int n,bl;

int main() {
	scanf("%d",&n);
	bl=sqrt(n);
	while(n>0) {
		for(int i=n-bl+1;i<=n;i++) {
			if(i>0) printf("%d ",i);
		}
		n-=bl;
	}
	return 0;
}
```

---

## 作者：皎月半洒花 (赞：3)

感觉这题就是十分的牛。

> 给定一个数 $n$ 。求构造一个长度为 $n$ 的排列，使之 $\rm LIS+LDS$ 最小。

一开始读题读成了最大值。然后随便画了画发现答案就是 $n+1$ emmm

然后读完了随便写了个奇怪的东西被轻松叉了，之后发现原来是个比较强的题。大概就是考虑 dilworth 定理，最长上升/下降子序列长度等于其反链的最多序列数。那么考虑如果是要算 LIS+LDS 之和的话，对于一个 LIS 的定长 $L$ ，根据 dilworth 定理必然会存在 $L$ 个反链，也就是 $L$ 个 DS 。于是可以知道最后有
$$
{\rm LIS+LDS}=\left\lceil \frac{n}{L}\right\rceil+L
$$
即为了使 $L$ 个 DS 的最大长度最小，所以要尽量分的平均一点。那么可以知道这个 $L$ 应该取 $\sqrt n$ 。

那么之后就变成了如何构造一个 LIS 为 $\sqrt n$，LDS 为 $\left\lceil\dfrac{n}{\sqrt n}\right\rceil$ 的串。不难知道可以分段构造。

```cpp
#include <cmath>
#include <cstdio>
#include <algorithm>

const int N = 300010 ;

int n, m ;
int ans[N] ;

int main(){
    scanf("%d", &n) ;
    m = std :: ceil(std :: sqrt(n)) ;
    /*
    if (n & 1){
        ans[(n >> 1) + 1] = n ;
        for (int i = 1 ; i <= n >> 1 ; ++ i) ans[i] = i ;
        for (int i = (n >> 1) + 2 ; i <= n ; ++ i) ans[i] = n - i + ((n >> 1) + 1) ;
    }
    else {
        for (int i = 1 ; i <= (n >> 1) ; ++ i) ans[i] = i ;
        for (int i = (n >> 1) + 1 ; i <= n ; ++ i) ans[i] = n - i + ((n >> 1) + 1) ;
    }
    for (int i = 1 ; i <= n >> 1 ; ++ i) res[i] = ans[i + (n >> 1)] ;
    for (int i = (n >> 1) + 1 ; i <= n ; ++ i) res[i] = ans[i - (n >> 1)] ;*/
    int p = 0, q, k = n ;
    for (int i = 1 ; i <= std :: ceil(1.0 * n / m) ; ++ i){
        q = p ; for (int j = 1 ; j <= m && p < n ; ++ j) ans[++ p] = k -- ;
        std :: reverse(ans + q + 1, ans + p + 1) ; // printf("%d %d %d\n", i, q + 1, p) ;
    }
    for (int i = 1 ; i <= n ; ++ i)
        printf("%d ", ans[i]) ; return 0 ;
}

```

# 

---

## 作者：agicy (赞：3)

# 题意

## 题目描述

给定$n$，求一个$1$~$n$的排列使得该排列的最长上升子序列长度与最长下降子序列长度之和最小。

翻译来自@AKEE 。

## 题面源代码

```
给定$n$，求一个$1$~$n$的排列使得该排列的最长上升子序列长度与最长下降子序列长度之和最小。
```

# 思路

我初看上来，摸不着头脑，但在经过暴力模拟后，得出了一部分数据。

```
n=1
ans=1
```

```
n=2
ans=2 1
```

```
n=3
ans=2 3 1
```

```
n=4
ans=3 4 2 1
```

```
n=5
ans=4 5 2 3 1
```

只看这$5$组数据，我得出了错误结论，但竟然过了$8$个点。

## [错误结论的评测记录](https://www.luogu.org/record/show?rid=9547610)

我不再使用手动模拟，而是使用**计算机**帮助我进行模拟，又得出了大量数据。（不得不说，**计算能力很重要**）

```
6
5 6 3 4 1 2

7
6 7 4 5 2 3 1

8
7 8 5 6 3 4 1 2

9
7 8 9 4 5 6 1 2 3

10
8 9 10 5 6 7 2 3 4 1

11
9 10 11 6 7 8 3 4 5 1 2

12
10 11 12 7 8 9 4 5 6 1 2 3

13
11 12 13 8 9 10 5 6 7 2 3 4 1

14
12 13 14 9 10 11 6 7 8 3 4 5 1 2

15
13 14 15 10 11 12 7 8 9 4 5 6 1 2 3
```

如果看到这$10$组数据，答案呼之欲出。

我们将对排列进行划分，例如：


- 当$n=4$时，结果为：$(\left\lceil\frac{4}{\left\lfloor\sqrt{4}\right\rfloor}\right\rceil=2)
$
```
3 4
1 2
```

- 当$n=8$时，结果为：$(\left\lceil\frac{8}{\left\lfloor\sqrt{8}\right\rfloor}\right\rceil=4)$

```
7 8
5 6
3 4
1 2
```

- 当$n=9$时，结果为：$(\left\lceil\frac{9}{\left\lfloor\sqrt{9}\right\rfloor}\right\rceil=3)$

```
7 8 9
4 5 6
1 2 3
```
- 当$n=14$时，结果为：$(\left\lceil\frac{14}{\left\lfloor\sqrt{14}\right\rfloor}\right\rceil=5)$

```
12 13 14
9 10 11
6 7 8
3 4 5
1 2
```

- 当$n=15$时，结果为：$(\left\lceil\frac{15}{\left\lfloor\sqrt{15}\right\rfloor}\right\rceil=5)$

```
13 14 15
10 11 12
7 8 9
4 5 6
1 2 3
```

很明显，结果共有$\left\lceil\frac{n}{\left\lfloor\sqrt{n}\right\rfloor}\right\rceil$行，对于每一行而言，这一行的元素递增。

对于第$1$~$\left\lceil\frac{n}{\left\lfloor\sqrt{n}\right\rfloor}\right\rceil-1$行来说，每行共$\left\lfloor\sqrt{n}\right\rfloor$个元素。

对于第$\left\lceil\frac{n}{\left\lfloor\sqrt{n}\right\rfloor}\right\rceil$行来说，共有$n-\left\lfloor\sqrt{n}\right\rfloor×(\left\lceil\frac{n}{\left\lfloor\sqrt{n}\right\rfloor}\right\rceil-1)$个元素



# 代码

代码如下。

```cpp
#include<stdio.h>
#include<math.h>

int n;

int main(void){
	register int i,root;//寄存器更快些
	scanf("%d",&n);//读入
	root=sqrt(n);//求√n向下取整的值
	while(n>0){//确保n为正数
		for(i=n-root+1;i<=n;i++)//一行的长度为√n向下取整的值
			if(i>0)//最后一行会出现非正数，可以用i>0来跳过
				printf("%d ",i);//输出
		n-=root;//下一部分，减去长度
	}
	return 0;
}
```

## [我的测评记录](https://www.luogu.org/record/show?rid=9548103)

---

## 作者：沉石鱼惊旋 (赞：1)

# 题目翻译

给出 $n(1\leq n\leq 2\times 10^5$，构造一个排列使得 $\operatorname{len(LIS)+len(LDS)}$ 最小。 

# 题目思路

样例提示我们分块操作，设分了 $x$ 块，每块块长为 $\frac{n}{x}$。我们这里为了方便书写先只讨论整除的情况，不整除是一样的。

那么我们就是最小化 $x+\frac{n}{x}$，显然 $x=\sqrt n$ 最优。

那么就很好构造了，参考样例从大到小分组即可。

# 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int main()
{
    cin >> n;
    int m = sqrt(n);
    for (int i = 1; i <= (n + m - 1) / m; i++)
    {
        for (int j = n - i * m + 1; j <= n - (i - 1) * m; j++)
            if (j > 0)
                cout << j << " ";
    }
    cout << endl;
    return 0;
}
```

---

## 作者：Scrutiny (赞：1)

一道神奇的构造题

首先，我们证明：一个 $1\sim n$ 的排列的 LIS 和 LDS 长度之和不小于 $\lceil 2\sqrt{n}\rceil$。

**这里给出一个与其他题解方法不同的证明。**


我们采用 DP 的思想，设  $f_i$ 为以  $a_i$ 结尾的最长递增子序列长度， $g_i$ 为以  $a_i$ 结尾的最长递减子序列长度。

显然，对于正整数 $i<j$，若  $a_i<a_j$，则  $f_i<f_j$。若  $a_i>a_j$，则  $g_i>g_j$。

因此，每对  $(f_i,g_i)$ 互不相同，其中  $i=1,2,\cdots,n$。

设  $f_{i}$ 的最大值是  $k$， $g_i$ 的最大值是  $l$。那么  $(f_i,g_i)$ 至多  $kl$ 对，至少  $n$ 对，因此   $kl\ge n$。

$k+l\ge2\sqrt{kl}\ge 2\sqrt{n}$，又因为 $k+l\in\mathbb{Z^+}$，故 $k+l\ge \lceil 2\sqrt{n}\rceil$，得证。

接下来，构造一组满足题意的排列。

以 $n=15$ 为例。考虑一个 $1\sim 15$ 的排列：

$$13\ 14\ 15,10\ 11\ 12,7\ 8\ 9,4\ 5\ 6,1\ 2\ 3$$

在相邻两个逗号之间，至多有一个数在 LDS 中。故最长的 LDS 长度为 $\frac{15}{3}=5$。容易发现，最长的 LIS 长度为 $3$。$5+3=8=\lceil\sqrt{15}\rceil$。

拓展到 $n$ 的情况，LIS 的长度恰为 $\lfloor\sqrt{n}\rfloor$，LDS 长度为 $\lceil\dfrac{n}{\sqrt{n}}\rceil$ 即可。

Sample Code(C++):

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,len,step;
int main(){
    cin>>n;
    len=sqrt(n);
    step=ceil(sqrt(n))+1;
    while(step){
        --step;
        for(int i=max(1,n-len+1);i<=n;++i){
            printf("%d ",i);
        }
        n-=len;
    }
    return 0;
}
```


---

## 作者：yijan (赞：1)

假设当LIS取到 $i$ 时得到LIS长度与LDS长度和最短。   
接着我们需要使用一个定理：对于一组数字，其最长上升/下降子序列长度等于其反链的最多序列数。
For example：  
对于数列$1,6,8,4,7$  
其最长上升子序列$1,4,7$长度为3  
其下降子序列最多序列数$1|6,4|8,7$块数为3  
对于证明详见：[这里](https://www.luogu.org/problemnew/solution/P1020)的第四篇题解。  
至此，由于我们假设的LIS长度为$i$  
但是，注意，原本LDS的反链应该是不降子序列，但是这里由于是1-n的排列所以说不降等价于上升。  
也就是说上升子序列的块数决定了下降LDS长度。  
由于每一个LIS长度为$i$，而在此基础上一定要保证LDS长度尽量小，所以说要使得每一块长度都为$i$  
由于本题是构造题，为了简便，我们可以构造成为如下排列：  
## $\{n-i+1,n-i+2,...|n-2i+1,n-2i+2,...|...\}$  
然后求块数是非常简单的，就是
## $\lceil{\frac{n}{i}}\rceil$
所以说LIS和LDS的和就是  
## $i+\lceil{\frac{n}{i}}\rceil$  
然后由于基本不等式  
## $i+\lceil{\frac{n}{i}}\rceil>=i+\frac{n}{i}>=2\sqrt{n}$  
我们都知道当且仅当$i=\sqrt{n}$时候取到这个值。  
所以说当$i=\sqrt{n}$时$i+\lceil{\frac{n}{i}}\rceil$一定可以取到最值，但是因为向上取整，所以说在有些时候尽管$i\ne\sqrt{n}$也使得这个取到了最值。比如，$n=10,i=4$得到答案和$n=10,i=3$答案一样为7。但由于是spj的构造题，所以直接$i=\sqrt{n}$来构造即可。故代码：
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,block;
int main(void){
    int n,q;cin >> n;
    block = sqrt(n);
    for(q=1;n-block*q >= 0; ++q)
    for(int i=1;i<=block;++i)
        printf("%d ",n-block*q+i);
    for(int i=1;i<=n-block*(q-1);++i)
        printf("%d ",i);
}
```

---

## 作者：yanxu_cn (赞：0)

### 题意简述
构造一个序列使其最长下降子序列和最长上升子序列的长度之和最小。
### 思路
+ 下文记最长上升子序列长度为 $i$，最长下降子序列长度为 $d$，长度之和为 $s=i+d$。

如果说给一个数 $n$ 来确定 $s$ 回比较困难，那么我们可以考虑以 $s$ 确定 $n$。易于证明的是，$n_0$ 对应的 $s_{min}$  $\le$  $n_0+1$ 对应的 $s_{min}$。

根据题意，$\begin{cases} n_{max}=i\cdot d \\ s=i+d \\ i,d>0\end{cases}$。所以我们可以用基本不等式很方便的得出 $n_{max}=\displaystyle{\frac{s^2}{4}}$。

所以我们的方法就是将 $i$ 和 $d$ 缩到最小，且 $\vert i-d\vert\le1$，一个简单的方法就是将整个序列划分为几个段，每个段内下降，段之间依次上升，或者相反。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int n;
    cin>>n;
    int c=ceil(sqrt(n));
    for(int i=c-1;i>=0;i--)
    {
        for(int j=1;j<=ceil(n*1.0/c)&&i*ceil(n*1.0/c)+j<=n;j++)
        {
            cout<<i*ceil(n*1.0/c)+j<<' ';
        }
    }
    return 0;
}
```

---

## 作者：Xssion37_XY (赞：0)

### 前情提要

[题目链接](https://www.luogu.com.cn/problem/CF1017C)

[更好的阅读体验](https://www.luogu.com.cn/article/kcm5bhgd)

### 题目大意

给一个数 $n$，让你构造一个长度为 $n$ 的排列，使得它的最长上升子序列长度与最长下降子序列长度之和最小。

### 实际分析

考虑分块。

将长度为 $n$ 的排列分成 $\frac{n}{x}$ 个长度为 $x$ 的块，每个块的最长上升子序列长度与最长下降子序列长度相等，均为 $x$，整个排列的最长上升子序列长度与最长下降子序列的长度就为 $2\times\frac{n}{x}\times x=2n$。

当 $x=\sqrt{n}$ 时它的最长上升子序列长度与最长下降子序列长度之和最小。

逆序输出即可。

### 代码部分

代码很简单就不放了。

---

## 作者：氧少Kevin (赞：0)

# CF1017C - The Phone Number
- https://www.luogu.com.cn/problem/CF1017C
- 分块构造、根号分块、均值不等式

## 题意
给出一个正整数 $n(1\leq n\leq 10^5)$，请构造一个长度为 $n$ 的排列，使得该排列的 **最长上升子序列长度** 和 **最长下降子序列长度** 的加和最小。

## 思路

考虑分块构造排列。

对于每一个块，元素自左到右是严格上升的。

块与块之间，下一个块的最大值小于上一个块的最小值。

也就是说，最长上升子序列长度 $=$ 最大的块长，最长下降子序列长度 $=$ 块的数量。

>例如，$n=15$ 时有如下构造：
>
>$[13,14,15],\ [9,10,11,12],\ [5,6,7,8],\ [1,2,3,4]$
>
>不难发现，最长上升子序列长度（即最大的块长） $=4$，最长下降子序列长度（块的数量） $=4$，加和为 $8$。这种构造是最优的。

**如何确定 最大的块长 和 块的数量？**

设最大的块长 $=len$，块的数量 $=cnt$。

有：

$$n=len\cdot cnt$$
$$sum=len+cnt\geq 2\sqrt{len\cdot cnt}=2\sqrt{n}$$

当 $len=cnt=\sqrt{n}$ 时，不等式取等号，$sum$ 是最小的。

## 实现
取块的数量为 $\lceil \sqrt{n}\ \rceil$，最大的块长为  $\lceil \sqrt{n}\ \rceil$，按照上述方法构造即可。

---

