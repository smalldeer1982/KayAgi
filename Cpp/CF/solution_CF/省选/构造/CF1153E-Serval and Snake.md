# Serval and Snake

## 题目描述

这是一个交互题。

现在 Serval 是 Japari 中学的一名高中生。然而，在去学校的路上，他必须穿过一个池塘，池塘里有一条危险的蛇。池塘可以表示为一个 $n \times n$ 的网格。蛇有一个头和一个尾，分别位于不同的格子中，蛇的身体是一系列相邻的格子，将头和尾连接起来，且不会自交。如果 Serval 碰到蛇的头或尾，蛇会咬他，他就会死。

幸运的是，他有一个特殊的装置，可以回答如下问题：你可以选择一个矩形区域，装置会告诉你，从蛇头到蛇尾沿着蛇的身体一格一格走时，需要穿过这个矩形边界的次数。下图展示了一条可能的蛇和一次对它的查询，答案为 $4$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153E/53fbbb51794507f6b8da5b86b0ce29d37f526437.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153E/310ecca9dbe4567ceada9b3d4a9ef179d283444f.png)

今天 Serval 起得太晚了，只能进行 $2019$ 次查询。作为他最好的朋友，你能帮他找出蛇头和蛇尾的位置吗？

注意，只有当两个格子有公共边时才算相邻，蛇的身体长度可以为 $0$，也就是说蛇只有头和尾且它们相邻。

另外，蛇正在睡觉，在 Serval 使用装置时不会移动。显然，蛇的位置与你的查询无关。

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153E/99e348aaccc97b295d205879f6d57ecbaca07b05.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153E/ce15833a1657c0eb9be15429504c2d44fae6f2bb.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153E/6d1e7d0b5adac9acef6d724724f8372e63587c4e.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153E/7ed306531d047140f56616a504d648434c6c8f4f.png)

上图展示了第一个样例中的查询和答案。我们首先对 $(1,1)$ 进行了查询，得到答案 $1$，于是知道它必须与另一个格子相连。然后我们对 $(1,2)$ 查询，得到答案 $0$，于是知道蛇从未经过这里。因此，与 $(1,1)$ 相连的格子只能是 $(2,1)$。接着我们对 $(2,2)$ 查询，得到答案 $0$，也知道蛇从未经过 $(2,2)$。所以蛇无法离开 $(2,1)$，这意味着答案是 $(1,1)$ 和 $(2,1)$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153E/d087b7ee2ce64273a766b278b890efa6686245bd.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153E/dc08e571bf34cdde551ce5154f9dbe2876bddd43.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153E/50d2eabe2572f343f866cfbec6f391d3bf47c83f.png)

上图展示了第二个样例中的查询和答案。通过对 $(2,2)$ 查询并得到 $2$，我们发现蛇占据了 $(2,2)$。再对从 $(2,1)$ 到 $(2,3)$ 的矩形查询，得到答案 $0$，于是知道蛇从未离开这个矩形。由于第一个答案是 $2$，说明 $(2,1)$ 和 $(2,3)$ 都被蛇占据，其他格子没有被占据，所以答案是 $(2,1)$ 和 $(2,3)$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2

1

0

0
```

### 输出

```

? 1 1 1 1

? 1 2 1 2

? 2 2 2 2

! 1 1 2 1```

## 样例 #2

### 输入

```
3

2

0
```

### 输出

```

? 2 2 2 2

? 2 1 2 3

! 2 1 2 3```

# 题解

## 作者：Dilute (赞：4)

[$$\huge\texttt{在本人blog食用更佳}$$](https://dilute.xyz/2019/04/14/Solutions/Solution-CF1153E/)

## 有趣的交互题

我们考虑一件事情

如果我们询问的矩形中有一个端点

那么答案 $\mod 2 = 1$

否则答案 $\mod 2 = 0$

换句话说，就是如果询问到的答案$\mod 2 = 0$，那么这个矩形内要么没有端点，要么有两个端点

我们考虑

如果两个答案不在同一行

那么我们可以$O(n)$次询问找到这两行然后二分答案，这是非常简单易懂轻松愉快的

如果在同一行

那么他们肯定不在同一列

然后我们只需要找到他们中的一个，而且只需要二分一次就行了

因为两个在同一行，他们有一维坐标是一样的，如果二分两次的话被卡满就是$n + n + 2\log n = 2020$次询问，刚刚好爆掉（来自出题人的恶意）

## 代码

```cpp
#include<bits/stdc++.h>

#define ll long long
#define INF 2147483647

