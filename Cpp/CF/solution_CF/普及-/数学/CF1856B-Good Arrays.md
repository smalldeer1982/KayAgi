# Good Arrays

## 题目描述

You are given an array of positive integers $ a $ of length $ n $ .

Let's call an array of positive integers $ b $ of length $ n $ good if:

1. $ a_i \neq b_i $ for all $ i $ from $ 1 $ to $ n $ ,
2. $ a_1 + a_2 +\ldots + a_n = b_1 + b_2 + \ldots + b_n $ .

Does a good array exist?

## 说明/提示

In the first test case, a possible good array is $ [3, 3, 3] $ . Some examples of not good arrays are:

- $ [8, 0, 1] $ — the array does not consist of only positive integers,
- $ [5, 2, 4] $ — the array does not have the same sum as the given array,
- $ [5, 2, 2] $ — the third element is equal to the third element of the given array.

In the second test case, $ [1, 1] $ is the only array of positive integers of length $ 2 $ that has the sum of it's elements equal to $ 2 $ . Since $ [1, 1] $ is not a good array, the answer is "NO".

## 样例 #1

### 输入

```
6
3
6 1 2
2
1 1
4
3 1 2 4
1
17
5
1 2 1 1 1
3
618343152 819343431 1000000000```

### 输出

```
YES
NO
YES
NO
NO
YES```

# 题解

## 作者：LHLeisus (赞：7)

## 题意简述：
> 给定一个序列 $a$，我们定义一个序列 $b$ 是好的当且仅当对于 $1\dots n$ 内的每一个 $i$，$a_i\neq b_i$ 且 $\sum_{i=1}^na_i=\sum_{i=1}^nb_i$($a_i$，$b_i$ 均为正整数)。

>现在有 $T$ 组数据，每组数据给定 $n$ 和序列 $a$，判断是否存在一个合法的序列 $b$。若存在输出 YES，否则输出 NO。


## solution
我们考虑让每一个 $a_i$ 加上或减去一个数，并且总和不变。

定义 $sum$ 为当前的变化总量。

可以贪心考虑：让每一个 $b_i$ 都为 $1$，并且让 `sum+=a[i]-1`，而 $a_i=1$ 的情况 $b_i$ 就变为 $2$，并让 `sum--`，这样可以保证当前的变化量最大，可供后面数的选择就多。

若最后 $sum<0$，由于每一步取的都是最大变化量，则说明无解

若 $sum\ge 0$，若存在 $b_i=2$，可以将 $sum$ 加到这个 $b_i$ 上；若不存在，则 $sum=\sum_{i=1}^na_i-1$，令 $b_n$ 加上 $sum$，一定 $>a_i$。当然了 $n=1$ 的情况一定无解，需要特判掉。

## code
```cpp
#include<cmath>
#include<cstring>
#include<string>
#include<utility>
#include<vector>
#include<queue>
#include<bitset>
#define FOR(i,a,b) for(register int i=a;i<=b;i++)
#define ROF(i,a,b) for(register int i=a;i>=b;i--)
#define mp(a,b) make_pair(a,b)
#define pll pair<long long,long long>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
inline int read();
typedef long long ll;
const int N=1e5+5;
const int INF=0x3f3f3f3f;
int n,m,k;
int main()
{
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		ll sum=0;
		FOR(i,1,n){
			scanf("%d",&k);
			if(k==1) sum--;
			else sum+=k-1;
		}
		if(sum<0||n==1) puts("NO");
		else puts("YES");
	}
	return 0;
}


inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f*x;
}
```
另：电脑没网，手机写的，大家点个赞支持一下qwq

---

## 作者：_Wind_Leaves_ShaDow_ (赞：7)

### 前言

~~赛时 WA 爆然后调了半个小时等到比赛结束后发现数组开小的我真的太屑了。~~

因为赛时打得不好，所以来写篇题解（生气）。

### 题意

