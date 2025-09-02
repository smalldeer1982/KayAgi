# [ABC018D] バレンタインデー

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc018/tasks/abc018_4

あるクラスには女子が $ N $ 人、男子が $ M $ 人いる。女子には $ 1 $ から $ N $ までの出席番号が、男子には $ 1 $ から $ M $ までの出席番号が割り当てられている。

幸運のキューピットはここから女子 $ P $ 人と男子 $ Q $ 人からなる、1 つの旅行グループを作る。

$ N $ 人の女子は合わせて $ R $ 個のチョコレートを持っており、チョコレートには $ 1 $ から $ R $ までの番号が付けられている。

チョコレート $ i\ (1\ ≦\ i\ ≦\ R) $ は出席番号が $ x_i $ である女子が持っており、旅行中に出席番号が $ y_i $ である男子に渡す予定である。そのため旅行グループに出席番号が $ x_i $ である女子と出席番号が $ y_i $ である男子が両方含まれていた場合に限り渡すことができる。無事にチョコレート $ i $ が渡された場合の幸福度は $ z_i $ である。

無事に渡されたチョコレートによる幸福度の合計値として考えられる最大値はいくらか。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ N\ ≦\ 8 $ かつ $ M\ ≦\ 8 $ を満たすデータセット $ 1 $ に正解した場合は、$ 30 $ 点が与えられる。

### Sample Explanation 1

出席番号が $ 1 $, $ 2 $ の女子と出席番号が $ 2 $, $ 3 $, $ 4 $ の男子からなる旅行グループを考えます。 - チョコレート $ 1 $ は出席番号が $ 1 $ の男子が旅行に参加しないため、渡されません。 - チョコレート $ 2 $ は受け渡しする男女がともに旅行に参加するため、無事に渡されます。チョコレートの幸福度は $ 7 $ です。 - チョコレート $ 3 $ は受け渡しする男女がともに旅行に参加するため、無事に渡されます。チョコレートの幸福度は $ 15 $ です。 - チョコレート $ 4 $ は受け渡しする男女がともに旅行に参加するため、無事に渡されます。チョコレートの幸福度は $ 6 $ です。 - チョコレート $ 5 $ は受け渡しする男女がともに旅行に参加するため、無事に渡されます。チョコレートの幸福度は $ 3 $ です。 - チョコレート $ 6 $ は受け渡しする男女がともに旅行に参加するため、無事に渡されます。チョコレートの幸福度は $ 6 $ です。 - チョコレート $ 7 $ は出席番号が $ 3 $ の女子が旅行に参加しないため、渡されません。 幸福度の合計値は $ 7\ +\ 15\ +\ 6\ +\ 3\ +\ 6\ =\ 37 $ となり、これが最大値となります。

## 样例 #1

### 输入

```
3 4 2 3 7
1 1 9
1 2 7
1 3 15
1 4 6
2 2 3
2 4 6
3 3 6```

### 输出

```
37```

## 样例 #2

### 输入

```
4 5 3 2 9
2 3 5
3 1 4
2 2 2
4 1 9
3 5 3
3 3 8
1 4 5
1 5 7
2 4 8```

### 输出

```
26```

# 题解

## 作者：ikunTLE (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc018_4)

### 思路

本题使用 dfs。

首先用类似邻接矩阵的方式存储幸福值，即 $A_{{X_i},{Y_i}}=Z_i$。

然后遍历老师。对于老师，每一个老师有选与不选两种情况，需要做 dfs。做完 $N$ 次遍历后，我们得到了一个表 $V$，其中 $V_i$ 代表第 $i$ 名老师是否参加活动。

