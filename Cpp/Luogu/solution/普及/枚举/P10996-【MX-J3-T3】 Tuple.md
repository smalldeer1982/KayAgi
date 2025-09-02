# 【MX-J3-T3】 Tuple

## 题目背景

原题链接：<https://oier.team/problems/J3D>。

## 题目描述

你有 $m$ 个三元组 $(u_i,v_i,w_i)$，保证 $1\le u_i<v_i<w_i\le n$ 且三元组两两不同。有多少组 $(a,b,c,d)$ 满足 $1\le a<b<c<d\le n$，且在这 $m$ 个三元组当中，存在四个三元组 $(a,b,c),\allowbreak (a,b,d),\allowbreak (a,c,d),\allowbreak (b,c,d)$？

## 说明/提示

**【样例解释 #1】**

有 $(1,2,3,4),(3,4,5,6),(1,2,3,7)$ 符合题意。

**【数据范围】**

|测试点编号|$n\le$|$m\le$|特殊性质|
|:-:|:-:|:-:|:-:|
|$1,2$|$20$|$100$||
|$3\sim 5$|$80$|$10^3$||
|$6\sim 8$|$2000$|$10^4$||
|$9\sim 12$|$300$|$5\times 10^4$|三元组随机均匀生成|
|$13\sim 17$|$300$|$5\times 10^4$||
|$18$|$2000$|$5\times 10^4$|$u_i=1$|
|$19\sim 25$|$2000$|$5\times 10^4$||

对于全体数据，保证 $4\le n\le 2000$，$4\le m\le 5\times 10^4$。

## 样例 #1

### 输入

```
7 11
1 2 3
2 3 4
1 3 4
1 2 4
3 4 5
4 5 6
3 5 6
3 4 6
1 2 7
2 3 7
1 3 7
```

### 输出

```
3
```

## 样例 #2

### 输入

```
9 30
1 2 3
1 2 5
1 2 6
1 3 4
1 3 5
1 3 6
1 3 7
1 3 8
1 3 9
1 4 5
1 4 6
1 4 9
1 7 9
2 3 4
2 3 5
2 3 6
2 3 7
2 3 8
2 3 9
2 4 9
2 5 8
2 6 7
2 7 9
3 4 5
3 4 8
3 4 9
3 5 9
3 7 8
3 7 9
3 8 9
```

### 输出

```
7```

# 题解

## 作者：yummy (赞：14)

# C. Tuple 官方题解

本题考察的主要知识点：

- 【1】枚举法
- （yummy 做法）【4】vector
- （yummy 做法）【4】指针

## 暴力做法

### 20 分

枚举四个点 $a,b,c,d$，检查四个三元组是否都存在。

时间复杂度 $O(n^4)\sim O(n^4 m)$ 不等，取决于你使用 `vector`、`set` 还是 `unordered_set` 存储所有的边。后两者不在 J 组考纲内，所以有一个办法使用 `bool` 数组解决。

如果我们开一个数组 $ex_{b,c,a}$ 表示 $(a,b,c)$ 是否存在，那么空间复杂度为 $O(n^3)$，但是大部分 $ex_{x,y}$ 都是全空的，非常浪费。我们可以开一个 `bool *ex[2005][2005];`，然后某条 $(a,b,c)$ 加入时，如果 `ex[a][b]` 已经存在就把 `ex[b][c][a]` 设成 $1$，如果不存在就先 `new` 一个。

这样一共只有 $m$ 个 `bool[2005]` 真实存在，空间复杂度 $O(nm)$。

### 32 分

枚举两条边 $p,q$，判断 $p,q$ 是否拥有相同的 $u,v$（记为 $a,b$），记 $p,q$ 的第三个数分别为 $c,d$，检查 $(a,c,d)$ 和 $(b,c,d)$ 是否存在。时间复杂度 $O(m^2)$。

## 正解

### yummy 法

和 32 分类似的做法，但是优化枚举 $p,q$ 的过程。

记录 $eg_{a,b}$ 表示所有 $(a,b,c)$ 中的 $c$ 构成的 `vector`。

四重循环，外两层循环枚举 $(a,b)$，内两层循环在 $eg_{a,b}$ 内枚举 $c,d$，然后使用 20 分思路里压缩空间的方法，可以做到空间都 $O(nm)$、单次查询 $O(1)$。

虽然看上去有四重循环，但是事实上每个三元组最多和 $n$ 个三元组产生一次查询，所以时间复杂度 $O(nm)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt=0;
vector<int> eg[2005][2005];
bool *ex[2005][2005];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		eg[u][v].emplace_back(w);
		if(ex[v][w]==nullptr){
			ex[v][w]=new bool[2005];
			memset(ex[v][w],0,2005);
		}
		ex[v][w][u]=1;
	}
	for(int a=1;a<n;a++)
		for(int b=a+1;b<=n;b++){
			sort(eg[a][b].begin(),eg[a][b].end());
			for(int cc=0;cc<eg[a][b].size();cc++)
				for(int dd=cc+1;dd<eg[a][b].size();dd++){
					int c=eg[a][b][cc],d=eg[a][b][dd];
					if(ex[c][d]!=nullptr && ex[c][d][a] && ex[c][d][b])
						cnt++;
				}
		}
	cout<<cnt<<endl;
	return 0;
}
```

### EA 法

然而事实上不需要这么麻烦。

考虑先枚举 $a$。枚举 $a$ 的时候，你可以 $O(m)$ 地维护一个桶 $c_{x,y}$，使得 $c_{x,y}$ 记录 $(a,x,y)$ 是否存在。然后枚举 $(u,v,w)$，如果 $c_{u,v},c_{v,w},c_{u,w}$ 都为 true，则 $(a,u,v,w)$ 是一个合法数对。

时间复杂度 $O(nm)$，空间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,u[50005],v[50005],w[50005],cnt=0;
bool c[2005][2005];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&u[i],&v[i],&w[i]);
	for(int a=1;a<=n;a++){
		for(int i=1;i<=m;i++)
			if(u[i]==a)
				c[v[i]][w[i]]=1;
		for(int i=1;i<=m;i++)
            if(c[u[i]][v[i]] && c[v[i]][w[i]] && c[u[i]][w[i]])
                cnt++;
		for(int i=1;i<=m;i++)
			if(u[i]==a)
				c[v[i]][w[i]]=0;
	}
	cout<<cnt;
	return 0;
}
```

---

## 作者：zhlzt (赞：4)

### 题解

显然满足条件的 $(a,b,c)$ 必定为 $m$ 个三元组之一。

于是我们暴力枚举 $(a,b,c)$ 和 $d$，使用哈希判断 $(a,b,d),(a,c,d),(b,c,d)$ 是否为 $m$ 个三元组之一即可。

