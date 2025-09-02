# [ABC344C] A+B+C

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc344/tasks/abc344_c

$ 3 $ 個の数列 $ A=(A_1,\ldots,A_N),\ B=(B_1,\ldots,B_M),\ C=(C_1,\ldots,C_L) $ が与えられます。

さらに数列 $ X=(X_1,\ldots,X_Q) $ が与えられるので、各 $ i=1,\ldots,Q $ に対して次の問題を解いてください。

問題：$ A,B,C $ からそれぞれ $ 1 $ 個ずつ要素を選び、和を $ X_i $ にすることができるか？

## 说明/提示

### 制約

- $ 1\ \leq\ N,M,L\ \leq\ 100 $
- $ 0\ \leq\ A_i,\ B_i\ ,C_i\ \leq\ 10^8 $
- $ 1\ \leq\ Q\ \leq\ 2\times\ 10^5 $
- $ 0\ \leq\ X_i\ \leq\ 3\times\ 10^8 $
- 入力は全て整数である

### Sample Explanation 1

\- $ A,B,C $ からそれぞれ $ 1 $ 個ずつ要素を選び和を $ 1 $ にすることはできません。 - $ A,B,C $ からそれぞれ $ 1,2,2 $ を選ぶと和を $ 5 $ にすることができます。 - $ A,B,C $ からそれぞれ $ 2,4,4 $ を選ぶと和を $ 10 $ にすることができます。 - $ A,B,C $ からそれぞれ $ 1 $ 個ずつ要素を選び和を $ 50 $ にすることはできません。

## 样例 #1

### 输入

```
3
1 2 3
2
2 4
6
1 2 4 8 16 32
4
1 5 10 50```

### 输出

```
No
Yes
Yes
No```

# 题解

## 作者：xxboyxx (赞：5)

### 思路

要求三序列的值的和是否存在，就可以先算出所有值的和的可能性，再存入容器中。$ 1\ \leq\ N,M,L\ \leq\ 100 $，时间复杂度 $O(NML)$ 就能预处理出来。

### 注意

序列中的值很大，数组是存不下的，这时候就需要 `map`，来记录某值是否存在。

