# Never·island

## 题目背景

您一觉醒来，发现已经到了20000年后的未来。

## 题目描述

为了寻找传说中的Avalon，island派出了 $n$ 个考察队。为了保持island的稳定，island有一个通向外界的大门。

这 $n$ 个考察队都需要出一次门进行考察，其中第 $i$ 支考察队会在 $l_i$ 时刻离开，并且在第 $r_i$ 时刻回来。我们保证这些值都是互不相等的。

每当一支考察队离开时，island的大门会变成开的。但是如果这支考察队得到了钥匙，那么他就可以决定关门或者不关门。同时每一个考察队回来的时候要么门本来就是开的（由于island是已知唯一的生活区，因此island内部人员不会主动为任何人开门），要么他必须拥有一把钥匙把门打开。注意，回来的时候无论有没有钥匙，那么这支考察队都可以选择把门关上。

由于一些奇怪的原因，island的设计者只设计了 $k$ 把钥匙，只能分给 $k$ 支考察队。得到钥匙证明了island上层对考察队的信任，因此考察队不会把钥匙交给任何人。

为了防止island下层居民逃出island，上层希望门处于开的时间越短越好。希望您帮他算出最短门会开多久。

## 说明/提示

【样例解释】
``` 
④                     ================
③/⑤       -------                              ------
②      -------------------------
①   ========================= 
    1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17
状态 X  O  O  O  X  X  X  X  O  X  X  X  X  X  O  O 
```
其中，1、4号考察队会带钥匙。

【数据范围】

对于 $30\%$ 的测试数据，$n \leq 20$

对于 $60\%$的测试数据，$n \leq 200$

对于全部的测试数据，$n \leq 2000$

$1 \leq l_i < r_i\leq 10^9, k \le n$

## 样例 #1

### 输入

```
5 2
1 9
2 10
3 5
7 12
15 17
```

### 输出

```
6
```

# 题解

## 作者：waaadreamer (赞：19)

月赛的时候有事没考……后来才看到这题出的超棒！手动膜zcy……

刚开始以为是一个网络流模型，然后建模建了十几分钟没成功……后来猛然间想到离散化之后分类讨论线段端点似乎可行。

考虑到我们只需要求出关门的最长时间即可。于是可以给每个考察队建一个带权点，然后进行如下操作：

1.一个线段左边为起点，右边为终点。如果这两个点同属于一个考察队，那么就给该点权加上当前线段长度，表示如果给该考察队钥匙可以获得的贡献；否则就在分属的两个考察队之间连一条权值为线段长度的边，表示如果给这两个考察队钥匙可以获得的贡献。

2.一个线段左边和右边都是起点，则给左边的考察队点权加上线段长度，原因同上；

3.一个线段左边和右边都是终点，则给右边的考察队点权加上线段长度；

4.一个线段左边是终点，右边是起点，则必然给答案造成贡献，直接给答案加上贡献即可。

接下来我想着这个图懵了一会儿，怎么求解从中选k个点使得诱导子图的权值和最大？刚开始想着这个图是个二分图，可以怎么做；后来猛然发现这个图实际上是由很多链组成的……

于是就很显然了，对于每条链都dp一下，dp[i][j][0/1]就表示当前dp到了前i个点，选j个点，当前点是否选择的最大值，这个dp是很easy的，于是问题就在O(n^2)的时间内解决了。

再次膜出题人Orz……/菜鸡的我刚开始连dp的初始值都没赋2333

