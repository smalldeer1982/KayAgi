# [ARC033B] メタ構文変数

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc033/tasks/arc033_2

「$ foo $」や「$ bar $」「$ hoge $」などの、特に意味を持たない変数の名前に使用される文字列のことを「メタ構文変数」と呼びます。

高橋君は今、メタ構文変数について調べています。メタ構文変数には色々な種類があることが分かり、見つけたメタ構文変数にそれぞれに番号をつけました。高橋君はアリの $ Ant $ さんと $ Bug $ くんのソースコードを読み、それぞれのソースコードに現れるメタ構文変数の番号を列挙しました。そして、$ Ant $ さんと $ Bug $ くんの使うメタ構文変数の集合がどれくらい似ているのかを調べるために「$ Jaccard $ 係数」を計算することにしました。$ Ant $ さんのソースコードに現れるメタ構文変数の集合を $ S_A $、$ Bug $ くんのソースコードに現れるメタ構文変数の集合を $ S_B $ とするとこれらの集合の $ Jaccard $ 係数は、

- $ ||S_{A}\ ∩\ S_{B}||\ /\ ||S_{A}\ ∪\ S_{B}|| $

という式で計算できます。ここで、$ ||S|| $ は集合 $ S $ の要素数を表すものとします。別の言い方をすると、

- 「$ S_{A} $ と $ S_{B} $ の両方に現れる要素の個数」$ / $「$ S_{A} $ と $ S_{B} $ の少なくともどちらか一方には現れる要素の個数」

となります。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ N_A,N_B\ ≦\ 1000 $ と $ A_i,B_i\ ≦\ 10^5 $ を満たすテストケース全てに正解した場合は、$ 40 $ 点が与えられる。
- $ A_i,B_i\ ≦\ 10^5 $ を満たすテストケース全てに正解した場合は、$ 70 $ 点が与えられる。

### Sample Explanation 1

$ Ant $ さんと $ Bug $ くんのソースコードの両方に現れるメタ構文変数は $ 1 $ 番のみで、$ Ant $ さんと $ Bug $ くんのソースコードの少なくともどちらか一方には現れるメタ構文変数は $ 1,2,3,5 $ 番の $ 4 $ つです。 よって、$ Jaccard $ 係数は $ 1/4 $ となります。

## 样例 #1

### 输入

```
3 2
1 3 5
1 2```

### 输出

```
0.2500000000```

## 样例 #2

### 输入

```
9 10
11 2 33 4 55 6 77 8 99
10 11 14 19 55 1000000000 4 5 7 8```

### 输出

```
0.2666666667```

# 题解

## 作者：Swirl (赞：4)

你，真的不用 set 吗？

# 思路简述

思路有些复杂，但应该还好理解。

首先，因为 `set` 可以自动去重，所以可以把两个集合的所有数都扔到一个 `set` $\texttt{S}$ 里面，得到的就是并集；

接着，将两个集合的元素分别放到两个 `set` $\texttt{A,B}$ 里，遍历 $\texttt{A}$，如果发现 $\texttt{A}$ 中的变量恰好也在 $\texttt{B}$ 中，则将其放入 `set` $\texttt{T}$ 里，此时 $\texttt{T}$ 便是交集。

最后输出 $\frac{|\texttt{T}|}{|\texttt{S}|}$ 即可。

# Code

```cpp
#include <bits/stdc++.h>
#define ios                  \
ios::sync_with_stdio(0); \
cin.tie(0);              \
cout.tie(0)
// #pragma GCC optimize(2)
#define ll long long
#define pll pair<ll, ll>
#define pii pair<int, int>
#define il inline
#define p_q priority_queue
#define u_m unordered_map
#define r_g register
#define NR Nothing::read
#define NW Nothing::write
using namespace std;

int n, m;
int a[100060], b[100060];
set<int> s, t, A, B;

signed main() {
	ios;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		s.insert(a[i]);
		A.insert(a[i]);
	}
	for (int i = 1; i <= m; i++) {
		cin >> b[i];
		s.insert(b[i]);
		B.insert(b[i]);
	}
	for (auto x : A) {
		if (B.find(x) != B.end()) {
			t.insert(x);
		}
	}
	printf("%.10lf", (double)(t.size()) / (double)(s.size()));
	return 0;
}
```

---

## 作者：xyx404 (赞：2)

## 思路：
题目要求求两个集合中相同的元素个数除以两个集合合并在一起并去重后的元素个数。

考虑使用 `set`。

