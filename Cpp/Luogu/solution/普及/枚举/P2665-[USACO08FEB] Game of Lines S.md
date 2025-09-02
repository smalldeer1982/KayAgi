# [USACO08FEB] Game of Lines S

## 题目背景

Farmer John 最近发明了一个游戏，来考验自命不凡的贝茜。


## 题目描述

Farmer John has challenged Bessie to the following game: FJ has a board with dots marked at N (2 ≤ N ≤ 200) distinct lattice points. Dot i has the integer coordinates Xi and Yi (-1,000 ≤ Xi ≤ 1,000; -1,000 ≤ Yi ≤ 1,000).

Bessie can score a point in the game by picking two of the dots and drawing a straight line between them; however, she is not allowed to draw a line if she has already drawn another line that is parallel to that line. Bessie would like to know her chances of winning, so she has asked you to help find the maximum score she can obtain.

游戏开始的时 候，FJ 会给贝茜一块画着 $N (2 \le N \le 200)$ 个不重合的点的木板，其中第 $i$ 个点的横、纵坐标分别为 $X_i$ 和 $Y_i (-1000 \le X_i \le 1000, -1000 \le Y_i \le 1000)$。

贝茜可以选两个点画一条过它们的直线，当且仅当平面上不存在与画出直线 平行的直线。游戏结束时贝茜的得分，就是她画出的直线的总条数。为了在游戏中胜出，贝茜找到了你，希望你帮她计算一下最大可能得分。


## 说明/提示

贝茜能画出以下 $4$ 种斜率的直线：$-1$，$0$，$\dfrac{1}{3}$ 以及 $1$。

## 样例 #1

### 输入

```
4 
-1 1 
-2 0 
0 0 
1 1```

### 输出

```
4 ```

# 题解

## 作者：大头 (赞：17)

水题一道。

对斜率进行排序，判重即可。

注意：特判一下直线与坐标轴垂直的情况。

```cpp
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm> 
using namespace std;
double a[205],b[205],c[40005];
int n,ans,cnt;
int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%lf%lf",&a[i],&b[i]);
    for (int i=1;i<n;i++)
        for (int j=i+1;j<=n;j++)
            if (a[i]==a[j]) c[++cnt]=0;
            else if (b[i]==b[j]) c[++cnt]=10000;
            else c[++cnt]=(a[i]-a[j])/(b[i]-b[j]);
    sort(c+1,c+cnt+1);
    ans=1;
    for (int i=2;i<=cnt;i++)
        if (c[i]-c[i-1]>1e-10) ans++;
    printf("%d",ans);
}
```

---

## 作者：hmh13951417981 (赞：8)

### 这道题用一次函数去求斜率，然后用map存储是否有这样斜率的直线，判重
### 设一次函数解析式为y=kx+b 现在告诉你横纵坐标去求k
### y1=k* x1+b , y2=k* x2+b 则k=(y1-y2)/(x1-x2)
### 由于斜率不一定为整型数，所以 double k=(y1-y2)*1.0/(x1-x2)
## But! 当x1=x2时，除数为0会出错，所以需要特判
## 代码如下：
------------

```c
#include<bits/stdc++.h>
using namespace std;
int n,a[201][2],s;
map<double,bool>xl;//开一个以double为下标的bool类型数组
double x;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i][0]>>a[i][1];//输入
    for(int i=1;i<n;i++)
        for(int j=i+1;j<=n;j++){//两两之间算斜率
            if(a[i][0]==a[j][0]) x=10000;//特判
            else x=(a[i][1]-a[j][1])*1.0/(a[i][0]-a[j][0]);
            if(!xl[x]) s++,xl[x]=1;//如果没有出现过，斜率累加，更新为出现过
        }
    cout<<s;//输出总数
    return 0;
}
```


---

## 作者：taoran (赞：7)

因为题目要求无平行即无直线的斜率相同。


尽管前几篇题解好像比我简单，


但我觉得我的方法还是~~较精确的~~    ~~恬不知耻~~


用了一个相当于二维的hash，先约分，用hash把最简分数下相同的分数去除，


最终有几个就是答案ans了。


而且找最终个数答案可以放在判重的过程中解决。


