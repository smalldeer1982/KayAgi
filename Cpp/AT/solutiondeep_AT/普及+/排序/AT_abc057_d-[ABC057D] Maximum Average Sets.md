# 题目信息

# [ABC057D] Maximum Average Sets

## 题目描述

你有 $n$ 个物品，第 $i$ 个物品的价值为 $v_i$。
你需要从这些物品中选择 $A$ 个以上，$B$ 个以下的物品，计算出所选物品平均值的最大值，并求出能使选择物品的平均值最大的选择方法有几种。

## 说明/提示

#### 数据规模与约定
对于 $100\%$ 的测试点数据，保证：
- $1\le a\le b\le n\le50$
- $1\le v_i\le10^{15}$
- $v_i$ 全部为整数。

#### 样例 $1$ 解释
选择第 $4$ 个物品和第 $5$ 个物品，价值的平均值是最大的，所以第一行输出 $4.5$。另外，由于除此之外的物品的选择方法中没有价值平均值为 $4.5$ 的东西，所以第二行输出 $1$。

#### 样例 $2$ 解释
物品价值平均值最大的物品的选择方法可能有多个。

---
翻译：@[Wuzetong](https://www.luogu.com.cn/user/1219873)

## 样例 #1

### 输入

```
5 2 2

1 2 3 4 5```

### 输出

```
4.500000

1```

## 样例 #2

### 输入

```
4 2 3

10 20 10 10```

### 输出

```
15.000000

3```

## 样例 #3

### 输入

```
5 1 5

1000000000000000 999999999999999 999999999999998 999999999999997 999999999999996```

### 输出

```
1000000000000000.000000

1```

## 样例 #4

### 输入

```
50 1 50

1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1```

### 输出

```
1.000000

1125899906842623```

# AI分析结果

### 题目中文重写
你有 $n$ 个物品，第 $i$ 个物品的价值为 $v_i$。
你需要从这些物品中选择 $A$ 个以上，$B$ 个以下的物品，计算出所选物品平均值的最大值，并求出能使选择物品的平均值最大的选择方法有几种。

### 说明/提示
#### 数据规模与约定
对于 $100\%$ 的测试点数据，保证：
- $1\le a\le b\le n\le50$
- $1\le v_i\le10^{15}$
- $v_i$ 全部为整数。

#### 样例 $1$ 解释
选择第 $4$ 个物品和第 $5$ 个物品，价值的平均值是最大的，所以第一行输出 $4.5$。另外，由于除此之外的物品的选择方法中没有价值平均值为 $4.5$ 的东西，所以第二行输出 $1$。

#### 样例 $2$ 解释
物品价值平均值最大的物品的选择方法可能有多个。

### 综合分析与结论
这些题解大多采用贪心算法解决本题。思路要点为：先将物品按价值从大到小排序，选择前 $A$ 个物品可使平均值最大。对于方案数，关键在于处理“临界值”（前 $A$ 大的数中最小的），一般情况下方案数为从临界值总数中选临界值在前 $A$ 个数中个数的组合数；特殊情况是临界值和最大值相等时，方案数为从 $A$ 到 $B$ 选取临界值的组合数之和。

解决难点主要是对特殊情况的判断和组合数的计算。部分题解使用杨辉三角预处理组合数，避免了重复计算。

### 评分较高的题解
- **作者：jzzcjb（5星）**
    - **关键亮点**：思路清晰，代码简洁，对贪心策略和特殊情况的处理解释详细。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
int n,L,R,a[55],ans1,ans2,cnt1,cnt2;
bool cmp(int a,int b){return a>b;}
int C[55][55];
void init(){
    C[0][0]=1;
    for(int i=1;i<=50;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++)
            C[i][j]=C[i-1][j]+C[i-1][j-1];
    }
}
signed main(){
    init();
    cin>>n>>L>>R;
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=L;i++) ans1+=a[i];
    for(int i=1;i<=n;i++) if(a[i]==a[L]) cnt1++;
    for(int i=1;i<=L;i++) if(a[i]==a[L]) cnt2++;
    if(a[1]==a[L])
        for(int i=L;i<=R;i++) ans2+=C[cnt1][i];
    else ans2=C[cnt1][cnt2];
    printf("%lf\n%lld",(double)ans1/L,ans2);
}
```
核心实现思想：先预处理组合数，输入数据后将数组从大到小排序，计算前 $L$ 个数的和作为平均值的分子，统计临界值的总数和在前 $L$ 个数中的个数，根据是否为特殊情况计算方案数。

- **作者：ycy1124（4星）**
    - **关键亮点**：对贪心思路和方案数计算的解释较为详细，代码逻辑清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long w[51],work[51][51];
bool cmp(long long x1,long long x2){
    return x1>x2;
}
int main(){
    for(int i=1;i<=50;i++){
        work[i][0]=1;
        for(int j=1;j<=i;j++){
            work[i][j]=work[i-1][j-1]+work[i-1][j];
            if(i==j){
                work[i][j]=1;
            }
        }
    }
    long long n,a,b;
    scanf("%lld%lld%lld",&n,&a,&b);
    for(int i=1;i<=n;i++){
        scanf("%lld",&w[i]);
    }
    long long js=0;
    double ans;
    sort(w+1,w+n+1,cmp);
    int bj=51;
    for(int i=1;i<=a;i++){
        js+=w[i];
        if(w[i]==w[a]){
            bj=min(i,bj);
        }
    }
    ans=1.000000*js/a;
    printf("%.6lf\n",ans);
    long long ans2=0;
    if(w[a]==ans){
        int ww=0;
        for(int i=1;i<=n;i++){
            if(w[i]==w[a]){
                ww++;
            }
        }
        for(int i=a;i<=b;i++){
            ans2+=work[ww][i];
        }
        cout<<ans2;
        return 0;
    }
    for(int i=1;i<=n;i++){
        if(w[i]==w[a]){
            ans2++;
        }
    }
    cout<<work[ans2][a-bj+1];
    return 0;
}
```
核心实现思想：预处理组合数，输入数据并排序，计算前 $a$ 个数的和及平均值，记录最早出现的最小数位置，根据是否为特殊情况计算方案数。

