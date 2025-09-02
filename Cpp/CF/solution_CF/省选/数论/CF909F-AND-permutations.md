# AND-permutations

## 题目描述

给一个 $n$（$1 \le n \le 10^5$），构造两个长度为 $n$ 的排列，第一个序列 $p$ 满足对任意 $i$，都有 $p_i\neq  i$ 且 $p_i \ \&\ i = 0$，第二个序列 $q$ 满足对任意 $i$ 都有 $q_i \neq  i$ 且 $q_i\ \&\ i \neq 0$。

## 样例 #1

### 输入

```
3
```

### 输出

```
NO
NO
```

## 样例 #2

### 输入

```
6
```

### 输出

```
YES
6 5 4 3 2 1 
YES
3 6 2 5 1 4
```

# 题解

## 作者：Yuno (赞：5)

先考虑 $p$ 的构造

首先简化问题，假如 $n=2^k$，那么问题变得非常的 EZ.

对于 $1$~$n$ 中的每个数，按位取反即可。

换个说法，如果 $a+b=2^k-1$，那么 $a\&b=0$。

根据这个，就可以构造出其他的 $n$ 的答案。

设最接近 $n$ 的 $2$ 的幂次为 $t$，

那么 $[2t-n-1,n]$ 中的每个数都可以找到另一个数与之配对

然后对于 $1$~$2t-1$，继续递归构造即可。

可以发现对于 $n$ 为奇数的情况，最后需要递归处理 $[1,1]$，显然无解。

-------

然后是 $q$ 的构造，这个比较简单。（被 w23c3c3 秒了）

把 $1$~$n$ 中的数分成形如 $[2^k,2^{k+1}-1]$ 的几个部分

对于每个部分，每个数的二进制下最高位都是 $1$

也就是说无论怎样匹配，只要在同一个部分，都满足条件。

当然最后一部分要稍微判一下

考虑处理 $1$，可以发现

当 $n\geq 7$ 时，把 $1$ 和 $7$ 的位置互换，然后$\{4,5,6\}$变成$\{5,6,4\}$即可

当 $n<7$ 时，打表即可 ~~雾~~

假如 $n=2^k$，那么最后会剩下一个单独的数一组，显然无解

Code:

```cpp
#include <bits/stdc++.h>

inline int read( ) {
	int x = 0;
	char c = getchar( );
	while ( !isdigit( c ) ) c = getchar( );
	while ( isdigit( c ) ) x = ( x << 3 ) + ( x << 1 ) + c - 48, c = getchar( );
	return x;
}

const int N = 1e5 + 7;
int n, p[ N ], q[ N ], k[ N ];
void solve( int x ) {
	if ( x == 0 ) return;
	int t = 1;
	while ( t * 2 <= x ) t <<= 1;
	int l = 2 * t - 1 - x;
	for ( int i = l; i <= x; ++ i ) p[ i ] = x + l - i;
   	solve( l - 1 );	
}
int main( ) {
	n = read( );
	if ( n & 1 ) puts( "NO" );
	else {
		solve( n );
		puts( "YES" );
		for ( int i = 1; i <= n; ++ i ) printf( "%d ", p[ i ] );
		puts( "" );
	}
	int t = 1;
	while ( t * 2 <= n ) t = t * 2;
	if ( t == n ) puts( "NO" );
	else {
		if ( n <= 5 ) puts( "NO" );
		if ( n == 6 ) printf( "YES\n3 6 1 5 4 2\n" );
		if ( n >= 7 ) {
			q[ 1 ] = 7;	q[ 2 ] = 3;	q[ 3 ] = 2; q[ 4 ] = 5; q[ 5 ] = 6; q[ 6 ] = 4; q[ 7 ] = 1;
			int pos = 8;
			while ( pos <= n ) {
				int cnt = 0;
				for ( int i = pos; i <= std::min( pos + pos - 1, n ); ++ i ) k[ ++ cnt ] = i;
				for ( int j = pos; j < std::min( pos + pos - 1, n ); ++ j ) q[ j ] = k[ j - pos + 2 ];
				q[ std::min( pos + pos - 1, n ) ] = k[ 1 ];
				pos = std::min( pos + pos - 1, n ) + 1;
			}
			for ( int i = 1; i <= n; ++ i ) printf( "%d ", q[ i ] );
			puts( "" );
		}
	}
	return 0;
}
```


---

## 作者：fade_away (赞：1)

我们不想用智商做此题，于是我们考虑打表找规律。
# Sotution
## Part 1
首先对于第一种，打表得$n$为奇数时无解，当$n=20$时，答案为：

