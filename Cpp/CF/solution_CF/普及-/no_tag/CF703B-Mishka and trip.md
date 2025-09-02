# Mishka and trip

## 题目描述

Little Mishka is a great traveller and she visited many countries. After thinking about where to travel this time, she chose XXX — beautiful, but little-known northern country.

Here are some interesting facts about XXX:

1. XXX consists of $ n $ cities, $ k $ of whose (just imagine!) are capital cities.
2. All of cities in the country are beautiful, but each is beautiful in its own way. Beauty value of $ i $ -th city equals to $ c_{i} $ .
3. All the cities are consecutively connected by the roads, including $ 1 $ -st and $ n $ -th city, forming a cyclic route $ 1—2—...—n—1 $ . Formally, for every $ 1<=i&lt;n $ there is a road between $ i $ -th and $ i+1 $ -th city, and another one between $ 1 $ -st and $ n $ -th city.
4. Each capital city is connected with each other city directly by the roads. Formally, if city $ x $ is a capital city, then for every $ 1<=i<=n,i≠x $ , there is a road between cities $ x $ and $ i $ .
5. There is at most one road between any two cities.
6. Price of passing a road directly depends on beauty values of cities it connects. Thus if there is a road between cities $ i $ and $ j $ , price of passing it equals $ c_{i}·c_{j} $ .

Mishka started to gather her things for a trip, but didn't still decide which route to follow and thus she asked you to help her determine summary price of passing each of the roads in XXX. Formally, for every pair of cities $ a $ and $ b $ ( $ a&lt;b $ ), such that there is a road between $ a $ and $ b $ you are to find sum of products $ c_{a}·c_{b} $ . Will you help her?

## 说明/提示

This image describes first sample case:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703B/f56e7113e4ecabd1250712cc69d300125f300e0b.png)

It is easy to see that summary price is equal to $ 17 $ .

This image describes second sample case:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703B/e184cc93e6f4812674986a147f81ce08dfb70d8b.png)

It is easy to see that summary price is equal to $ 71 $ .

## 样例 #1

### 输入

```
4 1
2 3 1 2
3
```

### 输出

```
17```

## 样例 #2

### 输入

```
5 2
3 5 2 2 4
1 4
```

### 输出

```
71```

# 题解

## 作者：peppaking8 (赞：4)

## 思路：
首先，这是一道简单的**图论**题。但是，它连图论标准函数 ```add_edge``` 都没有用上，因为它是橙题啊。

我们正式开始。首先，如果暴力枚举的话，思路就是建一个邻接矩阵，先把连接的边处理了，在一条一条的枚举，计算答案。时间复杂度 $O(n^2)$ ，空间复杂度 $O(n^2)$ 。

看来出现了多个问题，时间复杂度和空间复杂度都爆了。~~原来橙题没那么简单~~。我们一个一个解决。

### 1.空间问题
邻接矩阵就别想了。

考虑先把城市连接下一个城市的边连好，形成一个环，记录答案。然后就是**省会**的事情了。

省会怎么搞？我们用一个 ```bool``` 数组 ```is_cap[]``` 表示这个城市目前有没有被我们发现时省会。其中 ```cap``` 指 ```capital``` 。

每当我们搜到一个省会，我们**需要连接的边就是那些既不是这个点的前面一个点，又不是这个点的后继，也不是之前已经连过边的省会**。这样就能保证不重不漏了。

这样，空间复杂度就降到了 $O(n)$。

那，还得遍历之前的省会，寻找要连的边啊！这样时间复杂度不是还是 $O(n^2)$ 吗？

### 2.时间问题
通过观察，可以发现：边的个数也是$O(n^2)$的。所以我们不能把所有边都遍历一遍寻找答案。这怎么办？

假设之前**所有省会的点权和**为 $nowsum$。那么可以知道，在新加进一个省会之后， $nowsum$ 也可以在 $O(1)$ 的效率中更新。这样的话，我们没有必要枚举前面的点是否该连边，直接统计答案即可。

时间复杂度为$O(n)$。

