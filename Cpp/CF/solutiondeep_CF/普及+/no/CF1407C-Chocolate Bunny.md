# 题目信息

# Chocolate Bunny

## 题目描述

This is an interactive problem.

We hid from you a permutation $ p $ of length $ n $ , consisting of the elements from $ 1 $ to $ n $ . You want to guess it. To do that, you can give us 2 different indices $ i $ and $ j $ , and we will reply with $ p_{i} \bmod p_{j} $ (remainder of division $ p_{i} $ by $ p_{j} $ ).

We have enough patience to answer at most $ 2 \cdot n $ queries, so you should fit in this constraint. Can you do it?

As a reminder, a permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 样例 #1

### 输入

```
3

1

2

1

0```

### 输出

```
? 1 2

? 3 2

? 1 3

? 2 1

! 1 3 2```

# AI分析结果

### 题目内容中文重写
这是一道交互题。

我们向你隐藏了一个长度为 $n$ 的排列 $p$，该排列由从 $1$ 到 $n$ 的元素组成。你需要猜出这个排列。为此，你可以给我们两个不同的索引 $i$ 和 $j$，我们会回复 $p_{i} \bmod p_{j}$（$p_{i}$ 除以 $p_{j}$ 的余数）。

我们最多有耐心回答 $2 \cdot n$ 次查询，所以你需要满足这个限制。你能做到吗？

提醒一下，长度为 $n$ 的排列是一个由 $n$ 个不同的整数组成的数组，这些整数的范围是从 $1$ 到 $n$，顺序任意。例如，$ [2,3,1,5,4] $ 是一个排列，但 $ [1,2,2] $ 不是一个排列（$ 2 $ 在数组中出现了两次），$ [1,3,4] $ 也不是一个排列（$ n = 3 $，但数组中有 $ 4 $）。

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是利用取模运算的性质，通过两次询问 $a_i \bmod a_j$ 和 $a_j \bmod a_i$ 来确定 $a_i$ 和 $a_j$ 中较小的数。各题解的区别主要在于实现方式和细节处理。
 - **思路**：多数题解通过遍历排列中的元素对，进行两次询问并比较结果，从而确定其中一个元素的值。部分题解采用维护最大值下标的方式，减少不必要的询问。
 - **算法要点**：关键在于利用取模运算的性质，即当 $a < b$ 时，$a \bmod b = a$ 且 $b \bmod a < a$。通过比较两次询问的结果大小，确定较小的数。
 - **解决难点**：由于无法直接确定最大值 $n$ 的位置，多数题解在最后通过特判的方式确定 $n$ 的值。

### 所选题解
- **作者：rui_er (赞：4)，4星**
    - **关键亮点**：思路清晰，代码简洁，通过维护最大值的下标，每次询问最大值下标和当前下标，更新偏小的那个下标的值及最大数的下标，最后确定最大值为 $n$，总询问次数为 $2\times n - 2$。
- **作者：_•́へ•́╬_ (赞：9)，4星**
    - **关键亮点**：详细解释了取模运算的性质和解题思路，代码实现简单直接，通过双重循环遍历未确定值的元素对，每次询问两次确定一个值，最后特判未找出解的元素为 $n$。
- **作者：HeCao2008 (赞：0)，4星**
    - **关键亮点**：思路和其他题解类似，代码实现简洁明了，通过比较两次询问的结果更新元素值，最后确定最大值为 $n$。

### 重点代码
#### rui_er 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4+5;

int n, a[N], ma = 1;

int ask(int x, int y) {
    int _;
    printf("? %d %d\n", x, y);
    fflush(stdout);
    scanf("%d", &_);
    return _;
}

int main() {
    scanf("%d", &n);
    for(int i=2;i<=n;i++) {
        int _1 = ask(ma, i);
        int _2 = ask(i, ma);
        if(_1 > _2) {
            a[ma] = _1;
            ma = i;
        }
        else a[i] = _2;
    }
    a[ma] = n;
    putchar('!');
    for(int i=1;i<=n;i++) printf(" %d", a[i]);
    return 0;
} 
```
**核心实现思想**：维护最大值的下标 `ma`，每次询问 `ma` 和当前下标 `i`，根据询问结果更新元素值和 `ma`，最后 `ma` 对应的元素为 $n$。

#### _•́へ•́╬_ 的代码
```cpp
#include<stdio.h>
int a[10001];
main()
{
    register int n;
    scanf("%d",&n);
    for(register int i=1,x,y;i<=n;++i)if(!a[i])
        for(register int j=1;j<=n;++j)if(!a[j]&&i!=j)
        {
            printf("? %d %d\n? %d %d\n",i,j,j,i);fflush(stdout);
            scanf("%d%d",&x,&y);
            if(x<y)a[j]=y;
            else{a[i]=x;break;}
        }
    printf("! ");
    for(register int i=1;i<=n;++i)
        if(a[i])printf("%d ",a[i]);
        else printf("%d ",n);
    fflush(stdout);
}
```
**核心实现思想**：通过双重循环遍历未确定值的元素对，每次询问两次，根据询问结果确定一个元素的值，最后未确定的元素为 $n$。

#### HeCao2008 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=114514;
int solve(int i,int j){
    cout<<"? "<<i+1<<" "<<j+1<<endl;
    int ans;
    cin>>ans;
    return ans;
} 
int a[maxn];
int main(){
    int n;
    cin>>n;
    int l=0;
    for(int r=1;r<n;r++){
        int aa=solve(l,r);
        int b=solve(r,l);
        if(aa>b){
            a[l]=aa;
            l=r; 
        }else a[r]=b;
    }
    a[l]=n;  
    cout<<"!";
    for(int i=0;i<n;i++)cout<<" "<<a[i];
    return 0;
}
```
**核心实现思想**：通过比较两次询问的结果更新元素值，最后确定最大值为 $n$。

### 最优关键思路或技巧
利用取模运算的性质，通过两次询问 $a_i \bmod a_j$ 和 $a_j \bmod a_i$ 来确定 $a_i$ 和 $a_j$ 中较小的数，从而逐步确定整个排列。同时，通过维护最大值的下标或特判的方式确定最大值 $n$ 的位置。

### 可拓展之处
同类型题可能会有不同的交互方式或取模规则，但核心思路都是利用数学性质进行推理和判断。类似的算法套路还可以应用于其他需要通过交互来获取信息的题目，如猜数字、猜排列等。

### 推荐洛谷题目
- [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)

### 个人心得摘录与总结
- **_•́へ•́╬_**：第一次写交互题，感觉很有挑战。
- **rui_er**：交互题很好玩，通过分析询问次数的限制，找到了解题的思路。
- **walk_alone**：第一次写难度超过1500的题，通过构造线段树的方法解决问题，体会到了分治思想的应用。
- **onglu**：第一次做交互题，因为没刷新缓冲区WA了三发，提醒自己在交互题中要注意刷新缓冲区。

这些心得主要强调了交互题的特殊性和挑战性，以及在解题过程中需要注意的细节，如刷新缓冲区、分析询问次数限制等。同时，也体现了不同解题思路的探索和尝试。

---
处理用时：52.75秒