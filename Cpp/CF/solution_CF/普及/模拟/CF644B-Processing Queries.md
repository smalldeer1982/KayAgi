# Processing Queries

## 题目描述

##### 问题描述

有一条单线程的生产线，即同时只能处理一项工作，有 $n$ 个工作申请，第 $i$ 个工作的开始时间为 $t_i$，完成需要 $d_i$ 个单位时间，所有的 $t_i$ 都不相同。

当一项工作申请出现时，生产线会有如下三种处理方案：

1. 如果生产线是空闲的，而且等待队列是空的，则当前申请的工作会被马上执行。
2. 如果生产线正在工作，而且等待队列中的工作少于 $b$ 个，则当前申请的工作会被加入到等待队列的队尾。
3. 如果生产线正在工作，而且等待队列中的工作已经有 $b$ 个，则当前申请的工作会被拒绝，而且再也不会接受该工作的申请。

## 说明/提示

$1 \leq n,b \leq 2\times 10^5$。

$1\leq  t_i,d_i \leq 10^9$。

$t_{i-1}<t_i$。

## 样例 #1

### 输入

```
5 1
2 9
4 8
10 9
15 2
19 1
```

### 输出

```
11 19 -1 21 22 
```

## 样例 #2

### 输入

```
4 1
2 8
4 8
10 9
15 2
```

### 输出

```
10 18 27 -1 
```

# 题解

## 作者：KukCair (赞：5)

## CF644B Processing Queries

### 基本思路

模拟题。

对于每个工作申请，队列有如下两种操作：

首先，将 $\leq$ 当前开始时间（即 $t_i$）的所有操作弹出。

接下来有两种选择：

- 当队列已满，直接输出 `-1`。

- 当队列未满，更新结束时间并入队，输出新结束时间。

