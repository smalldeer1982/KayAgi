# Left-handers, Right-handers and Ambidexters

## 题目描述

你现在在一个运动队里。

这个队里有l 个人只能用他的左手训练（左撇子），另外有r 个人只能用右手训练（右撇子），还有a 个两只手都可以训练的人（既不是左撇子也不是右撇子，但只能用一只手）。

你们的教练决定组建一支队伍，但要保证队伍里用左手训练的人和用右手训练的人一样多。 你的任务是找到这个团队里最多能有多少个人。

## 样例 #1

### 输入

```
1 4 2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5 5 5
```

### 输出

```
14
```

## 样例 #3

### 输入

```
0 2 0
```

### 输出

```
0
```

# 题解

## 作者：Yaixy (赞：12)

# 题意及注意点

- 给出 $3$ 个**整数** $l$，$r$，$a$（均不大于 $100$），可以从 $a$ 中取任意**整数值**加到 $l$ 或 $r$ 中。求 $l$ 和 $r$ 的最大平均值。
- 如果组不成这样的队伍，则输出 $0$。

- 正解是**模拟判断**不用说了吧（
 
# 思路

其实把这个问题归纳一下，只有 $3$ 种情况，分别为：$l$ 小于 $r$，$l$ 大于 $r$，$l$ 等于 $r$。

**_P.S._** 由于这里把 $a$ 算为 $l$ 和 $r$ 的~~后备力量~~，所以不影响判断

 - **情况** $1$：$l$ 小于 $r$。
 
 在这种情况下，应将 $a$ 中整数值补到 $l$ 中，使其尽量与 $r$ 相等。如果此时 $a$ 还有剩余值，则将其平均分配给 $l$ 和 $r$。最后，将 $l$ 和 $r$ 的平均值乘以 $2$ 输出。
 
 - **情况** $2$：$l$ 大于 $r$。
 
 这种情况其实也是**相同的套路**，可以简化为：
 
 1. 将 $a$ 中整数值补到 $r$ 中，使其尽量与 $l$ 相等。
 
 1. 如果此时 $a$ 还有剩余值，则将其平均分配给 $l$ 和 $r$。
 
 1. 将 $l$ 和 $r$ 的平均值乘以 $2$ 输出。
 
 
 - **情况** $3$：$l$ 等于 $r$。
 
 最后一种情况，处理方法最为简单。只需将 $a$ 平分给 $l$ 与 $r$，最后将平均值乘以 $2$（即 ```2*(l+(a/2)) ``` ）
输出即可


------------

