# Also Try Minecraft

## 题目描述

You are beta testing the new secret Terraria update. This update will add quests to the game!

Simply, the world map can be represented as an array of length $ n $ , where the $ i $ -th column of the world has height $ a_i $ .

There are $ m $ quests you have to test. The $ j $ -th of them is represented by two integers $ s_j $ and $ t_j $ . In this quest, you have to go from the column $ s_j $ to the column $ t_j $ . At the start of the quest, you are appearing at the column $ s_j $ .

In one move, you can go from the column $ x $ to the column $ x-1 $ or to the column $ x+1 $ . In this version, you have Spectre Boots, which allow you to fly. Since it is a beta version, they are bugged, so they only allow you to fly when you are going up and have infinite fly duration. When you are moving from the column with the height $ p $ to the column with the height $ q $ , then you get some amount of fall damage. If the height $ p $ is greater than the height $ q $ , you get $ p - q $ fall damage, otherwise you fly up and get $ 0 $ damage.

For each of the given quests, determine the minimum amount of fall damage you can get during this quest.

## 样例 #1

### 输入

```
7 6
10 8 9 6 8 12 7
1 2
1 7
4 6
7 1
3 5
4 2```

### 输出

```
2
10
0
7
3
1```

# 题解

## 作者：happy_dengziyue (赞：6)

### 1 视频题解

![](bilibili:BV1GW4y127vj)

### 2 思路

我们可以分成两个问题解决：从左到右和从右往左。

我们可以使用前缀和的方法。一个数组记录从 $1$ 到 $i$ 的花费，一个数组记录从 $n$ 到 $i$ 的花费。按照题意计算即可。

+ 如果 $x<y$，说明是从左往右走，输出从 $1$ 到 $y$ 的花费减去从 $1$ 到 $x$ 的花费即可；

+ 否则，说明是从右往左走，输出从 $n$ 到 $y$ 的花费减去从 $n$ 到 $1$ 的花费即可。

### 3 代码与记录

```cpp
#include<bits/stdc++.h>
using namespace std;
#define max_n 200000
int n;
int q;
long long a[max_n+2];
long long s1[max_n+2];
long long s2[max_n+2];
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1709B_1.in","r",stdin);
	freopen("CF1709B_1.out","w",stdout);
	#endif
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i)scanf("%lld",a+i);
	s1[1]=s2[n]=0;
	for(int i=2;i<=n;++i)s1[i]=s1[i-1]+max(a[i-1]-a[i],0ll);
	for(int i=n-1;i>=1;--i)s2[i]=s2[i+1]+max(a[i+1]-a[i],0ll);
	for(int i=1,x,y;i<=q;++i){
		scanf("%d%d",&x,&y);
		if(x<y)printf("%lld\n",s1[y]-s1[x]);
		else printf("%lld\n",s2[y]-s2[x]);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/80733428)

By **dengziyue**

---

## 作者：tangrunxi (赞：2)

题意
-
给出 $n$ 个柱子的高度，如果从一个高度 $i$ 的柱子跳到一个高度为 $j$ 的柱子，若 $i \le j$，则受到伤害值为 $0$，如果 $i \ge j$，则为 $i-j$。每次只能从一个柱子跳到相邻的柱子。问从 $s_j$ 号柱子到 $t_j$ 号柱子受到的伤害值是多少。共 $m$ 组询问。

题目分析
-
首先肯定不能跳回头路，必然会受到无意义的伤害，所以肯定要一口气从 $s_j$ 朝着目标方向跳，直至跳到 $t_j$。这个题如果暴力算每一组询问的值，时间复杂度 $O(nm)$，肯定超时。考虑记录从起点到任意一点的伤害值。若 $s_j<t_j$，用 $f(i)$ 表示从 $1$ 开始跳到 $i$ 所受伤害值。则答案就是 $f(t_j)-f(s_j)$。若 $s_j>t_j$，用 $k(i)$ 表示从 $n$ 开始跳到 $i$ 所受伤害值。则答案就是 $k(t_j)-k(s_j)$。时间复杂度 $O(m)$。

注意循环的起点和终点，不要循环多了 $1$ 次或少了 $1$ 次。

代码
-
```
    #include<bits/stdc++.h>
    using namespace std;
    long long a[100001],s,t,ans,b[100001],c[100001];
    int main(){
    	int n,m;
    	cin>>n>>m;
    	for(int i=1;i<=n;++i) cin>>a[i];
    	for(int i=2;i<=n;++i){
    		if(a[i-1]>a[i]) b[i]=b[i-1]+a[i-1]-a[i];
            else b[i]=b[i-1];
    	}
    	for(int i=n-1;i>=1;--i){
    		if(a[i+1]>a[i]) c[i]=c[i+1]+a[i+1]-a[i];
            else c[i]=c[i+1];
    	}
    	for(int i=1;i<=m;++i){
    		cin>>s>>t;
    		if(s<t) cout<<b[t]-b[s]<<endl;
    		if(s>t) cout<<c[t]-c[s]<<endl;
    	}
    	return 0;
    }
