# Easy Equation

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/q0ae6v6a.png)

（图：某位不愿透露姓名的热心 /ˈfɜri/ 网友）

## 题目描述

定义：
$$f(n)=\sum_{i=1}^n\sum_{j=1}^n[\operatorname{popcount}(i+j)\gcd(i,j)=\max(i,j)]$$
其中 $\operatorname{popcount}(x)$ 是 $x$ 在二进制下 $1$ 的个数，$\gcd(i,j)$ 是 $i,j$ 的最大公约数。

现在给定正整数 $n$，你需要求出 $f(1)\oplus f(2)\oplus\cdots\oplus f(n)$ 的值。其中 $\oplus$ 是按位异或。

## 说明/提示

**本题采用捆绑测试。**

- Subtask 1 (10pts)：$n\le 10$。
- Subtask 2 (10pts)：$n\le 10^3$。
- Subtask 3 (20pts)：$n\le 10^5$。
- Subtask 4 (30pts)：$n\le 10^6$。
- Subtask 5 (30pts)：$n\le 10^7$。

对于全部数据，$1\le n\le 10^7$。

## 样例 #1

### 输入

```
10```

### 输出

```
13```

## 样例 #2

### 输入

```
10000```

### 输出

```
3159```

# 题解

## 作者：jijidawang (赞：5)

首先钦定 $i\le j$ 去掉 $\max(i,j)$ 的限制，之后可以简单转化到原问题，那么需要计算：
$$\sum_{i=1}^n\sum_{j=i}^n[\operatorname{popcount}(i+j)\gcd(i,j)=j]=\sum_{d=1}^n\sum_{i=1}^{\lfloor\frac nd\rfloor}\sum_{j=i}^{\lfloor\frac nd\rfloor}[\operatorname{popcount}(id+jd)=j][i\perp j]$$

（枚举 GCD）

依次枚举互质的 $i,j$ 和 $id+jd$ 即可。容易发现时间复杂度为：
$$\sum_{i=1}^{\log n}\varphi(i)\cdot \dfrac ni=n\sum_{i=1}^{\log n}\dfrac{\varphi(i)}i=O(n\log n)$$
由于常数较小（约为 $\frac6{\pi^2}$），所以可以轻松通过。~~没错，$\sout{n \log n}$ 就是能过 $\sout{10^7}$~~

---

## 作者：CQ_Bab (赞：2)

