# Odd Queries

## 题目描述

You have an array $ a_1, a_2, \dots, a_n $ . Answer $ q $ queries of the following form:

- If we change all elements in the range $ a_l, a_{l+1}, \dots, a_r $ of the array to $ k $ , will the sum of the entire array be odd?

 Note that queries are independent and do not affect future queries.

## 说明/提示

For the first test case:

- If the elements in the range $ (2, 3) $ would get set to $ 3 $ the array would become $ \{2, 3, 3, 3, 2\} $ , the sum would be $ 2+3+3+3+2 = 13 $ which is odd, so the answer is "YES".
- If the elements in the range $ (2, 3) $ would get set to $ 4 $ the array would become $ \{2, 4, 4, 3, 2\} $ , the sum would be $ 2+4+4+3+2 = 15 $ which is odd, so the answer is "YES".
- If the elements in the range $ (1, 5) $ would get set to $ 5 $ the array would become $ \{5, 5, 5, 5, 5\} $ , the sum would be $ 5+5+5+5+5 = 25 $ which is odd, so the answer is "YES".
- If the elements in the range $ (1, 4) $ would get set to $ 9 $ the array would become $ \{9, 9, 9, 9, 2\} $ , the sum would be $ 9+9+9+9+2 = 38 $ which is even, so the answer is "NO".
- If the elements in the range $ (2, 4) $ would get set to $ 3 $ the array would become $ \{2, 3, 3, 3, 2\} $ , the sum would be $ 2+3+3+3+2 = 13 $ which is odd, so the answer is "YES".

## 样例 #1

### 输入

```
2
5 5
2 2 1 3 2
2 3 3
2 3 4
1 5 5
1 4 9
2 4 3
10 5
1 1 1 1 1 1 1 1 1 1
3 8 13
2 5 10
3 8 10
1 10 2
1 9 100```

### 输出

```
YES
YES
YES
NO
YES
NO
NO
NO
NO
YES```

# 题解

## 作者：Loser_Syx (赞：6)

## 思路

看到题目数据范围 $1 \leq n \leq 10^4, 1 \leq q \leq 2 \cdot 10^5$。显然数据范围这么大不是让你跑暴力的，由于一组数据的查询都是基于原数组的，而且还要统计总和，那么我们就可以考虑使用前缀和优化，前缀和查询的复杂度是 $O(1)$ 的，并不用担心超时。

每次查询时，我们可以分 $3$ 段来统计总和（此处前缀和数组为 $s$）：

第一段：在 $l$ 端点前面的数的和，也就是 $s_{l-1}$。

第二段：从 $l$ 端点开始，再到 $r$ 端点结束，这么一段中每个数由于被替换成了 $k$，所以总和为 $k \times (l - r + 1)$。

第三段：从 $r + 1$ 端点开始，直到 $n$ 端点结束，这么多的总和是 $s_n - s_r$。

