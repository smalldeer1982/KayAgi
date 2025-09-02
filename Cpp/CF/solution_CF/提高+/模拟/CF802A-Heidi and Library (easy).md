# Heidi and Library (easy)

## 题目描述

Your search for Heidi is over – you finally found her at a library, dressed up as a human. In fact, she has spent so much time there that she now runs the place! Her job is to buy books and keep them at the library so that people can borrow and read them. There are $ n $ different books, numbered $ 1 $ through $ n $ .

We will look at the library's operation during $ n $ consecutive days. Heidi knows in advance that on the $ i $ -th day ( $ 1<=i<=n $ ) precisely one person will come to the library, request to borrow the book $ a_{i} $ , read it in a few hours, and return the book later on the same day.

Heidi desperately wants to please all her guests, so she will make sure to always have the book $ a_{i} $ available in the library on the $ i $ -th day. During the night before the $ i $ -th day, she has the option of going to the bookstore (which operates at nights to avoid competition with the library) and buying any book for the price of 1 CHF. Of course, if she already has a book at the library, she does not need to buy it again. Initially, the library contains no books.

There is a problem, though. The capacity of the library is $ k $ – this means that at any time, there can be at most $ k $ books at the library. If buying a new book would cause Heidi to have more than $ k $ books, she must first get rid of some book that she already has, in order to make room for the new book. If she later needs a book that she got rid of, she will need to buy that book again.

You are given $ k $ and the sequence of requests for books $ a_{1},a_{2},...,a_{n} $ . What is the minimum cost (in CHF) of buying new books to satisfy all the requests?

## 说明/提示

In the first test case, Heidi is able to keep all books forever. Therefore, she only needs to buy the book $ 1 $ before the first day and the book $ 2 $ before the second day.

In the second test case, she can only keep one book at a time. Therefore she will need to buy new books on the first, second and fourth day.

In the third test case, before buying book $ 3 $ on the third day, she must decide which of the books $ 1 $ and $ 2 $ she should get rid of. Of course, she should keep the book $ 1 $ , which will be requested on the fourth day.

## 样例 #1

### 输入

```
4 80
1 2 2 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 1
1 2 2 1
```

### 输出

```
3
```

## 样例 #3

### 输入

```
4 2
1 2 3 1
```

### 输出

```
3
```

# 题解

## 作者：_Warfarin_ (赞：5)