对于三元组 $(u,v,w)$，我们可令哈希值 $H(u,v,w)=n^2(u-1)+n(v-1)+w-1$。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=233333;
vector<ll>vec[mod];
const int maxm=5e4+10;
int u[maxm],v[maxm],w[maxm],n,m;
inline ll hsh(int u,int v,int w){
	return 1ll*u*n*n+v*n+w;
}
inline void add(ll val){
	vec[val%mod].push_back(val);
}
inline bool find(ll val){
	for(ll cur:vec[val%mod]){
		if(cur==val) return 1;
	}
	return 0;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0); 
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i]>>w[i];
		--u[i]; --v[i]; --w[i];
		add(hsh(u[i],v[i],w[i]));
	}
	int cnt=0;
	for(int i=1;i<=m;i++){
		for(int j=w[i]+1;j<n;j++){
			if(!find(hsh(u[i],v[i],j))) continue;
			if(!find(hsh(u[i],w[i],j))) continue;
			if(!find(hsh(v[i],w[i],j))) continue;
			cnt++;
		}
	}
	cout<<cnt<<"\n";
	return 0;
}
```

---

## 作者：zhaohongdi114514 (赞：4)

# P10996 Tuple 题解

[题目传送门](https://www.luogu.com.cn/problem/P10996)

### 20pts

显然，在 $n$ 的范围内枚举 $a,b,c,d$，按照题意检查是否存在四个对应的三元组即可。可以使用 `set` 来存储所有的三元组。

### 100pts

先讲一个我个人做这类“求满足条件的个数”的题的常用思路。

我们可以将“满足 $A$ 的个数”转化为“所有 $A$ 对应的个数之和”或是“所有满足 $A$ 的一部分的所对应的满足另一部分之和”。

什么意思呢？我们拿这题来举个例。

题目中要求“对于四元组 $(a,b,c,d)$，存在 $(a,b,c),(a,b,d),(a,c,d),(b,c,d)$ 的四元组的个数”。

那么就可以转化一下，变为“对于所有的 $a,b$ 相等的两个三元组，即 $(a,b,c)$ 和 $(a,b,d)$，求存在其余两个三元组的对数”。

这么一转换，是不是就很明了了？我们只需要找出所有前两个数相同的三元组，再在这些三元组中枚举每一对，判断是否存在即可。

对于上述过程，我采用了排序+双指针来实现。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename T>
inline void read(T &x){
	x=0;
	bool flag=false;
	char c=getchar();
	while (c<'0' || c>'9'){
		flag^=(c=='-');
		c=getchar();
	}
	while (c>='0' && c<='9'){
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	x=flag?-x:x;
}
template<typename T>
inline void write(T x){
	if (x<0){
		putchar('-');
		x=-x;
	}
	if (x>9) write(x/10);
	putchar(x%10+'0');
}
const int N=5e4+5;
struct Three{//三元组的结构体
	int a,b,c;
	Three(int a=0,int b=0,int c=0){//构造函数
		this->a=a;
		this->b=b;
		this->c=c;
	}
	bool operator <(const Three &b)const{//为了排序和支持set的查询
		return a==b.a?(this->b==b.b?c<b.c:this->b<b.b):a<b.a;
	}
};
set<Three> st;//存储所有三元组
Three th[N];//这个也是存储所有三元组
//只是用数组单独存一个会比遍历set快
int n,m;
int ans=0;
signed main(){
	read(n),read(m);
	for (int i=1,a,b,c;i<=m;i++){
		read(a),read(b),read(c);
		st.insert(Three(a,b,c));//加入到set中
		th[i]=Three(a,b,c);
	}
	sort(th+1,th+m+1);//排序
	for (int l=1,r=1;l<=m;){//双指针扫描
		if (th[r+1].a!=th[r].a || th[r+1].b!=th[r].b){
//在下一个区间不满足前两个数相等时更新答案
			for (int i=l;i<=r;i++){
				for (int j=i+1;j<=r;j++){
					if ((st.find(Three(th[i].a,th[i].c,th[j].c))!=st.end()) && 
						(st.find(Three(th[i].b,th[i].c,th[j].c))!=st.end()))//查询是否存在另外两个三元组
						{
							ans++;
						}
				}
			}
			l=r+1;//更新区间
		}
		r++;//更新区间
	}
	write(ans);//输出
}
```

---

## 作者：WhiteNight__ (赞：3)

## [P10996 【MX-J3-T3】Tuple](https://www.luogu.com.cn/problem/P10996#submit) 题解

比赛较简单的题。看到题目就可以知道三元组和四元组都是有序的，每个四元组都是一共只有四个不同数字的四个三元组，所以只需要找到满足条件的四个三元组即可求出四元组，时间复杂度 $O(n^4)$，显然不行。

通过观察可以发现四元组 $(a,b,c,d)$ 中 $(a,b,c)$ 和 $(b,c,d)$ 直接包含了四元组的四个不同的数字，所以只需要找到这两个三元组剩下的两个三元组 $(a,b,d)$ 与 $(a,c,d)$ 只需要判断是否存在即可。

最后的问题是如何通过枚举三元组 $(a,b,c)$ 来快速求出三元组 $(b,c,d)$。发现得到第一个三元组的末尾两个数字与第二个三元组开头两个数字相同，即可以用三元组开头两个数字保存每个三元组，这样省去了大量的时间。

### Code


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
int n , m , ans;
struct ThreeUn { // 存题目三元组
	int u , v , w;
	
	ThreeUn (int u_ = 0 , int v_ = 0 , int w_ = 0): // 构造函数
	u(u_) , v(v_) , w(w_) {}
	
