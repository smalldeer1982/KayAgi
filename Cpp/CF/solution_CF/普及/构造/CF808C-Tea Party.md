# Tea Party

## 题目描述

有n个客人到小名家来玩，他们每人酒杯的容量为a[i],小名家里共有w（w<=a[1]+a[2]+....）容量的酒，他们现在要喝酒，如果满足以下四个条件，证明这个倒酒方法是合法的。
1.每个人倒得酒必须不小于容量的一半
2.每个人倒得酒都是整数
3.所有的酒都倒满了。
4.每个朋友都是快乐的。
如果第a[i]>a[j]但是i装的酒小于j的，那么i是不快乐的。

## 样例 #1

### 输入

```
2 10
8 7
```

### 输出

```
6 4 
```

## 样例 #2

### 输入

```
4 4
1 1 1 1
```

### 输出

```
1 1 1 1 
```

## 样例 #3

### 输入

```
3 10
9 8 10
```

### 输出

```
-1
```

# 题解

## 作者：DarkShadow (赞：4)

# CF808C（贪心）

## 题目大意：

给出数组 $A$ 和 $w$，求一个数组 $B$，满足：

- $B_i \ge \lceil \frac{a}{b} \rceil$

- $\sum_{i=1}^{n} B_i = w$

- 对于所有 $A_i>A_j$，满足 $B_i \ge B_j$

## 思路分析：

本题可以明显看出来是一个贪心。

首先我们可以将 $A$ 数组从小到大（或从大到小）排序，然后每一个杯子先加刚好一半的酒，如果酒不够就说明无解。

如果此时还有剩余的酒，就从最大的杯子开始加，加到最大，这样可以保证答案合法。

## 完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct st{
	int v1,v2,pos;//v1表示当前杯子有多少酒，v2表示杯子容量，pos表示杯子编号
	bool operator <(st oth){
		return v2<oth.v2;
	}
};
st A[105];
int n,w,d[105];
int main(){
	scanf("%d%d",&n,&w);
	for(int i=1;i<=n;i++){
		scanf("%d",&A[i].v2);
		A[i].pos=i,A[i].v1=(A[i].v2+1)/2,w-=A[i].v1;//每个杯子先加一半的酒
	}
	sort(A+1,A+1+n);
	if(w<0){
		printf("-1");//判断无解
		return 0;
	}
	for(int i=n;i>=1&&w;i--)//如果酒还有剩余就从后往前加
		if(A[i].v1+w<=A[i].v2)  A[i].v1+=w,w=0;
		else  w-=(A[i].v2-A[i].v1),A[i].v1=A[i].v2;
	for(int i=1;i<=n;i++)//记录答案
		d[A[i].pos]=A[i].v1;
	for(int i=1;i<=n;i++)
		printf("%d ",d[i]);
	return 0;
}
```

---

## 作者：xiaoxiaoxia (赞：4)

# Part 1 题意分析
$n$ 个茶杯，每个茶杯有容量。现在给一壶茶，总量为 $w$。希望倒茶满足条件：每杯茶要超过容量的一半，并且 $w$ 被倒光，茶杯内的茶水为整数，容量大的杯子内的茶不允许比容量小的杯子内的茶水少。
# Part 2 思路分析
这道题不难证明贪心是可行的，首先特判不满足情况，然后将茶水给每一杯倒至一半以上。然后按照容量从大到小每次倒一个单位，直到倒完为止。这里我们可以使用结构体排序来简单处理，注意这道题是多组数据。
# Part 3 代码部分
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 100 + 10;
int n, w;
struct xx//结构体 
{
    int num, pos;
    int ans;
} a[N];
bool cmp1(xx a, xx b)//从大到小 
{
    return a.num > b.num;
}
 
bool cmp2(xx a, xx b)//从小到大 
{
    return a.pos < b.pos;
}
int main()
{
    while(scanf("%d%d",&n,&w)==2)
	{
        int ww=w;
        int Maxsum=0, Minsum=0;
        for(int i=1;i<=n;i++)
		{
            scanf("%d",&a[i].num);
            a[i].pos=i;
            a[i].ans=a[i].num/2;//贪心 
            if(a[i].num&1)
			{
				a[i].ans++;
			}
            Maxsum+=a[i].num;
            Minsum+=a[i].ans;
            w-=a[i].ans;
        }
        if(ww>Maxsum||ww<Minsum)//特判 
		{
            printf("-1\n");
        }
        else
        {
            sort(a+1,a+1+n,cmp1);
            for(int i = 1; i <= n; i++)
			{
                if(w+a[i].ans>=a[i].num)
				{
                    w-=a[i].num-a[i].ans;
                    a[i].ans=a[i].num;
                }
                else
				{
                    a[i].ans+=w;
                    w=0;
                }
                if(!w) 
				{
					break;
				}
            }
            sort(a+1, a+1+n, cmp2);
            for(int i = 1; i <= n; i++)
			{
                printf("%d%c",a[i].ans, i<n? ' ':'\n');//输出答案 
            }
        }
    }
}
```


