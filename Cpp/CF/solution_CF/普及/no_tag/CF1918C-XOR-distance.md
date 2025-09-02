# XOR-distance

## 题目描述

You are given integers $ a $ , $ b $ , $ r $ . Find the smallest value of $ |({a \oplus x}) - ({b \oplus x})| $ among all $ 0 \leq x \leq r $ .

 $ \oplus $ is the operation of [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR), and $ |y| $ is [absolute value](https://en.wikipedia.org/wiki/Absolute_value) of $ y $ .

## 说明/提示

In the first test, when $ r = 0 $ , then $ x $ is definitely equal to $ 0 $ , so the answer is $ |{4 \oplus 0} - {6 \oplus 0}| = |4 - 6| = 2 $ .

In the second test:

- When $ x = 0 $ , $ |{0 \oplus 0} - {3 \oplus 0}| = |0 - 3| = 3 $ .
- When $ x = 1 $ , $ |{0 \oplus 1} - {3 \oplus 1}| = |1 - 2| = 1 $ .
- When $ x = 2 $ , $ |{0 \oplus 2} - {3 \oplus 2}| = |2 - 1| = 1 $ .

Therefore, the answer is $ 1 $ .

In the third test, the minimum is achieved when $ x = 1 $ .

## 样例 #1

### 输入

```
10
4 6 0
0 3 2
9 6 10
92 256 23
165 839 201
1 14 5
2 7 2
96549 34359 13851
853686404475946 283666553522252166 127929199446003072
735268590557942972 916721749674600979 895150420120690183```

### 输出

```
2
1
1
164
542
5
3
37102
27934920819538516
104449824168870225```

# 题解

## 作者：BIG_CUTE_BUG (赞：5)

[题传](https://www.luogu.com.cn/problem/CF1918C)

## 思路

想让绝对值之差最小，就得让两数尽量接近。同时给两数异或 $x$ 的操作，实际就是选择二进制下某些位，并将两数在该位的值取反。因此让大的数尽量小，小的数尽量大。

称对某一位取反为一次操作。

由此对每一位贪心，分两种情况：

1. 该位两数相同：取反后对答案无影响，故不操作。

2. 该位两数不同：操作或保持，使得较大的数的这一位为 $0$，较小的数的这一位为 $1$。

另外，如果将第一位不相同的位取反，那两数的大小关系是会发生变化的，所以要从第一位不相同的位的后一位开始贪心。

但注意到 $x$ 有一个上界，贪心过程中保证操作总值不超过这一个上界即可。（也就是每次操作的时候看 $x$ 加当前操作值看超不超过上界，超过就不往后加了）


```cpp
#include<bits/stdc++.h>
using namespace std;
long long t, a, b, u, us;
inline long long lg(long long x) {return 63ll^ __builtin_clzll(x);}
signed main()
{
	ios:: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>> t;
	while(t--)
	{
		us= 0;
		cin>> a>> b>> u;
		if(a== b) {cout<< 0<< '\n'; continue;}
		if(b> a) a^=b^=a^=b;
		for(int i= min(lg(a^ b)- 1, lg(u)); i>= 0; i--)
		{
			if((a& (1ll<< i))== (b& (1ll<< i))) continue;
			if((a& (1ll<< i)) && ((us| (1ll<< i))<= u)) a^= (1ll<< i), b^= (1ll<< i), us|= (1ll<< i);
		}
		cout<< a- b<< '\n';
	}
	return 0;
}
```

---

## 作者：GXZJQ (赞：1)

# CF1918C XOR-distance 题解

- 更新于 $2024$ 年 $06$ 月 $16$ 日：更改了一处笔误，感谢  wangziwenhk 的指正。

[题目传送门](https://www.luogu.com.cn/problem/solution/CF1918C)

## 题目分析
由于绝对值永远是恒大于等于 $0$ 的，所以要使得绝对值最小，就要使两数尽可能的接近。

在 C++ 中，异或操作为 `^`，其实质是就是对当前位进行取反（由 $1$ 变为 $0$，由 $0$ 变为 $1$）。

通过上面的分析，相信各位已经知道了这道题应该使用贪心来做。对于每一次的贪心，有两种情况：

- 如果这位数字相同，就不用对其进行操作；
- 如果这位数字不同，就要使较大的一个数变小，较小的一个数变大（让大数这一位变为 $0$，让小数这一位变成 $1$）。

但是这里有个问题，如果将第一位不同的位取反，就会导致这两个数的大小关系转换。所以我们要从第一位不相同的位的**后一位**开始贪心运算。

与此同时，注意题目描述，$x$ 有一个上限，在过程中要保证操作次数不大于 $x$ 即可。

说了这么多，上代码：

## 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a, b, r, x;
long long ta[100], numa, tb[100], num2;
long long f[100][3];
bool flag;
int t;
//十年竞赛两茫茫，不开long long见祖宗
int main() {
	cin >> t;
	while (t--) {
		numa = num2 = 0;
		memset(f, 0, sizeof f);
		x = 0;
		flag = 1;
		//多测不清空，爆零两行泪
		cin >> a >> b >> r;
		if (a > b) swap(a, b);//翻转大小
		for (long long i = 60; i >= 0; i--) {
			long long a2 = a & (1ll << i);
			long long b2 = b & (1ll << i);
			if (a2 != b2) {
				if (flag) flag = 0;//判断是否是不同的第一位
				else if (!a2 && x + (1ll << i) <= r) {
					x += (1ll << i);
					a ^= (1ll << i);
					b ^= (1ll << i);//如题所说要用特殊运算符
				}
			}
		}
		cout << b - a << endl;
	}
	return 0;
}
```

---

## 作者：wangyishan (赞：1)

# CF1918C XOR-distance 题解

### 题意

给定三个正整数 $a,b,r$，请你选择一个非负整数 $x\in[0,r]$，使 $| (a\oplus x)-(b\oplus x)|$ 最小。其中 $\oplus$ 为按位异或运算符，$|m|$ 表示 m 的绝对值。

多测，$a,b,r\le10^{18}$ 。

### 题解

首先让我们想一下没有 $r$ 的时候怎么做。

设 $a>b$ 且 $a$ 的二进制表示为$A_1 A_2 … A_n$ ，$b$ 的二进制位表示为 $B_1 B_2 … B_n$。

我们可以构造一个这样的 $x$ : 对于 $a$ 与 $b$ 不同的第一个二进制位 $k$ ，我们留下 $a$ 的值，把 $B_k$ 异或成 $0$。在这之后，我们在所有不同的二进制上都把 $A_m$  异或成 $0$，留下 $B_m$。可以证明，这样一定是最小的。

加上 $r$ 的限制条件，我们发现因为给 $b$ 大数一定好于小数，所以我们二进制位从大到小遍历，只要能加给 $b$ 就加，一直到加不动为止。

时间复杂度单次 $\mathcal O(\log \max(a,b))$ 。

Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define NOOO                                                                   \
  { cout << "NO" << endl; }
#define YESS                                                                   \
  { cout << "YES" << endl; }
#define int long long
int a, b, r, x = 0;
int ta[100], cnta = 0, tb[100], cntb = 0;
int f[100][3];
void solve() {
  cnta = cntb = 0;
  memset(f, 0, sizeof f);
  cin >> a >> b >> r;
  if (a > b)
    swap(a, b);
  bool flag = 1;
  int x = 0;
  for (int i = 60; i >= 0; i--) {
    int ba = a & (1ll << i);
    int bb = b & (1ll << i);
    if (ba != bb) {
      if (flag)
        flag = 0;
      else if (!ba && x + (1ll << i) <= r) {
        x += (1ll << i);
        a ^= (1ll << i);
        b ^= (1ll << i);
      }
    }
  }
  cout<<b-a<<endl;
  return;
}

signed main() {
  ios::sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
```



---

## 作者：Eternity_Yoke (赞：1)

## 题目大意
给定 $a,b,r$，求 $\left|\left(a\oplus x\right)-\left(b\oplus x\right)\right|$ 的最小值。$0\leqslant x\leqslant r$。
## 解题思路
考虑贪心。将 $a$ 的值取 $a,b$ 中的较大值，$b$ 则反之。从二进制的最高位起，寻找第一个 $a_i>b_i$ 即 $a_i=1,b_i=0$ 的位置，往后遍历。

每当出现上述情况就对 $ans$ 加上此位二进制所对应的数，如果该数大于 $r$ 则放弃，反之则加上。
## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int t,cnta,cntb,cnt;
int fa[105],fb[105];
ll a,b,r,ans;
int main()
{	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{	cin>>a>>b>>r;
		if(a<b)swap(a,b);
		ll x,y;
		x=a;y=b;
		cnt=1;ans=0;
		memset(fa,0,sizeof(fa));
		memset(fb,0,sizeof(fb));
		cnta=0;cntb=0;
		while(a)
		{	fa[++cnta]=a%2;
			a/=2;
		}
		while(b)
		{	fb[++cntb]=b%2;
			b/=2;
		}
		for(int i=cnta;i>=1;i--)
		if(fa[i]==1&&fb[i]==0)
		{	cnt=i;
			break;
		}
		for(int i=cnt-1;i>=1;i--)
		{	if(fa[i]>fb[i])
			{	if(ans<=r-(ll)pow(2,i-1))
				ans+=(ll)pow(2,i-1);
			}
		}
		cout<<llabs((x^ans)-(y^ans))<<endl;
	}
	return 0;
}
```


---

## 作者：zhanglh (赞：0)

贪心。

要使两个数的差的绝对值最小，就是让两个数尽可能的接近。

因此，题意就转化为了，找到一个 $x$，让两个数异或 $x$ 得到的值尽可能的接近。

让较大数异或后尽量小，让较小数异或后尽量大。

对于二进制某一位，如果两数在该位相同，则 $x$ 在这一二进制位上取值任意。若不同，则与较大数保持一致。

注意：应使得异或后两数原本从高到低第一位不一致的二进制位仍保持原状（即较大数仍为 $1$，较小数仍为 $0$），否则会改变两数的大小关系。

设较大数为 $b$，时间复杂度 $O(\log b)$。

```
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll a, b, r, f[70];

void solve() {
    cin >> a >> b >> r;
    if (a > b) swap(a, b);
    ll t = 70;
    for (ll i = 0; (1ll << i) <= b; i++) {
        //cout << (a & (1ll << i))<< " " << (b & (1ll << i)) << "\n";
        if (((a & (1ll << i)) != (b & (1ll << i)))) {
            t = i;
        }
    }
    //cout << t << "\n";
    memset(f, 0, sizeof f);
    for (ll i = 0; i < t; i++) {
        if (((a & (1ll << i)) ^ (b & (1ll << i))) != 0) {
            if (b & (1ll << i)) {
                f[i] = 1;
            }
        }
    }
    ll x = 0;
    for (int i = 69; i >= 0; i--) {
        if (f[i] == 0) continue;
        if (x + (1ll << i) <= r) {
            x += (1ll << i);
        }
    }
    cout << abs((a ^ x) - (b ^ x)) << "\n";
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    int tcs;
    cin >> tcs;
    //tcs = 1;
    while(tcs--) {
        solve();
    }
    return 0;
}

```

---

## 作者：Special_Tony (赞：0)

# 思路
因为最后求的是绝对值，所以我首先使计算过程中 $a$ 始终比 $b$ 大。

设 $a_i$ 表示 $a$ 的二进制第 $i$ 位上的数字，$b_i$ 表示 $b$ 的二进制第 $i$ 位上的数字，若 $a_i=b_i$，则 $x$ 包不包含 $2^i$ 都无所谓，不如不选；若把 $i$ 从大到小枚举，$a_i=1$ 且 $b_i=0$，此时如果 $r$ 还够用且异或后 $a>b$ 则选上，并把 $r-2^i$。
# 代码
```cpp
# include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int t;
ll a, b, r;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> a >> b >> r;
		if (a < b)
			swap (a, b);
		for (int i = 62; ~i; -- i)
			if ((1ll << i) <= r && (1ll << i & a) && ! (1ll << i & b) && (a ^ (1ll << i)) >= (b ^ (1ll << i)))
				a ^= 1ll << i, b ^= 1ll << i, r -= 1ll << i;
		cout << a - b << '\n';
	}
	return 0;
}
```

---

## 作者：Fubaogege (赞：0)

#### 算法
贪心。
#### 思路
我们可以用贪心完成此题。

$x$ 有上线，贪心每次过程不超过此上限就行。

就 $2$ 种情况：

考虑两位数相同：

- 当两位数相同，取反后不会变化，也不会影响答案，所以不需要操作。

最后考虑两位数不同：

- 使大数位为 $0$。
- 小数位为 $1$。

考虑完按照上述思路写贪心代码就行。

---

## 作者：w9095 (赞：0)

[CF1918C XOR-distance](https://www.luogu.com.cn/problem/CF1918C)

考虑对 $a,b$ 进行二进制分解，在二进制位中进行计算。

设 $a_i$ 表示数 $a$ 二进制第 $i$ 位。如果 $a_i=b_i$，则不需要对 $x_i$ 进行任何构造。但如果 $a_i$ 不等于 $b_i$，把 $x_i$ 置为 $1$ 只能改变 $a_i$ 和 $b_i$ 的大小关系，不能使其相等。

所以，我们从高位开始考虑，因为高位影响一定超过低位影响，所以不需要管对低位的影响，计算比较方便。首先找到第一个 $a_i$ 与 $b_i$ 的大小关系，根据进制位定义，可以推出高位影响一定超过低位影响，$a$ 和 $b$ 的大小关系就已经确定了。接下来，就是在下面的几位中，尽量使较大的数较小，较小的数较大即可，不需要管对低位的影响。

注意在修改时 $x$ 的值不能超过 $r$。

时间复杂度为 $O(t\log n)$，可以通过。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,m,r,a[200][2];
int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	long long flag=-1,ans=0;
	   	scanf("%lld%lld%lld",&n,&m,&r);
	   	for(int i=0;i<=63;i++)
	   	    {
	   	    if(n&((long long)1<<i))a[i][0]=1;
	   	    else a[i][0]=0;
	   	    if(m&((long long)1<<i))a[i][1]=1;
	   	    else a[i][1]=0;
	   	    }
	   	for(int i=63;i>=0;i--)
	   	    {
	   	    if(a[i][0]==a[i][1])continue;
	   	    if(flag==-1)
	   	        {
	   	       	if(a[i][0]>a[i][1])flag=1;
	   	       	else if(a[i][0]<a[i][1])flag=0;
	   	       	ans+=((long long)1<<i);
				}
			else if(a[i][0]>a[i][1])
			   {
			   	if(flag==1&&r>=((long long)1<<i))r-=((long long)1<<i),ans-=((long long)1<<i);
			    else if(flag==0)ans-=((long long)1<<i);
			    else if(flag==1)ans+=((long long)1<<i);
			   }
			else if(a[i][0]<a[i][1])
			   {
			   	if(flag==0&&r>=((long long)1<<i))r-=((long long)1<<i),ans-=((long long)1<<i);
			    else if(flag==1)ans-=((long long)1<<i);
			    else if(flag==0)ans+=((long long)1<<i);
			   }
			}
		printf("%lld\n",ans);
	   }
	return 0;
} 
```


---

## 作者：Remarks (赞：0)

### 1.0

考虑对于 $a,b$ 进行二进制拆分。我们假定 $a>b$ （如果 $a>b$ 就交换）。

我们**假定在操作完后，依然有 $a>b$**，那么对于每一位的情况有如下：

（为了方便表述，$a_i$ 即为 $a$ 在二进制意义下的，从右至左第 $i$ 个位置上的值）。

| $a_i$ | $b_i$ | $a_i-b_i$ | $(a_i \oplus 1)-(b_i\oplus 1)$ |
| :----------: | :----------: | :----------: | :----------: |
| 1 | 1 | 0 | 0 |
| 1 | 0 | 1 | -1 |
| 0 | 0 | 0 | 0 |
| 0 | 1 | -1 | 1 |

### 1.1

**假定在操作完后，依然有 $a>b$**，所以仅当 $a_i =1, b_i=0$ 的时候我们会考虑在这一位上异或 $1$ 。从高位向地位考虑，如果前面能异或而选择不异或，即使后面所有位置全部异或也不会使答案更优，所以我们可以贪心的考虑，只要令 $x$ 在二进制位 $i$ 上 $+1$ 不会使 $x>r$ ，且满足 $a_i =1, b_i=0$ 的条件，选择他一定最优。

### 1.2

那么操作完后 $a<b$ 呢？

考虑，当且仅当我们舍弃 $a$ 与 $b$ 共有的一段**极长**前导 1 后，下一位必定是 $a_i=1,b_i=0$ 。假若我们在这一位上异或了 1，便会使得 $a$ 与 $b$ 大小变化。但是同时也发现，这样操作等同于在 $i$ 位置后的每一位都对 $a$ 与 $b$ 异或 1，而后者会使得 $x$ 增加 $(1<<i)-1$ ，前者增加 $(1<<i)$ ，而效果完全相同，所以这样是一定更不优的。

我们只需要跳过 $a$ 与 $b$ 共有的一段**极长**前导 1 与其的下一位之后，即可满足 1.1 中操作完成不改变 $a$ 与 $b$ 的大小关系大的条件。按照 1.1 所述的方法，贪心即可通过本题。

另：使用 `1ll<<k` 的方法获得一个超出 int 范围的 $2^k$ 。

code ： https://codeforces.com/contest/1918/submission/244123673

---

