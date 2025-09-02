# [PA 2014] Bohater

## 题目描述

在一款电脑游戏中，你需要打败 $n$ 只怪物（从 $1$ 到 $n$ 编号）。

为了打败第 $i$ 只怪物，你需要消耗 $d_i$ 点生命值，但怪物死后会掉落血药，使你恢复 $a_i$ 点生命值。

任何时候你的生命值都不能降到 $0$（或 $0$ 以下）。

请问是否存在一种打怪顺序，使得你可以打完这 $n$ 只怪物而不死掉。

## 说明/提示

对于 $100\%$ 的数据，$1\le n,z\le 10^5$，$0\le d_i,a_i\le 10^5$。

## 样例 #1

### 输入

```
3 5
3 1
4 8
8 3```

### 输出

```
TAK
2 3 1 ```

# 题解

## 作者：lgswdn_SA (赞：13)

## LG4025 Bohater

传送门：https://www.luogu.com.cn/problem/P4025

## 题意

一开始有 $z$ 点血。有 $n$ 只怪物，每只怪物需要先消耗 $d_i$ 点血，然后会恢复 $a_i$ 点血。中途不能死掉。求一种可行的打怪顺序。

$1\le n,z\le 10^5$。

一个需要思考的贪心。

## 题解

首先一个很明显的贪心，先打打了可以回血的怪物，再打打了会掉血的怪物。

这个贪心的一个证明：假如一个回血怪物放在掉血怪物前面都没法打掉，那么放在掉血怪物后面更不可能打掉。

然后考虑回血怪物以及掉血怪物内部的安排贪心。

先考虑回血怪物。

1. 对于那些 $d_i<z$ 的回血怪物，直接打即可。
2. 对于不能的，按照 $d_i$ 从小到大排序。可以用调整法证明。

然后考虑掉血怪物。有两种理解方法。第一种还是用调整法来做。第二种我们可以发现，如果倒过来反向看，掉血怪物相当于回血怪物（从终局往回走，$a_i$ 作为掉血量，$d_i$ 作为回血量，每次血量都不能小于 $0$），于是我们按照倒叙视角的“掉血量”排序，即按照 $a_i$ 排序。

排完序模拟即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
using namespace std;
const int N=1e5+9;

int n,sum,ans[N];
struct mons {int d,a,id;} a[N];
bool cmp(const mons &x, const mons &y) {
	if((x.a-x.d)*(y.a-y.d)<0) return x.a-x.d>0;
	else if(x.a-x.d<0) return x.a>y.a;
	else return x.d<y.d;
}

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

signed main() {
	n=read(), sum=read();
	rep(i,1,n) a[i].d=read(), a[i].a=read(), a[i].id=i;
	sort(a+1,a+n+1,cmp);
	rep(i,1,n) {
		sum-=a[i].d;
		if(sum<=0) return puts("NIE"), 0;
		ans[i]=a[i].id;
		sum+=a[i].a;
	}
	puts("TAK");
	rep(i,1,n) printf("%lld ",ans[i]);
	return 0;
}
```



---

## 作者：huanyue (赞：12)

读完题你大概就能想到是贪心无疑了,

这道题的灵魂就是~~狗头保命~~

显然的是,首先,我们要先打能回血的,别跟我说,~~我超勇的,一刀999~~

那么对于打回血的怪,我们有两种贪心策略

*   按照$d_i$升序打
*   按照$a_i$降序打

如果按照$a_i$升序,我们可以构造出

a=9999999999,d=100000000,

打BOSS奖励虽然丰厚,但是你~~开局一条狗~~

所以还是乖乖做个肝帝,勇贪心策略一吧.



**于是你养成了套神装**

好了接下来这题的难点来了,接下来的贪心策略是什么

*   按照$d_i$升序打

*   按照$d_i-a_i$升序打

*   按照$a_i$降序打

    

我一开始都直接否定了第三种贪心策略,然后试了两次前两种,然后就被自己~~构造的数据卡掉了~~

我就不给出数据了,直接想吧.

再打这些掉血的怪中,如果有一个皮糙肉厚的大BOSS,同时打完它也有大量的回复血量,

然而我们打不死,

那么我们不应该先打比较菜~~升级~~的吗.

**我们已知但是在这组怪中,打完后都会掉血,那么你打完菜的之后,你依然打不过大BOSS了吗?**

所以~~菜是原罪~~



好的给出严格证明

​				设最后剩下$T$的生命值，显然$T$的大小与顺序无关,我们从最后状况往前推.

​				于是问题转化成这样,当前我有$T$的血量,每倒推一个怪之后,会加上这个怪的$d$,扣去$a_i$,

随后我突然想起来刚刚我好像解决过这个问题.

​				还没懂?从头再读一遍.

CODE
```cpp
/*
 * @Author: Huanyue 
 * @Date: 2020-02-13 09:19:22 
 * @Last Modified by: Huanyue
 * @Last Modified time: 2020-02-13 10:14:43
 */

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>
#define rgi register
typedef long long ll;
using namespace std;