### 代码实现

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, b, nw;
queue<int> q;
signed main(){
    cin >> n >> b;
    while(n--){
        int t, d;
        cin >> t >> d;
        while(!q.empty() && q.front() <= t) q.pop();
        if(q.size() > b) cout << "-1 ";
        else{
            nw = max(nw, t) + d;
            q.push(nw);
            cout << nw << ' ';
        }
    }
    return 0;
}
```

---

## 作者：DarkShadow (赞：4)

# CF644B（模拟）

## 题目大意：

给出 $N$ 个工作申请以及它们的开始时间、所需时间。当出现一个工作申请时，如果生产线空闲就会直接执行，等待队列少于 $b$ 个工作会把当前申请加到生产线中，否则会拒绝申请，求每个工作的完成时间。

## 思路分析：

很明显的一道模拟题。

因为这道题 $t_i \le 10^9$，所以我们直接枚举时间是会超时的。我们可以只维护一个等待序列，先把最开头的一个工作拿出来执行，再枚举当前所有开始时间小于当前时间的工作，如果队列中已有 $b$ 个元素就拒绝掉，否则将它加入队列中，一直重复直到队列为空或工作已经枚举完为止。

## 注意事项：

1. 如果当前队列为空，那么再开始执行工作前必须把下一个工作加到队列里（相当于直接执行）。

2. 由于本题 $t_i,d_i \le 10^9$，所以需要开 long long。

## 完整代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=200005;
int n,b,p1=1,p2=0,q[N],d[N],t[N],p;
ll T,ans[N];
int main(){
	scanf("%d%d",&n,&b);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&t[i],&d[i]);
	T=(ll)(t[1]);
	while(1){
		if(p2<p1&&p<n)  q[++p2]=++p;//如果队列为空则直接取出下一个工作执行
		T=max(T,(ll)(t[q[p1]])),T+=(ll)(d[q[p1]]),ans[q[p1]]=T,p1++;//执行当前队列开头的工作
		while(p<n&&(ll)(t[p+1])<T){
			if(p2-p1+1<b)  q[++p2]=++p;//将工作加到队列中
			else  ans[++p]=-1;//拒绝当前工作
		}
		if(p==n&&p2<p1)  break;//如果队列为空且没有剩余的工作就退出
	}
	for(int i=1;i<=n;i++)
		printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：King_and_Grey (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF644B)
这是一道**模拟**题，需要用到 STL 库中的 `queue` 来实现。

## 容器介绍
`queue` 是一种先进先出（First in First out）的容器，与 `stack` 后进先出（First in Last out）不同，头文件也是 `queue`。

### 申明队列
`queue<Type, Container>` 第一个为数据类型，第二个为容器类型。**初始化时必须要有数据类型**，但是容器可省略，省略时则默认为 `deque` 类型。例子如下：

#### 例一：
```cpp
queue<int>q1;
queue<double>q2;  
queue<char>q3;
//默认用deque容器实现的queue。
```
#### 例二：
```cpp
queue<char,list<char>>q1;
//用list容器实现的queue 
queue<int,deque<int>>q2;
//用deque容器实现的queue。
```
#### 注意：不能用 `vector` 容器初始化 `queue`！
因为 `queue` 转换器要求容器支持 `front()`、`back()`、`push_back()` 及 `pop_front()`，说明 `queue` 的数据从容器后端入栈而从前端出栈。所以可以使用 `deque` 和 `list` 对 `queue` 初始化，而 `vector` 因其缺少 `pop_front()`，不能用于 `queue`。

### 常用函数
1. `push()` 在队尾插入一个元素。
2. `pop()` 删除队列第一个元素。
3. `size()` 返回队列中元素个数。
4. `empty()` 如果队列空则返回 true。
5. `front()` 返回队列中的第一个元素。
6. `back()` 返回队列中最后一个元素。

## 思路讲解
对于每次任务：
1. 输入任务开始的时间与完成任务需要的时间。
2. 找到任务开始之前能够完成的任务并把它弹出。
3. 查看这个任务能否加入等待队列。
4. 如果能加入队列，就更新时间并插入到队尾；如果不能，输出 $-1$。

**注意：十年 OI 一场空，不开 `long long` 见祖宗！！！**

AC Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,b,times,d,now;
queue<int> q;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin >> n >> b;
    while(n--){
        cin >> times >> d;
        while(!q.empty() && q.front() <= times){
			q.pop();
		}
        if(q.size() > b){
			cout << "-1 ";
		}else{
            now = max(now,times) + d;
            q.push(now);
            cout << now << " ";
        }
    }
    return 0;
}
```
[通过记录。](https://www.luogu.com.cn/record/164463641)  
谢谢观看！！！

---

## 作者：Special_Tony (赞：1)

# 思路
按照题目说的做就行。

对于每一个新进来的请求，先把完成时间比任务开始时间靠前的任务从队列里弹掉，然后判断队列里任务个数是否 $\le t_i$（是 $\le$ 不是 $<$，因为我们已经把正在工作的任务也放在队列里了），如果是，那就把结束时间累加上 $d_i$ 并塞进队列。注意要考虑上一个结束时间还不及这个任务开始时间的情况。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, m;
ll now, a, b;
queue <ll> q;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> m;
	while (n --) {
		cin >> a >> b;
		while (! q.empty () && q.front () <= a)
			q.pop ();
		now = max (now, a);
		if (q.size () <= m)
			q.push (now += b), cout << now << ' ';
		else
			cout << "-1 ";
	}
	return 0;
}
```

---

## 作者：李至擎 (赞：1)

[点我看题](https://www.luogu.com.cn/problem/CF644B)

思路：显然是模拟题，没什么好说的。

方法（以执行一次操作为例）：

- $1.$ 输入开始时间和持续时间；

- $2.$ 判断当前时间下的第一件事是否可以做完；

- $3.$ 根据事件数判断是等待（或执行）还是舍弃这件事；

- $4.$ 如果要等待（或执行）这件事，计算新时间；

- $5.$ 根据是等待（或执行）还是舍弃这件事来输出时间。

细节：

- $1.$ 因为第一组优先级最大，不会与后面的冲突，所以要直接计算和输出；

- $2.$ 因为我们的队列是用来存放等待的事和当前正在做的事的，所以判断条件是事件数 $\le b$ 而不是 $ \le b-1$

- $3.$ 一定要开 $long$ $long$ ，一定要开 $long$ $long$ ，一定要开 $long$ $long$ ！

代码：

```cpp
#include<bits/stdc++.h>//万能头
#define LL long long//个人习惯（写起来方便）
using namespace std;
LL n,b,T,t[200005],d[200005];//n、b、t和d的意思如题，T为当前结束时间
queue<LL>q;//定义队列（不开long long见祖宗）
int main()
{
	cin>>n>>b;//输入
	for(LL i=1;i<=n;i++)
	{
		cin>>t[i]>>d[i];
	}
	T=t[1]+d[1];//计算第一组结束时间
	printf("%lld ",T);//优先计算和输出第一组
	q.push(T);//入队
	for(int i=2;i<=n;i++)//因为第一件事已经计算过了，所以从第二件事开始循环
	{
		while(!q.empty()&&q.front()<=t[i])//如果当前时间下的第一件事可以做完，就弹出它（已完成，不再考虑）
		{
			q.pop();//弹出队列
		}
		if(q.size()<=b)//如果当前事件数不大于b
		{
			T=max(T,t[i]);//T与下一件事的开始时间取最大值
			T+=d[i];//计算结束时间
			printf("%lld ",T);//输出
			q.push(T);//将新时间入队
		}
		else//反之（事件加不进来了）
		{
			printf("-1 ");//选不了，输出-1
		}
	}
	return 0;//结束程序
}
```

---

## 作者：innocent__ (赞：1)

## 不会队列的看这里   
  额，楼上那位大佬为啥比我只早离了几天，恰好还是我童鞋   
  
一看题目就知是模拟题，而且是队列，听说 STL 效率差，就用数组模拟好了 ~~队列不会~~  
其实很简单用 head 表示队列的头，及目前处理的工作，一个 tail ，表示当前所等的工作的标号   
当一个数据输进来时，有三种可能  ：  
1.空的，即为 head==tail ，此时应直接输出 t【i】+d【i】，tail++；  
2.等待的，且少于 b 个，即 head-tail<b，那么直接输出  上一个的答案+这一个工作所需的时间，tail++;   
3.有等待的,且等于 b 个,那么直接输出 -1, tail 不变;     
### 显而易见,
这样的代码是不行的,因未处理好的工作并未出队,所以当一个工作来的时候必须看看当前的工作是否完成 ,也就是说  当 ans[ head]<t[i] 时head 必须加一
## 代码
~~之前还有一件事~~ ： 当head==tail 时 head不能再加一
```
#include<bits/stdc++.h>
using namespace std;
long long t[200005],d[200005],n,ans[200005],b,head,tail;//平时不开long long 见祖宗，吓傻了
int main()
{
	cin>>n>>b;
	for(int i=0;i<n;i++)
		cin>>t[i]>>d[i]; 
	for(int i=0;i<n;i++)
	{
		while(ans[head]<=t[i]&&head<tail)head++;
		if(head==tail)
		{
			ans[tail]=t[i]+d[i];
			cout<<ans[tail]<<" ";
			tail++;
		}
		else 
		{
			if(tail-head>b)
				cout<<"-1 ";
			else 
			{
				ans[tail]=ans[tail-1]+d[i];
				cout<<ans[tail]<<" ";
				tail++;
			}
		}
	}
	return 0;
}
```
~~本蒟蒻也就是这样，大佬勿喷~~




---

## 作者：hater (赞：1)

模拟赛T1就这题 爆了零

窝码力布星被 [这位巨佬](https://www.luogu.org/user/108530) 吊着打

（要退役了滚回文化课）

题目显然是非常好懂的 

数据和题目结合起来一看就是模拟 

之后如何模拟 

因为时间过大 （1e9）

只能遍历物品了 

不过又有等待又有不等待好麻烦啊  

首先建一个队列

每次先把做完的物品出队

如果是出队的 那么判断一下队列的长度就OK了

如果是进队的那么把物品放进来 

重点在于物品的等待

下面的代码以物品的下标存在队列里

这样的处理大家看看

[代码](https://www.luogu.org/record/27043109)

~~显然这不是我的代码~~ 

窝的思路是入队两个元素

一个是物品的下标 另一个是物品开始处理的时间 

```cpp
#include <bits/stdc++.h> 
#define MAX 200005 
#define LL long long 
#define R register 
using namespace std ; 
struct Queue  {
    LL Si , whe ; 
}q[MAX] ;  LL n , Ans[MAX] , h , t , ti[MAX] , di[MAX]  , K ;
signed main()  {
    ios::sync_with_stdio(false) ; cin >> n >> K ;
    for(R int i=1; i<=n; i++) cin >> ti[i] >> di[i] ;
    h = t = 1 ;  q[1].Si = ti[1] ;  q[1].whe = 1 ;
    for(R int i=2; i<=n; i++) {
        while( q[h].Si+di[q[h].whe] <= ti[i] && h<=t )
          Ans[q[h].whe] = q[h].Si+di[q[h].whe] , h++ ;  
        if( t-h+1 > K ) { Ans[i] = -1; continue ; } 
        q[++t].whe = i ;
        if( t<=h ) q[t].Si = ti[i] ;
            else q[t].Si = q[t-1].Si+di[q[t-1].whe] ; }
    for(R int i=h; i<=t; i++) Ans[q[i].whe] = q[i].Si+di[q[i].whe];
    for(R int i=1; i<=n; i++)  cout << Ans[i] << " " ;  cout << endl;  return 0 ;
}


