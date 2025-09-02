# [CSGRound3] 压岁钱

## 题目背景

祝大家庚子鼠年快乐！Best wishes! 

也愿肺炎早日得到控制吧，中国加油！

新年到了，小 Z 总是能收到很多的压岁钱。

小 Z 是个非常喜欢氪金的玩家，所以时不时都会把压岁钱花掉一部分用来买皮肤和石头。

但是小 Z 又十分担心压岁钱没过几天就都被自己花完了。为此，小 Z 有封印大法，能够暂时的把自己的一部分钱封印起来（即无法花费），直到某一天解除封印后才能使用。

## 题目描述

一共存在有 $m$ 个事件，且事件分为以下的 $3$ 种类型。

1. 小 Z 得到了 $a$ 元压岁钱。
2. 小 Z 花掉了 $a$ 元压岁钱用于买皮肤。
3. 小 Z 把自己的 $a$ 元钱封印了起来，只有当第 $b$ 个事件发生前 $1$ 秒才会解除封印，并保证每次小 Z 现有的钱大于等于封印的钱。

当小 Z 的钱在某个事件不够花时，小 Z 会感到不开心，同时钱不够花时小 Z 便不会花钱。

请告诉小 Z ，他的钱在几个事件中会不够花。

## 说明/提示

**【样例 1 解释】**

第一天：收入 $10$ 元，余额 $10$ 元。

第二天：不够支出 $20$ 元，余额 $10$ 元。

第三天：支出 $10$ 元，余额 $0$ 元。

总计：$1$ 天。

**【样例 2 解释】**

第一天：收入 $10$ 元，余额 $10$ 元。

第二天：封印 $5$ 元，余额 $5$ 元。

第三天：不够支出 $10$ 元，余额 $5$ 元。

第四天：收入 $10$ 元，余额 $15$ 元。

第五天：封印解开，支出 $20$ 元，余额 $0$ 元。

总计：$1$ 天。

---

**【数据范围】**

对于 $50\%$ 的数据，满足 $m,a \leq 5\times 10^3$。

对于 $70\%$ 的数据，$t \ne 3$。

对于 $100\%$ 的数据，满足 $ 1 \leq b \le m \leq 10^6$，$1 \le t \le 3$，$1 \leq a \leq 10^7$。

## 样例 #1

### 输入

```
3
1 10
2 20
2 10```

### 输出

```
1```

## 样例 #2

### 输入

```
5
1 10
3 5 5
2 10
1 10
2 20```

### 输出

```
1```

# 题解

## 作者：梦里调音 (赞：11)

纯模拟，要理解好题意。

>小 Z 把自己的 a 元钱封印了起来，只有当第 b 个事件发生前 1 秒才会解除封印，并保证每次小 Z 现有的钱大于等于封印的钱。

这里可能有点歧义。

这个保证是针对数据而言，也就是我们在第三个操作不用任何判断，只当是直接封印。

然后。。。

>十年OI一场空，不开long long见祖宗。

然后整个数组记录封印的钱就好了。

```
#include <bits/stdc++.h>
using namespace std;
const int N=1e8+5; 
unsigned long long m,n,ans;//rt,money,answer
unsigned long long f[N];//f[i]表示第i个事件前要解封的钱
int main()
{
	cin>>m;
	for(unsigned long long i=1,t;i<=m;i++)
	{
		n+=f[i];
		cin>>t;
		if(t==1)
		{
			unsigned long long a;
			cin>>a;
			n+=a;
		}
		else if(t==2)
		{
			unsigned long long a;
			cin>>a;
			if(n<a)ans++;
			else n-=a;
		}
		else{
			unsigned long long a,b;
			cin>>a>>b;
			f[b]+=a;
			n=n-a;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Skyjoy (赞：6)

# 这题着实是一道很水的签到题

直接模拟就可以了

**注意：钱数最好用数组存起来，这样处理封印情况才会比较方便。**

上代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define re register
using namespace std;
ll n,t,a,b,ans,f[1000010];
int main(){
	cin>>n;
	for(re ll i=1;i<=n;i++){
		cin>>t;
		f[i]+=f[i-1];
		if(t==3){
			cin>>a>>b;
			f[i]-=a;
			f[b]+=a;
		}
		else{
			cin>>a;
			if(t==1){
				f[i]+=a;
			}
			else{
				if(f[i]<a){
					ans++;
				}
				else{
					f[i]-=a;
				}
			}
		}
	}
	cout<<ans;
	return 0;
}
```
# 2020，武汉加油！中国加油！

---

## 作者：时间重洗 (赞：3)

没参加月赛，真遗憾

话说这题是不是放错位置了？（本人消息不灵通，勿喷）

