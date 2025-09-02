# [USACO3.2] 饲料调配 Feed Ratios

## 题目背景

农夫约翰从来只用调配得最好的饲料来喂他的奶牛。饲料用三种原料调配成：大麦，燕麦和小麦。他知道自己的饲料精确的配比，在市场上是买不到这样的饲料的。他只好购买其他三种混合饲料（同样都由三种麦子组成），然后将它们混合，来调配他的完美饲料。


## 题目描述

给出三组整数，表示 大麦：燕麦：小麦 的比例，找出用这三种饲料调配 x：y：z 的饲料的方法。

例如，给出目标饲料 3：4：5 和三种饲料的比例：

1:2:3
3:7:1
2:1:2
你必须编程找出使这三种饲料用量最少的方案，要是不能用这三种饲料调配目标饲料，输出“NONE”。“用量最少”意味着三种饲料的用量（整数）的和必须最小。


对于上面的例子，你可以用8份饲料1，1份饲料2，和5份饲料3，来得到7份目标饲料：

8\*(1:2:3) + 1\*(3:7:1) + 5\*(2:1:2) = (21:28:35) = 7\*(3:4:5)

表示饲料比例的整数以及目标饲料的都是小于100的非负整数。表示各种饲料的份数的整数，都小于100。一种混合物的比例不会由其他混合物的比例直接相加得到。


## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 3.2


## 样例 #1

### 输入

```
3 4 5
1 2 3
3 7 1
2 1 2 ```

### 输出

```
8 1 5 7```

# 题解

## 作者：Flokirie (赞：31)

其实，谁说本题爆搜就一定要特别处理有0的情况了？   
作为一名数竞生，我们自有方法。    

----
【数竞党必备知识】   
柯西不等式：   
对于实数$a_1,a_2,...,a_n$和$b_1,b_2,...,b_n$，有：   
$\left( \sum_{k=1}^n a_k b_k \right)^2 \leq \left( \sum_{k=1}^n a_k^2 \right) \left( \sum_{k=1}^n b_k^2 \right).$   

特别地，令$n=3$，得到柯西不等式的一个特例：   
$(ax+by+cz)^2\leq (a^2+b^2+c^2)(x^2+y^2+z^2).$   
等号成立当且仅当$a,b,c$与$x,y,z$两组数成比例。（$0:0$也算成比例，但是$0:1$不算）  
   
这样，我们妙用等号成立条件：   
“若$(ax+by+cz)^2=(a^2+b^2+c^2)(x^2+y^2+z^2)$，则$a,b,c$与$x,y,z$两组数成比例。”并且其逆命题也成立。

回到本题，令$a,b,c$分别为三种饲料的混合后的比例（样例里的$21:28:35$），$x,y,z$分别为欲求饲料的比例（样例里的$3:4:5$），对其用柯西不等式即可。

代码示意如下：
```cpp
#define squ(x) ((x)*(x))
if ((squ(a)+squ(b)+squ(c))*(squ(x)+squ(y)+squ(z))==squ(a*x+b*y+c*z)){
    //do something...
}
```
这样就避免了对0的判断。

---

## 作者：Mingoal (赞：10)

简单粗暴的枚举题，但我却用了高斯消元，还可能有精度误差，不过，还是和大家分享一下，毕竟时间复杂度很小

我以样例来解释一下

```cpp
3 4 5
1 2 3
3 7 1
2 1 2
```
把它横过来就成了一个方程组

```cpp
2 3 1 3//2x+3y+z=3k
1 7 2 4//x+7y+2z=4k
2 1 3 5//2x+y+3z=5k
```
我们只要枚举k，就能求出方程组的解

