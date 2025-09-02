# Lorry

## 题目描述

给定整数 $n,v$。  

有一辆载重量为 $v$ 的货车，准备运送两种物品。物品 A 的重量为 $1$，物体 B 的重量为 $2$，每个物品都有一个价值 $p_i$。求货车可以运送的物品的最大价值。

## 样例 #1

### 输入

```
3 2
1 2
2 7
1 3
```

### 输出

```
7
2
```

# 题解

## 作者：Heartlessly (赞：20)

## Description

有一个体积为 $v$ 的背包，一共有 $n$ 个物品，每个物品的体积为 $t_i$，价值为 $p_i$ 。现要从中取若干物品放入背包，使背包中物品的价值和最大。

$(1 \leq n \leq 10^5,1 \leq v \leq 10^9,1 \leq t_i \leq 2,1 \leq p_i \leq 10^4)$

## Solution

发现物品的体积只有 $2$ 种，分别是 $1$ 和 $2$ 。我们可以根据体积把它们分成两类。

假如所有物品都是同一类的，一个很显然的贪心是选价值较大的更优，所以对于每一类我们将物品按价值从大到小排序。

考虑枚举体积为 $1$ 的物品放多少个，剩下的空间全部放体积为 $2$ 的物品，判断是否能够更新答案即可。时间复杂度为排序的复杂度 $O(n \log n)$ 。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}

template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

const int MAXN = 1e5;
int n, v, cnt1, cnt2, pos1, pos2, ans, sum, pre[MAXN + 5];
struct Node {
    int p, id;
    
    inline friend bool operator<(Node x, Node y) {
        return x.p > y.p;//按价值从大到小排序 
    }
} t1[MAXN + 5], t2[MAXN + 5];

int main() {
    read(n), read(v);
    for (int t, p, i = 1; i <= n; ++i) {
        read(t), read(p);
        if (t == 1) {
            t1[++cnt1].p = p;
            t1[cnt1].id = i;
        } else {
            t2[++cnt2].p = p;
            t2[cnt2].id = i;
        }//根据体积分成两类 
    }
    sort(t1 + 1, t1 + cnt1 + 1), sort(t2 + 1, t2 + cnt2 + 1);
    for (int i = 1; i <= cnt2; ++i) pre[i] = pre[i - 1] + t2[i].p;
    //预处理出体积为 2 的物品价值的前缀和 
    for (int i = 0; i <= min(v, cnt1); ++i) {//选了 i 个体积为 1 的物品 
        sum += t1[i].p;//体积为 1 的物品价值和
        //体积为 2 的物品选了 min(cnt2, (v - i) / 2) 个 
        if (sum + pre[min(cnt2, (v - i) / 2)] > ans) {//如果更优 
            ans = sum + pre[min(cnt2, (v - i) / 2)];
            pos1 = i, pos2 = min(cnt2, (v - i) / 2);//记录该方案的位置 
        }
    }
    write(ans);
    putchar('\n');
    for (int i = 1; i <= pos1; ++i) {
        write(t1[i].id);
        putchar(' ');
    }
    for (int i = 1; i <= pos2; ++i) {
        write(t2[i].id);
        putchar(' ');
    }
    putchar('\n');
    return 0;
}
```


---

## 作者：皎月半洒花 (赞：16)

说实话我感觉写完这道题之后，打算来题解区看看有没有什么更好的Idea，然后看完题解之后我自己都不会做了……

其实是一个非常简单的贪心思路，就是如果两件重量为1的商品合成一件的话，比重量为2的要优我们就选合起来的。

$Somebody$谈过一个小Idea，就是看上去我们期望每次取偶数个。那么我们一开始如果$M$是奇数，就从重量为1的那一堆选一个最大的……（虽然我不知道这个到底有没有用但是听起来挺科学）

有些小细节需要注意。其中拿出来一个说一下：边界问题其实不需要考虑得太仔细，只要我们一开始memset整个数组为-INF，那么当一种重量的用完了，另一种重量的没用完时，取max之后不会出现越界的情况

```cpp
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

#define MAXN 200020
#define pb push_back
#define rep(i, a, x) for(i = a ; i <= x ; ++ i)

using namespace std ;
struct Data{
    int num ,val ;
} base1[MAXN], base2[MAXN] ; int N, M, p, v, v1, v2, c ;
long long Ans ; int tot1, tot2, t1, t2, i ; vector <int> ans ;

