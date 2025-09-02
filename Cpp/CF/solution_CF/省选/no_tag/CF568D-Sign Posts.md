# Sign Posts

## 题目描述

One Khanate had a lot of roads and very little wood. Riding along the roads was inconvenient, because the roads did not have road signs indicating the direction to important cities.

The Han decided that it's time to fix the issue, and ordered to put signs on every road. The Minister of Transport has to do that, but he has only $ k $ signs. Help the minister to solve his problem, otherwise the poor guy can lose not only his position, but also his head.

More formally, every road in the Khanate is a line on the $ Oxy $ plane, given by an equation of the form $ Ax+By+C=0 $ ( $ A $ and $ B $ are not equal to 0 at the same time). You are required to determine whether you can put signs in at most $ k $ points so that each road had at least one sign installed.

## 说明/提示

Note that you do not have to minimize $ m $ , but it shouldn't be more than $ k $ .

In the first test all three roads intersect at point (0,0).

In the second test all three roads form a triangle and there is no way to place one sign so that it would stand on all three roads at once.

## 样例 #1

### 输入

```
3 1
1 0 0
0 -1 0
7 -93 0
```

### 输出

```
YES
1
1 2
```

## 样例 #2

### 输入

```
3 1
1 0 0
0 1 0
1 1 3
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
2 3
3 4 5
5 6 7
```

### 输出

```
YES
2
1 -1
2 -1
```

# 题解

## 作者：lzqy_ (赞：2)

来个非随机算法。

首先肯定考虑降低 $n$ 的范围。

考虑存在一个 $s(s>k)$ 线共点的情况。若不选择该点，那么至少需要 $s$ 次操作才能覆盖 $s$ 条线段，而这是不可能的。

实现只需要从小到大枚举每一条直线，暴力求出其与其它直线的交点坐标，用 set 存每个交点对应的直线。若某个 set 中元素 $>k$，直接删除该 set 内的直线。

这个方法看上去是 $O(n^2\log n)$，考虑这样做为什么是对的。如果存在 set 要被删除，那么这样的直线个数是 $O(k)$ 的，因为至多删除 $k$ 个set；若不存在 set 要被删除，则该直线一定存在于最终至多只有 $k$ 线共点的图中。而此时的点数上界是 $k^2$ 的，所以这样的直线个数是 $O(k^2)$ 的。

$n \le k^2$ 后 $S={k^2\choose k}$ 的暴力枚举都可以随便碾了。总时间复杂度 $O(k^2n\log n+S)$。

注意精度问题。

