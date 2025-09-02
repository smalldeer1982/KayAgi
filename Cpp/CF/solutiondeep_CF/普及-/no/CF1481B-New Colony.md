# 题目信息

# New Colony

## 题目描述

After reaching your destination, you want to build a new colony on the new planet. Since this planet has many mountains and the colony must be built on a flat surface you decided to flatten the mountains using boulders (you are still dreaming so this makes sense to you).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1481B/cfa82fc997bb3aa9f87fa07cb8193ccc436f5cb7.png)You are given an array $ h_1, h_2, \dots, h_n $ , where $ h_i $ is the height of the $ i $ -th mountain, and $ k $ — the number of boulders you have.

You will start throwing boulders from the top of the first mountain one by one and they will roll as follows (let's assume that the height of the current mountain is $ h_i $ ):

- if $ h_i \ge h_{i + 1} $ , the boulder will roll to the next mountain;
- if $ h_i < h_{i + 1} $ , the boulder will stop rolling and increase the mountain height by $ 1 $ ( $ h_i = h_i + 1 $ );
- if the boulder reaches the last mountain it will fall to the waste collection system and disappear.

You want to find the position of the $ k $ -th boulder or determine that it will fall into the waste collection system.

## 说明/提示

Let's simulate the first case:

- The first boulder starts at $ i = 1 $ ; since $ h_1 \ge h_2 $ it rolls to $ i = 2 $ and stops there because $ h_2 < h_3 $ .
- The new heights are $ [4,2,2,3] $ .
- The second boulder starts at $ i = 1 $ ; since $ h_1 \ge h_2 $ the boulder rolls to $ i = 2 $ ; since $ h_2 \ge h_3 $ the boulder rolls to $ i = 3 $ and stops there because $ h_3 < h_4 $ .
- The new heights are $ [4,2,3,3] $ .
- The third boulder starts at $ i = 1 $ ; since $ h_1 \ge h_2 $ it rolls to $ i = 2 $ and stops there because $ h_2 < h_3 $ .
- The new heights are $ [4,3,3,3] $ .

The positions where each boulder stopped are the following: $ [2,3,2] $ .

In the second case, all $ 7 $ boulders will stop right at the first mountain rising its height from $ 1 $ to $ 8 $ .

The third case is similar to the first one but now you'll throw $ 5 $ boulders. The first three will roll in the same way as in the first test case. After that, mountain heights will be equal to $ [4, 3, 3, 3] $ , that's why the other two boulders will fall into the collection system.

In the fourth case, the first and only boulders will fall straight into the collection system.

## 样例 #1

### 输入

```
4
4 3
4 1 2 3
2 7
1 8
4 5
4 1 2 3
3 1
5 3 1```

### 输出

```
2
1
-1
-1```

# AI分析结果

### 题目内容
# 新殖民地

## 题目描述
到达目的地后，你想在这个新星球上建立一个新殖民地。由于这个星球有许多山脉，而殖民地必须建在平坦的表面上，所以你决定用巨石来夷平山脉（你还在做梦，所以这对你来说是有意义的）。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1481B/cfa82fc997bb3aa9f87fa07cb8193ccc436f5cb7.png)
给定一个数组$h_1, h_2, \dots, h_n$，其中$h_i$是第$i$座山的高度，以及$k$——你拥有的巨石数量。

你将从第一座山的山顶开始逐个投掷巨石，它们的滚动方式如下（假设当前山的高度为$h_i$）：
 - 如果$h_i \geq h_{i + 1}$，巨石将滚到下一座山；
 - 如果$h_i < h_{i + 1}$，巨石将停止滚动并使山的高度增加$1$（$h_i = h_i + 1$）；
 - 如果巨石到达最后一座山，它将落入废物收集系统并消失。

你想找到第$k$个巨石的位置，或者确定它是否会落入废物收集系统。

## 说明/提示
让我们模拟第一种情况：
 - 第一个巨石从$i = 1$开始；由于$h_1 \geq h_2$，它滚到$i = 2$，并在那里停止，因为$h_2 < h_3$。
 - 新的高度为$[4,2,2,3]$。
 - 第二个巨石从$i = 1$开始；由于$h_1 \geq h_2$，巨石滚到$i = 2$；由于$h_2 \geq h_3$，巨石滚到$i = 3$，并在那里停止，因为$h_3 < h_4$。
 - 新的高度为$[4,2,3,3]$。
 - 第三个巨石从$i = 1$开始；由于$h_1 \geq h_2$，它滚到$i = 2$，并在那里停止，因为$h_2 < h_3$。
 - 新的高度为$[4,3,3,3]$。

每个巨石停止的位置如下：$[2,3,2]$。

在第二种情况下，所有$7$个巨石都将在第一座山上停止，使其高度从$1$增加到$8$。

第三种情况与第一种情况类似，但现在你要投掷$5$个巨石。前三个将以与第一个测试用例相同的方式滚动。之后，山的高度将等于$[4, 3, 3, 3]$，这就是为什么另外两个巨石将落入收集系统。

在第四种情况下，第一个也是唯一的巨石将直接落入收集系统。

