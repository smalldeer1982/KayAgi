# [ABC117D] XXOR

## 题目描述

有n个数 $a_1,a_2,\dots,a_n$ 和一个数 $k$，$\oplus$ 表示按位异或。对于 $0\leq x\leq k，f(x)=(x \oplus a_1)+(x \oplus a_2)……(x \oplus a_n)$。求 $f_{\max}$ 为多少。

## 说明/提示

$1\leq n\leq 10^5,0\leq k,a_i\leq 10^{12}$。

## 样例 #1

### 输入

```
3 7
1 6 3```

### 输出

```
14```

## 样例 #2

### 输入

```
4 9
7 4 0 3```

### 输出

```
46```

## 样例 #3

### 输入

```
1 0
1000000000000```

### 输出

```
1000000000000```

# 题解

## 作者：Nightingale_OI (赞：5)

### 大意

给你一个长度为 $ n $ 数组 $ a $ 。

定义：

 $$ f(x) = \sum^{n}_{i=1} x \oplus a_i $$

求在 $ 0 \leq x \leq k $ 情况下 $ f(x) $ 的最大值。

### 思路

设 $ p(a,b) $ 表示 $ a $ 二进制下从右往左第 $ b  $ 位。

$ x $ 的第 $ i $ 位贡献就是：

$$ \sum^{n}_{i=1} p(x,i) \oplus p(a_i,i) $$

每个位置只有 $ 2 $ 中情况，可以处理出来，贪心选择。

但是我们不一定符合 $ x \leq k $ ，从左到右枚举哪一位比 $ k $ 的该位小，后面所有贪心即可。

可以用类似后缀和和维护。

时间复杂度 $ O(\sum_{i=1}^{n}\log_{2}a_i) $ 。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
long long k,h,r,ans;
long long a[101010];
long long p[50];
int t[50];
int main(){
    cin>>n>>k;
    f(i,1,n)scanf("%lld",&a[i]);
    f(i,1,n)r+=a[i];ans=r;
    p[1]=1;
    while(k){
        ++m;
        t[m]=k&1;
        p[m+1]=p[m]*2;
        f(i,1,n)s+=(a[i]&1?-1:1);
        f(i,1,n)a[i]/=2;
        p[m]*=max(s,0);
        k/=2;
        s=0;
    }
    f(i,1,m)p[i]+=p[i-1];
    g(i,m,1)if(t[i]){
        ans=max(ans,r+h+p[i-1]);
        h+=p[i]-p[i-1];
    }
    ans=max(ans,r+h);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：caocao11 (赞：4)

网上看到有些题解做法可以被卡掉，所以来发个应该是正解的做法。  
位运算多半要将数据转化为二进制，然后可以独立考虑每一位的贡献。于是将题目从计算每个数在所有二进制位上的贡献转化为计算每个二进制位上所有数字的贡献。  
从高到低分别考虑每个二进制位的贡献，容易贪心地想到若该二进制位上为 $0$ 的数比为 $1$ 的数多，那么 $x$ 该位取 $1$ ，反之取 $0$。但同时还要考虑 $x\leq k$ 的限制（即可能第 $i$ 位选 $1$ 比选 $0$ 优，但第 $i$ 位选了 $1$，第 $i-1$ 位为了保证 $x\leq k$ 就只能选 $0$，而第 $i$ 位选 $0$，第 $i-1$ 位选 $1$ 更优）,所以不能直接贪心，考虑 dp。  
运用类似数位 dp 的思想，令 $f[i][0]$ 为考虑到二进制第 $i$ 位，目前为止 $x$ 仍顶着 $k$ 的上限时的最大值；$f[i][1]$ 为考虑到二进制第 $i$ 位，$x$ 已经小于 $k$（即后面的二进制位可以不用考虑 $k$ 的限制）时的最大值。具体 dp 转移见代码。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define rg register int
using namespace std;
ll read(){
	char ch=getchar();
	ll res=0,f=1;
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		res=(res<<1)+(res<<3)+ch-'0';
		ch=getchar();
	}
	return res*f;
}
void write(ll x){
	if(x>9) write(x/10);
	putchar((x%10)^48);
}
const int N=1e5+5;
ll k,l,ans,a[N],f[60][2];
int main(){
	int i,j,l,n,m,num1,num2;
	n=read();k=read();
	for(i=1;i<=n;i++) a[i]=read();
	for(i=0;i<=55;i++) f[i][0]=f[i][1]=-1;
	f[51][0]=0;
	for(i=50;i>=0;i--){
		num1=num2=0;
		for(j=1;j<=n;j++){
			if((1ll<<i)&a[j]) num1++;
			else num2++;
		}
		if((1ll<<i)&k){
			if(f[i+1][0]!=-1)
			f[i][0]=f[i+1][0]+1ll*(1ll<<i)*num2;
			if(f[i+1][1]!=-1)
			f[i][1]=f[i+1][1]+1ll*(1ll<<i)*max(num1,num2);
			if(f[i+1][0]!=-1)
			f[i][1]=max(f[i][1],f[i+1][0]+1ll*(1ll<<i)*num1);
		}
		else{
			if(f[i+1][0]!=-1)
			f[i][0]=f[i+1][0]+1ll*(1ll<<i)*num1;
			if(f[i+1][1]!=-1)
			f[i][1]=f[i+1][1]+1ll*(1ll<<i)*max(num1,num2);
		}
	}
	write(max(f[0][0],f[0][1]));
	return 0;
}
```

---

## 作者：CQ_Bob (赞：2)

## 分析

拆位然后贪心就可以了。

对于二进制下第 $i$ 位，统计出 $x_i=1$ 时能有多少个 $j$，使得 $a_j$ 的第 $i$ 为与其异或为 $1$。这个其实就是在求 $a_j$ 的第 $i$ 位为 $0$ 的数量。那么，$x_i=1$ 时对答案的贡献就是 $2^i \times cnt$。$cnt$ 为数量。可以贪心地从最高位往下看，如果某一位取 $1$ 所得的贡献比 $0$ 的大，且这一位能够为 $1$，就让 $x_i=1$。答案就是最后的 $x$ 与 $a_i$ 的异或和。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int N=1e5+1;
int n,k,a[N];
int ans,sum;

il void solve(){
	cin>>n>>k;
	for(re int i=1;i<=n;++i) cin>>a[i];
	for(re int i=40;i>=0;--i){
		int cnt=0;
		for(re int j=1;j<=n;++j) cnt+=(!((a[j]>>i)%2));
		if(cnt>=n-cnt&&(ans+(1LL<<i))<=k) ans+=(1LL<<i);
	}
//	cout<<ans<<" ";
	for(re int i=1;i<=n;++i) sum+=(ans^a[i]);
	cout<<sum;
	return ;
}

signed main(){
	solve();
	return 0;
}

```


