# 题目信息

# Plus-Minus Split

## 题目描述

You are given a string $ s $ of length $ n $ consisting of characters "+" and "-". $ s $ represents an array $ a $ of length $ n $ defined by $ a_i=1 $ if $ s_i= $ "+" and $ a_i=-1 $ if $ s_i= $ "-".

You will do the following process to calculate your penalty:

1. Split $ a $ into non-empty arrays $ b_1,b_2,\ldots,b_k $ such that $ b_1+b_2+\ldots+b_k=a^\dagger $ , where $ + $ denotes array concatenation.
2. The penalty of a single array is the absolute value of its sum multiplied by its length. In other words, for some array $ c $ of length $ m $ , its penalty is calculated as $ p(c)=|c_1+c_2+\ldots+c_m| \cdot m $ .
3. The total penalty that you will receive is $ p(b_1)+p(b_2)+\ldots+p(b_k) $ .

If you perform the above process optimally, find the minimum possible penalty you will receive.

 $ ^\dagger $ Some valid ways to split $ a=[3,1,4,1,5] $ into $ (b_1,b_2,\ldots,b_k) $ are $ ([3],[1],[4],[1],[5]) $ , $ ([3,1],[4,1,5]) $ and $ ([3,1,4,1,5]) $ while some invalid ways to split $ a $ are $ ([3,1],[1,5]) $ , $ ([3],[\,],[1,4],[1,5]) $ and $ ([3,4],[5,1,1]) $ .

## 说明/提示

In the first test case, we have $ a=[1] $ . We can split array $ a $ into $ ([1]) $ . Then, the sum of penalties of the subarrays is $ p([1]) = 1 $ .

In the second test case, we have $ a=[-1,-1,-1,-1,-1] $ . We can split array $ a $ into $ ([-1],[-1],[-1],[-1],[-1]) $ . Then, the sum of penalties of the subarrays is $ p([-1]) + p([-1]) + p([-1]) + p([-1]) + p([-1]) = 1 + 1 + 1 + 1 + 1 = 5 $ .

In the third test case, we have $ a=[1,-1,1,-1,1,-1] $ . We can split array $ a $ into $ ([1,-1,1,-1],[1,-1]) $ . Then, the sum of penalties of the subarrays is $ p([1,-1,1,-1]) + p([1,-1]) = 0 + 0 = 0 $ .

## 样例 #1

### 输入

```
5
1
+
5
-----
6
+-+-+-
10
--+++++++-
20
+---++++-+++++---++-```

### 输出

```
1
5
0
4
4```

# AI分析结果

【中文重写】
# 正负拆分

## 题目描述
给定一个长度为 $n$ 的字符串 $s$，由字符 `+` 和 `-` 组成。$s$ 表示一个长度为 $n$ 的数组 $a$，若 $s_i =$ `+`，则 $a_i = 1$；若 $s_i =$ `-`，则 $a_i = -1$。

你将执行以下过程来计算惩罚值：
1. 将数组 $a$ 拆分为非空数组 $b_1, b_2, \ldots, b_k$，使得 $b_1 + b_2 + \ldots + b_k = a^\dagger$，其中 `+` 表示数组拼接。
2. 单个数组的惩罚值是其元素和的绝对值乘以其长度。换句话说，对于某个长度为 $m$ 的数组 $c$，其惩罚值计算为 $p(c) = |c_1 + c_2 + \ldots + c_m| \cdot m$。
3. 你将得到的总惩罚值为 $p(b_1) + p(b_2) + \ldots + p(b_k)$。

如果你能最优地执行上述过程，请找出你将得到的最小惩罚值。

$^\dagger$ 将 $a = [3, 1, 4, 1, 5]$ 拆分为 $(b_1, b_2, \ldots, b_k)$ 的一些有效方式有 $([3], [1], [4], [1], [5])$、$([3, 1], [4, 1, 5])$ 和 $([3, 1, 4, 1, 5])$，而一些无效的拆分方式有 $([3, 1], [1, 5])$、$([3], [], [1, 4], [1, 5])$ 和 $([3, 4], [5, 1, 1])$。

## 说明/提示
在第一个测试用例中，我们有 $a = [1]$。我们可以将数组 $a$ 拆分为 $([1])$。那么，子数组的惩罚值之和为 $p([1]) = 1$。

在第二个测试用例中，我们有 $a = [-1, -1, -1, -1, -1]$。我们可以将数组 $a$ 拆分为 $([-1], [-1], [-1], [-1], [-1])$。那么，子数组的惩罚值之和为 $p([-1]) + p([-1]) + p([-1]) + p([-1]) + p([-1]) = 1 + 1 + 1 + 1 + 1 = 5$。

