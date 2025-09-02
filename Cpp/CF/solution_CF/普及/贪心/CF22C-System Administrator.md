# System Administrator

## 题目描述

给定 $n$ 个顶点，可以在这些顶点之间连接 $m$ 条双向边，要求连接后整个图联通，并且去掉 $v$ 点后整个图不连通。

若有解，输出所连得的 $m$ 条边，随意输出一种方案即可；若无解，输出 ```-1```。

## 说明/提示

- $n, m \le {10}^5$

Translated by 稀神探女

## 样例 #1

### 输入

```
5 6 3
```

### 输出

```
1 2
2 3
3 4
4 5
1 3
3 5
```

## 样例 #2

### 输入

```
6 100 1
```

### 输出

```
-1
```

# 题解

## 作者：fls233666 (赞：6)

### 题目大意:

构造一个有 $n$ 个点，$m$ 条无向边的连通图，使编号为 $v$ 的点为图的割点。如果能构造，输出构造得到的 $m$ 条边，否则输出 $-1$ 表示无解。

### 题解：

首先，为了确保图连通，则**最少要有 $n-1$ 条边**。那么，当 $m<n-1$ 时无解。

其次，为了确保点 $v$ 是割点，我们可以**把起始的 $n-1$ 条边的一端全部连在点 $v$ 上**。这样后面再连边时可以保证点 $v$ 是割点。

那么继续考虑当 $m>n-1$ 时，怎么消耗掉剩下的边。**我们可以把除点 $v$ 以外的 $n-2$ 个点和点 $v$ 尽可能凑成完全图，剩下的一个点只与 $v$ 有连边**，保证点 $v$ 还是割点。

因为有 $n-1$ 个点的完全图边数为 $\dfrac{(n-1)(n-2)}{2}$，再算上和剩下的一个点有一条连边，我们得出， **当 $m>\dfrac{(n-1)(n-2)}{2}+1$ 时，又是无解**。

剩下的就是代码实现的问题了，下面是代码：

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rgt register int
using namespace std;

int n,m,vis;

