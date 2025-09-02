# 题目信息

# Preprefix sum

## 题目描述

前缀和（prefix sum）$S_i=\sum_{k=1}^i a_k$。

前前缀和（preprefix sum）则把 $S_i$ 作为原序列再进行前缀和。记再次求得前缀和第 $i$ 个是 $SS_i$。

给一个长度 $n$ 的序列 $a_1, a_2, \cdots, a_n$，有两种操作：

1. `Modify i x`：把 $a_i$ 改成 $x$。
2. `Query i`：查询 $SS_i$。


## 说明/提示

$1\le N,M\le 10^5$，且在任意时刻 $0\le A_i\le 10^5$。

## 样例 #1

### 输入

```
5 3
1 2 3 4 5
Query 5
Modify 3 2
Query 5```

### 输出

```
35
32```

# AI分析结果

这道题要求实现对序列的两种操作：单点修改和查询前前缀和。题解主要使用了树状数组、线段树和分块三种数据结构来解决问题。
1. **树状数组**：通过化简前前缀和公式\(\sum_{i=1}^{k}\sum_{j=1}^{i}a_j\)，得到\((k + 1)\sum_{i=1}^{k} a_i - \sum_{i=1}^{k}i\times a_i\)，然后用两个树状数组分别维护\(\sum_{i=1}^{k} a_i\)和\(\sum_{i=1}^{k}i\times a_i\)，从而实现快速查询和修改。
2. **线段树**：用线段树维护序列的前缀和，修改操作变为对前缀和数组的后缀区间加，查询操作则是求前缀和的前缀和，即区间求和。
3. **分块**：对前缀和进行分块预处理，修改时分别处理所在块和后续块，查询时累加所在块之前的块的和以及所在块内的部分和。

综合来看，树状数组和线段树的时间复杂度较低，适合大数据规模；分块的代码相对简单，但时间复杂度较高。以下是对各题解的评分：
1. **作者Leianha**：思路清晰，详细推导公式并给出代码，代码注释较全。**4星**
2. **作者Hexarhy**：不仅给出树状数组解法，还提及线段树做法，对细节有提示。**4星**
3. **作者SuperJvRuo**：推导过程和代码实现完整，但思路阐述相对简略。**3星**
4. **作者xieyi0408**：分块解法思路和代码清晰，但相比其他解法效率较低。**3星**
5. **作者Warriors_Cat**：线段树解法思路清晰，代码有详细注释。**4星**
6. **作者Ccliang**：从差分角度分析，给出线段树解法和代码，但代码注释较少。**3星**
7. **作者Poetic_Rain**：详细推导公式并给出树状数组代码，还拓展区间修改查询知识。**4星**
8. **作者DYan_Hyaena**：从差分和线段树角度解题，代码结构清晰。**4星**
9. **作者feicheng**：线段树解法思路清晰，代码简洁。**4星**
10. **作者Durancer**：推导公式并给出树状数组代码，代码有注释。**3星**
11. **作者AubRain**：线段树解法代码简洁，思路阐述清晰。**4星**
12. **作者顾z**：从差分和树状数组角度解题，代码有注释但思路阐述较简略。**3星**
13. **作者Zxsoul**：线段树解法思路和代码较清晰，但代码稍冗长。**3星**
14. **作者Na2PtCl6**：用树状数组和线段树结合解题，代码较长且注释少。**3星**
15. **作者Suuon_Kanderu**：线段树解法思路清晰，代码封装性好。**3星**
16. **作者那一条变阻器**：线段树解法思路清晰，代码有注释。**3星**
17. **作者rediserver**：从差分和树状数组角度解题，代码有注释。**3星**
18. **作者Patrickpwq**：树状数组解法思路清晰，代码简洁。**3星**
19. **作者封禁用户**：线段树解法代码较简洁，但思路阐述少。**3星**
20. **作者Arghariza**：线段树解法思路清晰，代码有注释。**3星**

评分较高（≥4星）的题解：
1. **作者Leianha**：
    - **星级**：4星
    - **关键亮点**：详细推导前前缀和公式，清晰展示树状数组维护思路与代码实现。
    - **核心代码**：
```cpp
void add1(int pos, int x)
{
    for (int i = pos; i <= (N << 1); i += lowbit(i)) tr1[i] += x;
}
void add2(int pos, int x)
{
    for (int i = pos; i <= (N << 1); i += lowbit(i)) tr2[i] += x;
}
int ask1(int pos)
{
    int lin = 0;
    for (int i = pos; i; i -= lowbit(i)) lin += tr1[i];
    return lin;
}
int ask2(int pos)
{
    int lin = 0;
    for (int i = pos; i; i -= lowbit(i)) lin += tr2[i];
    return lin;
}
signed main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        a[i] = read();
        add1(i, a[i]); add2(i, a[i] * i);
    }
    while (m--)
    {
        scanf("%s", s + 1);
        if (s[1] == 'Q')
        {
            x = read();
            ans = ((x + 1) * ask1(x) - ask2(x));
            printf("%lld\n", ans);
        }
        else
        {
            x = read(); y = read();
            add1(x, y - a[x]); add2(x, (y - a[x]) * x);
            a[x] = y;
        }
    }
    return 0;
}
```
    - **核心思想**：`add1`和`add2`函数分别用于更新两个树状数组，`ask1`和`ask2`用于查询。在`main`函数中，初始化时将原数组值及对应乘积加入树状数组，查询时根据推导公式计算前前缀和，修改时更新树状数组及原数组。
2. **作者Hexarhy**：
    - **星级**：4星
    - **关键亮点**：除树状数组解法外，还提及线段树做法，并对细节如数据类型、修改原数组等有提示。
    - **核心代码**：
