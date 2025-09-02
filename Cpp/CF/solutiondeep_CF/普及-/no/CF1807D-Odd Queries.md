# 题目信息

# Odd Queries

## 题目描述

You have an array $ a_1, a_2, \dots, a_n $ . Answer $ q $ queries of the following form:

- If we change all elements in the range $ a_l, a_{l+1}, \dots, a_r $ of the array to $ k $ , will the sum of the entire array be odd?

 Note that queries are independent and do not affect future queries.

## 说明/提示

For the first test case:

- If the elements in the range $ (2, 3) $ would get set to $ 3 $ the array would become $ \{2, 3, 3, 3, 2\} $ , the sum would be $ 2+3+3+3+2 = 13 $ which is odd, so the answer is "YES".
- If the elements in the range $ (2, 3) $ would get set to $ 4 $ the array would become $ \{2, 4, 4, 3, 2\} $ , the sum would be $ 2+4+4+3+2 = 15 $ which is odd, so the answer is "YES".
- If the elements in the range $ (1, 5) $ would get set to $ 5 $ the array would become $ \{5, 5, 5, 5, 5\} $ , the sum would be $ 5+5+5+5+5 = 25 $ which is odd, so the answer is "YES".
- If the elements in the range $ (1, 4) $ would get set to $ 9 $ the array would become $ \{9, 9, 9, 9, 2\} $ , the sum would be $ 9+9+9+9+2 = 38 $ which is even, so the answer is "NO".
- If the elements in the range $ (2, 4) $ would get set to $ 3 $ the array would become $ \{2, 3, 3, 3, 2\} $ , the sum would be $ 2+3+3+3+2 = 13 $ which is odd, so the answer is "YES".

## 样例 #1

### 输入

```
2
5 5
2 2 1 3 2
2 3 3
2 3 4
1 5 5
1 4 9
2 4 3
10 5
1 1 1 1 1 1 1 1 1 1
3 8 13
2 5 10
3 8 10
1 10 2
1 9 100```

### 输出

```
YES
YES
YES
NO
YES
NO
NO
NO
NO
YES```

# AI分析结果

### 题目内容
# 奇数查询

## 题目描述
你有一个数组 $a_1, a_2, \dots, a_n$ 。回答 $q$ 如下形式的查询：
- 如果我们将数组中范围为 $a_l, a_{l+1}, \dots, a_r$ 的所有元素都更改为 $k$ ，整个数组的和会是奇数吗？

注意，查询是相互独立的，不会影响后续查询。

## 说明/提示
对于第一个测试用例：
- 如果将范围 $(2, 3)$ 内的元素设置为 $3$ ，数组将变为 $\{2, 3, 3, 3, 2\}$ ，其和为 $2+3+3+3+2 = 13$ ，是奇数，所以答案是 “YES” 。
- 如果将范围 $(2, 3)$ 内的元素设置为 $4$ ，数组将变为 $\{2, 4, 4, 3, 2\}$ ，其和为 $2+4+4+3+2 = 15$ ，是奇数，所以答案是 “YES” 。
- 如果将范围 $(1, 5)$ 内的元素设置为 $5$ ，数组将变为 $\{5, 5, 5, 5, 5\}$ ，其和为 $5+5+5+5+5 = 25$ ，是奇数，所以答案是 “YES” 。
- 如果将范围 $(1, 4)$ 内的元素设置为 $9$ ，数组将变为 $\{9, 9, 9, 9, 2\}$ ，其和为 $9+9+9+9+2 = 38$ ，是偶数，所以答案是 “NO” 。
- 如果将范围 $(2, 4)$ 内的元素设置为 $3$ ，数组将变为 $\{2, 3, 3, 3, 2\}$ ，其和为 $2+3+3+3+2 = 13$ ，是奇数，所以答案是 “YES” 。

## 样例 #1
### 输入
```
2
5 5
2 2 1 3 2
2 3 3
2 3 4
1 5 5
1 4 9
2 4 3
10 5
1 1 1 1 1 1 1 1 1 1
3 8 13
2 5 10
3 8 10
1 10 2
1 9 100
```
### 输出
```
YES
YES
YES
NO
YES
NO
NO
NO
NO
YES
```

