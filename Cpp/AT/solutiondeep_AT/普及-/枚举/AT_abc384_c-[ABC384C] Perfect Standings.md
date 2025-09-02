# 题目信息

# [ABC384C] Perfect Standings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc384/tasks/abc384_c

高橋くんは、プログラミングコンテストを主催することにしました。

コンテストは A 問題、B 問題、C 問題、D 問題、E 問題の $ 5 $ 問からなり、それぞれの配点は $ a $ 点、$ b $ 点、$ c $ 点、$ d $ 点、$ e $ 点です。

コンテストには $ 31 $ 人が参加し、全員が $ 1 $ 問以上解きました。

より具体的には、文字列 `ABCDE` の空でない（連続するとは限らない）部分列すべてについて、その部分列を名前とする参加者が存在し、その参加者は名前に含まれる文字に対応する問題をすべて解き、それ以外の問題は解きませんでした。

例えば、A さんは A 問題のみを、BCE さんは B 問題、C 問題、E 問題を解きました。

参加者の名前を、取った点数が大きいほうから順に出力してください。 ただし、参加者が取った点数は、その参加者が解いた問題の配点の合計です。

ただし、同じ点数を獲得した参加者については、名前が辞書順で小さいほうを先に出力してください。

 辞書順で小さいとは？辞書順とは、一言で説明すると「単語が辞書に載っている順番」を意味します。

より厳密には、英大文字からなる相異なる文字列 $ S,T $ について、$ S $ が $ T $ より辞書順で小さいとは、以下の条件のどちらかが成り立つことを意味します。

- $ S $ の長さ $ |S| $ が $ T $ の長さより短く、$ T $ の先頭 $ |S| $ 文字が $ S $ と一致する
- ある整数 $ 1\leq\ i\leq\min\lbrace|S|,|T|\rbrace $ が存在して、次の $ 2 $ つの条件を両方を満たす
  - $ 1\leq\ j\lt\ i $ を満たすすべての整数 $ j $ に対して $ S $ の $ j $ 文字目と $ T $ の $ j $ 文字目が等しい
  - $ S $ の $ i $ 文字目が $ T $ の $ i $ 文字目よりアルファベット順で小さい
 
例えば、$ S= $ `AB` $ ,T= $ `ABC` とすると、ひとつめの条件が成り立つため $ S $ は $ T $ より小さいです。 また、$ S= $ `ABD` $ ,T= $ `ACD` とすると、ふたつめの条件が $ i=2 $ で成り立つため $ S $ は $ T $ より小さいです。

## 说明/提示

### 制約

- $ 100\leq\ a\leq\ b\leq\ c\leq\ d\leq\ e\leq\ 2718 $
- 入力はすべて整数
 
### Sample Explanation 1

