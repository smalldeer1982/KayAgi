# 题目信息

# [ABC155C] Poll

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc155/tasks/abc155_c

$ N $ 枚の投票用紙があり、$ i\ (1\ \leq\ i\ \leq\ N) $ 枚目には文字列 $ S_i $ が書かれています。

書かれた回数が最も多い文字列を全て、辞書順で小さい順に出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ S_i $ は英小文字のみからなる文字列 $ (1\ \leq\ i\ \leq\ N) $
- $ S_i $ の長さは $ 1 $ 以上 $ 10 $ 以下 $ (1\ \leq\ i\ \leq\ N) $

### Sample Explanation 1

書かれた回数は `beet` と `vet` が $ 2 $ 回、`beat` と `bed` と `bet` が $ 1 $ 回です。したがって、$ 2 $ 回書かれた `beet` と `vet` を出力します。

## 样例 #1

### 输入

```
7

beat

vet

beet

bed

vet

bet

beet```

### 输出

```
beet

vet```

## 样例 #2

### 输入

```
8

buffalo

buffalo

buffalo

buffalo

buffalo

buffalo

buffalo

buffalo```

### 输出

```
buffalo```

## 样例 #3

### 输入

```
7

bass

bass

kick

kick

bass

kick

kick```

### 输出

```
kick```

## 样例 #4

### 输入

```
4

ushi

tapu

nichia

kun```

### 输出

```
kun

nichia

tapu

ushi```

# AI分析结果

【题目内容】
# [ABC155C] Poll

## 题目描述

$ N $ 枚の投票用紙があり、$ i\ (1\ \leq\ i\ \leq\ N) $ 枚目には文字列 $ S_i $ が書かれています。

書かれた回数が最も多い文字列を全て、辞書順で小さい順に出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ S_i $ は英小文字のみからなる文字列 $ (1\ \leq\ i\ \leq\ N) $
- $ S_i $ の長さは $ 1 $ 以上 $ 10 $ 以下 $ (1\ \leq\ i\ \leq\ N) $

### Sample Explanation 1

書かれた回数は `beet` と `vet` が $ 2 $ 回、`beat` と `bed` と `bet` が $ 1 $ 回です。したがって、$ 2 $ 回書かれた `beet` と `vet` を出力します。

## 样例 #1

### 输入

```
7

beat

vet

beet

bed

vet

bet

beet```

### 输出

```
beet

vet```

## 样例 #2

### 输入

```
8

buffalo

buffalo

buffalo

buffalo

buffalo

buffalo

buffalo

buffalo```

### 输出

```
buffalo```

## 样例 #3

### 输入

```
7

bass

bass

kick

kick

bass

kick

kick```

### 输出

```
kick```

## 样例 #4

### 输入

```
4

ushi

tapu

nichia

kun```

### 输出

```
kun

nichia

tapu

ushi```

【算法分类】
排序、字符串处理

【题解分析与结论】
本题的核心是统计字符串出现的频率，并输出出现次数最多的字符串，且按字典序排列。大多数题解都使用了`map`来统计字符串的出现次数，并通过排序或直接遍历`map`来输出结果。以下是各题解的要点对比：

1. **zjyqwq**：使用Pascal语言，通过排序和最长平台长度来求解，虽然思路清晰，但代码复杂度较高，且Pascal语言在竞赛中不常见。
2. **eEfiuys**：使用C++的`map`和`sort`，思路清晰，代码简洁，但使用了额外的`map`来记录是否输出过，略显冗余。
3. **StObOtZ**：使用C++的`map`和`sort`，代码简洁，直接遍历`map`输出结果，效率较高。
4. **w33z8kqrqk8zzzx33**：使用C++的`map`，直接遍历`map`输出结果，代码简洁且高效，无需额外排序。
5. **cjZYZtcl**：使用C++的`map`，通过遍历`map`输出结果，代码简洁，但使用了迭代器，略显复杂。
6. **封禁用户**：使用C++的`map`和`vector`，通过去重和排序来输出结果，代码较为复杂，但思路清晰。

【评分较高的题解】
1. **w33z8kqrqk8zzzx33**（5星）
   - 关键亮点：直接使用`map`统计频率，遍历`map`输出结果，代码简洁高效。
   - 核心代码：
     ```cpp
     map<string, int> mpp;
     signed main() {
         int n; cin >> n;
         rep(i, n) {
             string s; cin >> s;
             mpp[s]++;
         }
         int bes = 0;
         for(auto& v:mpp) bes = max(bes, v.se);
         for(auto& v:mpp) {
             if(v.se == bes) cout << v.fi << endl;
         }
     }
     ```

2. **StObOtZ**（4星）
   - 关键亮点：使用`map`统计频率，通过`sort`排序后输出结果，代码简洁。
   - 核心代码：
     ```cpp
     map<string, int> a;
     signed main(){
         cin>>n;
         for(int i=1;i<=n;i++){
             cin>>s[i];
             a[s[i]]++;
             if(a[s[i]]>ans) ans=a[s[i]];
         }
         sort(s+1,s+1+n);
         for (int i=1;i<=n;i++)
         if (a[s[i]]==ans&&s[i]!=s[i-1]) cout<<s[i]<<endl;
     }
     ```

3. **eEfiuys**（4星）
   - 关键亮点：使用`map`统计频率，通过`sort`排序后输出结果，代码简洁。
   - 核心代码：
     ```cpp
     map<string,int>a;
     int main() {
         cin>>n;
         for(int i=1;i<=n;i++) {
             cin>>s[i];
             a[s[i]]++;
         }
         sort(s+1,s+n+1);
         for(int i=1;i<=n;i++) num=max(num,a[s[i]]);
         for(int i=1;i<=n;i++)
         if(!b[s[i]]&&a[s[i]]==num) {
             b[s[i]]=1;
             cout<<s[i]<<endl;
         }
     }
     ```

【最优关键思路】
使用`map`统计字符串的出现频率，遍历`map`找到最大频率，然后再次遍历`map`输出所有频率等于最大频率的字符串。这种方法简洁高效，无需额外排序。

【拓展思路】
类似的问题可以扩展到统计其他类型数据的频率，如数字、字符等。可以使用`map`或`unordered_map`来统计频率，然后根据需求输出结果。

【推荐题目】
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P3370 【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370)

---
处理用时：34.10秒