# 思路
我们考虑化柿子，首先我们可以设 $\gcd(x,y)=d$ 那么我们把 $x=d\times a,y=d\times b$ 然后柿子就变成了 $pc(d\times (a+b))\times d=\max(a,b)\times d$ 然后又变成了 $pc(d\times(a+b))=\max(a,b)$ 那么我们有考虑一下左边这坨柿子的最大值，我们发现最大值能取 $22$ 然后我们枚举的 $a,b$ 都最大是 $22$ 然后我们考虑暴力枚举 $a,b$ 并且要保证 $\gcd(a,b)=1$ 然后我们暴力枚举 $d$ 即可，再看是否合法，如果合法我们发现 $\max(a,b)\times d$ 就为这对值能取到的第一个值，然后我们在用前缀和求出每一个点的准确值即可。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
//#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    while (ch < '0' || ch > '9') {ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
}
int T=1;
int n;
const int N=1e7+10;
int a[N],f[N]; 
int cc[N*2];
vector<int>v[30];
int vis[30][30];
void solve() {
	in(n);
	rep(i,1,n*2) cc[i]=cc[i/2]+(i&1);
	rep(a,1,22) {
		rep(b,a,22) {
			if(__gcd(a,b)==1) {
				if(a==b) v[a].pb(b);
				else v[b].pb(a);
			}
		}
	}
	rep(a,1,22) {
		for(auto b:v[a]) {
			int tt=0;
			rep(k,1,n/max(a,b)) {
				if(cc[(a+b)*k]==max(a,b)) {
					if(a!=b) f[max(a*k,b*k)]+=2;
					else f[a*k]++;
				}
			}
		}
	}
	int res=0;
	rep(i,1,n) f[i]+=f[i-1],res^=f[i];
	print(res);
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```
要卡下常。

---

## 作者：Noiers (赞：2)

## [Easy Equation](https://www.luogu.com.cn/problem/P12388)

## 解析

因为有 $\gcd$ 在式子中，我们容易想到令：

$$
k1\times d=i,k2\times d=j
$$

于是原等式两边同时除以 $d$ 可得：

$$
\operatorname{popcount}((k1+k2)⋅d)=\max(k1,k2)
$$

令 $k1\ge k2$ 可得：

$$
\operatorname{popcount}((k1+k2)\times d)=k1
$$

**注**：$d=\gcd(i,j)$，$k1⊥k2$。

我们可以枚举 $d,k1,k2$，找到满足上式的值，$k1>k2$ 时**贡献两次**，$k1=k2$ 时**贡献一次**。把得到的贡献记在 $f_{k1\times d}$ 上，最后前缀和加异或。（不要枚举 $i,k1,k2$，时间复杂度会多一个 $\log$，~~比赛时我就这么超时的。~~）

**优化**：

1. 预处理 $\operatorname{popcount}(1\sim20000000)$ 的值。
2. 不难发现 $\operatorname{popcount}((k1+k2)\times d)$ 不大于 $\log(2 \times 10^7)$，即 $k1,k2$ 不大于 $25$。

---

[AC](https://www.luogu.com.cn/record/215730471) 记录。

---

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define lowbit(x) (x&(~x+1))

const int N=40,mx=25,N2=1e7+10;

int n;
long long ans;
bool st[N][N];//判断互质的数。
long long sum[N2];//贡献和。
int pop[N2<<1];//二进制下数中1的个数。

int gcd(int a,int b){//最大公因数。
	return b==0?a:gcd(b,a%b);
}

void prework(){
  //预处理二进制下数中1的个数。
	for(int i=1;i<=(N2-10)<<1;i++){
		pop[i]=pop[i-lowbit(i)]+1;
	}
  //预处理互质的数。
	for(int i=1;i<=25;i++){
		for(int j=1;j<=i;j++){
			if(gcd(i,j)==1){
				st[i][j]=true;
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	prework();
  //枚举d，k1，k2。
	for(int d=1;d<=n;d++){
		for(int i=1;i<=min(25,n/d);i++){
			for(int j=1;j<=i;j++){
				if(pop[i*d+j*d]==i && st[i][j]){
					if(i!=j)sum[i*d]+=2;
					else sum[i*d]++;
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		sum[i]+=sum[i-1];//前缀和。
		ans^=sum[i];//异或记入答案。
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：MspAInt (赞：2)

还得是暴力和打表。

钦定 $i>j$，不管那么多了把每个 $f$ 算出来。

简称 $\operatorname{popcount}$ 为 $\operatorname{pop}$。

关键在于怎么对 $i$ 求 $\sum_{j=1}^{i-1}[\operatorname{pop}(j+i)\times\gcd(j,i)=i]$。好吧直接枚举 $\operatorname{pop}$，求出 $\gcd(i,j)=\frac{i}{\operatorname{pop}}$。然后枚举其倍数作为 $j$，直接判定一遍 $i,j$，合法全加上（可以证明不会算重）。

把这一半的贡献做前缀和再乘 $2$，单独再求一下 $i=j$ 的答案就能够得到 $f(i)$。

很明显两层枚举都是 $\log$（$\operatorname{pop}$ 非常小），判定 $i,j$ 又需要 $\gcd$，共 $n\log^3 n$。直接写了交上去只有 70。$10^7$ 怎么过？

首先跑不满。

其次判定时 $\gcd$ 会很大，$\gcd(i,j)=d$ 等价于 $\gcd(\frac{i}{d},\frac{j}{d})=1$，预处理即可。

最后我以前缀和形式计算，所以先跑一遍 $n=5\times10^6$ 的答案，把此时的状态（贡献前缀和、$i=j$ 的答案、总异或值）记录下来。这样当 $n$ 很大的时候复杂度砍一半，过了。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;

const int N=1e7+10;
int n,ans,sum,cnt;
bool h[30][30];

signed main(){
    //freopen("","r",stdin);
    //freopen("","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=26;i++)
        for(int j=1;j<=26;j++)h[i][j]=__gcd(i,j)==1;
    int i=1;
    if(n>=5e6)i=5e6+1,sum=3002196,cnt=23,ans=7956622;
    for(;i<=n;i++){
        cnt+=__builtin_popcount(i+i)==1;
        for(int j=1;(1<<j-1)<=i;j++)if(i%j==0){
            int k=i/j;
            for(int o=k;o<i;o+=k)
                if(h[j][o/k]&&__builtin_popcount(o+i)==j)sum++;
        }
        ans^=(sum<<1)+cnt;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：qwqerty (赞：2)

被异或吓到了。
# 解题思路
若无特殊说明，本题解中的除法均向下取整。

考虑递推，有 $f(n)=f(n-1)+2\times\sum\limits_{i=1}^n [\operatorname{popcount}(i+n)\gcd(i,n)=n]-[\operatorname{popcount(i)}=1]$。$[\operatorname{popcount(i)}=1]$ 是方便计算的，关键在于计算 $\sum\limits_{i=1}^n [\operatorname{popcount}(i+n)\gcd(i,n)=n]$。考虑枚举 $\gcd$，则有 $\sum\limits_{d=2}^{100
} \sum\limits_{i=1}^{\frac{n}{i}} [\operatorname{popcount}((i+n)d)=n\wedge \gcd(i,n)=1]$。预处理所有互质的数，然后模拟即可。
# AC 代码
注意使用 `__builtin_popcount`，否则会被卡常。
```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
int n, res, ans;
vector<int> hz[105];
int cnt[10000005];
signed main() {
	cin >> n;
	for (int i = 1; i <= 100; i++) {
		for (int j = 1; j < i; j++) {
			if (__gcd(i, j) == 1) {
				hz[i].push_back(j);
			}
		}
	}
	for (int i = 1; i <= n; i <<= 1) cnt[i]++;
	for (int i = 2; i <= 100; i++) {
		if (n < i) break;
		for (int j = 1; j <= n / i; j++) {
			for (auto k : hz[i]) {
				if (__builtin_popcount((j * (i + k))) == i) {
					cnt[i * j] += 2;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) res += cnt[i], ans ^= res;
	cout << ans;
	return 0;
}
```

---

## 作者：_H17_ (赞：1)

## 题目分析

这里给出相对暴力的解法的卡常做法，审核员请不要因此打回，除非你可以构造出 HACK 数据。程序可以在任何符合数据范围的数据下在时间限制内跑完就是正确的，无论复杂度如何。

首先注意到该式子 $1\sim n$ 都要求，不妨递推求解。

式子是：$f(n)=f(n-1)+[\operatorname{popcount}(n\times 2)=1]+2\times\sum\limits_{i=1}^{n-1}[\operatorname{popcount}(n+i)\gcd(i,n)=n]=f(n-1)+[\operatorname{popcount}(n)=1]+2\times\sum\limits_{i=1}^{n-1}[\operatorname{popcount}(n+i)\gcd(i,n)=n]$。

前两项显然非常好搞，随便算。考虑第三项怎么处理，显然需要枚举 $n$ 的约数，由于 $\operatorname{popcount}(n+i)$ 比较小，考虑枚举它。暴力枚举满足最大公约数的 $i$，然后判断是否符合枚举的 $\operatorname{popcount}(n+i)$ 的条件。

显然跑不满。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N=1e7+1;
int n,f,ans;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        if(__builtin_popcount(i)==1)
            ++f;
        for(int pop=2,g;pop<=25;pop++){
            if(i%pop)
                continue;
            g=i/pop;
            for(int j=1,val=i+g;j<=pop;j++,val+=g){
                if(gcd(pop,j)==1&&__builtin_popcount(val)==pop)
                    f+=2;
            }
        }
        ans^=f;
    }
    cout<<ans;
    return 0;
}
```

我们使用极限数据测试，发现时间大约 $1.6$ 秒，考虑进行优化。

注意到 $\operatorname{popcount}(n+i)$ 不一定跑得满，考虑尝试调低，发现上界为 $21$ 时答案变了，说明 $22$ 及以上都是正确的。

得到新代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N=1e7+1;
int n,f,ans;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        if(__builtin_popcount(i)==1)
            ++f;
        for(int pop=2,g;pop<=22;pop++){
            if(i%pop)
                continue;
            g=i/pop;
            for(int j=1,val=i+g;j<=pop;j++,val+=g){
                if(gcd(pop,j)==1&&__builtin_popcount(val)==pop)
                    f+=2;
            }
        }
        ans^=f;
    }
    cout<<ans;
    return 0;
}
```

此时大约 $1.4$ 秒，我们发现判断语句中有两个条件，我们显然把后者成立的概率更小，放到前面的话可以增加剪枝，减少 `gcd` 的调用次数。

新代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N=1e7+1;
int n,f,ans;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        if(__builtin_popcount(i)==1)
            ++f;
        for(int pop=2,g;pop<=22;pop++){
            if(i%pop)
                continue;
            g=i/pop;
            for(int j=1,val=i+g;j<=pop;j++,val+=g){
                if(__builtin_popcount(val)==pop&&gcd(pop,j)==1)
                    f+=2;
            }
        }
        ans^=f;
    }
    cout<<ans;
    return 0;
}
```

此时约 $1.1$ 秒，考虑继续优化，不难发现 $\operatorname{popcount}(n+i)$ 刚才减少枚举 $3$ 的优化效果已经很大，不妨继续优化。如果 $i$ 时奇数，直接枚举奇数即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N=1e7+1;
int n,f,ans;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        if(__builtin_popcount(i)==1)
            ++f;
        if(i&1){
            for(int pop=3,g;pop<=21;pop+=2){
                if(i%pop)
                    continue;
                g=i/pop;
                for(int j=1,val=i+g;j<=pop;j++,val+=g){
                    if(__builtin_popcount(val)==pop&&gcd(pop,j)==1)
                        f+=2;
                }
            }
        }
        else{
            for(int pop=2,g;pop<=22;pop++){
                if(i%pop)
                    continue;
                g=i/pop;
                for(int j=1,val=i+g;j<=pop;j++,val+=g){
                    if(__builtin_popcount(val)==pop&&gcd(pop,j)==1)
                        f+=2;
                }
            }
        }
        ans^=f;
    }
    cout<<ans;
    return 0;
}
```

此时大约 $0.97$ 秒，足够通过题目。

跑的是 $n=10^7$，严格的最强数据，所以一定可以通过本题，是正确的解法，其它 $n$ 时间一定不严格更小。

---

## 作者：封禁用户 (赞：1)

# 思路
为了解决这个问题，我们需要计算从$1$到 $n$ 中每个数的模逆元之和，其中模数为 $p$ 的 $k$ 次幂。逆元存在的条件是数必须与 $p$ 互质。由于 $n$ 的范围可以达到 $10^{18}$，直接遍历每个数显然不可行，因此我们需要利用数论中的性质来高效计算。

方法思路
逆元存在条件：只有当数 $i$ 与 $p$ 互质时，$i$ 在模 $p^k$ 下才存在逆元。

欧拉定理：利用欧拉定理可以快速计算逆元，即 $i$ 的逆元为，
$$
    i^{(φ(p^k)-1)} \bmod p^k
$$
其中 $φ$ 是欧拉函数。

模运算性质：对于每个 $i$，如果 $i$ 与 $p$ 互质，我们可以使用快速幂算法计算其逆元。

余数处理：由于模运算的周期性，我们只需处理余数部分，即 $n \bmod {p^k} $ 的部分。
# Code

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int popcount(int x) {
    return __builtin_popcount(x);
}

int main() {
    int n;
    cin >> n;
    vector<int> diff(n + 2, 0);  

    int max_a = static_cast<int>(log2(2 * n)) + 2;
    max_a = min(max_a, n);

    for (int a = 1; a <= max_a; ++a) {
        for (int b = 1; b <= a; ++b) {
            if (__gcd(a, b) != 1) continue;

            int s = a + b;
            int max_d = n / a;
            if (max_d < 1) continue;

            for (int d = 1; d <= max_d; ++d) {
                int x = d * s;
                if (popcount(x) == a) {
                    int m = d * a;  
                    if (m > n) continue;

                    // 根据a和b是否相等决定增加次数
                    if (a == b) {
                        diff[m] += 1; 
                    } else {
                        diff[m] += 2;  
                    }
                }
            }
        }
    }

    // 计算前缀和得到每个f(k)
    vector<int> f(n + 1, 0);
    for (int k = 1; k <= n; ++k) {
        f[k] = f[k - 1] + diff[k];
    }

    // 计算异或和
    int ans = 0;
    for (int k = 1; k <= n; ++k) {
        ans ^= f[k];
    }

    cout << ans << endl;
    return 0;
}
```

