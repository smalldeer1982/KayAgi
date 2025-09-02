# station

## 题目描述

你需要规划一个城市的公交路线。

总共有 $n$ 条路线和 $m$ 个车站，编号均从 $1$ 开始。

你的主要任务是，规划每一条路线应该经过哪些车站。换言之，你要任意选择一个车站的子集，让这条路线经过这个子集中的所有车站。

定义两条路线是**关联**的，当且仅当它们经过了同一个车站，也就是它们的经过车站集合有交。

一个路线方案必须满足如下限制：

1. 一条线路不可能只通过一个车站，所以**每条线路至少要经过两个车站**；

2. 一个车站的运载能力是有限的，所以**一个车站最多只能被三条线路经过**。

3. 为了保证交通顺畅，对于任意两条不同线路 $i, j(i \not = j)$，都存在第三条线路 $k (k \not = i, k \not = j)$，使得 $k$ 与 $i, j$ 均**关联**。

现给定 $n$，请求出一个最小的 $m$ 和具体规划方案。

## 说明/提示

#### 「样例 1 解释」

如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/shh1iy56.png)

首先易知其满足题目描述中所给定的一、二条件。下面考虑三条件。

先考虑 $1, 2, 4$ 号线，可以发现这三条线路构成了一个三角形，任意两个线路均有剩下的一条线路与它们**关联**；

再对 $3$ 号线与 $1, 2, 4$ 号线分别考虑，容易验证满足对于任意 $x \in \{1, 2, 4\}$，均有另一条线路 $y \in \{1, 2, 4\}, y \not = x$ 与 $3, x$ 同时**关联**，满足题目条件。

---

#### 「Special Judge 说明与评分细则」

**请认真阅读输出格式**。

如果你的输出出现了如下情况，将会被判为 $0$ 分：

- 输出格式不符。如没有正确换行，输出了一些奇奇怪怪的字符，未输出车站个数等。
- 某一条线路经过了相同的车站，或者有某一个车站的编号不在 $[1, m]$ 内。
- 没有满足题目描述中所给定的三条限制。
- 输出文件大小过大或者是 $m$ 过大。如果你的 $m$ 大于 $10 ^6$ 将直接判为 $0$ 分。输出文件过大将导致 TLE 或 OLE，建议将输出文件大小控制在 25Mb 以内。

在没有被判为 $0$ 分的基础上，将会根据你输出的 $m$ 的大小进行判分。

每个测试点评测时会有 $10$ 个评测参数 $w _1, w _2, \cdots, w _{10}$，若你输出的 $m$ 小于等于其中 $k$ 个参数，那么你将得到该测试点 $k \times 10\%$ 的分数。

这 $10$ 个参数是对外不可见的，也即你的程序在运行时无法获知这些评测参数。

---

#### 「数据范围」

**本题采用捆绑测试**。你在某个 subtask 的得分为在**该 subtask 的所有测试点中的最小得分**。

- Subtask 1(20 points)：$n \le 10$。此处我们保证 $10$ 个评分参数均为 $10 ^6$。
- Subtask 2(40 points)：$n \le 200$。
- Subtask 3(40 points)：无特殊限制。

对于所有数据，均满足 $3 \le n \le 4 \times 10 ^3$，且 $ans + 5 \le w _1 \le w _2 \le \cdots \le w _{10} = 10 ^6$，其中 $ans$ 表示标准答案。

请注意此处的 $w _{10} = 10^6$ 的条件。

## 样例 #1

### 输入

```
4```

### 输出

```
4
2 1 2
2 2 4
2 2 3
3 1 3 4```

# 题解

## 作者：vectorwyx (赞：19)

