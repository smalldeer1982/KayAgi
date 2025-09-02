# 题目信息

# A TRUE Battle

## 题目描述

Alice and Bob are playing a game. There is a list of $ n $ booleans, each of which is either true or false, given as a binary string $ ^{\text{∗}} $ of length $ n $ (where $ \texttt{1} $ represents true, and $ \texttt{0} $ represents false). Initially, there are no operators between the booleans.

Alice and Bob will take alternate turns placing and or or between the booleans, with Alice going first. Thus, the game will consist of $ n-1 $ turns since there are $ n $ booleans. Alice aims for the final statement to evaluate to true, while Bob aims for it to evaluate to false. Given the list of boolean values, determine whether Alice will win if both players play optimally.

To evaluate the final expression, repeatedly perform the following steps until the statement consists of a single true or false:

- If the statement contains an and operator, choose any one and replace the subexpression surrounding it with its evaluation.
- Otherwise, the statement contains an or operator. Choose any one and replace the subexpression surrounding the or with its evaluation.

 For example, the expression true or false and false is evaluated as true or (false and false) $ = $ true or false $ = $ true. It can be shown that the result of any compound statement is unique. $ ^{\text{∗}} $ A binary string is a string that only consists of characters $ \texttt{0} $ and $ \texttt{1} $

## 说明/提示

In the first testcase, Alice can place and between the two booleans. The game ends as there are no other places to place operators, and Alice wins because true and true is true.

In the second testcase, Alice can place or between the middle true and the left false. Bob can place and between the middle true and the right false. The statement false or true and false is false.

Note that these examples may not be the best strategies for either Alice or Bob.

## 样例 #1

### 输入

```
5
2
11
3
010
12
101111111100
10
0111111011
8
01000010```

### 输出

```
YES
NO
YES
YES
NO```

# AI分析结果

### 题目中文重写
# 一场真正的较量

## 题目描述
爱丽丝（Alice）和鲍勃（Bob）正在玩一个游戏。有一个包含 $n$ 个布尔值的列表，每个布尔值要么为真，要么为假，以长度为 $n$ 的二进制字符串 $^{\text{∗}}$ 形式给出（其中 `1` 表示真，`0` 表示假）。初始时，布尔值之间没有运算符。

爱丽丝和鲍勃将轮流在布尔值之间放置“与”（and）或“或”（or）运算符，爱丽丝先行动。由于有 $n$ 个布尔值，所以游戏将进行 $n - 1$ 轮。爱丽丝的目标是使最终的表达式计算结果为真，而鲍勃的目标是使其为假。给定布尔值列表，确定如果双方都采取最优策略，爱丽丝是否会获胜。

为了计算最终表达式的值，重复执行以下步骤，直到表达式只包含一个真或假值：
- 如果表达式中包含“与”运算符，选择任意一个“与”运算符，并用其计算结果替换周围的子表达式。
- 否则，表达式中包含“或”运算符。选择任意一个“或”运算符，并用其计算结果替换周围的子表达式。

例如，表达式 `true or false and false` 计算为 `true or (false and false)` = `true or false` = `true`。可以证明，任何复合表达式的结果都是唯一的。$^{\text{∗}}$ 二进制字符串是只由字符 `0` 和 `1` 组成的字符串。

## 说明/提示
在第一个测试用例中，爱丽丝可以在两个布尔值之间放置“与”运算符。由于没有其他位置可以放置运算符，游戏结束，爱丽丝获胜，因为 `true and true` 为真。

在第二个测试用例中，爱丽丝可以在中间的 `true` 和左边的 `false` 之间放置“或”运算符。鲍勃可以在中间的 `true` 和右边的 `false` 之间放置“与”运算符。表达式 `false or true and false` 为假。

请注意，这些示例可能不是爱丽丝或鲍勃的最佳策略。

## 样例 #1
### 输入
```
5
2
11
3
010
12
101111111100
10
0111111011
8
01000010
```

### 输出
```
YES
NO
YES
YES
NO
```

