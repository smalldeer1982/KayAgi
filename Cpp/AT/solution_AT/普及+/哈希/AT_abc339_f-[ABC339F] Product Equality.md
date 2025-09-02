# [ABC339F] Product Equality

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc339/tasks/abc339_f

$ N $ 個の整数 $ A_1,A_2,\dots,A_N $ が与えられます。  
 以下の条件を満たす整数の組 $ (i,j,k) $ の個数を求めてください。

- $ 1\ \le\ i,j,k\ \le\ N $
- $ A_i\ \times\ A_j\ =\ A_k $

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 1000 $
- $ \color{red}{1\ \le\ A_i\ <\ 10^{1000}} $
 
### Sample Explanation 1

問題文中の条件を満たす $ (i,j,k) $ の組は以下の $ 6 $ 通りです。 - $ (1,2,3) $ - $ (1,3,4) $ - $ (1,4,5) $ - $ (2,1,3) $ - $ (3,1,4) $ - $ (4,1,5) $

### Sample Explanation 2

各整数 $ A_i $ の値が非常に大きくなりうることに注意してください。

### Sample Explanation 3

$ A_i $ の値に重複がありうることに注意してください。

## 样例 #1

### 输入

```
5
2
3
6
12
24```

### 输出

```
6```

## 样例 #2

### 输入

```
11
1
2
3
4
5
6
123456789123456789
123456789123456789
987654321987654321
987654321987654321
121932631356500531347203169112635269```

### 输出

```
40```

## 样例 #3

### 输入

```
9
4
4
4
2
2
2
1
1
1```

### 输出

```
162```

# 题解

## 作者：apiad (赞：5)

当我在尝试我能过都少个点的时候。。AC！

这题大抵上是得用到哈希的了，具体是几哈希，看就是数据水不水了，结果数据不水！甚至弱到爆！

接下来我讲讲我玄学地**单哈希**做法！

我们将每一个输入进来的字符串哈希一下，存到 $a$ 数组中，大概也就是自然的保留了后面一些位数，然后将这个哈希值放入一个 map 里，名为 $mp$，记录同样的哈希值有多少个。

接下来就是 $O(n^2)$ 枚举，答案就加上 $mp_{a_i \times a_j}$。

但是自然溢出会炸！

我们得取一个靠谱的模数。

于是我取了 $11451419198101111$ 这个数，竟然过了。

虽然有些玄学地成分，但是还是可以过的，证明，~~这玩意基本上应该也是对的~~ AT 数据水了。

