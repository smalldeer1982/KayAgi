# [POI 2006] KRA-The Disks

## 题目描述

Johnny 在他生日的那天收到了来自他父母的生日礼物：一个管子和一套圆盘。管子由若干个高度相等的圆柱体组合而成，并且每个圆盘拥有和每段圆柱相同的高度，每个圆柱体上开大小不同的孔。

Johnny 收到这套礼物后，发明了一个小游戏：他按一定顺序将圆盘放入管子当中，他想算出最后一个圆盘会停在哪个深度。

显然，有两种情况会让圆盘停止掉落：其一是圆盘无法通过小孔（即孔的直径小于圆盘的直径），其二则是被其他圆盘挡住。

Johnny 被他自己发明的游戏难住了，他现在把这个问题交给了你，你一定会帮助他解决这个难题的！

## 说明/提示

$1 \leq n,m \leq 3 \times 10^5$，$1 \leq r_i,k_i \leq 10^9$

## 样例 #1

### 输入

```
7 3
5 6 4 3 6 2 3
3 2 5```

### 输出

```
2```

# 题解

## 作者：_Lemon_ (赞：10)

本题其实并不难

首先我们可以建一个数组cl，保存此位置之前最窄的管子大小。

再从最底下扫一遍，依次看看盘子会卡在哪里；

最后如果最后一个没进去就到顶部，则输出0；

否则输出最后一个卡在哪里。

请注意这里管子的宽度是从上到下输入的，所以上方的先输入。

```cpp
#include<bits/stdc++.h>
using namespace std;
int cl[300001],now,n,m,pan[300001],guan[300001];
int main()
{
    int i,step;
    cin>>n>>m;
    step=n;
    for(i=1;i<=n;i++)
      scanf("%d",&guan[i]);
    for(i=1;i<=m;i++)
      scanf("%d",&pan[i]);
    cl[1]=guan[1];
    for(i=2;i<=n;i++)
      if(cl[i-1]<guan[i]) cl[i]=cl[i-1];
         else cl[i]=guan[i];//记录i之前最窄的位置的宽度。
    for(i=1;i<=m;i++)
     { 
      while(cl[step]<pan[i]) step--; //如果放不下，则向上走。
      step--;
      if(step==0) {
                        cout<<'0';
                        return 0;//如果step超出了最高的管子，直接输出0，结束程序。
                  }
     }
     cout<<step+1;//否则输出最后的位置。
     return 0; 
}
```

---

## 作者：FlashHu (赞：7)

$O(n)$的正解算法对我这个小蒟蒻真的还有点思维难度。考试的时候一看到300000就直接去想各种带log的做法了，反正不怕T。。。。。。

我永远只会有最直观的思路（~~最差的程序效率~~）

题目相当于每次让我们找区间$[1,las-1]$中上数第一个比当前盘子半径小的位置（las为上一次盘子掉到的位置）于是用线段树无脑搞一下，维护区间最小值，每次找这个位置，能往左跳就往左，不能的话再往右，当然如果超过了las-1就不用找了，直接放在las上面（相当于las--）直到全部放完或las=0为止。
```
#include<cstdio>
#define R register int
#define lc u<<1
#define rc u<<1|1
#define G c=getchar()
#define min2(x,y) x<y?x:y
#define in(z) G;\
	while(c<'-')G;\
	z=c&15;G;\
	while(c>'-')z*=10,z+=c&15,G
const int N=300009,M=10000009;
int las,k,a[N],mina[M];//mina记录最小值
void build(R u,R l,R r){
	if(l==r){
		mina[u]=a[l];
		return;
	}
	R m=(l+r)>>1;
	build(lc,l,m);build(rc,m+1,r);
	mina[u]=min2(mina[lc],mina[rc]);
}
int ask(R u,R l,R r){
	if(l==r)return l-1;
	R m=(l+r)>>1;
    //因为要找位置最靠前的，所以优先往左
	if(mina[lc]<k)return ask(lc,l,m);
	if(m<las-1&&mina[rc]<k)return ask(rc,m+1,r);//m要小于las-1
	return las-1;
}
int main(){
	R n,m;
	register char c;
	in(n);in(m);las=n+1;
	for(R i=1;i<=n;++i){in(a[i]);}
	build(1,1,n);
	while(m--&&las){//las=0直接就不放了
		in(k);
		las=ask(1,1,n);
	}
	printf("%d\n",las);
	return 0;
}
```

