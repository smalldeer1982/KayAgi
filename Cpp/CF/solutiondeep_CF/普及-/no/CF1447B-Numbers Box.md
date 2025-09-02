# 题目信息

# Numbers Box

## 题目描述

You are given a rectangular grid with $ n $ rows and $ m $ columns. The cell located on the $ i $ -th row from the top and the $ j $ -th column from the left has a value $ a_{ij} $ written in it.

You can perform the following operation any number of times (possibly zero):

- Choose any two adjacent cells and multiply the values in them by $ -1 $ . Two cells are called adjacent if they share a side.

Note that you can use a cell more than once in different operations.

You are interested in $ X $ , the sum of all the numbers in the grid.

What is the maximum $ X $ you can achieve with these operations?

## 说明/提示

In the first test case, there will always be at least one $ -1 $ , so the answer is $ 2 $ .

In the second test case, we can use the operation six times to elements adjacent horizontally and get all numbers to be non-negative. So the answer is: $ 2\times 1 + 3\times2 + 3\times 3 + 2\times 4 + 1\times 5 = 30 $ .

## 样例 #1

### 输入

```
2
2 2
-1 1
1 1
3 4
0 -1 -2 -3
-1 -2 -3 -4
-2 -3 -4 -5```

### 输出

```
2
30```

# AI分析结果

### 题目内容
# 数字方格

## 题目描述
给定一个有$n$行和$m$列的矩形网格。位于从上往下数第$i$行、从左往右数第$j$列的单元格中写有值$a_{ij}$。

你可以执行以下操作任意次（可能为零次）：
 - 选择任意两个相邻的单元格，并将它们的值乘以$-1$。如果两个单元格共享一条边，则称它们为相邻单元格。

注意，你可以在不同的操作中多次使用同一个单元格。

你对$X$感兴趣，$X$即网格中所有数字的和。

通过这些操作，你能得到的$X$的最大值是多少？

## 说明/提示
在第一个测试用例中，总会至少有一个$-1$，所以答案是$2$。

在第二个测试用例中，我们可以对水平相邻的元素使用该操作六次，使所有数字都变为非负数。所以答案是：$2×1 + 3×2 + 3×3 + 2×4 + 1×5 = 30$。

## 样例 #1
### 输入
```
2
2 2
-1 1
1 1
3 4
0 -1 -2 -3
-1 -2 -3 -4
-2 -3 -4 -5
```
### 输出
```
2
30
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解的核心思路均为贪心策略，要点在于发现每次操作可以等效为翻转任意两个数，进而根据矩阵中负数个数的奇偶性来决定最终的和。若负数个数为偶数，可将所有负数变为正数，答案就是所有数绝对值之和；若负数个数为奇数，则保留绝对值最小的数为负数，其余变为正数，答案为所有数绝对值之和减去绝对值最小数的两倍。各题解思路相近，主要区别在于代码实现的细节与风格。

### 所选的题解
 - **作者：试试事实上吗 (赞：4)  星级：5星**
    - **关键亮点**：清晰证明了每次操作可等效于翻转任意两个数，逻辑严谨，代码简洁明了。
    - **重点代码**：
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int maxn=105;

int n,m;

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int cnt=0,ans=0,mi=101;
        scanf("%d%d",&n,&m);
        for(int i=1,x;i<=n;++i)
            for(int j=1;j<=m;++j)
            {
                scanf("%d",&x);
                if(x<0) x=-x,++cnt;
                mi=min(mi,x);ans+=x;
            }
        if(cnt&1) printf("%d\n",ans-mi*2);
        else printf("%d\n",ans);
    }
    return 0;
}
```
    - **核心实现思想**：遍历输入矩阵，统计负数个数`cnt`，计算所有数绝对值之和`ans`并记录绝对值最小的数`mi`。根据`cnt`的奇偶性决定输出结果，若为奇数则`ans`减去`mi`的两倍，否则直接输出`ans`。
 - **作者：Sternenlicht (赞：0)  星级：4星**
    - **关键亮点**：代码结构清晰，采用自定义输入输出函数，对负数个数奇偶性的处理逻辑明确。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
namespace IO{
    #define LL long long
    inline LL read(){
        LL x=0,f=1;char c=getchar();
        for (;!isdigit(c);c=getchar())if (c=='-')f=-1;
        for (;isdigit(c);c=getchar())x=(x<<3)+(x<<1)+(c^48);
        return x*f;
    }
    inline void write(LL x,char c='\n'){
        if (x){
            if (x<0)x=-x,putchar('-');
            char a[30];short l;
            for (l=0;x;x/=10)a[l++]=x%10^48;
            for (l--;l>=0;l--)putchar(a[l]);
        }else putchar('0');putchar(c);
    }
}using namespace IO;
using namespace std;

#define INF 0x3f3f3f3f
const int N = 20;
int a[N][N];
int main(){
    int T=read();
    while (T--){
        //ans统计绝对值之和，num统计负数个数，minn记录绝对值最小的数 
        int n=read(),m=read(),ans=0,num=0,minn=INF;
        for (int i=1;i<=n;i++)
            for (int j=1;j<=m;j++)
                a[i][j]=read();
        for (int i=1;i<=n;i++)
            for (int j=1;j<=m;j++){
                minn=min(minn,abs(a[i][j]));//求绝对值最小的数 
                ans+=abs(a[i][j]);//求绝对值之和 
                if (a[i][j]<0)num++;//记录负数个数 
            }
        if (num&1)ans-=2*minn;//若有奇数个负数，ans减去绝对值最小的数
        write(ans);//输出 
    }
    return 0;
}
```
    - **核心实现思想**：通过自定义`read`和`write`函数进行输入输出，遍历矩阵获取绝对值最小数`minn`、所有数绝对值之和`ans`以及负数个数`num`，根据`num`奇偶性调整`ans`并输出。
 - **作者：vectorwyx (赞：0)  星级：4星**
    - **关键亮点**：简洁地阐述了负号转移思路，代码实现紧凑，对边界情况处理得当。
    - **重点代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
    int x=0,fh=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-') fh=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*fh;
}

int a[15][15];

void work(){
    int n=read(),m=read(),cnt=0,sum=0,mx=-1e9,mn=1e9;
    fo(i,1,n)
        fo(j,1,m) a[i][j]=read(),sum+=abs(a[i][j]);
    fo(i,1,n)
        fo(j,1,m){
            if(a[i][j]<0) ++cnt,mx=max(mx,a[i][j]);
            else mn=min(mn,a[i][j]);
        }
    if(cnt&1) printf("%d\n",sum-2*min(-mx,mn));
    else printf("%d\n",sum);
    //puts("");
}
int main(){
    int T=read();
    while(T--){
        work();
    }
    return 0;
}
```
    - **核心实现思想**：通过`read`函数输入，在`work`函数中遍历矩阵计算绝对值和`sum`、负数个数`cnt`，并分别记录负数中的最大值`mx`和非负数中的最小值`mn`，根据`cnt`奇偶性输出结果。

### 最优关键思路或技巧
发现相邻单元格操作可等效为翻转任意两个数这一关键性质，基于此根据负数个数的奇偶性进行贪心处理，这是解决本题的核心技巧。

### 可拓展思路
此类题目通常围绕某种操作对数据和的影响展开，类似套路是分析操作的本质效果，转化为简单的数学判断（如奇偶性），进而利用贪心策略求解。

### 洛谷相似题目推荐
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
 - [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199) 

---
处理用时：69.42秒