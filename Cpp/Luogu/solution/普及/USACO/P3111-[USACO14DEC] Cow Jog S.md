# [USACO14DEC] Cow Jog S

## 题目描述

 

The cows are out exercising their hooves again!  There are N cows

jogging on an infinitely-long single-lane track (1 <= N <= 100,000).

Each cow starts at a distinct position on the track, and some cows jog

at different speeds.


 

With only one lane in the track, cows cannot pass each other.  When a

faster cow catches up to another cow, she has to slow down to avoid

running into the other cow, becoming part of the same running group.

 

The cows will run for T minutes (1 <= T <= 1,000,000,000).  Please

help Farmer John determine how many groups will be left at this time.

Two cows should be considered part of the same group if they are at


the same position at the end of T minutes. 

有N (1 <= N <= 100,000)头奶牛在一个单人的超长跑道上慢跑，每头牛的起点位置都不同。由于是单人跑道，所有他们之间不能相互超越。当一头速度快的奶牛追上另外一头奶牛的时候，他必须降速成同等速度。我们把这些跑走同一个位置而且同等速度的牛看成一个小组。


请计算T (1 <= T <= 1,000,000,000)时间后，奶牛们将分为多少小组。



## 样例 #1

### 输入

```
5 3 
0 1 
1 2 
2 3 
3 2 
6 1 

 

```

### 输出

```
 

3 

 
```

# 题解

## 作者：NewErA (赞：20)

算是道shui题了吧！


只要在一开始算出所有牛的最终位置，并从后往前比对即可

如果前一头牛的最终位置达不到后一头牛，则res++

否则，将前一头牛的位置设置成和后一头牛相同


######注意，这里t的大小达到了10^9，因此要用long long!!!


附上代码

···cpp




    
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,t,last[100005];
struct cow
{
    long long spe,pos;
}a[100005];
int main()
{
    cin >> n >> t;
    for(int i=1;i<=n;i++)
    {
        cin >> a[i].pos >> a[i].spe;
        last[i]=a[i].pos+a[i].spe*t;
    }
    int res=1;
    for(int i=n-1;i>=1;i--)
    {
        if(last[i]>=last[i+1])
        {
            last[i]=last[i+1];
        }
        else
        {
            res++;
        }
    }
    cout<< res;
}
```
```cpp

---

## 作者：Tarsal (赞：9)

本蒟蒻又来发题解了，

一道较水的模拟题。

题意不过多解释，

思路如下：

在最开始的时候求出每头牛在t秒的位置（最终位置

然后，如果后一头牛追上了前一头牛，那就无视它，

把它们看成一个整体。

else

就++ ans；

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
//要开long long 
long long n, t, ans = 1, last[100010];
struct node
{
	long long s, p;
}a[100010];

