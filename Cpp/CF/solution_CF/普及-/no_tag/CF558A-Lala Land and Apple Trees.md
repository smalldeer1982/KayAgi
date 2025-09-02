# Lala Land and Apple Trees

## 题目描述

Amr lives in Lala Land. Lala Land is a very beautiful country that is located on a coordinate line. Lala Land is famous with its apple trees growing everywhere.

Lala Land has exactly $ n $ apple trees. Tree number $ i $ is located in a position $ x_{i} $ and has $ a_{i} $ apples growing on it. Amr wants to collect apples from the apple trees. Amr currently stands in $ x=0 $ position. At the beginning, he can choose whether to go right or left. He'll continue in his direction until he meets an apple tree he didn't visit before. He'll take all of its apples and then reverse his direction, continue walking in this direction until he meets another apple tree he didn't visit before and so on. In the other words, Amr reverses his direction when visiting each new apple tree. Amr will stop collecting apples when there are no more trees he didn't visit in the direction he is facing.

What is the maximum number of apples he can collect?

## 说明/提示

In the first sample test it doesn't matter if Amr chose at first to go left or right. In both cases he'll get all the apples.

In the second sample test the optimal solution is to go left to $ x=-1 $ , collect apples from there, then the direction will be reversed, Amr has to go to $ x=1 $ , collect apples from there, then the direction will be reversed and Amr goes to the final tree $ x=-2 $ .

In the third sample test the optimal solution is to go right to $ x=1 $ , collect apples from there, then the direction will be reversed and Amr will not be able to collect anymore apples because there are no apple trees to his left.

## 样例 #1

### 输入

```
2
-1 5
1 5
```

### 输出

```
10```

## 样例 #2

### 输入

```
3
-2 2
1 4
-1 3
```

### 输出

```
9```

## 样例 #3

### 输入

```
3
1 9
3 5
7 10
```

### 输出

```
9```

# 题解

## 作者：ForMyDream (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF558A)

## 一、整体思路

求最大值，过程很单调，确定**贪心**。

## 二、分析

您可以找一张纸，一支笔，按照题意画一下图。

由画图得知（图省略了，但是真的很好画） ：

比如：画**三棵树**，在原点两侧，一边**两棵**，一边**一棵**，
进行模拟，发现当我们**先采两棵**的那一边时就可以把三棵树**全部采完** ，但是**先采一棵**的那一边就只能采两棵树。（没有树，走不回去了）

也就是：第一种方案比第二种方案多采一次苹果，方案更优(您也可以把它类比成绕定滑轮动动滑轮)。 
 

从而得出结论：**当有一边多的时候，先采多的一边会比先采少的一边多采一次**。

## 三、其他

- 由于输入时坐标是乱序的，所以我们要**按照坐标给树排一个序**。

- 我们可以找树少的一边为基准点，**两边同时加上树少的一边的个数，树多的一边再多加一次，这是处理数据的核心**。

- 其他我会在代码注释里说明。

## 四、代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;

struct Tree{
	int apple,address;
	//树上的苹果 坐标 
};
Tree pos[101],neg[101];
//positive 存储坐标为正的树 negative 存储坐标为负的树 
int n,x,a,pos1,pos2;//指针 在存储、记录方面用 

