# Elections

## 题目描述

有 $n$ 个候选人，$m$ 个城市，每一个城市给出每一个候选人的票数，票数最多的就被这个城市选了。当票数一样是，号码最小的被这个城市选。获得票数最多的候选人候选人当选，当有多个候选人获得的票数一样时，号码最小的候选人当选。

## 样例 #1

### 输入

```
3 3
1 2 3
2 3 1
1 2 1
```

### 输出

```
2```

## 样例 #2

### 输入

```
3 4
10 10 3
5 1 6
2 2 2
1 5 7
```

### 输出

```
1```

# 题解

## 作者：HNYLMS_MuQiuFeng (赞：2)

这道题是一道比较简单的模拟(是的你没有看错)

具体解释见代码


```cpp
#include<iostream>
using namespace std;
int n,m;//n个候选人，m座城市 
int a,zuiniubidehouxuanren;//变量名皮一下我很开心
int maxn,zuiniubidehouxuanrenmax;
int main()
{
	cin>>n>>m;
	int c[n+1]={0};//存放候选人票数 
	for(int i=1;i<=m;i++)
	{
		zuiniubidehouxuanren=-1;//这两个变量必须每次更新到
        //-1！！！！原因：每个城市可以一张票都不投
		zuiniubidehouxuanrenmax=-1;//本蒟蒻就是因为一开始
        //每次更新到0而WA了第43还是第47个测试点
		for(int j=1;j<=n;j++)
		{
			cin>>a;
			if(a>zuiniubidehouxuanrenmax)//先弄出每个城市投的
			{
				zuiniubidehouxuanrenmax=a;
				zuiniubidehouxuanren=j;
			}
		}
		c[zuiniubidehouxuanren]++;//这位候选人的票数+1
	}
	for(int i=1;i<=n;i++)
	{
		if(c[i]>maxn)maxn=c[i];//先找出票数最大值
	}
	for(int i=1;i<=n;i++)
	{
		if(c[i]==maxn)//按顺序搜，只要找到就输出
		{
			cout<<i;
			return 0;
		 } 
	}//AC啦！锵锵！
}
```
# 杜绝抄袭，从我做起！

---

## 作者：TLMPEX (赞：1)

这是一道模拟题，先求出每个城市中票数最多的候选人，如果票数相等选编号小的，再选出获得城市最多的候选人，如果城市数相等选标号小的。

代码：
```c
#include<bits/stdc++.h>
using namespace std;
int k[110][110],p[110];
int main(){
	int n,m,i,j,z=0;
	cin>>n>>m;
	for(i=1;i<=m;i++){
		int x=0,y=1;//x为这个城市中的最大票数，y为第i个城市的候选人编号
		for(j=1;j<=n;j++){
			cin>>k[i][j];
			if(k[i][j]>x){//如果票数比目前的大，则更新x和y
				x=k[i][j];
				y=j;
			}
		}
		p[y]++;//编号为y的候选人城市数加一
	}
	for(i=1;i<=n;i++)
		z=max(z,p[i]);//取获得城市最多的
	for(i=1;i<=n;i++)
		if(p[i]==z){//找到第一个符合条件的就输出并结束程序
			cout<<i;
			return 0;
		}
}
```


---

## 作者：帝千秋丶梦尘 (赞：1)

## [题目链接在此](https://www.luogu.com.cn/problem/CF570A)

一题裸的不能再裸的模拟

但是要看清题目

我开始就刮了两眼后直接写。。。

结果发现是每次一票最后求总票数

原来我一直以为每个数字是每个人得到的票数最后求总和。。。

另外还要注意的是循环先是城市数量，而输入先是人数

这个注意下就$AC$啦

CODE：
```cpp
#include<bits/stdc++.h>
#define int long long
#define ri register
using namespace std;
int n,m,ans,wz;
int a[101],b[101];
signed main(void)
{
	cin>>n>>m;
	for(ri int i(1);i<=m;++i)
	{
		ans=-1;
		for(ri int j(1);j<=n;++j)
		{
			cin>>a[j];
			if(a[j]>ans)
			{
				ans=a[j];
				wz=j;
			}
		}
		b[wz]++;
	}
	ans=0;
	for(ri int i(1);i<=n;++i)
	{
		if(b[i]>ans)
		{
			ans=b[i];
			wz=i;
		}
	}
	cout<<wz<<endl;
	return 0;
}
```


---

## 作者：Eason_AC (赞：1)

## Content
有 $n$ 个候选人和 $m$ 个城市，每个城市可以给每个候选人投票，已知第 $i$ 个城市给第 $j$ 个人投的选票数是 $a_{i,j}$。我们将第 $i$ 个城市投的票最多的且号码最小的候选人的总票数加 $1$，请求出总票数最多并且号码最小的候选人。

