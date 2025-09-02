# [POI 2008] MAF-Mafia

## 题目描述

在赤道 Byteotia，黑帮之间的争斗愈演愈烈。黑帮老大们来到该国的首都 Byteburg，以解决争端。

谈判非常紧张，在某个时刻，手痒的参与者们拔出了他们的枪。

每个参与者都用手枪瞄准另一个人。

如果他们开始大开杀戒，射击将按照以下荣誉代码进行：

参与者按一定顺序射击，并且在任何时刻最多只有一个人开枪，射手不会失手，他的目标会立即死亡，因此他之后不能再开枪，每个人都开一次枪，前提是他在有机会开枪之前没有被击中，任何参与者都不能改变他最初选择的目标，即使目标已经死了（那么射击不会造成进一步的伤亡）。

一个殡葬承办人从远处观察，正如他通常所做的那样。毕竟，黑帮分子从未让他的生意冷清过。

他在射击中看到了潜在的利润，但他想知道准确的估计。他想知道最小和最大可能的死亡率。

殡葬承办人看到谁瞄准了谁，但不知道射击的顺序。

你需要编写一个程序来确定他如此渴望知道的数字。

任务 编写一个程序：

从标准输入读取每个黑帮分子选择的目标，确定最小和最大伤亡人数，将结果写入标准输出。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
8
2 3 2 2 6 7 8 5
```

### 输出

```
3 5
```

# 题解

## 作者：Always (赞：10)

# 分析:

此题需要画个图来看看

会发现如果i->ai连边 那么图就是一个有向图 并且这个图中会有很多环

我们来看环的情况:(自己画图看看)

最多死的人数就是:环的大小-1

最少活(死)的人数就是:环的大小/2

当然有可能有别的点向这个环连边:

最多死的人数就变成了:环的大小(那个人把环中剩下的一个人补死)

最少活(死)的人数仍然是:环的大小/2

# 然后

我们再来考虑本题:

### Min:

首先入度为0的点(没有人打他) 他是一定存活的

很容易就想到了跑拓扑序

不断加入入度为0的点 并减去他能打死的人能打死的人的入度

最后会剩下很多环 这个时候我们跑一遍tarjan 就得到了各个环的大小

根据分析 存活人数应该+=sum{siz[i]/2} if(i没死的话)

所以最小死亡人数就是 n-最大存活人数

### Max:

相对于min来说更好求一点

首先如果一个点有入度的话 他一定能被打死(按照某种顺序…)

如果他是一个闭环 那么ans+=siz[i]-1

如果他不是一个闭环(有点指向他) 那么ans+=siz[i]

(siz[i] 缩点后i的大小)

# 代码实现

```
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<queue>
#include<stack>
#define N 400000
#define M 1000005
#define il inline
#define lp long long
#define inf 0x7f7f7f7f
#define mm(x , y) memset(x , y , sizeof x)
#define rep(i , x , y) for(register int i = x ; i <= y ; ++i)
#define dep(i , x , y) for(register int i = x ; i >= y ; --i)
using namespace std ;
int n , x , k , t , cnt , ans , Ans , a[M] , bel[M] , dfn[M] , low[M] , siz[M] , rd[M] ;
bool ins[M] , die[M] , dea[M] ;
stack<int> s ;
queue<int> q ;
il int Max(int x , int y){return x > y ? x : y ;}
il int Min(int x , int y){return x < y ? x : y ;}
il void read(int &r){
    int f = 1 ; r = 0 ; char ch = getchar() ;
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1 ; ch = getchar();}
    while(ch >= '0' && ch <= '9'){r = r * 10 + ch - '0' ; ch = getchar();}
    r *= f ;
}
il void write(int x){
    if(x < 0)putchar('-') , x = -x ;
    if(x > 9)write(x / 10) ;
    putchar(x % 10 + '0') ;
}
il void tarjan(int u){
    ins[u] = 1 ; s.push(u) ;
    low[u] = dfn[u] = ++ t ; int v ;
    if(!dfn[(v = a[u])] && !die[v]){
        tarjan(v) ;
        low[u] = Min(low[u] , low[v]) ;
    }else if(ins[v])low[u] = Min(low[u] , dfn[v]) ;
    if(low[u] == dfn[u]){
        cnt ++ ;
        while(s.top() != u){
            bel[s.top()] = cnt ; ins[s.top()] = 0 ; s.pop() ;
        }bel[s.top()] = cnt ; ins[s.top()] = 0 ; s.pop() ;
    }
}
il void topsort(){
    rep(i , 1 , n)if(!rd[i]) q.push(i) , ans++ ;
    while(q.size()){
    	int u = q.front() ; q.pop() ;
    	if(die[a[u]]) continue ;
    	die[a[u]] = 1 ;
    	if(!(--rd[a[a[u]]])) q.push(a[a[u]]) , ans ++ ;
	}
}
int main(){
    read(n) ;
    rep(i , 1 , n)read(a[i]) , rd[a[i]] ++ ;
    topsort() ; mm(rd , 0) ;
    rep(i , 1 , n)if(!dfn[i])tarjan(i) ;
    rep(i , 1 , n)siz[bel[i]] ++ , dea[bel[i]] |= die[i] ; k = 0 ;
    rep(u , 1 , n){
        if(bel[u] != bel[a[u]])rd[bel[a[u]]] ++ ;
        else if(u == a[u])rd[bel[a[u]]] = 1 ;//处理自环的情况 
    }
    rep(i , 1 , cnt){
        if(siz[i] == 1 && rd[i])Ans ++ ;
        else if(siz[i] != 1 && rd[i])Ans += siz[i] ;
        else if(siz[i] != 1 && !rd[i])Ans += siz[i] - 1 ;
    }
    rep(i , 1 , cnt)if(siz[i] > 1 && !dea[i])ans += siz[i] / 2 ;
    write(n - ans) ; putchar(' ') ; write(Ans) ;
    return 0 ;
}
```

---

## 作者：Vocanda (赞：8)

# 题目
[题目链接](https://www.luogu.com.cn/problem/P3472)

# 分析
正如标签，贪心！没错，这个题的思想就是贪心了。

由于顺序不定，所以谁死了对谁有影响都是需要考虑进去的。但是有一点是一定可以肯定的，就是入度为$0$的点，也就是没有被人用枪指着的人的目标是必死的，因为没有人会杀死他而让他的目标存活。由于我们要求的就是死的最多和最小，那么我们逆向思考一下，我们就可以求出最大存活和最小存活数，最后减一下就好了。

我们利用一个队列来存储一定活着的人，也就是入度为$0$的人，每一次取出队首，然后将当前这个人的目标标记为死人……然后显然，这个死了的人的目标的入度就减一了。如果当前入度变成了$0$，那么这个人就可以放到队列里，让后让或者的最大人数加一，并且标记为没死。至于为什么不把最小存活也加一呢，因为这个人不一定会活着，只有目标为他的点死了，他才能够活，所以只把最大的存活人数加一。

处理完这样的单点之后，我们就应该处理环了，分析一下，我们可以得出，如果让环里的人死的最多，那么可以通过一定的顺序，让最后只剩下一个人，而死的最少的情况就是死一半。我们在扫描环的时候，记录一下是否有没有死的，并且记录环的大小，最后如果环里有能不死的，且环的长度大于一，那么一定有一个人没死，所以就让$Min++$，不然就不管。最后再让最大值加上环大小的两倍，最后只需要用总人数减去$Max$和$Min$就行了

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
int q[maxn];
int Max,Min;
int die[maxn],undie[maxn];
int to[maxn];
int n;
int rd[maxn];
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>to[i];
		rd[to[i]]++;//记录入度
	}
	for(int i=1;i<=n;++i){
		if(rd[i] == 0){//入度为0就死不掉
			Min++;//最小人数++
			q[++Max] = i;//最大人数++并且入队
		}
	}
	int head = 1;
	while(head<=Max){
		int cur = q[head];//取出队首
		head++;
		if(die[to[cur]])continue;//如果死了就continue
		die[to[cur]] = 1;//没死的话他的目标一定死，标记
		int li = to[to[cur]];
		rd[li]--;//他的目标的目标入度减一
		undie[li] = 1;//标记可以不死
		if(!rd[li]){//入度为0就入队，但是Min不加
			q[++Max] = li;
		}
	}
	for(int i=1;i<=n;++i){//下边就剩下环了
		int len = 0,flag = 0;
		if(rd[i] && !die[i]){//有入度，没死，就从这里开始
			for(int j=i;!die[j];j=to[j]){//一个个找环里的人
				len++;//环长度++
				flag|=undie[j];//看是否有不死的
				die[j] = 1;//标记死亡
			}
		if(!flag && len>1)Min++;//有可以不死的并且长度大于1,因为等于一就是自环，必死
		Max += len/2;//活的最大人数加上环长度的二分之一
		}
	}
	cout<<n-Max<<" "<<n-Min<<"\n";
}

```

