# [ARC047D] ナナメクエリ

## 题目描述

有一个 $N \times N$ 的方格纸。

我们将方格纸的最左上角定义为格子 $(0, 0)$，最右下角为格子 $(N-1, N-1)$。对任意格子 $(X, Y)$，其表示从最左上角格子向下移动 $X$ 格，向右移动 $Y$ 格所到达的位置。

初始时，所有格子的值均为 $0$。

现在，需要对这张方格纸进行 $Q$ 次操作。操作类型共有三种，描述如下：

1. `1 A B C`：对所有满足 $A \leq X+Y \leq B$ 的格子 $(X, Y)$，将其值增加 $C$。保证 $0 \leq A \leq B \leq 2N-2$ 且 $-10^5 \leq C \leq 10^5$。
2. `2 A B C`：对所有满足 $A \leq X-Y \leq B$ 的格子 $(X, Y)$，将其值增加 $C$。保证 $1-N \leq A \leq B \leq N-1$ 且 $-10^5 \leq C \leq 10^5$。
3. `3 A B C D`：在所有满足 $A \leq X \leq B$ 且 $C \leq Y \leq D$ 的格子中，找出最大值 $M$，并计算这些格子中写有 $M$ 的个数。保证 $0 \leq A \leq B \leq N-1$ 且 $0 \leq C \leq D \leq N-1$。

你的任务是编写程序，依次处理这些查询操作。

## 说明/提示

### 部分得分

本题有设置部分得分：

