# SAM - Toy Cars

## 题目描述

Jasio 是一个只有三岁的小男孩，他喜欢玩玩具车。他有 $n$ 辆玩具车被保存在书架上。

架子上的玩具车 Jasio 拿不到，但地板上的他可以拿到。Jasio 的母亲会帮 Jasio 拿架子上的玩具车到地板上。

地板最多只能放 $k$ 辆玩具车。

当地板已经放了 $k$ 辆玩具车时，Jasio 的母亲都会从地板上先拿走一个玩具车放回书架，再拿来 Jasio 想要的玩具车。

现在 Jasio 一共想依次玩 $p$ 个玩具车，问 Jasio 的母亲最少需要拿几次玩具车。（只算拿下来的，不算拿上去的）

## 说明/提示

对于 $100\%$ 的数据：$1\le t\le 16$，$1\le k\le n\le 10^5$，$1\le p\le 5\times 10^5$，$1\le a_i\le n$。

感谢 @Utilokasteinn 提供的翻译。

## 样例 #1

### 输入

```
1
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

## 作者：trickedout (赞：5)

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

## 作者：genshy (赞：4)

# 一道很妙的贪心题

我们考虑当我们插入时会面临的两种情况

1. 当地上的玩具，不满 $k$ 个时，那我们直接放就可以了。

1. 当满了 $k$ 个的时候，我们就要从地上拿出一个来给当前的腾位置。

   这就需要我们替换一个，根据我们贪心的思想，当一种玩具出现的比较晚
    
   的时候，那么我们就可以把它拿走，因为他后面用的次数比较少，这样妈妈
   
   的移动次数就会少很多 。
   
那么，我们就有了处理这道题的思路，先求出每个点，他下一次要玩的时间

为 $net_i$ 用堆来维护地板上玩具 $net_i$ 的最大值，来维护上述过程。

### 坑点

1. 多测数据一定要清空，最后不要忘记把堆清空

1. 如果当前这个玩具后面都不会在玩它，我们应该把他的 $net_i$ 
   数组设为一个极大值，而不是0
   
1. 如果当前这个点已经在地板上，我们依旧要把它入队，来代替之前的那个玩具。（我在这里卡了好长时间）

### Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
int t,n,k,p,ans,a[500010],last[500010],net[500010];
bool used[100010];
inline int read()
{
	int s = 0,w = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') w = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){s =s * 10+ch - '0'; ch = getchar();}
	return s * w;
}
priority_queue<pair<int,int> >q;
int main()
{
	t = read();
	while(t--)
	{
		memset(last,0,sizeof(last)); memset(used,0,sizeof(used)); //多组数据一定要清空
		n = read(); k = read(); p = read(); ans = 0;
		for(int i = 1; i <= p; i++) a[i] = read();
		for(int i = p; i >= 1; i--)
		{
			if(last[a[i]] == 0) net[i] = 2333333;//如果后面不会在玩这个玩具，我们要把他的 net[i] 数组设为极大值
			else net[i] = last[a[i]];
			last[a[i]] = i;
		}
		for(int i = 1; i <= p; i++)
		{
			if(used[a[i]])
			{
				k++;//如果这种玩具已经在地板上，我们要把他入队来替代之前不优的
				q.push(make_pair(net[i],i));
			}
			else
			{
				if(q.size() < k)//Case1
				{
					q.push(make_pair(net[i],i));
					used[a[i]] = 1; ans++;
				}
				else//Case2
				{
					int t = q.top().second; q.pop();
					used[a[t]] = 0; used[a[i]] = 1; ans++;
					q.push(make_pair(net[i],i));
				}
			}
		}
		printf("%d\n",ans);
		while(!q.empty()) q.pop();//最后记得把堆清空
	}
	return 0;
}
```

