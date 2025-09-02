# [ABC321D] Set Menu

## 题目描述

餐厅里有 $N$ 个主菜和 $M$ 个副菜，第 $i$ 个主菜的价格为 $A_i$，第 $j$ 个副菜的价格是 $B_j$。餐厅现在要推出一些套餐，每个套餐均由一道主菜和一道副菜组成，对于一个由第 $i$ 个主菜和第 $j$ 个副菜组成的套餐，我们定义 $s=A_i+B_j$，那么这个套餐的价格即为 $\min (s,P)$，$P$ 为一个给定的常数。

请你求出所有可能的套餐的价格总和。

------------

## 样例 #1

### 输入

```
2 2 7
3 5
6 1```

### 输出

```
24```

## 样例 #2

### 输入

```
1 3 2
1
1 1 1```

### 输出

```
6```

## 样例 #3

### 输入

```
7 12 25514963
2436426 24979445 61648772 23690081 33933447 76190629 62703497
11047202 71407775 28894325 31963982 22804784 50968417 30302156 82631932 61735902 80895728 23078537 7723857```

### 输出

```
2115597124```

# 题解

## 作者：Mr_Gengar (赞：12)

简单题。

### Description

计算 $\sum_{i=1}^n \sum_{j=1}^m \min\{P, A_i + B_j\}$。

### Solution

我们首先对于每一个 $B_i$，将 $A$ 数组分为两段，第一段为小于等于 $P - B_i$ 的，第二段为大于 $P - B_i$ 的。

对于第一段，由于不会超过 $P$，所以加上该段总和，再加上 $B_i$ 乘上该段的长度的积即可。

对于第二段，由于超过了 $P$，所以加上 $P$ 乘该段长度的积即可。

实现很简单，先将 $A$ 数组进行排序，记录 $A$ 的前缀和数组 $Pre$，再根据每个 $B_i$ 二分查找 $A$ 数组中第一个大于 $P - B_i$ 的值的下标数组 $x$。

最终答案为 $\sum_{i=1}^m(Pre_{x_i - 1} + b_i \times x_i + P \times (n  - x_i + 1))$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int kMaxN = 2e5 + 1;

long long n, m, p, x, sum, a[kMaxN], b[kMaxN], pre[kMaxN];

int main() {
  cin >> n >> m >> p;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> b[i];
  }
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) {
    pre[i] = pre[i - 1] + a[i];
  }
  for (int i = 1; i <= m; i++) {
    x = upper_bound(a + 1, a + n + 1, p - b[i]) - a;
    sum += pre[x - 1] + b[i] * (x - 1) + (n - x + 1) * p;
  }
  cout << sum << "\n";
  return 0;
}
```

---

## 作者：dayz_break404 (赞：4)

赛时傻傻分不清楚 $n$ 和 $m$ 的蒟蒻qwq。。。

题还是很水的。

## 题意描述

给定第一组 $n$ 个数 $a_1,a_2,\dots,a_n$，第二组 $m$ 个数 $b_1,b_2,\dots,b_m$。第一组的数可以任意和第二组的数搭配，对于每一种不同的搭配 $(a_i,b_j)$，对答案的贡献为 $\min(a_i+b_j,p)$，其中 $p$ 是一个已知的常数，求出这个答案。

## 题目分析

观察 $n$ 和 $m$ 的数据范围，很明显 $O(nm)$ 的暴力是过不去的，所以我们希望在线性时间复杂度 $O(n)$ 下求解此题。

稍稍思考得知，对于每一个 $b_j$，它与第一组搭配的结果分为两种：

1. 当 $a_i+b_j \le p$ 时，此时答案为 $a_i+b_j$。
2. 当 $a_i+b_j > p$ 时，此时答案为 $p$。

遍历每个 $b_j$，则我们需要在 $O(1)$ 的时间内计算每个 $b_j$ 对答案的贡献。

很容易想到对两个数组排序，然后遍历 $b_j$，类似于双指针的做法在数组 $a$ 中定义一个指针。

初始指针在 $a_n$ 位置，遍历时不断左移指针。直至指向的数字左侧与 $b_j$ 的和是小于等于 $p$ 的，右侧是大于 $p$ 的，左侧前缀和预处理，右侧直接计算答案即可。

## Code

注意开```long long```。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
#define ll long long
ll r,n,m,a[maxn],b[maxn],p,sum[maxn],ans;
ll h;
int main(){
	scanf("%lld%lld%lld",&n,&m,&p);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	sort(a+1,a+1+n);
	for(int i=1;i<=m;i++){
		scanf("%lld",&b[i]);
	}
	sort(b+1,b+1+m);
	r=n;//指针
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+a[i];//注意是在排序后做前缀和
	}
	for(int i=1;i<=m;i++){
		while(a[r]+b[i]>p&&r>0) r--;
		ans+=sum[r]+b[i]*r+p*(n-r);
	}
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：Dws_t7760 (赞：4)

可以用前缀和和二分解决。

我们首先将数组 $B$ 排序，并记录数组 $B$ 所有元素的前缀和，表示为数组 $qzh$。

遍历所有 $A_i$，如果数组 $B$ 中没有比 $P - A_i$ 大的数，则包含第 $i$ 道主菜的所有菜单的总价格为 $A_i \times M + qzh_M$，否则假设 $B_t$ 为第一个比 $P - A_i$  大的数，则前 $t - 1$ 个菜单的价格均为 $A_i + B_j$，后 $M - t + 1$ 个菜单的价格均为 $P$，所以此时包含第 $i$ 道主菜的菜单的总价格为 $qzh_{t-1} + A_i \times (t - 1) + P \times  (M - t + 1)$。

AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,p,a[222222],b[222222],s,qzh[222222];
long long first_upper(long long x) {
    int l=1,r=m+1,mid;
    while(l<=r){
        mid=(l+r)/2;
        if(b[mid]>=x&&b[mid-1]<x) return mid;
        if(b[mid]>=x) r=mid-1;
        else l=mid+1;
    }
    return 0;
}
int main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>p;
	for(int i=1;i<n+1;i++) cin>>a[i];
	for(int i=1;i<m+1;i++) cin>>b[i];
	sort(b+1,b+m+1);
	for(int i=1;i<m+1;i++) qzh[i]=qzh[i-1]+b[i];
	b[0]=-1145141919810,b[m+1]=1145141919810;
	for(int i=1;i<n+1;i++) {
		int t=first_upper(p-a[i]);
		if(t==0) s+=a[i]*m,s+=qzh[m];
		else {
			s+=p*(m-t+1);
			s+=a[i]*(t-1),s+=qzh[t-1];
		}
	}
	cout<<s;
	return 0;
}
```

