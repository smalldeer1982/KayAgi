# The Queue

## 题目描述

Finally! Vasya have come of age and that means he can finally get a passport! To do it, he needs to visit the passport office, but it's not that simple. There's only one receptionist at the passport office and people can queue up long before it actually opens. Vasya wants to visit the passport office tomorrow.

He knows that the receptionist starts working after $ t_{s} $ minutes have passed after midnight and closes after $ t_{f} $ minutes have passed after midnight (so that $ (t_{f}-1) $ is the last minute when the receptionist is still working). The receptionist spends exactly $ t $ minutes on each person in the queue. If the receptionist would stop working within $ t $ minutes, he stops serving visitors (other than the one he already serves).

Vasya also knows that exactly $ n $ visitors would come tomorrow. For each visitor Vasya knows the point of time when he would come to the passport office. Each visitor queues up and doesn't leave until he was served. If the receptionist is free when a visitor comes (in particular, if the previous visitor was just served and the queue is empty), the receptionist begins to serve the newcomer immediately.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767B/21e6fa9f8076fbac8e8f856cf43d41d3ac4208dc.png)"Reception 1"For each visitor, the point of time when he would come to the passport office is positive. Vasya can come to the office at the time zero (that is, at midnight) if he needs so, but he can come to the office only at integer points of time. If Vasya arrives at the passport office at the same time with several other visitors, he yields to them and stand in the queue after the last of them.

Vasya wants to come at such point of time that he will be served by the receptionist, and he would spend the minimum possible time in the queue. Help him!

## 说明/提示

In the first example the first visitor comes exactly at the point of time when the receptionist begins to work, and he is served for two minutes. At 12 minutes after the midnight the receptionist stops serving the first visitor, and if Vasya arrives at this moment, he will be served immediately, because the next visitor would only come at 13 minutes after midnight.

In the second example, Vasya has to come before anyone else to be served.

## 样例 #1

### 输入

```
10 15 2
2
10 13
```

### 输出

```
12```

## 样例 #2

### 输入

```
8 17 3
4
3 4 5 8
```

### 输出

```
2```

# 题解

## 作者：A_zjzj (赞：2)

### 一道贪心题

如果有两个人分别在 $x$ 和 $y$ 来（ $x<y$ 且这两个人来的时刻的中间没有其他人）

那么 $Vasya$ 从 $x+m$ 到 $y-1$ 这段时间来都一样。

那么我们就枚举每一个人，然后看看如果$Vasya$在这个人之前插进去最少要等多长时间，更新答案就可以了

### 代码


```cpp
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
int n;
ll s,e,m,x;
ll ans,minx,last;//答案,最少要等多长时间,上一个人什么时候结束
int main(){
	scanf("%lld%lld%lld%d",&s,&e,&m,&n);
	ans=minx=1e15;
	for(int i=1;i<=n;i++){
		scanf("%lld",&x);
		if(x==0||x+m>e)continue;
		last=max(x-1,s);//更新这一次Vasya要从哪里插进去
		if(last+m<=e&&s-(x-1)<=minx){//比答案更优,更新
			minx=s-(x-1);
			ans=min(s,x-1);
		}
		s=max(x,s)+m;//更新上一个人的结束时间
	}
	if(s+m<=e)ans=s;//如果到了最后没有人去排队，那么Vasya就在这个时候去
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：No21 (赞：0)

## 解题分析

一道模拟加贪心的题目，$Vasya$ 的等待时间会被服务开始时间 $Ts$，服务结束时间 $Tf$ 和每个人来的时间影响。

前两个的处理非常简单，而人数 $n$ 最多只有 $100000$，因此我们选择枚举 $Vasya$ 在某个人之前来。

这里不难发现，若 $Vasya$ 在第 $i$ 个人之后来且第 $i$ 个人来的时间为 $p_i$，则 $Vasya$ 在 $p_i-1$ 时刻来等待时间最少，因此我们枚举 $Vasya$ 在每个 $p_i-1$ 时刻来需要等待多长时间。

## 特判

- 若最后一个人结束后留出的时间大于等于服务需要时间 $t$，则 $Vasya$ 可以在最后一个人结束后来。

- 若第一个人来的时间晚于服务开始时间 $Ts$，则 $Vasya$ 可以在 $Ts$ 时来。

- 若第 $i$ 个人来的时间 $p_i$ 晚于第 $i-1$ 个人结束的时间 $en_{i-1}$，则 $Vasya$ 可以在 $en_{i-1}+1$ 时间来。

- 若一个人来的时间晚于 $Tf$，则他只是来闲逛了一圈，不用管他。


------------

上代码

注：代码中的 $en_i$ 指的是第 $i$ 个人**结束后**的时间，等价于上文的 $en_i+1$。

```
#include<bits/stdc++.h>
using namespace std;
namespace TO
{
    const int N=1e5+21;
    long long ans,ts,tf,t,n;
    long long f[N],p[N],en[N];
    int mian()
    {
        cin>>ts>>tf>>t>>n;
        if(n==0)
        {
            cout<<ts;
            return 0;
        }
        for(int i=1;i<=n;i++)
        {
            cin>>p[i];
            if(p[i]+t>tf)
            {
                p[i]=0;
                break;
            }
        }
        en[1]=max(p[1],ts)+t;
        f[0]=1e12;
        for(int i=2;i<=n;i++)
            en[i]=max(p[i],en[i-1])+t;
        if(en[n]+t<=tf)
        {
            cout<<en[n];
            return 0;
        }
        if(p[1]>ts)
        {
            cout<<ts;
            return 0;
        }
        else
            f[1]=ts-p[1]+1;
        for(int i=2;i<=n;i++)
        {
            if(p[i]>tf)
                break;
            if(p[i]>en[i-1])
            {
                cout<<en[i-1];
                return 0;
            }
            else
                f[i]=en[i-1]-p[i]+1;
        }
        for(int i=1;i<=n;i++)
        {
            if(p[i]-1>tf)
                break;
            if(f[0]>f[i])
            {
                ans=p[i]-1;
                f[0]=f[i];
            }
        }
        cout<<ans;
        return 0;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    return TO::mian();
}
```

---

