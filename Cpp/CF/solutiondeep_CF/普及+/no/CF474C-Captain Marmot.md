# 题目信息

# Captain Marmot

## 题目描述

Captain Marmot wants to prepare a huge and important battle against his enemy, Captain Snake. For this battle he has $ n $ regiments, each consisting of $ 4 $ moles.

Initially, each mole $ i $ ( $ 1<=i<=4n $ ) is placed at some position $ (x_{i},y_{i}) $ in the Cartesian plane. Captain Marmot wants to move some moles to make the regiments compact, if it's possible.

Each mole $ i $ has a home placed at the position $ (a_{i},b_{i}) $ . Moving this mole one time means rotating his position point $ (x_{i},y_{i}) $ $ 90 $ degrees counter-clockwise around it's home point $ (a_{i},b_{i}) $ .

A regiment is compact only if the position points of the $ 4 $ moles form a square with non-zero area.

Help Captain Marmot to find out for each regiment the minimal number of moves required to make that regiment compact, if it's possible.

## 说明/提示

In the first regiment we can move once the second or the third mole.

We can't make the second regiment compact.

In the third regiment, from the last $ 3 $ moles we can move once one and twice another one.

In the fourth regiment, we can move twice the first mole and once the third mole.

## 样例 #1

### 输入

```
4
1 1 0 0
-1 1 0 0
-1 1 0 0
1 -1 0 0
1 1 0 0
-2 1 0 0
-1 1 0 0
1 -1 0 0
1 1 0 0
-1 1 0 0
-1 1 0 0
-1 1 0 0
2 2 0 1
-1 0 0 -2
3 0 0 -2
-1 1 -2 0
```

### 输出

```
1
-1
3
3
```

# AI分析结果

### 题目内容
# 土拨鼠队长

## 题目描述
土拨鼠队长想要筹备一场对抗他的敌人——蛇队长的大型重要战役。为了这场战役，他有 $n$ 个团，每个团由 $4$ 只鼹鼠组成。

最初，每只鼹鼠 $i$（$1\leq i\leq 4n$）被放置在笛卡尔平面上的某个位置 $(x_{i},y_{i})$ 。土拨鼠队长希望移动一些鼹鼠，使各个团变得紧凑（如果可能的话）。

每只鼹鼠 $i$ 都有一个家，位于位置 $(a_{i},b_{i})$ 。移动这只鼹鼠一次意味着将它的位置点 $(x_{i},y_{i})$ 绕它的家点 $(a_{i},b_{i})$ 逆时针旋转 $90$ 度。

一个团紧凑的条件是，$4$ 只鼹鼠的位置点形成一个面积非零的正方形。

帮助土拨鼠队长找出每个团若要变得紧凑所需的最少移动次数（如果可能的话）。

## 说明/提示
在第一个团中，我们可以移动第二只或第三只鼹鼠一次。
我们无法使第二个团紧凑。
在第三个团中，从最后 $3$ 只鼹鼠里，我们可以移动其中一只一次，另一只两次。
在第四个团中，我们可以移动第一只鼹鼠两次，第三只鼹鼠一次。

## 样例 #1
### 输入
```
4
1 1 0 0
-1 1 0 0
-1 1 0 0
1 -1 0 0
1 1 0 0
-2 1 0 0
-1 1 0 0
1 -1 0 0
1 1 0 0
-1 1 0 0
-1 1 0 0
-1 1 0 0
2 2 0 1
-1 0 0 -2
3 0 0 -2
-1 1 -2 0
```
### 输出
```
1
-1
3
3
```

### 算法分类
枚举

### 综合分析与结论
三道题解思路相近，均利用数据范围小的特点采用枚举法解题。先预处理出每个鼹鼠旋转不同次数后的坐标，再枚举每个鼹鼠的旋转次数，判断这四个点能否构成正方形，记录最小移动次数。判断正方形的难点在于避免精度问题，均采用计算距离平方并比较的方式，同时要注意边长不能为0。

### 所选的题解
- **QQH08（5星）**
    - **关键亮点**：代码简洁，逻辑清晰，预处理和枚举过程实现流畅，直接利用循环和数组操作完成任务。
    - **个人心得**：认为本题暴力做法较繁琐。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=105;
