# [ARC084E] Finite Encyclopedia of Integer Sequences

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc084/tasks/arc084_c

有限整数列大辞典(Finite Encyclopedia of Integer Sequences)には、 $ 1 $ 以上 $ K $ 以下の整数からなる、長さ $ 1 $ 以上 $ N $ 以下の整数列がすべて載っています。

有限整数列大辞典に載っている整数列の個数が $ X $ 個あるとするとき、その中で辞書順で $ X/2 $ (小数点以下切り上げ)番目のものを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ K,N\ \leq\ 3\ ×\ 10^5 $
- $ N,K $ は整数である

### Sample Explanation 1

有限整数列大辞典に載っている整数列は、$ (1),(1,1),(1,2),(1,3),(2),(2,1),(2,2),(2,3),(3),(3,1),(3,2),(3,3) $ の $ 12 $ 個です。 この中で辞書順で $ 12/2\ =\ 6 $ 番目のものは、$ (2,1) $ です。

## 样例 #1

### 输入

```
3 2```

### 输出

```
2 1```

## 样例 #2

### 输入

```
2 4```

### 输出

```
1 2 2 2```

## 样例 #3

### 输入

```
5 14```

### 输出

```
3 3 3 3 3 3 3 3 3 3 3 3 2 2```

# 题解

## 作者：火车司机 (赞：5)

## 简要分析

当 $k$ 是偶数时，答案必然是 $\frac{k}{2}$ 后面接 $n-1$ 个 $k$

首先，有一个十分显然的结论：以每一个数作最高位的数字总数必然全部互相相同

因此当 $k$ 是偶数时，最中间的位置必然落在以 $\frac{k}{2}$ 为首的最后一个数字和以 $\frac{k}{2}+1$ 为首的第一个数字之间

所以答案即为以 $\frac{k}{2}$ 为首的最后一个数字

当 $k$ 是奇数时，同样根据上面的结论，答案必然是以 $\frac{k+1}{2}$ 为首的数中最中间的那个数，考虑怎么找到它

有长度小于 $n$ 的数干扰很难想，先暂时不考虑，那么这时最中间的数一定是 $n$ 个 $\frac{k+1}{2}$ 所组成的

再把长度小于 $n$ 的数重新放进来考虑

因为小于 $\frac{k+1}{2}$ 的数与大于 $\frac{k+1}{2}$ 的数一样多，所以对答案有影响的只有全部由 $\frac{k+1}{2}$ 组成的长度小于 $n$ 的数，共 $n-1$ 个

要使前面的数的个数小于等于后面的数的个数，答案应当向前移动 $\lceil\frac{n-1}{2}\rceil$ 个

