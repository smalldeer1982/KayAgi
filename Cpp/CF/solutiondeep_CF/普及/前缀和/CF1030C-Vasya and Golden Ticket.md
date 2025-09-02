# 题目信息

# Vasya and Golden Ticket

## 题目描述

Recently Vasya found a golden ticket — a sequence which consists of $ n $ digits $ a_1a_2\dots a_n $ . Vasya considers a ticket to be lucky if it can be divided into two or more non-intersecting segments with equal sums. For example, ticket $ 350178 $ is lucky since it can be divided into three segments $ 350 $ , $ 17 $ and $ 8 $ : $ 3+5+0=1+7=8 $ . Note that each digit of sequence should belong to exactly one segment.

Help Vasya! Tell him if the golden ticket he found is lucky or not.

## 说明/提示

In the first example the ticket can be divided into $ 7 $ , $ 34 $ and $ 52 $ : $ 7=3+4=5+2 $ .

In the second example it is impossible to divide ticket into segments with equal sum.

## 样例 #1

### 输入

```
5
73452
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
1248
```

### 输出

```
NO
```

# AI分析结果

### 题目内容重写
# Vasya and Golden Ticket

## 题目描述

最近，Vasya发现了一张黄金票——一个由$n$个数字$a_1a_2\dots a_n$组成的序列。Vasya认为一张票是幸运的，如果它可以被分成两个或更多个不相交的段，且这些段的和相等。例如，票$350178$是幸运的，因为它可以被分成三个段$350$、$17$和$8$：$3+5+0=1+7=8$。注意，序列中的每个数字必须属于且仅属于一个段。

帮助Vasya！告诉他他找到的黄金票是否是幸运的。

## 说明/提示

在第一个例子中，票可以被分成$7$、$34$和$52$：$7=3+4=5+2$。

在第二个例子中，无法将票分成和相等的段。

## 样例 #1

### 输入

```
5
73452
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
1248
```

### 输出

```
NO
```

### 题解分析与结论

通过对多条题解的分析，可以发现大多数题解采用了暴力搜索或枚举的方法来解决这个问题。主要的思路是通过计算前缀和或直接分段求和，然后判断是否可以将序列分成多个和相等的段。以下是几条较为优秀的题解：

#### 题解1：XUQING (4星)
- **关键亮点**：使用了深度优先搜索（DFS）来递归地尝试分割序列，并通过剪枝优化了搜索过程。
- **代码核心**：
  ```cpp
  bool dfs(string s, int tot, int f) {
      if(s.length() == 1 && s[0] - '0' == tot)
          return true;
      for(int i = 1; i <= s.length(); i++) {
          int ans = sum(s.substr(0, i));
          if(i == s.length() && ans == tot)
              return true;
          if(ans > tot && f)
              return false;
          if(ans == tot || !f) {
              bool b = dfs(s.substr(i, s.length()+1), ans, f + 1);
              if(b)
                  return true;
          }
      }
      return false;
  }
  ```

#### 题解2：lichenfan (3星)
- **关键亮点**：通过枚举分成的段数，直接模拟分段过程，代码简洁易懂。
- **代码核心**：
  ```cpp
  for(int i = 2; i <= n; i++) {
      ans = 0;
      if(sum%i==0){
          for(int j=1;j<=n;j++){
              ans+=a[j];
              if(ans==sum/i) ans=0;
              if(ans>sum/i) break;
              if(j==n){
                  cout<<"YES";
                  return 0;
              }
          }
      }
  }
  ```

#### 题解3：KillerXu (2星)
- **关键亮点**：通过枚举可能的段和，然后判断是否可以将序列分成多个和相等的段，思路清晰。
- **代码核心**：
  ```cpp
  for(int k = 0; k <= sum; k++){
      int rec = 0 , t = 0 , flag = 1;
      for(int i = 1; i <= n; i++){
          rec += a[i];
          if(rec == k){t++; rec = 0; continue;}
          if(rec > k) {flag = 0; break;}
      }
      if(flag && t > 1 && !rec) {cout << "YES"; return 0;}
  }
  ```

### 最优关键思路与技巧
- **DFS剪枝**：通过递归和剪枝，可以有效减少不必要的搜索，提高算法效率。
- **枚举段数**：通过枚举可能的段数，直接模拟分段过程，代码简洁且易于理解。
- **前缀和**：利用前缀和来快速计算任意子段的和，简化了分段判断的过程。

### 可拓展之处
- **动态规划**：可以考虑使用动态规划来优化分段判断的过程，减少重复计算。
- **贪心算法**：在某些情况下，贪心算法可以快速找到分段方案，但需要注意其正确性。

### 推荐题目
1. [P1042 最大子段和](https://www.luogu.com.cn/problem/P1042)
2. [P1043 分割数组的最大值](https://www.luogu.com.cn/problem/P1043)
3. [P1044 数字三角形](https://www.luogu.com.cn/problem/P1044)

### 个人心得摘录
- **XUQING**：通过剪枝优化了搜索过程，减少了不必要的递归调用，提高了代码效率。
- **lichenfan**：通过枚举段数直接模拟分段过程，代码简洁易懂，适合初学者理解。
- **KillerXu**：通过枚举可能的段和，思路清晰，但代码实现较为复杂，适合有一定基础的读者。

---
处理用时：35.27秒