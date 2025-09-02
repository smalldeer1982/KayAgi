# [USACO13DEC] The Bessie Shuffle G

## 题目描述

Bessie is practicing her card tricks.  She has already mastered the Bessie- shuffle -- a shuffle on M (2 <= M <= 100,000) cards that reorganizes the cards so the i-th card from the top is now the P[i]-th card from the top.

Now Bessie is practicing shuffles on larger decks.  She has a deck of N cards (M <= N <= 1,000,000,000) conveniently labeled 1 to N.  She shuffles this deck by taking the first M cards and performing the Bessie-shuffle on them, placing the shuffled cards back on top of the deck.  She then removes the top card from the deck and places it face down.  She repeats this process, placing the top cards successively on top of each other, until she is out of cards.  When Bessie has less than M cards left, she no longer performs the Bessie-shuffle, but continues to place the top card on top of the others.

Bessie knows that the deck initially started in sorted order, with 1 on top, 2 next, and N on the bottom.  Given the description of the Bessie-shuffle, help Bessie compute which cards end up located at Q different specified positions (1 <= Q <= N, Q <= 5,000) in the deck.

50% of test cases will have N <= 100,000. 

贝西有一种独门的洗牌方法，称为 A 类洗牌法；

A 类洗牌法的具体过程：将一堆共 $M$（$2 \le M \le 10 ^ 5$）张从上到下编号 $1, 2, \cdots, M$ 的纸牌，从上到下第 $i$ 张牌洗到位置 $p _ i$。

例如，$M=3，p = \{3, 1, 2\}$，则执行一次 A 类洗牌法后，从上到下将变为 $2, 3, 1$，即牌 $1$ 放到位置 $3$，牌 $2$ 放到位置 $1$，牌 $3$ 放到位置 $2$。


贝西现在要练习另外一种洗牌方法，称为 B 类洗牌法。


B 类洗牌法的具体过程： 

有一堆 $N$（$M \le N \le 10 ^ 9$）张编号为 $1, 2, \cdots, N$ 的牌，并按从上到下 $1$ 到 $N$ 的顺序堆放。另有一个牌堆用来辅助洗牌，称为临时堆，开始时为空。

1. 将最上面 $M$ 张牌进行一次 A 类洗牌法；
2. 将最上面的一张牌放到临时堆的最上方；
3. 重复前两个操作，直到原先的堆没有牌为止。


以上过程中，当原先堆的牌不足 $M$ 张的时候，将不进行 A 类洗牌法，而是将最上面的牌依次放到临时堆上。


给定 $N, M$ 和排列 $p$。现在有 $Q$（$1 \le Q \le \min(N, 5000)$）个询问，请求出对其做一次 B 类洗牌法后临时堆中 $q _ i$ 位置上的牌的编号。

$50\%$ 的数据中，$N \le 10 ^ 5$。


## 说明/提示

Bessie has a deck of 5 cards initially ordered as [1, 2, 3, 4, 5].  Her shuffle is on 3 cards and has the effect of moving the top card to the bottom.  There are 5 queries querying each position in the deck.


The shuffle proceeds as:

```plain
[1, 2, 3, 4, 5] -> [2, 3, 1, 4, 5] (put 2 face down) 
[3, 1, 4, 5] -> [1, 4, 3, 5] (put 1 face down) 
[4, 3, 5] -> [3, 5, 4] (put 3 face down) 
[5, 4] (put 5 face down) 
[4] (put 4 face down) 
```
This produces the final order of [4, 5, 3, 1, 2]

贝西的五张牌刚开始顺序为 [1, 2, 3, 4, 5]。她一次洗三张牌，效果是将第一张牌放到底部。以上五个问题询问了每一张牌的位置。


洗牌的顺序是:

```plain
[1, 2, 3, 4, 5] -> [2, 3, 1, 4, 5] (将2正面向下放置)
[3, 1, 4, 5] -> [1, 4, 3, 5] (将1正面向下放置) 
[4, 3, 5] -> [3, 5, 4] (将3正面向下放置) 
[5, 4] (将5正面向下放置) 
[4] (将4正面向下放置) 
```
这就形成了最终的顺序：[4, 5, 3, 1, 2]


## 样例 #1

### 输入

```
5 3 5 
3 
1 
2 
1 
2 
3 
4 
5 
```

### 输出

```
4 
5 
3 
1 
2 
```

# 题解

## 作者：XL4453 (赞：6)



------------
解题思路：

询问要求的是在第 $Q$ 个的是原来的第几个，那么就考虑把操作倒过来，然后求在把第 $Q$ 个移除顶部之前他是哪一个。