## 完整代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ri register int
#define N 300005
using namespace std;
int n, k, a[N];
template <typename T>
inline void read(T &x)
{
	register T f = 0, c = getchar();
	for (; c < 48 || 57 < c; c = getchar())
		if (c == '-')
			f = 1;
	for (x = 0; 48 <= c && c <= 57; c = getchar())
		x = (x << 3) + (x << 1) + (c & 15);
	if (f)
		x = ~(--x);
}
template <typename T>
inline void print(T x)
{
	if (x < 0)
		putchar('-'), x = ~(--x);
	if (x > 9)
		print(x / 10);
	putchar(x % 10 | 48);
}
signed main()
{
	read(k), read(n);
	if (k & 1)
	{
		for (ri i = 1; i <= n; ++i)
			a[i] = k + 1 >> 1;
		ri t = n >> 1;
		for (ri x = n; t > a[n];)
		{
			t -= a[n], a[n] = 0;
			for (; t && !a[x]; --x)
				if (a[x - 1] == 1)
					--t, a[x - 1] = 0;
			if (t)
			{
				for (ri i = x + 1; i <= n; ++i)
					a[i] = k;
				--t, --a[x], x = n;
			}
		}
		a[n] -= t;
		for (ri i = 1; i <= n; ++i)
			if (a[i])
				print(a[i]), putchar(' ');
	}
	else
	{
		print(k >> 1), putchar(' ');
		for (ri i = 1; i < n; ++i)
			print(k), putchar(' ');
	}
	puts("");
	return 0;
}
```


---

## 作者：Krimson (赞：2)

~~应该是有很多简便的方法的,我这种还是太麻烦了...~~

update:由于写代码的时候$N$和$K$看反了,所以题解里的$N$和$K$与题目里面的是反过来的...

 _Solve_ 
------------
首先应该不难得到所有排列的个数$X=\sum\limits^{k}_{i=1}n^i$  
为了方便最后的统计,这里设$b[j]=\sum\limits^{j}_{i=0}n^i$  
如果把每一位上的数$a[i]$看作是某个进制下的数,那么就相当于要满足  
$$
\sum\limits^{k}_{i=1}a_iv_i=\lfloor\frac{b[k]}{2} \rfloor
$$
其中$v_i$是第$i$位的贡献  
可以发现如果确定了第$i$位为$a_i$,那么就可以确定存在$(a_i-1)b_{k-i}+1$个排列都是一定比当前排列小的(类似数位DP)  
也就是说每一位的贡献$v_i=(a_i-1)b_{k-i}+1$  
  
~~到了这个地方似乎可以直接每一位都取最大的,可以很轻松的求出答案,我似乎走了弯路~~  
对原来的式子$\lfloor\frac{b[k]}{2} \rfloor$分析  
可以发现  
$$
\texttt{这里还需要设一个res,表示最后得到的序列比答案大了res个排名}\\
\lfloor\frac{b[k]}{2} \rfloor=\lfloor\frac{nb[k-1]+1}{2}\rfloor  
\\
\texttt{如果n是偶数,可以直接变成}\frac{nb[k-1]}{2},\texttt{等价于第1位上取}\frac{n}{2}+1,\texttt{并且res要+1}  
\\
\texttt{如果n是奇数,那么原式变成} \lfloor\frac{n}{2}\rfloor b[k-1]+[b[k-1]=2q+1,q\in N^*]+\lfloor\frac{b[k-1]}{2} \rfloor  
\\
\texttt{对于}[b[k-1]=2q+1,q\in N^*]\texttt{,如果b[k-1]是奇数,那么res-1就好了}  
\\  
\texttt{对于}\lfloor\frac{n}{2}\rfloor b[k-1]\texttt{,跟n是偶数的时候一样处理就好了}  
\\
\texttt{而}\lfloor\frac{b[k-1]}{2} \rfloor\texttt{,可以发现和}\lfloor\frac{b[k]}{2} \rfloor\texttt{形式一样,可以递归解决}  
$$  
最后剩下没解决的问题就是如何解决求比当前小$res$次的序列了  
可以证明$res\leq K$,可以暴力跳  
暴力往前跳比较简单,这里就不赘述了,但是细节比较多,这里就直接上代码了  
```cpp
void up(ll t){
    int lst=k;
    while(t>a[k]){
        t-=a[k];
        a[k]=0;
        while(t&&!a[lst]){
            if(a[lst-1]==1){
                a[lst-1]=0;
                t--;
                lst--;
            }
            else{
                lst--;
            }
        }
        if(t){
            t--;
            a[lst]--;
            for(ri i=lst+1;i<=k;++i) a[i]=n;
            lst=k;
        }
    }
    a[k]-=t;
}
```


 _Code_ 
------------
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il int max(const int &a,const int &b){return a>b?a:b;}
il int min(const int &a,const int &b){return a<b?a:b;}
const ll mod=1e9+7;
const int MAXN=3e5+7;
ll a[MAXN],b[MAXN];
ll n,k;
/*
先暴力往后跳
*/
void up(ll t){
    int lst=k;
    while(t>a[k]){
        t-=a[k];
        a[k]=0;
        while(t&&!a[lst]){
            if(a[lst-1]==1){
                a[lst-1]=0;
                t--;
                lst--;
            }
            else{
                lst--;
            }
        }
        if(t){
            t--;
            a[lst]--;
            for(ri i=lst+1;i<=k;++i) a[i]=n;
            lst=k;
        }
    }
    a[k]-=t;
}
ll now;
ll res;
void solve(int id){
    if(id>k) return;
    ++res;
    a[id]=(n/2+1);
    if(n&1){
        if(b[k-id]&1) res--;
        solve(id+1);
    }
}
int main(){
    n=read(),k=read();
    b[0]=1;
    for(ri i=1;i<=k;++i) b[i]=(b[i-1]*n+1)&1;
    solve(1);
    up(res);
    for(ri i=1;i<=k;++i){
        if(a[i]){
            write(a[i]),putchar(' ');
        }
    }
    puts("");
    return 0;
}
/*
1
1 1
1 2
2
2 1
2 2
*/
```


---

## 作者：skyskyCCC (赞：0)

## 前言。
远古 ARC 题选做。本题的主要思想是找规律。
## 分析。
是的，你没有听错，本题是个喜闻乐见的规律题！为什么这么考虑？因为我们观察样例，出现了好几个连续的数都是相同的，而且貌似和 $k$ 有某些规律。所以我们分类探讨一些。

- 如果 $k$ 是偶数。

显然对于这个情况，则在 $N$ 个元素组成的序列中，字典序最小的序列是 $\begin{matrix}\underbrace{1,1,\cdots,1}\\N\end{matrix}$ 且最大的序列是 $\begin{matrix}\underbrace{k,k,\cdots,k}\\N\end{matrix}$。举个例子，样例二中可能的序列排序为：
```
1 1 1 1
1 1 1 2
1 1 2 2
1 2 2 2//输出的答案。
2 1 1 1
2 1 1 2
2 1 2 2
2 2 2 2
```
一共有 $8$ 种情况，第四种情况是答案。所以显然答案就是 $\frac{k}{2},k,k,\ldots,k$ 的样子。
- 如果 $k$ 是奇数。

如果我们设一个序列是 $A$ 再设一个序列 $B$。序列 $B$ 中的每一个 $a_i$ 都可以看做是 $A$ 序列中的 $a_i$ 变成 $k-a_i+1$ 得来的。这样我们考虑映射。所以这个映射就是 $f\left(A\right)\rightarrow B$ 因此除了 $A$ 是某个序列的一个前缀外，每个 $A$ 和 $B$ 都是一个序列的前缀和后缀。设序列总个数为 $Q$ 则这个序列所在的位置就是 $\frac{\left(Q+1\right)}{2}+\frac{N}{2}$ 的地方。

于是从往前倒推 $\frac{N}{2}$ 就是答案序列。

代码如下，仅供参考：
```
#include<cstdio>
#include<iostream>
using namespace std;
int n,k;
int a[300005];
int mowei;
int main() {
	cin>>k>>n;
	mowei=n;
	if(k&1){
		for(int i=1;i<=n;i++){
			a[i]=(k+1)/2;
		}
		for(int i=1;i<=n/2;i++){
			if(a[mowei]==1){
			    mowei--;
			}
			else{
				a[mowei]--;
				for(int j=mowei+1;j<=n;j++){
					a[j]=k;
				}
				mowei=n;
			}
		}
		for(int i=1;i<=mowei;i++){
			cout<<a[i]<<" ";
		}
		cout<<"\n";
	}
	else{
		cout<<k/2<<" ";
		for(int i=2;i<=n;i++){
			cout<<k<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