## 代码：
```
#include<bits/stdc++.h>
#define int long long
//需要开long long
using namespace std;
const int N=100005;
int n,m,val[N],sum,nowsum,ans=0;
//val[]表示点权
bool is_cap[N];
int first_num(int k){//计算一个点的前接
    if(k==1) return n;
    return k-1;
}
int last_num(int k){//计算一个点的后继
    if(k==n) return 1;
    return k+1;
}
signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%lld",&val[i]);sum+=val[i];
        ans+=val[i]*val[i-1];
    }
    //用sum记录所有点的点权和
    //ans表示答案，这里统计了基本边，也就是环中的答案
    ans+=val[1]*val[n];
    //注意，上面的遍历中，当i=1时，答案并没有被成功的加入。所以说要再加一次
    for(int i=1;i<=m;i++){
        int capi;
        scanf("%lld",&capi);
        is_cap[capi]=true;
        nowsum+=val[capi];
        ans+=val[capi]*(sum-nowsum);
        //将不是省会的边全部连上，再减去两边的点
        if(!is_cap[first_num(capi)]) ans-=val[capi]*val[first_num(capi)];
        if(!is_cap[last_num(capi)]) ans-=val[capi]*val[last_num(capi)];
    }
    printf("%lld\n",ans);
    exit(0);//记得点赞哦～
}
```

---

## 作者：jixuan (赞：2)

#### [题目传送门](https://www.luogu.com.cn/problem/CF703B)

### 思路
这一题并不难，只是思维难度较高。

所有城市和下一个城市的边的权值先相加，我们再来考虑省会城市。

若该城市是省会城市，那么就只要再加上该省会城市与其他所有普通城市的边的权值即可，也就是**加上该省会城市与其他所有城市的边的权值，再减去它与前面出现过的省会城市和左右两边的城市的边的权值**。

