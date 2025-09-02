# Portal1

## 题目背景

Agent 获取资源有很多种方式，HACK 就是其中的一种，侵入 Portal 可以获得很多有用的资源。

ENLIGHTENED 总部因为参加 XM 大战，只剩下一点点可用资源了，所以 ENLIGHTENED 行动指挥想要进行 HACK 活动，尽量增加库存。

## 题目描述

地图上有 $n$ 个可以被 HACK 的 Portal，编号为 $1\sim n$。HACK 第 $i$ 号 Portal 需要时间 $t_i$ 秒，可以 HACK 出 $c_i$ 库存的资源。可是只有有能量的 Portal 才可以 HACK 出资源。第 $i$ 号 Portal 在第 $d_i$ 秒时，能量就会消失殆尽。ENLIGHTEDED 想知道，最多可以增加多少库存，并且按编号小到大输出需要 HACK 的 Portal 的编号。

## 说明/提示

对于 $20\%$ 的数据，$n\leq5$，$t_i\leq 5$，$c_i\leq 5$，$d_i\leq10$。

对于 $40\%$ 的数据，$n\leq 20$，$t_i\leq 10$，$c_i\leq 10$，$d_i\leq 100$。

对于 $60\%$ 的数据，$n\leq50$，$t_i\leq15$，$c_i\leq15$，$d_i\leq1000$。

对于 $100\%$ 的数据，$1\leq n\leq 100$，$1 \leq t_i \leq 20$，$1\leq c_i \leq 20$，$1 \leq d_i \leq 2000$。

## 样例 #1

### 输入

```
3
5 6 5
1 8 2
2 7 3
```

### 输出

```
7
2
1 2```

# 题解

## 作者：Yemaster (赞：2)