定义两个 `set`，第一个 `set` 存第一个集合中的元素，第二个 `set` 存两个集合的元素。

定义一个变量做两个集合中相同元素的计数器。

在输入时，把两个集合中的元素都放进第二个 `set` 里。

在输入第二个集合时，顺便判断这个元素是否在第一个集合中出现过，出现过让计数器加一。

最后输出两个集合中相同的元素个数除以两个集合合并在一起并去重后的元素个数就行了。

`set` 会自动去重。


## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
set<string>a,all;
string x;
int n,m;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>x;
		a.insert(x);
		all.insert(x);
	}
	int siz=0;
	for(int i=1;i<=m;i++){
		cin>>x;
		all.insert(x);
		if(a.count(x))siz++;
	}
	cout<<double(siz)/all.size();
	return 0;	
}

```

---

## 作者：Carey2012 (赞：1)

## 传送门
>[传送门](https://www.luogu.com.cn/problem/AT_arc033_2)
## 思路
因为题目中叫我们求 $ \frac{||S_a\cap S_b||}{||S_a\cup S_b||}$，\
所以我们先求解 $||S_a\cup S_b||$。\
我们可以统计 $A_i$ 和 $B_i$，对其标记，然后统计被标记的个数。
### data
```cpp
for(auto it:mii){
	bs++;
}/*
mii:标记用的
bs:即统计 S_a 和 S_b 的并集
*/
```
然后我们再求解 $||S_a\cap S_b||$。\
我们可以统计 $A_i$ 和 $B_i$ 的个数，然后统计个数大于 $1$ 的个数。
### data
```cpp
for(auto it:mii){
	if(it.second>1){as++;}
}/*
mii:标记个数用的(mii进阶)
as:即统计 S_a 和 S_b 的交集
*/
```
最后，把他们结合起来就行了。
## data（AC）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX=1e5+10,mod=1e9+7;
typedef long long ll;
typedef pair<int,int> pii;
int n,m;
map<int,int> mii;
int x;
int as,bs;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n+m;i++){scanf("%d",&x);mii[x]++;}
	for(auto it:mii){
		if(it.second>1){as++;}
		bs++;
	}printf("%.12lf",as*1.0/bs);
	return 0;
}
```

---

## 作者：PineappleSummer (赞：1)

[[ARC033B] メタ構文変数](https://www.luogu.com.cn/problem/AT_arc033_2)

这篇题解介绍两种方法。
### solution 1
发现 $size(a\cap b)$ 等于 $n + m - size(a\cup b)$，考虑先求出来并集的大小，再求出交集的大小。

求并集其实就是求不同数的个数，可以用 `map` 开一个桶标记该数是否出现过，然后计算即可。

部分代码：
```cpp
for(int i=1;i<=n;i++){
	cin>>a[i];
	if(mp[a[i]]) ans--;
	mp[a[i]]=1;
}
for(int i=1;i<=m;i++){
	cin>>b[i];
	if(mp[b[i]]) ans--;
	mp[b[i]]=1;
}
// ans 即为并集大小
```
[完整代码](https://atcoder.jp/contests/arc033/submissions/51710900)
### solution 2
考虑将 solution 1 中的 `map` 改为 `set` 维护，每次直接将数加入进 `set` 中，最后 `set` 的大小即为并集的大小。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x;set<int>s;
main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n+m;i++) scanf("%d",&x),s.insert(x);
	printf("%.10f",(n+m-s.size())*1.0/s.size());
}
```

solution 2 代码现为 AtCoder 该题 c++ 最短代码。

---

## 作者：zhengjh2818 (赞：1)

## 闲话多说

STL 大法……

## 题目描述
[题目传送门](https://www.luogu.com.cn/problem/AT_arc033_2)

## 解题思路
题目给出两个序列，分别表示两个集合。要求计算 Jaccard 系数，即两个集合的交集的大小除以两个集合的并集的大小。

具体代码思路如下：

- 初始化变量 sum，表示交集的元素个数。
- 遍历第一个序列，使用集合存储序列中的元素，方便进行查找。
- 遍历第二个序列，对于每个元素，如果它在前一个序列中存在，则将 $sum \gets sum + 1$。
- 计算并集的大小，即将两个序列合并为一个集合，并获取其大小。
- 计算 Jaccard 系数，即 sum 除以并集的大小。
- 输出 Jaccard 系数。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, sum, num, ans;
unordered_set<int> setA;
int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> num;
		setA.insert(num);
	}
	for (int i = 0; i < m; i++) {
		cin >> num;
		if (setA.count(num) > 0) {
			sum++;
		}
	}
	ans = setA.size() + m - sum;
	printf("%.10f", (double)sum / ans);
	return 0;
}
```
~~**蒟蒻的第四篇题解二审，望审核员大人通过。**~~