inline bool Comp(Data a, Data b){ return a.val > b.val ; }
int main(){
    cin >> N >> M ; 
    memset(base1, -63, sizeof(base1)) ; 
    memset(base2, -63, sizeof(base2)) ; 
    for (i = 1 ; i <= N ; ++ i){
        scanf("%d%d", &p, &v) ;
        if (p > 1) base2[++ tot2].val = v, base2[tot2].num = i ;
        else/*qwq*/base1[++ tot1].val = v, base1[tot1].num = i ;
    }
    sort(base1 + 1, base1 + tot1 + 1, Comp), 
    sort(base2 + 1, base2 + tot2 + 1, Comp) ;
    // for (i = 1 ; i <= N ; ++ i) cout << base1[i].num << " " << base1[i].val << " qwwq " ;
    // for (i = 1 ; i <= N ; ++ i) cout << base2[i].num << " " << base2[i].val << " qwwq " ;
    if (M & 1) ans.pb(base1[1].num), Ans += base1[1].val, ++ t1, M -- ;
    while (M > 1){//此处>1是选v=2时防止越界
        v2 = base2[t2 + 1].val ;
        if (t1 >= tot1 && t2 >= tot2) break ;
        v1 = base1[t1 + 1].val + base1[t1 + 2].val ; 
        if (t1 + 2 > tot1) v1 = base1[t1 + 1].val, c = 1 ; else c = 2 ; 
        if (v1 >= v2){
            Ans += v1 ; M -= c ;
            rep(i, 1, c) ans.pb(base1[++ t1].num) ; 
        }
        else Ans += v2, M -= 2, ans.pb(base2[++ t2].num) ; 
    }//因为while的条件是M>1,所以需要判断一下是不是还可以选。
    if (M && t1 < tot1) Ans += base1[++ t1].val, ans.pb(base1[t1].num) ; if (Ans < 0) return puts("0\n"), 0 ; 
    cout << Ans << endl ; for (vector<int> :: iterator k = ans.begin() ; k != ans.end() ; ++ k) cout << *k << " " ;
}
```


---

## 作者：ahawzlc (赞：10)

建议管理大大改一下题面，输出的应该是最优方案所包含的物品的序号。

----

这道题大可看成贪心来做。

根据题目所说，物品重量无非两种，要么重量是 1 ，要么重量是 2 ，那么按物品重量把它们分成两类，用一个 $pair<int,int>$ 来存物品的价值和序号（因为输出要用），按价值对两个物品序列降序排序。

然后枚举用 $i$ 个重量为 1 的物品（理论上 2 也可以），那么就用了 $\frac{v-i}{2}$ 个重量为 2 的物品，贪心计算当前的价值总和（按照排序尽量取价值大的），取 $\max$ 同时记录方案。

很显然这样直接求会 TLE ，那么我们要做的就是祭出优化！

优化： 同样显然，预处理出质量为 2 物体价值的前缀和，枚举循环内部时直接用就完了。

代码：
``` cpp
#include<bits/stdc++.h>
#define pi pair<int,int>
#define F first
#define S second
#define re register
using namespace std;
pi a[100005],b[100005];
int t1,t2,num[100005];
int ans,sum,maxi,maxj;
bool cmp(pi a,pi b) {//sort比较函数（降序）
	return a.F>b.F;
}
inline int read() {//快读
	int sum=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		sum=(sum<<3)+(sum<<1)+ch-'0';
		ch=getchar();
	}
	return sum*w;
}
int main() {
	int n,v;
	n=read();
	v=read();
	for(re int i=1;i<=n;i++) {
		int opt=read(),x=read();
		if(--opt) b[++t2]=make_pair(x,i);
		else a[++t1]=make_pair(x,i);
	}
	sort(a+1,a+t1+1,cmp);
	sort(b+1,b+t2+1,cmp);//STL大法好
	for(int i=1;i<=t2;i++) {
		num[i]=num[i-1]+b[i].F;//预处理前缀和
	}
	for(re int i=0;i<=t1&&i<=v;i++) {//i个质量1物品
		int j=min((v-i)>>1,t2);//j个质量2物品
		sum+=a[i].F;
		if(sum+num[j]>ans) {
			ans=sum+num[j];
			maxi=i;
			maxj=j;
		}
	}
	cout<<ans<<endl;
	for(re int i=1;i<=maxi;i++)
		cout<<a[i].S<<' ';
	for(re int i=1;i<=maxj;i++)
		cout<<b[i].S<<' ';
	return 0;
}
```

---

## 作者：CrTsIr400 (赞：7)

因为这道题目 $n\le 10^5,m\le 10^9$，所以 $O(nm)$ 的 `背包DP` 会**严重超时，不予采用。**

发现每件货物的 $t_i$ **只可能有两种** （$1$ 和 $2$），因此采用**贪心算法。**

考虑重量为 $1$ 的物品取 $i$ 件，则重量为 $2$ 的物品必须取 $\min(\frac{(m-i)}{2},bl)$ 件。其中 $bl$ 是重量为 $2$ 的物品个数。

然后算出来的结果就是 $\sum^{i} _{j=1} a[j] + \sum^{n} _{j=i+1} b[j]$  。以这个结果更新最大值。

注意：因为要求的是最大价值，**所以 $a $ 和 $ b$ 数组一定要按照降序排序！** 因为明显对于两个同样重量的东西，**价值更大的更优**。

其中的两个 $\sum$ 可以通过前缀和优化成 $O(1)$ 。

然后输出方案在前缀和加的时候处理一下即可。具体看代码。

总时间复杂度（加上排序） $O(n \log n)$。

```cpp
struct node
{
	int x,p;
}a[2][100001];
int n,m,maxx,t1,t2,l[2],p1[100001],p2[100001];
LL s1[100001],s2[100001],ans,ans1,ans2;
int c1[10001],c2[10001];
bool cmp(node t1,node t2)
{
	return t1.x>t2.x;
}
int main()
{
	in(n,m);
	Fu(i,1,n)
	{
		in(t1,t2);
		a[t1-1][++l[t1-1]].x=t2;
		a[t1-1][l[t1-1]].p=i;//输入时给它分拨一下
	}
	sort(a[0]+1,a[0]+l[0]+1,cmp);
	sort(a[1]+1,a[1]+l[1]+1,cmp);//排序
	Fu(i,1,l[0])s1[i]=s1[i-1]+a[0][i].x,p1[i]=a[0][i].p;//前缀和，顺便处理位置
	Fu(i,1,l[1])s2[i]=s2[i-1]+a[1][i].x,p2[i]=a[1][i].p;//同上
	Fu(i,0,min(l[0],m))
	{
		int j=min(l[1],(m-i)/2);//枚举重量为2的个数
		if(i+j*2>m)continue;//注意判断，有坑
		if(s1[i]+s2[j]>ans)ans=s1[i]+s2[j],ans1=i,ans2=j;
        //更新答案
	}
	cout<<ans<<endl;
	Fu(i,1,ans1)cout<<p1[i]<<" ";Fu(i,1,ans2)cout<<p2[i]<<" ";//输出路径
	return 0;
}
//BY 线段树蒟蒻


