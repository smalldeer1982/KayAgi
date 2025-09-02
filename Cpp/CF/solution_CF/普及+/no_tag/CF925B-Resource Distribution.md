# Resource Distribution

## 题目描述

One department of some software company has $ n $ servers of different specifications. Servers are indexed with consecutive integers from $ 1 $ to $ n $ . Suppose that the specifications of the $ j $ -th server may be expressed with a single integer number $ c_j $ of artificial resource units.

In order for production to work, it is needed to deploy two services $ S_1 $ and $ S_2 $ to process incoming requests using the servers of the department. Processing of incoming requests of service $ S_i $ takes $ x_i $ resource units.

The described situation happens in an advanced company, that is why each service may be deployed using not only one server, but several servers simultaneously. If service $ S_i $ is deployed using $ k_i $ servers, then the load is divided equally between these servers and each server requires only $ x_i / k_i $ (that may be a fractional number) resource units.

Each server may be left unused at all, or be used for deploying exactly one of the services (but not for two of them simultaneously). The service should not use more resources than the server provides.

Determine if it is possible to deploy both services using the given servers, and if yes, determine which servers should be used for deploying each of the services.

## 说明/提示

In the first sample test each of the servers 1, 2 and 6 will will provide $ 8 / 3 = 2.(6) $ resource units and each of the servers 5, 4 will provide $ 16 / 2 = 8 $ resource units.

In the second sample test the first server will provide $ 20 $ resource units and each of the remaining servers will provide $ 32 / 3 = 10.(6) $ resource units.

## 样例 #1

### 输入

```
6 8 16
3 5 2 9 8 7
```

### 输出

```
Yes
3 2
1 2 6
5 4```

## 样例 #2

### 输入

```
4 20 32
21 11 11 12
```

### 输出

```
Yes
1 3
1
2 3 4
```

## 样例 #3

### 输入

```
4 11 32
5 5 16 16
```

### 输出

```
No
```

## 样例 #4

### 输入

```
5 12 20
7 8 4 11 9
```

### 输出

```
No
```

# 题解

## 作者：S00021 (赞：1)

### 题号：CF925B/CF967D

### 题目大意：
给定 $n$ 个存储器和两个任务，第 $i$ 个存储器的内存为 $c_i$ ，若对第i个任务使用了 $k_i$ 个存储器则要求每个存储器的内存都要至少是 $\dfrac{x_i}{k_i}$ 上取整)，每个存储器只能供给一个任务使用，给定 $x_1,x_2$，构造方案或说明无解。

### 算法：

这个 D 比 E 还要难…

很好的题，但是如果我们想要直接随便构造方案还是不行的，我们应该要找到一些限制满足在这些限制下可行性不被破坏而且会有新的突破口，比如像：我们可以钦定ki最大/小的方案，$\dfrac{x_i}{k_i}$ 最大/小的方案（这些思路每一种想下去都是一种新方法，你可以通过二分，三分甚至模拟解决同一个问题），但是这些都与我们的实现有关，在这之前，我们应该把题目中给我们的东西分析好。

下文的所有除法都默认上取整。

我们发现将 $c_i$ 排序后，每一个存储器一定是占用连续的一段ci，这可以通过微扰的方法证明：假设一组最优方案中 $x_1$ 取了 $[l1,r1]$ ，$x_2$ 取了$[l_2,r_2]$，满足 $l_1\le r_1<l_2\le r_2$ ,则 $\dfrac{x_1}{k_2}\le \dfrac{x_2}{k_2}$ 假设从 $[l_1,r_1],[l_2,r_2]$ 两区间中分别取出了两个数 $c_x,c_y$ 将其交换，那么交换之后 $c_y$ 一定相比原先没有“物尽其用”，而 $c_x$ 很有可能不满足 $\ge \dfrac{x_2}{k_2}$ 的限制，原命题得证。

继续贪心地思考，假设我们钦定了 $x_i$ 占用的区间要在 $x_j$ 占用的区间之前，那么这些区间在什么情况下最优呢？很明显 $x_j$ 一定是占用 $i$ 至 $n$ 这一段区间最优（不然的话我用了比较小的数但是 $c_n$ 这种大数却没有用），$x_i$ 一定是从前到后扫描，只要满足条件就退出（这样可以使用最少数量的存储器，最大限度避免与 $x_j$ 重叠）。
那么我们的限制就出来了：我们要构造让这些选择的区间最优的方案，更本质些，区间是由 $k_i$ 决定的，即我们要构造让 $k_1,k_2$ 都尽量少的方案，这样，问题便迎刃而解了。


