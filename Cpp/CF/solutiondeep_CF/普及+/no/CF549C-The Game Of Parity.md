# 题目信息

# The Game Of Parity

## 题目描述

There are $ n $ cities in Westeros. The $ i $ -th city is inhabited by $ a_{i} $ people. Daenerys and Stannis play the following game: in one single move, a player chooses a certain town and burns it to the ground. Thus all its residents, sadly, die. Stannis starts the game. The game ends when Westeros has exactly $ k $ cities left.

The prophecy says that if the total number of surviving residents is even, then Daenerys wins: Stannis gets beheaded, and Daenerys rises on the Iron Throne. If the total number of surviving residents is odd, Stannis wins and everything goes in the completely opposite way.

Lord Petyr Baelish wants to know which candidates to the throne he should support, and therefore he wonders, which one of them has a winning strategy. Answer to this question of Lord Baelish and maybe you will become the next Lord of Harrenholl.

## 说明/提示

In the first sample Stannis will use his move to burn a city with two people and Daenerys will be forced to burn a city with one resident. The only survivor city will have one resident left, that is, the total sum is odd, and thus Stannis wins.

In the second sample, if Stannis burns a city with two people, Daenerys burns the city with one resident, or vice versa. In any case, the last remaining city will be inhabited by two people, that is, the total sum is even, and hence Daenerys wins.

## 样例 #1

### 输入

```
3 1
1 2 1
```

### 输出

```
Stannis
```

## 样例 #2

### 输入

```
3 1
2 2 1
```

### 输出

```
Daenerys
```

## 样例 #3

### 输入

```
6 3
5 20 12 7 14 101
```

### 输出

```
Stannis
```

# AI分析结果

### 题目内容
# 奇偶游戏

## 题目描述
维斯特洛大陆有$n$个城市。第$i$个城市居住着$a_{i}$个人。丹妮莉丝和史坦尼斯进行如下游戏：在一次操作中，一名玩家选择某一个城镇并将其付之一炬。很遗憾，该城镇所有居民都会丧生。史坦尼斯先开始游戏。当维斯特洛大陆恰好剩下$k$个城市时，游戏结束。

预言称，如果幸存居民的总数为偶数，那么丹妮莉丝获胜：史坦尼斯将被斩首，丹妮莉丝登上铁王座。如果幸存居民的总数为奇数，史坦尼斯获胜，一切将走向完全相反的方向。

培提尔·贝里席大人想知道他应该支持哪位王位候选人，因此他想知道，他们之中谁有获胜策略。回答贝里席大人的这个问题，也许你将成为下一位赫伦堡领主。

## 说明/提示
在第一个样例中，史坦尼斯将利用他的回合烧毁一个有两个人的城市，丹妮莉丝将被迫烧毁一个有一名居民的城市。唯一幸存的城市将剩下一名居民，也就是说，总数是奇数，因此史坦尼斯获胜。

在第二个样例中，如果史坦尼斯烧毁一个有两个人的城市，丹妮莉丝就烧毁有一名居民的城市，反之亦然。无论如何，最后剩下的城市将居住着两个人，也就是说，总数是偶数，因此丹妮莉丝获胜。

## 样例 #1
### 输入
```
3 1
1 2 1
```
### 输出
```
Stannis
```

## 样例 #2
### 输入
```
3 1
2 2 1
```
### 输出
```
Daenerys
```

## 样例 #3
### 输入
```
6 3
5 20 12 7 14 101
```
### 输出
```
Stannis
```

### 算法分类
数学

### 综合分析与结论
两道题解思路相近，均通过分析游戏规则和剩余城市人口奇偶性来确定获胜策略。关键在于明确操作次数、剩余城市数量与人口总数奇偶性之间的关系，利用奇偶运算特性判断胜负。两题解都先统计奇数和偶数人口城市数量，再根据操作次数的奇偶性分类讨论。

