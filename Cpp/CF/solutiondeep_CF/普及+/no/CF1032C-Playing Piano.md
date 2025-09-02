# 题目信息

# Playing Piano

## 题目描述

Little Paul wants to learn how to play piano. He already has a melody he wants to start with. For simplicity he represented this melody as a sequence $ a_1, a_2, \ldots, a_n $ of key numbers: the more a number is, the closer it is to the right end of the piano keyboard.

Paul is very clever and knows that the essential thing is to properly assign fingers to notes he's going to play. If he chooses an inconvenient fingering, he will then waste a lot of time trying to learn how to play the melody by these fingers and he will probably not succeed.

Let's denote the fingers of hand by numbers from $ 1 $ to $ 5 $ . We call a fingering any sequence $ b_1, \ldots, b_n $ of fingers numbers. A fingering is convenient if for all $ 1\leq i \leq n - 1 $ the following holds:

- if $ a_i < a_{i+1} $ then $ b_i < b_{i+1} $ , because otherwise Paul needs to take his hand off the keyboard to play the $ (i+1) $ -st note;
- if $ a_i > a_{i+1} $ then $ b_i > b_{i+1} $ , because of the same;
- if $ a_i = a_{i+1} $ then $ b_i\neq b_{i+1} $ , because using the same finger twice in a row is dumb. Please note that there is $ \neq $ , not $ = $ between $ b_i $ and $ b_{i+1} $ .

Please provide any convenient fingering or find out that there is none.

## 说明/提示

The third sample test is kinda "Non stop" song by Reflex.

## 样例 #1

### 输入

```
5
1 1 4 2 2
```

### 输出

```
1 4 5 4 5 ```

## 样例 #2

### 输入

```
7
1 5 7 8 10 3 1
```

### 输出

```
1 2 3 4 5 4 3 ```

## 样例 #3

### 输入

```
19
3 3 7 9 8 8 8 8 7 7 7 7 5 3 3 3 3 8 8
```

### 输出

```
1 3 4 5 4 5 4 5 4 5 4 5 4 3 5 4 3 5 4 ```

# AI分析结果

### 题目内容
# 弹钢琴

## 题目描述
小保罗想学弹钢琴。他已经有了一首想开始练习的旋律。为了简单起见，他将这首旋律表示为一个键编号序列 $a_1, a_2, \ldots, a_n$：数字越大，就越靠近钢琴键盘的右端。

保罗非常聪明，他知道关键在于为要弹奏的音符正确分配手指。如果他选择了不方便的指法，那么他将花费大量时间尝试用这些手指学习弹奏旋律，而且很可能不会成功。

我们用数字 $1$ 到 $5$ 表示手的手指。我们称任何手指编号序列 $b_1, \ldots, b_n$ 为一种指法。如果对于所有 $1\leq i \leq n - 1$ 都满足以下条件，则一种指法是方便的：
- 如果 $a_i < a_{i+1}$，那么 $b_i < b_{i+1}$，因为否则保罗需要将手从键盘上移开才能弹奏第 $(i + 1)$ 个音符；
- 如果 $a_i > a_{i+1}$，那么 $b_i > b_{i+1}$，原因同上；
- 如果 $a_i = a_{i+1}$，那么 $b_i\neq b_{i+1}$，因为连续两次使用同一根手指是不明智的。请注意，$b_i$ 和 $b_{i+1}$ 之间是 $\neq$，而不是 $=$。

请提供任何一种方便的指法，或者找出不存在这样的指法。

## 说明/提示
第三个样例测试有点像 Reflex 的《Non stop》这首歌。

## 样例 #1
### 输入
```
5
1 1 4 2 2
```
### 输出
```
1 4 5 4 5 
```

## 样例 #2
### 输入
```
7
1 5 7 8 10 3 1
```
### 输出
```
1 2 3 4 5 4 3 
```

