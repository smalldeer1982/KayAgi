# 题目信息

# Minimize Equal Sum Subarrays

## 题目描述

# 最小化相等和子数组


已知 [农夫约翰喜欢排列](https://usaco.org/index.php?page=viewproblem2&cpid=1421)，我也喜欢它们！

给定一个长度为 $ n $ 的排列 $ p $。

找到一个长度为 $ n $ 的排列 $ q $，使得以下条件下的对数最小化：对所有 $ 1 \leq i \leq j \leq n $，使得 $ p_i + p_{i+1} + \ldots + p_j = q_i + q_{i+1} + \ldots + q_j $。

**注**：一个长度为 $ n $ 的排列是一个包含 $ 1 $ 到 $ n $ 的 $ n $ 个不同整数的数组。例如，\[2, 3, 1, 5, 4\] 是一个排列，但 \[1, 2, 2\] 不是一个排列（数字 2 在数组中出现了两次），而 \[1, 3, 4\] 也不是一个排列（$ n=3 $，但数组中有 4）。

## 说明/提示

对于第一个测试用例，存在唯一一对 $ (i, j) $ ($ 1 \leq i \leq j \leq n $) 使得 $ p_i + p_{i+1} + \ldots + p_j = q_i + q_{i+1} + \ldots + q_j $，即 $ (1, 2) $。可以证明，没有这样的 $ q $ 使得不存在满足条件的对。

## 样例 #1

### 输入

```
3
2
1 2
5
1 2 3 4 5
7
4 7 5 1 2 6 3```

### 输出

```
2 1
3 5 4 2 1
6 2 1 4 7 3 5```

# AI分析结果

### 题目内容重写
已知 [农夫约翰喜欢排列](https://usaco.org/index.php?page=viewproblem2&cpid=1421)，我也喜欢它们！

给定一个长度为 $ n $ 的排列 $ p $。

找到一个长度为 $ n $ 的排列 $ q $，使得以下条件下的对数最小化：对所有 $ 1 \leq i \leq j \leq n $，使得 $ p_i + p_{i+1} + \ldots + p_j = q_i + q_{i+1} + \ldots + q_j $。

**注**：一个长度为 $ n $ 的排列是一个包含 $ 1 $ 到 $ n $ 的 $ n $ 个不同整数的数组。例如，\[2, 3, 1, 5, 4\] 是一个排列，但 \[1, 2, 2\] 不是一个排列（数字 2 在数组中出现了两次），而 \[1, 3, 4\] 也不是一个排列（$ n=3 $，但数组中有 4）。

### 题解分析与结论
本题的核心目标是通过构造一个排列 $ q $，使得与给定排列 $ p $ 的子数组和相等的对数最小化。所有题解都提出了相似的思路：通过将 $ p $ 的元素进行循环移位来构造 $ q $，从而使得只有整个数组的和相等的对数最小化。

### 精选题解

#### 题解1：作者：GLr137 (赞：1)
- **星级**：4
- **关键亮点**：通过表格直观地展示了循环移位的效果，并证明了这种构造方法的正确性。
- **代码实现**：
  ```cpp
  #include <bits/stdc++.h>
  using namespace std;
  int main (){
      int t, n, sz[200005];
      cin >> t;
      for (int i = 1; i <= t; i++){
          cin >> n;
          for (int i = 1; i <= n; i++){
              cin >> sz[i];
          }
          for (int i = 2; i <= n; i++){
              cout << sz[i] << " ";
          }
          cout << sz[1] << "\n";
      }
      return 0;
  }
  ```
- **核心思想**：将 $ p $ 的元素循环左移一位，使得只有整个数组的和相等的对数最小化。

#### 题解2：作者：Even_If (赞：1)
- **星级**：4
- **关键亮点**：通过将 $ q $ 的最后一个元素移到最前面，其他元素向后移一位，使得 $ sumq_{i,j} $ 与 $ sump_{i,j} $ 错位，从而最小化相等的对数。
- **代码实现**：
  ```cpp
  #include <bits/stdc++.h>
  using namespace std;
  #define int long long
  int t;
  const int N = 2e5 + 10;
  int a[N];
  signed main(void) {
      cin >> t;
      while (t --) {
          int n;
          cin >> n;
          for (int i = 1; i <= n; i ++) {
              cin >> a[i];
          }
          cout << a[n] << ' ';
          for (int i = 1; i < n; i ++) cout << a[i] << ' ';
          cout << endl;
      }
      return 0;
  }
  ```
- **核心思想**：将 $ p $ 的最后一个元素移到最前面，其他元素向后移一位，使得只有整个数组的和相等的对数最小化。

#### 题解3：作者：joe_zxq (赞：1)
- **星级**：4
- **关键亮点**：通过模拟样例和暴力计算小数据，验证了循环移位构造方法的正确性。
- **代码实现**：
  ```cpp
  #include <bits/stdc++.h>
  using namespace std;
  #define ll long long
  ll tc, n, a[200024];
  void solve() {
      scanf("%lld", &n);
      for (ll i = 1; i <= n; i++) {
          scanf("%lld", &a[i]);
      }
      printf("%lld ", a[n]);
      for (ll i = 1; i < n; i++) {
          printf("%lld ", a[i]);
      }
      printf("\n");
  }
  int main() {
      scanf("%lld", &tc);
      while (tc--) {
          solve();
      }    
      return 0;
  }
  ```
- **核心思想**：将 $ p $ 的最后一个元素移到最前面，其他元素向后移一位，使得只有整个数组的和相等的对数最小化。

### 最优关键思路
通过循环移位构造 $ q $，使得只有整个数组的和相等的对数最小化。这种方法简单高效，且易于实现。

### 可拓展之处
类似的问题可以通过循环移位或其他排列变换来最小化某种条件。例如，可以通过循环移位来最小化两个排列的逆序对数。

### 推荐题目
1. [P1045 排列](https://www.luogu.com.cn/problem/P1045)
2. [P1050 排列计数](https://www.luogu.com.cn/problem/P1050)
3. [P1051 排列组合](https://www.luogu.com.cn/problem/P1051)

### 个人心得摘录
- **GLr137**：通过表格直观地展示了循环移位的效果，并证明了这种构造方法的正确性。
- **Even_If**：通过将 $ q $ 的最后一个元素移到最前面，其他元素向后移一位，使得 $ sumq_{i,j} $ 与 $ sump_{i,j} $ 错位，从而最小化相等的对数。
- **joe_zxq**：通过模拟样例和暴力计算小数据，验证了循环移位构造方法的正确性。

---
处理用时：40.41秒