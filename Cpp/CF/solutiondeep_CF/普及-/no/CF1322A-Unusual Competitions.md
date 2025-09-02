# 题目信息

# Unusual Competitions

## 题目描述

A bracketed sequence is called correct (regular) if by inserting "+" and "1" you can get a well-formed mathematical expression from it. For example, sequences "(())()", "()" and "(()(()))" are correct, while ")(", "(()" and "(()))(" are not.

The teacher gave Dmitry's class a very strange task — she asked every student to come up with a sequence of arbitrary length, consisting only of opening and closing brackets. After that all the students took turns naming the sequences they had invented. When Dima's turn came, he suddenly realized that all his classmates got the correct bracketed sequence, and whether he got the correct bracketed sequence, he did not know.

Dima suspects now that he simply missed the word "correct" in the task statement, so now he wants to save the situation by modifying his sequence slightly. More precisely, he can the arbitrary number of times (possibly zero) perform the reorder operation.

The reorder operation consists of choosing an arbitrary consecutive subsegment (substring) of the sequence and then reordering all the characters in it in an arbitrary way. Such operation takes $ l $ nanoseconds, where $ l $ is the length of the subsegment being reordered. It's easy to see that reorder operation doesn't change the number of opening and closing brackets. For example for "))((" he can choose the substring ")(" and do reorder ")()(" (this operation will take $ 2 $ nanoseconds).

Since Dima will soon have to answer, he wants to make his sequence correct as fast as possible. Help him to do this, or determine that it's impossible.

## 说明/提示

In the first example we can firstly reorder the segment from first to the fourth character, replacing it with "()()", the whole sequence will be "()()())(". And then reorder the segment from the seventh to eighth character, replacing it with "()". In the end the sequence will be "()()()()", while the total time spent is $ 4 + 2 = 6 $ nanoseconds.

## 样例 #1

### 输入

```
8
))((())(```

### 输出

```
6```

## 样例 #2

### 输入

```
3
(()```

### 输出

```
-1```

# AI分析结果

