# Missing Subsequence Sum

## 题目描述

给定两个整数 $n,k$，你需要构造出一个长度不超过 $25$ 的数组 $a$，并满足以下条件：

* $a$ 中任意子序列元素和不为 $k$。

* $a$ 中所有子序列和可以表示 $1\sim n$ 中除了 $k$ 以外的任意整数。

子序列表示一个序列中任意一些元素按顺序组成的序列，比如 $[5,2,3]$ 是 $[1,5,7,8,2,4,3]$ 的子序列。

可以证明一定存在这样的方案。

## 说明/提示

对于全部数据，满足 $1\le t\le1000$，$1\le k\le n\le10^6$，$1\le \sum n\le10^7$。

你构造的数列需要满足 $1\le m\le25$，$0\le a_i\le10^9$。

## 样例 #1

### 输入

```
5
2 2
6 1
8 8
9 3
10 7```

### 输出

```
1
1
5
2 3 4 5 6
7
1 1 1 1 1 1 1
4
7 1 4 1
4
1 2 8 3```

# 题解

## 作者：UnfortunatelyDead (赞：8)

首先没有 $k$ 的限制是简单的。

没有了 $k$ 的限制，变成了在使用 $25$ 个数以内凑出 $1 \sim n$ 的所有数，易想到二进制的性质，将 $1 \sim n$ 每个数分解成二进制后形式，那么每个值只有选或不选，位数最多是 $\log n$ 位，$\log n \leq 25$。

接下来就是要求不能出现 $k$ 了。

虽然说不能凑出来 $k$，但是我们还是照样要凑 $1 \sim k-1$ 和 $k+1 \sim n$。

其中 $1 \sim k-1$ 是简单的，就是没有 $k$ 限制时的做法，不过最后一个加进去的数要注意不能凑出 $k$。具体地，定义 $d = \lfloor \log(k-1) \rfloor$，则第 $d+1$ 个数应该是 $k-1 - 2^d$。

对于 $k+1 \sim n$ 的方法，此处我们默认 $1 \sim k$ 是被凑出的，那么还是可以根据二进制性质，每次翻倍凑出直到 $n$ 的所有的数，但是我们发现 $2k$ 是无法被凑出的，加入 $k+1$ 使得 $k+1+k-1 = 2k$ 即可。

注意特判 $1$。

---

## 作者：Exp10re (赞：5)

## 解题思路

考虑构造出 $1\sim (k-1)$ 以及 $(k+1)\sim n$。

首先考虑 $1\sim (k-1)$。记 $x=\lfloor \log_2 k \rfloor$，则先尝试构造出 $1\sim (2^x-1)$，再构造出 $2^x \sim (k-1)$。

考虑二进制，可以通过加入 $1,2,\cdots,2^{x-1}$ 得到 $1\sim (2^x-1)$。

接下来我们考虑加入一个新的值 $y$ 会发生什么：若我们当前可构造的正整数集合为 $S_0$，则加入 $y$ 后，若我们钦定必须选 $y$ 则可以得到 $S_1=\{x\in \mathbb{Z}^+ \mid x=y+p,p\in S_0 \cup {0}\}$，而不选 $y$ 可以得到 $S_0$，故加入 $y$ 后的可构造正整数集合为 $S=S_0 \cup S_1$。

由此可知：若我们想构造出 $2^x \sim (k-1)(k\ne 2^x)$，则需要加入一个 $(k-2^x)$。

如此，我们构造出了 $2^x \sim (k-1)$，接下来考虑往后构造。

- 当前值域：$1\sim (k-1)$。  
  考虑加入 $(k+1)$，得到 $(k+1) \sim 2k$。

- 当前值域：$1\sim (k-1) \cup (k+1) \sim 2k$。  
  考虑加入 $(2k+1)$，得到 $(2k+1) \sim 3k$，之后的部分我们忽略。

