# 题目信息

# [USACO23OPEN] Pareidolia S

## 题目描述

### 题目背景

**注意：本题的时间限制为 4 秒，是默认时间限制的 2 倍。**

Pareidolia 是一种现象，指的是人们倾向于在并不真正存在的地方看到熟悉的图案——例如在云中看到一张脸。可以想象，由于农夫 John 经常与奶牛接触，他常常在日常物品中看到与奶牛相关的图案。例如，如果他看到字符串 "bqessiyexbesszieb"，农夫 John 的眼睛会忽略其中的一些字母，而他看到的只是 "bessiebessie"。


给定一个字符串 $s$，令 $B(s)$ 表示通过删除 $s$ 中的零个或多个字符后，能够形成的 "bessie" 的最大重复次数。在上面的例子中，$B(\text{``bqessiyexbesszieb"}) = 2$。

计算 $B(s)$ 是一个有趣的挑战，但农夫 John 对解决一个更有趣的挑战感兴趣：给定一个长度不超过 $3 \cdot 10^5$ 的字符串 $t$，且仅由字符 a-z 组成，计算所有连续子串 $s$ 的 $B(s)$ 之和。

## 说明/提示

对于第一个样例，有 12 个子串恰好包含 $1$ 个 "bessie"，有 $1$ 个子串恰好包含 $2$ 个 "bessie"，因此总数为 $12 \cdot 1 + 1 \cdot 2 = 14$。

- 输入 3-5：字符串长度不超过 $5000$。
- 输入 6-12：没有额外限制。

## 样例 #1

### 输入

```
bessiebessie
```

### 输出

```
14
```

## 样例 #2

### 输入

```
abcdefghssijebessie
```

### 输出

```
28
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕动态规划（dp）展开，通过定义不同的状态数组来解决问题。核心思路是计算以每个位置结尾的子串中 “bessie” 出现的数量，再将所有位置的结果累加得到最终答案。多数题解通过记录 “bessie” 每个字母的位置，找到最后一个 “bessie” 的起始位置，进而得到状态转移方程。部分题解还提到了改变求和顺序、贪心等思想辅助解题。

### 所选题解
- **作者：Nuyoah_awa (赞：14)，4星**
    - **关键亮点**：思路清晰，详细解释了状态数组的定义和转移方程的推导，代码简洁易懂。
- **作者：ylch (赞：3)，4星**
    - **关键亮点**：从改变求和顺序的角度出发，深入剖析了问题的本质，对状态转移方程的解释较为透彻。
- **作者：ForwardStar (赞：2)，4星**
    - **关键亮点**：先给出暴力算法，再逐步优化到动态规划，讲解过程循序渐进，易于理解。

### 重点代码及核心思想
#### Nuyoah_awa 的代码
```cpp
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;

const int N = 3e5 + 5; 
int n, f[7], ans, dp[N];
string s;

signed main()
{
    cin >> s;
    n = s.size(); 
    s = "#" + s;
    for(int i = 1;i <= n;i++)
    {
        if(s[i] == 'b')
            f[1] = i;
        if(s[i] == 'e')
            f[6] = f[5], f[2] = f[1];
        if(s[i] == 's')
            f[4] = f[3], f[3] = f[2];
        if(s[i] == 'i')
            f[5] = f[4];
        dp[i] = dp[f[6] - 1] + f[6];
    }
    for(int i = 1;i <= n;i++)
        ans += dp[i];
    printf("%lld", ans);
    return 0;
}
```
**核心思想**：定义 `dp[i]` 表示以 `i` 结尾的子串中 “bessie” 的数量，`f[i]` 记录到当前字符，最后一个 “bessie” 的前 `i` 个字母中 “b” 出现的位置。通过更新 `f` 数组找到最后一个 “bessie” 的起始位置，进而得到 `dp` 数组的转移方程。

#### ylch 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3e5 + 7;

int len, lst[maxn]; 
ll dp[maxn];

void solve()
{
    string s; cin >> s;
    len = s.size();
    s = " " + s; // 让下标从1开始
    
    for(int i = 1; i <= len; i ++){
        if(s[i] == 'b') lst[1] = i; 
        if(s[i] == 'e') lst[6] = lst[5], lst[2] = lst[1];
        if(s[i] == 's') lst[4] = lst[3], lst[3] = lst[2];
        if(s[i] == 'i') lst[5] = lst[4];
        int j = lst[6];
        dp[i] = dp[j - 1] + j;
    }
    
    ll ans = 0;
    for(int i = 1; i <= len; i ++) ans += dp[i];
    cout << ans << '\n';
}

signed main()
{
    ios :: sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
```
**核心思想**：通过改变求和顺序，将问题转化为求 `dp[i]` 表示在前 `i` 个字符中出现的 “bessie” 的数量。利用 `lst` 数组记录最后一个 “bessie” 每个字母的位置，得到状态转移方程。

#### ForwardStar 的代码
```c++
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdio>
using namespace std;
const int N=3e5+5,inf=2147483647;
char str[N];
int n;
int pos[10];
long long f[N];
long long ans;
int main(){
    scanf("%s",str+1);
    n=strlen(str+1);
    for(int i=1;i<=n;i++){
        if(str[i]=='b')pos[1]=i;
        else if(str[i]=='e'){
            pos[2]=pos[1];
            pos[6]=pos[5];
        }
        else if(str[i]=='s'){
            pos[4]=pos[3];
            pos[3]=pos[2];
        }
        else if(str[i]=='i')pos[5]=pos[4];
        f[i]=f[pos[6]-1]+1ll*pos[6];
        ans+=f[i];
    }
    printf("%lld\n",ans);
    return 0;
}
```
**核心思想**：先给出暴力算法，再通过贪心思想优化到动态规划。定义 `f[i]` 为以第 `i` 位为结尾的所有子串包含 “bessie” 的次数，`pos` 数组记录 “bessie” 每个字母的位置，得到状态转移方程。

### 最优关键思路或技巧
- **动态规划**：通过定义状态数组 `dp` 记录以每个位置结尾的子串中 “bessie” 的数量，利用状态转移方程递推求解。
- **记录位置**：使用额外的数组（如 `f`、`lst`、`pos` 等）记录 “bessie” 每个字母的位置，方便找到最后一个 “bessie” 的起始位置。
- **改变求和顺序**：将枚举子串的双重循环转化为枚举右端点，降低时间复杂度。

### 可拓展之处
同类型题或类似算法套路：
- **子序列计数问题**：可以拓展到计算其他子序列在字符串中出现的次数，如 “abc”、“123” 等。
- **动态规划优化**：对于更复杂的子序列或更长的字符串，可以考虑使用更高级的动态规划优化技巧，如滚动数组、前缀和等。

### 推荐题目
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：考察动态规划求解最大子段和问题。
- [P1049 装箱问题](https://www.luogu.com.cn/problem/P1049)：经典的 0 - 1 背包问题，通过动态规划求解。
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：动态规划的入门题目，通过递推求解路径最大值。

### 个人心得摘录与总结
- **Timmy_**：经过四次来自银组的折磨，终于通过 USACO。总结了解决该问题的三个步骤，先解决简化版问题，再逐步增加复杂度，最后通过循环 `dp` 数组解决最终问题。
**总结**：在解决复杂问题时，可以先从简化版问题入手，逐步分析和解决，最后得到最终答案。同时，多做练习，积累经验，才能在竞赛中取得好成绩。

---
处理用时：49.13秒