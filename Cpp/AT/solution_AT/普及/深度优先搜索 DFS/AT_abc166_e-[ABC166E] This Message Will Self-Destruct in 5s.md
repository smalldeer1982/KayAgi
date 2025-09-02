# [ABC166E] This Message Will Self-Destruct in 5s

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc166/tasks/abc166_e

AtCoder 王国の優秀なエージェントであるあなたは、盗まれた極秘情報が AlDebaran 王国の手に渡ることを阻止するため、取引現場であるパーティに潜入しました。

パーティには $ N $ 人の参加者がおり、それぞれ $ 1 $ から $ N $ までの番号がついています。参加者 $ i $ の身長は $ A_i $ です。

あなたは事前の尋問によって、極秘情報を取引するのは以下の条件を満たす $ 2 $ 人組であることを知っています。

- $ 2 $ 人の持つ番号の差の絶対値が、$ 2 $ 人の身長の和に等しい。

$ N $ 人の参加者のうちから $ 2 $ 人を選んでペアにする方法は $ \frac{N(N-1)}{2} $ 通りありますが、このうち上の条件を満たすペアは何通りあるでしょう？

なお、極秘情報の内容が何であるかはあなたの知るところではありません。

## 说明/提示

### 制約

- 入力はすべて整数
- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9\ (1\ \leq\ i\ \leq\ N) $

### Sample Explanation 1

\- $ A_1\ +\ A_4\ =\ 3 $ なので、参加者 $ 1,\ 4 $ のペアは条件を満たします。 - $ A_2\ +\ A_6\ =\ 4 $ なので、参加者 $ 2,\ 6 $ のペアは条件を満たします。 - $ A_4\ +\ A_6\ =\ 2 $ なので、参加者 $ 4,\ 6 $ のペアは条件を満たします。 その他に作れるペアはいずれも条件を満たさないので、$ 3 $ を出力します。

### Sample Explanation 2

条件を満たすペアが存在しないので、$ 0 $ を出力します。

## 样例 #1

### 输入

```
6
2 3 3 1 3 1```

### 输出

```
3```

## 样例 #2

### 输入

```
6
5 2 4 2 8 8```

### 输出

```
0```

## 样例 #3

### 输入

```
32
3 1 4 1 5 9 2 6 5 3 5 8 9 7 9 3 2 3 8 4 6 2 6 4 3 3 8 3 2 7 9 5```

### 输出

```
22```

# 题解

## 作者：fighter (赞：4)

题目所要求的条件是$a_i+a_j=|i-j|$

后面这个绝对值看起来不好直接处理，那么我们可以只考虑当前位置前面的数，也就是每组符合条件的数都会在后面一个数的位置被考虑到。

那么假设当前位置为$i$，柿子可以变形为$a_i-i=-a_j-j$。所以我们只要从左到右扫一遍，用一个map维护$-a_j-j$就好了。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define MAX 500005
using namespace std;

template<typename T>
void read(T &n){
    n = 0;
    T f = 1;
    char c = getchar();
    while(!isdigit(c) && c != '-') c = getchar();
    if(c == '-') f = -1, c = getchar();
    while(isdigit(c)) n = n*10+c-'0', c = getchar();
    n *= f;
}
template<typename T>
void write(T n){
    if(n < 0) putchar('-'), n = -n;
    if(n > 9) write(n/10);
    putchar(n%10+'0');
}

