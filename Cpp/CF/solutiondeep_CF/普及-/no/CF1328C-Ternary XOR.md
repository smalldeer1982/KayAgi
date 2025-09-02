# 题目信息

# Ternary XOR

## 题目描述

A number is ternary if it contains only digits $ 0 $ , $ 1 $ and $ 2 $ . For example, the following numbers are ternary: $ 1022 $ , $ 11 $ , $ 21 $ , $ 2002 $ .

You are given a long ternary number $ x $ . The first (leftmost) digit of $ x $ is guaranteed to be $ 2 $ , the other digits of $ x $ can be $ 0 $ , $ 1 $ or $ 2 $ .

Let's define the ternary XOR operation $ \odot $ of two ternary numbers $ a $ and $ b $ (both of length $ n $ ) as a number $ c = a \odot b $ of length $ n $ , where $ c_i = (a_i + b_i) \% 3 $ (where $ \% $ is modulo operation). In other words, add the corresponding digits and take the remainders of the sums when divided by $ 3 $ . For example, $ 10222 \odot 11021 = 21210 $ .

Your task is to find such ternary numbers $ a $ and $ b $ both of length $ n $ and both without leading zeros that $ a \odot b = x $ and $ max(a, b) $ is the minimum possible.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
4
5
22222
5
21211
1
2
9
220222021```

### 输出

```
11111
11111
11000
10211
1
1
110111011
110111010```

# AI分析结果

### 题目内容
# 三进制异或

## 题目描述
一个数如果只包含数字0、1和2，那么它就是三进制数。例如，以下数字是三进制数：1022、11、21、2002。

给定一个较长的三进制数x。保证x的第一个（最左边）数字是2，x的其他数字可以是0、1或2。

我们定义两个三进制数a和b（长度均为n）的三进制异或运算⊙为一个长度为n的数c = a⊙b，其中ci = (ai + bi) % 3（其中%是取模运算）。换句话说，将对应数字相加，并取和除以3的余数。例如，10222⊙11021 = 21210。

你的任务是找到两个长度为n且都无前导零的三进制数a和b，使得a⊙b = x，并且max(a, b)尽可能小。

你必须回答t个独立的测试用例。

## 样例 #1
### 输入
```
4
5
22222
5
21211
1
2
9
220222021
```
### 输出
```
11111
11111
11000
10211
1
1
110111011
110111010
```

### 算法分类
贪心

### 综合分析与结论
这几道题解的核心思路都是基于贪心策略，根据给定三进制数x的每一位数字，通过合理构造a和b对应位的数字，使得max(a, b)最小。它们的不同之处主要在于对贪心策略的具体实现方式和代码的组织形式。
1. **思路方面**：都围绕x每一位数字为0、1、2时，如何确定a和b对应位数字展开。如x[i] = 0时，a[i] = b[i] = 0；x[i] = 2时，多数题解在前面未出现特殊情况时让a[i] = b[i] = 1 。对于x[i] = 1的情况，需要考虑之前是否已出现过使a和b产生大小差异的位，从而决定a[i]和b[i]的取值。
2. **算法要点**：关键在于根据x每一位数字，结合已确定的a和b前面部分的大小关系（是否相等），来确定a和b当前位的取值。同时要注意处理多组测试数据时的初始化操作。
3. **解决难点**：难点在于理解并实现如何在满足a⊙b = x的同时，保证max(a, b)最小。需要考虑不同数字情况以及前面数位对当前数位取值的影响。

### 所选的题解
#### 作者：Minecraft万岁 (赞：2)  星级：4星
- **关键亮点**：思路清晰，对每种情况的分析详细，结合“总和最小、尽量均摊”的思想来确定a和b的取值，代码结构较为清晰，逻辑连贯。
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
char x[50005];//读入的字符串 
char ansa[50005];//第一个答案字符串 
char ansb[50005];//第二个答案字符串 
bool flag1;//判断之前有没有在高位填过1 
int t,n; 
inline void read(int &x)//快读 
{
    int f;char c;
    for (f=1,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
    for (x=0;c<='9'&&c>='0';c=getchar()) x=x*10+(c&15);x*=f;
}
inline int mn(int _x,int _y)
{
    return _x<_y?_x:_y;
}
inline int mx(int _x,int _y)
{
    return _x>_y?_x:_y;
}
inline int ab(int _x)
{
    if(_x<0) return -_x;
    else return _x;
}
int main()
{
    read(t);
    while(t--)
    {
        flag1=true;//开始肯定没有在高位填过1 
        read(n);
        scanf("%s",1+x);//从下标1开始读入字符串 
        for(int i=1;i<=n;i++)//从高到低  
        {
            if(x[i]=='0') //几个大情况 
            {
                ansa[i]=ansb[i]='0';
            }
            if(x[i]=='1')
            {
                if(flag1)//没填过 
                {
                    ansa[i]='1';//在 ansa[i]中填上1 
                    ansb[i]='0';
                    flag1=false;//标记为填过了 
                }
                else//填过了就在另一个中填 
                {
                    ansa[i]='0';
                    ansb[i]='1';
                }
            }
            if(x[i]=='2')
            {
                if(!flag1)//按照思路分类 
                {
                    ansa[i]='0';
                    ansb[i]='2';
                } 
                else
                {
                    ansa[i]=ansb[i]='1';
                }
            }
        }
        for(int i=1;i<=n;i++) printf("%c",ansa[i]);//打印两个答案 
        puts("");
        for(int i=1;i<=n;i++) printf("%c",ansb[i]);
        puts("");    
    } 
    return 0;
}
```
核心实现思想：从高位到低位遍历读入的字符串x，根据x[i]的值和flag1（标记之前是否在高位填过1）来确定ansa[i]和ansb[i]的值，最后输出ansa和ansb。

