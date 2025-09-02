# 题目信息

# Robot's Task

## 题目描述

Robot Doc is located in the hall, with $ n $ computers stand in a line, numbered from left to right from $ 1 $ to $ n $ . Each computer contains exactly one piece of information, each of which Doc wants to get eventually. The computers are equipped with a security system, so to crack the $ i $ -th of them, the robot needs to collect at least $ a_{i} $ any pieces of information from the other computers. Doc can hack the computer only if he is right next to it.

The robot is assembled using modern technologies and can move along the line of computers in either of the two possible directions, but the change of direction requires a large amount of resources from Doc. Tell the minimum number of changes of direction, which the robot will have to make to collect all $ n $ parts of information if initially it is next to computer with number $ 1 $ .

It is guaranteed that there exists at least one sequence of the robot's actions, which leads to the collection of all information. Initially Doc doesn't have any pieces of information.

## 说明/提示

In the first sample you can assemble all the pieces of information in the optimal manner by assembling first the piece of information in the first computer, then in the third one, then change direction and move to the second one, and then, having 2 pieces of information, collect the last piece.

In the second sample to collect all the pieces of information in the optimal manner, Doc can go to the fourth computer and get the piece of information, then go to the fifth computer with one piece and get another one, then go to the second computer in the same manner, then to the third one and finally, to the first one. Changes of direction will take place before moving from the fifth to the second computer, then from the second to the third computer, then from the third to the first computer.

In the third sample the optimal order of collecting parts from computers can look like that: 1->3->4->6->2->5->7.

## 样例 #1

### 输入

```
3
0 2 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
4 2 3 0 1
```

### 输出

```
3
```

## 样例 #3

### 输入

```
7
0 3 1 0 5 2 6
```

### 输出

```
2
```

# AI分析结果

### 题目中文重写
# 机器人的任务

## 题目描述
机器人 Doc 位于一个大厅中，大厅里有 $n$ 台电脑排成一排，从左到右依次编号为 $1$ 到 $n$。每台电脑都包含一条信息，Doc 最终希望获取所有信息。这些电脑配备了安全系统，因此要破解第 $i$ 台电脑，机器人需要至少从其他电脑中收集 $a_{i}$ 条信息。只有当机器人紧邻某台电脑时，才能对其进行破解。

该机器人采用现代技术制造，可以沿着电脑排成的直线向两个方向移动，但改变移动方向需要消耗大量资源。请计算出机器人在初始位置紧邻编号为 $1$ 的电脑的情况下，收集所有 $n$ 条信息所需的最少方向改变次数。

保证至少存在一种机器人的行动序列，能够收集到所有信息。初始时，Doc 没有任何信息。

## 说明/提示
在第一个样例中，最优的信息收集方式是先收集第一台电脑中的信息，然后收集第三台电脑中的信息，接着改变方向移动到第二台电脑，此时已拥有 $2$ 条信息，最后收集最后一条信息。

在第二个样例中，为了以最优方式收集所有信息，Doc 可以先移动到第四台电脑获取信息，然后带着一条信息移动到第五台电脑获取另一条信息，接着以同样的方式移动到第二台电脑，再到第三台电脑，最后到第一台电脑。在从第五台电脑移动到第二台电脑、从第二台电脑移动到第三台电脑、从第三台电脑移动到第一台电脑之前会发生方向改变。

在第三个样例中，收集电脑信息的最优顺序可能是：$1 -> 3 -> 4 -> 6 -> 2 -> 5 -> 7$。

## 样例 #1
### 输入
```
3
0 2 0
```
### 输出
```
1
```

## 样例 #2
### 输入
```
5
4 2 3 0 1
```
### 输出
```
3
```

