# New Year and Rating

## 题目描述

Every Codeforces user has rating, described with one integer, possibly negative or zero. Users are divided into two divisions. The first division is for users with rating $ 1900 $ or higher. Those with rating $ 1899 $ or lower belong to the second division. In every contest, according to one's performance, his or her rating changes by some value, possibly negative or zero.

Limak competed in $ n $ contests in the year 2016. He remembers that in the $ i $ -th contest he competed in the division $ d_{i} $ (i.e. he belonged to this division just before the start of this contest) and his rating changed by $ c_{i} $ just after the contest. Note that negative $ c_{i} $ denotes the loss of rating.

What is the maximum possible rating Limak can have right now, after all $ n $ contests? If his rating may be arbitrarily big, print "Infinity". If there is no scenario matching the given information, print "Impossible".

## 说明/提示

In the first sample, the following scenario matches all information Limak remembers and has maximum possible final rating:

- Limak has rating $ 1901 $ and belongs to the division $ 1 $ in the first contest. His rating decreases by $ 7 $ .
- With rating $ 1894 $ Limak is in the division $ 2 $ . His rating increases by $ 5 $ .
- Limak has rating $ 1899 $ and is still in the division $ 2 $ . In the last contest of the year he gets $ +8 $ and ends the year with rating $ 1907 $ .

In the second sample, it's impossible that Limak is in the division $ 1 $ , his rating increases by $ 57 $ and after that Limak is in the division $ 2 $ in the second contest.

## 样例 #1

### 输入

```
3
-7 1
5 2
8 2
```

### 输出

```
1907
```

## 样例 #2

### 输入

```
2
57 1
22 2
```

### 输出

```
Impossible
```

## 样例 #3

### 输入

```
1
-5 1
```

### 输出

```
Infinity
```

## 样例 #4

### 输入

```
4
27 2
13 1
-50 1
8 2
```

### 输出

```
1897
```

# 题解

## 作者：Loi_Anina (赞：6)

这个题打眼一看，最大值……或许是二分？

~~然后开始写……~~
 
仔细观察后我们发现，这个题其实可以**模拟**，而且是个特别简单的模拟~~（然而我考试写WA了）~~

# 模拟当然要直接上代码啦
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
int n;
int c,d;
int minn,maxn;//最小值和最大值，作为可选择（且确定）的区间
int main()
{
	maxn=300000000;//无穷大 
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&c,&d);
		if(d==1&&maxn<1900||d==2&&minn>1899)
        //第一种情况是要进行div1但当前最大值不符合（不能参赛）
        //第二种情况是要进行div2但当前最小值不符合（不能参赛）
        //读题可得要求每局比赛一定参加
        //因此不可能啊喂！
       ｛
			printf("Impossible");
			return 0;	
		} 
		if(d==1&&minn<1900) minn=1900;//要是最小值不确定或超过可参加的界限
		if(d==2&&maxn>1899) maxn=1899;//要是最大值还不确定或超过可参加的界限
		if(minn!=0) minn+=c;
        //0代表负无穷（数据会为负因此实际上或许应该更小，但0也能过）
		if(maxn!=300000000) maxn+=c;//正负无穷加不加就没有意义了