- 当前值域：$1\sim (k-1) \cup (k+1) \sim 3k$。  
  这个位置是一个重要的节点。从这里开始我们就可以使用 $(k+1) \sim 3k$ 这一段进行倍增了。
  具体的，我们加入 $2^ik,i\in\mathbb{Z}^+$ 直到 $2^ik\geq n$。可以发现，每一次这样的操作可以使大于等于 $(k+1)$ 的数可构造个数翻倍且连续，而每一次添加的数 $\gt k$ 可以保证无法构造 $k$。

次数是 $\log_2 k+\log_2 \frac n k +1=\log_2 k +eps$ 规模的，可以通过。

特判 $1$。具体的，往数列中加入 $2,3,4$ 然后按照上述同等思路构造即可。

---

## 作者：___Furina___ (赞：4)

### 题意简述：
无。
### 题解：
提出一个比较新奇的构造思路。

记录 $sum_i$ 为构造了 $i$ 个数时，能够表示的最大的数（前 $i$ 个数的和）；
再记录 $a_i$ 为构造的第 $i$ 个数字。

分三类讨论：
- 当 $sum_{i-1}+2^{i-1}<k$ 时，显然应该构造出 $a_i=2^{i-1}$；
- 当 $sum_{i-1}< k\le sum_{i-1}+2^{i-1}$ 时，考虑调整构造 $4$ 个数，分别构造成 $k-sum_{i-1}-1$、$k+1$、$2k$、$3k$；
- 当 $k\le sum_{i-1}$ 时，显然应该构造出 $a_i=2a_{i-1}$。

下面分 $4$ 步给出证明：
1. 在加入 $k-sum_{i-1}-1$ 后，根据二进制的性质，必然能构造出 $1$ 到 $k-1$ 的所有数；
1. 在加入 $k+1$ 后，由第 $1$ 步可得，必然可以表示出 $k+1$ 到 $2k$ 的所有数；
1. 在加入 $2k$ 后，由第 $2$ 步可得，必然可以得出 $2k+1$ 到 $4k$ 的除了 $3k$ 的所有数；
1. 在加入 $3k$ 后，由第 $3$ 步可得，必然可以得出 $4k+1$ 到 $7k$ 的所有数。

$\cdots$

以此类推，所有的数都能被表示，从而这种做法是正确的。

可能有人会问，为什么要插入 $3k$？原因很简单，因为我们并没有 $k$，所以无法构造出 $3k$。

于是就很愉快的构造出了正确方法！

注意 $n$ 可能等于 $m$！

### 代码如下：
```cpp
#include<bits/stdc++.h>
#define I_love_Furina return//发电+防抄袭
#define forever 0
#define N 200010
#define int long long
using namespace std;
int n,T,m,a[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		int x=1,cnt=0,sum=0,flag=0;
		cin>>n>>m;
		if(m==n)n--;//n=m怎么办！！！
		for(int i=1;i<=25&&x<=n;i++){
			if(flag)a[++cnt]=x,sum+=x,x*=2;//未到k 
			else {
				if(sum+x>=m){
					x=m-sum-1;
					if(x!=0)a[++cnt]=x,sum+=x;//1
					x=m+1,a[++cnt]=x,sum+=x;//2
					//x=m+1,a[++cnt]=x,sum+=x;
					x=m*2,a[++cnt]=x,sum+=x;//3
					x*=2,a[++cnt]=3*m,sum+=3*m;//4
					flag=1;
				}//刚好到k
				else a[++cnt]=x,sum+=x,x*=2;//过了k
			}
		}
		while(a[cnt]>n)cnt--;//可能有多余构造，去除掉
		cout<<cnt<<endl;
		for(int i=1;i<=cnt;i++)cout<<a[i]<<" ";
		cout<<endl;
	}
  I_love_Furina forever;//完结撒花~~~
}
```

点个赞再走！！！

---

## 作者：0tAp (赞：3)

