# Byteland, Berland and Disputed Cities

## 题目描述

比特兰（Byteland）和伯兰（Berland）的城市位于坐标轴 $Ox$ 上。此外，这条轴上还存在一些争议城市，两国都认为这些城市属于自己。因此，$Ox$ 轴上的城市分为三种类型：

- 比特兰的城市，
- 伯兰的城市，
- 争议城市。


最近，新一代计算机网络项目 BNET 正式启动。现在两国的任务是连接这些城市，使得各自国家的网络连通。

两国达成协议，通过铺设 BNET 电缆连接城市对，需满足以下条件：

- 如果仅考虑比特兰的城市和争议城市，那么在这些城市中，任意两个城市之间都可以通过一条或多条电缆相互到达；
- 如果仅考虑伯兰的城市和争议城市，那么在这些城市中，任意两个城市之间都可以通过一条或多条电缆相互到达。

因此，需要选择一个城市对集合来铺设电缆，使得上述两个条件同时满足。电缆支持双向数据传输，每条电缆连接两个不同的城市。

铺设一条连接两个城市的电缆的成本等于它们之间的距离。请找到满足条件的最小总成本。

每个城市是 $Ox$ 轴上的一个点。技术上允许连接城市 $a$ 和 $b$ 时，即使位于它们之间的城市 $c$（$a < c < b$）未被该电缆直接连接（$a$、$b$ 和 $c$ 同时表示城市的坐标）。

## 说明/提示

样例 $1$ 说明：  
应连接第一座城市与第二座（长度 $5$）、第二座与第三座（长度 $3$）、第三座与第四座（长度 $4$），总成本为 $5 + 3 + 4 = 12$。

样例 $2$ 说明：  
没有争议城市，因此需要连接所有相邻的比特兰城市和所有相邻的伯兰城市。  
- 伯兰城市坐标为 $10, 21, 32$，需铺设两条电缆（长度 $11$ 和 $11$）；  
- 比特兰城市坐标为 $ 14 $ 和 $ 16 $，需铺设一条电缆（长度 $2$）。  

总成本为 $11 + 11 + 2 = 24$。

## 样例 #1

### 输入

```
4
-5 R
0 P
3 P
7 B
```

### 输出

```
12
```

## 样例 #2

### 输入

```
5
10 R
14 B
16 B
21 R
32 R
```

### 输出

```
24
```

# 题解

## 作者：HD0X (赞：7)

鲜花：2200的紫？

# CF962E

### 题意

数轴上有三种点 PBR ，要求连边使得所有 BP 联通和所有 RP 联通， RB 间不能连边。问最小花费（边权为两点间的距离）。 $n≤2e5$

### 思路

首先第一个 P 前和最后一个 P 后正常连接，然后考虑如下两种排列。

#### PP 型（紧密连接）

这种情况下，必连多个 P 。注意不要重复计数。

#### P--P 型

第一反应是~~不考虑~~连两 P ，再在中间找最大的间隙，其它的依次连接至 P 点，这样另一种字符可以直接越过（中间只有一种字符）或一起使用（两种字符），可以省下空隙之和 $-$ 两 P 距离。注意 RB 分开讨论，如图：

~~手残轻喷~~

