# Ciel and Duel

## 题目描述

Fox Ciel is playing a card game with her friend Jiro.

Jiro has $ n $ cards, each one has two attributes: $ position $ (Attack or Defense) and $ strength $ . Fox Ciel has $ m $ cards, each one has these two attributes too. It's known that position of all Ciel's cards is Attack.

Now is Ciel's battle phase, Ciel can do the following operation many times:

1. Choose one of her cards $ X $ . This card mustn't be chosen before.
2. If Jiro has no alive cards at that moment, he gets the damage equal to ( $ X $ 's strength). Otherwise, Ciel needs to choose one Jiro's alive card $ Y $ , then: 
  - If $ Y $ 's position is Attack, then ( $ X $ 's strength) $ >= $ ( $ Y $ 's strength) must hold. After this attack, card $ Y $ dies, and Jiro gets the damage equal to ( $ X $ 's strength) - ( $ Y $ 's strength).
  - If $ Y $ 's position is Defense, then ( $ X $ 's strength) $ &gt; $ ( $ Y $ 's strength) must hold. After this attack, card $ Y $ dies, but Jiro gets no damage.

Ciel can end her battle phase at any moment (so, she can use not all her cards). Help the Fox to calculate the maximal sum of damage Jiro can get.

## 说明/提示

In the first test case, Ciel has 3 cards with same $ strength $ . The best strategy is as follows. First she uses one of these 3 cards to attack "ATK 2000" card first, this attack destroys that card and Jiro gets $ 2500-2000=500 $ damage. Then she uses the second card to destroy the "DEF 1700" card. Jiro doesn't get damage that time. Now Jiro has no cards so she can use the third card to attack and Jiro gets $ 2500 $ damage. So the answer is $ 500+2500=3000 $ .

In the second test case, she should use the "1001" card to attack the "ATK 100" card, then use the "101" card to attack the "ATK 10" card. Now Ciel still has cards but she can choose to end her battle phase. The total damage equals $ (1001-100)+(101-10)=992 $ .

In the third test case note that she can destroy the "ATK 0" card by a card with strength equal to 0, but she can't destroy a "DEF 0" card with that card.

## 样例 #1

### 输入

```
2 3
ATK 2000
DEF 1700
2500
2500
2500
```

### 输出

```
3000
```

## 样例 #2

### 输入

```
3 4
ATK 10
ATK 100
ATK 1000
1
11
101
1001
```

### 输出

```
992
```

## 样例 #3

### 输入

```
2 4
DEF 0
ATK 0
0
0
1
1
```

### 输出

```
1
```

# 题解

## 作者：Rbu_nas (赞：3)

[题目大意](https://www.luogu.org/problem/CF321B)

这道题目难处理的是我方的牌可以打完，也可以不打完，并且由样例二可以发现并不是出数值相近的牌就能赢，很像是 dp （事实上也是）

那到底如何出牌才能收益最大呢？考虑全两种情况：打完自己的牌、不打完自己的牌。

---

_策略一：打爆对方所有牌_

那么很明显此时先攻击 DEF 更优。因为我们期望的是打完所有牌，如果自己还有剩余直接构成真伤。

如果先攻击 ATK 很可能出现打不动 DEF 的尴尬局面。所以我们每次找与对方 DEF 最接近的牌打出，然后再找和对方 ATK 最相近的牌打。最后，如果还有剩余直接累加答案就好了。

为什么找和对方 ATK 最接近的牌打呢？貌似拿自己最大的打别人最小的更划算啊 其实，这就是我们的另一种策略了。因为不打完自己的所有牌，那就必须让打出的牌造成的伤害最大嘛

_策略二：中途退出_

这种策略下我们不打 DEF，因为要把牌都留着打 ATK。而且如果想着造成 ATK 伤害最大下同时试着打完 DEF 再造成真伤，就是策略一策略二两头都没顾着了，很容易被 hack

---

通过简述两种情况下的策略，我们很容易发现它们都能被 hack。

犹豫不定，想打完所有牌可见样例二

每次选最大打最小，容易构造：

```
3 4
ATK 1
ATK 2
ATK 3
4 3 2 2
```

所以，我们要考虑全两种情况，把两种贪心策略中择优啊

当然，dp 和 最小费用最大流都可做，可以参考 CF 的官方题解。

本题还有的坑点是力量值是非负的，初值要设为 `-1`


code :

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 100003;

int n, m;

int totAtk, totDef;
int xAtk[N];
int yAtk[N], yDef[N];

//totAtk totDef为对方手中ATK与DEF的数目，便于排序
//xAtk[]是我方卡牌数组
//yAtk[] yDef[]是对方卡牌数组

int copy_xAtk[N];
int copy_yAtk[N], copy_yDef[N];

//这里有上述三个数组的备份
//为了防止做完一种策略对后面策略中数组的影响

//rush便是打完所有牌的策略
inline LL rush(int *xAtk, int *yAtk, int *yDef)
{
    LL ret = 0;
    sort(xAtk + 1, xAtk + m + 1);
    sort(yDef + 1, yDef + totDef + 1);
    sort(yAtk + 1, yAtk + totAtk + 1);
    //先进行排序，然后找出与DEF相近的牌打
    
    for(register int i = 1; i <= totDef; ++i)
    {
        int P = upper_bound(xAtk + 1, xAtk + m + 1, yDef[i]) - xAtk;
        if(xAtk[P] < yDef[i]) return 0;
        //如果连DEF都还不能打完，那么这种策略收益为0
        
        xAtk[P] = -1; yDef[i] = -1;
    }
    sort(xAtk + 1, xAtk + m + 1);
    //注意这里要重新排序!数组的值发生了变化
    
    for(register int i = 1; i <= totAtk; ++i)
    {
        int P = lower_bound(xAtk + 1, xAtk + m + 1, yAtk[i]) - xAtk;
        if(xAtk[P] < yAtk[i] || xAtk[P] == -1 || yAtk[i] == -1) return ret;
        //如果打不动ATK了，只能删库带着收益跑路了
        
        ret += xAtk[P] - yAtk[i];
        xAtk[P] = -1; yAtk[i] = -1;
    }

    for(register int i = 1; i <= m; ++i) if(xAtk[i] != -1) ret += xAtk[i];
    //康康还有没有真伤qwq
    
    return ret;
}

//策略二，把大牌直接炸出去
inline LL blow(int *xAtk, int *yAtk, int *yDef)
{
    LL ret = 0;
    sort(xAtk + 1, xAtk + m + 1);
    sort(yAtk + 1, yAtk + totAtk + 1);
    
    //这里的变量条件的意思是
    //如果我的牌还没打完，就继续循环
    //因为可能还有DEF，所以这里不累计真伤
    //对方牌值-1就是没ATK牌了
    for(register int i = m, j = 1; i >= 1; --i, ++j)
        if(xAtk[i] >= yAtk[j])
        {
            if(yAtk[j] != -1)
            {
                ret += xAtk[i] - yAtk[j];
                xAtk[i] = -1; yAtk[j] = -1;
            }
        }
    return ret;
}

signed main()
{
    scanf("%d%d", &n, &m);
    char str[7];
    //设初值
    
    memset(xAtk, -1, sizeof(xAtk));
    memset(yAtk, -1, sizeof(yAtk));
    memset(yDef, -1, sizeof(yDef));
    memset(copy_xAtk, -1, sizeof(copy_xAtk));
	memset(copy_yAtk, -1, sizeof(copy_yAtk));
	memset(copy_yDef, -1, sizeof(copy_yDef));

    for(register int i = 1; i <= n; ++i)
    {
        scanf("%s", str);
        if(str[0] == 'A')
        {
        	++totAtk;
            scanf("%d", &yAtk[totAtk]);
        }
        else
        {
        	++totDef;
            scanf("%d", &yDef[totDef]);
        }
    }
    for(register int i = 1; i <= m; ++i) scanf("%d", &xAtk[i]), copy_xAtk[i] = xAtk[i];
    for(register int i = 1; i <= totAtk; ++i) copy_yAtk[i] = yAtk[i];
    for(register int i = 1; i <= totDef; ++i) copy_yDef[i] = yDef[i];
    printf("%lld", max( rush(xAtk, yAtk, yDef), blow(copy_xAtk, copy_yAtk, copy_yDef) ));
    //两种策略择优输出。
    return 0;
}

```

---

## 作者：XXh0919 (赞：2)

好久没写题解了，今天来写一发。

### 正文

比较简单的贪心。

我们可以分两种情况讨论。第一种，不打对方的 DEF 牌，用自己的牌去攻击对方较小的 ATK 牌。毕竟用自己的牌去攻击对方的 DEF 牌显然对自己不利，因为无法对对方造成伤害，自己还要丢牌。第二种，用自己较小的牌消耗完对方的牌，然后用自己剩下的的牌对对方贴脸开大。这样就可以保证伤害为最大。最终答案即为两种情况的最大值。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define pi pair<int,int>
#define mkp(a,b) make_pair((a),(b)) 
#define IOS ios::sync_with_stdio(0)
using namespace std;
const int N=3e6+15;

int n,m;
int atk[N],def[N],a,d;
char s[7];
int ciel[N];
bool f[N];

int f1(){
	int ans=0;
	int tot1=m,tot2=1;
	while(ciel[tot1]>=atk[tot2]&&tot1>0&&tot2<=a){//不消耗对方的 DEF 牌
		ans+=ciel[tot1]-atk[tot2];//计算伤害
		--tot1;++tot2;
	}
	return ans;
}

int f2(){
	int ans=0,tot1=1;
	bool ff=1;
	rep(tot2,1,d){
		while((ciel[tot1]<=def[tot2]||f[tot1])&&tot1<=m)++tot1;//磨完对方的 DEF 牌
		if(tot1==m+1){//磨不完
			memset(f,0,sizeof f);//那就把牌留着
			ff=0;
			break;
		}
		f[tot1]=1;//用掉一张
	}
	tot1=1;
	rep(tot2,1,a){
		while((ciel[tot1]<atk[tot2]||f[tot1])&&tot1<=m)++tot1;//开始攻击
		if(tot1==m+1){
			return ans;
		}
		ans+=ciel[tot1]-atk[tot2];
		f[tot1]=1;//用掉一张
	}
	if(ff){//对方没牌
		rep(i,1,m){
			if(!f[i]){
				ans+=ciel[i];//贴脸开大
			}
		}
	}
	return ans;
}

signed main(){
	scanf("%lld%lld",&n,&m);
	int k;
	rep(i,1,n){
		scanf("%s%lld",s,&k);
		if(s[0]=='A')atk[++a]=k;
		else def[++d]=k;
	}
	rep(i,1,m){
		scanf("%lld",&ciel[i]);
	}
	sort(ciel+1,ciel+m+1);
	sort(atk+1,atk+a+1);
	sort(def+1,def+d+1);
	int ans1=f1(),ans2=f2();
	printf("%lld\n",max(ans1,ans2));//最大值
	return 0;
}
```

---

## 作者：火羽白日生 (赞：1)

> 每张卡牌有类型（攻击或防御）和力量值两个信息。$\texttt J$ 有 $n$ 张卡牌，$\texttt C$ 有 $m$ 张卡牌。已知 $\texttt C$ 的卡牌全是攻击型的。

>游戏的每一轮都由 $C$ 进行操作，首先从自己手上选择一张没有使用过的卡牌 $X$。

>如果 $\texttt J$ 手上没有卡牌，受到的伤害为 $X$ 的力量值，否则 $\texttt C$ 要从 $\texttt J$ 的手上选择一张卡牌 $Y$ 。

>若 $Y$ 是攻击型（当 $X$ 的力量值不小于 $Y$ 的力量值时才可选择），此轮结束后 $Y$ 消失，$\texttt J$ 受到的伤害为 $X$ 的力量值与 $Y$ 的力量值的差；若 $Y$ 是防御型（当 $X$ 的力量值大于 $Y$ 的力量值时才可选择），此轮结束后 $Y$ 消失，$\texttt J$ 不受到伤害。

>$\texttt C$ 可以随时结束自己的操作（卡牌不一定要用完）。她想使得 $\texttt J$ 受到的总伤害最大。

考虑贪心，不难想到有两种打法：

* $\texttt C$ 尽量用力量值大的牌去打 $\texttt J$ 力量值小的牌，然后结束游戏。

* $\texttt C$ 用最小的代价将 $\texttt J$ 防御型牌全都打完后，再用最小代价将 $\texttt J$ 攻击型牌全部打完，最后直接贴脸打 $\texttt J$。

但是两种打法都能构造出数据 Hack 掉，那么就把两种打法都跑一遍然后取最大值（简单粗暴）。

$\texttt{Code}:$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rint register int
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout);
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x){
  		static int sta[35]; int top=0;
  		do{sta[++top]=x%10,x/=10;}while(x);
  		while(top) putchar(sta[top--]+48); puts("");
	}
}
using namespace IO;
namespace CL{
	#define fill(x,y) memset(x,y,sizeof(x))
	#define copy(x,y) memcpy(y,x,sizeof(x))
	