在第三个测试用例中，我们有 $a = [1, -1, 1, -1, 1, -1]$。我们可以将数组 $a$ 拆分为 $([1, -1, 1, -1], [1, -1])$。那么，子数组的惩罚值之和为 $p([1, -1, 1, -1]) + p([1, -1]) = 0 + 0 = 0$。

## 样例 #1
### 输入
```
5
1
+
5
-----
6
+-+-+-
10
--+++++++-
20
+---++++-+++++---++-
```
### 输出
```
1
5
0
4
4
```

【算法分类】
贪心

【综合分析与结论】
这些题解的核心思路都是尽可能地让子数组的和为 0，以减少总惩罚值。具体做法有统计 `+` 和 `-` 的数量并计算差值的绝对值、使用栈来模拟抵消过程、利用动态规划记录最小惩罚值等。
- **思路对比**：多数题解采用贪心策略，通过抵消 `+` 和 `-` 来使和为 0，剩余的单独成段；Zemu_Ooo 的题解使用动态规划，考虑所有可能的分割方式。
- **算法要点**：贪心算法主要是统计 `+` 和 `-` 的数量，计算差值绝对值；动态规划则是维护前缀和和最小惩罚值数组。
- **解决难点**：关键在于理解如何组合 `+` 和 `-` 使和为 0，以及处理剩余元素的最优分割方式。

【所选题解】
- **xu_zhihao（4星）**
  - **关键亮点**：思路清晰，代码简洁，直接统计 `+` 和 `-` 的数量，通过计算差值得到结果。
- **WAis_WonderfulAnswer（4星）**
  - **关键亮点**：思路明确，代码简洁，直接计算数组元素和的绝对值得到答案。
- **Zemu_Ooo（4星）**
  - **关键亮点**：使用动态规划解决问题，思路独特，通过维护前缀和和最小惩罚值数组找到最优解。

【重点代码】
- **xu_zhihao**
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[5010];
int i;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        scanf("%d",&n);
        scanf("%s",s);
        int jia=0,jian=0;
        int mp=0;
        for(i=0;i<n;i++)
        {
            if(s[i]=='+')
            {
                jia++;
            }
            else
            {
                jian++;
            }
        }
        cout<<n-min(jia,jian)*2<<endl;
    }	
}
```
**核心实现思想**：统计字符串中 `+` 和 `-` 的数量，用总长度减去能抵消的数量的两倍，得到最小惩罚值。

- **WAis_WonderfulAnswer**
```cpp
#include<bits/stdc++.h>
using namespace std;
int _;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>_;
    while (_--)
    {
        int n;
        string s;
        cin>>n>>s;
        int tmp=0;
        for (int i=0;i<(int)s.size();i++) tmp+=(s[i]=='+'?1:-1);
        cout<<abs(tmp)<<'\n';
    }
    return 0;
}
```
**核心实现思想**：计算数组元素的和，取其绝对值作为最小惩罚值。

- **Zemu_Ooo**
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <climits>

using namespace std;

int minPenal(const string& s, int n) {
    vector<int> dp(n + 1, 0);
    unordered_map<int, int> lastSum;  // 存储前缀和最后出现
    lastSum[0] = 0;  // 的位置为0
    int sum = 0;

    for (int i = 1; i <= n; ++i) {
        sum += (s[i - 1] == '+' ? 1 : -1);
        if (lastSum.count(sum)) {
            dp[i] = dp[lastSum[sum]];
        } else {
            dp[i] = dp[i - 1] + 1;
        }
        lastSum[sum] = i;
    }
    return dp[n];
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;
        cout << minPenal(s, n) << endl;
    }
    return 0;
}
```
**核心实现思想**：使用动态规划，维护前缀和和最小惩罚值数组，通过查找前缀和相同的位置来更新最小惩罚值。

【关键思路或技巧】
- 贪心策略：尽可能让子数组的和为 0，剩余元素单独成段。
- 动态规划：通过维护前缀和和最小惩罚值数组，找到最优分割方式。

【拓展思路】
同类型题可以考虑其他元素值的数组分割问题，或者改变惩罚值的计算方式。类似算法套路包括贪心算法中的区间合并、动态规划中的状态转移等。

【推荐题目】
- P1223 排队接水
- P1090 合并果子
- P1803 凌乱的yyy / 线段覆盖

【个人心得】
Zemu_Ooo 提到交了一遍发现超时，然后简单地优化下前缀和的计算，并减少不必要的哈希查找，避免了哈希表操作的开销，成功解决了超时问题。这提示我们在使用哈希表时要注意其操作开销，必要时进行优化。 

---
处理用时：47.04秒