**数据范围：$1\leqslant n,m\leqslant 100,1\leqslant a_{i,j}\leqslant 10^9$。**
## Solution
直接模拟。开个桶把选票丢进对应的人去，然后再去统计票数最多的且号码最小的人即可。
## Code
```cpp
int n, m, a[107][107], v[107], ans;

int main() {
	n = Rint, m = Rint;
	F(i, 1, m) {
		int id = 0;
		a[i][id] = -1;
		F(j, 1, n) {
			a[i][j] = Rint;
			if(a[i][j] > a[i][id]) id = j;
		}
		v[id]++;
	}
	v[ans] = -1;
	F(i, 1, n) if(v[i] > v[ans]) ans = i;
	printf("%d", ans);
	return 0;
}
```

---

## 作者：FuriousC (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF570A)

# 思路

模拟即可

边输入边判断此城市中得票数最高的候选人，然后最后统一找出总得票数最高的候选人即可（详见代码注释）

# 废话不多说，上代码：

```cpp
#include<bits/stdc++.h>//懒人专用头文件 
using namespace std;
int n,m,a,peo,maxp,maxn,ans,vot[105]={0};
//peo是当前城市票数最多的候选人
//maxp是当前城市中当前得票最多的候选人的票数
//maxn是所有城市中票数最多的候选人的票数
//ans是记录总票数最多的候选人的编号
//vot数组记录每位候选人的票数
int main(){
    cin>>n>>m;//输入 
    for(int i=1;i<=m;i++){
        peo=maxp=-0x7FFFF;//先重置 
        for(int j=1;j<=n;j++){
            cin>>a;//输入 
            if(a>maxp){//找出这个城市中票数最多的候选人 
                maxp=a;
                peo=j;//更新maxp与peo 
            }
        }
        vot[peo]++;//此城市中票数最多的候选人加一票 
    }
    for(int i=1;i<=n;i++){//找出最多票的候选人 
        if(vot[i]>maxn){
            maxn=vot[i];
            ans=i;
        }
    }
    cout<<ans<<endl;//输出 
    return 0;//好习惯 
}
```
代码看完了，你学废了吗？

ps：此题解写于2020/11/11，正值美国大选结束，非常应景，~~故有感而发，水了这篇题解~~

---

## 作者：ViXpop (赞：1)

### 正解：模拟+贪心

本来是想做一下离散化的题目来着的，找到了这题之后......

看完题一脸懵逼，这根离散化有关系吗？模拟直接搞定啊......

不愧是红题......

但是我却被这题卡了n久，为什么呢，因为~~我看错题目了~~

我看完题以为是$m$个城市里每个城市有$n$个人，即总共有$m*n$个人，然后就一顿乱搞......还莫名其妙的过了12个点？？？

下面是我乱搞的代码（题意大概是有$m*n$个人，每个人在对应的城市都有选票，选票最多的人成为该城市代表可参加总决赛，最后输出总决赛胜出者）

```
#include<bits/stdc++.h>
#define mem(i,j) memset(i,j,sizeof(i))
#define Endl printf("\n")
#define ka printf(" ")
using namespace std;
inline int read(){
    int res=0,f=1;char ch=' ';
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){res=res*10+ch-'0';ch=getchar();}
    return res*f;
}
void write(int x){
    if(x<0){putchar('-');x=-x;}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=1e2+5;
int n,m,tot,maxn[N],maxv,name,peo[N];
struct node{
    int a,x,y;
}q[N];
int main() {
    n=read(),m=read();
    int k=m;
    for(register int i=1;i<=m;i++)
        for(register int j=1;j<=n;j++)
            q[++tot].a=read(),q[tot].x=i,q[tot].y=j;//x城市 y编号 
    m++;
    while(m--)//寻找每个城市最强者 
        for(register int i=1;i<=tot;i++){
            if(q[i].x!=m)continue;//如果不是该城市的人 跳过 
            if(q[i].a>maxn[m])maxn[m]=q[i].a,peo[m]=q[i].y;//如果比之前最强的人还要强就更新 
            else if(q[i].a==maxn[m]&&q[i].y<peo[m])peo[m]=q[i].y;//如果一样强但是编号小也更新 
        }
    for(register int i=1;i<=k;i++){//在每个城市的最强的人之间找出最最强的人 
        if(maxv<maxn[i])maxv=maxn[i],name=peo[i];//找到更强的，更新 
        else if(maxn[i]==maxv&&peo[i]<name)name=peo[i];//编号更小 
    }
    write(name);
    return 0;
}
```