```

---

下面是加强版↓，重头戏，$O(n)$ 解法

问：如果 $n\le 10^7,p_i \le 10^9$ 怎么办呢？

排序可以通过**基数排序** 解决，不需要 $O(n \log n)$。

时间复杂度从 $O(n \log n)$ 变成 $O(n)$。

基数排序代码：

```cpp
void radixsort()
{
	vector<node>t[256];int tp=0;
	Fu(i,1,4)
	{
		tp=0;
		Fu(j,1,m)t[(a[j].x>>(8*(i-1)))&255].push_back(a[j]);
		Fd(j,255,0)
		{
			Fu(k,1,t[j].size())
			a[++tp]=t[j][k-1];
			t[j].clear();
		}
	}
}
```


这个 $a$ 是待排序的结构体数组。

按照 `a[j].x` 关键字排序，没有违背基数排序**把一个数拆成多个关键字排序**的思想。

换句话说，只要用这个 `a[j].x` 的**关键字带着这整个`a[j]`排一下序即可。**

时间复杂度 $O(n)$ ，完全碾压楼下的解法。

~~不过还是 $O(n\log n)$ 的快排好写亿点。~~


---

## 作者：灵茶山艾府 (赞：4)

看了其他题解，用到了前缀和、优先队列等做法，这里说下我的做法，只需要排序+遍历。

由于物品体积范围很小，我们可以贪心来做：按照单位体积的价值从大到小排序，然后依次取物品，若全部取完或者恰好装满，则可以愉快地输出答案。

现在来处理未取完且剩余一个空间的情况。此时遍历到的物品 $i$ 的体积必定为 $2$。

分三种情况讨论：
1. 当前就是最优取法；
2. 从 $i$ 向后遍历，寻找一个体积为 $1$ 的物品放入；
3. 从 $i$ 向前遍历，寻找一个体积为 $1$ 的物品，将其移除，然后取物品 $i$ 放入。

从这三种情况中输出价值最大的取法。实现细节见下。

AC 代码（Golang）:

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
	"sort"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var n, cap, i, s int
	Fscan(in, &n, &cap)
	type pair struct{ v, w, i int }
	a := make([]pair, n)
	for i := range a {
		Fscan(in, &a[i].w, &a[i].v)
		a[i].i = i
	}
	printAns := func() {
		Fprintln(out, s)
		for _, p := range a[:i] {
			Fprint(out, p.i+1, " ")
		}
	}

	// 按照单位体积的价值排序，然后依次取物品
	sort.Slice(a, func(i, j int) bool { a, b := a[i], a[j]; return a.v*b.w > b.v*a.w })
	for ; i < n && a[i].w <= cap; i++ {
		cap -= a[i].w
		s += a[i].v
	}
	if i < n && cap > 0 { // 未取完且有剩余空间（此时剩余空间必定为一）
		j := i - 1
		for ; j >= 0 && a[j].w == 2; j-- {} // 向前找一个体积为 1 的物品 j
		for k := i + 1; k < n; k++ {
			if a[k].w == 1 { // 向后找一个体积为 1 的物品 k
				if j >= 0 && a[i].v-a[j].v > a[k].v { // 情况 3
					break
				}
				// 情况 2
				s += a[k].v
				a[i].i = a[k].i
				i++
				printAns()
				return
			}
		}
		if j >= 0 && a[i].v > a[j].v { // 情况 3
			s += a[i].v - a[j].v
			a[j].i = a[i].i
		}
	}
	printAns()
}
```



