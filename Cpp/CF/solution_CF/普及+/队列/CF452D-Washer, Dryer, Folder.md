# Washer, Dryer, Folder

## 题目描述

You have $ k $ pieces of laundry, each of which you want to wash, dry and fold. You are at a laundromat that has $ n_{1} $ washing machines, $ n_{2} $ drying machines and $ n_{3} $ folding machines. Each machine can process only one piece of laundry at a time. You can't dry a piece of laundry before it is washed, and you can't fold it before it is dried. Moreover, after a piece of laundry is washed, it needs to be immediately moved into a drying machine, and after it is dried, it needs to be immediately moved into a folding machine.

It takes $ t_{1} $ minutes to wash one piece of laundry in a washing machine, $ t_{2} $ minutes to dry it in a drying machine, and $ t_{3} $ minutes to fold it in a folding machine. Find the smallest number of minutes that is enough to wash, dry and fold all the laundry you have.

## 说明/提示

In the first example there's one instance of each machine, each taking 5 minutes to complete. You have only one piece of laundry, so it takes 15 minutes to process it.

In the second example you start washing first two pieces at moment $ 0 $ . If you start the third piece of laundry immediately, then by the time it is dried, there will be no folding machine available, so you have to wait, and start washing third piece at moment $ 2 $ . Similarly, you can't start washing next piece until moment $ 5 $ , since otherwise there will be no dryer available, when it is washed. Start time for each of the eight pieces of laundry is $ 0,0,2,5,10,10,12 $ and $ 15 $ minutes respectively. The last piece of laundry will be ready after $ 15+10+5+2=32 $ minutes.

## 样例 #1

### 输入

```
1 1 1 1 5 5 5
```

### 输出

```
15
```

## 样例 #2

### 输入

```
8 4 3 2 10 5 2
```

### 输出

```
32
```

# 题解

## 作者：灵茶山艾府 (赞：9)

### 思路

由于每个洗衣机的用时都是一样的，不妨规定按照【第 $0$ 个洗衣机 $\rightarrow$ 第 $1$ 个洗衣机 $\rightarrow$ 第 $2$ 个洗衣机 $\rightarrow\cdots \rightarrow$ 第 $n_1-1$ 个洗衣机 $\rightarrow$ 第 $0$ 个洗衣机 $\rightarrow$ 第 $1$ 个洗衣机$\rightarrow\cdots$】的顺序使用。其它机器同理。

用 $f_1[x]$ 表示第 $x$ 个洗衣机洗完一件衣服的结束时间。其它机器同理，用 $f_2$ 和 $f_3$ 表示。

对于第 $i$ 件衣服，按照上面的规则，用第 $i\bmod n_1$ 个洗衣机，第 $i\bmod n_2$ 个烘干机，第 $i\bmod n_3$ 个熨斗。

考虑到中途不能停留，所以结束时间 $\textit{finish}$ 为 

$$
\max(f_1[i\bmod n_1]+t_1+t_2+t_3, f_2[i\bmod n_2]+t_2+t_3, f_3[i\bmod n_3]+t_3)
$$

然后更新

$$
\begin{aligned}
&f_1[i\bmod n_1] = \textit{finish} - t_2 - t_3\\
&f_2[i\bmod n_2] = \textit{finish} - t_3\\
&f_3[i\bmod n_3] = \textit{finish}
\end{aligned}
$$

答案为洗完最后一件衣服的结束时间。

### 复杂度分析

- 时间复杂度：$\mathcal{O}(k+n_1+n_2+n_3)$。
- 空间复杂度：$\mathcal{O}(n_1+n_2+n_3)$。

### AC 代码（Golang）

```go
package main
import . "fmt"
func max(a, b int) int { if b > a { return b }; return a }

func main() {
	var k, n1, n2, n3, t1, t2, t3, finish int
	Scan(&k, &n1, &n2, &n3, &t1, &t2, &t3)
	f1 := make([]int, n1)
	f2 := make([]int, n2)
	f3 := make([]int, n3)
	for i := 0; i < k; i++ {
		finish = max(max(f1[i%n1]+t1+t2+t3, f2[i%n2]+t2+t3), f3[i%n3]+t3)
		f1[i%n1] = finish - t2 - t3
		f2[i%n2] = finish - t3
		f3[i%n3] = finish
	}
	Print(finish)
}
```


---

## 作者：zhoukangyang (赞：9)

这题哪里有那么难，就是动态规划

我们考虑每样物品的**开始时间**

我们用$dp[i]$储存处理第$i$件物品的开始时间

很容易想到一开始处理$min(na,nb,nc)$的开始时间为零

于是考虑处理第$i$件物品，他处理的开始时间最少要：

1.第$i$件物品至少比第$i-na$件物品多用$ta$的时间，因为同时间最多处理$na$件物品，处理完第$i-na$件物品才能处理第$i$件物品。