- 如果正确解答 $1 \leq N \leq 50$ 的数据集，可以获得 $10$ 分。
- 如果正确解答 $1 \leq N \leq 500$ 的数据集，可以额外获得 $20$ 分，总分达到 $30$ 分。
- 如果正确解答 $1 \leq N \leq 5000$ 的数据集，可以再获得 $70$ 分，总分 $100$ 分。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4 4
1 1 4 2
3 0 1 2 3
2 -2 1 3
3 0 3 1 3```

### 输出

```
2 4
5 7```

## 样例 #2

### 输入

```
50 20
2 5 40 6
1 69 94 5
3 8 39 31 32
2 -29 -21 -10
2 20 43 3
2 -37 36 -10
2 -18 45 5
2 30 39 -2
3 0 1 19 33
3 27 47 0 43
3 0 1 28 39
1 90 97 0
2 -46 31 7
1 81 81 4
1 11 54 3
3 10 29 26 30
1 39 45 3
1 70 97 -4
3 24 46 14 34
3 1 18 48 48```

### 输出

```
11 5
-5 1
14 8
0 3
5 82
16 2
10 5```

# 题解

## 作者：shinkuu (赞：3)

首杀问号题，虽然没有问号题的难度，但是至少是自己想出来的。

对于操作一和二，我们直接用分一个数组记录下来，$O(nq)$。

对于操作三，我们思考怎么样通过上面记录的信息处理答案。发现对于一个矩形，只要确定了 $x+y$ 的值，$x-y$ 的值就是一个区间，因为矩形的约束可以变成 $2\times A\le(x+y)+(x-y)\le 2\times B,2\times C\le(x+y)-(x-y)\le 2\times D$。这启示我们可以类似莫队，维护两个指针。

但是删除操作是比较难做的。我们先考虑不用删除的情况是什么，发现在矩形左上，右下角割出一个等腰直角三角形，这是可以直接做的，因为只会有加入。

然后考虑剩下的部分，发现这是一个平行四边形。放入刚才的思路中，这就变成了一个滑动窗口，直接单调队列维护即可。时间复杂度 $O(nq)$。

细节还是不少的。首先要分成奇偶来讨论，其次单调队列部分要根据矩形形状决定加/删的是左端点还是右端点。处理答案可以像我一样，手写一个记录最大值和出现次数的 struct。

写得有点冗长，但是很多都是可以复制粘贴的，也不算很恶心，主要是样例强度足够。

code：

```cpp
int n,m,a[N],b[N];
struct node{
	int x,y;
	node(int _x=-inf,int _y=0){x=_x,y=_y;}
	node operator+(const node &tmp)const{
		node r=node(x,y);
		if(tmp.x>r.x)r.x=tmp.x,r.y=tmp.y;
		else if(tmp.x==r.x)r.y+=tmp.y;
		return r;
	}
};
struct Node{node x;int y;};
void Yorushika(){
	scanf("%d%d",&n,&m);
	if(n&1)n++;
	rep(i,1,m){
		int op,x,y,k;
		scanf("%d%d%d",&op,&x,&y);
		if(op==1){
			scanf("%d",&k);
			rep(j,x,y)a[j]+=k;
		}else if(op==2){
			scanf("%d",&k);
			rep(j,x,y)b[j+n]+=k;
		}else{
			int X,Y;scanf("%d%d",&X,&Y);
			x*=2,y*=2,X*=2,Y*=2;
			int l[2]={-1,-1},r[2]={0,0},pl=n*2,pr=0;
			node mx[2],ans;
			rep(i,0,n*2){
				int la=x-i,ra=y-i,lb=i-Y,rb=i-X,p=i&1;
				int L=max(la,lb)+n,R=min(ra,rb)+n;
				if(L>R)continue;
				if(l[p]<0)for(int j=l[p]=L;j<=(r[p]=R);j+=2)mx[p]=mx[p]+node(b[j],1);
				if(L>l[p]||R<r[p])break;
				while(r[p]<R)r[p]+=2,mx[p]=mx[p]+node(b[r[p]],1);
				while(l[p]>L)l[p]-=2,mx[p]=mx[p]+node(b[l[p]],1);
				node tmp=mx[p];tmp.x+=a[i];
				ans=ans+tmp,pl=i;
			}
			l[0]=l[1]=-1,r[0]=r[1]=0,mx[0]=mx[1]=node();
			drep(i,n*2,pl+1){
				int la=x-i,ra=y-i,lb=i-Y,rb=i-X,p=i&1;
				int L=max(la,lb)+n,R=min(ra,rb)+n;
				if(L>R)continue;
				if(l[p]<0)for(int j=l[p]=L;j<=(r[p]=R);j+=2)mx[p]=mx[p]+node(b[j],1);
				if(L>l[p]||R<r[p])break;
				while(r[p]<R)r[p]+=2,mx[p]=mx[p]+node(b[r[p]],1);
				while(l[p]>L)l[p]-=2,mx[p]=mx[p]+node(b[l[p]],1);
				node tmp=mx[i&1];tmp.x+=a[i];
				ans=ans+tmp,pr=i;
			}
			l[0]=l[1]=-1,r[0]=r[1]=0,mx[0]=mx[1]=node();
			deque<node> q[2];
			if(X-Y<=x-y){
				rep(i,pl+1,pr-1){
					int la=x-i,ra=y-i,lb=i-Y,rb=i-X,p=i&1;
					int L=max(la,lb)+n,R=min(ra,rb)+n;
					if(L>R)continue;
					if(l[p]<0)for(int j=r[p]=R;j>=(l[p]=L);j-=2){
						while(q[p].size()&&q[p].back().x<b[j])q[p].pop_back();
						if(q[p].size()&&q[p].back().x==b[j]){
							node tmp=q[p].back();
							q[p].pop_back();
							tmp.y++;
							q[p].push_back(tmp);
						}else q[p].push_back(node(b[j],1));
					}else{
						if(q[p].front().x==b[r[p]]){
							node tmp=q[p].front();
							q[p].pop_front();
							tmp.y--;
							if(tmp.y)q[p].push_front(tmp);
						}
						l[p]-=2,r[p]-=2;
						while(q[p].size()&&q[p].back().x<b[l[p]])q[p].pop_back();
						if(q[p].size()&&q[p].back().x==b[l[p]]){
							node tmp=q[p].back();
							q[p].pop_back();
							tmp.y++;
							q[p].push_back(tmp);
						}else q[p].push_back(node(b[l[p]],1));
					}
					node tmp=q[p].front();tmp.x+=a[i];
					ans=ans+tmp;
				}
			}else{
				rep(i,pl+1,pr-1){
					int la=x-i,ra=y-i,lb=i-Y,rb=i-X,p=i&1;
					int L=max(la,lb)+n,R=min(ra,rb)+n;
					if(L>R)continue;
					if(l[p]<0)for(int j=l[p]=L;j<=(r[p]=R);j+=2){
						while(q[p].size()&&q[p].back().x<b[j])q[p].pop_back();
						if(q[p].size()&&q[p].back().x==b[j]){
							node tmp=q[p].back();
							q[p].pop_back();
							tmp.y++;
							q[p].push_back(tmp);
						}else q[p].push_back(node(b[j],1));
					}else{
						if(q[p].front().x==b[l[p]]){
							node tmp=q[p].front();
							q[p].pop_front();
							tmp.y--;
							if(tmp.y)q[p].push_front(tmp);
						}
						l[p]+=2,r[p]+=2;
						while(q[p].size()&&q[p].back().x<b[r[p]])q[p].pop_back();
						if(q[p].size()&&q[p].back().x==b[r[p]]){
							node tmp=q[p].back();
							q[p].pop_back();
							tmp.y++;
							q[p].push_back(tmp);
						}else q[p].push_back(node(b[r[p]],1));
					}
					node tmp=q[p].front();tmp.x+=a[i];
					ans=ans+tmp;
				}
			}
			printf("%d %d\n",ans.x,ans.y);
		}
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：RedLycoris (赞：2)

[link](https://www.luogu.com.cn/problem/AT_arc047_d)

题目大意：

有一个 $n\times n$（$1\le n \le 5000$）的正方形矩阵，初始全部为 $0$，下标从 $0$ 开始。

有 $q$（$1 \le q \le 5000$）次操作：

+ $1$ $a$ $b$ $c$ 将所有满足 $a \le x+y \le b$ 的点 $(x,y)$ 的值加上 $c$。

+ $2$ $a$ $b$ $c$ 将所有满足 $a \le x-y \le b$ 的点 $(x,y)$ 的值加上 $c$。

+ $3$ $a$ $b$ $c$ $d$ 查询所有满足 $a \le x \le b$， $c \le y \le d$ 的点 $(x,y)$ 的最大值，并求出值为最大值的点的个数。

部分分：$1 \le n \le 500$

题解：

我们考虑维护两个数组 $s1,s2$，其中 $s1_i$ 表示所有满足 $x+y=i$ 的点加的和，$s2_i$ 表示所有满足 $x-y=i$ 的点加的和。

对于一个点 $(x,y)$，他的值就是 $s1_{x+y}+s2_{x-y}$，所以我们维护 $s1,s2$ 就可以知道全矩阵的值了，$1$ 和 $2$ 操作的复杂度都为 $O(nq)$。

关键在于这个询问。

我们可以枚举所有可能的 $sum$（就是 $x+y$ 的值），那么可以发现，那些在 $sum$ 已知的条件下可行的 $x-y$ 就是连续的一些奇数或者偶数。用数据结构维护可以做到 $O(qn\log n)$，得到部分分。

再继续考虑。

考虑特殊化，查询的是一个正方形。

如果我们从小到大枚举所有的 $sum$，且枚举的时候让 $step=2$（就是按照 $sum$，$sum+2$，$sum+4 \dots$ 的顺序枚举），可以发现每次只会新增两个可能的 $x-y$，不会变少，所以我们只要暴力用新增的两个 $x-y$ 更新就行了。

同理，我们再按照 $sum+1$，$sum+3\dots$ 的顺序枚举，两种情况合并后就是答案了。

再考虑把查询一般化为长方形，则可以按照类似辗转相减法的方法每次割出最大的正方形去查询，然后合并所有的答案，可以证明单次询问复杂度为 $O(n)$，故总时间复杂度为 $O(nq)$。

---

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mxn=1e4+9;
const int base=5003;
int n,q,s1[mxn],s2[mxn];
inline pair<int,int> G(pair<int,int> x,pair<int,int> y){
	if(x.first!=y.first){
		if(x.first>y.first)return x;
		else return y;
	}
	x.second+=y.second;
	return x;
}
inline pair<int,int> go(int a,int b,int c,int d){
	int cur,cnt,len;
	pair<int,int>rt={-1145141919,0};
	cur=-1145141919,cnt=0,len=-2;
	for(int sum1=a+b,sum2=c+d;sum1<=a+d;sum1+=2,sum2-=2){ //第一类
		len+=2;
		if(s2[a-b+base-len]>cur)cur=s2[a-b+base-len],cnt=1;
		else if(s2[a-b+base-len]==cur)++cnt;
		if(len!=0){
			if(s2[a-b+base+len]>cur)cur=s2[a-b+base+len],cnt=1;
			else if(s2[a-b+base+len]==cur)++cnt;			
		}
		if(s1[sum1]+cur>rt.first){
			rt.first=s1[sum1]+cur;
			rt.second=cnt;
		}else if(s1[sum1]+cur==rt.first){
			rt.second+=cnt;
		}
		if(sum1!=sum2){
			if(s1[sum2]+cur>rt.first){
				rt.first=s1[sum2]+cur;
				rt.second=cnt;
			}else if(s1[sum2]+cur==rt.first){
				rt.second+=cnt;
			}			
		}
	}
	len=-1,cnt=0,cur=-1145141919;
	for(int sum1=a+b+1,sum2=c+d-1;sum1<=a+d;sum1+=2,sum2-=2){ //第二类
		len+=2;
		if(s2[a-b+base-len]>cur)cur=s2[a-b+base-len],cnt=1;
		else if(s2[a-b+base-len]==cur)++cnt;
		if(len!=0){
			if(s2[a-b+base+len]>cur)cur=s2[a-b+base+len],cnt=1;
			else if(s2[a-b+base+len]==cur)++cnt;			
		}
		if(s1[sum1]+cur>rt.first){
			rt.first=s1[sum1]+cur;
			rt.second=cnt;
		}else if(s1[sum1]+cur==rt.first){
			rt.second+=cnt;
		}
		if(sum1!=sum2){
			if(s1[sum2]+cur>rt.first){
				rt.first=s1[sum2]+cur;
				rt.second=cnt;
			}else if(s1[sum2]+cur==rt.first){
				rt.second+=cnt;
			}			
		}
	}
	return rt;
}
inline auto solve(int a,int b,int c,int d){//割成极大正方形
	if(c-a==d-b)return go(a,b,c,d);
	int l=min(c-a,d-b);
	if(c-a>d-b){
		pair<int,int> rt=go(a,b,a+l,b+l);
		rt=G(rt,solve(a+l+1,b,c,d));
		return rt;
	}else{
		pair<int,int> rt=go(a,b,a+l,b+l);
		rt=G(rt,solve(a,b+l+1,c,d));
		return rt;
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(;q--;){
		int tp,a,b,c,d;
		cin>>tp;
		if(tp==1){
			cin>>a>>b>>c;
			for(int i=a;i<=b;++i)s1[i]+=c;
		}
		if(tp==2){
			cin>>a>>b>>c;
			a+=base,b+=base;
			for(int i=a;i<=b;++i)s2[i]+=c;
		}
		if(tp==3){
			cin>>a>>b>>c>>d;
			auto p=solve(a,c,b,d);
			cout<<p.first<<' '<<p.second<<'\n';
		}
	}
}
```

---

