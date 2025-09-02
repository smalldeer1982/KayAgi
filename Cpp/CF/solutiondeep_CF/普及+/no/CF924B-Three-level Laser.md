# 题目信息

# Three-level Laser

## 题目描述

An atom of element X can exist in $ n $ distinct states with energies $ E_{1}<E_{2}<...<E_{n} $ . Arkady wants to build a laser on this element, using a three-level scheme. Here is a simplified description of the scheme.

Three distinct states $ i $ , $ j $ and $ k $ are selected, where $ i<j<k $ . After that the following process happens:

1. initially the atom is in the state $ i $ ,
2. we spend $ E_{k}-E_{i} $ energy to put the atom in the state $ k $ ,
3. the atom emits a photon with useful energy $ E_{k}-E_{j} $ and changes its state to the state $ j $ ,
4. the atom spontaneously changes its state to the state $ i $ , losing energy $ E_{j}-E_{i} $ ,
5. the process repeats from step 1.

Let's define the energy conversion efficiency as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924B/dd021747dbc78de91e905a31390ad0cfead20383.png), i. e. the ration between the useful energy of the photon and spent energy.

Due to some limitations, Arkady can only choose such three states that $ E_{k}-E_{i}<=U $ .

Help Arkady to find such the maximum possible energy conversion efficiency within the above constraints.

## 说明/提示

In the first example choose states $ 1 $ , $ 2 $ and $ 3 $ , so that the energy conversion efficiency becomes equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924B/dce12a2cd3991eb50251b026c5d21e8a7972a1a8.png).

In the second example choose states $ 4 $ , $ 5 $ and $ 9 $ , so that the energy conversion efficiency becomes equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF924B/92eb31d78d8cae5d41f0d6508215bf8fc27fa5c7.png).

## 样例 #1

### 输入

```
4 4
1 3 5 7
```

### 输出

```
0.5
```

## 样例 #2

### 输入

```
10 8
10 13 15 16 17 19 20 22 24 25
```

### 输出

```
0.875
```

## 样例 #3

### 输入

```
3 1
2 5 10
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# 三能级激光

## 题目描述
元素X的一个原子可以处于 $n$ 个不同的状态，其能量分别为 $E_{1}<E_{2}<...<E_{n}$ 。阿尔卡迪（Arkady）想用这种元素构建一个三能级激光。以下是该方案的简化描述。

选择三个不同的状态 $i$ 、 $j$ 和 $k$ ，其中 $i<j<k$ 。然后会发生以下过程：
1. 最初原子处于状态 $i$ 。
2. 我们花费 $E_{k}-E_{i}$ 的能量将原子置于状态 $k$ 。
3. 原子发射一个具有有用能量 $E_{k}-E_{j}$ 的光子，并将其状态变为状态 $j$ 。
4. 原子自发地将其状态变为状态 $i$ ，损失能量 $E_{j}-E_{i}$ 。
5. 从步骤1开始重复该过程。

我们将能量转换效率定义为 $\frac{E_{k}-E_{j}}{E_{k}-E_{i}}$ ，即光子的有用能量与所花费能量的比率。

由于某些限制，阿尔卡迪只能选择满足 $E_{k}-E_{i}<=U$ 的三个状态。

请帮助阿尔卡迪在上述限制内找到最大可能的能量转换效率。

## 说明/提示
在第一个示例中，选择状态 $1$ 、 $2$ 和 $3$ ，这样能量转换效率就等于 $\frac{E_{3}-E_{2}}{E_{3}-E_{1}}$ 。

在第二个示例中，选择状态 $4$ 、 $5$ 和 $9$ ，这样能量转换效率就等于 $\frac{E_{9}-E_{5}}{E_{9}-E_{4}}$ 。

## 样例 #1
### 输入
```
4 4
1 3 5 7
```
### 输出
```
0.5
```
## 样例 #2
### 输入
```
10 8
10 13 15 16 17 19 20 22 24 25
```
### 输出
```
0.875
```
## 样例 #3
### 输入
```
3 1
2 5 10
```
### 输出
```
-1
```
### 算法分类
二分

### 综合分析与结论
三道题解均围绕寻找满足条件的 $i$、$j$、$k$ 来最大化能量转换效率 $\frac{E_{k}-E_{j}}{E_{k}-E_{i}}$ 。其中，“_edge_”的题解采用乱搞做法，设置阈值 $B$ 来扫描确定 $i$、$j$ 位置，并非正解；“codwarm”和“梦应归于何处”的题解思路相近，均通过数学分析得出当 $i$、$k$ 固定时，$j$ 应取 $i + 1$ 使效率最大，再通过二分查找满足 $E_{k}-E_{i} \leq U$ 条件下最大的 $E_{k}$ 对应的 $k$ ，时间复杂度均为 $O(n \log n)$ ，思路清晰，属于正解。

### 所选的题解
- **作者：codwarm（5星）**
    - **关键亮点**：思路清晰，对 $j$、$k$ 的取值进行数学证明，代码简洁明了，逻辑严谨。
    - **核心代码片段**：
```cpp
int find(int i)
{
    int x = a[i]+k,l = i+2,r = n;
    while (l < r) // 二分
    {
        int mid = l + r + 1 >> 1;
        if (a[mid] <= x) l = mid;
        else r = mid-1;
    }
    if (a[l] <= x) return l;
    else return -1;
}

