# [USACO16FEB] Circular Barn S

## 题目背景

*本题与 [金组同名题目](/problem/P6170) 在题意上一致，唯一的差别是数据范围。*

## 题目描述

作为当代建筑的爱好者，Farmer John 建造了一个圆形新谷仓，谷仓内部 $n$ 个房间排成环形（$3 \leq n \leq 1000$），按顺时针顺序编号为 $1\ldots n$，每个房间都有通往与其相邻的左右房间的门，还有一扇门通往外面。

现在 FJ 有 $n$ 头奶牛，他的目标是让每个房间恰好有一头奶牛。然而不幸的是，现在奶牛们随意呆在某个房间里，第 $i$ 个房间里有 $c_i$ 头奶牛。保证 $\sum c_i =n$。

FJ 决定采用这样的方法来解决这个问题：让某些奶牛**顺时针**穿过某些房间到达指定的位置。如果一头奶牛穿过了 $d$ 扇门，他消耗的能量为 $d^2$。你需要帮 FJ 算出所有奶牛消耗的能量和最小值是多少。

## 样例 #1

### 输入

```
10
1
0
0
2
0
0
1
2
2
2```

### 输出

```
33```

# 题解

## 作者：Zelotz (赞：19)

[题目链接](https://www.luogu.com.cn/problem/P3137)

本蒟蒻的第一篇题解，写得不好请指出，蟹蟹。

### 题意：
有 $n$ 头奶牛，分布在一些房间，某些房间可能有多头牛，要让这些牛按顺时针移动，求使每一个房间刚好有一个奶牛的最小花费。

花费计算：如果一头奶牛穿过了 $d$ 扇门，他消耗的能量为 $d^2$。

### 分析：
先把这个环看成一条链

首先说一个东西：如果有 $1$ 头奶牛在 $a$ 点，$1$头奶牛在 $b$ 点，还有一个没有奶牛的 $c$ 点，且 $c>b>a$，要想有一头奶牛在 $b$ 点，一头奶牛在 $c$ 点，方案 $a \to b,b \to c$ 比方案 $a \to c$ 好。

很容易知道这是对的，可以设 $x=b-a,y=c-b$，而 $c-a=y+x$，所以 $(x+y)^2=x^2+y^2+2xy>x^2+y^2$。

也就是说在如果一个房间的奶牛的移动算一个移动过程，移动过程中一头奶牛不要越过另一头没有移动的奶牛。

所以可以直接从一个起点开始，如果这个房间里有超过$1$头奶牛，就把这些奶牛移到依次后面每一个的房间的末尾，直到没有多余的奶牛可以移动为止。

留下房间里最后一头奶牛，也就是上一次最后一头牛，每一个房间都这么处理。

为了好写代码，可以留下最后一头牛，把这个房间里多余的奶牛移动到下一个房间，下一个房间再做处理。

问题是起点如何选择。

当一个起点是合法时，$\sum\limits_{i=1}^{n}c_{i} \geqslant i$。

不知道就枚举呗，反正 $n$ 不超过 $1000$。

窝语文不好，只能描述成这样惹。

### 代码：
为每一个奶牛编号，为 $1 \sim n$。

用 $d_i$ 来表示编号为 $i$ 的奶牛走过的距离。

用 $\texttt{vector}$ 来存每一个房间里的奶牛。

$\texttt{push\_back}$ 把元素 $\texttt{push}$ 到末尾，所以留下最后一个，其他的往下一个房间移动。

然后注意下一个房间 $\bmod n$ 就行了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define reg register int
#define msz(a) memset(a, 0, sizeof a);
#define rep1(i, j, n) for (reg i = j; i <= n; ++i)
#define rep2(i, j, n) for (reg i = j; i >= n; --i)
typedef long long LL;
typedef pair <int, int> PII;
const int INF1 = 0x3f3f3f3f, INF2 = 0x7fffffff;
int n, d[1005], ans, nowid, result = INF2;
vector <int> a[1005], b[1005];
bool vis[1005];
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        for (int j = 1; j <= x; ++j) a[i].push_back(++nowid), b[i].push_back(nowid); //编号
    }
    for (int start = 1; start <= n; ++start) {
    	// 枚举起点进行模拟
        for (int now = start; ; ++now) {
            if (now > n) now %= n;
            if (now == start && flg == 0) break;
            if (a[now].empty()) continue;
            flg = 0;
            int sz = a[now].size();
            int p = now + 1;
            if (p > n) p %= n;
            for (int i = 0; i < sz - 1; ++i) {
                a[p].push_back(a[now][i]);
                d[a[now][i]]++;
            }
            int endnum = a[now][sz - 1];
            a[now].clear();
            a[now].push_back(endnum);
        }
        for (int i = 1; i <= n; ++i) {
            if (a[i].size() != 1) { ans = -1; break; } //是否合法
            ans += d[i] * d[i]; //计算
        }
        if (ans ^ -1) result = min(result, ans);
        msz(d); msz(vis); ans = 0;
        for (int i = 1; i <= n; ++i) a[i].clear();
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j < (int)b[i].size(); ++j)
                a[i].push_back(b[i][j]); //还原
    }
    printf("%d", result);
    return 0;
}
```

 $n^2$ 算法可以通过 $1000$ 的数据，那么 $100000$ 的数据怎么办呢。

可以发现枚举 $start$ 会出现许多没用的枚举，那哪个一个 $start$ 可以确保不会出现非法情况呢。

可以大概猜出是最密集的那个地方的开头吧。

就是说最大字段和。

因为全部奶牛的和为 $n$，所以所有 $c_i$ 的和一定是最大子段和
所以要把每一个 $c_i$ 与 $1$ 做差，可以清晰看出最大的字段，再求出最大子段和的起点。

证明也很简单：

设最大子段和的值为 $x$，如果最大子段和不合法，那么在最大子段和之后必然有一个字段的值 $\leqslant -x-1$，由于所有数的和为 $0$，那么在这个字段之后，剩下的那个字段和 $\geqslant 1$。

所以最大子段和的值不为 $x$，矛盾。

这个证明有点。。充分显示出我的菜。

然后就是环状最大子段和惹。

环状最大子段和好像可以用单调队列，但是我用了另一种方法。

分两种情况讨论：

$1$.这个字段没有包含 $c_1$和 $c_n$，那么就是本来的最大子段和。

$2$.字段包含了 $c_1$和 $c_n$，那就是整个和减去全部的最小字段和。

最小字段和可以把所有元素取反，求最大子段和。

把两种情况取最大值即为答。

这样可以通过加强版的数据了。

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long //不开longlong见祖宗
#define mp make_pair
#define reg register int
#define msz(a) memset(a, 0, sizeof a);
#define rep1(i, j, n) for (reg i = j; i <= n; ++i)
#define rep2(i, j, n) for (reg i = j; i >= n; --i)
typedef long long LL;
typedef pair <int, int> PII;
const int INF1 = 0x3f3f3f3f, INF2 = 0x7fffffff;
const int N = 1e5 + 5;
int n, d[N], ans, nowid, result = INF2, maxn, start, f[N], b[N];
vector <int> a[N];
bool vis[N];
signed main() {
    // freopen("P6170_7.in", "r", stdin);
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%lld", &x);
        b[i] = x - 1;
        for (int j = 1; j <= x; ++j) a[i].push_back(++nowid);
    }
    bool flg = 1;
    int m1 = 0, m2 = 0, sum = 0, bg1, st1, st2;
    for (int i = 1; i <= n; ++i) {
        if (f[i - 1] > 0) f[i] = f[i - 1] + b[i];
        else f[i] = b[i], bg1 = i;
        if (f[i] > m1) m1 = f[i], st1 = bg1;
        sum += b[i];
        b[i] = -b[i];
    }
    for (int i = 1; i <= n; ++i) {
        if (f[i - 1] > 0) f[i] = f[i - 1] + b[i];
        else f[i] = b[i];
        if (f[i] > m2) m2 = f[i], st2 = i + 1;
    }
    m2 = sum + m2;
    if (m1 > m2) start = st1;
    else start = st2;
    // 分类讨论最大子段和
    for (int now = start; ; ++now) {
        if (now > n) now %= n;
        if (now == start && flg == 0) break;
        if (a[now].empty()) continue;
        flg = 0;
        int sz = a[now].size();
        int p = now + 1;
        if (p > n) p %= n;
        for (int i = 0; i < sz - 1; ++i) {
            a[p].push_back(a[now][i]);
            d[a[now][i]]++;
        }
        int endnum = a[now][sz - 1];
        a[now].clear();
        a[now].push_back(endnum);
    }
    for (int i = 1; i <= n; ++i) 
        ans += d[i] * d[i];
    printf("%lld", ans);
    return 0;
}
```

