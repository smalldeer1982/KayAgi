# [USACO1.4] 等差数列 Arithmetic Progressions

## 题目描述

一个等差数列是一个能表示成 $a, a+b, a+2b, \dots ,a+nb\space (n \in \mathbb N)$ 的数列。

在这个问题中 $a$ 是一个非负的整数，$b$ 是正整数。  
写一个程序来找出在双平方数集合：  
$$\{ x | x = p^2 + q^2 \wedge p,q \in \mathbb N \cap [0,m]\}$$
中长度为 $n$ 的等差数列。



## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$3 \le n \le 25$，$0 \le m \le 250$。

题目翻译来自NOCOW。

USACO Training Section 1.4


## 样例 #1

### 输入

```
5
7
```

### 输出

```
1 4
37 4
2 8
29 8
1 12
5 12
13 12
17 12
5 20
2 24
```

# 题解

## 作者：01190220csl (赞：46)

有一种特殊的思路：（证明$n>=4$时，$b=4k$）。

过程：设$p=a^2+b^2$。

1.$a,b$为偶数。设$a=2m,b=2n$，则$p=4(m^2+n^2)$。

2.$a,b$一奇一偶。不妨令$a=2m+1,b=2n$，则$p=4(m^2+n^2+m)+1$.

3.$a,b$为奇数。设$a=2m+1,b=2n+1$，则$p=4[m(m+1)+n(n+1)]+2$.

由于$m,m+1$中有$1$个偶数，故$m(m+1)$为偶数，同理，$n(n+1)$为偶数，即$m(m+1)+n(n+1)$为偶数，有$p=8l+2\text{（}l\text{为自然数）}$.

即$p\bmod 4\neq 3$.

即$n>=4$时，$b$为偶数.

若$4\nmid b$，则$a$为偶数。由于能写成$8l+6$的形式的数无法写生两个完全平方数的和（$8l+6=4(2l+1)+2$，即能$8l+6$写成$4l+2$的形式，但已证能写成$4l+2$形式的数一定不是完全平方数），故$a$为奇数，矛盾。

即$4\mid b$。

直接搜索，$b$要$4$个$4$个加（n=3时暴力搜索，有答案不超过$10000$个的限制，因此$m$很小）。


---

## 作者：tuyongle (赞：31)

枚举前两个数，即可推出公差，从而推出整个数列，判断质数即可。

代码如下：

```
#include<iostream>
#include<algorithm>
using namespace std;
struct data{
    int a,b;
};
data ans[10010];
int n,m,cnt;
bool book[250*250*2+10];//用来存是否为双平方数 
bool cmp(data x,data y){
    if(x.b<y.b)return true;
    if(x.b==y.b&&x.a<y.a)return true;
    return false;
}
int main(){
    cin>>n>>m;
    for(int i=0;i<=m;i++)
    for(int j=0;j<=m;j++)
    book[i*i+j*j]=true;
    int maxm=m*m*2;//枚举的上限 
    for(int i=0;i<=maxm;i++)
    if(book[i])
    for(int j=i+1;j<=maxm;j++)
    if(book[j]){
        int d=j-i;//公差 
        int maxi=i+d*(n-1);//最后一个数 
        if(maxi>maxm)break;//如果最后一个数大于上限，则跳出 
        bool f=true;
        for(int j=i+d;j<=maxi;j+=d)
        if(!book[j]){
            f=false;
            break;
        }//如果等差数列有一个数不是质数，则不是合法答案 
        if(f){
            cnt++;
            ans[cnt].a=i;
            ans[cnt].b=d;
        }//储存合法答案 
    }
    if(cnt==0){
    	cout<<"NONE";
    	return 0;
    }//如果没有，输出"NONE" 
    sort(ans+1,ans+cnt+1,cmp);//对合法答案排序 
    for(int i=1;i<=cnt;i++)
    cout<<ans[i].a<<' '<<ans[i].b<<endl;//输出 
    return 0;
}
```

---

## 作者：韩雅慧 (赞：19)

##更快的方法

每次枚举数列的前两项，就可以决定整个数列了！

b[i]=1表示i在集合中 

**要注意每次算出数列中的最小数，不能小于0**，

加上这个优化后就不超时了，最慢的点都只84ms

