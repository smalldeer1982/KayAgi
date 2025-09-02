# 题目信息

# Unforgivable Curse (easy version)

## 题目描述

This is an easy version of the problem. In this version, $ k $ is always $ 3 $ .

The chief wizard of the Wizengamot once caught the evil wizard Drahyrt, but the evil wizard has returned and wants revenge on the chief wizard. So he stole spell $ s $ from his student Harry.

The spell — is a $ n $ -length string of lowercase Latin letters.

Drahyrt wants to replace spell with an unforgivable curse — string $ t $ .

Drahyrt, using ancient magic, can swap letters at a distance $ k $ or $ k+1 $ in spell as many times as he wants. In this version of the problem, you can swap letters at a distance of $ 3 $ or $ 4 $ . In other words, Drahyrt can change letters in positions $ i $ and $ j $ in spell $ s $ if $ |i-j|=3 $ or $ |i-j|=4 $ .

For example, if $ s =  $ "talant" and $ t =  $ "atltna", Drahyrt can act as follows:

- swap the letters at positions $ 1 $ and $ 4 $ to get spell "aaltnt".
- swap the letters at positions $ 2 $ and $ 6 $ to get spell "atltna".

You are given spells $ s $ and $ t $ . Can Drahyrt change spell $ s $ to $ t $ ?

## 说明/提示

The first example is explained in the condition.

In the second example we can proceed as follows:

- Swap the letters at positions $ 2 $ and $ 5 $ (distance $ 3 $ ), then we get the spell "aaacbba".
- Swap the letters at positions $ 4 $ and $ 7 $ (distance $ 3 $ ), then you get the spell "aaaabbc".

In the third example, we can show that it is impossible to get the string $ t $ from the string $ s $ by swapping the letters at a distance of $ 3 $ or $ 4 $ .

In the fourth example, for example, the following sequence of transformations is appropriate:

- "accio" $ \rightarrow $ "aocic" $ \rightarrow $ "cocia" $ \rightarrow $ "iocca" $ \rightarrow $ "aocci" $ \rightarrow $ "aicco" $ \rightarrow $ "cicao"

In the fifth example, you can show that it is impossible to get the string $ s $ from the string $ t $ .

In the sixth example, it is enough to swap the two outermost letters.

## 样例 #1

### 输入

```
7
6 3
talant
atltna
7 3
abacaba
aaaabbc
12 3
abracadabraa
avadakedavra
5 3
accio
cicao
5 3
lumos
molus
4 3
uwjt
twju
4 3
kvpx
vxpk```

### 输出

```
YES
YES
NO
YES
NO
YES
NO```

# AI分析结果

### 题目内容重写（中文）

# 不可饶恕的诅咒（简单版）

## 题目描述

这是该问题的简单版本。在这个版本中，$k$ 始终为 $3$。

魔法部首席巫师曾经抓住了邪恶的巫师 Drahyrt，但邪恶巫师已经归来，并想要报复首席巫师。因此，他从他的学生 Harry 那里偷走了咒语 $s$。

咒语是一个长度为 $n$ 的小写拉丁字母字符串。

Drahyrt 想要用一个不可饶恕的诅咒——字符串 $t$ 来替换这个咒语。

Drahyrt 使用古老的魔法，可以任意次地交换咒语中距离为 $k$ 或 $k+1$ 的字母。在这个版本的问题中，你可以交换距离为 $3$ 或 $4$ 的字母。换句话说，Drahyrt 可以交换咒语 $s$ 中位置 $i$ 和 $j$ 的字母，如果 $|i-j|=3$ 或 $|i-j|=4$。

例如，如果 $s = $ "talant" 且 $t = $ "atltna"，Drahyrt 可以按以下步骤操作：

- 交换位置 $1$ 和 $4$ 的字母，得到咒语 "aaltnt"。
- 交换位置 $2$ 和 $6$ 的字母，得到咒语 "atltna"。

你被给定咒语 $s$ 和 $t$。Drahyrt 能否将咒语 $s$ 变为 $t$？

## 说明/提示

第一个例子在题目描述中已经解释。

在第二个例子中，我们可以按以下步骤操作：