const int N = 1e5 + 10;
const int inf = 0x3f3f3f3f;

inline void write(register int x)
{
    if (x < 0)
    {
        putchar('-'), x = -x;
    }
    if (x >= 10)
    {
        write(x / 10);
    }
    putchar('0' + x % 10);
}

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = ((x << 3) + (x << 1) + (ch ^ 48));
        ch = getchar();
    }
    return x * f;
}

struct master
{
    int id, a, d;
    master(int id = 0, int a = 0, int d = 0) : id(id), a(a), d(d) {}
} add[100005], minu[100005];
int n, addcnt, minucnt;
long long z;

bool cmp1(master a, master b)
{
    return a.a > b.a;
}
bool cmp2(master a, master b)
{
    return a.d < b.d;
}
int main()
{
    n = read(), z = read();
    for (rgi int i = 1; i <= n; i++)
    {
        int d = read(), a = read();
        if (a >= d)
            add[++addcnt] = master(i, a, d);
        else
            minu[++minucnt] = master(i, a, d);
    }

    sort(minu + 1, minu + minucnt + 1, cmp1);
    sort(add + 1, add + addcnt + 1, cmp2);
    
    for (rgi int i = 1; i <= addcnt; i++)
    {
        if (add[i].d >= z)
        {
            printf("NIE\n");
            return 0;
        }
        else
            z = z - add[i].d + add[i].a;
    }

    for (rgi int i = 1; i <= minucnt; i++)
    {
        if (minu[i].d >= z)
        {
            printf("NIE\n");
            return 0;
        }
        else
            z = z - minu[i].d + minu[i].a;
    }

    printf("TAK\n");
    for (rgi int i = 1; i <= addcnt; i++)
    {
        write(add[i].id);
        putchar(' ');
    }
    for (rgi int i = 1; i <= minucnt; i++)
    {
        write(minu[i].id);
        putchar(' ');
    }
    return 0;
}
```


---

## 作者：二gou子 (赞：8)

# 打怪
## 思路：
作为从幼儿园就开始玩游戏的我，遇到这个题心中暗喜。~~打怪？就这？还绿题？我不是随便切吗？既然你给我送咕值，那我就收下了。~~首先这很明显是一道贪心题，那么如何排序才能得到最优策略呢？首先我们按照回血量-掉血量排序，找到打他开始掉血的那个怪的编号。然后就相当于把所有的怪分成了两部分，一部分是打完他回血，另一部分是打完他掉血。很明显，当然是先打回血的才能确保是最优策略。在打回血怪的时候，可能有的怪打死他能回很多血，但是他的伤害也很高，所以我们需要先打小怪来加血，最后再去打血多的怪。我们可以这么理解，因为打回血怪一直是在回血，所以我们可以把伤害高的放到后面，这样我们就可以打完小怪恢复充足的血量再去打BOSS。感性理解一下可以证明这样打是正确的。也就是按伤害从小到大排序，然后打。好的，前半部分解决了，那么后半部分怎么办呢？我们很容易可以想到，打回血怪的时候血越打越多，那么就越有机会来杀掉最后的BOSS，所以后打BOSS。那么打掉血怪的时候，我们应该先把BOSS打掉。因为打掉血怪的时候你一直是在掉血，如果你现在不打死他，以后你血越来越少，那就更加不可能打死他了。所以这样就找到了贪心策略：先按净增加的血量排序（掉血怪是负的），打回血怪时按伤害从小到大排序，打掉血怪时按伤害从大到小排序。

###  _**但是这样是不对的**_ 

 比如我给你一组数据，在你打完回血怪的时候你还剩11滴血，这个时候有三只掉血怪，对你造成的伤害和你打死他回复的血量分别是（8,1），（4,3），（3,2），这个顺序是我们按照贪心策略打怪的顺序，然后我们发现，在打完第一只BOSS之后，你打不死第二只怪，所以NIE。但是如果我们更改一下顺序，先打死两只小怪，这个时候你还剩9滴血，是可以再去击杀BOSS的，这样就可以打死所有的怪。这个时候我们回头想一想，我们之前的贪心策略为什么不对。 

让我们回到一开始打回血怪时贪心的本源，如果我现在可以打死小怪，我肯定不亏，因为至少我不会掉血。打回血怪时我不用去考虑到底能回多少血，因为我只要不掉血就行。只要保证一直在增加血量，我就有机会去打死伤害更高的怪。但是打掉血怪的时候不一样，我们还要考虑他们给予我们的回血。我们可以用一种整体的思路去考虑这个问题：我们的终极目标是打死所有的怪，那么也就是说，我们打掉血怪时受到的伤害总量是一定的，那么我们只要回复尽可能多的血量，就越有机会打死所有的怪。那么这个时候我们就得到了这道题的正解：掉血怪按照回血量从大到小排序。

```c
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long int ll;
ll n,m;
struct guai{
	ll shang,xue,hao,zeng;//汉语拼音QWQ 
}a[100010];
ll cmp1(guai x,guai y){
	return x.zeng>y.zeng;
}
ll cmp2(guai x,guai y){
	return x.shang<y.shang;
}
ll cmp3(guai x,guai y){
	return x.xue>y.xue;
}//三个阶段不同的排序 
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&a[i].shang,&a[i].xue);
		a[i].zeng=a[i].xue-a[i].shang;
		a[i].hao=i;
	}
	sort(a+1,a+1+n,cmp1);//第一阶段的排序 
	int t=0;
	for(ll i=1;i<=n;i++){
		if(a[i].zeng<0){
			sort(a+1,a+i,cmp2);
			sort(a+i,a+n+1,cmp3);
		    t=1;//这里有一个细节要注意一下，如果所有的怪都是回血怪，那么它里面就没有进行排序，但是实际上我们依然要按照贪心策略进行排序。所以如果里面没有排序，那么我们就到外面排一次序 
			break;
		}
	}
	if(t==0){
		sort(a+1,a+n+1,cmp2);
	}//在外面单独排序 
	for(ll i=1;i<=n;i++){
		if(m<=a[i].shang){
			printf("NIE\n");
			return 0;
		}//如果血量小于等于0，那么结束循环同时输出不能 
		m-=a[i].shang;
		m+=a[i].xue;
	}
	printf("TAK\n");
	for(ll i=1;i<=n;i++){
		printf("%d ",a[i].hao);//可以的话输出编号 
	}
	return 0;
}
```


---

## 作者：一Iris一 (赞：5)

# 题意简述

总计$n$只怪，要求死绝，并且中途血量不为零，每只怪都有对应的回血机制

*****
# 题解思路
对于全部的怪，我们可以对其分成三类

$1^{\circ}$ 初始状态我们能击杀的，并且击杀后血量增加

$2^{\circ}$ 初始状态我们不能击杀，但击杀后血量增加

$3^{\circ}$ 不论我们目前什么状态，击杀后血量减少
 
 对于上述三种类别，很容易知道，
 
 优先执行第一种，其次执行第二种，最后执行第三种
 
 诶，这个这么简单应该不用证吧 ~~这不是有手就行吗~~
 
 接下来，我们比较关心每个类别内部的排序
 
 在$1^{\circ}$中，该类别完全不需要排序，直接枚举下去即可，反正每个怪的血量均比初始值小
 
 在$2^{\circ}$中，对该类，我们可以按照怪物的血量作为关键字从小到大排序
 
 假设我们不按照此法排序的话，可能会出现，虽然击杀后回血量很高，但是目前我们的血量不够的情况，这回被错判成$NIE$。
 
 在$3^{\circ}$中，我们按照击杀每只怪回血量来从大到小排序
 
 这里证明一下这个贪心策略：
 
对于第三类怪物，假设共计$k$只怪

总计消耗的血量是一定的

$$\sum^{k}_{i=1}d_i$$

但对于他们的回血量来说
最后一个怪，并不能回血 ~~是吧~~
所以我们将回血量最小的怪放到最后一定是最优的
****

# 代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

struct node{
	long long  d;
	long long  a;
	long long  k;
	long long  num;
}t[2332333];

node a[233333];
node b[233333];
node c[233333];
long long  f[2333333];
long long  bi=0;
long long  ai=0;
long long  ci=0;
long long  py=0;

long long  n,z;

bool cmpb(node a,node b)
{
	return a.d<b.d;//似乎没什么用
}

bool cmpa(node a,node b)
{
	return a.k>b.k;
}

bool cmpc(node a,node b)
{
	return a.a>b.a;
}

int  main()
{
	
	
	ios_base::sync_with_stdio(false);
	cout.tie(NULL);
	cin.tie(NULL);
	
	
	cin>>n>>z;
	
	for(long long  i=1;i<=n;i++)
	{
		cin>>t[i].d;
		cin>>t[i].a;
		t[i].num=i;
		t[i].k=-t[i].d+t[i].a;
	}
	
	for(long long  i=1;i<=n;i++)
	{
		if(t[i].d<z && t[i].k>=0)
		{
			a[++ai]=t[i];
			continue;
		}
		if(t[i].k>=0  && t[i].d>=z)
		b[++bi]=t[i];
		else{
			c[++ci]=t[i];
		}
		
	}

	
	sort(b+1,b+1+bi,cmpb);
	sort(a+1,a+1+ai,cmpa);
	sort(c+1,c+1+ci,cmpc);
	
	for(long long  i=1;i<=ai;i++)
	{
		f[++py]=a[i].num;
		z+=a[i].k;
	}
	
	for(long long  i=1;i<=bi;i++)
	{
		if(z<=b[i].d)
		{
			cout<<"NIE";
			return 0;
		}
		else{
			f[++py]=b[i].num;
			z+=b[i].k;
		}
	}
	
	for(long long  i=1;i<=ci;i++)
	{
		if(z<=c[i].d)
		{
			cout<<"NIE";
			return 0;
		}
		else{
			f[++py]=c[i].num;
			z+=c[i].k;
		}
	}
	
	cout<<"TAK"<<'\n';
	
	for(long long  i=1;i<=py;i++)
	{
		cout<<f[i]<<" ";
	}

}

```

