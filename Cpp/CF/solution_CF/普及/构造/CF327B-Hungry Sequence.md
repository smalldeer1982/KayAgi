# Hungry Sequence

## 题目描述

Iahub and Iahubina went to a date at a luxury restaurant. Everything went fine until paying for the food. Instead of money, the waiter wants Iahub to write a Hungry sequence consisting of $ n $ integers.

A sequence $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ , consisting of $ n $ integers, is Hungry if and only if:

- Its elements are in increasing order. That is an inequality $ a_{i}&lt;a_{j} $ holds for any two indices $ i,j $ $ (i&lt;j) $ .
- For any two indices $ i $ and $ j $ $ (i&lt;j) $ , $ a_{j} $ must not be divisible by $ a_{i} $ .

Iahub is in trouble, so he asks you for help. Find a Hungry sequence with $ n $ elements.

## 样例 #1

### 输入

```
3
```

### 输出

```
2 9 15
```

## 样例 #2

### 输入

```
5
```

### 输出

```
11 14 20 27 31
```

# 题解

## 作者：yydfj (赞：16)

**这是本蒟蒻第七次写的题解，如有错误点请好心指出！**

## 问题简述

__这道题我们可以换另一种思路去看待它，就容易理解了：__

给你一个整数 $n$，求出 $n$ 到 $2n-1$ 之间的数。

## 解法综述

这道题实际上是在求一个由 $n$ 个数字组成的不下降序列，且该序列内的数字不会被序列内其他数字整除。

有一种方法大概是大家都能想到的：求出 $n$ 个质数，将该 $n$ 个质数从小到大输出。但这次我想将__另一种方法__分享给大家，即求出 $n$ 到 $2n-1$ 之间的数，下面我们来探讨一下这个答案是怎么得来的。

随机找出一个整数 $n$ 作为起点，依次向后推 $n+1$，$n+2$，$n+3$ ... ... 直到推到 $2n$ 的时候就会发现， $2n$ 会被 $n$ 整除，而 $n$ 到 $2n-1$ 之间的这 $n$ 个数都互相不被整除，由此证出上述的答案。

## 代码描述
```cpp
#include<cstdio>
int n;
int main()
{
	scanf("%d",&n);
	for(int i=n;i<=2*n-1;i++) printf("%d ",i);//证出n到2n-1之间的这n个数互相不被整除
	return 0;
}
```

---

## 作者：Rosmarinus (赞：3)

### upd 2021.7.6 修复了题目简述中的表述错误问题，感谢 @yydfj 的指出。

## 思路分析

题目要求我们构造长度为 $n$ 的序列，满足：

- 递增；
- 互相不被整除；
- 序列中的元素不低于 $2$，不超过 $10^7$。

嗯……递增……互不相除……

啊讲个笑话：$2\sim 10^7$ 中共有 $664579$ 个质数，而 $n\le 10^5$。

显然，如果这个序列中全是质数的话是一定不能互相被整除的。

所以直接从小到大输出 $n$ 个质数即可。

使用筛质数法。

## AC 代码

```cpp
#include <iostream>
using namespace std;
const int maxn = 1e7;
bool p[maxn];
int n;
void Work()
{
    for (int i = 2; i < maxn; i++)
	{
        if(p[i] == false)
		{
			printf("%d ", i);
			n --;
			if(n <= 0) return;
            for (int j = i + i; j < maxn; j += i)
			{
                p[j] = true;
            }
        }
    }
}

int main()
{
	cin >> n;
	Work();
    return 0;
}
```

---

## 作者：cst_123 (赞：2)

### - [传送门](https://www.luogu.com.cn/problem/CF327B)

------------

### 题意

给你一个数 $n$，让你求出一个递增数列。

并满足数列中各个数互质，$2\le a_i\le 10^7$。

### 思路

~~这题输出 $n$ 个质数不就行了，就不放代码了~~

下面是重磅思路：

 ~~检测到小学数学，请谨慎观看~~

在小学数学里，两个数除 $1$ 外没有其他任何因数时，可以称之为两个数互质。那么就输出全部都互质的 $n$ 个数，就也能满足，我们列出这些情况。

- 两个质数，~~这不是废话~~
- 两个公因数只有 $1$ 的数
- 两个相差 $1$ 的数 （这是今天的重点）
 
那么，只要输出一个连续上升序列时，不就可满足题目条件了吗。

举个栗子

```cpp
3
----
3 4 5
```

设一个正整数 $k$，栗子中 $k$ 为 $3$，$k\sim(k+n-1)$ 的数列是可以的，也有 $n$ 个数。

再推几个栗子，就可发现 $k$ 为 $n$ 时( $a_{2n-1}$ 不会被 $a_k$ 整除)，是符合答案的。

继续思考，当 $k$ 为 $2n$ 时，答案也可以，那就尽情地去往后推吧。

---

## 作者：_Execution_ (赞：1)

## 思路
要求数列中互相不可以整除，因此可以想到只要数列中都是质数，每个数就互质，因而得到解法。

