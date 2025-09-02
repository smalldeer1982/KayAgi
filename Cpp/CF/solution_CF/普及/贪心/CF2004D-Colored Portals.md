# Colored Portals

## 题目描述

一条直线上有 $n$ 个城市，这些城市的编号为 $1$ 到 $n$。

传送门被用于在城市间移动，传送门有四种颜色：蓝色，绿色，红色和黄色。每一个城市都有两种颜色的传送门。你可以从城市 $i$ 到城市 $j$，当且仅当这两个城市存在同色的传送门（例如，你可以从有红色和蓝色的传送门的城市到有蓝色和绿色传送门的城市），花费 $|i - j|$ 个硬币。

你的任务是回答 $q$ 个询问：计算城市 $x$ 到城市 $y$ 的最小花费。

## 样例 #1

### 输入

```
2
4 5
BR BR GY GR
1 2
3 1
4 4
1 4
4 2
2 1
BG RY
1 2```

### 输出

```
1
4
0
3
2
-1```

# 题解

## 作者：copper_ingot (赞：3)

[洛谷](https://www.luogu.com.cn/problem/CF2004D)、[CF](https://codeforces.com/problemset/problem/2004/D) 题目传送门

[可能更好的阅读体验](https://www.luogu.com.cn/article/7rxduayb)

首先，我们把每个城市拥有的传送门转换成一个数字，方便后面处理。

对于两个城市 $u$ 和 $v$，如果他们至少有一对相同的传送门，那么他们显然可以互相到达。

否则，就要尽量找到一个城市 $w$，使得 $u$ 和 $w$、$v$ 和 $w$ 分别可以互相到达，且 $u$ 到 $w$ 与 $v$ 到 $w$ 的距离和最小。

我们可以搞两个数组 $pre$ 和 $suf$，分别表示城市 $i$ 左边和右边最近的与 $i$ **刚好有一对相同的传送门**的城市编号。

如果要求 $pre$，只需要用一个 $tmp$ 数组实时记录，$tmp_i$ 表示目前最靠右的传送门类型为 $i$ 的城市编号。求 $suf$ 和这个差不多，具体思路留给读者，实在不会就去看代码吧。

如果 $u$ 和 $v$ 的传送门完全不同，那么如果 $suf_u$ 在 $u,v$ 之间，$w$ 就是 $suf_u$，输出 $v - u$ 即可。

否则比较 $pre_u$ 和 $suf_v$ 哪个方案更优，并输出答案。

记得判无解情况。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
const int inf = 0x7f7f7f7f;
int t, n, q, a[200001], pre[200001], suf[200001], tmp[7];
int get(char b, char c){//转换函数，u和v可以直接到达<=>a[u]+a[v]!=7
	if (b == 'B' && c == 'G') return 1;
	else if (b == 'B' && c == 'R') return 2;
	else if (b == 'B' && c == 'Y') return 3;
	else if (b == 'G' && c == 'R') return 4;
	else if (b == 'G' && c == 'Y') return 5;
	else return 6;
}
int main(){
	scanf("%d", &t);
	while (t--){
		scanf("%d%d", &n, &q);
		for (int i = 1; i <= n; i++){
			string s; cin >> s;
			char b = s[0], c = s[1];
			a[i] = get(b, c);
		}
		for (int i = 1; i <= n; i++) pre[i] = 0, suf[i] = inf;//多测清空，这个别用memset
		memset(tmp, 0, sizeof(tmp));//但是这个可以用
		for (int i = 1; i <= n; i++){//求pre
			for (int j = 1; j <= 6; j++){
				if (a[i] != j && a[i] + j != 7) pre[i] = max(pre[i], tmp[j]);
			}
			tmp[a[i]] = max(tmp[a[i]], i);//实时记录
		}
		memset(tmp, 0x7f, sizeof(tmp));
		for (int i = n; i >= 1; i--){//同上，求suf
			for (int j = 1; j <= 6; j++){
				if (a[i] != j && a[i] + j != 7) suf[i] = min(suf[i], tmp[j]);
			}
			tmp[a[i]] = min(tmp[a[i]], i);
		}
		while (q--){
			int u, v; scanf("%d%d", &u, &v);
			if (u > v) swap(u, v);
			if (a[u] + a[v] != 7) printf("%d\n", v - u);//uv可以直达
			else if (pre[v] > u && suf[u] < v) printf("%d\n", v - u);//w在uv之间
			else if (pre[u] != 0 || suf[v] != inf){//w在uv外且有解
				if (pre[u] == 0) printf("%d\n", suf[v] * 2 - u - v);
				else if (suf[v] == inf) printf("%d\n", u + v - pre[u] * 2);
				else printf("%d\n", min(suf[v] * 2 - u - v, u + v - pre[u] * 2));
			}
			else puts("-1");//记得无解
		}
	}
	return 0;
} 
```

---

## 作者：初星逝者 (赞：1)

更好的阅读体验 : [Blog](https://www.luogu.com.cn/article/fe95tfmi)

> 定义 $s$ 和 $t$ 分别是两个城市含有的颜色，且 $s$ 和 $t$ 的字符集之间没有交集，我们称 $s$ 是 $t$ 的反串。

观察题目，首先发现一个性质，如果询问的两个城市 $s$ 和 $t$ 不是互为反串，那么最短路就是它们之间的距离。

反之，如果 $s$ 和 $t$ 互为反串，那么必须有一个中转点在两个城市的路径上。那么寻找答案的关键在于如何去寻找中转点。

我们可以发现如果一个 $s'$ 与 $s$ 不构成反串且 $s'$ 不等于 $s$，那么这个点就可以作为一个中转点。因为 $s$ 和 $t$ 占满了字符集，所以 $s'$ 当且仅当出现 $s$ 中的一个字符即为一个合法的中转点。

接下来我们把每个点左边的最近中转点和右边的最近中转点处理一下，询问就可以做到 $\mathcal{O}(1)$ 了。

代码:


```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long 
int t;
int n,q;
string s[200005];
int a[200005],b[200005];
map<string,int> mp;

inline string rs(string s){
	if(s=="BG")return "RY";
	if(s=="BR")return "GY";
	if(s=="GR")return "BY";
	if(s=="RY")return "BG";
	if(s=="GY")return "BR";
	if(s=="BY")return "GR";
}
vector<string> v;

signed main(){
	v.push_back("BG");
	v.push_back("BR");
	v.push_back("GR");
	v.push_back("GY");
	v.push_back("RY");
	v.push_back("BY");
	cin >> t;
	while(t--){
		cin >> n >> q;
		for(int i=1;i<=n;i++){
			a[i]=0;
			b[i]=1000000;
			cin >> s[i];
		}
		mp.clear();
		for(int i=1;i<=n;i++){
			for(auto y:v)if(y!=rs(s[i])&&s[i]!=y)a[i]=max(mp[y],a[i]);
			mp[s[i]]=i;
		}
		mp.clear();
		for(int i=n;i>=1;i--){
			for(auto y:v)if(y!=rs(s[i])&&s[i]!=y)b[i]=min(mp[y]==0?1000000:mp[y],b[i]);
			mp[s[i]]=i;
		}
		while(q--){
			int l,r;
			cin >> l >> r;
			if(l>r)swap(l,r);
			if(s[r]!=rs(s[l])){
				cout<<r-l<<endl;
			}
			else{
				int ans=100000000;
				if(a[l]!=0)ans=min(r-a[l]+l-a[l],ans);
				if(b[r]!=1000000)ans=min(b[r]-l+b[r]-r,ans);
				if(a[r]!=0){
					if(a[r]>=l)ans=min(r-l,ans);
					if(a[r]<=l)ans=min(r-a[r]+l-a[r],ans);
				}
				if(b[l]!=1000000){
					if(b[l]<=r)ans=min(r-l,ans);
					if(b[l]>=r)ans=min(b[l]-r+b[l]-l,ans);
				}
				if(ans==100000000)cout<<-1<<endl;
				else cout<<ans<<endl;
			}
		}
	}
	return 0;
} 
```

---

## 作者：封禁用户 (赞：1)

~~之前的tj炸时了，重发求过~~
## 构图
首先，根据输入的每个城市拥有的传送门颜色信息，将有同色传送门的城市之间建立连接，这里可以用邻接表的方式来表示图，每个城市对应一个列表，列表中存放与之有同色传送门相连的其他城市以及到达这些城市的边权。
## 处理询问
用 BFS 来在构建好的图中寻找从 $x$ 到 $y$ 的最短路径长度（即最小花费）。从起始城市 $x$ 开始，使用队列来存储待探索的节点以及到达该节点的当前累计花费，不断向外扩展搜索，直到找到目标城市 $y$ 或者队列为空（表示无法到达目标城市）。 

---
~~然后你就会发现炸时了~~
## 优化
1. 对传送门颜色进行预处理，使用合适的数据结构来记录每种颜色对应的城市列表，这样在构建图时，只需要遍历这些列表来添加边，而不是两两比较所有城市，从而降低构建图的时间复杂度。
2. 用 `unordered_set` 来记录节点是否被访问过，访问直接降（平均）$O(1)$。
3. 如果题目中的图满足一些特定条件（比如边权非负且相对稀疏等情况），可以考虑使用 Dijkstra 算法或者 A* 算法等更高效的单源最短路径算法来替代 BFS。这些算法在处理这类带权重的图求最短路径问题上，在平均情况下或者特定图结构下可能会有更好的时间复杂度。
---
有钩子的第一篇 tj，求过求赞qwq

---

## 作者：postpone (赞：0)

从题意得知，如果两个城市有共同的颜色，那么直接到就行，所以我们需要想怎么处理两个城市颜色没有交集的情况。

对于一个城市，不妨把和它颜色不*完全相同*，但有交集的城市称为这座城市的“中转站”。若预处理出所有城市往左和往右最近的中转站，那么就能 $O(1)$ 处理颜色无交集的两座城市的距离了。

其实此题思路比较好想，但实现起来并不简单。先用最朴素的想法，对于每个城市，都往左往右遍历找，这样的话复杂度是不能接受的。再想一想，如果我们分开处理呢？从前到后遍历一遍，找每个城市往左最近的“中转站”；从后到前遍历一遍，找往右最近，这样就行了。

代码如下，这里用 `map` 存颜色到城市的映射，代码量较大，但可读性还是比较好的。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

enum ColorCompare {
    same,
    diff,
    part,
};

ColorCompare check(const string &L, const string &R) {
    if (L == R) {
        return same;
    }
    for (auto i : L) {
        if (R.find(i) != string::npos) {
            return part;
        }
    }
    return diff;
}

map<string, int> f;
vector<string> g;

void solve() {
    int n, q;
    cin >> n >> q;

    vector<string> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    vector<int> L(n, -1e8), R(n, 1e8);
    for (int i = 0; i < n; i++) {
        for (auto color : g) {
            if (check(color, c[i]) == part and f.contains(color)) {
                L[i] = max(L[i], f[color]);
            }
        }
        f[c[i]] = i;
    }
    f.clear();
    for (int i = n - 1; ~i; i--) {
        for (auto color : g) {
            if (check(color, c[i]) == part and f.contains(color)) {
                R[i] = min(R[i], f[color]);
            }
        }
        f[c[i]] = i;
    }
    f.clear();

    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        if (r < l) {
            swap(l, r);
        }

        if (check(c[l], c[r]) != diff) {
            cout << r - l << "\n";
        } else if (L[l] != -1e8 or R[l] != 1e8) {
            cout << min({l - L[l] + r - L[l],
                         R[l] - l + std::abs(r - R[l]),
                         R[r] - r + R[r] - l,
                         r - L[r] + std::abs(L[r] - l)}) << "\n";
        } else {
            cout << -1 << "\n";
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    g = {"BG", "BR", "BY", "GR", "GY", "RY"};

    int T;
    for (cin >> T; T--;) {
        solve();
    }

    return 0;
}
```
[提交记录](https://codeforces.com/contest/2004/submission/281077012)

---

## 作者：GY程袁浩 (赞：0)

### 思路

我们研究颜色，发现最多只有四个不同的颜色，于是跳转时，我们的路程中只要有之前出现过的颜色（除入点），那么就可以省去入点，直接从之前出现过那个颜色的地方跳过来。于是我们得出了一个结论，路程中最多只会经过 $4$ 个颜色。

考虑起始点 $x$ 与终点 $y$，首先如果它们颜色有重合，那么一定可以直接跳，这样绝对是最短路。考虑它们颜色互不相同，如果想从 $x$ 到 $y$ 点，一定需要有一个点，既有 $x$ 上的一个颜色，也有 $y$ 上的一个颜色。所以考虑枚举 $x$ 上的颜色与 $y$ 上的颜色。**这个点可以直接到 $x$ 与 $y$**，这样颜色的点可能有很多个对吧，所以考虑找出一个点两个颜色固定，使它到 $x$ 的距离加上它到 $y$ 的距离最小。

首先考虑它与 $y$ 点在 $x$ 的同一边，如果我们选 $x$ 与 $y$ 之间的点，那么再到 $y$ 的距离都是一样的对吧，都是 $x$ 到 $y$ 的曼哈顿距离，考虑在 $y$ 之后了，那么还要加上到 $y$ 的两倍距离，这时离 $y$ 最近的点就更优对吧（同时也最靠近 $x$，因为所选点在 $y$ 之后，$x$ 与 $y$ 在选点的同一边）。

如果有 $x$ 与 $y$ 之间的点，那么一定选那些点，优于 $y$ 之后的点。所以考虑选 $y$ 那边的点，只需要选择离 $x$ 近的即可。

考虑 $y$ 对边的点，同样的，离 $x$ 越远意味着离 $y$ 越远（同上，所选点在 $x$ 与 $y$ 的同一边），所以考虑选离 $x$ 最近的点。

所以最后选离 $x$ 最近的与 $y$ 同边与对边的点，即 $x$ 点最近的左右边点，取路程最少的，预处理即可。

### Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
string ver[]={"BG","BR","BY","GR","GY","RY"};
int las[N][6],nex[N][6],a[N],n,q;
string putin[N];
signed main() {
	int tt;cin>>tt;
	while(tt--) {
		cin>>n>>q;
		for(int i=1;i<=n;i++) {
			cin>>putin[i];
			a[i]=find(ver,ver+6,putin[i])-ver;
		}
		for(int i=0;i<=n;i++)
          for(int j=0;j<6;j++) las[i][j]=-0x3f3f3f3f3f3f3f3f;
		for(int i=1;i<=n;i++) {
			for(int j=0;j<6;j++) las[i][j]=las[i-1][j];
			las[i][a[i]]=i;
		}
      	for(int i=1;i<=n+1;i++)
          for(int j=0;j<6;j++) nex[i][j]=0x3f3f3f3f3f3f3f3f;
		for(int i=n;i>=1;i--) {
			for(int j=0;j<6;j++) nex[i][j]=nex[i+1][j];
			nex[i][a[i]]=i;
		}
		while(q--) {
			int x,y;cin>>x>>y;
			bool flag=0;
			for(int i=0;i<2;i++)
				for(int j=0;j<2;j++)
					if(putin[x][i]==putin[y][j]) {
						flag=1;
						goto ok;
					}
			ok:
			if(flag) {
				cout<<abs(y-x)<<endl;
				continue;
			}
			int minn=1e9;
			for(int i=0;i<2;i++)
				for(int j=0;j<2;j++) {
					char xx=putin[x][i],yy=putin[y][j];
					if(xx>yy) swap(xx,yy);
					string s;s+=xx;s+=yy;
					int value=find(ver,ver+6,s)-ver;
					minn=min(minn,abs(x-las[x][value])+abs(y-las[x][value]));
					minn=min(minn,abs(x-nex[x][value])+abs(y-nex[x][value]));
				}
			cout<<(minn==(int)1000000000?-1:minn)<<endl;
		}
	}
	return 0;
} 
```

---

## 作者：Redamancy_Lydic (赞：0)

## 背景

`memset` 害死人。

## 分析

首先注意到字母种类只有四个，那么很显然任意两个城市至多只需要一个城市中转就能互相到达。

~~然后不就可以乱写了么。~~

先把可以直接到达的判断掉，设当前两个城市为 $x$ 和 $y$，我们对 $6$ 种字母组合分别存一下出现的位置，然后对 $x$ 的两个字母分别去找到对应的字母组合，并在相应的数组里面二分找到第一个比 $x$ 靠后的位置，最后计算即可。

需要注意的是，如果当前字母组合在 $x$ 之后一次也没有出现过，我们就需要找到在 $x$ 前面位置的再计算。

但是因为 $x$ 可能从未出现过，这时候我们可以先对每一个数组先存上一个极小值防止卡死。

然后就做完了。

## Code

[提交记录](https://codeforces.com/contest/2004/submission/276665473)

---

