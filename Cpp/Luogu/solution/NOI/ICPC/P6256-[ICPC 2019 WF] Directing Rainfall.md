# [ICPC 2019 WF] Directing Rainfall

## 题目描述

波尔图和附近的杜罗河谷因生产波特酒而闻名。来自世界各地的葡萄酒爱好者来到这里品尝这种甜美的葡萄酒。国际波特酒鉴赏家联盟（ICPC）正在组织到杜罗河上游葡萄园的旅行。为了让游客的参观更加愉快，ICPC 最近在葡萄园上方安装了遮阳篷。这些遮阳篷保护游客在葡萄藤间漫步和品尝陈年波特酒时不被晒伤。

不幸的是，遮阳篷存在一个小问题。葡萄需要阳光和水才能生长。虽然遮阳篷能透过足够的阳光，但它们完全防水。这意味着雨水可能无法到达下方的葡萄园。如果不采取措施，今年的葡萄酒收成将岌岌可危！

ICPC 想通过在遮阳篷上打孔来解决这个问题，以便雨水能透过遮阳篷到达下方的葡萄园。由于雨季即将到来，时间紧迫，ICPC 希望以最少的打孔次数实现这一目标。我们将考虑这个问题的二维版本。需要浇灌的葡萄园是 $x$ 轴上的一个区间，遮阳篷被建模为 $x$ 轴上方的线段。遮阳篷是倾斜的，即不平行于 $x$ 轴或 $y$ 轴（参见图 F.1 了解示例）。雨水从无限高处直线下落。当雨水落在遮阳篷上时，它会流向遮阳篷的低端并从那里落下，除非在雨水落下的地方和遮阳篷的低端之间有一个孔——在这种情况下，雨水将通过孔落下。雨水从遮阳篷上落下后，继续垂直下落。

这种情况会重复，直到雨水落到地面（$x$ 轴）上。

出于法律原因，您必须确保至少有一些雨水是直接从葡萄园上方落到葡萄园的。这是为了防止任何葡萄园从邻近的葡萄园窃取所有的雨水（参见第二个样例输入了解示例）。

## 说明/提示

