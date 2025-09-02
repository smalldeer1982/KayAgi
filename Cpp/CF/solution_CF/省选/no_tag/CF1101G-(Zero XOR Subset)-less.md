# (Zero XOR Subset)-less

## 题目描述

题意简述

给出一个序列$\{a_i\}$，试将其划分为尽可能多的非空子段，满足每一个元素出现且仅出现在其中一个子段中，且在这些子段中任取若干子段，它们包含的所有数的异或和不能为$0$．

## 样例 #1

### 输入

```
4
5 5 7 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
1 2 3
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3
3 1 10
```

### 输出

```
3
```

# 题解

## 作者：fzj2007 (赞：3)

### 题目描述

> 给定一个序列 $\{a_i\}$，请你将他划分成尽可能多的非空子段，每个子段的权值为这个这个字段中所有数的异或和，要求从中选出任意多个子段，其异或和不为 $0$。

### 算法思路

看到区间异或，设 $\{p_i\}$ 表示 $\{a_i\}$ 的前缀异或和，可以有如下转化：

$$
\oplus_{i=l}^r a_l=p_r\oplus p_{l-1}
$$

将原序列划分成一个子段，这个子段的异或和可以看做 $p_r\oplus p_{l-1}$。

而后，我们要求任意子段的异或和均不为 $0$，可以想到线性基。

首先考虑无解的情况。当所有元素的异或和为 $0$，即 $p_n=0$ 时，无论怎么划分，将所有的子段全选时一定异或和为 $0$，故无解。

对于有解的情况，可以尝试将 $\{p_i\}$ 中的每个数插入线性基，如果可以插入答案加一，否则证明如果选择在这里分段，与前面的某一段异或和为 $0$，与原题不符，故不能插入。

又由于线性基是唯一的，所以顺序不会影响答案。

故最终的答案即为线性基的大小。

### 代码实现

快读快写过长略去了，代码并不难写。

```
#define N 200005
int n,maxn=31,t[N],ans,lst;
inline void insert(int x){
	for(int i=maxn;~i;i--){
		if(!(x>>i&1)) continue;
		if(!t[i]) t[i]=x,ans++,i=0;
		else x^=t[i];
	}
}
int main(){
	read(n);
	for(int i=1,x;i<=n;i++) read(x),lst^=x,insert(lst);
	put('\n',!lst?-1:ans);
	return 0;
}

```


---

## 作者：是个汉子 (赞：3)