## 题目
[仙人指路](https://www.luogu.com.cn/problem/CF802A)

### 大意
一个背包，体积为 $k$，现在有 $n$ 件物品，$m$ 次查询。每次查询时，若被查寻物不在背包内，则将被查寻物加入背包，如若背包已满则和背包内任一物品替换，对于每次操作，代价为 $1$。求出最小代价。

### 思路
当需要交换时物品，将背包内紧急度，即距下次使用的距离，最远的物品进行交换。

#### 细节处理
 - 使用优先队列进行背包内存储。
 - 使用 `pair` 作为优先队列元素，优先队列默认按第一项排序。
 - 链式结构构建紧急度大小。

### AC 代码
```#include<bits/stdc++.h>

#define ll long long
#define io cin.tie(0),ios::sync_with_stdio(false)
//简单度读入优化
#define ri register int

using namespace std;
typedef pair<int,int> qwq ;
// first 紧急度
// second 物品种类
const int N =114514 ;
long long a[N],b[N],dis[N],_next[N],last[N];
bool vis[N];
priority_queue<qwq> q;
int main()
{
	io;
	int n,m;
	cin>>n>>m;
	ll ans=0,tmp=0;
	for(ri i=1; i<=n; i++)
	{
		cin>>b[i];
		a[i]=b[i];
	}
	sort(b+1,b+1+n);
//意义不是太大的离散化
	int tot=unique(b+1,b+n+1)-b-1;
	for(ri i=1; i<=n; i++)
	{
		a[i]=lower_bound(b+1,b+1+tot,a[i])-b;
//意义不是太大的离散化
		_next[last[a[i]]]=i;
		last[a[i]]=i;
		_next[i]=1e9;
	}
	for(ri i=1; i<=n; i++)
	{
		while(!q.empty()&&!vis[q.top().second])
			q.pop();
		if(!vis[a[i]])
		{
			ans++;
			vis[a[i]]=1;
			if(!q.empty()&&tmp>=m)
			{
				vis[q.top().second]=0;
				q.pop();
			}
			if(tmp<m)
			{
				tmp++;
			}
		}
		q.push({_next[i],a[i]});
	}
	cout<<ans<<endl;
	return 0;
}



```

---

## 作者：JiaY19 (赞：2)

一道三倍经验的题目。

[一倍](https://www.luogu.com.cn/problem/CF802A)，[二倍](https://www.luogu.com.cn/problem/CF802C)，[三倍](https://www.luogu.com.cn/problem/CF132E)。

至于[这个](https://www.luogu.com.cn/problem/CF802B)长得很相似，但网络流复杂度过不去。

#### 思路

考虑~~烂大街的~~费用流。

可以发现很难单独决定每天买不买，所以可以先把所有东西都买进来，再卖掉不必要的，抵消花费。

首先进行拆点 $i$ 与 $i'$ 之间连一条费用为 $0$ ，流量为 $1$ 的边。

从原点 $s$ ，连一条费用为 $c_{a_{i}}$ ，流量为 $1$ 的边。

再从每个 $i+1$ 向 $i$ 连一条流量为 $k - 1$ ，费用为 $0$ 的边。

从 $i-1$ 向 $a_i$ 上一次的出现位置 $j$ 对应的      $j'$ 连一条流量 $1$ ，费用为 $-c_{i}$ 的边。

最后从每个 $i'$ 向汇点 $t$ 连一条流量为 $1$ ，费用为 $0$ 的边。

代码实现直接套费用流板子就可以了。


#### Code

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf = 0x3f3f3f3f;
int n , k , tot , s , t , maxf , ans , head[5010] , d[5010] , in[5010] , pre[5010] , v[5010] , a[100] , c[100] , re[100];
struct E
{
	int to , nex , fei, liu;
}e[150100];

int read()
{
	long long X = 0 , w = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
		w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		X = X * 10 + c - '0' , c = getchar();
	return X * w;
}

void add(int x , int y , int z , int u)
{
	e[++tot].to = y , e[tot].liu = z , e[tot].fei = u , e[tot].nex = head[x] , head[x] = tot;
	e[++tot].to = x , e[tot].liu = 0 , e[tot].fei = -u , e[tot].nex = head[y] , head[y] = tot;
}

bool spfa()
{
	queue<int> q;
	memset(d , inf , sizeof(d));
	memset(v , 0 , sizeof(v));
	q.push(s); d[s] = 0; v[s] = 1;
	in[s] = 1 << 30;
	while(!q.empty()) 
	{
		int x = q.front(); v[x] = 0; q.pop();
		for(int i = head[x];i;i = e[i].nex)
		{
			if(!e[i].liu) continue;
			int y = e[i].to;
			if(d[y] > d[x] + e[i].fei)
			{
				d[y] = d[x] + e[i].fei;
				in[y] = min(in[x] , e[i].liu);
				pre[y] = i;
				if(!v[y]) v[y] = 1 , q.push(y);	
			} 
		}
	}
	if(d[t] == 4557430888798830399) return 0;
	return 1;
}

void update()
{
	while(spfa())
	{
		int x = t;
		maxf += in[t];
		ans += d[t] * in[t];
		int i;
		while(x != s)
		{
			i = pre[x];
			e[i].liu -= in[t];
			e[i ^ 1].liu += in[t];
			x = e[i ^ 1].to;
		} 
	}
}

signed main()
{
	n = read() , k = read() , s = 0 , t = 2 * n + 1;
	tot = 1;
	for(int i = 1;i <= n;++i) add(i , i + n , 1 , 0) , add(i + n , t , 1 , 0) , a[i] = read();
	for(int i = 1;i <= n;++i) c[i] = 1;
	for(int i = 1;i <= n;++i)
	{
		add(s , i , 1 , c[a[i]]);
		if(re[a[i]]) add(i - 1 , re[a[i]] + n , 1 , -c[a[i]]);
		re[a[i]] = i;
	}
	for(int i = 1;i < n;++i) add(i , i + 1 , k - 1 , 0);
	update();
	cout << ans;
	return 0;
}
```


---

## 作者：小杨小小杨 (赞：1)

## 题意
有 $n$ 个人要借书，每个人都要借第 $a_i$ 本书，但书店的库存只有 $m$，每一次满了之后都要扔掉一本书再购进一本。
## 思路
贪心。      

1. 如果当前这本书已经在书店里有了，就跳过。

2. 如果当前这本书没有，那么就
	1. 如果库存还没满，就直接买一本
   
   2. 如果库存满了，就丢掉下一次最晚用到的一本。
 
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,a[1001],f[1001],ma,tot,x[1001],j,h,ans;
vector<int> v[1001];
int main(){
	scanf("%d%d",&n,&m);
	for (i=1;i<=n;i++) scanf("%d",&a[i]),v[a[i]].push_back(i);//保存每一个数出现的位置
	for (i=1;i<=n;i++) v[i].push_back(2e9);//最后一本之后就没有出现了，优先处理
	for (i=1;i<=n;i++){
		x[a[i]]++;//这是当前这个数第几次出现
		if (f[a[i]]) continue;//如果已经有了，跳过
		else if (tot<m) tot++,f[a[i]]=1;//如果库存没满，直接购买
		else{
			ma=-1;h=1;//初始化
			for (j=1;j<=n;j++) if (f[j]&&v[j][x[j]]>ma) ma=v[j][x[j]],h=j;//取最晚出现的一本
			f[a[i]]=1;f[h]=0;//扔掉加购入
		}
		ans++;
	}
	printf("%d\n",ans);
    return 0;
}

```



---

## 作者：3_14 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF802A)

# 思路

整体是采用贪心来决定当图书馆容量已满，需要丢弃一本书为新购入的书腾出空间时，选择丢弃在未来最晚才会被再次请求的那本书。其直观的想法在于，通过这样的选择，能够让图书馆在后续应对借书请求时处于更有利的“状态”，尽可能减少后续因为丢弃了某本之后很快又需要用到的书而导致再次购买的情况，从而达到最小化买书成本的目的。

~~具体思路在代码里面（自己看）。~~

总的来说，整体思路是通过贪心结合上述具体的按天、按书查找等步骤实现，不过按照所描述的这种简单实现方式，由于存在多层嵌套循环遍历（最外层按天 $n$ 次，中间层按图书馆现有书最多 $k$ 次，内层按后续天数最多 $n$ 次），所以时间复杂度达到了 $O(n^3)$，但对于题目给定的数据范围（$n$ 和 $k$ 都较小，均不超过 $80$），这样的复杂度是可以的。


# 代码


```cpp
#include<bits/stdc++.h>
#define lcm(x,y) x/__gcd(x,y)*y;
#define str to_string
using namespace std;
using ll=long long;
const int MAX=1e5+1;
const double EPS=1e-6;
int n,k;
int main(){
    cin>>n>>k;
    vector<int>requests(n);
    for(int i=0;i<n;i++)cin>>requests[i];
    set<int>library;// 用set来存储图书馆当前拥有的书籍
    int cost=0;
    for(int i=0;i<n;i++){
        int book=requests[i];
        if(library.find(book)==library.end()){// 如果图书馆没有这本书
            if(library.size()==k){// 图书馆已满
                int latestNextUseBook=-1,latestNextUseDay=-1;
                // 遍历图书馆现有的每一本书，找未来最晚再被使用的书
                for(int b:library){
                    int nextUseDay=n;
                    for(int j=i+1;j<n;j++){
                        if(requests[j]==b){
                            nextUseDay=j;
                            break;
                        }
                    }
                    if(nextUseDay>latestNextUseDay){
                        latestNextUseBook=b;
                        latestNextUseDay=nextUseDay;
                    }
                }
                library.erase(latestNextUseBook);// 移除最晚再被使用的书
            }
            library.insert(book);
            cost++;
        }
    }
    cout<<cost<<'\n';
    return 0;
}
```

## [AC记录](https://codeforces.com/problemset/submission/802/298058347)

---

## 作者：fish_love_cat (赞：0)

简单贪心，然后忘记修改维护的信息调了一个小时 /qd

---

我们容易发现当架子满了的时候要扔书时，扔下一次使用最晚的书是不劣的。

为什么呢？

如果我们扔的不是这本最晚用到的书，那么在下一次用到它之前，我们除了现在买一次书外，扔掉的另一本下一次还得再买。这样算下来就多买了一次甚至更多，是不优的。

那么我们就应该扔最晚用的书。

考虑倒序统计下一次使用，然后利用优先队列处理。

注意如果当前需要的书已经在架上，需要更新优先队列中该书下一次的值（不然挂在第 $9$ 个点）。我们可以多加一本书覆盖原书来实现。

---

[代码](https://www.luogu.com.cn/paste/67z0e4eb)。

---

福利：

[六](https://www.luogu.com.cn/problem/P3419)[倍](https://www.luogu.com.cn/problem/P2088)[经](https://www.luogu.com.cn/problem/SP688)[验](https://www.luogu.com.cn/problem/CF802B)，[好](https://www.luogu.com.cn/problem/P4404)[耶](https://www.luogu.com.cn/problem/CF802A)！

甚至双倍[题](https://www.luogu.com.cn/article/tgf82p31)[解](https://www.luogu.com.cn/article/hga39xyp)！

---

## 作者：liuyifan (赞：0)

## 比较简单的贪心

思路:如果图书馆内已经有了就不用管了

如果还可以继续买就直接操作

否则舍弃最前面的就行了

注意hash操作的初始化~~(本人因此毒瘤1h)~~

code:
```cpp
#include<bits/stdc++.h>//万能头文件
#define reg register
#define ll long long
#define inf 0x3f3f3f3f
#define iinf 0x3f3f3f3f3f3f3f3fll//注意后缀ll,不加可能会死得惨烈
using namespace std;
ll a[1005],e[1005],n,k,cnt,maxx,maxxx,ans;//不开long long见祖宗
map<ll,bool>x;//map作为桶,常用用法
int main()
{
    scanf("%lld%lld",&n,&k);
    for(reg int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(reg int i=1;i<=n;i++)
    {
        maxx=0;
        maxxx=-1;//注意数据在每次循环中的初始化
        if(x[a[i]])continue;//桶中已经有了,直接跳过
        if(cnt<k)
        {
            cnt++;
            x[a[i]]=true;//map资瓷直接赋值运算,方便快捷
            ans++;
        }
        else
        {
            memset(e,0,sizeof e);//hash数组记得初始化
            for(reg int j=1;j<=n;j++)
            if(x[j])e[j]=100;//因为kmax=80，所以我们这时取100就可以了
            for(reg int j=1;j<=n;j++)
            if(x[j])//如果桶中有
            {
                for(reg int k=i+1;k<=n;k++)
                if(a[k]==j)
                {
                    e[j]=k;
                    break;
                }//直接hash处理
            }
            for(reg int j=1;j<=n;j++)
            if(e[j]>maxx)
            {
                maxx=e[j];
                maxxx=j;
            }//统计两个最大值
            x[maxxx]=0;
            x[a[i]]=1;//在本次循环结束之后要还原处理
            ans++;
        }
    }
    printf("%lld",ans);//输出最终答案
    return 0;
}
```


---

## 作者：lg_zhou (赞：0)

比较简单的贪心，如果图书馆内已经有了就不用管了

如果还可以继续买就直接操作

否则舍弃最前面的就行了。直接上代码
```cpp
#include <cstdio>
int a[81];
bool used[81];
int e[81];
int main()
{
    int n,k,cnt,maxx,maxi,ans=0;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    cnt=0;
    for(int i=1;i<=n;i++){
        if(used[a[i]])
            continue;
        if(cnt<k){
            cnt++;
            used[a[i]]=true;
            ans++;
        }
        else{
            for(int j=1;j<=n;j++)
                e[j]=0;
            for(int j=1;j<=n;j++)
                if(used[j])
                    e[j]=100;
            for(int j=1;j<=n;j++)
                if(used[j]) {
                    for(int k=i+1;k<=n;k++)
                        if(a[k]==j){
                            e[j]=k;
                            break;
                        }
                }
            maxx=0;
            maxi=-1;
            for(int j=1;j<=n;j++)
                if(e[j]>maxx){
                    maxx=e[j];
                    maxi=j;
                }
            used[maxi]=false;
            used[a[i]]=true;
            ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
```


---

