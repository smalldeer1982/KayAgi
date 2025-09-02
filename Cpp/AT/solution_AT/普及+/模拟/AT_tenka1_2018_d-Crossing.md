# Crossing

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2018/tasks/tenka1_2018_d

整数 $ N $ が与えられます。$ \{1,2,...N\} $ の部分集合の組 $ (S_1,S_2,...,S_k) $ であって、以下の条件を満たすものが存在するか判定し、 存在する場合はひとつ構成してください。

- $ 1,2,...,N $ のうちどの整数も、$ S_1,S_2,...,S_k $ のうちちょうど $ 2 $ つに含まれる
- $ S_1,S_2,...,S_k $ のうちどの $ 2 $ つの集合をとっても、それらに共通して含まれる要素はちょうど $ 1 $ つである

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ N $ は整数である

### Sample Explanation 1

$ (S_1,S_2,S_3)=(\{1,2\},\{3,1\},\{2,3\}) $ とすれば、条件を満たすことが確認できます。

## 样例 #1

### 输入

```
3```

### 输出

```
Yes
3
2 1 2
2 3 1
2 2 3```

## 样例 #2

### 输入

```
4```

### 输出

```
No```

# 题解

## 作者：Nightsky_Stars (赞：3)

# 题目大意：

给定一个整数 $n$ ,构造 $k$ 个集合，使每两个集合的交集仅有一个数，且所有 $1$ 到 $n$ 之间的数字在这些集合中仅出现过两次。

# 思路：

设有 $k$ 个集合，考虑每两个不同的集合中有一个相同的数，所以这个数就出现两次了。

所以，有且仅有 $n = \frac{k(k-1)}{2}$ 时，才有解。

因此我们就可以用二次方程的求根公式计算 $k$。然后构造，在范围内枚举选取的两个集合，往这两个集合里放一个独一无二的数即可。