---

## 作者：Genius_Star (赞：3)

### 题意：

餐厅里有 $N$ 个主菜和 $M$ 个副菜，第 $i$ 个主菜的价格为 $A_i$，第 $j$ 个副菜的价格是 $B_j$。餐厅现在要推出一些套餐，每个套餐均由一道主菜和一道副菜组成，对于一个由第 $i$ 个主菜和第 $j$ 个副菜组成的套餐，我们定义 $s=A_i+B_j$，那么这个套餐的价格即为 $\min (s,P)$，$P$ 为一个给定的常数。

请你求出所有可能的套餐的价格总和。

### 思路：

暴力直接算复杂度是 $O(n^2)$ 的，肯定过不去，考虑优化。

考虑分贡献计算，可以先将 $A$ 数组和 $B$ 数组从小到大排序。

逐个枚举 $A_i$，如果 $A_i \ge P$，那么这个主菜与所有副菜组合起来的价格肯定都 $\ge P$，同时因为数组是从大到小排序的，所以从 $A_{i \sim n}$ 的所有主菜与任何副菜组合都 $\ge P$，得到的贡献是 $(n-i+1) \times P \times m$。

那么如果 $A_i < P$，则我们可以用二分在 $B$ 数组中找第一个大于 $P-A_i$ 的值，设这个值的位置为 $t$，则对于 $B_{t \sim n}$ 的副菜，搭配出来的价钱肯定 $ \ge P$，得到的贡献为 $P \times (m-t+1)$。

那么对于 $B_{1 \sim (t-1)}$ 的副菜，搭配起来价格是小于 $P$ 的，那么我们可以计算出 $B$ 数组的前缀和，则得到的贡献为 $A_i \times \min(m,t-1)+s_{\min(t-1)}$。

最后我们输出贡献之和即可，时间复杂度为 $O(n \log n)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=200200;
ll read(){
	ll x;
	scanf("%lld",&x);
	return x;
}
void write(ll x){
	printf("%lld",x);
}
ll n,m,p,ans=0;
ll a[N],b[N],s[N];
int main(){
	n=read(),m=read(),p=read();
	for(int i=1;i<=n;i++)
	  a[i]=read();
	for(int i=1;i<=m;i++)
	  b[i]=read();
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	for(int i=1;i<=m;i++)
	  s[i]=s[i-1]+b[i];
	for(int i=1;i<=n;i++){
		if(a[i]>=p){
			ans+=(n-i+1)*p*m;
			break;
		}
		else{
			ll t=upper_bound(b+1,b+m+1,p-a[i])-b;
			ans+=a[i]*min(m,t-1)+s[min(m,t-1)];
			ans+=p*(m-(t-1));
		}
	}
	write(ans);
	return 0;
}
```


---

## 作者：PikachuQAQ (赞：2)

## Description

[Link](https://www.luogu.com.cn/problem/AT_abc321_d)

赛时 D 题。感觉复杂了。

## Solution

我们发现 $O(nm)$ 的求总价非常恶心，我们直接前缀和数组 $b$，对于一个 $a_i$，我们发现其的基础贡献为 $b$ 数组的和加上 $m \times a_i$，这使得我们可以**进行一个前缀和的计算**以省去 $O(m)$ 的求和。

那么对于一个**单调递增**的 $a$ 和 $b$，计算 $a_i$ 的贡献，我们发现它有三种状况：

- 如果 $a_i+b_m \le p$，说明对于这个 $a_i$，他与所有的 $b_j$ 的分别价格的和都一定小于 $p$，因为 $a$，$b$ 均单调递增这使得我们可以直接计算贡献 $\sum^n_{j=1}b+m\times a_i$。

- 又如果 $a_i\ge p$，这使得所有 $a_i+b_j$ 的和都一定大于 $p$，也就是说所有的贡献都超过了 $p$，直接按 $p$ 计算，即 $p\times m$ 的贡献。

- 又如果 $a_i+b_m \ge p$，但是 $a_i \le p$，我们二分出最大的 $b_j$ 使得 $a_i+b_j\le p$，这使得贡献最大。这里又分出了两种情况：

- 如果最大 $b_j$ 使得 $a_i+b_j=p$，则贡献直接为 $p \times m$，因为所有 $a_i+b_j=p$。

- 否则我们分别计算：显然少于 $p$ 的贡献为 $\sum^k_{j=1} b_j+a_i\times k$，其中 $k$ 为最大 $b_j$ 的下标，大于 $p$ 的贡献为 $p \times (m-g)$，也就是把小于 $p$ 的全部排除计算大于等于 $p$ 的个数。

最后将贡献合起来计算即可。

## Code

```cpp
// 2023/9/24 _Pikachu_

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;

const int kMaxN = 2e5 + 7;

ll n, m, p, a[kMaxN], b[kMaxN], l = 1, r, ans, preb[kMaxN];

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
    }
    sort(a + 1, a + n + 1), sort(b + 1, b + m + 1);
    for (int i = 1; i <= m; i++) {
        preb[i] = preb[i - 1] + b[i];
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] + b[m] <= p) {
            ans += preb[m];
            ans += a[i] * m;
        } else {
            if (a[i] >= p) {
                ans += p * m;
            } else {
                int g = lower_bound(b + 1, b + m + 1, p - a[i]) - b - 1;
                if (g != m) {
                    ans += preb[g];
                    ans += a[i] * g, ans += p * (m - g);
                } else {
                    ans += p * m;
                }
            }
        }
    }
    cout << ans << '\n';

    return 0;
}
```

---

## 作者：Airposs (赞：2)

## 题意概括

求：

$$\sum_{i=1}^{n} \sum_{j=1}^{m} \min(a_i+b_j,P)$$

## 解题思路：

直接暴力枚举肯定会 T，考虑优化。

可以发现对于每一个 $a_i$，都有一些值使其加和大于 P，所以我们把 b 数组排下序，二分查找一下第一个加和大于 P 的位置。

对于这个位置及以后的数，其贡献是固定的。而前边的部分，用一个前缀和优化一下就好了。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long M=2e5+10;
long long n,m,p;
long long ans,sum;
long long a[M],b[M],pre[M];
inline long long read(){
	long long x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}

int main(){
	n=read(); m=read(); p=read();
	for(long long i=1;i<=n;i++){
		a[i]=read();
	}
	for(long long i=1;i<=m;i++){
		b[i]=read();
	}
	sort(b+1,b+m+1);
	for(long long i=1;i<=m;i++){
		pre[i]=pre[i-1]+b[i];
	}
	for(long long i=1;i<=n;i++){
		if(a[i]>=p){
			sum+=m*p;
		}
		else {
			long long res=p-a[i];
			long long wei=lower_bound(b+1,b+m+1,res)-b;
			wei--;
			sum+=(m-wei)*p+a[i]*wei+pre[wei];
		}
	}
	cout<<sum<<'\n';
	return 0;
}
```