# 珂爱的代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,k;
int main()
{
	cin>>a>>b>>c;//a:左撇子 b:右撇子 c:左右手都可以
	k=c;
	if(a<b)
	 {
	 	k-=(b-a);
	 	if(k>=0) cout<<2*(b+(k/2));
	 	else cout<<2*(a+c);
	 }
	if(b<a)
	 {
	 	k-=(a-b);
	 	if(k>=0) cout<<2*(a+(k/2));
	 	else cout<<2*(b+c);
	 }
	if(a==b) cout<<2*(a+(c/2));
	return 0;
}
```
撒花完结awa

---

## 作者：大魔鬼灿灿 (赞：2)

这到题在我看来是一道要列出所有情况的题目，把所有情况都列出来，就能过了

下面讲这到题的所有情况

首先是当左撇子/右撇子和完好的人的数量都是0的时候，这时构不成左右手一样多，直接输出0，结束

然后是当左撇子>右撇子的时候

- 情况1：如果右撇子+完好 == 左撇子，那最多人数就是r+a+l

- 情况2：如果右撇子+完好 <  左撇子，那最多人数就是（r+a）*2 

- 情况3：如果右撇子+完好 >  左撇子，那最多人数就是（l+(r+a-l)/2）*2

然后是当左撇子<右撇子的时候

- 情况1：如果左撇子+完好 == 右撇子，那最多人数就是l+a+r

- 情况2：如果左撇子+完好 <  右撇子，那最多人数就是（l+a）*2 

- 情况3：如果左撇子+完好 >  右撇子，那最多人数就是（r+(l+a-r)/2）*2

最后是当左撇子==右撇子的时候，符合的人数就是（l+a/2）*2

这就是我考虑到的所以情况，如有遗漏，请指出，谢谢

最后上代码

```
#include<iostream>
#include<cstdio>
using namespace std;
int l,r,a;
int main()
{
    scanf("%d%d%d",&l,&r,&a);
    if(l==0&&a==0)
    {
        printf("0");
        return 0;
    }
    if(r==0&&a==0)
    {
        printf("0");
        return 0;
    }
    if(l>r)
    {
        if(r+a==l)
        {
            printf("%d",l*2);
            return 0;
        }
        if(r+a<l)
        {
            printf("%d",(r+a)*2);
            return 0;
        }
        if(r+a>l)
        {
            printf("%d",(l+(r+a-l)/2)*2);
            return 0;
        }
    }
    if(l<r)
    {
        if(l+a==r)
        {
            printf("%d",r*2);
            return 0;
        }
        if(l+a<r)
        {
            printf("%d",(l+a)*2);
            return 0;
        }
        if(l+a>r)
        {
            printf("%d",(r+(l+a-r)/2)*2);
            return 0;
        }
    }
    if(l==r)
    {
        printf("%d",(l+a/2)*2);
    }
    return 0;
}
```

---

## 作者：Eason_AC (赞：1)

## Content
有 $l$ 个人是左撇子，有 $r$ 个人是右撇子，另外有 $a$ 个人既惯用左手又惯用右手。现在想组成一个队伍，要求队伍中惯用左手的人和惯用右手的人相等，试求出团队里面的最大人数。

**数据范围：$0\leqslant l,r,a\leqslant 100$。**
## Solution
假设 $x=\max\{l,r\},y=\min\{l,r\}$，分两种情况讨论：

1. 当 $x-y>a$，那么我们就尽量多的往 $y$ 里面加入惯用两只手的人，那么答案就是 $2(y+a)$。
2. 否则，我们先往 $y$ 里面加人使得人数一样多，然后剩下的再均分进入两组即可（当然，如果剩下的 $a$ 是奇数，那么剩下的那一个直接丢弃），答案就是 $2(x+\left\lfloor\dfrac{a-x+y}{2}\right\rfloor)$，

综上，答案为 $\begin{cases}2(y+a)&x-y>a\\2(x+\left\lfloor\dfrac{a-x+y}{2}\right\rfloor)&x-y\leqslant a\end{cases}$。
## Code
```cpp
int l, r, a, ans;

int main() {
	getint(l), getint(r), getint(a);
	writeint(ans = (abs(l - r) > a) ? (min(l, r) + a) * 2 : max(l, r) * 2 + (a - (max(l, r) - min(l, r))) / 2 * 2);
	return 0;
}
```

---

## 作者：piggymichael (赞：1)

分两种情况来讨论

1, 少的那个加上都行的还是少于多的

这种情况下就是少的那个加上都行的两倍

2，剩下的情况

要让左和右尽量平均就行，仔细想一想，是肯定可以的。

附上代码理解一下：

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int a,b,c;
int main()
{
	cin>>a>>b>>c;
	if(a+c<=b||b+c<=a)
		cout<<(min(a,b)+c)*2<<endl;
	else
		cout<<(a+b+c)/2*2<<endl;
	return 0;//完美结束
}
```
仅供参考，请勿抄袭！

---

## 作者：土川崇贺 (赞：1)

```
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main()
{
    int a,b,c;
    cin>>a>>b>>c;
    while(c>0)
    {
    	if(a<b)
		{
			a++;
		}
		else
		{
			b++;
		}
    	c--;
	}
	cout<<2*min(a,b);
	return 0;//程序结束
}

```

---

## 作者：frankchenfu (赞：1)

我们把这道题目分成两种情况讨论。
## 情况一
如果左撇子和右撇子比例严重失调，也就是说即使所有可以左右手并用的都使用人数较少的那只手（不妨设为左手，也就是$l+a<r$），那么最终的答案一定就是$2(l+a)$，因为惯用右手的人会多出来，最优的方案就是让以左右手并用的都使用左手。
## 情况二
我们假设人数少的还是惯用左手的人，如果不是情况一中提到的，那么就存在$l+a\ge r$。这时，我们先让一部分左右手并用的把人数补齐，使得$l'=r$，那么此时剩下的$a'=a-(r-l)$，这$a'$个人肯定时尽量平均分即可。最后答案就是$2(r+\lfloor\frac{m'}{2}\rfloor)$。由于涉及奇偶性，这里不再对上式化简（其实对于解题来讲已经足够了）。
## 总结与代码
综上所述，当$l\le r$时有$$ans=\begin{cases}2(l+a) , for\ \  l+a<r.\\ 2(r+\lfloor\frac{r-l}{2}\rfloor) , for\ \ l+a\ge r\end{cases}$$

