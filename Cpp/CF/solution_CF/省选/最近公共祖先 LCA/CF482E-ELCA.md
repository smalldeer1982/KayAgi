# ELCA

## 题目描述

有一棵以 $1$ 为根的有根树，第 $i$ 个节点的父亲为 $f_i$，每个节点上有一个数为 $a_i$。

共有 $m$ 个事件：

`P x y` : 若 $x$ 是 $y$ 的祖先，把 $f_y$ 改为 $x$，否则把$ f_x$ 改为 $y$。

`V x v` : 把 $a_x$ 改为 $v$。

求初始和每个事件发生后随机两个点（可以是同一个点）的 LCA 的 $a_i$ 的期望

## 样例 #1

### 输入

```
5
1 2 2 1
1 2 3 4 5
5
P 3 4
P 4 5
V 2 3
P 5 2
P 1 4
```

### 输出

```
1.640000000
1.800000000
2.280000000
2.320000000
2.800000000
1.840000000
```

# 题解

## 作者：ezoiHQM (赞：5)

很显然是LCT，但是很难维护

因为求期望我们只需要在统计出所有情况的$a$的和之后除以$n^2$就好了，所以在LCT中只需要统计所有情况的$a$的和，下面LCT中的答案都表示这个。

LCT的每个节点维护6个值，分别为$siz,sum,ans,all,ad,de$。

$siz[x]$表示$x$的虚子树（以虚边连向的儿子为根的子树）的节点个数+1（这个1表示$x$）

$sum[x]$表示以$x$为根的子树的节点个数

$ans[x]$表示以$x$为根的子树的答案

$all[x]$表示以$x$所在的splay的$siz\times a$的和

$ad[x]$表示$x$的虚子树的答案

$de[x]$表示$x$的虚子树的$sum$的平方的和

对于每次更新节点$x$，我们有：
$$sum[x]=siz[x]+sum[ch[x][0]]+sum[ch[x][1]]$$
$$all[x]=all[ch[x][0]]+all[ch[x][1]]+a[x]\times siz[x]$$
$$ans[x]=ans[ch[x][0]]+ans[ch[x][1]]+ad[x]$$
$$+a[x]\times(siz[x]\times siz[x]-de[x])$$
$$+2\times a[x]\times siz[x]\times sum[ch[x][1]]$$
$$+2\times all[ch[x][0]]\times(sum[x]-sum[ch[x][0]])$$
$sum$和$all$的应该很好理解了，对于$ans$，我们可以分为四部分来理解
第一部分：$ans[ch[x][0]]+ans[ch[x][1]]+ad[x]$
就是把子树的答案统计下来
第二部分：$a[x]\times(siz[x]\times siz[x]-de[x])$
表示各个虚子树中$lca$为$x$的节点对的
第三部分：$2\times a[x]\times siz[x]\times sum[ch[x][1]]$
表示虚子树和$x$的右儿子的答案
第四部分：$2\times all[ch[x][0]]\times(sum[x]-sum[ch[x][0]])$
表示$x$的左儿子和以$x$为根的子树的剩余部分的答案。因为$x$的左儿子是$x$的祖先所以我们应该将剩余部分的节点个数乘$all[ch[x][0]]$而不是$a[x]\times sum[ch[x][0]]$

维护剩下的$siz,ad,de$，由于是存储虚子树的信息，所以我们只需要在$link,cut,access$的时候更新一下就好了，这部分比较简单，具体看代码实现。
由于这道题显然不用$makeroot$，所以我们可以不需要$pushdown$和反转操作，然后在普通的LCT中稍微修改一下$link$和$cut$就好了，具体看代码实现。
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=100010;
int n,m,tot,pre[N],a[N],siz[N],sum[N],f[N],ch[N][2];
ll ans[N],all[N],ad[N],de[N];
long double Ans;
bool isroot(int x){
	return ch[f[x]][0]!=x&&ch[f[x]][1]!=x;
}
int which(int x){
	return ch[f[x]][1]==x;
}
void push_up(int x){
	sum[x]=siz[x]+sum[ch[x][0]]+sum[ch[x][1]];
	all[x]=all[ch[x][0]]+all[ch[x][1]]+1ll*a[x]*siz[x];
	ans[x]=ans[ch[x][0]]+ans[ch[x][1]]+ad[x]+a[x]*(1ll*siz[x]*siz[x]-de[x])+2ll*a[x]*siz[x]*sum[ch[x][1]]+2ll*all[ch[x][0]]*(sum[x]-sum[ch[x][0]]);
	return;
}
void rotate(int x){
	int fa=f[x],ffa=f[fa],d=which(x);
	if(!isroot(fa))
		ch[ffa][which(fa)]=x;
	f[x]=ffa;
	ch[fa][d]=ch[x][d^1];
	f[ch[x][d^1]]=fa;
	ch[x][d^1]=fa;
	f[fa]=x;
	push_up(fa);
	push_up(x);
	return;
}
void splay(int x){
	for(int fa;!isroot(x);rotate(x))
		if(!isroot(fa=f[x]))
			rotate(which(x)==which(fa)?fa:x);
	return;
}
void access(int x){
	for(int y=0;x;y=x,x=f[x]){
		splay(x);
		siz[x]+=sum[ch[x][1]];
		de[x]+=1ll*sum[ch[x][1]]*sum[ch[x][1]];
		ad[x]+=ans[ch[x][1]];
		ch[x][1]=y;
		siz[x]-=sum[y];
		de[x]-=1ll*sum[y]*sum[y];
		ad[x]-=ans[y];
		push_up(x);
	}
	return;
}
void link(int x,int y){
	access(y);
	splay(y);
	access(x);
	splay(x);
	f[y]=x;
	siz[x]+=sum[y];
	ad[x]+=ans[y];
	de[x]+=1ll*sum[y]*sum[y];
	push_up(x);
	return;
}
void cut(int x,int y){
	access(x);
	splay(x);
	splay(y);
	siz[x]-=sum[y];
	ad[x]-=ans[y];
	de[x]-=1ll*sum[y]*sum[y];
	f[y]=0;
	push_up(x);
	return;
}
bool check(int x,int y){
	access(y);
	splay(y);
	splay(x);
	return !isroot(y);
}
int main(){
	scanf("%d",&n);
	for(int i=2;i<=n;i++)
		scanf("%d",pre+i);
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
		ans[i]=all[i]=a[i];
		siz[i]=sum[i]=1;
	}
	for(int i=2;i<=n;i++)
		link(pre[i],i);
	access(1);
	splay(1);
	Ans=ans[1];
	printf("%.10Lf\n",Ans/n/n);
	scanf("%d",&m);
	while(m--){
	    char op[2];
		int x,y;
		scanf("%s%d%d",op,&x,&y);
		if(op[0]=='P'){
			if(pre[y]==x||pre[x]==y)
				goto to;
			if(check(x,y))
				swap(x,y);
			cut(pre[x],x);
			pre[x]=y;
			link(y,x);
			access(1);
			splay(1);
			Ans=ans[1];
		}
		else{
			access(x);
			splay(x);
			a[x]=y;
			push_up(x);
			Ans=ans[x];
		}
		to:
		printf("%.10Lf\n",Ans/n/n);
	}
	return 0;
}
```

---

