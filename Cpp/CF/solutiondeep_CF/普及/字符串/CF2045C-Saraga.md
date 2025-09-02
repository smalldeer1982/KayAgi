# 题目信息

# Saraga

## 题目描述

在印尼语中，"sarana olahraga" 是体育设施的意思，缩写为 "saraga"。这个缩写可以通过两种不同的方式组合而成：一种是取 "sarana" 的前缀 "sara" 和 "olahraga" 的后缀 "ga"；另一种是取 "sarana" 的前缀 "sa" 和 "olahraga" 的后缀 "raga"。

如果一个字符串 $S$ 和 $T$ 的缩写有至少两种不同的分割方法，且这些分割能得到一个字符串，使得第一个部分是 $S$ 的前缀，第二个部分是 $T$ 的后缀，我们就称这个缩写是有趣的。

现在，给定两个字符串 $S$ 和 $T$，你需要找出一个最短的有趣缩写，或者判断是否无法构造这样的缩写。

## 说明/提示

样例 1 的解释：

字符串 "saga" 可以分割为 "s" 和 "aga"，或者 "sa" 和 "ga"。因此，"saraga" 和 "saga" 都是有趣的缩写，但 "saga" 更短。

样例 2 的解释：

缩写 "belhijau" 也是一个最短的有趣缩写，所以这个解也是有效的。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
sarana
olahraga```

### 输出

```
saga```

## 样例 #2

### 输入

```
berhiber
wortelhijau```

### 输出

```
berhijau```

## 样例 #3

### 输入

```
icpc
icpc```

### 输出

```
icpc```

## 样例 #4

### 输入

```
icpc
jakarta```

### 输出

```
-1```

# AI分析结果

### 综合分析与结论
这三道题解核心思路一致，均是通过枚举两个字符串中相同的字符，记录 $S$ 中以该字符结尾的最短前缀和 $T$ 中以该字符开头的最短后缀，将它们拼接得到有趣缩写，最后找出最短的有趣缩写。若不存在则输出 -1。

| 作者 | 思路要点 | 算法要点 | 解决难点 | 评分 |
| --- | --- | --- | --- | --- |
| siiii | 利用数组记录 $S$ 中各字符最早出现位置，通过遍历 $T$ 找到满足条件的字符，计算有趣字符串长度 | 数组记录、遍历查找 | 理解有趣字符串长度计算方式 | 3星 |
| lfxxx | 分析出答案串长度与 $\Delta$ 无关，取 $\Delta = 1$ 简化判定，枚举相同字符拼接 | 数组记录、枚举 | 推导答案串长度与 $\Delta$ 无关 | 4星 |
| SuyctidohanQ | 枚举相同字符，记录最短前缀和后缀拼接 | 数组记录、枚举 | 处理无解情况 | 4星 |

### 所选题解
- **lfxxx（4星）**
    - 关键亮点：思路清晰，通过分析得出答案串长度与 $\Delta$ 无关，简化了判定过程，代码可读性高。
```cpp
#include<bits/stdc++.h>
using namespace std;
int pre[26],suf[26];
string S,T;
int ans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    memset(pre,0x3f3f3f3f,sizeof(pre));
    memset(suf,0x3f3f3f3f,sizeof(suf));
    cin>>S>>T;
    for(int i=2;i<=S.size();i++){
        if(pre[S[i-1]-'a']==0x3f3f3f3f) pre[S[i-1]-'a']=i;
    }
    for(int i=T.size()-1;i>=1;i--){
        if(suf[T[i-1]-'a']==0x3f3f3f3f) suf[T[i-1]-'a']=T.size()-i+1;
    }
    ans=0x3f3f3f3f;
    for(int i=0;i<26;i++){
        ans=min(ans,pre[i]+suf[i]);
    }
    if(ans>=0x3f3f3f3f){
        cout<<"-1\n";
    }else{
        for(int i=0;i<26;i++){
            if(pre[i]+suf[i]==ans){
                for(int j=1;j<=pre[i];j++) cout<<S[j-1];
                for(int j=T.size()-suf[i]+2;j<=T.size();j++) cout<<T[j-1];
                return 0;
            }
        }
    }
    return 0;
}
```
核心实现思想：使用 `pre` 数组记录 $S$ 中以每个字符结尾的最短前缀长度，`suf` 数组记录 $T$ 中以每个字符开头的最短后缀长度，枚举所有字符，找出最短的拼接长度。

- **SuyctidohanQ（4星）**
    - 关键亮点：代码简洁，逻辑清晰，对无解情况处理明确。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 26 + 10, INF = 0x3f3f3f3f;
int a[MAXN], b[MAXN], ans = INF;
string S, T;
int main () {
    memset (a, INF,sizeof(a)); memset (b, INF,sizeof(b));
    cin >> S >> T;
    for (int i = 2; i <= S.size (); i ++) 
        if (a[S[i - 1] - 'a'] == INF) a[S[i - 1] - 'a'] = i;
    for (int i = T.size () - 1; i >= 1; i --)
        if (b[T[i - 1] - 'a'] == INF) b[T[i - 1] - 'a'] = T.size () - i + 1;
    for (int i = 0; i < 26; i ++) ans = min (ans, a[i] + b[i]);
    if (ans >= INF) cout << -1 << endl;
    else {
        for (int i = 0; i < 26; i ++) {
            if (a[i] + b[i] == ans) {
                for (int j = 1; j <= a[i]; j ++) cout << S[j - 1];
                for (int j = T.size () - b[i] + 2; j <= T.size (); j ++) cout << T[j - 1];
                cout << endl;
                return 0;
            }
        }
    }
    return 0;
}
```
核心实现思想：与 lfxxx 题解类似，使用数组记录最短前缀和后缀长度，枚举字符找出最短拼接长度，处理无解情况。

### 最优关键思路或技巧
- 利用数组记录每个字符在 $S$ 中的最短前缀和在 $T$ 中的最短后缀，通过枚举字符找出最短拼接结果，将复杂的字符串拼接问题转化为简单的数组操作。
- 分析出答案串长度与 $\Delta$ 无关，取 $\Delta = 1$ 简化判定过程。

### 拓展思路
同类型题目可能会改变字符串拼接的规则，如要求拼接后的字符串满足某种特定的模式或条件。类似算法套路可以应用在字符串匹配、子串查找等问题中，通过记录关键信息（如字符出现位置、子串长度等），枚举可能的情况来找到最优解。

### 洛谷相似题目推荐
1. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)：涉及数组记录和枚举查找。
2. [P1427 小鱼的数字游戏](https://www.luogu.com.cn/problem/P1427)：简单的字符串处理和输出。
3. [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)：字符串匹配和规则判断。

### 个人心得
题解中未包含个人心得。

---
处理用时：41.08秒