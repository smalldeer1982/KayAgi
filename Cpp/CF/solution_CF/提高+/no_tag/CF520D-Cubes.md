# Cubes

## 题目描述

一次，Vasya 和 Petya 用 $m$ 个方块搭建了一个图形。这些方块上被标号为 $0$ 到 $m - 1$。以地面为 $x$ 轴，以垂直向上为正方向建立 $y$ 轴。我们用每个方块左下角的坐标表示它的位置。每个方块的坐标都是整数。

这个图形原本是稳定的。这是指对于每个不是贴在地上的方块，它下方必然存在一个与它相交于一条边或一个角的方块支撑着它。更形式化地说，对于每个方块 $(x, y)$，要么有 $y = 0$，要么存在方块 $(x - 1, y - 1)$，$(x, y - 1)$ 或 $(x + 1, y - 1)$。

现在他们想要拆除这个图形，并吧这些方块一列排开。在一步操作中，一个方块会从图形中被移除，然后被放到已移除的所有方块的最右侧。他们移除方块时，图形仍然是稳定的。

为了使得这个过程更加有意思，Vasya 和 Petya 决定进行如下游戏。他们轮流从图形中取走方块。显然会发现，在图形被完全拆除后，所有方块的编号连起来形成了一个 $m$ 进制的数（可能有前导 $0$）。Vasya 希望这个数尽可能大，而 Petya 正相反，希望这个数尽可能小。Vasya 先手。

你的任务是在两人都采取最优策略的情况下，确定最终形成的数字是多少。输出答案对 $10 ^ 9 + 9$ 取模的结果。

## 样例 #1

### 输入

```
3
2 1
1 0
0 1
```

### 输出

```
19
```

## 样例 #2

### 输入

```
5
0 0
0 1
0 2
0 3
0 4
```

### 输出

```
2930
```

# 题解

## 作者：杨氏之子 (赞：6)

思路：

模拟，用一个大根堆和一个小根堆维护能拆的方块，用 map 维护方块的编号，每次拆一个方块就向周围方块扩展一次，到 Vasya 就从大根堆中取，到 Petya 就从小根堆中取，取出的方块标记为 1 并删除，避免重复


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define mp make_pair

const int mod=1e9+9;

int n,x[100010],y[100010],ans[100010];	//ans统计答案
bool vis[100010];	//标记数组
priority_queue<int> maxi;	//大根堆
priority_queue<int,vector<int>,greater<int> > mini;	//小根堆
map<pii,int> M;	//维护每个方块的编号

bool check(int a,int b){	//判断能不能取出 (a,b) 这个方块，如果它上方或斜上方有方块但旁边没有方块就不能取
	if(M[mp(a,b+1)]&&M[mp(a-1,b)]==0&&M[mp(a+1,b)]==0)
		return 0;
	if(M[mp(a-1,b+1)]&&M[mp(a-1,b)]==0&&M[mp(a-2,b)]==0)
		return 0;
	if(M[mp(a+1,b+1)]&&M[mp(a+1,b)]==0&&M[mp(a+2,b)]==0)
		return 0;
	return 1;
}

void update(int a,int b){	//扩展周围的方块
	if(M[mp(a,b-1)]&&check(a,b-1)){
		maxi.push(M[mp(a,b-1)]);
		mini.push(M[mp(a,b-1)]);
	}
	if(M[mp(a-1,b-1)]&&check(a-1,b-1)){
		maxi.push(M[mp(a-1,b-1)]);
		mini.push(M[mp(a-1,b-1)]);
	}
	if(M[mp(a+1,b-1)]&&check(a+1,b-1)){
		maxi.push(M[mp(a+1,b-1)]);
		mini.push(M[mp(a+1,b-1)]);
	}
	return;
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
		M[mp(x[i],y[i])]=i;	//维护方块编号
	}
	for(int i=1;i<=n;i++)
		if(check(x[i],y[i])){	//初始可行的方块入堆
			maxi.push(M[mp(x[i],y[i])]);
			mini.push(M[mp(x[i],y[i])]);
		}
	for(int i=1;i<=n;i++){
		if(i%2){	//到 Vasya 就从大根堆中取
			ans[i]=maxi.top();
			maxi.pop();
		}
		else {	//到 Petya 就从小根堆中取
			ans[i]=mini.top();
			mini.pop();
		}
		int t=ans[i];
		if(vis[t]||check(x[t],y[t])==0){	//如果已被取出或不能取，跳过
			i--;
			continue;
		}
		vis[t]=1;	//标记
		M.erase(mp(x[t],y[t]));	//删除
		update(x[t],y[t]);
	}
	int s=0,cj=1;
	for(int i=n;i>=1;i--){	//进制转换
		s=(s+(ans[i]-1)*cj%mod)%mod;	//编号为0到n-1，所以ans[i]-1
		cj=cj*n%mod;
	}
	cout<<s;
	return 0;
}
```


---

## 作者：lfxxx (赞：0)

$m$ 进制数最大或者最小，就是让代表其的字符串字典序最大最小，又因为后面的操作放的数所处位数更为靠后，所以每个人的策略都是在当前考虑的这一位尽可能最大或者最小化放的数，考虑将支撑关系连边用一个 set 维护，再用一个 set 维护所有取出后不会使得一个点没有支撑的点，每次取出最大或者最小，计入答案后更新其二级邻域中所有点是否能被取出即可，由于度数是 $O(1)$ 的，所以时间复杂度是 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9+9;
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 1e5+114;
map< pair<int,int> ,int> mp;
int m;
set<int> Out[maxn],In[maxn];
set<int> q;
int x[maxn],y[maxn];
bool check(int u){
	for(int v:Out[u])
		if(In[v].size()==1) return false;
	return true;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>m;
	for(int i=0;i<m;i++){
		cin>>x[i]>>y[i];
		mp[make_pair(x[i],y[i])]=i+1;
	}
	for(int i=0;i<m;i++){
		for(int dx=-1;dx<=1;dx++)
			if(mp[make_pair(x[i]+dx,y[i]+1)]!=0){
				Out[i].insert(mp[make_pair(x[i]+dx,y[i]+1)]-1);
				In[mp[make_pair(x[i]+dx,y[i]+1)]-1].insert(i);
			}
	}
	for(int i=0;i<m;i++){
		if(check(i)==true) q.insert(i);
	}
	int ans=0;
	int tot=0;
	while(q.size()>0){
		int u;
		if(tot==0){
			u=(*q.rbegin());
		}else{
			u=(*q.begin());
		}
		q.erase(u); 
		ans=(ans*m+u)%mod;
		tot^=1;
		for(int v:Out[u]){
			In[v].erase(u);
			for(int w:In[v]){
				if(check(w)==false&&q.find(w)!=q.end()) q.erase(w);
			}
		}
		for(int v:In[u]){
			Out[v].erase(u);
			if(check(v)==true&&q.find(v)==q.end()) q.insert(v);
		}
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

