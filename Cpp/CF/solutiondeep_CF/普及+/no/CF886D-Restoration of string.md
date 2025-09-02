# 题目信息

# Restoration of string

## 题目描述

A substring of some string is called the most frequent, if the number of its occurrences is not less than number of occurrences of any other substring.

You are given a set of strings. A string (not necessarily from this set) is called good if all elements of the set are the most frequent substrings of this string. Restore the non-empty good string with minimum length. If several such strings exist, restore lexicographically minimum string. If there are no good strings, print "NO" (without quotes).

A substring of a string is a contiguous subsequence of letters in the string. For example, "ab", "c", "abc" are substrings of string "abc", while "ac" is not a substring of that string.

The number of occurrences of a substring in a string is the number of starting positions in the string where the substring occurs. These occurrences could overlap.

String $ a $ is lexicographically smaller than string $ b $ , if $ a $ is a prefix of $ b $ , or $ a $ has a smaller letter at the first position where $ a $ and $ b $ differ.

## 说明/提示

One can show that in the first sample only two good strings with minimum length exist: "cfmailru" and "mailrucf". The first string is lexicographically minimum.

## 样例 #1

### 输入

```
4
mail
ai
lru
cf
```

### 输出

```
cfmailru
```

## 样例 #2

### 输入

```
3
kek
preceq
cheburek
```

### 输出

```
NO
```

# AI分析结果

### 题目重写
# 字符串恢复

## 题目描述
某个字符串的子串如果出现的次数不少于其他任何子串的出现次数，则称该子串为最频繁子串。

给定一组字符串。如果一个字符串（不一定来自这组字符串）满足该组中的所有元素都是这个字符串的最频繁子串，那么这个字符串称为好字符串。恢复出长度最小的非空好字符串。如果存在多个这样的字符串，恢复出字典序最小的字符串。如果不存在好字符串，则输出“NO”（不含引号）。

字符串的子串是字符串中连续的字母序列。例如，“ab”、“c”、“abc”是字符串“abc”的子串，而“ac”不是该字符串的子串。

子串在字符串中的出现次数是指该子串在字符串中出现的起始位置的数量。这些出现位置可能重叠。

如果字符串 $a$ 是字符串 $b$ 的前缀，或者在 $a$ 和 $b$ 第一个不同的位置上 $a$ 的字母更小，那么字符串 $a$ 的字典序小于字符串 $b$。

## 说明/提示
可以证明在第一个样例中，只有两个长度最小的好字符串：“cfmailru”和“mailrucf”。第一个字符串字典序最小。

## 样例 #1
### 输入
```
4
mail
ai
lru
cf
```
### 输出
```
cfmailru
```

## 样例 #2
### 输入
```
3
kek
preceq
cheburek
```
### 输出
```
NO
```

### 算法分类
构造

### 综合分析与结论
这两道题解均围绕如何根据给定的一组作为最频繁子串的字符串，构造出符合要求的好字符串展开。主要从判断无解情况和构建原串这两方面入手。题解一通过字符前后关系数组来构建原串并判断矛盾；题解二则是构建有向图，利用拓扑排序和DFS来求解。二者都考虑到了字符不能重复、不能有矛盾关系以及不能有环等关键条件。

### 所选的题解
- **题解一（yyandy）**：
  - **星级**：4星
  - **关键亮点**：思路清晰，通过将每个输入字符串转化为字符间前后顺序条件，利用数组记录字符前后关系，简洁地判断矛盾情况并构建原串。同时考虑到结果可能由多个“块”组成，最后通过排序得到字典序最小的结果。
  - **个人心得**：作者自谦可能有错误，欢迎大家提出问题。
  - **重点代码核心实现思想**：用`x[0][i]`和`x[1][i]`分别记录ASCII码为`i`的字符前面和后面的字符，遍历输入字符串更新这些关系，若出现矛盾则输出“NO”。最后根据记录的关系生成原串，并通过排序得到字典序最小的结果。
  ```cpp
  int x[2][10000];
  string st[120001],s[120001];
  int tt[12001],t[12001],v[12001];
  int n,i,j,k[120001],ii,kk;
  int main(){
      cin>>n;
      for(i=1;i<=n;++i){
          cin>>st[i];
          k[i]=st[i].length();
          for(j=0;j<k[i];++j){
              tt[st[i][j]]=1;
              if(t[st[i][j]]){
                  cout<<"NO";return 0;
              }
              t[st[i][j]]=1;
          }
          for(j=0;j<k[i];++j)t[st[i][j]]=0;
      }
      for(i=1;i<=n;++i){
          for(j=0;j<k[i];++j){
              if(j!=0){
                  if(x[0][st[i][j]]>0&&x[0][st[i][j]]!=st[i][j-1]){
                      cout<<"NO";return 0;
                  }
                  x[0][st[i][j]]=st[i][j-1];
              }
              if(j!=k[i]-1){
                  if(x[1][st[i][j]]>0&&x[1][st[i][j]]!=st[i][j+1]){
                      cout<<"NO";return 0;
                  }
                  x[1][st[i][j]]=st[i][j+1];
              }
          }
      }
      for(i=0;i<=200;++i){
          if(tt[i]&&x[0][i]==0){
              ii=i;++kk;v[ii]=1;
              while(ii){
                  s[kk]+=char(ii);
                  v[ii]=1;
                  ii=x[1][ii];
              }
          }
      }
      for(i=0;i<=200;++i)
          if(tt[i]&&!v[i]){
              cout<<"NO";
              return 0;
          }
      sort(s+1,s+kk+1);
      for(i=1;i<=kk;++i)
          cout<<s[i];
  }
  ```