```
2 1 4 3 10 9 8 7 6 5 20 19 18 17 16 15 14 13 12 11
```

这暗示我们把相邻的下降的块合并，于是我们对于$2~30$的偶数，打出相邻块合并后每一块的数的个数的表：
```
2

2 2
6

6 2
2 2 6
2 10
14

14 2
2 10 6
2 2 6 10
6 2 14
6 18
2 2 22
2 26
30

```

乍一看似乎没有规律，但是通过观察我们发现，16~30是由2~14加一个数$x$得到，而上面的同一块内的$x$的公差恰好为$4$。
即：$n$拆分的最后一个数$p$的值为$(n-t+1)*2$，其中$t$为$n$二进制表示下的最大的$1$。

于是我们可以在$O(lgn+n)$时间内解决第一个问题。

## Part 2
第二种稍麻烦一些，我们发现第二种的$dfs$打表代码速度极快，甚至可以在$5s$内跑出$100000$的数据。

但显然我们不会想着卡常通过此题，我们还是打表，发现$n<=5$时无解，$n=2^t$时无解，我们来看表：
```
3 6 1 5 4 7 2 9 8
3 6 1 5 4 2 9 10 7 8
3 6 1 5 4 2 9 10 7 11 8
3 6 1 5 4 2 9 10 7 8 12 11
...
```
我们发现它们有一段前缀相同，通过验证也确实如此，并且对于$n=89$这样的数据：
```
3 6 1 5 4 2 9 10 7 8 12 11 14 13 17 18 15 16 20 19 22 21 24 23 26 25 28 27 30 29 33 34 31 32 36 35 38 37 40 39 42 41 44 43 46 45 48 47 50 49 52 51 54 53 56 55 58 57 60 59 62 61 65 66 63 64 68 67 70 69 72 71 74 73 76 75 78 77 80 79 82 81 84 83 86 85 88 89 87
```

我们发现它的方案到$n$大于$36$时，都是$+3,-1,+3,-1,+3,-1...$的，除了在经过$2^t$或者接近$n$时会发生变化，如$61,65,66,63,64,68,67$。

当经过$2^t$次时，规律也是固定的，我们直接特判即可。

因此我们可以考虑先打出前$36$的表，然后递推得出$n$的表，最后暴力$dfs$后$6+(n\%6)$位。

时间复杂度$O(n)+O(dfs)$，（但是$dfs$可以跑n=100000？？？）。

# Code
打表代码：
```cpp

int flag[MAXN],a[MAXN],n;
void dfs(int x)
{
	if (x==n+1) { for (int i=1;i<=n;i++) printf("%d ",a[i]); exit(0); }
	for (int i=1;i<=n;i++)
		if (!flag[i]&&(x&i)!=0&&i!=x) //改成x&i==0时就是第一种
		{
			flag[i]=1,a[x]=i;
			dfs(x+1);
			flag[i]=0;
		}
}
signed main()
{
	n=read();
	dfs(1);
	return 0;
}

```
真正的代码：
```cpp

int a[MAXN]={0,3,6,1,5,4,2,9,10,7,8,12,11,14,13,17,18,15,16,20,19,22,21,24,23,26,25,28,27,30,29,33,34,31,32,36,35};
void solve(int x)
{
	if (!x) return;
	int t=x;
	while (t-(t&(-t))!=0) t-=t&(-t);
	int p=(x-t+1)*2;
	solve(x-p);
	for (int i=x;i>x-p;i--) printf("%d ",i);
}
int flag[MAXN],b[MAXN],n;
void dfs(int x)
{
	if (x==n+1) 
	{
		puts("YES");
		for (int i=1;i<=n-n%6-6;i++) printf("%d ",a[i]);
		for (int i=n-n%6-5;i<=n;i++) printf("%d ",b[i]);
		exit(0); 
	}
	for (int i=n-(n%6)-5;i<=n;i++)
		if (!flag[i]&&(x&i)!=0&&i!=x)
		{
			flag[i]=1,b[x]=i;
			dfs(x+1);
			flag[i]=0;
		}
}
signed main()
{
	n=read();
	if (n&1) puts("NO");
	else
	{
		puts("YES");
		solve(n);
		puts("");
	}
	for (int i=37,nw=64;i<=n;i+=2) 
	{
		a[i]=a[i-1]+3,a[i+1]=a[i]-1;
		if (a[i]==nw) nw*=2,a[i]++,a[i+1]=a[i]+1,a[i+2]=a[i]-2,a[i+3]=a[i]-1,a[i+4]=a[i]+3,a[i+5]=a[i]+2,i+=4;
	}
	if (n<=5) { puts("NO"); return 0; }
	dfs(n-n%6-5);
	puts("NO");
	return 0;
}


```



