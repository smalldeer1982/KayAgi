# [USACO13JAN] Painting the Fence S

## 题目描述

Farmer John has devised a brilliant method to paint the long fence next to his barn (think of the fence as a one-dimensional number line).  He simply attaches a paint brush to his favorite cow Bessie, and then retires to drink a cold glass of water as Bessie walks back and forth across the fence, applying paint to any segment of the fence that she walks past.

Bessie starts at position 0 on the fence and follows a sequence of N moves (1 <= N <= 100,000).  Example moves might be "10 L", meaning Bessie moves 10 units to the left, or "15 R", meaning Bessie moves 15 units to the right.  Given a list of all of Bessie's moves, FJ would like to know what area of the fence gets painted with at least K coats of paint.  Bessie will move at most 1,000,000,000 units away from the origin during her walk.



Farmer John 想出了一个给牛棚旁的长围墙涂色的好方法。（为了简单起见，我们把围墙看做一维的数轴，每一个单位长度代表一块栅栏）

他只是简单的把刷子蘸满颜料，系在他最喜欢的奶牛Bessie上，然后让Bessie来回地经过围墙，自己则在一旁喝一杯冰镇的凉水。（……-\_-|||) 

Bessie 经过的所有围墙都会被涂上一层颜料。Bessie从围墙上的位置0出发，并将会进行N次移动(1 <= N <= 100,000)。比如说，“10 L”的意思就是Bessie向左移动了10个单位。再比如说“15 R”的意思就是Bessie向右移动了15个单位。

给出一系列Bessie移动的清单。FJ 想知道有多少块栅栏涂上了至少K层涂料。注意：Bessie最多会移动到离原点1,000,000,000单位远的地方。


## 说明/提示

PS1：来源：usaco jan silver P01 想看原题的请戳http://www.usaco.org/index.php?page=viewproblem2&cpid=226）

PS2：测试数据也可以在在http://www.usaco.org/index.php?page=jan13problems上下载，还可以看到题解（不过是英文的:-D）

PS3:如果有翻译的问题或题目的不理解，可以在问答后面留言的说。


## 样例 #1

### 输入

```
6 2 
2 R 
6 L 
1 R 
8 L 
1 R 
2 R ```

### 输出

```
6```

# 题解

## 作者：Hades18 (赞：18)

这道题我们可以用差分的思想做，首先，每走一步相当于将走过的区间权值都加1，那么题目就可以转化为区间修改，查询>=k的值的个数，这不难想到树状数组，线段树。当然，由于区间是加上一个相同的值，所以可以使用差分优化。