[link](https://atcoder.jp/contests/abc339/submissions/49974698)。

---

## 作者：Elairin176 (赞：3)

[传送门](https://www.luogu.com.cn/problem/AT_abc339_f)     
## 题意
求出满足 $1\le i,j,k\le n$ 且 $a_ia_j=a_k$ 的 $(i,j,k)$ 组数。     
**$a$ 数据范围为 $10^{1000}$。**
## 解法      
我们这里可以使用类似哈希的方式。   
我们设定一个质数 $p$，那么我们只需要判断 $a_ia_j\bmod p=a_k\bmod p$ 就可以了。但是其哈希冲突的概率极大，所以我们需要双哈希，模数取 $998244353$ 和 $1000000993$。   
最后我们用 map 统计结果即可。      
CODE：   
```cpp
//完整缺省源请见洛谷云剪贴板 jo5j6ogx
cst int N=1e3;
cst ll p1=998244353,p2=1000000993;
string s;
ll a[3][N+10],ans;
int n,len;
umap<ll,ll>mp;
il ll get(ll a,ll b){
	ret a*(p2+10)+b;
}
int main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		len=s.length();
		for(int j=0;j<len;j++){
			a[0][i]=(a[0][i]*10+s[j]-'0')%p1;
			a[1][i]=(a[1][i]*10+s[j]-'0')%p2;
		}
		mp[get(a[0][i],a[1][i])]++;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			ans+=mp[get(a[0][i]*a[0][j]%p1,a[1][i]*a[1][j]%p2)];
		}
	}
	cout<<ans;
	ret 0;
}
```


---

## 作者：FurippuWRY (赞：3)

> $\color{red}1\le A_i\le 10 ^ {1000}$

>$\begin{aligned}N \\ A_1\\A_2\\ \vdots\\ A_N\end{aligned}$

大数字加换行输入，这不明摆着让你用 Python。

当然，$O(n^3)$ 暴力判断明显不可取，还需要一些优化 ~~（赛时用 $O(n^3)$ 然后没过，赛后才 AC，愤怒）~~。

咋做呢，先对数组排序，然后用 `Counter()` 函数求出数组中每个数的数量，定义数组为 $cnt$，然后定义变量 $ans=0$，再开个 $O(n^2)$ 循环，$ans\leftarrow ans + cnt_{a_i\times a_j}$，如果 $a_i\times a_j > a_{n-1}$，跳出循环并输出即可。

$cnt_i$ 表示的是数组 $a$ 中元素 $i$ 的数量（前提是已经执行了 `cnt = Counter(a)`）。

```python
from collections import *
n = int(input())
ans = 0
a = [int(input()) for i in range(n)]
a.sort()
cnt = Counter(a)
for i in range(n):
    for j in range(n):
        ans += cnt[a[i] * a[j]]
        if a[i] * a[j] > a[n - 1] : break
print(ans)
```

---

## 作者：Milthm (赞：2)

很高兴，abc 终于做出了 $6$ 题。

但这题出的其实很奇怪，不明白有什么意义。

看到这个 $a_i\times a_j=a_k$，又看到数据范围这么大，很容易想到哈希。

但是你选一些很小的模数是肯定会炸的。我们考虑把模数放的很大，接近 $10^{18}$ 量级，就可以通过此题。

概率不太会算，但反正出题人没卡单哈希。

### AC code

记得开 `__int128`。

```cpp
#include<bits/stdc++.h>
#define N 1005
#define int __int128
const int mod=(int)(1e18)+3;
using namespace std;
int a[N];
long long ans,n;
map<int,long long>m;
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		string s;
		cin>>s;
		for(int j=0;j<s.size();++j)a[i]=(a[i]*10+(s[j]-'0'))%mod;
		++m[a[i]];
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j)ans+=m[a[i]*a[j]%mod];
	}
	cout<<ans;
	return 0;
}

```






---

## 作者：cjh20090318 (赞：2)

学弟不经意间提出的做法，没想到过了。

~~某些同年级的大佬说用 NTT 做，显然我不会。~~

## 题意

有 $N$ 个数的序列 $A$，设 $S = \{ (i,j,k) \mid 1 \le i,j,k \le N, A_i \times A_j = A_k\}$，求 $\vert S \vert$。

$1 \le N \le 1000, 1 \le A_i \le 10^{1000}$。

## 分析

$A_i \times A_j = A_k$ 是 $A_i \times A_j \equiv A_k\pmod{p}$ 的充分不必要条件。

但是只要 $p$ 合适，如果满足后者那么大概率也满足前者。

所以直接对于每一个 $A_i$ 取模再用 `unordered_map` 存一下每一个数的个数。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<unordered_map>
using namespace std;
typedef long long LL;
const LL mod=99999999999999997;//大质数。
int n;
void read(LL&x){
	x=0;
	char ch=getchar();
	for(;ch<'0' || ch>'9';ch=getchar());
	for(;'0'<=ch && ch<='9';ch=getchar()) x=(x*10+(ch^'0'))%mod;//快速读入大质数。
}
unordered_map<LL,int> M;
LL x[1005];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) read(x[i]),++M[x[i]];//存入 map。
	LL ans=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(M.find((__int128)x[i]*x[j]%mod)!=M.end()) ans+=M[(__int128)x[i]*x[j]%mod];//记得强转类型。
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：1234567890sjx (赞：1)

$a_i$ 很大，所以考虑沿用套路，将每一个 $a_i$ 对一个大质数 $p$ 取模。

然后用一个 `map` 存储下所有的值，枚举两个数 $a_i$，$a_j$ 计算 $a_i\times a_j\bmod p$ 的出现次数即可。

------

$p$ 的取值：因为 $n$ 很小，因此出现哈希冲突的概率也很小，$p$ 在 $10^{16}$ 左右取一个大质数即可。

注意乘法可能会爆 `long long`，需要使用 `__int128`。

[Code](https://atcoder.jp/contests/abc339/submissions/49971674)

---

## 作者：Genius_Star (赞：1)

### 思路：

先试一下 FFT，发现时间复杂度为 $O(N^3 \log N)$，过不去，换一种算法。

考虑哈希，对于每一个大整数，将其取模，开一个桶记录其取模后的值的个数，后面每次枚举 $(i,j)$，只需要判断 $A_i \times A_j$ 在桶中的个数。

但是单哈希在如此大的数据下出错率较高，考虑五哈希法，即对于每一个大整数，记录 $5$ 种取模后的值；对于 $A_i \times A_j$ 五种取模后的值组成的向量 $S$，就是要找到有多少个 $A_k$ 五种取模后组成的向量 $T$ 使得 $S=T$，可以用 ``map`` 实现。

时间复杂度为 $O(N^2 \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=1010,M=6,P=1e8;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,ans;
ll t[M];
vector<ll> s;
vector<ll> a[N];
char c;
map<vector<ll>,ll> p;
ll mod[]={167772161,469762049,754974721,1045430273,1051721729,1053818881};
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=0;j<M;j++)
		  t[j]=0;
		while(1){
			scanf("%c",&c);
			if(c=='\n')
			  break;
			for(int j=0;j<M;j++)
			  t[j]=(t[j]*10ll+c-'0')%mod[j];
		}
		for(int j=0;j<M;j++)
		  a[i].push_back(t[j]);
		p[a[i]]++;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			s.clear();
			for(int k=0;k<M;k++)
			  s.push_back((a[i][k]*a[j][k])%mod[k]);
			ans+=p[s];
		}
	}
	write(ans);
	return 0;
}
```


---

## 作者：NATO (赞：1)

考虑到 $1\le n\le 1000$，我们想到可以暴力枚举 $A_i\times A_j$ 来进行统计，然而数最多 $1000$ 位，那么暴力高精度乘法加上枚举复杂度高达 $O(n^4)$（~~于是我们使用 FFT 优化乘法~~），不能通过本题。

考虑采用哈希的思想，我们将这些数对一个模数取余，那么就可以缩小值域使乘法复杂度可以忽略不计，再暴力枚举取模后的 $A_i\times A_j$ 进行统计即可。

注意出题人似乎卡自然溢出和单哈希，写多模哈希即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll bs=1045141919ll,bs2=998244353ll;
ll n;
string a;
ll ta[1005],ta2[1005];
map<ll,ll>vis;
map<ll,ll>vis2;
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    for(ll i=1;i<=n;++i)
	{
		cin>>a;
		ll hs=0,hs2=0;
		for(ll j=0;j<a.size();++j)
		{
			hs=(hs*10%bs+a[j]-'0')%bs;
			hs2=(hs2*10%bs2+a[j]-'0')%bs2;
		}
		ta[i]=hs;ta2[i]=hs2;
		++vis[hs];++vis2[hs2];
	}
	ll res=0;
	for(ll i=1;i<=n;++i)
		for(ll j=1;j<=n;++j)
			res+=min(vis[ta[i]*ta[j]%bs],vis2[ta2[i]*ta2[j]%bs2]);
	cout<<res;
}
```


