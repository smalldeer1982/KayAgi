# Closing ceremony

## 题目描述

The closing ceremony of Squanch Code Cup is held in the big hall with $ n×m $ seats, arranged in $ n $ rows, $ m $ seats in a row. Each seat has two coordinates $ (x,y) $ ( $ 1<=x<=n $ , $ 1<=y<=m $ ).

There are two queues of people waiting to enter the hall: $ k $ people are standing at $ (0,0) $ and $ n·m-k $ people are standing at $ (0,m+1) $ . Each person should have a ticket for a specific seat. If person $ p $ at $ (x,y) $ has ticket for seat $ (x_{p},y_{p}) $ then he should walk $ |x-x_{p}|+|y-y_{p}| $ to get to his seat.

Each person has a stamina — the maximum distance, that the person agrees to walk. You should find out if this is possible to distribute all $ n·m $ tickets in such a way that each person has enough stamina to get to their seat.

## 样例 #1

### 输入

```
2 2
3 3 3 2
1 3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2 2
3 2 3 3
1 2
```

### 输出

```
NO
```

# 题解

## 作者：iodwad (赞：5)

对于在 $(0,0)$ 的点，有一个显而易见的贪心决策：将人按耐力值升序排列，然后每个人随便选一个能到达的到 $(m+1,0)$ 距离最大的点就行了，因为一个人能到达的点后面的点都能到达。然后将剩下的点按到 $(m+1,0)$ 的距离排序，与剩下 $nm-k$ 个在 $(m+1,0)$ 的耐力值直接比较就行了。对于找到达 $(m+1,0)$ 距离最大且能到达点，可以用线段树来维护。总复杂度为 $\mathcal O(n\cdot \log n)$。

~~不要吐槽两格缩进~~

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAXN = 10000;

int n, m, k, tot;
int a[MAXN | 1], b[MAXN | 1];
std::pair < int, int > p[MAXN | 1];

inline int read() {
  register int x = 0;
  register char ch = getchar();
  while (!isdigit(ch)) ch = getchar();
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x;
}

namespace SegmentTree {
  struct Node {
    int maxv, posv;
    Node *ch[2];
    Node() : maxv(-1), posv(0) {
      ch[0] = ch[1] = NULL;
    }
  } *root;
  inline void pushup(Node *o) {
    if (o -> ch[0] -> maxv > o -> ch[1] -> maxv) {
      o -> maxv = o -> ch[0] -> maxv;
      o -> posv = o -> ch[0] -> posv;
    } else {
      o -> maxv = o -> ch[1] -> maxv;
      o -> posv = o -> ch[1] -> posv;
    }
  }
  void build(Node *&o, int l, int r) {
    o = new Node;
    if (l == r) {
      o -> maxv = p[l].second;
      o -> posv = l;
      return;
    }
    int mid = (l + r) >> 1;
    build(o -> ch[0], l, mid);
    build(o -> ch[1], mid + 1, r);
    pushup(o);
  }
  std::pair < int, int >  query(Node *o, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return std::make_pair(o -> maxv, o -> posv);
    int mid = (l + r) >> 1;
    std::pair < int, int> res = std::make_pair(-1, 0);
    if (ql <= mid) res = query(o -> ch[0], l, mid, ql, qr);
    if (mid < qr) {
      std::pair < int, int > ress = query(o -> ch[1], mid + 1, r, ql, qr);
      if (ress > res) res = ress;
    }
    return res;
  }
  void modify(Node *o, int l, int r, int pos, int val) {
    if (l == r) {
      o -> maxv = val;
      o -> posv = pos;
      return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) modify(o -> ch[0], l, mid, pos, val);
    else modify(o -> ch[1], mid + 1, r, pos, val);
    pushup(o);
  }
}

using namespace SegmentTree;

inline int find(int x) {
  int l = 1, r = tot, res = 0;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (p[mid].first <= x) {
      l = mid + 1;
      res = mid;
    } else r = mid - 1;
  }
  return res;
}

