# Maximum Median

## 题目描述

$Imakf$ 给您一个长度为 $n$ 的数组 $a$，$(n$ 为奇数 $)$ 您可以对数组进行如下操作

-  选择数组中的一个元素，使其增加 $1$

您有 $k$ 次操作机会，请最大化数组的中位数 

一组数据的中位数是指数组从小到大排序后位于最中间的数，例如 $[1,5,2,3,5]$ 的中位数是 $3$. 


第二行 $n$ 个整数表示数组 $a\ (1 \leq a_i \leq 10^9)$

## 说明/提示

样例 $1$ 中，对 $a_2$ 进行两次操作，数组变为 $[1,5,5]$

样例 $2$ 中，一种最佳操作是使数组变为 $[1,3,3,1,3]$ 

样例 $3$ 中，一种最佳操作是使数组变为 $[5,1,2,5,3,5,5]$

## 样例 #1

### 输入

```
3 2
1 3 5
```

### 输出

```
5```

## 样例 #2

### 输入

```
5 5
1 2 1 1 1
```

### 输出

```
3```

## 样例 #3

### 输入

```
7 7
4 1 2 4 3 4 4
```

### 输出

```
5```

# 题解

## 作者：_HMZ_ (赞：8)

## 解题思路：

看见各位大佬都是用的二分， ~~本蒟蒻表示瑟瑟发抖~~。

所以我想写一个比较简单的方法。

首先，对于每个在中位数之前的数字，不动即可。

因为你要变就得比当前中位数大，不然变来变去中位数根本就没动。

但是你要变的比当前大的话，还不如直接增加中位数。

再看后面的数字，如果没有和当前中位数相等的数，那么就直接加。

否则，就得把跟当前一样的所有数都加上。

如果你不加，那么当前数变大后一定会有和当前相等的数的排名降下来。

但是注意要开 long long，十年 OI 一场空，不开 long long 见祖宗。

## AC代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
#define int long long
int n,k,a[1000005],cnt;
signed main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+1+n);//排序，好求中位数。
    for(int i=n/2+1;i<=n;)//中位数以前的都不用考虑。
    {
        int now=a[i];
        while(a[i]==now)//看有几个跟当前相等的数
            ++cnt,++i;
        if(i>n)
            break;
        int c=(a[i]-now)*cnt;
        if(k>c)
            k-=c;//如果 k 还够那么直接加。
        else
        {
            cout<<k/cnt+now<<endl;
            return 0;
        }
    }
    cout<<a[n]+k/cnt;
    return 0;
}
```


---

## 作者：МiсDZ (赞：7)

最大化中位数，看上去就可以二分，再看数据范围二分的思路就得到确定了。

复杂度为：区间$\log2000000$，check$\Theta(n)$，合起来可以跑过。

总体思路是：
1. 因为数列最小值为1，那么左端点设为1
2. 右端点设为$a_i$的最大值与$k$的最大值之和，数列修改后最大值不会超过此值
3. 将序列排序
4. check只需要按照中位数的性质，从$\frac{n+1}{2}$开始，向右扫，遇到比前一个小的就一直加到与前一个相等即可，如果用完了但还没有到最后就代表该答案不正确

二分正确性的证明是显然的，随着中位数的增大，需要为其铺路的数会更多，修改的自然会更多。qwq

下面是代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define REP(i,e,s) for(register int i=e; i<=s; i++)
#define DREP(i,e,s) for(register int i=e; i>=s; i--)
#define file(a) freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define ll long long

ll read() {
	ll x=0,f=1,ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN=200000+10;

ll n,k,a[MAXN];

bool check(ll x) {
	int cnt=0;
	REP(i,(n+1)/2,n) {
		if(a[i]>=x) return 1;
		if(x-a[i]>k-cnt) return 0;
		cnt+=x-a[i];
	}
	return 1;
}

int main() {
	n=read(),k=read();
	REP(i,1,n) a[i]=read();
	sort(a+1,a+1+n);
	
	ll l=1,r=2000000000+1;
	while(l<r) {
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1;
		else r=mid;
	}

	printf("%d\n",r-1);
	return 0;
}
```

---

## 作者：Zechariah (赞：2)

存在唯一的最优策略：排序后，从中间开始，往后增加  
也就是从中间(第$i$个)，逐渐增加到第$i+1$,$i+2$个  
为什么不去加比当前中位数小的数呢？  
如果你加了，只会出来一个跟当前中位数一样的数，然后要想增加中位数，你得把前面几个和后面几个都增加，也就是说加比中位数小的数是徒劳的  
直接乱搞就完事