```


---

## 作者：PerssonBrown (赞：1)

> Update 2022.11.5：修复原有题解存在的错误之处，对部分表述不清的语句进行了修正。

---

每次任务，玩家需要从 $s_j$ 到 $t_j$ ，每次只能向左或向右移动一列，要求使最终受到的摔落伤害总和最少。可见只有两点一线才能受到最少的伤害。

首先想到的思路就是暴力求解，从 $s_j$ 到 $t_j$，每到达一列判断到达下一列是否会受到摔落伤害,最后将所有受到的摔落伤害加起来输出。

但是 $2\le n\le 10^5$ , $1\le m\le 10^5$ 。暴力会超时。

## 优化

![img](https://cdn.luogu.com.cn/upload/image_hosting/1gpo79v4.png?x-oss-process=image)

以从世界的第 $2$ 列到第 $7$ 列为例，暴力便是将第二行中对应的数据**相加**，即：$0+3+0+0+5=8$

可以发现：答案实际为一段**区间和**。

由此想到：可以计算第二行数据的**前缀和**，对于每次的询问只需输出 `arr[target] - arr[start];` 即可。

**特别注意**: 数据可能存在 $s_j > t_j$ ，所以需要两个数组存储不同方向的前缀和。

---

## 作者：HarryKane (赞：1)

## 题意简述
如果你从一个高的柱子跳到低的柱子，伤害值加上两个柱子的高度差，否则不用加。

对于每一个测试点，第一行两个数 $n$ 和 $m$，表示 $n$ 个数和 $m$ 个询问。

第二行输入 $n$ 个数，表示柱子的高度。

第 $3$ 行至第 $3+m$ 行，每行两个数 $x$ 和 $y$，表示从第 $x$ 个柱子跳到第 $y$ 个柱子。

输出最小的伤害值。

## 思路分析
前缀和。

设 $a1_i$ 表示从左到当前第 $i$ 根柱子要受到的伤害，$a2_i$ 表示从右到当前 第 $n - i$ 根柱子要受到的伤害。

输入 $x$ 和 $y$ 后，如果 $x < y$，输出 $a1_y - a1_x$ 最终答案，否则输出 $a2_x - a2_y$ 即可。

## Ac Code
```cpp
#include<stdio.h>
#pragma GCC optimize(2)
#define int long long
const int N=1e5;
int a[N+5],s1[N+5],s2[N+5],a1[N+5],a2[N+5];

void in(int &x){
	char c=getchar(),f=1;
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-'){
	   f=-1,
	   c=getchar();
	}
	for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	x*=f;
}

void _out(int x){
	if(x){
		_out(x/10);
		putchar('0'+x%10);
	}
}

void out(int x){
	if(x==0){
		putchar('0');
		return ;
	}
	else if(x>0) _out(x);
	else putchar('-'),_out(x*-1);
}

int ab(int x){
	if(x<0) return -x;
	else return x;
}

