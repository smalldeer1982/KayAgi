# [ABC191F] GCD or MIN

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc191/tasks/abc191_f

黒板に $ N $ 個の整数 $ A_1,\ A_2,\ A_3,\ \dots,\ A_N $ が書かれています。  
 あなたは次の操作を $ N\ -\ 1 $ 回行います。

- 黒板に書かれている数を $ 2 $ つ選んで消す。消した数を $ x $ と $ y $ として、$ \gcd(x,\ y) $ と $ \min(x,\ y) $ のどちらか一方を黒板に書く

$ N\ -\ 1 $ 回の操作を終えた後、黒板にはただ一つの整数が残りますが、この整数として考えられるものはいくつありますか ?

## 说明/提示

### 制約

- $ 2\ \le\ N\ \le\ 2000 $
- $ 1\ \le\ A_i\ \le\ 10^9 $
- 入力は全て整数

### Sample Explanation 1

$ 3 $ と $ 6 $ が、最後に黒板に残る整数として考えられるものです。 例えば以下のような操作をすることで $ 3 $ が残ります。 - $ 9 $ と $ 12 $ を選んで黒板から消し、$ \gcd(9,\ 12)\ =\ 3 $ を黒板に書く - $ 6 $ と $ 3 $ を選んで黒板から消し、$ \min(6,\ 3)\ =\ 3 $ を黒板に書く また、以下のような操作をすることで $ 6 $ が残ります。 - $ 6 $ と $ 12 $ を選んで黒板から消し、$ \gcd(6,\ 12)\ =\ 6 $ を黒板に書く - $ 6 $ と $ 9 $ を選んで黒板から消し、$ \min(6,\ 9)\ =\ 6 $ を黒板に書く

### Sample Explanation 2

$ 2 $ が、黒板に残る数として考えられる唯一の数です。

### Sample Explanation 3

$ 1,\ 2,\ 3,\ 4,\ 6,\ 7,\ 27 $ が最後に黒板に残る整数として考えられるものです。

## 样例 #1

### 输入

```
3
6 9 12```

### 输出

```
2```

## 样例 #2

### 输入

```
4
8 2 12 6```

### 输出

```
1```

## 样例 #3

### 输入

```
7
30 28 33 49 27 37 48```

### 输出

```
7```

# 题解

## 作者：Yizhixiaoyun (赞：7)

