# 题目信息

# Land Lot

## 题目描述

Vasya has a beautiful garden where wonderful fruit trees grow and yield fantastic harvest every year. But lately thieves started to sneak into the garden at nights and steal the fruit too often. Vasya can’t spend the nights in the garden and guard the fruit because there’s no house in the garden! Vasya had been saving in for some time and finally he decided to build the house. The rest is simple: he should choose in which part of the garden to build the house. In the evening he sat at his table and drew the garden’s plan. On the plan the garden is represented as a rectangular checkered field $ n×m $ in size divided into squares whose side length is 1. In some squares Vasya marked the trees growing there (one shouldn’t plant the trees too close to each other that’s why one square contains no more than one tree). Vasya wants to find a rectangular land lot $ a×b $ squares in size to build a house on, at that the land lot border should go along the lines of the grid that separates the squares. All the trees that grow on the building lot will have to be chopped off. Vasya loves his garden very much, so help him choose the building land lot location so that the number of chopped trees would be as little as possible.

## 说明/提示

In the second example the upper left square is (1,1) and the lower right is (3,2).

## 样例 #1

### 输入

```
2 2
1 0
1 1
1 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
4 5
0 0 1 0 1
0 1 1 1 0
1 0 1 0 1
1 1 1 1 1
2 3
```

### 输出

```
2
```

# AI分析结果

### 题目中文重写
# 土地地块

## 题目描述
瓦西亚有一个美丽的花园，那里生长着奇妙的果树，每年都能收获丰硕的果实。但最近，小偷们经常在夜间潜入花园偷水果。瓦西亚不能整夜待在花园里守护水果，因为花园里没有房子！瓦西亚攒了一段时间的钱，终于决定建一所房子。剩下的就很简单了：他应该选择在花园的哪个部分建房子。晚上，他坐在桌前，画出了花园的平面图。在平面图上，花园被表示为一个 $n×m$ 大小的矩形方格区域，被划分为边长为 1 的正方形。在一些正方形中，瓦西亚标记了生长在那里的树木（因为树木不能种得太近，所以一个正方形中最多只有一棵树）。瓦西亚想找到一块 $a×b$ 大小的矩形土地来建房子，并且土地的边界应该沿着分隔正方形的网格线。所有生长在建筑用地上的树木都必须砍掉。瓦西亚非常爱他的花园，所以请帮助他选择建筑用地的位置，使砍掉的树木数量尽可能少。

## 说明/提示
在第二个示例中，左上角的正方形是 (1,1)，右下角的是 (3,2)。

## 样例 #1
### 输入
```
2 2
1 0
1 1
1 1
```
### 输出
```
0
```

## 样例 #2
### 输入
```
4 5
0 0 1 0 1
0 1 1 1 0
1 0 1 0 1
1 1 1 1 1
2 3
```
### 输出
```
2
```

### 算法分类
前缀和

### 综合分析与结论
这些题解主要围绕在一个 $n×m$ 的矩阵中，找出面积为 $a×b$ 且包含 $1$ 的数量最少的子矩阵，关键在于考虑子矩阵横放和竖放两种情况。
- **思路对比**：部分题解采用暴力枚举子矩阵左上角的方法，通过四重循环计算子矩阵中 $1$ 的数量；部分题解使用二维前缀和预处理矩阵，再枚举右下角端点计算子矩阵中 $1$ 的数量。
- **算法要点**：暴力枚举法直接遍历所有可能的子矩阵，时间复杂度较高；二维前缀和法通过预处理矩阵，能快速计算子矩阵中 $1$ 的数量，时间复杂度较低。
- **解决难点**：所有题解都注意到了子矩阵横放和竖放的两种情况，避免了遗漏。

### 所选题解
- **亦枫（4星）**
    - **关键亮点**：思路清晰，使用二维前缀和预处理矩阵，代码简洁高效。
    - **个人心得**：无
- **ueettttuj（4星）**
    - **关键亮点**：详细解释了二维前缀和的原理，并配有图示，代码实现规范。
    - **个人心得**：无
- **hater（4星）**
    - **关键亮点**：指出了题目中 $a$ 和 $b$ 未明确长和宽的坑点，代码实现简洁。
    - **个人心得**：无

