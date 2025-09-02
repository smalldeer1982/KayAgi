# 题目信息

# Recommendations

## 题目描述

有 $n$ 个区间 $S_i=[l_i,r_i]$，对于每个区间求出 $|\bigcap\limits_{j} S_j|-|S_i|$，其中 $j\neq i$，且 $S_i\subseteq S_j$。即对于每个区间求出其包区间交集的大小，并减去自己的大小。

## 样例 #1

### 输入

```
4
3
3 8
2 5
4 5
2
42 42
1 1000000000
3
42 42
1 1000000000
42 42
6
1 10
3 10
3 7
5 7
4 4
1 2```

### 输出

```
0
0
1
999999999
0
0
0
0
0
2
3
2
4
8```

# AI分析结果

### 题目翻译
本题题目内容已是中文，无需翻译。

### 综合分析与结论
这些题解的核心目标都是求解每个区间的包区间交集大小减去自身区间大小。不同题解在思路和实现上各有特点，但整体可分为以下几类：
- **排序 + 集合操作**：如 Hide_In_The_Shadow、Eddie08012025、Austin0116、lyxxys、SuyctidohanQ 的题解，通过对区间按左端点或右端点排序，再利用 `set` 或 `multiset` 来查找满足条件的最大左端点和最小右端点。
- **线段树或树状数组**：SilverLi、lovely_nst、Arrtan_73、Guchenxi0971 的题解使用线段树或树状数组来维护区间信息，实现前缀最值查询和单点修改。
- **扫描线思想**：lovely_nst、Guchenxi0971 运用扫描线思想，按特定顺序遍历区间，结合数据结构求解。

难点主要在于如何高效地找到每个区间的包区间，并准确计算其交集。不同方法在处理区间重叠、离散化等细节上也有不同的技巧。

### 评分较高的题解
- **Hide_In_The_Shadow（5星）**
    - **关键亮点**：思路清晰，代码实现简洁，使用 `multiset` 方便地处理了区间的排序和查找，时间复杂度为 $O(n\log(n))$。
    - **核心代码**：
```c++
sort(a + 1, a + n + 1, cmp0);
s.clear();
int pre = 0;
for (int i = 1; i <= n; ++i) {
    pre = i;
    s.insert(a[i].r);
    while (i + 1 <= n && a[i + 1].l == a[i].l) s.insert(a[++i].r);
    for (int j = pre; j <= i; ++j) {
        auto it = s.lower_bound(a[j].r);
        it++;
        if (it!= s.end()) r[a[j].id] = *it;
        else r[a[j].id] = -1;
    }
}
```
- **Eddie08012025（4星）**
    - **关键亮点**：详细阐述了思路，通过排序和 `set` 的二分查找，分别处理最大左端点和最小右端点，代码逻辑清晰。
    - **核心代码**：
```cpp
sort(z + 1, z + n + 1, cmd);
sort(p + 1, p + n + 1, cmp);
set<int> s;
set<int, greater<int> > s1;
for (int i = 1; i <= n; i++) {
    auto a = s.lower_bound(z[i].second);
    rmn[mp[z[i]]] = *a;
    s.insert(z[i].second);
}
for (int i = 1; i <= n; i++) {
    auto a = s1.lower_bound(p[i].second);
    lmx[mp[p[i]]] = *a;
    s1.insert(p[i].second);
}
```
- **lyxxys（4星）**
    - **关键亮点**：结合 `set` 和树状数组，分别维护最小右端点和最大左端点，复杂度分析清晰，对区间重叠情况进行了处理。
    - **核心代码**：
```cpp
sort(segs.begin(), segs.end(), [&](auto &u, auto &v) {
    return u[0] == v[0]? u[1] > v[1] : u[0] < v[0];
});
vector <int> ans(n);
set <int> st;
for (int i = 0; i < n; ++i) {
    auto &[l, r, id] = segs[i];
    int L = -1, R = inf;
    if (i < n - 1 && segs[i + 1][0] == l && segs[i + 1][1] == r) {
        st.insert(r);
        Y.update(mps[r], l);
    }
    auto it = st.lower_bound(r);
    if (it!= st.end()) R = *it;
    L = Y.query(mps[r]);
    if (R!= inf && L!= -1) {
        ans[id] += l - L + R - r;
    }
    st.insert(r);
    Y.update(mps[r], l);
}
```

### 最优关键思路或技巧
- **排序策略**：合理的排序（如按左端点升序、右端点降序）能让区间的包区间集中在特定位置，便于后续查找。
- **数据结构运用**：`set` 或 `multiset` 可利用其有序性进行二分查找，线段树和树状数组能高效实现前缀最值查询和单点修改。
- **离散化处理**：当数据范围较大时，离散化可将数据映射到较小的区间，减少空间和时间复杂度。

### 拓展思路
同类型题可涉及区间覆盖、区间合并等问题，类似算法套路包括扫描线、排序 + 数据结构等。例如，计算多个区间的并集长度、求区间的最大重叠部分等。

### 洛谷相似题目推荐
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：可使用树状数组求解，与本题中树状数组的运用有相似之处。
- [P3372 线段树 1](https://www.luogu.com.cn/problem/P3372)：经典的线段树题目，可加深对线段树的理解和运用。
- [P2163 [SHOI2007]园丁的烦恼](https://www.luogu.com.cn/problem/P2163)：涉及二维平面上的点查询问题，可使用扫描线和树状数组解决。

### 个人心得摘录与总结
Hide_In_The_Shadow 提到被 C 卡太久导致没写出来，说明在解题过程中可能遇到了时间或空间复杂度的瓶颈，需要不断优化算法和代码实现。这提醒我们在解题时要注意复杂度分析，及时调整思路。 

---
处理用时：35.24秒