# Field Division (easy version)

## 题目描述

这是该问题的简单版本；它与困难版本的区别仅在于问题本身。简单版本只需要你判断某些值是否为非零。困难版本则需要你输出确切的数值。

Alice 和 Bob 正在分割一块田地。这块田地是一个 $n \times m$ 的矩形（$2 \le n, m \le 10^9$），行从上到下编号为 $1$ 到 $n$，列从左到右编号为 $1$ 到 $m$。第 $r$ 行第 $c$ 列的格子记为 $(r, c)$。

Bob 有 $k$ 个喷泉（$2 \le k \le 2 \cdot 10^5$），它们都位于田地中不同的格子里。Alice 负责分割田地，但她必须满足以下几个条件：

- 分割田地时，Alice 会从田地左侧或上侧的任意一个没有喷泉的格子出发，每次只能向下或向右移动到相邻的格子。她的路径将在田地的右侧或下侧结束。
- Alice 的路径会将田地分成两部分——一部分归 Alice 所有（包括她路径上的所有格子），另一部分归 Bob 所有。
- Alice 拥有包含格子 $(n, 1)$ 的那一部分。
- Bob 拥有包含格子 $(1, m)$ 的那一部分。

Alice 希望分割田地，使她获得尽可能多的格子。

Bob 希望保留所有喷泉的所有权，但他可以把其中一个喷泉让给 Alice。首先，输出整数 $\alpha$——如果 Bob 不让出任何喷泉（即所有喷泉都归 Bob 所有），Alice 所能获得的最大田地面积。然后输出 $k$ 个非负整数 $a_1, a_2, \dots, a_k$，其中：

- 如果 Bob 把第 $i$ 个喷泉让给 Alice 后，Alice 所能获得的最大田地面积没有增加（即仍为 $\alpha$），则 $a_i=0$；
- 如果 Bob 把第 $i$ 个喷泉让给 Alice 后，Alice 所能获得的最大田地面积增加了（即大于 $\alpha$），则 $a_i=1$。

## 说明/提示

以下是第二个样例的图片说明：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1980F1/50ede57a92b2f87fd310741ab01efa95ca5a8eab.png) 喷泉的编号用绿色标注。属于 Alice 的格子用蓝色标记。注意，如果 Bob 把喷泉 $1$ 或喷泉 $3$ 让给 Alice，那么该喷泉不能出现在 Alice 的田地里。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
2 2 3
1 1
1 2
2 2
5 5 4
1 2
2 2
3 4
4 3
2 5 9
1 2
1 5
1 1
2 2
2 4
2 5
1 4
2 3
1 3
6 4 4
6 2
1 3
1 4
1 2
3 4 5
2 1
3 2
1 4
1 3
2 4```

### 输出

```
1
1 0 1 
11
0 1 0 1 
1
0 0 1 1 0 0 0 0 0 
6
1 0 0 0 
1
1 1 0 0 0```

# 题解

## 作者：banned_gutongxing (赞：5)

## 思路
因为这道题有两个维度。考虑按照横坐标排序。

然后发现每一个纵坐标前面不能存在比它还小的坐标，不然是走不通的。

考虑单调栈维护纵坐标。最后求答案的话直接当前的横坐标减去前一个的横坐标乘以纵坐标就行。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5+10;
stack<pair<int,pair<int,int>>> st;
int T,n,m,k;
int ans[MAXN];
struct node{
	int x,y,id;
}a[MAXN];
bool cmp(node a,node b){
	return a.x==b.x?a.y<b.y:a.x<b.x;
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld%lld",&n,&m,&k);
		while(!st.empty()) st.pop();
		for(int i = 1;i<=k;i++){
			scanf("%lld%lld",&a[i].x,&a[i].y);a[i].id = i;
		}
		sort(a+1,a+1+k,cmp);
//		int anss = 0;
		for(int i = 1;i<=k;i++){
			if(a[i].x==a[i-1].x) ans[a[i].id] = 0;
			else{
				while(!st.empty()&&st.top().second.second>=a[i].y){
					ans[st.top().first] = 0;
					auto tmp = st.top();
					st.pop();
				st.push({a[i].id,{a[i].x,a[i].y}});
				ans[a[i].id] = 1;
			}
		}
		int anss = 0;
		st.push({0,{n,m+1}});
		while(!st.empty()){
			auto tmp = st.top();
			st.pop();
			if(st.empty()){
				anss += tmp.second.first*(tmp.second.second-1); 
			}else{
				anss += (tmp.second.first-st.top().second.first)*(tmp.second.second-1);
			}
		}
		printf("%lld\n",anss);
		for(int i = 1;i<=k;i++){
			printf("%lld ",ans[i]);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：FiraCode (赞：2)

这能绿？

由于 Alice 的路线不能往回走，所以他走的路线一定是这样的（红色是喷泉）：

![](https://cdn.luogu.com.cn/upload/image_hosting/ebl8wrmn.png)

那么我们发现，只有移走拐点且最小值变小后才会增加。

那么我们考虑维护后缀 $\min$，然后对于 $x$ 相同的点，若哪一个 $y$ 会使当前 $\min$ 变小，那么移走这个点；若有多个 $y$ 会使 $\min$ 变小，那么取使 $\min$ 变小最多的那个 $y$。

然后这一段路程就是当前 $\min$ 乘这段路程的长度 $x_i-x_{i-1}(x_i \not= x_{i-1})$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int T;
int n, m, k;
array<int, 3> a[200010];
int is[200010];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &k);
		for (int i = 1; i <= k; ++i) scanf("%d%d", &a[i][0], &a[i][1]), a[i][2] = i;

		sort(a + 1, a + 1 + k);
		ll minn = m + 1;
		ll sum = (minn - 1) * (n - a[k][0]);
		for (int i = k; i >= 1; --i) {
			int id = 0;
			if (a[i][1] < minn) id = a[i][2];
			minn = min(minn, 1ll * a[i][1]);
			while (i - 1 >= 1 && a[i - 1][0] == a[i][0]) {
				if (a[i - 1][1] < minn) id = a[i - 1][2];
				minn = min(minn, 1ll * a[i - 1][1]);
				--i;
			}

			sum += 1ll * (minn - 1) * (a[i][0] - a[i - 1][0]);

			is[id] = true;
		}

		printf("%lld\n", sum);
		for (int i = 1; i <= k; ++i) printf("%d ", (int)is[i]);
		puts("");
		for (int i = 1; i <= k; ++i) is[i] = 0;
	}
	return 0;
}
```

