# [POI 2011] PAT-Sticks

## 题目描述

小 Johnny 收到了祖父母送的生日礼物。

这个礼物是一盒各种长度和颜色的木棍。

Johnny 想知道，他收到的这些木棍中是否存在三根木棍，能够组成一个边长颜色各不相同的三角形。

需要注意的是，Johnny 只对非退化三角形感兴趣，即面积为正的三角形。

## 样例 #1

### 输入

```
4
1 42
2 6 9
3 8 4 8
1 12```

### 输出

```
3 8 4 12 2 9```

# 题解

## 作者：曹老师 (赞：4)

## Pro ##

[Luogu3528][1]


## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/poi2011-patsticks.html)

1.贪心题。

我们把边从小到大排序，然后依次的取出每一条边，维护三条边的颜色及长度。枚举的过程中，如果发现相同颜色的已经在维护中了，就更新该条边的长度，因为越往后边的长度越长，这条边只有更长才有更大的机会构成三角形。还有呢就是如果你维护的三条边当中没有新的这条边的颜色，就用新的这条边去更新你维护的当中最短的那个，这样有更多的机会去构成三角形。

2.二分查找（思路）。

是一个很暴力的方法，不过貌似有福利：大量的剪枝。枚举两个颜色，再分别枚举其中的两条边，从而能确定第三条能构成三角形的长度范围，再枚举第三种颜色，通过二分查找左右端点和判断是否相等来确定是否存在答案。剪枝的时候，还要维护最大值最小值，可以是前i行当中最长(短)的边，也可以是第i行之后的所有的边当中最长(短)的边，剪枝的话需要一定的数学能力（然而我没剪出来，这里只留做思路）

进一步的优化：设maxx[i]为第i种颜色到第k的所有颜色当中，木棍的最大值，同理minn为最小值。对于第i种颜色，能满足的区间最大为[maxx[i+1]-minn[i+1] ， 2 * maxx[i+1] ] ，因此我们就可以两个二分求出左右端点，然后枚举每一根木棍，对于第二条同样的道理，也用二分查出区间，然后枚举。我们可以看出，对于每一种颜色来说，它枚举的区间都是固定的，因此我们可以在处理maxx 和 minn的过程中求出区间的范围，预处理出来。对于枚举的第三条边，它的区间是由另外两条边决定的，因此我们不能提前预处理出来。还有一个很小的剪枝就是，我们也可以提前一起预处理出来第三条边的区间，在这个区间上二分，而不是在第三种颜色的整个区间上二分，但这个复杂度外面套了一个log，可能不会优化太多。


## 贪心Code ##
```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

struct node {
	int len , color;
	bool operator < (const node &a) const {
			return len < a.len;
	}
};
node g[1000010] , ans[5];
int n , top = 0;

int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++) {
		int x;
		scanf("%d",&x);
		for(int j=1; j<=x; j++) {
			scanf("%d",&g[++top].len);
			g[top].color = i;			
		}
	}
	sort(g+1 , g+top+1);
	for(int i=1; i<=3; i++)
		ans[i].color = ans[i].len = 0;
	for(int i=1; i<=top; i++) {
		bool flag = false;
		for(int j=1; j<=3; j++)
			if(g[i].color == ans[j].color) {
				ans[j].len = g[i].len;
				flag = true;
			}
		if(flag == false)
			ans[1] = g[i];
		sort(ans+1 , ans+4);
		if(ans[1].len + ans[2].len > ans[3].len) {
			for(int j=1; j<=3; j++)
				printf("%d %d ",ans[j].color,ans[j].len);
			return 0;			
		}
	}
	printf("NIE\n");
	return 0;
}
```


  [1]: https://www.luogu.org/problemnew/show/P3528
  [2]: https://www.lydsy.com/JudgeOnline/problem.php?id=2529

---

## 作者：zhaozixu2006 (赞：3)

## 题目描述：[戳这里](https://www.luogu.com.cn/problem/P3528)

## 题目大意：

1. 给你 $k$ 种颜色的木棍，每种木棍颜色不一样。