有兴趣的可以搞一下这个神奇的看错的题目......

#### 回归正题

有了之前看错题的思路，正解思路就很简单了

这个题目大概类似于USA总统选举的过程

即候选人在每个城市获得选票，只有获票最多者可以在这城市里得到一票，其他人票数作废，最后比谁票数多

那么模拟这个过程就解决了

#### 也许有人问，你说的正解不是模拟+贪心吗，那贪心体现在哪里呢

贪心就体现在统计总票数的过程上

### 上代码最直观

```
#include<bits/stdc++.h>
#define mem(i,j) memset(i,j,sizeof(i))
#define Endl printf("\n")
#define ka printf(" ")
using namespace std;
inline int read(){
    int res=0,f=1;char ch=' ';
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){res=res*10+ch-'0';ch=getchar();}
    return res*f;
}
void write(int x){
    if(x<0){putchar('-');x=-x;}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=1e2+5;
int n,m,maxn,maxv,name,peo,w[N];
int main() {
	n=read(),m=read();
	for(register int i=1;i<=m;i++){
		maxn=-1,peo=-1;
		for(register int j=1;j<=n;j++){
			int a=read();
			if(a>maxn)maxn=a,peo=j;//找出每个城市获票最多的人 
		}
		w[peo]++;//这个人获得一票 
	}
	for(register int i=1;i<=n;i++)if(w[i]>maxv)maxv=w[i],name=i;//统计出最大票数
	//由于统计总票数时我们是按照从小到大的序号进行统计的，所以每次更新的结果一定比之前的结果优
	//即就算之后有和最高票数一样的人，他的编号也一定比之前更新的人大
	//所以我们不需要判定有多个最高票数的人的编号大小 
	write(name);
    return 0;
}
```
#### PS:后来本蒟蒻仔细看了看数据范围，发现选票数最大为1e9，而我只是在每个城市的选票中找出最大值，并没有将其记忆化，所以省下了空间，应该也算离散化吧

---

## 作者：不到前10不改名 (赞：0)

//这题其实难了点，一开始使人认为是离散化，其实用冒泡的话根本不需要离散化，只需要记忆数组下标
```
#include<stdio.h>
int n,m,i,j,k,t,q,srx[1001],sry[1001],lhy[1001];
int main()
{
    scanf("%d%d",&n,&m);
    for(i=1;i<=m;++i)
    {for(j=1;j<=n;++j)
    {scanf("%d",&srx[j]);
    sry[j]=j;}//记录
    for(k=1;k<=n;++k)
    for(t=k+1;t<=n;++t)//冒泡，因为这里t=k+1,所以一定t<k，所以无需离散化，号码最小的被这个城市选，t一定号码大，所以k就要在等于是往后移
    if(srx[k]>=srx[t])
    {q=srx[k];
    srx[k]=srx[t];
    srx[t]=q;
    q=sry[k];
    sry[k]=sry[t];
    sry[t]=q;}
    lhy[sry[n]]++;}//桶记录分数
    for(i=1;i<=n;++i)
    sry[i]=i;
    for(k=1;k<=n;++k)
    for(t=k+1;t<=n;++t)
    if(lhy[k]>=lhy[t])
    {q=lhy[k];
    lhy[k]=lhy[t];
    lhy[t]=q;
    q=sry[k];
    sry[k]=sry[t];
    sry[t]=q;}//记录选择的人中号码最小的候选人当选，和前面的冒泡一样，同理的判断
    printf("%d",sry[n]);
    return 0;
}
//QAQ
```

---

## 作者：TRZ_2007 (赞：0)

## Remarks
看见大佬们用上了贪心，本蒟蒻深感不解。这题不就是一个模拟吗？

## Solution
首先这个题目有几个坑点，比如说，TA的读入是一个$m*n$的矩阵，而不是我们平时所想当然的$n*m$的矩阵（我被这里坑了2次）。  
然后好像有一个数据的读入票数是负数，我Max定义成0被卡了。

剩下来就没有坑点了，直接贴代码吧。  

```
#include <bits/stdc++.h>
using namespace std;

const int N = 110;

int x,id,city[N];
int n,m,Max;

int main()
{
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		Max = INT_MIN;id = 0;
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&x);
			if(x > Max)
			{
				Max = x;
				id = j;
			}
		}
		city[id]++;
	}
	id = 0;Max = INT_MIN;
	for(int i=1;i<=n;i++)
		if(city[i] > Max)
		{
			Max = city[i];
			id = i;
		}
	printf("%d\n",id);
}
```

---

