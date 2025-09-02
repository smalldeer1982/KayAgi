# 题目信息

# [ABC219C] Neo-lexicographic Ordering

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc219/tasks/abc219_c

AtCoder 王国を治める高橋君は、英小文字のアルファベット順を変更することにしました。

新たなアルファベット順は`a` $ , $ `b` $ ,\ \ldots, $ `z` を並べ替えて得られる文字列 $ X $ を用いて表されます。$ X $ の $ i\ \,\ (1\ \leq\ i\ \leq\ 26) $ 文字目は、新たな順番において $ i $ 番目に小さい英小文字を表します。

AtCoder 王国には $ N $ 人の国民がおり、それぞれの国民の名前は $ S_1,\ S_2,\ \dots,\ S_N $ です。ここで、$ S_i\ \,\ (1\ \leq\ i\ \leq\ N) $ は英小文字からなります。  
 これらの名前を、高橋君の定めたアルファベット順に基づく辞書順に従って並べ替えてください。

 辞書順とは？ 辞書順とは簡単に説明すると「単語が辞書に載っている順番」を意味します。より厳密な説明として、英小文字からなる相異なる文字列 $ S,\ T $ の大小を判定するアルゴリズムを以下に説明します。

以下では「 $ S $ の $ i $ 文字目の文字」を $ S_i $ のように表します。また、 $ S $ が $ T $ より辞書順で小さい場合は $ S\ \lt\ T $ 、大きい場合は $ S\ \gt\ T $ と表します。

1. $ S,\ T $ のうち長さが大きくない方の文字列の長さを $ L $ とします。$ i=1,2,\dots,L $ に対して $ S_i $ と $ T_i $ が一致するか調べます。
2. $ S_i\ \neq\ T_i $ である $ i $ が存在する場合、そのような $ i $ のうち最小のものを $ j $ とします。そして、$ S_j $ と $ T_j $ を比較して、$ S_j $ が $ T_j $ よりアルファベット順で小さい場合は $ S\ \lt\ T $ 、そうでない場合は $ S\ \gt\ T $ と決定して、アルゴリズムを終了します。
3. $ S_i\ \neq\ T_i $ である $ i $ が存在しない場合、$ S $ と $ T $ の長さを比較して、$ S $ が $ T $ より短い場合は $ S\ \lt\ T $ 、長い場合は $ S\ \gt\ T $ と決定して、アルゴリズムを終了します。

## 说明/提示

### 制約

- $ X $ は `a` $ , $ `b` $ ,\ \ldots, $ `z` を並べ替えて得られる
- $ 2\ \leq\ N\ \leq\ 50000 $
- $ N $ は整数
- $ 1\ \leq\ |S_i|\ \leq\ 10\ \,\ (1\ \leq\ i\ \leq\ N) $
- $ S_i $ は英小文字からなる $ (1\ \leq\ i\ \leq\ N) $
- $ S_i\ \neq\ S_j $ $ (1\ \leq\ i\ \lt\ j\ \leq\ N) $

### Sample Explanation 1

高橋君が新たに設定したアルファベット順において、`b` は `a` より小さく、`z` は `y` より小さいです。そのため、国民の名前を辞書順に並べ替えると、小さい順に `bzz` $ , $ `bzy` $ , $ `abx` $ , $ `caa` となります。

## 样例 #1

### 输入

```
bacdefghijklmnopqrstuvwxzy

4

abx

bzz

bzy

caa```

### 输出

```
bzz

bzy

abx

caa```

## 样例 #2

### 输入

```
zyxwvutsrqponmlkjihgfedcba

5

a

ab

abc

ac

b```

### 输出

```
b

a

ac

ab

abc```

# AI分析结果

【题目内容】
# [ABC219C] Neo-lexicographic Ordering

## 题目描述

AtCoder 王国的统治者高桥君决定改变英文字母的顺序。

新的字母顺序由字符串 $ X $ 表示，$ X $ 是将 `a` 到 `z` 重新排列得到的。$ X $ 的第 $ i $ 个字符（$ 1 \leq i \leq 26 $）表示在新的顺序中第 $ i $ 小的英文字母。