---

## 作者：沉石鱼惊旋 (赞：0)

# 题目翻译

$n$ 个大数 $a_i$，找三元组 $(i,j,k)$ 个数满足 $1\leq i,j,k\leq n$ 且 $a_i\times a_j=a_k$。

$n\leq 1000,a_i\leq \color{red}{10^{1000}}$。

# 题目思路

显然可以直接 FFT 高精度乘法。然后喜提 TLE，因为这个 $a_i$ 位数很长并且要跑很多轮乘法。

我们集中注意力，注意到满足 $a_i\times a_j=a_k$ 的必要条件是对于任意模数 $p$ 存在 $(a_i\bmod p)\times(a_j\bmod p)\equiv a_k \pmod p$。

所以我们多写几个模数判一下就好。高精度取模低精度可以一位一位扫过去。

时间复杂度是 $\mathcal O(n^2\log n)$，如果手写个 hash 可以做到 $\mathcal O(n^2)$。

本人组了 $8$ 个自己生日、同学生日和【数据删除】生日以及一些众所周知的大质数。

# 完整代码

[AT submission 49960822](https://atcoder.jp/contests/abc339/submissions/49960822)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int P[] = {20091119,
                 11190119,
                 20102009,
                 998244353,
                 19260817,
                 1000000007,
                 998244853,
                 1145141};
