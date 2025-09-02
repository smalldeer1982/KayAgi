# [USACO2.4] 分数化小数 Fractions to Decimals

## 题目描述

写一个程序，输入一个形如 $\dfrac{N}{D}$ 的分数，输出它的小数形式。如果小数有循环节的话，把循环节放在一对圆括号中。

例如，$\dfrac{1}{3}=0.33333333\ldots$ 写成 $0.(3)$，$\dfrac{41}{333}= 0.123123123\ldots$ 写成 $0.(123)$，整数 $x$ 写成 $x.0$。

## 说明/提示

翻译来自NOCOW

USACO 2.4


## 样例 #1

### 输入

```
45 56```

### 输出

```
0.803(571428)```

# 题解

## 作者：童年如作业 (赞：102)

## [[USACO2.4]Fractions to Decimals【分数化小数】](https://www.luogu.org/problemnew/show/P1530)
```cpp
PS:一道经典的模拟题（或许以后高精会用上），需要用到数学的基本知识（如何判断循环节）
```
## 题意简述
给你分数的分子 $N$ 和分母 $D$ ，求 $\frac{N}{D}$ 的分值。如果分值是整数，保留一位小数。如果分值是循环小数，用小括号 $()$ 括住循环节。如果答案长度超过 $76$ ，每行输出 $76$ 个字符后换行。

## 题目分析
**`注意：N/D是分数，分数属于有理数，有理数分为整数、有限小数和无限循环小数`**

这道题让你算的 $\frac{N}{D}$ 的值会有多种情况：
1. $N$ 可以被 $D$ 整除（即 $N \div D$ 的值是一个整数），但输出需在末尾加上 $.0$ ，例如 $2 \div 2 = 1.0$ 。
2. $N$ 可以被 $D$ 除尽（即 $N \div D$ 的值是一个有限小数），例如 $55 \div 100 = 0.55$ 。
3. $N$ 不可以被 $D$ 除尽（即 $N \div D$ 的值是一个无限循环小数），循环节用一对小括号 $()$ 括住，例如 $1 \div 3=0.(3)$ （所以想用`double`的同学请绕道吧，无限小数是会爆精的）。

## 算法
模拟

## 算法解析
由于用`double`会爆精，我们只好进行手动的除法模拟。经过 $\color{purple}RE$ 的手动验证，我发现有些答案的长度超过了$10^{7}$ ，所以不能用数组模拟，因为$int$类型数组开$10^{8}$会爆空间 $(MLE)$ 。所以我们得用字符串模拟除法（因为字符串是无限空间的）。