给定长度为 $n$ 的 **正整数** 数列 $a$，问能否构造出另一个 **正整数** 数列 $b$，满足：

- 对于 $i(1\leq i\leq n)$，$a_i \ne b_i$。

- $\sum_{i=1}^n a_i=\sum_{i=1}^n b_i$。

### 思路

给一个很神奇的做法。

特判一下，一个数一定构造不出。

将序列从小到大排序，然后对于前 $n-1$ 个数，如果是 1 就变成 2，否则变为 1。然后在中途判断一下如果此时的和大于等于应该的总和就返回不可行。**因为我们每一步取的是可以的最小值**，此时如果仍然不行就真的不行了。

那么就剩最后一个数要处理了。我们设 $\sum_{i=1}^n a_i=sum,\sum_{i=1}^{n-1} b_i=sm$，那么此时 $b_n$ 应该为 $sum-sm$。如果 $a_n \ne sum-sm$，那么皆大欢喜，直接返回 $true$，如果 $s_n=sum-sm$，那么我们就需要从前面的数中拿一个出来加 $1$。可以证无论如何都是能够取出一个数让它代表的 $b_i$ 加 $1$ 后与原数不冲突的。此时 $sm$ 加上了 $1$，那么 $a_n$ 就不会等于 $sum-sm$。

**结论：无论如何，只要中间的构造没有出现冲突，达到了最后一个数一定能够构造成功。**

### 证明

**为什么最后一个数一定能保证前面有数可以实现加 $1$ 操作？**

假设前面有 $a_i=1$，那么则有 $b_i=2$，此时 $b_i \gets b_i+1$ 就好。

假设没有任何 $a_i=1$，但有任意一个数不为 $2$，则 $b_i=1,b_i+1=2$。发现此时 $b_i$ 仍然满足要求。

只剩下前面所有数都是 $2$ 的情况了。那么 $sum$ 应该为 $2(n-1)$，$sm$ 为 $n-1$，$b_n$ 应等于 $sum-sm$ 即 $n-1$，则 $a_n=n-1$。那么 $sum+a_n=sm+b_n$，即 $2(n-1)+n-1=n-1+n-1$，即 $3(n-1)=2(n-1)$。显然仅当 $n=1$ 时式子成立。但是我们之前特判过 $n=1$ 的情况，所以 $n \ne 1$。那么在这种情况下不会出现前面全都是 $2$ 而最后一个数出现冲突的情况。

所以就解决了。感觉很麻烦，但至少做出来了。

```cpp
#include <bits/stdc++.h>
#define int long long
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

using namespace std;
const int N=1e5+10;

int T,n,a[N];

inline bool solve(){//能否构造
	cin>>n;
	int sum=0,sm=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	if(n==1)return 0;//特判
	sort(a+1,a+n+1);
	for(int i=1;i<n;i++){
		if(a[i]==1)sm+=2;
		else sm++;
		if(sm>=sum)return 0;//中途大于就构造不成
	}
	return 1;//不然一定构造得成
}

signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)cout<<(solve()?"YES\n":"NO\n");
	return 0;
}
```

---

## 作者：yuyc (赞：5)

