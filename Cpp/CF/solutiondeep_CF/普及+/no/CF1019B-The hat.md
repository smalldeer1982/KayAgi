# 题目信息

# The hat

## 题目描述

This is an interactive problem.

Imur Ishakov decided to organize a club for people who love to play the famous game «The hat». The club was visited by $ n $ students, where $ n $ is even. Imur arranged them all in a circle and held a draw to break the students in pairs, but something went wrong. The participants are numbered so that participant $ i $ and participant $ i+1 $ ( $ 1<=i<=n-1 $ ) are adjacent, as well as participant $ n $ and participant $ 1 $ . Each student was given a piece of paper with a number in such a way, that for every two adjacent students, these numbers differ exactly by one. The plan was to form students with the same numbers in a pair, but it turned out that not all numbers appeared exactly twice.

As you know, the most convenient is to explain the words to the partner when he is sitting exactly across you. Students with numbers $ i $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1019B/59f224a8151ecadc368b840c31ed2d1a88e25415.png) sit across each other. Imur is wondering if there are two people sitting across each other with the same numbers given. Help him to find such pair of people if it exists.

You can ask questions of form «which number was received by student $ i $ ?», and the goal is to determine whether the desired pair exists in no more than $ 60 $ questions.

## 说明/提示

Input-output in statements illustrates example interaction.

In the first sample the selected sequence is $ 1,2,1,2,3,4,3,2 $

In the second sample the selection sequence is $ 1,2,3,2,1,0 $ .

## 样例 #1

### 输入

```
8

2

2
```

### 输出

```

? 4

? 8

! 4
```

## 样例 #2

### 输入

```
6

1

2

3 

2

1

0```

### 输出

```

? 1

? 2

? 3

? 4

? 5

? 6

! -1```

# AI分析结果

### 题目内容
# 帽子

## 题目描述
这是一道交互题。

伊穆尔·伊沙科夫决定为热爱玩著名游戏“帽子”的人们组织一个俱乐部。有\(n\)名学生来到了俱乐部，其中\(n\)为偶数。伊穆尔将他们所有人安排成一个圆圈，并进行抽签以将学生两两分组，但出了点问题。参与者被编号，使得参与者\(i\)和参与者\(i + 1\)（\(1 \leq i \leq n - 1\)）相邻，以及参与者\(n\)和参与者\(1\)相邻。每个学生都得到一张写有数字的纸，以这样一种方式，即每两个相邻的学生，这些数字恰好相差\(1\)。原本的计划是将数字相同的学生组成一对，但结果发现并非所有数字都恰好出现两次。

如你所知，当你的搭档正好坐在你对面时，向他解释单词是最方便的。编号为\(i\)和\(i+\frac{n}{2}\)的学生彼此相对而坐。伊穆尔想知道是否有两个相对而坐的人拿到了相同的数字。帮助他找到这样一对人（如果存在的话）。

你可以提出形如“学生\(i\)拿到了什么数字？”的问题，目标是在不超过\(60\)个问题内确定是否存在所需的一对人。

## 说明/提示
陈述中的输入 - 输出说明了示例交互。

在第一个样例中，选定的序列是\(1, 2, 1, 2, 3, 4, 3, 2\)。

在第二个样例中，选定的序列是\(1, 2, 3, 2, 1, 0\)。

## 样例 #1
### 输入
```
8
2
2
```
### 输出
```
? 4
? 8
! 4
```
## 样例 #2
### 输入
```
6
1
2
3 
2
1
0
```
### 输出
```
? 1
? 2
? 3
? 4
? 5
? 6
! -1
```

### 算法分类
二分

### 综合分析与结论
这些题解的核心思路都是先判断\(n\)的取值情况，确定有解的条件为\(n\)能被\(4\)整除，再通过分析相对位置数字差的性质，利用二分查找来找到满足条件的位置。各题解在表述和代码细节上有所不同，但整体思路一致。

### 所选的题解
 - **作者：Piwry (5星)**
    - **关键亮点**：思路清晰，详细地分析了\(d(i)\)（第\(i\)位和他对面位置的数字的差）的性质，包括\(n\)不能被\(4\)整除时无解的证明，以及\(d(i)\)在\(i\)变化时的取值范围和奇偶性不变等特性，并据此给出了严谨的二分查找实现。
    - **重点代码**：