- 首先，答案的整数部分可以直接通过 $N/D$ 算出，所以我们可以直接把字符串赋值为 $N/D$ 的值，然后再加一个小数点$(.)$，因为答案无论如何都有小数部分。
- 然后，就是最重要的**除法模拟**部分了。**本题模拟的核心思路正是除法笔算**（长这样的）![](https://i.loli.net/2019/01/18/5c41252170825.png)

  由图可知，算商的小数部分时，会将上一次除下来的余数后面加上被除数的对应位的数字（如果没有就视作0）作为被除数，继续做除法。
  
  现在，模拟思想问题已经解决了，但如何判断循环节又成了一道难关。因为小数部分的商与前面相同时也不一定是循环节， $555 \div 1000 = 0.555$ 就是一个经典的例子，它其实是一个有限小数，所以排除了用商作为判断条件的可能性。
  
  有没有其他东西可以作为循环节的判断条件呢？答案是有的。通过观察我们发现，即使除出来的的商相同，商不是循环节的对应被除数（之前的余数）前面是找不到的，也就是**循环节的数具有被除数相同的必然性**。例如 $1 \div 3=0.3333……$ ，小数部分是这样的出来的：![](https://i.loli.net/2019/01/18/5c413db6e8a81.png)
  
  如图，循环节 $3$ 的被除数一直是 $10$ ，也就是之前算的余数一直是 $1$ ，余数相同。所以我们只要标记出现过的余数，**如果有余数与之前的相同，那么之前余数作为被除数算出的商的位置直到算出这个余数的商的位置就是这个小数的循环节**！
  
  解决了循环节的判断问题后，剩下的就简单了。
- 最后，就是输出了。输出也没什么难的，但要注意 **$76$ 个字符换一行，不要忘记记上整数部分、小数点和小括号。**

## 程序

```cpp
备注：do{}while()是先执行一次{}里的程序后，再进行判断符不符合()里的条件而决定是否继续循环的循环语句。
```

```cpp
#include<iostream>
#include<fstream>
#include<cstdio>
#include<algorithm> 
#include<string>
#include<cstring>
#include<cmath>
#include<vector>
using namespace std;
int n,d,k,w,sum,len;
//w用来记录循环节开始（左括号）的位置，sum为输出使用的计数器 
string ans;
//答案 
int pd[100005];
//pd数组用来记录每个余数出现的位置，判断余数是否重复，便于记录循环节开始（左括号）的位置。根据题目1<=N,D<=100000可得知余数最终不会超过99999 
int main()
{
     
    scanf("%d%d",&n,&d);
    k=n/d,w=-1;
    do
    {
        ans=char(k%10+'0')+ans;
		//这种方法要把拆分出来的整数放到前面去，不然会反过来，因为它先拆分个位，再拆分十位，直接加会使个位在前，直接加会使十位在后， 
        k/=10;
    }while(k>0);
	//拆分结果的整数部分进ans。由于0也算是整数部分，所以无论如何也要拆分一次，用do{}while()，不然用for() 整数部分为0时就不会拆进去，因为k=0了 
    ans+='.';
	//鉴于结果无论如何至少有一位小数，加个小数点
    n=n%d;
	//被除数取余，开始模拟小数部分的除法运算 
    do
    {
        if(pd[n]!=0)
        {
            w=pd[n];
            break;
        }
		//如果余数有重复，说明这是一个循环小数，上一个n出现的位置便是循环节开始（左括号）的位置
        else pd[n]=ans.size();
		//否则就记下这个余数变为被除数后对应的商出现的位置，以便未来判断和记录 
        n*=10;
		//n变成被除数，末尾加0（N,D一定是正整数，不存在小数可加在末尾）
        k=n/d;
        ans+=char(k+'0');
        n=n%d;
		//模拟除法 
    }while(n!=0);
	//由于结果如果是正整数的话，末尾也得加0，用do()while{} 
    if(w!=-1) ans+=')';
	//如果结果是一个循环小数，在末尾加个右括号，便于输出 
    len=ans.size();
    for(int i=0;i<len;i++)
    {
        if(i==w)
        {
            putchar('(');
            i--;
            w=-1;
        }
        //如果这个地方是循环节的开头，在这里输出左括号，并将w改为-1，避免重复输出括号，同时i--，因为这里的ans[i]还没输出  
        else putchar(ans[i]);
        sum++;
        if(sum%76==0) putchar('\n');
		//putchar( )可理解为cout<<char( );
    }
    //注：我这样处理循环节的开头是为了便于换行，因为左括号也算是字符 
    return 0;
}
```

[宣传一下我的博客（给写了一天的我点个赞吧%%%）。](https://www.luogu.org/blog/usersmsyxxLZY/)
[$\color{orange} \text{欢迎私信给予您宝贵的意见，让我的题解做得更好，有错误敬请私信我}$](https://www.luogu.org/space/show?uid=53695)
@[童年如作业](https://www.luogu.org/space/show?uid=53695)
[$\color{orange} \text{，我将作出更正！}$](https://www.luogu.org/space/show?uid=53695)

[![](https://cdn.luogu.com.cn/upload/usericon/53695.png)](https://www.luogu.org/blog/usersmsyxxLZY/)
# $\color{red} \text{谢谢观赏！！！}$

---

## 作者：key_rA9 (赞：22)

 ## [USACO2.4]Fractions to Decimals【分数化小数】
~~本奆鶸这道题做了三天，呜呜呜！  
我竟然看错样例输入卡了一天，忘记76换一行又卡一天，忘记计算整数部分的位数又卡一天。。。~~
这道题，_先输出整数部分及小数点_，然后：  
**1.整除。**  
输出0。  

**2.有限小数**  
求小数部分时直接输出，余数0结束。
我们知道分母质因数只有 2或5 时，这个数能被除尽，以此判断是否是有限小数。  

**3、无限小数**  
计算循环节，只要余数相同就是循环节。  

最后是~~恶心的~~输出。先算上整数部分及小数点的位数，接着用v记录是否有“（”，判断时用（i+v）%76即可。  
代*码*如*下*:
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,d,z=0,flag,v,a[110000],bk[1100000];
int main()
{
    scanf("%d%d",&n,&d);
    printf("%d.",n/d);//整数部分
    if(n%d==0){printf("0");return 0;}//整除
    int t=d;//准备计算能否除尽
    while(t%5==0)t/=5;
    while(t%2==0)t/=2;//先把2和5的因子去掉
    if(t==1)//如果没有别的质因数就会剩下1
    {
        while(n%d!=0)//余数0就除完了
        {
            n=(n%d)*10;//求小数部分
            printf("%d",n/d);
        }
    }
    else//否则就是无限循环
    {int q=n/d;v++;//小数点
    	if(!q)v++;//如果整数部为0要特判
    	while(q)q/=10,v++;//整数位数
        while(!bk[(n%d)*10])//这个余数没出现过
        {
            n=(n%d)*10;
            a[++z]=n/d;bk[n]=z;//记录这个余数的位置，待会有用
        }flag=bk[(n%d)*10];//重复的余数的位置就是加括号的位置
        for(int i=1;i<=z;i++)
        {
            if(i==flag)printf("("),v++;//括号算输出的一个位
            printf("%d",a[i]);//输出记录的数字
            if((i+v)%76==0)printf("\n");//76换行
        }printf(")\n");
    }return 0;
}
```

---

## 作者：「QQ红包」 (赞：12)

题解 by：redbag

原题解地址：http://redbag.duapp.com/?p=1384

若描述有误/描述不清欢迎在原题解中留言。

模拟。


大概思路：


每次求出商和余数。余数为0即除尽了，可以输出。

如过商和余数都相同，也可以输出了。只有余数相同并不可以，某个点会错。

判断商和余数建议使用hash，否则TLE


关于76个字符一换行：

0. 整数部分的位数要算上。

0. 小数点也要算上。

0. 括号也要算上。

0. 0要特殊处理。


然后数组要稍微开大点。


于是就可以愉快的ac了。

```cpp
/*
ID: ylx14271
PROG: fracdec
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
int n,m,f,i,j,l,r,he,x;//i：位数,第l~r位循环 
int y[500000],z[500000];//y:余数部分，z：整数部分 
int hash[100001];
int hs[100001];  
int main() 
{
    freopen("fracdec.in","r",stdin);
    freopen("fracdec.out","w",stdout);
    scanf("%d%d",&n,&m);
    if (n%m==0)//能整除
    {
     
        printf("%d.0\n",n/m); //输出
        return 0;//退出 
    }
    printf("%d.",n/m);//输出整数部分 
    x=1;
    he=n/m; 
    while (he>0)//统计整数部分位数 
    {
        he=he/10;
        x++;
    } 
    if (n/m==0) x++;//0的情况特殊处理 
    y[0]=n%m;//余数
    while (true)
    {
        i++; 
        z[i]=y[i-1]*10/m;//小数第i位整数部分 
        y[i]=y[i-1]*10%m;//余数
        if (y[i]==0) 
        {
            f=1;//标记除尽了 
            break;//除尽了 
        }
        if (hash[y[i]]>0&&hs[hash[y[i]]]==z[i])//商和余数都曾出现 
            {
                l=hash[y[i]];//标记 
                r=i-1;
                break;//退出 
            } 
        hash[y[i]]=i;//存余数为y[i]的位置 
        hs[hash[y[i]]]=z[i];//将商也存进去 
        if (i>499090) break;//不搜了 
    }
    for (j=1;j<=i;j++)//输出 
    {
        if (j==l)//输出括号 
        {
            printf("(");
            x++;//统计位数 
        }
        printf("%d",z[j]);
        x++;
        if (r==j) 
        {
            printf(")"); 
            break;
        }
        if (x%76==0) printf("\n");//换行 
    } 
    printf("\n");
    return 0;
}

```

---

## 作者：Rainbow_qwq (赞：5)

[原题链接](https://www.luogu.org/problemnew/show/P1530)

**一道很不错的模拟题。**

下面介绍我的做法：

---

首先，我用char数组$res$存结果，下面是变量:
```cpp
int n,m,len;    //len:结果长度
int tmp=-1;
//是否是循环小数
//如果是循环小数保存循环节开始位置
int vis[100010]; //标记余数位置
char res[100010];//结果
```
接下来，我们就分别做三个过程：
**处理整数部分，处理小数部分，输出**

先是处理整数部分的函数：**注意，如果整数部分是0也要加一个0**

还有，由于是倒着存进去的，要反转输出。
```cpp
void putInt()//整数部分
{
	int k=n/m;
	if(k==0){//必须特判0
		res[len++]='0';
		return;
	}
	while(k)
	{
		res[len++]=k%10+'0';
		k/=10;
	} 
	for(int i=0;i<len/2;i++)//注意要反转!!!!! 
		swap(res[i],res[len-i-1]);
}
```
处理小数部分：

注意题中说**用xxx.0 等表示整数**，所以要特判余数为0的情况。

处理小数部分是难点，要使用长除法+余数标记，另外要加小数点与右括号。

至于左括号，用$tmp$标记，输出时使用。

$tmp$为$-1$时，就是有限小数。
```cpp
void putDeci()//小数部分
{
	int k=n%m;
	res[len++]='.';//加个小数点
	if(k==0){//必须特判0
		res[len++]='0';
		return;
	}
	while(k)
	{
		if(vis[k]){
			tmp=vis[k];//位置
			break; 
		}
		vis[k]=len;
		k*=10;
		res[len++]=k/m+'0';
		k%=m;
	}
	if(tmp!=-1)res[len++]=')';
		//有循环节加右括号
}
```
最后是输出，~~全是坑~~

注意$76$字符一个换行，还要加左括号
```cpp
void printRes()
{
	int sum=0;  //输出了多少位
	for(int i=0;res[i];i++)
	{
		if(i==tmp)//左括号
		{
			printf("(%c",res[i]);
				//输出左括号+字符 
			sum++;
			if(sum%76==0)puts("");
		}
		else printf("%c",res[i]);
		sum++;
		if(sum%76==0)puts("");//换行
	}
}
```
最后附上完整代码：(大家不要抄袭哦)
```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
#define TP int
inline TP read(){
    char c=getchar();TP x=0;bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
int n,m,len;
int tmp=-1;
int vis[100010];
char res[100010];
void putInt()
{
    int k=n/m;
    if(k==0){
        res[len++]='0';
        return;
    }
    while(k)
    {
        res[len++]=k%10+'0';
        k/=10;
    } 
    for(int i=0;i<len/2;i++) 
        swap(res[i],res[len-i-1]);
}
void putDeci()
{
    int k=n%m;
    res[len++]='.';
    if(k==0){
        res[len++]='0';
        return;
    }
    while(k)
    {
        if(vis[k]){
            tmp=vis[k];
            break; 
        }
        vis[k]=len;
        k*=10;
        res[len++]=k/m+'0';
        k%=m;
    }
    if(tmp!=-1)res[len++]=')';
}
void printRes()
{
    int sum=0;
    for(int i=0;res[i];i++)
    {
        if(i==tmp)
        {
            printf("(%c",res[i]);
            sum++;
            if(sum%76==0)puts("");
        }
        else printf("%c",res[i]);
        sum++;
        if(sum%76==0)puts("");
    }
}
int main()
{
    n=read(),m=read();
    putInt();
    putDeci();
    printRes();
    return 0;
}
```

---

## 作者：installb (赞：3)

upd 2020/7/29 已修改代码中的错误

### 这是道有点复杂的模拟题
主要思路：**长除**

先得到整数部分存着暂时不管

处理N % D

### 主要思路：
如果长除中得到了一个之前出现过的结果 那么一定出现了循环节 所以把每一个余数出现的位置（初始值设为-1）都保存下来 如果发现一个余数的出现位置不是-1 那就找到了循环节 把循环节头尾记录下来

把小数部分每一位存下来 没有必要把不循环部分和循环部分分开来处理

模拟一下样例？

```cpp
45 56 - 0
        .
8 2   - 8
0 20  - 0 
3 32  - 3
5 40  - 5
7 8   - 7
1 24  - 1 
4 16  - 4
2 48  - 2 
8 32  - 8
(5 40 - 5)
32出现过 571428为循环节
```

**76个字符一换行**
这个其实不算最恶心的输出格式了。。

存一个sum
先加上1（小数点）
加上整数部分位数（这个一定小于76 不用判）

然后
出一个字符sum++
sum只要加就判

### 详见代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int apr[100005] = {0}; //apr[i]表示余数i第一次出现的位置
int zs;
int xs[100005] = {0}; //xs[i]代表除下来结果小数部分第i位（从0开始）
//循环节最长为D-1 所以开100000+5就够了
int ans = 0,tmp,flag = 0;
int sum = 0; //sum记录目前已输出多少个字符
int main() {
	int a,b,c,d;
	scanf("%d %d",&a,&b);
	memset(apr,-1,sizeof(apr));
	//正文开始
    zs = a / b; //整数部分
	c = a % b; //拿余数继续处理
	while(1) {
		if(apr[c] != -1) { //如果该余数之前出现过 就代表循环节已经出现了 把ans变为循环节起始位置，tmp是终止位置
			tmp = ans;
			ans = apr[c];
			break;
		}
		apr[c] = ans;
		c = c * 10; 
		d = c / b;
		c = c % b;
		xs[ans] = d; //长除过程
		ans ++; //ans表示当前正在处理第几位（从0开始）
		if(c == 0) { //余数为零代表除尽 立个flag flag=1表示没有循环节
			flag = 1;
			break;
		}
	}
    //正文结束，后面全是处理76个一换行
	printf("%d.",zs);
	sum ++;
	while(1) {
		sum ++;
		zs = zs / 10;
		if(zs == 0) break;
	}
	for(int i = 0; i < ans; i ++) {
		printf("%d",xs[i]);
		sum ++;
		if(sum % 76 == 0) {
			printf("\n");
		}
	}
	if(flag == 0) { //存在循环节
		printf("(");
		sum ++;
		if(sum % 76 == 0) {
			printf("\n");
		}
		for(int i = ans; i < tmp; i ++) {
			printf("%d",xs[i]);
			sum ++;
			if(sum % 76 == 0) {
				printf("\n");
			}
		}
		printf(")");
		sum ++;
		if(sum % 76 == 0) {
			printf("\n");
		}
	}
	return 0;
}
```

---

## 作者：Untitled (赞：2)

注释在代码中QAQ

```
#include<bits/stdc++.h>
using namespace std;
int n,m,glaf[100009],u[100009],v[100009],bg,gb;
bool flag[100009],dd=true;
/*
	解释:
	n,m:分子与分母
	glaf:每一位余数所对应的那一位除出来的商数
	u:每一位除出来的商数
	v:..............余数
	bg:循环结束那位的除出来的余数
	gb:......................商数 
	flag:储存每一位余数对应的除出来的商数
	dd:是否是无限小数 
*/
int main()
{
    memset(flag,true,sizeof flag);
    scanf("%d%d",&n,&m);
    if(n==0)//特判(虽然数据没有 
    {
        printf("0.0\n");
        return 0;
    }
    int zs=n/m;//除出来的整数(由于数据小,不用高精 
    printf("%d.",zs);//输出 
    int ws=0;//储存位数 
    for(int i=1;;i++)//把整数数位加到存储位数的里面 
    {
    	zs/=10;
    	if(zs==0) {ws=i+1;break;}//别忘了加上小数点 
    }
    n=n%m;//除 
    if(n==0)//特判整除 
    {
    	printf("0");
    	return 0;
    }
    int c=0;//小数点后 
    while(1)
    {
        c++;//233
        n*=10;//后退一位 
        u[c]=n/m,v[c]=n%m;//除 
        if(flag[v[c]]==false)//如果这个余数有过 
        {
            if(u[c]==glaf[v[c]])//如果还一样  循环小数无疑 
            {
                bg=v[c];
                gb=u[c];
                break;//跳出 
            }
            glaf[v[c]]=u[c];//更新到最后一位
        }
        //^^上面的两层,防范 1/6=0.1(6) 
        if(v[c]==0){dd=false;break;}//如果除尽了跳出 
        flag[v[c]]=false;//用过了 
        glaf[v[c]]=u[c];//标记 
        n=v[c];//接下来 
    }
    if(dd)
    	c-=1;//应该不计循环最后一位 
    int st=0;//没有循环的地方 
    for(int j=1;j<=c;j++)//搜 
    {
    	if(v[j]==bg&&u[j]==gb)//如果和最后一位雷同 
    		break;//这就是循环首位了,跳出 
    	st++;//加 
    }
    for(int i=1;i<=st;i++)//从非循环搜过去 
    {
		printf("%d",u[i]);//输出 
		ws++;
    	if(ws==76)//坑爹的换行 
    	{
    		cout<<endl;
    		ws=0;
    	}
    	
    }
    if(!dd) return 0;//有限就到此为止吧 
    //VVV下略 
    printf("(");
	ws++;
    if(ws==76)
    {
    	cout<<endl;
    	ws=0;
    }
    for(int i=st+1;i<=c;i++)
    {
    	printf("%d",u[i]);
		ws++;
    	if(ws==76)
    	{
    		cout<<endl;
    		ws=0;
    	}
    	
    }
    printf(")");
	ws++;
    if(ws==76)
    {
    	cout<<endl;
    	ws=0;
    }
    return 0;
}
```


---

## 作者：ADivT (赞：2)

给一个思路吧，先将A和B约分后统计B的2和5因子的个数，循环$max(t2,t5)$遍后没有结束就是有循环，然后直接模拟循环就好，注意输出要换行，具体实现看代码：
```cpp
#include<bits/stdc++.h>

inline int read(int num = 0, char c = getchar()) {
	while(c > '9' || c < '0') c = getchar();
	while(c >= '0' && c <= '9') num = num * 10 + c - 48, c = getchar();
	return num;
}

using namespace std;


int A, B, t2 = 0, t5 = 0, DA, cnt = 0;

void print(int x, int lx = 0) {
	for(int i = x; i; i /= 10, ++ lx);
	cnt += x ? lx : 1, printf("%d", x);
	if(cnt == 76) printf("\n"), cnt = 0;
}

int main() {
	A = read(), B = read();
  	print(A / B), A %= B, printf("."), ++ cnt;
	if(A == 0) 	return !printf("0");
	while( !(A % 2) && !(B % 2) ) A /= 2 , B /= 2;
	while( !(A % 5) && !(B % 5)) A /= 5, B /= 5;
	for(int i = B; i % 2 == 0; i /= 2, ++ t2);
	for(int i = B; i % 5 == 0; i /= 5, ++ t5);
	for(int i = 1; i <= max(t2, t5); ++i)
		A *= 10, print(A / B), A %= B;
	if(A == 0) return 0;
	DA = A, printf("("), ++ cnt;
	do	A *= 10, print(A / B),A %= B;
	while(DA != A);
	printf(")");
	return 0;
}

```

---

## 作者：Celebrate (赞：1)

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,f,i,j,l,r,t,x;//i：位数,第l~r位循环 
int y[510000],z[510000];//y:余数部分，z：整数部分 
int g[110000],a[110000];  
int main() 
{
    scanf("%d%d",&n,&m);
    if(n%m==0)//能整除
    {
        printf("%d.0\n",n/m); //输出
        return 0;//退出 
    }
    printf("%d.",n/m);//输出整数部分 
    x=1;
    t=n/m; 
    while(t>0)//统计整数部分位数 
    {
        t=t/10;
        x++;
    } 
    if(n/m==0) x++;//0的情况特殊处理 
    y[0]=n%m;//余数
    while(1)
    {
        i++; 
        z[i]=y[i-1]*10/m;//小数第i位整数部分 
        y[i]=y[i-1]*10%m;//余数
        if(y[i]==0) 
        {
            f=1;//标记除尽了 
            break;//除尽了 
        }
        if(g[y[i]]>0&&a[g[y[i]]]==z[i])//商和余数都曾出现 
        {
            l=g[y[i]];//标记 
            r=i-1;
            break;//退出 
        } 
        g[y[i]]=i;//存余数为y[i]的位置 
        a[g[y[i]]]=z[i];//将商也存进去 
        if(i>499090) break;//不搜了 
    }
    for(j=1;j<=i;j++)//输出 
    {
        if(j==l)//输出括号 
        {
            printf("(");
            x++;//统计位数 
        }
        printf("%d",z[j]);
        x++;
        if(r==j) 
        {
            printf(")"); 
            break;
        }
        if(x%76==0) printf("\n");//换行 
    } 
    printf("\n");
    return 0;
}
```

---

## 作者：vinvor (赞：1)

记得长除法吗？我们知道只有当出现了曾经出现过的余数时，小数部分才会出现重复。重复的部分就是自从我们上次见到同样的余数之后计算出的部分。

我们先读入并打印整数部分。接下来，我们对剩下的真分数部分进行长除直到我们发现了重复的余数或余数变为0。如果我们发现了重复的余数，即出现了循环节，就分别恰当地打印重复的部分和不重复的部分。如果余数变为0，即已经除尽，就打印整个小数部分。如果小数位根本没有被生成，那么打印一个0 就是正确答案了。

另一个解法

计算循环开始前的小数位数，这样你甚至无需保存各个小数位和余数，程序的空间花费将大幅减小，而运行速度也能有所提高。我们知道2 和5 的幂是仅有的两种不导致循环的数，因此要找到循环前的各数位，我们只需分别找到分子分母中包含的因子2和5个数的差，再取两者的最大值（详见代码片段）。然后我们仅使用第一个余数，在计算时输出各个数位即可。

我们知道，a/b 的每位运算所得的余数只可能是0..b-1，如果在某处出现一个余数之前曾经出现过（在小数位上），那么可以肯定此时从该处到上次用出现这个这个商之间存在循环节。用m 记录每种余数是否曾经出现过，ss 记录余数第一次出现的位置，如果余数为0 就是整除，否则就找到循环节，输出。

实际上，后面的小数内容完全取决于试除这一位时的商和余数。另外，注意输出格式。

下附代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int y[100005],c[100005];
bool hahash[100005];
int hahashi[100005];
int main()
{
    int n,m;
    cin>>n>>m;
    cout<<n/m;
    int o=n/m==0?2:log10(n/m)+2;
    n%=m;
    if(n==0){
        cout<<".0"<<endl;
        return 0;
    }
    cout<<'.';
    int kb=-1;
    int i;
    c[1]=0;
    y[1]=n;
    hahash[n]=true;
    hahashi[n]=1;
    n*=10;
    for(i=2;kb==-1;i++){
        c[i]=n/m;
        y[i]=n%m;
        n=y[i]*10;
        if(hahash[y[i]]){
            kb=hahashi[y[i]];
            break;
        }
        else{
            hahash[y[i]]=true;
            hahashi[y[i]]=i;
        }
        if(n==0)break;
    }
    if(kb>0)kb++;
    for(int k=2;k<=i;k++){
        o++;
        if(k==kb)cout<<"(",o++;
        cout<<c[k];
        if(o%76==0)cout<<endl;
    }
    if(kb!=-1)cout<<')';
    cout<<endl;
    return 0;
}
```

---

## 作者：wwwsy (赞：1)

有点可怕
我提交了9次

我记住这道题了〒⌒〒

主要是2个问题
1. 没有转行  （审题）
2. 没有特判  --取得长度时用了log但没有判0


```
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring> 
using namespace std;
int d=1000000;
int c;
int a,b;
int f[2000000],an[2000000];
int len;
int main()
{
    
    memset(f,-1,sizeof(f));
    scanf(" %d %d",&a,&b);
    if(a%b==0)
    {
        c=a/b;
        printf("%d.0",c);
        return 0; 
    }
    else
    {
        c=a/b;
        if(c==0) len=2;
        if(c!=0) len=log10(c)+2;
        printf("%d.",c);
        int y=a%b;
        int i=0,p=-1,pp=-1;
        f[y%b]=0;
        while(d--)
        {
            if(y==0)
            {
                for(int j=1;j<=i;j++)
                {
                    printf("%d",an[j]);
                    len++;
                    if(len==76)
                    {
                        printf("\n");
                        len=0;
                    }
                }
                
                return 0;
            }
            i++;
            y*=10;
            an[i]=y/b; 
            if(f[y%b]!=-1)
            {
                p=f[y%b]+1;           //循环开始 
                pp=i;                 //循环结束 
                break;
            }
            f[y%b]=i;
            y=y%b;
        }
            for(int i=1;i<p;i++)
            {
                printf("%d",an[i]);
                len++;
                    if(len==76)
                    {
                        printf("\n");
                        len=0;
                    }
            }
            printf("(");
            len++;
                if(len==76)
                {
                    printf("\n");
                    len=0;
                }
            for(int i=p;i<=pp;i++)
            {
                printf("%d",an[i]);
                len++;
                    if(len==76)
                    {
                        printf("\n");
                        len=0;
                    }
            }
            printf(")");
            len++;
                if(len==76)
                {
                    printf("\n");
                    len=0;
                }
            return 0;
    }
    return 0;
}
```

---

## 作者：JCY_ (赞：0)

个人觉得本蒟蒻代码(去掉那一堆没用的宏)比楼上几位巨佬短，详见注释
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
#define ms(a,b) memset(a,b,sizeof a)
#define sz(a) (int)a.size()
#define maxx(a,b) a=max(a,b)
#define minx(a,b) a=min(a,b)
#define endl '\n'
const int maxn=1e5+5,maxedge=2e5+5,inf=0x3f3f3f3f,mod=1e9+7;
int a,b;
string st=""; //答案
map<int,int> mp; //标记某个数作分子(被除数)时商第一次出现过的位置
void init()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
} //一些奇怪的ios优化
string tostr(int x)
{
	stringstream ss;
	string st;
	ss<<x;
	ss>>st;
	return st;
} //int化为string, 为了省事直接打了stringstream
int main()
{
	init();
	cin>>a>>b;
	st+=tostr(a/b)+'.'; //将商的整数部分录入答案
	a%=b; //a取除以b的余数
	do //这里之所以用do而非while是因为当a%b==0时, 答案要加上".0", 在进行过上一行的取模运算后, a必然等于0, 倘若用while便会直接跳出循环, 用do可以使答案在循环结束前再加上a/b, 即"0" (主要还是本蒟蒻懒得打判断了)
	{
		a*=10; //手动模拟除法运算, 每次都在商后添"0"
		if(mp[a]) //如果此时的分子(被除数)已经出现过, 即会陷入循环时
		{
			st.insert(mp[a],"("); //在上一次出现的位置前填上"("
			st+=')'; //在循环节末尾添上")"
			break; //跳出循环, 输出答案
		}
		mp[a]=sz(st); //如果此时的分子(被除数)没有出现过, 记录此次商的位置, sz()见程序第7行的宏
		st+=tostr(a/b); //答案加上a/b的商 (其实这里并没有必要强制转为string类型, 上一次循环中经历了a%=b, 本次循环一开始a*=10, 说明a/b必然<10, 所以可以直接加上'0'(不过要加括号) )
		a%=b; //a取除以b的余数
	} while(a);
	while(!st.empty()) //非常lj的输出方法, 见谅
	{
		if(sz(st)>76) //见程序第7行的宏
		{
			cout<<st.substr(0,76)<<endl;
			st.erase(0,76);
		}
		else
		{
			cout<<st<<endl;
			st.erase(0); //省略第2个参数说明从下标为0处直接删到末尾
		}
	}
	return EXIT_SUCCESS; //就是return 0;
}
```

---

## 作者：CZQ_King (赞：0)

这是一道长除法的题目，这里我使用了一个$map$记录了之前出现过的余数。当出现之前有的余数时，退出循环并输出。（详见代码）


------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int fz,fm,w,r,l,g,xhj[100005],mmp=2;
/*fz:分子;fm:分母;w:余数;r:左括号;l:右括号;g:小数部分的个数;xhj:小数部分;mmp:记录位数是否超过76位*/
map<int,int>m;//之前出现过的余数
int main(){
	cin>>fz>>fm;
	cout<<fz/fm<<".";//先把整数部分和小数点输出
	if(fz/fm!=0)mmp+=log10(fz/fm);//如果整数部分大于1位数就把位数加上
	w=fz%fm*10;//先把余数处理好
	for(int i=1;i<=fm*2;i++){//因为除以n的位数不超过n，且要找循环节，所以要乘2
		xhj[++g]=w/fm;//小数部分加上
		if(m[w]){//如果有出现之前的余数
			r=m[w];//左括号等于上一个的位置
			l=i-1;//右括号记得要减1
			break;//后面就不用找了，结束
		}
		m[w]=i;//记录这个数在小数部分中的位置
		if(w%fm==0)break;//如果被整除了就结束
		w=w%fm*10;//获取下一位
	}
	for(int i=1;i<=g;i++){//到最后一位小数的位置
		mmp++;//加位数
		if(i==r){mmp++;cout<<"(";}//如果是循环节开头
		cout<<xhj[i];//输出那一位
		if(i==l){cout<<")";return 0;}//是结束就输出右括号并结束
		if(mmp%76==0){puts("");mmp=0;}//如果到了76位就输出回车
	}
}
```

---

## 作者：tan90度 (赞：0)

```cpp
这题暴力模拟，没什么难度。
有两个引论：1.求循环节：用余数*10再取余数，如果遇到两个相同的余数，则这段过程里的商即循环节
           2.只有除数只有2,5两个质因子时才是有限小数
最后注意输出，左右括号算一个字节
#include<bits/stdc++.h>
using namespace std;
int c[1000000];
int d[1000000];
int e[1000000];
bool cf(int x)
{
	int i;
	i=2;
   while(i<=sqrt(x))
   {
   if (x%i==0)
   {
   x=x/i;
   if (i!=2&&i!=5)
   return false;
   }
   else i++;
   }
   if (x!=0)
   if (x!=2&&x!=5)
   return false;
   return true;
}
int main()
{
	int n,m,k,i,k1,k2,x,n1,j,l;
	cin>>n>>m;
	k=n%m;
	if (k==0)
	{
		cout<<n/m<<"."<<"0"<<endl;
		return 0;
	}
    cout<<n/m<<".";
    k1=1;
    for (i=1;i<=6;i++)
    {
    	k1=k1*10;
    	if (n/m/k1==0)
    	{
    		k2=i;
    		break;
		}
	}
	x=k2+1;
	k2=x;
	i=0;
	n1=n;
    while (true)
    {
    	k=n1%m;
    	n1=k*10;
		c[k]++;
    	if (c[k]==2||k==0)
    	{
    	l=e[k];
		break;
	}
    	i++;
    	d[i]=n1/m;
    	e[k]=i;
	}
	if (cf(m))
	for(j=1;j<=i;j++)
	{
	k2++;
	if (k2==76)
	{
	cout<<d[j]<<endl;
	k2=0;
    }
	else cout<<d[j];
    }
    else {
	      for (j=1;j<=i;j++)
         {
         	if (j==l)
			 {
			 cout<<"(";
         	k2++;
         	if (k2==76)
         	{
			 cout<<endl;
			 k2=0;
		}
         }
            cout<<d[j];
            k2++;
            if (k2==76)
         	{
			 cout<<endl;
			 k2=0;
         }
		 }
         cout<<")";
     }
  return 0;
}

```

---

## 作者：北极星 (赞：0)

~~本蒟蒻第一次发题解，望各位大佬支持~~

和一楼的思路差不多，但感觉比他简洁很多（具体注释详见代码）
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int a[500005],mo[500005];//a数组记录每位数，mo数组记录每次除法后的余数（mo数组用于下一位计算）
int f[15][100005];//f[x][y]记录得数为x，余数为y出现的位置（用来判断有无循环节）
int n,m,t,i,book1=0,book2=0;
int main(){
   memset(f,0,sizeof(f)); 
   int len=0;//记录结果的长度，用于换行
   scanf("%d%d",&n,&m);
   t=0;
   if (n%m==0){
      printf("%d.0",n/m);
      return 0;
   }//结果为整数
   if (n>m) {
      int x=n/m;
      printf("%d.",n/m);
      n=n%m;
      i=1;
      len=1;//小数点的长度为1
      while (1){
            len++;
            if (x/i<10) break;
            i=i*10;
        }//计算整数长度
   }//先输出整数和小数点
   else if (n<m) { 
        printf("0.");
        len=2;
    }
    //以下计算小数部分
   while (1){
      t++;
      a[t]=(n*10)/m;
      n=(n*10)%m;
      mo[t]=n;
      if (f[a[t]][mo[t]]>0){
            book1=f[a[t]][mo[t]];
            book2=t;
            break;
        }//如果有循环节，退出
      f[a[t]][mo[t]]=t;//记录位置（注意f数组第二维要开100000，防止n很小，而m很大，导致mo的值很大）
      if ((a[t]==0&&mo[t]==0)) break;
   }
   if (book1==0){
      t--;
      for (i=1;i<=t;i++)
       if (i%76==0) printf("%d\n",a[i]);
       else printf("%d",a[i]);
   }//无循环节
   else {
      for (i=1;i<book1;i++){
         len++;
         if (len%76==0) printf("%d\n",a[i]);
         else printf("%d",a[i]);
      }
      len++;
      if (len%76==0) printf("(\n");
      else printf("(");
      for (i=book1;i<book2;i++){
         len++;
         if (len%76==0) printf("%d\n",a[i]);
         else printf("%d",a[i]);
      }
      printf(")");
   }//有循环节
   return 0;
}


```

---

## 作者：封二少 (赞：0)

大概思路就是把n/d的余数存入数组，然后n = n % d \* 10，继续除d，

直到最新的余数与之前某一次的余数相等，那么这两个相等的余数之间就是循环节，

通过纪录这两个余数的位置输出

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
const int N = 10000086;
int n, d, f, a[N], b[N], bo, i, j, tot = 1;
using namespace std;
inline int get()
{
    char ch;
    int res = 0;
    while (((ch = getchar()) < '0' || ch > '9') && ch != '-');
    if (ch != '-')
      res = ch - '0';
    char c;
    while ((c = getchar()) >= '0' && c <= '9')
      res = (res << 3) + (res << 1) + c - '0';
    return ch == '-' ? ~res + 1 : res;
}
void put(int x)
{
    if (x < 0)
      putchar('-'), x = ~x + 1;
    if (x > 9) put(x / 10);
      putchar(x % 10 + '0'); 
}
int main()
{
    n = get(); d = get();    
    if (n % d == 0)
    {
        printf("%d.0", n / d);
        return 0;
    }
    else 
    {
        printf("%d.", n / d);
        int kk = n / d;
        if (kk == 0) tot++;
        while(kk != 0)
        {
            kk /= 10;
            tot++; 
        } 
        n = (n % d * 10);
        for (i = 1; n % d && i <= 1000000; i++, n = (n % d * 10))
        {
            b[i] = n;
            a[i] = n / d;
        }
        b[i] = n;
        a[i] = n / d;
        for (i = 1; i <= n; ++i)
        {
            for (j = i + 1; j <= n; ++j)
              if (b[j] == b[i]) break;
              if (b[j] == b[i]) break;
        }
        for (int l = 1; l <= n; ++l)
        {
            if (l == i && l == j - 1) return 0; 
            if (l == i) 
            {
                printf("(");
                tot++;
            }
            if (tot == 76)
            {
                printf("\n");
                tot = 0;
            }
            printf("%d", a[l]);
            tot++;
            if (tot == 76)
            {
                printf("\n");
                tot = 0;
            }
            if (l == j - 1)
            {
                printf(")");
                tot++;
                if (tot == 76)
                {
                printf("\n");
                tot = 0;
                }
                return 0;
            }
        } 
    }
    return 0;
}
```

---

## 作者：Great_Influence (赞：0)

# STL大法好！！！

这道题下面一堆人说了一堆复杂的方法，主要意思是记录除后留下的商和余数，当商和余数曾经出现过（注意这里）时便可以判断出是否循环。

而如何判断是否曾出现呢？这时便出现了map！！！有了map便可以愉快地AC了！！！



顺便说一下，这道题的输出好坑的，我一开始没注意，wa了3个点。。。。。。

代码：

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#include<map>
#define For(i,a,b) for((i)=(a);(i)<=(b);++(i))
using namespace std;
inline void read(int &x)
{
    int s=0;
    char k=getchar();
    while(!isdigit(k))k=getchar();
    while(isdigit(k))
    {
        s=(s<<3)+(s<<1)+(k^'0');
        k=getchar(); 
    }
    x=s;
}
struct node//开结构体记录商和余数
{
    int be,la;
    friend bool operator< (node a,node b)//这个重载运算符一定要打，因为map要靠它来排序，不打的话会报错
    {
        return a.be<b.be||a.be==b.be&&a.la<b.la;
    }
}s;
void dfi(int &x,int &y)//求最简分数
{
    int i,len=min(sqrt(x),sqrt(y));
    For(i,2,len)while(x%i==0&&y%i==0)
    {
        x/=i;
        y/=i;
    }
}
int n,m,t,loop[100000+100],flag;
int len(int x)//计算长度，其实只用了一次
{
    int s=0;
    while(x)
    {
        ++s;
        x/=10; 
    }
    return s;
}
map<node,int>G;//核心代码
int main()
{
    int i,lenth;//lenth是记录输出长度的
    read(n);
    read(m);
    dfi(n,m);
    if(n>=m)
    {
        printf("%d.",n/m);
        lenth=len(n/m)+1;
        n%=m;
    }
    else
    {
        printf("0.");
        lenth=2;
    }
    while(1)
    {
        n*=10;
        s.be=n/m;
        s.la=n%m;
        if(G[s])//判重
        {
            flag=G[s];
            break;
        }
        else G[s]=++t;
        loop[t]=n/m;
        n%=m;
        if(!n)break;
    }
    if(flag)//有循环节
    {
        For(i,1,flag-1)
        {
            printf("%d",loop[i]);
            ++lenth;
            if(lenth==76)
            {
                cout<<endl;
                lenth=0;
            }
        }
        cout<<'(';
        ++lenth;
        if(lenth==76)
        {
            cout<<endl;
            lenth=0;
        }
        For(i,flag,t)
        {
            printf("%d",loop[i]);
            ++lenth;
            if(lenth==76)
            {
                cout<<endl;
                lenth=0;
            }
        }
        cout<<')';
    }
    else For(i,1,t)//无循环节
    {
        printf("%d",loop[i]);
        ++lenth;
        if(lenth==76)
        {
            cout<<endl;
            lenth=0;
        }
    }
    cout<<endl;
    return 0;
}

```

---

## 作者：我不是柳橙汁 (赞：0)

# 这题时珍的皮！


如同楼下的说法，是用长除法来做，然而我并不知道长除法的做法233，于是就想了很久算法。由于我不会**哈希算法**，所以我用了结构体来标记已经保留过的余数。还有要注意的是输出时要判断76个字符一行，所以我自己加了个函数来换行hh

···cpp

```cpp
#include<cstdio>
struct node{
    int f,cr;
}mark[1000010];
int ans[1000010];//记录要输出的ans
int flag,len,point,k,kx,st[20];
void xo(int c){
    kx++;
    if (kx==77){//每输出76个字符换一行
        kx=1;
        puts("");
    }
    putchar(c);
}
void xout(int k){//输出优化
    int num=0;
    if (k<0) xo(45),k=-k;
    while (k) st[++num]=k%10,k/=10;
    if (num!=0)
        while (num) xo(st[num--]+48);
    else xo(48);
}
int main(){
    int n,d;
    scanf("%d%d",&n,&d);//输入
    xout(n/d);
    xo('.');//输出整数部分和小数点
    if (n%d==0){
        xo(48);
        return 0;
```
}//如果n被d整除就输出0结束
```cpp
    n=n%d;
    while (n!=0){//当n等于0时输出结果
        n*=10;//将上次计算得的余数乘10像长除法一样计算
        if (mark[n].f){//如果n已经出现过，就是出现了循环节，所以直接输出
            for (int i=1;i<mark[n].cr;i++)
                xo(ans[i]+48);
            xo('(');
            for (int i=mark[n].cr;i<=len;i++)
                xo(ans[i]+48);
            xo(')');
            return 0;
```
}//注意输出的格式
```cpp
        ans[++len]=n/d;
        mark[n].f=1;
        mark[n].cr=len;
        n=n%d;//标记n以及n出现的位置，标记结果，n更新为n被d除的余数
    }
    for (int i=1;i<=len;i++) xo(ans[i]+48);//最后输出
    return 0;
}
···
```

---

## 作者：gaoshanxun (赞：0)

{长除法}


  
  
```cpp
Var
  n,d,i:longint;
  s,ans:ansistring;
  pos:array[0..1000000] of longint;
Begin
  fillchar(pos,sizeof(pos),0);
  read(n,d);
  str(n div d,ans);  ans:=ans+'.';
  n:=n mod d*10;
  If n=0 then ans:=ans+'0'
  Else
    Repeat
      pos[n]:=length(ans);
      str(n div d,s);  ans:=ans+s;
      n:=n mod d*10;
      If pos[n]<>0 then ans:=copy(ans,1,pos[n])+'('+copy(ans,pos[n]+1,length(ans)-pos[n])+')'
    Until (n=0) or (pos[n]<>0);
  For i:=1 to length(ans) do
    Begin
      write(ans[i]);
      If i mod 76=0 then writeln
    End;
  writeln;
End.
```

---

## 作者：Memory_of_winter (赞：0)

```cpp
var
 sa,yu:array[1..1000000]of longint;
 pd:array[0..1000000]of boolean;
 i,j,l,x,y,n,m:longint;
 s:string;
function yes:boolean;
 var
  i,j,k:longint;
 begin
  for i:=1 to l-1 do if yu[i]=yu[l] then
                                     begin
                                      x:=i;//求循环的第一位
                                      y:=l-1;//求循环的最后一位
                                      exit;
                                     end;
 end;
begin
 readln(n,m);//读入
 write(n div m,'.');//输出整数部分和小数点
 str(n div m,s);
 j:=length(s)+1;//求长度
 l:=1;
 n:=n mod m;
 if n=0 then//如果除尽就结束程序
         begin
          writeln(0);
          halt;
         end;
 yu[l]:=n;
 pd[n]:=true;
 repeat
  sa[l]:=yu[l]*10 div m;//存商
  inc(l);
  yu[l]:=yu[l-1]*10 mod m;//存余数
  if pd[yu[l]] then//必须用这种方法求是否有这个余数，否则会超时
                begin
                 yes;//求循环
                 break;
                end;
  pd[yu[l]]:=true;//存已有这个余数
 until yu[l]=0;//直到除尽
 for i:=1 to l-1 do//输出
  begin
   if i=x then
           begin
            write('(');
            inc(j);
            if j mod 76=0 then writeln;//换行
           end;
   write(sa[i]);
   inc(j);
   if j mod 76=0 then writeln;//换行
   if i=y then
           begin
            write(')');
            inc(j);
            if j mod 76=0 then writeln;//换行
           end;
  end;
 writeln;
end.
```

---

## 作者：YczSS (赞：0)

记得长除法吗？我们知道只有当出现了曾经出现过的余数时，小数部分才会出现重复。重复的部分就是自从我们上次见到同样的余数之后计算出的部分。

我们先读入并打印整数部分。接下来，我们对剩下的真分数部分进行长除直到我们发现了重复的余数或余数变为0。如果我们发现了重复的余数，即出现了循环节，就分别恰当地打印重复的部分和不重复的部分。如果余数变为0，即已经除尽，就打印整个小数部分。如果小数位根本没有被生成，那么打印一个0就是正确答案了。

```cpp
var
  s:ansistring;
  bz:array[0..99999] of longint;
  i,j,k,m,n,last,wei:longint;
procedure print;
var
  i:longint;
begin
  for i:=1 to length(s) do
  begin
    write(s[i]);
    if i mod 76=0 then writeln;
  end;
  if i mod 76<>0 then writeln;
end;
Begin
  readln(m,n);
  fillchar(bz,sizeof(bz),0);
  str(m div n,s);
  k:=length(s);
  s:=s+'.';
  wei:=1;
  last:=m mod n;
  bz[last]:=1;
  if m mod n=0 then
  begin
    s:=s+'0';
    print;
  end else
  begin
    repeat
      inc(wei);
      last:=last*10;
      s:=s+chr(last div n+48);
      last:=last mod n;
      if bz[last]<>0 then break else bz[last]:=wei;
    until (last=0);
    if last=0 then print else
    begin
      insert('(',s,k+bz[last]+1);
      s:=s+')';
      print;
    end;
  end;
End.
```

---

