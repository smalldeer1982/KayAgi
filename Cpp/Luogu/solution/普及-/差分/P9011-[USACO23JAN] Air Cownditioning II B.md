# [USACO23JAN] Air Cownditioning II B

## 题目描述

农夫约翰的 $N$ 头奶牛 $(1≤N≤20)$ 住在一个谷仓里，谷仓里有连续的牛栏，编号为 $1-100$ 。 奶牛 $i$ 占据了编号 $[s_i,t_i]$ 的牛栏。 不同奶牛占据的牛栏范围是互不相交的。 奶牛有不同的冷却要求，奶牛 $i$ 占用的每个牛栏的温度必须至少降低 $c_i$ 单位。

谷仓包含 $M$ 台空调，标记为 $1-M$ $(1\le M\le10)$。第 $i$ 台空调需要花费 $m_i$ 单位的金钱来运行 $(1\le m_i \le 1000)$ ，如果运行，第 $i$ 台空调将牛栏 $[a_i,b_i]$ 所有牛栏的温度降低 $p_i$（$1\le p_i\le10^6）$。 空调覆盖的牛栏范围可能会重叠。

请帮助农夫约翰求出满足所有奶牛需求要花费的最少金钱。

## 说明/提示

### 样例解释 1

一种花费最少的可能解决方案是选择那些冷却区间为 $[2,9]$ 、$[1,2]$ 和 $[6,9]$ 的空调，成本为 $ 3+2+5=10$ .


对于 $100\%$ 的数据，$1 \le N \le 20$， $1 \le M \le 10$, $ 1 \le a_i, b_i, s_i, t_i \le 100$, $1 \le c_i, p_i \le 10^6$， $1 \le m_i \le 1000$。

## 样例 #1

### 输入

```
2 4
1 5 2
7 9 3
2 9 2 3
1 6 2 8
1 2 4 2
6 9 1 5```

### 输出

```
10```

# 题解

## 作者：Jorisy (赞：14)

数据范围较小，易想到 dfs 暴力搜索。

首先对于输入的 $s_i,t_i,c_i$，我们开一个桶 $cw$，将对于 $s_i\le\forall j\le t_i$，执行 $cw_j\leftarrow cw_j+c_i$。

然后开始 dfs。

dfs 每次做选或不选，在第 $dep$ 层选就是对于 $a_{dep}\le\forall i\le b_{dep}$，执行 $cw_i\leftarrow cw_i-p_{dep}$，然后价值 $+m_{dep}$。注意回溯。

然后搜完验证是否对于 $1\le\forall i\le \max\{t_i\}$，满足 $cw_i\le 0$ 即可。

赛时 AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,k,ans=1e9,cw[105],s[25],t[25],c[25],a[25],b[25],p[25],v[25];

bool f()//是否满足
{
	for(int i=1;i<=k;i++)
	{
		if(cw[i]>0) return 0;
	}
	return 1;
}