### 题目内容
#### 异常竞赛
#### 题目描述
一个括号序列被称为正确（规则）的，如果通过插入“+”和“1”，你可以从它得到一个格式良好的数学表达式。例如，序列“(())()”、“()”和“(()(()))”是正确的，而“)("、“(()”和“(()))(”是不正确的。

老师给德米特里的班级布置了一个非常奇怪的任务——她要求每个学生想出一个任意长度的序列，该序列仅由左括号和右括号组成。之后，所有学生依次说出他们想出的序列。轮到迪玛时，他突然意识到他所有的同学都得到了正确的括号序列，而他自己得到的括号序列是否正确，他并不清楚。

迪玛现在怀疑他只是在任务说明中遗漏了“正确”这个词，所以现在他想通过稍微修改他的序列来挽救局面。更准确地说，他可以任意次数（可能为零次）执行重新排序操作。

重新排序操作包括选择序列中任意一个连续的子段（子串），然后以任意方式重新排列其中的所有字符。这样的操作需要 $l$ 纳秒，其中 $l$ 是被重新排序的子段的长度。很容易看出，重新排序操作不会改变左括号和右括号的数量。例如，对于“))((”，他可以选择子串“)("并重新排序为“)()(”（此操作将花费 2 纳秒）。

由于迪玛很快就得回答，他想尽快使他的序列正确。帮助他完成这个任务，或者确定这是不可能的。
#### 说明/提示
在第一个示例中，我们可以首先重新排列从第一个到第四个字符的段，将其替换为“()()”，整个序列将变为“()()())("。然后重新排列从第七个到第八个字符的段，将其替换为“()”。最后，序列将变为“()()()()”，而总共花费的时间是 $4 + 2 = 6$ 纳秒。
#### 样例 #1
**输入**
```
8
))((())(
```
**输出**
```
6
```
#### 样例 #2
**输入**
```
3
(()
```
**输出**
```
-1
```
### 算法分类
贪心
### 综合分析与结论
所有题解都基于括号匹配的基本性质来解题，核心思路都是先判断括号总数是否相等，若不相等则直接判定无法构成正确序列。对于总数相等的情况，不同题解采用了不同的贪心策略来确定最小重排代价。
1. **tommymio题解**：利用栈匹配括号，同时结合前缀和来判断一对匹配括号两侧子串是否合法，若合法则减去这对括号的贡献，时间复杂度为 $O(n)$。
2. **sycqwq题解**：通过扫描括号串，根据左右括号的匹配情况更新答案，遇到不匹配的右括号则增加答案和未匹配右括号计数，遇到左括号则根据未匹配右括号情况处理，同样时间复杂度为 $O(n)$。
3. **xht题解**：通过前缀和将序列按和为0的位置分段，对每段判断是否有负的前缀和，若有则该段需重排，时间复杂度为 $O(n)$。
4. **VinstaG173题解**：令左括号为1，右括号为 -1 ，扫描过程中标记前缀和小于0的情况，当遇到前缀和为0时处理并解除标记，记录需重排区间长度，时间复杂度为 $O(n)$。

综合来看，各题解思路清晰，实现方式略有不同，但都能有效解决问题。其中tommymio的题解利用栈和前缀和的结合，逻辑较为巧妙；sycqwq的题解思路直接，代码简洁易懂；VinstaG173的题解利用前缀和的特性，实现简洁高效。
### 所选的题解
- **tommymio题解**
  - **星级**：4星
  - **关键亮点**：巧妙结合栈匹配括号与前缀和判断子串合法性，能精准减去无需重排的括号对的贡献。
  ```cpp
  int top=0;
  int st[1000005],sum[1000005];
  char a[1000005];
  int main() {
      int n,res;
      scanf("%d%s",&n,a+1);
      res=n;
      for(register int i=1;i<=n;++i) {
          if(a[i]=='(') sum[i]=sum[i-1]+1;
          else sum[i]=sum[i-1]-1;
      }
      if(sum[n]!=0) {printf("-1\n");return 0;}
      for(register int i=1;i<=n;++i) {
          if(a[i]=='(') {st[++top]=i;}
          else if(top) {
              if(sum[st[top]-1]==0&&sum[n]-sum[i]==0) res-=i-st[top]+1;
              --top;
          }
      }
      printf("%d\n",res);
      return 0;
  }
  ```
  核心实现思想：先通过前缀和数组 `sum` 记录每个位置的括号状态，若最终 `sum[n]` 不为0 则直接返回 -1。然后利用栈 `st` 匹配括号，当匹配到一对括号时，通过前缀和判断其两侧子串是否合法，若合法则从总长度 `res` 中减去这对括号的长度。
- **sycqwq题解**
  - **星级**：4星
  - **关键亮点**：思路直接，通过简单的计数和条件判断来处理括号匹配与重排代价。
  ```cpp
  #include<bits/stdc++.h>
  #define inf 2147283647
  using namespace std;
  int ans,l,r;
  int main(){
      int n;
      cin>>n;
      string s;
      cin>>s;
      int l1=s.size();
      for(int i=0;i<l1;i++)
      {
          if(s[i]=='(')
              ++l;
          if(s[i]==')')
              ++r;
      }
      if(l!=r)
      {
          cout<<-1;
          return 0;
      }
      l=0,r=0;
      for(int i=0;i<l1;i++)
      {
          if(s[i]==')')
          {
              if(l==0)
              {
                  ++r;
                  ++ans;
              }
              else
                  --l;
          }
          if(s[i]=='(')
          {
              if(r==0)
              {
                  ++l;
              }
              else
              {
                  --r;
                  ++ans;
              }
          }
      }
      cout<<ans;
      return 0;
  }
  ```
  核心实现思想：先统计左右括号总数判断是否相等，若不相等则输出 -1。然后再次遍历字符串，根据左右括号出现顺序及匹配情况更新答案 `ans` 和未匹配括号计数 `l`、`r`。
- **VinstaG173题解**
  - **星级**：4星
  - **关键亮点**：将括号转化为数字，利用前缀和特性标记并处理需重排区间，实现简洁高效。
  ```cpp
  #include<cstdio>
  int n;
  char s[1000007];
  int sum,ans,flg,lst=-1;
  int main()
  {
      scanf(" %d %s",&n,s);
      for(int i=0;i<n;++i)
      {
          if(s[i]=='(')++sum;
          else --sum;
          if(sum<0)flg=1;
          else if(sum==0)
          {
              if(flg)ans+=i-lst;
              lst=i;flg=0;
          }
      }
      if(sum)printf("-1");
      else printf("%d\n",ans);
      return 0;
  }
  ```
  核心实现思想：遍历字符串，将左括号设为1，右括号设为 -1 ，计算前缀和 `sum` 。当 `sum` 小于0时标记 `flg` ，当 `sum` 等于0时，若之前有标记则将当前位置与上次和为0位置的差加到答案 `ans` 中，并更新记录位置和解除标记。最后根据最终 `sum` 是否为0输出结果。
### 最优关键思路或技巧
1. **利用前缀和**：如tommymio、xht、VinstaG173题解，通过记录前缀和来判断子串状态，有助于分析括号匹配情况及确定需重排区间。
2. **贪心策略**：各题解都基于贪心思想，在满足括号总数相等的前提下，尽可能减少重排操作，如tommymio利用栈匹配合法括号对并减去其贡献，sycqwq根据括号匹配情况实时更新答案等。
### 可拓展之处
此类题目属于括号匹配及字符串操作优化问题，类似套路可应用于其他涉及字符串重排优化以满足特定条件的题目，如判断回文串重排能否构成合法形式等。关键在于找到合适的状态记录方式（如前缀和）以及贪心策略来优化操作。
### 洛谷相似题目
1. **P1047 [NOIP2005 普及组] 校门外的树**：涉及线段覆盖与统计，可通过类似贪心思想解决。
2. **P1223 排队接水**：同样是贪心策略应用，通过对数据排序并按一定规则处理以得到最优解。
3. **P1996 约瑟夫问题**：利用循环链表或数组模拟，结合贪心策略解决问题，与本题思路有相通之处。
### 个人心得摘录
无

---
处理用时：89.55秒