这个方法有点麻烦，比其他大佬的方法菜，不过我也是因为看不懂才来写的。

---

## 作者：Orion_Rigel (赞：16)

考虑一下每一个奶牛按下标排序，那么最终的位置必然是连续的一串数（%10意义下）

那么只需要确定好最终的位置，统计就可以了。

显然初始位置和排序数组中的下标之差最大的，最终位置就是当前位置（不需要移动）

其余的按照这种排列移动即可。

···
```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long 
using namespace std;
const int inf=0x3f3f3f3f;
int a[1001],n,x;
int b[1001];
int c[1001],maxx=-inf,p,cnt=0;
long long ans=0;
int main()
{
    scanf("%d",&n);
    for (int i=0;i<n;++i)
    {
        scanf("%d",&x);
        while (x)
        {
            a[cnt++]=i;
            x--;
        }
    }
    for (int i=0;i<n;++i) b[i]=a[i]-i;
    for (int i=0;i<n;++i)
        if (b[i]>maxx) maxx=b[i],p=i;
    c[p]=a[p];
    for (int i=p-1;i>=0;--i)
        c[i]=c[i+1]-1,c[i]%=n;
    for (int i=p+1;i<n;++i)
        c[i]=c[i-1]+1,c[i]%=n;
    for (int i=0;i<n;++i)
    {
        if (c[i]<a[i]) c[i]+=n;
        ans+=((ll)c[i]-a[i])*((ll)c[i]-a[i]);
    }
    printf("%lld\n",ans);
}
···
```

