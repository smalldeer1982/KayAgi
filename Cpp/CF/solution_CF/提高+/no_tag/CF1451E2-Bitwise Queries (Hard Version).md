# Bitwise Queries (Hard Version)

## 题目描述

The only difference between the easy and hard versions is the constraints on the number of queries.

This is an interactive problem.

Ridbit has a hidden array $ a $ of $ n $ integers which he wants Ashish to guess. Note that $ n $ is a power of two. Ashish is allowed to ask three different types of queries. They are of the form

- AND $ i $ $ j $ : ask for the [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) of elements $ a_i $ and $ a_j $ $ (1 \leq i, j \le n $ , $ i \neq j) $
- OR $ i $ $ j $ : ask for the [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR) of elements $ a_i $ and $ a_j $ $ (1 \leq i, j \le n $ , $ i \neq j) $
- XOR $ i $ $ j $ : ask for the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of elements $ a_i $ and $ a_j $ $ (1 \leq i, j \le n $ , $ i \neq j) $

Can you help Ashish guess the elements of the array?

In this version, each element takes a value in the range $ [0, n-1] $ (inclusive) and Ashish can ask no more than $ n+1 $ queries.

## 说明/提示

The array $ a $ in the example is $ [0, 0, 2, 3] $ .

## 样例 #1

### 输入

```
4

0

2

3```

### 输出

```
OR 1 2

OR 2 3

XOR 2 4

! 0 0 2 3```

# 题解

## 作者：OMG_wc (赞：15)

只有 $n+1$ 次询问的机会，所以我们必须省吃俭用。显然不能用太多的`AND`和`OR`操作，因为这两个操作会丢失信息（可以理解成不存在逆元），而`XOR`是无损的。

那么我们就钦定 $a_1$ 为天选之子，然后异或其他所有数，得到一个数组 $c_i=a_1 \oplus  a_i$，这样一共消耗了 $n-1$ 次，只剩下 2 次机会了。而我们的目标很明确，只要求出 $a_1$，那其他数就都能通过 $a_i=a_1\oplus c_i$ 算出来。

注意题目还有一个条件，数的范围在 $[0,n-1]$ 之间，而一共有 $n$ 个数，那么也就是说......

要分两种情况：

- 所有数都不重复

  此时一定存在某个 $c_x=1$，某个 $c_y=n-2$ 。

  假设一共 $m$ 位数，$c_x=1$ 意味着 $a_x$ 前面的 $m-1$ 位都和 $a_1$ 相同，那么我们直接让 $a_1$ 和 $a_x$ 做一次`AND`或者`OR`操作就能找出 $a_1$ 的前 $m$ 位。（这里前指高位，后指低位）

  同理，$c_y=n-2$ 就能找出 $a_1$ 的最后一位，也是通过一次`AND`或者`OR`操作。

  这样，总操作 $n+1$ 次就找完了。

- 存在重复的数

  可能是和 $a_1$ 重复，这样会有一个 $c_x=0$ ，做一次`AND`或者`OR`操作就能确定 $a_1$ 的值。

  也可能是后面某两个数重复，即 $c_x=c_y$，开个数组记录每个数上一次出现的位置就能把他们找出来。

  找到后，通过做一次`AND`或者`OR`操作就能确定 $a_x$ 的值，然后计算出 $a_1$ 。

	这样，总操作 $n$ 次就找完了。

所以无论哪种情况，最多只需 $n+1$ 次询问，参考代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const int N = 100005;

int a[N], b[N];
int main() {
    int n;
    cin >> n;
    for (int i = 2; i <= n; i++) {
        printf("XOR %d %d\n", 1, i);
        fflush(stdout);
        scanf("%d", &a[i]);
    }
    for (int i = 2; i <= n; i++) {
        if (a[i] == 0) {
            printf("OR %d %d\n", 1, i);
            fflush(stdout);
            scanf("%d", &a[1]);
            goto M1;
        }
    }
    for (int i = 2; i <= n; i++) {
        if (b[a[i]]) {
            int x;
            printf("OR %d %d\n", b[a[i]], i);
            fflush(stdout);
            scanf("%d", &x);
            a[1] = x ^ a[i];
            goto M1;
        }
        b[a[i]] = i;
    }
    int x, y, t;
    for (int i = 2; i <= n; i++) {
        if (a[i] == 1) x = i;
        if (a[i] == n - 2) y = i;
    }
    printf("OR %d %d\n", 1, x);
    fflush(stdout);
    scanf("%d", &t);
    a[1] = t >> 1 << 1;
    printf("OR %d %d\n", 1, y);
    fflush(stdout);
    scanf("%d", &t);
    a[1] += t & 1;
M1:;
    for (int i = 2; i <= n; i++) a[i] ^= a[1];
    printf("!");
    for (int i = 1; i <= n; i++) {
        printf(" %d", a[i]);
    }
    puts("");
    return 0;
}
```





---

## 作者：蒟酱 (赞：5)

看着这到题的题解我感觉都写的很诡异，所以我决定贡献一发题解。
题目大意：有一个长度为 $n$ 的数组（ $n$ 是 $2$ 的倍数），有 $3$ 种操作，AND OR XOR，可以获得数组两个元素的 AND OR XOR 值，仅限 $n-1$ 次操作求原数组。

首先考虑以 $a_1$ 为基准求出 $a_1\oplus a_k$，这样只要求出 $a_1$ 就可以求出整个数组，这一步需要 $n-1$ 次操作。

因为只有 $n$ 个元素，元素的范围是 $[0,n-1]$，所以可以进行分类讨论：  
1.所有元素并不是互不相同。也就是说有重复的元素，这样只要找到相同的元素，对相同的元素进行 AND 操作就可以求出这个元素（因为知道了这两个元素和 $a_1$ 的异或值），又因为知道了所有元素和 $a_1$ 的 XOR，所以可以直接算出整个数组。考虑如何找到相同的元素，可以开个桶记录每个元素出现的次数。取最大的出现次数（这种情况下至少两次），然后进行一次查找就可以得到所有异或 $a_1$ 相同的元素也就是相同的元素，任意取两个询问 AND 就可以了。不过这里有个要注意的，如果 $a_1$ 恰好是重复的元素只会扫到 $1$ 个不一样的元素，取 $1$ 询问即可。  
2.所有元素互不相同。也就是是 $[0,n-1]$ 的全排列。考虑 XOR 的性质，相同就是 $0$，也就是说可以选择 $1$ 这个数，只有最后一位是 $1$，其他都是 $0$，也就是说如果 $a_1\oplus a_k=1$，$a_1$ 和 $a_k$ 只有最后一位不一样，可以通过 AND 操作求出前 $\log n-1$ 位。同理如果 $a_1\oplus a_k=\frac n2$，$a_1$ 和 $a_k$ 只有第一位不一样，可以通过 AND 操作求出后 $\log n-1$ 位。把两个结果组合以下（直接或起来）就可以得到 $a_1$。其实不一定要选择 $1$ 和 $\frac n2$，只要保证这两个数二进制下每位都至少有个数是 $0$ 就行。

code:
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
constexpr int kN=(1<<16)+7;
int xr[kN],n,cnt[kN];
using std::cin,std::cout,std::endl;
auto AND=[](int a,int b){cout<<"AND "<<(a)<<' '<<(b)<<endl;int t;cin>>t;return t;};
auto XOR=[](int a,int b){cout<<"XOR "<<(a)<<' '<<(b)<<endl;int t;cin>>t;return t;};
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n;cnt[0]=1;
	for(int i=2;i<=n;i++)cnt[xr[i]=XOR(1,i)]++;
	if(int p=std::max_element(cnt,cnt+n)-cnt;cnt[p]!=1){// 有重复
		std::basic_string<int>g;
		for(int i=2;i<=n;i++)if(xr[i]==p)g+=i;
		int ak=AND(g.size()==1?1:g.front(),g.back()),a1=ak^p;
		cout<<"! "<<a1;
		for(int i=2;i<=n;i++)cout<<' '<<(a1^xr[i]);
	}else{// 没重复
		int xp=-1,yp=-1,tx=1,ty=n>>1;
		for(int i=2;i<=n;i++){
			if(xr[i]==tx)xp=i;
			if(xr[i]==ty)yp=i;
		}
		int a1=AND(1,xp)|AND(1,yp);
		cout<<"! "<<a1;
		for(int i=2;i<=n;i++)cout<<' '<<(a1^xr[i]);
	}
	cout.flush();
	return 0;
}
```