具体见代码 :

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int b[200010],a[200010];
bool cmp(int x,int y){
    return x>y;
}
struct node{
    int u, v;
}w[200010];
bool tmp(node x,node y){
    if(x.u!=y.u)return x.u<y.u;
    return x.v<y.v;
}
int main( ){
    int i,j,k,n,m,sum=0,num=0;
    scanf("%d%d",&n,&m);
    for(i=0;i<=m;i++)
        for(j=0;j<=m;j++){
            if(b[i*i+j*j]==0)a[++sum]=i*i+j*j;
            b[i*i+j*j]=1;
        }
    sort(a+1,a+sum+1,cmp);         //从大到小排序 
    for(i=1;i<=sum-n+1;i++)
        for(j=i+1;j<=sum-n+2;j++){           //枚举前两个数 
            int p=a[i]-a[j],q=n-2,t=a[j],flag=1; //p是公差，flag标记是否可成等差数列，q控制数列长度 
            if(t-(n-2)*p<0)break;        //优化 
            while(q){
                q--;
                t-=p;
                if(t<0){
                    flag=0;
                    break;
                }
                if(b[t]==0){         //不在集合中 
                    flag=0;
                    break;
                }
            }
            if(flag==1){
                w[++num].u=p;
                w[num].v=t;
            }
        }
    if(num==0){
        printf("NONE\n");
        return 0;
    }
    sort(w+1,w+num+1,tmp);    //按输出要求排序 
    for(i=1;i<=num;i++)
        printf("%d %d\n",w[i].v,w[i].u);
    return 0;
}
```

---

## 作者：lianliangyu (赞：11)

十分激动地发第一篇题解

这道绿题数据量也太水了吧，我打个暴搜都能AC。

其实就是先用桶排序（不会爆），然后再把数集中起来，搜索一下即可。

两重循环中还要一些神奇的判断和剪枝，让程序跑得更快。这样就能过了！

代码如下：
```
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
using namespace std;
int n,m,p,q,s[125000];
bool num[125000];
int main()
{
    scanf("%d%d",&n,&m);
    memset(num,false,sizeof(num));  //初始化 
    int i,j,a,b,l,cnt=0;
    for(i=0;i<=m;i++)
    for(j=0;j<=m;j++)
    num[i*i+j*j]=1;        //存所有双平方数 
    l=0;
    for(i=0;i<=125000;i++)
    if(num[i]) s[++l]=i;   //把所有数集中
//	for(i=1;i<=l;i++)
//	cout<<s[i]<<" ";
    for(b=1;b<s[l];b++)   //从小到大搜，就不用排序了 
    for(i=1;i<l-1;i++)    //因为n>=3，所以运行到倒数第三个就可以了
    {
    if(s[i]+(n-1)*b>s[l]) break;    //判断优化 
    for(a=2;a<=n;a++)
    if(!num[s[i]+(a-1)*b]) break;   //搜素等差数列 
    if(a==n+1&&num[s[i]+(n-1)*b])   //判断是否满足要求 
    printf("%d %d\n",s[i],b),cnt++; 
    }
    if(!cnt) printf("NONE");    //无答案则输出NONE
    return 0;
}
```

---

## 作者：逆时针的记忆 (赞：7)

1. 我的第一篇题解
1. 废话少说
1. 上代码
```
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;
int n,m,x[10005],y[10005],s[21050];
bool f[1250005];//这个不解释
```
```c
void kpai(int l,int r,int a[],int b[])//快速排序 
{
	int i,j,m,n,tmp;
	i=l; j=r; m=a[(l+r)/2]; n=b[(l+r)/2];
	while (i<=j)
	{
		while (m>a[i]||(m==a[i]&&n>b[i])) i++;
		while (m<a[j]||(m==a[j]&&n<b[j])) j--;
		if (i<=j)
		{
			tmp=a[i];
			a[i]=a[j];
			a[j]=tmp;
			tmp=b[i];
			b[i]=b[j];
			b[j]=tmp;
			i++;
			j--;
		}
	}
	if (i<r) kpai(i,r,a,b);
	if (l<j) kpai(l,j,a,b);
}
```

```c
int biao(int m)//打表，双平方数的表
{
	memset(f,false,sizeof(f));
	int i,j;
	for (i=0; i<=m; i++)
		for (j=i; j<=m; j++) f[i*i+j*j]=true;
	m=m*m*2; j=0;
	for (i=0; i<=m; i++)
		if (f[i]) j++,s[j]=i;
	return j;
}
```

```c
int main()//主程序
{
	int i,k,a,b,sb,t,l=0;
	scanf ("%d%d",&n,&m);
	sb=biao(m);
	m=m*m;
	for (k=1; k<=sb; k++)
	{
		a=s[k];//a一定是双平方数，如果不明白，仔细看题目，题目会帮你明白 
		for (b=1; b<=3000; b++)//至于这里为什么是3000，实践才是检验真理的唯一标准，小一点不要紧 
		{
			t=1;
			for (i=2; i<=n; i++)
			{
				if (f[a+t*b]) t++;
				else break;
			}
			if (t==n)
			{
				l++;
				x[l]=a;
				y[l]=b;
			}
		}
	}
	if (l==0) printf ("NONE\n");
	else
	{
		kpai(1,l,y,x);
		for (i=1; i<=l; i++) printf ("%d %d\n",x[i],y[i]);
	}
	return 0;
}
```
- ~~打到一半~~打完才发现自己代码好长
- 这是大佬（**ju ruo**）的标志
- 希望这篇题解有用

---

## 作者：SUNCHAOYI (赞：7)

## 枚举即可

------------

**1.枚举所有双平方数**

**2.记录下所有双平方数**

**3.从小到大进行搜索（便可不用排序）**

**--如果下一项比之前的小，便不符合条件，直接跳过**

**从第二项开始，判断如果不满足等差数列，直接跳过**

**否则判断如果项数刚好等于等差数列的长度且为等差数列（条件满足）：直接输出即可（起点，公差）**

------------

**question：题目中要求“这些行应该先按b排序再按a排序”，这应该怎么办呢？**

**仔细观察，发现一开始便从小开始循环，故不用再排序了，安心输出就好**

------------

**细节：题目中“如果没有找到数列,输出NONE”可千万不要忘了！！！**

**具体方法：有输出，则输出后标记一下（标记为1即可），最后循环完后判断，如果为0才需要输出NONE，否则就直接结束咯！**

------------

## 代码：
```