*****
 安利一下自己博客[别嫌弃太丑](https://www.cnblogs.com/-Iris-/)
 

---

## 作者：Little09 (赞：3)

题目中没有说怪物掉落的血药 $a_i$ 和消耗的生命值 $d_i$ 的大小关系，所以我们可以把怪物分为两类：补血怪（$d_i\le a_i$）与掉血怪（$d_i> a_i$）。

容易发现的是，一定是先打完补血怪再打掉血怪。因为打掉血怪没有益处，反而减少生命值。所以我们把它分为两部分，第一部分是打补血怪，第二部分是打掉血怪。

第一部分，在打每个补血怪时的要求是 $z>d_i$。由于 $z$ 会逐渐变大，所以应当先打 $d_i$ 小的怪物。

第二部分，在打每个掉血怪时的要求是 $z>d_i$。但是 $z$ 会逐渐变小，我们不能先打 $d_i$ 小/大的怪物。怎么办？我们考虑倒序，计算打完所有怪物后的剩余生命值，从最后开始考虑。每一个怪物相当于让 $z$ 先减去 $a_i$ 再加上 $d_i$。条件变成了 $z>a_i$。由于是倒序，$z$ 会逐渐增大，所以倒序按 $a_i$ 从小到大打就行了。调整回正序就是按照 $a_i$ 从大到小。

[感觉有异曲同工之妙的题目](https://www.luogu.com.cn/problem/P7095)。

以下是部分代码（几乎全部）。

```cpp
#define ll long long
const int N=100005;
ll n,z;
struct mon
{
	ll d,a;
	int id;
}a[N],b[N],c;
int cnta,cntb;
bool cmp1(mon x,mon y)
{
	return x.a<y.a;
}
bool cmp2(mon x,mon y)
{
	return x.d<y.d;
}
int main()
{
	n=read(),z=read();
	ll p=z;
	for (int i=1;i<=n;i++) 
	{
		c.d=read(),c.a=read(),c.id=i;
		if (c.d>c.a) b[++cntb]=c;
		else a[++cnta]=c;
		z-=c.d,z+=c.a;
	}
	sort(a+1,a+cnta+1,cmp2);
	sort(b+1,b+cntb+1,cmp1);
	for (int i=1;i<=cntb;i++) 
	{
		if (z>b[i].a) z+=b[i].d-b[i].a;
		else 
		{
			puts("NIE");
			return 0;
		}
	}
	z=p;
	for (int i=1;i<=cnta;i++) 
	{
		if (z>a[i].d) z+=-a[i].d+a[i].a;
		else 
		{
			puts("NIE");
			return 0;
		}
	}
	puts("TAK");
	for (int i=1;i<=cnta;i++) cout << a[i].id << " ";
	for (int i=cntb;i>=1;i--) cout << b[i].id << " ";
	return 0;
}
```


---

## 作者：genshy (赞：2)



### 一句话题意：

给你 $n$ 只怪物，打每个怪物需要扣除一定的血量，打完之后会回复一些血量。

你现在有初始血量 $z$ 点，让你设计一种打怪方案是所有的怪的可以被打完。

### solution：

一个很神奇的贪心。

首先我们把每个怪物分为两类，一类是回血怪，打完之后能回血的那种，另一类就是掉血怪。

我们把这两种怪物分开来考虑。

一个显然的策略就是先打回血怪再打掉血怪，不然先打掉血怪的话，血都掉没了你还怎么打其他的怪。

也就是说我们要先猥琐发育一波，等血量升高了（升满级了）再打掉血怪。

考虑同种怪物之间怎么安排顺序：

##### 1.对于回血怪：

我们要尽可能先打血量少的。假如说你先打回血量多的，遇到下面一组样例你就 GG 了。

当前血量 $10$ ,打 boss 掉血量 $100$  ,回血量 $10000$ 的。

这种情况你发现他虽然回血量比较多，但是你打不动他。

所以还是要先猥琐发育一波，等血量上来了，在打这个怪。

##### 2.对于掉血怪：

一开始我是按血量从高到低排序的，可连交了几发都 $WA$ 了，才发现这样写是不对的。

这是因为你可能会遇到一种情况就是 一个怪物他血量比较高，但回血量少。

这时候我们在打完所有的回血怪之后，第一个打他就会让我们的血量立刻降下来，导致后面的怪物都打不了。

所以我们要先紧着回血多的怪物打，是我们的血量尽可能的保持一个很高的状态。

然后这道题就做完了。

**Code**

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
int n,z,x,y,cnt1,cnt2;
struct node
{
	int id,x,y;
}a[100010],b[100010];
inline int read()
{
	int s = 0,w = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') w = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + ch - '0'; ch = getchar();}
	return s * w;
}
bool comp(node a,node b)
{
	return a.x < b.x;
}
bool cmp(node a,node b)
{
	return a.y > b.y;
}
signed main()
{
	n = read(); z = read();
	for(int i = 1; i <= n; i++)
	{
		x = read(); y = read();
		int tmp = y-x;
		if(tmp >= 0)
		{
			a[++cnt1].id = i;
			a[cnt1].x = x;
			a[cnt1].y = y;
		}
		else 
		{
			b[++cnt2].id = i;
			b[cnt2].x = x;
			b[cnt2].y = y;
		}
	}
	sort(a+1,a+cnt1+1,comp);
	sort(b+1,b+cnt2+1,cmp);
	for(int i = 1; i <= cnt1; i++)
	{
		z -= a[i].x;
		if(z <= 0) { printf("NIE\n"); return 0;}
		z += a[i].y;
	}
	for(int i = 1; i <= cnt2; i++)
	{
		z -= b[i].x;
		if(z <= 0) { printf("NIE\n"); return 0;}
		z += b[i].y;
	}
	printf("TAK\n");
	for(int i = 1; i <= cnt1; i++) printf("%lld ",a[i].id);
	for(int i = 1; i <= cnt2; i++) printf("%lld ",b[i].id);
	return 0;
}

```





---

## 作者：程门立雪 (赞：1)

**题意：**

需要打败 $n$ 只怪物（从 1 到 $n$ 编号）,为了打败第 $i$ 只怪物，消耗 $d[i]$ 点生命值，但恢复 $a[i]$ 点生命值。任何时候你的生命值都不能降到 0（或 0 以下）。
请问是否存在一种打怪顺序，使得你可以打完这 $n$ 只怪物而不死掉。

**题解：**

贪心，先打回血的怪物，再打掉血的怪物。

1. 对于$a[i] > d[i]$, 也就是回血的怪物，可以按 $d[i]$ 从小到大来排序。

2. 对于$a[i] < d[i]$, 也就是掉血的怪物，可以将最后剩余的血量看做初始血量 $x$（ $x$ 是固定的）, 将怪物的 $a$（增血量）与 $b$（掉血量）进行交换，倒着来看，就与上一种情况一样，倒着是按 $a[i]$ 从小到大排序，那么正着是按 $a[i]$ 从大到小排序。

一定要开long long！
```c
#include <cstdio>
#include <iostream>
#include <algorithm>
#define orz cout<<"AK IOI"<<"\n"
#define int long long

using namespace std;
const int maxn = 1e5 + 10; 

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar();}
    return x * f;
}
int n, z, ans[maxn];