int main(){

	scanf("%d%d%d",&n,&m,&vis);
	if(m<n-1||m>(n-1)*(n-2)/2+1){ //先判无解
		printf("-1");
		return 0;
	}
    
	m-=n-1;//保证图连通，先用掉n-1条边
	for(rgt i=1;i<=n;i++)  //构造这n-1条边
		if(i!=vis)
			printf("%d %d\n",vis,i);
            
	if(m){  //如果还有边可以用
    	//构造完全图
		for(rgt i=2;i<n;i++){
			if(i==vis)
				continue;
			for(rgt j=1;j<i;j++){
				if(j==vis)
					continue;
				printf("%d %d\n",i,j);
				m--;
				if(!m)  //边用完直接结束
					return 0;
			}
		}
	}
	return 0;
}
```


---

## 作者：Xiphi (赞：2)

小清新构造题，蛮有意思的。

考虑这样一种图，首先，把各个点连成一个菊花图，$v$ 点为中心。如果菊花图都连不了，那么输出`-1`。接着，从第一个点开始，连接次点编号大于这个点的点，这样即可满足题目条件。

代码：
```cpp
#include<iostream>
using namespace std;
#define int long long
signed main(){
    int n,m,v;
    cin>>n>>m>>v;
    if(n-1>m||m>(n-1)*(n-2)/2+1){
        puts("-1");
        return 0;
    }
    for(int i=1;i<n;++i){//先用n-1条边把所有点连起来，构成一个菊花图
        if(i==v) continue;
        cout<<i<<' '<<v<<'\n';
    }
    m-=(n-1);//减去n-1，因为构成菊花图就用了n-1条边
     for(int i=1;i<n&&m;i++)  
     {  
                for(int j=i+1;j<n&&m;j++)  
                {  
                    if(i!=v&&j!=v)  
                    {  
                       cout<<i<<' '<<j<<'\n'; 
                       m--;  
                    }  

                }  
    } 
    return 0;
}
```

---

## 作者：无尽星空 (赞：2)

### 题目大意

给定$n,m,v$，构造一个有$n$个点，$m$条无向边的连通图（无自环，重边），使$v$点为割点
### 思路分析

**第一问：**

对于给定的$n$,我们可以求出构造出符合题意的连通图最少用的边数$m_{min}$和最多用的边数$m_{max}$，如果$m_{min}≤m≤m_{max}$就可以构造,否则输出$-1$

求$m_{min}$很简单，只要构造出一颗树即可，所以$m_{min}=n-1$，姑且先将这$n-1$条边叫做树边

那么，如何求$m_{max}$呢？

首先，为保证是连通图，先将$n-1$条树边连起来，我们选择将每个点（$v$除外）与$v$连边，如下图（菊花图）

![](https://cdn.luogu.com.cn/upload/image_hosting/a1gr7qxv.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这样，我们再来考虑其他边，$v$点我们现在可以删去了，根据题目要求，删去$v$点后图不连通，所以图中会剩下几个联通块，如下图

![](https://cdn.luogu.com.cn/upload/image_hosting/p57hmudu.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

显然，剩下2个联通块时可以连的边最多

现在问题变成了：共有$a$个点，分成两部分（$x$和$a-x$），分别构造完全图，问怎么分使得总边数最多

推~~柿子~~式子：
$f(x)=\frac{x(x-1)}{2}+\frac{(a-x)(a-x-1)}{2}$

化简得：$f(x)=\frac{2x^2-2ax+a^2-a}{2}$

分析这个二次函数，可以得出，当$x=1\ or\ a-1$时，$f(x)$取得最大值

所以回到原题，我们应该分成$1,n-2$的两部分

可求$m_{max}=n-1+\frac{(n-2)(n-3)}{2}$

**第二问：**

前$n-1$条边：输出树边（将每个点（$v$除外）与$v$连边）

剩下$m-n+1$条边：

由于第一问中我们将剩下的$n-1$个点分成了$1$和$n-2$两部分，显然“$1$”和$v$号点不能连边，那么我们随便选一个点作为那个“$1$”，剩下的点随便连边即可

### 代码

```
#include<bits/stdc++.h>
using namespace std;
long long n,m;
int v,i,j,cz;
int main()
{
	scanf("%lld%lld%d",&n,&m,&v);
	if(m<n-1||m>n-1+(n-2)*(n-3)/2)  {cout<<-1;return 0;}
	//注意1e5*1e5会炸int，注意开long long（或者加上（long long）亦可）
	cz=(v==n)?1:n;   //被抛弃的“1”
	for(i=1;i<=n;i++)
		if(i!=v)  printf("%d %d\n",i,v);
	m-=(n-1);
	for(i=1;i<=n;i++)
		if(i!=v&&i!=cz)
			for(j=i+1;j<=n;j++)
				if(j!=v&&j!=cz)
				{
					if(!m)  return 0;
					//注意先判断再输出，如果先输出再判断的话当m=n-1时，进入循环的m=0，--后等于-1，会死循环
					printf("%d %d\n",i,j);
					m--;
				}
}
```

---

## 作者：Masna_Kimoyo (赞：1)

两种构造方式。

对于构造题的套路，很明确的，先讨论结果为 $-1$ 的情况。

这道题的结果是不是 $-1$ 主要由边的数量来决定。

考虑下界，如果边的数量比 $n$ 小，显然构不成一个连通图。

考虑上界，为了使得边的数量最大，一定是在割点的一侧放一个点，另一侧放其他所有点。那么贡献就很好算。剩下 $n-1$ 个点的完全图边数量加上割点所连的那条单独边。那么边的总数即为 $\frac{(n-1)\times(n-2)}2+1$。

剩下的就是如何构造了。

$1\degree$

比较麻烦的做法。为了方便，选择 $1$ 或 $n$ 作为这个割点所连的单独点，但程序一开始并不知道 $v$ 是否在 $1$ 或 $n$ 上。所以要判断一下。

连边就很简单了，由于 $v$ 点和其所连的单独点已经确定，剩下的点随便连即可。对于一个点，将所有连接后合法的边连上就完事了，直到边不够为止。

$2\degree$

一种很妙的方法。首先钦定一个点，当然这个点一定不是 $v$。那么现在将编号比它小的所有点与其连边（前提是边还够用，且连的点也不是 $v$）。可以发现，在所有边都用完，且此时的 $m$ 是对于 $n$ 的上限时，由于一开始连边每个点都连编号比自己小的，那剩下来编号最大的那个点没有被连过，自然而然就成了 $v$ 的单独连接点。

代码都十分短，主体就两个循环加输出。

---

## 作者：lixiao189 (赞：1)

## 题目大意:
这个题目的大概意思就是求一个图，**两个点之间最多只能连接一次**（这个地方题面貌似没翻译啊），开始的时候这个图是连通的，然后去掉一个顶点 $ v $ ，使得整个图不再连通（连通的意思就是有一些点无法通过任何方式到达另一个点）。

## 思路：
这个题目大概的思路算是一个贪心吧。~~(原谅我这个蒟蒻为了想这个贪心想了一整天）~~。如果我们要尽量满足这个目标，就必须要构造下面的这个图形：

![](https://cdn.luogu.com.cn/upload/pic/30657.png )

其中最上面的点Q是所有点中除了$ v $ 以外的一个点，为了方便计算，如果`v!=n`那么这个点就是 `v+1` ，如果`v==n`那么这个点就是 `v-1` ,然后现在这个图中的所有的边就是为了保证开始时图的连通性所弄的边。

至于为什么这几个点要这么摆，我们之后再讲。这个时候我们可以发现如果 $ m < (n-1) $ 那么我们连一开始的连通性都无法保证，直接输出-1走人。

如果可以保证了我们再这么做，由于整个图是连通的，如果我们把 $ v $ 删掉了以后，图一定会分成两个连通块（如果不知道连通块就去问老师）。 所以我们要保证去掉 $ v $ 后两个连通块之间都没有边相连，所以点 $ v $ 的位置一定在这两个连通块之间，并且所有从一个连通块到达另一个连通块的边一定是要经过点 $ v $ 的（要不然删掉点 $ v $ 后整个图还是连通的）。

所以我们接下来剩下的 $ m-(n-1) $ 条边就只能分别在两个连通块里添加，而且我们需要一种方案，能够使得剩下的边尽量被用完，如果不能被用完，那么输出-1走人。

之后我们要确定一边的连通块里的点的个数，要如何安排点的个数使得图能尽量能让剩下的边能添加进去。我们设一个连通块里的点的个数 $ x $ 那么另一个连通块里的点的个数为 $ (n-1-x) $ 很显然当一个连通块里有n个点的时候我们可以最多在这个连通块里连
 $ \frac{(x-1)\times (x-1+1)}{2} $ 条边，而另一个连通块里则最多可以连 $ \frac{(n-1-x)\times (n-2-x)}{2} $ 条边。所以我们可以把这两个式子加起来，去掉常数后的到 $ x^2+(1-n)\times x $ 我们发现当 $ x=\frac{1-n}{2} $ 的时候这个式子的值是最小的，而 $ \frac{1-n}{2} $ 本身是个负数，所以我们可以得到这个性质：** $ x $ 越大，这个图所能连的最多的边数越多。**
 
 所以我们让一边的连通块的个数为 $ n-2 $ , 另一边的连通块的个数为 $ 1 $ 就可以了，之后我们先判断一下剩下的边会不会超过这个连通块所能连的最多的边的数量，如果不行就输出 $ -1 $ 走人，之后把剩下的边往个数为 $ n-2 $ 的那个连通块里添加，这样就解决这个问题了。
 
## 代码：
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n,m,v;
vector <int> num;
vector <pair <int,int> > ans;

int main()
{
	scanf("%d %d %d",& n,& m,& v);

	if(m<(n-1) || ((m-(n-1))>(n-3)*(n-2)/2)){ //两个Bug
		printf("-1\n");
		return 0;
	}
	
	//首先要保证图连通
	for(register int i=1;i<=n;i++){
		if(i==v) continue;
		else m--,printf("%d %d\n",i,v);
	}
	
	//如果刚好连完了就停止程序要不然就要死循环
	if(m==0) return 0;
	
	if(v!=n){
		for(register int i=1;i<=n;i++){
			if(i==v || i==v+1) continue;
			num.push_back(int(i));
		}
	}
	else{
		for(register int i=1;i<=n;i++){
			if(i==v || i==v-1) continue;
			num.push_back(int(i));
		}
	}
	
	register int i=0,j=1;
	while(true){
		if(j==(int)num.size()) i++,j=i+1;
		if(i==(int)num.size()-1) break;
		printf("%d %d\n",num[i],num[j]);
		m--,j++; if(m==0) break;
	}
	
	return 0;
}

```