- 交换位置 $2$ 和 $5$（距离为 $3$），得到咒语 "aaacbba"。
- 交换位置 $4$ 和 $7$（距离为 $3$），得到咒语 "aaaabbc"。

在第三个例子中，我们可以证明无法通过交换距离为 $3$ 或 $4$ 的字母将字符串 $s$ 变为 $t$。

在第四个例子中，例如，以下变换序列是合适的：

- "accio" $ \rightarrow $ "aocic" $ \rightarrow $ "cocia" $ \rightarrow $ "iocca" $ \rightarrow $ "aocci" $ \rightarrow $ "aicco" $ \rightarrow $ "cicao"

在第五个例子中，你可以证明无法将字符串 $s$ 变为 $t$。

在第六个例子中，只需交换最外层的两个字母。

### 算法分类

字符串、模拟

### 题解分析与结论

1. **核心思路**：通过交换距离为 $k$ 或 $k+1$ 的字母，判断是否可以将字符串 $s$ 变为 $t$。关键在于判断哪些位置的字符可以被交换，以及字符的总体分布是否一致。

2. **难点**：确定哪些位置的字符无法被交换，以及如何通过这些交换操作实现字符的重新排列。

3. **优化点**：通过统计字符的频率，先判断两个字符串的字符分布是否一致，再检查无法交换的位置是否已经匹配。

### 精选题解

#### 题解1：作者：yyz1005 (赞：9)
- **星级**：★★★★★
- **关键亮点**：通过排序和字符频率统计，快速判断字符分布是否一致，再检查无法交换的位置是否匹配。
- **代码核心**：
  ```cpp
  sort(s11.begin(),s11.end());
  sort(s22.begin(),s22.end());
  if(s11!=s22) puts("NO");
  else {
      for(ll i = 0; i < n; i++){
          if(i-k<0&&i+k>=n&&s1[i]!=s2[i]){
              puts("NO");
              break;
          }
          if(i==n-1) puts("YES");
      }
  }
  ```

#### 题解2：作者：_GW_ (赞：2)
- **星级**：★★★★
- **关键亮点**：通过字符频率统计和越界检查，判断是否可以通过交换操作实现目标字符串。
- **代码核心**：
  ```cpp
  for(int i=0;i<n;i++) a[s[i]]++,b[ss[i]]++;
  for(int i=0;i<26;i++) {
      if(a['a'+i]!=b['a'+i]) {
          flag=0;
          cout<<"NO"<<endl;
          break;
      }
  }
  for(int i=0;i<n;i++) {
      if(i+k>=n&&i-k<0&&s[i]!=ss[i]&&flag==1) {
          flag=0;
          cout<<"NO"<<endl;
      }
  }
  ```

#### 题解3：作者：Larryyu (赞：2)
- **星级**：★★★★
- **关键亮点**：通过字符频率统计和位置检查，判断是否可以通过交换操作实现目标字符串。
- **代码核心**：
  ```cpp
  for(int i=0;i<n;i++){
      vis1[a[i]-'a'+1]++;
      vis2[b[i]-'a'+1]++;
  }
  for(int i=1;i<=26;i++) {
      if(vis1[i]!=vis2[i]){
          cout<<"NO"<<endl;
          return ;
      }
  }
  for(int i=0;i<n;i++){
      if(i+k>=n&&i-k<0){
          if(a[i]!=b[i]){
              cout<<"NO"<<endl;
              return ;
          }
      }
  }
  ```

### 最优关键思路

1. **字符频率统计**：首先统计两个字符串中每个字符的频率，确保字符分布一致。
2. **位置检查**：检查无法交换的位置是否已经匹配，确保这些位置的字符不需要交换。
3. **排序**：通过排序快速判断字符分布是否一致。

### 拓展思路

1. **类似题目**：可以考虑更复杂的交换规则，如任意距离的交换，或者限制交换次数。
2. **优化**：可以通过图论中的连通性来判断字符是否可以交换到目标位置。

### 推荐题目

1. [CF1800E2](https://www.luogu.com.cn/problem/CF1800E2)
2. [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：38.06秒