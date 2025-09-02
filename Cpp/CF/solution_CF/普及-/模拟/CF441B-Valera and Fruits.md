# Valera and Fruits

## 题目描述

Valera很爱他的花园，因为那里生长着n棵果树。

今年他将迎来一场大丰收！第i棵树上会结出bi个果实，它们将在第ai天全部成熟。不幸的是，这些果子将很快枯萎，因此Valera只能在第ai天和第ai+1天摘下它们。（所有不在指定的两天内摘下的果子，都不可食用）

Valera的动作不是很快，但他也有自己的优势。他已经准备好了，以保证每天都可以工作。一天，Valera最多可以摘下v个果子，这些果子有可能是同一棵树上的，也有可能不是。那么，在合理安排日程表的情况下，Valera最多可以收获多少个果子？

## 样例 #1

### 输入

```
2 3
1 5
2 3
```

### 输出

```
8
```

## 样例 #2

### 输入

```
5 10
3 20
2 20
1 20
4 20
5 20
```

### 输出

```
60
```

# 题解

## 作者：中缀自动机 (赞：0)

这题是一题贪心题。

首先，我们先证明一个结论。

当前是第 $n$ 天，要优先处理第 $n$−$1$ 天的果实，如果还能处理的话就处理今天的果实。

------------

这个贪心可以很容易的证明出来，因为第 $n−1$ 天的果实可以在第 $n$ 天处理，但是不能在第 $n+1$ 天处理，而第 $n$ 天的果实还可以在第 $n+1$ 天处理。当然，第 $n$ 天处理完第 $n$−$1$ 天的果实后还可以处理第 $n$ 天的果实，可以为第 $n+1$ 天减轻工作量。

对于怎么计算答案，可以开一个桶，存储当天的果实，枚举到第 $\max\{d_{i}\}+1$ 天，用变量 $ans$ 存储答案。

时间复杂度为 $\mathcal O(n+\max\{d_{i}\})$ 可以 $AC$ 了。


------------
代码实现：

```cpp
#include<iostream>
#include<algorithm> 
using namespace std;
const int N=3e6+5;
long long n,m,k,d,sum[N],maxn=0,ans=0,tmp;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
	    cin>>d>>m;
		sum[d]+=m;
		maxn=max(maxn,d);
	}
	for(int i=0;i<=maxn+1;i++){
		if(i==0){
			if(sum[i]<=k){
			    ans+=sum[i];
				sum[i]=0;
			}
			else{
				ans+=k;
				sum[i]-=k;
			}
		}
		else{
			if(sum[i-1]<=k){
				ans+=sum[i-1];
				tmp=sum[i-1];
				sum[i-1]=0;
			}
			else{
				ans+=k;
				tmp=k;
				sum[i-1]-=k;
				continue;
			}
			if(sum[i]<=k-tmp)
				ans+=sum[i];
				sum[i]=0;
			else{
				ans+=k-tmp;
				sum[i]-=(k-tmp);
			}
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：xiezihanAKIOI (赞：0)

题外话：这道题好像和挖土机杯重了吧。~~（我是不会告诉你们我挖土机杯 AC 的代码调了半天才过的。）~~

现在看来我当时好像个刚学编程的萌新。

思路：一道贪心题。对于每一个蔬菜，我们按照他们成熟的时间排序。然后从 $1$ 到 $n$ 枚举每个蔬菜的个数，如果你当天还能摘就当天摘，否则第二天摘。实在摘不了就~~给我吃~~只能让他烂在树上。

大家可以凭借代码里的注释慢慢消化（不要直接复制哦~）。

```
#include <bits/stdc++.h>
#define int long long
#define min(a, b) (a > b ? b : a)
#define max(a, b) (a > b ? a : b)

using namespace std;

struct node {
	int d, m;
} a[300005];

int vis[300005], n, k, maxn, cnt;

bool cmp (node a, node b) {
	if (a.d != b.d) return a.d < b.d;
	return a.m > b.m;
}

