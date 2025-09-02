# [USACO20OPEN] Social Distancing II B

## 题目描述

由于高传染性的牛传染病 COWVID-19 的爆发，Farmer John 非常担忧他的奶牛们的健康。

尽管他尽了最大努力使他的 $N$ 头奶牛们（$1\le N\le 1000$）践行“社交距离”，还是有许多奶牛不幸染上了疾病。编号为 $1\ldots N$ 的奶牛们分别位于一条长直道路上的不同位置（相当于一维数轴），奶牛 $i$ 位于位置 $x_i$。Farmer John 知道存在一个半径 $R$，任何与一头被感染的奶牛距离不超过 $R$ 单位的奶牛也会被感染（然后会传染给与其距离 $R$ 单位内的奶牛，以此类推）。

不幸的是，Farmer John 并不确切知道 $R$ 的值。他只知道他的哪些奶牛被感染了。给定这个数据，求出起初感染疾病的奶牛的最小数量。 

## 说明/提示

### 样例解释 1

在这个例子中，我们知道 $R<3$，否则位于位置 $7$ 的奶牛会传染给位于位置 $10$ 的奶牛。所以，至少 $3$ 头奶牛初始时已被感染：位于位置 $1$ 和 $3$ 的两头奶牛中的一头，位于位置 $6$ 和 $7$ 的两头奶牛中的一头，以及位于位置 $15$ 的奶牛。 

## 样例 #1

### 输入

```
6
7 1
1 1
15 1
3 1
10 0
6 1```

### 输出

```
3```

# 题解

## 作者：Gilbert1206 (赞：4)

## 贪心半径
先对牛的时间排序，找到感染距离 R，向前后寻找超过半径和没有超过半径的牛然后再逐层到最后的一头牛。

## AC code

```
#include<bits/stdc++.h>
using namespace std;
struct health{
	int x;
	int y;
}a[1000];
int ans(health a,health b){
	return a.x<b.x;
}

int main() {
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y; 
	}
	sort(a+1,a+n+1,ans);//排序 
//	for(int i=1;i<=n;i++){
//		cout<<a[i].x<<" "<<a[i].y<<endl;
//	}
	int minn=10000000;
	for(int i=1;i<=n;i++){//贪心 
		if(a[i].y==0){
			if(minn>a[i].x-a[i-1].x&&a[i-1].y!=0){
				minn=a[i].x-a[i-1].x;
			}
			if(minn>a[i+1].x-a[i].x&&a[i+1].y!=0){
				minn=a[i+1].x-a[i].x;
			}
	//		cout<<minn<<" ";
		}
	}
	int abb=0;
	for(int i=1;i<=n;i++){//寻找 
		if(a[i].y==1){
			if(a[i-1].y==1&&a[i].x-a[i-1].x<minn){
				continue;
			}
			abb++;
		}
	}
	cout<<abb;
	return 0;
}
```

---

## 作者：yangjinqian (赞：3)

## 思路：贪心

输入完后，从 $2$ 到 $n - 1$ 遍历一遍，如果当前牛没有被感染，那么上一头牛和下一头牛都不能感染它，更新 $R$ 为上一头（被感染过）和下一头（被感染过）到当前牛的距离和 $R$ 取 $\min$ 。

最后从 $2$ 到 $n - 1$ 遍历一遍，若当前牛被感染且上一头牛没被感染，或上一头牛到这一头牛的距离 $\le R$ 则答案加一。

最后输出答案。

## 代码
```cpp
#include <bits/stdc++.h>
#define f first
#define s second
#define pii pair<int, int>
using namespace std;
const int N = 1010;
int n, minn = 0x3f3f3f3f, ans;
pii a[N];
int flag[N];
bool cmp(pii c, pii d){
    return c.f < d.f;
}
int main(){
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].f >> a[i].s;
    sort(a + 1, a + n + 1, cmp);
    for (int i = 2; i < n; i++)
        if (!a[i].s){
            if (a[i - 1].s) minn = min(minn, a[i].f - a[i - 1].f);
            if (a[i + 1].s) minn = min(minn, a[i + 1].f - a[i].f);
        }
    for (int i = 1; i <= n; i++)
        if (a[i].s)
            if (!a[i - 1].s || a[i].f - a[i - 1].f >= minn)
                ans++;
    cout << ans;
    return 0;
}
```

注：读入时可以用 `pair` 或结构体，怎么方便怎么写。

---

## 作者：dabenBbx (赞：2)

## 贪心 $+$ 排序

