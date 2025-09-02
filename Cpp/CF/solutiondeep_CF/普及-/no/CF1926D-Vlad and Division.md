# 题目信息

# Vlad and Division

## 题目描述

Vladislav has $ n $ non-negative integers, and he wants to divide all of them into several groups so that in any group, any pair of numbers does not have matching bit values among bits from $ 1 $ -st to $ 31 $ -st bit (i.e., considering the $ 31 $ least significant bits of the binary representation).

For an integer $ k $ , let $ k_2(i) $ denote the $ i $ -th bit in its binary representation (from right to left, indexing from 1). For example, if $ k=43 $ , since $ 43=101011_2 $ , then $ 43_2(1)=1 $ , $ 43_2(2)=1 $ , $ 43_2(3)=0 $ , $ 43_2(4)=1 $ , $ 43_2(5)=0 $ , $ 43_2(6)=1 $ , $ 43_2(7)=0 $ , $ 43_2(8)=0, \dots, 43_2(31)=0 $ .

Formally, for any two numbers $ x $ and $ y $ in the same group, the condition $ x_2(i) \neq y_2(i) $ must hold for all $ 1 \leq i < 32 $ .

What is the minimum number of groups Vlad needs to achieve his goal? Each number must fall into exactly one group.

## 说明/提示

In the first test case, any two numbers have the same last $ 31 $ bits, so we need to place each number in its own group.

In the second test case, $ a_1=0000000000000000000000000000000_2 $ , $ a_2=1111111111111111111111111111111_2 $ so they can be placed in the same group because $ a_1(i) \ne a_2(i) $ for each $ i $ between $ 1 $ and $ 31 $ , inclusive.

## 样例 #1

### 输入

```
9
4
1 4 3 4
2
0 2147483647
5
476319172 261956880 2136179468 1671164475 1885526767
3
1335890506 811593141 1128223362
4
688873446 627404104 1520079543 1458610201
4
61545621 2085938026 1269342732 1430258575
4
0 0 2147483647 2147483647
3
0 0 2147483647
8
1858058912 289424735 1858058912 2024818580 1858058912 289424735 122665067 289424735```

### 输出

```
4
1
3
2
2
3
2
2
4```

# AI分析结果

### 题目中文重写
# Vlad 和分组

## 题目描述
弗拉季斯拉夫（Vladislav）有 $n$ 个非负整数，他想将所有这些数分成若干组，使得在任何一个组中，任意一对数字在第 1 位到第 31 位的二进制表示中没有相同的位值（即考虑二进制表示的 31 个最低有效位）。

对于一个整数 $k$，设 $k_2(i)$ 表示其二进制表示中的第 $i$ 位（从右到左，索引从 1 开始）。例如，如果 $k = 43$，因为 $43 = 101011_2$，那么 $43_2(1)=1$，$43_2(2)=1$，$43_2(3)=0$，$43_2(4)=1$，$43_2(5)=0$，$43_2(6)=1$，$43_2(7)=0$，$43_2(8)=0, \dots, 43_2(31)=0$。

形式上，对于同一组中的任意两个数字 $x$ 和 $y$，对于所有 $1 \leq i < 32$，条件 $x_2(i) \neq y_2(i)$ 必须成立。

弗拉季斯拉夫实现他的目标最少需要多少组？每个数字必须恰好属于一个组。

## 说明/提示
在第一个测试用例中，任意两个数字的最后 31 位都相同，所以我们需要将每个数字放在单独的组中。

在第二个测试用例中，$a_1 = 0000000000000000000000000000000_2$，$a_2 = 1111111111111111111111111111111_2$，所以它们可以放在同一组中，因为对于 $1$ 到 $31$ 之间（包括 $1$ 和 $31$）的每个 $i$，都有 $a_1(i) \ne a_2(i)$。

