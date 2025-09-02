# [ARC161B] Exactly Three Bits

## 题目描述

对于一个正整数 $X$，定义 $f(X)$ 为 $X$ 在二进制表示下 $1$ 的个数，比如，因为 $6=110_{(2)}$，$11=1101_{(2)}$，$16=10000_{(2)}$，所以 $f(6)=2$，$f(11)=3$，$f(16)=1$。

现在给定你一个正整数 $N$，问是否存在一个小于等于 $N$ 的正整数 $X$，满足 $f(X)=3$。如果存在，请输出满足条件的最大的 $X$，否则输出 `-1`。

本题有多组数据。

## 样例 #1

### 输入

```
4
16
161
4
1000000000000000000```

### 输出

```
14
161
-1
936748722493063168```

# 题解

## 作者：Su777 (赞：4)

# AT_arc161_b 题解

[洛谷题目传送门](https://www.luogu.com.cn/problem/AT_arc161_b)

[Atcoder 题目传送门](https://atcoder.jp/contests/arc161/tasks/arc161_b)

## 题意

给定 $T$ 个数，对于每个数，求出小于等于它的最大的二进制中有三个一的数。如果没有则输出 `-1`。

## 思路

因为 $n \leq 10^{18}$，所以二进制表达不会超过 $60$ 位。又因为只需要三位是 $1$，所以会有 $C_{60}^3=34220$ 个符合要求的数。通过 `for` 循环求出这些数后排序。对于每个数二分查找，使用 `upper_bound` 再 `--`，求到数组中第一个小于等于它的数即可。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long lint;

vector<lint> arr;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);    
    lint T;
    cin >> T;
    for (lint i = 0; i < 60; i ++) {
        for (lint j = i + 1; j < 60; j ++) {
            for (lint k = j + 1; k < 60; k ++) {
                lint value = (1ll << i) + (1ll << j) + (1ll << k);
                arr.push_back(value);
            }
        }
    }
    sort(arr.begin(), arr.end()); // 要用二分查找必须排序！
    while (T--) {
        lint n;
        cin >> n;
        if (n < 7) {
            cout << "-1\n"; // 明显没有答案
            continue;
        }
        cout << *prev(upper_bound(arr.begin(), arr.end(), n)) << endl;
    }
    return 0;
}
```



---

## 作者：良心WA题人 (赞：2)

## 题意

给定一个数 $n$，问小于等于这个数的所有数中最大的一个二进制下 $1$ 的个数为 $3$ 的数。

## 思路

容易知道若 $n\le6$ 则无解。

首先，若 $n$ 的二进制表示下有大于等于 $3$ 个 $1$，则一定是删除低位多余的 $1$ 变为 $0$ 最大。证明是平凡的，因为如果去掉当前的 $1$ 在别的位增加了 $1$ 则要么会大于原来的数，要么不如不去掉当前的 $1$。

那么小于 $3$ 个呢？首先，若有一个非最高位的 $1$ 的位置使得后面可以填两个 $1$，那么就删去这个 $1$ 并将其后面连续的两个位置填上 $1$。若不存在，则删去最高位的 $1$ 在后面填上三个 $1$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		ll n;
		scanf("%lld",&n);
		if(n<7)
		{
			puts("-1");
			continue;
		}
		int cnt=0,a[104],m=0;
		ll x=n;
		while(x)
		{
			if(x&1)
				cnt++;
			a[m++]=x%2;
			x/=2;
		}
		if(cnt>=3)
		{
			int t=0;
			ll ans=0;
			for(int i=m-1;~i;i--)
				if(t<3&&a[i])
				{
					ans+=1ll<<i;
					t++;
				}
			printf("%lld\n",ans);
		}
		else
		{
			bool flag=false;
			for(int i=m-2;i>=2;i--)
				flag|=a[i];
			if(!flag)
			{
				int t=0;
				ll ans=0;
				for(int i=m-2;~i;i--)
					if(t<3)
					{
						ans+=1ll<<i;
						t++;
					}
				printf("%lld\n",ans);
			}
			else
			{
				int t=1;
				bool flag=false;
				ll ans=1ll<<m-1;
				for(int i=m-2;~i;i--)
				{
					if(flag&&t<3)
					{
						ans+=1ll<<i;
						t++;
					}
					else
						flag|=a[i];
				}
				printf("%lld\n",ans);
			}
		}
	}
	return 0;
}
```

