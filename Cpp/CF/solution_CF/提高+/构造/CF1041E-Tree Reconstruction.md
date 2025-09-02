# Tree Reconstruction

## 题目描述

### 题目大意：
有一棵树，现在给你每条树边被去掉时，形成的两个联通块中点的最大的编号分别是多少，问满足条件的树存不存在

## 样例 #1

### 输入

```
4
3 4
1 4
3 4
```

### 输出

```
YES
1 3
3 2
2 4
```

## 样例 #2

### 输入

```
3
1 3
1 3
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
3
1 2
2 3
```

### 输出

```
NO
```

# 题解

## 作者：shadowice1984 (赞：11)

神奇构造题
______________

我们接下来要证明的是只要构造一条链就可以构造出我们想要的树了，如果构造链仍然没法满足的话，那就是无解了

## 本题题解

首先题目中每条边都是相互独立的，不是一条边一条切掉之后两边的联通块剩下的点最大值，而是对于每一条边来讲，假设这条边没有了，左右两侧点的最大值

所以我们可以看出来如果我们想构造出一个合法的树的话所有的$b_{i}$必须是$n$因为$n$这个点要么被分到左边要么被分到右边

所以现在让我们集中经历考虑所有的$b_{i}=n$的情况，此时我们需要考虑的是满足$a_{i}$的限制条件

那么我们可以先想一种简单粗暴无脑但是好用的构造方案，就是构造一条链，并且$n$在长链的一端

那么我们可以把这个长链看成一个数组，我们题目中输入的$a$数组相当于一个前缀$max$数组,也就是说，我们的问题变成了给你一个数组的前缀max数组，反着构造原数组

这个问题其实还是比较可做的，具体的构造方法就是我们会发现前缀max数组是单调递增的所以我们把所有的$a$值都排一个序,然后在前缀max变成$a$的位置放一个$a$，后边放若干个比$a$小的数字就可以了

现在我们要证明的是为什么当我们无法构造出一条链的时候我们同样构造不出一个树的解

考虑一下什么时候我们上述的构造算法会失效

那就是对于某一个数字k,小于等于k的前缀max比k还要多，根据抽屉原理前k个数字的前缀max值一定是大于等于k的，所以剩下的前缀max我们就放不下了，构造就失败了

那么问题来这种情况就算你是颗树我们还是构造不出来的

具体来讲我们反证法证明，假设我们构造了一个合法的树，然后我们钦定了n为根，那么另一端点的最大值就是子树内的最大值那么问题来了根据抽屉原理在k条边中最大值的最小值一定是大于等于k的(因为在这时候子树的根节点就会出现一个大于等于k的点了)，因此我们可以证明这种情况就算是个树我们也构造不出来解

所以这题就很好写了，我们尝试构造一条链出来，如果失败了就输出no，然后就是记得判一下有些b不是n的情况了

上代码~

```C
#include<cstdio>
#include<algorithm>
using namespace std;const int N=1e3+10;int mx[N];int a[N];int n;
bool book[N];
inline void cfil(){printf("NO\n");return;}
inline void csuc(){printf("YES\n");return;}
int main()
{
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++)
    {scanf("%d%d",&u,&v);if(u<v)swap(u,v);if(u!=n){cfil();return 0;}mx[i]=v;}
    sort(mx+1,mx+n);
    for(int i=1;i<=n;i++)
    {
        if(mx[i]!=mx[i-1])a[i]=mx[i],book[a[i]]=true;
        else
        {
            for(int j=1;j<=mx[i];j++)
            if(!book[j]){a[i]=j,book[j]=true;goto ed;}cfil();return 0;ed:;
        } 
    }
    csuc();a[n]=n;
    for(int i=1;i<n;i++)printf("%d %d\n",a[i],a[i+1]);
}
```

---

## 作者：Ezis (赞：7)

提供一种**不是链**的做法

### 题意：

给定 一棵树中每条边被删去后，形成的两个连通块中两个编号最大的点的编号，问 满足条件的树存不存在。若存在，输出 YES ，并给出方案，否则输出 NO 。