map<vector<ll>, int> mp;
vector<ll> f(string &s)
{
    vector<ll> p;
    for (int i = 0; i < 8; i++)
        p.push_back(0);
    for (char c : s)
    {
        int d = c ^ '0';
        for (int i = 0; i < 8; i++)
            p[i] = (p[i] * 10 + d) % P[i];
    }
    return p;
}
int n;
int ans;
string s[1020];
vector<ll> v[1020];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        // vector<ll> a ;
        v[i] = f(s[i]);
        mp[v[i]]++;
        // for (int j : v[i])
        //     cout << j << " ";
        // cout << endl;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            vector<ll> a = v[i];
            vector<ll> b = v[j];
            for (int k = 0; k < 8; k++)
                a[k] = a[k] * b[k] % P[k];
            // for (int i : a)
            //     cout << i << " ";
            // cout << endl;
            ans += mp[a];
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Link_Cut_Y (赞：0)

## 简要题意

给你 $n$ 个正整数 $a_i$，求满足下面条件的三元组 $(i, j, k)$ 个数：

 - $1 \le i, j, k \le n$。
 
 - $a_i \times a_j = a_k$。
 
注意，$a_i$ 可以达到 $10 ^ {1000}$ 数量级。

## 分析

显然我们不能直接将 $a_i, a_j$ 相乘。这时候用到一个比较常见的 trick：将正整数转化成 $10$ 为底的哈希。这时候，若有 $a_i \times a_j = a_k$，则他们的哈希值也一定满足这样的关系。

转成哈希之后，用 map 存一下就可以了。这样可以做到 $O(n ^ 2)$ / $O(n ^ 2 \log n)$。

模数真的难弄，找多了超时，找少了一直挂两个点。最后选择了 $10 ^ {13} + 37$，$10 ^ {16} + 61$ 两个模数。

```cpp
using PII = pair<int, int>;
int p[] = {(long long)1e13 + 37, (long long)1e16 + 61};
int n, ans; map<PII, int> bin;
vector<int> a[1010];
void read(vector<int> &s) {
	char ch = getchar(); vector<int> vec;
	for (; ch < '0' or ch > '9'; ch = getchar());
	for (; ch >= '0' and ch <= '9'; ch = getchar())
		for (int i = 0; i < 2; i ++ )
			s[i] = (s[i] * 10 % p[i] + (ch - '0')) % p[i];
}
int check(vector<int> a, vector<int> b) {
	int B = bin[make_pair(0, 1ll * ((i128)a[0] * (i128)b[0]) % p[0])];
	for (int i = 1; i < 2; i ++ )
		if (bin[{i, 1ll * ((i128)a[i] * (i128)b[i]) % p[i]}] != B)
			 return 0; return B;
}
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i ++ ) a[i].resize(7);
	for (int i = 1; i <= n; i ++ ) read(a[i]);
	for (int i = 1; i <= n; i ++ )
		for (int j = 0; j < 2; j ++ )
			bin[{j, a[i][j]}] ++ ;
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= n; j ++ )
			ans += check(a[i], a[j]);
	printf("%lld\n", ans); return 0;
}
```

---

## 作者：DerrickLo (赞：0)

考虑到若 $a\times b=c$ 那么 $(a\bmod p)\times (b\bmod p)=c\bmod p$。

那我们把 $a_i$ 都对一个大质数 $p$ 取模，然后再看看有多少个 $(i,j,k)$ 满足 $(a_i\bmod p)\times (a_j\bmod p)=a_k\bmod p$，这可以用一个 `map` 记录一下。

注意到一个模数可能被卡，所以我们用多一些模数，这样就很难被卡了。

