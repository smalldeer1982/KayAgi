# 题目信息

# R2D2 and Droid Army

## 题目描述

An army of $ n $ droids is lined up in one row. Each droid is described by $ m $ integers $ a_{1},a_{2},...,a_{m} $ , where $ a_{i} $ is the number of details of the $ i $ -th type in this droid's mechanism. R2-D2 wants to destroy the sequence of consecutive droids of maximum length. He has $ m $ weapons, the $ i $ -th weapon can affect all the droids in the army by destroying one detail of the $ i $ -th type (if the droid doesn't have details of this type, nothing happens to it).

A droid is considered to be destroyed when all of its details are destroyed. R2-D2 can make at most $ k $ shots. How many shots from the weapon of what type should R2-D2 make to destroy the sequence of consecutive droids of maximum length?

## 说明/提示

In the first test the second, third and fourth droids will be destroyed.

In the second test the first and second droids will be destroyed.

## 样例 #1

### 输入

```
5 2 4
4 0
1 2
2 1
0 2
1 3
```

### 输出

```
2 2
```

## 样例 #2

### 输入

```
3 2 4
1 2
1 3
2 2
```

### 输出

```
1 3
```

# AI分析结果

### 题目内容
#### R2D2和机器人军队
#### 题目描述
有一支由$n$个机器人组成的队伍排成一行。每个机器人由$m$个整数$a_{1},a_{2},\ldots,a_{m}$描述，其中$a_{i}$是该机器人机械装置中第$i$种零件的数量。R2 - D2想要摧毁最长的连续机器人序列。它有$m$种武器，第$i$种武器可以通过摧毁第$i$种零件（如果机器人没有这种零件，则对其无影响）来影响军队中的所有机器人。
当一个机器人的所有零件都被摧毁时，该机器人被视为被摧毁。R2 - D2最多可以射击$k$次。R2 - D2应该从每种类型的武器中射击多少次才能摧毁最长的连续机器人序列？
#### 说明/提示
在第一个测试用例中，第二个、第三个和第四个机器人将被摧毁。
在第二个测试用例中，第一个和第二个机器人将被摧毁。
#### 样例 #1
**输入**
```
5 2 4
4 0
1 2
2 1
0 2
1 3
```
**输出**
```
2 2
```
#### 样例 #2
**输入**
```
3 2 4
1 2
1 3
2 2
```
**输出**
```
1 3
```

### 算法分类
二分、双指针

### 综合分析与结论
这些题解主要围绕如何找到满足条件的最长连续机器人区间展开。核心思路是将问题转化为寻找一个区间，使得区间内每种零件类型的最大值之和小于等于$k$。
 - **思路方面**：多数题解利用了区间端点移动时，区间内零件最大值之和的单调性。如固定右端点右移，左端点也会右移，或者固定左端点，右端点具有单调性。
 - **算法要点**：常见方法有二分查找、双指针法，配合数据结构如单调队列、ST表、线段树来维护区间最大值。
 - **解决难点**：难点在于如何高效地计算和维护区间内每种零件类型的最大值，以及利用这些值的单调性来优化查找过程。

### 所选的题解
- **作者：QwQcOrZ（5星）**
  - **关键亮点**：思路清晰，采用双指针法，用单调队列优化找最大值过程，时间复杂度为$O(nm)$，代码简洁高效。
  - **个人心得**：无
  - **核心代码**：
```cpp
int calc(int m)
{
    int ret = 0;
    for (int i = 1; i <= m; i++) ret += a[q[i][h[i]]][i];
    return ret;
}
signed main()
{
    int n = read(), m = read(), k = read(), Max = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) a[i][j] = read();
    for (int j = 1; j <= m; j++) h[j] = 1, t[j] = 0;
    for (int l = 1, r = 1; r <= n; r++)
    {
        for (int i = 1; i <= m; i++)
        {
            while (h[i] <= t[i] && a[q[i][t[i]]][i] <= a[r][i]) t[i]--;
            q[i][++t[i]] = r;
        }
        while (l <= r && calc(m) > k)
        {
            l++;
            for (int i = 1; i <= m; i++)
                if (q[i][h[i]] < l)
                    h[i]++;
        }
        if (r - l + 1 > Max)
        {
            Max = r - l + 1;
            for (int i = 1; i <= m; i++) ans[i] = a[q[i][h[i]]][i];
        }
    }
    for (int i = 1; i <= m; i++) print(ans[i],'');
    return 0;
}
```
  - **核心实现思想**：`calc`函数计算当前区间内每种零件类型最大值之和。主函数中，通过双指针移动区间，右端点右移时，用单调队列更新每种零件类型的最大值；左端点右移时，调整单调队列保证区间合法，同时记录最大区间长度及对应每种零件类型的最大值。
