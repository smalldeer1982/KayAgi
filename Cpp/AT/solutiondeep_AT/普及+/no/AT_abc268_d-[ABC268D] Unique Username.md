# 题目信息

# [ABC268D] Unique Username

## 题目描述

高桥君有取名选择困难症，于是他找到你，希望帮他取一个用户名。

具体取名规则是：把给定的 $N$ 个字符串 $S_1，S_2,\ldots,S_N$ 以任意顺序排列，并在每两个字符串中间加 $\ge1$ 个下划线，要求不能与后面给定的 $M$ 个字符串 $T_1，T_2,\ldots,T_M$ 中的任意一个相同。

其中，你给出的字符串的长度 $X$ 应该满足 $3\le X \le 16$ 。如果无法满足条件，输出 $-1$。

## 样例 #1

### 输入

```
1 1

chokudai

chokudai```

### 输出

```
-1```

## 样例 #2

### 输入

```
2 2

choku

dai

chokudai

choku_dai```

### 输出

```
dai_choku```

## 样例 #3

### 输入

```
2 2

chokudai

atcoder

chokudai_atcoder

atcoder_chokudai```

### 输出

```
-1```

## 样例 #4

### 输入

```
4 4

ab

cd

ef

gh

hoge

fuga

____

_ab_cd_ef_gh_```

### 输出

```
ab__ef___cd_gh```

# AI分析结果

### 题目内容
高桥君有取名选择困难症，于是他找到你，希望帮他取一个用户名。

具体取名规则是：把给定的 $N$ 个字符串 $S_1，S_2,\ldots,S_N$ 以任意顺序排列，并在每两个字符串中间加 $\ge1$ 个下划线，要求不能与后面给定的 $M$ 个字符串 $T_1，T_2,\ldots,T_M$ 中的任意一个相同。

其中，你给出的字符串的长度 $X$ 应该满足 $3\le X \le 16$ 。如果无法满足条件，输出 $-1$。

### 样例 #1

#### 输入
```
1 1
chokudai
chokudai
```

#### 输出
```
-1
```

### 样例 #2

#### 输入
```
2 2
choku
dai
chokudai
choku_dai
```

#### 输出
```
dai_choku
```

### 样例 #3

#### 输入
```
2 2
chokudai
atcoder
chokudai_atcoder
atcoder_chokudai
```

#### 输出
```
-1
```

### 样例 #4

#### 输入
```
4 4
ab
cd
ef
gh
hoge
fuga
____
_ab_cd_ef_gh_
```

#### 输出
```
ab__ef___cd_gh
```

### 算法分类
深度优先搜索 DFS、剪枝

### 综合分析与结论
本题的核心是通过深度优先搜索（DFS）来枚举所有可能的字符串排列和下划线组合，同时使用剪枝来优化搜索过程。由于 $N \leq 8$，直接暴力搜索是可行的，但需要通过剪枝来减少不必要的搜索路径。具体来说，当当前字符串长度超过16时，直接回溯；当所有字符串排列完成后，检查生成的字符串是否在给定的 $M$ 个字符串中出现过，并且长度是否满足 $3 \leq X \leq 16$。

### 所选题解

#### 题解1：2020luke (赞：6)
- **星级**：5星
- **关键亮点**：使用DFS进行字符串排列和下划线组合的搜索，通过剪枝优化搜索过程，代码清晰且高效。
- **核心代码**：
```cpp
void dfs(int t, string s, int sum_) {
    if(s.size() > 16) {
        return;
    }
    if(t > n) {
        if(st.find(s) == st.end() && s.size() >= 3) {
            cout << s;
            exit(0);
        }
        return;
    }
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            string tmp_;
            for(int j = 1; j <= 16; j++) {
                tmp_ += '_';
                if(sum + sum_ + j + n - t - 1 <= 16) {
                    vis[i] = true;
                    dfs(t + 1, s + tmp_ + str1[i], sum_ + j);
                    vis[i] = false;
                }
                else {
                    break;
                }
            }
        }
    }
}
```
- **核心思想**：通过DFS枚举所有可能的字符串排列和下划线组合，使用剪枝来减少不必要的搜索路径。

#### 题解2：Empty_Dream (赞：2)
- **星级**：4星
- **关键亮点**：使用DFS进行字符串排列和下划线组合的搜索，通过剪枝优化搜索过程，代码清晰。
- **核心代码**：
```cpp
void dfs1(int x, int sum){
    if (sum < 0) return ;
    if (x == n){
        if(16 - sum < 3) return;
        string ans = v[0];
        for (int i = 1; i < n; i++){
            for (int j = 1; j <= a[i]; j++) ans += "_";
            ans += v[i];
        }
        if (mp[ans] == 0) cout << ans, exit(0);
        return ;
    }
    for (int i = 1; i <= sum; i++){
        a[x] = i;
        dfs1(x + 1, sum - i);
    }
}
```
- **核心思想**：通过DFS枚举所有可能的字符串排列和下划线组合，使用剪枝来减少不必要的搜索路径。

#### 题解3：FFTotoro (赞：2)
- **星级**：4星
- **关键亮点**：使用DFS进行字符串排列和下划线组合的搜索，通过剪枝优化搜索过程，代码清晰。
- **核心代码**：
```cpp
bool dfs(int t,string s){
    if(s.length()>=3&&t>=n&&b.find(s)!=b.end()){
        cout<<s<<endl;
        return true;
    }
    for(int i=1;i<=n;i++)
        if(!x[i]){
            for(int j=1;j<=16;j++){
                string tt=s; for(int k=1;k<=j;k++)tt+="_"; tt+=a[i];
                if(tt.length()>16)break; x[i]=true;
                if(tt.length()>=3&&dfs(t+1,tt))return true; x[i]=false;
            }
        }
    return false;
}
```
- **核心思想**：通过DFS枚举所有可能的字符串排列和下划线组合，使用剪枝来减少不必要的搜索路径。

### 最优关键思路或技巧
1. **DFS与剪枝结合**：通过DFS枚举所有可能的字符串排列和下划线组合，使用剪枝来减少不必要的搜索路径。
2. **字符串拼接与长度检查**：在每次拼接字符串时，检查当前长度是否超过16，若超过则回溯。
3. **使用集合进行快速查找**：使用`set`或`unordered_set`来存储给定的 $M$ 个字符串，以便快速检查生成的字符串是否在其中。

### 可拓展之处
本题的DFS与剪枝技巧可以应用于其他类似的排列组合问题，尤其是在需要枚举所有可能情况并进行剪枝优化的场景中。

### 推荐题目
1. [P1036 选数](https://www.luogu.com.cn/problem/P1036)
2. [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)
3. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)

---
处理用时：37.54秒