```cpp
#include<bits/stdc++.h>
#define mod1 998244353
#define mod2 1000000007
#define mod3 19260817
#define int long long
using namespace std;
int n,ans,a[1005],b[1005],c[1005];
string s;
struct dd{
	int x,y,z;
	friend bool operator<(const dd&a,const dd&b){
		if(a.x!=b.x)return a.x<b.x;
		if(a.y!=b.y)return a.y<b.y;
		return a.z<b.z; 
	}
};
map<dd,int>mp;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		int now1=0,now2=0,now3=0;
		for(int i=0;i<s.size();i++)now1=now1*10+s[i]-'0',now1%=mod1;
		for(int i=0;i<s.size();i++)now2=now2*10+s[i]-'0',now2%=mod2;
		for(int i=0;i<s.size();i++)now3=now3*10+s[i]-'0',now3%=mod3;
		mp[{now1,now2,now3}]++;
		a[i]=now1,b[i]=now2,c[i]=now3;
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
		ans+=mp[{a[i]*a[j]%mod1,b[i]*b[j]%mod2,c[i]*c[j]%mod3}];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

## 思路

因为曾经在某一场比赛中做到了 U235464，所以一眼看出了答案。

可以考虑先哈希一下这个数，然后用 map 来进行统计，这里说的三元组对是否有重复没有要求，所以就不用考虑相同数字怎么办，有一怎么办。

然后就是考虑哈希的问题，这个题目卡了很多的常见的哈希，这里我推荐大家使用大整数哈希，我用的是 $10^6+1029$，单模就过了。

## 代码

```cpp
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define per(i, l, r) for (int i = (r); i >= (l); i--)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
using namespace std;
using i64 = long long;
const i64 maxn = 10000, mod = 1e16 + 1029;
map<i64, i64> mp;
i64 a[maxn];
int mian() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  cin >> n;
  rep(i, 1, n) {
    string s;
    cin >> s;
    i64 x = 0;
    rep(i, 0, s.size() - 1) {
      x = x * 10 + s[i] - '0';
      x %= mod;
    }
    mp[x]++;
    a[i] = x;
  }
  i64 ans = 0;
  rep(i, 1, n) {
    rep(j, 1, n) {
      ans += mp[1ll * (((__int128)a[i] * (__int128)a[j] ) % mod)];
    }
  }
  cout << ans << "\n";
  return 0;
}
```

---

## 作者：fcy20180201 (赞：0)

## 思路
诡异的乱搞题，~~罚时靠阳寿~~。

如果 $a_i \le 10^9$，可以把所有 $a_k$ 丢进 `map` 里，然后暴力循环 $i,j$，在 `map` 里查询 $a_k$ 的数量。

回到原题 $a_i \le 10^{1000}$，如果高精度肯定超时。现在有两条路：

- FFT
- 乱搞

~~不会 FFT 的蒟蒻（me）当然选择乱搞~~。

可以哈希，算出每个 $a_i$ 对几个模数取模的余数。判断 $a_i \times a_j$ 是否等于 $a_k$ 时，用 $a_i$ 的余数和 $a_j$ 的余数**对应相乘**，看看是否依次等于 $a_k$ 的对应余数。知道怎么判相等之后就可以用 $a_i\le 10^9$ 的做法了。

## 代码
蒟蒻选择了三个模数 $131,998244353,10^9+7$。

**提醒：十年 OI 一场空，不开 long long 见祖宗。**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int m1=131;
const int m2=998244353;
const int m3=1e9+7;
int n,ans;
struct mods{
	int a,b,c;
}A[1005];
bool operator <(const mods &x,const mods &y){return x.a==y.a?(x.b==y.b?x.c<y.c:x.b<y.b):x.a<y.a;}
//一定要重载结构体运算符，否则可能会出现未知问题
map<mods,int>mp;
char s[1005];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		int a=0,b=0,c=0;
		for(int j=0;s[j];j++)
			a=(a*10+(s[j]^48))%m1,b=(b*10ll+(s[j]^48))%m2,c=(c*10ll+(s[j]^48))%m3;
		//算出余数
		A[i]={a,b,c},mp[A[i]]++;//在 map 里计数
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)
		ans+=mp[{A[i].a*A[j].a%m1,1ll*A[i].b*A[j].b%m2,1ll*A[i].c*A[j].c%m3}];
	//如果分别相等，就大概率是真的相等
	printf("%d",ans);
	return 0;
}
```

---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc339_f)
### 题解
第一次 AK ABC，必须写题解纪念一下。

想到了其实不难，关键在于你能不能想到。。。

看到 $a_i$ 如此大，考虑用多模数来检验（就是满足条件的对 $(i,j,k)$，在模上任意数是也一定成立，反过来用多模数可以减小不满足的概率）。

这里由于作者脑子不好使，就选模数 $10^9+7,10^9+9,998244353,10^9+21$ 了。