时间复杂度为 $\mathcal O(n+k)$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,sum,ssum,ans;
int c[100010],id[100010],f[100010];
signed main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>c[i];
	for(int i=1;i<=n;i++)
	{
		ans+=c[i]*c[i%n+1];
		sum+=c[i];//记录所有城市权值
	}
	for(int i=1;i<=k;i++)
	{
		cin>>id[i];
		f[id[i]]=1;
		int lf=id[i]-1,rt=id[i]+1,t=ssum;
		if(lf==0)lf=n;
		if(rt==n+1)rt=1;
		if(f[lf]==1)t-=c[lf];//如果左右两边是省会城市，就不需要去除两次
		if(f[rt]==1)t-=c[rt];
		ans+=c[id[i]]*sum;
		ans-=c[id[i]]*(c[rt]+c[lf]+c[id[i]]);//去除左右两边和自己
		ans-=c[id[i]]*t;//去除前面的省会城市
		ssum+=c[id[i]];//记录省会城市权值
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：xiaoyuchenp (赞：2)

此题在橙题中算是难题，思维含量较高。

**题目大意**

$n$ 个城市连成一个环，相邻的城市间有边相连（注意城市 $1$ 和城市 $n$ 间也有边相连，这一点题意翻译里没讲清楚）。省会城市与每个城市间都有边相连（做时注意去重边），每条边的权值为其两个端点的权值之积。求每条边的权值之和。

**思路一**

暴力，一条一条边枚举计算答案。具体做法这里就不细讲了，时间复杂度  $O(n^{2})$，不能通过本题。

**思路二**

站在思路一的角度上考虑如何优化，考虑把所有城市连成一个环，记录答案。比较复杂的是计算省会的问题。

设所有城市的权值之和为 $sum$，求省会时显然是用省会的权值 $c_i$ 乘上 $sum$ 减去省会本身的权值以及相邻两边城市的权值（注意相邻两边的城市需要不是省会才能减去，这一点很多题解都没提醒到）乘上该城市的权值即可。先初始化 $sum$ 再对省会城市进行操作，时间复杂度 $O(n)$，可以通过本题。

还有一个坑点是最终答案必须用 $\texttt{long long}$ 存储。

```cpp
#include<bits/stdc++.h>
#define MAXN 100005
#define pre(x) (x==1? n:x-1) //计算该点的前驱
#define next(x) (x==n? 1:x+1) //计算该点的后继
using namespace std;
int n,k;
int c[MAXN],id;
long long ans,sum;
bool iscap[MAXN];

int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>c[i];
	for(int i=1;i<=n;i++){
		ans+=c[i]*c[pre(i)];
		sum+=c[i]; //初始化sum
	}
	for(int i=1;i<=k;i++){
		cin>>id;
		iscap[id]=true;
		sum-=c[id];
		long long tmp=sum*c[id];
		if(!iscap[pre(id)])tmp-=c[pre(id)]*c[id];
		if(!iscap[next(id)])tmp-=c[next(id)]*c[id]; //删除重边
		ans+=tmp;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_SkyLine_ (赞：1)

其实是道有点小坑的图论题。。。
## 思路分析
观察可知 $n \le 10^5$，开邻接矩阵和邻接表等数据结构直接内存超限。所以我们要考虑其他的方法。

首先处理普通城市的情况。我们维护一个变量 $ans$ 作为最终答案，在读入普通城市权值的时候累加 $a_{i-1} \times a_i$，即计算完普通城市边的权值和。

这里就出现了坑点：点 $1$ 与点 $n$ 要建边。（观察样例给的图可知）

然后我们处理省会城市的情况。

一个初始想法就是对于每一个省会城市编号 $id_i$，遍历一遍 $n$ 个城市并对除自己、城市 $id_i-1$ 和城市 $id_i+1$ 且之前没有建过边的点建边。特别地，城市 $1$ 不与城市 $n$ 和城市 $2$ 建边；城市 $n$ 不与城市 $1$ 和城市 $n-1$ 建边。但这样使用了二重循环，$10^{10}$ 的循环次数承受不起直接超时。

考虑优化。

首先根据前面的讨论，我们知道与所有省会城市相连的边都不用被统计，
然后我们采用个 $vis$ 桶动态标记城市 $id_i$ 是否是省会城市，是则 $vis_{id_i}=1$，否则为 $0$。（因为省会城市的编号升序给出，提前记录会导致部分边被提前标记导致无法参与权值和的统计）。累加记录 $\sum_{j=1}^{i-1}c_{id_j}$ 到变量 $sub$ 中并观察从省会城市 $id_i$ 的连边对答案的贡献。该式子为：
$$\LARGE c_1 \times c_{id_i} + c_2 \times c_{id_i} + \cdots + c_n \times c_{id_i}$$
运用乘法分配律改写为：
$$\LARGE\sum_{j=1}^{n}c_j\times c_{id_i}$$
其中 $j$ 的限制与上方提到的相同，$c$ 数组是题目中城市的价值。

不难发现不论 $id_i$ 取何值，上式中 $\sum_{j=1}^nc_j$ 一直是一个定值，考虑预处理出 $\sum_{j=1}^nc_j$ 记录在变量 $mul$ 中，没必要每一次都计算。

我们前文提到 $j$ 有一定的限制，为了方便处理，不妨记录一个中间变量 $m$，赋初值为 $mul$。

据上方讨论出的限制条件，我们有如下情况：

- 对于 $id_i$ 为 $1$ 的情况，令 $m$ 先减去 $(a_1+a_2+a_n)$。如果 $vis_2$ 为 $1$，令 $m$ 加上 $a_2$，否则不用操作。对于 $vis_n$ 为 $1$ 的处理同理。

- 其余情况的处理与上一种情况类似，只是减的数目不同。具体见代码。

计算出最后的 $m$ 后，每次循环令 $ans$ 加上 $(a_{id_i} \times (m-sub))$，循环后输出最后的答案即可。

## $\texttt{Code:}$
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+10;
ll ans=0,mul=0,sub=0;
int n,k,a[N];
bool vis[N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    for(int i=1;i<=n;i++)
    {
    	cin >> a[i];
    	mul+=a[i];
    	ans+=(a[i-1]*a[i]);
	}
	ans+=(a[1]*a[n]);
	for(int i=1;i<=k;i++)
	{
		int id;
		cin >> id;
		ll m=mul;
		if(id==1)
		{
			m-=(a[1]+a[2]+a[n]);
			if(vis[2])
				m+=a[2];
			if(vis[n])
				m+=a[n];
			ans+=(a[1]*(m-sub));
		}
		else if(id==n)
		{
			m-=(a[n]+a[n-1]+a[1]);
			if(vis[n-1])
				m+=a[n-1];
			if(vis[1])
				m+=a[1];
			ans+=(a[n]*(m-sub));
		}
		else
		{
			m-=(a[id]+a[id+1]+a[id-1]);
			if(vis[id-1])
				m+=a[id-1];
			if(vis[id+1])
				m+=a[id+1];
			ans+=(a[id]*(m-sub));
		}
		sub+=a[id];
		vis[id]=true;
	}
	cout<<ans;
    return 0;
}
```
代码里的 $a$ 数组当成上文的 $c$ 数组看即可，其他相同。

---

## 作者：dengqingrui123 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF703B)

# Step 0 ~~题前闲话~~

初看这道题，还认为这题是一道贼难的图论题，正解是模拟。

# Step 1 解题方法

首先先将所有连线上的权值加起来，时间复杂度 $O(n)$，在处理时用一个 $bool$ 数组 $f$ 来记录是否为省会城市。

代码如下：

```cpp
f[x] = 1,s -= a[x],ans += a[x] * s;
```
# Step 2 删除权值

一共有 3 种情况需要扣除权值（设省会城市为 $a_i$，权值为 $q$，总权值为 $ans$)：

