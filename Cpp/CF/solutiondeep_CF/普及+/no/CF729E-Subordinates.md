# 题目信息

# Subordinates

## 题目描述

There are $ n $ workers in a company, each of them has a unique id from $ 1 $ to $ n $ . Exaclty one of them is a chief, his id is $ s $ . Each worker except the chief has exactly one immediate superior.

There was a request to each of the workers to tell how how many superiors (not only immediate). Worker's superiors are his immediate superior, the immediate superior of the his immediate superior, and so on. For example, if there are three workers in the company, from which the first is the chief, the second worker's immediate superior is the first, the third worker's immediate superior is the second, then the third worker has two superiors, one of them is immediate and one not immediate. The chief is a superior to all the workers except himself.

Some of the workers were in a hurry and made a mistake. You are to find the minimum number of workers that could make a mistake.

## 说明/提示

In the first example it is possible that only the first worker made a mistake. Then:

- the immediate superior of the first worker is the second worker,
- the immediate superior of the third worker is the first worker,
- the second worker is the chief.

## 样例 #1

### 输入

```
3 2
2 0 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 3
1 0 0 4 1
```

### 输出

```
2
```

# AI分析结果

### 题目内容
# 下属

## 题目描述
公司里有 $n$ 个员工，每个人都有一个唯一的编号，范围从 $1$ 到 $n$ 。其中恰好有一个人是主管，其编号为 $s$ 。除主管外，每个员工都恰有一个直属上级。

要求每个员工说出自己有多少上级（不仅是直属上级）。员工的上级包括其直属上级、直属上级的直属上级，依此类推。例如，如果公司有三个员工，其中第一个是主管，第二个员工的直属上级是第一个，第三个员工的直属上级是第二个，那么第三个员工有两个上级，一个是直属上级，一个是非直属上级。主管是除自己以外所有员工的上级。

有些员工很匆忙，可能会犯错。你需要找出可能犯错的最少员工人数。

## 说明/提示
在第一个样例中，有可能只有第一个员工犯了错。那么：
- 第一个员工的直属上级是第二个员工，
- 第三个员工的直属上级是第一个员工，
- 第二个员工是主管。

## 样例 #1
### 输入
```
3 2
2 0 2
```
### 输出
```
1
```

## 样例 #2
### 输入
```
5 3
1 0 0 4 1
```
### 输出
```
2
```

### 算法分类
贪心

### 题解综合分析与结论
所有题解思路核心均基于合法序列的性质：有且仅有一个0（对应主管），且序列在升序排列后是连续的（因为每个员工的上级数比其直接上级多1）。难点在于如何利用这些性质找到最少犯错人数，各题解均采用贪心策略，即从大到小拿数填补序列中的“缺口”。不同题解在实现细节上略有差异，如统计方式、填补缺口的具体逻辑等。

### 所选的题解
- **作者：xzggzh1 (5星)**
    - **关键亮点**：思路清晰简洁，代码精炼。直接利用桶计数，通过一次遍历完成统计和填补缺口的操作，逻辑紧凑。
    - **核心代码**：
```cpp
int n, s, x, ans, cnt = 1, a[200005];
int main()
{
    cin >> n >> s;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        i == s? ans += x > 0 : a[x]++;
    }
    for (int i = 1; cnt < n; i++) {
        cnt += a[i]? a[i] : 1;
        ans += a[i] == 0;
    }
    cout << ans;
}
```
    - **核心实现思想**：首先输入数据，若主管回答的上级数不为0则计入错误数，同时用桶a统计各上级数出现的次数。然后遍历桶，若当前数出现次数为0则填补缺口并增加错误数，否则更新已处理的人数。

- **作者：activeO (4星)**
    - **关键亮点**：思路阐述详细，代码注释丰富，易于理解。同样采用桶统计，按常规逻辑逐步实现填补缺口的操作。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int num[maxn];
int main() {
    int n, m, cnt = 1, ans = 0;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        if (i == m) ans += (x > 0);
        else num[x]++;
    }
    for (int i = 1; cnt < n; i++) {
        if (num[i]) cnt += num[i];
        else cnt++;
        ans += (num[i] == 0);
    }
    printf("%d\n", ans);
    return 0;
}
```
    - **核心实现思想**：与xzggzh1思路类似，先输入数据，统计主管错误及各上级数出现次数，再遍历桶，根据桶中数据情况填补缺口并统计错误数。

### 最优关键思路或技巧
利用桶来统计每个上级数出现的次数，基于合法序列的性质，通过贪心策略从大到小填补序列中的不连续“缺口”，快速计算出最少犯错人数。

### 可拓展之处
此类题目属于基于特定数据结构（树结构）性质的思维贪心题。类似套路如根据图或树的某些拓扑性质，通过贪心策略解决节点或边的相关计数、优化等问题。

### 洛谷相似题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：贪心策略应用，通过对数据的排序和贪心选择解决问题。
- [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)：结合字符串和贪心思想，利用后缀数组相关知识解决问题。
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)：典型的贪心算法应用，通过合理安排顺序优化生产调度。 

---
处理用时：42.38秒