int main()
{
	scanf("%lld%lld", &n, &t);//输入 
	for(int i = 1; i <= n; ++ i)
	{
		scanf("%lld%lld", &a[i].p, &a[i].s);//输入 
		last[i] = a[i].p + a[i].s * t;//记录下它的最终位置。 
	}
	for(int i = n - 1; i >= 1; -- i)
	{
		if(last[i] >= last[i + 1])//如果，追上来，就看成一样的 
			last[i] = last[i + 1];
		else
			++ ans;//++ ans 
	}
	printf("%lld", ans);//输出 
	return 0;
}
```


---

## 作者：zj余能 (赞：4)

这道题其实很水，因为牛开始都不在同一个位置，

所以只要判断在时间T内能否追到，即可知道两牛是否同组。

但题目中还有一层限制条件，即追到了要降速，不过这很好处理。


首先，把位置各不相同的奶牛看做N个组，Cnt\_Group=N；

如果一头奶牛追到了前一头奶牛，就把组数减一。

i从n-1开始递减迭代，用P表示前一头奶牛的标号，P初始为N；

假如(speed[i]-speed[p])\*T>=direction[p]-direction[i]，即i能追上P，

则Cnt\_Group--;否则对于i以前的奶牛不可能追上P，于是P=i；


本算法的正确性显然；


代码：




    
    
```cpp
#include<iostream>
using namespace std;
int d[200000],s[200000];
int main(){
    long long n,t,cnt,p;
    cin >>n>>t;cnt=n;
    for (int i=1;i<=n;++i)  cin >>d[i]>>s[i];
    p=n;
    for (int i=n-1;i>=1;--i)
        if ((s[i]-s[p])*t>=d[p]-d[i])
            cnt--;else p=i;
    cout <<cnt<<endl;
    return 0;
}
```

---

## 作者：_ZZH (赞：3)

单调队列了解一下？

我们将牛的顺序倒着排，按照牛的速度形成单增队列，对于每一只牛，我们判断它能否追上队尾的牛，如果能，将ans-1（初值为n，表示有多少小组），如果不能，将其入队。

因为我们容易发现，如果下一只牛跑得过这只牛前面的牛，那么它不一定比这只牛跑得快（因为它追上上一只牛会减速，而下一只牛追它则不按照减速），所以如果一只牛能追上队尾的牛，那么下一只牛追当前队尾的牛一定比追这一只牛容易些。

放代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
int n,t,ans;
struct cym{
	int _speed;
	int pos;
}a[100010];
deque<cym>q;
int main()
{
	scanf("%d%d",&n,&t);
	ans=n;
	for(int i=n;i>=1;i--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		a[i]._speed=y;
		a[i].pos=x;
	}
	for(int i=1;i<=n;i++)
	{
		while(!q.empty())
		{
			cym now=q.back();
			if(a[i]._speed<=now._speed)
			q.pop_back();
			else
			break;
		}
		if(!q.empty())
		{
		cym cnt=q.back();
		if((cnt.pos-a[i].pos)/(a[i]._speed-cnt._speed)<=t)
		ans--;
		else
		q.push_back(a[i]);
		}
		else	
		q.push_back(a[i]);
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Thomasguo666 (赞：2)

如何判断一头牛是否能追上另一头呢？
设一头牛速度为$v_i$，起点为$p_i$，另一头速度为$v_j$，起点为$p_j$($v_i\gt v_j,p_i\leq p_j$，否则追不上)，则$$(p_j-p_i)/(v_i-v_j)\leq T$$

相当于
$$p_j+T*v_j\leq p_i+T*v_i$$

所以反向扫一遍就行啦！
具体看代码：

py:
```python
n,t=input().split()
n=int(n)
t=int(t)
p=[]
v=[]
ans=1
for i in range(n):
    a,b=input().split()
    p.append(int(a))
    v.append(int(b))
    p[i]=p[i]+v[i]*t
for i in range(n-2,-1,-1):
    if p[i]<p[i+1]:
        ans=ans+1
    else:
        p[i]=p[i+1]
print(ans)
```
c++:
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll p[100005],v[100005];
int main()
{
	ll n,t,ans=1;
	cin>>n>>t;
	for (ll i=1;i<=n;i++) cin>>p[i]>>v[i],p[i]+=v[i]*t;
	for (ll i=n-1;i>0;i--) ans+=(p[i]<p[i+1]?1:(p[i]=p[i+1])*0);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Lance1ot (赞：2)

将一个牛跑的起点和跑的终点组成一条线段

然后我们可以知道，如果有两条线段不包含，就一定不会缩成一组。

如果包含，则会缩成一组，且右端点变成最小的辣一个。

然后我们进行如此操作，求最后又多少个组

自我感觉是递增的单调队列

我们在输入时就已经保证了起点是有序的，然后我们可以利用单调队列模拟一下这个过程。

我们入队一个元素，如果队尾的元素大于我们当前入队的元素，我们就可以知道，当前我们处理的选段被已经处理的线段所包含，我们就要更改吗。

然后说出队的事情，如果我们当前处理的线段的左端点已经比队首要大了，那么那些没有被处理的选段就一定不对现在的队首进行影响。出队时答案加一

最后输出已经出队的元素的个数+队中元素的个数

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int manx=101000;
long long que[manx<<1];
int head=1,tail=0;
long long ans;
void push(long long val)
{
	while(que[tail]>=val&&tail>=head)	tail--;
	que[++tail]=val;
	return ;
}
void pop(long long val)
{
	while(que[head]<=val)	head++,ans++;
	return ;
}
int main()
{
	int n,t;
	scanf("%d%d",&n,&t);
	long long a,b;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a,&b);
		push(a+b*t);
		if(a>=que[head]) pop(a);
	}
	printf("%lld",1ll*ans+tail-head+1);
}
```

