# 题目信息

# [ARC154B] New Place

## 题目描述

给你两个长度为 $N$ 的字符串 $S$ 和 $T$，仅包含英文小写字母。

你可以重复进行下面的操作（可以不执行）：

- 将 $S$ 的第一个字符删去，并将这个字符插入到 $S$ 的任意位置。

问你至少执行多少次操作使得 $S$ 与 $T$ 相等。

## 样例 #1

### 输入

```
4

abab

abba```

### 输出

```
2```

## 样例 #2

### 输入

```
3

arc

cra```

### 输出

```
2```

# AI分析结果

### 题目翻译
给你两个长度为 $N$ 的字符串 $S$ 和 $T$，仅包含英文小写字母。

你可以重复进行下面的操作（可以不执行）：

- 将 $S$ 的第一个字符删去，并将这个字符插入到 $S$ 的任意位置。

问你至少执行多少次操作使得 $S$ 与 $T$ 相等。

### 综合分析与结论
这些题解的整体思路较为一致，主要分为两个步骤：
1. **无解判断**：统计 $S$ 和 $T$ 中每个字母的出现次数，若存在某个字母在两个字符串中的数量不同，则一定无解，直接输出 `-1`。
2. **有解计算**：找到 $S$ 中是 $T$ 的子序列的最长后缀子串的长度 $l$，答案即为 $(N - l)$。这是因为保持后面 $l$ 位不动，把前面 $(N - l)$ 位插到这 $l$ 位中间去，所需操作次数最少。

各题解的主要区别在于代码实现细节和一些辅助函数的使用，但核心思路相同。

### 所选题解
- **CarroT1212（4星）**
    - **关键亮点**：思路清晰，代码简洁，对结论的阐述较为详细，通过计数数组统计字母个数，然后从后往前匹配最长后缀子序列。
```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
using namespace std;
const int N=2e5+7;
int n,cnts[129],cntt[129],ans;
char s[N],t[N];
int main() {
    scanf("%d%s%s",&n,s+1,t+1),ans=n;
    for (int i=1;i<=n;i++) cnts[s[i]]++,cntt[t[i]]++;
    for (int i='a';i<='z';i++) if (cnts[i]!=cntt[i]) return printf("-1"),0; // 字母数不相等
    for (int i=n;i;i--) if (s[ans]==t[i]) ans--; // 匹配
    printf("%d",ans);
    return 0;
}
```
- **Register_int（4星）**
    - **关键亮点**：思路简洁明了，代码实现较为高效，使用一个计数数组统计两个字符串中字母的差值，然后从后往前匹配。
```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int MAXN = 2e5 + 10;
 
int n, cnt[26]; char s[MAXN], t[MAXN];
 
int main() {
    scanf("%d%s%s", &n, s + 1, t + 1);
    for (int i = 1; i <= n; i++) cnt[s[i] - 'a']++, cnt[t[i] - 'a']--;
    for (int i = 0; i < 26; i++) if (cnt[i]) return puts("-1"), 0;
    for (int i = n, j = n; i; i--) {
        for (; j && t[j] != s[i]; j--);
        if (!j) return printf("%d", i), 0; j--;
    }
    puts("0");
}
```
- **All_Wrong_Answer（4星）**
    - **关键亮点**：将题目转化为找最长后缀子串的思路明确，使用 `map` 统计字母个数，代码逻辑清晰。
```cpp
#include <bits/stdc++.h>
using namespace std;
char x[200005],y[200005];

map<char,int>s1;
map<char,int>s2;
//用来判断无解 
int n;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x[i];
        s1[x[i]]++; 
    }
    for(int j=1;j<=n;j++){
        cin>>y[j];
        s2[y[j]]++;
    }
    for(int i=int('a');i<=int('z');i++/*遍历每个小写字母*/){
        if(s1[char(i)]!=s2[char(i)]){
            cout<<"-1\n";//有任何一个不同就是无解 
            exit(0);
        }
    }
    int sd=0;
    for(int i=n;i>=1;i--){
        if(x[n-sd]==y[i]) sd++;//找子串 
    }
    cout<<n-sd<<endl;
    return 0;
}
```

### 最优关键思路或技巧
- **无解判断技巧**：通过统计每个字母的出现次数，比较两个字符串中字母数量是否一致，快速判断是否有解。
- **贪心策略**：找到 $S$ 中是 $T$ 的子序列的最长后缀子串，保持该后缀不动，将前面的字符插入到合适位置，可得到最少操作次数。

### 拓展思路
同类型题目可能会有不同的操作规则，例如每次可以交换相邻两个字符、可以删除或添加字符等，但核心思路仍然是先判断是否有解，再寻找最优操作方案。类似的算法套路包括贪心算法、动态规划等，可根据具体题目要求选择合适的算法。

### 推荐题目
1. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：考察对字符串操作和贪心思想的应用。
2. [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)：涉及字符串处理和简单的判断逻辑。
3. [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067)：需要对字符串进行处理和格式化输出。

### 个人心得
题解中未包含个人心得相关内容。

---
处理用时：36.48秒