1. 若 $a_i = 1 $ 且未读入 $a_n$ 为省会，$ans = ans - a_x \times a_n$。

2. 若 $a_{x \pm 1}$ 不为省会城市，$ans = ans - a_x \times a_{x \pm 1}$。

3. 若 $a_i = n$ 且 $a_1$ 不为省会城市，$ans = ans - a_x \times a_1$。

代码如下：

```cpp
if (x == n && !f[1]) 
			ans -= a[x] * a[1];
		else if (!f[x + 1]) 
			ans -= a[x] * a[x + 1];
		if (x == 1 && !f[n]) 
			ans -= a[x] * a[n];
		else if (!f[x - 1]) 
			ans -= a[x] * a[x - 1];
```

# Step 3 AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int Maxn = 1e5 + 5;
long long n, k, a[Maxn], x, s, ans;
bool f[Maxn];
void check(){
	if (x == n && !f[1]) 
		ans -= a[x] * a[1];
	else if (!f[x + 1]) 
		ans -= a[x] * a[x + 1];
	if (x == 1 && !f[n]) 
		ans -= a[x] * a[n];
	else if (!f[x - 1]) 
		ans -= a[x] * a[x - 1];
}
int main()
{
	scanf("%lld%lld",&n,&k);
	for (int i = 1; i <= n; i ++) {
		scanf("%lld",&a[i]);
		s += a[i], ans += a[i] * a[i - 1];
	}
	ans += a[1] * a[n];
	while (k--) {
		scanf("%lld",&x);
		f[x] = 1,s -= a[x],ans += a[x] * s;
		check();
	}
	printf("%lld",ans);
	return 0;
}
```





---

## 作者：ylch (赞：1)

# CF703B Mishka and trip 题解

~~最难的一道橙题~~

看到大家都在用图论解，我来献上一个模拟的解法。

### 题目大意

有 $n$ 个城市，每个城市有个魅力值 $v_i$，首先，有 $n$ 条路将这 $n$ 个城市连成一个环，$1$ 号城市连 $2$ 号城市，$2$ 号连 $3$ 号 $\cdots\cdots$ $n$ 号连 $1$ 号城市，每条路的魅力值是其连接的两个城市的魅力值的乘积，这 $n$ 个城市其中还有 $k$ 个是特殊城市，每个特殊城市和任意一条城市都有一条路连接，看题目下面的图，保证每两个城市之间最多只有一条路，问所有路的魅力值之和是多少？

### 解题思路

首先是连接成环的路线魅力值，可以用类似前缀和的方法计算。①

然后每个特殊城市的路线，先求出路线的总魅力值为 $ans$，所有城市的魅力值之和为 $sum$。

依次求特殊城市的时候用 $ans$ 加上 $sum$ 减去这个特殊城市本身以及两边相邻的城市魅力值（因为相邻两边的路已经算过了）乘这个特殊城市自身魅力值的积。②

注意这样可能会重复计算左边和右边的路，题目说每条路只能算一次，所以我们只要计算特殊城市除了初始的连边之外其他“新”边的魅力值，而这个特殊城市的的“新”边也可能是其他特殊城市的“新”边，所以要用 $ans$ 减去当前魅力值乘上之前的魅力值的积，去掉重复的。④

考虑一种情况，如果当前特殊城市两边有特殊城市的话，我们是不是就会多减了呢？所以要加一个特判，如果左右两边有特殊城市的话，要减去两个城市的魅力值。③

$cas$ 是计数器，记录当前所有出现过的特殊城市的魅力值之和。⑤

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll a[100005];
bool has[100005];

int main()
{
    int n,m;
    ll sum = 0, ans = 0;
    cin >> n >> m >> a[1];
    for (int i=2; i<=n; i++)
    {
        cin >> a[i];
        ans += a[i]*a[i-1];	//①计算魅力值
        sum += a[i];	//计算加和
    }
    ans += a[1]*a[n];	//头尾相连的魅力值
    ll cas = 0;	//累加器
    while (m--)
    {
        int x,l,r;
        cin >> x;
        has[x] = true;
        //以下为确定左右边界
		l = (x == 1? n : x-1);
		r = (x == n? 1 : x+1);
        ans += (sum-a[x]-a[l]-a[r]) * a[x];	//②计算特殊城市的魅力值
        ll we = cas;
        //如果之前的特殊城市在这个特殊城市左右，要减掉多加的部分
        if (has[l])	we -= a[l];	//③
        if (has[r])	we -= a[r];	//③
        ans -= we * a[x];	//减去重复计算的④
        cas += a[x];	//求出特殊城市的魅力值和⑤
    }
    cout << ans << endl;
    return 0;
}
```