$r<l$时同理，在程序中只需要开始时判断并`swap`一下即可。
```cpp
#include<cstdio>
#include<cstring>

inline void swap(int &x,int &y){
	int t=x;x=y;y=t;
}

int main(){
	int l,r,m;scanf("%d%d%d",&l,&r,&m);
	if(l>r)
		swap(l,r);
	if(l+m<r){
		printf("%d\n",(l+m)<<1);
		return 0;
	}
	m-=(r-l);
	l=r;
	printf("%d\n",(l+m/2)<<1);
	return 0;
}
```

---

## 作者：hanzhang666 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF950A)
## 分析
1. 少的一组加上左右手都行的还是小于多的。  
输出少的加上左右手都行的两倍。
2. 否则让两组**尽量**一样。
## 代码
code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b,c;
	cin>>a>>b>>c;
	int d;
	if(a+c<=b||b+c<=a){
		d=(min(a,b)+c)*2;
	}
	else{
		d=(a+b+c)/2*2;
	}
	cout<<d;
}
```
谢谢。

---

## 作者：TLMPEX (赞：0)

这道题就是普通的模拟，分三种情况讨论，主要思路见代码。

代码：
```c
#include<bits/stdc++.h>
using namespace std;
int main(){
	int right,left,no;//right代表右撇子，left代表左撇子，no代表无撇子 
	cin>>left>>right>>no;
	if(left<right){//如果左撇子的数量比右撇子的数量少 
		if(no+left<=right)cout<<(no+left)*2;//如果无撇子+左撇子比右撇子人还少，则输出两者相加再乘2 
		else if(no+left>right)cout<<right*2+(no+left-right)/2*2;
		//如果两者相加人数比右撇子人数多，则先把左撇子人数与右撇子人数相等，再把剩余无撇子取偶数，三者相加 
	}
	else if(left>right){//与上一情况同理 
		if(no+right<=left)cout<<(no+right)*2;
		else if(no+right>left)cout<<left*2+(no+right-left)/2*2;
	}
	else cout<<left*2+no/2*2;//如果两者相同，则把无撇子取偶数，三者相加 
}
```


---

## 作者：WinterRain208 (赞：0)

CF950A 【Left-handers, Right-handers and Ambidexters】

居然一遍过了，必须写篇题解庆祝一下。

### 题意描述

有两个数$a,b$和一个数$k$，你可以给$a,b$分别加上$c,d$两个数，
$(c+d=k)$，$(c<=0,d<=0)$使得$min(a,b)$的值最大。

输出这个最大值。

### 分析

固定输入，我们无非就讨论几种情况。

$a$等于$b$

$a$小于$b$且$a+k$也小于等于$b$

$a$小于$b$且$a+k$大于$b$

$a$大于$b$且$b+k$也小于等于$a$

$b$小于$a$且$b+k$大于$a$

对于第一种，我们把$k$平均分给$a,b$。

对于第二种，我们把$k$全部给$a$。

对于第三种，我们先把$a$补到与$b$相等，然后均分给$a,b$。

对于第四种，我们把$k$全部给$b$。

对于第五种，我们先把$b$补到与$a$相等，然后均分给$a,b$。

这题就出来了。

### $CODE$

```cpp
#include<bits/stdc++.h>

using namespace std;

int main(){
	int a,b,k;
	cin>>a>>b>>k;
	if(a==b)cout<<(k/2+a)*2;
	if(a>b){
		if(b+k<=a)cout<<b+k+b+k;
		else cout<<(a+(k-(a-b))/2)*2;
	}
	if(a<b){
		if(a+k<=b)cout<<a+k+a+k;
		else cout<<(b+(k-(b-a))/2)*2;
	}
    return 0;
}

```

### 学会分类讨论！

$wtrl$



---

## 作者：2132B (赞：0)

### 思路

题目中是说要将左撇子和右撇子的人数调为一样，而且有一些双面手

既然要使这样的队伍人数尽可能多，那最多就是$(l+r)/2$

$(l$表示左撇子人数，$r$表示右撇子人数，$d$表示双面手人数

但，什么情况下不行呢？

$1.$即使所有双面手都当左撇子或都当右撇子，两种人人数也达不到一样。即$(l-r)>d($默认$l>r$

$2.(l+r)$为奇数时，则只能达到$(l+r-1)/2$

### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
inline void read(int &x)
{
    x=0;int f=1;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
    for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(c^48);
    x*=f;
}//快读
int l,r,d;
int main()
{
    read(l);read(r);read(d);
    if(l>r) swap(l,r);//保证l<r
    if(l+d<r)
    {
        cout<<2*(l+d);
        return 0;
    }
    cout<<(l+d+r)/2*2;//对(l+r)取整
    return 0;
}
```


