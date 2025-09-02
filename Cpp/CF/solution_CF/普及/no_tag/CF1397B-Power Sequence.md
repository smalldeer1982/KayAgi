# Power Sequence

## 题目描述

Let's call a list of positive integers $ a_0, a_1, ...,       a_{n-1} $ a power sequence if there is a positive integer $ c $ , so that for every $ 0 \le       i \le n-1 $ then $ a_i = c^i $ .

Given a list of $ n $ positive integers $ a_0, a_1, ...,       a_{n-1} $ , you are allowed to:

- Reorder the list (i.e. pick a permutation $ p $ of $ \{0,1,...,n - 1\} $ and change $ a_i $ to $ a_{p_i} $ ), then
- Do the following operation any number of times: pick an index $ i $ and change $ a_i $ to $ a_i - 1 $ or $ a_i + 1 $ (i.e. increment or decrement $ a_i $ by $ 1 $ ) with a cost of $ 1 $ .

Find the minimum cost to transform $ a_0, a_1, ..., a_{n-1} $ into a power sequence.

## 说明/提示

In the first example, we first reorder $ \{1, 3, 2\} $ into $ \{1, 2, 3\} $ , then increment $ a_2 $ to $ 4 $ with cost $ 1 $ to get a power sequence $ \{1, 2, 4\} $ .

## 样例 #1

### 输入

```
3
1 3 2```

### 输出

```
1```

## 样例 #2

### 输入

```
3
1000000000 1000000000 1000000000```

### 输出

```
1999982505```

# 题解

## 作者：⚡小林子⚡ (赞：9)

