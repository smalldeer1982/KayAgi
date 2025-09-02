# [ABC090D] Remainder Reminder

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc090/tasks/arc091_b

高橋君は、$ N $ 以下の正の整数の $ 2 $ つ組 $ (a,b) $ を持っていましたが、忘れてしまいました。 高橋君は、$ a $ を $ b $ で割ったあまりが $ K $ 以上であったことを覚えています。 高橋君が持っていた組としてあるうるものの個数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ K\ \leq\ N-1 $
- 入力は全て整数である

### Sample Explanation 1

ありうる組は、$ (2,3),(5,3),(2,4),(3,4),(2,5),(3,5),(4,5) $ の $ 7 $ 組です。

## 样例 #1

### 输入

```
5 2```

### 输出

```
7```

## 样例 #2

### 输入

```
10 0```

### 输出

```
100```

## 样例 #3

### 输入

```
31415 9265```

### 输出

```
287927211```

# 题解

## 作者：RainFestival (赞：4)

本题求 $\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}[i\mod j\ge k]$

$=\sum\limits_{j=1}^{n}\sum\limits_{i=1}^{n}[i\mod j\ge k]$

令 $x=\lfloor\frac{i}{j}\rfloor,y=n\mod i$

$=\sum\limits_{j=1}^{n}(\sum\limits_{i=1}^{x}\sum\limits_{p=0}^{j-1}[p\ge k]+\sum\limits_{p=0}^{y}[p\ge k]-[0\ge k])$

当 $k=0$ 时将多算一个 $i=0$ 的情况所以要减掉

$=\sum\limits_{j=k+1}^{n}(x\cdot (k-j)+\max(0,y-k+1)-[k=0])$

这样就可以在 $O(n)$ 的时间内做完

代码：

```cpp
#include<cstdio>
#include<algorithm> 
int n,k;
long long ans=0;
int main()
{
	scanf("%d%d",&n,&k);
	for (int i=k+1;i<=n;i++)
	{
		int x=n/i,r=n%i;
		ans=ans+1ll*x*(i-k)+std::max(0,r-k+1);
		if (k==0) --ans;
	}
	printf("%lld\n",ans);
}
```


---

## 作者：qwerty12346 (赞：3)

# [题目传送门](https://www.luogu.com.cn/problem/AT_arc091_b)

## 题意

就是求有序正整数对 $(a,b)$ 的个数，并且 $a$ $\operatorname{mod}$ $b$ $\ge$ $K$。

## 思路

循环求 $(a,b)$ 的个数，如果 $y-k+1$ 大于 $0$ 那么本轮的个数就是 $x×(i-k)+y-k+1$，否则本轮的个数是 $x\times(i-k)$。还有，如果 $k$ 为 $0$ 那么个数要减一，因为多算了 $i$ 为 $0$ 时的情况。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,ret;
int main(){
    cin>>n>>k;
    for(int i=k+1;i<=n;i++)
    {
	long long x=n/i,y=n%i;
        if(y-k+1>0)ret+=x*(i-k)+y-k+1;//判断
	else ret+=x*(i-k);
	if(k==0)ret--;//如果k=0那么个数减一
    }
    cout<<ret<<endl;
    return 0;
}
```


---

## 作者：Eason_cyx (赞：2)

考虑枚举除数。当除数为 $i$ 时，我们可以将 $1\sim n$ 所有的数进行分段，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/xj98rir8.png)

其中，整个数列被分成了 $m$ 段。注意：最后一段 $mi \sim n$ **可能**不是完整的一段。

我们可以分段考虑。对于第一段，有 $i-1-k+1=i-k$ 个数可以作为可行的被除数。除去最后一段，前面一共有 $\frac{n-(n\bmod i)}{i}$ 段，可以转换为 $\lfloor\frac{n}{i}\rfloor$ 段。所以，除去最后一段的答案为 $(i-k)\times\lfloor\frac{n}{i}\rfloor$。

那最后一段呢？最后一段的长度显然为 $n\bmod i$，而这个值可能大于等于，也可能小于 $k$。如果大于等于 $k$，那么这一段的长度为 $n\bmod i-k+1$。那么如果小于 $k$，这个值就应该是负数。所以最后一段的贡献为 $\max(n\bmod i-k+1,0)$。

由于余数至少大于等于 $k$，所以除数为 $1\sim k$ 时的枚举是没有意义的。所以我们直接从 $k+1$ 开始枚举。

注意：当 $k=0$ 时会多算 $n$（为什么？原因留给读者思考），所以记得减去。

[AC Record](https://atcoder.jp/contests/abc090/submissions/50026687)

---

## 作者：Cosine_Func (赞：1)

可以直接枚举 $b$ 的值，求对于每个 $b,a$ 满足条件的取值个数之和。

显然，只有当 $r+1\leq b\leq n$ 时，才能取到合适的 $a$。

考虑将 $[1,n]$ 划分成 $\lfloor n/b \rfloor$ 个每个区间有 $b$ 个元素的完整连续区间和一个剩余区间。对于每一个完整区间都有 $b−r$ 个 $a$ 的取值；对于剩余区间，可以进行分类讨论。

参考代码：
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define ll long long
#define endl '\n'
#define itn int
#define pi pair<int,int>
#define int ll
using namespace std;
const int MOD1=1e9+7;
const int MOD2=998244353;
const int N=1e5+5;
int ans;
inline void Solve(){
	int n,r;
	cin>>n>>r;
	for(int b=r+1;b<=n;b++){
		int L=r,R=b-1;
		int cnt=0;
		cnt+=(n/b)*(R-L+1ll);
		int p=n%b;
		if(1<=L and L<=p and p<=R)cnt+=p-L+1;
		if(1<=L and p>R)cnt+=R-L+1;
		if(1>L and 1<=R and R<=p)cnt+=R;
		if(1>L and R>p)cnt+=p;
		ans+=cnt;
	}
	cout<<ans;
}
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    int T=1;
    //cin>>T;
    while(T--)
    	Solve();
    return 0;
}
```

