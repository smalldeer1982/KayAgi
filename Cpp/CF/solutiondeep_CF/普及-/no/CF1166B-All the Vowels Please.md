# 题目信息

# All the Vowels Please

## 题目描述

Tom loves vowels, and he likes long words with many vowels. His favorite words are vowelly words. We say a word of length $ k $ is vowelly if there are positive integers $ n $ and $ m $ such that $ n\cdot m = k $ and when the word is written by using $ n $ rows and $ m $ columns (the first row is filled first, then the second and so on, with each row filled from left to right), every vowel of the English alphabet appears at least once in every row and every column.

You are given an integer $ k $ and you must either print a vowelly word of length $ k $ or print $ -1 $ if no such word exists.

In this problem the vowels of the English alphabet are 'a', 'e', 'i', 'o' ,'u'.

## 说明/提示

In the second example, the word "agoeuioaeiruuimaeoieauoweouoiaouimae" can be arranged into the following $ 6 \times 6 $ grid:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1166B/7d474325157104f047038dc9401e0f23cf51cf99.png)It is easy to verify that every row and every column contain all the vowels.

## 样例 #1

### 输入

```
7
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
36
```

### 输出

```
agoeuioaeiruuimaeoieauoweouoiaouimae```

# AI分析结果

### 题目内容
# 请给出所有元音字母

## 题目描述
汤姆喜欢元音字母，他喜欢含有很多元音字母的长单词。他最喜欢的单词是 “元音丰富的单词”。我们说一个长度为 $k$ 的单词是 “元音丰富的单词”，如果存在正整数 $n$ 和 $m$ 使得 $n \cdot m = k$，并且当这个单词以 $n$ 行 $m$ 列的形式书写时（先填充第一行，然后是第二行，依此类推，每行从左到右填充），英语字母表中的每个元音字母在每行和每列中至少出现一次。

给定一个整数 $k$，你必须要么输出一个长度为 $k$ 的 “元音丰富的单词”，要么如果不存在这样的单词则输出 $-1$。

在这个问题中，英语字母表中的元音字母是 'a', 'e', 'i', 'o', 'u'。

## 说明/提示
在第二个示例中，单词 “agoeuioaeiruuimaeoieauoweouoiaouimae” 可以排列成以下 $6 \times 6$ 的网格：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1166B/7d474325157104f047038dc9401e0f23cf51cf99.png)
很容易验证每行和每列都包含所有的元音字母。

## 样例 #1
### 输入
```
7
```
### 输出
```
-1
```

