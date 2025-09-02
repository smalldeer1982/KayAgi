# 题目信息

# Minimize Inversions

## 题目描述

You are given two permutations $ a $ and $ b $ of length $ n $ . A permutation is an array of $ n $ elements from $ 1 $ to $ n $ where all elements are distinct. For example, an array \[ $ 2,1,3 $ \] is a permutation, but \[ $ 0,1 $ \] and \[ $ 1,3,1 $ \] aren't.

You can (as many times as you want) choose two indices $ i $ and $ j $ , then swap $ a_i $ with $ a_j $ and $ b_i $ with $ b_j $ simultaneously.

You hate inversions, so you want to minimize the total number of inversions in both permutations.

An inversion in a permutation $ p $ is a pair of indices $ (i, j) $ such that $ i < j $ and $ p_i > p_j $ . For example, if $ p=[3,1,4,2,5] $ then there are $ 3 $ inversions in it (the pairs of indices are $ (1,2) $ , $ (1,4) $ and $ (3,4) $ ).

## 说明/提示

In the first test case, the minimum possible number of inversions is $ 10 $ .

In the second test case, we can sort both permutations at the same time. For this, the following operations can be done:

- Swap the elements in the positions $ 1 $ and $ 3 $ in both permutations. After the operation, $ a = $ \[ $ 2,1,3 $ \], $ b = $ \[ $ 2,1,3 $ \].
- Swap the elements in the positions $ 1 $ and $ 2 $ . After the operations, $ a $ and $ b $ are sorted.

In the third test case, the minimum possible number of inversions is $ 7 $ .

## 样例 #1

### 输入

```
3
5
1 2 3 4 5
5 4 3 2 1
3
3 1 2
3 1 2
6
2 5 6 1 3 4
1 5 3 6 2 4```

### 输出

```
3 2 5 1 4
3 4 1 5 2
1 2 3
1 2 3
2 3 4 6 5 1
1 2 4 3 5 6```

# AI分析结果

### 题目内容翻译
## 最小化逆序对

### 题目描述
给定两个长度为 $n$ 的排列 $a$ 和 $b$。排列是一个包含从 $1$ 到 $n$ 的 $n$ 个元素的数组，且所有元素都不同。例如，数组 $[2, 1, 3]$ 是一个排列，但 $[0, 1]$ 和 $[1, 3, 1]$ 不是。

你可以（任意次数）选择两个索引 $i$ 和 $j$，然后同时交换 $a_i$ 和 $a_j$ 以及 $b_i$ 和 $b_j$。

你讨厌逆序对，所以你想最小化两个排列中逆序对的总数。

排列 $p$ 中的逆序对是一对索引 $(i, j)$，使得 $i < j$ 且 $p_i > p_j$。例如，如果 $p = [3, 1, 4, 2, 5]$，那么其中有 $3$ 个逆序对（索引对为 $(1, 2)$、$(1, 4)$ 和 $(3, 4)$）。

### 说明/提示
在第一个测试用例中，逆序对的最小可能数量是 $10$。

在第二个测试用例中，我们可以同时对两个排列进行排序。为此，可以进行以下操作：
- 同时交换两个排列中位置 $1$ 和 $3$ 的元素。操作后，$a = [2, 1, 3]$，$b = [2, 1, 3]$。
- 交换位置 $1$ 和 $2$ 的元素。操作后，$a$ 和 $b$ 都已排序。

在第三个测试用例中，逆序对的最小可能数量是 $7$。

### 样例 #1
#### 输入
```
3
5
1 2 3 4 5
5 4 3 2 1
3
3 1 2
3 1 2
6
2 5 6 1 3 4
1 5 3 6 2 4
```
#### 输出
```
3 2 5 1 4
3 4 1 5 2
1 2 3
1 2 3
2 3 4 6 5 1
1 2 4 3 5 6
```

### 算法分类
排序

### 综合分析与结论
这些题解的核心思路基本一致，都是通过排序来最小化两个排列中逆序对的总数。大部分题解选择将数组 $a$ 按升序排序，同时数组 $b$ 中对应元素也跟着移动，因为消除 $a$ 的一个逆序对最多会让 $b$ 产生一个逆序对，将 $a$ 升序排序不会使逆序对总数增多，且之后再消除 $b$ 的逆序对必然会使 $a$ 产生逆序对。

各题解的算法要点主要是使用结构体或 `pair` 绑定两个数组元素，然后自定义比较函数进行排序。解决的难点在于证明排序是最优解，不同题解从不同角度进行了分析，如考虑相邻元素交换对逆序对的影响、分析不同情况下逆序对数量的变化等。