[博客园食用](https://www.cnblogs.com/yizhixiaoyun/p/17385793.html)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc191_f)

## 题目分析

我们发现，$\text{min}$ 操作实际上就是把两数当中较大的那个删除，较小的那个数不受影响，所以用最小的数删还是用另一个数删是无区别的。

一个性质：

$$\gcd(x,y) \le \min(x,y)$$

不管 $a_{min}$ 是原来的还是在 $\text{gcd}$ 操作后新生成的，所以无论什么时候删，该删的数都能删掉。

问题简化为：取一些数的 $\text{gcd}$，然后用最小的数删，删到只剩一个 $\text{gcd}$。

所以我们只需要求去除子集最大公因数的个数即可。那么对于每个 $a_i$ 都分解因数，对于每个因数，记录有哪些 $a_i$ 包含它。然后再遍历一遍，比对此因数是否与其对应的 $a_i$ 最大公因数相等即可。

## 贴上代码

```cpp
#include<bits/stdc++.h>
// #define int long long
#define debug puts("Shiina_Mashiro_kawaii")
#define ok puts("YES")
#define no puts("NO")
#define inf 1e9
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
const int maxn=2010;
int n;
int ans;
int a[maxn];
map<int,int> mp;
inline void init(){
	n=read();
	for(register int i=1;i<=n;++i) a[i]=read();
	sort(a+1,a+n+1);
}
int main(){
	init();
	for(register int i=1;i<=n;++i){
		for(register int j=1;j<=sqrt(a[i]);++j){
			if(a[i]%j==0){
				if(j<=a[1]) mp[j]=__gcd(mp[j],a[i]);
				if(a[i]/j<=a[1]) mp[a[i]/j]=__gcd(mp[a[i]/j],a[i]); 
			}
		}
	}
	map<int,int>::iterator it;
	for(it=mp.begin();it!=mp.end();++it){
		if(it->first==it->second) ans++;
	}
	printf("%d\n",ans);
}
```

---

## 作者：SalN (赞：4)

[linkqwq](https://www.luogu.com.cn/problem/AT_abc191_f)

### 题目大意

给定 $n$ 个整数 $a_1,\dots,a_n$，每次选择两个数 $x,y$ 去掉并加入 $\gcd(x,y)$ 或者 $\min(x,y)$，求最后一个数有多少种取值。

$2\leq n\leq 2000,1\leq a_i\leq 10^9$

----

### 题目解法

只有「删除 $x,y$ 加入 $\gcd(x,y)$」的情况，答案显然是所有数的 $\gcd$。

「删除 $x,y$ 加入 $\min(x,y)$」这种操作我们可以理解成「删去 $\max (x,y)$」。意思是，对于一个序列，除了 $\min\{a_i\}$ 以外的其它任何数肯定都可以随便被删除。

我们先考虑一个弱化版问题，可以「删除 $x,y$ 加入 $\gcd(x,y)$」或者「删除 $x$」。这种情况下，任意滴取一些数算其 $\gcd$ 都是合法的捏，不选的数删除就好了。

我们再考虑加上了「不能删除 $\min\{a_i\}$」的约束的情况。这个时候，如果算出来的最终值 $k>\min\{a_i\}$ ，此时 $\min\{a_i\}$ 仍然存在（不然怎么比最小值大嘛），无法正常的删除，因为祂不是最小值啊。因为序列的最小值肯定越来越小，所以这种情况不能通过调整顺序和操作来避免。反过来，如果 $x\leq \min\{a_i\}$ 那么显然很合法捏。

我们考虑弱化版问题中一个数 $k$ 可不可以成为最终答案，假设 $k$ 的倍数有 $a_{p_1},a_{p_2},...,a_{p_n}$。合法序列的 $\gcd=k$，因为任何的合法序列跟 $k$ 的倍数继续取 $\gcd$ 仍然是 $k$，所以 $\gcd\{a_{p_i}\}=k$ 相当于 $k$ 就合法。实际算的时候枚举 $a_i$ 的约数就可以做到 $O(\sum\sqrt a_i)$ 了。

具体而言，用 $g[t_0]$ 表示 $t_0$ 的倍数的 $\gcd$。对于每一个 $a_i$ 枚举其因数 $t$，使得 $g[t]=\gcd(g[t],a_i)$，最后算 $g[t_0]=t_0(t_0\leq\min\{a_i\})$ 的个数即可。复杂度 $O(n\sqrt a_i)$，map 的话再带一个 $\log$。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=2023, inf=1e9;
int n, a[N], m=inf, ans;
map<int,int> g;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for(int i=1; i<=n; ++i) {
		cin >> a[i];
		m=min(a[i],m);
	}
	for(int i=1; i<=n; ++i)
		for(int j=1; j*j<=a[i]; ++j)
			if(a[i]%j==0) {
				g[j]=__gcd(g[j],a[i]);
				g[a[i]/j]=__gcd(g[a[i]/j],a[i]);
			}
	map<int,int>::iterator it;
	for(it=g.begin(); it!=g.end(); ++it)
		if(it->first<=m) ans+=(it->first==it->second);
	cout << ans;
	return 0;
}
```


---

## 作者：DengDuck (赞：2)

这是我在洛谷通过的 $900$ 道题目，写一手题解纪念几下。

我们发现操作二可以看成删除较大的数。

我们可以把所有操作都看成一些数取最小公约数然后取最小值。

我们观察被选中的数字，发现有以下性质：

- 首先你需要是某一项的因数。
- 对于所有你的倍数，他们的最小公约数是你，换句话，除去你，他们是互质的。
- 你必须小于等于最小的数字。

三条的证明分别是：

- 最小公约数最起码得是个因数。
- 如果他们不不互质，他们的最小公约数才可能出现，你不可能出现，轮不到你。
- 你要么由最小的数字和其他数字取最小公因数构成，则你必然小于等于这个数字，要么不由这个数字构成，此时你必须小于等于最小的数字，不然最后删数字你不是最小的。

因此我们可以考虑暴力筛因数，然后根据以上性质判断，知道这些性质，代码是很好些的。

代码是参考别人的。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=1e5+5;
LL n,a[N],mn=1e18,ans;
map<LL,LL>ma;
LL gcd(LL x,LL y)
{
	if(!y)return x;
	return gcd(y,x%y);
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		mn=min(a[i],mn);
	}
	for(int i=1;i<=n;i++)
	{
		for(LL j=1;j*j<=a[i];j++)
		{
			if(a[i]%j==0)
			{
				if(j<=mn)ma[j]=gcd(ma[j],a[i]);
				if(a[i]/j<=mn)ma[a[i]/j]=gcd(ma[a[i]/j],a[i]);
			}
		}
	}
	for(pair<LL,LL> i:ma)
	{
		if(i.first==i.second)ans++;
	}
	cout<<ans<<endl;
}
```

---

## 作者：eric0928 (赞：2)

# [ABC191F] GCD or MIN

## 题目大意
有 $n$ 个自然数，每次可以去掉两个自然数 $x$，$y$，并添上 $\gcd(x,y)$ 或 $\min(x,y)$。问最后留下来的那个数有多少种可能。

## 题意分析
关于 $\gcd(x,y)$ 与 $\min(x,y)$ 有一个性质
$$\gcd(x,y) \le \min(x,y)$$
这个性质也是非常的好理解，$\min(x,y)$ 就是在 $x$ 与 $y$ 中取较小的一个，而 $\gcd(x,y)$ 则是取 $x$，$y$ 的最大公因数。众所周知 $x$ ，$y$ 的最大公因数肯定是小于或等于它们之中任何一个的（不然叫什么最大公因数）
所以就可以得出上面的结论

因此，我们就可以运用这个性质，来把题目改成这样：
有 $n$ 个自然数，取一些数的最大公因数后，在数组里找到一个 $a_i$ 为数组里最小的数，若之前没有一样的，$ans$ 增加 $1$。

## 贴上代码
~~~cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int>f;
int a[2005];
int minn=0x3f3f3f3f;
int ans;
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		minn=min(minn,a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j*j<=a[i]&&j<minn;j++)
		{
			if(a[i]%j==0)
			{
				if(f[j]==0)
				{
					f[j]=a[i];
				}
				else
				{
					f[j]=__gcd(f[j],a[i]);
				}
				if(a[i]/j<minn)
				{
					int x=a[i]/j;
					if(f[x]==0)
					{
						f[x]=a[i];
					}
					else
					{
						f[x]=__gcd(f[x],a[i]);
					}
				}
			}
			
		}
	}
	
	for (auto i=f.begin();i!=f.end();i++){
		ans+=(i->first==i->second);
	}
	printf("%d\n",ans+1);
	return 0;
}
~~~