	bool operator < (const ThreeUn x) const {
		if(v == x.v && w == x.w) return u > x.u;
		if(w == x.w) return v > x.v;
		return w > x.w;
	}
}a[50050];
std::vector<ThreeUn>en[2005][2005]; // 存每一个三元组开头两个数
std::set<ThreeUn>st;
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= m ; i ++)
	{
		int u , v , w;
		scanf("%d %d %d",&u,&v,&w);
		a[i] = ThreeUn (u , v , w);
		en[u][v].push_back(a[i]);
		st.insert(a[i]); // 加入集合
	}
	for(int i = 1 ; i <= m ; i ++) // 枚举每一个三元组做开头
	{
		const int u = a[i].u , v = a[i].v , w = a[i].w
		for(unsigned i = 0 ; i < en[v][w].size() ; i ++) 
		// 枚举以v、w开头的三元组
		{
			const int z = en[v][w].at(i).w;
			// 大小关系
			// 1 <= u < v < w < z <= n
			if(st.count(ThreeUn(u,w,z))&&st.count(ThreeUn(u,v,z)))
				++ ans; // 如果这两个三元组在集合中能找到对应，就答案+1
		}
	}
	printf("%d",ans);
	exit(0);
}
```
 当然，代码可以手动判断三元组的存在性问题，省去集合，用三元组的开头两个数做判断就行，代码就不放出来了。

---

## 作者：GONGX (赞：3)

### 解题思路
看完题目后，我们首先就会想到暴力枚举四元组，时间复杂度为 $O(N^4)$，看了数据范围之后就知道这显然过不了。

然后我们考虑优化，既然题目给出了 $M$ 个三元组，那么我们显然可以通过三元组的其中一项或两项用线性数据结构存储另外的两项或一项。所以，我们可以选择开两个动态数组分别存以 $u,v$ 开头的三元组的后一项有哪些和以 $u$ 开头的三元组的后两项有哪些。具体实现时，我们先枚举一个 $1$ 到 $N$ 的数 $a$，然后再枚举以 $a$ 开头的三元组的后两项 $b$ 和 $c$，然后继续枚举以这后两项为开头的三元组的最后一项 $d$。此时我们已经完成了四元组的枚举，且满足存在两个三元组 $(a,b,c)$ 和 $(b,c,d)$，而是否存在三元组 $(a,b,d)$ 和 $(a,c,d)$ 则可以考虑使用 ```map``` 或 ```unordered_map``` 来判断。
### 温馨提示
虽然 ```unordered_map``` 复杂度较低，但它是可以被卡的，只要出题人想，就可以把它卡得单次访问时间复杂度为 $O(N)$，所以请谨慎使用这个数据结构。
### 代码展示
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2002, M = 5e4 + 2;
int n, m, ans;
vector<int> s2[N][N];
vector<pair<int, int>> s1[N];
unordered_map<int, bool> mp[N][N]; 
int main() {
	ios::sync_with_stdio(0);//关闭同步流 
	cin.tie(0), cout.tie(0);//等待时间设为 0 
	cin >> n >> m;
	for (int i = 1, u, v, w; i <= m; i++) {
		cin >> u >> v >> w, mp[u][v][w] = true;
		s2[u][v].emplace_back(w), s1[u].emplace_back(make_pair(v, w));
	} for (int a = 1, b, c, d; a <= n; a++)//枚举四元组 
		for (auto Pair : s1[a]) {//冒号遍历 和 auto 不知道的可自行搜索
			b = Pair.first, c = Pair.second;
			for (int d : s2[b][c])
				if (mp[a][b][d] && mp[a][c][d])//判断该四元组是否合法
					ans++;
		}
	cout << ans;
	return 0;
}
```

---

## 作者：hanchengyi (赞：3)

### 思路

首先考虑暴力，枚举 $a,b,c,d$ 四个数，判断是否在 $m$ 个三元组内，时间复杂度 $O(mn^4)$。

判断是否在 $m$ 个三元组内这一步可以用哈希实现，省略 $m$ 的枚举，时间复杂度 $O(n^4)$。

观察四个三元组中的 $(a,b,c)$ 可以枚举 $m$ 个给定三元组得到，这样就省去了三层枚举，只需枚举一个 $m$，再枚举一个 $d$，计算答案，时间复杂度 $O(nm)$。

哈希要尽量避免碰撞，可以用多哈希。

### 实现

枚举 $m$ 个三元组中的一组 $(a,b,c)$，再枚举一个 $d$，判断 $(a,b,d),(a,c,d),(b,c,d)$ 是否在 $m$ 个三元组内即可，累计答案。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e4+7;
const int M=1e7+50;
int n,m;
int u[N],v[N],w[N]; 
int mp1[M]; 
int mp2[M];
int mp3[M];
//用多哈希，范围尽量开大 
int ans;
const int k1=6869;
const int k2=5021;
const int k3=2999;
const int mod1=10000019;
const int mod2=9999677;
const int mod3=9779779;//模数尽量大 
int cal1(int a,int b,int c){
	return ((1ll*a*(k1)*(k1)+b*(k1)+c)*971)%mod1+1; 
}
int cal2(int a,int b,int c){
	return ((1ll*a*(k2)*(k2)+b*(k2)+c)*97)%mod2+1;
}
int cal3(int a,int b,int c){
	return ((1ll*a*(k3)*(k3)+b*(k3)+c)*1523)%mod3+1;
}//三个哈希函数 
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i]>>w[i];
		mp1[cal1(u[i],v[i],w[i])]=1;
		mp2[cal2(u[i],v[i],w[i])]=1;
		mp3[cal3(u[i],v[i],w[i])]=1;
	}
	for(int i=1;i<=m;i++){//枚举m个三元组(a,b,c) 
		for(int d=w[i]+1;d<=n;d++){//由于a<b<c<d,所以d从c+1开始枚举 
			if(mp1[cal1(u[i],v[i],d)]&&mp2[cal2(u[i],v[i],d)]&&mp3[cal3(u[i],v[i],d)])//判断(a,b,d)是否存在 
			{
				if(mp1[cal1(u[i],w[i],d)]&&mp2[cal2(u[i],w[i],d)]&&mp3[cal3(u[i],w[i],d)])//判断(a,c,d)是否存在
				{
					if(mp1[cal1(v[i],w[i],d)]&&mp2[cal2(v[i],w[i],d)]&&mp3[cal3(v[i],w[i],d)])//判断(b,c,d)是否存在	
						ans++;//累计答案 
				}
			}
		}
	}
	cout<<ans;
}
```

---

## 作者：canwen (赞：2)

降智题，看了官解之后恍然大悟，这里补充一下。
## 题意

求有多少组 $(a,b,c,d)$ 满足在 $m$ 个互不相同的三元组中，存在四个三元组 $(a,b,c),(a,b,d),(a,c,d),(b,c,d)$。
## 分析
  先枚举 $a$，接着我们用变量 $i$ 作为下标枚举所有三元组，将其 $(a,u_{i},v_{i})$ 作为一个三元组 $(a,b,c)$，因为这样其余的三元组就可以直接用桶表示出来，分别是 $(a,u_{i},w_{i}),(a,v_{i},w_{i}),(u_{i},v_{i},w_{i})$。其中 $(u_{i},v_{i},w_{i})$ 枚举时肯定存在，所有无需判断。这就是为什么官解直接这么写。
  
```cpp
for(int i=1;i<=m;i++)
     if(c[u[i]][v[i]] && c[v[i]][w[i]] && c[u[i]][w[i]])
          cnt++;
