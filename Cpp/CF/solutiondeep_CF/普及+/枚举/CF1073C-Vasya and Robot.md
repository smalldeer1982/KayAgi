# 题目信息

# Vasya and Robot

## 题目描述

Vasya has got a robot which is situated on an infinite Cartesian plane, initially in the cell $ (0, 0) $ . Robot can perform the following four kinds of operations:

- U — move from $ (x, y) $ to $ (x, y + 1) $ ;
- D — move from $ (x, y) $ to $ (x, y - 1) $ ;
- L — move from $ (x, y) $ to $ (x - 1, y) $ ;
- R — move from $ (x, y) $ to $ (x + 1, y) $ .

Vasya also has got a sequence of $ n $ operations. Vasya wants to modify this sequence so after performing it the robot will end up in $ (x, y) $ .

Vasya wants to change the sequence so the length of changed subsegment is minimum possible. This length can be calculated as follows: $ maxID - minID + 1 $ , where $ maxID $ is the maximum index of a changed operation, and $ minID $ is the minimum index of a changed operation. For example, if Vasya changes RRRRRRR to RLRRLRL, then the operations with indices $ 2 $ , $ 5 $ and $ 7 $ are changed, so the length of changed subsegment is $ 7 - 2 + 1 = 6 $ . Another example: if Vasya changes DDDD to DDRD, then the length of changed subsegment is $ 1 $ .

If there are no changes, then the length of changed subsegment is $ 0 $ . Changing an operation means replacing it with some operation (possibly the same); Vasya can't insert new operations into the sequence or remove them.

Help Vasya! Tell him the minimum length of subsegment that he needs to change so that the robot will go from $ (0, 0) $ to $ (x, y) $ , or tell him that it's impossible.

## 说明/提示

In the first example the sequence can be changed to LULUU. So the length of the changed subsegment is $ 3 - 1 + 1 = 3 $ .

In the second example the given sequence already leads the robot to $ (x, y) $ , so the length of the changed subsegment is $ 0 $ .

In the third example the robot can't end his path in the cell $ (x, y) $ .

## 样例 #1

### 输入