看了题目，感觉……，就是模拟吧，数据也不大，开数组的话也不会爆。思路很简单，就是用一个数组存在这个时刻，解封的钱有多少，就把加上就行了

代码

```cpp
#include<cmath>
#include<vector>
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;

const int MAXN=1000005;
int m,ans,now,money[MAXN];

template <typename T> void in(register T& a){
    register T x=0,f=1;
	register char c=getchar();
    while(!isdigit(c)){
	    c=='-'?f=-1:f=1;
		c=getchar();
	}
    while(isdigit(c)){
        x=(x<<1)+(x<<3)+c-'0';
	    c = getchar();
	}
    a=x*f;
}

int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	in(m);
	int i=1;
	while(m--){
		now+=money[i++];
		int opt,k;
		in(opt);in(k);
		if(opt==1) now+=k;
		if(opt==2){
			if(now>=k) now-=k;
			else ans++;
		}
		if(opt==3){
			int t;
			in(t);
			now-=k;
			money[t]+=k;
		}
	}
	printf("%d\n",ans);
	return 0;
}

```

为什么60分???

~~不开long long见祖宗~~

~~不写stdio.h见祖宗~~

重新看数据范围，似乎会爆long long……

代码

```cpp
#include<cmath>
#include<vector>
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;

const int MAXN=1000005;
long long m,ans,now,money[MAXN];

template <typename T> void in(register T& a){
    register T x=0,f=1;
	register char c=getchar();
    while(!isdigit(c)){
	    c=='-'?f=-1:f=1;
		c=getchar();
	}
    while(isdigit(c)){
        x=(x<<1)+(x<<3)+c-'0';
	    c = getchar();
	}
    a=x*f;
}

int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	in(m);
	int i=1;
	while(m--){
		now+=money[i++];
		int opt,k;
		in(opt);in(k);
		if(opt==1) now+=k;
		if(opt==2){
			if(now>=k) now-=k;
			else ans++;
		}
		if(opt==3){
			int t;
			in(t);
			now-=k;
			money[t]+=k;
		}
	}
	printf("%lld\n",ans);
	return o;
}

```


---

## 作者：KazamiHina (赞：2)

这题是一题简单的模拟题

只要按照题目模拟就好了

如果是操作 $1$ 就把现在已有的钱加上

如果是操作 $2$ 就判断钱够不够

如果够就减去

否则计数器++

如果是操作 $3$ 就把一个用来保存封印的数组加上存入的钱（一定是加上，不能是等于，如果是等于的话可能有的钱会在同一天解除封印，就会少算封印的钱）

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
//这里用了一种玄学的东西，把int变成long long

using namespace std;

int opt,ans,n,a,b,tot;
//ans表示现在有的钱，tot表示钱不够用的次数
int w[1000005]; 
//w数组用来储存封印的钱