### 思路：

首先，我们可以很明显地看到，无论砍掉树上哪一条边，其中一个连通块内编号最大的树一定是 $N$。若不满足这一条件，可直接判无解。

我们把最后答案里的树想象成一个**类似**菊花图的样子，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/nl1k8mrr.png)

而这棵树的根一定是n。

然后，观察输入数据中每个数（除 $N$ 外 ）的出现次数，将其分为以下两类：

- $tot=0$ ，即没有出现，此时它应该属于一个**编号比它大**的叶子节点。

- $tot>0$ , 即出现过了，则它就是叶子节点，且它到 $N$ 的路径上（不包括 $N$ 和它自己）**有且仅有 $tot-1$ 个点**。

若不符合，则无解。

按以上操作不断更新即可。

### CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define NO printf("NO\n")
#define YES printf("YES\n")
int n,edgenum,tot_l,tot_m,tot[1005],leaves[1005],middle[1005];
struct node{
	int x,y;
}b[1005];
void add(int u,int v){
	edgenum++;
	b[edgenum].x=u;
	b[edgenum].y=v;
}
int main(){
	scanf("%d",&n);
	for(int i=1,x,y;i<n;i++){
		scanf("%d%d",&x,&y);
		if(x>y) swap(x,y);
		if(y!=n||x==y){NO;return 0;}
		tot[x]++;
	}
	for(int i=1;i<n;i++){
		if(tot[i]>0) leaves[++tot_l]=i;
		if(tot[i]==0) middle[++tot_m]=i;
	}
	sort(leaves+1,leaves+tot_l+1);
	sort(middle+1,middle+tot_m+1);
	int _top=1;
	for(int i=1;i<=tot_l;i++){
		if(tot[leaves[i]]==1){
			add(leaves[i],n);
			tot[leaves[i]]--;
			continue;
		}
		tot[leaves[i]]--;
		int u=leaves[i];
		while(tot[leaves[i]]){
			bool get=true;
			if(middle[_top]<=leaves[i]){
				add(u,middle[_top]);
				u=middle[_top];
				_top++;tot[leaves[i]]--;
				get=false;
			}
			if(get){NO;return 0;}
		}
		add(n,u);
	}
	YES;
	for(int i=1;i<n;i++) printf("%d %d\n",b[i].x,b[i].y);
	return 0;
}
```


---

## 作者：installb (赞：3)

一道比较有趣的构造题  
大概讲一下思考的过程

首先无论断掉树上的哪一条边 都会把它分成两个连通块 这两个连通块中必定有一个包含最大编号的点 包含最大编号的点的连通块中**点的最大的编号**一定是 $n$  

不满足这条直接无解  

接下来把这个$n$去掉 看剩下来的数组成了一个序列  
$1$到$n$中 有的数出现了一次 有的数出现了多次 有的数没有出现  

每一个数出现次数等于分割每一条边 它和$n$不在一个连通块内的方案数  
我们可以把$n$当成根  

这样序列最小的数一定是叶子结点  
次小的数可以是它的父亲节点 以此类推 可以构造出一条链  
然后把没有出现过的数插入到合适位置 就可以了  

如果一个数出现了$x$次 就选择$x-1$个数 插入在它和它的父亲节点之间  
这样以这些点连向父亲节点的边断掉时 一个连通块最大编号一定是这个数  
如果这一步选不出来 也无解  
这个时候某个编号的前缀大于等于它的编号大小  
即使不限定是链也是构造不出来的  

具体实现的不太一样 我是把所有编号排序 然后在每一个位置上取哪个编号  
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

int n;
int u,v;
int cnt = 0;
int a[1005]; // 原非n连通块的编号
int vis[1005] = {0}; // 记录某个点是否被用过
int pt[1005] = {0}; // 记录从链底到链顶的编号

int main(){
	cin >> n;
	for(int i = 1;i < n;i ++){
		cin >> u >> v;
		if(u > v) swap(u,v);
		if(v == n) cnt ++;
		a[i] = u;
	}
	if(cnt < n - 1){
		cout << "NO" << endl; // 无解1
		return 0;
	}
	a[n] = n;
	sort(a + 1,a + n + 1); // 从小到大排序
	for(int i = 1;i <= n;i ++){
		if(!vis[a[i]]){
			vis[a[i]] = 1;
			pt[i] = a[i];
		}
		else{
        // 这个数出现不止一次 找比他小的数填
			for(int j = 1;j < a[i];j ++){
				if(!vis[j]){
					vis[j] = 1;
					pt[i] = j;
					break;
				}
			}
        // 找不到能填的数 无解
			if(!pt[i]){
				cout << "NO" << endl;
				return 0;
			}
		}
	}
	cout << "YES" << endl;
	for(int i = 2;i <= n;i ++){
		cout << pt[i] << ' ' << pt[i - 1] << endl;
        // 输出
	}
	return 0;
}
```
说句题外话 Codefoces大多数题目的样例都会包含所有的情况  
比如这个样例中包含了 上面提到的两种无解 和 有解  

