# [GCJ 2018 #1B] Transmutation

## 题目描述

你是一个国家中最技艺高超的炼金术士，这个国家认为黄金、铂金和白银等金属毫无趣味，却极为珍视铅。在已知的 $\mathrm{M}$ 种金属中，铅在你的元素周期表上编号为 1。国家的领袖要求你利用国库中的金属，尽可能多地制造铅。

对于每种金属（包括铅），你都知道恰好有一种配方，可以通过消耗两种原料金属各一克来制造该金属一克。（如果你在思考质量守恒定律，另一克会变成无用的废弃物。）配方不能用部分克数操作。然而，只要你有足够的原料，每种配方你都可以使用任意多次（也可以不用）。

如果你做出最优选择，最终你最多能得到多少克铅？注意，操作结束后，可能还会剩下一些非铅金属。

## 说明/提示

**样例解释**

样例 1 中，最优策略是用 2 克 2 号金属和 2 克 3 号金属制造 2 克铅，最终共得到 7 克铅。

样例 2 中，最优策略是先用 2 克 3 号金属和 2 克 5 号金属制造 2 克 4 号金属，然后用 4 克 3 号金属和 4 克 4 号金属制造 4 克铅。注意，可能有两种配方使用相同的两种原料金属（只是炼金术手法不同）。也要注意，并不是每种金属都一定会作为其他配方的原料；在本例中，2 号金属从未作为原料。

样例 3 中，注意某种金属可能可以用来制造自身。（有时候炼金术的规律也很奇怪！）但在本例中无法制造出任何铅。注意，由于配方只能以整数克操作，不能用 0.5 克 2 号金属和 0.5 克 3 号金属制造 0.5 克 4 号金属，再用 0.5 克 3 号金属和 0.5 克 4 号金属制造 0.5 克铅。

**数据范围**

- $1 \leq T \leq 100$。
- 对所有 $i$，$1 \leq \mathbf{R_{i1}} < \mathbf{R_{i2}} \leq M$。

**测试点 1（15 分，可见）**

- $2 \leq M \leq 8$。
- 对所有 $i$，$0 \leq \mathbf{G_i} \leq 8$。

**测试点 2（18 分，隐藏）**

- $2 \leq M \leq 100$。
- 对所有 $i$，$0 \leq \mathbf{G_i} \leq 100$。

**测试点 3（12 分，隐藏）**

- $2 \leq M \leq 100$。
- 对所有 $i$，$0 \leq \mathbf{G_i} \leq 10^9$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
3
2 3
1 3
1 2
5 2 3
5
3 4
3 4
4 5
3 5
1 3
0 8 6 2 4
4
3 4
2 3
2 3
2 3
0 1 1 0```

### 输出

```
Case #1: 7
Case #2: 4
Case #3: 0```

# 题解

## 作者：Aurelia_Veil (赞：5)

# 题解：P13141 \[GCJ 2018 #1B] Transmutation

这道题在校内模拟赛中差点场切，就标记写错了（哭）。

注意到题目：

> 最终你最多能得到多少克铅？

我们大概可以猜出是二分答案。然后我们再次注意到，铅需要的越多，就越不可能完成，于是说明了这就是二分答案，于是我们二分枚举需要的**铅的重量**。代码易写：

```cpp
signed main(){//主函数部分
	int T,tttk=0;
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld%lld",&b[i].x,&b[i].y);
		}
		int sum=0;
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			sum+=a[i];
		}
		int l=a[1],r=sum+12;
		int ans=0;
		while(l<=r){
			int mid=(l+r)/2;
			if(check(mid)){
				ans=mid;
				l=mid+1;
			}else{
				r=mid-1;
			}
		}
		printf("Case #%lld: %lld\n",++tttk,ans);
		for(int i=1;i<=n;i++){
			b[i].x=0;
			b[i].y=0;
			a[i]=0;
		} 
	}
	return 0;
}
```

然后思考如何判断是否可以完成。首先，一个材料如果不够用，就需要同重量的两个材料来合成，于是我们可以使用递归的方式来判断，形参很容易想到，有当前材料和当前材料所需重量，于是基础框架有了：

```cpp
bool dfs(int k,int top){//返回值为是否可以提供该材料
	
}
bool check(int k){
	bool ans=dfs(k,1);
	return ans;
}
```

我们开始分类讨论。如果这个材料能够支持**现在**所需要的重量，直接将当前材料减去所需重量并返回 `true`，代码如下：

```cpp
bool dfs(int k,int top){//a数组为材料目前重量
	if(a[top]>=k){
		a[top]-=k;
		return 1;
	}
	
}
bool check(int k){
	bool ans=dfs(k,1);
	return ans;
}
```

接下来讨论不能支持**现在**所需要的重量的情况，首先先将材料所需量减去当前材料剩下的重量（以物换物），其次将当前材料剩下的重量归零（也就是用完了），然后将现在的材料所需量递归向两个合成材料“**索取**”。最后我们要知道，如果你合成需要的两个材料不够用，也就说明这个材料**无法获得**，于是便**无法合成铅**，反之则继续合成。代码非常容易写：