---

## 作者：封禁用户 (赞：3)

## 发题解啦
因为一些物理原因，盘子一定是向下掉的

所以我们可以搞一个数组r_min[i]来维护r[1]~r[i]的最小值

然后再弄一个指针指向r_min[n]

每次读入一个k，通过向上移动指针来确定每一个盘子放的位置

~~蒟蒻的代码~~  QAQ

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int r[300001],k,r_min[300001];
bool flo[300001];
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!(ch>='0'&&ch<='9'))
    {
        if(ch=='-') w=1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return w?-x:x;
}
int main(){
    n=read();
    m=read();
    for(register int i=1;i<=n;++i)
    {
        r[i]=read();
        if(i!=1) r_min[i]=min(r_min[i-1],r[i]);
        else r_min[i]=r[i];
    }
    int kkk=n;
    for(register int i=1;i<=m;++i)
    {
        k=read();
        int toto=kkk;
        while(k>r_min[kkk]) kkk--;
        if(kkk<=0){cout<<0; return 0;}
        if(toto==kkk&&i!=1) kkk--;
    }
    cout<<kkk;
}
```

---

## 作者：FjswYuzu (赞：1)

&emsp;&emsp;考虑到盘子会卡在从上至下第一个小于其大小的洞，我们维护一个序列 $r$，使得 $p_i=\min \{p_{i-1},r_i\}(p_0=\inf)$，现在的 $p_i=\min\{r\}$ 了。

&emsp;&emsp;我们模拟盘子下落的过程，知道盘子会掉在最后一个大小大于等于这个盘子大小的位置。用指针 $l$ 维护最底的空位，若盘子 $k_i > p_l$，也就是无法掉到这个地方，于是指针前移一位表示这个地方及下面的位置已经无法放置圆盘；直到当前 $k_i \leq p_l$，即为圆盘可以放入，将圆盘放入，指针前移表示当前位置也放不了圆盘了。

&emsp;&emsp;如果在放进圆盘的过程中 $l=0$，即已经无法放置，输出 $0$；否则放完之后，输出 $l+1$ 为最后一个被占用的位置。


```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,r[300005],k[300005],lastChance[300005];
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)	scanf("%d",&r[i]);
	for(int i=1;i<=m;++i)	scanf("%d",&k[i]);
	lastChance[1]=r[1];
	for(int i=2;i<=n;++i)	lastChance[i]=min(lastChance[i-1],r[i]);
	int situ=n;
	for(int i=1;i<=m;++i)
	{
		while(lastChance[situ]<k[i])	--situ;
		--situ;
		if(!situ)	return puts("0")&0;
	}
	printf("%d",situ+1);
	return 0;
}
```

---

## 作者：caidzh (赞：1)

你们怎么都会$O(n)$做法啊，蒟蒻我只会倍增做法，多一个$log$

主要思路就是倍增预处理区间最小值，然后倍增向后跳，边界判一下注意一点就好
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define INF 2147483647
#define LLINF 9223372036854775807
#define LL long long
#define xyx AKIOI
#define Dilute AKIOI
#define Chtholly_Tree AKIOI
#define time_interspace AKIOI
#define memset0 AKIOI
#define Isonan AKIOI
#define Sooke AKIOI
using namespace std;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
const int maxn=600010;
int n,m,a[maxn],now,f[maxn][21];
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();a[n+1]=-INF;
	memset(f,0x3f3f3f3f,sizeof(f));
	for(int i=1;i<=n;i++)f[i][0]=a[i];f[n+1][0]=-INF;now=n+1;
	for(int i=1;i<=19;i++)for(int j=1;j<=n+1;j++)f[j][i]=min(f[j][i-1],f[j+(1<<i-1)][i-1]);
	for(int i=1;i<=m;i++){
		int len=read(),pos=1;
		for(int j=19;j>=0;j--)if(len<=f[pos][j]&&pos+(1<<j)<=now)pos=pos+(1<<j);pos--;
		if(i==m)printf("%d\n",pos);now=pos;
	}
	return 0;
}
```


