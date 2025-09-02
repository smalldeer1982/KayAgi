# Deep Down Below

## 题目描述

In a certain video game, the player controls a hero characterized by a single integer value: power. The hero will have to beat monsters that are also characterized by a single integer value: armor.

On the current level, the hero is facing $ n $ caves. To pass the level, the hero must enter all the caves in some order, each cave exactly once, and exit every cave safe and sound. When the hero enters cave $ i $ , he will have to fight $ k_i $ monsters in a row: first a monster with armor $ a_{i, 1} $ , then a monster with armor $ a_{i, 2} $ and so on, finally, a monster with armor $ a_{i, k_i} $ .

The hero can beat a monster if and only if the hero's power is strictly greater than the monster's armor. If the hero can't beat the monster he's fighting, the game ends and the player loses. Note that once the hero enters a cave, he can't exit it before he fights all the monsters in it, strictly in the given order.

Each time the hero beats a monster, the hero's power increases by $ 1 $ .

Find the smallest possible power the hero must start the level with to be able to enter all the caves in some order and beat all the monsters.

## 说明/提示

In the first test case, the hero has to beat a single monster with armor $ 42 $ , it's enough to have power $ 43 $ to achieve that.

In the second test case, the hero can pass the level with initial power $ 13 $ as follows:

- enter cave $ 2 $ : 
  - beat a monster with armor $ 12 $ , power increases to $ 14 $ ;
  - beat a monster with armor $ 11 $ , power increases to $ 15 $ ;
- enter cave $ 1 $ : 
  - beat a monster with armor $ 10 $ , power increases to $ 16 $ ;
  - beat a monster with armor $ 15 $ , power increases to $ 17 $ ;
  - beat a monster with armor $ 8 $ , power increases to $ 18 $ .

## 样例 #1

### 输入

```
2
1
1 42
2
3 10 15 8
2 12 11```

### 输出

```
43
13```

# 题解

## 作者：sunzz3183 (赞：8)

# CF1561C Deep Down Below

## 题意

就是一个类似这样的游戏：

