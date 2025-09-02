# 题目信息

# Fancy Number

## 题目描述

A car number in Berland consists of exactly $ n $ digits. A number is called beautiful if it has at least $ k $ equal digits. Vasya wants to change the digits in his car's number so that the number became beautiful. To replace one of $ n $ digits Vasya has to pay the sum of money, equal to the absolute difference between the old digit and the new one.

Help Vasya: find the minimum sum of money he should pay to make the number of his car beautiful. You should also find the resulting beautiful number. If there are several such numbers, then print the lexicographically minimum one.

## 说明/提示

In the first sample replacing the second digit with an "8" costs $ |9-8|=1 $ . Replacing the fifth digit with an "8" costs the same. Replacing the sixth digit costs $ |6-8|=2 $ . As a result, Vasya will pay $ 1+1+2=4 $ for a beautiful number "888188".

The lexicographical comparison of strings is performed by the < operator in modern programming languages. The string $ x $ is lexicographically smaller than the string $ y $ , if there exists such $ i $ ( $ 1<=i<=n $ ), that $ x_{i}&lt;y_{i} $ , and for any $ j $ ( $ 1<=j&lt;i $ ) $ x_{j}=y_{j} $ . The strings compared in this problem will always have the length $ n $ .

## 样例 #1

### 输入

```
6 5
898196
```

### 输出

```
4
888188
```

## 样例 #2

### 输入

```
3 2
533
```

### 输出

```
0
533
```

## 样例 #3

### 输入

```
10 6
0001112223
```

### 输出

```
3
0000002223
```

# AI分析结果

### 题目内容
# 奇妙数字

## 题目描述
在伯兰，一个车牌号由恰好 $n$ 个数字组成。如果一个车牌号至少有 $k$ 个相同的数字，那么这个车牌号就被称为漂亮的。瓦夏想改变他车牌号中的数字，使这个车牌号变得漂亮。要替换 $n$ 个数字中的一个，瓦夏必须支付一笔钱，这笔钱等于旧数字和新数字之间的绝对差值。

请帮助瓦夏：找到他为使车牌号漂亮而应该支付的最小金额。你还应该找到最终得到的漂亮车牌号。如果有几个这样的车牌号，那么打印字典序最小的那个。

## 说明/提示
在第一个样例中，将第二个数字替换为“8”的花费为 $|9 - 8| = 1$ 。将第五个数字替换为“8”的花费也是一样。将第六个数字替换的花费为 $|6 - 8| = 2$ 。结果，瓦夏将为漂亮的车牌号“888188”支付 $1 + 1 + 2 = 4$ 。

字符串的字典序比较是通过现代编程语言中的 < 运算符来执行的。如果存在这样的 $i$ （$1 \leq i \leq n$），使得 $x_{i} < y_{i}$ ，并且对于任何 $j$ （$1 \leq j < i$）都有 $x_{j} = y_{j}$ ，那么字符串 $x$ 在字典序上小于字符串 $y$ 。在这个问题中比较的字符串长度总是 $n$ 。

## 样例 #1
### 输入
```
6 5
898196
```
### 输出
```
4
888188
```

## 样例 #2
### 输入
```
3 2
533
```
### 输出
```
0
533
```