```

其余的部分官解很明白了。

---

## 作者：OIer_Tan (赞：1)

## 思路

首先可以想到用 `std::map` 套 `std::set` 存前两个数可以对应的最后一个数，并枚举三元组+枚举另一个数，然而这样复杂度是 $O(nm\log m)$ 的，显然 T 飞。

考虑优化，我们想到可以先给每个三元组内部排序，然后只枚举每个三元组前两个数可以配对的数，这样复杂度最坏是 $O(nm\log m)$，看似没有优化，然而实测这样很难卡满，可以获得 $76$ 分的好成绩。

继续优化，我们发现可以和某个三元组产生贡献的数会是这三个数其中每两个数在前两个的位置的三元组中，第三个位置上数的并集，这样好做了许多。我们想到 C++ 中有个函数是 `std::set_intersection` 可以用来求已排序范围的并集，这样就可以在 $O(nm)$ 的时间复杂度内求出答案，这样已经足以卡过这道题。

然而如果我们把这个烂做法交到加强版，会发现跑的巨慢无比。考虑一个常见优化是不用 `std::set` 一个一个插，而是用 `std::vector` 全部加到末尾再一起排，尽管复杂度不变，但常数优化非常明显。经过测试，在加强版中除了一个 hack 点 T 飞了外其它全部点都在 350ms 内。

## 代码

这里仅给出最终代码。

```cpp
#include <bits/stdc++.h>

#ifndef CRT
#define endl '\n'
#endif

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

const ll N = 3e5 + 5 ;

ll u [N] , v [N] , w [N] ;

ll n , m , ans = 0 ;

map <pair<ll,ll>,vector <ll>> mp ;

int main ()
{
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	cin >> n >> m ;
	for ( ll i = 1 ; i <= m ; i ++ )
	{
		cin >> u [i] >> v [i] >> w [i] ;
		ll tmp [4] = { u [i] , v [i] , w [i] } ;
		sort ( tmp , tmp + 3 ) ;
		u [i] = tmp [0] , v [i] = tmp [1] , w [i] = tmp [2] ;
 		mp [make_pair ( u [i] , v [i] )].emplace_back ( w [i] ) ;
	}
	for ( auto & x : mp )
	{
	    sort ( x.second.begin () , x.second.end () ) ;
	}
	for ( ll i = 1 ; i <= m ; i ++ )
	{
		ll a = u [i] , b = v [i] , c = w [i] ;
		const auto & tmp1 = mp [make_pair ( a , b )] , tmp2 = mp [make_pair ( a , c )] , tmp3 = mp [make_pair ( b , c )] ;
		vector <ll> tmpa , tmpb ;
		set_intersection ( tmp1.begin () , tmp1.end () , tmp2.begin () , tmp2.end () , back_insert_iterator ( tmpa ) ) ;
		set_intersection ( tmpa.begin () , tmpa.end () , tmp3.begin () , tmp3.end () , back_insert_iterator ( tmpb ) ) ;
        ans += tmpb.size () ;
	}
	cout << ans << endl ;
	return 0 ;
}
```

---

## 作者：SkyWave (赞：1)

~~好久没写题解了~~

# 思路
注意到合法的四元组 $(a, b, c, d)$ 形如：

![形如](https://cdn.luogu.com.cn/upload/image_hosting/jknp6efi.png)

（如果 $u$ 有一个箭头连出到 $v$，则表示在输入的三元组中存在一组三元组使得 $v$ 是 $u$ 的后继（即形如 $(u, v, *)$ 或 $(*, u, v)$，$*$ 则表示我们不关心这个元素））

观察这张图，我们可以得出一些关系：

- $b$ 是 $a$ 的后继
- $c$ 同时是 $a$ 和 $(a, b)$ 的后继（二元组 $(u, v)$ 的后继定义为所有的 $w$ 使得存在一组三元组 $(u, v, w)$）
- $d$ 同时是 $(a, b)$、 $(a, c)$ 和 $(b, c)$ 的后继

所以我们可以使用以下算法解决此问题：

1. 枚举 $a$
2. 枚举 $a$ 作为三元组的第一个元素时的所有后继，即 $a$ 固定时所有合法的 $b$（即形如 $(a, b, *)$）
3. 在 $a$ 的后继与 $(a, b)$ 的后继的交中枚举，即 $(a, b)$ 固定时所有合法的 $c$
4. 将 $(a, b)$ 的后继、 $(a, c)$ 的后继与 $(b, c)$ 的后继的交的大小计入答案，即 $(a, b, c)$ 固定时所有合法的 $d$ 的数量

# 实现细节与复杂度

  如何实现上述算法？我们可以使用 ```bool``` 数组来储存一个元素或一个二元组的所有后继，即如果 $x$ 是对应元素或元组的后继，则在对应的 ```bool``` 数组的 $x$ 下标位置赋值为 ```true```，那么遍历后继即遍历数组里所有为 ```true``` 的下标，两个后继的交即为两个后继 ```bool``` 数组相同的下标同时为 ```true```的所有下标，交的数量就只要数一数有多少个都为 ```true``` 的下标即可

但储存上会有一个小问题，储存所有 $O(n^2)$ 个二元组的 $O(n)$ 个后继时会用到 $O(n^3)$ 空间，这是不能接受的。但是我们注意到所有的三元组最多只有 $O(m)$ 个，那么二元组也只有 $O(m)$ 个。我们可以只开 $O(m)$ 个后继数组，将每个出现过的二元组用 $1 \sim m$ 编号，并存储在对应编号的后继数组中，这样就只需要 $O(n^2+nm)$ 空间。

还有时间复杂度没有讨论：

1. 枚举三元组 $(a, b, c)$ 一共需要 $O(n^2+nm)$ 代价，因为：

  - 枚举每个 $a$ 再枚举 $b$ 判断是否是后继总共需要 $O(n^2)$ 代价，而 $(a, b)$ 最多只有 $O(m)$ 对。
  
  - 对于每个 $(a, b)$ 求出 $a$ 后继与 $(a, b)$ 后继的交需要 $O(n)$ 代价，在交中枚举总共需要 $O(m)$ 代价，因为所有的三元组 $(a, b, c)$ 最多只有 $O(m)$ 对

2. 对于 $O(m)$ 个三元组 $(a, b, c)$ 计算 $(a, b)$ 的后继、 $(a, c)$ 的后继与 $(b, c)$ 的后继的交的大小需要 $O(n)$ 时间，所以总共需要 $O(nm)$ 代价

故此算法时间复杂度为 $O(n^2+nm)$

# 代码

赛时我使用了 ```bitset``` 代替 ```bool``` 数组，```bitset``` 是个标准库中的容器，在 $64$ 位操作系统上将一个 $64$ 位整数的每一位当作一个 ```bool``` 变量，所以储存空间拥有 $\frac{1}{8}$ 的常数，做很多常见操作，如给两个 ```bool``` 数组的相同的下标上的元素求 ```&``` 时拥有 $\frac{1}{64}$ 的常数。为了用 $O$ 标记体现 ```bitset``` 带来的优化，同时也为了体现操作系统位数对优化的差异，我们设 $w$ 为操作系统位数，若使用 ```bitset``` 优化本算法，时间复杂度则为 $O(\frac{n^2+nm}{w})$。

我会在本题的代码的注释中解释 ```bitset``` 对应的操作的作用，若对 ```bitset``` 支持的更多操作感兴趣可以前往 [OI-Wiki](https://oi-wiki.org/lang/csl/bitset/) 学习更多用法。


```cpp
#include <iostream>
#include <bitset>
using namespace std;

