# [ARC147B] Swap to Sort

## 题目描述

现有一个$1$到$N$的排列$ P=(P_1,P_2,\ldots,P_N) $ 。你可以重复执行以下两种操作来使$P$从小到大排序。

- 操作$A:$选择一个整数$i$满足$1\ \leq\ i\ \leq\ N-1$，然后交换$P_i$和$P_{i+1}$。
- 操作$B:$选择一个整数$i$满足$1\ \leq\ i\ \leq\ N-2$，然后交换$P_i$和$P_{i+2}$。

请找出一个满足以下要求的操作序列
* 操作$A$的数量最少
* 操作的总数不超过$10^5$

在题目条件的约束下，我们可以证明合法的解总是存在的

## 说明/提示

- $ 2\ \leq\ N\ \leq\ 400 $
- $ 1\ \leq\ P_i\ \leq\ N\ \,(1\ \leq\ i\ \leq\ N) $
- $ P_i\ \neq\ P_j\ \,(1\ \leq\ i\ <\ j\ \leq\ N) $
- 输入均为正数

## 样例 #1

### 输入

```
4
3 2 4 1```

### 输出

```
4
A 3
B 1
B 2
B 2```

## 样例 #2

### 输入

```
3
1 2 3```

### 输出

```
0```

## 样例 #3

### 输入

```
6
2 1 4 3 6 5```

### 输出

```
3
A 1
A 3
A 5```

# 题解

## 作者：DaiRuiChen007 (赞：1)

# ARC147B 题解

## 思路分析

注意到仅利用 B 操作就可以把 $P$ 的奇数下标和偶数下标的元素全部按递增顺序排序。

因此原问题就转化成如何把所有奇数位上的偶数放到偶数位上，偶数位上的奇数放到奇数位上，注意到每次交换至多把其中的两个错位的数字，且可以证明这样的操作是存在的，只需要先利用 B 操作把所有错位的数字一起放到 $P$ 的开头，可以证明两种错位的数字是一样多的，所以然后用 A 操作两两交换即可。

时间复杂度 $\Theta(n^2)$，操作次数最多大概在 $60000$ 次左右。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=401;
int a[MAXN];
struct node {
	char op;
	int pos;
};
vector <node> res;
signed main() {
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=n-2;++j) {
			if((a[j+2]%2!=j%2)&&(a[j]%2==j%2)) {
				res.push_back((node){'B',j});
				swap(a[j],a[j+2]);
			}
		}
	}
	for(int i=1;i<=n;++i) {
		if(a[i]%2!=i%2) {
			res.push_back((node){'A',i});
			swap(a[i],a[i+1]);
		}
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=n-2;++j) {
			if(a[j]>a[j+2]) {
				res.push_back((node){'B',j});
				swap(a[j],a[j+2]);
			}
		}
	}
	printf("%d\n",(int)res.size());
	for(auto x:res) printf("%c %d\n",x.op,x.pos);
	return 0;
}
```

---

## 作者：CHNZhang (赞：1)

一道有趣的思维题

我们要让操作 $A$ 的次数最少，我们先考虑一下哪些操作 $A$ 是必要的。

操作 $A$ 可以让一个奇数位上的数和一个偶数位上的数交换。操作 $B$ 可以让奇数位奇数位，偶数位与偶数位之间交换。所以，如果一个奇数在偶数位上，或者一个偶数在奇数位上，就必须使用操作 $A$ 进行交换。

我们考虑怎么让所有奇数到奇数位上，所有偶数到偶数位上。

设第 $i$ 位上的数的奇偶性与 $i$ 的奇偶性不匹配，重复执行以下操作：
* 如果第 $i+1$ 位上的数的奇偶性与 $i+1$ 的奇偶性也不匹配，执行操作 $A$，结束循环
* 否则执行操作 $B$，将第 $i$ 位上的数与第 $i+2$ 位上的数交换，并且使当前的 $i$ 加 $2$。

从 $1$ 到 $N$ 遍历序列，重复执行上述操作，我们就可以让所有奇数到奇数位上，所有偶数到偶数位上。

这时，我们只需要用操作 $B$ 分别对奇数位和偶数位排序就行了，因为 $N$ 很小，并且要得到操作序列，所以采用冒泡排序。

在操作的同时记录操作即可得到答案。

```cpp
#include<bits/stdc++.h>
#define rint register int
#define LL long long int
using namespace std;
inline int read()
{
	int x = 0, ff = 1; char s = getchar();
	while (s < '0' || s > '9') { if (s == '-') ff = -ff; s = getchar(); }
	while (s >= '0' && s <= '9') { x = x * 10 + s - '0'; s = getchar(); }
	return x * ff;
}
int n,a[505],tot;
struct node
{
	char opt;
	int p;
}opt[10000005];
void workA(int p)
{
	int now=p;
	while((a[now]%2)!=(now%2))
	{
		if(a[now+1]%2!=(now+1)%2)
		{
			opt[++tot].opt='A';
			opt[tot].p=now;
			swap(a[now],a[now+1]);
			return ;
		}
		else if(now<n-1)
		{
			opt[++tot].opt='B';
			opt[tot].p=now;
			swap(a[now],a[now+2]);
			now+=2;
		}
	}
}
int main()
{
	rint i,j;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			if(a[j]%2!=j%2)
			{
				workA(j);
				break;
			}
	}
	for(i=1;i<=n;i+=2)
	{
		for(j=1;j+2<=n;j+=2)
		{
			if(a[j]>a[j+2])
			{
				opt[++tot].opt='B';
				opt[tot].p=j;
				swap(a[j],a[j+2]);
			}
		}
	}
	for(i=2;i<=n;i+=2)
	{
		for(j=2;j+2<=n;j+=2)
		{
			if(a[j]>a[j+2])
			{
				opt[++tot].opt='B';
				opt[tot].p=j;
				swap(a[j],a[j+2]);
			}
		}
	}
	cout<<tot<<endl;
	//for(i=1;i<=n;i++)cout<<a[i]<<" ";
	for(i=1;i<=tot;i++)
		printf("%c %d\n",opt[i].opt,opt[i].p);
	return 0;
}