另外 有时候样例会故意给你构造一个不应该是程序构造出来的输出(比如这题给一个非链)  

---

## 作者：Watanabe (赞：1)

容易发现如果有解，那么 $n$ 这个点一定会在每一组输入中出现，所以 $n$ 如果没有出现直接判无解。

接下来我们考虑每一组输入中不是 $n$ 的另一个点能作为某个联通块的最大值出现的情况。首先我们需要将这个点和 $n$ 断开，否则这个点不能作为最大值，所以我们删掉的这条边一定是 **$n$ 到这个点的路径上的一条边**。

那么显然，$n$ 到这个点的路径上有几条边，这个点就会作为某个块的最大值出现几次，所以在构造的时候直接将这个点和 $n$ 的距离强令为这个点出现的次数。

但是现在有个小问题，我们必须保证其他点不能篡位当前这个点代替它成为最大值，也就是说我们**倒序处理**，每次考虑在最右边加点，所以**新加的点应当和上一个点的距离为新加的点的出现次数**，若这个点没出现过则在前面找一个空位放。

具体实现时维护一个 $l$ 和 $r$，分别表示最左边的空位的前一个位置和最右边的点在哪里。注意，若当前 $l$ 移动到 $r$ 了，说明我们要在 $l+1$ 加这个出现次数为 $0$ 的点，但是这样显然不符合题意，故判无解。

最后，如果最开始放的位置和 $r$ 直接有大于 $n$ 个点也说明无解。

这里因为脑抽把 $l$ 初值赋为 $n$ 了，但问题不大。

code:

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define re register
#define int long long

using namespace std;
const int N=4e3+100;
int n,cnt[N],u,v;
int a[N];
int l,r;
bool flag=true ;
signed main()
{
	cin>>n;
	for(re int i=1;i<n;++i)
	{
		cin>>u>>v;
		if(u==n) swap(u,v);
		++cnt[u];
		if(v!=n) flag=false ;
	}
	if(!flag)
	{
		printf("NO");
		return 0;
	}
	l=r=n;
	a[n]=n;
	for(re int i=n-1;i;--i)
	{
		if(!cnt[i])
		{
			
			while(a[l]) l++;
			l--;
			if(l==r)
			{
				printf("NO");
				return 0;
			}
			a[++l]=i;
		}
		else
		{
			a[r+cnt[i]]=i;
			r=r+cnt[i];
		}
	}
	if(r>2*n-1)
	{
		printf("NO");
		return 0;
	}
	printf("YES\n");
	for(re int i=n;i<r;++i)
	{
		cout<<a[i]<<" "<<a[i+1]<<"\n";
	}
	return 0;
}
//list

