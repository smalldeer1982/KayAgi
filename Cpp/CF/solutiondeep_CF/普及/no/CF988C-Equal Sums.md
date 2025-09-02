# 题目信息

# Equal Sums

## 题目描述

You are given $ k $ sequences of integers. The length of the $ i $ -th sequence equals to $ n_i $ .

You have to choose exactly two sequences $ i $ and $ j $ ( $ i \ne j $ ) such that you can remove exactly one element in each of them in such a way that the sum of the changed sequence $ i $ (its length will be equal to $ n_i - 1 $ ) equals to the sum of the changed sequence $ j $ (its length will be equal to $ n_j - 1 $ ).

Note that it's required to remove exactly one element in each of the two chosen sequences.

Assume that the sum of the empty (of the length equals $ 0 $ ) sequence is $ 0 $ .

## 说明/提示

In the first example there are two sequences $ [2, 3, 1, 3, 2] $ and $ [1, 1, 2, 2, 2, 1] $ . You can remove the second element from the first sequence to get $ [2, 1, 3, 2] $ and you can remove the sixth element from the second sequence to get $ [1, 1, 2, 2, 2] $ . The sums of the both resulting sequences equal to $ 8 $ , i.e. the sums are equal.

## 样例 #1

### 输入

```
2
5
2 3 1 3 2
6
1 1 2 2 2 1
```

### 输出

```
YES
2 6
1 2
```

## 样例 #2

### 输入

```
3
1
5
5
1 1 1 1 1
2
2 3
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4
6
2 2 2 2 2 2
5
2 2 2 2 2
3
2 2 2
5
2 2 2 2 2
```

### 输出

```
YES
2 2
4 1
```

# AI分析结果

### 题目翻译

#### 题目描述

给定 $k$ 个整数序列，第 $i$ 个序列的长度为 $n_i$。

你需要选择两个不同的序列 $i$ 和 $j$（$i \ne j$），并从每个序列中删除一个元素，使得修改后的序列 $i$（长度为 $n_i - 1$）的和等于修改后的序列 $j$（长度为 $n_j - 1$）的和。

注意：必须从每个选中的序列中删除一个元素。

假设长度为 $0$ 的空序列的和为 $0$。

#### 输入格式

第一行一个整数 $k$（$2 \le k \le 2 \cdot 10^5$）。

接下来有 $k$ 组数据。

对于第 $i$ 组数据，第一行是一个整数 $n_i$（$1 \le n_i \le 2 \cdot 10^5$），表示这个序列的长度。第二行是 $n_i$ 个整数 $a_{i,1}, a_{i,2}, \dots, a_{i,n_i}$，表示这个序列的元素。每个元素的值在闭区间 $[-10^4, 10^4]$ 内，且每个序列的和不超过 $2 \cdot 10^5$。

#### 输出格式

第一行输出 `YES` 或 `NO`，表示是否有解。

如果有解，接下来两行分别输出两个序列的编号和删除的元素的位置（位置从1开始）。

如果没有解，输出文件无其余内容。

#### 样例解释

样例一：

选取序列1 $[2, 3, 1, 3, 2]$ 和序列2 $[1, 1, 2, 2, 2, 1]$。删除序列1的第2个元素得到 $[2, 1, 3, 2]$，删除序列2的第6个元素得到 $[1, 1, 2, 2, 2]$。两个序列的和都为8，符合题意。

样例二：

无解。

样例三：

选取序列2 $[2, 2, 2, 2, 2]$ 和序列4 $[2, 2, 2, 2, 2]$。删除序列2的第2个元素得到 $[2, 2, 2, 2]$，删除序列4的第1个元素得到 $[2, 2, 2, 2]$。两个序列的和都为8，符合题意。

### 算法分类
枚举、哈希表

### 题解分析与结论

#### 综合分析

所有题解的核心思路都是通过枚举每个序列中删除一个元素后的和，并使用哈希表（`map`）来记录这些和，以便快速查询是否有两个不同的序列可以通过删除一个元素得到相同的和。

#### 关键思路

1. **枚举删除元素**：对于每个序列，计算其总和，然后枚举删除每个元素后的和。
2. **哈希表记录**：使用 `map` 来记录每个和对应的序列编号和删除的元素位置。
3. **快速查询**：在枚举过程中，查询当前和是否已经存在于 `map` 中，如果存在且来自不同的序列，则输出结果。