2. 找出三根颜色不一样的木棍组成三角形。

3. 如果可以输出方案，不能输出 "NIE"。

## 思路：

遇事不决先看数据范围。

最多有 $50$ 种颜色，而有 $10^6$ 的木棍。

#### zhx 曾经说过如果题目中出现奇怪的数据范围要着重思考。

于是这个颜色的个数就很可疑。

下面从颜色开始入手。

如果不考虑不同种颜色，那么按长度排序，如果有解的话，那么一定有一组解，三根木棍是连续的，且长度是相近的，直接找相邻的三根木棍判断是否能构成三角形即可。

那么如果考虑同种颜色，只需要对于每种颜色开一个大根堆。

把每种颜色的木棍丢进去。

单独开一个大根堆，把每种颜色长度最大的木棍丢进去。


1. 每次取出最长的三根木棍

2. 如果可以组成则输出。

3.  如果当前的三根不能组成三角形则把最长的一根丢掉，因为不可能有其他的组合和它构成三角形，把剩下的两根丢回堆中。

4. 看看与之前那个最长的相同颜色的堆中还有没有其他的，如果有就丢入新的堆中。

5. 重复上面步骤，直至新的堆中元素不能构成三角形，输出无解。

具体细节看代码。

### 下面是贴心的代码。

```cpp
/*

　　　　　／＞　   フ
　　　　　| 　_　 _|
　 　　　／`ミ _x 彡
　　 　 /　　　 　 |
　　　 /　  ヽ　　 ?
　／￣|　　 |　|　|
　| (￣ヽ＿_ヽ_)_)
　＼二つ

*/
#include<bits/stdc++.h>
using namespace std;

struct node{
	int col,len;//颜色，长度 
	bool operator < (const node &T) const {
    return len < T.len;
}
};


priority_queue<node> q[55];
priority_queue<node> a;//单独开的大根堆，保证里面的木棍颜色不一样 

long long read()
{
	long long x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0'; ch = getchar();}
	return x * f;
}

int n;

bool check(node a, node b, node c)//判断是否能构成三角形 
{
	if(a.len + b.len > c.len && a.len - b.len < c.len) return true;
	else return false;
}

int main()
{
	n = read();
	for(int i = 1; i <= n; i++)
	{
		int x = read();
		for(int j = 1; j <= x; j++)
		{
			int y = read();
			q[i].push((node){i, y});
		}
	}
	
	//根据思路大模拟 
	 
	for(int i = 1; i <= n; i++) 
	{
		if(!q[i].empty())
		{
			a.push(q[i].top());	
			q[i].pop();
		}
	}

	//找最长的三根 

	while(!a.empty())
	{
		node x = a.top();//取出三根 
		a.pop();
		node y = a.top();
		a.pop();
		node z = a.top();
		a.pop();
		if(check(x, y, z))//能构成三角形 
		{
			cout << x.col << " " << x.len << " ";
			cout << y.col << " " << y.len << " ";
			cout << z.col << " " << z.len;
			return 0;
		}
		else//不能构成三角形 
		{
			a.push(y); 
			a.push(z);
			if(!q[x.col].empty())
			{
				a.push(q[x.col].top());
				q[x.col].pop();
			}
		}
		if(a.size() < 3)//如果小于三根则不能构成三角形 
		{
			cout << "NIE" << endl;
			return 0;
		}
	}
	
	return 0;
}

```

### 小结：

事出反常必有妖，一定要关注奇怪的数据范围进而抓住题目的重点。


---

## 作者：zhujingy (赞：2)

# [传送门](https://www.luogu.com.cn/problem/P3528)
参考了钟浩曦的讲解，但对于证明的地方可能更加详细。
## 题目意思：
给出每根木棍的颜色和长度，问你是否能找到三根颜色不同的木棍组成三角形。如果可以，输出任意一种方案，否则输出 "NIE"。
## 思路：
首先我们要知道一个数据结构：
### 堆
>堆是一棵树，其每个节点都有一个键值，且每个节点的键值都大于等于或小于等于其父亲的键值。每个节点的键值都大于等于其父亲键值的堆叫做小根堆，否则叫做大根堆。

以上来自 [OIWIKI](https://oi.wiki/ds/heap/)。

堆是一种支持插入、查询最值、删除最值、合并的数据结构。
- 大根堆

主要用来查询最大的元素，删除最大元素。

STL 中的优先队列（priority_queue）实际上就是一个大根堆。

下面是大根堆的几种操作：

```cpp
#include<queue>

