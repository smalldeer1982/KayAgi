# Strong Vertices

## 题目描述

Given two arrays $ a $ and $ b $ , both of length $ n $ . Elements of both arrays indexed from $ 1 $ to $ n $ . You are constructing a directed graph, where edge from $ u $ to $ v $ ( $ u\neq v $ ) exists if $ a_u-a_v \ge b_u-b_v $ .

A vertex $ V $ is called strong if there exists a path from $ V $ to all other vertices.

A path in a directed graph is a chain of several vertices, connected by edges, such that moving from the vertex $ u $ , along the directions of the edges, the vertex $ v $ can be reached.

Your task is to find all strong vertices.

For example, if $ a=[3,1,2,4] $ and $ b=[4,3,2,1] $ , the graph will look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1857D/d82544424ea2e3e9ac339f1c8fa7dad6ac60fbfc.png) The graph has only one strong vertex with number $ 4 $

## 说明/提示

The first sample is covered in the problem statement.

For the second sample, the graph looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1857D/4f95c34528d6169c692c6bf6f2ed63814b90c73c.png) The graph has two strong vertices with numbers $ 3 $ and $ 5 $ . Note that there is a bidirectional edge between vertices $ 3 $ and $ 5 $ .In the third sample, the vertices are connected by a single directed edge from vertex $ 2 $ to vertex $ 1 $ , so the only strong vertex is $ 2 $ .

In the fourth sample, all vertices are connected to each other by bidirectional edges, so there is a path from every vertex to any other vertex.

## 样例 #1

### 输入

```
5
4
3 1 2 4
4 3 2 1
5
1 2 4 1 2
5 2 3 3 1
2
1 2
2 1
3
0 2 1
1 3 2
3
5 7 4
-2 -3 -6```

### 输出

```
1
4 
2
3 5 
1
2 
3
1 2 3 
2
2 3```

# 题解

## 作者：BFSDFS123 (赞：3)

好题。比赛时蒙的的结论，但是后来证出来了。

但是我最小值开大了挂了一发。

但是我赛后叉掉了两个最小值开大却过了的倒霉老哥。快乐。

考虑转换式子得到 $a_u-b_u\ge a_v-b_v$。

不难发现，由于大于是连续性的，所以假如 $a>b,b>c$ 那么 $a>c$。此时就会发现，$a$ 连向 $b$，$b$ 连向 $c$。此时由于 $a>c$，$c$ 不能连向 $a$，故若都是大于号，我们会发现整个图没有环。于是在这个图上，我们可以得到若一个点被别的点指向，那么这个点一定不能走到指向它的那个点。从而得到，若一个点的入度为 $0$，那么它一定符合题意。

考虑 $a=b$ 的情况。此时 $a$ 与 $b$ 之间有一个双向边。此时 $a$ 可以到 $b$，$b$ 可以到 $a$。那么我们又得到了一个性质，若一个点除去所有的与其相连的双向边后，若其入度为 $0$，那么它一定符合题意。

具体实现的时候，我们计算出所有的 $a_i-b_i$，选取最大值即可。

注意到如果你是打擂台求最大值，你需要注意 max 的初始值，pretest 开到 -1e9 就可以过，但是由于 $-10^9\le a_i,b_i\le10^9$，所以需要开到 $2\times 10^9$，一堆倒霉老哥寄在了这里。

