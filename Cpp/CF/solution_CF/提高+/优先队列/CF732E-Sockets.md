# Sockets

## 题目描述

ICM ACPC 世界决赛就要来临了！不幸的是，赛事组织者因为在准备赛题时太忙碌了，他们几乎忘了一个关键点——为参赛者的工作站准备电力资源。  
  
赛场有 $n$ 台为参赛者准备的电脑，第 $i$ 台电脑拥有与正整数 $p_i$ 相等大小的电源。同时，有 $m$ 个可用的插座，第 $j$ 个插座拥有与正整数 $s_j$ 相等的电源。只有当 $p_i = s_j$ 时才可以将第 $i$ 台电脑和第 $j$ 个插座连接。一台电脑只可以接一个插座。不仅如此，如果所有的电脑与插座的电源都不同，那么没有任何电脑可以接通至插座。  
  
为了解决问题，Puch Williams 教授紧急订购了一车适配器（电源分离器）。每个适配器都有一个插头与一个插座，在它们之间还有一个分压器。在将适配器插入一个带有 $x$ 的电源后，适配器上的插座将会拥有一个 $\left \lceil \frac{x}{2} \right \rceil $ 的电源，这代表着将被插入的插座的电源除以 $2$，再取顶。例如：$\left \lceil \frac{10}{2} \right \rceil =5$，$\left \lceil \frac{15}{2} \right \rceil =8$。  
  
每个适配器只能使用一次。它可以被多次串联。例如，在将一个适配器插入一个插入带有 $10$ 电源的插座的适配器时，可以将一个带有 $3$ 电源的电脑插入这个适配器。  
  
组织者们会安装这些适配器，以确保它会同时输送给最多 $c$ 台电脑。如果有多种连接方案，组织者们想要在连接最多 $c$ 台电脑的前提下，使用最少 $u$ 个适配器的方案。  
  
你的任务是帮助组织者们计算完成这个任务最大的 $c$ 和最小的 $u$。  
  
这一车适配器是足够这个任务使用的，同时数据保证至少可以连接一台电脑。

## 样例 #1

### 输入

```
2 2
1 1
2 2
```

### 输出

```
2 2
1 1
1 2
```

## 样例 #2

### 输入

```
2 1
2 100
99
```

### 输出

```
1 6
6
1 0
```

# 题解

## 作者：_edge_ (赞：2)

没人来发题解？那我来说一下我的做法。

其实我第一眼看上去有点想二分图上匹配之类的，但是好像时空会双爆，跑比较快的网络流可能也不太行。

~~然后我就看了一眼标签，贪心？？？？~~

然后我就往贪心去想，发现如果我们把电脑要的电源从大到小排序，然后插座的也从大到小排序，如果当前大的电脑电源能匹配那肯定就匹配掉是最优的。

这个很明显，如果我们现在不匹配，等到后面贡献也只能是 $1$。

然后我们可以考虑如果说他的最大插座电源已经超过了当前的电源，那么我们是不是认为它已经没有贡献了？

答案是肯定的，我们需要把它除以二之后才能产生贡献，这是单调性。

于是我们的基本流程就是，枚举每一个电脑电源，然后把插座都从大到小搞一搞，然后如果当前插座电源大于电脑电源那就除以二，否则如果小了，那就没得用了。

以上的可以数据结构，set 堆都可以维护。

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
const int INF=5e5+5;
struct _node_queue {
	int v,x,id;
	bool operator < (const _node_queue &xx) const {
		if (xx.v!=v) return xx.v>v;
		else return xx.x<x;
	}
}p[INF];
int n,m,b[INF],a[INF],s[INF],ans,ans1;
priority_queue <_node_queue> q; 
bool cmp(_node_queue xx,_node_queue yy) {
	return xx.v<yy.v;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=n;i++) cin>>p[i].v,p[i].id=i;
	for (int i=1;i<=m;i++) 
		cin>>s[i],q.push((_node_queue){s[i],0,i});
	sort(p+1,p+1+n,cmp);
	for (int i=n;i>=1;i--) {
		while (q.size()) {
			_node_queue xx=q.top();q.pop(); 
//			cout<<xx.v<<" ????\n";
			if (xx.v==p[i].v) {
				b[p[i].id]=xx.id;a[xx.id]=xx.x;
				ans++;ans1+=xx.x;
				break;
			} 
			else if (xx.v<p[i].v) {q.push(xx);break;}
			else {
				xx.v++;xx.v/=2;
				xx.x++;
				q.push(xx);
			}
		}
	}
	
	cout<<ans<<" "<<ans1<<"\n";
	for (int i=1;i<=m;i++) cout<<a[i]<<" ";cout<<"\n";
	for (int i=1;i<=n;i++) cout<<b[i]<<" ";cout<<"\n";
	return 0;
}
```


---

## 作者：蒟酱 (赞：1)

功率是 $x$ 的插座插入一个适配器后功率是 $y$，功率是 $y$ 的插座插入一个适配器后功率是 $z$，那么相当于功率是 $x$ 的插座插入两个适配器。  
一个电脑可以用功率小的插座插入较少的适配器表达，也可以用功率大的插座插入较多的适配器表达。这里功率大的插座必然能表达出功率较小的插座。优先使用功率小的插座，就能把功率大的插座和较多的适配器尽可能的节省下来，所以这样是不劣的。  
那就从小到大判断每一个插座是否可行：如果可行，就进行分配；如果不可行，那就插入若干个适配器使得能够分配为止；如果最终还是不能分配就跳过下一个。  
使用 `multimap` 和 `pair` 可以很方便地维护。  
初始每个插座可以使用 $[0,\log w]$ 个适配器，每次判断的复杂度为 $\log n$，总共有 $m$ 个插座，总复杂度是 $\mathcal O(n\log n+m\log m+m\log n\log w)$。采取 `unordered_multimap` 即可做到 $\mathcal O(n+m\log m+m\log w)$。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<map>
#define fi first
#define se second
using std::cin;using std::cout;
using pii=std::pair<int,int>;
constexpr int N=2e5+1;
int n,m,ans1,ans2,r1[N],r2[N];
std::multimap<int,int>s;
pii b[N];
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);cin.tie(nullptr);
	cin>>n>>m;
	for(int i=1,x;i<=n;i++)
		cin>>x,s.emplace(x,i);
	for(int i=1;i<=m;i++)
		cin>>b[i].fi,b[i].se=i;
	sort(b+1,b+m+1);
	for(int i=1;i<=m;i++)for(int j=0;;j++)
		if(auto it=s.find(b[i].fi);it!=s.end()){
			r1[b[i].se]=j;
			r2[it->se]=b[i].se;
			ans1++;
			ans2+=j;
			s.erase(it);
			break;
		}else{
			if(b[i].fi==1)break;
			b[i].fi=(b[i].fi+1)/2;
		}
	cout<<ans1<<' '<<ans2<<'\n';
	for(int i=1;i<=m;i++)cout<<r1[i]<<' ';
	cout<<'\n';
	for(int i=1;i<=n;i++)cout<<r2[i]<<' ';
	return 0;
}
```

---