int main() {
  n = read();
  m = read();
  k = read();
  for (int i = 1; i <= k; ++i) a[i] = read();
  read();
  for (int i = 1; i <= n * m - k; ++i) b[i] = read();
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {  
      p[++tot] = std::make_pair(i + j, m + 1 - j + i);
    }
  }
  std::sort(p + 1, p + 1 + tot);
  build(root, 1, tot);
  std::sort(a + 1, a + 1 + k);
  std::sort(b + 1, b + 1 + n * m - k);
  for (int i = 1; i <= k; ++i) {
    int l = find(a[i]);
    if (l == 0) {
      puts("NO");
      return 0;
    }
    std::pair < int, int > res = query(root, 1, tot, 1, l);
    if (res.first == -1) {
      puts("NO");
      return 0;
    }
    modify(root, 1, tot, res.second, -1);
  }
  int cnt = 0;
  for (int i = 1; i <= tot; ++i) {
    if (query(root, 1, tot, i, i).first != -1) {
      a[++cnt] = query(root, 1, tot, i, i).first;
    }
  }
  std::sort(a + 1, a + 1 + cnt);
  for (int i = 1; i <= n * m - k; ++i) {
    if (a[i] > b[i]) {
      puts("NO");
      return 0;
    }
  }
  puts("YES");
  return 0;
}
```



---

## 作者：hjqhs (赞：2)

贪心好题。  
因为是从左上角和右上角进的，所以左下角和右下角是最远的，限制最大的。先将耐力值排序，每次贪心可以抵达左下角和右下角的最小的耐力值并把这个人从人群中抹去（使用 `lower_bound`）。如果找不到则输出 `NO`。
```cpp
#include<bits/stdc++.h>
// #define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define fv(i,p) for(int i=0;i<p.size();++i)
#define all(x) x.begin(),x.end()
#define ptc putchar
#define il inline
#define reg register
// #define push_back pb
// #define mp make_pair
// #define eb emplace_back
// #define ret; return 0;
using namespace std;
const int N=100005;
const int MOD=998244353;
const int INF=0x3f3f3f3f;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
int Max(int a,int b){return a>b?a:b;}
int MAx(int a,int b,int c){return Max(a,Max(b,c));}
int MAX(int a,int b,int c,int d){return Max(Max(a,b),Max(c,d));}
int Min(int a,int b){return a<b?a:b;}
int MIn(int a,int b,int c){return Min(a,Min(b,c));}
int MIN(int a,int b,int c,int d){return Min(Min(a,b),Min(c,d));}
void Swap(int&a,int&b){int tmp=a;a=b;b=tmp;}
void cmin(int&x,int y){if(x>y)x=y;}
void cmax(int&x,int y){if(x<y)x=y;}
int read(){
  int x=0,f=1;
  char ch=getchar();
  while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
  while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
  return x*f;
}
int T=1;
int n,m,k,x;
vector<int>a,b;
void solve(){
  cin>>n>>m>>k;
  rep(i,1,k){cin>>x,a.emplace_back(x);}
  cin>>x;rep(i,1,n*m-k){cin>>x;b.emplace_back(x);}
  sort(all(a)),sort(all(b));
  per(i,n,1)rep(j,1,m){
    vector<int>::iterator p,q;
    p=lower_bound(all(a),i+j);
    q=lower_bound(all(b),i+m+1-j);
    if(p!=a.end())a.erase(p);
    else if(q!=b.end())b.erase(q);
    else{cout<<"NO"<<'\n';return;}
  }
  cout<<"YES"<<'\n';
}
signed main(){
  // freopen(,,stdin);
  // freopen(,,stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  // cin>>T;
  while(T--)solve();
  return 0;
}
```

---

## 作者：幻影星坚强 (赞：2)

~~从前有个人，他n和m写反了，然后过了样例，WA了考试的所有点~~

我们考虑左边的人，他肯定尽量占对于右边的人距离远的点，然后按照焦虑度从小到大查询左边的人，能保证所有前面的人能到的点后面的人也能到。然后我们就能保证左边的人如果有解则肯定使得对于右边的人距离近的点最多，此时判断是否有解即可。

加个vector来处理右边点的各个距离所占的点对于左边的距离就可以到$O(n * m)$（大概吧），这样甚至能多测或者调大点范围什么的

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, t;
int l[10010], r[10010];
int now[10010];
vector<int> v[10010];
int b[10010];
int main()
{
t = 1;
	while(t --)
	{
		memset(l, 0, sizeof(l));
		memset(r, 0, sizeof(r));
		memset(now, 0, sizeof(now));
		memset(b, 0, sizeof(b));
		for (int i = 1; i <= n + m; ++ i)
		{
			v[i].clear();
		}
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; ++ i)
		{
			for (int j = 1; j <= m; ++ j)
			{
				v[i + m - j + 1].push_back(i + j);
				++ b[i + m - j + 1];
			}
		}
		int x, y;
		scanf("%d", &x);
		for (int i = 1; i <= x; ++ i)
		scanf("%d", &l[i]);
		scanf("%d", &y);
		for (int i = 1; i <= y; ++ i)
		scanf("%d", &r[i]);
		sort(l + 1, l + 1 + x);
		sort(r + 1, r + 1 + y);
		int sf = 0;
		for (int i = 1; i <= x; ++ i)
		{
			int maxs = 0;
			for (int j = 1; j <= n + m; ++ j)
			{
				if(now[j] < v[j].size() && v[j][now[j]] <= l[i])maxs = j;
			}
			if(maxs == 0)
			{
				sf = 1;
				printf("NO\n");
				break;
			}
			-- b[maxs];
			++ now[maxs];
		}
		if(sf == 1)continue;
		for (int i = 1; i <= y; ++ i)
		{
			int maxs = 0;
			for (int j = 1; j <= r[i]; ++ j)
			{
				if(b[j] > 0) maxs = j;
			}
			
			if(maxs == 0)
			{
				sf = 1;
				printf("NO\n");
				break;
			}
			-- b[maxs];
		}
		if(sf == 1)continue;
		printf("YES\n");
	}
	return 0;
}
```


