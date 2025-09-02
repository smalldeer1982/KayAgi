# Luntik and Subsequences

## 题目描述

有一个长度为 $n$ 的序列 $a_1,a_2,\dots,a_n$，和为 $s$，求这个序列有多少个子序列（可以为空）和为 $s-1$。

## 说明/提示

$1\le t\le1000,1\le n\le60,0\le a_i\le10^9$。
### 样例解释
第一组数据，满足条件的子序列为 $\{2,3,4,5\}$。

第二组数据，没有满足条件的子序列。

第三组数据，满足条件的子序列为 $\{\}$ 和 $\{0\}$。

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
2
1000 1000
2
1 0
5
3 0 2 1 1
5
2 1 0 3 0```

### 输出

```
1
0
2
4
4```

# 题解

## 作者：ZBAA_MKC (赞：5)

### 题目大意

给定一个长度为 $n$ 的序列 $a$，令数列 $a$ 中所有元素的和为 $s$，请你求出有多少种删数方案，可以使得操作后的序列 $a$ 的和为 $s-1$。

### 思路分析

很显然，因为输入的数都是非负整数，所以只有删去数列中的 $0$ 和 $1$ 才能符合要求。如果一个数列中既不包含 $0$ 也不包含 $1$，那么我们就输出 $0$，因为无论怎么操作也无法符合要求。 

对于 $0$，我们可以删除任意多个，而对于 $1$，我们只能删除一个。

记数列中 $0$ 的个数为 $b_0$，数列中 $1$ 的个数为 $b_1$。

对于 $1$ 的选择，我们有 $b_1$ 种选法，而对于 $0$，每一个 $0$ 有两种状态：删了或没删。所以 $b_0$ 个 $0$ 共有 $2^{b_0}$ 中选法。最终利用乘法原理可得最终答案为：$b_1 ·2^{b_0}$。

### 代码实现

**注意：一定要开 long long！！**

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        long long cnt0 = 0;
        long long cnt1 = 0;
        for (int i = 1; i <= n; i++)
        {
            long long x;
            cin >> x;
            if (x == 0)
            {
                cnt0++;
            }
            if (x == 1)
            {
                cnt1++;
            }
        }
        if (cnt0 == 0 && cnt1 == 0)
        {
            cout << 0 << endl;
        }
        else
        {
            cout << cnt1 * pow(2, cnt0) << endl;
        }
    }
    return 0;
}

```

---

## 作者：tzl_Dedicatus545 (赞：4)

**题意简述：**

- 有一个长度为 $n$ 的序列 $a_1,a_2,a_3 \cdots a_n$ ，和为 $s$，求这个序列有多少个子序列（可以为空）和为 $s-1$。
- 注意要开 `long long` ，否则对于极端情况 $n=60$ 且 $a_1=a_2=\cdots =a_{59}=0,a_{60}=1$ 时会炸。
- $ a_i \geq 0$

**方法讲解：**

注意到要求和为 $s-1$ ，显然等价于求方案数使其和为 $1$ （选出和为 $1$ 后，将其排除即可），又根据 $ a_i \geq 0$ 可知，选出的序列能且只能包含一个 $1$ 和若干个（可以为 $0$ ） $0$ ，不妨设一的个数为 `cnt1` ， 零的个数为 `cnt0` ，根据乘法原理可知，答案为 $2^{cnt0} \times \texttt{cnt1}$

建议评级：橙

**完整代码：**

注意如使用 `pow` 的话，它的返回值不是 `long long` ，对于大数 `cout` 会输出类似 `xxxe+xxx` 的形式，因此要转换一下，或者用龟速乘。


```cpp
//By: Luogu@Kamado Tanjirou(308854)
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int INF=0x3f3f3f3f;

signed main()
{
    int t;

    cin>>t;

    while(t--)
    {
        int n;

        cin>>n;

        int cnt0=0,cnt1=0;

        for(int i=1;i<=n;i++)
        {
            int t;

            cin>>t;

            if(t==0)
                cnt0++;
            if(t==1)
                cnt1++;
        }

        cout<<fixed<<setprecision(0)<<pow(2,cnt0)*cnt1<<endl;
    }

	return 0;
}

```


