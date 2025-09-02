# 题目信息

# Catching Cheaters

## 题目描述

You are given two strings $ A $ and $ B $ representing essays of two students who are suspected cheaters. For any two strings $ C $ , $ D $ we define their similarity score $ S(C,D) $ as $ 4\cdot LCS(C,D) - |C| - |D| $ , where $ LCS(C,D) $ denotes the length of the Longest Common Subsequence of strings $ C $ and $ D $ .

You believe that only some part of the essays could have been copied, therefore you're interested in their substrings.

Calculate the maximal similarity score over all pairs of substrings. More formally, output maximal $ S(C, D) $ over all pairs $ (C, D) $ , where $ C $ is some substring of $ A $ , and $ D $ is some substring of $ B $ .

If $ X $ is a string, $ |X| $ denotes its length.

A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

A string $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters.

Pay attention to the difference between the substring and subsequence, as they both appear in the problem statement.

You may wish to read the [Wikipedia page about the Longest Common Subsequence problem](https://en.wikipedia.org/wiki/Longest_common_subsequence_problem).

## 说明/提示

For the first case:

abb from the first string and abab from the second string have LCS equal to abb.

The result is $ S(abb, abab) = (4 \cdot |abb| $ ) - $ |abb| $ - $ |abab| $ = $ 4 \cdot 3 - 3 - 4 = 5 $ .

## 样例 #1

### 输入

```
4 5
abba
babab```

### 输出

```
5```

## 样例 #2

### 输入

```
8 10
bbbbabab
bbbabaaaaa```

### 输出

```
12```

## 样例 #3

### 输入

```
7 7
uiibwws
qhtkxcn```

### 输出

```
0```

# AI分析结果

### 题目翻译
你得到了两个字符串 $A$ 和 $B$，它们分别代表两个被怀疑作弊的学生的论文。对于任意两个字符串 $C$ 和 $D$，我们定义它们的相似度分数 $S(C, D)$ 为 $4\cdot LCS(C, D) - |C| - |D|$，其中 $LCS(C, D)$ 表示字符串 $C$ 和 $D$ 的最长公共子序列的长度。

你认为论文中可能只有部分内容被抄袭，因此你对它们的子串感兴趣。

计算所有子串对的最大相似度分数。更正式地说，输出所有子串对 $(C, D)$ 中的最大 $S(C, D)$，其中 $C$ 是 $A$ 的某个子串，$D$ 是 $B$ 的某个子串。

如果 $X$ 是一个字符串，$|X|$ 表示它的长度。

如果字符串 $a$ 可以通过从字符串 $b$ 的开头删除若干（可能为零个或全部）字符以及从结尾删除若干（可能为零个或全部）字符得到，那么 $a$ 是 $b$ 的子串。

如果字符串 $a$ 可以通过从字符串 $b$ 中删除若干（可能为零个或全部）字符得到，那么 $a$ 是 $b$ 的子序列。

请注意子串和子序列的区别，因为它们都出现在问题描述中。

你可能希望阅读[关于最长公共子序列问题的维基百科页面](https://en.wikipedia.org/wiki/Longest_common_subsequence_problem)。

### 算法分类
动态规划

### 综合分析与结论
这些题解的核心思路都是使用动态规划来解决问题。定义状态 $dp[i][j]$ 表示考虑到 $A$ 中以第 $i$ 位为最后一位，$B$ 中以第 $j$ 位为最后一位的子串的最大相似度。对于状态转移，当 $A[i]=B[j]$ 时，$LCS$ 长度加 1，对答案的贡献为 $4 - 1 - 1 = 2$，即 $dp[i][j]=dp[i - 1][j - 1] + 2$；当 $A[i]\ne B[j]$ 时，子串长度加 1 对答案的贡献为 -1，即 $dp[i][j]=\max(dp[i - 1][j], dp[i][j - 1]) - 1$。最后在所有状态中取最大值作为最终答案。

不同题解的差异主要在于状态转移方程的细节处理，如是否与 0 取 $\max$ 等，但整体思路一致。

### 所选题解
- **作者：AFOier (赞：8)，4星**
    - **关键亮点**：思路清晰，代码简洁，直接给出状态转移方程并实现，易于理解。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n, m, dp[5011][5011], ans;
char a[5011], b[5011];
void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= m; i++) cin >> b[i];
    for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++) {
        if(a[i] == b[j]) dp[i][j] = dp[i-1][j-1] + 2;
        dp[i][j] = max(dp[i][j], dp[i-1][j] - 1);
        dp[i][j] = max(dp[i][j], dp[i][j-1] - 1);
        ans = max(ans, dp[i][j]);
    }
    cout << ans << endl;
}
int main() {
    int T = 1;
    while(T--) solve();
    return 0;
}
```
    - **核心实现思想**：通过两层循环遍历两个字符串的所有位置，根据当前字符是否相等进行状态转移，同时更新最大相似度。
- **作者：Eddie08012025 (赞：6)，4星**
    - **关键亮点**：详细讲解了状态转移方程的推导过程，代码规范，注释清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,dp[5001][5001],maxn;//dp[i][j]代表s前i个字母与t前j个字母的最大相似度 
char s[5001],t[5001];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>a>>b;
    for(int i=1;i<=a;i++)cin>>s[i];
    for(int i=1;i<=b;i++)cin>>t[i];
    for(int i=1;i<=a;i++){
        for(int j=1;j<=b;j++){
            if(s[i]==t[j])dp[i][j]=dp[i-1][j-1]+2;
            else dp[i][j]=max(0,max(dp[i-1][j]-1,dp[i][j-1]-1));
            maxn=max(maxn,dp[i][j]);
        }
    }
    cout<<maxn;
    return 0;
}
```
    - **核心实现思想**：同样使用两层循环遍历，根据字符是否相等进行状态转移，并且在 $A[i]\ne B[j]$ 时与 0 取 $\max$，最后更新最大相似度。
