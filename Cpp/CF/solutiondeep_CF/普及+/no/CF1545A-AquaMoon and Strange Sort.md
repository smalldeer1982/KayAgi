# 题目信息

# AquaMoon and Strange Sort

## 题目描述

AquaMoon has $ n $ friends. They stand in a row from left to right, and the $ i $ -th friend from the left wears a T-shirt with a number $ a_i $ written on it. Each friend has a direction (left or right). In the beginning, the direction of each friend is right.

AquaMoon can make some operations on friends. On each operation, AquaMoon can choose two adjacent friends and swap their positions. After each operation, the direction of both chosen friends will also be flipped: left to right and vice versa.

AquaMoon hopes that after some operations, the numbers written on the T-shirt of $ n $ friends in the row, read from left to right, become non-decreasing. Also she wants, that all friends will have a direction of right at the end. Please find if it is possible.

## 说明/提示

The possible list of operations in the first test case:

1. Swap $ a_1 $ and $ a_2 $ . The resulting sequence is $ 3, 4, 2, 5 $ . The directions are: left, left, right, right.
2. Swap $ a_2 $ and $ a_3 $ . The resulting sequence is $ 3, 2, 4, 5 $ . The directions are: left, left, right, right.
3. Swap $ a_1 $ and $ a_2 $ . The resulting sequence is $ 2, 3, 4, 5 $ . The directions are: right, right, right, right.

## 样例 #1

### 输入

```
3
4
4 3 2 5
4
3 3 2 2
5
1 2 3 5 4```

### 输出

```
YES
YES
NO```

# AI分析结果

### 题目翻译
# AquaMoon和奇怪的排序

## 题目描述
AquaMoon 有 $n$ 个朋友。他们从左到右站成一排，从左数第 $i$ 个朋友穿着一件写有数字 $a_i$ 的 T 恤。每个朋友都有一个方向（向左或向右）。一开始，每个朋友的方向都是向右。

AquaMoon 可以对朋友们进行一些操作。在每次操作中，AquaMoon 可以选择两个相邻的朋友并交换他们的位置。每次操作后，这两个被选中的朋友的方向也会翻转：向左变为向右，反之亦然。

AquaMoon 希望经过一些操作后，从左到右读取的 $n$ 个朋友 T 恤上的数字变得非递减。此外，她还希望最后所有朋友的方向都向右。请判断这是否可能。

## 说明/提示
第一个测试用例中可能的操作列表：
1. 交换 $a_1$ 和 $a_2$。得到的序列是 $3, 4, 2, 5$。方向是：向左，向左，向右，向右。
2. 交换 $a_2$ 和 $a_3$。得到的序列是 $3, 2, 4, 5$。方向是：向左，向左，向右，向右。
3. 交换 $a_1$ 和 $a_2$。得到的序列是 $2, 3, 4, 5$。方向是：向右，向右，向右，向右。

## 样例 #1
### 输入
```
3
4
4 3 2 5
4
3 3 2 2
5
1 2 3 5 4
```
### 输出
```
YES
YES
NO
```

### 算法分类
排序

### 综合分析与结论
这些题解的核心思路都是基于每个人交换次数与方向的关系，即每个人交换次数为偶数时方向才能保持向右，进而得出每个人初始和最终位置的距离应为偶数，位置的奇偶性不变。

各题解的思路和方法有相似之处，主要区别在于具体的实现方式：
- 大部分题解通过统计每个数在原序列和排序后序列中奇数位和偶数位的出现次数来判断是否满足条件。
- 有题解使用树状数组求一个数前面比它大的数的个数和后面比它小的数的个数，再处理相同数的情况，将其转化为括号匹配问题。
- 还有题解利用 `std::valarray` 和 `std::slice` 进行切片排序来判断。

