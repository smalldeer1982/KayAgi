# Barracuda

## 题目背景

小正方形的冒险旅途，并不顺利。

一路上，小正方形看到了壮美秀丽的小岛被污染，看到了雄伟壮观的火山，还碰到了许许多多的敌人。

眼下，小正方形正在对付一个巨大的三角形。

## 题目描述

大三角形给小正方形讲起自己的过去：过去的它是一个挖宝工，后来被黑暗之主污染才会落到此番境地。

它也希望小正方形去战胜黑暗之主，不过限于黑暗之主的眼线密布，因此必须给小正方形设置障碍才能骗过那些“眼线”。

他给小正方形的问题是：它有 $n$ 个小三角形，每个小三角形有一定的质量，它对这些三角形进行了 $n + 1$ 次称量，然而由于托盘天平(?)的问题，有一次称量的结果是有误的。

现在，大三角形想要知道最重的小三角形的 编号。

一组输入是合法的，当且仅当输入满足以下条件：

不存在一组 $i$,$j$，使得当我们**假定**第 $i$ 条称量数据有误时能求出一种合法方案且我们**假定**第 $j$ 条称量数据有误时也能求出一种合法方案。

合法方案定义如下：

1、最重的三角形只有一个。

2、不存在重量不确定的三角形。

3、所有三角形的重量均为正整数。

## 说明/提示

样例一：

若第一次称量结果错误，则无法得出正确解。

若第二次称量结果错误，则第二个小三角形重量为负，显然不对。

若第三次称量结果错误，我们得出 $1$ 号小三角形重量为 $2$，$2$号小三角形重量为 $3$，$2$号小三角形最重。

本题采用捆绑测试，共有三个 $subtask$，描述如下：

$subtask 0 - 30Pts$ 保证小三角形的重量 <= 20且 $n <= 5$，在这个 $subtask$ 中，你每通过一个点可获得 $10$ 分。

$subtask 1 - 30Pts$ 保证小三角形的重量 <= 100 并且 $n <= 100$，数据为随机生成。

$subtask 2 - 40Pts$ 保证小三角形的重量 <= 100 并且 $n <= 100$

在后两个 $subtask$ 中，你必须通过所有数据才能得分。

对于 $100\%$ 的数据， $1 <= m <= n$

## 样例 #1

### 输入

```
2
1 1 2
2 1 2 5
2 1 2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
2
1 1 2
2 1 2 4
2 1 2 5```

### 输出

```
2```

## 样例 #3

### 输入

```
2
1 1 2
2 1 2 6
2 1 2 5```

### 输出

```
illegal```

# 题解

## 作者：Wen_kr (赞：12)

#### Subtask -1

我会输出 `illegal` ，预期得分 10 Pts

#### Subtask 0

我会枚举，预计得分 30 ~ 50 Pts

#### Subtask 1

我会高斯消元，可是我判 `illegal` 的情况漏了一些，预计得分 30 ~ 60 Pts

#### Subtask 2

考虑枚举是哪一次称量结果有误，然后暴力跑高斯消元，按题意判无解。 时间复杂度 $O(n^4)$

---

## 作者：LevenKoko (赞：8)

## 同步发表于博客:[Luogu P5027 【Barracuda】](https://www.cnblogs.com/zhenglw/p/10902575.html )

首先这道题给了你n+1个**一次方程**，n个**未知数**

其中有一个方程是错误的

求解在合法的前提下最大的未知数是多少...

~~显然高斯消元...~~

关注到$n≤100$所以$n^4$的算法是极限

高斯消元复杂度是$n^3$所以我们可以**暴力枚举**那个方程是错误的

之后判断合法性即可...

总之也不是很难啊，关键是不要忘记illegal...刚开始程序末尾的illegal忘了然后就Subtask2 WA了一个点...

直接看代码直观一点呢

```cpp
#include<cstdio>
#include<iostream>
#include<cstring> 
#include<cmath>
#define writeln(x)  write(x),puts("")
#define writep(x)   write(x),putchar(' ')
using namespace std;
inline int read(){
	int ans=0,f=1;char chr=getchar();
	while(!isdigit(chr)){if(chr=='-') f=-1;chr=getchar();}
	while(isdigit(chr)){ans=(ans<<3)+(ans<<1)+chr-48;chr=getchar();}
	return ans*f;
}void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}const double eps=1e-11; 
int n,w[105],p[105][105],tot,ANS,lst[105],lst_ans;
double a[105][105],ans[105];
inline void cmax(int &a,int b){if(a<b) a=b;}
inline void Gauss(){//高斯消元+回代 
    for(int i=1;i<=n;i++){
        int maxn=i;
        for(int j=i+1;j<=n;j++) if(fabs(a[j][i])>fabs(a[maxn][i])) maxn=j;
        for(int j=1;j<=n+1;j++) swap(a[maxn][j],a[i][j]);
        for(int j=n+1;j>=i;j--)
            for(int k=i+1;k<=n;k++)
                a[k][j]-=a[k][i]/a[i][i]*a[i][j];
    }
    for(int i=n;i>=1;i--){
        for(int j=i+1;j<=n;j++)
            a[i][n+1]-=a[j][n+1]*a[i][j];
        a[i][n+1]/=a[i][i];
    }
    for(int i=1;i<=n;i++)
        ans[i]=a[i][n+1];
}
int main(){
	n=read();
	for(int i=1,t;i<=n+1;i++){
		t=p[i][0]=read();
		for(int j=1;j<=t;j++)	p[i][j]=read();
		w[i]=read();
	}int ppp=0;
	for(int wr=1;wr<=n+1;wr++){//第wr(ong)次出现错误答案
		tot=0;memset(a,0,sizeof(a));
		for(int i=1;i<=n+1;i++)
			if(i!=wr){
				++tot,a[tot][n+1]=w[i];
				for(int j=1;j<=p[i][0];j++)a[tot][p[i][j]]=1;
			}
		Gauss();//构造方程+高斯消元
//------------------------------------------------------------------------		
		ANS=0;tot=0;int ff=0;
		for(int i=1;i<=n;i++){
			int flag=0;
			for(int j=1;j<=n;j++)
				if(fabs(a[i][j])>eps) flag=1;
			if(flag==0) {ff=1;break;}
		}if(ff) continue;//检查1_唯一解
//------------------------------------------------------------------------		
		for(int i=1;i<=n;i++)	
			if(fabs(ans[i]-(int)ans[i])<eps&&ans[i]>0) 	
				lst[i]=(int)ans[i];	
			else 	{ff=1;break;}//检查2_整数
		if(ff) continue;
		for(int i=1;i<=n;i++)	cmax(ANS,lst[i]);
		for(int i=1;i<=n;i++)   if(ans[i]==ANS) ++tot,ff=i;//检查3_最大值唯一
		if(tot>1) 	continue;
//------------------------------------------------------------------------
		if(ppp){puts("illegal");return 0;}//多种可能方案 
		lst_ans=ff;ppp=1;
	}
	if(!ppp) puts("illegal");//没有可能方案 
	else writeln(lst_ans);
	return 0;
}

```

---

## 作者：chenxia25 (赞：8)