# CODE:

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,a=1,b=-1,c,x,d=1;
	cin>>n;
	c=-2*n;
	x=(-b+sqrt(b*b-4*a*c))/(2*a);
	if(x*x-x!=n*2){
		cout<<"No\n";
		return 0;
	}
	set<int>s[x+1];
	cout<<"Yes\n"<<x<<"\n";
	for(int i=1;i<=x;i++){
		for(int j=i+1;j<=x;j++){
			s[i].insert(d);
			s[j].insert(d);
			d++;
		}
	}
	for(int i=1;i<=x;i++){
		cout<<x-1<<" ";
		for(auto k:s[i]){
			cout<<k<<" ";	
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：cosf (赞：1)

考虑建模。

把这 $k$ 个集合看作 $k$ 个点，第 $i$ 个数同时存在于两个集合相当于在两个集合之间连边。两个集合只有一个公共元素相当于点之间两两有且仅有一条边，这样的图是完全图。一个完全图的边数是 $\binom{k}{2}$，即 $\frac{k(k-1)}{2}$，故判断即可。

如果可行，我们给完全图的每条边标个标号，则一个点对应的集合就是与之相邻的边的标号构成的集合。

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int k = 2;
    while (k * (k - 1) / 2 < n)
    {
        k++;
    }
    if (k * (k - 1) / 2 > n)
    {
        cout << "No" << endl;
        return 0;
    }
    vector<vector<int>> res(k, vector<int>());
    int idx = 0;
    for (int i = 0; i < k; i++)
    {
        for (int j = i + 1; j < k; j++)
        {
            res[i].push_back(++idx);
            res[j].push_back(idx);
        }
    }
    cout << "Yes\n";
    cout << k << '\n';
    for (int i = 0; i < k; i++)
    {
        cout << res[i].size();
        for (int j : res[i])
        {
            cout << ' ' << j;
        }
        cout << '\n';
    }
    cout.flush();
    return 0;
}

```

---

## 作者：dvsfanjo (赞：0)

# 题解：AT_tenka1_2018_d Crossing

## 思路

设有 $k$ 个集合，只有 $n = \frac{k(k-1)}{2}$ 是才可以进行构造。

计算 $k$ 后枚举两个集合放入一个没有放过的数即可！

推一下算 $k$ 的柿子。

$n=\frac{k(k-1)}{2}$

$2n=k(k-1)$

$k^2-k=2n$

$k^2-k-2n=0$

因为 $k$ 不能是负数，所以：

$k=\frac{1+\sqrt{1+8n}}{2}$

## 注意

1. 打完 No 不要换行！

1. 打 No 和 Yes 时不要打成 NO 和 YES 啊！

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e3 + 5;
ll n, k, num = 1;
set<ll> s[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	k = (1 + sqrt(1 + 8 * n)) / 2;
	if (k * k - k - 2 * n != 0)
	{
		cout << "No";
		return 0;
	}
	cout << "Yes\n" << k << '\n';
	for (int i = 1; i <= k; i++)
		for (int j = i + 1; j <= k; j++)
		{
			s[i].insert(num);
			s[j].insert(num);
			num++;
		}
	for (int i = 1; i <= k; i++)
	{
		cout << k - 1 << ' ';
		for (auto j : s[i])
			cout <<j << ' ';
		cout << '\n';
	}
	return 0;
}
/*
n = k(k-1)/2
n = (k^2 - k)/2
k^2 - k - 2n = 0
*/
```

---

## 作者：封禁用户 (赞：0)

## 前言：
竟然有如此水的绿题。

## 思路：

假设有 $k$ 个集合，考虑一下每两个不同的集合中有一个相同的数，所以这个数就出现两次了。

所以，有且仅有 $n$ $=$ $\displaystyle \frac{k(k-1)}{2}$ 时，才会有解。

因此我们就可以用二次方程的求根公式计算 $k$。然后构造，在范围内枚举选取的两个集合，往这两个集合里放一个独一无二的数即可。

## AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,twt=1,ans=-1,tum=0,num=0,sum=1;

int main()
{
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
	tum=-2*n;
	num=(-ans+sqrt(ans*ans-4*twt*tum))/(2*twt);
	if(num*num-num!=n*2)
	{
		cout << "No" << endl;
		return 0;
	}
	set<int>t[num+1];
	cout << "Yes" << endl << num << endl;
	for(long long i=1;i<=num;i++)
	{
		for(long long j=i+1;j<=num;j++)
		{
			t[i].insert(sum);
			t[j].insert(sum);
			sum++;
		}
	}
	for(long long i=1;i<=num;i++)
	{
		cout << num-1 << " ";
		for(auto k:t[i])
		{
			cout << k << " ";	
		}
		cout << endl;
	}
	return 0;
}
``````

---

## 作者：Fubaogege (赞：0)

他给定了 $n$，试构造 $k$ 个集合，使得每两个集合的交集仅有一个数，并且所有 $1 \sim n$ 之间的数字在这些集合中出现两次。

所以，简化一下思路：

- 如果每两个集合 $i,j$ 中存在一个相同的数。
- 那么只有 $n$ 等于 $k^2-k$ 在除以 $2$ 的时候有解。

那么就简单了。

利用二次方程求解 $k$，就 AC 了此题。

代码：
```c
	for(int i=1;i<=x;i++){
		for(int j=i+1;j<=x;j++){
			s[i].insert(d);
			s[j].insert(d);
			d++;
		}
	}
	for(int i=1;i<=x;i++){
		cout<<x-1<<" ";
		for(auto y:s[i]){
			cout<<y<<" ";	
		}
		cout<<"\n";
	}
```
完结撒花。

---

## 作者：tZEROちゃん (赞：0)

不妨设有 $k$ 个集合。

我们可以注意到，对于任意 $i,j(1\le i<j \le k)$，显然集合 $i$ 和集合 $j$ 必定存在恰好一个相同的元素，这是题目告诉我们的，那么显然，对于这个元素，它就仅存在于 $i,j$ 这两个集合中，因为每个元素只能出现两次。因此，当且仅当 $n = \dfrac{k(k-1)}2$ 时，有解。

我们据此可以判断出 $k$ 的值，可以用二次方程的求根公式计算。

构造是显然的，在范围内枚举选取的两个集合，往这两个集合里扔一个新的数即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  int a = 1, b = -1, c = -2 * n;
  int x = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
  if (x * x - x != n * 2) {
    cout << "No\n";
  }
  set<int> S[x + 1];
  int d = 1;
  cout << "Yes\n" << x << '\n';
  for (int i = 1; i <= x; ++i) {
    for (int j = i + 1; j <= x; ++j) {
      S[i].insert(d);
      S[j].insert(d);
      ++d;
    }
  }
  for (int i = 1; i <= x; ++i) {
    cout << x - 1 << ' ';
    for (auto e : S[i]) cout << e << ' ';
    cout << '\n';
  }
}
// n = k(k-1) / 2
// n = (k^2 - k) / 2
// 2n = (k^2 - k)
// k^2 - k - 2n = 0
```

---

## 作者：irris (赞：0)

## Preface

低智商噗叽组 T4（T4 < T3），为啥你谷题解写了个逻辑上错的还做的这么麻烦。

## Solution

考虑每两个不同集合有一个相同的数，然后这个数已经出现两次了。

所以总共 $\dfrac{k(k-1)}2$ 个不同的集合对，每一个集合对对应一种数。

所以有解当且仅当 $n$ 可以表示为 $\dfrac{k(k-1)}2$ 的形式。

构造平凡，直接枚举每个不同的集合对，往里面放一个独一无二的数即可。这是 oi 题又不是 mo 题。

因为我很懒，所以写的是无解 $\mathcal O(\sqrt{n})$ 有解 $\mathcal O(n)$。

## Code

```cpp
#include <bits/stdc++.h>