先将牛的位置进行排序，按照从小到大的顺序。

这道题的关键就是：感染距离是多少。如果一头牛到最后也没被感染，证明它与前一只或后一只的距离是大于感染半径的，所以只需排序后从前向后遍历计算最小的感染半径，并再将感染半径带入遍历看每头是否为前一只所感染。如果是则它并非为感染源，否则反之。

## **Code**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,mind=1000006;
struct node{
	int d,z;
}a[1005];
bool cmp(node x,node y){
	return x.d<y.d;//将牛的位置从小到大排 
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].d>>a[i].z;
	}
	sort(a+1,a+n+1,cmp);//排序 
	for(int i=1;i<=n;i++){
		 if (a[i].z == 0)//健康牛为被感染，证明感染范围小于此牛与前后牛间的最小距离 
        {
            if (i > 1 && a[i - 1].z == 1) //与前一只的距离 
            	mind= min(mind, a[i].d - a[i - 1].d);
            if (i < n && a[i + 1].z == 1)//与后一只的距离 
            	mind = min(mind, a[i + 1].d - a[i].d);
        }
	}
	for(int i=1;i<=n;i++){
		if(a[i].z==1){//已被感染 
			if(a[i-1].z==1&&a[i].d-a[i-1].d<mind)//与前一只小于感染距离则是被前一只传染 
			   continue;
			ans++;//否则是传染源 
		} 
	}
	cout<<ans;//输出答案 
	return 0;
} 
```

---

## 作者：kuikuidadi (赞：1)

# 思路
如果学过并查集的同学，应该不难翻译这个题：

最大化 $R$，在 $R$ 范围内结点并为一个祖先，最后输出最小祖先数量。

还是先了解一下并查集标准的两个函数：
```cpp
int find(int x){
	if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy) fa[fx]=fy;
}
```
# 实现方法
利用位置来排序，遍历全部健康奶牛，左右寻找得病的奶牛，取最小值为 $R$。

对于每个得病奶牛，向左找位置小于 $R$ 的奶牛，合并他们。遍历全部得病奶牛，找祖先。

最后输出祖先个数。

---

## 作者：_luogu_huowenshuo_ (赞：1)

## 思路
先定义一个结构体，然后 `sort` 从小到大排序 `x`。最后分别循环，其中第一个循环用于算出 $x$ 的最小值，第二个用于算出答案。
## 代码
```cpp
#include<bits/stdc++.h>
#include<time.h>
#define int long long
#define double long double
const int N=2e6+5;
using namespace std;
int n,sum,minx=1919810114;
struct node
{
	int x,s;
}a[N];
bool cmp(node q,node p)
{
	return q.x<p.x;
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].s;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
		if(!a[i].s)
        {
            if(a[i-1].s)minx=min(minx,a[i].x-a[i-1].x);
            if(a[i+1].s)minx=min(minx,a[i+1].x-a[i].x);
        }
	for(int i=1;i<=n;i++)
		if(a[i].s)
		{
			if(a[i-1].s&& a[i].x-a[i-1].x<minx) 
				continue;
			sum++;
		}
	cout<<sum;	
 	return 0;
}
```

---

## 作者：Rainber (赞：0)

### 思路：贪心

1. 要使疾病开始传播之前已经得病的奶牛数量最少，就是使传播距离 $R$ 尽可能大。
2. 考虑对于一个已经感染的牛，如果它前（后）的牛没有被感染，则说明它与那一头牛的距离大于等于感染距离 $R$。通过此法可以求出最大的 $R$。
3. 如果患病牛与前一头患病牛距离小于 $R$，则认为这一头牛是被前一头牛传染的，否则它就是传染源。这里要注意 $ans$ 被提前初始化为 $1$，因为第一个传染源不会计入 $ans$，要被特殊考虑。

AC 代码（慎看，指针巨多）：
```cpp
#include<stdio.h>
#include<algorithm>
#define MAXN 1000
using std::sort;
struct Cow
{
	int place;//牛的位置
	int status;//牛的患病状态
} cows[MAXN];
int cmp(struct Cow a,struct Cow b)
{
	return a.place<b.place;//从小到大以位置排序
}
int min(int a,int b)
{
	return a<b?a:b;
}
int main()
{
	int n,r,ans;
	struct Cow *cp;//别怕，这是循环变量。
	scanf("%d",&n);
	for(cp=cows;cp<cows+n;++cp)
	{
		scanf("%d%d",&cp->place,&cp->status);//不要理会那个箭头，就是普通输入。。。
	}
	sort(cows,cp,cmp);
	r=1e9;//将r设为极大值。
	for(cp=cows+1;cp<cows+n-1;++cp)//这里的+1-1是防止越界，可以证明排除边界不影响答案。
	{
		if(cp->status==0)//如果这头牛没有患病……
		{
			if((cp-1)->status==1)//考虑前面的牛
			{
				r=min(r,cp->place-(cp-1)->place);//更新R
			}
			if((cp+1)->status==1)//考虑后面的牛
			{
				r=min(r,(cp+1)->place-cp->place);//更新R
			}
		}
	}
	ans=1;//初始化ans，包含第一个传染源。
	for(cp=cows+1;cp<cows+n;++cp)//这里的+1也是防止越界。
	{
		if(cp->status==1)//如果被感染……
		{
			if(cp->place-(cp-1)->place<r)//被上一头牛感染跳过
			{
				continue;
			}
			ans++;//否则计入总数
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：haoran2008 (赞：0)

# 贪心
解决思路：  
1.将奶牛的位置进行排序。  
2.找出感染的牛和没有感染的牛的最近距离，作为 R 值。  
3.根据 R 值计算答案。

### 代码如下：

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N=1e3+5;
struct Cow{
    int x,f;
}a[N];
bool cmp(Cow A,Cow B){
    return A.x < B.x;
}
int main(){
    int n,ans=0;
    cin>>n;
    for (int i=1;i<=n;i++) cin>>a[i].x>>a[i].f;
    sort(a+1,a+n+1,cmp);
    int r=1e9;
    for (int i=1;i<=n;i++){//确定r
        if (i+1<=n && a[i].f==1 && a[i+1].f==0) r=min(r,a[i+1].x-a[i].x);
        if (i+1<=n && a[i].f==0 && a[i+1].f==1) r=min(r,a[i+1].x-a[i].x);
    }
    for (int i=1;i<=n;i++){//计算答案
        if (a[i].f==1 && a[i-1].f==1 && a[i-1].x+r>a[i].x) continue;
        if (a[i].f==1) ans++; 
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：jsisonx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9953)

# 题目分析
思路与其他题解相似，只是稍微详细解释了一下。

读题可知本题需要使用贪心算法。

首先是一个大贪心，即要使初始感染的牛数量少，$R$ 必须要尽可能地大。证明比较简单：首先染病的牛分为两种：一开始就染了病的和被其他牛传染的，这两种牛的数量之和为定值，是所有的病的牛的总数。若 $R$ 在合法范围内取到了最大值，说明每头被感染的牛都可以将疾病传播到最远的地方，那么它所能感染到的区域一定是最大的，其中包含的牛一定是最多的，那么被其它牛传染的这一类牛就会最多，那么初始时感染的牛一定最少。

接下来再用贪心求 $R$ 的最大值。这里的思路比较绕：我们要求它的最大值，实际是要求它至少得小到什么程度，比如最后求出 $R<t$，那么 $R$ 的最大值就是 $t-1$ 了。因此这次贪心实际上是求 $t$。那么如何求呢？

首先对所有牛按照位置从小到大排序，因为题目要求与位置无关。一下所说的位置均为排序后的。

我们发现一点，如果第 $x$ 头牛没得病，而第 $x+1$ 头牛得病了，那么 $R$ 必须要小于这两头牛的距离，否则第 $x+1$ 头牛就会传染给第 $x$ 头牛了。除此之外，好像就没有关于 $R$ 的约束条件了，因此实际上是要求两头牛之间距离的最小值。这里需要注意一点，就是对于任意一个未染病的牛 $p$，只需要考虑其两边与它最近的染病的牛 $y$ 和 $k$。证明十分简单：设第 $i$ 头牛的坐标为 $X_i$。只考虑 $y$ 和 $k$ 时，$R<\min(\left| X_p-X_y \right|,\left| X_p-X_k \right|)$。若计算牛 $y-m$ 与牛 $k+n$（$m,n>0$ 且 $m$，$n$ 不同时为 $0$） ，则 $R<\min(\left| X_p-X_{y-m} \right|,\left| X_p-X_{k+n} \right|)$。易证后一个 $R$ 一定大于前一个。

这样，方法已经基本上明确了。下面说一下实现细节：先排序。排序后首先设一个数组存储所有感染的牛（这里认定第 $0$ 号和第 $n+1$ 号牛均已感染。求解 $R$ 最大值求解时枚举牛的编号，若该牛未感染，则 $R$ 应设为 $\min(R,\min(\left| X_p-X_y \right|,\left| X_p-X_k \right|))$，其中 $y$，$k$ 见上。这里实现时可以用一个变量 $h$ 指向感染数组中离这个牛最近且在该牛左边的牛的编号（有点绕，可以多读几遍理解一下）则在该牛右边的离他最近的感染的牛就是感染数组中的第 $h+1$ 个元素。初始时 $h=0$，枚举过程中遇到感染的牛就把 $h$ 加一。

最后再从头到尾遍历一遍感染数组，如果两头感染的牛距离**大于等于** $R$，那么答案加一。注意如果存在感染的牛的话初始答案应设为 $1$。

# 代码


```
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
struct cow{
	int x,ill;
}c[1001];
int cmp(cow a,cow b){
	return a.x<b.x;
}
int ans=1;
int main(){
	long long n,maxp=0x3ffffff,illy[1001],top=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>c[i].x>>c[i].ill;
	}
	illy[0]=0;
	c[0].x=-0x7ffffffff;
	c[n+1].x=0x7ffffffff;
	sort(c+1,c+1+n,cmp);
	for(int i=1;i<=n;i++){
		if(c[i].ill){
			illy[++top]=i;
		}
	}
	illy[top+1]=n+1;
	top++;
	if(!top){
		cout<<0;
		return 0;
	}
	int h=0;
	for(int i=1;i<=n;i++){
		if(c[i].ill==0){
			int d1=abs(c[i].x-c[illy[h]].x),d2=abs(c[i].x-c[illy[h+1]].x);
			if(maxp>min(d1,d2)){
				maxp=min(d1,d2);
			}
		}
		else{
			h++;
		}
	}
	for(int i=1;i<top;i++){
		if(c[illy[i+1]].x-c[illy[i]].x>=maxp){
			ans++;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：cly312 (赞：0)

解决思路：

根据奶牛的位置对数组进行排序。计算相邻健康奶牛和感染奶牛之间的最小距离。这个距离值减一用来估计感染传播的半径。（确保了感染奶牛之间的距离在当前半径下不会导致传播给其他健康奶牛。）

遍历排序后的奶牛列表，找到每一段连续感染奶牛的区域，并计算这些区域中可能需要的初始感染奶牛的数量。对于每一段连续感染奶牛，检查其能覆盖的区域，并增加初始感染奶牛的计数。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct cow{
	int x;
	bool h;
}a[1010];
int n;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].h;
	sort(a+1,a+n+1,[](const cow&a,const cow&b){return a.x<b.x;});
	int mr=INT_MAX;
	for(int i=1;i<n;i++)
		if(a[i].h!=a[i+1].h) mr=min(mr,a[i+1].x-a[i].x);
	mr--;
	int ans=0;
	for(int i=1;i<=n;i++){
		if(a[i].h){
			++i;
			while(i<=n&&a[i].h&&a[i].x-a[i-1].x<=mr)
				++i;
			++ans;
			--i;
		}
	}
	cout<<ans;
}
```

---

## 作者：wyc0607 (赞：0)

[题目传送门](https://luogu.com.cn/problem/P9953)

算法：贪心+结构体的排序。

先按奶牛的距离排序，距离小的在前，大的在后.再看看感染的牛和未感染牛最近的距离，即为 $R$ 值，再根据 $R$ 值判断即可。

 $p$ 为距离，$b$ 为该牛是否被感染（值为一即为被感染）。


```cpp
#include<bits/stdc++.h>
using namespace std;
class Node {
	public:
		int p;
		bool b;
};
bool cmp(Node a,Node b) {//距离按从小到大的顺序。
	return a.p<b.p;
}
Node a[1005];
int n;
main() {
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>a[i].p>>a[i].b;
	}
	sort(a+1,a+1+n,cmp);
	int r=0x7fffffff,ans=0;// R 即为感染半径。
	for(int i=1; i<=n-1; i++) if((a[i].b==1&&a[i+1].b==0)||(a[i].b==0&&a[i+1].b==1)) r=min(r,a[i+1].p-a[i].p);//确定 R 最大值。
		for(int i=1;i<=n;i++){  // 统计初始感染奶牛的个数。
			if(a[i].b==0) continue;
			if(a[i-1].b==1&&a[i].p-a[i-1].p<r) continue;//不满足条件的直接 out。
			ans++;//剩下的就是。
		}
	cout<<ans;//输出。
}
```

---

## 作者：Undefined_Shawn (赞：0)

#### 算法：贪心 + 模拟
这道题使用了贪心的思想，首先确定 $R$ 的范围，比如样例 $1$ ，$R$ 小于 $3$ ，因为位置 $7$ 的奶牛没有传染给位置为 $10$ 的奶牛。

确定好奶牛的范围后，不难发现要想初始感染的奶牛数量最少，就要使 $R$ 最大。

确定好 $R$ 后，如果自己和两边奶牛都被感染了，就看距离。如果距离大于 $R$ 就说明这头奶牛是初始感染奶牛，统计一下，最后输出答案即可。

上代码：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
struct P {
  int f, idx;  
};
P moo[1000005];
bool cmp(P x, P y) {
	return x.idx < y.idx;
}
int main() {
    int R = 1e9, n, ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> moo[i].idx >> moo[i].f;
    sort(moo + 1, moo + n + 1, cmp);    // 结构体排序
    for (int i = 1; i <= n; i++) {  // 确定R最大值
        if (moo[i].f == 0) {
            if (i > 1 && moo[i - 1].f == 1) R = min(R, moo[i].idx - moo[i - 1].idx);
            if (i < n && moo[i + 1].f == 1) R = min(R, moo[i + 1].idx - moo[i].idx);
        }
    }
    for (int i = 1; i <= n; i++) {  // 统计初始感染奶牛的个数
    	if (moo[i].f == 0) continue;
        if (moo[i - 1].f == 1 && (moo[i].idx - moo[i - 1].idx < R)) continue;
        ans++;
    }
    cout << ans;
    return 0;   // 华丽结束~~~
}
```

---

## 作者：HsNu1ly7_ (赞：0)

## 思路
我们可以通过每头奶牛的染病情况来判定 $R$ 的取值范围，如果奶牛 $i$ 未染病，就可以找到离它最近的染病的奶牛的位置，从而更新 $R$ 。

接着我们继续判断如果两头染病的牛的距离小于 $R$ 那么这两头牛可以互相传染，否则答案加一。

代码如下：


```c++
#include <iostream>
#include <algorithm>
using namespace std ;
#define int long long
int n ;
struct node {
	int x , s ;
}arr[1010];

bool cmp ( node a , node b ){ return a.x < b.x ; }

signed main (){
	ios::sync_with_stdio(0) ;
	cin.tie(0) ;
	cout.tie(0) ;
	cin >> n ;
	for ( int i = 1;  i <= n ;i++ ) cin >> arr[i].x >> arr[i].s ;

	sort ( arr + 1 , arr + 1 + n , cmp ) ;
	
	int R = 0x3f3f3f3f ;

	for ( int i = 1 ; i <= n ;i++ ){
		if ( !arr[i].s ){
			if ( arr[i + 1].s && i < n ){
				R = min ( R , arr[i + 1].x - arr[i].x ) ;
			}
			if ( arr[i - 1].s && i > 0 + 1 ){
				R = min ( R , arr[i].x - arr[i - 1].x ) ;
			}
		}
	}
	int cnt = 0 ;
	for ( int i = 1 ; i  <= n ; i++ ){
		if ( arr[i].s ){
			if ( arr[i - 1].s && arr[i].x - arr[i - 1].x < R ){
				cnt = cnt ;
				swap ( cnt , n ) ;
				swap ( cnt , n ) ;
				arr[i].s = arr[i].s ;
				continue ;
			}
			++cnt ;
		}
	}
	cout << cnt ;
	return 0 ;
}
```

---

## 作者：bitset_iTM (赞：0)

### 思路

先排序，按位置从小到大将奶牛排序。

$R$ 的求法：显然，可以通过每一个健康的奶牛的位置与其他被感染的奶牛的距离的最小值来确定 $R$ 的范围。而题目希望起初感染疾病的奶牛的数量最小，也就是希望在后期被感染的奶牛数越多越好，即 $R$ 在合法范围内越大越好。

知道了 $R$ 之后，模拟即可。如果发现一只被感染的牛，通过比较它与相邻的且也被感染的牛之间的距离和 $R$ 的大小，以此判断该牛是否因后期被传染而感染的。只需统计一开始就已经感染的牛的数量即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

struct cow 
{
    int id, p; // id 是牛的位置，p 代表牛是否感染
};

cow a[1005]; // 用结构体存方便排序

bool cmp(cow x, cow y) // 比较函数，按位置从小到大将奶牛排序
{
    return (x.id < y.id);
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d %d", &a[i].id, &a[i].p);
    sort(a + 1, a + n + 1, cmp); // 排序
    
    int r = 1e9; // 求 R
    for (int i = 1; i <= n; i++)
        if (a[i].p == 0) // 该牛没被传染
        {
            if (i > 1 && a[i - 1].p == 1) 
            	r = min(r, a[i].id - a[i - 1].id);
            if (i < n && a[i + 1].p == 1)
            	r = min(r, a[i + 1].id - a[i].id);
        }
    
    int res = 0; // 统计一开始就已经感染的牛的数量
    for (int i = 1; i <= n; i++)
        if (a[i].p == 1)
        {
            if (a[i - 1].p == 1 && (a[i].id - a[i - 1].id) < r)
                continue ; // 该牛是因后期被传染而感染的
            res++; // 该牛一开始就已经感染的牛的数量
        }
    printf("%d\n", res);
    return 0;
}
```


---

## 作者：Luogu_916767 (赞：0)

[In Luogu](https://www.luogu.com.cn/problem/P9953)

### 题目大意

给出 $n$ 只奶牛的位置，并告诉你每只奶牛是否感染疾病。求最初至少你要多少只奶牛被感染。

### 思路分析

如果发现相邻两只奶牛一只被感染一只没被感染，那么社交距离就小于这两只奶牛的距离。我们只需要求出最小距离，再判断至少多少只牛就好了。

综上

### Code

```cpp
#include<iostream>
#include<algorithm>

using namespace std;

int n;
struct node{
	int a;
	bool b;
}a[1001];
int r=0x3f3f3f3f;

bool cmp(node a,node b){
	return a.a<b.a;
}

int main(){
	cin>>n;
	for(int i = 1; i <= n; i ++ ){
		cin>>a[i].a>>a[i].b;
	}
	sort(a+1,a+n+1,cmp);
	for(int i = 1; i < n; i ++ ){
		if(a[i].b!=a[i+1].b){
			r = min(r,a[i+1].a-a[i].a);
		}
	}
	int ans = 0;
	if(a[1].b)ans ++ ;
	for(int i = 2; i <= n; i ++ ){
		if(a[i].b && a[i-1].b && a[i].a - a[i-1].a >= r){
			ans ++ ;
		}else if(a[i].b && !a[i-1].b){
			ans ++ ;
		}
	}
	cout<<ans;
}

```

---

## 作者：Arson1st (赞：0)

## [P9953 [USACO20OPEN] Social Distancing II B](https://www.luogu.com.cn/problem/P9953) 题解

### 排序+贪心

题目描述很详尽了，甚至样例解释给出了一些暗示。首先，对于给出的 $n$ 头牛，已知它们的坐标和感染情况，显然我们应先按坐标从小到大排序。考虑的相邻两头牛 $i,j$：如果两头牛感染情况相同，我们无法知道任何信息。但是如果一头被感染，另一头未被感染的话，这就隐含了信息：感染半径 $R$ 一定小于这两头牛之间的距离。所以我们先遍历一遍数组，处理出这种情况下最小的距离 $|x_i-x_j|$。这将是整个题目对 $R$ 的唯一限制。

在处理出 $R$ 的上界 $MAX$ 后，再遍历一遍数组。这次处理初始感染的奶牛。注意到由初始奶牛传播形成的被感染连通块中，任一一头奶牛都符合条件（既然 $i$ 能传染 $j$，那 $j$ 也能反过来传染 $i$）。同时每个连通块又必须选取一头奶牛，问题转换为了求出连通块的个数。注意这里对“连通块”的定义：相邻两头牛的距离小于 $MAX$。$O(n)$ 贪心计数连通块即可。

时间复杂度 $O(n\log n)$。

实现细节：注意第一个就被感染的情况和没有牛感染的情况，依据实现可能要特判。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3+10;

int n, mx = 1e9, cnt;
struct node{
	int x, s;
	bool operator < (node a) const{return x < a.x;}
} p[N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++)
		scanf("%d%d", &p[i].x, &p[i].s);
	sort(p+1, p+n+1);
	for (int i = 2; i <= n; i ++)
		if (p[i].s ^ p[i-1].s)
			mx = min(mx, p[i].x - p[i-1].x);
	if (p[1].s) cnt = 1;
	for (int i = 2; i <= n; i ++)
		if (p[i].s && p[i-1].s && p[i].x - p[i-1].x >= mx) cnt ++;
		else if (p[i].s && !p[i-1].s) cnt ++;
	printf("%d", cnt);
}
```



---