---

## 作者：20111019Yu (赞：2)

### 思路

很容易想到一个贪心：把人按耐力值排序，每个人放在最靠近门的位置。

但这个贪心是错误的，有可能从前门进的太多，把后门的位置占掉了。

所以我们换一个思路，放前门的人在什么位置时对后门的人影响最小?

所以贪心思路就出来了，把前门的人放在耐力值以内且距后门最远的座位，每个人每次把所有符合要求的座位都扫一次。

##### 友情提示：不要吝啬你的循环和数组。

### code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, k1, k2, a[10005], cnt[100005], sum[100005];
bool vis[10005][10005];\\开大点没问题

signed main(){
	cin >> n >> m >> k1;
	for( int i = 1; i <= k1; i++ ) cin >> a[i];
	sort(a + 1, a + k1 + 1);
	for( int i = 1; i <= k1; i++ ){
		int x = 0, y = m + 1;
		for( int j = 1; j <= min(n, a[i]); j++ ){
			for( int k = 1; k + j <= a[i] && k <= m; k++ ){
				if(vis[j][k]) continue;
				if(x - y < j - k || (x - y == j - k && x + y < j + k)){
					x = j;
					y = k;
				}\\计算最优位置
			}
		}
		if(!x){
			cout << "NO" << endl;
			return 0;
		}
		vis[x][y] = 1;
	}\\循环多写点没问题
	cin >> k2;
	for( int i = 1; i <= k2; i++ ){
		cin >> a[i];
		cnt[a[i]]++;
	}
	for( int i = 2; i <= n + m; i++ ) cnt[i] += cnt[i - 1];\\用前缀和小小的优化了一下
	for( int i = 1; i <= n; i++ ){
		for( int j = 1; j <= m; j++ ){
			if(!vis[i][j]) sum[i + m + 1 - j]++;
		}
	}
	for( int i = 2; i <= n + m; i++ ) sum[i] += sum[i - 1];\\前缀和优化
	for( int i = 0; i <= n + m; i++ ){
		if(sum[i] < cnt[i]){
			cout << "NO" << endl;
			return 0;
		}
	}
	cout << "YES" << endl;
	return 0;
}
```

---

## 作者：Seanq (赞：2)

**CF720A Closing ceremony题解**  
~~这是一道水题，我这个大菜鸡都过了~~  
一句话题意：  
n×m个座位有n×m个人，一开始有 k人在(0,0)点上，l个人在(0,m+1)点上，每个人有对应的体力值，体力值即为可以行走的距离（曼哈顿距离），问是否存在一种方案是每个人花费的体力不超过上限，且每个人都有位置坐。 

------------

先排序：从小到大。  
前K人:离（0，m+1）点越远越好，若路程相同则选择离起点越远越好  
后L人：离起点越远越好。  
若可行区间内节点都已选择，输出“NO”。  
否则输出“YES”。  
时间复杂度：O(n^2*m^2)  
可以通过此题  *  

std:  

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,m;
int q,l;
int a[10005],b[10005];//两个人的队列
bool cmp(int x,int y)//排序用
{
    return x<y;//从小到大
}
bool used[10005][10005];//存储已用节点
bool can_do()//判断可不可行
{
    for(int i=1;i<=l;i++)
    {
        int ans=-1,cx,cy,hans=-1;//最小距离，选取点坐标，另一个最小距离
        for(int j=1;j<=n;j++)
        {
            for(int k=1;k<=m;k++)
            {
                if(used[j][k]==1)//已用，返回
                {
                    continue;
                }
                else if((j+k)>a[i])//到不了，返回
                    continue;
                else
                {
                    if((j+m-k)>ans)
                    {
                        ans=j+m-k;
                        cx=j;
                        cy=k;
                    }
                    else if((j+m-k)==ans&&(j+k)>hans)//选取最优值
                    {
                        ans=j+m-k;
                        cx=j;
                        cy=k;
                    }
                }
            }
        }
        if(ans==-1) //若无可选点，返回
        {
            return 0;
        }
        used[cx][cy]=1;//标记已用点
    }
    for(int i=1;i<=q;i++)
    {
        int ans=-1,cx,cy;
        for(int j=1;j<=n;j++)
        {
            for(int k=1;k<=m;k++)
            {
                if(used[j][k]==1)//若以用，返回
                {
                    continue;
                }
                else if((j+m-k+1)>b[i])//若到不了，返回
                    continue;
                else//更新最好值
                {
                    if((j+m-k)>ans)
                    {
                        ans=j+m-k;
                        cx=j;
                        cy=k;
                    }
                }
            }
        }
        if(ans==-1) 
        {
            return 0;//无可使用的点
        }
        used[cx][cy]=1;//标记已用点
    }
    return 1;//返回可行
}
int main()
{
    scanf("%d%d",&n,&m);//输入
    scanf("%d",&l);
    for(int i=1;i<=l;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+l+1,cmp);//排序
    scanf("%d",&q);
    for(int i=1;i<=q;i++)
        scanf("%d",&b[i]);//排序
    sort(b+1,b+q+1,cmp);
    memset(used,0,sizeof(used));//清空数组
    if(can_do()==1)printf("YES\n");//若可行：输出YES
    else printf("NO\n");//否则输出NO
    return 0;//结束啦！
} 
```

