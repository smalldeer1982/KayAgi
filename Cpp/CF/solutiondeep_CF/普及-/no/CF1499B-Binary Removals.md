# 题目信息

# Binary Removals

## 题目描述

You are given a string $ s $ , consisting only of characters '0' or '1'. Let $ |s| $ be the length of $ s $ .

You are asked to choose some integer $ k $ ( $ k > 0 $ ) and find a sequence $ a $ of length $ k $ such that:

- $ 1 \le a_1 < a_2 < \dots < a_k \le |s| $ ;
- $ a_{i-1} + 1 < a_i $ for all $ i $ from $ 2 $ to $ k $ .

The characters at positions $ a_1, a_2, \dots, a_k $ are removed, the remaining characters are concatenated without changing the order. So, in other words, the positions in the sequence $ a $ should not be adjacent.

Let the resulting string be $ s' $ . $ s' $ is called sorted if for all $ i $ from $ 2 $ to $ |s'| $ $ s'_{i-1} \le s'_i $ .

Does there exist such a sequence $ a $ that the resulting string $ s' $ is sorted?

## 说明/提示

In the first testcase you can choose a sequence $ a=[1,3,6,9] $ . Removing the underlined letters from "10101011011" will produce a string "0011111", which is sorted.

In the second and the third testcases the sequences are already sorted.

In the fourth testcase you can choose a sequence $ a=[3] $ . $ s'= $ "11", which is sorted.

In the fifth testcase there is no way to choose a sequence $ a $ such that $ s' $ is sorted.

## 样例 #1

### 输入

```
5
10101011011
0000
11111
110
1100```

### 输出

```
YES
YES
YES
YES
NO```

# AI分析结果

### 题目内容
# Binary Removals

## 题目描述
给定一个仅由字符 '0' 或 '1' 组成的字符串 $s$ 。设 $|s|$ 为 $s$ 的长度。

要求选择某个整数 $k$（$k > 0$）并找到一个长度为 $k$ 的序列 $a$ ，使得：
- $1 \le a_1 < a_2 < \dots < a_k \le |s|$ ；
- 对于所有从 $2$ 到 $k$ 的 $i$ ，有 $a_{i - 1} + 1 < a_i$ 。

位于位置 $a_1, a_2, \dots, a_k$ 的字符将被移除，其余字符按顺序连接在一起，不改变顺序。也就是说，序列 $a$ 中的位置不应相邻。

设得到的字符串为 $s'$ 。如果对于所有从 $2$ 到 $|s'|$ 的 $i$ ，都有 $s'_{i - 1} \le s'_i$ ，则称 $s'$ 是已排序的。

是否存在这样的序列 $a$ ，使得得到的字符串 $s'$ 是已排序的？

## 说明/提示
在第一个测试用例中，可以选择序列 $a = [1, 3, 6, 9]$ 。从 “10101011011” 中移除带下划线的字母将生成字符串 “0011111” ，它是已排序的。

在第二个和第三个测试用例中，序列已经是已排序的。

在第四个测试用例中，可以选择序列 $a = [3]$ 。$s' = $ “11” ，它是已排序的。

在第五个测试用例中，不存在这样的序列 $a$ 使得 $s'$ 是已排序的。

## 样例 #1
### 输入
```
5
10101011011
0000
11111
110
1100
```
### 输出
```
YES
YES
YES
YES
NO
```

### 算法分类
字符串

### 题解综合分析与结论
多数题解的核心思路是判断字符串中是否存在 “11” 出现在 “00” 之前的情况。因为不能连续删除字符，若 “11” 在 “00” 前，无论如何删除都无法使剩余字符串单调不降。而 “__zyq_666_kpzc__”、“slzx2021zjx” 等多位作者的题解都基于此思路，通过遍历字符串标记是否出现 “11” 及后续是否出现 “00” 来判断结果。“Silence_water” 的题解采用动态规划，设计状态 $dp[i][0/1][0/1]$ 进行复杂的状态转移判断，虽能解决问题，但相对复杂。

