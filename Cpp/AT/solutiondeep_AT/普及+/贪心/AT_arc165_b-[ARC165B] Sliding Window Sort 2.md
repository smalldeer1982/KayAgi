# 题目信息

# [ARC165B] Sliding Window Sort 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc165/tasks/arc165_b

$ 1 $ から $ N $ までの整数からなる順列 $ P=(P_1,P_2,\dots,P_N) $ と整数 $ K $ が与えられます。

順列 $ P $ に対して以下のような操作を考えます。

- $ 1\ \leq\ i\ \leq\ N-K+1 $ を満たす整数 $ i $ を $ 1 $ つ選び、 $ P_i,P_{i+1},\dots,P_{i+K-1} $ を昇順に並び替える。すなわち、$ P_i,P_{i+1},\dots,P_{i+K-1} $ を小さい方から順に並べたものを $ (x_1,x_2,\dots,x_K) $ としたとき、各 $ 1\ \leq\ j\ \leq\ K $ に対して $ P_{i+j-1} $ を $ x_j $ で置き換える。
 
$ P $ に対して上記の操作をちょうど $ 1 $ 回行うことで得られる順列のうち、辞書式順序最大のものを求めてください。

  数列の辞書順とは？数列 $ S\ =\ (S_1,S_2,\ldots,S_{|S|}) $ が数列 $ T\ =\ (T_1,T_2,\ldots,T_{|T|}) $ より**辞書順で小さい**とは、下記の 1. と 2. のどちらかが成り立つことを言います。 ここで、$ |S|,\ |T| $ はそれぞれ $ S,\ T $ の長さを表します。

1. $ |S|\ \lt\ |T| $ かつ $ (S_1,S_2,\ldots,S_{|S|})\ =\ (T_1,T_2,\ldots,T_{|S|}) $。
2. ある整数 $ 1\ \leq\ i\ \leq\ \min\lbrace\ |S|,\ |T|\ \rbrace $ が存在して、下記の $ 2 $ つがともに成り立つ。 
  - $ (S_1,S_2,\ldots,S_{i-1})\ =\ (T_1,T_2,\ldots,T_{i-1}) $
  - $ S_i $ が $ T_i $ より（数として）小さい。

## 说明/提示

### 制約

- $ 1\ \leq\ K\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ P_i\ \leq\ N $
- $ (P_1,P_2,\dots,P_N) $ は $ 1 $ から $ N $ までの整数からなる順列
- 入力される値はすべて整数
 
### Sample Explanation 1

$ i=1 $ として操作を行うと $ (P_1,P_2,P_3)=(2,1,4) $ であり、これを昇順に並び替えると $ (1,2,4) $ となります。よって操作によって $ P_1,P_2,P_3 $ はそれぞれ $ 1,2,4 $ に置き換えられ、 $ P=(1,2,4,3) $ となります。同様に $ i=2 $ として操作を行うと $ P $ は $ (2,1,3,4) $ となります。 これらのうち辞書式順序で大きいのは $ (2,1,3,4) $ であるため、答えは $ (2,1,3,4) $ となります。

## 样例 #1

### 输入

```
4 3

2 1 4 3```

### 输出

```
2 1 3 4```

## 样例 #2

### 输入

```
5 1

3 1 4 2 5```

### 输出

```
3 1 4 2 5```

## 样例 #3

### 输入

```
20 7

9 4 3 1 11 12 13 15 17 7 2 5 6 20 19 18 8 16 14 10```

### 输出

```
9 4 3 1 11 12 13 15 17 7 2 5 6 8 18 19 20 16 14 10```

# AI分析结果

### 题目内容重写

#### [ARC165B] 滑动窗口排序 2

**题目描述**

给定一个由 $1$ 到 $N$ 的整数组成的排列 $P=(P_1,P_2,\dots,P_N)$ 和一个整数 $K$。

对排列 $P$ 进行如下操作：

- 选择一个满足 $1 \leq i \leq N-K+1$ 的整数 $i$，并将 $P_i,P_{i+1},\dots,P_{i+K-1}$ 按升序排序。即，将 $P_i,P_{i+1},\dots,P_{i+K-1}$ 替换为它们按升序排列后的结果。

