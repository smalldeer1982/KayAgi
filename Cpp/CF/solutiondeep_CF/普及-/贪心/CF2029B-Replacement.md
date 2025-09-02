# 题目信息

# Replacement

## 题目描述

You have a binary string $ ^{\text{∗}} $ $ s $ of length $ n $ , and Iris gives you another binary string $ r $ of length $ n-1 $ .

Iris is going to play a game with you. During the game, you will perform $ n-1 $ operations on $ s $ . In the $ i $ -th operation ( $ 1 \le i \le n-1 $ ):

- First, you choose an index $ k $ such that $ 1\le k\le |s| - 1 $ and $ s_{k} \neq s_{k+1} $ . If it is impossible to choose such an index, you lose;
- Then, you replace $ s_ks_{k+1} $ with $ r_i $ . Note that this decreases the length of $ s $ by $ 1 $ .

If all the $ n-1 $ operations are performed successfully, you win.

Determine whether it is possible for you to win this game.

 $ ^{\text{∗}} $ A binary string is a string where each character is either $ \mathtt{0} $ or $ \mathtt{1} $ .

## 说明/提示

In the first test case, you cannot perform the first operation. Thus, you lose the game.

In the second test case, you can choose $ k=1 $ in the only operation, and after that, $ s $ becomes equal to $ \mathtt{1} $ . Thus, you win the game.

In the third test case, you can perform the following operations: $ \mathtt{1}\underline{\mathtt{10}}\mathtt{1}\xrightarrow{r_1=\mathtt{0}} \mathtt{1}\underline{\mathtt{01}} \xrightarrow{r_2=\mathtt{0}} \underline{\mathtt{10}} \xrightarrow{r_3=\mathtt{1}} \mathtt{1} $ .

## 样例 #1

### 输入

```
6
2
11
0
2
01
1
4
1101
001
6
111110
10000
6
010010
11010
8
10010010
0010010```

### 输出

```
NO
YES
YES
NO
YES
NO```

# AI分析结果



# Replacement

## 题目描述

你有一个长度为 $n$ 的二进制字符串 $s$，Iris 给了你另一个长度为 $n-1$ 的二进制字符串 $r$。

Iris 将与你进行一个游戏。在游戏中，你需要对 $s$ 执行 $n-1$ 次操作。在第 $i$ 次操作中（$1 \le i \le n-1$）：

1. 首先，选择一个下标 $k$ 满足 $1 \le k \le |s| - 1$ 且 $s_k \neq s_{k+1}$。如果无法选择这样的下标，则你失败；
2. 然后，将 $s_ks_{k+1}$ 替换为 $r_i$。注意这会使得 $s$ 的长度减少 $1$。

若成功完成所有 $n-1$ 次操作，你获胜。判断你是否能赢得游戏。

（二进制字符串指仅由 $\mathtt{0}$ 和 $\mathtt{1}$ 组成的字符串）

## 样例 #1

### 输入
```
6
2
11
0
2
01
1
4
1101
001
6
111110
10000
6
010010
11010
8
10010010
0010010
```

### 输出
```
NO
YES
YES
NO
YES
NO
```

---

## 题解分析与结论

### 关键思路与算法
所有正确解法的核心在于维护字符数量：
1. **初始统计**：统计原字符串 $s$ 中 '0' 和 '1' 的数量
2. **动态维护**：遍历 $r$ 的每个字符：
   - 若当前操作符为 '0'，则意味着必须存在 '1' 被消耗（减少 '1' 的数量）
   - 若为 '1'，则减少 '0' 的数量
3. **终止条件**：任何时候若任一字符数量归零，则无法继续操作

该思路基于以下观察：
- 每次操作必须选择相邻不同字符对，等价于操作过程中必须同时存在 '0' 和 '1'
- 替换操作本质上会减少其中一个字符类型的总数量

### 复杂度分析
时间复杂度为 $O(n)$，仅需线性遍历字符串，适用于 $n \leq 10^5$ 量级的数据

### 最优题解推荐

#### 1. NEKO_Daze（★★★★★）
**核心思路**：  
维护计数器 `cnt0` 和 `cnt1`，直接根据 $r$ 的字符类型减少对应计数  
**代码亮点**：  
- 使用 `count()` 函数统计初始字符数，代码简洁
- 输出严格符合题目要求的大写格式

```cpp
void solve() {
    int n; cin >> n;
    string s, t; cin >> s >> t;
    int cnt0 = count(all(s), '0'), cnt1 = n - cnt0;
    for (int i = 0; i < n - 1; i++) {
        if (cnt0 == 0 || cnt1 == 0) {
            cout << "NO\n";
            return;
        }
        if (t[i] == '1') cnt0--;
        else cnt1--;
    }
    cout << "YES\n";
}
```

#### 2. tai_chi（★★★★★）
**实现技巧**：  
- 显式遍历字符统计，逻辑清晰
- 使用布尔标志位控制流程

```cpp
void solve() {
    int n; cin>>n;
    string s1,s2; cin>>s1>>s2;
    int cnt1=0,cnt0=0;
    for(int i=0;i<n;i++) {
        if(s1[i]=='0') cnt0++;
        else cnt1++;
    }
    bool flag=1;
    for(int i=0;i<n-1;i++) {
        if(cnt1<=0||cnt0<=0) {flag=0; break;}
        if(s2[i]=='0') cnt1--;
        else cnt0--;
    }
    cout<<(flag?"YES\n":"NO\n");
}
```

---

## 扩展与总结

### 关键技巧
- **逆向思维**：从最终操作结果倒推必要条件，避免模拟复杂过程
- **计数维护**：将字符串操作转化为数值运算，极大降低复杂度

### 相似题目推荐
1. [P7072 直播获奖](https://www.luogu.com.cn/problem/P7072) - 维护动态阈值  
2. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678) - 通过计数判断可行性  
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心策略与操作模拟

### 调试经验
- **输出格式**：多个题解因输出大小写错误导致失败，需注意题目具体要求
- **边界条件**：初始全0或全1的情况需优先判断，避免无效操作

---
处理用时：113.54秒