- **作者：qi__（4星）**
    - **关键亮点**：不仅给出了本题的解法，还介绍了组合数的计算方法和 `sort` 函数的用法。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int c[51][51],n,a,b;
long long arr[51],avg=0.00,ans=0.00,cnt=0;
bool cmp(long long a,long long b){
    return a>b;
}
int main(){
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++)cin>>arr[i];
    sort(arr+1,arr+n+1,cmp);
    for(int i=1;i<=a;i++)ans+=arr[i];
    ans/=(double)(a);
    printf("%lf\n",ans);
    c[0][0]=1;
    for(int i=1;i<=50;i++){
        c[i][0]=1;
        for(int j=1;j<=i;j++)
            c[i][j]=c[i-1][j]+c[i-1][j-1];
    }
    int c1=0,c2=0;
    for(int i=1;i<=n;i++)if(arr[i]==arr[a])c1++;
    for(int i=1;i<=a;i++)if(arr[i]==arr[a])c2++;
    if(arr[1]==arr[a])
        for(int i=a;i<=b;i++)cnt+=c[c1][i];
    else
        cnt=c[c1][c2];
    cout<<cnt<<endl;
    return 0;
}
```
核心实现思想：输入数据并排序，计算前 $a$ 个数的平均值，预处理组合数，统计临界值的总数和在前 $a$ 个数中的个数，根据是否为特殊情况计算方案数。

### 最优关键思路或技巧
- **贪心策略**：选择价值最大的前 $A$ 个物品可使平均值最大。
- **组合数预处理**：使用杨辉三角（递推公式 $C^m_n = C^{m - 1}_{n - 1} + C^m_{n - 1}$）预处理组合数，避免重复计算。
- **特殊情况处理**：判断临界值和最大值是否相等，分别计算方案数。

### 可拓展之处
同类型题可能会改变数据范围、物品选择条件或增加其他限制。类似算法套路可用于解决其他贪心和组合数相关的问题，如背包问题变种、排列组合计数问题等。

### 推荐题目
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)

### 个人心得摘录与总结
- **作者：细数繁星**：在解题过程中因变量类型问题多次 WA，总结出不要开 `double` 和 `long double`，尽量把 `int` 换成 `long long`，可用宏定义提前转换。提醒在做题时要注意数据类型的选择，避免因类型问题导致错误。

---
处理用时：52.21秒