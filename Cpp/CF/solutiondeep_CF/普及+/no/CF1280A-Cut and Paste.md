# 题目信息

# Cut and Paste

## 题目描述

We start with a string $ s $ consisting only of the digits $ 1 $ , $ 2 $ , or $ 3 $ . The length of $ s $ is denoted by $ |s| $ . For each $ i $ from $ 1 $ to $ |s| $ , the $ i $ -th character of $ s $ is denoted by $ s_i $ .

There is one cursor. The cursor's location $ \ell $ is denoted by an integer in $ \{0, \ldots, |s|\} $ , with the following meaning:

- If $ \ell = 0 $ , then the cursor is located before the first character of $ s $ .
- If $ \ell = |s| $ , then the cursor is located right after the last character of $ s $ .
- If $ 0 < \ell < |s| $ , then the cursor is located between $ s_\ell $ and $ s_{\ell+1} $ .

We denote by $ s_\text{left} $ the string to the left of the cursor and $ s_\text{right} $ the string to the right of the cursor.

We also have a string $ c $ , which we call our clipboard, which starts out as empty. There are three types of actions:

- The Move action. Move the cursor one step to the right. This increments $ \ell $ once.
- The Cut action. Set $ c \leftarrow s_\text{right} $ , then set $ s \leftarrow s_\text{left} $ .
- The Paste action. Append the value of $ c $ to the end of the string $ s $ . Note that this doesn't modify $ c $ .

The cursor initially starts at $ \ell = 0 $ . Then, we perform the following procedure:

1. Perform the Move action once.
2. Perform the Cut action once.
3. Perform the Paste action $ s_\ell $ times.
4. If $ \ell = x $ , stop. Otherwise, return to step 1.

You're given the initial string $ s $ and the integer $ x $ . What is the length of $ s $ when the procedure stops? Since this value may be very large, only find it modulo $ 10^9 + 7 $ .

It is guaranteed that $ \ell \le |s| $ at any time.

## 说明/提示

Let's illustrate what happens with the first test case. Initially, we have $ s =  $ 231. Initially, $ \ell = 0 $ and $ c = \varepsilon $ (the empty string). The following things happen if we follow the procedure above:

- Step 1, Move once: we get $ \ell = 1 $ .
- Step 2, Cut once: we get $ s =  $ 2 and $ c =  $ 31.
- Step 3, Paste $ s_\ell =  $ 2 times: we get $ s =  $ 23131.
- Step 4: $ \ell = 1 \not= x = 5 $ , so we return to step 1.
- Step 1, Move once: we get $ \ell = 2 $ .
- Step 2, Cut once: we get $ s =  $ 23 and $ c =  $ 131.
- Step 3, Paste $ s_\ell =  $ 3 times: we get $ s =  $ 23131131131.
- Step 4: $ \ell = 2 \not= x = 5 $ , so we return to step 1.
- Step 1, Move once: we get $ \ell = 3 $ .
- Step 2, Cut once: we get $ s =  $ 231 and $ c =  $ 31131131.
- Step 3, Paste $ s_\ell =  $ 1 time: we get $ s =  $ 23131131131.
- Step 4: $ \ell = 3 \not= x = 5 $ , so we return to step 1.
- Step 1, Move once: we get $ \ell = 4 $ .
- Step 2, Cut once: we get $ s =  $ 2313 and $ c =  $ 1131131.
- Step 3, Paste $ s_\ell =  $ 3 times: we get $ s =  $ 2313113113111311311131131.
- Step 4: $ \ell = 4 \not= x = 5 $ , so we return to step 1.
- Step 1, Move once: we get $ \ell = 5 $ .
- Step 2, Cut once: we get $ s =  $ 23131 and $ c =  $ 13113111311311131131.
- Step 3, Paste $ s_\ell =  $ 1 times: we get $ s =  $ 2313113113111311311131131.
- Step 4: $ \ell = 5 = x $ , so we stop.

At the end of the procedure, $ s $ has length $ 25 $ .

## 样例 #1

### 输入

```
4
5
231
7
2323
6
333
24
133321333
```

### 输出

```
25
1438
1101
686531475
```

# AI分析结果

### 题目中文重写
# 剪切与粘贴

## 题目描述
我们从一个仅由数字 1、2 或 3 组成的字符串 $ s $ 开始。$ s $ 的长度记为 $ |s| $。对于从 1 到 $ |s| $ 的每个 $ i $，$ s $ 的第 $ i $ 个字符记为 $ s_i $。

有一个光标。光标的位置 $ \ell $ 用一个在 $ \{0, \ldots, |s|\} $ 中的整数表示，其含义如下：
- 如果 $ \ell = 0 $，则光标位于 $ s $ 的第一个字符之前。
- 如果 $ \ell = |s| $，则光标位于 $ s $ 的最后一个字符之后。
- 如果 $ 0 < \ell < |s| $，则光标位于 $ s_\ell $ 和 $ s_{\ell+1} $ 之间。

我们用 $ s_\text{left} $ 表示光标左侧的字符串，用 $ s_\text{right} $ 表示光标右侧的字符串。

我们还有一个字符串 $ c $，我们称之为剪贴板，它最初是空的。有三种类型的操作：
- 移动操作。将光标向右移动一步。这会使 $ \ell $ 增加 1。
- 剪切操作。将 $ c \leftarrow s_\text{right} $，然后将 $ s \leftarrow s_\text{left} $。
- 粘贴操作。将 $ c $ 的值追加到字符串 $ s $ 的末尾。请注意，这不会修改 $ c $。