- **题解二（Wander_E）**：
  - **星级**：4星
  - **关键亮点**：巧妙地将问题转化为图论问题，通过构建有向图，利用拓扑排序判断是否有环以及DFS遍历图来得到结果，逻辑严谨。
  - **重点代码核心实现思想**：用`edge[i][j]`表示字符`i`到字符`j`有一条有向边，`in[i]`记录字符`j`的入度。通过遍历输入字符串构建图，先检查是否有自环，再用拓扑排序判断是否有环，最后从入度为0的点开始DFS得到结果。
  ```cpp
  void tupo()
  {
      queue<int> q;
      int cnt = 0;
      for (int i = 0; i < 26; i++)
          if (!in[i] && exist[i])
              q.push(i);
      while (!q.empty())
      {
          int t = q.front();
          q.pop();
          cnt++;
          for (int i = 0; i < 26; i++)
          {
              if (!edge[t][i] || vis[i])
                  continue;
              vis[i] = 1;
              in[i]--;
              if (in[i] <= 0)
                  q.push(i);
          }
      }
  }

  void dfs(int u)
  {
      int cnt = 0;
      ans += char(u + 'a');
      for (int i = 0; i < 26; i++)
      {
          if (!edge[u][i])
              continue;
          if (vis[i])
          {
              cout << "NO\n";
              exit(0);
          }
          cnt++;
          vis[i] = 1;
          dfs(i);
      }
  }

  int main()
  {
      cin >> n;
      for (int i = 1; i <= n; i++)
      {
          cin >> s;
          exist[s[0] - 'a'] = 1;
          for (int j = 1; j < s.size(); j++)
          {
              exist[s[j] - 'a'] = 1;
              edge[s[j - 1] - 'a'][s[j] - 'a'] = 1;
              in[s[j] - 'a']++;
          }
      }
      for (int i = 0; i < 26; i++)
      {
          if (edge[i][i])
          {
              cout << "NO\n";
              return 0;
          }
      }
      memcpy(t, in, sizeof(in));
      tupo();
      memcpy(in, t, sizeof(in));
      memset(vis, 0, sizeof vis);
      for (int i = 0; i < 26; i++)
      {
          if (exist[i] &&!vis[i] &&!in[i])
              dfs(i);
      }
      for (int i = 0; i < 26; i++)
      {
          if (in[i] &&!vis[i])
          {
              cout << "NO\n";
              exit(0);
          }
          int cnt = 0;
          for (int j = 0; j < 26; j++)
          {
              if(cnt > 1)
              {
                  cout << "NO\n";
                  exit(0);
              }
              cnt += edge[i][j];
          }
      }
      cout << ans << endl;
      return 0;
  }
  ```

### 最优关键思路或技巧
1. **转化思想**：将字符串子串问题转化为字符间关系问题，无论是用数组记录前后关系（题解一）还是构建有向图（题解二），都使得问题更易于分析和解决。
2. **无解判断**：敏锐地抓住无解的关键条件，如字符不能重复出现、不能有矛盾的前后关系以及不能存在环，通过这些条件快速排除不可能的情况。

### 拓展
同类型题通常围绕字符串的子串性质、字符间关系构建以及无解情况判断展开。类似算法套路是将字符串问题转化为图论或数组关系记录问题，通过分析这些关系来求解。

### 推荐洛谷题目
1. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：涉及字符串的查找与统计，与本题对字符串的处理有相似之处。
2. [P1502 窗口的星星](https://www.luogu.com.cn/problem/P1502)：需要处理字符串中的字符关系，构建符合条件的结果，和本题构建原串思路类似。
3. [P2084 进制转换](https://www.luogu.com.cn/problem/P2084)：虽然主要是进制转换，但在处理字符与数值关系上与本题处理字符间关系有一定共通思维方式。 

---
处理用时：81.04秒