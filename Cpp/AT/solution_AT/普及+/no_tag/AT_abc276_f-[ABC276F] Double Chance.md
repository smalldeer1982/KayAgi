# [ABC276F] Double Chance

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc276/tasks/abc276_f

カード $ 1 $, カード $ 2 $, $ \ldots $, カード $ N $ の $ N $ 枚のカードがあり、 カード $ i $ $ (1\leq\ i\leq\ N) $ には整数 $ A_i $ が書かれています。

$ K=1,2,\ldots,N $ について、次の問題を解いてください。

> カード $ 1 $, カード $ 2 $, $ \ldots $, カード $ K $ の $ K $ 枚のカードが入っている袋があります。  
> 次の操作を $ 2 $ 回繰り返し、記録された数を順に $ x,y $ とします。
> 
> > 袋から無作為にカードを $ 1 $ 枚取り出し、カードに書かれている数を記録する。その後、カードを **袋の中に戻す** 。
> 
> $ \max(x,y) $ の値の期待値を $ \text{mod}\ 998244353 $ で出力してください（注記参照）。  
> ただし、$ \max(x,y) $ で $ x $ と $ y $ のうち小さくない方の値を表します。

## 说明/提示

### 注記

求める期待値は必ず有限値かつ有理数となることが証明できます。また、この問題の制約下では、その値を互いに素な $ 2 $ つの整数 $ P $, $ Q $ を用いて $ \frac{P}{Q} $ と表したとき、$ R\ \times\ Q\ \equiv\ P\pmod{998244353} $ かつ $ 0\ \leq\ R\ \lt\ 998244353 $ を満たす整数 $ R $ がただ一つ存在することが証明できます。この $ R $ を出力してください。

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 2\times\ 10^5 $
- 入力は全て整数

### Sample Explanation 1

例えば、$ K=2 $ の時の答えは次のようにして求まります。 袋の中にはカード $ 1 $ とカード $ 2 $ が入っており、それぞれには $ A_1=5 $ と $ A_2=7 $ が書かれています。 - $ 1 $ 回目に取り出されたカードがカード $ 1 $ 、$ 2 $ 回目に取り出されたカードもカード $ 1 $ のとき、$ x=y=5 $ であり、$ \max(x,y)=5 $ となります。 - $ 1 $ 回目に取り出されたカードがカード $ 1 $ 、$ 2 $ 回目に取り出されたカードはカード $ 2 $ のとき、$ x=5 $, $ y=7 $ であり、$ \max(x,y)=7 $ となります。 - $ 1 $ 回目に取り出されたカードがカード $ 2 $ 、$ 2 $ 回目に取り出されたカードはカード $ 1 $ のとき、$ x=7 $, $ y=5 $ であり、$ \max(x,y)=7 $ となります。 - $ 1 $ 回目に取り出されたカードがカード $ 2 $ 、$ 2 $ 回目に取り出されたカードもカード $ 2 $ のとき、$ x=y=7 $ であり、$ \max(x,y)=7 $ となります。 これらが等確率で起こるため、期待値は $ \frac{5+7+7+7}{4}=\frac{13}{2} $ となります。 $ 499122183\times\ 2\equiv\ 13\ \pmod{998244353} $ であるため、$ 499122183 $ を出力します。

## 样例 #1

### 输入

```
3
5 7 5```

### 输出

```
5
499122183
443664163```

## 样例 #2

### 输入

```
7
22 75 26 45 72 81 47```

### 输出

```
22
249561150
110916092
873463862
279508479
360477194
529680742```

# 题解

## 作者：liangbowen (赞：4)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc261_f)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17435683.html)

非常好的数据结构优化题。

## 思路

对于第 $x$ 次询问，答案为 $\dfrac{\sum\limits_{i=1}^x\sum\limits_{j=1}^x \max(a_i, a_j)}{x^2}$。分母显然可以用逆元求，所以看上面那一坨。