### 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,l,q;
int a[105];
int b[105];
int c[105];
map<int,int> p;
signed main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
		cin>>a[i];
	cin>>m;
	for (int i=1;i<=m;i++)
		cin>>b[i];
	cin>>l;
	for (int i=1;i<=l;i++)
		cin>>c[i];
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			for (int k=1;k<=l;k++)
				p[a[i]+b[j]+c[k]]=1;//值存在 
	cin>>q;
	while (q--)
	{
		int x;
		cin>>x;
		if (p[x]==1)
			cout<<"Yes\n";
		else
			cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：OIer_Tan (赞：2)

## 题意

给你三个序列 $A=(A_1,\cdots,A_N)$、$B=(B_1,\cdots,B_M)$ 和 $C=(C_1,\cdots,C_L)$。

此外，还给出了一个序列 $X=(X_1,\ldots,X_Q)$。针对每个 $i=1,\ldots,Q$ 求解下面的问题：

问题：能否从 序列 $A$、$B$ 和 $C$ 中各选择一个元素，使它们的和为 $X_i$？

## 思路

很明显，序列 $A$、$B$、$C$ 的长度不大于 $100$，所以我们可以以 $O(NML)$ 的时间复杂度枚举出所有加起来可能出现的数。因为所有和的可能数不超过 $10^6$，所以可以存下。最后再对每个 $X_i$ 进行枚举，找出可能的答案数。

因为我们要对和进行去重并尽量快速的查找，所以可以使用 `unordered_set` 或 `set` 进行查找。

使用 `set` 的总时间复杂度为 $O(NML\log (NML)+Q \log (NML))$，使用 `unordered_set` 的总时间复杂度为 $O(NML+Q)$，均可通过本题。

## 代码

以下为用 `unordered_set` 实现的代码。

```cpp
#include<bits/stdc++.h>

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

ll n , m , l ;

const ll N = 105 ;

ll a [N] , b [N] , c [N] ;

unordered_set <ll> cnt ;

int main ()
{
	// freopen ( ".in" , "r" , stdin ) ;
	// freopen ( ".out" , "w" , stdout ) ;
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	cin >> n ;
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		cin >> a [i] ;
	}
	cin >> m ;
	for ( ll i = 1 ; i <= m ; i ++ )
	{
		cin >> b [i] ;
	}
	cin >> l ;
	for ( ll i = 1 ; i <= l ; i ++ )
	{
		cin >> c [i] ;
	}
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		for ( ll j = 1; j <= m ; j ++ )
		{
			for ( ll k = 1 ; k <= l ; k ++ )
			{
				cnt.insert ( a [i] + b [j] + c [k] ) ;
			}
		}
	}
	ll q ;
	cin >> q ;
	while ( q -- )
	{
		ll x ;
		cin >> x ;
		if ( cnt.find ( x ) != cnt.end () )
		{
			cout << "Yes" << "\n" ;
		}
		else
		{
			cout << "No" << "\n" ;
		}
	}
	return 0 ;
}
```

---

## 作者：littlebug (赞：2)

**形式化题意**：给定序列 $\{a\},\{b\},\{c\}$，$q$ 次询问，每次询问给定 $x$，求是否存在 $a_i,b_j,c_k$，使得 $a_i+b_j+c_k=x$。

注意到，数据范围中 $n,m,l\le100$，所以可以枚举所有可能组成的数字，即枚举所有 $a_i,b_j,c_k$，存到一个数组 $ans$ 里。时间复杂度 $O(nml)$，算出来大概 $10^6$，完全没问题。

然后对数组 $ans$ 进行排序，在每次询问时二分查找即可。

设 $s=nml$，则总共时间复杂度为 $O(s+s\log s+q\log s)$，因为 $s$ 是 $10^6$ 级别的，$q$ 是 $2\times10^5$ 级别的，所以不会超时。

**code**：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAX=100+5,MAX2=1e6+5;
int n,m,l,q;
int a[MAX],b[MAX],c[MAX];
int ans[MAX2],ai=0;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	cin>>m;
	for(int i=1;i<=m;++i)
		cin>>b[i];
	cin>>l;
	for(int i=1;i<=l;++i)
		cin>>c[i];
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			for(int k=1;k<=l;++k)
				ans[++ai]=a[i]+b[j]+c[k]; //统计所有可能组成的数字
	sort(ans+1,ans+ai+1); //排序
	cin>>q;
	int x,y;
	while(q--)
	{
		cin>>x;
		y=lower_bound(ans+1,ans+ai+1,x)-ans; //二分查找
		if(x==ans[y])
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}

```

---

## 作者：xiaoshumiao (赞：2)

我们可以 $\mathcal O(NML)$ 暴力把所有的和先预处理出来，存入一个桶中。

每次询问，如果 $X_i$ 所在的桶不为空，答案就是 `Yes`，否则就是 `No`。
```cpp
#include<cstdio>
using namespace std;
const int N=110,T=3e8+10; int a[N],b[N],c[N],t[T];
int main() {
  int n; scanf("%d",&n);
  for(int i=1;i<=n;i++) scanf("%d",&a[i]);
  int m; scanf("%d",&m);
  for(int i=1;i<=m;i++) scanf("%d",&b[i]);
  int l; scanf("%d",&l);
  for(int i=1;i<=l;i++) scanf("%d",&c[i]);
  for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++) for(int k=1;k<=l;k++) t[a[i]+b[j]+c[k]]++;//预处理
  int q,x; scanf("%d",&q);
  while(q--) scanf("%d",&x),puts(t[x]?"Yes":"No");
  return 0;
}
```

---

## 作者：coderJerry (赞：1)

### 题目描述
给出序列 $A,B,C,X$。问 $X$ 中的元素是否能等于 $A,B,C$ 中各选一元素之和。
### 题目分析
$A,B,C$ 序列的长度都不超过 $100$，故直接预处理出所有可能的和，用一个 ```map``` 存起来。最后一一查询 $X$ 中的元素是否在 ```map``` 即可。复杂度 $O(NML+NML\log NML+Q\log NML)$。
### AC 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[110],b[110],c[110],n,m,l,q,x;
map<int,int> mp;
signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);cout.tie(nullptr);
  cin>>n;
  for(int i=1;i<=n;i++) cin>>a[i];
  cin>>m;
  for(int i=1;i<=m;i++) cin>>b[i];
  cin>>l;
  for(int i=1;i<=l;i++) cin>>c[i];
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      for(int k=1;k<=l;k++){
        mp[a[i]+b[j]+c[k]]++;
      }
    }
  }
  cin>>q;
  for(int i=1;i<=q;i++){
    cin>>x;
    if(mp[x]>0) cout<<"Yes\n";
    else cout<<"No\n";
  }
  return 0;
}
```