```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define ll long long
#define il inline
using namespace std;
const double eps=1e-9;
const int maxn=100010;
il int read(){
	int x=0,f=1;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar())
		if(c=='-')f=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x*f;
}
map<pair<ll,ll>,int>id;
set<int>s[maxn];
struct seg{
	int A,B,C;
	bool fl;
}a[maxn];
pair<ll,ll> cro(seg x,seg y){
	double dx,dy;
	if(!y.A) swap(x,y);
	if(!x.A){
		dy=-1.0*x.C/x.B;
		dx=-1.0*y.B/y.A*dy-1.0*y.C/y.A;
		return mp((ll)(dx*1e8+0.5),(ll)(dy*1e8+0.5));
	}
	dy=(1.0*x.C/x.A-1.0*y.C/y.A)/(1.0*y.B/y.A-1.0*x.B/x.A);
	dx=-1.0*x.B/x.A*dy-1.0*x.C/x.A;
	return mp((ll)(dx*1e8+0.5),(ll)(dy*1e8+0.5));
}
bool para(seg x,seg y){
	if(!x.A&&!y.A) return 1;
	if(!x.B&&!y.B) return 1;
	if(!x.A||!y.A||!x.B||!y.B) return 0;
	if(fabs(x.A*1.0/y.A-x.B*1.0/y.B)<eps) return 1;
	return 0;
}
int n,k,cnt;
int st[maxn],top;
pair<int,int>ans[maxn];
int tot;
void Clear(){
	for(int i=1;i<=cnt;i++) s[i].clear();
	id.clear(),cnt=0;
}
bool chk(int x){
	Clear();
	pair<ll,ll>t;
	for(int i=x+1;i<=n;i++){
		if(!a[i].fl) continue;
		if(para(a[x],a[i])) continue;
		if(!id[t=cro(a[x],a[i])]) id[t]=++cnt;
		s[id[t]].insert(i),s[id[t]].insert(x);
	}
	for(int i=x+1;i<=n;i++){
		if(!a[i].fl) continue;
		if(para(a[x],a[i])) continue;
		if(s[id[t=cro(a[x],a[i])]].size()>k){
			++tot; 
			for(set<int>::iterator it=s[id[t]].begin();it!=s[id[t]].end();it++){
				a[*it].fl=0;
				if(!ans[tot].first) ans[tot].first=*it;
				else if(!ans[tot].second) ans[tot].second=*it;
			}
			return 0;
		}
	}
	return 1;
}
vector<int>v[maxn];
int vis[maxn];
bool dfs(int x,int c){
	if(x==cnt+1) return c==top;
	if(min(k-tot,cnt-x+1)*k<top-c) return 0;
	if(tot==k) return dfs(x+1,c);
	int C=c; tot++;
	for(set<int>::iterator it=s[x].begin();it!=s[x].end();it++){
		if(!(vis[*it]++)) c++;
		if(!ans[tot].first) ans[tot].first=*it;
		else if(!ans[tot].second) ans[tot].second=*it;
	}
	if(dfs(x+1,c)) return 1;
	ans[tot].first=ans[tot].second=0,tot--;
	for(set<int>::iterator it=s[x].begin();it!=s[x].end();it++) vis[*it]--;
	return dfs(x+1,C);
}
void subtask(){
	if(k<n) printf("NO\n");
	else{
		printf("YES\n");
		printf("%d\n",n);
		for(int i=1;i<=k;i++)
			printf("%d -1\n",i);
	}
}
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++){
		a[i].A=read(),a[i].B=read();
		a[i].C=read(),a[i].fl=1;
	}
	bool sub=1;
	for(int i=1;i<n;i++) sub&=para(a[i],a[i+1]);
	if(sub) return subtask(),0;
	for(int i=1;i<=n;i++){
		if(!a[i].fl) continue;
		if(chk(i)) st[++top]=i;
		if(top>k*k||tot>k){
			printf("NO\n");
			return 0;
		}
	}
	Clear(); pair<ll,ll>t;
	for(int i=1;i<=top;i++)
		for(int j=i+1;j<=top;j++){
			if(para(a[i],a[j])) continue;
			if(!id[t=cro(a[i],a[j])]) id[t]=++cnt;
			s[id[t]].insert(i);
			s[id[t]].insert(j);
		}
	k-=tot;
	if(dfs(1,0)){
		printf("YES\n");
		printf("%d\n",tot);
		for(int i=1;i<=tot;i++)
			printf("%d %d\n",ans[i].first,ans[i].second);
	}else printf("NO\n");
	return 0;
}
````

---

## 作者：cwfxlh (赞：1)

# [CF568D](https://www.luogu.com.cn/problem/CF568D)     

发现 $k$ 非常小，于是考虑搜索这 $k$ 个点。但这样显然是不行的，于是考虑优化，如果当前有 $n_0$ 条直线，还能选 $k_0$ 个点，$k_0\ge n_0$ 是简单的。否则占据直线最多的那个点必定覆盖了不少于 $\frac{n_0}{k_0}$ 条直线，而且候选的这种点的个数大概是 $k_0$ 级别的（可能会超但不会超太多）。      

于是对于每一层问题就变成了要搜索出这些候选点，然后枚举选哪个，递归进子问题。因为每个候选点覆盖了不少于 $\frac{n_0}{k_0}$ 条直线，所以随机两条直线的交点判断，随机 $50$ 次左右即可找到所有合法点，对每个点覆盖的直线集合哈希来去重，然后搜索即可。复杂度上限大概是 $O(Cnk!\log n)$，$C$ 是随机次数，实际复杂度很玄学，不过一看就很能过（）。    

代码：     

```cpp
#include<bits/stdc++.h>
#define pi 3.14159265358979323
#define eps 1e-9
using namespace std;
struct Point{
	double X;
	double Y;
	Point(){X=Y=0;}
	Point(double _X,double _Y){X=_X,Y=_Y;}
};
double dis(Point X,Point Y){return sqrt((X.X-Y.X)*(X.X-Y.X)+(X.Y-Y.Y)*(X.Y-Y.Y));}
double _atan(Point X){
	if(fabs(X.X)<eps){if(X.Y>0)return 0.5*pi;return 1.5*pi;}
	if(fabs(X.Y)<eps){if(X.X>0)return 0;return pi;}
	if(X.X<0)return atan(X.Y/X.X)+pi;
	if(X.Y<0)return atan(X.Y/X.X)+2.0*pi;
	return atan(X.Y/X.X);
}
double vec_pro(Point X,Point Y){return (X.Y*Y.X)-(X.X*Y.Y);}
double vec_pro2(Point X,Point Y,Point Z){return vec_pro(Point(Y.X-X.X,Y.Y-X.Y),Point(Z.X-X.X,Z.Y-X.Y));}
double calc_tr(Point X,Point Y,Point Z){return fabs(vec_pro(Point(Y.X-X.X,Y.Y-X.Y),Point(Z.X-X.X,Z.Y-X.Y)))*0.5;}
bool comp1(Point X,Point Y){if(fabs(X.X-Y.X)>eps)return X.X<Y.X;return X.Y<Y.Y;}
bool comp2(Point X,Point Y){return _atan(X)<_atan(Y);}
struct Line{
	double A;
	double B;
	double C;
	Line(){A=B=C=0;}
	Line(double _A,double _B,double _C){A=_A,B=_B,C=_C;}
};
void cnt_build(Line &L,Point X,Point Y){L.A=(Y.Y-X.Y),L.B=(X.X-Y.X),L.C=-L.A*X.X-L.B*X.Y;return;}
void slope_build(Line &L,double _slp,Point X){L.A=-_slp,L.B=1,L.C=-L.A*X.X-L.B*X.Y;return;}
Point get_intsct(Line X,Line Y){return Point((Y.C*X.B-Y.B*X.C)/(Y.B*X.A-X.B*Y.A),(Y.C*X.A-Y.A*X.C)/(Y.A*X.B-X.A*Y.B));}
int n,mk[500003],ans[500003][2],k,flg;
Line L[500003];
Point pt1,pt2,pt3;
int rnd(int l,int r){return ((rand()*1024ll+rand()*41)%(r-l+1))+l;}
map<int,int>mp;
void sol(int now){
	vector<int>abc;
	abc.clear();
	abc.shrink_to_fit();
	for(int i=1;i<=n;i++){
		if(mk[i])continue;
		abc.emplace_back(i);
	}
	if(abc.size()==0){
		cout<<"YES\n";
		cout<<now-1<<endl;
		for(int i=1;i<now;i++)cout<<ans[i][0]<<" "<<ans[i][1]<<endl;
		flg=1;
		return;
	}
	if(now==k+1)return;
	if((k-now+1)>=abc.size()){
		ans[now][0]=abc[0];
		ans[now][1]=-1;
		mk[abc[0]]=1;
		sol(now+1);
		return;
	}
	if(abc.size()==1){
		mk[abc[0]]=1;
		ans[now][0]=abc[0];
		ans[now][1]=-1;
		cout<<"YES\n";
		cout<<now<<endl;
		for(int i=1;i<=now;i++)cout<<ans[i][0]<<" "<<ans[i][1]<<endl;
		flg=1;
		return;
	}
	int cnt=50,v1=0,v2=0,v3=0,v4=0;
	while(cnt--){
		v1=rnd(0,abc.size()-1);
		v2=rnd(0,abc.size()-1);
		while(v1==v2)v2=rnd(0,abc.size()-1);
		v1=abc[v1];
		v2=abc[v2];
		pt1=get_intsct(L[v1],L[v2]);
		v3=v4=0;
		for(auto i:abc){
			if(fabs(L[i].A*pt1.X+L[i].B*pt1.Y+L[i].C)<=eps)v3=((v3*1287ll%998244353)^i),v4++;
		}
		if(v4<(abc.size()/(k-now+1)))continue;
		if(mp[v3]==1)continue;
		mp[v3]=1;
		for(auto i:abc){
			if(fabs(L[i].A*pt1.X+L[i].B*pt1.Y+L[i].C)<=eps)mk[i]=now;
		}
		ans[now][0]=v1;
		ans[now][1]=v2;
		sol(now+1);
		for(auto i:abc)if(mk[i]==now)mk[i]=0;
		if(flg)return;
	}
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>L[i].A>>L[i].B>>L[i].C;
	sol(1);
	if(!flg)cout<<"NO\n";
	return 0;
}
```


---

## 作者：Alex_Wei (赞：1)

### [CF568D Sign Posts](https://www.luogu.com.cn/problem/CF568D)

注意到 $k$ 相当小，考虑爆搜。

存在至少 $\lceil \frac n k\rceil$ 条直线经过同一点。而且当 $n$ 很大时，这样的点很少。关键在于如何找到这些点。随机化即可。随机 $50$ 次选取两条直线，求它们的交点，再求出有多少条直线经过该点。若直线数量小于 $\lceil \frac n k\rceil$ 则直接忽略。否则递归求解即可。注意记忆化，用 XOR-HASH 维护直线编号集合哈希值判重。

$n \gg k$ 时，能递归的点的数量为 $\mathcal{O}(k)$，所以总复杂度为 $\mathcal{O}(nk! C)$，其中 $C$ 是随机次数。但是显然卡不满。[代码](https://codeforces.com/contest/568/submission/210643834)。

优化：选 $k + 1$ 条直线，答案必然包含某两条直线的交。这样省去了随机化。

优化：若大于 $k$ 条直线经过一个点，那么该点一定被选择。随机化的过程中，如果向下递归没有发现解，且大于 $k$ 条直线经过交点，则无解。加入该优化后跑得相当快。

---