signed main(){
	for(int i=0;i<=N;i++) s1[i]=s2[i]=a1[i]=a2[i]=0;
	int n,m;
	in(n),in(m);
	for(int i=1;i<=n;i++) in(a[i]);
	for(int i=1;i<n;i++) s1[i]=(a[i]-a[i+1]>0)?a[i]-a[i+1]:0;
	for(int i=n;i>1;i--) s2[i]=(a[i]-a[i-1]>0)?a[i]-a[i-1]:0;//先把差值求出来
	a1[1]=a2[n]=0;
	for(int i=2;i<=n;i++) a1[i]=a1[i-1]+s1[i-1];
	for(int i=n-1;i>=1;i--) a2[i]=a2[i+1]+s2[i+1];//前缀和数组求出来
	while(m--){
		int x,y;
		in(x),in(y);
		if(x<y) out(ab(a1[y]-a1[x])),putchar('\n');
		else out(ab(a2[x]-a2[y])),putchar('\n');//如前面的思路
	}
	return 0;
}
```
注意，不开 $\texttt{long long}$ 见祖宗！

---

## 作者：_Ad_Astra_ (赞：1)

一道前缀和入门题。

我们可以按 $l \lt r$ 和 $l \gt r$ 分别去讨论。

+ 如果 $l \lt r$，则问题实际上是要求从 $l$ 到 $r$ 每次往下跳时跳下的高度之和，也就是 $\sum \limits_{i=l}^{r-1} max(0,a_i-a_{i+1})$。

+ 如果 $l \gt r$，则问题实际上是要求从 $r$ 到 $l$ 每次往下跳时跳下的高度之和，也就是 $\sum \limits_{i=l}^{r-1} max(0,a_{i+1}-a_i)$。

但是如果直接计算，复杂度为 $O(nm)$ 会TLE，所以我们可以用前缀和优化。

具体的话是开两个前缀和数组 $prel$ 和 $prer$，$prel_i$ 为 $\sum \limits_{j=l}^{i-1} \max(0,a_j-a_{j+1})$，也就是 $prel_{i-1} + \max(0,a_{i-1}-a_i)$，而$prer_i$ 为 $\sum \limits_{j=l}^{i-1} \max(0,a_{i+1}-a_i)$，也就是 $prer_{i-1} + \max(0,a_i-a_{i-1})$。

然后如果 $l \lt r$ 答案就为 $prel_r - prel_l$ （注意减去的是 $prel_l$ 而非 $prel_{l-1}$，否则会将 $a_{l-1} \gt a_l$ 的情况算上），而 $l \gt r$ 同理也为 $prer_l - prer_r$ 。

时间复杂度 $O(n)$ 。

code：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
//要开long long，不然答案可能会炸 
int n,m,a[100010],prel[100010],prer[100010];
void solve()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i]; 
	for(int i=2;i<=n;i++)
	{
		prel[i]=prel[i-1]+max(0LL,a[i-1]-a[i]);
		prer[i]=prer[i-1]+max(0LL,a[i]-a[i-1]);
	}
	while(m--)
	{
		int l,r;
		cin>>l>>r;
		if(l<r)cout<<prel[r]-prel[l]<<endl;
		else cout<<prer[l]-prer[r]<<endl;
	}	
}
signed main()
{
	solve();
	return 0;
}
```

---

## 作者：smallfang (赞：1)

## 题意简述

给你一个序列 $a_i$，表示这个点的高度， 一共有 $q$ 次询问，每次给定 $l, r$ 。询问 $l$ 到 $r$，下降量总和。

形式化来说就是

若 $l<r$ ，则 $ans = \sum^{r}_{i=l+1}a_i-a_{i-1}(a_{i-1}>a_i)$

若 $l>r$ ，则 $ans = \sum^{r-1}_{i=l}a_{i+1}-a_{i}(a_{i+1}<a_i)$

我们发现 $n$ 的大小较大。考虑前缀和维护两个序列分别为上升和下降。即可解决此题。时间复杂度 $O(Tn)$

### Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define F(i,s,n) for(int i=s;i<=n;i++)
#define R(i,s,n) for(int i=s;i>=n;i--)
#define re(n) cin>>n;

using namespace std;

typedef long long ll;

const int N = 3e5 + 5;
const ll INF=1e9+5;

int cur, cnt;
bool flag = false;
ll a[N], b[N];
ll d[N], f[N], ct[N];

// vector<int> g[N];

int in() {
	int x;
	cin >> x;
	return x;
}