![RT](https://cdn.luogu.com.cn/upload/image_hosting/ni06jy59.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果 R 和 B 省下的花费多于两 P 之间的距离，才合法可用。

如图，可以省下 $R_1R_2$ $+$ $P_1B$ $-$ $P_1P_2$ 。

### CODE

别忘了开 long long 。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+10;
int n,a[MAXN],mn1=INT_MAX,mn2=INT_MAX,mx1=-INT_MAX,mx2=-INT_MAX,t[MAXN],ans,pr;
char s[MAXN];
int vis[MAXN];
inline int read()
{
	int x=0,p=1;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if (ch=='-') p=-1;
		ch=getchar();}
	while('0'<=ch&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();}
	return x*p;
}
void make(char c,bool f)
{
	int sum=0,lst=0;
	for(int i=1;i<=n;i++)
	{
		if(s[i]==c) t[++sum]=i;
		else if(s[i]=='P')
		{
			if(lst!=0 && (i!=lst+1||i==lst+1&&!vis[lst]))
			{
				int y=0;
				t[++sum]=i;
				for(int j=0;j<sum;j++) y=max(y,a[t[j+1]]-a[t[j]]);
				if(1==i-lst) pr+=y;
				if(!f) vis[lst]=y;
				if(f && vis[lst]!=0 && vis[lst]+y>a[i]-a[lst]) pr+=vis[lst]+y-a[i]+a[lst];
			}
			lst=i;
			sum=0;
			t[0]=lst;
		}
	}
}
signed main()
{
	n=read();
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		a[i]=read(),s[i]=getchar();
		if(s[i]=='P')
		{
			mn1=min(mn1,a[i]);
			mn2=min(mn2,a[i]);
			mx1=max(mx1,a[i]);
			mx2=max(mx2,a[i]);
			++cnt;
		}
		else if(s[i]=='B')
		{
			mn1=min(mn1,a[i]);
			mx1=max(mx1,a[i]);
		}
		else
		{
			mn2=min(mn2,a[i]);
			mx2=max(mx2,a[i]);
		}
	}
	if(mn1==INT_MAX) mn1=mx1;
	if(mn2==INT_MAX) mn2=mx2;
	if(cnt<=1)
	{
		cout<<mx1-mn1+mx2-mn2<<endl;
		return 0;
	}
	make('R',0),make('B',1);
	int cha=max(0ll,pr);
	ans=mx1+mx2-mn1-mn2;
	cout<<ans-cha<<endl;
}
```

---

## 作者：QianianXY (赞：4)

[传送门](https://www.luogu.com.cn/problem/CF962E)
## 题目分析

一道有质量的构造题。

一种错误的做法是，直接将相邻的 $P,B$，$P,R$ 相连。

但其实两个 $P$ 之间的边是可以共用的，就出现了多种连边方案。

以下讨论 $P,R$ 的情况，因为 $P,B$ 同理。

对于最左端的 $P$ 左边的 $R$ 点，直接与该 $P$ 点相连，没有其它方案。对于最右端的 $P$ 点右边的 $R$ 点同理。

接下来对于两个相邻的 $P$ 点以及它们之间的 $R$ 点，有两种连法。

一是与错误解法相同，直接连相邻的 $P,R$ 点即可，代价等于这两个 $P$ 点的距离。

二是先连两个 $P$ 点，然后将其间相邻的 $R$ 点连接为两个连通块，分别接到两个 $P$ 点上。$R$ 点的两个连通块在距离最长的两个 $R$ 点间分割。

如图，紫色的是 $P$ 点，绿色的是 $R$ 点。

![](https://cdn.luogu.com.cn/upload/image_hosting/kx4tyhea.png)

每对相邻的 $P$ 点都可看作一个独立的小块计算代价并选择最优的方案，最后考虑 $P,B$ 即可。

---

## 作者：大菜鸡fks (赞：4)

画画图可以发现 无非两种决策：

1. PB依次连边（PR同理）
2.相邻两个P之间先连边（作为B和R 与P连通图的公用边）

然后相邻P之间的B和R单独连边（注意中间一条最大边可以去掉）

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll ans,n,i,R,d,c,f,v,g,B,P;
int main(){
	scanf("%I64d",&n);
	for (int i=1;i<=n;i++){
		ll m; char s;
		scanf("%I64d %c",&m,&s);
		if (s=='P'||s=='R'){
			if (R) ans+=m-d,c=max(c,m-d);
			R=1; d=m;
		}
		if (s=='P'||s=='B'){
			if (B) ans+=m-f,v=max(v,m-f);
			B=1; f=m;
		}
		if (s=='P'){
			if (P) ans+=min(0ll,m-g-v-c);
			P=1; c=v=0; g=m; 
		}
	}
	printf("%I64d\n",ans);
	return 0;
}
```

---

## 作者：蒋辰逸 (赞：1)

非常简单的贪心，~~但是是紫题~~。

我们先抛开 ```P```，发现最终的答案就是所有相邻的 ```B``` 和所有相邻的 ```R``` 之间的距离之和。实际上就是：$b_{lst}-b_1+r_{lst}-r_1$。这里的 $b_{lst}$ 和 $r_{lst}$ 指最后一个 ```B``` 和 ```R``` 的位置。

