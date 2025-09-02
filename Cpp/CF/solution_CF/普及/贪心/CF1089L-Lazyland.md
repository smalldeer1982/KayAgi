# Lazyland

## 题目描述

The kingdom of Lazyland is the home to $ n $ idlers. These idlers are incredibly lazy and create many problems to their ruler, the mighty King of Lazyland.

Today $ k $ important jobs for the kingdom ( $ k \le n $ ) should be performed. Every job should be done by one person and every person can do at most one job. The King allowed every idler to choose one job they wanted to do and the $ i $ -th idler has chosen the job $ a_i $ .

Unfortunately, some jobs may not be chosen by anyone, so the King has to persuade some idlers to choose another job. The King knows that it takes $ b_i $ minutes to persuade the $ i $ -th idler. He asked his minister of labour to calculate the minimum total time he needs to spend persuading the idlers to get all the jobs done. Can you help him?

## 说明/提示

In the first example the optimal plan is to persuade idlers 1, 6, and 8 to do jobs 2, 4, and 6.

In the second example each job was chosen by some idler, so there is no need to persuade anyone.

## 样例 #1

### 输入

```
8 7
1 1 3 1 5 3 7 1
5 7 4 8 1 3 5 2
```

### 输出

```
10
```

## 样例 #2

### 输入

```
3 3
3 1 2
5 3 4
```

### 输出

```
0
```

# 题解

## 作者：Molina (赞：2)

# 题目大意：
[题目链接](https://www.luogu.com.cn/problem/CF1089L)

一共有 $ n $ 个人，共有 $ k $ 件事需要完成。在最开始第 $ i $ 个人选择了第 $ a_i $ 份工作，但是由于有些工作可能不会被任何人选到，所以还需要劝一部分人换工作，劝第 $ i $ 个人换工作需要 $ b_i $ 分钟。

求分配工作的最短时间。
# 本题思路：
### 分析：
很水的一道黄题，没有很复杂，**贪心**求解即可。

由题意，第 $ i $ 个人选择了第 $ a_i $ 份工作，劝第 $ i $ 个人换工作需要 $ b_i $ 分钟，不难想到用一个**结构体**来存。另外，本题数据范围为 $ a_i \le k \le n \le 10^5 $，允许我们用**桶**去记录每种工作共有多少人选择。

### 步骤：
按题意输入，输入 $ a_i $ 时用桶去记录，每记录到一种之前未被选择的工作，将 $ k $ 减一。

特判一下，若 $ k $ 已经为 $ 0 $，证明已经做完了 $ k $ 种工作，不用再调整，输出 $ 0 $ 即可。

然后按说服每个懒人的时间给结构体从小到大排序。开一重循环，直接查找，若查到的人选择的工作有多人选择，就可以选择劝此人换工作，将答案累加，在桶中将选择这份工作的人数减一，将 $ k $ 继续减一。当 $ k $ 减到 $ 0 $ 后，证明已经做完了 $ k $ 种工作，退出循环，输出答案即可。

详细讲解请见代码。

# 代码来咯~
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,k,ton[N];
struct cz{//结构体
	int x,y;//x为每个懒人选的工作，y为说服每个懒人的时间 
}a[N];
long long ans=0;//注意开 long long
bool cmp(cz a,cz b){
    return a.y<b.y;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i].x;
		if(ton[a[i].x]==0)  
			k--;
		ton[a[i].x]++;//记录桶数组
	}
	for(int i=1;i<=n;i++)
		cin>>a[i].y;
   if(k==0){//特判
		cout<<"0";
		return 0;
	}
	sort(a+1,a+n+1,cmp);//排序
	for(int i=1;i<=n;i++){
		if(ton[a[i].x]>=2){//判断
			ans+=a[i].y;//累加答案
			ton[a[i].x]--;
			k--;
		}
		if(k==0)//判断，退出循环
			break;
	}
	cout<<ans;//输出答案
	return 0;
}
```

---

## 作者：lbh666 (赞：1)

## 题目大意
国王有 $n$ 位懒人，还有 $k$ 份工作，懒人们各自选了一个工作，但是会有人选相同的工作，于是就得劝他们换工作（劝的时间各不相同），求劝他们的最短总时间。

## 思路
- 不难看出，这是一道贪心的题。

- 从工作编号和劝的时间看，可以开一个**结构体**。

```cpp
const long long N=1e5+5;