priority_queue<int>heap;

int main()
{
	heap.push(x); //插入元素
	heap.empty(); //判断是否为空 
	heap.top(); //访问堆顶元素
	heap.size(); //查询元素数量
	heap.pop(); //删除堆顶元素 
}
```
- 小根堆

主要用来查询最小元素，删除最小元素。

这里提供一种用 priority_queue 实现小根堆的方法：

我们只要在插入和查询最值的时候**取相反数**就行了，其他与大根堆相同。

当然，使用 greater<int>、重载运算符都是可以的。
### 假设所有木棍的颜色都不一样
维护一个大根堆，将所有木棍的长度扔进堆里，每次取堆中第一个、第二个和第三个元素，如果他们不能组成三角形，那么**就没有木棍能与第一根组成三角形**，可以将堆顶丢掉。
> 证明：
因为这种情况下保证了堆里所有元素的颜色不同，所以我们只需要考虑木棍的长度。设上面选出的三个木棍的长度分别为 $a$，$b$，$c$（$a \ge b \ge c$）。他们要组成三角形的条件是：$a < b + c$。如果不满足，说明 $a \ge b + c$。又因为大根堆中保证了元素是不上升的，接下来选择的 $b$ 和 $c$ 一定小于等于原来的 $b$ 和 $c$，绝对不会再满足条件，此时将 $a$（堆顶）丢掉即可。
### 考虑正解
在上一种情况中，我们发现：只要堆中没有颜色相同的木棍，那么上一种方法就可行。那么我们可以：

**对于每一种颜色，建一个大根堆**；

**每次只取每个大根堆中的堆顶元素放入总的大根堆**；

**每次将总的大根堆的堆顶扔掉时，再向堆里扔一个同颜色的堆的堆顶**；（这样保证同一时刻的堆中没有颜色相同的木棍）

直到找到一组解。
## 代码：
要注意的点都写在代码里了。
```cpp
#include<bits/stdc++.h>

using namespace std;

int k,n;
int len;

priority_queue<int>Heap[55];
 //Heap[i]中存储颜色为 i 的木棍长度 
priority_queue<pair<int,int> >heap;
 //pair 的 first 存储 木棍的长度，pair 的 second 存储木棍的颜色 

