# [USACO22JAN] Searching for Soulmates S

## 题目描述

Farmer John 的每头奶牛都想找到她们的灵魂伴侣——另一头具有相似特点的奶牛，与她们最大程度地相容。每头奶牛的性格由一个整数 $p_i$（$1 \leq p_i \leq 10^{18}$）描述。两头性格相同的奶牛就是灵魂伴侣。奶牛可以通过「改变操作」，对她的性格乘以 $2$，除以 $2$（当 $p_i$ 是偶数时），或者加上 $1$。

Farmer John 最初以任意方式配对了他的奶牛。他很好奇为使每对奶牛成为灵魂伴侣需要进行多少次改变操作。对于每对奶牛，求配对中的第一头奶牛所必须进行的最小改变操作次数，从而可以与第二头奶牛成为灵魂伴侣。

## 说明/提示

【样例解释】

对于第一个子测试用例，一个最优的操作序列为 $31 \implies 32 \implies 16 \implies 8 \implies 9 \implies 10 \implies 11 \implies 12 \implies 13$。

对于第二个子测试用例，一个最优的操作序列为 $12 \implies 6 \implies 7 \implies 8$.

【数据范围】

- 测试点 1-4 满足 $p_i \le 10^5$。
- 测试点 5-12 没有额外限制。



## 样例 #1

### 输入

```
6
31 13
12 8
25 6
10 24
1 1
997 120```

### 输出

```
8
3
8
3
0
20```

# 题解

## 作者：MY（一名蒟蒻） (赞：19)