int n;
ll a[MAX];
map<ll, ll> mp;

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++){
        read(a[i]);
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++){
        ans += mp[a[i]-i];
        mp[-a[i]-i]++;
    }
    cout << ans << endl;

    return 0;
}
```

---

## 作者：Priori_Incantatem (赞：3)

[题目链接](https://atcoder.jp/contests/abc166/tasks/abc166_e)

第一次AC ABC的E题

### 题目大意
给出一个长度为 $n$ 的序列 $h$
问有多少个不同的无序数对 $(x,y)$，使得 $|x-y|=h_x+h_y$

### 解题思路
这个题目在转化前可能没那么好想，我们把它转换成一个更形象的题目

有 $n$ 棵树，编号为 $i$ 的树的高度为 $h_i$，问有多少个无序数对 $(x,y)$，使得树 $x,y$ 向对方的方向倒下之后，$[x,y]$ 这个区间刚好被覆盖，而且没有重叠，如下图

![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9jZG4ubHVvZ3UuY29tLmNuL3VwbG9hZC9pbWFnZV9ob3N0aW5nL2JpeDRyenZ0LnBuZw?x-oss-process=image/format,png)

那么，我们设 $cnt[i][0]$ 为往右倒后树顶落在为位置 $i$ 上的树的个数
$cnt[i][1]$ 为往左倒后树顶落在为位置 $i$ 上的树的个数

那么最后的答案就是 $\frac{\sum\limits_{i=1}^{n} cnt[i-h[i]][0]+cnt[i+h[i]][1]}{2}$

```cpp
#include<cstdio>
#include<iostream>
const long long Maxn=1000000+10;
long long a[Maxn],cnt[Maxn][2];
long long n,ans;
inline long long read()
{
	long long s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int main()
{
	n=read();
	for(long long i=1;i<=n;++i)
	{
		a[i]=read();
		if(i-a[i]>=0)++cnt[i-a[i]][1];
		if(i+a[i]<=n)++cnt[i+a[i]][0];
	}
	for(long long i=1;i<=n;++i)
	{
		if(i-a[i]>=0)ans+=cnt[i-a[i]][0];
		if(i+a[i]<=n)ans+=cnt[i+a[i]][1];
	}
	printf("%lld\n",ans>>1);
	return 0;
}
```

---

## 作者：HoshizoraZ (赞：2)

感觉很多题目都长得和这道题差不多。

首先，把式子改一下：

$$j-i=A_i+A_j \rightarrow (A_i+i)+(A_j-j)=0$$

令 $X_i=A_i+i$，$Y_i=A_i-i\ (1 \le i \le n)$。

那问题就可以转化成：

找到所有满足 $X_i+Y_j=0$ 的数对 $(i,j)$。

那对于每一个 $i$，只需要找满足 $Y_j=-X_i$ 的 $j$ 的数量。

我们可以使用 STL 中的 `lower_bound` 和 `upper_bound` **分别**找到数组 Y 中第一个**大于等于、大于** $-X_i$ 的数的位置 $L,R$，那么满足 $Y_j=-X_i$ 的 $j$ 就有 $R - L$ 个。

把所有的 $R-L$ 相加，就是最后的答案。

```cpp
#include <algorithm>
#include <cstdio>
#define INF 1e9
#define eps 1e-6
typedef long long ll;
using namespace std;

int n;
ll a[200010], A[200010], B[200010], l, r, ans;
// 2e5 的平方会爆，需要开 LL

int main(){

	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%lld", &a[i]);
		// 制造数组
		A[i] = a[i] + i;
		B[i] = a[i] - i;
	}
	sort(B + 1, B + n + 1);			// 排序，目的是用于二分查找
	for(int i = 1; i <= n; i++){
		// l, r 分别代表上文中的 L 和 R
		// 统计满足等于 -A[i] 的数组 B 中数的数量
		l = lower_bound(B + 1, B + n + 1, -A[i]) - B;
		r = upper_bound(B + 1, B + n + 1, -A[i]) - B;
		ans += r - l;
	}
	printf("%lld\n", ans);

	return 0;
}
```

---

## 作者：Fire_flame (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc166_e)

## $\mathtt{Solution}$

首先根据题目大意，可以列出下面的式子：

$$a_i-a_j=j-i$$

变换一下得：

$$a_i-i=a_j+j$$

我们可以枚举 $i$，所以 $i,a_i$ 都是已知的。

此时我们可以用一个 map 在循环过程中把 $a_i-i$ 记录下来，然后记录答案即可。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int s=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+(ch-'0');ch=getchar();}
	return s*f;
}
const int MAXN=2e5+5;
int n;
int a[MAXN];
map<int,int>num;
int ans;
signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)ans+=num[i-a[i]],num[a[i]+i]++;
	printf("%lld",ans);
	return 0;
}

```


---

## 作者：yuheng_wang080904 (赞：1)

## 题意

给出 $n(2\le n\le 2\times 10^5)$ 个数 $A_1,A_2,\cdots,A_n(1\le A_i\le10^9)$。求出有多少对 $(x,y)$ 满足 $|x-y| = A_x+A_y$。