---

## 作者：大菜鸡fks (赞：5)

这题好像画画图思路也比较清晰的。因为图保证联通，所以是一个环套树

最小：用拓扑排序的方式删掉入度为0的点，那么剩下的一定都是环，环的答案为size/2

最大：那就是n-ans入度为0的点和aim为自己的点

```cpp
#include<cstdio>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=1000005;
int n,a[N],in[N];
inline void init(){
	n=read();
	for (int i=1;i<=n;i++){
		a[i]=read(); in[a[i]]++;
	}
}
int ans1,ans2,q[N],die[N],cd[N];
inline void solve(){
	for (int i=1;i<=n;i++){
		if (!in[i]){
			ans1++;
			q[++ans2]=i;
		}
	}
	for (int i=1;i<=ans2;i++){
		int u=a[q[i]];
		if (die[u]) continue;
		die[u]=1; cd[a[u]]=1;
		--in[a[u]];
		if (!in[a[u]]) q[++ans2]=a[u];
	}
	for (int i=1;i<=n;i++){
		if (in[i]&&!die[i]){
			int len,bo; len=bo=0;
			for (int j=i;!die[j];j=a[j]){
				die[j]=1; ++len;
				bo|=cd[j];
			}
			if (!bo&&len>1) ++ans1;
			ans2+=len/2;
		}
	}
	write(n-ans2); putchar(' '); writeln(n-ans1);
}
int main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：kczno1 (赞：5)

每个点一个出边，形成一堆环套树。


最少:

树按拓扑序开枪

环上如果有点被毙了则加入队列，

否则随便选个点加入队列(直接计算也行)

然后按bfs序开枪。


最多:

树按拓扑序逆序开枪，则只要有儿子的点就会死

环上如果钦定一个点最后开枪，则除了这个点以外的点都能死；当有一个点有儿子时，则可以做到所有点都死。

(环长=1是特例)


```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define gc (c=getchar())
int read()
{
    char c;
    while(gc<'0');
    int x=c-'0';
    while(gc>='0')x=x*10+c-'0';
    return x;
}
template <typename T> void chmin(T &x,const T &y)
{
    if(x>y)x=y;
}
template <typename T> void chmax(T &x,const T &y)
{
    if(x<y)x=y;
}
#define rep(i,l,r) for(int i=l;i<=r;++i)
const int N=1e6+5;
int lk[N],du[N],q[N];
bool vis[N],die[N],son[N];