```


---

## 作者：Davis1 (赞：0)

注意到两种操作的作用不同。要 $A$ 操作最少，就得知道什么时候必须要用 $A$ 操作。

下面把下标为偶数的位置称为偶数位，并且如果一个数是奇数（或偶数），且这个数在奇数（或偶数）位上，就称这个数是合法的。

把原始序列分为两部分，一部分是偶数位上的数，一部分是奇数位上的数。发现可以用 $B$ 操作把这两部分分别排好序，因为 $B$ 操作只能交换偶数位和偶数位，或奇数位和奇数位，上的数，所以用冒泡排序可以将两部分分别排序好。

因为原序列是 $1$ 到 $n$ 的排列，所以排序完后一定是 $1,2,3,$ $\dots$ $,n $ ，想只用 $B$ 操作就可以把一个序列排成这样，那么这个序列中每个数都得是合法的。为什么？因为如果每个数都合法，那么奇数位上的数一定是小于等于 $n$ 的奇数的排列，用 $B$ 操作排完序后一定是 $1,3,5,7,$ $\dots$，偶数位也一样，所以两部分拼起来就是 $1,2,3,$ $\dots$ $,n$  了。

那么当有数字不合法怎么办？用 $B$ 操作肯定不能让它合法，那么只能用 $A$ 操作了。那把它和谁交换呢？肯定不能跟另一个合法的数交换，这样那个数就变得不合法了，因为只要有一个奇数不合法，那么还会有一个偶数也会不合法，那么我们就可以用 $B$ 操作把它们俩放挨着，再用 $A$ 操作把两个数交换就行了（因为放挨着太麻烦了，索性直接把所有不合法数都放在开头就行了，也不会多用 $A$ 操作）。最后万事具备，用 $B$ 操作排序就好了（因为一次只能交换两个相邻奇数或偶数位上的数，所以用冒泡排序实现）。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=401;
int a[N];
struct u{
	char c;//操作种类 
	int id;//题目中的i 
};
vector<u> res;
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n-2;j++) 
			if((a[j+2]%2!=j%2)&&(a[j]%2==j%2)){
				res.push_back((node){'B',j});
				swap(a[j],a[j+2]);
			}//把不合法数都放在开头 
	for(int i=1;i<n;i++)
		if(a[i]%2!=i%2){
			res.push_back((node){'A',i});
			swap(a[i],a[i+1]);
		}//用A操作使两个相邻的不合法数变得合法 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n-2;j++)
			if(a[j]>a[j+2]){
				res.push_back((node){'B',j});
				swap(a[j],a[j+2]);
			}//用B操作冒泡排序 
	cout<<(int)res.size()<<endl;
	for(auto x:res) cout<<x.c<<" "<<x.id<<endl;
	return 0;
}
```
谢观看。

