# 巴比伦塔 The Tower of Babylon

## 题目描述

你可能已经听说过巴比伦塔的传说。现在这个传说的许多细节已经被遗忘。所以本着本场比赛的教育性质，我们现在会告诉你整个传说：

巴比伦人有 $n$ 种长方形方块，每种有无限个，第 $i$ 种方块的三边边长是 $xi,yi,zi$。对于每一个方块，你可以任意选择一面作为底，这样高就随着确定了。举个例子，同一种方块，可能其中一个是竖着放的，一个是侧着放的，一个是横着放的。

他们想要用堆方块的方式建尽可能高的塔。问题是，只有一个方块的底的两条边严格小于另一个方块的底的两条边，这个方块才能堆在另一个上面。这意味着，一个方块甚至不能堆在一个底的尺寸与它一样的方块的上面。

你的任务是编写一个程序，计算出这个塔可以建出的最高的高度。

## 样例 #1

### 输入

```
1
10 20 30
2
6 8 10
5 5 5
7
1 1 1
2 2 2
3 3 3
4 4 4
5 5 5
6 6 6
7 7 7
5
31 41 59
26 53 58
97 93 23
84 62 64
33 83 27
0```

### 输出

```
Case 1: maximum height = 40
Case 2: maximum height = 21
Case 3: maximum height = 28
Case 4: maximum height = 342```

# 题解

## 作者：OBJECT_705X (赞：19)

本蒟蒻看到这道题的题解前几篇题解都是Pascal，
有几篇几篇C的还是用的for循环递推，那我就来一篇递归dp的；

这道题是紫书上的例题，就是把那个嵌套矩形模型变了一点；
模板求的是嵌套最大个数，状态转移方程为
d(i)=max{d(j)+1 | (i,j)∈E};