int main() {
	int n, m;
	ios::sync_with_stdio(false);cin.tie(0);cin >> n >> m;
	F(i,1,n)cin>>a[i];b[0]=0;b[1]=0;F(i,2,n) {
		b[i]=b[i-1];
		if(a[i]<a[i-1]){
			b[i]+=(a[i-1]-a[i]);
	}
	}
	for (int i = n - 1; i >= 1; i -- ) {
		f[i] = f[i + 1];
		if(a[i] < a[i + 1]) {
			f[i] += (a[i + 1]-a[i]);
		}
	}
	while(m--){
		int l,r;
		cin>>l>>r;if(l>r) cout<<f[r]-f[l] << endl; else cout<<b[r]-b[l]<<endl;
	}
	return 0;
}

```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

本题应该使用前缀和算法。

首先我们可以发现，无论怎么走，只走一个方向从起点到终点才是最优解。

因为每次只能走一格，如果走其它路线，就会受到更多的摔落伤害。

但是，这么算，也会导致时间超限。

因此，我们引入前缀和。

设置两个前缀和数组，第一个数组表示从第 $0$ 格走到第 $i$ 格要受多少伤害，第二个数组表示从第 $n+1$ 格走到第 $i$ 格要受多少伤害。以上均设第 $0$ 格和第 $n+1$ 格高度为 $0$。

接着，判断询问是从左往右还是从右往左，并分别输出即可。

### 二、代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m;
long long a[100005];
long long sum1[100005],sum2[100005];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)//输入
	{
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++)//计算前缀和数组1
	{
		sum1[i]=sum1[i-1]+max((long long)0,a[i-1]-a[i]);
	}
	for(int i=n;i>=1;i--)//计算“前”缀和数组2
	{
		sum2[i]=sum2[i+1]+max((long long)0,a[i+1]-a[i]);
	}
	while(m--)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		if(l>r)//从右往左
		{
			printf("%lld\n",sum2[r]-sum2[l]);
		}
		else//从左往右
		{
			printf("%lld\n",sum1[r]-sum1[l]);
		}
	}
	return 0;
}

```


---

## 作者：Qerucy (赞：0)

对于这道题，数据范围之大让你无法直接按题意模拟，怎么办呢？考虑优化。

看到题目要求的是求区间的和，就可以考虑用前缀和来优化。

我们先从左往右计算一次前缀和，再从右往左计算一次前缀和，最后在询问的时候按照题意把预处理的两个前缀和拿出来求就可以了。

代码：

```cpp
#include<bits/stdc++.h>
 
using namespace std;
 
#define int long long //注意开long long
 
int t,n,m;
int a[1000010];
int qz[1000010];
int hz[1000010];
 
int get(int x){ //get函数求掉落伤害
    if(x>0) return x;
    return 0;
}
 
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){ //从左往右求前缀和
	    scanf("%lld",&a[i]);
	    if(i==1) qz[i]=0;
	    else qz[i]=qz[i-1]+get(a[i-1]-a[i]);
	}
	for(int i=n;i>=1;i--){ //从右往左求前缀和
	    if(i==n) hz[i]=0;
	    else hz[i]=hz[i+1]+get(a[i+1]-a[i]);
	}
	while(m--){
	    int x,y;
	    scanf("%lld%lld",&x,&y);
	    if(x>y) printf("%lld\n",hz[y]-hz[x]);
	    else printf("%lld\n",qz[y]-qz[x]);
	}
	return 0;
}
```


---

## 作者：tZEROちゃん (赞：0)

> 你在打 MC，有 $n$ 个由方块组成的柱子，从高度为 $p$ 的柱子跳到高度为 $q(p > q)$ 的柱子消耗 $p - q$ 的生命值。$Q$ 次询问，每次输入 $l,r$，问从 $l$ 到 $r$ 需要消耗多少生命值。

考虑对消耗的生命值做前缀和。

令 $k = a_{i - 1} - a_{i}$，如果 $k > 0$ 那就说明上一个柱子比这一个要高，那我们就 $s_i \leftarrow s_{i - 1} + k$，否则就不会消耗生命值，所有 $s_i \leftarrow s_{i - 1}$。

但是这样显然不对，注意题面并没有说是从左往右还是从右往左，上面那一段描述的是从左往右跳，那怎么办呢？反过来再处理一次就可以了！