## 样例 #2
### 输入
```
36
```
### 输出
```
agoeuioaeiruuimaeoieauoweouoiaouimae
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是先判断能否构造出满足条件的矩阵，再根据规律构造出符合要求的字符串。判断部分，都意识到当 $k < 25$ 或 $k$ 无法分解为两个大于等于 $5$ 的因数时，不存在满足条件的单词，应输出 $-1$。构造部分，发现可以通过循环或错位排列元音字母来满足每行每列都包含所有元音的条件。不同题解在具体实现和细节处理上有所差异，如判断因数的方式、构造字符串的具体逻辑等。

### 所选的题解
#### 作者：世末OIer (赞：3)  5星
- **关键亮点**：思路清晰简洁，通过直接找规律，利用 `s[(i + j) % 5]` 这种简洁的方式来填充矩阵，代码实现高效且可读性强。
```cpp
#include<bits/stdc++.h>
#pragma GCC diagnostic error "-std=c++11"
#define ll long long
#define mp make_pair
using namespace std;
string s="aeiou";
inline void fill(int x,int y){
    int i,j;
    for(i=0;i<x;++i) for(j=0;j<y;++j)
        cout<<s[(i+j)%5];
}
int main(){
    int i,j;
    int k;
    cin>>k;
    if(k<25){
        cout<<-1<<endl;
        return 0;
    }
    for(int i=5;i*i<=k;++i){
        if(k%i==0 and k/i>=5){
            fill(i,k/i);
            return 0;
        }
    }
    cout<<-1<<endl;
    return 0;
}
```
核心实现思想：`fill` 函数通过双重循环，按照 `s[(i + j) % 5]` 的规律填充字符，主函数先判断 $k$ 是否小于 $25$，再寻找满足条件的因数 $i$ 和 $k/i$，若找到则调用 `fill` 函数输出结果，否则输出 $-1$。

#### 作者：T21C06 (赞：0)  4星
- **关键亮点**：通过将大矩阵与 $5 \times 5$ 矩阵建立联系，发现每一列按 $5 \times 5$ 矩阵的 $5$ 列循环，每一行按 $5 \times 5$ 矩阵的 $5$ 行循环的规律，思路独特，代码逻辑清晰。
```cpp
#include<bits/stdc++.h>
#include<string>
using namespace std;
int n;
string st[10];
void Out(int x,int y){ 
    int tx=0,ty=-1;
    for(int i=1;i<=x;i++){
        tx++;
        if(tx==6) tx=1;
        ty=-1; 
        for(int j=1;j<=y;j++){
            ty++;
            if(ty==5) ty=0;
            cout<<st[tx][ty];
        }
    }
}
int main(){
    cin>>n;
    st[1]="aeiou";
    st[2]="eioua";
    st[3]="iouae";
    st[4]="ouaei";
    st[5]="uaeio";
    for(int i=5;i<=n;i++){
        if(n%i==0&&n/i>=5){
            Out(i,n/i);
            return 0;
        }
    }
    cout<<"-1";
    return 0;
} 
```
核心实现思想：先初始化 $5 \times 5$ 矩阵对应的字符串数组 `st`，`Out` 函数通过控制 `tx` 和 `ty` 的循环来按规律输出字符，主函数寻找满足条件的因数并调用 `Out` 函数输出结果，否则输出 $-1$。

#### 作者：AC_Dolphin (赞：0)  4星
- **关键亮点**：详细分析了构造过程，先指出一般情况下的构造方法，再针对 $n$ 是 $5$ 的倍数时不能简单错开填入的情况进行特判，考虑全面。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int k;
    cin>>k;
    for(int i=1;i<=sqrt(k);i++){
        if(k%i!=0) continue;
        int j=k/i;
        if(i<5||j<5) continue;
        if(j%5){
            for(int s=1;s<=k/5;s++) cout<<"aeiou";
            switch(k%5){
                case 1:cout<<"a";break;
                case 2:cout<<"ae";break;
                case 3:cout<<"aei";break;
                case 4:cout<<"aeio";break;
            }
            return 0;
        }
        else{
            int m=j/5;
            for(int s=1;s<=i/5;s++){
                for(int l=1;l<=m;l++) cout<<"aeiou";
                for(int l=1;l<=m;l++) cout<<"eioua";
                for(int l=1;l<=m;l++) cout<<"iouae";
                for(int l=1;l<=m;l++) cout<<"ouaei";
                for(int l=1;l<=m;l++) cout<<"uaeio";
            }
            switch(j%5){
                case 1:for(int l=1;l<=m;l++) cout<<"aeiou";break;
                case 2:{
                for(int l=1;l<=m;l++) cout<<"aeiou";
                for(int l=1;l<=m;l++) cout<<"eioua";
                    break;
                }
                case 3:{
                    for(int l=1;l<=m;l++) cout<<"aeiou";
                    for(int l=1;l<=m;l++) cout<<"eioua";
                    for(int l=1;l<=m;l++) cout<<"iouae";
                    break;
                }
                case 4:{
                    for(int l=1;l<=m;l++) cout<<"aeiou";
                    for(int l=1;l<=m;l++) cout<<"eioua";
                    for(int l=1;l<=m;l++) cout<<"iouae";
                    for(int l=1;l<=m;l++) cout<<"ouaei";
                    break;
                }
            }
            return 0;
        }
    }
    cout<<-1<<endl;
    return 0;
}
```
核心实现思想：通过两层循环寻找满足条件的因数 $i$ 和 $j$，根据 $j$ 是否为 $5$ 的倍数进行不同方式的字符串构造输出，若未找到满足条件的因数则输出 $-1$。

### 最优关键思路或技巧
通过对 $5 \times 5$ 矩阵规律的挖掘，利用循环或错位排列元音字母来构造满足条件的矩阵，同时注意对 $k$ 取值范围和特殊情况（如 $k$ 是 $5$ 的倍数）的判断与处理。

### 拓展
此类题目属于构造类型题目，常见套路是先找出最小可行的基本结构（如本题的 $5 \times 5$ 矩阵），分析其规律，再将大问题转化为基于基本结构的扩展。同类型题目通常会要求根据特定规则构造出满足条件的数据结构或序列。

### 相似知识点洛谷题目
- [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)
- [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)
- [P1464 Function](https://www.luogu.com.cn/problem/P1464)

### 个人心得摘录与总结
部分作者提到在处理 $k$ 是 $5$ 的倍数时容易出错，如按一般错位填充会导致列不满足条件，需要特殊处理。这提示在解决构造类问题时，要全面考虑各种边界和特殊情况，对规律的应用不能一概而论，需细致分析不同条件下的差异。 

---
处理用时：113.20秒