一道有趣的线性代数题。首先可以枚举错误方程，每次高消跑一遍，$\mathrm O\!\left(n^4\right)$ 其中 $n\leq 100$，卡着时限过就没有意思了（但好像大多数人都是这么做的？这可能是难度只有蓝的原因）。这篇题解讲的是 $\mathrm O\!\left(n^3\right)$ 的做法。

考虑解线性方程组的另一个解法：克莱姆法则。对于系数矩阵为方阵的线性方程组 $A\pmb x=\pmb b$，我们有 $x_i=\dfrac{|A_i(\pmb b)|}{|A|}$。直接按照这个做需要求 $\mathrm O(n)$ 次行列式，这就四方了。再者，系数矩阵可能没满秩，也就是 $|A|=0$，那就做不了了。而且行列式的值可能会很大很大，爆 `double`（虽说消元求行列式仅包含乘法，可以取对数，但那还是麻烦啊）。不难发现普通情况下克莱姆法则解方程组漏洞百出，但是我们还是能修补复杂度的漏洞。

数学书上讲的东西总是很形式化的，那 $|A_i(\pmb b)|$ 这东西看起来就没有什么快速求的好思路。但你把 $\pmb b$ 拖拽到最后一列（也就是若干次列对换）就有灵感了：要求的 $|A_i(\pmb b)|$ 以及 $|A|$ 这 $n+1$ 个行列式刚好是增广矩阵分别**去掉每一列**所得矩阵的行列式乘上 $\pm1$（$\pm1$ 是 trivial 的，不去管它）。去掉一列的行列式，想到了什么？余子式！但是余子式要求去掉一行一列，现在一列有了，对于一行容易想到在增广矩阵下面随便补一行（补完之后恰好又是方阵！），这样要求的就是 $(n+1,1\sim n+1)$ 余子式。

要计算一个方阵每处的余子式，只要计算方阵的伴随矩阵，那么有 $\mathrm{adj}A=|A|A^{-1}$，其中行列式和逆矩阵都是好求的。但同时有个条件，那就是方阵行列式非零。但最后一行是我们自己补的，在增广矩阵行满秩的前提下可以刻意构造一行使得 $n+1$ 阶大方阵满秩。然后发现，克莱姆法则中两个余子式之比，恰好把伴随矩阵公式中的 $|A|$ 约掉了，只剩逆矩阵元素之比！那就不用担心爆 `double` 了。总结一下，克莱姆法则解线性方程组有几个漏洞：只能解系数矩阵为方阵的方程组，如果系数矩阵不满秩还判断不了无解还是无限解，无限解还没法求通解，还得动脑子在增广矩阵下面新加一行使得 $n+1$ 阶方阵满秩。

虽然克莱姆法则很不好，但是我们还是能发现一个优点：它把 $\mathrm O\!\left(n^2\right)$ 处的余子式都求出来了，但我们只用到了 $\mathrm O(n)$ 处，这说明这个算法很可扩展。回来看到该题，一开始列出一个 $n+1$ 阶增广矩阵，每次要去掉一行得到要求的 $n\times(n+1)$ 增广矩阵。等等，去掉一行？那刚好可以让这一行充当上述算法的新加的一行呀！这样一来不难发现，要解 $\mathrm O(n)$ 次线性方程组，每次 $\mathrm O(n)$ 个余子式，一共要 $\mathrm O\!\left(n^2\right)$ 个余子式，而它们恰好不重不漏地分布在伴随矩阵里！

