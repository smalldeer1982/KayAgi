# [ABC280D] Factorial and Multiple

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc280/tasks/abc280_d

$ 2 $ 以上の整数 $ K $ が与えられます。  
正の整数 $ N $ であって、$ N! $ が $ K $ の倍数となるようなもののうち最小のものを求めてください。

ただし、$ N! $ は $ N $ の階乗を表し、問題の制約下で、そのような $ N $ が必ず存在することが証明できます。

## 说明/提示

### 制約

- $ 2\leq\ K\leq\ 10^{12} $
- $ K $ は整数

### Sample Explanation 1

\- $ 1!=1 $ - $ 2!=2\times\ 1=2 $ - $ 3!=3\times\ 2\times\ 1=6 $ - $ 4!=4\times\ 3\times\ 2\times\ 1=24 $ - $ 5!=5\times\ 4\times\ 3\times\ 2\times\ 1=120 $ より、$ N! $ が $ 30 $ の倍数となる最小の正整数 $ N $ は $ 5 $ です。よって、$ 5 $ を出力します。

## 样例 #1

### 输入

```
30```

### 输出

```
5```

## 样例 #2

### 输入

```
123456789011```

### 输出

```
123456789011```

## 样例 #3

### 输入

```
280```

### 输出

```
7```

# 题解

## 作者：PineappleSummer (赞：13)

