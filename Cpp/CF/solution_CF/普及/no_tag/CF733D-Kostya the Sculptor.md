# Kostya the Sculptor

## 题目描述

Kostya is a genial sculptor, he has an idea: to carve a marble sculpture in the shape of a sphere. Kostya has a friend Zahar who works at a career. Zahar knows about Kostya's idea and wants to present him a rectangular parallelepiped of marble from which he can carve the sphere.

Zahar has $ n $ stones which are rectangular parallelepipeds. The edges sizes of the $ i $ -th of them are $ a_{i} $ , $ b_{i} $ and $ c_{i} $ . He can take no more than two stones and present them to Kostya.

If Zahar takes two stones, he should glue them together on one of the faces in order to get a new piece of rectangular parallelepiped of marble. Thus, it is possible to glue a pair of stones together if and only if two faces on which they are glued together match as rectangles. In such gluing it is allowed to rotate and flip the stones in any way.

Help Zahar choose such a present so that Kostya can carve a sphere of the maximum possible volume and present it to Zahar.

## 说明/提示

In the first example we can connect the pairs of stones:

- $ 2 $ and $ 4 $ , the size of the parallelepiped: $ 3×2×5 $ , the radius of the inscribed sphere $ 1 $
- $ 2 $ and $ 5 $ , the size of the parallelepiped: $ 3×2×8 $ or $ 6×2×4 $ or $ 3×4×4 $ , the radius of the inscribed sphere $ 1 $ , or $ 1 $ , or $ 1.5 $ respectively.
- $ 2 $ and $ 6 $ , the size of the parallelepiped: $ 3×5×4 $ , the radius of the inscribed sphere $ 1.5 $
- $ 4 $ and $ 5 $ , the size of the parallelepiped: $ 3×2×5 $ , the radius of the inscribed sphere $ 1 $
- $ 5 $ and $ 6 $ , the size of the parallelepiped: $ 3×4×5 $ , the radius of the inscribed sphere $ 1.5 $

Or take only one stone:

- $ 1 $ the size of the parallelepiped: $ 5×5×5 $ , the radius of the inscribed sphere $ 2.5 $
- $ 2 $ the size of the parallelepiped: $ 3×2×4 $ , the radius of the inscribed sphere $ 1 $
- $ 3 $ the size of the parallelepiped: $ 1×4×1 $ , the radius of the inscribed sphere $ 0.5 $
- $ 4 $ the size of the parallelepiped: $ 2×1×3 $ , the radius of the inscribed sphere $ 0.5 $
- $ 5 $ the size of the parallelepiped: $ 3×2×4 $ , the radius of the inscribed sphere $ 1 $
- $ 6 $ the size of the parallelepiped: $ 3×3×4 $ , the radius of the inscribed sphere $ 1.5 $

It is most profitable to take only the first stone.

## 样例 #1

### 输入

```
6
5 5 5
3 2 4
1 4 1
2 1 3
3 2 4
3 3 4
```

### 输出

```
1
1
```

## 样例 #2

### 输入

```
7
10 7 8
5 10 3
4 2 6
5 5 5
10 2 8
4 2 1
7 7 7
```

### 输出

```
2
1 5
```

# 题解

## 作者：sto__Liyhzh__orz (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF733D)

map 练手题。

对于每个长方形，长宽高分别为 $a$，$b$，$c$，他的贡献就是 $\min(\min(a,b),c)$。

就可以用到一个非常非常~~阴间~~的 map 来维护每个 $a \times b$ 的面，它的 $c$ 和编号是多少。

最后取最大值，输出。

~~你们最喜欢的~~代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define LL long long  