[MasterOJ](https://www.masteroj.cn)

看到题目描述，消耗时间？价值？

不就是一个背包吗？

不过加了一个时间限制，那么本来循环从$T_i$~$MAX_T$，就改成$T_i$~$D_i$，高高兴兴地写完代码

```cpp
	for (RI i = 1; i <= N; ++i) {
		scanf("%d%d%d", &T, &D, &C);
		if (D > mx)
			mx = D;
		for (RI j = D - 1; j >= T; --j) {
			if (f[j - T] + C > f[j]) {
				g[j] = g[j - T];
				g[j].push_back(i);
				f[j] = f[j - T] + C;
			}
		}
	}
```

太高兴了，$T,D,C$连数组都不用开了

再循环扫一遍$f$就行了

```cpp
	int ans = -1;
	int mni = -1;
	for (RI i = 1; i <= mx; ++i)
		if (f[i] > ans)
			ans = f[i], mni = i;
	printf("%d\n", ans);
	printf("%d\n", g[mni].size());
	for (vector<int>::iterator it = g[mni].begin(); it < g[mni].end(); it++)
		printf("%d ", *it);
 ```
 
 emmm，全是$WA$，只有$25$分
 
 问题出在哪里呢？
 
 普通的背包的限制都是$Max_T$，所有人的限制都是一样的，肯定不会越界。但是这次的限制不一样，你只是保证了当前没有超时，而不能保证前面的没有超时。
 
 一个修正就出来了：对$D_i$从小到大排序扫。
 
 **为什么这样可以保证不会超时呢？**
 
 证明：$D_i$从小到大排序，时间限制保证了前面的比后面的低，这样后面的操作肯定会比前面的宽裕，这样就不会影响到了。。。
 
 贴个代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define RI register int

using namespace std;

struct Node {
	int T, D, C, id;
	bool operator < (const Node& b) {
		return this->D < b.D;
	}
}a[105];

int main() {
	int N;
	scanf("%d", &N);
	int mx = -1;
	int f[2005];
	vector<int> g[2005];
	memset(f, 0, sizeof(f));
	for (RI i = 1; i <= N; ++i) {
		scanf("%d%d%d", &a[i].T, &a[i].D, &a[i].C);
		a[i].id = i;
		if (a[i].D > mx)
			mx = a[i].D;
	}
	sort(a + 1, a + N + 1);
	for (RI i = 1; i <= N; ++i) {
		for (RI j = a[i].D - 1; j >= a[i].T; --j) {
			if (f[j - a[i].T] + a[i].C > f[j]) {
				g[j] = g[j - a[i].T];
				g[j].push_back(a[i].id);
				f[j] = f[j - a[i].T] + a[i].C;
			}
		}
	}
	int ans = -1;
	int mni = -1;
	for (RI i = 1; i <= mx; ++i)
		if (f[i] > ans)
			ans = f[i], mni = i;
	printf("%d\n", ans);
	printf("%d\n", g[mni].size());
	for (vector<int>::iterator it = g[mni].begin(); it < g[mni].end(); it++)
		printf("%d ", *it);
	return 0;
}
```

---

## 作者：lz2018 (赞：2)

emm...怎么说，这数据搜索妥妥的过啊

按消失殆尽时间由小到大的顺序排序

搜索 寻找方案 替换

输出...就OK了？
```
#include<bits/stdc++.h>
using namespace std;
struct kkk{
	int t,miss,add,code;
}s[105];
int n,t_end,ans,num,k[105],gh[105];
int cmp(kkk a,kkk b)
{
	return a.miss<b.miss||a.miss==b.miss&&a.t<b.t||a.miss==b.miss&&a.t==b.t&&a.add>b.add;
}
void dfs(int i,int time,int added,int um)
{
	if(added>ans)
	{
		ans=added;
		num=um-1;
		for(int j=1;j<um;j++)k[j]=gh[j];
	}
	if(time>t_end)return;
	for(;i<=n;i++)
	{
		if(s[i].miss-s[i].t<=time)continue;
		gh[um]=s[i].code;
		dfs(i+1,time+s[i].t,added+s[i].add,um+1);
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>s[i].t>>s[i].miss>>s[i].add,s[i].code=i;
	sort(s+1,s+n+1,cmp);
	t_end=s[n].miss;
	dfs(1,0,0,1);
	cout<<ans<<endl;
	cout<<num<<endl;
	sort(k+1,k+num+1); 
	for(int i=1;i<=num;i++)
		cout<<k[i]<<" ";
	cout<<endl;
	return 0;
}
```
感觉...有黄题难度就不错了？？...

---

## 作者：BMTXLRC (赞：1)

题目重点：

关于为什么样例不是选择 $1$ 和 $3$ 的解释：只有 $t_{now}+t_i<d_i$ 才能加入第 $i$ 个 Portal，所以在加入了第一个的情况下，不能再加入第三个。

看到数据范围的第一反应就是搜索能不能过，不贪心的情况下应该过不了。



------------


每次搜索找到最近的快结束的 Portal，一直遍历到最后一个 Portal，全部各搜索一遍，搜索途中都得一直记录最大值，但是第一次搜索只能找到最大库存，而不能顺便求出方案，所以我们可以进行两次搜索，第二次如果发现当前答案与 $ans$ 相同，则按顺序输出这个序列。

奇怪的是我即使不对搜索序列排序也能过，不知道是不是数据问题，此题绝对没有蓝题难度。

代码如下：

```cpp
//P4937
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n,ans=0;
struct Portal{int t,d,c,node;}a[N];
vector<int> v;
bool cmp(Portal a,Portal b){return a.d<b.d;}
void dfs(int x,int t,int c){
    for(register int i=x+1;i<=n;i++){
        if(t+a[i].t<a[i].d){
            ans=max(ans,c+a[i].c);
            dfs(i,t+a[i].t,c+a[i].c);
        }
    }
}
void dfs2(int x,int t,int c){
    for(register int i=x+1;i<=n;i++){
        if(t+a[i].t<a[i].d){
            v.push_back(a[i].node);
            if(c+a[i].c==ans){
                printf("%d\n",v.size());
                sort(v.begin(),v.end());
                for(auto i:v) printf("%d ",i);
                exit(0);
            }
            dfs2(i,t+a[i].t,c+a[i].c);
            v.pop_back();
        }
    }
}
int main(){
    scanf("%d",&n);
    for(register int i=1;i<=n;i++){
        scanf("%d %d %d",&a[i].t,&a[i].d,&a[i].c);
        a[i].node=i;
    }
    sort(a+1,a+n+1,cmp);
    dfs(0,0,0);
    printf("%d\n",ans);
    dfs2(0,0,0);
}
```


---

## 作者：木木！ (赞：1)

这题和 [P4823 拯救小矮人](https://www.luogu.com.cn/problem/P4823) 类似，都是贪心 +DP 的简单组合。

首先可以发现所有合法方案都可以转化成按照 $d_i$ 排序之后的相应合法方案，因此可以将原数据按照 $d_i$ 排序。这一步是贪心。

贪心步必不可少，不然在 DP 的时候就没有明确的时序。

DP 的时候，只需要设置两个状态表示考虑到的物品和当前时间就可以了。DP 过程和记录过程都很简单，没有蓝题难度。

还需要说一点的是，这道题特别恶心，他要你按照编号从大到小而不是时间从大到小的顺序输出方案。这里提供一个善用 STL 的方法：

```cpp
vector<int> vec;
vec.reserve(200);
int nowtime = ansn;
for(int nowid=n; hackn[nowid][nowtime]; )
{
	int hkn = hackn[nowid][nowtime];
	vec.push_back(pi[hkn].id);
	nowid = hkn-1;
	nowtime -= pi[hkn].ti;
}

printf("%llu\n",vec.size());

sort(vec.begin(),vec.end());
for(int it : vec)
{
	printf("%d ",it);
}
```

代码量没少很多，但是速度一点不慢，而且还特别花哨（划掉）。使用的原理就是 `vector` 的 `reserve` 函数只会重新分配 `vector` 的空间，所以仍旧可以正常使用 `push_back` 和迭代器，并且速度还有了成倍提升。

附 AC 代码：

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

void chkmax(int& a,int b)
{
	if(b>a)
	{
		a = b;
	}
}

struct prot
{
	int ti;
	int ci;
	int di;
	int id;
};

prot pi[105];

bool cmp(prot a,prot b)
{
	return a.di < b.di;
}

int dp[105][2005];
int hackn[105][2005];

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
	{
		scanf("%d%d%d",&pi[i].ti,&pi[i].di,&pi[i].ci);
		pi[i].id = i;
	}

	sort(pi+1,pi+1+n,cmp);

	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<pi[i].ti; ++j)
		{
			dp[i][j] = dp[i-1][j];
			hackn[i][j] = hackn[i-1][j];
		}
		for(int j=pi[i].ti; j<pi[i].di; ++j)
		{
			if(dp[i-1][j] < dp[i-1][j-pi[i].ti]+pi[i].ci)
			{
				dp[i][j] = dp[i-1][j-pi[i].ti]+pi[i].ci;
				hackn[i][j] = i;
			}
			else
			{
				dp[i][j] = dp[i-1][j];
				hackn[i][j] = hackn[i-1][j];
			}
		}
		for(int j=pi[i].di; j<20*i; ++j)
		{
			dp[i][j] = dp[i-1][j];
			hackn[i][j] = hackn[i-1][j];
		}
	}

	int ansn = 0;
	for(int i=1; i<=2000*n; ++i)
	{
		if(dp[n][i] > dp[n][ansn])
		{
			ansn = i;
		}
	}

	printf("%d\n",dp[n][ansn]);

	vector<int> vec;
	vec.reserve(200);
	int nowtime = ansn;
	for(int nowid=n; hackn[nowid][nowtime]; )
	{
		int hkn = hackn[nowid][nowtime];
		vec.push_back(pi[hkn].id);
		nowid = hkn-1;
		nowtime -= pi[hkn].ti;
	}

	printf("%llu\n",vec.size());

	sort(vec.begin(),vec.end());
	for(int it : vec)
	{
		printf("%d ",it);
	}
}
```

另外，这题如果不用输出方案的话，可以用滚动数组优化，时间效率高很多，代码也很短（只有 30 行多一些），偷懒不放了。

---

