# 题目信息

# Balance (Easy version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version there are no "remove" queries.

Initially you have a set containing one element — $ 0 $ . You need to handle $ q $ queries of the following types:

- + $ x $ — add the integer $ x $ to the set. It is guaranteed that this integer is not contained in the set;
- ? $ k $ — find the $ k\text{-mex} $ of the set.

In our problem, we define the $ k\text{-mex} $ of a set of integers as the smallest non-negative integer $ x $ that is divisible by $ k $ and which is not contained in the set.

## 说明/提示

In the first example:

After the first and second queries, the set will contain elements $ \{0, 1, 2\} $ . The smallest non-negative number that is divisible by $ 1 $ and is not contained in the set is $ 3 $ .

After the fourth query, the set will contain the elements $ \{0, 1, 2, 4\} $ . The smallest non-negative number that is divisible by $ 2 $ and is not contained in the set is $ 6 $ .

In the second example:

- Initially, the set contains only the element $ \{0\} $ .
- After adding an integer $ 100 $ the set contains elements $ \{0, 100\} $ .
- $ 100\text{-mex} $ of the set is $ 200 $ .
- After adding an integer $ 200 $ the set contains elements $ \{0, 100, 200\} $ .
- $ 100\text{-mex} $ of the set is $ 300 $ .
- After adding an integer $ 50 $ the set contains elements $ \{0, 50, 100, 200\} $ .
- $ 50\text{-mex} $ of the set is $ 150 $ .

## 样例 #1

### 输入

```
15
+ 1
+ 2
? 1
+ 4
? 2
+ 6
? 3
+ 7
+ 8
? 1
? 2
+ 5
? 1
+ 1000000000000000000
? 1000000000000000000```

### 输出

```
3
6
3
3
10
3
2000000000000000000```

## 样例 #2

### 输入

```
6
+ 100
? 100
+ 200
? 100
+ 50
? 50```

### 输出

```
200
300
150```

# AI分析结果

### 题目内容重写
# Balance (Easy version)

## 题目描述

这是问题的简单版本。唯一的不同在于这个版本中没有“删除”操作。

初始时，你有一个包含一个元素的集合——$0$。你需要处理$q$个以下类型的查询：

- + $x$ —— 将整数$x$添加到集合中。保证这个整数不在集合中；
- ? $k$ —— 找到集合的$k\text{-mex}$。

在我们的问题中，集合的$k\text{-mex}$定义为最小的非负整数$x$，它能够被$k$整除且不在集合中。

## 说明/提示

在第一个例子中：

在第一个和第二个查询之后，集合将包含元素$\{0, 1, 2\}$。最小的能够被$1$整除且不在集合中的非负数是$3$。

在第四个查询之后，集合将包含元素$\{0, 1, 2, 4\}$。最小的能够被$2$整除且不在集合中的非负数是$6$。

在第二个例子中：

- 初始时，集合只包含元素$\{0\}$。
- 添加整数$100$后，集合包含元素$\{0, 100\}$。
- 集合的$100\text{-mex}$是$200$。
- 添加整数$200$后，集合包含元素$\{0, 100, 200\}$。
- 集合的$100\text{-mex}$是$300$。
- 添加整数$50$后，集合包含元素$\{0, 50, 100, 200\}$。
- 集合的$50\text{-mex}$是$150$。

## 样例 #1

### 输入

```
15
+ 1
+ 2
? 1
+ 4
? 2
+ 6
? 3
+ 7
+ 8
? 1
? 2
+ 5
? 1
+ 1000000000000000000
? 1000000000000000000```

### 输出

```
3
6
3
3
10
3
2000000000000000000```

## 样例 #2

### 输入

```
6
+ 100
? 100
+ 200
? 100
+ 50
? 50```

### 输出

```
200
300
150```

### 算法分类
模拟

### 题解分析与结论
本题的核心在于处理集合的插入和查询操作，特别是查询操作需要找到最小的$k\text{-mex}$。由于没有删除操作，且查询的$k\text{-mex}$是单调递增的，可以通过记忆化来优化查询效率。

### 高星题解推荐
#### 题解1：作者：lailai0916 (赞：4)
**星级：5星**
**关键亮点：**
- 使用`set`维护集合，`map`记录每个$k$的上一次查询结果，避免重复计算。
- 时间复杂度优化为$O(q \log q)$，通过记忆化查询结果。

**核心代码：**
```cpp
set<ll> s;
map<ll,ll> m;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin>>q;
    s.insert(0);
    while(q--) {
        char op;
        ll x;
        cin>>op>>x;
        if(op=='+') s.insert(x);
        else if(op=='?') {
            ll ans=m[x];
            while(s.find(ans)!=s.end()) ans+=x;
            m[x]=ans;
            cout<<ans<<'\n';
        }
    }
    return 0;
}
```

#### 题解2：作者：zac2010 (赞：4)
**星级：4星**
**关键亮点：**
- 使用`map`记录每个$k$的上一次查询结果，避免重复计算。
- 时间复杂度分析清晰，优化思路明确。

**核心代码：**
```cpp
map<int,int> mp, id;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    for(cin>>t;t;t--) {
        cin>>op>>n;
        if(op=='?') {
            int lst=id[n];
            if(lst==0) lst=1;
            while(mp[n*lst]) lst++;
            id[n]=lst;
            cout<<n*id[n]<<"\n";
        } else {
            mp[n]++;
        }
    }
}
```

#### 题解3：作者：fmdd_szx (赞：2)
**星级：4星**
**关键亮点：**
- 使用`map`记录每个$k$的上一次查询结果，避免重复计算。
- 代码简洁，实现思路清晰。

**核心代码：**
```cpp
map<int,int> f,a;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    while(n--) {
        cin>>c>>x;
        if(c=='+') f[x]++;
        else {
            if(!a[x]) t=1;
            else t=a[x];
            for(i=t;;i++)
                if(!f[i*x]) {
                    cout<<i*x<<"\n",a[x]=i;
                    break;
                }
        }
    }
    return 0;
}
```

### 最优关键思路或技巧
- **记忆化查询结果**：通过记录每个$k$的上一次查询结果，避免重复计算，显著提高查询效率。
- **数据结构选择**：使用`set`维护集合，`map`记录查询结果，确保操作的高效性。

### 拓展思路
- **类似问题**：处理动态集合的查询操作时，记忆化是一种常见的优化手段，特别是在查询结果具有单调性的情况下。
- **同类型题**：
  - [洛谷 P3369 【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369)
  - [洛谷 P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
  - [洛谷 P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)

---
处理用时：41.78秒