signed main()
//signed main 相当于 int main
//但是这里不能写成 int main
//因为上面把 int define 成了 long long
//写成 int main 就会 CE
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
    {
        ans+=w[i];
        //现在有的钱加上存的钱
        scanf("%lld",&opt);
        if(opt==1)
        {
            scanf("%lld",&a);
            ans+=a;
            //直接加上存的钱
        }
        if(opt==2)
        {
            scanf("%lld",&a);
            if(ans<a)tot++;
            //如果钱不够计数器就++
            else ans-=a;
            //否则就减掉氪掉的钱
        }
        if(opt==3)
        {
            scanf("%lld%lld",&a,&b);
            ans-=a;
            //钱存进去就减掉
            w[b]+=a;
            //存入计数数组
        }
    }
    printf("%lld",tot);
	//块乐地输出钱不够的次数然后结束程序
    return 0;
}
```

忠告：不开 long long 见祖宗

---

## 作者：StudyingFather (赞：2)

简单模拟题。

收入和支出都不是比较关键的问题，关键在于冻结。

对于冻结的资产，我们可以维护一个堆。每次要花钱的时候，将所有解禁时间小于等于当前时间的资产解冻即可。

```cpp
#include <iostream>
#include <queue>
using namespace std;
typedef pair<int,int> pii;
priority_queue<pii,vector<pii>,greater<pii> > q;
int main()
{
 ios::sync_with_stdio(false);
 int m,ans=0;
 long long x=0;
 cin>>m;
 for(int i=1;i<=m;i++)
 {
  int op,a,b;
  cin>>op;
  if(op==1)
  {
   cin>>a;
   x+=a;
  }
  else if(op==2)
  {
   cin>>a;
   while(!q.empty()&&q.top().first<=i)
   {
    x+=q.top().second;
    q.pop();
   }
   if(x>=a)x-=a;
   else ans++;
  }
  else
  {
   cin>>a>>b;
   q.push({b,a});
   x-=a;
  }
 }
 cout<<ans<<endl;
 return 0;
}
```


---

## 作者：李若谷 (赞：1)

### 模拟题
首先t=1，和t=2时都很简单。只需要加钱到一个变量，和减钱就行了。
主要看t=3的时候，我们可以那一个数组来记录第b天封印的钱。
然后每次枚举一天的时候看看数组是否有被封印的钱。如果有的话就加钱。

本题要开long long。
这道题还有一个坑，可能有多条时间在同一天封印钱。

代码

```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;
const int M = 1000001;
long long seal[M];
inline int read()
{
    int f = 1;
    int ans = 0;
    char ch = getchar();
    while(ch<'0'||ch>'9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        ans = ans * 10 + ch - '0';
        ch = getchar();
    }
    return ans*f;
}
int main()
{
    long long m,t,money = 0,tot = 0;
    m = read();
    for(register long long i=1;i<=m;++i)
    {
        if(seal[i])
        {
            money += seal[i];
        }
        t = read();
        if(t==1)
        {
            long long a = read();
            money += a;
        }
        else if(t==2)
        {
            long long a = read();
            if(money >= a)
            {
                money -= a;
            }
            else
            {
                tot ++;
            }
        }
        else if(t==3)
        {
            long long a = read(), b = read();
            seal[b] += a;
            money -= a;
        }
    }
    printf("%d\n",tot);
}
```

---

## 作者：WOWHandsome (赞：1)


**纯模拟，暴力 $O(n)$ 可过。**

其实这道题目主要是让你处理 $\color{red} case\ 3$ 的情况。其实很简单，题目的事件编号是固定的递增序列 $\{1,2,3,4,5,6...\}$。那么就可以用一个数组 $que[i]$ 来表示第 $i$ 件事件有多少钱被**解除**封印。

然后写出了第一个代码：

```
# include <bits/stdc++.h>
using namespace std;
int que[1000005];
int main() {
	int m, flag, a, b, t = 0;
	long long money = 0;
	int answer = 0;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		if (que[i]) money = money + que[i];
		scanf("%d", &flag);
		switch (flag) {
			case 1: {
				scanf("%d", &a);
				money = money + a;
				break;
			}
			case 2: {
				scanf("%d", &a);
				if (a > money) answer++;
				else money = money - a;
				break;
			}
			case 3: {
				scanf("%d%d", &a, &b);
				que[b] = a;
				money = money - a;
				break;
			}
		}
	}
	printf("%d\n", answer);
	return 0;
} 
```

$Rid:29783489. \color{red} \ 50pt/592ms/4.38MB$

怎么 50 分？**题目不保证** $\textit{b}$ **总是不相同**！然后仔细地看了一下：

~~$\sout{OI}$十年一场空，不开 $\sout {long \ long}$ 见祖宗~~

代码二：

```cpp
# include <bits/stdc++.h>
using namespace std;

typedef long long ll; //懒得改 long long. qwq
#define int ll        //define 大法好！

int que[1000005];

signed main() {
	int m, flag, a, b;
	long long money = 0;
	int answer = 0;
	scanf("%lld", &m);
	for (int i = 1; i <= m; i++) {
		if (que[i]) money = money + que[i];
		scanf("%lld", &flag);
		switch (flag) {
			case 1: {
				scanf("%lld", &a);
				money = money + a;
				break;
			}
			case 2: {
				scanf("%lld", &a);
				if (a > money) answer++;
				else money = money - a;
				break;
			}
			case 3: {
				scanf("%lld%lld", &a, &b);
				que[b] += a; //important!
				money = money - a;
				break;
			}
		}
	}
	printf("%lld\n", answer);
	return 0;
} 
```

ps. 此代码非常取$\sout{(lan)}$巧$\sout{(duo)}$地用了 define 来便携的将全局的所有 $int,\ signed \ int,\ unsigned \ int$ 都相应改为了 $long\ long,\ signed \ long \ long,\ unsigned \ long \ long$。

春节快乐鸭！

---

## 作者：codemap (赞：1)

做法:

直接模拟

如何处理"封印":开一个数组$c[i]=d$表示第$i$位将解封$d$元

**大**坑点:要开$longlong$

上代码:

```cpp
#include<iostream>
using namespace std;
long long c[1000001];//处理"封印"的c数组,注意开ll
int main()
{
	long long m,i,t,a,b,s=0,ans=0;注意开ll
	cin>>m;
	for(i=1;i<=m;i++)
	{
		s+=c[i];//解封
		cin>>t>>a;
		if(t==1)//第一种
			s+=a;//得到a元
		if(t==2)//第二种
		{
			if(s<a)//不够花
				ans++;//答案++
			else//否则
				s-=a;//花钱
		}
		if(t==3)//第三种
		{
			cin>>b;
			c[b]+=a;//到第b个解封a元
			s-=a;//"封印"a元
		}
	}
	cout<<ans;
	return 0;//结束
}
```
# 请勿抄袭

---

## 作者：Kevin_Wa (赞：1)

## T1 压岁钱

### 题目大意：

一道膜你题，就按照题目所说的去膜你即可。

用一个变量$sum$来存储他当前手上的钱数，然后当$1$事件发生后，将这个变量的值加一个数值，当二事件发生时，将这个变量的数值减一下。

三事件看上去复杂，其实我们只需要用一个数组存储在当前有没有解封的钱可以拿就可以了。

注意：十年$OI$一场空，不开$longlong$见祖宗。

### $Code$

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
long long a[1000010],n,ans;
long long sum;
template <typename T> void read(T &x) {
x = 0; char c = getchar();int f=1;
for (; !isdigit(c); c = getchar())if (c=='-') f=-1;
for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
x*=f;
}
int main()
{
read(n);
for (int i=1;i<=n;i++)
  a[i]=0;
ans=0,sum=0;
for (int i=1;i<=n;i++)
  { int o,x,y;
  	read(o);
  	sum+=a[i];
  	if (o==1)
  	  {
  	  	read(x);
  	  	sum+=x;
		}
	if (o==2)
	  {
	  	read(x);
	  	if (sum>=x) sum-=x;
	  	else ans++;
	  }
	if (o==3)
	  {
	  	read(x),read(y);
	  	sum-=x;
	  	a[y]+=x;
	  }
	}	
printf("%d\n",ans);
	return 0;
 } 
```