---

## 作者：Cosmos_zzx (赞：1)

- `upd:2025/6/26 增加了算贡献的部分。`

## 思路

首先推式子：

$$\sum_{i=1}^{n}\sum_{j=1}^{n}[\texttt{popcount}(i+j)\cdot\gcd(i,j)=\max(i,j)]$$

设 $d=\gcd(i,j)$，那么枚举**互质**的 $i,j$：

$$\sum_{d=1}^{n}\sum_{i=1}^{n/d}\sum_{j=1}^{n/d}[\texttt{popcount}((i+j)\times d)=\max(i,j)]$$

注意，此时是将 $\texttt{popcount}(i+j)\cdot\gcd(i,j)=\max(i,j)$ 的左右两边都乘以了 $d$。

设 $i > j$：

$$\sum_{d=1}^{n}\sum_{i=1}^{n/d}\sum_{j=1}^{n/d}[\texttt{popcount}((i+j)\times d)=i]$$

此时我们可以枚举 $d,i,j$ 便可以得到结果。

我们可以发现当 $i>j$ 时循环可以遍历到 $i,j$，$j,i$ 这两次，便对 $f_{i\times d}$ 造成了 $2$ 点贡献。同样的，当 $i=j$ 时对 $f_{i\times d}$ 造成了 $1$ 点贡献。