int n,a[3],ans,flag1,flag2;
map<pair<int,int>,pair<int,int>>m;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
    	cin>>a[0]>>a[1]>>a[2];	
    	sort(a,a+3);
		int temp;
		pair<int,int>x;
		for(int j=0;j<=1;j++)
		{
			for(int k=j+1;k<=2;k++)
			{
				x=m[make_pair(a[j],a[k])];
				temp=min(min(a[j],a[k]),x.first+a[3-k-j]);
				if(temp>ans) ans=temp,flag1=i,flag2=x.second;
			}
		}
		for(int j=0;j<=1;j++)
		{
			for(int k=j+1;k<=2;k++)
			{
				x=m[make_pair(a[j],a[k])];
				if(a[3-j-k]>x.first)
				{
					x.first=a[3-j-k];
					x.second=i;
					m[make_pair(a[j],a[k])]=x;
				}
			}
		}
	}
	if(flag1 && flag2) cout<<2<<endl;
	else cout<<1<<endl;
	if(flag1) cout<<flag1<<" ";
	if(flag2) cout<<flag2<<" ";
	cout<<endl;
	return 0;
}
```

---

## 作者：CaiXY06 (赞：1)

设一个石块的长宽高分别为 $L,W,H$。

那么对于某一个石块它的贡献就是 $L,W,H$ 中的最小值。

我们考虑贪心，用一个非常~~阴间~~阳间的 **map**：

```cpp
map<pair<int,int>,pair<int,int> >mp;
```

来维护对于一个 $L\times W (L\leq W)$ 的面，能取到的最大的 $H$ 是什么，和其编号。

然后就可以愉快地取最大值啦，从而得到答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[3],ans,A,B;
map<pair<int,int>,pair<int,int> >mp;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&a[0],&a[1],&a[2]);
		sort(a,a+3);//保证L<=W,不然要维护两次不是么
		int temp;
		pair<int,int>f;
		
		f=mp[make_pair(a[0],a[1])];
		temp=min(min(a[0],a[1]),f.first+a[2]);
		if(temp>ans)ans=temp,A=i,B=f.second;
		
		f=mp[make_pair(a[0],a[2])];
		temp=min(min(a[0],a[2]),f.first+a[1]);
		if(temp>ans)ans=temp,A=i,B=f.second;
		
		f=mp[make_pair(a[1],a[2])];
		temp=min(min(a[1],a[2]),f.first+a[0]);
		if(temp>ans)ans=temp,A=i,B=f.second;
		//对于每一个面，计算它的贡献
		
		f=mp[make_pair(a[0],a[1])];
		if(a[2]>f.first){
			f.first=a[2];
			f.second=i;
			mp[make_pair(a[0],a[1])]=f;
		}
		
		f=mp[make_pair(a[0],a[2])];
		if(a[1]>f.first){
			f.first=a[1];
			f.second=i;
			mp[make_pair(a[0],a[2])]=f;
		}
		
		f=mp[make_pair(a[1],a[2])];
		if(a[0]>f.first){
			f.first=a[0];
			f.second=i;
			mp[make_pair(a[1],a[2])]=f;
		}
		//更新map 
	}
	if(A&&B)puts("2");
	else puts("1");
	if(A)printf("%d ",A);
	if(B)printf("%d ",B);
	return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

STL 大法好！

用一个长方体的判断十分简单，找最小的最大即可。

用两个长方体直接用 map 记录下不同面的所有可能性，然后取最大的两个拼接然后取最大。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 3e5 + 10;
int T,n;
int a[N],b[N],c[N];
map <pair <int,int>,vector <pair <int,int> > > Map;
map <pair <int,int>,int> vis; 
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
bool cmp (pair <int,int> a,pair <int,int> b){
	return a.first > b.first; 
}
void solve(){
	Map.clear();
	vis.clear();
	cin >> n;
	for (int i = 1 ; i <= n ; i++)
		cin >> a[i] >> b[i] >> c[i];
	for (int i = 1 ; i <= n ; i++){
		if (c[i] > b[i]) swap(c[i],b[i]);
		if (b[i] > a[i]) swap(a[i],b[i]);
		if (c[i] > b[i]) swap(b[i],c[i]); // 三个数排序
		//cout << a[i] << ' ' << b[i] << ' ' << c[i] << endl;
	}
	for (int i = 1 ; i <= n ; i++){
		Map[make_pair(a[i],b[i])].push_back(make_pair(c[i],i));
		if (b[i] != c[i]) Map[make_pair(a[i],c[i])].push_back(make_pair(b[i],i));
		if (a[i] != b[i] && b[i] != c[i]) Map[make_pair(b[i],c[i])].push_back(make_pair(a[i],i));
        // 记录
	}
	for (int i = 1 ; i <= n ; i++){
		if (!vis[make_pair(a[i],b[i])]) sort(Map[make_pair(a[i],b[i])].begin(),Map[make_pair(a[i],b[i])].end(),cmp);
		if (!vis[make_pair(a[i],c[i])]) sort(Map[make_pair(a[i],c[i])].begin(),Map[make_pair(a[i],c[i])].end(),cmp);
		if (!vis[make_pair(b[i],c[i])]) sort(Map[make_pair(b[i],c[i])].begin(),Map[make_pair(b[i],c[i])].end(),cmp);
		vis[make_pair(a[i],b[i])] = 1;
		vis[make_pair(a[i],c[i])] = 1;
		vis[make_pair(b[i],c[i])] = 1;
    // 对每一个不同的面进行排序，方便取最大和次大，也可以优化到 O(n)
	}
	int mx = 0;
	int k = 1,id1 = 1,id2 = 1;
	for (int i = 1 ; i <= n ; i++){
		if (c[i] > mx){
			mx = c[i];
			id1 = i;
		}
	}
	for (int i = 1 ; i <= n ; i++){
		if (Map[make_pair(a[i],b[i])].size() >= 2){
			int This = min(b[i],Map[make_pair(a[i],b[i])][0].first + Map[make_pair(a[i],b[i])][1].first);
			if (This > mx){
				k = 2;
				mx = This;
				id1 = Map[make_pair(a[i],b[i])][0].second;
				id2 = Map[make_pair(a[i],b[i])][1].second; 
			}
		}
		if (Map[make_pair(a[i],c[i])].size() >= 2){
			int This = min(c[i],Map[make_pair(a[i],c[i])][0].first + Map[make_pair(a[i],c[i])][1].first);
			if (This > mx){
				k = 2;
				mx = This;
				id1 = Map[make_pair(a[i],c[i])][0].second;
				id2 = Map[make_pair(a[i],c[i])][1].second; 
			}
		}
		if (Map[make_pair(b[i],c[i])].size() >= 2){
			int This = min(c[i],Map[make_pair(b[i],c[i])][0].first + Map[make_pair(b[i],c[i])][1].first);
			if (This > mx){
				k = 2;
				mx = This;
				id1 = Map[make_pair(b[i],c[i])][0].second;
				id2 = Map[make_pair(b[i],c[i])][1].second; 
			}
		}
    // 取最大值
	}
	cout << k << endl; 
	if (k == 1) cout << id1 << endl;
	else cout << id1 << ' ' << id2 << endl;
}
signed main(){
	close();
	T = 1;
	while (T--) solve();
	return 0;
}
```