## 思路

我们令 $x<y$。

化简原式得 $y-x=A_x+A_y$，整理一下就是 $y-A_y=A_x+x$。

于是我们就可以用 map 维护 $i+A_i$ 出现的次数。对于每次输入，我们看 $i-A_i$ 与前面的那些和有几个相同的，加在 $ans$ 中，然后再将 map 中 $i+A_i$ 的和个数加一即可。

## 代码

接下来放上我的代码供参考。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[200005],ans;
map<int,int>m;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
	cin>>a[i];
	ans+=m[i-a[i]];
	m[i+a[i]]++;
    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：EthanC_ (赞：1)

本题并没有想象中的难。
## 思路：
首先，我们将式子转换一下：
- $ j-i=A_i+A_j $
- $ j-A_j=i+A_i $

我们直接遍历 $ A $ 数组，用map存储 $ A_i+i $ 的个数。然后我们就遍历 $ n $ 次，先将第 $ i $ 个元素看成 $ j $，将 $ ans+=m[i-A_i] $，再将第 $ i $ 个元素看成 $ i $，将 $ m[A_i+i] $ 加一即可。
## 代码：
```cpp
#include<iostream>
#include<map>;
using namespace std;
map<int,int> m;
int n,a[1000001];
int main(){
    cin>>n;
    long long ans=0;
    for(int i=0;i<n;++i){
        cin>>a[i];
        ans+=m[i-a[i]];
        m[a[i]+i]++;
    }
    cout<<ans<<endl;
}
```


---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc166_e)

## 思路

首先呢，我们要推一个式子，使这道题更好做。

题目中的 $j-i=A_i+A_j$，移项得 $(A_i+i)+(A_j-j)=0$。显然，$(A_i+i)$ 与 $(A_j-j)$ 互为相反数。

这时候我们就想到利用 STL 库中的 ``upper_bound`` 和 ``lower_bound`` 函数，以 $O(\log n)$ 的时间复杂度来查找差最小的 $(A_j-j)-(A_i+i)$。查找 $n$ 次，每次查找完就算出 ``upper_bound`` 与 ``lower_bound`` 查找出的两个数之差，并相加。

- 最后别忘换行。

## 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200010;
long long n,a[N],x[N],y[N],l,r,ans;
int main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        x[i]=a[i]+i;
        y[i]=a[i]-i;
    }
    sort(y+1,y+1+n);//二分查找需要排序。
    for(int i=1;i<=n;++i){
        l=lower_bound(y+1,y+1+n,-x[i])-y;//因为二分查找时返回的是位置，所以最后别忘减去 y。
        r=upper_bound(y+1,y+1+n,-x[i])-y;
        ans+=r-l;
    }
    cout<<ans<<endl;
    return 0;
}
~~~