---

## 作者：CodingOIer (赞：1)

## [ABC344C] A+B+C 题解

### 思路分析

我们注意到 $O(N^3)$ 的时间复杂度可以通过，但如果我们每次询问的时候都扫一遍则会超时。

我们可以预处理所有的和，将其保存在一颗红黑树中，即可 $O(N^3 + Q)$ 通过此题。

### 代码实现

```cpp
#include <cstdio>
#include <unordered_map>
constexpr int MaxN = 1e2 + 5;
constexpr int MaxQ = 2e5 + 5;
int n, m, l, q;
int a[MaxN];
int b[MaxN];
int c[MaxN];
std::unordered_map<int, bool> map;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &b[i]);
    }
    scanf("%d", &l);
    for (int i = 1; i <= l; i++)
    {
        scanf("%d", &c[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int k = 1; k <= l; k++)
            {
                map[a[i] + b[j] + c[k]] = true;
            }
        }
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
    {
        int x;
        scanf("%d", &x);
        printf("%s\n", map[x] ? "Yes" : "No");
    }
    return 0;
}
```

---

## 作者：Otue (赞：1)

先预处理出三个数组能拼出的数，存放到 `map` 中。

查询的时候只需要看这个数是否出现在 `map` 里即可。

时间复杂度 $O(n^3\log v+Q\log v)$，$n\leq100$，$\log v$ 是 `map` 的时间复杂度。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 3e5 + 5;

int n, m, l, q, a[N], b[N], c[N], d[N];
map<int, int> vis;

signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	cin >> m;
	for (int i = 1; i <= m; i++) cin >> b[i];
	cin >> l;
	for (int i = 1; i <= l; i++) cin >> c[i];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int k = 1; k <= l; k++) {
				vis[a[i] + b[j] + c[k]] = 1;
			}
		}
	}
	cin >> q;
	for (int i = 1; i <= q; i++) {
		cin >> d[i];
		if (vis[d[i]]) puts("Yes");
		else puts("No");
	}
}
```

---

## 作者：Albatross_LC (赞：1)

### 思路：

考虑使用 `map` 映射。

每次对 $a_i$、$b_j$、$c_k$ 的和记录下来并映射成 `true`，之后对每个 $x_i$ 的映射进行判断输出即可。

时间复杂度 $O(NML + Q)$。

### Code：

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int SIZE = 1 << 14;
char getc() {
    static char buf[SIZE], *begin = buf, *end = buf;
    if (begin == end) begin = buf, end = buf + fread(buf, 1, SIZE, stdin);
    return *begin ++ ;
}
int read() {
    int ret = 0, sgn = 0, ch = getc();
    while (!isdigit(ch)) sgn |= ch == '-', ch = getc();
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getc();
    return sgn ? -ret : ret;
}
int n, m, l, q;
int a[101], b[101], c[101], x;
map<int, int> p;
signed main() {
	n = read(); for (int i = 1; i <= n; i ++ ) a[i] = read();
	m = read(); for (int i = 1; i <= m; i ++ ) b[i] = read();
	l = read(); for (int i = 1; i <= l; i ++ ) c[i] = read();
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= m; j ++ )
			for (int k = 1; k <= l; k ++ )
				p[a[i] + b[j] + c[k]] ++ ;
	q = read(); for (int i = 1; i <= q; i ++ ) {
		x = read();
		if (p[x]) printf("Yes\n");
		else printf("No\n");
	}
}
```

---

## 作者：Jasoncwx (赞：1)

[题目传送门！](/problem/AT_abc344_c)
## 题目思路
观察数据范围，我们发现 $N,M,L\le 100$，我们便可以使用三重循环暴力枚举 $A,B,C$ 三个数组中的数，并把 $A_i+B_j+C_k$ 的值标记上。