---

## 作者：XL4453 (赞：0)


### 解题思路：

题目要求的其实是一个最短边最长的长方体，由于每一个单元长方体都最多只能和其他的一个长方体配对，哪么就可以将这个长方体拆成三面，每一面都放入一个 map 中，然后用后来的某一个长方体进行配对，并取最大值。

可以发现，假如两个有相同的一面的长方体的另一半长不等，那么较长的一个显然是严格优于较短的一个的，即假如较短的一个替换成较长的一个，那么答案一定不会更劣。根据这个规律，在进行操作的时候，可以直接将较小的一个答案顶替掉。

-------------
实现时，不妨将读入的 $a,b,c$ 降序，那么限制这个长方体继续扩大的限制条件一定是 $c$，那么也就不需要判断 $ac$ 面和 $bc$ 面是否能拼接了。

但是当作为拼接的另一半时长方体的三面都是有可能的，所以需要将三面都加入 map 中。

--------------
### 代码：

```cpp
#include<algorithm>
#include<cstdio>
#include<map>
using namespace std;
int n,a[100005],b[100005],c[100005],ans,ans1,ans2,x,y,z;
map <pair<int,int>,pair<int,int> > p;
pair <int,int> key;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&a[i],&b[i],&c[i]);
		x=max(max(a[i],b[i]),c[i]);
		z=min(min(a[i],b[i]),c[i]);
		y=a[i]+b[i]+c[i]-x-z;
		key.first=x;key.second=y;
		if(min(min(x,y),z+p[key].first)>ans){
			ans=min(min(x,y),z+p[key].first);
			ans2=i;ans1=p[key].second;
		}
		for(int j=1;j<=3;j++){
			swap(x,y);swap(y,z);
			key.first=x;key.second=y;
			if(p.count(key)){
				if(z>p[key].first){
					p[key].first=z;
					p[key].second=i;
				}
			}
			else{
				p[key]=make_pair(z,i);
			}
		}
	}
	if(ans1==0)printf("1\n%d",ans2);
	else printf("2\n%d %d",ans1,ans2);
	return 0;
}
```