再看看该题有没有撞上克莱姆法则的几个缺点。系数矩阵为方阵没错了，如果系数矩阵不满秩也根本不用去管它。但是并没有保证 $n+1$ 阶增广矩阵满秩！事实上，我们可以证明若不满秩，答案一定是 $\texttt{illegal}$。如果有自由变量，那把 $n+1$ 个方程合起来了都有自由变量了，再去掉一个必定没有唯一解。如果没有自由变量且秩等于 $n$，那么 $n+1$ 个方程有唯一解，又分成两类：如果解不合法，那去掉一个方程要么无限解，要么是这个不合法的唯一解，肯定不行；如果解合法，我们努力找到去掉两个方程的时候都得到唯一解，满足这个事情当且仅当去掉的是「冗余的」，即可以被其它行向量线性表出的行，由于 $n+1$ 行没有满秩，必定有至少一个，而「说明 / 提示」最后一行说 $m\geq1$，也就是不可能有零行，那线性表出式的 RHS 中必定有至少一项，那移个项即可得到另一个满足要求的行。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
const double eps=1e-6;
const int N=110;
int n;
double a[N][2*N];
void times(int x,double v){
	for(int i=1;i<=2*n+2;i++)a[x][i]*=v;
}
void swp(int x,int y){
	for(int i=1;i<=2*n+2;i++)swap(a[x][i],a[y][i]);
}
void tadd(int x,double v,int y){
	for(int i=1;i<=2*n+2;i++)a[y][i]+=a[x][i]*v;
}
void prt(){
	for(int i=1;i<=n+1;i++)for(int j=1;j<=2*n+2;j++)cout<<a[i][j]<<" \n"[j==2*n+2];
	puts("--------------------");
}
void gauss(){
	for(int i=1;;i++){
		int row=0,col=0;
		for(int j=1;j<=n+1;j++){
			for(int k=i;k<=n+1;k++)if(abs(a[k][j])>eps){row=k,col=j;break;}
			if(row)break;
		}
		if(!row)break;
		swp(i,row);
		for(int j=1;j<=n+1;j++)if(i!=j)tadd(i,-a[j][col]/a[i][col],j);
		times(i,1/a[i][col]);
//		prt();
	}
}
double M(int x,int y){return a[y][x+n+1]*(x+y+(y!=n+1)*(n-y&1)&1?-1:1);}
int main(){
	cin>>n;
	for(int i=1;i<=n+1;i++){
		int m;
		cin>>m;
		while(m--){
			int x;
			scanf("%d",&x);
			a[i][x]=1;
		}
		int x;
		scanf("%d",&x);
		a[i][n+1]=x;
	}
	for(int i=1;i<=n+1;i++)a[i][i+n+1]=1;
//	prt();
	gauss();
	for(int i=1;i<=n+1;i++)if(abs(a[i][i]-1)>eps)return puts("illegal"),0;
	vector<int> legal;
	for(int i=1;i<=n+1;i++){
		if(abs(M(i,n+1))<=eps)continue;
		bool flg=true;multiset<int> st;
		for(int j=1;j<=n;j++){
			double x=M(i,j)/M(i,n+1);
			flg&=x>.5&&abs(round(x)-x)<=eps;
			st.insert(round(x)+.5);
		}
		flg&=st.count(*--st.end())==1;
		if(flg)legal.pb(i);
	}
//	cout<<legal.size()<<"!\n";
	if(legal.size()!=1)return puts("illegal"),0;
	pair<int,int> mx(0,0);
	for(int i=legal[0];i<=legal[0];i++){
		for(int j=1;j<=n;j++){
			double x=M(i,j)/M(i,n+1);
			mx=max(mx,mp(int(round(x)+.5),j));
		}
	}
	cout<<mx.Y;
	return 0;
}
```

---

## 作者：Poetic_Rain (赞：5)

适合初学高斯消元

题目还是很好理解的，每次给定几个三角形和重量，就可以建立$n+1$个方程，转化为高斯消元模板

想一想高斯消元的模板长什么样子，一个$n*(n+1)$的矩阵，但是按照上面的思路来建立的话，会搞出来一个$(n+1)*(n+1)$的矩阵，那么就会遇到一些坑

思路就是假设每一行都是错误的情况

1. 并不是每一个编号的系数为$1$，最开始我这里想了很久，可以抓多次同个三角形

2. 如何假设是$x$行出错，对于高斯消元时的处理，并不能直接$continue$当前行，还是应该存储一个模板矩阵

然后就继续说如何判断题目中的条件

1. 最重的三角形只有一个，我们只需要在回代过后，对$maxx$的个数记录一下即可

2. 不存在重量不确定的三角形，说明该方程在转化为“上三角形”之后，出现了$0=0$这类恒等式，表示无数组解，当然无解也是这样

3. 三角形重量是正整数，我们用$duoble$来存储答案，如果$int$强制转换后的值比$duoble$类型小，说明不是正整数

4. 对于不是合法方案，其实就是相当于当$i$错误时，我们能求出来一组解,当$j$错误时，我们也能求出来一组解，说明$illegal$


```
#include<bits/stdc++.h>
using namespace std;
const double eps=1e-6;
double a[150][150];
double b[150][150];
int n,m,x;
int maxx,pre;
int gauss() {
	int c,r;
	for(c=1,r=1; c<=n; c++) {
		int t=r;
		for(int i=r; i<=n; i++) {
			if(fabs(a[t][c])<fabs(a[i][c])) t=i;
		}
		if(fabs(a[t][c])<eps) return 0;
		for(int i=c; i<=n+1; i++) swap(a[r][i],a[t][i]);
		for(int i=n+1; i>=c; i--) a[r][i]/=a[r][c];
		for(int i=r+1; i<=n; i++) {
			if(fabs(a[i][c])>eps) {
				for(int j=n+1; j>=c; j--) a[i][j]-=a[r][j]*a[i][c];
			}
		}
		r++;
	} //高斯消元模板 
	for(int i=n; i>=1; i--) {
		for(int j=i+1; j<=n; j++) {
			a[i][n+1]-=a[j][n+1]*a[i][j];
		}
		if(a[i][n+1]<eps||((int)a[i][n+1])<a[i][n+1]) return 0; //无解或是重量为小数的情况 
	} //回代 
	int sum;
	maxx=-1;
	for(int i=1; i<=n; i++) {
		if((int)a[i][n+1]>maxx) maxx=a[i][n+1],sum=i;
	} //记录最值 
	int num=0;
	for(int i=1; i<=n; i++) {
		if((int)a[i][n+1]==maxx) num++; //最值数量 
	}
	if(num>1) return 0;
	return sum;
}
int tot;
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n+1; i++) {
		scanf("%d",&m);
		for(int j=1; j<=m; j++) {
			scanf("%d",&x);
			b[i][x]++;
		}
		scanf("%d",&x);
		b[i][n+1]=x*1.0;
	} //存储初始的(n+1)*(n+1)的矩阵 
	for(int i=1; i<=n+1; i++) {
		int cnt=0;
		for(int h=1; h<=n+1; h++) {
			if(h==i) continue;
			cnt++;
			for(int k=1; k<=n+1; k++) {
				a[cnt][k]=b[h][k];
			}
		} //存储一个n*(n+1)的矩阵 
		int p=gauss();
		if(p==0) continue; //无解或者无数组解 
		else tot++,pre=p; //tot表示有几组解，pre是答案 
	}
	if(tot>1||tot==0) puts("illegal"); //全部无解或者出现多组解 
	else cout<<pre;  
	return 0;
}
```

[P4035 [JSOI2008]球形空间产生器](https://www.luogu.com.cn/problem/P4035)

感觉很多地方都介绍了这一道题，质量挺好的，建议做一做

---

## 作者：wubaiting2020 (赞：2)

因为这道题很有趣 ~~（其实是我毒了13遍才过)~~ ，同时也为了写给自己供复习，于是决定写篇题解  
首先，本题n<=100，而高斯消元n^3，如果暴力枚举错误的式子就是n^4，是卡得过去的  
这道题的细节处理很多，由题意可以得出这样几个无解情况  
1.判断答案是否为正整数  
2.是否有多个最重三角形  
3.重量不确定，即有多种删掉一个式子的情况合法  
于是，上代码 ~~（不喜勿喷）~~ 
```cpp
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;
int n;
int a[105][105];
double b[105][105];
int ans;
int ansbj; 
int Gauss()
{
    for(int i=1;i<=n;i++)
    {
        int no=i;
        for(int j=i+1;j<=n;j++)if(abs(b[j][i])>abs(b[no][i]))no=j;
        for(int j=1;j<=n+1;j++)swap(b[i][j],b[no][j]);
        double x=b[i][i];
        for(int j=i;j<=n+1;j++)b[i][j]/=x;
        for(int j=1;j<=n;j++)
        {
            double y=b[j][i];
            for(int k=1;k<=n+1;k++)
            if(i!=j)
            b[j][k]-=y*b[i][k];
        }
    }//高斯消元模版，此时第i个未知数的解存在b[i][n+1]中 
    int num;
    for(int i=1;i<=n;i++)
    {
        num=0;
        for(int j=1;j<=n+1;j++)if(!b[i][j])num++;
        if(num==n+1)return 0;//全为0,无数解 
    }
    for(int i=1;i<=n;i++)if(b[i][n+1]<=0)return 0;//是否为正数 
    for(int i=1;i<=n;i++)if(b[i][n+1]!=(int)b[i][n+1])return 0;//是否为整数 
    double maxx=-0x3f3f3f3f;int bjbj=0;
    for(int i=1;i<=n;i++)maxx=max(maxx,b[i][n+1]);//求出最重三角形 
    for(int i=1;i<=n;i++)if(b[i][n+1]==maxx){if(bjbj)return 0;maxx=b[i][n+1];bjbj=i;}//判断是否有多个最重三角形
  	//如果到这里还没有return就说明答案合法 
    return bjbj;//返回最重三角形的编号 
}
int main()
{
	int k,x;
    scanf("%d",&n);
    for(int i=1;i<=n+1;i++)
    {
        scanf("%d",&k);
        for(int j=1;j<=k;j++)
        {
            scanf("%d",&x);
            a[i][x]=1;
        }
        scanf("%d",&a[i][n+1]);
    }
    for(int i=1;i<=n+1;i++)
    {
    	swap(a[i],a[n+1]);//把错的式子换到第n+1行 
        for(int j=1;j<=n;j++)
        for(int k=1;k<=n+1;k++)b[j][k]=a[j][k];//将删去错误式子的矩阵存在b中 
        swap(a[i],a[n+1]);//换回去
        int nobj=Gauss();//判断是否合法 
        if(nobj)
        {
            if(ansbj){printf("illegal");return 0;}//有多种情况合法 
            ans=nobj;ansbj=1;//
        }
    }
    if(!ansbj)printf("illegal");else printf("%d",ans);//判断是否有合法结果 
    return 0;
}
```


---

## 作者：FutureThx (赞：2)

高斯消元的板题

### 题意

给出 $n + 1$ 多元一次方程，共 $n$ 个未知量，其中有一个是错误的方程，现在需要你把正确方程组中解最大的编号输出

### 思路

首先考虑如何构造方程矩阵，对于每一行的输入，都对这个编号在方程中的系数则都为 $1$ ，其他全为 $0$ ，所以显然方程系数不会超过 $1$

然后可以枚举这 $n + 1$ 个方程中的某一个为错误的，如果发现多解或无解则这次枚举出的矩阵不是正确的，最终输出包含唯一解的矩阵中解最大的编号，如果枚举发现没有这样的矩阵，则输出 ```illegal```


具体实现看代码
### 代码

```cpp
#include <iostream>
#include <cmath>
#include <cstdio>
#define eps 1e-7
#define MAX_N 1010
using namespace std;
double c[MAX_N][MAX_N],b[MAX_N];
int n;
bool integer(double s){
    if(abs(round(s) - s) < eps) 
        return true;
    return false;
}
int Gauss(int kill){
    double c2[MAX_N][MAX_N],b2[MAX_N];
    int t = 0;
    for(int i = 1;i <= n + 1;i++){
        if(kill == i)continue;
        t++;
        for(int j = 1;j <= n;j++)
            c2[t][j] = c[i][j];
        b2[t] = b[i];
    }
    double rate;
    for(int i = 1;i <= n;i++){
        for(int j = i;j <= n;j++)
            if(fabs(c2[j][i]) > 1e-8)
                swap(c2[i],c2[j]),swap(b2[i],b2[j]);
        if(c2[i][i] == 0)
            return -1;
        for(int j = 1;j <= n;j++){
            if(i == j)continue;
            rate = c2[j][i] / c2[i][i];
            for(int k = i;k <= n;k++)
                c2[j][k] -= c2[i][k] * rate;
            b2[j] -= b2[i] * rate;
        }
    }
    int maxn = -1,maxt = 0,maxs = -1;
    for(int i = 1;i <= n;i++){
        double ans = b2[i] / c2[i][i];
        if(ans < 0 || integer(ans) == false)return -1;
        if(ans > maxn)maxn = ans,maxt = 1,maxs = i;
        else if(ans == maxn)maxt++;
    }
    if(maxt != 1)return -1;
    return maxs;
}
int main(){
    cin >> n;
    for(int i = 1;i <= n + 1;i++){
        int m;
        cin >> m;
        while(m--){
            int x;
            cin >> x;
            c[i][x] = 1;
        }
        cin >> b[i];
    }
    int t = 0,ans = -1;
    for(int i = 1;i <= n + 1;i++){
        int x = Gauss(i);
        if(x != -1){
            ans = x;
            t++;
        }
    }
    if(t != 1){
        cout << "illegal" << endl;
        return 0;
    } 
    cout << ans << endl;
    return 0;
}
```

### 后记

$Updata \ 2021.1.30 \ :$ 完成题解，求管理员通过

---

## 作者：_anll_ (赞：1)

算是博客爆改专栏后的第一篇题解。
## 题目大意
给你 $n+1$ 个含有 $n$ 个未知量的方程，其中有 $1$ 个方程是错的，问你该方程是否合法，如果不合法输出 `illegal`，否则输出合法时最大解的编号。

## 大体思路
一开始看到题面毫无思路，只能想到 $O(n^4)$ 的暴力，结果一看数据范围 $n \le 100$，发现真的可以过。于是这道题就成为了一个高斯消元模板经验题。

考虑暴力枚举每个方程为错的情况，再跑一次高斯消元看是否符合题意就好了。判断部分在代码中已给出注释，不在此赘述。

## 代码演示
大体思路就是这样，如果有不理解或不清晰的地方可以结合代码理解。
```cpp
#include<iostream>
#include<math.h>
#define int long long
using namespace std;
int n,ans;
double mp[105][105],num[105][105],zero=1e-7;
bool gauss(){
	for(int i=1;i<=n;i++){
		int now=i;
		for(int j=i;j<=n;j++){
			if(fabs(num[j][i])>zero){
				now=j;break;
			}
		}
		if(now!=i) swap(num[i],num[now]);
		if(fabs(num[i][i])<zero) return 0;//该方程无解/无唯一解 
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			double t=num[j][i]/num[i][i];
			for(int k=i;k<=n+1;k++){
				num[j][k]-=num[i][k]*t;
			}
		}
	}
	int an=0,ann=0,len=0;
	for(int i=1;i<=n;i++){
		num[i][n+1]/=num[i][i];
		//如果出现负数/小数 
		if(num[i][n+1]<0||((int)num[i][n+1])!=num[i][n+1]) return 0;
		if(num[i][n+1]>an)
			an=num[i][n+1],ann=i,len=1;
		else if(num[i][n+1]==an) len+=1;
	}
	if(len>1) return 0;//如果最大值出现了两次 
	ans=ann;
	return 1;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	int len,awa;
	for(int i=1;i<=n+1;i++){
		cin>>len;
		for(int j=1;j<=len;j++){
			cin>>awa;
			mp[i][awa]=1;
		}
		cin>>awa;
		mp[i][n+1]=awa;
	}
	int tot=0;
	for(int i=1;i<=n+1;i++){
		bool state=0;
		for(int j=1;j<=n+1;j++){
			if(j==i){
				state=1;
				continue;
			}
			for(int k=1;k<=n+1;k++)
				num[j-state][k]=mp[j][k];
		}
		tot+=gauss();
	}
	if(tot!=1) cout<<"illegal";//如果正确方程组不唯一/没有成立的方程组 
	else cout<<ans;
	return 0;
}
```

---

## 作者：kczw (赞：1)

# 题意简述
给定一个有 $n+1$ 个有 $n$ 个未知量的方程的方程组，其中有且仅有一方程为假。问该方程组是否合法，以及合法时最大的未知量值。
# 思路
因为 $n\le100$，且高斯消元的时间复杂度为 $O(n^3)$，所以完全可以暴力枚举某一方程为假然后跑高斯消元。

然后注意下些特殊情况，像是最大值是否唯一，未知量是否为正整数，是否有唯一解。
# 实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int n,m,ANS,tot,b[N][N];
double a[N][N],eps=1e-7;
bool solve(){
    double ans=0;
    int id=0,num=0;
    for(int i=1;i<=n;i++){
        int r=i;
        while(r<=n&&fabs(a[r][i])<eps)//查找第一个第 i 未知量系数不为 0 的方程。
        	r++;
        if(r>n)return 0;//高斯消元目前处理的方程组内无有系数的第 i 未知量，即此未知量无唯一解，不合法，返回 false
        if(r!=i)swap(a[r],a[i]);
        for(int j=1;j<=n;j++){
            if(i==j)continue;
            double t=a[j][i]/a[i][i];
            for(int k=i;k<=n+1;k++)
                a[j][k]-=t*a[i][k];
        }
    }
    for(int i=1;i<=n;i++){
    	a[i][n+1]/=a[i][i];
        if(a[i][n+1]<eps)//为负数，返回false
        	return 0;
        if(fabs(a[i][n+1]-(int)a[i][n+1])>eps)
			return 0;//为小数，返回false
        if(a[i][n+1]>ans){判最大值
            ans=a[i][n+1];//记最大值
            id=i;//记编号
            num=1;
        }
        else if(fabs(a[i][n+1]-ans)<eps)//与之前的最大值相同，计数增一
            num++;
    }
    if(num>1)return 0;//最大值不唯一，返回false
    ANS=id;//方程式合法，记答案
    return 1;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n+1;i++){
        scanf("%d",&m);
        for(int j=1,v;j<=m;j++){
            scanf("%d",&v);
            b[i][v]=1;
        }
        scanf("%d",&b[i][n+1]);
    }
    for(int l=1;l<=n+1;l++){//枚举假方程
        for(int i=1;i<=n+1;i++)
        for(int j=1;j<=n+1;j++)
            a[i-(i>l)][j]=b[i][j];//赋值到处理高斯消元的数组
        if(solve())tot++;//记录解的数量
    }
    if(tot!=1)printf("illegal");//解不唯一
    else printf("%d",ANS);
    return 0;
}
```