---

## 作者：Carey2012 (赞：1)

## 传送门
> [传送门](/problem/AT_arc091_b)
## 思路
题目中叫我们求有序正整数对 $(a,b)$ 的个数，\
其中每个对需要满足 $1\le a,b\le N$ ，且 $a\bmod b\ge K$。\
我们可以打暴力看符合个数，看 data。
```CPP

//#pragma GCC optimize(2)
#include<bits/stdc++.h>
//#define gets(C) fgets(C,sizeof(C),stdin);
//#define fi first
//#define se second
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int MAX=2e5+11,mod=1e4+7,INF=0x3f3f3f3f;
int n,k;
ll ans=0;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=min(k+1,n);i<=n;i++){
		for(int j=max(1,k);j<=n;j++){
			if(j%i>=k){
				ans++;
				cout << j << ' ' << i << '\n';
			}
		}
	}printf("%lld",ans);
	return 0;
}
```
输入数据：
```
6 2
```
输出数据：
```
2 3
5 3
2 4
3 4
6 4
2 5
3 5
4 5
2 6
3 6
4 6
5 6
12
```
我们可以看到其中的规律，就是每一个模数 $i$，\
有 $\left \lfloor \frac{n-k}{i} \right \rfloor $ 组，每一组有 $i-k$ 个符合要求的 $j$，\
还有最后剩余的几个数，也要加上，\
即 $\min \left (i-k,n-\left \lfloor \frac{n-k}{i}  \right \rfloor *i-k+[k\ne 0]  \right ) $ 个。\
所以，上代码！
## Data（[AC link](https://atcoder.jp/contests/abc090/submissions/61457589)）
```CPP
//#pragma GCC optimize(2)
#include<bits/stdc++.h>
//#define gets(C) fgets(C,sizeof(C),stdin);
//#define fi first
//#define se second
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int MAX=2e5+11,mod=1e4+7,INF=0x3f3f3f3f;
int n,k;
ll ans=0;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=k+1;i<=n;i++){
		ans+=(n-k)/i*(i-k)+min(i-k,n-(n-k)/i*i-k+(k!=0));
	}printf("%lld",ans);
	return 0;
}
```

---

## 作者：LHLeisus (赞：1)