### 题意
对于一个长度为 $n$ 的正整数数组 $a$ ，能否构造出一个长度同样为 $n$ 的正整数数组 $b$ ，使得两数组相同下标对应的数两两不等，且数组中所有数的和相等。
### 思路
数的总和需要相等，意味着拿来构造数组 $b$ 的数有限。
![](https://cdn.luogu.com.cn/upload/image_hosting/tffae7rj.png)
那么，对于每个 $a_i$，就需要用尽可能小的数来构造相应的 $b_i$。根据题意可知，$b_i$ 最小可取 $1$，所以，我们就可以先将 $b_i$ 赋值为 $1$。以样例中的第一组数据为例：
![](https://cdn.luogu.com.cn/upload/image_hosting/cly9urzn.png)
此时，$a_1\not = b_1,a_3\not = b_3$ ，符合要求，但 $a_2\not = b_2$，这时只需让 $b_2+1$ 即可：
![](https://cdn.luogu.com.cn/upload/image_hosting/zl6brdpe.png)
至于剩下的 $5$,我们随随便便就能把它分配给 $b$，所以我们在实现代码的时候只需要考虑够不够分就行。
### 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[100005];
int main(){
	int T;
	cin>>T;
	while(T--){
		int n,cnt=0;
		ll s=0;
		cin>>n;
		for(int i=0;i<n;i++){
			cin>>a[i];
			if(a[i]==1) cnt++;//当a[i]=1时，b[i]需要多加1
			s+=a[i];//计算a数组中数的总和，即备用的数
		}
		if(n==1) cout<<"NO"<<endl;//特判
		else if(s-cnt-n>=0) cout<<"YES"<<endl;//备用的数减去需要用的数
		else cout<<"NO"<<endl;
	}
	return 0;
}
```


---

## 作者：信息向阳花木 (赞：2)

题目想让我们构造一个 **正整数** 序列 $b$，让 $b$ 的每一个元素和 $a$ 的都不相同，但和相同，问是否存在 $b$。

当 $n = 1$ 时，$b$ 不存在。

我们考虑特殊元素 $1$。设 $s = \sum_{i = 1}^{n}a_i$，则 $b$ 的最小值一定小于等于 $\lfloor \frac{s}{n} \rfloor$。可以用反证法证明。设 $a$ 中有 $cnt$ 个 $1$，则 $b$ 中最多有 $n - cnt$ 个 $1$。若 $\lfloor \frac{s}{n} \rfloor > 1$，则 $b$ 一定存在。否则，给 $b$ 填 $n - cnt$ 个 $1$，则 $b$ 剩下 $cnt$ 个位置的和为 $s - n + cnt$。若  $\lfloor \frac{s - n + cnt}{cnt} \rfloor = 1$，代表剩下 $cnt$ 的位置里必须还有 $1$， 则 $b$ 不存在。否则 $b$ 存在。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 100010;

inline void in(int &x)
{
	x = 0; bool f = 0; char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-') f = 1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c & 15);
		c = getchar();
	}
	x = f ? -x : x;
}

inline void out(int x)
{
	if(x < 0) putchar('-'), x = -x;
	if(x / 10) out(x / 10);
	putchar((x % 10) | 48);
}

int t, n;
int a[N];

int main()
{
	in(t);
	while (t -- )
	{
		in(n);
		
		long long sum = 0;
		int cnt = 0; 
		for (int i = 1; i <= n; i ++ )
		{
			in(a[i]);
			if(a[i] == 1) cnt ++;
			sum += (long long)a[i];
		}
		if(n == 1 || cnt == n) { puts("NO"); continue; }
		
		sum -= (n - cnt);
		if(cnt > 0) sum /= cnt;
		if(sum <= 1) puts("NO");
		else puts("YES");
	}
	return 0;
}


```

---

## 作者：LEle0309 (赞：2)

比赛时此题没调出来，然后第二天早上~~看题解~~想出来了。

[洛谷传送门](https://www.luogu.com.cn/problem/CF1856B) or [CF传送门](https://codeforces.com/contest/1856/problem/A)

#### 题目大意：

你有一个数组 $ a $ 存在一个数组 $ b $，使得：

- $ a_i \neq b_i $，其中 $ i \in [1,n] $。
- $ a_1 + a_2 +\ldots + a_n = b_1 + b_2 + \ldots + b_n $。

就被称作“好的数组”。

现在有 $ t $ 组数据，每组数据给你数列的长度 $ n $ 以及数列每一项的值，判断数列是否为“好的数组”。

#### 题目分析：

首先特判 $ n=1 $ 时肯定不可以。

我们构造一个数组 $ b $，先让它的每项为 $ 1 $，如果 $ a_i=1 $ 则变为 $ 2 $，剩下的和设为 $ s $。易得这种情况是满足条件 $ a_i \neq b_i $，其中 $ i \in [1,n] $ 的和最小数组。

如果 $ s<0 $，则说明 $ b $ 数组的和已经大于 $ a $ 数组。和最小的数组之和大于 $ a $ 数组之和，则说明一定不可以，直接输出 `NO`。

如果 $ s \ge 0 $ 且存在 $ b_i=2 $，则把 $ s $ 加到一个等于 $ 2 $ 的 $ b_i $ 上。此时这个 $ a_i $ 为 $ 1 $，一定可以。

如果 $ s\ge 0 $ 且不存在 $ b_i $ 是 $ 2 $，则 $ s $ 就是每一项 $ a_i $ 减去 $ 1 $ 的值之和，且所有 $ a_i $ 均大于 $ 1 $（不然 $ b $ 会有 $ 2 $），则 $ s \ge 2 $（$ n>1 $，因为 $ n=1 $ 已经特判）把 $ s $ 加到随便一个 $ b_i $ 上，则 $ b_i $ 一定大于 $ a_i $（此时 $ b_i $ 都是 $ a_i-1 $）。

上代码：
```cpp
#include<iostream>
using namespace std;
long long n,i,t,a,sum;//十年OI一场空，不开long long 见祖宗（WA了一次QAQ）
int main()
{
	cin>>t;
	while(t--)//t组数据
	{
		cin>>n;sum=0;//多测不清空，提交两行泪
		for(i=1;i<=n;i++)
		{
			cin>>a;
			if(a==1)sum--;
			else sum+=(a-1);//求sum
		}
		if(sum>=0&&n!=1)cout<<"YES\n";//满足条件
		else cout<<"NO\n";//注意换行
	}
	return 0;//完结撒花！
}
```

---

## 作者：jiangchen1234 (赞：2)

### 题意

$t$ 组数据。

每一组数据有一个 $n$，和一个数组 $a$。

我们要构造一个数据 $b$。

使得 $a_{1} + a_{2} + \cdots + a_{n} = b_{1} + b_{2} + \cdots + b_{n} $ 且对于任意的 $1 \le i \le n$ 都有 $a_{i}\ne b_{i}$。

### 思路
首先为了满足对于任意的 $1 \le i \le n$ 都有 $a_{i}\ne b_{i}$，我们可以把 $1$ 改成 $2$，其余的改成 $1$ 就可以满足了。

当 $n$ 为 $1$ 时，一定无解，其次当操作完之后的 $a$ 数组的和大于 $b$ 数组的和时，也一定无解（$b$ 数组的值已经最小了）。

其余情况都可以。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
#define rg register
#define IOS ios::sync_with_stdio(false);cin.tie(0); cout.tie(0)
using namespace std;
int t,n,a[2900001],res=0,sum=0;
signed main() {
	IOS;
	cin>>t;
	while(t--) {
		res = 0,sum = 0;
		cin>>n;
		for(rg int i(1); i<=n; ++i) {
			cin>>a[i];
			sum += a[i];
			if(a[i] == 1) res += 2;
			else res++;
		}
		if(n == 1 || res > sum) {
			cout<<"NO"<<endl;
		}else{
			cout<<"YES"<<endl;
		}
	}
	return 0;
}
```


---

## 作者：Crazyouth (赞：1)

**翻译**

给你一个 $n$ 个正整数的数组 $a$，请判断有没有 $n$ 个正整数的数组 $b$ 使 $\forall a_i\ne b_i$ 且 $\sum a_i=\sum b_i$。

**分析**

很 CF 的思维题。个人认为打 CF 的关键之处：把题目转换成尽可能数学的语言。

考虑把题目看成这样：你需要进行若干次操作，每次选择 $i,j(i\ne j)$，$a_i \leftarrow a_i+1,a_j \leftarrow a_j-1$，你要使整个序列与原先序列没有任何一个对应位置数相同且所有数为正整数。这样一来，第一个输出 `NO` 的情况就出来了：$n=1$。这种情况下你根本选择不了不同的 $i,j$。

进而，继续改变对题目的理解：你需要进行若干次操作，每次选择 $i,j(i\ne j,a_j>1)$，$a_i \leftarrow a_i+1,a_j \leftarrow a_j-1$，你要使整个序列与原先序列没有任何一个对应位置数相同。随之，下一个 `NO` 的情况也更显然了，当你找不到合适的 $a_j$ 来减，不就是 `NO` 吗？所以注意到序列中的 $1$ 是重要的，它决定了 $n\ne1$ 时是否能构造出 $b$。既然 $a_j>1$，且 $a_j$ 一定需要变化，那就考虑让数组中等于 $1$ 的数来当 $a_i$，找到大于 $1$ 的数不断分给每个是 $1$ 的数，让它们都变成 $2$。这样就得到式子了，若 $\displaystyle\sum_{i=1}^n [a_i
=1]>\displaystyle\sum_{i=1}^n [a_i\ne 1]\times a_i$，就是 `NO`，否则 `YES`。

**AC Code**
```
#include <bits/stdc++.h>
using namespace std;
long long a[int(1e5+10)];
int main()
{
	long long n,t;
	cin>>t;
	while(t--)
	{
		long long cnt=0,sum=0;//1的个数与非1数的和
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++)
		{
			if(a[i]==1) cnt++;
			else sum+=a[i]-1;
		}
		if(cnt>sum||n==1) cout<<"NO"<<endl;//两种情况
		else cout<<"YES"<<endl;
	}
	return 0;
}

---

## 作者：liruixiong0101 (赞：0)

## P0 题意：
给出一个长度为 $n$ 的**正整数**序列 $a$，让你求出是否有一个长度为 $n$ 的**正整数**序列 $b$ 满足以下条件：

1. $a_i\neq b_i(i\in[1,n])$
2. $\sum_{i=1}^{n} a_i=\sum_{i=1}^{n} b_i$

## P1 思路：
### 1.我的错误思路：
一开始我想到了错位，将 $a$ 序列错排到 $b$ 序列，也就是需要比较每个数出现的数量，但是这样的思路狠明显是错的，因为有些序列，你可以通过变换值的大小从而得到一个合法序列。

### 2.正确思路：
~~（我也不知道我的思路对不对捏。~~

由于此题的序列为**正整数**序列，所以我们肯定会想到让前 $n-1$ 个值为最小，这样就可以让最后一个值变为最大，也就是尽量不要让最后一个值为非正数，若最后一个值为非正数，那么输出 `NO`。操作如下：

- 若 $a_i=1$：$b_i:=2$。
- 若 $a_i\neq1$：$b_i:=1$。

很容易发现一个东西，若 $a_n\neq b_n$ 一定合法，但若 $a_n=b_n$，这样的情况只能调动前面的数，有两种情况可以考虑：

- 将 $b_n:=b_n+1$：这样只能让 $b_i:=b_i-1(i\in[1,n))$，这样又可以分为两种情况：

	- 若 $b_i=1$：$b_i-1=0$，不合法。
   - 若 $b_i=2$，则 $a_i=1$：$b_i-1=a_i$，不合法。
   
	这种情况是不可能出现的。
- 将 $b_n:=b_n-1$：这种情况必须先保证 $b_n\neq1$，接着只能让 $b_i:=b_i+1(i\in[1,n))$，这样只要出现了一个 $i(i\in[1,n))$，$b_i+1\neq a_i$ 那么就一定合法。

## P3 代码：
代码就很好实现了，代码如下：
```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int kMaxN = 1e5 + 5;

int T, n;
LL suma, sumb, a[kMaxN], b[kMaxN];

int main() {
  for (cin >> T; T; T--, suma = sumb = 0) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i], suma += a[i];
    }  // 输入序列a，记录序列a的元素总和
    for (int i = 1; i < n; i++) {
      b[i] = a[i] == 1 ? 2 : 1;  // 计算出b[1...n-1]
      sumb += b[i];              // 记录b[1...n-1]的和
    }
    if (sumb >= suma) {  // b[n]<=0
      cout << "NO\n";
      continue;
    }
    b[n] = suma - sumb;
    if (a[n] == b[n]) {  // 判断最后一位是否相同
      bool f = 0;
      for (int i = 1; i < n; i++) {
        if (b[i] + 1 != a[i] && b[n] > 1) {
          cout << "YES\n", f = 1;
          b[i]++, b[n]--;
          break;
        }
      }
      cout << (!f ? "NO\n" : "");
    } else {
      cout << "YES\n";
    }
  }
  return 0;
}
```

AC 记录：<https://codeforces.com/contest/1856/submission/217407090>



---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1856B)

这题很简单，但这位蒟蒻被罚了 $150$ 分。

如果你要满足题目中给的要求，那么我们在构造数组 $b$ 时只需要让数组 $b$ 中一半的元素变为 $a_i+1$，一半变为 $a_i-1$ 就行了。

但是我们发现 $1$ 不能再去减 $1$ 了，所以当 $a_i=1$ 时，$b_i$ 只能等于 $2$。如果数组 $a$ 内有 $k$ 个 $1$ 时，我们就需要用 $a$ 中不为 $1$ 的数去减掉一个数来使减去的数字之和能等于加上的 $1$ 的和，且这些数字减完后不能等于 $0$，也就是说这些数字最多只能减去 $a_i-1$。

所以我们现在要做的就是计算所有 $a_i$ 不为 $1$ 的数 $a_i-1$ 的和，看这个和是否能抵消因为 $a_i$ 为 $1$ 时加上的数。如果不为 $1$ 的数 $a_i-1$ 的和大于等于 $a_i$ 为 $1$ 的数的个数，就说明能抵消，就能保证 $\sum_{i=1}^{n}a_i=\sum_{i=1}^{n}b_i$，输出 `Yes`。否则就不能保证，输出 `No`。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100010];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		long long sum1=0,sum2=0;
		scanf("%d",&n);
		for(register int i=1;i<=n;i++) scanf("%d",&a[i]);
		if(n==1)
		{
			puts("No");
			continue;
		}
		for(register int i=1;i<=n;i++)
			if(a[i]==1) sum1++;
			else sum2+=a[i]-1;
		if(sum1>sum2) puts("No");
		else puts("Yes");
	}
	return 0;
}
```

---

## 作者：drah_yrev (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1856B)

## 思路
我们考虑让每一个 $a_i$，加上或减去一个数，并且总和不变。

定义 $sum$ 为当前的变化总量。

用贪心算法：

让每一个 $b_i$ 都为 $1$，并且让 $sum+a_i-1$。

而 $a_i=1$ 的情况下，让 $sum-1$，$b_i=2$，这样当前的变化越大，可供后面数的选择越多。

如果 $sum<0$，或 $n<0$，则无解。
## 代码
```cpp
#include<iostream>
using namespace std;
long long int n,x,sum,t;//温馨提示：不开 long long 见_________' 
int main(){
	cin>>t;// t组测试样例 
	while(t--){
		cin>>n;//输入n 
		x=0;//初始化sum 
		for(int i=1;i<=n;i++){
			cin>>x;//输入k(就是a[i]) 
			if(x==1)sum--;//判断x是否为1？如果是,sum--,让后面选择性更多。
			else    sum+=x-1;//让sum加上当前的数。
		}
		if(x<0||n==1)cout<<"NO"<<endl;//如果 x<0 或者 n等于1 (代表序列只有一个数字)。 
		else cout<<"YES"<<endl;
	}
	return 0;
}
```


---

