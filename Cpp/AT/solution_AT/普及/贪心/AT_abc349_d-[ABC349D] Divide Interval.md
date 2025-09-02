# [ABC349D] Divide Interval

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc349/tasks/abc349_d

非負整数 $ l,r\ (l\ <\ r) $ に対して、$ l $ 以上 $ r $ 未満の整数を順に並べた数列 $ (l,l+1,\ldots,r-2,r-1) $ を $ S(l,r) $ で表します。また、非負整数 $ i,j $ を用いて $ S(2^{i}j,2^{i}(j+1)) $ と表される数列を良い数列と呼ぶことにします。

非負整数 $ L,R\ (L\lt\ R) $ が与えられます。数列 $ S(L,R) $ をできるだけ少ない個数の良い数列に分割するとき、その個数と分割の方法を出力してください。より厳密には、以下を満たす非負整数の組の列 $ (l_1,r_1),(l_2,r_2),\ldots,(l_M,r_M) $ が存在するような正整数 $ M $ の最小値を求め、そのときの $ (l_1,r_1),(l_2,r_2),\ldots,(l_M,r_M) $ を出力してください。

- $ L=l_1\ <\ r_1=l_2\ <\ r_2=\cdots=l_M\ <\ r_M=R $
- $ S(l_1,r_1),S(l_2,r_2),\ldots,S(l_M,r_M) $ は良い数列

なお、$ M $ が最小となるような分割方法は一通りのみ存在することが示せます。

## 说明/提示

### 制約

- $ 0\leq\ L\lt\ R\leq\ 2^{60} $
- 入力は全て整数

### Sample Explanation 1

$ S(3,19)=(3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18) $ です。これは以下の $ 5 $ つの良い数列に分割でき、これが個数が最小となるような分割方法です。 - $ S(3,4)=S(2^0\cdot\ 3,2^0\cdot4)=(3) $ - $ S(4,8)=S(2^2\cdot\ 1,2^2\cdot\ 2)=(4,5,6,7) $ - $ S(8,16)=S(2^3\cdot\ 1,2^3\cdot\ 2)=(8,9,10,11,12,13,14,15) $ - $ S(16,18)=S(2^1\cdot\ 8,2^1\cdot\ 9)=(16,17) $ - $ S(18,19)=S(2^0\cdot\ 18,2^0\cdot\ 19)=(18) $

## 样例 #1

### 输入

```
3 19```

### 输出

```
5
3 4
4 8
8 16
16 18
18 19```

## 样例 #2

### 输入

```
0 1024```

### 输出

```
1
0 1024```

## 样例 #3

### 输入

```
3940649673945088 11549545024454656```

### 输出

```
8
3940649673945088 3940649673949184
3940649673949184 4503599627370496
4503599627370496 9007199254740992
9007199254740992 11258999068426240
11258999068426240 11540474045136896
11540474045136896 11549270138159104
11549270138159104 11549545016066048
11549545016066048 11549545024454656```

# 题解

## 作者：lutaoquan2012 (赞：7)

## 题意：
这道题就是给定你一个 $l$，让你通过一系列的操作把 $l$ 变成 $r$。

## 思路：
再给题目的意思进行更简单的描述。

题目的意思就是让我们从 $l$，每一次跳当前能跳的最大的 $2^n$ 步，$n$ 满足 $0\le n\le 60$ 并且 $l \bmod 2^n = 0$ 还要 $l+a_i\le r$。

在这里，我们可以先算出每一个 $2^n$。

```cpp
ll a[65] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
            1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912,
            1073741824, 2147483648, 4294967296, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472,
            274877906944, 549755813888, 1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416,
            35184372088832, 70368744177664, 140737488355328, 281474976710656, 562949953421312, 1125899906842624,
            2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 36028797018963968,
            72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976};
```

然后按着思路模拟即可。

## 代码：
```cpp
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
ll a[65] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
            1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912,
            1073741824, 2147483648, 4294967296, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472,
            274877906944, 549755813888, 1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416,
            35184372088832, 70368744177664, 140737488355328, 281474976710656, 562949953421312, 1125899906842624,
            2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 36028797018963968,
            72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976};
ll l,r,h1[1100000],h2[1100000],ans;
int main(){
    cin>>l>>r;
    while(l!=r){
        for(int i=60;i>=0;i--){
            if(l+a[i]<=r&&l%a[i]==0){
                h1[++ans]=l;
                h2[ans]=l+a[i];
                l+=a[i];
                break;
            }
        }
    }cout<<ans<<endl;
    for(int i=1;i<=ans;i++) cout<<h1[i]<<" "<<h2[i]<<endl;
    return 0;
}
```

## 如何想出思路
我们观察这个第一组样例，我们可以分为三部分。

1. 从 $3$ 如何跳到 $4$。
2. 从 $4$ 如何跳到 $16$。
3. 从 $16$ 如何跳到 $19$。

再观察一下第三组样例，我们可以按照前面的思路化为三部分。

1. 从 $3940649673945088$ 如何跳到 $4503599627370496$。
2. 从 $4503599627370496$ 如何跳到 $9007199254740992$。
3. 从 $9007199254740992$ 如何跳到 $11549545024454656$。

我们可以从上面发现一些规律。

设定一个 $L$ 代表第一个大于 $l$ 的 $2^L$。

再设定一个 $R$ 代表最后一个小于 $r$ 的 $2^R$。

所以我们分为了从 $l$ 到 $2^L$，从 $2^L$ 到 $2^R$，从 $2^R$ 到 $r$。

上面的三个步骤，其实都可以换成从一个点，跳很多次尽可能最大的步数，到达另一个点。


### 核心代码
```cpp
while (l != a[L]) {
    for (int i = L - 1; i >= 0; i--) {
        if (l % a[i] == 0 && l + a[i] <= a[L]) {
            h1[++ans] = l;
            h2[ans] = l + a[i];
            l += a[i];
            break;
        }
    }
}
while (l != a[R]) {
    h1[++ans] = l;
    h2[ans] = l * 2;
    l *= 2;
}
while (l != r) {
    for (int i = R - 1; i >= 0; i--) {
        if (l % a[i] == 0 && l + a[i] <= r) {
            h1[++ans] = l;
            h2[ans] = l + a[i];
            l += a[i];
            break;
        }
    }
}printf("%lld\n",ans);
for (int i = 1; i <= ans; i++) printf("%lld %lld\n",h1[i],h2[i]);
```