### 总结

这是一道很有难度的思维题（~~对于没学图论的蒟蒻我来说~~），写着写着自己就被绕了进去，好不容易才写出来。所以再写一篇题解理顺一下自己的思路，加深一下自己对题目的理解（~~纪念我浪费的六小时生命~~）。

End
-----------------------

解法参考 [Codeforces 703B (模拟) Mishka and trip](https://www.cnblogs.com/JJCHEHEDA/p/5774370.html)

管理员大大求过~辛苦啦！

谢谢大家！我们一起进步，一起 $rp++$！

---

## 作者：__Tonycyt__ (赞：1)

图论基础题目。   
~~如果暴力，时空复杂度都是 $O(n^2)$，爆炸啦！！！过于合理。（雾~~  
主要看时间（空间在时间优化之后也会跟着优化，也是 $O(n)$ 级别）。  
边数最多 $n^2$，所以遍历不行。  
把所有省会对应图上点的权值之和记为 $cnt$，更新效率 $O(1)$。   
所以复杂度 $O(n)$（最多 $n$ 个省会）。  
### code  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100005
long long n,k,c[N],sum,cnt,ans,id;//切记要开long long，(n,k为了简便作者也开了long long)
bool F[N];
long long f(long long x){//手懒，打一次函数一劳永逸 
	return x==1?n:x-1;
}
long long g(long long x){
	return x==n?1:x+1;
}
inline long long read(){//整形读入优化 
	long long fx=1,x=0;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') fx=-1;
		ch=getchar(); 
	}
	while(ch>='0' && ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return fx*x;
}
inline void write(long long x){//整形输出优化
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
    putchar(x%10+'0');
}
int main(){
	n=read();
	k=read();
    for(long long i=1;i<=n;i++){
    	c[i]=read();
		sum+=c[i];
        ans+=c[i]*c[i-1];//i=1时c[i-1]=c[0]=0
    }
    ans+=c[1]*c[n];
    for(long long i=1;i<=k;i++){
    	id=read();
        F[int(id)]=1ll;
        cnt+=c[int(id)];
        ans+=c[int(id)]*(sum-cnt);
        if(!F[f(int(id))]) ans-=c[int(id)]*c[int(f(id))];
        if(!F[g(int(id))]) ans-=c[int(id)]*c[int(g(id))];
    }
    write(ans);
    return 0;
}
```

---

## 作者：Steve_xh (赞：1)

# 题面：
[**题目传送门**](https://www.luogu.com.cn/problem/CF703B)

**题目大意:**

有 $n$ 个城市，每个城市有一个权值，其中有 $m$ 个省会城市，每个普通城市按顺序连线，省会会和所有城市连线，不会有重线，每条线权值为两相连城市权值之积，求总权值(边)和。
# 思路：
其实我刚看到题目还以为是个**图论**的超难橙题，但是后来看了题目才知道原来这么水……

一开始做的时候是想着套两层循环硬算，但是 $m \leq n \leq 10^6$，所以这个想法肯定是不成立的。

第二种思路就是输入一个处理一个。既然省会会和所有城市连线，那么我们可以只看当前的省会，**算出当前的所有可连线边，减去重边，并统计已经出现过的省会，下次计算就不看这些边了**，时复 $O(n)$，可以实现（参考本机房某大佬思路）。
# $AC$代码:
``` cpp
#include<bits/stdc++.h>
#define int long long//习惯了
#define last(i) (i==1?n:i-1)//简便函数用于求上一个城市的位置
#define next(i) (i==n?1:i+1)//简便函数用于求下一个城市的位置
using namespace std;
int n,m,ans=0,a[100005],sum=0;//sum是为了方便统计当前所有点的总权值，不用for一遍
bool cap[100005];//用于下标计数，方便查看是否为省会(cap全称capital)
signed main(){
    memset(cap,false,sizeof(cap));
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<n;i++)
        ans+=a[i]*a[i+1],sum+=a[i];
    ans+=a[n]*a[1],sum+=a[n];
    for(int i=1,t;i<=m;i++){
        cin>>t,cap[t]=true;//省会城市记为true
        sum-=a[t];//减去是为了下一次统计是不用看这个点
        ans+=sum*a[t];//所有可连线的点连当前点的边权总值
        if(!cap[last(t)])//如果上一个城市不是省会(已经连过了，因为相邻的点也会互连)
            ans-=a[t]*a[last(t)];
        if(!cap[next(t)])//同上，下一个不是省会就减这条重边
            ans-=a[t]*a[next(t)];
    }
    cout<<ans;
    return 0;
}
```


------------
**本蒟蒻第一篇题解，点个赞再走吧！**

---

## 作者：Colorful_Unicorn (赞：1)

# 思路
这题我们可以先把每一条线都互相连通的边的权值之和给统计出来，再减去没有线连接的两个点而预先加上的边的权值之和的即可。那有几种情况需要减去呢？我们可以先建一个 bool 型的数组 $f$ 来标记 $i$ 是否为省会城市，如果是省会城市，那么我们令 $f_i=1$，否则我们令 $f_i=0$。

我们需要判断四种情况（我们输入的省会城市的编号为 $x_i$ 每个点的权值为 $a_i$）：

- 若 $x_i=1$ 且在目前阶段并没有读入到 $n$ 为省会城市，那么答案减去 $a_x \times a_n$。

- 若 $x_{i-1}$ 不为省会城市，那么答案应减去 $a_x \times a_{x-1}$。

- 若 $x_i=n$ 且 $1$ 不为省会城市，那么答案应减去 $a_x \times a_1$。

- 若 $x_{i+1}$ 不为省会城市，那么答案应减去 $a_x \times a_{x+1}$。

其中前两种为一大类，或两种为一大类。

# code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 1e5 + 5;

long long n, k, a[kMaxN], x, s, ans;

bool f[kMaxN];

int main()
{
	cin >> n >> k;
	for (int i = 1; i <= n; i ++) {
		cin >> a[i];
		s += a[i];
		ans += a[i] * a[i - 1];
	}
	ans += a[1] * a[n];
	while (k --) {
		cin >> x;
		f[x] = 1;
		s -= a[x];
		ans += a[x] * s;
		if (x == 1 && !f[n]) {
			ans -= a[x] * a[n];
		}
		else if (!f[x - 1]) {
			ans -= a[x] * a[x - 1];
		}
		if (x == n && !f[1]) {
			ans -= a[x] * a[1];
		}
		else if (!f[x + 1]) {
			ans -= a[x] * a[x + 1];
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：wangjue233 (赞：0)

# Solution
[题目传送门](https://www.luogu.com.cn/problem/CF703B)

## 题目分析
有两种类型的城市：普通城市和省会城市。省会城市与所有其他城市都有连线，而普通城市只与它们的直接邻居有连线。每条连线的权值是由其两端城市的美丽值的乘积决定的。题目让我们计算所有连线的权值之和。

每个普通城市都会与它的两个邻居相连，形成环状结构。这代表如果没有省会城市的话，总权值将是每对相邻城市美丽值乘积的总和，再加上第一个城市和最后一个城市美丽值的乘积（因为城市是首尾相连的）。

每个省会城市都将与除自己之外的所有城市相连。所以，对于每一个省会城市，我们需要计算它与每个非省会城市的美丽值乘积，再加上它与其他省会城市的美丽值乘积（除了它自己）。

ps：如果一条连线连接的是两个省会城市，这条连线的权值只能计算一次。

## 题目思路

计算所有普通连线的权值总和。我们可以遍历每个城市，算一下它和下一个城市的权值。

接着，计算省会城市的连线权值总和。对于每个省会城市，计算它和其他非省会城市之间连线的权值总和，我们可以通过省会城市的美丽值乘上非省会城市的美丽值的总和来算出。

最后，对于每一对省会城市，它们之间的连线权值只计算一次。因为省会城市的序列是升序给出的，我们可以遍历给定的省会城市索引数列，计算连线权值。

答案就是将所有普通连线的权值总和和省会城市连线的权值总和相加。

思路已经讲的比较详细了，代码就不附了，有关于题解的任何问题欢迎私信我。

---

## 作者：Parrhesiates (赞：0)

这里提供一种新的思路，不用建图，直接借助容斥原理进行计算。
我们按照容斥原理一步步展开。
## step 1
先不考虑省会，把每个点都按照普通城市计算。
```
for(int i=1;i<=n;i++){
	int hou=i+1;
	if(hou>n)hou%=n;
	ans+=a[i]*a[hou];
}
```
## step 2
开始考虑只有一个省会的情况，我们可以发现在计算第一个省会的时候，（设省会编号为 $w$)那么 $w-1$ 与 $w$ 的连线以及 $w$ 和 $w+1$ 的连线就是我们重复算的，所以在计算的时候去掉。
## step 3
这是最难的一部分，我们要考虑别的省会。那么这个时候我们要去除的就是每个省会与别的省会的连线，如果直接处理，肯定会超时，那么怎样 $O(n)$ 的解决呢？我们考虑到，每次我们计算完一个省会后，与这个省会相关联的边都算过了，对吧。那它还有什么存在的意义呢，直接删了。
## 实现
ok，思路讲完了，不过实现起来可能还有点困难，这个时候就需要一些处理了，我们每次计算省会的时候，都不可避免的会用到别的点的权值，那如果每次用的时候都算一遍的话，肯定会超时，那么为什么不先预处理出所有点权值之和，用的时候在去掉不需要的呢。

那么问题就解决了呀，接下来就是愉快的代码时间。
```
#include<bits/stdc++.h>
#define int long long//注意long long
using namespace std;
int n,k,a[100010],ans,sum,w[100010];
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	for(int i=1;i<=n;i++){
		int hou=i+1;
		if(hou>n)hou%=n;//注意n号节点和1号节点是相连的 
		ans+=a[i]*a[hou];
	}
	for(int i=1;i<=k;i++){
		cin>>w[i];
	}
	sort(w+1,w+k+1);
	for(int i=1;i<=k;i++){
		int hou=w[i]+1,qian=w[i]-1;
		if(hou>n)hou%=n;
		if(qian==0)qian=n;
		ans+=a[w[i]]*(sum-a[w[i]]-a[hou]-a[qian]);
		sum-=a[w[i]],a[w[i]]=0;//删掉用过的节点 
	}
	cout<<ans;
	return 0;
}
```
怎么样，相当简单吧。

---

## 作者：封禁用户 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF703B)
# First 题意
~~请注意，这是一道橙题。~~

首先，题意很简单，有 $n$ 个城市，其中有 $m$ 个省会，连边的规则是：

1. $i$ 和 $i + 1$ 之间连一条边。
2. $n$ 和 $1$ 之间连一条边。
3. 省会城市和其它所有城市相连。
4. 边的边权是两顶点的点权积。
5. 图中没有重边或自环。

题目需要求每条边的边权和。

# Second 暴力

暴力代码其实 very 简单，直接 $O(nm)$ 去计算每一条边的边权，再去累加计算。

但显然， $n,m \le 100000$ ，这个时间复杂度是不能接受的，所以还需要优化。

# Third 优化

首先，题目中边分两种，第一种是 $i$ 和 $i + 1$ 之间的边（包括 $1$ 和 $n$ 之间的边），他们构成了一个环，可以用 $O(n)$ 的时间复杂度处理。

第二种是省会的边，他也分两种，第一种是省会和其它普通城市的边，可以用 `sum` 优化成 $O(1)$ 的；第二种是省会和省会之间的边，就需要用另一个变量 `shsum` 来存储省会的点权和，也可以优化成 $O(1)$ 的。

这样，我们就把 $O(nm)$ 的时间复杂度优化成了 $O(n + m)$ 的，当 $n,m \le  100000$ 时也不会 T 。

# Fourth Code
```cpp
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;
#define ll long long
#define il inline
ll n, m, a[100005], sum, ans, shsum, x;
bool b[100005];
il ll nxt(ll x){
	return x == n ? 1 : x + 1;
}
il ll lst(ll x){
	return x == 1 ? n : x - 1;
}
int main(){
	scanf ("%lld %lld", &n, &m);
	for (int i = 1; i <= n; i++){
		scanf ("%lld", &a[i]);
		sum += a[i];
	}
	for (int i = 1; i <= n; i++) ans += a[i] * a[nxt(i)];
	for (int i = 1; i <= m; i++){
		scanf ("%lld", &x);
		b[x] = 1;
		if (!b[nxt(x)]) ans -= a[x] * a[nxt(x)];
		if (!b[lst(x)]) ans -= a[x] * a[lst(x)];
		shsum += a[x];
		ans += a[x] * (sum - shsum);
	}
	printf ("%lld", ans);
	return 0;
}