```cpp
#include<bits/stdc++.h>
using namespace std;
const double eps=1e-13;
int flag,j,i,k;
double a[3][4],b[3][4];
int gauss(){//高斯消元
    int i,j;
    double now;
    for (i=0;i<3;++i){
        int k=i;
        for (j=i+1;j<3;++j)
        if (fabs(a[j][i])>fabs(a[k][i])) k=j;
        if ((fabs(now=a[k][i]))<eps) return 1;
        for (j=i;j<=3;++j) swap(a[i][j],a[k][j]);
        for (j=i;j<=3;++j) a[i][j]/=now;
        for (k=0;k<3;++k)
            if (k!=i){
               now=a[k][i];
               for (j=i;j<=3;++j) a[k][j]-=a[i][j]*now; 
            }
    }
    return 0;
}
int main(){
    for (i=0;i<3;i++) scanf("%lf",&b[i][3]);
    for (i=0;i<3;++i)
        for (j=0;j<3;++j) scanf("%lf",&b[j][i]);
    for (k=1;k<=100;k++){
        memcpy(a,b,sizeof(b));
        for (i=0;i<3;i++) a[i][3]=b[i][3]*k;
        if (!gauss()){
            flag=0;
            for (i=0;i<3;i++)
                if (a[i][3]-(int)a[i][3]>eps && (int)(a[i][3]+eps)==(int)a[i][3] || a[i][3]+eps<0){
//判断解出来的数是不是自然数
//关于(int)(a[i][3]+eps)==(int)a[i][3]这句话我解释一下
//有些时候会出现X.999999的情况，要处理一下
                    flag=1;
                    break;
                }
            if (!flag){//解都是自然数
                for (i=0;i<3;i++) printf("%d ",(int)(a[i][3]+eps));
                printf("%d\n",k);
                return 0;
            }
        }
    }
    printf("NONE\n");
}
```

---

## 作者：珅肐 (赞：6)

借鉴了@罗进瑶 的思路

他直接枚举了三种饲料的系数然后判断

但他并没有证明为什么第一个找到的就是最小值

这里简单说一下其正确性

我们要求的是

$$k_1a_1+k_2a_2+k_3a_3=ka$$
$$k_1b_1+k_2b_2+k_3b_3=kb$$
$$k_1c_1+k_2c_2+k_3c_3=kc$$

其中$a,b,c$代表大麦、燕麦、小麦

$k_1,k_2,k_3,k$是三种饲料的比例数，即我们要输出的答案。

要使$k_1+k_2+k_3$最小，那就是使$k$最小（因为一个$k$只对应一组$k_1k_2k_3$）

~~（那么我们可以枚举$k$）~~（说不定可以做，有心者可以试试）

既然这样，$k$只能成倍数增长，对应的$k_1k_2k_3$也是成倍数增长的

这样找到的第一个就是最小值

举个例子：

样例在$100$以内的所有解

$ $ $ $ $8$ $ $ $ $ $1$ $ $ $ $ $5$ $ $ $ $ $ $ $7$

$16$ $ $ $ $ $2$ $10$ $14$

$24$ $ $ $ $ $3$ $15$ $21$

$32$ $ $ $ $ $4$ $20$ $28$

$40$ $ $ $ $ $5$ $25$ $35$

$48$ $ $ $ $ $6$ $30$ $42$

$56$ $ $ $ $ $7$ $35$ $49$

$64$ $ $ $ $ $8$ $40$ $56$

$72$ $ $ $ $ $9$ $45$ $63$

$80$ $10$ $50$ $70$

$88$ $11$ $55$ $77$

$96$ $12$ $60$ $84$

应该不难懂..

最后再次感谢@罗进瑶

不然大概也不会想到直接枚举的做法

代码就不放了


---

## 作者：wky32768 (赞：5)

利用三阶行列式求解

笨方法写死我了

P.S.特殊情况

当x,y,z中有负数的时候无解

还有就是要判-0的情况。