不过题意确实挺坑的，一开始我第二段当成了替换为 $k$，而正确答案是里面的所有数都替换为 $k$。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define int long long
#define f(W, X, Y, Z) for(int W = X; W <= Y; W += Z)
#define F(W, X, Y, Z) for(int W = X; W >= Y; W -= Z)
#define debug puts("QAQ")
inline int read(){
	register int x = 0, s = 1;
	char c = getchar();
	while(c < '0' || c > '9'){
		if(c == '-') s = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		x = (x << 1) + (x << 3) + (c ^ '0');
		c = getchar();
	}
	return x * s;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9) write(x / 10);
	putchar((x % 10) + '0');
}
int a[200010], s[200010];
signed main(){
	int T = read();
	while(T--){
		int n = read(), q = read();
		s[0] = 0;
		f(i, 1, n, 1){
			a[i] = read();
			s[i] = s[i - 1] + a[i];//统计前缀和
		}
		while(q--){
			int l = read(), r = read(), k = read();
			int ans = s[l - 1] + s[n] - s[r] + k * (r - l + 1);
			if(ans % 2 == 1) puts("YES");
			else puts("NO");
		}
	}
	return 0;
}
```

---

## 作者：Larryyu (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1807D)
## _Description_
对于长度为 $n$ 的数列 $a$，有 $q$ 次询问，每次给定 $l,r,k$，问将 $a_l,a_{l+1}\dots a_r$ 全都转为 $k$ 后，该数列的总和是否为奇数。

注意，每次操作对后续操作没有影响，即每次操作都是在原数列 $a$ 上做操作。
## _Solution_
我们将每次操作完后分为两部分：操作部分和未操作部分。

操作部分总和为 $(r-l+1)\times k$，未操作部分为 $sum_n-(sum_r-sum_{l-1})$，其中 $sum_i$ 表示前 $i$ 个数的总和。

前缀和在输入时即可得到。

最后将两部分加起来，看是否为奇数即可。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int t;
ll sum[200200];
ll read(){
    ll x=0,f=1;
    char ch;
    ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void solve(){
	int n=read(),q=read();
	sum[0]=0;
	for(int i=1;i<=n;i++){
		sum[i]=0;
		int x=read();
		sum[i]=sum[i-1]+x;//求得前缀和
	}
	while(q--){
		int l=read(),r=read(),k=read();
		ll i=sum[n]-(sum[r]-sum[l-1]),j=k*(r-l+1); //分为两部分
		if((i+j)%2==0){
			cout<<"NO"<<endl;
		}else{
			cout<<"YES"<<endl;
		}
	}
}
int main(){
	t=read();
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：minVan (赞：1)

**题目大意**

给定一个长度为 $n$ 的数组 $a$，问将 $a_l$ 到 $a_r$ 全部变为 $k$ 后，整个数组的和是否为奇数，是则输出 `YES`，不是则输出 `NO`。

**解题思路**

先做一下前缀和，即 $s_0 = 0$ 且 $s_i=s_{i-1} + a_i$，则 $s_n$ 为原数组的和。

对于每次询问 $l,r,k$，定义 `tmp` 为 $s_n + s_y - s_{x - 1} + k \times (y - x + 1)$，如果 `tmp` 为奇数，则输出 `YES`，否则输出 `NO`。

**AC 代码，请勿抄袭**

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int a[N], sum[N];
signed main() {
    int t;
    cin >> t;
    while(t--) {
        int n, q;
        cin >> n >> q;
        sum[0] = 0;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            sum[i] = sum[i - 1] + a[i];
        }
        while(q--) {
            int x, y, k;
            cin >> x >> y >> k;
            cout << ((sum[n] + sum[y] - sum[x - 1] + k * (y - x + 1)) & 1 ? "YES" : "NO") << '\n';
        }
    }
    return 0;
}
```

---

## 作者：qifan_maker (赞：0)