这道题是求最大高度，于是状态转移变为
d(i)=max{d(j)+(i号长方体的高） | (i,j)∈E }

状态总数为n，每个状态的决策数为n，总时间复杂度为O(n²)
下面是代码：
```cpp
#include <iostream>
#include <cstring>
using namespace std;
int n,m,d[95];
struct Cube
{
	int x,y,z;//以x,y为底(不分顺序),z为高的立方体
	void in(int a,int b,int c)
	{
		x=a,y=b,z=c;
		return;
	}
	bool operator > (const Cube& T)// 重载 > 号表示T可以落在上面
	{
		return ((x>T.x && y>T.y) || (x>T.y && y>T.x));
	}
}c[95];//最多30个长方体,以不同棱为高，一共3*30=90种不同的长方体

int DP(int id)//当前的长方体下标是id
{
	if(d[id]>0) return d[id];//记忆化搜索，搜过的直接返回
	d[id]=c[id].z;//不在上面磊的话高度就等于该长方体的高
	for(int i=1;i<=m;i++) if(c[id]>c[i]) d[id]=max(d[id],DP(i)+c[id].z);
	//枚举所有长方体，如果i能落在id上，取最大的i能磊成的高度 （进入下一层DP） 加上该长方体的高；
	return d[id];//放回结果
}
int Solve(void)
{
	int Ans=0;
	memset(d,0,sizeof(d));
	for(int i=1;i<=m;i++) Ans=max(DP(i),Ans);//取最大的即为答案
    return Ans;
}
bool Input(void)//输入
{
	scanf("%d",&n);
	if(n==0) return false;
	m=3*n;
	for(int i=1;i<=m;i+=3)
	{
		int p,q,r;
		scanf("%d %d %d",&p,&q,&r);
		c[i].in(p,q,r),c[i+1].in(p,r,q),c[i+2].in(q,r,p);//一块长方体分别以r,q,q为高
	}
	return true;
}
int main(void)
{
	int cnt=0;
	while(Input()) printf("Case %d: maximum height = %d\n",++cnt,Solve());
	return 0;
}
```

---

## 作者：王奕霏 (赞：15)

~~挺简单的一道题~~

前面几位题解都在用动态规划，这里用的是最短路。
```



```


------------

**_首先输入方块，一种方块有三种摆放方法，所以当成三个点来看待。_ 
**
```cpp
for(int i=1;i<=3*n;i+=3){//输入方块
	int x, y, z;
	cin >> x >> y >> z;
	cube[i].x=x; cube[i].y=y; cube[i].z=z;
	cube[i+1].x=y; cube[i+1].y=z; cube[i+1].z=x;
	cube[i+2].x=z; cube[i+2].y=x; cube[i+2].z=y;
}

```
```




```


------------

** _规定如果一个方块i可以放到方块j上，那么从j到i连一条单向边，边权为方块i的高度。_ **
```cpp
for(int i=1;i<=n*3;i++){//建图
	for(int j=1;j<=n*3;j++){
		if((cube[i].x<cube[j].x && cube[i].y<cube[j].y) || (cube[i].x<cube[j].y && cube[i].y<cube[j].x)){
			Node a;
			a.from=j;
			a.to=i;
			a.weight=cube[i].z;
			edges[j].push_back(a);
		}
	}
}

```
```





```


------------

** _之后进行spfa算出最长路（其实跟最短路一样）
不会最短路的同学建议去看一下最短路模板_ **
```cpp
void spfa(){
	while(!q.empty()){
		int top=q.front(); q.pop();
		visited[top]=false;
		for(int i=0;i<edges[top].size();i++){
			int t=edges[top][i].to;
			if(dis[t]<edges[top][i].weight+dis[top]){
				dis[t]=edges[top][i].weight+dis[top];
				if(!visited[t]){
					visited[t]=true;
					q.push(t);
				}
			}
		}
	}
}




```


------------


------------

** _代码献上_ **
```cpp
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>

using namespace std;
int n, mx;
int dis[100], visited[100];
queue<int> q;
struct cubes{
	int x;
	int y;
	int z;
}cube[100];
struct Node{
	int from;
	int to;
	int weight;
};
vector<Node> edges[100];

void spfa(){
	while(!q.empty()){
		int top=q.front(); q.pop();
		visited[top]=false;
		for(int i=0;i<edges[top].size();i++){
			int t=edges[top][i].to;
			if(dis[t]<edges[top][i].weight+dis[top]){
				dis[t]=edges[top][i].weight+dis[top];
				if(!visited[t]){
					visited[t]=true;
					q.push(t);
				}
			}
		}
	}
}

int main(){
	cin >> n;
	int c=0;
	while(n!=0){
		c++;
		memset(cube, 0, sizeof(cube));
		memset(dis, 0, sizeof(dis));
		for(int i=0;i<100;i++){
			edges[i].clear();
		}
		for(int i=1;i<=3*n;i+=3){
			int x, y, z;
			cin >> x >> y >> z;
			cube[i].x=x; cube[i].y=y; cube[i].z=z;
			cube[i+1].x=y; cube[i+1].y=z; cube[i+1].z=x;
			cube[i+2].x=z; cube[i+2].y=x; cube[i+2].z=y;
		}
		for(int i=1;i<=n*3;i++){
			for(int j=1;j<=n*3;j++){
				if((cube[i].x<cube[j].x && cube[i].y<cube[j].y) || (cube[i].x<cube[j].y && cube[i].y<cube[j].x)){
//					cout << j << " to " << i << ": " << cube[j].x << " " << cube[i].x << "   " << cube[j].y << " " << cube[i].y << endl;
					Node a;
					a.from=j;
					a.to=i;
					a.weight=cube[i].z;
					edges[j].push_back(a);
				}
			}
		}
		for(int i=1;i<=3*n;i++){
			dis[i]=cube[i].z;
			q.push(i);
			visited[i]=true;
		}
		spfa();
		int mx=0;
		for(int i=1;i<=n*3;i++){
			if(dis[i]>mx) mx=dis[i];
		}
		cout << "Case " << c << ": maximum hight = ";
		cout << mx << endl;
		cin >> n;
	}
	return 0;
}
```

---

## 作者：一扶苏一 (赞：11)

### 　　一眼看出这是个DAG上的DP，一个信息分成三个方块存储。然后开始读入，拓扑，输出，过样例，提交，WA……

　　　这里的关键是拓扑序应该怎么求。首先我的比较函数写法如下：

```cpp
inline bool cmp(const Block &a,const Block &b) {
    return (a.l1<b.l1&&a.l2<b.l2)||(a.l2<b.l1&&a.l1<b.l2);
}
```


　　　然后由于sort的一些问题，这么写会挂掉。hack数据：我丢了……

　　　然后就来想想这个拓扑怎么求。

　　　考虑二元组(a,b)表示方块的长和宽，由于长和宽的顺序对放置无影响，所以不妨设a>=b。

　　　引理：若1能放在2上面，则2不能放在1上面。

　　　　证明：　　由题设，a1>a2，b1>b2。

　　　　　　　　　当2能放在1上面，a2>a1，b2>b1。矛盾。引理得证。

　　　定理：若a1+b1=a2+b2，则这两个方块不能叠放。

　　　	证明：不妨设a1>=a2。当a1==a2时，b1==b2。又a>b。显然不成立

　　	 当a1>a2，则b1<b2。故不成立。

　　　定理：当且仅当a1+b1<a2+b2时，方块2可能叠放在1上面。

　　　	证明：已证相等时不成立，现在证明前者大于后者时不成立。

　　　　　　　前者大于后者时，a1+b1>a2+b2。

　　　　　　　　　　当a1<a2，显然b1>b2。不成立。

　　　　　　　　　　当a1>a2，b1>b2，由引理，不成立。

　　　　　　　　　　当a1>a2，b1<b2，显然不成立。

　　　　　　　下面证明可能性

　　　　　　　　　　当a1<a2，b1<b2时，满足原式，可以叠放。

　　　　　　　定理得证。

　　　
## 由上述定理知，设si=ai+bi，则f[i]只可能由{f[j]|sj<si}转移得到。故将a+b得值设为阶段，进行转移。
  由此得到转移方程
     
# Code：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#ifdef ONLINE_JUDGE
#define putchar(o) \
puts("I am a cheater!")
#endif
#define maxn 100

inline void qr(int &x) {
    char ch=getchar();int f=1;
    while(ch>'9'||ch<'0')    {
        if(ch=='-')    f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')    x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x*=f;
    return;
}

inline int max(const int &a,const int &b) {if(a>b) return a;else return b;}
inline int min(const int &a,const int &b) {if(a<b) return a;else return b;}
inline int abs(const int &x) {if(x>0) return x;else return -x;}

inline void swap(int &a,int &b) {
    int c=a;a=b;b=c;return;
}

int n,a,b,c,frog[maxn];

struct Block {
    int h,l1,l2;
};
Block block[maxn];int top,cnt,ans;

inline void add(int x,int y,int z) {
    block[++top].h=x;block[top].l1=y;block[top].l2=z;
    if(block[top].l1<block[top].l2)    swap(block[top].l2,block[top].l1);
    block[++top].h=y;block[top].l1=x;block[top].l2=z;
    if(block[top].l1<block[top].l2)    swap(block[top].l2,block[top].l1);
    block[++top].h=z;block[top].l1=x;block[top].l2=y;
    if(block[top].l1<block[top].l2)    swap(block[top].l2,block[top].l1);
}

void clear() {
    std::memset(block,0,sizeof block);top=0;
    std::memset(frog,0,sizeof frog);ans=0;
}

inline bool cmp(const Block &a,const Block &b) {
    int sa=a.l1+a.l2,sb=b.l1+b.l2;
    return sa<sb;
}

inline bool judge(const Block &a,const Block &b) {
    return (a.l1<b.l1&&a.l2<b.l2)||(a.l2<b.l1&&a.l1<b.l2);
}

int main() {
    qr(n);
    while(n) {
        clear();
        for(int i=1;i<=n;++i) {
            a=b=c=0;qr(a);qr(b);qr(c);
            add(a,b,c);
        }
        std::sort(block+1,block+1+top,cmp);
        for(int i=1;i<=top;++i) {
            int &emm=block[i].h;
            frog[i]=emm;
            for(int j=1;j<i;++j) {
                if(judge(block[j],block[i])) frog[i]=max(frog[i],frog[j]+emm);
            }
            ans=max(ans,frog[i]);
        }
        printf("Case %d: maximum height = %d\n",++cnt,ans);
        n=0;qr(n);
    }
    return 0；
}
```

[blog](https://www.cnblogs.com/yifusuyi/p/9218939.html)上看更详细哦

---

## 作者：xs_siqi (赞：9)

补充一个没被提到的新 $O(n\log n)$ 做法。

首先先简化题意。

每个方块可以被利用多次，但是必须在严格小于的情况下。并且同一层不能有多个方块（否则可以无限放）。我们知道，一个方块最多只有 $n\times 6$ 种释放方式，所以我们把六种释放方式全部存到数组里。根据“严格小于”的条件，每个方块的每种释放方式最多只能被放一次了。

注意：以下提到的 $n$ 均为题面中的 $n$ 乘 $6$ 后的值。

对于多维状态的题目，我们第一步很自然都是去降状态。

我们发现，对于三元组 $(x,y,z)$，只有 $(x,y)$ 关于状态是有用的。所以我们只需要处理 $x,y$ 即可。

不难想到，首先按 $y$ 排序，然后我们只需要处理 $x$ 就行了。$z$ 可以交给 dp 处理。

然后我们就能发现一个 $O(n^3)$ 的 dp。不妨将 $x,y$ 离散化后，以 $x$ 为第一维下标，$y$ 为第二维下标。对于每一个二元组 $(x,y)$，可以从 $f_{k,l},k\in [x+1,n],l\in [y+1,n]$ 转移过来。为什么上界是 $n$？因为离散化后最多到 $n$。对于每个节点都要枚举 $n^2$ 次，复杂度是 $O(n^3)$ 的。离谱的是这竟然直接 AC 了。

给出一种可能的 dp 实现。

```cpp
for(int i=n;i>=1;i--)
	for(int j=a[i].x+1;j<=n;j++)
		for(int k=a[i].y+1;k<=n;k++)
			f[a[i].x][a[i].y]=max(f[j][k]+a[i].z,f[a[i].x][a[i].y]);
for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		ans=max(ans,f[i][j]);
```
然后我们继续考虑优化这件事情。

我们发现，$y$ 是已经排序过的东西。对于每一个 $(x_i,y_i)$，它不能转移的条件有且仅有 $y$ 是否与其相等。对于 $x$ 是否转移可以在循环内特判掉。

对于这个 $y$，我们可以当每一次不相等的时候，对 $y$ 做一个后缀最大值。对于相同的 $y$ 可以考虑用临时数组保存。这样的复杂度是 $O(n^2)$ 的。

给出一种可能的实现。

```cpp
int lst=n;
for(int i=n;i>=1;i--){
	for(int j=a[i].x+1;j<=n;j++)
		ls[a[i].x]=max(f[j]+a[i].z,ls[a[i].x]);
	if(a[i-1].y!=a[i].y){
		for(int j=lst;j>=i;j--)
     			f[a[j].x]=max(f[a[j].x],ls[a[j].x]),ls[a[j].x]=0;
		lst=i-1;}}
for(int i=1;i<=n;i++)
	ans=max(ans,f[i]);
```

请注意，后一段更新 $f$ 的复杂度是线性的，而不是平方的。因为考虑到我已经将每次更新的保存，在整个对于 $i$ 的循环中，这句话只会被执行 $n$ 次，均摊一下就是线性了。

然后发现瓶颈是对于临时数组的更新。我们发现上面更新的式子其实可以把 $f_j$ 提出来，对 $f_j$ 做一个区间最大值。然后对 $f$ 更新可以理解为单点修改。这样我们用线段树就可以完美的做完这件事情。时间复杂度变为 $O(n\log n)$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ls rt<<1
#define rs rt<<1|1
#define int long long
using namespace std;
const int maxn=185;
int n,b[maxn],f[maxn],ans,cs,lss[maxn],T[maxn*4];
struct edge{
	int x,y,z,id;}a[maxn];
bool cmp(edge x,edge y){
	return x.x<y.x;}
bool cmp2(edge x,edge y){
	return x.y<y.y;}
void pushup(int rt){
	T[rt]=max(T[ls],T[rs]);}
void modify(int rt,int l,int r,int x,int p){
	if(l==r&&l==x){
		T[rt]=max(T[rt],p);
		return ;}
	int mid=l+r>>1;
	if(x<=mid)modify(ls,l,mid,x,p);
	else modify(rs,mid+1,r,x,p);
	pushup(rt);}
void modify2(int rt,int l,int r,int x){
	if(l==r&&l==x){
		T[rt]=0;
		return ;}
	int mid=l+r>>1;
	if(x<=mid)modify2(ls,l,mid,x);
	else modify2(rs,mid+1,r,x);
	pushup(rt);}
int query(int rt,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return T[rt];
	int mid=l+r>>1,ans=0;
	if(ql<=mid)ans=query(ls,l,mid,ql,qr);
	if(qr>mid)ans=max(ans,query(rs,mid+1,r,ql,qr));
	return ans;}
signed main(){
	while(1){
		ans=0;
		scanf("%lld",&n);
		if(!n)break;
		for(int x,y,z,i=1;i<=n;i++){
			scanf("%lld%lld%lld",&x,&y,&z);
			a[6*(i-1)+1]=(edge){x,y,z,6*(i-1)+1};
			a[6*(i-1)+2]=(edge){x,z,y,6*(i-1)+2};
			a[6*(i-1)+3]=(edge){y,x,z,6*(i-1)+3};
			a[6*(i-1)+4]=(edge){y,z,x,6*(i-1)+4};
			a[6*(i-1)+5]=(edge){z,x,y,6*(i-1)+5};
			a[6*(i-1)+6]=(edge){z,y,x,6*(i-1)+6};}
		n*=6;
		for(int i=1;i<=n;i++)modify2(1,1,n,i);
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++){
			if(a[i].x==a[i-1].x)b[i]=b[i-1];
			else b[i]=b[i-1]+1;}
		for(int i=1;i<=n;i++)a[i].x=b[i];
		sort(a+1,a+n+1,cmp2);
		for(int i=1;i<=n;i++){
			if(a[i].y==a[i-1].y)b[i]=b[i-1];
			else b[i]=b[i-1]+1;}
		for(int i=1;i<=n;i++)a[i].y=b[i];
		int lst=n;
		for(int i=n;i>=1;i--){
			lss[a[i].x]=query(1,1,n,a[i].x+1,n)+a[i].z;
			if(a[i-1].y!=a[i].y){
				for(int j=lst;j>=i;j--)
					modify(1,1,n,a[j].x,lss[a[j].x]),lss[a[j].x]=0;
				lst=i-1;}}
		printf("Case %lld: maximum height = %lld\n",++cs,query(1,1,n,1,n));}
	return 0;}
```

总结：对于多维状态的 dp，降状态不乏为一个实用的套路。对于最终式子可以看情况进行数据结构优化。

---

## 作者：ljcljc (赞：6)

【分析】

很显然是一道$DAG$动归，我看没有人写$DFS$版的，于是就来凑个数。

我们可以用结构体存这长方体的长宽高，很明显每一个长方体都有$6$种摆法（自行脑补），然而我们不难发现高相等的两种摆法是可以算作一种，于是我们可以用长方体的编号与高的编号来确定一个长方体。

然后我们用一个二维数组$dp[i][j]$表示**加上用$j$作高的第$i$个长方体所能达到的最高高度**。

详细思路见代码。

【AC代码】

~~文明你我他，不要抄代码~~
```cpp
//UVA437 巴比伦塔 The Tower of Babylon
//code by ljc
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 50;
int n, k, ans, dp[MAXN][3];
struct block {
    int no[3];
} blk[MAXN];
int dfs(int t, int h) {
    if(dp[t][h] > 0) return dp[t][h];
    dp[t][h] = blk[t].no[h];
    for(int i=1; i<=n; i++) {
        for(int j=0; j<=2; j++) {
        	//下面长方体的长宽
            int a = (h+1)%3;
            int b = (h+2)%3;
        	//当前长方体的长宽
            int x = (j+1)%3;
            int y = (j+2)%3;
            if(blk[i].no[x]<blk[t].no[a] && blk[i].no[y]<blk[t].no[b] || blk[i].no[y]<blk[t].no[a] && blk[i].no[x]<blk[t].no[b]) { //上面长方体的长宽要严格小于下面的
                dp[t][h] = max(dp[t][h], blk[t].no[h]+dfs(i, j));
            }
        }
    }
    return dp[t][h];
}
int main() {
    while(cin >> n && n) {
        memset(dp, 0, sizeof(dp));
        ans = -1;
        for(int i=1; i<=n; i++)
            cin >> blk[i].no[0] >> blk[i].no[1] >> blk[i].no[2]; //长方形的长宽高
        for(int i=1; i<=n; i++)
            for(int j=0; j<=2; j++)//3种摆法
                ans = max(ans, dfs(i, j));
        printf("Case %d: maximum height = %d\n", ++k, ans);
    }
    return 0;
}
```

---

## 作者：夏真诚 (赞：6)

可以用记忆化搜索

题目中的三种放法，可以理解为三种不同的方块，其中长为a[i],宽为b[i]，高为c[i],那么n种方块就有三n种方块

思路

for i:=1 to 3n 开始 尝试以每块方块作为顶方块，再用状态（t,k）,t表示1到n种任意一种，k表示1到3种任意一种（也就是枚举3n种QAQ）

每次搜索依次寻找长和宽都大于当前方块的方块，若符合，则继续寻找下一方块，
返回时保存最优解pd数组，以便读取记忆

注意输出格式！

代码如下
 ```pascal
var i,j,n,t,max,k,h2,h1,j1,j2,tt:longint;
  a1,b1,c1:array[1..10000]  of longint;
 a,b,c,pd:array[1..10000,1..3] of longint;
 procedure hh(var a,b:longint);//判断哪个大
 var t:longint;
  begin
  if a<b then
  begin
    t:=a;a:=b;b:=t;
    end;
   end;

function dfs(t,k:longint):longint;//搜索搜索QAQ
  var i,j,s:longint;
   begin
   s:=c[t,k];//若该方块未有方块叠加，初始值为该方块高
   if pd[t,k]>0 then exit(pd[t,k]);//已有记忆（最优解）
   for i:=1 to n do
     for j:=1 to 3 do//循环3n种方块
       if (a[t,k]<a[i,j]) and (b[t,k]<b[i,j]) then//比该方块大
         if dfs(i,j)+c[t,k]>s//搜索下一方块，并累加值
          then
         s:=dfs(i,j)+c[t,k];//替换最优解
       pd[t,k]:=s;//记录最优解
       exit(s);//返回
  end;
begin
 while k=0 do
  begin
   inc(tt);
   max:=0;
    fillchar(pd,sizeof(pd),0);//清空记忆
  readln(n);
  if n=0 then exit;
  for i:=1 to n do//将一种方块依次以三种放法放置成三种方块，再将长宽中长的作为长，短的作为宽
    begin
     readln(a[i,1],b[i,1],c[i,1]);  hh(a[i,1],b[i,1]);
     a[i,2]:=b[i,1];b[i,2]:=c[i,1];c[i,2]:=a[i,1];   hh(a[i,2],b[i,2]);
     a[i,3]:=a[i,1];b[i,3]:=c[i,1];c[i,3]:=b[i,1];   hh(a[i,3],b[i,3]);
   end;
for i:=1 to n do
      for j:=1 to 3 do

   if dfs(i,j)>max then max:=dfs(i,j);//找出最优放置
  writeln('Case ',tt,': maximum height = ',max);//注意空格QAQ
 end;
end.

```

---

## 作者：Snoaple (赞：5)

一道动态规划题，属于DAG有向无环图求最长路

理一下题意：n个方块，给出长宽高，求最高高度

搭建标准：上一个方块的底面长宽必须严格小于这一个方块的底面长宽

首先要预处理输入数据，预处理很重要（~~废话~~）

读入长宽高，就有六种不同的摆法

长宽作底，长高作底，高宽作底三种，底的长宽互换有两种，3*2=6

用数组存储，两个用来判断，剩下一个用来累计高度

从小到大利用搭建标准进行排序

如果利用f数组储存最后答案

根据题意我们可以把f[i]定义为**前i个方块所能达到的最高高度**

每次判断比自己底面长宽小的方块取或不取即为
```pascal
f[i]:=max(f[i],f[j]+gaodu[j]);
```
取了加高度，不取保持不变，至于方程，还是要自己理解

动态转移方程伪代码如下

```pascal
   for i:=1 to t do
    f[i]:=d3[i];//当然一个方块也有高度
   for i:=1 to t do
    for j:=1 to i do//由于已经排序只要到i即可
     if (d1[i]>d1[j]) and (d2[i]>d2[j]) then//能不能达到搭建的标准 
      begin
       f[i]:=max(f[i],f[j]+d3[i]);//判断取和不取
       maxe:=max(maxe,f[i]);//求一个最大值
      end;
```

最后输出maxe即可

还有一个输入数据的处理，以0结束，用一个repeat循环，c数组记录每组数据的答案，最后for循环输出（记得每次处理一组数据之前都要清空数组为0）

附上AC代码

```pascal
var
  n,i,j,t1,t2,t3,t,l1,maxe,x,y,z:longint;
  d1,d2,d3,f,c:array[0..10000] of longint;
  pd:boolean;
  function max(a1,b1:longint):longint;
    begin if a1>b1 then exit(a1) else exit(b1);end;
begin
  repeat
   inc(l1);
   readln(n);
   if n=0 then begin dec(l1);break;end;//输入处理
   fillchar(f,sizeof(f),0);
   fillchar(d1,sizeof(d1),0);
   fillchar(d2,sizeof(d2),0);
   fillchar(d3,sizeof(d3),0);//清空数组
   maxe:=0;t:=0;
   for i:=1 to n do
    begin
     readln(x,y,z);
     inc(t);
     d1[t]:=x;d2[t]:=y;d3[t]:=z;//长宽作底
     inc(t);
     d1[t]:=x;d2[t]:=z;d3[t]:=y;//长高作底
     inc(t);
     d1[t]:=y;d2[t]:=x;d3[t]:=z;//宽长作底
     inc(t);
     d1[t]:=y;d2[t]:=z;d3[t]:=x;//宽高作底
     inc(t);
     d1[t]:=z;d2[t]:=x;d3[t]:=y;//高长作底
     inc(t);
     d1[t]:=z;d2[t]:=y;d3[t]:=x;//高宽作底
    end;//以上是非常长的预处理
   for i:=1 to t-1 do
    for j:=i+1 to t do
     begin
      if (d1[j]<d1[i]) and (d1[j]<d2[i]) then
       begin
        t1:=d1[j];d1[j]:=d1[i];d1[i]:=t1;
        t2:=d2[j];d2[j]:=d2[i];d2[i]:=t2;
        t3:=d3[j];d3[j]:=d3[i];d3[i]:=t3;
       end;
     end;//以上是排序
   for i:=1 to t do
    f[i]:=d3[i];//当然一个方块也有高度
   for i:=1 to t do//动态转移方程
    for j:=1 to i do
     if (d1[i]>d1[j]) and (d2[i]>d2[j]) then begin
      f[i]:=max(f[i],f[j]+d3[i]);
      maxe:=max(maxe,f[i]);
      end;
   c[l1]:=maxe;//记录最终答案
  until 1>2;
  for l1:=1 to l1 do
   writeln('Case ',l1,': maximum height = ',c[l1]);//格式很重要
end.
```

---

## 作者：tzl_Dedicatus545 (赞：4)

## 思路

这道题根据题目内容 `正方体可以旋转` 我们可以想到思路：把正方体存三份，如下图所示：

$$\begin{cases}1. \{a,b,h\}\\
 2.\{a,h,b\} \\ 3,\{h,a,b\}  \end{cases}$$

DP 的状态转移方程很简单，就是普通的 DAG 树上 DP，如下（$h$ 为积木的高度）

$$ dp[u][i] \gets dp(i)+block[u].h $$

最后，要注意，判断是否积木 $a$ 能放 $b$ 上时，要比较两个，而且要比较严格最小值。


## AC Code

```cpp
//By: Luogu@wangdemao(308854)
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

struct Block
{
	int h,x,y;
};

bool adj[10000][10000];
Block block[10000];
int n;
int Case;
int f[10000];

bool canPut(int x,int y)
{
	if (block[x].x<block[y].x && block[x].y<block[y].y)
		return true;
	if(block[x].y<block[y].x && block[x].x<block[y].y)
		return true;
	return false;
}

int dp(int u)
{
	if(f[u])
		return f[u];

	f[u]=block[u].h;

	for(int i=1;i<=3*n;i++)
		if(adj[u][i])
			f[u]=max(f[u],dp(i)+block[u].h);

	return f[u];
}

int main()
{
	while(cin>>n && n!=0)
	{
		Case++;

		for(int i=1;i<=n;i++)
		{
			int x,y,z;

			cin>>x>>y>>z;

			block[3*i-2]={x,y,z};
			block[3*i-1]={y,z,x};
			block[3*i]={z,x,y};
		}

		for(int i=1;i<=3*n;i++)
			for (int j = i; j <=3*n; j++)
			{
				adj[i][j]=canPut(i,j);
				adj[j][i]=canPut(j,i);
			}

		memset(f,0,sizeof(f));

		int ans=0;

		for(int i=1;i<=3*n;i++)
			ans=max(ans,dp(i));

		cout<<"Case "<<Case<<": maximum height = "<<ans<<endl;

	}
	return 0;
}

```

---

## 作者：meowla (赞：3)

一道动态规划的题
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;//n表示方块数 
int m=0;//m表示互不相同的面数，一定等于n*3 
int a[91][3];//存放面的数组，a[][0]是底边1，a[][1]是底边2，a[][3]是高，其中a[][0]与a[][1]无序 
int dp[91]={0};//dp[i],状态i表示目前最上面的底是哪个面，dp[i]表示在这个面以上堆的方块的最高高度。dp[i]与a[i][]一一对应 
int t=0;//t表示目前的组数 
int results[3001];//保存每组答案，最终输出 
int blocksort()//对面进行排序，若面A可以放在面B上，则A在B前，这样做是为了动规递推时参数只会向一个方向变化 
{
	int temp1,temp2,temp3;
	for(int i=1;i<m;i++)	//选择排序 
	for(int j=i+1;j<=m;j++)
	if((a[j][0]<a[i][0] && a[j][1]<a[i][1]) || (a[j][1]<a[i][0] && a[j][0]<a[i][1]))	//若满足条件，则j可以放在i上 
	{
		temp1=a[j][0];
		temp2=a[j][1];
		temp3=a[j][2];
		a[j][0]=a[i][0];
		a[j][1]=a[i][1];
		a[j][2]=a[i][2];
		a[i][0]=temp1;
		a[i][1]=temp2;
		a[i][2]=temp3;
	} 
}
int main()
{
	cin>>n;
	
	while(n!=0)
	{
		memset(dp,0,sizeof(dp));
		memset(a,0,sizeof(a));
		m=0;
		//以上为重新初始化变量和数组 
		t++;
		int xi,yi,zi;
		int finalans=0;//final ans，最终要输出的答案 
		for(int i=1;i<=n;i++)
		{
			cin>>xi>>yi>>zi;
			m++;a[m][0]=xi;a[m][1]=yi;a[m][2]=zi;
			m++;a[m][0]=yi;a[m][1]=zi;a[m][2]=xi;
			m++;a[m][0]=zi;a[m][1]=xi;a[m][2]=yi;
		}
		blocksort();
		for(int i=1;i<=m;i++)  //这里用递推，需要先用blocksort排序，以防止访问到还没计算的dp[i]，而如果用记忆化搜索实现动态规划则不需要排序 
		{
			for(int k=1;k<i;k++)	//状态转移方程：dp(i)=a[i][2]+max{dp(k)| k∈[1,i)} 
				if((a[k][0]<a[i][0] && a[k][1]<a[i][1]) || (a[k][1]<a[i][0] && a[k][0]<a[i][1]))  //确认可以重，以避免互相都不能重导致排序时总有一个在另一个前面的情况 
					dp[i]=max(dp[i],dp[k]);
			dp[i]+=a[i][2];
			finalans=max(finalans,dp[i]);	//因为dp[m]不一定是最大值，所以随时取max 
		}
		results[t]=finalans;
		cin>>n;
	}
	for(int i=1;i<=t;i++)
	{
		printf("Case %d: maximum height = %d\n",i,results[i]);	//亲测UVA的题输出最后必须有一个换行 
	}
} 
```

---

## 作者：QwQ蒟蒻wjr (赞：2)

~~一个被恶意评分的题~~

这题就是让你求最长路

输入方块，有三种摆放方式，默认为x是长，y是宽，于是衍生出存边操作(n已经扩大到它的三倍)
```cpp
for(re int i=1,x,y,z; i<=n; i+=3)
{
	read(x);
	read(y);
	read(z);
	cnt[i].add(max(x,y),min(x,y),z);
	cnt[i+1].add(max(x,z),min(x,z),y);
	cnt[i+2].add(max(y,z),min(y,z),x);
}
```
使用记忆化搜索，很容易推出以下程序
```cpp
#include<cstdio>
#include<cstring>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
struct Edge
{
	int next,to,dis;
} edge[14410];
int in[200],dp[200],n,answer,kase;
bool vis[200];
struct node
{
	int x,y,z;
	inline void add(const int & x,const int & y,const int & z)
	{
		this->x=x;
		this->y=y;
		this->z=z;
	}
} cnt[200];
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
inline int DP(int x)
{
	if(vis[x])
		return dp[x];
	vis[x]=true;
	int & ans=dp[x]=cnt[x].z;
	for(re int i=1; i<=n; i++)
		if(cnt[x].x>cnt[i].x&&cnt[x].y>cnt[i].y)
			ans=max(ans,cnt[x].z+DP(i));
	return ans;
}
int main()
{
	while(read(n),n)
	{
		answer=~0x7fffffff;
		n*=0b11;
		memset(vis,false,sizeof(vis));
		for(re int i=1,x,y,z; i<=n; i+=3)
		{
			read(x);
			read(y);
			read(z);
			cnt[i].add(max(x,y),min(x,y),z);
			cnt[i+1].add(max(x,z),min(x,z),y);
			cnt[i+2].add(max(y,z),min(y,z),x);
		}
		for(re int i=1; i<=n; i++)
			answer=max(answer,DP(i));
		printf("Case %d: maximum height = %d\n",++kase,answer);
	}
	return 0;
}

```
复杂度O(n^2)

因为这题连边后是有向无环图，所以除了记忆化搜索，还可以使用拓扑排序O(n+m)~~至少比跑Floyd强~~
连边部分：
```cpp
for(re int i=1; i<=n; i++)
	for(re int j=1; j<=n; j++)
		if(cnt[i].x>cnt[j].x&&cnt[i].y>cnt[j].y)
		{
			add_edge(i,j,cnt[j].z);
			in[j]++;
		}
```
代码：
```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
struct Edge
{
	int next,to,dis;
} edge[14410];
int in[200],dis[200],n,answer,kase,head[200],num_edge;
bool vis[200];
struct node
{
	int x,y,z;
	inline void add(const int & x,const int & y,const int & z)
	{
		this->x=x;
		this->y=y;
		this->z=z;
	}
} cnt[200];
#define max(x,y) (x>y?x:y)
inline void add_edge(const int & from,const int & to,const int & dis)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
}
int main()
{
	while(read(n),n)
	{
		answer=~0x7fffffff;
		n*=0b11;
		num_edge=0;
		memset(head,0,sizeof(head));
		memset(vis,false,sizeof(vis));
		for(re int i=1,x,y,z; i<=n; i+=3)
		{
			read(x);
			read(y);
			read(z);
			cnt[i].add(max(x,y),min(x,y),z);
			cnt[i+1].add(max(x,z),min(x,z),y);
			cnt[i+2].add(max(y,z),min(y,z),x);
		}
		for(re int i=1; i<=n; i++)
			for(re int j=1; j<=n; j++)
				if(cnt[i].x>cnt[j].x&&cnt[i].y>cnt[j].y)
				{
					add_edge(i,j,cnt[j].z);
					in[j]++;
				}
		queue<int>q;
		for(re int i=1; i<=n; i++)
			if(in[i]==0)
				q.push(i);
		for(re int i=1; i<=n; i++)
			dis[i]=cnt[i].z;
		re int u;
		while(!q.empty())
		{
			u=q.front();
			q.pop();
			answer=max(answer,dis[u]);
			for(re int i=head[u]; i; i=edge[i].next)
			{
				int &v=edge[i].to,&w=edge[i].dis;
				dis[v]=max(dis[v],dis[u]+w);
				if(--in[v]==0)
					q.push(v);
			}
		}
		printf("Case %d: maximum height = %d\n",++kase,answer);
	}
	return 0;
}

```


---

## 作者：Yeji_ (赞：2)

## 前言
本题正解是DAGdp。但是用记忆化搜索就可以水过去

### 记忆化搜索
其实就是一种搜索的优化，没有什么可说的

## 思路
现在来讲一讲本题的思路

我们可以知道长，宽，高，你如果将他顺序给打乱，那么他们全排列数量为6也就是

- 长宽高 	
- 长高宽
- ......

所以我们存储6次边

dfs 就可以判断以前有没有这个状态，如果有，下一个状态。

然后就是非常简单的dp了

下面给出代码
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int n,a[11001],b[11001],c[11001],tot,x,y,z,dp[50000],casse;
void add(int x,int y,int z)
{
    a[++tot]=x; b[tot]=y; c[tot]=z;
    a[++tot]=x; b[tot]=z; c[tot]=y;
    a[++tot]=y; b[tot]=x; c[tot]=z;
    a[++tot]=y; b[tot]=z; c[tot]=x;
    a[++tot]=z; b[tot]=x; c[tot]=y;
    a[++tot]=z; b[tot]=y; c[tot]=x;
}
int dfs(int u)
{
    if (dp[u]!=0)
        return dp[u];
    dp[u]=c[u];
    for(int i=1;i<=tot;i++)
        if (a[i]<a[u]&&b[i]<b[u])
            dp[u]=max(dp[u],c[u]+dfs(i));
    return dp[u]; 
}
int main()
{
    while(1)
    {
        scanf("%d",&n);
        if (n==0)
            break;
        tot=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d %d %d",&x,&y,&z);
            add(x,y,z);
        }
        int ans=0;
        for (int i=1;i<=tot;i++)
        {
            memset(dp,0,sizeof dp);
            ans=max(ans,dfs(i));
        }
        
        printf("Case %d: maximum height = %d\n",++casse,ans);
    }
}
```


---

## 作者：封禁用户 (赞：2)

一道DP

~~类似最长不下降子序列,CF4D~~

# 但注意要排序(按面积排序)

# 可以用结构体(struct/class)

说到这,OIer们一脸懵逼,What is struct,can it eat?

结构体(struct)是由一系列具有相同类型或不同类型的数据构成的数据集合，叫做结构。(度娘)

OIer们大呼how terrible!

其实,struct(class)是C语言一种用户可定义的数据类型。我们熟悉的数据类型有:int,double,float,long long,short,char,string,map,bool,vector,queue等

struct具体定义如下:
```cpp
struct OIer//新定义类型的名字
{
       int x,y;//参数
};//';'不能忘
```
class具体定义如下:
```cpp
class Oier//名字
{
	public://很重要!
		int x,y;
};//分号不要忘
```
定义一个变量就是把结构体的名字+变量的名字

调用该变量参数是直接加.参数

如:

```cpp
class OIer
{
public:
	double ability;
	double AC;
};
OIer ruoxiangxi;
ruoxiangxi.ability=0.2333;
ruoxiangxi.AC=23.3333333
```
结构体还可以重载(chóng zǎi)运算符:>,<,=,+……
如：
```cpp
bool operator<(const Node &A) const
//返回类型+operator+重载对象+(运算对象)
```
结构体也可以函数.

最常用的是构造函数.

它有2大特征:

1:无返回值

2:函数名为结构体名字

如下:
```cpp
Node(int a,int b,int c){x = a,y=b,z=c;}
```

贴代码:
```cpp
#include <bits/stdc++.h>
#define mp make_pair
using namespace std;

struct Node{
	int x, y, z;
	bool operator<(const Node &A) const
	{
		return mp(x, y)>mp(A.x, A.y);//节省了CMP函数
	}
	Node(){}
	Node(int a,int b,int c){x = a,y=b,z=c;}
}a[210];
int dp[210];
int main()
{
	int n,TTT=0;
	while(scanf("%d",&n)&&n!=0)
	{
		TTT++;
		int m=0;
		for (int i=0;i<n;i++)
		{
			int x,y,z; scanf("%d%d%d",&x,&y,&z);
			a[m++]=Node(x,y,z),a[m++]=Node(x,z,y);
			a[m++]=Node(y,x,z),a[m++]=Node(y,z,x);
			a[m++]=Node(z,x,y),a[m++]=Node(z,y,x);
		}
		sort(a,a+m);
		memset(dp,0,sizeof(dp));//DP
		int ans=0;
		for (int i=0;i<m;i++)
		{
			dp[i]=a[i].z;
			for (int j=0;j<i;j++)
				if (a[j].x>a[i].x&&a[j].y>a[i].y)
					dp[i] = max(dp[i],dp[j]+a[i].z);
			ans=max(ans,dp[i]);
		}
		printf("Case %d: maximum height = %d\n", TTT, ans);//输出格式
	}
	return 0;
}
```


---

## 作者：kradcigam (赞：1)

这题其实有 $O(n \log n)$​ 的做法。

首先，如果一个砖块可以压在另一个砖块上面只要满足长边比另一个砖块的长边小，短边也比另一个砖块的短边小，这是非常显然的。写成式子：如果这个砖块宽和长分别为 $kx,ky(kx<ky)$​，另一个砖块宽和长分别为 $tx,ty(tx<ty)$​，若满足 $kx<tx,ky<ty$​ 则可以放。

这就非常像二维数点，于是我们保证好长宽的大小关系，离散化一下，直接用树状数组二维数点即可。

```cpp
#include<bits/stdc++.h>
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define LL long long
#define SZ(x) ((int)x.size()-1)
#define ms(a,b) memset(a,b,sizeof a)
#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define DF(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
inline int read(){char ch=getchar(); int w=1,c=0;
	for(;!isdigit(ch);ch=getchar()) if (ch=='-') w=-1;
	for(;isdigit(ch);ch=getchar()) c=(c<<1)+(c<<3)+(ch^48);
	return w*c;
}
const int N=110;
int cnt,tot,s[N],x[N],y[N],z[N];
namespace BIT{
 	LL maxn[N];
 	void add(int x,LL y){for(;x<=tot;x+=x&-x)maxn[x]=max(maxn[x],y);}
 	LL qry(int x){LL s=0;for(;x;x-=x&-x)s=max(s,maxn[x]);return s;}
}
using namespace BIT;
vector<pair<int,int> >v[N];
LL f[N],ans;
signed main(){
	int n=read();
	for(;n;n=read()){
		ans=0;tot=0;
		F(i,1,n){
			x[i]=read(),y[i]=read(),z[i]=read();
			s[++tot]=x[i];
			s[++tot]=y[i];
			s[++tot]=z[i];
		}sort(s+1,s+tot+1);
		tot=unique(s+1,s+tot+1)-s-1;
		F(i,1,tot)maxn[i]=0,v[i].clear();
		F(i,1,n){
			x[i]=lower_bound(s+1,s+tot+1,x[i])-s;
			y[i]=lower_bound(s+1,s+tot+1,y[i])-s;
			z[i]=lower_bound(s+1,s+tot+1,z[i])-s;
			if(x[i]>y[i])swap(x[i],y[i]);
			if(x[i]>z[i])swap(x[i],z[i]);
			if(y[i]>z[i])swap(y[i],z[i]);
			v[y[i]].emplace_back(x[i],z[i]);
			v[z[i]].emplace_back(x[i],y[i]);
			v[z[i]].emplace_back(y[i],x[i]);
		}
		F(i,1,tot){
			queue<LL>q;
			for(auto[j,k]:v[i])q.push(qry(j-1)+s[k]);
			for(auto[j,k]:v[i]){
				LL x=q.front();q.pop();
				ans=max(ans,x);
				add(j,x);
			}
		}printf("Case %d: maximum height = %lld\n",++cnt,ans);
	}
	return 0;
}
```



---

## 作者：洛桃 (赞：1)

## 一道DAGdp
### 思路
首先要明确，我们要求的是**最长路**，图可以根据立方体间的关系来建，如果这个立方体可以放在另一个上面，就从代表这个立方体的点向那个点连一条有向边。
因为两条边都是严格小于下面的立方体的，所以这个图一定是个**有向无环图（DAG）**。

另外，由于每个立方体有三种高，所以总共会有3n种不同的立方体，空间要开三倍。

这里我是用的邻接矩阵建图+记忆化搜索；

### 代码如下（附注释）

```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,d[100][3],kase,sh[31][3];//d是记忆化用的数组 
int tot;
bool G[100][100];//因为只要判断能不能搭上去，所以只用bool，节省空间 
struct node{
	int x,y,su,h;//x,y,h分别代表这个立方体的长宽高，su代表高的类型 
}S[100];
int dp(int num,int su)//num是当前立方体的编号，su意思同上 
{
	int& ans=d[num][su];
	if(ans>0)return ans;//记忆化 
	ans=S[num].h;
	for(int i=1;i<=tot;i++)
	if(G[num][i])ans=max(ans,dp(i,S[i].su)+S[num].h);//如果有连边，就更新
	return ans;
}
int main()
{
	while(1)
	{
		scanf("%d",&n);
		if(!n)break;	
		memset(d,0,sizeof(d));
		memset(G,0,sizeof(G));//多组数据记得初始化 
		int maxn=-1;tot=0;
		for(int i=1;i<=n;i++)scanf("%d%d%d",&sh[i][0],&sh[i][1],&sh[i][2]);//读入三种边 
		printf("Case %d: maximum height = ",++kase);
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<3;j++)//记录每一种类型的立方体 
			{
				S[++tot].su=j;
				S[tot].h=sh[i][j];
				if(j==0)
				S[tot].x=sh[i][1],S[tot].y=sh[i][2];
				if(j==1)
				S[tot].x=sh[i][0],S[tot].y=sh[i][2];
				if(j==2)
				S[tot].x=sh[i][0],S[tot].y=sh[i][1];
			}
		}
		for(int i=1;i<=tot;i++)//建图 
		{
			for(int j=1;j<=tot;j++)
			{
				if(i!=j&&((S[i].x<S[j].x&&S[i].y<S[j].y)||(S[i].x<S[j].y&&S[i].y<S[j].x)))
				{
					G[i][j]=1;
				}
			}
		}
		for(int i=1;i<=tot;i++)
		{
			for(int j=0;j<3;j++)
			maxn=max(maxn,dp(i,j));
		}
		printf("%d\n",maxn);
	}
	return 0;
}
```



---

## 作者：ztxtjz (赞：1)

算法： $Floyd$ 求最~~短~~长路

## 【思路】
设三边长为 $a,b,c$ ，则每个方块有六种状态：

①长 $a$ ，宽 $b$ ，高 $c$

②长 $b$ ，宽 $a$ ，高 $c$

③长 $a$ ，宽 $c$ ，高 $b$

④长 $c$ ，宽 $a$ ，高 $b$

⑤长 $b$ ，宽 $c$ ，高 $a$

⑥长 $c$ ，宽 $b$ ，高 $a$

于是我们这样建图：

```cpp
struct node
{
	ll x,y,h;
}q[200];
void add(ll a,ll b,ll c)
{
	cnt++;
	q[cnt].x=a,q[cnt].y=b,q[cnt].h=c;
}
add(1e12,1e12,0); 
for(int i=1;i<=n;i++)
{
	ll a=read(),b=read(),c=read();
	add(max(a,b),min(a,b),c);
	add(max(a,c),min(a,c),b);
	add(max(b,c),min(b,c),a);
}
```
因为方块放在地上，而地面是无穷大，可以认为地面是长、宽极大，高为 $0$ 的方块。

这样建图每次可以少建三条边 ~~不然Floyd可能TLE~~
```cpp
bool cal(int i,int j)
{
	return (q[i].x>q[j].x&&q[i].y>q[j].y||q[i].x>q[j].y&&q[i].y>q[j].x);
}
for(int i=1;i<=cnt;i++)
	for(int j=1;j<=cnt;j++)
		if(cal(i,j))
			f[i][j]=q[j].h,ans=max(ans,f[i][j]);
```
$cal$ 用于比较前一个方块是否能放在后一个方块的下面，若能，则边长为后一个方块的高度。

$ans$ 不断取最大值，不过这里必要取，顺手写上了。~~以防万一~~

然后就可以跑 $Floyd$ 了。
```cpp
for(int k=1;k<=cnt;k++)
	for(int i=1;i<=cnt;i++)
		for(int j=1;j<=cnt;j++)
			if(f[i][k]&&f[k][j]&&f[i][j]<f[i][k]+f[k][j])
				f[i][j]=f[i][k]+f[k][j],ans=max(ans,f[i][j]);
```
找转折点 $k$ 的时候要注意判断 $k$ 能放在 $i$ 的上面且 $j$ 能放在 $k$ 的上面。最长路其实就是把 $min$ 换成了 $max$ 。

## 【代码】
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,t,cnt,f[181][181],ans;
ll read()
{
    ll x=0;char ch=getchar();
    while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x;
}
struct node
{
	ll x,y,h;
}q[200];
void add(ll a,ll b,ll c)
{
	cnt++;
	q[cnt].x=a,q[cnt].y=b,q[cnt].h=c;
}
bool cal(int i,int j)
{
	return (q[i].x>q[j].x&&q[i].y>q[j].y||q[i].x>q[j].y&&q[i].y>q[j].x);
}
int main()
{
	while(n=read())
	{
		cnt=ans=0;
		memset(f,0,sizeof(f));
		add(1e12,1e12,0); 
		for(int i=1;i<=n;i++)
		{
			ll a=read(),b=read(),c=read();
			add(max(a,b),min(a,b),c);
			add(max(a,c),min(a,c),b);
			add(max(b,c),min(b,c),a);
		}
		for(int i=1;i<=cnt;i++)
			for(int j=1;j<=cnt;j++)
				if(cal(i,j))
					f[i][j]=q[j].h,ans=max(ans,f[i][j]);
		for(int k=1;k<=cnt;k++)
			for(int i=1;i<=cnt;i++)
				for(int j=1;j<=cnt;j++)
					if(f[i][k]&&f[k][j]&&f[i][j]<f[i][k]+f[k][j])
						f[i][j]=f[i][k]+f[k][j],ans=max(ans,f[i][j]);
		printf("Case %lld: maximum height = %lld\n",++t,ans);
	}
	return 0;
}
```


---

## 作者：LLLLLLEMON (赞：1)

依据紫书上面的DAG想法 加上 各位大佬的神奇想法 
我采用了 记忆化搜索的DAG DP  
好处是不用排序 直接搜索 时间复杂度O（n*2）


首先我们可以想到 将一个长方体 按长宽高的任意定顺序进行存储 共有6*n种情况  然后就暴力DAG 就行了

f[i]表示 以i为顶块的当前状态的最大高度
下面是markdown
```
//
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define maxnn 500
int n;
int c[maxnn],k[maxnn],g[maxnn],tot=0,kk=0;
int f[maxnn];
int dfs(int t)
{
	int& ans=f[t];

	if(ans>0) return ans;	
	ans=g[t];
	for(int i=1;i<=6*n;i++)
	{
		if(c[i]>c[t]&&k[i]>k[t])
		{
			ans=max(ans,dfs(i)+g[t]);
		}
		
	} 
	
	return ans;
	
	
}
void add(int a,int b,int cc)
{
	c[++tot]=a;
	k[tot]=b;
	g[tot]=cc;
}
int main()
{
	int ans=0;
	int x,y,z;
	while(1)
	{   
	    tot=0;
	    memset(f,0,sizeof(f));
	     
	    ans=0;
		cin>>n;
		if(n==0)
		{
		    return 0;	
		}
		for(int i=1;i<=n;i++)
		{
			cin>>x>>y>>z;
			add(x,y,z);
			add(x,z,y);
			add(y,x,z);
			add(y,z,x);
			add(z,x,y);
			add(z,y,x);
		}
		for(int i=1;i<=6*n;i++)
		ans=max(ans,dfs(i));
		cout<<"Case "<<++kk<<": maximum height = "<<ans<<endl;
	}
	
	
	
	
}
```

---

## 作者：StephenC (赞：1)

# 动态规划
## 第一步先明确状态，一共有n个立方体，3*n个不同的面（3*n个状态），那么就储存下来
```cpp
ufor(i, 1, n)
		{
			int e[3];
			cin >> e[0] >> e[1] >> e[2];
			sort(e, e+3);
			fac[++cnt][0] = e[0]; fac[cnt][1] = e[1]; fac[cnt][2] = e[2];
			fac[++cnt][0] = e[0]; fac[cnt][1] = e[2]; fac[cnt][2] = e[1];
			fac[++cnt][0] = e[1]; fac[cnt][1] = e[2]; fac[cnt][2] = e[0];//chang kuan gao
		}
```
## 第二步找出动态转移方程。要么从一个最小面往下找，要么从一个最大面往上找。
### 最小面往下找：
#### 先将面排序
```cpp
inline void fac_sort()
{
	int t1, t2, t3;
	ufor(i, 1, cnt)
		ufor(j, i+1, cnt)
		{
			if((fac[j][0]<fac[i][0]&&fac[j][1]<fac[i][1]) || (fac[j][1]<fac[i][0]&&fac[j][0]<fac[i][1]))
			{
				t1 = fac[j][0]; t2 = fac[j][1]; t3 = fac[j][2];
				fac[j][0] = fac[i][0]; fac[j][1] = fac[i][1]; fac[j][2] = fac[i][2];
				fac[i][0] = t1; fac[i][1] = t2; fac[i][2] = t3;
			}
		}
}
```
#### 动态转移方程：dp[i] = fac[i][2] +　max{dp[k]|k∈[1,i)}
对于第i个面，可在这个面上加上之前的i-1个面里满足条件的最高状态的那个面。注意答案是最大的高度而不是最后一个高度。
```cpp
ufor(i, 1, cnt)
		{
			ufor(j, 1, i-1)
				if((fac[j][0]<fac[i][0]&&fac[j][1]<fac[i][1]) || (fac[j][1]<fac[i][0]&&fac[j][0]<fac[i][1]))
					dp[i] = max(dp[i], dp[j]);
			dp[i] += fac[i][2];
			ans = max(ans, dp[i]);
		}
```
### 最大面往上找的推导过程如上。


	

---

## 作者：Maktub (赞：0)

动态规划的一个很重要的思想就是把问题转化成DAG图，然后跑最长（短）路。

这个DAG，用状态做为节点，用转移条件作为边。

这个思想可以解决很多动态规划的题，或者可以用这个思想去打动态规划题的暴力。（比如乌龟棋，用这个思想拓展状态跑图可以拿50分）

简单的状态压缩DP就是运用这种思想，先处理出所有节点，然后再跑图。

这个题用这样的思路想是很简单的。将木块作为节点，如果符合题目条件就可以连边，然后跑DAG最长路就好了。

注意：每种木块可以有6种姿态。。不是3个（卡了好久）

更详细的注释见代码：

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<queue>
#include<vector>
#include<set>
using namespace std;
#define ll long long
struct node{
	int a, b, c;
} block[222];
int h[222];

vector<int>G[222];//用vector存图比较方便，而且数据规模小的情况影响不大 

int de[222];
int st[222];//不习惯用stl的stack 

int main(){
    int n,kase = 0;
    while(scanf("%d", &n) == 1 && n){
    	
    	for(int i = 1; i<= 180; i++)G[i].clear();//必须初始化的东西，栈没有必要。 
    	memset(de,0,sizeof(de));
    	memset(h,0,sizeof(h));
    	
    	for(int i = 1; i <= n; i++){//扩展所有状态，其实找到规律很好写 
    		scanf("%d%d%d", &block[i].a, &block[i].b, &block[i].c);
    		block[i+n].c = block[i].a; block[i+n].a = block[i].b; block[i+n].b = block[i].c;
    		block[i+2*n].c = block[i].a; block[i+2*n].a = block[i].c; block[i+2*n].b = block[i].b;
    		block[i+3*n].c = block[i].c; block[i+3*n].a = block[i].b; block[i+3*n].b = block[i].a;
    		block[i+4*n].c = block[i].b; block[i+4*n].a = block[i].a; block[i+4*n].b = block[i].c;
    		block[i+5*n].c = block[i].b; block[i+5*n].a = block[i].c; block[i+5*n].b = block[i].a;
		}
		n *= 6;//将n扩展 
		
	//	cout<<endl;
	//	for(int i = 1; i <= n; i++)printf("%d %d %d\n",block[i].a, block[i].b, block[i].c);
		//sort(block + 1,block + n + 1,cmp);
		//for(int i = 1; i <= n; i++)printf("%d %d %d\n",block[i].a, block[i].b ,block[i].c);
		//一开始想用sort。。发现自己太菜了不会写cmp 
		
		for(int i = 1;i <= n; i++){//建图，可能有方法不用建图进行拓扑排序，但是我不会。这样做思路清晰。 
			for(int j = 1;j <= n; j ++){
				if(i == j || block[i].a <= block[j].a || block[i].b <= block[j].b)continue;
				//if(block[i].a == block[j].a && block[i].b == block[j].b)continue;
				G[i].push_back(j);
				de[j]++;
			}
		}
		
	
		int top = 0;
		for(int i = 1;i <= n; i++)if(!de[i])st[++top] = i,h[i] = block[i].c;//为拓扑排序+DP做准备 
		
	//	cout << top << endl;
	//	for(int i = 1;i <= top; i++)cout << h[st[i]] << ' ';
	//	cout << endl;
	
		
		while(top){//进行拓扑排序+DP求最长路 
			int u = st[top--];
		//	cout<< u << ' ';
			for(int i = 0;i < G[u].size(); i++){
				int v = G[u][i];
				h[v] = max(h[v], h[u] + block[v].c);
				de[v]--;
				if(!de[v])st[++top] = v;
			}
		}
	//	for(int i = 1; i <= n; i++)cout<<h[i]<<' ';cout<<endl;
		int ans = 0;
		for(int i = 1; i <= n; i++)ans = max(ans, h[i]);
		printf("Case %d: maximum height = %d\n", ++kase, ans);//找最大值并输出 
	}
	return 0;//结束 
}


```

这个方法建图的时候耗费时间最多。求最长路还可以用记忆化搜索。但是我还是比较喜欢拓扑+DP。记忆中记忆化搜索好像也是建图比较方便。

因为是新学DP，希望能对同样新学DP的同学有所帮助。

---

## 作者：璀璨丶凋零 (赞：0)

- 题意：现在有n种长方体，每种都有无穷多个，现在选择一些立方体摞成一根尽量高的柱子（对于每一个立方体来说可以选择任一条边作为高），要求上方的立方体的底面长宽严格小于它下方立方体的底面长宽。
**
- 思路：在任何时候，只有顶面的尺寸会影响到后续决策，因此可以用二元组(a,b)来表示“顶面尺寸为a×b”这个状态。因为每次增加一个立方体以后顶面的长和宽都会严格减小，所以这个图是DAG，可以套用前面学过的DAG最长路算法。

  可以用(idx, k)这个二元组来“间接”表达这个状态，其中idx为顶面立方体的序号，k是高的序号（输入时把每个立方体的3个维度编号为0～2）。例如，若立方体3的大小为a*b*c，则状态(3,1)就是指顶面为a×c或c×a且高是b。因为idx是0～n－1的整数，k是0～2的整数，所以可以很方便地用二维数组来存取。状态总数是O(3×n)的，每个状态的决策有O(n)个，时间复杂度为 O(n^2)

 - 与 P1034 矩形覆盖 类似用记忆化搜索做（只不过把一个平面改成了长方体，也就是三个平面）
 
 上代码
 ```pascal
var
x,y,z,f:array[1..90]of longint;
n,i,s,tx,ty,tz,temp:longint;
function min(x,y:longint):longint;
 begin
 if x<y then
 exit(x)
 else
 exit(y);
 end;
function max(x,y:longint):longint;
 begin
 if x>y then
 exit(x)
 else
 exit(y);
 end;
function dfs(t:longint):longint;  //开始搜索
 var
 i:longint;
 begin
 if f[t]>0 then
 exit(f[t]);
 f[t]:=z[t];
 for i:=1 to n*3 do
  if (x[t]<x[i]) and (y[t]<y[i]) then //能搭上去则继续搜索
  f[t]:=max(f[t],dfs(i)+z[t]);
 exit(f[t]);
 end;
begin
temp:=0;
while true do
begin
inc(temp);
read(n);
 if n=0 then
 halt;
 for i:=1 to n do
 begin
 read(tx,ty,tz);
 x[i*3-2]:=max(tx,ty);  //就把一个立方体转化成了三个平面
 y[i*3-2]:=min(tx,ty);
 z[i*3-2]:=tz;
 x[i*3-1]:=max(tx,tz);
 y[i*3-1]:=min(tx,tz);
 z[i*3-1]:=ty;
 x[i*3]:=max(ty,tz);
 y[i*3]:=min(ty,tz);
 z[i*3]:=tx;
 end;
fillchar(f,sizeof(f),0);  //每做完一次一定要注意初始化
s:=0;
 for i:=1 to n*3 do
 s:=max(s,dfs(i));
writeln('Case ',temp,': maximum height = ',s);  //注意‘Case ’后面有个很恶心的空格，‘: maximum height = ’冒号后面，等号前后也有空格
end;
end.
```

---