[代码](https://www.luogu.com.cn/paste/m986eel4)。

附上叉掉了两个倒霉老哥的数据：

```
1
2
-1000000000 -1000000000
1000000000 1000000000
```

---

## 作者：WsW_ (赞：2)

### 思路
将题目中的式子移项，得：$a_u-b_u\ge a_v-b_v$。  
那么对于点 $u,v$，只存在以下三种情况：
- $a_u-b_u>a_v-b_v$，连一条从 $u$ 到 $v$ 的边。
- $a_u-b_u<a_v-b_v$，连一条从 $v$ 到 $u$ 的边。
- $a_u-b_u=a_v-b_v$，连两条边，从 $u$ 到 $v$，从 $v$ 到 $u$。 

显然，只有 $a_u-b_u$ 最大的点会向其他所有点连边。因此只需要找到最大的 $a_u-b_u$ 即可。

---
### 代码和[提交记录](https://www.luogu.com.cn/record/119649500)
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	long long x;
	int id;
};
node a[500005];
int t,n;
int b;
bool cmp(node x,node y){
	return x.x>y.x;
}
bool cmp2(node x,node y){
	return x.id<y.id;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i].x);
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&b);
			a[i].x-=b;
			a[i].id=i;
		}
		sort(a+1,a+1+n,cmp);
		int ans;
		for(ans=1;a[ans+1].x==a[1].x&&ans+1<=n;ans++);
		printf("%d\n",ans);
		sort(a+1,a+ans+1,cmp2);
		for(int i=1;i<=ans;i++){
			printf("%d ",a[i].id);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：Crazyouth (赞：1)

**翻译**

给定 $n$ 个数的数组 $a,b$，并给你 $n$ 个顶点，假如 $a_u-a_v\ge b_u-b_v$，$u$ 会向 $v$ 连一条有向边。求所有能到达除它之外任何一个顶点的点。

**分析**

~~CF 经典诈骗题。~~ 这题和图论根本没有任何关系。对原式做一点简单移项：$a_u-b_u\ge a_v-b_v$，就会发现，我们只需要按照 $a_i-b_i$ 从大到小排序，然后找到 $a_i-b_i$ 最大的几个数就解决了题目。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node
{
	int a,b,pos,sub;//a数组，b数组，位置，同位置的差
}s[int(2e5+10)];
int cmp(node x,node y)//按照差为第一关键字，位置为第二关键字
{
	if(x.sub!=y.sub) return x.sub>y.sub;
	else return x.pos<y.pos;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>s[i].a;
			s[i].pos=i;//记录位置
		} 
		for(int i=1;i<=n;i++)
		{
			cin>>s[i].b;
			s[i].sub=s[i].a-s[i].b;//记录差值
		}
		sort(s+1,s+n+1,cmp);
		s[0].sub=s[1].sub;//判断的时候会往前判一位，提前把0赋值了避免忽略1
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			if(s[i].sub!=s[i-1].sub) break;//不是最大，退出
			ans++;//答案加一
		}
		cout<<ans<<endl;
		for(int i=1;i<=ans;i++) cout<<s[i].pos<<' ';//循环答案个数次，输出答案
		cout<<endl;
	}
	return 0;
}

---

## 作者：szhqwq (赞：1)

## $\tt{Solution}$

~~诈骗题一道。~~

我们考虑将 $a_u - a_v \geq b_u - b_v$ 变为 $a_u - b_u \geq a_v - b_v$，令 $c_i \gets a_i - b_i$。

根据式子，得出 $c_i$ 最大的点 $i$ 会和其它所有点连边（可能有多个），所以处理好 $c_i$，排序后统计答案即可。