---

## 作者：雨过天青 (赞：4)

本题很容易看出来是一个贪心

先把所有酒杯令所有人快乐的最少装的酒求出来

然后依次找容量最大的把酒装满一直把酒装完为止

以下为AC代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>  //头文件
#define MAXX 100+5
using namespace std;
int i,j,k,l,n,w,ans,z,t;
int a[MAXX],d[MAXX],maxx;
bool vis[MAXX];
int main( )
{
	scanf("%d%d",&n,&w);
	for(i=1;i<=n;i++)
	scanf("%d",&a[i]);
	for(i=1;i<=n;i++)
	{
		if(a[i]%2==0) d[i]=a[i]/2;
		else d[i]=a[i]/2+1;
		for(j=1;j<=n;j++)
		if(a[i]>a[j]&&d[j]>d[i])
		d[i]=d[j];
	}                 //每个杯子最少能装多少酒
	for(i=1;i<=n;i++)
	ans+=d[i];
	if(ans>w)         //如果多了 输出
	printf("-1");
	if(ans==w)        //如果刚刚好 输出
	for(i=1;i<=n;i++)
	printf("%d ",d[i]);
	if(ans<w)         //如果少了 开始把多出来的酒倒出来
	{
		ans=w-ans;
		while(ans>0)
		{
			maxx=-1;
			for(i=1;i<=n;i++)      //每次找最大的值
			if(maxx<a[i]&&vis[i]==0)
			maxx=a[i],t=i;
			ans=ans-(a[t]-d[t]);   //然后倒酒 不能超出酒杯容量
			d[t]=a[t];vis[t]=1;
		}                          //我感觉之前的题解是这么错的————没有考虑酒杯容量把剩下的酒全装在一个杯子
		if(ans<0)
		d[t]=d[t]+ans;
		for(i=1;i<=n;i++)
		printf("%d ",d[i]);        //输出
	}
}
```

---

## 作者：hehaitong (赞：1)

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
long long m,n,fl,sum;
long long a[501],b[251];
struct stu
{
	long long c,w;//存体积与序号 
}s[501];
bool cmp(stu x,stu y)
{
	return x.c>y.c;
}
int main()
{
	scanf("%lld%lld",&m,&n);
	for(int i=1;i<=m;i++)
	{
	    scanf("%lld",&a[i]);
	    s[i].c=a[i];
	    s[i].w=i;
	    if(a[i]%2==1)//先将每个杯子中最少要装的体积装入杯中，且要判断奇偶性！！！
		b[i]=(a[i]+1)/2;
		else
		b[i]=a[i]/2;
        fl+=b[i];
	}
	if(fl>n)
    {
    	cout<<-1;
    	return 0;
    }
    if(fl==n)
    {
     	for(int i=1;i<=m;i++)
	   	printf("%lld ",b[i]);
	   	return 0;
    }
    sort(s+1,s+m+1,cmp);//注意，我们要先将体积大的杯子中装入尽量多的酒才能满足条件4 
	sum=n-fl; 
		for(int i=1;i<=m&&sum>0;i++)
		{
		int k=a[s[i].w]-b[s[i].w];//算还能倒入多少 
		if(sum>k)//分两种不同的情况，装得满和装不满 
		b[s[i].w]=a[s[i].w],sum-=k;
		else//两种情况，一定要打else！！！！ 
		if(sum>0&&sum<=k)
		b[s[i].w]+=sum,sum=0;

		if(sum<=0)
		break;
	   }
	   if(sum>0)
	   {
	   	cout<<-1;
	   	return 0;
	   }
	   else
	   {
	   	for(int i=1;i<=m;i++)
	   	printf("%lld ",b[i]);//输出 
	   	return 0;
	   }
}
```

