# 题目信息

# MKnez's ConstructiveForces Task

## 题目描述

MKnez wants to construct an array $ s_1,s_2, \ldots , s_n $ satisfying the following conditions:

- Each element is an integer number different from $ 0 $ ;
- For each pair of adjacent elements their sum is equal to the sum of the whole array.

More formally, $ s_i \neq 0 $ must hold for each $ 1 \leq i \leq n $ . Moreover, it must hold that $ s_1 + s_2 + \cdots + s_n = s_i + s_{i+1} $ for each $ 1 \leq i < n $ .

Help MKnez to construct an array with these properties or determine that it does not exist.

## 说明/提示

In the first test case, $ [9,5] $ is a valid answer since $ 9+5 $ (the sum of the two adjacent elements $ s_1+s_2 $ ) is equal to $ 9+5 $ (the sum of all elements). Other solutions include $ [6,-9], [-1,-2], [-5000,5000], \ldots $

For the second test case, let us show why some arrays do not satisfy the constraints:

- $ [1,1,1] $ — $ s_1+s_2 = 1+1 = 2 $ and $ s_1+s_2+s_3=1+1+1 = 3 $ differ;
- $ [1,-1,1] $ — $ s_1+s_2=1+(-1)=0 $ and $ s_1+s_2+s_3=1+(-1)+1 = 1 $ differ;
- $ [0,0,0] $ — The array $ s $ cannot contain a $ 0 $ .

This is not a proof, but it can be shown that the answer is "NO".

## 样例 #1

### 输入

```
2
2
3```

### 输出

```
YES
9 5
NO```

# AI分析结果

### 题目内容
# MKnez的构造性问题

## 题目描述
MKnez想要构造一个数组 $ s_1,s_2, \ldots, s_n $ ，满足以下条件：
- 每个元素都是非零整数；
- 对于每对相邻元素，它们的和等于整个数组的和。

更正式地说，对于每个 $ 1 \leq i \leq n $ ，必须满足 $ s_i \neq 0 $ 。此外，对于每个 $ 1 \leq i < n $ ，必须满足 $ s_1 + s_2 + \cdots + s_n = s_i + s_{i + 1} $ 。

帮助MKnez构造一个具有这些属性的数组，或者确定它不存在。

## 说明/提示
在第一个测试用例中，$ [9,5] $ 是一个有效的答案，因为 $ 9 + 5 $ （两个相邻元素 $ s_1 + s_2 $ 的和）等于 $ 9 + 5 $ （所有元素的和）。其他解决方案包括 $ [6,-9], [-1,-2], [-5000,5000], \ldots $ 。

对于第二个测试用例，让我们说明为什么一些数组不满足约束条件：
- $ [1,1,1] $  —— $ s_1 + s_2 = 1 + 1 = 2 $ ，而 $ s_1 + s_2 + s_3 = 1 + 1 + 1 = 3 $ ，两者不同；
- $ [1,-1,1] $  —— $ s_1 + s_2 = 1 + (-1) = 0 $ ，而 $ s_1 + s_2 + s_3 = 1 + (-1) + 1 = 1 $ ，两者不同；
- $ [0,0,0] $  —— 数组 $ s $ 不能包含 $ 0 $ 。

这不是一个证明，但可以证明答案是 “NO” 。