- **作者：Eibon (赞：4)，4星**
    - **关键亮点**：先回顾正常的 LCS 转移方程，再推导出本题的转移方程，逻辑连贯。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=5000+5;
int n,m,c,ans;
int dp[maxn][maxn],num1[maxn],num2[maxn];
char a[maxn],b[maxn];
signed main()
{
    scanf("%lld%lld",&n,&m);
    scanf("%s%s",a+1,b+1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i]==b[j]){
                dp[i][j]=dp[i-1][j-1]+2;
            }
            dp[i][j]=max(dp[i][j],max(dp[i][j-1],dp[i-1][j])-1);
            ans=max(ans,dp[i][j]);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```
    - **核心实现思想**：两层循环遍历，根据字符是否相等进行状态转移，更新最大相似度。

### 最优关键思路或技巧
- **动态规划思想**：通过定义合适的状态 $dp[i][j]$，将问题分解为子问题，利用子问题的解来求解原问题。
- **状态转移方程**：根据字符是否相等，分别考虑 $LCS$ 长度和子串长度的变化对答案的影响，得到简洁的状态转移方程。

### 可拓展之处
同类型题或类似算法套路：
- 最长公共子串问题：与本题类似，但要求子串是连续的，状态转移方程会有所不同。
- 编辑距离问题：计算将一个字符串转换为另一个字符串所需的最少操作次数，也可以使用动态规划解决。
- 最大子段和问题：求数组中连续子段的最大和，同样可以用动态规划的思想来解决。

### 推荐洛谷题目
- [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)
- [P2758 编辑距离](https://www.luogu.com.cn/problem/P2758)
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)

### 个人心得摘录与总结
- **作者：vectorwyx**：提到一开始想求 LCS 但卡在那里，后来发现 LCS 时间复杂度太高会 TLE，从而想到用动态规划解决问题。总结是在解题时不能局限于一种思路，当发现某种方法不可行时要及时转换思路。

---
处理用时：52.19秒