---

## 作者：xukuan (赞：1)

由于题目翻译并未完全覆盖题目要点，现在发新的翻译（题解在下面）


题目描述：

Johnny在生日时收到了一件特殊的礼物，这件礼物由一个奇形怪状的管子和一些盘子组成。 这个管子是由许多不同直径的圆筒(直径也可以相同) 同轴连接而成。 这个管子的底部是封闭的,顶部是打开的。

下图是由直径为: 5cm, 6cm, 4cm, 3cm, 6cm, 2cm和3cm 的圆筒组成的管子。 

![](http://topoi.top/assets/images/problems/p2955_1.png)

每个圆筒的高度都是相等的, 玩具中所带的盘子也是一些高度和它们相同的圆筒,直径有大有小。Johnny发明了一种游戏,把盘子从管子顶部一个接一个的扔下去,他想知道最后这些盘子落在了哪,假设盘子落下过程中圆心和管子的轴一直保持一致,比如说我们丢下去三个盘子: 3cm, 2cm和5cm, 下图展示了最终它们的停止位置: 

![](http://topoi.top/assets/images/problems/p2955_2.png)

如图可以知道,盘子掉下去以后,要么被某个圆筒卡住,要么就是因为掉在了以前的一个盘子上而停住。Johnny想知道他最后扔下去的那个盘子掉在了哪个位置,你来帮他吧。


输入格式

第一行两个整数n和m(1≤n,m≤300000) 表示水管包含的圆筒数以及盘子总数。 

第二行给出n个整数r_1,r_2,...,r_n(1≤r_i≤1000000000)表示水管从上到下所有圆筒的直径。 

第三行给出mm个整数k_1,k_2,...,k_m(1≤k_j≤1000000000)分别表示Johnny依次扔下去的盘子直径。


输出格式：
一个整数输出最后一个盘子掉在了哪一层,如果盘子不能扔进水管,那么打印0。

输入样例：
```pascal
7 3
5 6 4 3 6 2 3
3 2 5
```

输出样例：
```pascal
2
```

题目来源：

BZOJ1510 POI2006

——————————————————————————————————————————————————————————————————

题解正文：
虽然这题可以用O(nlogn)的方法过，但我还是想了O(n)的方法

每次如果前缀1..x存在点卡住k

也就是Min(r[1]..r[x])<k

就不断将x前移

code：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<map>
#include<set>
#define ll long long
#define INF 2147483647
using namespace std;

ll n,m,Min,a[300010];

int main(){
	scanf("%lld%lld",&n,&m);
	Min=INF;
	for(ll i=1; i<=n; i++){
		scanf("%lld",&a[i]);
		Min=a[i]=min(a[i],Min);
        //a[i]表示(r[1],r[2]......r[i])中的最小值
	}
	
	ll x=n+1; a[0]=INF;
	while(m--){
		ll k; x--;
		scanf("%lld",&k);
		while(k>a[x]) x--;//卡不住的时候向下找
		if(x==0){
			printf("0\n");
			return 0;
            //根本进不去
		}
	}
	printf("%lld",x);//进去到的最小的地方
	return 0;
}
```

---

## 作者：oscar (赞：1)

【POI补全计划#18 POI2006 KRA】

水到随便做的一道题，然而我的做法还是比楼下题解的做法多个log。。。

直觉上二分肯定能过，就没仔细想线性做法

预处理出管道的每个格子上方最小的半径，将该格子的半径设置为最细的那个，位置0的半径设为足够大的数（正确性：通不过上面的部分就到不了这个格子）（作用：方便二分）

然后每次记录上一个盘子掉到的位置x，在0和x之间查找比盘子半径大的最靠下的位置，若查到x则往上摞一个盘子，若查到0则说明后面的盘子都放不进去，其余情况正常处理就好了....

贴代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
const int MAXN=300010;
int siz[MAXN],n,m;
int main()
{
    scanf("%d%d",&n,&m);
    siz[0]=0x3f3f3f3f;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&siz[i]);
        if(siz[i]>siz[i-1])siz[i]=siz[i-1];
    }
    int tmp,cur=n;
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&tmp);
        int l=0,r=cur;
        while(l<r)
        {
            int mid=(l+r+1)/2;
            if(siz[mid]<tmp)r=mid-1;
            else l=mid;
        }
        if(l==cur)cur--;
        else cur=l;
        if(cur==0)break;
    }
    printf("%d\n",cur);
    return 0;
}
```

---

## 作者：年华天地 (赞：0)

## 思路：
首先，我们会很容易发现，如果一个圆柱的直径特别大，但他上方有一个比直径他小的圆柱，那么他的直径相当于是没有用的，因为盘子掉下来必定先经过直径小的圆柱，那么，我们就可以用一个数组记录从$1$号圆柱到这个圆柱直径的最小值，很容易发现它是一个递减的数列。那么，这个盘子会落在哪里呢？一是上一个盘子的上方，二是是直径比它小的圆柱的上方（可以用二分求），我们把两个值比较一下，去个最小值就是当前盘子落下的位置。具体实现看注释把。
## 代码 
```
#include<cstdio>
using namespace std;
const int maxn=6e5;
int n,m,a[maxn],en=1e9+100;
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int ef(int l,int r,int x)
{
	if (r-l<=5)
	{
		for (int i=l;i<=r;i++)
			if (a[i]<x)
				return i;
		return n+1;
	}
	int mid=(l+r)/2;
	if (a[mid]>=x)return ef(mid,r,x);
	else return ef(l,mid,x);
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)a[i]=read();
	for (int i=2;i<=n;i++)a[i]=a[i]<a[i-1]?a[i]:a[i-1];//记录最小值
	for (int i=1,x;i<=m;i++)
	{
		scanf("%d",&x);
		int t=ef(1,n,x);//二分查找比他小的圆柱
		t--;//在比它小的圆柱的上方
		if (en==0)break;//en记录上一次盘子落下的位置
		else if (en<=t)en--;//落在上一次盘子的上方
		else en=t;
	}
	printf("%d",en);
	return 0;
}
```


---

## 作者：老壁灯 (赞：0)

## 这里介绍一种不用二分的做法
对于每个扔下来的盘子，要么落在某个盘子上，要么落在它能掉落的最低位置，那么我们预处理出每个盘子最低会掉到哪里，然后与当前位置比较即可。
详见代码
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=5e5+1000;
struct node{
	int r,id;
}a[maxn];
int rad()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
bool cmp(node x,node y)
{
	return x.r<y.r;
}
int n,m,pos[maxn],r[maxn],st[maxn],top=0,num[maxn],ans=0;
int main()
{
	n=rad();m=rad();
	for(int i=1;i<=n;++i)
	{
		r[i]=rad();
	}
	for(int i=1;i<=m;++i)
	{
		a[i].r=num[i]=rad();
		a[i].id=i;
	}
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;++i)
	{
		if(a[i].r<=r[1])st[++top]=a[i].id;//st中储存原数组下标  
		else pos[a[i].id]=-1;//这个盘子会卡在管道之外 
	}
	r[n+1]=-1;//保证掉到最低点的元素被赋值 
	for(int i=2;i<=n+1;++i)
	{
		while(top&&num[st[top]]>r[i])pos[st[top--]]=i-1;//利用单调性 处理每个盘子掉落的最低层
		if(top==0)break;
	}
	ans=pos[1];
	for(int i=2;i<=m;++i)
	{
		if(pos[i]>=ans)//对于某个盘子，要么掉到某个盘子之上，要么掉到能掉落到的最低层； 
		{
			ans=ans-1;
		}
		else {
			ans=pos[i];
		}
	}
	if(ans<=0)
	{
		printf("0");
	}
	else printf("%d",ans);
	return 0;
}
```


---

## 作者：阔睡王子 (赞：0)

## 单调栈加二分

初看以为是一道模拟题，然后看数据范围发现问题并不是这么简单。

但是很快我们就可以手推样例找到规律：

因为盘子下落时会被上方的小于它的某个管口卡住，你可以发现下面这两个模型是等效的。

![](https://cdn.luogu.com.cn/upload/image_hosting/6mx4yr10.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
![](https://cdn.luogu.com.cn/upload/image_hosting/a78l61rm.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

因此我们可以在输入时就把管口的数组单调化，然后使用二分查找会被卡住的位置，根据当前最低位置分类讨论。

```
#include<cstdio>
using namespace std;
const int maxn=500010,maxm=500010;
int a[maxn],b[maxm],n,m,floor;
int minn(int a,int b)
{
	return a>b?b:a;
}
int check(int x,int l,int r)
{
	if(r-l<=5)//防止边界问题，在r和l距离小于5时直接暴力搜出答案 
	{
		for(int i=l;i<=r;i++)
		{
			if(a[i]<x)
			{
				return i-1;//返回的是小于盘子的管口上面那个位置 
			}
		}
	}
	int mid=(l+r)/2;
	if(a[mid]<x)return check(x,l,mid);
	else if(a[mid]>=x)return check(x,mid,r);
}
signed main()
{
	//数组单调性优化
	//二分优化 
	scanf("%d%d",&n,&m);
	int p=1e9;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		p=minn(a[i],p);
		a[i]=p;
	}
	a[n+1]=0;
	int floor=n+1;//floor表示当前可以放的最低位置 
	for(int i=1;i<=m;i++)
	{
		int x,pos;
		scanf("%d",&x);
		pos=check(x,1,n+1);//二分检查
		if(pos<floor)//如果当前被卡住的位置在最低位置上方，更新floor 
		floor=pos-1;//可以放的最低位置在被卡住的位置上方 
		else floor=floor-1;//不然就放在最低位置上方 
	}
	if(floor<=-1)printf("0");//模型里面不够放 
	else printf("%d",floor+1);
}
```



---

## 作者：lyt123 (赞：0)


### 大多数博主采用的是二维数组的形式，鄙人的做法不需要二维数组
题目说对于100%的数据，有0<=n<=10000，因此我第一个想到的就是建立10000个结构体，每个结构体包含四个变量，分别记入地毯的信息。这样处理数据会很方便。

**思路如下**：

**1：输入数据时，每个结构体储存一个地毯的信息****

**2：暴力枚举，每检验每一块地毯，检验次数+1，如果目标点在地毯范围内，将检验次数传值给结果，表示这是顶部的地毯序号。**

直接上代码

因为鄙人大一正学习C++，所以选这个语言，其实其他语言也很方便的。。

------------
```cpp
#include<iostream>
using namespace std;