### 所选的题解
- **作者：__zyq_666_kpzc__ 星级：4星**
  - **关键亮点**：思路简洁清晰，代码实现直接。通过一次遍历字符串，利用两个布尔变量分别标记是否出现 “11” 以及出现 “11” 后是否出现 “00” ，从而快速判断结果。
  - **重点代码核心思想**：遍历字符串，若发现相邻字符相同，判断是否为 “11” ，若是则标记；若已标记 “11” 且当前相邻字符为 “00” ，则标记不满足条件。最后根据标记输出结果。
  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  #define int long long

  signed main(){
      ios::sync_with_stdio(0);
      cin.tie(0),cout.tie(0);
      int T,ma_x=-1e9,ma_y=-1e9;
      cin>>T;
      while(T--){
          string s;
          cin>>s;
          bool f=false;
          bool ff=false;
          for(int i=1;i<s.size();i++){
              if(s[i]==s[i-1]){
                  if(s[i]=='1')f=true;
                  else if(f==true)ff=true;
              }
          }
          if(f==ff&&f==true)cout<<"NO\n";
          else cout<<"YES\n";
      } 
      return 0;
  } 
  ```
- **作者：slzx2021zjx 星级：4星**
  - **关键亮点**：同样基于核心判断思路，代码逻辑清晰，采用常规的遍历方式，适合初学者理解。
  - **重点代码核心思想**：遍历字符串，标记是否出现 “11” ，若已标记且出现 “00” ，则输出 “NO” ，否则输出 “YES” 。
  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,m,T;
  char a[105];
  bool k,kk;
  int main()
  {
      ios::sync_with_stdio(0);
      cin.tie(0);
      cout.tie(0);
      cin>>T;
      while(T--){
          cin>>a+1;
          for(int i=1;i<=101;i++){
              if(a[i]=='1'&&a[i+1]=='1') k=1;
              if(k==1&&a[i]=='0'&&a[i+1]=='0') kk=1;
          }
          if(kk==1) cout<<"NO"<<endl;
          else cout<<"YES"<<endl;
          k=0,kk=0;
      }
      return 0;
  }
  ```
- **作者：Silence_water 星级：4星**
  - **关键亮点**：运用动态规划解决问题，状态设计巧妙，能全面考虑各种情况。
  - **重点代码核心思想**：定义状态 $dp[i][0/1][0/1]$ 分别表示当前到第 $i$ 个字母，最后一位是 $0/1$ ，第 $i$ 个字母有没有被移除，是否存在一种移除方案满足题意。根据当前字符是 “0” 还是 “1” 进行分类讨论，从之前状态转移得到当前状态。
  ```cpp
  void solve()
  {
      scanf("%s",s+1);n=strlen(s+1);
      memset(dp,false,sizeof(dp));
      dp[0][0][0]=true;
      for(int i=1;i<=n;i++)
      {
          int c=s[i]-'0';
          if(c==0)
          {
              dp[i][0][0]|=(dp[i-1][0][0]||dp[i-1][0][1]);
              dp[i][0][1]|=(dp[i-1][0][0]);
              dp[i][1][1]|=(dp[i-1][1][0]||dp[i-1][0][0]);
          }
          else
          {
              dp[i][1][1]|=(dp[i-1][0][0]||dp[i-1][1][0]);
              dp[i][1][0]|=(dp[i-1][0][0]||dp[i-1][0][1]||dp[i-1][1][0]||dp[i-1][1][1]);
              dp[i][0][1]|=(dp[i-1][0][0]);
          }
      }
      bool ac=(dp[n][0][0]||dp[n][0][1]||dp[n][1][0]||dp[n][1][1]);
      if(ac)puts("YES");
      else puts("NO");
  }
  ```

### 最优关键思路或技巧
最优思路是抓住不能连续删除字符这一条件，分析得出若 “11” 出现在 “00” 之前则无法使剩余字符串单调不降，通过简单遍历字符串判断这种情况是否存在，实现简洁高效。

### 拓展思路
同类型题常围绕字符串的操作和性质判断，类似算法套路是分析关键子串或字符顺序对最终结果的影响。例如在一些字符串变换题目中，通过分析特定子串的出现顺序及操作限制，找到判断能否达成目标的条件。

### 推荐洛谷题目
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：涉及字符串查找与统计，与本题类似，需对字符串进行遍历分析。
- [P1125 笨小猴](https://www.luogu.com.cn/problem/P1125)：通过对字符串中字符出现次数的分析得出结论，锻炼对字符串性质的处理能力。
- [P1593 因子和阶乘](https://www.luogu.com.cn/problem/P1593)：虽然涉及数学计算，但同样需要对输入数据（可看作字符串）进行处理和分析，与本题思路有相通之处。 

---
处理用时：75.71秒