---

## 作者：Scintilla (赞：3)

首先一个基本的思路是：我们可以先确定几个数，再把确定的数和其他的 $\text{XOR}$，就可以知道所有的数了。

我们知道，三个数可以通过询问两两的 $\text{AND}$ 和 $\text{XOR}$ 来知道（其中 $\text{XOR}$ 只用询问两次，因为其具有结合律）这样五次，总共就是 $n + 2$ 次，可以通过 E1。

为什么不三次询问出两个数呢，因为不能知道它们的顺序。

我们考虑对此方法进行优化。

发现还有一个重要的条件没用，那就是 $n = 2^k$ 及 $a_i \in [0, n - 1]$。不难发现，如果没有重复的话，那 $a$ 就必定是 $[0, n - 1]$ 的一个排列。

所以我们可以把 $\text{XOR}$ 操作提前，用 $n - 1$ 次询问 $a_1$ 和其他数的 $\text{XOR}$ 值，判断有没有重复的（即判断 $\text{XOR}$ 值中是否存在相同的数或 $0$）。

如果有的话，那就询问这两个数的 $\text{OR}$ 值，其答案就是这两个数。那么就知道了 $a_1$，进而就可以知道所有的数了。总询问次数为 $n$。

反之，这 $n - 1$ 个 $\text{XOR}$ 值肯定是 $[1, n - 1]$ 的排列。那么我们可以先找到与 $a_1$ $\text{XOR}$ 值为 $1$ 的数，询问它们的 $\text{OR}$ 值，确定 $a_1$ 二进制下除了最低一位以外的位数，再找到与 $a_1$ $\text{XOR}$ 值为 $2$ 的数，询问它们的 $\text{OR}$ 值，确定 $a_1$ 二进制下最低一位，那么就知道 $a_1$ 了，进而知道所有数。总询问次数为 $n + 1$。其实这里没必要指定，但是我认为指定后更容易理解。

代码太丑陋了，就不放了。

---

## 作者：EnofTaiPeople (赞：2)

此题本质与 CF1556D 相同，只是多了一个异或的询问。大家可以先看一下 [这篇文章](https://www.luogu.com.cn/blog/lwxde/solution-cf1556d)。

相比起来，多了一个异或的查询，看到只能问 $n+1$ 次，不难想到只有对每个 $2\le i\le n$ 询问 XOR 1 i，这时，我们只剩下 2 次询问次数，需要将 $a_1$ 求出来。不同的是，这题的值域是确定的，我们可以有目的地去询问。

先考虑非特殊情况，即前 n-1 次询问的结果都在 $[1,n-1]$ 之间，且没有重复，虽然没有与 $a_1$ 完全相等的数，但我们可以寻找与 $a_1$ 大部分相近或大部分相反的数进行询问。1 是很容易想到的，如果 $a_i\operatorname{xor}a_1=1$，这表示 $a_1$ 和 $a_i$ 在二进制下只有最后一位不相等，这时我们耗费一次询问，求他们的与，结果就是出去最后一位的 $a_1$。如何求 $a_1$ 的最后一位？考虑与 $a_1$ 只有最后一位相等的数字，即 $a_i\operatorname{xor}a_1=n-2$ 在询问他们的与，结果就是 $a_1$ 的最后一位。

既然有非特殊情况，那么就一定有特殊情况了。

- 若存在 $i$，使得 $a_i\operatorname{xor}a_1=0$，这时有 $a_i=a_1$，询问他们的与，结果就是 $a_1$；
- 若存在 $x,y,x\neq y$ 使得 $a_x\operatorname{xor}a_1=a_y\operatorname{xor}a_1$，这时有 $a_x=a_y$，询问 $a_x \& a_y$，得到 $a_x$，进而得到 $a_1$。

求出 $a_1$ 之后，由异或运算的自反律，可以轻易得到 $a_2$~$a_n$。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
int Xor[100005],i,n,Map[100005],a1,x;
bool flag=true;
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	for(i=2,cin>>n;i<=n;++i){
		cout<<"XOR 1 "<<i<<endl;cout.flush();cin>>Xor[i];
		if(flag)
			if(Map[Xor[i]]){
				cout<<"AND "<<Map[Xor[i]]<<" "<<i<<endl;
				cout.flush();cin>>x;a1=x^Xor[i];flag=false;
			}else if(Xor[i]==0){
				cout<<"AND 1 "<<i<<endl;cout.flush();
				cin>>a1;flag=false;
			}
		Map[Xor[i]]=i;
	}
	if(flag){
		for(i=2;i<=n;++i)
			if(Xor[i]==1){
				cout<<"AND 1 "<<i<<endl;cout.flush();
				cin>>x;a1|=x;
			}else if(Xor[i]==n-2){
				cout<<"AND 1 "<<i<<endl;cout.flush();
				cin>>x;a1|=x;
			}
	}
	for(i=2,cout<<"! "<<a1;i<=n;++i)
		cout<<" "<<(a1^Xor[i]);
	cout<<endl;
	return 0;
}
```

---

## 作者：The_Godfather (赞：1)

## Problem
[题目传送门](https://www.luogu.com.cn/problem/CF1451E1)

这里说明一下就是此题只是询问的次数与 easy 不同剩下操作都一样。

## Solution
数组一般有两种情况：
1. 数组内出现相同值。
2. 数组内没有相同的值。

- 所以对于情况一，若两个值 $a [ i ]$ 跟 $a [ j ]$ 相同，则他们与 $a [ 1 ]$ 的 xor 值 $x [ i ]$ 与 $x [ j ]$ 相同，此时询问 $a [ i ]$ 与 $a [ j ]$ 的 and 值，得到的就是 $a[ i ]$ 本身，又因为 $a [ 1 ]$ xor $a [ i ]$ = $x [ i ]$，则 $a[ 1 ]$ = $a [ i ]$ xor $x [ i ]$，确定了 $a [ 1 ]$，有已知 $a [ 1 ]$ 与剩余的值的 xor 值，因此确定了整个数组，共 $n$ 次查询。同时，若两个相等的数中有一个 $a [ 1 ]$，则可以通过 $x [ i ]$ 是否等于 0 来判断。
- 对于情况二，因为 0 到 $n-1$ 的数都有，所以必定会有 $a [ i ]$ xor $a [ j ]$ = $n - 1$，所以 $a [ 1 ]$ = $a [ 1 ]$ and $a [ i ]$ + $a [ 1 ]$ and $a [ j ]$，通过两次询问得到 $a [ 1 ]$，共 $n + 1$ 次询问，所以最多 $n + 1$ 次询问即可确定整个数组。



## Code

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define best 131
#define INF 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int>
#define lowbit(x) x & -x
#define inf 0x3f3f3f3f
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const double pai = acos(-1.0);
const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
const double eps = 1e-9;
const int N = 1e6 + 10;
int t, n, m, k, d, x[maxn], a[maxn];
map<int, int> mp;
int ask(int i, int j, int f)
{
    if (f == 1)
    {
        cout << "AND " << i << " " << j << endl;
        cout.flush();
    }
    else if (f == 2)
    {
        cout << "OR " << i << " " << j << endl;
        cout.flush();
    }
    else if (f == 3)
    {
        cout << "XOR " << i << " " << j << endl;
        cout.flush();
    }
    int x;
    cin >> x;
    return x;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 2; i <= n; i++)
        x[i] = ask(1, i, 3);
    int flag = -1;
    for (int i = 2; i <= n; i++)
    {
        if (x[i] == 0)
        {
            flag = ask(1, i, 1);
            break;
        }
        if (mp.count(x[i]))
        {
            int tmp = mp[x[i]];
            flag = ask(tmp, i, 1);
            flag = flag ^ x[i];
            break;
        }
        mp[x[i]] = i;
    }
    if (flag == -1)
    {
        mp.clear();
        for (int i = 2; i <= n; i++)
        {
            if (mp.count((n - 1) ^ x[i]))
            {
                int num1 = mp[(n - 1) ^ x[i]];
                int num2 = i;
                flag = 0;
                flag += ask(1, num1, 1);
                flag += ask(1, num2, 1);
                break;
            }
            mp[x[i]] = i;
        }
    }
    a[1] = flag;
    for (int i = 2; i <= n; i++)
        a[i] = a[1] ^ x[i];
    cout << "!";
    cout.flush();
    for (int i = 1; i <= n; i++)
        cout << " " << a[i], cout.flush();
    cout << endl;
    return 0;
}
```