#### 最优关键思路

- **哈希表的使用**：通过 `map` 快速记录和查询，确保时间复杂度为 $O(N \log N)$，其中 $N$ 是所有序列的总长度。
- **提前终止**：一旦找到符合条件的两个序列，立即输出结果并终止程序，避免不必要的计算。

#### 可拓展之处

- **类似问题**：可以扩展到多个序列或多个删除操作的问题，使用类似的哈希表方法进行快速查询。
- **优化空间**：如果元素范围较小，可以使用数组代替 `map` 来进一步优化空间和时间复杂度。

### 推荐题目

1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)

### 个人心得

- **调试经历**：在实现过程中，需要注意 `map` 的查询和插入操作的正确性，避免重复记录同一个序列的和。
- **踩坑教训**：在枚举删除元素时，确保不会误判同一个序列的不同删除操作，导致错误输出。

### 所选高星题解

#### 题解1：泥土笨笨 (5星)

**关键亮点**：
- 使用 `map` 记录每个和对应的序列编号和删除位置，思路清晰。
- 代码简洁，逻辑明确，易于理解。

**核心代码**：
```cpp
struct Node {
    int s, p;
};
map<int, Node> m;

int main() {
    cin >> k;
    for (int i = 1; i <= k; ++i) {
        sum = 0;
        cin >> n;
        for (int j = 1; j <= n; ++j) {
            cin >> a[j];
            sum += a[j];
        }
        for (int j = 1; j <= n; ++j) {
            int diff = sum - a[j];
            if (m.count(diff) && m[diff].s != i) {
                cout << "YES" << endl;
                cout << m[diff].s << " " << m[diff].p << endl;
                cout << i << " " << j << endl;
                return 0;
            } else {
                m[diff].s = i;
                m[diff].p = j;
            }
        }
    }
    cout << "NO" << endl;
    return 0;
}
```

#### 题解2：Alexxu2024 (4星)

**关键亮点**：
- 使用 `map` 记录和，并提前终止程序，优化了时间复杂度。
- 代码结构清晰，注释详细。

**核心代码**：
```cpp
map<int,pair<int,int> > mp;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int k;
    cin >> k;
    for(int i=1;i<=k;i++){
        int n;
        cin >> n;
        long long sum=0;
        for(int j=1;j<=n;j++){
            cin >> a[j];
            sum+=a[j];
        }
        for(int j=1;j<=n;j++){
            long long presum=sum-a[j];
            if(mp.count(presum)&&mp[presum].first!=i){
                cout << "YES" << endl;
                cout << mp[presum].first << " " << mp[presum].second << endl;
                cout << i << " " << j;
                return 0;
            } else {
                mp[presum]={i,j};
            }
        }
    }
    cout << "NO";
    return 0;
}
```

#### 题解3：xyta (4星)

**关键亮点**：
- 使用多个 `map` 分别记录序列编号、删除位置和是否出现过，逻辑清晰。
- 代码结构合理，易于扩展。

**核心代码**：
```cpp
map<int,int> x;
map<int,int> y;
map<int,bool> z;

int main() {
    bool cmp=false;
    int ans1,ans2,ans3,ans4;
    int k;
    cin>>k;
    for(int i=1;i<=k;i++) {
        int sum=0;
        int n;
        cin>>n;
        for(int j=1;j<=n;j++) {
            cin>>a[j];
            sum+=a[j];
        }
        if(cmp) continue;
        for(int j=1;j<=n;j++) {
            if(!z[sum-a[j]]) {
                z[sum-a[j]]=1;
                x[sum-a[j]]=i;
                y[sum-a[j]]=j;
            } else if(x[sum-a[j]]!=i) {
                cmp=1;
                ans1=x[sum-a[j]];
                ans2=y[sum-a[j]];
                ans3=i;
                ans4=j;
            }
        }
    }
    if(cmp) {
        cout<<"YES"<<endl<<ans1<<" "<<ans2<<endl<<ans3<<" "<<ans4<<endl;
    } else cout<<"NO";
    return 0;
}
```

---
处理用时：51.93秒