![](https://cdn.luogu.com.cn/upload/image_hosting/q76bb9bo.png)

看上面这幅图就比较显然了，我们只需要在线维护数据结构，支持：

+ 求出有多少个 $a_j \le a_i$。
+ 求出所有满足 $a_j > a_i$ 的 $\sum a_j$。
+ 加入一个元素 $a_i$。

注意到 $\forall a_i \le 2 \times 10^5$，所以直接上权值树状数组即可，一个维护数量，一个维护总和。

## 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 2e5 + 5, mod = 998244353;
int inv(int x, int y = mod - 2)
{
	int ans = 1;
	while (y)
	{
		if (y & 1) ans = 1ll * ans * x % mod;
		x = 1ll * x * x % mod;
		y >>= 1;
	}
	return ans;
}
struct BIT { //权值树状数组 
	int idx[N];
	int lowbit(int x) {return x & -x;}
	void update(int i, int k) {for (; i < N; i += lowbit(i)) (idx[i] += k) %= mod;}
	int query(int i) {int ans = 0; for (; i; i -= lowbit(i)) ans = (ans + idx[i]) % mod; return ans;}
} cnt, sum;
int main()
{
	int n, total = 0, ans = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int a;
		scanf("%d", &a);
		ans += (2ll * cnt.query(a) + 1) * a % mod;         ans %= mod;
		ans += (2ll *(total - sum.query(a)) % mod + mod) % mod; ans %= mod;
		
		printf("%d\n", 1ll * ans * inv(1ll * i * i % mod) % mod);
		total = (total + a) % mod;
		cnt.update(a, 1), sum.update(a, a);
	}
	return 0;
}
```

希望能帮助到大家！

---

## 作者：Semorius (赞：2)

设 $b_x$ 表示第 $x$ 次操作的期望权值，由题意可得：
$$b_x=x^{-2}\times \sum\limits_{1 \leq i,j \leq x}\max(a_i,a_j)$$

前面的部分可通过求逆元直接获得。设后面那部分为 $c_x$，递推计算 $c_x$ 的值，只需要计算新增添的数 $a_x$ 对 $c_x$ 的影响。对于 $a_1$ 到 $a_{x-1}$ 中所有小于 $a_x$ 的数 $a_i$，$\max(a_i,a_x)=a_x$，否则 $\max(a_i,a_x)=a_i$，于是开两个树状数组维护 $a_1$ 到 $a_{x-1}$ 中小于等于 $a_x$ 的数的个数 $\text{cnt}$，以及 $a_1$ 到 $a_{x-1}$ 中比 $a_x$ 大的数的和 $\text{sum}$。由于选到相同的两个数调换顺序为两种情况，所以：
$$c_x=c_{x-1}+\text{cnt}\times a_x\times2+\text{sum}\times2+a_x$$

注意不要少取模，时间复杂度 $O(n \log n)$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll SIZE = 200005;
const ll mod = 998244353;
ll n;
ll a[SIZE];
ll cnt[SIZE];
ll sum[SIZE];

inline ll rd(){
	ll f = 1, x = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9'){
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return f*x;
}

ll lowbit(ll x){
	return x & (-x);
}

void addc(ll x, ll val){
	for(ll i = x; i <= 200000; i += lowbit(i)) cnt[i] += val;
}

void adds(ll x, ll val){
	for(ll i = x; i <= 200000; i += lowbit(i)) sum[i] = (sum[i] + val) % mod;
}

int askc(ll x){
	ll jl = 0;
	for(ll i = x; i; i -= lowbit(i)) jl += cnt[i];
	return jl;
}

int asks(ll x){
	ll jl = 0;
	for(ll i = x; i; i -= lowbit(i)) jl = (jl + sum[i]) % mod;
	return jl;
}

ll power(ll x, ll y){
	ll jl = 1;
	while(y){
		if(y&1) jl = (jl * x) % mod;
		x = (x * x) % mod;
		y >>= 1;
	}
	return jl;
}

int main(){
	n = rd();
	for(ll i = 1; i <= n; i++){
		a[i] = rd();
	}
	ll jl = a[1], ss = a[1]; printf("%lld\n", a[1]);
	addc(a[1], 1);
	adds(a[1], a[1]);
	for(ll i = 2; i <= n; i++){
		ll x = askc(a[i]);
		jl = (jl + ((x * a[i] % mod) * 2ll % mod)) % mod;
		x = ((ss - asks(a[i])) % mod + mod) % mod;
		jl = (jl + (x * 2ll % mod)) % mod;
		jl = (jl + a[i]) % mod;
		printf("%lld\n", (jl * power(i*i%mod, mod-2) % mod));
		addc(a[i], 1);
		adds(a[i], a[i]);
		ss = (ss + a[i]) % mod;
	}
	return 0;
}
```