## 样例 #1
### 输入
```
9
4
1 4 3 4
2
0 2147483647
5
476319172 261956880 2136179468 1671164475 1885526767
3
1335890506 811593141 1128223362
4
688873446 627404104 1520079543 1458610201
4
61545621 2085938026 1269342732 1430258575
4
0 0 2147483647 2147483647
3
0 0 2147483647
8
1858058912 289424735 1858058912 2024818580 1858058912 289424735 122665067 289424735
```
### 输出
```
4
1
3
2
2
3
2
2
4
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心策略，利用两个数二进制下第 1 到 31 位都不同时，两数之和为 $2^{31}-1$（即 2147483647）这一性质，尽可能地将能配对的数组合在一起，以达到分组数量最少的目的。各题解主要区别在于数据结构的选择和具体实现方式，多数使用 `map` 来记录数字出现的次数，部分使用 `multiset` 或二分查找。

### 所选题解
- __Dist__（4星）
  - 关键亮点：思路清晰，代码结构良好，通过自定义 `read` 函数和 `fan` 函数分别实现快速读入和取反操作，便于理解和维护。
  - 个人心得：2发罚时，疼。
- 2c_s（4星）
  - 关键亮点：使用 `multiset` 存储数字，利用 `find` 函数查找配对数字，代码简洁，逻辑清晰。
  - 个人心得：有多组测试数据，别忘清空变量、数组等。
- RyanLi（4星）
  - 关键亮点：思路简洁明了，使用 `map` 维护数字出现次数，贪心配对，代码可读性高。
  - 个人心得：没事别用 `unordered_map`，血的教训。

### 重点代码
#### __Dist__
```cpp
ll fan(ll x) {
    ll res = 0;
    for (ll i = 1; i <= 31; i++) {
        if(x >> (i - 1) & 1) {
            res = res & ~(1 << (i - 1));
        }
        else {
            res = res | (1 << (i - 1));
        }
    }
    return res;
}

void solve() {
    ll res = 0;
    map<ll, ll> mp;
    ll n = read();
    for (ll i = 1; i <= n; i++) {
        ll a = read();
        ll p = fan(a);
        if(!mp[p]) {
            ++res;
            mp[a]++;
        }
        else {
            mp[p]--;
        }
    }
    cout << res << '\n';
}
```
核心实现思想：先定义 `fan` 函数对数字的前 31 位取反，然后遍历数组，对于每个数字，查找其取反后的数字是否在之前出现过，若出现过则配对，否则新开一组。

#### 2c_s
```cpp
inline void solve(){
    cin>>n;
    st.clear();
    int ans = 0;
    for(int i = 1; i <= n; ++i){
        int x;
        cin>>x;
        auto p = st.find(x ^ inf);
        if(p == st.end()){
            st.insert(x);
            ++ans;
        }
        else st.erase(p);
    }
    cout<<ans;
    puts("");
    return ;
}
```
核心实现思想：使用 `multiset` 存储数字，对于每个读入的数字，查找其异或 `inf`（$2^{31}-1$）后的数字是否在集合中，若存在则删除，否则加入集合并增加答案计数。

#### RyanLi
```cpp
for (cin >> t; t; --t) {
    ans = 0, mp.clear();
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i], ++mp[a[i]];
    for (int i = 1; i <= n; ++i) if (mp[a[i]]) {
        --mp[a[i]];
        if (mp[LIM - a[i]]) --mp[LIM - a[i]];
        ++ans;
    } cout << ans << '\n';
}
```
核心实现思想：使用 `map` 记录每个数字出现的次数，遍历数组，对于每个数字，若其存在则减少其计数，若其配对数字存在则也减少计数，同时增加答案计数。

### 最优关键思路或技巧
- 利用位运算或异或运算快速找到配对数字。
- 使用 `map` 或 `multiset` 等数据结构记录数字出现次数，方便查找和配对。

### 可拓展之处
同类型题可能会改变二进制位的范围或条件，或者增加其他限制，解题思路仍然可以基于贪心策略，通过位运算找到满足条件的配对关系。

### 推荐洛谷题目
- P1803 凌乱的yyy / 线段覆盖
- P2240 【深基12.例1】部分背包问题
- P1094 纪念品分组

### 个人心得总结
- __Dist__：做题时可能会出现罚时，需谨慎。
- 2c_s：多组测试数据时，要记得清空变量和数组。
- RyanLi：在本题中使用 `unordered_map` 可能会出现问题，应谨慎使用。 

---
处理用时：51.01秒