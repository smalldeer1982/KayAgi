# [ABC137D] Summer Vacation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc137/tasks/abc137_d

$ N $ 件の日雇いアルバイトがあり、$ i $ 件目の日雇いアルバイトを請けて働くと、その $ A_i $ 日後に報酬 $ B_i $ が得られます。

あなたは、これらの中から $ 1 $ 日に $ 1 $ 件まで選んで請け、働くことができます。

ただし、請けたことのある日雇いアルバイトは選べません。

今日から $ M $ 日後まで($ M $ 日後を含む)に得られる報酬の合計の最大値を求めてください。

なお、日雇いアルバイトは今日から請けて働くことができます。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^5 $
- $ 1\ \leq\ B_i\ \leq\ 10^4 $

### Sample Explanation 1

以下のように日雇いアルバイトを請けて働くと、報酬の合計は $ 5 $ となり、このときが最大です。 - 今日、$ 1 $ 件目の日雇いアルバイトを請けて働き、今日から $ 4 $ 日後に報酬 $ 3 $ を得ます。 - 明日(今日から $ 1 $ 日後)、$ 3 $ 件目の日雇いアルバイトを請けて働き、今日から $ 1+2\ =\ 3 $ 日後に報酬 $ 2 $ を得ます。

## 样例 #1

### 输入

```
3 4
4 3
4 1
2 2```

### 输出

```
5```

## 样例 #2

### 输入

```
5 3
1 2
1 3
1 4
2 1
2 3```

### 输出

```
10```

## 样例 #3

### 输入

```
1 1
2 1```

### 输出

```
0```

# 题解

## 作者：MiddleRed (赞：11)