struct node{
	int d, a, id, c;
}b[maxn];

bool cmp(node a, node b)
{
	/*if(a.c > 0 && b.c > 0) return a.d < b.d;
	if(a.c < 0 && b.c < 0) return a.a > b.a;
	return a.c > 0;*/
	if(a.c * b.c < 0) return a.c > 0;
	if(a.c < 0) return a.a > b.a;
	return a.d < b.d; 
} 
signed main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n = read(), z = read();
    for(int i = 1; i <= n; i++)
    {
    	b[i].d = read(), b[i].a = read(), b[i].id = i;	
    	b[i].c = b[i].a - b[i].d;
	}
	sort(b + 1, b + n + 1, cmp);
	for(int i = 1; i <= n; i++)
	{
		z -= b[i].d;
		if(z <= 0) { printf("NIE"); return 0;}
		z += b[i].a;
	}
	printf("TAK\n");
	for(int i = 1; i <= n; i++)
	printf("%lld ", b[i].id);
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}
```

---

## 作者：smyslenny (赞：0)

### p2045 Bohater
这道题我们先来定义两个名词：

因为打一个怪既会掉血也会回血.

**回血怪**:掉的血比回的血少，打这个怪可以使我们回血，也就是$d_i<a_i$

**掉血怪**:掉的血比回的血多，打这个怪可以使我们掉血，也就是$d_i>a_i$ 

- 思考：

Q:我们是先打回血的还是先打掉血的呢?

若我们先打掉血的，有可能血就掉没了，~~人没了~~.\
若是先打回血的，我们可以以更多的血去打掉血的怪，活着的几率会大，所以，我们先去打回血的。

- 思考：

Q:单对回血怪和掉血怪，我们怎么打呢？

**回血怪**：

对于这种怪，我们可分为两类。

一类是$d_i \leq z$，也就是说我们一开始的时候就可以击杀，那他应该按什么顺序？

啥顺序都不用，因为无论怎么打，我们的血都会保持在安全范围之内，而且还会回血，不用去考虑还没等回血就over了的情况。

另一类是就是$d_i > z$ 的情况了，那这时候我们应该怎么打呢？

显然这时候不能再乱搞了，因为若没有一定的顺序，虽然会回血，但在回血之前就over了，~~那还回毛线血啊~~，所以我们要给怪安排一个合适的出场顺序。我们将伤害按从小到大排列，先打伤害低的，这样起码在低伤害之后还能回血，提高活的机会。

**掉血怪**：
这时候我们可以按照回血量从大到小排序。

这时候就有同学问了：为什么不能按照掉血量从高到低排呢？我先用多的血打掉血的怪，这不也可以吗？

A：对啊，为啥呢，我一开始也是这么认为的。但我们再回想，若是这个怪他让你掉的血多但回的血少，下一个怪一定是剩下的怪里面掉血最多的，打不过怎么办？~~over了呀~~

所以我们从回血量的角度出发，我们可以保持一个较高的血量，即使面对血量大的怪，我们也有充足的准备，~~我不怕不怕啦~~。
于是，这道题就这么完了。

**十年OI一场空，不开long long 见祖宗**

调了一个小时，就是因为没开long long,记得开long long

```c
/*
work by smyslenny
2021.02.05
P4025 [PA2014]Bohater
*/
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<iostream>
#include<algorithm>
#include<queue>
#include<map>
#define orz cout<<"LKP AK IOI\n"
#define INF 0x3f3f3f3f
#define ll long long
using namespace std;
const int maxn=1e5+5;
ll n,z,js=0,js_=0,j_s=0;
struct  monster_{
	ll num,d,a;
}mon[maxn],return_f[maxn],return_s[maxn],drop_[maxn];
inline int read()
{
	register int x=0;register int y=1;
	register char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=getchar();}
	return y?x:-x;
}
bool cmp(monster_ a,monster_ b)//回血怪
{
	return a.d<b.d;
}
bool cmp_(monster_ a,monster_ b)//掉血怪
{
	return a.a>b.a;
}
int main()
{
	n=read(),z=read();
	js=0,js_=0,j_s=0;
	for(int i=1;i<=n;i++)
	{
		mon[i].num=i;
		mon[i].d=read();
		mon[i].a=read();
		if(mon[i].d-mon[i].a<0)
		{
			if(mon[i].d>z)
			return_s[++js]=mon[i];//第二类
			else
			return_f[++j_s]=mon[i];//第一类
		}
		else
		drop_[++js_]=mon[i];//第三类
	}
	sort(return_f+1,return_f+1+j_s,cmp);
	sort(return_s+1,return_s+1+js,cmp);
	sort(drop_+1,drop_+1+js_,cmp_);
	for(int i=1;i<=j_s;i++)
	{
		if(z-return_f[i].d<=0)//其实没有必要 
		{
			printf("NIE\n");
			return 0;
		}
		z-=return_f[i].d;
		z+=return_f[i].a;
	}
	for(int i=1;i<=js;i++)
	{
		if(z-return_s[i].d<=0)
		{
			printf("NIE\n");
			return 0;
		}
		z-=return_s[i].d;
		z+=return_s[i].a;
	}
	for(int i=1;i<=js_;i++)
	{
		if(z-drop_[i].d<=0)
		{
			printf("NIE\n");
			return 0;
		}
		z-=drop_[i].d;
		z+=drop_[i].a;
	}
	printf("TAK\n");
	for(int i=1;i<=j_s;i++)
	printf("%lld ",return_f[i].num);
	for(int i=1;i<=js;i++)
	printf("%lld ",return_s[i].num);
	for(int i=1;i<=js_;i++)
	printf("%lld ",drop_[i].num);
	return 0;
}
```


---

