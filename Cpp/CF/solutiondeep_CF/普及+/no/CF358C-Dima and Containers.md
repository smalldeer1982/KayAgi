# 题目信息

# Dima and Containers

## 题目描述

# Dima和容器


Dima 的生日快到了！这是个重要的日子！Saryozha 送给 Dima的礼物是，他会离开房间，不打扰 Dima 和 Inna 庆祝生日。Inna 送给 Dima 的礼物是一个堆栈（stack）、一个队列（queue）和一个双端队列（deck）。

Inna 希望她的礼物能向 Dima 展示他是多么优秀的程序员。为此，她会逐个给 Dima 发送命令。有两种类型的命令：

1. 将给定的数字添加到其中一个容器中。对于队列和堆栈，你只能将元素添加到末尾。对于双端队列，你可以将元素添加到开头或末尾。
2. 从至多三个不同的容器中提取一个数字。将所有提取出的数字告诉 Inna，然后清空所有容器。对于队列容器，你只能从开头提取数字。对于堆栈容器，你只能从末尾提取数字。对于双端队列容器，你可以从开头或末尾提取数字。你不能从空容器中提取数字。

每次 Dima 执行第二类型的命令时，Inna 就会亲吻 Dima 若干次（可能为零）。Dima 非常了解 Inna，他确定这个数字等于他在此操作中从容器中提取的数字之和。

正如我们之前说的，Dima 非常了解 Inna，他知道 Inna 将给他什么命令以及命令的顺序。帮助 Dima 找到让他在生日上获得尽可能多亲吻的策略！

## 样例 #1

### 输入

```
10
0
1
0
1
2
0
1
2
3
0
```

### 输出

```
0
pushStack
1 popStack
pushStack
pushQueue
2 popStack popQueue
pushStack
pushQueue
pushFront
3 popStack popQueue popFront
```

## 样例 #2

### 输入

```
4
1
2
3
0
```

### 输出

```
pushStack
pushQueue
pushFront
3 popStack popQueue popFront
```

# AI分析结果

### 题目内容
# Dima和容器

## 题目描述

# Dima和容器

Dima 的生日快到了！这是个重要的日子！Saryozha 送给 Dima的礼物是，他会离开房间，不打扰 Dima 和 Inna 庆祝生日。Inna 送给 Dima 的礼物是一个堆栈（stack）、一个队列（queue）和一个双端队列（deck）。

Inna 希望她的礼物能向 Dima 展示他是多么优秀的程序员。为此，她会逐个给 Dima 发送命令。有两种类型的命令：

1. 将给定的数字添加到其中一个容器中。对于队列和堆栈，你只能将元素添加到末尾。对于双端队列，你可以将元素添加到开头或末尾。
2. 从至多三个不同的容器中提取一个数字。将所有提取出的数字告诉 Inna，然后清空所有容器。对于队列容器，你只能从开头提取数字。对于堆栈容器，你只能从末尾提取数字。对于双端队列容器，你可以从开头或末尾提取数字。你不能从空容器中提取数字。

每次 Dima 执行第二类型的命令时，Inna 就会亲吻 Dima 若干次（可能为零）。Dima 非常了解 Inna，他确定这个数字等于他在此操作中从容器中提取的数字之和。

正如我们之前说的，Dima 非常了解 Inna，他知道 Inna 将给他什么命令以及命令的顺序。帮助 Dima 找到让他在生日上获得尽可能多亲吻的策略！

## 样例 #1

### 输入
```
10
0
1
0
1
2
0
1
2
3
0
```

### 输出
```
0
pushStack
1 popStack
pushStack
pushQueue
2 popStack popQueue
pushStack
pushQueue
pushFront
3 popStack popQueue popFront
```

## 样例 #2

### 输入
```
4
1
2
3
0
```

### 输出
```
pushStack
pushQueue
pushFront
3 popStack popQueue popFront
```

### 算法分类
贪心