---

## 作者：Loner_Knowledge (赞：4)

这是一道贪心题
---

首先此题的数据范围不允许背包，那么就用贪心吧。

我的贪心策略是将数据以类型分开来按照**承载能力降序排列**。首先将类型2的货物尽可能地放入车内，再将类型1的货物尽可能地放入车内，之后对放入车内的类型2货物以**承载能力从小到大的顺序**一个一个地拿出来，尝试在剩下的类型1货物以**承载能力从大到小的顺序**寻找是否有超过该类型2货物承载能力的组合，如果有那么就拿出类型2货物并放入类型1货物的组合。

由于数据是降序排列的，那么对于一个无法被拿出的类型2货物，在它之前的货物承载能力均要比它大，那么在它之前的货物就和它一样无法被拿出。

注意**数据范围**，答案要用$long\ long$，$long\ long$在`CodeForces`要用`"%I64d"`输出。（当然如果你用`cout`另说）
 
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct Data {
	int id;
	int value;
}D1[100002],D2[100002],*t;	//如数组名后面的数字所示，D1代表类型1货物的队列，D2代表类型2货物的队列，以下的变量均用数字表示是与何种类型相关
							//t是指向当前输入数据的指针
int head1,head2;			//队列长度
bool Compare(const Data &a,const Data &b) {		//降序排列
	return a.value>b.value;
}
int main() {
	int n,v,mark1=0,mark2=0;	//mark标记的是货物能被放入的数量
	long long ans=0,temp;		//ans就是最大贡献，temp记录取出一个货物时的贡献
	scanf("%d%d",&n,&v);
	for(int i=1,j;i<=n;++i) {
		scanf("%d",&j);
		if(j==1)
			t=&D1[head1++];		//根据判断类型更新结构体指针
		else
			t=&D2[head2++];
		t->id=i;				//通过指针输入数据
		scanf("%d",&t->value);
	}
	for(sort(D2,D2+head2,Compare);v>1&&mark2<head2;v-=2)	//初始化是排序
		ans+=D2[mark2++].value;		//尽可能的放
	for(sort(D1,D1+head1,Compare);v>0&&mark1<head1;v-=1)	
		ans+=D1[mark1++].value;
	temp=ans;
	for(int i=mark2-1,j;i>=0;--i) {		//在类型2中尝试取出
		temp-=D2[i].value;			//录取出一个货物时的贡献
		v+=2;
		for(j=mark1;j<head1&&v>0;++j) {		//在类型1中寻找
			temp+=D1[j].value;
			v-=1;
		}
		if(ans<temp) {		//检查是否更新最大贡献
			ans=temp;
			mark1=j;
			mark2-=1;
		}
		else
			break;
	}
	printf("%I64d\n",ans);
	for(int i=0;i<mark2;++i)	//输出数据标号
		printf("%d ",D2[i].id);
	for(int i=0;i<mark1;++i)
		printf("%d ",D1[i].id);
	return 0;
}
```

---


---

## 作者：Minecraft万岁 (赞：3)

我们教练把题目魔改之后给我们做   
看到 $v$ 看到 $c$ 看到物品价值和和重量 我果断$01$背包   
~~结果全部 $TLE$~~ 教练还喜欢多组数据 说是防止我们~~骗分~~打表    


------------
好了 来看一下题目 发现 物品只有两种重量 也就是说   
### 重量只有两种 我们可以枚举每种重量分别选多少   
那么怎么在确定了两种重量分别选多少的情况下保证价值最大呢 $?$ ~~我也不知道~~  
我们可以先处理一下 分成两个结构体数组 一个是重量为 $1$ 的编号和价值 一个是重量为 $2$ 的编号和价值 对两个数组的价值分别按照价值降序排序 这样就可以保证在两种物品重量确定的情况下 取得的价值最大  
#### 注意 $:$ 必须用前缀和数组 $pre[i]$ 累计从 $1$ 到 $i$ 的价值和 这样可以 $O(1)$ 的复杂度算出两种物品重量分别对应的价值 不然会~~怎么样我也没试过~~$TLE$  
#### $Talk$ $is$ $easy.$ $Show$ $me$ $your$ $code.$ 
那就上代码吧  


------------
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
struct node//结构体保存价值和编号 
{
	int w;
	int id;
}w1[100005],w2[100005];//两个数组 分别保存重量为1的信息 和 重量为2的信息 
int pre1[100005],pre2[100005];//两个前缀和数组 
int hp1,hp2;//保存一下两个数组当前有多少个物品 
int ans;//答案 也就是最大价值 
int n,v;//物品个数 和 最大重量 
int rw,rc;//读入的重量 和 价值 
int tmp;//开个变量暂存一下每一次枚举i算出的答案 
int p1,p2;//当前最大价值对应的两个数组分别取到哪里 
inline void read(int &x)//快读 
{
	int f;char c;
	for (f=1,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for (x=0;c<='9'&&c>='0';c=getchar()) x=x*10+(c&15);x*=f;
}
inline int mn(int _x,int _y)//缺省源*1 
{
	return _x<_y?_x:_y;
}
inline int mx(int _x,int _y)//缺省源*2 
{
	return _x>_y?_x:_y;
}
inline int ab(int _x)//缺省源*3 
{
	if(_x<0) return -_x;
	else return _x;
}
inline bool cmp(node x,node y)//结构体排序 按价值从大到小排 
{
	return x.w>y.w;
}
int main()
{
	read(n);read(v);//读入*1 
	for(int i=1;i<=n;i++)
	{
		read(rw);read(rc);//读入*2 
		if(rw==1)//重量为1的 
		{
			hp1++;
			w1[hp1].w=rc;
			w1[hp1].id=i;//编号按照读入的顺序从1~i 
		}
		else//重量为2的 
		{
			hp2++;
			w2[hp2].w=rc;
			w2[hp2].id=i;
		}
	}
	sort(w1+1,w1+hp1+1,cmp);//给两个结构体排序 
	sort(w2+1,w2+hp2+1,cmp);
	for(int i=1;i<=hp1;i++)//给两个结构体做前缀和 
		pre1[i]=pre1[i-1]+w1[i].w;
	for(int i=1;i<=hp2;i++)
		pre2[i]=pre2[i-1]+w2[i].w;
	for(int i=0;i<=v;i++)//枚举两种物品的可能价值 枚举一个就可以算出另一个 
	{
		tmp=pre1[mn(i,hp1)]+pre2[mn((v-i)>>1,hp2)];//取个min 有可能可以取的个数大于这个物品个数 
		if(tmp>ans)//发现更好的 
		{
			ans=tmp;//保存更好的答案 
			p1=mn(i,hp1);//保存两个取到的位置 照样取min 
			p2=mn((v-i)>>1,hp2);
		}
	}
	printf("%d\n",ans);//按照格式输出答案 
	for(int i=1;i<=p1;i++) printf("%d\n",w1[i].id);
	for(int i=1;i<=p2;i++) printf("%d\n",w2[i].id);
	return 0;
}


```


