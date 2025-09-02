# 题目信息

# Businessmen Problems

## 题目描述

Two famous competing companies ChemForces and TopChemist decided to show their sets of recently discovered chemical elements on an exhibition. However they know that no element should be present in the sets of both companies.

In order to avoid this representatives of both companies decided to make an agreement on the sets the companies should present. The sets should be chosen in the way that maximizes the total income of the companies.

All elements are enumerated with integers. The ChemForces company has discovered $ n $ distinct chemical elements with indices $ a_1, a_2, \ldots, a_n $ , and will get an income of $ x_i $ Berland rubles if the $ i $ -th element from this list is in the set of this company.

The TopChemist company discovered $ m $ distinct chemical elements with indices $ b_1, b_2, \ldots, b_m $ , and it will get an income of $ y_j $ Berland rubles for including the $ j $ -th element from this list to its set.

In other words, the first company can present any subset of elements from $ \{a_1, a_2, \ldots, a_n\} $ (possibly empty subset), the second company can present any subset of elements from $ \{b_1, b_2, \ldots, b_m\} $ (possibly empty subset). There shouldn't be equal elements in the subsets.

Help the representatives select the sets in such a way that no element is presented in both sets and the total income is the maximum possible.

## 说明/提示

In the first example ChemForces can choose the set ( $ 3, 7 $ ), while TopChemist can choose ( $ 1, 2, 4 $ ). This way the total income is $ (10 + 2) + (4 + 4 + 4) = 24 $ .

In the second example ChemForces can choose the only element $ 10^9 $ , while TopChemist can choose ( $ 14, 92, 35 $ ). This way the total income is $ (239) + (15 + 65 + 89) = 408 $ .

## 样例 #1

### 输入

```
3
1 2
7 2
3 10
4
1 4
2 4
3 4
4 4
```

### 输出

```
24
```

## 样例 #2

### 输入

```
1
1000000000 239
3
14 15
92 65
35 89
```

### 输出

```
408
```

# AI分析结果

### 题目翻译
# 商人问题

## 题目描述
两家著名的竞争公司 ChemForces 和 TopChemist 决定在一次展览上展示他们最近发现的化学元素集。然而，他们知道任何元素都不应同时出现在两家公司的集合中。

为了避免这种情况，两家公司的代表决定就公司应展示的集合达成协议。集合的选择方式应使公司的总收入最大化。

所有元素都用整数编号。ChemForces 公司发现了 $n$ 种不同的化学元素，编号为 $a_1, a_2, \ldots, a_n$，如果该列表中的第 $i$ 种元素被包含在该公司的集合中，公司将获得 $x_i$ 伯兰卢布的收入。

TopChemist 公司发现了 $m$ 种不同的化学元素，编号为 $b_1, b_2, \ldots, b_m$，如果将该列表中的第 $j$ 种元素包含在其集合中，公司将获得 $y_j$ 伯兰卢布的收入。

换句话说，第一家公司可以展示 $\{a_1, a_2, \ldots, a_n\}$ 的任何子集（可能是空子集），第二家公司可以展示 $\{b_1, b_2, \ldots, b_m\}$ 的任何子集（可能是空子集）。子集中不应有相同的元素。

帮助代表们选择集合，使得没有元素同时出现在两个集合中，并且总收入尽可能大。

## 说明/提示
在第一个示例中，ChemForces 可以选择集合 $(3, 7)$，而 TopChemist 可以选择 $(1, 2, 4)$。这样，总收入为 $(10 + 2) + (4 + 4 + 4) = 24$。

在第二个示例中，ChemForces 可以选择唯一的元素 $10^9$，而 TopChemist 可以选择 $(14, 92, 35)$。这样，总收入为 $(239) + (15 + 65 + 89) = 408$。

## 样例 #1
### 输入
```
3
1 2
7 2
3 10
4
1 4
2 4
3 4
4 4
```
### 输出
```
24
```

## 样例 #2
### 输入
```
1
1000000000 239
3
14 15
92 65
35 89
```
### 输出
```
408
```

### 算法分类
贪心

### 综合分析与结论
- **思路对比**：
    - YUYGFGG 的题解使用 `map` 记录每个编号的最大价值，最后遍历 `map` 求和，思路简洁直接。
    - LJB00131 先提出暴力法因数据范围不可行，后采用二分法。先对两个数组排序，再在一个数组中查找另一个数组中同编号元素，取价值大的，最后加上只在一个数组中出现的元素价值。
    - Eason_AC 同样使用 `map` 来判断元素是否取过并存储价值，遇到相同编号元素时取价值较大的更新 `map` 和总价值。
- **算法要点**：
    - YUYGFGG 和 Eason_AC 都利用 `map` 的映射特性，简化了元素编号和价值的存储与查找。
    - LJB00131 则是通过排序和二分查找来处理元素编号的匹配。
- **解决难点**：
    - 主要难点在于数据范围大，普通数组无法存储。YUYGFGG 和 Eason_AC 用 `map` 解决，LJB00131 用二分法结合排序解决。

### 题解评分
- YUYGFGG：4星，思路清晰，代码简洁，直接利用 `map` 解决问题。
- LJB00131：3星，思路详细，提出了暴力和二分两种方法，但代码相对复杂。
- Eason_AC：3星，思路和 YUYGFGG 类似，但代码中使用了自定义的输入输出函数，增加了理解成本。

### 所选题解
- YUYGFGG（4星）：关键亮点是使用 `map` 记录每个编号的最大价值，代码简洁易懂。

### 重点代码
```cpp
#include<bits/stdc++.h>
#define fol(i,a,b) for(int i=a;i<=(b);i++)
#define bor(i,a,b) for(int i=a;i>=(b);--i)
#define int long long
using namespace std;
map<int,int> mp;
signed main(){
    int n,m,tmp;
    cin>>n;
    fol(i,1,n){
        cin>>m>>tmp;
        mp[m]=max(mp[m],tmp);
    }
    cin>>n;
    fol(i,1,n){
        cin>>m>>tmp;
        mp[m]=max(mp[m],tmp);
    }
    int sum=0;
    for(map<int,int>::iterator it=mp.begin();it!=mp.end();it++){
        sum+=(*it).second;
    }
    cout<<sum<<endl;
    return 0;
}
```
**核心实现思想**：先输入 ChemForces 公司的元素编号和价值，用 `map` 记录每个编号的最大价值。再输入 TopChemist 公司的元素，同样更新 `map` 中对应编号的最大价值。最后遍历 `map`，将所有最大价值相加得到总收入。

### 可拓展之处
同类型题可能会有更多组元素集合，或者元素有更多属性。类似算法套路可以用 `map` 或排序二分来处理元素编号的匹配和去重问题。

### 推荐洛谷题目
1. P1090 [NOIP2004 提高组] 合并果子：考察贪心算法，与本题贪心选择最大价值元素的思路类似。
2. P1223 排队接水：也是贪心算法的经典题目，通过合理排序来达到最优结果。
3. P1803 凌乱的yyy / 线段覆盖：同样是贪心思想，处理区间覆盖问题。

### 个人心得
本题解中没有包含个人心得内容。

---
处理用时：37.59秒