---

## 作者：Poole_tea (赞：0)

# 题意
给两个集合，一个长度为 $N$，另一个长度为 $M$，求两集合的交集的大小与并集的大小比值。

一看到集合，那必须得想到 ```set```，不知道的点[这里](https://oi-wiki.org/lang/csl/associative-container/)，这只是解决了并集大小的问题，但还有并集的大小的问题，我们可以用桶排，可是这道题数据比较大，数组用不了，于是我们可以用 ```map``` 来解决，不知道的点[这里](https://oi-wiki.org/lang/csl/associative-container/?query=map#map)。
此时我们计算在 ```map``` 中出现了两次及以上的数就是两个集合的交集，用 $ans$ 记录在 ```map``` 中出现了两次及以上的数的数量。

Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[20081128],b[20081128];
set<int> x;
map<int,int> t;
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		x.insert(a[i]);
		t[a[i]]++;
	}
	int ans=0;
	for(int i=1;i<=m;i++){
		cin>>b[i];
		x.insert(b[i]);
		t[b[i]]++;
		if(t[b[i]]>=2){
			ans++;
		}
	}
	printf("%.10lf",ans*1.0/x.size());
}
```

---

## 作者：opzc35 (赞：0)

## 题意

给你两个数列，求他们并集长度除以他们交集长度。

数学表示：给定两集合 $A$ 和 $B$，求以下公式值：$\frac{||A\cap B||}{||A\cup B||}$，

其中 $||x||$ 表示集合 $x$ 的长度。

## 概念

什么是集合？

> 你可以理解为一个数组。

什么是两个集合的并集？

> 两个集合共有的部分叫做并集（符号 $\cap$ 表示）。

什么是两个集合的交集？

> 两个集合包含的所有数字都可以算作这两个集合的交集（符号 $\cup$ 表示）。

举个例子：

集合 $A = {1,2,3,4,5}$，

集合 $B = {1,2,3,5,6}$，

那么 $A\cap B$ 就等于 ${1,2,3,5}$，

$A\cup B$ 就等于 $1,2,3,4,5,6$。

## 分析

我们考虑使用 C++ 的光荣：STL。

并集的话就考虑用一个 map 记录第一个序列是否出现，第二个序列输入时就将并集长度变量 $+1$ 即可。

交集考虑直接使用 map，最后再用

```cpp
std::map<int> size()
```

求出 map 中的数字个数即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
map<int,bool> mp1,mp2;
int jiao;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		mp1[x]=true;
		mp2[x]=true;
	}
	for(int i=1;i<=m;i++){
		int x;
		cin>>x;
		if(mp1[x]==true){
			jiao++;
		}
		mp2[x]=true;
	}
	printf("%.6lf",jiao*1.0/mp2.size());
	return 0;
}
```

## TIPS

可以使用 `printf("$.6lf",x);` 来输出 $6$ 位小数。

---

## 作者：A_grasser (赞：0)

## 题意简化

给定两个集合，求交集大小除以并集大小的商。

## 解法分析

提供一种非常易懂的 `map` 做法：

首先我们将集合 $A$ 读入，那么只要每读入一个数，它都必定会出现在并集里，所以并集大小加一。

接着读入集合 $B$。若读入元素在 $A$ 中出现过，那么交集大小加一；反之，这个元素没出现过，那么它必定会出现在并集里，并集大小加一。

毕竟可能有人不知道何为集合并集交集，在此说一下（仅为浅层理解）：

- 集合：含有一些不相同的元素的元素组。

- 并集：两个集合里所有元素所组成的元素组（与或运算相似）。

- 交集：两个集合里共有的的元素所组成的元素组与与运算相似）。

## 完整代码

```cpp
//已通过
#include<bits/stdc++.h>
//万能头文件
using namespace std;
int n,m;
unordered_map<int,bool>mp;
int main(){
	cin>>n>>m;
	double bing=0,jiao=0;
	int x;
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		mp[x]=1;
		bing++;
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&x);
		if(mp[x]==1) jiao++;//出现过，交集加一 
		else bing++;//没出现过，并集加一 
	}
	double ans=jiao/bing;
	cout<<fixed<<setprecision(10)<<ans;
	return 0;
}
```

---

## 作者：IAKIOI__ (赞：0)

### 前置知识