```cpp
inline void Ask(const int &i){
    printf("? %d\n", i);
    fflush(stdout);
    a[i] = read();
}
inline int get_b(const int &x){
    if(!vis[x])
        Ask(x), vis[x] = 1;
    if(!vis[(x - 1 + n / 2) % n + 1])
        Ask((x - 1 + n / 2) % n + 1), vis[(x - 1 + n / 2) % n + 1] = 1;
    return a[(x - 1 + n / 2) % n + 1] - a[x];
}
int main(){
    n = read();
    if(n % 4!= 0)
        puts("! -1");
    else{
        if(get_b(1) == 0)
            printf("! %d\n", 1);
        else{
            int l = 1, r = n / 2 + 1;
            while(l < r){
                int mid = (l + r) >> 1;
                if(get_b(mid) == 0){
                    printf("! %d\n", mid);
                    break;
                }
                else if(get_b(l) * get_b(mid) < 0)
                    r = mid;
                else
                    l = mid;
            }
        }
    }
}
```
    - **核心实现思想**：`Ask`函数用于向交互程序询问学生\(i\)的数字。`get_b`函数获取第\(i\)位和他对面位置数字的差。主函数中先判断\(n\)能否被\(4\)整除，若不能则无解；若能，先计算\(d(1)\)，若为\(0\)则直接得到解，否则通过二分查找找到使\(d(i)=0\)的\(i\)。
 - **作者：Mihari (4星)**
    - **关键亮点**：对题目进行了详细解读，清晰阐述了\(n = 4k + 2\)时无解的原因，以及\(t_i\)（\(a_i - a_{i'}\)）之间的差值关系，为二分查找提供了理论基础。
    - **重点代码**：代码链接：https://www.cnblogs.com/Arextre/p/12260753.html
    - **核心实现思想**：未提供具体代码，但思路上先判断\(n\)的形式确定无解情况，再通过分析\(t_i\)的性质，利用二分查找满足\(t_i = 0\)的位置。
 - **作者：Priestess_SLG (4星)**
    - **关键亮点**：对\(n\)的情况分类讨论详细，证明了\(n\equiv 2(\bmod\ 4)\)时无解，以及\(n = 4k\)时必然存在解（虽未严格证明），并深入分析了\(F(i)\)（\(|a_i - a_{i + \frac{n}{2}}|\)）的性质，为二分查找提供依据。
    - **重点代码**：
```cpp
inline int ask(int x){cout << "? " << x << endl; int o; cin >> o; return o;}
inline void qd(int x){cout << "! " << x << endl;}
int a[N]; inline int Task(int x){if(~a[x]) return a[x]; return a[x] = ask(x);}
inline int Fask(int x){int pw = x + n / 2; if(pw > n) pw -= n; return Task(x) - Task(pw);}
signed main(){
    memset(a, -1, sizeof a); cin >> n;
    if(n % 4 == 2){qd(-1); return 0;}
    int os = Fask(1); if(os == 0){qd(1); return 0;}
    int l = 1, r = n / 2 + 1;
    while(l <= r){
        int mid = l + r >> 1, mv = Fask(mid);
        if(!mv){qd(mid); return 0;}
        int ml = Fask(l); if(ml * mv < 0) r = mid - 1; else l = mid + 1;
    }
}
```
    - **核心实现思想**：`ask`函数询问学生数字，`Task`函数用于缓存已询问的数字，`Fask`函数计算\(F(i)\)。主函数中先判断\(n\)的情况，若\(n\)不能被\(4\)整除且余\(2\)则无解，否则计算\(F(1)\)，若为\(0\)则找到解，否则通过二分查找满足\(F(i)=0\)的\(i\)。

### 最优关键思路或技巧
1. **数学分析确定有解条件**：通过对\(n\)的取值分析，利用数字奇偶性判断出\(n\)不能被\(4\)整除时无解，缩小问题求解范围。
2. **定义函数分析性质**：定义表示相对位置数字差的函数（如\(d(i)\)、\(t_i\)、\(F(i)\)），分析其性质，如相邻函数值的差值范围、奇偶性以及对称性等，为二分查找提供理论依据。
3. **二分查找**：基于上述性质，在可能有解的区间内进行二分查找，高效地找到满足条件的位置。

### 同类型题或类似算法套路拓展
同类型题通常会给出一些具有特定规律的序列或排列，要求在满足一定限制条件下查找特定元素或判断是否存在满足条件的元素组合。类似算法套路包括先通过数学分析确定问题的可行域，再定义合适的函数并分析其性质，最后利用二分查找等高效算法解决问题。

### 洛谷相似题目推荐
1. **P2249 [HNOI2005]狡猾的商人**：通过分析账本数据之间的逻辑关系，利用差分约束系统判断是否存在矛盾，与本题先分析条件确定可行性类似。
2. **P1873 砍树**：给定树木高度和需要的木材长度，通过二分查找合适的砍伐高度，与本题利用二分查找满足条件的值思路相似。
3. **P3382 【模板】三分法**：在一个单峰函数上通过三分查找函数的最值，与本题在特定区间内通过二分查找满足条件的解的方式类似，都是利用函数性质进行查找。 

---
处理用时：115.75秒