2.第$i$件物品至少比第$i-nb$件物品多用$tb$的时间,同理，因为同时间最多处理$nb$件物品，处理完第$i-nb$件物品才能处理第$i$件物品。

3.第$i$件物品至少比第$i-nc$件物品多用$tc$的时间,也是一样的，因为同时间最多处理$nc$件物品，处理完第$i-nc$件物品才能处理第$i$件物品。

由于计算的是开始时间，所以最后$dp[k]$要加上$(ta+tb+tc)$

$Code$(加反作弊)：

```cpp
#include<bits/stdc++.h>
using namespace std;
int k,na,nb,nc,ta,tb,tc,dp[111111];
int mian() {
    scanf("%d%d%d%d%d%d%d",&k,&na,&nb,&nc,&ta,&tb,&tc);
    for(int i = 1; i <= k; i++){
        if(i>na) dp[i]=max(dp[i],dp[i-na]+ta);
        if(i>nb) dp[i]=max(dp[i],dp[i-nb]+tb);
        if(i>nc) dp[i]=max(dp[i],dp[i-nc]+tc);
    }
    printf("%d\n",dp[k]+ta+tb+tc);
	return 0;
}
```


---

## 作者：AK_400 (赞：1)

贪心+模拟。

因为每个同步的机器用时是一样的，所以一定是有空位就放。

然后我们枚举当前时间，开三个 deque/priority_queue/multiset 维护每步中每台被占用的机器处理好的时间即可。

为方便，可以选择维护若此时刻放入衣服，轮到这件衣服时恰好结束上次处理的时间。

一个小优化：因为有很多时间是没有机器处理完成且没有空位的，我们可以直接跳过。