离散化。

# 题意

给定两个集合，要你求出他们交集与并集的大小之比，结果保留六位小数。

# 思路

暴力求出两个集的大小，最后直接输出。

### 离散化

两集合判断是否有数值重复时应将数值离散化。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define _ 0
using namespace std;
const int MAXN=2e5;
int n,m;
int ans;//并集大小 
int cnt;//交集大小 
int a[MAXN],b[MAXN];
map <int,int> mp;//离散化 
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		mp[a[i]]++;
		if(mp[a[i]]==1){//第一次出现 
			cnt++;
		}
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
		if(mp[b[i]]==1){//第一次重复 
			ans++;
		}else if(mp[b[i]]==0){//第一次出现 
			cnt++;
		}
		mp[b[i]]++;
	}
	printf("%.6llf\n",ans*1.0/cnt);//保留6位小数 
	return ~~(0^_^0);
}
```

---

## 作者：FreedomKing (赞：0)

### 思路

首先转化一下题意，交集就是统计在两个集合**共**出现两次的元素，并集就是两个集合存在一块减去交集。

直接考虑两个 STL 容器的特性。由于元素的范围很大，可以使用 `map` 作为桶进行统计；`set` 是集合，可以直接为两个集合去掉交集，也就是去重。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int a[N],n,m,t,k;
vector<int>e[N];
bool vis[N];
string s;
set<int>st;
map<int,int>mp;
signed main(){
	cin>>n>>m;
	int n_m=n+m;
	for(int i=1;i<=n_m;i++){
		int x;
		cin>>x;
		st.insert(x);
		mp[x]++;
	}
	for(auto i:mp) if(i.second>=2) k++;
	int _size=st.size();
	printf("%.8f\n",(k*1.0/_size));
	return 0;
}
```

---

## 作者：zk_y (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc033_2)

## 插一句

这道题目有点玄乎，我提交了十几次全都是UKE，但是AT上显示的全都是正确，希望有大佬能私信告诉我一下为什么。（晚上十点测评的）


## 题目描述

我们可以看出，这个题目是让我们求 $|a\cap b|$ 和 $|a\cup b|$。

我们可以分开考虑：

首先考虑 $|a\cap b|$，我们应当怎么求呢？

我们只需要统计次数出现次数大于 $2$ 的数就可以了，这里可以使用 ``map`` 来存储每个数的出现次数。这里可以直接像下面代码一样只要出现次数大于 $2$，立刻将其的出现次数赋值成一个极小的数就可以了。

然后考虑 $|a\cup b|$。

我们使用集合统计就可以了，因为集合是自动去重的。最后直接输出大小就可以了。

最后记得输出精度，最好设置保留 $7$ 位小数，不过好像原题保留了 $10$ 位。