---

## 作者：Vin_1999 (赞：9)

楼下的代码写的很优美，但是题解蒟蒻我看不懂啊，所以由我来组成注释吧。

由于我们要求的是距离的平方和的最小值，那么我们就要用到一个性质：对于这种链式且单向的每个坑（谷仓）都要填一个什么东西（奶牛），当每个奶牛的路径不会经过别的奶牛的时候最小。

至于证明大家自己脑补，我只给出针对三个点的公式(b+c)^2+(a+b)^2<(a+b+c)^2+b^2;

为了不路径重复我们要**逆时针选择**每只奶牛，把奶牛尽量移到离它尽量远的地方。

但这是个环，我们该怎么把它变成一条链呢？

直接就照输入顺序当成一条链做是不行的，这样会留下空位。

另一种做法是破环成链，但楼下用了一种更巧妙的做法。一个性质：不管奶牛怎么分布，总有至少一只奶牛它是不动的。

我们先给每只奶牛顺时针排个序，就有了a数组，表示输入顺序下每个地方应该由哪里的奶牛占去。因为从左到右每个坑保证由剩下的下标最小的奶牛填，所以不会有哪只奶牛会越过别的奶牛。

（想了非常非常久b数组）观察a数组发现有些奶牛反而必须要去左边才能填满谷仓，而这是不符合移动规则的。

记谷仓号-下标为逆差，就有了b数组。（接下来需要烧脑）

事实上逆差=-位移（顺时针为正）。找出逆差最大的那个，如果我们把每只牛的移动路径都加上这个逆差，那就会都成为正数，也就满足移动规律。

那么我们找到的逆差最大的奶牛位移就为0，它一定待在原位。c数组表示下标对应a数组的每只奶牛的最终目的地。c[逆差最大的奶牛的a下标]=它所在谷仓。然后算出c数组就可以算出答案了。

楼下的代码太神了，蒟蒻我想了一天才想出来。

还有我不信这才普及难度，出到提高组应该得分率蛮低吧。


---

## 作者：LYang (赞：4)

看楼下大佬思维如此神奇；

作为蒟蒻的我理解起来可能有点困难；