	const int maxn=105;
	
	int n,m,totatk,totdef;
	int Jatk[maxn],Jdef[maxn],atk[maxn];
	bool used[maxn];
	inline int work1(){
		int res=0,p=1;
		sort(atk+1,atk+1+m,greater<int>());
		for(int i=1;i<=m;i++)
			if(atk[i]>=Jatk[p] && Jatk[p]!=-1)
				res+=atk[i]-Jatk[p],p++;
		return res;
	}// all in atk
	inline int work2(){
		int res=0,p1=1; bool check=1;
		sort(atk+1,atk+1+m);
		for(int p2=1;p2<=totdef;p2++){
			while((atk[p1]<=Jdef[p2] || used[p1]) && p1<=m) p1++;
			if(p1==m+1){
				fill(used,0); check=0;
				break;
			}
			used[p1]=1;
		}
		p1=1;
		for(int p2=1;p2<=totatk;p2++){
			while((atk[p1]<Jatk[p2] || used[p1]) && p1<=m) p1++;
			if(p1==m+1) return res;
			res+=atk[p1]-Jatk[p2];
			used[p1]=1;
		}
		if(check) 
			for(int i=1;i<=m;i++)
				if(!used[i]) res+=atk[i];
		return res;
	}// atack def first then all in atk & real_atk
	
