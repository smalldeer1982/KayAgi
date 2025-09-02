# Ithea Plays With Chtholly

## 题目描述

### 题面描述

**这是一道交互题。**

艾瑟雅想要和珂朵莉玩一个游戏来决定厨房晚上的使用权。

游戏进行 $m$ 个回合，艾瑟雅现在有 $n$ 张白纸，每一个回合，艾瑟雅都会给珂朵莉一个 $\in [1,c]$ 的数字，珂朵莉可以选择一个值 $i$，如果第 $i$ 张纸上没有数字，则珂朵莉会把当前的数字写上去，如果有，那么珂朵莉会把原来的数字替换成当前的数字。

珂朵莉需要在至多 $m$ 回合之后，对于所有 $i(1\le i\le n)$，第 $i$ 张纸都写了数字，并且对于编号大于 $1$ 的纸 $i$，写上的数字均 **大于等于** $i-1$ 张纸上写的数字。

## 说明/提示

对于 $100\%$ 的数据，保证 $n,m\ge 2,1\le c\le 1000$，**保证有 $1\le n\cdot\left\lceil\dfrac{c}{2}\right\rceil\le m\le 1000$**。

## 样例 #1

### 输入

```
2 4 4
2
1
3
```

### 输出

```
1
2
2
```

# 题解

## 作者：囧仙 (赞：17)

## 题目大意

有 $n$ 张卡纸，初始为空。现在有 $m$ 次操作，每次给一个 $[1,c]$ 内的正整数 $a_i$ ，要求将其写在某张卡纸上并覆盖原来的内容，使得 $m$ 次操作内，写在卡纸上的数从 $1$ 到 $n$ 非严格单调递增。

保证 $m\ge n\times \left\lceil\dfrac{c}{2}\right\rceil$ 。

## 题解

挺有意思的一道交互题。考虑到截至这篇题解并没有构造方法的证明，这里先给出构造方法，再给出证明。

**构造方法**：如果 $a_i\le \left\lfloor\dfrac{c}{2}\right\rfloor$ ，就从左往右找到第一个大于 $a_i$ 或空的卡纸填入；否则从右往左找到第一个小于 $a_i$ 或空的卡纸填入。

**证明**：先考虑一个小问题：如果有 $m_0$ 次， $c_0$ 种的操作，用这种方法从左往右填，可以保证多少格非严格单调递增？

考虑出现次数最多的操作。显然，所有操作出现次数的平均值为 $\dfrac{m_0}{c_0}$ ，因而最大值必定不小于平均值。也就是说，出现次数最多的操作至少出现了 $\left\lceil\dfrac{m_0}{c_0}\right\rceil$ 次，不妨设这种操作的数字为 $x$ 。考虑这 $m_0$ 次填充，显然小于 $x$ 的操作不会影响到已经形成的非严格单调递增序列，而 $x$ 会忽略所有大于 $x$ 的操作。因而，可以保证这个非严格单调队列的长度不小于 $\left\lceil\dfrac{m_0}{c_0}\right\rceil$ 。

现在我们的构造方案分成了两段。不妨设不超过 $\left\lfloor\dfrac{c}{2}\right\rfloor$ 的操作共有 $t$ 个，则超过的共有 $m-t$ 个。由刚刚证明的结论，两部分拼成的非严格单调递增序列的长度：

$$\left\lceil\dfrac{2\times t}{c}\right\rceil+\left\lceil\dfrac{2\times (m-t)}{c}\right\rceil\ge \frac{2\times m}{c} \ge n$$