随后处理学生。对于所有的学生，对于参加的老师和学生统计出幸福值总数。将得到的序列降序排序，取前 $Q$ 的和与答案取最大值。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=20;
int n,m,e,q,ans,a[N][N],p[N];
bool vis[N];
void dfs(int x,int y){
	if(y>e)
		return;
	if(x>n){
		if(y==e){
			memset(p,0,sizeof(p));
			for(int i=1;i<=n;++i)
				for(int j=1;j<=m;++j)
					p[j]+=vis[i]*a[i][j];
			sort(p+1,p+m+1,greater<int>());
			int sum=0;
			for(int i=1;i<=q;++i)
				sum+=p[i];
			ans=max(ans,sum);
		}
		return;
	}
	vis[x]=true,dfs(x+1,y+1);
	vis[x]=false,dfs(x+1,y);
	return;
}
int main(){
	n=read(),m=read(),e=read(),q=read();
	int r=read();
	while(r--){
		int x=read(),y=read(),z=read();
		a[x][y]+=z;
	}
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Walter_Fang (赞：4)

不要被题目内容所吓倒，这题其实是一道经典的深搜。

我们可以先深搜一边所有老师，当所有老师搜完后，再用一个子函数来遍历一遍学生（避免超时），并将所选中老师和学生的幸福值相加，求出最大，即为答案。

附上带注释的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,p,q,k,i,x,y,z,a[20][20],sum[20],ans,f[20];
//f数组用于计数是否选中老师i。a数组保存学生i，老师j的幸福值。
void check() {
	int s=0,i,j;
	for(i=1; i<=m; i++)sum[i]=0;  //赋初值0
	for(i=1; i<=m; i++)
		for(j=1; j<=n; j++)
			if(f[j])
				sum[i]+=a[j][i];  //计算幸福值
	sort(sum+1,sum+1+m,greater<int>());  //排序，greater参数用于更方便地进行降序排序
	for(i=1; i<=q; i++)s+=sum[i];  //累加
	ans=max(ans,s);  //答案求最大
}
void dfs(int step,int num) {
	if(num>p)return;  //终止条件
	if(step>n) {  //老师遍历完了
		if(num==p)check();  //处理学生
		return ;
	}
	f[step]=1;
	dfs(step+1,num+1);
	f[step]=0;
	dfs(step+1,num);
   //分别遍历选中和不选中两种情况
	return;
}
int main() {
	cin>>n>>m>>p>>q>>k;
	for(i=1; i<=k; i++)cin>>x>>y>>z,a[x][y]+=z;  //a数组计算幸福值
	dfs(1,0);  //深搜
	cout<<ans<<'\n';  //进行输出。注意：AT上的题目输出时必须加换行
   	return 0; //程序结束
}
```

完结撒花~

---

## 作者：lylcpp (赞：2)

## 暴力搜索

当我们发现 $u$ 很小时，就可以直接暴搜。但我们该怎么搜索呢？

因为是教师送给学生礼物，所以我们先搜索老师，记录下来当前这个老师选还是不选。

当我们选完了 $p$ 个老师，学生部分就可以直接算分数。

先枚举每一个老师，如果当前老师选上了，就去枚举学生，在当前这个学生的贡献中加上幸福度。

为了使幸福度最大，所以在算完所有学生的贡献后，我们要对 $m$ 个贡献进行从大到小的排序，最终在得分中加上前 $q$ 个学生的贡献，因为学生就要选 $q$ 个。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

int n, m, p, q, r;
// g: 幸福度，cache: 存学生的贡献 
int g[30][30], cache[30]; 
int a[30]; // 存储每位老师选不选 
int ans;

bool cmp(int x, int y) {
	return x > y;
}

void calc() {
	// 先清空贡献数组 
	memset(cache, 0, sizeof(cache));
	for (int i = 1; i <= n; i++) {
		if (a[i]) { // 选这位老师 
			for (int j = 1; j <= m; j++) { // 遍历学生 
				cache[j] += g[i][j]; // 第 j 位同学加上 g[i][j] 的幸福度 
			}
		}
	}
	sort(cache + 1, cache + m + 1, cmp); // 从大到小排序，最终取前 q 个记为得分 
	int res = 0;
	for (int i = 1; i <= q; i++)
		res += cache[i];
	ans = max(ans, res); // 取最大值 
}

void dfs(int x, int w) { // 暴搜，x: 当前选到第几位老师，w: 选了几位老师
	// 我们可以把每位老师当做一个编号，这样处理起来就比较方便 
	if (w > p) return ; // 超过了 p 个老师，不符合要求 
	if (x == n + 1) { // n + 1 代表第 1 ~ n 位老师都选完了  
		if (w == p) calc(); // 老师总数 = p，符合要求，计算得分 
		return ;
	}
	a[x] = 1; // 选这个老师 
	dfs(x + 1, w + 1);
	a[x] = 0; // 不选这个老师 
	dfs(x + 1, w);
}

int main() {
	scanf("%d%d%d%d%d", &n, &m, &p, &q, &r);
	for (int i = 1; i <= r; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		g[x][y] += z; // 记录幸福度 
	}
	dfs(1, 0);
	printf("%d\n", ans); // 不要忘了换行 
	return 0;
}
``````

---

## 作者：pengziyippp (赞：2)

## 题目大意  
从 $n$ 个老师和 $m$ 个学生中选择 $p$ 个学生和 $q$ 个老师。  
有 $k$ 个礼物，第 $i$ 个礼物由 $x[i]$ 老师送给 $y[i]$ 学生，并且可以获得 $z[i]$ 个幸福度。    
## 思路简述  
一道水水的搜索题目。  
我们用 $a[i][j]$ 表示 $i$ 老师送给 $j$ 学生所上升的幸福度总和。  
$vis[i]$ 表示第 $i$ 个老师选或者不选，不选为 $0$，选了为 $1$。  
$sum[i]$ 表示第 $i$ 个学生与所有老师产生的幸福总值。  
先暴力搜索每个老师的选或者不选，标记在 $vis$ 数组当中，选满 $p$ 个老师。  
当 $n$ 个老师都搜索完后搜索学生。  
由于老师的状态已经确定，故我们可以暴力枚举所有被标记为 $1$ 老师，遍历老师与每个学生产生的幸福价值，并加在每个学生的 $sum$ 数组里。  
最后再将 $sum$ 数组进行逆序排序，取前 $q$ 个学生的 $sum$ 数组的值全部加起来，再每次取总和最大值存在 $ans$ 里。  
每次搜索学生记得要初始化 $sum$ 数组。  
暴搜完，输出 $ans$，结束撒花。   
## 代码实现
具体请见代码。  
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 110;
int a[N][N];
int vis[N];
int sum[N];
int ans = 0;
int n, m, p, q, k;
bool cmp (int a, int b) {
	return a > b;
} // 逆序排序
void check () {
	memset (sum, 0, sizeof(sum)); // 每次暴搜初始化数组
	for (int i = 1; i <= n; i ++ ) {
		if (vis[i]) { // 选择的老师
			for (int j = 1; j <= m; j ++ ) {
				sum[j] += a[i][j]; // 加和
			}
		}
	}
	sort (sum + 1, sum + m + 1, cmp); // 排序
	int tmp = 0;
	for (int i = 1; i <= q; i ++ ) {
		tmp += sum[i];
	} // 取前q大的sum的学生
	ans = max (ans, tmp); // 取最大值
	return;
}
void dfs (int x, int cnt) {
	if (cnt > p) return; // 只选择p个
	if (x == n + 1) { // 选择完了
		if (cnt == p) check(); // 看学生
		return;
	}
	vis[x] = 1; // 标记
	dfs (x + 1, cnt + 1); // 选择
	vis[x] = 0; // 回溯
	dfs (x + 1, cnt); // 不选择
	return;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
    cin >> n >> m >> p >> q >> k;
	for (int i = 1; i <= k; i ++ ) {
		int x, y, z; cin >> x >> y >> z;
		a[x][y] += z; // 计算价值
	} 
	dfs (1, 0); // 暴搜
	cout << ans << "\n";
}
```

---

## 作者：yangyang1000 (赞：1)

暴力搜索即可。

我们用深度优先搜索枚举老师，再用贪心的思想去计算最大的幸福度（计算出每个学生参加带来的幸福值，再排序）。

我们用 $num_{ij}$ 表示第 $i$ 个老师，第 $j$ 个学生带来的幸福值。

然后使用深度优先搜索，将所有老师都搜索完毕后在再去用一个函数来计算盖选择那些学生 （同时深度优先搜索学生会超时）。

没什么思维难度，对代码能力稍有要求。

代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

int n,m,p,q,k,num[20][20],sum[20],ans;
bool x[20];

bool cmp(int a,int b)
{
	return a > b;
}

void calc()
{
	memset(sum,0,sizeof(sum));
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			if(x[j] == true)
				sum[i] += num[j][i];
	
	sort(sum+1,sum+m+1,cmp);
	
	int vg = 0;
	for(int i=1;i<=q;i++) vg += sum[i];
	ans = max(ans,vg);
}

void dfs(int step,int peo)
{
	if(peo > p) return ;
	
	if(step == n + 1)
	{
		if(peo == p) calc();
		return ;
	}
	
	x[step] = true;
	dfs(step+1,peo+1);
	
	x[step] = false;
	dfs(step+1,peo);
	
	return ;
}

int main()
{
	scanf("%d %d %d %d %d",&n,&m,&p,&q,&k);
	for(int i=1;i<=k;i++)
	{
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		num[x][y] += z;
	}
	
	dfs(1,0);
	
	printf("%d",ans);
	return 0;
}
```


---

## 作者：未来姚班zyl (赞：1)

## 题目大意
有 $N$ 个老师、$M$ 个学生和 $K$ 个礼物，一个礼物能被送出当且仅当指定的一名老师和一名学生都参与活动，被送出礼物可以获得指定的幸福度，只可以有 $p$ 名老师和 $q$ 名学生参与活动，最大化总幸福度。

$1\le N,M\le 18$。

## 题目分析

看到如此小的数据，大家都想到了使用 dfs 来暴力枚举老师，然后贪心学生。不过看到这样的数据范围，自然会想到：状态压缩！

方法很简单，用一个共 $N$ 位的二进制数来表示老师的状态，$1$ 表示这一位对应的老师参加活动，否则表示不参加活动。举个例子，如果 $N=4$ ，我枚举的状态是 $0101$，则表示第二个和第四个老师参与活动。那么这样的二进制数就只有 $2^n$ 个了，依次枚举就行。

对于人数限制，我们当然是要选满 $p$ 个老师和 $q$ 个学生，那么对于我们枚举的状态，只需要判断一下 1 的数量是否等于 $p$，是就处理学生，反之直接跳过。如果想不到贪心选择学生的方法，也可以直接 dp。方法是设计状态 $dp_{i,j}$ 表示前 $i$ 个人中，选择 $j$ 个人参加活动，能收获的最大总幸福度。那么对于一个学生，求出 $sum$ 表示选择他能获得的幸福度，这是可以通过直接便历一遍老师计算到的。那么状态转移就是枚举 $j=1\sim q$，$dp_{i,j}=\max{(dp_{i-1,j},dp_{i-1,j-1}+sum)}$。这个也是可以滚动数组优化的，第一维直接扔掉，然后 $j$ 倒着枚举，状态转移就成了 $dp_j=\max{(dp_j,dp_{j-1}+sum)}$。那么最后 $dp_q$ 的值就是当前状态的答案了。

这样省去了 dfs 较为复杂的代码和贪心较为复杂的思路，用简单直接的方法和更为优秀的复杂度 $O(nC_{n}^{p})$ 通过此题。 

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
int n,m,p,q,link[25][25],dp[25],k,ans; 
int lowbit(int x){
	return x&-x;
}
int getbit(int x){
	int ans=0;
	while(x)ans++,x-=lowbit(x);
	return ans;
}
int main(){
	n=read(),m=read(),p=read(),q=read(),k=read();
	for(int i=1,x,y,z;i<=k;i++)x=read(),y=read(),z=read(),link[x][y]=z;
	for(int S=0;S<1<<n;S++){
		int x=getbit(S);
		if(x^p)continue;
		memset(dp,0,sizeof(dp));
		for(int i=1;i<=m;i++){
			int z=0;
			for(int j=1;j<=n;j++)z+=link[j][i]*((S>>(j-1))&1);	
			for(int j=q;j>=1;j--)dp[j]=max(dp[j],dp[j-1]+z);
		}
		ans=max(ans,dp[q]);
	}
	cout <<ans<<endl;
	return 0;
}

```



---

## 作者：封禁用户 (赞：0)

## 前言：
竟然有如此水的绿题。

## 思路：

这是一道非常经典的深搜模板问题。

其实我们可以发现，我们先搜索遍历一下参加的老师，然后把这些老师一一去和学生进行判断，最后记录下总价值，多次进行后再输出 $maxn$ 即可。

## AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N=99;
const long long M=999999;
const long long P=999;
long long n,m,p,q,k,maxn=0,l[N][N],g[M],sum[P];
bool cmp(long long a,long long b)
{
	return a>b;
}
void find()
{
	memset(sum,0,sizeof(sum));
	for(long long i=1;i<=n;i++)
	{
		if(g[i]==1)
		{
			for(long long y=1;y<=m;y++)
			{
				sum[y]+=l[i][y];
			}
		}
	}
	sort(sum+1,sum+1+m,cmp);
	long long ans=0;
	for(long long i=1;i<=q;i++)
	{
		ans+=sum[i];
	}
	maxn=max(maxn,ans);
}
void dfs(long long x,long long w)
{
	if(w>p)
	{
		return;
	}
	if(x>n) 
	{
		find();
		return ;
	}
	g[x]=1;
	dfs(x+1,w+1);
	g[x]=0;
	dfs(x+1,w);
}
int main()
{
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n >> m >> p >> q >> k;
	for(long long i=1;i<=k;i++)
	{
		long long x,y,z;
		cin >> x >> y >> z;
		l[x][y]=z;
	}
	dfs(1,0);
	cout << maxn << endl;
	return 0;
}
``````

---

## 作者：lrb12345 (赞：0)

这题其实就是一个纯纯的深搜模板题。

其实想想就能发现我们先搜索遍历一下参加的老师，然后把这些老师一一去和学生判断，最后记录下价值，多次进行后输出 $\max$ 就行了。

参考代码如下
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m,p,q,k,l[99][99],mx,g[999999],sum[999];
bool cmp(int a,int b){
    return a>b;
}
void find()//判断老师与学生的配对
{
    memset(sum,0,sizeof(sum));
    for(int i=1;i<=n;i++)
    {
        if(g[i]==1)
        {
            for(int y=1;y<=m;y++)
            {
                sum[y]+=l[i][y];
            }
        }
    }
    sort(sum+1,sum+1+m,cmp);
    ll ans=0;
    for(int i=1;i<=q;i++)
    {
        ans+=sum[i];
    }
    mx=max(mx,ans);
}
void dfs(ll x,ll w)//遍历老师
{
    if(w>p)return;
	if(x>n) 
    {
        find();
        return ;
	}
	g[x]=1;
	dfs(x+1,w+1);
	g[x]=0;
	dfs(x+1,w);
}
int main()
{
    cin>>n>>m>>p>>q>>k;
    for(int i=1;i<=k;i++)
    {
        ll x,y,z;
        cin>>x>>y>>z;
        l[x][y]=z;//将老师与学生的配对关系保存，方便后面判断
    }
    dfs(1,0);//遍历老师
    cout<<mx<<endl;//记得换行！！！
}
```

---

## 作者：_AyachiNene (赞：0)

# 思路：
首先看到部分分，$n\leq8$ 且 $m\leq8$。对于这个数据范围，显然枚举学生集合和老师集合，最后算贡献即可。满分的数据范围，$n\leq18$ 且 $m\leq18$，这个数据范围启示我们省略冗余的枚举。考虑只枚举老师集合，对于学生集合，由于学生人数和老师人数无关，也就是说老师的选择对学生的选择没有影响，所以直接贪心选几个加进来能使贡献最大的就行了。
# Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int res=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<1)+(res<<3)+(c^48);c=getchar();}
	return res*f;
}
void write(int x)
{
	if(x<0){x=-x;putchar('-');}
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
int n,m,p,q,k;
int w[1145][1145];
int t[114514],cnt,s[114514];
int ans;
void dfs(int step)
{
	if(step>n)
	{
		if(p<cnt)
			return;
		int res=0;
		memset(s,0,sizeof s);		
		for(int i=1;i<=cnt;i++)
			for(int j=1;j<=m;j++)
				s[j]+=w[t[i]][j];
		sort(s+1,s+m+1);
		for(int i=m;i>max(0,m-q);i--)
			res+=s[i];
		ans=max(ans,res);
		return;
	}
	t[++cnt]=step;
	dfs(step+1);
	--cnt;
	dfs(step+1);
}
int main()
{
	n=read(),m=read(),p=read(),q=read(),k=read();
	for(int i=1;i<=k;i++)
	{
		int x=read(),y=read(),z=read();
		w[x][y]=z;
	}
	dfs(1);
	write(ans),puts("");
}
```


---

## 作者：technopolis_2085 (赞：0)

分析：

先看数据范围。

$n≤18$，$m≤18$。

很明显可以考虑暴力搜索。

可以用 $O(2^n)$ 的复杂度枚举哪些教师去参加活动。

然后我们可以用 dp 来考虑学生的参加情况。

我们令 $dp_{i,j}$ 表示考虑到第 $i$ 名学生，已经有 $j$ 个人参加的最大幸福度。

当第 $i$ 名学生参加时，我们要从 $dp_{i-1,j-1}$ 转移过来，我们已经枚举出了哪些老师参加活动，只需要枚举一下哪些参加了活动的老师会给第 $i$ 名学生送礼物即可。

当第 $i$ 名学生不参加时，我们要从 $dp_{i-1,j}$ 转移过来，此时不需要计算新的幸福度，因为第 $i$ 名学生不参加，因此也不会有新的幸福度。

转移完后，答案为每一种情况下的 $dp_{m,q}$ 的最大值。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=33;
int a[maxn],b[maxn];
int mark[maxn];
int n,m;
int p,q,r;
int ans=0;

int num[maxn][maxn];

void check(){
	int dp[maxn][maxn];
	memset(dp,0,sizeof(dp));
	
	for (int i=1;i<=m;i++){
		for (int j=0;j<=q;j++){
			
			int sum=0;
			for (int x=1;x<=n;x++){
				if (num[x][i]>0&&mark[x]) sum+=num[x][i];
			}
			
			if (j>0) dp[i][j]=max(dp[i][j],dp[i-1][j-1]+sum);
			dp[i][j]=max(dp[i][j],dp[i-1][j]);
			
		}
	}
	
	ans=max(ans,dp[m][q]);
}

void dfs(int dep,int cnt){
	if (dep==n+1){
		if (cnt!=p) return;
		
		check();
		return;
	}
	
	if (cnt+1<=p){
		mark[dep]=1;
		dfs(dep+1,cnt+1);
	}
	
	mark[dep]=0;
	dfs(dep+1,cnt);
}

int main(){
	scanf("%d%d%d%d%d",&n,&m,&p,&q,&r);
	for (int i=1;i<=r;i++){
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		num[x][y]=w;
	}
	
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}
```


---

