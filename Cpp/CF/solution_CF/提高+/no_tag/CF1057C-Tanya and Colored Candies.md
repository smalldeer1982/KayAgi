# Tanya and Colored Candies

## 题目描述

Tania 面前有 $n$ 个糖果盒。这些盒子从左到右排成一行，编号为 $1$ 到 $n$。第 $i$ 个盒子里有 $r_i$ 颗糖果，糖果的颜色为 $c_i$（颜色可以是红色、绿色或蓝色三种之一）。每个盒子里的糖果颜色都相同（即为 $c_i$）。

一开始，Tania 站在编号为 $s$ 的盒子旁边。Tania 可以移动到相邻的盒子（即编号相差 $1$ 的盒子），或者吃掉当前盒子里的糖果。Tania 吃糖果是瞬间完成的，但每次移动需要花费 $1$ 秒。

如果 Tania 吃掉某个盒子的糖果，盒子本身还在，但里面的糖果就没有了。换句话说，Tania 总是一次性吃光一个盒子里的所有糖果，且盒子里的糖果不会被补充。

已知 Tania 不能连续吃同一种颜色的糖果（即她连续吃糖果的两个盒子，其糖果颜色必须不同）。此外，Tania 的胃口会不断增长，因此她每次吃的下一个盒子里的糖果数量必须严格多于上一个盒子。

注意，对于 Tania 吃的第一个盒子，没有颜色和糖果数量的限制。

Tania 想要吃至少 $k$ 颗糖果。请问她最少需要多少秒？请记住，Tania 吃糖果不耗时，只有移动才耗时。

## 说明/提示

以第一个样例为例，Tania 的操作顺序如下：

- 从第 $3$ 号盒子移动到第 $2$ 号盒子；
- 吃掉第 $2$ 号盒子的糖果；
- 从第 $2$ 号盒子移动到第 $3$ 号盒子；
- 吃掉第 $3$ 号盒子的糖果；
- 从第 $3$ 号盒子移动到第 $4$ 号盒子；
- 从第 $4$ 号盒子移动到第 $5$ 号盒子；
- 吃掉第 $5$ 号盒子的糖果。

由于 Tania 吃糖果是瞬间完成的，因此所需时间为 $4$ 秒。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 3 10
1 2 3 4 5
RGBRR
```

### 输出

```
4
```

## 样例 #2

### 输入

```
2 1 15
5 6
RG
```

### 输出

```
-1
```

# 题解

## 作者：是个汉子 (赞：3)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1057C)	[CF传送门](http://codeforces.com/problemset/problem/1057/C)

### Description

给定一个长度为 $n$ 的序列，第 $i$ 个点的价值为 $r_i$ ，颜色为R，B，G其中的一种。

你的初始位置是 $s$ ，向左或右移动一步需要花费 $1$ 的时间，但是收集某个点的价值不需要时间。

要求是收集点的时候前后两个点的颜色不一样，并且当前点的价值要大于上一个点。

请问收集价值至少为 $k$ 的最小时间。

### Solution

发现 $n\leq 50$ ，那么可以~~瞎搞~~设计一个DP。

设 $f_{i,j}$ 表示到第 $i$ 个位置收集了 $j$ 的最小时间。

那么，初始状态为 $f_{i,r_i}=|i-s|$ ，转移方程为：
$$
f_{k,j+r_k}=\min_i^{col_i\not =col_k,r_i<r_k}(f_{k,j+r_k},f_{i,j}+|i-k|)
$$
注意：因为是至少 $k$ 的价值，而 $r_i\leq 50$ ，所以要枚举 $1$ 到 $k+50$ 。

### Code

```c++
#include<bits/stdc++.h>

using namespace std;
const int N=110,INF=0x3f3f3f3f;
int n,s,m,ans=INF,r[N],f[N][3010];
char col[N];