int inp(){
    char c = getchar();
    while(c < '0' || c > '9')
        c = getchar();
    int sum = 0;
    while(c >= '0' && c <= '9'){
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return sum;
}

std::pair<int, int> ans[4];
int n;

int query(int x1, int y1, int x2, int y2){
    printf("? %d %d %d %d\n", x1, y1, x2, y2);
    fflush(stdout);
    return inp();
}

int solve1(int cur){
    int l = 1;
    int r = n;
    while(l < r){
        int mid = (l + r) >> 1;
        if(query(cur, l, cur, mid) & 1)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}

int solve2(int cur){
    int l = 1;
    int r = n;
    while(l < r){
        int mid = (l + r) >> 1;
        if(query(l, cur, mid, cur) & 1)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}

int main(){
    n = inp();
    int cnt = 0;
    for(int i = 1; i <= n; i++){
        int num = query(i, 1, i, n);
        if(num & 1)
            ans[++cnt] = std::make_pair(i, solve1(i));
    }
    if(cnt == 0){
        for(int i = 1; i <= n; i++){
            int num = query(1, i, n, i);
            if(num & 1){
                if(cnt == 0)
                    ans[++cnt] = std::make_pair(solve2(i), i);
                else
                    ans[++cnt] = std::make_pair(ans[1].first, i);
            }
        }
    }
    printf("! %d %d %d %d\n", ans[1].first, ans[1].second, ans[2].first, ans[2].second);
    fflush(stdout);
}
```

---

## 作者：xukuan (赞：4)

二分答案+交互

首先我们可以发现，如果询问结果是奇数，那么头尾中必有一个在里面而另一个不在。

我们可以对每行每列进行询问，如果一行的结果为奇数，就二分这一行找到答案。

两个如果都找到就直接跳出去

最多多少次？

n\*2+(\[logn\]+1)\*2

当n=1000是这个是2020

刚好多一个QAQ

怎么办？

如果前面只有一个解，第1000列不用问了，直接二分，刚好省一次

代码：

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll n,x1,Y1,x2,y2;

inline ll read(){
    ll x=0,tmp=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-') tmp=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<3)+(x<<1)+ch-48;
        ch=getchar();
    }
    return tmp*x;
}

inline bool check_hang(ll x){//对每行进行二分
    ll l=1,r=n,mid=(l+r)>>1,ans;
    while(l<=r){
        printf("? %I64d %I64d %I64d %I64d\n",x,l,x,mid); fflush(stdout);
        if(read()&1){ans=mid;r=mid-1;}
        else l=mid+1;
        mid=(l+r)>>1;
    }
    if(x1==0){x1=x;Y1=ans;} 
    else{x2=x;y2=ans;} 
}

inline bool check_lie(ll x){//对每列进行二分
    ll l=1,r=n,mid=(l+r)>>1,ans;
    while(l<=r){
        printf("? %I64d %I64d %I64d %I64d\n",l,x,mid,x); fflush(stdout);
        if(read()&1){ans=mid;r=mid-1;}
        else l=mid+1;
        mid=(l+r)>>1;
    }
    if(x1==0){x1=ans;Y1=x;} 
    else{x2=ans;y2=x;} 
}

int main(){
    n=read();
    for(ll i=1; i<=n; i++){
    	if(x2) break;//这句话一定要写在前面
        printf("? %I64d 1 %I64d %I64d\n",i,i,n); fflush(stdout);//检查
        if(read()&1) check_hang(i);//如果可以确定在这一行（列），就二分
    }
    //同上
    for(ll i=1; i<n; i++){
    	if(x2) break;
        printf("? 1 %I64d %I64d %I64d\n",i,n,i); fflush(stdout);
        if(read()&1) check_lie(i);
    }
    if(x2==0) check_lie(n);//前1000行和999列都没有找到第二个解
    printf("! %I64d %I64d %I64d %I64d\n",x1,Y1,x2,y2); fflush(stdout);//输出并结束
    return 0;
}
```

---

## 作者：da32s1da (赞：3)

考虑对于一个矩形，如果里面有**一个**头(或尾)，那么答案一定是奇数。

直接查询每一行，每一列，会得到$2$个或$4$个奇数。

- $2$个奇数：头和尾在同一行或同一列
- $4$个奇数，头和尾在不同行不同列

对于一个奇数行或列，直接**二分**，就能得到头或尾了

需要的最大步数是$2\times 1000+2\times \lfloor\log_2n\rfloor=2020$。好像有点多啊

考虑**查询完$n-1$行**时，若之前有一个奇数，那么第$n$行一定是奇数，若之前没有奇数，那么第$n$行一定是偶数。

这样最大步数就是$2020-2=2018$步了，可以通过此题。

但是有没有更无耻一点的做法呢？

**随机询问！**

直接使用$2020$步的做法，随机询问行和列，然后再二分。

CF评测时300~1800步出答案 ~~运气还是不错的~~

这里给出随机询问的做法

```cpp
#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef pair<int,int> pr;
typedef pair<int,pr> prr;
int n,opt,x,wz1,wz2,ans1,ans2;prr a[2019];
int main(){
	srand((int)time(0));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)a[i]=prr(rand()*rand(),pr(i,1));
	for(int i=1;i<=n;i++)a[i+n]=prr(rand()*rand(),pr(i,2));
	sort(a+1,a+n+n+1);//随机行和列
	for(int i=1;i<=n+n;i++){
		if(opt&&a[i].second.second!=opt)continue;//找到第一个奇数后，只询问行或只询问列
		if(a[i].second.second==1)
			printf("? %d %d %d %d\n",a[i].second.first,1,a[i].second.first,n);
		else printf("? %d %d %d %d\n",1,a[i].second.first,n,a[i].second.first);//询问
		fflush(stdout);
		scanf("%d",&x);
		if(x&1)
			if(!opt)opt=a[i].second.second,wz1=a[i].second.first;//找到第一个奇数，并钦定询问行还是列
			else {wz2=a[i].second.first;break;}//找到第二个奇数，直接break
	}
	if(opt==1){//行
		for(int l=1,r=n,m;l!=r;ans1=l){//二分找答案
			m=l+r>>1;
			printf("? %d %d %d %d\n",wz1,l,wz1,m);
			fflush(stdout);
			scanf("%d",&x);
			if(x&1)r=m;
			else l=m+1;
		}
		for(int l=1,r=n,m;l!=r;ans2=l){//二分找答案
			m=l+r>>1;
			printf("? %d %d %d %d\n",wz2,l,wz2,m);
			fflush(stdout);
			scanf("%d",&x);
			if(x&1)r=m;
			else l=m+1;
		}
		printf("! %d %d %d %d\n",wz1,ans1,wz2,ans2);
	}else{//列
		for(int l=1,r=n,m;l!=r;ans1=l){//二分找答案
			m=l+r>>1;
			printf("? %d %d %d %d\n",l,wz1,m,wz1);
			fflush(stdout);
			scanf("%d",&x);
			if(x&1)r=m;
			else l=m+1;
		}
		for(int l=1,r=n,m;l!=r;ans2=l){//二分找答案
			m=l+r>>1;
			printf("? %d %d %d %d\n",l,wz2,m,wz2);
			fflush(stdout);
			scanf("%d",&x);
			if(x&1)r=m;
			else l=m+1;
		}
		printf("! %d %d %d %d\n",ans1,wz1,ans2,wz2);
	}
}
```

---

## 作者：small_john (赞：2)

## 思路

很明显，对于一个矩阵，如果对其询问的结果是奇数，那么矩阵中一定有一个头或者尾。感性理解一下，如果满足上述条件，说明进去了没出来，或者出来了没进去，就是有一个头或者尾。

那么询问每一行、每一列，如果找到在行上找到两个不同的行结果是奇数，就对这两行二分。列是同理的。

这样询问次数被卡满就是 $2\times 1000+2\times \lceil \log_2 n\rceil=2020$ 的，刚好超了一次。

发现在询问完 $n$ 行和 $n-1$ 列后如果还没找到，那么最后一列一定是合法的，可以省一次。

这样就能 AC 了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3+5;
int n,cnt;
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%d",&n);
	int p1 = -1,p2 = -1;
	for(int i = 1;i<=n;i++)
	{
		printf("? %d 1 %d %d\n",i,i,n);
		fflush(stdout);
		int x;
		scanf("%d",&x);
		if(x&1)
		{
			if(p1==-1) p1 = i;
			else
			{
				p2 = i;
				break;
			}
		}
	}
	if(p2!=-1)
	{
		int ans1,ans2,l = 1,r = n;
		while(l<r)
		{
			int mid = (l+r)/2;
			printf("? %d %d %d %d\n",p1,l,p1,mid);
			fflush(stdout);
			int x;
			scanf("%d",&x);
			if(x&1) r = mid;
			else l = mid+1;
		}
		ans1 = l;
		l = 1,r = n;
		while(l<r)
		{
			int mid = (l+r)/2;
			printf("? %d %d %d %d\n",p2,l,p2,mid);
			fflush(stdout);
			int x;
			scanf("%d",&x);
			if(x&1) r = mid;
			else l = mid+1;
		}
		ans2 = l;
		printf("! %d %d %d %d\n",p1,ans1,p2,ans2);
		fflush(stdout);
		return 0;
	}
	p1 = -1,p2 = -1;
	for(int i = 1;i<=n;i++)
	{
		if(p2==-1&&i==n)
		{
			p2 = n;
			break;
		}
		printf("? 1 %d %d %d\n",i,n,i);
		fflush(stdout);
		int x;
		scanf("%d",&x);
		if(x&1)
		{
			if(p1==-1) p1 = i;
			else
			{
				p2 = i;
				break;
			}
		}
	}
	if(p2!=-1)
	{
		int ans1,ans2,l = 1,r = n;
		while(l<r)
		{
			int mid = (l+r)/2;
			printf("? %d %d %d %d\n",l,p1,mid,p1);
			fflush(stdout);
			int x;
			scanf("%d",&x);
			if(x&1) r = mid;
			else l = mid+1;
		}
		ans1 = l;
		l = 1,r = n;
		while(l<r)
		{
			int mid = (l+r)/2;
			printf("? %d %d %d %d\n",l,p2,mid,p2);
			fflush(stdout);
			int x;
			scanf("%d",&x);
			if(x&1) r = mid;
			else l = mid+1;
		}
		ans2 = l;
		printf("! %d %d %d %d\n",ans1,p1,ans2,p2);
		fflush(stdout);
	}
	return 0;
}
```

---

## 作者：λᴉʍ (赞：2)

# CF1153E Serval and Snake


---

题意简单版：

在$n\times m$的方格上有一条链（蛇），你需要通过查询来找出这条链的两个端点。

你的查询形如`x1 y1 x2 y2`，这可以确定一个矩形，查询结果是链在矩形上的边数。

你最多能进行$2019$次查询。最后请输出`x1 y1 x2 y2`，表示链两个端点的坐标。

可以对于两个端点的x,y坐标分别查询。

假设现在先确定x坐标，先查询蛇与每一根竖线的交边数，设为$cn_i$。

如果蛇与一根竖线的交边数是奇数，那么表示两个顶点在这条线的两端，否则在同一边。

如果$x1\neq x2$，那么$cn$数组将会是一段偶数，一段奇数，接着一段偶数。那么可以通过中间一段奇数的左右端点知道$x1,x2$。

否则如果$x1=x2$，$cn$数组就是一整段偶数。

那么现在如果$x1\neq x2$可以知道$x1,x2$的确切值；否则只知道$x1=x2$。

对于$y$也这样做一遍，现在有两种情况：

如果$x,y$确切值都知道了，那么注意一下你不知道端点是$(x1,y1),(x2,y2)$还是$(x1,y2),(x2,y1)$，所以要多查询一次。

否则肯定只有一个坐标相等而且不知道，可以二分求出。注意这里就不需要再多查询一次了，然而我代码里没判

那么总的查询次数最坏应该是$999+999+10$的。（？）

```cpp
#include<bits/stdc++.h>
#define il inline
#define vd void
#define rg register
#define ll long long
il int gi(){
    rg int x=0,f=0;rg char ch=getchar();
    while(!isdigit(ch))f^=ch=='-',ch=getchar();
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}
int cn[1010],cm[1010];
int main(){
    int n=gi();
    for(int i=1;i<n;++i){
        printf("? %d %d %d %d\n",1,1,i,n);
        fflush(stdout);
        cn[i]=gi();
    }
    for(int i=1;i<n;++i){
        printf("? %d %d %d %d\n",1,1,n,i);
        fflush(stdout);
        cm[i]=gi();
    }
    int x1,x2,y1,y2;
    {
        int mn=1e9,mx=0;
        for(int i=1;i<n;++i)if(cn[i]&1)mn=std::min(mn,i),mx=std::max(mx,i);
        if(mn==1e9&&mx==0)x1=x2=0;
        else x1=mn,x2=mx+1;
    }
    {
        int mn=1e9,mx=0;
        for(int i=1;i<n;++i)if(cm[i]&1)mn=std::min(mn,i),mx=std::max(mx,i);
        if(mn==1e9&&mx==0)y1=y2=0;
        else y1=mn,y2=mx+1;
    }
    if(x1==0&&x2==0){
        int l=1,r=n,mid;
        while(l<r){
            mid=(l+r)>>1;
            printf("? %d %d %d %d\n",1,y1,mid,y1);
            fflush(stdout);
            if(gi()&1)r=mid;
            else l=mid+1;
        }
        x1=x2=l;
    }
    if(y1==0&&y2==0){
        int l=1,r=n,mid;
        while(l<r){
            mid=(l+r)>>1;
            printf("? %d %d %d %d\n",x1,1,x1,mid);
            fflush(stdout);
            if(gi()&1)r=mid;
            else l=mid+1;
        }
        y1=y2=l;
    }
    printf("? %d %d %d %d\n",x1,y1,x1,y1);
    fflush(stdout);
    if(gi()!=1)std::swap(x1,x2);
    printf("! %d %d %d %d\n",x1,y1,x2,y2);
    return 0;
}
```

---

## 作者：花里心爱 (赞：2)

这是一道交互题。

我们先观察那个~~很像插头dp的~~图：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153E/310ecca9dbe4567ceada9b3d4a9ef179d283444f.png)

然后考虑一个矩形里连出去的边的数量有什么性质。

然后我们可以发现当边的数量为奇数时，一定有且仅有1个端点在矩形里面，另外一个端点在矩形外面。

然后我们需要用尽量少的询问去定位这两个端点。

然后看数据范围，$n \leq 1000$，而且还可以做$2019$次询问。

然后我们发现如果我们要定位的话，只需要分别对每一行和每一列做询问就可以确定端点在哪两行和哪两列了。

但是这样有一个问题：可能有两个端点在一行（或一列）的情况出现，比如：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153E/50d2eabe2572f343f866cfbec6f391d3bf47c83f.png)

（没错这就是第二个样例）

这时候根据对行和列的询问，我们知道了端点在第1列和第3列，但不知道它在哪一行。

于是我们分别考虑，对这两列做二分。方法是每次取$mid$，然后看$[l, mid]$向外连了多少条边。如果是奇数的话说明这个端点在$[l, mid]$内，否则在$[mid+1, r]$内。

这样我们总共做了$n+n+logn+logn$次询问，当$n = 1000$时询问次数正好为$2020$，~~被卡了一次~~qwq

然后我们考虑一个~~神奇的~~性质。我们在对行和列分别进行询问的时候，可能出现两种情况：

1. 两个端点不在同一行（列）。这个时候我们一定能得到2个奇数的答案。

2. 两个端点在同一行（列）。这个时候我们一定得不到奇数的答案。

然后我们只要询问了前$n-1$行（列），就可以知道第$n$行（列）的奇偶性了，这样我们少了2次询问，剩下$2018$次，可以过了qwq

总代码（~~比较鬼畜~~）：
```cpp
#include <cstdio>
int n, res;
int lpos[5], totl, rpos[5], totr;
int main() {
    scanf("%d", &n);
    for(int i = 1; i < n; ++i) {
        printf("? %d %d %d %d\n", i, 1, i, n);
        fflush(stdout);
        scanf("%d", &res);
        if(res&1) lpos[++totl] = i;
    }
    if(totl == 1) lpos[++totl] = n;
    if(totl == 2) {
        // 这里如果发现两个端点在不同的行了，就没有必要再去对列做询问了
        int l = 1, r = n;
        for(int i = 1; l < r && i <= 10; ++i) {
            int mid = (l+r)>>1;
            printf("? %d %d %d %d\n", lpos[1], l, lpos[1], mid);
            fflush(stdout);
            scanf("%d", &res);
            if(res&1) r = mid;
            else l = mid+1;
        }
        int lans = r;
        l = 1, r = n;
        for(int i = 1; l < r && i <= 10; ++i) {
            int mid = (l+r)>>1;
            printf("? %d %d %d %d\n", lpos[2], l, lpos[2], mid);
            fflush(stdout);
            scanf("%d", &res);
            if(res&1) r = mid;
            else l = mid+1;
        }
        printf("! %d %d %d %d", lpos[1], lans, lpos[2], r);
        return 0;
    }
    // 如果两个端点在相同的行，它们一定在不同列
    for(int i = 1; i < n; ++i) {
        printf("? %d %d %d %d\n", 1, i, n, i);
        fflush(stdout);
        scanf("%d", &res);
        if(res&1) rpos[++totl] = i;
    }
    if(totl == 1) rpos[++totl] = n;
    int l = 1, r = n;
    for(int i = 1; l < r && i <= 10; ++i) {
        int mid = (l+r)>>1;
        printf("? %d %d %d %d\n", l, rpos[1], mid, rpos[1]);
        fflush(stdout);
        scanf("%d", &res);
        if(res&1) r = mid;
        else l = mid+1;
    }
    int lans = r;
    l = 1, r = n;
    for(int i = 1; l < r && i <= 10; ++i) {
        int mid = (l+r)>>1;
        printf("? %d %d %d %d\n", l, rpos[2], mid, rpos[2]);
        fflush(stdout);
        scanf("%d", &res);
        if(res&1) r = mid;
        else l = mid+1;
    }
    printf("! %d %d %d %d", lans, rpos[1], r, rpos[2]);
    return 0;
}
```
然后我们实际上还可以继续优化。

我们发现在上面的代码中，如果我们发现两个端点在同一行不同列中，实际上我们只需要对一列进行二分，另一列的端点所在行与这一个相同。

于是我们做到了最多使用$2008$次询问。

---
表示我做完这道题（用的是$2018$次询问的做法）之后，发现CF给的标算只需要$2007$次询问。于是我去翻了CF的官方题解。

然后大体思路是：我们只对$2$到$n-1$的行询问，对于列还是询问$1$到$n-1$。然后分3种情况：

1. 我们都没有询问到答案，那么两个端点一定在同一列，而且一个在第$1$行，一个在第$n$行。然后用上面$2008$次询问的方法进行二分，于是我们只需要$2007$次。

2. 在行上没有询问到答案，但我们知道了两个端点分别在哪一列。根据上面的思路，两个端点要么在同一行，要么一个在第$1$行，一个在第$n$行。对于后一种情况，我们需要多一次询问来确定它是不是同一行。这样我们需要减少二分的次数。我们发现当我们需要多一次询问时，最终二分到的结果要么是$1$要么是$n$，所以我们只需要让包含$1$或$n$的区间短一点即可。（这样做如果答案不是$1$或$n$，询问数没有改变，但我们也不需要那个多余的询问了）仍然只需要$2007$次。

3. 在行上询问到了答案，直接分别二分即可，询问不会超过$1019$次。

---
所以，有些题目的优化方案是一步一步优化出来的，这时我们需要充分利用题目的性质来优化我们的算法。

---

## 作者：xht (赞：1)

题目地址：[CF1153E Serval and Snake](https://www.luogu.org/problemnew/show/CF1153E)

这是一道交互题

由于只需要确定起点和终点

你选择的矩形会将整个矩形分成的两个部分

如果起点和终点在同一个部分里，那么很显然回答应该是个偶数

反之则为奇数

因此我们可以先通过

```cpp
	int i;
	for (i = 1; i < n; i++) {
		printf("? 1 1 %d %d\n", n, i);
		fflush(stdout);
		scanf("%d", &x);
		if (x & 1) break;
	}
```

来确定起点和终点是否在同一列

如果不在同一列（即 $i!=n$ ），那么 $i$ 即为起点和终点这两个点中靠左的那个点所在的列

那么同理可以找到起点和终点这两个点中靠右的那个点所在的列

如果在同一列（即 $i==n$ ） ，那么他们肯定不会在同一行（因为起点和终点是不同的点）

那么可以用同样的方法将两个点确定在两行内

现在已经能够锁定两个点在哪两条（行或列）了

在一条中确定一个点，二分再用奇偶判断即可

这样最坏的询问次数为 $999+1000+10+10=2019$

正好！

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, x, i, j;
int ax1, ay1, ax2, ay2;

int main() {
	cin >> n;
	for (i = 1; i < n; i++) {
		printf("? 1 1 %d %d\n", n, i);
		fflush(stdout);
		scanf("%d", &x);
		if (x & 1) break;
	}
	if (i != n) {
		for (j = n; j > 1; j--) {
			printf("? 1 %d %d %d\n", j, n, n);
			fflush(stdout);
			scanf("%d", &x);
			if (x & 1) break;
		}
		int l = 1, r = n;
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			printf("? %d %d %d %d\n", mid, i, n, i);
			fflush(stdout);
			scanf("%d", &x);
			if (x & 1) l = mid;
			else r = mid - 1;
		}
		ax1 = l, ay1 = i;
		l = 1, r = n;
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			printf("? %d %d %d %d\n", mid, j, n, j);
			fflush(stdout);
			scanf("%d", &x);
			if (x & 1) l = mid;
			else r = mid - 1;
		}
		ax2 = l, ay2 = j;
	} else {
		for (i = 1; i < n; i++) {
			printf("? 1 1 %d %d\n", i, n);
			fflush(stdout);
			scanf("%d", &x);
			if (x & 1) break;
		}
		for (j = n; j > 1; j--) {
			printf("? %d 1 %d %d\n", j, n, n);
			fflush(stdout);
			scanf("%d", &x);
			if (x & 1) break;
		}
		int l = 1, r = n;
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			printf("? %d %d %d %d\n", i, mid, i, n);
			fflush(stdout);
			scanf("%d", &x);
			if (x & 1) l = mid;
			else r = mid - 1;
		}
		ax1 = i, ay1 = l;
		l = 1, r = n;
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			printf("? %d %d %d %d\n", j, mid, j, n);
			fflush(stdout);
			scanf("%d", &x);
			if (x & 1) l = mid;
			else r = mid - 1;
		}
		ax2 = j, ay2 = l;
	}
	printf("! %d %d %d %d\n", ax1, ay1, ax2, ay2);
	return 0;
}
```

---

## 作者：hh弟中弟 (赞：0)

感觉比较平凡，不知道为啥有紫。\
只有端点的度为 $1$，所以如果一个询问结果是奇数，端点一定在这个范围内，不难想到对于所有行问一次，对于所有列问一次，接下来有两种情况。
- 端点在不同行，不同列，这时直接问一个点是否是端点就能确定位置了。
- 端点在同行或同列，只说下同行，这时已经确定了端点所在的两列，只考虑一列，在这一列上二分询问，端点在结果是奇数的一部分，然后就可以找到端点所在行数，同列同理。

总次数不会超过 $2009$，感觉答案范围的提示性也很强。
```cpp
#include<bits/stdc++.h>
#define endl std::endl
#define fi first
#define se second
#define pii std::pair<int,int>
#define eb emplace_back
#define pb push_back
typedef long long ll;
typedef unsigned long long ull;
std::mt19937 myrand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
inline int R(int n){return myrand()%n+1;}
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
const int N=2e5+10,mod=998244353,inf=1e9;
inline void Min(int &x,int y){if(x>y)x=y;}
inline void Max(int &x,int y){if(x<y)x=y;}
int n;
int h1,h2,l1,l2;
inline int ask(int i,int j,int x,int y){
	std::cout<<"? "<<i<<' '<<j<<' '<<x<<' '<<y<<endl;
	int cnt;std::cin>>cnt;return cnt&1;
}
inline void anwser(int i,int j,int x,int y){
	std::cout<<"! "<<i<<' '<<j<<' '<<x<<' '<<y<<endl;
}
signed main(){
    // freopen("in.in","r",stdin);freopen("out.out","w",stdout);
    // std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
	std::cin>>n;
	for(int i=1;i<=n;++i){
		if(ask(1,i,n,i)){
			if(l1)l2=i;
			else l1=i;
		}
	}
	for(int i=1;i<=n;++i){
		if(ask(i,1,i,n)){
			if(h1)h2=i;
			else h1=i;
		}
	}
	if(h1&&h2&&l1&&l2){
		if(ask(h1,l1,h1,l1)){
			anwser(h1,l1,h2,l2);
		}else{
			anwser(h1,l2,h2,l1);
		}
	}
	if(h1&&h2){
		int l=1,r=n;
		while(l<r){
			int mid=l+r>>1;
			if(ask(1,l,h1,mid)){
				r=mid;
			}else l=mid+1;
		}
		anwser(h1,l,h2,l);
	}else{
		int l=1,r=n;
		while(l<r){
			int mid=l+r>>1;
			if(ask(l,1,mid,l1)){
				r=mid;
			}else l=mid+1;
		}
		anwser(l,l1,l,l2);
	}
}
```

---

## 作者：Populus_euphratica (赞：0)

## 做法 

首先考虑如何通过询问一个矩形的返回值来判断这个矩形是否存在端点。

可以分三种情况讨论：

1. 如果这个矩形中不存在端点，那么如果有一个进入这个矩形的边，那么相对应地一定会有一条出这个矩形的边，这是显然的，因为没有端点在矩形内，所以有一个进就一定有一个出，那么这种情况的返回值就一定是个偶数。
2. 如果这个矩形中只存在一个端点，那么就会有一条进入的边无法匹配出边或者一条出边无法匹配上入边，原因和上面相反，所以这种情况的返回值就一定是个奇数。
3. 如果这个矩形中存在两个端点，那么一条出边一定可以匹配上一条入边，这是显然的，原因和第一条一样，这种情况的返回值一定是个偶数。

可以考虑先按照每一行枚举，这样第二种情况非常好判断，找到那两个返回值为奇数的行二分一下列即可。

现在来考虑如果两个端点在一行的情况。

如果在同一行，那么显然不再同一列，枚举一下列然后二分行即可。

值得注意的是如果对于两个端点都二分列会超出询问数的上界，又考虑到两个端点在同一行，那么在找到第二个点所在的列时直接继承上一个的行即可。

最大询问次数卡满是：$n + n + \log n$ 的，小于 2019。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m;
pair<int, int> ans[5];
int Out(int x1, int y1, int x2, int y2){
    cout << "? " << x1 << " " << y1 << " " << x2 << " " << y2 << '\n';
    fflush(stdout);
    int x;
    cin >> x;
    return x;
}
int solve(int x, int op){
    int ans = 0;
    int l = 1, r = n;
    while(l <= r){
        int mid = (l + r) >> 1;
        int s;
        if(!op) s = Out(x, l, x, mid);
        else s = Out(l, x, mid, x);
        if(s & 1) r = mid - 1, ans = mid;
        else l = mid + 1;
    }
    return ans;
}
signed main(){
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 1 ; i <= n ; i++){
        int s = Out(i, 1, i, n);
        if(s & 1) ans[++m] = {i, solve(i, 0)};
    }
    if(!m){
        for(int i = 1 ; i <= n ; i++){
            int s = Out(1, i, n, i);
            if(s & 1){
                if(!m) ans[++m] = {solve(i, 1), i};
                else ans[++m] = {ans[1].first, i};
            }
        }
    }
    cout << "! " << ans[1].first << " " << ans[1].second << " " << ans[2].first << " " << ans[2].second << '\n';
    return 0;
}
```

---

## 作者：LYY_yyyy (赞：0)

这题有一个关键的结论：对于每次询问，若回答是奇数，则该矩形中有 $1$ 个原图中的头 $/$ 尾，若是偶数，则该矩形中有 $0/2$ 个原图中的头 $/$ 尾。证明思路较简单。我们可以将询问矩形中的图分成若干个链考虑，然后分类讨论每种链的头 $/$ 尾对询问的贡献即可证明该结论。

有了这个结论，我们就可以考虑先询问每行每列。由于两个点不可能同时属于同一行同一列，所以我们的询问一定会有回答奇数的行 $/$ 列。对于每个回答为奇数的行 $/$ 列，我们二分询问出在这一行的头 $/$ 尾的第二个坐标即可。实现时注意判重。

关于询问次数，我们可以发现最后一行 $/$ 列可以通过前面的询问推知，于是询问行 $/$ 列的最大次数为 $999\times2=1998$ 次，每次二分的最大次数为 $\lceil \log_21000 \rceil=10$ 次，总次数最大值为 $1998+2\times10=2018$ 次，可以通过本题。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int h[1010],l[1010];
bool vis[1010][3];
bool check(int ask,int now){
	cout<<"? "<<ask<<' '<<1<<" "<<ask<<' '<<now<<endl;
	int p;
	cin>>p;
	if(p%2) return 0;
	return 1;
}
bool check1(int ask,int now){
	cout<<"? "<<1<<' '<<ask<<" "<<now<<' '<<ask<<endl;
	int p;
	cin>>p;
	if(p%2) return 0;
	return 1;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n-1;i++)
	{
		cout<<"? "<<i<<" 1 "<<i<<' '<<n<<endl;
		cin>>h[i];
		cout<<"? 1 "<<i<<' '<<n<<' '<<i<<endl;
		cin>>l[i]; 
	}
	int last=h[1];
	for(int i=2;i<n;i++) last=h[i]-last;
	h[n]=last;
	last=l[1];
	for(int i=2;i<n;i++) last=l[i]-last;
	l[n]=last;
	typedef pair<int,int> pii;
	vector<pii> s;	
	for(int i=1;i<=n;i++)
	{
		if(h[i]%2) s.push_back({i,1});
		if(l[i]%2) s.push_back({i,2});	
	}
	vector<pii> anss;
	for(auto i:s)
	{
		if(vis[i.first][i.second]) continue;
		if(i.second==1)
		{
			int l=1,r=n,ans;
			while(l<=r)
			{
				int mid=l+r>>1;
				if(check(i.first,mid)) l=mid+1;
				else r=mid-1,ans=mid;
			}
			anss.push_back({i.first,ans});
			vis[ans][2]=1;
		}
		else
		{
			int l=1,r=n,ans;
			while(l<=r)
			{
				int mid=l+r>>1;
				if(check1(i.first,mid)) l=mid+1;
				else r=mid-1,ans=mid;
			}
			anss.push_back({ans,i.first});
			vis[ans][1]=1;
		}
	}
	cout<<"! ";
	for(auto i:anss) cout<<i.first<<' '<<i.second<<' ';
	cout<<endl;
	return 0;
}
```


---

## 作者：_sys (赞：0)

对于**头和尾不在一行**的情况
![](http://1.z9ls.com/t6/701/1555215072x2890205873.png)
我们可以发现，我们每次取出一行来询问，得到的答案如果是奇数，那么这一行里必然有头或者尾。

比如上图询问$1,2,3$行得到的答案是$1,3,2$

那么这样我们可以确定头和尾在哪一行。

列的处理同理。

之后呢，我们就会得到两行$x1,x2$两列$y1,y2$，那这两个点一定是$(x1,y1),(x2,y2)$或$(x1,y2),(x2,y1)$，那我们询问一下$(x1,y1)$这一个点，看一下是不是奇数就可以确定了。

上面操作是$2*n+1(<=2001)$次的

但是如果**头和尾在同一行**

那他俩一定不在同一列，我们先可以确定$y1,y2$

然后我们发现如果询问$(1,1)~(z,y1$和$y2$间的一个数$)$，结果为奇数，那么真正的位置$x<=z$

（如图）

![](http://1.z9ls.com/t6/701/1555215764x2890205861.png)

如果$z=1$（红框），会得到$0$，说明$x>1$

如果$z=2$（橙框），会得到$1$，说明$x<=2$

那我们就可以愉快地二分啦！

注意上面例子的两个结果虽然是$0$和$1$，但是必须判断是否是奇数而不是是否有值，因为可能无关的线会影响结果。如下图。

![](http://1.z9ls.com/t6/701/1555216083x2890205873.png)

代码:
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,X[3],Y[3],cnt,x;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		printf("? %d %d %d %d\n",i,1,i,n);
		fflush(stdout);
		scanf("%d",&x);
		if(x%2)
			 X[++cnt]=i;
	}
	cnt=0;
	for(int i=1;i<=n;i++)
	{
		printf("? %d %d %d %d\n",1,i,n,i);
		fflush(stdout);
		scanf("%d",&x);
		if(x%2)
			 Y[++cnt]=i;
	}
	if(X[2]&&Y[2])
	{
		printf("? %d %d %d %d\n",X[1],X[1],Y[1],Y[1]);
		fflush(stdout);
		scanf("%d",&x);
		if(x%2)
			printf("! %d %d %d %d\n",X[1],Y[1],X[2],Y[2]),fflush(stdout);
		else printf("! %d %d %d %d\n",X[1],Y[2],X[2],Y[1]),fflush(stdout);
		return 0;
	}
	else
	{
		if(!X[1])
		{
			int YY=(Y[1]+Y[2])/2;
			int l=1,r=n;
			while(l+1<=r)
			{
				int mid=(l+r)/2;
				printf("? 1 1 %d %d\n",mid,YY);
				fflush(stdout);
				scanf("%d",&x);
				if(x%2)
					r=mid;
				else l=mid+1;
			}
			printf("! %d %d %d %d\n",l,Y[1],l,Y[2]);
			fflush(stdout);
			return 0;
		}
		if(!Y[1])
		{
			int XX=(X[1]+X[2])/2;
			int l=1,r=n;
			while(l+1<=r)
			{
				int mid=(l+r)/2;
				printf("? 1 1 %d %d\n",XX,mid);
				fflush(stdout);
				scanf("%d",&x);
				if(x%2)
					r=mid;
				else l=mid+1;
			}
			printf("! %d %d %d %d\n",X[1],l,X[2],l);
			fflush(stdout);
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：luan341502 (赞：0)

对于字典序最小类问题，显然我们应该贪心地使得当前最优。

因此，对于当前位置 $i$，要使得答案最小，从优到劣的选择方案是 $n-a_i,n-a_i+1,n-a_i+2,\dots,n-1,0,1,\dots,n-a_i-1$，因为可以知道对应的答案依次递增。

我们维护一个 multiset，对于每个 $a_i$ 使用 lower_bound 查询大于等于 $n-a_i$ 的第一个数，若不存在便选择集合的最小的数。

时间复杂度为 $O(n\log n)$。

**警钟长鸣：对于 set，multiset 这一类基于红黑树的 STL，在使用 lower_bound 函数时要使用内置版本，否则单次查询的时间复杂度为 $O(n)$。**

```cpp
#include<bits/stdc++.h>
using namespace std;
int tt;
int n,a[200005];
void solve(){
	cin>>n;
	multiset<int> s;
	multiset<int>::iterator it;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		s.insert(x);
	}
	s.insert(n);
	for(int i=1;i<=n;i++){
		it=s.lower_bound(n-a[i]);
		if(*it==n){
			cout<<(*s.begin()+a[i])%n<<" ";
			s.erase(s.begin());
		}else{
			cout<<(*it+a[i])%n<<" ";
			s.erase(it);
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	/*cin>>tt;while(tt--)*/solve();
	return 0;
}
```


---

## 作者：Iam1789 (赞：0)

先考虑这么一个性质：

当某个矩形内有蛇头蛇尾之一的时候，矩形上一定会有奇数条边，否则一定有偶数条。

下面给出证明：

当端点不在矩形内时，蛇身进入矩形后一定要出去，因此边数一定是偶数。当只有一个端点在矩形里时，与端点直接相连的蛇身进入矩形后就不再出去，因此边数是奇数。有两个端点在矩形内时，结果是两个奇数相加也是偶数。

于是我们暴力枚举每行每列，根据结果分两种讨论：

1.每行每列各有两个是奇数。蛇头蛇尾被确定在了 $4$ 个点之内，暴力枚举排除即可。操作次数为 $2n+1$。

2.只有一行或者一列有两个数是奇数。蛇头蛇尾在同一列或者一行，并且我们确定了它们的行或列。因此我们选择其中的一行或一列，二分端点的所在的列或行即可。操作次数为 $2n+\log n$。


---

## 作者：世末OIer (赞：0)

这是一道互动题

题目大意:

在一个n*n的矩阵中，有一条链。对于每一次查询，询问左上角为(a,b)，右下角为(c,d)的矩阵能将这条链割开几道。求头和尾的坐标。

题解:

我们知道，这条链是不会断开的——也就是说，只要那一行或一列中没有头或尾，那么他就要被进入x次，出去x次(x为非负整数),也就是说这一行或这一列如果当作一个矩阵来查询的话，得到的一定是2x，一个偶数。这就可以得出答案了。我们可以对于每一行查询(i,1,i,n)，对于每一列查询(1,i,1,n),就可以确定两个头和两个尾的行和列了。最后，对于只在同一行或者同一列的链，特判一下即可。

```cpp
#include<bits/stdc++.h>
#pragma GCC diagnostic error "-std=c++11"
using namespace std;
inline bool query(int aa,int b,int c,int d){
	cout<<"? "<<a<<' '<<b<<" "<<c<<' '<<d<<endl;
	int rt;
	cin>>rt;
	rt&=1;
	return rt; 
} 
vector<int> vx,vy;
inline void answer(int a,int b,int c,int d){
	cout<<"! "<<a<<' '<<b<<' '<<c<<' '<<d<<endl;
	exit(0);
}
int main(){
	ios_base::sync_with_stdio(false);
	int n,i,j;
	cin>>n;
	for(i=1;i<=n;++i){
		if(query(i,1,i,n)) vx.push_back(i);
		if(query(1,i,n,i)) vy.push_back(i);
	}
	if(!vx.size()){
		int l=1,r=n,md;
		while(l<r){
			md=l+r>>1;
			if(query(1,1,md,vy[0])) r=md;
			else l=md+1;
		}
		answer(l,vy[0],l,vy[1]);
		return 0;
	}
	if(!vy.size()){
		int l=1,r=n,md;
		while(l<r){
			md=l+r>>1;
			if(query(1,1,vx[0],md)) r=md;
			else l=md+1;
		}
		answer(vx[0],l,vx[1],l);
		return 0; 
	}
	if(query(vx[0],vy[0],vx[0],vy[0])) answer(vx[0],vy[0],vx[1],vy[1]);
	else answer(vx[0],vy[1],vx[1],vy[0]);
    return 0;
}
```


---