/*

*/
```


---

## 作者：king_xbz (赞：1)

首先我们可以发现，这里的树边是无序的。也就是说你删掉任意一条边，能满足以上条件均可。

结论1：只有一条链才能满足条件。

结论2：把一条链分成两份，那么必有一份编号为n，否则无解

那么我们考虑到假如让一个最小的值成为这个块最大值，那么该值一定在链的一端。

同时为了尽量消除最大值对小块值的影响，n应当在链的另一端。

那么看似我们需要构造的链是

$1\to2\to 3\to 4$,但是有可能出现删掉两边但是两块最大值最小值都一样，同时也会出现没有被询问的点。此时把没有询问的点放在多次被询问的点中间，且这些没有被问的点一定要比被询问的两端点小（工具人属性）

那么我们大概就有了构造的思路了；


代码：

```cpp
#include<bits/stdc++.h>
#define fint register int
#define H 5001
#define N 437984
using namespace std;
int a[N],t[N];
bool vis[N];
int main()
{
	int n;
	cin>>n;
	int x,y;
	for(fint i=1;i<n;i++)
	{
		cin>>x>>y;
		if(x>y)
		swap(x,y);
		if(y!=n)
		{
			puts("NO");
			return 0;
		}
		a[i]=x;
	}
	sort(a+1,a+n);
	a[n]=n;
	for(fint i=1;i<=n;i++)
	{
		bool ff=0;
		if(!vis[a[i]])
		{
			t[i]=a[i];
			vis[a[i]]=1;
			ff=1;
		}
		else
		{
			for(fint j=1;j<a[i];j++)
			if(!vis[j])
			{
				vis[j]=1,t[i]=j,ff=1;
				break;
			}
			if(!ff)
			{
				puts("NO");
				return 0;
			}
		}

	}
	puts("YES");
	for(fint i=2;i<=n;i++)
	cout<<t[i]<<" "<<t[i-1]<<endl;
	return 0;
}
```



---

## 作者：zythonc (赞：1)

~~又是你谷评分过高的一道题~~

## 【分析过程】

给出两个连通块中最大的点的编号

那么很轻易的可以想到这**两个数字之中一定有一个是等于n的**

> 特判一：如果输入的两个数其中一个不为一，那么就输出NO

由此可以得出

> 特判二：如果两个数相同，输出NO

继续分析

设输入的两个数为$a,b$，$b$ 等于 $n$

输入之后按照$a$的大小由小到大排序

容易得到一条性质：

**在 $a_i$ 之前一定有 $i-1$ 个节点小于 $a_i$**

> 特判三，如果 $a_i$ 小于 $i$ ，输出NO

然后根据这一性质可以得出，**对于一组数据如果可以对应的构造出一棵的树，那么一定也可以构造一条满足条件的链**

然后我们先将出现过的 $a_i$ 按顺序放在链中，根据

- 在 $a_i$ 之前一定有 $i-1$ 个节点小于 $a_i$
    
这一性质，我们将没有出现过的节点依次插入即可

**WA点的同学可以试试下面这组蒟蒻口胡的数据**

```
6
1 6
3 6
4 6
5 6
5 6
```

## 【代码实现】

```
#include<iostream>
#include<algorithm>
#define END cout<<"NO";return 0;
using namespace std;
int n,p,last,tree[1011],size,a,b,s[1011],num,now=1;
bool vis[1011];
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>a>>b;
		if(a==b) {END}
		if(a!=n&&b!=n) {END}
		s[i]=(a==n?b:a);
	}
	sort(s+1,s+n);
	while(++num<n) if(s[num]<num) {END}
	for(int i=1;i<n;i++){
		for(p=i+1;p<n;p++){
			if(s[p]!=s[i]){
				p-=1;break;
			}
		}
		tree[++size]=s[i];
		vis[s[i]]=1;
		for(int o=1;o<=p-i;o++){
			while(vis[now]) now+=1;
			tree[++size]=now;
			vis[now]=1;now+=1;
		}
		last=s[i];
		i=p;
	}
	cout<<"YES\n";
	for(int i=1;i<size;i++){
		cout<<tree[i]<<" "<<tree[i+1]<<"\n";
	}
}
```

---