---

## 作者：SpringFullGarden (赞：0)

## 题意

构造一个由 $n$ 个点，$m$ 条边组成无向连通图，使编号为 $v$ 的点为图的割点。

## 思路

### 有解

可以先连成一个菊花图（确保图联通），选一个点只和 $v$ 连（选点 $1$ 较为方便），其他点之间尽可能连边。

### 无解

- 至少要 $n - 1$ 条边以确保图联通。所以，当 $m < n - 1$ 时无解。
- 最多可以连 $\frac {(n - 1)(n - 2)} {2} + 1$ 条边。因为让一个点只连 $v$，其他点之间最多连 $\frac {(n - 1)(n - 2)} {2}$ 条边，加上前面的一条，共 $\frac {(n - 1)(n - 2)} {2} + 1$ 条边。所以，当 $m > \frac {(n - 1)(n - 2)} {2} + 1$ 时无解。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ui unsigned int
using namespace std;

int main() {
//  freopen(".in", "r", stdin);
//  freopen(".out", "w", stdout);
	int n, m, v; scanf("%d%d%d", &n, &m, &v);
	if((n - 1) * (n - 2) / 2 + 1 < m || m < n - 1) {
		printf("-1");
		return 0; 
	}
	for(int i = 1; i <= n; i++) 
		if(i != v) printf("%d %d\n", v, i), m--;
	if(!m) return 0;
    for(int i = 2; i <= n; i++)
        for(int j = 1; j < i; j++) {
        	if(i != v && j != v) printf("%d %d\n", i, j), m--;
        	if(!m) return 0;
		}
	return 0;
}