int main()
{
    freopen("1.in","r",stdin);
    int n=read();
    rep(i,1,n)lk[i]=read();
    rep(i,1,n)++du[lk[i]];
    int tail=0;
    rep(i,1,n)
    if(!du[i])q[++tail]=i;
    int ans1=0,ans2=0;
    rep(head,1,tail)
    {
        int x=q[head];
        int y=lk[x];
        son[y]=1;
        if(!die[x]&&!die[y])die[y]=1;
        if(!--du[y])q[++tail]=y; 
    }
    
    rep(i,1,n)
    {
        if(!du[i]){ans2+=son[i];continue;}
        if(vis[i])continue;
        if(lk[i]==i){++ans2;continue;}
        int x=i;bool have=0;
        while(!vis[x])
        {
            vis[x]=1;
            ++ans2;
            have|=son[x];
            x=lk[x];
        }
        if(!have)--ans2;
    }
    
    int tail2=tail;
    rep(x,1,n)
    if(du[x]&&die[x])
    {
        du[x]=0;
        q[++tail2]=x;
    }
    rep(head,tail+1,tail2)
    {
        int x=q[head];
        int y=lk[x];
        if(du[y])
        {
            du[y]=0;
            q[++tail2]=y;
            if(!die[x]&&!die[y])die[y]=1;
        }
    }
    rep(i,1,n)
    if(du[i])
    {
        int x=i;
        while(du[x])
        {
            du[x]=0;
            int y=lk[x];
            if(!die[x])die[y]=1;
            x=y;
        }
    }
    rep(i,1,n)ans1+=die[i];
    printf("%d %d\n",ans1,ans2);
}
```

---

## 作者：szm_ (赞：4)

洛谷居然没有dp的题解？  
~~调了半晚上dp结果爆栈了~~  
  
把每个人和他瞄准的人连单向边，就会形成一个环套树的森林。由于每棵环套树互不干涉，我们可以把答案简单地累加起来。  
最大死亡的情况：对于存在内向树的环套树，答案为环套树内点的总个数-叶子节点个数，否则为点的个数-1。  
最小死亡的情况：就是让活着的人最多。我们发现在环套树上相邻的两个点不能同时活着，那么是不是很像noip2018 d2t3……  
~~而且还没有修改~~  
所以我们在每棵内向树上跑一次树形dp，记$f[0/1][x]$表示$x$活着/死亡时子树死亡的最小人数。容易发现
$f[0][x]=\sum(f[1][k])+1$;  
$f[1][x]=\sum(min(f[0][k],f[1][k]))+1$;  
其中k为x的儿子。~~（其实和d2t3完全一个套路）~~  
那么我们就把一棵内向树的信息压到了环的一个点上。再在环上跑一次dp，记$g[0/1][i]$表示环上到第i个点（活着/死亡）,i之前的点中最小死亡数。转移同理。  
注意：由于是一个环，所以第一个点和最后一个点不能同时活着，在计算答案的时候不能列入考虑。  
自杀的情况可能要特判。

~~贴一份蜗牛代码~~  
```cpp
#include<cstdio>
#include<vector>
#include<string>
using std::min;using std::vector;
#define N 1000002
int n,m,t,a[N],s[N],z[N],f[2][N],h[2][2][N],c[N];
vector<int>v[N],e[N];bool p[N],g[N],y[N];
#define _(d) while(d(isdigit(ch=getchar())))
inline int R() {char ch;_(!);int x=(ch^48);_()x=(x<<3)+(x<<1)+(ch^48);return x;}
inline void F(int x,int dd,int fr) {
	if(!p[x]) {f[0][x]=0;return ;}
	if(f[0][x]<n || f[1][x]<n) return ;
	f[0][x]=0,f[1][x]=c[x]=1;
	for(int i=e[x].size()-1,k;~i;i--)
		if(!g[k=e[x][i]]) {
			F(k,dd+1,x);
			if(f[0][x]+f[1][k]<=n)
				f[0][x]+=f[1][k];
			else f[0][x]=1e9;
			if(f[1][x]+min(f[0][k],f[1][k])<=n)
				f[1][x]+=min(f[0][k],f[1][k]);
			else f[1][x]=1e9;
			c[x]+=c[k],y[x]=1;
		}
}
void D(int x,int t,int j) {
	if(z[x]==j) {
		m++;for(int i=t-1;i;i--) {
			v[m].push_back(s[i]),g[s[i]]=1;
			if(s[i]==x) return ;
		}return ;
	}z[x]=j,s[t]=x;
	if(!z[a[x]] || z[a[x]]==j) D(a[x],t+1,j);
}
inline int B(int x) {
	int t=0;bool fl=1;
	if(v[x].size()<2) return c[v[x][0]];
	for(int i=v[x].size()-1,k;i;i--)
		t+=c[k=v[x][i]],fl&=(!y[k]);
	fl&=(!y[v[x][0]]);
	return t+c[v[x][0]]-fl;
}
inline int A(int x) {
	int l=v[x].size()-1,k=v[x][l];
	for(int i=l;~i;i--)
		h[0][0][i]=h[0][1][i]=h[1][0][i]=h[1][1][i]=n;
	h[0][0][l]=f[0][k],h[1][1][l]=f[1][k];
	if(!l) return f[1][k];
	for(int i=l-1;~i;i--) {
		k=v[x][i];
		for(int j=0;j<2;j++) {
			if(h[j][1][i+1]+f[0][k]<=n)
				h[j][0][i]=h[j][1][i+1]+f[0][k];
			else h[j][0][i]=1e9;
			if(min(h[j][1][i+1],h[j][0][i+1])+f[1][k]<=n)
				h[j][1][i]=min(h[j][1][i+1],h[j][0][i+1])+f[1][k];
			else h[j][1][i]=1e9;
		}
	}return min(h[0][1][0],min(h[1][0][0],h[1][1][0]));
}
int main() {
	n=R();for(int i=1;i<=n;i++)
		a[i]=R(),p[a[i]]=1,e[a[i]].push_back(i);
	for(int i=1;i<=n;i++)
		if(!z[i]) D(i,1,i);
	for(int i=1;i<=n;i++)
		f[0][i]=f[1][i]=h[0][0][i]=n,
		h[0][1][i]=h[1][1][i]=h[1][0][i]=n;
	for(int i=1;i<=n;i++)
		if(g[i]) F(i,0,0);
	int pr1=0,pr2=0;
	for(int i=1;i<=m;i++)
		pr1+=B(i),pr2+=A(i);
return printf("%d %d\n",pr2,pr1),0;}
```

---

## 作者：hzoi_liuchang (赞：3)

## 分析

![](https://cdn.luogu.com.cn/upload/image_hosting/9ztnomuu.png)

如果$a$瞄准$b$，那么我们就从$a$到$b$建一条有向边

我们设最大存活程度为$Max$，最小存活程度为$Min$

不难发现，入度为$0$的点必定存活（左图中的绿圈）

因为没有人会瞄准他

进一步分析可以发现，建好图后的联通块有两种情况

1、左图（非环）

显然，$1$号节点、$4$号节点必定存活，而他们所指的$2$号节点必死

问题就在$3$号节点，如果他先射杀$2$号节点，那么他的入度变为$0$，存活人数为$3$

如果$2$号节点先射杀$3$，那么三号节点的入度仍为$1$,存活人数为$2$

所以，我们可以向拓扑排序那样维护入度为$0$的点，将其放入队列中

队首的目标必死，队首目标的目标可死可不死，打上标记

2、右图（环状）

最小存活：+1（无论如何都会剩一个人）

最大存活：隔一个人打一个，可以最大存活 len/2；

要特别判断自己打自己的环

## 代码
``` cpp
#include<stdio.h>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn=1e6+5;
int n,Max,Min,q[maxn],aim[maxn],rd[maxn];
bool die[maxn],undie[maxn];
void Init(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%d",&aim[i]);
        rd[aim[i]]++;
    }
    for(int i=1;i<=n;++i)//入度为0的点必活
        if(rd[i]==0){
            Min++;//最小必活数+1
            q[++Max]=i;//队列维护的是入度为0的点
        }
}
void Solve(){
    int head=1;
    while(head<=Max){//扫描队列
        int cur=q[head];head++;//取出队首并出队
        if(die[aim[cur]]) continue;//队首目标已死(多个入度为0的点指向一个点)
        die[aim[cur]]=1;//队首目标必死
        int live=aim[aim[cur]];//队首目标的目标可死可不死，看决策
        rd[live]--;//
        undie[live]=1;//可以让他活，但想死的时候随时可以让他死，在环可以最后死
        if(rd[live]==0)//虽然入度为0，但不一定是必活，所以Min不加
            q[++Max]=live;
    }
    //下面处理只剩下环
    for(int i=1;i<=n;++i)
        if(rd[i] && !die[i]){
            int len=0,flag=0;//len记录环大小,flag标记环上是否有undie的点    
            for(int j=i;!die[j];j=aim[j]){
                len++;
                flag|=undie[j];
                die[j]=1;//标记已死，避免其他的再来计算
            }
            if(!flag && len>1) Min++;//len=1表示自环，必死
            Max+=len/2;
    } 
    printf("%d %d",n-Max,n-Min);
}
int main(){
    Init();
    Solve();
    return 0;
}
```

---

## 作者：detect (赞：2)

## [题目传送门](https://www.luogu.org/problem/P3472)

等价于求最多存活人数，于最少存活人数。

我们发现若转化为图，则必定是（可能是森林），一个环外加环上的点上延伸出去一条链

-  最少存活人数： 
1. 对于链，我们显然可以按照拓扑序全部枪毙

2. 对于环，若环上有点被其他点指向，那么可以全歼，否则只有一个环必定剩下1个

- 最多存活人数：

1. 对于链：显然入度为0的点指向的必死，所以不如让其早点死，同事把其要枪毙的人入度-1，那么这样明显最优，于是同样按照拓扑序，外加一个die数组，记录那些点已死，统计时跳开它们就好了

2. 对于环，因为在解决链的时候，我们可能已经对于环动了手脚（可能环上的一些点已经被枪毙），但是我们发现对于这些“环”，其实已经变成了链，于是继续拓扑搞事情就行。 所有现在只剩下真正完整没有已经被枪毙的环了，不难得每次加上环长度/2即可

code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1000005],die[1000005],bj[1000005],head[2000005],nex[2000005],go[2000005];
int n,m,ru[1000005],ans1,ans2,vis[1000005],tot;
void add(int u,int v){
	nex[++tot]=head[u];head[u]=tot;go[tot]=v;
}queue <int> q;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);add(i,a[i]);ru[a[i]]++;
	}
	for(int i=1;i<=n;i++){
		if(!ru[i]) q.push(i),ans1++,ans2++;
	}
	while(!q.empty()){
		int u=q.front();vis[u]=1;q.pop();
		u=a[u];
		int v=a[u];
        if(die[u]) continue;die[u]=1;
		ru[v]--;bj[v]=1;
		if(!ru[v]){
			ans1++;
			q.push(v);
		}
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]&&!die[i]){
			int yy=i,len=0,bo=0;
			while(1){
				if(vis[yy]) break;vis[yy]=1;
				len++;bo|=bj[yy];yy=go[head[yy]];
			}
			if(len>1&&(!bo)) ans2++;//对于完全环，至少剩一个
			ans1+=len/2;
		}
	}cout<<n-ans1<<" "<<n-ans2<<endl;
	return 0;
}
```


