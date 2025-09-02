# [POI 2005] PUN-Points

## 题目描述

A set of grid points in a plane (points whose both cartesian coordinates are integers) which we shall refer to as the pattern, as well as a group of other sets of grid points on the plane are given. We would like to know which of the sets are similar to the pattern, i.e. which of them can be transformed by rotations, translations, reflections and dilations so that they are identical to the pattern. For instance: the set of points $\{(0,0),(2,0),(2,1)\}$ is similar to the set $\{(6,1),(6,5),(4,5)\}$, it is however not similar to the set $\{(4,0),(6,0),(5,-1)\}$.

TaskWrite a programme which:

reads from the standard input the description of the pattern and the family of the investigated sets of points,determines which of the investigated sets of points are similar to the pattern,writes the outcome to the standard output.

题目描述：


给出一个包含平面上格点的集合（格点的定义是xy坐标均为整数），我们将其称作“模式集合”。


接下来给出另外的几个包含平面上点的集合。我们想要考察后面给出的哪些集合和“模式集合”是“相似”的，即：该集合可以通过 旋转，平移，翻转，和缩放 使得该集合和“模式集合”完全相同。


例：{(0,0),(2,0),(2,1)}这个集合和{(6,1),(6,5),(4,5)}这个集合是相似的，但和{(4,0),(6,0),(5,-1)}这个集合是不相似的。


任务：


写一个程序，使得


能从标准输入读取“模式集合”和需要考察（是否相似）的集合，判断哪些集合和“模式集合”相似，并将结果输出到标准输出


输入格式：


标准输入的第一行有一个整数 k (1<=k<=25000)，代表“模式集合”中的点数


接下来k行，每行两个数，用一个空格分隔，第i+1行的两个数分别代表“模式集合”中第i个点的x坐标和y坐标(-20000<=x,y<=20000)


“模式集合”中的点两两不同。


接下来一行一个整数n，代表有n个需要考察的集合


接下来有n个对需要考察的集合的描述：


每个描述的第一行包含一个整数l，代表该集合中的点数(1<=l<=25000)


接下来l行每行包含该集合中一个点的x坐标和y坐标，用一个空格分隔(-20000<=x,y<=20000，为整数)


包含在同一集合中的点两两不同。


输出格式：


你的程序应该向标准输出流输出n行，每行代表对于一个需要考察的集合的结果。


如果第i个需要考察的集合与“模式集合”相似，则第i行应包含单词TAK，即波兰语中的yes


否则第i行应包含单词NIE，即波兰语中的no


## 样例 #1

### 输入

```
3
0 0
2 0
2 1
2
3
4 1
6 5
4 5
3
4 0
6 0
5 -1```

### 输出

```
TAK
NIE```

# 题解

## 作者：oscar (赞：2)

【POI补全计划#2 POI2005 PUN】

先说题目大意：

给定两个点集，判断是否相似，相似输出TAK，不相似输出NIE

相似的定义是可以经过四种操作后重合（平移，旋转，翻转，防缩）

多组数据（具体输入方式见题目）


----------------题解分割线-------------------


这题本来是个很水的题，但是卡我精度卡了好久。。可能是我太菜了。。

简单来说就是找到点集的重心（所有点加起来除以点的个数），

然后将所有点标准化至【最长的线段长度为1，重心在原点上】

这样就解决了平移和防缩的问题

接下来对极角排序后差分一下（**第二关键字为长度**）

最后由于圆上的整点个数比较少，只需要暴力判断其中一个点集是否是另一个旋转/翻转后的结果就行了，不需要KMP

**注意要特判有可能有点和重心重合**

**注意任何可能会被卡精度的地方**

