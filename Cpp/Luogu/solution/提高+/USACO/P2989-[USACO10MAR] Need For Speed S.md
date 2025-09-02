# [USACO10MAR] Need For Speed S

## 题目描述

Bassie正在为即将到来的赛车比赛作准备。

她有一辆赛车，重为M，且可以提供F的力。

现在她想要给这辆赛车安装一些零件（总共有N个零件），每个零件具有属性$M_i$和$F_i$，表示其重量以及可以提供的力。

设$X_i = 1\text{或}0$，表示第i个零件选或不选。

最大化$\frac{F+\sum_{i=1}^{n}X_i \times F_i}{M+\sum_{i=1}^{n}X_i \times M_i}$;

在此基础上最小化$\sum_{i=1}^{n}X_i \times M_i + M$。

## 样例 #1

### 输入

```
1500 100 4 
250 25 
150 9 
120 5 
200 8 
```

### 输出

```
2 
3 
4 
```

# 题解

## 作者：Isonan (赞：3)

原题传送门[>Here<](https://www.luogu.org/problemnew/show/P2989)

我的01分数规划学习笔记[>Here<](https://www.luogu.org/blog/PopulusEuphratica/post-xue-xi-bi-ji-01-fen-shuo-gui-hua)

这题是一道01分数规划问题，二分和判定的方法都比较常规，每次二分$mid$时判断能不能使选出的数之和为负数就可以了。对于要求的满足比率最大的条件下使重量最小，只要双关键字排序以后选择就可以了。在二分时顺便存一下选中的零件，最后输出就好了。

代码如下：

```cpp
#include <cstdio>
#include <algorithm>

struct point{
	double val;
	int pos,m;
}num[10001];
bool cmp(point a,point b){
	return a.val==b.val ? a.m<b.m : a.val<b.val;
} 
double F[10001],M[10001],l,r,mid;
int n,ans[10001],top,tem[10001],ttop;
bool judge(double u){
	for(int i=0;i<=n;i++)num[i].val=M[i]*u-F[i],num[i].m=M[i],num[i].pos=i;
	std::sort(num+1,num+n+1,cmp);
	ttop=0;
	for(int i=1;num[0].val>0.0&&i<=n;i++)tem[++ttop]=num[i].pos,num[0].val+=num[i].val;
	if(num[0].val>0.0)return 0;
	top=ttop;
	for(int i=1;i<=top;i++)ans[i]=tem[i];
	return 1;
}
int main(){
	scanf("%lf%lf%d",F,M,&n);
	for(int i=1;i<=n;i++)scanf("%lf%lf",F+i,M+i);
	l=0.0,r=10000000.0;
	while(r-l>=0.0001){
		mid=(l+r)/2;
		if(judge(mid))l=mid;
		else r=mid;
	}
	std::sort(ans+1,ans+top+1);
	for(int i=1;i<=top;i++)printf("%d\n",ans[i]);
	if(!top)puts("NONE");
}
```

---

## 作者：Gaode_Sean (赞：2)

## 45 pts

爆搜。枚举每个零件选还是不选。

时间复杂度：$O(2^n)$

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
double f,m,a[10001],b[10001],cnta,ans[10001],maxs,zh[10001];
int n;
void dfs(int now,int cnt,double x,double y)
{
	if(now==n+1){
		if(x/y>maxs){
			cnta=cnt;
			for(int i=1;i<=cnta;i++) ans[i]=zh[i];
			maxs=x/y;
		}
		return;
	}
	dfs(now+1,cnt,x,y);
	zh[cnt+1]=now;
	dfs(now+1,cnt+1,x+a[now],y+b[now]);
}
int main()
{
	cin>>f>>m>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	dfs(1,0,f,m);
	if(cnta==0){
		cout<<"NONE";
		return 0;
	}
	for(int i=1;i<=cnta;i++) cout<<ans[i]<<endl;
	return 0;
} 
```

## 100 pts

考虑贪心。贪心策略是 按照 $ \frac{F}{M} $ 从大到小排序，最后的结果一定是最优的。

排序后，对于第 $i$ 个零件（已选前 $i-1$ 个零件，当前答案最优），我们把选了第 $i$ 个零件的答案与原来的答案进行比较，如果小了，则不选第 $i$ 个零件，也不选其他零件。

最后按编号排序后输出答案即可。

时间复杂度：$O(n \log n)$

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	double x,y;
	int num;
}a[10001];
bool cmp(node a,node b)
{
	return a.x/a.y>b.x/b.y;
}
bool num(node a,node b)
{
	return a.num<b.num;
}
int n,i;
double f,m,ans;
int main()
{
	cin>>f>>m>>n;
	for(i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
		a[i].num=i;
	}
	sort(a+1,a+1+n,cmp);
	ans=f/m;
	for(i=1;i<=n;i++){
		f+=a[i].x,m+=a[i].y;
		if(f/m>ans) ans=f/m;
		else{
			if(i==1){
				cout<<"NONE";
				return 0;
			}
			sort(a+1,a+i,num);
			for(int j=1;j<i;j++) cout<<a[j].num<<endl;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：BitByBit (赞：1)

[AC记录](https://www.luogu.com.cn/record/210480882)
### 题意
给定 $F,M$ 和 $n$ 个零件，每个零件有 $F_i,M_i$ 两个属性，要求选一些零件，求 $F$ 加上 $F_i$ 的总和除以 $M$ 加上 $M_i$ 的总和最大，同时使 $M_i$ 的总和最小。
### 题解
贪心。把零件按照 $\frac{F_i}{M_i}$ 排降序，然后令 $F_0 = F,M_0=M$，每次 $F_0$ 加上 $F_i,M_0$ 加上 $M_i$，如果 $\frac{F_0}{M_0}$ 比原来大了就记录答案，否则结束选择，输出答案。

证明：令 $\frac{F_0}{M_0} < \frac{F_i}{M_i} < \frac{F_j}{M_j}$。如选零件 $i$ 则结果变为 $\frac{F_0+F_i}{M_0+M_i}$，选 $j$ 则为 $\frac{F_0+F_j}{M_0+M_j}$。显然有 $\frac{F_0+F_i}{M_0+M_i}<\frac{F_0+F_j}{M_0+M_j}$，所以选 $j$ 更优。
### code
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=100010;
ll n;
double ans;
struct S
{
	double x,y;//即题目中的F_i,M_i
	ll z;//编号
	friend bool operator<(S i,S j)
	{
		return i.x*j.y>j.x*i.y;//相当于i.x/i.y>j.x/j.y
	}
};
S a[N];
bool cmp(S i,S j)
{
	return i.z<j.z;
}
int main()
{
	double x,y;
	scanf("%lf%lf%lld",&x,&y,&n);
	for(ll i=1;i<=n;i++)
	{
		scanf("%lf%lf",&a[i].x,&a[i].y);
		a[i].z=i;
	}
	sort(a+1,a+n+1);
	ll k;
	ans=x/y;
	for(ll i=1;i<=n;i++)
	{
		x+=a[i].x;
		y+=a[i].y;
		if(x/y>ans)ans=x/y;
		else
		{
			if(i==1)return printf("NONE"),0;//判断不选
			k=i-1;
			break;
		}
	}
	sort(a+1,a+k+1,cmp);//记得按编号输出答案
	for(ll i=1;i<=k;i++)
		printf("%lld\n",a[i].z);
}
```
还有就是不选是 NONE 不是 None。`

---

## 作者：老咸鱼了 (赞：1)

这个题感觉像是橙题，贪心排个序就过了，就是中文翻译有点坑，如果不许要加新的零件那么输出None，后面的one是大写的。
就按照所谓的性价比排序记录下他原来的编号就行了，性价比最大的拿了反而还降低的话那么后面都可以直接不用拿了。
```cpp
#include<bits/stdc++.h>
using namespace std;
double F,M;
int n;
struct f{
	long long int a,b;
	int num;
}a[10005];
bool cmp(f a,f b)
{
	return a.a*b.b>b.a*a.b;//这个等价于a.a/a.b>b.a/b.b;不过这样写不会出现丢精度的问题。
}
bool ans[10005];
int main()
{
	scanf("%lf%lf%d",&F,&M,&n);
	for(int i=1;i<=n;i++)
	scanf("%lld%lld",&a[i].a,&a[i].b),a[i].num=i;
	sort(a+1,a+1+n,cmp);
	double s=F/M;
	for(int i=1;i<=n;i++)
	{
		F+=a[i].a,M+=a[i].b;
		if((F/M)>s)
		{
			s=F/M;
			ans[a[i].num]=true;
		}
		else
		{
			break;
		}
	}
	bool x=1;
	for(int i=1;i<=n;i++)
	{
		if(ans[i])
		{
			printf("%d\n",i);
			x=0;
		}
	}
	if(x)
	printf("NONE");
	return 0;
}
```


---

## 作者：COUPDETAT (赞：1)

### 手推一组式子
$\because$ 最大化
$$\frac {F+\sum_{i=1}^{n}X_i\times F_i}{M+\sum_{i=1}^{n}X_i\times M_i}$$
      最小化
$$\sum_{i=1}^{n}Xi\times Mi+M$$

~~这个东西看起来非常nb 那我们接下来就要把它干死~~（bushi）

这是啥意思呢

我们已知$F,M$ 然后开始选数

选数的时候要先排序 假如我们有一种方法可以使答案最优

然后能拿就拿即可

### 那么怎么排序呢

性感理解一下 把$Fi$和$Mi$做一个比值

### 严格证明：
if： $\frac{F}{M}<\frac{Fi}{Mi}<\frac{Fj}{Mj}$

so: $\frac{F+Fj}{M+Mj}>\frac{F+Fi}{M+Mi}$

数学题要什么代码啊

[小广告](http://www.coupdetat.cn)

---

## 作者：plwz (赞：1)

数学运算

如果满足 F / M < Fi / Mi < Fj / Mj，就得出 (F+Fj) / (M+Mj) > (F+Fi) / (M+Mi)

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
struct node
{
    double f,m;
    int num;
};
int n,i,b[10005];
double f,m;
node a[10005];
char ch;
int getnum()
{
    ch=getchar();
    for (;ch<'0' || ch>'9';ch=getchar());
    int ret=0;
    for (;ch>='0' && ch<='9';ch=getchar()) ret=ret*10+ch-48;
    return ret;
}
bool cmp(node a,node b)
{
    if ((a.f/a.m)!=(b.f/b.m)) return (a.f/a.m)>(b.f/b.m);
    return a.m<b.m;
}
bool cmq(int a,int b)
{
    return a<b;
}
void init()
{
    f=getnum();m=getnum();n=getnum();
    for (i=1;i<=n;i++)
    {
        a[i].f=getnum();a[i].m=getnum();a[i].num=i;
    }
}
void solve()
{
    sort(a+1,a+n+1,cmp);
    for (i=1;i<=n;i++)
    {
        if ((a[i].f/a[i].m)<(f/m)) break;
        if ((a[i].f/a[i].m)==(f/m) && a[i].m>m) break;
        f+=a[i].f;m+=a[i].m;
        b[++b[0]]=a[i].num;
    }
    if (b[0]==0)
    {
        printf("NONE");
        return;
    }
    sort(b+1,b+b[0]+1,cmq);
    for (i=1;i<=b[0];i++) printf("%d\n",b[i]);
}
int main()
{
    init();
    solve();
    return 0;
}
```

---

