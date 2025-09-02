# Negatives and Positives

## 题目描述

Given an array $ a $ consisting of $ n $ elements, find the maximum possible sum the array can have after performing the following operation any number of times:

- Choose $ 2 $ adjacent elements and flip both of their signs. In other words choose an index $ i $ such that $ 1 \leq i \leq n - 1 $ and assign $ a_i = -a_i $ and $ a_{i+1} = -a_{i+1} $ .

## 说明/提示

For the first test case, by performing the operation on the first two elements, we can change the array from $ [-1, -1, -1] $ to $ [1, 1, -1] $ , and it can be proven this array obtains the maximum possible sum which is $ 1 + 1 + (-1) = 1 $ .

For the second test case, by performing the operation on $ -5 $ and $ 0 $ , we change the array from $ [1, 5, -5, 0, 2] $ to $ [1, 5, -(-5), -0, 2] = [1, 5, 5, 0, 2] $ , which has the maximum sum since all elements are non-negative. So, the answer is $ 1 + 5 + 5 + 0 + 2 = 13 $ .

For the third test case, the array already contains only positive numbers, so performing operations is unnecessary. The answer is just the sum of the whole array, which is $ 1 + 2 + 3 = 6 $ .

## 样例 #1

### 输入

```
5
3
-1 -1 -1
5
1 5 -5 0 2
3
1 2 3
6
-1 10 9 8 7 6
2
-1 -1```

### 输出

```
1
13
6
39
2```

# 题解

## 作者：AbsMatt (赞：10)

## [题目传送器](https://www.luogu.com.cn/problem/CF1791E)
## [更爽的阅读体验](https://yaohaoyou.blog.luogu.org/CF1791E-negatives-and-positives-solution)

# 题意
给定一个 $n$ 和一个长度为 $n$ 的数组 $a$，每次可以将相邻的两个数取相反数（即将 $x$ 变成 $-x$），问数组和的最大值，即 $\max{\{\sum_{i=1}^{n} a_i\}}$，共有 $t$ 次询问。
# 思路
我们先证明**可以将任意两个数都进行取相反数**：

若给两个位置 $i,j(1 \le i < j \le n)$，想要使 $a_i,a_j$ 都取相反数，则可以先将 $a_i$ 和 $a_{i+1}$ 进行取相反数，然后再将 $a_{i+1}$ 和 $a_{i+2}$ 进行取相反数，一直操作直到将 $a_{j-1}$ 和 $a_j$ 为止。此时 $a_i$ 和 $a_j$ 刚好取了 $1$ 次相反数，而 $a_k (k \in (i,j))$ 刚好取了 $2$ 次相反数，也就是没有取相反数。

综上，每次可以找两个数进行取相反数，那我们每次看当前最小的两个数的和是否为负数，如果是就将这两个数取相反数，否则结束程序，输出答案。时间复杂度就是 $O(t \times n \times \log_2n)$。

注：没开 ```long long``` 见祖宗，有多组数据。
## AC Code
```cpp
#include <bits/stdc++.h>  // 开始了
#define int long long
using namespace std;
const int maxn=2e5+10,inf=1e9+10;
int t,n,a[maxn],ans=0;
void solve(){
    ans=0;
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        ans+=a[i];  // 当前数组总和
    }
    sort(a+1,a+n+1);   // 排序
    for(int i=1;i<n;i+=2){
        if(a[i]+a[i+1]<0){  // 将这两个数进行操作
            ans-=(a[i]*2);
            ans-=(a[i+1]*2);
        }
    }
    printf("%lld\n",ans);  // 输出。
}
signed main(){
    scanf("%lld",&t);
    while(t--)  solve();
}
```

---

## 作者：JWRuixi (赞：2)

~~/yun，尽然还有一发罚时。~~

- 题意

给定长度为 $n$ 的序列 $\{a_n\}$，每次可以将序列相邻两个数取反，问进行若干次操作后序列和的最小值。

- 分析

首先考虑，每个区间最多被操作 $1$ 次，假设区间 $[l,r-1]$ 均被操作则等价于 $a_l,a_r$ 取反，于是问题转换成了选择序列中偶数个数取反，问和的最小值。

考虑到这一步已经非常简单了，如果负数的数量是偶数，显然直接将负数全部取反即可，否则不妨假设剩下数 $a_p$，那么只要求出 $a_p+\min\limits_{1\le i \le n,i \not = p}a_i$，将其取反，与原答案取 $\max$ 即可。