------------

（此题共110个数据点，你是不可能用随机数过的）

---

## 作者：RainFestival (赞：1)

难度：$2000$

我们对于左上角进入的点，按照焦虑度排序，枚举。

如果现在某人焦虑度为 $k$，则所有离左上角的距离 $\le k$ 的点，都可以给 Ta 坐，**并且这些座位对于以后的左上角进入的人都是一样的**。简单地说，这些剩下的座位都可以被后面的左上角进入的人坐。

因为这些点离左上角的距离都 $\le k$，而以后的左上角进入的人的忍耐度都 $\ge k$。

所以我们要先坐离右上角最远的座位，这样比坐离右上角更近的座位更划算。

最后右上角也这么考虑，只是不用考虑左上角了。

于是我们可以用一个 priority_queue 维护。

代码如下：

```cpp
#include<cstdio>
#include<vector>
#include<bitset>
#include<cstdlib>
#include<utility>
#include<queue>
#include<cmath>
std::vector< std::pair<int,int> > s1[10005],s2[10005];
int t,n,m,p1,p2,f[20005],g[20005];
std::bitset<10005> used[10005];
int dist(int x1,int y1,int x2,int y2){return abs(x1-x2)+abs(y1-y2);}
void clear()
{
	int lim=n+m;
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) used[i][j]=0;
	for (int i=1;i<=lim;i++) f[i]=g[i]=0,s1[i].clear(),s2[i].clear();
	n=m=p1=p2=0;
}
int main()
{
//	freopen("cinema.in","r",stdin);
//	freopen("cinema.out","w",stdout);
//	scanf("%d",&t);
    t=1;
	while (t--)
	{
		std::priority_queue< std::pair< int,std::pair<int,int> > > pq;
		std::queue< std::pair<int,int> > q;
		int flag=0;
		std::scanf("%d%d",&n,&m);
		int lim=n+m;
		scanf("%d",&p1);
		for (int i=1;i<=p1;i++)
		{
			int x;
			scanf("%d",&x);
			if (x>lim) x=lim;
			++f[x];
		}
		scanf("%d",&p2);
		for (int i=1;i<=p2;i++)
		{
			int x;
			scanf("%d",&x);
			if (x>lim) x=lim;
			++g[x];
		}
		for (int i=1;i<=n;i++)
		    for (int j=1;j<=m;j++)
		    {
		    	s1[dist(i,j,0,0)].push_back(std::make_pair(i,j));
		    	s2[dist(i,j,0,m+1)].push_back(std::make_pair(i,j));
			}
//		for (int i=1;i<=lim;i++)
//		{
//			printf("%d:",i);
//			for (int j=0;j<s1[i].size();j++) printf("(%d,%d) ",s1[i][j].first,s1[i][j].second);
//			puts("");
//		}
//		for (int i=1;i<=lim;i++)
//		{
//			printf("%d:",i);
//			for (int j=0;j<s2[i].size();j++) printf("(%d,%d) ",s2[i][j].first,s2[i][j].second);
//			puts("");
//		}
		for (int i=1;i<=lim;i++)
		{
			for (int j=0;j<s1[i].size();j++)
			{
				int x=s1[i][j].first,y=s1[i][j].second;
				pq.push(std::make_pair(dist(x,y,0,m+1),std::make_pair(x,y)));
			}
			for (int j=1;j<=f[i];j++)
			{
				if (pq.empty())
				{
					flag=1;
					break;
				}
				int x=pq.top().second.first,y=pq.top().second.second;pq.pop();
				used[x][y]=1;
//				printf("left %d (%d,%d)\n",i,x,y);
			}
			if (flag) break;
		}
//		puts("qwq");
		if (flag)
		{
			puts("NO");
			clear();
			continue;
		}
		for (int i=1;i<=lim;i++)
		{
			for (int j=0;j<s2[i].size();j++)
			{
				int x=s2[i][j].first,y=s2[i][j].second;
				if (used[x][y]) continue;
				q.push(std::make_pair(x,y));
			}
			for (int j=1;j<=g[i];j++)
			{
				if (q.empty())
				{
					flag=1;
					break;
				}
				int x=q.front().first,y=q.front().second;q.pop();
				used[x][y]=1;
//				printf("right %d (%d,%d)\n",i,x,y);
			}
			if (flag) break;
		}
		if (flag)
		{
			puts("NO");
			clear();
			continue;
		}
		puts("YES");
		clear(); 
    }
	return 0;
}
```

