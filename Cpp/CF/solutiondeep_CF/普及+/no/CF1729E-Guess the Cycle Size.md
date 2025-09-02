# 题目信息

# Guess the Cycle Size

## 题目描述

This is an interactive problem.

I want to play a game with you...

We hid from you a cyclic graph of $ n $ vertices ( $ 3 \le n \le 10^{18} $ ). A cyclic graph is an undirected graph of $ n $ vertices that form one cycle. Each vertex belongs to the cycle, i.e. the length of the cycle (the number of edges in it) is exactly $ n $ . The order of the vertices in the cycle is arbitrary.

You can make queries in the following way:

- "? a b" where $ 1 \le a, b \le 10^{18} $ and $ a \neq b $ . In response to the query, the interactor outputs on a separate line the length of random of two paths from vertex $ a $ to vertex $ b $ , or -1 if $ \max(a, b) > n $ . The interactor chooses one of the two paths with equal probability. The length of the path —is the number of edges in it.

You win if you guess the number of vertices in the hidden graph (number $ n $ ) by making no more than $ 50 $ queries.

Note that the interactor is implemented in such a way that for any ordered pair $ (a, b) $ , it always returns the same value for query "? a b", no matter how many such queries. Note that the "? b a" query may be answered differently by the interactor.

The vertices in the graph are randomly placed, and their positions are fixed in advance.

Hacks are forbidden in this problem. The number of tests the jury has is $ 50 $ .

## 说明/提示

In the first example, the graph could look like this

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1729E/9ade550fb3e264ef1dadca91be3accfdcc0d9e04.png)The lengths of the simple paths between all pairs of vertices in this case are $ 1 $ or $ 2 $ .

- The first query finds out that one of the simple paths from vertex $ 1 $ to vertex $ 2 $ has a length of $ 1 $ .
- With the second query, we find out that one of the simple paths from vertex $ 1 $ to vertex $ 3 $ has length $ 2 $ .
- In the third query, we find out that vertex $ 4 $ is not in the graph. Consequently, the size of the graph is $ 3 $ .

## 样例 #1

### 输入

```
1

2

-1```

### 输出

```
? 1 2

? 1 3

? 1 4

! 3```

# AI分析结果

### 题目内容中文重写
## 猜测循环大小

### 题目描述
这是一个交互式问题。

我想和你玩一个游戏……

我们向你隐藏了一个有 $n$ 个顶点的循环图（$3 \leq n \leq 10^{18}$）。循环图是一个由 $n$ 个顶点组成一个环的无向图。每个顶点都属于这个环，即环的长度（其中边的数量）恰好为 $n$。环中顶点的顺序是任意的。

你可以通过以下方式进行查询：
- “? a b”，其中 $1 \leq a, b \leq 10^{18}$ 且 $a \neq b$。作为对查询的响应，交互器会在单独的一行输出从顶点 $a$ 到顶点 $b$ 的两条路径中随机一条的长度，如果 $\max(a, b) > n$ 则输出 -1。交互器以相等的概率选择两条路径中的一条。路径的长度是指其中边的数量。

如果你在不超过 50 次查询内猜出隐藏图中的顶点数量（数字 $n$），你就赢了。

请注意，交互器的实现方式是，对于任何有序对 $(a, b)$，无论进行多少次这样的查询，它总是返回相同的值。请注意，“? b a” 查询的答案可能与交互器的回答不同。

图中的顶点是随机放置的，并且它们的位置是预先固定的。

本题禁止使用 Hack。评测机的测试数据数量为 50 组。

### 说明/提示
在第一个示例中，图可能如下所示：
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1729E/9ade550fb3e264ef1dadca91be3accfdcc0d9e04.png)
在这种情况下，所有顶点对之间的简单路径长度为 1 或 2。
- 第一个查询发现从顶点 1 到顶点 2 的一条简单路径长度为 1。
- 第二个查询发现从顶点 1 到顶点 3 的一条简单路径长度为 2。
- 第三个查询发现顶点 4 不在图中。因此，图的大小为 3。

### 样例 #1
#### 输入
```
1
2
-1
```
#### 输出
```
? 1 2
? 1 3
? 1 4
! 3
```

### 算法分类
概率论