#include<iostream>
using namespace std;
const int MAX = 250 * 250 * 2 + 1;//数组开的最大 
bool f[MAX] = {0},ok = 0;int num[MAX]; 
int main()
{
    int n,m,cnt=0,k;
	cin>>n>>m;
	for (int i = 0;i <= m;i++)
		for (int j = 0;j <= m;j++) f[i * i + j * j] = 1;//枚举所有双平方数 
	for (int i = 0;i <= MAX;i++)
		if (f[i]) num[++cnt] = i;//记录下双平方数
	for (int i = 1;i < num[cnt];i++)//从小到大进行搜索 
	{
		for(int j = 1;j < cnt - 1;j++)
		{
			if (num[j] + (n - 1) * i > num[cnt]) break;//如果下一项比之前的小，便不符合条件，直接跳过 
			for (k = 2;k <= n;k++)//k直接从2开始，第二项 
		    	if (!f[num[j] + (k - 1) * i]) break;//如果不满足等差数列，直接跳过 
		    if (k == n + 1 && f[num[j] + (n - 1) * i])//如果k刚好等于等差数列的长度且为等差数列 
			{
				cout<<num[j]<<" "<<i<<endl;//输出答案(前面已经从小的开始循环，故不用考虑顺序了) 
				ok = 1;//标记有解 
			}
		}	
	} 
	if (!ok) cout<<"NONE"<<endl;//无解的输出 
	return 0;
}
```


---

## 作者：「QQ红包」 (赞：7)

楼下的分析十分清楚，此处放c++代码。

题解by：redbag

TLE了怎么办？如果代码没问题就多提交几遍。

记录：http://www.luogu.org/record/show?rid=634538

```cpp

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
struct hhh
{
    int a,b;
}a[100010];
int cmp(const hhh &a,const hhh &b)//先按a排序再按b排序 
{
    if(a.b<b.b) return 1;
    if(a.b>b.b) return 0;
    if(a.a<b.a) return 1;
    if(a.a>b.a) return 0;
    return 1;
}
int m,n,p,q,i,j,aa;
int f[100000];
int c[100000];
int cc;//存双平方数的个数 
int fff=0;
int ff;//ff标记是否越界&&是否符合条件。fff标记符合条件的等差数列的个数。 
int main()
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
    scanf("%d%d",&n,&m);//n等差数列长度,m搜索双平方数的上界 
    for (p=0;p<=m;p++)//把能表示成p的平方 + q的平方的数标记 
        for (q=p;q<=m;q++)
        {
            if (f[p*p+q*q]==0)//如果这个数之前没标记过就再标记 
            {
                cc++;//个数+1 
                c[cc]=p*p+q*q;//存起来 
                f[p*p+q*q]=1; //标记 
            } 
        }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    sort(c+1,c+cc+1);//c数组从小到大排序 
    i=0;
    for (i=1;i<=cc-n+1;i++)//因为后面有n个双平方数所以最多到cc-n+1 
    {
        aa=c[i];//存结果中的a 
        j=i;//初始化 
        int flag;
        do
        {
            j++;
            ff=0;//初始化 
            flag=0;
            int b=c[j]-c[i];//等差数列的差。 
            if (j>cc-n+2)//后面没那么多个数 
            {
                flag=1;// 标记 
                break;//跳出当前循环 
            }
            if (aa+b*(n-1)>c[cc])//如果最大的那个大于符合条件的最大的双平方数 
            {
                flag=1;// 标记 
                break;//跳出当前循环 
            }
            for (int k=2;k<=n-1;k++)//把后面的也给枚举+判断
            {
                if (f[aa+k*b]!=1)//如果这个不满足条件后面也不要算了
                {
                    ff=1;// 标记 
                    break;//跳出当前循环 
                }
            } 
            if (ff==0)//如果符合条件 
            {
                fff=fff+1;;//存个数的
                a[fff].a=aa;
                a[fff].b=b;
            }
        }while (flag==0); 
    } 
    sort(a+1,a+fff+1,cmp);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    for (i=1;i<=fff;i++)
    {
        printf("%d %d\n",a[i].a,a[i].b);
    }
    if (fff==0)
    printf("NONE");
    return 0;
}

