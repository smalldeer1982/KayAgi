# 题目信息

# Strong Password

## 题目描述

Monocarp finally got the courage to register on ForceCoders. He came up with a handle but is still thinking about the password.

He wants his password to be as strong as possible, so he came up with the following criteria:

- the length of the password should be exactly $ m $ ;
- the password should only consist of digits from $ 0 $ to $ 9 $ ;
- the password should not appear in the password database (given as a string $ s $ ) as a subsequence (not necessarily contiguous).

Monocarp also came up with two strings of length $ m $ : $ l $ and $ r $ , both consisting only of digits from $ 0 $ to $ 9 $ . He wants the $ i $ -th digit of his password to be between $ l_i $ and $ r_i $ , inclusive.

Does there exist a password that fits all criteria?

## 说明/提示

In the first testcase, Monocarp can choose password "50". It doesn't appear in $ s $ as a subsequence.

In the second testcase, all combinations of three digits, each of them being from $ 1 $ to $ 4 $ , fit the criteria on $ l $ and $ r $ . However, all of them appear in $ s $ as subsequences. For example, "314" appears at positions $ [3, 5, 12] $ and "222" appears at positions $ [2, 6, 10] $ .

In the third testcase, Monocarp can choose password "4321". Actually, that is the only password that fits the criteria on $ l $ and $ r $ . Luckily, it doesn't appear in $ s $ as a subsequence.

In the fourth testcase, only "49" and "59" fit the criteria on $ l $ and $ r $ . Both of them appear in $ s $ as subsequences.

In the fifth testcase, Monocarp can choose password "11".

## 样例 #1

### 输入

```
5
88005553535123456
2
50
56
123412341234
3
111
444
1234
4
4321
4321
459
2
49
59
00010
2
10
11```

### 输出

```
YES
NO
YES
NO
YES```

# AI分析结果

### 题目内容重写
# 强密码

## 题目描述

Monocarp终于鼓起勇气在ForceCoders上注册。他想出了一个用户名，但仍在考虑密码。

他希望自己的密码尽可能强，因此提出了以下标准：

- 密码的长度必须恰好为 $ m $；
- 密码只能由 $ 0 $ 到 $ 9 $ 的数字组成；
- 密码不能出现在密码数据库（给定为一个字符串 $ s $）中作为子序列（不一定是连续的）。

Monocarp还提出了两个长度为 $ m $ 的字符串 $ l $ 和 $ r $，它们都由 $ 0 $ 到 $ 9 $ 的数字组成。他希望密码的第 $ i $ 位数字在 $ l_i $ 和 $ r_i $ 之间，包括 $ l_i $ 和 $ r_i $。

是否存在一个符合所有标准的密码？

## 说明/提示

在第一个测试用例中，Monocarp可以选择密码 "50"。它没有在 $ s $ 中作为子序列出现。

在第二个测试用例中，所有由 $ 1 $ 到 $ 4 $ 的三个数字组合都符合 $ l $ 和 $ r $ 的标准。然而，它们都在 $ s $ 中作为子序列出现。例如，"314" 出现在位置 $ [3, 5, 12] $，"222" 出现在位置 $ [2, 6, 10] $。

在第三个测试用例中，Monocarp可以选择密码 "4321"。实际上，这是唯一符合 $ l $ 和 $ r $ 标准的密码。幸运的是，它没有在 $ s $ 中作为子序列出现。

在第四个测试用例中，只有 "49" 和 "59" 符合 $ l $ 和 $ r $ 的标准。它们都在 $ s $ 中作为子序列出现。

在第五个测试用例中，Monocarp可以选择密码 "11"。

## 样例 #1

### 输入

```
5
88005553535123456
2
50
56
123412341234
3
111
444
1234
4
4321
4321
459
2
49
59
00010
2
10
11```

### 输出

```
YES
NO
YES
NO
YES```

### 算法分类
贪心

### 题解分析与结论
本题的核心在于判断是否存在一个密码，该密码的长度为 $ m $，且每一位数字在给定的范围内，同时该密码不能是字符串 $ s $ 的子序列。由于直接枚举所有可能的密码不现实，因此需要采用贪心策略来优化搜索过程。

### 所选题解
1. **作者：Wf_yjqd (赞：9)**  
   - **星级：4**  
   - **关键亮点**：使用双指针策略，通过贪心思想找到每个位置的最优选择，确保密码不是 $ s $ 的子序列。代码简洁，思路清晰。  
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n&&j<=m;i++){
         if(a[i]>=l[j]&&a[i]<=r[j])
             vis[a[i]]=1;
         if(vis.count()==r[j]-l[j]+1){
             vis.reset();
             j++;
         }
     }
     puts(j!=m+1?"YES":"NO");
     ```

2. **作者：spider_oyster (赞：0)**  
   - **星级：4**  
   - **关键亮点**：使用 `set` 维护每种数字出现的位置，通过 `upper_bound` 快速找到下一个匹配位置，确保密码不是 $ s $ 的子序列。代码简洁，效率高。  
   - **核心代码**：
     ```cpp
     for(int i=0;i<m;i++){
         int tmp=0;
         for(int j=l[i]-'0';j<=r[i]-'0';j++){
             auto it=p[j].upper_bound(lst);
             if(it==p[j].end()) {puts("YES");return;}
             tmp=max(tmp,*it);
         }
         lst=max(lst,tmp);
     }
     puts("NO");
     ```

3. **作者：EuphoricStar (赞：0)**  
   - **星级：4**  
   - **关键亮点**：通过子序列自动机和动态规划结合，确保密码不是 $ s $ 的子序列。思路新颖，代码实现清晰。  
   - **核心代码**：
     ```cpp
     for(int i=1;i<=m;i++){
         for(int j=1;j<=n+1;j++){
             for(int d=l[i]-'0';d<=r[i]-'0';d++){
                 int nxt_pos = nxt[j][d];
                 if(nxt_pos <= n) f[i][nxt_pos] |= f[i-1][j];
             }
         }
     }
     ```

### 最优关键思路
1. **贪心策略**：通过双指针或 `set` 维护每个数字的出现位置，确保密码的每一位都能在 $ s $ 中找到匹配位置，且匹配位置尽可能靠后。
2. **子序列自动机**：通过预处理 $ s $ 中每个数字的出现位置，快速找到下一个匹配位置，减少搜索时间。

### 可拓展之处
类似的问题可以扩展到其他字符串匹配问题，如判断一个字符串是否是另一个字符串的子序列，或者在某些限制条件下构造字符串。

### 推荐题目
1. [P1036 选数](https://www.luogu.com.cn/problem/P1036)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：33.34秒