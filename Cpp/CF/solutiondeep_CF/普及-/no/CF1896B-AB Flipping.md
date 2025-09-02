# 题目信息

# AB Flipping

## 题目描述

You are given a string $ s $ of length $ n $ consisting of characters $ \texttt{A} $ and $ \texttt{B} $ . You are allowed to do the following operation:

- Choose an index $ 1 \le i \le n - 1 $ such that $ s_i = \texttt{A} $ and $ s_{i + 1} = \texttt{B} $ . Then, swap $ s_i $ and $ s_{i+1} $ .

You are only allowed to do the operation at most once for each index $ 1 \le i \le n - 1 $ . However, you can do it in any order you want. Find the maximum number of operations that you can carry out.

## 说明/提示

In the first test case, we can do the operation exactly once for $ i=1 $ as $ s_1=\texttt{A} $ and $ s_2=\texttt{B} $ .

In the second test case, it can be proven that it is not possible to do an operation.

In the third test case, we can do an operation on $ i=2 $ to form $ \texttt{ABAB} $ , then another operation on $ i=3 $ to form $ \texttt{ABBA} $ , and finally another operation on $ i=1 $ to form $ \texttt{BABA} $ . Note that even though at the end, $ s_2 = \texttt{A} $ and $ s_3 = \texttt{B} $ , we cannot do an operation on $ i=2 $ again as we can only do the operation at most once for each index.

## 样例 #1

### 输入

```
3
2
AB
4
BBBA
4
AABB```

### 输出

```
1
0
3```

# AI分析结果

### 题目内容（中文重写）
# AB 翻转

## 题目描述
给定一个长度为 $n$ 的字符串 $s$，该字符串仅由字符 $\texttt{A}$ 和 $\texttt{B}$ 组成。你可以进行如下操作：
- 选择一个索引 $1 \le i \le n - 1$，使得 $s_i = \texttt{A}$ 且 $s_{i + 1} = \texttt{B}$。然后，交换 $s_i$ 和 $s_{i+1}$。

对于每个索引 $1 \le i \le n - 1$，你最多只能进行一次该操作。不过，你可以按任意顺序进行操作。请找出你最多可以执行的操作次数。

## 说明/提示
在第一个测试用例中，我们可以对 $i = 1$ 执行一次操作，因为 $s_1 = \texttt{A}$ 且 $s_2 = \texttt{B}$。

在第二个测试用例中，可以证明无法执行任何操作。

在第三个测试用例中，我们可以先对 $i = 2$ 执行操作，得到 $\texttt{ABAB}$，然后对 $i = 3$ 执行操作，得到 $\texttt{ABBA}$，最后对 $i = 1$ 执行操作，得到 $\texttt{BABA}$。请注意，即使在最后 $s_2 = \texttt{A}$ 且 $s_3 = \texttt{B}$，我们也不能再对 $i = 2$ 执行操作，因为每个索引最多只能操作一次。

## 样例 #1
### 输入
```
3
2
AB
4
BBBA
4
AABB
```
### 输出
```
1
0
3
```

### 算法分类
贪心

### 综合分析与结论
这些题解主要围绕如何找出给定字符串中可执行的最大操作次数展开。不同题解思路各有特点：
- **_qingshu_、_anll_、kczw**：通过寻找字符串中第一个 $\texttt{A}$ 和最后一个 $\texttt{B}$ 的位置，利用它们的差值来计算最大操作次数，核心在于发现开头连续的 $\texttt{A}$ 和结尾连续的 $\texttt{B}$ 对结果无贡献。
- **zsh_haha、_txb_**：采用模拟的方法，从前往后遍历字符串，尝试将每个 $\texttt{B}$ 往前移动，同时标记已操作的位置，避免重复操作。
- **_O_v_O_**：通过数学推导，将字符串分割成特定的子串，计算可操作次数。
- **UncleSam_Died**：使用栈来维护操作过程，根据字符是 $\texttt{A}$ 还是 $\texttt{B}$ 进行不同处理。