---

## 作者：Cht_master (赞：1)

- 题意简述：给定数列 $a$，记 $S=\sum a(i)$，求 $a$ 有多少个子序列 $b$ 满足 $\sum b(i)=S-1$。多组数据，$1\le t \le 10^3$，$1\le n\le 60$，$0\le a_i\le 10^9$。

- 题目解析：

  - 首先想到的是背包，即计算 $n$ 个物品恰好填满容积为 $m$ 的背包的方案数。但值域太大，显然是不可行的。~~（貌似可以反过来二分）~~
  - 发现 $S-1$ 这个条件很特殊。因为元素非负，所以要达到 $S-1$ 只能从 $a$ 中扣除若干个 0 和一个 1。记 0 的个数为 $cnt0$，1 的个数为 $cnt1$，根据乘法原理，答案为 $2^{cnt0}\cdot cnt1$。

- ```cpp
  //由于和为s-1且元素非负,所以可以选/不选0,然后看少选哪一个1即可.
  //更为普通的是计算n个物品恰好填满容积为m的背包的方案数.
  #include<bits/stdc++.h>
  #define ll __int128//不用开__int128,其实long long就够了.
  using namespace std;
  const int mxN(60);
  int n,a[mxN+5];ll cnt0,cnt1;
  ll Qpow(ll p){
  	if(!p)return 1;else if(p==1)return 2;
  	ll t(Qpow(p>>1));
  	if(p&1)return t*t*2;else return t*t;
  }
  void print(ll x){if(x>9)print(x/10);putchar(x%10+48);}
  int main(){
  	int T;scanf("%d",&T);
  	while(T--){
  		scanf("%d",&n),cnt0=cnt1=0;
  		for(int i(1);i<=n;++i)scanf("%d",&a[i]),cnt0+=(!a[i]),cnt1+=(a[i]==1);
  		print(Qpow(cnt0)*cnt1),putchar('\n');
  	}
  	return 0;
  }
  ```

---

## 作者：gaozitao1 (赞：0)

**题目大意**：有一个长度为 $n$ 的序列 $a_1,a_2,\dots,a_n$，和为 $s$，求这个序列有多少个子序列（可以为空）和为 $s-1$。

对于所有大于 $2$ 的数，必须选，否则不满足条件。

对于 $1$，不选其中一个，剩下的全部选择。

对于 $0$，可以选也可以不选。

也就是说，答案和 $0$ 的个数和 $1$ 的个数有关。

如果有 $x$ 个 $0$， $y$ 个 $1$，那么答案就是 $2^x\ y$ 。

注意结果可能爆 int 。

代码：
```cpp
#include<cstdio>
#include<iostream>
int main()
{
	int a,i,n,t,x,y;
	scanf("%d",&t);
	while(t--)
	{
		x=y=0;
		scanf("%d",&n);
		for(i=1; i<=n; ++i)
		{
			scanf("%d",&a);
			if(a==0)
				++x;
			else if(a==1)
				++y;
		}
		printf("%lld\n",(1ll<<x)*y);
	}
	return 0;
}
```

---

## 作者：Cat_shao (赞：0)

本题难度系数红题。

## 题目大意

给你一个长度为 $n$ 的序列（序列中的每一项都是非负整数），问你有多少个子序列使得 `子序列的和 = 原序列的和 - 1`。

## 解法

由于都是非负整数，删除 0 不会对子序列的和造成影响，删  $\ge 2$ 的数就会使 子序列的和 $\le$ 原序列的和 $- 2$ ，所以我们只能删一个 1。

我们在读入的时候统计整个序列中 0 的个数和 1 的个数，分别记为 $x, y$。

很显然对于每一个 0，都可以删或不删，所以只删 0 的不同子序列有 $2 ^ x$ 个。

我们必须删一个 1 ，可以在 $y$ 个 1 中任选一个删去。

所以共有 $2 ^ x y$ 个子序列与原序列的差等于 1 。

