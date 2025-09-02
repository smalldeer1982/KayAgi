# [ABC258G] Triangle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc258/tasks/abc258_g

$ N $ 頂点単純無向グラフ $ G $ が与えられます。

$ G $ は $ N $ 行 $ N $ 列の隣接行列 $ A $ によって与えられます。つまり、$ A_{i,j} $ が $ 1 $ である場合は頂点 $ i,j $ 間に辺があることを、$ 0 $ である場合には辺がないことを意味します。

$ 1\ \le\ i\ <\ j\ <\ k\ \le\ N $ を満たす整数の組 $ (i,j,k) $ のうち、頂点 $ i,j $ 間にも頂点 $ j,k $ 間にも頂点 $ i,k $ 間にも辺があるようなものの個数を求めてください。

## 说明/提示

### 制約

- $ 3\ \le\ N\ \le\ 3000 $
- $ A $ は単純無向グラフ $ G $ の隣接行列である。
- 入力はすべて整数。

### Sample Explanation 1

$ (i,j,k)=(1,3,4),(2,3,4) $ が条件を満たします。 $ (i,j,k)=(1,2,3) $ は、頂点 $ 1,2 $ 間に辺がないため条件を満たしません。 よって、解は $ 2 $ です。

## 样例 #1

### 输入

```
4
0011
0011
1101
1110```

### 输出

```
2```

## 样例 #2

### 输入

```
10
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000```

### 输出

```
0```

# 题解

## 作者：DengDuck (赞：3)

本题堪称是 `bitset` 的板子题。

大家想一想，如果 $i$ 与 $j$ 有边相连，那根据定义，显然 $k$ 就应该是 $i$ 和 $j$ 共同连接的点，以下简称共同点。

再转回邻接矩阵，我们发现，共同点不就是第 $i$ 行与第 $j$ 行进行与运算之后为 $1$ 的位置吗？这个也显然，根据邻接矩阵的定义可得。

也就是说，对于固定的 $i$ 和 $j$,可行的 $k$ 的数量就是第 $i$ 行与第 $j$ 行进行与运算之后 $1$ 的数量。

我们暴力实现是 $O(n^3)$ 的，可以利用一个叫做 `bitset` 的黑科技优化，直接把 `bitset` 当成 `bool` 数组用,统计使用一个叫做 `count()` 的 `bitset` 内置函数，时间复杂度变成了 $O(\frac{n^3}{w})$

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, ans;
char c[3005];
bitset<3005> a[3005];
int main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", c + 1);
        for (int j = 1 + i; j <= n; j++) {
            if (c[j] == '1')
                a[i][j] = 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (a[i][j])
                ans += (a[j] & a[i]).count();
        }
    }
    printf("%lld", ans);
}
```

---

## 作者：12345678hzx (赞：3)

## 题目描述
给你一个 $N \times N$ 的邻接矩阵，让你找出其中 $i<j<k$ 的三角形的个数。
## 思路
暴力的思路很好想，枚举 $i,j,k$ 的位置，$O(n^3)$ 的时间复杂度，无法通过本题。

我们用另外一个思路，枚举 $i,j$ 的位置，一个位置，如果 $i,j$ 都能到达，则就是一个三角形，所以我们可以预处理出 $i,j$ 都能到达的点有哪些，再 $O(n^2)$ 枚举。

大家可以发现，枚举 $i,j$ 都能到达的点其实就是求 $i\&j$ 中 $1$ 的个数，所以我们把矩阵用 ```bitset``` 存起来，求 $1$ 的个数其实就是求 ```(a[i]&a[j]).count()```。
## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<set>
#include<queue>
#include<stack>
#include<vector>
#include<ctime>
#include<map>
#include<set>
#include<bitset>
#include<list>

using namespace std;

int n;
long long ans;
string c; 
bitset<3005>a[3005];
int main() {
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>c;
		for(int j=i;j<n;j++) a[i][j+1]=c[j]-'0';
	}
	for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) if(a[i][j]) ans+=(a[i]&a[j]).count();
	cout<<ans; 
	return 0;
}
```


---

## 作者：ZnHF (赞：2)

