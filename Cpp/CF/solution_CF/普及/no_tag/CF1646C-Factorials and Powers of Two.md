# Factorials and Powers of Two

## 题目描述

A number is called powerful if it is a power of two or a factorial. In other words, the number $ m $ is powerful if there exists a non-negative integer $ d $ such that $ m=2^d $ or $ m=d! $ , where $ d!=1\cdot 2\cdot \ldots \cdot d $ (in particular, $ 0! = 1 $ ). For example $ 1 $ , $ 4 $ , and $ 6 $ are powerful numbers, because $ 1=1! $ , $ 4=2^2 $ , and $ 6=3! $ but $ 7 $ , $ 10 $ , or $ 18 $ are not.

You are given a positive integer $ n $ . Find the minimum number $ k $ such that $ n $ can be represented as the sum of $ k $ distinct powerful numbers, or say that there is no such $ k $ .

## 说明/提示

In the first test case, $ 7 $ can be represented as $ 7=1+6 $ , where $ 1 $ and $ 6 $ are powerful numbers. Because $ 7 $ is not a powerful number, we know that the minimum possible value of $ k $ in this case is $ k=2 $ .

In the second test case, a possible way to represent $ 11 $ as the sum of three powerful numbers is $ 11=1+4+6 $ . We can show that there is no way to represent $ 11 $ as the sum of two or less powerful numbers.

In the third test case, $ 240 $ can be represented as $ 240=24+32+64+120 $ . Observe that $ 240=120+120 $ is not a valid representation, because the powerful numbers have to be distinct.

In the fourth test case, $ 17179869184=2^{34} $ , so $ 17179869184 $ is a powerful number and the minimum $ k $ in this case is $ k=1 $ .

## 样例 #1

### 输入

```
4
7
11
240
17179869184```

### 输出

```
2
3
4
1```

# 题解

## 作者：Eason_AC (赞：8)

## Update
- $\texttt{2022.3.13}$：修改了一处错误。

## Content
我们称一个数 $m$ 是好数，当且仅当 $m$ 为形如 $d!$ 或者 $2^d$ 的数。现在给定一个整数 $n$，请求出最小的整数 $k$，使得 $n$ 可以表示成 $k$ 个**互不相同**的好数的和。

**数据范围：$t$ 组数据，$1\leqslant t\leqslant 100$，$1\leqslant n\leqslant 10^{12}$。**
## Solution
由于 $15!\approx 1.3\times 10^{12}>10^{12}$，因此我们先预处理出所有的 $10^{12}$ 以内的阶乘（只有 $14$ 个），然后直接暴力枚举每个阶乘选还是不选，将 $n$ 减去所有选了的阶乘的和，得到的数 $n'$ 用若干 $2$ 的次幂表示，最少需要的 $2$ 的次幂的个数即为 $n'$ 的二进制表示中 $1$ 的个数，可以用 `__builtin_popcount()` 函数来直接计算。最后将所有阶乘个数和 $2$ 的次幂个数和取最小值即为答案。
## Code
```cpp
namespace Solution {
	long long fac[27];
	int m;
	int Tnum;
	int ans;
	long long n;
	
	void dfs(int x, int cnt, long long rest) {
		if(x > m) {
			ans = min(ans, cnt + __builtin_popcountll(rest));
			return;
		}
		if(rest - fac[x] >= 0
		&& cnt + 1 < ans)
			dfs(x + 1, cnt + 1, rest - fac[x]);
		dfs(x + 1, cnt, rest);
	}
	
	void Main() {
		fac[0] = 1;
		while(1) {
			++m;
			fac[m] = 1ll * fac[m - 1] * m;
			if(fac[m] > 1000000000000ll) {
				--m;
				break;
			}
		}
		read(Tnum);
		while(Tnum--) {
			read(n);
			ans = __builtin_popcountll(n);
			dfs(1, 0, n);
			write(ans);
			puts("");
		}
		return;
	}
}
```

---

## 作者：Duramente (赞：4)