光标最初位于 $ \ell = 0 $。然后，我们执行以下过程：
1. 执行一次移动操作。
2. 执行一次剪切操作。
3. 执行 $ s_\ell $ 次粘贴操作。
4. 如果 $ \ell = x $，则停止。否则，返回步骤 1。

给定初始字符串 $ s $ 和整数 $ x $。当过程停止时，$ s $ 的长度是多少？由于这个值可能非常大，只需求出它对 $ 10^9 + 7 $ 取模的结果。

保证在任何时候 $ \ell \le |s| $。

## 说明/提示
让我们来说明第一个测试用例中发生的情况。最初，我们有 $ s = $ 231。最初，$ \ell = 0 $ 且 $ c = \varepsilon $（空字符串）。如果我们按照上述过程执行，会发生以下情况：
- 步骤 1，移动一次：我们得到 $ \ell = 1 $。
- 步骤 2，剪切一次：我们得到 $ s = $ 2 且 $ c = $ 31。
- 步骤 3，粘贴 $ s_\ell = $ 2 次：我们得到 $ s = $ 23131。
- 步骤 4：$ \ell = 1 \not= x = 5 $，所以我们返回步骤 1。
- 步骤 1，移动一次：我们得到 $ \ell = 2 $。
- 步骤 2，剪切一次：我们得到 $ s = $ 23 且 $ c = $ 131。
- 步骤 3，粘贴 $ s_\ell = $ 3 次：我们得到 $ s = $ 23131131131。
- 步骤 4：$ \ell = 2 \not= x = 5 $，所以我们返回步骤 1。
- 步骤 1，移动一次：我们得到 $ \ell = 3 $。
- 步骤 2，剪切一次：我们得到 $ s = $ 231 且 $ c = $ 31131131。
- 步骤 3，粘贴 $ s_\ell = $ 1 次：我们得到 $ s = $ 23131131131。
- 步骤 4：$ \ell = 3 \not= x = 5 $，所以我们返回步骤 1。
- 步骤 1，移动一次：我们得到 $ \ell = 4 $。
- 步骤 2，剪切一次：我们得到 $ s = $ 2313 且 $ c = $ 1131131。
- 步骤 3，粘贴 $ s_\ell = $ 3 次：我们得到 $ s = $ 2313113113111311311131131。
- 步骤 4：$ \ell = 4 \not= x = 5 $，所以我们返回步骤 1。
- 步骤 1，移动一次：我们得到 $ \ell = 5 $。
- 步骤 2，剪切一次：我们得到 $ s = $ 23131 且 $ c = $ 13113111311311131131。
- 步骤 3，粘贴 $ s_\ell = $ 1 次：我们得到 $ s = $ 2313113113111311311131131。
- 步骤 4：$ \ell = 5 = x $，所以我们停止。

在过程结束时，$ s $ 的长度为 25。

## 样例 #1

### 输入
```
4
5
231
7
2323
6
333
24
133321333
```

### 输出
```
25
1438
1101
686531475
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟题目中的剪切、粘贴操作。由于字符串长度可能呈指数级增长，直接模拟会导致超时，因此各题解都采用了只维护前 $x$ 个字符，其余部分只记录长度的优化策略。在处理过程中，需要注意取模操作和负数取模的问题。

### 所选题解
- **ZLCT（4星）**
    - **关键亮点**：思路清晰，代码简洁，对取模操作的处理较为规范。
    - **个人心得**：刚看到题会觉得需要类似于等比数列之类的思想，结果一看数据范围发现 $x\le10^6$，就可以直接暴力模拟。同时指出不能判断 $ans$ 是否小于 $x$，因为在取模以后可能数值变小。

### 重点代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int x,a[1123456];
string s;
int ans,len;
void solve(){
    cin>>x>>s;
    len=s.size();ans=len;
    for(int i=0;i<len;++i){
        a[i]=s[i]-'0';
    }
    for(int i=0;i<x;++i){
        ans+=(a[i]-1)*(ans-i-1)%mod;
        ans%=mod;
        int slen=len;
        for(int j=1;j<a[i]&&len<x;++j){
            for(int k=i+1;k<slen&&len<x;++k){
                a[len++]=a[k];
            }
        }
    }
    cout<<(ans+mod)%mod<<'\n';
    return;
}
signed main(){
    int T;cin>>T;
    while(T--)solve();
    return 0;
}
```
**核心实现思想**：先读取输入的 $x$ 和字符串 $s$，将字符串的每个字符转换为数字存储在数组 $a$ 中。然后进行 $x$ 次操作，每次操作根据当前字符的值更新字符串的长度，并在字符串长度小于 $x$ 时，暴力扩展前 $x$ 个字符。最后输出最终字符串长度对 $10^9 + 7$ 取模的结果。

### 关键思路或技巧
- 只维护前 $x$ 个字符，其余部分只记录长度，避免字符串长度呈指数级增长导致超时。
- 注意取模操作，特别是负数取模的问题，确保结果的正确性。

### 拓展思路
同类型题或类似算法套路通常涉及对字符串的操作和模拟，可能会有不同的操作规则和限制条件。在处理这类问题时，关键是要找到合适的优化策略，避免不必要的计算。

### 推荐洛谷题目
- P1042 [NOIP2003 普及组] 乒乓球
- P1067 [NOIP2009 普及组] 多项式输出
- P1098 [NOIP2007 提高组] 字符串的展开

---
处理用时：56.19秒