[AC记录（AT）](https://atcoder.jp/contests/arc033/submissions/44646057)

# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,num,ans;
set<int>a;
map<int,int>b;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n+m;i++){
		scanf("%d",&num);
		a.insert(num);
		b[num]++;
		if(b[num]>=2){
			ans++;
			b[num]=-1e9;//这里赋值尽量小一点
		}
	}
	printf("%.7lf\n",double(ans)/a.size());//保存精度
	return 0;
}
```

---

## 作者：hellolin (赞：0)

[题面(洛谷)](https://www.luogu.com.cn/problem/AT_arc033_2)

[题面(AtCoder)](https://atcoder.jp/contests/arc033/tasks/arc033_2)

AtCoder Problems 评级难度：$\texttt{\color{#ffb972}{789}}$。

## 题意

- 给两个长度为 $N$ 的集合 $A$ 与 $B$，求 $\frac{\operatorname{size}(A\cap B)}{\operatorname{size}(A\cup B)}$。
- $1\le N\le 10^5,\ 1\le A_i, B_i\le 10^9$。

## 思路

对这些数计数，所有出现次数大于等于 $2$ 的元素的个数就是 $\operatorname{size}(A\cap B)$。下标数可能很大，所以扔 `map` 里。

将这些数扔到 `set` 里，`set.size()` 就是 $\operatorname{size}(A\cup B)$。

## 代码

``` cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
set<ll>x;
map<ll,ll>y;
int n,m,a,ans;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1; i<=n+m; i++)
    {
        cin>>a;
        x.insert(a);
        ++y[a];
    }
    for(auto i:y)ans+=(i.second>=2);
    cout<<fixed;
    cout.precision(10);
    cout<<ans*1.0/x.size()<<endl;
    return 0;
}
```

---

## 作者：Little_Cabbage (赞：0)

> 涉及知识点：`set`。

# 解题思路

为什么要用 `set` 呢？因为 `set` 可以去重！

令 $s1$ 与 $s2$ 均为 `set`。

$|a \cap b|$ 相当于把 $a$ 数组和 $b$ 数组的元素放进 $s1$ 里的长度。

$|a \cup b|$ 相当于把 $a$ 和 $b$ 都有的元素放进 $s2$ 里的长度。

最后直接相除输出即可。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ll __int128
#define db double
#define ldb long double
#define vo void
#define endl '\n'
#define il inline
#define re register
#define ve vector
#define p_q priority_queue
#define PII pair<int, int>
using namespace std;

//#define O2 1
#ifdef O2
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
#endif

namespace OI {
	template <typename T>
	il T read() {
		T x = 0, f = 1;
		int ch = getchar();
		while (!isdigit(ch)) {
			if (ch == '-') f = -1;
			ch = getchar();
		}
		while (isdigit(ch)) {
			x = (x << 3) + (x << 1) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template <typename TE>
	il void write(TE x) {
		if (x < 0) {
			x = -x;
			putchar('-');
		}
		TE sta[35];
		int top = 0;
		do {
			sta[top++] = x % 10, x /= 10;
		} while (x);
		while (top) putchar(sta[--top] + '0');
	}
	il string read_with_string() {
		string s = "";
		char ch = getchar();
		while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
			s += ch;
			ch = getchar();
		}
		return s;
	}
	il void write_with_string(string s) {
		for (int i = 0; i < s.size(); i ++ ) putchar(s[i]);
	}
}
namespace COMB {
	int fact[200000];
	int Triangle[1010][1010];
	void Fact(int n, int mod) {
		fact[0] = 1;
		for (int i = 1; i <= n; i ++ ) fact[i] = ((fact[i - 1]) % mod * (i % mod)) % mod;
	}
	void Pascal_s_triangle(int n, int mod) {
		for (int i = 0; i <= n; i ++ ) Triangle[i][0] = 1;
		for (int i = 1; i <= n; i ++ )
			for (int j = 1; j <= i; j ++ )
				Triangle[i][j] = (Triangle[i - 1][j] + Triangle[i - 1][j - 1]) % mod;
	}
	int pw(int x, int y, int mod) {
		int res = 1;
		while (y) {
			if (y & 1) res = ((res % mod) * (x % mod)) % mod;
			x = (x % mod) * (x % mod) % mod;
			y >>= 1;
		}
		return res;
	}
	int pw(int x, int y) {
		int res = 1;
		while (y) {
			if (y & 1) res *= x;
			x *= x;
			y >>= 1;
		}
	}
	int GCD(int x, int y, int mod) {
		return __gcd(x, y) % mod;
	}
	int LCM(int x, int y, int mod) {
		return (((x % mod) * (y % mod)) % mod / (GCD(x, y, mod) % mod)) % mod;
	}
	int C(int n, int m, int mod) {
		if (m > n || m < 0) return 0;
		return fact[n] * pw(fact[m], mod - 2, mod) % mod * pw(fact[n - m], mod - 2, mod) % mod;
	}
	int Ask_triangle(int x, int y) {
		return Triangle[x][y];
	}
}
using namespace OI;
using namespace COMB;

//#define fre 1
#define IOS 1
//#define multitest 1

const int N = 2e5 + 10;
const int M = 4e5 + 10;
const int inf = 1e12;

int n, m;
int a[N], b[N];
set<int> s1, s2, A, B;

il void Init() {
	cin >> n >> m;
	for (int i = 1; i <= n; i ++ ) cin >> a[i];
	for (int i = 1; i <= m; i ++ ) cin >> b[i];
}

il void Solve() {
	for (int i = 1; i <= n; i ++ ) s1.insert(a[i]), A.insert(a[i]);
	for (int i = 1; i <= m; i ++ ) s1.insert(b[i]), B.insert(b[i]);
	for (auto x : A)
		if (B.find(x) != B.end())
			s2.insert(x);
	printf("%.10lf", (db)(s2.size()) / (db)(s1.size()));
}

signed main() {
	int T;
#ifdef IOS
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#endif
#ifdef fre
	freopen(".in", "r", stdin);
	freopen(".out", "w", stdout);
#endif
#ifdef multitest
	cin >> T;
#else
	T = 1;
#endif
	while (T--) {
		Init();
		Solve();
	}
	return 0;
}
/*

*/
```

---

