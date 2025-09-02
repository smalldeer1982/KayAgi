# Dating

## 题目描述

你是一个约会软件的开发者。该软件有 $ n $ 个用户，编号为 $ 1\sim n $ 。每个用户的都有一个他们喜欢做的活动列表。每个人最多有 $ m $ 个喜欢的活动，编号为 $ 1\sim m $ 。

如果两个用户都喜欢的活动个数 $ \ge1 $ ，并且这两个用户中都各有至少一个自己喜欢而对方不喜欢的活动，那么这两个用户之间就称为是好的匹配。

如果存在好的匹配，请查找匹配项。

## 样例 #1

### 输入

```
3 5
3 1 2 4
5 1 2 3 4 5
2 1 5```

### 输出

```
YES
3 1```

## 样例 #2

### 输入

```
3 3
1 1
1 2
3 2 3 1```

### 输出

```
NO```

# 题解

## 作者：江户川·萝卜 (赞：10)

考虑把每个人看成一个集合 $S_i$，那么题意就是找到 $i,j\in [1,n]\cap\N,i<j$ 使得 $S_i\cap S_j\neq\varnothing\land S_i\not\subseteq S_j\land S_j\not \subseteq S_i$。

对 $S_i$ 按 $|S_i|$ 排序，则只需考虑前两个条件。

从 $1$ 开始枚举 $j$，假设 $1\sim j-1$ 中没有满足条件的集合对，那么对于所有 $1\le x<y\le j-1$，若 $S_x\cup S_y$ 非空，则有 $S_x\subseteq S_y$。

进一步地，对于每种元素 $x$，考虑 $1\sim j-1$ 中每个包含 $x$ 的集合，从后往前形成一条有包含关系的链，我们只需要链上最后一个集合，记编号为 $lst_x$。

$lst$ 序列在任意时刻都满足，对于所有出现在里面的集合编号 $a$，有 $\forall k\in S_a,lst_k=a$。易证。

回到 $S_j$，我们只需记录多重集 $\{lst_x|x\in S_j\}$ 中每个元素的出现次数 $cnt_i$。

- $S_i\cap S_j\neq\varnothing$，即 $cnt_i\neq0$。
- $S_i\not\subseteq S_j$，即 $cnt_i<|S_i|$。

判这两个条件即可。复杂度 $O(\sum|S_i|)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
vector<int> p[200005];
int id[200005],lst[1000005];
int vis[200005];
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int k;cin>>k;p[i].resize(k);
        for(int j=0;j<k;j++) cin>>p[i][j];
    }
    for(int i=1;i<=n;i++) id[i]=i;
    sort(id+1,id+n+1,[=](int x,int y){return p[x].size()<p[y].size();});
    for(int i=1;i<=n;i++){
        int z=id[i];
        vector<int> s;
        for(auto x:p[z]){
            if(!lst[x]){lst[x]=z;continue;}
            if(!vis[lst[x]]) s.push_back(lst[x]);
            vis[lst[x]]++;lst[x]=z;
        }
        for(auto x:s){
            if(vis[x]==p[x].size());
            else{
                cout<<"YES\n"<<z<<' '<<x<<'\n';
                return 0;
            }
            vis[x]=0;
        }
    }
    cout<<"NO\n";
}
```

---

## 作者：gdf_yhm (赞：2)

[CF1949F](https://www.luogu.com.cn/problem/CF1949F)

### 思路

不合法情况要么完全包含要么不交。按 $k_i$ 大小从小到大排序。实时记录每个爱好 $j$ 对应的最后的人 $f_j$。当枚举到 $i$ 时，枚举 $i$ 的每个爱好 $j$，如果最后不合法意味着每个 $f_j$ 的爱好都被 $i$ 完全包含，枚举 $f_j$ 所有爱好判断，否则找到一组解。如果最后不合法，所有 $f_j$ 的爱好数之和为 $k_i$，所以复杂度瓶颈在排序的 $O(n\log n)$。

### code

```cpp
int n,m;
vector<int> a[maxn];
int id[maxn],f[maxn];
bool cmp(int u,int v){return a[u].size()<a[v].size();}
bool vis[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		int x=read();
		while(x--){
			int u=read();
			a[i].push_back(u);
		}
		id[i]=i;
	}
	sort(id+1,id+n+1,cmp);
	for(int i=1;i<=n;i++){
		for(int j:a[id[i]])vis[j]=1;
		for(int j:a[id[i]])if(f[j]!=id[i]){
			if(!f[j])f[j]=id[i];
			else{
				int p=f[j];
				for(int k:a[p]){
					if(!vis[k]){
						printf("YES\n%lld %lld\n",p,id[i]);
						return ;
					}
					f[k]=id[i];
				}
			}
		}
		for(int j:a[id[i]])vis[j]=0;
	}
	printf("NO\n");
}
```

---