然后我们遍历一次 $X$ 数组，若 $X_i$ 被标记过，输出 `Yes`，否则输出 `No`。
## 代码
[Atcoder](https://atcoder.jp/contests/abc344/submissions/51057071)

---

## 作者：2011FYCCCTA (赞：0)

[原题](https://www.luogu.com.cn/problem/AT_abc344_c)

---
### 思路

注意到 $1 \le N,M,L \le 100$，可以直接暴力枚举每种可能，用 `stl::map` 记录一下，最后询问的时候直接判断一下即可。

---
### 代码

（赛时代码码风有点扭曲）

```cpp
#include "bits/stdc++.h"
using namespace std;
int n ,m,l,q , a[105] , b[105] , c[105] , x;
map<int , bool> mp;
int main()
{
    cin >>n;
    for (int i = 1 ; i <= n ; i++)
    {
        cin >> a[i];
    }
    cin >>m;
    for (int i = 1 ; i <= m ; i++)
    {
        cin >> b[i];
    }
    cin >>l;
    for (int i = 1 ; i <= l ; i++)
    {
        cin >> c[i];
    }

    for (int i =1 ; i <=n ; i++)
        for(int j = 1;j<=m;j++)
            for(int k = 1;k<=l ; k++) mp[a[i] + b[j] + c[k]] = 1;
    cin >>q;
    while (q--)
    {
        cin >> x;
        if (mp[x]) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
```

---

## 作者：mgcjade (赞：0)

# [AT_ABC344_c](https://www.luogu.com.cn/problem/AT_abc344_c) 的题解

## 题目大意

给定三个数列 $A,B,C$，问是否存在一个 $x$ 使得 $A_i+B_j+C_k=x$。

## 思路

由于发现数据范围很小，所以暴力枚举即可。

发现询问量很大，所以使用预处理。

tips：在记录当前数是否出现过时，可以使用 `map`。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, l;
int a[105], b[105], c[105];
int T, q;
map<int, bool> mp;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    cin >> m;
    for (int j = 1; j <= m; j++)
        cin >> b[j];
    cin >> l;
    for (int k = 1; k <= l; k++)
        cin >> c[k];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int k = 1; k <= l; k++)
                mp[a[i] + b[j] + c[k]] = 1;
    cin >> T;
    while (T--)
    {
        cin >> q;
        if (mp[q] == 1)
            cout << "Yes\n";
        else
            cout << "No\n";
    }
    return 0;
}
```

---

## 作者：smart_kai (赞：0)

注意到询问次数很大，但三个数组元素个数很少，所以我们可以先统计一遍所有相加的可能性，然后用很低的时间复杂度回答询问即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,m,l,q,x,len1,len2,len3,a[110],b[110],c[110];
set<long long> st;

void solve()
{
    cin >> n;
    for (int i=1; i<=n; i++) cin >> a[i];
    cin >> m;
    for (int i=1; i<=m; i++) cin >> b[i];
    cin >> l;
    for (int i=1; i<=l; i++) cin >> c[i];

    for (int i=1; i<=n; i++) for (int j=1; j<=m; j++) for (int k=1; k<=l; k++) st.emplace(a[i]+b[j]+c[k]);
    cin >> q;
    while (q--)
    {
        cin >> x;
        if (st.count(x)) cout << "Yes\n";
        else cout << "No\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t=1;
    // cin >> t;
    while (t--) solve();
    return 0;
}
```

---

## 作者：wly09 (赞：0)

# 题意简述

给定三个数列 $A=(A_1,A_2,\cdots,A_N),B=(B_1,B_2,\cdots,B_M),C=(C_1,C_2,\cdots,C_L)$，$Q$ 次询问，每次询问给出数字 $X$，若 $\exists a\in A,b\in B,c\in C,a+b+c=X$，输出 `Yes`，否则输出 `No`。

# 思路

对于每次询问，暴力枚举 $a,b,c$ 显然是 $O(NMLQ)$ 的，时间上不可接受。$Q$ 的大小要求我们单次处理询问的时间复杂度低于线性。考虑到 $N,M,L$ 均较小，我们可以预处理出所有 $a+b+c$ 的值，进行排序，每次询问时二分查找即可。预处理复杂度为 $O(N^3+N^3\log N)$ （这里假定 $N,M,L$ 同级），每次询问复杂度为 $O(\log N)$。

# 代码