[已 AC](https://www.luogu.com.cn/record/96595010)

---

## 作者：Otue (赞：0)

这题也配叫 ABC E 题？赛时 $3000$ 人 AC。

对原式进行移项：$j-A_j=i+A_i(i<j)$，那么对于每一个 $j$ 来说，直接看前面有多少个 $i$ 满足 $j-A_j=i+A_i$ 即可。

具体步骤：
* vis 数组统计每个数出现了多少次
* 循环枚举 $1\leq i \leq n$，答案加上 $vis_{j-A_j}$，同时也要更新 $vis$ 数组。

**参考代码：**
```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, a[N], ans;
map<int, int> vis;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		ans += vis[i - a[i]];
		vis[a[i] + i]++;
	}
	cout << ans << endl;
}
```

---

## 作者：kaceqwq (赞：0)

# 题目大意：
给定一个长度为 $n$ 的序列 $A$ ，求有多少组 $i$ ， $j$ 满足：

1. $i<j$
2. $j-i=A_i+A_j$

# 分析：
我们可以先运用等式的性质，把第2条转化为： $j-A_j=A_i+i$，然后问题就很简单了，我们可以用 map 来维护 $A_i+i$ 的数量，接着我们把 $i-A_i$ 与之前的和相同的数量累加起来作为答案，然后再将 map 中 $i+A_i$ 的个数加一即可。

# Code：
```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
map<int, int> mapp;   
int n, a[200005], ans=0;
signed main() {
	ios::sync_with_stdio(0);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        ans += mapp[i - a[i]];
        mapp[a[i] + i]++;
    }
    cout << ans << '\n';
    return 0;
}
```


---

## 作者：Lyu_echo (赞：0)

[题面](https://www.luogu.com.cn/problem/AT5309)


思路：
------------
先看题目:


给定一个长度为 $N$ 的序列 $A$,求有多少组 $i,j$ 满足:

- $i<j$
- $j - i = A_i + A_j$


~~俗话说  '暴力出奇迹’，所以拿到这道题肯定是先写暴力。~~ 看看数据范围：

- $2 \le N \le 2\times10^5$

暴力超时无疑。

看到 $10^5$ 的 $N$，肯定就要想到时间复杂度 $O(N\log N)$ 或者 $O(N)$ 算法。

那么，这道题目怎么搞 $O(N)$ 算法尼？

我们将将式子 $j - i = A_i + A_j$  转化一下，变成 $j - A_j = i + A_i$ 。

~~所以，我们只需要求 $j - A_j = i + A_i$ 的个数就好了~~（废话）

**如何求得个数呢?**  ~~枚举~~

用数组 $S$ 存储每一个 $i + A_i$ 的个数 ,再遍历一遍数组 $S$ 就好了。

遍历的过程中，对于每一个 $i$ ,先将每一个 $S_i$ 累加（即累加满足 $i-A_i$ 的 $i$ 的个数），再将当前的 $i+A_i$ 记录下来。

再看数据范围： 

- $1\le A_i\le 10^9(1\le i\le N)$

$A_i$ 已经去到了 $10^9$，再加上最大 $10^5$ 的 $i$， 用下标记录 $i+A_i$ 的值肯定是不现实的。

这个时候怎么办呢？？？

**用 map 映射一下**（ 不会 map 的可以看[这里](https://blog.csdn.net/sevenjoin/article/details/81943864?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522165888729616782184640955%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=165888729616782184640955&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-81943864-null-null.142^v35^pc_rank_34,185^v2^control&utm_term=map) ）


代码：
------------

```cpp
#include<bits/stdc++.h>
#define int long long  //十年oi一场空，不开long long见祖宗 
using namespace std;
map<int,int>s; //用来记录A[i]+i的数组s，不过A[i]太大，要映射一下 
int n,t,ans;  
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>t; 	  //因为一遍循环就跑完了， 没必要记录每一个A[i]，所以用t来暂存当前的A[i] 
		ans+=s[i-t];  //处理。将每一个s[i]的值累加，即记录有多少合法的A[i]-i 
		s[t+i]++;     //记录当前的A[i]+i
		//map每次[]操作时间复杂度O(logN) 
	}
	cout<<ans;
	return 0; //完美结束 
}
//总体时间复杂度为 循环*map操作。即O(NlogN) 

```



---

## 作者：little_rubbish (赞：0)

## 思路
因为 $2\le n\le2\times10^5$ ，如果直接暴力枚举的话显然是行不通的。

我么不妨对原式进行转换：

原式： $j-i=A_i+A_j$

转换后： $j-A_j=i+A_i$

我们就只需寻找 $j-A_j=i+A_i$ 的个数就好了。

#### 如何寻找呢
我们可以用一个数组来记录 $A_i+i$ 的个数，枚举一遍便可以得到答案。

#### 注意事项 
1. 因为考虑到 $i\le A_i \le 10^9$ 记录 $A_i+i$ 的个数的数组可以用 `map` 。

2. 答案可能会很大,要开 `long long ` 。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200001];
long long ans;
map<int,int>c;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		ans+=c[i-a[i]];//将符合条件的加起来
		c[a[i]+i]++;//记录
	}
	cout<<ans<<"\n";//记得换行
	return 0;
}
```


---

## 作者：AmamiyaYuuko (赞：0)

提供一个完全线性的做法.

将式子移项后得到 $j - a_j = i + a_i$.

注意到 $i, a_i$ 均非负, 则 $j - a_j$ 也非负.

若 $j - a_j$ 非负, 有可能作为答案的 $j$ 必须满足 $a_j < j$.

显然有 $1 \le a_j < n$.

将值域转换为 $[1, n)$ 后就随便写了.

代码: 

```cpp
read(n);
for (int i = 1; i <= n; ++i)    read(a[i]);
for (int i = 1; i <= n; ++i) {
    if (i - a[i] > 0) {
        ++t[i - a[i]];
    }
}
for (int i = 1; i <= n; ++i) {
    if (a[i] + i < n) {
        ans += t[a[i] + i];
    }
}
printf("%lld\n", ans);
return 0;
```

---

## 作者：juicyyou (赞：0)

# AT5309 [ABC166E] This Message Will Self-Destruct in 5s
## 题目大意：
给定一个长度为 $n$ 的数列 $a$，求有多少组 $(i, j)$ 满足：
$$i < j$$
且：
$$j - i = a_i + a_j$$
## 解法：
我们首先给这个式子变一下形：
$$j - i = a_i + a_j (i < j)$$
就可以推出：
$$a_i + i = j - a_j(i < j)$$
那么，我们就可以用一个 $map$ 去维护所有的：
$$j - a_j$$
的出现次数，然后直接统计即可。

下面是我的Code：
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<stack>
#include<vector>
#include<map>
#include<queue>
#include<cmath>
#include<set>
#include<cstdlib>
#include<cctype>
#include<ctime>
#include<utility>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll maxn = 2e5 + 5;
const ll maxm = 1e3 + 5;
template<class T>
inline T qread(T &IEE){
	register T x = 0, f = 1;
	register char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -f;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return IEE = x * f;
}
ll cnt, n;
ll a[maxn];
map<ll, ll> miu;
int main(){
//	freopen("1.in", "r", stdin);
//	freopen("1.out", "w", stdout);
	qread(n);
	for(int i = 1;i <= n;i++){
		qread(a[i]);
		miu[i - a[i]]++;
	}
	for(int i = 1;i <= n;i++){
		miu[i - a[i]]--;
		cnt += miu[a[i] + i];
	}
	cout << cnt << endl;
	return 0;
}
```
上述算法的时间复杂度为 $O(n \log n)$，可以通过此题。