[传送门](https://codeforces.com/contest/1646/problem/C)

感觉这个题非常妙。

## 题意  
给一个数 $n$，求最少用多少个不同 powerful 的数，使他们和为 $n$。  
powerful 数的定义为 $2$ 的整数次幂和任意数的阶乘。   
$n\leq 10^{12}$

## Solution
先考虑如果只能用 $2$ 的整数次幂怎么做。容易发现直接对 $n$ 进行二进制拆分即可。  
使用的数量为 $n$ 在二进制中 $1$ 的个数。  
然后我们考虑带入阶乘的情况。  
由于 $n\leq10^{12}$，而阶乘的增长是非常快的，$15!$ 已经大于 $10^{12}$ 了。  
于是我们可以状压枚举使用了哪些 $15$ 以下的数的阶乘，将减去使用了的阶乘的结果再二进制拆分取 min。  

## Code
```cpp
#include<bits/stdc++.h>
#define forn(i,a,b)for(int i=(a),_b=(b);i<=_b;i++)
#define fore(i,b,a)for(int i=(b),_a=(a);i>=_a;i--)
#define rep(i,n)for(int i=0,_n=n;i<n;i++)
#define ll long long
#define pii pair<int,int>
#define m_p make_pair
#define pb push_back
#define fi first
#define se second
#define int ll
#define foreach(i,c) for(__typeof(c.begin())i=(c.begin());i!=(c).end();i++)
using namespace std;
int fac[20];
int cnt(int x){
	int res=0;
	rep(i,60){
		if((x>>i)&1)res++;
	}
	return res;
} 
int x;
void solve(){
	cin>>x;
	int ans=cnt(x);
	rep(msk,1<<15){
		int y=x;
		rep(i,15){
			if((msk>>i)&1)y-=fac[i+1];
		}
		if(y>=0){
			ans=min(ans,cnt(y)+cnt(msk));
		}
	}	
	cout<<ans<<"\n";
}
signed main(){
    cin.tie(0);
	ios::sync_with_stdio(0);
	fac[0]=1;
	forn(i,1,15)fac[i]=fac[i-1]*i;
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}

---

## 作者：Composite_Function (赞：3)

# 思路

**我们会发现，这道题无论怎么加 $d!$ ，最后的结果一定可以用 $2^d$ 表示！！！**

证明：设已加上 $d!$ 后还需加的的数为 $m$ ，则 $m$ 的二进制中为 $1$ 的数位就用 $2^d$ 表示即可

然后我们求出 $1$ ~ $10^{12}$ 中阶乘数仅有 $15$ 个

不信请运行以下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long val=1,tme,num=1;
const long long MAX=pow(10,12);
//n的最大值
int main(){
    while(val<=MAX){
        //cout<<val<<endl;
        //把注释去掉就可以看见具体值
        val*=num;
        num++;
        tme++;
    }
    cout<<tme<<endl;
}
```

所以可以用 dfs 深搜是否需要选该阶乘数
~~（你想写 15 个循环我也不拦你）~~

注意要预处理出阶乘数

------------

# AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,num[20];
void init(){
    long long val=1;
    for(long long i=1;i<=15;i++)
        val*=i,num[i]=val;
    //预处理阶乘数
}
long long dfs(long long pos,long long val,long long tmp){
    if(val<0) return INT_MAX;
    else if(pos==15+1){
        long long ans=0;
        while(val>0){
            if(val&1) ans++;
            //检测二进制位是否为 1 
            val>>=1;
            //取位，往下检测
        }
        return ans+tmp;
    }
    else return min(dfs(pos+1,val,tmp),dfs(pos+1,val-num[pos],tmp+1));
    //标准的深搜
}
int main(){
    init();
    //预处理别忘写了
    cin>>t;
    while(t--){
        cin>>n;
        cout<<dfs(1,n,0)<<endl;
    }
    return 0;
}
```

复杂度：$O(t \cdot 2 ^ {15})$

**粘代码前请三思而后行，做题是为了学习，而不是为了显摆**

---

## 作者：_Fatalis_ (赞：1)

### Solution

首先，$-1$ 是不可能的。因为任意一个非负整数都可以转换成对应的二进制。而对应二进制位上的 $1$，单独拿出来，就都是强数。

比如 $7=(111)_2=1\times2^0+1\times2^1+1\times2^2$。

那么，现在就想，如何使 $k$（即分解个数）最小了。

若直接枚举强数相加，那么时间复杂度为 $2^{(\log_2 10^{12}+16)}$。比较危险。

但是，发现只要确定阶乘的强数，反过来就可以推出二次幂的强数个数。

所以，可以只枚举 $2^{16}$ 次就可以了。

（$16$ 来自何方？$10^{12}$ 的逆阶乘小于等于 $16$。）

```cpp
#include<bits/stdc++.h>
using namespace std;
int minx=-1;
long long a[17];

long long fac(int x)
{
    long long ans=1;
    for(int i=1;i<=x;i++) ans*=i;
    return ans;
}

void init()
{
    for(int i=1;i<=16;i++) a[i]=fac(i);
}

int bitcount(long long x)
{
    int ans=0;
    do
        ans+=(x&1);
    while(x>>=1);
    // cout<<x<<" "<<ans<<endl;
    return ans;
}

void dfs(int now,int tot,long long sum)
{
    if(now==16+1||sum-a[now]<0)
    {
        // cout<<sum<<" "<<tot<<" "<<bitcount(sum)<<endl;
        minx=min(minx,tot+bitcount(sum));
        // cout<<"debug "<<minx<<endl;
        return;
    }
    dfs(now+1,tot+1,sum-a[now]);
    dfs(now+1,tot,sum);
}

int main()
{
    init();
    int t;
    cin>>t;
    while(t--)
    {
        long long n;
        int ans=0;
        minx=1e9;
        cin>>n;
        dfs(1,0,n);
        cout<<minx<<endl;
    }
    return 0;
}
```

---

## 作者：ryanright (赞：1)

### Description

定义一个数为 **强大的** 当其可以被写成 $2^d$ 或 $d!$ 的形式（$d\in\mathbb N_+$）。特别的，$0!=1$。现给出一个正整数 $n$，问 $n$ 最少能够拆解为几个不同的强大的数的和。若不能拆解，输出 `-1`。

### Solution

为了方便，此处定义阶乘的反函数为 $\operatorname{arcfac}(x)$。

题目给出的范围为 $n\le10^{12}$，而 $\big\lfloor\log10^{12}\big\rfloor=39$，$\big\lfloor\operatorname{arcfac}(10^{12})\big\rfloor=14$，其中 $2^0=0!=1!=1$，$2^1=2!=2$，所以在数据范围内不同的强大的数有 $39+14-2-1=50$ 个。如果我们全部暴力 dfs 肯定是不行的。但是发现阶乘数却只有 $14$ 个，如果只枚举阶乘数，是可以过的。

事实上，一个自然数 $x$ 能被 $\operatorname{bitcount}(x)$ 个不同的 $2$ 的整数幂分解，其中 $\operatorname{bitcount}(x)$ 为 $x$ 的二进制表示中 $1$ 的个数。这是显而易见的。于是我们可以枚举阶乘数，将余下的部分求 $\operatorname{bitcount}$，求得每一种方案的分解数，最后去最小值即可。

单次询问时间复杂度为 $O(2^{\operatorname{arcfac}(n)}\log n)$。

### Code

还是要开 `long long`。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,fac[20];
int ans;
inline int bitcount(long long x)
{
    int tot=0;
    while(x)
    {
        tot+=x&1;
        x>>=1;
    }
    return tot;
}
inline void dfs(int pos,long long sum,int chosen)
{
    if(sum+fac[pos]>n||pos==16)
    {
        ans=min(ans,chosen+bitcount(n-sum));
        return;
    }
    dfs(pos+1,sum,chosen);
    dfs(pos+1,sum+fac[pos],chosen+1);
}
int main()
{
    fac[0]=1;
    for(int i=1;i<=15;i++) fac[i]=fac[i-1]*i;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld",&n);
        ans=100;
        dfs(0,0,0);
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：Rad_Forever (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1646C)

## 题目大意

给定一个正整数 $n$，你需要将其拆分为若干个不同的正整数之和，满足每一个数都可以表示为 $2^d$ 或者 $d!$ 的形式。

## 思路

看到题目的数据范围 $n \leq 10^{12}$，计算了一下发现 $15! > 10^{12}$，所以被拆分出来的 $d!$ 的形式的数不会超过 $14$ 个。

$14$ 很小，考虑状压。

用 $2^{14}$ 枚举每一个 $d!$ 的形式的数是否要被拆分出来，再用 $n$ 减去数字总和计算一下二进制下 $1$ 的个数即可。

[评测记录](https://codeforces.live/problemset/submission/1646/148339467)

---

## 作者：daniEl_lElE (赞：1)

## 思路

我们发现，满足 $i!<10^{12}$ 的 $i$ 非常少，只有 $14$ 种，所以我们可以暴力枚举选了哪些阶乘，先使用状态压缩的方式记录每种的和。然后，对于每种阶乘的组合选择，计算 $n-f_i$ 与 $i$ 二进制表示下分别的 $1$ 的数量相加，更新一下最小值即可。复杂度 $O(2^{14}\times\log n)$，即可通过本题。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int k[16385];
int pc(int i){
	int sum=0;
	while(i){
		sum+=(i%2);
		i/=2;
	}
	return sum;
}
signed main(){
	int a[15];
	a[0]=1;
	for(int i=1;i<=14;i++){
		a[i]=a[i-1]*i;
	}
	for(int i=0;i<(1<<14);i++){
		int bit[15],sum=0,now=i;
		for(int j=1;j<=14;j++){
			bit[j]=now%2;
			now/=2;
			sum+=bit[j]*a[j];
		}
		k[i]=sum;
	}
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int minv=pc(n);
		for(int i=0;i<(1<<14);i++){
			if(k[i]<=n){
				minv=min(minv,pc(n-k[i])+pc(i));
			}
		}
		cout<<minv<<endl;
	} 
	return 0;
}
```

---

## 作者：xiazha (赞：0)

### 思路

搜索题。

首先，这道题有一个很关键的地方：$15!>10^{12}$，而 $n\le10^{12}$。

也就是说，我们可以将 $15$ 以内的阶乘预处理出来，然后跑 ```dfs``` 暴力枚举当前阶乘选与不选即可。

但是，到达边界时还可能会有剩余。我们只需将剩余的数用 ```__builtin_popcount()``` 函数统计一下这个数在二进制表示下共有几个 $1$ 即可，这样就相当于求出了剩余的数需要用几个 $2^d$ 表示出来。

注意要开 ```long long```。



------------

### 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
int t,n,jc[16],minn;
void dfs(int now,int step,int sum)
{
	if(step>15)
	{
		minn=min(minn,sum+__builtin_popcountll(now));
		return;
	}
	if(now-jc[step]>=0) dfs(now-jc[step],step+1,sum+1);
	dfs(now,step+1,sum);
}
signed main()
{
	t=read();
	jc[0]=1;
	for(int i=1;i<=15;i++) jc[i]=jc[i-1]*i;
	while(t--)
	{
		minn=2100000000;
		n=read();
		dfs(n,1,0);
		printf("%lld\n",minn);
	}
	return 0;
}
```


---

## 作者：BorisDimitri (赞：0)

# 题意
给出一个数 $n$，定义一个数 `powerful` 当且仅当这个数是 $2$ 的幂，或者是一个阶乘。

求最少要用多少个`powerful`数才能凑出(加法) $n$ (不能重复使用)。

如果不能凑出则输出 $-1$。

# 分析

首先这个数一定可以被凑出来，永远不会输出 $-1$ 。

> **proof:**
>
> 由于 $n$ 一定可以表示为二进制，所以 $n$ 一定可以用若干个 $2^k$ 表示出来，且最少的个数为它二进制表示中 $1$ 的个数。

预处理出所有的阶乘(最多有 $14$ 个)

$DP$ 处理使用阶乘和 $2$ 的幂一起使用的情况。

记 $x$ 的二进制表示中 $1$ 的个数为: $f(x)$ , 选择了 $t$ 个阶乘且阶乘之和和为 $s$, 代价则是 $t+f(n-s)$。

# code
```cpp
typedef long long LL;
const LL N = 1e12;

int get_first_bit(LL n)
{
    return 63 - __builtin_clzll(n);
}

int get_bit_count(LL n)
{
    int res = 0;
	while(n) n -= (n & -n), res ++;
	return res;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

    int t;
    cin >> t;

	vector<LL> fact;
	LL factorial = 6, number = 4;
	while (factorial <= N)
	{
		fact.push_back(factorial);
		factorial *= number;
		number++;
	}

	vector<pair<LL, LL>> fact_sum(1 << fact.size());
	fact_sum[0] = {0ll, 0ll};

	for (int i = 1; i < (1 << fact.size()); i++)
	{
		auto first_bit = get_first_bit(i);
		fact_sum[i].first = fact_sum[i ^ (1 << first_bit)].first + fact[first_bit];
		fact_sum[i].second = get_bit_count(i);
	}

    while(t--)
    {
        LL n;
        cin >> n;

        LL res = get_bit_count(n);
        for (auto i : fact_sum)
            if (i.first <= n)
                res = min(res, i.second + get_bit_count(n - i.first));
        
        cout << res << "\n";
    }

    return 0;
}
```

---