---

## 作者：OIer991215 (赞：1)

数据水，wys保佑我n^2过十万。

将速度从小到大排序，从最慢的奶牛开始枚举，这头奶牛左边凡是最终能超过这头奶牛的奶牛试做一个整体，往后就不用遍历了。

最后数一下多少个奶牛被枚举到，就是答案。

hack数据，生成一个 位置和速度都递减的数据，我的代码就TLE了。

但我的做法是有勇气的，居然过了。


```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
long long n,t,ans;
bool vis[1010100];
struct pro
{
    long long pos,v;
}cow[1010100];
bool cmp(pro a,pro b)
{
    return a.v<b.v;
}
int main()
{
    scanf("%lld%lld",&n,&t);
    for(int i=1; i<=n; i++)
        scanf("%lld%lld",&cow[i].pos,&cow[i].v);
    sort(cow+1,cow+1+n,cmp);
    for(int i=1; i<=n; i++)
        if(!vis[i])
        {
            for(int j=1; j<=n; j++)
            {
                if(cow[j].pos>=cow[i].pos)
                    continue;
                long long x=cow[j].pos + cow[j].v*t;
                long long y=cow[i].pos + cow[i].v*t;
                if(x>=y)
                    vis[j]=1;
            }
            ans++;
        }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Create_Random (赞：0)

一道模拟题

本蒟蒻的思路：

让每头牛先跑到最终位置

如果后面的牛在前面的牛之前或与其在同一位置

就把它的位置移动到前面的牛的位置

注意要从后往前修改！！！

（不然求的剩余组数会出锅）

然后按照其最终位置求出剩余组数

最终的数量就是答案

注意开long long！！！

贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,t;
long long ans=1;//最开始就有一组
struct node
{
	long long p,s;
}a[100010];
bool cmp(node x,node y)
{
	return x.p<y.p;//把最终位置从小到大排
}
int main()
{
	scanf("%d%d",&n,&t);
	for(long long i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].p,&a[i].s);
		a[i].p=a[i].p+a[i].s*t;//直接求出每头牛的最终位置
	}
	for(long long i=n;i>=1;i--)//注意从后向前修改
	{
		if(a[i-1].p>=a[i].p)
		{
			a[i-1].p=a[i].p;
		}
	}
	unique(a+1,a+n+1,cmp);//直接修改为组数
	for(long long i=2;i<=n;i++)//统计最终组数
	{
		if(a[i-1].p<a[i].p)
		{
			ans++;
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Yuanchenpu (赞：0)

可以用贪心算法解决

先处理出每头牛在不减速的情况下的最终距离d

考虑从后往前扫，维护一头当前能跑得最近的一头牛p, 设当前处理到第i头牛.

如果d[i] >= d[p], 则牛i可以追上牛p, 更新答案；否则将p更新为i.

上代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;

typedef long long ll;
const int MAXN = 1e5 + 10;

ll p[MAXN], s[MAXN], d[MAXN];
ll n, t;

int main() {
	scanf("%lld%lld", &n, &t);
	for (register int i = 1; i <= n; i++) {
		scanf("%lld%lld", &p[i], &s[i]);
		d[i] = p[i] + s[i] * t;
	}
   ll ans = n, x = n;
	for (int i = n - 1; i >= 1; i--) {
		if (d[i] >= d[x]) {
			ans--;
		} else {
			x = i;
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：yz0414 (赞：0)

那个.....

在场的老P可能受苦了

粗粗看了一下题解，根本没有pascal的（-_-||）

那么，就让我来带大家脱离苦海吧！（当我没说）

嗯嗯，回归正题

这是一道用暴力模拟就可以解决的问题。
我们只需要先求出各自的最后状态，因为在后面的牛最终位置超过了前面的牛,那么他们一定合并在一起了,所以从前往后依次合并就可以了.

附上代码：

```pascal
var i:longint; n,t,x,y,ans:int64;
    m:array[0..100001]of int64;