现在，再加上 ```P```，实际上，```P``` 就是 ```B``` 和 ```R``` 同时都需要考虑的城市，我们在上一步计算长度时在两个国家的城市中都应加上 ```P```。

但 ```P``` 的出现会带来重边，例如：
```
BPRPB
```
在这个情况中，在算 ```B``` 时会有 1 - 2，2 - 4，4 - 5 三个边，而在算 ```R``` 时会有 2 - 3，3 - 4 两个边。但实际上，如果去掉 3 - 4 这一条边，3、4 仍然可以通过 2 - 3，2 - 4 两条边联通，可以删去。

所以，在实际操作中，我们应遵循以下原则：

- 对于形如 ```P***P``` （```*``` 代表任意数量的 ```B``` 和 ```R```）的区间，对于 ```B``` 和 ```R```，分别可以删去一条边（为使答案最小，应删去最大的边）。
- 最终答案加上 $b_{lst}-b_1+r_{lst}-r_1$。

### AC CODE：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a[200010];
char c[200010];
int lstb,lstr,lstp,fstb,fstr;//lst表示上一个（扫完时就是最后一个），fst表示第一个 
int maxb,maxr;
bool isp,isb,isr;
int ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>c[i];
		if(c[i]=='B'){
			if(isb)maxb=max(maxb,a[i]-lstb);//实时更新max 
			else isb=1,fstb=a[i];//如果是第一个B，记录位置 
			lstb=a[i];//更新上一个B 
		}
		if(c[i]=='R'){//同理 
			if(isr)maxr=max(maxr,a[i]-lstr);
			else isr=1,fstr=a[i];
			lstr=a[i];
		}
		if(c[i]=='P'){
			//P同样要做B和R的处理 
			if(isb)maxb=max(maxb,a[i]-lstb);
			else isb=1,fstb=a[i];
			lstb=a[i];
			if(isr)maxr=max(maxr,a[i]-lstr);
			else isr=1,fstr=a[i];
			lstr=a[i];
			//删去其中的最大边 
			if(isp&&a[i]-lstp-maxb-maxr<0)ans+=a[i]-lstp-maxb-maxr;
			maxb=maxr=0;
			lstp=a[i];
			isp=1;
		}
	}
	ans+=lstb-fstb+lstr-fstr;//加上B和R的答案 
	return cout<<ans,0;
} 
```

---

## 作者：Ryanhao (赞：1)

### [CF962E Byteland, Berland and Disputed Cities(比特兰，博尔兰和争议城市)](https://www.luogu.com.cn/problem/CF962E)
# 思路

不好说，有点大模拟，有点贪心，反正挺水紫的。

首先，我们可以把那些城市按照 `P` 来划分成若干段。

对于头尾那两段：我们可以将城市在各自的国家用国家道路连接，再把最靠近 `P` 的城市都和 `P` 连接。

![](https://cdn.luogu.com.cn/upload/image_hosting/d8j0doz6.png)

对于中间的段，分三种情况：

1. 没城市
2. 只有一个国家的城市
3. 两个国家的城市都有。

对于 1.，我们把两边的 `P` 连上即可。

对于 2.，我们要将两边的 `P` 用一条路连上，然后中间的城市挨个连上。于是发现我们可以利用一下刚才那条长路：
![](https://cdn.luogu.com.cn/upload/image_hosting/cdci652g.png)

看见了吧，把在中间的路**选一条最长的，炸了它**，又可以省一笔钱。（司机：……）

对于 3. 看图：![](https://cdn.luogu.com.cn/upload/image_hosting/ir2ywzr2.png)

首先，两个 `P` 相连。

对于上面的方案，每个国家各自修建道路；对于下面的方案，也能利用一下下连着两个 `P` 的道路。又省一笔钱。两个方案取成本最小。

然后算修的路的总长度即可。

说说修路长度：

对于两头那两段，直接硬算即可。

对于中间那几段，我们发现，挨个连过去其实总长度还是两个 `P` 的距离。

那么记两个 `P` 的距离为 $S$,记两点间的距离为 $\text{dis}(i,j)$，记第 $i$ 个点的国家为 $\text{con}(i)$:

第一种情况：$S$

第二种情况：$2S-\max\limits_{i=P_1+1}^{P_2}\text{dis}(i-1,i)$

第三种情况：$\min\{2S,3S-\max\limits_{i=P_1+1,\text{con}(i)=R}^{P_2}\text{dis}((j,\text{con}(j)=R,j < i),i)-\max\limits_{i=P_1+1,\text{con}(i)=B}^{P_2}\text{dis}((j,\text{con}(j)=B,j < i),i)\}$

然后直接算即可。时间复杂度 $O(n)$

# ACCode
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

struct node {
  int x;
  char op;
}a[214514];

int pid[214514];

int __30pts(int s, int e) { // 头尾两段：分别连
  int b1 = -1,b2 = -1,r1 = -1,r2 = -1;
  for (int i = s; i <= e; i++) {
    if (a[i].op == 'B') {
      if (b1 == -1) b1 = i;
      b2 = i;
    }
    if (a[i].op == 'R') {
      if (r1 == -1) r1 = i;
      r2 = i;
    }
  }
  return (a[b2].x-a[b1].x)+(a[r2].x-a[r1].x);
}

int32_t main() {
  freopen("connect.in","r",stdin);
  freopen("connect.out","w",stdout);
  int n,pc = 0;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].x >> a[i].op;
    if (a[i].op == 'P') pid[++pc] = i;
  }
  // 求两头的段 
  int ans = __30pts(1,pid[1]-1) + __30pts(pid[pc]+1,n);
  if (pc > 0) { // 连上 P
    int lpr = pid[1], lpb = pid[1];
    for (int j = pid[1]-1; j >= 1; j--) {
      if (a[j].op == 'R') {
        lpr = j;
        break;
      }
    }
    for (int j = pid[1]-1; j >= 1; j--) {
      if (a[j].op == 'B') {
        lpb = j;
        break;
      }
    }
    int rpr = pid[pc], rpb = pid[pc];
    for (int j = pid[pc]+1; j <= n; j++) {
      if (a[j].op == 'R') {
        rpr = j;
        break;
      }
    }
    for (int j = pid[pc]+1; j <= n; j++) {
      if (a[j].op == 'B') {
        rpb = j;
        break;
      }
    }
    //求各自最靠近P的城市，连上。
    ans += (a[pid[1]].x-a[lpr].x)+(a[pid[1]].x-a[lpb].x)+(a[rpr].x-a[pid[pc]].x)+(a[rpb].x-a[pid[pc]].x);
  } 
  for (int i = 2; i <= pc; i++) {
    if (pid[i]-pid[i-1] == 1) { // 1. 
      ans += a[pid[i]].x-a[pid[i-1]].x;
      continue;
    }
    int rc = 0, bc = 0;
    for (int j = pid[i-1]+1; j < pid[i]; j++) {
      if (a[j].op == 'R') rc++; 
      if (a[j].op == 'B') bc++;
    }
    if (rc == 0 || bc == 0) { // 2.
      int bggp = -1;
      for (int j = pid[i-1]+1; j <= pid[i]; j++) {
        bggp = max(bggp,a[j].x-a[j-1].x);
      }
      ans += 2*(a[pid[i]].x-a[pid[i-1]].x)-bggp;
    } else { // 3.
      int ans1 = 2*(a[pid[i]].x-a[pid[i-1]].x); // 方案1 
      int gpr = -1,gpb = -1;
      int lstr = pid[i-1], lstb = pid[i-1];
      for (int j = pid[i-1]+1; j <= pid[i]; j++) { // 求各自最大区间
        if (a[j].op == 'R') {
          gpr = max(gpr,a[j].x-a[lstr].x);
          lstr = j;
        }
        if (a[j].op == 'B') {
          gpb = max(gpb,a[j].x-a[lstb].x);
          lstb = j;
        }
        if (a[j].op == 'P') {
          gpr = max(gpr,a[j].x-a[lstr].x);
          gpb = max(gpb,a[j].x-a[lstb].x);
          lstr = lstb = j;
        }
      }
      int ans2 = 3*(a[pid[i]].x-a[pid[i-1]].x)-gpr-gpb; // 方案2 
      ans += min(ans1,ans2);
    }
  }
  cout << ans;
  return 0;
}
```