```

# The end

---

## 作者：BigRooster (赞：0)

# Mishka and trip 题解

**先感慨一句，这是我做过最难的橙题，感觉这道题难度设定虚低了。**

[题目传送门](https://www.luogu.com.cn/problem/CF703B)

## 寒暄部分

先简单讲一下题目的大意，所有城市按顺序连成一个环，相邻两个城市有直接边连接，并且省会城市会和其它所有城市有一条边连接，去除重叠边后求所有边权值之和。一条边的权值等于这条边两个端点的权值相乘。

那么，这道题用一个暴力加图模拟，作为一道橙题，允许 $n^2$ 的复杂度不过分吧——

不幸的是，这道题要求 $n$ 的时间和空间复杂度。

这篇题解会用一个很简单的分类让你不用判重，不用建图就做出这道题目。

## 讲解部分

首先，我们将最后的图分为三个部分，第一个部分是所有省会城市的集合，因为省会城市和所有城市都有连线，所以省会城市之间一定是完全图的关系，换句话说，每两个省会城市之间必有一条连线，下面就是乘积求和的部分了，请看推导：

设所有省会城市权值集合为 $a$，$a_i$ 为第 $i$ 个省会城市的权值，则第一个省会城市的权值一定要被其它所有省会城市的权值乘一遍，第二个省会城市的权值要被后面（第三个到最后一个）所有的省会权值乘一遍（第一个和第二个在第一个中已经乘过了），也就是第一部分的答案和为

$$\sum_{i=1}^{k-1}(\sum_{j=i+1}^{k} a_j \times a_i)$$

其中 $k$ 为省会城市数量。

可能有人会问，这不是 $n^2$ 复杂度吗？但是有没有可能，权值之和我们已经求好了，而每当 $i$ 变化时，我们只要减去 $a_i$ 就能得到 $\sum\limits_{j=i+1}^{k}a_j$ 呢？

显然，只需要输入时求出省会权值之和即可，第一部分计算完毕。

第二部分，是把省会和普通城市连接，并求所有由一个省会和一个普通城市连接的边的权值。这部分更加简单，因为省会权值之和我们已经算出，根据乘法分配律，所有省会城市分别乘普通城市就等于省会城市之和乘普通城市，这时，只需枚举所有节点，用不是省会的城市乘省会城市权值之和，请看推导：

设所有省会城市权值集合为 $a$，非省会城市权值集合为 $b$，则第二部分答案和为

$$(\sum a) \times (\sum b)$$

因为集合 $b$ 题目没有给出，所以使用 $O(n)$ 的复杂度枚举所有不是省会的城市，即可得到集合 $b$。

第三部分，是圆环部分，需要注意，只有两个端点都不是省会时，才能够加入答案中，因为所有带有省会的边都已经做完，虽然也属于判重，但逻辑相比其它办法更加易于理解。

这样，我们就把图分为了三个部分，更加方便答案求解。

## 代码部分

**首先是变量定义部分**

```cpp
int sum1,sum2;//sum1和sum2都是省会权值之和，复制一份方便第一部分的递减操作
int ans;//ans表示最终答案
int n,k;//与题目表述一致
int a[100001];//该节点权值
int b[100001];//省会城市的下标
bool c[100001];//true表示该节点是省会，false表示普通城市
```

**第一部分**

```cpp
for(int i=1;i<=k;i++)
	cin>>b[i],c[b[i]]=true,sum1+=a[b[i]];//sum1就是省会权值之和
