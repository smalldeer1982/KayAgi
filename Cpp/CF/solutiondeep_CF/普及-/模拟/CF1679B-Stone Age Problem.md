# 题目信息

# Stone Age Problem

## 题目描述

数组 $a$ 有 $n$ 个元素，需要进行 $q$ 次操作。

操作1：将第 $i$ 号元素改为 $x$

操作2：将数组中所有元素改为 $x$

每次操作完成后，输出当前数组中所有元素的总和。

## 样例 #1

### 输入

```
5 5
1 2 3 4 5
1 1 5
2 10
1 5 11
1 4 1
2 1```

### 输出

```
19
50
51
42
5```

# AI分析结果

### 题目翻译
#### 石器时代问题

#### 题目描述
数组 $a$ 包含 $n$ 个元素，需要进行 $q$ 次操作。

操作 1：将第 $i$ 个元素修改为 $x$。

操作 2：将数组中的所有元素修改为 $x$。

每次操作完成后，输出当前数组中所有元素的总和。

#### 样例 #1
##### 输入
```
5 5
1 2 3 4 5
1 1 5
2 10
1 5 11
1 4 1
2 1
```
##### 输出
```
19
50
51
42
5
```

### 综合分析与结论
这些题解主要围绕数组的单点修改、全局修改以及求和操作展开，核心是高效处理操作并输出每次操作后的数组总和。题解思路可分为两类：
1. **使用数据结构**：如线段树和珂朵莉树，利用其特性处理区间操作，但代码复杂度较高。
2. **不使用数据结构**：通过记录操作时间、标记或使用集合等方式，以较低的时间和空间复杂度解决问题。

### 所选题解
- **作者：_lfxxx_（5星）**
    - **关键亮点**：思路清晰，代码简洁，时间复杂度为 $O(n + q)$，通过记录元素最后修改时间和全局操作时间，巧妙处理单点和全局修改。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace solution{
#define ll long long
constexpr int N=2e5+5;
int a[N],t[N],tag,T=-1;
void main(){
    int n,q,op,x,y;
    ll sum=0;
    cin>>n>>q;
    for(int i=1;i<=n;++i)
        cin>>a[i],sum+=a[i];
    for(int i=1;i<=q;++i){
        cin>>op>>x;
        if(op==1){
            cin>>y;
            sum+=y-(t[x]>T?a[x]:tag);
            t[x]=i,a[x]=y;
        }
        else
            tag=x,T=i,sum=(ll)n*x;
        cout<<sum<<'\n';
    }
}
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solution::main(),0;
}
```
    - **核心实现思想**：用 $t_i$ 记录 $a_i$ 最后修改的时间，$T$ 记录 2 操作最后的时间。操作 1 时，比较 $t_i$ 和 $T$ 确定元素修改前的值；操作 2 时，直接更新总和为 $n\times x$。

- **作者：Anguei（4星）**
    - **关键亮点**：提供了两种思路，珂朵莉树思路有拓展性，不使用数据结构的方法时间复杂度为 $O(n + q)$，通过记录时间戳处理操作冲突。
    - **核心代码**：
```cpp
void solution() {
  int n, q;
  read(n, q);
  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) read(a[i]);
  ll s = std::accumulate(a.begin() + 1, a.end(), 0ll);
  int lastAll = -1, lastAllVal = -1;
  std::vector<int> lastSingle(n + 1);
  for (int _ = 1; _ <= q; ++_) {
    int opt;
    read(opt);
    if (opt == 1) {
      int idx, x;
      read(idx, x);
      s -= lastSingle[idx] < lastAll? lastAllVal : a[idx];
      s += x;
      lastSingle[idx] = _;
      a[idx] = x;
    } else {
      int x;
      read(x);
      lastAll = _;
      lastAllVal = x;
      s = 1ll * x * n;
    }
    print(s);
  }
}
```
    - **核心实现思想**：记录每个位置上次修改的时间戳 `lastSingle[i]`、上一次全局修改的时间 `lastAll` 和修改的值 `lastAllVal`。操作 1 时，根据时间戳确定元素修改前的值；操作 2 时，更新全局信息和总和。

### 最优关键思路或技巧
不使用数据结构的方法通过记录操作时间或标记，避免了数据结构的复杂实现，降低了代码复杂度和时间复杂度。

### 可拓展之处
同类型题可拓展到多维数组的单点和区间修改，或增加更多类型的操作。类似算法套路可用于处理需要记录历史操作信息的问题。

### 洛谷推荐题目
1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)：基础线段树区间修改和查询。
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)：树状数组区间修改和单点查询。
3. [P2023 [AHOI2009]维护序列](https://www.luogu.com.cn/problem/P2023)：线段树区间乘法和加法操作。

### 个人心得
无。

---
处理用时：27.82秒