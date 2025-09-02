# [SDCPC 2023] Math Problem

## 题目描述

给定两个正整数 $n$ 和 $k$，您可以进行以下两种操作任意次（包括零次）：

- 选择一个整数 $x$ 满足 $0 \leq x < k$，将 $n$ 变为 $k\cdot n+x$。该操作每次花费 $a$ 枚金币。每次选择的整数 $x$ 可以不同。
- 将 $n$ 变为 $\lfloor \frac{n}{k} \rfloor$。该操作每次花费 $b$ 枚金币。其中 $\lfloor \frac{n}{k} \rfloor$ 表示小于等于 $\frac{n}{k}$ 的最大整数。

给定正整数 $m$，求将 $n$ 变为 $m$ 的倍数最少需要花费几枚金币。请注意：$0$ 是任何正整数的倍数。

## 样例 #1

### 输入

```
4
101 4 207 3 5
8 3 16 100 1
114 514 19 19 810
1 1 3 1 1```

### 输出

```
11
2
0
-1```

# 题解

## 作者：WhitD (赞：2)

## 题目大意
给定两个正整数 $n$ 和 $k$，您可以进行以下两种操作任意次（包括零次）：

- 选择一个整数 $x$ 满足 $0 \leq x < k$，将 $n$ 变为 $k\times n+x$。该操作每次花费 $a$ 枚金币，每次选择的整数 $x$ 可以不同。
- 将 $n$ 变为 $\lfloor \frac{n}{k} \rfloor$。该操作每次花费 $b$ 枚金币。其中 $\lfloor \frac{n}{k} \rfloor$ 表示小于等于 $\frac{n}{k}$ 的最大整数。

给定正整数 $m$，求将 $n$ 变为 $m$ 的倍数最少需要花费几枚金币。
## 思路
我们发现，先乘再除对结果是没有影响的（因为操作一加的值小于 $k$，操作二的除法向下取整就把多加的数也除掉了），因此一定是先除再乘。

我们假定当前的数为 $n$，将它进行一次操作一：如果乘完了不加数，它会变成 $n\times k$；如果乘完后加数，最多可以加 $x(x<k)$，也就是 $k-1$，它会变成$n\times k+k-1$。这说明 $n$ 进行完操作一后可以变到的范围是 $[n\times k,n\times k+k-1]$。

于是我们可以先枚举出进行操作二的次数（这个过程是 $\log$ 的），同时进行重复进行操作一直到 $n$ 成为 $m$ 的倍数（根据区间端点来判断是否在区间内），然后计算总代价，全局取 $\min$ 就可以了。