来源：ICPC 世界总决赛 2019 问题 F：引导降雨。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
10 20 5
32 50 12 60
30 60 8 70
25 70 0 80
15 30 28 40
5 20 14 25
```

### 输出

```
2```

## 样例 #2

### 输入

```
2 4 2
3 2 0 3
5 2 1 5```

### 输出

```
1```

# 题解

## 作者：ix35 (赞：9)

巨大多恐怖题。

首先要设法给这些挡板排个序，使得水只能从排在前面的流到排在后面的。

直接使用 sort 是不可行的，因为我们定义的是偏序关系，只有 $x$ 区间有交的两个挡板才能比较大小，但由于是偏序，可以考虑用拓扑排序的办法解决。

按 $x$ 从左到右扫描，用一个 set 按照 $y$ 的顺序维护一个包含当前 $x$ 坐标的挡板集合（由于它们的 $x$ 区间有交，所以是全序），在每一个挡板的端点处，将它此时在 set 中的前驱向它连边，它向 set 中的后继连边。

得到的图中进行一次拓扑排序，就得到了一个可行的顺序。

得到顺序之后考虑 DP：

从下往上扫描挡板，令 $f_i$ 表示仅考虑当前的挡板时，$x=i$ 处的雨水要落到规定区间至少需要的洞数。

现在加入一块覆盖区间 $[l,r]$ 且左边低右边高的挡板，考虑对 $f$ 的影响：

- 如果要保持原有的轨迹，那么 $[l+1,r]$ 内所有点都需要在这块挡板上凿一个洞；

- $[l+1,r]$ 内的某个点 $i$ 也可以选择流到 $[l,i)$ 的某个点后再落下。

所以这个操作可以概括为：

- 先将 $[l+1,r]$ 内的 $f$ 区间增加 $1$；

- 再对 $[l,r]$ 中每个 $f_i$ 更新为区间内前缀最小值。

左高右低同理，不过是求后缀最小值。

我们发现没有什么好的数据结构直接支持取一个区间的前缀最小值这个操作，所以考虑更改一下维护信息。

令 $g_i=f_i-f_{i-1}$，区间加操作就是 $g_i$ 的单点修改。

而对于区间取前缀最小值操作，我们发现有 $f_i\leq f_{i-1}$，所以 $g_i\leq 0$，我们需要找到所有 $g_i>0$ 的 $i$，然后将它修改为 $0$，同时为了保证后面的信息正确，我们实际上要找到 $i$ 后面的一些 $g_j<0$ 的 $j$，将 $g_j$ 和 $g_i$ 抵消。

所以在做前缀最小值时，我们顺次找 $g_i>0$ 的 $i$，然后找 $i$ 后面第一个满足 $g_j<0$ 的 $j$，如果 $|g_j|>|g_i|$，就将 $g_j$ 改为 $g_j+g_i$ 并将 $g_i$ 清零；否则就将 $g_i$ 变为 $g_i+g_j$ 并将 $g_j$ 清零。如果这样的 $j$ 已经在区间外，就直接这个 $g_i$ 加到 $g_{r+1}$ 上。

可以用 set 分别维护 $g_i>0$ 和 $g_i<0$ 的情况，由于访问过的元素大多被删除，所以最终复杂度是 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1000010,INF=2e9,INFV=1e8;
struct P {
	P (int a=0,int c=0,int d=0) {x=a,bel=c,flg=d;}
	int x,bel,flg;
}p[MAXN*2];
struct Tarp {
	Tarp (int a=0,int b=0,int c=0,int d=0,int e=0) {x1=a,y1=b,x2=c,y2=d,id=e;}
	int x1,x2,y1,y2,id;
}t[MAXN];
int l,r,n,tot,cnt,ans,in[MAXN],sx[MAXN];
vector <int> v[MAXN];
multiset < pair<int,int> > s1,s2;
bool cmp (P a,P b) {return a.x<b.x;}
bool operator < (Tarp a,Tarp b) {
//	cout << a.x1 << "  " << a.x2 << "  " << b.x1 << "  " << b.x2 << endl;
	if (a.x2<b.x1||a.x1>b.x2) {return 0;}
	if (a.x1<b.x1&&b.x1<a.x2) {
//		cout << 1ll*a.y1*(a.x2-a.x1)+1ll*(a.y2-a.y1)*(b.x1-a.x1) << "  " << 1ll*b.y1*(a.x2-a.x1) << endl;
		return 1ll*a.y1*(a.x2-a.x1)+1ll*(a.y2-a.y1)*(b.x1-a.x1)<1ll*b.y1*(a.x2-a.x1);
	} else {
		return 1ll*b.y1*(b.x2-b.x1)+1ll*(b.y2-b.y1)*(a.x1-b.x1)>1ll*a.y1*(b.x2-b.x1);
	}
}
set <Tarp> st;
void add_edge (int a,int b) {
	in[b]++;
	v[a].push_back(b);
	return;
}
void print () {
	multiset< pair<int,int> >::iterator it,it2;
	it=s1.begin(),it2=s2.begin();
	while (it!=s1.end()&&it2!=s2.end()) {
		pair<int,int> a=(*it),b=(*it2);
		if (a.first<=b.first) {
			printf("%d  %d\n",a.first,a.second);
			it++;
		} else {
			printf("%d  %d\n",b.first,b.second);
			it2++;
		}
	}
	while (it!=s1.end()) {
		pair<int,int> a=(*it);
		printf("%d  %d\n",a.first,a.second);
		it++;
	}
	while (it2!=s2.end()) {
		pair<int,int> b=(*it2);
		printf("%d  %d\n",b.first,b.second);
		it2++; 
	}
}
int main () {
	scanf("%d%d%d",&l,&r,&n);
	l*=2,r*=2;
	for (int i=1;i<=n;i++) {
		scanf("%d%d%d%d",&t[i].x1,&t[i].y1,&t[i].x2,&t[i].y2);
		t[i].x1*=2,t[i].x2*=2;
		if (t[i].x1>t[i].x2) {swap(t[i].x1,t[i].x2),swap(t[i].y1,t[i].y2);}
		t[i].id=i;
		p[++tot]=P(t[i].x1,i,0);
		p[++tot]=P(t[i].x2,i,1);
	}
	st.insert(Tarp(-1,0,2e9+1,0,0));
	st.insert(Tarp(-1,1e9+1,2e9+1,1e9+1,n+1));
	sort(p+1,p+tot+1,cmp);
	for (int i=1;i<=tot;i++) {
		if (p[i].flg==1) {
			st.erase(t[p[i].bel]);
		}
		set<Tarp>::iterator it=st.lower_bound(t[p[i].bel]),it2;
		it2=it;
		it2--;
		if ((*it).id!=n+1) {add_edge(p[i].bel,(*it).id);}
		if ((*it2).id!=0) {add_edge((*it2).id,p[i].bel);}
		if (p[i].flg==0) {
			st.insert(t[p[i].bel]);
		}
	}
	queue <int> q;
	for (int i=1;i<=n;i++) {
		if (!in[i]) {q.push(i);}
	}
	while (!q.empty()) {
		int a=q.front();
		q.pop();
		sx[++cnt]=a;
		int len=v[a].size();
		for (int j=0;j<len;j++) {
			if (--in[v[a][j]]==0) {q.push(v[a][j]);} 
		}
	}
	s1.insert(make_pair(r+1,INFV));
	s2.insert(make_pair(l,-INFV));
	multiset< pair<int,int> >::iterator it,it2;
	for (int i=1;i<=n;i++) {
		Tarp tmp=t[sx[i]];
		if (tmp.y1<tmp.y2) {
			s1.insert(make_pair(tmp.x1+1,1));
			s2.insert(make_pair(tmp.x2+1,-1));
			it=s1.lower_bound(make_pair(tmp.x1+1,-INF-1));
			while (it!=s1.end()&&(*it).first<=tmp.x2) {
				//printf("    %d  %d\n",(*it).first,(*it).second);
				int flg=1;
				it2=s2.lower_bound(make_pair((*it).first,-INF-1));
				while (it2!=s2.end()&&(*it2).first<=tmp.x2) {
					//printf("        %d  %d\n",(*it2).first,(*it2).second);
					if ((*it).second>-(*it2).second) {
						pair<int,int> tmp2=(*it);
						s1.erase(it);
						s1.insert(make_pair(tmp2.first,tmp2.second+(*it2).second));
						s2.erase(it2);
						it=s1.lower_bound(make_pair(tmp2.first,-INF-1));
						it2=s2.lower_bound(make_pair((*it).first,-INF-1));
					} else if ((*it).second==-(*it2).second) {
						s1.erase(it);
						s2.erase(it2);
						flg=0;
						break;
					} else {
						pair<int,int> tmp2=(*it2);
						s2.erase(it2);
						s2.insert(make_pair(tmp2.first,tmp2.second+(*it).second));
						s1.erase(it);
						flg=0;
						break;
					}
				}
				if (flg) {
					s1.insert(make_pair(tmp.x2+1,(*it).second));
					s1.erase(it);
					//cout << "             " << i << "  " << tmp.x1+1 << endl;
				}
				it=s1.lower_bound(make_pair(tmp.x1+1,-INF-1));
			}
		} else {
			s1.insert(make_pair(tmp.x1,1));
			s2.insert(make_pair(tmp.x2,-1));
			it=s2.lower_bound(make_pair(tmp.x2,INF+1));
			while (it!=s2.begin()&&(*(--it)).first>=tmp.x1+1) {
				//printf("    %d  %d\n",(*it).first,(*it).second);
				int flg=1;
				it2=s1.lower_bound(make_pair((*it).first,INF+1));
				while (it2!=s1.begin()&&(*(--it2)).first>=tmp.x1+1) {
					//printf("        %d  %d\n",(*it2).first,(*it2).second);
					if (-(*it).second>(*it2).second) {
						pair<int,int> tmp2=(*it);
						s2.erase(it);
						s2.insert(make_pair(tmp2.first,tmp2.second+(*it2).second));
						it=s2.find(make_pair(tmp2.first,tmp2.second+(*it2).second));
						s1.erase(it2);
						it2=s1.lower_bound(make_pair((*it).first,INF+1));
					} else if (-(*it).second==(*it2).second) {
						s2.erase(it);
						s1.erase(it2);
						flg=0;
						break;
					} else {
						pair<int,int> tmp2=(*it2);
						s1.erase(it2);
						s1.insert(make_pair(tmp2.first,tmp2.second+(*it).second));
						s2.erase(it);
						flg=0;
						break;
					}
				}
				if (flg) {
					s2.insert(make_pair(tmp.x1,(*it).second));
					s2.erase(it);
				}
				it=s2.lower_bound(make_pair(tmp.x2,INF+1));
			}
		}
		//printf("%d\n",i);
		//print();
		//printf("----------------------------\n");
	}
	int las=-1,val=INFV;
	ans=INF;
	it=s1.begin(),it2=s2.begin();
	while (it!=s1.end()&&it2!=s2.end()) {
		pair<int,int> a=(*it),b=(*it2);
		if (a.first<=b.first) {
			//printf("%d  %d\n",a.first,a.second);
			if (las<=r&&a.first>l) {ans=min(ans,val);}
			val+=a.second;
			las=a.first;
			it++;
		} else {
			//printf("%d  %d\n",b.first,b.second);
			if (las<=r&&b.first>l) {ans=min(ans,val);}
			val+=b.second;
			las=b.first;
			it2++;
		}
	}
	while (it!=s1.end()) {
		pair<int,int> a=(*it);
		//printf("%d  %d\n",a.first,a.second);
		if (las<=r&&a.first>l) {ans=min(ans,val);}
		val+=a.second;
		las=a.first;
		it++;
	}
	while (it2!=s2.end()) {
		pair<int,int> b=(*it2);
		//printf("%d  %d\n",b.first,b.second);
		if (las<=r&&b.first>l) {ans=min(ans,val);}
		val+=b.second;
		las=b.first;
		it2++; 
	}
	printf("%d\n",ans);
	return 0;
}

```




