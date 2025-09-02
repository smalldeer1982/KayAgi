# Relatively Prime Graph

## 题目描述

我们将一个无向图称作互质图，当且仅当对于其中每一条边$(v, u)$有$v$和$u$互质（也即$GCD(v,u)=1$）。当两个顶点之间没有边时不需要考虑。顶点从1开始标号。

现在给你$n$个顶点和$m$条边，要求你建立一个无重边和自环并且连通的互质图，如果无法构造输出"Impossible"，对于多种可能的答案输出任意一种即可。

## 样例 #1

### 输入

```
5 6
```

### 输出

```
Possible
2 5
3 2
5 1
3 4
4 1
5 4
```

## 样例 #2

### 输入

```
6 12
```

### 输出

```
Impossible
```

# 题解

## 作者：_6_awa (赞：6)

题目大意：构建一个连通图，$n$ 点 $m$ 边，使得边连接的两个点的编号均互质。

首先，我们可以看出：$m \le 10^5$

而我们又知道：$n^2 \ge m \ge n + 1$

所以这说明什么呢？当 $n$ 在 $5000$ 左右时，可以直接暴力过；而当 $n \ge 10^4$ 的时候，因为一与任何数互质，直接凑出 $n - 1$ 条边并保证联通，以 $2$ 为点的也有少 $\frac{n}{2}$ 条，以 $3$ 为点的有 $\frac{2n}{3}$ 条（因为只有是 $3$ 的倍数的编号才与 $3$ 不互质）......所以你会发现很快就能凑齐 $10^5$ 条线了。所以这样暴力，如果及时退出，复杂度并不是 $n^2$ 级别。于是我们就能顺利的爆切此题了。

## AC Code:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[250001],b[250001],sum;
signed main()
{
    cin >> n >> m;
    if(m > n * n || m < n - 1)//这里可以粗略的排除
    {
        cout << "Impossible";
        return 0;
    }
    for(int i = 1;i <= n;i ++)
        for(int j = i + 1;j <= n;j ++)
        {
            if(__gcd(i,j) == 1)a[++sum] = i,b[sum] = j;//注意，这里gcd最多是log级别的，所以不会超时
            if(sum >= m)break ;//及时跳出
        }
    if(sum < m)//若没有m条边，排除
    {
        cout << "Impossible";
        return 0;
    }
    cout << "Possible\n";
    for(int i = 1;i <= m;i ++)cout << a[i] << " " << b[i] << endl;
}

---

## 作者：fish_love_cat (赞：2)

绷，诈骗，暴力枚举两端即可。

连通性可以先试着构造一个菊花，$1$ 做中心。显然 $1$ 可以乱连。

连菊花都不行那肯定假了。

爆枚出来后看看达不达标，注意到当枚举合法的边数超过 $m$ 可以提前退出，这是个显然的优化。

---

有大佬说时间复杂度 $O(\min(n^2,m))$？

反正 $n^2$ 是跑不满的，随便过。

同时讲个笑话：

输入：

```
700 100000
```

有解。

所以 $n$ 要跑到的实际范围只有 $700$。

---

```cpp
#include<bits/stdc++.h>
using namespace std;
int u[100005],v[100005],top;
int main(){
    int n,m;
    cin>>n>>m;
    if(m<n-1){
        puts("Impossible");
        return 0;
    }
    for(int i=1;i<=n&&top<=m;i++)
    for(int j=i+1;j<=n&&top<=m;j++)
    if(__gcd(i,j)==1)u[++top]=i,v[top]=j;
    if(top<m){
        puts("Impossible");
        return 0;
    }
    puts("Possible");
    for(int i=1;i<=m;i++)cout<<u[i]<<' '<<v[i]<<endl;
    return 0;
}
```

---

评到绿可能是因为太多人赛时被诈骗了？

---

## 作者：YuntianZhao (赞：2)

# CF1009D

这道题非常暴力。

已知有 $n$ 个点， $m$ 条边。

由于1和所有数互质，所以1可以连接所有点，因此只要 $m \geq n - 1$ 此时图一定连通。

之后暴力枚举可以连接的边，用 tot 记录一下连接的边的数量，如果 $tot \geq m$ 直接返回输出边，不然输出 impossible。

