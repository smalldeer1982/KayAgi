# Counting of Trees

## 题目描述

[problemUrl]: https://atcoder.jp/contests/nikkei2019-2-qual/tasks/nikkei2019_2_qual_b

$ N $ 要素からなる整数列 $ D_1,...,D_N $ が与えられます。頂点に $ 1 $ から $ N $ の番号が付けられた $ N $ 頂点からなる木であって、 以下の条件をみたすものの個数を $ 998244353 $ で割ったあまりを求めてください。

- $ 1 $ 以上 $ N $ 以下の任意の整数 $ i $ に対して、頂点 $ 1 $ と頂点 $ i $ の距離が $ D_i $ である。

## 说明/提示

### 注記

- $ N $ 頂点の木とは $ N $ 頂点 $ N-1 $ 辺からなる連結無向グラフのことであり、$ 2 $ 頂点の距離とは一方から他方への最短路に用いられる辺の個数を指します。
- $ 2 $ つの木が異なるとは、ある $ 2 $ 頂点 $ x $, $ y $ が存在して、$ x $ と $ y $ の間に一方の木では辺が存在し、 もう一方の木では辺が存在しないことを指します。

### 制約

- $ 1\ ≦\ N\ ≦\ 10^5 $
- $ 0\ ≦\ D_i\ ≦\ N-1 $

### Sample Explanation 1

例えば、$ (1,2) $, $ (1,3) $, $ (2,4) $ の間に辺があるような木が条件をみたします。

## 样例 #1

### 输入

```
4
0 1 1 2```

### 输出

```
2```

## 样例 #2

### 输入

```
4
1 1 1 1```

### 输出

```
0```

## 样例 #3

### 输入

```
7
0 3 2 1 2 2 1```

### 输出

```
24```

# 题解

## 作者：nytyq (赞：1)

## 分析

这道题就是思维题。

由于不能直接构出整棵树，则考虑排列进行计算数量。

对于深度相同的节点，直接根据上一个深度的节点数量与此节点深度的节点乘方即可。

用 $C_i$ 代表深度为 $i$ 的节点编号，因为题目中有 $a_i(0 \le i < n)$ 为约束，所以 $c_i(0 \le i \le \max(a_i))$ 一定是固定的。

则形式化的，则为：

考虑当前的深度为 $d$，令 $c1=C_d$，$c2=C_{d-1}$，则一共可构成的状态有 $c1^{c2}$ 个。

特别地，开头需要判断是否 $c_0>1$ 或者 $a_0\ne 0$，如果是，则无解。不是，则有解。

## ACcode

```
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod=998244353,N=1e5+10;

ll fp(ll a,ll b){//快速幂
	ll ans=1;
	while(b){
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}

int n;
int d[N],C[N];

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>d[i];C[d[i]]++;//统计
	}
	ll cnt=1;
	if(d[0]!=0 || C[0]>1){//特判
		cout<<0;
		exit(0);
	}
	
	for(int i=1;i<n;i++){
		cnt*=fp(C[i-1],C[i]);
		cnt%=mod;
	}
	cout<<cnt;
	return 0;
}
```

---

## 作者：chengjindong (赞：1)

