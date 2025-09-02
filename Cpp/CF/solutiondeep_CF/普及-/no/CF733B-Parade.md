# 题目信息

# Parade

## 题目描述

Very soon there will be a parade of victory over alien invaders in Berland. Unfortunately, all soldiers died in the war and now the army consists of entirely new recruits, many of whom do not even know from which leg they should begin to march. The civilian population also poorly understands from which leg recruits begin to march, so it is only important how many soldiers march in step.

There will be $ n $ columns participating in the parade, the $ i $ -th column consists of $ l_{i} $ soldiers, who start to march from left leg, and $ r_{i} $ soldiers, who start to march from right leg.

The beauty of the parade is calculated by the following formula: if $ L $ is the total number of soldiers on the parade who start to march from the left leg, and $ R $ is the total number of soldiers on the parade who start to march from the right leg, so the beauty will equal $ |L-R| $ .

No more than once you can choose one column and tell all the soldiers in this column to switch starting leg, i.e. everyone in this columns who starts the march from left leg will now start it from right leg, and vice versa. Formally, you can pick no more than one index $ i $ and swap values $ l_{i} $ and $ r_{i} $ .

Find the index of the column, such that switching the starting leg for soldiers in it will maximize the the beauty of the parade, or determine, that no such operation can increase the current beauty.

## 说明/提示

In the first example if you don't give the order to change the leg, the number of soldiers, who start to march from the left leg, would equal $ 5+8+10=23 $ , and from the right leg — $ 6+9+3=18 $ . In this case the beauty of the parade will equal $ |23-18|=5 $ .

If you give the order to change the leg to the third column, so the number of soldiers, who march from the left leg, will equal $ 5+8+3=16 $ , and who march from the right leg — $ 6+9+10=25 $ . In this case the beauty equals $ |16-25|=9 $ .

It is impossible to reach greater beauty by giving another orders. Thus, the maximum beauty that can be achieved is 9.

## 样例 #1

### 输入

```
3
5 6
8 9
10 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2
6 5
5 6
```

### 输出

```
1
```

## 样例 #3

### 输入

```
6
5 9
1 3
4 8
4 5
23 54
12 32
```

### 输出

```
0
```

# AI分析结果

### 题目翻译
# 游行

## 题目描述
很快，伯兰将举行一场战胜外星入侵者的胜利游行。不幸的是，所有士兵都在战争中牺牲了，现在军队完全由新兵组成，其中许多人甚至不知道应该从哪条腿开始行军。平民也不太清楚新兵从哪条腿开始行军，所以重要的是有多少士兵步伐一致。

游行将有 $n$ 个方阵参加，第 $i$ 个方阵中有 $l_{i}$ 名从左腿开始行军的士兵，以及 $r_{i}$ 名从右腿开始行军的士兵。

游行的美观度按以下公式计算：如果 $L$ 是游行中从左腿开始行军的士兵总数，$R$ 是从右腿开始行军的士兵总数，那么美观度等于 $|L - R|$。

你最多可以选择一个方阵，让这个方阵中的所有士兵换一下起始腿，即这个方阵中所有从左腿开始行军的士兵现在从右腿开始行军，反之亦然。形式上，你最多可以选择一个索引 $i$ 并交换 $l_{i}$ 和 $r_{i}$ 的值。

找出这样一个方阵的索引，使得改变这个方阵中士兵的起始腿能使游行的美观度最大化，或者确定没有这样的操作可以增加当前的美观度。

## 说明/提示
在第一个样例中，如果你不发出改变腿的命令，从左腿开始行军的士兵数量将是 $5 + 8 + 10 = 23$，从右腿开始行军的士兵数量将是 $6 + 9 + 3 = 18$。在这种情况下，游行的美观度将是 $|23 - 18| = 5$。

如果你命令第三个方阵改变腿，那么从左腿开始行军的士兵数量将是 $5 + 8 + 3 = 16$，从右腿开始行军的士兵数量将是 $6 + 9 + 10 = 25$。在这种情况下，美观度等于 $|16 - 25| = 9$。

通过发出其他命令不可能达到更高的美观度。因此，能达到的最大美观度是 9。

## 样例 #1
### 输入
```
3
5 6
8 9
10 3
```
### 输出
```
3
```

## 样例 #2
### 输入
```
2
6 5
5 6
```
### 输出
```
1
```