[洛谷题目](https://www.luogu.com.cn/problem/CF1101G)	[CF原题](http://codeforces.com/problemset/problem/1101/G)

### Solution

因为要求区间异或和，所以很自然的想到异或前缀和，即设 $sum_i=a_1\oplus a_2\oplus \cdots\oplus a_i$ ，那么 $(l,r)$ 的异或和就能用 $sum_{l-1}\oplus sum_r$ 来表示。

那么我们就需要找出尽量多的点 $p_x$ ，使得 $\{sum_{p_1},sum_{p_2}\oplus sum_{p_1},\cdots ,sum_{p_{t-1}}\oplus sum_n\}$ 的子集的异或非 $0$ 。

等等，我们可以先构造另一个和上面等价的序列 $\{sum_{p_1},sum_{p_2},\cdots ,sum_{p_{t-1}},sum_n\}$ ，因为将上面里面的东西相互异或对最后的命题是否成立没有影响。

说人话就是：对于子集非 $0$ ，或者它们的线性基是等价的。

比如： $sum_x\oplus sum_y=((sum_x\oplus sum_{x+1})\oplus(sum_{x+1}\oplus sum_{x+2})\cdots (sum_{y-1}\oplus sum_y))$ 

ok，现在只要找到一个合适的顺序使得 $sum_i$ 的序列的线性基元素最多就行。

接下来，可以看我[这篇题解](https://www.luogu.com.cn/blog/jasony/p4570-bjwc2011-yuan-su)关于**一个序列的线性基元素数量唯一** 的证明。

既然知道元素数量都一样，那就直接扫一遍就行。

完结~~撒花~~上代码(o゜▽゜)o☆

### Code

```c++
#include<bits/stdc++.h>

using namespace std;
const int N=2e5+10;
int n,ans,a[N],cnt,d[35];

inline void insert(int x){
    for(int i=30;i>=0;i--){
        if(x&(1<<i)){
            if(!d[i]){
                ++cnt; d[i]=x;
                break;
            }
            else x=d[i]^x;
        }
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),a[i]^=a[i-1];
    if(!a[n]){
        puts("-1");
        return 0;
    }
    for(int i=1;i<=n;i++) insert(a[i]);
    printf("%d\n",cnt);
    return 0;
}
```



---

## 作者：_Clown_ (赞：1)

这道题目我们可以用线性基解决

线性基的定义： 

对于n个数，a1,a2,a3,a4……

线性基b1,b2……

线性基满足的情况是这n个数，其中的任意个数的异或值都能用数组b中的某几个数求出来。

我们先来看看无解的情况，如果所有数的异或和为0，不管你怎么分都是无解。

如果有解，直接输出线性基就好了。

为什么线性基是正确的呢？

线性基中的任意几个数都不可能异或是0，这个性质我们可以通过反证法来进行，如果异或是0的话，那就说明这个这几个数中，存在可以互相表达的情况，这就有违求线性基的过程了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int Total;
int Array[200001];
int Prefix[200001];
int Basic[31];
int Ans;
inline void Add(int X)
{
	register int i;
	for(i=30;i>=0;i--)
	{
		if(X&(1<<i))
		{
			if(Basic[i])
			{
				X^=Basic[i];
			}
			else
			{
				Ans++;
				Basic[i]=X;
				break;
			}
		}
	}
}
int main(void)
{
	register int i;
	cin>>Total;
	for(i=1;i<=Total;i++)
	{
		cin>>Array[i];
		Prefix[i]=Prefix[i-1]^Array[i];
	}
	if(!Prefix[Total])
	{
		goto UnSolve;
	}
	for(i=1;i<=Total;i++)
	{
		Add(Prefix[i]);
	}
	cout<<Ans<<endl;
	return 0;
	UnSolve:
		cout<<-1<<endl;
		return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

感谢 LitDarkness 秒切提供思路。

假设划分为 $(0,l_1]$，$(l_1,l_2]$，$\dots$，$(l_t,n]$，假设求出 $a$ 的异或前缀和 $b$，那么 $b_{l_1} \oplus b_{0}$、$b_{l_2} \oplus b_{l_1}$、$\dots$，$b_n \oplus b_{l_t}$ 线性无关。

既然线性无关，可以做一些变换，得到：

$b_{l_1}$、$b_{l_2}$、$\dots$、$b_{n}$ 线性无关。

当 $b_n=0$ 的时候必定无解。

否则，显然就是 $\{b_1 ,b_2,\dots,b_n\}$ 构成的线性基的大小。

> 显然不会超过线性基的大小。考虑构造的时候直接把 $b_n$ 扔进去，那么就可以构造一组大小为线性基大小的线性无关组。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,a[MAXN],cnt,bs[35];
void insert(int u) {
	roff(i,30,0) if(u&(1<<i)) {
		if(bs[i]) u^=bs[i];
		else return bs[i]=u,cnt++,void(); 
	}
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>a[i],a[i]^=a[i-1];
	if(a[n]==0) return cout<<-1,0;
	ffor(i,1,n) if(a[i]) insert(a[i]);
	cout<<cnt;
	return 0;
}
```

---

## 作者：forest114514 (赞：0)

首先答案不会超过 $30$，因为线性基的性质易得基的大小不会超过 $\log V$。

然后一段数的异或和为 $0$ 肯定是不行的，不然怎么划分直接全取异或和就为 $0$ 了，否则异或和不为 $0$ 的数组一定可以划分成一段即以上合法的子段（至少能划分成一段异或和不为 $0$ 的子段）。

考虑如下的贪心构造方式：如果一个数无法成为基底，就跟后面的数异或合并成一个新的数，直到线性基满了或数用完了为止（用不完下面将单独讨论）。

但我们想想这样构造有没有如下的问题，如果最后的数入不了基而且基没满，是否存在更优的划分？

意会一下是没有的，如果一个数能入异或线性基，那么它二进制某一位一定会在基中没有出现过，否则它肯定可以入基，所以这样可以说明无论怎么划分都不可能增大基的大小，如果想要造划分方案，把最后一段无法入基的区间和最后入基的那个区间合并在一起就行啦。

所以结论是：最大划分段数等于最后构造出的线性基大小，直接套线性基的板子就行了。



CODE：
```cpp
const int N=2e5+100;
int n,a[N],x,p[35],ans;
bool insert(int x){
	rep(i,0,30){
		if((x>>i)&1){
			if(!p[i]){
				p[i]=x;++ans;return 1;
			}
			x^=p[i];
		}
		if(!x) return 0;
	}
	return 0;
}
signed main(){
	read(n);
	rep(i,1,n) read(a[i]),x^=a[i];
	if(!x) return puts("-1"),0;
	rep(i,1,n){
		if(!insert(a[i])) a[i+1]^=a[i];
	}
	write(ans,'\n');
	return 0;
}

```

---