复杂度：$O(k\log(k))$  或 $O(k)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int k,n1,n2,n3,t1,t2,t3;
multiset<pair<int,int>>m1,m2,m3;//分别表示结束时间和机器个数
int sum1,sum2,sum3;//被使用的机器个数
void slv(){
    cin>>k>>n1>>n2>>n3>>t1>>t2>>t3;
    int t=0;
    while(k>0){
        if(m1.size()&&m1.begin()->first==t){
            sum1+=m1.begin()->second;
            m1.erase(m1.begin());
        }
        if(m2.size()&&m2.begin()->first==t){
            sum2+=m2.begin()->second;
            m2.erase(m2.begin());
        }
        if(m3.size()&&m3.begin()->first==t){
            sum3+=m3.begin()->second;
            m3.erase(m3.begin());
        }
        int n=min({n1-sum1,n2-sum2,n3-sum3});//能放就放
        m1.insert({t+t1,-n});
        m2.insert({t+t2,-n});
        m3.insert({t+t3,-n});
        sum1+=n,sum2+=n,sum3+=n;
        k-=n;
        if(k>0)
        t=min({m1.begin()->first,m2.begin()->first,m3.begin()->first});//跳到最早结束的机器的结束时间
    }
    cout<<t+t1+t2+t3;//开始处理就减去，所以要加上最后处理的衣服的时间
}
int main(){
    slv();
    return 0;
}
```

---

## 作者：enyyyyyyy (赞：0)

这题是一道数学题，只要考虑最有效的利用时间，由于每个洗衣机，烘干机和熨斗的用时都是一样的，所以可以开 $3$ 个优先队列，维护每一个洗衣机，在何时会有一件衣服洗完。可以提前处理把所有优先队列先初始为 $0$。用 `max(q1.top(),max(q2.top()-x,q3.top()-x-y))` 记录最大值，以保存答案。

```cpp
#include <bits/stdc++.h>
#define ll long long//不开long long见祖宗 
#define lint __int128
using namespace std;
inline ll read() {//快读
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}
inline void print(ll x) {//快写
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x >= 10)
		print(x / 10);
	putchar(x % 10 + '0');
	return;
}
ll n,a,b,c,x,y,z,ans;
priority_queue<ll,vector<ll>,greater<ll> >q1,q2,q3;//优先队列 
int main(){
	n=read(),a=read(),b=read(),c=read(),x=read(),y=read(),z=read();//快读解决一切 
	for(ll i=1;i<=a;i++) q1.push(0);//预处理
	for(ll i=1;i<=b;i++) q2.push(0);
	for(ll i=1;i<=c;i++) q3.push(0);
	for(ll i=1;i<=n;i++){
		ll op=max(q1.top(),max(q2.top()-x,q3.top()-x-y));//求出最大值 
		q1.pop(),q2.pop(),q3.pop();//把对队头弹出 
		q1.push(op+x),q2.push(op+x+y),q3.push(op+x+y+z);//把对下一轮的队头压入 
		ans=op+x+y+z;//记录答案 
	}
	print(ans);//输出 
	return 0;
} 	 	   	   							 			 	  	  	
```

致谢：[残阳如血](/user/726139)帮忙修改错误。

---

## 作者：ZJMZJM (赞：0)

用3个优先队列; 

维护每一种洗衣机,在何时是处于空闲状态的;(即什么时候会有一件衣服操作完); 

每次将时间跳转到; 

min{q1.top(),q2.top(),q3.top()}; 

然后将操作完的衣服放入下一步骤; 

然后将正在等待操作的衣服;如果能放入对应的洗衣机,就放入;

```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<queue>//头文件
#define For(k,i,j) for(int k=i;k<=j;k++)//for循环
#define ll long long
#pragma GCC optimize(4)//O4
using namespace std;
inline int read()
{
    char ch;
    int res=1;
    while((ch=getchar())<'0'||ch>'9') if(ch=='-') res=-1;
    res*=ch-48;
    while((ch=getchar())>='0'&&ch<='9')
        res=res*10+ch-48;
    return res;
}//快读
const int INF=0x7fffffff;
int w1,w2,w3;
priority_queue <int,vector<int>,greater<int> > q1,q2,q3;
int main()
{
	int k=read(),n1=read(),n2=read(),n3=read(),t1=read(),t2=read(),t3=read(),ans;
    w1=k;
    q1.push(INF),q2.push(INF),q3.push(INF);
    while(w1||w2||w3||(int)q1.size()>1||(int)q2.size()>1||(int)q3.size()>1)
	{
        ans=min(q1.top(),min(q2.top(),q3.top()));
        if(ans==INF) 
			ans=0;
        while(q1.top()<=ans)
		{
            q1.pop();
            w2++;
        }
        while(q2.top()<=ans)
		{
            q2.pop();
            w3++;
        }
        while(q3.top()<=ans)
		{
            q3.pop();
        }
        while(w1&&(int)q1.size()<=n1)
		{
            w1--;
            q1.push(ans+t1);
        }
        while(w2&&(int)q2.size()<=n2)
		{
            w2--;
            q2.push(ans+t2);
        }
        while(w3&&(int)q3.size()<=n3)
		{
            w3--;
            q3.push(ans+t3);
        }
    }
    printf("%d\n",ans);//输出
    return 0;
}
```

---

## 作者：AdzearDisjudge (赞：0)

显然我们能加入一件衣服的条件是：

**当前洗衣机有空闲。**

**t1时间后烘干机有空闲。**

**t1+t2时间后熨斗有空闲。**

所以考虑分别维护这三种机器下一个有空闲的时间点。

显然地，我们要保存所有衣服的状态，因为当前衣服进入下一个机器或走完流程后，下一件衣服处理完毕的时间就成为了最早空闲的时间点。

所以我们列举出要维护的数据：

1.当前机器被使用的个数。（如果不满ni，意味着下一件衣服可以直接放入该机器而不必考虑第一件是否处理完毕）

2.当前机器最早空闲的时间点。（如果机器没满，显然已经空闲；否则就是最早放入的衣服放入时间点+ti）

3.所有衣服处理完毕的时间。这可以用放入的时间+ti直接得到。

综上，我们考虑使用三个双向队列每次维护三个机器最晚的最早空闲时间点,在这个时间点插入新衣服，并将它的处理完毕时间点加入。注意后面两个机器如果在t时间空闲，意味着在t-t1（烘干机）或t-t1-t2（熨斗）时间就可以将衣服放入洗衣机，因此加入到这两个队列中的数据要分别减去t1，t1+t2。

最后的答案就是最后一件衣服处理完毕的时间。

实际上似乎用队列就可以了，不过用双向队列的正确姿势是对于没满的机器在开头补足0，然后就可以直接比较三个开头的时间。我这里是先用size()和ni作比较确定是否满，再去比较开头。~~（其实我觉得没啥区别）~~

~~反正这题也没人做，写着开心就好~~

代码：

```cpp

#include<bits/stdc++.h>
#define rep(i,a,n) for(register int i=a;i<=n;++i)
#define mi min(n1,min(n2,n3))
#define ma max(q1,max(q2,q3)) 
using namespace std;
deque<int>w,d,f;
int k,n1,n2,n3,t1,t2,t3,q1,q2,q3,mo;
int main()
{
    cin>>k>>n1>>n2>>n3>>t1>>t2>>t3;
    rep(i,1,mi)
    {
        w.push_back(t1);
        d.push_back(t1+t2);
        f.push_back(t1+t2+t3);
    }
    rep(i,mi+1,k)
    {
        q1=w.at(0);
        q2=d.at(0)-t1;
        q3=f.at(0)-t1-t2;
        if(w.size()<n1)
        q1=0;
        if(d.size()<n2)
        q2=0;
        if(f.size()<n3)
        q3=0;
        mo=ma;
        if(!(w.size()<n1))
        w.pop_front();
        if(!(d.size()<n2))
        d.pop_front();
        if(!(f.size()<n3))
        f.pop_front();
        w.push_back(mo+t1);
        d.push_back(mo+t1+t2);
        f.push_back(mo+t1+t2+t3);
    }
    cout<<f.back();
    return 0;
}

```

---