### 综合分析与结论
这几道题解思路较为一致，均采用贪心策略，核心在于每次遇到提取操作（输入为0）时，要从三种容器中取出尽可能大的数字，使得取出数字之和最大。不同题解在具体实现细节和代码表述上存在差异。

### 所选的题解
 - **作者：流绪 (赞：4)  星级：4星 关键亮点：思路清晰，代码实现完整且注释详细。**
```cpp
#include<bits/stdc++.h>
#define maxn 1000010
int p[maxn];
using namespace std;
int main()
{
    char pop[3][10]={"popStack","popQueue","popFront"};
    int n;
    cin >> n;
    for(int i=1;i<=n;i++)
        cin >> p[i];
    int a,b,c;
    for(int i=1;i<=n;i++)
    {
        a=b=c=0;
        int j=i;
        while(p[j]&&j<=n)
        {
            if(p[j] > a)
                c=b,b=a,a=p[j];
            else if(p[j] > b)
                c=b,b=p[j];
            else if(p[j] > c)
                c=p[j];
            j++;
        }
        if(!a&&!b&&!c)
            cout << 0 <<endl;
        else
        {
            int cnt = 3;
            if(!b)
                cnt--;
            if(!c)
                cnt--;
            for(int k=i;k<j;k++)
            {
                if(p[k] == a)
                {
                    cout << "pushStack\n";
                    a=0;
                }
                else if(p[k] == b)
                {
                    cout << "pushQueue\n";
                    b=0;
                }
                else if(p[k] == c)
                {
                    cout << "pushFront\n";
                    c=0;
                }
                else
                    cout << "pushBack\n";
            }
            if(j > n)
                break;
            cout << cnt;
            for(int k=0;k<cnt;k++)
                cout << " " << pop[k];
            cout << endl;
            i=j;
        }
    }
}
```
核心实现思想：通过两重循环遍历输入数据，内层循环找出两个0之间的最大值a、次大值b和第三大值c，然后外层循环根据这些值决定将数字压入哪个容器，最后根据最大值的个数输出弹出操作。

 - **作者：wish_ (赞：1)  星级：4星 关键亮点：对思路和模拟过程阐述详细。**
```cpp
    for(int i=1;i<=n;i++){
        a=b=c=0;
        j=i;
        while(o[j]&&j<=n){
            if(o[j]>a)c=b,b=a,a=o[j];
            else if(o[j]>b)c=b,b=o[j];
            else if(o[j]>c)c=o[j];
            j++;
        }
        if(!a&&!b&&!c)cout<<0<<endl;
        else{
            int cnt=3;
            if(!b)cnt--;
            if(!c)cnt--;
            for(int k=i;k<j;k++){
                if(o[k]==a)cout<<"pushStack\n",a=0;
                else if(o[k]==b)cout<<"pushQueue\n",b=0;
                else if(o[k]==c)cout<<"pushFront\n",c=0;
                else cout<<"pushBack\n";
            }
            if(j>n)break;
            cout<<cnt;
            for(int k=0;k<cnt;k++)
                cout<<" "<<p[k];
            cout<<endl;
            i=j;
        }
    }
```
核心实现思想：与流绪的代码类似，同样是利用循环寻找最值并根据最值分配压入操作，最后根据最值情况输出弹出操作。

### 最优关键思路或技巧
采用贪心策略，每次在两个0之间的数据中，找出最大的三个数分别放入栈、队列和双端队列（较大端），其余数放入双端队列（较小端），这样在遇到提取操作时能保证取出数字之和最大。

### 拓展思路
此类题目属于贪心策略结合数据结构应用的类型，相似套路为在特定数据结构操作规则下，通过贪心选择最优解。例如在一些任务调度问题中，根据任务的不同属性（如执行时间、优先级等），利用栈、队列等数据结构，采用贪心策略分配任务以达到最优目标。

### 洛谷相似题目推荐
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
 - [P1937 [USACO10MAR]Barn Allocation G](https://www.luogu.com.cn/problem/P1937) 

---
处理用时：53.73秒