```

其他都还好理解 重点是这句话  

```cpp
if( t<=h ) q[t].Si = ti[i] ;
    else q[t].Si = q[t-1].Si+di[q[t-1].whe] ; }
```

如果队列里无物品等待

开始时间为它到的时间

如果有物品等待 

显然就是最后一个物品处理完的时间 

那么  诶

为什么如果队列里无物品等待的判断是 

t <= h 呢 ？

答 ： 您要算上刚刚入队的元素 

**~~窝就这里错了 之后100挂成0~~**

---

## 作者：qzhwlzy (赞：1)

### [传送门](https://www.luogu.com.cn/problem/CF644B)
## 思路
其实这题暴力模拟就好了（~~但本蒟蒻模拟赛T1还是爆0~~）。但是，值得一提的是，可以不用队列来模拟等待队列，只需要用变量存放队列的首尾即可（即 $head$ 和 $tail$），因为我们用数组存下了每项工作的信息，所以把他们看做队列即可。  
**而对于每一项工作开始执行时，若队头的结束时间小于其开始时间（即到这项工作时生产线以空），就让队头加一**，然后，**若等待队列中没有工作，就执行工作且输出**，否则，**将此工作加入等待队列**。加入时，**若队列中有 $b$ 个元素就输出，否则拒绝**（具体代码中也有说明）。
## AC代码
```cpp
#include<iostream>
#include<cstdio>//防伪标记
using namespace std;
const int N=200005;
long long n,b,he,ta;
long long t[N],d[N],w[N];
int main(){
//	freopen("process.in","r",stdin);
//	freopen("process.out","w",stdout);
	cin>>n>>b;
	for(long long i=1;i<=n;i++){
		cin>>t[i]>>d[i];
	}
	for(long long i=1;i<=n;i++){
		while(w[he]<=t[i]&&he<ta){
			he++;//若生产线上的工作结束则head++
		}
		if(he==ta){//若队中无元素
			w[ta]=t[i]+d[i];
			cout<<w[ta]<<" ";
            ta++;
		}else{
			if(ta-he>b){//若元素超过b个
				cout<<"-1 ";
			}else{
				w[ta]=w[ta-1]+d[i];
				cout<<w[ta]<<" ";
                ta++;
			}
		}
	}
	return 0;
}
```
~~有错欢迎评论。~~

---

## 作者：Ascnbeta (赞：0)

# CF644B 
## 题目大意
有 $n$ 个工作申请，对于每个工作申请，如果生产线空闲**且**等待队列为空就直接开始工作，否则如果等待队列中的工作申请数 $< b$ 就放入队列，若队列也无位置就输出 $-1$。

## 思路分析
挺裸的一道模拟题，可以用于练习 `queue` 的用法。由于 $n \le 10^5$，我们可以 $O(n)$ 地遍历所有工作申请，分别判断每一个工作申请是否可以执行。

## 具体实现
由于题目保证了后读入任务的时间晚于先读入任务的时间，那么我们可以在读入每一个任务的数据后就以当前任务的时间来处理等待队列中的任务。

所以我们用结构体数组 $ta$ 存储三个变量：当前任务开始时间 $t$，当前任务所需时间 $d$，该任务实际完成时的时间（即答案）$time$。同时维护一个队列 $q$，存储任务的编号。再用一个变量 $ent$ 表示生产线完成上一个任务时的时刻。

那么当我们读入一个任务后，我们可以这样判断：

* 若等待队列不为空，如果当前读入任务的开始时间 $t \ge ent$，那么表示上一个任务已经完成，生产线已经空闲，则**从队首不停地**取出任务来更新 $ent$ 和对应任务的完成时刻 $time$ 直到 $t < ent$，即当前时间生产线已经不再空闲；或者是等待队列已经为空。
* 若队列为空（包括其本身为空或是在上述循环执行后为空），那么判断当前任务 $t \ge edt$ 是否成立（即当前时刻生产线是否空闲），如果空闲则不必入队，直接更新 $edt$ 与当前任务的完成时间 $time$；如果生产线忙碌，由于队列为空则直接让当前任务入队。接着直接开始读入并判断下一个任务（即 `continue`）。
* 若队列不为空（在上述循环执行后仍不为空），那么说明生产线一定忙碌，则判断队列长度是否 $< b$，若小于，则表明队列有空，则使当前任务入队；否则将当前任务 $time$ 更新为 $-1$。

最后读入并判断完所有数据后，再执行一次上述操作第一项（即处理等待队列），由于此时还在队里的一定能执行完毕，所以直接更新对应任务的 $time$ 即可。

最终遍历全部任务，输出对应的 $time$ 即可。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,b;
queue<int> q;
bool ava = true;
int edt;
struct task{
	int t,d,time;
}ta[200005];
signed main () {
	cin >> n >> b;
	for (int i = 1; i <= n; i++) {
		int t,d;
		cin >> t >> d;
		ta[i].t = t,ta[i].d = d;
		while(!q.empty()) {
			if (t >= edt) {
				edt = edt + ta[q.front()].d;
                ta[q.front()].time = edt;
				q.pop();
				
			}else{
				break;
			}
		}
		if (q.empty()) {
			if (t >= edt) {
				ta[i].time = t + d;
				edt = t + d;
			}else{
				q.push(i);
			}
			continue;
		}
		if (q.size() < b) {
			q.push(i);
		}else{
			ta[i].time = -1;
		}
    //以上就是3种判断
	}
	while(!q.empty()) {
		edt = edt + ta[q.front()].d;
        ta[q.front()].time = edt;
		q.pop();
	}//最后处理队列
    for (int i = 1; i <= n; i++) {
        cout << ta[i].time << ' ';
    } 
	return 0;
}
```
蒟蒻第一篇题解，感谢审核员两次审核。

