# [POI 2005] SAM-Toy Cars

## 题目描述

Jasio 是一个只有三岁的小男孩，他喜欢玩玩具车。他有 $n$ 辆玩具车被保存在书架上。

架子上的玩具车 Jasio 拿不到，但地板上的他可以拿到。Jasio 的母亲会帮 Jasio 拿架子上的玩具车到地板上。

地板最多只能放 $k$ 辆玩具车。

当地板已经放了 $k$ 辆玩具车时，Jasio 的母亲都会从地板上先拿走一个玩具车放回书架，再拿来 Jasio 想要的玩具车。

现在 Jasio 一共想依次玩 $p$ 个玩具车，问 Jasio 的母亲最少需要拿几次玩具车。（只算拿下来的，不算拿上去的）

## 说明/提示

对于 $100\%$ 的数据：$1\le k\le n\le 10^5$，$1\le p\le 5\times 10^5$，$1\le a_i\le n$。

## 样例 #1

### 输入

```
3 2 7
1
2
3
1
3
1
2```

### 输出

```
4```

# 题解

## 作者：oscar (赞：20)

【POI补全计划#3 POI2005 SAM】

这题貌似是个经典贪心诶

每次选择将来最晚用到的玩具放上柜子就好了

**本做法根本不需要手写堆**

我们先预处理一个NEXT数组，

NEXT[i]=j 代表与第i个位置的数相同的数下一次出现在第j个位置

接下来使用priority\_queue

比较函数自己写一个

```cpp
struct cmp
{
    inline bool operator()(const int &x,const int &y)
    {
        return NEXT[x]<NEXT[y];
    }
};
```
注意传给priority\_queue的模板参数必须要是一个class/struct

然后这么声明priority\_queue

```cpp
priority_queue<int,vector<int>,cmp> pq;
```
接下来就是一个模拟的过程，开一个数组记录当前哪些玩具在地上

每次发现一个要玩的玩具不在地上且地上的玩具满的时候（相当于优先队列大小恰好等于 $ k $ ）把优先队列中将要最后使用的玩具放到柜子上，再把柜子上的玩具拿下来

**但是这里有点问题：**

**如果某个玩具在地上的话是不会更新优先队列中的时间信息的**

**观察到如果一个玩具被使用过后就再也不会成为优先队列的top**

**所以我们每次发现玩具在地上时把地板大小（ $ k $ ）+1就好了**


