# 题目信息

# Longest Strike

## 题目描述

Given an array $ a $ of length $ n $ and an integer $ k $ , you are tasked to find any two numbers $ l $ and $ r $ ( $ l \leq r $ ) such that:

- For each $ x $ $ (l \leq x \leq r) $ , $ x $ appears in $ a $ at least $ k $ times (i.e. $ k $ or more array elements are equal to $ x $ ).
- The value $ r-l $ is maximized.

If no numbers satisfy the conditions, output -1.

For example, if $ a=[11, 11, 12, 13, 13, 14, 14] $ and $ k=2 $ , then:

- for $ l=12 $ , $ r=14 $ the first condition fails because $ 12 $ does not appear at least $ k=2 $ times.
- for $ l=13 $ , $ r=14 $ the first condition holds, because $ 13 $ occurs at least $ k=2 $ times in $ a $ and $ 14 $ occurs at least $ k=2 $ times in $ a $ .
- for $ l=11 $ , $ r=11 $ the first condition holds, because $ 11 $ occurs at least $ k=2 $ times in $ a $ .

A pair of $ l $ and $ r $ for which the first condition holds and $ r-l $ is maximal is $ l = 13 $ , $ r = 14 $ .

## 样例 #1

### 输入

```
4
7 2
11 11 12 13 13 14 14
5 1
6 3 5 2 1
6 4
4 3 4 3 3 4
14 2
1 1 2 2 2 3 3 3 3 4 4 4 4 4```

### 输出

```
13 14
1 3
-1
1 4```

# AI分析结果

### 题目翻译
## 最长连续区间

### 题目描述
给定一个长度为 $n$ 的数组 $a$ 和一个整数 $k$，你需要找出任意两个数 $l$ 和 $r$（$l \leq r$），使得：
- 对于每个 $x$（$l \leq x \leq r$），$x$ 在 $a$ 中至少出现 $k$ 次（即数组中至少有 $k$ 个元素等于 $x$）。
- $r - l$ 的值最大。

如果没有满足条件的数，输出 -1。

例如，如果 $a = [11, 11, 12, 13, 13, 14, 14]$ 且 $k = 2$，那么：
- 当 $l = 12$，$r = 14$ 时，第一个条件不满足，因为 $12$ 在 $a$ 中出现的次数不足 $k = 2$ 次。
- 当 $l = 13$，$r = 14$ 时，第一个条件满足，因为 $13$ 在 $a$ 中至少出现 $k = 2$ 次，$14$ 也至少出现 $k = 2$ 次。
- 当 $l = 11$，$r = 11$ 时，第一个条件满足，因为 $11$ 在 $a$ 中至少出现 $k = 2$ 次。

满足第一个条件且 $r - l$ 最大的 $l$ 和 $r$ 是 $l = 13$，$r = 14$。

### 样例 #1
#### 输入
```
4
7 2
11 11 12 13 13 14 14
5 1
6 3 5 2 1
6 4
4 3 4 3 3 4
14 2
1 1 2 2 2 3 3 3 3 4 4 4 4 4
```
#### 输出
```
13 14
1 3
-1
1 4
```

### 综合分析与结论
这些题解的核心思路基本一致，都是先统计数组中每个数的出现次数，筛选出出现次数不少于 $k$ 的数，再找出这些数中最长的连续数字段作为最终答案。

#### 思路对比
- **统计出现次数**：多数题解使用 `map` 来统计每个数的出现次数，部分题解先对数组排序后再统计。
- **筛选数字**：将出现次数不少于 $k$ 的数存入新的容器（如 `vector` 或数组）。
- **寻找最长连续段**：对筛选后的容器排序，遍历容器找出最长连续数字段的左右端点。

#### 算法要点
- **数据结构**：主要使用 `map` 统计出现次数，用 `vector` 或数组存储筛选后的数字。
- **排序**：对筛选后的数字进行排序，以便找出连续段。
- **遍历**：遍历排序后的容器，记录最长连续段的信息。

#### 解决难点
- **数据范围大**：使用 `map` 避免开大规模数组，解决空间问题。
- **连续段判断**：通过比较相邻元素是否相差 1 来判断是否连续。