---

## 作者：huangzhixia (赞：1)

挺好的贪心题，有意思。

-------

【**大体解法**】

首先我们观察到需要满足 $4$ 个条件：如下：

- 每个杯子至少有一半的茶水。
 
- 每个杯子的茶水毫升数都是整数。
 
- 茶壶中的所有茶水都倒入杯子中。
 
- 要使所有的朋友都会满意。

大体解法就是贪心，起先将所有茶水按一半分好，每次从大到小倒茶水，直到茶水倒完。

更加细致的分析见下。

----


【**条件 1 分析**】

对于条件 1，为了满足，十分简单，在输入完后，将茶水分一半即可。

但是这里要注意，看第 2 个条件可知，茶水的毫升数必须是**整数**，所以有些情况就不能完完全全的分为相等的两半，这时候就要判断 $a_i$ 能不能被 $2$ 整除，能则直接分，否则在**整除** $2$ 后还需加 $1$。

 
 -----
 
【**条件 2 分析**】 

不需要讲了吧，满足为整数，不用讲，自行结合上面的分析。

-----

【**条件 3 分析**】 

这个条件还是挺重要的。

首先我们想，因为题目中有满足 $w \le \sum _ {i=1} ^ {n} a_i$，所以也就不可能会出现把所有的杯子都倒满了茶水，却还剩下一些茶水的情况，这种情况不必考虑。

还有一种可能的情况就是在起先我们给每个杯子分一半茶水的时候，有可能还没把所有的杯子分完就已经没有茶水了，这个在分茶过程中自行判断即可。

-----

【**条件 4 分析**】

是所有的朋友都满意，就是利用贪心的思想，每次都取当前容量最大的杯子每次倒一个单位的茶水， 

这样循环渐进，即可满足让所有的朋友都满意。

---------

【**代码**】 

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, w, res, pos, a[110], p[110], maxn;
bool pre[110];

int main(){
	scanf("%d%d", &n, &w);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) {
		if (!(a[i] % 2)) 
			p[i] = a[i] / 2;
		else 
			p[i] = a[i] / 2 + 1;
		for (int j = 1; j <= n; j++)
			if (a[i] > a[j] && p[j] > p[i])
				p[i] = p[j];
	}                
	for (int i = 1; i <= n; i++)
		res += p[i];
	if (res > w) {
		puts("-1");
		return 0;
	}
	if (res == w) {
		for (int i = 1; i <= n; i++)
			printf("%d ", p[i]);
		puts("");
		return 0;
	}
	if (res < w) {
		res = w - res;
		while (res > 0) {
			maxn = -1;
			for (int i = 1; i <= n; i++)     
				if (maxn < a[i] && !pre[i]) {
					maxn = a[i];
					pos = i;
				}
			res = res - (a[pos] - p[pos]);  
			p[pos] = a[pos];
			pre[pos] = true;
		}                        
		if (res < 0)
			p[pos] += res;
		for (int i = 1; i <= n; i++)
			printf("%d ", p[i]);      
		puts("");  
	}
}

```

---

## 作者：Frank08 (赞：1)

## 思路

先将酒杯容量 $a$ 从小到大排序，根据题意我们不难发现，此时第 $i$ 个点的答案 $s_i$ 的最小情况是 $\max(s_{i-1}, \lceil \frac{a_i}{2} \rceil)$。当所有答案加起来超过 $w$ 时即为不合法的情况。当酒还有剩余时，将剩余的酒从后往前逐个倒满，直至酒全部倒完为止即可。

## 代码

```cpp
#include <stdio.h>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;

int n,w; pii a[111],s[111];

