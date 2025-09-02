# 1D Sokoban

## 题目描述

You are playing a game similar to Sokoban on an infinite number line. The game is discrete, so you only consider integer positions on the line.

You start on a position $ 0 $ . There are $ n $ boxes, the $ i $ -th box is on a position $ a_i $ . All positions of the boxes are distinct. There are also $ m $ special positions, the $ j $ -th position is $ b_j $ . All the special positions are also distinct.

In one move you can go one position to the left or to the right. If there is a box in the direction of your move, then you push the box to the next position in that direction. If the next position is taken by another box, then that box is also pushed to the next position, and so on. You can't go through the boxes. You can't pull the boxes towards you.

You are allowed to perform any number of moves (possibly, zero). Your goal is to place as many boxes on special positions as possible. Note that some boxes can be initially placed on special positions.

## 说明/提示

In the first testcase you can go $ 5 $ to the right: the box on position $ 1 $ gets pushed to position $ 6 $ and the box on position $ 5 $ gets pushed to position $ 7 $ . Then you can go $ 6 $ to the left to end up on position $ -1 $ and push a box to $ -2 $ . At the end, the boxes are on positions $ [-2, 6, 7, 11, 15] $ , respectively. Among them positions $ [-2, 6, 7, 15] $ are special, thus, the answer is $ 4 $ .

In the second testcase you can push the box from $ -1 $ to $ -10^9 $ , then the box from $ 1 $ to $ 10^9 $ and obtain the answer $ 2 $ .

The third testcase showcases that you are not allowed to pull the boxes, thus, you can't bring them closer to special positions.

In the fourth testcase all the boxes are already on special positions, so you can do nothing and still obtain the answer $ 3 $ .

In the fifth testcase there are fewer special positions than boxes. You can move either $ 8 $ or $ 9 $ to the right to have some box on position $ 10 $ .

## 样例 #1

### 输入

```
5
5 6
-1 1 5 11 15
-4 -3 -2 6 7 15
2 2
-1 1
-1000000000 1000000000
2 2
-1000000000 1000000000
-1 1
3 5
-1 1 2
-2 -1 1 2 5
2 1
1 2
10```

### 输出

```
4
2
0
3
1```

# 题解

## 作者：CodyTheWolf (赞：1)

可以做到$O(Tn)$


------------

显然可以正负数方向分开讨论，正数：

首先要处理前缀和$sum_i$，表示从$0$开始，能推$sum_i$个箱子过来。这个具体看代码，用两个指针$O(n)$能很轻松完成。

再处理$in_i$，表示从$0$开始一共有$in_i$在推箱子之前已经在他的位置上了

我们枚举每一个位置$i$：

- 我们想再找到一个位置$j$，使得推来的箱子刚好能达到或超过这个点。注意这里推来的箱子不止$sum_i$，而应该是$sum_j$，因为$i$到$j$的箱子也会被推过来，所以应该是$sum_i + (sum_j - sum_i) == sum_j$

- 我们现在就有$sum_j$个箱子，而两点的格子数有$b[j] - b[i] + 1$，如果$b[j] - b[i] + 1 \leq sum_j$就说明$j$这个点合法。

- 显然，这个位置$j$是单调的，因此二分即可。

但是我们再想想，当$i$单调时，$j$肯定也是单调的（积累的箱子会越来越多），所以也是用两个指针就可以维护了

负数边相似，但是注意边界。