---

## 作者：Piggy343288 (赞：3)

我认为，这道题是我学 OI 历史以来做过的最难写，最难受，最变态，最不可做，最怀疑人生的题。  

~~然后还莫名其妙遇见了！~~  

给出一种时间复杂度略劣于 ix35 的做法。因为本人码力不是很好，因此认为这道题讲讲代码写法也很必要。

题意就是给一些线段上戳洞，使得对于给定的一个区间 $[l,r]$，从无穷远到水平轴有一条通路。  

### Part 1：转化

首先，我们考虑戳洞的方案，不难发现如果我们只戳了下面的挡板却不戳上面的挡板不一定有什么用，这启发我们可以先对所有的挡板进行处理，使得有一种戳洞的顺序是合理的。感性理解，我们不能单纯按横坐标排序，这样错得离谱。另一方面，对于这种涉及图的，还是偏序关系的，我们考虑拓扑排序。  

然后考虑怎么建图。第一个想法是按照纵坐标从上到下连边，但这样横坐标的处理就迷惑了起来。我们只好采取扫描线类似思想，从左到右扫描，**对于每个挡板的端点**，对 set 中的前驱和后继分别连边，不仅保证了偏序关系，还减少了不必要的边。  

第一步就结束了，对于我们建的图，跑一边拓扑排序，可以得到一个挡板序列。代码如下：  