## 样例 #3
### 输入
```
7
0 3 1 0 5 2 6
```
### 输出
```
2
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟机器人在电脑间移动收集信息的过程，通过不断尝试黑掉满足条件的电脑，直到收集完所有信息，同时记录方向改变的次数。

各题解的思路和实现细节略有不同，但整体框架相似。Ptilopsis_w 的题解采用贪心策略，每次走到头，把能黑的电脑全黑掉；Edmundino、Hanghang、谷民、Otomachi_Una_ 和 Meteorshower_Y 的题解都是以一个回合（$1 - n - 1$）为一个循环，交替从前往后和从后往前扫描电脑，黑掉满足条件的电脑。

### 所选的题解
- **Ptilopsis_w（4星）**
    - **关键亮点**：思路清晰，采用贪心策略，代码实现简洁明了，注释详细。
    - **核心实现思想**：使用一个变量记录已黑掉的电脑数，一个变量记录方向，不断移动并判断是否可以黑掉当前电脑，若走出范围则改变方向。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int a[1005];
bool vis[1005];//记录电脑是否被黑过

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    int tot = 0, ans = 0, i = 1, way = 1;//黑的电脑数，回头次数，当前位置，方向
    while(tot < n)
    {
        if(i < 1 or i > n)//走出去了，说明需要回头
        {
            way *= -1;//回头
            i += way;//因为本来就走出去了所以走一步再回来
            ans++;//记录回头的次数
        }
        if(!vis[i] and a[i] <= tot)//符合条件且没被黑过
        {
            vis[i] = true;//黑掉
            tot++;//累计
        }
        i += way;//向当前方向走一步
    }
    printf("%d", ans);
    return 0;
}
```
- **Hanghang（4星）**
    - **关键亮点**：思路清晰，代码有详细注释，通过判断转弯次数的奇偶来决定扫描方向。
    - **核心实现思想**：使用一个变量记录已黑掉的电脑数，一个变量记录转弯次数，根据转弯次数的奇偶交替从前往后和从后往前扫描电脑，黑掉满足条件的电脑。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
//万能头大法号

int n,a[1003],s,k;
//n表示电脑数量，a数组每台电脑分别需要多少信息
//s表示当前已经黑的电脑数量，k表示转了多少次弯
bool v[1003];
//v数组表示当前这个电脑是否被黑过，0表示是，1表示否
int main()
{
    cin>>n;
   //读入n
    for(int i=1;i<=n;i++)cin>>a[i];
   //读入数组a
    while(s<n)
   //当前是否黑了所有电脑，没有的话就进入
    {
        if(k%2==0)
     //看是从前往后还是从后往前
        {
            for(int i=1;i<=n;i++)
        //循环
                if(a[i]<=s&&v[i]==0)s++,v[i]=1;
           //判断当前电脑是否可以黑
            if(s==n)
         //判断是否黑完了所有电脑
            {
                cout<<k<<endl;return 0;
           //直接输出走人
            }
        }
        else
        {
            for(int i=n;i>0;i--)
        //循环
                if(a[i]<=s&&v[i]==0)s++,v[i]=1;
            //判断当前电脑是否可以黑
            if(s>=n)
        //判断是否黑完了所有电脑
            {
                cout<<k<<endl;return 0;
           //直接输出走人
            }
        }
        k++;
     //转一次弯
    }
}
```
- **谷民（4星）**
    - **关键亮点**：思路清晰，代码简洁，通过判断转弯次数的奇偶来决定扫描方向。
    - **核心实现思想**：使用一个变量记录已黑掉的电脑数，一个变量记录转弯次数，根据转弯次数的奇偶交替从前往后和从后往前扫描电脑，黑掉满足条件的电脑。
    - **核心代码**：
```cpp
#include<stdio.h>
#include<string.h>
int n,a[1001],vis[1001];
int main()
{
    while(~scanf("%d",&n))
    {
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        int pre=0,ans=0;
        memset(vis,0,sizeof(vis));
        while(1)
        {
            if(ans%2==0)
            {
                for(int i=1;i<=n;i++)
                    if(!vis[i]&&a[i]<=pre)
                    {
                        vis[i]=1;
                        pre++;
                    }
            }
            else
            {
                for(int i=n;i>=1;i--)
                    if(!vis[i]&&a[i]<=pre)
                    {
                        vis[i]=1;
                        pre++;
                    }
            }
            if(pre==n)break;
            ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

### 最优关键思路或技巧
- **贪心策略**：每次都尽可能多地黑掉电脑，即走到头把能黑的全黑了，这样可以减少回头次数。
- **模拟过程**：通过交替从前往后和从后往前扫描电脑，黑掉满足条件的电脑，直到收集完所有信息。
- **标记数组**：使用标记数组记录电脑是否已被黑掉，避免重复操作。

### 拓展思路
同类型题或类似算法套路：
- 模拟机器人在地图上的移动，根据不同的条件进行操作，如收集物品、避开障碍物等。
- 模拟游戏角色的行动，根据不同的规则进行决策，如打怪升级、探索地图等。

### 推荐题目
- [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)
- [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067)
- [P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098)

### 个人心得摘录与总结
- **Meteorshower_Y**：提到 21 中考在即，发篇题解涨 Rp，希望大家有误提醒更正，体现了作者积极分享和学习的态度。 

---
处理用时：51.53秒