---

## 作者：SegTre (赞：1)


# 思路
发现题解区没有最小公倍数消元的，这里给一篇供参考。

比较裸的解方程题目，多了解为正整数的条件，用最小公倍数消元更好判断。

用的是高斯约旦消元法，在消元的过程中没有直接乘上系数比例，而是求出最小公倍数，保证消元过程中系数为整数。原理如下（当然，作为小学知识各位可以跳过）：

假设我们要消去第 $col$ 个未知数，保留第 $x$ 个方程的系数，将第 $y$ 行的该未知数系数变为 $0$。

设 $a=A_{x,col}$，$b=A_{y,col}$，$d=\gcd(a,b)$

那么 $\operatorname{lcm}(a,b)= a*b/d$

要把 $A_{y,col}$ 消为 $0$，可以将第 $y$ 个方程各系数变为 （显然都是整数）

$$A_{y,i}=a/d*A_{y,i}-b/d*A_{x,i}$$

对于 $i=col$ 有

$$A_{y,col}=a/d*A_{y,c ol}-b/d*A_{x,col}=0$$

然后注意一些细节：方程中系数可能为负数，因此求最大公因数时要取绝对值；题目要求只能有一个最大解，记得特判；题目要求输出的是编号而不是重量。

# Code
主要改了一下 $remove$ 函数（用于实现消元），其他部分没有很大改动。