### 所选的题解
- **_qingshu_（4星）**
    - **关键亮点**：思路清晰，通过简单的遍历找到第一个 $\texttt{A}$ 和最后一个 $\texttt{B}$ 的位置，直接计算差值得到结果，代码简洁易懂。
- **_anll_（4星）**
    - **关键亮点**：从模拟过程中发现规律，统计开头连续的 $\texttt{A}$ 和结尾连续的 $\texttt{B}$，进而计算最大操作次数，思路巧妙。
- **zsh_haha（4星）**
    - **关键亮点**：采用模拟的方法，详细描述了字符移动的过程，并且通过标记数组避免重复操作，逻辑严谨。

### 重点代码
#### _qingshu_ 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
string s;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>s;
        int lef=n,rig=-1;
        for(int i=0;i<n;i++){
            if(s[i]=='A'){
                lef=i;
                break;
            }
        }
        for(int i=n-1;i>=0;i--){
            if(s[i]=='B'){
                rig=i;
                break;
            }
        }
        if(lef<rig)cout<<rig-lef<<endl;
        else cout<<0<<endl;
    }
} 
```
**核心实现思想**：先遍历字符串找到第一个 $\texttt{A}$ 的位置 `lef` 和最后一个 $\texttt{B}$ 的位置 `rig`，若 `lef` 小于 `rig`，则输出它们的差值，否则输出 0。

#### _anll_ 的代码
```cpp
#include<iostream>
#define int long long
using namespace std;
int t,n,a,b;
string s;
signed main(){
    cin>>t;
    while(t--){
        a=b=0;
        cin>>n;
        cin>>s;
        for(int i=0;i<n;i++){
            if(s[i]=='A') break;
            b+=1;
        }
        for(int i=n-1;i>=0;i--){
            if(s[i]=='B') break;
            a+=1;
        }
        cout<<max(n-b-a-1,(int)0)<<endl;
    }
    return 0;
}
```
**核心实现思想**：统计开头连续的 $\texttt{B}$ 的个数 `b` 和结尾连续的 $\texttt{A}$ 的个数 `a`，用字符串长度减去 `b` 和 `a` 再减 1 得到最大操作次数，若结果小于 0 则输出 0。

#### zsh_haha 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char c[200001];
bool b[200001];
int main(){
    int t,n,ans,l;
    cin>>t;
    while(t--){
        memset(b,1,sizeof b);
        cin>>n>>c+1;
        l=1;
        ans=0;
        for(int i=2;i<=n;i++){
            int j=i;
            while(c[j]=='B'&&c[j-1]=='A'&&b[j-1]){
                swap(c[j],c[j-1]);
                b[j-1]=false;
                j--;
                ans++;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
**核心实现思想**：使用标记数组 `b` 记录每个位置是否已操作，从前往后遍历字符串，若当前字符为 $\texttt{B}$ 且前一个字符为 $\texttt{A}$ 且该位置未操作，则交换它们的位置，标记该位置已操作，指针前移并增加操作次数。

### 最优关键思路或技巧
- 观察到开头连续的 $\texttt{A}$ 和结尾连续的 $\texttt{B}$ 对结果无贡献，通过寻找第一个 $\texttt{A}$ 和最后一个 $\texttt{B}$ 的位置来简化计算。
- 采用模拟的方法，通过标记数组避免重复操作，确保每个位置最多操作一次。

### 可拓展之处
同类型题可能会改变操作规则，例如可以进行多次操作、操作的条件变化等。类似算法套路可以应用于其他字符串操作问题，通过观察字符串的特征，找出规律来简化计算。

### 推荐题目
- [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)
- [P1071 潜伏者](https://www.luogu.com.cn/problem/P1071)
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)

### 个人心得
题解中未包含个人心得。

---
处理用时：43.66秒