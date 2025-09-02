# 题目信息

# Saitama Destroys Hotel

## 题目描述

Saitama accidentally destroyed a hotel again. To repay the hotel company, Genos has volunteered to operate an elevator in one of its other hotels. The elevator is special — it starts on the top floor, can only move down, and has infinite capacity. Floors are numbered from $ 0 $ to $ s $ and elevator initially starts on floor $ s $ at time $ 0 $ .

The elevator takes exactly $ 1 $ second to move down exactly $ 1 $ floor and negligible time to pick up passengers. Genos is given a list detailing when and on which floor passengers arrive. Please determine how long in seconds it will take Genos to bring all passengers to floor $ 0 $ .

## 说明/提示

In the first sample, it takes at least $ 11 $ seconds to bring all passengers to floor $ 0 $ . Here is how this could be done:

1\. Move to floor $ 5 $ : takes $ 2 $ seconds.

2\. Pick up passenger $ 3 $ .

3\. Move to floor $ 3 $ : takes $ 2 $ seconds.

4\. Wait for passenger $ 2 $ to arrive: takes $ 4 $ seconds.

5\. Pick up passenger $ 2 $ .

6\. Go to floor $ 2 $ : takes $ 1 $ second.

7\. Pick up passenger $ 1 $ .

8\. Go to floor $ 0 $ : takes $ 2 $ seconds.

This gives a total of $ 2+2+4+1+2=11 $ seconds.

## 样例 #1

### 输入

```
3 7
2 1
3 8
5 2
```

### 输出

```
11
```

## 样例 #2

### 输入

```
5 10
2 77
3 33
8 21
9 12
10 64
```

### 输出

```
79
```

# AI分析结果

### 题目内容中文重写
# 埼玉摧毁酒店

## 题目描述
埼玉又不小心摧毁了一家酒店。为了赔偿酒店公司，杰诺斯自愿在该公司的另一家酒店操作电梯。这部电梯很特殊——它从顶层开始，只能向下移动，并且有无限的容量。楼层编号从 $0$ 到 $s$，电梯最初在时间 $0$ 时位于 $s$ 层。

电梯每向下移动 $1$ 层恰好需要 $1$ 秒，搭载乘客的时间忽略不计。杰诺斯得到了一份详细的列表，列出了乘客何时以及在哪个楼层到达。请确定杰诺斯将所有乘客带到 $0$ 层需要多少秒。

## 说明/提示
在第一个样例中，至少需要 $11$ 秒才能将所有乘客带到 $0$ 层。以下是一种可行的做法：
1. 移动到 $5$ 层：需要 $2$ 秒。
2. 搭载乘客 $3$。
3. 移动到 $3$ 层：需要 $2$ 秒。
4. 等待乘客 $2$ 到达：需要 $4$ 秒。
5. 搭载乘客 $2$。
6. 前往 $2$ 层：需要 $1$ 秒。
7. 搭载乘客 $1$。
8. 前往 $0$ 层：需要 $2$ 秒。

这样总共需要 $2 + 2 + 4 + 1 + 2 = 11$ 秒。

## 样例 #1
### 输入
```
3 7
2 1
3 8
5 2
```
### 输出
```
11
```

## 样例 #2
### 输入
```
5 10
2 77
3 33
8 21
9 12
10 64
```
### 输出
```
79
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟电梯从顶层向下移动的过程，在遇到有乘客的楼层时，需要考虑等待最后一个乘客到达的时间。各题解的主要区别在于实现细节和数据处理方式。
- **思路**：大部分题解都是先记录每个楼层最晚到达的乘客时间，然后从顶层开始向下模拟电梯的移动过程，在每层楼比较当前时间和该楼层最晚乘客到达时间，取较大值更新当前时间。
- **算法要点**：需要对乘客信息进行排序或记录每个楼层的最晚到达时间，模拟电梯的移动过程，注意时间的更新。
- **解决难点**：关键在于处理电梯等待乘客的时间，确保在每层楼都等到最后一个乘客到达后再继续向下移动。

### 所选题解
- **Grisses（5星）**
    - **关键亮点**：思路清晰，代码简洁，通过结构体对乘客信息按楼层从大到小排序，模拟过程直观。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,s,ans,cnt=1;
struct node{
    int a,t;
    bool operator<(const node &b)const{
        return a>b.a;//按楼层从大到小排序
    }
}a[105];
signed main()
{
    scanf("%lld%lld",&n,&s);
    for(int i=1;i<=n;i++)scanf("%lld%lld",&a[i].a,&a[i].t);
    sort(a+1,a+n+1);
    for(int i=s;i>=0;i--,ans++){
        while(i==a[cnt].a){
            ans=max(ans,a[cnt].t);
            cnt++;//模拟
        }
    }
    printf("%lld",ans-1);
    return 0;
}
```
核心实现思想：先读取输入的乘客信息并按楼层从大到小排序，然后从顶层开始向下遍历楼层，遇到有乘客的楼层就更新当前时间为当前时间和该乘客到达时间的较大值。

- **Jr_Zlw（4星）**
    - **关键亮点**：详细解释了模拟过程，通过数组记录每个楼层最晚到达的乘客时间，逻辑清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[1001]; 
int main()
{
    int n,s;
    cin>>n>>s;
    int ans=s,t=0;
    for(int i=1;i<=n;++i)
    {
        int a,b;
        cin>>a>>b;
        f[a]=max(f[a],b);
    }//输入并标记
    for(int i=s;i>=0;--i)
    {
        if(f[i]>t)
        {
            ans+=(f[i]-t);//加上多余的时间
            t=f[i];//刷新时间值
        }
        t++;//电梯的正常运营时间
    }
    cout<<ans;
    return 0;
}
```
核心实现思想：先读取输入，记录每个楼层最晚到达的乘客时间，然后从顶层开始向下遍历楼层，比较当前时间和该楼层最晚乘客到达时间，若乘客还未到则更新时间和总时间。

- **WA_sir（4星）**
    - **关键亮点**：简洁明了地阐述了题目的关键点，代码实现简洁高效。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,a[1005],t;
int main()
{
    scanf("%d%d",&n,&s);
    for(int i=1;i<=n;i++)
    {
        int ax,ay;
        scanf("%d%d",&ax,&ay);
        a[ax]=max(a[ax],ay);//每层楼乘客所到时间最大值
    }
    for(int i=s;i;i--,t++)t=max(t,a[i]);//模拟
    printf("%d",t);
    return 0;
}
```
核心实现思想：先读取输入，记录每个楼层最晚到达的乘客时间，然后从顶层开始向下遍历楼层，更新当前时间为当前时间和该楼层最晚乘客到达时间的较大值。

### 最优关键思路或技巧
- 使用结构体或数组记录每个楼层最晚到达的乘客时间，方便后续模拟过程中进行比较。
- 对乘客信息按楼层从大到小排序，确保模拟过程按顺序进行。
- 在模拟电梯移动过程中，每次更新当前时间为当前时间和该楼层最晚乘客到达时间的较大值，保证电梯在每层楼都等到最后一个乘客到达。

### 可拓展之处
同类型题可能会有更多的限制条件，如电梯有容量限制、电梯可以向上移动等。类似算法套路就是模拟实际场景的过程，根据不同的规则和条件进行状态更新。

### 推荐洛谷题目
- P1042 乒乓球
- P1067 多项式输出
- P1098 字符串的展开

### 个人心得
无

---
处理用时：39.23秒