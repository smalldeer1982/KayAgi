# New Year and the Mallard Expedition

## 题目描述

Bob 是一只鸭子。他想要到达 Alice 的巢穴，这样他们就能一起“鸭”了！

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1091F/6ea17347fb888fdf90ed3aa4a06fea6a2b533b11.png) 鸭子是终极动物！（图片由 See Bang 提供）

这段旅程可以表示为一条直线，由 $n$ 段组成。Bob 位于第一段的左侧，而 Alice 的巢穴在最后一段的右侧。每一段都有一定的长度（单位为米），并且有地形类型：草地、湖水或岩浆。

Bob 有三种移动方式：游泳、步行和飞行。他可以在任意时刻切换移动方式或改变方向（即使他处于非整数坐标时也可以），并且切换方式不需要额外时间。Bob 只能在水面上游泳，只能在草地上步行，而可以在任何地形上飞行。飞行每米需要 $1$ 秒，游泳每米需要 $3$ 秒，步行每米需要 $5$ 秒。

Bob 有有限的体力，称为耐力。游泳和步行对他来说很轻松，因此每走或游 1 米，他会获得 1 点耐力。另一方面，飞行非常耗体力，每飞行 1 米会消耗 1 点耐力。停留在原地不会影响他的耐力。当然，他的耐力永远不会变为负数。最初，他的耐力为零。

请问 Bob 到达 Alice 巢穴所需的最短时间是多少？

## 说明/提示

在第一个样例中，Bob 先步行 $5$ 米，用时 $25$ 秒。然后他飞行剩下的 $5$ 米，用时 $5$ 秒。

在第二个样例中，Bob 先游泳 $10$ 米，用时 $30$ 秒。然后他飞越岩浆，用时 $10$ 秒。

在第三个样例中，水塘很小。Bob 先游过水塘，用时 $3$ 秒。但他还不能飞越岩浆，因为他只有 $1$ 点耐力，而需要 $2$ 点。因此他又游回半米，再游前进半米，总共用时 $3$ 秒。现在他有 $2$ 点耐力，可以用 $2$ 秒飞越岩浆。

在第四个样例中，他步行 $50$ 秒，飞行 $10$ 秒，游泳 $15$ 秒，最后飞行 $5$ 秒。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1
10
G
```

### 输出

```
30
```

## 样例 #2

### 输入

```
2
10 10
WL
```

### 输出

```
40
```

## 样例 #3

### 输入

```
2
1 2
WL
```

### 输出

```
8
```

## 样例 #4

### 输入

```
3
10 10 10
GLW
```

### 输出

```
80
```

# 题解

## 作者：Provicy (赞：7)

个人感觉是一道非常好的贪心题...

首先会考虑到草地或水中积累一定的能量来飞行是不比在草地中行走，水中游泳更优的。所以我们只需要贪心地在草地上行走，水中游泳，岩浆上飞行即可。

考虑在经过岩浆，需要飞行的时候能量不够的情况。这意味着我们一定要在之前的草地或者水中积累能量。显然的，在水中积累能量是更优的，因为所消耗的时间更短。所以，当需要积累 $x$ 能量时，如果前面出现过 $W$，则要增加 $3x$ 的时间；否则，需要增加 $5x$ 的时间（因为我们可以把所有要积累的能量都放在第一个水中或者第一个草地去积累，所以这是正确的）。

还要考虑走到最后，如果能量有多余，我们可以考虑在之前经过的草地或水中用飞行来增快速度。显然的，我们要尽量在草地多飞行，如果还有剩下的，那么在水上飞行。那么可以用来增快的能量只有 $\frac{E}{2}$，原因是在那个位置我们不但没有积攒能量还消耗了一个能量。记经过的草地长度为 Groad，则可以增快的长度是 $min(\frac{E}{2},Groad)$。为了方便我们可以直接用 Groad 去更新它。那么我们把剩下 $\frac{E}{2}-Groad$ 的能量给到水上飞行即可。

然后我们发现 $\frac{E}{2}$ 可能不是个整数！观察题目给的数据很巧，多余能量在草地可以每一米增快 $4s$，在水中可以每一米增快 $2s$。所以直接把 $Groad$ 乘上 $2$ 去更新即可，这样就不会出现有小数而精度爆炸的情况了。

代码如下：

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
#include <stack>
#include <map>
#define ri register
#define inf 0x7fffffff
#define E (1)
#define mk make_pair
#define int long long
using namespace std; const int N=200010;
inline int read()
{
	int s=0, w=1; ri char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48), ch=getchar(); return s*w;
}
void print(int x) {if(x<0) x=-x, putchar('-'); if(x>9) print(x/10); putchar(x%10+'0'); }
int n,l[N],T,minn=1e18; char s[N];
signed main()
{
	n=read(); bool wb=false;
	for(ri int i=1;i<=n;i++) l[i]=read();
	scanf("%s",s+1);
	int nowr,Gr,Wr; nowr=Gr=Wr=0;
	for(ri int i=1;i<=n;Gr=min(Gr,nowr), i++)
	{
		if(s[i]=='G') nowr+=l[i], Gr+=l[i]*2, T+=l[i]*5;
		if(s[i]=='W') nowr+=l[i], T+=l[i]*3, wb=true;
		if(s[i]=='L')
		{
			nowr-=l[i]; T+=l[i]; if(nowr>=0) continue;
			if(wb) T-=nowr*3; else T-=nowr*5; nowr=0;
		}
	}
	if(!nowr) printf("%lld\n",T);
	else printf("%lld\n",T-Gr*2-(nowr-Gr));
	return 0;
}
```


