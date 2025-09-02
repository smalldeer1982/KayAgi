# Finding lines

## 题目描述

After some programming contest Roma decided to try himself in tourism. His home country Uzhlyandia is a Cartesian plane. He wants to walk along each of the Main Straight Lines in Uzhlyandia. It is known that each of these lines is a straight line parallel to one of the axes (i.e. it is described with the equation $ x=a $ or $ y=a $ , where $ a $ is integer called the coordinate of this line).

Roma lost his own map, so he should find out the coordinates of all lines at first. Uncle Anton agreed to help him, using the following rules:

- Initially Roma doesn't know the number of vertical and horizontal lines and their coordinates;
- Roma can announce integer coordinates of some point in Uzhlandia, and Anton then will tell him the minimum among the distances from the chosen point to each of the lines. However, since the coordinates of the lines don't exceed $ 10^{8} $ by absolute value, Roma can't choose a point with coordinates exceeding $ 10^{8} $ by absolute value.

Uncle Anton is in a hurry to the UOI (Uzhlandian Olympiad in Informatics), so he can only answer no more than $ 3·10^{5} $ questions.

The problem is that Roma doesn't know how to find out the coordinates of the lines. Write a program that plays Roma's role and finds the coordinates.

## 说明/提示

The example test is

`<br></br>1 2<br></br>2<br></br>0 -3<br></br>`The minimum distances are:

- from $ (1,2) $ to $ x=2 $ ;
- from $ (-2,-2) $ to $ y=-3 $ ;
- from $ (5,6) $ to $ x=2 $ ;
- from $ (-2,2) $ to $ y=0 $ .

## 样例 #1

### 输入

```
1
1
3
2
```

### 输出

```
0 1 2
0 -2 -2
0 5 6
0 -2 2
1 1 2
2
0 -3
```

# 题解

## 作者：whiteqwq (赞：6)

