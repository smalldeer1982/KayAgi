# 题目信息

# Gotta Catch Em' All!

## 题目描述

Bash wants to become a Pokemon master one day. Although he liked a lot of Pokemon, he has always been fascinated by Bulbasaur the most. Soon, things started getting serious and his fascination turned into an obsession. Since he is too young to go out and catch Bulbasaur, he came up with his own way of catching a Bulbasaur.

Each day, he takes the front page of the newspaper. He cuts out the letters one at a time, from anywhere on the front page of the newspaper to form the word "Bulbasaur" (without quotes) and sticks it on his wall. Bash is very particular about case — the first letter of "Bulbasaur" must be upper case and the rest must be lower case. By doing this he thinks he has caught one Bulbasaur. He then repeats this step on the left over part of the newspaper. He keeps doing this until it is not possible to form the word "Bulbasaur" from the newspaper.

Given the text on the front page of the newspaper, can you tell how many Bulbasaurs he will catch today?

Note: uppercase and lowercase letters are considered different.

## 说明/提示

In the first case, you could pick: Bulbbasaur.

In the second case, there is no way to pick even a single Bulbasaur.

In the third case, you can rearrange the string to BulbasaurBulbasauraddrgndgddgargndbb to get two words "Bulbasaur".

## 样例 #1

### 输入

```
Bulbbasaur
```

### 输出

```
1
```

## 样例 #2

### 输入

```
F
```

### 输出

```
0
```

## 样例 #3

### 输入

```
aBddulbasaurrgndgbualdBdsagaurrgndbb
```

### 输出

```
2
```

# AI分析结果

### 题目内容重写

Bash有一天想成为一名宠物小精灵大师。虽然他喜欢很多口袋妖怪，但他一直对Bulbasaur（妙蛙种子：在它出生的时候背上就背着种子。妙蛙种子经常在阳光下酣睡。它背上的种子通过吸收阳光渐渐长大）最为着迷。很快，事情开始变得严肃起来，他的迷恋变成了一种痴迷。由于他太小（未成年），不能出去捕捉Bulbasaur，他想出了自己捕捉Bulbasaur的方式。

每天，他都会看报纸的头版（他很闲）。他从报纸头版的任何地方一次切出一个字母（闲的一批），形成“Bulbasaur”字样（木有引号好吧！）并将它贴在墙上。 Bash非常讲究（是一个活泼的讲究怪）“Bulbasaur”的第一个字母必须是大写字母，其余字母必须是小写字母。通过这样做，他认为他抓住了一个Bulbasaur，（然后放入精灵球是吧！）。然后他在左边的报纸上重复了这一步骤。他一直这样做，直到不可能从报纸上形成“Bulbasaur”这个词。

鉴于报纸头版的文字，你能告诉他今天会抓到多少个Bulbasaurs？

注意：大写和小写被视为不同。

### 题解分析与结论

这道题的核心是通过统计字符串中组成“Bulbasaur”所需的各个字母的数量，然后根据字母的重复次数（如`u`和`a`出现两次）来确定最多可以组成多少个“Bulbasaur”。以下是各题解的要点总结：

1. **外太空**：使用数组计数，统计每个字母的出现次数，特别注意`u`和`a`需要除以2。代码简洁，思路清晰。
2. **pigstd**：使用数组计数，通过一个数组存储“Bulbasaur”中每个字母的出现次数，`u`和`a`除以2，最后取最小值。
3. **hanyuchen2019**：使用桶计数，特别注意大写字母`B`的处理，其他大写字母忽略。通过木桶原理确定最小数量。
4. **_Cloud_**：使用数组模拟，统计每个字母的数量，通过循环减去已组成的“Bulbasaur”的字母数量，直到无法组成。
5. **moqizhu2005**：使用STL的`map`来统计字母数量，`u`和`a`除以2，最后取最小值。
6. **Hanson水题大佬**：使用暴力枚举，统计每个字母的数量，`u`和`a`加0.5，最后取最小值。
7. **A_Cute_757**：使用数组计数，统计每个字母的数量，`u`和`a`除以2，最后取最小值。
8. **Jinyeke**：使用数组统计字母数量，`u`和`a`除以2，最后取最小值。
9. **CZQ_King**：使用数组计数，统计每个字母的数量，`u`和`a`除以2，最后取最小值。
10. **RioBlu**：使用数组统计字母数量，`u`和`a`通过特殊处理，最后取最小值。

### 评分较高的题解

1. **外太空**（5星）
   - 关键亮点：代码简洁，思路清晰，使用数组计数，特别处理`u`和`a`的重复次数。
   - 核心代码：
     ```cpp
     for(int i=0;i<n;i++) {
         if(st[i]=='B') B++;
         if(st[i]=='u') u++;
         if(st[i]=='l') l++;
         if(st[i]=='b') b++;
         if(st[i]=='a') a++;
         if(st[i]=='s') s++;
         if(st[i]=='r') r++;
     }
     a/=2; u/=2;
     cout<<min(min(B,min(u,l)),min(min(b,a),min(s,r)));
     ```

2. **pigstd**（4星）
   - 关键亮点：使用数组计数，通过一个数组存储“Bulbasaur”中每个字母的出现次数，`u`和`a`除以2，最后取最小值。
   - 核心代码：
     ```cpp
     for (int i=0;i<len;i++) {
         char ch=s[i];
         for (int j=0;j<lenb;j++)
             if (b[j]==ch) a[j]++;
     }
     a[4]/=2; a[1]/=2;
     int minn=999999;
     for (int i=0;i<lenb;i++) minn=min(minn,a[i]);
     cout<<minn;
     ```

3. **hanyuchen2019**（4星）
   - 关键亮点：使用桶计数，特别注意大写字母`B`的处理，其他大写字母忽略。通过木桶原理确定最小数量。
   - 核心代码：
     ```cpp
     while(cin>>ch) {
         if(ch=='B') t[26]++;
         else if(ch>='a'&&ch<='z') t[ch-'a']++;
     }
     int ans=99999999;
     if(t['a'-'a']/2<ans) ans=t['a'-'a']/2;
     if(t['b'-'a']<ans)   ans=t['b'-'a'];
     if(t['l'-'a']<ans)   ans=t['l'-'a'];
     if(t['r'-'a']<ans)   ans=t['r'-'a'];
     if(t['s'-'a']<ans)   ans=t['s'-'a'];
     if(t['u'-'a']/2<ans) ans=t['u'-'a']/2;
     if(t[26]<ans)        ans=t[26];
     cout<<ans;
     ```

### 最优关键思路与技巧

1. **数组计数法**：通过数组统计每个字母的出现次数，特别处理重复字母（如`u`和`a`需要除以2）。
2. **木桶原理**：最终的“Bulbasaur”数量取决于最少的字母数量。
3. **STL的`map`**：使用`map`可以更方便地统计字母数量，但代码复杂度稍高。

### 可拓展之处

- **类似题目**：可以扩展到其他需要统计字母数量并计算组合数的题目，如统计单词“banana”可以组成多少个“banana”。
- **优化思路**：可以通过哈希表或更高效的数据结构来优化字母数量的统计。

### 推荐题目

1. **P1179**：统计字符串中某个字符的出现次数。
2. **P1308**：统计单词在文本中的出现次数。
3. **P1598**：统计字母在文本中的出现频率。

### 个人心得摘录

- **外太空**：提到“其实这道题并不难，使用数组计数可以过”，强调了数组计数的简单性。
- **hanyuchen2019**：提到“如果忘了判断是不是其他的大写字母，你会在第2个测试点光荣的RE”，提醒了处理大写字母的重要性。

---
处理用时：43.33秒