sum2=sum1;//复制一份
if(k>1)
	for(int i=2;i<=k;i++)
		sum2-=a[b[i-1]],ans+=a[b[i-1]]*sum2;//先减去前一个省会权值，再用后面的省会权值之和乘前一个省会权值
```

**第二部分**

```cpp
for(int i=1;i<=n;i++)
	if(!c[i])//不是省会的城市
		ans+=sum1*a[i];//用省会权值之和乘普通城市权值
```

**第三部分**

```cpp
for(int i=1;i<n;i++)//防止越界
	if((!c[i])&&(!c[i+1]))//如果当前城市和下一个都不是省会，那么将乘积加入答案
		ans+=a[i]*a[i+1];
if((!c[n])&&(!c[1]))//判定最后一个和第一个（头尾）
	ans+=a[n]*a[1];
```

**将它们结合起来即可得到最终代码**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int sum1,sum2;
int ans;
int n,k;
int a[100001];
int b[100001];
bool c[100001];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	//输入
	for(int i=1;i<=n;i++)
		cin>>a[i];
	//第一部分
	for(int i=1;i<=k;i++)
		cin>>b[i],c[b[i]]=true,sum1+=a[b[i]];
	sum2=sum1;
	if(k>1)
		for(int i=2;i<=k;i++)
			sum2-=a[b[i-1]],ans+=a[b[i-1]]*sum2;
	//第二部分
	for(int i=1;i<=n;i++)
		if(!c[i])
			ans+=sum1*a[i];
	//第三部分
	for(int i=1;i<n;i++)
		if((!c[i])&&(!c[i+1]))
			ans+=a[i]*a[i+1];
	if((!c[n])&&(!c[1]))
		ans+=a[n]*a[1];
	cout<<ans;
	return 0;
}
```

## 总结

这道题是一道思维含量较高的橙题，这个做法应该是最好理解的，当然码量有点高。题解写得有点啰嗦，希望各位见谅。

再见了，祝各位好运！

---