~~其实本来不是第一篇但是原来那篇已经被打回并关闭题解通道了。~~

---

## 作者：ThySecret (赞：0)

# [本题链接](https://www.luogu.com.cn/problem/CF644B)

## 题目大意：

  有一个队列，其中的每项工作 $i$ 都有两个值：最早可以处理的时间 $t_{i}$ 和处理所需要的时间 $d_{i}$。等待队列中的数量不可以超过 $b$，求出每个工作完成时间（无法完成则输出 $-1$）。

## 模拟思路

这是一道结合了队列的模拟题，自然可以使用队列来做，但首先我们要搞清一下几点：

1. 如何判断当前时间点有多少件事情可以完成。

2. 如何根据队列中的等待数判断是否可以完成。

3. 如何计算下一个事情前的完成时间。

我们可以定义一个一维数组 $bg[N]$，其中 $bg_{i}$ 表示第 $i$ 个事情时最早的可以做的时间，而由于每个事情都有自己的最早可处理时间 $t_{i}$，因此 $\max(bg_{i - 1}, t_{i})$ 即为第 $i$ 个事情的实际开始时间。显然可以得出状态转移方程：

$bg_{i} = \max (bg_{i - 1} + d_{i-1},t_{i})$

有因为一维数组 $bg_{i}$ 的状态只和 $bg_{i - 1}$ 有关，所以我们可以直接使用一个变量来代替。