~~实测开 O2 跑的飞快~~

```cpp
#include<cstdio>
#include<cctype>
#define int long long
using namespace std;
inline int read() {
	int res;char c;
	while(!isdigit(c=getchar()));res=c^48;
	while(isdigit(c=getchar())) res=(res<<3)+(res<<1)+(c^48);
	return res;
}
int n,maxn,ans,A[105][105],data[105][105];
int abs(int x) {return x>0? x:-x;}
int gcd(int a,int b) {
	return b? gcd(b,a%b):a;
}
inline void swap(int &x,int &y) {
	int tmp=x;
	x=y,y=tmp;
}
inline void exchange(int x,int y) {
	for(int i=1;i<=n+1;++i) swap(A[x][i],A[y][i]);
}
inline bool remove(int x,int y,int col) { // 加减消元 
	int a=A[x][col],b=A[y][col],d=gcd(abs(A[x][col]),abs(A[y][col]));
	for(int i=1;i<=n+1;++i) A[y][i]=a/d*A[y][i]-b/d*A[x][i]; // 最小公倍数消元 
	// 系数约分，防止溢出 
	d=0;
	for(int i=1;i<=n;++i) d=gcd(d,abs(A[y][i]));
	if(d==0) return 0;
	if(abs(A[y][n+1])%d!=0) return 0; // 由裴蜀定理可知，不能整除则没有整数解 
	for(int i=1;i<=n+1;++i) A[y][i]/=d;
	return 1;
}
bool Gauss(int del) {
	for(int i=1,row=0;i<=n+1;++i) {
		if(i==del) continue;
		row++;
		for(int j=1;j<=n+1;++j) A[row][j]=data[i][j];
	}
	for(int i=1,row;i<=n;++i) {
		row=0;
		for(int j=i;j<=n;++j)
			if(A[j][i]) {
				row=j;
				break;
			}
		if(!row) return 0;
		if(i!=row) exchange(i,row);
		for(int j=1;j<=n;++j) if(i!=j&&A[j][i]!=0) if(!remove(i,j,i)) return 0;
	}
	maxn=0;
	bool is_only=1;
	for(int i=1;i<=n;++i) {
		// 判断解是否为正整数 
		if(A[i][n+1]==0) return 0;
		if(A[i][n+1]<0&&A[i][i]>0) return 0; 
		if(A[i][n+1]>0&&A[i][i]<0) return 0;
		if(abs(A[i][n+1])%abs(A[i][i])!=0) return 0;
		// 判断解是否唯一 
		A[i][n+1]/=A[i][i];
		if(A[i][n+1]>A[maxn][n+1]) {
			maxn=i;
			is_only=1;
		}
		else if(A[i][n+1]==A[maxn][n+1]) is_only=0;
	}
	if(!is_only) return 0;
	return 1;
}
signed main() {
	n=read();
	int m,x;
	for(int i=1;i<=n+1;++i) {
		m=read();
		for(int j=1;j<=m;++j) {
			x=read();
			data[i][x]++;
		}
		data[i][n+1]=read();
	}
	int ans=0;
	for(int i=1;i<=n+1;++i)
		if(Gauss(i)) { // 暴力枚举，设第 i 个是错误方程 
			if(ans) {
				printf("illegal\n");
				return 0;
			}
			ans=maxn;
		}
	if(ans) printf("%lld\n",ans);
	else printf("illegal\n");
	return 0;
}
```


---

## 作者：Durancer (赞：1)

#### 前言

因为一个 $fabs$ 卡了一天的题=_=，一开始读题不认真导致后面WAWA的裂开，所以特别想写一篇题解纪念一下

#### 题意

给出 $n+1$ 一个方程 $n$ 个未知数，其中有一个是错误的，要求在有唯一合法的情况下输出最大的砝码的编号，反之输出无解 $illegal$

那么什么是唯一合法呢?

首先，题目说了， 如果你在枚举不同的两个方程不合法的时候出现了都合法的方案，那么这就直接无解就可以啦

其次，合法的方案中未知数的最大值必须是唯一的，否则也是不合法的

#### 思路

首先，输入是一个神奇的问题，系数其实就是这个位置数被拿的次数，每一次 $+1$ 就可以啦 

我们肯定是要枚举出错的方程的编号，我们可以设置一个二维数组 $ans[i][j]$ 表示在第 $i$ 个方程出错时第 $j$ 个未知数的值，每一次求解的时候记得将不合法的放到最后面，方便计算

在计算的时候用到高斯-约旦消元法求解即可，~~加上随机化更加保险~~，

最重要的是，每一次计算完以后，要记得检查一下是否合法，如果遇到了不合法的值或者某一个元素无解或者无数解的时候，设为 $0$ 即可，因为合法方案中值都是正整数。

当遇到不合法的时候记录一下 $i$ 方程出错时不存在合法方案，并且记录一下不合法的个数，如果最后不是 $n$ 个不合法的话，直接无解即可啦，因为合法方案必须是唯一的，否则就找到最大值的编号输出就好了

