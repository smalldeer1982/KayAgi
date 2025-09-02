# Easy Assembly

## 题目描述

Emma 喜欢玩积木，她有若干相同大小的、标有不同数字的积木，将它们竖直堆放。

现在，她可以进行以下操作：

- 分裂：从将一堆积木（数量大于 $1$）的顶端拿出若干块，按原来的顺序放在地上形成一堆新的积木。操作后积木堆数加一；

- 合并：将一堆积木全部按原来的顺序全部堆到另一堆积木的顶端。操作后积木堆数减一。

她想让所有木块形成一堆且积木上的数字由顶端到底端升序排列。请求出最小操作次数。

## 样例 #1

### 输入

```
2
3 3 5 8
2 9 2```

### 输出

```
1 2```

# 题解

## 作者：Alex_Wei (赞：9)

将塔视为序列，分裂操作等价于将一个序列切成两半，合并操作等价于将两个序列相接。

考虑初始序列及其相邻两个数 $x, y$，如果 $x$ 在最终序列的后继不是 $y$，则 $x, y$ 之间需要用至少一次分裂操作分开。

通过执行上述必需的分裂操作，我们得到一些序列，它们是最终序列的极长连续段。设至少分裂 $c$ 次，则得到 $n + c$ 个序列。对它们执行 $n + c - 1$ 次合并操作即可达到目标。

如何检查 $x$ 在最终序列的后继是否为 $y$：将所有数离散化。设 $x, y$ 离散化后得到 $x', y'$，则充要条件为 $x' + 1 = y'$。

- 另一种自然地分析合并次数的方向：考虑最终序列及其相邻两个数 $x, y$，如果 $x$ 在初始序列的后继不是 $y$，则 $x, y$ 之间需要用至少一次合并操作连接。

设 $m = \sum k_i$，则时间复杂度为 $\mathcal{O}(m\log m)$。

```cpp
// LUOGU_RID: 97121879
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e4 + 5;
int n, cnt, d[N];
vector<int> k[N];
int main() {
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  cin >> n;
  for(int i = 1; i <= n; i++) {
    int sz, a;
    cin >> sz;
    while(sz--) cin >> a, k[i].push_back(d[++cnt] = a);
  }
  sort(d + 1, d + cnt + 1);
  int split = 0;
  for(int i = 1; i <= n; i++) {
    for(int &it : k[i]) it = lower_bound(d + 1, d + cnt + 1, it) - d;
    for(int p = 1; p < k[i].size(); p++) split += k[i][p - 1] + 1 != k[i][p];
  }
  cout << split << " " << n + split - 1 << "\n";
  return 0;
}
/*
g++ E.cpp -o E -std=c++14 -O2 -DALEX_WEI
*/
```

---

## 作者：FFTotoro (赞：8)

本题需要使用离散化算法。

因为本题我们只关注数的相对大小，先对塔里面的数进行离散化处理。即，按照从小到大的顺序编号为 $1,2,3\ldots$。

然后，如果对于一个塔 $a$，塔里存在 $a_i-a{i+1}\ne 1$，那么这两个元素之间就必须进行一次分裂操作（不妨设 $a_i<a_{i+1}$，因为存在 $a_i<k<a_{i+1}$，而 $k$ 在最后必须插入它们之间，如果不进行分裂无法插入）。

因为所有数皆不相同，所以不存在两个塔分别是 $\{1,2\}$ 和 $\{2,1\}$ 导致无法合并的情况，上述的做法是正确的。

记分裂的次数为 $c$，那么分裂完成后总共就有 $c+n$ 个塔，所以共需 $c+n-1$ 次合并。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int n,c=0,c0=0; cin>>n;
  vector<vector<int> > a(n);
  set<int> s; map<int,int> m;
  for(auto &i:a){
    int k; cin>>k; i.resize(k);
    for(auto &j:i)cin>>j,s.emplace(j); // 记录
  }
  for(auto &i:s)m[i]=++c; // 编号
  for(auto &i:a)for(auto &j:i)j=m[j]; // 赋值
  for(auto &i:a)
    for(int j=1;j<i.size();j++)
      if(i[j]-i[j-1]>1||i[j]-i[j-1]<0)c0++; // 判断
  cout<<c0<<' '<<c0+n-1<<endl;
  return 0;
}
```

---

