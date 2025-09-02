# [GCJ 2012 #2] Aerobics

## 题目描述

有氧操课程开始了。教练说：“请大家在训练垫上站好，保证每个人都有足够的空间能自由挥动手臂，而且不会碰到其他人。”大家开始在垫子上走动，试图找到合适的位置。时间一分一秒过去，最终教练非常恼火，要求你写一个程序来给所有人安排正确的位置，希望这样比让他们自己慢慢挪要快！

你会得到课程所用垫子的尺寸（宽度和长度）。对于每位学员，都有一个属于她自己的圆形区域，半径等于她手臂的可达范围。这些圆不能相交，但可以相切；每个圆的圆心（即学员所站的位置）必须在垫子上。注意，手臂可以伸出垫子之外。你知道垫子的空间非常充足——垫子的面积至少是所有圆面积总和的五倍。所有学员都能按要求站下这一点始终成立。

## 说明/提示

**限制条件**

- $1 \leq \mathbf{T} \leq 50$
- $1 \leq \mathbf{W}, \mathbf{L} \leq 10^9$
- $1 \leq \mathbf{r}_i \leq 10^5$
- 垫子的面积至少是所有圆面积总和的 5 倍：
- $5 \times \pi \times (\mathbf{r}_1^2 + \ldots + \mathbf{r}_\mathbf{N}^2) \leq \mathbf{W} \times \mathbf{L}$

**测试集 1（6 分，结果可见）**

- $1 \leq \mathbf{N} \leq 10$

**测试集 2（15 分，结果隐藏）**

- $1 \leq \mathbf{N} \leq 10^3$
- 所有测试用例的圆总数不超过 6000

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
2
2 6 6
1 1
3 320 2
4 3 2```

### 输出

```
Case #1: 0.0 0.0 6.0 6.0
Case #2: 0.0 0.0 7.0 0.0 12.0 0.0```

# 题解

## 作者：sqh0012 (赞：0)

### 题意：

我们需要在尺寸为 $W \times L$ 的矩形垫子上安排 $N$ 个学员的位置。每个学员 $i$ 需要占据一个半径为 $r_i$ 的圆形区域，要求：

- 所有圆形区域互不重叠（可以相切）；

- 圆心必须位于垫子内，即 $0 \le x_i \le W$，$0 \le y_i \le L$；

- 保证垫子面积至少是所有圆面积总和的 $5$ 倍。

---

### 解法：

你可能想到了分治。

但是圆的半径差异可能极大（如 $r=100$ 和 $r=1$ 共存），难以找到公平的分割线。若用直线将空间分成两半，可能导致一侧无法容纳大圆，而另一侧空间浪费。即使你成功划分，两侧圆的边界区域仍可能互相干扰（需要重叠检查），无法完全独立解决。

思考到大圆占用更多空间，限制更多。如果先放小圆，可能导致大圆无处可放。所以可以用贪心。思路就是将学员按半径从大到小排序，确保优先处理约束最强的圆。

你还想要依据？大圆的半径平方（面积）增长更快，优先处理能更高效利用剩余空间。

那怎么找到合法位置？题目明确说明：垫子面积不小于 $5$ 倍所有圆面积总和。这意味着：

- 随机撒点时，每个尝试有至少 $20\%$ 的成功概率（因为圆的覆盖面积不大于 $20\%$ 垫子面积）；

- 数学期望上，平均只需 $5$ 次随机尝试即可找到合法位置。

那不就好办了，对每个学员尝试最多 $1000$ 次随机放置，大概率能成功。只不过……

有几种极端情况，如果排列的位置是一个狭长的条，大圆周围可能出现"环形禁区"，此时随机尝试可能低效，系统化扫描能保证找到解。所以他们两个相结合，会十分高效。

时间复杂度 $O(N^2K)$，其中 $K$ 是随机尝试次数（最坏情况），空间复杂度 $O(N)$。


```cpp
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<ctime>
using namespace std;

const int MAXN=1005;
struct S
{
    int i;
    double r;
};
vector<S>s(MAXN);
vector<pair<double,double>>p(MAXN);
vector<double>d(MAXN);
vector<pair<double,double>>o(MAXN);
vector<double>od(MAXN);

bool c(const S&a,const S&b)
{
    return a.r>b.r;
}

bool v(double x,double y,int n,double cr)
{
    for(int i=1;i<=n;++i)
    {
        double dx=x-p[i].first;
        double dy=y-p[i].second;
        if(sqrt(dx*dx+dy*dy)<(cr+d[i]))return false;
    }
    return true;
}

void solve(int cn)
{
    int N,W,L;
    cin>>N>>W>>L;
    for(int i=1;i<=N;++i)
    {
        cin>>s[i].r;
        s[i].i=i;
    }
    sort(s.begin()+1,s.begin()+N+1,c);
    for(int st=1;st<=N;++st)
    {
        double r=s[st].r;
        bool placed=false;
        for(int a=0;a<1000;++a)
        {  // 随机尝试
            double x=((double)rand()/RAND_MAX)*W;
            double y=((double)rand()/RAND_MAX)*L;
            if(v(x,y,st-1,r))
            {
                p[st]={x,y};
                d[st]=r;
                placed=true;
                break;
            }
        }
        
        if(!placed)
        {  // 系统化尝试
            for(double x=0;x<=W&&!placed;x+=r)
            {
                for(double y=0;y<=L&&!placed;y+=r)
                {
                    if(v(x,y,st-1,r)){
                        p[st]={x,y};
                        d[st]=r;
                        placed=true;
                        break;
                    }
                }
            }
        }
        
        if(!placed)
        {  // 还没找到？那就更精确些
            for(double x=0;x<=W&&!placed;x+=0.1){
                for(double y=0;y<=L&&!placed;y+=r*2){
                    if(v(x,y,st-1,r)){
                        p[st]={x,y};
                        d[st]=r;
                        placed=true;
                        break;
                    }
                }
            }
        }
    }
    
    for(int i=1;i<=N;++i)
    {
        o[s[i].i]=p[i];
        od[s[i].i]=d[i];
    }
    
    cout<<"Case #"<<cn<<":";
    for(int i=1;i<=N;++i)
    {
        cout<<" "<<o[i].first<<" "<<o[i].second;
    }
    cout<<endl;
}

int main()
{
    srand(time(0));
    int T;
    cin>>T;
    for(int t=1;t<=T;++t)
    {
        solve(t);
    }
    return 0;
}
```

---