福利：[原题地址](http://oi.edu.pl/old/php/show.php?ac=e180702)

贴代码时间（不要吐槽我不小心面向对象了QWQ）

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const double eps=1e-10,PI=3.1415926535897932384626;
const int MAXN=25050;
struct point
{
    double x,y;
    inline point(){}
    inline point(double xx,double yy){x=xx,y=yy;}
    inline point(const point &p){x=p.x,y=p.y;}
    inline point operator=(const point &p){x=p.x,y=p.y;return *this;}
    inline point operator+(const point &p)const{return point(x+p.x,y+p.y);}
    inline point operator+=(const point &p){return *this=*this+p;}
    inline point operator-(const point &p)const{return point(x-p.x,y-p.y);}
    inline point operator-=(const point &p){return *this=*this-p;}
    inline double operator*(const point &p)const{return x*p.x+y*p.y;}
    inline point operator/(const double &n)const{return point(x/n,y/n);}
    inline point operator/=(const double &n){return *this=*this/n;}
    inline bool operator==(const point &p)const{return abs(x-p.x)<eps&&abs(y-p.y)<eps;}
}set1[MAXN],set2[MAXN];
struct atom
{
    double len,deg;
    inline bool operator==(const atom &a)const
    {
        return abs(len-a.len)<eps&&abs(deg-a.deg)<eps;
    }
    inline bool operator!=(const atom &a)const
    {
        return !(*this==a);
    }
    inline bool operator<(const atom &a)const
    {
        return abs(deg-a.deg)<eps?len<a.len:deg<a.deg;
    }
}revarr1[MAXN],arr1[MAXN],arr2[MAXN];
inline bool cmp(const atom &a,const atom &b)
{
    return a.len<b.len;
}
inline bool cmp2(const atom &a,const atom &b)
{
    return abs(a.deg-b.deg)<eps?a.len<b.len:a.deg>b.deg;
}
inline double sqr(const double &x){return x*x;}
inline bool match(const atom arr1[],const atom arr2[],int len)
{
    static int tt=0;
    ++tt;
    for(int delta=0;delta<len;delta++)
    {
        bool flag=true;
        for(int i=1;i<=len;i++)
        {
            if(arr1[i]!=arr2[(i+delta-1)%len+1])
            {
                flag=false;
                break;
            }
        }
        if(flag)return true;
    }
    return false;
}
int main()
{
    int n,t,n2;
    bool havecenter=false,havecenter2;
    scanf("%d",&n);
    point c1(0,0);
    for(int i=1;i<=n;i++)
    {
        scanf("%lf%lf",&set1[i].x,&set1[i].y);
        c1+=set1[i];
    }
    c1/=n;
    for(int i=1;i<=n;i++)
    {
        if(!havecenter)set1[i]-=c1;
        else set1[i]=set1[i+1]-c1;
        if(set1[i]==point(0,0))
        {
            havecenter=true;
            n--;i--;
            continue;
        }
        arr1[i].len=sqrt(sqr(set1[i].x)+sqr(set1[i].y));
        arr1[i].deg=acos(set1[i].x/arr1[i].len);
        if(set1[i].y<0)arr1[i].deg=2*PI-arr1[i].deg;
    }
    sort(arr1+1,arr1+n+1,cmp);
    double maxlen=arr1[n].len;
    for(int i=1;i<=n;i++)
    {
        arr1[i].len/=maxlen;
        revarr1[i]=arr1[i];
    }
    sort(arr1+1,arr1+n+1);
    sort(revarr1+1,revarr1+n+1,cmp2);
    double maxdeg=arr1[n].deg;
    for(int i=n;i>=2;i--)
    {
        revarr1[n-i+2].deg=(arr1[i].deg-=arr1[i-1].deg);
    }
    revarr1[1].deg=arr1[1].deg+=2*PI-maxdeg;
    scanf("%d",&t);
    while(t--)
    {
        havecenter2=false;
        scanf("%d",&n2);
        for(int i=1;i<=n2;i++)
        {
            scanf("%lf%lf",&set2[i].x,&set2[i].y);
        }
        point c2(0,0);
        for(int i=1;i<=n2;i++)
        {
            c2+=set2[i];
        }
        c2/=n2;
        for(int i=1;i<=n2;i++)
        {
            if(!havecenter2)set2[i]-=c2;
            else set2[i]=set2[i+1]-c2;
            if(set2[i]==point(0,0))
            {
                havecenter2=true;
                n2--;i--;
                continue;
            }
            arr2[i].len=sqrt(sqr(set2[i].x)+sqr(set2[i].y));
            arr2[i].deg=acos(set2[i].x/arr2[i].len);
            if(set2[i].y<0)arr2[i].deg=2*PI-arr2[i].deg;
        }
        if(n2!=n)
        {
            printf("NIE\n");
            continue;
        }
        else if(n==0)
        {
            printf("TAK\n");
            continue;
        }
        sort(arr2+1,arr2+n2+1,cmp);
        double maxlen=arr2[n2].len;
        for(int i=1;i<=n2;i++)
        {
            arr2[i].len/=maxlen;
        }
        sort(arr2+1,arr2+n2+1);
        double maxdeg=arr2[n2].deg;
        for(int i=n2;i>=2;i--)
        {
            arr2[i].deg-=arr2[i-1].deg;
        }
        arr2[1].deg+=2*PI-maxdeg;
        bool f1=match(arr1,arr2,n),f2=match(revarr1,arr2,n);
        if(havecenter==havecenter2&&(f1||f2))printf("TAK\n");
        else printf("NIE\n");
    }
    return 0;
}
```

---

