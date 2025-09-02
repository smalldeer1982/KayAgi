# Equalizing by Division (hard version)

## 题目描述

简单版和困难版之间的唯一区别在于数组元素的数量。

给定一个数组$a$，包含$n$个整数。每次操作你可以选择任一$a_i$并且将其除$2$向下取整（也就是说，每次操作中你可以使$a_i:=\lfloor \frac{a_i}{2} \rfloor$）。

你可以对任何$a_i$进行任意次（可以是零次）操作。

你的任务是计算最小的操作次数使得至少$k$个数组中的数字相等。

别忘了在几次操作后可能会有$a_i=0$的情况出现，因此答案始终存在。

## 样例 #1

### 输入

```
5 3
1 2 2 4 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 3
1 2 3 4 5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 3
1 2 3 3 3
```

### 输出

```
0
```

# 题解

## 作者：andyli (赞：3)

将原序列中所有数进行处理，将当前处理的数计算所有它能变成的数以及变成那些数需要花费的**最小**次数，考虑如何最小化，只需将原序列从小到大依次处理即可。  
代码如下：  
```cpp
#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 200005;

int A[maxn];  // 原序列
int cnts[maxn]; // cnts[i]表示变成所有数均变成i需要的次数
int cntc[maxn]; // cntc[i]表示变成i的数量
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &A[i]);
    sort(A + 1, A + n + 1);
    for (int i = 1; i <= n; i++) {
        int x = A[i], sum = 0;
        while (x) {
            if (cntc[x] < k)
                cntc[x]++, cnts[x] += sum;
            x /= 2;
            sum++;
        }
    }
    int ans = -1u / 2;
    for (int i = 1; i <= maxn; i++)
        if (cntc[i] >= k)
            ans = min(ans, cnts[i]);
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：Guess00 (赞：2)

~~直接切D2~~

这题数据范围是$2e+5,$可以考虑$\Theta(n\log_2^n)$的算法.

我们可以在$\log$的复杂度下求出每个$a_i$可转换出的数$,$用数组记录$,$求每个数$,$就在外面加一层循环就行了$!$

$\mathbb{CODE:}$

```cpp
#include <bits/stdc++.h>
#define MAXN 200005
#define inf 0x3f3f3f3f
using std::sort;
int n,k,i,ans=inf,a[MAXN],v[MAXN],t[MAXN];
//其中v数组表示每个数出现次数,t数组表示转换到这个数的步数总和 
inline void read(int &x)  //快读 
{
	short negative=1;
    x=0;
    char c=getchar();
    while(c<'0' || c>'9')
    {
		if(c=='-')
			negative=-1;
		c=getchar();
	}
    while(c>='0' && c<='9')
        x=(x<<3)+(x<<1)+(c^48),c=getchar();
    x*=negative;
}
inline void print(int x)  //快输 
{
    if (x<0)
        putchar('-'),x=-x;
    if (x>9)
        print(x/10);
    putchar(x%10+'0');
}
signed main(void)
{
	read(n),read(k);
	for (i=1;i<=n;i++)
		read(a[i]);
	sort(a+1,a+n+1);   //排序确保答案最小 
	for (i=1;i<=n;i++)
	{
		int x=a[i],y=0;//y表示转换到其他数的步数 
		while (x)
		{
			v[x]++;
			t[x]+=y;
			ans=(v[x]==k && t[x]<ans)?t[x]:ans;
			//只统计等于k即可,大于k的情况答案定大于等于k的 
			y++;
			x/=2;
		}
	}
	print(ans);
	return 0;
} 
```

---

## 作者：A_Đark_Horcrux (赞：1)

对于每一个数，记录下它能变成什么数，以及变成该数需要多少步，

那么如果某一个数在某一时刻，有恰好 $k$ 个数能变为它，则更新答案。

注意，假设有两数 $x,y$ 且 $x>y$ ，对于它们要转化到的那个目标数字，肯定 $x$ 除 $2$ 的次数比 $y$ 多，

所以为了让答案最小，需要先对输入的数组从小到大排序qwq

```cpp
//部分代码
int n,k,x,minn=2e9+7,i,a[N],s[N],b[N];//si表示目前数转化成i需要多少步 bi表示有多少个数能转化成i
int main()
{
	n=read(),k=read();
	for(i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);//排序
	for(i=1;i<=n;i++)
	{
		int t=0,x=a[i];
		while(x)
		{
			s[x]+=t,b[x]++;//对现在的x更新s[x]和b[x]
			if(b[x]==k)//如果有恰好k个数能变为x
            minn=min(minn,s[x]);//更新答案
			t++,x/=2;//步数++，x变为原来1/2
		}
	}
	printf("%d\n",minn);
	return 0;
}