### 重点代码
#### 亦枫的代码
```cpp
#include<bits/stdc++.h>
#define rt return
#define f(i,a,b) for(register int i=a;i<=b;i++)
using namespace std;
int n,m,a,b,tmp,ans=0x7fffffff,tree[55][55],c[55][55];
int main() {
    scanf("%d %d",&n,&m);
    f(i,1,n)f(j,1,m)scanf("%d",&c[i][j]);
    f(i,1,n)f(j,1,m)tree[i][j]=c[i][j]+tree[i][j-1];//先处理出每行的前缀和 
    f(i,1,m)f(j,1,n)tree[j][i]=tree[j][i]+tree[j-1][i];//在每行依次相加得到二维前缀和 
    scanf("%d %d",&a,&b);
    f(i,a,n)f(j,b,m)tmp=tree[i][j]-tree[i-a][j]-tree[i][j-b]+tree[i-a][j-b],ans=min(ans,tmp);//a*b的情况，竖着放的矩阵 
    f(i,b,n)f(j,a,m)tmp=tree[i][j]-tree[i-b][j]-tree[i][j-a]+tree[i-b][j-a],ans=min(ans,tmp);//b*a的情况，横着放的矩阵 
    printf("%d",ans);
    rt 0;
}
```
**核心实现思想**：先处理每行的前缀和，再处理二维前缀和，最后枚举右下角端点，根据二维前缀和公式计算子矩阵中 $1$ 的数量，取最小值。

#### ueettttuj的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long mapp[51][51];
long long rec[51][51];
long long n,m,a,b;
long long ans;
int main(){
    scanf("%lld %lld",&n,&m);
    for(long long i=1;i<=n;i++){
        for(long long j=1;j<=m;j++){
            scanf("%lld",&mapp[i][j]);
        }
    }
    for(long long i=1;i<=n;i++){
        for(long long j=1;j<=m;j++){
            rec[i][j]=mapp[i][j]+rec[i][j-1];
        } 
    }
    for(long long i=1;i<=m;i++){
        for(long long j=1;j<=n;j++){
            rec[j][i]=rec[j][i]+rec[j-1][i];      //求二维前缀和(我写的比较麻烦) 
        }                                       
    }
    scanf("%lld %lld",&a,&b);
    ans=1000000007;
    for(long long i=1;i<=n;i++){
        for(long long j=1;j<=m;j++){
            long long anss;
            if(i>=a && j>=b){
                anss=rec[i][j]-rec[i-a][j]-rec[i][j-b]+rec[i-a][j-b]; //a*b的矩阵 
                if(anss<ans) ans=anss;
            }
            if(i>=b && j>=a){
                anss=rec[i][j]-rec[i-b][j]-rec[i][j-a]+rec[i-b][j-a];//b*a的矩阵 
                if(anss<ans) ans=anss;
            }
        }
    } 
    printf("%lld\n",ans);
    return 0;
}
```
**核心实现思想**：先读入矩阵，再计算二维前缀和，最后枚举所有可能的子矩阵，根据二维前缀和公式计算子矩阵中 $1$ 的数量，取最小值。

#### hater的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int Map[55][55],n,m,cnt[55][55],r,c,ans=0x7f7f7f7f;
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
      for(int j=1;j<=m;j++)
        cin>>Map[i][j];
    cin>>r>>c;
    for(int i=1;i<=n;i++)
      for(int j=1;j<=m;j++)
        cnt[i][j]=cnt[i-1][j]+cnt[i][j-1]-cnt[i-1][j-1]+Map[i][j];
    for(int i=r;i<=n;i++)
      for(int j=c;j<=m;j++)
        ans=min(ans,cnt[i][j]-cnt[i-r][j]-cnt[i][j-c]+cnt[i-r][j-c]);
    swap(r,c);
    for(int i=r;i<=n;i++)
      for(int j=c;j<=m;j++)
        ans=min(ans,cnt[i][j]-cnt[i-r][j]-cnt[i][j-c]+cnt[i-r][j-c]);
    cout<<ans<<endl;
    return 0;
} 
```
**核心实现思想**：先读入矩阵，再计算二维前缀和，然后枚举子矩阵，根据二维前缀和公式计算子矩阵中 $1$ 的数量，交换 $r$ 和 $c$ 后再枚举一次，取最小值。

### 最优关键思路或技巧
使用二维前缀和预处理矩阵，能在 $O(1)$ 时间内计算出子矩阵中 $1$ 的数量，大大降低了时间复杂度。同时，注意子矩阵横放和竖放的两种情况，避免遗漏。

### 可拓展之处
同类型题或类似算法套路：在矩阵中寻找满足特定条件的子矩阵问题，如求子矩阵的最大和、最小和等，都可以考虑使用二维前缀和来优化时间复杂度。

### 推荐题目
1. [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)
2. [P2004 领地选择](https://www.luogu.com.cn/problem/P2004)
3. [P3397 地毯](https://www.luogu.com.cn/problem/P3397)

### 个人心得摘录与总结
部分题解提到了题目中 $a$ 和 $b$ 未明确长和宽的坑点，提醒我们在做题时要仔细审题，考虑全面，避免遗漏情况。

---
处理用时：50.02秒