int main(){
    scanf("%d%d%d",&n,&s,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&r[i]);
    scanf("%s",ch+1);
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=n;i++)   
        f[i][r[i]]=abs(i-s);
    for(int j=1;j<=m+50;j++)
        for(int i=1;i<=n;i++)
            for(int k=1;k<=n;k++)
                if(col[i]!=col[k]&&r[i]<r[k]) f[k][j+r[k]]=min(f[k][j+r[k]],f[i][j]+abs(i-k));
    for(int i=1;i<=n;i++)
        for(int j=m;j<=m+50;j++)
            ans=min(ans,f[i][j]);
    if(ans==INF) puts("-1");
    else printf("%d\n",ans);
    return 0;
}
```



---

## 作者：wizardMarshall (赞：2)

## 题意

每个地方有不同的糖果数量，每次移到相邻的坐标花费一个代价。每次只能得到较上次个数更多的糖果。而且颜色不能相同。求问至少得到 $k$ 个糖果的最低代价。

形式化题意：（变量名与原题面相同）

找到一个序列 $a_1,a_2\dots a_m$，使得 $\sum ^{m}_{i=1} r_{a_i} \ge k$ 且 $r_{a_i}\ge r_{a_{i-1}} (1 < i \le m)$，并且 $s_{a_i}\ne s_{a_{i-1}} (1 < i \le m)$。

## 思路

不要被原网站的算法标签误导了，虽然动态规划可做但理解可能不太容易。

观察一下 $n$ 的范围，$1\le n\le 50$。并且 $k$ 也不超过 $3 \times 10^3$。因此对于每个坐标开一个当前糖果个数也不会爆内存。

于是就可以开始搜索了。对于当前状态来讲，可以枚举其他的位置，如果符合条件就转移。这里采用类似最短路的算法，将步数少的优先排在前面。

时间复杂度为 $O(nk(\log n + \log k))$。但全部状态其实不会跑满，因为只要搜到一个符合状态的就会跳出。实测跑到了最优解前几个。

## 代码

```c++


#include <bits/stdc++.h>
using namespace std;
int r[55];
char ch[55];
int dp1[55], dp2[55], f[55];
int v[55][3005];
signed main() {
	int n, s, k;
	cin >> n >> s >> k;
	for (int i = 1; i <= n; i++) {
		cin >> r[i];
		for (int j = 0; j <= k + 55; j++) {
			v[i][j] = 1e9;//初始化v数组
		} 
	}scanf("%s", ch + 1);
    
	priority_queue <pair <int, pair <int, int> > > q;//步数，当前位置，总和
	for (int i = 1; i <= n; i++) {//注意起点不一定是s，因为也有可能放到后面才拿
		q.push({-abs(s - i), {i, r[i]}});
		v[i][r[i]] = abs(s - i);
	}
	while (!q.empty()) {
		pair <int, pair <int, int> > f = q.top();q.pop();
		
		f.first = -f.first;
		if (f.second.second >= k) {//按照最短路跑，代价小的一定在前面，因此只要等到第一个符合条件就可以输出
			cout << f.first;
			return 0;
		}
		for (int i = 1; i <= n; i++) {//转移其他的点，代价为abs(i-f)
			if (ch[i] != ch[f.second.first] && r[i] > r[f.second.first]) {//题面条件
				if (f.first + abs(f.second.first - i) < v[i][f.second.second + r[i]]) {
					v[i][f.second.second + r[i]] = f.first + abs(f.second.first - i);
					q.push({-v[i][f.second.second + r[i]], {i, f.second.second + r[i]}});
				}
			}
		}
	}cout << -1;
	return 0;
}


```

---

## 作者：CashCollectFactory (赞：1)

注意到本题的 $n$ 的最大值也只有 $50$，除了动态规划外，我们也可以考虑直接采用暴力搜索来解决这样的问题。

第一种做法是使用优先队列维护广度优先搜索。同时，为了优化搜索的时间复杂度以及空间复杂度，我们需要一个 $vis_i$ 数组来储存局部最优解，当搜索得到的解劣于局部最优解时，就直接放弃该搜索枝。这样，我们得到的第一个解就会是最优解，用时相对较短。

第二种是深度优先搜索。然而，如果没有采用任何效果拔群的剪枝，深度优先搜索得到的第一个解不一定是最优解。所以，我使用了计时器进行了卡时操作。实际上，程序运行 $2\ \text{s}$ 时，得到的答案已经很有可能是最优解了，所以最终也可以顺利通过本题。

具体的代码实现见下方代码：

### 优先队列+广度优先搜索写法：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,k;
int num[100];
string color;
int vis[100][5000]; 
struct node{
	int id;
	int sum;
	int tim;
	bool operator < (const node x) const{
		if(tim==x.tim) return sum<x.sum;
		else return tim>x.tim;
	}//大根堆
	node(int idq,int sumq,int timq){
		id=idq,sum=sumq,tim=timq;
	}//构造函数
};
priority_queue<node> q;
int ans=INT_MAX;
int cnt=1;
int main(){
	for(int i=0;i<100;i++){
		for(int j=0;j<5000;j++){
			vis[i][j]=INT_MAX;
		}
	}
	cin>>n>>s>>k;
	for(int i=1;i<=n;i++){
		cin>>num[i];
	} 
	cin>>color;
	color=" "+color;
	for(int i=1;i<=n;i++){
		q.push(node(i,num[i],abs(s-i)));
	}
	while(!q.empty()){
		
		node nd=q.top();
		q.pop();
//		cout<<"id:"<<nd.id<<" sum:"<<nd.sum<<" tim:"<<nd.tim<<endl;
		if(nd.sum>=k){
			
			ans=min(ans,nd.tim);
			cnt--;
			if(!cnt){
				cout<<ans;
				return 0;
			}
			
		}
		
		for(int i=1;i<=n;i++){
			if(num[i]>num[nd.id] && color[i]!= color[nd.id]){
				if(nd.tim+abs(i-nd.id)<vis[i][nd.sum+num[i]]){
					vis[i][nd.sum+num[i]]=nd.tim+abs(i-nd.id);
					q.push(node(i,nd.sum+num[i],nd.tim+abs(i-nd.id)));
				}
				
			}
		}
	}
	if(ans==INT_MAX) cout<<-1;
	else cout<<ans;
	return 0;
}
```