``````cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2005;
map<int, int> mp;
int srt[maxn * 2], f[maxn][maxn][2], val[maxn], ss[maxn];
int vis[maxn], nxt[maxn], ord[maxn], tot, n, m;
void dfs(int u){
	vis[ord[++tot] = u] = 1;
	if(nxt[u]) dfs(nxt[u]);
}
int main(){
	freopen("input.txt", "r", stdin);
	freopen("out1.txt", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++){
		int l, r;
		scanf("%d%d", &l, &r);
		mp[l] = i * 2;
		mp[r] = i * 2 + 1;
		srt[i] = l;
		srt[i + n] = r;
	}
	sort(srt + 1, srt + n + n + 1);
	int res = 0;
	for(int i = 1; i < n + n; i++){
		int l = srt[i], r = srt[i + 1];
		int ld = mp[l], rd = mp[r];
		if((ld & 1) && !(rd & 1)) res += r - l;
		if((ld & 1) && (rd & 1)) val[rd >> 1] += r - l;
		if(!(ld & 1) && !(rd & 1)) val[ld >> 1] += r - l;
		if(!(ld & 1) && (rd & 1)){
			if((ld >> 1) == (rd >> 1)) val[ld >> 1] += r - l;
			else nxt[rd >> 1] = ld >> 1, ss[rd >> 1] = r - l;
		}
	}
	for(int i = 1; i <= n + n; i++){
		int d = mp[srt[i]];
		if(!(d & 1) && !vis[d >> 1]) dfs(d >> 1);
	}
	//for(int i = 1; i <= n; i++) printf("%d ", ord[i]);
	memset(f, 0xbf, sizeof(f));
	f[n + 1][0][0] = 0;
	for(int i = n; i > 0; i--){
		f[i][0][0] = 0;
		for(int j = min(n - i + 1, m); j > 0; j--){
			f[i][j][0] = max(f[i + 1][j][0], f[i + 1][j][1]);
			if(!nxt[ord[i]]) f[i][j][1] = max(f[i + 1][j - 1][0], f[i + 1][j - 1][1]) + val[ord[i]];
			else f[i][j][1] = max(f[i + 1][j - 1][0], f[i + 1][j - 1][1] + ss[ord[i]]) + val[ord[i]];
		}
	}
	printf("%d\n", srt[n + n] - srt[1] - res - max(f[1][m][0], f[1][m][1]));
	return 0;
}
```

---

## 作者：myyes (赞：2)

摘自我的博客文章：[钥匙题专项训练](https://www.luogu.com.cn/blog/666666new/keys-tm)。

题意：

有 $n$ 个师傅从 $0$ 到 $M$ 时刻上班，第 $i$ 个师傅会在 $S_i$ 时刻去饮水机洗手再在 $T_i$ 时刻回来。没撇钥匙的师傅出门以后不能关门，撇起钥匙的师傅可以随便进出，没撇钥匙的师傅要门开起才能回去，撇起钥匙的师傅回去的时候可以把门锁起。总共 $K$ 串钥匙分给这些师傅，求分配方案使得关门时间最小。

做法：

考虑每个时间段的贡献。如果前一个时间点是某个师傅出去洗手，后面一个时间点也是某个师傅出去洗手，那么这段时间可以关起当且仅当前面一个师傅撇起钥匙。

如果前面一个时间点是某个师傅回来，后面一个时间点也是某个师傅回来，那么这段时间可以关起当且仅当后面的师傅撇起钥匙。

如果前面一个的时间点是某个师傅回来，后面一个时间点是某个师傅出去洗手，那么不管有没有师傅去洗手这段时间一定能关起。

如果前面一个时间点是某个师傅出去洗手，后面一个时间点是某个师傅回来，此时如果它们是同一个师傅，那么只要这个师傅撇起钥匙这段时间就可以关起，不然必须两个师傅都撇起钥匙才能关起。

我们把必须两个师傅同时撇起钥匙的时间段嗲出来连条边，可以发现这张图就是一大串一大串的链，跟撇钥匙一样滴把串串些撇到一起在序列上做个 DP 算一下贡献就可以了得咩。具体来说就是 $dp_{i,j,0/1}$ 表示链上前 $i$ 个师傅撇起 $j$ 串钥匙，师傅 $i$ 撇没撇钥匙，转移就枚举一下前一个师傅有没有撇钥匙转移过来，撇起钥匙的话就加上这个师傅撇钥匙的贡献，要是两个师傅都撇起钥匙就加上这部分的贡献就可以了得咩。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,tot,b[2008],c[2008],dp[2][2008][2],nxt[2008];
struct node
 {
  int x,id,typ;
 bool operator<(node q){return x<q.x;
}
}a[6666];
void cmax(int&x,int y){if(y>x)x=y;
}
int main()
{scanf("%d%d%d",&n,&m,&k);
for(int i=1,x;i<=n;++i)
  {
 scanf("%d",&x);a[++tot]=(node){x,i,0};
scanf("%d",&x),a[++tot]=node{x,i,1};
 }
 sort(a+1,a+tot+1);
int yu=m+a[1].x-a[tot].x;
  for(int i=1;i<tot;++i)
   {
 int len=a[i+1].x-a[i].x;
 if(a[i].typ&&!a[i+1].typ)
 yu+=len;
 else if(a[i].typ&&a[i+1].typ)c[a[i+1].id]+=len;
else if(!a[i].typ&&!a[i+1].typ)
c[a[i].id]+=len;
  else if(a[i].id==a[i+1].id)
c[a[i].id]+=len;
else nxt[a[i+1].id]=a[i].id,b[a[i].id]+=len;
  }
for(int i=1,las=0;i<=n;++i)
 if(!b[i]){
 nxt[las]=i;
  while(nxt[las])
las=nxt[las];
}
dp[0][0][0]=yu;
 int w=0;
  for(int i=nxt[0];i;i=nxt[i]){
w^=1;
for(int j=0;j<=k;++j)for(int t:{0,1})
  {if(!dp[!w][j][t])
continue;
cmax(dp[w][j][0],dp[!w][j][t]);
   cmax(dp[w][j+1][1],dp[!w][j][t]+t*b[i]+c[i]);
 dp[!w][j][t]=0;
  }
}
cout<<max(dp[w][k][0],dp[w][k][1]);
 return 0;
  }
```