然后发现暴力模拟洗牌不行 （~~显然~~） ，发现关键问题在于可能这个点在区间里反复横跳了若干次。

想到用倍增来优化处理，用 $p_{ij}$ 来表示在 $2^i$ 次操作后原先在第 j 个的在哪里。 

细节上注意一开始处理的时候是自下而上的顺序，并且要考虑到向前挪了一位（要减一）。

------------

代码：

```cpp
#include<cstdio>
#include<cmath>
using namespace std;
int n,m,T,p[30][100005],x,now,sz;
int main(){
	scanf("%d%d%d",&n,&m,&T);
	for(int i=m-1;i>=0;i--){
		scanf("%d",&x);
		p[0][m-x+1]=i;
	}
	for(int i=1;i<=29;i++)
	for(int j=1;j<=m;j++)
	p[i][j]=p[i-1][p[i-1][j]];
	while(T--){
		scanf("%d",&x);
		if(x<=m)now=m-1;
		else now=x-1,x=m;
		for(int i=29;i>=0;i--){
			if(now+(1<<i)<=n&&p[i][x]){
				now+=1<<i;
				x=p[i][x];
			}
		}
		if(now<n){
			x=0;
			now++;
		}
		printf("%d\n",n-now+m-x);
	}
	return 0;
}
```


---

## 作者：Graphcity (赞：5)

发现顺推需要考虑非常多的东西，不妨来试试倒推。设 $Pre_i$ 表示现在的第 $i$ 张牌是上一轮的第 $Pre_i$ 张牌。以样例为例，$Pre_1=2,Pre_2=3,Pre_3=1$。

如果一张牌它现在是第一位（也就是要被淘汰了），那么它上一轮就在第 $Pre_1+1=3$ 位（因为上一轮也淘汰了一个，所以要加上 1），上上轮就在第 $Pre_3+1=2$ 位，以此类推，倒数第三轮它就到了第 4 位，走出了洗牌环节。再后来，每往后一轮它就会往后一位，直到第一轮洗牌完后停止。

这个东西可以用倍增来处理，设 $f(i,j)$ 表示现在在第 $i$ 位的牌往后 $2^j$ 轮后的位置。特别地，$f(i,j)=m+1$ 表示它走出了洗牌环节。

这样，对于每一个询问，我们只要知道它要被淘汰时 / 到最后一轮洗牌的开始位置，再往前推，就可以得到它的初始位置。分两种情况讨论：

- 到了第一轮还没有走出洗牌，直接输出它在第一轮的位置。

- 在中间某一轮走出了洗牌，二分它走出的轮数，接着往后一步一步移就行了。

时间复杂度 $O(m\log n+q\log^2n)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,q,P[Maxn+5],Pre[Maxn+5];
int f[Maxn+5][40]; // 倍增数组

inline int Check(int x,int y,int z)
{
    if(y==z+1) return 1;
    Rof(i,30,0)
        if(y>=(1<<i)) x=f[x][i],y-=(1<<i);
    return (x==m+1);
}
inline int Count(int x)
{
    int Rnd=min(n-m,n-x); // 需要进行的轮数
    int l=1,r=Rnd+1,Start=(x<m)?m-x+1:1; // Start:开始位置
    while(l<r)
    {
        int mid=(l+r)/2;
        if(Check(Start,mid,Rnd)) r=mid;
        else l=mid+1;
    }
    if(l==Rnd+1) // 没有走出去
    {
        x=Start;
        Rof(i,30,0)
            if(Rnd>=(1<<i)) x=f[x][i],Rnd-=(1<<i);
        return Pre[x];
    }
    else return min(n,m+1+Rnd-l); // 走出去了
}

