# 题目信息

# Balloons

## 题目描述

There are quite a lot of ways to have fun with inflatable balloons. For example, you can fill them with water and see what happens.

Grigory and Andrew have the same opinion. So, once upon a time, they went to the shop and bought $ n $ packets with inflatable balloons, where $ i $ -th of them has exactly $ a_i $ balloons inside.

They want to divide the balloons among themselves. In addition, there are several conditions to hold:

- Do not rip the packets (both Grigory and Andrew should get unbroken packets);
- Distribute all packets (every packet should be given to someone);
- Give both Grigory and Andrew at least one packet;
- To provide more fun, the total number of balloons in Grigory's packets should not be equal to the total number of balloons in Andrew's packets.

Help them to divide the balloons or determine that it's impossible under these conditions.

## 说明/提示

In the first test Grigory gets $ 3 $ balloons in total while Andrey gets $ 1 $ .

In the second test there's only one way to divide the packets which leads to equal numbers of balloons.

In the third test one of the boys won't get a packet at all.

## 样例 #1

### 输入

```
3
1 2 1
```

### 输出

```
2
1 2
```

## 样例 #2

### 输入

```
2
5 5
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
1
10
```

### 输出

```
-1
```

# AI分析结果

### 题目翻译
# 气球

## 题目描述
有很多种玩充气气球的有趣方式。例如，你可以给它们装满水，然后看看会发生什么。

格里戈里和安德鲁也有同样的想法。所以，从前，他们去商店买了 $n$ 包充气气球，其中第 $i$ 包里面正好有 $a_i$ 个气球。

他们想把气球分给彼此。此外，还需要满足以下几个条件：
- 不能撕开包装（格里戈里和安德鲁都应该得到完整的包装）；
- 分配所有的包装（每个包装都应该分给某个人）；
- 给格里戈里和安德鲁至少各一个包装；
- 为了更有趣，格里戈里的包装中的气球总数不应等于安德鲁的包装中的气球总数。

帮助他们分配气球，或者确定在这些条件下无法分配。

## 说明/提示
在第一个测试中，格里戈里总共得到 3 个气球，而安德烈得到 1 个。
在第二个测试中，只有一种分配包装的方式，这会导致气球数量相等。
在第三个测试中，其中一个男孩根本得不到包装。

## 样例 #1
### 输入
```
3
1 2 1
```
### 输出
```
2
1 2
```

## 样例 #2
### 输入
```
2
5 5
```
### 输出
```
-1
```

## 样例 #3
### 输入
```
1
10
```
### 输出
```
-1
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是先处理特殊情况，当 $n = 1$ 或 $n = 2$ 且两包气球数量相等时无法分配，输出 -1。对于其他情况，采用贪心策略，将装有最少气球的一包分给一个人，其余的分给另一个人，以此保证两人气球总数不同。

各题解的区别主要在于实现方式，有的使用排序找最小值及其编号，有的边输入边记录最小值及其编号。

### 所选的题解
- sheeplittlecloud（4星）
  - 关键亮点：思路清晰，代码简洁，先复制数组方便查找最小值的原始位置，然后排序找到最小值，再遍历原数组确定其编号。
- LLGZ（4星）
  - 关键亮点：使用结构体存储每包气球的数量和编号，通过自定义比较函数排序，逻辑清晰。
- 清清老大（4星）
  - 关键亮点：边输入边处理，每次发现最小值时更新最小值和编号，减少了额外的遍历操作。

### 重点代码
#### sheeplittlecloud
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,a[1001],b[1001];
int main()
{
    int i,j;
    cin>>n;
    for(i=1;i<=n;i++) cin>>a[i];
    if(n==1||(n==2&&a[1]==a[2]))
    {
        cout<<-1;
        return 0;
    }
    for(i=1;i<=n;i++) b[i]=a[i];
    sort(a+1,a+n+1);
    for(i=1;i<=n;i++)
        if(a[1]==b[i]) 
            break;
    cout<<1<<endl<<i;
    return 0;
}
```
核心实现思想：先复制数组，对复制后的数组排序找到最小值，再在原数组中查找最小值的位置。

#### LLGZ
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
    int s,i;
}a[10010];
bool cmp(node x,node y)
{
    return x.s<y.s;
}
int n;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].s;
        a[i].i=i;
    }
    if(n==1)
        cout<<-1;
    else if(n==2&&(a[1].s==a[2].s))
        cout<<-1;
    else
    {
        sort(a+1,a+1+n,cmp);
        cout<<"1"<<endl;
        cout<<a[1].i;
    }
    return 0;
}
```
核心实现思想：使用结构体存储每包气球的数量和编号，通过自定义比较函数排序，直接输出排序后第一个元素的编号。

#### 清清老大
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,a,mina = 302986,minaid;
    cin >> n;
    if(n == 1)
    {
        cout << -1;
        return 0;
    }
    if(n == 2)
    {
        int a2;
        cin >> a >> a2;
        if(a == a2)
        {
            cout << -1;
            return 0;
        }
        else
        {
            cout << 1 << endl << 1;
            return 0;
        }
    }
    for(int i = 1;i <= n;i ++)
    {
        cin >> a;
        if(a < mina)
        {
            mina = a;
            minaid = i;
        }
    }
    cout << "1\n" << minaid;
}
```
核心实现思想：边输入边记录最小值及其编号，减少了排序和额外的遍历操作。

### 可拓展之处
同类型题可能会增加更多的限制条件，如要求输出所有满足条件的分配方案，或者对气球的分配有其他的规则。类似的算法套路可以应用在资源分配问题中，通过贪心策略找到满足条件的最优解。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：同样使用贪心策略解决资源合并问题。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：通过排序和贪心思想来优化排队顺序。
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)：使用贪心算法解决区间覆盖问题。

### 个人心得
题解中未包含个人心得。

---
处理用时：41.57秒