另外，此题还有[双倍经验](https://www.luogu.com.cn/problem/P3419) QAQ。





---

## 作者：1234567890sjx (赞：1)

这个题还是比较简单的贪心。

对于每一辆玩具车：

+ 如果这辆玩具车已经被拿下来了，那么肯定直接用。
+ 如果这辆玩具车没有被拿下来，则分类讨论：
  + 如果当前地板上放的玩具车不超过 $k$ 辆（还能接着放），那么直接放。
  + 否则，贪心的选取地板上的玩具车中下一次使用时间最晚的那一辆，把她拿上去，换下来这辆玩具车即可。

为了快速的实现上面的第三个操作，用一个堆来维护当前地板上的玩具车的信息，每一次选择堆头元素即可。

对于单组数据，时间复杂度 $O(n\log n)$。

不知道算不算反悔贪心。

---

## 作者：hzoi_liuchang (赞：1)

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

## 作者：D_14134 (赞：1)

题意：有n件玩具p次操作，每次将pi加入大小为k的集合中，若以存在则无视，大小超过k就需要弹出，问最少加入几次。

可以先感性理解到这是贪心，那么如何证明呢?

我们假设现在有一个大小为5的集合，已经装满了玩具
并知道他们下一次出现的时间
```
编号	       1,2,3,4,5
下一次出现时间  7,6,8,9,11

```
现在在第5个时间节点加入玩具6，于是我们需要弹出集合k中的一个元素。

假如剔除1号，我们将需要在第6个时间节点中在假如1号。即剔除1号能带来的空当时间为5-7；而假如剔除5号，空当时间为5-11。

显然空当时间越长我们的操作次数接越小；证明：假如剔除元素i那么我们在next[i]再加入后有可能在next[i]+1的时候再将它剔除，所以nxt[i]越靠后可能的操作次数一定越少。

于是我们先处理处对于每一位每一个元素的下一次出现时间，每一次在集合k中剔除下一次出现时间最完的元素就好了。

先用队列维护出每一位的next，再用优先队列贪心。

特别的，如果该元素是最后一次出现，那么他的next应该直接赋为inf。

### code
```cpp
#include<queue> 
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define maxn 100010
using namespace std;

struct no{
	int id,nx;
	bool operator <(const no &x) const{
		return nx<x.nx;
	}
};

int n,k,p,ans,a[maxn*5],nxt[maxn*5],ins[maxn];
queue<int> s[maxn];
priority_queue<no> q;

int main(){
	int T;scanf("%d",&T);
	while(T--){
		ans=0;
		while(!q.empty()) q.pop();
		memset(ins,0,sizeof(ins));
		memset(nxt,0,sizeof(nxt));
		scanf("%d%d%d",&n,&k,&p);
		for(int i=1;i<=p;i++){
			scanf("%d",&a[i]);
			s[a[i]].push(i);
		}
		for(int i=1;i<=p;i++){
			s[a[i]].pop();
			if(s[a[i]].empty()) nxt[i]=p+1;
			else nxt[i]=s[a[i]].front();
		}
		for(int i=1;i<=p;i++){
			if(ins[a[i]]) q.push((no){i,nxt[i]}),k++;
			else{
				if(q.size()==k){
					ins[a[q.top().id]]=0;
					q.pop();
				}
				q.push((no){i,nxt[i]});
				ins[a[i]]=1;
				ans++;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：rechenz (赞：0)

#### 双倍经验[P3419](https://www.luogu.com.cn/problem/P3419)

其实我第一眼看到这道题的时候以为是一道 $\texttt {DP}$，但是想了想就发现要记录的状态实在太多，于是就去想贪心。

考虑每次拿玩具对总体的贡献，因为能同时放在地上的玩具个数有限，而我们又只计算拿玩具下来的次数，于是便可得出一个贪心结论，那便是对于把玩具放回去这个行为，下一次玩这个玩具的时间距离现在越远一定越优，因为我们不能不玩任何一个玩具。

所以我们在把玩的顺序读入后，倒序枚举预处理出这个玩具下一次玩的时间，那么至于如何选择，只需要用一个优先队列维护即可，因为要存两维，一个是用来排序的 $\texttt {next}$ 数组，一个是这个玩具的 $\texttt{id}$，所以我们用优先队列存一个 $\texttt{pair}$ 类即可。

复杂度为跑不满的 $\rm O(nlogn)$。

另外温馨提示，多测不清空，爆零两行泪。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=500005;
int n,k,p,a[N],nex[N],temp[N],ans,vis[N],tot;

priority_queue<int,vector<pair<int,int>>>q;
//也可以这样写
// priority_queue<pair<int,int>>q;
void init(){//预处理函数
    while(!q.empty()){
        q.pop();
    }
    memset(temp,0,sizeof temp);
    memset(nex,0,sizeof nex);
    memset(vis,0,sizeof vis);
    ans=0;
}

int main(){
    int T;
    scanf("%d",&T);
    for(int l=1;l<=T;l++){
        scanf("%d%d%d",&n,&k,&p);
        for(int i=1;i<=p;i++){
            scanf("%d",&a[i]);
        }
        for(int i=p;i>=1;i--){//预处理出nex数组
            if(temp[a[i]]==0) nex[i]=1e6;
            else nex[i]=temp[a[i]];
            temp[a[i]]=i;
        }
        for(int i=1;i<=p;i++){
            if(!vis[a[i]]){
                if(q.size()==k){
                    vis[q.top().second]=0;
                    q.pop();
                }
                q.push(make_pair(nex[i],a[i]));
                ans++;
                vis[a[i]]=1;
            }else{//因为有新的进入队列更新，而优先队列不好维护弹出，所以把范围开大一个，防止错误弹出
                k++;
                q.push(make_pair(nex[i],a[i]));
            }
        }
        printf("%d\n",ans);
        init();
    }
    return 0;
}
```


---

## 作者：Vocanda (赞：0)

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
	int T;
	cin>>T;
	while(T--){
		memset(jl,0,sizeof(jl));
		memset(a,0,sizeof(a));
		memset(vis,0,sizeof(vis));
		memset(pos,0,sizeof(pos));
		while(!q.empty()){
			q.pop();
		}
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
}

```

---

## 作者：like1 (赞：0)

这题其实和P3419是一模一样的题，为什么P3419是蓝题，而此题是紫题？难道是因为题库不同？（雾）

好了，言归正传；

这题其实就是一道贪心的题目；我们看完问题可以发现，题目要我们求拿玩具的次数尽量的少,应该怎么安排放玩具的顺序；像这样求...最小（少）或是求...最大（多），这类问题大多数可以采用贪心；

那么我们该怎么贪呢？

很明显我们把当前放在地上但下次需要的时间最晚的放回柜子里是最优的，于是我们可以先处理出每个玩具下一次需要它是什么时候

```
 for(int i=m;i>=1;i--)
{//倒序枚举m个玩具，P记录该玩具上次出现的位置，再次出现时赋给S 
    if(p[a[i]]==0) s[i]=1e6;
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
    //倒序枚举m个玩具，P记录该玩具上次出现的位置，再次出现时赋给S 
    for(int i=m;i>=1;i--)
	{
        if(p[a[i]]==0) s[i]=1e6;
        else s[i]=p[a[i]];
        p[a[i]]=i;
        //cout<<i<<":"<<" "<<s[i]<<" "<<p[a[i]]<<endl;
    }
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
    printf("%d\n",ans);
}

```
最后祝大家CSP2019rp++,score++;

---

## 作者：破忆 (赞：0)

### 【题目大意】

有n种玩具，地上每次最多摆k个

如果地上没有就要拿

给定需要的玩具序列，求最下拿取次数
### 【分析】

如果地上不足k个玩具

直接拿即可

否则，每次拿玩具都要选择一个地上的玩具替换

假设将要替换地上的玩具i或玩具j

玩具i与玩具j可能在之后还需要再次拿下

如果玩具i下一次离得很近，而玩具j离得很远

选择替换玩具j就可以尽量避免再次拿取玩具i

从而使答案减小

所以，每次选择下一次出现最靠后的玩具

最终答案最优

### 【具体实现】

求每个玩具下一次出现的位置

可以从后往前记录每种玩具上一次出现的位置

从地上挑下一次出现的位置最靠后的玩具

可以用单调序列/堆/集合

### 【代码】
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5,maxm=5e5+5;
int n,m,k,cnt,len,ans;
int a[maxm],nxt[maxm],id[maxn];
bool vis[maxn];
struct why{
	int x,nxt;
	bool operator <(why b)const{return nxt>b.nxt;}
}hep[maxm];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
void put(int x,int y){
	hep[++len]=(why){x,y};
	int son=len;
	while(son>1&&hep[son]<hep[son>>1]){
		swap(hep[son],hep[son>>1]);
		son>>=1;
	}
}
int get(){
	int ret=hep[1].x;
	hep[1]=hep[len--];
	int fa=1,son;
	while((fa<<1)<=len){
		if((fa<<1|1)>len||hep[fa<<1]<hep[fa<<1|1]) son=fa<<1;else son=fa<<1|1;
		if(hep[son]<hep[fa]) swap(hep[fa],hep[son]),fa=son;else break;
	}
	return ret;
}
int main(){
// 	freopen("sam.in","r",stdin);
// 	freopen("sam.out","w",stdout);
    int t=read();
    while(t--){
    	memset(id,0,sizeof id);
    	memset(vis,0,sizeof vis);
    	len=ans=cnt=0; //变量记得清空
        n=read(),k=read(),m=read();
    	for(int i=1;i<=m;i++) a[i]=read();
    	for(int i=m;i;i--){
	    	if(!id[a[i]]) nxt[i]=m+1,id[a[i]]=i; // 坑点：不要把m写成n
    		else nxt[i]=id[a[i]],id[a[i]]=i;
    	}
    	for(int i=1;i<=m;i++){
	    	if(vis[a[i]]){put(a[i],nxt[i]); continue;}//地上有，不用管
	    	if(cnt<k){//地上空，直接拿
	    		put(a[i],nxt[i]);
	    		vis[a[i]]=1;
	    		ans++;
	    		cnt++;
	    		continue;
	    	}
	    	int x=get();//地上满了，找一个换
	    	vis[a[i]]=1;
	    	vis[x]=0;
	    	put(a[i],nxt[i]);
	    	ans++;
	    }
    	printf("%d\n",ans);
    }
	
	return 0;
}
```


---