---

## 作者：zztqwq (赞：1)

题目要求 $n+1$ 次操作，那么大概可以猜出有一步是找一个数把所有数都做一个神秘操作。

首先用 $a_1$ 把 $a_i\oplus a_1\;(1<i\le n)$ 都弄出来，然后分几种情况讨论：

1. $a_i\oplus a_1$ 存在 $0$，假设这个位置为 $p$，那么就可以做一次 `AND p 1` 得到 $a_1$，再将所有 $a_i\oplus a_1$ 异或一遍 $a_1$ 即可；
2. $a_i\oplus a_1$ 存在相同的值，设这两个下标为 $x,y$，那么做一次 `AND x y` 得到 $a_x,a_y$，异或出 $a_1$，进一步就可以得到所有 $a_i$；
3. $a_i\oplus a_1$ 不存在重复的值，那么这个时候 $a$ 是一个 $0$ 到 $n-1$ 的排列，找到满足 $a_1\oplus a_p=n-1$ 的位置 $p$，不难发现 $a_p$ 本质上就是 $a_1$ 的补集，那么对于任意位置都有 $(a_i\And a_p)+(a_i\And a_1)=a_i$，随便找一个位置 $x$ 求出 $a_x$ 的值然后再带到 $a_1$ 中即可得到所有 $a_i$。

1、2 的操作次数是 $n$，3 的操作次数是 $n+1$，满足条件。

```cpp
const int N=1<<18;
int x[N],a[N];
map<int,int> vis;
int main()
{
	int n=read();
	for(int i=2;i<=n;i++)
	{
		printf("XOR %d %d\n",1,i);
		fflush(stdout);
		x[i]=read();
	}
	for(int i=2;i<=n;i++)
	{
		if(x[i]==0)
		{
			printf("AND %d %d\n",1,i);
			fflush(stdout);
			a[1]=read();
			printf("! %d",a[1]);
			for(int i=2;i<=n;i++)printf(" %d",(a[1]^x[i]));
			fflush(stdout);
			return 0;
		}
		else if(vis[x[i]])
		{
			int j=vis[x[i]];
			printf("AND %d %d\n",i,j);
			fflush(stdout);
			a[i]=a[j]=read();
			a[1]=a[i]^x[i];
			printf("! %d",a[1]);
			for(int i=2;i<=n;i++)printf(" %d",(a[1]^x[i]));
			fflush(stdout);
			return 0;
		}
		vis[x[i]]=i;
	}
	int p=0;
	for(int i=2;i<=n;i++)if(x[i]==n-1){p=i;break;}
	if(p!=2)
	{
		printf("AND %d %d\n",1,2);
		fflush(stdout);
		a[2]+=read();
		printf("AND %d %d\n",p,2);
		fflush(stdout);
		a[2]+=read();
		a[1]=a[2]^x[2];
		for(int i=3;i<=n;i++)a[i]=a[1]^x[i];
		printf("!");
		for(int i=1;i<=n;i++)printf(" %d",a[i]);
		fflush(stdout);
	}
	else
	{
		
		printf("AND %d %d\n",1,3);
		fflush(stdout);
		a[3]+=read();
		printf("AND %d %d\n",p,3);
		fflush(stdout);
		a[3]+=read();
		a[1]=a[3]^x[3];
		for(int i=2;i<=n;i++)
		{
			if(i==3)continue; 
			a[i]=a[1]^x[i];
		}
		printf("!");
		for(int i=1;i<=n;i++)printf(" %d",a[i]);
		fflush(stdout);
	}
	return 0;
}
//zzt qwq
```

---

## 作者：dead_X (赞：1)

## 前言
我用两种完全不同的方法切了 E1 和 E2，因此题解也会同时介绍两种方法。
## 思路
请忘掉 $\texttt{E1}$ 的一切思路。

我们先求出 $a_1\oplus a_2,a_1\oplus a_3,\cdots,a_1\oplus a_n$。

如果这些数里有重复的，我们是可以探测出来的。

证明：重复的一方是 $1$ 则有一个异或是 $0$，不然有两个异或相同。

