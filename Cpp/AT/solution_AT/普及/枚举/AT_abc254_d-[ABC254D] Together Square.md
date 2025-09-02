# [ABC254D] Together Square

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc254/tasks/abc254_d

整数 $ N $ が与えられます。以下の条件を満たす $ N $ 以下の正整数の組 $ (i,j) $ の個数を求めてください。

- $ i\ \times\ j $ は平方数である。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ N $ は整数である。

### Sample Explanation 1

$ (1,1),(1,4),(2,2),(3,3),(4,1),(4,4) $ の $ 6 $ 個が条件を満たします。 $ (2,3) $ は $ 2\ \times\ 3\ =6 $ が平方数でないため条件を満たしません。

## 样例 #1

### 输入

```
4```

### 输出

```
6```

## 样例 #2

### 输入

```
254```

### 输出

```
896```

# 题解

## 作者：_qingshu_ (赞：4)

# 题意：

求满足 $i\times j=k^2$ 且 $1 \le i,j \le n$ 的二元组 $(i,j) $ 的个数。

# 思路：

考虑完全平方数的特点，易证所有完全平方数相同质因子个数一定为偶数。同理，可证所有相同质因子个数为偶数的数一定为完全平方数。根据这个特点我们可以遍历 $i$ 然后分类讨论。

- 当 $i$ 为完全平方数的时候：

    因为其本身一定有偶数个质因子，而我们可以任意寻找 $1 \le j \le n$ 且 $j$ 为完全平方数。所以这种情况对于答案的贡献就是小于 $n$ 的完全平方数的个数。
    
- 当 $i$ 不为完全平方数的时候：
	
    考虑补全 $i$ 中奇数的质因子，而这一部分需要尽可能的小，也就是每一种补充一个到原本为完全平方数的 $j$ 里面。保证更改后的 $j$ 依然满足 $1 \le j \le n$ 且 $j$ 为完全平方数的条件。对答案贡献为满足条件的 $j$ 的个数。  
    
# code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long ans;
int ton[5200010],flag[5200010],tot;
int main(){
	cin>>n;
	for(int i=1;i*i<=n;i++){
		ton[++tot]=i*i;
		flag[i*i]=1;
	}
	for(int i=1;i<=n;i++){
		if(flag[i]){
			ans+=tot;
		}
		else{
			int now=i;
			for(int j=2;j<=tot;j++){
				while(now%ton[j]==0){
					now/=ton[j];
				}
			}
			for(int j=1;j<=tot&&ton[j]*now<=n;j++){
				ans++;
			}
		}
	}
	cout<<ans;
}
```

---

## 作者：Dreamerly (赞：2)

## 题目：[AT_abc254_d](https://www.luogu.com.cn/problem/AT_abc254_d)
## 思路：
看规模，暴力枚举肯定不行，因此需要枚举与数学思维。

**首先**，对于 $i$ 来说，若它本身即使一个平方数，要想让 $i$ $\times$ $j$为完全平方数，则 $j$ 也必须是平方数。

**然后**，对于 $i$ 来说，若它不是平方数，要想让 $i$ $\times$ $j$为完全平方数，则需要用 $j$ 将 $i$ 中质因子为奇数个的数变成偶数个，以此满足完全平方数每种质因子为偶数个的性质。而每个质因子为奇数个的都剔除其中一个后，剩下的就是小于 $i$ 且最接近 $i$ 的完全平方数。

## 总结：
对于二元组 $\left( i,j \right)$ 中的 $i$ 来说。

若它本身就是完全平方数。则 $j$ 可以取 $1$ $-$ $n$ 中的所有完全平方数。

若它本身不是完全平方数。则 $j$ 可以取，小于 $i$ 且最接近 $i$ 的完全平方数，乘以 $i$ 中质因子为奇数个的数。

## 代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){ 
	int num=0,sign=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') sign=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		num=(num<<3)+(num<<1)+(ch^48);
		ch=getchar(); 
	}
	return num*sign;
} 
void write(int x){ 
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}
const int N=2e5+10;
vector<int> ve;
bool vis[N];
int n,ans;
void init(){
	for(int i=1; ;i++){
		if(i*i>n) break;
		vis[i*i]=1;
		ve.push_back(i*i);
	}
	return;
}
signed main(){
	n=read();
	init();
	for(int i=1;i<=n;i++){
		if(vis[i]){ 
			ans+=ve.size();
			continue;
		} 
		int ti=i;
		for(int j=1;j<ve.size();j++){
			while(ti%ve[j]==0) ti/=ve[j];
		}
		for(int j=0;j<ve.size();j++){
			if(ve[j]*ti>n) break;
			ans++;
		}
	}
	write(ans);
	return 0;
} 
```