```

---

## 作者：Celebrate (赞：2)

这一题我不用高深的算法，我直接用暴力过了

其实这题数据很水，如果再多一些，可能就AC不了了

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstdlib>
using namespace std;
struct node
{
	int x,y;
}a[11000];int len=0;//a记录每一个开头和公差 
int n,m;
bool f[12510000];//f[i]表示i是否可以被找到 
bool bk;
inline int cmp(const void *xx,const void *yy)
{
	node x=*(node*)xx;
	node y=*(node*)yy;
	if(x.y>y.y) return 1;
	if(x.y<y.y) return -1;
	if(x.x<y.x) return -1;
	if(x.x>y.x) return 1;
	return 0;
}
inline int _(int x){return x*x;}//这样更加方便 
inline void Arithmetic_Progressions()
{
	int i,j,k,t;scanf("%d%d",&n,&m);
	t=_(m)+_(m);
	memset(f,false,sizeof(f));
	for(i=0;i<=m;i++)//S集合中所有的数 
		for(j=0;j<=m;j++)
			f[_(i)+_(j)]=true;
	for(i=0;i<=30000;i++)//枚举头，根据答案，我感觉30000就够了，不用太多，我也不知道为什么 
	{
		if(f[i]==false) continue;//如果头都不可以的话 
		for(j=1;j<=5000;j++)//枚举公差 
		{	
			bk=true;
			for(k=1;k<n;k++)//枚举长度 
			{
				if(f[i+j*k]==false)
				{
					bk=false;break;
				}
			}
			if(bk==true)//记录 
			{
				len++;
				a[len].x=i;a[len].y=j;
			}
		}
	}
	qsort(a+1,len,sizeof(node),cmp);//排序 
	if(len==0) printf("NONE\n");//输出 
	else for(i=1;i<=len;i++) printf("%d %d\n",a[i].x,a[i].y);
}
int main()
{
	Arithmetic_Progressions();return 0;
}
```

---

## 作者：转身、已陌路 (赞：2)

这是一道比较基础的搜索题  比较难想的是怎么搜索？？

显然枚举是不会超时 的 那么怎么枚举呢？？？

我枚举的是第一个数 和 第二个数  这样公差自然而然就出来了

即可以推出整个等差数列 然后判断质数就好