```cpp
#include <algorithm>
#include <iostream>
using namespace std;

int n, m, l, q;
int a[120], b[120], c[120], sum[17280000], sum_cnt = 0;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	cin >> m;
	for (int i = 0; i < m; ++i) cin >> b[i];
	cin >> l;
	for (int i = 0; i < l; ++i) cin >> c[i];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			for (int k = 0; k < l; ++k)
				sum[sum_cnt++] = a[i] + b[j] + c[k];
	sort(sum, sum + sum_cnt);
	sum_cnt = unique(sum, sum + sum_cnt) - sum;
	cin >> q;
	for (int i = 0; i < q; ++i) {
		int x;
		cin >> x;
		if (binary_search(sum, sum + sum_cnt, x)) cout << "Yes\n";
		else cout << "No\n";
	}
	return 0;
}
```

赛时我用的 `map`，同样能过。

---

## 作者：ToastBread (赞：0)

# ABC344 C 题解
## 大意
现有三个数字序列，分别为 $A=(A_1,…,A_N)$、$B=(B_1,…,B_M)$ 和 $C=(C_1,…,C_L)$。

现还有一个询问序列 $X=(X_1,\ldots,X_Q)$。对于询问序列中的每一项，若可以通过在上面的三个数字序列中各取一个数相加得到，输出 `Yes`，否则，输出 `No`。
## 思路
关注数据范围：

-   $1 \leq N,M,L \leq 100$
-   $0 \leq A_i, B_i ,C_i \leq 10^8$

很明显可以发现，数据范围还是很小的，自然想到**枚举**。这道题因为只需要输出能否凑到，想到开一个 `bool` 类型的答案数组 `ans` 解决。给定的 $N,M,L$ 很小，所以自然想到枚举 $A,B,C$ 中的每一项，组成一组，相加后存到答案数组中。对于给定的询问数组中的每一项，仅需判断 `ans[x[i]]` 是否为真即可。
 
可是时间复杂度呢？空间会爆吗？

时间复杂度：因为枚举了 $A,B,C$ 中的每一项配对，所以时间复杂度为 $O(NML)$，可以通过。

空间复杂度：定义了一个大小为 $3\times 10^8$ 大小的答案数组，约等于 $1 \times 10^7$ 大小的 `int` 数组，实测不会爆空间（感谢超大空间）。

具体的实现思路可以看我的代码。


## AC 代码

```cpp
#include<iostream> 
using namespace std;
bool ans[300000005];//不会爆的答案数组 
int a[105],b[105],c[105],n,m,l,x,q;//x不开数组，后面不会用前面的x 
int main()
{
	cin>>n;
	for(int i = 1; i <= n; i++)
	{
		cin>>a[i];
	}
	cin>>m;
	for(int i = 1; i <= m; i++)
	{
		cin>>b[i];
	}
	cin>>l;
	for(int i = 1; i <= l; i++)
	{
		cin>>c[i];
	}
	for(int i = 1; i <= n; i++)//O(NML)，枚举部分 **关键**
	{
		for(int j = 1; j <= m; j++)
		{
			for(int k = 1; k <= l; k++)
			{
				ans[a[i]+b[j]+c[k]]=1;//a[i]+b[j]+c[k]的情况下有解，存入。 
			}
		}
	}
	cin>>q;
	for(int i = 1; i <= q; i++)
	{
		cin>>x;
		if(ans[x])//有解吗？ 
		{
			cout<<"Yes"<<endl;//有 
		}
		else
		{
			cout<<"No"<<endl;//无 
		}
	}
	return 0;//华丽收尾 
}
```

结束了。

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc344_c)

## 思路

看到这题数据范围是 $1\le N,M,L\le 100$ 与 $1\le Q\le 2\times 10^5$，直接能想到用三重循环预处理能凑出的所有数，并用 map 保存。时间复杂度 $\mathcal{O}(NML+Q)$，足以通过此题。

- 可选优化：把 map 替换为常数更小的 unordered_map。

## AC 代码