要求对 $P$ 进行恰好一次上述操作，得到的所有可能的排列中，字典序最大的那个排列。

**数列的字典序定义**

数列 $S = (S_1,S_2,\ldots,S_{|S|})$ 比数列 $T = (T_1,T_2,\ldots,T_{|T|})$ **字典序更小**，当且仅当以下任一条件成立：

1. $|S| < |T|$ 且 $(S_1,S_2,\ldots,S_{|S|}) = (T_1,T_2,\ldots,T_{|S|})$。
2. 存在整数 $1 \leq i \leq \min\{|S|, |T|\}$，使得：
   - $(S_1,S_2,\ldots,S_{i-1}) = (T_1,T_2,\ldots,T_{i-1})$
   - $S_i < T_i$（数的大小比较）。

**输入输出样例**

**样例 #1**

输入：
```
4 3
2 1 4 3
```
输出：
```
2 1 3 4
```

**样例 #2**

输入：
```
5 1
3 1 4 2 5
```
输出：
```
3 1 4 2 5
```

**样例 #3**

输入：
```
20 7
9 4 3 1 11 12 13 15 17 7 2 5 6 20 19 18 8 16 14 10
```
输出：
```
9 4 3 1 11 12 13 15 17 7 2 5 6 8 18 19 20 16 14 10
```

### 题解综合分析与结论

#### 题解思路对比

1. **EuphoricStar 的题解**：
   - **思路**：首先判断是否存在长度大于等于 $K$ 的递增子段，若存在则直接输出原排列。否则，找到以 $n - k$ 为右端点的最长递增子段，并选择最小的 $l$ 使得排序后不影响前 $n - k$ 个数的顺序。
   - **难点**：如何在不影响前 $n - k$ 个数的情况下，选择最优的排序区间。
   - **评分**：4星。思路清晰，代码简洁，时间复杂度为 $O(n)$。

2. **lzyqwq 的题解**：
   - **思路**：首先判断是否存在长度大于等于 $K$ 的递增子段，若存在则直接输出原排列。否则，选择最靠后的区间 $[n-K+1,n]$ 进行排序，但需要考虑是否可以通过左移区间来优化结果。
   - **难点**：如何在不影响前 $n - k$ 个数的情况下，选择最优的排序区间。
   - **评分**：4星。思路清晰，代码简洁，时间复杂度为 $O(n)$。

3. **stswkl 的题解**：
   - **思路**：使用线段树维护区间最小值，通过二分查找确定排序后第一个变化的位置，选择最优的排序区间。
   - **难点**：如何高效地找到排序后第一个变化的位置。
   - **评分**：4星。思路清晰，代码实现较为复杂，时间复杂度为 $O(n \log n)$。

#### 最优关键思路

- **贪心策略**：在不影响前 $n - k$ 个数的前提下，选择最靠后的区间进行排序，以最大化字典序。
- **数据结构优化**：使用线段树或 ST 表来快速查询区间最小值，优化查找效率。

#### 可拓展之处

- **类似问题**：可以考虑其他类型的排序操作，如降序排序，或者对多个区间进行排序。
- **算法套路**：贪心策略与数据结构的结合，适用于需要在不影响某些部分的情况下进行局部优化的场景。

#### 推荐题目