于是，我们证明了构造方法是正确的。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
const int MAXN =1e3+3;
int n,m,c,t,A[MAXN],f;
int main(){
    scanf("%d%d%d",&n,&m,&c);
    up(1,m,i){
        scanf("%d",&t); if(t<=c/2){
            up(1,n,j) if(!A[j]||A[j]>t){A[j]=t,f=j;break;}
        } else {
            dn(n,1,j) if(!A[j]||A[j]<t){A[j]=t,f=j;break;}
        }
        printf("%d\n",f);
        fflush(stdout);
    }
    return 0;
}
```

---

## 作者：wwwwwza (赞：10)

### I always love Chtholly!
### 有珂爱的珂朵莉在题目里，怎么能不做！
珂朵莉要给威廉做好吃的，我们要帮助珂朵莉跟艾瑟雅比赛，赢得厨房的使用权。  
~~威廉真的好幸福。~~  

（上方纯粹瞎扯淡，下面正文开始）

---
## 简化题意
珂朵莉有 $n$ 张空白的纸和 $m$ 个不超过 $c$ 的数。对于每一个数，可以将其写在一张白纸上或替换某一张纸上的一个数，输出这张纸的编号。珂朵莉必须保持在纸上的数构成一个非降序排列。

## 构造方式
- 当 $x \leq \left \lfloor \frac{c}{2}  \right \rfloor $ 时，从左往右便利到 $a_i$，满足 $a_i=0$ 或 $a_i>x$。   
- 当 $x > \left \lfloor \frac{c}{2}  \right \rfloor $ 时，从右往左便利到 $a_i$，满足 $a_i=0$ 或 $a_i<x$。

## 证明结论
设在这 $m$ 个数中出现次数最多的数为 $x$，那么 $x$ 最少会出现 $\left \lceil \frac{m}{c}  \right \rceil $ 次。   

- 若一个数 $y$ 满足 $x=y$，排列的长度最少为$\left \lceil \frac{m}{c}  \right \rceil $。  
- 若一个数 $y$ 满足 $x>y$，当 $y$ 在 $x$ 后出现时，其将毫无意义，所以排列的长度最少为$\left \lceil \frac{m}{c}  \right \rceil $。  
- 若一个数 $y$ 满足 $x<y$，当 $y$ 在 $x$ 前出现时，其将毫无意义，所以排列的长度最少为$\left \lceil \frac{m}{c}  \right \rceil $。  

综合得，无论如何单调不降序列的长度至少有$\left \lceil \frac{m}{c}  \right \rceil $。

---
对于原来的构造方式，假设有 $k$ 个 $x \leq \left \lfloor \frac{c}{2}  \right \rfloor$，则有 $m-k$ 个 $x > \left \lfloor \frac{c}{2}  \right \rfloor$。

两段序列的单调不降序列的长度至少为 $\left \lceil \frac{2k}{c}  \right \rceil$ 和 $\left \lceil \frac{2(m-k)}{c}  \right \rceil$。

将两段序列拼接而成的长度为 $\left \lceil \frac{2k}{c}  \right \rceil + \left \lceil \frac{2(m-k)}{c}  \right \rceil \ge \frac{2m}{c} \ge n$。

得证。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,c,x,a[1005];
signed main(){
	cin >>n>>m>>c;
	while(m--){
		cin >>x;
		if(x<=c/2){
			for(int i=1;i<=n;i++){
				if(x<a[i]||a[i]==0){
					a[i]=x;
					cout <<i<<endl;
					break;
				}
			}
		}else{
			for(int i=n;i>=1;i--){
				if(x>a[i]||a[i]==0){
					a[i]=x;
					cout <<i<<endl;
					break;
				}
			}
		}
	}
	return 0;
}

```

---

## 作者：Laser_Crystal (赞：5)

### 有可爱的珂朵莉在题目里面，再难也要做啊对不对qwq
~~什么？你问我珂朵莉是什么~~

哈哈哈我先放图哈哈哈

![](https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1581079263156&di=89e2822ed32dfa903d0c2a64a775ba5c&imgtype=0&src=http%3A%2F%2Fi2.hdslb.com%2Fbfs%2Farchive%2Fd6be2df0543aaed6566714f51d5ddd489009ce8d.jpg)