## upd on 2020/10/14
[被hack](https://www.luogu.com.cn/discuss/show/266044)后修正了疏漏

------------

一道相当有思维含量的构造题，~~让我找回了昔日做毒瘤数学题的感觉~~

这道题的计分方式其实就在提醒我们：不要一上来就想找到最优方案，先把一种合法的构造方案找出来把部分分拿到手再去考虑优化。

如果你也像我一样在草稿纸上写写画画了好久，就会发现第2条限制和第3条限制是很难同时满足的，至少我随缘画了十几次都没试出来（。这个时候就要**有意识地先满足一个限制，再不断向另一个限制靠拢**。我们先来看一下限制3：
>为了保证交通顺畅，对于任意两条不同线路 $i,j(i \not = j)$，都存在第三条线路 $k (k \not = i, k \not = j)$，使得 $k$ 与 $i,j$ 均关联。

换句话说，就是任选两条线路，一定有另一条线路“横跨”在它们中间，但是要注意，这条“横跨”的线路与我们所选出的两条线路中的任意一条的组合也要满足限制3。这卡死了很多看起来可行的方案，因为如果你为了让这条“横跨”的线路与原本的两条线路之间的组合也满足限制3而**不断“引入”新线路**，一定会走向穷途末路，毕竟**每“引入”一条新线路就会多出好多组新的限制要满足**╮(╯▽╰)╭。

说这么多，其实就是想揭示一个道理：我们的方案应该是由多个“元结构”拼接而成的。每个“元结构”自身就是一个合法的方案（尽管线路条数不一定等于 $n$，但一定满足那三条限制），通过某种方式拼接起来后得到的整体也是一个合法的方案。比如说以下两个就是“元结构”（图有点粗糙，还请谅解QAQ）：

![这个](https://cdn.luogu.com.cn/upload/image_hosting/4jevaa5z.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
![这个](https://cdn.luogu.com.cn/upload/image_hosting/afb45bty.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

第一个显然不如第二个优秀。而对于第二个，我们很容易就能找到一种拼接方式：

![](https://cdn.luogu.com.cn/upload/image_hosting/6hsb3qwn.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

（什么？你问我元结构中间那条线路哪去了？当然是被用来保证限制3了qwq）

这种方案简明易懂，尤其要注意的是下面那条最长的线路，**这条线路的存在使得限制3一定被满足**。这种方案的点数为 $n-1$。如果 $n$ 为偶数的话需要再添加一条经过上面那些点的线路，因此点数为 $n-2$。能拿到76分。

但是很显然这不是最优的，因为上面那一行点还没有达到承载的极限（每个点只有2条线路经过）。如果每个点能承载3条线路的话，点数将减小很多，因此就有了下面的构造方案（这实际上也是一个“元结构”）qwq：

![](https://cdn.luogu.com.cn/upload/image_hosting/jpg508z1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这种方案里每5个点组成的元结构中有6条线路，我们只需要大概  $\frac{5}{6}(n-1)$ 个点，交上去，满分！


------------
代码如下（码字不易，希望能给个赞QAQ）：
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;
inline int read(){ int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){ if(ch=='-') fh=-1; ch=getchar(); } while(isdigit(ch)){ x=(x<<1)+(x<<3)+ch-'0'; ch=getchar(); } return x*fh; }

vector<int> g;//g用来存储最下面那条线路 

int main(){
	int n=read(),k=(n-1)/6,ans=k*5,t=(n-1)%6,a,b,c,d,e;
	if(n==3){//注意当n等于3时最下面那条线路只会有1个车站，就会WA掉，特判一下就好了 
		puts("2\n2 1 2\n2 1 2\n2 1 2");
		return 0;
	} 
	//由于n-1不一定被6整除，因此在处理完前k个元结构后需要对剩下的t条线路进行特殊处理。 
	switch(t){
		case 1:ans+=2;break;
		case 2:ans+=2;break;
		case 3:ans+=3;break;
		case 4:ans+=4;break;
		case 5:ans+=5;break;	
	}
	cout<<ans<<endl;
	fo(i,1,k){
		a=(i-1)*5+1,b=a+1,c=b+1,d=c+1,e=d+1;//a,b,c,d,e是元结构里的五个顶点 
		printf("2 %d %d\n",a,d);
		printf("2 %d %d\n",a,d);
		printf("2 %d %d\n",b,d);
		printf("2 %d %d\n",b,e);
		printf("2 %d %d\n",c,e);
		g.push_back(a);g.push_back(b);g.push_back(c);
		if(t==1&&i==k){ 
			printf("2 %d %d\n2 %d %d\n",e+1,e+2,e+1,e+2);g.push_back(e+1);
			goto H;
		}
		printf("2 %d %d\n",c,e);
	}
	a=k*5+1,b=a+1,c=b+1,d=c+1,e=d+1;
	switch(t){
		//case 1:printf("2 %d %d\n",a,b);g.push_back(a);break;
		case 2:printf("2 %d %d\n2 %d %d\n",a,b,a,b);g.push_back(a);break;
		case 3:printf("2 %d %d\n2 %d %d\n2 %d %d\n",a,b,a,b,b,c);g.push_back(a);g.push_back(c);break;
		case 4:printf("2 %d %d\n2 %d %d\n2 %d %d\n2 %d %d\n",a,b,a,b,c,d,c,d);g.push_back(a);g.push_back(c);break;
		case 5:printf("2 %d %d\n2 %d %d\n2 %d %d\n2 %d %d\n2 %d %d\n",a,b,a,b,b,c,c,d,d,e);g.push_back(a);g.push_back(c);g.push_back(e);break;	
	}
	H:
	int s=g.size();
	cout<<s<<" ";
	fo(i,0,s-1) printf("%d ",g[i]); 
	return 0;
}

```



---

## 作者：Binah (赞：13)

大概是目前唯一一篇带证明的题解吧

趁着没有题解赶紧来一篇

以下 $sum(f(i))$ 均为 $\Sigma_{i=1}^nf(i)$

因为 $n<=20$ 没有点数限制,以下证明均为 $n>=21$ 的情况

首先,题意里面的"路径"是很丑陋的,我们尝试简化一下题意

我们尝试把每一条路径对应成一个点,两个路径相连则把他们连上一条边

显然最优情况下每个车站都经过三条路径

则:对于每一个车站,他被路径 $a,b,c$ 经过,则相当于把 $ab,bc,ca$ 连上

现在考虑题目的第三条限制:每两个点都有一个点和他们都相连

记三元组 $(a,b,c)$ 为一组使 $a,b$ 均和 $c$ 相连的 $a,b,c$

其中 $(a,b,c)=(x,y,z)$ 等价于无序对 $(a,b)=(x,y)$ 且 $c=z$

由于对每个不同的 $(a,b)$,都存在 $c$ 与 $a,b$ 相连

则我们有: $s>=C_{n}^2$

对于一个点 $i$,记它的度数为 $p[i]$ (算上重边)

则使得 $c=i$ 的 $(a,b,c)$ 有 $C_{p[i]}^2$ 个

所以:$sum(C_{p[i]}^2))>=C_{n}^2$

又每一个点 $i$ 被至少两个车站经过,所以 $p[i]>=4$

由简单的数学运算(或者使用人类的直觉),可以知道:
使得 $sum(p[i])$ 最小且 $sum(C_{p[i]}^2)>=C_{n}^2$ 的p满足:
 $p[1]$ 很大,$p[2]=...=p[n]=4$

由 $C_{p[1]}^2+6n-6>=C(n,2)$

$p[1]=n-6$ 时,上式恒成立,$p[1]=n-8$ 时,上式在 $n>=15$ 时不成立,所以$sum(p[i])>=5n-12=4*(n-1)+n-8$

又因为每个 $m$ 连了三条边,即:$sum(p[i])=6m$ (每条边从两端各计算一次)

所以 $m>=sum(p[i])/6>=(5n-12)/6$,即标答 $ans>=5n/6-2$

接下来给出一组 $m$ 接近 $5n/6$ 的构造:

把车站分成两组:

组 $1$:第 $k$ 个车站连接 $1,2k,2k+1(k<=n/2),2k=n$ 时将 $2k+1$ 视为 $2$

组 $2$:第 $k$ 个车站连接 $3k-2,3k-1,3k(k<=(n+2)/3),3k-x>n$ 时,视为 $3k-n-x$

此时至多出现 $(n/2+1)+(n/3+1)=5n/6+2$ 个车站
由 $ans>=5n/6-2$ 得: $w1>=5n/6+3>5n/6+2$

所以,我们确保了这个程序完美满足要求了

最后,放代码了
```cpp

#include <bits/stdc++.h>
//#include <windows.h>
//#define int long long
using namespace std;
#define N 4001
vector<int>mp[N];
int a[N],b[N],c[N];
int top=0;
int n;
int main()
{
    scanf("%d",&n);
    for(int i=2; i<=n; i+=2)//处理组1的车站
    {
        top++;
        a[top]=1;
        b[top]=i;
        c[top]=i+1;
        if(i==n)
        {
            c[top]=2;
        }
    }
    for(int i=2; i<=n; i+=3)//处理组2的车站
    {
        top++;
        a[top]=i;
        b[top]=i+1;
        if(i+1>=n+1)
        {
            b[top]-=n;
        }
        c[top]=i+2;
        if(i+2>=n+1)
        {
            c[top]-=n;
        }
    }
    for(int i=1; i<=top; i++)//把车站信息存进路径
    {
        mp[a[i]].push_back(i);
        mp[b[i]].push_back(i);
        mp[c[i]].push_back(i);
    }
    printf("%d\n",top);
    for(int i=1; i<=n; i++)
    {
        printf("%d ",mp[i].size());
        for(int j=0; j<mp[i].size(); j++)
        {
            printf("%d ",mp[i][j]);
        }
        printf("\n");
    }
    return 0;
}
```
修正:34行敲成了$i+2>=n+2$,感谢@sxw2018的指正

---

## 作者：zhoukangyang (赞：4)

[来蒟蒻无人问津的博客园里来看/kel](https://www.cnblogs.com/zkyJuruo/p/13775857.html)

## 蒟蒻语
还是蒟蒻太菜了，这场 div1 竟然一题都没做出来/kk/kk/kk
## 蒟蒻解
首先我们把每 **5** 个点分为一组。然后分组结果大概是这样子：

![station.png](https://i.loli.net/2020/10/06/ciWenZIEavzY8sN.png)

可以看到首先下面需要有一条边来让整张图有一条支撑的路径。然后每一组内都有 6 条边。

那么这样子的图是可行的。原因：

1. 对于每条线路，都至少经过两个车站，满足第一个条件。
1. 对于所有点，经过他的路径数不超过 $3$，满足第二个条件。
1. 对于任意两条边， 都与最下面的那条边有交点，满足第三个条件。

那么可以先将边的数量-1， 然后再按模 6 的余数分类，单独处理 (细节看代码)。

---

小蒟蒻太菜了，不会证明这为什么这样点数是最小的。

## 蒟蒻码
```cpp
#include<bits/stdc++.h>
#define re register
#define L(i, j, k) for(re int i = j; i <= k; i++) 
#define R(i, j, k) for(re int i = j; i >= k; i--) 
#define db double 
#define ll long long
using namespace std;
int n, m, tot;
void print(int x) { // 把每一个组内的点输出 
	L(i, 1, x) {
		L(j, 1, 3) printf("2 %d %d\n", (i - 1) * 5 + 1, (i - 1) * 5 + 2 + j);
		L(j, 1, 3) printf("2 %d %d\n", (i - 1) * 5 + 2, (i - 1) * 5 + 2 + j);
	}
} 
int main() {
    scanf("%d", &n), n--; // 先在最下面放一条线 
    int ds = n / 6 * 5;
    if(n % 6 == 0) {
 	   	printf("%d\n", ds);
		printf("%d ", ds / 5 * 3);
		L(i, 1, ds) if(i % 5 == 0 || i % 5 == 3 || i % 5 == 4) printf("%d ", i) // 输出这一个组内元素 
		puts("");
 	   	print(ds / 5);
	} 
	else if(n % 6 == 1) {
		ds -= 5;  // 特别注意一下，为了让剩下的那条边有依靠，这里是把一个组再拆开来qwq 
 	   	printf("%d\n", ds + 7);
		printf("%d ", ds / 5 * 3 + 4);
		L(i, 1, ds) if(i % 5 == 0 || i % 5 == 3 || i % 5 == 4) printf("%d ", i);
		printf("%d %d %d %d\n", ds + 1, ds + 2, ds + 3, ds + 4);
	   	print(ds / 5);
	   	printf("2 %d %d\n", ds + 5, ds + 1); // 处理不属于那一组一组的那些边 
 	   	printf("2 %d %d\n", ds + 5, ds + 2);
 	   	printf("2 %d %d\n", ds + 5, ds + 3);
 	   	printf("2 %d %d\n", ds + 6, ds + 2);
 	   	printf("2 %d %d\n", ds + 6, ds + 3);
 	   	printf("2 %d %d\n", ds + 7, ds + 1);
 	   	printf("2 %d %d\n", ds + 7, ds + 4);
	} // 后面的分类讨论和上面的几乎一样 
	else if(n % 6 == 2) {
		printf("%d\n", ds + 3);
		printf("%d ", ds / 5 * 3 + 2);
		L(i, 1, ds) if(i % 5 == 0 || i % 5 == 3 || i % 5 == 4) printf("%d ", i);
		printf("%d %d\n", ds + 1, ds + 2);
	   	print(ds / 5);
	   	printf("2 %d %d\n", ds + 3, ds + 1);
 	   	printf("2 %d %d\n", ds + 3, ds + 2);
	} 
	else if(n % 6 == 3) {
 	   	printf("%d\n", ds + 4);
		printf("%d ", ds / 5 * 3 + 3);
		L(i, 1, ds) if(i % 5 == 0 || i % 5 == 3 || i % 5 == 4) printf("%d ", i);
		printf("%d %d %d\n", ds + 1, ds + 2, ds + 3);
	   	print(ds / 5);
 	   	printf("2 %d %d\n", ds + 4, ds + 1);
 	   	printf("2 %d %d\n", ds + 4, ds + 2);
 	   	printf("2 %d %d\n", ds + 4, ds + 3);
	} 
	else if(n % 6 == 4) {
	   	printf("%d\n", ds + 4);
		printf("%d ", ds / 5 * 3 + 2);
		L(i, 1, ds) if(i % 5 == 0 || i % 5 == 3 || i % 5 == 4) printf("%d ", i);
		printf("%d %d\n", ds + 1, ds + 2);
	   	print(ds / 5);
	   	printf("2 %d %d\n", ds + 3, ds + 1);
	   	printf("2 %d %d\n", ds + 3, ds + 2);
	   	printf("2 %d %d\n", ds + 4, ds + 1);
	   	printf("2 %d %d\n", ds + 4, ds + 2);
	} 
	else if(n % 6 == 5) {
 	   	printf("%d\n", ds + 5);
		printf("%d ", ds / 5 * 3 + 3);
		L(i, 1, ds) if(i % 5 == 0 || i % 5 == 3 || i % 5 == 4) printf("%d ", i);
		printf("%d %d %d\n", ds + 1, ds + 2, ds + 3);
 	   	print(ds / 5);
 	   	printf("2 %d %d\n", ds + 4, ds + 1);
 	   	printf("2 %d %d\n", ds + 4, ds + 2);
 	   	printf("2 %d %d\n", ds + 5, ds + 1);
 	   	printf("2 %d %d\n", ds + 5, ds + 2);
 	   	printf("2 %d %d\n", ds + 5, ds + 3);
	} 
	return 0;
}
```

---

## 作者：zythonc (赞：3)

~~可能是月赛中最简单的构造题？~~

## 【分析过程】

我们首先分析一下题意，能总结出以下题面中没有说的几点：

- 一条线路可以经过**无数**个车站

- 只要经过的车站集合**有交**就可以，并不管它是不是直的，甚至还可能是高架桥

所以说我们就想着将**每个车站最大化利用**，也就是说尽量的对于每个车站，都有**三条线路经过**

我们可以画个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/o9y3v8j3.png)

大概是这个样子，我们发现这样一来 $13$ 条线路就只用了 $10$ 个车站，$n$ 条线路就近似是 $\dfrac{5}{6}n$ 个车站

所以我们就按照这个思路来写就可以，注意 $(n-1)\%6=1$ 的时候要单独处理，防止其不满足题目限制

```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,zn,m,cp;
bool b,c;
signed main(){
	cin>>n;
	m=(n-2)/3+1;
	if((n-2)%3==0) b=1,n-=1;
	if(n%6==0) c=1;
	cp=m+1-b;
	int dt=cp+n-1-(((n-2)/3+1)/2*3);
	if(b) cout<<dt+1<<"\n";
	else cout<<((n%6)?dt-1:dt)<<"\n";
	for(int i=1;i<n;i++,cp++){
		cout<<((b&&i==n-1)?3:2)<<" "<<(i-1)/3+1<<" "<<cp-(((i-1)/3+1)/2*3);
		if(i!=n-1) cout<<"\n";
	}
	if(b) cout<<" "<<dt<<"\n2 "<<dt<<" "<<dt+1<<"\n";
	else cout<<"\n";
	if(b) dt+=3;
	cout<<dt-m-1+c<<" ";
	for(int i=1;i+m<dt+c;i++){
		cout<<i+m-b<<" ";
	}
	cout<<"\n";
	return 0;
}
```

---

## 作者：VinstaG173 (赞：1)

看样例大概就能看出点东西来了吧（雾

我们发现三条线路在同一点相交时是最优的，所以我们尽可能地让多一点站有三条线路。

然后我们发现如果有一条线路上有很多很多的站，和很多很多其他线路相连，就可以用很少的站点满足很多对 $(i,j,k)$ 的要求。

所以我们可以尝试用一条线路连接一堆点，然后其他的线路三条一组连一个站，然后分别连中间这条线路上的三个站，像这样：

![pic.png](https://i.loli.net/2020/10/08/fqeWX2ZKnJzv94x.png)

这样我们可以解决 $n=3k+1$ 的情况。

然后我们考虑 $n=3k+2$，我们新加一条线路，显然其与中间的线路有交点时可以用一个站满足很多组要求，然后它只要随便连到一个其他线路上就可以满足其与中间的线路被另一条线路关联了，像这样：

![pic.png](https://i.loli.net/2020/10/08/6ZRyuABvnEdYejH.png)

最后我们考虑再加一条线路，发现我们可以像上面一样考虑，然后和上图中的红色线路相交，像这样：

![pic.png](https://i.loli.net/2020/10/08/wIflvd6m7jrbCTZ.png)

然后我们就解决了这个问题，可以发现这个点数是在 $\dfrac{5}{6}n$ 左右的。

注意奇偶要分类讨论，因为有奇数个三条线路的组合时是没法凑满三条线路交于一点的。

时间复杂度 $O(n)$。

Code:
```cpp
#include<cstdio>
int n,t;
int v[4007];
int a[4007][4007];
int main()
{
	scanf(" %d",&n);
	if(n==3)
	{
		printf("3\n2 1 2\n2 1 3\n2 2 3\n");
		return 0;
	}
	if(n%3==1)
	{
		if(n&1)
		{
			printf("%d\n",n/2+n/3);
			for(int i=1;i<n;++i)printf("2 %d %d\n",(i-1)/3+1,n/3+(i-1)%3+1+(i-1)/6*3);
			printf("%d ",n/2);
			for(int i=1;i<=n/2;++i)printf("%d ",n/3+i);
		}
		else
		{
			printf("%d\n",n/2+n/3+1);
			for(int i=1;i<n;++i)printf("2 %d %d\n",(i-1)/3+1,n/3+(i-1)%3+1+(i-1)/6*3);
			printf("%d ",n/2+1);
			for(int i=1;i<=n/2+1;++i)printf("%d ",n/3+i);
		}
	}
	else if(n%3==2)
	{
		--n;
		if(n&1)
		{
			printf("%d\n",n/2+n/3+2);
			printf("3 1 %d %d\n",n/3+1,n/2+n/3+1);
			for(int i=2;i<n;++i)printf("2 %d %d\n",(i-1)/3+1,n/3+(i-1)%3+1+(i-1)/6*3);
			printf("%d ",n/2+1);
			for(int i=1;i<=n/2;++i)printf("%d ",n/3+i);
			printf("%d\n",n/2+n/3+2);
			printf("2 %d %d\n",n/2+n/3+1,n/2+n/3+2);
		}
		else
		{
			printf("%d\n",n/2+n/3+3);
			printf("3 1 %d %d\n",n/3+1,n/2+n/3+2);
			for(int i=2;i<n;++i)printf("2 %d %d\n",(i-1)/3+1,n/3+(i-1)%3+1+(i-1)/6*3);
			printf("%d ",n/2+2);
			for(int i=1;i<=n/2+1;++i)printf("%d ",n/3+i);
			printf("%d\n",n/2+n/3+3);
			printf("2 %d %d\n",n/2+n/3+2,n/2+n/3+3);
		}
	}
	else if(n%3==0)
	{
		n-=2;
		if(n&1)
		{
			printf("%d\n",n/2+n/3+3);
			printf("3 1 %d %d\n",n/3+1,n/2+n/3+1);
			for(int i=2;i<n;++i)printf("2 %d %d\n",(i-1)/3+1,n/3+(i-1)%3+1+(i-1)/6*3);
			printf("%d ",n/2+2);
			for(int i=1;i<=n/2;++i)printf("%d ",n/3+i);
			printf("%d %d\n",n/2+n/3+2,n/2+n/3+3);
			printf("2 %d %d\n",n/2+n/3+1,n/2+n/3+2);
			printf("2 %d %d\n",n/2+n/3+1,n/2+n/3+3);
		}
		else
		{
			printf("%d\n",n/2+n/3+4);
			printf("3 1 %d %d\n",n/3+1,n/2+n/3+2);
			for(int i=2;i<n;++i)printf("2 %d %d\n",(i-1)/3+1,n/3+(i-1)%3+1+(i-1)/6*3);
			printf("%d ",n/2+3);
			for(int i=1;i<=n/2+1;++i)printf("%d ",n/3+i);
			printf("%d %d\n",n/2+n/3+3,n/2+n/3+4);
			printf("2 %d %d\n",n/2+n/3+2,n/2+n/3+3);
			printf("2 %d %d\n",n/2+n/3+2,n/2+n/3+4);
		}
	}
	return 0;
}
```

---

## 作者：寒冰大大 (赞：1)

显然，我们可以转化为$S$ 个点 使得存在一条含有极大的与所有点有关的链（以下称为链）的树，并满足 $\Delta=4$ 的时候链外有 $n-1$ 条边的图，此时考虑链外的点，有 $\sum degG'$ 个（即不在链上的所有点的和） 由于每个点度为 $3$（肯定是最优的），因此可以构造出点为 $5$ 的度序列为$3,3,3,3,4$ 的子图，也就是说可以得到答案最优为 $\frac{5}{6}(n-1)$,但是还没完，链两端的端点度为 $3$ 还可以连一条边，最优的答案为 $\frac{5n-2}{6}$~~不过貌似比$n$低一点就可以了~~

另外考虑hack，$n=6$ 即任意两个点距离 $\leq2$ 的时候都不需要考虑一个极大的链，此时在$K_4$上取得

~~另外spj是不是有点锅啊（那个判限制3的地方）~~

貌似可以推广一下，车站最多连 $k$ 个的话应该是 $\frac{(k+(k-1))n-(k-1)}{k*(k-1)}$个点？ 

---

## 作者：dead_X (赞：1)

## 前言
简单的构造题。
## 思路
首先，有一个 $n$ 条站点的方法，但是那个和正解没啥关系，所以我们直接考虑正解。

我们发现如果我们要车站数量**竟可能少**，那么一个车站**穿过的线路数量**应该尽可能取 $3$，而一条线路穿过的车站数也应该尽量取 $2$。

但是还有**关联**的条件让人有点不爽，我们考虑干掉他。怎么干呢？我们考虑用一条线路和**所有线路**都交一下，剩下的线路再穿过另一个点，这样就可以分两种情况考虑关联线路了：

首先，我们定义下方的点（在穿过所有线路那条线路上的点）和上方点（其余的点）

1. 一条最底下(穿过 $A$)的路和一条连接上下的路(穿过 $AB$)：即另一条连接上下的路(穿过 $BC$)。**但因此，我们需要一个上方点至少与两个下方点有线路**。
2. 两条连接上下的路：即最底下的路。

然后我们考虑一个最优结构（即下图最左），显然已经利用到了最优，站点数量为 $\frac{5}{6}n$。但是这样是 $6$ 条线路的，可能有余数，因此我们可以使用右边比较劣的三种结构处理边界条件，加亿点细节就过了。

![](https://cdn.luogu.com.cn/upload/image_hosting/nyw68u1o.png)
## 代码
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int tot,cnt=1;
vector<int> a[1000003];
signed main()
{
	int n=read(),m=n,ans=1+(n/6)*4;
	if(n==3) puts("3\n2 1 2\n2 1 3\n2 2 3"),exit(0);
	if(n==4) puts("4\n2 1 2\n2 2 4\n2 2 3\n3 1 3 4"),exit(0);
	n--;
	while(n>=6)
	{
		if(n==7)
		{
			int x=++tot;
			a[++cnt].push_back(++tot),a[1].push_back(tot),a[cnt].push_back(x);
			a[++cnt].push_back(++tot),a[1].push_back(tot),a[cnt].push_back(x);
			x=++tot;
			tot-=3;
			a[++cnt].push_back(++tot),a[cnt].push_back(x);
			a[++cnt].push_back(++tot),a[cnt].push_back(x);
			tot=x;
			x=++tot;
			a[++cnt].push_back(++tot),a[1].push_back(tot),a[cnt].push_back(x);
			a[++cnt].push_back(++tot),a[1].push_back(tot),a[cnt].push_back(x);
			a[++cnt].push_back(++tot),a[1].push_back(tot),a[cnt].push_back(x);
			n-=7;
			break;
		}
		int x=++tot;
		a[++cnt].push_back(++tot),a[1].push_back(tot),a[cnt].push_back(x);
		a[++cnt].push_back(++tot),a[1].push_back(tot),a[cnt].push_back(x);
		a[++cnt].push_back(++tot),a[1].push_back(tot),a[cnt].push_back(x);
		x=++tot;
		tot-=4;
		a[++cnt].push_back(++tot),a[cnt].push_back(x);
		a[++cnt].push_back(++tot),a[cnt].push_back(x);
		a[++cnt].push_back(++tot),a[cnt].push_back(x);
		tot=x;
		n-=6;
	}
	if(2<=n && n<=3)
	{
		int x=++tot;
		while(n--) a[++cnt].push_back(++tot),a[1].push_back(tot),a[cnt].push_back(x);
	}
	if(n>3)
	{
		int x=++tot;
		a[++cnt].push_back(++tot),a[1].push_back(tot),a[cnt].push_back(x);
		a[++cnt].push_back(++tot),a[1].push_back(tot),a[cnt].push_back(x);
		a[++cnt].push_back(++tot),a[1].push_back(tot),a[cnt].push_back(x);
		x=++tot;
		tot-=4,n-=3;
		while(n--) a[++cnt].push_back(++tot),a[cnt].push_back(x);	
		tot=x;
	}
	printf("%d\n",tot);
	for(int i=1; i<=m; i++) 
	{
		printf("%d ",a[i].size());
		for(int j=0; j<a[i].size(); j++) printf("%d ",a[i][j]);
		puts("");
	}
	exit(0);
}
```

---

## 作者：larsr (赞：0)

这道题的关键在这:
> 为了保证交通顺畅，对于任意两条不同线路 $i, j(i \not = j)$，都存在第三条线路 $k (k \not = i, k \not = j)$，使得 $k$ 与 $i, j$ 均**关联**。

其中最难处理的是**线路** $k$。使用**贪心思路**，居然 $k$ 难**处理**，那么我们可以让**某一条**线路成为与**其他**线路**都**关联的线路，这样 $k$ 就不会构造不出来了。

构建方法如下:
> 1.总共 $n - 1$ 个车站。

> 2.其中的一条线路**车战**集合为**所有**的车站。

> 3.对于**剩下的** $n-1$ 条线路，第 $i$ 条线路，经过的**车站**为 $i$ 和 $i + 1$，**特别的**第 $n - 1$ 条线路，经过车站为 $1$ 和 $n - 1$。

程序如下:
```cpp
#include<cstdio>
using namespace std;
int n;
int main()
{
	scanf("%d", &n);
	printf("%d\n", n - 1);
	printf("%d ", n - 1);
	for(int i = 1; i < n; i++)
	{printf("%d", i);if(i != n - 1)printf(" ");}
	printf("\n");
	for(int i = 2; i < n; i++)
	printf("2 %d %d\n", i, i - 1);
	printf("2 1 %d", n - 1);
	return 0;
}
```
现在可以轻松得到 $76$ 分。

思考换一个**模型**，首先那个与其他**所有**线路**都**关联的线路还**存在**。可以**变换**成这样（除去那条线路，其他的线路车站集合只有两个，并如下每六个一组）:
![](https://cdn.luogu.com.cn/upload/image_hosting/6b98px6u.png)
解释一下:
> 1.边权为 $a$ 的边是刚说的那个**线路**的边。

> 2.其他的代表**通过**这条边的**线路**有几个。

其中有 $\frac{5}{6}(n - 1)$ 条边，非常优秀，这样就可以拿满分了。

---