## 一些优化

### 关于时间复杂度

可以发现 $\log(10000000)\approx25$，那么 $\texttt{popcount}((i+j)\times d)$ 最大为 $25$，所以 $i\le \texttt{popcount}((i+j)\times d)$，$i,j\le 25$，$i,j$ 只要枚举到 $25$ 就可以啦。

### 更多优化

因为 $\texttt{popcount}$ 的时间复杂度为 $\log(n)$，`for`循环时会炸掉，所以我们要预处理出 $1$ 到 $20000000$ 的 $\texttt{popcount}$。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i,s,t) for(int i=s;i<=t;i++)
using namespace std;
const int N=1e7+114;
int n,f[N];
bool st[30][30];
int pop[10000000<<1];
int lowbit(int x){return (x&-x);}
void init()
{
	for(int i=1;i<=2*(10000000-10);i++)pop[i]=pop[i-lowbit(i)]+1;
	rep(i,1,25)
		rep(j,1,i)
			if(__gcd(i,j)==1)st[i][j]=1;
}
int main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	init();int res=0;
	rep(d,1,n)
		rep(i,1,min(25,n/d))
			rep(j,1,i)
				if(pop[i*d+j*d]==i && st[i][j])
				{
					if(i>j)f[i*d]+=2;
					else f[i*d]++;
				}
	rep(i,1,n)f[i]+=f[i-1],res^=f[i];
	cout<<res;
	return 0;
}
//__builtin_popcount(5)
```

---