bool cmp(Tree t1,Tree t2){
	return t1.address<t2.address;
	//记住树的坐标是混乱的 要按照坐标排序 
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
   //上面的几行是输入&输出的优化，不懂的可以忽略                              
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>x>>a;
		if (x<0){
			//如果坐标为负 取绝对值 存入neg中
			/*当然您也可以不这样做 但是要多写一个cmp2函数*/ 
			x=-x;
			neg[pos2].address=x;neg[pos2].apple=a;
			pos2++; 
		}else {
			pos[pos1].address=x;pos[pos1].apple=a;
			pos1++;
		} 
	}
	sort(pos,pos+pos1,cmp);
	sort(neg,neg+pos2,cmp);
	//找苹果少的一边 以它为基准点 一边是x 另一边是x+1 
	int x=min(pos1,pos2),ans=0;
	for (int i=0;i<x;i++){
		ans+=pos[i].apple;
		ans+=neg[i].apple;
	}
	if (pos1>pos2) ans+=pos[x].apple;
	else if (pos2>pos1) ans+=neg[x].apple;
	//注意 还有一种情况：pos1==pos2 啥也不用做 
	cout<<ans;
	return 0;
} 
```

虽然我写的不是很好，但是您看的这么认真，留个赞好吗？

二零二二年七月二十六日。

---

## 作者：crh1272336175 (赞：1)

很容易想到的一个贪心：如果0点左边多，就先往左走，反之先往右边走

因为这样能够摘到的苹果数量是$min(左边个数，右边个数)+1$

我们可以用两个vector  le与ri，分别存储0点左边的和右边的苹果的信息

至于要存储的信息，自然是2个，所以我们可以使用pair来存储

还有一个很小的很容易想到的贪心，那就是排序，将左右两边的苹果都按照x下标进行排序，然后扫一遍就可以得出答案

时间复杂度$O(n log n)$

AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> PLL;
const int N=1005;
ll n,ans;
vector<PLL> le,ri;//正方向，负方向 
int main()
{
    scanf("%lld",&n);
    for(register ll i=1; i<=n; i++)
    {
        ll a,b; scanf("%lld%lld",&a,&b);
        if(a>0) ri.push_back({a,b});
        else le.push_back({-a,b});
    }
    sort(ri.begin(),ri.end());
    sort(le.begin(),le.end());
    ll num=min(le.size(),ri.size());
    for(register ll i=0; i<num; i++)
        ans+=le[i].second+ri[i].second;
    if(le.size()>ri.size()) ans+=le[ri.size()].second;
    else if(le.size()<ri.size()) ans+=ri[le.size()].second;
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：TLEWA (赞：1)

很简单的~~蓝~~红题,运用最基础的贪心即可解决该问题

以 $Amr$ 为中心,考虑两种不同情况：

1. 两边树的数量不同，那么一定是先走树多的一边最优，因为可以多摘到树多那一边的下一棵树的果子
2. 两边树的数量相同，可以摘掉所有果子，不会有一边多摘一个树的果子

在第一种情况下，树少的一边摘完了自己的果子，树多的一边多摘一个

在第二种情况下，所有的果子都被摘完了

注意要排序，时间复杂度 $O(n\log n)$，以下是我的 AC 代码，详细过程在注释里：
```cpp
//简单贪心,建议评红
#include<bits/stdc++.h>

using namespace std;

struct Node{ //用来存储苹果信息的结构体
	int val,num;
}arr1[10086],arr2[10086];

int p1,p2; //两个变量,作为指针使用
long long summ; //计数变量

bool cmp(Node n1,Node n2){ //别问我为什么不用pair(其实是忘了)
	return n1.val<n2.val;
}

int main(){
	ios::sync_with_stdio(false); //解除同步流
	cin.tie(0);
	cout.tie(0);
	int n,val,num;
	cin >> n;
	for(int i=0;i!=n;++i){ //循环读入
		cin >> val >> num;
		if(val<0) arr1[p1].val=-val/*倒序一下*/,arr1[p1].num=num,p1++; //给垃圾(划掉)苹果分类
		else arr2[p2].val=val,arr2[p2].num=num,p2++;
	}
	//将分好类的苹果分别排序
	sort(arr1,arr1+p1,cmp);
	sort(arr2,arr2+p2,cmp);
	
	int p3=min(p1,p2);
	for(int i=0;i<p3;++i){
		summ+=arr1[i].num+arr2[i].num; //两个数组同时累加
	}
	//最后判断一下哪边大
	if(p1<p2) summ+=arr2[p3].num;
	else if(p1>p2) summ+=arr1[p3].num;
	
	cout << summ; //输出结果
	return 0;
}