不多说了，看代码注释。

## AC Code

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll; // 不开long long见祖宗
const int N = 2e5 + 9;

queue<ll> q; // STl大法好
ll t[N], d[N];
ll bg_time, n, b;

int main()
{
    cin >> n >> b;
    for (int i = 1; i <= n; i++)
	cin >> t[i] >> d[i];
	for (int i = 1; i <= n; i++)
	{
	    while (!q.empty() && q.front() <= t[i]) // 弹出或询问STL容器前一定要先判断容器是否为空！
		q.pop();
	    if (q.size() <= b)
	    {
	        bg_time = max(bg_time, t[i]) + d[i]; // 相当于下一件事情的最早开始时间，也是本次结束时间。 
	        cout << bg_time << ' ';
	        q.push(bg_time); // 将本次的可完成时间推入队列方便下次询问。
	    }
	    else cout << -1 << ' '; // 其余的可能情况只能是无解的。
	}
    return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

# 题目大意

给你 $n$ 个任务，每个任务有一个申请时间 $t_i$ 和一个完成所需时间 $d_i$。若没有任务正在等待，则立即执行这个新任务；若有任务正在执行，那么判断正在等待的任务数量是否小于 $b$，如果小于，那么将其加入等待队列，否则输出 $-1$ 表示不会完成这个任务。

# 思路分析

一道裸的小模拟。每次进来一个任务，先判断这个队列头有没有已经完成了的，即队头记录的某个任务的完成时间是否**小于等于**本次任务的开始时间。如果是，那么就将队头弹出，一直执行下去，直到队列为空或不满足上述条件为止。

每次入队时，我们用一个全局变量 $tim$ 表示加入队列的最后一个元素的完成时间，并在这个元素入队的时候认为 $\max(tim,t_i)$ 为该任务的开始时间，结束时间即为上述值加上 $d_i$，最新的 $tim$ 就是上述的值，将其压入队列。

不过需要特别注意的是，判断能否压入的时候，应当判断队列中的元素个数是否小于等于 $b$！因为第一个元素（队头）实际上是正在执行的任务。

题面中好像没有保证输入序列有序？

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{
    int id,lv,rv;
}v[200005];
int n,b,tim; queue<int>q;
inline bool cmp(node l,node r){
	return l.lv==r.lv?(l.rv==r.rv?l.id<r.id:l.rv<r.rv):l.lv<r.lv;
} 
signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>b;
    for(int i=1;i<=n;++i)
        cin>>v[i].lv>>v[i].rv,v[i].id=i;
    random_shuffle(v+1,v+n+1); //防止被卡
    sort(v+1,v+n+1,cmp);
    for(int i=1;i<=n;++i){
    	while(!q.empty()&&q.front()<=v[i].lv) q.pop();
		if(q.size()<=b){
			tim=max(v[i].lv,tim)+v[i].rv;
			q.push(tim); cout<<tim<<" ";
		}
		else cout<<"-1 ";
	}
	return 0;
}
```

---

## 作者：qzhwlyn (赞：0)

一道队列模拟

~~水题~~

核心代码
------------

```c
while(!q.empty()&&max(now,t[q.front()])+d[q.front()]<=t[i]){//如果在下个数开始前，在进行的已经进行好了，就弹出去，开始下一个数
	    	now=max(now,t[q.front()]);//下个数开始时间
			ans[q.front()]=now+d[q.front()];//结束时间
	    	now+=d[q.front()];q.pop();//弹出第一个数
		}
		if (q.size()<=b) q.push(i);//如果超过了b，就弹出这个数
		else ans[i]=-1;
	}