[题目传送门](https://www.luogu.com.cn/problem/CF1397B)

------------

### 题目大意

给定一个序列 $a_0,a_1......a_{n-1}$，需要你找出一个正整数 $c$，需满足 $\sum\limits_{i=0}^{n-1}|a_i-c^i|$ 最小，输出$\sum\limits_{i=0}^{n-1}|a_i-c^i|$。

------------

### 思路

最简单的思路就是枚举 $c$，计算每个 $c$ 和 $a$ 序列对应的值。

注意这里 $c$ 不要爆 `long long`，这里我是使用 `pow(LONG_LONG_MAX,1.0/n)` 来判断可取的最大的 $c$ 的。

然后暴力枚举 $c$，计算 $\sum\limits_{i=0}^{n-1}|a_i-c^i|$ 即可。

最后一点：计算前的时候先给 $a$ 排序（因为 $c_i$ 的增长是从小到大的，$a$ 如果也从小到大能保证答案最优）。

看到这里有人会问：会不会有 $c^{n-1}$ 爆了 `long long` 但是答案却是最小的情况？

肯定没有啊。

幂的增长是十分可怕的，假设 $n=50$，$2^{50}$ 并没有爆 `long long`，但是 $3^{50}$ 就爆了，而且 $3^{50}$ 都不知道大到哪去了 （比 $2^{75}$ 都大），所以不用担心爆 `long long` 但是答案最优的问题。

然后代码就好打了：

- 先给 $a$ 排序。

- 暴力枚举 $c$ 并计算对应的值。

Code：

```cpp
#include<bits/stdc++.h>
#define LONG_LONG_MAX 0x7fffffffffffffff
#define int long long
using namespace std;
const int N=1e5+5;
int n,a[N],ans=LONG_LONG_MAX;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)	
		scanf("%lld",&a[i]);
	sort(a+1,a+1+n);
	int t=pow(LONG_LONG_MAX,1.0/n);
	for(int i=1;i<=t;i++){
		int sum=0,tmp=1;
		for(int j=1;j<=n;j++)
			sum+=abs(tmp-a[j]),tmp*=i;
		ans=min(ans,sum);
	}
	printf("%lld",ans);
	return 0;
}
```

看到有些题解说这题 $n$ 很小时会 `TLE`，其实根本不需要考虑这种情况。

**题目里面明确说了** $3\le n\le10^5$，这个代码时间复杂度是 $\Theta(n\times\sqrt[n]{2^{63}-1})$，$n$ 取多少都不会炸的，所以不用考虑那么多，一个暴力枚举即可。

[AC！](https://www.luogu.com.cn/record/37899534)

------------

还是还是千万记住要看数据范围，考场上我就因为没看到 $n$ 的范围在那写优化写了将近 20min，然后才发现暴力可过，浪费了大把时间。

# $\sf{The\, End.}$

---

## 作者：vectorwyx (赞：2)

非常有意思的一道题。

首先，由于“幂序列”是不下降的，那么我们先把序列 $a$ 从小到大排序再考虑加减肯定是最优的。

又因为 $c$ 只需要是正整数，那么我们可以令 $c$ 等于1，这时答案为$\sum_{i=0}^{n-1}abs(a_{i}-1)$，所以我们最多需要$1e5\times 1e9=1e14$次操作就可以把 $a$ 变为幂序列。

接下来考虑最暴力的解法：把 $c$ 从1枚举到1e14，每次枚举求出 $c$ 所对应的幂序列$p_{0},p_{1},…,p_{n}(p_{i}=c^{i})$，再求出答案为$\sum_{i=0}^{n-1}abs(a_{i}-p_{i})$。

但这显然会超时。事实上，我们并不需要从1枚举到1e14，当目前的 $c$ 的 $n$ 次方超过1e14时，答案一定会劣于 $c=1$ 的情况，这时候就不需要再进行枚举了。

因此，我们可以把那些 $n$ 次方的值大于 1e14 的数 $(i^{n}\ge1e14)$ 排除掉，换句话说，我们的 $c$ 只需要从1枚举到$\sqrt[n]{1e14}$（下取整），总时间复杂度为$O(n\times\sqrt[n]{1e14})$，$3\le n\le 1e5$，稳过。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int maxn=1e5+5;
const ll INF=1e15;//这里把上限由1e14调为了1e15，可以省去一些细节，但不会影响正确性 
int a[maxn];
ll ans=INF,power[maxn],sum;

int main(){
	int n=read();
	fo(i,1,n) a[i]=read();
	sort(a+1,a+1+n);
	int R=floor(pow(INF,1.0/n));
	fo(i,1,R){ 
		sum=0;
		power[0]=1;
		fo(j,1,n) power[j]=power[j-1]*i,sum+=abs(a[j]-power[j-1]);
		ans=min(ans,sum);
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：寒鸽儿 (赞：1)

我们观察一下数据 , $n \leqslant 10^5$ , 即便是 $2^{10^5}$ 这个数据也是大到无法承受的 , 对 $a_i \leqslant 10^9$ 而言 $c = 0$ 或者 $c = 1$ 都是更加优的选择。也就是 , 对于规模大的 $n$ , $c = 0/1$ 。  
对于规模较小的 $n$ , 暴力枚举 $c$ 就可以保证复杂度。  
因为 $n \leqslant 10^5$ , $a_i \leqslant 10^9$ , 所以选择 $c = 0$ 的方案答案不会超过 $10^{14}$ , 我们设置 $10^{14}$ 为上限 , 如果 $c^i$ 超过这个上限就直接结束枚举 , 这样就能保证时间和正确性。
```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define repp(i,a,b) for(int i=(a);i<(b);++i)
#define perr(i,a,b) for(int i=(b);i>(a);--i)

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> VI;
typedef vector<long long> VL;
typedef vector<double> VD;
typedef vector<int>::iterator itra;

const int maxn = 123456;
const ll limit = 100000000000005ll;
ll a[maxn];

int main() {
//	ios_base::sync_with_stdio(false);
//	cin.tie(NULL);
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%lld", a + i);
    sort(a + 1, a + n + 1);
    ll ans = 0, t2 = 0;
    for(int i = 1; i <= n; ++i) ans += abs(a[i] - 1);
    for(int i = 1; i <= n; ++i) t2 += a[i];
    ans = min(ans, t2);
    int bs = 2;
    bool flg = true;
    int cnt = 1;
    while(flg) {
        ll tmp = 1, tans = 0;
        bool f2 = true;
        for(int i = 1; i <= n; ++i) {
            if(tmp > limit) {
                flg = false;
                break;
            }
            if(a[i] > tmp) f2 = false;
            tans += abs(a[i] - tmp);
            tmp *= bs;
        }
        if(flg) ans = min(ans, tans);
        if(f2) flg = false;
        ++bs;
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：jun头吉吉 (赞：1)

## 题意
如果我们把一个正整数序列$a_0,a_1,\ldots,a_{n-1}$叫做幂次序列，那么存在一个整数$c$,使每个$0\leq i\le n-1$，$a_i=c^i$。

给出$n$个正整数$a_0,a_1,\ldots,a_{n-1}$的序列，您可以：

重新排序列表（即选择$p_i\in \{0,1,\ldots,n-1\}$，并将$a_i$更改为$a_{p_i}$），然后
执行以下操作任意次数：选择一个下标$i$并将$a_i$更改为$a_i−1$或$a_i+1$（即$a_i$递增或递减1），成本为$1$。

求出将$a_0,a_1,\ldots,a_{n-1}$转换为幂序列的最小成本。


简单来说，就是把$a_0,a_1,\ldots,a_{n-1}$重排成$a^\prime_0,a^\prime_1,\ldots,a^\prime_{n-1}$，求$min_{c=1}(\sum_{i=0}^{n-1}|a^\prime_i-c^i|)$

## 题解

题目看上去很长但其实不难~~毕竟只有B题~~

首先如果我们有$a_x,a_y,c^z,c^{z+1}$~~(cz?)~~，那我们应该怎么分配？

直观上看，我们肯定是**大的减大的，小的减小的**，这样肯定是最划算的（别问我证明~~画个图试一下就知道了~~）

那么$a^\prime_0,a^\prime_1,\ldots,a^\prime_{n-1}$实际上就是对$a_0,a_1,\ldots,a_{n-1}$进行从大到小的排序。然后再考虑$c$如何求

首先暴力谁都会写

```cpp
for(int i=1;;i++){
		long long tmp=0,now=1;
		for(int j=1;j<=n;j++)
			tmp+=abs(a[j]-now),now*=i;
		ans=min(ans,tmp);
	}
```
**没有限制条件，那还不死循**

但是我们可以发现，当$c=1$时，花费为$\sum_{i=1}^{n-1}|a_i-1|$，那么当最后一个数字过大时，甚至远大于$a_n$那么其花费比$c=1$还多得多得多，肯定是不能选的，于是我们得出了改进版的代码（其实还可以防止精度爆炸）

用c++内置的`log10`可以很方便地判断大小
```cpp
for(int i=1;;i++){
		if(log10(i)*(n-1)>=15)break;
		long long tmp=0,now=1;
		for(int j=1;j<=n;j++)
			tmp+=abs(a[j]-now),now*=i;
		ans=min(ans,tmp);
	}
```
但此时在$n$很小的时候还是会T，比如：
```
1
1
```
那`i`要枚举到猴年马月。

**~~下面的操作是此题的关键~~**

由于是B题，在根据做出来的的人数，我们可以得出一个结论：

$\sum_{i=0}^{n-1}|a^\prime_i-c^i|$是一个单峰函数！！！

~~这充分体现了OIer大胆猜测，不去求证的精神（~~

单峰函数我们可以三分，但没必要。我们只需要在加一句话：

```
		if(tmp>ans)break;
```

然后就做出来啦

## 代码
```cpp
#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
namespace in{
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){
	    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
	}
	template <typename T>inline void read(T& t){
	    t=0;int f=0;char ch=getc();
	    while (!isdigit(ch)){
	        if(ch=='-')f = 1;
	        ch=getc();
	    }
	    while(isdigit(ch)){
   	    	t=t*10+ch-48;
   	    	ch = getc();
   		}
		if(f)t=-t;
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args){
	    read(t);read(args...);
	}
}
namespace out{
	char buffer[1<<21];
	int p1=-1;
	const int p2 = (1<<21)-1;
	inline void flush() {
		fwrite(buffer,1,p1+1,stdout),
		p1=-1;
	}
	inline void putc(const char &x) {
		if(p1==p2)flush();
		buffer[++p1]=x;
	}
	template <typename T>void write(T x) {
		static char buf[30];
		static int len=-1;
		if(x>=0){
			do{
    			buf[++len]=x%10+48,x/=10;
    		}while (x);
		}else{
    		putc('-');
			do {
    			buf[++len]=-(x%10)+48,x/=10;
			}while(x);
		}
		while (len>=0)
			putc(buf[len]),--len;
	}
}
using namespace std;
int n,a[100000+10];
signed main(){
	//freopen("111","r",stdin);
	in::read(n);
	for(int i=1;i<=n;i++)in::read(a[i]);
	sort(a+1,a+1+n);long long ans=0x3f3f3f3f3f3f3f3f;
	for(int i=1;;i++){
		if(log10(i)*(n-1)>=15)break;
		long long tmp=0,now=1;
		for(int j=1;j<=n;j++)
			tmp+=abs(a[j]-now),now*=i;
		ans=min(ans,tmp);
		if(tmp>ans)break;
	}
	out::write(ans);
	out::flush();
	return 0;
}
```

---

## 作者：引领天下 (赞：0)

由于是乘方操作，所以 $a_i\le 10^9$ 实际上是个挺友善的范围。

采用贪心的思想，将原数组升序排序后的答案一定比乱序更优。

考虑枚举 $c$，暴力找最优解。时间复杂度 $O(cn)$。

当 $n,c$ 很大的时候，$c^n$ 必然很大，于是为了让答案更小，$c$ 必须很小。于是这种情况下的复杂度完全可以承受。

同理当 $n$ 很小的时候，尽管 $c^n$ 也比较小，但是每次统计的复杂度很小。

于是这个复杂度是完全可以跑过去的。

那么暴力的边界是什么呢？

如果当前的 $c^i(i\le n)$ 已经超过了我们设定的一个极大值（超过这个极大值之后就不可能比当前答案更优了），我们就直接退出。

**注意！坑点来了！不能用快速幂，中间会爆！这个可怜的孩子就是这么吃了一发罚时的！！！**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long ans=1ll<<62,a[100005],k;
int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);
    for(int c=1;k<=(1ll<<50);c++){//枚举c
        k=1;//暴力算乘方
        long long now=0;
        for(int i=1;i<=n;i++){
            now+=abs(k-a[i]),k*=c;
            if(k>(1ll<<50))break;//超过极大值，直接退出
        }
        ans=min(ans,now);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：smallfang (赞：0)

先排个序

循环枚举 $c$
然后如果 $c ^ {(n-1)} > Maxnum $ 退出即可。因为再往上取一定会比现在更大。不会再次缩小。

为了防止越界、我们在每次相乘后、判断是否合理、注意、途中的判断需要更加谨慎需要保证更大。所以推荐判断 $fw > Maxnum * c ^ 2$


找到所有枚举的最小值。

Code:
```cpp
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 1e5 + 5;
const long long INF = 4e16;

ll h[N];

int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++ )
    {
        cin >> h[i];
    }
    sort(h + 1, h + 1 + n);
    long long res = INF;
    for (int c = 0; c <= h[n]; c ++ )
    {
    	bool flag = false;
        long long cnt = 0, ft = 0;
        for (int i = 1; i <= n; i ++ )
        {
        	if (i == 1)
        	{
        		ft = min(c, 1);
        	}
        	else
        	{
        		ft *= c;
        	}
    		if (c != 0 && i != 0 && ft > h[n] * c * c)
    		{	
    			flag = true;
    			break;
    		}
            cnt += abs(h[i] - ft);
        }
        if (flag)
        	break;
        res = min(res, cnt);
    	if (c != 0 && ft > h[n])
    		break;
    }
    cout << res;
}
```

---

## 作者：KellyFrog (赞：0)

当 $n\ge 3$ 的时候，我们发现 $c^{n-1}$ 的增长是极快的，我们又知道 $c^{n-1}$ 的上界约为 $10^{10}$（事实上我取的 $10^{12}$），$c$ 的范围应该很小，直接判断 $c^{n-1}$ 在不在 $[1,10^{12}]$ 中就行了。

复杂度大概是 $O(n\cdot D^{\frac{1}{n}})$，简单估算之后发现在 $n\ge 3$ 的时候非常小，可以通过此题。

所以加上 $n=1$ 或 $n=2$ 的特判就行了。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 5;

#define int long long

int a[MAXN], n;

int poww(int a,int b) {
	int ans = 1, base = a;
	while(b) {
		if(b & 1) {
			ans *= base;
		}
		base *= base;
		b >>= 1;
	}
	return ans;
}

signed main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	sort(a + 1, a + 1 + n);
	if(n >= 3) {
		int ans = 1e18;

		for(int i = 1; poww(i, n - 1) <= 1e12; i++) {
			int mul = 1;
			int cur = 0;
			for(int j = 1; j <= n; j++) {
				if(mul > 1e12) {
					cur = 1e18;
					break;
				}
				cur += mul > a[j] ? mul - a[j] : a[j] - mul;
				mul = mul * i;
			}

			ans = min(ans, cur);
		}
		cout << ans << endl;
	} else {
		cout << a[1] - 1 << endl;
	}
}
```

---

