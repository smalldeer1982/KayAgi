# 题目信息

# [ABC363C] Avoid K Palindrome 2

## 题目描述

给定长度为 $N$ 的字符串 $S$。
请求出 $S$ 重排字符串（包括 $S$ 本身）中，**不包含**长度为 $K$ 的回文子字符串的个数。

但是，长度为 $N$ 的字符串 $T$“包含长度为 $K$ 的回文作为子字符串” 是指$\exist i \le n-k,j=1,2,3,\dots,k,T_{i+j}=T_{i+K+1-j}$成立。

$T_k$ 表示字符串 $T$ 的第 $k$ 个字符。

## 说明/提示

#### 约束条件
- $ 2\le K \le N \le 10$
- $N,K$为整数
- $S$ 长度为 $N$，仅包含小写字母
  
#### 样例 #1 解释
重新排列 `aab` 得到的字符串是 `aab`，`aba`，`baa`，其中 `aab` 和 `baa` 包含长度 $2$ 的回文子串 `aa` 作为部分字符串。因此，满足条件的字符串只有 `aba`，输出 $1$。
#### 样例 #2 解释
排列 `zzyyx` 得到的字符串有 $30$ 个，其中不包含长度 $3$ 的回文子串的字符串有 $16$ 个。因此，输出 $16$。

## 样例 #1

### 输入

```
3 2
aab```

### 输出

```
1```

## 样例 #2

### 输入

```
5 3
zzyyx```

### 输出

```
16```

## 样例 #3

### 输入

```
10 5
abcwxyzyxw```

### 输出

```
440640```

# AI分析结果

### 题目内容（已为中文，无需翻译）
给定长度为 $N$ 的字符串 $S$。
请求出 $S$ 重排字符串（包括 $S$ 本身）中，**不包含**长度为 $K$ 的回文子字符串的个数。

但是，长度为 $N$ 的字符串 $T$“包含长度为 $K$ 的回文作为子字符串” 是指$\exist i \le n-k,j=1,2,3,\dots,k,T_{i+j}=T_{i+K+1-j}$成立。

$T_k$ 表示字符串 $T$ 的第 $k$ 个字符。

#### 约束条件
- $ 2\le K \le N \le 10$
- $N,K$为整数
- $S$ 长度为 $N$，仅包含小写字母
  
#### 样例 #1 解释
重新排列 `aab` 得到的字符串是 `aab`，`aba`，`baa`，其中 `aab` 和 `baa` 包含长度 $2$ 的回文子串 `aa` 作为部分字符串。因此，满足条件的字符串只有 `aba`，输出 $1$。
#### 样例 #2 解释
排列 `zzyyx` 得到的字符串有 $30$ 个，其中不包含长度 $3$ 的回文子串的字符串有 $16$ 个。因此，输出 $16$。

#### 样例 #1
##### 输入
```
3 2
aab
```
##### 输出
```
1
```

#### 样例 #2
##### 输入
```
5 3
zzyyx
```
##### 输出
```
16
```

#### 样例 #3
##### 输入
```
10 5
abcwxyzyxw
```
##### 输出
```
440640
```

### 综合分析与结论
这些题解的核心思路都是基于数据范围较小（$2\le K \le N \le 10$），采用暴力枚举的方法来解决问题。主要分为两种实现方式：一是使用 `next_permutation` 函数来生成全排列；二是使用 DFS 来生成全排列。在生成全排列后，再对每个排列进行检查，判断是否包含长度为 $K$ 的回文子串。

#### 思路对比
- **`next_permutation` 方式**：通过 `next_permutation` 函数生成字符串的所有排列，然后遍历每个排列，检查是否包含长度为 $K$ 的回文子串。这种方式代码简洁，实现方便。
- **DFS 方式**：使用深度优先搜索生成所有可能的排列，在生成过程中可以进行剪枝优化，避免生成不必要的排列。

#### 算法要点
- **全排列生成**：使用 `next_permutation` 或 DFS 生成字符串的所有排列。
- **回文子串检查**：对于每个排列，枚举所有长度为 $K$ 的子串，判断是否为回文串。

#### 解决难点
- **去重**：由于字符串中可能存在重复字符，需要去重，避免重复计算。`next_permutation` 函数可以自动过滤重复排列，DFS 方式可以使用 `map` 或 `set` 来去重。
- **回文判断**：通过双指针或反转字符串的方式判断子串是否为回文串。