- code

```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#define LL long long
using namespace std;

namespace IO {
    char ibuf[(1 << 20) + 1], *iS, *iT;
#if ONLINE_JUDGE
#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
#else
#define gh() getchar()
#endif
#define reg register
    inline long long read () {
        reg char ch = gh();
        reg long long x = 0;
        reg char t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? ~(x - 1) : x;
    }
    inline void write(long long x) {
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        if (x > 9)
            write(x / 10);
        putchar(x % 10 + '0');
    }
}

using IO::read;
using IO::write;

const int maxn(2e5 + 500);
int T, n, a[maxn];
LL ans;

int main() {
    T = read();
    while (T--) {
        n = read();
        for (int i = 1; i <= n; i++) a[i] = read();
        int cnt = 0;
        for (int i = 1; i <= n; i++) cnt += (a[i] < 0);
        cnt = cnt - (cnt & 1);
        for (int i = 1; i <= n && cnt; i++) 
            if (a[i] < 0) a[i] = -a[i], --cnt;
        LL res = 0;
        for (int i = 1; i <= n; i++) res += a[i];
        ans = res;
        int pos = 0;
        for (int i = 1; i <= n; i++) if (a[i] < 0) { pos = i; break; }
        if (!pos) {
            write(ans), puts("");
            continue;
        }
        int mn = 1000000000;
        for (int i = 1; i <= n; i++) if (a[i] >= 0) mn = min(mn, a[i]);
        res -= 2 * (mn + a[pos]);
        ans = max(ans, res);
        write(ans), puts("");
    }
}
```

---

## 作者：LincW (赞：1)

目的显然是尽可能减少负数的数量，以及最小化不能消去的负数的绝对值。

先考虑尽可能减少负数的数量。

显然，只有两个负数相邻时，操作才能减少负数的数量。

所以需要找到“移动”负数的办法。

例：

| $a_1$ | $a_2$ | $a_3$ | $a_4$ |
| -----------: | -----------: | -----------: | -----------: |
| $1$ | $2$ | $3$ | $-4$ |



考虑进行一次操作，$i$ 取 $3$，按照定义，$a_3\gets -a_3$，$a_4\gets -a_4$，操作后的结果如下。

| $a_1$ | $a_2$ | $a_3$ | $a_4$ |
| -----------: | -----------: | -----------: | -----------: |
| $1$ | $2$ | $-3$ | $4$ |

可以发现负数“移动”到了 $a_3$。

类似的，一次操作可以把负数移动到它的当前位置减一或当前位置加一。

因为操作次数不限，所以可以将所有负数移动到数组的开头。

这里分 $2$ 种情况。

第一种情况：负数的数量是偶数。

只需要两两消去已经全部相邻的负数，就可以使数组中每一个数成为非负数，答案为 $\sum_{i=1}^{n}{|a_i|}$。

第二种情况：负数的数量是奇数。

这时，两两消去相邻的负数后会剩下一个负数。

显然，单个负数是不能消去的，又因为要最小化不能消去的负数的绝对值，所以要最小化这个剩下的负数的绝对值。

因为这个负数也可以随意移动，那么为了最小化这个负数的绝对值，将它移动到绝对值最小的一项上。

所以此时答案是 $\sum_{i=1}^{n}{|a_i|}-2\min\{\operatorname{abs}(a_i)\mid i\in [1,n]\}$。

总结：

$$\mathrm{ans}=\begin{cases}\sum\limits_{i=1}^{n}{|a_i|}&2\mid\sum\limits_{i=1}^n{[a_i<0]}\\\sum\limits_{i=1}^{n}{|a_i|}-2\min\{\operatorname{abs}(a_i)\mid i\in [1,n]\}&2\nmid\sum\limits_{i=1}^n{[a_i<0]}\end{cases}$$