```cpp
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <cstring>
using namespace std;

constexpr size_t MAXN = 2e5 + 5;
int a[MAXN], b[MAXN];
int sum[MAXN], in[MAXN];//sum 前缀和，in （已经在位置上的点个数）的前缀和
int T, n, m;

signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> n >> m;
		unordered_set<int> s;
		for (int i = 0; i < m; i++) in[i] = sum[i] = 0;
		for (int i = 0; i < n; i++) cin >> a[i], s.insert(a[i]);
		for (int i = 0; i < m; i++) cin >> b[i], in[i] = (s.count(b[i]) >= 1);
		for (int i = 1; i < m; i++) in[i] += in[i - 1];
		//分别找到a,b负数边开始的点，统计前缀和
		int ta = lower_bound(a, a + n, 0) - a - 1;
		int tb = lower_bound(b, b + m, 0) - b - 1;
		while (tb >= 0) {
			while (ta >= 0 && a[ta] >= b[tb]) sum[tb]++, ta--;
			tb--;
		}
		//分别找到a,b正数边开始的点，统计前缀和
		ta = lower_bound(a, a + n, 0) - a;
		tb = lower_bound(b, b + m, 0) - b;
		while (tb < m) {
			while (a[ta] <= b[tb] && ta < n) sum[tb]++, ta++;
			tb++;
		}
		// b数组中 pos <= posl是负数边 pos >= posr是正数边 
		int posl = lower_bound(b, b + m, 0) - b - 1, posr = posl + 1;
		for (int i = posl - 1; i >= 0; i--) sum[i] += sum[i + 1];
		for (int i = posr + 1; i < m; i++) sum[i] += sum[i - 1];
		int ansl = 0, ansr = 0;
		//处理负数边
		for (int i = posl, mx = posl + 1; i >= 0; i--) {
			while (mx - 1 >= 0 && b[i] - b[mx - 1] + 1 <= sum[mx - 1]) mx--;
			if (mx >= 1)
				ansl = max(ansl, i - mx + 1 + in[mx - 1]);
			else
				ansl = max(ansl, i - mx + 1);
		}
		//处理正数边
		for (int i = posr, mx = posr - 1; i < m; i++) {
			while (mx + 1 < m && b[mx + 1] - b[i] + 1 <= sum[mx + 1]) mx++;
			ansr = max(ansr, mx - i + 1 + in[m - 1] - in[mx]);
		}
		int ans = ansl + ansr;
		cout << ans << '\n';
	}
}
```


---

## 作者：大宝和小宝 (赞：0)

正负的箱子是独立的两部分，我们分开考虑，现在只考虑正的那部分，我们可以枚举第一个箱子推到哪个位置，但是直接枚举的话就无了，其实第一个箱子一定是在特殊点上是最优的。假如不在特殊点上，把整体往右推到特殊点上，此时占据的特殊点个数不会变少，因为我们是完全覆盖后面的区间。至于怎么算当前点后面延申了多少点，发现延申的点是单调递增的，所以没往后多延申一个点就更新一个末尾距离，同时看看能不能再往下碰到其他箱子。

--------
```c
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=2e5+5;
int a[N],b[N],vis[N];
int main(){
	int T; scanf("%d",&T); while(T--){
	int n,m; scanf("%d %d",&n,&m);
	int sta=1,stb=1;
	for(int i=1;i<=n;++i){ 
		vis[i]=0; scanf("%d",&a[i]); 
		if(a[i-1]<0 && a[i]>0){
			sta=i;
		} 
	}
	for(int i=1;i<=m;++i){
		vis[i]=0; 
		scanf("%d",&b[i]); 
		if(b[i-1]<0 && b[i]>0){
			stb=i; 
		} 
	}
	for(int i=1;i<=n;++i){
		int x=lower_bound(b+1,b+m+1,a[i])-b;
		if(b[x]==a[i]) vis[x]=1;
	}
	int ans=0;
	if(a[n]<0 && sta==1) sta=n+1; 
	if(b[m]<0 && stb==1) stb=m+1;
	if(sta>1 && stb>1){
		for(int i=stb;i>=1;--i) vis[i]+=vis[i+1];
		int res=0;
		for(int i=stb-1;i>=1;--i){
			int x=lower_bound(a+1,a+n+1,b[i])-a;
			int num=sta-x;
			int y=lower_bound(b+1,b+m+1,b[i]+num-1)-b;
			int nowans=y-i;
			if(b[y]==b[i]+num-1){
				nowans++;
			}
			res=max(res,nowans+vis[1]-vis[i]);
		}
		ans+=res;
	}
	if(a[n]>0 && b[m]>0){
		for(int i=stb;i<=m;++i){
			vis[i]+=vis[i-1];
		}
		int res=0;
		for(int i=stb;i<=m;++i){
			int x=upper_bound(a+1,a+n+1,b[i])-a-1;
			int num=x-sta+1;
			int y=lower_bound(b+1,b+m+1,b[i]-num+1)-b;
			int nowans=i-y+1;
			res=max(res,nowans+vis[m]-vis[i]);
		}
		ans+=res;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```



---

