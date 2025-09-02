# Black Cells

## 题目描述

You are playing with a really long strip consisting of $ 10^{18} $ white cells, numbered from left to right as $ 0 $ , $ 1 $ , $ 2 $ and so on. You are controlling a special pointer that is initially in cell $ 0 $ . Also, you have a "Shift" button you can press and hold.

In one move, you can do one of three actions:

- move the pointer to the right (from cell $ x $ to cell $ x + 1 $ );
- press and hold the "Shift" button;
- release the "Shift" button: the moment you release "Shift", all cells that were visited while "Shift" was pressed are colored in black.

 (Of course, you can't press Shift if you already hold it. Similarly, you can't release Shift if you haven't pressed it.)Your goal is to color at least $ k $ cells, but there is a restriction: you are given $ n $ segments $ [l_i, r_i] $ — you can color cells only inside these segments, i. e. you can color the cell $ x $ if and only if $ l_i \le x \le r_i $ for some $ i $ .

What is the minimum number of moves you need to make in order to color at least $ k $ cells black?

## 说明/提示

In the first test case, one of the optimal sequences of operations is the following:

1. Move right: pointer is moving into cell $ 1 $ ;
2. Press Shift;
3. Release Shift: cell $ 1 $ is colored black;
4. Move right: pointer is moving into cell $ 2 $ ;
5. Move right: pointer is moving into cell $ 3 $ ;
6. Press Shift;
7. Move right: pointer is moving into cell $ 4 $ ;
8. Release Shift: cells $ 3 $ and $ 4 $ are colored in black.

 We've colored $ 3 $ cells in $ 8 $ moves.In the second test case, we can color at most $ 8 $ cells, while we need $ 20 $ cell to color.

In the third test case, one of the optimal sequences of operations is the following:

1. Move right: pointer is moving into cell $ 1 $ ;
2. Move right: pointer is moving into cell $ 2 $ ;
3. Move right: pointer is moving into cell $ 3 $ ;
4. Press Shift;
5. Move right: pointer is moving into cell $ 4 $ ;
6. Move right: pointer is moving into cell $ 5 $ ;
7. Release Shift: cells $ 3 $ , $ 4 $ and $ 5 $ are colored in black.

 We've colored $ 3 $ cells in $ 7 $ moves.

## 样例 #1

### 输入

```
4
2 3
1 3
1 4
4 20
10 13 16 19
11 14 17 20
2 3
1 3
1 10
2 4
99 999999999
100 1000000000```

### 输出

```
8
-1
7
1000000004```

# 题解

## 作者：Flanksy (赞：10)

#### 贪心

------------

抽象题意：给出 $n$ 个不相交且相互之间距离至少为 $1$ 的区间，对某个区间的子区间 $[l,r]$ 染色的代价为 $r-l+3$，求总染色长度为 $k$ 时的最小花费，如果不可行输出 $-1$。

试着拿堆做，最后还是没做出来，只好写正解了。

可以证明选择长度大于等于 $2$ 的区间一定不劣：假设最优答案为 $ans$ 且获得 $ans$ 的过程中存在一个长度为 $len(len\geq 2)$ 的区间 $[l_i,r_i]$ 被跳过，对 $[l_i,r_i]$ 染色至少可以少走 $len$ 步，选择这段区间增加的花费为 $2$。由于 $len\geq 2$，选择对这段区间染色的答案为 $ans'=ans-len+2\leq ans$，$ans$ 可能不是最优答案，矛盾。

所以只需要记录 $len=1$ 的区间数量，贪心选择 $len\geq 2$ 的区间即可。当 $len\geq 2$ 的区间总长度大于 $k$ 后选择的区间都是不优的。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans,sum,one,two,l[200005],r[200005];
void solution(){
	cin>>n>>k,sum=0;
	for(int i=1;i<=n;i++) cin>>l[i];
	for(int i=1;i<=n;i++) cin>>r[i];
	for(int i=1;i<=n;i++) sum+=r[i]-l[i]+1;
	if(sum<k) return cout<<"-1\n",void();
	sum=0,one=0,two=0,ans=INT_MAX;
	for(int i=1;i<=n;i++){
		static int len,ned;
		len=r[i]-l[i]+1;//当前线段长度 
		if(len==1) one++;//区分长度统计 
		else two++,sum+=len;
		if(sum>=k){//不需要补1的情况 
			ned=len-(sum-k);//实际需要染色的长度 
			ans=min(ans,l[i]-1+ned+two*2);
			break;//继续向后不可能存在更优情况 
		}
		else if(sum+one>=k){//需要补1的情况 
			ans=min(ans,r[i]+two*2+(k-sum)*2);
		}
	}
	cout<<ans<<'\n';
}
int T;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--) solution();
	return 0;
}
```


---

## 作者：LinuF (赞：5)

~~提供一个很好想（比较套路的）反悔贪心的思路。~~
### 思路
考虑观察性质可知答案只和**右端点大小**以及**选择的区间数量**有关。甚至可以直接写出计算式，当选择的区间覆盖的点数大于等于 $k$ 的时候，显然答案会的等于最大的右端点加上选择的区间数量乘以 $2$。但是我们不确定到底以哪个右端点，也不确定保留哪些区间。

使用反悔贪心。用堆维护堆元素之和大于等于 $k$ 的所有区间长度，堆内保留的元素一定是前 $size$ 大的区间长度。每一次和答案取 $max$ 即可。

### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
template<typename types>
inline void read(types &x){
    x = 0; char c = getchar(); int f = 1;
    while (!isdigit(c)){ if (c == '-') f = -1; c = getchar(); }
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    x *= f; return;
}
inline void read(){}
template<typename types, typename... Args>
void read(types &x, Args&... args){
    read(x), read(args...);
    return;
}
template<typename types>
void write(types x){
    if (x < 0) putchar('-'), x = -x;
    types k = x / 10;
    if (k) write(k);
    putchar(x - k * 10 + '0');
    return;
}
const int N=2e5+5;
int l[N],r[N],n,k;
void solve(){
    priority_queue<int,vector<int>,greater<int>> q;
    read(n,k);
    for(int i=1;i<=n;i++) read(l[i]);
    for(int i=1;i<=n;i++) read(r[i]);
    int num=0,sum=0,ans=INT_MAX;
    for(int i=1;i<=n;i++){
        q.push(r[i]-l[i]+1);num++;sum+=r[i]-l[i]+1;
        while(q.size()&&sum>=k){
            ans=min(ans,r[i]-(sum-k)+num*2);
            sum-=q.top();q.pop();num--;
        }
    }
    if(ans==INT_MAX){
        write(-1);puts("");
        return;
    }
    write(ans);puts("");
}   
signed main(){
#ifndef ONLINE_JUDGE
    freopen(".in","r",stdin);
#endif  
    int T;
    read(T);
    while(T--)
        solve();
    return 0;
}
```


