# 题目信息

# [ROI 2018] Extraction of radium

## 题目背景

译自 [ROI 2018 Day1](https://neerc.ifmo.ru/school/archive/2017-2018.html) T1. [Добыча радия](https://neerc.ifmo.ru/school/archive/2017-2018/ru-olymp-roi-2018-day1.pdf) ([Extraction of radium](http://codeforces.com/gym/102147/problem/A))。 

## 题目描述

给一个 $n\times m$ 的矩阵 $a$，矩阵中的数互不相同。
接下来有 $q$ 次修改，每次修改会将某个值修改为一个更大的值。保证修改后矩阵中的数仍互不相同。
每次修改后，请求出：矩阵中有多少个数，既是它所在行的最大值，又是它所在列的最大值。

## 说明/提示

对于所有数据，$1\leq a(i,j) \leq 10^7$，$1\leq t\leq 10^7$，$1 \leq n,m,q \leq 2 \times 10^5$。

| 子任务编号 | $n,m$ | $q$ |
| :-----------: | :-----------: | :-----------: |
| $1$ | $1 \leq n \times m \leq 100$ | $1 \leq q \leq 100$ |
| $2$ | $1 \leq n \times m \leq 5000$ | $1\leq q \leq 5000$ |
| $3$ | $1 \leq n,m \leq 400$ | $1 \leq q \leq 2 \times 10^5$ |
| $4$ | $1 \leq n \times m \leq 2 \times 10^5$ | $1 \leq q \leq 2 \times 10^5$ |

## 样例 #1

### 输入

```
2 3 3
1 4 3
6 5 2
2 2 9
1 3 5
2 2 10```

### 输出

```
1
2
2```

# AI分析结果

### 综合分析与结论
本题主要是对一个矩阵进行多次修改，每次修改后求矩阵中既是所在行最大值又是所在列最大值的元素个数。各题解思路主要围绕预处理每行每列最大值，然后在每次修改时动态维护答案。

暴力解法是每次修改后遍历整个矩阵，时间复杂度为 $O(nmq)$，只能通过部分数据。正解则是通过维护每行每列的最大值，在修改时只更新相关行和列的最大值及答案，时间复杂度可优化到 $O(nm + q)$ 或 $O(nm + \min(n, m) \cdot q)$。

### 所选题解
- **作者：MornStar（5星）**
    - **关键亮点**：思路清晰，详细分析了修改点时答案的各种变化情况，代码实现简洁明了，时间复杂度为 $O(nm + q)$，能通过所有数据。
    - **核心代码**：
```cpp
int row[200005],col[200005],ma1[200005],ma2[200005],ans;
bool r[200005],c[200005];
// 预处理每行每列最大值及初始答案
for(int i=1;i<=n;i++){
    for(int j=1,k;j<=m;j++){
        cin>>k;
        row[i]=max(row[i],k);
        col[j]=max(col[j],k);
    }
}
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
        if(row[i]==col[j]){
            ans++;
            r[i]=c[j]=1;
            ma1[i]=j;
            ma2[j]=i;
        }
    }
}
// 处理每次修改
for(int i=1;i<=q;i++){
    int cx,cy,val;
    cin>>cx>>cy>>val;
    if(ma1[cx]==cy) ans--;
    if(val>row[cx]){
        row[cx]=val;
        if(r[cx]==1&&ma1[cx]!=cy){
            r[cx]=c[ma1[cx]]=0;
            ma2[ma1[cx]]=0;
            ma1[cx]=0;
            ans--;
        }
    }
    if(val>col[cy]){
        col[cy]=val;
        if(c[cy]==1&&ma2[cy]!=cx){
            c[cy]=r[ma2[cy]]=0;
            ma1[ma2[cy]]=0;
            ma2[cy]=0;
            ans--;
        }
    }
    if(row[cx]==col[cy]){
        ans++;
        r[cx]=c[cy]=1;
        ma1[cx]=cy;
        ma2[cy]=cx;
    }
    cout<<ans<<endl;
}
```
核心实现思想：使用数组 `row` 和 `col` 维护每行每列的最大值，`ma1` 和 `ma2` 记录满足条件的点的行列信息，`r` 和 `c` 标记该行或列是否有满足条件的点。在每次修改时，根据修改点的情况更新最大值和答案。

- **作者：zzy0618（4星）**
    - **关键亮点**：思路清晰，对修改点时的情况进行了分类讨论，代码简洁，时间复杂度为 $O(nm + q)$。
    - **核心代码**：
```cpp
const int N = 200005;
int n, m, q, ans;
int mx[N], my[N];
int w[N], r[N];
// 预处理 mx，my
for (i = 1; i <= n; i++) {
    for (j = 1; j <= m; j++) {
        cin >> t;
        mx[i] = max(mx[i], t);
        my[j] = max(my[j], t);
    }
}
// 预处理 ans，w，r
for (i = 1; i <= n; i++)
    for (j = 1; j <= m; j++)
        if (mx[i] == my[j])
            ans++, w[i] = j, r[j] = i;
// 处理每次修改
while (q--) {
    cin >> x >> y >> t;
    if (w[x] == y)
        ans--;
    if (t > mx[x]) {
        mx[x] = t;
        if (w[x]!= y && w[x]!= 0)
            w[x] = r[w[x]] = 0, ans--;
    }
    if (t > my[y]) {
        my[y] = t;
        if (r[y]!= x && r[y]!= 0)
            r[y] = w[r[y]] = 0, ans--;
    }
    if (mx[x] == my[y])
        ans++, w[x] = y, r[y] = x;
    cout << ans << '\n';
}
```
核心实现思想：使用 `mx` 和 `my` 数组维护每行每列的最大值，`w` 和 `r` 数组记录满足条件的点的行列信息。在每次修改时，根据修改点的情况更新最大值和答案。

- **作者：Cure_Wing（4星）**
    - **关键亮点**：提出了将长度更长的数组插入桶，用长度更短的数组查询的优化思路，时间复杂度为 $O(nm + \min\{n, m\} \cdot q)$。
    - **核心代码**：
```cpp
constexpr int N=200005,M=10000007;
int n,m,q,b,x,y,t,l[N],r[N],c[M];
std::vector<int>a[N];
// 预处理每行每列最大值
for(int i=1;i<=n;++i){
    for(int j=1;j<=m;++j){
        cin>>b;
        a[i].push_back(b);
        l[i]=std::max(l[i],b);
    }
}
for(int i=1;i<=m;++i)
    for(int j=1;j<=n;++j)
        r[i]=std::max(a[j][i],r[i]);
// 处理每次修改
if(n<=m){
    for(int i=1;i<=m;++i) ++c[r[i]];
    for(int i=1;i<=q;++i){
        cin>>x>>y>>t;
        l[x]=std::max(l[x],t);
        --c[r[y]];
        r[y]=std::max(r[y],t);
        ++c[r[y]];
        int ans=0;
        for(int j=1;j<=n;++j)
            if(c[l[j]])
                ++ans;
        cout<<ans<<'\n';
    }
}else{
    for(int i=1;i<=n;++i) ++c[l[i]];
    for(int i=1;i<=q;++i){
        cin>>x>>y>>t;
        r[y]=std::max(r[y],t);
        --c[l[x]];
        l[x]=std::max(l[x],t);
        ++c[l[x]];
        int ans=0;
        for(int j=1;j<=m;++j)
            if(c[r[j]])
                ++ans;
        cout<<ans<<'\n';
    }
}
```
核心实现思想：使用 `l` 和 `r` 数组维护每行每列的最大值，`c` 数组作为桶。根据 `n` 和 `m` 的大小关系，将较长的数组插入桶，用较短的数组查询，更新答案。

### 最优关键思路或技巧
- 维护每行每列的最大值，在修改时只更新相关行和列的最大值，减少不必要的遍历。
- 利用“一行（列）中满足要求的点最多只有一个”这一性质，通过标记和记录满足条件的点的行列信息，快速更新答案。
- 将长度更长的数组插入桶，用长度更短的数组查询，降低时间复杂度。

### 可拓展之处
同类型题可能会有更多维度的矩阵修改和查询问题，或者修改规则更加复杂。类似算法套路可以应用于需要动态维护矩阵中某些元素性质的问题，关键在于找到修改操作对整体结果的影响规律，通过预处理和动态更新来优化时间复杂度。

### 推荐题目
- P1168 中位数：维护序列并动态查询中位数，可使用堆等数据结构动态维护。
- P2088 烤鸡：对组合问题进行动态修改和计数，与本题动态维护答案的思想类似。
- P1090 合并果子：每次合并果子会改变序列状态，需要动态维护最小代价，可使用优先队列优化。

### 个人心得摘录与总结
- **作者：pjx0106**：最初代码在判断修改是否影响原最大值时，对每一行都进行了循环，复杂度为 $O(n^2)$ 导致只能拿到 86 分。后来通过只枚举有最大值的行，降低了实际复杂度，从而通过了题目。总结：在编写代码时要注意循环的范围，避免不必要的计算，降低时间复杂度。 

---
处理用时：50.63秒