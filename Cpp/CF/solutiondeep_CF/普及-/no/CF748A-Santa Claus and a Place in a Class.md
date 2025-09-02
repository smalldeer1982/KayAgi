# 题目信息

# Santa Claus and a Place in a Class

## 题目描述

Santa Claus is the first who came to the Christmas Olympiad, and he is going to be the first to take his place at a desk! In the classroom there are $ n $ lanes of $ m $ desks each, and there are two working places at each of the desks. The lanes are numbered from $ 1 $ to $ n $ from the left to the right, the desks in a lane are numbered from $ 1 $ to $ m $ starting from the blackboard. Note that the lanes go perpendicularly to the blackboard, not along it (see picture).

The organizers numbered all the working places from $ 1 $ to $ 2nm $ . The places are numbered by lanes (i. e. all the places of the first lane go first, then all the places of the second lane, and so on), in a lane the places are numbered starting from the nearest to the blackboard (i. e. from the first desk in the lane), at each desk, the place on the left is numbered before the place on the right.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF748A/bbf8fc48769a6dddf0555cdcd0723e32248a57bd.png)The picture illustrates the first and the second samples.Santa Clause knows that his place has number $ k $ . Help him to determine at which lane at which desk he should sit, and whether his place is on the left or on the right!

## 说明/提示

The first and the second samples are shown on the picture. The green place corresponds to Santa Claus' place in the first example, the blue place corresponds to Santa Claus' place in the second example.

In the third sample there are two lanes with four desks in each, and Santa Claus has the fourth place. Thus, his place is in the first lane at the second desk on the right.

## 样例 #1

### 输入

```
4 3 9
```

### 输出

```
2 2 L
```

## 样例 #2

### 输入

```
4 3 24
```

### 输出

```
4 3 R
```

## 样例 #3

### 输入

```
2 4 4
```

### 输出

```
1 2 R
```

# AI分析结果

### 题目翻译
# 圣诞老人与教室座位

## 题目描述
圣诞老人是第一个来到圣诞奥林匹克竞赛现场的，他将第一个在课桌前就座！教室里有 $n$ 排，每排有 $m$ 张课桌，每张课桌有两个座位。排从左到右编号为 $1$ 到 $n$，每一排的课桌从黑板开始依次编号为 $1$ 到 $m$。请注意，排是垂直于黑板排列的，而不是沿着黑板排列（见图片）。

组织者将所有座位从 $1$ 到 $2nm$ 进行编号。座位按排编号（即第一排的所有座位先编号，然后是第二排的所有座位，依此类推），在每一排中，座位从离黑板最近的位置开始编号（即从该排的第一张课桌开始），在每张课桌上，左边的座位编号在右边的座位之前。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF748A/bbf8fc48769a6dddf0555cdcd0723e32248a57bd.png)
该图展示了第一个和第二个样例。圣诞老人知道他的座位编号是 $k$。请帮助他确定他应该坐在哪一排、哪一张课桌，以及他的座位是在左边还是右边！

## 说明/提示
第一个和第二个样例在图中展示。绿色座位对应第一个样例中圣诞老人的座位，蓝色座位对应第二个样例中圣诞老人的座位。

在第三个样例中，有两排，每排有四张课桌，圣诞老人的座位编号是 $4$。因此，他的座位在第一排的第二张课桌上，位于右边。

## 样例 #1
### 输入
```
4 3 9
```
### 输出
```
2 2 L
```

## 样例 #2
### 输入
```
4 3 24
```
### 输出
```
4 3 R
```

## 样例 #3
### 输入
```
2 4 4
```
### 输出
```
1 2 R
```

### 算法分类
模拟

### 综合分析与结论
这些题解主要围绕如何根据给定的座位编号 $k$ 来确定其在教室中的位置（排、课桌、左右）。思路主要分为两类：
1. **模拟枚举法**：通过三重循环依次模拟行、列和左右座位，逐个增加座位编号，直到找到与 $k$ 相等的编号，输出对应位置。
2. **数学推理法**：通过找规律，利用数学公式直接计算出座位所在的排、课桌和左右位置，避免了循环枚举。

### 所选题解
- **zplqwq（4星）**
    - **关键亮点**：思路清晰，通过找规律直接得出计算公式，代码简洁高效。
    - **个人心得**：无
- **4526_（4星）**
    - **关键亮点**：详细分析了从座位编号到桌子编号，再到行列数的推导过程，逻辑严谨。
    - **个人心得**：在推导行列数公式时，考虑到特殊情况并巧妙处理，避免了特判。
- **WNico（4星）**
    - **关键亮点**：代码简洁，对公式的运用熟练，通过简单的计算得出结果。
    - **个人心得**：无

### 重点代码
#### zplqwq
```c++
#include<bits/stdc++.h>
using namespace std;
int n,m,k;

int main()
{
    cin>>n>>m>>k;
    int ans=(k+1)/2-1;
    if(k%2==1)
    {
        cout<<ans/m+1<<" "<<ans%m+1<<" L"<<endl;
    }
    else
    {
        cout<<ans/m+1<<" "<<ans%m+1<<" R"<<endl;
    }
    return 0;
}
```
**核心实现思想**：先计算出桌子编号 `ans`，再根据 `k` 的奇偶性判断左右，输出对应位置。

#### 4526_
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

int n,m,k,pos;

int main(){
    scanf("%d %d %d",&n,&m,&k);
    pos=(k+1)/2-1;
    printf("%d %d ",pos/m+1,pos%m+1);
    if(k&1) printf("L");
    else printf("R");
    return 0;
}
```
**核心实现思想**：先计算桌子编号 `pos`，再根据 `pos` 计算行列数，最后根据 `k` 的奇偶性判断左右并输出。

#### WNico
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m>>k;
    int s=(k+1)/2;
    cout<<((s-1)/m+1)<<" "<<((s-1)%m)+1<<" "<<((k%2)?'L':'R');
    return 0;
}
```
**核心实现思想**：计算桌子编号 `s`，然后根据 `s` 计算行列数，根据 `k` 的奇偶性判断左右并输出。

### 最优关键思路或技巧
- 对于此类找位置的问题，可以先找规律，通过数学公式直接计算，避免使用复杂的循环枚举，提高效率。
- 在推导公式时，要考虑到特殊情况，如边界条件，确保公式的通用性。

### 可拓展之处
同类型题可能会改变座位的编号规则或教室的布局，解题思路仍然是先分析规律，再用数学公式或模拟的方法求解。类似算法套路包括在二维矩阵中根据编号找位置、根据位置找编号等问题。

### 推荐题目
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1427 小鱼的数字游戏](https://www.luogu.com.cn/problem/P1427)

### 个人心得摘录与总结
- **Mysterious_bird**：尝试用二维数组和 `vector` 模拟都失败了，最后采用三重循环直接查找编号，提醒我们在选择数据结构和算法时要根据题目特点进行尝试和调整。
- **Chtholly_L**：因之前模拟赛用二维数组爆零，所以否定了二维数组的方法，强调了要吸取过往经验教训，选择更合适的方法。
- **4526_**：在推导行列数公式时，遇到特殊情况，通过将错就错的方法解决，避免了特判，体现了在解决问题时要灵活思考。 

---
处理用时：45.75秒