#### 代码

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<stack>
#include<map>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#define random(a,b) ((a)+rand()%((b)-(a)+1))
using namespace std;
const int N=1e2+9;
int a[N][N];
int b[N][N];
int n,m;
int ans=0;
int idx=0;
int lim=0;
bool hang[N];//记录行是不是合法方案 
int cun[N][N];//表示第i个出错时j的值 
int tong[N*10000]; 
int cnt;
bool check()//存入每一个解 
{
	memset(tong,0,sizeof(tong));//清空 
	int maxn=0;
	for(int i=1;i<=n;i++)
	{
		if(!b[i][i])//有0，不对 
		cun[lim][i]=0,hang[lim]=true;
		else if(b[i][i]&&!b[i][n+1])//系数为零，值不为零，更不对 
		cun[lim][i]=0,hang[lim]=true;
		else if(b[i][n+1]/b[i][i]<=0)//是负数，也不对 
		cun[lim][i]=0,hang[lim]=true;
		else //找到最大值，并且在计算过程中桶存每一个值的个数 
		{
			cun[lim][i]=b[i][n+1]/b[i][i];	
			tong[cun[lim][i]]++;
			maxn=max(maxn,cun[lim][i]);
		}
	}
	if(tong[maxn]>1) hang[lim]=true;//最大值不唯一，也不合法 
	if(hang[lim]==true) cnt++;//如果不合法，就记录不合法的方案数 
}
void search()
{
	for(int i=1;i<=n+1;i++)
		swap(b[lim][i],b[n+1][i]);//将没有用的一行换到最下面 
	for(int i=1;i<=n;i++)
	{
		int maxn=i;
		for(int j=i+1;j<=n;j++)
			if(abs(b[j][i])>abs(b[maxn][i]))//记得要加绝对值鸭 
				maxn=j;
		for(int j=1;j<=n+1;j++)
			swap(b[i][j],b[maxn][j]);//高斯约旦消元法 
		if(!b[i][i]) continue;
		for(int j=1;j<=n;j++)
		{
			if(j==i) continue;//别忘了判断i，i 
			int tmp=b[j][i]/b[i][i];
			for(int k=i+1;k<=n+1;k++)
				b[j][k]-=b[i][k]*tmp;
		} 
	}
}
int main()
{
	srand(time(NULL));
	scanf("%d",&n);
	for(int i=1;i<=n+1;i++)
	{
		scanf("%d",&m);
		for(int j=1;j<=m;j++)
		{
			int x;
			scanf("%d",&x);
			a[i][x]++; 
		} 
		scanf("%d",&a[i][n+1]);
	}//按照方程组的方式输入
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			int x=random(1,100);
			if(x&1)
				for(int k=1;k<=n+1;k++)
					swap(a[i][k],a[j][k]);
		}//随机打乱，貌似没啥用 
	}
	for(int i=1;i<=n+1;i++)//枚举所有的情况 
	{
		memcpy(b,a,sizeof(a));//拷贝一下，防止用原方程计算只能应用一次的情况 
		lim=i;
		search();//计算 
		check();//判断一下是否合法 
	}
	if(cnt!=n)//合法方案没有或者不是唯一的，直接无解 
	{
		cout<<"illegal"<<endl;
		return 0;
	}
	for(int i=1;i<=n+1;i++)
	{
		if(hang[i]) continue;//找出唯一和法的一行来  
		for(int j=1;j<=n;j++)
		{
			if(cun[i][j]>ans)
			{
				ans=cun[i][j];
				idx=j;
			} 
		}
	}
	cout<<idx<<endl;
	return 0;
}
```


---

## 作者：maruize (赞：1)

感觉用辗转消元法的好少？

辗转消元类似于辗转相除，辗转相除可以使两个數有一个变成零，这个表现和消元的目的很像。这可以远离**double**。

```cpp
gcd(a,b){
	if(a<b)swap(a,b);
	while(b!=0){
		int c=a/b;
		a-=b*c;
		swap(a,b);
	}
	//return a;
} 
```
先上个gcd，代码实际就是把它放进普通高斯消元里。

同其他题解，枚举不合法的式子（称量），再判断。

code:
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
int f[105][105],a[105][105],ans[105];
int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n+1;i++){
		int m,t;
		scanf("%d",&m);
		for(int j=1;j<=m;j++)scanf("%d",&t),f[i][t]=1;
		scanf("%d",&t),f[i][n+1]=t;
	}
	bool can=0;int anss;
	for(int w=1;w<=n+1;w++){//枚举不合法的。
		int maxx=0,maxi;
		for(int i=1,ii=1;i<=n+1;i++){
			if(i!=w){
				for(int j=1;j<=n+1;j++)
					a[ii][j]=f[i][j];
				ii++;
			}
		}//将此次“合法”的拷贝进a数组检查。
		for(int i=1;i<=n;i++){
			if(a[i][i]==0)
			for(int j=i+1;j<=n;j++){
				if(a[j][i]!=0){
					for(int k=1;k<=n+1;k++)swap(a[i][k],a[j][k]);
					break;
				}
			}//如果a[i][i]是0要找一排换掉。
			if(a[i][i]==0)goto down;
			for(int j=i+1;j<=n;j++){
				//v辗转消元核心：（目的：把a[j][i]变成零。）（'a'->a[i][i],'b'->a[j][i]）
				while(a[j][i]!=0){
					int c=a[i][i]/a[j][i];
					for(int k=1;k<=n+1;k++)a[i][k]-=a[j][k]*c;
					for(int k=1;k<=n+1;k++)swap(a[i][k],a[j][k]);
					//swap(a[i],a[j]); //上面换成这样更像。
				}//是不是很像刚才的gcd?
			}
		}
		for(int i=n;i>0;i--){
			
			int las=0;
			for(int j=i+1;j<=n;j++)las+=a[i][j]*ans[j];
			double t=1.0*(a[i][n+1]-las)/a[i][i];//算重量。
			if(t<1e-8||fabs(t-int(t))>=1e-8)goto down;
			ans[i]=t;
		}
		for(int i=1;i<=n;i++)if(ans[i]>maxx)maxi=i,maxx=ans[i];
		for(int i=1,j=0;i<=n;i++){
			if(ans[i]==maxx)j++;
			if(j>1)goto down;
		}//判max是否唯一。
		if(!can){anss=maxi,can=1;goto down;}
		else puts("illegal");
		return 0;
		down:;
			//去枚举下一个。
	}
	if(can)printf("%d\n",anss);
	else puts("illegal");
	return 0;
}
```

---

## 作者：code_hunter (赞：1)

**什么？题解区只有 $O(n^4) $ 的算法？那就让本蒟蒻献上 $O(n^3)$ 的算法吧！——题记**

## 分析

首先大致分析一下题意：给定 $n+1$ 个含 n 个未知数的方程，去掉一个方程，使方程组有唯一解且解为正整数。

首先解方程，首先想到的就是高斯消元吧。题解区大部分做法都是暴力枚举错行，进行高斯消元。显然，这样的做法无法充分利用计算的结果，造成了巨大的时间复杂度。

事实上，求解线性方程组还可以使用克拉默法则：

