# [ABC150C] Count Order

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc150/tasks/abc150_c

大きさ $ N $ の順列 ($ (1,~2,~...,~N) $ を並び替えてできる数列) $ P,~Q $ があります。

大きさ $ N $ の順列は $ N! $ 通り考えられます。このうち、$ P $ が辞書順で $ a $ 番目に小さく、$ Q $ が辞書順で $ b $ 番目に小さいとして、$ |a\ -\ b| $ を求めてください。

## 说明/提示

### 注記

$ 2 $ つの数列 $ X,~Y $ について、ある整数 $ k $ が存在して $ X_i\ =\ Y_i~(1\ \leq\ i\ <\ k) $ かつ $ X_k\ <\ Y_k $ が成り立つとき、$ X $ は $ Y $ より辞書順で小さいと定義されます。

### 制約

- $ 2\ \leq\ N\ \leq\ 8 $
- $ P,~Q $ は大きさ $ N $ の順列である。
- 入力は全て整数である。

### Sample Explanation 1

大きさ $ 3 $ の順列は、$ (1,~2,~3) $、$ (1,~3,~2) $、$ (2,~1,~3) $、$ (2,~3,~1) $、$ (3,~1,~2) $、$ (3,~2,~1) $ の $ 6 $ 個あります。このうち $ (1,~3,~2) $ は辞書順で $ 2 $ 番目、$ (3,~1,~2) $ は辞書順で $ 5 $ 番目なので、答えは $ |2\ -\ 5|\ =\ 3 $ です。

## 样例 #1

### 输入

```
3
1 3 2
3 1 2```

### 输出

```
3```

## 样例 #2

### 输入

```
8
7 3 5 4 2 1 6 8
3 8 2 5 4 6 7 1```

### 输出

```
17517```

## 样例 #3

### 输入

```
3
1 2 3
1 2 3```

### 输出

```
0```

# 题解

## 作者：peppaking8 (赞：2)

$$\huge{\texttt{Description}}$$
### 1.$O(n!)$ 想法
首先，$N\le 8$，所以说标准做法就是一个一个枚举。

你当然可以用 ```C++``` 的 ```STL``` 中的 ```next_permutation()``` 函数来完成，这里我们讲不用这个函数的方法。

假设已经有了一个序列：$1,3,4,2,5,6$。我们要求它的后继。

第一步，看最后一位。如果最后一位比倒数第二位大，就直接交换；

否则，就看倒数第二位，直到出现一位 $x$ 比前一位大的时候，就将 $x-1$ 位到 $n$ 位**排序**即可。

到此为止题目已经解决。但是，还有没有更好的解法？如果 $N\le 10^4$ 呢？
### 2.$O(n^2)$ 想法
我们定义数组 ```la[i],lb[i]```，**分别表示 $a_i$ 在 $a_i-a_n$ 中的排名和 $b_i$ 在 $b_i-b_n$ 的排名**。比如 $a=\{1,3,2,4,5,6\}$，那么 $la=\{ 1,2,1,1,1,1\}$。

这一个处理是 $O(n^2)$ 的效率，也是程序的瓶颈。

下一步，从小到大遍历 $1-n$，更新答案，加上 $(la_i-lb_i)\times (n-i)!$。也就是说，我们更新了**前 $i$ 位和 $a,b$ 数组相同，后 $n-i$ 位都是 $a$ 数组的数的编号之差**。

如果我们预处理阶乘，那么复杂度就是 $O(n)$。
### 3.$O(n\log n)$ 想法
注意到我们每次处理 $la,lb$ 的时候都会重复枚举，这样肯定耽误时间。

我们可以理解为，$la_i=a_i-\text{a[1]到a[i-1]中比a[i]小的个数}$。

这样答案就非常显然了：用**树状数组**维护。

~~或者线段树也行，不过我懒得写~~。