---

## 作者：FreedomKing (赞：2)

### 思路

大力分讨。

首先，不难得出当 $n\le 6$ 时是无法给出答案的。

考虑使用 STL 容器 `bitset`，将 $n$ 直接扔进去转为二进制，暂且将其存为 $f$，并统计 $f$ 中 $1$ 的个数 $k$，然后开始分类讨论：

- 若 $k=3$，则 $n$ 必然是 $\le n$ 中的最优解，读者自证不难。

- 若 $k>3$，舍去 $f$ 中二进制低位的 $1$，可以证明这样得出的解是最优的。具体为反复遍历将 $f$ 低位的 $1$ 转为 $0$，直至 $k=3$。可以使用 `f.to_ullong()` 把 $f$ 转为十进制输出。

- 若 $k<3$，考虑多次将 $f-1$，使得 $k\geq 3$，可以证明最多 $4$ 次便可成立。然后重复一边前面的操作即可。

------------

### AC Code
```
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int N=1e6+5;
int a[N],n,m,t,k;
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		if(n<=6){
			cout<<"-1\n";
			continue;
		}
		bitset<64>f(n);
		k=0;
		for(int i=0;i<f.size();i++) if(f[i]==1) k++;
		if(k==3) cout<<n<<'\n';
		if(k>3){
			int x=0;
			while(k>3){
				if(f[x]==1){
					k--;
					f[x]=0;
				}
				x++;
			}
			cout<<f.to_ullong()<<'\n';
		}
		if(k<3){
			int x=0;
			while(f[x]==0){
				f[x]=1;
				x++;
			}
			f[x]=0;
			k=0;
			for(int i=0;i<f.size();i++) if(f[i]==1) k++;
			if(k<3){
				int x=0;
				while(f[x]==0){
					f[x]=1;
					x++;
				}
				f[x]=0;
				k=0;
				for(int i=0;i<f.size();i++) if(f[i]==1) k++;
				if(k<3){
					int x=0;
					while(f[x]==0){
						f[x]=1;
						x++;
					}
					f[x]=0;
					k=0;
					for(int i=0;i<f.size();i++) if(f[i]==1) k++;
					if(k<3){
						int x=0;
						while(f[x]==0){
							f[x]=1;
							x++;
						}
						f[x]=0;
						k=0;
						for(int i=0;i<f.size();i++) if(f[i]==1) k++;
					}
				}
			}
			x=0;
			while(k>3){
				if(f[x]==1){
					k--;
					f[x]=0;
				}
				x++;
			}
			cout<<f.to_ullong()<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：XYTZ (赞：1)

## 题目思路

由于此题是多组样例测试且 $T(1\le T\le 10^5)$，所以只能考虑 $O(T)$ 到 $O(T \log n)$ 的方法。

显然，此题并没有较为简单的 $O(T)$ 方法，只能考虑 $O(T \log n)$ 的方法。

先看看 10 分的暴力代码:

```cpp
#include<bits/stdc++.h>
#define INF 62
using namespace std;
long long num[100],a[300000];
int main()
{
	num[0]=1;for(long long i=1;i<INF;i++)num[i]=num[i-1]*2;
	long long t;
	cin>>t;
	while(t--)
	{
		long long n;
		cin>>n;
		long long x=1;
		for(long long i=0;i<INF;i++)
		{
			for(long long j=i+1;j<INF;j++)
			{
				for(long long k=j+1;k<INF;k++)
				{
					long long sum=num[i]+num[j]+num[k];
					if(sum<=n){a[x]=sum;x++;}
				}
			}
		}
		if(x==1)cout<<-1<<endl; 
		else{sort(a+1,a+x);cout<<a[x-1]<<endl;}
	}
}
```
显然，这个算法的复杂度过大。

那么，怎么优化呢？

### 优化

预处理，及枚举全部可能。

由于这道题是多组样例测试，所以可以将三循环枚举放到外面，并 $O(nT)$ 找到答案。

但这任然不是最优的，我们可以先对预处理内容排序后再使用二分找答案，复杂度 $O(T \log n)$。
## 代码
```cpp
#include<bits/stdc++.h>
#define INF 62
using namespace std;
long long num[100],a[300000];
int main()
{
	long long x=1;
	num[0]=1;for(long long i=1;i<INF;i++)num[i]=num[i-1]*2;
	for(long long i=0;i<INF;i++)
	{
		for(long long j=i+1;j<INF;j++)
		{
			for(long long k=j+1;k<INF;k++)
			{
				a[x]=num[i]+num[j]+num[k];
				x++;
			}
		}
	}
	sort(a+1,a+x);
	long long t;
	scanf("%lld",&t); 
	while(t--)
	{
		long long n;
		scanf("%lld",&n);
		long long k=upper_bound(a+1,a+x,n)-a-1;
		if(a[k]==0)
		{
			cout<<-1<<endl;
			continue;
		}
		cout<<a[k]<<endl;
	}
}
```

---

## 作者：escapist404 (赞：0)

# [ARC161B] Exactly Three Bits 题解

## 题目描述

对于一个正整数 $X$，定义 $f(X)$ 为 $X$ 在二进制表示下 $1$ 的个数，比如，因为 $6=110_{(2)}$，$11=1101_{(2)}$，$16=10000_{(2)}$，所以 $f(6)=2$，$f(11)=3$，$f(16)=1$。

现在给定你一个正整数 $N$，问是否存在一个小于等于 $N$ 的正整数 $X$，满足 $f(X)=3$。如果存在，请输出满足条件的最大的 $X$，否则输出 `-1`。

本题有多组数据。

## 题解

首先 $n < 7$ 的必定无解，$7$ 为使得 $f(X) = 3$ 的最小值。

由 $1 \le N \le {10}^{18} < 2^{60}$，所有 $f(X) = 3$ 的 $X$ 的二进制表示，等价于在 $60$ 个 $0$ 中选 $3$ 个变为 $1$，一共有大约 $C_{60}^3 = 34,220$ 种，很少。

预处理出这些数装进 `set` 里，每次 `lower_bound` 求即可。复杂度 $O(C \log C + T \log C)$，$C \approx C_{60}^3$。

```cpp
#include <bits/stdc++.h>
using namespace std;
set <unsigned long long, greater <unsigned long long>> table;
int main()  {
    long long n, t;
    cin >> t;
    for(int i = 1; i <= 64; ++i)    {
        for(int j = i + 1; j <= 64; ++j)    {
            for(int k = j + 1; k <= 64; ++k)    {
                table.insert(((unsigned long long)1ll << i) + ((unsigned long long)1ll << j) + ((unsigned long long)1ll << k));
            }
        }
    }
    while(t--)  {
        cin >> n;
        if(n < 7)   {
            cout << -1 << endl;
            continue;
        }
        cout << *table.lower_bound(n) << endl;
    }
    return 0;
}
```

---

## 作者：aeiouaoeiu (赞：0)

发现满足 $f(x)=3$ 的 $x$ 只有 $C_r^3$ 个，其中 $r$ 为最大的满足 $2^r\le10^{18}$ 的正整数，发现 $r=60$ 而 $C_{60}^3=34220$ 较小，于是我们可以考虑用 set 存下所有满足 $f(x)=3$ 的 $x$，对于每个询问进行二分查找即可（记得特判 $n<7$）。
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long ll;
const ll inf=0x3f;
ll n;
set<ll> s;
void init(ll bit,ll sum,ll lay){
	if(lay>60) return;
	if(bit==3) s.insert(-sum);
	else init(bit+1,sum+(1ll<<lay),lay+1);
	init(bit,sum,lay+1);
}
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	ll T=1;
	cin>>T;
	init(0,0,0);
	for(int tcs=1;tcs<=T;tcs++){
		cin>>n;
		if(n<7){
			cout<<"-1\n";
			continue;
		}
		cout<<-(*s.lower_bound(-n))<<"\n";
	}
	return 0;
}
```