# 后记

这道题又双叒叕被拿来当校内比赛题了，当时是 T3, 但赛后觉得，放在 T2 更合适，思路还挺简单，没有太多太复杂的算法，纯纯的模拟。所以大家不要被各种难度标识迷惑了双眼（比如题目后面那个红色/橙色/黄色/绿色/蓝色/紫色/深蓝色/灰色的牌子），先看题，找到思路了一切都简单了。
## update

OCT18：发现并修复一个较为致命的错误。

---

## 作者：封禁用户 (赞：0)

# Problem
对一条直线上的点连边，使得只有红点和绿点的子图联通且只有蓝点和绿点的子图联通。
# Solution
由于端点均为绿点的边（以下称之为“绿边”）在两个子图中均存在，所以我们考虑这种边。  
可以证明绿边一定只会连相邻两个绿点，所以我们对相邻的两个绿点进行分类讨论。

## 1.绿边相连
我们要保证这两个绿点之间的所有红、蓝点分别连通，便有以下方法：
>将相邻红、蓝点分别连边，删掉最长一条边，如下图。
>![](https://cdn.luogu.com.cn/upload/image_hosting/4uinjglz.png)

我们可以用 st 表来维护区间最值。  

代价为三倍绿边长度减去最长的红、蓝边。
## 2.绿边不连
我们需要保证两个绿点连通，所以不能删掉最长边。

代价为两倍绿边长度。

**注意，我们这样只算了绿边之间的代价，还要加上最左边的绿点的左侧与最右边的绿点右侧的代价。**
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5,LG=20;
int n,n1,n2,n3,a[N+5],b[N+5],mp1[N+5],mp2[N+5],lg[N+5],st1[N+5][LG+5],st2[N+5][LG+5];
int query1(int l,int r){
	int len=lg[r-l];
	return max(st1[l][len],st1[r-(1<<len)][len]);
}
int query2(int l,int r){
	int len=lg[r-l];
	return max(st2[l][len],st2[r-(1<<len)][len]);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		char opt;
		cin>>x>>opt;
		if(opt=='B')a[++n1]=x;
		if(opt=='R')b[++n2]=x;
		if(opt=='P')a[++n1]=x,b[++n2]=x,n3++,mp1[n3]=n1,mp2[n3]=n2;
	}
	if(!n3){
		cout<<a[n1]-a[1]+b[n2]-b[1];
		return 0;
	}
	for(int i=1;i<n1;i++)st1[i][0]=a[i+1]-a[i];
	for(int i=1;1+(1<<i)<=n1;i++)for(int j=1;j+(1<<i)<=n1;j++)st1[j][i]=max(st1[j][i-1],st1[j+(1<<(i-1))][i-1]);
	for(int i=1;i<n2;i++)st2[i][0]=b[i+1]-b[i];
	for(int i=1;1+(1<<i)<=n2;i++)for(int j=1;j+(1<<i)<=n2;j++)st2[j][i]=max(st2[j][i-1],st2[j+(1<<(i-1))][i-1]);
	for(int i=2;i<=max(n1,n2);i++)lg[i]=lg[i>>1]+1;
	int ans=a[mp1[1]]-a[1]+b[mp2[1]]-b[1]+a[n1]-a[mp1[n3]]+b[n2]-b[mp2[n3]];
	for(int i=2;i<=n3;i++){
		int ans1=3*(a[mp1[i]]-a[mp1[i-1]]),ans2=2*(a[mp1[i]]-a[mp1[i-1]]);
		if(mp1[i]-mp1[i-1]>1)ans1-=query1(mp1[i-1],mp1[i]);
		else ans1-=a[mp1[i]]-a[mp1[i-1]];
		if(mp2[i]-mp2[i-1]>1)ans1-=query2(mp2[i-1],mp2[i]);
		else ans1-=a[mp1[i]]-a[mp1[i-1]];
		ans+=min(ans1,ans2);
	}
	cout<<ans;
}
```

---