---

## 作者：XYQ_102 (赞：0)

## 思路
考虑最终选出的所有位置，从小到大排序，令第 $\lfloor \frac n2 \rfloor$ 个为 $x$，则排序时排在 $x$ 左边，且其位置的值 $<x$ 的变量如果能往右移哪怕 $1$ 个位置，也是好的，但是为什么不能移，因为它已经在对应线段的右端点了。排序时排在 $x$ 右边的同理。这启发我们可以枚举所在的区间。把所有 $l_i$ 和 $r_i$ 排序并去重，枚举排好的序列中相邻的 $2$ 个位置 $a,b$，计算 $a \leq x \leq b$ 时的最优答案。找出所有 $r_i < a$ 的线段，它们对应的值只能选 $r_i$，令这样的线段有 $c\times a$ 个。所有 $l_i > b$ 的只能选 $l_i$，令这样的线段有 $c\times b$ 个。其他的显然是选与 $x$ 相同最好。如果 $c\times a \geq c\times b$，显然 $x$ 选 $a$ 比较好，否则 $x$ 选 $b$ 比较好。记录几个部分的线段数量、端点位置之和等信息即可 $O(1)$ 计算。

时间复杂度 $O(n\times \log n)$。
## AC Code
```cpp
#include <bits/stdc++.h>
 
#define rep(i,n) for(int i=0;i<n;++i)
#define repn(i,n) for(int i=1;i<=n;++i)
#define LL long long
#define pii pair <LL,LL>
#define pb push_back
#define fi first
#define se second
#define mpr make_pair
 
using namespace std;
 
LL n,l[300010],r[300010],lsum=0,rsum=0,lcnt=0,rcnt=0,stat[300010],ans=LONG_LONG_MAX;
vector <pair <LL,pii> > op;
vector <LL> L;
 
int main()
{
  cin>>n;
  LL addi=0;
  rep(i,n)
  {
    scanf("%lld%lld",&l[i],&r[i]);
    op.pb(mpr(l[i],mpr(-1,i)));op.pb(mpr(r[i],mpr(1,i)));
    stat[i]=1;
    L.pb(l[i]);
  }
  sort(L.begin(),L.end());
  rep(i,L.size())
  {
    addi+=L[i]*rcnt-rsum;
    rsum+=L[i];++rcnt;
  }
 
  sort(op.begin(),op.end());
  rep(i,op.size()-1)
  {
    if(op[i].se.fi==-1)
    {
      stat[op[i].se.se]=0;
      --rcnt;rsum-=l[op[i].se.se];
      addi-=rsum-l[op[i].se.se]*rcnt;
    }
    else
    {
      stat[op[i].se.se]=1;
      addi+=r[op[i].se.se]*lcnt-lsum;
      ++lcnt;lsum+=r[op[i].se.se];
    }
    LL lb=op[i].fi,ub=op[i+1].fi,mid=n-lcnt-rcnt,act=(lcnt>=rcnt ? lb:ub);
    LL res=0;
    res+=act*(mid+rcnt)*lcnt-lsum*(mid+rcnt);
    res+=rsum*(mid+lcnt)-act*(mid+lcnt)*rcnt;
    ans=min(ans,res+addi);
    //cout<<lb<<' '<<ub<<' '<<lcnt<<' '<<rcnt<<' '<<res<<' '<<lsum<<' '<<rsum<<' '<<act<<endl;
  }
  cout<<ans<<endl;
  return 0;
}
```

---