---

## 作者：KawaragiMomoka (赞：1)

# 分析

这是一道很有意思的思维题~~考试给我整红温的题~~。在写代码前，我们先来想一下这道题的特性：

1. 对于没有被枪指着的人，他无论如何都不会死，并且他瞄准的人是必死的。我们不妨转换一下，求最多最少能存活多少人，然后用 $n$ 来减。
2. 如果把枪指向自己（自环），他要么被别人杀死，要么自己把自己崩了，总之就是必死无疑。
3. 对于不同的顺序，死的人数不同，举个例子：$1->2->3$，如果 $2$ 先开枪，$1$ 再开枪，那么就死了两个人；$1$ 先开枪，$2$ 直接就死了，$3$ 不再受到威胁，总共只死了一个人。可以发现这种隔一个死一个的方式可以增加活下来的人，而从最后一个一个往前打死的最多。
4. 对于一个大小为 $n$ 的环，那么它最多存活 $\frac{n}{2}$ 个人（隔一个死一个）。
5. 对于一个环，如果它独立于其他点，那么它最多存活 $1$ 个人。否则环上全部都会死。

![解释](https://cdn.luogu.com.cn/upload/image_hosting/3nlv65e0.png)



再来讲实现的问题：

1. 首先读完数据后我们先进行缩点。最少存活人数是很好求的，根据上面说的，只要没有入度，他必然存活，其他的都会死。缩完点后统计新图上入度为 $0$ 的点即可。
2. 然后求最多存活人数，这个难搞一点。
   1. 采用拓扑排序（在原先的图上），先找出所有入度为 $0$ 的点并把它们入队，同时记录最多存活人数。
   2. 为什么要在**原图**上跑**拓扑排序**？这涉及到对于环的处理，首先不能单纯在新图上根据点的大小大于 $1$ 来判断，因为上面我们所讨论的环上的最多存活的人数有局限性，如果环上有多个点被环外的点瞄准，那么情况可能会发生变化（比方说全部都杀了，当然也有可能没变化，看具体瞄准的是哪些点）。在新图上整个环被缩成了一个点，对于其中每个单独的点，我们没法细致的讨论，所以我们在原先的图上跑拓扑，统计入队的点都属于新图上的哪些点。最后，如果新图上某个环上没有点入队，那他就不受影响，那么这个环就满足最多存活 $\frac{n}{2}$。
   3. 对于将队列中的元素，我们直接标记其目标已被击杀，然后目标的目标入度减一。当目标的目标入度为 $0$ 时将其入队，同时更新最多存活人数（前面的人已经被杀了，现在不受威胁）。
   4. 如果被标记为已击杀，直接跳过。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int n, maxalive, minalive;
int head[maxn], to[maxn], indeg[maxn], indeg2[maxn];
struct Edge {
    int to, next;
} edge[maxn];

int edgecnt;
inline void insertEdge(int u, int v) {
    edge[++edgecnt].to = v;
    edge[edgecnt].next = head[u];
    head[u] = edgecnt;
}

bool insta[maxn];
int dfn[maxn], low[maxn], sta[maxn], belong[maxn], nodecnt[maxn];
int tim, top, cnt;
void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    sta[++top] = u;
    insta[u] = true;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (insta[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        cnt++;
        while (sta[top] != u) {
            belong[sta[top]] = cnt;
            nodecnt[cnt]++;
            insta[sta[top--]] = false;
        }
        belong[sta[top]] = cnt;
        nodecnt[cnt]++;
        insta[sta[top--]] = false;
    }
}

// 建新图
inline void buildNewGraph() {
    int temp = edgecnt;
    edgecnt = 0;
    memset(head, 0, sizeof(head));
    for (int i = 1; i <= temp; i++) {
        int u = i, v = to[i];
        if (belong[u] == belong[v] && u != v) continue; // 自环也需要建边
        insertEdge(belong[u], belong[v]);
        indeg2[belong[v]]++;
    }
}

bool mark[maxn], killed[maxn];
inline void topo() {
    queue<int> que;
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) {
            que.push(i);
            maxalive++;
            mark[belong[i]] = true;
        }
    }
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        int v = to[u]; // 目标
        int vnext = to[v]; // 目标的目标
        mark[belong[v]] = true;
        if (!killed[v]) {
            killed[v] = true;
            indeg[vnext]--;
            if (!indeg[vnext]) {
                maxalive++;
                que.push(vnext);
                mark[belong[vnext]] = true;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &to[i]);
        insertEdge(i, to[i]);
        indeg[to[i]]++;
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }
    buildNewGraph();
    topo();
    for (int i = 1; i <= cnt; i++) {
        if (!mark[i]) {
            maxalive += nodecnt[i] / 2;
        }
        if (!indeg2[i]) {
            minalive++;
        }
    }
    printf("%d %d", n - maxalive, n - minalive);
    return 0;
}
```

---

## 作者：Code_星云 (赞：1)

比较有趣的一道贪心。首先容易看出这是一个基环内向森林。

首先考虑将问题转化为最大和最小的存活人数。

然后找一下性质。发现入度为 0 的点一定会存活。若是最小存活人数，容易发现存活的就只有这些点和环上的一个点（或者没有）。

然后考虑如何求最大存活。对于某一条链，按照奇偶性（遍历深度）分类，容易发现使奇数层存活，偶数层死亡时存活人数最多。当然多条链时要拓扑排序处理一下。

其实这时问题几乎完成了，但还有一种情况就是对于每一条链，环的节点都处在偶数层的时候。此时拓扑排序不会处理到他们。此时只剩下的是一些环。贪心的保留他们的一半即可。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1000005;
int n, minn, maxn, h, to[N], d[N], q[N], die[N], lv[N];

int main(){
	scanf("%d", &n); for(int i = 1; i <= n; i ++) scanf("%d", &to[i]), d[to[i]] ++;
	for(int i = 1; i <= n; i ++) if(! d[i]){
		q[++ maxn] = i; ++ minn;
	}
	h = 1;
	while(h <= maxn){
		int x = q[h ++]; if(die[to[x]]) continue;
		die[to[x]] = true; int y = to[to[x]]; lv[y] = true; d[y] --;
		if(d[y] == 0) q[++ maxn] = y;
	}
	for(int i = 1; i <= n; i ++) if((! die[i]) && d[i]){
		int cnt = 0, flag = 0;
		for(int x = i; ! die[x]; x = to[x]){cnt ++; flag |= lv[x]; die[x] = true; if(to[x] == i) break;}
		maxn += cnt / 2; if(cnt > 1 && (! flag)) minn ++;
	}
	printf("%d %d\n", n - maxn, n - minn); return 0;
}
```


