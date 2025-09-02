# Teamwork

## 题目描述

As soon as SWERC starts, your experienced $ 3 $ -person team immediately realizes that the contest features $ a $ easy problems, $ b $ medium problems, and $ c $ hard problems. Solving a problem will take any of you $ 2 $ , $ 3 $ , or $ 4 $ time units, depending on whether the problem is easy, medium, or hard. Regardless of the difficulty of the problem, the last time unit spent to solve it has to be spent using your shared computer.

You organize your efforts so that each of you starts (and ends) solving problems at integer time units. Any given problem can be solved by only one contestant; it requires a contiguous amount of time (which depends on the difficulty of the problem). None of the $ 3 $ of you can solve more than one problem at a time, but you can start solving a new problem immediately after finishing one. Similarly, the shared computer cannot be used by more than one of you at a time, but any of you can start using the computer (to complete the problem currently being solved) immediately after someone else stops using it.

Given that the contest lasts $ l $ time units, find the maximum number of problems that your team can solve. Additionally, find one way to solve the maximum number of problems.

## 说明/提示

In the first sample, the first contestant solves an easy problem between time $ 0 $ and time $ 2 $ while the second contestant solves a medium problem between time $ 0 $ and time $ 3 $ .

In the second sample, the first contestant solves an easy problem between time $ 0 $ and time $ 2 $ , and then also solves a medium problem between time $ 2 $ and time $ 5 $ . In the meantime, the second contestant solves another medium problem between time $ 0 $ and time $ 3 $ , while the third contestant solves a hard problem between time $ 0 $ and time $ 4 $ .

In the third sample, the contest only has medium and hard problems, and there is not enough time to solve any of them.

## 样例 #1

### 输入

```
2 1 1 3```

### 输出

```
2
1 0 2
2 0 3```

## 样例 #2

### 输入

```
1 2 3 5```

### 输出

```
4
1 0 2
2 0 3
3 0 4
1 2 5```

## 样例 #3

### 输入

```
0 1 2 2```

### 输出

```
0```

# 题解

## 作者：caizhetong (赞：6)

### 题目简述

有三个人和 $a$ 道简单题，$b$ 道中等难度题和 $c$ 道高难度题。已知做三种题的时间分别为 $2,3,4$。每个人在一个时间内只能做一道题，且在做一道题的最后一个单位时间要使用超级计算机，一个超级计算机在一个时间内只能给一个人用。问在 $l$ 个时间内他们总共最多能做多少道题，并给出构造方案。

### 解决方案

枚举在每个时间超级计算机会处理谁的难度为什么的题。优先做难题，优先选择做上到题的时间离现在近的人。

根据贪心思想若能做难题，则一定能做简单题，但能做简单题不一定能做难题，所以能做难题时要先做难题。设一个做上一道题的时间距离现在近的人为 $a$ 人，一个做上一道题的时间距离现在远的人为 $b$ 人，若一道题 $a$ 能做则 $b$ 一定能做，但是一道题 $b$ 能做 $a$ 能做，所以若 $a$ 能做这题则优先选择 $a$。

### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
long long a,b,c,l,cnt;
struct gz{
    long long l,id;
}t[10];
struct tx{
    long long a,b,c;
}ans[1000010];
bool px(gz a,gz b)
{
    if(a.l>b.l) return true;
    if(a.l<b.l) return false;
    return false;
}
signed main()
{
    //freopen("ti.in","r",stdin);
    //freopen("ti.out","w",stdout);
    //ios::sync_with_stdio(0);

    cin>>a>>b>>c>>l;t[1].id=1;t[2].id=2;t[3].id=3;
    for(int i=1;i<=l;i++)
    {
        sort(t+1,t+4,px);
        int tag=0;
        if(c!=0)
        {
            for(int j=1;j<=3;j++)
            {
                if(i-4>=t[j].l)
                {
                    c--;cnt++;
                    ans[cnt].a=t[j].id;
                    ans[cnt].b=i-4;
                    ans[cnt].c=i;
                    t[j].l=i;tag=1;
                    break;
                }
            }
        }
        if(tag==1) continue;
        if(b!=0)
        {
            for(int j=1;j<=3;j++)
            {
                if(i-3>=t[j].l)
                {
                    b--;cnt++;
                    ans[cnt].a=t[j].id;
                    ans[cnt].b=i-3;
                    ans[cnt].c=i;
                    t[j].l=i;tag=1;
                    break;
                }
            }
        }
        if(tag==1) continue;
        if(a!=0)
        {
            for(int j=1;j<=3;j++)
            {
                if(i-2>=t[j].l)
                {
                    a--;cnt++;
                    ans[cnt].a=t[j].id;
                    ans[cnt].b=i-2;
                    ans[cnt].c=i;
                    t[j].l=i;
                    break;
                }
            }
        }
    }
    cout<<cnt<<"\n";
    for(int i=1;i<=cnt;i++) cout<<ans[i].a<<" "<<ans[i].b<<" "<<ans[i].c<<"\n";

    //fclose(stdin);
    //fclose(stdout);
	return 0;
}

```

---