### 综合分析与结论
这些题解主要围绕如何在不超过 50 次询问的条件下猜出循环图的顶点数 $n$。核心思路是利用询问 $(a,b)$ 和 $(b,a)$ 可能返回不同结果的特性，若两次结果不同，其和即为环的顶点数 $n$。同时，要注意特判询问结果为 -1 的情况，这表示询问的顶点超出了图的范围。各题解的差异主要在于实现细节和对特殊情况的处理方式，但整体思路一致。

### 所选题解
- **Mashiroqwq（5星）**
    - **关键亮点**：不仅给出了常规情况的解法，还提供了加强版（询问 $(a,b)$ 和 $(b,a)$ 结果相同）的做法，思路清晰且全面。
    - **个人心得**：提醒大家不要只看大意而忽略细节。
- **FFTotoro（4星）**
    - **关键亮点**：思路清晰，代码简洁，还提到了将 WA 变成 TLE 利用 CF 重测机制的技巧。
    - **个人心得**：对 Div.3 出交互题表示感动。
- **zhicheng（4星）**
    - **关键亮点**：详细计算了算法完全正确的概率，让读者对算法的可靠性有更清晰的认识。
    - **个人心得**：提到代码在赛时评测有一个点跑了 18 次询问，像撞大运。

### 重点代码
#### Mashiroqwq 常规情况代码
```cpp
for(int i=2;i<=26;++i){
    int a=ask(1,i);
    if(a==-1){
        cout << "! " << i-1 << endl;
        return 0;
    }
    int b=ask(i,1);
    if(a!=b){
        cout << "! " << a+b << endl;
        return 0;
    }
}
```
**核心实现思想**：枚举点 $i$，询问 $(1,i)$ 和 $(i,1)$，若结果不同则输出两结果之和作为环的顶点数；若结果为 -1，则输出 $i - 1$ 作为环的顶点数。

#### FFTotoro 代码
```cpp
#include<iostream>
#define int long long
using namespace std;
main(){
    ios::sync_with_stdio(false);
    for(int i=2;i<=26;i++){
        cout<<"? 1 "<<i<<endl;
        cout<<flush;
        int x; cin>>x;
        if(x==-1){
            cout<<"! "<<i-1<<endl;
            cout<<flush;
            return 0;
        }
        cout<<"? "<<i<<" 1"<<endl;
        cout<<flush;
        int y; cin>>y;
        if(x!=y){
            cout<<"! "<<x+y<<endl;
            cout<<flush;
            return 0;
        }
    }
    while(1);
}
```
**核心实现思想**：与 Mashiroqwq 常规情况思路一致，只是增加了 `while(1)` 防止 WA，利用 CF 重测机制。

#### zhicheng 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long p,q;
    for(int i=2;;i++){
        printf("? 1 %d\n",i);  //两次询问
        fflush(stdout);
        scanf("%lld",&p);
        if(p==-1){  //越界
            printf("! %d",i-1);
            fflush(stdout);
            return 0;
        }
        printf("? %d 1\n",i);
        fflush(stdout);
        scanf("%lld",&q);
        if(p!=q){  //得出答案
            printf("! %d",p+q);
            fflush(stdout);
            return 0;
        }
    }
}
```
**核心实现思想**：同样是枚举点 $i$，询问 $(1,i)$ 和 $(i,1)$，根据结果判断环的顶点数。

### 关键思路或技巧
- 利用询问 $(a,b)$ 和 $(b,a)$ 可能返回不同结果的特性，若不同则两结果之和即为环的顶点数。
- 特判询问结果为 -1 的情况，此时询问的顶点超出图的范围。
- 对于随机化算法，可以考虑利用评测机制（如 CF 的重测机制）来提高通过概率。

### 拓展思路
同类型题可能会有不同的交互规则或图的性质变化，但核心思路都是利用有限的询问次数和已知信息来推断未知信息。类似的算法套路包括利用对称性、概率特性等进行信息收集和推断。

### 推荐洛谷题目
- P1168 中位数
- P1969 积木大赛
- P2678 跳石头

### 个人心得总结
- Mashiroqwq 提醒大家做题要注意细节，不要只看大意。
- FFTotoro 提到 Div.3 出交互题很感动，还介绍了将 WA 变成 TLE 利用重测机制的技巧。
- zhicheng 分享了代码在赛时的运行情况，像撞大运，体现了随机化算法的不确定性。

---
处理用时：50.97秒