1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P3372 线段树 1](https://www.luogu.com.cn/problem/P3372)
3. [P3384 线段树 2](https://www.luogu.com.cn/problem/P3384)

#### 个人心得摘录

- **EuphoricStar**：赛时代码赛后被 hack 了，发现对子段排序不会使排列的字典序变大。
- **lzyqwq**：被题目名里的滑动窗口误导了，卡 B 40min。
- **stswkl**：赛时挂了无数发，赛后又被加的数据 hack 了。

### 所选高分题解

#### 1. EuphoricStar 的题解

**星级**：4星  
**关键亮点**：通过贪心策略和预处理区间最小值，高效地找到最优排序区间，代码简洁且时间复杂度为 $O(n)$。

**核心代码**：
```cpp
int n, k, a[N], maxn, pos = 1, lg[N], ans, pre[N];
int main() {
    read(n), read(k); for (int i = 1; i <= n; ++i) read(a[i]), lg[i] = __lg(i);
    for (int i = 1, la, len = 0; i <= n; ++i) {
        if (i == 1 || a[i] > la) ++len; else maxn = max(len, maxn), len = 1;
        la = a[i];
    }
    if (maxn >= k) { for (int i = 1; i <= n; ++i) print(a[i], ' '); return 0; }
    for (int i = n - k, la = N; i >= 1; --i) 
        if (a[i] > la) { pos = i + 1; break; } else la = a[i];
    pre[n - k + 1] = a[ans = n - k + 1];
    for (int i = n - k + 2; i <= n; ++i) pre[i] = min(pre[i - 1], a[i]);
    for (int i = pos; i <= n - k; ++i) 
        if (pre[i + k - 1] > a[n - k]) { ans = i; break; }
    sort(a + ans, a + ans + k); for (int i = 1; i <= n; ++i) print(a[i], ' ');
    return 0;
}
```

#### 2. lzyqwq 的题解

**星级**：4星  
**关键亮点**：通过贪心策略和预处理区间最小值，高效地找到最优排序区间，代码简洁且时间复杂度为 $O(n)$。

**核心代码**：
```cpp
int n, k, a[N], maxn, pos = 1, lg[N], ans, pre[N];
int main() {
    read(n), read(k); for (int i = 1; i <= n; ++i) read(a[i]), lg[i] = __lg(i);
    for (int i = 1, la, len = 0; i <= n; ++i) {
        if (i == 1 || a[i] > la) ++len; else maxn = max(len, maxn), len = 1;
        la = a[i];
    }
    if (maxn >= k) { for (int i = 1; i <= n; ++i) print(a[i], ' '); return 0; }
    for (int i = n - k, la = N; i >= 1; --i) 
        if (a[i] > la) { pos = i + 1; break; } else la = a[i];
    pre[n - k + 1] = a[ans = n - k + 1];
    for (int i = n - k + 2; i <= n; ++i) pre[i] = min(pre[i - 1], a[i]);
    for (int i = pos; i <= n - k; ++i) 
        if (pre[i + k - 1] > a[n - k]) { ans = i; break; }
    sort(a + ans, a + ans + k); for (int i = 1; i <= n; ++i) print(a[i], ' ');
    return 0;
}
```

#### 3. stswkl 的题解

**星级**：4星  
**关键亮点**：使用线段树维护区间最小值，通过二分查找确定排序后第一个变化的位置，选择最优的排序区间，时间复杂度为 $O(n \log n)$。

**核心代码**：
```cpp
class segment_tre {
    private:
        int minn[N<<2];
        void push_up(int id){minn[id]=min(minn[id<<1],minn[id<<1|1]);}
    public:
        void build(int id,int l,int r,int*a) {
            if(l==r)minn[id]=a[l];
            else {
                int mid=l+r>>1;
                build(id<<1,l,mid,a);
                build(id<<1|1,mid+1,r,a);
                push_up(id);
            }
        }
        int query(int id,int l,int r,int x,int y) {
            if(x<=l&&r<=y)return minn[id];
            int mid=l+r>>1,res=inf;
            if(x<=mid)res=min(res,query(id<<1,l,mid,x,y));
            if(y>mid)res=min(res,query(id<<1|1,mid+1,r,x,y));
            return res;
        }
}tree;
int a[N],id[N],r[N];
int find(int L,int R,int val) {
    int l=L-1,r=R+1;
    while(l+1<r) {
        int mid=l+r>>1;
        if(a[mid]<val)l=mid;
        else r=mid;
    }
    return r;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    tree.build(1,1,n,a);
    int tot=1;
    for(int i=1;i<=n;i++) {
        if(a[i-1]>a[i])tot++;
        id[i]=tot;
        r[tot]=i;
    }
    int maxn=0,minx;
    for(int i=1;i+k-1<=n;i++) {
        if(r[id[i]]>=i+k-1) {
            for(int j=1;j<=n;j++)cout<<a[j]<<' ';
            return 0;
        }
        int ret=find(i,r[id[i]],tree.query(1,1,n,r[id[i]]+1,i+k-1));
        if(ret>maxn)maxn=ret,minx=i;
    }
    sort(a+minx,a+minx+k);
    for(int i=1;i<=n;i++)cout<<a[i]<<' ';
    return 0;
}
```

---
处理用时：95.13秒