```


---

## 作者：b6e0_ (赞：1)

[CF题面传送门](https://codeforces.com/problemset/problem/1213/D2) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1213D2) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1213D2)

如果本篇觉得比较难理解，可以先看看弱化版中我的做法：[CF1213D1的题解](https://www.luogu.com.cn/blog/b6e0/tijie-CF1213D1)

设值域为 $m$。

开 $m$ 个 `vector`，第 $i$ 个中存了所有能变成 $i$ 的数变成 $i$ 所需要的步数。对于每一个数，求出它能变成的所有的数 $x$，将第 $x$ 个 `vector` 中加入步数。每个数最多能变成 $\log m$ 个数，所以这里的时空复杂度都是 $\mathcal O(n\log m)$。

然后，将每个 `vector` 排序，取前 $k$ 个更新答案即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010],s[200010];
vector<int>v[200010];
inline int read()//快读
{
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
inline void write(int x)//快写
{
	if(!x)
	{
		putchar('0');
		return;
	}
	int sta[10],tp=0;
	while(x)
	{
		sta[++tp]=x%10;
		x/=10;
	}
	while(tp)
		putchar(sta[tp--]+'0');
}
int main()
{
	int n=read(),k=read(),i,j,t,d,ans=2147483647;
	for(i=1;i<=n;i++)
	{
		a[i]=read();
		t=a[i];
		d=0;
		while(t)
		{
			v[t].push_back(d);//预处理
			t>>=1;
			d++;
		}
		v[0].push_back(d);//最后还剩下一个0
	}
	for(i=0;i<200005;i++)
	{
		sort(v[i].begin(),v[i].end());//排序
		if(v[i].size()>=k)//如果够取
		{
			for(j=0;j<k;j++)//取前k小的
				s[i]+=v[i][j];//其实这里开一个变量就行了
			ans=min(ans,s[i]);
		}
	}
	write(ans);
	return 0;
}
```
时间复杂度为 $\mathcal O(n\log m+m\log(n\log m))$。

---

## 作者：孑彧 (赞：1)

## D.Equalizing by Division

### 题意描述

给定一个数组$a$，包含$n$个整数。每次操作你可以选择任一$a_i$并且将其除2向下取整（也就是说，每次操作中你可以使$a_i=\lfloor \frac{a_i}{2} \rfloor$。

你可以对任何$a_i$进行任意次（可以是零次）操作。

你的任务是计算最小的操作次数使得至少$k$个数组中的数字相等。

别忘了在几次操作后可能会有$a_i=0$的情况出现，因此答案始终存在。

### 思路

一开始我是想找一个数，然后让所有的数都降到它附近，然后再去统计答案，但是我们发现这样的时间复杂度是会爆炸的。。。

所以我们需要去优化，不去找一个数让别的数降到它，而是去统计出每一个可以到达的数，以及到达它的最小步数

具体来说就是先由小到大排序，然后让每个数去不停的除以二，同时给到达的数累加上步数，需要注意的是，当一个数被到达的次数到达k之后，就不再需要去累加步数了，因为小的数永远比大的数更优，时间复杂度为$O(\sum_{i=1}^nlog_2a_i+nlog_2n)$，可以接受

### 代码

```c++
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define maxn 2000000
using namespace std;
int a[maxn]; 
int m[maxn],s[maxn];
int n,k;
int minn=231312312,maxx;
int main(){
	int n,k;
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		maxx=max(maxx,a[i]);
		m[a[i]]++;
		if(m[a[i]]==k){
			printf("0");
			return 0;
		}
	}
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++){
		int step=0;
		while(a[i]!=0){
			a[i]/=2;
			step++;
			if(m[a[i]]==k){
				continue;
			}
			m[a[i]]++;
			s[a[i]]+=step;
		}
		if(a[i]==0){
			m[0]++;
			s[0]+=step; 
		}
	}
	int ans=31312312;
	for(int i=1;i<=maxx;i++){
		if(m[i]>=k){
			ans=min(ans,s[i]);
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：览遍千秋 (赞：1)

这道题不算很难，我直接切的D2qwq

---

## $\mathrm{D1,D2}$的区别

观察D1和D2的区别，发现主要是$n,k$的范围不太一样，发现$a_i$的范围同样都是$\le 2 \times 10^5$，不像常规题目$a_i$的范围都是$\le 2 \times 10^9$，于是想到从$a_i$上面搞些事情。

---

## 解法

考虑枚举最后变成的数，只需要预处理出所有$a_i$可以变成的数$b_j$和需要的步数，按照变成的数$b$为第一关键字，需要的步数为第二关键字排序，枚举$b$即可。

---

## $\mathrm{code}$

```
#include<bits/stdc++.h>
using namespace std;
 
#define maxn 5000007
#define maxm 200007
 
//#define edgew
 