### 评分较高的题解
- **作者：Coros_Trusds（5星）**
    - **关键亮点**：思路清晰，代码注释详细，时间复杂度分析准确。
    - **核心代码**：
```cpp
inline void solve() {
    cin >> n >> m;
    map<int,int>mp;
    for (register int i = 1;i <= n; ++ i) {
        cin >> a[i];
        mp[a[i]] ++;
    }
    for (map<int,int>::iterator it = mp.begin();it!= mp.end(); ++ it) {
        if ((*it).second >= m) {
            vec.push_back((*it).first);
        }
    }
    if (!vec.size()) {
        puts("-1");
        return;
    }
    sort(vec.begin(),vec.end());
    int l = vec[0],r = vec[0],st = vec[0],maxx = 0;
    for (register int i = 1;i < vec.size(); ++ i) {
        if (vec[i] == vec[i - 1] + 1) {
            if (maxx < vec[i] - st) {   
                maxx = vec[i] - st;
                l = st,r = vec[i];
            }
        } else {
            st = vec[i];
        }
    }
    cout << l << " " << r << "\n";
}
```
- **作者：FQR_（4星）**
    - **关键亮点**：思路清晰，代码结构清晰，逐步给出实现步骤。
    - **核心代码**：
```cpp
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int t;
    cin>>t;
    while(t--)
    {
        map<int,int> a;
        int n,k,x;
        cin>>n>>k;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            a[x]++;
        }
        int b[200005],t=0;
        for(map<int,int>::iterator it=a.begin();it!=a.end();it++)
        {
            if(it->second>=k) b[t++]=it->first;
        }
        if(t==0) 
        {
            cout<<-1<<endl;
            continue;
        }
        sort(b,b+t);
        int l=b[0],r=b[0];
        int ll=b[0];
        for(int i=1;i<t;i++)
        {
            if(b[i]!=b[i-1]+1) ll=b[i];
            if(b[i]-ll>r-l) l=ll,r=b[i];
        }
        cout<<l<<" "<<r<<endl;
    }
    return 0;
}
```
- **作者：lwx20211103（4星）**
    - **关键亮点**：思路清晰，使用变量记录关键信息，代码简洁易懂。
    - **核心代码**：
```cpp
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    vector<int> v;
    map<int, int> mp;
    for (auto &&i : nums) 
        cin >> i, mp[i]++;
    for (auto i : mp)
        if (i.nd >= k)
            v.p_b(i.ft);
    if (v.empty())
    {
        cout << "-1\n";
        return ;
    }
    int l, r, lastnum, sum = -114514;
    l = r = lastnum = v.front();
    for (int i = 1; i < v.size(); i++)
    {
        if (v[i] - v[i - 1] == 1)
        {
            if (v[i] - lastnum > sum)
            {
                sum = v[i] - lastnum;
                l = lastnum, r = v[i];
            }
        }
        else lastnum = v[i];
    }
    cout << l << " " << r << "\n";
}
```

### 最优关键思路或技巧
- **使用 `map` 统计出现次数**：可以处理数据范围大的情况，避免开大规模数组。
- **筛选后排序**：将满足条件的数字筛选出来并排序，方便找出最长连续段。

### 可拓展之处
同类型题目可能会改变条件，如要求区间内数字出现次数在某个范围内，或要求区间长度满足特定条件等。解题思路仍然是先统计出现次数，再根据条件筛选和处理。

### 洛谷推荐题目
- [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
- [P1991 无线通讯网](https://www.luogu.com.cn/problem/P1991)
- [P2676 [USACO07DEC]Bookshelf B](https://www.luogu.com.cn/problem/P2676)

### 个人心得摘录与总结
- **作者：Deamer**：提到第二种方法可能会遗漏 `s[0]=s[1]-1;` 和 `if((r-l+1)>maxn) ansl=s[l],ansr=s[r];`，提醒要注意边界条件和更新最优解。总结为在处理连续区间问题时，要特别注意边界情况和最终结果的更新。 

---
处理用时：47.21秒