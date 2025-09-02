# 题目信息

# Minimum Notation

## 题目描述

You have a string $ s $ consisting of digits from $ 0 $ to $ 9 $ inclusive. You can perform the following operation any (possibly zero) number of times:

- You can choose a position $ i $ and delete a digit $ d $ on the $ i $ -th position. Then insert the digit $ \min{(d + 1, 9)} $ on any position (at the beginning, at the end or in between any two adjacent digits).

What is the lexicographically smallest string you can get by performing these operations?

A string $ a $ is lexicographically smaller than a string $ b $ of the same length if and only if the following holds:

- in the first position where $ a $ and $ b $ differ, the string $ a $ has a smaller digit than the corresponding digit in $ b $ .

## 说明/提示

In the first test case:

- Delete $ 8 $ and insert $ 9 $ at the end of the notation. The resulting notation is $ 04299 $ .
- Delete $ 4 $ and insert $ 5 $ in the $ 3 $ -rd position of the notation. The resulting notation is $ 02599 $ .

Nothing needs to be done in the second and third test cases.

## 样例 #1

### 输入

```
4
04829
9
01
314752277691991```

### 输出

```
02599
9
01
111334567888999```

# AI分析结果

### 题目内容重写
给定一个仅包含数字 $0$ 到 $9$ 的字符串 $s$，你可以执行以下操作任意次（包括零次）：

- 选择一个位置 $i$，删除该位置上的数字 $d$，然后将数字 $\min(d+1, 9)$ 插入到字符串的任意位置（开头、结尾或任意两个相邻数字之间）。

求通过执行这些操作后，能够得到的字典序最小的字符串。

### 算法分类
贪心

### 题解分析与结论
本题的核心思路是通过贪心策略，尽可能将较小的数字放在前面，以得到字典序最小的字符串。具体来说，当某个数字后面有比它更小的数字时，应该将该数字删除并插入到后面，以避免它阻碍更小的数字向前移动。大多数题解都采用了类似的后缀最小值或单调栈的思路，通过维护一个单调不减的序列来达到目的。

### 精选题解
#### 1. 作者：win10 (赞：5)
**星级：5星**
**关键亮点：**
- 使用了单调栈的思想，维护一个单调不减的序列。
- 通过将弹出的元素加1后排序，确保最终字符串的字典序最小。
- 代码结构清晰，逻辑严谨。

**核心代码：**
```cpp
void work() {
    cin >> s;
    int len = s.length();
    for(int i = 0;i < len;i++) {
        while(!st.empty() && st.top() > s[i]) {
            els.push_back(min(st.top() + 1,57));
            st.pop();
        }
        st.push(s[i]);
    }
    while(!st.empty()) {
        ans.push_back(st.top());
        st.pop();
    }
    sort(els.begin(),els.end());
    int pos = 0;
    for(int i = ans.size() - 1;i >= 0;i--) {
        cout << ans[i];
        while(pos < els.size() && els[pos] >= ans[i] && els[pos] <= ans[i-1] && i > 0) cout << els[pos++];
    }
    for(int i = pos;i < els.size();i++) cout << els[i];
    cout << endl;
}
```

#### 2. 作者：Vct14 (赞：1)
**星级：4星**
**关键亮点：**
- 使用后缀最小值来判断是否需要删除当前数字。
- 直接将要删除的数字加1后排序，逻辑简洁明了。

**核心代码：**
```cpp
int main(){
    int t;cin>>t;
    while(t--){
        string a;cin>>a;
        int l=a.length();
        b[l-1]=a[l-1]-'0';mn[l-1]=b[l-1];
        for(int i=l-1-1; i>=0; i--){
            b[i]=a[i]-'0';
            mn[i]=min(b[i],mn[i+1]);
            if(b[i]!=mn[i]) b[i]=min(b[i]+1,9);
        }
        sort(b,b+l);
        for(int i=0; i<l; i++) cout<<b[i];cout<<"\n";
    } 
    return 0;
}
```

#### 3. 作者：CNS_5t0_0r2 (赞：0)
**星级：4星**
**关键亮点：**
- 通过贪心策略，将较大的数字往后排，确保较小的数字尽可能靠前。
- 代码实现简洁，逻辑清晰。

**核心代码：**
```cpp
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T;
    cin >> T;
    while(T--){
        memset(cnt,0,sizeof cnt);
        cin >> (s + 1);
        n = strlen(s + 1);
        for(int i = 1;i <= n;i++)
            a[i] = s[i] - '0';
        int Min = 114514;
        for(int i = n;i >= 1;i--){
            cnt[a[i] > Min ? f(a[i]) : a[i]]++;
            Min = min(Min,a[i]);
        }
        for(int i = 0;i <= 9;i++)
            while(cnt[i]--)
                cout << i;
        cout << '\n';
    }
    return 0;
}
```

### 最优关键思路
- **单调栈与后缀最小值**：通过维护一个单调不减的序列，确保较小的数字尽可能靠前。当发现当前数字比栈顶数字大时，将其弹出并加1后插入到后面，最终通过排序得到字典序最小的字符串。
- **贪心策略**：优先处理较大的数字，将其往后移动，以确保较小的数字能够尽可能靠前。

### 可拓展之处
- **类似问题**：类似的问题可以出现在需要维护一个单调序列的场景中，如滑动窗口中的最小值、最大子序列等。
- **数据结构**：单调栈和后缀最小值的技巧在处理字符串或数组的排序问题时非常有用。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1045 最大子序和](https://www.luogu.com.cn/problem/P1045)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：33.50秒