复杂度 $O(n^2)$。
```c++
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;

vector<int> gcd_list[maxn];
int n, m, tot;

void init() {
  for (int i = 1; i <= n; i++) {
    int k = 0;
    for (int j = i + 1; j <= n; j++) {
      if (__gcd(i, j) == 1) {
        gcd_list[i].push_back(j);
        tot++;
        if (tot > m) return;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin >> n >> m;
  if (m < n - 1) {
    cout << "Impossible" << endl;
    return 0;
  }
  init();
  if (tot < m) {
    cout << "Impossible" << endl;
    return 0;
  } else {
    cout << "Possible" << endl;
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j < gcd_list[i].size() && m > 0;j++, m--) {
        cout << i << " " << gcd_list[i][j] << endl;
      }
    }
  }
  return 0;
}
```

---

## 作者：InversionShadow (赞：0)

诈骗题，*1700。

先考虑什么情况构不成图：$m<n-1$，即边数小于点数减一。

接下来我们暴力去找 $(i,j)$ 满足 $\gcd(i,j)=1$，时间复杂度 $\mathcal{O(n^2)}$，$n\le 10^5$，肯定超时。

怎么“优化”呢？

发现只要你现在的边数已经大于 $m$ 了，那就可以构成一个图，没必要再找了，所以直接跳出循环。

这样我们就知道了暴力是可以过的，时间复杂度 $\mathcal{O(\min(n^2,m))}$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 100;

int n, m, cnt, tot;
bool flag = 1;

pair<int, int> a[N];

void solve() {
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (__gcd(i, j) == 1) {
        cnt++;
        if (cnt == m + 1) {
          return ;
        }
        a[++tot] = {i, j};
       }
     }
   }
}

int main() {
  cin >> n >> m;
  if (m < n - 1) {
    cout << "Impossible\n";
    return 0;
  }
  solve();
  if (cnt < m) {
//  cout << cnt << endl;
    cout << "Impossible";
    return 0;
  } else {
    cout << "Possible\n";
  }
  for (int i = 1; i <= tot; i++) {
    cout << a[i].first << ' ' << a[i].second << endl;
  }
  return 0;
}
```

---

## 作者：lskksl (赞：0)

这道题的大意十分明确，很明显是想让我们建一个连通图使得互相连接的两个点互质。

很显然，要让一个图联通，我们首先要有 $n-1$ 条边。显然如果 $m<n-1$ 便是无解的一种特例。

当然，如果 $m$ 满足，那么我们便需要一个通解来满足联通的题意。显然我们可以发现，只可以使 $1$ 与其他所有点连接，并且满足互质。

其余的，枚举剩余除 $1$ 外的所有点，保证保证互质即可。循环即可解决，当边数达到 $m$ 时跳出循环。

最后，如果将所有可能的边全部连上也无法满足，也输出无解。总的来看，时间复杂度 $O(m)$。

---

## 作者：codeLJH114514 (赞：0)

# Analysis

首先，如果 $m < n - 1$ 必定无解，输出 `Impossible`。

其次，枚举 $i \in \{1, \ldots, n\}$ 和 $j \in \{1, \ldots, n\}$，如果 $\gcd(i, j) = 1$，直接把这条边加入答案的图，判断如果已经够了直接跳出去。

如果把所有可以加入的边全部加了也没有 $m$ 条，输出 `Impossible`。

否则输出 `Possible`，然后把加入答案的边输出。

但是这样是 $\mathcal{O}(n^2)$ 的，会 T 吗？

答案是否定的，因为 $\mathcal{O}(n^2)$ 的最坏情况只在无解时才会有，但是如果 $n$ 开满的话显然不可能因为边数不够无解，所以不会 TLE。

# Coding

```cpp
#include <iostream>
#include <vector>
#include <algorithm> 
int n, m;
std::pair<std::string, std::vector<std::pair<int, int>>> SolveIt() {
	if (m < n - 1)
		return std::make_pair("Impossible", std::vector<std::pair<int, int>>());
	int number = 0;
	std::vector<std::pair<int, int>> G;
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			if (std::__gcd(i, j) == 1) {
				number += 1;
				G.emplace_back(i, j);
				if (number == m)
					return std::make_pair("Possible", G);
			}
	return std::make_pair("Impossible", std::vector<std::pair<int, int>>());
}
int main() {
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::ios::sync_with_stdio(false);
	std::cin >> n >> m;
	auto ret = SolveIt();
	std::cout << ret.first << "\n";
	for (auto i : ret.second)
		std::cout << i.first << " " << i.second << "\n";
	return 0;
} 
```

---