![](https://cdn.luogu.com.cn/upload/image_hosting/vwzesdtn.png)

唯一的不同就是一个洞里有 $k_i$ 只怪物，你要按顺序击杀洞内每一只怪物，每击杀一只怪物会获得 $1$ 点力量。现在你可以任意选择洞的路线，请你求出击杀所有怪物的最小初始力量。

## 分析

我们先看题：**按顺序击杀洞内每一只怪物**。即，每到达一个洞，你就无法退出，并且击杀顺序无法改变。所以，你可以在输入时预处理出打败每个洞的最小力量 $d_i$ 。

代码（预处理）：

```cpp
for(int i=1;i<=n;i++){
	q[i]=i;//记录标记，排序用，后面会讲
	scanf("%d",&k[i]);
	int a,num;//num来记录当前的你的力量
	scanf("%d",&a);
	d[i]=num=a+1;
	for(int j=2;j<=k[i];j++){
		num++;//每击杀一个怪物就+1
		scanf("%d",&a);
		if(a>=num){ //如果当前力量不够了
			int t=num;
			num=a+1;//力量更新到当前怪的盔甲+1
			d[i]+=(num-t);//最小力量增加
		}
	}
}
```
 
然后，继续看题：**每击杀一只怪物会获得 $1$ 点力量**。也就是说：每进入一个洞，你就可以获得 $k_i$ 点力量。

这时你发现，题目转化成：给你 $n$ 个洞，每个洞里有一只怪，你击杀它需要 $d_i$ 点力量,击杀后会获得 $k_i$ 点力量，请你求出击杀所有怪物的最小初始力量

然后，我们从小到大排个序，做贪心：

```
sort(q+1,q+n+1,cmp);
```

cmp ：

```
bool cmp(int x,int y){
	return d[x]<d[y];
}
```
贪心：

```cpp
//sum经过每个洞后的力量
//ans初始力量
sum=ans=d[q[1]];//初始化
for(int i=2;i<=n;i++){
	sum+=k[q[i-1]];//加上走过的洞
	if(sum<d[q[i]])//力量不够了
		ans+=(d[q[i]]-sum),sum+=(d[q[i]]-sum);//更新
}
```

证明：我们已经得到了打败每个洞的力量。现在假设我们打败当前的洞的力量不是所有洞中最小的，那么我们打败当前的洞的力量肯定可以打败其他的力量比它小的洞。 此时我们打败这些洞后力量一定会增加（因为 $1\leq k_i$ ），而再通过当前洞时就会有**多余的力量**，所以我们要从最小的洞开始**贪心**，当力量不足时，就加上**不足的力量**。


## 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n,ans,sum;
int k[100010],d[100010],q[100010];
bool cmp(int x,int y){
	return d[x]<d[y];
}
int main(){
	scanf("%d",&T);
	while(T--){
		memset(d,0,sizeof(d));
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			q[i]=i;
			scanf("%d",&k[i]);
			int a,num;
			scanf("%d",&a);
			d[i]=num=a+1;
			for(int j=2;j<=k[i];j++){
				num++;
				scanf("%d",&a);
				if(a>=num){
					int t=num;
					num=a+1;
					d[i]+=(num-t);
				}
			}
		}
		sort(q+1,q+n+1,cmp);
		sum=ans=d[q[1]];
		for(int i=2;i<=n;i++){
		    sum+=k[q[i-1]];
		    if(sum<d[q[i]])
				ans+=(d[q[i]]-sum),sum+=(d[q[i]]-sum);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```




---

## 作者：LinkZelda (赞：4)

- **题意**：

$T$ 组数据，每次给定 $n$ 个任务，第 $i$ 个任务给定 $k_i$ 个怪物，每个怪物有一个能力值 $a_{i,j}$ 你要按顺序把这 $k_i$ 个怪物杀死，你能杀死一个怪物当且仅当你的能力值严格大于怪物的能力值，杀死一个怪物后，你的能力值将会 $+1$。

你可以按任意顺序完成这 $n$ 个任务，你需要确定最小的初始能力值。

$T\leq 10^5,n\leq 10^5,k_i\leq10^5,\sum k_i\leq 10^5,a_{i,j}\leq 10^9$。

- **做法**：

随着初始能力值越大，越可能满足条件，即满足可二分性。

二分初始能力值，考虑如何 `check`。

对于一个任务 $i$，打任务中的第 $j$ 个怪物前，会获得 $j-1$ 的能力加成，那么我们把一个任务中的所有怪物的能力值 $a_{i,j}$ 改为 $a_{i,j}-(j-1)$ 之后取最大值，就是能完成这个任务的最低能力值了。

我们把所有任务按上面算出来的完成最低能力值从小到大排序，然后扫一遍即可，如果中间打不过就直接 `return false;` 即可。

时间复杂度为 $O(n\log \max(a_{i,j}))$。

- [代码](https://www.luogu.com.cn/paste/szo16kyd)

---

## 作者：KSToki (赞：2)

题外话：个人觉得 C 比 A 简单（可能只有我开始把 A 想复杂了）。
# 题目大意
有 $n$ 个关卡，第 $i$ 个关卡有 $k_i$ 个敌人。每个敌人的都有一个防御值，当你的力量严格大于敌人的防御值时你才能打败他，每打败一个敌人你的力量就会加一。进入一个关卡后必须打完，问初始力量至少要为多少才能通关。
# 题目分析
由于进入一个关卡后必须打完，所以可以直接算出进入该关卡所需的最低力量，那么题目就可以转化为：有 $n$ 个关卡，通过第 $i$ 个关卡力量至少为 $a_i$，通过后力量会增加 $k_i$，问初始力量至少要为多少才能通关。

这个时候我们就可以贪心了，将关卡按 $a$ 排序，从小往大打。假设这种方法是错误的，那么一定有一次必须先打 $a_i$ 高的。既然能打 $a_i$ 高的，那么一定能过低的，并且过了后力量还会增加，所以假设不成立，即贪心正确。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,Mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,x;
struct stu
{
	int k,a;
}b[100001];
I bool cmp(stu b1,stu b2)
{
	return b1.a<b2.a;
}
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		For(i,1,n)
		{
			b[i].k=read();
			b[i].a=0;
			For(j,0,b[i].k-1)
			{
				x=read();
				chkmax(b[i].a,x-j);
			}
		}
		sort(b+1,b+n+1,cmp);
		int ans=0,now=0;
		For(i,1,n)
		{
			if(now<=b[i].a)
			{
				ans+=b[i].a+1-now;
				now=b[i].a+1;
			}
			now+=b[i].k;
		}
		putint(ans);
	}
	return 0;
}

```

---

## 作者：luckydrawbox (赞：0)

## 分析

首先可以确定的两点是：

- 每个洞穴是互不干扰的。也就是说，第 $i$ 个洞穴能否通过，只和来第 $i$ 个洞穴前的 $power_i$ 有关。

- 必然存在一个 $power_i'$，使得 $power_i<power_i'$ 时，过不了这个山洞；$power_i\ge power_i'$ 时，能过这个山洞。

既然这样，我们就可以预处理出能过第 $i$ 个洞穴的最小的 $power_i$。

如何求呢？我们先给 $power_i$ 赋一个最小值 $0$，一个一个地经过怪物，面对怪物 $a_{i,j}$ 时，英雄的 $power$ 为 $power_i+j-1$，如果 $power_i+j-1<a_{i,j}+1$，说明 $power_i$ 太小了，我们要把它调到符合要求的最小值 $power_i+j-1=a_{i,j}+1$，也就是令 $power_i\Leftarrow a_{i,j}+2-j$。

经过第 $i$ 个洞穴的所有怪物后，我们就得到了第 $i$ 个洞穴需要的最小的 $power_i$。

接下来我们要求经过所有洞穴需要的最小力量 $ans$，我们可以把每个洞穴按照 $power_i$ 从小到大排序，排序时带上洞穴的怪物数量 $k_i$。

接下来我们一个一个经过山洞 $i$，并记录前 $i-1$ 个山洞的怪物数量前缀和 $sum_{i-1}$。

然后和前面怪物的计算方法一样，把山洞当成怪物，面对山洞 $i$ 时，英雄的 $power$ 为 $ans+sum_{i-1}$，如果 $ans+sum_{i-1}<power_i$，说明 $ans$ 太小了，我们要把它调到符合要求的最小值 $ans+sum_{i-1}=power_i$，也就是令 $ans\Leftarrow power_i-sum_{i-1}$。

最后的 $ans$ 即为所求。

时间复杂度 $O(tn\log n)$，主要是排序。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int t,n,ans,a_i_j,sum;
struct asdf{
	int power,k;
}b[N];
bool cmp(asdf x,asdf y){
	return x.power<y.power;
}
int main(){
    scanf("%d",&t);
    while(t--){
    	scanf("%d",&n);
    	ans=sum=0;
    	for(int i=1;i<=n;i++){
    		b[i].power=0;
    		scanf("%d",&b[i].k);
    		for(int j=1;j<=b[i].k;j++){
    			scanf("%d",&a_i_j);
    			b[i].power=max(b[i].power,a_i_j+2-j);
			}
		}
		sort(b+1,b+n+1,cmp);
		for(int i=1;i<=n;i++){
			ans=max(ans,b[i].power-sum);
			sum+=b[i].k;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：jinxdtaiy (赞：0)

### 题意简述

- 有 $n$ 个洞穴，第 $i$ 个洞穴里有 $k$ 个怪物，你每杀死一个怪物，你的武力值就加一，你能杀死这个怪物，当且仅当你的武力值严格大于这个怪物的武力值，求出你杀死所有怪物需要的最小初始武力值。

### 分析

- 贪心和模拟

- 我们可以先求出通关每个洞穴的最小初始值，然后对这些初始值进行排序，然后从最小初始值的洞穴开始打怪，模拟打怪的过程即可。

```
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define req(i,j,k) for(int i=j;i>=k;i--)
#define rex(i,j,k) for(int i=j;i<k;i++)
#define rey(i,j,k) for(int i=j;i>k;i--)
#define maxn 100005
#define int long long
using namespace std;
struct jin{
	int k,power;
}f[maxn];
int cmp(jin x,jin y)
{
	return x.power<y.power; 
}
int t,n,m,ans,a[maxn];
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		//求初始武力值 
		for(int i=1;i<=n;i++)
		{
			cin>>f[i].k;
			for(int j=1;j<=f[i].k;j++)
			cin>>a[j];
			f[i].power=a[1]+1; 
			int qwq=f[i].power;
			for(int j=2;j<=f[i].k;j++)
			if(qwq>a[j]) qwq++;
			else f[i].power+=a[j]-qwq,qwq=a[j]+1;
		}
		sort(f+1,f+1+n,cmp);
		ans=f[1].power;
		int kk=ans;
		//模拟打怪 
		for(int i=1;i<=n-1;i++)
		{
			if(kk+f[i].k<=f[i+1].power) ans+=f[i+1].power-(kk+f[i].k),kk=f[i+1].power;
			else kk+=f[i].k;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：引领天下 (赞：0)

由于每个洞穴是独立的，而每个洞穴里的怪必须按顺序全部打完，所以可以考虑预处理出想打穿每个洞穴所需要的初始攻击力。

在考虑进入洞穴的顺序时，显然应从最容易打穿的开始（进简单的，然后后面见机行事补初始攻击力一定不劣。）

那么一个贪心就做完了。$\color{black}\colorbox{black}{话说这种东西不应该放在2A吗}$

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n;
struct Node{
    int k,id,cnt;//一开始写的时候还觉得可能要记住进入的顺序，后面发现不需要输出进入顺序，所以这个id是不必要的。
    inline bool operator<(const Node&p)const{
        return k^p.k?k<p.k:cnt>p.cnt;
    }
}b[100005];
vector<int>a[100005];
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n;
        for(register int i=1;i<=n;i++)b[i].k=0;
        for(register int i=1;i<=n;i++){
            cin>>b[i].cnt;b[i].id=i;
            a[i].resize(b[i].cnt+2);
            for(register int j=1;j<=b[i].cnt;j++){
                cin>>a[i][j];
                b[i].k=max(b[i].k,a[i][j]-(j-1));//打第j个怪时前面打了j-1个
            }
        }
        sort(b+1,b+n+1);
        int ans=b[1].k+1,x=b[1].k+1;//攻击力需要严格大于，所以+1
        for(register int i=1;i<=n;i++)if(x>b[i].k)x+=b[i].cnt;else ans+=b[i].k-x+1,x=b[i].k+1+b[i].cnt;//够就直接进，不够就补初始攻击
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：wanggiaoxing (赞：0)

### 分析算法
我们看到最小值很容易想到二分，但是这题二分如何判断这一值能否平安打完怪呢？我们又想到了贪心，显然我们可以先二分出每个洞穴所需的最小值，然后按这个值从小往大排，然后再二分最终所需的值，这里的检查便轻松许多，我们只需要按照排好的顺序判断当前值是否大于等于此洞穴所需的最小值，大于等于了就让当前值加上此洞穴的怪物个数，否则让二分的值加上目前的答案。

代码如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')w=-1;
        ch=getchar();
    }
    while(ch<='9'&&ch>='0')s=s*10+ch-'0',ch=getchar();
    return s*w;
}
struct node{
    int id,val;
}a[100005];
vector<int>v[100005];
int t,n;
bool check(int val,int id){
    for(int i=0;i<(int)v[id].size();i++){
        int x=v[id][i];
        if(val>x)val++;
        else return 0;
    }
    return 1;
}
bool cmp(node a,node b){
    return a.val<b.val;
}
signed main()
{
    t=read();
    while(t--){
        n=read();
        for(int i=1;i<=n;i++){
            v[i].clear();
            int k=read();
            for(int j=1;j<=k;j++)
                v[i].push_back(read());
            int ans=0;
            for(int j=(1<<29);j;j>>=1)
                if(!check(ans+j,i))ans+=j;
            a[i].id=i;
            a[i].val=ans;
        }
        sort(a+1,a+1+n,cmp);
        int ans=0;
        for(int j=(1<<29);j;j>>=1)
        {
            int k=ans+j;
            bool flag=0;
            for(int i=1;i<=n;i++)
                if(k>=a[i].val)k+=v[a[i].id].size();
                else{
                    flag=1;
                    break;
                }
            if(flag==1)ans+=j;
        }
        ans+=2;
        printf("%d\n",ans);
    }
    return 0;
}
```


---

## 作者：reailikezhu (赞：0)

单独考虑每个洞。

第 $i$ 个洞的第 $j$ 关，如果把它当做第一个洞打，所需的战斗力是 $a_{i,j}-j+1$，对其取 $\max$。

然后把战斗力从小到大排序，显然这是最优的。

现在我们已经确定了顺序，第 $i$ 个洞所需的战斗力是刚才求得 $\max -$前面打的怪的总数。

再对这个取 $\max$，就是答案。

代码献上。

```cpp
#include<stdio.h>
#include<string.h>
#include<algorithm>

using std::sort;

int t;
int n;
struct node{
	int k,_max,s;
}cave[100010];
int k[100010];
int _max[100010];

bool cmp(node a,node b){ return a._max<b._max; }

int max(int a,int b){ return a>b?a:b; }

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=0;i<=n;i++) cave[i]._max=cave[i].s=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&cave[i].k);
			for(int j=1;j<=cave[i].k;j++){
				int x;
				scanf("%d",&x);
				cave[i]._max=max(cave[i]._max,x-j+1);
			}
		}
		sort(cave+1,cave+1+n,cmp);
		int minn=cave[1]._max;
		for(int i=1;i<=n;i++) cave[i].s=cave[i-1].s+cave[i].k;
		for(int i=2;i<=n;i++) minn=max(minn,cave[i]._max-cave[i-1].s);
		printf("%d\n",minn+1);
	}
	return 0;
}
```

---

## 作者：cszhpdx (赞：0)

昨天比赛 （ div.2 ）自认为最简单的一题，比 A 还简单，因为至少 A 需要模拟的勇气

首先我们发现每个洞穴相互独立，假设对于一个洞穴，有 $k$ 个 boss 分别是 $a_1,a_2, \dots ,a_k$ 假设我们进来的时候 power 是 $x$ ，那么打第 $i$ 个 boss （之前还没死）之前 power 是 $x+i-1$  ，也就是如果我们要进入这个山洞，必须对于任意的 $1 \le i \le n$ 满足 $x+i-1>a_i$  即 $x>a_i-i+1$ 我们把所有的 $x>a_i-i+1$ 取交集，设交集第 $i$ 个山洞为 $x>p_i$  有 $k_i$ 个 boss 

于是我们将山洞的 $p_i$ 值升序排序，因为容易证明不是升序的顺序打山洞不会比升序更优，显然初始 power $x$ 满足 $x+\sum_{j=1}^{i-1}k_i>p_i$  即 $x>p_i-\sum_{j=1}^{i-1}k_i$ 取交集得到 $x>p_0$ ，$p_0+1$ 为最优解

代码：

```cpp
#include<cctype>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define mem(a, x) memset(a, x, sizeof(a))
#define rps(i, b, e) for(int i=(b);i<=(e);i++)
#define prs(i, e, b) for(int i=(e);i>=(b);i--)
#define rp(i, e) rps(i, 1, e)
#define pr(i, e) prs(i, e, 1)
#define rp0(i, e) rps(i, 0, (e)-1)
#define pr0(i, e) prs(i, (e)-1, 0)
#define rpg(i, x) for(int i=head[x];i;i=e[i].nxt)
#define opf(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)
using namespace std;
const int NR=1e5+10;
inline int read() {
	int num=0;
	bool f=false;
	char c=getchar();
	while(!isdigit(c))f|=(c=='-'), c=getchar();
	while(isdigit(c))num=num*10+(c-'0'), c=getchar();
	return (f?-num:num);
}
int T, n, x;
struct node {
	int v, k;
}a[NR];
bool cmp(node x, node y) {
	return x.v<y.v;
}
int main()
{
	T=read();
	while(T--) {
		n=read();
		rp(i, n) {
			a[i].v=-2e9;
			a[i].k=read();
			rp(j, a[i].k) {
				x=read();
				a[i].v=max(a[i].v, x-j+1);
			}
		}
		sort(a+1, a+n+1, cmp);
		int sum=0, ans=-2e9;
		rp(i, n) {
			ans=max(ans, a[i].v-sum);
			sum+=a[i].k;
		}
		printf("%d\n", ans+1);
	}
	return 0;
}
```



---