[题目](https://www.luogu.com.cn/problem/AT_nikkei2019_2_qual_b)

分两种情况，有解和无解。

- 有解：记录每一层的结点，答案就是每一层结点排列的乘积。

- 无解：需要特判一下：第一个数字一定为 $0$ 且其余的数字一定不为 $0$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int mod=998244353;//模数 
int f(int a,int b){//求幂，不会超时，不用快速幂，因为快速幂写错，我错了好几次。。 
	int ans=1;
	for(int i=0;i<b;i++){
		ans*=a;
		ans%=mod;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
    int n;
    cin >>n;
    int a[n];
    map<int,int>m;//这里也可以替换为数组，用来统计每个深度出现过的次数 
    for(int i=0;i<n;i++){
    	cin >>a[i];
    	m[a[i]]++;//为a[i]的个数加一 
	}
    if(a[0]!=0||m[0]>1){//特判 
        cout<<0<<endl;
        return 0;
    }
    int ans=1;
    for(int i=1;i<n;i++){//到n-1即可 
       	ans*=f(m[i-1],m[i])%mod;//i-1的个数的i的个数次方 
    	ans%=mod;//取余 
	}
    cout<<ans<<endl;
	return 0;
}
```

---

## 作者：CmsMartin (赞：1)

## 前言

很不要脸的推广一下 [CmsBlog](116.62.168.66:8090)

## 题目描述

见[题目翻译](https://www.luogu.com.cn/problem/AT5633)

## 思路

https://oi-wiki.org/math/quick-pow/

首先，先要判定不合法的情况，即：

+ 第一个数字一定为 $0$；
+ 其余的数字一定不为 $0$。


遇到这个情况，用一个变量标记下来，输出 $0$

**给出的样例无解就没有输出，但是[实测](https://www.luogu.com.cn/record/62652502)会 WA ，必须输出 $0$ !!!**

如果有解，那么很显然，即为每一层的结点的排列的乘积。

用桶或 map 记录每一层的结点，别忘了用快速幂优化。。。

**三年 OI 一场空，不开 `long long` 见祖宗！！！**

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int Mod = 998244353;

int N , T , MAXN , Ans = 1;

bool Flag = 1;

map<long long , long long> Tong;

long long binpow(long long a, long long b, long long m) {
  a %= m;
  long long res = 1;
  while (b > 0) {
    if (b & 1) res = res * a % m;
    a = a * a % m;
    b >>= 1;
  }
  return res;
}

int main() {
	ios::sync_with_stdio(false);
	
	cin >> N;
	
	for(long long i = 0; i < N; i++) {
		cin >> T;
		Tong[T]++;
		MAXN = max(MAXN , T);
		if((i == 0 && T != 0) || (i != 0 && T == 0)) Flag = 0;
	}
	
	if(Flag) {
		for(long long i = 1; i <= MAXN; i++) {
			Ans = (Ans % Mod * binpow(Tong[i - 1] , Tong[i] , Mod) % Mod) % Mod;
		}	
		cout << Ans % Mod << endl;
	}	
	
	else cout << 0 << endl;
	
	return 0;
}
```

---

## 作者：lyh0217 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_nikkei2019_2_qual_b)

题意题目已描述的十分简洁，这里不再赘述。

### 思路

对于每个节点，其深度为 $x$，如果要让这个树是好的，就应该和一个深度为 $x-1$ 的点连边，那么对于这个点它的可能方案数就是 $d_{x-1}$，其中 $d_i$ 表示深度为 $i$ 的节点个数，根据乘法原理将所有点的方案数乘起来就可以了。

发现深度相同的点的方案数是一样的，可以用快速幂（虽然没啥用）


### code

码风较丑，见谅 QwQ。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ksm(long long x,int y)
{
	long long ans=1;
	while(y)
	{
		if(y&1) ans=ans*x%998244353;
		x=x*x%998244353;
		y/=2;
	}
	return ans;
}
int deep[100005];
int main()
{
	int n,maxx=-1;
	bool f=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		if(!x)//如果这个点是根，且不是一号节点，就不可行
		{
			if(i!=1)
			{
				f=1;
			}
		}
		if(i==1&&x)//1不是根
		{
			f=1;	
		}
		deep[x]++; //统计深度为x的节点个数
		maxx=max(maxx,x);
	}
	if(f) //根不合法情况
	{
		cout<<0;
		return 0;
	}
	long long ans=1;
	for(int i=1;i<=maxx;i++)
	{
		ans=ans*ksm(deep[i-1],deep[i])%998244353;//统计答案（多取模）
	}
	cout<<ans;
	return 0;
}
```

[评测记录](https://atcoder.jp/contests/nikkei2019-2-qual/submissions/61962612)

---

## 作者：Ryan_Adam (赞：0)

# Counting of Trees 题解
## 题目大意
给你一个长度为 $n$ 的序列 $a$，问有多少颗树满足第 $i$ 个点的深度为 $a_i$。
## 分析
开一个桶数组 $t$，$t_i$ 统计深度为 $i$ 的点的个数。假设深度为 $i-1$ 的点有 $x$ 个，深度为 $i$ 的点有 $y$ 个。对于每个深度为 $i$ 的点，都可以连接 $x$ 个深度为 $i-1$ 的点，所以方案数为 $x^y$。每两层都次方，用 $ans$ 累乘起来就是答案了。

**需要注意特判的三个情况**：
- 当 $a_1$ 不是 $0$ 时直接输出 $0$。
- 当 $t_0$ 不是 $1$ 时直接输出 $0$。
- 当深度不连续时，比如说序列 $a$ 为 $1,3,5,7,8$ 时，直接输出 $0$。
## 示例代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace Raiden
{
    const int N = 2e5 + 5, mod = 998244353;
    int a[N];
    int t[N];
    int qpow(int a, int p, int m)
    {
        if (p == 0)
        {
            return 1;
        }
        long long result = 1;
        long long base = a % m;
        while (p > 0)
        {
            if (p % 2 == 1)
            {
                result = (result * base) % m;
            }
            base = (base * base) % m;
            p /= 2;
        }
        return result;
    }
    signed work()
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            t[a[i]]++;
        }
        if (a[1] != 0 || t[0] > 1)
        {
            cout << 0 << endl;
            return 0;
        }
        for (int i = 1; i <= n; i++)
        {
            if (t[i] == 0 && t[i + 1] != 0)
            {
                cout << 0 << endl;
                return 0;
            }
        }
        int ans = 1;
        for (int i = 1; i <= n; i++)
        {
            if (t[i - 1] != 0)
            {
                ans = ans * (qpow(t[i - 1], t[i], mod)) % mod;
            }
        }
        cout << ans << endl;
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
```

---

## 作者：xiao_dong_xi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_nikkei2019_2_qual_b)
### 解题思路
理解题目，想到构建一棵满足条件的树，使得每个节点的深度与给定的 $D_i$ 相对应。

其余内容在注释中展现。

还有，在计算时，可能会爆 `int`，所以要开 `long long`！
### CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MOD 998244353
#define int long long
int d[100005],cnt[100005];//cnt数组统计每个深度出现的次数
int fast_power(int a, int n, int p) {//快速幂，高效计算底数的指数次方并取模
    int res = 1;
    while (n > 0) {
        if (n & 1) {
            res = (res * a) % p;
        }
        a = (a * a) % p;
        n >>= 1;
    }
    return res;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) scanf("%d", &d[i]);
    int ans = 1;
    for (int i = 0; i < n; i++) cnt[d[i]]++;//对于每个深度 d[i]，将 cnt[d[i]] 的值加一
    if (d[0] != 0 || cnt[0] != 1) { //检查深度为 0 的节点是否只有一个，且距离为 0，如果不是即无解，输出 0。
        cout << 0;
        return 0;
    }
    for (int i = 1; i < n; i++) {
        ans *= fast_power(cnt[i - 1], cnt[i], MOD);//计算答案，对于深度为 i 的节点，选取深度为 i-1 的节点的数量作为底数，深度为 i 的节点的数量作为指数，然后计算 a^b mod MOD 并将结果累积。
        ans %= MOD;
    }

    cout << ans;
    return 0;
}

