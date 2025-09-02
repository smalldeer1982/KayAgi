# Arrangement

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dwacon6th-prelims/tasks/dwacon6th_prelims_d

ニワンゴ君は $ N $ 枚のカードを持っています。カードには $ 1,2,\ldots,N $ と番号が振られています。 ニワンゴ君はこれらのカードを一列に並べることにしました。

ニワンゴ君は以下の $ N $ 個の条件の全てを満たすカードの並べ方が存在するかどうかを知りたいです。 ニワンゴ君のためにそのような並べ方が存在するかどうかを判定し、存在する場合は辞書順最小の並べ方を求めてください。

- カード $ 1 $ の右隣のカードは(存在するならば) $ a_1 $ でない
- カード $ 2 $ の右隣のカードは(存在するならば) $ a_2 $ でない
- $ \vdots $
- カード $ N $ の右隣のカードは(存在するならば) $ a_N $ でない

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^{5} $
- $ 1\ \leq\ a_i\ \leq\ N $
- $ a_i\ \neq\ i $

### Sample Explanation 1

\- $ (1,3,2,4) $ よりも辞書順で小さい並べ方は $ (1,2,3,4) $ がありますが、これはカード $ 1 $ の右隣のカードは $ 2 $ でない、という条件に反するため不適切です。

### Sample Explanation 2

\- 条件を満たす並べ方が存在しない場合は `-1` を出力してください。

## 样例 #1

### 输入

```
4
2 3 4 1```

### 输出

```
1 3 2 4```

## 样例 #2

### 输入

```
2
2 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
13
2 3 4 5 6 7 8 9 10 11 12 13 12```

### 输出

```
1 3 2 4 6 5 7 9 8 10 12 11 13```

# 题解

## 作者：MadokaKaname (赞：2)

正好测试一下专栏的题解系统。

~~我省选寄了都怪洛谷/fn/fn/fn/fn/fn/fn/fn~~

[博客园](https://www.cnblogs.com/monster-hunter/p/18068245)

## 题解

显然可以对于所有关系建有向边，显然是基环内向树森林。

由于是字典序最小，因此找到**最小的上一个点没有直接连向边的点**一定最优。

但是有时取最优会导致最后无法选完，我们考虑无法选完的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/azzt6i0p.png)

第一种是剩下一朵菊花，具体如上图，选择 $1$ 之后如果选择 $2$，则只能将菊花非根节点取完而无法取根，此时应该先取根。

![](https://cdn.luogu.com.cn/upload/image_hosting/tlvpwjzy.png)

第二种是剩下一个两个节点的环和一个独立的点，具体如上图，如果在选择 $1$，$3$ 之后选择 $2$，则最后 $4$，$5$ 只能选择一个，此时应该选择 $5$（$4$ 由于 $3$ 指向无法选择）。

全部特判完即可通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
LL to[200005],sum[200005],num[200005];
LL n,i,j,k,m,maxx=0,x,y;
set<LL> st;
bool vis[200005];
int main(){
	scanf("%lld",&n);
	for(i=1;i<=n;i++){
	    scanf("%lld",&to[i]);
	    sum[to[i]]++;
	}
	for(i=1;i<=n;i++){
		maxx=max(maxx,sum[i]);
		num[sum[i]]++;
	}
	if(n==2 && to[1]==2 && to[2]==1){
		printf("-1");
		return 0;
	}
	for(i=2;i<=n;i++)
	  st.insert(i);
	LL now=0,cnt=0,tmp=1;
	while(cnt<n){
		if(now>0){
			if(vis[to[now]]==false){
				num[sum[to[now]]]--;
				num[--sum[to[now]]]++;	
			}
			num[sum[now]]--;
			while(num[maxx]==0) maxx--;
		}
		cnt++;
		if(st.empty()){
			printf("%lld ",tmp);
			return 0;
		}
		if(maxx==(n-cnt)){
			if(sum[tmp]==maxx){
				printf("%lld ",tmp);
				now=tmp;
				vis[tmp]=true;
				tmp=*st.begin();
				st.erase(tmp);
				continue;
			}
			else if(vis[to[tmp]]==false){
				printf("%lld ",to[tmp]);
				now=to[tmp];
				st.erase(to[tmp]);
				vis[to[tmp]]=true;
				continue;
			}
		}
		if(n-cnt==2){
			x=*st.begin(),st.erase(x);
			y=*st.begin(),st.erase(y);
			if(to[tmp]==x && to[x]==tmp){
				if(to[now]==tmp){
					printf("%lld ",x);
					now=x,vis[x]=true;
					st.insert(y);continue;
				}
				else{
					printf("%lld ",tmp);
					now=tmp,vis[tmp]=true;
					tmp=x,st.insert(y);continue;
				}
			}
			if(to[tmp]==y && to[y]==tmp){
				if(to[now]==tmp){
					printf("%lld ",y);
					now=y,vis[y]=true;
					st.insert(x);continue;
				}
				else{
					printf("%lld ",tmp);
					now=tmp,vis[tmp]=true;
					tmp=x,st.insert(y);continue;
				}
			}
			if(to[x]==y && to[y]==x){
				if(to[now]==x){
					printf("%lld ",y);
					now=y,vis[y]=true;
					st.insert(x);continue;
				}
				else{
					printf("%lld ",x);
					now=x,vis[x]=true;
					st.insert(y);continue;
				}
			}
			st.insert(x),st.insert(y);
		}
		if(tmp==to[now]){
			printf("%lld ",*st.begin());
			now=*st.begin();
			vis[*st.begin()]=true;
			st.erase(*st.begin());
		}
		else{
			printf("%lld ",tmp);
			now=tmp;
			vis[tmp]=true;
			tmp=*st.begin();
			st.erase(tmp);
		}
	}
	return 0;
}
```

---