```cpp
//
// Created by Cat-shao on 2021/10/24.
//
 
#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
const int MAX_N = 1000100;
 
signed main()
{
    int T, n, a, zero, one;
    cin >> T;
    while (T--) {
        cin >> n;
        zero = one = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> a;
            if (a == 0) {
                zero ++;
            }
            if (a == 1) {
                one ++;
            }
        }
        cout << one * (1LL << zero) << endl;
    }
    return 0;
}
```

---

## 作者：Alex_Wei (赞：0)

1582B. [Luntik and Subsequences](https://codeforces.com/contest/1582/problem/B)

乘法原理和加法原理的简单应用。

对于每个 $0$，我们可以选择选或不选，因为不影响选出的数的和。对于所有 $1$，我们最多也必须选择 $1$ 个才能符合题意。选择其它数会让和减小至少 $2$，不符合题意。

因此，令 $1$ 的个数为 $a$，$0$ 的个数为 $b$，则答案为 $a\ \text{(有 a 种方法选 1)}\times 2^b\ \text{(对于每个 0 有 2 种方法，共有 b 个 0)}$。时间复杂度 $\mathcal{O}(n)$。需要开 long long。

```cpp
int main() {
	int T, n, v; cin >> T;
	while(T--) {
		ll a = 0, b = 0; cin >> n;
		while(n--) {
			cin >> v;
			if(v == 1) a++;
			else if(!v) b++;
		} cout << (a << b) << endl;
	}
	return 0;
}
```

---

## 作者：望月Asta (赞：0)

### 前置知识

乘法原理,补集转化.

### 朴素算法

先计算总和 $s$ ,再枚举所有子序列,判断其和是否为$s$.

时间复杂度 $\mathrm{O}(n \cdot 2^n)$,显然会超时.

### 对值域的算法

考虑维护一个桶, $B_i$ 表示和为 $i$ 的子序列的个数,每次添加一个数到桶里.

$a_i \le 10^9$,显然桶开不下.

### 正解

考虑补集转化,从 $a$ 中取出一个和为 $s - 1$ 的子序列后,剩下的所有元素和为 $1$ ,问题转化为求和为 $1$ 的子序列个数.

再看 $a$ 的值域 : $0 \le a_i \le 10^9$

发现其中不包含负数,于是和为 $1$ 的子序列形态为 $0,0,0,0 \cdots ,0,1$,最多只包含一个 $1$,此时这样的子序列个数只与序列中  $0$ 和 $1$ 的个数有关.

输入时统计序列中 $0$ 和 $1$ 的个数,记为 $x_0,x_1$

每个 $0$ 可以取或者不取,取出 $0$ 的方案数为 $2^{x_0}$.

只能取一个 $1$,取出 $1$ 的方案数为 $x_1$.

结果为 $2^{x_0} \cdot x_1$.

一定要记得开 ``long long`` !

### 代码

```cpp
#include<cstdio>
void solve() {
    int n;
    long long buc0 = 0,buc1 = 0;
    scanf("%d",&n);
    for(int i = 1;i <= n;++i) {
        int p;
        scanf("%d",&p);
        if(!p) ++buc0;
        else if(p == 1) ++buc1;
    }
    printf("%lld\n",(1ll << buc0) * buc1);// 这里不用1ll就会爆int
}

int main() {
    int T;
    scanf("%d",&T);
    while(T--) solve();
    return 0;
}
```

---

## 作者：KSToki (赞：0)

# 题目大意
给定一个长度为 $n$ 的数组 $a$，设 $s=\sum a_i$，求有多少种删数方案使得删除后的 $\sum a_i=s-1$。
# 题目分析
总和只减了 $1$，那么大于 $1$ 的数显然不能删，$1$ 能且仅能删除一个，每个 $0$ 都可以选择删或不删，那么设 $1$ 的个数为 $a$，$0$ 的个数为 $b$，答案即为 $a2^b$。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first
#define se second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,x,cnt0,cnt1;
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		cnt0=cnt1=0;
		while(n--)
		{
			x=read();
			if(x==0)
				++cnt0;
			if(x==1)
				++cnt1;
		}
		putll((1ll<<cnt0)*cnt1);
	}
	return 0;
}
```


---