如果有重复，我们直接求这两个重复的 $\&$ 或者 $|$ ，就能求出这个数，然后求出 $a_1$，然后求出所有数。

**这部分的询问次数是 $(n-1)+1=n$ 次**

如果没有重复，由于所有数在 $[0,2^n)$ 的范围，所有数必定覆盖了 $[0,2^n) $。

那么它们和 $a_1$ 的异或，也必定覆盖了 $(0,2^n)$。

显然我们找一个异或为 $1$ 的 $\&$ 一下可以确定 $a_1$ 的前几位。

找一个异或为 $2$ 的 $\&$ 一下可以确定 $a_1$ 的最后一位。

因此你可以确定 $a_1$。

**这部分的询问次数是 $(n-1)+2=(n+1)$ 次**
## 代码
```
#include<bits/stdc++.h>
#define mp make_pair
#define pi pair<int,int>
#define pb push_back
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[1000003];
int vis[1000003];
int main()
{
	int n=read();
	vis[0]=1;
	int tmpx=0,tmpy=0,tmpz=0,tmpw=0;
	for(int i=2; i<=n; i++)
	{
		printf("XOR 1 %d\n",i);
		fflush(stdout);
		a[i]=read();
		if(vis[a[i]]) tmpx=vis[a[i]],tmpy=i;
		else vis[a[i]]=i;
		if(a[i]==1) tmpz=i;
		if(a[i]==2) tmpw=i;
	}
	if(tmpx)
	{
		printf("AND %d %d\n",tmpx,tmpy);
		fflush(stdout);
		a[1]=read()^a[tmpx];
		for(int i=2; i<=n; i++) a[i]^=a[1];
	}
	else
	{
		printf("AND 1 %d\n",tmpz);
		fflush(stdout);
		int qwq=read();
		printf("AND 1 %d\n",tmpw);
		fflush(stdout);
		int awa=read();
		if(awa&1) ++qwq;
		a[1]=qwq;
		for(int i=2; i<=n; i++) a[i]^=a[1];
	}
	printf("! ");
	for(int i=1; i<=n; i++) printf("%d ",a[i]);
	fflush(stdout);
	return 0;
}
```

---

## 作者：__ikun__horro__ (赞：0)

## Solution

可以有 $\operatorname{AND}$ 、$\operatorname{OR}$、$\operatorname{XOR}$ 三种运算，我们先来看表格。

| $A=$ | $B=$ | $\operatorname{AND}$ | $\operatorname{OR}$ | $\operatorname{XOR}$ |
| :-: | :-: | :-: | :-: | :-: |
| $0$ | $0$ | $0$ | $0$ | $0$ |
| $0$ | $1$ | $0$ | $1$ | $1$ |
| $1$ | $0$ | $0$ | $1$ | $1$ |
| $1$ | $1$ | $1$ | $1$ | $0$ |

可以发现，大多数情况 $\operatorname{AND}$ 运算的值都为 $0$，就不知道是哪种情况。$\operatorname{OR}$ 运算也是如此，大多数情况它的值为 $1$。

所以我们主要用 $\operatorname{XOR}$ 进行运算。我们可以先求出 $a_1 \oplus a_{2 \sim n}$ 的值记为 $x_{2 \sim n}$，然后求出 $a_1$ 的值，这时 $a_i = a_i \oplus a_1 \oplus a_1$ 也就是 $x_i \oplus a_1$。

那么如何求出 $a_1$ 呢？我们可以开始愉快地分讨：

- $x_2 x_3 \cdots x_n = 0$，找出 $p$ 使 $x_p = 0$，此时 $a_1 = a_p$，$a_1 \operatorname{AND} a_p$ 的值就是 $a_1$。
- 存在 $x_i = x_j$，此时 $a_i = a_j$，$a_i \operatorname{AND} a_j$ 的值就是 $a_i$ 的值，那么 $a_1 = a_1 \oplus a_i \oplus a_i = x_i \oplus a_i$。
- $\textrm{Otherwise}$，$x_{2 \sim n}$ 就是 $1 \sim n - 1$ 的一个排列，我们找出 $i$、$j$ 分别满足 $x_i = 1$ 和 $x_j = 2$。此时，$a_1 \operatorname{AND} a_i$ 就是 $a_1$ 去掉倒数第一位的结果，$a_1 \operatorname{AND} a_j$ 就是 $a_1$ 去掉倒数第二位的结果，把两个答案按位或，就是 $a_1$ 的值。

## Code

```cpp
#include <iostream>
#include <map>
#include <cstring>

using namespace std;

const int N = (2 << 16) + 5;

int n, a[N];

signed main() {
	cin >> n;
	int f = 1;
	for (int i = 2; i <= n; i++) {
		cout << "XOR 1 " << i << "\n";
		cout.flush();
		cin >> a[i];
		if (a[i] == 0) f = 0;
	}
	if (f == 0) {
		int pos;
		for (int i = 2; i <= n; i++) {
			if (a[i] == 0) {
				pos = i;
				break;
			}
		}
		cout << "AND 1 " << pos << "\n";
		cout.flush();
		cin >> a[1];
		for (int i = 2; i <= n; i++) {
			a[i] ^= a[1];
		}
	} else {
		map<int, int> mp;
		for (int i = 2; i <= n; i++) mp[a[i]]++;
		if (mp.size() != n - 1) {
			int vis[N];
			memset(vis, 0, sizeof vis);
			for (int i = 2; i <= n; i++) {
				if (vis[a[i]]) {
					int j = vis[a[i]];
					cout << "AND " << i << " " << j << "\n";
					cout.flush();
					cin >> a[1];
					a[1] ^= a[i];
					break;
				}
				vis[a[i]] = i;
			}
			for (int i = 2; i <= n; i++) {
				a[i] ^= a[1];
			}
		} else {
			int pos[N];
			for (int i = 2; i <= n; i++) if (a[i] <= 2) pos[a[i]] = i;
			int x, y;
			cout << "AND 1 " << pos[1] << "\n";
			cout.flush();
			cin >> x;
			cout << "AND 1 " << pos[2] << "\n";
			cout.flush();
			cin >> y;
			a[1] = x | y;
			for (int i = 2; i <= n; i++) {
				a[i] ^= a[1];
			}
		}
	}
	cout << "! ";
	for (int i = 1; i <= n; i++) {
		cout << a[i] << " ";
	}
	return 0;
}
```

---

## 作者：_lgh_ (赞：0)

首先肯定可以先用 $n-1$ 次异或操作，求出 $a_1$ 和其他位置的异或值，这样只需要知道 $a_1$ 就可以知道所有的值。

于是问题转化为怎么在两次操作内用三种操作求出 $a_1$。

首先如果有两个位置的异或值是一样的，说明这两个位置的值是一样的。于是对这两个位置做一次 AND 或者 OR 就可以知道值，进而推出所有值。

