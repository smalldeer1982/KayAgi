# 题目信息

# Andryusha and Socks

## 题目描述

Andryusha is an orderly boy and likes to keep things in their place.

Today he faced a problem to put his socks in the wardrobe. He has $ n $ distinct pairs of socks which are initially in a bag. The pairs are numbered from $ 1 $ to $ n $ . Andryusha wants to put paired socks together and put them in the wardrobe. He takes the socks one by one from the bag, and for each sock he looks whether the pair of this sock has been already took out of the bag, or not. If not (that means the pair of this sock is still in the bag), he puts the current socks on the table in front of him. Otherwise, he puts both socks from the pair to the wardrobe.

Andryusha remembers the order in which he took the socks from the bag. Can you tell him what is the maximum number of socks that were on the table at the same time?

## 说明/提示

In the first example Andryusha took a sock from the first pair and put it on the table. Then he took the next sock which is from the first pair as well, so he immediately puts both socks to the wardrobe. Thus, at most one sock was on the table at the same time.

In the second example Andryusha behaved as follows:

- Initially the table was empty, he took out a sock from pair $ 2 $ and put it on the table.
- Sock $ (2) $ was on the table. Andryusha took out a sock from pair $ 1 $ and put it on the table.
- Socks $ (1,2) $ were on the table. Andryusha took out a sock from pair $ 1 $ , and put this pair into the wardrobe.
- Sock $ (2) $ was on the table. Andryusha took out a sock from pair $ 3 $ and put it on the table.
- Socks $ (2,3) $ were on the table. Andryusha took out a sock from pair $ 2 $ , and put this pair into the wardrobe.
- Sock $ (3) $ was on the table. Andryusha took out a sock from pair $ 3 $ and put this pair into the wardrobe.

 Thus, at most two socks were on the table at the same time.

## 样例 #1

### 输入

```
1
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
2 1 1 3 2 3
```

### 输出

```
2
```

# AI分析结果

### 题目翻译
# Andryusha和袜子

## 题目描述
Andryusha是一个井井有条的男孩，喜欢把东西放在该放的地方。

今天他面临一个问题，要把他的袜子放进衣柜里。他有 $n$ 双不同的袜子，最初都放在一个袋子里。这些袜子的编号从 $1$ 到 $n$。Andryusha想把成对的袜子放在一起，然后放进衣柜。他从袋子里一只一只地拿出袜子，对于每只袜子，他会查看这只袜子的配对是否已经从袋子里拿出来了。如果没有（即这只袜子的配对还在袋子里），他就把当前这只袜子放在面前的桌子上。否则，他就把这双袜子都放进衣柜。

Andryusha记得他从袋子里拿出袜子的顺序。你能告诉他桌子上最多同时有多少只袜子吗？

## 说明/提示
在第一个样例中，Andryusha拿出了第一双袜子中的一只，放在了桌子上。然后他拿出了同一双中的另一只，于是他立刻把这两只袜子都放进了衣柜。因此，桌子上最多同时有一只袜子。

在第二个样例中，Andryusha的操作如下：
- 最初桌子是空的，他拿出了编号为 $2$ 的袜子，放在了桌子上。
- 桌子上有编号为 $(2)$ 的袜子。Andryusha拿出了编号为 $1$ 的袜子，放在了桌子上。
- 桌子上有编号为 $(1,2)$ 的袜子。Andryusha拿出了编号为 $1$ 的袜子，然后把这双袜子放进了衣柜。
- 桌子上有编号为 $(2)$ 的袜子。Andryusha拿出了编号为 $3$ 的袜子，放在了桌子上。
- 桌子上有编号为 $(2,3)$ 的袜子。Andryusha拿出了编号为 $2$ 的袜子，然后把这双袜子放进了衣柜。
- 桌子上有编号为 $(3)$ 的袜子。Andryusha拿出了编号为 $3$ 的袜子，然后把这双袜子放进了衣柜。

因此，桌子上最多同时有两只袜子。

## 样例 #1
### 输入
```
1
1 1
```
### 输出
```
1
```

## 样例 #2
### 输入
```
3
2 1 1 3 2 3
```
### 输出
```
2
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟Andryusha拿袜子的过程。通过一个数组记录每双袜子的出现次数，根据袜子是否配对来更新桌子上袜子的数量，同时记录桌子上袜子数量的最大值。

不同题解的差异主要在于代码实现的细节，如更新桌子上袜子数量的方式，有的是先加1再根据配对情况减2，有的是直接根据配对情况加1或减1。

### 所选的题解
- 作者：songxiao（赞：3），4星
  - 关键亮点：思路清晰，提供了两种实现方式，一种是朴素模拟，另一种是简化模拟，代码可读性高。
  - 个人心得：无

### 重点代码
```cpp
// 法一（朴素）
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],cnt,ans;
int main()
{
    cin>>n;
    for(int i=1;i<=2*n;i++)	//别忘了乘以2，因为n双有2*n只
    {
        int x;
        cin>>x;
        a[x]++;		//发现一只袜子，桌上就多一只相应种类的袜子
        cnt++;		//桌子上总袜子数增加（第一种）
        if(a[x]==2)	//同种袜子凑够两只，放入衣柜（第二种）
            cnt-=2;	//桌子上少掉两只
        ans=max(ans,cnt);//更新答案，取最多的
    }
    cout<<ans;
    return 0;
}

// 法二（简化）
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],cnt,ans;
int main()
{
    cin>>n;
    for(int i=1;i<=2*n;i++)	//别忘了乘以2，因为n双有2*n只
    {
        int x;
        cin>>x;
        a[x]++;		//发现一只袜子，桌上就多一只相应种类的袜子
        if(a[x]==2)	//第二种
            cnt--;	//桌子上共少一只
        else
            cnt++;	//第一种
        ans=max(ans,cnt);//更新答案，取最多的
    }
    cout<<ans;
    return 0;
}
```
**核心实现思想**：使用数组 `a` 记录每双袜子的出现次数，`cnt` 记录桌子上当前袜子的数量，`ans` 记录桌子上袜子数量的最大值。在每次取出袜子时，更新 `a` 数组和 `cnt` 的值，同时更新 `ans`。

### 可拓展之处
同类型题可能会有不同的规则变化，如袜子的配对规则改变，或者增加更多的操作步骤。类似的算法套路可以用于模拟其他具有顺序操作和状态更新的问题，如游戏模拟、事件处理等。

### 推荐题目
1. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
2. [P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098)
3. [P1161 开灯](https://www.luogu.com.cn/problem/P1161)

### 个人心得摘录与总结
部分作者认为这道题被评为绿题不合理，觉得难度应该更低，属于暴力模拟的水题。这反映出不同人对题目的难度感受可能存在差异。 

---
处理用时：36.33秒