int main(){
	scanf("%d%d",&n,&w);
	for(int i = 1;i <= n;i++)
		scanf("%d",&a[i].first), a[i].second = i;
	sort(a + 1,a + n + 1);
	for(int i = 1;i <= n;i++){
		s[i].first = a[i].second;
		s[i].second = max((a[i].first + 1) / 2,s[i-1].second);
		w -= s[i].second; 
		if(w < 0){
			puts("-1");
			return 0;
		}
	}
	for(int i = n;w;i--){
		int tmp = min(w,a[i].first - s[i].second);
		s[i].second += tmp;
		w -= tmp;
	}
	sort(s + 1,s + n + 1);
	for(int i = 1;i <= n;i++)
		printf("%d ",s[i].second);
}
```

---

## 作者：2012zxt (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/CF808C)

## 1.思路

本题是一道贪心加排序的题目。

我们可以根据第四条限制条件考虑到将每个人的酒杯容量排序。

于是所有人就形成了一个单调不减的串。

于是我们可以想到，第四条的另一条件也满足了，因为如果我的容量不小于你，那我容量的一半同样不小于你呀。

于是我们就按照这个顺序给所有人倒酒就可以了，在中间看看如果没有酒了就输出 -1 并结束程序。

但如果你这样做…… wa on #9  

接着再看题，发现酒还必须全倒光才行。

这不好办吗？直接从大到小枚举每一次给那个人倒现有的酒的量和他酒杯剩余的量的较小值就可以了。

## 2.代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,w;
struct node{//结构体存编号，容量和答案
	int id,val,ans;
}a[105];
bool cmp(node x,node y){//这里需要两个，一个按容量从小到大，另一个按编号
	return x.val<y.val;
}
bool cmp2(node x,node y){
	return x.id<y.id;
}
int main(){
	cin>>n>>w;
	for(int i=1;i<=n;i++){
		cin>>a[i].val;
		a[i].id=i;
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		w-=(a[i].val+1)/2;//直接向上取整
		a[i].ans=(a[i].val+1)/2;
		if(w<0){//酒连满足最基本的需求都不够了，结束
			cout<<-1;
			return 0;
		}
	}
	for(int i=n;i>=1;i--){//处理剩余的酒
		if(w>0){
		    int tmp=min(w,a[i].val-a[i].ans);
			a[i].ans+=tmp;
			w-=tmp;
		}
		else break;
	}
	sort(a+1,a+1+n,cmp2);
	for(int i=1;i<=n;i++)
		cout<<a[i].ans<<" ";
	return 0;
}

```

---

## 作者：Lavande (赞：1)

# 题目

[LINK！](https://www.luogu.com.cn/problem/CF808C)

# 题意

有 $n$ 个茶杯，每个茶杯都有自身的容量。现在又一壶茶，总量为 $m$，每次倒茶都需要满足以下条件：

1. 每个人倒得茶必须不小于容量的一半。

2. 每个人倒得茶都是整数。

3. 所有的酒都倒满了。

4. 容量大的杯子内的茶比容量小的杯子内的茶水多。

# 算法

贪心

# 思路


首先把每个茶杯令所有人快乐的最少装的茶水求出来，然后按照容量**从大到小**依次将每个茶杯装满，直到茶水倒完为止。这里我们可以使用**结构体**排序来简单处理。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,sum;
struct node{
	int id;  //编号 
	int tea;  //茶杯容量 
	int val;  //方法 
}a[100005]; 

bool cmp1(node a,node b) { //容量从小到大
	return a.tea<b.tea; 
}

bool cmp2(node a,node b) {//编号从小到大
	return a.id<b.id; 
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","m",stdout);
//	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=n;i++){
		cin>>a[i].tea;
		a[i].id=i;  //记录编号 
	}
	sort(a+1,a+n+1,cmp1);
	for(int i=1;i<=n;i++){
		a[i].val=(a[i].tea+1)/2;
		m-=a[i].val;
		if(m<0){
			cout<<-1;
			return 0;
		}
	}
	for(int i=n;i>=1;i--){
		if(m>0){
			sum=min(m,a[i].tea-a[i].val);
			a[i].val+=sum;
			m-=sum;
		}
	}	
	sort(a+1,a+n+1,cmp2);
	for(int i=1;i<=n;i++) cout<<a[i].val<<" ";
	return 0; 
}
```




---

## 作者：Yiyi_52MIYEON1314 (赞：0)

# 题意
给你水的总量 $w$ 和 $n$ 个杯子的容量，分别为 $a_i$。

求一种合法的倒水方案，使得它满足以下要求。

1. 每个杯子，水必不小于杯子容量的一半。
2. 每个杯子中的水必须是整数。
3. 水必须全部倒完，也就是 $w=0$。
4. 若 $a_i>a_j$，则 $i$ 的装水量也不能小于 $j$ 的装水量，也就是 $n$ 杯水为一个单调不下降的序列。

# 思路
- 看到要求 $1$，可以想到先把每一个杯子都刚好加到一半，记得向上取整。这个操作之后如果 $w<0$ 那么输出 $-1$。 
- 看到要求 $4$，我们可以想到**贪心**。把每个杯子的容量从大到小排序，然后依次按最大量加水即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int now,t,id;	//分别为现在有的，容量，变号 
}a[105];
int n,w;
bool cmp(node x,node y){
	return x.t>y.t;
} 
int ans[105];
int main()
{
	cin>>n>>w;
	for(int i=1;i<=n;i++){
		cin>>a[i].t;
		a[i].id=i;
		a[i].now=(a[i].t+1)/2;	//向上取整
		w-=a[i].now;
	}
	sort(a+1,a+n+1,cmp);
	if(w<0){
		cout<<-1;
		return 0;
	}
	for(int i=1;i<=n&&w>0;i++){
		if(a[i].now+w<=a[i].t){
			a[i].now+=w;
			w=0;
		}
		else{
			w-=(a[i].t-a[i].now);
			a[i].now=a[i].t;
		}
	}
	for(int i=1;i<=n;i++){
		ans[a[i].id]=a[i].now;
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
 	return 0;
}

```
### 谢谢！

