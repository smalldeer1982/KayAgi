# Hierarchy

## 题目描述

小 $n$ 的公司有 $n$ 个员工，每个员工 $i$ 有一个初始的权值 $q_i$ ，每一个员工有且只有一个上司。 有 $m$ 条申请，每个申请由三个数 $a_i$，$b_i$，$c_i$ 构成，代表将 $a_i$ 任命为 $b_i$ 的上司所需要的花费为$c_i$，同时必须保证 $q_{a_i}>q_{b_i}$。试求使每个员工(顶头上司除外)都有且只有一个上司所花费的最小代价。

## 说明/提示

#### 数据规模与约定

$1 \le n \le 10^3$，$0 \le m \le 10^4$, $0 \le q_i \le 10^6$，$0 \le c_i \le 10^6$，$1 \le a_i,b_i \le n$ 。

## 样例 #1

### 输入

```
4
7 2 3 1
4
1 2 5
2 4 1
3 4 1
1 3 5
```

### 输出

```
11
```

## 样例 #2

### 输入

```
3
1 2 3
2
3 1 2
3 1 3
```

### 输出

```
-1
```

# 题解

## 作者：_Blue_ (赞：8)

### 很简单的一道贪心题  
----------------------  
感觉它就是**Kruskal**去掉了**并查集**。  

题目的意思就是要求我们给**每个人**找**一个**上司，**最大**上司除外。 并且满足上司的工资**大于**部下的工资。
  
想想，Kruskal求最小生成树是怎么做的？  
> 把每条边排序，从短边开始选，用并查集维护关系  
>  
  
这题做法是类似的，我们把m条关系按照代价排序，从**小的**开始处理  
什么时候x能当y的上司呢？  
**当x的工资大于y并且此时y没有上司**  
```cpp
if(!fa[y]&&a[x]>a[y]){
	fa[y]=true;  //标记，y有上司了
	ans+=c;    //记录答案
	num++;     //num记录有几个人找到了上司
}
```

显然，当n-1个人有了上司，就完成了任务。  
如果m个关系都不能满足n-1人有上司，那么输出-1。  
### code： 
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000];
bool fa[1000];
struct node{
	int x,y,c;
}q[10005];
int n,m;
int cmp(node x,node y){
	return x.c<y.c;
}
int ans,num;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&q[i].x,&q[i].y,&q[i].c);
	sort(q+1,q+m+1,cmp);
	for(int i=1;i<=m;i++){
		int x=q[i].x;
		int y=q[i].y;
		int c=q[i].c;
		if(!fa[y]&&a[x]>a[y]){
			fa[y]=true;
			ans+=c;
			num++;
		}
		if(num==n-1){
			break;
		}
	}
    if(num==n-1){
        printf("%d\n",ans);
    }
	else printf("-1\n");
}
```
  

---

## 作者：XiaoyuWan_ (赞：4)

### [题目传送门](https://www.luogu.com.cn/problem/CF17B)

前言：被第三个点坑的看过来。

---

### 思路：

看到题目中的**每一个员工有且只有一个上司**时一开始没太在意，但是实际上这就决定了这个题是**用贪心而不是用一个完全的 Kruskal 去做**，因为只有一个上司，所以说并不需要找好几个爹，相当于 Kruskal 去掉了其中的并查集。

那么整体思路就明了了：先从小的开始处理，**当 $x$ 的工资大于 $y$ 且 $y$ 没有上司时，$x$ 能当 $y$ 的上司**。

这个题还有一个**坑点**（也就是第三个点），必须在循环外面写输出，因为我就是这样错的。

[错的记录](https://www.luogu.com.cn/record/126350217)

[对的记录](https://www.luogu.com.cn/record/126352167)

---

### **code：**
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int a[N], fa[N];
int n, m, ans, cnt;
struct edge
{
	int to;
	int nxt;
	int dis;
}e[N << 5];
bool cmp(edge a1, edge a2)
{
	return a1.dis < a2.dis;
}
bool check(int i)
{
	if (!fa[e[i].nxt] && a[e[i].to] > a[e[i].nxt])
	{
		return true;
	}
	return false;
}
signed main()
{
	scanf("%d", &n);
	for (int i = 1;i <= n;i++)
	{
		scanf("%d", &a[i]);
	}
	scanf("%d", &m);
	for (int i = 1;i <= m;i++)
	{
		scanf("%d%d%d", &e[i].to, &e[i].nxt, &e[i].dis);
	}
	sort(e+1, e+m+1, cmp);
	cnt = n;
	for (int i = 1;i <= m;i++)
	{
		if (check(i))
		{
			fa[e[i].nxt] = true;
			ans += e[i].dis;
			cnt--;
		}
		if (cnt == 1)
		{
			break;
		}
	}
	if (cnt == 1) printf("%d", ans); 
	else printf("-1");
	return 0;
}
```


