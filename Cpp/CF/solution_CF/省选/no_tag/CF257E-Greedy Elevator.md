# Greedy Elevator

## 题目描述

The $ m $ -floor $ (m>1) $ office of international corporation CodeForces has the advanced elevator control system established. It works as follows.

All office floors are sequentially numbered with integers from 1 to $ m $ . At time $ t=0 $ , the elevator is on the first floor, the elevator is empty and nobody is waiting for the elevator on other floors. Next, at times $ t_{i} $ $ (t_{i}>0) $ people come to the elevator. For simplicity, we assume that one person uses the elevator only once during the reported interval. For every person we know three parameters: the time at which the person comes to the elevator, the floor on which the person is initially, and the floor to which he wants to go.

The movement of the elevator between the floors is as follows. At time $ t $ ( $ t>=0 $ , $ t $ is an integer) the elevator is always at some floor. First the elevator releases all people who are in the elevator and want to get to the current floor. Then it lets in all the people waiting for the elevator on this floor. If a person comes to the elevator exactly at time $ t $ , then he has enough time to get into it. We can assume that all of these actions (going in or out from the elevator) are made instantly. After that the elevator decides, which way to move and at time $ (t+1) $ the elevator gets to the selected floor.

The elevator selects the direction of moving by the following algorithm.

- If the elevator is empty and at the current time no one is waiting for the elevator on any floor, then the elevator remains at the current floor.
- Otherwise, let's assume that the elevator is on the floor number $ x $ $ (1<=x<=m) $ . Then elevator calculates the directions' "priorities" $ p_{up} $ and $ p_{down} $ : $ p_{up} $ is the sum of the number of people waiting for the elevator on the floors with numbers greater than $ x $ , and the number of people in the elevator, who want to get to the floors with the numbers greater than $ x $ ; $ p_{down} $ is the sum of the number of people waiting for the elevator on the floors with numbers less than $ x $ , and the number of people in the elevator, who want to get to the floors with the numbers less than $ x $ . If $ p_{up}>=p_{down} $ , then the elevator goes one floor above the current one (that is, from floor $ x $ to floor $ x+1 $ ), otherwise the elevator goes one floor below the current one (that is, from floor $ x $ to floor $ x-1 $ ).

Your task is to simulate the work of the elevator and for each person to tell the time when the elevator will get to the floor this person needs. Please note that the elevator is large enough to accommodate all the people at once.

## 说明/提示

In the first sample the elevator worked as follows:

- $ t=1 $ . The elevator is on the floor number $ 1 $ . The elevator is empty. The floor number $ 2 $ has one person waiting. $ p_{up}=1+0=1,p_{down}=0+0=0,p_{up}>=p_{down} $ . So the elevator goes to the floor number $ 2 $ .
- $ t=2 $ . The elevator is on the floor number $ 2 $ . One person enters the elevator, he wants to go to the floor number $ 7 $ . $ p_{up}=0+1=1,p_{down}=0+0=0,p_{up}>=p_{down} $ . So the elevator goes to the floor number $ 3 $ .
- $ t=3 $ . The elevator is on the floor number $ 3 $ . There is one person in the elevator, he wants to go to floor $ 7 $ . The floors number $ 4 $ and $ 6 $ have two people waiting for the elevator. $ p_{up}=2+1=3,p_{down}=0+0=0,p_{up}>=p_{down} $ . So the elevator goes to the floor number $ 4 $ .
- $ t=4 $ . The elevator is on the floor number $ 4 $ . There is one person in the elevator who wants to go to the floor number $ 7 $ . One person goes into the elevator, he wants to get to the floor number $ 8 $ . The floor number $ 6 $ has one man waiting. $ p_{up}=1+2=3,p_{down}=0+0=0,p_{up}>=p_{down} $ . So the elevator goes to the floor number $ 5 $ .
- $ t=5 $ . The elevator is on the floor number $ 5 $ . There are two people in the elevator, they want to get to the floors number $ 7 $ and $ 8 $ , correspondingly. There is one person waiting for the elevator on the floor number $ 6 $ . $ p_{up}=1+2=3,p_{down}=0+0=0,p_{up}>=p_{down} $ . So the elevator goes to the floor number $ 6 $ .
- $ t=6 $ . The elevator is on the floor number $ 6 $ . There are two people in the elevator, they want to get to the floors number $ 7 $ and $ 8 $ , correspondingly. One man enters the elevator, he wants to get to the floor number $ 5 $ . $ p_{up}=0+2=2,p_{down}=0+1=1,p_{up}>=p_{down} $ . So the elevator goes to the floor number $ 7 $ .
- $ t=7 $ . The elevator is on the floor number $ 7 $ . One person leaves the elevator, this person wanted to get to the floor number $ 7 $ . There are two people in the elevator, they want to get to the floors with numbers $ 8 $ and $ 5 $ , correspondingly. $ p_{up}=0+1=1,p_{down}=0+1=1,p_{up}>=p_{down} $ . So the elevator goes to the floor number $ 8 $ .
- $ t=8 $ . The elevator is on the floor number $ 8 $ . One person leaves the elevator, this person wanted to go to the floor number $ 8 $ . There is one person in the elevator, he wants to go to the floor number $ 5 $ . $ p_{up}=0+0=0,p_{down}=0+1=1,p_{up}<p_{down} $ . So the elevator goes to the floor number $ 7 $ .
- $ t=9 $ . The elevator is on the floor number $ 7 $ . There is one person in the elevator, this person wants to get to the floor number $ 5 $ . $ p_{up}=0+0=0,p_{down}=0+1=1,p_{up}<p_{down} $ . So the elevator goes to the floor number $ 6 $ .
- $ t=10 $ . The elevator is on the floor number $ 6 $ . There is one person in the elevator, he wants to get to the floor number $ 5 $ . $ p_{up}=0+0=0,p_{down}=0+1=1,p_{up}<p_{down} $ . So the elevator goes to the floor number $ 5 $ .
- $ t=11 $ . The elevator is on the floor number $ 5 $ . One person leaves the elevator, this person initially wanted to get to the floor number $ 5 $ . The elevator is empty and nobody needs it, so the elevator remains at the floor number $ 5 $ .

