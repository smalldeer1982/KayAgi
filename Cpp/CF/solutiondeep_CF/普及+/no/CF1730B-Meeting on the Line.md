# 题目信息

# Meeting on the Line

## 题目描述

$ n $ people live on the coordinate line, the $ i $ -th one lives at the point $ x_i $ ( $ 1 \le i \le n $ ). They want to choose a position $ x_0 $ to meet. The $ i $ -th person will spend $ |x_i - x_0| $ minutes to get to the meeting place. Also, the $ i $ -th person needs $ t_i $ minutes to get dressed, so in total he or she needs $ t_i + |x_i - x_0| $ minutes.

Here $ |y| $ denotes the absolute value of $ y $ .

These people ask you to find a position $ x_0 $ that minimizes the time in which all $ n $ people can gather at the meeting place.

## 说明/提示

- In the $ 1 $ -st test case there is one person, so it is efficient to choose his or her position for the meeting place. Then he or she will get to it in $ 3 $ minutes, that he or she need to get dressed.
- In the $ 2 $ -nd test case there are $ 2 $ people who don't need time to get dressed. Each of them needs one minute to get to position $ 2 $ .
- In the $ 5 $ -th test case the $ 1 $ -st person needs $ 4 $ minutes to get to position $ 1 $ ( $ 4 $ minutes to get dressed and $ 0 $ minutes on the way); the $ 2 $ -nd person needs $ 2 $ minutes to get to position $ 1 $ ( $ 1 $ minute to get dressed and $ 1 $ minute on the way); the $ 3 $ -rd person needs $ 4 $ minutes to get to position $ 1 $ ( $ 2 $ minutes to get dressed and $ 2 $ minutes on the way).

## 样例 #1

### 输入

```
7
1
0
3
2
3 1
0 0
2
1 4
0 0
3
1 2 3
0 0 0
3
1 2 3
4 1 2
3
3 3 3
5 3 3
6
5 4 7 2 10 4
3 2 5 1 4 6```

### 输出

```
0
2
2.5
2
1
3
6```

# AI分析结果

### 题目内容翻译
# 线上会议

## 题目描述
有 $n$ 个人住在数轴上，第 $i$ 个人住在点 $x_i$ 处（$1 \leq i \leq n$）。他们想选择一个位置 $x_0$ 进行会面。第 $i$ 个人到达会面地点需要花费 $|x_i - x_0|$ 分钟。此外，第 $i$ 个人需要 $t_i$ 分钟来穿衣打扮，所以总共需要 $t_i + |x_i - x_0|$ 分钟。

这里 $|y|$ 表示 $y$ 的绝对值。

这些人要求你找到一个位置 $x_0$，使得所有人能够聚集到会面地点的时间最短。

## 说明/提示
- 在第一个测试用例中，只有一个人，所以选择他或她所在的位置作为会面地点是最有效的。这样，他或她到达会面地点需要的时间就是穿衣打扮所需的 3 分钟。
- 在第二个测试用例中，有两个人，他们不需要时间来穿衣打扮。他们每个人到达位置 2 都需要 1 分钟。
- 在第五个测试用例中，第一个人到达位置 1 需要 4 分钟（4 分钟穿衣打扮，0 分钟路程）；第二个人到达位置 1 需要 2 分钟（1 分钟穿衣打扮，1 分钟路程）；第三个人到达位置 1 需要 4 分钟（2 分钟穿衣打扮，2 分钟路程）。

## 样例 #1
### 输入
```
7
1
0
3
2
3 1
0 0
2
1 4
0 0
3
1 2 3
0 0 0
3
1 2 3
4 1 2
3
3 3 3
5 3 3
6
5 4 7 2 10 4
3 2 5 1 4 6
```

### 输出
```
0
2
2.5
2
1
3
6
```

### 算法分类
贪心

### 综合分析与结论
这些题解主要围绕如何找到一个最优的会面位置 $x_0$，使得所有人到达该位置的最大时间最小。不同题解的思路各有特色，主要分为贪心、三分、二分等方法。
- **贪心思路**：大部分题解采用贪心策略，通过将穿衣时间 $t_i$ 转化为距离，把问题转化为求新坐标下最左和最右点的中点。
- **三分思路**：利用三分算法的特性，对 $x_0$ 进行三分查找，找到使 $\max\{f_1(x),f_2(x),\dots,f_n(x)\}$ 最小的 $x$ 值。
- **二分思路**：对 $x_0$ 进行二分，判断左右两边人到达 $x_0$ 的最大时间，根据大小调整二分区间。