### 算法分类
前缀和

### 综合分析与结论
所有题解思路基本一致，均利用前缀和优化来解决问题。由于题目中查询次数多且数据范围较大，暴力解法会超时，因此采用前缀和算法。通过预处理前缀和数组，每次查询时，将数组分为操作部分和未操作部分，操作部分总和为 $(r - l + 1) \times k$，未操作部分为原数组总和减去操作区间的和（即 $sum_n - (sum_r - sum_{l - 1})$），将两部分相加判断奇偶性，从而得出答案。不同题解在代码实现细节上略有差异，如输入输出方式、变量命名等，但核心思路和算法要点相同。

### 所选的题解
- **作者：Loser_Syx（5星）**
    - **关键亮点**：思路清晰，详细阐述了利用前缀和优化的原因及具体实现方式，代码中自定义了输入输出函数，对数据范围大可能导致超时的情况有明确说明。
    - **个人心得**：提到题意较坑，开始对第二段理解有误，正确是将区间内所有数替换为 $k$。
    - **重点代码**：
```cpp
int a[200010], s[200010];
signed main(){
    int T = read();
    while(T--){
        int n = read(), q = read();
        s[0] = 0;
        f(i, 1, n, 1){
            a[i] = read();
            s[i] = s[i - 1] + a[i];//统计前缀和
        }
        while(q--){
            int l = read(), r = read(), k = read();
            int ans = s[l - 1] + s[n] - s[r] + k * (r - l + 1);
            if(ans % 2 == 1) puts("YES");
            else puts("NO");
        }
    }
    return 0;
}
```
核心实现思想：先读入数据并统计前缀和，每次查询时，根据前缀和计算操作后的数组总和，判断其奇偶性输出结果。

- **作者：Larryyu（4星）**
    - **关键亮点**：简洁明了地阐述了将操作完后数组分为操作部分和未操作部分的思路，代码简洁，逻辑清晰。
    - **重点代码**：
```cpp
ll sum[200200];
void solve(){
    int n=read(),q=read();
    sum[0]=0;
    for(int i=1;i<=n;i++){
        sum[i]=0;
        int x=read();
        sum[i]=sum[i-1]+x;//求得前缀和
    }
    while(q--){
        int l=read(),r=read(),k=read();
        ll i=sum[n]-(sum[r]-sum[l-1]),j=k*(r-l+1); //分为两部分
        if((i+j)%2==0){
            cout<<"NO"<<endl;
        }else{
            cout<<"YES"<<endl;
        }
    }
}
```
核心实现思想：读入数据同时计算前缀和，每次查询分别计算操作部分和未操作部分的和，相加判断奇偶性输出。

- **作者：minVan（4星）**
    - **关键亮点**：解题思路表述清晰，代码使用 `bits/stdc++.h` 头文件且利用位运算判断奇偶性，使代码更简洁。
    - **重点代码**：
```cpp
int a[N], sum[N];
signed main() {
    int t;
    cin >> t;
    while(t--) {
        int n, q;
        cin >> n >> q;
        sum[0] = 0;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            sum[i] = sum[i - 1] + a[i];
        }
        while(q--) {
            int x, y, k;
            cin >> x >> y >> k;
            cout << ((sum[n] + sum[y] - sum[x - 1] + k * (y - x + 1)) & 1? "YES" : "NO") << '\n';
        }
    }
    return 0;
}
```
核心实现思想：先预处理前缀和，每次查询计算操作后的总和，利用位运算判断奇偶性输出结果。

### 最优关键思路或技巧
利用前缀和数据结构优化计算，通过预处理前缀和数组，将每次查询的时间复杂度从暴力的 $O(n)$ 降低到 $O(1)$，从而高效解决问题。

### 可拓展之处
同类型题常涉及区间查询、修改等操作，类似算法套路如利用差分解决区间增减问题，树状数组、线段树解决更复杂的区间查询和修改操作。

### 洛谷相似题目推荐
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：通过前缀和思想解决连续子段和的问题。
- [P3370 【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370)：利用前缀和思想优化字符串哈希计算。
- [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)：可通过前缀和优化动态规划解决最大正方形问题。 

---
处理用时：48.19秒