---

## 作者：shinzanmono (赞：0)

# [ARC161B] Exactly Three Bits

首先，我们可知，$n<7$ 时，是绝对不可能有解的。

然后我们对每个 $n$ 转成二进制串 $s$，然后进行分类讨论。

1. $\mathrm{popcount}(s)=1$，也就是说二进制串的形式是 $1\underset{n个0}{00\cdots00}$，那么我们可以那么答案便是 $111\underset{n-4个0}{00\cdots00}$
2. $\mathrm{popcount}(s)=2$ 且第二个 $1$ 在字符串末尾，这个答案同第一种情况。
3. $\mathrm{popcount}(s)=2$ 且第二个 $1$ 不在字符串末尾，我们找到第二个 $1$ 的位置 $p$，将 $s_p$ 改为 $0$，$s_{p+1}$ 和 $s_{p+2}$ 改为 $1$（由于 $s$ 是字符串，所以 $i$ 越大，$s_i$ 的位数越低）。
4. $\mathrm{popcount}(s)\geq3$，我们找到第三个 $1$ 的位置 $p$，然后将 $[p+1,\mathrm{len}(s)]$ 全部变为 $0$。

我们对二进制串 $s$ 进行操作，最后将 $s$ 转为十进制。这里介绍一个函数：

`long long stoll(const std::string &__str, std::size_t *__idx, int __base)`

