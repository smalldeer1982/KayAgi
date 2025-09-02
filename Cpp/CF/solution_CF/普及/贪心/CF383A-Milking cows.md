# Milking cows

## 题目描述

Iahub在农场帮助他的祖父，今天他必须挤牛奶。农场里有$n$只牛左成一排，从左到右编号$1$到$n$。每只牛不是面向左边就是面向右边。当Iahub挤某一只牛的牛奶时，所有看得到这当前只牛的牛都会因为受到惊吓而损失一单位量的牛奶。面向左边的牛可以看到它左边的所有牛（不包括自己），面向右边的牛可以看到它右边的所有牛（不包括自己）。被惊吓过的牛可以再次被惊吓。被挤过奶的牛不会再被惊吓。我们假定每一头牛可以生产无限量的牛奶。

Iahub可以决定挤牛奶的顺序，但他必须每头牛都要挤。Iahub想损失尽可能少的牛奶。请输出最少的牛奶损失量。

## 说明/提示

在第一个样例中,Iahub按照下面的顺序可以使得牛奶损失最少：$3,4,2,1$。当他挤牛$3$时，牛$4$会损失$1$单位牛奶。在此之后，没有牛奶损失。

Translated by @Imakf

## 样例 #1

### 输入

```
4
0 0 1 0
```

### 输出

```
1```

## 样例 #2

### 输入

```
5
1 0 1 0 1
```

### 输出

```
3```

# 题解

## 作者：花里心爱 (赞：10)

### CF383A 题解
相信大家题意都能看懂吧。

这道题我们可以使用贪心的解法。

由题意可知，如果我们把向左看的牛从右到左去挤奶，这样面朝左的牛就不会失去牛奶。这样，向右看的牛$i$丢失的牛奶量为$i$右边所有向左看奶牛的总和。

另一种情况，如果我们把向右看的牛从左到右去挤奶，这样面朝右的牛就不会失去牛奶。这样，向左看的牛$i$丢失的牛奶量为$i$左边所有向右看奶牛的总和。

不难证明，上述贪心算法是正确的。实际上，上述两种方案的结果是一样的，因为若第一种情况中有向左看的$a$惊吓了向右看的$b$，则第二种情况中就会有向右看的$b$惊吓了向左看的$a$。

所以，上述两种情况是等价的，只需算出任一种情况就行。

下面上代码：
```cpp
#include<cstdio>
#include<iostream>
using namespace std;     //不解释的开头
int n,t;
long long cnt,sum;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%d",&t);
        if(t)++cnt;      //前缀和思想线性求出向左看的牛前面向右看牛的数量
        else sum+=cnt;   //如果i向左看，更新答案
    }
    cout<<sum<<endl;     //long long类型用cout或%I64d输出
    return 0;
}
```

---

## 作者：Buried_Dream (赞：6)

## 题意:

你是一名农场主，你很贪，你想获得最多的牛奶，但是当你挤一头牛的奶的时候，能看到这头牛的牛很害怕，然后他就缩奶。

## 思路：

考虑贪心，也就是让最少的牛缩奶。

比如一头脸朝右的牛，与他反向的能看见他，那就让同向的尽量少，于是就从左往右挤，这样就看不见他了。

考虑从脸朝左的奶牛也一样。

## AC code：

```cpp
/*
work by: TLE_Automation
Time: O(轻轻松松过)
knowledge: 垃圾算法
*/
#include<bits/stdc++.h>
#define int long long
#define Min(x, y)  (x > y ? y : x);
#define Max(x, y)  (x > y ? x : y);
#define orz cout << "szt lps fjh AK IOI";
using namespace std;

const int maxn = 3e6;
const int MAXN = 3e3;
const double down = 0.996;
const double limit = 1e-10;
const int mod = 1e9 + 7;

inline int read() {
	int s = 0, w = 1;
	char ch = getchar();
	while (!isdigit(ch)) {if(ch == '-') {w = -1;}ch = getchar();}
	while (isdigit(ch)) {s = (s << 1) + (s << 3) + (ch ^ 48);ch = getchar();}
	return s * w;
}

inline void print(int x) {
	if (x < 0 ) putchar('-'), x = -x;
	if (x > 9 ) print(x / 10);
	putchar(x % 10 + '0');
}
int js = 0;
int ans;
signed main() {
	int n = read();
	for(int i = 1; i <= n; i++) {
		int x = read(); 
		if(x) ++js;
		else ans += js;
	}print(ans);
	return 0;
}


```

---

## 作者：巫妖王 (赞：4)

$\color{purple}\text{这题竟然是黑题，是福利题吗？}$

**~~过了之后就可以拿来装13~~**

$\color{blue}\text{切入正题，这题使用贪心的解法}$ 

**如题，如果我们把向左看的牛从右到左去挤奶，这样面朝左的牛就不会失去牛奶。这样，向右看的牛 *i* 丢失的牛奶量为 *i* 右边所有向左看奶牛的总和,也就是说，此时，我们只需统计每头向右看的牛前面向左看牛的数量，然后加起来输出**

$\color{red}\text{是不是有些难理解，我们看样例1}$

如果我们把向左看的牛从右到左去挤奶，第1,2,4头牛就不会因为看到3号奶牛而被惊吓（看到3号时已被挤奶或无法看到3号奶牛）；

**一样的如果我们把向右看的牛从左到右去挤奶，这样面朝右的牛就不会失去牛奶。这样，向左看的牛 *i* 丢失的牛奶量为 *i* 左边所有向右看奶牛的总和，也就是说，此时，我们只需统计每头向左看的牛前面向右看牛的数量，然后加起来输出**