### 所选的题解
 - **作者：CASSINI_Thx（4星）**
    - **关键亮点**：思路清晰，通过详细的分类讨论，对最后一次操作是先手和后手的情况分别分析，易于理解。代码结构清晰，将不同情况的判断封装成函数，提高了代码可读性。
    - **个人心得**：作者自谦表示是即将退役蒟蒻的第一篇题解，做题过程体现出对奇偶运算等基础知识的运用。
 - **作者：233zhang（4星）**
    - **关键亮点**：简洁明了地指出奇数人口城市是影响最终结果的关键因素，从操作数和奇偶数城市数量关系入手，快速得出获胜条件，代码简洁高效。

### 重点代码及核心实现思想
#### CASSINI_Thx题解核心代码
```cpp
void xianshou()	//最后一次操作为先手的情况 
{
    if((m>>1)>=odd)
    {
        printf("Daenerys\n");
        return ;	//因为只有一组数据所以也可以直接exit(0),下同 
    } 
    if((m>>1)>=even &&!(k&1)) 
    {
        printf("Daenerys\n");
        return ;
    }
    printf("Stannis\n");
}
void houshou()	//最后一次操作为后手的情况 
{
    if((m>>1)>=odd) 
    {
        printf("Daenerys\n");
        return ;
    }
    if((m>>1)>=even && (k&1)) 
    {
        printf("Stannis\n");
        return ; 
    } 
    printf("Daenerys\n");
}
// 读入及预处理
int pre()	//读入及其它预处理 
{
    n=qr(),k=qr();
    m=n-k;	//操作数的计算 
    for(re i=1;i<=n;i++)
    {
        int a=qr();
        if(a&1) odd++;
        else even++; 
    }	//统计人口总数为奇数的城市数和人口总数为偶数的城市数
} 
```
**核心实现思想**：`pre`函数统计奇数和偶数人口城市数量及操作次数。`xianshou`和`houshou`函数分别针对最后一次操作是先手和后手的情况，根据操作数与奇数、偶数人口城市数量以及剩余城市数$k$的奇偶性判断谁能获胜。

#### 233zhang题解核心代码
```cpp
int main() {

    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin>>n>>k;
    m=n-k;
    for (int i=1;i<=n;i++) {
        cin>>x;
        if (x&1) odd++;
        else even++;
    }
    if (m==0) {
        if (odd&1) cout<<"Stannis\n";
        else cout<<"Daenerys\n";
        return 0;
    }
    if ((m>>1)>=odd) {
        cout<<"Daenerys\n";return 0;
    }
    if (m&1) {
        if ((m>>1)>=even&&(!(k&1))) {cout<<"Daenerys\n";return 0;}
        cout<<"Stannis\n";
    }
    else {
        if ((m>>1)>=even&&(k&1)) {cout<<"Stannis\n";return 0;}
        cout<<"Daenerys\n";
    }


    return 0;
}
```
**核心实现思想**：先读入数据并统计奇数和偶数人口城市数量以及操作次数。然后根据操作次数是否为0、操作数与奇数人口城市数量关系，以及操作次数和剩余城市数$k$的奇偶性判断谁能获胜。

### 最优关键思路或技巧
- **奇偶性分析**：抓住奇数人口城市对最终人口总数奇偶性的关键影响，通过统计奇数和偶数人口城市数量，结合操作次数和剩余城市数的奇偶性来判断获胜策略。
- **分类讨论**：对最后一次操作是先手还是后手的情况分别进行详细讨论，全面分析各种可能情况，得出通用的获胜条件。

### 拓展及类似算法套路
此类题目属于博弈论结合数学运算的类型，通常需要分析游戏规则，找到影响结果的关键因素（如本题的人口奇偶性），通过分类讨论不同情况得出获胜策略。类似套路可应用于其他博弈类数学问题，例如一些取石子游戏，根据取石子的规则和剩余石子数量等条件，利用奇偶性或其他数学特性判断胜负。

### 洛谷相似题目推荐
 - **P1247 取火柴游戏**：经典的博弈论问题，通过分析取火柴的规则和剩余火柴数量，利用数学方法确定获胜策略。
 - **P2197 【模板】nim游戏**：同样是博弈论中的nim游戏，考察对游戏规则的理解和数学分析能力。
 - **P1907 统计单词数**：虽然表面是字符串题目，但在判断单词出现次数等方面可运用到一些类似的逻辑分析和条件判断，与本题分析问题的思路有相通之处。 

---
处理用时：63.83秒