---

## 作者：君のNOIP。 (赞：0)

设 $i<j$

有 $j-i=A_i+A_j$

即 $j-A_j=A_i+i$

我们用 map 记录 $A_i+i$ 的个数（下文记作 $mp[i]$），初始都为 0。

那么我们只需将 $A_i$ 从 $1$ 到 $n$ 遍历一遍，对于第 $i$ 个元素，我们先将他作为 $j$，答案加上 $mp[i-A_i]$，然后再将其作为 $i$，即将 $mp[A_i+i]$ 加 1。

Code：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<map>
using namespace std;
#define G() Cr = getchar()
#define LL long long
int Xr; char Cr;
inline int rd() {
	Xr = 0, G();
	while(Cr < '0' || Cr > '9') G();
	while(Cr >= '0' && Cr <= '9') Xr = (Xr<<1) + (Xr<<3) + (Cr&15), G();
	return Xr;
}
#define MAX_N 200005
int n;
int va[MAX_N];
map<int,int>mp;
LL ans;
int main() { 
	n = rd();
	for(int i = 1; i <= n; i++) {
		va[i] = rd();
		ans += mp[i-va[i]];
		mp[va[i]+i]++;
	}
	cout<<ans;
}
```


---

## 作者：钓鱼王子 (赞：0)

一个很老的问题，化一下式子。

$A_j+A_i=j-i$

$A_j=j-i-A_i$

令每一个 $A_i+=i$，得到 $A_j=-A_i$

也就是说，找相反数的对数。

map 即可。

```cpp
#include<bits/stdc++.h>
#define in inline
#define int long long
#define re register
using namespace std;
in int read() {
	re int t=0;
	re char v=getchar();
	while(v<'0'||v>'9')v=getchar();
	while(v>='0'&&v<='9') {
		t=(t<<3)+(t<<1)+(v^48);
		v=getchar();
	}
	return t;
}
map<int,int>v;
int n,m,ans,a[200002];
signed main(){
	n=read();
	for(re int i=1;i<=n;++i){
		a[i]=read();
	}
	for(re int i=n;i;--i){
		ans+=v[-(i+a[i])];
		++v[a[i]-i];
	}
	printf("%lld",ans);
}
```


---