```

---

## 作者：Forever1507 (赞：0)

清新小构造，就是坑有点多。

先上方案：单独连接 $v$ 和任意 $1$ 个点，剩下的 $n-2$ 个连完全图，并将 $v$ 和其中每个点相连优先级是先连链再构造完全图。这样在确保 $v$ 是割点的同时使边数最大。

首先点数量一定时显然构造完全图能使 $m$ 的上限最大，接下来证明一下为什么一边 $n-2$，一边 $1$ 个是最优的。

设两边点数为 $x$ 和 $y$ 且 $x>y$。

最大边数为 $x+y+\frac{x\times(x-1)}{2}+\frac{y\times(y-1)}{2}$。

如果 $x$ 分一个给 $y$，最大边数为：$x+y+\frac{(x-2)\times(x-1)}{2}+\frac{y\times(y+1)}{2}$。

相减后（前式减后式）的 $x-y$，大于 $0$，所以前者更优。

至于多分叉的情况证明与之类似（分叉之间不能相互连），便不再赘述。

所以只要 $m$ 在 $[n-1\text{(链)},n-1+\frac{(n-2)\times(n-3)}{2}]$ 的范围内就有解，构造如上。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,v,a[100005];
int main(){
	cin>>n>>m>>v;
	long long maxn=n-1+(n-2)*(n-3)/2;//不开long long......
	if(n-1>m||m>maxn){
		cout<<-1;//无解
		return 0;
	}
	int cnt=0;
	for(int i=1;i<=n;++i){
		if(i==v)continue;
		a[++cnt]=i;
	}
	queue<pair<int,int> >q;
	q.push(make_pair(v,a[n-1]));
	cnt=1;
	int i=1,j=1,ii=0;
	while(cnt<m){
		++ii;
		if(ii==v)++ii;
		if(ii==a[n-1])break;
		q.push(make_pair(v,ii));
		++cnt;
	}//先构造链
	while(cnt<m){
		if(i==v)++i,j=i;
		++j;
		if(j==v)++j;
		if(j==a[n-1]){
			i++;
			if(i==v)++i;
			j=i+1;
		}
		if(j==v)++j;
		if(j==a[n-1]){
			i++;
			if(i==v)++i;
			j=i+1;
		}
		cnt++;
		q.push(make_pair(i,j));//连完全图，注意避开v!!!
	}
	while(!q.empty()){
		cout<<q.front().first<<' '<<q.front().second<<'\n';
		q.pop();
	}
	return 0;
}
```


