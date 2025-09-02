# [USACO07FEB] Cow Sorting G

## 题目描述

Farmer John 的 $n$（$1 \leq n \leq 10^5$）头牛一字排开。每头奶牛都有一个“脾气暴躁”水平，范围在 $1 \ldots 10^5$，且任意两头奶牛的脾气暴躁值不相同。由于脾气暴躁的奶牛更有可能损坏 FJ 的挤奶设备，因此 FJ 希望对奶牛进行重新排序，以便按照脾气暴躁程度依此提升的顺序排列它们。

在此过程中，任何两头奶牛（不一定相邻）的位置都可以互换。由于脾气暴躁的母牛难以移动，因此 FJ 总共需要 $X + Y$ 单位的时间来交换两只脾气暴躁程度为 $X$ 和 $Y$ 的母牛。请帮助 FJ 计算将奶牛按脾气暴躁程度的升序排序所需的最短时间。

## 样例 #1

### 输入

```
3 
2 
3 
1```

### 输出

```
7```

# 题解

## 作者：Feather_Moon (赞：17)

本蒟蒻的第一篇题解，求求管理员大大审核通过 QAQ。

[P6193 [USACO07FEB] Cow Sorting G ](https://www.luogu.com.cn/problem/P6193)解题报告。

## 题意
有一个长度为 $n$（$1 \leq n \leq 10^5$）的序列，第 $i$ 个数有一个权值 $a_i$（$1 \leq a_i \leq 10^5$, $a_i$ 互不相同）。你可以花费 $a_i+a_j$ 的代价去交换第 $i$ 个元素和第 $j$ 个元素，求将 $a$ **升序**排序的最小代价。

## 分析

这个 $a_i+a_j$ 的代价就很烦，我们先考率题目的弱化。

### 弱化版

如果不管代价，只要求**交换次数**最少，答案是什么呢？

举一个例子：

> 数列 $\{5,1,4,3,2\}$，最少需要三次操作。
>
> 第一次操作：交换 $3$ 和 $4$，数列变成 $\{5,1,3,4,2\}$。
>
> 第二次操作：交换 $1$ 和 $5$，数列变成 $\{1,5,3,4,2\}$。
>
> 第三次操作：交换 $2$ 和 $5$，数列变成 $\{1,2,3,4,5\}$。
>
>可以证明不存在更少的操作次数。

可以发现，我们的操作策略就是把一个元素移到它该去的地方。

我们将一个元素与它要去的位置所在的元素连边（如元素 $5$ 要与在第 $5$ 个位置的元素 $2$ 连边），如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/zep7bexf.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

我们可以发现，图是由若干个环组成的。

感性证明也非常简单，每个点被连一次，出去一次，入度和出度均是一，这样的图只能是若干个环组成的。

观察上图的环，以环 $2 \rightarrow 1 \rightarrow 5 \rightarrow 2$ 举例子。

我们可以发现 $2,5,1$ 虽然不在自己应该在的位置，但是如果把它们看成整体，对于整个序列来说它们占据了排好序后 $2,5,1$ 应该在的位置，所以对于整个序列来说是有序的，它们只是自身内部无序而已。所以只需要环内换序就可以了。

而对于一个含有 $n$ 个元素的环，只要交换 $n-1$ 次（一次操作排好一个元素，最后一个不用排）。所以，答案就是元素的数量减去环的数量。

严格的证明较复杂，可以参考 [这篇文章](https://blog.csdn.net/yunxiaoqinghe/article/details/113153795)。

弱化版核心代码：
```
ans=n;
for(int i=1;i<=n;i++){
	if(vis[i])continue;
	int now=i;ans--;
	while(!vis[now]){
		vis[now]=1;//打标记
		now=a[now];//遍历下一个结点
	}
}
```
由于每个结点只经过一次，时间复杂度是 $\mathcal{O}(n)$ 的。
### 原题

扯了这么多，让我们回到正轨。

我们将上面的方法迁移过来，先找到一个元素它排序后在哪里，这可以用二分或排序解决，然后建环。

那么现在的问题就变成了：

>把一个环内的元素有序排列的最小代价。

每个元素要回到原位置，最少也得交换一次。而像这样简单强势的交换，一共有 $siz-1$ 次（$siz$ 是环的大小）。只需要利用圈里面最小的那个~~当苦力~~参与交换即可，此时代价为 $(siz - 2)\times Min + Sum$，其中 $ Sum $ 表示环中所有元素之和，$Min$ 表示环中最小的元素（$Min$ 与其它所有元素做了 $siz-1$ 次交换，$Sum$ 中包含了一个 $Min$，所以是 $(siz - 2)\times Min + Sum$）。

当你自信满满的拿着代码甩在这道题脸上时，你会发现这道题拿着 WA 甩了你一脸。

问题出在哪呢？我们来看下面这个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/7q4a4js2.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

按照我们原来的的方式，我们会拿 $9997$ 分别与 $9998$ 到 $10000$ 进行交换，代价是 $ (9997+ 9998)+(9997 + 9999)+(9997 + 10000)=59988$。如果我们将外面的 1 介入呢：
>
>1.先将外部**最小**的与内部**最小**的交换，代价为  $(1+9997)=9998$。
>
>2.再将外部**最小**代替以前内部**最小**进行交换，代价为 $(1+9998)+(1+9999)+(1+10000)=30000$。
>
>3.最后将外部**最小**的与内部**最小**交换回来，代价为 $(1+9997)=9998$。
>
>总代价为 $9998+30000+9998=49996 < 59988$。
>>关于为什么要与内部最小的交换的简要证明：
>>
>>设外部最小 $Min$（这应该很好理解）与内部权值为 $X$ 的元素交换。
>>
>>- 第一、三步的代价为 $Min+x$。
>>
>>- 第二步的代价为 $(siz-2)\times Min+(Sum-x+Min)$（定义同上）。
>>
>>总代价为 $x+(siz+1)\times Min+Sum$。
>>
>>由于 $Sum,siz,Min$ 是定值，当 $x$ 最小时代价最小。
>
**所以，共有两种调换办法，大部分人都会想到利用圈里面最小的那个参与交换，还有一个办法就是把全局最小的调入圈里，弄好了再还回去。**

此时，代价为 $\min(Sum+( siz - 2 ) \times Min1,(siz+1)\times Min2+Sum+Min1)$，其中 $siz$ 是环的大小， $ Sum $ 表示环中所有元素之和，$ Min1 $ 表示环中最小的元素，$ Min2 $ 表示全局最小的元素。

每个元素只折腾一次，故核心时间复杂度为 $\mathcal{O}(n)$。

瓶颈在于排序或二分的 $\mathcal{O}(n \log n)$。

注意开 `long long`。

## 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=200005;
int n,b[maxn],a[maxn],nxt[maxn],ans,Min1=(int)1<<60;;
bool vis[maxn];
int read(){
	char ch=getchar();int ret=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+(ch&15),ch=getchar();
	return ret*f;
}
int find(int x){//二分枚举每个数排序后的排名
	int L=1,R=n,mid,ans;
	while(L<=R){
		mid=L+R>>1;
		if(b[mid]==x)return mid;
		if(b[mid]<x)L=mid+1; 
		if(x<b[mid])R=mid-1;
	}
}
signed main(){
//	freopen("csort.in","r",stdin);
//	freopen("csort.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)b[i]=a[i]=read(),Min1=min(Min1,a[i]);
	sort(b+1,b+1+n);
	for(int i=1;i<=n;i++)nxt[i]=find(a[i]);
	for(int i=1;i<=n;i++){
    	if(vis[i])continue;
    	int now=i;
		int Min2=(int)1<<60,cnt=0,sum=0;
		while(!vis[now]){//遍历环
			cnt++;sum+=a[now];vis[now]=1;
    		Min2=min(Min2,a[now]);
    		now=nxt[now];
		}
    	int now1=(cnt-1)*Min2+sum-Min2;
    	int now2=cnt*Min1+sum+Min2+Min1;
    	ans+=min(now1,now2);//计算代价
    }
	printf("%lld\n",ans);
	return 0;
}
```

都看到这里了，能不能给个赞呢？

有不懂随时@我。

蒟蒻第一篇题解写得不好请见谅。

---

## 作者：a___ (赞：6)

首先，由于 $a_i$ 确定，所以一头牛开始和结束的位置构成的置换是确定的。置换 $\begin{pmatrix}p_1,p_2,p_3,\dots,p_n\\q_1,q_2,q_3,\dots,q_n\end{pmatrix}$ 表示将位置 $p_i$ 的数换到位置 $q_i$。   

然后，我们知道一个置换一定可以分解成若干循环节。循环节 $(r_1,r_2,r_3,\dots,r_m)$ 表示将 $r_1$ 换到 $r_2$ ，将 $r_2$ 换到 $r_3$ ，...，将 $r_m$ 换到 $r_1$ 。  

如 $\begin{pmatrix}1,2,3,4,5,6\\3,4,5,2,1,6\end{pmatrix}=(1,5,3)(2,4)(6)$。

容易发现，对于一个循环节，每个数至少要被换一次，那么我们选循环节内代价最小数换一遍一定最优。  

另外，由于各个循环节互不相关，仅在同一循环节内部互换一定最优.....吗？  

发现有一种特殊情况，即如果 **本循环节内**代价最小数 仍然代价过大，可以考虑先把 **整个数列中**的代价最小数 与 **本循环节内**代价最小数 互换，循环一整圈以后再换回来。   

代码很简单，就不贴了。

---

## 作者：zumgze (赞：2)

考虑两种情况（这里以5个奶牛为例）

①5 1 2 3 4

显然让1一直向右交换，直到回到它原本的位置最优

在这个过程中，1计算了4次，其他数字都只计算了一次

②1 10 7 8 9

这里可以10 7 8 9构成了一个类似上面的圈，然而还存在一个1可供“借用”，我们可以先交换1和7，再利用1将8 9 10都归位最优，最后别忘了再把1和7换回来

在这个过程中除去用于“借用的”  2*（1+7），1计算了3次，8 9 10均只计算了一次

基于这两种情况，上代码_ 

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	long long no,ele;
};
node b[100000];//存放有序数据，其中b[i].no表示，最后排在第i为=位的奶牛初始的位置 
long long a[100000];//存放原始数据，用于模拟交换 
long long ans;
bool cmp(node a,node b)
{
	return a.ele<b.ele;
}
int main()
{
	ios::sync_with_stdio(false);
    long long n;
    cin>>n;
    for(long long i=0;i<n;i++)
    {
    	cin>>a[i];
    	b[i].ele=a[i];
    	b[i].no=i;
	}
	sort(b,b+n,cmp);
	for(long long i=0;i<n;i++)
		if(a[i]!=b[i].ele)
		{
			long long lo=b[i].no;
			long long ans1=2*(b[0].ele+a[lo]),ans2=0;//ans1表示“借用”的情况，ans2表示不“借用”的情况 
			while(a[lo]!=b[lo].ele)
			{
				ans1+=b[0].ele+a[b[lo].no];
				ans2+=a[lo]+a[b[lo].no];
				swap(a[lo],a[b[lo].no]);
				lo=b[lo].no;
			}
			ans+=min(ans1,ans2);
		}
	cout<<ans;
    return 0;
}
```


---

## 作者：Purslane (赞：1)

## Solution

置换 . 考虑将每头牛的位置和它要转移到的位置之间连边 . 

根据置换的性质 , 这个图一定是由一堆不相交的环构成 . 显然每个环之间独立 .

考虑到每个环中的每个数都要被交换 , 那么肯定希望交换的另一个数是最小的 . 那么可以构造出一种方法 :

> 从要转移到最小值点的那个点开始 , 不断和它前面的那个点交换 . 这里使得交换的另一个点总是最小值点 .

但如果这个最小值还太大怎么办 ? 那么不得不向环外求助了 . 用最小值点把整个序列的最小值换过来 , 跑一边上面的算法 , 再跑回去即可 .

code :

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+20;
int n,val=INT_MAX,a[MAXN],b[MAXN],p[MAXN],vis[MAXN],ans;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;ffor(i,1,n) cin>>a[i];val=*min_element(a+1,a+n+1);
	ffor(i,1,n) b[i]=a[i];sort(b+1,b+n+1);
	ffor(i,1,n) p[i]=lower_bound(b+1,b+n+1,a[i])-b;
	ffor(i,1,n) if(!vis[i]) {
		int tot=0,sum=0,MN=INT_MAX,u=i;
		do {vis[u]=1,tot+=a[u],sum++,MN=min(MN,a[u]),u=p[u];}while(u!=i);
		int meth1=tot+(sum-2)*MN,meth2=(tot-MN+val)+(sum-2)*val+2*(MN+val);
		ans+=min(meth1,meth2);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：crescentic (赞：1)

[Cow Sorting G](https://www.luogu.com.cn/problem/P6193)

**简单题意：**

> 农夫 John 准备把他的 $N$ 头牛排队以便于行动。因为脾气大的牛有可能会捣乱，John 想把牛按脾气的大小排序。在排序过程中，John 可以交换任意两头牛的位置。因为脾气大的牛不好移动，John 需要 $X+Y$ 秒来交换脾气值为 $X$ 和 $Y$ 的两头牛。 请帮 John 计算把所有牛排好序的最短时间。

**思路：**

首先，因为起始顺序和最后的位置顺序都是固定的，所以置换是确定的 $\begin{pmatrix}a_i&a_{i+1}&a_{i+2}&……&a_n\\b_i&b_{i+1}&b_{i+2}&……&b_n\end{pmatrix}$；

找出所有轮换（循环节）。

对于每个轮换来说，其所包含的牛肯定是在轮换内部交换，每头牛至少交换一次。但是最小花费却并不能因此确定……因为无法保证轮换内的最小花费就是整个序列的最小花费。

有两种情况：

- 仅限轮换内部交换；

贪心可知每次交换都应该是脾气之最小的牛和另外一头牛交换。一遍一遍换，知道排好顺序。

- 有轮换外的牛参与交换。

其实就是将轮换外脾气值最小的牛 $x$ 换进来，每次参与交换，轮换内的牛排好位置之后再把 $x$ 换出去。

求轮换就很套路了，这里不赘述……

**代码：**

```cpp

#include<cstdio>
#include<vector> 
#include<algorithm>
using namespace std;
#define ll long long
const int N = 1e5 + 5, inf = 1e5;
int n,a[N],b[N],id[N],bel[N],tot,mi,sz;
ll ans;
vector<int> G[N];
int main() {
	scanf("%d",&n);
	for(int i = 1; i <= n; i ++) scanf("%d",&a[i]), b[i] = a[i];
	sort(b + 1,b + 1 + n);
	for(int i = 1; i <= n; i ++) id[b[i]] = i;
	int node,nex;
	for(int i = 1; i <= n; i ++) {//求轮换
		node = id[a[i]];
		if(bel[node]) continue;
		nex = id[a[node]], bel[node] = ++tot;
		while(nex != node) {
			bel[nex] = tot;
			nex = id[a[nex]];
		}
	}
	for(int i = 1; i <= n; i ++) G[bel[id[a[i]]]].push_back(a[i]);
	for(int i = 1; i <= tot; i ++) {
		mi = inf, sz = G[i].size();
		for(int j = 0; j < sz; j ++) {
			ans += G[i][j], mi = min(mi,G[i][j]);//每头牛都至少交换一次。
		}
		ans -= mi, ans += min((sz - 1) * mi,b[1] * (sz + 1) + mi * 2); //上述两种情况取最小值。
	}
	printf("%lld",ans);
	return 0;
}

```


---

## 作者：zdy111111 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P6193)

读完这道题，只要交换任意两头牛若干次，求出使其暴躁程度从小到大的最小时间。

首先第一个问题，如何交换任意两头牛若干次，使其暴躁程度从小到大呢？当然，不能真的给暴躁程度排序。只需构造一个`id`数组，给`id`数组按照暴躁程度的规则排序，再`nxt`数组建图就行了。

第二个问题是从小到大的最小时间。我们第一个想到的肯定是环中最小的那头牛参与交换，但还有一种可能，就是全局最小的那头牛进绕一圈然后和环中最小的那头牛参与交换就OK了。

上代码！


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],id[100005],nt[100005];
long long ans;
bool vis[100005];
bool cmp(int x,int y){return a[x]<a[y];}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),id[i]=i;
	sort(id+1,id+1+n,cmp);//暴躁程度的规则排序
	long long Min1=a[id[1]];//全局最大
	for(int i=1;i<=n;i++) nt[id[i]]=i;//建图
	for(int i=1;i<=n;i++){
		if(vis[i]) continue;//必须没走过
		int p=i;
		long long Min2=(long long)1<<62,cnt=0,sum=0;
		do{
			cnt++;sum+=a[p];
			Min2=min(Min2,(long long)a[p]);//环中最小的那头牛
			vis[p]=1;p=nt[p];
		}while(p!=i);
		ans+=min((cnt-2)*Min2+sum,(cnt+1)*Min1+sum+Min2);//两者之间挑个min
	}
	printf("%lld\n",ans);
	return 0;
} 
```
## 完！

---

## 作者：封禁用户 (赞：0)

## 读题
考虑将每头牛的位置和它要转移到的位置之间连边。

根据置换的性质,这个图一定是由一堆**不相交**的环构成，显然每个环之间**独立**。

考虑到每个环中的每个数都要被**交换**,那么肯定希望交换的另一个数是最小的。那么可以构造出一种方法。

## 解题方法
从要转移到最小值点的那个点开始,不断和它前面的那个点**交换**。这里使得交换的另一个点总是最小值点。

但如果这个最小值还太大怎么办?那么不得不向环外求助了。用最小值点把整个序列的**最小值换过来**,跑一边上面的算法,再跑回去即可。

## 代码
[剪切板是个好东西:)](https://www.luogu.com.cn/paste/rh2o0mnx)

## 综合评价
题目不错，可以用来练练手。

## 方法2

此方法不进行过多介绍，感觉不是很好，主要是因为有点暴力，或者说不是很优雅。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+100;
int n;
int a[N];
int b[N];
bool vis[N];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(b+1,b+n+1,a[i])-b;
	}
	int ans=0;
	int small=b[1];
	for(int i=1;i<=n;i++) if(!vis[i]){
		int sum=b[a[i]],minn=b[a[i]],len=1;
		vis[i]=true;
		for(int j=a[i];j!=i;j=a[j]){
			sum+=b[a[j]];
			minn=min(minn,b[a[j]]);
			len++;
			vis[j]=true;
		}
		ans+=min(sum+minn*(len-2),2*(minn+small)+small*(len-1)+sum-minn);
	}
	cout<<ans;
}
```
这个也是正解。

由此，我们完成了这道题目。

---

