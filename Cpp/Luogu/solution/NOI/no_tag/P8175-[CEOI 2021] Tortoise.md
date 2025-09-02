# [CEOI 2021] Tortoise

## 题目背景

译自 CEOI2021 Day2 T2. [Tortoise](https://hsin.hr/ceoi/competition/ceoi2021_day2_tasks.pdf)。


## 题目描述

Wilco 想购买糖果，为此它将访问 Nakamise 商店街。

Tom 想让 Wilco 少吃点糖果，为此它将在 Wilco 前购买一些糖果。商店街上共有 $N$ 个等距离的地点，它们要么是商店要么是空地。

每家商店都有一定数量的糖果（可能为 $0$） Wilco 将会从第一个地点走到最后一个，顺序访问所有地点。每当它到达一家商店时它会买走所有糖果。Tom 每一刻的移动速度是 Wilco 的两倍，且可以朝两个方向移动。但是，Tom 每一刻只能携带最多一颗糖果。一旦 Tom 拿到一颗糖果，它就会把它带走直到把它交给在空地上玩的小孩。假设购买和给出糖果均不消耗时间。

Tom 的目标是最小化 Wilco 能拿到的糖果。初始时它们均在第一个地点，Tom 任何时刻先于 Wilco 行动。即如果第一个地点是商店，Tom 可以先于 Wilco 购买一颗糖果。

那么在 Tom 的干扰下 Wilco 能拿到多少糖果呢？

## 说明/提示

#### 数据范围与约定

对于 $100\%$ 的数据：$1\leq n \leq 5\times 10^5$，$-1\leq a_i \leq 10^4$。

| 子任务 | 分值 |                       约束                        |
| :----: | :--: | :-----------------------------------------------: |
|  $1$   | $8$  |          $1\leq N\leq 20$，$-1\leq a_i\leq 1$          |
|  $2$   | $10$ |         $1\leq N\leq 300$，$-1\leq a_i\leq 1$          |
|  $3$   | $30$ |     $1\leq N\leq 300$，$-1\leq a_i\leq 10^4$      |
|  $4$   | $25$ | $1\leq N\leq 5\times 10^3$，$-1\leq a_i\leq 10^4$ |
|  $5$   | $27$ | $1\leq N\leq 5\times 10^5$，$-1\leq a_i\leq 10^4$ |

## 样例 #1

### 输入

```
5
-1 1 1 1 1```

### 输出

```
2```

## 样例 #2

### 输入

```
8
-1 1 0 0 -1 0 0 3```

### 输出

```
1```

## 样例 #3

### 输入

```
8
2 -1 2 -1 2 -1 2 -1```

### 输出

```
1```

# 题解

## 作者：_ZSR_ (赞：5)

### [P8175 [CEOI2021] Tortoise](https://www.luogu.com.cn/problem/P8175)

定义一段区域表示一段极大的子区间，其中至少有一个糖果，并且没有垃圾站。

我们可以发现这样一个事实，对于一段区域，一定会先买一些糖，然后丢到这段区域左边的空地上，再买一些糖，丢到这段区域右边的空地上。后半段很好理解，假设在第 $j$ 段区域买了糖，那么我们可以把买的地点下标最大的那颗糖在去第 $j+1$ 段区域的路上顺路扔在第 $j$ 段区域右边的空地上。考虑证明前半段，假设先买了一颗糖丢到右边，再买了一颗糖丢到左边。令这段区域左右两边的空地分别位于 $a,d$，两次买糖的位置分别位于 $b,c$，其中 $a<b \leq c<d$。分别求出两种扔糖方案的距离后可以发现，把 $c$ 扔到右边，把 $b$ 扔到左边优于把 $c$ 扔到左边，把 $b$ 扔到右边。

根据扔的方式不同，我们把所有行动分为三种。第一种：从某个糖出发，把它扔到左边离它最近的空地然后回来。第二种：从某个空地出发，往左走去买一颗糖，然后回来扔掉。第三种：从一个空地出发，买了一颗糖，走到下一个空地扔掉。那么我们会发现，对于每一段区域，我们都会先进行第一种行动，然后进行第三种行动，最后进行第二种行动。

问题在于我们不知道在哪个地方进行哪种行动，进行几次最优。那么我们可以考虑反悔贪心，先尽量扔，扔不了了再调剂。具体的，我们用大根堆维护扔掉每一颗糖需要付出的路程代价，对于每一个糖果商店的 $a_{i}-1$ 颗糖，枚举通过第一种和第二种行动扔掉的个数。如果还可以扔，那么就扔，不然如果堆顶的糖扔掉的代价大于它，那么把堆顶弹掉，相当于不扔堆顶了，转成扔它。那么剩下的那颗糖是干什么的呢？注意到，对于那 $a_{i}-1$ 颗糖，我们只考虑了第一种和第二种行动，第三种行动被我们忽略了，因此剩下的那颗糖就是枚举第三种行动的。

还有一些具体的实现就在代码注释里讲吧。

code
```
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int n;
int a[N],pre[N],nxt[N],to[N];
priority_queue<int> q;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for (int i=1;i<=n;++i) cin>>a[i];
	pre[0]=-1e9;
	for (int i=1;i<=n;++i)//找到前一个空地
    {
		pre[i]=pre[i-1];
		if (a[i]==-1) pre[i]=i;
	}
	nxt[n+1]=1e9;
	for (int i=n;i>=1;--i)//找到后一个空地
    {
		nxt[i]=nxt[i+1];
		if (a[i]==-1) nxt[i]=i;
	}
	int last=0;
	for (int i=n;i>=1;--i)//这个数组的含义不太好描述，结合后面理解一下
    {
		if (a[i]==0) continue;
		if (a[i]==-1)
        {
			last=0;
            continue;
		}
		to[i]=last,last=i;
	}
	int sum=0,ans=0;
	for (int i=1;i<=n;++i)
    {
		if (a[i]==-1) continue;
		if (a[i]==0) continue;
		int cnt=a[i]-1,dis=min(i-pre[i],nxt[i]-i)*2;
		while (cnt)
        {
			if (sum<=i-1)//不用乘2的原因是Tom走到i也走了i-1的路程，相当于他只剩下i-1的路程可以继续走
            {
				q.push(dis);
				sum+=dis;
				++ans,--cnt;
				continue;
			}
			else if (dis<q.top())
            {
				sum-=q.top();
                q.pop();
                --cnt;
                sum+=dis;
				q.push(dis);
                continue;
			}
			else break;
		}
		dis=(i-pre[i])<<1;
		if (!to[i]) dis=0;//直到下一个空地之间都没有有糖的地方，那么就把这颗糖顺路带过去
		else dis=min(dis,(nxt[i]-to[i])<<1);//减to[i]而不是减i是因为这里所有的糖已经考虑完了，不用再回来了
		if (sum<=i-1)
        {
			q.push(dis);
			sum+=dis;
			++ans;
		}
		else if (dis<q.top())
        {
            sum-=q.top();
            q.pop();
            sum+=dis;
            q.push(dis);
		}
	}
	ans=-ans;
	for (int i=1;i<=n;++i) if (a[i]!=-1) ans+=a[i];
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：SnowTrace (赞：3)

有意思的题。

设每个位置与最近的空地距离为 $d_i$，设被选了至少一次的位置为 $S$，考虑如果钦定一个 $S$，最优的策略。

很容易发现，最优的策略一定是从左到右的访问商店。

一个比较 trivial 的想法是，每选择一个数，就要多浪费 $2d_i$ 的时间（从商店跑到最近的空地再跑回来），显然是不对的。考虑最后一次买商品的时候，实际上没有必要回到原点，如果当前在商店 $a$，下一步要去商店 $b$，$[a,b]$ 间存在一个空地，那我们带着最后一个商品直接往前走就可以，这就不需要花费额外的时间。

还有一种情况，称为决策 2：存在一个 $c>b$ 使得 $c$ 是空地，这时会花费额外的 $2c-a-b$ 的时间。

发现这个就不是很好做，因为在一个商店购买若干物品的代价甚至还可能和下一个你要去商店的位置有关。我们再考虑决策 2，如果我们在 $b$ 点购买了一件商品，运到 $c$，代价只需要 $2c-2b$，这个数比 $2c-a-b$ 小。更进一步的，设 $a$ 右边第一个商店是 $p_a$，则如果我们做了决策 2，$p_a$ 应该被选满，否则可以进行调整。


所以如果做了决策 2 则 $a$ 在 $S$ 中的后继一定是 $p_a$，否则做决策 2 不优，再设 $a$ 后面第一个空地位置是 $q_a$，我们可以等价的认为在 $a$ 位置上购买的最后一个商品需要额外花费的时间是 $c_a = \min(2d_a,\max (0,2q_a-2p_a))$。

也就是说我们可以在 $a$ 位置买一个代价为 $c_a$ 的商品，也可以在 $a$ 位置买不超过上限个代价为 $2d_a$ 的商品，要求如果当前在位置 $i$ 则花费的总代价不能超过 $i-1$。这个问题可以简单的用反悔贪心解决。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 10000000000;
int n;
int a[500005],pre[500005],nxt[500005],pos[500005];
priority_queue<int>q;
signed main(){
	cin >> n;
	for(int i =1;i<=n;i++)cin >> a[i];
	pre[0] = -inf;for(int i = 1;i<=n;i++){if(a[i]==-1)pre[i]=i;else pre[i] = pre[i-1];}
	nxt[n+1] =inf;for(int i = n;i>=1;i--){if(a[i]==-1)nxt[i]=i;else nxt[i] = nxt[i+1];}
	int p = 0;
	for(int i = n;i>=1;i--){
		if(a[i]==0)continue;
		if(a[i]==-1)p = 0;
		else pos[i] = p,p = i;
	}
	int ans = 0,tot = 0;
	for(int i = 1;i<=n;i++){
		if(a[i] == 0 or a[i] == -1)continue;
		int d = min(i-pre[i],nxt[i]-i)*2;
		for(int j = 1;j<a[i];j++){
			if(tot<=i-1){
				q.push(d);
				tot += d;
				++ans;
			}else if(q.size() and d<q.top()){
				tot -= q.top();
				q.pop();
				tot += d;
				q.push(d);
			}else break;
		}
		if(!pos[i])d = 0;
		else d = min(i-pre[i],nxt[i]-pos[i])*2;
		if(tot<=i-1){
			q.push(d);
			tot += d;
			++ans;
		}else if(q.size() and d<q.top()){
			tot -= q.top();
			q.pop();
			tot += d;
			q.push(d);
		}
	}
	replace(a+1,a+1+n,-1,0);
	int res = accumulate(a+1,a+1+n,0)-ans;
	cout << res << endl;
	return 0;
}
```

---

## 作者：UNVRS (赞：3)

## 题意

$n$ 个位置，每个位置可能有游乐园或若干糖果。

Tom 在 $0$ 时刻位于位置 $1$，每 $1$ 时刻可以移动 $2$ 位置。有糖果可以带一个糖果，然后（必须）去到一个游乐园放下糖果（带上与放下均不消耗时间）。当时间严格大于 $T$ 时位置 $T$ 上的糖果会消失。

问最少消失几颗糖果。

$n\le5\times10^5$

## 思路

### 初步分析

显然我们带一个糖果之后，必须去左右最近的一个游乐园放下去，所以我们定义两个游乐园及中间的部分为一个区块（一个游乐园允许在多个区块中），特殊的，如果最左边没有游乐园我们依然视其为一个区块（注意最右边不算）。我们假定每个区块中至少有一颗糖果，否则我们忽略这个区块。对于总的移动情况，我们肯定是从左到右依次处理每个区块。

然后考在区块内的移动方式，分为三种：

1. 左循环：

    ```plain
    游乐园 --出程-> 糖果
    游乐园 <-归程-- 糖果
    ```

2. 右循环：

    ```plain
    糖果 <-出程-- 游乐园
    糖果 --归程-> 游乐园
    ```

3. 漫游（从官方题解生草出来的）：

    ```plain
    游乐园 --出程-> 糖果 --归程-> 游乐园
    ```

~~你谷不支持 mermaid，愤怒了。~~

那么对于一个区块内，我们显然是先**从左到右**做若干个左循环，然后做一次漫游，然后**从左到右**做若干个右循环。

如果我们规定 A 必须从最左边走到最右边的话，显然漫游是不会增加我们总的移动时间的，所以我们规定每个区块都必须进行一次**有糖果**的漫游。

对于任意一个不进行漫游的糖果，我们显然是选择最短的一个循环把它做掉。

因为总的能移动的时间是有限的，所以我们考虑先处理距离最短的糖果。

于是我们对这个距离排序，然后一颗一颗插入糖果（循环），只要合法就继续。

> 这边建议您可以先到此为止，尝试写一个 $O(n^2)$ 的做法。

关于正确性，你考虑如果一个糖果 $x$ 试图弹出前面的糖果 $y$ 以使得自己合法，那么有两种情况：

1. $y$ 的位置大于 $x$，这样显然不优；
2. $y$ 的位置小于 $x$，这样看起来似乎我们可以给中间的糖果多一些机会，然而因为如果这中间有任何没有被插入的糖果，那么其耗时一定是大于被弹出的糖果的（否则在 $y$ 加入之前就被加入了），故插入任何糖果都会使得 $x$ 不合法。

于是这样并不会带来更多的收益，所以我们无需考虑它的发生。

## 做法一

### 二步分析

> 对于满分，我们可以用一些数据结构维护。

以上官方题解原话。

~~我们发现这题解太棒了，以后 Ynoi 的题目都可以这么写题解：~~

> 这道题要维护……我们可以用一些数据结构维护。

---

首先我们分析一下加入一颗糖会对它之后产生什么影响，由于我们插入的是循环，所以我们可以把贡献打到其对应的游乐园上。

那么我们的需求就分为两个部分，挂在游乐园上的循环对时间的要求以及游乐园之间的漫游对时间的要求。糖果的具体可行性要根据左右循环以及漫游进行讨论：

1. 左循环：

   因为所有距离比这颗糖果小的糖果都已经计算过了，所以这颗糖果一定是最右的一个。我们对游乐园 $i$ 维护一个 $out_i$ 表示我们在 $out_i$ 时刻在游乐园 $i$，并且接下来准备润到右边的区块（左边的区块被放弃），这样我们就可以判断这颗糖果是否可行。

   我们再维护一个 $in_i$ 表示我们第一次到达游乐园 $i$ 是在时刻 $in_i$，我们可以维护出 $mx0_i$ 表示游乐园 $i$ 最晚能在什么时候到达，这样就可以判断后面的循环是否合法。

2. 右循环：

   同理，这颗糖果是最左的一个，那么我们相当于在原有的 $in$ 上加了一个循环，为了维护 $in$ 的含义，我们直接在 $mx0_i$ 上减去这个距离。

3. 漫游：

   我们可以先对每一个区块钦定最右的糖果，表示这颗糖果将会漫游。

   在加循环时，若我们将令这个糖果进行循环，就将这个钦定向左转移。

   这样就会变成这个区间左边的游乐园的 $out$ 最大值受到了一定的限制，即 $mx1_i$。

   注意最左若没有游乐园则需要特殊处理。

我们可以令 $mx0$ 始终减去 $in$，对 $mx1$ 同样操作，这样就可以将判断是否大于某个值变为是否大于零，便于数据结构维护。

我们发现 $in,out$ 均需要支持单点查询，后缀加减。$mx0,mx1$ 还需要额外支持单点修改，后缀最小值。线段树即可。

### 实现

处理最左边的时候，可以设 $0$ 有一个游乐园，但是所有点与它的距离为 $+\infty$。

无论是左循环还是右循环，都要注意可能对 $mx0$ 做出限制。

不然完整数据会挂一个点（不清楚谷上有没有这个点）。

### CODE

看了看代码感觉 $in/out$ 与 $mx0/mx1$ 可以去掉其中一个，但是我不想动脑了，于是喜提最劣解。

```c++
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=500010,FSIZE=1<<24,INF=0x33ffffff;
using ll=long long;
int n,a[N],l[N],lf[N],r[N],s[N];
ll ans;
struct candy{int d,x,t,p;};
vector<candy> v;
vector<int> c[N];
struct node0{
    int a;
    void operator+=(int x){a+=x;}
    void pushup(node0,node0){}
};
struct node1{
    int a,mi;
    node1(){mi=INF;}
    node1(int x){a=mi=x;}
    void operator+=(int x){a+=x;mi+=x;}
    void pushup(node1 &x,node1 &y){mi=min(x.mi,y.mi)+a;}
};
template<typename node>struct ST{
    node a[N<<2];
    void pushdown(int x){
        if(a[x].a){
            a[x<<1]+=a[x].a;
            a[x<<1|1]+=a[x].a;
            a[x].a=0;
        }
    }
    void pushup(int x){
        for(;x;x>>=1) a[x].pushup(a[x<<1],a[x<<1|1]);
    }
    template<class T>int trans(int x,T work){
        int m=1,l=0,r=n,mid;
        for(;l<r;){
            pushdown(m);
            if((mid=(l+r)>>1)<x){
                l=mid+1;
                m=m<<1|1;
            }else{
                work(m<<1|1);
                r=mid;
                m<<=1;
            }
        }
        return(m);
    }
    void plus(int x,int t){
        if(x>n) return;
        int m=trans(x,[&](int x){a[x]+=t;});
        a[m]+=t;
        pushup(m>>1);
    }
    int& operator[](int x){
        return(a[trans(x,[](int){})].a);
    }
    void tag(int x,int t){
        int m=trans(x,[](int){});
        a[m]=t;
        pushup(m>>1);
    }
    int query(int x){
        int re=INF;
        return(min(re,a[trans(x,[&](int x){re=min(re,a[x].mi);})].a));
    }
};
ST<node0> in,out;
ST<node1> mx0,mx1;
char BuF[FSIZE],*InF=BuF;
template<typename T>void read(T &x){
    bool f=1;
    for(;48>*InF||*InF>57;f^=*InF++=='-');
    for(x=0;47<*InF&&*InF<58;x=x*10+(*InF++^48));
    x=f?x:-x;
}
bool solve(candy x){
    int g=lf[x.x],bk=c[g].back();
    return((x.x-1)<<1>=(x.t?in:out)[x.p]+(x.d>>1)&&mx0.query(x.p+!x.t)>=x.d&&
        (a[x.x]>1||out[g]<=((bk-1)<<1)-g+bk)&&mx1.query(x.p)>=x.d);
}
int main(){
    fread(BuF,1,FSIZE,stdin);
    read(n);
    l[0]=-INF;
    for(int i=1;i<=n;++i){
        read(a[i]);
        if(~a[i]) ans+=a[i];
        lf[i]=max(l[i]=~a[i]?l[i-1]:i,0);
        if(a[i]>0){
            s[lf[i]]+=a[i];
            c[lf[i]].push_back(i);
        }
        out[i]=in[i]=i-1;
        mx0[i]=INF;
    }
    r[n+1]=INF;
    for(int i=n;i;--i) r[i]=~a[i]?r[i+1]:i;
    for(int i=1;i<=n;++i){
        sort(c[i].begin(),c[i].end());
        mx1.tag(i,~a[i]||r[i+1]==INF||c[i].empty()?INF:((c[i].back()-1)<<1)+i-c[i].back()-out[i]);
        if(a[i]>0)
            v.push_back({min(i-l[i],r[i]-i)<<1,i,i-l[i]>r[i]-i,(i-l[i]>r[i]-i?r:l)[i]});
    }
    sort(v.begin(),v.end(),[](candy a,candy b){return(a.d<b.d);});
    for(auto i:v)
        for(int g;a[i.x];--s[g],--ans)
            if((s[g=lf[i.x]]>1||r[i.x]==INF)&&solve(i)){
                auto &bk=c[g];
                if(!--a[i.x]&&bk.back()==i.x&&r[i.x]<INF){
                    bk.pop_back();
                    mx1.tag(g,((bk.back()-1)<<1)+g-bk.back()-out[g]);
                }
                int p=min(INF,mx0[i.p]),s=((i.x-1)<<1)-(i.d>>1);
                mx0.tag(i.p,i.t?min(s-in[i.p],p-i.d):min(s-out[i.p],p));
                in.plus(i.p+1,i.d);
                mx0.plus(i.p+1,-i.d);
                out.plus(i.p,i.d);
                mx1.plus(i.p,-i.d);
            }else break;
    for(int i=1;i<=n;++i) ans-=i==r[i]&&s[lf[i-1]]>0;
    printf("%lld\n",ans);
    fclose(stdin);
    fclose(stdout);
    return(0);
}
```

## 做法二

我们发现可以按照区块顺序从前往后扫，然后对块内按照上述处理糖果。

这样就无需处理跨块的时间贡献了，使用可撤销贪心维护一个堆就没了。

代码没写，感觉很好写。

---