```cpp
#include<iostream>
#include<algorithm>
#define endl '\n'
using namespace std;
typedef long long ll;
ll arr[200005];
ll read()
{
	ll res=0;
	int flag=1;
	char c=0;
	while((c>'9' || c<'0') && c!='-')
	{
		c=getchar();
	}
	if(c=='-')
	{
		flag=-1;
		c=getchar();
	}
	while(c<='9' && c>='0')
	{
		res*=10;
		res+=(ll)(c-'0');
		c=getchar();
	}
	return res*flag;
}
int main()
{
	ll t;
	cin>>t;
	while(t--)
	{
		ll n;
		cin>>n;
		ll nega=0;
		ll mi=1000000001;
		ll sum=0;
		for(int i=1;i<=n;++i)
		{
			cin>>arr[i];
			if(arr[i]<0) nega++;
			mi=min(abs(arr[i]),mi);
			sum+=abs(arr[i]);
		}
		if(nega%2==1)
		{
			sum-=(2*mi);
		}
		cout<<sum<<endl;
	 } 
	return 0;
}

```


---

## 作者：loser_seele (赞：1)

观察到一次操作不会影响负数个数的奇偶性，于是我们通过若干次操作显然可以将负数的个数变为 $ 0,1 $，取决于初始的奇偶性。

如果初始个数是偶数则可以全部变为非负数，答案为所有数绝对值之和。

否则我们必须选一个数变为负数，可以发现选绝对值最小的数总是最优，于是答案为其它所有数绝对值之和减去这个数的绝对值。

时间复杂度 $ \mathcal{O}(n) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int a[2000020],ans=0;
void gen(int n)
{
int f[2000020];
for(int i=1;i<=n;i++)
f[i]=i;
do
{
if(0)//add something here.
ans++;
}while(next_permutation(f+1,f+n+1));
}
#define Y cout<<"Yes"<<'\n'
#define N cout<<"No"<<'\n'
int cnt[26],p[26];
signed main()
{
int T;
cin>>T;
while(T--)
{
    int n,minn=2e9,cnt=0,sum=0;  
    cin>>n;
    for(int i=1;i<=n;i++)
    cin>>a[i],cnt+=(a[i]<0),a[i]=abs(a[i]),minn=min(minn,a[i]),sum+=a[i];
    if(cnt%2)
    cout<<sum-2*minn<<'\n';
    else
    cout<<sum<<'\n';
}
}
```


---

## 作者：5k_sync_closer (赞：0)

存在策略通过若干次操作取反任意偶数个数。

具体地，按如下策略取反 $a_x,a_y$：

- 进行 $y-x$ 次操作，第 $i$ 次操作取反 $a_{x+i-1},a_{x+i}$。

将所有负数两两取反。

若无剩余，此时 $\sum a_i$ 即为答案。

若剩余 $a_k$，此时的 $\sum a_i$ 与取反 $a_k,\min\limits_{i\neq k}a_i$ 后的 $\sum a_i$ 的最大值即为答案。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int T, n, m, c, p, a[200050];
long long q;
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = c = q = 0; i < n; ++i)
        {
            scanf("%d", a + i);
            if (a[i] < 0)
                ++c, p = i;
            q += a[i] = abs(a[i]);
        }
        if (c & 1)
        {
            m = a[p];
            for (int i = 0; i < n; ++i)
                if (i != p)
                    m = min(m, a[i]);
            printf("%lld\n", q - (m << 1));
        }
        else
            printf("%lld\n", q);
    }
    return 0;
}
```


---

## 作者：Gaode_Sean (赞：0)

本题有几个关键的性质：

$1.$ 每个数至多被选择 $1$ 次。

$2.$ 若对一段连续的区间 $[l,r]$ 进行操作，那么最终结果是 $a_l=-a_l$，$a_{r+1}=-a_{r+1}$，并且其他位置均不改变。

这样一来，对于序列中的任意两个数，我们都能使他们同时取反。

统计序列中负数的数量，设为 $cnt$。

若 $cnt$ 为偶数，则直接将序列中所有负数取反。

若 $cnt$ 为奇数，且序列中最小的非负整数绝对值小于序列中最大的负数的绝对值，则将序列中所有负数取反，并将最小的非负整数取反。

否则，将除最大负数的所有负数取反。

这样做能保证答案最优。

时间复杂度 $\mathcal{O}(T n \log n)$，空间复杂度 $\mathcal{O}(n)$。时间复杂度较劣的原因是因为我使用了排序。