```

~~你们最喜欢的程序~~
```
#include<bits/stdc++.h>
#define maxn 200005
using namespace std;
int n,b,t[maxn],d[maxn],top=0,h=0,tot=0;
int ans[maxn];
queue<int>q;
int main(){
	//freopen("process.in","r",stdin);
	//freopen("process.out","w",stdout);
	cin>>n>>b;
	int now=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&t[i]);
		scanf("%d",&d[i]);
	}
	for(int i=1;i<=n;i++){	
	    while(!q.empty()&&max(now,t[q.front()])+d[q.front()]<=t[i]){
	    	now=max(now,t[q.front()]);
			ans[q.front()]=now+d[q.front()];
	    	now+=d[q.front()];q.pop();
		}
		if (q.size()<=b) q.push(i);
		else ans[i]=-1;
	}
	while(!q.empty()){//处理末尾的数
	    	now=max(now,t[q.front()]);
			ans[q.front()]=now+d[q.front()];
	    	now+=d[q.front()];q.pop();
		}
	for (int i=1;i<=n;i++) printf("%d ",ans[i]);
}
```


---

## 作者：WHJ___ (赞：0)

我是和@hater 同一个机房的大蒟蒻

同样的，我和他一样也爆了零

首先看到这题$n,b<=200000$的数据范围，就知道这道题应该有时间复杂度为$O(n)$或者$O(nlogn)$的作法

$O(n)$就是线性的队列作法

$O(nlogn)$就是分治的做法

这里由于队列的作法比较简单
~~,而且我没学分治~~,所以这里讨论队列的做法

第一点，也是最重要的一点：**队满**的条件！

队列满的条件在题面中极具误导性，导致一些人（包括我）首先会认为队满的条件是q.size()==b，但是实际上，每个时间段当队列非空时，总有一项工作**在进行**，即q.size()==1时，**工作队列**中是没有工作任务的。

那么，可以得出，队满的条件应该是q.size()==b+1，队未满的条件则是q.size()<b+1。

第二，是入队元素的问题。

如果直接将t和d加入队列，需要一个结构体。但这没有必要，我们只需要将结束的时间加入队列。结束的时间就是开始的时间+d[i]，开始的时间又成了一个问题，且听我徐徐道来。

我们可以先定义一个变量k，每次循环都将上一次工作结束(输出-1就不执行)的时间保存下来，当输入一个任务时，将这t[i]与k对比，如果k<t[i]，那么这项任务将会从t[i]时间点开始执行，那么入队元素将会在t[i]+d[i]时间点结束这项任务，并将t[i]+d[i]复制给k；反之，k>=t[i]时，这项任务将会从k时间点开始,这项任务会在k+d[i]时间点结束，将k+d[i]复制给k。
代码如下：

```cpp
if(q.size()<b+1){
   k=max(k,t[i]);
   k+=d[i];
   q.push(k);
}
```


第三，是输出顺序的问题。

如果把所有可以入队元素都放入队列，等到出队时再输出，会产生一个问题：输出的顺序。可以入队的元素本身的顺序不会改变，但无法入队的元素会直接输出$-1$。这是有解决方法的，用一个额外的变量p代替q.size()，将所有元素都入队，可以进入工作队列的元素执行++p，不能加入的元素则不增加p，并且在输出之后弹出。但同时这需要一个结构体Node，包含结束的时间和是否输出-1，这会导致代码非常繁琐，增加出错的概率。所以我们可以在入队后直接输出结果。

完整代码如下：
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
queue<long long>q;//不开long long见祖宗
long long i,n,b,t[200001],d[200001],k;
int main()
{
	cin>>n>>b;
	cin>>t[1]>>d[1];//输入前两个元素，因为初始状态下队列必空
	k=t[1]+d[1];
	q.push(t[1]+d[1]);//加入队列
	cout<<t[1]+d[1]<<" ";//直接输出
	for(i=2;i<=n;i++){
		cin>>t[i]>>d[i];//输入数据
		while(q.front()<=t[i]&&!q.empty()) q.pop();//队列不空，且队首可以做完
		if(q.size()<b+1){//队列不满
			k=max(k,t[i]);
			k+=d[i];//等效于第二点中的语句
			cout<<k<<" ";//直接输出，不必担心顺序
			q.push(k);//放入队列
		}
		else cout<<-1<<" ";//队列满了，不执行
	}
	return 0;
} 
```


---

