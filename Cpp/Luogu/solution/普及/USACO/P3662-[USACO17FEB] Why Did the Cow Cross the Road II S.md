# [USACO17FEB] Why Did the Cow Cross the Road II S

## 题目描述

穿过 Farmer John 农场的长路上有 $N$ 个人行横道，方便地用编号 $1 \ldots N$ 标识（$1 \leq N \leq 100,000$）。为了让奶牛能够通过这些横道过马路，FJ 安装了电子过马路信号灯，当奶牛可以安全过马路时，信号灯会显示绿色的奶牛图标，否则显示红色。不幸的是，一场大雷暴损坏了他的一些信号灯。给定损坏信号灯的列表，请计算 FJ 需要修复的最少信号灯数量，以便存在至少 $K$ 个连续的信号灯正常工作。

## 样例 #1

### 输入

```
10 6 5
2
10
1
5
9```

### 输出

```
1```

# 题解

## 作者：Anguei (赞：31)

考虑枚举每个长度为 $K$ 的区间端点。由于区间长度固定，所以枚举所有区间的时间复杂度为 $O(N)$（只需要移动端点位置即可）。既然枚举的区间长度已经固定为 $K$，那么区间内所有损坏信号灯都要修复。因此可以在读入损坏信号灯数据的时候预处理前缀和，在每次区间枚举过程中 $O(1)$ 查询。

已损坏的位置值为一，未损坏的值为零，那么这道题就转化为了长度固定的区间求最小和。

总时间复杂度 $O(N)$。

```cpp
// 代码里的 rep(i, a, b) 相当于 for (int i = a; i <= b; ++i)
// read() 和 println() 就是快读/快写
const int N = 100000 + 5;
int n, k, b, a[N], s[N], ans = -1u / 2; // -1u / 2 就是 int 最大值
int main() {
    n = read(), k = read(), b = read();
    rep(i, 1, b) a[read()] = 1;
    rep(i, 1, n) s[i] = s[i - 1] + a[i];
    rep(i, k, n) ans = std::min(ans, s[i] - s[i - k]);
    println(ans);
}
```

---

## 作者：Drug__Lover (赞：16)

**前缀和**

**由于区间的长度已经确定了**

**那么我们可以通过枚举区间的左端点来确定一个区间**

**枚举每一个长度为k的区间，然后就判断哪一个区间中损坏的灯的数目最少**