---

## 作者：xxr___ (赞：1)

### 思路：
本题用到位运算加贪心的思想，首先对于运算方面，因为以二为底，所以我们直接用左移即可，其次我们贪心的想，每一种最大的情况只有两种，所以我们只需要枚举两种情况即可，这里我们可以定义一个二维数组来记录，然后这个题就结束了。
### 代码：
```cpp
#include<bits/stdc++.h>
#define FOR(i, n) for(i = 0; i < n; i++)
#define int long long
using namespace std;
int n, k;
int a[100000];
signed main(){
	int i,j; 
	cin >> n >> k;
	FOR(i,n) cin >> a[i];
	int x = 0;
	for (i = 40; i >= 0; i--) {
		int cnt = 0;
		FOR(j, n)
			if ((a[j] >> i) % 2) cnt++;
		if (cnt < n - cnt && x + (1LL << i) <= k)
			x += (1LL << i);
	}
	
	int ans = 0;
	FOR(i, n) {
		ans += x ^ a[i];
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：EuphoricStar (赞：0)

## 思路

能算得上是贪心（？）

碰到异或一类的位运算的题，通常都考虑拆位算贡献。所以我们从高位往低位算 $x$ 的最优值。

发现我们如果要让 $x$ 的第 $i$ 位变为 $1$ 时答案更优，那就需要满足 $a$ 中第 $i$ 位为 $0$ 的数的个数大于第 $i$ 位为 $1$ 的数的个数。因为异或的本质是对于每一位如果两位上的数相加的和为 $1$ 结果的这一位就为 $1$，否则为 $0$。所以 $0$ 的个数大于 $1$ 的个数时是可以使最后的答案增加的。

注意如果个数相等，那么 $x$ 的这一位变为 $1$ 结果会更劣。因为不仅不能使答案增加，还有可能使低位无法增加贡献。

算出 $x$ 后就可以直接算答案了。

## 代码

```cpp
/*

p_b_p_b txdy
AThousandMoon txdy
AThousandSuns txdy
hxy txdy

*/

#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define scd second

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

const int maxn = 100100;

ll n, m, a[maxn];

void solve() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
	}
	ll x = 0;
	for (int j = 60; ~j; --j) {
		int cnt0 = 0, cnt1 = 0;
		for (int i = 1; i <= n; ++i) {
			if (a[i] & (1LL << j)) {
				++cnt1;
			} else {
				++cnt0;
			}
		}
		if (cnt0 > cnt1 && (x | (1LL << j)) <= m) {
			x |= (1LL << j);
		}
	}
	ll ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans += (x ^ a[i]);
	}
	printf("%lld\n", ans);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}

```


---

## 作者：cppcppcpp3 (赞：0)

因为异或运算不同二进制位之间是独立的，所以可以按位拆开贪心；因为更高位对答案的贡献会比低位更多，所以从高往低位贪心。

设 $a$ 中从低到高第 $i$ 位（最低位为第 $0$ 位）为 $1$ 的有 $cnt_i$ 个。则进行第 $i$ 位的选择时进行如下考虑：

- $2 \times cnt_i > n$，超过总数一半，这个时候 $x$ 的第 $i$ 位相应取 $0$。贡献为 $cnt_i \times 2^i$。

- $2 \times cnt_i = n$，刚好一半，取 $0$ 取 $1$ 贡献相等。但题目限制 $x \le k$，因此取 $0$ 使当前 $x$ 尽量小，贡献如第一种情况。

- $2 \times cnt_i < n$，如果该位取 $1$ 后 $x$ 仍不大于 $k$ 就贪心取 $1$，贡献为 $(n-cnt_i) \times 2^i$；否则取 $0$。 

从高位往低位扫一遍即可。

```cpp
#include<bits/stdc++.h>
#define il inline
#define int long long
using namespace std;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}

int n,k,cnt[41];
int sum,t;

main(){
	n=wrd(),k=wrd();
	for(int i=1;i<=n;++i){
		int a=wrd();
		for(int j=0;(1ll<<j)<=a;++j) cnt[j]+=((a>>j)&1);
	}
	
	for(int i=40;i>=0;--i){
		if(cnt[i]*2<n && (t|(1ll<<i))<=k) t|=(1ll<<i),sum+=((n-cnt[i])<<i); 
		else sum+=(cnt[i]<<i);
	}
	return printf("%lld",sum),0;
}
```

---