## 样例 #3
### 输入
```
6
5 9
1 3
4 8
4 5
23 54
12 32
```
### 输出
```
0
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心目标都是找出一个方阵，交换其左右腿行军士兵数量，使得游行美观度（即左右腿行军士兵总数差值的绝对值）最大。主要有两种思路：
- **数学推导法**：通过数学公式推导，找出 $a_i - b_i$ 和 $b_i - a_i$ 的最大值，比较交换后的美观度来确定答案。
- **暴力枚举法**：枚举每一个方阵，计算交换后的美观度，取最大值对应的方阵索引。

### 所选题解
- **N_z_（5星）**：
    - **关键亮点**：思路清晰，通过数学公式推导得出结论，代码简洁高效。
    - **个人心得**：无
- **Zhl2010（4星）**：
    - **关键亮点**：对思路进行了详细的证明，逻辑严谨，代码注释清晰。
    - **个人心得**：无
- **xiexinzhe（4星）**：
    - **关键亮点**：采用暴力枚举的方法，步骤清晰，代码可读性高。
    - **个人心得**：无

### 重点代码
#### N_z_ 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int nowl=0,nowr=0,n,nowlid=1,nowrid=1,suml=0,sumr=0;
    cin>>n;
    for(int x=1;x<=n;x++)
    {
        int y,z;
        cin>>y>>z;
        if(y>z&&y-z>=nowl)nowl=y-z,nowlid=x;
        if(y<z&&z-y>=nowr)nowr=z-y,nowrid=x;
        suml+=y;
        sumr+=z;
    }
    if(nowl*nowr==0)cout<<0<<endl;
    else if(abs(suml-sumr-2*nowl)>=abs(suml-sumr+2*nowr))cout<<nowlid;
    else cout<<nowrid;
}
```
**核心实现思想**：在输入时记录 $a_i - b_i$ 和 $b_i - a_i$ 的最大值及其对应的索引，最后比较交换后的美观度，输出对应的索引。

#### Zhl2010 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,r;
int x1=0,x2=0;
int a1,a2;
int ans1,ans2;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&l,&r);
        if(a1<l-r){
            a1=l-r,ans1=i;
        }if(a2<r-l){
            a2=r-l,ans2=i;
        }
        x1+=l,x2+=r;
    }
    if(abs(x1-x2-2*a1)>=abs(x1-x2+2*a2))cout<<ans1<<endl;
    else cout<<ans2<<endl;
    return 0;
}
```
**核心实现思想**：同样在输入时记录 $l - r$ 和 $r - l$ 的最大值及其对应的索引，最后比较交换后的美观度，输出对应的索引。

#### xiexinzhe 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int l[100001],r[100001];
int mx,mxid;
int main()
{
    int n;
    scanf("%d",&n);
    int ll=0,rr=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&l[i],&r[i]);
        ll+=l[i];
        rr+=r[i];
    }
    mx=abs(ll-rr);
    for(int i=1;i<=n;i++)
    {
        ll-=l[i];
        ll+=r[i];
        rr+=l[i];
        rr-=r[i];
        if(abs(ll-rr)>mx)
        {
            mx=abs(ll-rr);
            mxid=i;
        }
        ll+=l[i];
        ll-=r[i];
        rr-=l[i];
        rr+=r[i];
    }
    printf("%d\n",mxid);
    return 0;
}
```
**核心实现思想**：先计算初始的美观度，然后枚举每一个方阵，交换其左右腿行军士兵数量，计算交换后的美观度，更新最大值及其对应的索引。

### 最优关键思路或技巧
- **数学推导**：通过数学公式推导，可以减少不必要的枚举，提高效率。
- **打擂法**：在输入时记录最大值及其对应的索引，避免额外的遍历。

### 拓展思路
同类型题可以考虑增加限制条件，如可以交换多次、方阵有不同的权重等。类似算法套路可以应用于其他需要枚举或比较的问题，如数组元素交换、序列调整等。

### 推荐题目
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1181 数列分段 Section I](https://www.luogu.com.cn/problem/P1181)

### 个人心得摘录与总结
- **Andy_WA**：认为题目较简单，但自己还是卡了差不多十分钟，其中五分钟卡在测评上。总结：即使题目看似简单，也可能在测评等环节遇到问题，要注意细节。

---
处理用时：47.87秒