---

## 作者：xuezhe (赞：3)

首先，纠正一下这道题的翻译，输出的第二行应为在最优情况下所有选择的物品的**编号**。

以下是正文。

---

看到这道题，首先想到的是01背包。

然而一看数据范围， $1 \leq v \leq 10^9$ ，时间空间双爆。

事实上， 由于背包有可能有许多空余的空间，所以 $v$ 可以转换为 $\min \lbrace v , \sum \limits_{i=1}^n t_i \rbrace$ 。但是依然超时。

经典的01背包做法~~应该~~已经被榨干了，这时我们不妨从另一个角度考虑一下。

这里的重量只有 1 和 2 两种可能，看上去无从下手，我们不妨从更简单的角度来看看。

假如重量只有一种可能，则执行一个贪心策略：按价值从大到小选，即可使总价值最大。

那么，面对两种重量时，我们可以将其转化为下面的问题：
> 假如你要买两个背包，它们的总容量为 v ，一个用来装 a 个体积为 1 的物品，一个用来 b 个装体积为 2 的物品。问：装入两个背包物品的价值最大为多少？

（问题描述并不算很严谨，在这里仅作示例使用。）

对于两个背包，由于同一包内所装物品体积相等， 我们可以枚举两个背包的容积，然后对于每个背包，执行上文所述贪心策略，即可得到最终解。

事实上，对于这道题，虽然题目中并没有说什么两个背包，但我们可以将其拆解成两个部分，一部分装物品 A ，一部分装物品 B 。问题就得到了解决。

然而，这里如果使用拆解重量完全按照 $v$ 来拆分，依旧会超时。所以我们可以同时按照物品 A 的个数 $a$ 和 $v$ 来拆分。即使物品 A 全部装入，最多也就占 $a$ 个单位质量，若多给也无济于事。故分给物品 A 的部分所能容纳的质量仅需小于 $\min \lbrace v,a \rbrace$ 即可。

C++代码：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

inline int mmin(int a,int b){
    return a<b?a:b;
}

struct Thing{
    int p,id;
}a[100001],b[100001];
int an=0,s1[100001]={},bn=0,s2[100001]={};