![](https://cdn.luogu.com.cn/upload/pic/19735.png)

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5],b[5],c[5],d[5],D,Dx,Dy,Dz;
double x,y,z,xx,yy,zz;
int main() {
	cin>>d[1]>>d[2]>>d[3]>>a[1]>>a[2]>>a[3]>>b[1]>>b[2]>>b[3]>>c[1]>>c[2]>>c[3];
	D=a[1]*b[2]*c[3]+b[1]*c[2]*a[3]+c[1]*a[2]*b[3]-c[1]*b[2]*a[3]-b[1]*a[2]*c[3]-a[1]*c[2]*b[3];
	Dx=d[1]*b[2]*c[3]+b[1]*c[2]*d[3]+c[1]*d[2]*b[3]-d[3]*b[2]*c[1]-b[1]*d[2]*c[3]-d[1]*c[2]*b[3];
	Dy=a[1]*d[2]*c[3]+d[1]*c[2]*a[3]+c[1]*a[2]*d[3]-c[1]*d[2]*a[3]-d[1]*a[2]*c[3]-a[1]*c[2]*d[3];
	Dz=a[1]*b[2]*d[3]+b[1]*d[2]*a[3]+d[1]*a[2]*b[3]-d[1]*b[2]*a[3]-b[1]*a[2]*d[3]-a[1]*d[2]*b[3];//与图片中的一样 
	if(D==0||D==-0) {
		cout<<"NONE";
	} else {
		x=(double)Dx/D;
		xx=x;
		y=(double)Dy/D;
		yy=y;
		z=(double)Dz/D;
		zz=z;
		if(xx<0||yy<0||zz<0){cout<<"NONE";return 0;}
		int cnt=1;
		while(xx-floor(xx)!=0||yy-floor(yy)!=0||zz-floor(zz)!=0){
			cnt++;//枚举系数 
			xx=x*cnt;
			yy=y*cnt;
			zz=z*cnt;
		}
		if(xx==-0) xx=0;
		if(yy==-0) yy=0;
		if(zz==-0) zz=0;
		cout<<xx<<" "<<yy<<" "<<zz<<" "<<cnt;	
		cout<<"sxdakking"
	}
	return 0;
 
	






```

---

## 作者：QianhanOfficial (赞：3)

dfs解决 需要一定的剪枝 不需要特判0 不需要太多数学知识 不需要~~极其恐怖的~~方程组  
枚举一下要求的比例的倍数 用成倍的比例去枚举减去每一种饲料 如果减到0就是正解 直接退出程序  
但如果只是枚举比例而一个个搜索会只有50分+ 所以需要一个部分剪枝 然后就过了qwq  
具体来讲就是在枚举饲料的时候 我们的dfs会重复搜索许多 但结果是相同的 例如：（以1 2 3代表饲料种类）  
1111111111112 和 1111111111121 和 1111111111211……是完全相同的 所以在枚举到2的时候 以后不需要再次搜索1的情况 就是让1111111211111 变成 1111111222222这样的搜索。  
```cpp
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define re register
int c1, c2, c3, num; 
int x[4], y[4], z[4];
void dfs(re int a, re int b, re int c, re int last)
{
	if(!a && !b && !c)//减完了
	{//c1 c2 c3是使用的各种饲料的个数
		printf("%d %d %d %d", c1, c2, c3, num);//num是原饲料比例倍数
		exit(0);//直接退出程序
	}
	for(re int i = last; i <= 3; ++i)
	{
		if(a - x[i] >= 0 && b - y[i] >= 0 && c - z[i] >= 0)
		{
			if(i == 1) ++c1, dfs(a - x[i], b - y[i], c - z[i], 1), --c1;
			if(i == 2) ++c2, dfs(a - x[i], b - y[i], c - z[i], 2), --c2;
			if(i == 3) ++c3, dfs(a - x[i], b - y[i], c - z[i], 3), --c3;
		}//标准dfs模板
	}
}
int main()
{
	int a, b, c;
	scanf("%d%d%d", &a, &b, &c);
	for(re int i = 1; i <= 3; ++i) scanf("%d%d%d", &x[i], &y[i], &z[i]);
	re int i = 0;
	while(++i <= 100) num = i, c1 = c2 = c3 = 0, dfs(a * i, b * i, c * i, 1);//注意判断无解情况 如果100倍的原饲料也无法满足 就不搜索了。因为各种饲料的比例和个数都是100以内的整数。
	printf("NONE");
	return 0;
}
```

---

## 作者：「QQ红包」 (赞：1)

题解by：redbag

简单粗暴的枚题，但是一些关于0的情况要单独处理

```cpp
/*
ID: ylx14274
PROG: ratios
LANG: C++     
*/
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
int f[4][4];
int aa,bb,cc;
int a,b,c;
int i,j,k,s;
int main() 
{
    scanf("%d%d%d",&aa,&bb,&cc);
    for (i=1;i<=3;i++)//读入比例
    {
        scanf("%d%d%d",&f[i][1],&f[i][2],&f[i][3]);//读入饲料比例 
    } 
    for (i=0;i<=100;i++)//枚举每种饲料的份数
        for (j=0;j<=100;j++)
            for (k=0;k<=100;k++)
            {
                if (i==0&&j==0&&k==0) continue;
                a=(f[1][1]*i)+(f[2][1]*j)+(f[3][1]*k);//大麦 
                b=(f[1][2]*i)+(f[2][2]*j)+(f[3][2]*k);//燕麦
                c=(f[1][3]*i)+(f[2][3]*j)+(f[3][3]*k);//小麦
                int ma=0,mb=0,mc=0;
                int da=0,db=0,dc=0;
                if (aa!=0)
                {
                    ma=a%aa;
                    da=a/aa;
                }
                if (bb!=0)
                {
                    mb=b%bb;
                    db=b/bb;
                }
                if (cc!=0)
                {
                    mc=c%cc;
                    dc=c/cc;
                }
                if (ma==0&&mb==0&&mc==0)//能够整除 
                {
                    int ff=0;//标记用 
                    if (bb==cc&&cc==0&&a!=0) ff=1;//只需饲料a
                    if (bb==aa&&aa==0&&b!=0) ff=1;//只需饲料c
                    if (aa==cc&&aa==0&&c!=0) ff=1;//只需饲料b  
                    if (da==db&&db==dc&&da!=0) ff=1;
                    if (da==db&&cc==0&&da!=0) ff=1;
                    if (da==dc&&bb==0&&dc!=0) ff=1;
                    if (db==dc&&aa==0&&dc!=0) ff=1;
                    if (ff==1)
                    {
                        s=a/aa;//饲料份数
                        printf("%d %d %d %d\n",i,j,k,s); 
                        return 0;
                    }
                }
            } 
    printf("NONE\n");
    return 0;
}
```

---

## 作者：Youngsc (赞：1)

[Youngsc](http://youngscc.github.io/)

关于这道题很恶心的一点就是~~特判0~~，但我们也有办法去避免特判。

既然题目中要求三种饲料之和最小,那我们就先枚举饲料总量，然后分别枚举前两种饲料的量，进而得出第三种饲料的数量，在判断是否合法时

我们可以判断当前每种营养与目标量的比值是否相等，我们设$a$ $b$为其中两种营养的目标值，$x$ $y$为这两种营养的当前值，然后只需判断$a/x=b/y$ 病将其转化为$a*y=b*x$，即可避免特判零的情况，比较两次就能够得出三种营养的比值是否相等。


## 代码在这里

```cpp
# include <algorithm>
# include <iostream>
# include <cstring>
# include <cstdio>
# include <queue>
# include <cmath>
# define R register
# define LL long long

using namespace std;

int no[4],to[4],a[4][4];

inline void in(R int &a){
    R char c = getchar();R int x=0,f=1;
    while(!isdigit(c)){if(c == '-') f=-1; c=getchar();}
    while(isdigit(c)) x = (x<<1)+(x<<3)+c-'0',c = getchar();
    a = x*f;
}

inline void maxx(R int &a,const int b){a>b? 0:a=b;}
inline void minn(R int &a,const int b){a<b? 0:a=b;}


inline int yg(){
    for(R int i=1; i<=3; ++i) in(to[i]);
    for(R int i=1; i<=3; ++i)
        for(R int j=1; j<=3; ++j)
            in(a[i][j]);
    for(R int tot=1; tot<=300; ++tot)//体面说每种都不超过100
        for(R int i=0; i<=tot; ++i)
            for(R int j=0; j<=tot-i; ++j)
            {
                R int k = tot-i-j;
                for(R int d = 1; d<=3; ++d)
                    no[d] = i*a[1][d]+j*a[2][d]+k*a[3][d];
                if(no[1]>=to[1]&&no[2]>=to[2]&&no[3]>=to[3]&&
                   no[1]*to[2]==to[1]*no[2]&&no[3]*to[2]==to[3]*no[2])
                    printf("%d %d %d %d",i,j,k,no[1]/to[1]),exit(0);
            }
    printf("NONE");
    return 0;
}

int youngsc = yg();
int main(){;}
```
（减少代码复制，共创美好洛谷）


---

## 作者：Celebrate (赞：0)

这一道题我为了方便，就打了一个暴力代码

首先枚举一次饲料总数，在枚举第一种和第二种，第三种

就可以直接求出来了，这样做找到就可以直接输出，无需判断

是否是最优值，原因是这样总是最小的

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[11][11];//记录
int x,y,z;//给出的饲料 
int g[11];//记录第i种饲料有多少总 
inline bool pd()
{
	//为了不用精度，就直接交叉相乘，但是要判断一下是否都大于给出的值 
	if(g[1]>=x && g[2]>=y && g[3]>=z && g[1]*y==g[2]*x && g[2]*z==g[3]*y) return true;
	return false;
}
int main()
{
	int i,j,k,t;
	scanf("%d%d%d",&x,&y,&z);
	for(i=1;i<=3;i++) for(j=1;j<=3;j++) scanf("%d",&a[i][j]);//输入 
	for(t=1;i<=300;t++)//枚举份数，可以说是每一份一百把 
	{
		for(i=0;i<=t;i++)//枚举第一种方案 
		{
			for(j=0;j<=t-i;j++)//枚举第二种方案 
			{
				k=t-i-j;memset(g,0,sizeof(g));//一开始记录全部为0 
				for(int ki=1;ki<=3;ki++) g[ki]=a[1][ki]*i+a[2][ki]*j+a[3][ki]*k;//记录下所有的数 
				if(pd()==true)//如果可以 
				{
					printf("%d %d %d %d\n",i,j,k,g[1]/x);//输出 
					return 0;
				}
			}
		}
	}
	printf("NONE\n");//如果不可以 
	return 0;
}
```

---

## 作者：thhhty (赞：0)

用~~奇葩的~~纯数论AC了这题，所以高兴的蒟蒻来发一下题解~
开始是看到楼下的高斯消元，才发现是一个四元一次方程组。。（眼挫）
于是就~~闲着没事干~~试着用单纯的解方程。。
就这么模拟过了！
蒟蒻代码：
```c
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int a[7][5];
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
int main()
{
	int s;
	scanf("%d%d%d",&a[1][4],&a[2][4],&a[3][4]);
	for(int i=1;i<=3;i++)
	{
		scanf("%d%d%d",&a[1][i],&a[2][i],&a[3][i]);
	}
	
	if(a[1][1]==a[2][1])
	{
		for(int i=1;i<=4;i++)a[4][i]=a[1][i]-a[2][i];
	}
	else
	{
		s=gcd(a[1][1],a[2][1]);
		for(int i=2;i<=4;i++)
		{
			a[4][i]=a[1][i]*a[2][1]/s-a[2][i]*a[1][1]/s;
		}
	} 
	if(a[4][2]<0)for(int i=2;i<=4;i++)a[4][i]*=-1;
		
	if(a[2][1]==a[3][1])
	{
		for(int i=1;i<=4;i++)a[5][i]=a[2][i]-a[3][i];
	}
	else 
	{
		s=gcd(a[2][1],a[3][1]);
		for(int i=2;i<=4;i++)
		{
			a[5][i]=a[2][i]*a[3][1]/s-a[3][i]*a[2][1]/s;
		}
	}
	if(a[5][2]<0)for(int i=2;i<=4;i++)a[5][i]*=-1;
		
	if(a[4][2]==a[5][2])
	{
		for(int i=1;i<=4;i++)a[6][i]=a[4][i]-a[5][i];
	}
	else
	{
		s=gcd(a[4][2],a[5][2]);
		for(int i=3;i<=4;i++)
		{
			a[6][i]=a[4][i]*a[5][2]/s-a[5][i]*a[4][2]/s;
		}
	} 
	if(a[6][3]<0)
		for(int i=3;i<=4;i++)a[6][i]*=-1;
	int x,y,z,k;
	s=gcd(a[6][4],a[6][3]);
	z=a[6][4]/s,k=a[6][3]/s;
	y=(a[4][4]*k-a[4][3]*z)/a[4][2];
	x=(a[1][4]*k-a[1][3]*z-a[1][2]*y)/a[1][1];
	if(x<=0&&y<=0&&z<=0&&k<=0)x*=-1,y*=-1,z*=-1,k*=-1;
	if(x<0||y<0||z<0||k<0)printf("NONE\n");
	else printf("%d %d %d %d\n",x,y,z,k);
	return 0;
}
```
判断一下都是负的（就要全部乘-1）
以及坑爹的0就好了

---

## 作者：IS_THAT_DISTANCE (赞：0)

###   本题可用三阶行列式求解
关于行列式可以上网查或者咨询一些dalao，这里简单提一下：  
主要就是这样便可求出x,y,z,k。但是你会发现存在负数的情况，不过没关系，只要他们全是负数，就可以直接倒回来，否则就是无解。  
然后就是对x,y,z,k的约分，这里我用的方法比较低效，就是直接枚举约数。对于0的情况，这里只需将其忽略即可。

	#include<iostream>
	#include<cmath>
	using namespace std;
	int a[3],b[3],c[3],d[3];
	int sq(int a[],int b[],int c[])
	{
		return (a[0]*b[1]*c[2]+a[1]*b[2]*c[0]+a[2]*b[0]*c[1]-a[2]*b[1]*c[0]-a[1]*b[0]*c[2]-a[0]*b[2]*c[1]);
	}
	bool ck(int &A,int &B,int &C,int &D)
	{
		if (!(A>=0&&B>=0&&C>=0&&D>=0)&&!(A<=0&&B<=0&&C<=0&&D<=0)) return 0;
		if (A<=0&&B<=0&&C<=0&&D<=0)
	{
		A=-A;B=-B;C=-C;D=-D;
	}
	int p=1<<30;
	if (A&&p>A) p=A;
	if (B&&p>B) p=B;
	if (C&&p>C) p=C;
	if (D&&p>D) p=D;
	//cout<<p<<endl;
	for (int i=p;i>=2;i--)//floor(sqrt(p))
	{
		if (A%i==0&&B%i==0&&C%i==0&&D%i==0)
		{
			A/=i;B/=i;C/=i;D/=i;
		}
	}
	return 1;
	}
	int main()
	{
		cin>>d[0]>>d[1]>>d[2];
		cin>>a[0]>>a[1]>>a[2];
		cin>>b[0]>>b[1]>>b[2];
		cin>>c[0]>>c[1]>>c[2];
		int A=sq(d,b,c);//abs(d[0]*b[1]*c[2]+d[1]*b[2]*c[0]+b[0]*c[1]*d[2]-d[2]*b[1]*c[0]-d[1]*b[0]*c[2]-b[2]*c[1]*d[0]);
		int B=sq(a,d,c);//abs(a[0]*d[1]*c[2]+a[1]*d[2]*c[0]+d[0]*c[1]*a[2]-a[2]*d[1]*c[0]-a[1]*d[0]*c[2]-d[2]*c[1]*a[0]);
		int C=sq(a,b,d);
		int D=sq(a,b,c);
		//cout<<A<<' '<<B<<' '<<C<<' '<<D<<endl;
		if (ck(A,B,C,D)) cout<<A<<' '<<B<<' '<<C<<' '<<D<<endl;else cout<<"NONE"<<endl;
		return 0;
	}

---

## 作者：巨型方块 (赞：0)

300^3爆搜

答案都在300内，暴力就好了

当然要特判a[i]是0的情况

代码也不长

```cpp
var
a,c,b,d:array[1..3]of longint;
i,j,k,g,x,y,z,std:longint;
begin
for i:=1 to 3 do read(a[i]);
if(a[1]=0)and(a[2]=0)and(a[3]=0)then
begin
  write('0 0 0 0'); halt;
end;
for i:=1 to 3 do read(b[i]);
for i:=1 to 3 do read(c[i]);
for i:=1 to 3 do read(d[i]);
  for j:=0 to 300 do
    for k:=0 to 300 do
      for g:=0 to 300 do
      begin
        if(j=0)and(k=0)and(g=0)then continue;
        x:=d[1]*j+b[1]*k+c[1]*g;
        y:=d[2]*j+b[2]*k+c[2]*g;
        z:=d[3]*j+b[3]*k+c[3]*g;
        if(a[1]<>0)and(x mod a[1]<>0)then continue;
        if(a[2]<>0)and(y mod a[2]<>0)then continue;
        if(a[3]<>0)and(z mod a[3]<>0)then continue;
        if(a[1]<>0)then std:=x div a[1] else
        if(a[2]<>0)then std:=y div a[2] else
        if(a[3]<>0)then std:=z div a[3];
        if(a[1]*std<>x)then continue;
        if(a[2]*std<>y)then continue;
        if(a[3]*std<>z)then continue;
        write(k,' ',g,' ',j,' ',std);
        halt;
      end;
write('NONE');
end.

```

---

## 作者：fengjunjie (赞：0)

迭代深搜，枚举目标饲料调配的份数（1~100）；

如果在搜索范围内有解满足，则输出，否则为NONE

```cpp
program ex01;
var x,y,z:array[0..5] of longint;
    i,j,k:longint;
    sum,ans1,ans2,ans3:longint;
    an,s:array[1..3] of longint;
    p:boolean;
procedure dfs(a,b,c,k:longint);
var i,j:longint;
begin
  if (s[1]=a) and (s[2]=b) and (s[3]=c) then
   if (an[1]+an[2]+an[3])<sum then                                                                       //最优解
    begin
      ans1:=an[1]; ans2:=an[2]; ans3:=an[3]; sum:=an[1]+an[2]+an[3]; p:=true;
    end;
  for i:=k to 3 do
   if (s[1]+x[i]<=a) and (s[2]+y[i]<=b) and (s[3]+z[i]<=c) then                               //剪枝
   begin
     inc(an[i]);
     inc(s[1],x[i]); inc(s[2],y[i]); inc(s[3],z[i]);
     dfs(a,b,c,i);                                                                                                       //为了防止重复，要从上一个搜过的开始搜索
     dec(s[1],x[i]); dec(s[2],y[i]); dec(s[3],z[i]);
     dec(an[i]);
   end;
end;
begin
  for i:=0 to 3 do
   readln(x[i],y[i],z[i]);                                                       
  for i:=1 to 100 do
  begin
    s[1]:=0; s[2]:=0; s[3]:=0;
    p:=false; sum:=maxlongint;
    an[1]:=0; an[2]:=0; an[3]:=0;
    dfs(i*x[0],i*y[0],i*z[0],1);
    if p then
    begin
     writeln(ans1,' ',ans2,' ',ans3,' ',i);
     halt;
    end;
  end;
  writeln('NONE');
end.
```

---

