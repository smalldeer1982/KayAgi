# 题目信息

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

# AI分析结果

### 题目翻译
#### [ABC344C] A + B + C

#### 题目描述
[problemUrl]: https://atcoder.jp/contests/abc344/tasks/abc344_c

给定 3 个数列 $A=(A_1,\ldots,A_N)$、$B=(B_1,\ldots,B_M)$ 和 $C=(C_1,\ldots,C_L)$。

此外，还会给出数列 $X=(X_1,\ldots,X_Q)$。对于每个 $i = 1,\ldots,Q$，请解决以下问题：

问题：能否从数列 $A$、$B$ 和 $C$ 中各选一个元素，使它们的和等于 $X_i$？

#### 说明/提示
##### 限制条件
- $1 \leq N,M,L \leq 100$
- $0 \leq A_i, B_i,C_i \leq 10^8$
- $1 \leq Q \leq 2\times 10^5$
- $0 \leq X_i \leq 3\times 10^8$
- 输入的所有值均为整数

##### 样例解释 1
- 无法从 $A$、$B$、$C$ 中各选一个元素，使它们的和为 1。
- 从 $A$、$B$、$C$ 中分别选 1、2、2 时，它们的和为 5。
- 从 $A$、$B$、$C$ 中分别选 2、4、4 时，它们的和为 10。
- 无法从 $A$、$B$、$C$ 中各选一个元素，使它们的和为 50。

#### 样例 #1
##### 输入
```
3
1 2 3
2
2 4
6
1 2 4 8 16 32
4
1 5 10 50
```
##### 输出
```
No
Yes
Yes
No
```

### 综合分析与结论
这些题解的核心思路都是先预处理出 $A$、$B$、$C$ 三个数列中各取一个元素相加的所有可能结果，再对 $X$ 中的每个元素进行查询判断。

#### 算法要点对比
- **使用 `map` 或 `unordered_map`**：多数题解使用 `map` 或 `unordered_map` 来记录和的存在情况，利用其查找功能判断 $X_i$ 是否存在。`map` 基于红黑树实现，查找复杂度为 $O(\log n)$；`unordered_map` 基于哈希表实现，平均查找复杂度为 $O(1)$。
- **使用 `unordered_set` 或 `set`**：部分题解使用 `unordered_set` 或 `set` 存储和的集合，同样用于查找 $X_i$。`set` 基于红黑树，查找复杂度为 $O(\log n)$；`unordered_set` 基于哈希表，平均查找复杂度为 $O(1)$。
- **二分查找**：有题解将所有和存储在数组中并排序，然后使用二分查找判断 $X_i$ 是否存在，时间复杂度为 $O(NML + NML\log NML + Q\log NML)$。
- **桶标记**：少数题解使用桶标记的方法，但由于和的范围较大，可能会受到空间限制。

#### 解决难点
- **数据范围大**：由于序列中的值很大，使用普通数组存储会超出空间限制，因此多数题解采用 `map`、`unordered_map`、`set` 或 `unordered_set` 等数据结构。
- **查询次数多**：$Q$ 的值较大，需要在预处理后以较低的时间复杂度进行查询，不同的数据结构和算法在查询效率上有所差异。

### 评分较高的题解
- **作者：xxboyxx (赞：5)，5星**
    - **关键亮点**：思路清晰，代码简洁易懂，详细说明了使用 `map` 的原因，时间复杂度分析明确。
    - **核心代码**：
```cpp
map<int,int> p;
for (int i=1;i<=n;i++)
    for (int j=1;j<=m;j++)
        for (int k=1;k<=l;k++)
            p[a[i]+b[j]+c[k]]=1;
while (q--)
{
    int x;
    cin>>x;
    if (p[x]==1)
        cout<<"Yes\n";
    else
        cout<<"No\n";
}
```
- **作者：OIer_Tan (赞：2)，4星**
    - **关键亮点**：分析了使用 `set` 和 `unordered_set` 的时间复杂度，提供了不同数据结构的选择，代码规范。
    - **核心代码**：
```cpp
unordered_set <ll> cnt;
for (ll i = 1 ; i <= n ; i ++ )
{
    for (ll j = 1; j <= m ; j ++ )
    {
        for (ll k = 1 ; k <= l ; k ++ )
        {
            cnt.insert ( a [i] + b [j] + c [k] ) ;
        }
    }
}
while ( q -- )
{
    ll x;
    cin >> x;
    if ( cnt.find ( x )!= cnt.end () )
    {
        cout << "Yes" << "\n" ;
    }
    else
    {
        cout << "No" << "\n" ;
    }
}
```
- **作者：littlebug (赞：2)，4星**
    - **关键亮点**：采用二分查找的方法，对时间复杂度进行了详细分析，代码实现规范。
    - **核心代码**：
```cpp
int ans[MAX2],ai=0;
for(int i=1;i<=n;++i)
    for(int j=1;j<=m;++j)
        for(int k=1;k<=l;++k)
            ans[++ai]=a[i]+b[j]+c[k];
sort(ans+1,ans+ai+1);
while(q--)
{
    cin>>x;
    y=lower_bound(ans+1,ans+ai+1,x)-ans;
    if(x==ans[y])
        puts("Yes");
    else
        puts("No");
}
```

### 最优关键思路或技巧
- **预处理**：通过三重循环枚举 $A$、$B$、$C$ 中各取一个元素的所有组合，计算它们的和并记录，避免了每次查询时的重复计算。
- **使用合适的数据结构**：根据数据范围和查询需求，选择 `map`、`unordered_map`、`set` 或 `unordered_set` 等数据结构来存储和查询和的存在情况，提高查询效率。

### 拓展思路
同类型题或类似算法套路：
- 给定多个数组，判断是否能从每个数组中选取一个元素，使它们的和满足特定条件。
- 可以通过预处理和使用合适的数据结构来优化查询过程，降低时间复杂度。

### 洛谷相似题目推荐
- [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
- [P1991 无线通讯网](https://www.luogu.com.cn/problem/P1991)
- [P2676 [USACO07DEC]Bookshelf B](https://www.luogu.com.cn/problem/P2676)

### 个人心得摘录与总结
本题题解中未包含个人心得（调试经历、踩坑教训、顿悟感想等）。

---
处理用时：45.11秒