**取min之后输出就可以了**


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define maxn 100201
using namespace std;
int n,k,b;
int vis[maxn];
int sum[maxn];
int ans=0x7fffffff;
int main()
{
    cin>>n>>k>>b;
    for(int i=1;i<=b;i++)    
    {
        int x;
        scanf("%d",&x);
        vis[x]=1;
    }
    for(int i=1;i<=n;i++) sum[i]+=sum[i-1]+vis[i];
    for(int i=1;i<=n-k+1;i++) ans=min(ans,sum[i+k-1]-sum[i-1]);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：黑发隐士 (赞：9)

###  看提交的人不多，以为掉进了dalao坑
### 但看了下题感觉不是多难
#### 就先用题目的样例来说
#### 我们用“*”表示坏掉的灯
       1  2  3  4  5  6  7  8  9  10
       *  *        *           *  * 
       ————————————————   ← 盒子
#### 假设有一个盒子，长度是K，从1开始，它可以向右移动
#### 题目就变成了盒子里最少包含多少个“*”
#### 只要设置一个区间就可以了
#### 不断更新最小值
#### 当到达尾部时就返回值
下面附上代码

```cpp
#include<bits/stdc++.h>
#define FOR(i, l, r)  for(int i=l;i<=r;i++)//用一个define代表下面的“FOR（i, 初始值, 结束值）”为“for(int i=初始值; i<=结束值; i++)” 两者等价；

using namespace std;

int n,b,k,ans,r,l,tot=100010;
int a[100050];

int search(int l,int r)
{
	if(r > n) return tot;//到了return
	FOR(i, 1, b) if(a[i]>=l && a[i]<=r) ans++;计数
	tot=min(ans,tot);//比较取小的
	ans=0;
	search(l+1,r+1);
}

int main()
{
	scanf("%d%d%d" ,&n ,&k, &b);
	FOR(i, 1, b) 
	  scanf("%d",&a[i]);//输入
	l = 1; r = k;
	cout<<search(l,r);
    return 0;
} 
```
写的不太好，望dalao们海涵(｡・`ω´･)

---

## 作者：Countjoyyauldly (赞：5)

# 前言

以为大佬们都会用队列来切这道题，但发现没几个，都用的前缀和什么的，~~这不就浪费了标签里面的队列吗~~（doge）
希望蒟蒻的队列对大家有帮助

# 正片

#### 这道题的基本思路是每次将区间向右移动1个单位，记录这个区间内坏掉灯的数量，当数量最少时就是答案

于是本蒟蒻就写了个伪的队列（用循环也可以实现）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,b;
queue<char>ser;
int br[100005];
char sd[100005];
int sum;
int ans;
int minn=21473648;
int main()
{
    cin>>n>>k>>b;
    for(int i=1; i<=b; i++)
        cin>>br[i];
    sort(br+1,br+b+1);
    memset(sd,' ',sizeof(sd));
    for(int i=1; i<=b; i++)
        sd[br[i]]='*';
    for(int i=1; i<=k; i++)
        ser.push(sd[i]);
    sum=ser.size();
    while(sum<=n)
    {
        for(int i=1; i<=k; i++)
        {
            if(ser.front()=='*')
                ans++;
            ser.pop();
        }
        sum++;
        for(int i=sum-k+1; i<=sum+1; i++)
            ser.push(sd[i]);
        //cout<<"ans:"<<ans<<" ";
        minn=min(ans,minn);
        ans=0;
    }
    cout<<minn;
    return 0;
}
```

但是这个写法的时间复杂度为O(k*n)，会tle6个点，
原因也在于以下代码

```cpp

    while(sum<=n)
    {
        for(int i=1; i<=k; i++)
        {
            if(ser.front()=='*')
                ans++;
            ser.pop();
        }
        sum++;
        for(int i=sum-k+1; i<=sum+1; i++)
            ser.push(sd[i]);
        //cout<<"ans:"<<ans<<" ";
        minn=min(ans,minn);
        ans=0;
    }

    return 0;
}
```

所以我们不能全部进队，判断，再全部出队，这就是tle的原因。

优化自然就是很简单了，只要弹出队首，进队尾，并不清空队列即可。代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,b;
queue<char>ser;
int br[100005];
char sd[100005];
bool ch[100005];
int sum;
int ans;
int minn=21473648;
int main()
{
    cin>>n>>k>>b;
    for(int i=1; i<=b; i++)
        cin>>br[i];
    sort(br+1,br+b+1);
    memset(sd,' ',sizeof(sd));
    for(int i=1; i<=b; i++)
    {
        sd[br[i]]='*';
        ch[br[i]]=1;
    }
    for(int i=1;i<=k;i++)
    {
        ser.push(sd[i]);
        if(ch[i])
        ans++;
    }
    minn=ans;
    for(int i=k+1;i<=n;i++)
	{

		ser.push(sd[i]);
		if(ch[i]==1)
		{
			minn++;
		}
		if(ser.front()=='*')
		minn--;
		ser.pop();
		ans=min(minn,ans);

	}
    cout<<ans;
return 0;
}

```

希望管理大大给过，因为题解区的队列写法好像没有（可能我眼瞎？）


---

## 作者：船医 (赞：4)

刚开始想用暴力直接枚举长度为k的区间，但是我的n*k算法TLE了呜。（看到有枚举的大佬，~~果然是我太弱~~）

但想想我的枚举区间的过程，我突然发现我可以用队列来模拟这个过程。

只需要在**入队**和**出队**的时候根据他们是否损坏对当前的sum进行增减，再在一次循环的结束后对ans和sum进行取min操作。

这样一个n次循环就可以解决，就是一个O(n)的算法啦！

代码及注释如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
queue <int> q;//STL大法好
int n,k,b,ans=0,t;
bool d[100005];//是否损坏
int main (){
    cin>>n>>k>>b;
    for(int i=1;i<=b;i++)
    {
    	cin>>t;
    	d[t]=1;
	}
	for(int i=1;i<=k;i++)
	{
		q.push(i);
		if(d[i]==1)
		{
			ans++;
		}
	}//先进行初始化
	int sum=ans;//初始化sum
	for(int i=k+1;i<=n;i++)
	{
		
		q.push(i);
		if(d[i]==1)//如果损坏
		{
			sum++;
		}
		if(d[q.front()])//如果队头损坏，那么pop时sum就要减少
		sum--;
		q.pop();
		ans=min(ans,sum);
	}
	cout<<ans;
    return 0;
}
```
完

---

## 作者：deleted (赞：2)

我们考虑这样的思路：

对于每个点，用前缀和求出该点到起点的断点个数。

从$1$到$n-k+1$（要保留长度为$k$的区间，所以只能枚举到$n-k+1$）枚举每个点，查询以该点为左端点的长度为$K$的区间中有多少个断点，不断尝试更新答案。

先上代码。

```cpp
#include<bits/stdc++.h>//P3662 [USACO17FEB]Why Did the Cow Cross the Road II S
using namespace std;
#define re register
#define N 100010
#define INF 999999999
int n,k,b,ans=INF;
int a[N],sum[N],vis[N];
int main()
{
	cin>>n>>k>>b;
	for(re int i=1;i<=b;i++)
	{
		cin>>a[i];
		vis[a[i]]=1;
	}
	for(re int i=1;i<=n;i++)
		sum[i]=sum[i-1]+vis[i];
	for(re int i=1;i<=n-k+1;i++)
	{
		int last=i+k-1;
		int num=sum[last]-sum[i];
		ans=min(ans,num);
	}
	cout<<ans<<endl;
	return 0;
}
```

下面来解释一下。

$n$、$k$、$b$的意思如题；$ans$是答案，也就是最少要修的信号灯数量。$a$数组储存损坏的信号灯编号；$sum[i]$ 表示从第1个信号灯到第$i$个信号灯中损坏的个数；$vis[i]$ 储存第$i$个点的情况，若损坏则值为1，反之值为0。

这样做是$O(n)$复杂度的，可以通过本题。

---

## 作者：封禁用户 (赞：2)

#### ~~~~此题很水
	刚刚看到这题还以为很强 其实非常好写（喂！！！）
   1.由于给出了区间的长度，如果直接的暴力显然是不可取的会TLE，但是这题如果离线做会降低许多复杂度
   给出了区间长度为K  
   w代表区间的第一个数初始化是在第一个路灯下，h代表末尾开始时h=K。
   所以w和h走的最大长度均为n-k  
   2.
   先把1~k需要维修的路灯统计出来作为sum和ans的初值
   随后移动区间每移完一次都要判断刚刚进来的这个数和刚刚出去的的灯是好的还是坏的  
   **如果进来的是坏的那么sum++  
   如果走的是坏的sum--**  
   判断代码：  
   if(a[w]==1)
        sum++;  
    if(a[h-1]==1)
        sum--;  
   3.
	接下来每一次移动操作后把sum去跟ans比对，因为取最小值所以if(ans>sum)ans=sum;  
   以下是代码
   

------------


------------

```cpp
#include<cstdio>
#include<iostream>
int a[100005];
using namespace std;
int main()
{
    int n,k,b;
    cin>>n>>k>>b;
    int v,ans=n;
    for(int i=1;i<=b;i++)
    {
        scanf("%d",&v);
        a[v]=1;
    }
int sum=0;
int h=2,w=k+1;
    for(int y=1;y<=k;y++)
    {
        if(a[y]==1)
        sum++;
    }
for(int u=2;u<=n-k;u++)
{
    if(a[w]==1)
        sum++;
    if(a[h-1]==1)
        sum--;
    if(ans>sum)
        ans=sum;
    w++;
    h++;
}
printf("%d",ans);
return 0;
}

```


---

## 作者：entity (赞：1)

### 水的一批
这道题我的大致解法：计算出前k个点中损坏的数目之后一直向后枚举

每一次枚举：记录区间的的损坏数目t，每一次去除最前面的，如果是损坏的则t--，之后加上最后面的点，如果是损坏的就t++

看题解中大多数巨佬都写前缀和，但是我这应该不算前缀和，况且前缀和我也不会，本人太弱，枚举万岁（doge）

### 上代码
```cpp
#include<cstdio>
using namespace std;
/*
10 6 5
2
10
1
5
9
*/
int n,m,k;
bool dat[100001]={};
int minn=100001,t=0;
int min(int a,int b){
	return a<b?a:b;
}
int main(){
	scanf("%d%d%d",&n,&k,&m);
	for(int i=1;i<=m;i++){
		int x;
		scanf("%d",&x);
		dat[x]=1;
	}//读入
	for(int i=1;i<=k;i++) if(dat[i]) t++;//计算出前k个点中损坏的数目
	for(int i=k+1;i<=n;i++){
		if(dat[i-k]) t-=1;//去除最前面的点，如果是损坏的t--
		if(dat[i]) t++;//加上最后一个，如果是损坏的就t++
		minn=min(minn,t);//取最小值
	}
	printf("%d",minn);
	return 0;
} 
```


---

## 作者：zhangyuhan (赞：1)

一道很好的利用前缀和的题。

这道题题目描述很清楚，如果乍一看没有思路的话，我们可以考虑画图。

| $1$ | $1$ | $0$ | $0$ | $1$ | $0$ | $0$ | $0$ | $1$ | $1$ |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |

这是由样例画出的图。其中$1$表示损坏，$0$表示未损坏。

题目要求最少的维修量，使得有连续的$K$个灯。

由于区间长度被固定为$K$，所以我们可以考虑枚举区间，来修理区间中的灯，求出每次中的最少量即可。

如果采用朴素做法，及每次枚举区间时来计算需要修理的电灯数量，时间复杂度为$O(NK)$，太慢了。

让我们来考虑优化。

由于这道题涉及到区间求值，而且没有任何修改操作，所以我们很容易想到前缀和。

所以我们考虑将需要修理的位置赋为$1$，其余赋为$0$，用前缀和就能很容易的得到每个区间需要修理的电灯数了。

时间复杂度：$O(N)$，可过。

$AC$ $Code$

```cpp
#include <iostream>
#define _for(i, a, b) for (int i=(a); i<=(b); i++)
using namespace std;

const int MAXN = 100010;

int light[MAXN], s[MAXN], n, k, b, ans = 1e9;//由于求最小值，ans要赋大

int main() {
    cin >> n >> k >> b;
    _for (i, 1, b) {
        int x;
        cin >> x;
        light[x] = 1;
    } //读入+初始化
    _for (i, 1, n) s[i] = s[i-1] + light[i];//前缀和初始化
    _for (i, k, n) ans = min(ans, s[i] - s[i-k]);//统计答案。注意！i的下限为k，否则会溢出
    cout << ans << endl;//输出答案
    return 0;//完结撒花！
}
```

---

## 作者：fangxk2003 (赞：1)

这题的难度也就普及组第二道吧

线性的类似于队列的算法

首先枚举1~k个中，有多少个是损坏的信号灯，然后只要每次队首进一个，队尾出一个，然后处理一下就好了。

时间复杂度O（n）

详见代码。

【参考程序】

```cpp
var n,k,b,i,x,min,now:longint;
    a:array[1..100000]of integer;
begin
 //assign(input,'maxcross.in');reset(input);
 //assign(output,'maxcross.out');rewrite(output);
 readln(n,k,b);
 for i:=1 to b do
 begin
  readln(x);
  a[x]:=1;
 end;
 for i:=1 to k do
  inc(now,a[i]);
 min:=now;//最小值初始化
 for i:=k+1 to n do
 begin
  inc(now,a[i]);//进队列
  dec(now,a[i-k]);//出队列
  if now<min then min:=now;
 end;
 writeln(min);
 close(input);close(output);
end.

```

---

## 作者：小手冰凉 (赞：0)

AC中最短的代码O(∩\_∩)O


这道题可以用非常好用的区间伸缩大法（貌似就是滑动窗口？）


当该区间符合条件时记录答案并且左区间右移，否则右区间左移


和单调队列的思想貌似有点类似，不过简单许多


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,b,k,a[100005],l,ans;
int main(){
    scanf("%d%d%d",&n,&k,&b);
    for(int i=1;i<=b;i++)scanf("%d",&a[i]);
    sort(a+1,a+b+1),l=0,ans=b,a[n+1]=n+1;
    for(int i=1;i<=n+1;i++)while(a[i]-a[l]>k)ans=min(i-l-1,ans),l++;//区间伸缩大法吼哇
    printf("%d",ans);
    return 0;
}
```

---

## 作者：jzqjzq (赞：0)

滑动窗口？

我们可以把题目看作一个k的连续区间的破掉的灯个数的最小值

我们把这个长度为k的窗口一个个滑过去，统计一下答案，取最小值

这个过程当然也可以用前缀和来实现，我是直接滑动窗口的

代码就不多解释了

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <ctime>
#include <map>
#include <queue>
#include <cstdlib>
#include <string>
#include <climits>
#include <set>
#include <vector>
using namespace std;
bool b[100010];
int main()
{
    int n,k,m;scanf("%d%d%d",&n,&k,&m);
    for(int i=1;i<=m;i++){
        int x;scanf("%d",&x);
        b[x]=1;
    }
    int l=1,r=0,p=0;while(r<k)p+=b[++r];int ans=p;
    while(r<n){
        p-=b[l++];p+=b[++r];
        ans=min(ans,p);
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：OfstAutomataMachine (赞：0)

一道相当水的题目

考虑任意一个长度为 $k$ 的区间，如果这个区间的坏掉的灯最少，就是答案。

可以用前缀和来计算每个区间有多少坏的灯，时间复杂度为 $O(n)$ 。

喜闻乐见的代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,k,b,ans,a[100001],f[100001];
int main()
{
	cin>>n>>k>>b;
	ans=k;
	while(b--)
	{
		int t;
		cin>>t;
		a[t]=1;
	}
	for(int i=1;i<=n;i++)
		f[i]=f[i-1]+a[i];
	for(int i=1;i<=n-k;i++)
		ans=min(ans,f[i+k]-f[i]);
	cout<<ans;
	return 0;
}
```


---

## 作者：sunson (赞：0)

一看到查询区间最值我就忍不住打树状数组（毕竟短，不费脑）

~~线段树表示不满~~

这里提一下树状数组的坑：

**ask时一定要将区间左值减一**

但这一题中ask(i)-ask(i-k)

是因为加一（m到n一共n-m+1个数）和减一抵消了

```
#include<bits/stdc++.h>
using namespace std;
int a[100005];
int n,k,b;
void add(int x,int y){
	for(;x<=n;x+=x&-x){
		a[x]++;
	}
}
int ask(int x){
	int ans=0;
	for(;x;x-=x&-x){
		ans+=a[x];
	}
	return ans;
}
int mian(){
	int minx=1<<30;
	cin>>n>>k>>b;
	for(int i=1;i<=b;i++){
		int q;
		cin>>q;
		if(ask(q)-ask(q-1)==0)//判重
		add(q,1);
	}
	for(int i=k+1;i<=n;i++){
		int a=ask(i)-ask(i-k);
		minx=min(a,minx);
	}
	cout<<minx<<endl;
	return 0;
} 
```

---