## Discription  
一共有 $N$ 个任务和 $M$ 天，一天只能做一个任务，任务只能做一次，任务当天做完。做完任务后可以在做完后的第 $A_i$ 天拿到 $B_i$ 的工资，问 $M$ 天内最多可以拿到多少工资？
  
  
## Solution  
### 不是01背包！！！！~~(误解了原题面卡了我快半个小时（ )~~
贪心。由于是当天完成隔 $B_i$ 天才能得到工资，可能会存在在 $M$ 天内做完工作但是收不到工资的情况（等 $B_i$ 的时间超过了 $M$），所以我们尽量去做工作完成后 $B_i$ 比较小的任务，然后再在这些任务中做工资最大的任务。  
其中要得到最少天数的任务，直接对原数组按 $B_i$ 大小排序。之后枚举天，每天选择一个工资最大的任务，对于如何选出最大工资的任务，我们选择用优先队列来维护这些任务，这样可以继承前一天可以做但没有做的任务，之后每次弹出工资最大的任务并计入 $ans$ 。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans,idx;
struct job{int d,v;}a[100001];
priority_queue<int> q;
bool cmp(job a,job b){return a.d<b.d;}
int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)	cin>>a[i].d>>a[i].v;
	sort(a,a+n,cmp);
	for(int i=0;i<m;i++)
	{
		for(;a[idx].d<=i+1 and idx<n;idx++)	q.push(a[idx].v);
		if(!q.empty())	
		{
			ans+=q.top();
			q.pop();
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Steadywelkin (赞：4)

### 题意

有 $N$ 个任务和 $M$ 天，每天只能做一个任务，任务只能做一次，任务当天做完，做完任务后可以在完成后的第 $A_i$ 天得到 $B_i$ 的工资，问 $M$ 天内最多可以得到多少工资？

### 思路

本题与 [UVA1316 Supermarket](https://www.luogu.com.cn/problem/UVA1316) 很相似，同样是有一定时限，问取得的最大值。所以我们将这题的思路与上题衔接。

两题的不通点在于本题给出的是完成任务后第 $A_i$ 天可以得到的收益，而上题给出的是每一个物品的使用时限。同样，如果一项任务对我们的答案有贡献，其实就相当于这个任务要在第 $M-A_i+1$ 天之前完成，所以我们可以在输入的时候将时间进行转换，两题就变得没有什么区别啦。

建立一个并查集，再用经典的贪心思路，就可以通过此题。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define int long long
using namespace std;

inline int read()
{
	int a=0,f=1;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar())
		if(ch=='-')f=-1;
	for(;isdigit(ch);ch=getchar())
		a=(a<<3)+(a<<1)+ch-'0';
	return a*f;
}

const int mod=1e9+7;
const int N=2e5+5;
int n,m,fa[N],ans,g;

int find(int x)
{
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}

struct work
{
	int tim,val;
	inline bool operator<(const work& a)const{
		if(val==a.val) return tim<a.tim;
		return val>a.val;
	}
}w[N];

signed main()
{
	n=read(),m=read();
	
	for(int i=1;i<=n;i++)
	{
		w[i].tim=m-read()+1;
		w[i].val=read();
		g=max(g,w[i].tim);
	}
	
	for(int i=1;i<=g;i++)
		fa[i]=i;
	
	sort(w+1,w+n+1);
		
	for(int i=1;i<=n;i++)
	{
		int t=w[i].tim;
		if(t<=0)continue;
		int k=find(t);
		if(k>0)
		{
			ans+=w[i].val;
			fa[k]=k-1;
		}
	}
	
	printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：Sexy_Foxy (赞：2)

## 题意：

给你一组数，每个数都有两个值，一个值表示收益要几天后到，另一个值表示能获得的收益，问 $m$ 天后你能获得的最大收益。

## 解题思路：

我们先从题意抽出一个数学模型来：每天所选择的数中，必须满足天数小于剩余天数，在从中找出一个最大的加上即可。

### 第一步：

不难看出，这题要用贪心，但是不是 01 背包 呢？从上述中我们知道只要天数满足小于剩余天数，再从中找收益最大的即可，而不满足的你做了也对总收益没有贡献，所以是纯贪心！（~~题面真害人！~~）

### 第二步：

思路有了，怎样实现呢？如果开一个数组保存的话，那排序的话，每次排序都要耗费大量时间，再结合数据范围来看是完全行不通的，怎么办呢？

首先，我们只要一个最大值就行了，并不需要把非最大值也进行操作，我们就可以用一种更便捷的做法去找最大值。这里就涉及到了 [大根堆](https://blog.csdn.net/dream_follower/article/details/105202811) 的知识点（没学过的可以去看看，这里给了链接），而大根堆插入元素时维护所需的时间复杂度是 $O(\log n)$ 的，再结合数据范围一看，时间复杂度是绰绰有余的，所以此方法可行！

为了方便大家理解代码（~~手动模拟大根堆太麻烦~~），所以这里直接用万能的 **STL** 中的 [priority_queue 优先队列](https://blog.csdn.net/qq_42410605/article/details/100537452) 充当大根堆（有兴趣的可以去了解一下）。

### 第三步：

接下来是代码时间！

#### 定义部分：

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
struct node //结构体储存所需时间和收益
{
	int a,b;
	void input() //除了秀以外没啥用的输入函数
	{
		scanf("%d%d",&a,&b);
	}
}ab[100010];
priority_queue<int>line; //优先队列，用来处理最大值
int n,m;
ll ans; //答案
bool cmn(node x,node y) //排序所需的函数
{
	return x.a<y.a;
}
```

#### 输入+预处理：

```
scanf("%d%d",&n,&m);
for(int i=1;i<=n;i++)
{
	ab[i].input(); //输入函数
}
sort(ab+1,ab+n+1,cmn); //先按时间排序
```

#### 贪心：

```
int cnt=1; //记录当前是第几个元素
for(int i=1;i<=m;i++) //i表示剩余天数
{
	while(ab[cnt].a<=i&&cnt<=n) //将满足条件的全部插入优先队列
	{
		line.push(ab[cnt].b);
		cnt++;
	}
	if(!line.empty()) //如果队列不为空
	{
		ans+=line.top(); //找到最大值，让答案加上它
		line.pop();
	}
}
```

#### 输出：

```
printf("%lld",ans); //输出答案
return 0; //完结撒花
```

## 完整的Code

The following code is what you want most.

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
struct node
{
	int a,b;
	void input()
	{
		scanf("%d%d",&a,&b);
	}
}ab[100010];
priority_queue<int>line;
int n,m;
ll ans;
bool cmn(node x,node y)
{
	return x.a<y.a;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		ab[i].input();
	}
	sort(ab+1,ab+n+1,cmn);
	int cnt=1;
	for(int i=1;i<=m;i++)
	{
		while(ab[cnt].a<=i&&cnt<=n)
		{
			line.push(ab[cnt].b);
			cnt++;
		}
		if(!line.empty())
		{
			ans+=line.top();
			line.pop();
		}
	}
	printf("%lld",ans);
	return 0;
}
```

## 后记：

注：本篇题解中的链接中的内容非本人所写

#### qwq

---

## 作者：duchengjun (赞：1)

# 题意

一共有 $N$ 个任务和 $M$ 天，一天只能做一个任务，任务只能做一次，任务当天做完。做完任务后可以在做完后的第 $A_i$ 天拿到 $B_i$ 的工资，问 $M$ 天内最多可以拿到多少工资？

# 分析

贪心，数组 $a$ 以 $A_i$ 的值排序，若 $A_i$ 相同则以工资多的先。

枚举 $1\sim M$ 的每一天，若有可以拿到工资的就拿 $B_i$ 最大的值。

先排序，后用优先队列来维护 $B_i$ 的值，每一次加上可以拿到工资的最大 $B_i$ 值即可。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
//此处为快读代码
const int N=1e5+10;
int n,m,ans,t;
struct P{
	int a,b;
}a[N];
bool cmp(P u,P v){
	return u.a<v.a;
}
priority_queue<int>q;
int main(){
	read_(n,m);
	for(int i=1;i<=n;i++)
		read_(a[i].a,a[i].b);
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=m;i++){
		while(a[t].a<=i&&t<=n){
			q.push(a[t].b);
			t++;
		}
		if(!q.empty()){
			ans+=q.top();
			q.pop();
		}
	}
	write_(ans);
	return 0;
}


```


---

## 作者：Anaxagoras (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT4877)

### 0x00 所需知识

1. 贪心（不是 01 背包）

1. STL priority_queue 优先队列

### 0x01 思路

这里我们要求的是 $M$ 天所得工资最大值，那么我们就需要把所需天数少的优先做完，然后再考虑工资数量。那么我们可以在按天数排好序后在枚举每一天时用一个从大到小的优先队列把当天天数加上所等天数尽量小的工资数量存起来

```cpp
#include<bits/stdc++.h>
using namespace std;
struct rw
{
  int d;//所等天数
  int p;//工资
};
rw a[100005];
inline bool cmp(rw x,rw y)
{
  return x.d<y.d;//按所等天数尽量小来排序
}
priority_queue<int>q;//从大到小排序的优先队列
int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n,m;
  cin>>n>>m;
  for(int i=1;i<=n;i++)
    {
      cin>>a[i].d>>a[i].p;
    }
  sort(a+1,a+n+1,cmp);
  int rank=0;
  int ans=0;
  for(int i=1;i<=m;i++)
    {
      while(rank<=n&&a[rank].d<=i)//不越界并且所等天数加上当前天数尽量小的入队
        {
          q.push(a[rank++].p);
        }
      if(!q.empty())//有符合条件的
        {
          ans+=q.top();
          q.pop();
        }
    }
  cout<<ans<<'\n';
  return 0;
}

```

完结散花～（暗示）

---

## 作者：L_zaa_L (赞：0)

## 分析
可以考虑贪心，价值从大到小枚举，先把这个价值取到，也就是在 $1\ldots m-a_i+1$ 中从大到小找，找到最接近且小于且这天没有做过的。但可以知道代码复杂度是 $O(N^2)$，很明显，会超时，但再找的时候，可以用并查集找最接近且小于且这天没有做过的，就可以得到 $O(N \log N)$ 的复杂度。
## Code
```
// The leadone who wants to destory his OI life
/*Mlm:  Tlm:*/
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define mid ((l+r)>>1)
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
#define modj(x) ((x)-=((x)>=MOD)?MOD:0)
#define qmin(x,y) ((x)=min((x),(y)))
#define qmax(x,y) ((x)=max((x),(y)))
using namespace std;
inline ll read(){
	ll t=0,f=0;char v=getchar();
	while(!isdigit(v))f|=(v=='-'),v=getchar();
	while(isdigit(v))t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
}
inline void write(ll x){
	if(x<0){x*=-1; putchar('-');}
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}
struct XX{
	int w,day;
}a[1000005];
bool cmp(XX x,XX y){
	if(x.w!=y.w)return x.w>y.w;
	return x.day>y.day;
}
int fa[10000005];
int find(int f){//并查集
	if(fa[f]==f) return f;
	return fa[f]=find(fa[f]);
}
int ss[10000005],op;

signed main() {
	int n,m;
	n=read(),m=read();
	int s=0,ans=0;
	for(int i=1;i<=n;i++){
		a[i].day=read(),a[i].w=read();
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=m;i++){
		fa[i]=i;
	}
	for(int i=1;i<=n;i++){
		int p=find(m-a[i].day+1);//查找最接近且小于且这天没有做过
		if(p<=0){
			continue;
		}//如果找不到，这个工作就不做了
		fa[p]=find(p-1);//路径压缩
		ans+=a[i].w;
		ss[p]=1;//标记这天走过了
	}
	cout<<ans;
    return 0;
}
```

## End
但为什么这个贪心是对的呢，因为如果过这一天放其他的工作，答案肯定比他小，而从大到小可以使一些 $b$ 小 $a $ 小的数，放进去，而从小到大，可能到了后面，有些数本来能放但是又放不进去了。

---

## 作者：Jairon314 (赞：0)

> [题目链接](https://atcoder.jp/contests/abc137/tasks/abc137_d)

$ Solution $

------------

考虑 dp ，设 $ dp_i $ 表示 $i$ 天内能获得的最大收益。枚举 $i$ ，每多一天就相当于 $ i-1 $ 天处理完了，在前面补上一天。把当前天数内能得到收益的加入一个优先队列，每天贪心选出最优的一个即可。

[AC记录](https://atcoder.jp/contests/abc137/submissions/29191049)

代码：

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <queue>
using namespace std;

#define $int long long

/***** Fast_IO *****/

using vii = vector<int>;
using pii = pair<int,int>;

namespace IO{
	char buf[(1<<21)],*p1=buf,*p2=buf,buf1[(1<<21)]; int _=0;

	#define gc getchar
	#define pc putchar

	template<class I>
	inline I read(I &x){
		x=0; I f=1; char c=gc(); if(c==EOF){ return -1; }
		while(c<'0'||c>'9'){ if(c=='-'){ f=f*(-1); } c=gc(); }
		while(c>='0'&&c<='9'){ x=(x<<1)+(x<<3)+(c^48); c=gc(); }
		return x=x*f;
	}

	template<typename I,typename ...Args>
	inline void read(I &a, Args &...args){
		read(a),read(args...);
	}

	template<class I>
	inline void write(I x){
		if(x==0){ pc('0'); return; }
		int tmp=x>0?x:(-x),cnt=0;
		if(x<0){ pc('-'); }
		while(tmp){ buf[cnt++]=(tmp%10)+'0'; tmp/=10; }
		while(cnt){ pc(buf[--cnt]); }
		return;
	}
	
	template<class I>
	inline void chmax(I &x,I y){ return x=max(x,y),void(); }
	
	template<class I>
	inline void chmin(I &x,I y){ return x=min(x,y),void(); }

	#define out(x) write(x),pc(' ')
	#define outn(x) write(x),pc('\n')
	#define assi() pc('\t')
	#define FOR(i,a,b) for(int i(a);i<=(b);++i)
	#define ROF(i,a,b) for(int i(a);i>=(b);--i)
	#define FORs(i,a,b,s) for(int i(a);i<=(b);i+=(s))
	#define ROFs(i,a,b,s) for(int i(a);i>=(b);i-=(s))
	#define next(i,now) for(int i(link[now]);i;i=edge[i].nexty)
	#define all(v) (v).begin(),(v).end()
	#define each(i,v) for(auto &i:v)
	#define sqr(k) ((k)*(k))
	#define inf 0x3f3f3f3f
	#define pb push_back
	#define mp make_pair
	#define fir first
	#define sec second
	#define db double
}using namespace IO;

/***** Fast_IO *****/

#define maxn 1000010
#define SIZE 5010

int n,m;

priority_queue<int> pq;

int main(){
	read(n,m);
	vector<pii> obj(n);
	FOR(i,0,n-1){ read(obj[i].fir,obj[i].sec); }
	sort(all(obj)); int d=0,res=0;
	FOR(Day,1,m){
		while(d<n&&obj[d].fir<=Day){
			pq.push(obj[d].sec); ++d;
		} if(!pq.empty()){ res+=pq.top(); pq.pop(); }
	} outn(res);
	return 0;
}
```


---