```cpp
#include<bits/stdc++.h>
using namespace std;
int dx,dy,ddl,dl,dd,ans,a[5000][5000],x[100000],y[100000],i,n,j;
int gcd(int a,int b)//gcd来约至最简分数
{
        int r=a%b;
        if (r==0)
            return b;
        return gcd(b,r);
}
int main()
{
        scanf("%d",&n);
        for (i=1;i<=n;++i)
            scanf("%d%d",&x[i],&y[i]);
        for(i=1;i<=n;++i)//枚举进行选择的过程
            {
                    for (j=1;j<=n;++j)
                        {
                                if (i==j)
                                    continue;        
                                dx=x[i]-x[j];
                                dy=y[i]-y[j];
                                if (dx==0 && dy==0)
                                    continue;
                                //注意分母不得为0，此二种情况单独讨论
                                if (dx==0)
                                    {
                                            if (!dl)
                                                {
                                                        dl=1;
                                                        ans++;
                                                }
                                            continue;
                                    }
                                if (dy==0)
                                    {
                                            if (!ddl)
                                                {
                                                        ddl=1;
                                                        ans++;
                                                }
                                            continue;
                                    }
                                dd=gcd(dx,dy);
                                if (!a[dx/dd+2100][dy/dd+2100])
                                    {
                                            ans++;
                                            a[dx/dd+2100][dy/dd+2100]=1;
                                            //由于有负数坐标，
                                           //加上2100可以避免RE
                                    }
                        }
            }
        printf("%d",ans);
        return 0;
}
```

---

## 作者：planche (赞：4)

这个用set就行吧，set自动排序且自动去重
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define inf 2147483647
const ll INF = 0x3f3f3f3f3f3f3f3fll;
#define ri register int
template <class T> inline T min(T a, T b, T c)
{
    return min(min(a, b), c);
}
template <class T> inline T max(T a, T b, T c)
{
    return max(max(a, b), c);
}
template <class T> inline T min(T a, T b, T c, T d)
{
    return min(min(a, b), min(c, d));
}
template <class T> inline T max(T a, T b, T c, T d)
{
    return max(max(a, b), max(c, d));
}
#define pi acos(-1)
#define me(x, y) memset(x, y, sizeof(x));
#define For(i, a, b) for (int i = a; i <= b; i++)
#define FFor(i, a, b) for (int i = a; i >= b; i--)
#define mp make_pair
#define pb push_back
const int maxn = 100005;
// name*******************************
set<double>k;
double x[300],y[300];
int n;
// function******************************

//***************************************
int main()
{
    cin>>n;
    For(i,1,n)
    {
        cin>>x[i]>>y[i];
        For(j,1,i-1)
        {
            if(x[i]==x[j])
                k.insert(inf);
            else
                k.insert((y[i]-y[j])/(x[i]-x[j]));
        }
    }
    cout<<k.size();
    return 0;
}

```

---

## 作者：YosemiteHe (赞：2)

思路较简单，可以使用 `map <double, bool>` 存储斜率（因为计算出斜率后答案可能是小数，要用 `double`），并判重，**当除数 $(x_j - x_i) = 0$ 时需要特判**。

斜率计算公式：$(y_j - y_i) ÷ (x_j - x_i)$。

Code:

```cpp
#include <iostream>
#include <map>//map头文件
using namespace std;
double N, x[205], y[205], a, ans;
map <double, bool> mp;//定义map
int main(void) {
	cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> x[i] >> y[i];//输入 i 点的坐标
	}
	for (int i = 1; i < N; ++i) {
		for (int j = 1 + i; j <= N; ++j) {
			if (x[j] - x[i] == 0) a = 999999;//特判
			else a = (y[j] - y[i]) / (x[j] - x[i]);//计算斜率
			if (mp[a] == false) mp[a] = true, ans++;//判重
		}
	}
	cout << ans << endl;//输出答案
	return 0;
}
```

---

## 作者：ModestCoder_ (赞：2)

又是一道水题


做这道题首先要明确平行


所谓平行，就是斜率相等


那就是求所有线的斜率


有多少个不同的斜率


就是答案


怎么算斜率？


不会不知道吧


斜率k=(yi-yj)/(xi-xj)


这里需要注意一个细节，楼下也提到


不过只用特判一个


就是x坐标相同时，防止被零除


最后去个重


```cpp
var
    x,y:array[0..10000] of longint;
    a:array[0..100000] of real;
    n,i,j,ans,t:longint;
    flag:boolean;