```cpp
bool dfs(int k,int top){//b数组为当前材料所需的两个材料（结构体）
	if(a[top]>=k){
		a[top]-=k;
		return 1;
	}
	k-=a[top];
	a[top]=0;
	bool flag=dfs(k,b[top].x);
	if(flag==0){
		return 0;
	}
	flag=dfs(k,b[top].y);
	if(flag==0){
		return 0;
	}
	return 1;
}
bool check(int k){
	for(int i=1;i<=n;i++){//记得初始化
		c[i]=a[i];
		v[i]=0;
	}
	bool ans=dfs(k,1);
	for(int i=1;i<=n;i++){//记得还原
		a[i]=c[i];
	}
	return ans;
}
```

但是聪明的你肯定发现了，如果想样例那样自己给自己合成或者像环一样合成，那就会无限递归下去，于是我们要写标记数组。

标记数组非常好写，**在最差情况下**，最多每个元素只需要参与合成 $n$ 次，于是使用标记数组存储当前元素合成次数，如果超过 $n$，直接返回退出**无法合成**，代码很好写：

```cpp
bool dfs(int k,int top){//v数组为标记数组
	if(a[top]>=k){
		a[top]-=k;
		return 1;
	}
	v[top]++;
	if(v[top]>n){
		return 0;
	}
	k-=a[top];
	a[top]=0;
	bool flag=dfs(k,b[top].x);
	if(flag==0){
		return 0;
	}
	flag=dfs(k,b[top].y);
	if(flag==0){
		return 0;
	}
	return 1;
}
bool check(int k){
	for(int i=1;i<=n;i++){
		c[i]=a[i];
		v[i]=0;
	}
	bool ans=dfs(k,1);
	for(int i=1;i<=n;i++){
		a[i]=c[i];
	}
	return ans;
}
```

于是代码就写完了，完整代码如下（[洛谷 AC 记录](https://www.luogu.com.cn/record/230737613)）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=111;
struct pai{
	int x,y;
}b[N];
int a[N],c[N],n;
int v[N];
bool dfs(int k,int top){
	if(a[top]>=k){
		a[top]-=k;
		return 1;
	}
	v[top]++;
	if(v[top]>n){
		return 0;
	}
	k-=a[top];
	a[top]=0;
	bool flag=dfs(k,b[top].x);
	if(flag==0){
		return 0;
	}
	flag=dfs(k,b[top].y);
	if(flag==0){
		return 0;
	}
	return 1;
}
bool check(int k){
	for(int i=1;i<=n;i++){
		c[i]=a[i];
		v[i]=0;
	}
	bool ans=dfs(k,1);
	for(int i=1;i<=n;i++){
		a[i]=c[i];
	}
	return ans;
}
signed main(){
	int T,tttk=0;
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld%lld",&b[i].x,&b[i].y);
		}
		int sum=0;
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			sum+=a[i];
		}
		int l=a[1],r=sum+12;
		int ans=0;
		while(l<=r){
			int mid=(l+r)/2;
			if(check(mid)){
				ans=mid;
				l=mid+1;
			}else{
				r=mid-1;
			}
		}
		printf("Case #%lld: %lld\n",++tttk,ans);
		for(int i=1;i<=n;i++){
			b[i].x=0;
			b[i].y=0;
			a[i]=0;
		} 
	}
	return 0;
}
```

求点赞谢谢捏。

---

## 作者：LastKismet (赞：1)

# Sol
直接算的话不太方便，考虑二分答案。

从点 $1$ 开始，如果已经超过要求的值，那么显然有解。否则，就需要从原料那里贡献，如果两个原料中存在至少一个正在等待当前点贡献，也就是形成了一个环，那么显然是无解的。

那么要求两个原料至少有当前点仍需要的值，直接递归子问题求解即可，由于不存在环，每个点至多被其余每个点要求贡献一次（事实上远远达不到这个上限），复杂度大致为 $O(n^2)$。具体实现细节可以参见代码，很暴力也很简单。

最后复杂度是 $O(Tn^2\log V)$ 的。

# Code
```cpp
const int N=105;

int n;
int a[N],b[N];
ll c[N];
ll  g[N];
bool ins[N];

bool check(ll m,int x=1){
    ins[x]=1;
    if(g[x]>=m){
        g[x]-=m;
        ins[x]=0;
        return 1;
    }
    m-=g[x],g[x]=0;
    if(ins[a[x]]||ins[b[x]])return 0;
    if(!check(m,a[x])||!check(m,b[x]))return 0;
    ins[x]=0;
    return 1;
}

inline void Main(){
    read(n);
    rep(i,1,n)read(a[i],b[i]);
    ll l=0,r=0;
    rep(i,1,n)read(c[i]),r+=c[i];
    l=c[1];
    while(l<r){
        ll m=l+r+1>>1;
        rep(i,1,n)g[i]=c[i],ins[i]=0;
        if(check(m))l=m;
        else r=m-1;
    }
    put(l);
}
int main(){
    int tt=0;
	#define MultiTasks
	#ifdef MultiTasks
	int t;read(t);while(t--)
	#endif
	put("Case #",0),put(++tt,0),put(": ",0),Main();
	return 0;
}
```

---