---

## 作者：Lvlinxi2010 (赞：0)

考虑贪心，我们分环和链讨论，

一个长度为 $len$ 的环，最多可以存活 $\left\lfloor\dfrac{len}{2}\right\rfloor$ 个点，最少可以只存活一个。

在链上的点，从入度为 $0$ 的点开始算，偶数位的点必死。

用拓扑排序处理，在求最少死亡的时候可以证明入度为 $0$ 的点先开枪一定不会更劣，在求最多死亡的时候可以证明有一种顺序让只有入度为 $0$ 的点存活。

如果环上的点如果有一个点有子树，我们可以让这个点存活然后让他的子树杀掉他，这时候环上存活数可以为 $0$。

附上代码：

```cpp
#include<bits/stdc++.h>
#define FL(i,a,b) for(int i=(a);i<=(b);i++)
#define FR(i,a,b) for(int i=(a);i>=(b);i--)
#define ll long long
using namespace std;
const int MAXN = 1e6 + 10;
int a[MAXN],d[MAXN];
bool v[MAXN],son[MAXN];
//v[i]记录是否死亡，son[i]记录若i在环上是否有子树 
queue<int>q; 
int main(){
	int n,mx=0,mn=0;
	//mx表示最大存活人数，mn表示最小存活人数 
	scanf("%d",&n);
	FL(i,1,n) scanf("%d",&a[i]),d[a[i]]++;
	FL(i,1,n){
		if(!d[i]) mx++,mn++,q.push(i);
	}
	while(!q.empty()){
		int x=q.front();
		q.pop();
		if(v[a[x]]) continue;
		v[a[x]]=1;
		int t=a[a[x]];
		son[t]=1;
		d[t]--;
		if(!d[t]) mx++,q.push(t);
	} 
	FL(i,1,n){
		if(v[i]||!d[i]) continue;
		int len=0,j=i;
		bool f=0;
		while(j){
			len++;
			v[j]=1;
			f|=son[j];
			j=a[j];
			if(j==i) break;
		}
		mx+=(len/2);
		if(len>1&&!f) mn++; 
	}
	printf("%d %d\n",n-mx,n-mn);
}
```