### 深度优先搜索写法：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,k,ans=INT_MAX; 
int r[100];
string c;
double t0;
void dfs(int id,int sum,int tim){
	if(tim>=ans) return; //可行性剪枝优化

	if((clock()-t0)/CLOCKS_PER_SEC>1.985){
		return; //卡时间
	}
    
	if(sum>=k){
		ans=min(ans,tim);
		return ;
	}
	if(id==0){
		for(int i=1;i<=n;i++){
			dfs(i,sum+r[i],tim+abs(i-s));
		}
		return;
	}
	for(int i=1;i<=n;i++){
		if(r[i]>r[id]&&c[i]!=c[id]) dfs(i,sum+r[i],tim+abs(i-id)) ;
	}
}
int main(){
	t0=clock();
	cin>>n>>s>>k;
	for(int i=1;i<=n;i++) cin>>r[i];
	cin>>c;
	c=" "+c;
  dfs(0,0,0);
	if(ans!=INT_MAX) cout<<ans;
	else cout<<-1;
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1057C)
## 思路
这个题乍一看像是一个状压 $\verb!DP!$，但是，$n \le 50$ 的数据范围不允许我们这么做，稍加分析，发现穿衣服是有规律的。

要么是直接从 $s$ 开始往右穿，要么是从 $s$ 先往左到某个点 $i$，然后从 $i$ 开始往右穿。

$s$ 先往左的情况可以预处理出来，接下来的问题就变成从某个点 $i$ 开始往右穿的最小时间。

不妨设 $f_{i,j}$ 表示穿到第 $i$ 个节点，穿了 $j$ 件衣服的最小时间，转移 $f_{k,j+r[i]}=\min (f_{k,j+r[i]},f_{i,j})$，能转移的条件题目里说明了。

这样就做完了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=5e3+10;
int r[N],f[N][N],ans=9e18;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,s,k;cin>>n>>s>>k;
    memset(f,0x3f,sizeof(f));
    int maxn=f[0][0];
    for (int i=1;i<=n;++i) cin>>r[i],f[i][r[i]]=abs(i-s);
    string co;cin>>co;
    for (int j=0;j<=k+50;++j)
         for (int i=1;i<=n;i++){
            for (int k=1;k<=n;k++)
                if (co[i-1]!=co[k-1] && r[i]<r[k]) f[k][j+r[k]]=min(f[k][j+r[k]],f[i][j]+abs(i-k));
            if (j>=k) ans=min(ans,f[i][j]);
        }
    ans=(ans==maxn)?-1:ans;
    cout<<ans<<'\n';
    return 0;
}
```


---

## 作者：dead_X (赞：0)

## 前言
黑题（迫真）
## 思路
设 $dp_{i,j}$ 为最后一个选择第 $i$ 堆后共穿了 $j$ 件小裙子的方案数。

显然 $dp_{i,j}=\min\limits_{a_k<a_i,s_k\neq s_i}dp_{k,j-a_j}+|i-k|$。

直接暴力 $dp$ 即可，记得决策 $a_i$ 从小到大做（如代码中排序部分），时间复杂度 $O(n^2k)$。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int ans[53][2003],a[53],b[53];
char s[53];
bool cmp(int x,int y){return a[x]<a[y];}
signed main()
{
    int n=read(),sdt=read(),k=read(),Ans=7872754;
    memset(ans,0x3f,sizeof(ans));
    for(int i=1; i<=n; i++) a[i]=read(),b[i]=i;
    scanf("%s",s+1),sort(b+1,b+n+1,cmp);
    for(int i=1; i<=n; i++) 
	{
		for(int j=0,x=b[i]; j<=a[x]; j++) ans[x][j]=abs(x-sdt);
		for(int j=1,x=b[i]; j<=n; j++) 
		if(a[j]<a[x]&&s[j]!=s[x]) for(int dis=abs(x-j),g=k; g>=a[x]; g--) ans[x][g]=min(ans[x][g],ans[j][g-a[x]]+dis);
	}
    for(int i=1; i<=n; i++) Ans=min(Ans,ans[i][k]);
    if(Ans==7872754) Ans=-1;
    printf("%d\n",Ans);
    return 0;
}
```

---