其次，因为所有位置的异或值都不一样，说明每个值出现了 **恰好一次**。考虑如果 $x\oplus y=1$，说明 $x$ 和 $y$ 只有最低位不同。因此找出这个位置，求出 $a_1$ 除了最后一位的值。那么求最后一位的值只需要找其中一个异或值的最后一位为 $0$ 的位置就可以了。

```cpp
signed main() {
    int n; rd(n);
    t[0]=1;
    for(int i=2; i<=n; i++) cout<<"XOR 1 "<<i<<endl,cin>>c[i],t[c[i]]++;
    for(int i=0; i<n; i++)
        if(t[i]>=2) {
            int w1=-1,w2=-1;
            for(int j=1; j<=n; j++)
                if(c[j]==i) {
                    if(w1==-1) w1=j;
                    else {
                        w2=j;
                        break;
                    }
                }
            assert(w1!=w2);
            cout<<"AND "<<w1<<' '<<w2<<endl,cin>>a[w1];
            a[1]=a[w1]^c[w1];
            cout<<"! "<<a[1]<<' '; for(int i=2; i<=n; i++) a[i]=a[1]^c[i],cout<<a[i]<<' '; cout<<'\n';

            return 0;
        }
    int w=0;
    for(int i=2; i<=n; i++) if(c[i]==1) w=i;
    int res1;
    cout<<"AND 1 "<<w<<endl,cin>>res1;
    int res2;
    for(int i=2; i<=n; i++) if(c[i]==2) w=i;
    cout<<"AND 1 "<<w<<endl,cin>>res2;
    assert(res1+res2%2==res1|res2);
    a[1]=res1+res2%2;
    cout<<"! "<<a[1]<<' '; for(int i=2; i<=n; i++) a[i]=a[1]^c[i],cout<<a[i]<<' '; cout<<'\n';
    return 0;
}
```

---

## 作者：_lxy_ (赞：0)

### 分析

首先可以用 $n-1$ 次询问得出第 $a_1$ 和其它数的异或值，然后只要求出 $a_1$ 的值整个数组就都出来了。

分两种情况讨论：

1. 该数组中的数两两不同

   此时必有 $i,j$ 满足 $a_1 \oplus a_i=1,a_1 \oplus a_j=n-2$，也就是只有最后一位和 $a_1$ 不同的和只有最后一位和 $a_1$ 相同的，此时容易求出 $a_1$ 的值。

2. 该数组中的数有重复

   若有与 $a_1$ 重复的，直接询问它和 $a_1$ 的与就能得出 $a_1$ 的值；

   若有两个不是 $a_1$ 的数相等，即 $a_1 \oplus a_i=a_1 \oplus a_j$，此时询问 $a_i \oplus a_j$ 即可得出 $a_i$ 的值，再异或上 $a_1 \oplus a_i$ 的值就能得出 $a_1$ 的值。

得出 $a_1$ 的值后，就可以用 $a_i=a_1 \oplus (a_1 \oplus a_i)$ 算出每一个数的值。

### 代码

```cpp
#include <bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
#define fre(z) freopen(z".in","r",stdin),freopen(z".out","w",stdout)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;
typedef pair<int,int> Pair;
const int inf=2139062143;
// static char buf[1000000],*p1=buf,*p2=buf,obuf[1000000],*p3=obuf;
// #define gc() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
// #define getchar gc
inline void qread(){}template<class T1,class ...T2>
inline void qread(T1 &a,T2&... b)
{
    register T1 x=0;register bool f=false;char ch=getchar();
    while(ch<'0') f|=(ch=='-'),ch=getchar();
    while(ch>='0') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    x=(f?-x:x);a=x;qread(b...);
}
template<class T> T qmax(T x,T y){return x>y?x:y;}
template<class T,class ...Arg> T qmax(T x,T y,Arg ...arg){return qmax(x>y?x:y,arg...);}
template<class T> T qmin(T x,T y){return x<y?x:y;}
template<class T,class ...Arg> T qmin(T x,T y,Arg ...arg){return qmin(x<y?x:y,arg...);}
template<class T> T randint(T l,T r){static mt19937 eng(time(0));uniform_int_distribution<T>dis(l,r);return dis(eng);}
const int MAXN=1e5+7;
int n,a[MAXN],p[MAXN];
int main()
{
    scanf("%d",&n);int i,j;
    for(i=2;i<=n;i++) 
    {
        printf("XOR %d %d\n",1,i);fflush(stdout);
        scanf("%d",&a[i]);
    }
    for(i=2;i<=n;i++)
    {
        if(!a[i]) 
        {
            printf("AND %d %d\n",1,i);fflush(stdout);
            scanf("%d",&a[1]);goto label;
        }
    }
    for(i=2;i<=n;i++)
    {
        if(p[a[i]])
        {
            printf("AND %d %d\n",p[a[i]],i);fflush(stdout);
            int x;scanf("%d",&x);a[1]=x^a[i];goto label;
        }p[a[i]]=i;
    }
    int p1,p2;p1=p2=1;
    for(i=2;i<=n;i++)
    {
        if(a[i]==1) p1=i;
        if(a[i]==n-2) p2=i;
    }
    printf("OR %d %d\n",1,p1);fflush(stdout);
    int x;scanf("%d",&x);a[1]=x-(x&1);
    printf("OR %d %d\n",1,p2);fflush(stdout);
    scanf("%d",&x);a[1]+=(x&1);
    label:;printf("! %d",a[1]);
    for(i=2;i<=n;i++) printf(" %d",a[i]^a[1]);
    return 0;
}
```



---

## 作者：Sol1 (赞：0)

一个很容易想到的是用 $n-1$ 次询问求出 $a_1\text{ xor } a_i(2\leq i\leq n)$，这样问题变为用 $2$ 次询问确定出任意一个数。

考虑到有 $a_{i}\text{ and }a_j$ 和 $a_{i}\text{ xor }a_j$ 就可以求出 $a_{i}\text{ or }a_j$，所以不妨只询问 $\text{and}$。

那么如果询问 $\text{and}$，就可以确定出所有 $\text{xor}$ 值为 $0$ 的位。

由抽屉原理，$(a_i\oplus a_j)\& (a_j\oplus a_k)\& (a_k\oplus a_i)=0$，所以问出两两之间的 and 就可以了，但是这样需要 3 次询问。

考虑怎么省掉一次，发现有两种情况：

1. 存在 $a_i\oplus a_j=0$，这时 $a_i\&a_k=a_j\&a_k$。
2. 存在 $a_i\oplus a_j=2^n-1$，这时 $a_i\&a_j=0$。

只有所有数两两不同时没有 1，容易发现此时必然出现 2。

然后就做完了。

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

int x[66666], n, idx[66666], a[66666];

inline void GetXor() {
	for (int i = 2;i <= n;i++) {
		cout << "XOR " << 1 << " " << i << endl;
		cin >> x[i];
	}
}