signed main () {
	ios::sync_with_stdio (false), cin.tie (0), cout.tie (0);
	cin >> n >> k;
	for (int i = 1 ; i <= n ; i++) {
		cin >> a[i].d >> a[i].m;
	}
	sort (a + 1, a + 1 + n, cmp); \\按照时间排序。 
	for (int i = 1 ; i <= n ; i++) { 
		if (vis[a[i].d] < k && a[i].m) { \\如果第一天还能摘并且这颗果树上还有果实。 
			int l = k - vis[a[i].d]; \\判断是否够摘。 
			if (l < a[i].m) { \\如果够摘。 
				vis[a[i].d] = k; \\今天摘满。 
				a[i].m -= l; 
			} else {
				vis[a[i].d] += a[i].m; \\够摘就全部摘了。 
				a[i].m = 0;
			}
		}
		if (vis[a[i].d + 1] < k && a[i].m) { \\第一天不够摘，第二天接着摘。 
			int l = k - vis[a[i].d + 1]; \\同上。 
			if (l < a[i].m) {
				vis[a[i].d + 1] = k;
				a[i].m -= l;
			} else {
				vis[a[i].d + 1] += a[i].m;
				a[i].m = 0;
			}
		}
		maxn = max (maxn, a[i].d);
	}
	int cnt = 0;
	for (int i = 1 ; i <= maxn + 1 ; i++) { \\把每天摘的个数相加。 
//		cout << vis[i] << ' ';
		cnt += vis[i];
	}
	cout << cnt;
	return 0;
}
```

---

## 作者：OoXiao_QioO (赞：0)

# 前言

和月赛撞题了。。。。

# 思路

把每一次太阳日的时间放到时间轴上面，进行模拟操作。

设排序后最后一天的时间为 $t$，那么我们需要模拟到 $a+1$ 天（毕竟最后一天还可以在击毁一次），判断每一天是否可以击毁，其中判断条件为如果第 $i$ 天正好对应第 $d_i$ 天或第 $d_i+1$ 天，也就是判断这一天可不可以击毁陨石。转换成编程语言就是 `i-d[i]<=1`。

如果满足条件，那么再来判断一下还可不可以再击毁陨石，即 `k>m[i]`,满足条件，就让累加器 $s$ 加上 `m[i]`，并且消耗了当天可以击毁的陨石数量，将 $k$ 减去 `m[i]`。如果这一天只能击毁一半，就先把今天要击毁的陨石击毁一部分，即 `d[i] -= k`，同时把击毁的陨石计入累加器，`s += k`。

分析的还算透彻吧，接下来给大家放代码。

# 代码

```cpp
struct node//用结构体封装代码更有条理性。 
{
	int d,m;//d,m 意义与题意相符。 
}a[300001];
bool cmp(node a,node b)
{
	return a.d<b.d;
}
signed main()
{
	int n,k,ma=INT_MIN,s=0;
	int i,j;
	cin>>n>>k;
	for(i=1;i<=n;i++)
	{
		cin>>a[i].d>>a[i].m;
		ma = max(a[i].d,ma);
	}
	sort(a+1,a+1+n,cmp);
	for(i=1;i<=ma+1;i++)//枚举到 max + 1 天
	{
		int t = k;//注意到文章讲解的只是针对一天的情况，多天时需要用 t 来储存 k 变量。 
		for(j=1;j<=n;j++)
		{
			if(i-a[j].d==0||i-a[j].d==1)//这一天可以击毁陨石 
			{
				if(t<a[j].m)//一天击毁不了全部 
				{
					a[j].m -= t;
					s += t;
					break;
				}
				else//可以击毁全部 
				{
					t -= a[j].m;
					s += a[j].m;
					a[j].m = 0;//击毁完了 
				}
			}
		}
	}
	cout<<s<<endl;//输出 
    return 0;//结束 
}
```


---

## 作者：Need_No_Name (赞：0)

# Solution For CF441B

## 题意

阿伟有一片果树林，其中有 $n$ 颗果树，第 $i$ 颗果树上有 $a_i$ 个果子，在第 $t_i$ 天全部成熟。果子成熟后只能再待一天，再下一天就会腐烂不能要了（也就是第 $j$ 天没有摘完的果子第 $j + 1$ 还能摘）。阿伟每天最多能摘 $v$ 个果子，求这些天后最多能摘多少个。

## 思路

我们可以把整个过程放在时间轴上。

初始时将第 $i$ 天成熟的所有的果实记在 $d_i$ 里（可以看做一个桶），然后记下这一天的剩下的果实 $nxtnum$ ，然后在第二天的时候优先考虑昨天没摘完的果子即可。

其余直接暴力枚举即可。

## 代码

```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;
const int N = 3e3 + 10;
struct Tree
{
	int day;
	int f;
}t[N];
int n, v;
int nxtday;
int daynum[N];
signed main()
{
	int maxd = -INT_MAX;
	cin >> n >> v;
	for(int i = 1; i <= n; i++)
	{
		cin >> t[i].day >> t[i].f;
		maxd = max(maxd, t[i].day);
		daynum[t[i].day] += t[i].f;
	}
	nxtday = 0;
	int ans = 0;
	for(int i = 1; i <= maxd + 1; i++)
	{
		int num = daynum[i] + nxtday;
		if(daynum[i] == 0 && nxtday == 0) continue;
		else
		{
			if(num <= v)
			{
				ans += num;
				nxtday = 0;
				continue;
			}
			else
			{
				if(nxtday >= v)
				{
					ans += v;
					nxtday -= v;
					nxtday = 0;
					nxtday = daynum[i];
					continue;
				}
				else
				{
					ans += v;
					int lft = daynum[i] - (v - nxtday);
					nxtday = 0;
					nxtday = lft;
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：221B (赞：0)

**这道题没有人写题解？本蒟蒻来水一发（逃**

这道题不算太难，但是也有需要注意的几点。具体请见代码详解（大佬勿喷）
```cpp
#include<bits/stdc++.h>
using namespace std;
struct px {//定义结构体，方便运算
	int a;
	int b;
} x[100001];
bool cmp(px x,px y) {//结构体排序，将每棵果树成熟的日期从小到大排列，方便计算采摘日期
	return x.a<y.a;
}
inline int read() {//水一波快读快写的函数。。。
	int X=0,w=0;//我是不会告诉你快读比cin和scanf都快的
	char ch=0;
	while(!isdigit(ch)) {
		w|=ch=='-';
		ch=getchar();
	}
	while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
	return w?-X:X;
}
inline void write(int x) {//我当然不会告诉你快写比cout和printf都快的
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
void fanhui(int &x){//自己写的清零函数，比较方便
	x=0;
}
int main() {
	int n=read(),v=read()/*将题目中的n,v用快读读入*/,s=0,maxn=-1;
	for(int i=1; i<=n; i++) {
		x[i].a=read();//输入到定义的结构体中
		x[i].b=read();//x[i].a代表第i棵树上的果子会在哪一天完全成熟，x[i].b代表第i棵树上会结出多少个果子
		maxn=max(x[i].a,maxn);//将果子最晚成熟的日期储存起来
	}
	sort(x+1,x+n+1,cmp);//将每棵果树成熟的日期从小到大排列
	for(int i=1; i<=maxn+1; i++) {//从第一天开始到最后一天，由于每棵果树有两天的采摘时间，最晚成熟的果树也是一样的，所以要在原来的天数上+1，i代表第i天
		int k=v;
		for(int j=1; j<=n; j++) {
			if(i-x[j].a==0||i-x[j].a==1) {//如果这棵果树在采摘时间内
				if(k<x[j].b) {//如果这棵果树上的果子比每天最多可以摘下的果子数还多
					x[j].b-=k;//摘下这棵果树上能摘的果子
					s+=k;//计入总数
					break;//这一天的果子已经采集完毕，后面的果树不能再采摘，break
				} else {//否则
					k-=x[j].b;//摘下这棵树上的所有的果子，将这一天最多能摘的果子减去这棵树上的果子，剩下这一天还可以摘的果子
					s+=x[j].b;//计入总数
					fanhui(x[j].b);//将这棵果树清零
				}
			}
		}
	}
	write(s);//输出
	return 0;//养成好习惯
}
```
有不明白或有错误想要指出的，请随时@我，本蒟蒻真心为大家答疑！（虽然本蒟蒻很蒟）

---