### 所选题解
- **作者：隐仞Mrsu（4星）**
    - **关键亮点**：思路清晰，详细阐述了贪心、三分、二分三种方法的原理和实现，对绝对值的处理和问题的转化分析到位，代码可读性高。
    - **个人心得**：最初使用三分算法超时，后来发现取精度为 $10^{-8}$ 会超时，改为 $10^{-7}$ 后通过，并且指出用 `cout<<r<<'\n'` 可能会按科学计数法输出浮点数导致答案错误。
- **作者：GalwayGirl（4星）**
    - **关键亮点**：通过画图直观地展示了问题的转化过程，将复杂的绝对值问题转化为两点间距离问题，思路易于理解，代码简洁。
- **作者：abensyl（4星）**
    - **关键亮点**：采用模拟 + 贪心的思路，先让穿衣服时间最长的人穿衣服，其他人向其靠近，再根据剩余人的位置确定最终会面地点，思路独特。

### 重点代码
#### 隐仞Mrsu - 贪心代码
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 500005;
const int inf = 0x3f3f3f3f;
LL _,n,a[N],t[N],mn,mx;
void work(){
    cin>>n;
    for(LL i=1;i<=n;i++){
        cin>>a[i];
    }
    for(LL i=1;i<=n;i++){
        cin>>t[i];
    }
    mx=-inf,mn=inf;
    for(LL i=1;i<=n;i++){
        mn=min(mn,a[i]-t[i]);
        mx=max(mx,a[i]+t[i]);
    }
    double res=(mn+mx)*1.0/2.0;
    printf("%.6lf\n",res);
}
int main(){
    ios::sync_with_stdio(false);
    cin>>_;
    while(_--){
        work();
    }
}
```
**核心实现思想**：通过遍历每个人的坐标 $a_i$ 和穿衣时间 $t_i$，计算出 $a_i - t_i$ 的最小值和 $a_i + t_i$ 的最大值，最后取这两个值的平均数作为最优会面位置。

#### GalwayGirl - 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+100;
long long T,n,x[N],t[N];
void solve(){
    scanf("%lld",&n);
    long long min_=1e18,max_=-1e18;
    for(int i=1;i<=n;i++)scanf("%lld",&x[i]);
    for(int i=1;i<=n;i++)scanf("%lld",&t[i]);
    for(int i=1;i<=n;i++){         
        min_=min(min_,x[i]-t[i]);
        max_=max(max_,x[i]+t[i]);
    }                         
    printf("%.6lf\n",(min_+max_)*1.0/2);
}
int main(){
    scanf("%lld",&T);
    while(T--)solve();
    return 0;
}
```
**核心实现思想**：同样是遍历每个人的坐标和穿衣时间，找出 $x_i - t_i$ 的最小值和 $x_i + t_i$ 的最大值，取平均值得到结果。

#### abensyl - 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+4;
int x[N];
int t[N];
void solve() {
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",x+i);
    int goal=0;
    int up=-1;
    for(int i=1;i<=n;++i) {
        scanf("%d",t+i);
        if(t[i]>up) up=t[i],goal=x[i];
    }
    int ne=goal,fa=goal;
    for(int i=1;i<=n;++i) {
        if(x[i]<goal) x[i]=min(x[i]+(up-t[i]),goal);
        else if(x[i]>goal) x[i]=max(x[i]-(up-t[i]),goal);
        if(x[i]>fa) fa=x[i];
        else if(x[i]<ne) ne=x[i];
    }
    printf("%lf\n",(fa+ne)/2.);
}
int main() {
    int T;
    scanf("%d",&T);
    while(T--) solve();
    return 0;
}
```
**核心实现思想**：先找出穿衣服时间最长的人的位置，在其穿衣服时让其他人向其靠近，最后根据剩余人的最左和最右位置确定最终会面地点。

### 关键思路或技巧
- **转化思想**：将穿衣时间 $t_i$ 转化为距离，把问题转化为求新坐标下最左和最右点的中点，简化了问题。
- **绝对值处理**：利用绝对值的性质 $\vert a - b \vert = \max\{a - b, b - a\}$ 对式子进行变形，便于分析和计算。

### 拓展思路
同类型题或类似算法套路：
- 涉及到“最大值最小”或“最小值最大”的问题，可考虑二分、三分或贪心算法。
- 对于包含绝对值的问题，可尝试通过分类讨论或变形将绝对值去掉，简化问题。

### 推荐题目
- [P1883 函数](https://www.luogu.com.cn/problem/P1883)：考察三分算法的应用。
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：典型的二分答案问题。
- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：同样是二分答案的题目，与本题的“最大值最小”思路相似。

---
处理用时：77.04秒