```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); i ++)
#define per(i, r, l) for(auto i = (r); i >= (l); i --)

#define LL long long

LL s[1000010], a[1000010], ss[1000010];
 
int main() {
  LL n, q;
  cin >> n >> q;
  rep (i, 1, n) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; ++i) {
    if (a[i - 1] - a[i] > 0) s[i] = s[i - 1] + a[i - 1] - a[i];
    else s[i] = s[i - 1];  
  }
  for (int i = n; i >= 1; --i) {
    if (a[i + 1] - a[i] > 0) ss[i] = ss[i + 1] + a[i + 1] - a[i];
    else ss[i] = ss[i + 1];
  }
  while (q--) {
    LL l, r;
    cin >> l >> r;
    printf("%lld\n", l < r ? s[r] - s[l - 1] : ss[r] - ss[l - 1]);
  }
}
```

---

## 作者：cachejtt (赞：0)

## 题意
有长度为 $n$ 的一串柱子，每个高度为 $a_i$，给出 $m$ 次询问，每次要求你从第 $s_j$ 个柱子走到第 $t_j$ 个柱子。当你向上走时，不会产生任何代价，当你向下走时，你会受到跌落伤害，该伤害为两柱子之间的差值。问你该伤害总和最小值。每次只能走一步。

## 思路
每次只能走一步，意味着我们必定从 $s_j$ 开始一步一步走到 $t_j$，不走回头路得到的即为最小值。

所以一开始想到一个朴素算法，对于每次询问，去模拟走柱子的过程，若下降则将答案加上目前跌落伤害。

注意到时间复杂度不对，考虑前缀和优化，由于会出现从后向前走的情况，还需要一个后缀和。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define int long long 
using namespace std;
int n,m,x,a[200005],sum[200005],sum1[200005];
signed main(){
  std::ios::sync_with_stdio(0);
  cin>>n>>m;
  rep(i,1,n){
    cin>>a[i];
    if(i>1){
      x=a[i-1]-a[i];
      if(x>0)sum[i]=sum[i-1]+x;
      else sum[i]=sum[i-1];
    }
  }
  nrep(i,n,1){
    if(i<n){
      x=a[i+1]-a[i];
      if(x>0)sum1[i]=sum1[i+1]+x;
      else sum1[i]=sum1[i+1];
    }
  }
  int u,v;
  rep(i,1,m){
    cin>>u>>v;
    if(u<v){
      cout<<sum[v]-sum[u]<<"\n";
    }
    else{
      cout<<sum1[v]-sum1[u]<<"\n";
    }
  }
  return 0;
}
```

---

## 作者：BetaCutS (赞：0)

前缀和。

设 $p_i$ 为从左边到第 $i$ 格下坡的落差和，$q_i$ 为从左边到第 $i$ 格上坡的落差和，$p$ 和 $q$ 都可以通过前缀和算法求出来。

对于每次询问，如果 $x>y$，因为是从右向左走，所以从左到右的上坡变为了下坡，造成伤害。所以答案就是 $q_x-q_y$；如果 $x<y$，就是从左到右的下坡造成伤害，答案就是 $p_y-p_x$。

```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<queue>
#include<string>
#include<vector>
#define int long long
using namespace std;
const int INF=0x3f3f3f3f;
const int N=1e5+10;
const double eps=1e-5;
int read()
{
	char ch=getchar();
	int x=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48,ch=getchar();}
	return x*f;
}
int n,m,a[N],p[N],q[N];
signed main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[i]=read(),p[i]=p[i-1]+max(0ll,a[i-1]-a[i]),q[i]=q[i-1]+max(0ll,a[i]-a[i-1]);
	while(m--)
	{
		int x=read(),y=read();
		if(x>y)
			printf("%lld\n",q[x]-q[y]);
		else
			printf("%lld\n",p[y]-p[x]);
	}
	return 0;
}
```


---

## 作者：wuwenjiong (赞：0)

这次比赛的 `B` 题也是不难的。
## 题意
题面给出的题意有点复杂，这里给它简化一下：

给出一排柱子的高度，如果你从一个矮柱子走上一个高柱子，就**不会受到伤害**，否则就会受到值为这两个柱子的**高度差**的伤害。

然后多次给出一个起点和一个终点，依次求出你从起点到终点**最少**要受到多少伤害。
## 思路
首先不难发现，直接从起点到终点的策略就是最优的。

然后看数据范围 $n,m\le 10^5$，显然直接暴力会`TLE`，继续想，这个受伤害的机制是满足前缀和性质。

又因为起点既可以在终点的左边，又可以在终点的右边，所以就应该要前后都扫一遍跑前缀和。

这样，预处理前缀和 $O(n)$，单次查询 $O(1)$，总时间复杂度 $O(n+m)$，过这题没问题。

最后，记得开 `long long`。

代码如下：
```cpp
for(int i=1;i<=n;i++){
        cin>>a[i];
        s[i]=s[i-1];
        if(a[i]<a[i-1])
            s[i]=s[i]+a[i-1]-a[i];
    }
    for(int i=n;i>=1;i--){
        ss[i]=ss[i+1];
        if(a[i]<a[i+1])
            ss[i]=ss[i]+a[i+1]-a[i];
    }
    while(m--){
        int x,y;
        cin>>x>>y;
        if(x<=y)
            cout<<s[y]-s[x]<<'\n';
        else
            cout<<ss[y]-ss[x]<<'\n';
    }