---

## 作者：SMTwy (赞：0)

首先，依据瞄准关系建个图，没有入度的点一定不会死，那么同样，他指向的人一定会死。

从没有入度的点开始，求最大死亡人数他最后开枪，求最小他第一个开枪。

我们又可得，如果是一个环，最少要死一半（间隔开枪，且这个枪一定要响），最多死得只剩下一个。

这就是模拟的思路。把模拟进行优化，分析发现，图中不会出现一条链的情况，因为每个人必定指向一个人(哪怕是指自己)，图中要么是环，要么是链加环，或者这两者结合，但基本图就是这两种。

一个环： $n/2$ 和 $1$。

一个链 $+$ 环：环上的点可以全死 链上的点依次记录即可。

我们完全可以从入度为零的点开始跑一个拓扑，从入度为零的点开始依次删点，删完之后图中就只会剩下环了。

有一个区别就是奇数点链加环会被拓扑消解掉，偶数点链加环，它的环不会被消解，但它的环最多可以死的一个都不剩，所以要与普通环区分一下。

更多的细节放代码里了，看代码实现吧。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mx=3000000+1000;
int n,an1,an2;//记录被杀不如记录存话方便
int q[mx],l=1,r=0; 
bool vis[mx];//可能一个人被毙了一次后又被毙 ，所以打个标记
int in[mx],aim[mx],save[mx]; 
void MYH(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		int x;scanf("%d",&x);
		aim[i]=x;in[x]++;//入度加1，指向更新
	} 
	for(int i=1;i<=n;++i){
		if(in[i]==0){
			an1++;an2++; //此刻这个点没有入度，那么它一定存活，无论最大存活还是最小都要加一
			q[++r]=i; 
		}
	}
	while(l<=r){
		int u=q[l];l++;
		int v=aim[u];
		if(vis[v]==1)continue;//一个人可能被多个人指向
		vis[v]=1; int vv=aim[v];
		in[vv]--;
		save[vv]=1;//u指向v，v指向vv,u毙了v之后可以救活vv,可以记录进最大存活人数
		if(in[vv]==0){
			//它能不死就不死
			an2++;//所以记录一下存活最大人数 
			q[++r]=vv;//用队列记录不死而不是死 
		}
	}
	//此刻图中只会有环了，因为已经将所有入度为零的点和他指向的人删了 
	//如果环是外面有奇数链指向，有一个人会开枪进环内，也会被消解掉
	int huan=0;
	for(int i=1;i<=n;++i){
		if(in[i]!=0 && vis[i]==0){
			int v=i;int pd=0;
			huan=0;
			while(1){
				if(vis[v]==1)break;
				vis[v]=1;v=aim[v];
				huan++;
				if(save[v]==1)pd=1;
			}
			if(pd==0 && huan>1)an1++;//最少
			an2+=huan/2;//最多活一半
		}
	}
	int d1=n-an1;
	int d2=n-an2;
	printf("%d %d\n",d2,d1); 
}