AtCoder 王国有 $ N $ 个国民，每个国民的名字分别为 $ S_1, S_2, \dots, S_N $。其中，$ S_i $（$ 1 \leq i \leq N $）由小写字母组成。请根据高桥君定义的新字母顺序对这些名字进行字典序排序。

字典序的定义如下：对于两个不同的字符串 $ S $ 和 $ T $，按以下规则比较大小：

1. 取 $ S $ 和 $ T $ 中较短的长度为 $ L $。对于 $ i = 1, 2, \dots, L $，比较 $ S_i $ 和 $ T_i $。
2. 如果存在 $ S_i \neq T_i $，则找到最小的 $ j $ 使得 $ S_j \neq T_j $。比较 $ S_j $ 和 $ T_j $，如果 $ S_j $ 在新字母顺序中小于 $ T_j $，则 $ S < T $，否则 $ S > T $。
3. 如果所有字符都相同，则比较字符串长度，较短的字符串较小。

## 说明/提示

### 约束

- $ X $ 是由 `a` 到 `z` 重新排列得到的。
- $ 2 \leq N \leq 50000 $
- $ N $ 是整数。
- $ 1 \leq |S_i| \leq 10 $（$ 1 \leq i \leq N $）
- $ S_i $ 由小写字母组成（$ 1 \leq i \leq N $）
- $ S_i \neq S_j $（$ 1 \leq i < j \leq N $）

### 样例解释 1

在新的字母顺序中，`b` 比 `a` 小，`z` 比 `y` 小。因此，国民的名字按字典序排序后为 `bzz`, `bzy`, `abx`, `caa`。

## 样例 #1

### 输入

```
bacdefghijklmnopqrstuvwxzy

4

abx

bzz

bzy

caa
```

### 输出

```
bzz

bzy

abx

caa
```

## 样例 #2

### 输入

```
zyxwvutsrqponmlkjihgfedcba

5

a

ab

abc

ac

b
```

### 输出

```
b

a

ac

ab

abc
```

【算法分类】
排序

【题解分析与结论】
本题的核心是根据自定义的字母顺序对字符串进行排序。由于字母顺序被重新定义，因此需要将字符串中的每个字符映射到新的顺序中，然后进行比较。

【通用建议与扩展思路】
1. **映射字符到新顺序**：首先需要将每个字符映射到新的顺序中，可以通过数组或哈希表实现。
2. **自定义比较函数**：在排序时，使用自定义的比较函数，根据映射后的顺序进行比较。
3. **优化**：由于 $ N $ 可能达到 50000，排序算法的时间复杂度应尽量低，建议使用快速排序或归并排序。

【推荐题目】
1. [P1781 宇宙总统](https://www.luogu.com.cn/problem/P1781)
2. [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)
3. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)

【关键思路与技巧】
1. **字符映射**：通过数组或哈希表将字符映射到新的顺序中，方便后续比较。
2. **自定义排序**：使用自定义的比较函数，根据映射后的顺序进行字符串比较。
3. **时间复杂度优化**：选择合适的排序算法，确保在大数据量下的高效排序。

【核心代码实现】
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    string X;
    int N;
    cin >> X >> N;
    
    vector<string> names(N);
    for (int i = 0; i < N; ++i) {
        cin >> names[i];
    }
    
    map<char, int> order;
    for (int i = 0; i < 26; ++i) {
        order[X[i]] = i;
    }
    
    sort(names.begin(), names.end(), [&](const string& a, const string& b) {
        int len = min(a.size(), b.size());
        for (int i = 0; i < len; ++i) {
            if (order[a[i]] != order[b[i]]) {
                return order[a[i]] < order[b[i]];
            }
        }
        return a.size() < b.size();
    });
    
    for (const string& name : names) {
        cout << name << endl;
    }
    
    return 0;
}
```

【代码说明】
1. **字符映射**：使用 `map<char, int>` 将字符映射到新的顺序中。
2. **自定义比较函数**：在 `sort` 函数中使用 lambda 表达式，根据映射后的顺序进行字符串比较。
3. **排序**：使用 `sort` 函数对字符串进行排序，时间复杂度为 $ O(N \log N) $。

---
处理用时：34.41秒