inline void GetArray(int i, int j, int k, int aij, int ajk, int aki) {
	int xij = x[i] ^ x[j], xjk = x[j] ^ x[k], xki = x[k] ^ x[i];
	for (int idx = 0;idx < n;idx++) {
		if (!((xij >> idx) & 1)) {
			if ((aij >> idx) & 1) {
				a[i] |= (1 << idx);
				a[j] |= (1 << idx);
			}
			a[k] |= (a[i] & (1 << idx)) ^ (xki & (1 << idx));
		}
		if (!((xjk >> idx) & 1)) {
			if ((ajk >> idx) & 1) {
				a[j] |= (1 << idx);
				a[k] |= (1 << idx);
			}
			a[i] |= (a[j] & (1 << idx)) ^ (xij & (1 << idx));
		}
		if (!((xki >> idx) & 1)) {
			if ((aki >> idx) & 1) {
				a[k] |= (1 << idx);
				a[i] |= (1 << idx);
			}
			a[j] |= (a[i] & (1 << idx)) ^ (xij & (1 << idx));
		}
	}
	for (int l = 1;l <= n;l++) a[l] = a[i] ^ x[i] ^ x[l];
	cout << "! ";
	for (int i = 1;i <= n;i++) cout << a[i] << " ";
	cout << endl;
}

inline void WorkEqual(int i, int j) {
	int k;
	if (i == 1 && j == 2) k = 3;
	else if (i == 1) k = 2;
	else k = 1;
	int aij, ajk, aki;
	cout << "AND " << k << " " << j << endl;
	cin >> ajk;
	aki = ajk;
	cout << "AND " << i << " " << j << endl;
	cin >> aij;
	GetArray(i, j, k, aij, ajk, aki);
}

inline void WorkAnd0(int i, int j) {
	int k;
	if (i == 1 && j == 2) k = 3;
	else if (i == 1) k = 2;
	else k = 1;
	int aij, ajk, aki;
	cout << "AND " << k << " " << j << endl;
	cin >> ajk;
	cout << "AND " << i << " " << k << endl;
	cin >> aki;
	aij = 0;
	GetArray(i, j, k, aij, ajk, aki);
}

inline void Solve() {
	for (int i = 1;i <= n;i++) {
		if (idx[x[i]]) {
			WorkEqual(idx[x[i]], i);
			return;
		}
		idx[x[i]] = i;
	}
	memset(idx, 0, sizeof(idx));
	for (int i = 1;i <= n;i++) {
		if (idx[(n - 1) ^ x[i]]) {
			WorkAnd0(idx[(n - 1) ^ x[i]], i);
			return;
		}
		idx[x[i]] = i;
	}
}

int main() {
	cin >> n;
	GetXor();
	Solve();
	#ifdef CFA_44
	while (1);
	#endif
	return 0;
}

```

---

## 作者：FjswYuzu (赞：0)

请丢掉 E1 的做法。我们发现我们完全没有用 $n$ 是 $2$ 的幂次，值域在 $[0,n-1]$ 的消息。

首先注意到数的数量是 $n$，值域大小也是 $n$。所以说这个序列要么有重复元素，要么是一个 $0 \sim n-1$ 的排列。

首先求 $1$ 对其他数的 $\operatorname{xor}$ 值无可避免。于是先求出来。

发现如果整个序列有相同的值，显然有一个数对 $(x,y)$ 满足两个数与 $a_1$ 异或值相等。随便找一找，如果存在这个数对，我们就能通过一次 $\operatorname{and}$ 或者 $\operatorname{or}$ 操作求出 $a_x,a_y$。然后反代回去求出整个序列。操作次数 $n$。

顺便注意一下有没有一个数满足这个数与 $a_1$ 异或值为 $0$。同样的做法求一发 $a_1$ 即可。

重要的是这个排列怎么求。实际上也很简单。因为这是一个排列，所以说一定存在两个数 $x,y$，使得 $a_1 \operatorname{xor} a_x = n-1,a_1 \operatorname{xor} a_y = 1$。

考虑这样个玩意儿的意义。首先第二个式子可以发现，$a_1,a_y$ 一定只相差 $1$。进行一个 $\operatorname{and}$ 操作可以知道 $a_1$ 除奇偶性的所有前面的信息。

两个式子连起来一看，发现 $a_x$ 与 $a_y$ 的奇偶性一定相同。所以我们也能知道 $a_1$ 的奇偶性。具体就询问 $a_x \operatorname{and} a_y$，其奇偶性与 $a_1$ 不同。综上，操作次数 $n+1$。

至此，我们解决了这道题。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int val,pos;
	node(int V=0,int P=0){val=V,pos=P;}
	bool operator < (node ano) const {return val<ano.val;}
}cf[(1<<16)+5];
int e2[(1<<16)+5],n,a[(1<<16)+5];
int main(){
	scanf("%d",&n);
	for(int i=2;i<=n;++i)
	{
		printf("XOR 1 %d\n",i);
		fflush(stdout);
		scanf("%d",&e2[i]);
		cf[i-1]=node(e2[i],i);
	}
	sort(cf+1,cf+n);
	for(int i=2;i<n;++i)
	{
		if(cf[i].val==cf[i-1].val)
		{
			int x=cf[i].pos,y=cf[i-1].pos;
			printf("AND %d %d\n",x,y);
			fflush(stdout);
			scanf("%d",&a[x]);
			a[y]=a[x];
			a[1]=a[x]^e2[x];
			for(int j=2;j<=n;++j)
			{
				if(a[j])	continue;
				a[j]=a[1]^e2[j];
			}
			putchar('!');
			for(int j=1;j<=n;++j)	printf(" %d",a[j]);
			puts("");
			fflush(stdout);
			return 0;
		}
	}
	for(int i=2;i<=n;++i)
	{
		if(e2[i]==0)
		{
			printf("AND 1 %d\n",i);
			fflush(stdout);
			scanf("%d",&a[1]);
			for(int j=2;j<=n;++j)	a[j]=a[1]^e2[j];
			putchar('!');
			for(int j=1;j<=n;++j)	printf(" %d",a[j]);
			puts("");
			fflush(stdout);
			return 0;
		}
	}
	int x=0,y=0;
	for(int i=2;i<=n;++i)
	{
		if(e2[i]==n-1)	x=i;
		if(e2[i]==1)	y=i;
	}
	printf("AND %d %d\n",min(x,y),max(x,y));
	fflush(stdout);
	int p;
	scanf("%d",&p);
	p%=2;
	if(p==1)	p=0;
	else	p=1;
	printf("AND 1 %d\n",y);
	fflush(stdout);
	int q;
	scanf("%d",&q);
	q+=p;
	a[1]=q;
	for(int i=2;i<=n;++i)	a[i]=a[1]^e2[i];
	putchar('!');
	for(int i=1;i<=n;++i)	printf(" %d",a[i]);
	puts("");
	fflush(stdout);
	return 0;
}
```

---

## 作者：lgswdn_SA (赞：0)

赛场只做出来 E1。首先 E1 的思路非常明确。先用 5 步求出 $a_1,a_2,a_3$，然后再询问 $a_i \text { xor } a_1$ 的值，求出整个序列，一共花了 $n+2$ 步。

