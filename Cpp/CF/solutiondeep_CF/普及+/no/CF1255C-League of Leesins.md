# 题目信息

# League of Leesins

## 题目描述

Bob is an avid fan of the video game "League of Leesins", and today he celebrates as the League of Leesins World Championship comes to an end!

The tournament consisted of $ n $ ( $ n \ge 5 $ ) teams around the world. Before the tournament starts, Bob has made a prediction of the rankings of each team, from $ 1 $ -st to $ n $ -th. After the final, he compared the prediction with the actual result and found out that the $ i $ -th team according to his prediction ended up at the $ p_i $ -th position ( $ 1 \le p_i \le n $ , all $ p_i $ are unique). In other words, $ p $ is a permutation of $ 1, 2, \dots, n $ .

As Bob's favorite League player is the famous "3ga", he decided to write down every $ 3 $ consecutive elements of the permutation $ p $ . Formally, Bob created an array $ q $ of $ n-2 $ triples, where $ q_i = (p_i, p_{i+1}, p_{i+2}) $ for each $ 1 \le i \le n-2 $ . Bob was very proud of his array, so he showed it to his friend Alice.

After learning of Bob's array, Alice declared that she could retrieve the permutation $ p $ even if Bob rearranges the elements of $ q $ and the elements within each triple. Of course, Bob did not believe in such magic, so he did just the same as above to see Alice's respond.

For example, if $ n = 5 $ and $ p = [1, 4, 2, 3, 5] $ , then the original array $ q $ will be $ [(1, 4, 2), (4, 2, 3), (2, 3, 5)] $ . Bob can then rearrange the numbers within each triple and the positions of the triples to get $ [(4, 3, 2), (2, 3, 5), (4, 1, 2)] $ . Note that $ [(1, 4, 2), (4, 2, 2), (3, 3, 5)] $ is not a valid rearrangement of $ q $ , as Bob is not allowed to swap numbers belong to different triples.

As Alice's friend, you know for sure that Alice was just trying to show off, so you decided to save her some face by giving her any permutation $ p $ that is consistent with the array $ q $ she was given.

## 样例 #1

### 输入

```
5
4 3 2
2 3 5
4 1 2
```

### 输出

```
1 4 2 3 5 
```

# AI分析结果

### 题目翻译
# 英雄联盟全球总决赛

## 题目描述
Bob 是电子游戏《英雄联盟》的狂热粉丝，今天他格外兴奋，因为英雄联盟全球总决赛落下帷幕！

本次锦标赛有 $n$（$n \ge 5$）支来自世界各地的队伍参赛。在锦标赛开始前，Bob 对每支队伍的排名进行了预测，排名从第 1 到第 $n$。总决赛结束后，他将预测结果与实际结果进行了对比，发现他预测中的第 $i$ 支队伍最终排名为 $p_i$（$1 \le p_i \le n$，所有的 $p_i$ 都是唯一的）。换句话说，$p$ 是 $1, 2, \dots, n$ 的一个排列。

由于 Bob 最喜欢的英雄联盟选手是著名的“3ga”，他决定记录下排列 $p$ 中每连续的 3 个元素。具体来说，Bob 创建了一个包含 $n - 2$ 个三元组的数组 $q$，其中 $q_i = (p_i, p_{i + 1}, p_{i + 2})$，对于每个 $1 \le i \le n - 2$。Bob 对自己的数组非常自豪，于是将其展示给了他的朋友 Alice。

在得知 Bob 的数组后，Alice 宣称，即使 Bob 重新排列 $q$ 中的元素以及每个三元组内的元素，她也能还原出排列 $p$。当然，Bob 不相信这种“魔法”，所以他按照上述方式对数组进行了重新排列，想看看 Alice 如何应对。

例如，如果 $n = 5$ 且 $p = [1, 4, 2, 3, 5]$，那么原始数组 $q$ 将是 $[(1, 4, 2), (4, 2, 3), (2, 3, 5)]$。Bob 可以重新排列每个三元组内的数字以及三元组的位置，得到 $[(4, 3, 2), (2, 3, 5), (4, 1, 2)]$。请注意，$[(1, 4, 2), (4, 2, 2), (3, 3, 5)]$ 不是 $q$ 的有效重排，因为 Bob 不允许交换属于不同三元组的数字。