所以想了一种比较简单又暴力的方法；


大概思路就是：

先将环变成链；

就是将数组复制一份接在a后面；

然后枚举初始位置；

再从此位置向后；

遇到有牛的就都给拿出来放进优先队列；

然后再找一个距离这个位置最远牛放进去；

这样保证最优；

证明楼下已经给了；

就是a^2+b^2<(a+b)^2;

```#include<bits/stdc++.h>

using namespace std;

int n,cnt,ans=1e9,a[4045];

bool flag;

priority_queue<int,vector<int>,greater<int> >q;//小根堆；

int main()

{
	scanf("%d",&n);
	
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),a[i+n]=a[i];
	
    for(int i=1;i<=n;i++)
	
    {
        cnt=0;flag=0;
		for(int j=i;j<=i+n-1;j++)
	{
		if(q.size()==0&&a[j]==0) {flag=1;break;}
		int sa=a[j];
		while(sa--) q.push(j);
		int t=q.top();q.pop();
		cnt+=(j-t)*(j-t);
	}
		if(flag) continue;
		ans=min(ans,cnt);
	}
		printf("%d",ans);
		return 0;
}```

---

## 作者：Supor__Shoep (赞：3)

这篇题解可以让你同时最对两道题。

首先一看到题目我就想到了逆推。。

按照题目要求，让目前每一个牛回到自己的房间，也就是每个房间只允许有一只牛，那么我们就可以用数组假定第 $i$ 头牛的初始房间编号。

接着，我们定义一个队列，这个队列是可以妙用的！！

从一个房间开始，按照逆向遍历完所有的房间，用定义的队列存放每一个空着的房间编号。遍历完之后，此时队列的首位一定是顺时针方向最优的一间。我们把这里多余的牛搬到队列首位的房间去，也就是原本的奶牛数必须要在 $1$ 以上才可以进行此操作。

即为：

    while(a[i]>0&&!que.empty())
    {
        a[i]--;
        a[que.front()]++;
        s[que.front()]=s[i];
        que.pop();
    }
    
#### 这个时候有人要问了：为什么队列首位的房间一定是最优房间呢？

因为这样可以让后面奶牛的移动能量尽量小。不信你试试。。

进行完操作之后，特殊来看队列是有可能还有元素的。这个时候我们进行重复的操作，继续把队列里剩下的元素全部用完，更好达到最优解。

最后就是统计答案了。

这个没有什么说的，按照走过的 $d$ 个房间往答案上增加 $d^2$ 。

此时你以为可以对了

但是别忘记把数据范围看一下（懂的都懂）。

代码如下：