---

## 作者：whhsteven (赞：2)

由题目描述和期望的定义知，对于一个固定的 $K$，答案是 $\dfrac{\sum_{i=1}^K\sum_{j=1}^K\max(A_i,A_j)}{K^2}$。

$K = 1$ 时答案显然是 $A_1$。接下来，考虑增量计算答案。

分母的处理是平凡的。考察分子。

当 $K = K_0$ 的结果已计算，现在令 $K = K_0 + 1$，并加入 $A_{K_0 + 1}$ 时，分子增加了以下三个部分：

- 对于所有先前加入的 $A_i \le A_{K_0 + 1}$，$A_{K_0 + 1}$ 都会作为较大值在 $(i, K_0 + 1)$ 和 $(K_0 + 1, i)$ 处各贡献 $1$ 次；

- $A_{K_0 + 1}$ 会在 $(K_0 + 1, K_0 + 1)$ 处贡献 $1$ 次；

- 对于所有先前加入的 $A_i > A_{K_0 + 1}$，$A_i$ 都会作为较大值在 $(i, K_0 + 1)$ 和 $(K_0 + 1, i)$ 处各贡献 $1$ 次。

第一种贡献需要知道先前加入的 $A_i \le A_{K_0 + 1}$ 的 $i$ 的数目，第三种贡献需要知道先前加入的 $A_i > A_{K_0 + 1}$ 的 $A_i$ 的和。任写一种支持维护前后缀权值和的数据结构即可。

&nbsp;

[AT 提交记录](https://atcoder.jp/contests/abc276/submissions/36249590)

---

## 作者：Find_Yourself (赞：1)

很容易想到分类。

我们可以把 $1$ 到 $i-1$ 的球分为两类，一类是权值小于 $val_i$，另一类是权值大于 $val_i$。

对于第一类，$sum$ 加上小于 $val_i$ 的球的个数乘以 $val_i$。

对于第二类，$sum$ 加上所有大于 $val_i$ 的球的权值。

这显然可以用两个树状数组维护。

最后再乘上总方案数的逆元即可。

复杂度 $O(n\log n)$。

### code:

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5 + 5, mod = 998244353;
ll n, a[N], c[3][N];
int lbt(int x) {
	return x & (-x);
}
void update(int i, ll k, int id) {
	for (; i <= 2e5; i += lbt(i)) c[id][i] = (c[id][i] + k) % mod;
}
ll getsum(int i, int id) {
	ll res = 0;
	for (; i > 0; i -= lbt(i)) res = (res + c[id][i]) % mod;
	return res;
}
ll ksm(ll x, ll y) { //求逆元
	ll res = 1;
	while (y) {
		if (y & 1) res = res * x % mod;
		y >>= 1;
		x = x * x % mod;
	}
	return res;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	ll sum = 0;
	for (ll i = 1; i <= n; ++i) {
		sum = (sum + getsum(a[i], 0) * a[i] % mod * 2 % mod) % mod; //小于
		sum = (sum + (getsum(2e5, 1) - getsum(a[i], 1) + mod) % mod * 2 % mod) % mod; //大于
		sum = (sum + a[i]) % mod; //选了两次都是自己
		cout << sum * ksm(i * i % mod, mod - 2) % mod << endl;
		update(a[i], 1, 0);
		update(a[i], a[i], 1);
	}
	return 0;
}
```


---

## 作者：Y2y7m (赞：1)

考场上差一点就切掉了啊啊啊啊啊。

期望即为价值乘以概率，先考虑概率。

总的情况永远是 $n^2$ 的，非常简易，不用考虑，在输出时计算一下逆元即可。对于选择 $i$, $j$($i\neq j$) 两个球的选法只有两种，就是先选 $i$ 还是先选 $j$。当 $i=j$ 时有一种。

现在计算每个球加入袋子对总价值的影响，设在该球加入袋子中权值不大于该球权值的球数为 $c$，权值大于该球权值的球的权值总和为 $s$，该球权值为 $d$，则增加的价值为：

$$c\times d\times2 + 2\times s+d$$

用权值树状数组和 ```vector``` 维护一下即可（其实你两棵树状数组也可以）。

```cpp
#include <bits/stdc++.h>

using namespace std;
#define int long long
const int maxn=2e5+10;
const int mod=998244353;
int n;
int a[maxn];
int q_pow(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b%2==1)
		{
			ans*=a;
			ans%=mod;
		}
		a*=a;
		a%=mod;
		b/=2;
	}
	return ans;
}
struct node
{
	int t[maxn];
	int lowbit(int x)
	{
		return x&-x;
	}
	void change(int i,int d)
	{
		while(i<=200000)
		{
			t[i]+=d;
			i+=lowbit(i);
		}
	}
	int sum(int i)
	{
		int ans=0;
		while(i)
		{
			ans+=t[i];
			i-=lowbit(i);
		}
		return ans;
	}	
}t1,t2;