这个函数可以将字符串转为 `long long` 型，`__idx` 一般使用 `nullptr`，`base` 是字符串的进制，默认为 $10$ 进制转换。

给出代码：

```cpp
#include<iostream>
#include<algorithm>
#include<string>
#include<stack>
using ll = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        ll n;
        std::cin >> n;
        if (n < 7) std::cout << "-1\n";
        else {
            std::stack<ll> s;
            std::string bit;
            if (n < 7) std::cout << "-1\n";
            ll cx = n;
            while (cx)
                s.push(cx % 2), cx /= 2ll;
            while (!s.empty()) 
                bit += s.top() + '0', s.pop();
            int cnt = 0;
            for (char c: bit) 
                if (c == '1') cnt++;
            if (cnt < 3) {
                if (cnt == 1) bit = "111" + std::string(bit.length() - 4, '0');
                else {
                    int pos = bit.find('1', bit.find('1') + 1);
                    if (pos > bit.length() - 3) 
                        bit = "111" + std::string(bit.length() - 4, '0');
                    else bit[pos] = '0', bit[pos + 1] = bit[pos + 2] = '1';
                }
            }
            else {
                int pos = bit.find('1', bit.find('1', bit.find('1') + 1) + 1);
                for (int i = pos + 1; i < bit.size(); i++) bit[i] = '0';
            }
            std::cout << std::stoll(bit, nullptr, 2) << "\n";
        }
    }
    return 0;
}
```

---

## 作者：Empty_Dream (赞：0)

## 题意
给你一个正整数 $N$，求小于等于 $N$ 的所有数中最大的一个在二进制下拥有 $3$ 个 $1$ 的数。

## 思路
我们先看无解的情况，因为题目要求必须有 $3$ 个 $1$，所以当 $n \leq 6$ 时，直接输出 $-1$。

我们可以考虑使用递归，设 $f(X)$ 为 $X$ 在二进制下 $1$ 的个数，我们可以得到以下几种情况。

1. 当 $f(X) \lt 3$ 时，将 $X$ 减去 $1$（因为在递归过程中，每一步都是将 $X$ 变得更小，即比 $X$ 大的数都不满足要求，只能去比 $X$ 小的数去找可行情况）。

2. 当 $f(X) =3$ 时，$X$ 即为答案。

3. 当 $f(X) \gt 3$ 时，将 $X$ 在二进制下最右边的 $1$ 变为 $0$（满足贪心，减去一个最小的数，使答案最大化）。

这个数据范围要做什么不用我多说了吧。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, n;

int f(int x){
    int cnt = 0;
    while (x){
        cnt++;
        x ^= (x & -x);
        /*
         N & -N 用于获取 N 的最低位的 1。
         这是通过将 N 的二进制表示与其负值（按位取反再加 1）进行按位与操作得到的。
         N ^ (N & -N) 则是将 N 的最低位的 1 置为 0，其它位保持不变。
        */
    }
    return cnt;
}

int solve(int x, int k){//x 表示当前数值，k 表示 x 在二进制数下有多少个 1。
    if (k < 3) return solve(x - 1, f(x - 1));
    if (k == 3) return x;
    if (k > 3) return solve(x ^ (x & -x), k - 1);
}

