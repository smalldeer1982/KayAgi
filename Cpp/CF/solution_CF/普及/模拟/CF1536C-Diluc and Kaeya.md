# Diluc and Kaeya

## 题目描述

给你一个字符串 $S$，其中只包含 'K' 或 'D' 两种字符，要求划分这个字符串使得各部分的 $n(D):n(K)$ 相同，其中 $n(D)$ 表示 $S$ 中字符 'D' 出现的个数，最大化划分后形成的组数。

求出 $S$ 的所有前缀中的上述答案。

## 样例 #1

### 输入

```
5
3
DDK
6
DDDDDD
4
DKDK
1
D
9
DKDKDDDDK```

### 输出

```
1 2 1 
1 2 3 4 5 6 
1 1 1 2 
1 
1 1 1 2 1 2 1 1 3```

# 题解

## 作者：¶凉笙 (赞：7)

## [题解] CF1536C Diluc and Kaeya

> [传送门](https://www.luogu.com.cn/problem/CF1536C)

> [更~~差~~的阅读体验](https://www.luogu.com.cn/blog/AG-Liangsheng/solution-cf1536c)

### 题意

给你一个字符串 $S$，其中只包含 'K' 或 'D' 两种字符，要求划分这个字符串使得各部分的 $n(D):n(K)$ 相同，其中 $n(D)$ 表示 $S$ 中字符 'D' 出现的个数。

其实本题要求我们求出所有前缀的答案，但是我们可以先抽象成一个字符串来看。

### 题解

- 何为无解情况？

显然，当 $n(D)$ 与 $n(K)$ 互质时无解，因为此时**第一次出现** $n(D):n(K)$ 这个比例，它肯定是无法划分的。

- 如何统计答案？

由于第一次出现比例 $c$ 时是无解情况，第二次出现时一定存在一种可划分方案把 $S$ 划分为比例相同的两部分。

一边扫描一边用 $map$ 统计即可，复杂度 $\text O(n\ logn)$。

```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#include <string>
template <typename T>
inline T read(){
	T x=0;char ch=getchar();bool fl=false;
	while(!isdigit(ch)){if(ch=='-')fl=true;ch=getchar();}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);ch=getchar();
	}
	return fl?-x:x;
}
#include <map>
#define Pair pair<int,int>
const int maxn = 5e5 + 10;
int ans[maxn],top=0;
#define read() read<int>()
#define mp make_pair
int n;
char ch[maxn];
int gcd(int a,int b){
	if(!b)return a;
	return gcd(b,a%b);
}
void solve(){
	memset(ans,0,sizeof ans);
	map <Pair,int> m;
	int D=0,K=0;
	for(int i=1;i<=n;i++){
		D+= ch[i]=='D';K+= ch[i]=='K';
		int g=gcd(D,K);
		//cerr<<D<<" "<<K<<" "<<g<<endl;//
		ans[i]=++m[mp(D/g,K/g)];
	}
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
	puts("");
}
int main(){
	int T=read();
	while(T--){
		n=read();cin>>(ch+1);
		solve();
	}
}
```

---

## 作者：123hh2 (赞：5)

--->[传送门](https://www.luogu.com.cn/problem/CF1536C)

upate: 删除了一堆没用的废话

------------


### 题目大意
给定一字符串 $S$，只包含 K 和 D 两种大写字母，现要求我们求在对于 $S$ 的**每一个前缀和串中**，能够划分这个前缀和串使得该前缀和串能够在**每一个部分中 D 和 K 的比值的最大组数**

------------


### 思路
对于每个测试数据，先遍历一遍前缀和，可以注意到能划分出大于一组的每个部分中的 D 和 K 的比值是相等的。那么容易知道:

-   当这个字符串中 D 与 K **互质**的时候，这个字符串不能划分出比 1 更多的组数

-   当 D 与 K 不互质的时候
	- D : K 的比值第一次出现，则只能划分出一个组
    - D : K 的比值不是第一次出现，能划分出该比值出现次数的组数
    
所以我们可以考虑用 map 和 pair 来存一下这个比值，然后每读到一个比值，就把他扔进去，对应的映射值++，再找找这个比值出现的次数并输出就好了

------------
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register
inline int gcd(int x,int y) {return y?gcd(y,x%y):x;}
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0') {if(ch=='-') {f=-1;}ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
map<pair<int,int>,int>q;//这是个从<D,K>映射到int的的map 
int main()
{
	int t=read();
	while(t--)
	{
		q.clear();//多测不清空，boom_0两行泪
		int n=read(),D=0,K=0;string a;cin>>a;
		for(ri int i=0;i<a.size();i++)
		{
			a[i]=='D'?D++:K++;
			int temp=gcd(D,K);
			q[make_pair(D/temp,K/temp)]++;
			printf("%d ",q[make_pair(D/temp,K/temp)]);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Cutest_Junior (赞：3)

## 题解 CF1536C 【Diluc and Kaeya】

注意：本题解做法不保证能通过该题数据范围内所有测试点，但能通过该题包括 hack 数据的所有数据。本人不会分析该做法的时间复杂度，如果有人能帮我证明做法正确或给出 hack 数据并申请撤下题解，感激不尽。

### 题意

+ 一个字符串可以分为多个连续子串，当且仅当子串中 D 和 K 的个数比两两相等；
+ 给出长度为 $n$ 的 DK 串；
+ 求这个 DK 串每个前缀子串最多可以分为多少个连续子串；
+ 多组数据，$n\le5\times10^5$。

### 做法

设 $dp_i$ 为原串长度为 $i$ 的前缀子串最多可以分为的子串的个数。

容易写出 $dp_i=\max\limits_{j=1}^{i-1}dp_j+1(d_i*k_j=d_j*k_i)$。（$d_i$ 表示长度为 $i$ 的前缀子串的 D 的个数，$k_i$　同理，用乘法是为了特判掉 K 的个数为 $0$ 的情况）。

复杂度 $O(n^2)$。

考虑优化。

容易发现一个结论：

设 $t=gcd(d_i,k_i)$，则任何 $j$ 使$\dfrac{i}{t}\nmid j$，则 $(d_i*k_j\neq d_j*k_i)$。

证明：

不妨设 $d_i=ta$，$k_i=tb$，容易发现 $\dfrac{i}{t}=a+b$，$gcd(a,b)=1$。

对于任意 $j$，若 $(d_i*k_j=d_j*k_i)$，则 $a*k_j=b*b_j$。

设 $u=gcd(k_j,b_j)$，则一定有 $ua=b_j$，$ub=k_j$。

$j=k_j+b_j=u(a+b)$，$(a+b)\mid u(a+b)$，即若 $(d_i*k_j=d_j*k_i)$，则$\dfrac{i}{t}\mid j$。

不会分析复杂度，但能过所有测试点。

### 代码

```cpp
#include <cstdio>

using namespace std;

typedef long long ll;

const int iinf = (1 << 30) - 1;
const ll linf = (1ll << 60) - 1;

int gcd(int a, int b) {
	if (!b) {
		return a;
	}
	return gcd(b, a % b);
}

const int N = 5e5 + 5;

char s[N];

int d[N], k[N];

int dp[N];

void solve() {
	int n;
	scanf("%d%s", &n, s + 1);
	for (int i = 1; i <= n; ++i) {
		d[i] = d[i - 1];
		k[i] = k[i - 1];
		if (s[i] == 'D') {
			++d[i];
		}
		else {
			++k[i];
		}
		int t = gcd(d[i], k[i]);
		int m = i / t;
		for (int j = i - m; j >= 0; j -= m) {
			if ((ll)d[i] * k[j] == (ll)d[j] * k[i]) {
				dp[i] = dp[j] + 1;
//				printf("%d ", j);
				break;
			}
		}
		printf("%d ", dp[i]);
	}
	printf("\n");
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		solve();
	}
}
```

---

## 作者：Yang818 (赞：2)

## 这是一道黄题？确实！
## 题目传送门
戳[这里](https://www.luogu.com.cn/problem/CF1536C)
## 分析
这道题标准来讲呢他是动态规划的分组问题，能写出方程

$$f_i=\max{f_j}+1$$

$f_x$表示到 $x$ 能划分多少组

相当于这一刀划在 $i$ 上一刀划在 $j$ ，1到$j$ 内满足题目且1到 $i$ 满足要求然后自然 $i$ 到 $j$ 这段区间j就满足要求了，然后就可以 $dp$ 了。
我们举个例子：

![例子1](https://cdn.luogu.com.cn/upload/image_hosting/vp2r4t8u.png)


比如说第一次划到 80:32 比值是 5:2，第二次滑倒 100:40，比值还是 5:2，那么两者相减，20:8，比值依然没变，所以验证了这个方程是正确的。

### 所以怎么选呢？

![选法](https://cdn.luogu.com.cn/upload/image_hosting/k86deztz.png)

如图，划到第 $i$ 段，比值是 2:1，前面有 3 个$j$比值都是 2:1，分别是 $j_1\ j_2\ j_3$ 那肯定选 $j_3$ 喽，因为 $j_3$ 包含了 $j_1\ j_2$ 

这可能给你感觉像什么决策单调啊，长的式子啊，什么的，那为什么要用一个数组去存这个 $f$ 呢？直接用一个 $map$ 不就完了吗？那 $map$ 怎么存比例呢？如下:
```cpp
map<pair<int,int>,int>m;
```

第一个 $pair$ 可以存储比值并且当作关键字进行查询。多好啊！
**STL万岁**

## 代码
代码还要给吗？
这里给个核心部分吧：
```
for(i->n)
	if(s[i]=="0")
		nD++;
	else
		nK++;
	make_pair<nD/gcd,nK/gcd>
cout<<++m[nD/gcd,nK/gcd]
```
望通过，谢谢


---

## 作者：The_foolishest_OIer (赞：1)

STL 大法好！

维护两个数，分别代表 `D` 出现的次数和 `K` 出现的次数。

如果 `D` 出现的次数与 `K` 出现的次数互质或者这个最简比第一次出现，答案肯定是 $1$。

否则就能划分出的组数为这个比值的出现次数。

用 map 维护即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int T,n;
string s;
map <pair <int,int>,int> Map;
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void solve(){
	cin >> n;
	cin >> s;
	s = ' ' + s;
	Map.clear();
	int _d = 0,_k = 0;
	for (int i = 1 ; i <= n ; i++){
		if (s[i] == 'D') _d++;
		else _k++;
		int Gcd = __gcd(_d,_k); // (_d / Gcd) : (_k / Gcd) 就是这个比的最简比
		Map[make_pair(_d / Gcd,_k / Gcd)]++;
		cout << Map[make_pair(_d / Gcd,_k / Gcd)] << ' ';
	}
	cout << endl;
}
signed main(){
	close();
	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：songtaoran (赞：0)

如果 $n(D)$ 与 $n(K)$ 互质，那么答案为 $1$。  
那么如果不互质呢？
> 可以发现，$4 : 8$ 或 $12 : 24$ 都可以化为 $1 : 2$，也就是说需要约分。  
> 如果这个比例是第一次出现，那么答案为 $1$，否则为之前出现的次数加一。  
> 也就是说我们可以维护一个 $\operatorname{map}$。
> > ```cpp
> > ll d = 0, k = 0;
> >	for(ll i = 1; i <= n; i++){
> >	    if(c[i] == 'D') d++;
> >	    else k++;
> >	    ll t = __gcd(d, k);
> >	    printf("%lld ", ++mp[{d / t, k / t}]);
> >	}
> >	printf("\n");
> > ```

---

## 作者：Vii_Truly (赞：0)

显然当 $d$ 和 $k$ 的个数互质的时候是不可划分的，这个想一下应该不难明白。

如果不互质的时候怎么办呢？不难发现，如果 $d:k$ 的值是第一次出现，那还是无法划分，如果是第二次出现呢？

考虑分数 $\frac{d}{k}$，随着 $d$ 和 $k$ 的个数不断增加，令 $x,y$ 分别表示 $d,k$ 增加的个数，比值就变成了 $\frac{d+x}{k+y}$ 那什么时候 $\frac{d+x}{k+y}=\frac{d}{k}$ 呢，是 $\frac{x}{y}=\frac{d}{k}$ 的时候，这样就是说，当一个比值出现两次的时候，就说明可以划分成两段，第一段是从开头到比值第一次出现，第二段就是两次比值相等的中间一段。同理，如果出现三次，就是三段...

另外还有一种特殊情况，就是其中一个为 $0$ 的时候，这时直接输出另一个数即可。

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void solve() {
    int n;
    map<pair<int, int>, int> mp;
    string str;
    cin >> n >> str;
    int d = 0, k = 0;
    for (int i = 0; i < n; i++) {
        if (str[i] == 'D') d++;
        else k++;
        if (!d || !k) cout << max(d, k) << ' ';
        else cout << ++mp[{d / __gcd(d, k), k / __gcd(d, k)}] << ' ';
    }
    cout << endl;
}

int main() {
//    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int _ = 1;
    cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}
```

---

## 作者：nalemy (赞：0)

这道题要求我们给一个字符串的所有前缀求出满足每一部分 $n(D):n(K)$ 值相等的最大划分后的组数。

首先，如果值给一个字符串求 $n(D):n(K)$ 相等的最大花粉，其实只用枚举划分点就可以。

但是这道题让我们对一个字符串的所有前缀都做这个工作，复杂度就假了。所以我们考虑，算后面的时候**是否能用到前面算出来的结果**。

我们考虑，如果一个字符串 $s=s_1+s_2$，加号表示拼接。易证：
$$
n_{s_1}(D):n_{s_1}(K)=n_s(D):n_s(K)\Longrightarrow n_{s_1}(D):n_{s_1}(K)=n_{s_2}(D):n_{s_2}(K)
$$
也就是说，如果验证发现左边式等式立，那么右边等式也成立。

那么，如果我们扫到原字符串第 $i$ 位时，发现**这个前缀的某个真前缀**算出来的 $n(D):n(K)$ 与**这个前缀**相等，那么我们可以**怀疑**，**当前前缀**的答案就等于**这个真前缀**的答案 $+1$。

形式化地，我们定义 $pre_i$ 为 $s$ 的前缀。如果我们发现 $n_{pre_i}(D):n_{pre_i}(K)=n_{pre_j}(K):n_{pre_j}(K)\quad(i<j)$，那么我们可以**怀疑** $ans_i=ans_j+1$。

为什么说是 **怀疑** 呢？因为可能不是**最大化分**。那么如何保证最大呢？只用找到满足上式的**最大的**的 $j$ 就好啦！这个很好理解。

进一步地，我们可以考虑优化这个算法。我们开一个 map，键是 $n(D):n(K)$，值是知道当前对应这个键的最大化分，在每次扫字符串的时候更新这个 map​。

具体看代码吧：

```C++
#include<iostream>
#include<map>
#define N 500000
using namespace std;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
struct frac {
    int a, b;
    frac(int _a, int _b) {
        int t = gcd(_a, _b);
        a = _a / t, b = _b / t;
    }
};
// map 需要
bool inline operator < (frac a, frac b) {
    return a.a == b.a ? a.b < b.b : a.a < b.a;
}
map<frac, int> mp;
int main() {
    int t, n, d, k; string s; cin >> t;
    while (t--) {
        cin >> n >> s, d = k = 0, mp.clear();
        for (int i=0; i<n; i++) {
            s[i] == 'D' ? d++ : k++;
            frac rat = frac(d, k);
            // 如果没有对应的键
            if (mp.find(rat) == mp.end()) mp[rat] = 1;
            else mp[rat]++;
            cout << mp[rat] << ' ';
        }
        cout << '\n';
    }
    return 0;
}
```

因为我们**每一次扫**都会更新 map，所以保证每次找到的 $j$ 都是最大的。

---