---

## 作者：hjqhs (赞：1)

将 $a,b$ 两个数组先排序并统计前缀和。然后枚举 $a$ 数组每个值，在 $b$ 数组中二分查找最后一个小于等于 $p-a_i$ 的数的位置，记为 $pos$。$pos$ 之前的数就是小于等于 $p$ 的，之后的数就是大于 $p$ 且需要取 $\min$ 变成 $p$。考虑贡献，$pos$ 之前的贡献为 $a_i \times pos+sumb_{pos}$，$pos$ 之后的贡献为 $(m-pos) \times p$。
```cpp
 rep(i,1,n){
    int pos=upper_bound(b+1,b+1+m,p-a[i])-b-1;
    // cout<<i<<":"<<p-a[i]<<' '<<pos<<'\n';
    ans+=a[i]*pos+sumb[pos],ans+=(m-pos)*p;
  }
```

---

## 作者：无钩七不改名 (赞：1)

二分 + 前缀和。

先对 $b$ 数组进行排序，并计算排序后每个位置对应的前缀和 $qzh_i$。

对于每个 $a_i$，二分查找 $b$ 数组最后一个使得 $a_i+b_j\le p$ 的位置 $j$。那么位置 $1\sim j$ 和 $a_i$ 组合的价格之和便为 $qzh_j+a_i\times j$，位置 $j+1\sim m$ 和 $a_i$ 组合组合的价格之和便为 $(m-j)\times p$。所有结果加起来则可以得到所有组合菜的价格之和。


### 赛时代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=200005;

int n,m,p;
int a[N],b[N];
long long qzh[N];
long long ans;

int read(){
	int f=1,k=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=k*10+c-'0';
		c=getchar();
	}
	return f*k;
}