---

## 作者：Acerkaio (赞：1)

## 题解：P4890 Never·island
### 思路

正难则反，考虑最长关门时间。

考虑时间轴上的相邻关键点之间的时间段贡献，这里要分类讨论：

对于时间轴上相邻的两个点

1. 若前者为离开，后者也为离开，则分配一把钥匙给前者即可得到此段贡献，即让前者关门。
2. 若前者为进入，后者也为进入，则分配一把钥匙给后者可得到此段贡献。
3. 若前者为进入，后者为离开，则无需分配给他们都可以获得此段贡献。
4. 若前者为离开，后者为进入，则他们要同时被分配到钥匙才可以得到贡献；特别的，若前者、后者是同一个人则只要分配给其即可。

前面的好处理，发现第四种比较棘手，要被同时分配的人的关系似乎很乱啊，且好像又不连续。

但是由于限制条件，我们观察到一个人 $x$ 至多只会有一个人 $y$ 在前面要与他一起被分配，这个人 $x$ 还至多只会有一个人 $z$ 在后面要与他一起被分配。所以，只要恰当安排顺序，把他们都安排在一起去考虑 $dp$，每个人都可以从前一个人去更新。

我们设 $dp_{i,j,0/1}$ 表示考虑到第 $i$ 个人，一共分配了 $j$ 把钥匙，第 $i$ 个人要不要被分配的最长关门时间，最终状态是 $dp_{n,k,0}$ 和 $dp_{n,k,1}$。初始化 $dp_{0,0,0}$ 为第三种情况一定能选的贡献。

### Code
```cpp
#include<bits/stdc++.h>
#define pb push_back

const int N=2010;
using namespace std;
using ll=long long;

int n,m,k,cnt,f[N][N][2],val[N],u[N],alws,p[N],tot;
vector<int>e[N];
struct TimeStamp{
	int t,id;bool flag;
	bool operator <(const TimeStamp x)const{
		return t<x.t;
	}
}q[N<<1];
void restructure(){
	for(int i=1;i<=n;i++){
		if(!u[i]){
			p[++tot]=i;
			int it=i;
			while(!e[it].empty()){
				it=e[it][0];
				p[++tot]=it;
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		int l,r;cin>>l>>r;
		q[++cnt]=(TimeStamp){l,i,0},q[++cnt]=(TimeStamp){r,i,1};
	}
	sort(q+1,q+cnt+1);
	for(int i=2;i<=cnt;i++){
		int time=q[i].t-q[i-1].t;
		if(!q[i-1].flag&&!q[i].flag)val[q[i-1].id]+=time;
		else if(q[i-1].flag&&q[i].flag)val[q[i].id]+=time;
		else if(q[i-1].flag&&!q[i].flag)alws+=time;
		else
			if(!(q[i-1].id^q[i].id))val[q[i].id]+=time;
			else  e[q[i-1].id].pb(q[i].id),u[q[i].id]+=time;
	}
	restructure();//重构顺序
	f[0][0][0]=alws;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=k;j++){
			for(auto last:{0,1}){
				if(!f[i-1][j][last])continue;
				f[i][j][0]=max(f[i][j][0],f[i-1][j][last]);
				f[i][j+1][1]=max(f[i][j+1][1],f[i-1][j][last]+last*u[p[i]]+val[p[i]]);
			}
		}
	}
	cout<<q[cnt].t-q[1].t-max(f[n][k][0],f[n][k][1])<<'\n';
	return 0;
}
```

---