```cpp

#include<bits/stdc++.h>
using namespace std;
int a[100005];
int s[100005];
long long ans;
int main()
{
	queue<int> que;
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	for(int i=0;i<n;i++)
	{
		s[i]=i;
	}
	for(int i=n-1;i>=0;i--)
	{
		while(a[i]>0&&!que.empty())
		{
			a[i]--;
			a[que.front()]++;
			s[que.front()]=s[i];
			que.pop();
		}
		if(a[i]==0)
		{
			que.push(i);
		}
	}
	int i=-1;
	while(!que.empty())
	{
		i=(i+n)%n;
		while(a[i]>0&&!que.empty())
		{
			a[i]--;
			a[que.front()]++;
			s[que.front()]=s[i];
			que.pop();
		}
		if(a[i]==0)
		{
			que.push(i);
		}
		i--;
	}
	for(int i=0;i<n;i++)
	{
		if(s[i]>i)
		{
			ans+=long((i+n-s[i])*(i+n-s[i]));
		}
		else
		{
			ans+=long((i-s[i])*(i-s[i]));
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：CuriousCat (赞：3)

一道超级锻炼思维的好题。三节课就奉献给它了。。。。。。

首先， 我们把它抽象成图， 每一个节点就当成图中的一个节点。每一次奶牛移动都是顶点之间的一条连边， 对应着起点的奶牛数减一， 终点的奶牛数加一， 边的权为花费。

性质一:每个节点的入度恒为一。实际上每个节点度入度可以不是一， 但是既然题目中的能量耗费定义的是d^2, 那么强制规定每一个点的入度为一不但会方便计算， 而且也不会影响算法的正确性。

性质二:每个点的出度等于这个节点的奶牛数。

性质三:图中没有环。如果图中有环， 那么对应着图的定义， 我们可以直接把环去掉， 然后整个图的作用还是和先前一样。


算法流程:

首先， 选定一个点作为起点， 由性质三， 我们可以放心的断环为链。对于每一个出边 ，我们都贪心的找到离它最近的还没有被填起来的入边， 然后填起来。至于这样做为什么是对的， 如图:

可以证明红色的永远是比蓝色优秀的。


PS:还有一点很烦人， 就是没有办法找出起点。如果暴力枚举的话， 会带来\*N的复杂度， 很显然， 这是无法承受的。但是如果求一下最大连续字段和， 那么最大连续字段和中间一定是没有负数的， 要是有的话， 那一段就可以被切掉了， 然后求出最大连续字段和之后我们是不是就已经找到了最优顶点中的一个?


---

## 作者：_zexal_ (赞：2)

## 思路
转换题意，对于第 $i$ 个牛棚来说，有多少个牛经过就等于前面还有多少个牛棚没填满。假设存在一牛棚有 $i$ 头牛走过，那么由于最后每个牛棚只能站一头牛，所以，他前面必定有 $i-1$ 个牛棚为空，这样，我们就转换了题意，把他变成一个环，然后模拟即可，如果有多余的牛，我们就往前走，如果我们每一个点都有了牛，就可以结束了。最后算出对于任意一个牛棚牛的经过次数，然后直接计算即可。对于正确性的保障，也很好说，最先到必定花费最小。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int walk,next,num;
}a[100005];
int n;
long long ans,ans1;
bool book[100005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].num;
		a[i].next=i%n+1; //变成环 
	}
	int post=1;
	while(ans1!=n){
		if(a[post].num>1){前走 
			a[a[post].next].num+=a[post].num-1;
			a[a[post].next].walk+=a[post].num-1;
			a[post].num=1;
		}
		if(a[post].num==1&&book[post]==0){
			book[post]=1;
			ans1++; 
		}
		post=a[post].next;
	}
	for(int i=1;i<=n;i++) ans+=a[i].walk*a[i].walk;
	cout<<ans;
	return 0;
} 
```


---

## 作者：Adchory (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P3137)

一道很好的数论题。

### 题意：
有 $n$ 头奶牛，分布在一些房间，某些房间可能有多头牛，要让这些牛按顺时针移动，使每一个房间恰好有一个奶牛的最小花费。

花费计算：如果一头奶牛穿过了 $d$ 扇门，他消耗的能量为 $d^2$。

### 思路:
对于这道题，我可以直说，用**暴力**就行了，~~根本不需要其他的技巧~~。

首先说一个东西：如果有 $1$ 头奶牛在 $a$ 点，$1$ 头奶牛在 $b$ 点，还有一个没有奶牛的 $c$ 点，且 $c>b>a$，要想有一头奶牛在 $b$ 点，一头奶牛在 $c$ 点，方案 $a \to b,b \to c$ 比方案 $a \to c$ 好。

因为 $\sum c_i = n$，且要使得 $\forall c_i = 1$，每头奶牛走的步数最少，所以可以直接从第 $1$ 个房间开始遍历，如果 $c_i > 1$，就把这个房间的 $ (c_i-1)$ 头奶牛移到后面的一个房间，留在这个房间里的奶牛一定是步数走的最多的，所以不用判断每头奶牛的新旧，以此类推，直到满足 $\forall c_i =1$，循环结束。

比如说:

样例数据 : `10 1 0 0 2 0 0 1 2 2 2`.

明显最优的方案是：
$4\to5,4\to6,1\to4,10\to3,10\to2,9\to1,9\to10,8\to9$ 。

如果一个一个走的话，时间复杂度是 $O(n^2)$，不会爆。

但是如果全部走的话，时间复杂度是 $O(n)$，刚好。