---

## 作者：TNoName (赞：0)

刚拿到这个问题，第一反应：$n^2$暴力

看到n<$10^5$，哦豁不行。没有头绪，怎么办呢？

先考虑一下简单一点的问题吧：

1.不允许拼接：

这太简单了，取最小值的最大值即可

2.二维情形：

设矩形(a,b)，则用这个矩形可以做一个直径为$d=min\{a,b\}$的内切圆，记为$d \in S$.

设有矩形(a,b)和(b,c),拼接成(a+c,b).于是这时候我们可达成的内切圆直径多了一个选项:$min\{a+c,b\}$.

但是我们已经有$min\{a,b\} \in S$和$min\{b,c\} \in S$——也就是说如果$min\{a+c,b\}==min\{a,b\}$或者$min\{a+c,b\}==min\{b,c\}$,合了等于没合.那么什么时候**一定**会产生这种情况呢？注意到三个$min$中都含有$b$，且$a+c>a,a+c>a$，故得到当$b<a$或$b<c$时合并矩形不能提升答案.或者说，**仅当**$b>a$且$b>c$时合并矩形才是有意义的.

那么知道了这一点，我们就可以将矩形的长和宽进行升序排序，保证长$\leq$宽，然后只对宽相等的矩形进行合并尝试，比较两个矩形的长的和与矩形的宽，维护它们的最小值的最大值，并与不拼接的情况相比较即可得到答案。

回到三维情景，易知：仅当两个长方体相等的两边均不是最长边时，合并才有意义.故对输入的长宽高（单个长方体）做升序排序，再对高宽长（全部长方体）做排序，最后直接$O(n)$扫一遍判断相邻两个长方体能否合并并维护解即可.

码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int a[100005][3];
int idx[100005];
int rs[2];

bool cmp(int u,int v){
	if(a[u][2]==a[v][2]){
		if(a[u][1]==a[v][1]) return a[u][0]<a[v][0];
		return a[u][1]<a[v][1];
	}
	return a[u][2]<a[v][2];
}

