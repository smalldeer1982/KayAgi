# [USACO21DEC] Bracelet Crossings G

## 题目描述

奶牛 Bessie 喜欢手工艺。在她的空闲时间，她制作了 $N$（$1\le N\le 50$）个手链，编号为 $1 \ldots N$。第 $i$ 个手链涂有颜色 $i$，是 $N$ 种不同的颜色之一。制作完手链后，Bessie 将它们放在桌子上进行展示（我们可以将其视为二维平面）。她精心布置这些手链，以满足以下三个条件：

- 每个手链是一个简单闭合折线——一组顶点（点）依次用线段连接，并且第一个点和最后一个点相同（欢迎查阅维基百科页面了解更多详情：[Polygonal_chain](https://en.wikipedia.org/wiki/Polygonal_chain)，或百度百科：[折线](https://baike.baidu.com/item/%E6%8A%98%E7%BA%BF/486302)），

- 没有手链与自身相交（这对应「简单」折线）；

- 以及没有两条手链相交。

不幸的是，就在 Bessie 如此小心翼翼地布置好手链之后，Farmer John 开着拖拉机经过，桌子晃动起来，导致手链四处移动甚至可能断成了多个（不一定是闭合的或简单的）折线！在那之后，Bessie 还是想检查以上三个条件是否仍然成立。然而，天色已暗，她现在无法看清手链。

幸好 Bessie 有一个手电筒。她选择了 $M$（$1\le M\le 50$）条垂直线 $x=1, x=2, \ldots, x=M$，并且对于每条线，她用手电筒的光沿着那条线从 $y=-\infty$ 扫至 $y=\infty$，按照出现的顺序记录她看到的所有手链的颜色。幸运的是，没有光束穿过任何折线的顶点或同时穿过两条线段。此外，对于每一束光，所有出现的颜色都恰好出现了两次。

你能帮助 Bessie 使用此信息来确定手链是否仍然满足上述所有三个条件吗？

## 说明/提示

【样例解释】

对于第一个子测试用例，一组可行的手链位置为：

![](https://cdn.luogu.com.cn/upload/image_hosting/q3mohld2.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

对于第四个子测试用例，一组可行的手链位置为：

![](https://cdn.luogu.com.cn/upload/image_hosting/8m2hcgbb.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

【数据范围】

- 测试点 2 满足 $N = 1$。
- 测试点 3-5 满足 $N=2$。
- 测试点 6-8 满足 $M=1$。
- 测试点 9-14 满足 $M=2$。
- 测试点 15-20 没有额外限制。

## 样例 #1

### 输入

```
5

1 2
2 1 1
2 1 1

1 3
2 1 1
0
2 1 1

2 1
4 1 2 1 2

4 2
6 1 2 2 3 3 1
6 1 2 4 4 2 1

2 2
4 1 1 2 2
4 2 2 1 1```

### 输出

```
YES
NO
NO
YES
NO```

# 题解

## 作者：Eibon (赞：4)

首先，每个手链必须为连续的。

接下来，我们需要判断两条手链之间是否会相交。

正难则反，由于直接求相交并不好求，所以考虑求出包含和相离的情况。

设 $c1_{i,x}$ 与 $c2_{i,x}$ 表示在第 $i$ 行颜色 $x$ 出现的上端与下端，如果 $c1_{i,x}$ 为 $0$ 则表示该颜色手链在第 $i$ 行为出现。

设 $l_{x}$ 与 $r_{x}$ 表示 $x$ 颜色出现的最左一行与最右一行。

具体步骤请结合代码食用 TWT。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=100+5;
const int inf=1e18;
int T=1,n,m;
int l[maxn],r[maxn],c1[maxn][maxn],c2[maxn][maxn];
bool in(int i,int j)
{
	if(!(l[i]<=l[j]&&r[j]<=r[i])){
		return 0;
	}
	for(int x=l[j];x<=r[j];x++){
		if(!(c1[x][i]<c1[x][j]&&c2[x][j]<c2[x][i])){
			return 0;
		}
	}
	return 1;
}
bool ud(int i,int j)
{
	for(int x=1;x<=m;x++){
		int xi=c2[x][i],xj=c1[x][j];
		if(xi&&xj&&xi>xj){
			return 0;
		}
	}
	return 1;
}
bool VIP()
{
	for(int i=1;i<=n;i++){
		if(!l[i]){
			continue;
		}
		for(int j=l[i];j<=r[i];j++){
			if(!c1[j][i]){
				return 0;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			if(!in(i,j)&&!in(j,i)&&!ud(i,j)&&!ud(j,i)){
				return 0;
			}
		}
	}
	return 1;
}
void solve()
{
	scanf("%lld%lld",&n,&m);
	memset(l,0,sizeof l);memset(r,0,sizeof r);
	memset(c1,0,sizeof c1);memset(c2,0,sizeof c2);
	for(int i=1;i<=m;i++){
		int k;
		scanf("%lld",&k);
		for(int j=1;j<=k;j++){
			int x;
			scanf("%lld",&x);
			if(!c1[i][x]){
				c1[i][x]=j;
			}
			else{
				c2[i][x]=j;
			}
			if(!l[x]){
				l[x]=i;
			}
			else{
				r[x]=i;
			}
		}
	}
	if(VIP()){
		puts("YES");
	}
	else{
		puts("NO");
	}
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	scanf("%lld",&T);
	while(T--){
		solve();
	}
	return 0;
}
//dyyyyds
```

---

## 作者：cmll02 (赞：2)

如果每个颜色出现的线段不连续，显然是 NO。

否则我们对两个颜色进行判断，有两种情况：

1. 多边形存在包含关系

$a$ 包含 $b$ 条件是 $a$ 出现的线段区间包含 $b$ 出现的线段区间，且在每条 $b$ 出现的线段上 $a$ 都在 $b$ 外侧。

2. 不存在包含关系

要求每一 $a,b$ 同时出现的线段上 $a$ 都在 $b$ 的左侧或者都在右侧。

两两判断即可。


---

## 作者：XL4453 (赞：2)

### 解题思路：

思路很简单，就是进行一些不可能的情况的判断，但是想不全。

1. 链子断掉了。记录下某根链子最早出现的位置和最后出现的位置，如果链子没有断掉，在这些位置之间一定全都会出现这种颜色的链子，如果没有，就是断掉了。

2. 一条链子从另一条外面跑到了里面或者跑到了另一端。这个的判断可以通过记录一个链子和另一个链子的相对位置关系来解决。在程序中，我完成了两个函数，一个函数（$\text{UP}$）用来判断链子 $x$ 是否在某一个时刻出现在了链子 $y$ 的上方，另一个函数 $\text{IN}$ 判断了是否存在某一个时刻使得链子 $x$ 包含于 $y$ 内。这两个函数只要出现对于的情况就立即返回，分别调用这两个函数两次，取相对关系。在最后，只需要知道这些函数中是否只有一个是真就行了，否则就一定出现了从链子相交的情况。

3. 出现了一个链子一段在另一个链子中间，另一段在外面。这种情况比较简单，而且一旦出现，一定是不符合题目的，直接判断就好。

4. 包含在外面的链子只出现了一小段。这种情况是最难想到的。当能照到的地方链子 $a$ 全都在 $b$ 的外面，但是 $b$ 要比 $a$ 更长，也就是出现得更早或者结束得更晚，这种情况同样是不可能的，因为在如果真的包含，就一定在外层全都包裹住，出现上述情况的可能结果只有链子断掉或者相交，都是不满足条件的。


---
### 代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,T,x1[55][55],x2[55][55],len[55],num,fi[55],la[55];
int check(int x,int y){
	for(int i=max(fi[x],fi[y]);i<=min(la[x],la[y]);i++){
		if(x1[i][x]>x1[i][y]&&x1[i][x]<x2[i][y]&&!(x2[i][x]>x1[i][y]&&x2[i][x]<x2[i][y]))return 1;
		if(x2[i][x]>x1[i][y]&&x2[i][x]<x2[i][y]&&!(x1[i][x]>x1[i][y]&&x1[i][x]<x2[i][y]))return 1;
	}
	return 0;
}
int IN(int x,int y){
	for(int i=max(fi[x],fi[y]);i<=min(la[x],la[y]);i++){
		if(x1[i][x]>x1[i][y]&&x1[i][x]<x2[i][y]&&x2[i][x]>x1[i][y]&&x2[i][x]<x2[i][y]){
			if(fi[x]<fi[y]||la[x]>la[y])return 2;
			return 1;//x in y
		}
	}
	return 0;
}
int UP(int x,int y){
	for(int i=max(fi[x],fi[y]);i<=min(la[x],la[y]);i++){
		if(x1[i][x]>x2[i][y])return 1;
	}
	return 0;
}
void init(){
	memset(x1,0,sizeof(x1));
	memset(x2,0,sizeof(x2));
	memset(len,0,sizeof(len));
	memset(fi,0,sizeof(fi));
	memset(la,0,sizeof(la));
}
void work(){
	init();
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&len[i]);
		for(int j=1;j<=len[i];j++){
			scanf("%d",&num);
			if(x1[i][num]==0)x1[i][num]=j;
			else x2[i][num]=j;
			if(fi[num]==0)fi[num]=i;
			la[num]=i;
		}
	}
	//判断是否是连续的
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		if(fi[i]<=j&&j<=la[i]&&x1[j][i]==0){
			printf("NO\n");
			return;
		}
	}
	//两两判断
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++){
		if(la[i]<fi[j]||la[j]<fi[i])continue;
		if(check(i,j)||check(j,i)){
			printf("NO\n");
			return;
		}
		int tot=IN(i,j)+IN(j,i)+UP(i,j)+UP(j,i);
		if(tot>1){
			printf("NO\n");
			return;
		}
	}
	printf("YES\n");
}
int main(){
	scanf("%d",&T);
	while(T--){
		work();
	}
	return 0;
}
```


---

## 作者：blln (赞：1)

#### 详细思路

钦定 $1\leq a<b<c\leq n$,$1\leq x,y\leq n$。

需要考虑以下几种情况是不合法的。

1. 在同一层里有交叉的。
2. 颜色 $i$ 在第 $a$ 层出现过，在第 $b$ 层没有出现，在第 $c$ 层出现过。
3. 在第 $x$ 层颜色 $i$ 包含颜色 $j$，在第 $y$ 层颜色 $j$ 包含颜色 $i$。
4. 颜色 $i$ 与颜色 $j$ 并列在同一层，在第 $x$ 层颜色 $i$ 在颜色 $j$ 的前面，在第 $y$ 层颜色 $i$ 在颜色 $j$ 的后面。
5. 在第 $x$ 层颜色 $i$ 包含颜色 $j$ ，在第 $y$ 层颜色 $i$ 与颜色 $j$ 并列在同一层。
6. 在第 $x$ 层颜色 $i$ 被最近一种颜色包含的是颜色 $j$，在第 $y$ 层颜色 $i$ 被最近一种颜色包含的是颜色 $k$。

#### 具体实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105,Mx=1e5;
int T,n,m,K,X,Z,O,o=0,a[N],b[N],L[N],c[N],w[N],vis[N],d[N][N],f[N][N],D[N],F[N],Kr[N];
int main(){
    priority_queue<int>tot;
    scanf("%d",&T);
    while(T--){
        scanf("%d %d",&n,&m);Z=0;
        for(int i=1;i<=n;i++)a[i]=c[i]=b[i]=L[i]=D[i]=F[i]=Kr[i]=0,w[i]=Mx;
        for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)d[i][j]=f[i][j]=0;
        for(int i=1;i<=m;i++){
            scanf("%d",&K);O=0;
            for(int j=0;j<=n;j++)L[j]=0;
            for(int j=1;j<=K;j++){
                scanf("%d",&X);
                if(a[X]!=0&&a[X]<i-1)Z=1;a[X]=i;
                if(c[X]==0){if(Kr[X])Z|=b[O]!=Kr[X];else Kr[X]=b[O];c[X]=1,d[b[O]][X]=1,O++,b[O]=X,w[X]=min(w[X],O),L[O+1]=0;}
                else{
                    if(b[O]!=X)Z=1;
                    else{if(L[O]!=0)f[L[O]][X]=1;L[O]=X;}
                    O--;c[X]=0;
                }
            }
        }
        for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(d[i][j]&&w[i]>=w[j])Z=1;
        for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)D[i]+=d[j][i];
        for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)F[i]+=f[j][i];
        for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if((d[i][j]||d[j][i])&&(f[i][j]||f[j][i]))Z=1;
        for(int i=1;i<=n;i++)if(D[i]==0)tot.push(i);
        O=0;while(!tot.empty()){K=tot.top();tot.pop();O++;for(int i=1;i<=n;i++)if(d[K][i]){D[i]--;if(D[i]==0)tot.push(i);d[K][i]=0;}}Z|=(O!=n);
        for(int i=1;i<=n;i++)if(F[i]==0)tot.push(i);
        O=0;while(!tot.empty()){K=tot.top();tot.pop();O++;for(int i=1;i<=n;i++)if(f[K][i]){F[i]--;if(F[i]==0)tot.push(i);f[K][i]=0;}}Z|=(O!=n);
        if(Z)printf("NO\n");
        else printf("YES\n");
    }
}
```

---

## 作者：Purslane (赞：0)

## Solution

Trick : 两两检查 .

考虑到相交肯定是两两相交 , 所以可以两两 check 一下 .

考虑怎么不相交 : 包含或相离 . 这两个都很好判断 .

还有考虑断开 . 显然出现的区间一定是连续的 , 不连续果断判错 .

code :

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=50+10;
int T,n,m,fst[MAXN],lst[MAXN],pl1[MAXN][MAXN],pl2[MAXN][MAXN];
int contain(int x,int y) {
	if(!(fst[x]<=fst[y]&&lst[x]>=lst[y])) return 0;
	ffor(i,fst[y],lst[y]) if(!(pl1[i][x]<=pl1[i][y]&&pl2[i][x]>=pl2[i][y])) return 0;
	return 1;
}
int diff(int x,int y) {
	ffor(i,1,m) if(pl1[i][y]&&!(pl2[i][x]<=pl1[i][y])) return 0;
	return 1;
}
void work(void) {
	memset(pl1,0,sizeof(pl1)),memset(pl2,0,sizeof(pl2)),memset(fst,0,sizeof(fst)),memset(lst,0,sizeof(lst));
	cin>>n>>m;
	ffor(i,1,m) {
		int len;cin>>len;
		ffor(j,1,len) {
			int col;cin>>col;
			if(pl1[i][col]) pl2[i][col]=j;
			else pl1[i][col]=j;
			if(fst[col]==0) fst[col]=i;lst[col]=i;
		}
	}
	ffor(col,1,n) {
		ffor(j,1,m) if(j>=fst[col]&&j<=lst[col]&&!pl1[j][col]) return printf("NO\n"),void();
	}
	ffor(i,1,n) ffor(j,1,n) if(i!=j&&!contain(i,j)&&!contain(j,i)&&!diff(i,j)&&!diff(j,i)) return printf("NO\n"),void();
	printf("YES\n");
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;while(T--) work();
	return 0;
}
```

---