---

## 作者：sinsop90 (赞：0)

这一道题我们可以分成以下几种情况:

1.$m$-$n$>$k$ 或者 $n$-$m$>$k$,这时候我们就输出($n$和$m$中小的数+$k$)*2

2.如果一个数大于另一个数,但是小的那个数加上$k$就大于等于了大的数

这时候如果小的数加上$k$后是等于大的数,我们就输出大的数乘$2$就行了

但如果是大于,最优方案就是让$k$去补全小的数,让他们相等,再平均分

3.最后一种情况就是本来$n$就和$m$一样,那我们就直接平均分即可

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m,k;
	cin>>n>>m>>k;
	if(m-n>k){//第一种情况
		cout<<(n+k)*2<<endl;
	}
	else if(n-m>k){
		cout<<(m+k)*2<<endl;
	}
	else if(m>n && n+k>=m){//第二种情况
		if(n+k>m){
			k = k-(m-n);
			if(k%2==1){
				cout<<m*2+k-1<<endl;
			}
			else{
				cout<<m*2+k<<endl;
			}
		}
		else{
			cout<<m*2<<endl;
		}
	}
	else if(n>m && m+k>=n){
		if(m+k>n){
			k = k-(n-m);
			if(k%2==1){
				cout<<n*2+k-1<<endl;
			}
			else{
				cout<<n*2+k<<endl;
			}
		}
		else{
			cout<<n*2<<endl;
		}
	}
	else if(n==m){//第三种情况
		if(k%2==1){
			cout<<n*2+k-1<<endl;
		}
		else{
			cout<<n*2+k<<endl;
		}
	}
}
```


---

## 作者：codesonic (赞：0)

数学题用循环做没意思

找公式才好玩

我们把组成训练队的人分成对，为了方便，我称用左手的人为$X$，右手的人为$Y$,皆可以的为$Z$

那么第一种情况就是一个$X$和一个$Y$，这种情况当然是要耗尽$l$和$r$中的一个才最划算

所以这样有$2*min(l,r)$人

接下来拿$l$和$r$配对完其中一种剩下的人去和$Z$配对，当然，如果$l$和$r$相等，那就是0人,另外，也有$Z$不够的情况

这样有$2*(min(max(l,r)-min(l,r),m))$

最后可能会剩下$Z$，那么我们把$Z$相互配对，但是我们要先减去第二种情况耗去的人，那么有$max(m-(max(l,r)-min(l,r)),0)$人，因为这个数可能是奇数，所以我们把它改成这样$max(m-(max(l,r)-min(l,r)),0)/2*2$

那么就读入然后马上输出这三个值加起来，就可以解决这个问题了

代码：
```cpp
#include<iostream>
using namespace std;
int l,r,m;
int main()
{
	cin>>l>>r>>m;
	cout<<2*min(l,r) + 2*(min(max(l,r)-min(l,r),m)) + max(m-(max(l,r)-min(l,r)),0)/2*2;
	return 0;
}
```

---

## 作者：_Qer (赞：0)

看到数据范围时，我脸上泛起一抹邪魅的笑，可以暴力，nice!

精简版暴力计算解法：

可以这样理解

把用左手和右手的人分别列队，再让每个可以双手的人过来，排队，每个都排到左、右手中较短的那个队，最后看能组多少队。

最多的人数是较短那队的人数\*2，这样看（一个 - 代表一个人）：

一队：-------

二队：----------

那么最多的情况就是把一队的人都要了，二队留和一队相同的人数，结果是 (2 \* 一队人数)

```cpp
#include <bits/stdc++.h>
using namespace std;
int l, r, a;
int main() {
    cin >> l >> r >> a;
    while (a) { //把双手的人排好队，每个人进左、右队
    	l < r ? ++l : ++r; //较短的队人数+1
    	--a; //双手队离队一人
	}
	cout << 2 * min(l, r) << endl;
    //最多人数取决于两队中较短的那队
	return 0;
}

```

---