想到这里，我们可以放弃 $L$ 和 $R$ 这两个中转点，直接从 $l$ 到 $r$ 进行操作，就和前面的一样了。

---

## 作者：Redamancy_Lydic (赞：4)

## 背景

太逊了，调了三次才调出来，所以写篇题解寄念。~~LC好睿智~~

## 题意 

给你两个数 $a,b$，现在要从 $a$ 跑到 $b$，每次可以将当前的 $a$ 拆分成 $2^n\times m(n,m\in N)$ 的形式，并将它变成 $2^n\times (m+1)$。问最少变几次能跑到 $b$，输出次数和每次变化前后 $a$ 的值。 

## 分析

这道题有一个~~一眼~~贪心。在一次变化后不会超过 $b$ 的情况下，我们要让 $n$ 的值尽可能大来使得 $a$ 变化后更大。所以我们可以写一个函数来先找到 $n$ 最大可以是多少，具体就是看看 $a$ 的因数中最大的 $2$ 的整次幂是多少，下面给出：
```cpp
int p(int x)
{
	int ans=1;
	while(x%ans==0)
	{
		ans=ans<<1;
	}
	if(x%ans)ans/=2;
	return ans;
}
```
然后计算出 $m$，并判断这样拆分后一次变化是否会超过 $b$，如果超过就让 $n>>1$，直到满足条件。因为要先输出变化次数，所以用两个数组记录每次变化前后 $a$ 的值即可。

### 细节

如果 $a$ 的初值为 $0$，我们发现此时 $n$ 可以是任意值，所以我们特判一下，直接找到不大于 $b$ 的最大的 $2$ 的整次幂，让 $a$ 变成它就行了。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
int w=1,s=0;char ch=getchar();
while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();}
while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
return w*s;
}
const int maxn=6e7+10;
int l,r;
int p(int x)//得出最大因数 
{
	int ans=1;
	while(x%ans==0)
	{
		ans=ans<<1;
	}
	if(x%ans)ans/=2;
	return ans;
}
int lo(int x)//得出最大2的整次幂 
{
	int i;
	for(i=1;i<=x;i*=2);
	if(i>x)i/=2;
	return i;
}
int ansl[maxn],ansr[maxn],tot;//记录答案 
signed main()
{
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
	cin>>l>>r;
	while(l<r)
	{
		if(l==r)break;
		ansl[++tot]=l;
		if(l==0)//特判 
		{
			int pr=lo(r);
			l=pr;
			ansr[tot]=l;
			continue;
		}
		int p2=p(l);
		int bei=l/p2;//计算n和m 
		while(p2*(bei+1)>r)//向下缩小n 
		{
			p2=p2>>1;
			bei=l/p2;
		}
		l=p2*(bei+1); 
		ansr[tot]=l;
	}
	cout<<tot<<endl;
	for(int i=1;i<=tot;i++)
	cout<<ansl[i]<<' '<<ansr[i]<<endl;
	return 0;
}
```

---

## 作者：wflhx2011 (赞：3)

## 思路

一种新的思路。

当时看到这个题时，突然想到了线段树，这个题目中所要求划分的区间跟线段树的区间差不多。

于是，想到模仿线段树来递归实现。

此处，设 $f(l,r,L,R)$ 函数表示一个符合题意的区间与$[L,R)$ 的交集。

具体来说：

1. 如果 $[l,r)$ 包含在 $[L,R)$ 中，那么 $[l,r)$ 一定是最优划分中的一部分。

1. 否则，设 $m=(l+r)\div2$，此时 $[l,m)$ 和 $[m,r)$ 都是满足题意的区间。

- 如果 $[L,R)$ 包含在 $[l,m)$ 中，即 $R\le m$，那么 $[l,m)$ 是最优划分中的一部分。类似的，如果 $m\le L$，那么 $[m,r)$ 是最优划分中的一部分。

- 如果不满足上面的条件，那么就分左半和右半两部分求。

因为这题数据最大到 $2^{60}$，所以从 $f(0,2^{60},L,R)$ 开始递归即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
long long c[N],d[N];
long long ksm(long long a,long long n) 
{
	long long ans=1;
	while(n) 
	{
		if(n&1) 
			ans*=a;
		n>>=1;
		a*=a;
	}
	return ans;
}
long long cnt=0;
void f(long long a,long long b,long long x,long long y) 
{
	if(x<=a&&b<=y) 
	{
		c[++cnt]=a;
		d[cnt]=b;
		return ;
	}
	long long m=(a+b)/2;
	if(y<=m) 
	{
		f(a,m,x,y);
		return;
	}
	if(m<=x) 
	{
		f(m,b,x,y);
		return;
	}
	f(a,m,x,y);
	f(m,b,x,y);
	return ;
}
int main() 
{
	long long l,r;
	scanf("%lld%lld",&l,&r);
	f(0,ksm(2,60),l,r);
	cout<<cnt<<endl; 
	for(int i=1;i<=cnt;i++)
		cout<<c[i]<<" "<<d[i]<<endl;
	return 0;
}
```

---

## 作者：IJN_Shokaku (赞：2)

# [ABC349D] Divide Interval 题解