如果线性方程组
$$\begin{cases}
a_{11}x_1+a_{12}x_2+\cdots+a_{1n}x_n=b_1,\\
a_{21}x_1+a_{22}x_2+\cdots+a_{2n}x_n=b_2,\\
\cdots\\
a_{n1}x_1+a_{n2}x_2+\cdots+a_{nn}x_n=b_n\\
\end{cases}$$
的系数行列式不等于零，即
$$D=
\begin{vmatrix}
a_{11}&\cdots&a_{n1}\\
\cdots&&\cdots\\
a_{n1}&\cdots&a_{nn}
\end{vmatrix}\ne0$$
则方程有唯一解 $x_1=\frac{D_1}{D},\cdots ,x_n=\frac{D_n}{D}$
其中
$$D_j=
\begin{vmatrix}
a_{11}&\cdots&a_{1,j-1}&b_1&a_{1,j+1}&\cdots&a_{1n}\\
a_{21}&\cdots&a_{2,j-1}&b_2&a_{2,j+1}&\cdots&a_{2n}\\
\cdots\\
a_{n1}&\cdots&a_{n,j-
1}&b_n&a_{n,j+1}&\cdots&a_{nn}
\end{vmatrix}$$

利用构造矩阵，可以得出该定理。

在一般的解线性方程组问题中，该定理并不比一般的高斯消元优秀，因而容易被忽视。

那么该定理是如何在本题中发挥作用的呢？

我们发现，题目中给出了 $n+1$ 个方程，加上增广列就正好是一个 $n+1$ 阶方阵了！暴力枚举错误方程并利用克拉默法则求解，不难发现，所需求的行列式正好可以直接从上述方阵的伴随矩阵中得出！（变一变符号就行了。）

那么伴随矩阵该如何求呢？众所周知，方阵 A 的伴随矩阵 $A^*=|A|\cdot A^{-1}$ 。
而方阵行列式和逆元又是 $O(n^3)$ 易求的！（这也是本算法的复杂度瓶颈了qwq）

## 清奇的码风
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

#define For(i,a,b) for(int i = a ; i <= b ; i ++)
#define FoR(i,a,b) for(int i = a ; i >= b ; i --)
typedef double ll;
ll MAX(ll x , ll y) {return (x > y) ? x : y;}
ll MIN(ll x , ll y) {return (x < y) ? x : y;}

using namespace std;

const int MAXN = 123;
const ll eps = 1e-9;

inline int Read() {
	register int x = 0;
	bool flag = false;
	register char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			flag = true;
		ch = getchar();
	}
	if (flag) {
	    while ('0' <= ch && ch <= '9') {
	   		 x = x * 10 - ch + '0';
			 ch = getchar();
	    }
	}
	else {
        while ('0' <= ch && ch <= '9') {
	   		 x = x * 10 + ch - '0';
			 ch = getchar();
	    }
	}
	return x;
}

int N;
vector<vector<ll> > a(MAXN , vector<ll>(MAXN << 1 | 1));
vector<vector<ll> > b(MAXN , vector<ll>(MAXN));
ll det = 1.0;
int ID = -1; 

bool judge(int i) {
	ll bas = b[i][N];
	if (fabs(bas) < eps)
		return false;
	int mx = 0;
	int cnt = 0 , id = -1;
	For (j , 1 , N - 1) {
		ll nw = b[i][j];
		if (!((j ^ N) & 1))
			nw = -nw;
		ll m = nw / bas;
		if (m < eps || fabs(round(m) - m) > eps) 
			return false;
		int w = round(m); 
		if (w > mx) {
			mx = w;
		  	id = j;
			cnt = 1;
		}
		else if (w == mx)
			cnt ++;
	}
	if (cnt != 1)
		return false;
	ID = id;
	return true;
}

void solve() {
	For (i , 1 , N)
		a[i][i + N] = 1;
	For (i , 1 , N) {
		int k = i;
		For (j , i , N)
			if (a[j][i]) {
				k = j;
				break;
			}
		swap(a[i] , a[k]);
		if (! a[i][i]) {
			printf ("illegal\n");
			return;
		}
		For (j , 1 , N)
			if ((j ^ i) && a[j][i]) {
				ll w = a[j][i] / a[i][i];
				a[j][i] = 0;
				For (p , i + 1 , (N << 1)) 
					a[j][p] = a[j][p] - a[i][p] * w;
			}
	}
	For (i , 1 , N) 	
		det = det * a[i][i];
	For (j , 1 , N) {
		ll w = det / a[j][j];
		For (i , 1 , N) {
			b[i][j] = a[j][i + N] * w;
			if ((i ^ j) & 1)
				b[i][j] = -b[i][j];
		}
	}
	int cnt_true = 0;
	For (i , 1 , N)
		cnt_true += judge(i);
	if (cnt_true ^ 1)
		printf ("illegal\n");
	else
		printf ("%d\n" , ID);
}

int main() {
	N = Read() + 1;
	For (i , 1 , N) {
		int M = Read();
		For (j , 1 , M)
			a[i][Read()] = 1;
		a[i][N] = Read();
	}
	solve();	
    return 0;
}