### 题目链接
[洛谷](https://www.luogu.com.cn/problem/CF1807D)

[Codeforces](https://codeforces.com/contest/1807/problem/D)
### 题意分析
共 $t$ 组测试数据，每组测试数据给定一个长度为 $n$ 的数组 $a$，并进行 $q$ 次查询，每次查询给定三个变量 $l,r,k$，问将 $a_l,a_{l+1},\dots,a_r$ 全部替换为 $k$ 后，数组 $a$ 所有值得和如果为奇数，输出 `YES`，否则输出 `NO`。
### 题目解法
如果我们希望得到 $a_l,a_{l+1},\dots,a_r$ 的值，直接遍历一遍并累加的效率比较低，我们需要用到**前缀和**算法。前缀和算法比较简单，这里就不过多介绍了，不了解的朋友可以去 [OI-wiki](https://oi-wiki.org/basic/prefix-sum/) 看看。

查询时按照题意：用 $a$ 的所有值（前缀和预处理后的 $a_n$）减去 $a_l,a_{l+1},\dots,a_r$ 的值（前缀和预处理后的 $a_r-a_{l-1}$）再加上 $(r-l+1)\times k$，如果最终答案为奇数，就输出 `YES`，否则输出 `NO`。

时间复杂度 $\mathcal{O}(n+q)$。
### [AC](https://www.luogu.com.cn/record/106150725) Code
```cpp
/*
题目编号：
D. Odd Queries
思路：
前缀和预处理数据 
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--){
		int n,q;
		int a[200100];
		cin >> n >> q;
		for (int i=1;i<=n;i++){
			cin >> a[i];
			a[i] += a[i-1];     //前缀和预处理 
		}
		while (q--){
			int l,r,k;
			cin >> l >> r >> k;
			if ((a[n] - (a[r]-a[l-1]) + (r-l+1)*k) % 2 == 1){      //由于这里的范围是左闭右开的，所以 a[l] 要减 1，r-l 也要加一 
				cout << "YES" << endl;
			}
			else {
				cout << "NO" << endl;
			}
		}
	} 
	return 0;
}

```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1807D)

## 思路

使用**前缀和**来解题。

读入改变的区间 $l$ 和 $r$ 后，如果 $a_1\sim a_n$ 和减去 $a_l\sim a_r$ 的和再减去 $(r-l+1)\times k$ 的差是奇数，则进行完这步操作的数组之和为奇数,否则为偶数。

- 数据范围最大可以到 $2\times 10^{14}$，记得开 long long。

## AC 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int t,n,x,q;
long long sum[N],l,r,k;
int main(){
	cin>>t;
	while(t--){
		scanf("%d%d",&n,&q);
		for(int i=1;i<=n;++i){
			scanf("%d",&x);
			sum[i]=sum[i-1]+x;//前缀和。
		}
		while(q--){
			scanf("%lld%lld%lld",&l,&r,&k);
			long long tmp1=sum[r]-sum[l-1],tmp2=(r-l+1)*k;
			if((sum[n]-tmp1-tmp2)&1)printf("yes\n");
			else printf("no\n");
		}
	}
	return 0;
}
~~~

---

## 作者：云裳 (赞：0)

**思路**

比较套路的题。

对于每组数据，我们定义数列 $\left \{  a_n\right \} $ 的前缀和为 $pre_n=  \sum\limits_{i=1}^{n}  a_i=a_1+a_2+\cdots+a_n$。

对于每次询问的 $l,r,k$，改变之后的 $\sum\limits_{i=1}^{n} a_i$ 就等于 $pre_n-pre_r+pre_{l-1}+k\cdot(r-l+1)$。因为，$pre_n-pre_r+pre_{l-1}$ 是在改变之前的 $\sum\limits_{i=1}^{n} a_i-\sum\limits_{i=l}^{r} a_i$，$k\cdot(r-l+1)$就是改变之后的 $\sum\limits_{i=l}^{r} a_i$。因此 $pre_n-pre_r+pre_{l-1}+k\cdot(r-l+1)$ 就是改变之后的 $\sum\limits_{i=1}^{n} a_i$。

这样，每次询问判断 $pre_n-pre_r+pre_{l-1}+k\cdot(r-l+1)$ 的奇偶性就好了。

**代码**

```cpp
void solve() {
  int n, q;
  cin >> n >> q;
  int a[200007], pre[200007];
  for(int i=1;i<=n;i++) cin >> a[i];
  for(int i=1;i<=n;i++) pre[i] = pre[i - 1] + a[i];//前缀和
  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;
    ll sum = pre[n] - pre[r] + pre[l - 1] + (r - l + 1) * k;
    cout << (sum % 2 ? "YES\n" : "NO\n");
  }
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  ll t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}
```



---

## 作者：__LiChangChao__ (赞：0)

# 题意
给你一个数组，每次选定一个区间 $l,r$，将区间内所有数字改为 $k$（**每次修改不会影响到原数组**），请问现在这个数组的和是否是奇数？

# 思路
由于修改并不会影响到原数组，考虑**前缀和**。

可以先计算原数组之和的奇偶性，再计算被修改区间之和的奇偶性和修改后的区间之和奇偶性，如果原数组的和是奇数，并且原区间之和与修改后的区间之和的奇偶性是**一样**的，则不会影响原数组之和整体奇偶性。如果原数组的和是偶数，并且原区间之和与修改后的区间之和的奇偶性**不同**，也不会影响原数组之和整体奇偶性。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a,k,t,n,q,l,r,f;
int main() {
	cin>>t;
	while(t--) {
		scanf("%lld%lld",&n,&q);
		long long sum[200005]={0};//前缀和数组
		for(int i=1; i<=n; i++) {
			scanf("%lld",&a);
			sum[i]=sum[i-1]+a;//计算前缀和
		}
		f=sum[n]%2;//计算原数组之和的奇偶性
		while(q--) {
			scanf("%lld%lld%lld",&l,&r,&k);
			long long b=((r-l+1)*k)%2,c=(sum[r]-sum[l-1])%2;//计算原区间之和与修改后的区间之和的奇偶性
			if((b==c&&f==1)||(b!=c&&f==0)) cout<<"YES\n";
			else cout<<"NO\n";
		}
	}
	return 0;
}
```

---

## 作者：LegendaryGrandmaster (赞：0)

前缀和处理一下数列。

接下来的询问，如果区间各数之和的奇偶和修改后此区间的奇偶一样，则这个数列奇偶不改变；否则改变。

原本此区间各数之和（前缀和知识）：$S_r-S_{l-1}$。

此区间长度：$r-l+1$。

变化后的各数之和（$k$ 为改变后的数）: $k \times (r-l+1)$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int a[N],s[N];
signed main()
{
	int t;
	cin>>t;
	while(t--){
		memset(s,0,sizeof(s));
		int n,q;
		cin>>n>>q;
		for(int i=1;i<=n;i++)cin>>a[i],s[i]=s[i-1]+a[i];
		while(q--){
			int l,r,k;
			cin>>l>>r>>k;
			int a1=s[r]-s[l-1];
			int a2=k*(r-l+1);
			int ans=s[n];
			if(s[n]&1)cout<<(a1%2==a2%2?"YES":"NO")<<'\n';
			else cout<<(a1%2==a2%2?"NO":"YES")<<'\n';
		}
	}
}
```

---

## 作者：Iniaugoty (赞：0)

~~关于这么水的题都能交题解这件事。~~

***

## 题意

给出一个序列 $a_i(1\le i\le n)$ 和 $q$ 次操作。

对于每次操作，查询：**如果**将 $[l,r]$ 中的每个数都替换为 $k$，$\sum_{i=1}^{n}a_i$ 是否是奇数。是则输出 $\text{yes}$，否则输出 $\text{no}$。

***

## 解法

注意到每次操作不会真的更改，不需要用什么乱七八糟线段树，静态维护即可，考虑使用**前缀和**。

设 $s_i=\begin{cases}
0&i=0\\
s_{i-1}+a_i&i>0
\end{cases}$，

则 $\sum_{i=1}^{n}a_i=s_n$，$\sum_{i=l}^{r}a_i=s_r-s_{l-1}$。

那么每次查询的序列总和就是 $s_n-s_r+s_{l-1}+k(r-l+1)$。

***

## 代码

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int t,q,n,a[N],s[N];
signed main(){
	scanf("%d",&t);
	while(t--){
		memset(a,0,sizeof(a));
		memset(s,0,sizeof(s));
		scanf("%d%d",&n,&q);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
		for(int i=1,l,r,k;i<=q;i++){
			scanf("%d%d%d",&l,&r,&k);
			int ans=s[n]-(s[r]-s[l-1])+(r-l+1)*k;
			puts(ans&1?"yes":"no");
		}
	} 
	return 0;
}
```

***

全文完。

---

## 作者：Ariasaka (赞：0)

# 题目大意

给你一个长度为 $n$ 的数列，有 $q$ 次询问，每一次询问给出 $3$ 个参数 $l, r, k$，将 $[l,r]$ 范围内的数修改为 $k$ ，计算当前的数列所有项的和是否为奇数，如果是，输出 `YES`，否则输出 `NO` （每一次询问不影响数列原本的元素）

当然按照 CF 的习惯，会给出 $T$ 个测试用例。

# 思路

维护一个前缀和数组来存储数列每一项前面所有元素之和（包括这一项），每一次询问时因为要把 $[l,r]$ 范围内的数修改为 $k$ ，所以把原本的总和 (`pref[n]`) 减掉 $[l,r]$ 范围内的数（`pref[r]-pref[l-1]`），再加上 $(r-l+1)×k$ 即为修改数据后数列的总和，判断输出即可。

# 代码

```
#include <bits/stdc++.h>
#define ll long long //不开见祖宗
ll n,q,arr[1919810],b[1919810]={0},t,l,r,k; //定义一定放在外面！！！不然放循环里局部变量会T的
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>n>>q;
		for(int i=1;i<=n;i++){
		 	cin>>arr[i];
		 	b[i]=arr[i]+b[i-1]; //维护前缀和
		}
		for(int i=1;i<=q;i++){
			cin>>l>>r>>k;
			if((b[n]-(b[r]-b[l-1])+(r-l+1)*k)%2) cout<<"YES\n"; //每一次询问时计算总和并判断
			else cout<<"NO\n";
		}
	} 
	return 0;
}
```

---

## 作者：_299817_ (赞：0)

## Part 1: 题意简述

你有一个长为 $n$ 的数列：$a_1, a_2, \dots, a_n$，接下来有 $q$ 次询问，每次询问给定 $3$ 个数：$l$、$r$、$k$，问如果把 $a_l , \dots, a_r$ 的值全部改成 $k$，最后数列的所有数的和是否为奇数。

注意每次询问不会对后来的询问产生影响，即询问不会改变原数列。

## Part 2: 思路

由于每次询问不会改变原数列，那么我们就可以用离线算法。

我们可以每次将 $a_l, \dots,a_r$ 的和全部求出来，接着把原来的数列在总和减去 $a_l, \dots,a_r$ 的和，再加上 $(r - l + 1) \times k$，看这个值是否为奇数即可。

既然是离线求和，就自然想到前缀和啦！

## Part 3: 代码

~~蚂蜂比较奇怪，轻喷。~~

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#define sort stable_sort
#define map unordered_map
using namespace std;
typedef long long ll;

ll T;
ll n, q;
ll a[200010];
ll sum[200010];
ll ssum;
ll l, r, k;

//注意题目范围，a[i] 是小于10的9次方的数，所以要开long long。

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while(T--){
        cin >> n >> q;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
        } // 输入
        sum[0] = 0;
        for(int i = 1; i <= n; i++){
            sum[i] = sum[i - 1] + a[i];
        } // 前缀和
        ssum = sum[n]; // 数列中所有的数的总和
        while(q--){
            cin >> l >> r >> k;
            ll now = sum[r] - sum[l - 1]; // a[l]到 a[r]的区间和
            if((ssum - now + k * (r - l + 1)) % 2 == 1){ // 判断改变区间后数列中所有数的和是否为奇数
                cout << "YES" << endl;
            }else{
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}

```