作为 Alice 的朋友，你确定 Alice 只是在炫耀，所以你决定帮她挽回面子，给她一个与她所得到的数组 $q$ 一致的排列 $p$。

## 样例 #1

### 输入
```
5
4 3 2
2 3 5
4 1 2
```

### 输出
```
1 4 2 3 5 
```

### 算法分类
构造

### 综合分析与结论
- **思路对比**：三位作者的思路本质相同，都是基于数字在三元组中出现的次数来确定排列的起始元素，然后依次推导后续元素。postpone 和 alan1118 采用迭代的方式逐步确定每个位置的元素，寒鸽儿则借助图论的思想，用深搜的方式构建排列。
- **算法要点**：都先统计每个数字在三元组中出现的次数，利用出现次数为 1 的数字确定排列的开头，再结合出现次数为 2 的数字确定第二个元素，之后根据已确定的元素在相关三元组中寻找下一个元素。
- **解决难点**：关键在于如何从打乱的三元组中还原出原始排列。通过数字出现次数的特性，能够确定排列的起始部分，再利用三元组的关联性逐步推导后续元素，从而解决问题。

### 题解列表
- **postpone（4星）**：
  - **关键亮点**：思路清晰，代码简洁，通过简单的迭代方式实现了排列的还原，复杂度可视作线性。
  - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;

    vector<array<int, 3>> q(n - 2);
    for (int i = 0; i < n - 2; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> q[i][j];
            q[i][j]--;
        }
    }

    vector a(n, vector<int>());
    for (int i = 0; i < n - 2; i++) {
        for (int j = 0; j < 3; j++) {
            a[q[i][j]].push_back(i);
        }
    }

    vector<int> p(n);
    vector<bool> used(n);

    for (int i = 0; i < n; i++) {
        if (a[i].size() == 1) {
            p[0] = i;
            used[p[0]] = true;
            break;
        }
    }

    for (auto i : a[p[0]]) {
        for (int j = 0; j < 3; j++) {
            if (a[q[i][j]].size() == 2) {
                p[1] = q[i][j];
                break;
            }
        }
        used[p[1]] = true;
    }
    for (int i = 2; i < n; i++) {
        for (auto j : a[p[i - 2]]) {
            for (int k = 0; k < 3; k++) {
                if (not used[q[j][k]]) {
                    p[i] = q[j][k];
                }
            }
        }
        used[p[i]] = true;
    }
    for (auto i : p) {
        cout << i + 1 << " ";
    }

    return 0;
}
```
**核心实现思想**：先读取输入的三元组，统计每个数字所在的三元组编号。然后找到出现次数为 1 的数字作为排列的开头，再在其所在三元组中找到出现次数为 2 的数字作为第二个元素。最后从第三个位置开始，根据已确定的元素在相关三元组中寻找未使用的数字，依次确定排列的后续元素。

### 最优关键思路或技巧
- 利用数字在三元组中出现的次数来确定排列的起始元素，这是解决问题的关键思路。
- 通过记录每个数字所在的三元组编号，方便后续查找相关三元组，提高查找效率。

### 拓展思路
同类型题目可能会有不同的元组形式，如两元组、四元组等，解题思路类似，都是通过统计元素出现的次数和元组的关联性来还原原始序列。

### 推荐洛谷题目
- [CF1095D](https://www.luogu.com.cn/problem/CF1095D)：与本题思路相关，是“两元组”的问题。
- [P1103 书本整理](https://www.luogu.com.cn/problem/P1103)：涉及序列的构造和优化。
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：需要构造数字三角形并进行相关计算。

### 个人心得摘录与总结
- **alan1118**：提到看到其他同学用拓扑 AC，但认为本题不需要用到图论，灵感来自 [CF1095D]，说明可以从类似题目中获取解题思路，拓宽思维方式。 

---
处理用时：48.57秒