int main(){
	scanf("%d",&n);
	int ans=0;
	for(int i=1;i<=n;i++){
		scanf("%d %d %d",a[i],a[i]+1,a[i]+2);
		sort(a[i],a[i]+3);
		if(ans<a[i][0]){
			ans=a[i][0];
			rs[0]=i;
		}
		idx[i]=i;
	}
	sort(idx+1,idx+n+1,cmp);
	for(int i=1;i<n;i++){
		if(a[idx[i]][1]!=a[idx[i+1]][1]||a[idx[i]][2]!=a[idx[i+1]][2]) continue;
		int t=a[idx[i]][0]+a[idx[i+1]][0];
		t=t<a[idx[i]][1]?t:a[idx[i]][1];
		t=t<a[idx[i]][2]?t:a[idx[i]][2];
		if(ans<t){
			ans=t;
			rs[0]=idx[i];
			rs[1]=idx[i+1];
		}
	}
	if(rs[1]) printf("2\n%d %d",rs[0],rs[1]); else printf("1\n%d",rs[0]);
	return 0;
}
```

[评测记录](https://www.luogu.com.cn/record/43612903)

---

## 作者：Yingluosanqian (赞：0)

惊喜，打开题解页面发现还没有题解， 本萌新终于有了提交题解的机会了。

先大致说一下题目：

``` txt
如果两个长方体有长和宽均相等的面，则它们可以拼接在一起。
求 使用一个长方体或使用两个长方体拼接成一个新的长方体 的最大内接球。
最终需要输出用到的长方体编号。
```

显然求一个长方体的最大内接球很简单，我们需要考虑的是求两个长方体拼接的情况。

由于**如果两个长方体有长和宽均相等的面，则它们可以拼接在一起。** 如果能够枚举所有能够拼接在一起的面，那么答案就可以求出。至于怎么找所有能够拼接在一起的面，我们使用C++的STL容器**map**。

定义如下：

``` cpp
map<pair<int,int>,pair<int,int> > Map;
//第一个pair表示一个面的长和宽
//第二个pair的first表示这个面所在的长方体的编号
//（因为答案要求输出，所以要保存信息）
//第二个pair的second表示这个面所在长方体的高
//（这样就可以计算拼接后的高了）
```

第一个问题，如何把长方体的一个面的信息存进去？
实现类似如下：

``` cpp
pair<int,int> Key1,Key2;
Key1.first=chang;Key1.second=kuan;
Key2.first=bianhao;Key2.second=gao;
Map[Key1]=Key2;
```

第二个问题：如何找到之前存进去的面？
实现类似如下：

``` cpp
pair<int,int> Key1,Key2;
Key1.first=chang;Key1.second=kuan;
if(Map.count(Key1)){
	Key2=Map[Key1];
}
```

第三个问题：算法流程是什么？

* 首先，依次读入所有a,b,c。
* 其次，对于每组a,b,c。作三次判断，分别判断ab面，bc面，ac面能接到什么面以及接上面后的内接球。
* 接着，更新。如果之前map中没有ab面，那就把ab面更新，如果之前map中的ab面的高小于这次ab面的高，那么更新数据，如果之前map中的ab面的高更大，那么不需要更新。

仔细思考，会发现这样的算法是正确的。有问题可以评论区留言。

完结。代码如下：

``` cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAXN=200050;

pair<int,int> Key1,Key2;
map<pair<int,int>,pair<int,int> > Map;

int n,e[3],ans=0,ans1=-1,ans2=-1;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",e+0,e+1,e+2);
		
		//单个
		sort(e,e+3);//这个sort是必要的
		if(e[0]>ans){
			ans=e[0];
			ans1=i;ans2=-1;
		}
		
		//两个 
		for(int mode=1;mode<=3;mode++){
			//e[0],e[1],e[2]轮换
			swap(e[0],e[1]);swap(e[1],e[2]);
			
			//操作 
			Key1.first=e[0];Key1.second=e[1];
			if(Map.count(Key1)){
				int MIN=min(min(e[0],e[1]),e[2]+Map[Key1].second);
				if(MIN>ans){
					ans=MIN;
					ans1=Map[Key1].first;ans2=i;
				}
				if(e[2]>Map[Key1].second){
					Key2.first=i;Key2.second=e[2];
					Map[Key1]=Key2;
				}
			}
			else{
				Key2.first=i;Key2.second=e[2];
				Map[Key1]=Key2;
			}	
		}
	}
	
	if(ans2==-1){
		printf("%d\n%d",1,ans1);
	}
	else{
		printf("%d\n%d %d",2,ans1,ans2);
	}
	
	return 0;
}
```

---