signed main(){
    cin >> t;
    while (t--){
        cin >> n;
        if (n <= 6) cout << -1 << endl;
        else cout << solve(n, f(n)) << endl;
    }
    return 0;
}
```


---

## 作者：LiJinLin_AFO (赞：0)

# AT_arc161_b 题解
~~大模拟好题~~
## 正文开始
首先，当 $N\le6$ 时，本题肯定无解，输出 $-1$。为什么呢？因为 $1\sim6$ 的二进制表示中，$1$ 的个数永远不会达到 $3$，大家可以尝试一下。

如果遇到其他的数，我们可以先将这个数进行十进制转二进制，并记录 $1$ 的个数 $all$，二进制数位数为 $sum$，再进行分类讨论：

1. $all=3$。这种情况最简单，直接输出原数 $N$ 即可。

2. $all\ge3$。为了求最大值，我们通过贪心策略可知，将转化的二进制数中末尾的 $1$ 去除，只留下 $3$ 个最前面的 $1$，最后将二进制转化回来，就是答案。

3. $all=2$。我们设二进制数中最先出现的 $1$ 的位置为 $first$，如果按从右往左的顺序 $first$ 在第二位之后，则将位置为 $first$ 的二进制位变为 $0$，位置为 $first-1,first-2$ 的二进制位变为 $1$，否则将位置为 $sum$ 的二进制位变为 $0$，位置为 $sum-1,sum-2$ 的二进制位变为 $1$，最后将二进制转化回来，就是答案。

4. $all=1$。我们将位置为 $sum$ 的二进制位变为 $0$，位置为 $sum-1,sum-2,sum-3$ 的二进制位变为 $1$，最后将二进制转化回来，就是答案。

上代码：
```cpp
#include<stdio.h>
int a[1000];
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		long long n;
		scanf("%lld",&n);
		if(n<7){
			puts("-1");
			continue;
		}
		int bit=0,all=0;
		long long yu=n;
		while(yu){
			a[bit++]=yu%2;
			yu/=2;
			if(a[bit-1]) all++;
		}
		if(all==3){
			printf("%lld\n",n);
			continue;
		}
		if(all>3){
			for(int i=0;i<bit&&all>3;i++) if(a[i]) a[i]=0,all--;
			long long ans=0;
			for(int quan=0;quan<bit;quan++) if(a[quan]) ans+=1ll<<quan;
			printf("%lld\n",ans);
			continue;
		}
		if(all==2){
			int first;
			for(first=0;first<bit&&!a[first];first++);
			if(first<2){
				a[--bit]=0;
				a[bit-1]=a[bit-2]=1;
			}
			else{
				a[first]=0;
				a[first-1]=a[first-2]=0;
			}
			long long ans=0;
			for(int quan=0;quan<bit;quan++) if(a[quan]) ans+=1ll<<quan;
			printf("%lld\n",ans);
		}
		if(all==1){
			a[--bit]=0;
			a[bit-3]=a[bit-1]=a[bit-2]=1;
			long long ans=0;
			for(int quan=0;quan<bit;quan++) if(a[quan]) ans+=1ll<<quan;
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```
注：请勿抄袭！

---

## 作者：code_hyx (赞：0)

这不是 $A$ 题的难度吗。  
显然，$N<7$ 时，无解。  
然后，枚举三个二进制位下的 $1$ 的位置，可以使用贪心法，原因也很显然，因为如果高位有 $1$，那么一定比 $1$ 在低位的数要大。再说得详细一点，$2^n=2^m \times 2^{n-m}$，在后面补 $1$，就相当于给 $2^{n-m}$ 加上 $2^{n-m-k}$（$k$ 为正整数），$2^{n-m-k}$ 一定不如 $2^{n-m}$ 大，所以不可能加出比 $2^n$ 还大的结果。  
那么，从高位到低位枚举就行了，优先满足高位的 $1$。  
常数约为 $64 \times 3$，有点大，但可以稳过这道题。  
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		if(n<7)
		{
			cout<<-1<<"\n";
			continue;
		}
		long long maxx=0,maxx1=0,maxx2=0,ans=0;
		for(long long i=62;i>=0;i--)
		{
			if(n-(1LL<<i)>=3)
			{
				maxx=i;
				ans+=(1LL<<i);
				break;
			}
		}
		for(long long i=maxx-1;i>=0;i--)
		{
			if(ans+(1LL<<i)<n)
			{
				maxx1=i;
				ans+=(1LL<<i);
				break;
			}
		}
		for(long long i=maxx1-1;i>=0;i--)
		{
			if(ans+(1LL<<i)<=n)
			{
				maxx2=i;
				ans+=(1LL<<i);
				break;
			}
		}
		cout<<ans<<"\n";
	} 
	return 0;
} 
```


---