题目链接：[Missing Subsequence Sum](https://www.luogu.com.cn/problem/CF1965B)


------------
非常好的一道构造题啊，考虑从二进制来思考这道题，我们需要构造的序列长度最大为 $25$，因此在 $n\le10^6$ 的情况下，我们完全可以构造出序列的，从二进制的情况下考虑问题就简单多了，对于二进制下每一位来说考虑取和不取即可，但需要注意的是第 $k$ 个数无法被表示出来，那么换个思路，把问题分成两个部分，表示出 $1$ 到 $k-1$ 之间的数，以及 $k+1$ 到 $n$ 之间的数。

对于 $1$ 到 $k-1$ 之间的数我们只需一个循环判断一下能取到哪一位即可，对于 $k+1$ 到 $n$ 的数来说，我们只用利用我们已经得到的 $1$ 到 $k-1$ 的数便可得到 $k+1$ 到 $n$ 的数（从二进制的方面思考），具体程序实现如下。


------------
coding：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)
const int N=1e6+10;

int main()
{
	int T;
	scanf("%d",&T);
	while(T--){
		int n,k;
		int m=0,sum=0;
		scanf("%d%d",&n,&k);
		vector<int>a(26);a[++m]=2*k;
		int bit=1;
		while(sum<k-1){
			if(sum+bit<=k-1)a[++m]=bit,sum+=bit;
			else {a[++m]=k-1-sum,sum=k-1;break;}
			bit<<=1;
		}
		if(k<n){
			k=k+1;
			while(sum<n){
				a[++m]=k;
				sum+=k;
				k=sum+1;
			}
		}
		printf("%d\n",m);
		rep(i,1,m)printf("%d ",a[i]);
		printf("\n");
	}
	return 0;
} 
```

---

## 作者：hejianxing (赞：1)

[link](https://www.luogu.com.cn/problem/CF1965B)

# 题意

构造一个长度不超过 $25$ 的序列，满足子序列和包含 $1\sim n$ 中的所有数，除了 $k$。

$n,k\le 10^6$。

# 题解

考虑构造 $1\sim n$。显然是 $1,2,4,8,\dots,2^m,n-2^m$。原理是 $[1,x]+a=[1,x+a]$。

于是构造 $1\sim k-1$。

那么根据原理，接下来应当选第一个无法表示出来的数，即 $k+1$。然后这样一直加下去即可。

再观察 $k$ 空掉产生的影响。考虑第二次加进一个数，$k+(2k+1)=3k+1$ 似乎是无法表示出来的。所以需要加一个 $(3k+1)-(k+1)=2k$。这样每次加入的数产生的 $k+x$ 就恰好可以用 $2k+x'$ 来表示。

加入的数题解给的次数是 $\log_2k+\log_2\frac n k=\log_2 n$。反正大概就在这个量级。

时间复杂度 $O(T\log n)$。

# 实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1000005;
int T, n, k, m, a[N];
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k), m = 0, a[++m] = k * 2;
        int lim = 0, add = k + 1;
        for (int w = 1; lim < k - 1; w <<= 1)
            if (lim + w <= k - 1) a[++m] = w, lim += w;
            else a[++m] = k - 1 - lim, lim = k - 1;
        if (k < n) while (lim < n) a[++m] = add, lim += add, add = lim + 1;
        printf("%d\n", m);
        for (int i = 1; i <= m; i++) printf("%d ", a[i]);
        printf("\n");
    }
    return 0;
}
```

---

## 作者：yyz1005 (赞：1)

比较经典的题目。

题目大意：给定 $n,k$，构造一个长度不超过 $25$ 的数组 $\{a_n\}$，满足 $\forall i \le n,i \not= k,i \in N^*$ 有存在 $\{a_n\}$ 的子序列和为 $i$。同时不存在 $\{a_n\}$ 的子序列何为 $k$。

首先考虑**构造一个存在子序列和为 $1,2,3,\cdots,k-1$** 的数组。显然可以构造 $1,2,4,\cdots,2^{t},k-1-(2^{t+1}-1)$。使 $t$ 尽量大。

