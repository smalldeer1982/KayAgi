# 题目信息

# Photo to Remember

## 题目描述

One day $ n $ friends met at a party, they hadn't seen each other for a long time and so they decided to make a group photo together.

Simply speaking, the process of taking photos can be described as follows. On the photo, each photographed friend occupies a rectangle of pixels: the $ i $ -th of them occupies the rectangle of width $ w_{i} $ pixels and height $ h_{i} $ pixels. On the group photo everybody stands in a line, thus the minimum pixel size of the photo including all the photographed friends, is $ W×H $ , where $ W $ is the total sum of all widths and $ H $ is the maximum height of all the photographed friends.

As is usually the case, the friends made $ n $ photos — the $ j $ -th ( $ 1<=j<=n $ ) photo had everybody except for the $ j $ -th friend as he was the photographer.

Print the minimum size of each made photo in pixels.

## 样例 #1

### 输入

```
3
1 10
5 5
10 1
```

### 输出

```
75 110 60 ```

## 样例 #2

### 输入

```
3
2 1
1 2
2 1
```

### 输出

```
6 4 6 ```

# AI分析结果

### 题目翻译
#### 值得纪念的照片

### 题目描述
有一天，$n$ 个朋友相聚在一场聚会上。他们已经很久没有见面了，所以决定一起拍一张合影。

简单来说，拍照的过程可以描述如下。在照片中，每个被拍照的朋友占据一个像素矩形：第 $i$ 个人占据一个宽度为 $w_{i}$ 像素、高度为 $h_{i}$ 像素的矩形。在合影中，每个人站成一排，因此包含所有被拍照朋友的照片的最小像素尺寸为 $W×H$，其中 $W$ 是所有宽度的总和，$H$ 是所有被拍照朋友中的最大高度。

通常情况下，朋友们拍了 $n$ 张照片——第 $j$ （$1\leq j\leq n$）张照片中除了第 $j$ 个朋友，因为他是摄影师。

请输出每张照片的最小像素尺寸。

### 样例 #1
#### 输入
```
3
1 10
5 5
10 1
```
#### 输出
```
75 110 60
```

### 样例 #2
#### 输入
```
3
2 1
1 2
2 1
```
#### 输出
```
6 4 6
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟整个拍照的过程，先计算所有人的总宽度和最高、第二高的人的高度，然后依次去掉每个人，根据去掉的人是否为最高的人来计算相应照片的最小面积。

不同题解的差异主要体现在实现细节和优化方式上。部分题解使用排序来找到最高和第二高的人，部分题解则通过一次遍历直接记录最高和第二高的人，避免了排序的时间复杂度。

### 所选题解
- **zplqwq（4星）**
    - **关键亮点**：思路清晰，代码简洁，直接通过一次遍历记录最高和第二高的人的高度，避免了排序的开销。
    - **个人心得**：作者在题解中分享了小学毕业时的感慨，提到拍毕业照可以参考这道题，呼吁珍惜当下。
- **封禁用户（4星）**
    - **关键亮点**：使用结构体存储每个人的宽和高，通过排序来找到最高和第二高的人，代码逻辑清晰，使用三目运算符简化输出。
- **WanderingTrader（4星）**
    - **关键亮点**：详细解释了维护两个最大值的思路，并且考虑了有两个相同最大值的情况，代码有详细的注释。

### 重点代码
#### zplqwq的核心代码
```c++
#include<bits/stdc++.h> 
using namespace std;
const int N=1000010;
int n,cnt,ret;
int a[N],b[N],sum;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i]>>b[i];
        if(b[i]>cnt)
        {
            ret=cnt;
            cnt=b[i];
        }
        else if(b[i]>ret)
        {
            ret=b[i];
        }
        sum+=a[i];
    }
    for(int i=1;i<=n;i++)
    {
        if(b[i]==cnt)
        {
            cout<<ret*(sum-a[i])<<" ";
        }
        else
        {
            cout<<cnt*(sum-a[i])<<" ";
        }
    }
    return 0;
}
```
**核心实现思想**：通过一次遍历，记录最高和第二高的人的高度，同时累加所有人的宽度。然后再次遍历，根据去掉的人是否为最高的人来计算相应照片的最小面积。

#### 封禁用户的核心代码
```cpp
struct people{   
    int w,h;
}a[200001],b[200001];   
bool cmp(people x,people y)   
{
    return x.h>y.h;
}
int main()
{
    int n;   
    int sw=0;   
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].w>>a[i].h;
        b[i].w=a[i].w,b[i].h=a[i].h;   
        sw+=a[i].w;   
    }
    sort(a+1,a+1+n,cmp);   
    for(int i=1;i<=n;i++)
    {
        cout<<(b[i].h==a[1].h? a[2].h*(sw-b[i].w):a[1].h*(sw-b[i].w))<<" ";    
    }
    return 0;   
}
```
**核心实现思想**：使用结构体存储每个人的宽和高，通过排序来找到最高和第二高的人，然后根据去掉的人是否为最高的人来计算相应照片的最小面积。

#### WanderingTrader的核心代码
```cpp
int max1=INT_MIN,max2=max1;
for(int i=1;i<=n;++i)
{
    if(h[i] > max2) max2 = h[i];
    if(max2 > max1) swap(max2,max1);
}
int sum=0;
for(int i=1;i<=n;++i)
    sum+=w[i];
for(int i=1;i<=n;++i)
{
    int length = (h[i]==max1?max2:max1);
    int width = sum-w[i];
    int ans = length*width;
    printf("%d ",ans);
}
```
**核心实现思想**：通过一次遍历维护两个最大值，同时累加所有人的宽度。然后再次遍历，根据去掉的人是否为最高的人来计算相应照片的最小面积。

### 最优关键思路或技巧
- 一次遍历记录最高和第二高的人的高度，避免了排序的时间复杂度，时间复杂度为 $O(n)$。
- 处理有两个相同最大值的情况，确保结果的正确性。

### 可拓展之处
同类型的题目可能会有更多的限制条件，例如增加人数、增加照片的排列方式等。类似的算法套路可以用于处理需要记录最大值和次大值的问题，例如在一些统计问题中，需要找出最大和次大的数值。

### 推荐洛谷题目
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)
- [P1161 开灯](https://www.luogu.com.cn/problem/P1161)

---
处理用时：35.10秒