# Virtual Friends

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2498

[PDF](https://uva.onlinejudge.org/external/115/p11503.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11503/22196a0b85da544cbb9282738f8363a33f28edf0.png)

## 样例 #1

### 输入

```
1
3
Fred Barney
Barney Betty
Betty Wilma```

### 输出

```
2
3
4```

# 题解

## 作者：tjtdrxxz (赞：8)

题意：

有 $ n $ 组关系，每组关系会给你两个人名，你需要输出与他们有关的人的数量（包括他们自己）。

看到题目要我们输出每次合并后与这两人有关的人的数量，很容易想到并查集。因为有输出联通块大小，所以我们可以直接写按秩合并的并查集（根据两个块的大小合并，时间复杂度严格 $ O (n \log {n}) $）。
![](https://cdn.luogu.com.cn/upload/image_hosting/jwgoiq2y.png)
但输入的是两个人名，所以还要哈希一下，其他的话其实就没什么要注意的了。

并查集 code：
```cpp
int find (int x)
{
	return fa[x] == x ? x : find (fa[x]);
}
void merge (int u, int v)
{
	u = find (u), v = find (v);
	if (u != v)
	{
		if (size[u] > size[v])
		{
			size[u] += size[v];
			fa[v] = u;
		}
		else
		{
			size[v] += size[u];
			fa[u] = v;
		}
	}
}
```

---

## 作者：jianhe (赞：5)

## [UVA11503 Virtual Friends](https://www.luogu.com.cn/problem/UVA11503) 题解

## 算法：并查集+哈希

 字符串怎么处理呢？ 可以用哈希来解决，用 `unordered_map` 来存储每一个字符串所对应的数值。之后就可以用并查集来做啦~。（之所以不用 `map` ，是因为 map 的常数比较大，里面的数据都是自动排序的，而 `unordered_map` 不会自动排序，常数略小。）
 
 并查集不会的同志请做 [P3367](https://www.luogu.com.cn/problem/P3367)
 
 此外，还有不少细节要注意。因为有多组数据，所以不要忘记每次循环都要**初始化**。初始化时，还要注意每次读入是两个人名，所以记得数组要开两倍。 

## 上代码：

```cpp
//UVA11503 Virtual Friends 题解 
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2e5+10;//开两倍不要忘了 
ll T,n,fa[N],sz[N],tot;
string x,y;
unordered_map<string,ll> p;
void jian(){
	//注意，i<=n*2，要*2哦 
	for(int i=0;i<=n*2;i++) fa[i]=i,sz[i]=1;
	return;
}
ll getfa(ll x){
	// fa=getfa(fa[x]) 用路径压缩，节省时间复杂度 
	return fa[x]==x?x:fa[x]=getfa(fa[x]);
}
void hebing(ll x,ll y){
	ll fx=getfa(x),fy=getfa(y);
	if(fx!=fy){//若 x 和 y 本身就是朋友，不需要再合并了 
		if(sz[fx]>sz[fy]) swap(fx,fy);
		fa[fx]=fy,sz[fy]+=sz[fx];//启发式合并，合并在短的一边，优化时间复杂度 
	}
}
ll size(ll x){
	return sz[getfa(x)];
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		p.clear(),tot=0,jian();//初始化 
		while(n--){
			cin>>x>>y;
			if(p.find(x)==p.end()) p[x]=++tot;//用 p 记录字符串所对应的数值 
			if(p.find(y)==p.end()) p[y]=++tot;
			hebing(p[x],p[y]);
			cout<<size(p[x])<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：xhhhh36 (赞：4)

# 题意
有 $n$ 组数据和 $f$ 组关系，每组关系表示 $A$ 和 $B$ 是朋友。朋友的朋友也是朋友。每次合并后问 $A$ 和 $B$ 所在的朋友群有多少人？
# 思路
看到这题的描述马上会想到用**并查集**维护集合。那并查集怎么维护集合呢？首先用一个 $fa$ 数组来存储每个集合的代表元素，最开始有 $n$ 个集合。每遇到一个关系，就将 $A$ 和 $B$ 所在的集合合并，即 $fa_{B} \to fa_{A}$。最后再用一个计数数组 $ans$ 来计数每个集合中的元素个数并实时更新，即 $ans(fa_{A})+ans(fa_{B}) \to ans(fa_{A})$。因为输入的 $A$ 和 $B$ 为字符串类型，所以要使用 [map](https://zhuanlan.zhihu.com/p/127860466) 来处理人名。[并查集模板题](https://www.luogu.com.cn/problem/P3367)。
# AC code
```cpp
#include <bits/stdc++.h>

using namespace std;
map<string,int> z;
int n,f,fa[200001],ans[200001],cnt;
int find(int x)
{
	if (x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
void un(int x,int y)
{
	ans[find(y)]+=ans[find(x)];
	fa[find(x)]=find(y);
}
int main()
{
	cin>>n;
	while (n--)
	{
		cin>>f;
		for (int i=1;i<=f*2;i++)
		{
			fa[i]=i;
			ans[i]=1;
		}
		for (int i=1;i<=f;i++)
		{
			string x,y;
			cin>>x>>y;
			if (!z[x]) z[x]=++cnt;
			if (!z[y]) z[y]=++cnt;
			if (find(z[x])!=find(z[y])) un(z[x],z[y]);
			cout<<ans[find(z[y])]<<endl;
		}
	}
	return 0;
}
```



---

## 作者：星沐 (赞：2)

### 这道题我们可以用并查集来做。
#### 首先我们来了解一个STL容器——“map”；
[mk一个map解析](https://blog.csdn.net/ajianyingxiaoqinghan/article/details/78540736)
#### 不懂map的含义为一个映射的可以先看看。
![常用函数](https://cdn.luogu.com.cn/upload/pic/36816.png)
------------

#### 思路：并查集题目无非查询和合并，我们用map来存名字，   map<string,int> p,   相当于以string为下标， 值为int类型的一个映射。
#### 在后面输出名字的时候，判断p[string]中此名字是否存在，不存在的话就给存入map里，注意：存名字时按顺序一个一个赋，就是下面代码中的k++操作。
#### 注意每次合并的时候把朋友人数相加，num[fx]+=num[fy];


------------
### 代码如下：
```
#include<bits/stdc++.h>
using namespace std;
map<string,int> p;
#define N 200100
int fx,fy;
int fa[200100],num[200100];
inline int get(int x)//并查集的查询操作 
{
    if(fa[x]==x)return x;
    return fa[x]=get(fa[x]);
}
inline int read()//快读，不过多解释 
{
    int x=0,o=1;char ch=getchar();
    while(!isdigit(ch)&&ch!='-') ch=getchar();
    if(ch=='-') o=-1,ch=getchar();
    while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
    return x*o;
}
int main()
{
    int t,n;
    string s1,s2;
    t=read();
    while(t--)
    {
        int k=1;
        p.clear();
        n=read();
        for(int i=0;i<=n*2;i++)
        {
            num[i]=1;//每个人的朋友数为1； 
            fa[i]=i;
        }//初始化 
        for(int i=0;i<n;i++)
        {
            cin>>s1>>s2;
            if(p.find(s1)==p.end())
			p[s1]=k++;
            if(p.find(s2)==p.end())
			p[s2]=k++;//如果在map中没有找到此时输入的s1与s2就新存入map里； 
            fx=get(p[s1]);
            fy=get(p[s2]);
            if(fx!=fy)
            {
                fa[fy]=fx;//合并操作 
                num[fx]+=num[fy];//朋友数相加 
            }
            int ans=num[get(p[s2])];
            printf("%d\n",ans);//输出答案 
        }
    }
    return 0;
}
```

#### 谢谢。

---

## 作者：_qwerty_ (赞：2)

upd：更新码风、表述等。
## 翻译
####  from  [@青鸟_Blue_Bird](https://www.luogu.com.cn/user/234224)
### 题目内容
你的任务是观察在一个网站上人们之间的相互关系，并追踪每个人的社交网络的大小。假定每个友情是互相的。即，如果 Fred 是 Barney 的朋友，那么 Barney 也是 Fred 的朋友。

### 输入格式
第一行一个整数 $T$，代表数据组数。

对于每组数据，第一行有一个正整数（$1 \le F \le 10^5$），表示形成的友情的数量。

接下来的 $F$ 行，每行包含两个字符串，表示刚刚成为朋友的两个人的名字，用空格隔开。（名字长度不超过 $20$，包含大小写）。

### 输出格式

每当一对友情产生时，输出这两个人所属的社交网络的大小。

## 思路

1. 转化编号（用 `map` 或者 `unordered_map`），将名字转化为编号。
2. 使用[并查集](https://oi-wiki.org/ds/dsu/)记录元素之间的关系。用数组分别记录以毎个节点为祖先的家族的人数和节点之间的关系。
3. 每次查询都找到这个节点的祖先，查询人数。

## 注意事项

- 并查集数组要初始化！
- 合并两个集合时，将小集合连接到大集合中，以实现较优的复杂度。（其实纯路径压缩也能过）

## 代码
```cpp
#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
int f[maxn<<1],sum[maxn<<1];
int find(int x){
    if(x!=f[x])
        return f[x]=find(f[x]);
    return f[x]; 
}
void uni(int x,int y){
    x=find(x);
    y=find(y);
    if(x==y)	         // 如果本来就是一个集合里的，就不要重复计算
        return ;
    if(sum[x]<sum[y])    // 优化，合并两个集合时，将小集合连接到大集合中。
        swap(x,y);
    f[y]=x;
    sum[x]+=sum[y];
}
int t,n;
int cnt=1;              
unordered_map<string,int>mp;
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<(maxn<<1);i++){		//初
            f[i]=i;				        //始
            sum[i]=1;			        //化
        }

        for(int i=1;i<=n;i++){
            string a,b;
            cin>>a>>b;
            if(!mp[a])	
                mp[a]=cnt++;
            if(!mp[b])
                mp[b]=cnt++;
            uni(mp[a],mp[b]);
            cout<<sum[find(mp[a])]<<'\n';// sum[find(mp[b])]也行，毕竟它们是一家的
        }
    }
    return 0;
}
```

---

## 作者：Ferdina_zcjb (赞：1)

## 题目大意

有 $T$ 组数据和 $n$ 个关系，每个关系代表 $A$ 和 $B$ 是朋友关系（朋友的朋友也是朋友）。每次关系表时候，都要输出 $A$ 和 $B$ 所在朋友群中的人数。

## 题目解析

这道题其实就是一道并查集模版。处理关系只需要将 $A$ 的祖先与 $B$ 的祖先进行合并，并且人数也进行合并。

合并：

```cpp
int find(int x){//找父节点。
    if(fa[x] == x)return x;
    return fa[x] = find(fa[x]);
}
void bing(int x,int y){
    if(x == y)return ;
    else{
        fa[y] = x;
        ans[x] += ans[y];//合并人数。
        return ;
    }
}
```

$ans$ 数组在此处表示当前祖先节点所属的朋友集合的人数。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int ans[200001],fa[200001];
int find(int x){
    if(fa[x] == x)return x;
    return fa[x] = find(fa[x]);
}
void bing(int x,int y){
    if(x == y)return ;
    else{
        fa[y] = x;
        ans[x] += ans[y];
        return ;
    }
}
void nt(int n){//初始化。
    for(int i = 1;i <= n;++i){
        fa[i] = i;
        ans[i] = 1;
    }
}
signed main(){
    int T;
    cin >> T;
    while(T--){
        int flag = 0;
        map<string,int> mp;//由于是string类型，考虑使用STL的map。
        int n;
        cin >> n;
        nt(n*2);
        for(int i = 1;i <= n;++i){
            string s1,s2;
            cin >> s1 >> s2;
            if(mp.find(s1) == mp.end()){
                ++flag;
                mp[s1] = flag;
            }
            if(mp.find(s2) == mp.end()){
                ++flag;
                mp[s2] = flag;
            }//检查之前是否出现过s1和s2。
            int fx = find(mp[s1]),fy = find(mp[s2]);
            bing(fx,fy);//合并。
            fy = find(mp[s2]);
            cout << ans[fy] << endl;
        }
    }
}
```


---

## 作者：Max_s_xaM (赞：1)

# UVA11503 Virtual Friends

**基础并查集**

并查集模板题，处理名字可以用 STL map。注意有多组数据，需要初始化。$n$ 对朋友关系最多有 $2n$ 个人，初始化时将所有节点的父节点设为自己， $sum[x]$ 表示以 $x$ 为根节点的子数的节点数量，初始化为 $1$ 。

并查集合并时将节点数累加到新的父节点。查询节点数时返回根节点的 $sum$ 值。

### Code

```cpp
#include <iostream>
#include <string>
#include <map>
using namespace std;

int fa[200010], sum[200010];
// 并查集查询 
int Find(int x) {return fa[x] == x ? x : fa[x] = Find(fa[x]);}
// 并查集合并 
int Union(int x, int y)
{
	int u = Find(x), v = Find(y);
	if (u != v) fa[u] = v, sum[v] += sum[u];
	return sum[v];
}

int main()
{
	int t, n, tot;
	string a, b;
	cin >> t;
	while (t--)
	{
		cin >> n;
		// 初始化 
		tot = 0;
		for (int i = 1; i <= n << 1; i++) fa[i] = i, sum[i] = 1;
		map <string, int> m;
		
		while (n--)
		{
			cin >> a >> b;
			// 判断名字是否已经出现 
			if (!m[a]) m[a] = ++tot;
			if (!m[b]) m[b] = ++tot;
			cout << Union(m[a], m[b]) << endl;
		}
	}
	return 0;
}
```


---

## 作者：Zskioaert1106 (赞：0)

题目传送门：[UVA11503 Virtual Friends](https://www.luogu.com.cn/problem/UVA11503)

### 题意简述

大意是给你一堆人名，每次是两个人交上朋友，此时这两个人的交际圈合并（最初每个人的交际圈只有自己），你要输出每次这对朋友的交际圈大小。多测。

### 做题过程

看到合并朋友关系，考虑并查集。

发现本题并不要求记录交朋友的具体顺序，于是只要用并查集维护每个人所属的交际圈即可。

并查集可以保证同一圈内所有人的最终祖先都是同一个，因此我们更新这个人的交际圈大小并输出即可。

同时这题输入的是字符串，所以考虑哈希：可以用 map。

### 代码编写

由于我没有找到 $n$ 的范围，因此开了 $10^6$，同时注意每次是两个人名，因此初始化要 $2n$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[1000006],siz[1000006];
int find(int x){
    if(f[x]!=x)f[x]=find(f[x]);
    return f[x];
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        cin>>n;
        map<string,int>p;
        int I=1;
        for(int i=1;i<=(n<<1);i++)f[i]=i,siz[i]=1;//初始化
        while(n--){
            string a,b;
            cin>>a>>b;
            if(!p.count(a))p[a]=I++;
            if(!p.count(b))p[b]=I++;//哈希
            int x=find(p[a]),y=find(p[b]);//找祖先
            if(x!=y){//合并
                siz[x]+=siz[y];
                f[y]=x;
            }
            cout<<siz[x]<<'\n';
        }
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/210414398)。

---