考虑到我可能讲得不清楚，我还是贴一下代码吧：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=100010,MAXM=500010;
queue<int> q[MAXN];
int NEXT[MAXM];
int a[MAXM];
int n,k,m;
struct cmp
{
    inline bool operator()(const int &x,const int &y)
    {
        return NEXT[x]<NEXT[y];
    }
};
priority_queue<int,vector<int>,cmp> pq;
int inq[MAXN],ans;
int main()
{
    scanf("%d%d%d",&n,&k,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&a[i]);
        q[a[i]].push(i);
    }
    for(int i=1;i<=m;i++)
    {
        q[a[i]].pop();
        if(q[a[i]].empty())NEXT[i]=m+1;
        else NEXT[i]=q[a[i]].front();
    }
    for(int i=1;i<=m;i++)
    {
        if(!inq[a[i]])
        {
            if(pq.size()==k)
            {
                inq[a[pq.top()]]=0;
                pq.pop();
            }
            pq.push(i);
            ++ans;
            inq[a[i]]=1;
        }
        else
        {
            ++k;
            pq.push(i);
        }
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：千里马 (赞：14)

## [P3419 SAM-Toy Cars](https://www.luogu.org/problem/P3419)
这道题用贪心的思想。

假如现在地板满了，我要去架子上取某个玩具，那么我要把谁放回去呢？

很自然的想到把下次玩的时间最晚的那个玩具放回（如果某个玩具之后再也不玩了，那么下次玩的时间为inf）。

关键是如何确定下次玩的时间最晚的那个玩具，这时我们想到优先队列，用堆维护玩具下次玩的时间的最大值。

~~楼下有几篇讲的很详细，但自我感觉我的代码实现比较简单~~

具体看代码注释吧。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
priority_queue<pair<int,int> > q;
int n,k,m,ans;
int a[500100],s[500100],p[100100];
bool v[100100];
int main()
{
	cin>>n>>k>>m;
	for(int i=1;i<=m;++i) scanf("%d",&a[i]);
	//倒序枚举m个玩具，P记录该玩具上次出现的位置，再次出现时赋给S 
	for(int i=m;i>=1;i--){
		if(p[a[i]]==0) s[i]=1e6;
		else s[i]=p[a[i]];
		p[a[i]]=i;
	}
	for(int i=1;i<=m;++i){
		if(v[a[i]]) k++,q.push(make_pair(s[i],a[i]));//已经在队列中，但更新不便，所以用k++代替 
		else{
			if(q.size()==k)v[q.top().second]=0,q.pop();//若队列已满，取出下次出现最晚的，即队头 
			q.push(make_pair(s[i],a[i])),v[a[i]]=1;
		        ans++;
		    }
	}
	printf("%d\n",ans);
}
```


---

## 作者：trickedout (赞：8)

### 实际上是一道贪心题：
	以样例为例：
    3 2 7
    1 2 3 1 3 1 2
    在地面上玩具超过k时，拿下一件玩具的同时需要放回一件玩具才能满足要求
    在样例中，在地面上放置1，2玩具后，现在玩具数量达到饱和，而下一步需要将3号玩具放在地上，则需要从1、2中拿回一件玩具
    那么为了尽量少拿，以后还要用的玩具最好不要放回。则最优情况应为放回从现在起“最不急需”的玩具（即从现在起最后使用的玩具）
    由此看来可以用贪心的思想。
### 怎样考虑放置情况
    考虑放置的最终目的是为了得到玩具使用的“急需度”（先后顺序），容易想到使用一个数组将玩具的先后顺序存储下来。
    这里可以使用一个nxt数组，nxt[i]用来表示第i个需要使用的玩具下一次出现的位置。
    那么怎么处理呢？
```cpp
	for(int i = 1; i <= p; ++i)	
	{
		in(a[i]);
		if(head[a[i]]) nxt[head[a[i]]] = i;
		head[a[i]] = i;
	}
```

	这里我用到了类似前向星的形式,head[i]表示第i个玩具的上一个，那么自然nxt[head[a[i]] = i即当前玩具为上一个的下一次出现位置。
    同时还有一种情况：即当前玩具使用后就不再使用了。
```cpp
	for(int i = 1; i <= p; ++i)
		if(!nxt[i]) nxt[i] = p + 1;
```
	于是再进行这样一步操作，没有处理到的玩具不会再被使用，将它的下一次出现位置定位到边界。
    这样我们就将玩具使用的先后顺序存储下来了，再之后的贪心过程中进行最优选择。
### 贪心过程中玩具先后顺序的维护
	在处理过程中需要维护一个nxt的大根堆。
    定义一个结构体存储玩具的编号和nxt。
```cpp
	struct Toy
	{
		int num, nxt;
		bool operator < (const Toy &toy) const
		{
			return nxt < toy.nxt;
		}
	};
    priority_queue <Toy> q;
```
	大根堆的维护就可以利用重载运算符 + STL priority_queue 实现 
### 怎样考虑放置 k个玩具达到“饱和” 的情况
	在未放置满k个的状态下，遇到未被放置的编号的玩具可以直接放置（入队）。
    这里需要用到一个chosen数组，表示玩具是否被选择放在地上,同时定义一个ans表示操作次数。
```cpp
	bool chosen[1000010];
    int ans = 0;
```
在枚举过程中如果未达饱和，操作如下：
```cpp
		if(chosen[a[i]])//玩具已被放置地上
		{
			q.push((Toy)
			{
				a[i], nxt[i]
			});
			continue;//玩具入队
		}
		if(k)
		{
			q.push((Toy)
			{
				a[i], nxt[i]
			});//将当前玩具入队（找到了新玩具并未饱和）
			chosen[a[i]] = 1;//标记已放地上
			k--, ans++;//增加操作次数，减小“饱和度” k
		}
```
在达到饱和状态后（地上玩具达到k时）：
```cpp
		else
		{
			while(!chosen[q.top().num]) q.pop();//寻找到被放置地上的玩具
			chosen[q.top().num] = 0;
			q.pop();//将玩具放回，取消标记
			q.push((Toy)
			{
				a[i], nxt[i]
			});
			chosen[a[i]] = 1;//放置新玩具并标记
			ans++;//增加操作次数
		}
```
在两种情况的操作结束后，ans即为最后的答案（最少操作次数）。
### 最后贴上完整代码供参考
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define open(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)
#define close fclose(stdin), fclose(stdout)
using namespace std;
template <typename T> void in(T &a)
{
	T num = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch))
	{
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(isdigit(ch)) num = (num << 3) + (num << 1) + ch - '0', ch = getchar();
	a = num * f;
}
void print(int x)
{
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
struct Toy
{
	int num, nxt;
	bool operator < (const Toy &toy) const
	{
		return nxt < toy.nxt;
	}
};
priority_queue <Toy> q;
int n, k, p, a[5000050], nxt[1000010], head[1000010];
bool chosen[1000010];
int main()
{
	open("sam");
	in(n), in(k), in(p);
	for(int i = 1; i <= p; ++i)
	{
		in(a[i]);
		if(head[a[i]]) nxt[head[a[i]]] = i;
		head[a[i]] = i;
	}
	for(int i = 1; i <= p; ++i)
		if(!nxt[i]) nxt[i] = p + 1;
	int ans = 0;
	for(int i = 1; i <= p; ++i)
	{
		if(chosen[a[i]])
		{
			q.push((Toy)
			{
				a[i], nxt[i]
			});
			continue;
		}
		if(k)
		{
			q.push((Toy)
			{
				a[i], nxt[i]
			});
			chosen[a[i]] = 1;
			k--, ans++;
		}
		else
		{
			while(!chosen[q.top().num]) q.pop();
			chosen[q.top().num] = 0;
			q.pop();
			q.push((Toy)
			{
				a[i], nxt[i]
			});
			chosen[a[i]] = 1;
			ans++;
		}
	}
	print(ans);
	puts("");
	close;
	return 0;
}
```



---

## 作者：kakakaka (赞：5)

堆加贪心：

首先用邻接链保存后一个点的位置，保存在next里；

然后维护一个结构体大根堆，每次加入next和a[i]就可以了。

也就是说：每次找一个最远的删掉就可以了。（本人一开始就是贪心策略错了，哈哈）

注意一下细节：

邻接链要赋初值；大根堆中每一个数不一定有效，所以不能用size记录大根堆中的数。

一下是AC代码：

    
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int N=100001;
const int M=500001;
int a[M];
int n,k,m;
int nxt[M],last[N];
bool in[N];
int read()
{
    int k=0;
    char s=getchar();
    while(s<'0'||s>'9')s=getchar();
    while(s>='0'&&s<='9')k=k*10+s-'0',s=getchar();
    return k;
}
struct student
{
    int next,id;
}heap[M];
int size;
void insert(int nxt,int x)
{
    size++;
    int place=size,parent=size>>1;
    while(parent>=1&&heap[parent].next<nxt)
    {
        heap[place]=heap[parent];
        place=parent;
        parent>>=1;
    }
    heap[place].next=nxt;
    heap[place].id=x;
    return;
}
void delet()
{
    student x=heap[size--];
    int place=1,child=2;
    while(child<=size)
    {
        if(child<size&&heap[child].next<heap[child+1].next)child++;
        if(heap[child].next>x.next)
        {
            heap[place]=heap[child];
            place=child;
            child<<=1;
        }
        else break;
    }
    heap[place]=x;
    return;
}
int main()
{
    int i,j,ans=0;
    n=read();k=read();m=read();
    for(i=1;i<=m;i++)
        a[i]=read();
    for(i=1;i<=n;i++)last[i]=M+1;
    for(i=m;i>=1;i--)
    {
        nxt[i]=last[a[i]];
        last[a[i]]=i;
    }
    int cnt=0;
    for(i=1;i<=m;i++)
    {
        if(in[a[i]]){insert(nxt[i],a[i]);continue;}
        if(cnt<k)
        {
            ans++;
            cnt++;
            insert(nxt[i],a[i]);
            in[a[i]]=1;
        }
        else
        {
            while(in[heap[1].id]==0)delet();
            in[heap[1].id]=0;
            delet();
            ans++;
            in[a[i]]=1;
            insert(nxt[i],a[i]);
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Luo_Saisei (赞：4)

## 分析
把这个过程看成这样：

就是对于一个颜色的相邻两次出现位置，你可以对这个区间进行一次线段覆盖并且让答案减少一，并且要求每个整点的覆盖次数不超过给定的一个数，考虑到从左往右扫的时候不用关心当前区间的左端点，为了让后续区间被更少的线段覆盖，拿掉长度最长的线段是必定最优的。

## 细节

如果有个玩具已经在地上了，可以通过增加容积来实现一次懒更新。

## Code

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
#define int long long
#define fc freopen("in.in", "r", stdin), freopen("out.out", "w", stdout)
const int N = 1e6 + 10;
int a[N];
int cnt[N], pre[N];
int vis[N];
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, k, p;
    cin >> n >> k >> p;
    for (int i = 1; i <= p; i++)
        cin >> a[i];
    for (int i = p; i >= 1; i--)
    {
        if (!cnt[a[i]])
            pre[i] = 1e9;
        else
            pre[i] = cnt[a[i]];
        cnt[a[i]] = i;
    }
    priority_queue<pair<int, int>> pq;
    int ans = 0;
    for (int i = 1; i <= p; i++)
    {
        if (vis[a[i]])
        {
            k++;
            pq.push({pre[i], a[i]});
        }
        else
        {
            if (pq.size() == k)
            {
                vis[pq.top().second]--;
                pq.pop();
            }
            pq.push({pre[i], a[i]});
            vis[a[i]]++;
            ans++;
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：Vocanda (赞：4)

# 题目
[题目链接](https://www.luogu.com.cn/problem/SP688)

# 分析
这个题的主要思路就是贪心，具体思路楼下说的应该挺清楚了，这里再进行一番具体的分析（~~魔改~~）

### 思路
题意是我们要求出来最小的步数能让$Jasio$把所有想玩的玩完。那么我们就可以跟~~饿狼~~一样贪了。

考虑一下，假如说地上不足$k$个物品并且当前地上没有$Jasio$想要玩的玩具，那么肯定就直接取下来就行。

假如地上已经满足了$k$个东西了，那么这时候是需要放回一个物品，所以放回哪个物品就是这个题的关键。

因为地上的东西已经有$k$个了，而从当前向后可能还会有要玩某个玩具的需求，那么我们就可以找出当前地上所有东西之中，下一次玩最靠后的那个玩具拿走就行，而这个下一次玩最靠后的玩具可以用大根堆来进行维护，在前边反着枚举预处理。

因为大根堆（优先队列）无法进行单独的删除操作，每次只能把堆顶取出，但是如果之前入过队的，但是和当前需要入队的玩具是同种，那么直接取出是不行的，但是当前这个玩具的下一次玩肯定是比上一个要靠后，那么我们就可以把$k++$，让上一个这种玩具永远保留在里边，为了记录这个玩具出队，我们可以使用一个$vis$数组，每次堆中元素个数等于$k$了，就让堆顶元素的$vis$清空，然后弹出堆顶，然后统计答案并将当前要玩的东西加入队列即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;
const int maxm = 5e5+10;
int jl[maxm],a[maxm];
int vis[maxn],pos[maxn];
priority_queue<pair<int,int> >q;//按pair第一个元素大根堆排序
int main(){
	int n,k,p;
	scanf("%d%d%d",&n,&k,&p);
	for(int i=1;i<=p;++i){
		scanf("%d",&a[i]);
	}
	for(int i=p;i>=1;--i){//反着枚举
		if(!pos[a[i]])jl[i] = 0x3f3f3f3f;//后边不出现了就极大值，不影响
		else jl[i] = pos[a[i]];//记录下一次当前玩具出现的时候
		pos[a[i]] = i;//记录出现位置
	}
	int ans = 0;
	for(int i=1;i<=p;++i){
		if(vis[a[i]]){//如果之前取过但是没出队，就保留着
			k++;//保留了一个就让限制++
			q.push(make_pair(jl[i],a[i]));//入队
		}
		else{
			if(q.size() == k){//地上放不下了，就出队
				vis[q.top().second] = 0;//出队了说明没取，vis数组清除
				q.pop();
			}
			ans++;//答案++
			q.push(make_pair(jl[i],a[i]));//入队
			vis[a[i]] = 1;//记录当前玩具入队了
		}
	}
	printf("%d\n",ans);
}

```

---

## 作者：yzxoi (赞：3)

# 洛谷 P3419 [POI2005]SAM-Toy Cars题解
## 题目描述
Jasio 是一个三岁的小男孩,他最喜欢玩玩具了,他有n 个不同的玩具,它们都被放在了很高的架子上所以Jasio 拿不到它们. 为了让他的房间有足够的空间,在任何时刻地板上都不会有超过k 个玩具. Jasio 在地板上玩玩具. Jasio'的妈妈则在房间里陪他的儿子. 当Jasio 想玩地板上的其他玩具时,他会自己去拿,如果他想玩的玩具在架子上,他的妈妈则会帮他去拿,当她拿玩具的时候,顺便也会将一个地板上的玩具放上架子使得地板上有足够的空间. 他的妈妈很清楚自己的孩子所以他能够预料到Jasio 想玩些什么玩具. 所以她想尽量的使自己去架子上拿玩具的次数尽量的少,应该怎么安排放玩具的顺序呢?

## 输入输出格式
### 输入格式：
第一 行三 个整数:n,k,p(1≤k≤n≤100,000,1≤p≤500000), 分别表示玩具的总数,地板上玩具的最多个数以及 JasioJasio 他想玩玩具的序列的个数,接下来 pp 行每行描述一个玩具编号表示 Jasio 想玩的玩具。

### 输出格式：
一个数表示 JasioJasio 的妈妈最少要拿多少次玩具。

## 输入输出样例
### 输入样例#1： 
3 2 7
1
2
3
1
3
1
2
### 输出样例#1： 
4
### 思路
#### luogu一直AC不了的小朋友们看这里：
#### 不要提交SP688，提交P3419 [POI2005]SAM-Toy Cars
#### 不要提交SP688，提交P3419 [POI2005]SAM-Toy Cars
#### 不要提交SP688，提交P3419 [POI2005]SAM-Toy Cars
至于为什么，我也不知道。。。反正本人卡了3次提交在luogu上（手动滑稽）

>这道题使用贪心+堆优化。

贪心为：

每一次输入一个数将弹出一个大小为k的集合中的一个数才能使该数加入。

当然，如果该数早就在集合当中就可以直接切换到下一个数。

前k个数也可以直接进入集合中。

问题来了？到底弹集合中的哪一个数才能最优呢？

当然是下一次出现的距离最远的那一个数了。

堆优化：
```
priority_queue<int> q;
```
就是一个大根堆。

那么这道题需要将堆里的类型修改一下。
```
priority_queue<pair<int,int> >q;
```
pair的前一个储存节点的下一次出现位置，第二个储存该节点的值。

这样就可以自动的排序出距离最远的那一个数了。

所以每次操作只需要将q.top()取出，然后将头元素删除——q.pop()。

最后，上代码：
```
#include<algorithm>
#include<bitset>
#include<complex>
#include<deque>
#include<exception>
#include<fstream>
#include<functional>
#include<iomanip>
#include<ios>
#include<iosfwd>
#include<iostream>
#include<istream>
#include<iterator>
#include<limits>
#include<list>
#include<locale>
#include<map>
#include<memory>
#include<new>
#include<numeric>
#include<ostream>
#include<queue>
#include<set>
#include<sstream>
#include<stack>
#include<stdexcept>
#include<streambuf>
#include<string>
#include<typeinfo>
#include<utility>
#include<valarray>
#include<vector>
#include<cstring>
#include<cmath>
#define ll long long 
#define FHAKIOI int
using namespace std;//头文件结束
inline ll read(){
    ll ret=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9') {if (ch=='-') f=-f;ch=getchar();}
    while (ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
    return ret*f;
}//读优结束
inline void write(ll zx){
    if(zx<0){zx=-zx;putchar('-');}
    if(zx<10) putchar(zx+'0');
    else{
        write(zx/10);
        putchar(zx%10+'0');
    }
}//输优结束
ll n,k,p,a[500010];
ll use[100010];
ll f[500010];
ll las[500010],ans;
ll nxt[500010];
priority_queue<pair<int,int> > q;//堆
FHAKIOI main(){
    n=read();k=read();p=read();
    for(ll i=1;i<=p;i++) a[i]=read(),las[a[i]]=p+1;//读入
    for(ll i=p;i>=1;i--){
        nxt[i]=las[a[i]];
        las[a[i]]=i;
    }//先预处理与下一次出现的位置的距离
    for(int i=1;i<=p;i++){
        if(use[a[i]]!=0){
            q.push(make_pair(nxt[i],a[i]));//已经在集合里了
        }else if(k!=0){//前K个数
            k--;
            ans++;
            use[a[i]]=1;
            q.push(make_pair(nxt[i],a[i]));
        }else{//最后一种情况，需要弹出一个数
            while(!use[q.top().second]) q.pop();//目前没有在集合中
            int x=q.top().second;//取距离最远的
            q.pop();
            use[x]=0;
            ans++;//ans加一
            use[a[i]]=1;
            q.push(make_pair(nxt[i],a[i]));
        }
    }
    write(ans);putchar('\n');/输出
    return 0;
}
 ```

---

## 作者：hzoi_liuchang (赞：2)

## 分析
这是一道比较经典的贪心题目

我们要使取玩具的次数尽可能少，那么当地面上的空间足够大的时候，我们就直接把玩具放在地板上

如果地面上的空间不够，我们就将地面上的玩具里下一次最晚出现的放到架子上

因此，我们要维护一个优先队列，存储所有在地板上的玩具，按照出现顺序从晚到早排序

``` cpp
struct asd{
    int num,tim;
    asd(){}
    asd(int aa,int bb){
        num=aa,tim=bb;
    }
    bool operator < (const asd& A)const{
        return tim<A.tim;
    }
};
priority_queue<asd> q;
```
同时，我们还要用一个数组$nex$记录当前元素上一次出现的位置
这个东西我们倒序枚举处理就可以

要注意的是，因为优先队列的删除操作不好处理，所以我们想要从地板上拿出一个玩具，只需要把地板能容纳的玩具数加一就可以

因为要拿出玩具的最晚出现时间一定要早，不会对后面的产生影响
## 代码
``` cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int lat[maxn],nex[maxn],a[maxn];
bool vis[maxn];
struct asd{
    int num,tim;
    asd(){}
    asd(int aa,int bb){
        num=aa,tim=bb;
    }
    bool operator < (const asd& A)const{
        return tim<A.tim;
    }
};
priority_queue<asd> q;
int main(){
    int n,k,nn;
    scanf("%d%d%d",&n,&k,&nn);
    for(int i=1;i<=nn;i++){  
        scanf("%d",&a[i]);
    }
    for(int i=nn;i>=1;i--){
        if(lat[a[i]]==0) nex[i]=0x3f3f3f3f;
        else nex[i]=lat[a[i]];
        lat[a[i]]=i;
    }
    int ans=0;
    for(int i=1;i<=nn;i++){
        if(vis[a[i]]==1){
            k++;
            q.push(asd(a[i],nex[i]));
        } else if(q.size()<k){
            vis[a[i]]=1;
            q.push(asd(a[i],nex[i]));
            ans++;
        } else {
            int now=q.top().num;
            vis[now]=0;
            q.pop();
            vis[a[i]]=1;
            q.push(asd(a[i],nex[i]));
            ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：stdlifg (赞：2)

# [POI2005]SAM-Toy Cars

## 我的做法：删除堆

## 思路：

贪心策略：每次将**下一次**玩的时间**最晚**的玩具放回去即可。因为在**这一次**到**下一次**的过程中，它都在占地板上的名额，没有对答案做贡献，把**占名额最长**的玩具先拿掉显然最优。

## 实现

可删除堆适用于思维简单粗暴的人。

当然我们要按**下一次玩的时间为关键字**建堆

每次拿**下一次玩的时间最晚的**换当前的玩具

但是呢，堆是不支持更新的

当我们发现我们要的玩具已经在地上了

我们没有办法更新这个玩具的**下一次玩的时间**

而此时又必须要更新

所以我们建立一个删除堆

当我们发现我们要的玩具已经在地上时

删除以**这一次玩的时间为关键字**的节点

加入以**下一次玩的时间为关键字**的节点

就行了

还有注意我使用list求的关键字时间。

```cpp
#include <bits/stdc++.h>

#define pb push_back
#define pf pop_front
#define mk make_pair
#define RG register
#define il inline

using namespace std;

il int gi() {
	int x=0,o=0;char ch=getchar();
	while(ch!='-'&&(ch<'0'||'9'<ch)) ch=getchar();
	if(ch=='-') o=1,ch=getchar();
	while('0'<=ch&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return o?-x:x;
}

#define N 100010
#define M 500010
const int inf=2147483647;

int n,k,p,ans,b[M];
list <int> a[N];
bool inq[N];

#define pir pair<int,int>
#define fir first
#define sec second
struct Heap {
	priority_queue <pir> hp,dl;
	void Push(int num) { a[num].pf(); hp.push(mk(a[num].front(),num));}
	void Del(int num) { dl.push(mk(a[num].front(),num)); }
	void Upd() { while(!dl.empty()&&dl.top()==hp.top()) dl.pop(),hp.pop(); }
	void Pop() { Upd(),hp.pop(); }
	int Top() { Upd(); return hp.top().sec; }
}Q;

int main() {
	n=gi(),k=gi(),p=gi();
	for(int i=1; i<=p; ++i) b[i]=gi(),a[b[i]].pb(i);
	for(int i=1; i<=n; ++i) a[i].pb(inf);
	for(int tmp,i=1; i<=p; ++i) {
		if(inq[b[i]]) { Q.Del(b[i]),Q.Push(b[i]); continue; }
		++ans;
		if(k) { Q.Push(b[i]),inq[b[i]]=1,--k; }
		else {
			tmp=Q.Top();
			Q.Pop(),inq[tmp]=0;
			Q.Push(b[i]),inq[b[i]]=1;
		}
	}
	printf("%d",ans);
	return 0;	
}
```

---

## 作者：AC_Automation (赞：1)

### 贪心+线段树
---
另一篇用线段树的题解码风自认为有点奇怪，就写一篇（自认为）码风正常一点的

提供一道弱化版[P2088 果汁店的难题](https://www.luogu.com.cn/problem/P2088)题目基本一样，范围小了很多

思路比较简单，就是每次需要将玩具放回架子上时，优先放离下次使用最远的玩具

那么我们先预处理出一个next数组（代码中为nxt），来保存对于每个玩具，下一次使用同样的玩具是什么时候

那么线段树用来维护什么呢？我们用线段树来维护每种玩具下一次使用是什么时候。当然，如果这种玩具不在地上，就不加入线段树的维护（因为我们需要用线段树来维护最大值，所以将这种玩具下一次使用的时间设为0）

这样的话，我们每次要将一个新的玩具放到地上时，就要用线段树来查询离下次使用时间最远的一个玩具，然后放回架子上了！

最后就是代码了，细节还是有一点的，需要注意一下
```
#include<iostream>
using namespace std;
int nxt[500005],book[500005],a[500005];//book数组辅助处理nxt数组，a为初始数组
bool bj[500005];//bj数组记录玩具是否在地上
int maxx[400005],wz[400005];//线段树数组
void up(int root){
	if((maxx[root<<1])>(maxx[root<<1|1])){
		maxx[root]=maxx[root<<1];
		wz[root]=wz[root<<1];
	}
	else{
		maxx[root]=maxx[root<<1|1];
		wz[root]=wz[root<<1|1];
	}
}
void change(int root,int l,int r,int k,int temp){
	if(l==r){maxx[root]=temp;wz[root]=l;return;}
	int mid=(l+r)>>1;
	if(k<=mid)change(root<<1,l,mid,k,temp);
	else change(root<<1|1,mid+1,r,k,temp);
	up(root);
}
//----以上是线段树板子
int main(){
	int k,q,n,st=0,sum=0;//sum是答案，st记录地上的玩具数目
	cin>>k>>q>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		nxt[book[a[i]]]=i;
		book[a[i]]=i;
	}//处理nxt数组，用book数组记录当种玩具最靠后的位置
	for(int i=1;i<=n;i++)if(nxt[i]==0)nxt[i]=999999999;//如果是同种玩具最后一个，nxt设为inf
	for(int i=1;i<=n;i++){
		if(bj[a[i]]){
			change(1,1,k,a[i],nxt[i]);
			continue;
		}//玩具在地上就直接在线段树上改，然后直接过
		if(st<q){
			st++;
			change(1,1,k,a[i],nxt[i]);
			bj[a[i]]=1;
			sum++;
			continue;
		}//玩具还没放满时直接放，线段树上改
		int x=wz[1];//找到最远的玩具
		change(1,1,k,x,0);//放回架子
		change(1,1,k,a[i],nxt[i]);//当前的拿回地上
		bj[x]=0;
		bj[a[i]]=1;
		sum++;//统计答案
	}
	cout<<sum;
	return 0;
}

```

---

## 作者：like1 (赞：1)

我们看完问题可以发现，题目要我们求拿玩具的次数尽量的少,应该怎么安排放玩具的顺序；像这样求...最小（少）或是求...最大（多），这类问题大多数可以采用贪心；

那么我们该怎么贪呢？

很明显我们把当前放在地上但下次需要的时间最晚的放回柜子里是最优的，于是我们可以先处理出每个玩具下一次需要它是什么时候
```
for(int i=m;i>=1;i--)
{//倒序枚举m个玩具，P记录该玩具上次出现的位置，再次出现时赋给S 
	if(p[a[i]]==0) s[i]=1e8;
   else s[i]=p[a[i]];
   p[a[i]]=i;
   //cout<<i<<":"<<" "<<s[i]<<" "<<p[a[i]]<<endl;
}
```


对于如何维护最大值，我们可以想到用优先队列，
priority_queue<pair<int,int> > q; pair的前一个储存节点的下一次出现位置，第二个储存该节点的值。
```
for(int i=1;i<=m;++i)
{
   if(v[a[i]]) 
	{
		k++;					//已经在队列中,直接加入即可，因为加入了两个一样的，所以等价于k+1 
		q.push(make_pair(s[i],a[i]));    //pair的前一个储存节点的下一次出现位置，第二个储存该节点的值。
   } 
	else                                         
	{
      if(q.size( )==k) 
		{
			v[q.top( ).second]=0;
			q.pop( );          //若队列已满，取出下次出现最晚的，即队头 
		}
      q.push(make_pair(s[i],a[i])),v[a[i]]=1;
      ans++;
   }
}
```


    
再放上完整的代码
```
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

const int N=5e5+5,M=1e5+5;
int n,k,m,ans;
int a[N],s[N];
int v[M],p[M];
priority_queue<pair<int,int> > q;

int main( )
{
	//freopen("toy.in","r",stdin);
	//freopen("toy.out","w",stdout);
    scanf("%d%d%d",&n,&k,&m);
    for(int i=1;i<=m;i++) scanf("%d",&a[i]);
    for(int i=m;i>=1;i--)
	{
        if(p[a[i]]==0) s[i]=1e8;
        else s[i]=p[a[i]];
        p[a[i]]=i;
        //cout<<i<<":"<<" "<<s[i]<<" "<<p[a[i]]<<endl;
    }
    for(int i=1;i<=m;++i)
	{
    	if(v[a[i]]) 
		{
			k++;					
			q.push(make_pair(s[i],a[i]));    
        } 
		else                                         
		{
            if(q.size( )==k) 
			{
				v[q.top( ).second]=0;
				q.pop( );          
			}
            q.push(make_pair(s[i],a[i])),v[a[i]]=1;
            ans++;
        }
    }
    printf("%d\n",ans);
}
```


最后祝大家CSP2019rp++,score++;

---

## 作者：fdfdf (赞：1)

提供一种线段树的思路。

~~似乎最近一段时间本人的思路都比较奇怪~~

考虑一个玩具需要使用的时候不用从柜子上拿意味着什么。

由于前一次使用这个玩具的时候这个玩具一定会被拿下来，那么从前一次使用这个玩具开始这个玩具都要保留在地上。

具体来说，设$pre_i$为需要使用的第$i$个玩具之前需要使用的前一个位置，那么我们需要保证$[pre_i,i)$之内都要有玩具$p_i$。

那么我们就把这个问题转换乘了一个区间覆盖问题:

有$p$个区间$[pre_i,i)$，每个点不能被覆盖超过$k-1$次，求能放下的最多的区间数

直接按照右端点排序贪心即可，检查是否能覆盖的时候使用线段树。

```cpp
#include<bits/stdc++.h>
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<cstring>
#include<complex>
#include<vector>
#include<cstdio>
#include<string>
#include<bitset>
#include<ctime>
#include<cmath>
#include<queue>
#include<stack>
#include<map>
#include<set>
#define F "a"
#define mp make_pair
#define pb push_back
#define RG register
#define il inline
using namespace std;
typedef unsigned long long ull;
typedef pair<int,int> PI;
typedef vector<int>VI;
typedef long long ll;
typedef double dd;
const int N=5e5+10;
const int M=3e5+10;
const int K=3e5+10;
const int mod=998244353;
const int inf=2147483647;
const ll INF=1ll<<60;
const dd eps=1e-7;
const dd pi=acos(-1);
il ll read(){
  RG ll data=0,w=1;RG char ch=getchar();
  while(ch!='-'&&(ch<'0'||ch>'9'))ch=getchar();
  if(ch=='-')w=-1,ch=getchar();
  while(ch<='9'&&ch>='0')data=data*10+ch-48,ch=getchar();
  return data*w;
}

il void file(){
  freopen(F".in","r",stdin);
  freopen(F".out","w",stdout);
}

int n,m,k,p,a[N],t[N],pre[N],mx[N<<2],lz[N<<2];
#define ls (i<<1)
#define rs (i<<1|1)
#define mid ((l+r)>>1)
il void update(int i){mx[i]=max(mx[ls],mx[rs]);}
il void cover(int i,int v){mx[i]+=v;lz[i]+=v;}
il void pushdown(int i){if(lz[i]){cover(ls,lz[i]);cover(rs,lz[i]);lz[i]=0;}}
void modify(int i,int l,int r,int x,int y){
  if(x<=l&&r<=y){cover(i,1);return;}
  pushdown(i);
  if(x<=mid)modify(ls,l,mid,x,y);
  if(mid<y)modify(rs,mid+1,r,x,y);
  update(i);
}
int query(int i,int l,int r,int x,int y){
  if(x<=l&&r<=y)return mx[i];pushdown(i);int s=0;
  if(x<=mid)s=query(ls,l,mid,x,y);
  if(mid<y)s=max(s,query(rs,mid+1,r,x,y));
  return s;
}

int main()
{
  RG int T=read();
  while(T--){
    memset(t,0,sizeof(t));
    memset(mx,0,sizeof(mx));
    memset(lz,0,sizeof(lz));
    n=read();k=read();p=read();
    for(RG int i=1;i<=p;i++){a[i]=read();if(a[i]==a[i-1])i--,p--;}
    for(RG int i=1;i<=p;i++)pre[i]=t[a[i]],t[a[i]]=i;
    for(RG int i=1;i<=p;i++)
      if(pre[i]&&query(1,1,p,pre[i]+1,i-1)<k-1){
	m++;modify(1,1,p,pre[i]+1,i-1);
      }
    printf("%d\n",p-m);
  }
  return 0;
}

```

---

## 作者：WNico (赞：1)

> 我要用各种 $STL$ 切掉这道题

思路 ： 模拟+贪心(每次选下一次想玩的时间最后的玩具出队)

实现 ： ~~树套树~~ set维护在地上的玩具的下一次想被玩的时间的最大值

这里只放了TLE的程序

~~明明unordered_map复杂度是O(1)了怎么还不让我过~~

想过照着注释改一改就行，实现方法看注释

记得交 C++11（或以上

```cpp
#include<bits/stdc++.h>				// Luogu + O2 90pts 需要一点卡常
using namespace std;

inline int read(){
    int s=0,w=1;char ch;
    while(ch=getchar(),!isdigit(ch)&&ch!=EOF) if(ch=='-') w=-1;
    while(isdigit(ch)&&ch!=EOF) s=s*10+ch-'0',ch=getchar();
    return ch==EOF?-1:s*w;
}
										// 要卡常可以:
unordered_map<int,set<int> > toy;		// 换成数组
set<pair<int,int> > nxt; // 维护最大值
unordered_set<int> onf;					// 换成bool数组
list<int> str;							// 随便换不换
int n,k,p,ans,vol,l;

template<class T1,class T2>				// 或许可以换成
pair<T1,T2> mp(T1 a,T2 b){				// #define mp(x,y) make_pair(x,y)
    return pair<T1,T2>(a,b);
}

int main(){
    //freopen("in.txt","r",stdin); 
    n=read();k=read();p=read();
    for(int i=1,inp;i<=p;++i){
        inp=read();
        str.push_back(inp);			// 储存玩具的序列
        toy[inp].insert(i);			// 储存该数的入队时间
    }
    for(auto i=toy.begin();i!=toy.end();++i){ // 塞到前面去会更快
        i->second.insert(p+1);		// 为每个数添加下界
    }
    for(auto x : str){				// c++11 就是爽
        l++;
        if(onf.find(x)==onf.end()){
            ans++;					// 如果地板上没有，答案++
            if(vol==k){
                auto del = *(--nxt.end());	// 找到下一次入队最晚的元素
                nxt.erase(--nxt.end());
                onf.erase(del.second);		// 删除出队玩具
                auto add = *(toy[x].upper_bound(l));	// 找到目前元素的下一次入队时间
                onf.insert(x);
                nxt.insert(mp(add,x));		// 添加要玩的玩具的下一次入队时间
            }else{
                vol++;				// 如果地板没满直接加入
                onf.insert(x);
                nxt.insert(mp(*(toy[x].upper_bound(l)),x));
            }
        }else{						
            auto del = *nxt.begin();
            nxt.erase(nxt.begin());		// 删除目前元素
            nxt.insert(mp(*toy[x].upper_bound(del.first),x));	// 添加目前的元素的下一次入队时间
        }
    }
    cout<<ans<<endl;

    return 0;
}
```

--- 

$$\ fin$$

---