template <typename Tp>
void read(Tp &x){
	x=0;char ch=1;int fh;
	while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
	if(ch=='-'){
		fh=-1;ch=getchar();
	}
	else fh=1;
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	x*=fh;
}
 
struct node{
	int num,val;
};
 
int n,m;
node a[maxn];
 
void readin(){
	for(int i=1;i<=n;i++) read(a[i].num);
}
 
 
int tot;
 
bool comp(node a,node b){
	return a.num==b.num?a.val<b.val:a.num<b.num;
}
 
int cnt,ans=0x3f3f3f3f,ret;
int lim;
int main(){
	read(n);read(lim);tot=n;
	readin();
	for(register int i=1;i<=n;i++){
		int k=a[i].num;int p=0;
		do{
			k>>=1;;++p;
			a[++tot].num=k,a[tot].val=p;
		}while(k);
	}//
	sort(a+1,a+tot+1,comp);
	for(register int i=1;i<=tot;i++){
		if(a[i].num!=a[i-1].num||i==1){
			ret=a[i].val;cnt=1;
		}
		else{
			ret+=a[i].val,cnt++;
		}
		if(cnt>=lim) ans=min(ans,ret);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：HMZHMZHMZ (赞：0)

## 题意
读入两个数 $ n $ , $ k $ ,接下来读入 $ n $ 个正整数。一次操作中，你可以使 $ a_i = \left \lfloor \frac { a_i }{ 2 } \right \rfloor $ 。问最少有多少次后可以使数组中至少有 $ k $ 个数相同。

## 思路
我们发现 $ 1 \leq a_i \leq 2 \times 10^5 $ ,我们考虑枚举是哪一个数的个数 $ \ge k $ 。

可以开 $ 2 \times 10^5 $ 个优先队列，第 $ i $ 个优先队列中的元素记为将别的数字进行操作，最终达到 $ i $ 的次数。

然后在读入的时候对于每一个数处理一遍即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,k,m,maxn,ans=1e9;
priority_queue<int> q[N];
int main(){
    scanf("%d%d",&n,&k);
    for(register int i=1;i<=n;++i){
        scanf("%d",&m);
        int cnt=0;
        while(m){//对 m 能到的数做处理
            q[m].push(-cnt);//因为priority_queue是大根堆，所以要负着存。
            cnt++;
            m>>=1;
        }
        q[0].push(-cnt);
    }
    for(register int i=0;i<=2e5;++i){
        if(q[i].size()<k) continue;//如果个数小于k就不用管
        int sum=0;
        for(register int j=1;j<=k;++j) sum-=q[i].top(),q[i].pop();//将最小的次数加起来
        ans=min(ans,sum);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Dreamweaver (赞：0)

# Preface

提供一种比较好理解但是复杂度高的船锌做法qwq。

# Solution

## procedure：

1. 对值域上的每个数都开一个大根堆。

1. 遍历 $a$ 数组，对于数组中的某个数 $u$：

	- 将 $0$ 丢进第 $u$ 个堆；

	- 将 $1$ 丢进第 $\left\lfloor\dfrac{u}{2}\right\rfloor$ 个堆；

	- 将 $2$ 丢进第$\left\lfloor\dfrac{\left\lfloor\dfrac{u}{2}\right\rfloor}{2}\right\rfloor$个堆；

	- 以此类推，直到这个元素变为 $0$（不能再操作了）。

1. 遍历值域上的每个数，从每个堆中选择较小的 $k$ 个值，用它们的和更新答案。

## Detail:

因为题目只要求有 $k$ 个数相同，所以每个堆中最多只需有 $k$ 个元素。

插入元素的时候，先看一下堆中元素个数：

- 如果小于 $k$，直接加入；

- 否则，如果待加入的元素比堆顶小，就把堆顶扔掉，把这个元素丢进去（反悔贪心）。

同时维护一个 $sum$ 数组，$sum_i$ 表示第 $i$ 个堆所有元素的和，插入元素的时候顺便维护一下就好了。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 200010
#define inf 0x7f7f7f7f
#define int long long
#define re register
int n,k,sum[maxn],qwq=inf;
priority_queue<int>Q[maxn];//STL txdy!
signed main()
{
	cin>>n>>k;
	for(re int i=1;i<=n;++i)	
	{
		int u;
		cin>>u;
		for(re int j=0;u;++j,u>>=1)
			if(Q[u].size()<k)	Q[u].push(j),sum[u]+=j;//直接加入
			else
				if(j<Q[u].top())	sum[u]-=Q[u].top(),Q[u].pop(),Q[u].push(j),sum[u]+=j;/反悔贪心
	}
	for(re int i=0;i<=200000;++i)
		if(Q[i].size()>=k)	qwq=min(qwq,sum[i]);//用每个数更新答案
	cout<<qwq;//快乐输出qwq
	return 0;//不写return一时爽，考场爆零火葬场（大雾）
}

```

---

## 作者：youngk (赞：0)

发现绝大多数的人都和官方题解的思路类似，然而其实可以不用的排序的方法也能AC这道题，就是这个题目的数字范围小于等于200000，呢么统计每个值的个数，从小到大往大的方向bfs搜索，当搜索到值大于200000时就可以不再搜索了，这样的复杂度也是O(nlogn)，但在cf中跑的比官方题解快很多，而且元素的个数也可再增加

代码:

```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<set>
#define _USE_MATH_DEFINES
#include<math.h>
#include<queue>
#include<vector>
#include<limits.h>
#include<functional>
#include<stack>
typedef long long ll;
#pragma GCC optimize(2)
using namespace std;
inline void write(int x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
int a[300000];
int n, k, ans[300000];
int aans = INT_MAX;
struct node
{
	int num, times;
};
void bfs(int x)
{
	int num = k;
	queue<node> q;
	q.push({ x,0 });
	while (num > 0)
	{
		node u = q.front();
		q.pop();
		int xx = u.num, yy = u.times;
		if (xx > 200000)
		{
			ans[x] = -1;
			return;
		}
		if (num > a[xx])
		{
			num -= a[xx];
			ans[x] += a[xx] * yy;
		}
		else
		{
			ans[x] += num * yy;
			return;
		}
		if (xx == 0)
		{
			q.push({ 1,yy + 1 });
		}
		else
		{
			q.push({ (xx << 1),yy + 1 });
			q.push({ (xx << 1) + 1,yy + 1 });
		}

	}
}
signed main()
{
	n = read(), k = read();
	for (int i = 0; i < n; i++)
		a[read()]++;
	for (int i = 0; i <= 200000; i++)
	{
		bfs(i);
	}
	for (int i = 0; i <= 200000; i++)
	{
		if (ans[i] == -1)
			continue;
		aans = min(ans[i], aans);
	}
	write(aans);
	return 0;
}

```


---

## 作者：兮水XiShui丶 (赞：0)

我们可以发现,对于某一个数$i$,他能变成的数的个数为$log_2i+1$个,而且题目中$i$的权值也不大,所以我们可以开一个桶,按照从小到大的顺序处理每一个数字,每次处理的时候将它能变成的$log_2i$个数字在桶中的权值全部+1,同时花费就是从原来的i到目前的数字要除几次二,当发现有桶中的数字大于给定的$k$时,更新答案.

```cpp
#include<bits/stdc++.h>
using namespace std;
 
const int N = 2e5 + 10; 
 
int n,k,ans=2147483647;
int num[N];
struct Node{
	int val;
	int now;
}buck[N];
 
int main(){
	
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0); 
 
	cin>>n>>k;
	for(int i=1;i<=n;i++) { 
		cin>>num[i];
		buck[num[i]].now++;
		if(buck[num[i]].now>=k){
			cout<<"0"<<endl;
			return 0; 
		}
	} 
	sort(num+1,num+1+n);
	for(int i=1;i<=n;i++){
		int idx=1,tmp=num[i]/2;
		while(tmp){
			buck[tmp].now++;
			buck[tmp].val+=idx;
			if(buck[tmp].now>=k)
				ans=min(ans,buck[tmp].val);
			tmp/=2;
			idx++;
		}
	}
	cout<<ans<<endl;
	return 0;
} 
//
```

---

## 作者：Helium_Ship (赞：0)

介绍一种比较暴力的解法，对于 $\dfrac{a_i}{2^x}$，我们考虑建一个`vector`数组，下标对应 $\dfrac{a_i}{2^x}$，元素为 $x$，对于如果有大于 $k$ 个数的某个取值相同，我们就将`vector`排序，累加前 $k$ 个次数，答案即为所有和的最小值。

因为每个数 $a_i$ 最多贡献 $log(a_i)$ 个 $x$，而只有大于 $k$ 个数的某个取值相同，我们才进行后面的操作，所以时间复杂度应为 $O(\frac{\sum_{i=1}^{n}\log(a_i)}{k}\times(k \log(k)+k))$ 简化为 $O(n\log(v)\log(k))$，足矣通过这题。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[200010],ans=1e9,maxn;
vector<int> G[200010];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for (int i=1;i<=n;i++){
		cin>>a[i];
		int tmp=a[i];
		maxn=max(maxn,a[i]);
		int cnt=0;
		while (tmp){
			G[tmp].push_back(cnt);
			tmp>>=1;
			cnt++;
		}
	}
	for (int i=0;i<=200000;i++){
		if (G[i].size()<k)continue;
		sort(G[i].begin(),G[i].end());
		int sum=0;
		for (int j=0;j<k;j++){
			sum+=G[i][j];
		}
		ans=min(ans,sum);
	}
	cout<<ans;
	return 0;
}

```

---