int main()
{
    n=read(),m=read(),q=read(),Pre[m+1]=m+1;
    For(i,1,m) P[i]=read(),Pre[P[i]]=i;
    For(i,1,m+1) f[i][0]=min(m+1,Pre[i]+1);
    For(j,1,30)
        For(i,1,m+1) f[i][j]=min(m+1,f[f[i][j-1]][j-1]);
    while(q--)
    {
        int x=read();
        printf("%d\n",Count(x));
    }
    return 0;
}
```

---

## 作者：littleming (赞：3)

http://www.cnblogs.com/clrs97/p/7468655.html

usaco给的题解已经把思路说出来了，但没给代码。

网上就这一个人的代码，还是挺清楚的。

我给代码加了注释，如下：

滑动窗口+倍增

复杂度（（m+q）log n）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int ch_top=1e6;
char ch[ch_top],*now_r=ch-1,*now_w=ch-1;
inline int read()
{
    while(*++now_r<'0');
    register int x=*now_r^48;
    while(*++now_r>='0')    x=(x<<1)+(x<<3)+(*now_r^48);
    return x;
}
inline void write(int x)
{
    static int ss[20];static int top;
    while(ss[++top]=x%10^48,x/=10);
    while(*++now_w=ss[top],--top);
    *++now_w='\n';
}
int n,m,q,t,sz,r;
int a[30][100008];
int main()
{
    fread(ch,1,ch_top,stdin);
    n=read();m=read();q=read();
    sz=log2(n);
    for(int i=m-1;~i;--i){
        t=read();a[0][m+1-t]=i;//如题解所说，将整个序列反过来，a[i][j]=k表示在窗口[1,m]中的j经过2^i次移动会到k，k=0表示j移动i次后已经不在窗口内（即在0位置）
    }
    for(int i=1;i<=sz;++i){
        for(int j=1;j<=m;++j){
            a[i][j]=a[i-1][a[i-1][j]];//倍增
        }
    }
    while(q--){
        t=read();
        if(t<=m){
            r=m-1;
        }
        else{
            r=t-1;
            t=m;
        }
//t表示询问的数在当前窗口所在的位置，r表示已处理的窗口的上界，r=m-1说明还没有处理任何窗口
        for(int i=sz;~i;--i){
            if(r+(1<<i)<=n&&a[i][t]){//如果能移动2^i
                t=a[i][t];
                r+=(1<<i);
            }
        }
        if(r<n){//如果r没有移动到头，则再移动一次，方便计算答案
            t=0;
            ++r;
        }
        write(n-(r-m+t));//公式自己推推
    }
    fwrite(ch,1,now_w-ch,stdout);
    return 0;
}
```

---

## 作者：FQ04gty (赞：1)


##### [原题链接](https://www.luogu.com.cn/problem/P3098)

---

考虑新牌堆位置 $Q$ 的牌 $C$。

对于每一轮洗牌，将其抽象为两步：

1. 将前 $m$ 张牌按规则转移。
2. 所有牌向前移动一位，如果移动到 $0$ 的位置，就放入新牌堆。

考虑 $C$ 遵循以上移动方式，将其从 $0$ 开始反向移动。

倍增移动即可，每一层倍增倍增的是一轮的移动。

##### 实现细节

由于 $n$ 很大，移动时应该分为两部分，即被洗牌的部分和不被洗牌的部分。被洗牌的部分坐标在 $0$ 到 $m-1$ 之间。倍增处理时将 $m$ 的 `nxt[m][0]` 设为 $m$，当倍增时遇到 $m$ 时意味着无需再洗牌了（因为在 $m$ 的位置，再向后移动一位就无需洗牌）。剩下部分倍增跳长度即可。

### Code

```cpp
#include<cstdio>
using namespace std;
typedef long long ll;
const ll SIZE=1e5+10,BIT=63;
inline ll read()
{
    ll x=0,opr=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')opr=-opr;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x*10)+(ch^48),ch=getchar();
    return x*opr;
}
ll n,m,q,p[SIZE],op[SIZE],nxt[SIZE][BIT];
inline ll min(ll x,ll y){return x<y?x:y;}
inline ll max(ll x,ll y){return x>y?x:y;}
inline ll solve(ll x)
{
    ll cnt=min(x,n-m+1),t=max(0,x-(n-m+1));
    for(ll i=BIT-1;~i;i--)if(cnt>=(1ll<<i)&&nxt[t][i]!=m)t=nxt[t][i],cnt-=(1ll<<i);
    if(!cnt)return t;
    t=m,cnt--;
    for(ll i=BIT-1;~i;i--)if(cnt>=(1ll<<i))t+=(1ll<<i),cnt-=(1ll<<i);
    return t;
}
int main()
{
    n=read(),m=read(),q=read();
    for(ll i=1;i<=m;i++)p[i]=read();
    for(ll i=1;i<=m;i++)op[p[i]]=i;
    for(ll i=0;i<m;i++)nxt[i][0]=op[i+1];
    for(ll k=0;k<BIT;k++)nxt[m][k]=m;
    for(ll k=1;k<BIT;k++)for(ll i=0;i<m;i++)nxt[i][k]=nxt[nxt[i][k-1]][k-1];
    for(ll i=1,t;i<=q;i++)
    {
        t=n-read()+1;
        printf("%lld\n",solve(t));
    }
    return 0;
}
```



---