E2 怎么优化？我一开始是觉得说这 5 步可以再简化啥的，但是目前来说是无法再降低步数的。我们发现我们还没有用到 $n=2^k$ 的条件，不过也不知道怎么用。

我们发现，如果有两个相等的数，那么根本不需要这么多步我们就可以算出来这两个数的值。于是我们先求出所有 $a_1\text{ xor }a_i$ 然后判断是否存在两个数 $i,j$ 使得 $a_i=a_j$。如果存在，我们找到这两个数，通过一次 $\text{and}$ 或者 $\text{or}$ 就可以知道这两个数是什么。接着我们用已知的信息再得到 $a_1$ 和整个序列。一共只需要 $n$ 步。

如果没有相同的呢？如果没有，意味着这个序列有一个好的性质，就是是一个全排列。一个更好的性质，由于存在 $x$ 使得 $a_1+a_x=n-1$，又因为 $n-1$ 是一个二的整次幂见一，所以我们可以直接知道 $a_1\operatorname{and} a_x$ 的值为 $0$ 以及 $a_1\operatorname{or}a_x$ 的值为 $n-1$。所以就不需要再问询这些东西了。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=1e6+9;

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int query(int i,int j,int opt) {
	if(opt==1) printf("AND %d %d\n",i,j);
	else if(opt==2) printf("OR %d %d\n",i,j);
	else if(opt==3) printf("XOR %d %d\n",i,j);
	fflush(stdout);
	return read();
}
bool bit(int s,int i) {
	return (1<<i)&s;
}
int calc(int x,int xorx,int ret=0) {
	rep(h,0,16) {
		int r=(1<<h);
		if(bit(x,h)&&!bit(xorx,h)) ret+=r;
		else if(bit(xorx,h)&&!bit(x,h)) ret+=r;
	}
	return ret;
}
int n,a[N],x[N],cnt[N],rp=-1;

int main() {
	n=read();
	rep(i,2,n) x[i]=query(1,i,3), cnt[x[i]]++;
	cnt[0]++;
	rep(i,0,n) if(cnt[i]>1) {rp=i; break;}
	if(rp!=-1) {
		vector<int>vec;
		rep(i,1,n) if(x[i]==rp) vec.push_back(i);
		int res=query(vec[0],vec[1],1);
		a[1]=calc(res,x[vec[0]]);
		rep(i,2,n) a[i]=calc(a[1],x[i]);
		putchar('!');
		rep(i,1,n) printf(" %d",a[i]);
	}
	else {
		rep(i,1,n) if(x[i]==n-1) {rp=i; break;}
		int tp=(rp==2 ? 3 : 2);
		int and1t=query(1,tp,1),andrt=query(rp,tp,1);
		rep(h,0,30) {
			int g=(1<<h);
			if(bit(and1t,h)) {
				a[1]+=g;
			} else {
				if(!bit(x[tp],h)) {
					a[rp]+=g;
				} else {
					if(!bit(andrt,h)) {
						a[1]+=g;
					} else {
						a[tp]+=g, a[rp]+=g;
					}
				}
			}
		}
		rep(i,2,n) a[i]=calc(a[1],x[i]);
		putchar('!');
		rep(i,1,n) printf(" %d",a[i]);
	}
	return 0;
}
```

---

## 作者：AsunderSquall (赞：0)

考场上没做出来，现在用大号过了，所以用大号发题解（雾）  

[官方题解通道](https://codeforces.com/blog/entry/84885)  

[E1题解通道](https://www.luogu.com.cn/blog/FOOLISH-JUSTIN/cf1451e1-ti-xie)
# 题意  
这是一道交互题  
有一个长度为$n$的序列（$n$为$2$的幂次），每个数在$[0,n-1]$内  
每次你可以询问任意两个数之间的或、与或者异或  
你需要在$n+1$次询问中得到序列并输出  

# 题解  
如果你看了E1的题解，会发现根本没有用上$n$为$2$的幂次这个条件  
现在我们考虑把他用上  

看到$n=2^k$，你能想到什么？  
~~（我在考场上只想到了什么FFT，分治，然而他们都是$\text n \log \text n$级别的）~~  
事实上，结合每个数再$[0,n-1]$这个条件，可以搞一搞

XOR询问可以判断出有没有重复的  
我们进行$n-1$次XOR询问，$a_1 \oplus a_2,a_1 \oplus a_3,a_1 \oplus a_4,\cdots a_1 \oplus a_n$，结果设为$b_2,b_3,\cdots b_n$  
如果$\exists i\ne j,b_i=b_j$  ，那么说明$a_i=a_j$，证明显然。  
那么这个时候我们再询问`AND i j`，就可以得到$a_i$，然后再反推出$a_1$，进而可以得到整个序列，这样子总共用了$n$次询问  

如果不存在，那么说明每个$a_i$均不相同，由于值域只有$n$个，那么一定全部覆盖。  
所以一定$\exists i,j,a_i \oplus a_j=n-1$，那么这个情况下肯定有$a_i \&a_j=0$，我们考虑E1的情况，这就省下了一次询问，只需要再2次询问就能确定3个值，进而推出所有值  
这样子总共用了$n+1$次询问  

代码：讲个笑话：把一个`A`打成`B`调了1h+  
```cpp
#include<bits/stdc++.h>
#define int long long
#define rd(x) x=read()
using namespace std;
const int N=2e6+5;
const int M=5005;
const int mod=998244353;
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int ksm(int x,int y){int ret=1;while (y){if (y&1) ret=(ret*x)%mod;x=(x*x)%mod;y>>=1;}return ret;}

int n,q,sum,id1,id2;
int b[N];
int a[N];
int c[N];
int gb(int x,int i)
{
	//找到x的第i位
	x>>=i;
	return x&1; 
}

signed main()
{
	cin>>n;
	for (int i=2;i<=n;i++)
	{
		cout<<"XOR 1 "<<i<<endl;
		cin>>b[i];
		if (c[b[i]]) id1=c[b[i]],id2=i;//说明有重复的
		else  c[b[i]]=i;
	}
	if (id1)
	{
		//说明有重复的
		//b[id1]=b[id2]
		cout<<"AND "<<id1<<" "<<id2<<endl;cin>>b[n+1];
		a[id1]=b[n+1];a[1]=a[id1]^b[id1];
		for (int i=2;i<=n;i++) a[i]=a[1]^b[i]; 
	} else if (c[0])
	{
		//说明有重复的，而且是和a[1]重复
		//a[c[0]]=a[1]
		cout<<"AND 1 "<<c[0]<<endl;cin>>a[1];
		for (int i=2;i<=n;i++) a[i]=a[1]^b[i]; 
	}else
	{
		//说明没有重复的，覆盖整个值域
		//以c[n/2]和c[n/2-1]为例吧
		id1=c[n/2];id2=c[n/2-1];
		int a1,a2,a3,a4,a5;
		a1=b[id1];a2=b[id2];a5=0;
		cout<<"AND 1 "<<id1<<endl;cin>>a3;
		cout<<"AND 1 "<<id2<<endl;cin>>a4;
		for (int i=0;i<=15;i++)
    	{
    	    //考虑第i位
    	    for (int A=0;A<=1;A++)
    	    for (int B=0;B<=1;B++)
    	    for (int C=0;C<=1;C++)
    	    {
    	        if ((A^B)==gb(a1,i)) if ((A^C)==gb(a2,i))
    	        if ((B&A)==gb(a3,i)) if ((C&A)==gb(a4,i))
    	        if ((B&C)==gb(a5,i))
    	        {
    	            a[1]|=(A<<i);
                    a[id1]|=(B<<i);
                    a[id2]|=(C<<i);
    	            break;
    	        }
    	    }
    	}
    	for (int i=2;i<=n;i++) a[i]=a[1]^b[i];
	}
	cout<<"! ";for (int i=1;i<=n;i++) cout<<a[i]<<" ";cout<<endl;
}