---

## 作者：Claire0918 (赞：2)

显然，结果最大为 $\displaystyle \min_{i = 1}^{n}\{a_i\}$，因为 $\gcd(x, y) \leq \min(x, y), \forall x, y \in \mathbb{N}_+$。

记 $r = \displaystyle \min_{i = 1}^{n}\{a_i\}$。

若结果小于 $r$，则必有多个数用 $\gcd$ 合并。可以预处理因数。

我们设 $b_1, b_2, b_3 \ldots b_n$ 都有因数 $d$，且 $d \leq r$，则 $d$ 是一个新的结果。

预处理因倍关系，统计符合条件的答案数量即可。

Code: 

```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 2000 + 10;

int n;
long long a_min = 1e9, res = 0;
map<long long, vector<long long> > hsh;
// 第一项为因数，第二项为所有该因数在序列中的倍数。

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		long long a;
		scanf("%lld", &a);
		a_min = min(a_min, a);
		// 预处理一个数的因数。
		for (long long j = 1; j * j <= a; j++){
			if (!(a % j)){
				hsh[j].push_back(a);
				if (j != a / j){
					hsh[a / j].push_back(a);
				}
			}
		}
	}
	// 统计答案。
	for (auto x: hsh){
		if (x.first > a_min){
			break;
		}
		long long d = x.second[0];
		for (auto y: x.second){
			d = __gcd(d, y);
		}
		if (d == x.first){
			res++;
		}
	}
	printf("%lld", res);

return 0;
}
```

---

## 作者：high_sky (赞：1)

### 思路
其实不难看出，`最小值` 操作的结果就是删去一个数（这应该谁都知道）。且只有最小值不能被删去，但是 `最大公因数` 的操作也是**单调递减**的。所以最好后一个数的大小一定 $\leq \min{a_i}$。

那么，问题转换为：从 $n$ 个数中选去除一个子集的最大公因数，问你有多少种结果 $\leq \min{a_i}$。

注：因为一旦从一个子集中最大公因数一个 $\leq \min{a_i}$ 的数。接下来就是不把他们全部取一个最小值，这样就可以实现上述操作了。

那么，问题来了：**如何求子集最大公因数的个数?**