using ll = long long;

constexpr int N = 2000 + 1, M = 50000 + 1;

int mid[N][N];
bitset<N> um[N], uvm[M];

int main() {
	int n, m;
	cin >> n >> m;
	int tot = 0;
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		int &nid = mid[u][v];//(u, v) 二元组对应的编号
		if (!nid) {//如果之前没有编号过
			nid = ++tot;//新建编号
		}
		um[u][v] = true; uvm[nid][w] = true;
	}
	
	ll ans = 0;
	for (int a = 1; a < n; ++a) {
		auto &uma = um[a];
		for (int b = uma._Find_next(a)/*_Find_next(x)函数：找到 bitset 中 x 下标后的第一个 true 的位置*/; b <= n; b = uma._Find_next(b)) {//实现了 b 不重不漏地遍历了 a 的所有后继
			auto &uvmab = uvm[mid[a][b]];
			auto cs = uma & uvmab;//& 运算符：求两个 bitset 每个相同下标对应的元素的 & 的结果，cs 即为 a 的后继与 (a, b) 的后继求交后的 bitset
			for (int c = cs._Find_next(b); c <= n; c = cs._Find_next(c)) {//同理，访问所有合法的 c
				ans += (uvmab & uvm[mid[b][c]] & uvm[mid[a][c]]).count();//count函数：数一个 bitset 中有多少个下标为 true，将 $(a, b)$ 的后继、 $(a, c)$ 的后继与 $(b, c)$ 的后继的交的大小计入答案
			}
		}
	}
	cout << ans << '\n';
	return 0;
}
```

# 评价与总结

此题很好地考察了均摊枚举的基本技巧，是一道很合适的普及组赛题。均摊枚举的关键就是尽量保证每次枚举到的元素都是对计入答案有贡献的。

同时题目也需要对分析均摊复杂度有一定理解，复杂度并不是简单的嵌套起来的代价相乘，有时也要注意到代价有总和保证。

希望写得这么详细可以让一个刚学会 ```bool``` 数组的萌新也可以看懂，也是让普及组选手更好地感受均摊枚举的魅力。如任何人有任何不理解的地方或者异议欢迎私信!

---

## 作者：jjy2023 (赞：1)

# P10996 【MX-J3-T3】Tuple
比赛时只想出 68 分算法，~挠破头想了一个小时，卡常也没卡过去~，赛后看官方题解竟如此清爽，当场给我整麻了。

## 68 分做法：
用一个 `set` 加上 `tuple` 来存储三元组，再枚举第四个数。时间复杂度为 $O(nm\log m)$。
### Code： 

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans=0;
set<tuple<int,int,int>> s;
set<pair<int,int>> s1,s2,s3;//我也不知道这一段什么意思，但加上速度会变快
int main()
{
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=m;++i)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		s.insert(make_tuple(x,y,z));
		s1.insert({x,y});
		s2.insert({x,z});
		s3.insert({y,z});
	}
	for(const auto&i:s)
		for(register int j=4;j<=n;++j)
		{
			int x=get<0>(i),y=get<1>(i),z=get<2>(i);
			if(s.count({x,y,j})&&s.count({x,z,j})&&s.count({y,z,j})) ans++;
		}
	printf("%d",ans);
	return 0;
}
```
## 100 分算法：
先枚举第一个数 $a$，用一个二维数组 $f$ 来维护 $(a,b,c)$ 是否存在。再枚举 $(b,c,d)$，若 $f_{b,c},f_{b,d},f_{c,d}$ 都存在，那么 $(a,b,c,d)$ 也存在。时间复杂度为 $O(nm)$。
### Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,b[50005],c[50005],d[50005],ans=0;
bool f[2005][2005];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d%d%d",&b[i],&c[i],&d[i]);
	for(int a=1;a<=n;a++)
	{
		for(int i=1;i<=m;i++)
			if(b[i]==a) f[c[i]][d[i]]=1;
		for(int i=1;i<=m;i++)
            if(f[b[i]][c[i]]==1&&f[c[i]][d[i]]==1&&f[b[i]][d[i]]==1) ans++;
		for(int i=1;i<=m;i++)
			if(b[i]==a) f[c[i]][d[i]]=0;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：diamond_plus (赞：1)

一个简单的思路是，枚举所有三元组作为 $(a, b, c)$，再枚举 $d$，用 `set` 之类的东西判断一下存不存在，然后计数。

这样是 $O(nm\log n)$ 的，后面几个点会超时。

注意到匹配条件中 $d$ 只出现三次，于是我们可以换一下枚举顺序，先枚举 $d$，预处理出对于每对 $(x, y)$，$(x, y, d)$ 是否存在。

然后枚举 $(a, b, c)$，根据预处理的结果判断即可。时间 $O(nm)$。

``` cpp
void main() {
  int n, m;
  io.read(n, m);

  struct Tuple {
    int x, y, z;
  };
  vector<Tuple> a(m);

  for (auto &[x, y, z] : a) {
    io.read(x, y, z);
  }

  int ans = 0;
  vector<vector<int>> vis(n + 1, vector<int>(n + 1));
  for (int k = 1; k <= n; ++k) {
    for (const auto &[x, y, z] : a) {
      if (z == k) {
        vis[x][y] = true;
      }
    }
    for (const auto &[x, y, z] : a) {
      if (vis[x][y] and vis[x][z] and vis[y][z]) {
        ++ans;
      }
    }
    for (const auto &[x, y, z] : a) {
      if (z == k) {
        vis[x][y] = false;
      }
    }
  }

  io.writeln(ans);
}
```

另类方法：只枚举前两个元素是 $a, b$ 的 $d$ 即可，理论最坏复杂度还是带 $\log n$，可能数据比较弱这种写法也过去了。

![](https://cdn.luogu.com.cn/upload/image_hosting/cdi0i369.png)

``` cpp
void main() {
  int n, m;
  io.read(n, m);

  struct Tuple {
    int x, y, z;
    bool operator<(const Tuple &p) const {
      if (x == p.x) {
        if (y == p.y) {
          return z < p.z;
        }
        return y < p.y;
      }
      return x < p.x;
    }
  };

  map<pair<int, int>, set<int>> num;
  set<Tuple> st;
  for (int i = 0, x, y, z; i < m; ++i) {
    io.read(x, y, z);
    st.insert({x, y, z});
    num[{x, y}].insert(z);
  }

  int ans = 0;
  for (const auto &[x, y, z] : st) {
    auto &v = num[{x, y}];
    auto it = v.upper_bound(z);
    // 只枚举比 z 大的数
    for (; it != v.end(); ++it) {
      int k = *it;
      if (st.count({x, z, k}) and st.count({y, z, k})) {
        ++ans;
      }
    }
  }

  io.writeln(ans);
}
```

---

## 作者：Flanksy (赞：0)

以下使用 $n$ 表示三元组数量，$V$ 表示值域。

对于四元组 $(a,b,c,d)$ 枚举 $a,b$，然后枚举所有形如 $(a,b,x)$ 的三元组两两配对并确认是否满足条件。值域限制 $(a,b,x)$ 至多存在 $2000$ 个，这样的 $(a,b,x)$ 至多出现 $25$ 个，极限计算量级为 $2000^2 \times 25 = 10^8$，可以通过。

实现中直接使用 `set` 统计三元组，没有进行卡常。

至多有 $O \left( \dfrac{n}{V} \right)$ 个形如 $(a,b,x)$ 的三元组能够达到 $O(V)$ 量级，时间复杂度 $O \left( \dfrac{n}{V} \times V^2 \log V \right) = O(nV\log V)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
set<int> w[2'005][2'005];
int n,m,ans,t[50'005];
inline void calculate(int a,int b,int x){
    for(int i=1;i<=x;i++) for(int j=i+1;j<=x;j++)
        if(w[a][t[i]].count(t[j])&&w[b][t[i]].count(t[j])) ++ans;
}
int main(){
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        static int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        w[x][y].emplace(z);
    }
    for(int i=1;i<=m;i++)
        for(int j=i+1;j<=m;j++) if(!w[i][j].empty()){
            int cnt=0;
            for(int k:w[i][j]) t[++cnt]=k;
            calculate(i,j,cnt);
        }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：xuan_gong_dong (赞：0)

## 题面
[P10996 【MX-J3-T3】Tuple](https://www.luogu.com.cn/problem/P10996#submit)
## 分析

大致将一个三元组看成两条路径，且第二条路径基于第一条路径存在，可以用指针实现。

查询答案的时候直接离线暴力枚举 $d$，并判断所求的路径是否存在即可。

有一点卡空间，不能全用长整型。

时间复杂度 $O(n \times m)$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,mm;
long long ans=0;
int tree[2010][50010];
int tot=2001;
struct node {
	int aaa,bbb,ccc;
} xgd[50010];
signed main() {
	scanf("%d%d",&n,&mm);
	for(int i=1; i<=mm; i++) {
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		xgd[i]=(node) {
			a,b,c
		};
		if(tree[b][a]==0)
		{
			tree[b][a]=++tot;
			tree[c][tot]++;
		}
		else tree[c][tree[b][a]]++;
	}
	for(int i=1; i<=mm; i++) {
		int a,b,c;
		a=xgd[i].aaa;
		b=xgd[i].bbb;
		c=xgd[i].ccc;
		for(int d=c+1; d<=n; d++) {
			int t1=tree[d][tree[b][a]];
			int t2=tree[d][tree[c][a]];
			int t3=tree[d][tree[c][b]];
			ans+=t1*t2*t3;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：zhoujunchen (赞：0)

目前应该是代码比较短的一篇。

做题思路
---
开一个二维的 set，像邻接矩阵一样来存储三元组，每读入一对三元组就在前两个数所属的集合里插入第三个数。随后用两层循环，第一层遍历三元组，第二层遍历第一层三元组所属的集合。

代码很简单，如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
set<int> ztl[2005][2005];
int n,m,a[50004],b[50004],c[50004],ans;
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>a[i]>>b[i]>>c[i];
        ztl[a[i]][b[i]].insert(c[i]);
    }
    for(int i=1;i<=m;i++)
        for(auto d:ztl[a[i]][b[i]])//(a,b,c)和(a,b,d)不需要管，他们的第三个数肯定会被遍历到
            //对应 (a,c,d) 和 (b,c,d)
            if(ztl[a[i]][c[i]].count(d)&&ztl[b[i]][c[i]].count(d))ans++;
    cout<<ans;
    return 0;
}
```

---

## 作者：HHC883 (赞：0)

# 题目分析
对于三元组 $(u_i,v_i,w_i)$，我们尝试计算是否存在 $a$ 满足三元组 $(a,u_i,v_i),(a,u_i,w_i),(a,v_i,w_i)$ 也都在 $m$ 个三元组中出现过，若出现过，则将答案加一。容易想到可以使用 set 来进行计算。我们开一个 $n \times n$ 的 set 数组 $s$，对于一个输入的三元组 $(u_i,v_i,w_i)$，在 $s_{u_i,v_i}$ 中加入 $w_i$，接下来的统计就很容易了。
# 参考代码

```cpp
#include<iostream>
#include<set>
using namespace std;
int n,m,u[(int)5e4+5],v[(int)5e4+5],w[(int)5e4+5],ans;
set<int> s[2005][2005];
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i]>>w[i];
		s[u[i]][v[i]].insert(w[i]);
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<u[i];j++){
			if(s[j][u[i]].count(v[i]))
			if(s[j][u[i]].count(w[i]))
			if(s[j][v[i]].count(w[i]))
			ans++;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：sbno333 (赞：0)

令我唐了很长时间。

考虑枚举其中一个三元组 $(a,b,c)$，然后枚举第四个数，判断是否存在，然后去重，去重可能会导致直接爆炸，不可取。

我们考虑优化过程，我们发现必须存在三元组 $(a,b,d),(a,c,d),(b,c,d)$，于是我们发现就是一个交，可以 bitset 维护第三个数，然后与以下，加上 $1$ 数量。

于是你获得了 $96$ 的高分。

发现 MLE，可以把 bitset 的交集可能的值域分段，每一次空间只记录一段的，然后答案统计一段的，时间换空间。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
struct st{
	int a,b,c;
}sd[50009];
bitset<202> f[2002][2009];
bitset<202> qwq;
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>sd[i].a>>sd[i].b>>sd[i].c;
		
	}int ans;
			ans=0;
	for(int cc=1;cc<=12;cc++){
		for(int i=1;i<=m;i++){
			if(sd[i].c-(cc-1)*200>=0&&sd[i].c-(cc-1)*200<200)
				f[sd[i].a][sd[i].b][sd[i].c-(cc-1)*200]=1;
			
		}
			
			for(int i=1;i<=m;i++){
				qwq=(f[sd[i].a][sd[i].b]&f[sd[i].a][sd[i].c]&f[sd[i].b][sd[i].c]);
				ans+=qwq.count();
			}
			for(int i=1;i<=m;i++){
			if(sd[i].c-(cc-1)*200>=0&&sd[i].c-(cc-1)*200<200)
				f[sd[i].a][sd[i].b][sd[i].c-(cc-1)*200]=0;
			
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10996)

## 思路

桶、二分查找。

读入数据时，我们把每个 $w_i$ 都放进对应的桶 $t_{u_i,v_i}$ 中。这个桶用 `vector` 来模拟，由于是动态分配空间，而三元组有 $m$ 个且 $1\le m\le 5\times 10^4$，所以实际空间占用仅仅只为 $m$。

对于每个桶，由于之后要进行二分查找，所以我们都要排序。

之后枚举 $m$ 个三元组。此时 $a=u_i,b=v_i,c=w_i$。首先我们在 $t_{a,b}$ 中查找 $c$ 的位置，再从这个位置**之后**枚举出的值即为 $d$，由于之前排了序，所以满足 $c<d$ 的要求。

之后我们分别查找 $t_{a,c},t_{b,c}$ 中是否存在 $d$。如果都存在，那么说明这组 $(a,b,c,d)$ 是满足要求的，答案 $+1$。

乍一看时间复杂度有 $\mathcal{O}(mn\log n)$，但由于 $1\le u_i<v_i<w_i\le n$，若数字是分散的，那么每个桶的大小都很小；若数字是集中的，那么每个桶的大小也不会超过 $n$。所以总的复杂度约为 $\mathcal{O}(n^2\log n)$ 级别，足以通过此题。

## 代码

```cpp
#include<bits/stdc++.h>
#define lb lower_bound
using namespace std;
int read(){
	int k=0;bool flag=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')flag=0;c=getchar();}
	while(isdigit(c)){k=(k<<1)+(k<<3)+(c^48);c=getchar();}
	if(flag)return k;return -k;
}
const int N=2010,M=5e4+10;
int n,m,ans;
struct node{
	int a,b,c;
}a[M];//记得开够。
vector<int>ve[N][N];
signed solution(){
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		a[i]={read(),read(),read()};
		ve[a[i].a][a[i].b].push_back(a[i].c);
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j)sort(ve[i][j].begin(),ve[i][j].end());
	}
	for(int i=1;i<=m;++i){
		int A=a[i].a,B=a[i].b,C=a[i].c;
		int p=lb(ve[A][B].begin(),ve[A][B].end(),C)-ve[A][B].begin();
		for(int j=p+1;j<ve[A][B].size();++j){
			int D=ve[A][B][j];//此时 ABCD 都一定存在。
			auto p=lb(ve[A][C].begin(),ve[A][C].end(),D);
 			if(p==ve[A][C].end()||*p!=D)continue;//有可能返回的不是 vector.end()，所以还要特判。
			p=lb(ve[B][C].begin(),ve[B][C].end(),D);
 			if(p==ve[B][C].end()||*p!=D)continue;
			++ans;//都存在就记录。
		}
	}
	cout<<ans;
	return 0;
}
```

[AC 代码](https://www.luogu.com.cn/record/174725826)

---

## 作者：shinzanmono (赞：0)

考虑枚举分别以 $a,d$ 开头、结尾的三元组，然后枚举两个中间值 $b,c$，查找是否存在 $(a,b,c)$ 和 $(b,c,d)$ 即可。

先给出代码：

```cpp
#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
std::unordered_set<long long>tpl;
std::unordered_map<long long,std::basic_string<int>>mp;
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n,m;
    std::cin>>n>>m;
    auto value=[&](int u,int v,int w){return (u-1ll)*n*n+(v-1)*n+w-1;};
    for(int i=1,u,v,w;i<=m;i++){
        std::cin>>u>>v>>w;
        mp[value(1,u,w)]+=v;
        tpl.insert(value(u,v,w));
    }
    long long ans=0;
    for(auto p:mp){
        int a=p.first/n+1,d=p.first%n+1;
        std::basic_string<int>mid(p.second);
        std::sort(mid.begin(),mid.end());
        for(int i=0;i<mid.size();i++){
            for(int j=i+1;j<mid.size();j++){
                int b=mid[i],c=mid[j];
                if(tpl.find(value(a,b,c))!=tpl.end()&&tpl.find(value(b,c,d))!=tpl.end())ans++;
            }
        }
    }
    std::cout<<ans<<"\n";
    return 0;
}
```

分析时间复杂度。

```cpp
for(auto p:mp){
    int a=p.first/n+1,d=p.first%n+1;
    std::basic_string<int>mid(p.second);
    std::sort(mid.begin(),mid.end());
    for(int i=0;i<mid.size();i++){
        for(int j=i+1;j<mid.size();j++){
            int b=mid[i],c=mid[j];
            if(tpl.find(value(a,b,c))!=tpl.end()&&tpl.find(value(b,c,d))!=tpl.end())ans++;
        }
    }
}
```

考虑前两个循环为整体 $O(m)$，而后面的循环复杂度上限为 $O(n)$，故时间复杂度为 $O(nm+m\log m)$（其实可以不排序直接枚举）。

---

## 作者：thh_loser (赞：0)

# P10996 【MX-J3-T3】Tuple 题解

[题目链接](https://www.luogu.com.cn/problem/P10996)

# 思路

由于是个三元组，我们可以考虑状态压缩，将所有已有的三元组储存。最后枚举所有三元组，每次枚举四元组的另一个数，并判断是否有另外三个三元组，统计数量即可。

复杂度应该是 $O\left(nm\right)$ 的，但是有点常数，这时我们可以进行减枝，在枚举时从三元组的最大一个数开始枚举（因为若有更小的满足，则在之前一定枚举过了），就可以通过了。

# code
```c++
#include<bits/stdc++.h>
#define N 50010
#define int long long
using namespace std;
int n,m,u[N],v[N],w[N],ans,p[N];
const int p1=10000,p2=100000000;
unordered_map<int,bool>ma;
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1,x,y,z;i<=m;i++){
		scanf("%lld%lld%lld",&x,&y,&z);
		int k=x*p2+y*p1+z;//压一下 
		p[i]=k;
		ma[k]=1;
		u[i]=x,v[i]=y,w[i]=z;
	}
	for(int i=1;i<=m;i++){
		int k=w[i]+1;
		for(;k<=n;k++){
			if(ma.find(u[i]*p2+v[i]*p1+k)!=ma.end()&&ma.find(u[i]*p2+w[i]*p1+k)!=ma.end()&&ma.find(v[i]*p2+w[i]*p1+k)!=ma.end()){
				ans++;//依次枚举得到答案 
			}	
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

暴力美学。

看到的第一眼，就首先想了一个哈希的程序，如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
unordered_set<long long>s; int n,m,ans;
inline long long gh(const int&a,const int&b,const int&c){
	return (long long)a*n*n+b*n+c;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1,l,r,x;i<=m;++i){
		cin>>l>>r>>x;
		for(int i=1;i<l;++i)
			if(s.count(gh(i,l,r))&&s.count(gh(i,l,x))&&
				s.count(gh(i,r,x))) ans++;
		for(int i=l+1;i<r;++i)
			if(s.count(gh(l,i,r))&&s.count(gh(l,i,x))&&
				s.count(gh(i,r,x))) ans++;
		for(int i=r+1;i<x;++i)
			if(s.count(gh(l,r,i))&&s.count(gh(l,i,x))&&
				s.count(gh(r,i,x))) ans++;
		for(int i=x+1;i<=n;++i)
			if(s.count(gh(l,r,i))&&s.count(gh(l,x,i))&&
				s.count(gh(r,x,i))) ans++;
		s.insert(gh(l,r,x));
	}
	cout<<ans<<endl;
} 
```

然而很遗憾，它并不能通过这道题（显然）。

考虑一下优化，我们发现有大量的时间都用来枚举了，但实际有用的点并不多，这会导致大量的时间浪费。

所以这时候，我们考虑换一种记录方式：对于 $u_i,v_i$，有哪些 $w_i$。这个东西可以用 `set` 维护。

但是还有问题，这样做最极限情况下仍然会把前面的点枚举完，复杂度退化为类似于哈希做法。

其实，我们发现我们就是在枚举其中一个的点，验证另外两个中有没有。显然，我们如果枚举大小最小的那个，时间复杂度会更优。

因此，我们就可以卡过这道题了。代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#ifdef _WIN32
#define getchar_unlocked getchar
#define putchar_unlocked putchar
#endif
inline int read() {
	int r = 0; char c = getchar_unlocked();
	while (c < '0' || c>'9') c = getchar_unlocked();
	while (c >= '0' && c <= '9') r = r * 10 + (c ^ 48), c = getchar_unlocked();
	return r;
}
int n,m,ans; set<int>v[4002001]; set<int>::iterator it;
inline int gh(const int&a,const int&b){
	return a*n+b;
}
signed main(){
	n=read(); m=read();
	for(int i=1,l,r,x;i<=m;++i){
		l=read(); r=read(); x=read();
		const set<int>&va=v[gh(l,r)];
		int sa=va.size();
		const set<int>&vb=v[gh(l,x)];
		int sb=vb.size();
		const set<int>&vc=v[gh(r,x)];
		int sc=vc.size();
		if(sa<=sb&&sa<=sc)
			for(it=va.begin();it!=va.end();++it){
				if(vb.count(*it)&&vc.count(*it)) ans++;
			}
		else if(sb<=sa&&sb<=sc)
			for(it=vb.begin();it!=vb.end();++it){
				if(va.count(*it)&&vc.count(*it)) ans++;
			}
		else
			for(it=vc.begin();it!=vc.end();++it){
				if(vb.count(*it)&&va.count(*it)) ans++;
			}
		v[gh(l,r)].insert(x);
		v[gh(l,x)].insert(r);
		v[gh(r,x)].insert(l);
	}
	cout<<ans<<endl;
} 
```

时间复杂度我并不太会计算，但是因为所有的三元组之间互不相同，因此每轮枚举的数量是 $O(\log m)$ 级别的，可以通过。

---

## 作者：Lele_Programmer (赞：0)

# P10996 题解

## 思路

写一个这样的东西：`map<pair<int,int>,unordered_set<int>> hs;`。

对于输入的 $(a,b,c)$，将 $c$ 添加到 $(a,b)$ 对应的集合里面。

枚举每一个 $(a,b)$，对于每一个 $(a,b)$，枚举每一个 $c$ 和 $d$，然后得到了两个三元组 $(a,b,c)$ 和 $(a,b,d)$，只需查找一下是否存在 $(a,c,d)$ 和 $(b,c,d)$ 即可。

判断是否存在一个三元组 $(a,b,c)$，先查找是否有 $(a,b)$，然后再查找 $(a,b)$ 有没有 $c$ 即可，如果不想这么麻烦的话，应该也可以再开一个 `set` 来存三元组。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)

namespace IO {
    inline void read(int &a) {
        int sym=1,num=0;
        char c=getchar();
        while (c<'0' || c>'9') {
            if (c=='-') {
                sym=-1;
            }
            c=getchar();
        }
        while (c>='0' && c<='9') {
            num=num*10+c-'0';
            c=getchar();
        }
        a=sym*num;
    }
    inline void write(int a) {
        if (a<0) {
            putchar('-');
            a*=-1;
        }
        if (a>=10) {
            write(a/10);
        }
        putchar(a%10+'0');
    }
}

using namespace IO;

typedef pair<int,int> pii;

int n,m;
int ans;
map<pii,unordered_set<int>> hs;

inline bool check(int a,int b,int c) {
    if (!hs.count({a,b})) return false;
    else if (!hs[{a,b}].count(c)) return false;
    else return true;
}

int main() {
    read(n); read(m);
    _rep(i,1,m) {
        int a,b,c;
        read(a); read(b); read(c);
        hs[{a,b}].emplace(c);
    }
    _iter(it,hs) {
        auto &a=it->first.first,&b=it->first.second;
        auto &st=it->second;
        _iter(i,st) {
            auto &c=*i;
            _iter(j,st) {
                auto &d=*j;
                if (d<=c) continue;
                if (check(a,c,d) && check(b,c,d)) {
                    ans++;
                }
            }
        }
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：huyangmu (赞：0)

暴力就不说了，枚举每个四元组，并判断四元组是否满足条件，时间复杂度 $O(n^4m)$，虽然可以用哈希优化到 $O(n^4)$，但时间显然会超。

注意到，暴力枚举会枚举到很多没必要的情况，所以只需要枚举 $m$ 个三元组，再枚举第四个数，判断是否满足条件即可，时间复杂度 $O(nm)$。

考场上我开了个 `map` 维护三元组出现的次数，结果时间又爆了，所以考虑再次优化。

注意到 $O(nm)$ 的复杂度本身是没有问题的，超时主要是因为 `map` 常数太大了，改成数组时间上就不会有问题了，但要开成三维，空间又爆掉了。

因为第四个数是枚举到的，所以肯定不会变了，所以可以把这一维优化掉，设 $pos_{x,y}$，表示三元组的第一个数确定时，第二个数为 $x$，和第三个数为 $y$ 的三元组数量，只需要按照题意判断即可。

需要注意，因为 $pos$ 数组是二维的，直接清空会超时，所以只把改过的数清空即可。

### Code


```cpp

#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 5e4 + 5;
const int M = 2e3 + 5;
int n, m, x, y, w, ans, pos[M][M];
struct node{
	int x, y, w;
}a[N];
signed main (){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; ++i){
		cin >> x >> y >> w;
		a[i].x = x, a[i].y = y, a[i].w = w;
	}
	for (int i = 1; i <= n; ++i){
		for (int j = 1; j <= m; ++j){
			if (a[j].x == i) ++pos[a[j].y][a[j].w];
		}
		for (int j = 1; j <= m; ++j){
			if (pos[a[j].x][a[j].y] && pos[a[j].x][a[j].w] && pos[a[j].y][a[j].w]) ++ans;
		}
		for (int j = 1; j <= m; ++j){
		    if (a[j].x == i) pos[a[j].y][a[j].w] = 0;
		}
	}
	cout << ans << '\n';
	return 0;
}

---