[CF788D Finding lines](https://www.luogu.com.cn/problem/CF788D)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1796002)

## 题意

有$n$条平行于$y$轴的直线$m$条平行于$x$轴的直线，你每次询问可以得到一个点距离其最近的直线距离，在不多于$3\times 10^5$次询问中你需要确定这些直线。

$1\leqslant n,m\leqslant 10^4$

## 分析

普通的交互题。

考虑这些直线都会与一三象限平分线$y=x$产生交点，我们可以在这条直线上分治确定这些交点。

具体地，我们每次处理区间$[l,r]$的时候询问$(mid,mid)$（$mid$为区间中点），如果返回值$res$为$0$那么就确定了一个交点，且继续递归$[l,mid-1]$与$[mid+1,r]$，否则递归到区间$[l,mid-res]$与$[mid+res,r]$。

这一部分的询问次数有点难分析（下面纯口胡）：考虑$solve$一个有线段的区间会在两次询问中找到某条线段，并产生$3$个区间的无用递归（原区间没有这条线段的另一个区间，以及找到这条线段后递归的两个区间），而如果某个区间没有线段，只需要一次询问就可以排除（因为会递归到两个空区间），所以询问次数有一个很松的上界为$5(n+m)$，但是实际表现甚至跑不满$3(n+m)$。

找到这些直线与$y=x$交点后，我们任取一个之前询问不在线段上的点$(no,no)$，枚举每个交点$(k,k)$，如果$(k,no)$在线段上的话就有一条$x=ans$，如果$(no,k)$在线段上的话就有一条$y=k$（注意有可能同时存在）。

这一部分的询问次数上界为$2(n+m)$。

那么总询问次数最多$7(n+m)$，似乎在CF上最多只跑到$5(n+m)$（还是小数据）。
## 代码
```
#include<stdio.h>
#include<vector>
using namespace std;
int no;
vector<int>ans,X,Y;
int ask(int x,int y){
	printf("0 %d %d\n",x,y);
	fflush(stdout);
	int res;
	scanf("%d",&res);
	return res;
}
void solve(int l,int r){
	if(l>r)
		return ;
	int mid=(l+r)>>1,res=ask(mid,mid);
	if(res==0)
		ans.push_back(mid),res=1;
	else no=mid;
	solve(l,mid-res),solve(mid+res,r);
}
int main(){
	solve(-100000000,100000000);
	for(int i=0;i<ans.size();i++){
		if(ask(ans[i],no)==0)
			X.push_back(ans[i]);
		if(ask(no,ans[i])==0)
			Y.push_back(ans[i]);
	}
	printf("1 %d %d\n",X.size(),Y.size());
	for(int i=0;i<X.size();i++)
		printf("%d%c",X[i],i==X.size()-1? '\n':' ');
	for(int i=0;i<Y.size();i++)
		printf("%d%c",Y[i],i==Y.size()-1? '\n':' ');
	return 0;
}
```

---

## 作者：素质玩家孙1超 (赞：3)

题意：（翻译有问题，范围是 $10^8$ 而不是 $10^{18}$ ）

二维平面上有共 $n+m$ 条未知的平行于坐标轴的直线。

你每次可以询问一个平面上点，交互库将返回该点与离它最近的直线之间的距离。

你要在 $3 \times 10^5$ 次询问内确定这 $n$ 条直线。

题目保证直线 $x=a$ 或者 $y=a$ 中 $|a|<=10^{8}$，你询问的点坐标也要在  $[-10^8,10^8]$  中，其中 $n,m \leq 10^4$ 。

---

一道普通的交互题。

容易想到我们应该多询问 $(a,a)$ 这样的点，然后对于回答为 $0$ 的直接问 $(a,x)$ 和 $(x,a)$ 即可确定直线（其中 $x$ 可以为一个随机值）。

设每一次询问的点为 $(now,now)$，询问的回答为 $ans$ 。

最一开始询问 $(-10^8,-10^8)$ 然后每次都把 $pos$ 加上 $ans$ ，若加上后刚好在线上则 $pos$ 加一，易知这样不会错过任意的线，但这样的询问的最坏是 $ 2 \times 10^4  \times \sqrt{2\times 10^4} +4\times 10^4$ 左右，当数据比较均匀的时候。

考虑如何优化这个东西，在加上 $ans$ 且在直线上时，我们不直接加 $1$ 而是考虑是否能加 $k$ ，若加上 $k$ 询问的 $ans$ 还是 $k$ ，则直接加 $k$，若不是则这两条线相距的 $dis < 2\times k$，则用刚才的加 $1$ 只要差不多 $\sqrt{ 2 \times k}$ 左右询问即可。

这么算总的询问次数大约 $ 2 \times 10^4  \times \sqrt{\frac{2 \times 10^4}{2\times k}} +4\times 10^4$ 在数据随机分布下，而若每两个都相差 $2\times k -1  $ 则总次数大约是 $2 \times 10^4 \times \sqrt{ 2 \times k} +4\times 10^4 $。

经测算 $k=100$ 是最优，大概不会超过 $\rm 24w$ 次，实际最多的点大概 $\rm 22w$ 左右。但事实上许多人取的 $k=1000$ 在 cf 的数据下跑得更快，因为cf中好像没有相邻线差值为 $2000$ 左右的数据，否则理论上可以被卡掉。

---

若有错误请指正，下面是核心代码:

```cpp
while(now<=1e8){//ask表示询问
	int ans=ask(now,now);
	if (!ans){
		if (now>-1e8){//rnd是一个随机值
			if (!ask(rnd,now)) b[++m]=now;
			if (!ask(now,rnd)) a[++n]=now;
		}
		if (now+100<=1e8){
			ans=ask(now+100,now+100);
			if (ans!=100) now++;
			else now+=100;
		}
		else now++;
	}
	else now+=ans;
}
```


---

## 作者：daniEl_lElE (赞：1)

考虑将横着和竖着的直线分开来考虑。显然是对称的，这边只考虑竖着的线。

考虑先找出一行使得距离上下横着的线的最小距离尽可能大，这边可以选择随机一些取最大值。设为 $qmax$。

接着，考虑分治。每次取中间点。

* 如果中间位置有线，那么在答案中加入并分治为 $[l,mid-1]$ 和 $[mid+1,r]$ 即可。
* 如果中间位置查询的结果等于 $qmax$，那么两边 $qmax$ 距离都没有线，分治为 $[l,mid-qmax]$ 和 $[mid+qmax,r]$ 即可。
* 如果中间位置查询的结果小于 $qmax$，设其为 $ans$，则左右两边 $ans$ 必定有一个有线。查询一下是哪个，分治为 $[l,mid-ans-1]$ 和 $[mid+ans+1,r]$ 即可。

对两边（横、竖）都做一遍即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
mt19937 rng(time(0));
const int mod=200000001;
vector<int> ans;
int qmax,nowy,nows;
int query(int x,int y){
	cout<<0<<" ";
	if(!nows) cout<<x<<" "<<y<<"\n";
	else cout<<y<<" "<<x<<"\n";
	fflush(stdout);
	int a; cin>>a; return a;
}
void divq(int l,int r,int pl,int pr){
	if(l>r) return ;
	int mid=(l+r)>>1;
	int ans2=query(mid,nowy);
	if(ans2==0){
		ans2=1;
		ans.push_back(mid);
		divq(l,mid-1,pl,-1);
		divq(mid+1,r,-1,pr);
		return ;
	}
	if(l==r) return ;
	if(ans2==qmax){
		divq(l,mid-qmax,pl,-1);
		divq(mid+qmax,r,-1,pr);
		return ;
	}
	else{
		int ans1=query(mid-ans2,nowy),ans3=query(mid+ans2,nowy);
		if(ans1==0&&mid-ans2>=l) ans.push_back(mid-ans2);
		if(ans3==0&&mid+ans2<=r) ans.push_back(mid+ans2);
		divq(l,mid-ans2-1,pl,-1);
		divq(mid+ans2+1,r,-1,pr);
	}
}
vector<int> solvep(){
	int maxv=0,maxx=0,maxy=0;
	for(int i=1;i<=100;i++){
		int x=rng()%mod-100000000,y=rng()%mod-100000000;
		int qq=query(x,y);
		if(qq>maxv){
			maxv=qq,maxx=x,maxy=y;
		}
	}
	int nowl=-100000000,nowr=100000000,add;
	while((add=query(nowl,maxy))>=maxv) nowl+=maxv;
	nowl+=add;
	while((add=query(nowr,maxy))>=maxv) nowr-=maxv;
	nowr-=add;
	qmax=maxv,nowy=maxy;
	ans.clear();
	divq(nowl,nowr,0,0);
	return ans;
}
signed main(){
	vector<int> v1=solvep();
	nows=1;
	vector<int> v2=solvep();
	cout<<1<<" "<<v1.size()<<" "<<v2.size()<<"\n";
	for(auto v:v1) cout<<v<<" "; cout<<"\n";
	for(auto v:v2) cout<<v<<" "; cout<<"\n";
	fflush(stdout);
	return 0;
}
```

---

## 作者：Sparkle_ZH (赞：1)

比较有意思的交互题！正解做法太神仙了，提供一种偏乱搞的解法。

已经尽可能地写得很详细了，这也大致是我的思考流程（？）

----

考虑分别处理两维的答案，比如处理与 $y$ 轴平行的直线时不希望受到 $x$ 那一维的干扰，那么一种直观的想法就是找到一个合适 $a$，划定一条基准线 $y = a$，它距离最近的给定的那些与 $x$ 轴平行的直线尽可能地远，然后在我们划定的这条线上找点询问，这样就能直接排除掉另一维的影响。

尽可能地远，具体能有多远呢？题目限定了询问的点坐标必须在 $[-10^8, 10^8]$ 之内，当然不能无限地远了，想象一下如果这些直线均匀排布，相邻两条直线间的距离只有 $2 \times 10^4$，那么我们取两条直线的正中间或者边界还是只有 $10^4$ 左右。而且，怎么找到这个合适的 $a$ 呢？

尝试一步解决，不断地随机一个点 $(x_0, y_0)$，直到 $(x_0, y_0)$ 满足它距离最近的直线大于等于设定好的一个值 $d$，这样 $y = y_0$ 和 $x = x_0$ 就直接把两个维度都解决了。$d$ 取 $9000$ 时可以在期望一百次操作以内找到这个点 $(x_0, y_0)$。

----

划好了基准线，接下来要找题目所给的直线了，比如说先到与 $y$ 轴平行的直线。这时候前面求到的基准线就有用了，考虑到 $y = y_0$ 距离最近的与 $x$ 轴平行的直线的距离在 $9000$ 以上，所以如果我们询问得到基准线上某个点 $(x, y_0)$ 的答案在 $9000$ 之内，那么说明它附近必定有一条与 $y$ 轴平行的直线。

因此我们得到了一个初步的想法：从 $(x_0, y_0)$ 开始，以 $9000$ 为单位一步一步地**跳**，比如 $(x_0, y_0) \rightarrow (x_0 + 9000, y_0) \rightarrow (x_0 + 18000, y_0)$ 这样，每跳到一个点就询问一次该点。每次遇到答案小于 $9000$ 时，就说明附近有要找的直线，可以根据距离推断出该直线的位置......吗？

这个想法很模糊，我们不知道直线是在左侧还是右侧，还可能会数不全，这是因为我们会**跳过头**。比如有三条相邻的直线 $x = 9001, x = 9002, x = 9003$，我们直接 $(0, 0) \rightarrow (9000, 0) \rightarrow (18000, 0)$，从而漏掉了中间那条直线。

我们希望时刻保持下一条直线在当前所在点的右侧，不能跳过头。直觉告诉我们，可以在每次找到一条直线后**慢下来**，把步长调小（为了不漏，其实需要直接调成 $1$），然后再一点点增大，直到某一刻询问的点的答案 $< 4500$ 且不等于到上一条直线的距离，就意味着我们找到新的直线了。

我们当然希望这个一点点增大的幅度越大越好，毕竟跳的步长越大，操作次数越少。如果我们假设上一条直线位置为 $x = x_1$，现在我们位于 $(x_1, y_0)$。第一步，当然是只能向右跳一格，不然漏了 $x = x_1 + 1$ 咋办。第二步，也只能跳一格，不然也有可能漏 $x = x_1 + 2$。如果此时还没找到新的直线，那么第三步可以直接跳两格，毕竟前两步已经判掉了 $x = x_1 + 3$；第四步直接跳四格，第五步直接跳八格，以二的次幂形式增长，直到到达了 $d = 9000$ 的上界为止，就接着按照 $9000$ 的步长正常跳。

这样，就能求出 $(x_0, y_0)$ 右侧的所有直线了，同理也可以求出上侧下侧左侧的直线。分析一下操作次数，$\frac{4 \times 10^8}{d} + n \log d$ 大概在 $2 \times 10^5$ 左右，可能再带点常数......然后就被卡了。

---

还得优化。发现上文中最耗操作次数的部分其实就是 $n \log d$ 那部分，而感性理解一下，大部分情况下相邻直线的距离肯定不会太近，找到一条直线后直接把步长调成 $1$ 其实是非常愚蠢的，会浪费很多操作次数。但是又不能调成更高，不然只要数据中存在两条相邻距离为 $1$ 的直线就寄了。怎么办呢？

结合一下两种思路，我们在调步长前先**试探一下**。比如上一条直线是 $x = x_1$，现在我们位于 $(x_1, y_0)$，那么我们先询问一次 $(x_1 + 9000, y_0)$，如果答案大于等于 $9000$，那么说明 $(x_1, x_1 + 9000]$ 里根本没有直线，这时候不用调步长继续向前跳就行；反之，我们再回到 $(x_1, y_0)$，把步长调为 $1$，再一步步询问 $(x_1 + 1, y_0), (x_1 + 2, y_0), ...,(x_1 + 2^k, y_0)$。

其实可以再试探一次。假如 $(x_1 + 9000, y_0)$ 的答案小于 $9000$，那就再同理试探一步 $(x_1 + 100, y_0)$，如果没有直线就把步长调为 $100$ 就够了，然后继续翻倍增长到 $9000$；否则才调成 $1$。这两次试探非常巧妙，以 $2n$ 次操作的代价换来了 $n \log d$ 部分的极小常数。

从而，我们解决了本题，大部分测试点的操作次数甚至不到 $5 \times 10 ^ 4$ 次，最劣点也没有超过 $2 \times 10 ^ 5$。通过计算或许可以得到该做法的严格操作次数上界，我相信应该也是在题目限制之内的。

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
有一个平面，上面有一些水平或竖直的直线.  
你每次可以选择一个点，询问**距离该点最近的直线到该点的距离**.  
请求出所有的直线的横/纵坐标.  
总直线数不超过 $10^4$.  
坐标范围不超过 $10^8$.（询问的点也不能超过该范围）
## $\text{Solution}$
思路很妙的一道题.  
不难想到利用 **分治**.  
如何设计分治状态是本题的关键.  
第一感似乎是设计 $solve(x1,x2,y1,y2)$ 表示寻找横坐标在 $(x1,x2)$ 和纵坐标在 $(y1,y2)$ 的直线，然后找到这个矩形的中点尝试.  
但是这样分治的两个子结构**不互相独立**，左边找到的直线也会影响右边，难以处理.  
~~别问我为什么知道难以处理~~  
所以我们要尝试一些特别的设计.  
设计 $solve(l,r)$ 表示解决坐标在 $(l,r)$ 的直线（同时包括横纵坐标）.  
询问中点 $(mid,mid)$ .  
1. 若距离为 $0$，说明有线经过该点，记录该位置并递归 $solve(l,mid-1),solve(mid+1,r)$
2. 若距离为 $d\ne0$，递归 $solve(l,mid-d),solve(mid+d,r)$  

最后，我们需要确定步骤一中得到的位置 $(p,p)$ 经过的是竖线还是横线，记录之前任何一次询问不在线上的点的坐标为 $(no,no)$，分别询问 $(no,p)$ 和 $(p,no)$ 即可.
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define double long double 
#define ull unsigned long long
//#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=1e5+100;
const double eps=1e-12;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,k;
int pl[N],tot;
int no;
int X[N],xx,Y[N],yy;
int o=1e8;
int debug(0);
void solve(int l,int r){
  if(debug)  printf("solve:(%d %d)\n",l,r);
  if(l>r) return;
  int mid=(l+r)/2;  
  printf("0 %d %d\n",mid,mid);fflush(stdout);
  int d=read();
  if(d==0){
    if(debug) printf("  ok\n");
    pl[++tot]=mid;
    solve(l,mid-1);
    solve(mid+1,r);
  }
  else{
    no=mid;
    if(debug) printf("  ??\n");
    solve(l,mid-d);solve(mid+d,r);
  }
  return;
}
signed main(){
#ifndef ONLINE_JUDGE
  //freopen("a.in","r",stdin);
  //freopen("a.out","w",stdout);
#endif
  solve(-o,o);
  if(debug) printf("tot=%d no=%d\n",tot,no);
  for(int i=1;i<=tot;i++){
    int p=pl[i];
    printf("0 %d %d\n",no,p);fflush(stdout);
    if(!read()) Y[++yy]=p;    
    printf("0 %d %d\n",p,no);fflush(stdout);
    if(!read()) X[++xx]=p;
  }
  printf("1 %d %d\n",xx,yy);
  for(int i=1;i<=xx;i++) printf("%d ",X[i]);
  putchar('\n');
  for(int i=1;i<=yy;i++) printf("%d ",Y[i]);
  return 0;
}
/*

*/

```


---