使用质数筛，然后从小到大输出前 $n$ 个质数即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
bool v[100000005];
int k,sum;
const int MAX=7000005;
void prime(int n){//欧拉筛
    memset(v,0,sizeof(v));
    for(int i=2;i<=sqrt(n);i++){
        if(v[i]) continue;
        v[i]=0;
        for(long long j=i;i*j<=n;j++){
            v[j*i]=1;
        }
    }
}
int main() {
  prime(MAX);
  cin>>k;
  for(int i=2;sum<k;i++){
    if(!v[i]){
      sum++;
      cout<<i<<" ";
    }
  }
  return 0;
}
```


---

## 作者：Wf_yjqd (赞：0)

模拟赛题。

------------

考虑任意两个质数一定互质，所以不可能存在 $i\ne j$ 且 $a_i\mid a_j$。

发现 $10^7$ 内的质数个数肯定大于 $n$。

所以筛质数然后按顺序输出 $n$ 个即可。

复杂度 $\operatorname{O}(n)$。

------------

然后就这我花了 $22$ 分钟。。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e7+84,maxm=1e7;
int n,pcnt,prime[maxn];
bitset<maxn> imprime;
void get_prime(){
    for(int i=2;i<=maxm;i++){
        if(!imprime[i])
            prime[++pcnt]=i;
        for(int j=1;j<=pcnt&&i*prime[j]<=maxm;j++){
            imprime[i*prime[j]]=1;
            if(i%prime[j]==0)
                break;
        }
    }
    return ;
}
int main(){
    get_prime();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        printf("%d Sherry",prime[i]);
    return 0;
}
```


---

## 作者：ly618x (赞：0)


### 大致题意：

构造一个长度为 $n$ 的序列 $a$ 并满足序列中没有数可以整除另一个数。

### 思路：

我们可以使这一个数组中的所有数字都为**质数**（各不相同）就自然满足条件。

注：第 $10^5$ 个质数符合要求。

### 代码：

``` cpp
#include <bits/stdc++.h>
using namespace std;
bool prime(int x)//判断质数。
{
	if(x<2)return false;
	if(x==2)return true;
	for(int i=2;i<=sqrt(x);i++)
	  if(x%i==0)return false;
	return true;
}
int main()
{
	int n;
	cin>>n;
	int num=1;
	while(n!=0)//输出n个数就循环结束。
	{
		num++;
		if(prime(num))
		{
			cout<<num<<" ";
			n--;//成功输出一个数字就减一。
		}
	}
	return 0;
}
```

---

## 作者：shengheng (赞：0)

#### [传送门](https://www.luogu.com.cn/problem/CF327B)

## 题目大意
题目绕了很多弯子。其实就是想让你组建一个上升序列，序列里每个数都互质。

这样，思路就很清晰了。

## 题目思路
由于 $2\le a_i\le 10^7$ 且 $1$ 能被任何数整除，所以 $1 \sim n$ 的序列不符合要求。

$n$ 的 $2$ 倍是 $2n$。$2n$ 能被 $n$ 整除，那么 $n \sim 2n-1$ 中所有数必然互质：$2n$、$2(n+1)$、$2(n+2)$……$2(2n-1)$ 都会超过 $2n-1$ 的范围。

所以，我们只用输出 $n \sim 2n-1$ 中的所有数就可以了。

PS：题目告诉你有多种答案输出其一（没有翻译出来），所以各位大佬不必拘泥于样例。

## 正解

```cpp
#include<bits/stdc++.h>//万能头文件。
using namespace std;
int n; 
int main(){
	cin>>n;//输入n。
	for(int i=n;i<=2*n-1;i++)cout<<i<<' ';//输出n～2n-1区间里的所有数。
	return 0;
}
```


---

## 作者：Nwayy (赞：0)

- 提供一种新思路。

# solution

- 题目要求构造一个长度为 $n$，呈严格上升，且不存在某个数能被另一个数整除的序列。

- 注意到有 $1 \le n \le 10^5$，$2 \le a_{i} \le 10^7$，数据范围允许我们**构造一个长度为 $n$，首项为 $10^6$，公差为 $1$ 的等差数列**。

- 为什么这样构造是可行的呢？由于 $n$ 的范围只有 $10^5$，那我们从 $10^6$ 起构造等差数列，那么末项最多为 $10^6+10^5$，符合 $a_{i}$ 的数据限制，且从中不会有整除的情况出现。因为公差为 $1$，若是要出现整除的情况至少也要到 $2 \times 10^6$，但是这与末项可能的最大情况相差甚远，因此这样的构造方案是可行的。

# code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i;
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++) printf("%d ",999999+i);
	return 0;
}
```


---

## 作者：Diphosphonate (赞：0)

## [题面传送门](https://www.luogu.com.cn/problem/CF327B)

## 题意
构造一个上升序列使得其中元素两两互质。
## 思路
因为 $n \nmid n+k(k \le n)$，所以自然而然可以想到构造序列 $a_i=n+i-1(1 \le i \le n)$，这样取任意 $i,j(1 \le i<j \le n)$，均有 $a_j-a_i=(n+j-1)-(n+i-1)=j-i<n$，所以 $a_i \nmid a_j$，命题成立。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	cin>>n;
	for(int i=n;i<=2*n-1;i++)cout<<i<<" ";
	return 0;
}

```

---

## 作者：_easy_ (赞：0)

# 思路
由题目知：我们要构造一个任意两个数都不成倍数关系的数列。首先可以想到全部互质，线性筛代码如下（不是本题代码）：
```cpp
void find(long long n){
	for(int i=2;i<=n;i++){
		if(!a[i]){
			ans[cnt++]=i;
		}
		for(int j=0;j<cnt&&ans[j]*i<=n;j++){
			a[ans[j]*i]=1;
			if(i%ans[j]==0){
				break;
			}
		}
	}
}
```

但还有另一种方法：我们只需要输出从 $\texttt{n}$ 开始的连续的 $\texttt{n}$ 个整数就行了。证明如下：

假设有一个 $\texttt{a}$ 属于 $\texttt{n}$ 到 $\texttt{2n-1}$ 且可以被 $\texttt{n}$ 到 $\texttt{2n-1}$ 中的一个数整除，则 $a \geq 2n-1$。但是  $\texttt{a}$ 属于 $\texttt{n}$ 到 $\texttt{2n-1}$，所以矛盾，则满足条件。
# 代码
过于简单，这里就不放了

---