## 样例 #3
### 输入
```
19
3 3 7 9 8 8 8 8 7 7 7 7 5 3 3 3 3 8 8
```
### 输出
```
1 3 4 5 4 5 4 5 4 5 4 5 4 3 5 4 3 5 4 
```

### 算法分类
构造

### 综合分析与结论
这些题解主要分为两类思路，一类是基于动态规划（DP）的方法，通过定义状态和状态转移方程来求解；另一类是构造法，根据序列 $a$ 中相邻元素的大小关系，按照一定规则直接构造出序列 $b$。
 - **动态规划类**：定义 $dp[i][j]$ 表示第 $i$ 位填 $j$ 的情况是否可行，根据 $a_i$ 与 $a_{i + 1}$ 的大小关系进行状态转移。其难点在于状态转移方程的准确编写以及最后根据转移结果倒推答案序列。这类方法的时间复杂度为 $O(5^2n)$。
 - **构造类**：根据 $a_{i - 1}$、$a_i$ 和 $a_{i + 1}$ 之间的大小关系，分多种情况讨论来确定 $ans_i$ 的值。例如当 $a_{i - 1}<a_i\wedge a_i>a_{i + 1}$ 时，$ans_i = 5$ 等。在相等情况时的构造相对复杂，需要细致考虑。这类方法时间复杂度为 $O(n)$，且不依赖于 $b_i$ 的取值范围，相对更优。

### 所选的题解
 - **作者：zbbfans（5星）**
    - **关键亮点**：思路清晰，对每种相邻元素大小关系的情况进行了详细分析，并通过贪心思想确定每个位置的指法。代码实现简洁明了，对边界情况和越界情况处理得当。
    - **重点代码**：
```cpp
if(a[1]>a[2]) ans[1]=5;
else if(a[1]<a[2]) ans[1]=1;
else ans[1]=3;
for(int i=2;i<n;i++){
    if(a[i]>a[i-1]){
        if(a[i]>a[i+1]){
            if(ans[i-1]==5){
                print(-1);
                return 0;
            }
            ans[i]=5;
        }
        else ans[i]=ans[i-1]+1;
    }else if(a[i]<a[i-1]){
        if(a[i]<a[i+1]){
            if(ans[i-1]==1){
                print(-1);
                return 0;
            }
            ans[i]=1;
        }else ans[i]=ans[i-1]-1;
    }else{
        if(a[i]<a[i+1]){
            if(ans[i-1]==1) ans[i]=2;
            else ans[i]=1;
        }else if(a[i]>a[i+1]){
            if(ans[i-1]==5) ans[i]=4;
            else ans[i]=5;
        }else{
            if(ans[i-1]<=2) ans[i]=ans[i-1]+1;
            else ans[i]=ans[i-1]-1;
        }
    }
    if(ans[i]<=0||ans[i]>5){
        print(-1);
        return 0;
    }
}
if(a[n]>a[n-1]){
    if(ans[n-1]==5){
        print(-1);
        return 0;
    }
    ans[n]=5;
}else if(a[n]<a[n-1]){
    if(ans[n-1]==1){
        print(-1);
        return 0;
    }
    ans[n]=1;
}else{
    if(ans[n-1]==1) ans[n]=2;
    else if(ans[n-1]==5) ans[n]=4;
    else ans[n]=5;
}
```
核心实现思想：先确定第一个指法，然后遍历序列，根据当前音符与前后音符的大小关系，分情况确定当前指法，并处理边界和越界情况，最后确定最后一个指法。
 - **作者：IceKylin（5星）**
    - **关键亮点**：提出严格 $O(n)$ 的构造做法，对每种大小关系的情况进行了全面且准确的分析，结论清晰。代码实现按照构造过程模拟，简洁高效。
    - **重点代码**：