---

## 作者：FJ_OIer (赞：2)

可以使用类似 kruskal 的贪心策略解题。

先“建边”，$a_i → b_i$ 的权值是 $c_i$。然后把“边”按权值排序，枚举“边”，如果 $a_i$ 要成为 $b_i$ 的上司，首先 $b_i$ 必须还没有安排上司（每个人只能有一个上司），并且 $q_{a_i}>q_{b_i}$。$b_i$ 成为 $a_i$ 的上司同理。
```cpp
#include <bits/stdc++.h>
using namespace std;
struct Edge{
    int u,v,w;
    bool operator<(const Edge &b)const{
        return w<b.w;
    }
}p[10001];
int n,m,ans,cnt;
int a[1001],pa[1001];//记录每个人的上司
void kruskal(){
    sort(p+1,p+m+1);
    for (int i=1;i<=m;i++){
        if (!pa[p[i].v]&&a[p[i].u]>a[p[i].v]){
            ans+=p[i].w;
            cnt++;
            pa[p[i].v]=p[i].u;//标记上司
        }else if (!pa[p[i].u]&&a[p[i].v]>a[p[i].u]){
            ans+=p[i].w;
            cnt++;
            pa[p[i].u]=p[i].v;
        }
    }
    if (cnt<n-1){//没有选出n-1条“边”
        cout<<-1;
        exit(0);
    }
}
int main(){
    cin>>n;
    for (int i=1;i<=n;i++){
        cin>>a[i];
    }
    cin>>m;
    for (int i=1;i<=m;i++){
        cin>>p[i].u>>p[i].v>>p[i].w;
    }
    kruskal();
    cout<<ans;
    return 0;
}
```

---

## 作者：Firstly (赞：1)

这是一道贪心题。

## **题目思路：**

这道题上司与员工的关系其实就像是一个树形结构，一个儿子有且仅有一个父亲。（虽然这样形容可能有点不太恰当……）我们将每一次任命需要的花费从小到大排序，如果员工还没有上司且准上司的权值比他大，那么就正式任命。如果满足要求的任命有 $n-1$ 条及以上，那么就输出答案，否则就不行。

因为本题不需要使用到并查集，所以不需要存储每个员工的上司是谁，只需要判断每个员工是否有上司即可。

## **Code:**

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct edge{
	int u,v,w;
}a[10005];
int n,q[1005],m,tot,ans;
bool vis[1005];
inline bool cmp(edge n1,edge n2){
	return n1.w<n2.w;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>q[i];
	cin>>m;
	for(int i=1;i<=m;i++)cin>>a[i].u>>a[i].v>>a[i].w;
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;i++){
		if(!vis[a[i].v]&&q[a[i].u]>q[a[i].v]){
			vis[a[i].v]=true;
			ans+=a[i].w;
			tot++;
		}
		if(tot==n-1)break;
	}if(tot==n-1)cout<<ans;
	else cout<<-1;
	return 0;
}
```


---

## 作者：lixiao189 (赞：1)

# 毒瘤题目，看上去是一个树形结构题，实际上是一个贪心题！
## 做法： 
由于这个题目说了每个人只有一个上司就够了。所以说只要出现有一个人对被不同的上司雇佣，只要判断取那次雇佣花费最小就可以了。
## 代码（写得很乱）：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

//定义常量
const int N = 1e5+5;

//定义变量
int n,m;
int q[N];
int book[N],mark[N];
int min_ans[N];

int main(){

	for (int i=0;i<N;i++) min_ans[i]=1e7+1;

	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>q[i];
	}

	cin>>m;
	int ans=0;
	int temp_a,temp_b,temp_c;
	for (int i=1;i<=m;i++){
		cin>>temp_a>>temp_b>>temp_c;
		if (q[temp_a]<=q[temp_b]){
			cout<<-1<<endl;
			return 0;
		}
		if (book[temp_b]){
			book[temp_b]++;
			ans-=mark[temp_b];
			ans+=min(mark[temp_b],temp_c);
			mark[temp_b]=min(mark[temp_b],temp_c);
			continue;
		}
		mark[temp_b]=temp_c;
		ans+=temp_c;
		book[temp_b]++;
	}

	int sum=0;
	for (int i=1;i<=n;i++){
		if (book[i]==0){
			sum++;
		}
	}

	//又不只是一组祖先
	if (sum!=1){
		cout<<-1<<endl;
		return 0;
	}

	cout<<ans<<endl;

	return 0;

}
```

---

## 作者：Jin_Yichen (赞：0)