---

## 作者：Hexarhy (赞：1)

被评测机卡到交 $5$ 次才过……

自闭。

----------

### 解题思路

作为比赛的签到题，一看就是**模拟**。

直接根据每天的操作模拟即可。步骤如下：

- 在每一天伊始，都要更新自己的压岁钱，因为有的可能解封了。

- 当 $t=1$，直接加余额。

- 当 $t=2$，判断余额是否足够（包括等号）。不够（即小于）则统计答案，否则直接扣余额。

- 当$t=3$，记录封印和解封时间，同时扣除余额。为了方便每天更新压岁钱，我们用`set`按照时间顺序记录封印。

- 在每一天伊始，更新自己的压岁钱时，直接用`set`的第一个元素判断是否为当前时间即可。

若忽略`set`的复杂度，则时间复杂度 $O(m)$。但其实实际得分依然为 $100\%$。

-----------

### 实现细节

1. 封印之后，余额要减。

1. $\infty$ 年OI一场空，不开`long long`见祖宗。

1. 判断余额是否足够时，注意等号。

1. `set`解封时判断是否是当前日期，使用`while`而非`if`，因为可能一天同时解封多个。

----------

### 参考代码

使用类封装。当然可以写成一般函数的形式。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
typedef long long ll;
ll m,t,a,b;
class money//别介意
{
private:
	ll total,ans;
	struct Lock
	{
		ll v,date;//封印金额和解封时间
		bool operator<(const Lock& x)const
		{
			return date<=x.date;//按时间排序
		}
	};
	set <Lock> locked;
public:
	void update(const ll& now)//每天第一步：更新压岁钱（解封）
	{
		while(!locked.empty() && locked.begin()->date==now)//实现细节4
		{
			total+=locked.begin()->v;
			locked.erase(locked.begin());//别忘了删除记录
		}
	}
	void save(const ll& v)//存钱
	{
		total+=v;
	}
	void cost(const ll& v)//花费
	{
		if(total<v)
		 ans++;//钱不够了统计答案
		else
		 total-=v;
	}
	void lock(const ll& v,const ll& date)//封印
	{
		locked.insert(Lock{v,date});
		total-=v;//别忘了减
	}
	ll unhappy(void)
	{
		return ans;
	}
}q;
int main(int argc, char const *argv[])
{
	//输入最好用scanf()快些。本题输入量不小。
	cin>>m;
	for(ll i=1;i<=m;i++)
	{
		q.update(i);
		cin>>t>>a;
		switch(t)
		{
			case 1:q.save(a);continue;
			case 2:q.cost(a);continue;
			case 3:cin>>b;q.lock(a,b);continue;
		}
	}
	cout<<q.unhappy()<<endl;
	return 0;
}
```

---

## 作者：Apro1066 (赞：1)

退役了，真的退役了......三个月没怎么刷题，$div2$的第一题就把我弄自闭了，写了半个小时，跑的还死慢。。不过我想只要是人都能看懂我这个代码，大体上就是硬核模拟。
```cpp
#include <stdio.h>
#include <iostream>
#include <queue>
#define int long long int
#define N 1000001
using namespace std;
struct node//并没有什么卵用的结构体，事实上在后面的读入中只需要3个变量。 
{
	int id,val,to;//id:事件；val:得到或花掉的钱；to:仅事件3才有的参数[持续到第几天] 
}a[N];
struct lst//这个结构体处理专门一系列的事件三 
{
	int duration,v;//duration代表封印持续到第几天，v代表封印的钱 
	bool operator < (const lst &a)const
	{
		return a.duration<duration;//把持续时间从小到达排序 
	}
}tmp;
int n,s,ans,f;
priority_queue<lst> q;//优先队列 
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	register int i,j;
	cin>>n;
	for(i=1;i<=n;i++)//枚举事件i 
	{
		while(!q.empty())
		{
			if(q.top().duration==i)//判断某个事件3的持续时间是否已经到了i 
			{
				s=s+q.top().v;//把钱拿回来 
				q.pop();//踢掉 
			}
			else break;//如果不是就不管 
		}
		cin>>a[i].id;//输入事件类型 
		if(a[i].id!=3)//如果不是3 
		{
			cin>>a[i].val;
			if(a[i].id==1)
			{
				s+=a[i].val;//直接赚钱即可 
			}
			else//事件2 
			{
				s-=a[i].val;//花钱 
				if(s<0)//如果没有足够的钱 
				{
					s+=a[i].val;//再加回来 
					ans++;//不满意的次数+1 
				}
			}
		}
		else//事件3 
		{
			cin>>a[i].val>>a[i].to;
			s-=a[i].val;//减钱 
			tmp.duration=a[i].to; 
			tmp.v=a[i].val;
			q.push(tmp);//塞进队列 
		}
		//cout<<s<<endl<<endl;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Chen_cntj (赞：0)

提供一种新奇的做法。

------------

我们可以将每一天的事件分为两类：

1. 收入
1. 支出

那么封印要怎么处理呢？

我们似乎可以这样想：

**封印时**，要从手中的钱里面拿出一部分，所以是**支出**。

**封印的时间到了**，则可以拿回封印的钱，所以是**收入**。

封印处理的问题解决了，还有一个非常小的细节：

**不能直接将一天的收支综合**。

为什么呢？因为如果封印解除后的事件是收入，则可以直接加入**收入**部分。

但是，如果封印解除后的事件是支出，而我们又**以收抵支**，就可能出现**就算抵了也不够支出**的情况。那你总不会就这样把封印了的钱丢了吧？

所以我们必须将收入与支出分开，单独处理。

------------

以上问题解决后就按照每日的收支进行计算和统计就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int m,ans,mn,opr,dy;
long long sum;
struct afo
{
	long long pl,mi;//这里因某著名见祖宗原因挂了20分
}a[1000001];
int main()
{
	cin>>m;
	for (int i=1;i<=m;++i)
	{
		cin>>opr;
		if (opr==1)
		  cin>>mn,a[i].pl+=mn;
		if (opr==2)
		  cin>>mn,a[i].mi=mn;
		if (opr==3)
		  cin>>mn>>dy,a[i].mi=mn,a[dy].pl+=mn;
	}
	for (int i=1;i<=m;++i)
	{
		sum+=a[i].pl;
		if (a[i].mi<=sum)
		  sum-=a[i].mi;else
		  ++ans;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：DreamFox (赞：0)

本题思路：

对于操作$1$，直接加即可

对于操作$2$，如果花的钱小于等于已有的钱，则花掉，否则天数加$1$

对于操作$3$，用一个数组记录每天可以接解封的钱数，每封印一次就把每天可以接解封的钱数加上封印的钱数，在每次循环的开始加上每天可以接解封的钱数即可

记住，要开$long$ $long$

$AC$ $Code$
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,x[1000001],money,ans;
int m,c;
int main()
{
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		money+=x[i];
		scanf("%lld",&a);
		if(a==1)scanf("%lld",&b),money+=b;
		if(a==2)
		{
			scanf("%lld",&b);
			if(money>=b)
			money-=b;
			else
			++ans;
		}
		if(a==3)
		{
			scanf("%lld%d",&b,&c);
			x[c]+=b;
			money-=b;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Suuon_Kanderu (赞：0)

首先要提醒大家，作为一个普及T1难度的题，还是比较坑的。

大家注意$ \textcolor{white}{
In ,ten, years, OI ,is ,empty. , Without,long long , I, will ,see, my, ancestors.} $
我就因为此错了3+回（太菜）$\color{white}\texttt{十年OI一场空，不开long long 见祖宗}$

没办法，弱就是我的归宿，被大佬暴打就是我的命运~~强行凑字~~$\color{white}\texttt{百度机翻差评}$
  
  
 ，这题,看起来$ int$就够了,但是$m<=5 \times10^6$, $a<=10^7$,这么一乘，$ int $就不负众望的爆了，要开~~龙龙~~long long
 
 这个题还是挺简单的，思路看注释吧。
 ```
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<string.h>
#include <algorithm>
using namespace std;
const long long N=1e6+100;    
long long n,ans,sum;// n个事件,钱不够花的事件数,当前的钱数
long long money[N];//在第i个事件将解封a元钱
int main(){
   	int n;
   	cin>>n;
   	for(int i=1;i<=n;i++){
   	int op,a,b;		
		sum+=money[i];//在第i个事件能解封a元钱
		scanf("%d",&op);
		if(op==1){
			scanf("%d",&a);	
			sum+=a;	//存a元钱		
		}
		if(op==2){
			scanf("%d",&a);
			if(a>sum)ans++;//如果钱不够了，ans++
			else sum-=a;	
		}			

		if(op==3){
			scanf("%d%d",&a,&b);
				sum-=a;//封印a元钱
				money[b]+=a;//	在第b个事件将解封a元钱
			
		}				
	}
	cout<<ans<<endl;
    return 0;
}


```
主要针对蒟蒻 $ \textcolor{white}{isn't,me?} $

比较详细，大佬请无视。

$
 \color{blue}\texttt{文} \color{green}\texttt{内} \color{silver}\texttt{有} \color{pink}\texttt{彩}\color{purple}\texttt{蛋} \color{orange}\texttt{啊} 
$
 

---

## 作者：Y_B_Y (赞：0)

### 要点:注意要开long long

观察题面,一共有三种操作:

1.小 Z 得到了$a$元压岁钱

2.小 Z 花掉了$a$ 元压岁钱

3.小 Z 把自己的 $a$ 元钱存起来，直到第$b$个操作时才可使用,且存的钱数小于等于现在有的钱

求钱不够花的次数

操作$1$和$2$很好理解,操作$3$我们可以视为花掉$a$元,使第$b$个操作时自己得到$a$元,所以我们定义一个数组$mon[i]$,表示进行完操作i所剩的钱,所以得

**初始化:** $mon[0]=0$

**mon[i]的继承:** $mon[i]+=mon[i-1]$(继承上一次操作剩的钱,且因为之前可能有**操作3**使$mon[i]$**初始化前**就有钱,所以是"$+=$")

**操作1:** $mon[i]+=a$

**操作2:** 如果$mon[i]<a$,钱不够花次$+1$,如果$mon[i]≥a$,$mon[i]-=a$

**操作3:** $mon[i]-=a($根据题目$a≤mon[i]),mon[b]+=a$(花掉$a$元,使第$b$个操作时自己得到$a$元)

### 上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long//define定义以ll代替long long
const int N=1e6+6;
ll mon[N],m,ans;//ans表示钱不够花的次数,注意用long long
inline ll read()//快读,这一题不用也可以AC
{
    char c;
    ll sum=0;
    ll f=1;
    while(((c=getchar())>'9'||c<'0')&&c!='-');
    if(c=='-') f=-1;
    else sum=c-'0';
    while((c=getchar())!='\n'&&c!='\r'&&c!=32) sum=((sum<<1)+(sum<<3))+(c-'0');
    return sum*f;
}
int main()
{
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		ll opt,a;
		opt=read();//可改为cin,下同
		a=read();
		mon[i]+=mon[i-1];//初始化
		if(opt==1)//操作1
		{
			mon[i]+=a;
		}
		if(opt==2)//操作2
		{
			if(mon[i]>=a)
			{
				mon[i]-=a;
			}
			else
			{
				ans++;
			}
		}
		if(opt==3)//操作3
		{
			ll b;
			b=read();
			mon[b]+=a;
			mon[i]-=a;
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Edmundino (赞：0)

# 题意

其实就是一道模拟题

就是说，当t=1时，存钱数（下面称为s）便加a

当t=2时，s如果大于等于a，就s-=a，否则，s不变，不够钱的事（下面称为ans）就加1

当t=3时，我们就设一个标记m[i]，此时m[b]+=a;

# 分析

模拟题，是考验代码能力的时候

这题思路不难，

循环m次

每次cin>>t且s+=m[i]

if(t==1)的时候，cin>>a,s+=a;

if(t==2)的时候，cin>>a,

此时进行分支

if(s>=a) s-=a;

else ans++

if(t==3)的时候，m[b]+=a;

最后输出ans即可

# 代码

不难实现，直接上AC代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<iomanip>

using namespace std;

const int N=1e6+50;

long long n,t,a,b,s,ans,m[N];

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>t;
		s+=m[i];
		if(t==1)
		{
			cin>>a;
			s+=a;
		}
		if(t==2)
		{
			cin>>a;
			if(s<a)
			{
				ans++;
			}
			else
			{
				s-=a;
			}
		}
		if(t==3)
		{
			cin>>a>>b;
			s-=a;
			m[b]+=a;
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：james1BadCreeper (赞：0)

签到模拟。

对于 $50\%$ 的数据，建立一个变量，直接按题意模拟。

```cpp
int main(void)
{
	cin>>m;//操作次数
	while(m--)//对于每次操作
	{
		cin>>op;
		if(op==1)//加钱
		{
			cin>>a;
			sum+=a;
		}
		else//花钱
		{
			cin>>a
			if(sum<a) ans++;//钱不够
			else sum-=a;
		}
		
	}
	cout<<ans;
	return 0;
}

```

对于 $70\%$ 的数据，数据很大，需要开```long long```。

对于 $100\%$ 的数据，操作 $3$ 我们可以考虑建立一个数组存储被封印的钱，当到了解封的一天在加到 $sum$ 上。

```cpp
#include<iostream>
using namespace std;
int m,op,ans=0;
long long sum=0;
long long a,b;
long long g[1000005];
int main()
{
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		sum+=g[i];//到了第i天，把这一天的钱拿出来
		cin>>op;
		if(op==1)
		{
			cin>>a;
			sum+=a;
		}
		else if(op==2)
		{
			cin>>a;
			if(sum<a) ans++;
			else sum-=a;
		}
		else
		{
			cin>>a>>b;
			sum-=a;//拿钱去封印
			g[b]+=a;//封进去
		}
	}
	cout<<ans;
	return 0;
}
 ```


---

## 作者：　　　吾皇 (赞：0)

### 题目分析
- 首先，我们可以用一个变量 $pr$ 来表示当前的钱数。
- 对于 $1 \le i \le n$，我们用 $sm[i]$ 来表示第 $i$ 天需要解封的钱数。
- 我们用 $ans$ 表示**钱不够花**的事件数。

那么就是一道简单的模拟题了。
#### 注意
- 如果当前钱数不能买皮肤即 $pr<a$，则不需要付钱，`ans++`。
- 封印的钱可以叠加，也就是 `sm[i]+=a` 而不是 `am[i]=a`。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   register int s=0,w=1;
   register char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int pr,sm[1000001],t,a,b,m,ans;
int main(){
	m=read();
	for(int i=1;i<=m;i++){
		pr+=sm[i];//加上当天解封的钱数，如果没有就是0
		t=read();
		if(t==1)
			pr+=read();
		else if(t==2){
			a=read();
			if(a>pr) ans++;//如果不能付款答案加一
			else pr-=a;// 否则付钱
		}
		else {
			a=read(),b=read();
			sm[b]+=a;//封印
			pr-=a;//还要扣除自己当前钱数 因为题目已经明确说明操作合法，所以不需要特判
		}
	}
	printf("%d",ans);//输出答案
}
```


---

## 作者：SUNCHAOYI (赞：0)

#### 读完题后，发现有三种情况，一一模拟即可
**t = 1 存钱 直接把钱存入即可**
```
if(t == 1)
{
	cin>>a;
	money += a;//直接把钱存入 
}
```
**t = 2 花钱 需要判断够不够花：若不够花，小 Z 会感到不开心，同时钱不够花时小 Z 便不会花钱；若够花，减去相应的钱即可。**
```
if(t == 2)
{
	cin>>a;
	if(money < a) ans++;//不够花 
	else money -= a;//够花，减去所用的钱 
}
```
**t = 3 封印，即存钱，设置一个数组b[k]表示第k天时可解除b[k]元的封印**
```
if(t == 3)
{
	cin>>a>>b;
	if(b > i)//以防过时
	{
		s[b] += a;//封印 
		money -= a;//减去相应的钱 
	}
}
```
**最后在判断类型前加上解除的封印的钱哦！**
```
money += s[i];//解除封印 

```

------------
**注意：对于100%的数据，满足 1≤b≤m≤10 ^ 6,1≤t≤3,1≤a≤10 ^ 7。因为数据比较大，所以要开long long才能过哦！！！**

------------

#### 完整代码：
```
#include <iostream>
using namespace std;
const int MAX = 1000005;
int k = 0,m,ans = 0;
long long s[MAX] = {0},money = 0;//s[i]表示在第i天前会解封s[i]元 
int main()
{
	cin>>m;
	for(int i = 1;i <= m;i++)
	{
		int t,a,b;
		cin>>t;
		if(s[i] != 0) money += s[i];//解除封印 
		if(t == 1)
		{
			cin>>a;
			money += a;//直接把钱存入 
		}
		if(t == 2)
		{
			cin>>a;
			if(money < a) ans++;//不够花 
			else money -= a;//够花，减去所用的钱 
		}
		if(t == 3)
		{ 
			cin>>a>>b;
			if(b > i)
			{
				s[b] += a;//封印 
				money -= a;//减去相应的钱 
			}
		}
	}
	cout<<ans<<endl;
	return 0;
} 
```


---

## 作者：HohleFeuerwerke (赞：0)

赶紧过来。

[水题](https://www.luogu.com.cn/problem/P6013)。直接模拟即可。

比较难受的是一开始没想到正解，想到了每次先枚举是否有本次事件解封的。

正解：

用一个数组记录每次的花钱开销，如果 $t=3$ 那么本次先去掉封印钱数，再在解封日期加上封印钱数即可。

贴代码

```cpp
#include<bits/stdc++.h>
#define MAXM 1000005
using namespace std;
int m;
typedef long long ll;
ll cur[MAXM];
int ans;
int main()
{
	ios::sync_with_stdio(false);
	cout.tie(0);cin.tie(0);
	cin>>m;//读入
	for(int i=1;i<=m;i++)
	{
 		//按照每天模拟
		cur[i]+=cur[i-1];//先加上上一次时间留下的
		int t;//含义如题
		cin>>t;//读入
		if(t==1){
			int a;cin>>a;
			cur[i]+=a;//收到红包，钱数增加
		}
		if(t==2){
			int a;cin>>a;//读入
			if(cur[i]<a) ans++;//如果钱不够花，答案++，钱数不变
			else cur[i]-=a;//否则就得花钱买皮肤
		}
		if(t==3){
			int a,b;
			cin>>a>>b;
			cur[b]+=a;/*给遥远的将来寄去aRmb*/cur[i]-=a;//现在少了a元
		}
	}
	cout<<ans<<endl;//输出答案
	return 0;
}
```

---

## 作者：andyli (赞：0)

用一个数组A记录第i个事件能新增多少元钱，在处理第$i$个事件时把钱加上，操作1直接累积当前所有的钱，操作2要先判断当前所有的钱是否不少于$a$，若少于$a$则钱不够花的事件数++。注意操作3时要将所有的钱减去存储的钱。  
主要代码如下：  
```cpp
const int maxn = 1000005;

LL A[maxn];
int main()
{
    int n;
    io.read(n);
    int ans = 0;
    LL money = 0;
    for (int i = 1; i <= n; i++) {
        int opt, b;
        LL a;
        io.read(opt, a);
        money += A[i];
        if (opt == 1) {
            money += a;
        } else if (opt == 2) {
            if (money >= a)
                money -= a;
            else
                ans++;
        } else
            io.read(b), A[b] += a, money -= a; // 去除要存的钱
    }
    writeln(ans);
    return 0;
}
```

---

## 作者：S1gMa (赞：0)

### 压岁钱！！！懒人写法 简单易懂 欢迎学习


### 一. 分析题意

``` 
小Z 得到了 a 元压岁钱
```
```
小 Z 花掉了 a 元压岁钱用于买皮肤。
```
```
小 Z 把自己的 a 元钱封印了起来，只有当第 b 个事件发生前 1 秒才会解除封印，并保证每次小 Z 现有的钱大于等于封印的钱
```
总结以上中心题意 

1.  你妈妈给你一个红包 你把这个红包收起来
2.  看到自己想要的东西花钱买
3.  管不住自己剁手施加魔法 在红包总数里拿出一部分 在第 b 天是才可以用 也就是说这些一部分钱在 b天前视作不存在

好的题意理清楚了开始代码

### 二. 代码部分
```

#include <bits/stdc++.h>
using namespace std;
bool flag[10000001];//记录封存时间
long long f[10000001];//记录封存的钱数
long long mon = 0， sum = 0;
long long x, a, b，n;
int main()
{
    cin >> n;//天数
    memset(flag, 1, sizeof flag);//在没有封印是先全部标记一遍
    for (int j = 1; j <= n; j++)
    {
        cin >> x;//输入要进行的

        if (flag[j] == 0)
        {
            mon += f[j];
        }//提前判断如果到了封印时间就要在钱的总数上加上封印的钱

        if (x == 1)//收红包
        {
            cin >> a;
            mon += a;
            continue;
        }
        if (x == 3)//封印红包
        {
            cin >> a >> b;
            flag[b] = 0;//标记封印的时间
            f[b] += a;//累加封印的钱
            mon -= a;//在总钱数里减去
            continue;
        }
        if (x == 2)
        {
            cin >> a;
            if (mon - a < 0)//如果钱不够只好继续攒喽。。。 并统计次数
            {
                sum++;
                continue;
            }
            mon -= a;//钱够了 就减去
        }
    }
    cout << sum << endl;//输出钱不够的此时
}

```
###### 总结一下 小朋友们 要合理利用钱钱哦！


---