输出方案的过程不再赘述，这些确定了就是简单模拟。

代码：
```cpp    #include<bits/stdc++.h>
    #define MAXN 1000000
    #define int long long
    using namespace std;
    int n,x1,x2,used[MAXN+5];
    struct node{
    	int v,id;
    }c[MAXN+5];
    bool cmp(node x,node y){return x.v<y.v;}
    bool check(int fl){
    	int k1=-1; for(int i=1;i<=n;i++) used[i]=0;
    	int k2=-1,ln=0,ti=0;
    	for(int i=n;i;i--){
    		used[i]=2,++ln;
    		if((x2+ln-1)/ln<=c[i].v){k2=ln,ti=i; break;}
    	}if(k2==-1) return 0; int pln=0; 
    	for(int i=ti-1;i;i--){
    		used[i]=1; ++pln;
    		if((x1+pln-1)/pln<=c[i].v){k1=pln; break;}
    	}if(k1==-1) return 0;
    	int t1=1,t2=2;
    	if(fl) swap(k1,k2),swap(t1,t2); 
    	printf("Yes\n%lld %lld\n",k1,k2);
    	for(int i=1;i<=n;i++){
    		if(used[i]==t1) printf("%lld ",c[i].id);
    	}puts(""); for(int i=1;i<=n;i++) if(used[i]==t2) printf("%lld ",c[i].id); puts("");
    	exit(0); return 1;
    }signed main(){
    	scanf("%lld%lld%lld",&n,&x1,&x2);
    	for(int i=1;i<=n;i++) scanf("%lld",&c[i].v),c[i].id=i;
    	sort(c+1,c+n+1,cmp); int l=1,r=n;
    	check(0); swap(x1,x2); check(1);
    	puts("No");
    	return 0;
    }
```

