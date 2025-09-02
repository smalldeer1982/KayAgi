# [ARC072F] Dam

## 题目描述

你负责管理一个最多能储存 $L$ 升水的水库。一开始，水库是空的。接下来 $n$ 天，第 $i$ 天早上，有 $v$ 升 $t_i$ ℃ 的水会流进来；每天晚上，你可以决定要放多少水，但你必须保证第二天水不会溢出。水不会蒸发，温度也和流进水之外的因素无关。$v_1$ 升 $t_1$ ℃ 的水与 $v_2$ 升 $t_2$ ℃ 的水混合后的温度为 $\dfrac {t_1v_1+t_2v_2}{v_1+v_2}$。对于第 $i (i \in [1,n] \cap \mathbb N)$ 天，你需要求出最后水库是满的的情况下能达到的最高水温。不同日期的答案相互独立。

## 说明/提示

- $1 \le n \le 5 \times 10^5$

- $1 \le L \le 10^9$

- $\forall i \in [1,n], 0 \le t_i \le 10^9, 1 \le v_i \le L,v_1=L$

- 所有数据都是整数。

## 样例 #1

### 输入

```
3 10
10 10
20 5
4 3```

### 输出

```
10.0000000
15.0000000
13.2000000```

## 样例 #2

### 输入

```
4 15
0 15
2 5
3 6
4 4```

### 输出

```
0.0000000
0.6666667
1.8666667
2.9333333```

## 样例 #3

### 输入

```
4 15
1000000000 15
9 5
8 6
7 4```

### 输出

```
1000000000.0000000
666666669.6666666
400000005.0000000
293333338.8666667```

# 题解

## 作者：command_block (赞：43)

**题意** ： 有个水库，最多能存 $L$ 单位水，一开始是空的。

接下来 $n$ 天，第 $i$ 天早上有 $v_i$ 单位的，水温为 $t_i$ 的水流入水库。

每天晚上你可以放掉一些水，多少自定，但必须保证第二天水库不会溢出。

现在问，对于每个 $i$ ，在使用最优放水策略的情况下，第 $i$ 天水库是满的情况下最高水温（每一问之间互相独立）。

$n \leq 5 * 10^5$，时限$\texttt{2s}$。

------------

总水温 $=$ 各部分不同温度的水的 体积$\times$温度 的和除以总量 $L$。

我们称 体积$\times$温度 为“热量”。由于体积 $L$ 一定，我们只需要最大化热量。

记 $f[i][x]$ 表示第 $i$ 天晚上，若水库内只能保留 $x$ 升水，能获得的最大热量。

若将 $f[i][x]$ 视作函数 $f_i(x)$ ，观察其性质。

若存在一组方案，容量为 $x_0$ ，热量为 $w$ ，则单纯的倒水可以得到 $y=wx/x_0\ (x\in[0,x_0])$ 这个和原点相连的线段。

此外，水变多了热量不会变少。对于 $x\geq x_0$ ，$f_i(x)\geq w$。

于是，这个函数上的任意一点，向原点的连线下方不会有函数，水平向右发射的射线下方也不会有函数。不难发现，这必然是一个**上凸壳**。

接下来，考虑凸壳 $f_{i-1}(x)$ 的转移，如图 ：

转移无非两步，第一步强制加水，第二步任意倒水。第一步可以刻画为加一个向量，第二步则向原点连线并取 $\max$。