#### 作者：laboba (赞：1)  星级：4星
- **关键亮点**：从最高位开始逐位枚举a和b，通过一个bool变量equal记录a和b前i - 1位是否相同，以此为依据进行贪心决策，逻辑清晰，代码简洁明了。
```cpp
#include<cstdio>
using namespace std;
const int N=50010;
int n;
int a[N],b[N],x[N];//x[i]即为t[i]。
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%1d",&x[i]);//%1d可以保证只读入一位。
        bool equal=true;
        for(int i=1;i<=n;i++){
            if(equal){//相等的情况
                if(x[i]==0){
                    a[i]=0;
                    b[i]=0;
                }
                if(x[i]==1){
                    equal=false;
                    a[i]=1;
                    b[i]=0;
                }
                if(x[i]==2){
                    a[i]=1;
                    b[i]=1;
                }
            }
            else {//不等的情况
                a[i]=0;
                b[i]=x[i];
            }
        }
        for(int i=1;i<=n;i++)printf("%d",a[i]),a[i]=0;
        printf("\n");
        for(int i=1;i<=n;i++)printf("%d",b[i]),b[i]=0;
        printf("\n");
    }
}
```
核心实现思想：通过循环遍历x的每一位，依据equal的值判断a和b前面部分是否相同，进而确定当前位a和b的值，最后输出a和b。

#### 作者：Ignotus (赞：0)  星级：4星
- **关键亮点**：先确定a和b的首位为1保证较大值最小，之后按位根据x的值和flag（标记第一次出现1的情况）来确定a和b对应位的值，思路直接，代码实现较为直观。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int t,n,flag;
char x[100010],a[100010],b[100010];

int main()
{
        cin>>t;
        while(t--){
                memset(x, '0', sizeof x);
                memset(a, '0', sizeof a);
                memset(b, '0', sizeof b);
                flag=0;//多组数据，需要初始化
                cin>>n;
                getchar();//先读入上一行的换行符
                for(int i=1; i<=n; i++) x[i]=getchar();
                a[1]=b[1]='1';
                for(int i=2; i<=n; i++){
                        if(x[i]=='0') a[i]=b[i]='0';
                        if(x[i]=='1') {
                                if(flag==0){
                                        a[i]='1';
                                        b[i]='0';
                                        flag=1;
                                }
                                else if(flag==1){
                                        a[i]='0';
                                        b[i]='1';
                                }
                        } 
                        if(x[i]=='2'){
                                if(flag==0){
                                        a[i]='1';
                                        b[i]='1';
                                }
                                else if(flag==1){
                                        a[i]='0';
                                        b[i]='2';
                                }
                        }
                }//再根据题意模拟即可
                for(int i=1; i<=n; i++) cout<<a[i];
                cout<<endl;
                for(int i=1; i<=n; i++) cout<<b[i];
                cout<<endl;//输出
        }
        return 0;
}
```
核心实现思想：初始化后，从第二位开始遍历x，根据x[i]的值和flag判断，确定a[i]和b[i]的值，最后输出a和b。

### 最优关键思路或技巧
1. **贪心策略**：根据x每一位数字，优先考虑让a和b的较大值最小。例如x[i] = 0时，a[i] = b[i] = 0 ；x[i] = 2时，在未出现特殊情况前让a[i] = b[i] = 1 。对于x[i] = 1，通过标记记录首次出现时的处理情况，后续根据该标记合理分配a和b对应位的值。
2. **状态记录**：通过一个标记（如flag、flag1、equal等）记录前面数位处理过程中a和b的大小关系情况，以便在当前数位进行决策。

### 可拓展之处
同类型题或类似算法套路：此类题目通常围绕特定进制下的运算规则，结合优化条件（如使某个值最大或最小）进行构造。解决这类问题一般都需要根据运算规则和优化目标，从高位到低位进行贪心构造。类似的题目可能会改变进制、运算规则或优化目标，但解题的核心思路仍基于贪心。

### 洛谷题目推荐
1. **P1080 [NOIP2012 提高组] 国王游戏**：同样是贪心策略的应用，通过对数据进行排序和贪心选择，解决问题。
2. **P2859 [USACO06DEC]Milk Patterns G**：需要利用贪心思想结合字符串相关知识解决问题，与本题类似，需要根据题目条件合理构造答案。
3. **P1223 排队接水**：典型的贪心算法题目，根据每个元素的属性进行贪心决策，使某个目标最优。 

---
处理用时：97.47秒