# 题目信息

# Bulbs

## 题目描述

Vasya wants to turn on Christmas lights consisting of $ m $ bulbs. Initially, all bulbs are turned off. There are $ n $ buttons, each of them is connected to some set of bulbs. Vasya can press any of these buttons. When the button is pressed, it turns on all the bulbs it's connected to. Can Vasya light up all the bulbs?

If Vasya presses the button such that some bulbs connected to it are already turned on, they do not change their state, i.e. remain turned on.

## 说明/提示

In the first sample you can press each button once and turn on all the bulbs. In the 2 sample it is impossible to turn on the 3-rd lamp.

## 样例 #1

### 输入

```
3 4
2 1 4
3 1 3 1
1 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3 3
1 1
1 2
1 1
```

### 输出

```
NO
```

# AI分析结果

### 题目中文重写
# 灯泡

## 题目描述
Vasya 想要点亮由 $m$ 个灯泡组成的圣诞灯。初始时，所有灯泡都是关闭的。这里有 $n$ 个按钮，每个按钮都连接着一些灯泡。Vasya 可以按下任意一个按钮。当按下按钮时，它会点亮所有与之相连的灯泡。Vasya 能否点亮所有的灯泡呢？

如果 Vasya 按下的按钮所连接的某些灯泡已经点亮，那么这些灯泡的状态不会改变，即保持点亮状态。

## 说明/提示
在第一个样例中，你可以每个按钮都按一次，这样就能点亮所有的灯泡。在第二个样例中，不可能点亮第 3 个灯泡。

## 样例 #1
### 输入
```
3 4
2 1 4
3 1 3 1
1 2
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
3 3
1 1
1 2
1 1
```
### 输出
```
NO
```

### 算法分类
无算法分类

### 综合分析与结论
这些题解的核心思路都是利用数组来标记每个灯泡是否被按钮连接，以此判断能否点亮所有灯泡，本质上都是桶排思想的应用。
- **思路**：先初始化一个数组来表示灯泡的状态（未连接），接着读入每个按钮连接的灯泡信息，将对应灯泡标记为已连接，最后检查数组中是否有未被标记的灯泡，若有则输出 `NO`，否则输出 `YES`。
- **算法要点**：使用数组记录灯泡状态，通过循环读入数据并更新状态，最后遍历数组检查结果。
- **解决难点**：关键在于正确处理按钮与灯泡的对应关系，确保每个灯泡的状态被准确记录。

### 所选题解
- **作者：Ryan_Yu (赞：4)  4星**
    - **关键亮点**：思路清晰，代码简洁易懂，详细说明了每一步的操作。
- **作者：Terraria (赞：2)  4星**
    - **关键亮点**：简洁明了地阐述了桶排思想的应用，代码结构清晰。
- **作者：chenpengda (赞：0)  4星**
    - **关键亮点**：对题目中的关键条件进行了详细解读，有助于理解题意。

### 重点代码
```cpp
// Ryan_Yu的代码
#include<bits/stdc++.h>
using namespace std;
long long n,m,j,i,sum;bool flag[105]={false};
int main()
{
    cin>>n>>m;
    for(i=1;i<=n;i++)
    {
        cin>>sum;
        while(sum--)//由于是多行数据读入，sum减到0就会自动跳出
        {
            cin>>j;
            flag[j]=true;
        }
    }
    for(i=1;i<=m;i++)
    {
        if(flag[i]==false)
            {
                cout<<"NO"<<endl;
                return 0;
            }
    }
    cout<<"YES"<<endl;
    return 0;
}

// Terraria的代码
#include<bits/stdc++.h>
using namespace std;
bool f[10009];
int n,m;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        while(k--){
            int a;
            cin>>a;
            f[a]=true;
        }
    }
    for(int i=1;i<=m;i++){
        if(f[i]==false){
            cout<<"NO"<<endl;
            return 0;
        }
    }
    cout<<"YES"<<endl;
}

// chenpengda的代码
#include<bits/stdc++.h> 
using namespace std;
bool lian[105];//判断是否被连接 
int main()
{
    int n,m;
    cin>>n>>m;//RT。 
    for(int i=1;i<=n;i++)
    {
        //第i个按钮。
        int x;
        cin>>x;//连接灯泡的个数 
        int y;
        while(x--)
        {
            cin>>y;
            lian[y]=true; //这个灯泡被第i个开关连接上了 
        }
    }
    for(int i=1;i<=m;i++)
    {
        if(!lian[i])//如果没有被连接(lian[i]==0也可以) 
        {
            cout<<"NO";
            return 0;
        }
    }
    cout<<"YES";
} 
```
**核心实现思想**：使用布尔数组来记录每个灯泡的连接状态，初始化为 `false` 表示未连接。通过循环读入每个按钮连接的灯泡信息，将对应数组元素置为 `true` 表示已连接。最后遍历数组，若有元素为 `false` 则输出 `NO`，否则输出 `YES`。

### 最优关键思路或技巧
使用布尔数组作为桶来标记灯泡是否被连接，能高效地处理按钮与灯泡的对应关系，避免了复杂的数据结构和算法。

### 拓展思路
同类型题目可能会有更多的限制条件，如按钮有使用次数限制、灯泡有不同的状态（如闪烁、变色等），但核心思路仍然是记录和判断元素的状态。类似的算法套路可以应用于其他需要标记和检查元素状态的问题，如判断集合中的元素是否都被访问过等。

### 推荐题目
1. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
2. [P1427 小鱼的数字游戏](https://www.luogu.com.cn/problem/P1427)
3. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)

### 个人心得
- **chenpengda**：刚开始误解了题意，以为按下按钮会切换灯泡的开关状态，后来仔细读题才发现已点亮的灯泡状态不会改变，从而明确了解题思路。这提醒我们在做题时要仔细阅读题目条件，避免因理解错误而浪费时间。 

---
处理用时：37.80秒