int n;
ll x[N*4],y[N*4],p[10];
ll pf(ll x){return x*x;}
ll calc(int a,int b){
    return pf(x[a]-x[b])+pf(y[a]-y[b]);
}
int main(){
    scanf("%d",&n);
    for(int T=1;T<=n;T++){
        for(int i=0;i<4;i++){
            ll a,b,c,d;
            scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
            a-=c,b-=d;
            x[i*4]=a,y[i*4]=b;
            for(int j=1;j<4;j++)
                x[i*4+j]=-y[i*4+j-1],y[i*4+j]=x[i*4+j-1];
            for(int j=0;j<4;j++)x[i*4+j]+=c,y[i*4+j]+=d;
        }
        int ans=1e9;
        for(int i=0;i<4;i++)
            for(int j=4;j<8;j++)
                for(int k=8;k<12;k++)
                    for(int l=12;l<16;l++){
                        p[0]=calc(i,j),p[1]=calc(i,k),p[2]=calc(i,l),p[3]=calc(j,k),p[4]=calc(j,l),p[5]=calc(k,l);
                        sort(p,p+6);
                        if(p[0]==p[1]&&p[1]==p[2]&&p[2]==p[3]&&p[4]==p[5]&&p[0]*2==p[4]&&p[0]!=0)ans=min(ans,i+j+k+l-24);
                    }
        if(ans==1e9)ans=-1;
        printf("%d\n",ans);
    }
    return 0;
}
```
核心实现思想：先预处理每个鼹鼠旋转后的坐标，再通过四层循环枚举每个鼹鼠的旋转状态，计算六点间距离平方并排序，根据正方形边长和对角线关系判断是否构成正方形，更新最小移动次数。

- **Rain_G（4星）**
    - **关键亮点**：思路清晰，对判断正方形的条件阐述详细，代码结构较清晰，通过函数封装使代码可读性较好。
    - **个人心得**：强调判断正方形时使用平方避免精度问题，边长不能为0的条件卡了很久。
    - **核心代码片段**：
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<math.h>
#include<algorithm>
#define int long long
using namespace std;
const int N = 2e3 + 20;
const int INF = 0x7f;
struct node{int x, y;};
int f( node a, node b) {return ( a.x - b.x) * ( a.x - b.x) +  ( a.y - b.y) * ( a.y - b.y);}
node q[N];
int a, b, c, d;
int T, sum[10], ans = INF;
void init(int qwq)
{
    q[qwq].x = a, q[qwq].y = b,q[qwq + 1].x = - q[qwq].y,q[qwq + 1].y = q[qwq].x,q[qwq + 2].x = - q[qwq + 1].y,q[qwq + 2].y = q[qwq + 1].x,q[qwq + 3].x = - q[qwq + 2].y,q[qwq + 3].y = q[qwq + 2].x;
    q[qwq + 0].x += c,q[qwq + 0].y += d,q[qwq + 1].x += c,q[qwq + 1].y += d,q[qwq + 2].x += c,q[qwq + 2].y += d,q[qwq + 3].x += c,q[qwq + 3].y += d;
}
bool check()
{
    if(sum[0] == sum[1] && sum[1] == sum[2] && sum[2] == sum[3] && sum[4] == sum[5] && sum[0] * 2 == sum[4] && sum[0]!= 0)
        return 1;
    return 0;
}
signed main() {
    scanf("%lld", &T);
    while(T--)
    {
        for( int i = 0; i < 4; i++) {
            
            scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
            int qwq = i * 4;
            a -= c, b -= d;
            q[qwq].x = a, q[qwq].y = b;
            init(qwq);
        }
        ans = INF;
        for( int i = 0; i <= 3; i++)
            for( int j = 4; j <= 7; j++)
                for( int k = 8; k <= 11; k++)
                    for( int l = 12; l <= 15; l++) 
                    {
                        sum[0] = f( q[i], q[j]);
                        sum[1] = f( q[i], q[k]);
                        sum[2] = f( q[i], q[l]);
                        sum[3] = f( q[j], q[k]);
                        sum[4] = f( q[j], q[l]);
                        sum[5] = f( q[k], q[l]);
                        sort( sum, sum + 6);
                        if(check())
                            ans = min( ans, i + j + k + l - 24);
                    }
        if(ans == INF)
            ans = -1;
        printf("%lld\n", ans);
    }
    return 0;
}
```
核心实现思想：通过`init`函数预处理每个鼹鼠旋转后的坐标，在主函数中通过四层循环枚举旋转状态，计算各点间距离平方并存入数组，调用`check`函数判断是否构成正方形，更新最小移动次数。

### 最优关键思路或技巧
利用数据范围小的特点采用枚举法，预处理每个点旋转后的坐标，通过计算距离平方避免开根号带来的精度问题，利用排序和特定的边长、对角线关系判断是否构成正方形。

### 可拓展之处
同类型题可考虑增加点数或旋转角度的多样性，类似算法套路适用于数据范围小，可通过枚举所有可能情况求解的题目，如一些几何图形判定和组合问题。

### 洛谷相似题目
- [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)：通过枚举组合情况解决问题，与本题枚举思路类似。
- [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)：利用枚举和数学运算求解，涉及到类似的暴力枚举思想。
- [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举数字组合并进行判断，与本题枚举判断的思路相符。

### 个人心得摘录与总结
QQH08认为暴力做法繁琐；Rain_G强调判断正方形时用平方避免精度问题，边长不能为0的条件调试耗时久。总结为在处理几何判定问题时，要注意精度处理和特殊条件判断，暴力枚举虽思路直接，但实现细节可能较繁琐。 

---
处理用时：99.73秒