[赏心悦目的阅读体验](https://www.cnblogs.com/LHLeisus/p/17836380.html)

原题链接： [洛谷](https://www.luogu.com.cn/problem/AT_arc091_b) $\ $ [AtCoder](https://atcoder.jp/contests/abc090/tasks/arc091_b)

如果你觉得 $O(n)$ 没有跑到极限的话，你可以试试整除分块。

先来化一下式子：

$$\sum\limits_{i=1}^n\sum\limits_{j=1}^n\;[i\bmod j\ge k]$$

$$\sum\limits_{i=1}^n\sum\limits_{j=1}^n\;[i-\left\lfloor\dfrac{i}{j}\right\rfloor\times j\ge k]$$

$$\sum\limits_{i=1}^n\sum\limits_{j=1}^n\;[\left\lfloor\dfrac{i}{j}\right\rfloor\times j\le i-k]$$


这个 $\left\lfloor\frac{i}{j}\right\rfloor$ 长得就很能整除分块。然后就是基础的操作了，我们枚举 $i$，对于每个 $j$，一直到 $\left\lfloor\frac{i}{\left\lfloor\frac{i}{j}\right\rfloor}\right\rfloor$，$\left\lfloor\frac{i}{j}\right\rfloor$ 的取值都不变，但是这里还有一个 $\times j$ 没有处理。我们可以把 $\left\lfloor\frac{i}{j}\right\rfloor$ 除过去，算一下 $\left\lfloor\frac{i-k}{\left\lfloor\frac{i}{j}\right\rfloor}\right\rfloor$，也就是最大可以乘多大的 $j$，再与当前块的左端点作比较即可。需要注意 $\left\lfloor\frac{i}{j}\right\rfloor=0$ 的情况，特殊处理。

时间复杂度 $O(n\sqrt n)$。

code:

```cpp
int main()
{
	n=read(),k=read();
	ll ans=0;
	FOR(i,1,n){
		for(int l=1,r;l<=n;l=r+1){
			if(i/l==0) r=n;
			else r=min(i/(i/l),n);
			int t=i/l;
			if(t==0){
				if(i-k>=0) ans+=r-l+1;
				continue;
			}
			t=(i-k)/t;
			ans+=max(0,t-l+1);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：yihang2011 (赞：0)

# [ABC090D] Remainder Reminder题解

[题目传送门](https://www.luogu.com.cn/problem/AT_arc091_b)

----

整体思路就是枚举除数，从 $\displaystyle k + 1$ 枚举到 $\displaystyle n$。

对于每次枚举，都会有 $\displaystyle \lfloor \frac{n}{i} \rfloor$ 个完整的区间，每一个区间会有 $\displaystyle i - 1 - k + 1 = i - k$ 个符合要求的被除数。

分割完完整区间后而剩下的会产生 $\displaystyle (n \bmod i) - k + 1$ 个符合要求的被除数，但 $\displaystyle (n  \bmod i) - k + 1$ 有可能会小于零，所以要与 $\displaystyle 0$ 取较大值，最后得出不能划分区间的部分会产生 $\max((n \bmod i) + k - 1, 0)$ 个符合要求的被除数。

最后的最后，每一次枚举产生的符合要求的被除数有 $\displaystyle \lfloor \frac{n}{i} \rfloor \times (i - k) + \max((n \bmod i) + k - 1, 0)$ 个。

-----------------

不过，观察数据范围，$\displaystyle 0 \le k \le n - 1$，发现 $\displaystyle k = 0$ 时会多算一个 $n$（当 $i = 0$ 时）。

可以考虑减去，也可以直接利用数据的特殊性质直接输出  $\displaystyle n^{2}$ 好了。

------

时间复杂度是 $\displaystyle O(n)$，很好说。

注意要开 `long long`。

```cpp
#include <iostream
using namespace std;

int n, k;
long long ans;

int main() {
	cin >> n >> k;
	if (k == 0) {
		cout << (long long)n * n << endl;
		return 0;
	}
	for (int i = k + 1; i <= n; i++) {
		ans += (n / i * (i - k) + max(n % i - k + 1, 0));
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

就是说，如果暴力就能过，那么你还会推式子吗？

这里的暴力不是让你枚举所有的数对，而是枚举模数，然后算合法区间的大小。合法区间倒是很好整，假设模数为 $v$，那么合法区间就是 $[tv+k,(t+1)v-1]$，其中 $t$ 为非负整数。

当然了，不要忘了特判一下 $k=0$ 的情况。当 $k=0,t=0$ 的时候上述区间会包含 $0$，需要减掉。

你以为这是 $O(n^2)$ 的吗？错了，他的极限复杂度应该是 $\Sigma_{i=1}^n\frac{n}{i}$。这是调和级数，与 $n\log n$ 同级。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,ans;
signed main(){
	cin>>n>>k;
	for(int i=k+1;i<=n;++i)
		for(int j=0;;j++){
			int lp=j*i+k,rp=i*(j+1)-1;
			if(lp>n) break;
			if(rp>n){
				ans+=(n-lp+1);
				break;
			}
			ans+=(rp-lp+1);
		}
	cout<<ans-n*(k==0)<<endl;
	return 0;
} 
```

---

## 作者：Berd__ (赞：0)

### 题面大意

求出满足 $1\le a,b\le N$ 且 $a\bmod b\ge K$ 的有序数对 $(a,b)$ 的个数。

### 数据范围

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ K\ \leq\ N-1 $
- 输入的都是整数

### 思路

看楼上大佬有 $O(n\sqrt n)$ 的，蒟蒻来一发 $O(N)$ 的。

直接枚举。

枚举到每个 $b$，求对于每个 $b,a$ 满足条件的个数的总和。

可以发现，因为 $a \bmod b$ 如果要大于 $K$，$b$ 必须大于 $K+1$，综上，$b$ 的取值范围在 $K+1,N$ 之间，所以考虑将 $[1,N]$ 划分成 $N/b$ 个每个区间有 $b$ 个元素的完整连续区间和一个剩余区间（这个很重要！）。

在每一个完整区间里有 $b-K$ 个 $a$，就不讲了。

而在剩余区间里，$a$ 则可以取 $N\bmod b-k+1$ 个值。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,k,answer;
signed main(){
	cin>>n>>k;
	for(int b=k+1;b<=n;b++){
		answer+=(b-k)*(n/b);
		answer+=max(0,n%b-k+1);
		if(k<=0) answer--;
	}
	cout<<answer;
	return 0;
} 

```

---

## 作者：___cjy__ (赞：0)

# Remainder Reminder 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_arc091_b)

[更好的阅读体验](https://www.luogu.com.cn/blog/chengjiayi666/solution-at-arc091-b)

### 题目大意：

求有序正整数对 $(a,b)$ 满足 $1\le a,b\le N$ 且 $a\bmod b\ge K$ 的个数。

### 正文：

总要：枚举加一点点数学思想。

由于数据量并不大，可以直接枚举 $b$ 的值，求对于每个 $b$，$a$ 满足条件的取值个数之和。

显然，只有当 $K+1\le b \le N$ 时，才能取到合适的 $a$。

考虑将 $[1,N]$ 划分成 $\lfloor N/b\rfloor$ 个每个区间有 $b$ 个元素的完整连续区间和一个剩余区间。对于每一个完整区间都有 $b-K$ 个 $a$ 的取值；对于剩余区间 $a$ 可以取 $\max(0,N\%b-K+1)$ 个值。

值得注意的是，当 $K=0$ 时 $i=0$ 会出现重复计算，记得避免。

### AC Code：

```cpp
#include <bits/stdc++.h>
#define int long long
#define N 205
#define INF 0x3f3f3f3f
#define bug printf(".....bug!.....\n");
#define max(a,b) a>b?a:b

using namespace std;

int n, k, ans = 0;

signed main(){
	cin >> n >> k;
	for(int b=k+1; b<=n; b++){
		ans += (n/b)*(b-k);
		ans += max(0, n%b-k+1);
		if(!k) ans--;
	}
	cout << ans;
	
	return 0;
} 
```

---

## 作者：Demons_Killer (赞：0)

# 解题思路：
本题求满足条件的序列，可以直接模拟。

求 $a$ 和 $b$ 的个数，一轮一轮地去求。如果 $y-k+1$ 大于 $0$ 那么本轮的个数就是 $x×(i-k)+y-k+1$。记得要判断 $k$ 为 $0$ 时要减去后面的一，以为多算了为 $0$ 的情况。

# code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
int ans=0;
signed main(){
	cin>>n>>k;
	for (int i=k+1;i<=n;i++)
	{
		int x=n/i,r=n%i;
		ans=ans+1ll*x*(i-k)+max(0ll,r-k+1);
		if (k==0) --ans;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