传送门：
[luogu]() | [atcoder](https://atcoder.jp/contests/abc349/tasks/abc349_d)

## 题目简述

给定非负整数 $l$ 和 $r$（$l<r$），令 $S(l,r)$ 表示序列 $(l,l+1,\ldots,r-2,r-1)$，其中包含从 $l$ 到 $r-1$ 的所有整数。此外，一个序列被称为“好序列”，当且仅当它可以表示为 $S(2^i j,2^{i}(j+1))$，其中 $i$ 和 $j$ 是非负整数。

## 解题思路

容易看出，使用贪心可以求解这个问题。即从左到右划分序列，每次划分的序列都是最大的即可。具体地，重复执行以下步骤：

- 当前起点为 now。
- 找到最大的合法 $i$ 值，并反求 $j$ 值。
- 分离序列 $(2^ij,2^i(j+1))$。
- 将 now 更新为 $2^i(j+1)$。

如何找到最大的合法 $i$ 值？

我们可以枚举 $i$，然后判断反推出的 $j$ 是否合法，当 $j$ 不合法或此时右边界越界时，就退出枚举。

因为 $2^i$ 是指数级增长的，所以枚举的次数不会超过 $60$，不会超时。

注意：

1. 需要使用 `long long` 存储数据。

2. 如果使用位运算求解 $2^i$ ，需要使用 `(1LL << i)`，否则会因为爆出 `int` 范围而返回错误值 $0$。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int l, r;
signed main() {
    cin >> l >> r;
    int now = l, num = 0;
    queue<pair<int,int>>ans; 
    while (now < r) {
        int i = 0;
        do { // 枚举 i 值
            int pow = (1LL << i);
            // 判断合法性
            if (now % pow != 0) break;
            if (pow * ((now / pow) + 1) > r) break;
        } while (++i);
        i--, num++;
        int pow = (1LL << i);
        int j = now / pow;
        ans.emplace(pow * j, pow * (j + 1));
        now = pow * (j + 1);
    }
    cout << num << endl;
    while (!ans.empty()) {
        cout << ans.front().first << " " << ans.front().second << endl;
        ans.pop();
    }
    return 0;
}
``````

---

## 作者：cqbzcjh (赞：2)

## 分析
由题意可知，每一个区间的长度都为 $2$ 的非负次幂，而 $2^0=1$，说明本题一定有解。

我们记区间左端点为 $l$，右端点为 $r$，长度为 $len$。对于每个区间：
1. 固定 $l=$ 上一个区间的 $r+1$。从 $2^{60}$ 开始从大到小枚举 $2$ 的幂，即当前的 $len$。
1. 对于每个 $len$，必须要保证 **$l$ 能被 $len$ 整除且 $r$ 没有超过 $R$**，才是满足条件的区间。
1. 因为要使答案最小，我们取 $len$ 最大的满足条件的区间。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long M=1152921504606846976;//2的60次方
long long L,R,ans;//不开long long见祖宗
vector<pair<long long,long long> > v;
int main(){
	cin>>L>>R;
	for(long long l=L;l<R;)//l为当前区间左端点
		for(long long len=M;len;len/=2)//len为区间的长度
			if(l%len==0&&(l+len-1)<R){
				ans++;
				v.push_back({l,l+len});
				l+=len;
				break;
			}
	cout<<ans<<endl;
	for(auto i:v)
		cout<<i.first<<" "<<i.second<<endl;
	return 0;
}
```

---

## 作者：破壁人罗辑 (赞：2)

题目传送门：[洛谷](https://www.luogu.com.cn/problem/AT_abc349_d)/[Atcoder](https://atcoder.jp/contests/abc349/tasks/abc349_d)

## 题意简述

给出两个正整数 $l,r$，每次可以将 $l$ 表示成 $a\times 2^b$ 的形式，其中 $a,b\in\N$，然后将 $l$ 改为 $(a+1)\times 2^b$，请给出一个操作方案使得经过最小的步数让 $l$ 变成 $r$。

## 解题思路

设 $\text{lowbit}(x)$ 表示 $x$ 的二进制最低位的 $1$ 代表的大小，$\text{highbit}(x)$ 表示 $x$ 的二进制最高位的 $1$ 代表的大小。

### 前置知识

由定义可知，$\text{lowbit}(2^n)=\text{highbit}(2^n)=2^n$，$\text{lowbit}(x)\leq\text{highbit}(x)\leq x$。

### 最优解及证明

最优解是贪心，看着很显然，但要证明的话可能有些麻烦。

将 $l=a\times 2^b$ 变为 $l=(a+1)\times 2^b$ 相当于选择一个 $b\leq\log_2(\text{lowbit}(l))$，将 $l$ 加上 $b$。

假设 $l=0,r=\sum_{i=1}^n2^{b_i}$，$b_i$ 单调递减。显然每一次操作都只能把 $l$ 的二进制表示中的一位由 $0$ 变成 $1$，所以至少需要 $n$ 次操作；假如我们共进行 $n$ 次操作，第 $i$ 次操作将 $l$ 加上 $b_i$，显然最后得到的答案是 $r$，第一次操作中令 $l=0\times2^{b_1}$，显然能够正常进行，设 $1\leq m<n$，在进行了 $m$ 次操作后 $l=\sum_{i=1}^m2^{b_i}=2^{b_{m+1}}\times\sum_{i=1}^m2^{b_i-b_{m+1}}$，由假设中的 $b_i$ 单调递减可知 $b_i-b_{m+1}>0$，故 $\sum_{i=1}^m2^{b_i-b_{m+1}}\in\N$，能够进行第 $m+1$ 次操作，所以由数学归纳法可知每一次操作都是合法的，可以只进行 $n$ 次操作将 $l$ 变成 $r$。故在此情况下将 $l$ 变成 $r$ 的最佳方案是进行 $n$ 次操作，每次操作加上 $\text{highbit}(r-l)$。

假设 $\text{highbit}(r-l)\leq\text{lowbit}(l)$。设 $r-l=\sum_{i=1}^n2^{b_i}$，且 $b_i$ 单调递减，由假设定义可知 $\log_2(\text{lowbit}(l))\geq b_1>b_2>\cdots>b_n$，每一次操作都只能把 $r-l$ 的二进制表示中的一位由 $0$ 变成 $1$，所以至少需要 $n$ 次操作；假如我们共进行 $n$ 次操作，第 $i$ 次操作将 $l$ 加上 $b_i$，显然最后得到的答案是 $r$，记 $l_0=a\times2^{b_0}$ 为第一次操作之前的 $l$，其中 $b_0=\text{lowbit}(l)$，在第 $m$ 次操作时我们可以将 $l$ 表示为 $2^{b_m}\times\left(a\times2^{b_0-b_m}+\sum_{i=1}^{m-1}2^{b_i-b_m}\right)$，由假设可知 $a\times2^{b_0-b_m}+\sum_{i=1}^{m-1}2^{b_i-b_m}\in\N$，故操作合法，可以只进行 $n$ 次操作将 $l$ 变成 $r$。故在此情况下将 $l$ 变成 $r$ 的最佳方案是进行 $n$ 次操作，每次操作加上 $\text{highbit}(r-l)$。

假设 $\text{highbit}(r-l)>\text{lowbit}(l)$。我们可以将 $l=a\times2^{\text{lowbit}(l)}$ 变为 $(a+1)\times2^{\text{lowbit}(l)}=l+\text{lowbit}(l)$，所以 $l$ 变为 $r$ 的过程中可以经过 $l+\text{lowbit}(l)$ 且将 $l$ 变为 $l+\text{lowbit}(l)$ 只需要经过一步；若将 $l$ 变为 $r$ 的过程中不经过 $l+\text{lowbit}(l)$，则 $\exists l'\geq l,l'<l+\text{lowbit}(l),\exists b'\leq\log_2(\text{lowbit}(l')),l'+2^{b'}>l+\text{lowbit}(l)$，又因为 $\text{highbit}(l'-l)\leq l'-l<\text{lowbit}(l)$，则 $\text{lowbit}(l+\text{lowbit}(l)-l')=\text{lowbit}(l')=\min(\text{lowbit}(l'-l),\text{lowbit}(l))=\text{lowbit}(l'-l)$，故 $2^{b'}\leq\text{lowbit}(l+\text{lowbit}(l)-l')\leq l+\text{lowbit}(l)-l',l'+2^{b'}\leq l+\text{lowbit}(l)$，与假设中的 $l'+2^{b'}>l+\text{lowbit}(l)$ 不符。故 $l$ 在变成 $r$的过程中必然经过 $l+\text{lowbit}(l)$，且最优方法是只经过一步直接加上 $\text{lowbit}(l)$。此操作会使 $r-l$ 减小但不会减到 $0$，$\text{lowbit}(l)$ 增加，所以经过有限次此操作后一定会使得 $\text{highbit}(r-l)\leq\text{lowbit}(l)$。

所以最优方法如下：

若 $l=0$，则将 $l$ 变成 $r$ 的最佳方案是进行 $n$ 次操作，每次操作给 $l$ 加上 $\text{highbit}(r-l)$；

若 $\text{highbit}(r-l)>\text{lowbit}(l)$，则每次操作给 $l$ 加上 $\text{lowbit}(l)$，直到 $\text{highbit}(r-l)\leq\text{lowbit}(l)$，然后按照 $\text{highbit}(r-l)\leq\text{lowbit}(l)$ 的情况执行；

若 $\text{highbit}(r-l)\leq\text{lowbit}(l)$，则每次操作给 $l$ 加上 $\text{highbit}(r-l)$。

### 小知识

由于计算机中采用补码存储数值，可以使用 `x&(-x)` 计算变量 `x` 的二进制最低位。

## AC 代码
### C++
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<long long>ans[2];
int main(){
	long long l,r;scanf("%lld%lld",&l,&r);
	int tot=0;
	while(l<r){
		if(l){
			long long t=l&(-l);
			while(l+t>r)t>>=1;
			ans[0].push_back(l);ans[1].push_back(l+t);
			l+=t;tot++;
		}
		else{
			long long t=1;
			while(t<<1<=r)t<<=1;
			ans[0].push_back(0);ans[1].push_back(t);
			l=t;tot++;
		}
	}
	printf("%d\n",tot);
	for(int i=0;i<tot;i++){
		printf("%lld %lld\n",ans[0][i],ans[1][i]);
	}
	return 0;
}
```
### Python
```python
[l,r]=input().split()
l=int(l)
r=int(r)
if l==0:
    a=r
    while a!=a&(-a):
        a=a-(a&(-a))
    cnt=1
    l=a
    ans=[[0],[a]]
else:
    cnt=0
    ans=[[],[]]
while l!=r:
    ans[0].append(l)
    if l+(l&(-l))<=r:
        l=l+(l&(-l))
    else:
        a=1
        while l+a*2<=r:
            a=a*2
        l=l+a
    ans[1].append(l)
    cnt=cnt+1
print(cnt)
for i in range(cnt):
    print(str(ans[0][i])+' '+str(ans[1][i]))
```

---

## 作者：HasNoName (赞：1)

### 思路：

如果 $a=0$，$a$ 为最接近 $b$ 的 $2$ 的整数次幂时最优。

在 $a$ 小于 $b$ 时，将 $a$ 加上 $a$ 能整除的最大 $2$ 的整数次幂。

每次从高到地位枚举 $b$ 的二进制位，若 $b$ 的那一位为 $1$ 且 $a$ 的那一位为 $0$ 将 $a$ 增加一个 $2$ 的整数次幂使 $a$ 的那一位为 $1$。

### 代码：

```cpp
#include<bits/stdc++.h>
#define ret while(1);
using namespace std;
typedef long long ll;
ll u[100005];
ll get(ll x)//lowbit
{
    return x&(-x);
}
ll get1(ll x)//小于等于x的最大二的整数次幂
{
    ll c=1;
    while(c<=x)
        c<<=1;
    return c>>1;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll a,b,x=0,c;
    cin>>a>>b;
    if(a==0)
    {
        u[++x]=a;
        a=get1(b);
    }
    c=a;
    while(a<=b)//让a的贡献值最大
    {
        u[++x]=a;
        c=get(a);
        a+=c;
    }
    a-=c;//最后的时候多加了一个c
    b-=a;
    while(b)
    {
        c=get1(b);//因为从低到高位无法满足条件，必须从高到低位
        a=a+c;
        u[++x]=a;
        b-=c;
    }
    cout<<x-1<<'\n';
    for(int i=2;i<=x;i++)
    {
        cout<<u[i-1]<<' '<<u[i]<<'\n';
    }
    return 0;
}

```

---

## 作者：Xuan_qwq (赞：1)

### 题面大意
现有一个正整数 $l$，每次操作定义如下：

如果可以将 $l$ 表示为 $2^i \times j$ 的形式，那么就可以将 $l$ 变为 $2^i \times (j+1)$。

求最小的操作次数使得 $l$ 变为 $r$，并输出操作方法。

### 思路分析

看了一下样例解释，感觉是让 $l$ 增加的尽可能大。于是有了贪心的思路：每次取最大的 $i$ 使得当前的 $l$ 可以表示为 $2^i \times j$ 的形式并且 $2^i \times (j+1) \leq r$，将 $l$ 变为 $2^i \times (j+1)$ 即可。

于是火速有了第一版代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int l,r;
int cnt(int a,int d){//计算当前的l最多能加多少
	int ans=1;
	while(a%2==0){
		a/=2;
		ans*=2;
		if(ans==d)return ans;
		if(ans>d)return ans/2;
	}
	if(ans>d)return ans/2;
	return ans;
}
vector<pair<int,int> >v;//记录操作序列
signed main(){
	cin>>l>>r;
	while(l<r){
		int d=cnt(l,r-l);
		v.push_back({l,l+d});
		l+=d;
	}
	cout<<v.size()<<endl;
	for(int i=0;i<v.size();i++){
		cout<<v[i].first<<" "<<v[i].second<<endl;
	} 
	return 0;
}
```

交上去，过了。

那么接下来我们来证明这个贪心：

设当前 $l$ 最大可以变为 $l_1=2^{i_1}\times {(j_1+1)}$。若存在一种方法，使得当前 $l$ 变为 $l_2=2^{i_2}\times {(j_2+1)}<l_1$，且此种方法操作数最优。

容易知道有：$j_2=2^k \times j_1$。

此时 $2 \nmid (j_2+1)$，所以 $l_2$ 最大可以变为 $l_2=2^{i_2}\times {(j_2+2)}$

若 $l_2$ 接下来变为 $l_2=2^{i_2}\times {(j_2+2)}$，那么此种操作方法可以等价于将 $l$ 直接变为 $2^{i_2+1}\times {(\frac{j_2}{2}+1)}$，操作次数更少，所以不是最优。

否则，$l_2$ 最大变为 $l_3=2^{i_2-1}\times {(2\times j_2+3)}$，$l_3$ 最大变为 $l_4=2^{i_2-2}\times {(4\times j_2+7)}$，……，最终变为 $l_n=2^{i_2}\times j_2+2^{i_2+1}-1<2^{i_2+1}\times(\frac{j_2}{2}+1)\leq 2^{i_1}\times {(j_1+1)}=l_1$，不连续加两次相同的值无法达到 $l_1$，故不是最优。

所以贪心成立。

---

## 作者：Floating_Trees (赞：1)

### 题意
令 $S(l,r)$ 为 从 $l$ 到 $r-1$ 的所有整数从小到大的一个序列，如果 $S(l,r)$ 可以表示为 $S(2^i\times j,2^i\times(j+1))$ 那么称这是一个好的序列。现在给你一个 $l$ 和 $r$，把 $S(l,r)$ 分解成 $m$ 个好的序列，请求出 $m$ 的最小值，并输出分解成的 $m$ 个 $S(l_1,r_1),S(l_2,r_2),\cdots ,S(l_m,r_m)$。数据保证答案唯一。

### 思路
题目说要 $m$ 最小，那么一个区间就要尽量的长。我们可以对于每个 $l_k$ 分解成 $2^i\times j_1$ 的形式，那么**理论上**的 $r_k$ 就是 $2^i\times(j_1+1)$，但是我们需要判断这个 $r_k$ 是否小于等于 $r$，如果大于，那么就看 $2^{i-1}\times j_1$ 是否小于等于 $r$，以此类推，直到小于等于 $r$。那么 $l_{k+1}=r_k$。一直再重复上面的操作，直到 $r_k=r$。

### 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define pll pair<ll,ll>
#define mp make_pair

using namespace std;

vector< pll > v;

void solve(ll l, ll r)
{
	if (l == r)
		return ;
	ll p = 1, k = 0, x = l, idnxt;
	if (l == 0)
	{
		while (p <= r)
			p = p * 2;
		p = p / 2;
		v.push_back(mp(l,p));
		solve(p,r);
		return ;
	}
	while (x % 2 == 0)
		x = x / 2, p = p * 2, k++;
	while (k >= 0)
	{
		ll n = l / p;
		ll nxt = p * (n + 1);
		if (nxt <= r)
		{
			idnxt = nxt;
			break;
		}
		p = p / 2;
		k--;
	}
	v.push_back(mp(l,idnxt));
	solve(idnxt,r);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	
	ll l, r; cin >> l >> r;
	solve(l,r);
	cout << v.size() << endl;
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	 
	return 0;
}

```

---

## 作者：I_Love_DS (赞：1)

### 前言

第 $4$ 题就这水平？？？

$15$ 分钟切掉好吧。

### 思路

这题就是个模拟 + 小贪心，步骤如下（伪代码加注释）：

（虽然可能不是伪代码 QwQ）

```cpp
while l < r : //当左小于右时
	w = 0
	while l % ppow[w] == 0 && ppow[w] * (l / ppow[w] + 1) <= r : w++
	w--
	//有一点小贪心，找到合格的最大的幂
	ans[++cnt] = {l,ppow[w] * (l / ppow[w] + 1)} //记录答案
	l = ppow[w] * (l / ppow[w] + 1) //更新左边界
```

解释一下变量：

- $ppow$ 是存 $2$ 的若干次幂的。
- $l,r$ 见题目描述。
- $w$ 是枚举最大合格幂的。
- $ans$ 是一种 `pair<>` 变量，记录答案。
- $cnt$ 记录答案个数。

记得开 `long long`！！！

时间复杂度 $O(\log(r - l))$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll pw[64],s = 1,l,r,cnt = 0;//见上
pair <ll,ll> ans[10000];//以防万一要开大
int main(){
	for (int i = 0; i <= 61; i++) pw[i] = s,s *= 2;//预处理2的若干次幂
	scanf("%lld%lld",&l,&r);
	while (l < r) {
		int w = 0;
		while (l % pw[w] == 0 && pw[w] * (l / pw[w] + 1) <= r) w++;
		w--;
		ans[++cnt] = {l,pw[w] * (l / pw[w] + 1)};
		l = pw[w] * (l / pw[w] + 1);
	}
	//见上
	printf("%lld\n",cnt);
	for (int i = 1; i <= cnt; i++) printf("%lld %lld\n",ans[i].first,ans[i].second);
	return 0;
}
```

不错吧~~~

---

## 作者：yaaaaaan (赞：0)

### 思路
这道题就是一个贪心，每次加上合法的最大的幂。因为数据中最大才 $2^{60}$，可以直接预处理 $2^1\dots2^{60}$(当然也可以用位运算)。

### 核心代码
```cpp
cin>>l>>r;
int old=l;
c[0]=1;
for(int i=1; i<=61; i++) {
	c[i]=c[i-1]*2;
}//预处理2的次方
while(old<r) {
	a[++k]=old;
	fl=0;
	for(int i=61; i>=0; i--) {
		if(old%c[i]==0&&old+c[i]<=r) { //判断是否合法
			b[k]=old+c[i];
			old+=c[i];
			fl=1;
		}
		if(fl==1) break;
	}
}
cout<<k<<"\n";
for(int i=1; i<=k; i++) {

	cout<<a[i]<<" "<<b[i]<<"\n";
}//输出
```
**注意开 long long。**
```cpp
#define int long long
```

---

## 作者：nxd_oxm (赞：0)

# 题意
我们定义：$S(i,j)$ 表示 $i \sim i+2^j-1$ 的数列。给定整数 $l,r$，让你用最少的 $S(x,y)$ 来拼出 $i \sim j-1$ 的数列。

# 思路
贪心。

对于每一个 $S(l_i,r_i)$，$l_i$ 肯定是 $r_{i-1}$，$r_i$ 一定取最大。

证明：假设不取最大值 $maxri$，取 $maxri-1$，那一定至少要用 $S(l_i,maxri-1)$ 和 $S(l_i+2^{maxri-1},maxri-1)$ 来拼出原本的区间 $S(l_i,maxri)$。

我们只需要枚举 $r_i$，如果 $l_i+2^{r_i+1}$ 并没有超过给定的 $r$，那就将 $r_i$ 加一。统计答案即可。
## AC code
```cpp
#include<bits/stdc++.h>
#define f(i,j,n) for(int i=j;i<=n;i++)
#define int long long
using namespace std;
int l,r;
int opt[1001][2];
signed main(){
	cin>>l>>r;
	int ans=0;
//	cout<<l<<endl;
//	if(l==0){
//		ans++;
//		opt[ans][0]=0,opt[ans][1]=pow(2,(int)log2(r));
//		l=pow(2,(int)log2(r));
//	}
	while(l<r){
//		cout<<l<<endl;
		ans++;
		int uo=pow(2,(int)log2(l));
//		if(uo!=l){
//			cout<<1<<":";
		int ooo=0ll,ll=l;
		while(ll%2==0&&!((l/(int)pow(2ll,ooo+1)+1)*(int)pow(2ll,ooo+1)<0)||((l/(int)pow(2ll,ooo+1ll)+1)*(int)pow(2ll,ooo+1ll)>r)){
			ll/=2;
			ooo++;
			int oo=(l/(int)pow(2ll,ooo)+1)*(int)pow(2ll,ooo);
			if(oo<0||oo>r){
				ooo--;
				break;
			}
		}
//		while(ooo>0&&((l/(int)pow(2ll,ooo)+1)*(int)pow(2ll,ooo)<0)||((l/(int)pow(2ll,ooo)+1)*(int)pow(2ll,ooo)>r)){
//			ooo--;
//		}
		opt[ans][0]=l,opt[ans][1]=(l/(int)pow(2ll,ooo)+1)*(int)pow(2ll,ooo);
		l=(l/(int)pow(2ll,ooo)+1)*(int)pow(2ll,ooo);
//		}else{
////			cout<<2<<":";
//			int oo=(int)log2(l);
//			while((l+(int)pow(2,oo)<0)||(l+(int)pow(2,oo)>r)){
//				oo--;
//			}
//			
////			cout<<(l+pow(2,oo)<0||l+pow(2,oo)>r)<<" "<<(int)(l+pow(2,oo));
//			
//			int qt=pow(2,oo);
////			cout<<((l+qt)<0)<<" ";
//			opt[ans][0]=l,opt[ans][1]=l+qt;
//			l+=qt;
//		}
	}
	cout<<ans<<endl;
	f(i,1,ans){
		cout<<opt[i][0]<<" "<<opt[i][1]<<endl;
	}
	cout<<endl;
	return 0;
}
```

---

## 作者：unordered_yao (赞：0)

## 思路

1. 我们首先要开一个数组 $p$，第 $i$ 项表示 $2^i$。

2. 我们为了让 $W$ 最小化，可以采用贪心的思想。数据范围到 $2^{60}$，我们可以从 $2^{60}$ 开始，一直循环到 $2^0$，直到找到 $l$ 能整除的 $p_i$，并且不超过有边界 $r$，就存一下结果，最后 break 结束。

## 代码

```cpp
#include <iostream>
#define int long long

using namespace std;
const int N = 1e6;
int p[61];
struct node{
    int nl,nr;
}a[N];
void makepow(int l,int r){
    p[0] = 1;
    for(int i=l;i<=r;i++) p[i] = p[i-1]*2;
}
void solve(int l,int r,int& w){
    while(l<r){
        for(int i=60;i>=0;i--){ 
            if(l%p[i]==0 && l+p[i]<=r){
                a[w++] = {l,l+p[i]};
                l+=p[i];
                break;
            }
        }
    }
    
}
signed main(){
    int l,r;
    cin >> l >> r;
    makepow(1,60);
    int w = 0;
    solve(l,r,w);
    cout << w << '\n';
    for(int i=0;i<w;i++){
        cout << a[i].nl << ' ' << a[i].nr << '\n'; 
    }
    return 0;
}
```

---

## 作者：haokee (赞：0)

贪心。先说结论：对于当前左边界 $l$，想要尽可能快地靠近 $r$，那么我们需要找到一个最大的 $p$ 使得 $l\bmod 2^p=0$ 且 $l+2^p\le r$，然后将 $l$ 加上 $2^p$ 即可，不断重复操作。

为什么能这样子呢？考虑如下二进制 $100110$，满足 $l\bmod 2^p=0$ 的 $p$ 有 $0$ 和 $1$（$2^p$ 分别为 $1$ 和 $2$），其实第一个 $1$ 及后面的位置。由于我们可以加上 $2^p$，那么就可以将那个位置加上 $1$，然后进位。能够发现，每次都加在前面的一定不会更劣。因为如果我们先加后面在加前面的话，万一位置过于靠后，那么就需要一位一位加起来；而先加上前面的在加后面的每次先把尽可能大的给加了，那么后面的小的就不会多加。

可能比较抽象，代码可能会要直观一点。

```kotlin
import java.util.*

val cin = Scanner(System.`in`)

var l = cin.nextLong()
val r = cin.nextLong()
val ans = ArrayList<Pair<Long, Long>>()  // 记录答案

fun main() {
  while (l < r) {                  // 一直循环直到 l == r
    val t = l                      // 保存 l 之前的值
    var p = 0                      // 思路中有详解
    for (i in 0..60) {             // 不断循环
      if (l + (1L shl i) > r) {    // 如果已经超出了 r
        break;                     // 直接退出循环
      }
      if (l % (1L shl i) == 0L) {  // 如果能够整除
        p = i                      // 记录下来
      }
    }
    l += 1L shl p                  // 更新 l
    ans.add(Pair(t, l))            // 加入答案数组
  }
  // 打印答案
  println(ans.size)
  for (i in ans) {
    println("${i.first} ${i.second}")
  }
}
```

---

## 作者：Eason_cyx (赞：0)

简单 D。

容易发现，要使划分的段数最少，每一段应当尽量长。

那么我们找到能被 $l$ 整除的最大的 $2$ 的正整数次幂（将这个结果记为 $p$），然后将 $l$ 作为这一段的左端点，此时右端点就是 $(\frac{l}{p}+1)\times p$，将 $l$ 设为这个值。反复这个过程，直到 $l=r$ 即可。

注意：在寻找过程中 $l$ 不能大于 $r$ 哦。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int ans1[100005],ans2[100005];
signed main() {
    long long l,r; cin >> l >> r;
    int cur = 0;
    while(l < r) {
    	int p = 1;
		while(l % p == 0 && ((l/p)+1)*p <= r) p *= 2;
		p /= 2;
		ans1[++cur] = l;
		ans2[cur] = ((l/p)+1)*p;
		// cout << "wwawawa" << l << ' ' << ((l/p)+1)*p << endl;
		l = ((l/p)+1)*p;
    }
    int ncur = cur;
    for(int i = 1;i <= cur;i++) {
    	if(ans1[i] == ans2[i]) ncur--;
    }
	cout << ncur << endl;
	for(int i = 1;i <= cur;i++) {
		if(ans1[i] == ans2[i]) continue;
		cout << ans1[i] << " " << ans2[i] << endl;
	}
    return 0;
}
```

---

## 作者：joe_zxq (赞：0)

# 思路

~~所以这年头 ABC 的 D 都这么水的吗（十四分钟切掉）？~~

考虑贪心。因为尽量要让总次数最少，于是我们每一次用的 $2$ 的幂尽可能大。

我们直接枚举指数（$10^{18} < 2^{64}$，可以放心枚举），找到最大的指数，相加得到新的数，然后用数组存起来最后输出就行啦。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll a[114514], x = 1;

int main() {

	ll l, r;
	cin >> l >> r;
	a[x] = l;
	for (ll i = l, u; i <= r;) {
		for (ll j = 1; j <= r; j *= 2) {
			if (i % j == 0 && i + j <= r) {
				u = j;
			}
		}
		x++;
		i += u;
		a[x] = i;
	}
	cout << x - 2 << "\n";
	for (ll i = 1; i < x - 1; i++) {
		cout << a[i] << " " << a[i + 1] << "\n";
	}

	return 0;
}

```

---

## 作者：int_stl (赞：0)

这道题其实很简单，思考一下就过了。

这道题其实是让我们把 $[l,r]$ 区间分成若干个长度为 $2^t$（$t \in \text{N}$） 的区间，满足任意 $L,R$  都可以表示为 $i \times 2^t,(i+1) \times 2^t$ 的形式，最小化区间表示个数。

考虑用贪心做，让区间长度尽量大，那么枚举当前 $L$ 的 $2^t$ 因子，在 $L + 2^t \le r$ 的情况下取最大值，令 $R \gets L + 2^t$ 即可。

代码十分简短，如下：
```cpp
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#define int long long
using namespace std;
vector < pair <int, int> > ans;
signed main() {
	int l, r;
	cin >> l >> r;
	int start = l;
	while (start < r) {
		// cout << start << " ";
		int power = pow(2, (int)log2(r));
		while (1) {
			if (power == 0) break;
			if (start % power == 0) {
				if (start + power <= r) {
					break;
				}
			}
			power /= 2;
		}
		ans.push_back({ start,start + power });
		start += power;
	}
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i].first << " " << ans[i].second << endl;
	}
}
```

---

## 作者：Fantasy_Segment_Tree (赞：0)

其实这道题就是暴力。

考虑想要让次数最少，就要每次找到一个最大的区间，所以每次找到最大的 $2^x \mid l$ 就可以了。然后在它的因数中找到最大的一个数 $t$ 使得 $l + t \leq r$ 即可，在找到 $t$ 之后令 $l \gets l + t$ 然后执行下一次流程。到了 $r$ 就退出。

还是简单的！

```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