代码：

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
bool f[250*250*2+10];//用来存质数
int n,m; 
int t=0;
struct hehe
{
    int z,y;
}pp[100000];
bool mmp(hehe a,hehe b)//按照题意进行排序
{
    return(a.y<b.y||(a.y==b.y&&a.z<b.z));
}
int main()
{
    int num=0;
    int sum;
    cin>>n>>m;
    memset(f,false,sizeof(f));
    for (int i=0;i<=m;i++)
    for (int j=0;j<=m;j++)
    f[i*i+j*j]=true;//类似于桶排序的一个判断质数平方和的方法
    int mm=m*m*2;//上限
    for (int i=0;i<=mm;i++)
    {
        if (f[i])
        {
            for (int j=i+1;j<=mm;j++)
            {
                if (f[j])
                {
                    sum=0;
                    int nn=i+(n-1)*(j-i);//最后一个数
                    if (nn>mm) break;//剪枝  如果最后一个数出超过上限  就跳出
                    int g=j-i;//计算公差
                    for(int k=i;k<=nn;k+=g)
                    {
                        if (f[k]) sum++;
                        else break;//这个语句可以保证你不会超时  很好的剪枝  粗心漏了就会超时
                    }
                    if (sum==n) {pp[++t].z=i;pp[t].y=g;num++;}//存储合法的数
                }
            }
        }
    }
    if (num==0) cout<<"NONE";//额外判断 没有数列的情况
    else 
    {
        sort(pp+1,pp+t+1,mmp);//排序
    }
    for (int i=1;i<=t;i++) cout<<pp[i].z<<" "<<pp[i].y<<endl;//美妙的输出时间！！！！
    return 0;
}
```

---

## 作者：YczSS (赞：2)

分析

这道题就是暴力搜索,方法是很简单的：枚举所有的可能解，注意剪枝。


但是在编程细节上要注意，很多时候你的程序复杂度没有问题，但常数过大就决定了你的超时（比如说，你比别人多赋值一次，这在小数据时根本没有区别，但对于1个运行5s的大数据，你可能就要用10s甚至更多）。


具体来说，预处理把所有的bisquare算出来，用一个布尔数组bene[i]记录i是否是bisquare 另外为了加速，用list记录所有的bisquare（除去中间的空位置，这在对付大数据时很有用），list中的数据要有序。


然后枚举list中的数，把较小的作为起点，两数的差作为公差，接下来就是用bene判断是否存在n个等差数，存在的话就存入path中，最后排序输出。 此时缺少重要剪枝，会超时


思考程序发现，费时最多的地方是枚举list中的数，所以对这个地方的代码加一些小修改，情况就会不一样：

1.在判断是否存在n个等差数时，从末尾向前判断（这个不是主要的）。

2.在枚举list中的数时，假设为i,j，那么如果list[i]+(list[j]-list[i])×(n-1)>lim（lim是最大可能的bisquare），那么对于之后的j肯定也是大于lim的，所以直接break掉。（这个非常有效）


AC，最大数据0.464s(如果是PASCAL的话应该还不止。请看C++的GPF的程序)。


其实输出时可以不用排序，用一个指针b[i]存公差为i的a的链表，由于搜索时a是有序的，存到b[i]中也应是有序的，这样就可以直接输出。对极限数据b的范围应该不超过m^2/n=2500,即b:array[1..2500]of point; 而如果qsort的话，复杂度为n\*logn,n<=10,000


枚举a,b也可以过的 。。要加几个小优化

```cpp
type ac=record
       a,b:longint;
     end;
var b:array[0..125000] of boolean;
    a:array[1..125000] of longint;
    r:array[1..125000] of ac;
    n,m,lim,i,j,k,p,q,la,d,v,lr:longint;
procedure qsort1(low,high:longint);
  var i,j,k:longint;
      tmp:ac;
  begin
    i:=low;
    j:=high;
    while low<high do
      begin
        while (low<high) and (r[low].b<=r[high].b) do dec(high);
        if low<high then begin tmp:=r[low];r[low]:=r[high];r[high]:=tmp;end;
        while (low<high) and (r[low].b<=r[high].b) do inc(low);
        if low<high then begin tmp:=r[low];r[low]:=r[high];r[high]:=tmp;end;
      end;
    if i<low-1 then qsort1(i,low-1);
    if high+1<j then qsort1(high+1,j);
  end;
procedure qsort2(low,high:longint);
  var i,j,k:longint;
      tmp:ac;
  begin
    i:=low;
    j:=high;
    while low<high do
      begin
        while (low<high) and (r[low].a<=r[high].a) do dec(high);
        if low<high then begin tmp:=r[low];r[low]:=r[high];r[high]:=tmp;end;
        while (low<high) and (r[low].a<=r[high].a) do inc(low);
        if low<high then begin tmp:=r[low];r[low]:=r[high];r[high]:=tmp;end;
      end;
    if i<low-1 then qsort2(i,low-1);
    if high+1<j then qsort2(high+1,j);
  end;
procedure save;
  begin
    inc(lr);
    r[lr].a:=a[i];
    r[lr].b:=d;
  end;