```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define jh(x, y) x ^= y ^= x ^= y
#define loc(x, y) (x - 1) * m + y
#define rg register
#define inl inline
#define PI 3.141592654
typedef long long ll;
const int N = 2e5 + 5, INF = 0x3f3f3f3f, mod = 998244353;
using namespace std;
namespace fast_IO {
	inl ll read() {
		rg char c;
		rg ll x = 0;
		rg bool flag = false;
		while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
		if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
		while ((c = getchar()) != ' ' && c != '\n' && c != '\r' && ~c)
			x = (x << 1) + (x << 3) + (c ^ 48);
		if (flag)return -x; return x;
	}
	inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
	inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
	void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
ll a[N];

int main() {
	rg ll n = fast_IO::read(), k = fast_IO::read(), cnt = 1;
	for (rg int i = 1; i <= n; ++i)a[i] = fast_IO::read();
	sort(a + 1, a + n + 1);
	for (rg int i = (n >> 1) + 2; i <= n; ++i) {
		if (k >= cnt * (a[i] - a[(n >> 1) + 1])) {
			k -= cnt * (a[i] - a[(n >> 1) + 1]);
			++cnt; a[(n >> 1) + 1] = a[i];
		}
		else break;
	}
	fast_IO::write(a[(n >> 1) + 1] + k / cnt);
	return 0;
}
```


---

## 作者：wizard（偷开O2 (赞：1)

一道挺好的二分题。

### 题意

有一长度为 $n$ 的序列 $a$，共 $k$ 次操作，最大化序列中位数

### 分析
因为我们要在 $k$ 次之内完成最大化，所以排序后直接二分。观察数据范围发现，左区间应该定为 $1$，右区间定为 $a_i+k$，也就是 $2e9$。

从 $\frac{n+1}{2}$ 开始扫，如果遇到一个比 $mid$ 小的 $a_i$ 的话，所以 $mid-a_i$ 就是操作次数，累计操作次数。如果最后操作次数没有超过 $k$，那就是最优解了。

由中位数的性质得知，如果要让中位数尽可能得大，排序后位于其后方的数字也要尽可能得大，花费的代价也会更多。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e6+10;
int n,k;
int a[maxn];
bool check(int x){
	int ans=0;
	for(int i=(n+1)/2;i<=n;i++){
		if(a[i]<x){
			ans+=(x-a[i]);
		}else{
			break;
		}
	}
	return ans<=k;
}
signed main(){
	cin >> n >> k;
	for(int i=1;i<=n;i++){
		cin >> a[i];
	}
	sort(a+1,a+n+1);
	int l=1;int r=2e9;
	while(l<r){
        int mid=(1LL+l+r)>>1;
		if(check(mid)){
			l=mid;
		}else{
			r=mid-1;
		}
	}
	cout << r << endl;
	return 0;
} 
```


---

## 作者：Abeeel51 (赞：1)

#### 题目大意

每次取中位数加 $1$ ，然后排序。执行 $k$ 次后，最大的中位数是多少？

#### 解题思路

看到数据 $10^9$ ，第一时间想到二分答案。先将序列排序，因为不保证递增。接着考虑区间：$L = 1$ ， $R = 2 \times 10^9$ ( $a_i$ 的最大值和 $k$ 的最大值)。最后考虑二分函数：按照题面计算，合法就减小区间右端点，不合法就加大区间左端点。按照题意写就行了。

#### AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k;
int a[200005];
bool erfen(int mid){
    long long cnt=0;
    for (int i=(n+1)/2;i<=n;i++){
        if(a[i]<mid){
        	cnt+=mid;
			cnt-=a[i];
        }else{
        	break;
        }
    }
    return cnt<=k;
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
	}
    sort(a+1,a+n+1);
    int left=0;
	int right=2e9;
	int mid;
    while(left<right){
        mid=(1LL+left+right)>>1;
        if(erfen(mid)==1){
        	left=mid;
        }else{
        	right=mid-1;
        }
    }
	printf("%d",right);
    return 0;
}
```


---

## 作者：Fantasy_Segment_Tree (赞：0)

首先一看到这道题就感觉可以二分，然后发现有单调性：满足中位数可以达到 $x$ 也必然满足中位数可以达到 $x - 1$。

首先二分中位数，为了使得中位数达到 $x$，最廉价的方案就是把其中最大的 $\frac{n+1}{2}$ 个数全部变成 $x$，如果超过 $x$ 就不用加了。再与代价限制进行比较，如果未超过代价限制则尝试让中位数更大，否则把中位数变小。

代码如下。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

long long n, a[200005], k;

bool cmp(long long x, long long y) {
	return x > y;
}

bool check(long long x) {
	long long cnt = 0;
	for(long long i = 1; i <= (n + 1) / 2; i++) {
		if(a[i] >= x) continue;
		cnt += x - a[i];
	}
	return cnt <= k;
}