其实是有很多别的方法的，比如像什么二分三分还有直接找，都比较巧妙，复杂度视实现优劣而定，可以参考 [link](https://codeforces.com/contest/967/submission/37721060)。

---

## 作者：gcx12012 (赞：0)

### Solution
小清新构造题。

可以转换为一个更易于理解的问题。

给定 n 个物品和两个背包的容量，每个物品具有价值 $val_i$，你可以选择将这个物品放进两个背包中的其中一个背包，也可以不放。求一种放置方案，使得两个背包都满足以下条件：

设背包容量为 $c$，放入了 $d$ 个物品，要求每个物品的 $val_i$ 大于等于 $\lceil\frac{c}{d}\rceil$。

这样想的话也许问题会变得容易一些。

但是这个 $d$ 没有给出具体的数。

我们可以对于每一个 $d\in[1,n]$ 分别处理出两个背包在已确定的 $\lceil\frac{c}{d}\rceil$ 条件下最多能放入多少个物品。

显然需要对 $val$ 进行降序排序以方便处理，且当这个可放入最多物品数 $mx_d<d$ 时是无解的。

这个可以通过双指针来解决，但是 $n\leq 3\times10^5$，所以也可以二分解决。

然后我们对于第一个背包找出其满足 $mx_d\geq d$ 的最小 $d$，设为 $d_{\min}$，对于第二个背包，考虑每一种有解的 $d$，当 $mx_d-d>=d_{\min}$ 时，存在一组具体解，这样的话可以把前 $d_{\min}$ 大的数放入第一个背包，然后把第 $d_{\min}+1$ 到 $d_{\min}+d$ 大的数放入第二个背包，可以证明该解是合法的。

时间复杂度为 $O(n \log n)$，瓶颈在于排序，排序的话可以用基数排序来做到 $O(n)$，但实际上这两种运行效率差不多。 ~~（其实是我人傻常数大）~~
### Code
$O(n \log n)$
```cpp
// LUOGU_RID: 154368021
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define lll __int128
#define ull unsigned long long
#define N 300010
#define For(i,a,b) for(ll i=a;i<=b;i++)
#define Rof(i,a,b) for(ll i=a;i>=b;i--)
#define ls x<<1
#define rs x<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
#define pb push_back
#define mk make_pair
#define pque priority_queue
#define pii pair<int,int>

using namespace std;
struct node{
	int val,bh;
}a[N];
int b1[N],b2[N];
int n,x1,x2;

ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}


int main()
{
	n=read(),x1=read(),x2=read();
	For(i,1,n) a[i].val=read(),a[i].bh=i;
	sort(a+1,a+n+1,[&](node x,node y){return x.val>y.val;});
	int now=1;
	For(i,1,n){
		while(now<=n && a[now].val>=x1/i+(x1%i>0)) now++;
		b1[i]=now-1;
	}
	now=1;
	For(i,1,n){
		while(now<=n && a[now].val>=x2/i+(x2%i>0)) now++;
		b2[i]=now-1;
	}
	For(i,1,n) if(b1[i]<i) b1[i]=0;
	For(i,1,n) if(b2[i]<i) b2[i]=0;
	int p=1919810;
	For(i,1,n){
		if(b1[i]!=0){
			p=i;
			break;
		}
	}
	For(i,1,n){
		if(!b2[i]) continue;
		if(b2[i]-i>=p){
			printf("Yes\n%d %d\n",p,i);
			For(j,1,p) printf("%d ",a[j].bh);
			printf("\n");
			For(j,p+1,p+i) printf("%d ",a[j].bh);
			printf("\n");
			return 0;
		}
	}
	p=1919810;
	For(i,1,n){
		if(b2[i]!=0){
			p=i;
			break;
		}
	}
	For(i,1,n){
		if(!b1[i]) continue;
		if(b1[i]-i>=p){
			printf("Yes\n%d %d\n",i,p);
			For(j,p+1,p+i) printf("%d ",a[j].bh);
			printf("\n");
			For(j,1,p) printf("%d ",a[j].bh);
			printf("\n");
			return 0;
		}
	}
	printf("No");
	return 0;
}
```
$O(n)$
```cpp
// LUOGU_RID: 154369355
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define lll __int128
#define ull unsigned long long
#define N 300010
#define For(i,a,b) for(ll i=a;i<=b;i++)
#define Rof(i,a,b) for(ll i=a;i>=b;i--)
#define ls x<<1
#define rs x<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
#define pb push_back
#define mk make_pair
#define pque priority_queue
#define pii pair<int,int>

using namespace std;
struct node{
	int val,bh;
}a[N],c[N];
int b1[N],b2[N];
int n,x1,x2;

ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int B=40000;
int cnt[40010];
void sort1(){
	memset(cnt,0,sizeof(cnt));
	For(i,1,n) cnt[a[i].val/B]++;
	For(i,1,40000) cnt[i]+=cnt[i-1];
	Rof(i,n,1){
		int p=cnt[a[i].val/B]--;
		c[p]=a[i];
	}
	For(i,1,n) a[i]=c[i];
	memset(cnt,0,sizeof(cnt));
	For(i,1,n) cnt[a[i].val%B]++;
	For(i,1,40000) cnt[i]+=cnt[i-1];
	Rof(i,n,1){
		int p=cnt[a[i].val%B]--;
		c[p]=a[i];
	}
	For(i,1,n) a[i]=c[i];
}

int main()
{
	n=read(),x1=read(),x2=read();
	For(i,1,n) a[i].val=read(),a[i].bh=i;
	sort1();
	For(i,1,n) if(i<=n/2) swap(a[i],a[n-i+1]);
	//For(i,1,n) cout<<a[i].val<<' ';
	//cout<<endl;
	int now=1;
	For(i,1,n){
		while(now<=n && a[now].val>=x1/i+(x1%i>0)) now++;
		b1[i]=now-1;
	}
	now=1;
	For(i,1,n){
		while(now<=n && a[now].val>=x2/i+(x2%i>0)) now++;
		b2[i]=now-1;
	}
	For(i,1,n) if(b1[i]<i) b1[i]=0;
	For(i,1,n) if(b2[i]<i) b2[i]=0;
	int p=1919810;
	For(i,1,n){
		if(b1[i]!=0){
			p=i;
			break;
		}
	}
	For(i,1,n){
		if(!b2[i]) continue;
		if(b2[i]-i>=p){
			printf("Yes\n%d %d\n",p,i);
			For(j,1,p) printf("%d ",a[j].bh);
			printf("\n");
			For(j,p+1,p+i) printf("%d ",a[j].bh);
			printf("\n");
			return 0;
		}
	}
	p=1919810;
	For(i,1,n){
		if(b2[i]!=0){
			p=i;
			break;
		}
	}
	For(i,1,n){
		if(!b1[i]) continue;
		if(b1[i]-i>=p){
			printf("Yes\n%d %d\n",i,p);
			For(j,p+1,p+i) printf("%d ",a[j].bh);
			printf("\n");
			For(j,1,p) printf("%d ",a[j].bh);
			printf("\n");
			return 0;
		}
	}
	printf("No");
	return 0;
}
```

---