struct st{
	long long pot,time; //pot代表工作的编号，time表示劝他们的时间 
}a[N];
```
- 再开一个**桶**数组，取名为 $b$，用来记录每个工作被选了几次。

- 用一个变量 $tot$ 统计没人选的工作，用 $ans$ 来记录答案，再根据劝的时间做快速排序。

- 将结构体遍历一遍，如果工作都有人选了，那跳出循环，直接输出答案 $ans$。

- 如果有，去对应工作编号的桶数组里找，如果数量大于一，就说明可以劝他做其他没人做的工作，而且时间会尽可能的短，符合**贪心**策略，将 $ans$ 和 $tot$ 更新，把桶当前的数量减一。

#### 代码里有更详细的讲解

## AC Code
```cpp
#include<bits/stdc++.h>
#define ll long long    //将long long简写成ll 
using namespace std;

const ll N=1e5+5; 
ll n,k,b[N],ans=0,tot=0;

struct st{
	ll pot,time; //pot代表工作的编号，time表示劝他们的时间 
}a[N];//定义一个结构体来存储pot和time. 

bool cmp(st x,st y){
	return x.time<y.time;
}

int main(){
	cin>>n>>k;  
	for(ll i=1;i<=n;++i){
		cin>>a[i].pot;       
		b[a[i].pot]++;//开个桶记录一下每个工作有多少个人选 
	}
	for(ll i=1;i<=n;++i){
		cin>>a[i].time;
		if(i<=k)if(!b[i])++tot;//在k份工作里，如果有工作没选到，tot+1.     
	}
	sort(a+1,a+n+1,cmp); //对劝他们的时间进行排序，这是贪心的关键 
	for(ll i=1;i<=n;++i){
		if(tot==0)break;  //如果工作都被人选了，退出循环去输出答案 
		if(b[a[i].pot]>1){ //如果这个工作有两人以上选了 
			ans+=a[i].time;   //把劝的时间加进答案 
			--tot;      //已经有人去干其它工作，将tot-1 
			b[a[i].pot]--;   //于是就少一人干这个工作 
		}else continue;    //否则继续找 
	}
	cout<<ans;     //最后输出答案 
	return 0;
}
```

---

## 作者：kimidonatsu (赞：1)

# CF1089L Lazyland 题解

## 题意简述

有 $n$ 位懒人，有 $k$ 件事需要完成，首先每个懒人会选择一份工作 $a_i$，但是由于工作可能没有全部做完，所以国王还需要劝一部分懒人做其他工作，而劝第 $i$ 个懒人干另一份工作需要 $b_i$ 分钟。要求分配所有工作最短时间。

## 思路分析

不妨大胆设想贪心策略，现将愿意做工作的人按 $b_i$ 大小从小到大排列一下。对于 $b_i$ 最大的人尽可能安排他想要做的工作，然后从 $b_i$ 最小的人开始说服直到 $k$ 份工作都有人干。

那么接下来就是我们的代码环节，对于每个懒人建立一个 $node$ 结构体来存储其 $a_i$ 属性和 $b_i$ 属性，之后可以选择 $cmp$ 或者重载运算符来排序，然后就是使用我们的贪心策略进行说服啦。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1e6 + 50;

struct node {
	ll x, y;

	friend bool operator < (const node &a, const node &b) {
		return a.y < b.y;
	}
} a[N];

ll n, k, cnt, ans;
int vis[N];

int main() {
	scanf("%lld %lld", &n, &k);
	for (ll i = 1; i <= n; i++) {
		scanf("%lld", &a[i].x);
		if (vis[a[i].x] == 0) cnt++;
		vis[a[i].x]++;
	}
	for (ll i = 1; i <= n; i++) scanf("%lld", &a[i].y);

	sort(a + 1, a + n + 1);
	for (ll i = 1; i <= n; i++) {
		if (cnt == k) break;
		if (vis[a[i].x] > 1) {
			vis[a[i].x]--;
			cnt++;
			ans += a[i].y;
		}
	}
	printf("%lld\n", ans);
	return 0;
}

```

代码小注：

* 在这里重载了 $node$ 的 $<$ 符号，而不是使用 $cmp$ 函数。
* 通过 $vis$ 数组来判定当前工作是否有多人选可以进行说服调换。
* 对于所有没做完的工作，就按时间从短到长的顺序开始说服懒人。
* 当 $cnt = k$ 时可以结束程序，因为此时所有工作已经安排完了。
* 由于说服时间的数据范围是 $ 1 \le b_i \le 10^9 $ 且 $k$ 和 $n$ 的数据范围是 $ 1 \le a_i \le k $，所以需要开 `long long`。


---

## 作者：A524 (赞：1)

人生中第一道白题！

这题题目意思很简单，直接看题意翻译就行。