struct
{
	int x, y, w, h;   //x，y表示地毯左下角横纵坐标，w，h表示宽与长
}rectangle[10000];   //测试最多有1万个，那就设置1万吧
int main()
{
	int n,i;    //n表示地毯数量 i只是循环变量
	int f_x, f_y;  //这两个代表选择的坐标
	int reckon=0;  //reckon相当于计数器，每次使用加一
	int real;    //表示最终的答案
	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> rectangle[i].x >> rectangle[i].y >> rectangle[i].w >> rectangle[i].h;
	}
	cin >> f_x >> f_y;
	for (i = 0; i < n; i++)
	{
		reckon++;
        //下面语句一眼看去确实很烦，没关系，你只要理解判定的含义就行了
		if (rectangle[i].x + rectangle[i].w >= f_x && rectangle[i].y + rectangle[i].h >= f_y&& f_x >= rectangle[i].x && f_y >= rectangle[i].y)
			real = reckon;
	}
	if (reckon == 0)
		cout << -1;
	else
		cout << real;
}
```


------------
题解就到这里，是不是理解很简单？本人第一次发题解，菜鸟一枚。之前沉迷游戏，后遭遇挫折，深受打击。如今决心戒游，钻研于计算机知识，觊觎大佬博学聪慧。希望能找到和我一样的志同道合的菜鸟，共同学习！

---

## 作者：管仲 (赞：0)

//这题看上去很像一道名叫铺地毯的题目

//可其实不然

//本题复杂度是一个难题

//很多巨佬都有O（n）算法，而我只会nlogn(二分)

//对于这题我一开始只会朴素算法,可也可以用二分

//那么问题来了,这里不是单调序列

//怎么伯？？？

```cpp
	for(i=1;i<=n;i++)
	{
		cin>>r[i];
		if(r[i]>=r[i-1])r[i]=r[i-1];
	}