bool cmp(Thing a,Thing b){
    return a.p>b.p;
}

int n,v,t,p,maxp=0,ca=0,cb=0;

int main(){
    int i;
    
    scanf("%d%d",&n,&v);
    for(i=1;i<=n;++i){
        scanf("%d%d",&t,&p);
        if(t==1){
            a[++an].p=p;
            a[an].id=i;
        }else{
            b[++bn].p=p;
            b[bn].id=i;
        }
    }
    sort(a+1,a+1+an,cmp);
    sort(b+1,b+1+bn,cmp);
    
    /*只有物品B*/
    if(an==0){
        for(i=1;i<=n && 2*i<=v;++i){
            maxp+=b[i].p;
        }
        printf("%d\n",maxp);
        
        for(i=1;i<=n && 2*i<=v;++i){
            printf("%d ",b[i].id);
        }
        return 0;
    }
    
    /*只有物品A*/
    if(bn==0){
        for(i=1;i<=n && i<=v;++i){
            maxp+=a[i].p;
        }
        printf("%d\n",maxp);
        for(i=1;i<=n && i<=v;++i){
            printf("%d ",a[i].id);
        }
        return 0;
    }
    
    /*既有物品A,又有物品B*/
    for(i=1;i<=an;++i){
        s1[i]=s1[i-1]+a[i].p;
    }
    for(i=1;i<=bn;++i){
        s2[i]=s2[i-1]+b[i].p;
    }
    for(i=0;i<=an && i<=v;++i){
        if(s1[i]+s2[mmin((v-i)/2,bn)]>maxp){
            maxp=s1[i]+s2[mmin((v-i)/2,bn)];
            ca=i; cb=mmin((v-i)/2,bn);
        }
    }
    printf("%d\n",maxp);
    for(i=1;i<=ca;++i){
        printf("%d ",a[i].id);
    }
    for(i=1;i<=cb;++i){
        printf("%d ",b[i].id);
    }
    return 0;
}
```
```

---

## 作者：fls233666 (赞：2)

**2020年2月14日更新：修正题解排版格式问题**

-------------

首先纠正翻译中的一个错误：

**第二行要输出的是能构成最大价值的物品的序号。**

看到这题，我的第一个想到的就是**动态规划里面的 01 背包**。然而这道题是**不能用 01 背包**直接出解的。为什么呢？请看数据范围：

$1 \le v \le 10^9,1 \le n \le 10^5$

即使最优的01背包做法，也要 $O(v)$ 的空间复杂度。显然， $O(10^9)$ 的空间复杂度面对 $64MB$ 的空间限制太大了。


------------


那么，从什么地方下手呢？我们注意到，这题给出的物品重量 $t_i$ 有一个特点：

$1 \le t_i \le 2$

由于 $t_i$ 只有 $1$ 和 $2$ 两种取值，那么我们按题意**把物品分成两类**：A 物品（重量为1）和 B 物品（重量为2）。

因为题目要求最大的价值，所以我们**把所有的 A 物品放进一个大根堆里面，把所有的B物品放进另一个大根堆里面**。**然后取出堆顶进行比较**。这里就采用了**贪心**的思想。

那么，比较的情况有哪些呢？我们设把装着 A 物品的大根堆堆顶表示为 $A$，把装着 B 物品的大根堆堆顶表示为 $B$，然后分类讨论：

$A \ge B$ 时，**因为 $A$ 的重量比 $B$ 小，所以肯定选择 $A$ 是更优的**。

$A < B$ 时，**此时可以拿一个 $t$ 存储 $A$ 的价值，然后把堆顶 $A$ 删除，得到新的一个堆顶 $A$ （如果拿出堆顶后堆空了，直接选择 $B$ ）** 。然后比较 $A+t$ 与 $B$ 的大小，如果 $A+t<B$，选择 $B$ （**此时要记得把 $t$ 放回去！**），如果 $A+t>B$，选择 $A+t$。 $A+t=B$ 时，可以任意取之中的一个 $A+t$ 与 $B$。

**如果在取的过程中，有一个堆空了，就一直取另一个堆的物品，直到无法再取。**

最后，题目还要求输出选择的物品编号。**我们可以开一个 pair，first 值是物品的价值，second 是物品的编号。**然后在选择物品时，用一个 vector 动态数组**把每次选择的物品的 second 值记录下来**，最后输出这个 vector 动态数组即可。

根据上述思路，我们可以得到如下代码：