namespace FastIO {
	template <typename T> inline T read() { T x = 0, w = 0; char ch = getchar(); while (ch < '0' || ch > '9') w |= ch == '-', ch = getchar(); while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar(); return w ? ((~x) + 1) : x; }
	template <typename T> inline void write(T x) { x && (write<T>(x / 10), putchar(x % 10 ^ '0')); }
	template <typename T> inline void print(T x) { x || putchar('0'); x < 0 && (putchar('-'), x = (~x) + 1); write<T>(x); }
	template <typename T> inline void print(T x, char end) { x || putchar('0'); x < 0 && (putchar('-'), x = (~x) + 1); write<T>(x), putchar(end); }
};
using namespace FastIO;

#define MAXK 401
std::vector<int> p[MAXK];
int main() {
	int N = read<int>(), K = 1;
	while (K * (K - 1) / 2 < N) ++K;
	if (K * (K - 1) / 2 > N) return puts("No"), 0;
	puts("Yes");
	print<int>(K, '\n');
	for (int i = 1, cnt = 1; i < K; ++i) for (int j = i + 1; j <= K; ++j) 
		p[i].push_back(cnt), p[j].push_back(cnt++);
	for (int i = 1; i <= K; ++i) {
		print<int>(p[i].size(), ' ');
		for (int u : p[i]) print<int>(u, ' ');
		puts("");
	}
	return 0;
}
```

---

## 作者：ztlh (赞：0)

# Solution

首先，每个数出现两次，意味着含有这个数的两个集合的交集就是它；反过来说，一个集合中的**每个数**都会作为这个集合和其他集合的交集**恰好一次**。

也就意味着每个集合的元素个数是**一样**的，并且**集合总数**刚好比**单个集合的元素个数**大 $1$。

由此可以判断：

- 当 $n$ 可以表示成 $m \times (m + 1)$ 的形式时，输出 $\text{Yes}$。

- 否则输出 $\text{No}$。

那如何构造合法解呢？

由于每个数的地位平等，我们可以令第一个集合为 $\{ 1, 2, ..., m \}$，在此基础上进行构造。

举个栗子：$n = 10$，$m = 4$。

第一个集合：

- $1, 2, 3, 4$

第二个集合要和第一个集合有刚好一个公共元素，为方便就取个 $1$ 吧。剩下 $3$ 个位置给还没用过的元素：

- $1, 5, 6, 7$

第三个集合和前两个集合都要有公共元素。显然 $1$ 已经不能再用了，因此前两个位置取 $2$ 和 $5$：

- $2, 5, 8, 9$

此时我们可以发现：第 $i$ 个集合与前 $i - 1$ 个集合的公共元素就是前面的集合组成的矩阵中第 $i - 1$ 列的 $i - 1$ 个元素。

于是第四个同理：

- $3, 6, 8, 10$

第五个无脑：

- $4, 7, 9, 10$

构造完毕：

- $1, 2, 3, 4$

- $1, 5, 6, 7$

- $2, 5, 8, 9$

- $3, 6, 8, 10$

- $4, 7, 9, 10$

当然，我们需要一个指针记录当前已经用过的数。

# Code

```cpp
#include<bits/stdc++.h>
#define N 455
using namespace std;
int n;
int m;
int ans[N][N];
int tot;// 指针
int main(){
    scanf("%d",&n);
    m=sqrt(n*2);
    if(m*(m+1)!=n*2){
    	printf("No");
    	return 0;
	}
	printf("Yes\n%d\n",m+1);
	for(int i=1;i<=m;i++) ans[1][i]=i;
	tot=m;
	for(int i=2;i<=m+1;i++){
		for(int j=1;j<i;j++) ans[i][j]=ans[j][i-1];
		for(int j=i;j<=m;j++) ans[i][j]=++tot;
	}
	for(int i=1;i<=m+1;i++){
		printf("%d ",m);
		for(int j=1;j<=m;j++)
			printf("%d ",ans[i][j]);
		printf("\n");
	}
    return 0;
}
//20=4*5
//1 2 3 4
//1 5 6 7
//2 5 8 9
//3 6 8 10
//4 7 9 10
```

---