begin
  readln(n);
  readln(m);
  for i:=0 to 2*m*m do
    b[i]:=false;
  for p:=0 to m do
    for q:=p to m do
      begin
        k:=p*p+q*q;
        b[k]:=true;
      end;
  la:=0;
  for i:=0 to 2*m*m do
    if b[i] then
      begin
        inc(la);
        a[la]:=i;
      end;
  lim:=a[la];
  lr:=0;
  {for i:=1 to la do
    write(a[i],' ');
  writeln;}
  for i:=1 to la-n+1 do
    for j:=i+1 to la do
      begin
        d:=a[j]-a[i];
        if a[i]+(n-1)*d>lim then break;
        k:=a[j];
        for v:=3 to n do
          if b[k+d] then k:=k+d
            else break;
        if k-a[i]=(n-1)*d then save;
      end;
  if lr=0 then writeln('NONE')
    else
      begin
        qsort1(1,lr);
        j:=1;
        k:=0;
        while j<=lr do
          begin
            v:=r[j].b;
            while (j<=lr) and (r[j].b=v) do j:=j+1;
            dec(j);
            if j>k+1 then qsort2(k+1,j);
            k:=j;
            inc(j);
          end;
        for i:=1 to lr do
          writeln(r[i].a,' ',r[i].b);
      end;
end.
```

---

## 作者：Lates (赞：1)

考虑枚举前两项，得到公差，然后暴力判后面的符不符合双平方数。

由于 $p,q\in[0,m]$，所以可以通过类似素数筛的方法筛出双平方数。

然后写完会 T 一点。

由于朴素枚举前两项再判是不是双平方数要 $O((m^2)^2)$，$m$ 最大到250，所以最坏情况下是不行的。

考虑把范围内所有双平方数**去重**后保存下来，最多时是21047，所以复杂度就成了 $O(21047^2)$。$5s$ 的时限绰绰有余了。测出来是 $1.01s$.

Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read(){
	register int x=0,f=0,ch=getchar();
	while('0'>ch||ch>'9')f^=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	return f?-x:x;
}
const int MAX=125005;
int n,m,chc[MAX],b;
struct E{
	int a,b;
}ans[10005];
int tot=0,Mx,fl,p[MAX],cnt;
inline bool cmp(E x,E y){
	if(x.b==y.b)return x.a<y.a;
	return x.b<y.b;
}
signed main(){
	n=read(),m=read();
	Mx=(m*m)<<1;
	for(register int i=0;i<=m;++i)
		for(register int j=0;j<=m;++j){
			if(!chc[i*i+j*j])p[++cnt]=i*i+j*j;
			chc[i*i+j*j]=1;
		}
	printf("%d ",cnt);
	sort(p+1,p+cnt+1);
	for(register int j=1;j<=cnt;++j){
		for(register int k=j+1;k<=cnt;++k){
			b=p[k]-p[j];fl=0;
			if(p[j]+(n-1)*b>Mx)continue;
			for(register int i=2;i<n;++i)if(!chc[p[j]+i*b]){fl=1;break;}
			if(!fl)ans[++tot]=(E){p[j],b};
		}
	}
//	for(register int a=0;a<=Mx;++a){
//		if(!chc[a])continue;
//		for(register int nex=a+1;nex<=Mx;++nex){
//			b=nex-a;fl=0;
//			if(!chc[nex]||a+(n-1)*b>Mx)continue;
//			for(register int i=2;i<n;++i)if(!chc[a+i*b]){fl=1;break;}
//			if(!fl)ans[++tot]=(E){a,b};
//		}
//	}
	if(tot==0)return printf("NONE\n"),0;
	sort(ans+1,ans+tot+1,cmp);
	for(register int i=1;i<=tot;++i){
		printf("%d %d\n",ans[i].a,ans[i].b);
	}
	return 0;
}

```



---

## 作者：水库中的水库 (赞：1)

这道题我一开始做的时候思路特别简单，观察数据发现双平方数最多也就只有$250^2$左右（还有很多重复的），很明显可以全部枚举出来

对于等差数列来说，我们只需要枚举前面两个数

但对于后面的数的判定，我最开始想到的是二分所有的双平方数，但发现多了个$log$就会T掉，考虑到双平方数大小在$260^2*2$以内，可以直接用一个数组标记就可以了

另外这道题还有一个坑是没有解输出NONE