long long p2[64], cnt, tnc;

long long c[100005][2], cc;

long long find(long long x) {
	long long l = 0, r = 63;
	while(l < r) {
		long long mid = (l + r) >> 1;
		if(p2[mid] > x) r = mid;
		else l = mid + 1;
	}
	return r;
}

int main() {
	p2[0] = 1;
	for(long long i = 1; i <= 63; i++) {
		p2[i] = p2[i - 1] << 1;
	}
	long long l, r;
	cin >> l >> r;
	while(l < r) {
		long long tmp = 0, tmp2 = l;
		if(l == 0) tmp = find(r) - 1;
		else {
			while((tmp2 & 1) == 0) {
				tmp2 >>= 1;
				tmp++;
			}
		}
		long long t = p2[tmp];
		while(l + t > r && tmp > 0) tmp--, t >>= 1;
		c[++cc][0] = l, c[cc][1] = l + t;
		l += t;
		//cout << endl;
		//cout << c[cc][0] << " " << c[cc][1] << endl;
	}
	cout << cc << endl;
	for(long long i = 1; i <= cc; i++) {
		cout << c[i][0] << " " << c[i][1] << endl;
	}
}
```

---

## 作者：PDAST (赞：0)

## 题目大意

给你一个左端点为 $l$，右端点为 $r - 1$ 的区间，现在你要把他们分成 $m$ 个“完美的区间”，我们对完美的区间的定义如下：左端点可以表示成 $2 ^ {i} j$，右端点可以表示成 $2 ^ {i} (j + 1) - 1$ 的区间。求 $m$ 的最小值。

## 思路

第一眼看数据，要开 long long。由于要使 $m$ 最小，所以我们要使每一个区间尽可能大，于是乎，我们先做一个预处理，把 $2 ^ {1}$ 到 $2 ^ {60}$ 存进一个数组里，接着一个 while 循环，条件是 $l < r$，每次从大往小查找刚才预处理的数组，找到一个小于等于 $l$ 且能整除 $l$ 并且构成的右端点不会超过给定的右端点的数，找到后把 $m$ 加一，新生成的左端点与右端点放进一个路径数组里，并把 $l$ 赋值成构成的右端点后，跳出循环即可。注意，由于 $l$ 有可能是 $0$ 所以循环判断时要特判一下。

## 代码

[AC 记录](https://atcoder.jp/contests/abc349/submissions/52356442)

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[101],m,way[10001][2],l,r;
signed main()
{
	cin>>l>>r;
	a[0]=1;
	for(int i=1;i<=61;i++){
		a[i]=a[i-1]*2;
	}
	while(l<r){
		for(int i=61;i>=0;i--){
			if((l%a[i]==0)&&(a[i]<=l||l==0)&&(l/a[i]+1)*a[i]<=r){
				m++;
				way[m][0]=l;
				way[m][1]=(l/a[i]+1)*a[i]; 
				l=way[m][1];
				break;
			}
		}
	}
	cout<<m<<"\n";
	for(int i=1;i<=m;i++){
		cout<<way[i][0]<<" "<<way[i][1]<<"\n";
	}
	return 0;
}

```

