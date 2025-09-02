# 题目信息

# Interesting Story

## 题目描述

Stephen Queen wants to write a story. He is a very unusual writer, he uses only letters 'a', 'b', 'c', 'd' and 'e'!

To compose a story, Stephen wrote out $ n $ words consisting of the first $ 5 $ lowercase letters of the Latin alphabet. He wants to select the maximum number of words to make an interesting story.

Let a story be a sequence of words that are not necessarily different. A story is called interesting if there exists a letter which occurs among all words of the story more times than all other letters together.

For example, the story consisting of three words "bac", "aaada", "e" is interesting (the letter 'a' occurs $ 5 $ times, all other letters occur $ 4 $ times in total). But the story consisting of two words "aba", "abcde" is not (no such letter that it occurs more than all other letters in total).

You are given a sequence of $ n $ words consisting of letters 'a', 'b', 'c', 'd' and 'e'. Your task is to choose the maximum number of them to make an interesting story. If there's no way to make a non-empty story, output $ 0 $ .

## 说明/提示

In the first test case of the example, all $ 3 $ words can be used to make an interesting story. The interesting story is "bac aaada e".

In the second test case of the example, the $ 1 $ -st and the $ 3 $ -rd words can be used to make an interesting story. The interesting story is "aba aba". Stephen can't use all three words at the same time.

In the third test case of the example, Stephen can't make a non-empty interesting story. So the answer is $ 0 $ .

In the fourth test case of the example, Stephen can use the $ 3 $ -rd and the $ 4 $ -th words to make an interesting story. The interesting story is "c bc".

## 样例 #1

### 输入

```
6
3
bac
aaada
e
3
aba
abcde
aba
2
baba
baba
4
ab
ab
c
bc
5
cbdca
d
a
d
e
3
b
c
ca```

### 输出

```
3
2
0
2
3
2```

# AI分析结果

### 中文重写题目内容

# 有趣的故事

## 题目描述

Stephen Queen 想要写一个故事。他是一个非常不寻常的作家，他只使用字母 'a', 'b', 'c', 'd' 和 'e'！

为了编写故事，Stephen 写下了 $n$ 个单词，每个单词由拉丁字母表的前 $5$ 个小写字母组成。他想选择尽可能多的单词来组成一个有趣的故事。

一个故事是由若干个单词组成的序列，这些单词不一定不同。如果一个故事中存在一个字母，它在所有单词中出现的次数比其他所有字母加起来出现的次数还要多，那么这个故事就是有趣的。

例如，由三个单词 "bac", "aaada", "e" 组成的故事是有趣的（字母 'a' 出现了 $5$ 次，而其他字母总共出现了 $4$ 次）。但是由两个单词 "aba", "abcde" 组成的故事不是有趣的（没有一个字母的出现次数超过其他所有字母的总和）。

给定一个由 $n$ 个单词组成的序列，每个单词由字母 'a', 'b', 'c', 'd' 和 'e' 组成。你的任务是选择尽可能多的单词来组成一个有趣的故事。如果无法组成一个非空的故事，输出 $0$。

## 说明/提示

在第一个样例中，所有 $3$ 个单词都可以用来组成一个有趣的故事。有趣的故事是 "bac aaada e"。

在第二个样例中，第 $1$ 个和第 $3$ 个单词可以用来组成一个有趣的故事。有趣的故事是 "aba aba"。Stephen 不能同时使用所有三个单词。

在第三个样例中，Stephen 无法组成一个非空的有趣故事。因此输出 $0$。

在第四个样例中，Stephen 可以使用第 $3$ 个和第 $4$ 个单词来组成一个有趣的故事。有趣的故事是 "c bc"。

## 样例 #1

### 输入

```
6
3
bac
aaada
e
3
aba
abcde
aba
2
baba
baba
4
ab
ab
c
bc
5
cbdca
d
a
d
e
3
b
c
ca```

### 输出

```
3
2
0
2
3
2```

### 算法分类
贪心

### 综合分析与结论
题目要求从给定的字符串中选择尽可能多的字符串，使得存在一个字母在所有选中的字符串中出现的次数严格大于其他字母的总和。由于字符集大小仅为5，可以通过枚举每个字母，计算每个字符串对该字母的贡献（即该字母出现的次数减去其他字母出现的次数），然后贪心地选择贡献最大的字符串，直到贡献和不再大于0。最后取所有枚举结果中的最大值。