int main() {
	cin >> n >> k;
	for(long long i = 1; i <= n; i++) {
		cin >> a[i];
	}
	sort(a + 1, a + n + 1, cmp);
	long long l = 1, r = 2000000000;
	while(l < r) {
		long long mid = (l + r) >> 1;
		if(check(mid)) l = mid + 1;
		else r = mid;
	}
	cout << r - 1;
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1201C)

一道二分题。

熟悉的 $n \le 2 \times 10^5$，一眼二分。

在 `check(x)` 函数里，我们需要判断的是在 $k$ 次操作以内是否能将 $x$ 变为中位数。显然的，我们只需要往上看，因为只有加法操作，将小的数进行操作一定不利。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
ll n, k, ans;
ll a[200005], tmp[200005];
bool check(ll x) {
    for (int i = 1; i <= n; i++) tmp[i] = a[i];
    ll cnt = 0, mid = n / 2 + 1;
    cnt += x - a[mid];
    a[mid] = x;
    for (int i = mid + 1; i <= n; i++) {
        if (a[i] < a[i - 1]) {
            cnt += a[i - 1] - a[i];
            a[i] = a[i - 1];
        }
    }
    for (int i = 1; i <= n; i++) a[i] = tmp[i];
    if (cnt <= k) return 1;
    return 0;
}
void f(ll l, ll r) {
    while (l <= r) {
        ll mid = (l + r) / 2;
        if (check(mid)) {
            l = mid + 1;
            ans = mid;
        }
        else r = mid - 1;
    }
}
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + 1 + n);
    f(1, 2 * INF);
    cout << ans;
    return 0;
}
```


---

## 作者：cheng_qi (赞：0)

题意要求最大化中位数。根据初中学过的知识，中位数等于数组从小到大排序后的第 $\lfloor\frac{len}{2}\rfloor+1$ 个数，其中 $len$ 为数组长度。也就是说，当我们最大化中位数时，前 $\lfloor\frac{len}{2}\rfloor$ 个数对答案不造成影响。于是得出了一个贪心结论：我们将 $k$ 次加值分给最大的 $\lfloor\frac{len}{2}\rfloor+1$ 个数，使它们的最小值最大，实现也非常简单，~~好像并没有爆 `int` 的情况~~。
```cpp
#include <bits/stdc++.h>

using namespace std;
int n, k, a[200005];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    int mid = a[n / 2 + 1], r = n / 2 + 1, cnt = 1;
    while (1) {
        while (a[r + 1] == mid && r < n) ++r, ++cnt;
        if (k < cnt) {
            cout << mid << endl;
            return 0;
        }
        int ret;
        if (r == n)
            ret = k / cnt;
        else
            ret = min(k / cnt, a[r + 1] - mid);
        mid += ret;
        k -= ret * cnt;
    }
    return 0;
}
```

---

## 作者：_dijkstra_ (赞：0)

本题有两种做法：暴力模拟、二分答案。

## 做法一：暴力模拟

首先，显然要对数组排序。

假设现在 $a$ 是 $1, 3, 5, 6, 8$。

我们每次都对中位数加一：变成 $1, 3, 6, 6, 8$。

这个时候，如果只对中位数加一，会变成 $1, 3, 7, 6, 8$。中位数仍然是 $a_4 = 6$！

所以，我们要对**往后的相同的数**同时加。比如这个例子，我们应该加到 $1, 3, 7, 7, 8$。

以此类推，大家可以模拟一下，非常好理解。

当然，模拟也是要稍微优化一下的，具体就是相同的一起加、一直相同一次加完。

---

这个方法也是完全可以的。

不过代码难度稍大，我们有更加好的方法：二分答案。

## 做法二：二分答案

我们二分答案：中位数最终会变成什么数。

答案显然具有单调性。

你会发现，$\operatorname{check}(x)$ 非常好写：

```cpp
bool chk(int x) //中位数是 x
{
	long long sum = 0;
	for (int i = (n + 1) / 2; i <= n; i++) sum += max(x - a[i], 0);
	return sum <= k;
}
```

然后套个二分就完事了。代码难度明显比做法一低。

## 完整代码（做法二）

~~我不会告诉你，我没打过做法一的代码。~~

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int n, k, a[200005];
bool chk(int x) //中位数是 x
{
	long long sum = 0;
	for (int i = (n + 1) / 2; i <= n; i++) sum += max(x - a[i], 0);
	return sum <= k;
}
int FIND(int l, int r) //TTT【T】FFFF
{
 	while (r - l > 10)
	{
		long long mid = (1ll * l + r) >> 1;
		if (chk(mid)) l = mid;
		else r = mid - 1;
	}
	for (int i = l; i <= r; i++)
		if (!chk(i))
			return i - 1;
	return r;
}
int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	cout << FIND(a[(n + 1) / 2], 2e9);
	return 0;
}
```