vector<int> vec;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int cnt=t2.sum(a[i]);
		if(cnt<0) cnt=0;
		int t=(t1.sum(2e5)-t1.sum(a[i]))*2;
		ans+=t;
		ans+=a[i];
		ans+=cnt*a[i]*2;
		t1.change(a[i],a[i]);
		t2.change(a[i],1);
		ans%=mod;
		cout<<ans*q_pow(i*i%mod,mod-2)%mod<<endl;
	}
	return 0;
}

```


---

## 作者：JiaY19 (赞：0)

### 思路

由于题目中需要我们求的东西是最大值。

可以发现，如果一个数比当前的加入的数小，那么贡献即为当前加入的一个数。

如果一个数比当前的加入的数大，那么贡献即为更大的那个数。

所以相当与我们需要很快的计算出比一个数小的数的个数与比一个数大的数的和。

很容易想到使用权值线段树，来对这个东西进行维护。

具体来说，每个节点存储权值和与个数和两个东西。

查询时就可以直接在线段树上查询即可。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
 
const int N = 200010;
const int M = 200000;
const int mod = 998244353;
 
int n, m, ans;
 
struct Tree
{
    int val , num;
} t[N * 4];
 
inline int read()
{
    int asd = 0 , qwe = 1; char zxc;
    while(!isdigit(zxc = getchar())) if(zxc == '-') qwe = -1;
    while(isdigit(zxc)) asd = asd * 10 + zxc - '0' , zxc = getchar();
    return asd * qwe;
}
 
inline void push_up(int p)
{
    t[p].val = t[p * 2].val + t[p * 2 + 1].val;
    t[p].num = t[p * 2].num + t[p * 2 + 1].num;
    t[p].val %= mod, t[p].num %= mod;
}
 
inline void update(int p , int l , int r , int k)
{
    if(l == r)
        return t[p].val += k, t[p].num++, t[p].val %= mod, t[p].num %= mod, void();
    int mid = (l + r) / 2;
    if(mid >= k) update(p * 2, l, mid, k);
    else update(p * 2 + 1, mid + 1, r, k);
    push_up(p);
}
 
inline int ask1(int p, int l, int r, int ls, int rs)
{
    if(ls <= l && r <= rs)
        return t[p].val;
    int mid = (l + r) / 2 , ans = 0;
    if(ls <= mid)
        ans += ask1(p * 2, l, mid, ls, rs);
    if(rs > mid)
        ans += ask1(p * 2 + 1, mid + 1, r, ls, rs);
    return ans % mod;
}
 
inline int ask2(int p, int l, int r, int ls, int rs)
{
    if (ls <= l && r <= rs)
        return t[p].num;
    int mid = (l + r) / 2, ans = 0;
    if (ls <= mid)
        ans += ask2(p * 2, l, mid, ls, rs);
    if (rs > mid)
        ans += ask2(p * 2 + 1, mid + 1, r, ls, rs);
    return ans % mod;
}
 
inline int power(int x , int y)
{
    int res = 1;
    while(y)
    {
        if(y & 1)
            res = res * x % mod;
        x = x * x % mod, y /= 2;
    }
    return res;
}
 
signed main()
{
    n = read();
    for (int i = 1; i <= n;i++)
    {
        int x = read();
        ans += 2 * x * ask2(1, 1, M, 1, x);
        ans += 2 * ask1(1, 1, M, x + 1, M);
        ans += x, update(1, 1, M, x), ans %= mod;
        printf("%lld\n", ans * power(i * i % mod, mod - 2) % mod);
    }
    return 0;
}
```

---