```cpp
#include<iostream>
#include<queue>
#include<vector>
#define pir pair<int,int>
//pair<价值，编号>
using namespace std;
priority_queue<pir>q[3];
//q[1]是存放A物品的大根堆，q[2]是存放B物品的大根堆
vector<int>ch;
//记录选择的物品的编号
int main()
{
    int n,v,ans=0;  //ans记录最大总价值
    cin>>n>>v;
    pir t;
    for(int t,p,i=0;i<n;i++){
        cin>>t>>p;
        q[t].push(make_pair(p,i+1));  
  		//把编号和价值进行封装，并根据重量塞到对应的堆中
    }
  //读入数据&数据预处理
  
    while(!q[1].empty()&&!q[2].empty()&&v){  //在两个堆都不空并且有剩余容量的情况下循环
        if(v==1){  //如果容量为1，直接取当前A物品的堆的堆顶（价值最大）
            ans+=q[1].top().first;
            ch.push_back(q[1].top().second);
            q[1].pop();
            v--;
        }else{
            if(q[1].top().first>=q[2].top().first){  //比较两个堆的堆顶
            //选择A物品
                ans+=q[1].top().first;
                ch.push_back(q[1].top().second);
                q[1].pop();
                v--;
            }else{
                t=q[1].top();  //拿出一个A物品
                q[1].pop();
                if(!q[1].empty()){   //判断A物品的堆是否为空
                    if(q[1].top().first+t.first<=q[2].top().first){  //再次比较
                    //选择B物品
                        ans+=q[2].top().first;
                        ch.push_back(q[2].top().second);
                        q[2].pop();
                        v-=2;
                        //把刚才拿出来的A物品放回去
                        q[1].push(t);
                    }else{
                    	//选择两个A物品
                        ans+=q[1].top().first+t.first;
                        ch.push_back(t.second);
                        ch.push_back(q[1].top().second);
                        q[1].pop();
                        v-=2;
                    }
                }else{  //堆空选择B物品
                    ans+=q[2].top().first;
                    ch.push_back(q[2].top().second);
                    q[2].pop();
                    v-=2;
                    q[1].push(t);
                }
            }
        }
    }
    
    //如果B物品的堆空了，一直取A物品的堆
    while(!q[1].empty()&&v>=1){
        ans+=q[1].top().first;
        ch.push_back(q[1].top().second);
        q[1].pop();
        v--;
    }
    
    //如果A物品的堆空了，一直取B物品的堆
    while(!q[2].empty()&&v>=2){
        ans+=q[2].top().first;
        ch.push_back(q[2].top().second);
        q[2].pop();
        v-=2;
    }
    
    //至此，物品选择完成，下面输出
    
    cout<<ans<<endl;   //输出ans
    for(int i=0;i<ch.size();i++)
        cout<<ch[i]<<" ";   //输出选择的物品编号
    return 0;
}
```

我往CF上面一交，只见一行大字：

$\color{red}Wrong$ $\color{red}answer$ $\color{red}on$ $\color{red}test$ $\color{red}5$


------------


问题出在哪里呢？

我们发现，上述思路中有一块的策略可能不是最优的：

**我们取 $A$ 物品时，可能会把两个 $A$ 物品一起取。这就导致 $A$ 物品的选择不一定是最优的。**

那么，我们来解决这个问题：

1. 更改物品选择后记录的方式：**把 vector 拆成两个小根堆，一个存 $A$ 物品，一个存 $B$ 物品**；
2. 在做完上述决策后，**把存 $A$ 物品的答案的小根堆取出两次堆顶（其中一次存到 $t$ 里面），然后与存 $B$ 物品的大根堆堆顶比较**；
3. **如果取 $B$ 物品的策略更优，则删除 $A$ 物品的这两个答案，改为 $B$ 物品**；
4. 重复更改直到 $A$ 物品答案的小根堆空了或者 $B$ 物品的大根堆空了
5. 如果发现不能更改就可以提前结束第3步进行输出；
6. 因为 CF 题目全部都是 SPJ，所以我们不用考虑序号输出的顺序，只要序号输出的是对的即可。

总的来说解决方案就是**把所有选择的 $A$ 物品中最小的两个与未选的 $B$ 物品中最大的进行比较，再次更新选择（因为两个 $A$ 物品重量 $=$ 一个 $B$ 物品的重量）**。

我再一提交，终于看到了：

$\color{green}Accepted$

代码如下：