### 所选题解
- **作者：T_TLucas_Yin (赞：6) - 4星**
  - **关键亮点**：思路清晰，代码简洁，使用 `next_permutation` 函数自动过滤重复排列，减少了去重的复杂度。
  - **个人心得**：无
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,sum;
char c[1000005];
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>c[i];
    sort(c+1,c+1+n);
    do{
        bool flag=1;
        for(int i=1;i<=n;i++){
            bool flagg=1;
            for(int j=i,k=i+m-1;j<=k;j++,k--){
                if(c[j]!=c[k]) flagg=0;
            }
            if(flagg){
                flag=0;
                break;
            }
        }
        if(flag) sum++;
    }while(next_permutation(c+1,c+1+n));
    cout<<sum;
    return 0;
}
```
核心实现思想：先对输入的字符串进行排序，然后使用 `next_permutation` 函数生成所有排列。对于每个排列，枚举所有长度为 $m$ 的子串，判断是否为回文串。如果不包含回文串，则计数器加 1。

- **作者：OIerWu_829 (赞：3) - 4星**
  - **关键亮点**：使用 DFS 生成全排列，通过记录每个字符的出现次数来避免重复排列，同时在生成过程中进行剪枝，提高了效率。
  - **个人心得**：看到赛时好多人被 C 卡常了，所以写题解尽可能详细。
```cpp
#include <iostream>
#include <vector>
using namespace std;

int n, k;
string s;
vector<int> cnt;
int ans;

bool Check(string str, int sta, int end)
{
  while (sta < end)
  {
    if (str[sta] != str[end])
      return false;
    sta++;
    end--;
  }
  return true;
}

void dfs(string t, int pos)
{
  if (pos == n)
  {
    bool f = true;
    for (int i = 0; i <= n - k; i++)
    {
      if (Check(t, i, i + k - 1))
      {
        f = false;
        break;
      }
    }
    if (f) ans++;
    return;
  }
  for (int i = 0; i < 26; i++)
  {
    if (cnt[i] > 0)
    {
      cnt[i]--;
      t[pos] = i + 'a';
      dfs(t, pos + 1);
      cnt[i]++;
    }
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> n >> k >> s;
  cnt.resize(26, 0);
  for (char c : s) cnt[c - 'a']++;
  string t(n, ' ');
  dfs(t, 0);
  cout << ans;
  return 0;
}
```
核心实现思想：使用 DFS 生成所有可能的排列。在 DFS 过程中，通过记录每个字符的出现次数来避免重复排列。当生成一个完整的排列后，检查是否包含长度为 $k$ 的回文子串，如果不包含则计数器加 1。

- **作者：Moya_Rao (赞：1) - 4星**
  - **关键亮点**：使用 DFS 生成全排列，通过 `check` 函数和 `is` 函数分别判断是否包含长度为 $K$ 的回文子串和子串是否为回文串，逻辑清晰。
  - **个人心得**：无
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans,h[26];
string s,t;
bool is(string st){
    for(int i=0,j=st.size()-1;i<st.size()&&j>=0;i++,j--)
        if(st[i]!=st[j])return 0;
    return 1;
}
bool check(string str){
    for(int i=0;i<=n-k;i++)
        if(is(str.substr(i,k)))return 0;
    return 1;
}
void DFS(int len){
    if(len>=n){
        if(check(t))ans++;
        return;
    }
    for(int i=0;i<26;i++){
        if(h[i]!=0){
            t+=(char)(i+'a');
            h[i]--;
            DFS(len+1);
            t.erase(len,1);
            h[i]++;
        }
    }
}
int main(){
    cin>>n>>k>>s;
    for(int i=0;i<s.size();i++)h[s[i]-'a']++;
    DFS(0);
    cout<<ans;
    return 0;
}
```
核心实现思想：使用 DFS 生成所有可能的排列。在 DFS 过程中，通过记录每个字符的出现次数来生成排列。当生成一个完整的排列后，使用 `check` 函数检查是否包含长度为 $k$ 的回文子串，如果不包含则计数器加 1。`is` 函数用于判断子串是否为回文串。

### 最优关键思路或技巧
- **使用 `next_permutation` 函数**：可以自动生成字符串的所有排列，并过滤重复排列，减少去重的复杂度。
- **DFS 剪枝**：在 DFS 生成排列的过程中，通过记录每个字符的出现次数来避免重复排列，同时可以进行剪枝，提高效率。
- **双指针判断回文串**：通过双指针从两端向中间遍历，判断子串是否为回文串，时间复杂度为 $O(K/2)$。

### 可拓展之处
- **同类型题**：类似的全排列问题，如求满足某种条件的排列个数、排列的最大/最小值等。
- **算法套路**：对于数据范围较小的问题，可以考虑使用暴力枚举的方法，如全排列、组合等。在枚举过程中，可以使用剪枝、去重等技巧来提高效率。

### 推荐洛谷题目
- [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)
- [P1088 火星人](https://www.luogu.com.cn/problem/P1088)
- [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)

### 个人心得摘录与总结
- **OIerWu_829**：看到赛时好多人被 C 卡常了，所以写题解尽可能详细。总结：在竞赛中，即使是简单的题目也可能存在卡常等问题，写题解时详细说明可以帮助他人更好地理解和避免类似问题。

---
处理用时：57.70秒