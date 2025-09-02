# 题目信息

# Minimise Oneness

## 题目描述

For an arbitrary binary string $ t $ $ ^{\text{∗}} $ , let $ f(t) $ be the number of non-empty subsequences $ ^{\text{†}} $ of $ t $ that contain only $ \mathtt{0} $ , and let $ g(t) $ be the number of non-empty subsequences of $ t $ that contain at least one $ \mathtt{1} $ .

Note that for $ f(t) $ and for $ g(t) $ , each subsequence is counted as many times as it appears in $ t $ . E.g., $ f(\mathtt{000}) = 7, g(\mathtt{100}) = 4 $ .

We define the oneness of the binary string $ t $ to be $ |f(t)-g(t)| $ , where for an arbitrary integer $ z $ , $ |z| $ represents the absolute value of $ z $ .

You are given a positive integer $ n $ . Find a binary string $ s $ of length $ n $ such that its oneness is as small as possible. If there are multiple strings, you can print any of them.

 $ ^{\text{∗}} $ A binary string is a string that only consists of characters $ \texttt{0} $ and $ \texttt{1} $ .

 $ ^{\text{†}} $ A sequence $ a $ is a subsequence of a sequence $ b $ if $ a $ can be obtained from $ b $ by the deletion of several (possibly, zero or all) elements. For example, subsequences of $ \mathtt{1011101} $ are $ \mathtt{0} $ , $ \mathtt{1} $ , $ \mathtt{11111} $ , $ \mathtt{0111} $ , but not $ \mathtt{000} $ nor $ \mathtt{11100} $ .

## 说明/提示

In the first test case, for the example output, $ f(t)=1 $ because there is one subsequence that contains only $ \mathtt{0} $ ( $ \mathtt{0} $ ), and $ g(t)=0 $ because there are no subsequences that contain at least one $ 1 $ . The oneness is $ |1-0|=1 $ . The output $ \mathtt{1} $ is correct as well because its oneness is $ |0-1|=1 $ .

For the example output of the second test case, $ f(t)=1 $ because there is one non-empty subsequence that contains only $ \mathtt{0} $ , and $ g(t)=2 $ because there are two non-empty subsequences that contain at least one $ \mathtt{1} $ ( $ \mathtt{01} $ and $ \mathtt{1} $ ). The oneness is thus $ |1-2|=1 $ . It can be shown that $ 1 $ is the minimum possible value of its oneness over all possible binary strings of size $ 2 $ .

## 样例 #1

### 输入

```
3
1
2
3```

### 输出

```
0
01
010```

# AI分析结果



# Minimise Oneness 题目中文翻译

## 题目描述
对于任意二进制字符串 $t$，令 $f(t)$ 表示仅包含 $\mathtt{0}$ 的非空子序列的数量，$g(t)$ 表示至少包含一个 $\mathtt{1}$ 的非空子序列的数量。每个子序列的出现次数会被重复计算（例如 $f(\mathtt{000})=7$）。

定义字符串 $t$ 的单一性为 $|f(t)-g(t)|$。给定正整数 $n$，构造一个长度为 $n$ 的二进制字符串 $s$，使得其单一性尽可能小。若有多个解，输出任意一个。

## 说明/提示
- 二进制字符串仅由 $\texttt{0}$ 和 $\texttt{1}$ 构成。
- 子序列的定义是通过删除若干字符（可能为零或全部）得到的序列，且保留原始顺序。

## 样例
### 输入
```
3
1
2
3
```
### 输出
```
0
01
010
```

---

## 综合分析与结论
所有题解的核心思路是构造含 $n-1$ 个 $\mathtt{0}$ 和 $1$ 个 $\mathtt{1}$ 的字符串，使得单一性最小为 $1$。通过数学推导可知，当 $0$ 的个数为 $n-1$ 时，$|f(t)-g(t)|$ 的最小值为 $1$，无法进一步优化。

---

## 精选题解

### 1. 末然Ender（★★★★★）
**关键亮点**：通过严格的数学公式推导，证明当 $0$ 的个数为 $n-1$ 时，单一性最小为 $1$，思路清晰且代码简洁。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        scanf("%d",&n);
        putchar('1');
        for(int i=1;i<n;i++)putchar('0');
        putchar('\n');
    }
    return 0;
}
```

### 2. xixisuper（★★★★☆）
**关键亮点**：通过拆分公式 $|2^{x+1}-2^n-1|$，明确最小值条件，代码实现直接高效。
```cpp
#include <iostream>
using namespace std;
void solve(){
    int n;
    cin>>n;
    cout<<"1";
    while(--n) cout<<"0";
    cout<<"\n";
}
int main(){
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}
```

### 3. wuyouawa（★★★★☆）
**个人心得**：通过具体样例分析差值构成，强调构造方式的直观性，代码逻辑清晰。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        cout << 1;
        for (int i = 1; i < n; i++) cout << 0;
        cout << endl;
    }
    return 0;
}
```

---

## 关键思路总结
1. **数学推导**：通过公式 $|2^{x+1}-2^n-1|$ 发现当 $x=n-1$ 时，最小差值为 $1$。
2. **构造技巧**：构造一个 $\mathtt{1}$ 和 $n-1$ 个 $\mathtt{0}$ 的字符串，顺序不影响结果。
3. **优化验证**：总子序列数 $2^n-1$ 为奇数，最小奇差 $1$ 无法再优化。

---

## 相似题目推荐
1. **CF1520B** - 构造特殊数字的最小差值
2. **洛谷P1106** - 子序列计数问题
3. **洛谷P2678** - 最优化构造与差值最小化

---
处理用时：70.20秒