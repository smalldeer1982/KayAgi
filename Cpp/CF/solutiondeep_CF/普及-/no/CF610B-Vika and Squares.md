# 题目信息

# Vika and Squares

## 题目描述

Vika 有 $n$ 桶油漆，第 $i$ 桶有 $a_i$ 升油漆。

Vika 有一张无限长的长方形纸条，她将长方形纸条分成了无限个正方形，她将按照以下规则对正方形涂色。

- 涂一个正方形需要 $1$ 升油漆。
- 第一个正方形可以用第任意第 $i$ 桶油漆。
- 若第 $k$ 个正方形用了第 $x$ 桶油漆，则第 $k+1$ 个正方形将用第 $x+1$ 桶油漆，若 $x=n$，则第 $k+1$ 个正方形将用第 $1$ 桶油漆。若 $a_x = 0$ 则停止涂色。

求 Vika 最多可以涂多少个正方形。

## 样例 #1

### 输入

```
5
2 4 2 3 3
```

### 输出

```
12
```

## 样例 #2

### 输入

```
3
5 5 5
```

### 输出

```
15
```

## 样例 #3

### 输入

```
6
10 10 10 1 10 10
```

### 输出

```
11
```

# AI分析结果

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法。先找出所有油漆桶中油漆量的最小值 `minn`，因为每种油漆至少能涂 `minn` 次，所以至少能涂 `minn * n` 个正方形。然后，关键在于找到合适的起始位置，使得在涂完 `minn * n` 个正方形后，还能尽可能多地涂更多的正方形，也就是要找到两个最小数量油漆桶之间距离最大的地方作为起始点。

各题解的不同之处在于实现细节，有的通过复制数组来处理循环情况，有的直接在原数组上处理，还有的在计算间隔时采用不同的方式。

### 所选题解
- 作者：流绪 (赞：2)，4星。关键亮点：思路清晰，对特殊情况有详细说明，代码注释完善。
- 作者：sqh_let_it_be (赞：1)，4星。关键亮点：通过复制数组的方式，将循环情况在一个数组中呈现，便于理解和处理。
- 作者：一只大龙猫 (赞：1)，4星。关键亮点：对计算间隔的情况进行了分类讨论，逻辑清晰。

### 重点代码
#### 流绪的代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
using namespace std;
ll a[maxn];
int main()
{
    ios::sync_with_stdio(false);
    ll n;
    cin >> n;
    ll minn = inf,p=0;
    for(int i=1;i<=n;i++)
    {
        cin >> a[i];
        minn = min(minn,a[i]);//找到最小数量的颜色
    }
    int p1=0,p2=0;//记录第一个和最后一个最小数量的颜色
    for(int i=1;i<=n;i++)
    {
        if(a[i] == minn)
        {
            if(!p1)
                p1=i;
            p2=i;
            ll j=i+1;
            while(a[j]!=minn&&j<n)
                j++; //记录间隔
            p = max(p,j-i-1); //更新最大间隔
            i=j-1;
        }
    }
    p=max(n-p2+p1-1,p); //更新特殊情况的间隔
    cout << minn*n+p;
    return 0; 
}  
```
核心实现思想：先找出最小油漆量 `minn`，然后遍历数组记录第一个和最后一个最小油漆量的位置，计算相邻最小油漆量之间的间隔，最后更新特殊情况（循环情况）的间隔，答案为 `minn * n + 最大间隔`。

#### sqh_let_it_be 的代码
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
long long int n,a[400005],minn=1e9+9,sum;
bool xt=true;
inline long long int read()
{
    long long int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){s=s*10+ch-48;ch=getchar();}
    return s*w;
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
        a[i]=read();
        if(i!=1)
        {
            if(a[i]!=a[i-1])
              xt=false;
        }
        minn=min(a[i],minn);
    }
    if(xt==true)
    {
        cout<<n*minn;
        return 0;
    }
    sum+=n*minn;
    for(int i=n+1;i<=2*n;i++)
        a[i]=a[i-n];
    int l=-1,maxn=-1;
    for(int i=1;i<=2*n;i++)
    {
        if(a[i]==minn)
        {
            if(l==-1)
                l=i;
            else
            {
                maxn=max(i-l-1,maxn);
                l=i;
            }
        }
    }
    cout<<sum+maxn;
}
```
核心实现思想：先找出最小油漆量 `minn`，判断数组元素是否相同。若不同，将数组复制一份，遍历复制后的数组，计算相邻最小油漆量之间的间隔，答案为 `minn * n + 最大间隔`。

#### 一只大龙猫的代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
long long sum=-18e16,n,a[200001],minn=18e16,last;
int main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        if(a[i]<=minn){
            minn=a[i];
            last=i;
        }
    }                          
    for(int i=1;i<=n;i++){
        if(a[i]==minn){
            if(last>=i){
                sum=max(sum,(n-last)+(i-1));
            }else{
                sum=max(sum,i-last-1);
            }
            last=i;
        }
    }
    printf("%lld",sum+minn*n);
    return 0;
}
```
核心实现思想：先找出最小油漆量 `minn` 并记录其位置 `last`，然后遍历数组，根据 `last` 和当前位置 `i` 的大小关系计算间隔，更新最大间隔，答案为 `minn * n + 最大间隔`。

### 关键思路或技巧
- 利用贪心思想，先确定至少能涂的正方形数量 `minn * n`，再通过寻找最大间隔来增加可涂的正方形数量。
- 对于循环情况，可以通过复制数组或分类讨论的方式处理。

### 拓展思路
同类型题或类似算法套路：此类贪心问题通常需要先找出基础的解，再通过贪心策略寻找最优解。例如在环形数组中寻找最优起始点的问题，都可以考虑类似的思路。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：贪心算法，每次合并最小的两堆果子。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：贪心算法，让接水时间短的人先接水。
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)：贪心算法，按结束时间排序，选择不冲突的线段。

### 个人心得
- zgy_123：提醒变量要初始化，数组要开两倍，要使用 `long long` 类型，不要抄袭。
总结：在解题时要注意数据范围和变量初始化，避免因这些小问题导致错误。

---
处理用时：42.59秒