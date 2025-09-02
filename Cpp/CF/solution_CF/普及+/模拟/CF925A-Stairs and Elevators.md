# Stairs and Elevators

## 题目描述

在 $30XX$ 年，某世界编程锦标赛的参赛选手们齐聚在一座巨大的酒店。酒店共有 $n$ 层楼，每层楼有 $m$ 个区域，它们通过一条走廊相连。每层的区域从 $1$ 到 $m$ 进行编号，且在不同楼层中编号相同的区域位于正上方。因此，整栋酒店可以看作是一个高为 $n$ 且宽为 $m$ 的矩形结构。我们用整数对 $(i, j)$ 来表示各个区域，其中 $i$ 是楼层编号，$j$ 是该楼层的区域编号。

客人可以在每层楼的走廊上行走，也能通过楼梯和电梯到达其他楼层。每部楼梯或电梯占据了从 $(1, x)$ 到 $(n, x)$ 的所有区域，这里 $x$ 介于 $1$ 和 $m$ 之间。所有未被楼梯或电梯占用的区域是客房。

在同一楼层内相邻区域间的移动需要花费一个时间单位，使用楼梯上下楼层同样需要一个时间单位。使用电梯可以在任意方向上最多跨越 $v$ 层楼，但也只需一个时间单位。而且，你无需等待电梯，进入和退出电梯所需的时间可以忽略不计。

你需要处理 $q$ 个查询。每个查询的问题是：“从 $(x_1, y_1)$ 区域的某个房间到 $(x_2, y_2)$ 区域的某个房间，所需的最短时间是多少？”

## 样例 #1

### 输入

```
5 6 1 1 3
2
5
3
1 1 5 6
1 3 5 4
3 3 5 3
```

### 输出

```
7
5
4
```

# 题解

## 作者：gesong (赞：1)