```cpp
#include<bits/stdc++.h>
#define rep(k,l,r) for(int (k)=(l);k<=(r);++k)
using namespace std;
const int N=110;
int n,a[N],b[N],c[N],m,k,q;
unordered_map<int,bool>mp;
int main(){
	cin>>n;
	rep(i,1,n)cin>>a[i];
	cin>>m;
	rep(i,1,m)cin>>b[i];
	cin>>k;
	rep(i,1,k)cin>>c[i];
	cin>>q;
	rep(i,1,n)rep(j,1,m)rep(l,1,k)mp[a[i]+b[j]+c[l]]=1;
	while(q--){
		int op;
        cin>>op;
		if(mp[op])puts("Yes");
		else puts("No");
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/150149065)

---

## 作者：tder (赞：0)

暴力 $O(NMLQ)$ 肯定会死。

于是考虑预处理出 $m_p=1$ 表示 $p$ 有解，即可以表示为 $A_i+B_j+C_k$ 的形式，反之亦然。此处可以用 map 或 set 实现，枚举 $i,j,k$ 即可。

同时注意数据范围，查询的 $p$ 可能达到 $10^8$ 量级，于是无法使用普通数组，但 map 仅会占用已赋值元素的空间。

预处理复杂度 $O(NML)$，单次查询复杂度 $O(1)$，总复杂度 $O(NML+Q)$。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 5;
int n, m, l, q, a[N], b[N], c[N];
map<int, bool> t;
signed main() {
    cin>>n; for(int i = 1; i <= n; i++) cin>>a[i];
    cin>>m; for(int i = 1; i <= m; i++) cin>>b[i];
    cin>>l; for(int i = 1; i <= l; i++) cin>>c[i];
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) for(int k = 1; k <= l; k++) t[a[i] + b[j] + c[k]] = 1;
    cin>>q;
    while(q--) {
        int x; cin>>x;
        if(t[x]) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
}
```

---

## 作者：hexu2010 (赞：0)

# ABC344C A+B+C 题解

先考虑最朴素的做法，每次询问枚举选取 $A,B,C$ 中的哪些数，复杂度 $O(Q\cdot n^3)$ 超时。

接下来考虑如何优化。最终要求的是是否存在 $i,j,k$ 使得 $A_i+B_j+C_k=x$，所以如果已经枚举出了 $i,j$ 的值，那么 $C_k$ 也可以确定下来。所以可以考虑开一个桶记录某个数是否在 $C$ 中出现过，每次 $O(1)$ 查询 $x-A_i-B_j$ 是否在 $C$ 中出现，若出现则说明存在，复杂度降为 $O(Q\cdot n^2)$，照样超时。

看一眼数据范围，发现 $Q$ 远大于 $N$，每次询问的复杂度要求在 $O(n)$ 以内，代表着我们每次只能枚举一个数组中的数。受此启发，可以预处理 $cnt_i$ 记录是否存在 $j,k$ 使得 $A_j+B_k=i$，询问时 $O(n)$ 枚举选取 $C$ 中的哪个数，查询 $cnt_{x-C_i}$ 即可。预处理的复杂度是 $O(n^2)$ 的，整体复杂度是 $O(Q\cdot n+n^2)=O(Qn)$，已经可以通过此题。

当然，我们可以顺着刚才的思路往下走，$O(n^3)$ 预处理 $cnt_i'$ 表示是否存在 $p,q,l$ 使得 $A_p+B_q+C_l=i$，每次询问时查询 $cnt_x$ 即可，复杂度 $O(Q+n^3)=O(n^3)$，也可以通过。

综上所述，本题有复杂度分别为 $O(Qn)$ 与 $O(n^3)$ 的两种做法，均可以选择。本人采用了 $O(Qn)$ 的做法，代码如下：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int s = 0, w = 1;
	char ch = getchar();
	for(; ch < '0' || ch > '9'; w *= ch == '-' ? -1 : 1, ch = getchar());
	for(; ch >= '0' && ch <= '9'; s = 10 * s + ch - '0', ch = getchar());
	return s * w;
}
const int MAXN = 105;
int N, M, L, a[MAXN], b[MAXN], c[MAXN];
map<int, bool> mp;
signed main(){
    N = read();
    for(int i = 1; i <= N; i++) a[i] = read();
    M = read();
    for(int i = 1; i <= M; i++) b[i] = read();
    L = read();
    for(int i = 1; i <= L; i++) c[i] = read();
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            mp[a[i] + b[j]] = true;
        }
    }
    sort(c + 1, c + L + 1);
    int Q = read();
    for(int i = 1, x; i <= Q; i++){
        x = read();
        bool flag = false;
        for(int j = 1; j <= L; j++){
            if(mp.find(x - c[j]) != mp.end()){
                flag = true;
                break;
            }
        }
        if(flag == true){
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
```

---

