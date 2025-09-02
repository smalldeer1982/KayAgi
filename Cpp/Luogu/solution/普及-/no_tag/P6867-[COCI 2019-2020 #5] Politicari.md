# [COCI 2019/2020 #5] Politicari

## 题目描述

有 $n$ 个人互相批评。

另提供矩阵 $A$。

规则如下：

- 第一次，第 $1$ 个人批评第 $2$ 个人。

- 如果第 $i-1$ 次为第 $u$ 个人批评第 $v$ 个人，

	那么第 $i$ 次为第 $v$ 个人批评第 $A_{v,u}$ 个人。

求第 $k$ 次是谁**进行**批评（注意：不是**被**批评）。

## 说明/提示

### 数据范围

- 对于 $35 pts$ 的数据，保证 $1\leq k\leq 10^5$。
- 对于所有的数据，$2\leq n\leq 500$ 且 $1\leq k\leq 10^{18}$。

### 说明

**题目译自 [COCI2019-2020](https://hsin.hr/coci/archive/2019_2020/) [CONTEST #5](https://hsin.hr/coci/archive/2019_2020/contest5_tasks.pdf)  _T2 Političari_** ，译者 [90693](/user/90693)。

## 样例 #1

### 输入

```
2 4
0 2
1 0
```

### 输出

```
2```

## 样例 #2

### 输入

```
3 7
0 3 2
3 0 3
2 1 0
```

### 输出

```
1```

## 样例 #3

### 输入

```
4 7
0 4 3 2
4 0 4 1
2 1 0 1
3 2 3 0
```

### 输出

```
3```

# 题解

## 作者：zhaoyp (赞：17)

## Solution
### 对于 $35 pts$ 的数据
由于 $k \le 10^5$，直接按题意模拟即可。
### 对于所有的数据
由于 $1 \le k \le 10^{18}$，直接模拟显然是行不通的，考虑优化。

如果将第 $u$ 个人批评第 $v$ 个人的定义为一个状态的话，因为一共有 $n$ 个人，每个人可以对其他 $n - 1$ 个人进行批评 ，那么 $k$ 次批评最多的状态数为： $n \times (n - 1) = 500 \times 499 = 249500$ 。

因为在确定上一次批评的批评者和被批评者时，下一次批评的批评者和被批评者是确定的。换句话说，对于已知的现有状态，有唯一确定的下一状态。如果将状态视为节点，批评的过程视为边的话，则每个节点出度均为 $1$。

以样例 $2$ 为例：
```latex
3 7
0 3 2
3 0 3
2 1 0
```
通过模拟我们不难发现第 $1$ 次和第 $4$ 次批评都是第 $1$ 个人批评第 $2$ 个人，可见在 $k$ 次批评中有许多状态会被重复访问。即该图中存在环，大量批评的过程在此环中重复进行，浪费了大量时间。我们只需找出此环，在进入到环中任意一节点时，将剩余批评次数对环的长度进行求余，再模拟即可，这样就省去了无数次在环中“绕圈”的过程。

## code
下面给出递归实现：
```cpp
#include<bits/stdc++.h>
int n,a[505][505],vis[505][505];
long long m;
void input()
{
	scanf("%d%lld",&n,&m);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++)
			scanf("%d",&a[i][j]);
}
void dfs(int x,int y,long long k)
{
	if(vis[x][y])
		m = (m - k) % (k - vis[x][y]) + k;
	if(k == m)
	{
		printf("%d",x);
		exit(0);
	}
	vis[x][y] = k;
	dfs(y,a[y][x],k + 1);
}
int main()
{
	input();
	dfs(1,2,1);
	return 0;
}
```

---

## 作者：Jekyll_Y (赞：9)

### ~~这是一道大水题（指调了10次才过）~~
通过样例不难看出批评的顺序是会**循环**的

比如：
```c
输入：
4 7
0 4 3 2
4 0 4 4
2 1 0 1
3 2 3 0
输出：
4
批评顺序为：
1 2
2 4
4 2
2 4
4 2
2 4
4 2
所以输出为4

```
所以我们只需要找到这个循环的起点和终点就可以了

 （~~一开始打暴力只有30~~）
 
###  Code：
```c
#include<cstdio>
#include<iostream>
using namespace std;
long long n,k,l;//k的范围要开long long  
long long a[510][510],tot,ans[1010000],last;
int b[510][510];//记录每次批评所对应的次数 
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>a[i][j];
			if(i!=j)b[i][j]=-1;
			//输入和初始化 
		}
	}
	ans[tot++]=1;last=2;
	b[1][2]=0;
	//第一次
	while(1)
	{
		int xx=a[last][ans[tot-1]];//被批评的 
		ans[tot++]=last;//存进行批评的人 
		if(b[last][xx]!=-1)//如果批评已经进行过 
		{
			l=b[last][xx];//存循环起点 
			break;
		}
		if(tot==k)//如果循环还没找到，却已经达到了次数，直接输出 
		{
			cout<<ans[k-1];
			return 0;
		}
		b[last][xx]=tot-1;//存每次批评所对应的次数 
		last=xx;//下一个要进行批评的人 
	}
	cout<<ans[l+(k-l-1)%(tot-l-1)];//循环的起点加上第k次所对应这个循环的第几次； 
	//因为调这里卡了n次
	//至于为什么这样写自己可以多找几个样例试试 
	return 0;
	//AC
}
```
（惨烈[阿巴阿巴](https://www.luogu.com.cn/record/list?pid=P6867&user=239160)）
 

---

## 作者：Wu_while (赞：6)

## 一、直接模拟
模拟代码
```cpp
#include<iostream>
#include<cstdio>
#define ll unsigned long long//不开long long 见祖宗
using namespace std;
ll k;
int n,a[510][510];
int u,v,t;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	u=1;//u为批评者
	v=2;//v为被批评者
	for(int i=2;i<=k;i++)
	{
		t=v;
		v=a[v][u];
		u=t;
	}//第v个人批评a[v][u]个人
         //t用来辅助交换
	cout<<u<<endl;
	return 0;
}
```
[TLE 35分](https://www.luogu.com.cn/record/44828852)

## 二、周期循环
看**数据范围**：
$1≤k≤10^{18}$

于是~~打表~~找规律
```cpp
#include<iostream>
#include<cstdio>
#define ll unsigned long long
using namespace std;
ll k;
int n,a[510][510];
int u,v,t;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	u=1;
	v=2;
	for(int i=2;i<=k;i++)
	{
		t=v;
		v=a[v][u];
		u=t;
		cout<<v<<' '<<u<<endl;
	}
	return 0;
}
```
**发现有规律！**

上代码：

```cpp
#include<iostream>
#include<cstdio>
#define ll unsigned long long
using namespace std;
ll k;
int n,a[510][510];
int s[510][510];//储存批评双方的出现位置 
int u,v,t,len,c;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	u=1;
	v=2;
	for(int i=2;i<=k;i++)
	{
		t=v;//模拟 
		v=a[v][u];
		u=t;
		if(s[v][u])//这个双方是否出现过 
		{
			len=i-s[v][u];//周期长度 
			c=s[v][u]; 
			break;
		}
		s[v][u]=i;//标记批评双方 
	}
	if(c)//是否找到周期 
	{
		len=(k-c)%len;//周期外的 
		for(int i=1;i<=len;i++)
		{
			t=v;//模拟 
			v=a[v][u];
			u=t;
		}
	}
	cout<<u<<endl;
	return 0;
}
```
[AC 70分](https://www.luogu.com.cn/record/44829419)

---

## 作者：_edge_ (赞：3)

这题目~~到底是哪门子图论呀？~~

首先看 35pts 的部分分，可以想到一个 $O(k)$ 的暴力做法，按照题意模拟一遍即可。

然后 …… 想一下，它这个是不是肯定会有循环的产生？

所以 …… 就会产生如下的可能性：

$1,2$ $→$ $2,3$ $→$ $3,1$ $→$ $1,2$

然后又变成了 $1,2$ 开始循环。

于是可以用一个二维数组来记录当前到第几步，如果说遍历到的两个人在之前出现过了，就可以判断一定有循环节，注意循环节有可能不从 $1,2$ 开始哦！

然后用一个取模运算省去过程，暴力模拟剩下的余数就可以了。

总时间复杂度：$O(n^2)$

空间复杂度：$O(n^2)$

于是 …… 这题目就愉快地解决了！

```cpp
#include <iostream>
#include <cstdio>
#define int long long//注意开 long long 。
using namespace std;
const int INF=505;
int n,a[INF][INF];
int f[INF][INF];
long long m,tot;
signed main()
{
        scanf("%lld %lld",&n,&m);
        for (int i=1; i<=n; i++)
                for (int j=1; j<=n; j++)
                        scanf("%lld",&a[i][j]);
        int x=1,y=2;tot=1;
        while (tot<m && !f[x][y]) {
                f[x][y]=tot;tot++; 
				int tmp=x;x=y; 
				y=a[y][tmp];
        }
		if (tot==m) {cout<<x<<"\n";return 0;}
		tot=tot-f[x][y];//注意减去前面的。
//		cout<<f[x][y]<<"\n";
        m-=f[x][y]-1;m%=tot;//取余数。
		if (m==0) m=tot;
		tot=1;
        while (tot<m) {
        	tot++;
        	int tmp=x;x=y; 
			y=a[y][tmp];
		}
		cout<<x<<"\n";
		return 0;
}
```

---

## 作者：梨衣 (赞：2)

## 又是一个大模拟找规律
本想直接模拟，看到 $k$ 值才发现此题不简单，各种特判提交数次才过了，有些麻烦，真真纯模拟题

### 打表找规律
只要找到循环规律就可以用模运算解决问题了，而且规律很好找，关键是后面的判断麻烦。
#### 代码如下
```cpp
int a=1,b=2,c;
	r[1][1]=1,r[2][1]=2,v[1][2]=1;
	for(int i=1;;i++){//模拟过程找循环点 
		c=f[b][a];
		a=b;
		b=c;	
		r[1][++cnt]=a;
		r[2][cnt]=b;
		if(v[a][b]==1)//找到循环位置，退出 
			break;
		v[a][b]=1;
	}
```
需要注意，**本题不一定从第一次传递直接开始循环，会出现传递几次后再开始循环的情况**，那么就要求出真正的循环长度，且对 $k$ 要先预处理到进入循环时再运算。
```cpp
int ii;
	for(int i=1;i<=cnt;i++)
		if(r[1][i]==r[1][cnt]&&r[2][i]==r[2][cnt]){
			cnt-=i;//求出循环长度 
			ii=i-1;//记录进入循环前的位置 
			break;
		}
	//此时ii为循环前无规则的部分，很无用，但模拟时要算进去 
```
### 接着就可以计算答案了
**记得时刻带着循环前的部分，不然必出错**
#### 代码如下
```cpp
int ans;
	if(k-ii<=cnt)//如果不满足一个循环 
		ans=r[1][k];
	else {
		k-=ii;//除去无用部分还可循环几次 
		k%=cnt;
		if(k==0)ans=r[1][ii+cnt];//计数时记得带上ii 
		else ans=r[1][ii+k];
	}
```
## 完整代码
```cpp
#include<cstdio>
#define int long long
using namespace std;
int f[550][550],cnt=1,r[3][100010],v[550][550];
//r数组记录每次批评者与被批评者 
//v标记找过的位置 
signed main(){
	int n,k;
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%lld",&f[i][j]);
	int a=1,b=2,c;
	r[1][1]=1,r[2][1]=2,v[1][2]=1;
	for(int i=1;;i++){//模拟过程找循环点 
		c=f[b][a];
		a=b;
		b=c;	
		r[1][++cnt]=a;
		r[2][cnt]=b;
		if(v[a][b]==1)//找到循环位置，退出 
			break;
		v[a][b]=1;
	}
	int ii;
	for(int i=1;i<=cnt;i++)
		if(r[1][i]==r[1][cnt]&&r[2][i]==r[2][cnt]){
			cnt-=i;//求出循环长度 
			ii=i-1;//记录进入循环前的位置 
			break;
		}
	//此时ii为循环前无规则的部分，很无用，但模拟时要算进去 
	int ans;
	if(k-ii<=cnt)//如果不满足一个循环 
		ans=r[1][k];
	else {
		k-=ii;//除去无用部分还可循环几次 
		k%=cnt;
		if(k==0)ans=r[1][ii+cnt];//计数时记得带上ii 
		else ans=r[1][ii+k];
	}
	printf("%lld\n",ans);
	return 0; 
} 
```
## The end

---

## 作者：SingularPoint (赞：1)

### 题目大意
给出一个矩阵$A$，按指定规则进行$k$次批评后求第$k$次**进行批评**的人。
### 分析
首先想到可以模拟出每次批评的过程，但是看到数据范围： $1\le k\le 10^8$……嘶……

于是**纯模拟必爆**~~（它SPFA了）~~

发现如果按照题目中根据矩阵指示的方式进行批评，会有**环**的出现，即在进行数次批评后会回到之前的某次批评过程，可以想到利用这一点减少模拟次数。

批评的过程可以用一个一维数组（代码中为$ans$）进行存储，$ans_i$代表第$i$次**进行批评**的人，根据题目中描写的批评过程，可知第$i-1$次批评为$ans_{i-1}$对$ans_i$（当前进行批评的人）的批评。同时，我们还需要用一个函数来计算循环节开始的时间。

分析结束，上代码！（更多细节请看注释~）
### Code
对了……

![](https://cdn.luogu.com.cn/upload/image_hosting/u59n3gd7.png)

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
using namespace std;
const int INF=0x3f3f3f3f;
ll n,k,T,st;//1<=k<=10^18，十年OI一场空，不开long long___~ 
ll a[501][501];
ll ans[500001];
bool v[501][501];//v[i][j]记录第i个人是否批评过第j个人。 
void get_st(ll v,ll u)//找循环起点 
{
	for(ll i=1;i<T;i++)
		if(ans[i]==v&&ans[i+1]==u){
			st=i;
			return;
		}
}
void find(ll now,ll cnt)
{
	ans[cnt]=now;
	ll t=a[now][ans[cnt-1]];
	if(cnt==k){//小优化，如果已经找到了第k次批评，直接输出 
		printf("%d",now);
		T=0;
		return;
	}
	if(v[now][t]){
		T=cnt;
		get_st(now,t);
		return;
	}
	v[now][t]=1;
	find(t,cnt+1);
}
int main()
{
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%lld",&a[i][j]);
	memset(v,0,sizeof(v));
	ans[1]=1;
	v[1][2]=1;//第一次批评为1批评2 
	find(2,2);
	if(!T) return 0;
	T-=st;
	k-=st;
	printf("%lld",ans[k%T+st]);
	return 0;
}
```
完结撒fa~

---

## 作者：王炸拆开打 (赞：1)

# 核心思想：模拟

### 重要思想：周期

------------
35分的代码我就不展示了，下面咱们根据样例二来分析一下：

```
3 7
0 3 2
3 0 3
2 1 0
```
那么它应该是这个过程：
```
u v：
1 2
2 3
3 1
1 2
2 3 哇！周期出现了
3 1
1 2
```
不难发现```2 3```是一个循环节，简单粗暴，直接用$VIS$标记然后看它有没有出现过就完事了


------------
所以，我们的思路是找到周期，然后略过中间无用的过程，直接模拟最后的一个周期就可以了^__^

上代码，起飞，芜湖~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define LL long long// 10^18开LL 
using namespace std;
int n;
LL k;
int a[1001][1001];
int vis[1001][1001];
int main(){
	scanf("%d %lld",&n,&k);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			scanf("%d",&a[i][j]);
	int u=1,v=2,cnt=1,c=0;
	for(int i=2;i<=k;i++){
		int v1=v;
		v=a[v][u];
		u=v1;//模拟 
		cnt=i-vis[u][v];//记住循环的长度 
		if(vis[u][v]){//如果遇到有过的，c会记住他之前出现的位置 
			c=vis[u][v];break;
		}
		vis[u][v]=i;
	}
	if(c){
		cnt=(k-c)%cnt;//长度%周期=最后剩多少 
		if(cnt==0) printf("%d",u);//直接输出 
		else{
			for(int i=1;i<=cnt;i++){//走一遍 
				int v1=v;
				v=a[v][u];
				u=v1;
			}
			printf("%d",u);
		}
	}
	else printf("%d",u);//有可能一直没遇到循环，直接模拟答案即可 
	return 0;
}
```
大佬们多指教

---

## 作者：yf最qhhh (赞：1)

~~这道题也就卡了我亿会而已qwq（而且为什么标签里有图论）~~

首先，一个正常人拿到这个题，都会想到暴力。

But，十八次方注定了这道题不能暴力，所以我们就要换一种思路。

其实枚举一下就能发现有是存在规律的，到某个人的时候就又从头开始了，当枚举到那个人的时候就取模就行了，剩下的再枚举，就比暴力节省了好多的时间！

~~（怎么还不走？这里没有你想要的东西）~~

贴一份35分的友情代码吧（听懂了的话这份代码上改改就AC了）
```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
int A[505][505];
int main(){
	ll n,k,u=1,v=2,u1,v1;
	scanf("%lld%lld",&n,&k);
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n;j++){
			scanf("%lld",&A[i][j]);
		}
	}
	for(int i=2;i<=k;i++){
		u1=v;
		v1=A[v][u];
		u=u1;
		v=v1;
	}
	cout<<u;
	return 0;
}
```


---

## 作者：Viktley (赞：0)

### P6867 【[COCI2019-2020#5] Politicari】

---

**题目大意：**

有 $n$ 个人， $k$ 次批评，问 $k$ 次批评后是哪位大佬在进行批评？

批评的过程是：

+ 第一次，第 $1$ 个人批评第 $2$ 个人。

- 如果第 $i−1$ 次为第 $u$ 个人批评第 $v$ 个人，

* 那么第 $i$ 次为第 $v$ 个人批评第 $A[v,u]$ 个人。

求第 $k$ 次是谁进行批评（注意：不是被批评）。

---

**思路**

 _对于 $35 pts$ 。_ 

暴力按照批评的过程来进行模拟，最后输出答案即可！

 _对于 $100 pts$ 。_ 
 
 $k = 10^{18}$,对于这种超大的数据，模拟一定会T，于是我们试得找规律。
 
 来例3来说：
 
 ```cpp
 4 7
0 4 3 2
4 0 4 1
2 1 0 1
3 2 3 0

批评过程：
1 2
2 4
4 2
2 4
4 2
2 4
4 2
 ```
 
由上图可知，批评过程当到一定时间时，

批评顺序会进行循环，那我们只有通过

模拟求出批评过程中的循环节，那不就

转换成了一个周期性问题了吗？

但细心的你一定会发现，批评过程中

除了循环节外，还会有一些无规律的批评

也就是说我们还要排除无规律的，然后才能进行

周期性问题！！

---

**Code:**
```cpp
#include<cstdio>
using namespace std;
int n,b[250005],a[505][505],p[505][505];
long long k;
int main()
{
	scanf("%d%lld",&n,&k);
	for(int i=1;i<=n;i++)
	 for(int j=1;j<=n;j++)
	  scanf("%d",&a[i][j]);
	int head=1,tail=2,o=1; //批评人，被批评人, 第k次批评；
	p[1][2]=1; //用来判断循环节是从哪里开始的
	b[o]=1;   //记录第几次是谁在进行批评
	while(o)
	{
		o++;
		int x=tail;
		tail=a[tail][head];
		head=x;
		if(p[head][tail]==0)p[head][tail]=o;  //还没有找到循环节
		else break;  //已找到循环节
		b[o]=head;  //记录答案
	}
	if(k>(p[head][tail]-1))k-=(p[head][tail]-1);
	else{printf("%d",b[k]);return 0;} //如果k次后的批评还在无规律中，直接输出答案
   //以下为周期性问题求解
	int len=o-p[head][tail]; 
	k%=len;
	if(k==0){printf("%d",b[o-1]);return 0;}  
	for(int i=p[head][tail];i<o;i++)
	{
		k--;
		if(k==0){printf("%d",b[i]);break;}
	}
	return 0;
}
```

---

## 作者：苏黎世 (赞：0)

[支持一下吧~](https://www.luogu.com.cn/blog/Psycho-520/)

首先看到这个题，我们就直接while循环模拟了。

但是交上去会发现吧。[评测记录](https://www.luogu.com.cn/record/40839126)


于是，我们又回头，认真看了这个题。

模拟~~半天~~明白：这个题吧，是个找规律的题。

当我们模拟时突然发现，批评中就出现了循环。

这里就不给过程了，有兴趣的可以手模一下。

这个时候，我们就知道了这个题的关键。

### 找出规律。

~~上句是废话。~~

比如说：
我们把每次批评的人存到st数组里面。

4个数， 2个一循环 1开始循环。
结果是什么呢？

```cpp
printf("%d", st[q + (k - q )%(top - q + 1)]);
```
这个是要理解的。

(k - q )%(top - q + 1)的作用就是看看要取规律的第几个数，再加上q就是结果。

如果不理解，可以自己多调试几遍。

再下来，就是如何while进行找规律。

原题目：

### 第一次，第 1 个人批评第 2 个人。
### 如果第 i−1 次为第 u 个人批评第 v 个人，
### 那么第 i 次为第 v 个人批评第 A${v,u}$ 个人。

于是，我们有以下思路：

令u为每次批评的人，初值为1。

v为每次被批评的人，初值为2。

st数组存下来每次批评的人。

b数组存一下每个人是第几次被批评的。

那么代码就是：

```cpp
memset(b, -1, sizeof(b));
int temp, u = 1, v = 2, q;
	
st[++top] = 1;
b[1][2] = 1;

while(1)
{
	
	temp = u;
	u = v;
	v = a[u][temp]; 
	if(b[u][v] != -1)
	{
		q = b[u][v];
		break;
	}
	++top;
	b[u][v] = top;
	st[top] = u;
}
```

是不是一脸懵？

再看一下注释：

```cpp
memset(b, -1, sizeof(b));//存每个人是第几次被批评
int temp, u = 1, v = 2, q;
//temp用来临时存一下，因为u，v的值会改变
//q是指第几次开始有的规律
st[++top] = 1;
b[1][2] = 1;
//在while外面完成第一次批评
while(1)
{
	temp = u;
	u = v;
	v = a[u][temp]; //到此一次批评结束
	if(b[u][v] != -1)//被批评过，说明规律出现
	{
		q = b[u][v];
		break;
	}
	++top;
	b[u][v] = top;//第几次被批评
	st[top] = u;//存批评的人
}
```
理解到这里，整个题就已经没有难度了。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 505;
int n, a[maxn][maxn], b[maxn][maxn];
int st[110110];
ll k, top;//注意数据范围

void cini()
{
	scanf("%d%lld", &n, &k);
	for(int i = 1;i <= n; ++i)
	  for(int j = 1;j <= n; ++j)
	    scanf("%d", &a[i][j]);
}//输入

void work()
{
	memset(b, -1, sizeof(b));
	int temp, u = 1, v = 2, q;
	
	st[++top] = 1;
	b[1][2] = 1;
	
	while(1)
	{
		
		temp = u;
		u = v;
		v = a[u][temp]; 
//		printf("%d %d %d\n", u, v, b[u][v]);
		if(b[u][v] != -1)
		{
			q = b[u][v];
			break;
		}
		++top;
		b[u][v] = top;
		st[top] = u;
		if(top - 1 == k)
		{
			printf("%d", st[top-1]);
			return;
		}//特判，如果到了k次还没有规律，就输出
	}
	printf("%d", st[q + (k - q )%(top - q + 1)]);
}

int main()
{
	cini();
	work();
	return 0;
}
```
总的来说，这个题规律确实不太好找，要多思考。

---