### 所选题解
1. **作者：NXYorz (赞：6)**
   - **星级：5**
   - **关键亮点：**
     - 思路清晰，代码简洁。
     - 通过结构体存储每个字符串的贡献，排序后贪心选择。
     - 代码可读性高，逻辑清晰。
   - **核心代码：**
     ```cpp
     void judge(char x)
     {
         memset(a , 0 , sizeof(a)); ans = 0; 
         for(int i = 1; i <= n; i++)
         {
             int cnt = 0; int len = s[i].length();
             for(int j = 0; j < len; j++)
                 if(s[i][j] == x) cnt++;
             a[i].w = cnt - (len - cnt);a[i].size = len;
         }
         sort(a + 1 , a + 1 + n);
         int sum = 0;
         for(int i = 1; i <= n; i++)
         {
             if(sum + a[i].w <= 0) break;
             sum += a[i].w; ans ++;
         }
         prt = max(prt , ans);
     }
     ```

2. **作者：ncwzdlsd (赞：2)**
   - **星级：4**
   - **关键亮点：**
     - 使用二维数组存储每个字母在每个字符串中的出现次数和差值。
     - 通过排序和贪心选择，思路清晰。
   - **核心代码：**
     ```cpp
     void solve()
     {
         int n;cin>>n;
         for(int i=1;i<=n;i++) for(int j=0;j<5;j++) cnt[j][i]=0;
         for(int i=1;i<=n;i++)
         {
             string s;cin>>s;
             for(int j=0;j<s.length();j++) cnt[s[j]-'a'][i]++;
             for(int j=0;j<5;j++) dif[j][i]=cnt[j][i]*2-s.length();
         }
         int ans=0;
         for(int i=0;i<5;i++)
         {
             sort(dif[i]+1,dif[i]+n+1);
             int now=0,tmp=0;
             int j=n;
             while(now+dif[i][j]>0&&j) now+=dif[i][j],tmp++,j--;
             ans=max(ans,tmp);
         }
         cout<<ans<<'\n';
     }
     ```

3. **作者：KSToki (赞：2)**
   - **星级：4**
   - **关键亮点：**
     - 代码结构清晰，逻辑明确。
     - 通过枚举每个字母，计算差值并排序，贪心选择。
   - **核心代码：**
     ```cpp
     int main()
     {
         T=read();
         while(T--)
         {
             n=read();
             for(R int i=1;i<=n;++i)
                 for(R int j=0;j<5;++j)
                     cnt[i][j]=0;
             for(R int i=1;i<=n;++i)
             {
                 cin>>s;
                 for(R int j=0,up=s.length();j<up;++j)
                     ++cnt[i][s[j]-'a'];
                 for(R int j=0;j<5;++j)
                     a[j][i]=2*cnt[i][j]-s.length();
             }
             ans=0;
             for(R int i=0;i<5;++i)
             {
                 sort(a[i]+1,a[i]+n+1);
                 int res=0,now=0;
                 for(R int j=n;j;--j)
                     if(now+a[i][j]>0)
                     {
                         now+=a[i][j];
                         ++res;
                     }
                 ans=max(ans,res);
             }
             putint(ans);
         }
         return 0;
     }
     ```

### 最优关键思路或技巧
1. **枚举每个字母**：由于字符集大小仅为5，可以枚举每个字母作为可能的主导字母。
2. **计算贡献**：对于每个字符串，计算该字母的贡献（即该字母出现的次数减去其他字母出现的次数）。
3. **贪心选择**：将字符串按贡献从大到小排序，贪心地选择贡献最大的字符串，直到贡献和不再大于0。

### 可拓展之处
类似的问题可以扩展到更大的字符集或更复杂的条件，例如要求多个字母的出现次数满足某种关系。此外，可以考虑动态规划或更复杂的贪心策略来处理更复杂的情况。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1168 中位数](https://www.luogu.com.cn/problem/P1168)
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

### 个人心得
在调试过程中，发现排序后的贪心选择策略非常有效，能够快速找到最优解。此外，通过枚举每个字母的方式，能够简化问题，使得代码更加清晰易读。

---
处理用时：48.51秒