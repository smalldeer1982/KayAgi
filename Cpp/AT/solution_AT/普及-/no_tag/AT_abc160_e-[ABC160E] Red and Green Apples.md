# [ABC160E] Red and Green Apples

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc160/tasks/abc160_e

あなたは、$ X $ 個の赤色のリンゴと $ Y $ 個の緑色のリンゴを食べようとしています。  
 あなたは $ A $ 個の赤色のリンゴを持っており、美味しさはそれぞれ $ p_1,p_2,\ \dots\ ,p_A $ です。  
 あなたは $ B $ 個の緑色のリンゴを持っており、美味しさはそれぞれ $ q_1,q_2,\ \dots\ ,q_B $ です。  
 あなたは $ C $ 個の無色のリンゴを持っており、美味しさはそれぞれ $ r_1,r_2,\ \dots\ ,r_C $ です。  
 無色のリンゴは食べる前に着色することで、赤色のリンゴもしくは緑色のリンゴと見なすことができます。  
 以上のリンゴの中から、できるだけ美味しさの総和が大きくなるように食べるリンゴを選びます。  
 $ 0 $ 個以上の無色のリンゴに適切に着色したとき、食べる $ X+Y $ 個のリンゴの美味しさの総和が最大でいくつになるか求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ X\ \leq\ A\ \leq\ 10^5 $
- $ 1\ \leq\ Y\ \leq\ B\ \leq\ 10^5 $
- $ 1\ \leq\ C\ \leq\ 10^5 $
- $ 1\ \leq\ p_i\ \leq\ 10^9 $
- $ 1\ \leq\ q_i\ \leq\ 10^9 $
- $ 1\ \leq\ r_i\ \leq\ 10^9 $
- 入力はすべて整数である。

### Sample Explanation 1

以下のようにすることで、食べるリンゴの美味しさの総和を最大にすることができます。 - $ 2 $ 番目の赤色のリンゴを食べる。 - $ 1 $ 番目の緑色のリンゴを食べる。 - $ 1 $ 番目の無色のリンゴを緑色に着色し、食べる。

## 样例 #1

### 输入

```
1 2 2 2 1
2 4
5 1
3```

### 输出

```
12```

## 样例 #2

### 输入

```
2 2 2 2 2
8 6
9 1
2 1```

### 输出

```
25```

## 样例 #3

### 输入

```
2 2 4 4 4
11 12 13 14
21 22 23 24
1 2 3 4```

### 输出

```
74```

# 题解

## 作者：ix35 (赞：7)

对于 $A$ 个红苹果，显然只有排序后前 $X$ 个有用（不能选超过 $X$ 个）

对于 $B$ 个绿苹果，显然只有排序后前 $Y$ 个有用（不能选超过 $Y$ 个）

所以我们将 $X$ 个之后的红苹果和 $Y$ 个之后的绿苹果扔掉。

这样我们得到了 $X$ 红，$Y$ 绿和 $C$ 无色。

结论是显然的：我们将 $X+Y+C$ 个苹果放一起，排序后取前 $X+Y$ 个。