procedure sort(l,r: longint);
      var
         i,j: longint;     x,y:real;
      begin
         i:=l;
         j:=r;
         x:=a[(l+r) div 2];
         repeat
           while a[i]<x do
            inc(i);
           while x<a[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=a[i];
                a[i]:=a[j];
                a[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort(l,j);
         if i<r then
           sort(i,r);
      end;
begin
    readln(n);
    for i:=1 to n do
        begin
            readln(x[i],y[i]);
            for j:=1 to i-1 do
                if x[i]=x[j] then  //特判
                    flag:=true else
                    begin
                        inc(t);
                        a[t]:=(y[i]-y[j])/(x[i]-x[j]); //计算斜率
                    end;
        end;
    sort(1,t);
    a[0]:=a[1]-1;
    for i:=1 to t do  //去重 
        if a[i]<>a[i-1] then
            inc(ans);
    writeln(ans+ord(flag));
end.
```

---

## 作者：YuJieSong (赞：1)

这题点数最多只有200个

所以是可以暴力枚举过滴

双重循环遍历每两个点的组合生成的直线的斜率即可

至于去重的话

这里介绍一下stl库里的set

用set\<double>保存所有的斜率

insert同样的数据时，是不会产生变化滴

最后输出set.size()即可

```cpp
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

set<double> s;

int main() {
    int i,j,n;
    cin >> n;
    double a[n],b[n]; // 分别保存点的x,y坐标
    for (i=0; i<n; i++) cin >> a[i] >> b[i];
    // 注意需要特判斜率不存在的情况
    for (i=0; i<n; i++)
        for (j=i+1; j<n; j++)
            s.insert(a[j]-a[i] == 0 ? 9999999999 : (b[j]-b[i])/(a[j]-a[i]));
    cout << s.size() << endl;
}
```



---

## 作者：嘟嘟cqy (赞：1)

~~水题~~，set 可以自动去重。   
set<...>a;
a.size()指a的长度	a.insert()是插入。  
代码如下——
```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f;
set<double>k;
double x[300],y[300],n;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x[i]>>y[i];
        for(int j=1;j<=i-1;j++)
        {
            if(x[i]==x[j])	k.insert(INF);
            else	k.insert((y[i]-y[j])/(x[i]-x[j]));
        }
    }
    cout<<k.size();
    return 0;
}
```

---

## 作者：Hiraeth (赞：1)

明天跑路去冬令营

期末考试完炸

现在一个人瑟瑟发抖得在机房刷题…… 可怜兮兮

本题的题意简要概述一下：

对于给定的n个点的横纵坐标，求出两两组合的不同的斜率的总数；

set进行自动去重 

有两个坑点说明一下：

1.注意斜率不存在的情况的特判 除0的结果好像是一些奇奇怪怪的东西……

斜率不存在时应该算一条直线 所以用pp标记一下 最后输出结果的时候加上pp即可

2.斜率是小数 double 而计算斜率的时候用的坐标值都是int 所以除下来的结果就

整数…… 于是乎就爆掉了 qaq 

整型计算浮点型要乘1.0

整型计算浮点型要乘1.0

整型计算浮点型要乘1.0

~~重要的事情说三遍~~

→_→

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,pp;
struct p{
    int x,y;
}a[210];
set<double> p;
int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++){
            if (i==j) continue;
            if (a[i].x==a[j].x) pp=1;
                else p.insert(1.0*(a[i].y-a[j].y)/(a[i].x-a[j].x));
        }
    printf("%d\n",p.size()+pp);
    return 0;
}
```


---

## 作者：ljc20020730 (赞：1)

虽然是水题但是还有值得注意的地方，

这道题考察的枚举的思想，稍带快速排序去重的思想。

所以整个题目难度不大，卡数据的点几乎没有，AC也是比较容易的 。

和楼下一样，思路就是枚举每两点坐标，求出斜率k对k进行去重排序，得出答案。

在这里我需要提醒各位三点：

- 两点的x坐标相等的时候（如果不注意k=0），即其与y轴平行，也还是可以画的

- 两点的y坐标相等的时候（如果不注意pas要200），即其与x轴平行，也还是可以画的

- 两点重合时，上述两条均失效。

所以枚举题还是要认真的，但是（数据太水）貌似不考虑上述三点也还是能过的。

强烈要求增加数据，这里我给各位出一组样例：

```cpp
input#11
8
1 1
1 1
2 1
2 4
1 4
1 6
4 7
8 9
output#11
16
```

---