- **作者：hank0402（4星）**
  - **关键亮点**：利用双指针法和ST表，分析出在右端点右移过程中最优左端点的移动规律，优化了枚举过程，时间复杂度为$O(n \log n)$。
  - **个人心得**：无
  - **核心代码**：
```cpp
int query(int l, int r) { 
    int qans = 0, k = LOG[r - l + 1];
    for(int i = 1; i <= m; ++i) {
        qans += max(f[i][l][k], f[i][r - (1 << k) + 1][k]);
    }
    return qans;
}
void update(int l, int r) { 
    int k = LOG[r - l + 1];
    vector<int> _new;
    for(int i = 1; i <= m; ++i) {
        _new.push_back(max(f[i][l][k], f[i][r - (1 << k) + 1][k]));
    }
    A = _new;
}
signed main() {
    n = read(), m = read(), k = read();
    LOG[1] = 0;
    for(int i = 0; i < m; ++i) A.push_back(0); 
    for(int i = 2; i <= n; ++i) LOG[i] = LOG[i >> 1] + 1; 
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            f[j][i][0] = read();
        }
    }
    for(int p = 1; p <= m; ++p) {
        for(int j = 1; (1 << j) <= n; ++j) {
            for(int i = 1; i + (1 << j) - 1 <= n; ++i) {
                f[p][i][j] = max(f[p][i][j - 1], f[p][i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int pl = 1;
    for(int i = 1; i <= n; ++i) {
        while(pl <= i && query(pl, i) > k) pl ++; 
        if(i - pl + 1 > ans) {
            update(pl, i);
            ans = i - pl + 1;
        }
    }
    for(int i : A) {
        cout << i << ' ';
    }
    return 0;
}
```
  - **核心实现思想**：`query`函数利用ST表计算区间$[l,r]$内每种零件类型最大值之和。`update`函数记录当前区间每种零件类型的最大值。主函数中，先预处理ST表，然后通过双指针移动区间，保证区间合法并更新最大区间长度及对应每种零件类型的最大值。
- **作者：_Felix（4星）**
  - **关键亮点**：采用二分法确定连续人数，用单调队列求区间最大值，思路简洁明了，时间复杂度为$O(n \log n)$。
  - **个人心得**：无
  - **核心代码**：
```cpp
int check(int len){
    rep(i,1,m) hd[i]=1,tl[i]=0;
    int q[M][N];memset(q,0,sizeof(q));
    int p[M][N];memset(p,0,sizeof(p));
    rep(i,1,n){
        LL sum = 0;
        rep(j,1,m){
            while(hd[j]<=tl[j]&&q[j][tl[j]]<=a[i][j]) tl[j]--;
            q[j][++tl[j]]=a[i][j],p[j][tl[j]]=i;
            while(hd[j]<=tl[j]&&p[j][hd[j]]<=i-len) hd[j]++;
            if(i>=len) sum+=q[j][hd[j]],maxx[j]=q[j][hd[j]];
        }
        if(i>=len&&sum<=k){
            rep(j,1,m) qaq[j]=maxx[j];
            qaq[m]+=k-sum;return 1;
        } 
    }
    return 0;
}
int main(){
    rd(n);rd(m);scanf("%lld",&k);
    rep(i,1,n) rep(j,1,m)
        rd(a[i][j]);
    int l = 0,r = n,ans;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) ans=mid,l=mid+1;
        else r=mid-1;
    }
    rep(i,1,m) printf("%d ",qaq[i]);
    return 0;
}
```
  - **核心实现思想**：`check`函数用于检查长度为`len`的区间是否满足条件，通过单调队列维护每种零件类型在长度为`len`的区间内的最大值，计算所有类型最大值之和并与`k`比较。主函数中二分查找满足条件的最大连续人数，并输出对应每种零件类型的最大值。

### 最优关键思路或技巧
 - **利用单调性**：通过分析发现区间端点移动时，区间内零件最大值之和的单调性，从而使用双指针或二分法减少枚举量。
 - **数据结构优化**：采用单调队列、ST表、线段树等数据结构高效维护区间最大值，提升算法效率。

### 同类型题或类似算法套路
此类题目通常涉及区间最值问题，关键在于利用区间端点移动时某些值的单调性，结合合适的数据结构优化计算。常见套路是先将问题转化为可利用单调性求解的形式，再选择合适的数据结构维护关键值。

### 推荐洛谷题目
 - [P3865 【模板】ST 表](https://www.luogu.com.cn/problem/P3865)：经典的ST表练习题，用于熟悉ST表的构建与查询。
 - [P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)：通过滑动窗口问题，加深对单调队列的理解与应用。
 - [P2678 [NOIP2015 提高组] 跳石头](https://www.luogu.com.cn/problem/P2678)：二分法解决最值问题的典型题目，锻炼二分查找的思维与应用能力。

---
处理用时：82.18秒