# Zebra Tower

## 题目描述

Little Janet likes playing with cubes. Actually, she likes to play with anything whatsoever, cubes or tesseracts, as long as they are multicolored. Each cube is described by two parameters — color $ c_{i} $ and size $ s_{i} $ . A Zebra Tower is a tower that consists of cubes of exactly two colors. Besides, the colors of the cubes in the tower must alternate (colors of adjacent cubes must differ). The Zebra Tower should have at least two cubes. There are no other limitations. The figure below shows an example of a Zebra Tower.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF159E/f33171cfff84c23150eb82e578a37293690a12de.png)A Zebra Tower's height is the sum of sizes of all cubes that form the tower. Help little Janet build the Zebra Tower of the maximum possible height, using the available cubes.

## 样例 #1

### 输入

```
4
1 2
1 3
2 4
3 3
```

### 输出

```
9
3
2 3 1 
```

## 样例 #2

### 输入

```
2
1 1
2 1
```

### 输出

```
2
2
2 1 
```

# 题解

## 作者：7KByte (赞：0)

给定 $N$ 个物品，每个物品有一个颜色 $c_i$ 和大小 $s_i$ ，你需要找出一些物品排成一排，使得只有两种颜色且两种颜色交替排列，要最大化选出物品的$\sum s_i$ 。

考虑枚举一个颜色，然后找到能和它匹配的最优颜色。

我们将相同颜色的物品排在一起，包含物品多的颜色排在前面，相同的颜色中$s_i$大的物品排在前面。

然后依次考虑每种颜色。

由于前面的颜色数量一定不小于当前颜色数量，所以当前颜色的物品一定可以全选。

我们再记录一下 $a_i$ 表示选择 $i$ 个相同颜色的物品能获得的最大价值即可。

排序函数中用了$\rm map$，时间复杂度$\rm O(N\log^2 N)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 100005
#define int long long 
using namespace std;
map<int,int>h,ll,rr;
struct node{
	int c,s,op;
	bool operator<(const node o)const{
		if(c!=o.c){
			if(h[c]!=h[o.c])return h[c]>h[o.c];
			return c<o.c;
		}
		return s>o.s;
	}
}u[N];
int n,mx,p,q;
pair<int,int>c[N];
void calc(int l,int r){
	int sum=0;
	rep(i,l,r){
		sum+=u[i].s;
		if(c[i-l+1].second&&sum+c[i-l+1].first>mx)mx=sum+c[i-l+1].first,p=u[i].c,q=c[i-l+1].second;
		if(c[i-l+2].second&&sum+c[i-l+2].first>mx)mx=sum+c[i-l+2].first,p=u[i].c,q=c[i-l+2].second;
		if(sum>c[i-l+1].first)c[i-l+1].first=sum,c[i-l+1].second=u[i].c;
	}
}
void solve(){
	if(rr[p]-ll[p]==rr[q]-ll[q]){
		int ans=0;
		rep(i,ll[p],rr[p])ans+=u[i].s+u[ll[q]+i-ll[p]].s;
		printf("%lld\n",ans);
		printf("%lld\n",(rr[p]-ll[p]+1)*2);
		rep(i,ll[p],rr[p])printf("%lld %lld ",u[i].op,u[ll[q]+i-ll[p]].op);
	}
	else{
		int ans=0;
		rep(i,ll[p],rr[p])ans+=u[i].s+u[ll[q]+i-ll[p]].s;
		ans+=u[ll[q]+rr[p]-ll[p]+1].s;
		printf("%lld\n",ans);
		printf("%lld\n",(rr[p]-ll[p]+1)*2+1);
		rep(i,ll[p],rr[p])printf("%lld %lld ",u[ll[q]+i-ll[p]].op,u[i].op);
		printf("%lld\n",u[ll[q]+rr[p]-ll[p]+1].op);
	}
}
signed main(){
	scanf("%lld",&n);
	rep(i,1,n)scanf("%lld%lld",&u[i].c,&u[i].s),h[u[i].c]++,u[i].op=i;
	sort(u+1,u+n+1);
	int pre=1;
	rep(i,2,n){
		if(u[i].c!=u[i-1].c)ll[u[i-1].c]=pre,rr[u[i-1].c]=i-1,calc(pre,i-1),pre=i;
	}
	ll[u[n].c]=pre;rr[u[n].c]=n;calc(pre,n);
	//rep(i,1,n)printf("ss  %lld %lld  %lld %lld\n",u[i].c,u[i].s,ll[u[i].c],rr[u[i].c]);
	//cout<<p<<" "<<q<<endl;
	solve();
	return 0;
}
```

---