```cpp
#include<iostream>
#include<queue>
#define pir pair<int,int>
using namespace std;
priority_queue<pir>q[3];
priority_queue< pir , vector<pir> ,greater<pir> >anses[3];  //建存答案的小根堆：anses[1]存A物品，anses[2]存B物品
int main()
{
    int n,v,ans=0;
    cin>>n>>v;
    pir t;
    for(int t,p,i=0;i<n;i++){
        cin>>t>>p;
        q[t].push(make_pair(p,i+1));
    }
    while(!q[1].empty()&&!q[2].empty()&&v){
        if(v==1){
            ans+=q[1].top().first;
            anses[1].push(q[1].top());
            q[1].pop();
            v--;
        }else{ 
            if(q[1].top().first>=q[2].top().first){
                ans+=q[1].top().first;
                anses[1].push(q[1].top());
                q[1].pop();
                v--;
            }else{
                t=q[1].top();
                q[1].pop();
                if(!q[1].empty()){
                    if(q[1].top().first+t.first<q[2].top().first){
                        ans+=q[2].top().first;
                        anses[2].push(q[2].top());
                        q[2].pop();
                        v-=2;
                        q[1].push(t);
                    }else{
                        ans+=q[1].top().first+t.first;
                        anses[1].push(t);
                    	anses[1].push(q[1].top());
                        q[1].pop();
                        v-=2;
                    }
                }
                else{
                    ans+=q[2].top().first;
                    anses[2].push(q[2].top());
                    q[2].pop();
                    v-=2;
                    q[1].push(t);
                }
            }
        }
    }
    while(!q[1].empty()&&v>=1){
        ans+=q[1].top().first;
        anses[1].push(q[1].top());
        q[1].pop();
        v--;
    }
    while(!q[2].empty()&&v>=2){
        ans+=q[2].top().first;
        anses[2].push(q[2].top());
        q[2].pop();
        v-=2;
    }
  
  //以上部分大致相同，不再多解释
  
    while(q[2].size()>=1&&anses[1].size()>=2){
    	t=anses[1].top();
    	anses[1].pop();  //取出堆顶
    	if(anses[1].top().first+t.first<q[2].top().first){
    		//比较&&更新答案
            ans=ans-(anses[1].top().first+t.first)+q[2].top().first;//更新ans值
            anses[1].pop();
    		anses[2].push(q[2].top());
    		q[2].pop();  //记录答案
        }else{
            anses[1].push(t);  //不能更新要把t放回去！
            break;
        }
    }
                                                           
     //输出答案
                                                           
    cout<<ans<<endl;
    while(!anses[1].empty()){
    	cout<<anses[1].top().second<<" ";
    	anses[1].pop();
    }
    while(!anses[2].empty()){
    	cout<<anses[2].top().second<<" ";
    	anses[2].pop();
    }
    return 0;
}
```


---

## 作者：2simon2008 (赞：0)


## 题意简化
给你 $n$ 个数对，从中选出任意个数对，在数对第一个数之和不大于 $m$ 的情况下，数对第二个数之和（即价值的和）要尽可能的大。

## 过程
中途复制黏贴时忘记把 $a$ 和 $b$ 数组改过来了，调了半天。

## 思路
这个数对特点是第一个数只有 $1$ 或者 $2$，枚举 $1$ 的个数 $i$，求出 $2$ 的个数 $j$，此时分成两类，存入两个数组中（方便排序，见下），每类中第二个数大的数对要尽量靠前放。

## 优化
但是，这样求第二个数之和（即价值和）的速度太慢了，很容易可以想到用前缀和数组预处理。由于我们肯定是每类中，按照价值从大到小使用，所以顺序是固定的，先排序然后用前缀和数组求前 $i$ 个数的价值和。我用 $s$ 数组表示前缀和。

前缀和数组可以更快的求出两类的最终总和，是一个小优化。

## 求值
这里主要要求两个值：

从 $i$ 求 $j$ 的个数，其实很好得出：要么是剩余空间尽量放，空间有多数量不够就空着。所以是 $j=min(cnt2,(m-i) \div 2)$; 这里 $cnt2$ 是第一个数为 $2$ 的总个数, $m$ 是总空间，

求 $ans$，求是很简单，就是两者之和 $ans=s1_i+s2_j$;



## 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s1[100005],s2[100005],cnt1,cnt2;
//s1、s2是前缀和数组
int ans,ans1,ans2,x,y;
struct node{
	int num,p;
}a[100005],b[100005];//num是编号，p是价值即数对中第二个数
bool cmp(node x,node y){
	return x.p>y.p;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x,&y);
		if(x==1) a[++cnt1].num=i,a[cnt1].p=y;
		else b[++cnt2].num=i,b[cnt2].p=y;
	}//输入并分类存储
	sort(a+1,a+cnt1+1,cmp);
	sort(b+1,b+cnt2+1,cmp);//排序，按照价值的大小
	for(int i=1;i<=cnt1;i++) s1[i]=s1[i-1]+a[i].p;
	for(int i=1;i<=cnt2;i++) s2[i]=s2[i-1]+b[i].p;//求前缀和
	for(int i=0;i<=min(cnt1,m);i++){
		int j=min(cnt2,(m-i)/2);
		if(i+2*j>m) continue;//避免越界
		if(s1[i]+s2[j]>ans)
			ans1=i,ans2=j,ans=s1[i]+s2[j];
         //ans1记录第一个数为1的个数，ans2记录为2的个数，ans为答案
	}
	cout<<ans<<endl;
	for(int i=1;i<=ans1;i++) printf("%d ",a[i].num);
	for(int i=1;i<=ans2;i++) printf("%d ",b[i].num);
	printf("\n");//输出
	return 0;
} 
```

------------

**完结撒花**

---