这样的最优性是显然的，为什么一定可行呢？因为已经固定颜色的红绿苹果都没有超出限制，而总数也是对的，所以总存在一种涂无色苹果的方案数，使得红绿限制都能被保证。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=100010;
int x,y,a,b,c,t,tot;
ll p[MAXN*3],q[MAXN],r[MAXN],ans;
int main () {
	scanf("%d%d%d%d%d",&x,&y,&a,&b,&c);
	for (int i=1;i<=a;i++) {
		scanf("%d",&q[i]);
	}
	sort(q+1,q+a+1);
	for (int i=a;i>=a-x+1;i--) {p[++tot]=q[i];}
	for (int i=1;i<=b;i++) {
		scanf("%d",&r[i]);
	}
	sort(r+1,r+b+1);
	for (int i=b;i>=b-y+1;i--) {p[++tot]=r[i];} 
	for (int i=1;i<=c;i++) {
		scanf("%d",&t);
		p[++tot]=t;
	}
	sort(p+1,p+tot+1);
	for (int i=tot;i>=tot-x-y+1;i--) {
		ans+=p[i];
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：oimaster (赞：3)

在我的[博客](https://oi-master.github.io/post/atcoder-abc-160-e-ti-jie/)阅读体验更好哦！

首先，感谢大佬 hhhyyyfff 和他的程序，它们开导了我的思路。好了，现在开始正题了，先讲一下题面。

## 题面
### 英文题面
请你点 [这里](https://atcoder.jp/contests/abc160/tasks/abc160_e)，会带你去 AtCoder 的官网。
### 中文题面
你们将吃 $X$ 个红苹果和 $Y$ 个青苹果。

你有 $A$ 个美味的红苹果 $p_1,p_2,...,p_A$，$B$ 个美味的青苹果 $q_1,q_2,...,q_B$ 和 $C$ 个无色美味的苹果 $r_1,r_2,...,r_C$。
在吃无色苹果之前，你可以把它涂成红色或绿色，它将分别算作红色或青色苹果。
从上面的苹果中，你可以选择要吃的苹果，同时把吃过的苹果的美味之和尽可能地做大。

找出将零个或更多无色苹果进行最佳着色时所能达到的吃掉苹果美味的最大可能总和。

输入格式大家自己看吧，我不翻译了。
## 思路
这道题比 D 题简单，不过比赛的时候没出来……其实就是一个大根堆，来维护一下所有的苹果的美味程度，同时记录下来这个苹果的颜色。然后，每次把堆顶拿出来。如果堆顶是一个红色苹果，且还没有吃到 $X$ 个红苹果，那么就吃！如果堆顶是一个青色苹果，且还没有吃到 $X$ 个青苹果，还是马上就吃！如果是一个无色的苹果，先不计数，然后将剩下的总数减掉一。当然，吃有颜色的苹果时，也要将 $X$ 或者是 $Y$ 减掉一，同时把苹果的总数也减掉一。我语文很差，但是代码写得还行，所以大家先看代码吧。不理解的可以在评论留言。
## 代码
那么，就上代码啦。
```cpp
#include<iostream>
#include<queue>
using namespace std;
#define int long long
signed main(){
	int x,y,a,b,c;
	cin>>x>>y>>a>>b>>c;
	priority_queue<pair<int,int> >h;
	while(a--){
		int w;
		cin>>w;
		h.push(make_pair(w,1));
	}
	while(b--){
		int w;
		cin>>w;
		h.push(make_pair(w,2));
	}
	while(c--){
		int w;
		cin>>w;
		h.push(make_pair(w,3));
	}
	int z=x+y;
	int ans=0;
	while(z){
		pair<int,int>f=h.top();
		h.pop();
		if(f.second==3){
			ans+=f.first;
			--z;
		}
		else if(f.second==1&&x){
			ans+=f.first;
			--x;
			--z;
		}
		else if(f.second==2&&y){
			ans+=f.first;
			--y;
			--z;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```
本文到此结束，谢谢您的观看。

---

## 作者：Limury (赞：0)

### 题意

分别给出红苹果，绿苹果，无色苹果的数量和美味值，其中无色苹果可为红绿苹果中的一种，求 $x$ 个红苹果和 $y$ 个绿苹果的最大美味值。


### 思路

题目提到最多选 $x$ 个红苹果和 $y$ 个绿苹果，所以我们可以先不考虑无色苹果，找到 $x + y$ 个美味值最大的红绿苹果。此时，把已经选好的红绿苹果看成一个整体，用每一个无色苹果去比较已选苹果的美味值最低的苹果，比它高则替代它。最后选择的苹果美味值总和即为答案。

### 正确性

因为无色苹果可为红绿苹果中的一种，所以选择无色苹果替代红绿苹果不存在改变此时红绿苹果数量的问题。而从始至终我们选择的都是可供选择的苹果中美味值最大的，所以最后的答案是正确的。

### 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int maxn=1000005;
ll x,y,a,b,c,cnti=1,cnt;
ll lans[maxn],ai[maxn],bi[maxn],ci[maxn];

bool cmp(ll u,ll v){
	return u>v;
}

int main(){
    scanf("%lld%lld%lld%lld%lld",&x,&y,&a,&b,&c);
    for(int i=1;i<=a;i++){
    	scanf("%lld",&ai[i]);
	}
    for(int i=1;i<=b;i++){
    	scanf("%lld",&bi[i]);
	}
    for (int i=1;i<=c;i++){
    	scanf("%lld",&ci[i]);
	}
    sort(ai+1,ai+a+1,cmp);
    sort(bi+1,bi+b+1,cmp);
    sort(ci+1,ci+c+1,cmp);
    for(int i=1;i<=x;i++){
    	lans[++cnt]=ai[i];
	}
    for(int i=1;i<=y;i++){
    	lans[++cnt]=bi[i];
	}
    sort(lans+1,lans+x+y+1,cmp);
    for(int i=x+y;i>=1;i--){
        if(lans[i]<ci[cnti]){
            lans[i]=ci[cnti];
            cnti++;
        }
        if(cnti>c){
        	break;
		}
    }
    ll ans=0;
    for(int i=1;i<=cnt;i++){
    	ans+=lans[i];
	}
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：IGJHL (赞：0)

我在这里先补充一下，题目的输入第一行分别是 $x, y, a, b, c$。

[原题传送门](https://www.luogu.com.cn/problem/AT5240)

### 题意
有红、绿、无色三种苹果 $a, b, c$ 个，每个苹果都有自己的美味程度。一共要吃 $x$ 个红苹果，$y$ 个绿苹果，而无色的苹果绿色或红色，问当吃的苹果的美味程度值和最大时，这个值为多少。

## solution

在选之前先将所有的苹果按美味程度从大到小排个序，然后 `while` 循环一遍累加还没吃过苹果的美味程度最大值，最后输出就行（具体实现见代码）。

## a little details
记得开 `long long`。
## code
```cpp
//我是用堆来实现从大到小排序的
#include <iostream>
#include <queue>

//#define int long long

using namespace std;

struct apple
{
	int tasty, kind;
	//分别表示一个苹果的美味程度及种类：0表示无色，1表示红色，2表示绿色 

	apple(int tt, int kk)
	{
		tasty = tt, kind = kk;
	}
};

//重载<，用来让堆排序
bool operator< (apple x, apple y)
{
	return x.tasty < y.tasty;	
} 

priority_queue <apple> q; 

int x, y, a, b, c, s;

signed main()
{
	cin.tie(0);cout.tie(0);ios::sync_with_stdio(0);
	
	cin >> x >> y >> a >> b >> c;
	
	s = x + y;
	
	for (int i = 1; i <= a; ++ i)
	{
		int p;
		
		cin >> p;
		
		q.push(apple(p, 1));
	}
	
	for (int i = 1; i <= b; ++ i)
	{
		int p;
		
		cin >> p;
		
		q.push(apple(p, 2));
	}
	
	for (int i = 1; i <= c; ++ i)
	{
		int p;
		
		cin >> p;
		
		q.push(apple(p, 0));
	}
	
	int ans = 0;
	
	while (s > 0)
	{
		apple k = q.top();
		q.pop();
		
		if (k.kind == 0)//如果现在美味值最大的是无色苹果 
			ans += k.tasty, -- s;
		else if (k.kind == 1 && x > 0)//如果现在美味值最大的是红苹果且还没有吃到x个红苹果 
			ans += k.tasty, -- x, -- s;//吃，并减少还能吃的红苹果和还能吃苹果总量 
		else if (k.kind == 2 && y > 0)//同理，不过是判断红苹果 
			ans += k.tasty, -- y, -- s;
	}
	
	cout << ans;
	
	return 0;
}
```

对了，直接复制过不了很正常，我改了点细节。

## Thanks For Reading

---

## 作者：fanersaiwenxue (赞：0)

## Describe

你将要吃 $ x $ 个红苹果以及 $ y $ 个绿苹果

你有 $ A $ 个红苹果，它们的美味值分别是 $ p_1 , p_2 ... p_A $ ，以及 $ B $ 个绿苹果，美味值分别 $ q_1,q_2...q_B  $ 
 ，以及 $ C $ 个无色苹果，美味值分别 $ r_1,r_2...r_C $ 。 

在吃无色苹果之前，你可以将它涂成红的或者绿的，然后这个苹果会按照红的或绿的苹果计数 。

你要从上面的苹果来选择要吃的，使得吃过的美味值尽可能大 。

找出将零个或更多无色苹果进行最佳着色时所能达到的吃掉苹果美味的最大可能总和。

## Idea

既然题上说选取美味值最大的 $ x $ 个红苹果和 $ y $ 个美味值最大的绿苹果 , 那我们不妨 :

- 先将红苹果美味值排序 , 选出最大的前 $ x $ 个 存入数组 $ n $ 。

- 再将绿苹果美味值排序 , 选出最大的前 $ y $ 个 存入数组 $ n $ 。

- 最后将所有无色苹果全部存入数组 $ n $ ， 将数组 $ n $ 排序 , 选出美味值最大的 $ x+y $ 个值加入 $ sum $ 最后输出 $ sum $ 。

## Working

我的方法比较麻烦 , 前前后后用了 $ 2.08 s $ , [这里](https://www.luogu.com.cn/record/59645570) 。

方法也不难 , 就是将每一个苹果的美味值存入相应的数组中 , 再用 $ sort $ 将每个数组排一遍 , 选出 $ x  $ 或 $ y $ 个美味值 , 最后排一遍大数组即可 。

注意在将苹果存入数组时用一个变量 $ cnt $ 存苹果的个数不然排大数组时没法排 ( 自作聪明的笑了
 
### 注 : 记得开 $ long long $ 。

## AC Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long x,y,a[100001],b[100001],c[100001],n[1000001],cnt,aa,bb,cc,sum; // cnt 求个数
int main()
{
	cin>>x>>y;
	cin>>aa>>bb>>cc;
	for(int i=1;i<=aa;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+aa+1); // 排出红苹果中的 x 个
	for(int i=aa;i>=aa-x+1;i--)
	{
		n[++cnt]=a[i]; // 将 x 个红苹果加入大数组
	}
	for(int i=1;i<=bb;i++)
	{
		cin>>b[i]; // 排出绿苹果中的 y 个
	}
	sort(b+1,b+bb+1);
	for(int i=bb;i>=bb-y+1;i--)
	{
		n[++cnt]=b[i]; // 将 y 个绿苹果加入大数组
	}
	for(int i=1;i<=cc;i++)
	{
		cin>>c[i]; // 将无色苹果加入大数组
		n[++cnt]=c[i];
	}
	sort(n+1,n+cnt+1); 
	for(int i=cnt;i>=cnt-x-y+1;i--)
	{
		sum+=n[i]; // 排出 x+y 个苹果
	}
	cout<<sum<<endl;
	return 0; // 好习惯..
}
```
✿✿ヽ(°▽°)ノ✿


---

## 作者：LJB00131 (赞：0)

一种不一样的思路(

[博客](https://www.cnblogs.com/LJB00131/p/12590040.html)内体验更佳

显然从大到小排好序后最优，无色的苹果不用管它，因为只要你取到个数且不超过限制一定可以通过分配使他满足。(所以代码特别好写)

```cpp
#include<bits/stdc++.h>

using namespace std;

#define N 500005

int a, b, c, n, X, Y;

long long ans = 0;

struct point
{
	int v, id;

	bool operator < (const point &o) const
	{
		return v > o.v;
	}
}p[N];

int main()
{
	ios::sync_with_stdio(false);
	cin >> X >> Y >> a >> b >> c;
	n = a + b + c;
	for(int i = 1; i <= n; i++)
	{
		cin >> p[i].v;
		if(i <= a) p[i].id = 1;
		else if(i <= a + b) p[i].id = 2;
		else p[i].id = 3; 
	}
	sort(p + 1, p + n + 1);
	int x = 0, y = 0, cnt = 0;
	for(int i = 1; i <= n; i++)
	{
		if(p[i].id == 1)
		{
			if(x == X) continue;
			else x++;
		}
		else if(p[i].id == 2)
		{
			if(y == Y) continue;
			else y++;
		}
		ans += 1ll * p[i].v;
		cnt++;
		if(cnt == X + Y) break;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Pink__ink (赞：0)

# 分析

读完题后，我们可以知道这是一道贪心题。

所以，我们要想，这道题的贪心策略是什么？

这道题让我们输出最大值，那么我们就把输入的红，绿，未涂色的苹果存起来，分别从大到小排序，再进行处理。

我们可以定义一个 $ans$ 把前 $x$ 个红苹果，和前 $y$ 个绿苹果的值想加，就是 $ans$ 的初值，再另外定义一个变量，存上 $ans$ 后，从大到小枚举未涂色的苹果，用两个指针从小到大分别指红，绿苹果，如果当前的红苹果大，那么绿苹果指针向前走一个，反之，红苹果指针走一个，然后把先前赋值的变量减去当前的苹果，再加上现在的未涂色苹果，并与 $ans$ 比一下大小，最后，就是答案。

**注意数据范围**

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 100005
#define ll long long
ll A,B,C,x,y,a[MAXN],b[MAXN],c[MAXN],ans;
bool cmp(int x,int y){
	return x>y;
}
int main(){
	scanf("%lld%lld%lld%lld%lld",&x,&y,&A,&B,&C);
	for(int i=1;i<=A;i++){
		scanf("%lld",&a[i]);
	} 
	for(int i=1;i<=B;i++){
		scanf("%lld",&b[i]);
	}
	for(int i=1;i<=C;i++){
		scanf("%lld",&c[i]);
	}
	sort(a+1,a+1+A,cmp);
	sort(b+1,b+1+B,cmp);
	sort(c+1,c+1+C,cmp);
	for(int i=1;i<=x;i++){
		ans+=a[i];
	}
	for(int i=1;i<=y;i++){
		ans+=b[i];
	}
	ll t=ans;
	int lx=x,ly=y;
	for(int i=1;i<=C;i++){
		if(lx>0&&ly>0){
			t-=min(a[lx],b[ly]);
			t+=c[i];
			ans=max(t,ans);
			if(a[lx]==min(a[lx],b[ly])){
				lx--;
			}
			else{
				ly--;
			}
		} 
		else if(lx>0&&ly==0){
			t-=a[lx];
			lx--;
			t+=c[i];
			ans=max(ans,t);
		}
		else if(lx==0&&ly>0){
			t-=b[ly];
			ly--;
			t+=c[i];
			ans=max(ans,t);
		}
		else{
			break;
		}
	}
	printf("%lld",ans);
	return 0;
} 
```



---