```cpp
/***************************************************************
	File name: P1214.cpp
	Author: ljfcnyali
	Create time: 2019年05月06日 星期一 11时23分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

int n, m, a[1000010], sum, ans, k;
bool vis[1000010];

struct node
{
	int x, y;
}f[50010];

inline int cmp(node a, node b)
{
	return a.y == b.y ? a.x < b.x : a.y < b.y;
}

inline bool find(int l, int r, int x)
//二分其实不要用
{
	while ( l <= r ) 
	{
		int Mid = (l + r) / 2;
		if ( x == a[Mid] ) return true;
		if ( x < a[Mid] ) r = Mid - 1;
		else l = Mid + 1;
	}
	return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 0, m) REP(j, 0, m) { a[++ sum] = i * i + j * j; vis[a[sum]] = true; }
	sort ( a + 1, a + sum + 1 );	
	REP(i, 1, sum - 1) if ( a[i] == a[i + 1] ) { a[i] = -1; ++ k; }
	sort ( a + 1, a + sum + 1 );
	REP(i, k + 1, sum - 1)
		REP(j, i + 1, sum)
		{
			int cha = a[j] - a[i], p = a[j];
			bool flag = true;
			REP(o, 3, n)
			{
				p += cha;
				if ( vis[p] == false ) { flag = false ; break ; }
			}
			if ( flag == true ) { f[++ ans].x = a[i]; f[ans].y = cha; }
		}
	if ( ans == 0 ) { printf("NONE\n"); return 0 ; }
	sort ( f + 1, f + ans + 1, cmp );
	REP(i, 1, ans ) printf("%d %d\n", f[i].x, f[i].y);
    return 0;
}
```

---

## 作者：楯山文乃 (赞：1)

这一题是有技巧的搜索~~~

倒着搜更快哦~~~

```cpp
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<map>
#include<vector>
using namespace std;
int n,m,i,j,k,sum,num,ans,flag=0;
int a[1000000],f[1000000];
struct node{
    int x,y;
}d[1000000];
int cmp(node u,node v){
    if(u.y!=v.y) return u.y<v.y;
    return u.x<v.x;
}
int main(){
    scanf("%d%d",&n,&m);//读入~ 
    for(i=0;i<=m;i++)//记得是从零开始！！！不然会漏掉许多完全平方数！ 
        for(j=0;j<=m;j++){
            if(f[i*i+j*j]==0){
                f[i*i+j*j]=1;
                num++;
                a[num]=i*i+j*j;
            }
        }
    for(i=1;i<=num;i++){
        for(j=1;j<=m*m;j++){
            if(a[i]+(n-1)*j>m*m+m*m) break;
            ans=1;
            for(k=n-1;k>=1;k--){//越到后面越稀疏，所以倒着搜排除得更快~~
                if(f[a[i]+k*j]==1) ans++;
                else break;
            }
            if(ans==n){
                sum++;
                d[sum].x=a[i]; d[sum].y=j;
                flag=1;//标记，证明有等差数列~ 
            }
        }
    }
    sort(d+1,d+sum+1,cmp);//排序 
    for(i=1;i<=sum;i++){
        printf("%d %d\n",d[i].x,d[i].y);
    }
    if(flag==0) printf("NONE\n");
    return 0;
}
```

---

## 作者：Violette (赞：0)

大体思路：

可以设置布尔类型的flag数组，

在二重循环的遍历中，把数组的第i乘i加j乘j的这个下标赋值为true。

到后面，发现需要排序，且两个元素必须在一起发生变化，所以想到需要用到结构体。

把上限范围内的双平方数储存起来，如果有一项没有在bool数组里，则令bool值f为false。

在经过对等差数列每一项检查后，f仍为真，则满足题。

而num记录满足条件的数列的个数，num为0，则输出NONE。

满足条件的数列，输出首项和公差。

代码：

```cpp
#include<iostream>
#include<algorithm> 
using namespace std;
const int NR=250*250*2;
struct dc{
    int a;
    int b;
}ans[NR];
bool cmp(dc x,dc y){
    if(x.b!=y.b) return x.b<y.b;
    return x.a<y.a;
}
bool f[NR+10];
int sum[NR];
int main() {
int n,m;
cin>>n>>m;
for(int i=0;i<=m;i++)
    for(int j=0;j<=m;j++)
        f[i*i+j*j]=true;
int sz=0;
for(int i=0;i<=2*m*m;i++){
    if(f[i]) sum[++sz]=i;
}
int num=0;
for(int i=1;i<=sz;i++)
    for(int j=i+1;j<=sz;j++){
        int a=sum[i],b=sum[j]-sum[i];
bool pd=true;
if(a+(n-1)*b>2*m*m) break;
for(int k=2;k<=n-1;k++)
    if(!f[a+k*b]){
        pd=false;
        break;
    }
if(pd){
    num++;
    ans[num].a=a;
    ans[num].b=b;
}
}
sort(ans+1,ans+1+num,cmp);
for(int i=1;i<=num;i++){
    cout<<ans[i].a<<" "<<ans[i].b<<endl;
}
if(num==0) cout<<"NONE";
    return 0;
}

```


---

## 作者：不存在之人 (赞：0)

### 思路：

为了减少时间复杂度,我们先预处理出第$i$个数是否可以表示为$p^2+q^2$

