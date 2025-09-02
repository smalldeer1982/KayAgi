# 题目信息

# [USACO14JAN] Recording the Moolympics S

## 题目描述

Being a fan of all cold-weather sports (especially those involving cows),Farmer John wants to record as much of the upcoming winter Moolympics as possible.


The television schedule for the Moolympics consists of N different programs(1 <= N <= 150), each with a designated starting time and ending time.  FJ has a dual-tuner recorder that can record two programs simultaneously.

Please help him determine the maximum number of programs he can record in total.

农民约翰热衷于所有寒冷天气的运动（尤其是涉及到牛的运动）， 农民约翰想录下尽可能多的电视节目。 moolympics 的节目时间表有 $N$ 个不同的节目 （$1\le N\le 150$），每个节目给定开始时间和结束时间。FJ 有一个双调谐器录音机，可以同时录制两个节目。 请帮助他确定他能录制的节目的最大数量。


## 说明/提示

INPUT DETAILS:


The Moolympics broadcast consists of 6 programs.  The first runs from time 0 to time 3, and so on.


OUTPUT DETAILS:


FJ can record at most 4 programs.  For example, he can record programs 1 and 3 back-to-back on the first tuner, and programs 2 and 4 on the second tuner.


Source: USACO 2014 January Contest, Silver


## 样例 #1

### 输入

```
6
0 3
6 7
3 10
1 5
2 8
1 9```

### 输出

```
4```

# AI分析结果

### 综合分析与结论
本题要求在有两个调谐器的情况下，从给定的节目时间表中录制最多的节目，属于区间贪心或动态规划问题。大部分题解采用贪心策略，少数采用动态规划。

贪心题解的核心思路是先按节目结束时间排序，再遍历节目，尽量将节目安排到结束时间较晚的调谐器上，以保证每个调谐器的空闲时间最少。动态规划题解则通过定义状态和转移方程来求解最优解。

### 所选题解
- **作者：shadowice1984（5星）**
    - **关键亮点**：思路清晰，代码简洁，通过交换摄像机优先级将双摄像机问题转化为单摄像机问题，易于理解和实现。
    - **核心代码**：
```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
int n;
struct data
{
    int st;int ed;
    friend bool operator <(struct data a,struct data b)
    {
        if(a.ed==b.ed)return a.st>b.st;
        return a.ed<b.ed;
    }
}mis[150];
int now1=-1;int now2=-1;int res;
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d%d",&mis[i].st,&mis[i].ed);
    }
    sort(mis,mis+n);
    for(int i=0;i<n;i++)
    {
        if(now1<=mis[i].st)
        {
            res++;now1=mis[i].ed;
        }
        else if(now2<=mis[i].st)
        {
            res++;now2=mis[i].ed;
            swap(now1,now2);
        }
    }
    printf("%d",res);
    return 0;
}
```
    - **核心实现思想**：先按节目结束时间排序，遍历节目，优先使用第一台摄像机录制。若第一台摄像机无法录制，则使用第二台摄像机，并交换两台摄像机的优先级。

- **作者：onepeople666（4星）**
    - **关键亮点**：详细解释了区间贪心的思路，将本题与常见的区间贪心题进行对比，有助于理解。
    - **核心代码**：
```cpp
struct cow
{
  int s,e;
};
int cmp(cow a,cow b)
{
  if(a.e<b.e)
    return 1;
  return 0;
}
int main()
{
  int n;
  cin>>n;
  cow a[n+1];
  for(int i=1; i<=n; i++)
    cin>>a[i].s>>a[i].e;
  sort(a+1,a+n+1,cmp);
  int p1=0,p2=0;
  int c=0;
  for(int i=1; i<=n; i++)
  {
    if(a[i].s>=p1&&p1>p2||(a[i].s>=p1&&a[i].s<p2))
    {
      c++;
      p1=a[i].e;
    }
    else if(a[i].s>=p2)
    {
      c++;
      p2=a[i].e;
    }
  }
  cout<<c;
  return 0;
}
```
    - **核心实现思想**：定义结构体存储节目开始和结束时间，按结束时间排序。遍历节目，优先将节目安排到结束时间较晚的调谐器上，更新调谐器的结束时间。

- **作者：A_Đark_Horcrux（4星）**
    - **关键亮点**：将本题与经典的线段覆盖问题进行对比，思路清晰，代码简洁。
    - **核心代码**：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct A{int x,y;} a[2000000];
bool cmp(A x,A y){ return x.y<y.y;}
int n,s,l=-1,t=-1,i;
int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d %d",&a[i].x,&a[i].y);
	sort(a+1,a+n+1,cmp);
	for(i=1;i<=n;i++)
		if(a[i].x>=l) s++,l=a[i].y;
		else if(a[i].x>=t) s++,t=a[i].y,swap(l,t);	
	printf("%d",s);
	return 0;
}
```
    - **核心实现思想**：按节目结束时间排序，遍历节目，先尝试用第一个调谐器录制，若无法录制则用第二个调谐器录制，并交换两个调谐器的结束时间。

### 最优关键思路或技巧
- **贪心策略**：按节目结束时间排序，优先将节目安排到结束时间较晚的调谐器上，可使每个调谐器的空闲时间最少，从而录制更多节目。
- **交换优先级**：在使用第二个调谐器录制节目后，交换两个调谐器的优先级，将问题转化为单摄像机问题，简化逻辑。

### 可拓展之处
同类型题或类似算法套路：
- 多区间覆盖问题：给定多个区间和多个资源，要求用最少的资源覆盖所有区间。
- 活动选择问题：给定多个活动的开始和结束时间，要求选择最多的活动参加。

### 推荐题目
- P1803 凌乱的yyy / 线段覆盖
- P2970 自私的放牧
- P1233 木棍加工

### 个人心得
- **作者：Expecto**：第一次题解Wa了3个点，说明在贪心算法实现过程中容易出现细节错误，需要仔细调试。
- **作者：meowla**：动规的状态定义和方程式很难想，做过类似的双调动规题会好很多，强调了刷题积累经验的重要性。 

---
处理用时：38.10秒