## 样例 #1
### 输入
```
4
4 3
4 1 2 3
2 7
1 8
4 5
4 1 2 3
3 1
5 3 1
```

### 输出
```
2
1
-1
-1
```

### 算法分类
模拟

### 综合分析与结论
所有题解的核心思路均为按照题目描述模拟巨石滚动过程。算法要点在于对巨石滚动规则的准确实现，即根据当前山与下一座山高度的比较，决定巨石是继续滚动、停止并增加当前山高度还是落入废物收集系统。解决难点在于处理较大的 $k$ 值，不过各题解都利用了 “若有巨石落入废物收集系统，后续巨石也必定落入” 这一性质，避免了对所有 $k$ 个巨石的无意义模拟，从而降低了时间复杂度。整体来看，各题解思路相近，实现方式略有差异，主要体现在代码风格和细节处理上。

### 所选的题解
 - **作者：Microperson（5星）**
    - **关键亮点**：思路清晰，代码简洁明了，变量命名直观，直接按照题目描述进行模拟，逻辑流畅。
    - **核心代码**：
```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#define N 100010
using namespace std;
int n,k,t,h[N];
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        memset(h,0,sizeof(h));
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&h[i]); 
        }
        int tmp;
        while(k){
            tmp=1;
            for(int i=1;i<=n;i++)
            {
                if(h[i]>=h[i+1]){
                    tmp++;
                } 
                if(h[i]<h[i+1]){
                    h[i]+=1;k--;
                    break;
                }
            }
            if(tmp>=n) {
                cout<<-1<<endl;
                break;
            }   
        }
        if(tmp<n) cout<<tmp<<endl;
    }
    return 0;
 } 
```
核心实现思想：通过两层循环，外层循环控制巨石数量，内层循环模拟巨石滚动，根据高度比较更新巨石位置和山的高度，当巨石到达最后一座山或所有巨石模拟完毕时输出结果。
 - **作者：kdy20100729（4星）**
    - **关键亮点**：代码结构清晰，利用 `while` 循环简洁地实现了巨石滚动的模拟过程，边界条件处理得当。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,pos,a[105];
int main()
{
    cin >> t;
    while(t--)
    {
        cin >> n >> k;
        for(int i=1; i<=n; i++)
            cin >> a[i];
        a[n+1]=0;
        while(k--)
        {
            pos=1;
            while(pos<=n&&a[pos]>=a[pos+1])
                pos++;
            a[pos]++;
            if (pos==n+1)
            {
                pos=-1;
                break;
            }
        }
        cout << pos << "\n";
    }
    return 0;
}
```
核心实现思想：同样通过两层 `while` 循环，外层循环处理每个巨石，内层循环找到巨石停止位置，更新山的高度并判断是否落入废物收集系统，最后输出结果。
 - **作者：huayucaiji（4星）**
    - **关键亮点**：在代码开头对题目进行简要分析，点明 $k$ 大但可利用特殊性质模拟的思路，代码实现中逻辑严谨，边界处理清晰。
    - **核心代码**：
```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
    char ch=getchar();
    int f=1,x=0;
    while(ch<'0'||ch>'9') {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return f*x;
}

const int MAXN=100+10;

int n,h[MAXN],k;

signed main() {
    int t=read();
    while(t--) {
        n=read();k=read();
        for(int i=1;i<=n;i++) {
            h[i]=read();
        }
        h[n+1]=0;
        
        bool flag=1;
        int pos;
        while(k--&&flag) {
            pos=1;
            while(pos<=n&&h[pos]>=h[pos+1]) {
                pos++;
            }
            h[pos]++;
            if(pos==n+1) {
                flag=0;
                pos=-1;
            }
        }
        cout<<pos<<endl;
    }
    return 0;
}
```
核心实现思想：通过两层循环模拟巨石滚动，利用 `flag` 标记是否有巨石落入废物收集系统，在循环中根据高度比较更新位置和高度，最后输出结果。

### 最优关键思路或技巧
利用 “若有巨石落入废物收集系统，后续巨石也必定落入” 这一性质，在模拟过程中一旦发现有巨石落入废物收集系统，即可停止后续模拟，从而优化时间复杂度。

### 可拓展之处
此类题目属于模拟类题目，常见套路是准确理解题目给定的规则，然后按照规则进行模拟。类似题目通常会在规则的复杂程度上进行变化，例如增加更多的条件判断或改变物体的运动规则等。

### 洛谷相似题目推荐
 - [P1035 级数求和](https://www.luogu.com.cn/problem/P1035)：通过模拟计算级数和，考察对简单循环模拟的掌握。
 - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：根据不同包装铅笔的价格和需求数量进行模拟计算，选择最优购买方案，与本题类似在于都需要按照一定规则进行模拟操作。
 - [P5732 【深基5.例3】冰雹猜想](https://www.luogu.com.cn/problem/P5732)：按照特定的数字变换规则进行模拟，直到满足特定条件，同样是对给定规则的模拟实现。

### 个人心得摘录与总结
无。 

---
处理用时：106.37秒