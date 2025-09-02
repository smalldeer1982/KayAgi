# 题目信息

# Magic Ship

## 题目描述

坐标系上有一只小船，现在想从 $(x_1,y_1)$ 去 $(x_2,y_2)$ 。每时刻都有风，会把船往对应的风向吹一个单位（比如北风会把船往南吹），风是循环的，吹完 $s_1 \sim s_n$ 就又会从 $s_1$ 开始。船在每一时刻都可以向指定方向移动一个单位。求船到目的地的最少时间，如果不能到达输出 **-1** 。

## 样例 #1

### 输入

```
0 0
4 6
3
UUU
```

### 输出

```
5
```

## 样例 #2

### 输入

```
0 3
0 0
3
UDD
```

### 输出

```
3
```

## 样例 #3

### 输入

```
0 0
0 1
1
L
```

### 输出

```
-1
```

# AI分析结果

### 算法分类
二分

### 综合分析与结论
这些题解的核心思路都是利用二分答案来解决问题。因为如果在 $t$ 时刻能到达终点，那么在 $t + 1$ 时刻也一定能到达，答案具有单调性，所以可以使用二分来查找最小的到达时间。

各题解的主要步骤如下：
1. **预处理**：将起点平移到原点，计算风向对应的位移向量和位移前缀和，得到一个风周期的总位移。
2. **二分答案**：二分枚举时间 $k$，计算在 $k$ 轮中风吹导致的船的位置，再考虑人最多走 $k$ 步，判断此时船与终点的曼哈顿距离是否小于等于 $k$。
3. **结果判断**：如果对于所有枚举的情况都无解，则输出 -1，否则输出最小的满足条件的时间。

各题解的区别主要在于代码实现的细节和一些处理方式，但整体思路是一致的。

### 所选题解
- **George1123（5星）**
    - **关键亮点**：思路清晰，对整个解题过程的分析非常详细，包括坐标系平移、位移前缀和的计算、单调性的证明等，代码简洁且注释清晰。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;

//Start
#define lng long long
#define db double
#define mk make_pair
#define pb push_back
#define fi first
#define se second
#define rz resize
#define sz(x) (int)((x).size())
const int inf=0x3f3f3f3f;
const lng INF=0x3f3f3f3f3f3f3f3f;

//Data
const int N=1e5;
int n; char s[N+7];
lng ans=INF;

//Point
typedef pair<lng,lng> point;
point st,ed,ad[N+7];
lng dis(point x,point y){return abs(x.fi-y.fi)+abs(x.se-y.se);}
point operator-(const point x,const point y){return mk(x.fi-y.fi,x.se-y.se);}
point operator+(const point x,const point y){return mk(x.fi+y.fi,x.se+y.se);}
point operator*(const point x,const lng y){return mk(x.fi*y,x.se*y);}

//Main
int main(){
    scanf("%lld%lld%lld%lld%d%s",&st.fi,&st.se,&ed.fi,&ed.se,&n,&s[1]);
    ed=ed-st;
    if(ed.fi==0&&ed.se==0) return puts("0"),0;
    for(int i=1;i<=n;i++)
        if(s[i]=='U') ad[i]=ad[i-1]+mk(0,1);
        else if(s[i]=='D') ad[i]=ad[i-1]+mk(0,-1);
        else if(s[i]=='L') ad[i]=ad[i-1]+mk(-1,0);
        else if(s[i]=='R') ad[i]=ad[i-1]+mk(1,0);
    for(int i=1;i<=n;i++){
        lng l=-1,r=1e12+1;
        while(l<r-1){
            lng mid((l+r)>>1);
            if(dis(ad[i]+ad[n]*(mid),ed)-mid*n-i<=0) r=mid;
            else l=mid;
        }
        if(dis(ad[i]+ad[n]*r,ed)-r*n-i<=0) ans=min(ans,r*n+i);
    }
    if(ans==INF) puts("-1");
    else printf("%lld\n",ans);
    return 0;
}
```
- **LAICZ（4星）**
    - **关键亮点**：详细解释了使用二分的原因，通过具体例子说明判断时刻能否到达的关键，代码注释详细，对算法复杂度进行了分析。
    - **核心代码**：
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#define maxn 100005
#define maxt 1000000000000000005
#define int long long
using namespace std;

int a1,b1,a2,b2,n;
//(a1,b1) 起点，(a2,b2) 终点 
char s[maxn];
//s{n} 表示风的位移（题目中） 

struct point{
    int x,y;
    friend point operator + (point a,point b){
        return (point){a.x + b.x,a.y + b.y};
    }
    friend point operator * (int a,point b){
        return (point){a * b.x,a * b.y};
    }
    //点加，点乘 
}sum[maxn],d[200],p1,p2;
//sum[i] 表示前 i 时刻风导致的位移
//d['U','D','L','R'] 分别表示该指令的位移
//p1,p2 表示起点终点 

int dis(point a,point b){
    //表示 a 和 b 的曼哈顿距离 
    return abs(a.x - b.x) + abs(a.y - b.y);
}

bool check (int t){
    //检查 t 时刻可不可以到达终点 
    int a,b;
    a = t / n,b = t % n;
    //拆分为 a * sum[n] + sum[b] 
    point oft = a * sum[n] + sum[b];
    //前 t 时刻偏移量 
    point realstart = p1 + oft;
    //realstart:真实的起点，计算其与终点的曼哈顿距离 
    if(dis(realstart,p2) <= t)
        return true;
    else 
        return false;
}

signed main(){
    scanf("%lld%lld%lld%lld%lld%s",&a1,&b1,&a2,&b2,&n,s+1);
    p1 = {a1,b1},p2 = {a2,b2};
    d['U'] = {0,1},d['D'] = {0,-1};
    d['L'] = {-1,0},d['R'] = {1,0};
    //d['U','D','L','R'] 分别表示该指令的位移
    for(int i = 1;i <= n;i++){
        sum[i] = sum[i - 1] + d[s[i]];
        //前缀和 
    }
    
    int l = 0,r = maxt,mid;
    while(l <= r){
        mid = (l + r) >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
        if(l == mid) break;
    }
    if(l >= maxt)
        //如果比最大的时间还大，那么肯定不可能到达 
        cout<<-1<<endl;
    else
        //输出的是最小时间 
        cout<<l<<endl;
    
    return 0;
}
```
- **dyc2022（4星）**
    - **关键亮点**：对思路的解释清晰，通过将起点设为原点简化计算，使用 `pair` 重载运算符方便操作，代码简洁。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int sx,sy,ex,ey,n,l=1,r=1e15;
