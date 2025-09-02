# Bertown Subway

## 题目描述

The construction of subway in Bertown is almost finished! The President of Berland will visit this city soon to look at the new subway himself.

There are $ n $ stations in the subway. It was built according to the Bertown Transport Law:

1. For each station $ i $ there exists exactly one train that goes from this station. Its destination station is $ p_{i} $ , possibly $ p_{i}=i $ ;
2. For each station $ i $ there exists exactly one station $ j $ such that $ p_{j}=i $ .

The President will consider the convenience of subway after visiting it. The convenience is the number of ordered pairs $ (x,y) $ such that person can start at station $ x $ and, after taking some subway trains (possibly zero), arrive at station $ y $ ( $ 1<=x,y<=n $ ).

The mayor of Bertown thinks that if the subway is not convenient enough, then the President might consider installing a new mayor (and, of course, the current mayor doesn't want it to happen). Before President visits the city mayor has enough time to rebuild some paths of subway, thus changing the values of $ p_{i} $ for not more than two subway stations. Of course, breaking the Bertown Transport Law is really bad, so the subway must be built according to the Law even after changes.

The mayor wants to do these changes in such a way that the convenience of the subway is maximized. Help him to calculate the maximum possible convenience he can get!

## 说明/提示

In the first example the mayor can change $ p_{2} $ to $ 3 $ and $ p_{3} $ to $ 1 $ , so there will be $ 9 $ pairs: $ (1,1) $ , $ (1,2) $ , $ (1,3) $ , $ (2,1) $ , $ (2,2) $ , $ (2,3) $ , $ (3,1) $ , $ (3,2) $ , $ (3,3) $ .

In the second example the mayor can change $ p_{2} $ to $ 4 $ and $ p_{3} $ to $ 5 $ .

## 样例 #1

### 输入

```
3
2 1 3
```

### 输出

```
9
```

## 样例 #2

### 输入

```
5
1 5 4 3 2
```

### 输出

```
17
```

# 题解

## 作者：小明小红 (赞：1)

# CF884C 题解
**题目性质**：这是一道适合初学者**深搜**的**思维**题。

**循环节**：由于本题的指向是 $1$ 至 $n$ 且不重复，我们可以容易地发现几个数字互相指向形成一个循环节，整个数组就变成了**多个**循环节。

**如何求便利度**：dfs 可以求每个**循环节**及其**含元素个数**，最后计算即可。

**便利度**：题目中**便利值**的定义其实就是一个循环节不同起点终点方案的**数量**，其实就是若本循环节的由 $x$ 个数字**构成**，那么本循环节的总便利度是 $x^{2}$。

**思维题**：题目里说了最多改变 $2$ 个数字，且无论是改前改后**总共**都是 $1$ 至 $n$，所以易得前后要么不变要么交换两个数字，接下来我们**分类讨论**。

**不交换**：不交换其实就是每个循环节的便利度之**和**。

**交换**：交换只有两种情况，第一种是把一个长为 $x+y$ 的循环节拆成长为 $x$ 和 $y$ 的循环节。第二种是把一个长为 $x$ 和一个长为 $y$ 的循环节**合成**一个长为 $x+y$ 的循环节，接下来我们来算一算哪个长。

**拆解**最终便利度：$x^2+y^2$

**合成**最终便利度：$(x+y)^2=x^2+y^2+2xy$

明显，由于 $x$ 和 $y$ 都是正数，所以**合成**的便利度明显**大于拆解**和**不合成**，所以为了便利度更大，我们将**最大**的两项合成，然后每项求便利度**相加**即可。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,size[100009],a[100009],ans;//size[i]表示以i为代表的循环节的大小，0说明被标记过了，1说明没有dfs过 
void dfs(ll x) {
	ans++;
	size[x]=0;//标记 
	if(size[a[x]]==1) {
		dfs(a[x]);
	}

}
int main() {
	cin>>n;
	for(ll i=1; i<=n; i++) {
		cin>>a[i];
		size[i]=1;//初始化每个循环节大小都为1 
	}
	for(ll i=1; i<=n; i++) {
		ans=0;
		if(size[i]==1) {
			dfs(i);
		}
		size[i]=ans;//统计元素数量 
	}
	sort(size+1,size+n+1);//排个序求最大次大和其他 
	ll sum=(size[n]+size[n-1])*(size[n]+size[n-1]);//最大次大合并 
	for(ll i=1; i<n-1; i++) {
		sum+=size[i]*size[i];//其他的循环节 
	}
	cout<<sum;
	return 0;
}
```
到现在就能**通过**这道题，但是现在这份代码的时间复杂度最多的竟然是**排序**的 $O(n\log n)$，所以我们可以通过乱七八糟的**循环**能把**求最大次大和其他**的功能由 $O(n)$ 完成，这样总代码的时间复杂度是 $O(n)$，遥遥领先！

这篇题解到这里就结束了，如果你有任何疑问或者找出任何错误可以在评论区联系我，我看到会及时回复。

---

## 作者：yuheng_wang080904 (赞：1)

## 题意

给出一个长度为 $n(1\le n\le 10^5)$ 的排列 $p_1,p_2,\cdots,p_n$。你可以修改最多两个位置，修改完后必须还是排列。使得修改完后的排列中满足以下条件的 $(x,y)$ 对数最多：从 $x$ 出发，通过
`x->p[x]->p[p[x]]->…->y`
能够走到 $y$。(允许 $x=y$ )

## 思路

这题的图必定是由几个环构成的。环上的任意两点 $i,j$ 都满足条件，因此这个环(环长为 $l$ )上符合要求的对数为 $l^2$ 对。

允许修改两个位置，但改完后仍是排列，其实上就是让你交换某个 $p_i$ 和 $p_j$。自己造几个样例试一试就知道，交换 $p_i$ 与 $p_j$ 共有两种情况。第一种是将两个环合并，第二种是讲一个环拆开。由 $(a+b)^2-(a^2+b^2)=2ab>0\space(a,b>0)$ 可知，为了使得对数最多，我们只能是将两个环长最大的环合并。

代码思路：首先 DFS (简单化)求环长，然后合并两个环，求出答案。

## 代码

接下来放上我的代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,p[100005],c[100005],cnt,maxi,maxj,ans;
bool vis[100005];
void dfs(int x){
    long long res=0;
    while(!vis[x]){
	vis[x]=1;
	res++;
	x=p[x];
    }
    c[++cnt]=res;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>p[i];
    for(int i=1;i<=n;i++){
	if(!vis[i])dfs(i);
    }
    sort(c+1,c+1+cnt);
    for(int i=1;i<=cnt-2;i++)ans+=c[i]*c[i];
    ans+=(c[cnt-1]+c[cnt])*(c[cnt-1]+c[cnt]);
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：流绪 (赞：1)

这题我吐了,Bertown Transport Law 看了一年才理解!!!

粗略地看,每个 i 点都有一个目的地 j,好像没啥用,想了半天还是不会写,搜了搜之后一脸懵逼,啥玩意?成环??? 2->1 1->1 直接 hack 了好吗?然后继续找,全世界都是说必成环,然后又读了半小时题,终于让我发现了!!!

exists exactly 存在确定的一条路线!!!

所以每个点都有一个目的地,而且这个目的地只能由这个点前往!!!然后就必定成环了...感觉我在写英语阅读理解...

其实上面的也是我猜的...强行解释为什么成环,如果有大佬知道为什么,请私信我!!!谢谢!!!

**正文**

必成环就好写多了,先跑一遍每个点,看看有几个环,然后把每个环内含几个点记录下来

然后对于每个环来计算它的舒适度,设舒适度为 S,环内点数量为 a

环内每个点都能互相到达,所以每个点的舒适度就是 a ,所以 S=a*a;

那怎么修改呢?显然对于把几个环的舒适度相加 S1=a1*a1+a2*a2+a3*a3+...

把几个环合并起来 S2=(a1+a2+a3+...)^2

根据完全平方展开式,显然 S2>S1,且合并后的增加量是 a1*a2*a3...

所以我们要找几个环来合并,只能该两次,刚好合并两个环,那我们排序,将最大的两个环合并就行啦!

下面是 AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[100010];
int v[100010]={0};
ll b[100010];
int main()
{
	ios::sync_with_stdio(false);
	ll n;
	cin >> n;
	for(int i=1;i<=n;i++)
		cin >> a[i];// i 开往 a[i] 
	ll ans=0,p=0;
	for(int i=1;i<=n;i++)
	{
		if(v[i])
			continue;
		ll cnt = 1;
		ll x = a[i];
		v[x] = 1;
		while(x!=i)
		{
			x=a[x];
			v[x] = 1;
			cnt++;
		}
		b[p++] = cnt;//每一个环有几个站 
		ans += cnt*cnt;
	}
	if(p==1)
		cout << ans;
	else
	{
		sort(b,b+p);
	//	cout << b[p-1] << " " << b[p-2] <<endl;
		ans += b[p-1]*b[p-2]*2;
		cout << ans;
	}
} 
```


---