```cpp
if(a[1]>a[2])ans[1]=5;
else if(a[1]<a[2])ans[1]=1;
else ans[1]=3;
for(int i=2;i<n;++i){
    if(a[i]>a[i-1]){
        if(a[i]>a[i+1])ans[i]=5;
        else ans[i]=ans[i-1]+1;
    }
    else if(a[i]<a[i-1]){
        if(a[i]<a[i+1])ans[i]=1;
        else ans[i]=ans[i-1]-1;
    }
    else{
        if(a[i]>a[i+1]){
            if(ans[i-1]==5)ans[i]=4;
            else ans[i]=5;
        }
        else if(a[i]<a[i+1]){
            if(ans[i-1]==1)ans[i]=2;
            else ans[i]=1;
        }
        else{
            if(ans[i-1]<=2)ans[i]=ans[i-1]+1;
            else ans[i]=ans[i-1]-1;
        }
    }
    if(ans[i]<1||ans[i]>5){
        cout<<-1;
        return 0;
    }
}
if(a[n]>a[n-1])ans[n]=5;
else if(a[n]<a[n-1])ans[n]=1;
else{
    if(ans[n-1]==5)ans[n]=1;
    else ans[n]=ans[n-1]+1;
}
```
核心实现思想：与 zbbfans 的思路类似，先确定首指法，遍历过程中依据音符大小关系分情况确定指法，处理越界，最后确定尾指法。
 - **作者：dbxxx（4星）**
    - **关键亮点**：将序列拆分为连续大于段、连续小于段和连续不等段进行贪心构造，考虑了段与段之间的边界情况，提出的构造方法时空复杂度与 $b$ 的值域无关，具有创新性。
    - **重点代码**：
```cpp
int lst = 1;
if (b[1] == '>')
    lst = 5;
else if (b[1] == '!')
    lst = 2;

std :: vector <int> ans = {lst};

for (int i = 2; i < n; ++i) {
    int now;
    char p = b[i - 1], q = b[i];
    if (p == '<') {
        if (lst == 5)
            break;
        now = lst + 1;
        if (q == '>')
            now = 5;
    } else if (p == '>') {
        if (lst == 1)
            break;
        now = lst - 1;
        if (q == '<')
            now = 1;
    } else if (p == '!') {
        if (q == '!') {
            now = 3;
            if (lst == 3)
                now = 2;
        } else if (q == '<') {
            now = 1;
            if (lst == 1)
                now = 2;
        } else if (q == '>') {
            now = 5;
            if (lst == 5)
                now = 4;
        }
    }

    ans.push_back(lst = now);
}

if (b[n - 1] == '<')
    ans.push_back(5);
else if (b[n - 1] == '>')
    ans.push_back(1);
else
    ans.push_back(lst == 5? 4 : 5);
```
核心实现思想：先根据第一个关系确定首指法，遍历过程中依据相邻段的关系确定当前指法，最后根据最后一段的关系确定尾指法。

### 最优关键思路或技巧
构造类方法中，根据相邻元素大小关系分情况直接构造序列 $b$ 的思路最优。这种方法避免了动态规划中对所有状态的遍历和转移，时间复杂度低且不依赖于 $b_i$ 的取值范围。具体技巧在于对各种大小关系情况的细致分析和合理的指法分配，如在转折点处（如 $a_{i - 1}<a_i\wedge a_i>a_{i + 1}$）将 $ans_i$ 设为 $5$ 等。

### 拓展
同类型题通常围绕序列元素间的大小关系或逻辑关系，要求构造满足特定规则的新序列。类似算法套路是根据给定规则，对序列进行分段分析或者对每个位置分情况讨论，利用贪心思想做出局部最优选择以构造全局解。

### 推荐题目
 - [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：通过枚举和构造来解决火柴棒拼等式的问题，与本题构造满足条件序列的思路类似。
 - [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)：需要根据一定规则从给定数中选取数字进行组合，与本题按规则构造序列有相似之处。
 - [P1464 Function](https://www.luogu.com.cn/problem/P1464)：根据函数定义和给定条件构造函数值序列，锻炼按规则构造的能力。 

---
处理用时：100.86秒