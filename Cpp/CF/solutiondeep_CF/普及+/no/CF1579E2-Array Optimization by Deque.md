# 题目信息

# Array Optimization by Deque

## 题目描述

In fact, the problems E1 and E2 do not have much in common. You should probably think of them as two separate problems.

You are given an integer array $ a[1 \ldots n] = [a_1, a_2, \ldots, a_n] $ .

Let us consider an empty [deque](https://tinyurl.com/pfeucbux) (double-ended queue). A deque is a data structure that supports adding elements to both the beginning and the end. So, if there are elements $ [3, 4, 4] $ currently in the deque, adding an element $ 1 $ to the beginning will produce the sequence $ [\color{red}{1}, 3, 4, 4] $ , and adding the same element to the end will produce $ [3, 4, 4, \color{red}{1}] $ .

The elements of the array are sequentially added to the initially empty deque, starting with $ a_1 $ and finishing with $ a_n $ . Before adding each element to the deque, you may choose whether to add it to the beginning or to the end.

For example, if we consider an array $ a = [3, 7, 5, 5] $ , one of the possible sequences of actions looks like this:

 $ \quad $ 1.add $ 3 $ to the beginning of the deque:deque has a sequence $ [\color{red}{3}] $ in it; $ \quad $ 2.add $ 7 $ to the end of the deque:deque has a sequence $ [3, \color{red}{7}] $ in it; $ \quad $ 3.add $ 5 $ to the end of the deque:deque has a sequence $ [3, 7, \color{red}{5}] $ in it; $ \quad $ 4.add $ 5 $ to the beginning of the deque:deque has a sequence $ [\color{red}{5}, 3, 7, 5] $ in it;Find the minimal possible number of inversions in the deque after the whole array is processed.

An inversion in sequence $ d $ is a pair of indices $ (i, j) $ such that $ i < j $ and $ d_i > d_j $ . For example, the array $ d = [5, 3, 7, 5] $ has exactly two inversions — $ (1, 2) $ and $ (3, 4) $ , since $ d_1 = 5 > 3 = d_2 $ and $ d_3 = 7 > 5 = d_4 $ .

## 说明/提示

One of the ways to get the sequence $ [5, 3, 7, 5] $ in the deque, containing only two inversions, from the initial array $ [3, 7, 5, 5] $ (the first sample test case) is described in the problem statement.

Also, in this example, you could get the answer of two inversions by simply putting each element of the original array at the end of the deque. In this case, the original sequence $ [3, 7, 5, 5] $ , also containing exactly two inversions, will be in the deque as-is.

## 样例 #1

### 输入

```
6
4
3 7 5 5
3
3 2 1
3
3 1 2
4
-1 2 2 -1
4
4 5 1 3
5
1 3 1 3 2```

### 输出

```
2
0
1
0
1
2```

# AI分析结果

### 题目内容中文重写
实际上，问题 E1 和 E2 并没有太多共同之处。你应该把它们当作两个独立的问题来考虑。

给定一个整数数组 $ a[1 \ldots n] = [a_1, a_2, \ldots, a_n] $ 。

我们考虑一个空的[双端队列](https://tinyurl.com/pfeucbux)（double - ended queue）。双端队列是一种支持在开头和结尾添加元素的数据结构。因此，如果当前双端队列中有元素 $ [3, 4, 4] $ ，在开头添加元素 $ 1 $ 将得到序列 $ [\color{red}{1}, 3, 4, 4] $ ，在结尾添加相同的元素将得到 $ [3, 4, 4, \color{red}{1}] $ 。

数组中的元素按顺序添加到初始为空的双端队列中，从 $ a_1 $ 开始，到 $ a_n $ 结束。在将每个元素添加到双端队列之前，你可以选择将其添加到开头还是结尾。

例如，如果我们考虑数组 $ a = [3, 7, 5, 5] $ ，一种可能的操作序列如下：
1. 将 $ 3 $ 添加到双端队列的开头：双端队列中的序列为 $ [\color{red}{3}] $ ；
2. 将 $ 7 $ 添加到双端队列的结尾：双端队列中的序列为 $ [3, \color{red}{7}] $ ；
3. 将 $ 5 $ 添加到双端队列的结尾：双端队列中的序列为 $ [3, 7, \color{red}{5}] $ ；
4. 将 $ 5 $ 添加到双端队列的开头：双端队列中的序列为 $ [\color{red}{5}, 3, 7, 5] $ ；

求出处理完整个数组后，双端队列中可能的最小逆序对数量。

序列 $ d $ 中的逆序对是指一对索引 $ (i, j) $ ，使得 $ i < j $ 且 $ d_i > d_j $ 。例如，数组 $ d = [5, 3, 7, 5] $ 恰好有两个逆序对 —— $ (1, 2) $ 和 $ (3, 4) $ ，因为 $ d_1 = 5 > 3 = d_2 $ 且 $ d_3 = 7 > 5 = d_4 $ 。

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法，即每次添加元素时，比较将其添加到双端队列队头和队尾产生的逆序对数量，选择产生逆序对数量少的方式。由于数组元素的值域较大，所有题解都采用了离散化来处理。在数据结构的选择上，大部分题解使用树状数组，也有部分使用权值线段树、平衡树或分块来维护序列中比某个数大或小的数的数量。

### 所选题解
- **EternalHeart1314（5星）**
    - **关键亮点**：思路清晰，详细阐述了贪心策略和树状数组的使用，代码注释丰富，可读性高。
    - **个人心得**：无
- **zhaoyp（4星）**
    - **关键亮点**：对问题分析全面，给出了离散化加普通线段树的实现，代码结构清晰。
    - **个人心得**：无
- **npqenqpve（4星）**
    - **关键亮点**：思路简洁明了，代码实现简洁，使用离散化后线段树解决问题。
    - **个人心得**：无

### 重点代码
#### EternalHeart1314 的核心代码
```cpp
// 树状数组添加操作
void add(int x) {
    while(x <= n + 7) {
        ++ c[x];
        x += x & -x;
    }
}
// 树状数组求和操作
int sum(int x) {
    static int s;
    s = 0;
    while(x) {
        s += c[x];
        x -= x & -x;
    }
    return s;
}
// 主函数
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    a[0].se = 1e18;
    cin >> t;
    while(t --) {
        memset(c, 0, sizeof c);
        cin >> n;
        ans = cnt = 0;
        for(int i(1); i <= n; ++ i) {
            cin >> a[i].fi;
            a[i].se = i;
        }
        sort(a + 1, a + n + 1);
        for(int i(1); i <= n; ++ i) {
            mp[a[i].fi] = ++ cnt;
        }
        sort(a + 1, a + n + 1, cmp);
        for(int i(1); i <= n; ++ i) {
            b[i] = mp[a[i].fi];
        }
        for(int i(1); i <= n; ++ i) {
            ans += min(sum(n) - sum(b[i]), sum(b[i] - 1));
            add(b[i]);
        }
        cout << ans << '\n';
    }
    return 0;
}
```
**核心实现思想**：先对数组进行离散化处理，将元素映射到较小的范围内。然后使用树状数组维护每个元素的出现情况，在添加元素时，通过树状数组计算将其添加到队头和队尾产生的逆序对数量，取最小值累加到结果中。

#### zhaoyp 的核心代码
```cpp
// 线段树更新操作
void update(int pos) {
    t[pos].sum = t[pos << 1].sum + t[pos << 1 | 1].sum;
}
// 线段树添加操作
void add(int L, int R, int l, int pos, long long k) {
    if(L > l||R < l)
        return ;
    if(L == R&&L == l) {
        t[pos].sum++;
        return ;
    }
    int mid = (L + R) >> 1;
    add(L, mid, l, pos << 1, k);
    add(mid + 1, R, l, pos << 1 | 1, k);
    update(pos);
}
// 线段树查询操作
void query(int L, int R, int l, int r, int pos) {
    if(L > r||R < l)
        return ;
    if(L >= l&&R <= r) {
        anss += t[pos].sum;
        return ;
    }
    int mid = (L + R) >> 1;
    query(L, mid, l, r, pos << 1);
    query(mid + 1, R, l, r, pos << 1 | 1);
}
// 主处理函数
void work() {
    ans = 0;
    for(int i = 1; i <= n; i++) {
        anss = 0;
        query(1, n, 1, a[i].num - 1, 1);
        long long p = anss;
        anss = 0;
        query(1, n, a[i].num + 1, n, 1);
        ans += min(p, anss);
        add(1, n, a[i].num, 1, 1);
    }
    printf("%lld\n", ans);
}
```
**核心实现思想**：使用离散化加普通线段树来维护序列。在添加元素时，通过线段树查询比该元素小和大的元素数量，选择产生逆序对少的方式，将逆序对数量累加到结果中。

#### npqenqpve 的核心代码
```cpp
// 线段树添加操作
void add(int u, int st, int ed, int id, int k) {
    if(st==ed) {
        t[u]+=k;
        return ;
    }
    int mid=(st+ed)>>1;
    if(mid>=id) add(u*2, st, mid, id, k);
    else add(u*2+1, mid+1, ed, id, k);
    t[u]=t[u*2]+t[u*2+1];
}
// 线段树求和操作
int sum(int u, int st, int ed, int l, int r) {
    if(l<=st&&r>=ed) return t[u];
    if(l>ed||r<st) return 0;
    int mid=(st+ed)>>1;
    return sum(u*2, st, mid, l, r)+sum(u*2+1, mid+1, ed, l, r);
}
// 主函数
signed main() {
    int q; cin>>q;
    while(q--) {
        cin>>n;
        for(int i=1; i<=n; i++) cin>>a[i], b[i]=a[i];
        sort(b+1, b+1+n);
        int len=unique(b+1, b+1+n)-b-1;
        for(int i=1; i<=n; i++) a[i]=lower_bound(b+1, b+1+len, a[i])-b;
        int ans=0;
        memset(t, 0, sizeof(t));
        for(int i=1; i<=n; i++) {
            int cnt1=sum(1, 1, n, a[i]+1, n), cnt2=sum(1, 1, n, 1, a[i]-1);
            ans+=min(cnt1, cnt2);
            add(1, 1, n, a[i], 1);
        }
        cout<<ans<<"\n";
    }
}
```
**核心实现思想**：先对数组进行离散化，然后使用线段树维护序列。在添加元素时，通过线段树查询比该元素大或小的元素数量，选择产生逆序对少的方式，将逆序对数量累加到结果中。

### 最优关键思路或技巧
- **贪心策略**：每次添加元素时，比较将其添加到队头和队尾产生的逆序对数量，选择产生逆序对数量少的方式，因为每次操作对后续操作无后效性。
- **离散化**：由于数组元素的值域较大，使用离散化将元素映射到较小的范围内，便于使用树状数组或线段树等数据结构进行维护。
- **树状数组或线段树**：用于高效地查询序列中比某个数大或小的数的数量，时间复杂度为 $O(\log n)$ 。

### 可拓展之处
同类型题或类似算法套路：
- 涉及双端队列操作的题目，如双端队列的滑动窗口问题。
- 逆序对相关问题，如归并排序求逆序对。
- 贪心算法与数据结构结合的问题，如区间调度问题中使用优先队列优化。

### 推荐洛谷题目
- P1908 逆序对
- P2234 [HNOI2002]营业额统计
- P1972 [SDOI2009]HH的项链

### 个人心得摘录与总结
- **苏联小渣**：在考试时发现了结论但忘了怎么求逆序对，打了个 $O(n^2)$ 的暴力，考完后才推出来。总结是考场上一定要多想。
- **zqh123b**：提醒注意数据范围，$n \le 2 \times 10^5$ 而非 $n \le 10^5$，要开 `long long`，注意 $-10^9 \le a_i \le 10^9$ 需离散化。
- **一铭君一**：写代码时要注意值域需离散化，逆序对数可能爆 `int` 需开 `long long`，多测要清空数据。 

---
处理用时：114.20秒