```
// 读入&&建边
    cin >> l >> r >> n;
    for (int i = 1; i <= n; i++)
        lines[i].read();
    sort(lines + 1, lines + 1 + n, cmp);
    l <<= 1, r <<= 1;
    for (int i = 1; i <= n; i++)
    {
        lines[i].id = i;
        lines[i].enlarge();
    }
    set<Line> s;
    priority_queue<pii> q;
    for (int i = 1; i < n; i++)
    {
        while (q.size() && -q.top().first < lines[i].a)
            s.erase(lines[q.top().second]), q.pop();
        auto it = s.lower_bound(lines[i]);
        if (it != s.begin())
            e[i].push_back(prev(it)->id), ++deg[prev(it)->id];
        if (it != s.end())
            e[it->id].push_back(i), ++deg[i];
        s.insert(lines[i]);
        q.push({-lines[i].c, i});
    }
```
按照题解所说，模拟即可。  

```
// 拓扑
    queue<int> q;    
    for (int i = 1; i <= n; i++)
        if (!deg[i])
            q.push(i);    
    while (q.size())
    {
        int u = q.front();
        q.pop();
        //这里应该有一大段代码
        for (auto v : e[u])
            if (!(--deg[v]))
                q.push(v);
    }
```
这是很标准的拓扑。

### Part 2：DP  

转化为序列以后就可以快乐 DP 了。先把整个区间分段便于处理。  

我们定义，$\operatorname{dp}(i,j)$ 表示前 $i$ 个挡板处理完，落在第 $j$ 个区间所需要戳的最少的洞的个数，然后考虑转移。  

首先，这东西倒着做比正着做好做得多。因此来倒着转移。

显然转移要沿着线段转移。对于一条左低右高的线段，如果我们想要落在这个线段的区间的话，显然应该在上边戳个洞，那么我们直接对这一段区间 $(l,r]+1$。那么对于左高右低的线段同理，也是转化成区间操作。具体的不在赘述。总之是显然可做的。  

```
// DP 部分，塞在上文所留的空里
if (lines[u].b > lines[u].d)
        {
            auto it = f.lower_bound(pii(lines[u].a + 1, -inf));
            int sum = 0;
            vector<set<pii>::iterator> vec;
            for (; it != f.end() && it->first <= lines[u].c; ++it)
            {
                sum += it->second;
                vec.push_back(it);
                auto fd = g.lower_bound(pii(it->first, -inf));
                if (fd == g.end())
                    continue;
                while (fd != g.end() && sum + fd->second >= 0 && fd->first <= lines[u].c)
                {
                    sum += fd->second;
                    tmp = next(fd);
                    g.erase(fd);
                    fd = tmp;
                }
                if (sum > 0 && fd != g.end() && fd->first <= lines[u].c)
                {
                    int p = fd->first;
                    sum += fd->second;
                    g.erase(fd), g.insert(pii(p, sum));
                    sum = 0;
                }
            }
            for (auto fd : vec)
                f.erase(fd);
            if (sum > 0)
                f.insert(pii(lines[u].c + 1, sum));
            f.insert(pii(lines[u].a, 1)), g.insert(pii(lines[u].c, -1));
        }
        
```
因为篇幅原因，另一种情况的就不给出了。实际上一点点迭代模拟即可。  

### Part 3：统计答案和时间复杂度
考虑区间赋值的操作，在线段树上做前缀后缀 $\min$ 是很容易的，操作几次以后就不变了，因此可以直接区间赋值了。更具体的，我们考虑维护区间单增单减，利用 segment beats 的理论我们直接把这个操作变成可赋值的操作。   
最后统计答案的时候，我们只需要遍历 set 去看所有处于边界的线段，对这样的线段 ans 取 $\min$ 即可！

时间复杂度用势能分析，修改增加 $\log n$ 的势能，每点势能的减少的时间复杂度为 $O(\log n)$，总的时间复杂度是 $O(n\log^2n)$。   

```
    int ans = INT_MAX, sum = 0;
    f.insert(pii(l, 0)), f.insert(pii(r, 0)), f.insert(g.begin(), g.end());
    for (auto it = f.begin(); it != f.end(); it++)
    {
        sum += it->second;
        if (next(it) == f.end() || it->first != next(it)->first)
        {
            if (it->first >= l && it->first <= r)
                ans = min(ans, sum);
        }
    }
```
这是统计答案部分的代码，和上文所说相符。
你需要注意的是，此题的 dp 是极不寻常的。别问我 dp 数组在哪里，在 set 里（bushi）。  

另外，讨厌我使用的这台电脑，怎么大括号换行的。

---

## 作者：_ANIG_ (赞：1)