```

---

## 作者：Nightsky_Stars (赞：0)

# 题目大意：

给定一个长度为 $n$ 的数列 $a$，问有多少个树满足第 $i$ 个点的深度为 $a_i$。

# 思路：

有解时，用桶记录每一层的结点，答案就是每一层的结点的排列的乘积。

无解时，需要特判一下：

- 第一个数字一定为 $0$；

- 其余的数字一定不为 $0$。

记得开 long long。

# CODE:

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[100010],s[100010],ans=1,mod=998244353;
ll qow(ll a,ll b){//快速幂优化
	ll ans=1;
	while(b>0){
        if(b%2!=0) ans=ans*a%mod;
        a=a*a%mod;
        b=b>>1;
    }
    if(ans%mod==0) return ans;
    ans%=mod;
    return ans;
}
int main(){
	ll n;
	cin>>n;
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		s[a[i]]++;
	}
	if(a[1]!=0||s[0]>1){
		cout<<"0\n";
		return 0;
	}
	for(ll i=1;i<=n;i++){
		if(s[i]==0&&s[i+1]!=0){
			cout<<"0\n";
			return 0;
		}
	}
	for(ll i=1;i<=n;i++){
		if(s[i-1]!=0) ans=ans*qow(s[i-1],s[i])%mod;
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