---

## 作者：2018ljw (赞：2)

首先操作次数可以拆分为两部分：
1. 最远向右走到哪里。
2. 涂了多少连续段。

对于这种问题，类似 [P2107](https://www.luogu.com.cn/problem/P2107) 的套路，我们先确定最远走了多少，然后贪心最小化第二部分的代价。

贪心部分显然，尽可能保留长的连续段。

从左到右枚举每个连续段。遇到新的一段时，若当前总长度加上这段仍不够，我们直接把这段加入，然后考虑下一段。

否则，我们先在这段上走一部分让总长度够，然后考虑用剩下的部分替换一些段。

有结论是，这种情况下，被替换的段长度只能为 $1$。

考虑如果我们要替换掉一个 $x$ 长度的连续段，那就要往右多走 $x$ 步，然后可以少涂一段，减少的操作次数为 $2-x$。因此，$x\neq 1$ 的情况下一定不优。

因此，记录当前选了几段，以及有多少段长度为 $1$，每次暴力替换即可。

这样无需考虑新加入一个整段时，对之前段选法的影响。因为如果替换掉的长度只有 $1$，那么会在上一部分暴力处理完。否则就是多走至少 $x$ 步来节约两步，此后的决策一定是不优的。

[code](https://codeforces.com/contest/1821/submission/202864688)。

---

## 作者：Hisaishi_Kanade (赞：1)

考虑染一个区间需要的花费。

首先，进入这个区间开机器人；然后关机器人。

只需要两次操作，即花费为 $2$。

那么显然的，如果区间长度 $\ge 2$，选择是肯定不劣的。

那如果区间长度 $=1$，选还是不选呢？

我们可以先记录下来，当染的格子加上记录的格子足够的时候记录答案。

我们对“选不选长度为 $1$ 的区间”分类讨论一下即可。

另外有一个优化：如果不选长度为 $1$ 的区间就满足条件了，就可以不必考虑选的情况（显然成立）。

```cpp
#include <stdio.h>
#define rep(i,l,r) for(i=l;i<=r;++i)
using ll=long long;
const ll inf=1ll<<55;
const int N=200005;
ll ret;
int n,k,i;
int l[N],r[N];
ll cnt,used,len,sl;
inline ll min(ll x,ll y){return x<y?x:y;}
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		ret=inf;
		scanf("%d %d",&n,&k);
		rep(i,1,n)
			scanf("%d",l+i);
		rep(i,1,n)
			scanf("%d",r+i);
		cnt=used=sl=0;
//sl 是 len>=2 的区间长度之和。
//cnt 记录 len=1 的个数
//used 每加入一个 len>=2 的，就需要开关机各一次，used <- used+2
		rep(i,1,n)
		{
			len=r[i]-l[i]+1;
//			printf("debug:%d %d %d %d %d\n",len,sl,used,ret,l[i]);
			if(sl+len>=k)//不选 len=1 也足够
			{
				ret=min(used+l[i]+k-sl+1,ret);//先前所用（used）加上当前区间所用。
				break;
			}
			else if(sl+len+cnt>=k)
				ret=min(used+(k-sl-len)*2+r[i]+2,ret);//先前所用（used）加上 len=1 所用（(k-sl-len)*2）加上当前所用。
			if(len==1)
				++cnt;
			else
			{
				used+=2;
				sl+=len;
			}//记录
		}
		printf("%lld\n",ret==inf?-1:ret);
	}
}

// 几个统计的变量一定要清空。
// 多测不清空，抱灵两行泪。
```

---

## 作者：falling_cloud (赞：1)

一道凭着贪心连续推导的题目，在很多部分感性猜出的结论都可能快理性证明一步，这就是 guessforces 的奇妙之处！

题目中的要求是给至少 $k$ 个块染色，但很显然的是，染色恰好 $k$ 个的最优方案代价一定不高于染 $k$ 个块以上的代价：最优方案的结束点一定是某条线段覆盖范围之内，因为在染色块数达到 $k$ 个之后没有理由继续进行其他操作。

首先可以发现一个结论：如果不是被选择染色的最后一条线段，那么给它完全染色一定优于只染其中的若干个，因为指针向后移动而找到新的未被染色线段的代价至少是 $1$，而在确认终点的情况下把眼前这条线段完全染色的代价和不完全染色的代价相同。

接下来需要想的就是哪一些线段可以被选择，我们先假设在某个方案中，有一个长度为 $x$ 的线段被选择了，这个方案结束时指针处于 $r$ 的位置。如果不选择这个线段，可以省下来的操作数为 $2$。并且为了补齐缺失的染色块，指针至少需要多移动 $x$ 次，所以得出一个结论：当线段长度 $x \geq 2$ 时，选择这条线段一定比不选优。

那么我们只需要记录长度为 $1$ 的线段个数，然后记录其他块被选择后被染色的块数和松放 Shift 的代价，顺序扫过去就可以了，可以发现的是，如果选择了使用长度为 $1$ 的线段，那么这是结束位置一定是某条线段的结尾（因为如果不是结尾就直接右移指针而不是拿散块来凑数了）。而如果不选择长度为 $1$ 的线段，那么就是统计其他块在什么时候总和会大于 $k$，这时给指针“回退”若干次并统计就可以了。

分讨完这几个情况后，实现的细节并不多，代码是赛时写的，有点丑。


```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std; 
const int N = 2e5 + 5; 
const int M = 1e9 + 7;
int a[N],b[N]; 
void solve()
{
	int i,j,n,m,k,l,r,x,y,w,sum=0,ans=1e18,cnt=0,Max=0,Min=1e9+5,key=0,tot=0;
	int tmp=0,la;
	bool flag=true;
	cin>>n>>k;
	for(i=1;i<=n;i++)	cin>>a[i];
	for(i=1;i<=n;i++)	cin>>b[i],tot+=(b[i]-a[i]+1);
	if(tot<k){cout<<"-1"<<endl;return ;}//可以染色的块数比 k 小自然是无解
	for(i=1;i<=n;i++)
	{
		if(a[i]==b[i])	
		{
			cnt++;	x=k-sum;
			if(cnt>=x)
			{
				ans=min(ans,a[i]+tmp+2*x);
			}
		}
		else			
		{
			x=k-sum;
			tmp+=2;
			if(x<=b[i]-a[i]+1)
			{
				ans=min(ans,a[i]+x-1+tmp);
				break;
			}
			sum+=(b[i]-a[i]+1);
			x=k-sum;
			if(cnt>=x)
			{
				ans=min(ans,b[i]+tmp+2*x);	
			}			
		}
	}
	cout<<ans<<endl;
} 
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int Ti;
	for(cin>>Ti;Ti;Ti--)
		solve();
	return 0;
}
```



---

## 作者：Zimo_666 (赞：0)

## D. Black Cells

### Statement

在一条数轴上有无穷个点，下标为 $0, 1, 2, \ldots$，初始时每个点都是白色的。

你控制着一个机器人，初始时机器人位于坐标为 $0$ 的那个点。  

机器人有两种状态：激活状态 和 非激活状态。  

当处于激活状态时，机器人所在的点都会被染成黑色。

处于非激活状态时，机器人所在的点不会被染成黑色。  

初始时机器人处于非激活状态。  

你可以对这个机器人进行若干次操作，操作分为三种类型。每一次操作，你可以选择如下三种操作之一执行：  

- 将机器人的位置像数轴的正方向移动一个单位（即：若当前机器人在坐标 $x$，则执行一次该操作后机器人将移动到坐标 $x+1$ 的那个点）；
- 激活机器人：该操作只有当机器人处于非激活状态时才能执行，执行该操作后机器人将变为 激活状态；
- 撤销激活机器人：该操作只有当机器人处于激活状态时才能执行，执行该操作后机器人将变为 非激活状态。

有 $n$ 个区间，第 $i$ 个区间用 $[l_i, r_i]$ 表示。  

你需要使用最少的操作次数，将至少 $k$ 个点染成黑色，但是有一个限制，就是：这些染成黑色的点必须包含在至少一个给定的区间中，这也就是说，如果你要将坐标为 $x$ 的那个点染成黑色，则必须保证存在一个 $i(1 \le i \le n)$ 满足 $l_i \le x \le r_i$。  

同时，本题也要求操作结束时机器人恢复到非激活状态（这也就意味着最少操作次数对应的最后一次操作是 _撤销激活机器人_）。

问：至少需要进行几次操作能够使至少 $k$ 个点被染成黑色，且最终机器人处于非激活状态？

### Solution

首先选取长度大于等于 `2` 的区间肯定不劣。考虑最后答案的组成会是什么样子的，要么全部选取一些长度大于等于 `2` 的区间，最后没选完就够了。要么选取一些长度大于等于 `2` 的区间再拼一些长度为 `1` 的区间。

显然如果是第一种的话答案唯一。第二种可能之后加上一些长度大于等于 `2` 的区间拼成答案。

[Code](https://codeforces.com/contest/1821/submission/229527521)

---

## 作者：541forever (赞：0)

本文提供一种写法十分简洁的线性做法。（然而本蒟蒻赛时写了一个线段树上二分还没调出来

首先，我们可以枚举最后一个选的线段是哪一条，考虑前面选了哪些线段，不难发现，选一个前面的线段的代价为 $2$，这就意味着，选掉前面的所有长度 $\ge 2$ 的线段一定不劣，那么预处理出前面线段 $\ge 2$ 的线段的数量和长度，以及长度为 $1$ 的线段的数量，便可以直接计算最后一条线段为当前线段的最小代价了。具体实现可以看[代码](https://codeforces.com/contest/1821/submission/203025332)。

---