```
5
RURUU
-2 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
RULR
1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
UUU
100 100
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# Vasya和机器人

## 题目描述
Vasya有一个机器人，它位于无限的笛卡尔平面上，初始位置在单元格 (0, 0)。机器人可以执行以下四种操作：
- U — 从 (x, y) 移动到 (x, y + 1)；
- D — 从 (x, y) 移动到 (x, y - 1)；
- L — 从 (x, y) 移动到 (x - 1, y)；
- R — 从 (x, y) 移动到 (x + 1, y)。

Vasya还有一个包含n个操作的序列。Vasya想修改这个序列，使机器人在执行完该序列后最终到达 (x, y)。

Vasya希望修改的序列子段长度尽可能小。这个长度的计算方法如下：maxID - minID + 1，其中maxID是修改操作的最大索引，minID是修改操作的最小索引。例如，如果Vasya将RRRRRRR改为RLRRLRL，那么索引为2、5和7的操作被修改，所以修改子段的长度是7 - 2 + 1 = 6。另一个例子：如果Vasya将DDDD改为DDRD，那么修改子段的长度是1。

如果没有修改，那么修改子段的长度为0。修改一个操作意味着用某个操作替换它（可能是相同的操作）；Vasya不能在序列中插入新操作或删除操作。

请帮助Vasya！告诉他为了让机器人从 (0, 0) 移动到 (x, y)，他需要修改的子段的最小长度，或者告诉他这是不可能的。

## 说明/提示
在第一个例子中，序列可以改为LULUU。所以修改子段的长度是3 - 1 + 1 = 3。

在第二个例子中，给定的序列已经能使机器人到达 (x, y)，所以修改子段的长度是0。

在第三个例子中，机器人无法在单元格 (x, y) 结束它的路径。

## 样例 #1
### 输入
```
5
RURUU
-2 3
```
### 输出
```
3
```

## 样例 #2
### 输入
```
4
RULR
1 1
```
### 输出
```
0
```

## 样例 #3
### 输入
```
3
UUU
100 100
```
### 输出
```
-1
```

### 题解综合分析与结论
这些题解主要围绕二分答案 + 前缀和的思路来解决问题。思路上，利用二分答案的单调性，二分修改子段的长度，通过前缀和预处理快速计算除去修改子段后的机器人位置，再判断在该子段长度下能否通过修改操作使机器人到达目标点。

解决难点在于：
1. **发现单调性**：意识到若修改长度为l的子段可行，那么大于l的子段必然可行，从而确定可以二分答案。
2. **高效计算**：通过前缀和优化，避免每次都模拟计算除去修改子段后的位置，将时间复杂度从O(n^3)或O(n^2)降到O(nlogn)。

### 所选的题解
- **作者：yeshubo_qwq (5星)**
    - **关键亮点**：思路清晰，详细阐述了二分答案的原因及判断依据，对前缀和的使用及二分判断函数的实现解释到位。
    - **个人心得**：无
    - **核心代码**：
```cpp
l=0;r=n; 
ans=-1;
while(l<=r){
    mid=(l+r)>>1;
    if(check(mid))r=mid-1,ans=mid;
    else l=mid+1;
}
cout<<ans;
for(i=1;i<=n;i++){
    x[i]=x[i-1];y[i]=y[i-1];
    switch(s[i]){
        case 'U':y[i]++;break;
        case 'D':y[i]--;break;
        case 'L':x[i]--;break;
        case 'R':x[i]++;break;
    }
}
bool check(int l){
    int i,j,n2,m2,p;
    for(i=1,j=i+l-1;j<=n;i++,j++){
        n2=x[n]-x[j]+x[i-1];
        m2=y[n]-y[j]+y[i-1];
        p=abs(n1-n2)+abs(m1-m2);
        if(l==p)return true; 
        else if(l>p&&(l-p)%2==0)return true;
    }
    return false;
}
```
核心实现思想：先二分答案，在check函数中枚举长度为l的子段，通过前缀和计算除去该子段后的位置，再判断能否到达目标点。

- **作者：JMercury (4星)**
    - **关键亮点**：代码简洁明了，对二分答案和前缀和的实现清晰，对判断子段可行性的条件解释较清楚。
    - **个人心得**：考试没做出来表示遗憾。
    - **核心代码**：
```cpp
bool check(int len)
{
    for(int l=1,r=len;r<=n;l++,r++)
    {
        int nx=frtx[n]-(frtx[r]-frtx[l-1]);
        int ny=frty[n]-(frty[r]-frty[l-1]);
        if(len>=abs(x-nx)+abs(y-ny) && (len-abs(x-nx)-abs(y-ny))%2==0) return true;
    }
    return false;
}
l=0,r=n;
while(r>=l)
{
    mid=(l+r)>>1;
    if(check(mid)) r=mid-1,ans=mid;
    else l=mid+1;
}
printf("%d",ans);
```
核心实现思想：同样是二分答案，check函数通过前缀和计算子段外的位置，依据条件判断子段是否可行。

- **作者：CYZZ (4星)**
    - **关键亮点**：对题意和思路分析详细，代码结构清晰，对二分答案和前缀和的结合使用阐述较好。
    - **个人心得**：无
    - **核心代码**：
```cpp
bool check(int x)
{
    int l=1,r=x;
    while(r<=n)
    {
        int nx=sum[n][0]-sum[r][0]+sum[l-1][0];
        int ny=sum[n][1]-sum[r][1]+sum[l-1][1];
        int step=abs(nx-tx)+abs(ny-ty);
        if(x>=step&&!((x-step)&1))
            return 1;
        l++;r++;
    }
    return 0;
}
int l=0,r=n;
while(l<=r)
{
    int mid=(l+r)>>1;
    if(check(mid))
    {
        r=mid-1;
        flag=1;
    }
    else 
        l=mid+1;
}
printf("%d",flag?l:-1);
```
核心实现思想：二分答案，在check函数中遍历长度为x的子段，利用前缀和计算剩余位置，判断是否满足到达目标点的条件。

### 最优关键思路或技巧
1. **二分答案**：利用问题的单调性，通过二分查找修改子段的最小长度，减少搜索空间，降低时间复杂度。
2. **前缀和优化**：预处理操作序列，使得在计算除去修改子段后的机器人位置时能够在O(1)时间内完成，提高计算效率。

### 可拓展之处
同类型题或类似算法套路：这类题目通常涉及路径规划、序列修改并求最优值，可拓展到其他类似的移动规划问题，如在特定地图上移动并满足某些条件，通过二分答案和前缀和、差分等优化手段解决。

### 推荐洛谷题目
1. **P2678 [NOIP2015 提高组] 跳石头**：同样是二分答案的题目，通过二分最短跳跃距离，判断能否满足移除一定数量石头的条件。
2. **P1873 砍树**：利用二分查找合适的砍树高度，以满足收集到足够木材的需求，和本题二分思路类似。
3. **P3853 [TJOI2007] 路标设置**：通过二分答案确定路标间的最小距离，判断是否满足路标数量限制，与本题在二分应用上有相似之处。 

---
处理用时：38.03秒