# 题目信息

# Equal XOR

## 题目描述

You are given an array $ a $ of length $ 2n $ , consisting of each integer from $ 1 $ to $ n $ exactly twice.

You are also given an integer $ k $ ( $ 1 \leq k \leq \lfloor \frac{n}{2} \rfloor  $ ).

You need to find two arrays $ l $ and $ r $ each of length $ \mathbf{2k} $ such that:

- $ l $ is a subset $ ^\dagger $ of $ [a_1, a_2, \ldots a_n] $
- $ r $ is a subset of $ [a_{n+1}, a_{n+2}, \ldots a_{2n}] $
- [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of elements of $ l $ is equal to the bitwise XOR of elements of $ r $ ; in other words, $ l_1 \oplus l_2 \oplus \ldots \oplus l_{2k} = r_1 \oplus r_2 \oplus \ldots \oplus r_{2k} $

It can be proved that at least one pair of $ l $ and $ r $ always exists. If there are multiple solutions, you may output any one of them.

 $ ^\dagger $ A sequence $ x $ is a subset of a sequence $ y $ if $ x $ can be obtained by deleting several (possibly none or all) elements of $ y $ and rearranging the elements in any order. For example, $ [3,1,2,1] $ , $ [1, 2, 3] $ , $ [1, 1] $ and $ [3, 2] $ are subsets of $ [1, 1, 2, 3] $ but $ [4] $ and $ [2, 2] $ are not subsets of $ [1, 1, 2, 3] $ .

## 说明/提示

In the first test case, we choose $ l=[2,1] $ and $ r=[2,1] $ . $ [2, 1] $ is a subset of $ [a_1, a_2] $ and $ [2, 1] $ is a subset of $ [a_3, a_4] $ , and $ 2 \oplus 1 = 2 \oplus 1 = 3 $ .

In the second test case, $ 6 \oplus 4 = 1 \oplus 3 = 2 $ .

## 样例 #1

### 输入

```
4
2 1
1 2 2 1
6 1
6 4 2 1 2 3 1 6 3 5 5 4
4 1
1 2 3 4 1 2 3 4
6 2
5 1 3 3 5 1 2 6 4 6 4 2```

### 输出

```
2 1
2 1
6 4
1 3
1 2
1 2
5 1 3 3
6 4 2 4```

# AI分析结果

### 题目中文重写
## 相等的异或

### 题目描述
给定一个长度为 $2n$ 的数组 $a$，其中从 $1$ 到 $n$ 的每个整数恰好出现两次。

同时给定一个整数 $k$（$1 \leq k \leq \lfloor \frac{n}{2} \rfloor$）。

你需要找到两个长度均为 $\mathbf{2k}$ 的数组 $l$ 和 $r$，满足以下条件：
- $l$ 是 $[a_1, a_2, \ldots a_n]$ 的一个子集。
- $r$ 是 $[a_{n + 1}, a_{n + 2}, \ldots a_{2n}]$ 的一个子集。
- $l$ 中元素的按位异或（[按位异或操作](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)）等于 $r$ 中元素的按位异或；换句话说，$l_1 \oplus l_2 \oplus \ldots \oplus l_{2k} = r_1 \oplus r_2 \oplus \ldots \oplus r_{2k}$。

可以证明，至少存在一组 $l$ 和 $r$ 满足条件。如果有多个解，你可以输出其中任意一个。

### 说明/提示
在第一个测试用例中，我们选择 $l = [2, 1]$ 和 $r = [2, 1]$。$[2, 1]$ 是 $[a_1, a_2]$ 的子集，$[2, 1]$ 是 $[a_3, a_4]$ 的子集，并且 $2 \oplus 1 = 2 \oplus 1 = 3$。

在第二个测试用例中，$6 \oplus 4 = 1 \oplus 3 = 2$。

### 样例 #1
#### 输入
```
4
2 1
1 2 2 1
6 1
6 4 2 1 2 3 1 6 3 5 5 4
4 1
1 2 3 4 1 2 3 4
6 2
5 1 3 3 5 1 2 6 4 6 4 2
```
#### 输出
```
2 1
2 1
6 4
1 3
1 2
1 2
5 1 3 3
6 4 2 4
```

### 综合分析与结论
这些题解的核心思路都是利用异或运算的性质 $x \oplus x = 0$ 来构造满足条件的数组 $l$ 和 $r$。算法要点在于先统计每个数在前半段和后半段的出现次数，然后优先将出现两次的数加入到 $l$ 和 $r$ 中，因为它们的异或和为 $0$，不会影响整体的异或结果。如果数量不够 $2k$，再加入在前半段和后半段各出现一次的相同数字，这样能保证两边异或和相等。

难点在于如何合理地选择数字，确保最终能得到长度为 $2k$ 且异或和相等的两个数组。不同题解在实现细节上有所差异，比如使用的数据结构、循环的顺序等，但本质思路一致。

### 评分较高的题解
- **作者：jiangchen1234（5星）**
    - **关键亮点**：思路清晰，详细阐述了构造数组的过程，代码结构良好，使用了自定义的输入输出函数，提高了代码的效率。
    - **核心代码**：
```cpp
il void solve(){
    mp1.clear();
    mp2.clear();
    cnt1 = 0;
    cnt2 = 0;
    len1 = 0;
    len2 = 0;
    int n = read(),k = read();
    F(i,1,n){
        a[i] = read();
        ++mp1[a[i]];
    }
    F(i,1,n){
        b[i] = read();
        ++mp2[b[i]];
    }
    F(i,1,n){
        if(mp1[a[i]] == 2 && len1 <= 2 * k - 2){
            mp1[a[i]] = 0;
            ++cnt1;
            len1 += 2;
            ans1[len1 - 1] = ans1[len1] = a[i];
        }
    }
    F(i,1,n){
        if(mp2[b[i]] == 2 && len2 <= 2 * k - 2){
            mp2[b[i]] = 0;
            ++cnt2;
            len2 += 2;
            ans2[len2 - 1] = ans2[len2] = b[i];
        }
    }
    F(i,1,n){
        if(len1 < 2 * k && mp1[a[i]] == 1){
            ++len1,++len2;
            ans1[len1] = ans2[len2] = a[i];
        }
    }
    F(i,1,2 * k){
        cout<<ans1[i]<<" ";
    }
    cout<<endl;
    F(i,1,2 * k){
        cout<<ans2[i]<<" ";
    }
    cout<<endl;
}
```
- **作者：Shadow_T（4星）**
    - **关键亮点**：思路简洁明了，代码实现直接，使用 `vector` 存储结果，方便操作。
    - **核心代码**：
```cpp
void solve()
{
    int n,k;
    cin>>n>>k;
    map<int,int>mp1,mp2;
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]),mp1[a[i]]++;
    for(int i=1;i<=n;i++)
        scanf("%d",&b[i]),mp2[b[i]]++;
    vector<int> ansa,ansb;
    for(int i=1;i<=n;i++)
        if(mp1[i]==1) ansa.push_back(i),ansb.push_back(i);
    if(ansa.size()<2*k&&ansa.size()%2==1) ansa.pop_back(),ansb.pop_back();
    for(int i=1;i<=n;i++)
        if(mp1[i]==2) ansa.push_back(i),ansa.push_back(i);
    for(int i=1;i<=n;i++)
        if(mp2[i]==2) ansb.push_back(i),ansb.push_back(i);
    for(int i=0;i<2*k;i++)
        cout<<ansa[i]<<" ";
    cout<<"\n";
    for(int i=0;i<2*k;i++)
        cout<<ansb[i]<<" ";
    cout<<"\n";
}
```
- **作者：Blikewsr（4星）**
    - **关键亮点**：对思路进行了详细的证明，代码注释清晰，便于理解。
    - **核心代码**：
```cpp
signed main() {
    cin >> T;
    while (T --) {   // 多测
        cin >> n >> k; cntA = 0, cntB = 0;
        memset(v, 0, sizeof(v));  // 初始化 
        for (int i = 1; i <= n; ++ i) {
            cin >> mp[0][i];
            ++ v[0][mp[0][i]];  // 记录数列左半边每一个数在左边出现的次数
        }
        for (int i = 1; i <= n; ++ i) {
            cin >> mp[1][i];
            ++ v[1][mp[1][i]];  // 记录数列右半边每一个数在右边出现的次数
        }
        for (int i = 1; i <= n; ++ i) {
            if (v[0][i] == 2) {  // 左边出现了 2 次的，直接异或得到 0，对答案没有影响
                A[++ cntA] = i;
                A[++ cntA] = i; // 记录下这些数
            }
            if (v[1][i] == 2) {  // 右边出现了 2 次的，同上
                B[++ cntB] = i;
                B[++ cntB] = i;
            }
        }
        if (cntA >= k * 2) {
            // 每一个数只在一半边出现
            for (int i = 1; i <= k * 2; ++ i)
                cout << A[i] << ' ';
            cout << '\n';  // 左边
            for (int i = 1; i <= k * 2; ++ i)
                cout << B[i] << ' ';
            cout << '\n';  // 右边
        }
        else {
            // 有一些数在两半边都有
            for (int i = 1; i <= n; ++ i) {
                if (cntA >= k * 2) break;
                if (v[0][i] == 1) A[++ cntA] = i, B[++ cntB] = i;
                // 把这些之出现一次的数记录下来
            }
            for (int i = 1; i <= k * 2; ++ i) 
                cout << A[i] << ' ';
            cout << '\n';
            // 输出这两种数（左边）
            for (int i = 1; i <= k * 2; ++ i) 
                cout << B[i] << ' ';
            cout << '\n';
            // 右边
        }
    }
    return 0;
}
```

### 最优关键思路或技巧
- 利用异或运算的性质 $x \oplus x = 0$ 来简化问题，优先选择出现两次的数加入结果数组，保证异或和为 $0$。
- 当出现两次的数数量不足时，加入在前半段和后半段各出现一次的相同数字，确保两边异或和相等。
- 使用 `map` 或数组来统计每个数的出现次数，方便后续处理。

### 可拓展之处
同类型题可能会改变数组的长度、数字的出现次数或异或和的要求，但核心思路仍然是利用异或运算的性质进行构造。类似的算法套路可以应用于其他需要构造满足特定条件的数组或序列的问题。

### 洛谷相似题目推荐
- [P1469 找筷子](https://www.luogu.com.cn/problem/P1469)：考察异或运算的基本性质。
- [P2158 [SDOI2008] 仪仗队](https://www.luogu.com.cn/problem/P2158)：涉及数学推导和异或运算的应用。
- [P3811 乘法逆元](https://www.luogu.com.cn/problem/P3811)：虽然主要考察数论知识，但异或运算在一些优化中可能会用到。

### 个人心得摘录与总结
- **作者：SJH__qwq**：认为这是有史以来最难写的 Div2 B 题，强调了按位异或运算性质的重要性，通过选择相同的数和利用两边各出现一次的数来构造合法方案。总结：在解决异或相关问题时，要充分利用异或运算的性质进行构造。 

---
处理用时：56.54秒