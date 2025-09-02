# [ABC252D] Distinct Trio

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc252/tasks/abc252_d

長さ $ N $ の数列 $ A=(A_1,A_2,\ldots,A_N) $ が与えられます。  
 以下の $ 2 $ 条件をともに満たすような整数の組 $ (i,j,k) $ の個数を求めてください。

- $ 1\leq\ i\ \lt\ j\ \lt\ k\ \leq\ N $
- $ A_i,A_j,A_k $ は相異なる

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 2\times\ 10^5 $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

条件を満たす整数の組 $ (i,j,k) $ は $ (1,2,3),(1,3,4) $ の $ 2 $ つです。

## 样例 #1

### 输入

```
4
3 1 4 1```

### 输出

```
2```

## 样例 #2

### 输入

```
10
99999 99998 99997 99996 99995 99994 99993 99992 99991 99990```

### 输出

```
120```

## 样例 #3

### 输入

```
15
3 1 4 1 5 9 2 6 5 3 5 8 9 7 9```

### 输出

```
355```

# 题解

## 作者：chengning0909 (赞：3)

# abc 252 d

[AT 链接](https://atcoder.jp/contests/abc252/tasks/abc252_d)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc252_d)

## 题意

给定长度为 $n$ 的序列 $a = (a_1, a_2, \dots, a_n)$，请你求出满足以下条件的三元组的数量：

- $1 \le i < j < k \le n$。

- $a_i, a_j, a_k$ 均不相同。

$3 \le n \le 2 \times 10 ^ 5$。

$1 \le a_i \le 2 \times 10 ^ 5$

## 思路

这道题目可以转换成这样：

求出满足 $1 \le i, j, k \le n$ 且 $a_i < a_j < a_k$ 的三元组数量。

那么，我们可以直接枚举中间的 $a_j$ 的值。

令 $s_i$ 表示在序列 $a$ 中，小于等于 $i$ 的数字数量，$cnt_i$ 表示在序列 $a$ 中，$i$ 的出现次数，$V$ 表示最大的 $a_i$。

那么对于每个 $a_j$，它对答案的贡献就是 $cnt_i \times s_{i - 1} \times (s_{V} - s_i)$。

统计答案即可。

时间复杂度为 $O(n + V)$，$V$ 表示最大的 $a_i$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, INF = 2e5;

int n, a[N], cnt[N], s[N];
long long ans;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    cnt[a[i]]++;  // 统计出现次数
  }
  for (int i = 1; i <= INF; i++) {
    s[i] = s[i - 1] + cnt[i];  // 前缀和
  }
  for (int i = 1; i <= INF; i++) {
    ans += 1ll * cnt[i] * s[i - 1] * (s[INF] - s[i]);  // 统计答案
  }
  cout << ans;
  return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 思路
我们可以用一个正难则反的方法，那么我们就可以用总的方法减去重复两个的以及重复三个的，那么我们就能发现总的方法就是 $n\times (n-1)\times(n-2)\div 6$ 那么我们就可以统计一个重复的次数为 $mp_i$，那么我们对于每一个不同的 $a_i$ 只需要减去 $mp_i\times (mp_i-1)\times(mp_i-2)\div 6+(mp_i-1)\times(mp_i-1)\times(n-mp_i)\div 2$即可，前者为重复三个后者为重复两个，因为要满足 $i<j<k$ 所以我们要除以 $6$ 以及除以 $2$ 至于为什么后面一组还要乘上 $n-mp_i$ 是因为我们这些剩下的数一定能找一个位置插进去（记住要标记一下是否在值为 $a_i$ 时更新过答案避免重复）。
# 代码
```
#include <bits/stdc++.h>
using namespace std ;
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define int long long
#define fire signed
int n,a[200100];
map<int,int>mp;
map<int,bool>f;
fire main() {
	cin>>n;
	rep(i,1,n) cin>>a[i],mp[a[i]]++;
	int res=n;
	int ans=n*(n-1)*(n-2);
	rep(i,1,n) {
		if(mp[a[i]]>=2&&!f[a[i]]) {
			ans-=(mp[a[i]]*(mp[a[i]]-1)*(mp[a[i]]-2)); //减去重复三个的
			f[a[i]]=1; //标记
			ans-=((mp[a[i]])*(mp[a[i]]-1)*(n-mp[a[i]]))*3; //减去重复两个的
		}else continue;
	}
	cout<<ans/6<<endl;
	return false;
}
/*
5
3 1 4 1 5
3 1 4
3 1 5
3 4 1
3 4 5
1 4 5
4 1 5
*/
```