	inline int main(){
		n=read(); m=read();
		fill(Jatk,-1); fill(Jdef,-1); fill(atk,-1);
		for(int i=1;i<=n;i++){
			char op; cin>>op;
			if(op=='A') Jatk[++totatk]=read();
			if(op=='D') Jdef[++totdef]=read();
		}
		for(int i=1;i<=m;i++) atk[i]=read();
		sort(Jatk+1,Jatk+1+totatk);
		sort(Jdef+1,Jdef+1+totdef);
		int ans1=work1(),ans2=work2();
		printf("%d\n",max(ans1,ans2));	
		return 0;
	}
}
signed main(){return CL::main();}
```

---

## 作者：eee_hoho (赞：0)

好多做法啊，来一发费用流吧QAQ

对于这个题，我们会发现几个比较特殊的点：

1. $Ciel$可以选择随时结束操作。

2. 当$Juro$没有牌之后，$Ciel$可以把自己剩下的牌全打上去。

第一个操作考虑直接枚举打了几张牌，多建一个点连向源点限制流量就可以。

重点是第二个操作，可以考虑把$Juro$的牌拆成两个点$i,i'$。

- $i\to i'$流量$1$，费用$-2inf$；

- $i\to T'$，流量$1$，费用$0$；

用$j$表示$Ciel$的牌。

- $S\to j$，流量$1$，费用$0$；

- $j\to i(k_i=ATK,X_j\le Y_i)$，流量$1$，费用$inf-(X_j-Y_i)$；

- $j\to i(k_i=DEF,X_j>Y_i)$，流量$1$，费用$inf$；

- $j\to T$，流量$1$，费用$inf-X_j$。

这样子为什么是对的？

注意那条费用为$-2inf$的边，因为我们跑最小费用最大流，所以我们肯定会优先流完那些边，才会流$inf-X_j$的边，这样子保证了先把$Juro$的牌打完才能打剩下的牌。

而我们之前多枚举了打几张牌$x$，所以我们可以很容易通过最小费用还原伤害，最后建个这样的边：

- $SS\to S$，流量$x$，费用$0$。

画出图来就是这样子的：

![](https://cdn.luogu.com.cn/upload/image_hosting/vq1b3t62.png)

**Code**
``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N = 100;
const int M = 1e6;
const int inf = 1e7;
const int INF = 2e9;
using namespace std;
struct card
{
    int typ,v;
}a[N + 5];
int n,m,b[N + 5],s,ss,t,nxt[M * 2 + 5],head[M + 5],edge_cnt = 1,chi,cost,ans,ress,cur[M + 5],dis[M + 5],vis[M + 5],p[M + 5],q[M + 5];
struct edges
{
    int v,w,f;
}edge[M * 2 + 5],e[M * 2 + 5];
char ch[10];
void add_edge(int u,int v,int w,int f)
{
    edge[++edge_cnt] = (edges){v,w,f};
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}
bool spfa(int s,int t)
{
    for (int i = 1;i <= t;i++)
    {
        cur[i] = head[i];
        dis[i] = INF;
        p[i] = 0;
        vis[i] = 0;
    }
    int l = 1,r = 0;
    dis[s] = 0;
    q[++r] = s;
    vis[s] = 1;
    while (l <= r)
    {
        int u = q[l++];
        vis[u] = 0;
        for (int i = head[u];i;i = nxt[i])
        {
            int v = edge[i].v,w = edge[i].w,f = edge[i].f;
            if (dis[u] + f < dis[v] && w)
            {
                dis[v] = dis[u] + f;
                if (!vis[v])
                {
                    vis[v] = 1;
                    q[++r] = v;
                }
            }
        }
    }
    return dis[t] != INF;
}
int dfs(int u,int flow)
{
    if (u == t)
        return flow;
    int sm = 0;
    p[u] = 1;
    for (int &i = cur[u];i;i = nxt[i])
    {
        int v = edge[i].v,&w = edge[i].w,f = edge[i].f;
        if (dis[u] + f == dis[v] && w && !p[v])
        {
            int res = dfs(v,min(w,flow));
            w -= res;
            sm += res;
            flow -= res;
            edge[i ^ 1].w += res;
            cost += f * res;
            if (!flow)
                break;
        }
    }
    return sm;
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i = 1;i <= n;i++)
    {
        scanf("%s",ch + 1);
        scanf("%d",&a[i].v);
        if (ch[1] == 'A')
            a[i].typ = 1;
        else
            a[i].typ = 2;
    }
    for (int i = 1;i <= m;i++)
        scanf("%d",&b[i]);
    s = n * 2 + m + 1,ss = n * 2 + m + 2,t = n * 2 + m + 3;
    for (int i = 1;i <= m;i++)
    {
        add_edge(ss,n * 2 + i,1,0);
        add_edge(n * 2 + i,ss,0,0);
        add_edge(n * 2 + i,t,1,inf - b[i]);
        add_edge(t,n * 2 + i,0,b[i] - inf);
    }
    for (int i = 1;i <= n;i++)
    {
        add_edge(i,i + n,1,-2 * inf);
        add_edge(i + n,i,0,2 * inf);
        add_edge(i + n,t,1,0);
        add_edge(t,i + n,0,0);
        for (int j = 1;j <= m;j++)
        {
            if (a[i].typ == 1 && b[j] >= a[i].v)
            {
                add_edge(n * 2 + j,i,1,inf - (b[j] - a[i].v));
                add_edge(i,n * 2 + j,0,b[j] - a[i].v - inf);
            }
            if (a[i].typ == 2 && b[j] > a[i].v)
            {
                add_edge(n * 2 + j,i,1,inf);
                add_edge(i,n * 2 + j,0,-inf);
            }
        }
    }
    add_edge(s,ss,0,0);
    chi = edge_cnt;
    add_edge(ss,s,0,0);
    for (int i = 2;i <= edge_cnt;i++)
        e[i] = edge[i];
    for (int i = 1;i <= m;i++)
    {
        e[chi].w = i;
        for (int j = 2;j <= edge_cnt;j++)
            edge[j] = e[j];
        cost = 0;
        while (spfa(s,t))
            ress += dfs(s,inf);
        //cout<<i<<" "<<cost<<" "<<-(inf * min(n,i) - inf * max(i - n,0) + cost)<<endl;
        ans = max(ans,-(inf * min(n,i) - inf * max(i - n,0) + cost));
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：_Qer (赞：0)

贪心。考虑两种决策方式：  
1. 不将对方手牌打完，也就是尽量用自己大的牌攻击对方小的ATK，不动对方的DEF（显然攻击DEF不优），直到自己无法攻击对方   
2. 消耗完对方手牌，然后剩下的直接骑脸造成真伤，也就是用自己的尽量小的牌换掉对方的DEF，然后用数值相近的牌攻击对方的ATK，最后剩下的骑脸 

如果单独使用其中任意一种，都可能无法得到最优解，但当我们把两种方案综合起来，各跑一遍然后取更优的解法就可以水过去了。

最后，要注意数据范围，开上$long\ long$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL long long
const int maxn = 100000 + 10;
int n, m, ca, cd;
//ca为atk牌数，cd为def牌数
LL a[maxn], atk[maxn], def[maxn];
//a为小X手牌，其余如题
bool used[maxn];
//方案2中用于记录小X的手牌是否使用
char t[10];
LL solve1() {//方案1 
	LL sum = 0;
	int p1 = m, p2 = 1;//注意枚举顺序
	while (a[p1] >= atk[p2] && p1 > 0 && p2 <= ca) {
		sum += a[p1] - atk[p2];
		--p1, ++p2;
	}
	return sum;
}
LL solve2() {//方案2 
	LL sum = 0;
	int p1 = 1;
	bool b = true;//记录是否能消耗完对方手牌
	for (int p2 = 1; p2 <= cd; ++p2) {
		while ((a[p1] <= def[p2] || used[p1]) && p1 <= m) {
			++p1;
		}
		if (p1 == m + 1) {
			b = false;
			memset(used, false, sizeof(used));
            		//消耗不完对方的DEF，可以将自己的牌留着
			break;
		}
		used[p1] = true;
	}
	p1 = 1;
	for (int p2 = 1; p2 <= ca; ++p2) {
		while ((a[p1] < atk[p2] || used[p1]) && p1 <= m) {
			++p1;
		}
		if (p1 == m + 1) {
			return sum;
		}
		sum += a[p1] - atk[p2];
		used[p1] = true;
	}
	if (b)
	for (int i = 1; i <= m; ++i) {
		if (!used[i]) {
			sum += a[i];
            		//多余的牌骑脸
		}
	}
	return sum;
}
int main() {
	scanf("%d%d", &n, &m);
	LL x;
	for (int i = 1; i <= n; ++i) {
		scanf("%s%lld", t, &x);
		if (t[0] == 'A') {
			atk[++ca] = x;
		} else {
			def[++cd] = x;
		}
	}
	for (int i = 1; i <= m; ++i) {
		scanf("%lld", &a[i]);
	}
    	//先排序方便后面做
	sort(a + 1, a + m + 1);
	sort(atk + 1, atk + ca + 1);
	sort(def + 1, def + cd + 1);
	cout << max(solve1(), solve2()) << endl;
	return 0;
}
```

---