![](https://ss0.bdstatic.com/70cFuHSh_Q1YnxGkpoWK1HF6hhy/it/u=1181238268,1362642324&fm=26&gp=0.jpg)

![](https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1581079271797&di=2e983451580367aff6789252e2941ab4&imgtype=0&src=http%3A%2F%2Fi2.hdslb.com%2Fbfs%2Farchive%2Ff4f6243cce5c61159b23297fad3ff9aeada5b4d7.jpg)

~~好好好不皮了，切入正题~~

那么问题来了，交互提是个什么鬼？

我也是看了[帖子](https://www.luogu.com.cn/discuss/show/48737)之后才懂的

那么就姑且抛开交互题这个~~奇葩的东西~~不说，先考虑如果这不是交互题该怎么做

自己推导方案推了好久才做出来……

易知，

当$2x<=c$的时候，就从前往后找，找到第一个大于这个数的位置补上或者找到第一个空位置填上

当$2x>c$的时候，就从后往前找，找到第一个小于这个数的位置补上或者找到第一个空位置填上

这么一通瞎搞之后你就赢了，因为**珂朵莉是很可爱的吖**对吧

那么问题又回到了交互提上面来了，

交互提的确很有意思，但是fflush（stdout） in C/C++又是个什么东东啊……

我自己的英语不好，就瞎猜了个意思，就是每行输出后，要刷新一下，加一条语句fflush（stdout)；（大概如此吧）

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long t[1005]={0};//其实int也能过，就是被卡long long卡怕了qwq
int main()
{
  long long n,m,c,x;
  cin>>n>>m>>c;
  while(m--)
  {
    cin>>x;
    if(x*2<=c)
    {
      for(int i=1; i<=n; i++)
        if(t[i]>x||!t[i]) { t[i]=x; cout<<i<<endl; break; }
    }
    else
    {
      for(int i=n; i>0; i--)
        if(t[i]<x||!t[i]) { t[i]=x; cout<<i<<endl; break; }
    }
    fflush(stdout);
  }
  return 0;
}
```
对没错就是这样做的

希望洛谷能早日出几道交互题并加入有关交互题的ILE这种状态

---

## 作者：添哥 (赞：4)

**我永远稀饭珂朵莉！QWQ**

为了让珂朵莉能给威廉做好吃的，我们要跟艾瑟雅比赛赢得厨房的使用权。

>为了抓住一个人的胃而独占厨房是不好的哦(bushi
>
>——艾瑟雅

（以上全属扯淡）


------------
交互题。

分两种情况考虑，即 $x\le\frac{c}{2} $ 和 $x>\frac{c}{2} $ 。

- 当 $x\le\frac{c}{2} $ ：正着遍历，把第一个大于（**想一想，为什么不是大于等于？**） $x$ 的或空的位置替换/放上。

- 当 $x>\frac{c}{2} $ ：反着遍历，把第一个小于 $x$ 的或空的位置替换/放上。

放完你就赢了。

## code
```cpp
#include<iostream>
using namespace std;
int a[1001];
int main()
{
    int n,m,c;
	cin>>n>>m>>c;
	while(m--)
	{
	    int x;
		cin>>x;
		if(x<=c/2)
		{
			for(int i=1;i<=n;i++)//正着遍历
			{
				if(x<a[i]||a[i]==0)
				{
					a[i]=x;
					cout<<i<<endl;
					break;//记得退出循环
				}
			}
		}
		else
		{
			for(int i=n;i;i--)//反着遍历
			{
				if(x>a[i]||a[i]==0)
				{
					a[i]=x;
					cout<<i<<endl;
					break;
				}
			}
		}
		cout<<endl;//这同样可以清空缓存区哦
	}
	return 0;
}
```
~~话说这题真的有紫吗~~

---

## 作者：damage (赞：1)

# 好希望你咕早早出交互题啊！

---

## 题解

我们并不知道它的下一个数会是多少，而且还要写满所有纸（不然你全部写在第一张纸上），所以这就有麻烦了

幸好可爱的$\footnotesize{\color{skyblue}{\text{珂朵莉}}}$让我们可以替换数字（不然$n\lt{m}$怎么办），这样就好办多了

仔细阅读英文原题面，发现在输入格式的第一行有这么一个东西：

> $1\leq{n\cdot{\lceil{\frac{c}{2}}\rceil}}\leq{m}\leq{1000}$

由此受到启发，我们根据数与$\frac{c}{2}$的大小来判断放置方法，这样就行了。

很容易想到方案（假设每次给的数为$x$）：

1. 当$x\leq{\frac{c}{2}}$，则**正**着遍历纸，第一个找到的有**大**于这个数的或空位置则替换/放上

2. 反之当$x\gt{\frac{c}{2}}$，则**反**着遍历纸，第一个找到的有**小**于这个数的或空位置则替换/放上

可以不用记录已经放了多少纸，因为你所有数都要放一遍（即放$m$次）

放完就立刻结束了（然后你会发现你赢了）

---

## 代码

```cpp
#include<stdio.h>
int n,m,c,x,paper[1010]; //x是每次收到的数
int main()
{
	scanf("%d%d%d",&n,&m,&c);
	while(m--)
	{
		scanf("%d",&x);
		if((x<<1)<=c) //情况1，x<<1表示x*2，即x*2<=c，基本等同于x<=c/2
		{
			for(register int i=1;i<=n;++i) //正着遍历
			{
				if(paper[i]>x||!paper[i]) //找到第一个符合要求的
				{
					paper[i]=x; //替换/放置该数
					printf("%d\n",i); //输出
					break; //放完就退出遍历
				}
			}
		}
		else //反之情况2
		{
			for(register int i=n;i;--i)
			{
				if(paper[i]<x||!paper[i]) //反着遍历
				{
					paper[i]=x; //替换/放置该数
					printf("%d\n",i); //输出
					break; //放完就退出遍历
				}
			}
		}
		fflush(stdout); //记得刷新输出缓冲区
	}
	return 0;
}
```

---


## 说明

关于本篇涉及到的位运算的讲解（其实就一种）

```x<<1```表示```x*2```，其实$x$<<$i$ $=x\times{2^{i}}$。

---

## 作者：Skyjoy (赞：1)

# 这题紫题太高了吧

我们只用比较 $x$ 和与 $c/2$ 的大小关系来选择遍历顺序就可以了

不过题目有要求，每一次输出后都要加一句 fflush(stdout) 加上就好了

**注意：在输入 c 后，每一次输入都不能用快读，不然会神奇地 TLE （亲身尝试过）**

# CODE:

```cpp
#include<bits/stdc++.h>
#define ll long long
ll n,m,c,x,k[1010];
ll read(){
	ll x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x;
}
int main(){
	n=read(),m=read(),c=read();
	while(m--){
		scanf("%d",&x);
		if(x*2<=c){
			for(int i=1;i<=n;i++){
				if(k[i]>x||!k[i]){
					k[i]=x;
					printf("%d\n",i);
					break;
				}
			}
		}
		else{
			for(int i=n;i;i--){
				if(k[i]<x||!k[i]){
					k[i]=x;
					printf("%d\n",i);
					break;
				}
			}
		}
		fflush(stdout);
	}
	return 0;
}
```
~~终于找到机会水题解了qwq~~

---

## 作者：Nygglatho (赞：0)

### Sol 1

对于每次给定的一个数，如果大于等于前面所有的数则加入到最后，否则替换尽量后面的数。

这样的最坏情况是：

$[c,c-1,c-2,\cdots,1,c,c-1,c-2,\cdots,1,\cdots]$。

会需要 $nc$ 次，无法通过，考虑优化。

### Sol 2

初始 $l=1,r=n$。

令 $a_0=0,a_{n+1}=\infty$，容易发现这样不影响答案。

对于每次给定的一个数 $s$，分成两种情况：

1. $\le \dfrac{c}{2}$：

如果 $s\ge s_l$，则 $l\gets l+1,a_l\gets s,p_i\gets l$。

否则找到一个数 $t$，使得 $t\le l_i$ 且 $a_t\ge s,a_{t-1}\le s$，然后 $a_t\gets s,p_i\gets l$。

2. $> \dfrac{c}{2}$：

如果 $s< s_r$，则 $r\gets r-1,a_r\gets s,p_i\gets r$。

否则找到一个数 $t$，使得 $t\ge r_i$ 且 $a_t\le s,a_{t+1}\le s$，然后 $a_t\gets s,p_i\gets l$。

容易发现，这样最坏情况是 $[\dfrac{c}{2},\dfrac{c}{2}-1,\dfrac{c}{2}-2,\cdots,1,\dfrac{c}{2},\cdots,1,\cdots,\dfrac{c}{2}+1,\cdots,c,\dfrac{c}{2}+1,\cdots,c,\cdots]$。

这样每个 $i$，$a_i$ 至多修改 $\dfrac{c}{2}$ 次，总共 $n\cdot \dfrac{c}{2}$ 次，次数在 $m$ 以下。

代码较其他题解较为繁琐。

```cpp
void Putting(ll p) {
	a[0] = -inf; a[n + 1] = inf;//初始设为 -inf，防止判断问题。
	if (p > (c >> 1)) {
		F(i, 1, n)
			if (a[i] == 0)a[i] = -inf;
		D(i, n, 1) {
			if (p >= a[i - 1] && p <= a[i + 1] && a[i] == -inf) {
				a[i] = p;
				cout << i << endl;
				F(j, 1, n)
					if (a[j] == -inf) a[j] = 0;
				return ;
			}
		}// 当时写的时候没有记录 l, r，而是暴力判断是否可以放在 a[l] 后面，赋值 -inf 是为了暴力判断，下面同理
		F(i, 1, n) {
			if (p >= a[i - 1] && p <= a[i + 1]) {
				a[i] = p;
				cout << i << endl;
				F(j, 1, n)
					if (a[j] == -inf) a[j] = 0;
				return ;
			}
		}// 找到 t
	} else {
		F(i, 1, n)
			if (a[i] == 0)a[i] = inf;
		F(i, 1, n) {
			if (p >= a[i - 1] && p <= a[i + 1] && a[i] == inf) {
				a[i] = p;
				cout << i << endl;
				F(j, 1, n)
					if (a[j] == inf) a[j] = 0;
				return ;
			}
		}
		D(i, n, 1) {
			if (p >= a[i - 1] && p <= a[i + 1]) {
				a[i] = p;
				cout << i << endl;
				F(j, 1, n)
					if (a[j] == inf) a[j] = 0;
				return ;
			}
		}
	}
}

int main() {
	cin >> n >> m >> c;
	
	F(i, 1, m) {
		ll p; cin >> p; Putting(p);int flg = 1;
		F(i, 1, n - 1) {
			if (a[i] == 0 || a[i] > a[i + 1]) flg = 0;
		}
		if (flg == 1) break;
	}
}
```

---

## 作者：JWRuixi (赞：0)

I always love Chtholly!

- 题意

给定 $n$ 张 sheet，和常数 $c$，初始为空，进行 $m$ 此操作：

每次程序给你一个数 $x$，$1 \le x \le c$，将 $x$ 写入一张空 sheet 或替换某一张 sheet 上的数，若某一刻你的 $n$ 张 sheet 均非空，且其上的数单调不降，则 Chtholly wins，你现在要帮助 Chtholly 获得胜利。

- 分析

其实我们只需要维护数列单调不降的性质不变即可，我们每次找到第一个严格大于 $x$ 的位置，将其替换为 $x$。

接下来证明这样做是对的：

对于每一个数，替换操作后其必定至少见少 $1$，也就是说对于一张纸，最多进行 $c$ 次操作，所以对于一个长度为 $len$ 的序列需要至多 $len \times c$ 次操作。

那就好做了，题目告诉我们满足 $n \times \lceil\frac{c}{2}\rceil \le m$，所以我们就维护两个序列就可以了！

若输入的数 $x$ 小于等于 $\lfloor\frac{c}{2}\rfloor$ 那就从左到右找到第一个严格大于它的数（或为空），替换；反之从后往前找到第一个严格小于它的数（或为空），替换。

- code

```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;

const int maxn(1005);
int n, m, c, a[maxn], x;

int main () {
	scanf("%d%d%d", &n, &m, &c);
	const int lim = c / 2;
	for (int i = 1; i <= m; i++) {
		scanf("%d", &x);
		if (x <= lim) {
			for (int j = 1; j <= n; j++) if (!a[j] || x < a[j]) {
				a[j] = x;
				printf("%d\n", j);
				fflush(stdout);
				break;
			}
		} else {
			for (int j = n; j; j--) if (!a[j] || a[j] < x) {
				a[j] = x;
				printf("%d\n", j);
				fflush(stdout);
				break;
			}
		}
	}
}
```

---

## 作者：wzm2007 (赞：0)

    我们只需根据数与c/2的大小来判断遍历的顺序即可
    代码:

------------

    #include<bits/stdc++.h>
    using namespace std;
    int p[1010];
    int main()
    {
        int n,m,c,x;      //x为每次收到的数
        cin>>n>>m>>c;
        while(m--)
        {
            cin>>x;       //读入
            if((x<<1)<=c)        //等同于x<=c/2
            {
                for(int i=1;i<=n;++i)      //正着遍历

                    if(p[i]>x||!p[i])
                    {
                        p[i]=x;
                        cout<<i<<endl;      //输出
                        break;    //退出
                    }
            }
            else   //情况相反
            {
                for(int i=n;i;--i)
                    if(p[i]<x||!p[i])
                    {
                        p[i]=x;
                        cout<<i<<endl;
                        break;
                    }
            }
            fflush(stdout);    //刷新
        }
        return 0;
    }

---