---

## 作者：Caro23333 (赞：1)

嗯......其实刷构造题真的很打击智商，毫无头绪的感觉的确不太好......

但我相信，只要用心，或许所谓的“智力”也可以在灵感和思路的积累之间慢慢提升吧......

进入正题。

#### Task 1

看到$p_i\ \textrm{and}\ i=0$的条件，我们可以想到，让$p_i$恰为$i$的按位取反就可以满足条件。然而，这样做存在一个问题：$i$的按位取反可能超出$[1,n]$的范围。

这时可以贪心地想：对于取反后属于$[1,n]$的$i$，先把$p_i$设置为$i$的取反，其他的再另想办法。找出$n$的二进制最高位，设其位权为$2^k$，则闭区间$I=[2^{k+1}-n-1,n]$中的数都可以按照此法优先处理。因为$I$中的数取反后还在$I$中，所以我们会看到问题转化为对$[1,2^{k+1}-n-2]$做相同的构造，只要递归进行即可。

然而这里存在一些问题，会导致这种方法不能构造出答案：递归到最后如果剩一个$[1,1]$，显然是无法完成的。简单推理发现，这等价于初始的$n$为奇数。那么，$n$为奇数是否一定无解呢？

事实上有一种简明的整体化思考方法：当$n$为奇数时，$[1,n]$中的奇数恰比偶数多一个；但若$i$为奇数，则$p_i$必为偶数，否则不满足$p_i\ \textrm{and}\ i=0$。这样的话显然没办法一一对应，所以无解。

#### Task 2

感觉这个有点难想。

首先排除$n$恰为$2$的整数次幂的情况，因为这时$n$没办法找到合适的$p_n$。

~~根据网上的题解~~，对于构造固定长度排列的题，经常可以使用交换的方法来解决。所以我们假设初始时$p_i=i$，并通过若干次交换来达成条件。

考虑对于任意一个正偶数$2k$，它和$2k+1$之间只有最后一位不同，所以$2k\ \textrm{and}\ 2k+1\neq 0$；那么我们只要交换$p_{2k},p_{2k+1}$即可。

这时，如果$n$是偶数，那最后会剩下$1$和$n$无家可归。直接交换$p_1$和$p_n$显然行不通，因为$n$是偶数。这时候有一些奇思妙想：只要随便找一个奇数位置$s$和$p_1$互换，这样它们两个就一定满足；如果还有$s-1\ \textrm{and}\ n\neq 0$，那只要交换$p_{s-1}$和$p_n$就好了。

观察发现$s=n-1$恰好是满足条件的：因为$n$不是$2$的整数次幂，所以$n-2$和$n$的二进制最高位一定是相同的，那么它们的按位与也就不为$0$了。所以只要交换$p_1,p_{n-1}$和$p_{n-2},p_n$就好。

如果$n$是奇数，我们会发现按照交换相邻奇数偶数的做法，最后会单独剩下一个$1$，很尴尬。考虑将问题转化为已经解决的情况，那就是在一个长度为奇数的前缀内部单独进行特异性构造，后面套用交换相邻的方法。

根据样例，这个前缀长度不能为$3$；手玩一把发现$5$好像也不太行。然后构造出来一个$7$：$p_{1\dots7}=[3,6,1,5,7,2,4]$。所以单独特判掉$n=3,5$的情况，其余的就先输出上面的七个数，后面再用交换方法做。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;
typedef long long ll;
const int MAXN = 100005;
int n;
int ans1[MAXN],ans2[MAXN];
inline void calc(int x)
{
	if(x<=0)
	    return;
	int k = log2(x);
    reverse(ans1+((1<<(k+1))-x-1),ans1+x+1);
	calc((1<<(k+1))-x-2);	
}
inline void solve1(int n)
{
	if(n&1)
	{
        cout << "NO" << endl;
        return;
	}
	cout << "YES" << endl;
	for(int i = 1; i<=n; i++)
	    ans1[i] = i;
    calc(n);
    for(int i = 1; i<=n; i++)
        cout << ans1[i] << " ";
    cout << endl;
}
inline void solve2(int n)
{
	if(n==(n&-n)||n==3||n==5)
	{
        cout << "NO" << endl;
        return;
	}
	cout << "YES" << endl;
	for(int i = 1; i<=n; i++)
	    ans2[i] = i;
	if(n&1)
	{
        cout << "3 6 1 5 7 2 4 ";
        for(int i = 8; i<=n; i += 2)
            swap(ans2[i],ans2[i+1]);
	    for(int i = 8; i<=n; i++)
	        cout << ans2[i] << " ";
	    cout << endl;
	}
	else
	{
        for(int i = 2; i<=n-3; i += 2)
            swap(ans2[i],ans2[i+1]);
        swap(ans2[1],ans2[n-1]);
        swap(ans2[n],ans2[n-2]);
        for(int i = 1; i<=n; i++)
            cout << ans2[i] << " ";
        cout << endl;
	}
}