```

---

## 作者：LTb_ (赞：0)

upd：修了注释的锅

[更好的阅读体验](http://lycltb.top/post/solution-cf1451e2/)

也许你应该在阅读这篇题解之前读一读 [E1的题解](https://www.luogu.com.cn/blog/LTb/solution-cf1451e1)

限制从 $n+2$ 减少到了 $n+1$，于是考虑把 $3$ 次 $\operatorname{AND}$ 操作减少至 $2$ 次。

注意到，如果原序列中存在两个相等的数，在它们之前做一次 $\operatorname{AND}$ 询问就可以简单地得出它们的值。

若不存在，因为有 $a_i \in [0,n-1]$，所以原序列是 $0 \sim n-1$ 的一个排列。我们考虑使取到的 $b,c$（$b,c$ 同E1题解中的定义） 满足 $b \operatorname{AND} c = 0$，这样 $b,c$ 不会在任何一位产生相等，可以少询问一次 $b \operatorname{AND} c$。

```cpp
// 2020.11.22
// Code by LTb
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN=2<<17;
int n;
int a[MAXN];
int ap[MAXN];

signed main()

{
	cin>>n;
	int xx=0,yy=0,zz;
	ap[0]=1;
	for (int i=2;i<=n;i++){
		cout<<"XOR 1 "<<i<<endl;
		cin>>a[i];
		if (ap[a[i]] && !xx){ // 此时 a[ap[a[i]]] 与 a[i] 相等
			yy=ap[a[i]];
			xx=i;
		}
		ap[a[i]]=i;
	}

	if (!xx){ // 若不存在相等的数
		xx=1;
		zz=0;
		for (int i=2;i<=n;i++){
			if (a[i]==n-2) yy=i;
			else if (a[i]==1) zz=i; //随便钦定两个数使它们AND值为0
		}
	}
	else{ // 若存在相等的数
		for (int i=1;i<=n;i++)
			if (i!=xx && i!=yy) zz=i;
	}

	int x,y,z;
	cout<<"AND "<<xx<<' '<<yy<<endl;
	cin>>x;
	cout<<"AND "<<xx<<' '<<zz<<endl;
	cin>>y;

	int qwq=a[2]^a[3],ans=0;
	for (int i=15;i>=0;i--){
		int tmp1=(x>>i)&1,tmp2=(y>>i)&1;
		int tmp4=((a[xx]^a[yy])>>i)&1,tmp5=((a[xx]^a[zz])>>i)&1,tmp6=((a[yy]^a[zz])>>i)&1;
		if ((!tmp4) && (!tmp5) && (!tmp6)){
			ans|=tmp1<<i;
		}
		else{
			if (!tmp4) ans|=tmp1<<i;
			else ans|=tmp2<<i;
		}
	}

	cout<<"! "<<(ans^a[xx]);
	for (int i=2;i<=n;i++){
		cout<<' '<<(ans^a[i]^a[xx]);
	}
	cout<<endl;
	return 0;
}
```



---

## 作者：wmy_goes_to_thu (赞：0)

水题。

首先，与，或，异或哪个功能最强大？肯定是异或。所以先得到 $a_1 \oplus a_i$ 的值，这样花费了 $n-1$ 步。

因为 $a_i \in [0,n-1]$，根据鸽巢原理，所以只分为两种情况，一种是 $\exists \ i,j, \ s.t. \ a_i=a_j$，另一种是 $\forall \ i,j \ , a_i \ !=a_j$。

对于第一种情况，很容易找出一组 $i,j$，我们可以得到它们的 AND 值，这样就可以求出 $a_1$，即可求出 $a_i$，一共是 $n$ 步。

对于第二种情况，肯定有 $t_1,t_2$，使得 $a_1 \oplus a_{t_1}=1,a_1 \oplus a_{t_2}=n-1$。我们只需要得到 $a_1 \ or \ a_{t_1}$ 和 $a_{t_1} \ and \ a_{t_2}$，就可以了。具体怎么做呢：

根据 $a_1 \ or \ a_{t_1}$，可以求出 $a_{t_1}$ 的前面若干位（不包括最后一位），通过 $a_{t_1} \ and \ a_{t_2}$ 可以求出最后一位，合在一起就是 $a_{t_1}$ 的值，即可求出 $a_1$，一共是 $n+1$ 步。

最后放代码（这个代码是赛场写的，有点冗长）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int x[1000005],y[1000005];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<n;i++)
	{
		printf("XOR %d %d\n",i,i+1);
		fflush(stdout);
		int aa;
		cin>>aa;
		x[i+1]=x[i]^aa;
	}
	for(int i=1;i<=n;i++)y[i]=x[i];
	sort(y+1,y+n+1);
	int ls=0,t1=0,t2=0;
	for(int i=1;i<n;i++)if(y[i]==y[i+1])ls=i;
	if(!ls)
	{
		int tt1=0,tt2=0;
		for(int i=1;i<=n;i++)
		{
			if(x[i]==1)tt1=i;
			else if(x[i]+1==n)tt2=i;
		}
		printf("OR %d %d\n",1,tt1);
		fflush(stdout);
		int a1;
		cin>>a1;
		printf("AND %d %d\n",tt1,tt2);
		fflush(stdout);
		int a2;
		cin>>a2;
		int xx1=x[tt1]^((a1-a1%2)+a2);
		printf("!");
		for(int i=1;i<=n;i++)printf(" %d",xx1^x[i]);
		printf("\n");
		fflush(stdout);
		return 0;
	}
	ls=y[ls];
	for(int i=1;i<=n;i++)if(x[i]==ls)
	{
		if(t1)t2=i;
		else t1=i;
	}
	printf("AND %d %d\n",t1,t2);
	fflush(stdout);
	int yu,xxx=0;
	cin>>yu;
	for(int i=15;i>=0;i--)xxx|=(1ll<<i)*(((yu>>i)&1)^((x[t1]>>i)&1));
	printf("!");
	for(int i=1;i<=n;i++)printf(" %d",xxx^x[i]);
	printf("\n");
	fflush(stdout);
	return 0;
}
```

---