---

## 作者：ダ月 (赞：0)

### 题意概要：

给定长度为 $n$ 的序列 $a_i$，进行 $q$ 次询问，每次询问给定三个正整数 $l,r,k$，先将 $a_{l,l+1,\dots,r-1,r}$ 中所有的数替换成 $k$，问 $\sum_{i=1}^na_i$ 是否为奇数。操作都为临时操作。

### 题目分析：

我们可以直接模拟，可以得到一个 $O(qn)$ 的超时做法。

我们考虑优化，记录 $a_i$ 的前缀和 $S_i$，$S_i=\sum_{i=j}^ia_i$。显然，在未修改之前序列中所有数的和为 $S_n$。每次修改，先删掉 $l$ 到 $r$ 中所有 $a_i$，即 $S_r-S_{l-1}$，再加上 $(r-l+1)k$，做出判断即可。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
const int N=2e5+10;
int n,q;
ll a[N],s[N];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&q);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i];
		while(q--){
			ll l,r,k;scanf("%lld%lld%lld",&l,&r,&k);
			ll sum=s[n]-(s[r]-s[l-1])+k*(r-l+1);
			puts(sum&1?"YES":"NO");
		}
	}
}
```

数据很大，别忘记开 `long long`。

时间复杂度：$O(n+q)$。

---

## 作者：封禁用户 (赞：0)

**【翻译】**

共 $T$ 组询问，每次给定 $n$ 个整数 $a_1,a_2,...,a_n$。接下来有 $m$ 次询问，每次给定 $l,r,k$，若将 $a_l,a_{l+1},...,a_{r-1},a_r$ 的值都修改成 $k$，问整个数组的和是否为奇数？

**【分析】**

因为我们是修改的 $l$ 到 $r$，所以我们可以用前缀和将除修改的区间的值全算出来。再将修改的区间的总和加进去，判断奇偶即可。

**【代码】**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int t;
int n,m;
int a[N],s[N];
int main()
{
	cin>>t;
	while(t--) 
	{
		memset(s,0,sizeof(s));
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>a[i],s[i]=s[i-1]+a[i];
		while(m--)
		{
			int l,r,k;cin>>l>>r>>k;
			int sum=s[l-1]+(s[n]-s[r]);
			sum+=(r-l+1)*k;
			if(sum&1) cout<<"YES\n";
			else cout<<"NO\n";
		}
	}
	return 0;
} 
```

---