明显是一道贪心题 ~~（太毒瘤了）~~
## 题目大意
小 $n$ 的公司有 $n$ 个员工，每个员工 $i$ 有一个初始的权值 $q_i$ ，每一个员工有且只有一个上司。 有 $m$ 条申请，每个申请由三个数 $a_i$，$b_i$，$c_i$ 构成，代表将 $a_i$ 任命为 $b_i$ 的上司所需要的花费为$c_i$，同时必须保证 $q_{a_i}>q_{b_i}$。试求使每个员工(顶头上司除外)都有且只有一个上司所花费的最小代价。若无解则输出 `-1`。~~好长~~

## 思路分析
用贪心求解。

这道题的上司员工就像树形结构中的父亲和儿子，我们将花费进行排序，如果员工权值没有上司和准上司的权值大，那么就连接这条边。

如果满足要求的边有 $n-1$ 条及以上，那么就输出答案，否则就输出`-1`。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int q[1005],n,m,ans,num;//ans为答案，num为边数
bool f[1005],flag=false;
struct node{
	int a,b,c;//意思见题目
	operator <(const node& a){//排序有用
		return c<a.c;
	}
}x[10005];
int main(){
	scanf("%d",&n)
	for(int i=1;i<=n;i++)scanf("%d",&q[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	scanf("%d%d%d",&x[i].a,&x[i].b,&x[i].c);
   	//输入
	sort(x+1,x+m+1);//排序花费
	for(int i=1;i<=m;i++){
		if(f[x[i].b]==false&&q[x[i].a]>q[x[i].b]){//满足要求就连边
			f[x[i].b]=true;//有边了
			ans+=x[i].c,num++;//边数+1，花费+输入的花费
		} 
		if(num>=n-1)break;//边数大于等于n-1就跳出循环
	}
	if(num>=n-1)printf("%d",ans);//边数大于等于n-1就输出答案
	else puts("-1");//否则就没有答案，输出-1
	return 0;
}
```

---

## 作者：kaceqwq (赞：0)

# 题目大意：
有 $n$ 个员工，每个员工 $i$ 有一个初始的权值 $q_i$，每一个员工有且只有一个上司。 有 $m$ 条申请，由三个数 $a$，$b$，$c$ 构成，代表将 $a$ 任命为 $b$ 的上司所需要的花费为 $c$，同时必须保证 $q_a > q_b$。试求满足所有员工都有一位上司（除顶头上司）所花费的最小代价，若无解输出 -1。

# 分析：
首先根据题意，我们可以发现这道题其实没那么复杂，直接贪心求出最小代价即可。如果遇到冲突，取最小值，最后特判没有上司的人数，因为没有上司的只有顶头上司，所以如果这个人数大于 1，说明无解。

# Code：
```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
int n, m, a[1000005], sum[1000005], num, ans;
signed main() {
	cin >> n;
	for (int i = 1; i <= 10005; i++) sum[i] = 2147483647; //初始化
	for (int i = 1; i <= n; i++) cin >> a[i]; //输入每一个员工的权值
	cin >> m;
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		if (a[x] <= a[y]) { 
        //因为是申请 x 当 y 的上司，如果 y 都比 x 强了，说明无解
			cout << -1 << '\n';
			return 0;
		}
		sum[y] = min(sum[y], z);  //求出每一个人花费的最小代价
	}	
	for (int i = 1; i <= n; i++) {
		if (sum[i] == 2147483647) num++;  //num 表示没上司的人数
		else ans += sum[i];   //算出最小代价的总数
	}
	if (num > 1) cout << -1 << '\n';  //若有大于 1 个人没上司，无解
	else cout << ans << '\n';
	return 0;
}
```


---

## 作者：晨·曦 (赞：0)

### - 题意

有 $n$ 个人，他们分别有一个权值 $q_i$，给出 $m$ 条信息，分别为 $a_i$，$b_i$，$c_i$，即第 $a_i$ 个人可为第 $b_i$ 个人的上司，代价为 $c_i$，但 $q_{a_i}$ 必须**大于**     $q_{b_i}$。

求每个人都**有且仅有**一个上司时（不包括顶头上司），总代价最小。若无解则输出 `-1`。

### - 分析

乍一看，以为是一道最短路的题，但再仔细看一遍，就会发现这道题其实只是**贪心**。

只需要用一个数组存每个人当下属时的最小代价，再累加一遍即可。

### - 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int q[10010],mo[10010]; 
// q为每个人的权值，mo存每个人当下属时的最小代价
int main(){
	for(int i=1;i<=1145;i++) mo[i]=1e9; // 初始化
	int n,m;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>q[i];
	cin>>m;
	for(int i=1;i<=m;i++) {
		int a,b,c;
		cin>>a>>b>>c;
		if(q[a]<=q[b]) { //先判断权值大小
			cout<<-1;
			return 0;
		}
		mo[b]=min(mo[b],c); //存储最小代价
	}
	long long c=0,ans=0; // c为没有上司的人的数量
	for(int i=1;i<=n;i++) {
		if(mo[i]==1e9) c++;
		else ans+=mo[i];
	}
	if(c>=2) { // 因为只有一个顶头上司，所以c大于1时无解
		cout<<-1;
		return 0;
	}
	cout<<ans;
	return 0;
} 
```


---

## 作者：chenpengda (赞：0)

贪心，首先明确一个特点：如果有两个人同时可以成为一个人的上司，那么**选择任命花费小的那个人**，可以使得总花费最小（因为选择花费小的还是大的都不会影响下一步选择的结果）

那么遍历一遍，把每个人的数组存为其上司的最小花费，最后遍历一遍累加花费即可。

$Code$：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q[1005],m,price[1005],a,b,c;//a[10005],b[10005],c[10005];
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		price[i]=1000005;//初始化
		cin>>q[i];
	}
	cin>>m;
	for(int i=0;i<m;i++)
	{
		cin>>a>>b>>c;
		if(q[a-1]>q[b-1])//符合任命条件
		{
			price[b-1]=min(price[b-1],c); //贪心，取最小值
        //price[b-1]存的是给第b个人任命上司的最小花费。
        //这里减去1是因为开始的q[i]是从0开始计数的，你也可以让q[i]从1开始计数。
		}
	}
	int chongfu=0,ans=0;
	for(int i=0;i<n;i++)
	{
		if(price[i]==1000005)//没有被任命上司（这样的人最多有一个）
		{
			chongfu++;
		}
		else ans+=price[i];//累加最小花费
	}
	if(chongfu>1)//因为能力值最大的人不可能有上司，于是chongfu>=1。
	{
		cout<<-1;
	}
	else cout<<ans;
}
```


---

## 作者：封禁用户 (赞：0)

### 前言

吐槽一下题面。。。

没有用 $\LaTeX$ 

笔者已经去反馈了，相信管理很快就会修正。

### 分析

这题目的意思大概就是让你建一棵树，满足父亲的权值大于儿子的权值。

一看这道题目以为是 $\operatorname{kruskal}$ ，但其实认真思考一下，发现上司是只有一位的！

那么也就不需要并查集维护了，但是我们需要一个假的并查集来维护上司是否存在。

然后我们利用 **贪心** 排序一下，因为如果是这样子的话，那么第一次遇见的上司必然是最小值，也就可以维护最小值了。

如何判断不能达成呢？

可以利用一个 $cnt$ 变量来维护边的数量，如果 $cnt \neq n-1$ 那么就证明每个人都不一定会有上司(除了顶层上司)，那么也就可以输出 `-1` 了。

先来一段 伪代码 ：

```cpp