```


---

## 作者：Starw (赞：0)

### 题意：

你有一个 $1$ 到 $n$ 的序列 $a$，代表每个格子的高度，若你在 $x$，则你可以走到 $x+1$ 或 $x-1$。若你从一个高为 $p$ 的格子走到一个比它矮的高为 $q$ 格子会受到 $p-q$ 的伤害，若走到一个比它高的格子则不会受到伤害，求从 $s$ 走到 $t$ 所受到的最少的伤害。

### 思路：

显而易见，直接从 $s$ 走到 $t$ 是最优的，所以要不你一直向前走，要不一直向后走，我们可以算出所有从一个格子向前或向后走所会受到的伤害。

所以我们可以开两个前缀和数组，分别记录向前走和向后走所受到伤害和，$s$ 到 $t$ 所受到的伤害就为到 $t$ 的伤害和减去到 $s$ 的伤害和。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005];
long long sum1[100005],sum2[100005];//不开long long见祖宗
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){//向前走的前缀和
		scanf("%d",&a[i]);
		sum1[i]=sum1[i-1];
		if(a[i-1]>a[i])sum1[i]+=a[i-1]-a[i];//若i-1比i的高度高则计算伤害
	}
	for(int i=n;i;i--){//向后走的前缀和
		sum2[i]=sum2[i+1];
		if(a[i+1]>a[i])sum2[i]+=a[i+1]-a[i];//若i+1比i的高度高则计算伤害
	}
	while(m--){
		int s,t;
		scanf("%d%d",&s,&t);
		if(s<t)printf("%lld\n",sum1[t]-sum1[s]);//若s<t则是向前
		else printf("%lld\n",sum2[t]-sum2[s]);//若s>t则是向后
	}
	return 0;
}
```


---

## 作者：happybob (赞：0)

## 题意

给定 $n$ 个数的序列 $a_1, a_2, \cdots, a_n$。$m$ 次询问，每次询问给定两个数 $l, r$，需要输出 $\begin{cases}
    \sum \limits_{i=l}^{r-1} \max\{0,a_{i}-a_{i+1}\} && l \leq r \\ \sum \limits_{i=r}^{l-1} \max\{0,a_{i+1}-a_i\} && r < l
\end{cases}$。

## 解法

先考虑暴力，显然就是区间求和，但是由于 $2 \leq n \leq 10^5$，$1 \leq m \leq 10^5$。这个复杂度是 $O(nm)$ 的，显然超时。但是赛时好像有人暴力卡常过了 pretest，不过被 hack 了。

显然区间求和是可以优化的，因为这题没有修改操作，可以预处理出两个前缀和数组，$O(n)$ 预处理，$O(1)$ 单次查询。

当然区间和也可以用线段树或树状数组等数据结构，复杂度 $O(m \log n)$。我赛时就用的是树状数组。

---