$\color{Aquamarine}\text{不难发现实际上，上述两种方案的结果是一样的，}$
$\color{Aquamarine}\text{因为若第一种情况中有向左看的 a 惊吓了向右看的 b ，}$
$\color{Aquamarine}\text{则第二种情况中就会有向右看的 b惊吓了向左看的 a} $

$\color{Gold}\text{如果还是难理解的话，看代码吧}$

下面上代码：

```pascal
var n,t,i:longint;
    cnt,sum:int64;
begin
 readln(n);
  for i:=1 to n do
  begin
   read(t);
   if t=1 then inc(cnt)//求出向左看的牛前面向右看牛的数量
   else sum:=sum+cnt;//累加
  end;
 writeln(sum);//输出
end.
```
$\color{brown}\text{是不是很简单（大佬勿喷）}$

~~写得太差赶紧逃~~

---

## 作者：Wf_yjqd (赞：2)

最水黄题？我又来水题解了。

------------

显然，一定要造成损失从大到小的顺序挤损失之和最小。

那考虑由于看的方向固定，从一侧往另一侧顺序挤一定使每次损失单调不增，总会有一种是最小的。（具体要看朝一个方向的牛的数量）

考虑从左往右，从右往左各模拟一次，求最小值即可。

------------

没人看的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=4e5;
ll n,a[maxn],dp1,dp2,cnt;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)
        a[i]?cnt++:dp1+=cnt;
    cnt=0;
    for(int i=n;i>=1;i--)
        a[i]^1?cnt++:dp2+=cnt;
    printf("%lld",min(dp1,dp2));
    return 0;
}
//dT&小l
```


---

## 作者：Qerucy (赞：1)

~~话说这些奶牛有那么亿点点任性啊~~

压缩题意：当一头奶牛被挤奶的时候，能看到这头奶牛的其它奶牛就会减少出奶量，问挤完所有奶牛之后最少损失是多少。

那么就在挤一头奶牛之前让这头奶牛减少出奶量的次数变少。

对于面朝左的牛，我们考虑从右往左去挤奶，这样面朝左的牛就不会减少出奶量，那么只需要统计面朝右的奶牛所减少出奶量的和就行了。

从左往右挤奶，统计面朝左的奶牛所减少出奶量的和也可以，思路相同。

求每头牛减少的出奶量，我们可以用前缀和来求。

代码：

```cpp
#include<cstdio>

using namespace std;

#define int long long//注意开long long

int n;
int x;
int sum;
int ans;

signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&x);
		if(x) sum++;//前缀和
		else ans+=sum;
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：违规用户名U56916 (赞：0)

不要怀疑这道题为什么紫，他不是代码难，而是思路难（~~假装很难~~）

首先这道题运用贪心思路，这一点应该明确；

那么，怎么贪？客官，莫急，往下看。

首先如果一个方向的奶牛已经全部被挤奶，那么对于剩下的另一方向（以面向左为例）的奶牛，只需要每次找到那个最右边的，挤它，那么这个方向所有的奶牛对答案的贡献就是
# **0**

多棒啊

所以我们就要先挤完同一方向的奶牛，然后按以上方向去挤另一方向

那么这同一方向如何去挤(⊙o⊙)？（以面左为例）

假设甲、乙两牛还没确定顺序，其他均已确定，且甲在乙左边

那么如果我们先挤甲，再挤乙，甲就会算在乙的答案，但先挤乙，再挤甲，乙就不会算在甲的答案里

而对于除甲乙外的牛无论甲乙顺序如何，都不会影响挤甲乙对答案的贡献

所以，对面向左的牛，我们先挤靠右的

贪心完成

仔细想想这就是统计了一下所有面左的牛的左边有多少面右的牛

AC代码

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long sum,ans;
int n,x;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		if(x) sum++;
		else ans+=sum;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Instudy (赞：0)

奇了怪了前缀和有了归并排序有了竟然还没有树状数组（~~当然线段树也行~~）

这不就是个逆序对裸题吗？直接 $ ctrl+c+v $完事……

当然，如果这么写肯定被打回来没商量，所以：我来解释一下树状数组求逆序对。

什么是逆序对：

对于给定的一段正整数序列，逆序对就是序列中 $ a_i>a_j $
  且 $i<j $ 的有序对。
  
按照序列从左到右将数据的值对应的位置的数加一，代表又有一个数出现。因此，在循环到第$ i $ 项时，前 $ i-1 $ 项已经加入到树状数组内了 , 树状数组内比 $ a_i  $	  大的都会与$ a_i $	 构成逆序对，因为它们一定出现的更早，所以答案就是当前位置减去前缀和。


代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+10;
int a[maxn];
int n;
long long ans;
int c[maxn];
int p[maxn];
bool cmp(int x,int y)
{
	return a[x]<a[y];
}
int lowbit(int x)
{
	return x&(-x);
}
long long sum(int x)
{
	long long res=0;
	while(x>0)
	{
		res+=c[x];
		x-=lowbit(x);
	}
	return res;
}
void update(int x,int v)
{
	while(x<=n)
	{
		c[x]+=v;
		x+=lowbit(x);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	 {
	 scanf("%d",&a[i]);
	 p[i]=i;
}
   sort(p+1,p+n+1,cmp);
   for(int i=1; i<=n; i++) a[p[i]]=i;
	for(int i=n;i>=1;i--)
	{
		 ans+=sum(a[i]-1);
    update(a[i],1);
	}
	printf("%lld",ans);
	return 0;
}
```


---