[Link](https://codeforces.com/contest/1857/submission/217683360)

---

## 作者：ScottSuperb (赞：1)

## 解法分析
我们首先将连边条件 $a_u-a_v \ge b_u-b_v$ 移项得到 $a_u-b_u \ge a_v-b_v$，可知将两次读入的数组做差，较大者到较小者之间有边。因此做差后结果最大的点为“强结点”，无需考虑间接联通。证明：设做差后数组为 $c$，已知 $c_i \ge c_j, c_j \ge c_k$，可得 $c_i \ge c_k$，因此任意间接联通的点一定直接联通。
## 代码
快读快写函数定义已省略。
```
#include <bits/stdc++.h>

using namespace std;

const int MXN = 2e5 + 5;
int n, ans[MXN], cnt;
struct vertex {
  int n, v;
  bool operator<(vertex b) { return v < b.v; }
} a[MXN];

int main() {
  int t = read(), n;
  while (t--) {
    n = read(), cnt = 0;
    for (int i = 1; i <= n; ++i) a[i].v = read(), a[i].n = i;
    for (int i = 1; i <= n; ++i) a[i].v -= read();
    sort(a + 1, a + n + 1);
    for (int i = n; i; --i) {
      if (a[i].v != a[n].v) break;
      ans[cnt++] = a[i].n;
    }
    sort(ans, ans + cnt);
    write(cnt);
    for (int i = 0; i < cnt; ++i) write(ans[i], ' ');
    pc('\n');
  }
  return 0;
}
```

---

## 作者：Special_Tony (赞：1)

[洛谷传送门](/problem/CF1857D) & [CF 传送门](//codeforces.com/problemset/problem/1857/D)
# 思路
先吐槽一下：CF 咋又来诈骗题了啊，一看是到图论题，但实际上咋和图半毛钱关系都没有啊！

这题给的原式是 $a_i-a_j\ge b_i-b_j$，我们可以对原式做点手脚（移一下项），会变成 $a_i-b_i\ge a_j-b_j$。所以我们只要按照 $a_i-b_i$ 从大到小排序就可以了，而到达其它所有点的点就是 $a_i-b_i$ 最大的几个点了。
# 代码
```cpp
# include <bits/stdc++.h> //万能头
using namespace std;
int t, n, x, sum;
struct node {
	int v, id;
	bool operator < (const node& x) const { //重载运算符，当然也可以用 cmp 代替
		if (v != x.v)
			return v > x.v;
		return id < x.id;
	}
} a[200005];
int main () {
	cin >> t;
	while (t --) {
		cin >> n;
		sum = 0; //多组数据要清空！
		for (int i = 0; i < n; ++ i)
			cin >> a[i].v, a[i].id = i + 1;
		for (int i = 0; i < n; ++ i)
			cin >> x, a[i].v -= x; //a[i]-b[i]
		sort (a, a + n); //排序
		for (int i = 0; i < n; ++ i)
			if (a[i].v == a[0].v) //和最大值相同
				++ sum;
			else
				break ;
		cout << sum << '\n';
		for (int i = 0; i < n; ++ i)
			if (a[i].v == a[0].v)
				cout << a[i].id << ' ';
			else
				break ;
		cout << '\n'; //别忘了换行！
	}
	return 0;
}
```

---

## 作者：2huk (赞：1)

# D. [Strong Vertices](https://codeforces.com/contest/1857/problem/D)

## Description

给定两个数组 $a$ 和 $b$，对此构造一张有向图：

- 若 $a_u - a_v \ge b_u - b_v$，则 $u$ 向 $v$ 连边。

求所有向其他**所有**顶点连边的顶点个数，并按**从小到大**顺序输出它们。

## Solution

将 $a_u - a_v \ge b_u - b_v$ 移项，得 $a_u - b_u \ge a_v - b_v$。所以我们统计一个 $c_i = a_i - b_i$，那么最后只需要看有多少个 $c_i$ 满足它大于等于所有数即可。

这个值显然为 $c$ 中的最大值，因此我们需要做的就是统计 $c$ 中最大值的数量。这里可以直接排序，为了方便第二问，需要用一个 `pair` 同时存储位置。

## Code

```cpp
void Solve()
{
	n = read();
	
	fup (i, 1, n)
		a[i] = read();
	
	fup (i, 1, n)
		b[i] = read(),
		c[i] = {a[i] - b[i], i};
	
	sort(c + 1, c + n + 1);
	reverse(c + 1, c + n + 1);
	
	int res = 1;
	fup (i, 2, n)
		if (c[i].first == c[i - 1].first)
			++ res;
		else break;
	
	wel(res);
	fdw (i, res, 1)
		wsp(c[i].second);
	
	puts("");
	return;
}
```

---

## 作者：Wf_yjqd (赞：1)

这场 Div.3 最简单的一道一眼题。

------------

一看到不等式直接考虑移项为 $a_u-b_u\ge a_v-b_v$。

相当于每个数往所有比他小的数连边，所以只有最大值能到达其他所有点。

所以求出 $a_i-b_i$ 的最大值个数和位置即可。

------------

太简单辣！

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+84;
int T,n,a[maxn],b,mx;
vector<int> ad;
int main(){
    scanf("%d",&T);
    while(T--){
        ad.clear();
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        mx=-0x7f7f7f7f;
        for(int i=1;i<=n;i++){
            scanf("%d",&b);
            a[i]-=b;
            mx=max(mx,a[i]);
        }
        for(int i=1;i<=n;i++)
            if(a[i]==mx)
                ad.push_back(i);
        printf("%d\n",ad.size());
        for(int i:ad)
            printf("%d ",i);
        putchar('\n');
    }
    return 0;
}
```


---

## 作者：stswkl (赞：0)

## 题目翻译

给定长度均为 $n$ 的两个数组 $a$ 和 $b$。对于每个 $u \left (1 \le u \le n \right )$ 和 $v \left (1 \le v \le n \right )$ 若满足 $u \ne v$ 和 $a_u-a_v \ge b_u-b_v$ 则建一条边，输出所有出度为 $n-1$ 的节点。

## 思路

可以想到暴力的解法，枚举每一个 $u$ 和 $v$，判断是否建边，时间复杂度 $O(n^2)$，显然过不了。暴力过不去，就思考如何优化，将题目给的算式变成 $a_u+b_v-b_u-a_v \ge 0$ 如果要满足题目的的输出情况，可以枚举每个 $v(v \ne u)$，求出其中 $b_v-a_v$ 的最小值，然后判断是否满足 $a_u+b_v-b_u-a_v \ge 0$，若满足，则表示其他所有的 $v$ 都可以建边，输出该节点。可以用 map 使得求最小值的这个过程时间复杂度降至 $O(\log n)$，总体的时间复杂度为 $O(n \log n)$，可以过。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
long long T,n,k,a[N],b[N],ans[N];
map<long long,int>x; //x用于存最小值
int main()
{
    cin>>T;
    while(T--)
    {
        x.clear(),k=0;
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1;i<=n;i++)cin>>b[i];
        for(int i=1;i<=n;i++)x[b[i]-a[i]]++; //将每个b_v-a_v存下来
        for(int i=1;i<=n;i++)
        {
            x[b[i]-a[i]]--; //v!=u
            if(x[b[i]-a[i]]==0)x.erase(b[i]-a[i]);
            if(a[i]-b[i]+(x.begin()->first)>=0) //x.begin()->first 是每个b_v-a_v中的最小值
                ans[++k]=i;
            x[b[i]-a[i]]++;
        }
        cout<<k<<'\n';
        for(int i=1;i<=k;i++)
            cout<<ans[i]<<' ';
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：LCat90 (赞：0)

首先排除是图论的可能性，因为建边就需要 $n^2$，而 div3 不可能在这里考什么线段树优化建图。

所以应该是思维。观察样例发现，对于点 $x,y,z$，如果有边 $x\rightarrow y,y\rightarrow z$，那么一定有边直接 $x\rightarrow z$。

这说明，每个点直接到达的点和通过其它点到达的点是相同的，就和图论没有关系了。

将式子 $a_x-a_y\ge b_x-b_y$ 移项得 $(a_x-b_x)-(a_y-b_y)\ge 0$，所以此题的 $a$ 和 $b$ 直接合并为 $a-b$。并按此从小到大排序。

然后对于每个点，如果要到达所有点，那么肯定是要 $a_y-b_y$ 最大时仍满足条件，即 $(a_i-b_i)-(a_n-b_n)\ge 0$。

----------

考场上的代码有些乱，打得很冗余。但道理是一样的。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5;
int t, n, b[N], ot[N]; 
struct node {
	int x1, x2, id;
} a[N];
bool cmp(node a, node b) { return a.x2 < b.x2; } 
signed main() {
	cin >> t;
	while(t--) {
		int cnt = 0;
		cin >> n;
		for(int i = 1;i <= n; ++i) scanf("%lld", &a[i].x1), a[i].id = i;
		for(int i = 1;i <= n; ++i) scanf("%lld", &b[i]), a[i].x1 -= b[i], a[i].x2 = -a[i].x1;
		sort(a + 1, a + n + 1, cmp);
		for(int i = 1;i <= n; ++i) {
			int x = a[i].x1;
			if(i == 1 or x + a[1].x2 >= 0) ot[++cnt] = a[i].id;
		} 
		sort(ot + 1, ot + cnt + 1);
		printf("%lld\n", cnt);
		for(int i = 1;i <= cnt; ++i) printf("%lld ", ot[i]); puts("");
	}
	return 0;
}
```

---