---

## 作者：Dtw_ (赞：0)

[atcoder](https://atcoder.jp/contests/abc349/tasks/abc349_d)
# 题目大意
给你一个定义，好的区间 $(l, r)$ 可以由非负整数 $i$，$j$ 表示成这样的形式 $(2^ij,2^i(j+1))$ 。

给定区间 $(L,R)$ 问你这个区间最少可以被分成几个好区间。

# 思路
我们可以考虑，对于每个被分解的区间我们希望它越长越好，并且每个端点都是由 $2^i$ 构成的那么就考虑枚举这个 $i$ 因为答案最多为 $60$ 左右所以肯定不会超时。我们考虑如何求 $j$。

我们可以把这个大的区间分解，每次分出来一个小区间，然后移动左端点。因为我们是挨着分的，所以我们要保证这一次分的区间的左端点要与上一次分的有段点重合，又因为每次分完后我们直接将左端点移到右端点处，所以 $j=\frac{l}{2^i}$，但要满足 $l \bmod 2^i = 0$ 并且 $l + 2^i(j+1) \leq r$，然后我们就可以挨个判断最后取最大值即可。（倒着枚举 $i$ 即可解决取最大值问题）。然后继续进行下一个好的区间的分解。

# Code
`a` 数组就是预处理的 $2^i$
```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define TRACE 1
#define tcout TRACE && cout

#define IN(o) insert(o)

#define fi first
#define se second

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 1e6 + 10;

vector<pair<int, int>> g;

int a[100];

signed main()
{
	a[0] = 1;
	for(int i=1; i<=61; i++)
	{
		a[i] = a[i-1] * 2;
	}
	int l, r;
	cin >> l >> r;
	while(l != r)
	{
		for(int i=61; i>=0; i--) //倒着枚举可不用求最大值
		{
			if(l % a[i] == 0) //要满足上述式子
			{
				int j = l / a[i];
				int t = a[i] * (j + 1);
				if(t <= r)
				{
					g.push_back({l, t});
					l = t; //把要操作的左端点跳到此次的右端点处
					break;
				}
			}
		}
	}
	cout << g.size() << endl;
	for(auto e : g)
	{
		cout << e.fi << " " << e.se << endl;
	}
	return 0;
}




```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc349_d)