```



---

## 作者：_WHITE_NIGHT_ (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P5027)

一道很板子的高斯消元。

首先，阅读题目：

合法方案的定义：

 - 最重的三角形只有一个。

- 不存在重量不确定的三角形。

- 所有三角形的重量均为正整数。

题目主要部分：

> 他给小正方形的问题是：它有 $n$ 个小三角形，每个小三角形有一定的质量，它对这些三角形进行了 $n+1$ 次称量，然而由于托盘天平的问题，**有一次称量的结果是有误的**。

再者：

> **不存在**一组 $i$,$j$，使得当我们假定第 $i$ 条称量数据有误时能求出一种合法方案，且我们假定第 $j$ 条称量数据有误时也能求出一种合法方案。

否则：

> 输出**最重的小三角形的编号**。 

------------
 
简化一下题意，就是：

如果一组称量是**合法的**，满足以下条件：

我们定义条件 $p$ 为：
>所有未知数**有且只有一个正整数解**。并且这些解满足最大的解在解集中有且仅有一个。用数学语言表达，即为设最大的 $x$ 为 $x_{max}$，解集为 $s$，则有 $\sum_{x\in s}{|x = x_{max}|} = 1$

- 去掉一个方程后，满足 $p$。

- 去掉另一个方程后，不满足 $p$。

意思就是**有且仅有一个方程**，删掉它后，这个多元一次方程组**有且仅有一组整数解**，并且在所有解中，**最大值只有一个**。

------------
现在我们已经理解了题意，代码该如何实现呢？

数据范围：

$$ 1 \leq m \leq n \leq 100$$

明显的 $O(n ^ 4)$ 的数据范围（单次高斯消元最慢 $O(n ^ 3)$，枚举方程 $O(n)$，相乘即可）

这样，再结合题意，我们的思路就已经很明确了：

- 首先，枚举应该删掉哪一个方程。

- 接着，使用高斯消元解出该方程的可行解。

- 判断该解是否合法。

- 枚举结束后，根据记录可行解数量，判断是否有且仅有一组可行解，若有，输出答案；否则，输出“illegal”。

------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

namespace FastIO //快读快输 
{
	const int Mt = 1e5;
	inline char getch()
	{
		static char buf[Mt],*p1 = buf,*p2 = buf;
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,Mt,stdin),p1 == p2) ? EOF : *p1++;
	}
	
	inline int input()
	{
		int num = 0,f = 1;
		char ch = getch();
		while(ch < '0' || ch > '9')
		{
			if(ch == '-') f = -1;
			ch = getch();
		}
		while(ch >= '0' && ch <= '9')
		{
			num = (num << 1) + (num << 3) + (ch ^ 48);
			ch = getch();
		}
		return num * f;
	}
	
	inline void printNum(int num)
	{
		if(num >= 10) printNum(num / 10);
		putchar(num % 10 + 48);
	}
	
	inline void print(int num,char ch = ' ')
	{
		if(num < 0) putchar('-'),num = -num;
		printNum(num);
		putchar(ch);
	}
}
using FastIO::input;
using FastIO::print;

const int N = 105;
const double eps = 1e-3;
int n,m,cnt,ans;
double res[N];
double ipt[N][N],mat[N][N];

void init(int x) //将删掉后的方程组复制到mat数组里面 
{
    int line = 0;
    for(int i = 1;i <= n + 1;i++)
    {
        if(i == x) continue;
        line++;
        for(int j = 1;j <= n + 1;j++)
            mat[line][j] = ipt[i][j];
    }
}

void guass() //高斯消元模板 
{
	int id = 0; //id 记录最重的小三角形编号 
    bool f = 0; //f 记录是否有三角形重量与最重的三角形数量相等 
    for(int line = 1;line <= n;line++)
    {
        int pos = line;
        while(pos <= n && !mat[pos][line]) pos++;
        if(!mat[pos][line]) return;
        if(pos != line) swap(mat[line],mat[pos]);

		for(int i = n + 1;i >= line;i--)
			mat[line][i] /= mat[line][line];
        for(int i = line + 1;i <= n;i++)
        {
            if(!mat[i][line]) continue;
            for(int j = n + 1;j >= 1;j--)
                mat[i][j] -= mat[line][j] * mat[i][line];
        }
    }
	
    for(int i = n;i >= 1;i--)
    {
        res[i] = mat[i][n + 1];
        for(int j = i + 1;j <= n;j++)
            res[i] -= mat[i][j] * res[j];
        if(fabs(((int)res[i]) - res[i]) > eps || res[i] <= 0) return; //判断正整数 
        if(res[id] == res[i]) f = 1; //判断是否与最重的小三角形相同 
        else if(res[id] < res[i]) f = 0,id = i;
    }
    if(f) return; //如果与最重的小三角形重量相同，不合法 
    cnt++,ans = id; //记录最重的编号，方案数加一 
}

int main()
{
    n = input();
    for(int i = 1;i <= n + 1;i++)
    {
        m = input();
        for(int j = 1;j <= m;j++)
            ipt[i][input()] = 1;
        ipt[i][n + 1] = input();
    }//输入部分，将原方程输入到 ipt 数组中 

    for(int i = 1;i <= n + 1;i++)
        init(i),guass();//枚举应该删掉的方程，消元求解 
    
    if(cnt != 1) return puts("illegal") & 0;//可行解数量不是1个，判断不合法 
    print(ans); //输出可行解 
}
```

效率为 $O(n^4)$，能够通过此题。

另：感谢题解审核志愿者[Wuyanru](https://www.luogu.com.cn/user/400201)对本人的指导，十分感谢。

---

## 作者：快斗游鹿 (赞：0)

## 思路

发现 $n$ 很小，可以先 $O(n)$ 枚举哪个方程错误，再用 $O(n^3)$ 高斯消元检验。需要注意的是判不合法。对于一次检验，如果方程无解或者有无数个解，则不合法。如果解不是正整数或最大值不唯一，也无解。所有可能都检验完后，还需要判断是否只有一组合法解。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int nn;
bool flag,f,F;
double a[N][N],b[N][N],ans[N],eps=1e-7,fans;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void Gauss(){
	f=0;
	int n=nn-1;
	/*cout<<n<<endl;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n+1;j++)cout<<b[i][j]<<" ";
		cout<<endl;
	}*/
	for(int i=1;i<=n;i++){
		int r=i;
		for(int j=i+1;j<=n;j++){
			if(fabs(b[j][i])>fabs(b[r][i]))r=j;
		}
		if(fabs(b[r][i])<eps){
			f=1;return;
		}
		swap(b[r],b[i]);
		double div=b[i][i];
		for(int j=i;j<=n+1;j++)b[i][j]/=div;
		for(int j=i+1;j<=n;j++){
			div=b[j][i];
			for(int k=i;k<=n+1;k++){
				b[j][k]-=(b[i][k]*div);
			}
		}
	}
	int num=0;
    for(int i=1;i<=n;i++)
    {
        num=0;
        for(int j=1;j<=n+1;j++)if(!b[i][j])num++;
        if(num==n&&b[i][n+1]){//无数个解或无解
        	f=1;return;
        }
        if(num==n+1){
        	f=1;return;
        }
    }
	ans[n]=b[n][n+1];
	for(int i=n-1;i>=1;i--){
		ans[i]=b[i][n+1];
		for(int j=i+1;j<=n;j++){
			ans[i]-=(ans[j]*b[i][j]);
		}
	}
	double mx=0;
	int id=0;
	for(int i=1;i<=n;i++){
	//	printf("%.2lf ",ans[i]);
		if(ans[i]<=0){//解非正数
			f=1;return;
		}
		if(fabs(ans[i]-(int)ans[i])>eps){//解非整数
			f=1;return;
		}
		if(ans[i]>mx)mx=ans[i],id=i;
	}
	int ccc=0;
	for(int i=1;i<=n;i++){
		if(fabs(ans[i]-mx)<eps){//最大值不唯一
			ccc++;
			if(ccc>1){
				f=1;return;
			}
		}
	}
	fans=id;
	//cout<<endl;
	//cout<<"ok"<<endl;
}
int main(){
	//freopen("std.in","r",stdin);
	nn=read();nn++;
	for(int i=1;i<=nn;i++){
		int m;m=read();
		for(int j=1;j<=m;j++){
			int x;x=read();a[i][x]=a[i][x]+1.0;
		}
		double w;cin>>w;a[i][nn]=w;
	}
	for(int i=1;i<=nn;i++){
		int ccc=0;
		for(int j=1;j<=nn;j++){
			if(i==j)continue;
			ccc++;
			for(int k=1;k<=nn;k++)b[ccc][k]=a[j][k];
		}
		Gauss();
		if(flag&&!f)F=1;//合法解不止一组
		if(!f)flag=1;
	}
	if(flag&&!F)cout<<fans;
	else cout<<"illegal";
	return 0;
}
```


---

## 作者：Pwtking (赞：0)

前置知识：高斯消元。

高斯消元是解决线性方程组的一种方法，对于本题，我们只需要考虑如何将题目转化为线性方程组即可。

先观察数据范围：$n,m<=100$，所以我们可以枚举每一个称量情况作为错误的情况进行 $n$ 次讨论。

我们可以将每个三角形的质量作为每组方程的未知数，那么如果在一组输入数据中称量了某个三角形的质量，那么将他对应的增广矩阵上的值设为一。最后判断得出的解是否合法即可。

---

