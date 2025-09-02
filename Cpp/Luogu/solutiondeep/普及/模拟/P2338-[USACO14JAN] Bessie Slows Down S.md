# 题目信息

# [USACO14JAN] Bessie Slows Down S

## 题目背景

奶牛题


## 题目描述

Bessie the cow is competing in a cross-country skiing event at the winter Moolympic games.  She starts out at a speed of 1 meter per second. However, as she becomes more tired over time, she begins to slow down. Each time Bessie slows down, her speed decreases: she moves at 1/2 meter per second after slowing down once, then 1/3 meter per second after slowing down twice, and so on.

You are told when and where Bessie slows down, in terms of a series of events.  An event like this:

T 17
means that Bessie slows down at a specific time -- here, 17 seconds into the race.  An event like this:

D 10
means that Bessie slows down at a specific distance from the start -- in this case, 10 meters.

Given a list of N such events (1 <= N <= 10,000), please compute the amount of time, in seconds, for Bessie to travel an entire kilometer.  Round your answer to the nearest integer second (0.5 rounds up to 1).

贝西正在参加一项滑雪比赛。她从起点出发的时候，速度恒定为每秒 1 米。然而，随着比赛进程的增加，她会犯很多错误，每次失误都会使她的速度下降。当她第一次失误后，速度会下降到每秒1/2 米，第二次失误后，速度会下降到每秒 1/3 米，第 k 次失误后，速度会下降到每秒 1/(k + 1) 米。

约翰记录了贝西的所有失误，一共有 N 个。有两种失误，一种发生在比赛开始后的某个时间点，另一种发生在赛道的某个位置上。有时，贝西可能在某个时间点到达某个位置，而恰好在这个时间点和位置上都有一次失误的记录，这两个记录要算作不同的失误，会对贝西的速度造成两次影响。比赛的终点距离起点有 1000 米，请问贝西需要多少时间才能滑过终点？


## 说明/提示

前 10 秒，贝西的速度是每秒 1 米，她滑了 10 米。然后她遭遇了第一次失误，在接下

来的 20 秒内，她又滑了 10 米。之后她遭遇了第二次失误，还剩下 980 米，所以她共计花去

10 + 20 + 2940 = 2970 秒才完成比赛


## 样例 #1

### 输入

```
2
T 30
D 10```

### 输出

```
2970```

# AI分析结果

• 综合分析与结论：这些题解思路大致相同，均先将T（时间）和D（距离）事件分开存储并排序，再通过比较下一个T事件和D事件，按规则更新路程、时间和速度，直至到达1000米处，最后四舍五入输出总时间。主要难点在于正确处理T和D事件的先后顺序及相应的速度、路程和时间更新逻辑。各题解质量参差不齐，思路清晰度、代码可读性和优化程度有所差异。
  - 作者LevenKoko（5星）
    - 关键亮点：思路清晰，代码注释详细，对T和D事件的处理逻辑明确，考虑到边界情况，在数组末尾添加极大值防止循环异常。
    - 重点代码及核心思想：
```cpp
// 分别读入T和D事件
for(int i=1;i<=n;i++)
{
    cin>>chr;
    if(chr=='T') cin>>t[++lt];
    else cin>>d[++ld];
}
sort(t+1,t+lt+1);
sort(d+1,d+ld+1);
// 处理边界情况
d[ld+1]=0x3f3f3f3f;
t[lt+1]=0x3f3f3f3f;
int i=1,j=1;
while(i<=lt||j<=ld)
{
    v1=1.0/v;
    st=s+(t[i]*1.0-tot)*v1;
    sd=d[j];
    if(st<sd)
    {
        s=st;
        tot=t[i];
        i++;
    }
    else
    {
        tot+=(sd-s)/v1;
        s=sd;
        j++;
    }
    v++;
}
// 加上剩余路程所需时间
tot+=(1000-s)/(1.0/(v*1.0));
cout<<int(tot+0.5);
```
核心思想是通过比较按时间和按距离计算出的路程，决定先处理T事件还是D事件，更新路程和时间，并调整速度，最后计算剩余路程时间并四舍五入输出。
  - 作者Yeji_ （4星）
    - 关键亮点：代码简洁，逻辑连贯，以简洁的方式实现了模拟过程，通过for循环和条件判断处理T和D事件。
    - 重点代码及核心思想：
```cpp
for (int i=1;i<=n;i++)
    if ((r>tot2||(b[r]-y)*x+z>=a[l])&&(l<=tot1))
    {
        if ((a[l]-z)/x+y>1000)
            break;
        y+=(a[l]-z)/x;
        z=a[l];x++;
        l++;
    }
    else
    {
        if (b[r]>1000)
            break;
        z+=(b[r]-y)*x;
        y=b[r];
        x++;
        r++;
    }
cout<<int((1000-y)*x+z+0.499999);
```
核心思想是在循环中通过比较当前位置到下一个D事件位置和下一个T事件时间的关系，决定处理T还是D事件，更新路程、时间和速度，最后计算剩余路程时间并四舍五入输出。
  - 作者moosssi（4星）
    - 关键亮点：思路表述清晰，通过依次枚举D数组元素，在每个D元素区间内处理T事件，逻辑较为直观。
    - 重点代码及核心思想：
```cpp
for(int i=1;i<=D[0];i++){
    double temp=(T[j]-tim)*1.0*(1/k)+pos;
    while(temp<=D[i]&&j<=T[0]){
        tim=T[j++],pos=temp,k++;
        temp=(T[j]-tim)*1.0*(1/k)+pos;
    }
    tim+=(D[i]-pos)*1.0/(1/k);
    pos=D[i],k++;
}
double temp=(T[j]-tim)*1.0*(1/k)+pos;
while(temp<=1000&&j<=T[0]){
    tim=T[j++],pos=temp,k++;
    temp=(T[j]-tim)*1.0*(1/k)+pos;
}
if(pos<1000)tim+=(1000-pos)*k;
printf("%d",(int)(tim+0.5)); 
```
核心思想是先枚举D事件，在每个D事件区间内处理T事件，更新位置、时间和速度，若未到达终点，继续处理剩余T事件，最后计算剩余路程时间并四舍五入输出。

• 最优关键思路或技巧：将T和D事件分开存储排序，通过比较下一个T和D事件对路程、时间和速度进行更新，注意边界处理和四舍五入。

• 可拓展之处：同类型题可涉及不同条件下的速度变化模拟，类似算法套路为对不同类型事件分类处理，按特定规则更新状态。

• 相似知识点洛谷题目：
  - P1035 [NOIP2002 普及组] 级数求和
  - P1909 [NOIP2016 普及组] 买铅笔
  - P1161 开灯

• 个人心得摘录及总结：
  - 作者zhangbubu提到未对时间和位置排序导致只ac第一个点，强调了排序在本题的重要性。总结为处理此类按顺序处理事件的题目，要注意对事件相关数据进行合理排序。 

---
处理用时：47.94秒