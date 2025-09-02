# Elections

## 题目描述

有n(n<=100)个人,m(m<=100)个投票站,每个投票站对每个人都有一定的票数(<=1000).  
第n个是坏蛋,请问去除掉哪几个投票站才能使他的票数不大于其他每个人中的一个，也就是不能让第n个人的总票数最多。

## 样例 #1

### 输入

```
5 3
6 3 4 2 8
3 7 5 6 7
5 2 4 7 9
```

### 输出

```
2
3 1 
```

## 样例 #2

### 输入

```
2 1
1 1
```

### 输出

```
0

```

## 样例 #3

### 输入

```
3 3
2 3 8
4 2 9
3 1 7
```

### 输出

```
3
1 2 3 
```

# 题解

## 作者：jianhe (赞：4)

[CF1267E Elections](https://www.luogu.com.cn/problem/CF1267E)
题解

### 算法：贪心

先枚举第 $ x $ 位为最终票数超过反叛者的人，然后计算反叛者与第 $ x $ 位在每轮投票中票数之差，再从大到小排序。之后贪心地取差的最大值，将第 $ x $ 位与反叛者票数的差距逐渐缩小，更新答案即可。


### 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=110;
ll n,m,a[N][N],ans=LONG_LONG_MAX,t,p2[N],ct,p[N];
struct Vote{
	ll v,id;
}a2[N];
bool cmp(Vote l,Vote r){
	return l.v>r.v;//按差从大到小排序 
}
ll solve(ll x){
	t=ct=0;
	for(ll i=1;i<=m;i++) a2[i].v=a[i][n]-a[i][x],t+=a2[i].v,a2[i].id=i;
	//数组a2存的是反叛者与第x个人每轮中的票数之差
	//id用来存放投票站编号 
	sort(a2+1,a2+m+1,cmp);//排序 
	while(t>0) t-=a2[++ct].v,p2[ct]=a2[ct].id;//贪心取差的最大值 
	return ct;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++) cin>>a[i][j];
	for(int i=1;i<n;i++){//枚举哪个人票数超过反叛者 
		t=solve(i);
		if(t<ans){
			ans=t;
			for(int j=1;j<=ans;j++) p[j]=p2[j];
			//更新答案 
		}
	}		
	cout<<ans<<"\n";
	for(int i=1;i<=ans;i++) cout<<p[i]<<" ";
	return 0;
}

```

---

## 作者：codeLJH114514 (赞：1)

[原题链接](https://www.luogu.com.cn/problem/CF1267E)  
[CodeForces 链接](https://codeforces.com/problemset/problem/1267/E)

题意：给定一个 $m$ 行 $n$ 列的矩阵 $a$，请问最少删去多少行才能使得在前 $n - 1$ 列中存在某一列的和大于等于第 $n$ 列的和。

数据范围：$1 \leqslant m \leqslant 100, 2\leqslant n \leqslant 100$，$a$ 矩阵中的所有元素非负且不超过 $1000$。

本题数据范围非常小，因此，我们可以考虑对于所有 $1 \leqslant i < n$，求出最少需要删去几行才能使得第 $i$ 列的和大于等于第 $n$ 列的和。然后再取最小值即可。

对于每个 $i$，我们考虑贪心地删去行。具体的，因为删去一行并不会对其他行造成任何影响，每一行都是独立的，所以我们可以直接选择能使第 $i$ 列和第 $n$ 列的和差距变得最小的那一行来进行删除，然后重复进行这个操作。实现时只需先把每一行对 $a(r, i) - a(r, n)$ 进行排序，然后找出在删去第几行的时候才满足题目要求。时间复杂度瓶颈在排序，$\mathcal{O}(m \log m)$。

总时间复杂度：$\mathcal{O}(n) \times \mathcal{O}(m \log m) = \mathcal{O}(n m \log m)$。

C++ 代码：

```cpp
#include <bits/stdc++.h>
#define int long long

constexpr int maxn = 200;
constexpr int infinity = 1145141919810LL;

int n, m;
int a[maxn][maxn];
int bad_votes;

