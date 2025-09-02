# Milky Days

## 题目描述

### 题目背景
小约翰爱喝牛奶。

他的日记有 $n$ 条记录，表明他在第 $d_i$ 天获得了 $a_i$ 品脱鲜牛奶。牛奶的新鲜度会随着时间的推移而下降，最多可以饮用 $k$ 天。换句话说，在第 $d_i$ 天获得的鲜牛奶在第 $d_i$ 天和第 $d_i+k-1$ 天（含）之间可以饮用。

小约翰每天最多喝 $m$ 品脱牛奶，并且会尽量多喝。如果牛奶少于 $m$ 品脱，他会喝完所有牛奶，但不会感到满足；如果牛奶至少有 $m$ 品脱，他会喝下 $m$ 品脱并感到满足，称这是牛奶满足日。

小约翰总是先喝最新鲜的可饮用牛奶。

请求出小约翰的牛奶满意日的数量。

 _**本题有多组测试数据。**_

## 样例 #1

### 输入

```
6
1 1 3
1 5
2 3 3
1 5
2 7
4 5 2
1 9
2 6
4 9
5 6
5 2 4
4 7
5 3
7 1
11 2
12 1
4 1 3
5 10
9 4
14 8
15 3
5 5 5
8 9
10 7
16 10
21 5
28 9```

### 输出

```
3
3
4
5
10
6```

# 题解

## 作者：Eibon (赞：2)

很套路的考虑，将这些牛奶的信息打入时间轴。

因为要先喝鲜牛奶，所以考虑用一个栈进行维护。

考虑在两次购买牛奶之间，消耗新牛奶的方式是确定的，即从栈顶逐渐往下，待到下一次买牛奶时，再将新牛奶丢到栈顶。

即，我们每次都维护 $d_{i}$ 到 $d_{i+1}-1$ 这一段区间。

每个牛奶只有加入和弹出两次贡献，时间复杂度为 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+5;
const int mod=998244353;
const int inf=0x3f3f3f3f3f3f3f3f;
int T=1,n,m,k,ans;
int d[maxn],a[maxn];
vector<pair<int,int>>sp;
void solve()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	sp.clear();d[n+1]=inf;ans=0;//赋一个大亿点的右端点
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&d[i],&a[i]);
	}
	for(int i=1;i<=n;i++){
		sp.push_back({d[i],a[i]});
		int t=d[i],res=0;
		while(sp.size()){
			int tt=sp.back().first;
			int w=sp.back().second;
			int d1=tt+k-1;//过期时间
			int d2=t+(res+w)/m-1;//被消耗完时间
			int dd=min(min(d1,d2),d[i+1]-1);//最先发生事件时间
			if(d1<t){//下面都过期了
				break;
			}
			if(d[i+1]-1==dd){//没消耗完，到下一次加入新牛奶了
				sp.back()={tt,w+res-(d[i+1]-t)*m};
				ans+=d[i+1]-t;
				break;
			}
			if(d1==dd){//过期了
				res=0;
			}
			else{
				res+=w-(dd-t+1)*m;
			}
			ans+=dd-t+1;
			t=dd+1;
			sp.pop_back();
		}
	}
	printf("%lld\n",ans);
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	scanf("%lld",&T);
	while(T--){
		solve();
	}
	return 0;
}
//dyyyyds
```

---