### 综合分析与结论
这些题解的核心思路基本一致，都是围绕着找出爱丽丝获胜的条件。由于“与”运算优先级高于“或”运算，爱丽丝希望用“或”运算保护 `1`，而鲍勃则用“与”运算破坏。大家都发现了两个关键的获胜条件：一是序列的首尾为 `1`，二是序列中存在连续的两个 `1`。

在算法要点上，题解们都通过遍历序列来检查是否满足上述两个条件。代码实现上，大多使用了循环和条件判断，部分题解还使用了字符串查找函数。

解决的难点在于分析出爱丽丝获胜的条件，特别是连续两个 `1` 这个条件，需要仔细考虑双方的操作策略。

### 题解评分与选择
- **jubaoyi2011**：4星。思路清晰，代码简洁，直接命中关键条件，可读性强。
- **Yxy7952**：4星。详细说明了注意点和操作价值，对思路的解释较为全面，代码规范。
- **HNOIRPplusplus**：4星。不仅给出结论，还进行了充分性和必要性证明，逻辑严谨。

### 最优关键思路或技巧
- **思维方式**：通过分析“与”和“或”运算的优先级以及双方的目标，找出爱丽丝获胜的关键条件，将复杂的博弈问题转化为简单的条件判断。
- **代码实现**：使用循环遍历序列来检查首尾和连续 `1` 的情况，简洁高效。

### 拓展思路
同类型题可能会改变运算符的种类、优先级或者操作规则，但核心思路依然是分析双方的最优策略和获胜条件。可以从运算符的性质出发，寻找关键的局面或条件。

### 洛谷相似题目推荐
- [P1288 取数游戏 II](https://www.luogu.com.cn/problem/P1288)：考察博弈策略和局面分析。
- [P1290 欧几里德的游戏](https://www.luogu.com.cn/problem/P1290)：涉及博弈论和数学推理。
- [P2197 【模板】nim 游戏](https://www.luogu.com.cn/problem/P2197)：经典的博弈论题目，锻炼博弈思维。

### 重点代码及核心思想
#### jubaoyi2011 的代码
```cpp
#include<bits/stdc++.h>
int T,n;
char ch[100005];
signed main(){
    cin>>T;
    while(T--){
        scanf("%d",&n);
        scanf("%s",ch+1);
        bool f=0;
        if(ch[1]=='1'||ch[n]=='1'){
            puts("YES");
            continue;
        }
        for(int i=1;i<n;i++){
            if(ch[i]=='1'&&ch[i+1]=='1'){
                f=1;
                break;
            }
        }
        if(f) puts("YES");
        else puts("NO");
    }
}
```
核心思想：先检查首尾是否为 `1`，若满足则爱丽丝获胜；若不满足，再遍历序列检查是否有连续的两个 `1`，若有则爱丽丝获胜，否则鲍勃获胜。

#### Yxy7952 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int T,n;
string s; 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>T;
    while(T--){
        bool f=0;
        cin>>n>>s;
        if(s[0]=='1'||s[n-1]=='1'){
            cout<<"YES\n";
            continue;
        }
        for(int i=1;i<n;i++){
            if(s[i]=='1'&&s[i-1]=='1'){
                cout<<"YES\n";
                f=1;
                break;
            }
        }
        if(!f) cout<<"NO\n";
    }
    return 0;
}
```
核心思想：与上一题解类似，先检查首尾，再检查连续 `1` 的情况，根据结果输出。

#### HNOIRPplusplus 的代码
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1005;

int a[N];

void solve() {
  int n;
  string s;
  cin >> n >> s;
  s = ' ' + s;
  if(s[1] == '1' || s[n] == '1') {
    cout << "YES\n";
    return;
  }
  for(int i = 1; i < n; i++) {
    if(s[i] == '1' && s[i + 1] == '1') {
      cout << "YES\n";
      return;
    }
  }
  cout << "NO\n";
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    solve();
  }
}
```
核心思想：同样是检查首尾和连续 `1` 的情况，并且给出了结论的充分性和必要性证明。

### 个人心得摘录与总结
题解中未包含个人心得内容。

---
处理用时：39.22秒