//		cout<<minn<<" "<<maxn<<endl;
	}
	if(maxn==300000000) printf("Infinity");//还是正无穷说明上边界不确定
	else printf("%d",maxn);
	return 0;
}
```

总而言之其实不是个很弯弯绕绕的模拟，翻译题面就好了~~（加的注释够多应该很好理解啦）~~

---

## 作者：到底几只鱼呢 (赞：4)

[CF750C New Year and Rating](https://www.luogu.com.cn/problem/CF750C)

## 做法：二分

考虑枚举开始时的 $rating$，$check$ 的时候判断:

- 是否为合法解

- 枚举答案是否需要调大/调小

二分上下界为 $[-inf,+inf]$ ,注意特判无解和无穷的情况。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace HMFS{
	const int maxn=2e5+10;
	struct node {
		int change,tag;
	}a[maxn];
	int n,ans=-1e9-1;
	int check(int mid) {
		for(int i=1;i<=n;i++) {
			if(a[i].tag==1) {
				if(mid<1900) return 1;
			}
			if(a[i].tag==2) {
				if(mid>=1900) return 0;
			}
			mid+=a[i].change;
		}
		return 2;
	}
	void work() {
		cin>>n;
		for(int i=1;i<=n;i++) {
			cin>>a[i].change>>a[i].tag;
		}
		int l=-1e9,r=1e9;
		while(l<=r) {
			int mid=(l+r)/2;
			int bj=check(mid);
			if(bj==2) ans=max(ans,mid),l=mid+1;
			else if(bj==1) l=mid+1;
			else r=mid-1;
		}
		if(ans==-1e9-1)cout<<"Impossible\n",exit(0);
		if(ans==1e9)cout<<"Infinity\n",exit(0);
		for(int i=1;i<=n;i++) {
			ans+=a[i].change;
		}
		cout<<ans;
	}
}
int main() {
	return HMFS::work(),0;
}
```

---

## 作者：caibet (赞：2)

### 题意：