还可以知道第$l$个可以表示为$p^2+q^2$的是什么数

$ans[i]-$第$i$个数是否可以表示为$p^2+q^2$可以为$1$,不可以为$0$

**进行枚举(枚举长度,起点)适当剪枝**

**判断是否合法**
```cpp
#include<cstdio>
using namespace std;
int ans[1000100],f[1000000];
int main()
{
    int n,m,p,q,i,l=0,j,k,d1=0;
    scanf("%d%d",&n,&m);
    for(p=0;p<=m;p++)
        for(q=p;q<=m;q++)
		{
            ans[p*p+q*q]=1;
        }
    l=0;
    for(i=0;i<=m*m+m*m;i++)
	{
        l+=ans[i];
        if(ans[i]) f[l]=i;
    }
    for(j=1;j<=m*m*2/(n-1);j++)
	{
        for(i=1;i<=l;i++)
		{
            if(f[i]+j*(n-1)>m*m*2) break;
            int c=1,d=f[i];
            for(k=1;k<=n-1;k++)
			{
                d=d+j;
                if(!ans[d])
				{
                    c=0;
                    break;
                }
            }
            if(c)
			{
				d1=1;
				printf("%d %d\n",f[i],j);
			}
        }
    }
    if(d1==0) printf("NONE\n");
    return 0;
}
```

---

## 作者：西瓜狼 (赞：0)

这道题可以用暴力。先求出所有双平方数，再枚举a,判断是否成立，成立就存进数组里。

```pascal
var
        c:array[0..1250000]of boolean;//判断是不是双平方数
        a:array[0..1000000]of longint;//存双平方数
        d:array[0..10000001,1..2]of longint;//存首项和公差
        i,j,k,ans,n,t,m,l,f:longint;
        p:boolean;
procedure qsort(l,r:longint);//快排
var
        i,j,mid,h:longint;
begin
        i:=l;
        j:=r;
        mid:=a[(i+j)div 2];
        repeat
                while a[i]<mid do inc(i);
                while a[j]>mid do dec(j);
                if i<=j then
                        begin
                                h:=a[i];
                                a[i]:=a[j];
                                a[j]:=h;
                                inc(i);
                                dec(j);
                        end;
        until i>j;
        if i<r then
                qsort(i,r);
        if l<j then
                qsort(l,j);
end;
procedure qsort1(l,r:longint);//快排
var
        mid,mid1,i,j,h:longint;
begin
        i:=l;
        j:=r;
        mid:=d[(i+j)div 2,2];
        mid1:=d[(i+j) div 2,1];
        repeat
                while (d[i,2]<mid)or(d[i,2]=mid)and(d[i,1]<mid1)do inc(i);
                while (d[j,2]>mid)or(d[j,2]=mid)and(d[j,1]>mid1)do dec(j);
                if i<=j then
                        begin
                                d[0]:=d[i];
                                d[i]:=d[j];
                                d[j]:=d[0];
                                inc(i);
                                dec(j);
                        end;
        until i>j;
        if j>l then
                qsort1(l,j);
        if r>i then
                qsort1(i,r);
end;
begin
        
        readln(n);
        readln(m);//要找的等差数列的长度n，搜索双平方数的上界m
        t:=0;
        for i:=0 to m do
                for j:=0 to m do
                        if c[i*i+j*j]=false then
                                begin
                                        inc(t);
                                        a[t]:=i*i+j*j;
                                        c[i*i+j*j]:=true;
                                end;//求所有的双平方数
        qsort(1,t);
        k:=0;
        ans:=0;
        for i:=1 to t-n+1 do
                begin
                        l:=i;
                        while (l+1<=t-m+1)and(a[l+1]>a[i])and(a[i]+(m-1)*(a[l+1]-a[i])<=720000) do
                                begin
                                        f:=a[l+1]-a[i];//求公差
                                        inc(l);
                                        p:=true;//初始化
                                        for j:=1 to n-1 do
                                        begin
                                         	if c[a[i]+f*j]=false then
                                         	begin
                                         		p:=false;
                                         		break;
                                                end;//如果有不是双平方数，则退出
                                        end;
                                        if p then//判断可不可行
                                        begin
                                             	inc(ans);
                                              	d[ans,1]:=a[i];
                                                d[ans,2]:=f;
                                        end;
                                end;
                end;
        qsort1(1,ans);//先按b排序再按a排序。
        for i:=1 to ans do
                writeln(d[i,1],' ',d[i,2]);//输出答案
        if ans=0 then
                writeln('NONE');
end.
```


---