int main(){
	n=read();m=read();p=read();
	for(int i(1);i<=n;++i)a[i]=read();
	for(int i(1);i<=m;++i)b[i]=read();
	sort(b+1,b+1+m);
	for(int i(1);i<=m;++i)qzh[i]=qzh[i-1]+b[i];
	for(int i(1);i<=n;++i){
		if(a[i]+b[1]>=p)ans+=1ll*m*p;
		else if(a[i]+b[m]<=p)ans+=qzh[m]+1ll*a[i]*m;
		else{
			int l=1,r=m,wz=1;
			while(l<=r){
				int mid=(l+r)>>1;
				if(b[mid]+a[i]<=p)wz=mid,l=mid+1;
				else r=mid-1;
			}
			//cout<<i<<": "<<qwq<<" "<<wz<<'\n';
			ans+=qzh[wz]+1ll*a[i]*wz+1ll*(m-wz)*p;
		}
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：TempestMiku (赞：1)

# [洛谷](https://www.luogu.com.cn/problem/AT_abc321_d)&[Atcoder](https://atcoder.jp/contests/abc321/tasks/abc321_d)

## 题目大意

给定 $n$ 个主菜，$m$ 个副菜，和常数 $P$，求每个主菜和每个副菜组合的价格和与 $P$ 取最小值的总和。

### 形式化题意：

给定 $a$，$b$，求 $\sum_{i=1}^{n} \sum_{j=1}^{m} \min \{a_i+b_j,P\}$。

## 思路

先将 $a$ 和 $b$ 升序排序，然后对于 $a_i$，找到 $b$ 数组中第一个大于等于 $P-a_i$ 的数的下标记为 $pos$，那么 $pos$ 位之前的和 $a_i$ 加起来不超过 $
P$，利用前缀和加 $sum_{pos}+a_i \times pos$ 即可，$pos$ 位之后的和 $a_i$ 加起来超过 $
P$，直接加 $(n-pos)\times P$ 即可。

注意求前缀和需要在排完序之后求，而不是一开始读入的时候求。

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;
namespace Testify{
    inline int read(){
        int f(1),x(0);
        char ch=getchar();
        for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
        for(;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
        return f*x;
    }
    inline void Write(int x){
        if(x>9) Write(x/10);
        putchar(x%10+48);
    }
    inline void write(int x){
        if(x<0) putchar('-'),x=-x;
        Write(x);
        putchar('\n');
    }
}
using namespace Testify;
int n,m,p,Avantgarde=0;
const int N=2e5+5;
int a[N],b[N],sum[N],maxn=-1;
signed main(void){
    n=read(),m=read(),p=read();
    for(register int i=1;i<=n;i++){
        a[i]=read();
    }
    for(register int i=1;i<=m;i++){
        b[i]=read();
        maxn=max(maxn,b[i]);
    }
    stable_sort(a+1,a+n+1);
    stable_sort(b+1,b+m+1);
    for(register int i=1;i<=m;i++){
        sum[i]=sum[i-1]+b[i];
    }
    for(register int i=1;i<=n;i++){
        if(a[i]>=p){
            Avantgarde+=(p*m);
            continue;
        }
        if(a[i]+maxn<=p){
            Avantgarde+=(a[i]*m+sum[m]);
            continue;
        }
        int pos=lower_bound(b+1,b+m+1,p-a[i])-b-1;
        Avantgarde+=(a[i]*pos+sum[pos]+p*(m-pos));
    }
    write(Avantgarde);
    return 0;
}
```


---

## 作者：cjh20090318 (赞：1)

## 题意

给定一个长度为 $N$ 的正整数数列 $A$，和一个长度为 $M$ 的正整数数列 $B$，还有一个正整数 $P$。

你需要求：

$$
\sum\limits^{N}_{i=1}\sum\limits^{M}_{j=1}\min(A_i+B_j,P)
$$

## 分析

~~说实话感觉这题比 C 还要简单。~~

先考虑单个 $A_i$ 能产生的贡献，可以发现当 $B_j \ge P - A_i$ 时产生的贡献只有 $P$。

所以先将 $B$ 数组排序，二分找到第一个 $B_x \ge P - A_i$ 的地方。所以这一部分的所有的答案贡献即为 $(M-x+1)P$。

再考虑 $B_j < P - A_i$ 的这部分情况，很容易发现这一部分的答案就是 $A_i(x-1)+\sum\limits^{x-1}_{i=1}B_i$，可以发现一个前缀和的结构，提前预处理就好了。

时间复杂度 $O(n \log m + m \log m)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<algorithm>
#define MAXN 200002
using namespace std;
typedef long long LL;
int n,m,p;
int a[MAXN],b[MAXN];
LL s[MAXN];//b 的前缀和。
int main(){
	scanf("%d%d%d",&n,&m,&p);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++) scanf("%d",&b[i]);
	sort(b+1,b+m+1);//排序。
	for(int i=1;i<=m;i++) s[i]=s[i-1]+b[i];
	LL ans=0;
	for(int i=1,x;i<=n;i++){
		x=lower_bound(b+1,b+m+1,p-a[i])-b;//找到第一个 b[x]>=p-a[i] 的位置。
		ans+=(LL)a[i]*(x-1)+s[x-1]+(LL)p*(m-x+1);//两部分的贡献加起来即可。
	}
	printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：lrx___ (赞：1)

[题目](https://www.luogu.com.cn/problem/AT_abc321_d)

**题意简述**

有 $N$ 个主菜和 $M$ 个副菜，第 $i$ 个主菜的价格为 $A_i$，第 $j$ 个副菜的价格为 $B_i$。选择一个主菜和一个副菜一共有 $N \times M$ 种方法，其价格为 $\min(A_i+B_j,P)$。求出这 $N \times M$ 种方法的价格总和。

**思路**

直接枚举会超时。我们可以把主菜按价格排序，二分查找第一个小于等于 $P-B_j$ 的位置，这个位置及以前的价格都为 $A_i+B_j$，后面的价格都为 $P$。这样就可以通过了。注意要使用 `long long`。

时间复杂度为 $O(M \log{N})$。

**代码**

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5e5+5;
ll a[N],s[N];
/* a为主菜价格，s为a的前缀和 */
int main(){
	ll n,m,b,i,j,p,ans=0;
	scanf("%lld%lld%lld",&n,&m,&p);
	for(i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	sort(a+1,a+n+1);
	for(i=1;i<=n;i++){
		s[i]=s[i-1]+a[i];
		/* 计算前缀和 */
	}
	for(i=0;i<m;i++){
		scanf("%lld",&b);
		j=upper_bound(a+1,a+n+1,p-b)-a-1;
		/* 二分查找第一个小于等于p-b的数 */
		ans+=s[j]+b*j+(n-j)*p;
		/* 前j个菜的价格为s[j]+b*j，后面n-j个菜的价格为(n-j)*p */
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：xiaomuyun (赞：1)

- [洛谷题目传送门](https://www.luogu.com.cn/problem/AT_abc321_d)
- [AtCoder 题目传送门](https://atcoder.jp/contests/abc321/tasks/abc321_d)

昨晚有事没打，今天早上看了看题，发现挺好玩的，所以写篇题解。

Update：修正了关于时间复杂度的计算错误。

## 思路分析

这篇题解有两种正解做法，复杂度都可过。

### 方法一：时间复杂度 $\mathcal{O}(n\log_2n)$

将 $b$ 数组从小到大排序，然后扫一遍 $a$ 数组，对于扫到的每个 $a_i$，在 $b$ 中二分查找出第一个 $a_i+b_j>p$ 的 $j$。

然后我们就可以发现，对于 $b_1,\dots,b_{j-1}$ 中的每个数与 $a_i$ 的和一定小于等于 $p$，对于 $b_j,\dots,b_m$ 中的每个数与 $a_i$ 的和一定大于 $p$。

所以 $a_i$ 对答案的贡献即为 $\sum\limits_{k=1}^{j-1}(b_k+a_i)+(n-j+1)\times p$。这个式子可以拆成 $\sum\limits_{k=1}^{j-1}b_k+(j-1)\times a_i+(n-j+1)\times p$，用前缀和维护 $\sum\limits_{k=1}^{j-1}b_k$ 可以使复杂度优化到 $\mathcal{O}(n\log_2n)$。其中这个 $\log$ 是二分的复杂度。

### 方法二：时间复杂度 $\mathcal{O}(n\log_2n)$

将两个数组都从小到大排序，然后扫一遍 $a$ 数组，同时维护一个位置 $cur$，初始为 $m$，表示最后一个满足 $a_i+b_j\le p$ 的位置 $j$。

每次扫到一个 $a_i$ 时，因为排序使得 $a_i\ge a_{i-1}$，所以和 $a_i$ 相加小于等于 $p$ 的 $b_j$ 不会比 $a_{i-1}$ 还多。所以维护 $cur$ 非常简单。

$a_i$ 对答案的贡献即为 $\sum\limits_{k-1}^{cur}(b_k+a_i)+(n-cur)\times p$。前缀和优化后算法的时间复杂度为 $\mathcal{O}(n)$。但是因为还有排序，所以复杂度也是 $\mathcal{O}(n\log_2n)$。

## 代码实现

自己感觉讲得不是很明白，看看方法二的代码吧。

```cpp
// Problem: D - Set Menu
// URL: https://atcoder.jp/contests/abc321/tasks/abc321_d
// Start Time: 2023-09-24 09:08:08
// 
// Powered by CP Editor (https://cpeditor.org)

#include<algorithm>
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<queue>
using namespace std;
#define inf 0x3f3f3f3f
#define inff 0x3f3f3f3f3f3f3f3f
#define mod1 998244353
#define mod2 1000000007
#define int long long
const int maxn=2e5+2;
int n,m,p,a[maxn],b[maxn],sum[maxn],res=0;
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>p;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=m;++i) cin>>b[i];
	sort(a+1,a+1+n);sort(b+1,b+1+m);
	for(int i=1;i<=m;++i) sum[i]=sum[i-1]+b[i];
	for(int i=1,cur=m;i<=n;++i){
		while(cur>0&&a[i]+b[cur]>p) --cur;
		res+=sum[cur]+cur*a[i]+(m-cur)*p;
	}
	cout<<res<<'\n';
	return 0;
}
```

---

## 作者：xxr___ (赞：1)

### 思路：
这个题实际上就是求任意两个数两两相加与 $P$ 判断，我们只需要用二分判断第一个大于等于 $P$ 减 $a_i$ 的下标，然后下标后的用 $P$ ，前的用前缀和再加上一个 $a_i$ 乘下标。
### 代码：
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define int long long
signed main() {
    int n, m, p;
    cin>>n>>m>>p;
    vector<int> a(n + 1), b(m + 1), sum(m + 1);
    for (int i=1;i<= n; i++) cin>>a[i];
    for (int i=1;i<= m; i++) cin>>b[i];
    sort(b.begin()+1,b.end());
    for (int i=1;i<=m;i++) {
        sum[i]=sum[i-1]+b[i];
    }
    unsigned long long ans = 0;
    for(int i=1;i<=n;i++){
    	if(a[i]>=p){
    		ans+=p*m;
    		continue;
		}
    	int pos=lower_bound(b.begin()+1,b.end(),p-a[i])-b.begin();
		if(b[m]+a[i]<p){
			ans+=sum[m]+(a[i]*m);
		}
		if(b[m]>=p-a[i])
			ans+=sum[pos-1]+(1ll*a[i]*(pos-1))+1ll*(m-pos+1)*p;
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：No21 (赞：1)

### 题意简述

餐厅里有 $N$ 个主菜和 $M$ 个副菜，第 $i$ 个主菜的价格为 $A_i$，第 $j$ 个主菜的价格是 $B_j$。餐厅现在要推出一些套餐，每个套餐均由一道主菜和一道副菜组成，对于一个由第 $i$ 个主菜和第 $j$ 个副菜组成的套餐，我们定义 $s=A_i+B_j$，那么这个套餐的价格即为 $\min (s,P)$，$P$ 为一个给定的常数。请你求出所有可能的套餐的价格总和。

### 解题分析

考虑 $N$ 和 $M$ 的最大值为 $2 \times 10^5$，所以我们可以枚举 $A_i$（或者枚举 $B_j$ 也可以）。不难发现，我们需要自己手动算的只有 $A_i+B_j<P$ 的部分，因此我们考虑在 $B$ 数组中二分查找 $P-A_i$，$B_j$ 大于 $P-A_i$ 的套餐价格我们全部算作 $P$，因为题目要求的是求和，所以处理 $B_j$ 小于 $P-A_i$ 的套餐我们可以维护前缀和然后求答案，我们设 $ans_i$ 表示所有包含价格为 $A_i$ 的主菜的价格和，$pos$ 表示我们二分出的位置（第一个大于等于 $P-A_i$ 的数的位置），$sum$ 为前缀和数组，那么具体的式子为：

$$ans_i=A_i \times (pos-1)+sum_{pos-1}+P \times (M-pos+1)$$

然后 $O(N)$ 枚举 $A_i$ 即可，总复杂度 $O(N \log M)$。

其实挺好想的，不懂的话看看代码？（但蒟蒻代码很丑）

记得开 long long，~~蒟蒻赛时没开 long long 导致半小时没调出来~~ qwq。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace TO
{
    const int N=2e5+21;
    int n,m,P;
    long long ans;
    int a[N],b[N],sum[N];
    int mian()
    {
        cin>>n>>m>>P;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        for(int i=1;i<=m;i++)
            cin>>b[i];
        sort(a+1,a+1+n);
        sort(b+1,b+1+m);
        for(int i=1;i<=m;i++)
            sum[i]=sum[i-1]+b[i];
        for(int i=1;i<=n;i++)
        {
            int pos=lower_bound(b+1,b+1+m,P-a[i])-b;
            ans+=a[i]*(pos-1)+sum[pos-1];
            ans+=P*(m-pos+1);
        }
        cout<<ans<<'\n';
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    return TO::mian();
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc321_d)

## 思路

如果读入数据后直接双重循环查找，时间复杂度就是 $\mathcal{O}(n^2)$，肯定过不了 $1\le N,M\le 2\times 10^5$ 的数据。这时我们考虑用**二分 $+$ 前缀和**的方法来解决此题，时间复杂度 $\mathcal{O}(n\log n)$，绝对能过。

读入数据后对 $B$ 数组进行从小到大的排序，排序完成后计算它的前缀和方便之后求和。之后遍历 $A$ 数组，对于每个 $A_i\space (1\le i\le N)$，找到 $B$ 数组内**第一个与之相加大于等于 $P$（第一个大于等于 $P-A_i$）的位置** $Q(1\le Q \le M)$。

$B$ 数组内 $Q$ 之前与 $A_i$ 之和都不大于 $P$，计算 $Q$ 及以前所有位置与 $A_i$ 的和；$Q$ 及之后所有位置与 $A_i$ 之和都大于等于 $P$，会**直接舍入到 $P$**，所以直接求出 $P\times (M-Q+1)$ 的值即可。最后把这两个值相加就求出了 $A_i$ 所能凑成的所有餐费。最后输出总和即可。

- 数据可能超出 $32$ 位整型的范围，记得开 long long。

## AC 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define fi first
#define se second
using namespace std;
inline ll read(){//快读。
	ll k=0,flag=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return k*flag;
}
inline void print(ll x){//快写。
    if(x<0){
        putchar('-');
        x=-x;
    }
    ll y=10,len=1;
    while(y<=x){
        y=(y<<1)+(y<<3);
        len++;
    }
    while(len--){
        y/=10;
        putchar(x/y+48);
        x%=y;
    }
}
const int N=2e5+10;
ll n,m,k,a[N],b[N],p[N],ans;
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1;i<=m;++i)b[i]=read();
	sort(b+1,b+1+m);
	for(int i=1;i<=m;++i)p[i]=p[i-1]+b[i];//计算前缀和。
	for(int i=1;i<=n;++i){
		int q=lower_bound(b+1,b+1+m,k-a[i])-b;
		ans+=p[q-1]+a[i]*(q-1)+k*(m-q+1);
	}
	cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/125900049)

---

## 作者：WaterSun (赞：0)

# 思路

首先发现答案与 $a,b$ 的顺序无关，那么我们可以将 $a$ 从小到大排序，$b$ 从大到小排序。

那么我们现在可以用两个指针 $i,j$ 枚举 $a,b$。

在这里 $i$ 表示当前要算 $a_i$ 对答案的贡献，$j$ 表示在 $1 \sim (j - 1)$ 中对答案的贡献都是 $p$。

因为 $a$ 单调不降，$b$ 单调不升，所以在 $i$ 越大时，$j$ 要么不动，要么向后动。

所以，我们不需要对于每一个 $i$，再来枚举一个 $j$。

显然，答案就是（其中 $s_i$ 表示排序后 $\sum_{j = 1}^ib_j$）：

$$
\sum_{i = 1}^n(j - 1) \times p + a_i \times (m - j + 1) + s_m - s_{j - 1}
$$

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 2e5 + 10;
int n,m,p,ans;
int arr[N],brr[N],s[N];

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

signed main(){
	n = read();
	m = read();
	p = read();
	for (re int i = 1;i <= n;i++) arr[i] = read();
	for (re int i = 1;i <= m;i++) brr[i] = read();
	sort(arr + 1,arr + n + 1);
	sort(brr + 1,brr + m + 1,[](const int a,const int b){
		return a > b;
	});
	for (re int i = 1;i <= m;i++) s[i] = s[i - 1] + brr[i];
	int id = 1;
	for (re int i = 1;i <= n;i++){
		while (id <= m && arr[i] + brr[id] >= p) id++;
		ans += (id - 1) * p + arr[i] * (m - id + 1) + s[m] - s[id - 1];
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

**翻译**

给定 $n$ 个数的数列 $a$，$m$ 个数的数列 $b$，与常数 $p$，求 $\displaystyle\sum_{i=1}^n\sum_{j=1}^m\min(a_i+b_j,p)$。

**分析**

这样的题肯定是要排序的，排完之后对于每个 $a$ 的数，找到 $b$ 中一个数，使得这个数加 $a$ 的那个数和为 $p$ 且下标最小，把下标减一。从这个下标往后结果都是 $p$，前面就是 $\displaystyle(\sum_{i=1}^{idx}b_i)+idx\times a_i$，其中 $idx$ 为找到的 $b$ 中的数的下标减一。维护一个 $b$ 的前缀和，然后每次使用 `upper_bound()` 函数即可。设 $n,m$ 统计，复杂度 $O(n\log n)$。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
long long sum[int(2e5+10)],a[int(2e5+10)],b[int(2e5+10)];
int main()
{
	long long n,m,p,ans=0;//不开long long见祖宗
	cin>>n>>m>>p;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	for(int i=1;i<=m;i++) sum[i]=sum[i-1]+b[i];
	for(int i=1;i<=n;i++)
	{
		if(b[1]>p-a[i])//若ai+b1都大于p，直接计算，因为这时候upper_bound会出问题
		{
			ans+=p*m;
			continue; 
		}
		long long pp=upper_bound(b+1,b+m+1,p-a[i])-b-1;//下标-1
		ans+=(m-pp)*p;//后面都是p
		ans+=pp*a[i]+sum[pp];//前面的计算
	}
	cout<<ans;
} 

---

## 作者：szhqwq (赞：0)

## $\tt{Solution}$

考虑二分和前缀和优化。

因为 $a_i$ 和 $b_j$ 组合有两种情况：要么 $a_i + b_j < p$，要么 $a_i + b_j \ge p$。那么我们可以考虑将 $b$ 数组从小到大排序后进行前缀和，得到前缀和数组 $s$。

对于每一个 $a_i$，二分第一个大于等于 $p - a_i$ 的 $b_{j}$，我们令其下标为 $id$，则它对答案的贡献为：$a_i \times (id - 1) + s_{id - 1} + (m - id + 1) \times p$。

[Link](https://atcoder.jp/contests/abc321/submissions/45848308)

---

## 作者：FreedomKing (赞：0)

这场好水啊没打亏死。

### 思路

就是一道纯纯的二分加前缀和水题。

考虑先将序列 $B$ 排序，然后对于每个 $A_i$ 二分出 $B_i$ 中一个点：它的左边的元素与 $A_i$ 搭配都是原价，右边都是价格为 $P$ 元的搭配。得到这个点后一切都好办了，左边的总价就是 $B$ 的某段前缀和加上元素数量乘以 $A_i$，右边的总价就是元素数量乘上 $P$。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int a[N],b[N],f[N],n,m,t,k;
vector<int>e[N];
bool vis[N];
string s;
signed main(){
	cin>>n>>m>>t;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i];
	sort(b+1,b+m+1);
	for(int i=1;i<=m;i++) f[i]=f[i-1]+b[i];
	for(int i=1;i<=n;i++){
		int pos=lower_bound(b+1,b+m+1,t-a[i])-b;
		k+=f[pos-1]+(pos-1)*a[i]+(m-pos+1)*t;
	}
	cout<<k;
	return 0;
}
```

---

## 作者：zhizhi_c (赞：0)

如果我们直接用暴力解决就会 T，想到将 $B$ 数组排序，这样就可以二分查找 
$B$ 数组第一个大于 $P-A_i$ 的元素的位置，时间复杂度为 $O((N+M)\log M)$。

我们也可以再将 $A$ 数组排序，这样$B$ 数组第一个大于 $P-A_i$ 的元素的位置成单调性，可以双指针，时间复杂度为 $O(N\log N+M\log M)$。

### AC code：
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[200005], b[200005];
long long p, ans, sum;

int main() {
	scanf("%d%d%lld", &n, &m, &p);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= m; i++) scanf("%d", b + i), sum += b[i];
	sort(a + 1, a + n + 1);
	sort(b + 1, b + m + 1);
	for (int i = 1, j = m; i <= n; i++) {
		while (j && b[j] > p - a[i]) sum -= b[j--];
		ans += (long long)a[i] * j + sum + p * (m - j);
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：sevenki (赞：0)

## 题意

给定数组 $a$，$b$，长度分别为 $n$，$m$，以及一个数 $p$，求 
$$
\sum_{i=1}^n\sum_{j=1}^m\min(a_i+b_j , p)
$$

## 思路

这道题适合练习差分和双指针。

考虑将数组排序，首先将数组 $b$ 升序排序。

容易发现，对于每一个 $a_i$，数组 $b$ 中都存在一个位置 $pos$，使得对于任意的 $j<pos$，都有 $a_i+b_j \leq p$，对于任意的 $j\geq pos$，都有 $a_i+b_j > p$。

因此我们可以通过**双指针**来解决这道题。

创建两个指针 $pa$、$pb$，分别对应数组 $a$ 和 $b$。

为了使每次都不重新从 $1$ 开始枚举 $pb$，我们也需要对数组 $a$ 进行排序处理。

我们可以将数组 $a$ 进行降序排序，然后枚举 $a_i$，容易发现，后枚举到的 $a_i$ 所对应的 $pos$ 总是大于等于先枚举到的 $a_i$。这样子就可以 $O(n)$ 枚举了。

但是如何计算答案呢？如果一个一个枚举到 $pos$，复杂度会退化到 $O(n^2)$。

对于每个 $j\geq pos$，我们可以直接统计 $p \times (m-pos+1)$。

对于每个 $j<pos$，我们可以先统计 $a_i\times(pos-1)$，然后对于数组 $b$，我们可以新建一个数组，表示数组 $b$ 中每一个数字在答案中被统计的次数，每次只需要将该数组下标为 $1$ 到 $pos-1$ 中的元素各加上 $1$，容易发现，这样的操作，可以使用**差分数组**来高效地完成，每次修改的时间复杂度为 $O(1)$。

这样，在枚举完成后，只需要通过差分数组还原原数组中的各个元素，再进行统计，就可以得到最终的答案了。

## 代码

注意有一些地方需要强转 `long long`。

```cpp
#include <bits/stdc++.h>
#define MAXN 200005
#define ll long long
using namespace std;
int n, m, p, a[MAXN], b[MAXN];
ll cf[MAXN];  //差分数组
ll ans;
bool cmp(int aa, int bb) { return aa > bb; }
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cin >> n >> m >> p;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= m; i++) cin >> b[i];
  sort(a + 1, a + n + 1, cmp);
  sort(b + 1, b + m + 1);
  int pa = 1, pb = 1;
  for (; pa <= n; pa++) {
    while (a[pa] + b[pb] <= p && pb <= m) {
      pb++;
    }
    cf[1]++, cf[pb]--;
    ans += 1ll * (pb - 1) * a[pa];
    ans += 1ll * (m - pb + 1) * p;
  }
  ll tmp = 0;
  for (int i = 1; i <= m; i++) {
    tmp += cf[i];
    ans += tmp * b[i];
  }
  cout << ans;
  return 0;
}
```



---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc321_d)
### 题意
略。
### 题解
不难想到 $a,b$ 菜单排好序后，对于每一个 $a_i$，必定有一个 $j$ 满足 $a_i+b_j\leqslant p$ 且 $j$ 最大。对于 $a_i+b_1>p$ 的情况，$j$ 不存在，此时为了方便可以令 $j=0$。

然后 $(i,1),(i,2)\dots(i,j)$ 的答案和为 $a_i\times j+b_1+b_2+\cdots+b_j$，$(i,j+1),(i,j+2),\dots(i,m)$ 的答案和为 $p \times (m-j)$。

求和部分搞个前缀和优化就行。

然后就做完了。
### 代码
```cpp
#include <bits/stdc++.h>
#define x first
#define y second
#define pb push_back
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,-1,0,0},dy[] = {0,0,1,-1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = cin.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = cin.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = cin.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
const int N = 200010;
int n,m,p;
int a[N],b[N];
LL sa[N],sb[N];
int main () {
	cin >> n >> m >> p;
	for (int i = 1;i <= n;i++) cin >> a[i];
	sort (a + 1,a + n + 1);
	for (int i = 1;i <= n;i++) sa[i] = sa[i - 1] + a[i];
	for (int i = 1;i <= m;i++) cin >> b[i];
	sort (b + 1,b + m + 1);
	for (int i = 1;i <= m;i++) sb[i] = sb[i - 1] + b[i];
	LL ans = 0;
	for (int i = 1;i <= n;i++) {
		int l = 1,r = m;
		while (l < r) {
			int mid = l + r + 1 >> 1;
			if (a[i] + b[mid] <= p) l = mid;
			else r = mid - 1;
		}
		if (a[i] + b[l] > p) ans += (LL)m * p;
		else ans += (LL)a[i] * l + sb[l] + (LL)(m - l) * p;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：CommunismFighter (赞：0)

我们不需要考虑每个 $a_{i}+b_{j}$ 具体的值，只需要找出对于 $a_{i}$，有多少个 $b_{j}$ 与其相加使得 $a_{i}+b_{j} \le p$，以及有多少个 $b_{j}$ 使得 $a_{i}+b_{j} > p$。

可以建一个下标代表权值的树状数组，维护权值 $b_{j} \le w$ 的个数即可。再将 $b$ 数组排序并维护前缀和，这样一来对于每一个 $a_{i}$ 查询 $b_{j} \le p-a_{i}$ 的个数 $num$，产生的贡献就是  $a_{i} \times num+sum[num]$，$p$ 产生的贡献即为 $p \times (m-num)$。


```cpp
#include<bits/stdc++.h>
#define int long long
#define mian main
#define rg register int
using namespace std;
const int N = 1e7+5,M = 2e8+1e7+5,inf = 1e18;
inline int read(){
	char c=getchar();
    int x=0,f=1;
    while(c<48)<%if(c=='-')f=-1;c=getchar();%>
    while(c>47)x=(x*10)+(c^48),c=getchar();
    return x*f;
}
int n,m,p,a[N],b[N],c[M],ans,lim,sum[N];
inline int lb(int x){return x&(-x);}
inline void ad(int x,int y){for(;x<=p;x+=lb(x)) c[x] += y;}
inline int query(int x){
	int res = 0;
	for(;x;x-=lb(x)) res += c[x];
	return res;
}
signed mian(){
	n = read(),m = read(),p = read();
	for(rg i=1;i<=n;++i) a[i] = read();
	for(rg i=1;i<=m;++i) b[i] = read();
	sort(b+1,b+1+m);
	for(rg i=1;i<=m;++i){
		ad(b[i],1);
		sum[i] = sum[i-1]+b[i];
	}
	int ps;
	for(rg i=1;i<=n;++i){
		ps = query(max(p-a[i],0ll));
		ans += ps*a[i]+sum[ps];
		ans += p*(m-ps);
	}
	printf("%lld\n",ans);
	return 0;
} 
```

---

## 作者：uid_647775 (赞：0)

### 题意
有 $n$ 种主菜，第 $i$ 种价格为 $A_i$ ，有 $m$ 种配菜，第 $j$ 种价格为 $B_j$ ，任意主菜和任意配菜组成一个套餐，套餐价格为主菜和配菜价格之和与 $p$ 的最小值，求 $nm$ 种套餐价格之和。
### 思路
先给 $B$ 排序，计算 $B$ 前缀和储存在 $F$。  
之后枚举 $A_i$，二分计算最大的 $k$ ， 使得 $B_k$ 小于等于 $p-A_i$。  
那么 $A_i$ 与 $m$ 个 $B_j$ 组成的套餐价格之和就是 $A_im+F_k+(m-k)(p-A_i)$ 。   
时间复杂度 $O(n \log m)$ 。
### Code
```cpp
#include<stdio.h>
#include<algorithm>
typedef long long ll;
int n,m,p,A[200005],B[200005];
ll F[200005]; //前缀和
int get(int x) { //二分寻找临界值
	int l=0,r=m,res=0;
	while(l<=r) {
		int mid=(l+r)/2;
		if(B[mid]<=x) {
			l=mid+1;
			res=mid;
		} else {
			r=mid-1;
		}
	}
	return res;
}
int main() {
	scanf("%d%d%d",&n,&m,&p);
	for(int i=1;i<=n;i++) 
		scanf("%d",&A[i]);
	for(int i=1;i<=m;i++)
		scanf("%d",&B[i]);
	std::sort(B+1,B+1+m);
	for(int i=1;i<=m;i++)
		F[i]=F[i-1]+B[i];
	ll res=0;
	for(int i=1;i<=n;i++) { //枚举 A
		if(A[i]>=p) { //若 Ai >= p ，不必寻找
			res+=1ll*p*m;
		} else {
			res+=1ll*A[i]*m;
			int k=get(p-A[i]);
			res+=F[k]+1ll*(p-A[i])*(m-k);
		}
	}
	printf("%lld",res);
	return 0;
}
```

---

## 作者：joe_zxq (赞：0)

# 思路

将 $A$ 数组和 $B$ 数组从小到大排序。遍历 $A$ 数组，二分出满足 $A_i+B_j \ge P$ 的最小的 $j$，其中 $i$ 指当前遍历 $A$ 数组所到的下标。

那么 $B$ 数组大于等于 $P$ 的部分直接按 $P$ 来算，其余的部分预处理出一个前缀和再计算即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200023],b[200023],pre[200023];
int main(){
	long long n,m,p,ans=0; cin>>n>>m>>p;
	for(long long i=0;i<n;i++)cin>>a[i];
	for(long long i=0;i<m;i++){
		cin>>b[i];
	}
	sort(a,a+n);
	sort(b,b+m);
	for(long long i=0;i<m;i++){
		if(i>=1){
			pre[i]+=pre[i-1]+b[i];
		}else{
			pre[i]=b[i];
		}
	}
	for(long long i=0;i<n;i++){
        long long id=upper_bound(b,b+m,p-a[i])-b;
		long long cnt=m-id;
		ans+=p*cnt;
		ans+=pre[id-1]+a[i]*id;
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：_7Mr (赞：0)

# 翻译
一家会员制餐厅有 $N$ 道主菜和 $M$ 道配菜。第 $i$ 种主菜的价格是 $A_i$，第 $j$ 种配菜的价格是 $B_j$。食堂正在考虑推出新的套餐菜单。套餐包括一道主菜和一道配菜。设主菜和配菜的价格之和为 $s$，则该套餐的价格为      $\min(s,P)$。这里，$P$ 是输入中给定的常数。

选择套餐主菜和配菜的方法有 $N \times M$ 种，求所有这些套餐的总价。
# 思路
拿到这种题目，我们先把他有序化，排序以后，模拟几个样例便可发现，对于每一道主菜我们可以分为两种情况计算他与所有配菜的价格。如果当前配菜加上主菜小于 $P$ 我们就直接用他这个价格，如果不是就用 $P$。这时我们很容易想到，我们可以二分答案这个配菜，那么二分出来的这个配菜就以它为界限，左边的是不用 $P$，右边包括他自己就用 $P$。那么这个时候，我们就还有最后一个问题，如何计算不是 $P$ 的价钱，我们可以用前缀和优化，这样就可以通过此题了。
# ACcode
```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
#define INF INT_MAX
using namespace std;
const int maxn=2e5+5;
int n,m,p,sum,ans;
int a[maxn],b[maxn],qzh[maxn];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n>>m>>p;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i];
	sort(a+1,a+1+n);sort(b+1,b+1+m);//有序化
	for(int i=1;i<=m;i++) qzh[i]=qzh[i-1]+b[i];//前缀和优化
	for(int i=1;i<=n;i++){
		int l=1,r=m;
		while(l<=r){//二分答案
			int mid=(l+r)/2;
			if(a[i]+b[mid]<p) l=mid+1;
			else r=mid-1;
		}
		ans+=(a[i]*(l-1)+qzh[l-1]+(m-l+1)*p);//计算贡献
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：Hanzelic (赞：0)

## [题目链接](https://www.luogu.com.cn/problem/AT_abc321_d)
这道题我们发现这道题具有单调性，也就是如果 $a_i+b_j$ 大于 $p$ 的话，对于任意 $k>j$，都有 $a_i+b_k>p$。  

因此我们可以将 $a$ 数组和 $b$ 数组排序，再通过二分找到 $a$ 和 $b$ 的和大于等于的位置，最后计算即可。
   
对于 $a_i+b_j<p$ 的情况，我们通过前缀和优化就行了，时间复杂度 $O(n \log{n})$，可以通过。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define M 200005
int n,m,c,k,last,ans;
int a[M],b[M],sum[M];
signed main(){
    cin>>n>>m>>k;
    for(int q=1;q<=n;q++){
        scanf("%d",&a[q]);
    }
    for(int q=1;q<=m;q++){
        scanf("%d",&b[q]);
    }
    sort(a+1,a+n+1);
    sort(b+1,b+m+1);
    for(int q=1;q<=m;q++){
        sum[q]=sum[q-1]+b[q];
    }
    for(int q=1;q<=n;q++){
        int op=lower_bound(b+1,b+m+1,k-a[q])-b;
        ans+=sum[op-1]+a[q]*(op-1)+(m-op+1)*k;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