## 样例 #1
### 输入
```
2
2
3
```
### 输出
```
YES
9 5
NO
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是先通过对条件 $ s_1 + s_2 + \cdots + s_n = s_i + s_{i + 1} (1 \leq i < n) $ 的推导，得出数组元素的规律，即 $ s_1 = s_3 = s_5 = \cdots $ ，$ s_2 = s_4 = s_6 = \cdots $ 。然后分 $ n $ 为偶数和奇数两种情况进行构造：
 - **偶数情况**：普遍采用 $ s_i = (i \mod 1) \times 2 - 1 $ 这样交错的 $ 1 $ 和 $ -1 $ 构造方式，满足相邻两数和与总和相等（都为 $ 0 $ ）。
 - **奇数情况**：通过设 $ s_1 = x $ ，$ s_2 = y $ ，根据条件列方程求解出 $ x $ 和 $ y $ 的关系，进而构造数组，但都注意到 $ n = 3 $ 时无解。

各题解的主要区别在于推导过程的详细程度、代码实现的简洁性和对无解情况的判断方式。

### 所选的题解
- **作者：SuperCowHorse (5星)**
  - **关键亮点**：思路清晰，先证明数组元素规律，再分别针对偶数、奇数情况详细推导并构造数组，代码简洁明了，逻辑连贯。
  - **重点代码**：
```cpp
inline void solve(){
    scanf("%d",&n);
    if(n==3){//3特判掉
        printf("NO\n");
        return;
    }
    printf("YES\n");
    if(n&1){//奇数
        for(int i=1;i<=n;++i){
            if(i&1){
                printf("%d%c",3-n," \n"[i==n]);
            }
            else{
                printf("%d%c",n-1," \n"[i==n]);
            }
        }
        return;
    }
    for(int i=1;i<=n;++i){//偶数
        if(i&1){
            printf("%d%c",1," \n"[i==n]);
        }
        else{
            printf("%d%c",-1," \n"[i==n]);
        }
    }
}
```
  - **核心实现思想**：先判断 $ n $ 是否为 $ 3 $ ，若为 $ 3 $ 则输出 “NO” 。否则，若 $ n $ 为奇数，按规律交替输出 $ 3 - n $ 和 $ n - 1 $ ；若 $ n $ 为偶数，交替输出 $ 1 $ 和 $ -1 $ 。
- **作者：Awsdkl (4星)**
  - **关键亮点**：证明过程清晰，通过等式推导得出数组元素规律，对奇数情况通过设值代入方程求解并构造数组，代码逻辑清晰。
  - **重点代码**：
```cpp
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        if(n & 1) //当n为奇数时
        {
            if(n <= 3)
            {
                printf("NO\n");
                continue;
            }
            printf("YES\n");
            for(int i = 1;i <= n;i++)
            {
                if(i & 1) printf("%d ",(3-n)/2);
                else printf("%d ",(n-1)/2);
            }
            puts("");
            continue;
        }
        //n为偶数
        printf("YES\n");
        for(int i = 1;i <= n;i++)
        {
            printf("%d ",(i & 1) * 2 - 1);
        }
        puts("");
    }
    return 0;
}
```
  - **核心实现思想**：读入数据后，对奇数情况先判断 $ n $ 是否小于等于 $ 3 $ ，若满足则输出 “NO” ，否则按推导结果交替输出 $ \frac{3 - n}{2} $ 和 $ \frac{n - 1}{2} $ ；偶数情况则按规律输出 $ (i \mod 1) \times 2 - 1 $ 。
- **作者：cjh20090318 (4星)**
  - **关键亮点**：对题意理解清晰，通过移项得到方程组，利用加减消元法得出元素规律，分情况构造数组，代码简洁，注释详细。
  - **重点代码**：
```cpp
void solve(){
    int n;scanf("%d",&n);
    if(n==3){puts("NO");return;}//特判 n=3 时。
    puts("YES");//不等于 3 必定有解。
    if(n&1){//按照分析，分类讨论。
        int a=n>>1,b=a-1;//处理 s_1,s_2 的系数。
        for(int i=1;i<n;i+=2) printf("%d %d ",b,-a);
        printf("%d\n",b);
    }
    else{
        for(int i=1;i<=n;i+=2) printf("1 -1 ");
        putchar('\n');
    }
}
```
  - **核心实现思想**：先特判 $ n = 3 $ 输出 “NO” 。对于奇数情况，计算出系数 $ b $ 和 $ -a $ 并交替输出，最后单独输出 $ b $ ；偶数情况则交替输出 $ 1 $ 和 $ -1 $ 。

### 最优关键思路或技巧
通过对给定等式条件的数学推导得出数组元素的分布规律，即奇偶位置元素分别相等。利用这个规律，分奇偶情况进行针对性构造，在奇数情况构造时注意到 $ n = 3 $ 时无解的特殊情况。

### 可拓展思路
此类构造题通常需要根据给定条件进行数学分析，挖掘隐藏规律，再依据规律进行构造。类似题目可能会改变数组元素的限制条件或等式关系，解题时依旧从分析条件入手，推导元素规律后构造。

### 相似知识点洛谷题目
 - [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过分析条件构造满足要求的方案。
 - [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：根据等式条件进行构造和枚举。
 - [P1423 小玉在游泳](https://www.luogu.com.cn/problem/P1423)：依据题目描述的规则构造计算过程。 

---
处理用时：61.56秒