int main()
{
    cin >> n;
    solve1(n), solve2(n);
	return 0;
}

```


---

## 作者：Yansuan_HCl (赞：0)

## P

奇数肯定无解，最低位 1 的数量比 0 的数量多 $1$，鸽巢一下肯定寄了。注意到 $n=2^k-2$ 时有显然的构造（反转），考虑拓展。观察 $1$ 到 $n$ 的二进制序列，有如下构造：

1. 初始排列为 $p_i=i$。
1. 设当前 $n$ 最高位为 $h$。注意到 $2^h+i$ 和 $2^h-1-i$ 无交且并为 $2^{h+1}-1$。记 $c=n-2^h+1$，则可翻转 $[n-2c+1,n]$。
1. $n\gets n - 2c$，跳转到 2。

$c$ 最小为 $1$，故算法能在 $n=0$ 结束。

## Q

Q 的限制相当松。打表发现除了 $1$ 到 $7$ 比较特殊以外，剩下的情况只有 $n=2^k$ 无解。直接让 $q_i = i+1$，$q_n=1$，这样只有 $2$ 的幂处无解，只有 $O(\log n)$ 个数；而剩下的都有解，且是 $O(n)$ 个，直接对每个不合法的数找另一个位置交换，使交换后合法即可。

---

## 作者：wflhx2011 (赞：0)

# Solution

先看 $p$ 如何构造。

不难发现，每一位都变为原数的取反即可符合要求。

所以，将最接近 $n$ 的 $2$ 的次数设为 $k$。

于是，$[2k-n-1,n]$ 每一个数都可以有与之对应的数。

剩下的便递归即可。

最后，奇数会递归到 $[1,1]$，显然无解。

事实上，当 $n$ 为奇数时，奇数便会比偶数多 $1$ 个，可是要想按位与结果为 $0$，奇数与偶数必须相互对应，所以无解。

------------

接下来看 $q$。

这个个人认为简单，只需至少一位相同即可。

所以，让每个数最高位上相同，即分成 $[2^k,2^{k+1}-1]$ 这样几个部分，最后一部分需单独一层循环。

那 $1$ 自己一个部分怎么办？

其实多打几个表就会发现：

当 $n\ge7$ 时，将 $1$ 和 $7$ 调换位置，$q_4$，$q_5$，$q_6$ 随便换即可。

当 $n<7$ 时，打表！

代码也就那样：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,p[100005],q[100005],k[100005],f;
void p1(long long a)
{
	if(a==0)
		return ;
	long long t=1;
	while(t*2<=a)
		t*=2;
	long long l=2*t-1-a;
	for(long long i=l;i<=a;i++)
		p[i]=l+a-i;
	p1(l-1);
}
void q1(long long b)
{
	long long t=1;
	while(t*2<=b)
		t*=2;
	if(t==b||b<=5)
	{
		cout<<"NO";
		f=1;
		return ;
	}
	if(b==6) 
	{
		cout<<"YES"<<endl<<"3 6 2 5 1 4";
		f=1;
		return ;
	}
	cout<<"YES"<<endl;
	q[1]=7,q[2]=3,q[3]=2,q[4]=5,q[5]=6,q[6]=4,q[7]=1;
	long long opq=8;
	while(opq<=b)
	{
		long long cnt=0,s=min(opq*2-1,b);
		for(long long i=opq;i<=s;i++)
			k[++cnt]=i;
		for(long long j=opq;j<s;j++)
			q[j]=k[j-opq+2];
		q[s]=k[1];
		opq=s+1;
	}	
}
int main()
{
    cin>>n;
    if(n%2==1)
    	cout<<"NO"<<endl;
    else
    {
    	cout<<"YES"<<endl;
    	p1(n);
    	for(long long i=1;i<=n;i++)
    		cout<<p[i]<<" ";
    	cout<<endl;
	}
	q1(n);
	if(f)
		return 0;
	else
		for(long long i=1;i<=n;i++)
			cout<<q[i]<<" ";
    return 0;
}
```

---