---

## 作者：yqr123YQR (赞：1)

#### 题意
给定一正整数 $n$，求 $1\sim n$ 中相乘为平方数的二元组个数。
#### 分析
**知周所众**，若一**平方数** $a$ 乘上 $b$ 依然是**平方数**，则 $b$ 也**只能**是**平方数**。

所以，我们在**枚举**题目中的 $i$ 时，可以将 $i$ 中的平方数部分**去掉**，剩下部分记为 $i'$。同样的，对 $j$ 进行**相同操作**，剩余部分记为 $j'$。则 $i\times j$ 为**平方数** $\Longleftrightarrow i'\times j'$ 为**平方数**，即 $i'=j'$。

此时，我们就**只需要**找有多少个**平方数**乘上 $i'$ 后，依然在 $n$ 以内（**包括** $n$）即可。这里，其他题解都是用的**二分**，其实只需要求 $\lfloor\sqrt{\frac{n}{i'}}\rfloor$ 就行。~~虽然二分也很简单，但为什么不用一个函数就搞定一切呢\~~~

证明：设 $x=i'\times (x')^2,x'\in N^*$，则 $1\leqslant (x')^2\leqslant \frac{n}{i'}$，即 $1\leqslant x'\leqslant \lfloor\sqrt{\frac{n}{i'}}\rfloor$。因为 $x'\in N^*$，所以这样的 $x'$ **正好有** $\lfloor\sqrt{\frac{n}{i'}}\rfloor$ 个。

#### 时间复杂度
枚举 $i$ 有 $O(n)$，求 $i'$ 为 $O(\sqrt n)$，求 $x'$ 的个数 $O(1)$，总计 $O(n\sqrt n)$。

#### 代码
```cpp
#include<stdio.h>
#include<math.h>
#define maxn 200000
typedef long long ll;
int n, cnt, prime[maxn + 5];
bool flag[maxn + 5];
ll ans;
int main()
{
	scanf("%d", &n);
	for(int i = 2; i <= n; i++)//欧拉筛，筛出所有质数。当然，不筛质数，直接分解也行
	{
		if(!flag[i]) prime[++cnt] = i;
		for(int j = 1; j <= cnt && prime[j] <= n / i; j++)
		{
			flag[prime[j] * i] = true;
			if(i % prime[j] == 0) break;
		}
	}
	for(int i = 1; i <= n; i++)
	{
		int t = i, mn = 1;//即上文的 i'
		for(int j = 1; j <= cnt && prime[j] <= t; j++)
		{
			int cnt = 0;
			while(t % prime[j] == 0)
			{
				cnt++;
				t /= prime[j];
			}
			if(cnt & 1) mn *= prime[j];//计算 i 中 prime[j] 的个数，只保留个数为奇数的质数
		}
		ans += sqrt(n / mn);//原理上文有讲
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Zikake (赞：0)

# 思路
众所周知，完全平方数的质因子的指数一定为偶数个。所以我们可以将 $ n $ 除以完全平方数，得到的除数如果相等，那么他们的乘积就是完全平方数。

# ACcode
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n,f[N],cnt[N],ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		f[i]=i;
	}
	for(int i=2;i<=n/i;i++){
		for(int j=2;j<=n;j++){
			while(f[j]%(i*i)==0){
				f[j]/=(i*i);	
			}
		}		
	}
	for(int i=1;i<=n;i++){
		cnt[f[i]]++;
	}
	for(int i=1;i<=n;i++){
		ans+=cnt[i]*cnt[i];
	}
	cout<<ans;
	return 0;
}
```



---

## 作者：WaterSun (赞：0)

# 思路

令 $f_i$ 表示 $i$ 最大的完全平方数因子。

那么，现在如果有两个数 $i,j$，要使 $i \times j$ 为完全平方数，一定要使 $\frac{i}{f_i} = \frac{j}{f_j}$。

换句话说，$i \times j$ 为完全平方数，当且仅当 $\frac{i}{f_i} = \frac{j}{f_j}$。因为 $i \times j = f_i \times \frac{i}{f_i} \times f_j \times \frac{j}{f_j}$，且 $f_i,f_j$ 均为完全平方数，所以 $\frac{i}{f_i} \times \frac{j}{f_j}$ 也是完全平方数，所以 $\frac{i}{f_i} = \frac{j}{f_j}$。

由此，统计 $\frac{i}{f_i}$ 的数量即可。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 2e5 + 10;
int n,ans;
int vis[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline int f(int x){
	int res = 0;
	for (re int i = 1;i * i <= x;i++){
		if (x % i == 0){
			int j = x / i;
			int si = sqrt(i);
			int sj = sqrt(j);
			if (si * si == i) res = max(res,i);
			if (sj * sj == j) res = max(res,j);
		}
	}
	return res;
}

signed main(){
	n = read();
	for (re int i = 1;i <= n;i++) vis[i / f(i)]++;
	for (re int i = 1;i <= n;i++) ans += vis[i / f(i)];
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：DengDuck (赞：0)

这道题考虑枚举 $i$，我们设 $i\times k$ 是一个完全平方数且 $k$ 最小。

那么，$j$ 一定是 $k$ 的倍数，否则无法使 $i\times j$ 为完全平方数。

那么在 $i\times k$ 是一个完全平方数的情况下，$j$ 剩下的部分显然也应该是一个完全平方数。

考虑求出 $i$ 对应的 $k$，再求出有多少 $x$ 满足 $x^2k\leq n$。这个是可以二分解决的。

但是求 $k$ 需要质因数分解，所以时间复杂度为 $O(n\sqrt n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std; 
const LL N=3e5;
LL n,b[N],tot[N],cnt,ans;
int main()
{
	scanf("%lld",&n); 
	for(LL i=2;i<=n;i++)
	{
		if(!b[i])
		{
			tot[++cnt]=i;
			for(LL j=2*i;j<=n;j+=i)b[j]=1;
		}
	} 
	for(LL i=1;i<=n;i++)
	{
		LL k=1,t=i;
		for(LL j=1;tot[j]*tot[j]<=t&&j<=cnt;j++)
		{
			if(t%tot[j]==0)
			{
				LL cnt=0;
				while(t%tot[j]==0)t/=tot[j],cnt++;
				if(cnt&1)k*=tot[j];
			}
		}
		k*=t; 
		LL l=1,r=n,len=0;
		while(l<=r)
		{
			LL mid=(l+r)/2;
			if(mid*mid*k<=n)len=mid,l=mid+1;
			else r=mid-1;
		}
		ans+=len;
	}
	printf("%lld",ans);
}
```

---

## 作者：chengning0909 (赞：0)

# abc 254 d

[AT 链接](https://atcoder.jp/contests/abc254/tasks/abc254_d)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc254_d)

## 题意

给定一个正整数 $n$，请你求出有多少个数对满足一下条件：

- $1 \le i, j \le n$。

- $i \times j$ 是一个完全平方数。

$1 \le n \le 2 \times 10 ^ 5$。

## 思路

### 暴力

枚举 $i$ 和 $j$，判断乘积是否为完全平方数。

时间复杂度为 $O(n ^ 2)$。

### 正解

对于每个 $i \ (1 \le i \le n)$，令 $f(i)$ 表示 $i$ 最大的完全平方数因子。

也就是说，如果 $i \times j$ 为完全平方数，就说明 $\frac{i}{f(i)} = \frac{j}{f(j)}$。

因为 $i \times j = f(i) \times f(j) \times \frac{i}{f(i)} \times \frac{j}{f(j)}$，而 $f(i)$ 和 $f(j)$ 都是完全平方数，那么 $\frac{i}{f(i)} \times \frac{j}{f(j)}$ 也必须是完全平方数，也就是 $\frac{i}{f(i)} = \frac{j}{f(j)}$。

所以做法就是，记录所有 $\frac{i}{f(i)}$ 出现的数量，再统计答案。

#### 时间复杂度

如果用埃式筛预处理，那么时间复杂度为 $O(n \times \log n)$。

如果直接循环找 $f(i)$，那么时间复杂度为 $O(n \times \sqrt n)$。

```cpp
// 我的是 O(n * sqrt(n))
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, cnt[N];
long long ans;

int f(int i) {
  int s = 0;
  for (int j = 1; j * j <= i; j++) {
    if (i % j == 0) {
      int k = i / j;
      if (int(sqrt(j)) * int(sqrt(j)) == j) {
        s = max(s, j);
      }
      if (int(sqrt(k)) * int(sqrt(k)) == k) {
        s = max(s, k);
      }
    }
  }
  return s;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cnt[i / f(i)]++;
  }
  for (int i = 1; i <= n; i++) {
    ans += cnt[i / f(i)];
  }
  cout << ans;
  return 0;
}
```

---

## 作者：Tsawke (赞：0)

# [[ABC254D] Together Square](https://www.luogu.com.cn/problem/AT_abc254_d) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC254D)

## 题面

给定 $ n $，求满足以下条件的二元组 $ (i, j) $ 数量：$ 1 \le i, j \le n, i \times j = k^2(k \in \mathbb{N}^*) $。

## Solution

首先有一个较为显然的想法，即埃筛 $ [1, n] $ 每个数的所有因数，然后枚举每个 $ i^2, i \in [1, n] $，将 $ i \times i $ 转化为 $ (i \times t) \times (\dfrac{i}{t}) $，其中 $ t $ 为 $ i $ 的因数，然后如果 $ i \times t \le n $ 那么若 $ t = 1 $ 则 $ ans \leftarrow ans + 1 $，反之 $ ans \leftarrow ans + 2 $。不过很遗憾这个很简单也很好写的思路是假的，不难发现比如 $ 6 \times 6 \Rightarrow 4 \times 9 $，这里的因数是 $ \dfrac{3}{2} $，然后我们忽略了，所以会漏。

考虑正解，有个妙妙转化，即将原式的 $ i, j $ 转化为 $ i = a^2 \times c, j = b^2 \times c $，然后我们钦定 $ i \lt j $，此时计算后对于每个答案都 $ \times 2 $ 可以不漏 $ i \gt j $ 的部分，然后将最后的答案加上 $ n $ 即不漏 $ i = j $ 的部分。

然后考虑处理钦定 $ i \lt j $ 后的答案，不难想到有 $ i \lt j \lt n \Rightarrow a^2 \times c \lt b^2 \times c \lt n \Rightarrow a^2 \lt b^2 \lt \dfrac{n}{c} \Rightarrow a \lt b \lt \sqrt{\dfrac{n}{c}} $。

于是不难发现 $ a, b $ 都是 $ \sqrt{n} $ 级别的，于是枚举 $ a, b $，对于确定的 $ a, b $，则显然有 $ c \in [1, \dfrac{n}{b^2}] $，则此时的答案贡献即为 $ 2 \times \lfloor \dfrac{n}{b^2} \rfloor $。然后发现这个东西还是假的，会重，即对于 $ \gcd(a, b) \neq 1 $ 的 $ c $，显然会被 $ a' = \dfrac{a}{\gcd(a, b)}, b' = \dfrac{b}{\gcd(a, b)} $ 所包含，所以不难想到只要将对答案的贡献转化为 $ 2 \times \lfloor \dfrac{n}{b^2} \rfloor \times [\gcd(a, b) = 1] $ 即可不重不漏地求出答案。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

int N;
ll ans(0);

int main(){
    N = read();
    for(int a = 1; a * a <= N; ++a)
        for(int b = a + 1; b * b <= N; ++b)
            if(__gcd(a, b) == 1)
                ans += 2 * (N / (b * b));
    printf("%lld\n", ans + N);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_12_06 初稿

---

## 作者：ChenYanlin_20 (赞：0)

### 思路
暴力枚举 $O(n^2)$ 复杂度是绝对要超时的。

不难发现，对于每一个平方数，因为是两个相同数的积，它所有的质因子一定是偶数次方。对与每个数，先求出这个数去掉已有平方因数所剩的因数，而两个数想要凑成平方数，必须所剩因数相同才行。

![](https://cdn.luogu.com.cn/upload/image_hosting/fwmjzvb1.png)
列如：图中 $2\div1=2$，$8\div1\div4=2$，$18\div1\div9=2$
则三个数中每两个数是可以凑一个平方数的，根据排列组合算出答案。
### CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int f[N],s[N],ans;
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		f[i]=i;
	}
	for(int i=2;i*i<=n;i++){
		int t=i*i;
		for(int j=t;j<=n;j+=t){
			while(f[j]%t==0)
				f[j]/=t;
		}
	}
	for(int i=1;i<=n;i++){
		s[f[i]]++;
	}
	for(int i=1;i<=n;i++){
		ans+=s[i]*s[i];
	}
	cout<<ans;
```

---