题目传送门：[CF925A](https://www.luogu.com.cn/problem/CF925A)。
# 思路

一道贪心好题。

首先我们发现如果 $x_1=x_2$ 那么我们根本不用乘坐电梯和扶梯，直接走到即可，答案为 $\lvert y_2-y_1\rvert$。

否则我们就可以贪心的想：我们不会先坐一部电梯，然后又换另一部，因为 $\lceil \frac{a+b}{v}\rceil \le \lceil \frac{a}{v} \rceil + \lceil \frac{b}{v} \rceil$，同理我们也不会先走楼梯然后又换一个楼梯走，我们更不可能会先坐电梯再走楼梯，因为走楼梯的过程换成电梯明显更优。

这时候我们将题目转化为求走一条楼梯和坐一部电梯的方案的最小值的最小值，我们再次贪心，我们肯定会选择离起点最近的楼梯和电梯进行乘坐，因此我们可以使用二分查找来找到最近的电梯和扶梯。

到这里，这道题就基本做完了，但还要考虑一些特殊情况，比如没有电梯或扶梯，具体的可以参考代码。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int a[N],b[N];
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
inline int ceil(int a,int b){
	return (a+b-1)/b;
}
main(){
	read(),read();
	int n=read(),m=read(),v=read();
	for (int i=1;i<=n;i++) a[i]=read();
	for (int i=1;i<=m;i++) b[i]=read();
	int T=read();
	while(T--){
		int x1=read(),y1=read(),x2=read(),y2=read();
		if (x1==x2){
			cout <<abs(y1-y2)<<endl;
			continue;
		}
		int ans=1e18;
		if (n){
			int l=lower_bound(a+1,a+n+1,y1)-a-1;
			int r=lower_bound(a+1,a+n+1,y1)-a;
			if (l) ans=min(ans,abs(y2-a[l])+abs(y1-a[l])+abs(x2-x1));
			if (r<=n) ans=min(ans,abs(y2-a[r])+abs(y1-a[r])+abs(x2-x1));
		}
		if (m){
			int l=lower_bound(b+1,b+m+1,y1)-b-1;
			int r=lower_bound(b+1,b+m+1,y1)-b;
			if (l) ans=min(ans,abs(y2-b[l])+abs(y1-b[l])+ceil(abs(x2-x1),v));
			if (r<=m) ans=min(ans,abs(y2-b[r])+abs(y1-b[r])+ceil(abs(x2-x1),v));
		}
		printf("%lld\n",ans);
	}
    return 0;
}


```

---

## 作者：S00021 (赞：1)

### 题号：CF967C/CF925A

### 题目大意：
有一幢大楼可以视为 $n \times m$ 的矩形，在 $ce$ 列上有电梯连通 $1-n$ 行，使得任意两行两两可达，这些列为 $e[1...n]$ ；在 $cl$ 列上有楼梯连通 $1-n$ 行使任意两行两两可达，这些列为 $l[1...n]$，走一层楼楼梯花费 $1$ 的时间，乘坐 $v$ 层楼电梯花费 $1$ 的时间，现在有 $Q$ 组询问，每组询问问 $(x_a,y_a)$ 到 $(x_b,y_b)$ 需要花费多少时间。
$2\le n,m\le 10^8$ , $1\le cl+ce \le n-1$ ,$1\le v\le n-1 $,$0\le cl,ce\le 10^5,Q\le 10^5$


### 算法：

简单题。

这道题首先需要分析的是楼梯和电梯两个操作分别具有什么功能。

首先，感性理解可以发现我能坐电梯一定不会走楼梯。

但是这里还有一些情况，比如像如果坐电梯需要在起点和终点的两层楼上同层绕很远的路，反而没有走楼梯来的直接；或者是两层楼之间没有电梯等等。这样怎么办呢？最暴力也是最靠谱的想法是将楼梯与电梯的最优情况都处理出来然后取 $\min$，那会不会漏掉走一部分楼梯再坐一部分电梯这种情况呢？答案是不会，因为这样走楼梯的部分也可以替换为坐电梯，答案不劣。

接下来就非常好了，直接二分出第一个 $<y_a$ 和 $>y_b$ 的楼梯/电梯计算答案并判断有没有楼梯/电梯在 $y_a$ 与 $y_b$ 中间更新答案，这里有个非常容易忽略的地方就是当 $x_a=x_b$ 时我们需要特判，不然诸如 $(y_a-l_i)+(y_b-l_i)$ 这种语句会将答案算重，这就是赛时那么多人 fst 的原因。

代码：
```cpp        #include<bits/stdc++.h>
    #define MAXN 1000000
    #define int long long
    using namespace std;
    int n,m,Q,cl,ce,v,l[MAXN+5],e[MAXN+5];
    signed main(){
    	scanf("%lld%lld%lld%lld%lld",&n,&m,&cl,&ce,&v);
    	for(int i=1;i<=cl;i++) scanf("%lld",&l[i]);
    	for(int i=1;i<=ce;i++) scanf("%lld",&e[i]);
    	scanf("%lld",&Q);
    	while(Q--){
    		int x1,x2,y1,y2,ret=1e13;
    		scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
    		if(x1==x2){printf("%lld\n",abs(y1-y2)); continue;}
    		if(y1>y2) swap(x1,x2),swap(y1,y2);
    		int u1=lower_bound(l+1,l+cl+1,y1)-l-1;
    		int u2=upper_bound(l+1,l+cl+1,y2)-l;
    		if(u1+1<u2) ret=min(ret,abs(x1-x2)+abs(y1-y2));
    		if(u1) ret=min(ret,(y1-l[u1])+(y2-l[u1])+abs(x2-x1));
    		if(u2<=cl) ret=min(ret,(l[u2]-y1)+(l[u2]-y2)+abs(x2-x1));
    		u1=lower_bound(e+1,e+ce+1,y1)-e-1;
    		u2=upper_bound(e+1,e+ce+1,y2)-e;
    		if(u1+1<u2) ret=min(ret,(abs(x1-x2)+v-1)/v+(abs(y1-y2)));
    		if(u1) ret=min(ret,(y1-e[u1])+(y2-e[u1])+(abs(x2-x1)+v-1)/v);
    		if(u2<=ce) ret=min(ret,(e[u2]-y1)+e[u2]-y2+(abs(x2-x1)+v-1)/v);
    		printf("%lld\n",ret);
    	}
    	return 0;
    }


```


---

