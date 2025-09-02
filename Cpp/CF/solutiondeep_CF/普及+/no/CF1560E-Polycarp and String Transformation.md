# 题目信息

# Polycarp and String Transformation

## 题目描述

Polycarp has a string $ s $ . Polycarp performs the following actions until the string $ s $ is empty ( $ t $ is initially an empty string):

- he adds to the right to the string $ t $ the string $ s $ , i.e. he does $ t = t + s $ , where $ t + s $ is a concatenation of the strings $ t $ and $ s $ ;
- he selects an arbitrary letter of $ s $ and removes from $ s $ all its occurrences (the selected letter must occur in the string $ s $ at the moment of performing this action).

Polycarp performs this sequence of actions strictly in this order.

Note that after Polycarp finishes the actions, the string $ s $ will be empty and the string $ t $ will be equal to some value (that is undefined and depends on the order of removing).

E.g. consider $ s $ ="abacaba" so the actions may be performed as follows:

- $ t $ ="abacaba", the letter 'b' is selected, then $ s $ ="aacaa";
- $ t $ ="abacabaaacaa", the letter 'a' is selected, then $ s $ ="c";
- $ t $ ="abacabaaacaac", the letter 'c' is selected, then $ s $ ="" (the empty string).

You need to restore the initial value of the string $ s $ using only the final value of $ t $ and find the order of removing letters from $ s $ .

## 说明/提示

The first test case is considered in the statement.

## 样例 #1

### 输入

```
7
abacabaaacaac
nowyouknowthat
polycarppoycarppoyarppyarppyrpprppp
isi
everywherevrywhrvryhrvrhrvhv
haaha
qweqeewew```

### 输出

```
abacaba bac
-1
polycarp lcoayrp
is si
everywhere ewyrhv
-1
-1```

# AI分析结果

### 题目内容（已为中文，无需翻译）
Polycarp 有一个字符串 $ s $ 。Polycarp 执行以下操作，直到字符串 $ s $ 为空（ $ t $ 最初是一个空字符串）：
- 他将字符串 $ s $ 追加到字符串 $ t $ 的右侧，即执行 $ t = t + s $ ，其中 $ t + s $ 是字符串 $ t $ 和 $ s $ 的连接；
- 他选择 $ s $ 中的任意一个字母，并从 $ s $ 中删除该字母的所有出现（在执行此操作时，所选字母必须出现在字符串 $ s $ 中）。

Polycarp 严格按照此顺序执行此操作序列。

注意，在 Polycarp 完成操作后，字符串 $ s $ 将为空，字符串 $ t $ 将等于某个值（该值未定义，取决于删除的顺序）。

例如，考虑 $ s $ ="abacaba" ，操作可能按如下方式执行：
- $ t $ ="abacaba" ，选择字母 'b' ，然后 $ s $ ="aacaa" ；
- $ t $ ="abacabaaacaa" ，选择字母 'a' ，然后 $ s $ ="c" ；
- $ t $ ="abacabaaacaac" ，选择字母 'c' ，然后 $ s $ ="" （空字符串）。

你需要仅使用字符串 $ t $ 的最终值来恢复字符串 $ s $ 的初始值，并找出从 $ s $ 中删除字母的顺序。

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是先确定删除字母的顺序，再根据该顺序计算初始字符串 $s$ 的长度并截取初始字符串，最后模拟操作过程来验证解的合法性。
- **思路对比**：各题解在确定删除顺序时，都利用了从字符串 $t$ 末尾向前遍历，越早出现的字符越迟被删除这一特性。在计算初始字符串长度时，都是根据每个字符的出现次数和删除顺序的关系来计算。
- **算法要点**：主要算法要点包括统计字符出现次数、确定删除顺序、计算初始字符串长度、模拟操作过程进行验证。
- **解决难点**：难点在于不仅要保证字符的出现次数符合要求，还要保证字符的出现顺序正确，所以需要模拟操作过程进行验证。

### 所选题解
- **Miraik（4星）**
    - **关键亮点**：思路清晰，详细解释了每一步的原理和可能出现的问题，代码注释丰富，可读性高。
- **LinkZelda（4星）**
    - **关键亮点**：简洁明了地阐述了做法，时间复杂度分析清晰。
- **Illusory_dimes（4星）**
    - **关键亮点**：对解题思路的分析细致，解释了为什么要从后往前找删除顺序以及为什么要进行模拟验证。

### 重点代码
```cpp
// Miraik的代码关键部分
void solve(){
    cin>>s;
    int sz=s.size();
    for(int i=0;i<26;i++)f[i]=0;
    cnt=0;
    for(int i=sz-1;i>=0;i--){//倒序处理，得到第二问的解
        if(!f[s[i]-'a'])ans[++cnt]=s[i]-'a';
        f[s[i]-'a']++;
    }
    l=0;
    for(int i=1;i<=cnt;i++)
        if(f[ans[i]]%(cnt-i+1)!=0){//cnt-i+1即ans[i]出现的轮数
            puts("-1");//这个解已经不合法了
            return;
        }
        else l+=f[ans[i]]/(cnt-i+1);
    s1="",s2="";
    for(int i=0;i<l;i++)s1+=s[i];
    int now=cnt;
    while(s1!=""){
        s2+=s1;
        s3="";
        sz=s1.size();
        for(int i=0;i<sz;i++)
            if(ans[now]!=s1[i]-'a')
                s3+=s1[i];
        s1=s3;
        now--;
    }
    if(s2==s){
        for(int i=0;i<l;i++)cout<<s[i];
        cout<<' ';
        for(int i=cnt;i;i--)putchar(ans[i]+'a');
        puts("");
    }
    else puts("-1");
}
```
**核心实现思想**：先倒序遍历字符串 $s$ 确定删除顺序，再根据删除顺序计算初始字符串长度，截取初始字符串，最后模拟操作过程，将模拟得到的字符串与原字符串比较，判断解是否合法。

### 关键思路或技巧
- **确定删除顺序**：从字符串 $t$ 末尾向前遍历，越早出现的字符越迟被删除。
- **计算初始字符串长度**：根据每个字符的出现次数和删除顺序的关系，若某个字符在第 $q$ 轮操作中被删除，其在初始串中的出现次数为 $\frac{f_i}{q}$ （$f_i$ 为该字符在 $t$ 中的出现次数），若不能整除则无解。
- **模拟验证**：按照题面中的操作过程对得到的解进行模拟，判断模拟得到的字符串是否与原字符串相同，以确保字符的出现顺序也正确。

### 拓展思路
同类型题或类似算法套路通常涉及字符串的操作和模拟，例如字符串的拼接、删除、替换等操作，以及根据最终结果反推初始状态的问题。解题时需要仔细分析操作过程，找出其中的规律和关键信息。

### 推荐洛谷题目
- P1055 [NOIP2008 普及组] ISBN 号码
- P1308 [NOIP2011 普及组] 统计单词数
- P1598 垂直柱状图

### 个人心得摘录与总结
- **Cry_For_theMoon**：赛场上写了一百多行垃圾代码调了一小时，把之前的手速优势全玩没了，提醒我们在比赛中要保持清晰的思路，避免写出复杂且难以调试的代码。
- **きりと**：赛时由于前一天熬夜打派，困得头昏脑涨，没想到 $t$ 中前 $l$ 个就是可能答案，在写 KMP，导致比赛结束约 $30s$ 以后才写出来，提醒我们要保持良好的作息，在比赛中要冷静思考，避免走弯路。

---
处理用时：91.60秒