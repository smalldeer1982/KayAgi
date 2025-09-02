# [MtOI2019] 膜Siyuan

## 题目背景

你强归你强，$\mathsf S\mathsf{\color{red} iyuan}$ 比你强。——$\mathsf S \mathsf{\color{red} iyuan}$

disangan233 最近发现了一款 OIer 们的游戏：[膜 $\color{black} \mathsf S \mathsf{\color{red} iyuan}$](https://lmoliver.github.io/mosiyuan/index.html)。

他被里面的「真理 IV」所困惑，于是他找到了你寻求帮助。


## 题目描述

给你 $1$ 个正整数 $M$，$n(n\leq 5)$ 个正整数 $3$ 元组 $\{a_i,b_i,c_i\}(a_i,b_i,c_i\leq M\leq 2000)$，请你求出所有满足

$$
\forall i\leq n ,s.t.~|a_i-x|\oplus |b_i-y|\oplus |c_i-z| = 9
$$

的**有序**正整数 $3$ 元组 $\{x,y,z\}(x,y,z \leq M)$的个数。

其中，$\forall$ 表示 "对于所有"，$s.t.$ 表示 "使得"，$A \oplus B \oplus C$ 表示 $A,B,C$ 的异或和。

对于 C++，`A^B^C` 或 `A xor B xor C` 即为 $A \oplus B \oplus C$ 的答案 。

这里提供一份模板：

```cpp
if ((a ^ b ^ c) == 9) 
{
	Your code here...
}
```

对于 $2$ 个有序 $3$ 元组 $A,B$，如果 $x_A \not =x_B$ 或 $y_A \not =y_B$ 或 $z_A \not =z_B$，$A,B$ 即被视为是不同的。


## 说明/提示

#### 样例解释 $1$

所有满足条件的 $\{x,y,z\}$ 有： 

$\{88,88,120\}$，$\{88,104,104\}$，$\{120,120,120\}$ 和 $\{120,136,104\}$。

共 $4$ 个。

### 子任务

对于 $10\%$ 的数据，保证与样例完全一致。

对于 $60\%$ 的数据，保证 $M\leq 200$。

对于所有数据，保证 $a_i,b_i,c_i\leq M\leq 2000$，$n\leq 5$。


### 题目来源

[MtOI2019 Extra Round](https://www.luogu.org/contest/22614) T2

出题人：disangan233

验题人：Studying Father


## 样例 #1

### 输入

```
5 200
21 84 198
38 47 102
44 47 132 
63 150 166
76 79 132```

### 输出

```
4```

# 题解

## 作者：hwx12233 (赞：16)

# 首先
我想哭一会。。。

我交了27遍才过。。。我的27遍提交啊！！？？

### 然后进入正题

#### 先是一般暴力：

枚举X，Y，Z，再把所有a、b、c检验一遍，判断A^B^C是否成立

显然这种做法是m三方n的；期望得分60

m=2000？？？
炸了呀！咋办？

#### 优化：

很容易 ~~被大佬指点~~ 得出只要枚举X和Y，再去判断Z是否成立就行啦

因为只要X和Y确定，那么Z一定也可以确定，不用枚举了，只要和暴力一样去判断就好了

时间复杂度m方，可以满分

#### 做法：

当枚举第一组三元组时
先求出Z

由异或交换律得A^B^C=9
<=>
C=A^B^9

设一个L=
(abs(a[w]-i)^abs(b[w]-j)^9)
=C

再解一个绝对值方程
|ci-Z|=L

可得

Z=ci-L（ci>Z）

Z=ci+L（ci<Z）


就得出（此处temp，temp2为两个解）

temp=ci-L（当temp<m&&temp>0&&ci>temp） 

temp2=ci+L（当temp2<m&&temp2>0&&ci<temp2）

（p.s.没有temp=0的情况，因为Z是正整数，~~这个改了我十多遍~~,也没有temp2=m的情况，因为ci也<=m）

如果不符合解的条件
那就把解赋为-1，自动跳过

判断不符合的方

之后就枚举每一个a,b,c判断是否符合

代码中a，b，c数组分别对应x，y，z


```cpp
#include<cstring>
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,x[6],y[6],z[6],ans=0,temp,temp1,temp2;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i]>>z[i];
	for(int i=1;i<=m;i++)
	for(int j=1;j<=m;j++)
	for(int w=1;w<=n;w++)
	{
		if(w==1)//第一组数时解出两个解 
		{
			int l=(abs(x[w]-i)^abs(y[w]-j)^9);
			temp=z[w]-l;//算出两个解 
			temp2=z[w]+l;
			if(temp<=0||temp>m||z[w]<temp) temp=-1;//如果解不符合范围，赋值-1
			//题目中说XYZ是正整数所以要<=0   和   <=z[w] 
			if(temp2>m||temp2<=z[w]||temp2<0) temp2=-1;//判断范围为原范围的补集 
		}
		if((abs(x[w]-i)^abs(y[w]-j)^abs(z[w]-temp))==9&&temp!=-1){//每一个解进行判断 
			if(w==n&&temp!=-1){
				ans++; cout<<temp<<" temp1"<<endl;
			}
			//如果符合，ans++ 
		}
		else temp=-1;//有一个不符合就停止 
		if((abs(x[w]-i)^abs(y[w]-j)^abs(z[w]-temp2))==9&&temp2!=-1)//同上 
		{
			if(w==n&&temp2!=-1){
				ans++;cout<<temp2<<" temp2"<<endl;
			}
		}
		else temp2=-1;
	}
	cout<<ans<<endl;
}
```


谢谢观看





---

## 作者：disangan233 (赞：16)

### 引理

> 你强归你强，$\mathsf S\mathsf{\color{red} iyuan}$ 比你强。

### 算法一

我会输出样例！期望得分 $10$ 分。

我会暴力枚举！时间复杂度 $O(M^3n)$，期望得分 $60$ 分。

注意 xor 的优先级低于四则运算。

### 算法二

观察一下本题的式子：
$$
\forall i\leq n ,s.t.~|a_i-x|\oplus |b_i-y|\oplus |c_i-z| = 9
$$
考虑优化枚举。因为 $\oplus$ 具有交换律，且 $|x|=y$ 的解为 $x=\pm y$，所以可以将其中枚举的一位拆开，得到：
$$
\forall i\leq n ,s.t.~|a_i-x|\oplus |b_i-y|\oplus 9 = |c_i-z|
$$
时间复杂度 $O(M^2n)$，期望得分 $100$ 分。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=15;
int n,m,a[N],b[N],c[N],ans;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d%d%d",a+i,b+i,c+i);
	for(int i=1;i<=m;i++) for(int j=1;j<=m;j++)
	{
		int tmp=(abs(i-a[1])^abs(j-b[1])^9),l=c[1]-tmp,r=c[1]+tmp; 
		int ok1=(l>0&&l<=m),ok2=(r>0&&r<=m&&(l^r));
		for(int k=2;k<=n;k++) 
		{
			ok1&=!(abs(i-a[k])^abs(j-b[k])^abs(l-c[k])^9);
			ok2&=!(abs(i-a[k])^abs(j-b[k])^abs(r-c[k])^9);
		}
		ans+=ok1+ok2;
	}	
	cout<<ans<<endl;
	return 0;
}
//Author: disangan23
//In my dream's scene,I can see the everything that in Cyaegha.
```

---

## 作者：Crab_Dave (赞：16)

出题人丧心病狂啊qwq

~~果然在大佬眼中正解就是暴力qwq~~

先讲一下思路qwq

首先我们枚举x和y，再根据第一组a,b,c解出z，并把z代入剩下的a,b,c里检验，如果均成立则答案+1。

显然这里我们需要解一个异或方程 a^b^x = 9 （注意，C++里Xor的优先级在==之后！！！所以不打括号的话就会变成a^b^(x==9?1:0)qwq...~~我的暴力就因为这个挂了一次~~）

我们注意到，如果两个数的值相同，那么它们的异或值为0；

又：0异或上一个数就等于这个数本身；

所以有：a^b^x^9 = 0

交换x和9得：a^b^9^x =0

那么把x移到右边就可以解得：x = a^b^9

还有一点，这里的x是abs(c[1]-z)，我们还需要解一个绝对值方程求出z，并对z是否在[1,M]中进行判断。~~但是像这种初一的知识就免掉不谈吧哈哈哈哈~~

上代码咯~

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstdlib>//头文件，cstdlib说明有JFCA（
using namespace std;

int n,M,fl;
int u[7],v[7],w[7],ans;

int main()
{
	scanf("%d%d",&n,&M);
	for(register int i=1;i<=n;i++)
		scanf("%d%d%d",&u[i],&v[i],&w[i]);//输入
	if(M<=200)//这部分是暴力，我就不解释了，自己感性理解吧（
	{
		for(register int x=1;x<=M;x++)
			for(register int y=1;y<=M;y++)
				for(register int z=1;z<=M;z++)
				{
					int sum=0;
					for(register int i=1;i<=n;i++)
					{
						if((abs(u[i]-x)^abs(v[i]-y)^abs(w[i]-z))==9)sum++;
					}
					if(sum==n)ans++;
				}
		printf("%d\n",ans);
		return 0;
	}
	for(register int x=1;x<=M;x++)
		for(register int y=1;y<=M;y++)//枚举x和y
		{
			int t=abs(u[1]-x)^abs(v[1]-y)^9;//解出abs(w[1]-z)
			int z=w[1]-t;//先判断第一个解
			if(z>0)
			{
				fl=0;
				for(register int i=2;i<=n;i++)
					if(abs(u[i]-x)^abs(v[i]-y)^abs(w[i]-z)^9){fl=1;}//判断其它几组数
				if(!fl)ans++;
			}
			if(t)//如果t为0，就只有一个解了qwq
			{
				z=w[1]+t;//如果没有，我们就判断另一个解
				if(z<=M)
				{
					fl=0;
					for(register int i=2;i<=n;i++)
						if(abs(u[i]-x)^abs(v[i]-y)^abs(w[i]-z)^9){fl=1;}//不解释
					if(!fl)ans++;
				}
			}
		}
	printf("%d\n",ans);//啊，输出了...（大雾）
	return 0;/结束了罪恶的一生qwq
}
```

呼真的累死我了不介意的话顶一下再走吧qwq


---

## 作者：zjy111 (赞：10)

作为xjoi的一员 , 我大力资瓷这个题目 !

壮哉我${\color{Black}S}{\color{Red}iyuan}$神教 !

[mosiyuan theme](https://www.luogu.org/theme/design/5321)

[mosiyuan website](https://lmoliver.github.io/mosiyuan/)

好了先讲一下题意 :

玩过%${\color{Black}S}{\color{Red}iyuan}$的都知道 ,

![](https://lmoliver.github.io/mosiyuan/daily3.png)

~~这题数据范围远远超过真实游戏 , dsg太毒瘤了~~

真理IV是相位 , 也就是说 ,

答案为固定值 $x,y,z$ , 给定若干组数据 $a_i,b_i,c_i$ , 求有多少组解 $x,y,z$ 满足三元一次方程组

$\begin{cases} 	\left| a_1 - x \right| xor \left| b_1 - y \right| xor \left| c_1 - z \right| = 9
\\ \left| a_2 - x \right| xor \left| b_2 - y \right| xor \left| c_2 - z \right| = 9
\\......
\\ \left| a_n - x \right| xor \left| b_n - y \right| xor \left| c_n - z \right| = 9
\end{cases}$

一看数据范围 , $2000$ 的范围是不可能让 $m^3$ 过的

那么我们就要考虑一下如何优化

首先我们可以知道 ,

![](https://lmoliver.github.io/mosiyuan/daily4.png)

异或等效于二进制下的不进位加法和不进位减法 , 所以如果有

$a$ $xor$ $b$ $=$ $c$

那么就有

![](https://lmoliver.github.io/mosiyuan/daily2.png)

$a$ $xor$ $c$ $=$ $b$ , $b$ $xor$ $c$ $=$ $a$ 等式子

反之亦然

所以我们做这道题时完全不用三重循环枚举$x,y,z$ , 

可以通过已知的答案$9$和枚举的 $x,y$ 算出 $\left| c_i - z \right|$ 的可能的两组解并一一加以判断 , 复杂度 $O(m^2n)$, 可以通过本题

注意事项:

![](https://lmoliver.github.io/mosiyuan/daily1.png)

## 如果发现$\left| a_2 - x \right| xor \left| b_2 - y \right|$的值等于9 , 那么最后算出来的是只有一组解的 , 不能重复算两遍 !

献上码风奇特的代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define r register
#define Siyuan AK IOI //作为Siyuan的忠实信徒,这一句怎么能少呢?
int n,m,a[15],b[15],c[15];
long long orzsiyuan=0;
int main(){
	cin>>n>>m;
	for(r int i=1;i<=n;++i) cin>>a[i]>>b[i]>>c[i];
	for(r int x=1;x<=m;++x){
		for(r int y=1;y<=m;++y){
			int t=0,tmp=(abs(a[1]-x)^abs(b[1]-y)),qwq=tmp^9,z1=c[1]-qwq,z2=c[1]+qwq,flg1=1,flg2=1; //找到z1和z2两组满足第一个式子的解
			if(z1<=0 || z1>m)flg1=0; //必须特判算出来的z是否在范围之内
			if(z2<=0 || z2>m)flg2=0;
			if(flg1)
			for(r int i=2;i<=n;++i)
				if((abs(a[i]-x)^abs(b[i]-y)^abs(c[i]-z1))!=9){flg1=0;break;} //判断z1是否满足方程
			if(flg2)
			for(r int i=2;i<=n;++i)
				if((abs(a[i]-x)^abs(b[i]-y)^abs(c[i]-z2))!=9){flg2=0;break;} //判断z2是否满足方程
			orzsiyuan+=flg1+flg2;
			if(!qwq && flg1 && flg2)--orzsiyuan; //注意如果之前的qwq是0的话那么z1和z2相等,只能算一个!
		}
	}
	cout<<orzsiyuan;
	return 0;
}
```

最后的最后 , 祝大家%${\color{Black}S}{\color{Red}iyuan}$愉快 , 不要弃坑哦qwq

也希望游戏开发者${\color{Black}L}{\color{Red}MOliver}$能够持续更新 , 让${\color{Black}S}{\color{Red}iyuan}$神教发扬光大 !


---

## 作者：zombie462 (赞：7)

$O(M^3n)$做法：

使用我初赛前颓膜$S\color{red}{iyuan}$时的做法，$3$重循环枚举。

但是显然这样是过不了的，因为$M$有$1000$。

~~像膜$S\color{red}{iyuan}$里那样$x,y,z$只能取$[160,220]$范围内的数这样多好~~

$O(M^2n)$做法：

枚举$x,y$。

对于每组$a_i,b_i$，可以得到$|c_i-z|$的值。

具体地，$|c_i-z|=9\ xor\ |a_i-x|\ xor\ |b_i-y|$

注：$xor$有一个运算法则：$a\ xor\ b=c\to c\ xor\ b=a\to c\ xor\ a=b$

之后对于每个$c_i$，求出对应的两个$z$。

具体地，$|c_i-z|=p\to c_i-z=\pm\ p\to z=c_i\pm p$

只要某一个$z$同时在所有的组里出现，$z$就可以作为答案的一部分，也就是说有一组$(x,y,z)$符合条件，$ans$就可以加一。这可以用计数数组实现，但也可以一通乱搞（比如我就是这么做的）。

具体见代码：

```
//这是我比赛时现场写的代码，所以有些变量名称取得不是很好，请见谅
#include <bits/stdc++.h>
using namespace std;
#define N 111111
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while (c<'0' || c>'9'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0' && c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
int x[N],y[N],z[N],b[N];
int main(){
	int n=read(),m=read();
	for (int i=1;i<=n;++i){
		x[i]=read(),y[i]=read(),z[i]=read();
	} 
	int ans=0;
	for (int i=1;i<=m;++i){
		for (int j=1;j<=m;++j){
			int dimc=-1,dimd=-1; //dimc和dimd是用来找那个在每组都出现过的z的
			for (int k=1;k<=n;++k){
				int b,c,d;
				b=9^(abs(i-x[k])^abs(j-y[k])); //求出对应的|ci-z|
				c=z[k]+b; //求出|ci-z|=b的两个根
				d=z[k]-b;
				if (c>m) c=-2; //如果根不符合条件就舍去
				if (d<=0) d=-2;
				if (k==1){
					if (c!=-2) dimc=c; 
					if (d!=-2) dimd=d;
				}else{
					if (c==dimc && d==dimd){ //一通乱搞看看这两个根在之前有没有一直在出现，如果没有就不要这个根了
						continue;
					}else if (c==dimd && d==dimc){
						continue;
					}else if (c==dimc){
						dimd=-1;
					}else if (c==dimd){
						dimc=-1;
					}else if (d==dimc){
						dimd=-1;
					}else if (d==dimd){
						dimc=-1;
					}else{
						dimc=dimd=-1;
					}
				}
			}
			if (dimc!=-1) ans++;
			if (dimd!=-1 && dimc!=dimd) ans++; //如果有可行的根，那么对答案增加贡献
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

最后来一波宣传：

长期更新：[膜Siyuan攻略](https://www.luogu.org/blog/zombie462/mosiyuan)

~~话说这次比赛之后膜$S\color{red}{iyuan}$的人明显多了啊~~

~~作为一个初赛前就将膜$S\color{red}{iyuan}$真理`V`搞定的玩家，我有必要发一点关照新手的攻略~~

顺便改版了`LMOliver`的`Game`，并更新了超出膜$S\color{red}{iyuan}$的一小部分内容

[膜Yukai](https://zombie462.github.io/moyukai/index.html)

---

## 作者：StudyingFather (赞：6)

> 你强归你强，$\color{red}{\mathsf{S}}\color{black}\mathsf{iyuan}$ 比你强！

大家好，我是本题的验题人。

~~其实这题本来应该放 A 题的位置的，但因为不够签到就成了 B 题。~~

接下来进入正题。

## 算法一

当 $M \leq 200$ 时，我们可以直接枚举 $x,y,z$ 的值，判断其是否满足所有等式即可。

时间复杂度：$O(n^3)$，期望得分 $60$。

## 算法二

假如这个方程只有一个未知数（像 $|a-x|=b$ 这样的形式，其中 $a,b$ 为常数），显然我们可以直接求出该方程的解，而不用枚举 $x$ 的值。

因此我们可以只枚举两个未知数，将两个未知数代入其中一个等式，推算出第三个未知数的值，将这组解代入其余等式，判断是否成立即可。

时间复杂度：$O(n^2)$，期望得分 $100$。

几个注意事项：

1. 记得判断第三个未知数是否在 $[1,M]$ 的范围内；
1. 绝对值方程可能会出现两个相同解的情况（像 $|x-6|=0$ 这样的方程的解为 $x_1=x_2=6$），需要处理这种情况。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
struct node
{
 int a,b,c;
}p[15];
int main()
{
 int n,m,ans=0;
 scanf("%d%d",&n,&m);
 for(int i=1;i<=n;i++)
  scanf("%d%d%d",&p[i].a,&p[i].b,&p[i].c);
 for(int i=1;i<=m;i++)
  for(int j=1;j<=m;j++)
  {
   int tmp=abs(i-p[1].a)^abs(j-p[1].b)^9;
   int res1=p[1].c+tmp,res2=p[1].c-tmp;
   int flag1=(res1>0&&res1<=m),flag2=(res2>0&&res2<=m);
   for(int k=2;k<=n;k++)
   {
    if((abs(i-p[k].a)^abs(j-p[k].b)^abs(res1-p[k].c))!=9)flag1=false;
    if((abs(i-p[k].a)^abs(j-p[k].b)^abs(res2-p[k].c))!=9)flag2=false;
   }
   //if(flag1)printf("%d %d %d\n",i,j,res1);
   //if(flag2)printf("%d %d %d\n",i,j,res2);
   if(res1==res2)flag2=false;//排除两个相同解的情况
   ans+=flag1+flag2;
  }
 printf("%d\n",ans);
 return 0;
}
```


## 题外话

Orz $\color{red}{\mathsf{S}}\color{black}\mathsf{iyuan}$！

---

## 作者：Hexarhy (赞：2)

异或运算好题，适合初学者巩固异或运算的性质。

-------

**update:**

由于笔者大意，证明那一块出现了小瑕疵。现已修正，请看清楚再审核。

-------

### 解题思路

**算法一**

暴力枚举 $\{x,y,z\}$，时间复杂度为 $O(nm^3)$。

预计得分 $60\%$。参考代码略。

**算法二**

这是一个三元一次不定方程。

那么方程就可以**只枚举两个未知数**，剩下一个未知数就可以算出来。这样就省去了一个循环。

但是解异或方程需要简单地证明一下。

-------

#### 关于异或

**提示：下面将是较长的有关异或运算的内容，如果您已经熟练可跳过这个部分。**

下面统一用 $\oplus$ 来表示异或运算符 $\mathrm{xor}$。

复习一下异或的常用性质：

1. 交换律：$a\oplus b=b\oplus a$

1. 结合律：$(a\oplus b)\oplus c=a\oplus(b\oplus c)$

1. 根据定义得：$a\oplus a=0\quad a\oplus 0=a$。文字表示为：一个数异或本身为 $0$；一个数异或 $0$ 不变。

1. 自反性：$a\oplus b\oplus b=a$

1. 满足等式的基本性质，即等式两边异或同一个数，等式依然成立。

1. 异或得到的数一定不大于原来任意一个数，即 $a_1\oplus a_2\oplus \cdots\oplus a_n=c$，则 $\forall 1\le i\le n,c\le a_i$。

自反性的证明很简单，用结合律即可。

$a\oplus b\oplus b=a\oplus (b\oplus b)=a\oplus 0=a$

-----------

那么对于等式：

$$x\oplus y\oplus z=t$$

有：

$$x\oplus y\oplus t=z$$

证明如下：

由性质 $3,5$ 得，
$$x\oplus y\oplus z\oplus t=t\oplus t=0$$

由性质 $5$ 得，

$$x\oplus y\oplus z\oplus t\oplus z=0\oplus z$$

由性质 $1,2,3$ 得，

$$x\oplus y\oplus t\oplus 0=0\oplus z$$

由性质 $3$ 得，

$$x\oplus y\oplus t=z$$

得证。

----------


#### 优化算法

说完了异或的性质，那么优化算法就很简单了。

我们依然枚举 $x,y$，但对于 $z$ 我们计算得到。

根据刚才的证明，我们有：

$$|a_i-x|\oplus|b_i-y|\oplus9=|c_i-z|$$

设 $t=|a_i-x|\oplus|b_i-y|\oplus9$，那么 $|c_i-z|=t$。

去绝对值得到：

$$c_i-z=\pm t$$

解得：

$$z_1=c_i+t,z2=c_i-t$$

至此，只需要检验 $z_1,z_2$ 是否在区间 $[1,m]$ 范围内并且满足 $n$ 组数据。

时间复杂度为 $O(nm^2)$。

---------

### 实现细节

- 注意**去重**。绝对值当然可能有 $z_1=z_2$，故要特判，只算 $1$ 个答案。

- **一个小技巧**：由于我们要保证每一组数据都能成立，我们可以用第一组 $\{a,b,c\}$ 求出 $z$。然后在 $[2,n]$ 的范围内代入原式验证。操作起来比解 $n$ 个方程简单得多。

- 代码中使用 `bool` 计数答案是否可行。只要有一组答案不满足，即标记为 `false` 或 `0`。

-----------

### 参考代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN=15;
int n,m;
int a[MAXN],b[MAXN],c[MAXN];
int ans;

void input(void)
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	 cin>>a[i]>>b[i]>>c[i];
}

void solve(void)
{
	for(int x=1;x<=m;x++)
	 for(int y=1;y<=m;y++)
	 {
		 const int t=abs(x-a[1])^abs(y-b[1])^9;
		 const int z1=c[1]+t;
		 const int z2=c[1]-t;//利用第一组数据计算z1,z2
		 bool f1=(0<z1 && z1<=m),f2=(0<z2 && z2<=m);//首先判断z1,z2是否在合法区间内
		 for(int i=2;i<=n;i++)//逐个代入验证。任一不符就为false
		 {
			 if((abs(x-a[i])^abs(y-b[i])^abs(z1-c[i]))!=9)
			  f1=false;
			 if((abs(x-a[i])^abs(y-b[i])^abs(z2-c[i]))!=9)
 			  f2=false;
		 }
		 ans=ans+f1+f2;
         if(z1==z2)//去重，多算了一个答案
          ans--;
	 }
}

int main()
{
	input();
	solve();
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：寒鸽儿 (赞：2)

暴力:  
枚举$x,y,z,$代入验证即可。  
复杂度$O(m^3n)$  
优化：  
说一下推式子:  
$a\space xor \space b \space xor \space c \space = \space 9$  
$ \Leftrightarrow a \space xor \space b \space xor \space c \space xor \space 9 = \space 9 \space xor \space 9 \space = \space 0 $  
$ \Leftrightarrow a \space xor \space b \space xor \space c \space xor \space c \space xor \space 9 \space = \space 0 \space xor \space c \space = \space c $  
$ \Leftrightarrow a \space xor \space b \space xor \space 9 \space = \space 0 \space xor \space c \space = \space c $  
即:  
$ |a_i - x| \space xor \space |b_i - y| \space xor \space 9 \space = \space |c_i-z|$  
那么枚举$x, y$,计算$z$,若所有式子算出的都相同即可。  
注意可能对同一组$x, y$算出的$z$相等,注意判重。  
```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
	int fmt[6][4], n, m, cnt = 0;
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; ++i) scanf("%d %d %d", &fmt[i][0], &fmt[i][1], &fmt[i][2]);
	for(int x = 1; x <= m; ++x)
		for(int y = 1; y <= m; ++y) {
			int tmp = 9 ^ abs(fmt[0][0] - x) ^ abs(fmt[0][1] - y);
			int z1 = tmp + fmt[0][2], z2 = fmt[0][2] - tmp;
			if(z1 < 1 || z1 > m) z1 = -1;
			if(z2 < 1 || z2 > m) z2 = -1;
			for(int i = 1; i < n; ++i) {
				tmp = 9 ^ abs(fmt[i][0] - x) ^ abs(fmt[i][1] - y);
				if(abs(fmt[i][2] - z1) != tmp) z1 = -1;
				if(abs(fmt[i][2] - z2) != tmp) z2 = -1;
			}
			if(~z2) ++cnt;
			if(~z1 && z1 != z2) ++cnt;
		}
	printf("%d\n", cnt);
	return 0;	
}
```

---

## 作者：Kevin_Wa (赞：2)

### 题目大意：

需要你找到三元组，使得每个输入的三元组与此对应的差的异或和为9.

### 解题分析

首先想到的肯定是暴力，通过枚举每一个三元组，再进行判断即可统计出三元组的总量。时间复杂度$O(M^3 \times n)$。

然后再仔细想一下，其实异或的逆运算是他的本身，也就是说只需要枚举前两个元素的值，再与$9$算异或和，即可推出剩下一个元素的可能值，由于有绝对值，需要再分类讨论，带入其他的式子即可，若其他式子可推出相同的结果，即此二元组所对应的三元组是所求答案之一，时间复杂度$O(M^2 \times n)$。

### 评价

对于考场的T2，本题并不难，但作者因为没有分类讨论，所以只有$90$分。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,M,cnt;
int x[6],y[6],z[6];
template <typename T> void read(T &x) {
x = 0; char c = getchar();
for (; !isdigit(c); c = getchar());
for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
}
int work(int a,int b,int c){
	if (a<=0||b<=0||c<=0||a>M||b>M||c>M) return 0;
	for (register int i=1;i<=n;i++)
		if ((abs(a-x[i])^abs(b-y[i])^abs(c-z[i]))!=9) return 0;
	return 1;
}
int main()
{
//freopen(".in","r",stdin);
//freopen(".out","w",stdout);
read(n);read(M);
for (int i=1;i<=n;i++)
  read(x[i]),read(y[i]),read(z[i]);
if (M<=200)
  {
  	for (int i=1;i<=M;i++)
  for (int j=1;j<=M;j++)
    for (int k=1;k<=M;k++)
      {
      	int flag=1;
      	for (int t=1;t<=n;t++)
      	  if ((abs(x[t]-i)^abs(y[t]-j)^abs(z[t]-k))!=9) 
      	    {
      	    	flag=0;
      	    	break;
			  }
		if (flag) cnt++;
	  }
  }
else
{
for (int i=1;i<=M;i++)
  for (int j=1;j<=M;j++)  //abs(z[1]-k)=sum
    {
    	int sum=abs(i-x[1])^abs(j-y[1])^9;
    	int k1=z[1]-sum,k2=z[1]+sum;
    	if (sum) cnt+=work(i,j,z[1]+sum)+work(i,j,z[1]-sum);
			else cnt+=work(i,j,z[1]);
    }
}
printf("%d\n",cnt);
return 0;
}
```


---

## 作者：opened (赞：1)

首先了解一下 $xor$ 的性质：

- 1.交换律

- 2.结合律 $(a\ xor\ b)\ xor\ c == a\ xor\ (b\ xor\ c)$

- 3.对于任何数 $x$ ，都有 $x\ xor\ x=0$ ，$x\ xor\ 0=x$

- 4.自反性 $A\ xor\ B\ xor\ B=A\ xor\ 0=A$

$So:$枚举 $x$ , $y$ ，根据 $xor$ 的性质算出 $z$ 后判断即可。

复杂度 $O(m^2)$
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int read(){
    int x=0;char c=getchar();
    while(!isdigit(c))c=getchar();
    while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x;
}
int m,n,a[10],b[10],c[10],cnt;
int work1(int k,int i,int j){
	return c[k]-(abs(a[k]-i)^abs(b[k]-j)^9);
}
int work2(int k,int i,int j){
	return c[k]+(abs(a[k]-i)^abs(b[k]-j)^9);
}
int main(){
    n=read(),m=read();
    for(int i=1;i<=n;i++) a[i]=read(),b[i]=read(),c[i]=read();
    for(int i=1;i<=m;i++)
    	for(int j=1;j<=m;j++){
			int x1=work1(1,i,j),f=0;
			if(x1<=m&&x1>0){
				for(int k=2;k<=n;k++){
					int s=abs(a[k]-i)^abs(b[k]-j)^9,t=abs(c[k]-x1);
	    			if(s!=t){
	    				f=1;
	    				break;
					}
				}
				if(!f) cnt++;
			}
			f=0;
			int x2=work2(1,i,j);
			if(x2!=x1){
				if(x2<=m&&x2>0){
					for(int k=2;k<=n;k++){
						int s=abs(a[k]-i)^abs(b[k]-j)^9,t=abs(c[k]-x2);
		    			if(s!=t){
		    				f=1;
		    				break;
						}
					}
					if(!f) cnt++;
				}
			}
		}
	printf("%d\n",cnt);
	return 0;
}
```

---

## 作者：sun30815 (赞：0)

# P5614 [MtOI2019]膜Siyuan 题解 ##
------------
~~不得不说，mosiyuan是不错的~~  
   先来看题的背景 讲述了一个Oier的游戏  
   ~~暂且少说废话~~  
### 题目描述

	既然大家都是学过Chinese 的，我这位0分选手也不好给大家普及了。

### 分析
	显然，是暴力
    O(m^3)的暴力如下，P 党
```Pascal
    var
    bb:boolean;
    ans,i,j,k,m,n,ii:longint;
    a,b,c:array[0..100]of longint;
	begin
    read(n,m);
    for i:=1 to n do
      read(a[i],b[i],c[i]);
      for i:=1 to m do
        for j:=1 to m do
          for k:=1 to m do
          begin
            bb:=true;
            for ii:=1 to n do
            begin
                if abs(i-a[ii])xor abs(j-b[ii]) xor abs(k-c[ii])<>9 then
                  bb:=false;
            end;
            if bb then begin writeln(i,' ',j,' ',k); exit; end;
          end;
    write(ans);
	end.
```
	浅显易懂的暴力
 	O(m^2*n)的暴力
```
	var
  f:array[0..10000]of longint;
  a,b,c:array[0..10]of longint;
  ans,i,j,m,n,x,y,z,ii,u,g,h,k:longint;
begin
  read(n,m);
  for i:=1 to n do read(a[i],b[i],c[i]);
  for i:=1 to m  do
    for j:=1 to m do
    begin
        u:=(abs(a[1]-i))xor(abs(b[1]-j)) xor 9;
        g:=0; h:=0;
        if (c[1]-u>=1)and(c[1]-u<=m) then
          g:=c[1]-u;
        if (u+c[1]>=1)and(u+c[1]<=m) then
          h:=u+c[1];
          // 有绝对值 g, h 双向讨论
        for k:=2 to n do
          if g<>0 then
          if (abs(a[k]-i))xor(abs(b[k]-j))xor(abs(c[k]-g))<>9 then
              begin g:=0; break; end;
        for k:=2 to n do
          if h<>0 then
          if (abs(a[k]-i))xor(abs(b[k]-j))xor(abs(c[k]-h))<>9 then
              begin h:=0; break; end;
        if g<>0 then  inc(ans);
        if h<>0 then  inc(ans);
        if (g<>0)and(h<>0)and(g=h) then dec(ans);
    end;
  write(ans);
end.
```
	然而 过了。


---

## 作者：QMQMQM4 (赞：0)

### 闲来无事写写水题题解

#### 先说说比赛经历

本来就少打一个多小时，然后div2的T1 naive了，调了30min，T2（就是此题）40pts的优化又 naive了，索性放弃。最后五十分钟打了个T3子集枚举和T4的3pts草草收场，体验极差。

于是我发誓要调出来。

#### 进入正题

首先异或运算有这么个性质，不知道的就没法做

### a ^ b ^ c=d -> a ^ b ^ d=c
然后做法就显然了，先搞两层循环，枚举题中的$x,y$，然后根据$x,y,c_{1}$
算出两个值记为当前答案$z_{1},z_{2}$，直接检查$z_{1},z_{2}$带入题中所给的$a_{i},b_{i},c_{i}$是否满足条件。只选$c_{1}$的原因是因为如果当前$z_{1},z_{2}$是答案，每组数据结果是一样的。

因为顺序枚举，连判重都省了，只用判断下$z1==z2$,如果这样只记一组答案。

#### CODE
```
#include<cstdio>
#include<iostream>
#include<cmath>
#include<map>
#include<cstring>
using namespace std;

const int maxn = 2001;
int a[10],b[10],c[10],n,m,ans;
int flag[10][2001][2001];


inline int read()
{
	char c = getchar();int x = 0,f = 1;
	while(c<'0'||c>'9') {if(c=='-')f = -1;c = getchar();}
	while(c>='0'&&c<='9') {x = x*10+c-'0';c = getchar();}
	return x*f;
}



int abss(int x)
{
	return x>0?x:-x;
}

bool check(int x,int y,int z)
{
	for(int i = 1;i<=n;++i)
		if((abss(a[i]-x)^abss(b[i]-y)^abss(c[i]-z))!=9)
			return false;
	return true;
}

int main()
{
	n = read();m = read();
	for(int i = 1;i<=n;++i)
		a[i] = read(),b[i] = read(),c[i] = read();
	for(int i = 1;i<=m;++i)
	{
		for(int j = 1;j<=m;++j)
		{
			int a1 = abss(i-a[1]);
			int b1 = abss(j-b[1]);
			int tot = a1^b1^9;
			int z1 = -tot+c[1];
			int z2 = tot+c[1];
			if(z1==z2) z2 = 0;
			if(check(i,j,z1)&&z1>0&&z1<=m) ans++;
			if(check(i,j,z2)&&z2>0&&z2<=m) ans++;
		}
	}
	printf("%d",ans);
	return 0;
}
```
csp即将到来，祝大家rp++，score++






---

## 作者：nth_element (赞：0)

想要更丰富的展示，请进入[我的BLog](https://www.cnblogs.com/nth-element/p/11788448.html)

***

吐槽：~~数据好像有点水~~，直接枚举到200可以得80 points。

另：我还是太弱了，比赛的时候只有90 points，#7死卡不过去，最后发现是没有判断 $z_1$ 和 $z_2$ 的范围……

***

## Subtask 1:

**Method**:

直接输出`4`，完。

***

## Subtask 2：

**Method**:

直接暴力枚举 $x$ , $y$ , $z$ ，判断是否满足一下关系即可：
$$
\forall i\in\left[1,n\right],s.t.\left |a_i-x\right|\bigoplus \left|b_i-y\right| \bigoplus \left|c_i -z\right|=9
$$
时间复杂度：$O(nM^3)$ （ $n\leq 5$ ，可以忽略 ）

可以通过 $60\%$ 的数据。

**Code**：

```cpp
#include<bits/stdc++.h>
#define int long long 
#define Maxn 10
using namespace std;
inline void read(int &x)
{
    int f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}
int n,M;
int ans=0;
int a[Maxn],b[Maxn],c[Maxn];
void solve1()
{
	int flag=1;
	for(int x=1;x<=M;x++)
	{
		for(int y=1;y<=M;y++)
		{
			for(int z=1;z<=M;z++)
			{
				for(int i=1;i<=n;i++)
				{
					if((((abs(a[i]-x))^(abs(b[i]-y)))^(abs(c[i]-z)))!=9)
					{
						flag=0;
						break;
					}
				}
				if(flag==1)
				{
					ans++;
				}else
				{
					flag=1;
				}
			} 
		}
	}
	printf("%lld\n",ans);
	return ;	
} 
signed main()
{
	read(n),read(M);
	for(int i=1;i<=n;i++)
	{
		read(a[i]);
		read(b[i]);
		read(c[i]);
	}
	ans=0;
	if(M<=200)
	{
		solve1();
		return 0;
	}
}
```

***

## Subtask 3:

**Method **:

考虑优化枚举。若满足一下的性质：
$$
A\bigoplus B\bigoplus C=D
$$
则显然可以得到：
$$
\begin{equation}
\begin{aligned}
& A\bigoplus B \bigoplus D\\
& =A \bigoplus B \bigoplus \left(A\bigoplus B\bigoplus C\right) \\
& = \left[\left(A \bigoplus B\right) \bigoplus \left(A\bigoplus B\right)\right]\bigoplus C\\
& \because x \bigoplus x=0,0\bigoplus x=x\\
& \therefore A \bigoplus B \bigoplus D =C
\end{aligned}
\end{equation}
$$
故只需要枚举 $x$ 、$y$ ，则：
$$
\begin{equation}
\begin{aligned}
& \left|c_1-z\right|=\left|a_1-x\right|\bigoplus \left|b_1-y\right| \bigoplus 9
\end{aligned}
\end{equation}
$$
我们设
$$
C=\left|a_1-x\right|\bigoplus \left|b_1-y\right| \bigoplus 9
$$
则：
$$
z_1=c_1-C,z_2=c_1+C
$$
最后只需要判断一下 $z_1$ 和 $z_2$ 是否满足以下性质即可:
$$
\forall i \in \left [2,n\right] ,s.t.\left |a_i-x\right|\bigoplus \left|b_i-y\right| \bigoplus \left|c_i -z_j\right|=9\text{且}z_j \in [1,M] \\
(j\in \{1,2\})
$$
时间复杂度：$O(nM^2)$ （ $n\leq 5$ ，可以忽略 ）

**Code**:

```cpp
#include<bits/stdc++.h>
#define int long long 
#define Maxn 10
using namespace std;
inline void read(int &x)
{
    int f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}
int n,M;
int ans=0;
int a[Maxn],b[Maxn],c[Maxn];
map<int,int>mp;
void solve1()
{
	int flag=1;
	for(int x=1;x<=M;x++)
	{
		for(int y=1;y<=M;y++)
		{
			for(int z=1;z<=M;z++)
			{
				for(int i=1;i<=n;i++)
				{
					if((((abs(a[i]-x))^(abs(b[i]-y)))^(abs(c[i]-z)))!=9)
					{
						flag=0;
						break;
					}
				}
				if(flag==1)
				{
					ans++;
				}else
				{
					flag=1;
				}
			} 
		}
	}
	printf("%lld\n",ans);
	return ;	
} 
void solve2()
{
	int flag1=1,flag2=1;
	for(int x=1;x<=M;x++)
	{
		for(int y=1;y<=M;y++)
		{
			mp.clear();
			int tmp=(((abs(a[1]-x))^(abs(b[1]-y)))^9);
			int zkkk=c[1]-tmp;
			int zwww=c[1]+tmp;
			if(zkkk>=1&&zkkk<=M)
			{
				for(int i=2;i<=n;i++)
				{
					if((((abs(a[i]-x))^(abs(b[i]-y)))^(abs(c[i]-zkkk)))!=9)
					{
						flag1=0;
						break;
					}
				}
				if(flag1==1&&mp.find(zkkk)==mp.end())
				{
					ans++;
					mp[zkkk]=1;
				}else
				{
					flag1=1;
				}
			}else
			{
				flag1=1;
			}
			if(zwww>=1&&zwww<=M)
			{
				for(int i=2;i<=n;i++)
				{
					if((((abs(a[i]-x))^(abs(b[i]-y)))^(abs(c[i]-zwww)))!=9)
					{
						flag2=0;
						break;
					}
				}
				if(flag2==1&&mp.find(zwww)==mp.end())
				{
					ans++;
				}else
				{
					flag2=1;
				}
			}else
			{
				flag2=1;
			}
		}	
	}
	printf("%lld\n",ans);
	return ;
}
signed main()
{
	read(n),read(M);
	for(int i=1;i<=n;i++)
	{
		read(a[i]);
		read(b[i]);
		read(c[i]);
	}
	ans=0;
	if(M<=200)
	{
		solve1();
		return 0;
	}
	else 
	{
		solve2();
		return 0;
	}
}
```









---

## 作者：HoshizoraZ (赞：0)

此题的一眼暴力，是直接枚举三元组的每一个元素，复杂度 $O(M^3)$，可以拿到 $60$ 分。

但是我们发现 $M \le 2000$，无法直接通过。

所以，我们需要观察这个题目中的一些性质。

看这个式子：

$$\mid a_i-x\mid ⊕ \mid b_i-y \mid ⊕ \mid c_i-z \mid \;=9$$

如果我们把原式异或上 $\mid a_i-x\mid ⊕ \mid b_i-y \mid$，那么会变成

$$\mid c_i-z \mid \;=9 \;⊕\mid a_i-x\mid ⊕ \mid b_i-y \mid$$

所以，我们可以枚举其中的两维，剩下一维的答案可以直接推出。

当然这是绝对值，因此一般有两个答案。

针对于此题，可以这样想：

- 通过枚举确定三元组的前两元，并利用它们以及判定三元组 $\{a_1,b_1,c_1\}$ 来得到两个待定第三元；

- 判定两个第三元是否相同，以及它们是否在 $[1,n]$ 的范围中；

- 把整合好的待定答案放到其它判定三元组 $\{a_i,b_i,c_i\}\;(2 \le i \le n)$ 中判断是否依旧成立；

- 对于两个第三元中的每一个，如果成立于所有判定三元组并且答案合法，那么将答案累加。

P.S. 以上的“判定三元组”即 $n$ 对给定的三元组。

参考代码：

```cpp
#include <cstdio>
#define reg register
#define INF 1e9
#define eps 1e-9
typedef long long ll;

int m, n, a[10], b[10], c[10], ans, ansa, ansb, now;
bool bbbb, bba, bbb, vis[2010];

inline int abs(reg int a){
	return a > 0 ? a : -a;
} 

int main(){
	
	scanf("%d%d", &n, &m);
	for(reg int i = 1; i <= n; i++)
		scanf("%d%d%d", &a[i], &b[i], &c[i]);
	
	for(reg int i = 1; i <= m; i++)
		for(reg int j = 1; j <= m; j++){
			bba = bbb = true;
			now = 9 ^ abs(a[1] - i) ^ abs(b[1] - j);
			ansa = now + c[1], ansb = -now + c[1];	// 因为是绝对值方程所以有两个（可能相等）的答案
			
			if(ansa == ansb) bbb = false;			// 去除相同的解 
			if(ansa > m || ansa < 1) bba = false;	// 去除不合法答案 
			if(ansb < 1 || ansb > m) bbb = false;
			
			for(reg int t = 2; t <= n; t++){			// 判断这两个解是否可以适用于其它解 
				if(bba && (abs(a[t] - i) ^ abs(b[t] - j) ^ abs(c[t] - ansa)) != 9) 
					bba = false;
				if(bbb && (abs(a[t] - i) ^ abs(b[t] - j) ^ abs(c[t] - ansb)) != 9)
					bbb = false;
			}
			
			// 判断两个答案分别是否依旧成立，同时累计 
			if(bba) ans++;
			if(bbb) ans++;
		}
			
	printf("%d\n", ans);	

	return 0;
}
```

---

## 作者：TEoS (赞：0)

比赛中没看到小于等于$M$，30pts调了3.5h都没调对……（~~草，我是怎么没看到的，为什么我调不对还不再看一遍题面~~）


------------
**思路分析**

#### 60pts

~~根据题目概况的暴力可过~~可以想到枚举$x,y,z$，用题面给的模板（大雾），时间复杂度$O(M^3)$，可以拿到60pts。

#### 100pts

显然一个已知数异或上一个未知数等于一个已知数，这个未知数只会有一个解；换句话说，我们可以通过异或的逆运算，还是异或，来求出这个未知数。这样，我们可以通过枚举$x,y$，然后求出$z$，降低复杂度到$O(M^2)$，拿到100pts。

**具体实现**

1. 枚举$x,y,k$（k为第几个三元组{$a,b,c$}），计算出$abs(a[k]-x)$ $xor$ $abs(b[k]-y)$ $xor$ $9$，这个答案就是$abs(c[k]-z)$，设其为$p$。
1. 显然，$p$有两个可能的值，并且有可能这两个值都是满足条件的。我们可以分别尝试着两个值，判断是否满足条件。注意，当两个值都满足条件时，这两个值不能相等，即$p!=0$。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int N=100; 
int n,m,ans;
int a[10],b[10],c[10];
bool check(int x,int y,int z)
{
	for(int i=1;i<=n;i++)
		if((abs(a[i]-x)^abs(b[i]-y)^abs(c[i]-z))!=9)
			return 0;
	return 1;
}//判断是否都为9
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&a[i],&b[i],&c[i]);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=m;j++)
		{
			int p=abs(a[1]-i)^abs(b[1]-j)^9;
			if(c[1]+p<=m && c[1]+p>0 && check(i,j,c[1]+p))//要在(0,m]内
				ans++;
			if(c[1]-p<=m && c[1]-p>0 && check(i,j,c[1]-p) && p)
				ans++;
		}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Starlight237 (赞：0)

枚举两个数，利用异或的交换律以及性质$a\ xor\ a=0$，可以得到$abs(c[1]-z)=9\ xor\ abs(a[1]-x)\ xor\ abs(b[1]-y)$（事实上，利用异或的逆运算是其本身亦可以推出）。

分类讨论把z解出来，然后检验$i=2,3,...,n$的情形是否全部满足即可。

舍解、去重细节参见代码，较简单。但是完全没必要set啥的……
```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
extern "C"{
namespace io{
	#define IOSIZE 1000
	static char in[IOSIZE],*p=in,*pp=in,out[20],*q=out,ch[20],*t=ch;
	inline char gc(){return p==pp&&(pp=(p=in)+fread(in,1,IOSIZE,stdin),p==pp)?EOF:*p++;}
	inline int read(){
		reg int x=0;reg char ch;
		while(!isdigit(ch=gc()));
		while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=gc();
		return x;
	}
	inline void write(long long x){
		!x&&(*q++='0'),x<0&&(*q++='-',x=-x);
		while(x)*t++=x%10+48,x/=10;
		while(t!=ch)*q++=*--t;
	}
	inline void flush(){fwrite(out,1,q-out,stdout);}
}}
#define rd io::read
#define wt io::write
static int n,m,ans,a[6],b[6],c[6];
int main(){
	n=rd(),m=rd();
	for(reg int i=1;i<=n;++i)a[i]=rd(),b[i]=rd(),c[i]=rd();
	for(reg int x=1;x<=m;++x)
		for(reg int y=1;y<=m;++y){
			int A=abs(a[1]-x),B=abs(b[1]-y),C=9^A^B;
			if(C<0)continue;
			int flag=1,z=c[1]-C;
			if(z>0&&z<=m)for(reg int i=2;i<=n;++i)flag&=(abs(a[i]-x)^abs(b[i]-y)^abs(c[i]-z))==9;
			else flag=0;
			ans+=flag;
			z=c[1]+C,flag=1;
			if(z>0&&z<=m)for(reg int i=2;i<=n;++i)flag&=(abs(a[i]-x)^abs(b[i]-y)^abs(c[i]-z))==9;
			else flag=0;
			ans+=flag;
			ans-=(flag&&C==0);
		}
	wt(ans);
	io::flush();
	return 0;
}
```

---

