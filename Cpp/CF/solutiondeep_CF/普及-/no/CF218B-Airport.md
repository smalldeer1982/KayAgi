# 题目信息

# Airport

## 题目描述

Lolek and Bolek are about to travel abroad by plane. The local airport has a special "Choose Your Plane" offer. The offer's conditions are as follows:

- it is up to a passenger to choose a plane to fly on;
- if the chosen plane has $ x $ $ (x&gt;0) $ empty seats at the given moment, then the ticket for such a plane costs $ x $ zlotys (units of Polish currency).

The only ticket office of the airport already has a queue of $ n $ passengers in front of it. Lolek and Bolek have not stood in the queue yet, but they are already wondering what is the maximum and the minimum number of zlotys the airport administration can earn if all $ n $ passengers buy tickets according to the conditions of this offer?

The passengers buy tickets in turn, the first person in the queue goes first, then goes the second one, and so on up to $ n $ -th person.

## 说明/提示

In the first test sample the number of passengers is equal to the number of empty seats, so regardless of the way the planes are chosen, the administration will earn the same sum.

In the second sample the sum is maximized if the 1-st person in the queue buys a ticket to the 1-st plane, the 2-nd person — to the 2-nd plane, the 3-rd person — to the 3-rd plane, the 4-th person — to the 1-st plane. The sum is minimized if the 1-st person in the queue buys a ticket to the 1-st plane, the 2-nd person — to the 1-st plane, the 3-rd person — to the 2-nd plane, the 4-th person — to the 2-nd plane.

## 样例 #1

### 输入

```
4 3
2 1 1
```

### 输出

```
5 5
```

## 样例 #2

### 输入

```
4 3
2 2 2
```

### 输出

```
7 6
```

# AI分析结果

### 题目内容
# 机场

## 题目描述
洛莱克（Lolek）和博莱克（Bolek）即将乘飞机出国旅行。当地机场推出了一项特别的“选择您的飞机”优惠活动。该优惠活动的条件如下：
- 乘客可以自行选择乘坐哪架飞机；
- 如果所选飞机在当时有\(x\)（\(x>0\)）个空座位，那么该飞机的机票价格为\(x\)兹罗提（波兰货币单位）。

机场唯一的售票处前已经排了\(n\)名乘客。洛莱克和博莱克还没有排队，但他们已经在想，如果所有\(n\)名乘客都按照此优惠条件购买机票，机场管理部门最多和最少能赚多少钱呢？

乘客依次购票，排在队列中的第一个人先买，然后是第二个人，依此类推，直到第\(n\)个人。

## 说明/提示
在第一个测试样例中，乘客数量与空座位数量相等，所以无论选择飞机的方式如何，管理部门赚取的金额都相同。

在第二个测试样例中，如果队列中的第1个人购买第1架飞机的机票，第2个人购买第2架飞机的机票，第3个人购买第3架飞机的机票，第4个人购买第1架飞机的机票，那么总金额将达到最大。如果队列中的第1个人购买第1架飞机的机票，第2个人购买第1架飞机的机票，第3个人购买第2架飞机的机票，第4个人购买第2架飞机的机票，那么总金额将达到最小。