qwq


---

## 作者：anonymous_Y (赞：0)

题意很简单不说了。

对于如果只有一个门的时候，不难得出需要将数组从大到小进行排序，然后将他们的位置安排在离门尽可能远的地方，因为此时对后面的人选位置的影响是最小的。

不妨举一个当时我挂掉的例子证明他是错的：


```cpp
1 6
3 7 5 6
2 3 4
```

这时就不难发现距离更远的位置距离后门更近，从而会影响到后门的位置安排。

但是此时题目是两个门，所以我们会发现如果对于前门更远的地方，实际上对于后门更近的，所以这样子对后面的座位安排会产生影响。

那么我们不妨从小到大排序，此时可以发现现在这个人可以到达的位置后面的人都可以到达，但是后面更远的位置这个人就无法到达。

所以我们的贪心的思路就是前门排续过后找到尽可能离后门远的位置，后门的人则是离后门远的位置则更优。

___


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4+10;
int r[maxn],l[maxn];
int n,m,rn,ln;
bool jud[maxn][maxn],tmp;
bool cmp(int a,int b){return a<b;}
int sol1(){
	for(int i=1;i<=ln;i++){
		int ans=-1,cx,cy,hans=-1;
		for(int j=1;j<=n;j++){
			for(int k=1;k<=m;k++){
				if(jud[j][k]==1) continue;
				if(j+k>l[i]) continue;
				//cout<<j<<" "<<m<<" "<<k<<endl; 
				if((j+m-k)>ans){
					ans=j+m-k;
					cx=j,cy=k;
				}
				if((j+m-k)==ans&&(j+k)>hans){
					ans=j+m-k;
					cx=j,cy=k;
					hans=j+k;
				}
			}
		}if(ans==-1) return 0;
		jud[cx][cy]=1;
		
	}
	//cout<<1<<endl;
	for(int i=1;i<=rn;i++){
		int ans=-1,cx,cy;
		for(int k=1;k<=m;k++){
			for(int j=1;j<=n;j++){
				if(jud[j][k]==1) continue;
				if((j+m-k+1)>r[i]) continue;
				//cout<<j<<" "<<m<<" "<<k<<endl; 
				if((j+m-k)>ans){
					ans=j+m-k;
					cx=j,cy=k;
				}
			}
		}
		if(ans==-1) return 0;
		jud[cx][cy]=1;
		
	}
	return 1;
}
int main(){
	cin>>n>>m;
	cin>>ln; 
	for(int i=1;i<=ln;i++){
		cin>>l[i];
		if(l[i]<2){
			cout<<"NO"<<endl;
			return 0;
		}
	}
	cin>>rn;
	for(int i=1;i<=rn;i++){
		cin>>r[i];
		if(r[i]<2){
			cout<<"NO"<<endl;
			return 0;
		}
	}
	sort(l+1,l+1+ln,cmp); sort(r+1,r+1+rn,cmp);
	if(sol1()==0){
		cout<<"NO"<<endl;
		return 0;
	}
	cout<<"YES"<<endl;
	return 0;
}
```

---

## 作者：Leap_Frog (赞：0)

### P.S.
这个叫 leapfrog 的人还是太菜了。  
![](https://cdn.luogu.com.cn/upload/image_hosting/xpvwnjm3.png "总时长 2h")  

### Description.
略

### Solution1.
首先考虑这是一个匹配问题，可以往流那边考虑。  
相当于要求存在一个完美的 点 和 格子 之间的匹配。  
点有两种，一种是左上角，设为 $A$ 集合，一种是右上角，设为 $B$。  
可以考虑霍尔定理。  

相当于我们枚举左部的一个子集，要求右边和它相邻的点大于这个集合的大小。  
首先对于 $A$ 或 $B$ 的点，肯定是耐力越小限制越紧，所以排序后枚举前缀。  
然后此时复杂度已经成为 $O(n^2m^2)$ 了，我们需要算出和右边相邻的点个数。  
这个点数可以 $O(1)$ 算，但是有更加简便的方法。  

可以考虑暴力枚举，就在枚举 $A$ 集合前缀时直接算出有多少个和 $A$ 相邻。  
在每次 $B$ 多一个前缀时算多出来的有多少 **只** 和 $B$ 相邻。  
分析一下总复杂度是 $O(ln^2+lk)=O(n^2m^2)$ 的，稍微卡一下常就过了。  

### Solution2.
同时，考虑换一种思路，考虑对于每个右部图。  
限制最紧的肯定是一个左下角加上一个右下角。  
考虑判断过程，优先判断左下角、右下角。  
所以每次贪心地往左、右塞肯定最优。  
然后就有了一个 $O(nm)$ 的做法。  

就从下往上贪心填，每次能填就填。  
复杂度显然 $O(nm)$，正确性证明了。  

### Coding of Solution1.
```cpp
const int N=100005;int n,m,at,a[N],bt,b[N];
int main()
{
	read(n,m),read(at);for(int i=1;i<=at;i++) read(a[i]);
	read(bt);for(int i=1;i<=bt;i++) read(b[i]);
	sort(a+1,a+at+1),sort(b+1,b+bt+1);
	for(int i=0;i<=at;i++)
	{
		int la=a[i],rs=0;
		for(int i=1;i<=n&&i<=la-1;i++) rs+=min(la-i,m);
		if(rs<i) return puts("NO"),0;
		for(int j=1,ls=2;j<=bt;j++)
		{
			int lb=b[j];for(int k=ls;k<=lb;k++)
				for(int x=max(1,k-m),y=x+m+1-k;x<=n;x++,y++)
					if(y>m) break;else if(x+y>la) rs++;
			ls=b[j]+1;if(rs<i+j) return puts("NO"),0;
		}
	}return puts("YES"),0;
}
```

---