注意特判 $k=1$ 是无解的。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
int main()
{
	cin>>T;
	while(T--)
	{
		ll n,k,m,a,b,ans=114514191981011451;
		cin>>n>>k>>m>>a>>b;
		if(n%m==0)
		{
			cout<<0<<endl;
			continue;
		}
		if(k==1)
		{
			cout<<-1<<endl;
			continue;
		}
		for(ll i=0,d=0;;i++,n/=k,d=i*b)
		{
			if(!n)
			{
				ans=min(ans,b*i);
				break;
			}
			__int128 l=n,r=n;
			while(l%m&&(r/m==l/m))
			{
				r=r*k+k-1;
				l*=k;
				d+=a;
			}
			ans=min(ans,d);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：One_JuRuo (赞：2)

## 思路

首先发现应该优先除，理由很简单，如果先乘以 $k$ 再加上一个不超过 $k$ 的值，那么除以 $k$ 后，就除回去了，没有发生任何变化。

所以我们可以先枚举除以多少次 $k$，得到除以这么多次 $k$ 后的 $n$。我们再进行若干次乘法，计算 $n$ 的取值范围 $[l,r]$，那么只要这个区间包含了 $m$ 的倍数就行。

易知对 $n$ 进行 $x$ 次乘法操作后的取值区间是 $[k^x\times n,k^{x+1}\times n-1]$。

所以我们可以只记录区间左端点 $l$ 和区间长度 $len$，这是为了方便后面的取模操作判断是否包含 $m$ 的倍数。

因为只要包含倍数，所以左端点 $l$ 可以模 $m$，这样 $l+len\geq m$ 或者 $m-l\leq len$ 就代表满足条件，记录下次数就可以得到答案，然后取最小值就可以了。 

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,k,m,a,b,ans,res,cnt,l,len,rp;
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld%lld%lld%lld",&n,&k,&m,&a,&b);
		if(n%m==0){printf("0\n");continue;}//直接满足条件
		if(k==1){printf("-1\n");continue;}//乘以和除以都没用，所以无解
		ans=0x3f3f3f3f3f3f3f3f,cnt=rp=0;
		while(1)
		{
			l=n%m,len=1,res=cnt;//此处的len多了1，方便计算，判断也只需要把>=变成>即可
			for(int i=1;;++i)
			{
				if(len>(m-l)%m){ans=min(ans,res);break;}//满足条件
				res+=a,l*=k,len*=k,l%=m;//进行一次乘法操作
			}
			if(!n) break;//n为0也算满足条件，同时也不用继续进行除法操作
			n/=k,cnt+=b;
		}
		printf("%lld\n",ans);
	}
}
```

---

## 作者：Auto_Accepted (赞：1)

可以发现如果 $2$ 操作和 $1$ 操作交错进行的话是没有意义的，然后显然是先 $2$ 后 $1$。

然后对于每一次 $1$ 操作是可以计算上下界的，如果上下界除以 $m$ 的结果不一样即可。

所以直接枚举进行了几次 $2$ 操作，然后去算上下界取最小，最后取最小操作次数即可。

注意特判 $k=1$。

上下界记得开 `__int128`。

## 代码
```
#include <bits/stdc++.h>
using namespace std;
#define int __int128
inline int read(){
	int s = 0 , xi = 1;
	char op = getchar();
	while(op < '0' || op > '9'){
		if(op == '-') xi = -1;
		op = getchar();
	}
	while(op >= '0' && op <= '9'){
		s = (s << 1) + (s << 3) + op - '0';
		op = getchar();
	}
	return s * xi;
}
inline void print(int x){
	if(x < 0) putchar('-') , x *= -1;
	if(x < 10){
		putchar(x + '0');
		return;
	}
	print(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
    int t = read() , n , k , m , a , b;
    AK:
    while(t--){
        n = read() , k = read() , m = read() , a = read() , b = read();
        if(k == 1){
            puts(n % m ? "-1" : "0");
            continue;
        }
        int ans = LONG_LONG_MAX;
        int cnt = 0;
        while(1){
            if(!n){
                ans = min(ans , b * cnt);
                break;
            }
            int l = n , r = n;
            int tmp = b * cnt;
            while(l % m && l / m == r / m){
                r *= k;
                r += k - 1;
                l *= k;
                tmp += a;
            }
            ans = min(ans , tmp);
            cnt++;
            n /= k;
        }
        print(ans);
        puts("");
    }
}
```


---

## 作者：zzbzwjx (赞：1)

## 题意

[~~自己看题~~](https://www.luogu.com.cn/problem/P9560)

## 思路
对于操作 1 ，会使我们的数变得更大。对于一个确定的 $n$ ，执行确定的操作 1 会得到一个确定的范围，只要 $n$ 在此范围存在 $\min_n \div m \ne \max_n \div m$ 时就存在 $n$ 是 $m$ 的倍数。

仔细观察可以发现在执行操作 2 以后再执行操作 1 会进行重复操作，因此我们只需要枚举操作 2 的操作次数即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,k,m,a,b;
void do_() {
	cin>>n>>k>>m>>a>>b;
	if (k==1) { // 特判
		if (n%m!=0) {
			cout<<"-1\n";//无解
			return ;
		} else {
			cout<<"0\n";//无需操作
			return ;
		}
	}
	long long ans = 1e18;//设为上限值
	for (int i=0;;i++,n/=k) {
		if (n == 0) {//n=0时无需再操作
			ans = min(ans, 1ll * i * b);
			break;
		}
		__int128 l = n, r = n;//int128防炸（考场上千万别用）
		long long rr = i * b;
		while (r/m==l/m&&l%m) {
			r=r*k+k-1;
			l*=k;
        rr+=a;
		}
		ans=min(ans,rr);//取最小值
	}
	cout<<ans<<'\n';
}
int main() {
	cin>>t;
	while(t--) {
		do_();//封装成函数简洁美观
	}
	return 0; //好习惯
}
```
**不开 long long 见祖宗**。

---

## 作者：panxz2009 (赞：0)

操作一中的 $0\le x < k$ 和 $k\cdot n + x$ 两个元素长得就很带余除法，结合操作二是 $\lfloor\frac{n}{k}\rfloor$，不难发现操作一后面如果跟操作二一定很亏，因为这样的话就会把操作一造成的改变还原。所以考虑钦定操作顺序是先做操作二再做操作一。

又发现操作二次数也不能太多，最多 $\log n$ 次（$k=1$ 除外，在开头特判即可）。自然想到枚举操作二的操作次数，问题就转化为已知一个数 $t$，最少进行几次操作一能使得 $t$ 变为 $m$ 的倍数。我们同理发现操作一的操作次数也不会太多，数量级和操作二差不多。

考察对一个数 $t$ 进行一次操作一能造成的所有可能值。答案区间应该为 $[kt,kt+k-1]$。联系操作一次数不多，考虑也枚举操作一的操作次数，动态记录形成的所有可能值的取值区间左右端点 $l,r$，判断区间内有没有 $m$ 的倍数。如果区间内包含了 $m$ 的倍数，那么只有两种情况： $\lfloor\frac{l}{m}\rfloor<\lfloor\frac{r}{m}\rfloor$，或 $m\mid l$。

开头记得特判 $m\mid n$ 和 $k=1$ 的情况，样例很良心，两种情况都给出了。以及 $l,r$ 要开 `__int128`。
```cpp
#include <bits/stdc++.h>
#define int long long
#define ll __int128
using namespace std;
int n, k, m, a, b, ans;
void chkmin(int &x, const int &y) {
	if(x > y) x = y;
}
void solve() {
	scanf("%lld%lld%lld%lld%lld", &n, &k, &m, &a, &b);
	if(n % m == 0) {
		puts("0");
		return;
	}
	if(k == 1) {
		puts("-1");
		return;
	}
	ans = 1e18;
	ll t = n;
	for(int i = 0; i <= 65; i++) {
		ll l, r;
		l = r = t;
		for(int j = 0; j <= 65; j++) {
			if(l / m < r / m || (l / m == r / m && l % m == 0)) {
				chkmin(ans, i * b + j * a);
				break;
			}
			l = k * l, r = k * r + k - 1;
		}
		if(!t) break;
		t /= k;
	}
	printf("%lld\n", ans);
}
signed main() {
	int T;
	scanf("%lld", &T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：jamesharden666 (赞：0)

考场上就想到操作顺序只能为操作 $2$ 后跟操作 $1$ ，但是想不到如何处理操作 $1$ ，遂挂。

你可以将 $n$ 看成一个 $k$ 进制的数，每次都左移一位然后在新的一位填数。

既然不知道填啥，那就不管呗。我们只要保证对于初始的 $n$ ，左移若干位后，新位置上填的数与其相加是 $m$ 的倍数即可。

由于操作 $2$ 最多进行 $\log_{k} n $ 次，操作 $1$ 最多进行 $\log_{k} m$ 次，所以总时间复杂度为 $\mathcal O(T \log_{k} n \log_{k} m)$ 。

代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,k,m,a,b,ans=0;
long long read()
{
    long long s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
        s=s*10+(ch-'0'),ch=getchar();
    return s*w;
}
void work(long long v,long long sum)
{
    long long val=1;    
    while(1)
    {
        v=v*k%m;
        val=val*k;
        sum=sum+a;  
        if(val-1>=m-v||v==0)
            break;
    }
    ans=min(ans,sum);
}
int main()
{
    t=read();
    while(t--)
    {
        n=read(),k=read(),m=read(),a=read(),b=read();
        if(n%m==0)
        {
            printf("0\n");
            continue;
        }
        if(k==1)
        {
            printf("-1\n");
            continue;
        }
        ans=LONG_LONG_MAX;
        long long sum=0;
        while(n>0)
        {
            if(n%m==0)
                ans=min(ans,sum);
            else
                work(n%m,sum);
            n/=k;
            sum+=b;
        }
        ans=min(ans,sum);
        printf("%lld\n",ans);
    }
}
```

---

## 作者：huangrenheluogu (赞：0)

不知道哪个唐氏在模拟赛 T1 少了一个字符被挂分。

$1$ 操作是在 $n$ 的 $k$ 进制后增加一位；$2$ 操作是把 $n$ 的 $k$ 进制最后一位去掉。

应该先进行 $2$ 操作再进行 $1$ 操作，不然一个 $2$ 操作会消去 $1$ 操作的影响。

特判 $k=1$，枚举 $2$ 操作操作的次数，然后算至少进行几次 $1$ 操作，及找到最小的 $bit$ 满足 $n\times k^{bit}\le am\lt n\times k^{bit}+k^{bit},a\in\mathbb{N}$。

复杂度 $\mathcal{O}(T\log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf = 0x3f3f3f3f3f3f3f3f;
int T, n, k, m, A, B, ans, tmp;
inline int calc(int n){
	n %= m;
	for(int i = 1, j = 0; ; i = i * k, j++, n = n * k % m){
		if(n == 0 || n + i - 1 >= m) return j * A;
	}
	return inf;
}
inline int solve(){
	if(n % m == 0) return 0;
	if(k == 1) return -1;
	tmp = 0;
	ans = inf;
	ans = min(ans, calc(n));
	while(n){
		tmp += B;
		n /= k;
		ans = min(ans, calc(n) + tmp);
	}
	return ans;
}
signed main(){
// 	freopen("transform.in", "r", stdin);
// 	freopen("transform.out", "w", stdout);
	scanf("%lld", &T);
	while(T--){
		scanf("%lld%lld%lld%lld%lld", &n, &k, &m, &A, &B);
		printf("%lld\n", solve());
	}
	return 0;
}

```

---

## 作者：__zfy__ (赞：0)

### 思路
通读题目，不难发现如果 operate $1$ 和 operate $2$ 交替进行的话，是没有意义的。其实只要先 $2$ 后 $1$ 即可。接着只要枚举每一次 operate $2$，去找这次的上下限找到最小操作次数和最小上下限。

需要特判 $k = 1$ 的情况。
### 代码
下面是来自[这位大佬](https://www.luogu.com.cn/user/607943)的代码。
```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;

void hh()
{
	int n,k,m,a,b;
	cin >> n >> k >> m >> a >> b;

	if (k == 1) {
		if (n % m != 0) {
			cout << "-1" << endl;
			return;
		}
		else {
			cout << "0" << endl;
			return;
		}
	}
	int ans = 1e16,op = 0;
	while (1) {
		if (n == 0) {
			ans = min(ans, op * b);
			break;
		}
		__int128_t front = n, rear = n;
		int cur = op * b;
		while (rear / m == front / m && front % m) {
			rear = rear * k + k - 1;
			front *= k;
			cur += a;
		}
		ans = min(ans, cur);
		
		op++;
		n /= k;
	}

	cout << ans << endl;
}
signed main()
{
    int T;
    cin >> T;

    while (T--) hh();

    return 0;
}
```


---

## 作者：hh__hh (赞：0)

对于操作 $1$，会使我们的数变得更大。

对于一个确定的 $n$，执行确定的操作 $1$ 会得到一个确定的范围，只要 $n$ 在此范围存在 $\frac{n_{min}}{m} \ne \frac{n_{max}}{m}$ 时就是，就存在 $n$ 是 $m$ 的倍数。

观察可得在执行操作以后再执行操作一会进行重复操作，因此我们需要枚举操作二的操作次数计可。

注意特判一下 $k=1$ 的情况。

代码：

```c
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;

void hh()
{
	int n,k,m,a,b;
	cin >> n >> k >> m >> a >> b;

	if (k == 1) {
		if (n % m != 0) {
			cout << "-1" << endl;
			return;
		}
		else {
			cout << "0" << endl;
			return;
		}
	}
	int ans = 1e16,op = 0;
	while (1) {
		if (n == 0) {
			ans = min(ans, op * b);
			break;
		}
		__int128_t front = n, rear = n;
		int cur = op * b;
		while (rear / m == front / m && front % m) {
			rear = rear * k + k - 1;
			front *= k;
			cur += a;
		}
		ans = min(ans, cur);
		
		op++;
		n /= k;
	}

	cout << ans << endl;
}
signed main()
{
    int T;
    cin >> T;

    while (T--) hh();

    return 0;
}
```

注意开 $\text{long long}$，还有那个友（e）好（xin）的 `__int128`。

---

## 作者：SakurajiamaMai (赞：0)

## 思路:
很明显我们一开始要除，因为如果先进行乘法然后再除的话那就没有意义了，会把之前乘的再除掉。

那么要除多少次才合适呢？由于时间限制我们可以枚举每一次直到 $n$ 对 $k$ 的取模为 $0$ 为止，每次枚举都取最小值，最终得出来的值一定是最优解。在枚举的过程中设置两个边界进行判断即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,mod=1e9+7;
string s;
int n,t,a,b,res,ans,m,k;
bool vis[N];
void solve()
{
    cin>>n>>k>>m>>a>>b;
    if(k==1){
        if(n%m) cout<<-1<<endl;
        else cout<<0<<endl;
        return;
    }
    res=2e18;
    for(int i=0;~i;n/=k,i++){
        if(n==0){
            res=min(res,i*b);
            break;
        }
        __int128_t l=n,r=n;
        int ans=i*b;
        while(l/m==r/m&&l%m){
            l*=k,r=r*k+k-1;
            ans+=a;
        }
        res=min(res,ans);
    }
    cout<<res<<endl;
    return;
}
signed main()
{
    std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
```



---