---

## 作者：_shine_ (赞：1)

### 1.题目大意
有一个长度为 $n$ 的序列，请你求出三元组满足以下条件的数量：

- $1 \le i \le j \le k \le n$。
- 三元组中的三个数互不相同。

### 2.思路分析
设这个三元组中的三个数为 $a,b,c$，则会有 $a<b<c$，则解决本题最简单的办法就是枚举 $b$。

显然对于题目要求中：$a\ne b \ne c$ 这一要求中 $a,b,c$ 不能相等，但显然可以有 $a^1,b^1,c^1$ 满足 $a^1=a,b^1=b,c^1=c$，且满足要求，显然用 $p$ 记录每个数字出现的次数，并且使用前缀和 $sum$ 维护小于等于 $b$ 的数量，则有答案为 $p_{i} \times sum_{i-1} \times\left(sum_{maxn}-sum_{i}\right)$（$maxn$ 在此表示序列中最大的数字）。
### 3.Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5;
const int maxn=2e5+10;
int n,a[maxn];
int p[maxn],sum[maxn];
int ans;
signed main(){
	cin >> n;
	for(int i=1;i<=n;++i){
		cin >> a[i];
		p[a[i]]++;
	}
	for(int i=1;i<=N;++i){
		sum[i]=sum[i-1]+p[i];
	}
	for(int i=1;i<=N;++i){
		ans+=(sum[N]-sum[i])*p[i]*sum[i-1];
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：CQ_Bob (赞：1)

## 分析

我们运用一个叫做正难则反的思路进行求值。

总个数，即不考虑约束条件的方案数，而这个值正好就是 $\frac{n\times(n-1)\times(n-2)}{1\times2\times3}$，即在 $n$ 个数中取任意 $3$ 个数的方案数。但是，这个方案数是满足条件一的，因为我们选的 $3$ 个数是不可能在同一位置的，再将选取的任意三个数的下标排序一下，一定有 $a_1<a_2<a_3$。

不满足个数，即在选出的三个数中相同数字出现过 $2$ 次及以上的方案数。我们找出所有出现次数大于等于 $2$ 的数字，还是按照组合计数进行计算即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
const int N=1e6+10;
int a[N];
int ans;
map<int,bool> vis;
map<int,int> mp;//记录每个数字出现的次数
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],mp[a[i]]++;
	ans=(n*(n-1)*(n-2))/1/2/3;//总数
	for(int k=1;k<=n;k++)
	{
		if(vis[a[k]]) continue;//计算过了，跳过
		vis[a[k]]=1;//第一次出现，就能求了
		int s=mp[a[k]]*(mp[a[k]]-1)/2;
		int ss=n-mp[a[k]];
		ans-=ss*s;//减去有2个相同的方案数
		if(mp[a[k]]>=3)//有三个以上，说明可能全部相同
		{
			int sss=mp[a[k]]*(mp[a[k]]-1)*(mp[a[k]]-2)/1/2/3;
			ans-=sss;//减去有3个相同的方案数
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：As_Snow (赞：1)

### 思路
考虑在读入 $A_i$ 时计算它对于答案的贡献。既然 $A_i$ 已经确定，就可以将问题转化成求出有多少对 $j,k$ 满足 $1\le j,k < i ,A_j\ne A_k\ne A_i$。

用 $res$ 记录下在 $1\sim i$ 中有多少数对满足其中的两个数不同，那么 $A_i$ 对于答案的贡献便是 $res$ 减去所有包含 $A_i$ 的数对。

### Code
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5+25;
int n;
ll num[N],sum;//num[i]记录值为i的数有多少，sum记录当前有多少个数
ll res,ans;
signed main(){
	scanf("%d",&n);
	for(int i=1,a;i<=n;i++){
		cin>>a;
		res+= sum-num[a];//更新res
		++sum,++num[a];
		ans+= res-(sum-num[a])*num[a];//减去包含a[i]的数对
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：wnsyou (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc252_d)

这是数学题耶！

## 题意

给定一个整数 $n$ 和一个长度为 $n$ 的整数序列 $a$，求满足以下要求的三元组个数：

- $1 \leqslant i < j < k \leqslant n$。
- $a_i \ne a_j$，$a_j \ne a_k$，$a_k \ne a_i$。

## 思路

先想正着做，好，不会。

正着做不行就反着做，先算出所有情况，再去掉不合法。


### 所有情况的公式

公式：$\frac{n \times (n-1) \times (n - 2)}{6}$。

公式小解析：首先不考虑顺序，选掉一个数就少一个，选 $3$ 个就是 $n \times (n - 1) \times (n - 2)$，考虑顺序，去掉不合法，除以 $6$。

### 不合法情况的公式

不合法的情况就两种：

1. 两个数相同，另一个不同。
1. 三个数都相同。

那公式就好办了，令 $cnt_i$ 表示 $i$ 在序列中的出现次数。

- 对于一个出现在序列中的整数 $i$，它对答案的负贡献分为以下两种：
  - $\frac{cnt_i \times (cnt_i - 1) \times (cnt_i - 2)}{6}$，三个元素都相同，与所有情况同理。
  - $\frac{cnt_i \times (cnt_i - 1) \times (n - cnt_i)}{2}$，其中两个元素相同需要去重，除以 $2$，另外一个数可以是非 $i$ 的任意数。

记得开个 `long long`。

## Code

```cpp
#include <iostream>

using namespace std;
using ll = long long;

const int N = 2e5 + 10;

int n, a[N], cnt[N];
bool f[N];
ll ans; // 记得开 long long

int main () {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    cnt[a[i]]++; // 统计出现次数
  }
  ans = 1ll * n * (n - 1) * (n - 2) / 6; // 所有情况
  for (int i = 1; i <= n; i++) {
    if (f[a[i]]) { // 同一个数不用多次求
      continue;
    }
    f[a[i]] = 1; // 标记
    ans -= 1ll * cnt[a[i]] * (cnt[a[i]] - 1) * (cnt[a[i]] - 2) / 6; // 套用公式
    ans -= 1ll * cnt[a[i]] * (cnt[a[i]] - 1) * (n - cnt[a[i]]) / 2;
  }
  cout << ans;
  return 0;
}
```

---

## 作者：Gaode_Sean (赞：0)

小清新计数题，不难想到“正难则反”。

如果**只考虑第一个条件**，即 $1 \le i \le j-1 \le k-2 \le n-2$，那么答案即为 ${n \choose 3}$。

考虑加入第二个条件后，减去的值为多少。

设有 $m$ 种不同的值，$cnt_i$ 表示第 $i$ 种元素的数量。那么减去的值即为 $\sum_{i=1}^n [{cnt_i \choose 3}+(n-cnt_i) \times {cnt_i \choose 2}]$。其中 ${cnt_i \choose 3}$ 指的是 $3$ 个数相同的情况，$(n-cnt_i) \times {cnt_i \choose 2}$ 指的是**仅有**两个数相同的情况。

代码实现非常简洁。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
typedef long long ll;
int a[N];
ll n,ans,cnt[N];
int main()
{
	scanf("%lld",&n); ans=n*(n-1)*(n-2)/6ll;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),cnt[a[i]]++;
	for(int i=1;i<=2e5;i++) ans-=cnt[i]*(cnt[i]-1)*(cnt[i]-2)/6ll+(cnt[i]*(cnt[i]-1)/2ll)*(n-cnt[i]);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Tsawke (赞：0)

# [[ABC252D] Distinct Trio](https://www.luogu.com.cn/problem/AT_abc252_d) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC252D)

## 题面

给定序列 $ a_n $，求满足以下条件的三元组 $ (i, j, k) $ 的数量：

$ 1 \le i \lt j \lt k \le n, a_i \neq a_j \neq a_k $。

## Solution

首先不难想到三元组满足 $ i \lt j \lt k $，那么就可以认为是去掉这个条件然后求本质不同三元组，也就是求组合数。

然后考虑正难则反，直接求不好求，考虑先求 $ n \choose 3 $，然后考虑从中去掉不合法的方案。

显然要去掉的就是有两个数相同的组合数和有三个数相同的组合数。当然这个从容斥的角度来看三个数相同的似乎应该是加上，但是实现的时候会发现这个实际上不算是容斥。

我们实现的时候不难发现值域较小，于是想到需要建桶。枚举每个桶，令 $ i $ 的个数为 $ cnt_i $，如果 $ cnt_i \ge 2 $，那么直接减掉 $ {cnt_i \choose 2} \times (n - cnt_i) $，这个式子很显然，并且这个是有且仅有两个数相同的方案数，所以不需要容斥，再次枚举，如果 $ cnt_i \ge 3 $ 再减去 $ cnt_i \choose 3 $ 即可。

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
int a[210000];
int cnt[210000];
ll ans(0);

int main(){
    N = read();
    for(int i = 1; i <= N; ++i)cnt[a[i] = read()]++;
    ans = (ll)N * (N - 1) * (N - 2) / (3 * 2 * 1);
    for(int i = 1; i <= 201000; ++i){
        if(cnt[i] >= 2)ans -= (ll)cnt[i] * (cnt[i] - 1) / (2 * 1) * (N - cnt[i]);
        if(cnt[i] >= 3)ans -= (ll)cnt[i] * (cnt[i] - 1) * (cnt[i] - 2) / (3 * 2 * 1);
    }printf("%lld\n", ans);
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

update-2022_12_03 初稿

---

## 作者：_zhx (赞：0)


# 题目大意

有一个长度为 $n$ 的数列 $A$，求满足以下条件的三元组的数量：

* $1 \leq i < j < k \leq n $

* $A_i$，$A_j$，$A_k$ 互不相同

并且

$ 3 \leq n \leq 2 \times 10^5 $

$ 1 \leq A_i \leq 2 \times 10^5 $

## 题目做法 （桶+前缀和）

题目要求，$1 \leq i < j < k \leq n $，所以 $A_i<A_j<A_k$，那要求出这个三元组，肯定先求 $A_j$ 最方便。 所以可以用 $b$ 来统计每个数字出现的次数，用前缀和 $c$ 来保证小于等于 $A_j$ 的数量。

### 代码部分

AC code

```cpp
#include<bits/stdc++.h>
#define N 2000050
#define LL long long
using namespace std;
LL n,a[N],b[N],c[N],x;//a是输入的数组，b是统计每个数字出现的个数，c是前缀和，x是满足条件的三元组的数量
int Read()//快读
{
    int ff=1,xx=0;
    char cc=getchar();
    while(cc<'0'||cc>'9')
	{
        if(cc=='-')ff=-ff;
        cc=getchar();
    }
    while(cc>='0'&&cc<='9')
	 {
        xx=xx*10+cc-'0';
        cc=getchar();
    }
    return ff*xx;
}
int main()
{
	cin>>n;
	for(LL i=1;i<=n;i++) a[i]=Read(),b[a[i]]++;//统计
	for(LL i=1;i<=N;i++) c[i]=c[i-1]+b[i];//前缀和
	for(LL i=1;i<=N;i++) x+=(c[N]-c[i])*b[i]*c[i-1];//答案
	cout<<x<<endl;//输出
        //（AT不换行，亲人两行泪）
	return 0;
}
```

---