![](https://cdn.luogu.com.cn/upload/image_hosting/yqt0ssaf.png)

其中第二步需要找到移动后的凸壳上与原点相连斜率最大的点，然后将前面的线段去掉，并将该点和原点相连。

容易使用双端队列维护凸壳，队列中装的是向量，从左到右描述相邻两个顶点的差值。

- 将凸壳 $>L-v_i$ 的部分去掉。

- 将当前向量 $(v_i,t_i)$ 放到队头。

- 若队头的向量的斜率小于下一个向量，则将两者相加。这对应下面的过程。

  ![](https://cdn.luogu.com.cn/upload/image_hosting/hdzc8m9r.png)

  不难发现，这可以实现我们想要的效果。

（需要维护各项量的和，以便回答询问）

复杂度 $O(n)$。

```cpp
#include<algorithm>
#include<cstdio>
#include<queue>
#define db double
#define MaxN 500500
using namespace std;
struct Point{db x,y;};
deque<Point> q;
int n,L;
int main()
{
  scanf("%d%d",&n,&L);
  db ans=0.0;
  for (int i=1,u,v;i<=n;i++){
    Point now;
    scanf("%lf%lf",&now.y,&now.x);
    now.y*=now.x;
    db dx=now.x;
    while(!q.empty()&&dx>1e-10)
      if (dx>q.back().x+1e-10){
        dx-=q.back().x;ans-=q.back().y;
        q.pop_back();
      }else {
        q.back().y/=q.back().x;
        ans-=q.back().y*dx;
        q.back().y*=(q.back().x-=dx);
        dx=0.0;
      }
    q.push_front(now);ans+=now.y;
    while(q.size()>1&&q[0].y/q[0].x<q[1].y/q[1].x){
      Point sav=q[0];q.pop_front();
      q[0].x+=sav.x;q[0].y+=sav.y;
    }printf("%.9f\n",ans/L);
  }return 0;
}
```

---

## 作者：Ebola (赞：21)

首先明确一点，每天的水不管你觉得它好不好，你都得接下它

假如现在需要放出x升，并且L升之前的那个水u，它后面有一个比它温度更大的水v，显然是放掉u的x升。那假如v的温度比u更小，你是选择在v进来之前放掉u的x升，还是等v进来之后再放x升呢？傻子都知道等v进来再放！根据热量守恒定理，你的总热量是不变的，而同样失去x升水，肯定放出温度小的热量损失更小。

于是我们就可以用单调递增队列来做了！队列里将最后那L升水分成若干份存储，满足温度递增，假如有哪个水的温度比前面那个小，那就把它们混合起来（直接套题目给的公式）

然后每进来一盆水就把它丢进队尾，并维护一遍单调队列，顺便计算答案。答案很好统计，只要随时记录队列中各个水的温度与体积的乘积之和，答案就用它除以L就是了

复杂度是O(n)的，瓶颈在于IO，我凭借fread/fwrite成功跑进了100ms。不过话说网上怎么搜不到浮点数快输的板子，搞得我还自己手写了一遍，嗯以后可以存着用了

```cpp
#include<bits/stdc++.h>
#define FR first
#define SE second
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}
char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
inline void printd(int d,double x)
{
    long long t=(long long)floor(x),f=t;
    while(t) qu[++qr]=t%10,t/=10;
    while(qr) putc(qu[qr--]+'0');
    putc('.');x-=f;
    while(d--)
    {
        double y=x*10;x*=10;
        int c=(int)floor(y);
        putc(c+'0');x-=c;
    }
}

typedef long long LL;
typedef pair<LL,double> pld;
const int N=500010;
LL t[N],v[N];
pld q[N];
int l=1,r=0;

int main()
{
    int n=read(),L=read();
    for(int i=1;i<=n;i++)
        t[i]=read(),v[i]=read();
    int sum=0;double cur=0;
    for(int i=1;i<=n;i++)
    {
        while(v[i]+sum>L)
        {
            int pour=min(v[i]+sum-L,q[l].FR);
            sum-=pour;
            q[l].FR-=pour;
            cur-=q[l].SE*pour;
            if(!q[l].FR) l++;
        }
        q[++r]=pld(v[i],t[i]);
        sum+=v[i];cur+=1ll*t[i]*v[i];
        while(l<r&&q[r].SE<q[r-1].SE)
        {
            q[r-1].SE=(q[r-1].SE*q[r-1].FR+q[r].SE*q[r].FR)/(q[r-1].FR+q[r].FR);
            q[r-1].FR+=q[r].FR;r--;
        }
        printd(7,cur/L);putc('\n');
    }
    flush();
    return 0;
}
```



---

## 作者：Tony102 (赞：4)

[Link](https://www.luogu.com.cn/problem/AT2402)

[更好的阅读体验](https://tony102.xyz/index.php/2020/11/26/at2402-arc072f-dam/)

墙裂推荐的好题

### Sol

首先考虑一些特殊的情况. 

假如每天流进来的水的温度都是递减的,那么我们肯定希望前面的水多一些,后面的水少一些. 

假如每天流进来的水温度都是递增的,那么相当于把递减的情况反过来,也就是选出一段后缀.但是在溢出的时候要用一个双指针来维护一下把一些水给倒掉.

现在来想想正解

有了上面两个特殊情况的启发. 在 $t_i > t_{i-1}$ 的时候我们会让他们尽可能少地混合, 要尽可能地多弄温度为 $t_i$  的水. 相反就要尽可能多地混合.

所以可以维护一个单调队列, 队列中的每个元素就是一段水混合在一起.

溢出的时候直接把队头一段温度比较小的丢掉即可. 然后把现在的水加进队列. 判一下如果 $t_{tail-1} > t_{tail}$, 那么这个水会破坏队列的单调性,就把他和 $tail-1$ 的水混在一起就可以了

中途维护一下总热量, 每次除以 $L$ 就是答案了



### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double 

const int SIZE = 5e5 + 5;

int n, L;
double t[SIZE], v[SIZE];

struct node {
	int v; double t;
} q[SIZE];

namespace ae86 {
	const int bufl = 1 << 15;
	char buf[bufl], *s = buf, *t = buf;
	inline int fetch() {
		if (s == t) { t = (s = buf) + fread(buf, 1, bufl, stdin); if (s == t) return EOF; }
		return *s++;
	}
	inline int read() {
		int a = 0, b = 1, c = fetch();
		while (!isdigit(c))b ^= c == '-', c = fetch();
		while (isdigit(c)) a = a * 10 + c - 48, c = fetch();
		return b ? a : -a;
	}
}
using ae86::read;

signed main() {
	// freopen("crescendo.in", "r", stdin);
	// freopen("crescendo.out", "w", stdout);
	n = read(), L = read();
	for (int i = 1, ti, vi; i <= n; ++ i) {
		ti = read(), vi = read();
		t[i] = ti * 1.0000, v[i] = vi * 1.0000;
	}
	int head = 1, tail = 0;
	int curV = 0; double curT = 0.00000, ans = 0.0000;
	for (int i = 1; i <= n; ++ i) {
		while (curV + v[i] > L) {
			int del = std::min(q[head].v, curV - (L - (int) v[i]));
			q[head].v -= del, curV -= del; ans -= q[head].t * del;
			if (!q[head].v) ++ head;
		}	
		curV = L, ans += t[i] * v[i];
		++ tail; q[tail].t = t[i], q[tail].v = v[i];
		while (head < tail && q[tail - 1].t > q[tail].t) {
			q[tail - 1].t =
			((q[tail - 1].v * q[tail - 1].t) + (q[tail].v * q[tail].t)) / (q[tail - 1].v += q[tail].v);
			-- tail;
		}
		printf("%.7Lf\n", ans / L);
	}
	return 0;
}
```



---

## 作者：Hadtsti (赞：3)

### 题意简述
*    给你 $n$ 杯水，第 $i$ 杯的水温为 $t_i$，容量为 $v_i$，依次倒入容量为 $V$ 的大盆。注意每次倒入水后盆内水的总体积必须恒定为 $V$，且每杯水必须全部倒入，因此为防止倒进水时溢出，在倒水之前可以从盆里往外倒出一些水。求每次倒进水后盆里水温度的最大值（每次计算时**情况独立**~~否则太简单了~~，不计倒水时的热损耗）。数据保证有解（即每次倒入水时总有办法使盆内水总体积为 $V$）。
*   $1\leq n\leq 5\times 10^5$,$1\leq V\leq 10^9,0\leq t_i\leq 10^9(1\leq i\leq n),1\leq v_i\leq V(1\leq i\leq n,v_1=V)$

### 题目分析
题意中既要按顺序倒入水又要倒出水，还要不停维护最大值，考虑到较大的数据范围，我们应使用单调队列进行求解。根据题意我们可以维护一些水的决策，具体每个决策有 $v$（体积）、$t$（温度） 两个属性值。

我们先考虑在“倒进”水之前要“倒出”的水决策。很明显它的 $t$ 一定要尽可能低，否则倒出 $t$ 更低的决策明显可以使总温度更高，因此更优。从而考虑维护 $v$ 值单调递增的单调队列。每次“倒入”水（将当前决策入队）之前，为保持总体积恒定，根据“倒入”的水的 $v$ 值不断“倒出”队头决策（出队），当队头决策无法完全“倒出”（即队头的 $v$ 过大）时仅“倒出”一部分（保留队头决策，将它的 $v$ 值减小一部分）。

然后我们再考虑倒入水的情况。首先将当前决策入队。由于当前决策的 $t$ 值可能小于原来队尾决策的 $t$ 值，违反了单调性，因此可以通过不停将原队尾与当前决策“混合”，降低队尾的 $t$ 值，直到满足单调性为止。

值得一提的是，我们与其不断计算维护总温度值，不如利用物理学概念：热量 $Q=mt$（此题中是水，我们可以姑且认为 $v$ 与 $m$ 等价），这样每次混合水的时候，可以直接得出 $Q'=Q_1+Q_2$，$v'=v_1+v_2$，温度则只需要计算 $t=\frac{Q}{m}$ （此题中也可以表示为$t=\frac{Q}{v}$），明显方便许多。
### 代码实现
```cpp
#include<bits/stdc++.h> 
using namespace std;
const double eps=1e-8;//避免浮点误差 
int n,l=1/*队首*/,r/*队尾*/;
double V/*恒定总体积*/,q1[500010]/*单调队列中每个决策的体积*/,q2[500010]/*单调队列中每个决策的热量*/;
double del/*每次倒出的水*/,a1/*倒入水的温度*/,a2/*倒入水的体积*/,sm1/*总体积*/,sm2/*总热量*/;
int main()
{
	scanf("%d%lf",&n,&V);
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf",&a1,&a2);	
		while(sm1+a2>V)//当前体积加上倒入水的体积大于恒定体积就倒出队头 
		{
			del=min(q1[l],sm1+a2-V);//倒出队头，倒不完就只倒一部分
			sm1-=del;//减去队头体积 
			sm2-=del*q2[l];//减去队头热量 
			q1[l]-=del;//队头体积减去倒掉的部分 
			if(fabs(q1[l])<eps)//如果队头倒没了就出队 
				l++;
		}
		q2[++r]=a1;
		q1[r]=a2;//倒入水，入队 
		sm1+=a2;//更新体积 
		sm2+=a2*a1;//更新热量 
		while(l<r&&q2[r-1]>q2[r])//维护单调性 
		{
			r--;
			q2[r]=(q2[r]*q1[r]+q2[r+1]*q1[r+1])/(q1[r]+q1[r+1]);//混合后的队尾温度 
			q1[r]+=q1[r+1];//混合后的体积 
		}
		printf("%.7lf\n",sm2/sm1);//热量÷质量（体积）=温度 
	}
	return 0;
}

```


~~第一次写 AT 的题解，管理大大就给过了吧~~

---

## 作者：OIerAlbedo (赞：1)



## $ \texttt{Introduction} $

一道思维题，但教练说如果不卡常没有紫题难度，这是为什么呢？

## $ \texttt{Solution} $

考虑到每次询问水的体积是固定的，我们就只要使温度 $ \times L$  的值最大即可。

问题转换到了这一步，还是很难做，那怎么办呢，我们注意到题目中的一个条件：每天早上都会有 $ v_i $ 单位，水温为 $ t_i $ 的水流进来，而这个条件恰恰是解题的关键，也就是水是一定要接的，只是倒水可以在接它之前倒好，也可以在接它之后倒好。

那么现在就有两种情况。

##### 之前的温度比这次水的温度小

那么显然把之前的水倒掉，因为加入水温度会变大，丧失同等体积水的情况下，温度低的水丧失的温度更小。

##### 之前的温度比这次水的温度大

也是同理，因为加入水后温度变小，那么一定加入以后倒。

到这里为止，我认为都没有什么思维难度，但是接下来，如何实现这个过程就有一些思维难度了，因为我们要满足加入这次的水之后，体积恰好为 $ L $ ,而这次之前，水的体积不一定要为 $ L $,这是个很难的问题，那怎么办呢，当然是看题解啦。

其实是维护一个单调队列，满足队列里温度递增，这样子每次只要取出队首，将他倒掉，使得满足当前的体积为 $ L-v_i $ ,看起来我们还是没有解决刚才的问题，但是如果我们考虑温度的混合公式，我们会发现，如果他乘上 $ L $ ，答案是一段一段的热量的相加，而会破坏这个秩序的只有倒水，如果我们把队首直接去掉，实际上就是在他倒入的时候直接去掉，而最后两个数不合并，就说明我们一定是在倒最后一次水之前将他倒了，这样子最后一次水就与前面几次倒水的贡献独立了，而如果合并，说明是倒了之后才倒水，因为我们把这两桶水捆绑了，而只有水是同一次倒的才能捆绑，至此，我们所要的操作全部实现。

## $ \texttt{Code} $

```c++
int main()
{
	//ios::sync_with_stdio(0);cin.tie();cout.tie();
    n=read();L=read();
    for (i=1;i<=n;i++) t[i]=read(),v[i]=read();
    //vol 现在的体积。 
    l=1;r=0;
    for (i=1;i<=n;i++)
        {
        	while ((v[i]+vol>L)&&(l<=r))
        	    {
        	    	lose=min(v[i]+vol-L,q[l].vol);
        	    	hq-=q[l].tmp*lose;
        	    	vol-=lose;q[l].vol-=lose;
        	    	if  (q[l].vol==0) l++;
				}
		    r++;q[r].tmp=t[i];q[r].vol=v[i];hq+=t[i]*v[i];vol+=v[i];
		    while ((l<r)&&(q[r-1].tmp>q[r].tmp))
		           {
		           	  q[r-1].tmp=(q[r-1].tmp*q[r-1].vol+q[r].tmp*q[r].vol)/(q[r-1].vol+q[r].vol);q[r-1].vol+=q[r].vol;r--;
				   }
			printf("%.7lf\n",hq/L);
		    
		}
    return 0;
}

```



---