---

## 作者：ATION001 (赞：1)

### 思路
我一开始的思路其实是暴力判断，但是：$1\le n,m\le 10^9$，显然行不通。

于是考虑将喷泉的位置作为切入点做这道题。

发现对于第 $j$ 列及以后能不能取走取决于之前的列中有没有喷泉。

将喷泉位置按照横坐标排序，如果这个喷泉纵坐标前面存在比它小的纵坐标，说明这个位置不可取。

但是我们是按照横坐标进行排序的，不能直接判断。

考虑拿单调栈维护纵坐标，如果发现现在的喷泉比前面的喷泉的纵坐标要大的话，那么前面的那个喷泉即使 Bob 给了 Alice 也无法增加 Alice 拥有的田地数。

![](https://cdn.luogu.com.cn/upload/image_hosting/rx9271mz.png)

比如在位置 $(2,5)$ 的喷泉，虽然横坐标小于 $(3,3)$，但是 $(3,3)$ 依然在 $(2,5)$ 的前面（从列的角度出发），所以田地宽度只能是 $2$，不能是 $4$。

然后现在需要解决的问题是：怎么计算面积。

直接拿当前的横坐标减去前一个的横坐标乘上纵坐标 $-1$。

这么说可能抽象了一点，图示：

![](https://cdn.luogu.com.cn/upload/image_hosting/ca9oexu1.png)

假设上一个喷泉的位置为 $(x,y)$，现在的喷泉位置为 $(x',y')$。

那么能获得的面积是：$(x'-x)\times y'$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,m,k;
pair<pair<int,int>,int>a[200005];
stack<pair<pair<int,int>,int>>st;
bool ans[200005];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		fill(ans,ans+k+1,false);
		int sum=0;
		for(int i=1;i<=k;i++){
			cin>>a[i].first.first>>a[i].first.second;
			a[i].second=i;
		}
		sort(a+1,a+k+1);
		for(int i=1;i<=k;i++){
			if(a[i].first.first==a[i-1].first.first){
				ans[a[i].second]=false;
			}else{
				while(st.size()&&st.top().first.second>=a[i].first.second){
					ans[st.top().second]=false;
					st.pop();
				}
				st.push(a[i]);
				ans[a[i].second]=true;
			}
		}
		st.push({{n,m+1},0});
		while(st.size()){
			auto p=st.top();
			st.pop();
			if(st.size()){
				sum+=((p.first.first-st.top().first.first)*(p.first.second-1));
			}else{
				sum+=(p.first.first*(p.first.second-1));
			}
		}
		cout<<sum<<'\n';
		for(int i=1;i<=k;i++){
			cout<<ans[i]<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```

---