int main()
{
    scanf("%d%d",&n,&k);
    for (int i = 1;i <= n;i++) scanf("%d",&a[i]);
    for (int i = 1;i <= n-2;i++)
    {
        int x = find(i);
        if (x == -1) continue; // i j k 分别为 i i+1 x
        res = max(res,1.0*(a[x]-a[i+1])/(a[x]-a[i]));
    }
    if (res < 0) puts("-1"); //不存在
    else printf("%.10f",res);
    return 0;
}
```
    - **核心实现思想**：`find` 函数通过二分查找找到满足 $E_{k}-E_{i} \leq U$ 的最大 $E_{k}$ 对应的 $k$ 。主函数遍历 $i$ ，调用 `find` 函数获取 $k$ ，计算并更新最大能量转换效率。

- **作者：梦应归于何处（5星）**
    - **关键亮点**：表述清晰，先分析出 $j$ 应取 $i + 1$ ，再利用 `upper_bound` 函数进行二分查找，代码简洁。
    - **核心代码片段**：
```cpp
int main() {
    ll n, u;
    cin >> n >> u;
    for (int i = 0; i < n; i++) {
        cin >> e[i];
    }
    double ans = -1e9;
    for (int i = 0; i < n - 2; i++) {
        ll j = i + 1;
        ll k = upper_bound(e, e + n, e[i] + u) - e - 1;
        if (k - i >= 2) {
            ans = max(ans, double(double(e[k] - e[j]) / (e[k] - e[i])));
        }
    }
    if (ans < 0) {
        cout << "-1";
    } else {
        printf("%.12lf", ans);
    }
    return 0;
}
```
    - **核心实现思想**：遍历 $i$ ，确定 $j = i + 1$ ，通过 `upper_bound` 找到满足 $E_{k}-E_{i} \leq U$ 的最大 $E_{k}$ 对应的 $k$ ，计算并更新最大能量转换效率。

### 最优关键思路或技巧
1. **数学分析**：通过数学推理得出当 $i$、$k$ 固定时，$j$ 取 $i + 1$ 能使能量转换效率最大，简化问题。
2. **二分查找**：利用二分查找在满足 $E_{k}-E_{i} \leq U$ 的条件下找到最大的 $E_{k}$ 对应的 $k$ ，优化时间复杂度。

### 可拓展之处
此类题目通常围绕在一定限制条件下，通过数学分析确定某些变量的最优取值，再结合二分查找等算法优化求解。类似套路可应用于在有序序列中寻找满足特定条件的元素组合，以最大化或最小化某个目标函数。

### 推荐题目
1. **P2249 [HNOI2005] 狡猾的商人**：通过前缀和与二分查找判断账本是否存在矛盾。
2. **P1873 砍树**：在有序数组上二分查找满足条件的最大砍伐高度。
3. **P3382 【模板】三分法**：通过三分查找单峰函数的极值，与本题利用二分查找最优值思路类似。 

---
处理用时：50.22秒