[AC Code](https://codeforces.com/contest/1791/submission/191997324)

---

## 作者：arrow_king (赞：0)

## 思路

以下定义 $x_p$ 和 $x_n$ 分别为数列中正数和负数的个数。（$0$ 放在哪个里都可以，随便选一个就可以了）

根据 $a_i$ 和 $a_{i+1}$ 的符号情况，操作带来的变化会分为以下三种：

1. $x_p$ 增长 $2$，$x_n$ 减少 $2$。（$a_i,a_{i+1}<0$）
2. 不变。（$a_i<0,a_{i+1}>0$ 或 $a_i>0,a_{i+1}<0$）
3. $x_p$ 减少 $2$，$x_n$ 增加 $2$。（$a_i,a_{i+1}>0$）

可以发现 $\left\vert x_p-x_n\right\vert$ 的奇偶性是一定的。因为要么不变，要么增减一个偶数。

那么把 $x_n$ 最小化时，和就能取到最大值。

所以得到思路：首先计算 $x_n$ 最小值（初始时，$\left\vert x_p-x_n\right\vert$ 是奇数则最小值为 $1$，$\left\vert x_p-x_n\right\vert$ 为偶数则为 $0$），接下来将原数组所有元素取绝对值然后由小到大排序（显然，负数的绝对值越小对结果影响越小），最后根据计算出的 $x_p$ 最小值，选前 $x_p$ 个数作为负数，后面的的作为正数。

时间复杂度 $\mathcal O(n\log n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int t,n,a[200005];
il int abs(int x) {
	return x>=0?x:-x;
}
int main() {
	t=read();
	while(t--) {
		n=read();
		int po=0,ne=0;
		for(int i=1;i<=n;i++) {
			a[i]=read();
			if(a[i]<0) ne++;
			else po++;
			a[i]=abs(a[i]);
		}
		sort(a+1,a+n+1);
		po+=int(ne/2)*2;
		ne%=2;
		ll sum=0;
		for(int i=1;i<=ne;i++) sum+=-a[i];
		for(int i=ne+1;i<=n;i++) sum+=a[i];
		printf("%lld\n",sum);
	}
	return 0;
}
```

---

## 作者：ttq012 (赞：0)

[![pS6iWNR.png](https://s1.ax1x.com/2023/02/05/pS6iWNR.png)](https://imgse.com/i/pS6iWNR) 吐血。

对于两个 $<0$ 的位置，我们可以先将他们和相邻的位置执行操作，直到两个数相邻为止。

然后对这两个数执行操作即可。

于是序列到最后最多有 $1$ 个 $<0$ 的数。

然后判断：如果一开始 $<0$ 的数的个数是偶数，那么到最后可以没有 $<0$ 的数。

否则，只需要找到绝对值最小的那一个数，让她变成负数即可。

时间复杂度 $O(\sum n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int a[N],f[N][2];
signed main(){
  int T;
  cin>>T;
  while(T--){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    vector<int>pos;
    for(int i=1;i<=n;i++){
      if(a[i]<0)pos.push_back(i);
    }
    for(int i=1;i<=n;i++)a[i]=abs(a[i]);
    if(pos.size()%2==0){
      cout<<accumulate(a+1,a+n+1,0ll)<<'\n';
    }
    else{
      int id=-1,mi=1e18;
      for(int i=1;i<=n;i++){
        if(mi>a[i]){
          mi=a[i];
          id=i;
        }
      }
      assert(id!=-1);
      int sum=accumulate(a+1,a+n+1,0ll);
      sum-=2*a[id];
      cout<<sum<<'\n';
    }
    // for(int i=1;i<=n;i++)f[i][0]=f[i][1]=-1e18;
    // f[1][0]=f[1][1]=a[1];
    // for(int i=2;i<=n;i++){
    //   f[i][0]=max({f[i-2][0]+a[i]+a[i-1],f[i-2][1]+a[i-1]+a[i],f[i-1][0]+a[i],f[i-1][1]+a[i]});
    //   f[i][1]=max({f[i-2][0]-a[i-1]-a[i],f[i-2][1]-a[i]-a[i-1]});
    // }
    // for(int i=1;i<=n;i++)cout<<f[i][0]<<' '<<f[i][1]<<'\n';
    // cout<<max(f[n][0],f[n][1])<<'\n';
    // for(int i=1;i<n;i++){
    //   if(a[i]+a[i+1]<0)a[i]=-a[i],a[i+1]=-a[i+1];
    //   else if(a[i]+a[i+1]==0){
    //     if(a[i]<a[i+1])swap(a[i],a[i+1]);
    //   }
    // }
    // cout<<accumulate(a+1,a+n+1,0ll)<<'\n';
  }
  return 0;
}
```

---