## 样例 #1

### 输入

```
3 10
1 2 7
3 6 5
3 4 8
```

### 输出

```
7
11
8
```

## 样例 #2

### 输入

```
2 10
1 2 5
7 4 5
```

### 输出

```
5
9
```

# 题解

## 作者：佬头 (赞：3)

# 题解 - 贪婪的电梯

[**佬夫的博客(空间跳跃)**](https://www.luogu.com.cn/blog/Glory-of-the-King/solution-cf257e)

## Description

鉴定为**中模拟**。

让你模拟一个[**公司的电梯**](https://www.luogu.com.cn/problem/CF257E)的运行，总共有 $n$ 名员工要求乘坐电梯，并且第 $i$ 名员工在时刻 $t_i$ 将于 $s_i$ 层楼等待并乘坐电梯前往 $f_i$ 层楼。

**1.** 电梯 $0$ 时刻在第 $1$ 层，一共有 $m$ 层楼（进出电梯不耗时）。

**2.** 当某一时刻 $t$，如果没有员工乘坐电梯或等待电梯，电梯会停留在原来所在的楼层；否则，若电梯在 $x$ 层楼，令 $p_{up}$ 表示电梯中要前往更高楼层以及在更高楼层等待的员工数，$p_{down}$ 电梯中要前往更低楼层以及在更低楼层等待的员工数。当 $p_{up}\geq p_{down}$ 时，电梯将在时刻 $t+1$ 来到楼层 $x+1$，否则电梯将前往楼层 $x-1$。

**题目要求**：输出每个人到目的地的时刻。

## Solution

定义**目标楼层**：当 $p_{up}\geq p_{down}$ 时，**表示**上方等待的员工所在的楼层和电梯中员工想前往的上方楼层中的最低楼层，否则**表示**下方等待的员工所在的楼层和电梯中员工想前往的下方楼层中的最高楼层。

**1.** **纯模拟**，不过需要加上**优先队列**优化，不然会 **TLE**。[这是一发 **TLE** 的代码](https://www.luogu.com.cn/record/119069918)，第 $6$ 个点就 **T** 飞了。

**2.** 由于输入并不按照 $t$ 的顺序，所以可以考虑**离线**处理，将员工按照 $t$ **从小到大**排序，然后就可以开始愉快的模拟了，更多细节在代码注释后方。

**3.** 电梯不用一层一层跳，这样铁定 **TLE** 。可以直接通过通过**楼层之差**或**时间之差**来让电梯进行跳跃。**楼层之差**：目标楼层和电梯当前所在楼层的差的绝对值，**时间之差**：下一位新员工来到电梯门口等待的时刻与此时的时刻之差。

**4.** 由于随时都有可能有新员工来到电梯门口等待，所以在跳往目标楼层时，先判断一下是否会有新员工来到电梯门口等待电梯 **——** 电梯的上下运行状态可能会因此而改变。

**5.** 对了，不开 `long long` 见祖宗！

```cpp
#include <queue> //考虑priority_queue优化
#include <vector>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 100005;
int n, m, p = 1;
ll ans[N], t;
struct elevator{
	int t, s, f, id; //员工在t时刻于s楼等电梯到f楼,id为输入序列编号(离线+按t排序)
	bool operator < (const elevator &a) const{
		return t < a.t;
	}
} x[N];
vector <int> waiting[N]; //waiting[i]:在第i层楼等的员工
priority_queue <int> downq; //大根堆维护电梯下方以及要去电梯下方的员工的楼层
priority_queue <int, vector <int>, greater <int>> upq; //小根堆维护电梯上方以及要去电梯上方的员工的楼层
int read(){
	int x = 0;
	char a = getchar();
	while(a < '0' || '9' < a) a = getchar();
	while('0' <= a && a <= '9') x = (x << 3) + (x << 1) + (a ^ 48), a = getchar();
	return x;
}
void write(ll x){
	if(x > 9) write(x / 10);
	putchar(x % 10 | 48);
}
void Push(int &i){
	if(x[i].s != p){
		waiting[x[i].s].push_back(i);
		if(x[i].s > p) upq.push(x[i].s);
		else downq.push(x[i].s);
	}
	else{ //s!=f
		waiting[x[i].f].push_back(i);
		if(x[i].f > p) upq.push(x[i].f);
		else downq.push(x[i].f);
	}
	++ i;
}
void rePush(int &id){
	if(x[id].s == p){
		waiting[x[id].f].push_back(id);
		if(x[id].f > p) upq.push(x[id].f);
		else downq.push(x[id].f);
	}
	else ans[x[id].id] = t;
	waiting[p].erase(-- waiting[p].end());
}
int main(){
	n = read(), m = read();
	for(int i = 1; i <= n; ++ i) x[i].t = read(), x[i].s = read(), x[i].f = read(), x[i].id = i;
	sort(x + 1, x + 1 + n);
	for(int i = 1; i <= n;){
		t = x[i].t; //无人用电梯时进行时间跳跃
		Push(i);
		while(!upq.empty() || !downq.empty()){
			while(i <= n && x[i].t == t) Push(i);
			if(upq.size() >= downq.size()){
				if(i > n || upq.top() - p <= x[i].t - t){
					t += upq.top() - p; //时间不用一刻一刻取,算差值直接跳
					p = upq.top();
					for(int j = waiting[p].size() - 1; j >= 0; -- j) upq.pop();
					while(!waiting[p].empty()) rePush(*(-- waiting[p].end()));
				}
				else p += x[i].t - t, t += x[i].t - t;
			}
			else if(i > n || p - downq.top() <= x[i].t - t){
				t += p - downq.top();
				p = downq.top();
				for(int j = waiting[p].size() - 1; j >= 0; -- j) downq.pop();
				while(!waiting[p].empty()) rePush(*(-- waiting[p].end()));
			}
			else p -= x[i].t - t, t += x[i].t - t;
		}
	}
	for(int i = 1; i <= n; ++ i) write(ans[i]), puts("");
	return 0;
}
```

_~~这是鄙人的第一发题解，还是紫的，有点小激动。~~_ 

$\texttt{2023 年 8 月 16 日 update:}$ 简化了代码。

---

## 作者：Elaina_ (赞：1)

第一道自己码的“打磨你”，体育节打了一天才做完。

## 思路：

0 分：vector+暴力跳时间（[手法不可参考](https://www.luogu.com.cn/paste/xjp7uzuu)）

100 分：

### 开始之前我们要先知道两件事情：

1. 一旦这个人开始等电梯，那么这个人和电梯的相对位置不变。

2. 一旦这个人进入电梯，那么这个人的目标地点和电梯的相对位置不变。

证明：以 1 为例，一旦这个人开始等电梯，那么他如果被电梯经过他就会进入电梯而不会被跨过，所以相对位置不变，2 也同理

### 模拟思路：

1. 开四个优先队列，分别存等待位置在电梯上方，电梯下方的电梯外的等待者和目标位置在电梯上方，电梯下方的电梯内的等待者。

2. 每次跳的时候先判断方向（只用通过队列大小比较即可）

3. 随后（以向下跳为例）取出电梯下方中最上方的等待者和目标在电梯下方的电梯内的等待者，以及马上要开始等待的人，设电梯到电梯外的等待者的时间为 $tim1$，到目标点的时间为 $tim2$，此刻距离下一个开始等待的人的时间为 $tim3$。然后比较一下三者时间，哪个更小就转移到它那里即可。

对于第三个操作，具体来说，同样以向下跳为例：首先时间加上三者中的最小，电梯位置也减去三者最小，然后如果是 $tim1$ 那么从等待队列中跳出在那个位置等待的所有人，如果是 $tim2$ 那么从代表电梯内的队列中跳出在目标在那个位置的所有人，如果是 $tim3$ 把所有时间为该时间的人全部加入等待队列。

### 小细节：

1. 如果那个队列代表在电梯上方（等待位置在电梯下方和目标位置在电梯下方），记得乘以 $-1$。

2. 电梯外的序列以起点位置为关键字，电梯内的序列以目标位置为关键字。

3. 记得 long long。

4. 如果当前没有人在等并且没人在电梯内，那么直接从还没开始等待的人中加入时间最小的就行，而且更新时间的时候不要通过队列中的时间，直接从存还没开始等待的人的数组中修改就行，不然可能会 90 分（我觉得这个问题也只有我会犯了）。

## 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int F=110000;
const int inf=1145141919;
int read()
{
    char ch=getchar();int x=0,f=1;
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}

struct sl1{
    int id,st,ed,tag,beg,kk;//开始时间，目标位置，开始位置，编号，结束时间
    friend bool operator<(sl1 a,sl1 b){
        return a.beg<b.beg;
    }
}peo[F];

struct sl2{
    int id,st,ed,tag,beg,kk;//开始时间，目标位置，开始位置，编号，结束时间
    friend bool operator<(sl2 a,sl2 b){
        return a.tag<b.tag;
    }
};

int n,m,puup,pudo,head,tim,now=1,check;
priority_queue<sl1> waitdown,waitup;
priority_queue<sl2> peodown,peoup;
//1下方，2上方

bool cmp(sl1 a,sl1 b)
{
    if(a.st==b.st){
        return a.beg<b.beg;
    }
    return a.st<b.st;
}
bool cmp1(sl1 a,sl1 b)
{
    return a.id<b.id;
}
void prin()
{
    sort(peo+1,peo+1+n,cmp1);
    for(int i=1;i<=n;i++) cout<<peo[i].ed<<'\n';
}
void chuan(sl1 a,sl2 &b)
{
    b.id=a.id;
    b.st=a.st;
    b.ed=a.ed;
    b.tag=a.tag;
    b.beg=a.beg;
    b.kk=a.kk;
}

void pushin(sl1 p){
    sl2 x;
    chuan(p,x);
    if(x.tag>now){
        x.tag*=-1;
        peoup.push(x);
    }
    else{
        peodown.push(x);
    }
}

void pushoutwait(int x){
    if(x==1){
        sl1 a=waitdown.top();
        pushin(a);
        waitdown.pop();
        if(waitdown.top().beg==a.beg&&waitdown.size()) pushoutwait(1);
    }
    else{
        sl1 a=waitup.top();
        pushin(a);
        waitup.pop();
        if(waitup.top().beg==a.beg&&waitup.size()) pushoutwait(2);
    }
}

void pushoutin(int x){
    if(x==1){
        sl2 a=peodown.top();
        peo[a.kk].ed=tim;
        peodown.pop();
        if(peodown.top().tag==a.tag&&peodown.size()) pushoutin(1);
    }
    else{
        sl2 a=peoup.top();
        peo[a.kk].ed=tim;
        peoup.pop();
        if(peoup.top().tag==a.tag&&peoup.size()) pushoutin(2);
    }
}

void pushwait(sl1 p){
    if(p.beg>now){
        p.beg*=-1;
        waitup.push(p);
    }
    else{
        if(p.beg<now) waitdown.push(p);
        else pushin(p);
    }
}

void getdo(sl1 &pl,sl2 &p,int k){
    if(k-1){
        if(waitdown.size()){
            pl=waitdown.top();
        }
    }
    else{
        if(peodown.size()){
            p=peodown.top();
        }
    }
}

void getup(sl1 &pl,sl2 &p,int k){
    if(k-1){
        if(waitup.size()){
            pl=waitup.top();
            pl.beg*=-1;
        }
    }
    else{
        if(peoup.size()){
            p=peoup.top();
            p.tag*=-1;
        }
    }
}

int getmin(int x,int y,int z){
    if(x<=y&&x<=z) return x;
    if(y<=x&&y<=z) return y;
    if(z<=x&&z<=y) return z;
    return x;
}

void pushinwait(){
    pushwait(peo[head]);
    head++;
    while(peo[head-1].st==peo[head].st&&head<=n){
        pushwait(peo[head]);
        head++;
    }
}

signed main(){
    freopen("try.in","r",stdin);
    n=read(),m=read();
    for(int i=1;i<=n;peo[i].st=read(),peo[i].beg=read(),peo[i].tag=read(),peo[i].id=i,i++);
    sort(peo+1,peo+1+n,cmp);
    for(int i=1;i<=n;i++) peo[i].kk=i;
    head=now=1;
    while(1){
        if(head>n && !peodown.size() && !peoup.size() && !waitdown.size() && !waitup.size()) break;
        pudo=peodown.size()+waitdown.size(),puup=peoup.size()+waitup.size();
        if(!pudo&&!puup){
            pushinwait();
            tim=peo[head-1].st;
        }
        else{
            if(pudo>puup){
                sl1 we1,we;
                sl2 pe1;
                getdo(we1,pe1,1);
                getdo(we1,pe1,2);
                int tim1,tim2,tim3;
                if(head<=n) we=peo[head];
                else we.st=we.beg==inf;
                
                if(!waitdown.size()) tim1=inf;
                else tim1=now-we1.beg;
                if(!peodown.size()) tim2=inf;
                else tim2=now-pe1.tag;
                if(head>n) tim3=inf;
                else tim3=we.st-tim;
                int opt=getmin(tim1,tim2,tim3);
                now-=opt,tim+=opt;
                if(tim1<=tim2&&tim1<=tim3) pushoutwait(1);
                if(tim2<=tim1&&tim2<=tim3) pushoutin(1);
                if(tim3<=tim1&&tim3<=tim2) pushinwait();
            }
            else{
                sl1 we2,we;
                sl2 pe2;
                getup(we2,pe2,1);
                getup(we2,pe2,2);
                int tim1,tim2,tim3;
                if(head<=n) we=peo[head];
                else we.st=we.beg==inf;
                
                if(!waitup.size()) tim1=inf;
                else tim1=we2.beg-now;
                if(!peoup.size()) tim2=inf;
                else tim2=pe2.tag-now;
                if(head>n) tim3=inf;
                else tim3=we.st-tim;
                int opt=getmin(tim1,tim2,tim3);
                now+=opt,tim+=opt;
                if(tim1<=tim2&&tim1<=tim3) pushoutwait(2);
                if(tim2<=tim1&&tim2<=tim3) pushoutin(2);
                if(tim3<=tim1&&tim3<=tim2) pushinwait();
            }
        }
    }
    prin();
    return 0;
}
```


---

## 作者：Hoks (赞：1)

## 前言
[题目传送门](https://www.luogu.com.cn/problem/CF257E)，[个人博客](https://www.luogu.com.cn/blog/Hok/solution-cf257e)内食用可能也许大概不会更佳。~~我调了一天终于发现锅的快乐题目。~~
## 题意
让你模拟一个高级的电梯，会判断想去上面的人数和想去下面的人数决定向上或者向下走。
## 思路分析
先按照时间排序，然后枚举时，在上一个人等电梯到这个人还没来的时间是没有人要上电梯的，所以这一段时间就可以用来模拟电梯运行时，最后尝试判断一下这个时间的人有没有刚好能上电梯。

暴力枚举是不行的，因为 $1\le n\le100000$，所以我们考虑用优先队列优化。

因为在电梯上的人如果到达自己要下电梯的层数就会离开，所以当他还在电梯上时。他要去的层数和电梯目前层数的大小是确定的。我们就可以把他放在一个独立的优先队列中。

开 $4$ 个优先队列分别维护电梯中向上的人，向下的人，在上面等的人，在下面等的人。使用优先队列维护要上楼层数更少的人和要下楼层数更少的人，保证不会因为为了一个人上楼而错过中间的人离开电梯。

每次模拟电梯尝试让人上电梯和下电梯即可。
## 注意事项
每次操作玩之后注意更新 $up$，$down$。~~就这东西卡了我一天。~~

在每一次模拟电梯运行时，要先判断上电梯，再判断下电梯，因为不排除有上了电梯立刻下来的可能性。
## 代码
```cpp
//xysj：需要时间，mq：目前，sysj：剩余时间
//up1：在电梯上要向上的人，up2：在电梯目前层数上面要上电梯的人。
//down1，down2同理
#include<bits/stdc++.h>
#define int long long
#define ec 114514
#define fi first
#define se second
using namespace std;
struct node
{int t,st,ed,id;}a[ec];
int n,m,t,mq=1,up,down;
int ans[ec];
priority_queue<pair<int,int> > down1,down2;
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > up1,up2;
int read()
{
    char c=getchar();int x=0;
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x;
}
bool cmp(node x,node y){return x.t<y.t;}
signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++) a[i].t=read(),a[i].st=read(),a[i].ed=read(),a[i].id=i;
    sort(a+1,a+1+n,cmp);a[n+1].t=1145141919810;//防止处理不完
    for(int i=1;i<=n+1;i++)
    {
        int sysj=a[i].t-a[i-1].t;t=a[i-1].t;
        up=up1.size()+up2.size();down=down1.size()+down2.size();
        while(sysj&&up+down>0)
        {
            if(up>=down)
            {//向上
                int xysj=0x3f3f3f3f3f3f3f3f;
                if(!up2.empty()) xysj=min(xysj,up2.top().fi);
                if(!up1.empty()) xysj=min(xysj,up1.top().fi);
                xysj-=mq;
                if(xysj>sysj){mq+=sysj;break;}
                if(!up2.empty()&&mq+xysj==up2.top().fi)
                    while(!up2.empty()&&up2.top().fi==mq+xysj)
                    {
                        int u=up2.top().se;up2.pop();
                        if(a[u].ed>mq+xysj) up1.push(make_pair(a[u].ed,a[u].id));
                        else down1.push(make_pair(a[u].ed,a[u].id));
                    }//上电梯
                if(!up1.empty()&&mq+xysj==up1.top().fi)
                    while(!up1.empty()&&up1.top().fi==mq+xysj)
                    {
                        int u=up1.top().se;up1.pop();
                        ans[u]=t+xysj;
                    }//下电梯
                sysj-=xysj;t+=xysj;mq+=xysj;
            }
            else
            {
                int xysj=-1;
                if(!down2.empty()) xysj=max(xysj,down2.top().fi);
                if(!down1.empty()) xysj=max(xysj,down1.top().fi);
                xysj=mq-xysj;
                if(xysj>sysj){mq-=sysj;break;}
                if(!down2.empty()&&mq-xysj==down2.top().fi)
                    while(!down2.empty()&&down2.top().fi==mq-xysj)
                    {
                        int u=down2.top().se;down2.pop();
                        if(a[u].ed>mq-xysj) up1.push(make_pair(a[u].ed,a[u].id));
                        else down1.push(make_pair(a[u].ed,a[u].id));
                    }
                if(!down1.empty()&&mq-xysj==down1.top().fi)
                    while(!down1.empty()&&down1.top().fi==mq-xysj)
                    {
                        int u=down1.top().se;down1.pop();
                        ans[u]=t+xysj;
                    }
                sysj-=xysj;t+=xysj;mq-=xysj;
            }
            up=up1.size()+up2.size();down=down1.size()+down2.size();
        }
        if(i>n) break;
        if(a[i].st==mq)
            if(a[i].ed>mq) up1.push(make_pair(a[i].ed,a[i].id));
            else down1.push(make_pair(a[i].ed,a[i].id));
        else 
            if(a[i].st>mq) up2.push(make_pair(a[i].st,i));
            else down2.push(make_pair(a[i].st,i)); 
        while(a[i+1].t==a[i].t)
        {
            i++;
            if(a[i].st==mq)
                if(a[i].ed>mq) up1.push(make_pair(a[i].ed,a[i].id));
                else down1.push(make_pair(a[i].ed,a[i].id));
            else 
                if(a[i].st>mq) up2.push(make_pair(a[i].st,i));
                else down2.push(make_pair(a[i].st,i));
        }
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<endl;
    return 0;
}
```


---

## 作者：zhjzhmh (赞：1)

按照题意模拟即可，注意如果在上方等待的人，一定不会变成下方等待，反之亦然，所以可以分上下进行维护，将等待与电梯里的人分开处理，找最近的人，可以直接用优先队列 STL 维护注意一些小细节，将人离线处理，按时间从小到大进行排序，详见代码注释。


```cpp

#include<bits/stdc++.h>
#define int long long
#define p_up go_up.size()+wait_up.size()
#define p_down go_down.size()+wait_down.size()//同题意
using namespace std;
inline int read()
{
   int s=0,w=1;char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int n,m,x,ans[100010],T;
struct node{int t,l,r,id;bool operator < (const node &c) {return t<c.t;}}q[100010];//按时间先后排序
priority_queue< pair<int,int> > go_down,wait_down;//下行、在下方等待的人
priority_queue< pair<int,int> , vector< pair<int,int> > , greater< pair<int,int> > > go_up,wait_up;//上行、在上方等待的人
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) q[i]=(node){read(),read(),read(),i};
	sort(q+1,q+n+1);x=1;q[n+1].t=0x3f3f3f3f3f3f3f3f;//x代表当前楼层，q[n+1].t保证最后处理完全
	for(int i=1;i<=n+1;i++)
	{
		int p=q[i].t-q[i-1].t;T=q[i-1].t;//p表示剩余时间直到下一次有人加入等待序列，T表示当前时间
		while(p&&p_up+p_down>0)
		{
			if(p_up>=p_down)
			{
				int hf=0x3f3f3f3f3f3f3f3f;
				if(!wait_up.empty()) hf=min(hf,wait_up.top().first);
				if(!go_up.empty()) hf=min(hf,go_up.top().first);
				hf-=x;//最近上方消耗时间
				if(hf>p) {x+=p;break;}//剩余时间不够
				if(!wait_up.empty()&&x+hf==wait_up.top().first)
				{
					while(!wait_up.empty()&&wait_up.top().first==x+hf)
					{
						int u=wait_up.top().second;wait_up.pop();
						if(q[u].r>x+hf) go_up.push(make_pair(q[u].r,q[u].id));
						  else go_down.push(make_pair(q[u].r,q[u].id));
					}	
				}//进电梯
				if(!go_up.empty()&&x+hf==go_up.top().first)
				{	
					while(!go_up.empty()&&go_up.top().first==x+hf)
					{
						int u=go_up.top().second;go_up.pop();
						ans[u]=T+hf;
					}
				}//出电梯
				p-=hf;T+=hf;x+=hf;
			}//上行
			else
			{
				int hf=-1;
				if(!wait_down.empty()) hf=max(hf,wait_down.top().first);
				if(!go_down.empty()) hf=max(hf,go_down.top().first);
				hf=x-hf;//最近下方消耗时间
				if(hf>p) {x-=p;break;}//剩余时间不够
				if(!wait_down.empty()&&x-hf==wait_down.top().first)
				{
					while(!wait_down.empty()&&wait_down.top().first==x-hf)
					{
						int u=wait_down.top().second;wait_down.pop();
						if(q[u].r>x-hf) go_up.push(make_pair(q[u].r,q[u].id));
						  else go_down.push(make_pair(q[u].r,q[u].id));
					}
				}//进电梯
				if(!go_down.empty()&&x-hf==go_down.top().first)
				{
					while(!go_down.empty()&&go_down.top().first==x-hf)
					{
						int u=go_down.top().second;go_down.pop();
						ans[u]=T+hf;
					}
				}//出电梯
				p-=hf;T+=hf;x-=hf;
			}//下行
		}
		if(i>n) break;
		if(q[i].l==x)
		  if(q[i].r>x) go_up.push(make_pair(q[i].r,q[i].id));
			else go_down.push(make_pair(q[i].r,q[i].id));
		else 
		  if(q[i].l>x) wait_up.push(make_pair(q[i].l,i));
		  	else wait_down.push(make_pair(q[i].l,i)); 
		while(q[i+1].t==q[i].t)
		{
			i++;
			if(q[i].l==x)
			  if(q[i].r>x) go_up.push(make_pair(q[i].r,q[i].id));
			    else go_down.push(make_pair(q[i].r,q[i].id));
			else 
			  if(q[i].l>x) wait_up.push(make_pair(q[i].l,i));
		  	    else wait_down.push(make_pair(q[i].l,i)); 
		}//将这一串时间相等的人全部加入，注意刚好与电梯同一高度的人可以直接进电梯
	}
	for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);
}
```

---

## 作者：GI录像机 (赞：0)

## 思路

考虑什么时候电梯会改变方向。

发现只有当：
1. 有新的人开始等待
2. 有人上电梯
3. 有人下电梯

时，电梯会改变方向，而这三种情况都只会有 $O(n)$ 次，因此我们按照题意模拟即可。

因为上电梯与下电梯对于 $p_{up}$ 和 $p_{down}$ 的贡献是一样，放在一棵以层数为下标的线段树里，记录区间和。

设当前电梯所在层数为 $now$，我们要把电梯往它的前驱\后继开，这取决于 $p_{up}$ 和 $p_{down}$ 的大小关系，所消耗时间为 $|nxt-now|$。注意，如果这之间有一个人要来等电梯，方向可能会改变，因此不能直接走到。

然后对于每一层开一个 vector，维护要在这一层上/下的信息，电梯到这一层的时候暴力算即可。

## 代码
有点丑陋，实际上可以短很多。


```cpp
#include<bits/stdc++.h>
using namespace std;
int read() {
	int x = 0, f = 1;
	char c = getchar();
	while(c > '9' || c < '0') {
		if(c == '-')f = -f;
		c = getchar();
	}
	while(c <= '9' && c >= '0') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}
void write(long long x) {
	if(x < 0) {
		putchar('-');
		x = -x;
	} if(x > 9)write(x / 10);
	putchar((x % 10) + '0');
}
const int N = 1e5 + 10, INF = 0x3f3f3f3f, MOD = 1e9 + 7;
int n, m, sum[N << 2], now = 1;
long long ans[N], las;
vector<pair<int, bool> >v[N];
struct GICamera {
	int t, s, f, id;
}a[N];
bool cmp(GICamera x, GICamera y) {
	return x.t < y.t;
}
void pushup(int pos) {
	sum[pos] = sum[pos << 1] + sum[pos << 1 | 1];
}
void add(int pos, int l, int r, int L, int k) {
	if(l == r) {
		sum[pos] += k;
		return;
	} int mid = (l + r) >> 1;
	if(L <= mid)add(pos << 1, l, mid, L, k);
	else add(pos << 1 | 1, mid + 1, r, L, k);
	pushup(pos);
}
int find_las(int pos, int l, int r) {
	if(l == r)return l;
	int mid = (l + r) >> 1;
	if(sum[pos << 1 | 1])return find_las(pos << 1 | 1, mid + 1, r);
	return find_las(pos << 1, l, mid); 
}
int find_nxt(int pos, int l, int r) {
	if(l == r)return l;
	int mid = (l + r) >> 1;
	if(sum[pos << 1])return find_nxt(pos << 1, l, mid);
	return find_nxt(pos << 1 | 1, mid + 1, r); 
}
int query_las(int pos, int l, int r, int L, int R) {
	if(L <= l && r <= R) {
		if(sum[pos])return find_las(pos, l, r);
		return 0;
	} int mid = (l + r) >> 1, res = 0;
	if(mid + 1 <= R)res = query_las(pos << 1 | 1, mid + 1, r, L, R);
	if(!res)res = query_las(pos << 1, l, mid, L, R);
	return res;
}
int query_nxt(int pos, int l, int r, int L, int R) {
	if(L <= l && r <= R) {
		if(sum[pos])return find_nxt(pos, l, r);
		return 0;
	} int mid = (l + r) >> 1, res = 0;
	if(L <= mid)res = query_nxt(pos << 1, l, mid, L, R);
	if(!res)res = query_nxt(pos << 1 | 1, mid + 1, r, L, R);
	return res;
}
int query(int pos, int l, int r, int L, int R) {
	if(L <= l && r <= R)return sum[pos];
	int mid = (l + r) >> 1, res = 0;
	if(L <= mid)res = query(pos << 1, l, mid, L, R);
	if(mid + 1 <= R)res += query(pos << 1 | 1, mid + 1, r, L, R);
	return res;
}
signed main() {
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= n; i++)a[i].t = read(), a[i].s = read(), a[i].f = read(), a[i].id = i;
	sort(a + 1, a + n + 1, cmp);
	for(int i = 1; i <= n; i++) {
		int t = a[i].t;
		while(sum[1] && las != t) {
			int id;
			if(query(1, 1, m, 1, now) <= query(1, 1, m, now, m)) {
				id = query_nxt(1, 1, m, now, m);
				if(id - now > t - las)now += t - las, las = t;
				else {
					las += id - now, now = id;
					for(int j = 0; j < v[id].size(); j++) {
						if(v[id][j].second)ans[a[v[id][j].first].id] = las;
						else add(1, 1, m, a[v[id][j].first].f, 1), v[a[v[id][j].first].f].push_back({v[id][j].first, 1});
					}
					add(1, 1, m, id, -v[id].size());
					v[id].clear();
				}
			} else {
				id = query_las(1, 1, m, 1, now);
				if(now - id > t - las)now -= t - las, las = t;
				else {
					las += now - id, now = id;
					for(int j = 0; j < v[id].size(); j++) {
						if(v[id][j].second)ans[a[v[id][j].first].id] = las;
						else add(1, 1, m, a[v[id][j].first].f, 1), v[a[v[id][j].first].f].push_back({v[id][j].first, 1});
					}
					add(1, 1, m, id, -v[id].size());
					v[id].clear();
				}
			}
		}
		add(1, 1, m, a[i].s, 1), v[a[i].s].push_back({i, 0}), las = t;
	}
	while(sum[1]) {
		int id;
		if(query(1, 1, m, 1, now) <= query(1, 1, m, now, m)) {
			id = query_nxt(1, 1, m, now, m);
			las += id - now, now = id;
			for(int j = 0; j < v[id].size(); j++) {
				if(v[id][j].second)ans[a[v[id][j].first].id] = las;
				else add(1, 1, m, a[v[id][j].first].f, 1), v[a[v[id][j].first].f].push_back({v[id][j].first, 1});
			}
			add(1, 1, m, id, -v[id].size());
			v[id].clear();
		} else {
			id = query_las(1, 1, m, 1, now);
			las += now - id, now = id;
			for(int j = 0; j < v[id].size(); j++) {
				if(v[id][j].second)ans[a[v[id][j].first].id] = las;
				else add(1, 1, m, a[v[id][j].first].f, 1), v[a[v[id][j].first].f].push_back({v[id][j].first, 1});
			}
			add(1, 1, m, id, -v[id].size());
			v[id].clear();
		}
	}
	for(int i = 1; i <= n; i++)write(ans[i]), putchar('\n');
	return 0;
}//不开longlong___
```

---