signed main() {
	std::cin >> n >> m;
	
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			std::cin >> a[i][j];
		
	for (int i = 1; i <= m; i++)
		bad_votes += a[i][n]; 
	
	int minimum = infinity;
	std::vector<int> solution;
	
	for (int i = 1; i < n; i++) { // n m log m
		int now_votes = 0;
		for (int j = 1; j <= m; j++)
			now_votes += a[j][i];
		
		std::vector<std::pair<int, int>> stations;
		for (int j = 1; j <= m; j++)
			stations.emplace_back(a[j][i] - a[j][n], j);
			
		int difference = now_votes - bad_votes;
		std::sort(stations.begin(), stations.end(), std::greater<std::pair<int, int>>()); // m log m
		int removed = 0; std::vector<int> nowsolution;
		while (difference < 0) {
			difference -= stations.back().first;
			removed += 1, nowsolution.push_back(stations.back().second);
			stations.pop_back();
		}
		
		if (removed < minimum) {
			minimum = removed;
			solution = nowsolution;
		}
	}
	
	std::cout << minimum << std::endl;
	for (auto i : solution) std::cout << i << " "; 
	
	return 0;
}
```

---

## 作者：nynkqh_yzp (赞：0)

枚举哪一个人超过第 $n$ 个人即可，贪心判断要删掉哪些投票站。即若现在在枚举第 $i$ 个人，优先删除第 $j$ 个投票站，仅当 $a_{j,i}-a_{j,n}$ 最大。若已经超过了第 $n$ 个人，就输出答案。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a[110][110],b[110],ans=0x3f3f3f3f;
struct ac{
	int x,i;
}s[110];
vector<int>f;
int cmp(ac x,ac y){
	return x.x>y.x;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]),b[j]+=a[i][j];
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++)
			s[j].x=a[j][n]-a[j][i],s[j].i=j;
		sort(s+1,s+m+1,cmp);
		if(b[i]>=b[n]){
			ans=0;
			continue;
		}
		for(int j=1;j<=m;j++){
			b[i]+=s[j].x;
			if(b[i]>=b[n])
				if(j<ans){
					f.clear();
					ans=j;
					for(int k=1;k<=j;k++)
						f.push_back(s[k].i);
					break;
				}
		}
	}
	printf("%d\n",ans);
	for(int i=0;i<ans;i++)
		printf("%d ",f[i]);
    return 0;
}
  	 			  		 		    	 		   				 	
```


---

## 作者：gyh20 (赞：0)

枚举最后成为第一的人。判断能否通过操作使他的票数大于$n$号的票数即可。

可以求出每一个投票站的贡献，将复杂度优化至$O(n^2logn)$

代码：

```cpp
#include<cstdio>
#include<algorithm>
#define in inline
#define re register
using namespace std;
in int read() {
	re int t=0;
	re char v=getchar();	
	while(v<'0'||v>'9'){
	v=getchar();
	}	
	while(v>='0'&&v<='9'){		
	t=(t<<3)+(t<<1)+(v^48);		
	v=getchar();	}
	return t;
}
int n,m,ans[102],v[102][102],mn,sum[102];
struct piao{
	int pos,vot;
}q[102];
inline bool cmp(re piao x,re piao y){
	return x.vot>y.vot;
}
int main(){
	n=read();
	m=read();
	mn=0x7fffffff;
	for(re int i=1;i<=m;++i)
		for(re int j=1;j<=n;++j)
			v[i][j]=read(),sum[j]+=v[i][j];
	for(re int i=1;i<n;++i){
		for(re int j=1;j<=m;++j){
		q[j].pos=j;
		q[j].vot=v[j][n]-v[j][i];
		}
		sort(q+1,q+m+1,cmp);
		int tmp=sum[i]-sum[n],tmp1=0;
		while(tmp<0){
			tmp+=q[++tmp1].vot;
		}
		if(tmp1<mn){
			mn=tmp1;
			for(re int j=1;j<=tmp1;++j){
				ans[j]=q[j].pos;
			}
		}
	}
	printf("%d\n",mn);
	for(re int i=1;i<=mn;++i)printf("%d ",ans[i]);
}
```


---

## 作者：子归 (赞：0)

## 贪心
问的是去除那几个投票站.  
### 思路
先对每个人进行处理,使用一个结构体,存下每个投票站给他的票数和给第n个人的票数的差和投票站编号.  
在进行排序,差值从小到大,在倒序判断,加上当前的差值后总差值是否小于0，因为就算当前总差值小于0也可能在之后变为正,所以需要排序之后从大到小求和，如果当前已经为负了，就可以考虑去除这个投票站。因为只要有任意一个严格大于第n个就行了，所以取这n-1个人中需要去掉投票站最少的一个。  
此处可以用vector维护.
### 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll N=105;
int n,m;
struct node{
    int a;
    int b;
}brr[N];
bool comp(node x, node y){
    return x.a<y.a;
}
int arr[N][N];
vector<int> boy[N];
int main() {
	scanf("%d%d",&n,&m);
    for (int i=0;i<m;i++)
        for (int j=0;j<n;j++)
			scanf("%d",&arr[i][j]);
    for (int i=0;i<n-1;i++){
        for (int j=0;j<m;j++){
            brr[j].a=arr[j][i]-arr[j][n-1];
            brr[j].b=j;
        }
        sort(brr,brr+m,comp);
        int val=0;
        for ( int j=m-1;j>=0;j--)
            if (val+brr[j].a>=0)
                val+=brr[j].a;
            else
                boy[i].push_back(brr[j].b);
    }
    int minn=0;
    for(int i=0;i<n-1;i++)
        minn=boy[i].size()<boy[minn].size()?i:minn;
	printf("%d\n",boy[minn].size());
    for(int i=0;i<boy[minn].size();i++)
		printf("%d ",boy[minn][i]+1);
	printf("\n");
}
```


---