char ch[100006];
pair<int,int> sum[100006];
pair<int,int> operator +(pair<int,int> x,pair<int,int> y){return make_pair(x.first+y.first,x.second+y.second);}
pair<int,int> operator -(pair<int,int> x,pair<int,int> y){return make_pair(x.first-y.first,x.second-y.second);}
pair<int,int> operator *(pair<int,int> x,int y){return make_pair(x.first*y,x.second*y);}
pair<int,int> dire(char ch)
{
    switch(ch)
    {
        case 'U':return make_pair(0,1);
        case 'D':return make_pair(0,-1);
        case 'L':return make_pair(-1,0);
        case 'R':return make_pair(1,0);
    }
}
int judge(int tim)
{
    pair<int,int> chng=make_pair(ex,ey)-(sum[n]*floor(tim*1.0/n)+sum[tim%n]);
    return abs(chng.first)+abs(chng.second)<=tim;
}
main()
{
    scanf("%lld%lld%lld%lld%lld%s",&sx,&sy,&ex,&ey,&n,ch+1);
    ex-=sx,ey-=sy;
    for(int i=1;i<=n;i++)sum[i]=sum[i-1]+dire(ch[i]);
    while(l<r)
    {
        int mid=(l+r)>>1;
        if(judge(mid))r=mid;
        else l=mid+1;
    }
    if(l==1e15)printf("-1");
    else printf("%lld",l);
    return 0;
}
```

### 最优关键思路或技巧
1. **坐标系平移**：将起点平移到原点，简化计算，使终点坐标变为 $(x_2 - x_1, y_2 - y_1)$。
2. **前缀和预处理**：计算风向对应的位移向量和位移前缀和，方便快速计算在任意时刻风吹导致的船的位置。
3. **二分答案**：利用答案的单调性，通过二分查找最小的到达时间，将时间复杂度从暴力枚举的 $O(T)$ 降低到 $O(\log T)$。

### 拓展思路
同类型题或类似算法套路：
- 对于具有单调性的最值问题，可以考虑使用二分答案来解决，例如在一些求最小步数、最小时间等问题中。
- 当问题中存在周期性的影响因素时，可以先预处理一个周期的影响，然后利用周期性快速计算任意时刻的状态。

### 推荐题目
1. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：二分答案求解最小的最大跳跃距离。
2. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：二分答案求解最大分段和的最小值。
3. [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)：二分答案求解最小的最大相邻路标距离。

### 个人心得摘录与总结
- **cike_bilibili**：提到不开 `long long` 见祖宗，强调了在处理大数据范围时要注意数据类型的选择。
- **LAICZ**：指出一些结尾为 1 的变量（如 y1）是 c++ 关键字，不能用，提醒在命名变量时要注意避免使用关键字。同时提到二分的右边界取值要足够大，需要考虑极端情况，保证结果的准确性。

---
处理用时：75.78秒