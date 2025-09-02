# 题目信息

# Take a Guess

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1556D/63568455333cc0a029d6e5fa4f79ae6dd332397f.png)This is an interactive task

William has a certain sequence of integers $ a_1, a_2, \dots, a_n $ in his mind, but due to security concerns, he does not want to reveal it to you completely. William is ready to respond to no more than $ 2 \cdot n $ of the following questions:

- What is the result of a [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) of two items with indices $ i $ and $ j $ ( $ i \neq j $ )
- What is the result of a [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR) of two items with indices $ i $ and $ j $ ( $ i \neq j $ )

You can ask William these questions and you need to find the $ k $ -th smallest number of the sequence.

Formally the $ k $ -th smallest number is equal to the number at the $ k $ -th place in a 1-indexed array sorted in non-decreasing order. For example in array $ [5, 3, 3, 10, 1] $ $ 4 $ th smallest number is equal to $ 5 $ , and $ 2 $ nd and $ 3 $ rd are $ 3 $ .

## 说明/提示

In the example, the hidden sequence is $ [1, 6, 4, 2, 3, 5, 4] $ .

Below is the interaction in the example.

 Query (contestant's program)  Response (interactor)  Notes  and 2 5  2  $ a_2=6 $ , $ a_5=3 $ . Interactor returns bitwise AND of the given numbers.  or 5 6  7  $ a_5=3 $ , $ a_6=5 $ . Interactor returns bitwise OR of the given numbers.  finish 5   $ 5 $ is the correct answer. Note that you must find the value and not the index of the kth smallest number.

## 样例 #1

### 输入

```
7 6

2

7```

### 输出

```
and 2 5

or 5 6

finish 5```

# AI分析结果

### 题目内容翻译
这是一个交互式任务。

威廉心里有一个特定的整数序列 $ a_1, a_2, \dots, a_n $，但出于安全考虑，他不想完全向你透露这个序列。威廉准备回答不超过 $ 2 \cdot n $ 个以下类型的问题：
- 索引为 $ i $ 和 $ j $（$ i \neq j $）的两个元素按位与（[按位与操作](https://en.wikipedia.org/wiki/Bitwise_operation#AND)）的结果是什么？
- 索引为 $ i $ 和 $ j $（$ i \neq j $）的两个元素按位或（[按位或操作](https://en.wikipedia.org/wiki/Bitwise_operation#OR)）的结果是什么？

你可以向威廉提出这些问题，并且需要找出该序列中第 $ k $ 小的数。

形式上，第 $ k $ 小的数等于按非递减顺序排序的 1 - 索引数组中第 $ k $ 位的数。例如，在数组 $ [5, 3, 3, 10, 1] $ 中，第 4 小的数是 5，第 2 和第 3 小的数是 3。

### 算法分类
位运算

### 综合分析与结论
这些题解的核心思路都是利用位运算的性质，通过有限次数的询问求出序列中的所有数，再排序找出第 $k$ 小的数。主要运用的位运算性质有：$a + b = (a\ \text{and}\ b) + (a\ \text{or}\ b)$，$a\ \text{xor}\ b = (a\ \text{and}\ b)\ \text{xor}\ (a\ \text{or}\ b)$ 等。

不同题解的差异在于询问的策略和计算序列元素的方式。部分题解通过询问每个数与 $a_1$ 的和，再利用额外的询问求出 $a_1$；部分题解则将数组分组，每次处理三个相邻的数。

### 所选题解
- **作者：b6e0_ (赞：20)，4星**
    - **关键亮点**：详细证明了两个重要的位运算引理，给出了询问次数的具体证明，代码注释详细，思路清晰。
    - **核心实现思想**：将数组每三个相邻的数分为一组，通过 5 次询问求出这三个数的值。对于剩余不足三个数的情况，再进行额外的询问。最后对数组排序，输出第 $k$ 小的数。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[10005];
inline void get(int i)
{
    int aandb,aorb,axorb,aandc,aorc,axorc,bandc,bxorc,x,y,z;
    cout<<"and "<<i-2<<' '<<i-1<<endl;
    cin>>aandb;
    cout<<"or "<<i-2<<' '<<i-1<<endl;
    cin>>aorb;
    axorb=aandb^aorb;
    cout<<"and "<<i-2<<' '<<i<<endl;
    cin>>aandc;
    cout<<"or "<<i-2<<' '<<i<<endl;
    cin>>aorc;
    axorc=aandc^aorc;
    bxorc=axorb^axorc;
    cout<<"and "<<i-1<<' '<<i<<endl;
    cin>>bandc;
    x=axorb+2*aandb;
    y=axorc+2*aandc;
    z=bxorc+2*bandc;
    a[i-2]=(x+y+z)/2-z;
    a[i-1]=(x+y+z)/2-y;
    a[i]=(x+y+z)/2-x;
    if(i+1==n)
    {
        cout<<"and "<<i<<' '<<i+1<<endl;
        cin>>x;
        cout<<"or "<<i<<' '<<i+1<<endl;
        cin>>y;
        a[i+1]=(x^y)+2*x-a[i];
    }
    if(i+2==n)
    {
        cout<<"and "<<i<<' '<<i+1<<endl;
        cin>>x;
        cout<<"or "<<i<<' '<<i+1<<endl;
        cin>>y;
        a[i+1]=(x^y)+2*x-a[i];
        cout<<"and "<<i<<' '<<i+2<<endl;
        cin>>x;
        cout<<"or "<<i<<' '<<i+2<<endl;
        cin>>y;
        a[i+2]=(x^y)+2*x-a[i];
    }
}
signed main()
{
    int k,i;
    cin>>n>>k;
    for(i=3;i<=n;i+=3)
        get(i);
    sort(a+1,a+n+1);
    cout<<"finish "<<a[k]<<endl;
    return 0;
}
```
- **作者：Miraik (赞：2)，4星**
    - **关键亮点**：详细解释了 $(a\ \text{or}\ b) + (a\ \text{and}\ b) = a + b$ 的结论，代码结构清晰，有完整的输入输出处理。
    - **核心实现思想**：先通过 $2n - 2$ 次询问求出每对相邻元素的和，再通过两次询问求出 $a_1 + a_3$，进而求出 $a_1$，最后根据相邻元素的和求出其他元素的值。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll;
const int N=100005;
const int inf=1<<30;
const ll inff=1ll<<60;
inline int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*f;
}
int s[N],a[N];
void get_a1(int x,int y,int z){
    int a1_a3=x-y;
    a[1]=(a1_a3+z)/2;
}
int main(){
    int tests=1;
    while(tests--){
        int n=read(),k=read();
        for(int i=1;i<n;i++){
            printf("or %d %d\n",i,i+1);
            fflush(stdout);
            s[i+1]=read();
            printf("and %d %d\n",i,i+1);
            fflush(stdout);
            s[i+1]+=read();
        }
        printf("or %d %d\n",1,3);
        fflush(stdout);
        s[1]=read();
        printf("and %d %d\n",1,3);
        fflush(stdout);
        s[1]+=read();
        get_a1(s[2],s[3],s[1]);
        for(int i=2;i<=n;i++)a[i]=s[i]-a[i-1];
        sort(a+1,a+n+1);
        printf("finish %d\n",a[k]);
        fflush(stdout);
    }
    return 0;
}
```
- **作者：NXYorz (赞：2)，4星**
    - **关键亮点**：简洁地证明了 $a + b = a\& b + a|b$ 的结论，代码简洁明了，直接实现了核心思路。
    - **核心实现思想**：先通过 6 次询问求出 $a_1 + a_2$，$a_1 + a_3$，$a_2 + a_3$，解方程组求出 $a_1$，$a_2$，$a_3$，再通过询问 $a_1$ 与其他元素的和求出其他元素的值。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
int n,k;
int a[N];
int main()
{
    scanf("%d%d",&n,&k);
    printf("and 1 2");
    fflush(stdout);
    int x; scanf("%d",&x);
    printf("or 1 2");
    fflush(stdout);
    int x_; scanf("%d",&x_);
    x += x_;
    printf("and 1 3");
    fflush(stdout);
    int y; scanf("%d",&y);
    printf("or 1 3");
    fflush(stdout);
    int y_; scanf("%d",&y_);
    y += y_;
    printf("and 3 2");
    fflush(stdout);
    int z; scanf("%d",&z);
    printf("or 3 2\n");
    fflush(stdout);
    int z_; scanf("%d",&z_);
    z += z_;
    a[2] = (x + z - y) / 2;
    a[1] = x - a[2];
    a[3] = z - a[2];
    for(int i = 4; i <= n; i++)
    {
        printf("and 1 %d",i);
        fflush(stdout);
        scanf("%d",&x);
        printf("or 1 %d",i);
        fflush(stdout);
        scanf("%d",&x_);
        x += x_;
        a[i] = x - a[1];
    }
    sort(a + 1 , a + 1 + n);
    printf("finish %d",a[k]);
    fflush(stdout);
}
```

### 最优关键思路或技巧
- 利用位运算的性质，如 $a + b = (a\ \text{and}\ b) + (a\ \text{or}\ b)$，$a\ \text{xor}\ b = (a\ \text{and}\ b)\ \text{xor}\ (a\ \text{or}\ b)$ 等，将按位与和按位或的结果转化为有用的信息。
- 通过分组处理数组元素，减少询问次数。

### 可拓展之处
同类型题或类似算法套路：
- 其他交互式位运算题目，可能会有不同的询问规则和限制条件，需要灵活运用位运算的性质。
- 涉及位运算的数学问题，如位运算的优化、位运算与方程的结合等。

### 推荐题目
- [P1550 打井问题](https://www.luogu.com.cn/problem/P1550)：涉及位运算和贪心算法。
- [P2114 [NOI2014] 起床困难综合症](https://www.luogu.com.cn/problem/P2114)：主要考察位运算的应用。
- [P3812 【模板】线性基](https://www.luogu.com.cn/problem/P3812)：与位运算和线性代数相关。

### 个人心得
部分题解提到需要注意开 `long long`，否则可能会出现溢出问题。在处理交互式题目时，要注意及时刷新输出缓冲区，确保与交互器的正常通信。

---
处理用时：122.06秒