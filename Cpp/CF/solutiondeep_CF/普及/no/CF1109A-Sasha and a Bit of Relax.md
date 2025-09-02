# 题目信息

# Sasha and a Bit of Relax

## 题目描述

Sasha likes programming. Once, during a very long contest, Sasha decided that he was a bit tired and needed to relax. So he did. But since Sasha isn't an ordinary guy, he prefers to relax unusually. During leisure time Sasha likes to upsolve unsolved problems because upsolving is very useful.

Therefore, Sasha decided to upsolve the following problem:

You have an array $ a $ with $ n $ integers. You need to count the number of funny pairs $ (l, r) $ $ (l \leq r) $ . To check if a pair $ (l, r) $ is a funny pair, take $ mid = \frac{l + r - 1}{2} $ , then if $ r - l + 1 $ is an even number and $ a_l \oplus a_{l+1} \oplus \ldots \oplus a_{mid} = a_{mid + 1} \oplus a_{mid + 2} \oplus \ldots \oplus a_r $ , then the pair is funny. In other words, $ \oplus $ of elements of the left half of the subarray from $ l $ to $ r $ should be equal to $ \oplus $ of elements of the right half. Note that $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

It is time to continue solving the contest, so Sasha asked you to solve this task.

## 说明/提示

Be as cool as Sasha, upsolve problems!

In the first example, the only funny pair is $ (2, 5) $ , as $ 2 \oplus 3 = 4 \oplus 5 = 1 $ .

In the second example, funny pairs are $ (2, 3) $ , $ (1, 4) $ , and $ (3, 6) $ .

In the third example, there are no funny pairs.

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6
3 2 2 3 7 6
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3
42 4 2
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# Sasha and a Bit of Relax

## 题目描述

Sasha喜欢编程。在一次非常长的比赛中，Sasha决定他有点累，需要放松一下。于是他放松了。但由于Sasha不是一个普通人，他喜欢以不寻常的方式放松。在闲暇时间，Sasha喜欢解决未解决的问题，因为解决问题非常有用。

因此，Sasha决定解决以下问题：

你有一个包含$n$个整数的数组$a$。你需要计算有趣的数对$(l, r)$ $(l \leq r)$的数量。要检查一个数对$(l, r)$是否有趣，取$mid = \frac{l + r - 1}{2}$，然后如果$r - l + 1$是偶数且$a_l \oplus a_{l+1} \oplus \ldots \oplus a_{mid} = a_{mid + 1} \oplus a_{mid + 2} \oplus \ldots \oplus a_r$，则该数对是有趣的。换句话说，从$l$到$r$的子数组的左半部分的元素的异或和应等于右半部分的元素的异或和。注意，$\oplus$表示[位异或操作](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

是时候继续比赛了，所以Sasha请你解决这个任务。

## 说明/提示

像Sasha一样酷，解决问题！

在第一个例子中，唯一有趣的数对是$(2, 5)$，因为$2 \oplus 3 = 4 \oplus 5 = 1$。

在第二个例子中，有趣的数对是$(2, 3)$，$(1, 4)$，和$(3, 6)$。

在第三个例子中，没有有趣的数对。

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6
3 2 2 3 7 6
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3
42 4 2
```

### 输出

```
0
```

### 算法分类
前缀和、位运算

### 题解分析与结论
本题的核心在于利用前缀和和位运算的性质来高效地计算满足条件的数对。所有题解都使用了前缀异或和的性质，即如果两个前缀异或和相等，则它们之间的子数组的异或和为0。此外，由于子数组长度必须为偶数，题解中还引入了奇偶性的判断。

### 所选高星题解
1. **作者：zhangqiuyanAFOon2024 (4星)**
   - **关键亮点**：使用`map`记录前缀异或和的奇偶性，代码简洁高效。
   - **核心代码**：
     ```cpp
     map<int,int>mp[2];
     int a[N],q[N];
     signed main(){
         int n,cnt=0;
         cin>>n;
         for(int i=1;i<=n;i++){
             cin>>a[i];
             q[i]=q[i-1]^a[i];
         }
         mp[0][0]=1;
         for(int i=1;i<=n;i++){
             cnt+=mp[i%2][q[i]];
             mp[i%2][q[i]]++;
         }
         cout<<cnt;
         return 0;
     }
     ```
   - **个人心得**：通过`map`记录前缀异或和的奇偶性，避免了复杂的判断，代码简洁且高效。

2. **作者：lzy120406 (4星)**
   - **关键亮点**：使用`unordered_map`记录前缀异或值的出现次数，分为奇数和偶数两种情况，代码清晰。
   - **核心代码**：
     ```cpp
     unordered_map<int, int> cnt[2];
     int main() {
         int n;
         cin >> n;
         for (int i = 0; i < n; ++i) {
             cin >> a[i];
         }
         for (int i = 1; i <= n; ++i) {
             s[i] = s[i - 1] ^ a[i - 1];
         }
         cnt[0][0] = 1;
         long long ans = 0;
         for (int i = 1; i <= n; ++i) {
             int k = i % 2;
             if (cnt[k].count(s[i])) {
                 ans += cnt[k][s[i]];
                 cnt[k][s[i]]++;
             } else {
                 cnt[k][s[i]] = 1;
             }
         }
         cout << ans << endl;
         return 0;
     }
     ```
   - **个人心得**：通过`unordered_map`记录前缀异或值的出现次数，分为奇数和偶数两种情况，代码清晰且高效。

3. **作者：JWRuixi (4星)**
   - **关键亮点**：使用数组记录前缀异或值的出现次数，分为奇数和偶数两种情况，代码简洁高效。
   - **核心代码**：
     ```cpp
     int c[2][2000007];
     LL ans;
     int main() {
         n = read(), c[0][0] = 1;
         for (int i = 1; i <= n; i++) {
             a[i] = read() ^ a[i - 1];
             ans += c[i & 1][a[i]], c[i & 1][a[i]]++;
         }
         write(ans);
     }
     ```
   - **个人心得**：通过数组记录前缀异或值的出现次数，分为奇数和偶数两种情况，代码简洁且高效。

### 最优关键思路或技巧
1. **前缀异或和**：利用前缀异或和的性质，快速计算子数组的异或和。
2. **奇偶性判断**：通过判断子数组长度的奇偶性，进一步筛选符合条件的数对。
3. **哈希表或数组记录**：使用`map`或数组记录前缀异或值的出现次数，分为奇数和偶数两种情况，提高查找效率。

### 可拓展之处
类似的问题可以扩展到其他位运算操作，如与、或等。此外，可以结合其他数据结构如树状数组、线段树等，进一步优化查询和更新操作。

### 推荐相似题目
1. [P3919 【模板】可持久化线段树 1（可持久化数组）](https://www.luogu.com.cn/problem/P3919)
2. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
3. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)

---
处理用时：41.67秒