于是我们用一个 map 存储每一个数在模上 $4$ 个模数后的结果作为下标统计数量，然后 $O(n^2)$ 枚举 $i$ 和 $j$，第三个数用 $a_i\times a_j$ 算出并模上 $4$ 个模数后的结果做下标求出 $a$ 中与这个数相同的数量。

总结一下，其实就是把 $a$ 换成 $\{a\bmod m_1,a \bmod m_2,a \bmod m_3,a \bmod m_4\}$ 来求解（$m_1,m_2,m_3,m_4$ 是 $4$ 个模数）。
### 代码
```
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <ctime>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = in.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = in.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = in.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
const int N = 1010;
int n;
int p[5] = {0,(int)(1e9 + 7),(int)(1e9 + 9),998244353,(int)(1e9 + 21)},cnt = 4;
char s[N];
int a[N][5];
using type = pair <PII,PII>;
type v[N];
map <type,int> mp;
int main () {
	scanf ("%d",&n);
	for (int i = 1;i <= n;i++) {
		scanf ("%s",s + 1);
		int len = strlen (s + 1);
		for (int k = 1;k <= cnt;k++) {
			int res = 0;
			for (int j = 1;j <= len;j++) res = ((LL)res * 10 + s[j] - '0') % p[k];
			a[i][k] = res;
		}
		v[i] = {{a[i][1],a[i][2]},{a[i][3],a[i][4]}};
		mp[v[i]]++;
	}
	LL ans = 0;
	bitset <N> tmp;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= n;j++) {
			vector <int> vec;
			for (int k = 1;k <= 4;k++) vec.pb ((LL)a[i][k] * a[j][k] % p[k]);
			type tmp = {{vec[0],vec[1]},{vec[2],vec[3]}};
			if (mp.find (tmp) != mp.end ()) ans += mp[tmp];
		}
	}
	printf ("%lld\n",ans);
	return 0;
}
```

---

## 作者：FFTotoro (赞：0)

第一次 AK ABC，写个题解纪念一下。

大数运算判断相等，果断考虑哈希。

具体地，把每个数对质数 $p$ 取模，使用 `__gnu_pbds::gp_hash_table` 存储每个数的出现次数；然后枚举两个乘数，在哈希表中查找它们的积的数量，加入答案即可。

但是单模哈希容易被卡，于是本人使用 $3$ 个质数 $p_1=10^9+9,p_2=1610612741,p_3=10^8+81$ 进行**三模哈希**，卡卡常可以通过。

令 $a_i$ 在十进制下的位数为 $l_i$，时间复杂度 $O(n^2+\sum l_i)$，带个 $3$ 的常数。

放代码：

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define int long long
using namespace std;
const int p[3]={1000000009,1610612741,100000081};
int H(string s,int x){
  int c=0;
  for(char i:s)
    ((c*=10)+=i-48)%=p[x];
  return c;
}
main(){
  ios::sync_with_stdio(false);
  int n,c=0; cin>>n;
  vector<string> a(n);
  for(auto &i:a)cin>>i;
  vector<array<int,3> > h(n);
  __gnu_pbds::gp_hash_table<int,int> m[3];
  for(int i=0;i<n;i++)
    for(int j=0;j<3;j++)
      m[j][h[i][j]=H(a[i],j)]++;
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++){
      int s=1000;
      for(int k=0;k<3;k++)
        s=min(s,m[k][h[i][k]*h[j][k]%p[k]]);
      c+=s;
    }
  cout<<c<<endl;
  return 0;
}
```

---

## 作者：Starrykiller (赞：0)

纪念一下首次 AK ABC。

给定长度为 $N$ 的序列 $A$，求满足以下条件的无序三元组 $(i,j,k)$ 的数量：

- $1\leq i,j,k\leq N$
- $A_i\cdot A_j=A_k$

$N\leq 10^3$，$A_i\leq 10^{1000}$。

不难想到 hash。理由是若 $a\cdot b\equiv c\pmod p$，对多个 $p$ 成立，则大概率有 $a\cdot b=c$ 成立。

可以被精心构造的数据卡掉，不过可以用随机模数的方式提高正确率。

然后开个 map 记录一下贡献即可。

```cpp
#include <bits/stdc++.h>
#include <atcoder/all>

using namespace std;