---

## 作者：liangbowen (赞：2)

[blog](https://www.cnblogs.com/liangbowen/p/18085715)。提供线性做法，各方面完爆反悔贪心。

---

先钦定**能不飞就不飞**，最后再分配盈余的能量。

可能会在飞 Lava 的时候不够能量，只需要在前面来回移动，刷能量即可。

由于 Swim 比 Walk 快，所以能 Swim 就全部用 Swim 刷能量，不能就 Walk。

最后是分配盈余能量。显然优先把 Walk 换成 Fly，换一格会快 $4s$，能量减少 $2$。Swim 同理。

那么能换多少呢？发现在「不够能量」时必须把前面的能量留下，所以这时在前面的 Land 换是不优的。

所以，累加可以换的最大 Land 长度，结束时与 $\dfrac{\text{能量}}2$ 取 min 即可。

---

直接 double 实现 $\dfrac{\text{能量}}2$ 会[寄](https://codeforces.com/contest/1091/submission/252422794)，所以翻倍存储即可。

[code](https://codeforces.com/contest/1091/submission/252421258)，时间复杂度 $O(n)$。

---

## 作者：daniEl_lElE (赞：0)

反悔贪心。

考虑经过每一段的时候都贪心去飞，然后用前面的效率最高的来抵消飞行的长度。

对于每一段加进优先队列：

* 将这一段中飞的变为他特殊可以的。距离两倍价值差值。
* 重走/游一段距离。距离一倍价值走/游的代价。

需要在每次加之前先计算要多少用自己这一段变成走/游的。

剩下来用堆维护即可。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2,3,"Ofast","inline")
#define int long long
using namespace std;
int a[100005];
char c[100005];
signed main(){
	int n,ans=0; cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]*=2;
	for(int i=1;i<=n;i++) cin>>c[i];
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
	int hg=0,hw=0;
	for(int i=1;i<=n;i++){
		if(c[i]=='G'){
			ans+=a[i];
			int v=0;
			while((!pq.empty())&&a[i]&&pq.top().first==1){
				auto f=pq.top(); pq.pop();
				int cut=min(a[i],f.second);
				a[i]-=cut;
				v+=cut;
				f.second-=cut;
				ans+=f.first*cut;
				if(f.second) pq.push(make_pair(f.first,f.second));
			}
			ans+=a[i]*2;
			pq.push(make_pair(2,a[i]+v*2));
			if(!hg) pq.push(make_pair(5,1e18)),hg=1;
		}
		if(c[i]=='W'){
			ans+=a[i]*2;
			pq.push(make_pair(1,a[i])); 
			if(!hw) pq.push(make_pair(3,1e18)),hw=1;
		}
		if(c[i]=='L'){
			ans+=a[i];
			while(a[i]){
				auto f=pq.top(); pq.pop();
				int cut=min(a[i],f.second);
				a[i]-=cut;
				f.second-=cut;
				ans+=f.first*cut;
				if(f.second) pq.push(make_pair(f.first,f.second));
			}
		}
//		cout<<ans<<" ";
	}
	cout<<ans/2;
	return 0;
}

```

---