## 思路

一道贪心。

首先我们想到：按照题目里叙述的要求，我们需要让每次找到的数列尽可能长。这时候我们想可以去找最大满足要求（即这时候的 $r<=R$）的 $i$ 来保证。

想到这里，$i$ 的变化趋势就可以看出来了：是一个先单调升，之后单调降的序列，即为一个**单峰曲线**。之后按照题意一步步模拟运算即可。

代码片段解释：

- ``now``：当前的节点所代表的 $2^i\cdot j$。

- ``nowi(ll now)``：当前的 ``now`` 所能取到的最大的 $i$。由于 $0\le L,R\le 2^{60}$，所以直接暴力枚举即可。计算方法为找到一个最大的 $i$ 使得 ``now`` 可以被 $2^i$ 整除且 $2^i<=R$。

- ``nowj(ll now)``：当前的 ``now`` 取最大 $i$ 时对应的 $j$，计算方法是 $\Large\frac{2^i\cdot j}{2^i}\normalsize=j$。

- ``nexti(ll now)``：在上文中曲线的后半部分下降时，下一个最大能取到的 $i$。由于 $0\le L\le R\le 2^{60}$，所以直接暴力枚举即可。计算方法为只要找到一个 $i$ 满足 $2^i\cdot(\Large\frac{2^i\cdot j}{2^i}\normalsize+1)=2^i\cdot(j+1)\le R$，就返回。