## 样例 #1
### 输入
```
4 3
2 1 1
```
### 输出
```
5 5
```
## 样例 #2
### 输入
```
4 3
2 2 2
```
### 输出
```
7 6
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解都围绕贪心算法展开，核心思路是通过不同策略选择飞机座位以获取最大和最小收益。
 - **思路方面**：求最大收益时，让乘客优先选择空位多的飞机；求最小收益时，让乘客优先选择空位少的飞机。
 - **算法要点**：实现方式主要有两种，一种是利用排序，每次排序后选取最大或最小空位的飞机并更新空位；另一种是利用优先队列，大根堆维护最大空位，小根堆维护最小空位，每次取出堆顶元素并更新后重新入堆。
 - **解决难点**：难点在于理解贪心策略的正确性，以及在代码实现中处理好座位数量的更新和边界条件，如防止空座位数为负、判断所有乘客是否都有座位等。

### 所选的题解
 - **作者：L_zaa_L (5星)**
    - **关键亮点**：思路清晰，详细阐述了最大最小值的贪心策略，先排序后通过循环模拟乘客选座过程，代码简洁明了，可读性高。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[10001],mn,mx;
int main(){
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    } 
    sort(a+1,a+n+1);
    int s=0;
    bool flag=0;
    for(int i=1;i<=n;i++){
        int p=a[i];
        while(s!=m&&p){
            mn+=p;
            p--;
            s++;
        }
        if(s==m) break;
    }
    int p=a[n];
    s=0;
    for(int i=p;i>=1;i--){
        for(int j=n;j>=1;j--){
            while(a[j]>=i&&s!=m){
                s++;
                mx+=a[j];
                a[j]--;
            }
            if(s==m) break;
        }
        if(s==m) break;
    }
    cout<<mx<<" "<<mn; 
    return 0;
} 
```
    - **核心实现思想**：先对飞机座位数排序，求最小值时，从前往后遍历座位数，将每架飞机坐满直到所有乘客都有座位；求最大值时，从最大座位数开始，从后往前遍历座位数组，让乘客选择空位大于等于当前值的飞机，更新答案和座位数。
 - **作者：_byta (4星)**
    - **关键亮点**：利用优先队列（大根堆和小根堆）分别维护最大空位和最小空位，代码简洁高效，对优先队列的使用熟练。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1002;
int n,m,k,p,ans,sum,tot,cnt,a[N],b[N],c[N];
priority_queue<int> q;
priority_queue<int,vector<int>,greater<int> > q2;
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>a[i];
        q.push(a[i]);
        q2.push(a[i]);
    }
    for(int i=1;i<=n;i++)
    {
        int maxn=q.top();
        q.pop();
        ans+=maxn;
        if(maxn-1!=0)q.push(maxn-1);
        int minn=q2.top();
        q2.pop();
        sum+=minn;
        if(minn-1!=0)q2.push(minn-1);
    }
    cout<<ans<<" "<<sum;
    return 0;
}
```
    - **核心实现思想**：将飞机座位数分别加入大根堆和小根堆，每次从大根堆取最大值作为当前乘客选择的飞机空位计算最大收益，从取出值减1后若非零则重新入堆；从小根堆取最小值计算最小收益，同样处理更新后的座位数。
 - **作者：xiaomuyun (4星)**
    - **关键亮点**：对优先队列的使用讲解详细，代码结构清晰，在代码注释中对变量和每一步操作解释到位，便于理解。
    - **重点代码**：
```cpp
#include<cstdio>
#include<queue>
using namespace std;
int n,m,seat[1001],res1=0,res2=0;
priority_queue<int,vector<int>,less<int> > q1;
priority_queue<int,vector<int>,greater<int> > q2;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i) scanf("%d",&seat[i]);
    for(int i=1;i<=m;++i){
        q1.push(seat[i]);
        q2.push(seat[i]);
    }
    for(int i=1;i<=n;++i){
        int val=q1.top();
        q1.pop();
        res1+=val--;
        if(val>0) q1.push(val);
    }
    for(int i=1;i<=n;++i){
        int val=q2.top();
        q2.pop();
        res2+=val--;
        if(val>0) q2.push(val);
    }
    printf("%d %d\n",res1,res2);
    return 0;
}
```
    - **核心实现思想**：与 _byta 的思路类似，利用优先队列分别求最大和最小收益，每次从相应优先队列取顶元素计算收益并更新座位数重新入队，注意判断座位数是否为零。

### 最优关键思路或技巧
利用贪心策略，结合排序或优先队列数据结构。优先队列能高效地获取最大或最小值，在动态更新数据时优势明显；排序后的数组则可以通过遍历实现类似的效果，且代码相对简单，理解成本低。

### 可拓展思路
此类贪心题目通常围绕资源分配，可拓展到类似的场景，如任务分配（每个任务有不同报酬和所需资源，根据资源贪心分配任务获取最大报酬）、背包问题的变体（物品价值随背包剩余容量变化）等。

### 洛谷相似题目推荐
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)
 - [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248) 

---
处理用时：54.46秒