```

//就巧妙的将此题化为了一个单调递减的区间，为什么能这样做呢？？

//因为加入后面一个数大于等于前面的数，盘子也不会调到该盘子，

//so understand???

```cpp
//本题我的思路是
//当然要用二分了 
//2.先判断该直径是否能容下，如果能容下判断上面是否可以
//2.(1)如果可以落下去
//*1  那么第一个一定是落在第一个小于等于他长度，并且上一个还>=他长度的盘子上
//*2  后面的物品，可以如上所说，也可以落在前一块木块上（有前提）
#include<iostream>
#include<cstdio>
#include<ctime>
#include<cstring>
#include<queue>
#include<map>
#define maxn 300030
using namespace std;
int m,n,k;
long long r[maxn];
int search(int ed,int x)
{
	if(x<=r[ed])return ed-1;
	int left=0;
	int right=ed-1;
	int mid;
	while(left<=right)
	{
		mid=(left+right)/2;
		if(x<=r[mid])
		{
			left=mid+1;
		}
		else right=mid-1;
	}
	return right;
}
int main()
{
	cin>>n>>m;
	int i,j,k;
	int p,q,t;//t代表当前盘子的位置。 
	r[0]=9999999999;
	for(i=1;i<=n;i++)
	{
		cin>>r[i];
		if(r[i]>=r[i-1])r[i]=r[i-1];
	}
	t=n+1;
	for(i=1;i<=m;i++)
	{
		cin>>k;
		t=search(t,k);
		if(t==0)
		{
			cout<<0;
			return 0;
		}
	}
	cout<<t;
	return 0;
}
```

---

## 作者：SHDITYR (赞：0)

无论一个管子的半径多长，只要它上面有比它半径小的管子，它的长就毫无意义。
即一个管子真正有效的半径长度是它之上所有半径长中的最小值

然后按管子从下到上，盘子从前到后的顺序，类似乎归并排序的实现
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int S=300030;
ll r[S]; ll k[S]; 
int n,m;
int main()
{
	scanf("%d %d",&n,&m);
	for(int i=n;i>=1;i--) scanf("%lld",&r[i]);//倒着输入，方便处理
    	//r数组中从下到上储存“有效”的半径长度，就是毫无阻碍时能够掉下来
            //的最大值
	for(int i=1;i<=m;i++) scanf("%lld",&k[i]);//盘子顺序
	for(int i=n-1;i>=1;i--)
		r[i]=min(r[i],r[i+1]);

	int head_1=1; //第head_1个管子
    int head_2=1;//第head_2个盘子
	while(head_1<=n && head_2<=m)
	{
		if(r[head_1]>=k[head_2])
		{
			head_1++; head_2++;
		}
		else
			head_1++;
	}
	if(head_2<=m)//若盘子未全部放进，则输出0
		printf("0\n");
	else//可以全部放入，换算出结果
		printf("%d\n",n-(head_1-1)+1);
	return 0;
}
```

---

## 作者：kczno1 (赞：0)

考虑木块位置上移总次数<=n。

维护当前位置now

假设第i次木块宽x

所以每次如果前缀1..now存在点卡住x

也就是Min(a[1]..a[now])<x

就不断前移

时间O(n)

```cpp
#include<bits/stdc++.h>
using std::min;

#define gc (c=getchar())
#define rep(i,l,r) for(int i=l;i<=r;++i)
int read()
{
    char c;
    while(gc<'0');
    int x=c-'0';
    while(gc>='0')x=x*10+c-'0';
    return x;
}

const int N=3e5+5;
int a[N];

int main()
{
    freopen("1.in","r",stdin);
    int n=read(),m=read();
    int now=a[1]=read();
    rep(i,2,n) now=a[i]=min(read(),now);
    
    now=n+1;a[0]=1e9+5;
    while(m--)
    {
        int x=read();
        do
        {
            --now;
        }
        while(x>a[now]);
        if(!now){puts("0");return 0;}
    }
    printf("%d\n",now);
}
```

---