[$\color{orangered}\text{题目传送门}$](https://www.luogu.com.cn/problem/AT_abc280_d)

[$\color{orangered}\text{在cnblogs中阅读}$](https://www.cnblogs.com/PineappleSummer/p/ABC280.html#d---factorial-and-multiple)
## 题意
- 给出一个数 $k$，求一个数 $n$，要求 $n!$ 是 $k$ 的倍数，输出 $n$ 的最小值。
- $k\le10^{12}$

## 分析
如果答案小于 $2\times10^6$，直接枚举。

否则，一定有某个质因子 $p^k$ 没有被 $n!$ 完全包含。其必要条件是：$p\times k\ge 2\times10^6$，但根据数据范围又有 $p^k\le10^{12}$，

因此，只可能是 $k=1$ ，才不会产生矛盾。在这种情况下，答案是 $p$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long k,g;
	cin>>k;
	for(long long i=2;i<=2000000;i++){
		k/=__gcd(k,i);
		if(k==1)
		{
			cout<<i<<endl;
			return 0;
		}
	}
	cout<<k<<endl;
	return 0; 
}
```

---

## 作者：_dijkstra_ (赞：8)

D 题。为什么人均二分？？这题就是暴力啊。

## 思路

考虑对 $k$ 分解质因数。

对于一组质因数 $p^c$，容易想到，阶乘只有 $p$ 的倍数才能对这个质因数产生贡献。

所以枚举 $p$ 的倍数即可。注意，**并不是所有的 $p$ 的倍数都只会贡献 $1$ 点**。比如说 $p^2$ 显然可以贡献两点指数。

所以我们还要看一个数里面有多少个 $p$。具体看代码。

## 代码

```cpp
ll calc(ll p, int c) //p^c
{
	ll i, cnt;
	for (i = p, cnt = 0;; i += p)
	{
		ll ti = i;
		while (i % p == 0) i /= p, cnt++;
		i = ti;
		if (cnt >= c) return i;
	}
}

void solve()
{
	ll k, ans = 0;
	cin >> k;
	ll tk = k;
	for (int i = 2; 1ll * i * i <= tk; i++)
		if (k % i == 0)
		{
			int cnt = 0;
			while (k % i == 0) cnt++, k /= i;
			ans = max(ans, calc(i, cnt));
		}
	if (k > 1) ans = max(ans, calc(k, 1));
	cout << ans << '\n';
}
```

---

## 作者：2011qiqi (赞：7)

题意：

给你一个数 $k$，你需要求出一个最小的数 $n$，使得 $n!$  是 $k$ 的倍数，且 $n$ 得最小。

---

思路：

对 $k$ 分解质因数，然后再二分答案。

我们对 $k$ 质因数分解之后，根据唯一分解定理，有唯一的表达式 $k=k_1^{x_1}\cdot~k_2^{x_2}\cdot~...\cdot~k_k^{x_k}$。

对 $n!$ 分解质因数后，同样也有一个表达式。把这两个表达式做比较，如果 $k_1,k_2,...,k_k$ 的幂次 $x_1,x_2,...,x_k$ 全都大于等于 $n!$ 中对应的质因子的幂次，那么 $n!$ 就是 $k$ 的倍数。

求 $n!$ 中能分解出的因子 $x$ 的个数。质因子 $x$ 不仅存在于 $x$ 的倍数中，还存在于 $x^2,x^3,x^4,...,x^n$ 中。

对于每一个个数的阶乘，比如，$5$ 的因子一定是每相隔 $5$ 个数出现一次，例如下面这个样子：

$n!~=~1~\times~2~\times~3~\times~4~\times~(1~\times~5)~\times~...~\times~(2~\times~5)~\times~...~\times~n$

因为每相隔 $5$ 个数就会出现一个 $5$，所以只需要计算出出现了几个 $5$，计算有多少个 $5$ 我们只需要用 $n~/~5$ 即可。

但真的就结束了吗？没有，再看下面：


$...~\times~(1~\times~5)~\times~...~\times~(1~\times~5~\times~5)~\times~...~\times~(2~\times~\times~\times~5)~\times~...~\times~n$

每相隔 $25$ 个数就会出现两个 $5$，所以除了每相隔 $5$ 算作一个 $5$，每相隔 $25$ 个数还需要多算一个 $5$，也就是需要再加上 $n~/~25$ 个 $5$。

同理，每相隔 $125$ 个数就会出现三个 $5$，所以还需要加上 $n~/~125$ 个 $5$。

以此类推，最终 $5$的个数就是：

$n~/~5~+~n~/~25~+~n~/~125~+~...$

同理，其他的因子也是一样的。

__注意：本人本来是用数组来存储，结果呢？爆了，所以这里用 vector。__

---

Code(删去了前面贼长的缺省源)：

```c++
#include<bits/stdc++.h>

using namespace std;

// ```

vector<PLL> v;// k的质因子及个数

inline bool check(ll x){
	re ll i,now,cnt;
	for(i=0;i<v.size();++i){
  		now=x,cnt=0;
		while(now){
			cnt+=now/v[i].x;
			now/=v[i].x;
		}
		if(cnt<v[i].y) return false;// n的因子是否小于k的因子 
	}
	return true;
}

int main(){
 	re ll k=read_ll(),l=1,r=k,mid,i;
	for(i=2;i*i<=k;++i)
		if(k%i==0){
			v.EB(M(i, 0));// 记录k的因子
			while(k%i==0){
				k/=i;
				v.back().y++;// k因子的数量 
			}
		}
	if(k>1) v.EB(M(k, 1));// 剩下的数
	while(l<=r){// 二分
		mid=l+r>>1;
		if(check(mid)) r=mid-1;
		else l=mid+1;
	}
 	print(l);
	return 0;
}
```

---

## 作者：NightStriker (赞：6)

赛时打了30min只切了三题的蒟蒻，D一直没调出来qwq

对于这道题~~我一开始想起来的时候是打表，但是WA了大概一半的点。~~

----

回归正题。

这道题就是让我们 $n$ 是某个阶乘的因数，阶乘要尽量小。

我们可以边求阶乘，边用 $n$ 去除这个阶乘的其中一个因数，如果最后 $n=1$，就说明 $n$ 可以被该阶乘整除，就输出阶乘。

我们看到 $n \le 10^{12}$，需要枚举 $\operatorname{log_2} n$ 次来找到能整除的阶乘，求出阶乘需要 $\sqrt{n}$，所以总时间复杂度是 $\mathcal{O}(\sqrt{n})$，完全可以通过本题。

细节在代码里了，大家可以配着注释理解代码。

```cpp
for(int i=1;i<=18;i++){//18的阶乘约等于1e12
	if(i>1){
		while(n%i==0) n/=i;//如果能整除，就继续除下去。
	}
	ans = ans*i%m;//m 是 n 的原值。如果当前阶乘能整除 n，就直接结束循环。
	if(ans==0){
		cout<<i<<endl;
		return 0;
	}
}
cout<<n<<endl;//如果都不能整除，就输出现在 n 的值。
```



---

## 作者：Moyou (赞：4)

# 题意

找到一个最小的 $N!$ 使得它包含 $x$ 的所有因数。

# 思路

- 对 $x$ 进行质因数分解。

- 对于它的任意一个质因数及其指数 $p^\alpha$，$N!$ 必须满足 $ p^\alpha | N!$，我们知道，$N!$ 中 $p$ 的数量 $\text{cnt}_N$ 可以通过这个公式计算出来：

$$
\text{cnt}_N = \dfrac{N}{p} + \dfrac{N}{p^2} + \dfrac{N}{p^3} + \dots + \dfrac{N}{p^k}
$$

由此我们可以快速判断一个阶乘 $N!$ 是否满足 $\text{cnt}_N \geq \alpha$。

- 可以明显发现$\text{cnt}$ 随 $N$ 增大而增大，也就是其具有单调性，萌发一个简单的思路——二分对于每个质因数 $p ^\alpha$ 找到一个最小的 $N'$ 满足 $\text{cnt}_N\geq \alpha$。而由于最终答案 $N!$ 需要涵盖所有的质因数，因此在所求得的 $N'$ 中取最大值即为答案。

# 时间复杂度分析

1. 分解质因数：$O(\sqrt k)$；
2. 枚举 $k$ 的所有质因数：$O(\log k)$;
3. 二分找局部最优 $N!$ ：$O(\log k)$。

**时间复杂度：** $O(\sqrt{k} + \log^2 k)$。

# 代码

```cpp
vector<PII> prime;
int mx = -INF;

bool check(int x, int num, int k) // 分别对应 N p k
{
    int sum = 0;
    while (x)
    {
        sum += x / num; 
        x /= num; // 每次对 N / p 等价于上述式子
    }
    return sum >= k;
}

signed main()
{
    LL n;
    cin >> n; // 也就是题目中的 k
    p(n); // 分解质因数，略去

    for (auto i : prime) // 枚举质因数
    {
        int num = i.x, k = i.y; // 分别对应 p、α
        int l = 1, r = n;
        while (l + 1 < r) // 二分，注意边界
        {
            int mid = l + r >> 1;
            if (check(mid, num, k))
                r = mid;
            else
                l = mid;
        }
        mx = max(mx, l + 1); // 取最大 N
    }

    cout << mx << endl;

    return 0;
}
```

[完整代码](https://atcoder.jp/contests/abc280/submissions/37002196)。

---

## 作者：Neil_Qian (赞：1)

# [ABC280D] Factorial and Multiple 题解
给定一个整数 $K$，让你求出一个最小的整数 $N$，使得 $K|N!$。其中 $N!=1\times 2\times \dots \times N$。

我们不妨将所得到的 $K$ 和 $N!$ **分解质因数**，设 $K=2^{a1}\times 3^{a2}\times5^{a3}\times \dots$ 和 $N!=2^{b1}\times 3^{b2}\times5^{b3}\times \dots$。由 $K|N!$ 可以得到 $a_i\le b_i$，而 $a_i$ 我们可以通过分解质因数在 $O(\sqrt K)$ 的时间复杂度得到。我们只需要枚举 $N$，每次把枚举到的数分解质因数到每个指数上面，最后看一下所有指数是不是都满足 $a_i\le b_i$。

本题有点卡常，常数太大可能过不去，讲一下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;using ll=long long;const int N=2e6+2;
ll k,cnt[N],f[N],v[N],c,s,x;bool prime[N];
int main(){
	memset(prime,1,sizeof(prime));//把质数先筛出来，给后面分解质因数加速
	for(int i=2;i*i<=2e6;i++)if(prime[i])for(int j=i*i;j<=2e6;j+=i)//这里从i*i开始是因为之前(i-1)*i被i-1筛了，其它同理
		prime[j]=0;
	for(int i=2;i<=2e6;i++)if(prime[i])v[++c]=i;
	scanf("%lld",&k),s=1e6-1,x=k;
	for(ll i=2;i*i<=k;i++)while(k%i==0)k/=i,cnt[i]++;//把K分解质因数
	if(x==k)printf("%lld\n",k),exit(0);//优化：是个质数，只能K!满足
	for(ll i=2;i<=1e6;i++)s-=(cnt[i]==0);
	for(ll i=2,j,l;;i++){
		x=i;
		for(l=1;v[l]*v[l]<=x;l++){//枚举每个质数
			j=v[l];
			if(j*j<=x)while(x%j==0){
				f[j]++,x/=j;//分解质因数
				if(f[j]==cnt[j])s--;//又满足了一个质数
			}
		}
		f[x]++;
		if(f[x]==cnt[x])s--;//同上
		if(s==0){printf("%lld\n",max(i,k));break;}//其它满足了，别忘了还有K这个质数，还要看一看哪个大
	}
	return 0;
}
```

---

## 作者：Escapism (赞：1)

赛后 VP，口胡了个二分问了是对的，然后就来发题解了。

[题目传送门](https://www.luogu.com.cn/problem/AT_abc280_d)

# 题意

给定一个自然数 $K$，求最小的 $n$ 满足 $n!$ 整除 $K$。

# 思路

一种暴力和一种正解。

## 暴力：？pts

直接暴力求 $n!$，然后判断最小的 $n!$ 整除 $K$。

但是显然会 ``TLE``，如果 $K$ 是一个大质数，$n$ 的最小值就是 $K$。

比如说 $K=10^9+7$，$(10^9+7)!$ 都不知道高精能不能用了。

## 正解：二分加勒让德定理

前置知识：勒让德定理

在正数 $n!$ 的质因子标准分解式中，质数 $p$ 的最高指数记作 $L_P(n!)$，则有：

$$L_p(n!) = \sum_{k\geq1}\left[\dfrac{n}{p^k}\right]$$

来自[百度百科](https://baike.baidu.com/item/%E5%8B%92%E8%AE%A9%E5%BE%B7%E5%AE%9A%E7%90%86/4826654)。

---

首先，在阶乘过程中，每个质因数的个数**单调递增**。

因此当 $n$ 大于等于某个值的时候 $n!$ 必然满足条件，但是当 $n$ 小于某个值的时候必然不满足条件，我们就是要找到这个临界值。

这种时候就可以二分查找了。

因为 $n$ 必然小于等于 $K$，所以我们以 $K$ 作为范围作二分。

当 $n!$ 中的所有质因子个数均大于等于 $K$，就说明我们找大了；反之，就是我们找小了。

当二分中的 $l=r$ 时，我们就找到了临界值。

当然，为了速度，检验的时候我们就要使用上面提到的**勒让德定理**。

质因数分解时间复杂度 $O(\sqrt{K})$，二分复杂度比较玄学。

但是能过，跑的还[挺快](https://atcoder.jp/contests/abc280/submissions/37198949)，最慢不到 $20$ ms。

---

另外好像有种解法是基于 ``GCD`` 的，但是我没想到。似乎代码要短小精悍一些。

# 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 1e6 + 5;
ll n,m,q,k,p=1;
ll prime[MAXN],num[MAXN]; //开 int 会炸

void factor(ll x){ //分解质因数
    for(ll i = 2;i * i <= x;i++){ //求出所有小于 x 的平方根的质因子
        if(x % i == 0){
            prime[++q] = i; //求质因子
            while(x % i == 0) num[q]++,x /= i; //求指数
        }
    }
    if(x>1) prime[++q]=x,num[q]++; //在前面的分解完毕后，剩下来的就是个质数
}

bool check(ll x){
    for(ll i = 1;i <= q;i++){ //q 个质因子
        ll pnum = 0,n = x;
        while(n){ //勒让德求最高次
            pnum += n / prime[i];
            n /= prime[i];
        }
        if(pnum < num[i]) return false; //当某个质因子不达标时
    }
    return true; //达标
}

void Solve(){
    cin>>k;
    factor(k);
    ll l = 1,r = k + 2,ans = k;
    while(l <= r){ //二分经典板子
        ll mid = (l + r) >> 1;
        if(check(mid)) ans = mid,r = mid - 1;
        else l = mid + 1;
    }
    cout<<ans;
}

int main(){
    Solve();
    return 0;
}
```

[**彩蛋：让ChatGPT来写这题（非本人创作）**](https://www.luogu.com.cn/blog/xrk2006ac/post-yu-le-rang-ai-ac-shang-zhou-abc-di-d)

---

## 作者：xiaohaoaibiancheng66 (赞：1)

# 题意
给定 $k$，求最小的 $n$，使 $n! \bmod k=0$。
# 思路
$n! \bmod k=0$ 即为”$n!$ 的每个**相同**因数的**数量**都大于 $k$“。

所以就可以得出一个思路：
1. 将 $k$ 质因数分解；
2. 针对每个因子求出最大的 $n$;
3. 将第二步的 $\max$ 输出。

第一步和第三步都很简单，关键是第二步。

因为答案**满足单调性**，故可用**二份答案**。
# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

long long yinshu[100][3];//0:number,1:shuliang,2:jianhuashuliang;

bool check(long long n,long long m,int p)
{
	long long ans=0;
	while(n)
	{
		ans+=n/m;
		n/=m;
	}
	return ans>=p;
}

long long find(int l,int r,int p,int a)
{
//	cout<<l<<' '<<r<<endl;
	if(l==r)return l;
	int m=(l+r)/2;
	if(check(m,p,a))return find(l,m,p,a);
	else return find(m+1,r,p,a);
}

signed main()
{
	int k;
	cin>>k;
	int n=k;
	int j=-1;
	for(int i=2;i*i<=k;i++)
	{
		if(n%i)continue;
	//	cout<<i<<endl;
		yinshu[++j][0]=i;
		int cnt=0;
		while(n%i==0)
		{
			n/=i;
			cnt++;
		}
		yinshu[j][1]=cnt;
	}
	if(n-1)
	{
		yinshu[++j][0]=n;
		yinshu[j][1]=1;
	}
	int ans=0;
	for(int i=0;i<=j;i++)
		ans=max(ans,find(1,k,yinshu[i][0],yinshu[i][1]));
	cout<<ans;
}
```

---

## 作者：Find_Yourself (赞：0)

先给 $k$ 分解质因数，接着二分 $x$ ，判断 $x!$ 是否能包含 $k$ 的所有因子。

而对于 $x!$ 中质因子 $d$ 的个数，可以在 $O(\log x)$ 内计算出来，即：

$$\sum\limits_{i=1}^{\log_d x}\left\lfloor \frac{x}{d^i}\right\rfloor$$

每个因子都算一遍，判断大小即可。

#### code:

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100 + 5;
ll n, tot = 0, a[N], cnt[N];
bool check(ll up) {
	for (int i = 1; i <= tot; ++i) {
		ll num = 0;
		for (ll j = a[i]; j <= up; j *= a[i])  {
			num += up / j;
		}
		if (num < cnt[i]) return false;
	}
	return true;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	ll x = n;
	for (ll i = 2; i <= sqrt(x); ++i) {
		if (x % i == 0) a[++tot] = i;
		while (x % i == 0) {
			cnt[tot]++;
			x /= i;
		}
	}
	if (x != 1) a[++tot] = x, cnt[tot] = 1;
	ll l = 1, r = n, ans;
	while (l <= r) {
		ll mid = (l + r) / 2;
		if (check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：DHeasy (赞：0)

### 修改日志

$2022/12/20\text{ }\text{ }9:22$：修改了时间复杂度。

### 思路

**核心算法：二分**

#### 一：分解质因数

首先，对输入的 $K$，进行分解质因数，若分解后质数 $p$ 有 $l$ 个，则 $sum_p=l$。

**质因数的枚举**

显然不能暴力。

但是，对于一个正整数 $K$，只要 $p$ 枚举到 $\sqrt{K}$ 即可，因为如果 $p\bmod K=0(p\gt \sqrt{K})$，那么 $K\div p$ 一定 $\lt \sqrt{K}$，那这一定会在之前除掉了。

所以以只要在 $[1,\lfloor\sqrt{K}\rfloor]$ 内枚举 $p$ 即可

对于每个 $p$，做如下的事情：

```cpp
while(K2%i==0) K2/=i,sum[i]++;
```
这里的 $i$ 就是 $p$，$K2$ 的初值是 $K$（由于 $K$ 要做边界）。

最后，如果 $K2\gt 1$，则输出 $K2$，结束程序。（因为这个 $K2$ 一定是质数）

**分解质因数代码：**
```cpp
long long K2=k;
for(long long i=2;i<=sqrt(k)+100;i++){
	while(K2%i==0) K2/=i,sum[i]++;
}
if(K2!=1) return !printf("%lld\n",K2);
```
#### 二：二分答案

**Q：为什么能用二分？**  
**A：因为答案满足单调性。**  
**Q：具体点？**  
**A：你自己往下看吧！**

因为如果一个正整数 $a$ 满足 $a$ 的阶乘是 $K$ 的倍数，那么 $a+b$ 的阶乘一定也是 $K$ 的倍数，满足单调性，可以二分。

------------

定义左边界为 $l$，右边界为 $r$，初值：$l=1,r=K+100$（稍微大一点，其实没必要，因为 $K$ 的阶乘一定是 $K$ 的倍数）。

对于每个 $mid$，用 一 的分解质因数的方法输出数组 $sum2$，在将 $sum2_i$ 和 $sum_i$ 作比较，如果有任意一个 $i$ 使得 $sum_i\gt sum2_i$，就将 $l\gets mid$，否则将 $r\gets mid$。

最后输出 $r$ 即可

#### 时间复杂度：$\Theta(\log_2K\times\sqrt{K})$

### 代码（语言：c++，仅供参考，不可抄袭）

```cpp
#include<bits/stdc++.h>
using namespace std;
long long k,sum[1001000],l=1,r;
int main(){
	scanf("%lld",&k);
	long long K2=k;
	for(long long i=2;i<=sqrt(k)+100;i++){
		while(K2%i==0) K2/=i,sum[i]++;
	}
	if(K2!=1) return !printf("%lld\n",K2);
	r=k+100;
	while(l<r-1){
		long long mid=l+r>>1,now=mid;
		bool f=0;
		for(long long i=2;i<=sqrt(k)+100;i++){
			long long p=i,s=0;
			while(p<=mid){
				s+=mid/p;
				p*=i;
			}
			if(sum[i]>s){
				f=1;
				break;
			}
		}
		if(f) l=mid;
		else r=mid;
	}
	return !printf("%lld",r);
}
```


---

## 作者：liujy_ (赞：0)

 #### 题目大意  
 给定一个正整数 $n$，求一个整数 $k$ 使得 $k!$ 是 $n$ 的倍数。
 

 ------------
 考虑什么样的数会满足条件。对于这个整数 $n$ 的每一个质因数 $p_i$，$k!$ 的质因数中 $p_i$ 的个数要大于等于 $n$ 的质因数中 $p_i$ 的个数。  
 我们对于每一个 $p_i$ 寻找一个 $K_i$，使得 $K_i!$ 的质因数中 $p_i$ 的个数要大于等于 $n$ 的质因数中 $p_i$ 的个数。最后的答案显然就是最大的 $K_i$。  
 那么我们现在要解决的问题就是如何寻找 $K_i$。对于一个整数 $x$，$x$ 如果满足条件，那么 $x+1$ 显然也满足条件；$x$ 如果不满足条件，那么 $x+1$ 显然也不会满足条件。那么我们可以二分来找这个 $K_i$。  
 接下来我们要解决的问题就是如何快速求出 $x!$ 的质因数中 $p_i$ 的个数。然后显然 $1 \sim x$ 中每一个 $p_i$ 的倍数会产生一个的贡献，$p_i^2$ 的倍数又会产生一个贡献（这里只算一个不算两个是因为在前面计算 $p_i$ 的倍数的时候已经算过一遍了）。计算 $1 \sim x$ 中整数 $y$ 的倍数的个数可以直接用 $x$ 整除 $y$。  
 下面附上赛时代码。
 ```cpp
#include<iostream>
#include<cstring> 
#include<cstdio>
using namespace std;
long long k,ans;
bool f(long long up,long long s,long long x){
	long long cnt=0,base=x;
	while(x<=up){
		cnt+=up/x;
		if(cnt>=s)return true;
		x*=base;
	}
	return false;
}
long long check(long long s,long long x){
	long long l=1,r=k,p=-1;
	while(l<=r){
		long long mid=(l+r)>>1;
		if(f(mid,s,x))r=mid-1,p=mid;
		else l=mid+1;
	}
	return p;
}
signed main(){
	scanf("%lld",&k);
	long long y=k;
	for(int i=2;i<=y/i;i++)
		if(k%i==0){
			int cnt=0;
			while(y%i==0){
				cnt++;
				y/=i;
			}
			ans=max(ans,check(cnt,i));
		}
	if(y>1)ans=max(ans,check(1,y));
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：c20231020 (赞：0)

### 题目链接

[luogu](https://www.luogu.com.cn/problem/AT_abc280_d)

[atcoder](https://atcoder.jp/contests/abc280/tasks/abc280_d)

### 题目大意

给出一个大于或等于 $2$ 的整数 $K$。

求最小的正整数 $N$，使 $N!$ 是 $K$ 的倍数。

在这里，$N!$ 表示 $N$ 的阶乘。可以证明，在问题的约束下，这样的 $N$ 一定存在。

（我的翻译）

### 思路

（十分长，看到题解区的大佬们简洁的思路我自愧不如）

1. 对 $K$ 进行质因数分解并存下每个质因数的幂次（可能会有一个 $> \sqrt{K}$ 的质因数不会存下来）。

	> 因为 $K \le 10^{12}$，查表得 $K$ 的质因数个数不会超过 $12$。

	1. 若发现 $K$ 是质数，答案就是 $K$。

	2. 否则，答案要么是 $K$ 的最大质因数，要么肯定 $\le \sqrt{K}$。

2. 通过递推分别求出 $M!(1 \le M \le \sqrt{K})$ 的每种质数的幂次。这里可以用试除+前缀和实现。

3. 找到满足上述的质因数数量均大于 $K$ 的质因数数量的最小值 $ans$。可以顺序扫过去，也可以二分。

4. 答案取 $ans$ 与 $K$ 的最大质因数中的最小值。

（考场思路如此，可以发现是真的乱）


#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
ll k,a[20],c[20],cnt,ans,tot[20][2000050];
int main(){
	cin>>k;ll t=k;
	for(ll i=2;i*i<=k;++i){
		if(t%i==0){
			a[++cnt]=i;
			for(;t%i==0;t/=i,++c[cnt]);
		}
	}
	if(t==k){
		cout<<k;
		return;
	}
	int p=2*sqrt(k)+10;//忘了这里为什么开两倍才能过，一倍过不了
	for(int i=1;i<=p;++i){
		for(int j=1;j<=cnt;++j){
			ll tem=i;
			while(tem%a[j]==0)tot[j][i]++,tem/=a[j];
			tot[j][i]+=tot[j][i-1];
		}
	}
	for(int i=1;i<=p;++i){
		int f=1;
		for(int j=1;j<=cnt;++j)if(tot[j][i]<c[j]){
			f=0;
			break;
		}
		if(f){
			ans=i;
			break;
		}
	}
	cout<<max(ans,t);
	return 0;
}
```

---

## 作者：Fire_flame (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc280_d)

## $\mathtt{Solution}$

首先看数据范围 $k\le 10^{12}$，就知道不应该用暴力枚举，想用暴力枚举卡过的同学们就跳过这篇题解吧。

令 $k=p_1^{q_1}\times p_2^{q_2}\times \dots p_n^{q_n}$，其中 $p_1,p_2\dots p_n$ 均为质数。

可以求出每一个最小的 $s_i$ 使得 $s_i!$ 被 $p_i^{q_i}$ 整除，所以显然 $\max\{s_1,s_2,\dots s_n\}$ 就是答案，不然的话至少有一个 $p_i^{q_i}$ 无法被它整除。

如何找到满足的 $s_i$：如果 $q_i=1$，则 $s_i=p_i$。否则暴力枚举直到符合的 $s_i$。

时间复杂度：$O(\sqrt n)$ 左右（如果有更精确的可以私信我），因为最多枚举次数是在 $q_i=2$ 的时候，此时要枚举 $2\times p_i$ 次，极端的话是接近 $\sqrt n$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+5;
int n,cnt;
int a[MAXN],num[MAXN];
int calc(int x,int p){
	if(p==1)return x;
	int k=0;
	for(int i=2;;i++){
		int op=i;
		while(op%x==0){
			k++;
			op/=x;
		}
		if(k>=p)return i;
	}
}
signed main(){
	scanf("%lld",&n);
	for(int i=2;i*i<=n;i++){
		if(n%i==0){
			a[++cnt]=i;
			while(n%i==0)n/=i,num[cnt]++;
		}
	}
	if(n!=1)a[++cnt]=n,num[cnt]++;
	int ans=0;
	for(int i=1;i<=cnt;i++)
		ans=max(ans,calc(a[i],num[i]));
	printf("%lld",ans);
	return 0;
}

```


---

## 作者：Jasper08 (赞：0)

看到这种和倍数有关的题，先将 $K$ 分解质因数。设在算数基本定理下，$K=\prod_{i=1}^m p_i^{r_i}$。那么我们就要找到一个正整数 $N$，使得 $N!$ 中有大于等于 $r_i$ 个质因子 $p_i$。

我们知道，$[1,N]$ 中有 $\lfloor N/p_i\rfloor$ 个能被 $p_i$ 整除的数，有 $\lfloor N/p_i^2\rfloor$ 个能被 $p_i^2$ 整除的数，以此类推，有 $\lfloor N/p_i^k\rfloor$ 个能被 $p_i^k$ 整除的数。所以 $N!$ 中质因子 $p_i$ 的数量即为 $\sum_{k=1} \lfloor N/p_i^k\rfloor$。我们可以用二分找到 $[1,N]$ 中有大于等于 $r_i$ 个质因子 $p_i$ 最小的 $N$，将它们取最大值即可。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

#define int long long

int k, ans = 2;
unordered_map<int, int> primes;

int count(int x, int p) { // 计算 x! 中质因子 p 的数量
    int cnt = 0;
    while (x) {
        cnt += x/p;
        x /= p;
    }
    return cnt;
}

signed main() {
    scanf("%lld", &k);
    for (int i = 2; i <= k/i; ++i) {
        while (k % i == 0) {
            primes[i] ++;
            k /= i;
        }
    }
    if (k > 1) primes[k] ++;

    for (auto P : primes) {
        int p = P.first, t = P.second;
        int l = p, r = pow(p, t);
        while (l < r) {
            int mid = l + r >> 1;
            if (count(mid, p) >= t) r = mid;
            else l = mid+1;
        }
        ans = max(ans, l);
    }
    printf("%lld\n", ans);
    system("pause");
    return 0;
}
```

---

## 作者：loser_seele (赞：0)

题意：给定 $ K $，求最小的 $ N $ 使得 $ K $ 能整除 $ N! $。

分析：无脑二分答案，如果 $ mid! $ 能整除 $ K $ 则缩小 $ r $，否则扩大 $ l $ 即可。

但是暴力判断是否能整除会超时，考虑先对 $ K $ 质因数分解后枚举每个质因子判断是否合法。注意二分的边界为 $ K $，因为 $ K! $ 显然能整除 $ K $，所以最坏情况下要开 long long。

时间复杂度 $ \mathcal{O}(\log{K}^2d(K)) $，其中一个 $ \log $ 来自质因子分解，一个来自二分答案，$ d(K) $ 表示 $ K $ 的质因子个数，当 $ K \leq 10^{12} $ 的时候不会很大，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
typedef long long LL;
#define int long long
#define pb push_back
const int INF = 0x3f3f3f3f;
const int maxn = 1e6+10;
using namespace std;
struct node
{
    int x;
    int num;
}fac[maxn];
int cnt=0;
int judge(int x)
{
    for(int i=1;i<=cnt;i++)
    {
        int t=x;
        int num=0;
        while(t)
        {
            num += t/fac[i].x;
            t /= fac[i].x;
        }
        if(num<fac[i].num) 
  	return 0;
    }
    return 1;
}
signed main()
{
    int T=1;
    while(T--)
    {
        int n;
        scanf("%lld",&n);
        cnt = 0;
        for(int i=2;i*i<=n;i++)
        {
            if(n%i==0)
            {
                fac[++cnt].x = i;
                fac[cnt].num = 0;
                while(n%i==0)
                {
                    fac[cnt].num++;
                    n/=i;
                }
            }
        }
        if(n>1)
        {
            fac[++cnt].x = n;
            fac[cnt].num = 1;
        }
        int L=1,R=1e13;
        int ans=n;
        while(L<=R)
        {
            int mid=(L+R)>>1;
            if(judge(mid))
            {
                R = mid-1;
                ans = mid;
            }
            else 
  		L=mid+1;
        }
        printf("%lld\n",ans);
    }
}
```


---

## 作者：what_else (赞：0)

数学题。

### 题目概要

找出最小的 $N$，使 ${k}\mid {(N!)}$。

数据范围 $k\le10^{12}$。

### $\text{Solution}$

考虑暴力枚举 $N$ 的值。

不要试图去存储任意时刻的 $N!$，因为阶乘容易爆 $\text{long long}$。

发现，对 $k$ 真正有用的实际上是 $\gcd(N,k)$ （ $N$ 为当前枚举到的）。

枚举 $N$ 的过程中，让 $k$ 除以 $\gcd(N,k)$ 的值。

直到 $k$ 为 $1$ 的时候，退出循环，输出结果。

然而 $k$ 过于庞大，此方法会超时。

考虑只让 $N$ 枚举 $2\sqrt{k}$ 次。

如果枚举后 $k$ 还不是 $1$，那显然，$k$ 剩下一个很大的质数，满足 $2\sqrt{k} \le k$。直接输出 $k$ 即可

之所以选择 $2\sqrt{k}$ 而不是 $\sqrt{k}$，是因为有一些特例比如 $32$，枚举 $\sqrt{k}$ 会输出错解，实质是因为小数字幂次，容易漏枚举项。

$\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
long long k;
long long p,z,i,sp;
long long gcd(long long a,long long b){return b==0 ? a : gcd(b,a%b);}
int main(){
	cin>>k;
	sp=k;
	for(i=1;i*i<=sp*4;i++){//sp*4模拟2根号k
		z=gcd(i,k);
		k/=z;
		if(k==1) {cout<<i;break;}
	}
	if(k!=1) cout<<k;
}
```

---

## 作者：郑朝曦zzx (赞：0)

## 题解
很显然，这道题目的时间复杂度是小于 $O(n)$ 级别的，而且和质因数分解有关。

每个质因数是相对独立的，本题的答案就是满足所有质因数条件的最大数，即 $\max\{OK_{p}\}$，$OK_p$ 表示满足质因数 $p$ 个数的最小 $N$。

记 $K$ 的某个质因数 $p$ 的个数为 $cnt$，那么我们枚举 $1\times p$ 至 $cnt\times p$ 中所有 $p$ 的倍数，并记录当前有几个 $p$ 了，如果够了就`break`。

时间复杂度 ： $O(\sqrt{k}+\log(k))$

## 代码
参考了官方题解，官方题解写的挺简洁的。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline LL read()
{
    char c=getchar(); LL x=0LL, s=1;
    while(c<'0'||c>'9') { if(c=='-')s=-1;c=getchar();}
    while(c>='0'&&c<= '9') { x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return x*s;
}
LL ans;
int main()
{
	LL n = read();
	for (LL i = 2; i * i <= n; ++i)
	{
		LL cnt = 0, tmp = 0;
		while (n % i == 0)
		{
			++cnt;
			n /= i;
		}
		while (cnt > 0)
		{
			tmp += i;
			LL x = tmp;
			while (x % i == 0) x /= i, --cnt;	
		}
		ans = max(ans, tmp);
	}
	ans = max(ans, n);
	printf("%lld\n", ans);
    return 0;
}
```


---

## 作者：lfxxx (赞：0)

先求出 $k$ 的所有质因子数量。然后对于每个质因子， $x !$ 所包含的 $y$ 因子数量为 $x / y + x/ {y^2} +...+ x/{y^n}$，且具有单调性，那么对于每一个质因子去二分，再把二分出来的结果取最大值即可。质因子数量为 $O(\log n)$ ，故二分复杂度一共为 $O(\log^2 n)$ 。

代码：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int k;
int ans;
int anser;
bool check(int x,int sum,int op){
    int res=0,d=op;
    while(d<=x){
        res+=x/d;
        d*=op;
    }
    if(res>=sum) return true;
    else return false; 
}
int hhx;
signed main(){
    cin>>k;
    hhx=k;
    if(k==1){
        cout<<1;
        return 0;
    }
    while(k!=1){
        int sum=0;
        for(int i=2;i<=sqrt(k);i++){
            if(k%i==0) {
                sum=i;
                break;
            }
        }
        if(sum==0){
            anser=max(anser,k);
            break;
        }
        int res=0;
        while(k%sum==0){
            k/=sum;
            res++;
        }
        int l=1,r=hhx;
        while(l+1<r){
            int mid=(l+r)/2;
            if(check(mid,res,sum)==true){
                r=mid;
            }
            else
            {
                l=mid;
            }
        }
        anser=max(anser,r);
    }
    cout<<anser;
}

```


---