upd ：原来的代码被[这位大佬](https://www.luogu.com.cn/user/685127)在[这个帖子](https://www.luogu.com.cn/discuss/437045)里 hack 了。思路没有问题，在实现的时候有一个细节没有处理好，修改的地方在代码注释中给出。

[P8093 [USACO22JAN] Searching for Soulmates S](https://www.luogu.com.cn/problem/P8093)

## Part 0. 闲话

赛时：啊这啥玩意啊数据范围这么大，爆搜又炸了。

躺平。

赛后补题看了网上的题解，自我感觉有些地方不是特别清晰。于是就有了这篇题解。

## Part 1. 从 SPFA 的爆搜开始

~~关于搜索，它死了。~~

以下称乘 $2$、除以 $2$、加上 $1$ 分别为 $1$、$2$、$3$ 操作。

除了极大的数据范围外，让爆搜挂掉的还有搜索过程中不断交替的 $1$ $2$ 操作。

考虑什么时候两种操作不断交替进行是不优的。显然当没有 $3$ 操作在中间时，重复操作是在浪费时间。  
那么有 $3$ 操作在中间的情况呢？手玩一下就能发现，这种情况也是不优的。

也就是说，$1$ $2$ 两种操作必然分段进行。即有一个分界点，使得一边没有 $1$ 操作，另一边没有 $2$ 操作。

## Part 2. 分析样例

那么哪种操作在前半段呢？我们分两种情况讨论:  
设两头奶牛的性格值分别为 $P_A$ $P_B$ ，  
1. $P_A > P_B$ 。样例中并没有先进行 $1$ 操作。分析此时先进行 $1$ 操作的意义，我们希望通过进行 $1$ 操作，使得后来进行 $2$ 操作时，可以更快向 $P_B$ 靠近。但这一过程中进行的 $3$ 操作总数却比不先进行 $1$ 操作更多，所以无需先进行 $1$ 操作。
2. $P_A < P_B$ 。分析样例也可得知显然先进行 $1$ 操作然后进行 $2$ 操作无意义，我们也可以理解为先进行 $0$ 次 $2$ 操作。

至于等于的情况，特判即可。

综上我们发现，前半段是 $2$ 操作，后半段是 $1$ 操作。

## Part 3. 算法实现

因为操作有奇偶限制。根据以上分析可知，前半部分当 $P_A$ 是奇数时，执行 $3$ 操作，否则执行 $2$ 操作。不妨设分界点为最后一次执行 $2$ 操作。

前半部分结束后的 $P_A$ 仅通过 $1$ $3$ 操作变成 $P_B$ 的代价是：

$g(a,b)= \begin{cases}+\infty&(a>b)\\ b-a&(2a>b) \\ g(a,b-1)+1&(b\bmod 2 = 1) \\ g(a,b/2)+1&(b\bmod 2 = 0 
\ \text{and}\ 2a\leq b)\end{cases}$

发现这个函数可以在 $O(\log10^{18})$ 时间内求解，前半段的操作也是同样的复杂度。注意到何时结束前半部分是任意的，那么我们对于每一个可能的结束点求 $g$ 函数，答案取最小值。总复杂度 $O(\log^210^{18})$ ，可以接受。

## Part 4. Talk is cheap, show me the code.

~~其实不放出来也可以吧。~~

因为实际上就是翻译了一遍思路，所以建议各位自己写，实在写不出来可以参考以下代码。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>

using namespace std;

typedef long long ll;

ll a,b;

ll dfs(ll x,ll y)
{
	if(x > y) return 1e18;
	if(x << 1 > y) return y-x;
	return y&1? dfs(x,y-1)+1:dfs(x,y>>1)+1;
}

inline ll solve()
{
	if(a == b) return 0;
	ll ans=1e12,cnt=0;
	do //原来写的是 while ，被 hack 了
	{
		ll res=dfs(a,b);
		ans=min(ans,res+cnt);
		if(a&1) a++;
		else a>>=1;
		cnt++;
	} while(a > 1);
	return ans;
}

int main()
{
//  freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	int n;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%lld%lld",&a,&b);
		printf("%lld\n",solve());
	}
//  fclose(stdin); fclose(stdout);
    return 0;
}
```

***Thanks for your reading!***

~~所以金组 B 题啥时候有带代码的题解啊，不懂怎么实现。~~

---

## 作者：YCSluogu (赞：17)

这里提供一个新奇的思路。

大家考虑一个弱化情况：如果只允许除以 $2$ 和加一并且 $a > b$。会怎么做？

这就非常容易考虑。让 $a$ 不断加 $1$ 与除以 $2$ 直到 $b > a$，这样 $a$ 便可以一路加到 $b$ 去。

大家推样例是否发现这样一个情况：$a$ 会一开始不断除以 $2$ 和加 $1$，一旦开始乘 $2$ 后就不会再除以 $2$。
原因其实很好理解，若除以 $2$ 后乘 $2$ 对答案不会更优。

啧……是不是就和我们弱化情况开始有点类似了呢？也就是说，我们需要找一个数 $t$，作为我们的中转值。
负责让我们完成弱化情况。那么这个中转值，要满足什么条件？

后面只允许乘 $2$ 和加 $1$。所以，$t$ 的二进制一定是 $b$ 二进制表示下的一个前缀。

所以，我们只需要枚举 $b$ 二进制前缀表示的数字，即 $t$。然后按照弱化情况求出 $a$ 变为 $t$ 所花的次数。
这都求出来了，还想不到后面怎么写？不断将 $a$ 乘 $2$ 和加 $1$，使其与 $b$ 的前缀保证相同即可。

code
``` cpp
#include <bits/stdc++.h>

using namespace std;

long long n;

long long len(long long num) {
  for (long long i = 63; i >= 0; i--) {
    if ((num >> i) & 1) {
      return i + 1;
    }
  }
  return 0;
}

long long get(long long num, long long i, long long len) {
  return num >> (len - i);
}

void solve() {
  long long a, b, c, cnt = 0, ans = INT_MAX;
  cin >> a >> b;
  if (a == b) {
    cout << 0 << endl;
    return;
  }
  c = len(b);
  long long save = a;
  for (long long i = 1; i <= c; i++, ans = min(ans, cnt), a = save) {
    cnt = 0;
    long long nowb = get(b, i, c);
    while (a != nowb) {
      if (a > nowb) {
        if (a & 1) a++;
        else a /= 2;
        cnt++;
      } else {
        cnt += nowb - a;
        a = nowb;
      }
    }
    for (long long j = i + 1; j <= c; j++) {
      nowb = get(b, j, c);
      a <<= 1;
      cnt++;
      if (nowb != a) a++, cnt++;
    }
  }
  cout << ans << endl;
}

int main() {
  cin >> n;
  while (n--) {
    solve();
  }
  return 0;
}
```

---

## 作者：sync_with_stdio (赞：8)

题意：给定两个整数 $a,b$，可以让 $a$ 乘 $2$、 除 $2$、加 $1$，使得他以最小的步骤变成 $b$。

首先，我们要明确一点，必须 $a \leq b$ 时， $a$ 才有可能变成 $b$。

所以当 $a>b$ 时：

- 如果 $a\equiv1\pmod{2}$， 令 $a+1$。

- 否则令 $a \div 2$。

但如果 $b \geq a \times 2$，也是要将 $b$ 操作至 $\leq a$ 。但是注意一下，因为是反过来操作，所以 $+1$ 操作会变为 $-1$ 操作， $\div 2$ 的操作会变为 $\times 2$ 操作， $\times 2$ 的操作会变为 $\div 2$ 操作。

为什么呢？因为一旦一个数能够通过 $\times 2$ 和 $\times 2+1$ 达到 $b$ （相当于在该数的二进制串的末尾 $+1$ 或 $+0$），则它一定是 $b$ 的二进制前缀，而 $b$ 的二进制前缀只有 $\text{log\ b}$ 个，所以可以放心枚举。

- 如果 $b\equiv1\pmod{2}$， 令 $b-1$。

- 否则令 $b \div 2$。

一旦 $a$ 和 $b$ 进入范围，最后不断尝试将 $a$ 按刚才的方式变小， $b$ 以刚才的方式变小，在不断计算取最小值就可以了。

最后放一下代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
    int T;
    scanf("%lld",&T);
    while(T--)
    {
        int a,b;
        scanf("%lld%lld",&a,&b);
        int cnt=0;
        while(a>b)           //让a变小
        {
            cnt++;
            if(a%2==1)
                a++;
            else
                a/=2;
        }
        while(b>=a*2)       //让b变小
        {
            if(b%2==1)
                b--;
            else
                b/=2;
            cnt++;
        }
        if(a==b)                //如果已经一样了，输出就行
        {
            printf("%lld\n",cnt);
            continue;
        }
        int aa=a,bb=b;                      //备份
        int minn=0x3f3f3f3f,bs=0;           // 最小值记录，临时计步器
        while(aa>=1 && bb>=1 && aa<=bb)
        {
            minn=min(minn,cnt+bs+(bb-aa));          //按刚才说的同时变小，计算原步数+新步数+相邻两数应走步数
            if(aa%2==1)
                aa++,bs++;
            aa/=2;
            bs++;
            if(bb%2==1)
                bb--,bs++;
            bb/=2;
            bs++;
        }
        printf("%lld\n",minn);
    }
    return 0;
}

```

感谢阅读。

---

## 作者：jimmy2021 (赞：6)

$\text{update on 2022/5/18}$：原来的代码被[这位大佬](https://www.luogu.com.cn/user/685127)在[这个帖子](https://www.luogu.com.cn/discuss/437045)里hack了。思路没有问题，在实现的时候有一个特殊情况没有处理好，修改的地方在代码注释中给出。

---

首先，乘操作和除操作肯定不是交替出现的，只能是有一段分界点。

> 证（fei）明（hua）：
> 
> 如果交替出现，那么交替出现的乘和除操作就会抵消。

那么知道肯定有一个分界点，下一个应该研究的问题就是分界点前后分别是哪些操作？

> 分情况讨论：
> 
> - 如果 $a > b$：
> 
> 那么先进行乘操作反而离 $b$ 更远，只能再除一遍，就会出现乘除交替情况，抵消，不是最优。
> 
> 所以只能先进行除操作。
> 
> - 如果 $a < b$：
> 
> 第一步可以选择加或乘操作。当然，也可以看成用了 $0$ 次除操作后进行乘操作。

综上所述，可知分界点前后是先除后乘。

除法操作很简单，直接加法调整，除法缩小即可。那么只用乘操作和加操作至少用多少步能使得 $a$ 和 $b$ 相等呢？

> 分情况讨论：
> 
> 假设使得 $a$ 和 $b$ 相等的最小操作次数为 $f(a, b)$ ，那么 $f(a, b) = $
> 
> - 如果 $a > b$：
> 
> 无穷大次操作
> 
> > 证（fei）明（hua）：
> > 
> > 因为乘法和加法只能使得 $a$ 变大，不能使得 $a$ 变小，所以永远不可能达成目标。
> 
> - 如果 $a * 2 > b$：
> 
>  $b - a$ 次操作
> 
> > 证明：
> > 
> > 如果先将 $a$ 乘一下，那么就转换为第 $1$ 种情况，无解。所以只能加。
> 
> - 如果 $b\ \text{mod}\ 2 = 1$：
> 
>  $f(a, b - 1) + 1$ 次操作
> 
> > 解释：
> > 
> > 先将 $a$ 变为 $b - 1$，再加一次。
> 
> - 如果 $b\ \text{mod}\ 2 = 0$ 且 $a \leq \dfrac{b}{2}$
> 
>  $f(a, \dfrac{b}{2}) + 1$ 次操作
> 
> > 解释：
> > 
> > 先将 $a$ 变为 $\dfrac{b}{2}$，再乘一次。
> 
> 其实上面的第二个条件“$a \leq \dfrac{b}{2}$”是判断有解的情况

其他详情见代码。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <limits.h>
#include <cstring>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
const int INF = 0x3f3f3f3f, INF_BIT = 0x3f;

const int N = 1e5 + 10;

LL t;
LL a, b;

LL f(LL a, LL b){
    if(a > b) return 1e18;
    if(a * 2 > b) return b - a;
    if(b % 2 == 1) return f(a, b - 1) + 1;
    if(b % 2 == 0 && a <= b / 2) return f(a, b / 2) + 1;
}
LL solve(LL a, LL b){
    LL cnt1 = 0;  //光由除操作和加操作的最小操作次数
    if(a == b) return 0;
    LL ret = 1e18;
    //此处改成do...while循环了，直接while循环会被卡
    do{
        //可以随时设当前为分界点
        LL cnt2 = f(a, b);
        ret = min(ret, cnt1 + cnt2);
        
        if(a % 2 == 1) a++;
        else a /= 2;
        cnt1++;
    }while(a > 1);
    return ret;
}

int main(){
    scanf("%lld", &t);
    while(t--){
        scanf("%lld%lld", &a, &b);
        
        printf("%lld\n", solve(a, b));
    }
    return 0;
}
```

---

## 作者：Oborozuki (赞：4)

# 题意

将数 $a$ 通过 **乘 $2$**、**除以 $2$** 和 **加上 $1$** 操作变为 $b$，求最少的操作次数。

注：数 $a$ 进行乘法、除法和加法操作，相当于数 $b$ 可以进行乘法、除法和减法。

# 思路

可以分下列情况讨论：

1. $a = b$
2. $a \lt b$
3. $a \gt b$

首先，第一种情况，即 $a = b$，显然操作次数为 $0$。

不难发现，将较大的数变为较小的数只能通过除法，因此，将较小的数变为较大的数比较容易，我们先讨论 $a < b$ 的情况。

当 $b >= 2a$ 时，为了减少操作次数，$a$ 最后通过乘以 $k$ 个 $2$ 可以得到 $b$。所以我们可以反过来对 $b$ 先进行操作，使 $a \le b \lt 2a $ （记作 $b_{1}$ ）。此时 $\lfloor log_{2}{a} \rfloor = \lfloor log_{2}{b_{1}} \rfloor$。

此时，要将 $a$ 变换为 $b_{1}$ ，可以直接加上 $b_{1}-a$，但如果先除以 $2k$ 加上一定值再乘 $2k$，所加的数也会被扩大，操作次数可能更少。

接下来，我们同时考虑 $a$ 和 $b_{1}$，注意由于是 $a$ 变到 $b_{1}$，$a/2$ 应向上取整（即 $a$ 时奇数时为 $(a+1)/2$），$b_{1}/2$应向下取整（认为是 $a$ 在此处加 $1$）。

![例](https://cdn.luogu.com.cn/upload/image_hosting/m4gv43ek.png)

如上图，我们可以发现，由 $a$ 到 $b_{1}$ 的总花费（图右侧）总是先减小再增大，我们一旦发现总花费大于上一次的总花费就退出循环。

**代码如下：**
```cpp
long long ss=b-a, cnt=0; // ss即为由 a 到 b1 的总花费
while(a){
	int si=0;
	if(a%2) a++, cnt++;
	if(b%2) cnt++;
	cnt+=2;
	a/=2; b/=2;
	si+=b-a+cnt;
	if(si>=ss||b<a) break;
	else if(b==a){
		ss=si;
		break;
	}else ss=si;
}
```

最后我们来看 $a \gt b$ 时的情况。如前文所说，将较大的数变为较小的数只能通过除法。我们先将 $a$ 除以 $2$ 直到 $\frac{b}{2} \lt a \lt b$。此时我们发现问题转化为了情况二（即 $a \lt b$），套用上述算法即可得到答案。

# 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t; long long p1,p2; // p1 p2 即为题解中的 a b

long long solve1(long long a, long long b){ // a<b
	long long ans=0;
	while(b>=a*2){
		if(b%2) ans++;
		ans++; 
		b/=2;
	}
	long long ss=b-a, cnt=0; // ss即为由 a 到 b1 的总花费
	while(a){
		int si=0;
		if(a%2) a++, cnt++;
		if(b%2) cnt++;
		cnt+=2;
		a/=2; b/=2;
		si+=b-a+cnt;
		if(si>=ss||b<a) break;
		else if(b==a){
			ss=si;
			break;
		}else ss=si;
	}
	ans+=ss;
	return ans;
}

void solve(){
	long long ans=0;
	if(p1==p2){
	    printf("0\n");
	    return;
	}
	if(p1<p2) printf("%lld\n", solve1(p1,p2));
	else{
		while(p1>=p2){
			if(p1%2) p1++, ans++;
			ans++;
			p1/=2;
		}
		printf("%lld\n", ans+solve1(p1,p2));
	}
}

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%lld%lld", &p1, &p2);
		solve();
	}
	return 0;
}
```

---

## 作者：桃雨凪丝 (赞：3)

### 这个题解和大部分题解区的题目思路不同。


------------
要把数 A 变成数 B ，可以分下来。

对于数 A ，对其 $a{\div}2$ 或 $a+1$ ；

对于数 A ，对其 $a{\div}2$ 或 $a-1$ ；

易证每个数都可以变成 1 。


------------
用数组存下每一次变换，用每一个 A 的变换序列去找最靠近的 B 的变换序列。

总步数 $= i+id-2+rb[id]-ra[i]$ 。

**这里可以用二分优化**


------------


贴贴
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define inf 1e9+10
#define lim 100010
ll ra[lim],rb[lim],xba,xbb;
void deala(ll a){
	ra[1]=a;
	xba=2;
	while(a>1){
		if(a%2==0) a/=2;
		else a+=1;
		ra[xba]=a;
		xba++;
	}
	xba--;
}
void dealb(ll b){
	rb[1]=b;
	xbb=2;
	while(b>1){
		if(b%2==0) b/=2;
		else b-=1;
		rb[xbb]=b;
		xbb++;
	}
	xbb--;
}
int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);
	int t;
	cin>>t;
	while(t--){
		ll a,b;
		cin>>a>>b;
		memset(ra,0,sizeof(ra));
		memset(rb,0,sizeof(rb));
		deala(a);dealb(b);
		ll ans=inf;
		for(ll i=1;i<=xba;i++){
			ll l=1,r=xbb,x=ra[i];
			while(l<r){
				ll mid=(l+r)>>1;
				if(rb[mid]<=x) r=mid-1;else l=mid+1;
			}
			if(x>rb[l]) l--;
			ll id=l;
			if(rb[id]>=ra[i])
			ans=min(ans,i+id-2+rb[id]-ra[i]);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：wwz1428572008 (赞：1)

### 思路
题目大意：有 $n$ 次查询，每次给定整数 $x$ 和 $y$。有三种操作，分别是乘 $2$（操作一），除以 $2$（当原数是偶数时）（操作二），以及加 $1$（操作三）。查询从 $x$ 最少需要几次操作才能变成 $y$。

可以发现，最优的操作序列应当是先通过操作二和操作三使 $x$ 小于在二进制下$y$ 的前 $k$ 位（$1\leq k\leq \lfloor\log_2y\rfloor+1$）。然后，可将 $x$ 通过操作三变成二进制下 $y$ 的前 $k$ 位。最后，用操作一和操作三把 $x$ 变成 $y$。具体细节比较多，可以参考我的代码。
## 代码
```cpp
#include<iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	while(n--)
	{
		long long x,y;
		cin>>x>>y;
		if(x==y)
		{
			cout<<0<<endl;
			continue;
		}
		long long ans=100000000,res;
		for(long long k=1;(1LL<<(k-1))<=y;k++)
		{
			res=0;
			long long a=x,b=y;
			while(b>=(1LL<<k))
				b/=2;
			while(a>b)
			{
				if(a%2)
					a++,res++;
				a/=2;
				res++;
			}
			res+=b-a;
			int cnt=0;
			while((b<<(cnt+1))<=y)
				cnt++;
			for(int i=0;i<cnt;i++)
				res+=((y>>i)&1)+1;
			ans=min(ans,res);
		}
		cout<<ans<<endl;
	}
	return 0;
}

```


---