> Ps：差分，数组b[i]维护原数组a[i]-a[i-1]的值，原数组a[i]的值就是b[i]的前缀和，利用树状数组 ~~线段树~~ 可以做到区间修改(虽然被优化成了点修改)，单点查询。当在原数组[l，r）区间中加上同一个数val，相当于在差分数组中的b[l]+=val,b[r]-=val。

以上所讲，除了差分，在这题都是大材小用，本题可以用扫描线来写。


> Ps：扫描线，记录一条线段的左端点l，右端点r，当你"扫描"到l时，表示你进入了这条线段，当你扫描到r时，表示你离开了这条线段，所以这条线段的覆盖区间为[l，r）。

now：此时被几条线段覆盖。

由于我们只用记录一个点被涂过几次，所以进入一条线段是将now+1，离开一条线段时将now-1，此时我们只需统计now>=k的区间。~~由于数据范围过大~~我们需要离散化，记录每一条线段的左右端点，排序一下，从一个端点到另一个端点，如果此时now>=k，就将answer加上两个端点中的点数。

具体见代码：

```cpp
#include<cstdio>
#include<algorithm>
#define N 100005
using namespace std;
int n,l,len,m,now,i,ans;
char k;
//x记录这个点的坐标，val记录这个点是线段的头还是线段的尾;
struct P{int x,val;int operator<(const P&t)const{return x<t.x;}}line[N<<1];
main()
{
    scanf("%d%d",&n,&m);
    for(i=0;i<n;++i)
    {
        scanf("%d %c",&len,&k);
        //将线段拆成点;
        if(k=='R')
        {
            line[++l]=(P){now,+1};
            line[++l]=(P){now+=len,-1};
        }
        else
        {
            line[++l]=(P){now,-1};
            line[++l]=(P){now-=len,+1};
        }
    }
    sort(line+1,line+l+1);
    //"扫描..."
    now=line[1].val;
    for(i=2;i<=l;++i)
    {
        if(now>=m) ans+=line[i].x-line[i-1].x;
        now+=line[i].val;
    }
    printf("%d",ans);
}
```
精简过的：

```cpp
#include<cstdio>
#include<algorithm>
struct P{int x,y;int operator<(const P&t)const{return x<t.x;}}e[200010];
int l,n,m,i,w,ans;char c;
inline void R(int &x){c=getchar();for(;c<48||c>57;c=getchar());for(x=0;c>47&&c<58;c=getchar())x=(x<<1)+(x<<3)+c-48;}
main()
{
    R(n);R(m);
    for(i=0;i<n;++i)
    {
        R(l);e[i<<1].x=w;
        if(getchar()=='L')
        {
            e[i<<1].y=-1;
            e[i<<1|1]=(P){w-=l,+1};
        }else
        {
            e[i<<1].y=+1;
            e[i<<1|1]=(P){w+=l,-1};
        }
    }std::sort(e,e+(n<<1));
    w=e[0].y;
    for(i=0;i+1<n<<1;w+=e[++i].y)
        if(w>=m)ans+=e[i+1].x-e[i].x;
    printf("%d",ans);
}
```

---

## 作者：Waddles (赞：8)

好像并没有我这种思路的离散化，我来发一波

此题难在如何确定起点和离散化后怎样处理

~~请无视代码中注释的调试语句~~

处理的内容主要是找到上一次的点，如果是L则上一次的点为终点，这一次点为起点，如果为R，这一次点为终点

离散化的内容主要是时间点打散，按时间排序，然后按先终点再起点排序

处理的时候就求第一个多于k的时间点和紧接着第一个小于k的时间点，相减，就OK了~~（实际上这道题不是时间而是涂料，我说时间更形象化吧）~~

我觉得讲的很清楚有什么不明白的评论区可以指出

code:

```
#include<map>
#include<cmath>
#include<stack>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
template<class AC>void r(AC &x){
    x=0;
    int f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        f|=(ch=='-');
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    x=f?-x:x;
    return;
}
struct AC{
    int x;
    int id;
}a[200005];
int n,k,sum,ans,last,flag,id;
bool cmp(AC x,AC y){
    if(x.x!=y.x)return x.x<y.x;
    else return x.id<y.id;
}
int main(){
    r(n);r(k);
    for(int i=1;i<=n;i++){
        int x,f,e;
        char c;
        r(x);cin>>c;
        if(c=='L'){
            f=last-x;
            e=last;
            last=f;
        }
        else{
            f=last;
            e=last+x;
            last=e;
        }
        //printf("%d %d\n",f,e);
        a[i].x=f;
        a[i].id=1;
        a[i+n].x=e;
        a[i+n].id=-1;
    }
    sort(a+1,a+1+n*2,cmp);
//	for(int i=1;i<=n*2;i++){
//		printf("%d %d\n",a[i].x,a[i].id);
//	}
    for(int i=1;i<=n*2;i++){
        sum+=a[i].id;
        if(sum>=k&&!flag){
            flag=1;
            id=a[i].x;
        }
        if(sum<k&&flag){
            flag=0;
            //printf("%d %d\n",id,a[i].x);
            ans+=(a[i].x-id);
        }
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：ueettttuj (赞：7)

[题目](https://www.luogu.org/problem/P2205)

此题将每个端点记录下来，再排序后从小到大扫一遍。用 $col$ 记录接下来的区间的颜色数量。在每段左端点时 $col+1$ ，在右端点时$col-1$。如果 $col>k$，则表示接下来这段区间颜色层数满足条件，统计这段区间距离即可。

代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,k;
long long cnt,ans;
struct node{
	long long id,flag;
};
node a[200010];
bool cmp(const node &qw,const node &we){
	return qw.id<we.id;
}
int main(){
	scanf("%lld %lld",&n,&k);
	long long las=0;
	long long pos;
	char ch;
	for(long long i=1;i<=n;i++){
		scanf("%lld",&pos);
		cin>>ch;
		if(ch=='R'){
			a[++cnt].id=las;
			a[cnt].flag=1;          //记下左端点 
			a[++cnt].id=las+pos;
			a[cnt].flag=-1;         //记下右端点 
			las=las+pos;
		}
		else{
			a[++cnt].id=las-pos;
			a[cnt].flag=1;          //记下左端点 
			a[++cnt].id=las;  
			a[cnt].flag=-1;         //记下右端点 
			las=las-pos;
		}
	}
	sort(a+1,a+cnt+1,cmp);          //排序 
	long long col=0;
	long long ss;
	for(long long i=1;i<=cnt;i++){
		if(a[i].flag==1){           //左端点，颜色层数+1 
			col++;
			if(col==k) ss=a[i].id;
		}
		else{
			col--;                  //右端点，颜色层数-1 
			if(col==k-1){
				ans+=a[i].id-ss;    //统计答案 
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

[双倍经验？？？！！！](https://www.luogu.org/problem/P2070)

---

## 作者：lnwhl (赞：6)

# P2205 [USACO13JAN]Painting the Fence S 题解
- $\text{Upd on 2022.2.8}$ 修改了格式，增加了扫描线的做法。

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P2205)

可怜的奶牛 Bessie 刷围墙。刷 $n$ 段。每段是连续的一段栅栏。最后求刷了 $k$ 次的栅栏数。

其实无非就是区间修改问题，很容易想到 **差分**。但这道题的数据范围还是很大的，所以需要 **离散化**。


------------


## 解法
### $\text{Part 0}$ 暴力模拟
要解这道题，首先可以把题目抽象成用点来覆盖数轴。
可是题目输入的是移动方向和距离啊。我们可以用一个结构体记录每条线段的左右端点。变量 ```place``` 记录奶牛当前位置。

如果移动方向向右，线段的左端点就是 ```place```，```place``` 再加上移动距离，线段的右端点就是改变后的 ```place``` 了！如果移动方向向左也是同样的道理。之后只要模拟一下就可以了。

**注意：下标可能为负数！！！** 所以我们得把每条线段的左右端点进行偏移，也就是都加上一个较大的数。~~（水了一个Part）~~


### $\text{Part 0.5}$ 差分优化
其实就是把 **区间修改** 转变为了两个 **单点修改**。差分不懂的可以右转 BDFS。

[贴一个差分代码](https://www.luogu.com.cn/paste/5kd7kav2)

这样，你就能得到 $60$ 分了，$\textcolor{purple}{\text{RE}}$ 了四个点。数据范围太大了以至于数组开不下，所以我们要进行优化。



### $\text{Part 1}$ 离散化
#### $\text{Part 1.0}$ 前置知识：离散化

~~正文刚刚开始/bs~~

离散化是什么？？？离散化，把无限空间中有限的个体映射到有限的空间中去，以此提高算法的时空效率。通俗的说，离散化是在不改变数据相对大小的条件下，对数据进行相应的缩小。
举个栗子吧：

- 原数据：$1$,$999$,$100000$,$15$；

	处理后：$1$,$3$,$4$,$2$；

- 原数据：{$100$,$200$}，{$20$,$50000$}，{$1$,$400$}；

	处理后：{$3$,$4$}，{$2$,$6$}，{$1$,$5$}；
 
其实，离散化就是缩小数据范围啊！

#### $\text{Part 1.1}$ 离散化具体过程
	
离散化的基本思路就是把线段的左右端点排一个序，将原来点的 **原始坐标** 用 **排序完的序号** 代替。
假设有这样两条线段（图丑勿喷）：

![](https://cdn.luogu.com.cn/upload/image_hosting/kx6x9dnk.png)

离散化之前两条线段的左右端点分别是 {$1$,$800$} 和 {$300$,$1000$}。离散化后用该点的 **排序后的序号** 代替该点的坐标，线段的左右端点就变成了 {$1$,$3$} 和 {$2$,$4$} 了。复杂度就降到了 $O(n)$。

（代码如下）
```
	sort(whl+1,whl+sr1*2+1,cmp);//将左右端点排序
	int cnt=unique(whl+1,whl+2*sr1+1)-whl-1;//求不重复的个数
	for(int i=1;i<=sr1;i++)//离散化
	{
		a[i].left=lower_bound(whl+1,whl+cnt+1,a[i].left)-whl;//将左端点用离散化后的序号表示
		a[i].right=lower_bound(whl+1,whl+cnt+1,a[i].right)-whl;//右端点
	}
```
其他的处理方法和之前一样。但还要注意，统计长度的时候要加上离散化之前的距离。这次可以 $\textcolor{green}{\text{AC}}$ 了。总体的时间复杂度是 $O(nlogn)$
的，来自快排。

#### $\text{Part 1.2}$ 代码
```
#include <iostream>
#include <algorithm>
using namespace std;
int place=0,sr1,sr2,ans=0;
int cf[200006]={},qian[200006],whl[200006];
struct data
{
	int left,right;
}a[100003];
bool cmp(int q,int w)
{
	return q<w;
}
int main()
{
	cin>>sr1>>sr2;
	for(int i=1;i<=sr1;i++)
	{
		int x;
		char y;
		cin>>x>>y;
		if(y=='R')
		{
			a[i].left=place;
			place+=x;
			a[i].right=place;
		}
		else 
		{
			a[i].right=place;
			place-=x;
			a[i].left=place;
		}
		whl[2*i-1]=a[i].left;
		whl[2*i]=a[i].right;
	}
	sort(whl+1,whl+sr1*2+1,cmp);
	int cnt=unique(whl+1,whl+2*sr1+1)-whl-1;
	for(int i=1;i<=sr1;i++)
	{
		a[i].left=lower_bound(whl+1,whl+cnt+1,a[i].left)-whl;
		a[i].right=lower_bound(whl+1,whl+cnt+1,a[i].right)-whl;
	}
	for(int i=1;i<=sr1;i++)
	{
		cf[a[i].left]++;
		cf[a[i].right]--;
	}
	for(int i=1;i<=2*sr1;i++)
	{
		qian[i]=qian[i-1]+cf[i];
		if(qian[i]>=sr2)ans+=whl[i+1]-whl[i]; 
	}
	cout<<ans<<endl;
	return 0;
}
```

### $\text{Part 2}$ 扫描线
$\text{Upd on 2022.2.8}$ 
#### $\text{Part 2.1}$ 思路
扫描线也是一种常用的处理大数据的技巧。思想和离散化也很像。依旧是差分把每条线段拆分成前后两个端点，然后将每一个端点的位置从小到大排序，再用扫描线记录当前重合的数量，遇到起点就 $+1$，遇到终点就 $-1$，如果超过 $k$ 层，将距离累加到答案中。
#### $\text{Part 2.2}$ 代码
```
#include <bits/stdc++.h>
using namespace std;
int n,m;
struct node{int left,right;}a[200005];
bool cmp(node q,node w){return q.left<w.left;}
int main()
{
    cin>>n>>m;
    int k=0,now=0;
    for(int i=1;i<=n;i++)
    {
        int len;char c;
        cin>>len>>c;
        if(c=='L')
        {
            a[++k]={now,-1};
            a[++k]={now-=len,1};
        }
        else
        {
            a[++k]={now,1};
            a[++k]={now+=len,-1};
        }
    }
    sort(a+1,a+k+1,cmp);
    int temp=a[1].right,ans=0;
    for(int i=2;i<=k;i++)
    {
        if(temp>=m)ans+=a[i].left-a[i-1].left;
        temp+=a[i].right;
    }
    cout<<ans;
    return 0;
}
```



## 后记
P2070 也用的是同样的办法，可以练手。



---

## 作者：Minclxc (赞：6)

正解是离散化+差分

楼下的是离线做法

在线做法可以用二叉搜索树来进行离散化

理论复杂度一样是O(nlogn)

但裸的二叉搜索树会被卡，需要平衡操作

最后遍历一遍和楼下题解一样处理就好了


---

## 作者：封禁用户 (赞：5)

类似差分的算法

把每个端点存下来

如果左端点lr=0否则lr=1

然后按位置排序

接下来O(n)扫一遍即可

如果左端点k++,右端点k--

如果k>=m那么就说明这部分被刷了至少m次

统计输出即可

没加读入优化没开O3 84ms 还算快吧...

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
int i,j,k,m,n,x,y,wz;
struct ppp{
    int wz,lr;
}a[200001];
bool cmp(ppp x,ppp y)
{
    return x.wz<y.wz;
}
char c;
using namespace std;
int main()
{
    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++)
    {
        scanf("%d %c",&x,&c);
        a[i*2-1].wz=wz;
        if(c=='R')wz+=x;else wz-=x;
        a[i*2].wz=wz;
        if(a[i*2-1].wz<a[i*2].wz)
        a[i*2-1].lr=0,a[i*2].lr=1;
        else 
        a[i*2-1].lr=1,a[i*2].lr=0;
```
}//存端点信息而不是线段信息
```cpp
    sort(a+1,a+2*n+1,cmp);
    int ans=0;
    for(i=1;i<=n*2;i++)
    {
        if(k>=m)ans+=(a[i].wz-a[i-1].wz);
        if(a[i].lr==0)k++;else k--;
    }
    cout<<ans;
    return 0;
}

```

---

## 作者：OldVagrant (赞：4)

## 题意简述
[题意传送门](https://www.luogu.com.cn/problem/P2205)
## Solution   
线段树可以做，但差分更快。   
对于每次移动，计算出移动后 Bessie 的位置，将这些位置排序并离散化后，把所有相邻的两个位置看做一个区间，区间的左端点和右端点就是这两个位置。然后建一个差分数组 $c$，每次区间修改就在 $c$ 里相应地修改。最后遍历一遍 $c$，设一个变量 $sum$ 记录下差分数组的前缀和，$sum$ 累加到差分数组的第 $i$ 个位置时，对应的就是第 $i$ 个区间被覆盖的次数。然后在累加过程中判断,如果 $sum\geq k$ 就更新答案。
## Code
```c
#include <bits/stdc++.h>
using namespace std;
int n,a[100001],now,tmp,b[100001],ans,x,y,cnt,cf[100001],sum,k; 
char ch;
//下面到主函数前的所有内容都是用于卡常的快读
const int LEN=32768;
char BUF[LEN],*Pin,*Pin_last,PUF[LEN],*Pout=PUF,*Pout_last=PUF+LEN-1;
char gc(){
	return Pin==Pin_last&&(Pin_last=(Pin=BUF)+fread(BUF,1,LEN,stdin),Pin==Pin_last)?EOF:*Pin++;
}
int read(){
	int x=0;
	char c=gc();
	while(c>57||c<48) c=gc();
	while(c>47&&c<58) x=x*10+c-48,c=gc();
	return x;
}
int main(){
	n=read(),k=read()-1;//这里直接减一，后面判断的时候直接判大于即可
	for(int i=1;i<=n;i++){
		tmp=read(),ch=gc();
		while(ch!='L'&&ch!='R') ch=gc();
		ch=='L'?now-=tmp:now+=tmp,a[i]=b[i]=now;
	}sort(b,b+n+1);//注意这里要把b[0]也算进排序的范围里，因为牛最开始站在位置0
	for(int i=0;i<=n;i++) a[i]=lower_bound(b,b+n+1,a[i])-b;
	for(int i=0;i<n;i++) a[i]>a[i+1]?(++cf[a[i+1]],--cf[a[i]]):(++cf[a[i]],--cf[a[i+1]]);//直接在差分数组上修改
	for(int i=0;i<n;i++){
		sum+=cf[i];//更新当前点被覆盖了几次
		if(sum>k) ans+=b[i+1]-b[i];
	}printf("%d",ans);
	return 0;
}
```


---

## 作者：VanishmentThisWorld (赞：4)

还是没有线段树题解……只好我自己写一篇了。

------------

首先，把 Bessie 的每一次移动都转换成将一段**区间**染上一层颜料

因为数据范围较大，考虑离散化区间左右端点

然后考虑用线段树维护一下每个点被染了几层,最后每次先找一段小于 $k$ 层的，再找一段大于等于 $k$ 的算入贡献，注意更改 $i$ 的下标为 $r+1$ ，因为前面的已经计算过避免重复计算。

但是！！！

单纯的这样写 WA 了

[记录](https://www.luogu.com.cn/record/75418607)

于是我调了好久，最后改了一下：

```cpp
for(int i=1;i<=n;i++)change(1,1,tot,m[al[i]],m[ar[i]]);
```

变成

```cpp
for(int i=1;i<=n;i++)change(1,1,tot,m[al[i]],m[ar[i]]-1);
```

过了

------------

为什么呢？画图解释。

![](https://cdn.luogu.com.cn/upload/image_hosting/fky7c4nk.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/yjo0ogl4.png)

讲白了就是一个左闭右开的区间

（完）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define lc(x) x<<1
#define rc(x) x<<1|1
const int maxn=1e5+5;
char op;
int n,k,x=2e9,y,tot;
int al[maxn],ar[maxn],a[maxn<<1],cnt;
map<int,int>m,e;
int tag[maxn<<2],sum[maxn<<2];//线段树
void addtag(int x,int l,int r,int v){
	tag[x]+=v;sum[x]+=(r-l+1)*v;
}
void pushdown(int x,int l,int r){
	if(tag[x]){
		int mid=(l+r)>>1;
		addtag(lc(x),l,mid,tag[x]);
		addtag(rc(x),mid+1,r,tag[x]);
		tag[x]=0;
	}
}
void pushup(int x){
	sum[x]=sum[lc(x)]+sum[rc(x)];
}
void change(int x,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr){
		addtag(x,l,r,1);return;
	}
	int mid=(l+r)>>1;
	pushdown(x,l,r);
	if(ql<=mid)change(lc(x),l,mid,ql,qr);
	if(qr>mid)change(rc(x),mid+1,r,ql,qr);
	pushup(x);
}
int query(int x,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return sum[x];
	int mid=(l+r)>>1,res=0;
	pushdown(x,l,r);
	if(ql<=mid)res+=query(lc(x),l,mid,ql,qr);
	if(qr>mid) res+=query(rc(x),mid+1,r,ql,qr);
	return res;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>y>>op;
		if(op=='R'){//处理区间
			al[i]=x;ar[i]=x+=y;
		}else{
			ar[i]=x;al[i]=x-=y;
		}
		a[++cnt]=al[i];a[++cnt]=ar[i];
	}sort(a+1,a+1+cnt);//离散
	for(int i=1;i<=cnt;i++)if(a[i]!=a[i-1])m[a[i]]=++tot,e[tot]=a[i];
	int ans=0,l,r;
	for(int i=1;i<=n;i++)change(1,1,tot,m[al[i]],m[ar[i]]-1);//染色
	for(int i=1;i<=tot;i++){//统计
		l=i;
		while(l<=tot&&query(1,1,tot,l,l)<k)l++;
		if(l>tot)break;
		r=l;
		while(r<=tot&&query(1,1,tot,r,r)>=k)r++;
		r=min(r,tot);
		ans+=e[r]-e[l];
		i=r;
	}
   return 0;//达咩
	cout<<ans<<endl;
}
```

---

## 作者：巨型方块 (赞：4)

my blog:


http://blog.csdn.net/largecub233/article/details/69943586

本来要抄题解的 ，结果发现搜不到；

….
其实就是一个离散化；

假如现在的点是now;

要向右移动x个单位；

我们直接在now的地方+1;

在now+x的地方-1；

就好了；

然后排序判重乱搞；

要注意它是一个单位长度是一个栏栅；

所以2个点组成一个栏栅；


```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<map>
#define Ll long long
using namespace std;
map<int,int>F;
int q[300000],top;
int n,m,now,x,ans;
char c;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&x);
        cin>>c;
        if(c=='R'){
            q[++top]=now;
            F[q[top]]++;
            q[++top]=now+x;
            F[q[top]]--;
            now+=x;
        }else{
            q[++top]=now-x;
            F[q[top]]++;
            q[++top]=now;
            F[q[top]]--;
            now-=x;
        }
    }
    sort(q+1,q+top+1);
    now=F[q[1]];
    for(int i=2;i<=top;i++)
        if(q[i]!=q[i-1]){
            if(now>=m)ans+=q[i]-q[i-1];
            now+=F[q[i]];
        }
    printf("%d",ans);
}
```

---

## 作者：BrotherCall (赞：3)

## 核心思想：利用差分实现离散化，求线段覆盖问题。
### 我们以样例为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/0e0rs6hu.png)

线段覆盖情况如图所示。

### 就一般情况而言：

我们的思路为：用一个“桶（可用 $map$ 或 数组）“标记一个区间内的线段覆盖条数，再从头到尾扫一遍，记录哪些部分被覆盖条数 $ >= k$ 。

而这样做，付出的时间以及空间的代价是巨大的。

从空间方面考虑：数组需要从 $-1e9$ 开到 $+1e9$，显然是会 $RE$ 的。

从时间方面考虑：光从头到尾扫描一遍，都需要 $O(Dis(max) - Dis (min))$ ，即最远正半轴距离与最远负半轴距离的差。

### 于是，我们考虑用 差分 + 离散化 实现优化：

将每条线段的左端点记录下来，并使其权值 $ +1$ ；将每条线段的右端点记录下来，并使其权值 $-1$ 。将所有端点按其位置从小到大排序，用变量 $sum$ 对于每段覆盖的线段个数进行记录，这样遍历每一条线段即可。

从空间方面考虑：需要一个长度为 $2n$ 的数组。

从时间方面考虑：读入 $O(n)$ ，快排 $O(nlogn)$ ，对每一个端点遍历 $O(2n)$ ， 总时间复杂度为 $O(nlogn)$ 。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;

int n,k;
ll next,now,last,s,sum;
char ch;
struct qz{
	ll seat,num;
}QZ[200010];//数组需开到 2n 

bool compare(qz x1,qz x2){
	return x1.seat < x2.seat;//按端点位置从小到大排序 
}

int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>next>>ch;
		last = now;
		if(ch == 'R'){
			now += next;
			QZ[i].seat = last;
			QZ[i].num = 1;
			QZ[i + n].seat = now;
			QZ[i + n].num = -1; 
		}
		if(ch == 'L'){
			now -= next;
			QZ[i].seat = now;
			QZ[i].num = 1;
			QZ[i + n].seat = last;
			QZ[i + n].num = -1;
		}
	}
	//以上是对每个端点的记录 
	sort(QZ + 1,QZ + 1 + 2 * n,compare);//将端点从小到大排序 
	last = QZ[1].seat;//记录第一个端点的位置 
	sum = QZ[1].num;//记录当前被多少条线段覆盖 
	ll ans = 0;
	for(int i = 2;i <= 2 * n;i ++){
		sum += QZ[i].num;//修改线段覆盖的条数 
		if(last == QZ[i].seat)continue;//如果还是同一个端点，则不计算线段长度 
		if(sum - QZ[i].num >= k)ans += QZ[i].seat - last;//如果线段覆盖条数 >= k，则将区间长度加在答案中 
		last = QZ[i].seat;
	} 
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：caibet (赞：1)

### 题意：

[原题 Link](/problem/P2205)

### 解法：

乍一看，这不就是个差分区间修改吗？

然后再一看，哦豁，Bessie 最多会移动到离原点 $1,000,000,000$ 单位远的地方。那么我们肯定不能直接差分，还需要离散化一下。

具体来说，Bessie 从坐标 $0$ 开始，$0$ 已经是待离散化的数。若往右走 $2$ 个单位，我们就把 $2$ 加入待离散化的数中；接着往左走 $6$ 个单位，那就把 $-4$ 加入。

离散化之后，各个到达的坐标就变成了正整数。这就很方便我们进行修改。但值得注意的是，若从 $1$ 走到 $3$，只给 $2$ 个区间，而不是 $3$ 个区间涂上了颜色。因此我们在区间修改，从 $x$ 涂到 $y$ 时，差分的操作不应是 `d[x]++;d[y+1]--;`，而是 `d[x]++;d[y]--;`。

最后我们求出每个离散化后区间被覆盖过的次数 $cnt$。如果 $cnt\ge k$，且这个区间实际大小为 $len$，显然被覆盖过超过 $k$ 次的区间的总数就会增加 $len$。

代码如下。

```cpp
namespace{
	const int lim=1e5+3;
	int m,k,cur,d[lim],sum;
	vector<int> a,b;//离散化用数组
	void work(){
		m=read();k=read();
		a.push_back(0);
		b.push_back(0);
		F(i,0,<m){
			Int d=read(),c=readc();
			if(c=='L') cur-=d;
			else cur+=d;
			a.push_back(cur);
			b.push_back(cur);
		}
		{//经典离散化
			vector<int> p;//这个数组记录一个被离散化数的实际坐标
			sort(b.begin(),b.end());
			F(i,0,<=m){
				p.push_back(b[i]);
				a[i]=lower_bound(b.begin(),b.end(),a[i])-b.begin()+1;
			}
			b=p;//b 不用了所以干脆覆盖掉
		}
		F(i,0,<m){
			Int p1=min(a[i],a[i+1]),p2=max(a[i],a[i+1]);
			d[p1]++;d[p2]--;//差分区间修改
		}
		F(i,1,<=m)d[i]+=d[i-1];
		F(i,1,<=m){
			if(d[i]>=k){
				sum+=b[i]-b[i-1];//加入覆盖次数不少于 k 次的区间实际大小
			}
		}
		put("%d",sum);
	}
}
```

---

## 作者：Usada_Pekora (赞：1)

输入，并记录左右端点。

排序后进行一次扫描。

扫描时记录颜色数量，若颜色数量超出限制 ，则记录区间长度。

```cpp
#include <cstdio>
#include <algorithm>
#define NMAX 100005
using namespace std;
struct Event {
	int x;
	int inc;
	bool operator<(Event const& e) const {
		return x < e.x;
	}
};
Event events[2*NMAX];
int main() {
//	freopen("paint.in","r",stdin);
//	freopen("paint.out","w",stdout);
	int n, k;
	scanf("%d", &n);
	scanf("%d", &k);
	int x = 0;
	for (int i = 0; i < n; i++) {
		int dist;
		scanf("%d", &dist);
		char c;
		do { c = fgetc(stdin); } while (c != 'L' && c != 'R');
		int x1 = x + dist * (c == 'L' ? -1 : 1);
		events[2*i].x = min(x, x1);
		events[2*i].inc = 1;
		events[2*i+1].x = max(x, x1);
		events[2*i+1].inc = -1;
		x = x1;
	}
	sort(events, events + (2*n));
	int nCoats = 0;
	int answer = 0;
	for (int i = 0; i < 2*n; i++) {
		if (i > 0 && nCoats >= k) {
			answer += events[i].x - events[i-1].x;
		}
		nCoats += events[i].inc;
	}
	printf("%d\n", answer);
	return 0;
}
```



---

## 作者：xxasmcd (赞：0)

这道题我的思路是差分+扫描线。

先对每一条线段进行差分处理，将它拆成两端的两个点，分别附一个值，正一和负一，方便区分左端点和右端点，为了将来扫描线做预处理。

然后将每一个端点的位置从小到大排序，再用扫描线记录当前重合的数量，最后如果超过 k 层，将两端的距离累加到答案中。

代码如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
struct node
{
    int x,v;
}stu[200005];
bool cmp(node a,node b)
{
    return a.x<b.x;
}
int main()
{
    cin>>n>>m;
    int k=0,o;
    for(int i=1;i<=n;i++)
    {
        int len;
        char c;
        cin>>len>>c;
        if(c=='L')
        {
            stu[++k]={o,-1};
            stu[++k]={o-=len,1};
        }
        else
        {
            stu[++k]={o,1};
            stu[++k]={o+=len,-1};
        }
    }
    sort(stu+1,stu+k+1,cmp);
    int temp=stu[1].v;
    int ans=0;
    for(int i=2;i<=k;i++)
    {
        if(temp>=m)ans+=stu[i].x-stu[i-1].x;
        temp+=stu[i].v;
    }
    cout<<ans;
    return 0;
}

```

---