### 所选题解
- **云浅知处（5星）**
    - **关键亮点**：思路清晰，详细阐述了从位置变化到利用桶统计奇偶位置出现次数的推理过程，代码简洁明了，有自定义的输入函数。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
    int x=0,f=1;char ch=getchar();
    for(;(!(ch>='0'&&ch<='9'));ch=getchar())if(ch=='-')f=-1;
    for(;(ch>='0'&&ch<='9');ch=getchar())x=(x<<1)+(x<<3)+(ch-'0');
    return x*f;
}
const int MN=1e5+5;
int n,a[MN],f[MN],g[MN];
signed main(void){
    int tt=read();while(tt--){
        n=read();bool ans=1;
        for(int i=1;i<=n;i++){
            a[i]=read();
            f[a[i]]+=(i%2==0),g[a[i]]+=(i%2==1);
        }
        sort(a+1,a+n+1);
        for(int i=1;i<=n;i++)f[a[i]]-=(i%2==0),g[a[i]]-=(i%2==1);
        for(int i=1;i<=n;i++)if(f[a[i]]!=0||g[a[i]]!=0)ans=0;
        puts(ans?"YES":"NO");
        for(int i=1;i<=n;i++)f[a[i]]=g[a[i]]=0;
    }
    return 0;
}
```
    - **核心实现思想**：用 `f` 数组统计每个数在原序列偶数位的出现次数，`g` 数组统计奇数位的出现次数。排序后再次统计，若对应次数不相等则无法满足条件。

- **JCLinux（4星）**
    - **关键亮点**：详细分析题意关键点和思路过程，代码结构清晰，注释较少但逻辑易懂。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int inital[100005];
int sorted[100005];
int arr[100005];
int n;
int main(){
    int t;cin >>t;
    while(t--){
        cin >>n;
        int mmax=0;
        int mmin=100005;
        for(int i=1;i<=n;i++){
            cin >>arr[i];
            mmax=max(mmax,arr[i]);
            mmin=min(mmin,arr[i]);
        }
        for(int i=mmin;i<=mmax;i++)inital[i]=sorted[i]=0;
        for(int i=1;i<=n;i++) {
            if(i%2){
                inital[arr[i]]++;
            }
        }
        sort(arr+1,arr+1+n);
        for(int i=1;i<=n;i++){
            if(i%2){
                sorted[arr[i]]++;
            }
        }
        bool flag=1;
        for(int i=mmin;i<=mmax;i++){
            if(inital[i]!=sorted[i]){
                flag=0;
                break;
            }
        }
        if(flag)cout <<"YES"<<endl;
        else cout <<"NO"<<endl;
    }
}
```
    - **核心实现思想**：用 `inital` 数组统计原序列中奇数位每个数的出现次数，排序后用 `sorted` 数组统计，比较两个数组对应值是否相等。

- **KSToki（4星）**
    - **关键亮点**：详细分析题目大意和解题思路，强调多测时数组清空的重要性，避免 FST，代码有自定义输入函数。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
I int read()
{
    char ch=getchar();
    int res=0,flag=1;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            flag=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        res=res*10+ch-'0';
        ch=getchar();
    }
    return res*flag;
}
int T,n,a[100001],cnt[100001][2];
int main()
{
    T=read();
    while(T--)
    {
        n=read();
        memset(cnt,0,sizeof(cnt));
        for(R int i=1;i<=n;++i)
        {
            a[i]=read();
            ++cnt[a[i]][i&1];
        }
        sort(a+1,a+n+1);
        for(R int i=1;i<=n;++i)
        {
            if(!cnt[a[i]][i&1])
            {
                puts("NO");
                goto over;
            }
            --cnt[a[i]][i&1];
        }
        puts("YES");
        over:;
    }
    return 0;
}
```
    - **核心实现思想**：用 `cnt` 数组统计每个数在原序列中奇偶位置的出现次数，排序后依次检查，若对应位置次数不足则无法满足条件。

### 最优关键思路或技巧
- 利用位置的奇偶性不变这一特性，通过统计每个数在原序列和排序后序列中奇数位和偶数位的出现次数来判断是否能满足条件。
- 对于多测问题，要注意每次测试前将相关数组清空，避免数据残留导致错误。

### 可拓展之处
同类型题可能会有不同的交换规则和限制条件，但核心思路可能都是基于元素的位置变化和某种不变性来判断是否能达到目标状态。类似算法套路可以应用于其他涉及元素交换和排序的问题，通过分析元素的移动规律和不变量来解决问题。

### 推荐洛谷题目
1. [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)
2. [P1093 奖学金](https://www.luogu.com.cn/problem/P1093)
3. [P1271 【深基9.例1】选举学生会](https://www.luogu.com.cn/problem/P1271)

### 个人心得摘录与总结
- **FutaRimeWoawaSete**：在做题时差点得到正解，但因自己打错代码且未发现，还轻信别人的错解，导致后续出现问题。总结出以后要先思考再动手。
- **Acfboy**：在赛场上对问题的思考出现错误，错误地认为交换能改变奇偶性，实际上两个奇偶性相同位置的交换没有改变什么，提醒我们要仔细分析问题，避免逻辑错误。
- **KSToki**：指出本题多测时由于 $a_i$ 可能大于 $n$，按习惯从 $1$ 扫到 $n$ 会导致 FST，强调要注意多测时数组清空的范围，避免因数据范围问题出错。 

---
处理用时：66.71秒