做法也很简单，首先找出一个工作中，说服其中一个懒人的最大时间求出，根据贪心的思路，别的懒人肯定是换工作。把剩下的懒人求出，再排一次序（从小到大），依次加上 $m$ - $s$ 个数， $m$为总工作数， $s$ 就是还没有做的工作的数量，减一下就是还没做的工作。

接下来贴上我的代码:
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define maxm 100100
using namespace std;
int i,n,m,t,s,a[maxm],b[maxm],c[maxm],f[maxm],maxn[maxm];
long long sum;
int main(){
	scanf("%d %d",&n,&m);
	for (i=1;i<=n;i++) scanf("%d",&a[i]);
	for (i=1;i<=n;i++) scanf("%d",&b[i]);//输入
	for (i=1;i<=n;i++) s+=1-f[a[i]],f[a[i]]=1;//算出还没有做的工作的数量
	for (i=1;i<=n;i++)
		if (b[i]>b[maxn[a[i]]])
			maxn[a[i]]=i;  //找出一个工作中，说服其中一个懒人的最大时间（用编号记录）
	for (i=1;i<=n;i++)
		if (i!=maxn[a[i]])
			c[++t]=b[i];  //找出剩下的懒人
	sort(c+1,c+1+t);    //再进行一次排序
	for (i=1;i<=m-s;i++) sum+=c[i]; 	//依次取 $m$ - $s$ 个
	printf("%lld\n",sum); 	//输出
	return 0;
} 
```
怎么样，是不是很简单。


---

## 作者：欣逸 (赞：1)

感觉这题还简单

不管做每个工作的人里面的说服时间最长的人，将其他的人的时间排序找出最小的就行

读入n和k

首先把数据分别存入结构体，然后按照说服时间从大到小进行排序

接下来遍历结构体，将第一个做某个工作的人（也就是最难说服的人）忽略，将其他的人的说服时间加入一个数组time中，并统计最初有多少个工作被做（设这个为count）。最后将time数组排序，选出前k-count个相加即为结果

代码如下：
```cpp
#include <algorithm>
#include <cstdio>
using namespace std;
struct person{
    int t,x;
}a[100005];		//定义结构体
bool cmp(person x,person y){
    return x.t>y.t;
}
int main(){
    int count,p,c[100005]={0};//c数组用来记录工作是否有人选过
    long long ans=0;
    count=p=0;
    int time[100005]={0};
    int per,n;
    scanf("%d %d",&per,&n);
    //读入数据
    for(int i=0;i<per;i++)
    	scanf("%d",&a[i].x);
    for(int i=0;i<per;i++)
    	scanf("%d",&a[i].t);
    //排序
    sort(a,a+per,cmp);
    for(int i=0;i<per;i++){
        if(c[a[i].x]){
            time[p++]=a[i].t;
        }
        else{
        count++;
        c[a[i].x]=1;
        }
    }
    sort(time,time+p);
    for(int i=0;i<n-count;i++){
        ans+=time[i];
    } 
    printf("%lld",ans);
}
```


---

## 作者：xxxxxzy (赞：0)

#### CF1089L 的题解

简单贪心。

很容易想到贪心策略，劝 $b_{i}$ 比较小并且选的工作有人选了的矮人。

所以只需要拿个桶记录一下选这份工作的人，然后按 $b_{i}$ 从小到大排序，判断当前矮人是否能被拿去干其他事，再累加答案就行了。


#### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long//记得开 long long
using namespace std;
int f[100005],n,k,tot,ans,s[100005];
struct m{
	int a,b;
}tt[100005];
bool cmp(m q,m p){
	return q.b<p.b;
}
signed main(){
	cin>>n>>k;
	for(int i=0;i<n;i++){
		cin>>tt[i].a,f[tt[i].a]++;
		if(f[tt[i].a]==1) k--;//当前这个工作已被选，总工作量 -1
	}
	for(int i=0;i<n;i++) cin>>tt[i].b;
	sort(tt,tt+n,cmp);//排序
	for(int i=0;i<n;i++){
		if(k==0) break;//完成工作
		if(f[tt[i].a]>=2) k--,f[tt[i].a]--,ans+=tt[i].b;//当前矮人可以去做未被选的工作
	} 
	cout<<ans;
}
```



---

## 作者：Shanganze (赞：0)

很水的一道贪心啊。