这样的话就能保证每次更新的时候是 $\log n$ 的效率，常数的增加没有过多影响。
$$\huge{\texttt{Code}}$$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int n;
int a[N],b[N];
int t[N];
int cal[N];
int ans=0;
//树状数组基本三件套
int lowbit(int x){
	return x&(-x);
}
void add(int pos){
	for(int i=pos;i<=n;i+=lowbit(i))
		t[i]++;
}
int query(int pos){
	int ret=0;
	for(int i=pos;i>=1;i-=lowbit(i))
		ret+=t[i];
	return ret;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		add(a[i]);
		int prev=query(a[i]-1);
		a[i]-=prev;//我们将la[]代替a[]，处理方式上面说了
	}
	memset(t,0,sizeof(t));
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		add(b[i]);
		int prev=query(b[i]-1);
		b[i]-=prev;//处理lb[]数组，同la[]
	}
    //预处理cal数组，其中cal[i]=i!
	cal[0]=1;
	for(int i=1;i<=n;i++) cal[i]=cal[i-1]*i;
    //按照解答中所说进行答案更新
	for(int i=1;i<=n;i++){
		ans+=(a[i]-b[i])*cal[n-i];
	}
    //注意到b数组的序号可能多于a数组，所以要取绝对值
	printf("%d\n",abs(ans));
	exit(0);
}
```
写一篇题解不容易，看完记得点个赞哦~

---

## 作者：Karry5307 (赞：1)

### 题意

给定两个长度为 $n$ 的排列 $P,Q$，求两个排列的排名之差。

$\texttt{Data Range:}1\leq n\leq 8$

### 题解

讲一下 Cantor Expansion。

首先很明显有一个 $O(n!)$ 的做法就是暴力枚举所有排列然后逐一 check，代码又短又好写又容易 AC，是比赛时的不二之选。然而赛后的话我们要寻求一些更优的做法。

对于长度为 $n$ 的排列 $\pi$ 来说，它在所有排列中的排名为

$$\text{ord}\ \pi=\sum\limits_{i=1}^{n}\left(\sum\limits_{j=i+1}^{n}[\pi_j<\pi_i]\right)(n-i)!$$

也即对于每一个数来说，统计一下它后面有多少个比他小，然后乘上一个阶乘加起来就好了，这里给个证明。

考虑数学归纳法，假设结论在 $n-1$ 时成立。对于长度为 $n$ 的排列 $\pi$ 来说，有一个很明显的结论：设 $\pi^{\prime}_i=\pi_{i+1}$，那么 $\text{ord}\ \pi=(\pi_1-1)(n-1)!+\text{ord}\ \pi^{\prime}$，也即将第一个数和后面的分开算再合并。

于是我们可以将排列的第一个数拿出来，算出 $\pi_2,\cdots,\pi_n$ 的排名再加上 $\pi_1$ 的贡献即可。

注意到 $\pi_1-1$ 刚好为比 $\pi_1$ 小的数的个数，对于后面那一段我们可以按照大小重新标号成长度为 $n-1$ 的排列，直接利用结论可以知道它一样在 $n$ 的地方成立。

对于 $n=1$ 来说这个结论明显成立，于是没了。

这个时候可以 $O(n^2)$ 计算 $\text{ord}\ \pi$ 了，但是还不够。

注意到我们可以从后往前考虑每一个数，开一个权值树状数组就可以统计比这个数小的数有多少个，于是复杂度变成 $O(n\log n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
ll n,ru,rv,flg,cur;
ll u[MAXN],v[MAXN],p[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	n=read();
	for(register int i=1;i<=n;i++)
	{
		u[i]=read(),p[i]=i;
	}
	for(register int i=1;i<=n;i++)
	{
		v[i]=read();
	}
	do
	{
		flg=1,cur++;
		for(register int i=1;i<=n;i++)
		{
			if(p[i]!=u[i])
			{
				flg=0;
				break;
			}
		}
		flg?ru=cur:1,flg=1;
		for(register int i=1;i<=n;i++)
		{
			if(p[i]!=v[i])
			{
				flg=0;
				break;
			}
		}
		flg?rv=cur:1;
	}
	while(next_permutation(p+1,p+n+1));
	printf("%d\n",abs(ru-rv));
}
```

---

## 作者：DengDuck (赞：0)

本题十分简单，甚至不需要康拓展开