[题目链接](https://www.luogu.com.cn/problem/AT_abc258_g)
### 题意简述
给定一张无向图，若图中三个点 $a$，$b$，$c$ 满足 $a$ 与 $b$ 有边相连，$a$ 与 $c$ 有边相连，$b$ 与 $c$ 有边相连，则称点 $a$，$b$，$c$ 构成了一个三角形，求在给定的图中三角形的个数。
### 题目分析
一个比较直接的想法是枚举 $a$，$b$，$c$ 的编号，时间复杂度为 $O(n^3)$，无法通过本题。

我们可以只枚举 $a$，$b$ 的编号，若一个点与 $a$ 有边相连且与 $b$ 有边相连，则这个点必定是满足条件的点 $c$。使用 `bitset` 可以比较方便地解决这个问题。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans;
bitset<3005> m[3005];
char t;
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin>>t;
			if(t=='1') m[i][j]=1;
			else m[i][j]=0;
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(m[i][j]){
				ans+=(long long)((m[i]&m[j]).count());//满足条件的c点个数
			}
		}
	}
	cout<<ans/6<<endl;//统计出的结果有一定的重复，需要除以6后再输出
	return 0;
}
```


---

## 作者：Gaode_Sean (赞：1)

个人感觉这是一道比较套路的题目。

为了使代码更为简洁，便先不考虑 $i,j,k$ 的大小关系。这样在统计结束之后将答案除以 $6$ 即可。

考虑枚举两个点 $i$ 和 $j$，当 $a_{i,j}=1$ 时，我们统计一下有多少个 $k$ 满足 $a_{i,k}=1$ 且 $a_{j,k}=1$。

以上的暴力算法复杂度为 $O(n^3)$，瓶颈在于统计 $k$ 的数量。容易想到使用 ``bitset`` 优化，即对于每一个点的出边用 ``bitset`` 维护，$k$ 的数量即为 ``(s[i]&s[j]).count()``。

时间复杂度为 $O(\frac{n^3}{w})$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3005;
typedef long long ll;
char ch[N];
int n;
ll ans;
bitset<N> s[N];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",ch+1);
		for(int j=1;j<=n;j++) if(ch[j]=='1') s[i][j]=1;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++) if(s[i][j]) ans+=(ll)((s[i]&s[j]).count());
	}
	printf("%lld",ans/6ll);
	return 0;
}

---

## 作者：August_Light (赞：0)

# [ABC258G] Triangle 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc258_g)

## 题意简述

以邻接矩阵的形式给定一个 $n$ 个点的无向图，求三点环的数量。

$n \le 3 \times 10^3$。

## 前置知识

- `bitset`

## 解法

写出暴力：

注意尽量在枚举 $k$ 的时候从 $1$ 到 $n$ 完整的枚举一遍（而并非从 $j+1$ 开始），这样可以为后文用 `bitset` 优化做铺垫。

最后 $\dfrac {ans} 3$ 是因为每个三点环被计入了三回啊三回。

```cpp
    for (int i = 1; i <= n; i++)
        for (int j = i+1; j <= n; j++)
            if (b[i][j])
                for (int k = 1; k <= n; k++)
                    if (b[i][k] && b[j][k])
                        ans++;
    write(ans / 3);
```

`bitset` 优化：

```cpp
    for (int i = 1; i <= n; i++)
        for (int j = i+1; j <= n; j++)
            if (b[i][j])
                ans += (b[i] & b[j]).count();
    write(ans / 3);
```

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

// 省略快读快写的实现

const int MAXN = 3e3 + 100;
bitset<MAXN> b[MAXN];

int main() {
    int n = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            int tmp; scanf("%1d", &tmp);
            b[i][j] = tmp;
        }

    LL ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i+1; j <= n; j++)
            if (b[i][j])
                ans += (b[i] & b[j]).count();
    write(ans / 3);
    return 0;
}
```


---

## 作者：qifan_maker (赞：0)

### 题目链接
[洛谷](https://www.luogu.com.cn/problem/AT_abc258_g)

[AtCoder](https://atcoder.jp/contests/abc258/tasks/abc258_g)
### 题目解法

我们需要用到 `bitset` 容器，不了解的朋友可以去 [OI-wiki](https://oi-wiki.org/lang/csl/bitset/) 看看。

`bitset` 与 `vector<bool>` 的储存方式是相同的，但 `bitset` 中有一些好用库函数，此题就需要用到 `count()` 函数，他的作用是统计 `true` 的数量。

---

暴力枚举 $i,j,k$ 的位置，时间复杂度为 $\mathcal{O}(n^3)$，无法通过此题。

可以发现，$k$ 是 $i$ 和 $j$ 是共同连接的点，所以我们只需要将第 $i$ 行与第 $j$ 行进行与运算，结果中 $1$ 的个数就是 $k$ 的数量，也就是 `(a[i]&a[j]).count()`。

时间复杂度 $\mathcal{O}(\frac{n^3}{w})$，可以分解为 $\mathcal{O}(\frac{n}{w}n^2 )$，其中 $\frac{n}{w}$ 为 `bitset` 的时间复杂度。
### [AC](https://www.luogu.com.cn/record/109676641) Code
```cpp
/*
题目编号：
[ABC258G] Triangle
By：
qifan_maker
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
bitset<3100> a[3100];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	string s;
	for (int i=1;i<=n;i++){
		cin >> s;
		s = ' '+s;
		for (int j=i+1;j<=n;j++){
			a[i][j] = s[j]-'0';
		}
	}
	ll ans=0;
	for (int i=1;i<=n;i++){
		for (int j=i+1;j<=n;j++){
			if (a[i][j]){
				ans += (a[i]&a[j]).count();
			}
		}
	}
	cout << ans;
	return 0;
}

```

---

## 作者：tZEROちゃん (赞：0)



显然我们可以想到枚举 $i,j,k$ 然后判断是否可行，但是时间复杂度是 $O(n^3)$ 的，不可以被接受，考虑优化。

当我们枚举 $i, j$ 后，若一个 $k$ 满足要求，那么显然一定有 $(i, k)$ 和 $(j, k)$ 这两条边。

回到题目，可以发现在存在 $(i, j)$ 的情况下，我们只需要判断若 $A_{i, k} = A_{j, k} = 1$，那么这个 $k$ 就是可以的。 

不难发现只需要将第 $i$ 行与第 $j$ 行进行按位与运算，然后统计有多少个 $1$ 就可以了。

这个过程可以使用 `bitset` 进行，最后调用 `(A[i] & A[j]).count()` 即可。

具体细节见代码。

代码：*[37553455](https://atcoder.jp/contests/abc258/submissions/37553455)*。

---