我们很容易就能想到要先选择说服时间短的人进行说服，但是说服这跟人的前提是他所做的工作有多人选择，一直这样选择到所有工作都有人做。应定要开 **long long**。
### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct a1{
	int a,b;
}x[100001];
bool a2(a1 a,a1 b){return a.b<b.b;}
int v[100001];
signed main(){
	int n,k,p=0,ans=0;
	cin>>n>>k;
	for(int q=1;q<=n;q++)
	{
		cin>>x[q].a;
		if(v[x[q].a]==0)p++;
		v[x[q].a]++;
	}
	for(int q=1;q<=n;q++)
	{
		cin>>x[q].b;
	}
	sort(x+1,x+1+n,a2);
	for(int q=1;q<=n;q++){;
		if(p==k)break;
		if(v[x[q].a]>1){
			v[x[q].a]--;
			p++;
			ans+=x[q].b;
		}
	}
	cout<<ans;
	return 0;
}
```



---

## 作者：ran_qwq (赞：0)

给愿意做每个工作的人的 $b_i$ 从大到小排序一遍。对于每个工作 $b_i$ 最大的人一定做他喜欢的工作。设有 $k$ 个工作没人选，则其他的人中选 $b_i$ 最小的 $k$ 个做这 $k$ 个工作。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n,m,k,a[N],b[N],p[N],len,ans;
vector<int> v[N];
bool cmp(int x,int y)
{
	return x>y;
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cin>>b[i],v[a[i]].push_back(b[i]);
	for(int i=1;i<=m;i++)
	{
		if(v[i].empty())
			k++;
		sort(v[i].begin(),v[i].end(),cmp);
	}
	for(int i=1;i<=m;i++)
		for(int j=1;j<v[i].size();j++)
			p[++len]=v[i][j];
	sort(p+1,p+1+len);
	for(int i=1;i<=k;i++)
		ans+=p[i];
	cout<<ans;
}
```


---

## 作者：user470883 (赞：0)

话说这一场题难度没排好吧，估摸着最多普及-放到 $L$ 题去了。。。

## 思路：

贪心。

输入进来以后，我们先扫描一遍，找出没人干的工作。

然后就要有贪心的思想，如果有两个以上的人干同一份工作的话，由于一份工作一个人干就可以完成，我们就可以劝服这几个人里面最好劝服的（也就是 $b_i$ 最小的），直到每个人都有了工作，输出劝服所花的时间。

**具体实现**：

我们输入进来，每一次都选择**工作时间最小的且和别人干一个工作的**即可。

代码略，如果您的代码有问题可以私信找我帮您找错。

---

## 作者：Patpowder (赞：0)

# CF1089L Lazyland 题解
推荐难度 **普及-** ~ **入门**。

[题目转送门](https://www.luogu.com.cn/problem/CF1089L) 和 [更好的阅读服务](https://www.luogu.com.cn/blog/patpowder-114514/solution-cf1089l) 一站式服务。


## 正片开始

一看，题目说是第 $i$ 个懒人选择了第 $a_i$ 项工作，劝说第 $i$ 个懒人需要 $b_i$ 分钟，咱不难想到用 **结构体** 来做。


```cpp
struct lan{
	ll a, b;
}l[N];

```


---


其实还有一个坑点（？


举个栗子：


假如有 $3$ 个懒人和 $2$ 份工作，


则耗时最多的那个懒人的劝说时间可以忽略不计


也就是所有的懒人分配完时候剩下那些要劝换工作人人中，不一定有那么多工作给所有人做，所以那些就是不肯换工作的可以不用计入总时间，忽略不计。

---

接下来就是主要思路了。


大概流程长这个样：


1. 定义变量，数组；
2. 用 ``sort()`` 从大到小排个序；
3. 循环 $n$ 次查看有没有选重复工作的懒人，如果有，则把劝说时间偏短的懒人加入数组；
4. 再次用 ``sort()`` 从小到大排序；
5. 循环 $vs-(n-k)$ 次（ 则 多余懒人数量 - ( 懒人数量 - 工作数量 ) 为要劝说的懒人 ）统计劝说时间；
6. 输出。


# AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+50;
typedef long long ll;
struct lan{
	ll a, b;
}l[N];
ll n, k, ans;
ll v[N], vs;
bool flag[N] = {false};

int main() {
	cin>>n>>k;
	
	for(ll i=1;i<=n;++i)
		cin>>l[i].a;
	for(ll i=1;i<=n;++i)
		cin>>l[i].b;

	sort(l+1, l+n+1, [](lan a, lan b){
		return a.b > b.b;
	});
	
	for(ll i=1;i<=n;++i){
		if(flag[l[i].a] == false)
			flag[l[i].a] = true;
		else {
			vs++;
			v[vs] = l[i].b;
		}
	}

	sort(v+1, v+vs+1, [](lan a, lan b){
		return a.b > b.b;
	});

	for(ll i=1;i<=vs-(n-k);++i){
		ans += v[i];
	}

	cout<<ans;
	return 0;
}
```

---