## 作者：Rui_R (赞：0)

[原题](https://www.luogu.com.cn/problem/CF1494C)

显然正负可以分开处理。下面以正数为例。

最后的状态中，箱子可以分为两部分：从第一个箱子开始到某一个箱子被推到一起，其末段是一个得分点。之后的箱子留在原位。

枚举那一串箱子的末端得分点，那么当前贡献可以分为两部分：那连在一起的箱子所涵盖的得分点数量，以及之后本就在得分点上的箱子数量。

后者可以预处理一个后缀和。

前者可以二分出那一串箱子的最后一个箱子编号，从而得出那一串箱子的数量，算出那一串箱子的起点。接着就可以二分最后一个小于那串箱子起点的得分点位置，从而算出涵盖的得分点数量。

当然要先保证序列有序。

这样可以单次 $O(\log n)$ 计算，总复杂度为 $O(n \log n)$ 。

代码：

```cpp
#pragma GCC optimize(2)

#include <cstdio>
#include <vector>
#include <algorithm>

const int maxn = 2e5 + 5;

template<typename T>
inline T max(const T &a,const T &b){
	return a>b?a:b;
}

struct IO{
	IO(){};char c;
	inline char gc(){
		static char buf[maxn],*p1=buf,*p2=buf;
		return p1==p2&&(p2=(p1=buf)+fread(buf,1,maxn,stdin),p1==p2)?EOF:*p1++;
	}
	template<typename T>
	inline IO&operator>>(T &_){
		_=0;bool f=1;c=gc();while(c<'0'||c>'9'){if(c=='-') f=0; c=gc();}
		while(c>='0'&&c<='9'){_=_*10+c-48;c=gc();}if(!f) _=-_;return *this;
	}
	char buf[maxn];int p = 0;~IO(){fwrite(buf,1,p,stdout);}
	inline void pc(char c){
		buf[p++] = c;
		if(p==maxn) fwrite(buf,1,maxn,stdout),p=0;
	}
	template<typename T>
	inline IO&operator<<(T x){
		if(!x){pc(48);pc('\n');return *this;}static int wt[40],len;len=0;if(x<0){pc('-');x=-x;}
		for(;x;x/=10){wt[++len]=x%10;}
		while(len){pc(wt[len--]+48);}pc('\n');return *this;
	}
}io;

std::vector<int> alpha;std::vector<int> beta;
std::vector<int> v;

int n,m,a[maxn],b[maxn];

int count(){
	v.clear();v.resize(beta.size());
	int answer = 0;
	for(int j=0;j<(int)beta.size();j++){
		std::vector<int>::iterator it = std::lower_bound(alpha.begin(),alpha.end(),beta[j]);
		if(j) v[j] = v[j-1];
		if(it != alpha.end() && *it == beta[j]) v[j] ++ ;
	}
	for(int j=0;j<(int)beta.size();j++){
		int id = std::upper_bound(alpha.begin(),alpha.end(),beta[j]) - alpha.begin();
		// printf("id:%d\n",id);
		if(id == 0) continue ;id -- ;
		int num = id + 1;int st = beta[j] - num + 1;//这样可能看起来好懂一点
		int Id = std::lower_bound(beta.begin(),beta.end(),st) - beta.begin();
		Id -- ;
		answer = max(answer , j - Id + v.back()-v[j]);
	}
	return answer ;
}

int main(){
	int cas;scanf("%d",&cas);
	while(cas--){
		io>>n>>m;
		for(int i=1;i<=n;i++) io>>a[i];
		for(int i=1;i<=m;i++) io>>b[i];
		int answer = 0;
		alpha.clear(),beta.clear();
		for(int i=1;i<=n;i++) if(a[i]<0) alpha.push_back(-a[i]);
		for(int i=1;i<=m;i++) if(b[i]<0) beta.push_back(-b[i]);
		std::reverse(alpha.begin(),alpha.end()),std::reverse(beta.begin(),beta.end());
		answer += count();
		alpha.clear(),beta.clear();
		for(int i=1;i<=n;i++) if(a[i]>0) alpha.push_back(a[i]);
		for(int i=1;i<=m;i++) if(b[i]>0) beta.push_back(b[i]);
		answer += count();
		io << answer ;
	}
	return 0 ;
}


```



---