```cpp
class BIT//模板
{
private:
    ll tree[MAXN];
    ll lowbit(const ll x){return x&(-x);}
public:
    void modify(ll pos, const ll x)
    {
        for (; pos <= n; pos += lowbit(pos))
            tree[pos] += x;
    }
    ll query(ll pos)
    {
        ll res = 0;
        for (; pos; pos -= lowbit(pos))
            res += tree[pos];
        return res; 
    }
}t1,t2;
int main()
{
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    for (ll i = 1; i <= n; i++)
        cin >> a[i];
    for (ll i = 1; i <= n; i++)
    {
        t1.modify(i, a[i]);
        t2.modify(i, a[i] * i);
    } 
    while (m--)
    {
        string s; cin >> s;
        if (s == "Modify")
        {
            ll pos, x; cin >> pos >> x;
            t1.modify(pos, x - a[pos]);
            t2.modify(pos, (x - a[pos]) * pos);
            a[pos] = x;
        }
        if (s == "Query")
        {
            ll pos; cin >> pos;
            cout << ((pos + 1) * t1.query(pos) - t2.query(pos)) << endl;
        }
    }
    return 0;
}
```
    - **核心思想**：定义`BIT`类封装树状数组操作，`modify`函数更新数组，`query`函数查询。在`main`函数中，初始化时将原数组值及对应乘积加入树状数组，查询时根据公式计算前前缀和，修改时更新树状数组及原数组。
3. **作者Warriors_Cat**：
    - **星级**：4星
    - **关键亮点**：线段树解法思路清晰，代码注释详细，对修改操作中计算原`a_i`值有独特方法。
    - **核心代码**：
```cpp
inline void pushup(int p){d[p] = d[p << 1] + d[p << 1 | 1];}
inline void pushdown(int p, int l, int r)
{
    if (f[p])
    {
        int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1;
        d[ls] += f[p] * (mid - l + 1);
        d[rs] += f[p] * (r - mid);
        f[ls] += f[p]; f[rs] += f[p]; f[p] = 0;
    }
}
inline void build(int p, int l, int r)
{
    if (l == r){d[p] = a[l]; return;}
    int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1;
    build(ls, l, mid); build(rs, mid + 1, r);
    pushup(p);
}
inline void change(int p, int l, int r, int x, int y, int z)
{
    if (x <= l && r <= y)
    {
        d[p] += (r - l + 1) * z;
        f[p] += z;
        return;
    }
    pushdown(p, l, r);
    int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1;
    if (x <= mid) change(ls, l, mid, x, y, z);
    if (y > mid) change(rs, mid + 1, r, x, y, z);
    pushup(p); 
}
inline int query(int p, int l, int r, int x, int y)
{
    if (x <= l && r <= y) return d[p];
    pushdown(p, l, r);
    int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1, ans = 0;
    if (x <= mid) ans += query(ls, l, mid, x, y);
    if (y > mid) ans += query(rs, mid + 1, r, x, y);
    return ans;
}
signed main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%lld", a + i), a[i] += a[i - 1];
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%s", s + 1);
        if (s[1] == 'M')
        {
            scanf("%lld%lld", &x, &y);
            int X;
            if (x == 1) X = query(1, 1, n, 1, 1);
            else if (x == 2) X = query(1, 1, n, 1, 2) - (query(1, 1, n, 1, 1) << 1);
            else X = query(1, 1, n, 1, x) + query(1, 1, n, 1, x - 2) - (query(1,1, n, 1, x - 1) << 1);
            change(1, 1, n, x, n, y - X);
        }
        else
        {
            scanf("%lld", &x);
            printf("%lld\n", query(1, 1, n, 1, x));
        }
    }
    return 0;
}
```
    - **核心思想**：通过线段树的标准操作`pushup`、`pushdown`、`build`、`change`和`query`维护前缀和数组。在`main`函数中，先初始化前缀和数组并建树，查询时直接调用`query`，修改时先计算原`a_i`值，再调用`change`进行区间修改。

**最优关键思路或技巧**：
1. **数学推导优化**：通过对前前缀和公式的化简，将\(O(n^2)\)的计算复杂度优化为可通过树状数组\(O(\log n)\)维护，大大提高效率。
2. **数据结构选择**：根据题目操作特点，选择树状数组或线段树。树状数组代码相对简洁，线段树更灵活通用，都能高效解决单点修改和区间查询问题。

**可拓展之处**：
1. **同类型题**：涉及前缀和、差分及动态修改查询的题目，如维护多维数组的前缀和并支持动态操作。
2. **类似算法套路**：对于具有区间修改、区间查询特征的问题，可考虑树状数组、线段树或分块；通过数学推导化简公式，将复杂问题转化为可高效维护的形式。

**相似知识点洛谷题目**：
1. **P3372 【模板】线段树 1**：基础线段树区间修改、单点查询题目，帮助巩固线段树基本操作。
2. **P3368 【模板】树状数组 2**：树状数组区间修改、区间查询模板题，加深对树状数组应用理解。
3. **P1972 [SDOI2009]HH的项链**：结合树状数组和离散化解决区间不同颜色数查询问题，拓展树状数组应用场景。

**个人心得摘录与总结**：
1. **不开long long见祖宗**：多位作者提到，由于数据范围，需使用`long long`类型避免溢出错误。
2. **公式推导重要性**：通过推导前前缀和公式，将复杂计算转化为可由树状数组或线段树高效维护的形式，强调数学推导在算法优化中的作用。
3. **细节处理**：如修改操作时不仅要更新数据结构，还要修改原数组；线段树操作中懒标记的正确使用和下传等，细节处理不当易导致错误。 

---
处理用时：95.91秒