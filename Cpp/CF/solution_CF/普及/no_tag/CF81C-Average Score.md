# Average Score

## 题目描述

给定一个序列，长度为 $n$ ，在其中取出 $x$ 个数，构成一个数列 $X$ ，剩下的 $y$ 个数构成数列 $Y$ ，请你给出**字典序最小的方案**使得数列 $X$ 内所有数的平均值与数列 $Y$ 内所有数的平均值之和最大，输出这个方案。

## 样例 #1

### 输入

```
5
3 2
4 4 5 4 4
```

### 输出

```
1 1 2 1 2 ```

## 样例 #2

### 输入

```
4
2 2
3 5 4 5
```

### 输出

```
1 1 2 2 ```

## 样例 #3

### 输入

```
6
1 5
4 4 4 5 4 4
```

### 输出

```
2 2 2 1 2 2 ```

# 题解

## 作者：天亮codekiller (赞：2)

# 大致思路:
### part 1 预处理排序：
首先，我们为了方便处理，需要对数据进行排序。

注意题目的信息，由于 $1$ $\le$ $t_{i}$ $\le$ $5$ ，所以不要用 sort ，而要使用计数排序，用 $5$ 个 vector 来存储对应大小的值输入的次序，既节省时间复杂度，又保证了数据的稳定性，使“字典序最小”求解更容易。

### part 2 贪心法求解：
考虑 $x$ $\lt$ $y$ 的情形，不妨设 t 数组已从小到大（小的数值在小的 vector 中，由输入顺序排列）排序好，则两数列的平均值之和（以下简称答案）应该是

$avg$ $($ $t_{1}$ $+$ $t_{2}$ $+$ $...$ $+$ $t_{x}$ $)$ $+$ $avg$ $($ $t_{x+1}$ $+$ $t_{x+2}$ $+$ $...$ $+$ $t_{n}$ $)$ 。

该贪心算法的证明如下：

我们任意交换 $t_{i}$ $($ $1$ $\le$ $i$ $\le$ $x$ $)$ 和 $t_{j}$ $($ $x+1$ $\le$ $j$ $\le$ $n$ $)$ 的位置。

第一种情况，若 $t_{i}$ $=$ $t_{j}$ ，则交换位置后答案值不变，但字典序变大，显然结果变差。

第二种情况，若 $t_{i}$ $\lt$ $t_{j}$ ，记 $\Delta$ $t$ = $t_{j}$ $-$ $t_{i}$，那么交换后，记答案的变化量
 $\Delta$ $ans$ $=$ $\frac{(x-y)}{ab}$ $\Delta$ $t$ （请读者推导，很容易），很明显该值小于 $0$ ，结果变差。

综上所述，该贪心算法正确。

当 $x$ $\gt$ $y$ 时，方法和上文相仿。具体的实现字典序详见代码注释。

当 $x$ $=$ $y$ 时，由于任意变换 $\Delta$ $ans$ 都是 $0$ ，所以只要考虑字典序最小，特判一下，输出 $x$ 个 $1$， $y$ 个 $2$ 就可以了。

奉上 AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int n,x,y;//含义如题意所述 
int a[MAXN];//本题的a数组等价于t数组 
vector<int> num[6];//5个桶，分别记录值为1~5的值 
int color[MAXN];
int main(){
	scanf("%d",&n);
	scanf("%d%d",&x,&y);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		num[a[i]].push_back(i);//把数字的下标压入桶中 
	}
	if(x==y){//特判x=y，直接输出字典序最小 
		for(int i=1;i<=x;++i)printf("1 ");
		for(int i=1;i<=y;++i)printf("2 ");
		return 0;
	}
	if(x<y){
		int numY=0;
		for(int i=1;i<=5;++i){
			int len=num[i].size();
			for(int j=len-1;j>=0;--j)//注意！这里为了使字典序最小，一定要用倒序循环！！！！！ 
				if(numY<y){//统计y数组的元素个数，优先考虑 
					++numY;
					color[num[i][j]]=2;
				}
				else
					color[num[i][j]]=1;
		}
	}
	else{
		int numX=0;
		for(int i=1;i<=5;++i){
			int len=num[i].size();
			for(int j=0;j<len;++j)//注意！这里为了使字典序最小，一定要用正序循环！！！！！ 
				if(numX<x){
					++numX;
					color[num[i][j]]=1;
				}
				else
					color[num[i][j]]=2;
		}
	}
	for(int i=1;i<=n;++i)printf("%d ",color[i]);//输出数字所对应的分组 
	return 0;//Goodbye!
} 
```
希望能对你们的理解有帮助。

---

## 作者：XL4453 (赞：2)

### 解题思路：

要注意一点小细节的贪心。

优先将所有的较大的元素放到容量较小的集合里，如果两个集合大小相等，那么随便放。此种要保证字典序最小。

---
考虑证明：

~~显然。~~

将一个元素放到集合里本质上是在这个元素之前加上一个权值，这个权值等于 $\dfrac{1}{X}$ 或者 $\dfrac{1}{Y}$。那么，将一个值小但是有较大权的元素和一个值大但是有较小权的元素的权换一下一定是优的。

这样就证明完了。

---
### 代码:
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,X,Y;
struct str{
	int x,id,ch;
	bool operator <(const str u)const{
		if(x==u.x)
		{
			if(X<Y)
			return id>u.id;
			else
			return id<u.id;
		}
		return x<u.x;
	}
}num[100005];
bool cmd(str a,str b){
	return a.id<b.id;
}
int main(){
	scanf("%d%d%d",&n,&X,&Y);
	for(int i=1;i<=n;i++){
		scanf("%d",&num[i].x);
		num[i].id=i;
	}
	sort(num+1,num+n+1);
	
	if(X<Y)for(int i=n;i>=n-X+1;i--)num[i].ch=1;
	if(X>Y) for(int i=1;i<=X;i++)num[i].ch=1;
	if(X==Y){
		sort(num+1,num+n+1,cmd);
		for(int i=1;i<=X;i++)
		num[i].ch=1;
	}
	
	sort(num+1,num+n+1,cmd);
	for(int i=1;i<=n;i++)
	if(num[i].ch==1)printf("1 ");
	else printf("2 ");
	printf("\n");
	return 0;
}
```