希望能帮助到大家！

---

## 作者：BlueSu (赞：0)

### Analysis

观察给出的样例及样例解释，可以发现我们不需要改动全部的数。继续往下思考，我们将该数列排序后，若想让中位数变大，那就需要中位数及从中位数开始往后的数都变大，才能保证现在的中位数不变换在数列中的位置。

想到这里，不少同学已经想到二分了。由于随着中位数的增大，所需要添补的数越来越多，所需要的 $k$ 也就越大。所以，这里的中位数是满足单调性的，可以使用二分答案求解中位数的最大值。

### Solve

现在的思路大体已经有了，接下来的问题就是如何设计 `check(mid)` 函数。

看一眼数据范围，如果暴力统计需要的 $k$ 的大小，那么最大时间就是 $10^9 \log_2 \times 10^5$，是可以过的。但是在统计过程中，如果不采取一定的优化策略，会爆 `int`，所以记得开 `long long`。（这里没有优化）

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LEN 200005
int n,k,a[LEN],ans,pos;
bool check(long long mid);
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    if(n==1){printf("%d",a[1]+k);exit(false);};
    sort(a+1,a+1+n);
    pos=n/2+1;
    long long l=a[pos],r=a[pos]+k;
    while(l<r){
        long long mid=(l+r+1)>>1;
        if(check(mid)){l=mid;}
        else{r=mid-1;}
    }
    printf("%lld",l);
    return 0;
}
bool check(long long mid){
    long long cnt=0;
    for(int i=pos;i<=n;i++){
        cnt+=max((long long)0,mid-a[i]);
    }
    if(cnt>k){return false;}
    return true;
}
```

这里附上一个美观一些的代码，方便查看：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define LEN 200005
int n , k , a[LEN] , ans , pos ;
bool check ( long long mid ) {
    long long cnt = 0 ;
    for ( int i = pos ; i <= n ; i++ ){
        cnt += max ( ( long long ) 0, mid - a[i] ) ;
    }
    if ( cnt > k ) {
        return false ;
    }
    return true ;
}
int main () {
    scanf ( "%d%d" , &n , &k ) ;
    for ( int i = 1 ; i <= n ; i++ ) {
        scanf ( "%d" , &a[i] );
    }
    
    if ( n == 1 ) {
        printf ( "%d" , a[1] + k ) ;
        exit ( false ) ;
    }
    sort ( a + 1 , a + 1 + n ) ;
    pos = n / 2 + 1 ;
    long long l = a[pos] , r = a[pos] + k ;
    while ( l < r ) {
        long long mid = ( l + r + 1 ) >> 1 ;
        if ( check ( mid ) ) {
            l = mid ;
        }
        else {
            r = mid - 1 ;
        }
    }

    printf ( "%lld" , l ) ;
    return 0 ;
}
```

---

## 作者：HoshizoraZ (赞：0)

看到这一题的第一反应是要用堆，但是一看到 $k\le10^9$ 就知道会被 T 飞

观察发现，排序后的这个序列，中位数前面的数都可以删去，因为把 $k$ 次操作分给它们是毫无意义的。

因此去除这些数字之后，原来的中位数就变成了现在的最小的数

所以问题就变成如何操作使得剩余序列中**最小值最大**，可以用**二分答案**，$n$ 的规模 $O(n$ $log$ $n)$ 可以通过。

注意事项：

二分的右端点初始值虽然要开大一些，但是**一定不能开太大**，否则可能会在判断 $mid$ 的时候出现爆 $long$ $long$ 的情况。

代码：

```cpp
#include <algorithm>
#include <cstdio>
typedef long long ll;

ll n, k, a[200010], ans, l, r;

bool check(ll x){
	ll sum = 0;
   
	for(ll i=1; i<=n; i++)
		if(a[i] < x)
			sum += x - a[i];		// r 开太大有可能会让 sum 爆 long long
		else
			break;
            
	return sum <= k;
}

int main(){
	
	scanf("%lld%lld", &n, &k);
	
	for(ll i=1; i<=n; i++)
		scanf("%lld", &a[i]);
	
	std::sort(a + 1, a + n + 1);
	
	n = n / 2 + 1;					// 注意 n 的规模要更新
   
	for(ll i=1; i<=n; i++)
		a[i] = a[n + i - 1];		// 移动下标，相当于删除中位数前面的数字
	
	l = 1, r = 2e9;					// r 不要开太大
	
	while(l < r){					// 二分
		ll mid = (l + r + 1) >> 1;
		if(check(mid)) l = mid;
		else r = mid - 1;
	}
	
	printf("%lld\n", l);

	return 0;
}
```

---