- 第一个循环中的 ``nowpow``：当前的 $2^i\cdot j$ 所对应的 $2^i$，为最大值。计算方法为 $2$ 的 ``nowi(now)`` 次方。

- 第二个循环中的 ``nowpow``：$2^i\cdot (j+1)<=R$ 时最大的 $2^i$。计算方法为 $2$ 的 ``nexti(now)`` 次方。

如果用位运算 ``1<<i`` 来代替 ``pow(2,i)`` 的话，记得**前面的 ``1`` 要转成 long long**，否则就会超出 int 范围。我这里是直接用 ``1LL`` 代替 ``1``。

## AC 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define pll pair<ll,ll>
#define fi first
#define se second
using namespace std;
vector<pll>v;
int cnt;
ll L,R;
ll nowi(ll now){
	ll t=0;
	while(now%(1ll<<t)==0&&(1ll<<t)<=R)++t;
	return t;
}
ll nowj(ll now){return now/(1ll<<nowi(now));}
ll nexti(ll now){
	for(ll i=nowi(now)-1ll;i>=0;--i){
		if((now/(1ll<<i)+1ll)*(1ll<<i)<=R)return i;
	}
	return (ll)"How genius am I!";//这行不会返回。
}
signed main(){
	cin>>L>>R;
	ll now=L;
	while((1ll<<nowi(now))*(nowj(now)+1ll)<R){//i 单增时。
		ll nowpow=1ll<<nowi(now);
		v.pb({now,(now/nowpow+1ll)*nowpow});
		now=(now/nowpow+1ll)*nowpow;
	}
	while(now<R){//i 单降时，2^i*j 需要比 R 小才能有 2^i*(j+1)。
		ll nowpow=1ll<<nexti(now);
		v.pb({now,(now/nowpow+1ll)*nowpow});
		now=(now/nowpow+1ll)*nowpow;
	}
	cout<<v.size()<<"\n";
	for(int i=0;i<v.size();++i)printf("%lld %lld\n",v[i].fi,v[i].se);
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/abc349/submissions/52375494)

---

## 作者：qw1234321 (赞：0)

较水，直接模拟即可。

首先，当 $n$ 不为 $0$ 时，贪心的取出当前左端点最多的 $2$，更新最大的右端点直到最大的右端点大于 $R$ 后截止，并枚举 $0$ 至左端点 $2$ 的因子个数，取出最大且不超过 $R$ 的右端点，然后继续更新。

否则，取到的第一段区间肯定为 $[0, r]$，其中 $r \lt R$ 且 $r$ 为离 $R$ 最近的 $2$ 的幂。

然后就把 $r$ 当做 $n$ 即可。

代码不放了，没用递归写的又丑又复杂。

---