## 贴贴代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct node{ll N,S,W;}a[101000];
// N 当前房间的下一个房间
// S 当前房间还有多少头牛
// W 当前房间还有多少头牛
ll n,ans,p=1;
int main(){
	cin>>n;
	for(ll i=1;i<=n;i++) cin>>a[i].S;
	for(ll i=1;i<=n;i++)
		a[i].N=i+1;
	a[n].N=1;
    // 记录当前房间的下一个房间的编号
	for(ll i=1;i<=2*n;i++){
		if(a[p].S>1){
			a[a[p].N].S+=a[p].S-1;
			a[a[p].N].W+=a[p].S-1;
			a[p].S=1;
		}
		p=a[p].N;
	}
	for(ll i=1;i<=n;i++) ans+=(a[i].W*a[i].W);
	printf("%lld",ans);
	return 0;
}
```
时间复杂度还挺低 , $O(n)$。

~~这样你就能一下 A 两道题啦~~

---

## 作者：Vic_ (赞：1)

\_尝试无数次提交题解但都被挡会的苟蒻又来发题解了\_

\_行行好吧。。。。。。\_


好，言归正传。这题是个破环为列的题目，只需要枚举顶点，再不停地递推奶牛位置，是最终实现每个牛棚一只奶牛的目标。将过程中所有得出的步数平方和对比，得最优解，输出。AC

上代码

        
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int n;
int rcow[10001];
int step[10001];
bool hash[10001];
int cow[10001];
int ans= 1 << 30;
int res=0;
int abs(int x)//确保每次的点在该环上，破环为列的关键
{
    if(x>n)x-=n;
    return x;
}
void reset(void)//每次重置，以防数组囤积起来
{
    memset(step,0,sizeof(step));
    for(int i=1;i<=n;i++)
        cow[i]=rcow[i];
}
int main()
{
    memset(step,0,sizeof(step));
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        int x;
        cin >> x;
        for(int j=1;j<=x;j++)
            rcow[++res]=i;//确定每次重置的对象数组
    }
    for(int i=1;i<=n;i++)
    {
        reset();
        res=0;
        memset(hash,0,sizeof(hash));
        for(int j=0;j<n;j++)
        {
            if(hash[cow[abs(i+j)]]==0)
            {
                hash[cow[abs(i+j)]]=1;//说明该牛棚有奶牛了
                continue;
            }
            else
            {
                while(hash[cow[abs(i+j)]]==1)
                {
                    cow[abs(i+j)]=abs(cow[abs(i+j)]+1);//有牛了就让奶牛往前走
                    step[abs(i+j)]++;
                }
                hash[cow[abs(i+j)]]=1;
            }
        }
        for(int j=1;j<=n;j++)
            res+=step[j]*step[j];    
        if(res<ans)ans=res;//对比
    }
    cout << ans;
    return 0;
}
```

---

## 作者：羚羊WANG (赞：1)

相信大家看到这里的时候对题目都有了比较深刻的了解

题目让我们求消耗能量的最小值

通过观察数据，我们可以发现$n \leq 1000$，我们可以考虑暴力
来解决问题

我们可以考虑环的情况，如果存在环，我们就可以把环上的一个点设定为起点，这样他会形成一个序列

我们可以在有前导零的情况

我们可以将区间左右移，方案也是一样的

看到这里，我们可以找到区间，并根据区间找到最优方案即可

考虑三重循化，可以转移我们所求的状态

代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int c[2010];
int a[1010];
int n;
int ans;
int l,r;
int cnt;
signed main(){
	n=read();
	for(register int i=1;i<=n;++i)
		a[i]=read();
	for(register int i=1;i<=n;++i)
		{
			c[i]=a[i];
			c[i+n]=a[i];	
		}
	for(register int i=1;i<=n;++i)
		{
			l=1;
			r=0;
			cnt=i;
			ans=0;
			for(register int j=i;j<n+i;++j,cnt=j)
				{
					for(register int k=1;k<=c[j];++k)
						{
							r++;
							a[r]=j;
						}
					c[j]=0;
					if(l>r)
						{
							ans=-1;
							break;
						}
					else
						{
							ans=ans+(a[l]-j)*(a[l]-j);
							l++;
						}
				}
			if(ans>-1)
				break;
			i=cnt;
		}
	write(ans);
	return 0;
}

```


---