begin
   readln(n,t);
   for i:=1 to n do
     begin
        readln(x,y);
        m[i]:=x+(y*t);
     end;
   ans:=n;
   for i:=n downto 2 do
     if m[i-1]>=m[i] then
      begin
         dec(ans);
         m[i-1]:=m[i];
      end;
   writeln(ans);
end.
```
我的程序还是比较短的呢~~

---

## 作者：yxl_ (赞：0)

 这是一道用暴力模拟就可以解决的问题。
 

我们只需要先求出各自的最后状态，因为在后面的牛最终位置超过了前面的牛,那么他们一定合并在一起了,所以从前往后依次合并就可以了.


```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	long long  x;
	long long  v;
}f[100001];
long long  m[100001];
int ans;
long long n,t;
int sum[100001];
int main(){
	scanf("%lld%lld",&n,&t);
	for(register long long i=1;i<=n;i++){
	    scanf("%lld%lld",&f[i].x,&f[i].v);
	    m[i]=f[i].x+(f[i].v*t);
		}
	ans=n;
	for(long long i=n;i>=2;i--){
		if(m[i-1]>=m[i]){
			ans--;
			m[i-1]=m[i];
		}			
	}
	cout<<ans;
}
```

---

## 作者：曹老师 (赞：0)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco14dec-cowjog.html)

简单的模拟题。

直接求出如果没有限制的时候牛的位置，从后向前扫一遍，如果发现前一头牛比后一头牛靠后，说明前一头牛被限制了，如果没有的话，答案加一。

**时间复杂度：$O(n)$**

## Code ##

```
#include<iostream>
#include<cstdio>
using namespace std;

int n;
long long t , val[100005] , ans = 0;

int main() {
	scanf("%d%lld",&n,&t);
	for(int i=1; i<=n; i++) {
		long long x , y;
		scanf("%lld%lld",&x,&y);
		val[i] = x + y * t;
	}
	for(int i=n-1; i>=1; i--) {
		if(val[i] >= val[i+1])
			val[i] = val[i+1];
		else
			ans++;
	}
	printf("%lld",ans+1);
	return 0;
}
```


  [1]: http://usaco.org/index.php?page=viewproblem2&cpid=493
  [2]: https://www.luogu.org/problemnew/show/P3111

---

## 作者：Limerick (赞：0)

首先感谢大神yg对我的指导，

其实这题十分的水，

题意：有n头奶牛在一条线上，每头奶牛有一个速度和一个初始位置，当后面的奶牛追上前面的奶牛时，两头奶牛就并成一个小组。

当后一头奶牛可以追上前一头奶牛时（即（前一头奶牛的初始位置-后一头奶牛的初始位置）/（后一头奶牛的速度-前一头奶牛的速度）>=T）&&（后一头奶牛的速度>前一头奶牛的速度）)就把后一头奶牛的位置设置成前面一头奶牛的位置，否则后一头奶牛的位置不变，ans++。

附上AC代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<ctime>
using namespace std;
```
/\*
P3111牛慢跑  题解

\*/
```cpp
const int N=100005;
long long n,t,i,s,ans=1;
struct node{
    long long x,v;
}a[N];
bool cmp(node p,node q){
    return p.x<q.x;
}
int main(){
    cin>>n>>t;
    for(i=1;i<=n;i++){
        cin>>a[i].x>>a[i].v;//读入
    }
    sort(a+1,a+1+n,cmp);//注意:原初始位置不是有序的,要先排序
    s=a[n].x+t*a[n].v;//最后一头奶牛最终到达的地点
    for(i=n-1;i>=1;i--){//注意:要倒着模拟
        if((a[i].x+a[i].v*t)<s){
            ans++;
```
}//后一头奶牛追不上前一头奶牛
s=min(s,a[i].x+a[i].v\*t);//注意:要取当前奶牛最终到达的地点和s的最小值,否则会WA

```cpp
    }
    cout<<ans<<endl;
    exit(0);
}

```

---