### 所选题解
- **作者：ylch (赞：2)，4星**
    - **关键亮点**：思路清晰，不仅给出了排序的思路，还提出了用映射（打表）法配合哈希的实现方式，复杂度为 $O(Tn)$，并对代码实现进行了详细解释。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const int N = 2e5 + 10;

int n, m;
vector <int> a, b;
unordered_map <int, int> vis; 

int main() {
    int T; cin >> T;
    while(T --){
        cin >> n; a.resize(n + 1), b.resize(n + 1); 
        for(int i = 1; i <= n; i ++){
            cin >> a[i];
        }
        for(int i = 1; i <= n; i ++){
            cin >> b[i];
            vis[a[i]] = b[i];
        }
        for(int i = 1; i <= n; i ++){
            cout << i << " ";
        }
        cout << endl;
        for(int i = 1; i <= n; i ++){
            cout << vis[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}
```
    - **核心实现思想**：先将数组 $a$ 中值为 $i$ 的元素对应的数组 $b$ 中的元素记录在 `vis[i]` 中，然后直接输出 $1$ 到 $n$ 作为排序后的数组 $a$，再输出 `vis[1]` 到 `vis[n]` 作为数组 $b$ 中对应元素。

- **作者：Mashu77 (赞：0)，4星**
    - **关键亮点**：对排序是最优解进行了较为详细的证明，通过将交换操作视为交换若干次相邻元素的结果，分析相邻元素交换对逆序对的影响，逻辑严谨。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
struct node{
    int a,b;
}q[200005];
bool cmp(node x,node y){
    return x.a<y.a;
}
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++)cin>>q[i].a;
        for(int i=1;i<=n;i++)cin>>q[i].b;
        sort(q+1,q+n+1,cmp);
        for(int i=1;i<=n;i++)cout<<q[i].a<<" ";
        puts("");
        for(int i=1;i<=n;i++)cout<<q[i].b<<" ";
        puts("");
    }
    return 0;
}
```
    - **核心实现思想**：使用结构体 `node` 存储数组 $a$ 和 $b$ 的元素，自定义比较函数 `cmp` 按数组 $a$ 的元素升序排序，最后输出排序后的数组 $a$ 和 $b$。

- **作者：CheZiHe929 (赞：0)，4星**
    - **关键亮点**：给出了两种做法，一种是按数组 $a$ 从小到大排序，另一种是按数组 $a$ 和 $b$ 的和排序，并对两种做法都进行了详细的分类讨论和证明。
    - **核心代码（按数组 $a$ 排序）**：
```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
const int MAXN=2e5+5;

std::pair<int,int> a[MAXN];

signed main(){
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        for(int i=1;i<=n;i++)a[i].first=read();
        for(int i=1;i<=n;i++)a[i].second=read();
        
        std::sort(a+1,a+n+1);
        for(int i=1;i<=n;i++)cout << a[i].first << ' ';
        cout << endl;
        for(int i=1;i<=n;i++)cout << a[i].second << ' ';
        cout << endl;
    }
    return 0;
}
```
    - **核心实现思想**：使用 `pair` 存储数组 $a$ 和 $b$ 的元素，直接使用 `sort` 函数按数组 $a$ 的元素升序排序，最后输出排序后的数组 $a$ 和 $b$。

### 最优关键思路或技巧
- **排序思想**：通过排序将一个数组变为升序，同时另一个数组对应元素跟着移动，可最小化逆序对总数。
- **数据结构**：使用结构体或 `pair` 绑定两个数组的元素，方便排序操作。

### 拓展思路
同类型题可能会有更多限制条件或不同的操作规则，但核心思路可能仍然是通过排序或类似的贪心策略来优化目标值。例如，可能会增加数组的数量，或者改变交换操作的规则等。

### 推荐题目
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：经典的逆序对问题，可使用归并排序或树状数组求解。
- [P1093 奖学金](https://www.luogu.com.cn/problem/P1093)：涉及多条件排序的问题，与本题的排序思想有一定关联。
- [P1104 生日](https://www.luogu.com.cn/problem/P1104)：同样是排序问题，需要根据多个条件进行排序。

### 个人心得摘录与总结
部分题解提到这是一道“诈骗题”，点破思路后很简单，强调了找规律和分析问题本质的重要性。在解决这类问题时，要多尝试列举例子，从简单情况入手，找出规律，从而找到最优解。

---
处理用时：52.13秒