利用 `next_permutation` 函数求出两个数组的排名再相减即可

时间复杂度为 $O(n\times n!)$ ，因为 `next_permutation` 是 $O(n)$ 的，全排列最多有 $n!$ 个

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[105],b[105],c[105],ans,i,p,q;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        c[i]=i;
    }
    for(int i=1;i<=n;i++)
    {
        cin>>b[i];
    }
    i=1;
    do
    {
        bool flag=true;
        for(int j=1;j<=n;j++)
        {
            if(a[j]!=c[j])
            {
                flag=false;
                break;
            }
        }
        if(flag)
        {
            p=i;
        }
        flag=true;
        for(int j=1;j<=n;j++)
        {
            if(b[j]!=c[j])
            {
                flag=false;
                break;
            }
        }
        if(flag)
        {
            q=i;
        }
        if(p!=0&&q!=0)break;
        i++;
    }while(next_permutation(c+1,c+n+1));
    cout<<abs(p-q)<<endl;
}
```

---

## 作者：_huangyicheng_ (赞：0)

## 一个很暴力的写法

观察可以发现，这题的 $N$ 很小，最大只有8，因此 $O(n!)$ 的暴力是能过的。

思路：

枚举 $N$ 的全排列，找出 $Q$ 是第几个排列， $P$ 是第几个排列，最后输出它们的差就可以了，很简单。

问题来了，如何枚举全排列呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/n6sr6l7g.png)

好吧有点模糊。

然后就可以开心的用dfs写出代码了。

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int n,a[10],b[10],path[10],cnt,l,r;
bool vis[10];//用来记录数是否填过 
bool check1();//提前声明函数 
bool check2();
void dfs(int pos){//当前填第pos位置的数 
	if(pos>n){//边界 
		cnt++;
		//当前构造的这个排列是否与我们知道的序列相等，如果相等，说明这个排列是第cnt个 
		if(check1()) l=cnt;//找第一个序列 
		if(check2()) r=cnt;//找第二个序列 
		return ;
	}
	for(int i=1;i<=n;i++){//从小到大遍历每个数，判断是否可以填 
		if(!vis[i]){//i这个数未填过 
			vis[i]=true;
			path[pos]=i;//当前pos位置填数，填的数为i
			dfs(pos+1);//去填下一个位置 
			vis[i]=false;//回溯状态 
		}
	}
	return ;
}
bool check1(){//判断函数，就是判断两个序列是否相等 
	for(int i=1;i<=n;i++){
		if(a[i]!=path[i]) return false;
	}
	return true;
}
bool check2(){
	for(int i=1;i<=n;i++){
		if(b[i]!=path[i]) return false;
	}
	return true;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	dfs(1);//从第1个数开始填 
	cout<<abs(l-r);//输出它们的绝对值 
	return 0;
}
```

---

## 作者：codemap (赞：0)

这道题题意很简洁,做法也很简单:

用STL自带的next_permutation枚举全排列,

每次暴力比较这个数组和原数组,

最后找到排列的排名后直接求绝对值即可

上代码
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int a[10],b[10],s[9]={0,1,2,3,4,5,6,7,8};//s为全排列数组
int main()
{
	int n,i,t=0,a1,a2;//t为计数器,a1,a2分别为a,b的排名
	bool f1,f2;//两个flag
	cin>>n;
	for(i=1;i<=n;i++)
		cin>>a[i];
	for(i=1;i<=n;i++)
		cin>>b[i];
	do//next_permutation do-while循环
	{
		t++;//计数器++
		f1=0;//将第一个flag归0
		for(i=1;i<=n;i++)
			if(s[i]!=a[i])//只要有一位不一样
				f1=1;//将flag改为1
		if(!f1)//如果flag仍然是0
			a1=t;//找到a的排名
		f2=0;//同上
		for(i=1;i<=n;i++)
			if(s[i]!=b[i])
				f2=1;
		if(!f2)
			a2=t;
	}while(next_permutation(s+1,s+n+1));
	cout<<abs(a1-a2);//输出绝对值
	return 0;//结束
}
```
# 请勿抄袭

---