それぞれの参加者の得点は以下のようになります。 !\[\](https://img.atcoder.jp/abc384/4dac80dfad9b0f66c75fec40eedb5e2d.png) 例えば、ADE さんと BCE さんは同じ得点を獲得していますが、ADE さんのほうが辞書順で小さい名前をもつため、ADE さんを先に出力してください。

## 样例 #1

### 输入

```
400 500 600 700 800```

### 输出

```
ABCDE

BCDE

ACDE

ABDE

ABCE

ABCD

CDE

BDE

ADE

BCE

ACE

BCD

ABE

ACD

ABD

ABC

DE

CE

BE

CD

AE

BD

AD

BC

AC

AB

E

D

C

B

A```

## 样例 #2

### 输入

```
800 800 900 900 1000```

### 输出

```
ABCDE

ACDE

BCDE

ABCE

ABDE

ABCD

CDE

ACE

ADE

BCE

BDE

ABE

ACD

BCD

ABC

ABD

CE

DE

AE

BE

CD

AC

AD

BC

BD

AB

E

C

D

A

B```

## 样例 #3

### 输入

```
128 256 512 1024 2048```

### 输出

```
ABCDE

BCDE

ACDE

CDE

ABDE

BDE

ADE

DE

ABCE

BCE

ACE

CE

ABE

BE

AE

E

ABCD

BCD

ACD

CD

ABD

BD

AD

D

ABC

BC

AC

C

AB

B

A```

# AI分析结果

### 题目翻译
高桥先生决定举办一场编程竞赛。

竞赛由 A 问题、B 问题、C 问题、D 问题、E 问题这 5 道题组成，每题的分值分别为 $a$ 分、$b$ 分、$c$ 分、$d$ 分、$e$ 分。

竞赛有 31 人参加，所有人都至少解出了 1 道题。

更具体地说，对于字符串 `ABCDE` 的所有非空（不一定连续）子序列，都存在以该子序列为名字的参赛者，且该参赛者解出了名字中包含的字符所对应的所有问题，其他问题则未解出。

例如，A 先生只解出了 A 问题，BCE 先生解出了 B 问题、C 问题、E 问题。

请按照参赛者得分从高到低的顺序输出他们的名字。这里，参赛者的得分是其解出的问题的分值总和。

对于得分相同的参赛者，请按照名字的字典序从小到大输出。

### 综合分析与结论
这些题解的核心思路都是先计算出每个参赛者的得分，再按照得分从高到低排序，得分相同则按字典序从小到大排序。主要区别在于计算参赛者名字和得分的方式不同。
- **暴力枚举法**：直接列出所有参赛者的名字，手动计算得分，如违规用户名1053866的题解。
- **打表法**：先打表存储所有参赛者的名字，再遍历名字计算得分，如 ryf2011 的题解。
- **位运算枚举法**：利用位运算枚举所有可能的子集，对应参赛者的名字和得分，如 4041nofoundGeoge 的题解。

### 所选题解
- **违规用户名1053866（4星）**：
  - **关键亮点**：思路直接，代码简单易懂，直接列出所有参赛者的名字和得分，然后进行排序。
  - **核心代码**：
```cpp
struct node{
    string s;
    int score;
}st[105];
bool cmp(node a,node b){
    if(a.score!=b.score)
        return a.score>b.score;
    return a.s<b.s;
}
// 手动列出所有参赛者的名字和得分
st[1].s="ABCDE"; st[1].score=a+b+c+d+e;
// ... 其他参赛者 ...
sort(st+1,st+32,cmp);
for(int i=1;i<=31;i++)
    cout<<st[i].s<<"\n";
```
- **ryf2011（4星）**：
  - **关键亮点**：通过打表存储名字，再遍历计算得分，代码结构清晰，易于理解和维护。
  - **核心代码**：
```cpp
string names[]={"ABCDE","BCDE","ACDE",/* ... 其他名字 ... */}; 
struct node{ 
    string name;
    int val;
} p[105];
bool cmp(node a,node b){ 
    if(a.val!=b.val){ 
        return a.val>b.val;
    }
    return a.name<b.name;
}
for(int i=0;i<=30;i++){ 
    p[i+1].name=names[i];
    for(int j=0;j<names[i].size();j++){
        if(names[i][j]=='A') p[i+1].val+=a;
        // ... 其他题目 ...
    }
}
sort(p+1,p+32,cmp); 
for(int i=1;i<=31;i++){ 
    cout<<p[i].name<<'\n';
}
```
- **4041nofoundGeoge（4星）**：
  - **关键亮点**：使用位运算枚举所有子集，巧妙地对应参赛者的名字和得分，代码简洁高效。
  - **核心代码**：
```cpp
map<int, vector<string>> scores;
vector<string> p;
for(int i = 1; i < (1<<5); ++i){
    string name = "";
    int score = 0;
    if(i & (1<<0)){ name += "A"; score += a; }
    if(i & (1<<1)){ name += "B"; score += b; }
    if(i & (1<<2)){ name += "C"; score += c; }
    if(i & (1<<3)){ name += "D"; score += d; }
    if(i & (1<<4)){ name += "E"; score += e; }
    p.push_back(name);
    scores[score].push_back(name);
}
for(auto &it : scores){
    sort(it.second.begin(), it.second.end());
}
for(int i = 2718*5; i >= 100; --i){
    if(scores.find(i) != scores.end()){
        for(auto name : scores[i]){
            cout << name << endl;
        }
    }
}
```

### 最优关键思路或技巧
- **位运算枚举子集**：对于集合元素较少的情况，使用位运算可以方便地枚举所有子集，对应不同的参赛者。
- **结构体存储信息**：使用结构体存储参赛者的名字和得分，方便进行排序操作。

### 可拓展之处
同类型题目可能会有更多的题目数量或更多的参赛者，此时可以使用更高效的算法，如状态压缩动态规划。类似算法套路包括使用位运算解决组合问题、使用自定义比较函数进行排序等。

### 洛谷相似题目推荐
- P1093 [NOIP2007 普及组] 奖学金
- P1781 宇宙总统
- P1104 生日

### 个人心得
本题解中未包含个人心得内容。 

---
处理用时：35.27秒