---

## 作者：Zhuluoan (赞：0)

## 题目简述

给定一个长度为 $n$ 的序列，在其中取出 $x$ 个数，构成一个数列 $a$，剩下的 $y$ 个数构成数列 $b$。

若第 $i$ 个数在数列 $a$ 中，$ans_i$ 等于 $1$，否则等于 $2$，请你给出一种方案使得两数列的平均数之和最大且 $ans$ 的字典序最小.

## 题目分析

我们先考虑 $x=y$ 的情况，在这种情况下，对于第 $i$ 个数字，放入 $a$ 序列或者 $b$ 序列对答案的贡献都是一样的，由于字典序最小的要求，应优先将序号小的数放入 $a$ 序列中.

接下来考虑 $x$ 和 $y$ 不相等的情况，为了方便一些，我们令 $x \lt y$。对于一个数 $w$，它放入 $a$ 序列中对答案的贡献为 $\frac{w}{x}$，$b$ 序列中为 $\frac{w}{y}$，由于 $\frac{w}{y} \lt \frac{w}{x}$，所以它放入 $a$ 序列更优。

接下来，我们便有了贪心策略，将前 $x$ 大的数放入 $a$ 序列，剩余的放入 $b$ 序列，最后考虑一下字典序即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define random(a,b) (rand()%(b-a+1)+a)
const int N=1e5+1;
int n,x,y,T,ans[N];
struct Num
{
	int num,id;
}a[N];
bool cmp1(Num x,Num y)
{
	return x.num==y.num?x.id>y.id:x.num<y.num;
}
bool cmp2(Num x,Num y)
{
	return x.num==y.num?x.id<y.id:x.num<y.num;
}
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>x>>y;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].num;
		a[i].id=i;
	}
	if(x<y)
	{
		sort(a+1,a+1+n,cmp1);
		for(int i=1;i<=y;i++) ans[a[i].id]=2;
		for(int i=y+1;i<=n;i++) ans[a[i].id]=1;
	}
	else if(x==y)
	{
		for(int i=1;i<=x;i++) ans[i]=1;
		for(int i=x+1;i<=n;i++) ans[i]=2;
	}
	else
	{
		sort(a+1,a+1+n,cmp2);
		for(int i=1;i<=x;i++) ans[a[i].id]=1;
		for(int i=x+1;i<=n;i++) ans[a[i].id]=2;
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：CarroT5656 (赞：0)

**题目大意**

给定一个长度为 $n$ 的序列。将它分成序列 $X$ 和 $Y$，使得 $|X|=x,|Y|=y(x+y=n)$。

若一个数在序列 $X$ 中，则记为 $1$；否则为 $2$。求字典序最小的方案使得序列 $X$ 的平均值与序列 $Y$ 的平均值的和最小。

**解法分析**

考虑对于一个数 $a_i$，如果它进入 $X$，贡献为 $\frac{a_i}{x}$；如果它进入 $Y$，贡献则为 $\frac{a_i}{y}$。

容易想到贪心：将较大的数尽可能地放到长度较小的序列中，按元素的值的大小排序即可。

因为还要求字典序最小，所以元素值相同的情况下，要优先考虑将下标较小的元素放入 $X$。

时间复杂度为 $O(n\log n)$，可以通过。

**Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 100005
ll n,x,y,ans[N];
struct nod{ll x,id;}a[N];
bool cmp(nod a,nod b){
	if(a.x!=b.x) return a.x>b.x;
	return x<=y?a.id<b.id:a.id>b.id;
}
int main(){
	scanf("%lld%lld%lld",&n,&x,&y);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i].x),a[i].id=i;
	sort(a+1,a+n+1,cmp);
	if(x<y) for(ll i=1;i<=x;i++) ans[a[i].id]=1;
	else if(x>y) for(ll i=n;i>=n-x+1;i--) ans[a[i].id]=1;
	else for(ll i=1;i<=x;i++) ans[i]=1;
	for(ll i=1;i<=n;i++){
		if(ans[i]==1) printf("1 ");
		else printf("2 ");
	}
	return 0;
}
```

---