---

## 作者：Tx_Lcy (赞：0)

简单的构造题。

[题目传送门](https://www.luogu.com.cn/problem/CF22C)
## 思路
首先为了保证原图是联通的，显然我们最少需要 $n-1$ 条边。如果 $m<n-1$，显然是无解的。

接下来我们考虑边数上限。

因为 $v$ 要是割点，所以显然我们一定可以把原图按照 $v$ 分成两个互不相交的部分。这两个部分之间一定会有边。同时为了连边数尽可能多，我们需要构造完全图。设某一个部分的点数为 $x$，则另一个部分的点数为 $n-x-1$。由于它们都要构造成完全图，所以总边数 $y=\frac{(x-1) \times x}{2} + \frac{(n-x-2) \times (n-x-1)}{2}=\frac{x^2-x+n^2-nx-2n-nx+x^2-2x-n+x+2}{2}=x^2-(n+1)x+\frac{n^2-3n}{2}$。

我们发现，根据这个二次函数，当 $x=1$ 或 $x=n-2$ 时，取到最大值，所以最终 $y=n-1+ \frac{(n-2)(n-3)}{2}$。显然，当 $m>y$ 时，也是无解的。

接下来就非常简单了，直接构造方案即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define rint register int
using namespace std;
signed main(){
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	int n,m,v;cin>>n>>m>>v;
    if (n-1>m) return cout<<"-1\n",0;
    if (n-1+((n-3)*(n-2)>>1)<m) return cout<<"-1\n",0;
    m-=(n-1);for (rint i=1;i<=n;++i) if (i^v) cout<<i<<' '<<v<<'\n';
    int del=(v+1)%n+1;
    for (rint i=1;i<=n;++i){
        if (!m) break;
        if (i==del) continue;
        if (i==v) continue;
        for (rint j=i+1;j<=n;++j){
            if (j==v) continue;
            if (!m) break;
            if (j==del) continue;
            --m;cout<<i<<' '<<j<<'\n';
        }
    }
    return 0;
}

```


---

## 作者：fuzhelin1984 (赞：0)

## 题意

给定 $ n $ 个顶点，可以在这些顶点之间连接 $ m $ 条双向边，要求连接后整个图联通，并且去掉 $ v $ 点后整个图不连通。

若有解，输出所连得的 $ m $ 条边，随意输出一种方案即可；若无解，输出 $ -1 $ 。

## 思路

为了保证满足题目要求，我们需要使一个点只与 $ v $ 点联通，这样就能保证去掉 $ v $ 点后全图不连通。为了方便，我们可以默认非联通点为 $ 1 $ 号点，如果 $ v $ 点为 $ 1 $ ，则取 $ 2 $ 号。

题目要求我们输出所有的边，由于 $ m $ 不大，我们可以直接暴力查找符合条件的边并输出。

只有两种不可能的情况，边数不足以在一开始构造连通图，或需要连的边数大于最多可连的边数。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int _read()
{
    register int x=0,f=0;register char ch=getchar();
    while(ch<'0'||ch>'9')f|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return f?-x:x;
}
inline void read(int& t)
{
	t=_read();
}
template<typename ...Arg> inline void read(int& t, Arg& ...args)
{
	t = _read();
	read(args...);
}
int n,m,v;
signed main()
{
	read(n,m);
	read(v);
	if((n-1) > m || m > (n-1)*(n-2) / 2 + 1) return cout<<"-1",0;//
	m -= n-1;
	for(int i = 1;i <= n;++i) if(i != v) cout<<i<<" "<<v<<"\n";
	if(m != 0)
	{
		for(int i = 2;i <= n;++i) 
		{
			if(i == v) continue;
			for(int j = 1;j < i;++j)
			{
				if(j == v) continue;
				cout<<i<<" "<<j<<"\n";
				m--;
				if(!m) return 0;
			}
		}
	}
}

```


---

## 作者：XL4453 (赞：0)

### 解题思路：

将某一个节点删掉后图不联通，也就是这个点旁边的几个联通块之间没有连边，那么就考虑如何分块使得所能构成的边最多。

设当前除了点 v 还有 $n$ 个点，将其分成至少两块使得 $\sum \dfrac{a_i\times(a_i+1)}{2}$ 最大，显然有将尽可能多的值放到一起才能使得这样的一个总和最大。

那么就将某一个点单独放到一边，然后将所有的其它点构成一个完全图。可以证明，这样构成的图边的数量是最多的。

题目还要求整个图是联通的，显然需要 $n-1$ 条边才能联通。

考虑具体的构造方法，首先将所有的点和天选之点连边，然后再将剩下的 $n-2$ 个点构成一个完全图就行。

--------
### 代码：
```cpp
#include<cstdio>
using namespace std;
int n,m,v,num[100005],p1,p2;
int main(){
	scanf("%d%d%d",&n,&m,&v);
	if(n-1>m||(n-2)*(n-1)+2<2*m){
		printf("-1\n");
		return 0;
	}
	num[2]=v;
	for(p1=1,p2=1;p1<=n&&p2<=n;p1++,p2++){
		if(num[p1]!=0)p1++;
		if(p2==v)p2++;
		num[p1]=p2;
		printf("%d %d\n",v,p2);
	}
	m-=n-1;
	p1=3;p2=4;
	while(m){
		printf("%d %d\n",num[p1],num[p2]);
		p2++;m--;
		if(p2>n)p1++,p2=p1+1;
	}
	return 0;
}//5 6 3
```


---

## 作者：CrTsIr400 (赞：0)

构造题。

考虑构造一棵菊花图，这样能保证 $v$ 一定是割点，删除它后这张图比别的树更优（两两不可达）。

然后再定住一个菊花图上的叶子节点，保证这张图被删除 $v$ 之后至少有 $2$ 个连通块。于是这个叶子节点不与别的点连边，自己组成一个连通块。

然后剩下的边构造一张完全图就行。

```cpp
#include<bits/stdc++.h>
#define RI register int
using namespace std;typedef long long LL;const int inf=0x3fffffff;char CH;int Fl;template<typename T>void in(T&x){CH=getchar();Fl=1;x=0;while(!isdigit(CH))Fl=(CH=='-')?-1:1,CH=getchar();while(isdigit(CH))x=x*10+CH-'0',CH=getchar();x*=Fl;}template<typename T,typename...Args>void in(T&x,Args&...args){in(x);in(args...);}
int n,m,ans,v,X[100001],Y[100001];
void ins(int x,int y){
	X[++ans]=x;Y[ans]=y;--m;
	if(m<=0){
		for(RI i=1;i<=ans;++i)printf("%d %d\n",X[i],Y[i]);
		exit(0);}}
int Dnode;
int main(){
	in(n,m,v);
	if(m<n-1)return printf("-1"),0;
	for(RI i=1;i<=n;++i)if(i!=v)ins(i,v);
	for(RI i=1;i<=n;++i)if(i!=v){
		Dnode=i;break;
	}for(RI i=1;i<n;++i)if(i!=v&&i!=Dnode){
		for(RI j=i+1;j<=n;++j)if(j!=v&&j!=Dnode)
		ins(i,j);
	}
	if(m>0){
		printf("-1");
		return 0;}}
```

---

## 作者：MuYC (赞：0)

[MYCui的博客，更好的体验](https://www.cnblogs.com/MYCui/p/13945384.html)
#### 前言
这是一个构造题。

点明两个公理：

+ 一个$n$个点的无向完全图最多有$\frac{(n-1)*n}{2}$条边。

+ 要使得一个$n$个点的无向图联通，至少需要$n-1$条边

#### 思路：

根据上面提到的公理，我们很明显的可以知道：

+ #### $Case1$
假如给出的$m$ < $n-1$，显然无解，输出$-1$。

+ #### $Case2$
假若$m$ = $n-1$，那么你给出的连通图必然是一棵树，当然，这个题很好满足条件，构建一朵菊花，中心点为$v$即可，即用$v$向其它$n-1$个点连边。

+ #### $Case3$

$m$ >= $n$

从上面$Case2$得到启发，我们可以先构造一朵以$v$为中心的菊花。

这样子操作后，我们就连上了$n-1$个点

我们剩下要连的边数就会等于$m-n+1$条。

我们就保证了给出的图一定是联通的。

考虑如何使得整个图按题意删除点$v$后整个图不联通。

因为整个图不连通，那么整个图至少分裂出了两个部分。

我们不妨假设其中一个图只有一个点，另外的一个图就会有$n-2$个点。

在$Case3$下上面情况下会无解？

答案是：当那一个点数为$n-2$的图已经是**完全图**的时候，仍然存在没有连完的边。

因为你把其中点数为$n-2$的那一个图已经连满了，那一个图已经无法在自己内部连了，只能连入仅有一个点的那个图了。这样子的话，就算$v$点被删除，剩下的整个图仍然会是联通的。

这样子就无解了。也就是$m - n + 1 < \frac{(n-2)*(n-3)}{2}$即无解

(下面是关于上面的做法的证明，如果不想看可以选择跳过)

有人会问：为什么一定是两个不连通的图？难道三个的，四个的就不能满足条件了吗？

我们至少得剔除一个点出来，这个点不能与其他点联通(指删除点$v$后的图)

剩下的点一共就$n-2$个了(因为点$v$)被删除了 .

证明：当剩下的$n-2$个点在同一联通块时，能连的边最多。

假设这$n-2$个点分裂成了$k$个联通块。

$k$个联通块的点数分别为$p_1,p_2,p_3...p_k$

并且满足:$p_1+p_2+p_3+...+p_k = n - 2$

能连的边的总数就会是:

$\frac{(p_1-1)*p_1}{2} + \frac{(p_2-1)*p_2}{2}$ + ... + $\frac{(p_k-1)*p_k}{2}$

把式子暴力展开变为:

$\frac{p_1^2}{2} + \frac{p_2^2}{2} + ... +\frac{p_k^2}{2} - \frac{\sum_{i = 1}^{i = k} p_i}{2}$

把证明的内容写为不等式即为：

$\frac{p_1^2}{2} + \frac{p_2^2}{2} + ... +\frac{p_k^2}{2} - \frac{\sum_{i = 1}^{i = k} p_i}{2} < \frac{(n-2)(n-3)}{2}$

不妨将$p_1 + p_2 + ... + p_k$写成$n-2$的形式。

原式等于：

$\frac{p_1^2}{2} + \frac{p_2^2}{2} + ... +\frac{p_k^2}{2} - \frac{n-2}{2} < \frac{(n-2)(n-3)}{2}$

移项，合并同类项：
$\frac{p_1^2}{2} + \frac{p_2^2}{2} + ... +\frac{p_k^2}{2} < \frac{(n-2)^2}{2}$

∵ $p_1+p_2+p_3+...+p_k = n - 2$

∴ 上面不等式恒成立 。

证毕。

使用完全图的形式使得一个点的度数尽可能多进行连边即可，这个贪心是很显然的。

把任意一个不是点$v$的点拿出来，然后剩下的$n-2$个点里面按照贪心使得一个点度数尽可能多，任意连$m-n+1$条边即可

(继续任意找一个点当做菊花的中心然后就可以递归处理问题了。这是这个题目递归标签的由来)。

这个题目就完了。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n , m , v;
int arr[100005],tail = 0;
signed main()
{
	cin >> n >> m >> v;
	if(m < n - 1){cout << -1 ; return 0;}
	if(m == n - 1)
	{
		for(int i = 1 ; i <= n ; i ++)
			if(i != v)
			cout << v << " " << i << endl;
		return 0;
	}

	m = m - n + 1;
	if((n - 2) * (n - 3) / 2 < m){cout << -1 ; return 0;}//判断是否有解
	for(int i = 1 ; i <= n ; i ++)
		if(i != v)
		cout << v << " " << i << endl;//先构造一朵菊花
	int now = 0;
	while(now <= n - 2)
	{
		if(now * (now - 1) / 2 >= m)break;
		now ++;
	}
	for(int i = 1 ; i <= n - 1 ; i ++)
	{
		if(now == 0)break;
		if(i != v)tail ++ , now -- , arr[tail] = i;
	}
	for(int i = 1 ; i < tail && m; i ++)
	{
		for(int j = i + 1 ; j <= tail && m; j ++)
			cout << arr[i] << " " << arr[j] << endl , m --;
	}
	return 0;
}
```

---