## 样例 #3
### 输入
```
10 6
0001112223
```
### 输出
```
3
0000002223
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是通过枚举最终要使车牌号码中出现 $k$ 个相同的数字，然后采用贪心策略来确定如何修改其他数字以达到最小代价和字典序最小。不同题解在具体实现贪心的方式以及处理字典序最小的细节上有所不同。有的通过特定顺序遍历修改数字，有的通过复杂的排序规则来实现。解决难点主要在于如何巧妙地结合贪心策略来保证字典序最小，同时还要考虑各种边界情况和细节处理。

### 所选的题解
 - **作者：dzk_QwQ (5星)**
    - **关键亮点**：思路清晰，通过分情况讨论修改数字的方向（往小或往大修改），并按特定顺序修改（往小从前往后，往大从后往前）来保证字典序最小，代码实现简洁明了。
    - **重点代码核心实现思想**：枚举要改成相同为 $k$ 个的那个数字 $i$，对原车牌每个数字与 $i$ 的差值进行分析，分往小和往大修改两种情况，按特定顺序遍历原车牌数字进行修改，记录最小代价和字典序最小的结果。
    ```cpp
    for(int i = 0 ; i <= 9 ; i ++){//枚举我们所要求的那k个相同的数 
        int cnt = num[i], MIN = 0 ; 
        memcpy  (str, s, sizeof( s ));
        for(int j = 1 ; j <= 9 && cnt < k ; j ++){
            if(i + j < 10){
                int sum = i + j , id = i;
                for(int temp = 0 ; temp < n && cnt < k ; temp++){ 
                    if(str[temp] - '0' == sum){
                        str[temp] = id + '0';
                        cnt ++;
                        MIN += j;
                    }
                }
            }
            if(i - j >= 0){
                int sum = i - j, id = i;
                for(int temp = n - 1 ; temp >= 0 && cnt < k ; temp--){
                    if(str[temp] - '0' == sum){
                        str[temp] = id + '0';
                        cnt ++;
                        MIN += j;
                    }
                } 
            }
        }
        if(MIN < ans){
            ans = MIN;
            strcpy(Sans, str);
        }
        else if( MIN == ans &&strcmp( Sans, str )>0 )
            strcpy( Sans, str ); 
    }
    ```
 - **作者：wheneveright (4星)**
    - **关键亮点**：利用排序来解决问题，通过自定义复杂的排序规则，综合考虑数字与枚举数字的绝对差值、数字大小以及位置等因素，从而同时满足最小代价和字典序最小的要求。
    - **重点代码核心实现思想**：先快读输入，然后枚举目标数字 $xp$，对每个数字与 $xp$ 的绝对差值等信息进行排序，计算最小代价 $res$ 并记录相关信息。之后对满足最小代价的方案进行处理，通过排序和比较刷出字典序最小的结果。
    ```cpp
    struct QDS {
        int num, id;
        bool operator < (register const QDS & P) const {
            return abs (num - xp) < abs (P.num - xp) ||
                (abs (num - xp) == abs (P.num - xp) && num > P.num) ||
                (num == P.num && (num > xp? id < P.id : id > P.id));
        }
    } A[10005], B[10005];
    // 排序核心代码
    for (xp = 0; xp <= 9; xp++) {
        sort (A + 1, A + 1 + N); register int now = 0;
        for (register int i = 1; i <= K; i++) now += abs (A[i].num - xp);
        if (now < res) res = now, mid = xp;
        rs[xp] = now;
    }
    for (xp = 0; xp <= 9; xp++) {
        if (rs[xp]!= res) continue;
        sort (A + 1, A + 1 + N);
        for (register int i = 1; i <= N; i++) B[i] = A[i];
        for (register int i = 1; i <= K; i++) A[i].num = xp;
        sort (A + 1, A + 1 + N, cmp);
        bool check = false;
        for (register int i = 1; i <= N; i++) {
            if (A[i].num < R[i]) {check = true;  break;}
            if (A[i].num > R[i]) {check = false; break;}
            continue;
        }	if (check == true)
            for (register int i = 1; i <= N; i++) R[i] = A[i].num;
        for (register int i = 1; i <= N; i++) A[i] = B[i];
    }
    ```
 - **作者：jdsb (4星)**
    - **关键亮点**：采用贪心加模拟的方式，思路直接易懂。同样分改大改小两种情况，按特定顺序修改数字，在代码实现中对细节处理较好，通过注释清晰说明关键步骤。
    - **重点代码核心实现思想**：输入后记录每个数字出现次数，枚举要改成的数字 $i$，对每个数字与 $i$ 的差值进行分析，分改小（从头扫）和改大（从尾扫）两种情况遍历原数字序列进行修改，记录最小代价和字典序最小的结果。
    ```cpp
    for(int i=0;i<=9;i++)
    {
        int tot=num[i],sum=0;
        memcpy(str,s,sizeof(s));
        for(int j=1;j<=9&&tot<k;j++)
        {
            int x=i+j,y=i-j;
            if(x<10) 
            {
                for(int l=0;l<len&&tot<k;l++)
                    if(str[l]-'0'==x)
                    {
                        str[l]=i+'0';
                        tot++;
                        sum+=j;
                    }
            }
            if(y>=0)
            {
                for(int l=len-1;l>=0&&tot<k;l--)
                {
                    if(str[l]-'0'==y)
                    {
                        str[l]=i+'0';
                        tot++;
                        sum+=j;
                    }
                }
            }
        }
        if(sum<ans)
        {
            ans=sum;
            strcpy(anss,str);
        }
        else
        {
            if(sum==ans&&strcmp(anss,str)>0)
                strcpy(anss,str);
        }
    }
    ```

### 最优关键思路或技巧
在这类问题中，贪心策略结合特定的遍历顺序（如改小从前往后、改大从后往前）是保证字典序最小的有效方法。同时，通过合理的排序规则（综合考虑数字与目标数字的差值、数字本身大小、位置等因素）也能巧妙地解决问题。在实现过程中，要注意边界情况的处理以及对每个数字修改情况的准确记录。

### 可拓展之处
同类型题通常围绕在给定条件下通过最小代价对序列进行变换，以满足特定的数量或排列要求。类似算法套路是先确定一个枚举方向（如本题枚举最终要出现多次的数字），然后利用贪心思想结合特定顺序或排序规则来解决最小代价和其他附加条件（如字典序最小）的问题。

### 洛谷相似题目推荐
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
 - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)

### 个人心得摘录与总结
 - **作者：Astatinear**：提到本题细节多，调试花费1小时。总结出在处理字典序相关问题时，排序规则的设定要特别注意，需结合题目条件准确设定。
 - **作者：洛璟**：指出暴力枚举虽思路简单，但细节易出错，如字符串赋值应使用push_back防止玄学错误。强调在处理多方案且需考虑字典序时，要谨慎处理方案的存储和比较。 

---
处理用时：92.68秒