```


---

## 作者：Aya_tt (赞：0)

这题好像不是蓝题难度吧，就是一道规律题。







# 思路
这题说从 $0$ 开始采摘，那我们就先用 $sum1$,$sum2$ 统计一下坐标大于零和小于零的数量，相信只要你细心观察，就会发现那边多就先往哪边走。

就比如原点左边有三个数 $a1$,$b1$,$c1$(不妨设 $a1$ 在最右端，$c1$ 在最左端),原点右边只有 $a2$,我们分两种情况讨论一下。

$1$,假如向数少的右边走，得出来的和是 $a2 + c1$。
$2$,假如向数多的左边走，和就变成了 $a2+c1+b1$。

多举几个例子也是这样，综上所处，**想要最终的数更大，就往多的地方走**。


# 实现
让 $k$ 标记为原点坐标，不妨令 $j=\min(sum1,sum2)$，会发现在 $0$ 左右 $j$ 个数肯定要被加上，然后再看看 $sum1$,$sum2$ 谁大，找一组数据随便模拟一下，会发现那边多那边就多加一个元素。

贴一下核心代码：
```c
 int j = min(sum1,sum2),ans = 0;
    for(int i = k - j + 1;i <= k + j;i++){
        ans += q[i].w;
    }
    if(sum1 > sum2) ans += q[k + j + 1].w;
    if(sum1 < sum2) ans += q[k - j].w;
```

总体代码就不贴了，相信已经说的差不多了。

---

## 作者：李柯欣 (赞：0)

[CF558A Lala Land and Apple Trees](https://www.luogu.com.cn/problem/CF558A)。

[更好的阅读体验](https://www.luogu.com.cn/blog/likexin/solution-cf558a)
。

## 思路：

贪心即可。

先按照树的坐标从小到大排序，得出 Amr 左右侧的树的个数 $l$ 和 $r$。

略微思考，画一下草图后得出结论：向树多的那一侧走更优。

此时 Amr 会把树的个数更小的那一边摘完。

设树的个数更小的那一边有 $x$ 棵树，那么另一边就会摘 $x + 1$ 棵树，剩下的模拟即可。

特别的，如果 $l = r$，那么 Amr 就会把两边的树都摘光。

考虑三种情况：

1.  $l<r$：向右边走，左边摘 $x$ 棵，右边摘 $x+1$ 棵。
2.  $l=r$：向哪边走都可以，左右都摘 $x$ 棵。
3.  $l>r$：向右边走，左边摘 $x+1$ 棵，右边摘 $x$ 棵。

这三种情况可以压缩一下：

```cpp
int ql=((x==l)?x:x+1);//左边摘多少棵树。 
int qr=((x==r)?x:x+1);//右边摘多少棵树。 
```

## 代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
int n; 
struct node{
	int xi;
	int ai;
}a[100001];
bool cmp(node xx,node yy){ 
	return xx.xi<yy.xi;
}
signed main(){
	//读入。 
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].xi>>a[i].ai;
	}
	sort(a+1,a+1+n,cmp);
	int l=0,r=0;
	for(int i=1;i<=n;i++){//从左到右遍历树的坐标，找 Amr 的左侧和右侧分别有几棵树。 
		if(a[i].xi<0){
			l++;
		}
		if(a[i].xi>0){ 
			r++;
		}
	}
	int x=min(l,r);//树更小的那一边的个数 。 
	int ql=((x==l)?x:x+1); 
	int qr=((x==r)?x:x+1);
	int ans=0;//Amr最多可以摘到多少苹果。 
	for(int i=1;i<=n;i++){
		if(qr&&a[i].xi>0){
			qr--;
			ans+=a[i].ai;
		} 
	}  
	for(int i=n;i>=1;i--){ 
		if(ql&&a[i].xi<0){
			ql--;
			ans+=a[i].ai;
		} 
	} 
	cout<<ans;//输出。 
	return 0;
}

```