我们知道：**对于一个数 $a_i$，包含它的最大公因数的最终结果一定是它的因子。**

我们可以一开始对每个数 $a_i$ 求解他的因数。对于每个因数 $f_i$，我们用 `map` 存下来有哪些 $a_i$ 中含有他（所以他们之间含有公共因子 $f_i$）。然后枚举因数，对对应的 $a_i$ 求一遍最大公因数，如果等于 $f_i$，答案就可以加一了。
### Code
```cpp
#include<iostream>
#include<algorithm>
#include<map>
using namespace std;
#define ll long long
const int maxn = 2000 + 5;
const int mod = 1e9 + 7;
map<ll,vector<ll>> q;
int main()
{
    ios::sync_with_stdio(false);
    int n; cin >> n;
    ll d = 1e9;
    for (int i = 1 ; i <= n ; i++){
        ll x ; cin >> x;
        d = min(d , x);
        for (ll j = 1 ; j * j <= x ; j++){
            if (x % j == 0){
                q[j].push_back(x);
                if (j * j != x) q[x/j].push_back(x);
            }
        }
    }
    int ans = 0;
    for (auto g : q){
        if (g.first > d) break;
        ll gcd = g.second[0];
        for (auto k : g.second) gcd = __gcd(gcd , k);
        if (gcd == g.first) ans++;
    }
    cout << ans << endl;
    return 0;
}

```
我绝对不会告诉你选哪一种语言才会对 :)

---

## 作者：tabelog_AFO (赞：1)

[ABC191F] GCD or MIN / [洛谷](https://www.luogu.com.cn/problem/AT_abc191_f) / [AtCoder](https://atcoder.jp/contests/abc191/tasks/abc191_f)

[更好的阅读体验](https://www.luogu.com.cn/blog/tabelog/solution-at-abc191-f)

#### 题目大意
有 $n$ 个整数，你每次可以将其中两个数 $x,y$ 去掉，并添上 $\gcd(x,y)$ 或 $\min(x,y)$ 。问最后剩下的一个数有多少种可能的取值。

#### 思路
首先要知道 $\gcd(x,y) \leqslant \min(x,y)$ ，这个比较显然，但是很重要。因为上述性质也就决定了答案不可能超过 $\min(A_i)$ 。

那我们思考一下对于小于 $\min(A_i)$ 的数怎么判断是否能取到呢？

由于小于 $\min(A_i)$ ，因此不可能直接通过 $\gcd$ 取到，假设我们有一个数 $x \le \min(A_i)$ ，那么 $x$ 一定是 $A$ 的子集的 $\gcd$ ，然后再通过和其他数取 $\min$ 得到。

而且一个比较好的性质就是，如果我们已经通过一些子集的 $\gcd$ 获得了 $x$ ，那么我们在让它和其他含有 $x$ 这个因子的数做 $\gcd$ ，那么还一定是 $x$ ，因为 $\gcd(k \times x,x) = x, k \in N^{+}$ 。所以如果有一个 $A$ 的子集的 $\gcd$ 为 $x$ ，那么 $A$ 中所有含 $x$ 这个因子的数的 $\gcd$ 也必定是 $x$ 。

那考虑按顺序处理，对每一个 $a_i$ 处理一下 $a_i$ 的因数。设 $f_x$ 表示到目前为止含因子 $x$ 的数的 $\gcd$ ，最后看一下有多少 $f_x = x$ 的 $x$ 即可，由于值域较大，因此要拿`map`存。

#### 复杂度
- 时间复杂度 $\Theta(N^2)$
- 空间复杂度 $\Theta(N)$

#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=200005;
int n,a[N],maxn=0x3f3f3f3f;
map<int,int>f;
map<int,int>::iterator it;
int main() {
    cin>>n;
    for (int i=1;i<=n;i++) cin>>a[i],maxn=min(maxn,a[i]);
    for (int i=1;i<=n;i++) {
        for (int j=1;j*j<=a[i]&&j<maxn;j++) {
            if (a[i]%j==0) {
                if (f[j]==0) f[j]=a[i];
                else f[j]=__gcd(f[j],a[i]);
                if (a[i]/j<maxn) {
                    int x=a[i]/j;
                    if (f[x]==0) f[x]=a[i];
                    else f[x]=__gcd(f[x],a[i]);
                }
            }
        }
    }
    int ans=0;
    for (it=f.begin();it!=f.end();it++)
        ans+=(it->first==it->second);
    printf("%d\n",ans+1);
    return 0;
}
```

---

