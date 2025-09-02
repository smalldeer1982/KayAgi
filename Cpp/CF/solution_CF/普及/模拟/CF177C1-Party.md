# Party

## 题目描述

Beaver 有 $n$ 个熟人，这些人之间有若干个朋友关系与讨厌关系。现在，Beaver 想邀请他们去一个派对

当然，对于去派对的人是有要求的。

对于每一个去派对的人：

- 他的所有朋友的应该在派对中，不管是直接朋友还是间接朋友
- 派对里不应该有他讨厌的人

你的任务是求出 Beaver 可以邀请的最多的人数

## 说明/提示

$n \le 2000$  
$0 \le k,m \le min(10^5, \frac{n\cdot (n-1)}{2})$
$0 \le k+m \le min(10^5, \frac{n\cdot (n-1)}{2})$

感谢 @[_Wolverine](https://www.luogu.com.cn/user/120362) 提供的翻译

## 样例 #1

### 输入

```
9
8
1 2
1 3
2 3
4 5
6 7
7 8
8 9
9 6
2
1 6
7 9
```

### 输出

```
3```

# 题解

## 作者：Priori_Incantatem (赞：5)

[CF177C1](https://www.luogu.com.cn/problem/CF177C1) 与 [CF177C2](https://www.luogu.com.cn/problem/CF177C2) 完全一样，可放心食用

首先我们不考虑互相讨厌的关系，先将朋友之间连边，使得这 $n$ 个人形成若干个连通块，我们把这些连通块成为“朋友圈”  

仔细想想就可以发现：在一个朋友圈中，如果存在两个互相讨厌的人 $u,v$，那么这个朋友圈中的所有人都去不了派对  
因为 $u,v$ 两人在同一连通块中，所以他们互为朋友；而他们又互相讨厌，所以只去一个人也是不满足要求的，只能全部不去

我们可以用并查集维护朋友信息  
对于一条互相讨厌的信息，如果两人不在同一朋友圈中，无视此信息，否则将该朋友圈打上标记

最后，寻找人数最多且未被标记的朋友圈，并输出人数

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int Maxn=2020,inf=0x3f3f3f3f;
int f[Maxn],c[Maxn]; //c[] 统计每个朋友圈的人数
bool vis[Maxn]; // 标记
int n,m,ans;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int find(int x)
{
	if(f[x]==x)return x;
	return f[x]=find(f[x]);
}
int main()
{
//	freopen("in.txt","r",stdin);
	n=read(),m=read();
	
	for(int i=1;i<=n;++i)
	f[i]=i;
	for(int i=1;i<=m;++i) // 维护朋友关系
	{
		int x=read(),y=read();
		f[find(x)]=find(y);
	}
	m=read();
	for(int i=1;i<=m;++i) // 维护互相讨厌的关系
	{
		int x=read(),y=read();
		if(find(x)!=find(y))continue;
		vis[find(x)]=1;
	}
	for(int i=1;i<=n;++i) // 统计朋友圈人数
	c[find(i)]++;
	
	for(int i=1;i<=n;++i) // 寻找答案
	{
		if(f[i]!=i || vis[i])continue;
		ans=max(ans,c[i]);
	}
	printf("%d\n",ans);
	
	return 0;
}
```

---

## 作者：封禁用户 (赞：3)

# 题目解法

一道并查集的题目。

- 他的所有朋友都该在派对中，不管是直接朋友还是间接朋友。所以是并查集，将直接的朋友和间接的朋友都放在一起。

- 考虑完朋友关系，再考虑一下互相讨厌的关系：派对里不该会有他讨厌的人。用 bool 数组标记一下他讨厌的人，在求结果时直接将这个人跳过去即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,m,a[100050],cnt,A[100050];
bool kop[10005];
int check(int x){
	if(x==a[x]) return x;
	return a[x]=check(a[x]);
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) a[i]=i;
	for(int i=1;i<=k;i++){
		int x,y;
		cin>>x>>y;
		if(check(x)!=check(y)) a[check(y)]=check(x);		
	}
	cin>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		if(check(x)!=check(y)) continue;
		kop[check(x)]=1;
	}
	for(int i=1;i<=n;i++) A[check(i)]++;
	for(int i=1;i<=n;i++)
		if(a[i]==i&&!kop[i]) cnt=max(cnt,A[i]);
	cout<<cnt;
    return 0;
}
```


---

## 作者：WaterSky (赞：1)

[CF177C1 Party](https://www.luogu.com.cn/problem/CF177C1)。

这一题与 [CF177C2 Party](https://www.luogu.com.cn/problem/CF177C2) 完全相等。

首先，读题。


Beaver 有 $n$ 个熟人，这些人之间有若干个朋友关系与讨厌关系。现在，Beaver 想邀请他们去一个派对。

当然，对于去派对的人是有要求的。

对于每一个去派对的人：

- 他的所有朋友的应该在派对中，不管是直接朋友还是间接朋友。
- 派对里不应该有他讨厌的人。

你的任务是求出 Beaver 可以邀请的最多的人数。


然后仔细阅读题后需要判断使用的算法。

通过阅读题目中的第一条判断条件：他的所有朋友的应该在派对中，不管是直接朋友还是间接朋友，和题目的第一句：Beaver 有 $n$ 个熟人，这些人之间有若干个朋友关系与讨厌关系，可以判断出这一道题可以用并查集的做法。

再思考算法的细节。

题目给出了一张图片很好的提示了我们。
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF177C2/2a1afae751aa0d8fbeb2d7b54cbbe0f7e8bfc3ce.png)

这张图片表示了样例中的朋友关系。

不看红色的线条，可以看出这些人组成了三个连通块，可以说这几个连通块指朋友圈。我们可以代入并查集的模版维护每一个朋友圈。

然后加入红色的线条。我们以第 $6$,$7$,$8$,$9$ 个人组成的朋友圈提出问题：这一个朋友圈是否可以参加派对？再一次阅读题目。


对于每一个去派对的人：

- 他的所有朋友的应该在派对中，不管是直接朋友还是间接朋友。
- 派对里不应该有他讨厌的人。


可以得出答案为否。因为如果要所有成员都在派对里，那么中间就有两个人出现了矛盾，不符合第二点，所以不可以。

由此得出如果朋友圈中有一对讨厌的关系的人是不能参加派对的，因为一定会与规则矛盾。我们可以在维护并查集后，用一个数组记录每一个出现讨厌关系的朋友圈。

然后再看另外两个朋友圈。依次判断他们是否合法，得出答案：都是合法的。那么就挑选比较优的一点（疑问：翻译好像有误，第二点应该是：派对里不应该有他讨厌的人或非朋友的人）。是否更优的条件是什么呢？当然是人数多的更优啦！那么我们可以再用一个数组记录每一个合法的朋友圈的人数，再用变量判断最大值就可以了。

到了这里，所有核心部分都讲解完了。下面贴出代码：
```
#include<bits/stdc++.h>
using namespace std;
long long n,k,m,a[100005],ans,A[100005];
bool bj[10005];
long long find(long long x)//寻找朋友圈代表。
{
	if(x==a[x]) return x;//如果就是x，那么就返回x。
	return a[x]=find(a[x]);并查集的一个优化，将自己的上级直接等于自己所在的朋友圈代表。
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++) a[i]=i;//一开始每一个人的朋友圈只有自己，代表也是自己。
	for(int i=1;i<=k;i++)
	{
		long long x,y;
		cin>>x>>y;
		if(find(x)!=find(y)) a[find(y)]=find(x);//如果本来就不是同一个朋友圈的那么就将其中一个的代表的代表记录为另一个的代表。		
	}
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		long long x,y;
		cin>>x>>y;
		if(find(x)!=find(y)) continue;//如果不是同一个朋友圈则不用进行下面的步骤。
		bj[find(x)]=1;//将自己的朋友圈记录为不合法。
	}
	for(int i=1;i<=n;i++) A[find(i)]++;//将每一个朋友圈的人数记录。
	for(int i=1;i<=n;i++)
		if(a[i]==i&&!bj[i]) ans=max(ans,A[i]);//如果合法那么就择优。
	cout<<ans;/
    return 0;
}
```

致管理员：如果有错误，请一次性将错误指出，让我更快的改正错误，谢谢。

---

## 作者：e4fsrc2e4fsrc2 (赞：0)

## [Party](https://www.luogu.com.cn/problem/CF177C1)
## 思路分析
用并查集记录下每个人的间接朋友和直接朋友，再用 $siz_i$ 表示并记录下直接或间接朋友中有 $i$ 的人有多少个。

再判断 $m$ 个组相互讨厌的人是否在同一组：设这两个人分别为 $x,y$，当且仅当 `getf(x)=getf(y)` 的情况下，直接或间接朋友中有 `getf(x)` 就不可取，此时用 `vis` 数组记录下第 $i$ 个可不可取即可（其中 `getf(x)` 表示 $x$ 的祖先是谁）。

最后答案就是当 $vis_i=0$ 的最大的 $siz_i$。

PS：
1. 在合并时要将合并过去的数清空，就像这样：
```cpp
for(R i=1,x,y; i<=k; i++){
		cin>>x>>y;
		int a=getf(x),b=getf(y);
		if(f[a]!=b)f[a]=b,siz[b]+=siz[a],siz[a]=0;
	}
```
2. 初始化为 $siz_i=1$。
## AC 代码
[代码](https://codeforces.com/contest/177/submission/222432025)

---

## 作者：Neilchenyinuo (赞：0)

- 本题使用并查集来做。

- #### ~~本人觉得这题和[团伙](https://www.luogu.com.cn/problem/P1892)很相似。~~

## 题目大意

Beaver 有 $n$ 个熟人，这些人之间有若干个朋友关系与讨厌关系。现在，Beaver 想邀请他们去一个派对。

当然，对于去派对的人是有要求的。

对于每一个去派对的人：

- 他的所有朋友的应该在派对中，不管是直接朋友还是间接朋友。

- 派对里不应该有他讨厌的人。

你的任务是求出 Beaver 可以邀请的最多的人数。

## 核心函数

1. $find(x)$ 这个函数是用来寻找根节点的，方便判断两个元素是否在同一集合内，代码如下：

```cpp
int find(int x)
{
	if(fa[x]==x)
		return x;
	return fa[x]=find(fa[x]);//路径压缩，这样不容易超时，相当于每个子结点都直接连着根节点，这样遍历时就更加快速。
}
```
2. $u(x,y)$ 这个函数是用来合并两个集合，用 find 函数找出两个需合并的点的根节点，然后将其中一个根节点接在另一个根节点之下即可，代码如下：

```cpp
void u(int x,int y)
{
	x=find(x),y=find(y);
	if(x!=y)
		fa[x]=y;
	return ;
}
```

## Solution

1. 先将输入的每一个朋友关系合并到一个集合中。

2. 然后统计 Beaver 的朋友数量。

3. 再输入讨厌的人，然后将其标记。

4. 再整个扫一遍，如果是讨厌就跳过，最后找到一个最大的集。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2005;
int n,k,fa[N],cnt[N],ans;
bool vis[N];
int find(int x)
{
	if(fa[x]==x)
		return x;
	return fa[x]=find(fa[x]);
}
void u(int x,int y)
{
	x=find(x),y=find(y);
	if(x!=y)
		fa[x]=y;
	return ;
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=k;i++)
	{
		int x,y;
		cin>>x>>y;
		u(x,y);
	}
	for(int i=1;i<=n;i++)
		cnt[find(i)]++;
	cin>>k;
	for(int i=1;i<=k;i++)
	{
		int x,y;
		cin>>x>>y;
		x=find(x),y=find(y);
		if(x==y)
			vis[x]=1;
	}
	for(int i=1;i<=n;i++)
		if(vis[find(i)]==0)
			ans=max(ans,cnt[find(i)]);
	cout<<ans;
	return 0;
}
```

### ~~[双倍经验](https://www.luogu.com.cn/problem/CF177C2)~~

---

## 作者：qinmingze (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF177C1)
### [双倍经验](https://www.luogu.com.cn/problem/CF177C2)
## 思路
- 先不考虑互相讨厌的关系，先只看题目中的一个条件：**他的所有朋友的应该在派对中，不管是直接朋友还是间接朋友。** 这时我们第一个想到的应该就是[**并查集**](https://oi-wiki.org/ds/dsu/)，将直接的朋友和间接的朋友放在一起。

- 考虑完朋友关系，我们在考虑一下互相讨厌的关系：**派对里不应该有他讨厌的人**。 很简单只需要用 bool 数组标记一下他讨厌的人，在求结果时直接将这个人跳过去就行了。


# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2010;
int n, k;
int t[N], fa[N];
bool vis[N];//标记数组，标记他讨厌的人
int find(int x){
	if(fa[x] == x)return fa[x];
	return fa[x] = find(fa[x]);
}
void merge(int x, int y){
	int fx = find(x);
	int fy = find(y);
	fa[fx] = fy;
}
int main(){
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i++)fa[i] = i;
	for(int i = 1; i <= m; i++){//朋友关系
		int x, y;
		cin >> x >> y;
		merge(x, y);
	}
	for(int i = 1; i <= n; i++)t[find(i)]++;//统计人数
	cin >> m;
	for(int i = 1; i <= m; i++){//讨厌关系
		int x, y;
		cin >> x >> y;
		if(find(x) == find(y))vis[find(x)] = 1;//标记，不加入派对
	}
	int ans = 0;
	for(int i = 1; i <= n; i++){
		if(!vis[find(i)])ans = max(ans, t[find(i)]);
	}
	cout << ans << endl;
   return 0;
}
```


------------

### [已AC](https://www.luogu.com.cn/record/97609383)

---

## 作者：2c_s (赞：0)

[C1 题目传送门](https://www.luogu.com.cn/problem/CF177C1)

[C2 题目传送门](https://www.luogu.com.cn/problem/CF177C2)

## 思路

> 他的所有朋友的应该在派对中，不管是直接朋友还是间接朋友。

通过这句话，我们联想到并查集。把所有直接朋友和间接朋友放到同一个集里面。

> 派对里不应该有他讨厌的人。

如果派对里有他讨厌的人，就用 bool 数组标记，最后遍历的时候直接跳过就行了。最后找最大的一个集。

## 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2010;
int n,k,m,fa[N],tom[N],ans;
bool flag[N];
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	int fx=find(x);
	int fy=find(y);
	fa[fx]=fy;
	return ;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;++i)fa[i]=i;
	for(int i=1;i<=k;++i){
		int x,y;
		cin>>x>>y;
		merge(x,y);
	}
	for(int i=1;i<=n;++i)tom[find(i)]++;
	cin>>m;
	for(int i=1;i<=m;++i){
		int x,y;
		cin>>x>>y;
		if(find(x)==find(y))flag[find(x)]=1;
	}
	for(int i=1;i<=n;++i){
		if(!flag[find(i)])ans=max(ans,tom[find(i)]);
	}
	cout<<ans<<endl;
    return 0;
}
~~~

---

## 作者：linaonao (赞：0)

第一眼看过去以为是[P1352没有上司的舞会](https://www.luogu.com.cn/problem/P1352)，用树上dp打了半天

后来看到题干中“他的所有朋友的应该在派对中，不管是直接朋友还是间接朋友”，马上改掉，写并查集去了。

所以我们将所有朋友放到同一集中，碰到有仇人直接原地解散。

代码实现是靠一个标记数组no标记所有被毁掉的朋友们

代码：

```cpp
#include<bits/stdc++.h>
template<typename T>inline void read(T &x){
	T f=0;x=0;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f|=ch=='-';
    for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    x=f?-x:x;
}
template<typename T>inline void write(T x){
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	putchar(x%10+48);
}
using namespace std;	
int n,k,m,fa[2005];
int s[2005],cnt,no[2005];
inline int find(int x){
	if(x==fa[x])return x;
	return fa[x]=find(fa[x]);
}
inline void add(int x,int y){fa[find(x)]=find(y);}
int main(){
	read(n),read(k);
	for(int i=1;i<=n;++i) fa[i]=i;
	for(int i=1;i<=k;++i){
		int a,b;read(a),read(b);
		add(a,b);
	}
	for(int i=1;i<=n;++i) ++s[find(i)];
	read(m);
	for(int i=1;i<=m;++i){
		int a,b;read(a),read(b);
		if(find(a)==find(b)){
			no[find(a)]=1;	
		}
	}
	for(int i=1;i<=n;++i){
		if(no[find(i)]) continue;
		cnt=max(cnt,s[find(i)]); 
	}
	write(cnt);
	return 0;
}

```


---

## 作者：InversionShadow (赞：0)

[双倍经验？](https://www.luogu.com.cn/problem/CF177C2)

考虑使用并查集。维护每一对朋友与敌人，如果某个集合中既出现了朋友又出现了敌人，那么这个集合就可以跳过了。答案就是没有跳过的最大集合中的元素个数了。

```cpp
#include <bits/stdc++.h>

using namespace std;

int a[100001], n, m, k, cnt[100001];
bool vis[100001];

void inii() {
  for (int i = 1; i <= n; i++) {
    a[i] = i;
  }
}

int find(int i) {
  if (a[i] != i) {
    a[i] = find(a[i]);
  }
  return a[i];
}

void add(int i, int j) {
  int _i = find(i);
  int _j = find(j);
  a[_i] = _j; 
}

int main() {
  cin >> n >> k;
  inii();
  for (int i = 1; i <= k; i++) {
    int u, v;
    cin >> u >> v;
    add(u, v);
  }
  for (int i = 1; i <= n; i++) {
    cnt[find(i)]++; 
  }
  cin >> m;
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    if (find(u) == find(v)) {
      vis[find(u)] = 1;
    }
  }
  int maxx = 0;
  for (int i = 1; i <= n; i++) {
    if (vis[find(i)]) {
      continue;
    }
    maxx = max(maxx, cnt[i]);
  }
  cout << maxx;
  return 0;
}
```

---