[ AC 记录](https://www.luogu.com.cn/record/80320102)。
~~（本来可以一遍过的，但是 [ Waiting ](https://www.luogu.com.cn/record/80320069) ）~~。

---

## 作者：_Legacy (赞：0)

#### 分析
别看这题难度不高，但是坑点多多：

坑点一：输入坐标的要排序

坑点二：要判断从那一边开始能得更多苹果

由此可见，一道红题难度的题是怎么坑提交数的，所以记得

### 做题前千万要好好看题

~~CF特点之一~~

#### 代码结构

1. 将输入坐标分类

2. 将正负坐标排序

3. 判断从那一边开始能得到更多苹果

4. 挨个"采摘"，直到有一边"采摘"完

#### 上代码
```
#include <bits/stdc++.h>
using namespace std;
long long n,a[100][2],b[100][2],lena=0,lenb=0,x,y,ans=0;
int main(){
	cin >> n;
	for(int i=0;i<n;i++){
		cin >> x >> y;
		if(x<0){
			a[lena][0]=x;
			a[lena][1]=y;
			lena++;
		}
		else{
			b[lenb][0]=x;
			b[lenb][1]=y;
			lenb++;
		}
	}
	for(int i=0;i<lena;i++){
		for(int j=i+1;j<lena;j++){
			if(a[i][0]<a[j][0]){
				swap(a[i][0],a[j][0]);
				swap(a[i][1],a[j][1]);
			}
		}
	}
	for(int i=0;i<lenb;i++){
		for(int j=i+1;j<lenb;j++){
			if(b[i][0]>b[j][0]){
				swap(b[i][0],b[j][0]);
				swap(b[i][1],b[j][1]);
			}
		}
	}
	if(lena>lenb){
		for(int i=0;i<n;i++){
			if(i%2==0){
				if(a[i/2][1]==0)
					break;
				ans+=a[i/2][1];
			}
			else{
				if(b[i/2][1]==0)
					break;
				ans+=b[i/2][1];
			}
		}
	}
	else{
		for(int i=0;i<n;i++){
			if(i%2==0){
				if(b[i/2][1]==0)
					break;
				ans+=b[i/2][1];
			}
			else{
				if(a[i/2][1]==0)
					break;
				ans+=a[i/2][1];
			}
		}
	}
	cout << ans;
} 
//CF558A
```

---

## 作者：动态WA (赞：0)

一开始看题目以为跟[关路灯](https://www.luogu.com.cn/problem/P1220)这题差不多，仔细看才发现是红题难度

第一步：先用结构体分别记录每个点的坐标，x<0的点放一个结构体，x>0的点放另外一个结构体

第二步：对结构体进行排序（我这里用的是operator重载运算符，效果跟写cmp函数差不多）

第三步：用i来模拟坐标，一开始用while保持i<=左边点的个数&&i<=右边点个数，当while结束后，比较哪边点个数大，再加上大的那边的一个点
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;
struct edge{
	int x,a;
}r[1001],l[1001];
int n,ln,rn;
bool operator < (edge a,edge b){
	return a.x<b.x;
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int x,a;
		scanf("%d%d",&x,&a);
		if (x>0){
			r[++rn].x=x;
			r[rn].a=a;
		}else{
			l[++ln].x=-x;
			l[ln].a=a;
		}
	}
	sort(l+1,l+1+ln);
	sort(r+1,r+1+rn);
	int i=1;
	int ans=0; 
	while (i<=rn&&i<=ln){
		ans+=r[i].a+l[i].a;
		i++;
	}
	if (rn>ln) ans+=r[i].a;
	if (ln>rn) ans+=l[i].a;
	cout<<ans;
}
```


---

## 作者：zzx0826 (赞：0)

## [【Codeforces #312 div2 A】Lala Land and Apple Trees](https://www.luogu.com.cn/problem/CF558A)
--------------------
首先，此题的大意是在一条坐标轴上，有$n$个点，每个点的权值为$a_{i}$,第一次从原点开始走，方向自选(<- or ->)，在过程中，若遇到一个权值>0的点，则将此权值计入答案，并归零。当次、此方向上的所有点均为0后，输出此时的答案。

然后，进行分析:

我们很容易想到这是一个**贪心**，我们将正的和负的分别存入两个数组，最初的方向为: $sum_{zheng} > sum_{fu} ? zheng : fu$即正负两边那边权值 > 0的点多就先往哪个方向走，然后，就成模拟题了……

*Code*:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 100 + 5;
const int M = 100001;
int n,dir,l[M],r[M],lsum,rsum,ans;
int markjia[M] = {0},markjian[M] = {0};
int check()
{
    if(dir == -1)
    {
        for(int i=1;i<=100000;i++)
        {
            if(markjian[i])return i;
        }
        return 0;
    }else{
        for(int i=1;i<=100000;i++)
        {
            if(markjia[i])return i;
        }
        return 0;
    }
}
int main()
{
    scanf("%d",&n);
    int x,a;
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&x,&a);
        if(x < 0){x *= -1;l[x] = a,markjian[x] = 1,lsum++;}
        else r[x] = a,markjia[x] = 1,rsum++;
    }
    if(lsum >= rsum)dir = -1;
    else dir = 1;
    for(int i=1;i<=n;i++)
    {
        if(check() == 0)break;
        if(dir == -1)
        {
            ans += l[check()];
            markjian[check()] = 0;
            dir = 1;
        }else{
            ans += r[check()];
            markjia[check()] = 0;
            dir = -1;
        }
    }
    cout << ans;
    return 0;
}
```
## 总结
所谓贪心，就是要找到最佳策略，再通过分析得到解题方法。

$End.$

---

## 作者：　　　吾皇 (赞：0)

### 很容易想到，这道题应该有三种情况：（左边有x1个，右边有x2个）
#### 1.x1<x2:应先向右边走，这种情况等同于左边有x2-1个
#### 2.x1=x2：向哪边走都可以
#### 3.x1>x2:应先向左边走，这种情况等同于右边有x1-1个
### 所以无论x1与x2的大小关系，一定要走的一定为a[1..x3]+b[1..x3](a是左边的，b是右边的，个人开了个结构体；x3=min（x1，x2））
### 大概的就是这样，代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
#define F(a,b) for(int i=a;i<=b;i++)
int n,m,x1,x2,x3,ans;
struct apple{
	int a1,x;
};
apple a[101],b[101];
bool cmp1(apple x,apple y){
	return x.a1>y.a1;
}
bool cmp2(apple x,apple y){
	return x.a1<y.a1;
}
int main(){
	cin>>n;
	F(1,n){
	    cin>>m;
		if(m>0) cin>>a[++x1].x,a[x1].a1=m;
		else cin>>b[++x2].x,b[x2].a1=m;
	}
	sort(a+1,a+1+x1,cmp2);
	sort(b+1,b+1+x2,cmp1);
	x3=min(x1,x2);
	F(1,x3) ans+=(a[i].x+b[i].x);
	if(x1>x2) ans+=a[x3+1].x;
	if(x1<x2) ans+=b[x3+1].x;
	cout<<ans;
} 
```

## 切勿Ctrl+C

---

## 作者：Vnlamac (赞：0)

**前言：** 感谢 EWEN 同志把这道水蓝题搬到模拟赛让我们切！

**正文：** 一开始看，以为是一道大模拟题，后来仔细看看，发现了一个关键的信息。采集苹果时采完一个就掉头，也就是说，数轴的正半轴和负半轴几乎是同时采摘的，只是先后顺序不同，然而这取决于初始的方向。最后的结束条件是某个半轴上的苹果树都采光了。那么这时很容易想到，采集苹果数量的最大值，不是取决于苹果树上苹果的数量，而是半轴上苹果树的数量。

先将正半轴上的苹果树的棵树记为 $ac$ ，负半轴上的苹果树的棵树记为 $bc$ ，读进来时用变量 $ans$ 记录所有苹果树上的苹果总和。接下来根据坐标进行从小到大排序，进行分类讨论。如果 $ac > bc$ ，说明负半轴上的苹果肯定会先被摘完，那么正半轴上的一些苹果就摘不到，就得把剩下的苹果树上的苹果减去，就是正半轴上靠外的共 $ac-bc-1$ 棵苹果树。反之，如果 $ac \leq bc $ ，那么就要对负半轴进行同样的操作。

下面是主要代码。
```cpp
int n,k,ac,bc,ans=0;rd(n);ac=bc=0;//分别记录左、右半轴上苹果树的棵数
	for(int i=1;i<=n;i++){
		rd(k);
		if(k>0){ac+=1;a[ac].pos=k;rd(a[ac].val);ans+=a[ac].val;}
		else {bc+=1;b[bc].pos=k;rd(b[bc].val);ans+=b[bc].val;}
	}
	sort(a+1,a+ac+1,cmp);//读进来记得排序
	sort(b+1,b+bc+1,cmp);
	if(ac>bc){for(int i=1;i<=ac-bc-1;i++)ans-=a[ac-i+1].val;}//最后进行处理
	else {for(int i=1;i<=bc-ac-1;i++)ans-=b[i].val;}
	wt(ans);
```


---