void dfs(int dep,int s)
{
	if(dep>m)
	{
		//cerr<<"DE: ";for(int i=1;i<=k;i++) cerr<<cw[i]<<' ';cerr<<endl;
		if(f()) ans=min(ans,s);//合法就更新答案
		return;
	}
	dfs(dep+1,s);//不选
	for(int i=a[dep];i<=b[dep];i++) cw[i]-=p[dep];
	dfs(dep+1,s+v[dep]);//选
	for(int i=a[dep];i<=b[dep];i++) cw[i]+=p[dep];//回溯
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i]>>t[i]>>c[i];
		k=max(k,t[i]);
		for(int j=s[i];j<=t[i];j++) cw[j]+=c[i];//事先处理
	}
	for(int i=1;i<=m;i++) cin>>a[i]>>b[i]>>p[i]>>v[i];
	dfs(1,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：doumingze (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/P9011)
# 分析
$N \leq 20$，$M \leq 10$，数据这么小，不需要特别难的算法，可以直接枚举。

枚举方式也很简单：使用 dfs 枚举。每个空调只有两种状态：使用或不使用。然后再计算一下选择被使用的空调是否符合降温要求，若符合计算其花销，取其中最小值即可。

判断是否符合降温需求，可以先求出每个牛棚至少需降多少温度，再对于每次枚举，计算本次枚举的状态下每个牛棚降了多少温度，然后比对每个牛棚该状态下降的温度与需要降的温度即可。

有不理解的看代码与注释就行了，还是比较好理解的。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 110, MM = 15;
int n, M;
int tp[N], jtp[N];
int a[MM], b[MM], m[MM], p[MM];
bool st[MM];
int res = 1e9;

int judge()
{
	memset(jtp, 0, sizeof jtp);
	int mon = 0;
	for(int i = 1; i <= M; i ++)
	{
		if(st[i])
		{
			for(int j = a[i]; j <= b[i]; j ++)
				jtp[j] += p[i]; //加上下降的温度
			mon += m[i]; //加上花销
		}
	}
	for(int i = 1; i <= 100; i ++)
		if(jtp[i] < tp[i]) return -1; //未达到需求，返回
	return mon;
}

void dfs(int step)
{
	if(step > M)
	{
		int com = judge();
		if(com != -1) res = min(res, com);
		return;
	}
	dfs(step + 1); //不选这个空调
	st[step] = true;
	dfs(step + 1); //选这个空调
	st[step] = false;
}

int main()
{
	cin >> n >> M;
	int s, t, c;
	for(int i = 1; i <= n; i ++)
	{
		scanf("%d%d%d", &s, &t, &c);
		for(int j = s; j <= t; j ++)
			tp[j] = max(tp[j], c);
	}
	for(int i = 1; i <= M; i ++)
		scanf("%d%d%d%d", &a[i], &b[i], &p[i], &m[i]);
	dfs(1);
	cout << res << "\n";
	return 0;
}
```

有错误或疑问请评论，谢谢！

---

## 作者：so_find_skind (赞：6)

~~我又来水题解啦。~~

## 题意

别看它写了那么多，但综合起来就一句话：给你 $N$ 个范围，每个范围有一个权值且不重复；再给你 $M$ 个东西，每个东西可以使范围内的点权值减 $p_i$，但要付出 $m_i$ 点代价，求使得所有点的权值均不大于 0 时，最少付出多少代价。

## 思路

不难想象，一个像我一样蒟蒻的人拿到此题时是什么想法，估计一看到就直接~~跳过~~想到一种算法，因为它虽然每个只能用一次而且是在范围内，但只要选不了我们再恢复不就行了，没什么大不了的，所以此算法为：dfs！

有了思路代码就不难写毕竟就一个子集问题板子改一点点而已。

AC Code：

```
#include<bits/stdc++.h>
using namespace std;
int n,m,s[25],t[25],c[25],a[15],b[15],p[15],l[15],ans=0x3f3f3f3f,k[5555];
bool check(){
	for(int i=1;i<=5554;i++){
		if(k[i]>0)
			return false;
	}
	return true;
}
void dfs(int i,int dollar){
	if(i==m+1){
		if(check()){
			ans=min(ans,dollar);
		}
		return;
	}
	dfs(i+1,dollar);
	for(register int j=a[i];j<=b[i];++j){
		k[j]-=p[i];
	}
	dfs(i+1,dollar+l[i]);
	for(register int j=a[i];j<=b[i];++j){
		k[j]+=p[i];
	}
}
int main(){
	cin>>n>>m;
	for(register int i=1;i<=n;++i){
		cin>>s[i]>>t[i]>>c[i];
		for(int j=s[i];j<=t[i];j++)
			k[j]=c[i];
	}
	for(register int i=1;i<=m;++i)
		cin>>a[i]>>b[i]>>p[i]>>l[i];
	dfs(1,0);
	cout<<ans;
	return 0;
}
```

[std](http://usaco.org/current/data/sol_prob2_bronze_jan23.html)（~~弱弱地吐槽一下 std 好复杂~~）

顺便说一句希望把 dfs 加入到算法标签。

---

## 作者：LegendaryGrandmaster (赞：6)

[铜组全部题解](https://www.luogu.com.cn/blog/686297/usaco-2023-cu-ti-xie)

前置芝士：[枚举子集](https://www.luogu.com.cn/problem/B3622)

是的，我们分为**取**和**不取**的情况考虑然后取最小值就行了。

这里用二进制模拟，其实很多方法都可以实现。

可以先把每个单位的牛棚所要的温度加上，如果最后减的话每个单位都比 0 小，那么我们就取最小值。

由于 $m$ 的范围非常小，所以是可以过去的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N],f[N],x[N],n,m;
struct node{
	int l,r,x,t;
}s[N];
string bin(int n,int m)
{
	int x[101],t=0,s=m;
	while(n!=0){
	    x[t]=n%2;
	    t++;
	    n=n/2;
	}
	string st="";
	while(t<s){
		s--;
		st+='0';
	}
    for(int i=t-1;i>=0;i--)st+=char(x[i]+48);
    return st;
}
int main()
{
    cin>>n>>m;
    int L=INT_MAX,R=0;
    for(int i=1;i<=n;i++){
        int l,r,c;
        cin>>l>>r>>c;
        a[l]+=c;
        a[r+1]-=c;
        L=min(L,l);//左边界
        R=max(R,r);//有边界
    }
    //多余的区域是不需要管的。
    for(int i=L;i<=R;i++)f[i]=f[i-1]+a[i];//差分求每一的单位所需减少的温度。
    //for(int i=L;i<=R;i++)cout<<f[i]<<' ';
    for(int i=1;i<=m;i++)cin>>s[i].l>>s[i].r>>s[i].x>>s[i].t;
    int mi=INT_MAX;
    for(int i=0;i<=pow(2,m)-1;i++){
    	for(int j=L;j<=R;j++)x[j]=f[j];
    	string st=bin(i,m);
    	int ans=0;
    	for(int j=0;j<st.size();j++){
    		if(st[j]=='1'){
    			for(int k=s[j+1].l;k<=s[j+1].r;k++)x[k]-=s[j+1].x;
    			ans+=s[j+1].t;
    		}
    	}
    	bool ok=1;
    	//for(int j=L;j<=R;j++)cout<<x[j]<<' ';
    	//puts("");
    	for(int j=L;j<=R;j++)
    		if(x[j]>0){
    			ok=0;
    			break;
    		}
    	if(ok)mi=min(mi,ans);
    }
    cout<<mi;
}
```

---

## 作者：DreamLand_zcb (赞：3)

## 简要题意

有 $N$ 头牛 $M$ 个空调。

第 $i$ 头牛有三个参数 $s_i$，$t_i$，$c_i$，分别表示第 $i$ 头牛所占的位置 $s_i$ 到 $t_i$ 之间必须至少下降 $c_i$ 个温度才能让它感到舒适。

第 $i$ 个空调有四个参数 $a_i$，$b_i$，$p_i$，$m_i$，分别表示第 $i$ 个空调可以让 $a_i$ 到 $b_i$ 之间下降 $p_i$ 个温度，但是要消耗成本 $m_i$ 元。

求让所有奶牛都能舒适的最小成本，题目保证至多开所有空调可以让所有奶牛都舒适（也就是题目保证有解）。

## 思路

可以看到，$N$ 和 $M$ 大小都不大，很经典的 `dfs` 暴力深搜问题，定义参数 `dfs(int pos, int pay)`，其中 `pos` 指当前搜索的是第 `pos` 个空调，`pay` 表示当前成本总数，每次搜索时，如果当前凉度已经满足所有奶牛条件，$ans$ 更新，剪枝；如果不满足条件，当 `pos > N`，剪枝；剩下的就先考虑开这个空调继续搜索、回溯然后考虑不开这个空调继续搜索。

## 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
#define setp setprecision
#define mem(a, m) memset(a, m, sizeof(a));
using namespace std;

int N, M; 
struct cows{
	int s, t, c;
}cow[25];
int cool[105];//Cool[i]：第i个区间降低的温度 (差分)
struct aircondition{
	int a, b, p, m;
}air[15];
int ans=1145141919;

bool check()
{
	for(int i=1;i<=N;i++)
		for(int j=cow[i].s;j<=cow[i].t;j++)
			if(cool[j] < cow[i].c)
				return false;
	return true;
}
void dfs(int pos, int pay)//第p个空调，当前成本总数
{
	/*cout << "第" << pos-1 << "个空调：";
	for(int i=1;i<=10;i++)	cout << cool[i] << " ";
	cout << endl;*/
	if(check())//所有区间都满足条件 
	{
		//cout << pos << endl;
		ans=min(ans, pay);
		return ;
	}
	else if(pos > M)	return ;//没有达到目标，剪枝 
	else//可以继续搜 
	{
		//开这个空调 
		int d[105];
		mem(d, 0);
		d[air[pos].a]+=air[pos].p;
		d[air[pos].b+1]-=air[pos].p;
		for(int i=1;i<=100;i++)	d[i]+=d[i-1];
		for(int i=1;i<=100;i++)	cool[i]+=d[i];
		dfs(pos+1, pay+air[pos].m);
		//不开，回溯
		for(int i=1;i<=100;i++)	cool[i]-=d[i];
		dfs(pos+1, pay);
	}
}
int main()
{
	ios::sync_with_stdio(false);
	mem(cool, 0);
	cin >> N >> M;
	for(int i=1;i<=N;i++)	cin >> cow[i].s >> cow[i].t >> cow[i].c;
	for(int i=1;i<=M;i++)	cin >> air[i].a >> air[i].b >> air[i].p >> air[i].m;
	dfs(1, 0);
	cout << ans;
	return 0;
}
```

---

## 作者：快斗游鹿 (赞：3)

观察数据范围，发现 $M\le10$。这提示我们可以直接暴力枚举开哪些空调。对于每种开空调的方案，按照题意模拟并判断是否可以让所有奶牛都感到舒适即可。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=500;
struct Node{
	int s,t,c;
}e[N];
struct node{
	int a,b,p,m;
}c[N];
struct _Node{
	int a,b,p,m;
}k[N];
int n,m,tot,mp[N],kkk[N],ans=1145141919810;
bool flag[N];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
bool cmp(_Node xxx,_Node yyy){
	if(xxx.a!=yyy.a)return xxx.a<yyy.a;
	return xxx.b<yyy.b;
}
void solve(){//按照题意模拟并判断
	int _ans=0;
	for(int i=1;i<=100;i++)kkk[i]=mp[i];
	for(int i=1;i<=tot;i++){
		for(int j=k[i].a;j<=k[i].b;j++)kkk[j]-=k[i].p;
		_ans+=k[i].m;
	}
	int flag=0;
	for(int i=1;i<=100;i++){
		if(kkk[i]>0)flag=1;
	}
	if(!flag)ans=min(ans,_ans);
}
void dfs(int step){//深搜，枚举所有方案
	if(step==m){
		tot=0;
		for(int i=1;i<=m;i++){
			if(flag[i]){
				k[++tot].a=c[i].a;
				k[tot].b=c[i].b;
				k[tot].m=c[i].m;
				k[tot].p=c[i].p;
			}
		}
		solve();
		return; 
	}
	flag[step+1]=0;
	dfs(step+1);
	flag[step+1]=1;
	dfs(step+1);
}
signed main(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		e[i].s=read();e[i].t=read();e[i].c=read();
		for(int j=e[i].s;j<=e[i].t;j++)mp[j]+=e[i].c;
	}
	for(int i=1;i<=m;i++){
		c[i].a=read();c[i].b=read();c[i].p=read();c[i].m=read();
	}
	dfs(0);
	cout<<ans;
	return 0;
}

```

---