[传送门](https://www.luogu.com.cn/problem/P6256)

本题主要分为两部分：排序和 dp。
# 排序
如果线段 $a$ 上的水可以落到线段 $b$ 上，则线段 $a$ 要排在线段 $b$ 前面。

这样我们才能从前往后 dp。

由于不存在两个线段相交，所以不存在环。

也就是把图建出来取任意一个拓扑序即可。

考虑如何判断线段 $a$ 是否排在线段 $b$ 前面。

可以发现，只要存在任意一个横坐标 $x$，满足 $x$ 同时在线段 $a,b$ 对应的横坐标区间上，且 $x$ 在 $a$ 上对应的纵坐标大于 $b$ 上对应的纵坐标，则 $a$ 应排在线段 $b$ 前面。

可以发现，此时即使 $a$ 上的水落不到 $b$ 上，$b$ 上的水无论如何都落不到 $a$ 上，所以把 $a$ 排到 $b$ 前面不会影响正确性。

直接算解析式判断即可。

现在问题转化为找到任意一个同时存在于两个线段上的 $x$ 坐标。

可以直接取两个线段左端点的最大值。

由于可能有精度误差，所以需要除法变乘法。

暴力判断所有点对建图，拓扑排序，复杂度 $O(n^2)$。

可以发现有很多无用边。

对于每条线段，做一条经过其左端点，垂直 $x$ 轴的直线，所交到的上下两个最近的线段，只需要维护这两个线段和它的偏序关系即可。

由于线段没有交点，所以可以直接从左往右扫一遍，用 set 维护所有线段的纵坐标的大小关系。

这样这部分总复杂度 $O(n\log n)$。
# DP
设在删除前 $i$ 条线段后，横坐标为 $j$ 的雨滴垂下落，第一次被阻断的点为 $P$，则 $f_{i,j}$ 表示删除前 $i$ 条线段后，雨滴想要到达点 $P$ 的最小代价。

每次，对于第 $i$ 条线段，线段上的所有点都可以不花费代价流到更低点。

在删除线段 $i$ 后，线段内部的点要想往下落，需要戳一个洞，所以要给线段内部的区间的 dp 值加 $1$。

即问题转化为区间每个数变成这个区间的前缀最小值或后缀最小值，区间加。

直接线段树上打 tag 就能维护。

每个点打一个区间每个数变成前缀或后缀最小值的 tag，再维护一个区间取 $\min$ 的 tag 和区间赋值 tag。

在下传的时候就要打上区间取 $\min$ 的 tag，如果同时有每个数变成前缀和后缀最小值的 tag，就替换成一个区间赋值成区间最小值的 tag。

这样总复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5,inf=1e9;
namespace tr{
    struct node{
    	int l,r,laz1,laz2,add,laz,chm,sm;
    }p[N<<2];
    int w[N];
    void upset(int x){
    	p[x].sm=min(p[x<<1].sm,p[x<<1|1].sm);
    }
    void reset(int x,int l,int r){
    	p[x].l=l,p[x].r=r;p[x].laz=p[x].chm=inf;
    	if(l==r){
    		p[x].sm=w[l];
    		return;
    	}
    	int mid=l+r>>1;
    	reset(x<<1,l,mid);
    	reset(x<<1|1,mid+1,r);
    	upset(x);
    }
	void sets(int x,int sm){
        p[x].laz1=p[x].laz2=p[x].add=0;
        p[x].chm=inf;
        p[x].laz=sm;
        p[x].sm=sm;
    }
    void g1(int x){
    	if(p[x].laz!=inf)return;
    	p[x].laz1=1;
    	if(p[x].laz2)sets(x,p[x].sm);
    }
    void g2(int x){
    	if(p[x].laz!=inf)return;
    	p[x].laz2=1;
    	if(p[x].laz1)sets(x,p[x].sm);
    }
    void add(int x,int sm){
    	if(p[x].laz!=inf){
    		p[x].laz+=sm;
    		p[x].sm+=sm;
    		return;
    	}
    	p[x].sm+=sm;
    	p[x].add+=sm;
    	if(p[x].chm!=inf)p[x].chm+=sm;
    }
    void chmin(int x,int sm){
    	if(p[x].laz!=inf)p[x].laz=min(p[x].laz,sm);
    	else p[x].chm=min(p[x].chm,sm);
    	p[x].sm=min(p[x].sm,sm);
    }
    void dnset(int x){
	    if(p[x].add){
    		add(x<<1,p[x].add);
    		add(x<<1|1,p[x].add);
    		p[x].add=0;
    	}
		if(p[x].chm!=inf){
    		chmin(x<<1,p[x].chm);
    		chmin(x<<1|1,p[x].chm);
    		p[x].chm=inf;
    	}
    	if(p[x].laz1){
    		g1(x<<1);
    		chmin(x<<1|1,p[x<<1].sm);
    		g1(x<<1|1);
    		p[x].laz1=0;
    	}
    	if(p[x].laz2){
		    g2(x<<1|1);
		    chmin(x<<1,p[x<<1|1].sm);
    		g2(x<<1);
    		p[x].laz2=0;
    	}
    	if(p[x].laz!=inf){
    		sets(x<<1,p[x].laz);
    		sets(x<<1|1,p[x].laz);
    		p[x].laz=inf;
    	}
    }
    int g1(int x,int l,int r,int sm){
    	if(l<=p[x].l&&r>=p[x].r){
    		chmin(x,sm);
    		g1(x);
    		return p[x].sm;
    	}
    	int mid=p[x].l+p[x].r>>1,res=0;
    	dnset(x);
    	if(r<=mid)res=g1(x<<1,l,r,sm);
    	else if(l>mid)res=g1(x<<1|1,l,r,sm);
    	else res=g1(x<<1|1,l,r,g1(x<<1,l,r,sm));
    	upset(x);
    	return res;
    }
    int g2(int x,int l,int r,int sm){
    	if(l<=p[x].l&&r>=p[x].r){
    		chmin(x,sm);
    		g2(x);
    		return p[x].sm;
    	}
    	int mid=p[x].l+p[x].r>>1,res=0;
    	dnset(x);
    	if(r<=mid)res=g2(x<<1,l,r,sm);
    	else if(l>mid)res=g2(x<<1|1,l,r,sm);
    	else res=g2(x<<1,l,r,g2(x<<1|1,l,r,sm));
    	upset(x);
    	return res;
    }
    void add(int x,int l,int r,int sm){
    	if(l<=p[x].l&&r>=p[x].r){
    	//	cout<<p[x].l<<" "<<p[x].r<<"+"<<sm<<endl;
    		add(x,sm);
    		return;
    	}
    	int mid=p[x].l+p[x].r>>1;
    	dnset(x);
    	if(l<=mid)add(x<<1,l,r,sm);
    	if(r>mid)add(x<<1|1,l,r,sm);
    	upset(x);
    }
}
int idx,st,ed,n,m,rd[N],nw;
struct node{
	int x1,y1,x2,y2,bh;
	friend bool operator<(node a,node b){
		return (__int128)(1ll*a.y1*(a.x2-a.x1)+1ll*(a.y2-a.y1)*(nw-a.x1))*(b.x2-b.x1)<(__int128)(1ll*b.y1*(b.x2-b.x1)+1ll*(b.y2-b.y1)*(nw-b.x1))*(a.x2-a.x1);
	}
}p[N],tmp[N];
struct nodes{
	node sm;
	int op;
}g[N];
vector<int>jl,e[N];
deque<int>q;
set<node>qs;
int fd(int x){
	return lower_bound(jl.begin(),jl.end(),x)-jl.begin()+1;
}
void add(int b,int a){
	e[a].push_back(b);
	rd[b]++;
}
void SORT(){
	for(int i=1;i<=n;i++){
		g[fd(p[i].x1)]={p[i],1};
		g[fd(p[i].x2)]={p[i],2};
	}
	for(int i=1;i<=m;i++){
		if(!g[i].op)continue;
		nw=jl[i-1];
		if(g[i].op==1){
			auto w=qs.insert(g[i].sm).first,a=w,b=w;
			if(a!=qs.begin()){
				a--;
				add((*a).bh,(*w).bh);
			}
			b++;
			if(b!=qs.end()){
				add((*w).bh,(*b).bh);
			}
		}else{
			qs.erase(qs.find(g[i].sm));
		}
	}
	for(int i=1;i<=n;i++)if(!rd[i])q.push_back(i);
	while(q.size()){
		int x=q.front();
		q.pop_front();
		tmp[++idx]=p[x];
		for(auto c:e[x]){
			rd[c]--;
			if(!rd[c])q.push_back(c);
		}
	}
	memcpy(p,tmp,sizeof(p));
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>st>>ed>>n;
	jl.push_back(st);
	jl.push_back(ed);
	for(int i=1;i<=n;i++)cin>>p[i].x1>>p[i].y1>>p[i].x2>>p[i].y2,p[i].bh=i,jl.push_back(p[i].x1),jl.push_back(p[i].x2);
	sort(jl.begin(),jl.end());
	m=jl.size();
	for(int i=1;i<=n;i++)if(p[i].x1>p[i].x2)swap(p[i].x1,p[i].x2),swap(p[i].y1,p[i].y2);
	st=fd(st);ed=fd(ed);
	SORT();
	for(int i=1;i<=n;i++)p[i].x1=fd(p[i].x1),p[i].x2=fd(p[i].x2);
	for(int i=1;i<=m;i++)tr::w[i]=inf;
	for(int i=st;i<=ed;i++)tr::w[i]=0;
	tr::reset(1,1,m);
	for(int i=1;i<=n;i++){
		if(p[i].y1>p[i].y2)tr::g1(1,p[i].x1,p[i].x2,inf);
		else tr::g2(1,p[i].x1,p[i].x2,inf);
		if(p[i].x1+1<=p[i].x2-1)tr::add(1,p[i].x1+1,p[i].x2-1,1);
	}
	cout<<tr::g1(1,st,ed,inf);
}
```

---

## 作者：Leasier (赞：0)

~~阴间 DS。能不能少出点这种题啊。~~

看到未给定坠落时雨滴的顺序，考虑给顺序进行一个钦定（即只能从前面的掉落到后面的）。

但是这里的限制不太能构成树的结构，考虑找出若干先后关系后拓扑排序。这里显然是无环的。

对于某一组特定的 $a, b$ 间的关系，不妨钦定 $(x_1)_a < (x_1)_b$，则我们要求 $(x_1)_b$ 在 $l_1$ 上的投影点的纵坐标 $< (y_1)_b$。

我们考虑按 $x$ 排序，在加入和删除一个点时找出当前在集合中按上述方式排序时它的前驱后继连边。该操作结束后拓扑排序即可找出一组我们期待的顺序。

接下来考虑 dp。设 $dp_{i, j}$ 表示考虑顺序中的前 $i$ 条线段，现在落在横坐标为 $j$ 的位置时的最小穿孔数量。

初值：$dp_{0, i} = [i < l \operatorname{or} i > r] +\infty$。

转移需要分斜线段向上还是向下讨论。这里讲一下向上的情况。下面默认 $(x_1)_i < (x_2)_i$。

- $j < (x_1)_i \operatorname{or} j > (x_2)_i$：$dp_{i, j} = dp_{i - 1, j}$。
- $dp_{i, (x_1)_i} = \displaystyle\min_{j = (x_1)_i}^{(x_2)_i} dp_{i - 1, j}$。
- $(x_1)_i < (x_1)_i \leq (x_2)_i$：$dp_{i, j} = \displaystyle\min_{k = j}^{(x_2)_i} dp_{i - 1, k} + 1$。

答案：$\displaystyle\min_{i = l}^r dp_{n, i}$。

直接写暴力时需要注意两个整点之间的位置可能也会被用到。下面离散化前也需要这个操作。

为了优化这个 $O(nw)$ 暴力 dp，我们显然可以先进行一个离散化（想清楚哪些端点 $\pm 1$ 也要离散化，要不然可能会出现一些神秘的错误；当然全都要也可以），这样第二维的大小就是 $O(n)$ 的了。

接下来考虑数据结构优化。不难发现我们可以将上面的转移拆成两部分：

- 给 $[(x_1)_i, (x_2)_i]$ 中的位置取后缀 $\min$。
- 给 $((x_1)_i, (x_2)_i]$ 中的位置加 $1$。

这两个操作可以通过在线段树上打标记来进行一个维护。

斜线段向下的情况我们还需要取前缀 $\min$。打一个优先级与取后缀 $\min$ 相等的标记类似维护即可。

时间复杂度为 $O(n \log n)$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
#include <cstdio>

using namespace std;

typedef long long ll;

int x1[500007], y1[500007], x2[500007], y2[500007];

typedef struct Compare_tag {
	bool operator ()(const int a, const int b){
		if (x1[a] > x1[b]) return !Compare_tag()(b, a);
		return (ll)(y1[b] - y1[a]) * (x2[a] - x1[a]) < (ll)(y2[a] - y1[a]) * (x1[b] - x1[a]);
	}
} Compare;

typedef struct Node1_tag {
	int id;
	int x;
	int type;
	Node1_tag(){}
	Node1_tag(int id_, int type_){
		id = id_;
		type = type_;
		if (type == 1){
			x = x1[id];
		} else {
			x = x2[id];
		}
	}
} Node1;

typedef struct {
	int nxt;
	int end;
} Edge;

typedef struct {
	int l;
	int r;
	int add;
	int pre;
	int suf;
	int min;
} Node2;

int cnt = 0;
int deg[500007], head[500007], order[500007], bucket[3000007];
Node1 a[1000007];
Edge edge[2000007];
Node2 tree[12000007];
set<int, Compare> s;
queue<int> q;

bool operator <(const Node1 a, const Node1 b){
	return a.x < b.x;
}

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

inline void update(int x){
	tree[x].min = min(tree[x * 2].min, tree[x * 2 + 1].min);
}

void build(int x, int l, int r, int L, int R){
	tree[x].l = l;
	tree[x].r = r;
	tree[x].pre = tree[x].suf = 0x7fffffff;
	if (l == r){
		tree[x].min = L <= l && l <= R ? 0 : 2e9;
		return;
	}
	int mid = (l + r) >> 1;
	build(x * 2, l, mid, L, R);
	build(x * 2 + 1, mid + 1, r, L, R);
	update(x);
}

inline void pushdown(int x){
	int ls = x * 2, rs = x * 2 + 1;
	if (tree[x].add != 0){
		tree[ls].add += tree[x].add;
		if (tree[ls].pre != 0x7fffffff) tree[ls].pre += tree[x].add;
		if (tree[ls].suf != 0x7fffffff) tree[ls].suf += tree[x].add;
		tree[ls].min += tree[x].add;
		tree[rs].add += tree[x].add;
		if (tree[rs].pre != 0x7fffffff) tree[rs].pre += tree[x].add;
		if (tree[rs].suf != 0x7fffffff) tree[rs].suf += tree[x].add;
		tree[rs].min += tree[x].add;
		tree[x].add = 0;
	}
	if (tree[x].pre != 0x7fffffff){
		tree[ls].pre = min(tree[ls].pre, tree[x].pre);
		tree[ls].min = min(tree[ls].min, tree[x].pre);
		tree[rs].pre = min(tree[rs].pre, tree[ls].min);
		tree[rs].min = min(tree[rs].min, tree[ls].min);
		tree[x].pre = 0x7fffffff;
	}
	if (tree[x].suf != 0x7fffffff){
		tree[rs].suf = min(tree[rs].suf, tree[x].suf);
		tree[rs].min = min(tree[rs].min, tree[x].suf);
		tree[ls].suf = min(tree[ls].suf, tree[rs].min);
		tree[ls].min = min(tree[ls].min, tree[rs].min);
		tree[x].suf = 0x7fffffff;
	}
}

void chksuf(int x, int l, int r, int &suf){
	if (l <= tree[x].l && tree[x].r <= r){
		tree[x].suf = min(tree[x].suf, suf);
		tree[x].min = suf = min(tree[x].min, suf);
		return;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	pushdown(x);
	if (r > mid) chksuf(x * 2 + 1, l, r, suf);
	if (l <= mid) chksuf(x * 2, l, r, suf);
	update(x);
}

void inc(int x, int l, int r){
	if (l <= tree[x].l && tree[x].r <= r){
		tree[x].add++;
		if (tree[x].pre != 0x7fffffff) tree[x].pre++;
		if (tree[x].suf != 0x7fffffff) tree[x].suf++;
		tree[x].min++;
		return;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	pushdown(x);
	if (l <= mid) inc(x * 2, l, r);
	if (r > mid) inc(x * 2 + 1, l, r);
	update(x);
}

void chkpre(int x, int l, int r, int &pre){
	if (l <= tree[x].l && tree[x].r <= r){
		tree[x].pre = min(tree[x].pre, pre);
		tree[x].min = pre = min(tree[x].min, pre);
		return;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	pushdown(x);
	if (l <= mid) chkpre(x * 2, l, r, pre);
	if (r > mid) chkpre(x * 2 + 1, l, r, pre);
	update(x);
}

int get_min(int x, int l, int r){
	if (l <= tree[x].l && tree[x].r <= r) return tree[x].min;
	int mid = (tree[x].l + tree[x].r) >> 1, ans = 0x7fffffff;
	pushdown(x);
	if (l <= mid) ans = get_min(x * 2, l, r);
	if (r > mid) ans = min(ans, get_min(x * 2 + 1, l, r));
	return ans;
}

int main(){
	int l = read(), r = read(), n = read(), m = 0, k = 0;
	for (register int i = 1; i <= n; i++){
		x1[i] = read();
		y1[i] = read();
		x2[i] = read();
		y2[i] = read();
		if (x1[i] > x2[i]){
			swap(x1[i], x2[i]);
			swap(y1[i], y2[i]);
		}
		a[++m] = Node1(i, 1);
		a[++m] = Node1(i, -1);
	}
	sort(a + 1, a + m + 1);
	for (register int i = 1; i <= m; i++){
		set<int, Compare>::iterator it;
		if (a[i].type == 1){
			it = s.upper_bound(a[i].id);
			if (it != s.end()){
				deg[*it]++;
				add_edge(a[i].id, *it);
			}
			if (it != s.begin()){
				it--;
				deg[a[i].id]++;
				add_edge(*it, a[i].id);
			}
			s.insert(a[i].id);
		} else {
			s.erase(a[i].id);
			it = s.upper_bound(a[i].id);
			if (it != s.end()){
				deg[*it]++;
				add_edge(a[i].id, *it);
			}
			if (it != s.begin()){
				it--;
				deg[a[i].id]++;
				add_edge(*it, a[i].id);
			}
		}
	}
	for (register int i = 1; i <= n; i++){
		if (deg[i] == 0) q.push(i);
	}
	for (register int i = 1; !q.empty(); i++){
		int cur = q.front();
		q.pop();
		order[i] = cur;
		for (register int j = head[cur]; j != 0; j = edge[j].nxt){
			int x = edge[j].end;
			if (--deg[x] == 0) q.push(x);
		}
	}
	l *= 2;
	bucket[++k] = l;
	bucket[++k] = l + 1;
	r *= 2;
	bucket[++k] = r;
	bucket[++k] = r - 1;
	for (register int i = 1; i <= n; i++){
		x1[i] *= 2;
		bucket[++k] = x1[i];
		bucket[++k] = x1[i] - 1;
		bucket[++k] = x1[i] + 1;
		x2[i] *= 2;
		bucket[++k] = x2[i];
		bucket[++k] = x2[i] - 1;
		bucket[++k] = x2[i] + 1;
	}
	sort(bucket + 1, bucket + k + 1);
	k = unique(bucket + 1, bucket + k + 1) - bucket - 1;
	l = lower_bound(bucket + 1, bucket + k + 1, l) - bucket;
	r = lower_bound(bucket + 1, bucket + k + 1, r) - bucket;
	for (register int i = 1; i <= n; i++){
		x1[i] = lower_bound(bucket + 1, bucket + k + 1, x1[i]) - bucket;
		x2[i] = lower_bound(bucket + 1, bucket + k + 1, x2[i]) - bucket;
	}
	build(1, 1, k, l, r);
	for (register int i = 1; i <= n; i++){
		if (y1[order[i]] < y2[order[i]]){
			int suf = 0x7fffffff;
			chksuf(1, x1[order[i]], x2[order[i]], suf);
			inc(1, x1[order[i]] + 1, x2[order[i]]);
		} else {
			int pre = 0x7fffffff;
			chkpre(1, x1[order[i]], x2[order[i]], pre);
			inc(1, x1[order[i]], x2[order[i]] - 1);
		}
	}
	cout << get_min(1, l, r);
	return 0;
}
```

---