---

## 作者：tallnut (赞：0)

贪心+排序题。
# 思路
我们依次想想题目中要求的四个条件如何解决。
- Every cup will contain tea for at least half of its volume

  很简单，只要提前给每个茶杯倒上，中途判断茶液还够不够即可。
  
  我们先从小到大排序一次，这样就顺便解决了第④条的要求。因为如果 $a_i>a_j$，那么 $\lceil a_i\div2\rceil\ge\lceil a_j\div2\rceil$ 也恒成立。
- Every cup will contain integer number of milliliters of tea

  在第①条的基础上再加一个向上取整即可。
- All the tea from the teapot will be poured into cups
  
  从后往前扫一遍，贪心地给每个茶杯倒上即可。由于已经从小到大排序过了，容易发现这样从大到小操作，不会影响第④条的结果。
  
最后还需要把编号从小到大排序一次，还原原来的顺序，才能符合题目的输出要求。
# AC 代码
[AC 记录](https://www.luogu.com.cn/record/138409431)。
```
#include <iostream>
#include <algorithm>
using namespace std;
struct cup
{
	int idx;
	int num;
	int ans;
} a[101];
//容量从小到大
bool cmp1(const cup& a,const cup& b) { return a.num < b.num; }
//编号从小到大
bool cmp2(const cup& a,const cup& b) { return a.idx < b.idx; }
int n,w,tmp;
int main()
{
	cin >> n >> w;
	for (int i = 1;i <= n;i++)
	{
		a[i].idx = i;
		cin >> a[i].num;
	}
	sort(a + 1,a + n + 1,cmp1);
	for (int i = 1;i <= n;i++)
	{
		//向上取整做除
		a[i].ans = (a[i].num + 1) >> 1;
		w -= a[i].ans;
		if (w < 0)
		{
			cout << -1;
			return 0;
		}
	}
	for (int i = n;i >= 1;i--)
		if (w > 0)
		{
			tmp = min(w,a[i].num - a[i].ans);
			a[i].ans += tmp;
			w -= tmp;
		}
	sort(a + 1,a + n + 1,cmp2);
	for (int i = 1;i <= n;i++)
		cout << a[i].ans << ' ';
}
```

---

## 作者：0okoukio0 (赞：0)

      第一次发题解，写的不好请见谅。
      首先根据已知分析，如果要让每个酒杯倒上一半，那么至少
      需要让w的值大于等于每个酒杯容量一半的总和。
      
      不过大家都知道C++整形数/2的结果自动向下取整，如果容量
      是一个奇数，那么a[i]/2会小于a[i]的一半，所以要判定这
      个数是奇数或偶数并进行不同处理。
      
```cpp
#include<bits/stdc++.h>
#define N 1000010
#define LL long long
#define UNLL unsigned long long
using namespace std;
int n,w,a[N],b[N],mark[N];
int main(){
	cin>>n>>w;
	int cnt=0;//记录每个酒杯装一半总共要多少酒 
	for(int i=1;i<=n;i++){
		cin>>a[i];//记录每个酒杯的容量 
		if(a[i]&1){//一个数&1 &是按位与 结果为true为奇数，结果为false为偶数 
			cnt+=a[i]/2+1;
			b[i]=a[i]/2+1;//记录每个酒杯中现有的酒 
		}
		else{
			cnt+=a[i]/2;
			b[i]=a[i]/2;
		}
	}
	if(cnt>w){//如果至少装一半都不够，那么找不到题解，输出-1 
		cout<<-1;
		return 0;
	}
	w-=cnt;//如果装一半够了，把倒了一半的酒减掉 
```

      现在我们继续思考剩下的酒怎么处理。
      
      既然要把所有酒全部倒完，并且让所有人全部满意，那么就
      需要从容量最大的开始倒酒，一直到酒被倒完
      
      注意这里有一个误区，不可以把剩下的所有酒全部倒到一个
      人的杯子里，可能会满出来，并且一定要根据容量判定给谁
      倒，因为根据现在有多少酒会让有的样例不满意（我就这么
      错了一回）
      
      同时为了避免死循环，一定要让倒过酒的人标记一下，否则
      循环就会一直进行在一个倒过酒的人上
```cpp
	while(w){
		int big=-1,t;//big记录最大的容量，t为下标 
		for(int i=1;i<=n;i++){
			if(!mark[i]&&a[i]>big){//排除已经倒过酒的人 
				big=a[i];
				t=i;
			}
		}
		mark[t]=1;//这次是第t个杯子倒酒，标记防止下次继续点到这个杯子 
		if(w>a[t]-b[t]){//判定剩下的酒是倒满有多余或是不能倒满 
			w-=a[t]-b[t];
			b[t]=a[t];//直接倒满，并把剩余的酒酒减去倒入的量 
		}
		else{
			b[t]+=w;//倒不满只能把剩下所有的酒全部倒进去 
			w=0;//注意一定别忘记清空w，避免死循环 
		}
	}
	for(int i=1;i<=n;i++){
		cout<<b[i]<<' ';//注意一定要输出当前酒量的数组 
	}
	return 0;
}
```

      希望管理员大大让我通过 这是我想的最简单的代码了
      

---

## 作者：神之影 (赞：0)

首先看下题干
有n个客人到小名家来玩，他们每人酒杯的容量为a[i],小名家里共有w（w<=a[1]+a[2]+....）容量的酒，他们现在要喝酒，如果满足以下四个条件，证明这个倒酒方法是合法的。 1.每个人倒得酒必须不小于容量的一半 2.每个人倒得酒都是整数 3.所有的酒都倒满了。 4.每个朋友都是快乐的。 如果第a[i]>a[j]但是i装的酒小于j的，那么i是不快乐的。 输入格式： 第一行2个整数n，w 接下来一行n个整数，a[i] 输出格式： 输出一种合法的倒酒方法，如果有多解，输出任意1解，如果没有一种合法的，输出-1 样例3解释：没人至少倒得酒之和：5+4+5=14，大于w的10

感谢@Hjl1777 提供的翻译
先分析，首先满足不小于一般，所以a[i]/2,但不小于，所以如果是奇数要+1(因为c++自动向下取整）所以先除2.
先满足(包括输入）：
```cpp
#include<bits/stdc++.h> 
using namespace std;
int main()
{
	int n,v;
	cin>>n>>v;
	int a[n+3];
	for(int i=1;i<=n;i++)
	cin>>a[i];
	int tot=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]%2==0)
		a[i]/=2;
		else
		a[i]=a[i]/2+1;
		tot+=a[i];
	}
```
再处理无解的情况
```cpp
if(tot>v)
	{
		cout<<-1;
		return 0;
	}
	tot=v-tot;
	int t;
```
因为要倒满所有酒并且a[i]>a[j]时到的酒不能小于，所以我想到把多余的给最多的。
```cpp
	int t;//位置 
	int max=-1;
	for(int i=1;i<=n;i++)
	{
		if(a[i]>max)
		{
			max=a[i];
			t=i;
		}
	}
	a[t]+=tot;
	for(int i=1;i<=n;i++)
	cout<<a[i]<<' ';
	return 0;
}
```
第一次发题解，求管理员大大别删。

---