[传送门](https://www.luogu.com.cn/problem/CF750C)

### 解法：

想法跟题解区有点不一样。

设最开始的 rating 为 $x$，则可以把给的 $n$ 条信息看成 $n$ 个不等式。

对于样例：

```
3
-7 1
5 2
8 2
```

可列不等式组：

$\begin{cases}
x\geq1900\\
x-7<1900\\
x-7+5<1900\end{cases}$

即

$\begin{cases}
x\geq1900\\
x<1907\\
x<1902\end{cases}$

接着，根据不等式的解法，大于等于号取最大值，小于号取最小值，最终解得：$1900\le x<1902$。

最初的 rating 最大为 $1901$，因而最终最大 rating 为 $1901-7+5+8=1907$。

类比这个算法，我们对于每次比赛判断 $x$ 的上下界，最后把所有的 rating changes 加起来，加上 $x$ 即为答案。

特别地，如果上界没有更新过（即 $114514\le x$ 情况）则可以为无限 rating，下界大于上界（即类似 $1919810\le x<114514$ 情况）即无解。

中间的过程可以前缀和优化一下。

```cpp
namespace{
	const int lim=2e5+2;
	int n,c[lim],d[lim],l=-inf,r=inf;
	void work(){
		n=read();
		F(i,1,<=n) c[i]=readn()+c[i-1],d[i]=read();//先读入数据，顺便前缀和
		if(d[1]==1) l=1900;//第 1 场比赛的 div 决定了最初 rating 的上界/下界
		else r=1899;
		F(i,1,<n){
			if(d[i+1]==1){//判断下次比赛的 div
				l=max(l,1900-c[i]);//下界往上
			}else{
				r=min(r,1899-c[i]);//上界往下
			}
		}
		if(l>r) puts("Impossible");
		else if(r==inf) puts("Infinity");
		else put("%d",r+c[n]);
	}
}
```

---

## 作者：frankchenfu (赞：2)

  我们考虑，题目已经给出了所有rating的变化，那么要求最后我们rating的大小，其实就是求rating初始值的大小。接着我们考虑怎么求出初始时rating可能的最大值。

  当一次比赛结束之后，如果rating在区域1（$\ge 1900$），那么我们就可以重新划定下界可能在的范围（最少就是1900-之前加的rating）；同理可以划定上界所在的范围。这样，当所有操作结束之后我们就可以求出一个rating可能的范围了。注意初始下界为$-inf$，上界为$inf$。
  
  那么我们求下界有什么用？
  
  如果我们不求下界的话，那么有可能出现`Impossible`的情况就判断不了了。这种情况就是我们判断出来的下界大于上界，区间不存在。
  
  `Infinity`？
  
  就是我们发现如果上界一直都是$inf$，那么最后就是输出`Infinity`。
  
  最后一般情况就是输出(上界+变化量)。注意，不要忘记加上变化量。
  
  代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=200010;
const int INF=0x7fffffff;
int state[MAXN][2];
int lans=-INF,rans=INF;

int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&state[i][0],&state[i][1]);
	
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		if(state[i][1]==1)
			lans=max(lans,1900-sum);
		else
			rans=min(rans,1899-sum);
		sum+=state[i][0];
	}
	
	if(lans>rans)
		puts("Impossible");
	else
		if(rans==INF)
			puts("Infinity");
		else
			printf("%d\n",rans+sum);
	return 0;
}
```

---

## 作者：逢秋商独季 (赞：1)

拿第一个样例，假设一开始分数为0，分数线为x（即当分数线为1900时原始分数为1900-x），则0>=x，-7<x,-2<x，显然为了达到要求，问题为求x的最小值（因为分数线越低说明原始分数越高）。那问题就很简单了：对于所有d=1的情况比较得出x的上界,对于所有d=2的情况比较得出x的下界。若上界<=下界则该区间不存在输出“Impossible”，若无下界（说明原始分数无上界）则输出“Infinity”，否则x取下界值。最后将分数线移回1900即可。
```cpp
#include<iostream>
using namespace std;
int n;
int height,a,b;
int min1=20000001,max2=-20000001;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a>>b;
        if(b==1)min1=min(min1,height);
        else max2=max(max2,height);
        height+=a;
    }
    if(max2==-20000001)cout<<"Infinity";
    else
    if(min1<=max2)cout<<"Impossible";
    else
    {
        height-=max2;//取下界
        height+=1899;//将分数线移回1900
        cout<<height;
    }
    return 0;
}
```


---

## 作者：JustinXiaoJunyang (赞：0)

思路分析：

这道题有人会以为是二分，但模拟就可以了。

那这样分类讨论：

- div.1 不能参赛，也就是最大值不符合

- div.2 不能参赛，也就是最小值不符合。

我们就设最大值和最小值（可选择的区间）。如果两个 div 都不能参加，那么就输出 `Impossible` 就可以了。区间每次都要更新，以免越界。

最后注意每场比赛都要打！

参考代码：

这个是 [AC 记录](https://www.luogu.com.cn/record/81432945)，按照题意模拟即可。

---

## 作者：封禁用户 (赞：0)

## 这道题可以用模拟来做

### [传送门](https://www.luogu.com.cn/problem/CF750C)

通过题目翻译可知：输入  $n$  场比赛的 rating 变化值 $ c_{i} $ 和 $ d_{i} $。

而其中 $ d_{i} $ 有两种可能：

$1.d_{i} =1$ 即比赛为 div1，rating $≥1900$。

$2.d_{i} =2$ 及比赛为 div2，rating $<1900$。

但是通过分析样例 $2$ 可知，当 rating $<1900$ 却参加 div1 时，或者当 rating $>1900$ 却参加 div2 时，输出 Impossible。

分析样例 $3$ 可知，当最大值一直为开始设定的数从未变过的话（也就是最大值无上限），输出  Infinity。

## AC Code
```
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
using namespace std;
void tio(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
}
ll maxn=0x7fffffff,minn=0;
int main(){
	tio();
	ll n;
	cin>>n;
	for(ll i=1;i<=n;i++){
		ll c,d;
		cin>>c>>d;
		if((d==1 && maxn<1900) || (d==2 && minn>1899)){
        // 这里是当要参加Div1 or Div 2时，rating最大值到不了或者
        // rating最小值超了。
			cout<<"Impossible";
			return 0;
		}
		if(d==1 && minn<1900){
			minn=1900;//已经能打Div1了，所以最小值最低就是1900。
		}
		if(d==2 && maxn>1899){
			maxn=1899;//打的是Div2，所以最大值最大只能是1899。
		}
		if(minn!=0){
			minn+=c;
		}
      		//处理完后把比赛加的rating加上
		if(maxn!=0x7fffffff){
			maxn+=c;
		}
	}
	if(maxn==0x7fffffff){
		cout<<"Infinity";//无上限时输出
	}
	else{
		cout<<maxn;//输出最大值
	}
	return 0;
}
/* by aw_aw*/
```

---