#define int long long 
using ll=atcoder::modint998244353;

constexpr int p1=998244353, p2=1e9+7, p3=19260817, p4=1e9+9;

constexpr int MAXN=1e3+10;
string s[MAXN]; int n; 
struct node {
    int a, b, c, d;
    node(const string& s) {
        a=b=c=d=0;
        for (auto i: s) {
            int ch=i-'0';
            a=(a*10+ch)%p1;
            b=(b*10+ch)%p2;
            c=(c*10+ch)%p3;
            d=(d*10+ch)%p4;
        }   
    }
    node() {
        a=b=c=d=0;
    }
} a[MAXN]; 

bool operator==(node a, node b) {
    return a.a==b.a&&a.b==b.b&&a.c==b.c&&a.d==b.d;
}
node operator*(node a, node b) {
    node c;
    c.a=a.a*b.a%p1;
    c.b=a.b*b.b%p2;
    c.c=a.c*b.c%p3;
    c.d=a.d*b.d%p4;
    return c;
}
bool operator<(node a, node b) {
    if (a.a!=b.a) return a.a<b.a;
    if (a.b!=b.b) return a.b<b.b;
    if (a.c!=b.c) return a.c<b.c;
    return a.d<b.d;
}
map<node,int> mp;


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin>>n; 
    for (int i=1; i<=n; ++i) {
        cin>>s[i];
        a[i]=node(s[i]);
    }
    for (int i=1; i<=n; ++i)
        for (int j=1; j<=n; ++j) mp[a[i]*a[j]]++;
    int ans=0;
    for (int i=1; i<=n; ++i) {
        if (mp.count(a[i])) ans+=mp[a[i]];
    }
    cout<<ans;

    
}
```

---

## 作者：WilliamFranklin (赞：0)

### 主要思路

看到这么大的数，我直接晕了过去。

但是回想一下之前做的题，有这么大数的，还记得做法，只是忘了是哪道题。

考虑将这一堆数都对于某几个质数取模，然后判断 $A_i \times A_j$ 对于这些质数取模，是否分别等于 $A_k$ 对于这些质数取模即可。

看下数据范围，发现枚举 $i$ 和 $j$ 是完全够了的，那么 $k$，我们可以用 `map` 来存，这里请看下下面的代码，了解一下。

我用的是 `bitset`，这样是更严谨的，不过某些人直接累计最小值不是不行，只是不太严谨，但是赛场上，卡哈希有什么好玩的呢？

细节看下代码吧。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 1005, mod1 = 1e9 + 7, mod2 = 998244353, mod3 = 13331;
int n;
long long a1[N], a2[N], a3[N];
map<long long, bitset<N> > mp;
map<long long, bitset<N> > mp1;
map<long long, bitset<N> > mp2;
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n;
	For(i, 1, n) {
		string s;
		cin >> s;
		int x = s.size() - 1;
		For(j, 0, x) {
			a1[i] = a1[i] * 10 % mod1;
			a2[i] = a2[i] * 10 % mod2;
			a3[i] = a3[i] * 10 % mod3;
			a1[i] = (a1[i] + s[j] - '0') % mod1;
			a2[i] = (a2[i] + s[j] - '0') % mod2;
			a3[i] = (a3[i] + s[j] - '0') % mod3;
		}
	}
	For(i, 1, n) {
		mp[a1[i]][i] = 1;
		mp1[a2[i]][i] = 1;
		mp2[a3[i]][i] = 1;
	}
	long long ans = 0;
	For(i, 1, n) {
		For(j, i + 1, n) {
			long long m1 = a1[i] * a1[j] % mod1, m2 = a2[i] * a2[j] % mod2, m3 = a3[i] * a3[j] % mod3;
			bitset<N> b = mp[m1];
			b &= mp1[m2];
			b &= mp2[m3];
			ans += b.count();
		}
	}
	ans *= 2;
	for (int i = 1; i <= n; i++) {
		int j = i;
		long long m1 = a1[i] * a1[j] % mod1, m2 = a2[i] * a2[j] % mod2, m3 = a3[i] * a3[j] % mod3;
		bitset<N> b = mp[m1];
		b &= mp1[m2];
		b &= mp2[m3];
		ans += b.count();
	}
	cout << ans;
	return 0;
}
```

### 谢谢观看

---