接下来考虑构造 $k+1,\cdots,n$。

维护一个 $sum = k-1,pos = k+1$。

只要 $sum \le n$，考虑为数组加入 $pos$，令 $sum \leftarrow sum+pos,pos \leftarrow sum+1$。

事实上，$sum$ 维护了前面所有数能构造的最大和 $x$，$x$ 满足了当前数组中所有数可以构造 $1,2,3,\cdots,k-1,k+1,\cdots,x$。$pos$ 维护了当前要加入的下一个数。

考虑最大长度 $S = \log_2k+\log_2(\dfrac{n}{k}) = \log_2n$，成立。

[Code](https://codeforces.com/contest/1966/submission/258451878)

---

## 作者：LiuIR (赞：1)

### 题目大意

[题目传送门](https://www.luogu.com.cn/problem/CF1965B)

给出 $n$ 和 $k$，要求你构造出一个长度不超过 $25$ 是数组 $a$，并满足一下条件：

+ $a$ 中任意子序列的和不为 $k$。
+ $a$ 中任意子序列的和为 $x$，其中 $x$ 为区间 $[1,n]$ 中不为 $k$ 的整数。

多组数据。

$1\le k\le n\le10^6$，$1\le\sum n\le10^7$。

### 题目分析

首先，对于固定的 $k$，满足 $n=m$ 的解也满足 $n<m$，所以我们可以默认 $n=10^6$。

如果没有 $a$ 中任意子序列的和不为 $k$ 的限制，那么答案为 $[1,2,4,8,\dots,2^{18},2^{19}]$。而我们的答案是这个数组的改良版。

设 $i$ 为满足 $2^i\le k$ 的最大整数，则我们的答案为 $[1,2,4,8,\dots,2^{i-1},2^{i+1},\dots,2^{18},2^{19},k-2^i,k+1,k+2^i+1]$，共有 $22$ 个元素。

接下来考虑证明：

1. 对于 $k$ 来说，因为 $1,2,4,8,\dots,2^{i-1},k-2^i$ 这些元素的和为 $k-1$ 且其他元素中没有 $1$，所以和不能为 $k$。

2. 对于满足 $x\le2^{i-1}$ 的 $x$ 来说，可以直接用二进制表示。

3. 对于满足 $2^{i-1}<x<k$ 的 $x$ 来说，我们可以先加上和为 $k-1$ 的所有元素，然后再删去和为 $k-x-1$ 的元素。因为 $2^{i-1}<x<k<2^i$，所以有 $k-x-1\le2^{i-1}$，所以 $k-1$ 和 $k-x-1$ 均能被表示，且能表示 $k-x-1$ 的集合被能表示 $k-1$ 的集合包含。

4. 对于满足 $x>k$ 的 $x$ 来说，我们可以加上 $k+1$ 这一元素，还有和为 $x-k-1$ 的所以元素。$x-k-1$ 可以直接用二进制表示，但若 $x-k-1$ 的构成中需要 $2^i$，则将 $k+1$ 替换为 $k+2^i+1$。

综上所述，该数组可以满足题目要求。

### 代码

注：代码中将上述讲解中的 $i$ 替换为 $pos$。

```c++
//Author:LIUIR
//Created: 2024.07.06:11:08:09 +08:00:00
//Last Modified: 2024.07.06:11:38:17 +08:00:00
#include <bits/stdc++.h>

const int N = 27;

int T, n, k, pos, tot, a[N];

signed main()
{
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d%d", &n, &k);
		pos = tot = 0;
		while(1 << (pos + 1) <= k)
			pos++;
		for (int i = 0; i <= 19; i++)if (i != pos)
			a[++tot] = 1 << i;
		a[++tot] = k - (1 << pos);
		a[++tot] = k + 1;
		a[++tot] = k + (1 << pos) + 1;
		printf("%d\n", tot);
		for (int i = 1; i <= tot; i++)
			printf("%d ", a[i]);
		printf("\n");
	}
	return 0;
}
```

---