int main()
{
	scanf("%d",&k);
	for(int i = 1;i <= k;i ++)
	{
		scanf("%d",&n);
		for(int j = 1;j <= n;j ++)
		{
			scanf("%d",&len);
			Heap[i].push(len);
		}
	}
	for(int i = 1;i <= k;i ++)
	 //先把每种颜色的木棍中最长的放入总的堆中 
	{
		if(! Heap[i].empty())
		{
			int lens = Heap[i].top();
			heap.push({lens,i});
			Heap[i].pop();
		}
	}
	while(heap.size() >= 3) //开始查找 (注意，这里的条件是堆中木棍数量 >= 3 )
	{
		int a = heap.top().first,a_i = heap.top().second;
		heap.pop();
		int b = heap.top().first,b_i = heap.top().second;
		heap.pop();
		int c = heap.top().first,c_i = heap.top().second;
		if(a < b + c){
			printf("%d %d %d %d %d %d",a_i,a,b_i,b,c_i,c);
			return 0;//找到了一组合法解，结束 
		}
		heap.push({b,b_i});
		if(! Heap[a_i].empty())
		{
			int lens = Heap[a_i].top();
			heap.push({lens,a_i});
			Heap[a_i].pop();
		}
	}
	printf("NIE");
	return 0;
}
```

---

## 作者：lfxxx (赞：1)

首先考虑怎么判断一个集合中所有数是否能找出一组三角形。

考虑三角形三条边越接近越有可能构成三角形，所以我们将这个集合排序后去检查相邻的三条边，即枚举一条边，剩下两条边就钦定为前驱后继。

现在你考虑怎么处理颜色限制，首先把边按照颜色分类，然后对于当前枚举的边 $x$ 你需要在其他颜色的边集中找出前驱后继，考虑把所有边集排序后通过双指针的方式找出前驱后继然后记录最大次大合并信息即可。

时间复杂度是 $O(nk + n \log n)$ 的。

```cpp
/*
首先我们当颜色不存在
那么能够构成三角形的话在按照长度排序后一定是相邻的
现在考虑枚举每一种颜色的每一根木棍，并且在其他颜色的木棍集合中维护一个双指针找前驱后继
时间复杂度 O(nk + n \log n)
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+114;
int k;
vector<int> col[maxn];
int t1[maxn],t2[maxn];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>k;
    for(int i=1;i<=k;i++){
        int n;
        cin>>n;
        for(int j=1;j<=n;j++){
            int x;
            cin>>x;
            col[i].push_back(x);
        }
        sort(col[i].begin(),col[i].end());
    }
    for(int i=1;i<=k;i++){
        for(int j=1;j<=k;j++) t1[j]=-1,t2[j]=0;
        for(int j=0;j<col[i].size();j++){
            for(int p=1;p<=k;p++){
                while(col[p][t1[p]+1]<=col[i][j]&&t1[p]<(int)(col[p].size()-1)) t1[p]++;
                while(col[p][t2[p]]<col[i][j]&&t2[p]<(int)(col[p].size()-1)) t2[p]++;       
            }
            int mx1=0,mx2=0,cmx1=0,cmx2=0;
            int mi1=1e9+7,mi2=1e9+7,cmi1=0,cmi2=0;
            for(int p=1;p<=k;p++){
                if(p==i) continue;
                if(t1[p]!=-1&&col[p][t1[p]]<=col[i][j]){
                    if(col[p][t1[p]]>=mx2) mx2=col[p][t1[p]],cmx2=p;
                    if(mx2>=mx1){
                        swap(mx1,mx2);
                        swap(cmx1,cmx2);
                    }
                }
                if(col[p][t2[p]]>=col[i][j]){
                    if(col[p][t2[p]]<=mi2) mi2=col[p][t2[p]],cmi2=p;
                    if(mi2<=mi1){
                        swap(mi1,mi2);
                        swap(cmi1,cmi2);
                    } 
                }
            }
            if(cmx1!=cmi1&&cmx1!=0&&cmi1!=0&&mx1<mi1){
                if(mi1-mx1<col[i][j]&&mx1+mi1>col[i][j]){
                    cout<<i<<' '<<col[i][j]<<' '<<cmx1<<' '<<mx1<<' '<<cmi1<<' '<<mi1<<'\n';
                    return 0;
                }
            }
            else{
                if(mi1-mx2<col[i][j]&&mx2+mi1>col[i][j]&&cmx2!=0&&cmi1!=0&&mx2<mi1){
                    cout<<i<<' '<<col[i][j]<<' '<<cmx2<<' '<<mx2<<' '<<cmi1<<' '<<mi1<<'\n';
                    return 0;
                }
                if(mi2-mx1<col[i][j]&&mx1+mi2>col[i][j]&&cmx1!=0&&cmi2!=0&&mx1<mi2){
                    cout<<i<<' '<<col[i][j]<<' '<<cmx1<<' '<<mx1<<' '<<cmi2<<' '<<mi2<<'\n';
                    return 0;
                }
            }
        }
    }
    cout<<"NIE\n";
    return 0;
}
```


---

## 作者：老官童鞋gogo (赞：1)

## 前言

1. 前往[我的博客](https://www.laoguantx.top)（可能正在备案）获得更好的阅读体验。

2. 这篇题解的讲者为：钟皓曦，我只是将钟老师的讲解整理并复述一遍。

## 启发

我们从简单的问题开始，假设所有的木棍颜色都是不同的，也就是说我们可以选择任意木棍来尝试着组成三角形。

> zhx：
>
> 如果题目中给出的数据顺序变换不会影响最终结果的话，就去考虑对数据进行排序。

排序，设我们要找出的三根木棒的长度为 $a,b,c(a>b>c)$ ，因为 $a,b,c$ 的可以构成一个三角形，所以应该满足以下条件：

$$a>b>a-c$$

所以存在一种方法：分别查找 $a$ 和 $a-c$ 的位置，在这两个位置中间，是否可以加入 $b$ 这个数，如果有，则存在构成三角形的方法。

如何避免查找呢？那就是选择排序后三根连续的木棒进行判断，当确定 $a$ 的时候，我们去寻找尽可能小的 $a-c$ ，也就是寻找尽可能大的 $c$ ，又要去寻找尽可能大但是又不超过 $a$ 的 $b$ ，所以连续的三根木棒是极端情况最优解，所以面对所有木棍颜色都不同的情况下，从头枚举三根木棍即可得到答案，时间复杂度 $O(n)$ 。

## 问题解决

根据启发，我们知道，选择长度相近的三根木棒是最有肯能得到解决方案的，那么面对存在颜色相同的木棒应该如何处理？

仍然是排序，每种颜色的木棒分别排序，每次选择颜色不同的、长度最相近的三根木棒逐个判断也可以得到答案。

思路已有，如何实现？

因为我们要不断获得不同颜色木棒的长度的最长值（考虑从长到短寻找），所以使用大根堆来维护，并单独建立起一个大根堆，这个单独的大根堆中存储着当前还未排除的不同颜色的最长的木棍，每次选择最长的三根木棍进行比较，能构成三角形则输出，否则将单独建立的大根堆堆顶的木棍弹出，说明其不能和其他木棍构成符合要求三角形。被弹出的木棍属于哪种颜色，就将哪种颜色剩下木棍中最长的加入单独建立的大根堆，直到该颜色没有木棍可用，这样保证了单独建立的大根堆内所有的木棍颜色不同，并包含所有可用颜色的木棍。最终如果没有三根木棍来组成三角形，说明结果不存在。

# 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
struct Node{
	int len,col;
}temp[4];
bool operator <(const Node &a,const Node &b){
	return a.len<b.len;
}
priority_queue<Node> h[50];
priority_queue<Node> q; 
int n,col[55][1000010];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&col[i][0]);
		for(int j=1;j<=col[i][0];j++){
			scanf("%d",&col[i][j]);
			h[i].push({col[i][j],i});
		}
	}
	for(int i=1;i<=n;i++){
		q.push(h[i].top());
		h[i].pop();
	}
	while(q.size()>=3){
		for(int i=1;i<=3;i++){
			temp[i]=q.top();
			q.pop();
		}
		if(temp[1].len-temp[2].len<temp[3].len){
			printf("%d %d %d %d %d %d",temp[1].col,temp[1].len,temp[2].col,temp[2].len,temp[3].col,temp[3].len);
			return 0;
		}
		if(h[temp[1].col].size()){
			q.push(h[temp[1].col].top());
			h[temp[1].col].pop();
		}
		q.push(temp[2]);
		q.push(temp[3]);
	}
	printf("NIE");
	return 0;
}
```



---

## 作者：Vatyr (赞：1)

很容易理解的一点就是，如果有解的话，那么一定有一组解，三根木棍是“连续的”。所以我们只要排一遍序，然后维护连续的三根木棍就好了。具体说来就是维护三根颜色不同且长度最长的木棍。一些细节请见代码。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct dou{
    int col,len;
}a[1000006];
inline bool cmp(dou x,dou y)
{
    if(x.len==y.len)return x.col<y.col;
    return x.len<y.len;
}
int n;
int tot;
int ans[10];
int vis[100];
int t;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int m;
        scanf("%d",&m);
        for(int j=1;j<=m;j++)
        {
            tot++;
            a[tot].col=i;
            scanf("%d",&a[tot].len);
        } 
    }
    sort(a+1,a+1+tot,cmp);//从小到大排序
    for(int i=1;i<=tot;i++)
    {
        int col=a[i].col;
        int len=a[i].len;
        if(vis[col]==0)//如果没选完三根就把没用过的颜色选上
        {
            t++;
            vis[col]=t;
            ans[t]=i;
            if(t==3)
                if(a[ans[3]].len>=a[ans[2]].len+a[ans[1]].len)//当选满三根木棍时
                {                                                                 
                    vis[a[ans[1]].col]=0;//判断是否合法，合法则退出循环
                    ans[1]=ans[2];//否则弹掉最小的那根，继续找
                    ans[2]=ans[3];
                    vis[a[ans[1]].col]=1;
                    vis[a[ans[2]].col]=2;
                    t=2;
                }
                else break;
        }
        else//如果当前颜色已经被选中的话则将其替换为当前木棍
            if(t==1)ans[1]=i;//以维护最长的三根木棍
            else 
                if(t==2)
                    if(vis[col]==1)
                    {
                        ans[1]=ans[2];
                        ans[2]=i;
                        vis[a[ans[1]].col]=1;
                        vis[a[ans[2]].col]=2;
                    }
                    else 
                        if(vis[col]==2)
                            ans[2]=i;
    }
    if(t!=3)
    {
        printf("NIE");
        return 0;
    }
    for(int i=1;i<=3;i++)
        printf("%d %d ",a[ans[i]].col,a[ans[i]].len);
    return 0;
} 
```
代码丑陋望谅解qwq，还有要注意当木棍调整时记得调整对应的颜色，在这上面WA了好几遍= =


---

## 作者：NinT_W (赞：0)

# [POI2011]PAT-Sticks

## 杂项

[传送门](https://www.luogu.com.cn/problem/P3528)

## 思路

数据结构题（也是贪心），首先考虑颜色全都不同的操作，那么我们可以从大到小进行排序，然后每次找到三个相邻的数，判断能不能构成三角形即可。

那么如果有好多种颜色，那么我们可以将每个颜色都搞一个大根堆，然后再搞一个最终存答案的大根堆 $PQ$ ，每次可以选所有颜色里最长的那根（堆顶） push 进 $PQ$ ，然后每次取出三个最长的，如果符合直接输出，否则将最长的那根彻底放弃，再选一根同样颜色的最长棍 push 进 $PQ$ 来，这样就可以保证颜色互不相同，问题就转化为了所有颜色都不同的情况。

AC code
```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstdlib>
#define pii pair<int,int>

using namespace std;

const int maxn=1e6+5;

inline int read()
{
	int w=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
	{
		w=(w<<3)+(w<<1)+(ch^48);
		ch=getchar();
	}
	return w*f;
}

struct node
{
	int col,len;
};

priority_queue <int> q[55];

priority_queue <pii> q_ans;

int k;

int main()
{
	k=read();
	
	for(int i=1;i<=k;i++)
	{
		int n=read();
		for(int j=1;j<=n;j++)
		{
			int len=read();
			q[i].push(len);
		}
	}

	for(int i=1;i<=k;i++)
	{
		if(!q[i].empty())
		{
			int val=q[i].top();
			q[i].pop();
			q_ans.push(make_pair(val,i));
		}
	}

	while(q_ans.size()>=3)
	{
		pair<int,int> a=q_ans.top(); q_ans.pop();
		pair<int,int> b=q_ans.top(); q_ans.pop();
		pair<int,int> c=q_ans.top(); q_ans.pop();
		
		if(c.first>a.first-b.first)
		{
			cout<<a.second<<" "<<a.first<<" ";
			cout<<b.second<<" "<<b.first<<" ";
			cout<<c.second<<" "<<c.first<<" ";
			exit(0);
		}
		else
		{
			q_ans.push(make_pair(b.first,b.second));
			q_ans.push(make_pair(c.first,c.second));
			
			if(!q[a.second].empty())
			{
				int k=q[a.second].top();
				q[a.second].pop();
				q_ans.push(make_pair(k,a.second));
			}
		}
	}
	
	cout<<"NIE";
	
	return 0;
}
```


---