int main(){
	//freopen("maf.in","r",stdin);
	//freopen("maf.out","w",stdout);
	MYH();
	return 0;
}
```

祝您，武运昌隆

---

## 作者：望眼浮云 (赞：0)

最小值：

	 1.入度为0的点，一定存活，将它们加入队列。
 	2.从队列里取出节点，开枪，可能出现新的0入度的节点。
 	3.最后剩下若干个环，每个环的贡献为ceil(size/2)。
    
最大值：

	 1.一个自环，贡献1
	 2.一个大于1的环，贡献size-1
	 3.一个基环树，贡献size-num_leaf
     
 ```cpp
#include<bits/stdc++.h>
#define maxn 1000100
using namespace std;
struct node
{
    int to,next;
}a[maxn<<1];
int n,cnt,tot;
int c[maxn],du[maxn],head[maxn],vis[maxn],v[maxn],fir[maxn];
int belong[maxn],du2[maxn],siz[maxn];
void add(int x,int y)
{
	a[++cnt].next=head[x];
	a[cnt].to=y;
	head[x]=cnt;
}
void dfs(int x,int fa)
{
    vis[x]=1,belong[x]=tot,siz[tot]++;
    for(int i=head[x];i;i=a[i].next)
    {
        int y=a[i].to;
        if(y==x||y==fa||vis[y])continue;
        dfs(y,x);
    }
}
int check(int x,int num)
{
    v[x]=1;
    int t=x,cntt=1;
    while(!v[c[t]])
    {
        v[c[t]]=1;
        t=c[t];
        cntt++;
    }
    t=c[t];
    if(t==x&&cntt==num) return 1;
    else return 0;
}
int main()
{
	int maxx=0,minn=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&c[i]);
        du[c[i]]++;
        add(i,c[i]);add(c[i],i);
    }
    
    queue<int>q;
    for(int i=1;i<=n;i++)
        if(!du[i]) q.push(i);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        v[u]=1;
        if(!vis[c[u]])
        {
            v[c[u]]=vis[c[u]]=1;
			minn++;
            du[c[c[u]]]--;
            if(!du[c[c[u]]])
                q.push(c[c[u]]);
        }
    }
    for(int i=1;i<=n;i++)
        if(!v[i])
        {
            int t=i,cur=0;
            while(!v[t])
            {
                v[t]=1;
                cur++;
                t=c[t];
            }
            minn+=(cur+1)/2;
        }
    
    for(int i=1;i<=n;i++) du[c[i]]++;
    memset(v,0,sizeof(v));
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        if(!vis[i]) tot++,dfs(i,0),fir[tot]=i;
    for(int i=1;i<=n;i++)
        if(du[i]==0) du2[belong[i]]++;
    for(int i=1;i<=tot;i++)
    {
        if(siz[i]==1) maxx++;
        if(check(fir[i],siz[i])) maxx+=siz[i]-1;
        else maxx+=siz[i]-du2[i];
    }
    printf("%d %d",minn,maxx);
}

```





---

