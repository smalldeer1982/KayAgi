# 题目信息

# [ABC036C] 座圧

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc036/tasks/abc036_c

# AI分析结果

【题目内容翻译】
# [ABC036C] 座圧

## 题目描述

给定一个长度为 $n$ 的数组 $a$，要求对其进行离散化处理，输出离散化后的数组 $b$。

【算法分类】
离散化

【题解分析与总结】
本题的核心是离散化处理，即将原始数据映射到较小的范围内，同时保持数据的相对顺序不变。以下是各题解的要点对比：

1. **cff_0102** 的题解：
   - 使用 `sort` 和 `unique` 进行排序和去重，然后通过 `lower_bound` 查找离散化后的值。
   - 代码简洁，思路清晰，适合初学者理解离散化的基本流程。
   - 评分：4星

2. **a1ioua** 的题解：
   - 同样使用 `sort` 和 `unique` 进行排序和去重，并通过 `lower_bound` 查找离散化后的值。
   - 代码结构清晰，使用了快读快写优化输入输出。
   - 评分：4星

3. **heaksicn** 的题解：
   - 使用结构体存储原始数据和索引，排序后手动进行离散化处理。
   - 代码逻辑清晰，适合理解离散化的手动实现过程。
   - 评分：4星

【最优关键思路】
- 使用 `sort` 和 `unique` 进行排序和去重，然后通过 `lower_bound` 查找离散化后的值。这种方法简洁高效，适合大多数离散化场景。

【可拓展之处】
- 离散化常用于处理值域较大的数据，如统计频数、区间查询等。类似的问题可以在洛谷上找到，如 P1908 逆序对、P1972 [SDOI2009]HH的项链、P3369 【模板】普通平衡树。

【推荐题目】
1. P1908 逆序对
2. P1972 [SDOI2009]HH的项链
3. P3369 【模板】普通平衡树

【个人心得摘录】
- **cff_0102**：通过 `lower_bound` 查找离散化后的值，注意要减去起始地址以得到正确的索引。
- **a1ioua**：使用快读快写优化输入输出，提升代码效率。
- **heaksicn**：手动进行离散化处理，适合理解离散化的底层逻辑。

【核心代码片段】
```cpp
// cff_0102 的核心代码
sort(a.begin()+1, a.end());
a.erase(unique(a.begin()+1, a.end()), a.end());
for(int i=1;i<=n;i++){
    int t=lower_bound(a.begin()+1, a.end(), b[i])-a.begin()-1;
    cout<<t<<endl;
}
```

```cpp
// a1ioua 的核心代码
sort(a + 1, a + n + 1);
for (int i = 1; i <= n; i++)
    if (i == 1 || a[i] != a[i - 1])
        b[++cnt] = a[i];
for (int i = 1; i <= n; i++) {
    write(f(c[i]));
    putchar('\n');
}
```

```cpp
// heaksicn 的核心代码
sort(a+1,a+n+1,cmp);
int now=0,lst=a[1].x;
a[1].x=0;
for(int i=2;i<=n;i++){
    if(a[i].x==lst) a[i].x=now;
    else a[i].x=++now;
    lst=a[i].x;
}
sort(a+1,a+n+1,cmp2);
for(int i=1;i<=n;i++){
    cout<<a[i].x<<endl;
}
```

---
处理用时：26.83秒