前面是读入;

按照权值大小，sort 排序一下;

for 并查集初始化 fa(i)=i;

for 开始枚举边

if 儿子已经有父亲了 || 儿子的工资小于等于父亲 那么 不连这条边;

边数+1 cnt+1;

ans 加上 权值;

并查集连接;

if 边的数量满足 n-1 条 那么 跳出循环;

判断是否 cnt = n-1 不是输出 -1;

是输出 ans;

```

### 代码

然后就可以愉快地 Code 了！

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int INFN=1e3+5;
const int INFM=1e4+5;
int n,a[INFN],m,fa[INFN],rank_set[INFN],ans;
struct _node_ {
        int x,y,z;
} b[INFM];
__inline__ bool cmp(_node_ x,_node_ y) {
        return x.z<y.z;
}
signed main()
{
        scanf("%d",&n);
        for (int i=1; i<=n; i++)
                scanf("%d",&a[i]);
        scanf("%d",&m);
        for (int i=1; i<=m; i++)
                scanf("%d %d %d",&b[i].x,&b[i].y,&b[i].z);
        sort(b+1,b+1+m,cmp);
        int cnt=0;
        for (int i=1; i<=n; i++) fa[i]=i;
        for (int i=1; i<=m; i++) {
                int x=b[i].x;
                int y=b[i].y;
                if (fa[y]!=y || a[x]<=a[y]) continue;//儿子已经有父亲了 || 儿子的工资小于等于父亲 那么 不连这条边。
                cnt++;//边的数量+1
                ans=ans+b[i].z;//答案更新。
                fa[y]=x;//并查集维护。
                if (cnt==n-1) break;//如果边的数量够了，那么就跳出循环。
        }
        if (cnt!=n-1) printf("-1\n");
        else printf("%d\n",ans);
        //最后判断，是否所有人(除了顶层上司)有没有上司。
        return 0;
}
```

### 写在后面的话

我这篇题解如果有错误，那么请在评论区里留言，我将会很感谢反映的人。

**谢谢观赏！**

---

