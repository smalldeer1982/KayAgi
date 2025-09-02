# [USACO2.2] 派对灯 Party Lamps

## 题目描述

在 IOI98 的节日宴会上，我们有 $n$ 盏彩色灯，他们分别从 $1 \sim n$ 被标上号码。这些灯都连接到四个按钮：

按钮 $1$：当按下此按钮，将改变所有的灯：本来亮着的灯就熄灭，本来是关着的灯被点亮。

按钮 $2$：当按下此按钮，将改变所有奇数号的灯。

按钮 $3$：当按下此按钮，将改变所有偶数号的灯。

按钮 $4$：当按下此按钮，将改变所有序号是 $3k+1 \ (k \in [0,+\infty) \cap \mathbb Z)$ 的灯。例如：$1,4,7,10 \dots$

一个计数器 $c$ 记录按钮被按下的次数。当宴会开始，所有的灯都亮着，此时计数器 $c$ 为 $0$。

你将得到计数器 $c$ 上的数值和经过若干操作后某些灯的状态。写一个程序去找出所有灯最后可能的与所给出信息相符的状态，并且没有重复。


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$10 \le n \le 100$，$0 \le c \le 10^4$。

【样例解释】  
在这个样例中，有三种可能的状态：

- 所有灯都关着

- $1,4,7,10$ 号灯关着，$2,3,5,6,8,9$ 亮着。

- $1,3,5,7,9$ 号灯关着，$2,4,6,8,10$ 亮着。


翻译来自NOCOW

USACO 2.2


## 样例 #1

### 输入

```
10
1
-1
7 -1
```

### 输出

```
0000000000
0101010101
0110110110
```

# 题解

## 作者：Orzalpha (赞：45)

~~其实这道题掌握了规律就很简单。~~

规律如下：

规律一：对于任意c，总能转化为c≤2时的某种状态。

首先，给出公理。

公理1：按钮的顺序不决定状态。打个例子，12和21得到的状态是相同的。

公理2：同一个按钮按两次等于没按。打个例子，121与2得到的状态是相同的。

公理3：按钮123满足任意两个等于第三个。打个例子，12得到的状态与3是相同的。

通过以上三个公理，可以得到如下推论：

推论1：对于任意c＞4，所得到的状态总是与c≤4中的某种不重复序列的状态相同。证明：对于c＞4的按钮序列中，由抽屉原理得必然有一个按钮至少按了两次，就可以抵消掉。打个例子，12343→124。

推论2：对于任意2＜c≤4的不重复序列，所得到的状态总是与c≤2中的某种状态相同。证明：对于2＜c≤4的不重复序列，4出现的次数总是小于等于1，即至少有2个123中的按钮。由公理2与公理3得，任意2＜c≤4的不重复序列总是与c≤2的某种序列等效。打个例子，1234→114→4。

至此，我们可以得出最终的结论，即规律一：对于任意c，总能转化为c≤2时的某种状态。

规律二：当c≤2时，分别出现如下状态。

当c=0时，0；

当c=1时，1，2，3，4；

当c=2时，0，1(23)，2(13)，3(12)，14，24，34；

另外，由规律一，当c＞2时，有可能取到c≤2时的所有情况，即0，1，2，3，4，14，24，34。

规律三：无论哪种状态，循环节总为6。

因此，根据这三个规律，就可以用常量表存出所有c的情况，只需要挨个检验即可。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int h[9][7]= {{},
	{0,0,0,0,0,0}, //1
	{0,0,0,1,1,1}, //34
	{1,0,1,0,1,0}, //2
	{1,0,1,1,0,1}, //4
	{0,1,0,0,1,0}, //14
	{0,1,0,1,0,1}, //3
	{1,1,1,0,0,0}, //24
	{1,1,1,1,1,1}  //0
};
int n,c,on[101],off[101];
inline void work(int w[9])
{
	int flag=1;
	for(int k=1; k<=w[0]; k++)
	{
		int tag=0;
		for(int i=1; i<=on[0]; i++)
			if(!h[w[k]][on[i]%6])
			{tag=1;break;}
		if(tag) continue;
		for(int i=1; i<=off[0]; i++)
			if(h[w[k]][off[i]%6])
			{tag=1;break;}
		if(tag) continue;
		flag=0;
		for(int i=1; i<=n; i++)
			printf("%d",h[w[k]][i%6]);
		printf("\n");
	}
	if(flag) printf("IMPOSSIBLE");
	exit(0);
}
int main()
{
	int tmp;
	scanf("%d%d",&n,&c);
	while(1)
	{
		scanf("%d",&tmp);
		if(tmp==-1) break;
		on[++on[0]]=tmp;
	}
	while(1)
	{
		scanf("%d",&tmp);
		if(tmp==-1) break;
		off[++off[0]]=tmp;
	}
	if(c==0)
	{int w[9]={1,8};work(w);}
	if(c==1)
	{int w[9]= {4,1,3,4,6};work(w);}
	if(c==2)
	{int w[9]= {7,1,2,3,5,6,7,8};work(w);}
	if(c>2)
	{int w[9]= {8,1,2,3,4,5,6,7,8};work(w);}
	return 0;
}
```

---

## 作者：fastle (赞：30)

看楼下的方法都是模拟按键，其实并不用那么麻烦。

我们来分析一下对灯的操作

1.对所有灯的，这时吧所有灯看成一个整体

2.奇偶数的操作，这时可以把每两个数看成一个循环节

3.对3X+ 1的操作，这时可以把每三个数看成一个循环节

显而易见的，我们把序列看成6个一组的循环节，便能模拟整个序列。

用笔画一下，我们发现将这个含六个元素的序列进行变换最终只会有八种结果，那么我们只需要判断一下最后这八种结果

最后是否符合题意要求就行了（至于他是怎么变换的我们不用管）

这时的八种情况是这样色的

const int map[8][7] ={

0,0,0,0,0,0,0,

0,0,0,1,1,1,0,//1

0,0,1,0,1,0,1,

0,0,1,1,0,1,1,//到这里是一步的 //1//2

0,1,0,0,1,0,0,//1

0,1,0,1,0,1,0,

0,1,1,0,0,0,1,//1

0,1,1,1,1,1,1,

};
看到我在题号后面标一的吗，对了，这就是特殊情况，你会发现当c小于三时是有一些情况是无法变换来的

（后面标一的是一步达不到的，后面标二的是两步达不到的）

这时候我们特判跳过。


至于输出的时候  我们把符合要求的循环节多次输出直到n就行了。


以下是代码：

//大体思路是找到 其实在只有这几种开关灯的方式时，整个序列的状态只有八种\

而且这八种的状态都是六位一循环的\

所以我们只要看一下最后的这八种状态，看一下是否能够找到适合的方法\

但是要注意当c 《 三时要特判

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int map[8][7] ={
```
0,0,0,0,0,0,0,
0,0,0,1,1,1,0,//1

0,0,1,0,1,0,1,

0,0,1,1,0,1,1,//到这里是一步的 //1

0,1,0,0,1,0,0,//1

0,1,0,1,0,1,0,

0,1,1,0,0,0,1,//1

0,1,1,1,1,1,1,




```cpp
};
int n,c;
int kai[10];int guan[10];
int ktop = 0;int gtop = 0;
bool flag = false;
bool judge(int x)
{
        for(int j = 1;j <= ktop;j ++)
        {
            if(!map[x][kai[j]])
              return false;
        }
        for(int j = 1;j <= gtop;j ++)
        {
            if(map[x][guan[j]])
              return false;
        }
        for(int i = 1;i <= n;i ++)
        {
            printf("%d",map[x][(i - 1) % 6 + 1]);//这里是循环的 
        }
        printf("\n");
        return true;
}
void cz(int x)
{
    for(int i = 0;i <= 7;i ++)
    {
        if(x == 2 && i == 3)continue;
        if(x == 1)
        {
            if(i == 1||i == 3|| i == 4|| i== 6)continue;
        }
        bool t = judge(i);
        if(!flag)flag = t;
    }
    if(!flag)//没有一种情况符合 
      puts("IMPOSSIBLE");
}
int main()
{
    scanf("%d%d",&n,&c);
    while("zbq is handsome")//记录必须开着的地方 
    {
        int zz;
        scanf("%d",&zz);
        if(zz == -1)break;
        kai[++ ktop] =( zz - 1) % 6 + 1;
    }
    while("zbq is handsome")//记录必须关着的地方 
    {
        int zz;
        scanf("%d",&zz);
        if(zz == -1)break;
        guan[++ gtop] =  ( zz - 1) % 6 + 1;
    }
    if(c == 0)//不能变换时也要特判 
    {
        if(gtop)
        {
            puts("IMPOSSIBLE");
        }
        else
            for(int i = 1;i <= n;i ++)
              printf("1");
        return 0;
    }
    cz(c);
    return 0;
} 

```

---

## 作者：key_rA9 (赞：13)

### [USACO2.2]Party Lamps【派对灯】  
这道题因为前3个按钮最多只每两个改变状态，而第4个按钮每三个改状态，所以这些灯每相隔2*3=6个就会重复，所以总共共有以下8种可能：  
###### 1、不按  
###### 2、四个按钮分别按  
###### 3、1+4,2+4,3+4这些组合  
然后可以发现：按两次相当于没按，前三个任意按两个都相当于按另外一个，三个全按相当于不按，说明只要至少C≥3上述所有情况都可以做到，可以通过转换消掉次数，最终就可以到达这些状况。  
C＜3就是特判。  
C=0，就不按  
C=1，就按1,2,3,4  
C=2，除了4其他都可以，因为第4个无法通过两个按钮转换成。  
剩下就是看看符不符合要求状态了。  
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,c,b[7];bool bk;//有没有解
const int a[8][7]=//八种状况
{0,0,0,0,0,0,0,//1
1, 0,0,1,1,1,0,//6=3+4
2, 0,1,0,1,0,1,//2
3, 0,1,1,0,1,1,//4
4, 1,0,0,1,0,0,//5=1+4
5, 1,0,1,0,1,0,//3
6, 1,1,0,0,0,1,//7=2+4
7, 1,1,1,1,1,1};//0
```
```cpp
void pd(int k)  
{
	for(int i=1;i<=6;i++)if(b[i]!=-1&&a[k][i]!=b[i])return;//如果有要求却不合就不成立
	for(int i=1;i<=n;i++)printf("%d",a[k][(i-1)%6+1]);//循环输出
	printf("\n");bk=1;//解记号
}
int main()  
{
	scanf("%d%d",&n,&c);int t;
	memset(b,-1,sizeof(b));//初始化灯都没要求
	while(scanf("%d",&t)!=EOF){if(t==-1)break;b[(t-1)%6+1]=1;}//将第几盏转换成六位中的位置
	while(scanf("%d",&t)!=EOF){if(t==-1)break;b[(t-1)%6+1]=0;}
	if(!c){pd(7);if(bk)return 0;}//有解就结束程序
	else if(c==1)
	{
		pd(0);pd(2);pd(3);pd(5);
		if(bk)return 0;
	}
	else if(c==2)
	{
		pd(0);pd(1);pd(2);pd(4);pd(5);pd(6);pd(7);
		if(bk)return 0;
	}
	else//正常情况
	{
		for(int i=0;i<8;i++){pd(i);}//8种判断
		if(bk)return 0;
	}printf("IMPOSSIBLE\n");//无解
	return 0;
}
```

---

## 作者：ylsoi (赞：10)

首先看到这一道题，表示一脸的懵逼，我想一个一个地深度优先搜索，但是好像不可行的样子，因为好像要消耗4^1000的时间复杂度，后面又想，其实按灯的顺序是没有任何关系的，所以我们只要看这四种方案中每一种我们按了多少次就可以了，但是还是时间复杂度太高，所以后面又想到，一个灯按1次和按3次其实是没有任何区别的，按2次和不按也是没有任何区别的，所以当每一种方案的奇偶性相同的时候，实质上是一样的，所以每一种方案只有按奇数次与偶数次两种选择，同时还需要满足总按灯次数的奇偶性，同事还要满足题目一开始预设的需求，仔细想了一番之后发现，最多最多也就只有2\*2\*2\*2=16中选择，还有大部分无用，所以就变成了一道非常简单的模拟+排序+枚举的题目了，至于排序，我们可以用冒泡，但是一定要注意排序n次，因为只排序一次的话就有可能并没有注意到后面的数位!

附上代码如下，好神奇的。。。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
using namespace std;
const int maxn=100+10;
int n,time,s[maxn],a[20][maxn],cnt,order[maxn];
int main()
{
    int tmp;
    scanf("%d%d",&n,&time);
    for(int i=1;i<=n;i++)
    s[i]=-1;
    while(1)
    {
        scanf("%d",&tmp);
        if(tmp==-1)break;
        s[tmp]=1;
    }
    while(1)//这里是处理预设的要求
    {
        scanf("%d",&tmp);
        if(tmp==-1)break;
        s[tmp]=0;
    }
    for(int i=0;i<=1;i++)
        for(int j=0;j<=1;j++)
            for(int k=0;k<=1;k++)
                for(int l=0;l<=1;l++)//枚举每一种选择
                    {
                        if((i+j+k+l)%2==time%2 && i+j+k+l<=time)//满足预设的要求，同时不可超过次数的限制
                        {
                            cnt++;
                            for(int t=1;t<=n;t++)
                            a[cnt][t]=1;
                            if(i)
                            for(int t=1;t<=n;t++)
                            a[cnt][t]=1-a[cnt][t];
                            if(j)
                            for(int t=1;t<=n;t+=2)
                            a[cnt][t]=1-a[cnt][t];
                            if(k)
                            for(int t=2;t<=n;t+=2)
                            a[cnt][t]=1-a[cnt][t];
                            if(l)
                            for(int t=1;t<=n;t+=3)
                            a[cnt][t]=1-a[cnt][t];
                            for(int t=1;t<=n;t++)
                            if((a[cnt][t]==s[t])||(a[cnt][t]==s[t])||s[t]==-1);//筛去不满足要求的情况
                            else
                            {
                                cnt--;
                                break;
                            }
                        }
                    }
    if(cnt==0)
    {
        printf("IMPOSSIBLE\n");//输出无情况
        return 0;
    }
    for(int ca=1;ca<=n;ca++)//排序很多次，也就是给每一个数位都进行排序
        for(int i=1;i<=cnt-1;i++)
            for(int j=1;j<=cnt-i;j++)
                for(int k=1;k<=n;k++)//依次选择每一个数位
                    if(a[j][k]==a[j+1][k])
                    continue;
                    else if(a[j][k]<a[j+1][k])break;
                    else
                    {
                        swap(a[j],a[j+1]);
                        break;
                    }
    for(int i=1;i<=cnt;i++,cout<<endl)
        for(int j=1;j<=n;j++)
            printf("%d",a[i][j]);
    return 0;
}
```

---

## 作者：OdtreePrince (赞：6)

# 派对灯 Party Lamps
　　※ 算法：暴力＆模拟
  
　　※ 我们可以使用大量的时间来~~找规律~~推导此题的分类方式，发现大致可以分为这五种：
  
　　　　※ 1. $c=0$ 
    
　　　　此时全部都应该是亮着的，输出一堆 $1$ 即可.如果输入告诉你有关着的灯，反手一个"IMPOSSIBLE"甩出题人脸上.
    
　　　　※ 2. $c=1$ 
    
　　　　按题意模拟四种操作，定义一个 $bool$ 型变量判断是否成立即可.
    
　　　　※ 3. $c=2$ 
    
　　　　继续按题意模拟四种操作(的**组合**)，定义一个 $bool$ 型变量判断是否成立即可.
    
　　　　※ 4. $c∈ A\{x|x=2k+1,x∈N_+,k∈N_+\}$ 
    
　　　　还是题意模拟四种操作(的**组合**)，定义一个 $bool$ 型变量判断是否成立即可.
    
　　　　※ 5. $c∈ A\{x|x=2k,x∈N_+,k∈N_+\}$ 
    
　　　　接着按题意模拟四种操作(的**组合**)，定义一个 $bool$ 型变量判断是否成立即可.
    
　　※ $Tip:$ 　 1. $Pay$ $attention$ $to$ $DEBUG$ $your$ $code$ $to$ $make$ $your$ $"Outputs"$ $in$ $the$ $right$ $ORDER!$
  
　　　　 　 　  　2. $You$ $can$ $use$ $DFS$ $to$ $make$ $your$ $code$ $shorter$ $as$ $well$.
           
　　　　 　 　  　3. 神仙代码警告!!!!!!
           
　　
  
  

------------


　

　　code:
  
  ```cpp
//此代码已压行
#include<bits/stdc++.h>
using namespace std;
bool flag,pd;
int n,c,o,a[105],k[105];     //a=当前状态，k=条件 
int main(){
	memset(k,4,sizeof(k));
	scanf("%d%d",&n,&c);
	scanf("%d",&o);
	while(o!=-1) k[o]=1,scanf("%d",&o);
	scanf("%d",&o);
	while(o!=-1) k[o]=0,scanf("%d",&o);
	for(register int i=1;i<=n;i++) a[i]=1;
	if(!c){
		for(register int i=1;i<=n;i++) if(a[i]!=k[i]&&k[i]<3) puts("IMPOSSIBLE"),exit(0);
		for(register int i=1;i<=n;i++) printf("%d",a[i]);return 0;
	} 
	if(c==1){
		flag=1;
		for(register int i=1;i<=n;i++){
			a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++){
			if(i%2==1)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++){
			if(i%3==1)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++){
			if(i%2==0)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		if(!pd) puts("IMPOSSIBLE");return 0;
	}
	if(c==2){
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++) if(i%2==0)a[i]^=1;
		for(register int i=1;i<=n;i++){
			if(i%2==1)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++) if(i%2==0)a[i]^=1;
		for(register int i=1;i<=n;i++){
			if(i%3==1)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++) a[i]^=1;
		for(register int i=1;i<=n;i++){
			if(i%2==0)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++) a[i]^=1;
		for(register int i=1;i<=n;i++){
			if(i%3==1)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++) a[i]^=1;
		for(register int i=1;i<=n;i++){
			if(i%2==1)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++) if(i%2==1)a[i]^=1;
		for(register int i=1;i<=n;i++){
			if(i%3==1)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++) if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		if(!pd) puts("IMPOSSIBLE");return 0;
	}
	if(c&1){
		flag=1;
		for(register int i=1;i<=n;i++){
			a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++) a[i]^=1;
		for(register int i=1;i<=n;i++) if(i%2==1)a[i]^=1;
		for(register int i=1;i<=n;i++){
			if(i%3==1)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++){
			if(i%2==1)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++){
			if(i%3==1)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++) if(i%2==0)a[i]^=1;
		for(register int i=1;i<=n;i++) if(i%2==1)a[i]^=1;
		for(register int i=1;i<=n;i++){
			if(i%3==1)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++){
			if(i%2==0)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++) a[i]^=1;
		for(register int i=1;i<=n;i++) if(i%2==0)a[i]^=1;
		for(register int i=1;i<=n;i++){
			if(i%3==1)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++) if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		if(!pd) puts("IMPOSSIBLE");return 0;
	}
	else{
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++) if(i%2==0)a[i]^=1;
		for(register int i=1;i<=n;i++){
			if(i%2==1)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++) if(i%2==0)a[i]^=1;
		for(register int i=1;i<=n;i++){
			if(i%3==1)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++) a[i]^=1;
		for(register int i=1;i<=n;i++){
			if(i%2==0)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++){
			if(i%3==1)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++) a[i]^=1;
		for(register int i=1;i<=n;i++){
			if(i%3==1)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++) a[i]^=1;
		for(register int i=1;i<=n;i++){
			if(i%2==1)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++) if(i%2==1)a[i]^=1;
		for(register int i=1;i<=n;i++){
			if(i%3==1)a[i]^=1;
			if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		flag=1;
		for(register int i=1;i<=n;i++) a[i]=1;
		for(register int i=1;i<=n;i++) if(a[i]!=k[i]&&k[i]<3){flag=0;break;}
		if(flag){for(register int i=1;i<=n;i++) printf("%d",a[i]);puts("");pd=true;}
		if(!pd) puts("IMPOSSIBLE");return 0;
	}
	return 0;
}
```

---

## 作者：issue_is_fw (赞：5)

考点其实比较老套了

因为任意一个按键按偶数次就等于没按

所以4个$for$枚举每个开关按还是不按

判断一下枚举的按的次数是否和c的奇偶性相同

相同的话就简单了,因为起始都开灯,模拟就是了

然后和题目给的状态对比,可行就存下来

**当然我写的是比较好看的(除了没有加空格)**

```
#include <bits/stdc++.h>
using namespace std;
const int maxn=109;
int n,c;
int a[maxn],b[maxn],top;
string f[maxn];
void run()
{
	string temp="";
	for(int i=1;i<=n;i++)	temp+=char(b[i]+'0');
	f[++top]=temp;
}
int main()
{
	cin >> n >> c;
	int ok;
	memset(a,-1,sizeof(a));
	while( cin >> ok && ok!=-1 )	a[ok]=1;//亮着 
	while( cin >> ok && ok!=-1 )	a[ok]=0;//熄灭 
	for(int i=0;i<=1;i++)
	{
		for(int j=0;j<=1;j++)
		for(int q=0;q<=1;q++)
		for(int w=0;w<=1;w++)
		{
			if(i+j+q+w>c)	continue;//次数太多
			if( (i+j)%2==(q+w)%2&&c%2==1 )//那么i+j+q是偶数
				continue;
			if( (i+j)%2!=(q+w)%2&&c%2==0 )//那么i+j+q是奇数	
				continue;
			for(int i=1;i<=n;i++)	b[i]=1;//初始都是开灯 
			if(i)	for(int i=1;i<=n;i++)	b[i]^=1;
			if(j)	for(int i=1;i<=n;i+=2)	b[i]^=1;
			if(q)	for(int i=2;i<=n;i+=2)	b[i]^=1;
			if(w)	for(int i=1;i<=n;i+=3)	b[i]^=1;
			int flag=1;
			for(int s=1;s<=n;s++)
			{
				if( a[s]==-1 )	continue;
				if( a[s]!=b[s] )	flag=0;
			}
			if(flag)	run();
		}
	}
	sort(f+1,f+1+top);
	if( top==0 )	cout<<"IMPOSSIBLE";
	else
		for(int i=1;i<=top;i++)	cout<<f[i]<<endl;
}

```

---

## 作者：「QQ红包」 (赞：4)

/\*
ID: ylx14274

PROG: lamps

LANG: C++

\*/

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
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>   
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
int n,c,i,j;//c：计数器君，n：灯的盏数
int l[101];//最后灯的状态,-1为不作要求，1为亮，0为灭 
int f;//标记有没有解，无解为0 
int b[9][7]=//华丽的表 
{0,0,0,0,0,0,0,  
    0,0,0,0,0,0,0,//按1  
    0,0,0,1,1,1,0,//按1按4  
    0,0,1,0,1,0,1,//按3  
    0,0,1,1,0,1,1,//按1按4  
    0,1,0,0,1,0,0,//按4  
    0,1,0,1,0,1,0,//按2  
    0,1,1,0,0,0,1,//按2按4  
    0,1,1,1,1,1,1,};//不按  注意顺序！ 
//int s[9]={0,1,1,1,1,2,2,2,0};//达到对应的某种状态最少需要按的次数 
int main() 
{
    scanf("%d%d",&n,&c);
    i=0;
    int x;
    for (i=1;i<=6;i++) l[i]=-1;
    scanf("%d",&x);//读入
    while (x!=-1)
    {
        if ((x%6)==0) l[6]=1;//标记
        else l[x%6]=1;//标记 ，全部映射到1~6中 
        scanf("%d",&x);//读入 
    }
    scanf("%d",&x);//读入
    while (x!=-1) 
    {
        if ((x%6)==0) l[6]=0;//标记
        else l[x%6]=0;//标记 ，全部映射到1~6中 
        scanf("%d",&x);//读入 
    }
    //-------------------读入完毕-------------------//
    if (c>=4) c=3;//反正3以上所有方法都可行 
    switch (c)
    {
        case 0://什么都不按 ,别忽略，有2个点 
        {
            for (i=8;i<=8;i++)//只有不按 
                {    
                    int ah=1;//标记用 
                    for (j=1;j<=6;j++)
                    {
                        if (l[j]!=-1)//对这一位有做要求 
                            if (b[i][j]!=l[j])
                            {
                                ah=0;//标记
                                break; 
                            }
                    }
                    if (ah==1)//这种情况符合条件 
                    {
                        f=1;//标记 
                        for (j=1;j<=n;j++)
                            printf("%d",b[i][(j-1)%6+1]);
                        printf("\n");
                    }
                }
                break;
        }
        case 1:
            {
                for (i=1;i<=8;i++)//前四种都可以有 
                {    
                    if (i!=1||i!=3||i!=5||i!=6) continue; 
                    int ah=1;//标记用 
                    for (j=1;j<=6;j++)
                    {
                        if (l[j]!=-1)//对这一位有做要求 
                            if (b[i][j]!=l[j])
                            {
                                ah=0;//标记
                                break; 
                            }
                    }
                    if (ah==1)//这种情况符合条件 
                    {
                        f=1;//标记 
                        for (j=1;j<=n;j++)
                            printf("%d",b[i][(j-1)%6+1]);
                        printf("\n");
                    }
                }
                break;
            }
        case 2:
            {
                for (i=1;i<=8;i++)//除开4都可以 
                {    
                    if (i==5) continue; 
                    int ah=1;//标记用 
                    for (j=1;j<=6;j++)
                    {
                        if (l[j]!=-1)//对这一位有做要求 
                            if (b[i][j]!=l[j])
                            {
                                ah=0;//标记
                                break; 
                            }
                    }
                    if (ah==1)//这种情况符合条件 
                    {
                        f=1;//标记 
                        for (j=1;j<=n;j++)
                            printf("%d",b[i][(j-1)%6+1]);
                        printf("\n");
                    }
                }
                break;
            }
        case 3:
            {
                for (i=1;i<=8;i++)//都可以 
                {    
                    int ah=1;//标记用 
                    for (j=1;j<=6;j++)
                    {
                        if (l[j]!=-1)//对这一位有做要求 
                            if (b[i][j]!=l[j])
                            {
                                ah=0;//标记
                                break; 
                            }
                    }
                    if (ah==1)//这种情况符合条件 
                    {
                        f=1;//标记 
                        for (j=1;j<=n;j++)
                            printf("%d",b[i][(j-1)%6+1]);
                        printf("\n");
                    }
                }
                break;
            }
    } 
    if (f==0) printf("IMPOSSIBLE\n");//无解 
    return 0; 
}
```
以下分析来自NOCOW.//我觉得这个分析比我自己描述得好多了

分析

每个按钮按2次和没按效果是一样的。所以每个按钮或者按或者不按，一共有2^4=16种状态。枚举每个按钮是否按下，然后生成结果，排序输出即可（注意判重）。


另外灯1和灯7,2和8,3和9…是一样的因此当N>=6时只需处理前6个,排序时转换为10进制数, 输出时反复输出前6个的状态.


深究：


我们现在记不按按钮，以及按下1，2，3，4按钮分别O，①，②，③，④， 那么，按下3，4，可以记为③④，以此类推， 我们发现一个问题，那就是①，②，③之间微妙的关系， ①②=③，而②③=①，①③=②（可以自己试试），于是我们知道，①②③也相当与不按，即相差3的倍数也可互相转换；

所以，所谓前四个的16种按法其实只有8种， 分别为：O,①，②，③，④，①④，②④，③④；

然后讨论c， 由于当c>4时，均可化为当c<=4的情况， 所以我们先讨论当c<=4的情况，


当c=0时，只有一种O；


当c=1时，四种：①，②，③，④；


当c=2时，除了④均可（可以自己想想）；


当c=3时，由于3-1=2，所以c=1的情况都满足，而在c=2中，把所有有前三类的展开，如①④变为②③④， 可知满足c=2的同时满足c=3，所以c=3其实是c=2和c=1的并集，即所有按法均可。


当c=4时，由于4-1=3（①②③相当于不按），且4-2=2，由上，c=4也是所有按法均可。

当c>4时，我先有一个引理：对于任意的正整数n>1，均可写成n=2\*p+3\*q(p,q为非负整数）的形式， 证明如下：若n为偶数，必然成立，若n为奇数，必然大于2，则n-3必为非负偶数，得证。 由这个引理我们可以知道，任意c>4均可写成，c=2\*p+3\*q+3(p,q为非负整数）的形式，而可知， 对于两个相同的按键，以及情况①②③（按键三次），均相当于不按，所以任意c>4均可化归为c=3的情况， 即当c>4时，所有按法均可。


综上所述，


当c=0时，只有一种O；


当c=1时，四种：①，②，③，④；


当c=2时，除了④均可；


当c>2时，所有按法均可。


好了，这样一来就非常简单了， 只有四种情况，8种按法。


于是我们就可以打个表了。打表也要注意下顺序。


---

## 作者：resftlmuttmotw (赞：1)

这道题很简单

但我看了题解 大多是打表

大分类讨论

反正一大堆代码

~~没那么麻烦啊~~

一点:

我们只需要枚举操作$1-4$的奇偶

```cpp
for(reg i = 0;i <= 1;i++)
	{
		for(reg j = 0;j <= 1;j++)
		{
			for(reg k = 0;k <= 1;k++)
			{
				int res = c - i - j - k;
				if(res < 0) continue;
				res %= 2;
				count_(i,j,k,res);
			}
		}
	}
```

可以保证正确性

即我们可以证明若有

$a+b+c+d=E$

已知 $a,b,c$的奇偶

那么可以确定$d$的奇偶

证明很简单 这里就略了

枚举一种状态后

再检查可行性

```cpp
for(reg q = 0;q < light.size();q++)
		if(check(i,j,k,l,light[q])) return; 
for(reg q = 0;q < dark.size();q++)
		if(!check(i,j,k,l,dark[q])) return;
```

$check$为当前位置按的次数

注意要排序输出

因为我懒 所以用优先队列了

如果去掉读优和一些不必要的东西后 应该是最短的了
```cpp
/*
ID:death_r2
TASK:lamps
LANG:C++
*/
#include <queue>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
#define reg register int
#define isdigit(x) ('0' <= x&&x <= '9')
template<typename T>
inline T Read(T Type)
{
	T x = 0,f = 1;
	char a = getchar();
	while(!isdigit(a)) {if(a == '-') f = -1;a = getchar();}
	while(isdigit(a)) {x = (x << 1) + (x << 3) + (a ^ '0');a = getchar();}
	return x * f;
}
vector<int> light,dark;
int n,c;
priority_queue<string,vector<string>,greater<string> > ans;
inline bool check(int i,int j,int k,int l,int num)
{
	int g = num & 1;
	if((i + (j & g) + (k & (!g)) + ((num % 3 == 1) & l)) & 1) return 1;
	return 0;
}
inline void count_(int i,int j,int k,int l)
{
	for(reg q = 0;q < light.size();q++)
		if(check(i,j,k,l,light[q])) return; 
	for(reg q = 0;q < dark.size();q++)
		if(!check(i,j,k,l,dark[q])) return;
	string a;
	for(reg v = 1;v <= n;v++)
	{
		if(check(i,j,k,l,v)) a = a + '0';
		else a = a + '1'; 
	}
	ans.push(a);
}
int main()
{
    freopen("lamps.in","r",stdin);
    freopen("lamps.out","w",stdout);
    n = Read(1),c = Read(1);int x = Read(1);
    while(x != -1)
    {
    	light.push_back(x);
    	x = Read(1);
	}
	x = Read(1);
	while(x != -1)
    {
    	dark.push_back(x);
    	x = Read(1);
	}
	for(reg i = 0;i <= 1;i++)
	{
		for(reg j = 0;j <= 1;j++)
		{
			for(reg k = 0;k <= 1;k++)
			{
				int res = c - i - j - k;
				if(res < 0) continue;
				res %= 2;
				count_(i,j,k,res);
			}
		}
	}
	if(ans.empty())
	{
		printf("IMPOSSIBLE\n");
	} else {
		while(!ans.empty())
		{
			cout << ans.top() << endl;
			ans.pop();
		}
	}
	return 0;
}
```

---

## 作者：天泽龟 (赞：1)

### 其他题解已经把思路说明得十分详细了，这篇题解就 着重说明一下 对数据巧~~(tou)~~妙~~(lan)~~的处理技巧。

---

- **思路：**看到这个数据范围发现暴力显然是不可以的，于是可以往**记忆化或者简化模拟**的方面去想。

然后经~~(you)~~思~~(ti)~~考~~(jie)~~可得如下性质：
1. 以6为循环节，超过直接取模修改
2. 对于$C=3$，即可取完所有情况，且超过可以通过各种方法转换至$C=3$（譬如连按两下任意按钮，或者通过按$1,2,3$浪费次数）。

 

### 于是可以往只判断前6个字符和压缩开关次数$<=3$次，使其在常数范围内即可得解。

---
- ### 那么如何处理本题数据呢？

## 我们可以通过打表将已知数据全部表示出来，使用时直接调用即可。
~~(我凭本事打的表怎么能说偷懒！）~~

首先理一下我们已经可以知道哪些东西：

1. 草稿纸上画出的$C=1,C=2,C=3$的所有可能出现的情况$map[i][j]$（重复的或可替代的不算）
2. 根据输入数据得出的1~6循环节内各位置的开关灯情况$a[i]$。
3. $c-map[i]$图式表$go[c][i]$，表示当前的C在map上有哪些情况可取到。

其中1,3我们均可以直接打表出来：
```
int a[10],map[8][8]={}  //已按照字典序(1表示开灯，2表示关灯）
	
{0,2,2,2,2,2,2},
//c=1,2,3
{0,2,2,1,1,1,2},
//c=2,3
{0,2,1,2,1,2,1},
//c=1,2,3 
{0,2,1,1,2,1,1},
//c=1,3
{0,1,2,2,1,2,2},
//..2,3 
{0,1,2,1,2,1,2},
//..1,2,3
{0,1,1,2,2,2,1},
//..2,3 
{0,1,1,1,1,1,1}
//..2,3

};
bool f,f2,go[4][10]={ //i表示当前的c,j表示与上表对应的开关灯情况
{0,0,0,0,0,0,0,0},
{1,0,1,1,0,1,0,0},
{1,1,1,0,1,1,1,1},
{1,1,1,1,1,1,1,1}
};

```

别看这么长，全是草稿纸扫一眼的问题，手速快的人1分钟就可以敲完。

其次2号表我们读入中即可处理，至此题目已经做完一半，而我们才刚刚读入处理完。_(:з」∠)

---

- 主程序

得出3张表后，我们对8种情况一一判断，枚举表中数据和输入数据是否相符，并在go数组内判断当前c是否包含此情况。

于是主程序一共两个函数，不到十行：
```
bool equal(int x) //若输入数据存在当前位置信息就判断与map是否相符
{
	for (int i=1;i<=6;i++) 
		if (map[x][i]!=a[i]&&a[i]) return 0;
	return 1;
}
void check(int c)
{
	for (int i=0;i<=7;i++)
		if (equal(i)&&go[c][i]) print(i); //打印
}
```

---
- 细节


1. 一开始忘记考虑$c=0$的情况，又懒得修改三张表了，于是直接最后特判了一下。。
2. $IMPOSSIBLE$的情况就两种：在八种情况没找到满足的，或者输入的时候膜6时矛盾了，判断一下即可。
3. 打完之后发现也有八十多行，但是大部分都是特判和打表，实际长度是真的少。

---
于是上我丑陋的代码：
```
#include <iostream>
using namespace std;

int n,c;
int a[10],map[8][8]={  //按照字典序 	
{0,2,2,2,2,2,2},
//1,2,3
{0,2,2,1,1,1,2},
//2,3
{0,2,1,2,1,2,1},
//1,2,3 
{0,2,1,1,2,1,1},
//1,3
{0,1,2,2,1,2,2},
//2,3 
{0,1,2,1,2,1,2},
//1,2,3
{0,1,1,2,2,2,1},
//2,3 
{0,1,1,1,1,1,1}
//2,3
};
bool f,f2,go[4][10]={
{0,0,0,0,0,0,0,0},
{1,0,1,1,0,1,0,0},
{1,1,1,0,1,1,1,1},
{1,1,1,1,1,1,1,1}
};
//打表
void print(int i)
{
	f2=1;
	for (int j=1;j<=n;j++) 
	cout<<(map[i][(j%6!=0)?j%6:6]!=2)?1:0;
	cout<<endl;
}

bool equal(int x)
{
	for (int i=1;i<=6;i++) 
		if (map[x][i]!=a[i]&&a[i]) return 0;
	return 1;
}
void check(int c)
{
	for (int i=0;i<=7;i++)
		if (equal(i)&&go[c][i]) print(i);
}

int main()
{
	cin>>n>>c; if (c>3) c=3;
	for (int i=1,p=0;i<=n;) {
		cin>>p; 
		
		if (p!=-1) {
			if (!c) f=1; //特判 
			int kp=(p%6!=0)?p%6:6; a[kp]=1;
		} else break;
	}	
	for (int i=1,p=0;i<=n;f) {
		cin>>p; 
		if (p!=-1) {
			if (!c) f=1; //特判 
			int kp=(p%6!=0)?p%6:6;
			if (!a[kp]) a[kp]=2; else f=1;
		} else break;
	}
    //读入处理
    
	if (f){
		cout<<"IMPOSSIBLE"<<endl; return 0;
	}
	check(c);
	if (!c) {  //特判 
		for (int i=1;i<=n;i++) cout<<1; return 0;
	}
	if (!f2) cout<<"IMPOSSIBLE"<<endl;
	return 0;
}
```

---

## 作者：何卓然 (赞：1)

仔细阅读题目，可以得出以下定理：


任何按钮按两次，则没有任何效果产生。

即为：一个按钮按下奇数次，发生作用，按下偶数次，无效。


由于这个结论，我们可以发现，4个按钮，可能的变化情况也只有15种。

我们可以用二进制枚举的方法，来逐一确定这个状态是否合法，最后排序输出。


自认为我的代码比其他几位美观很多，也比较好理解














```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,cnt; //灯数，操作次数
int lightUp[105],light_cnt = 0; // 要求亮的灯，亮的灯的计数器
int lightOff[105],off_cnt = 0; // 要求灭的灯，灭的灯的计数器
bool cur[105]; // 当前枚举的按钮操作情况下的灯的状态
struct Node
{
    char s[105]; // 结构体方便排序
    Node(){}
    bool operator < (const Node &temp) const // 重载小于号运算符，排序
    {
        for (int i=1;i<=n;i++)
        {
            if (s[i] > temp.s[i]) return false;
            if (s[i] < temp.s[i]) return true;
        }
    }
}N[5000];
int state_cnt = 0;
void init()
{
    cin >> n >> cnt;
    for (;;)
    {
        int light;
        cin >> light;
        if (light == -1) break; // 读入要求亮的灯
        lightUp[light_cnt] = light;
        light_cnt++;
    }
    for (;;)
    {
        int off;
        cin >> off;
        if (off == -1) break; // 读入要求灭的灯
        lightOff[off_cnt] = off;
        off_cnt++;
    }
}
int main()
{
    init();
    for (int i=0;i<16;i++) // 二进制枚举按钮操作
    {
        memset(cur,1,sizeof(cur)); // 状态恢复为全亮
        int turn = 0;
        if (i & (1 << 0)) { turn++; for (int j=1;j<=n;j++) cur[j] = 1 - cur[j]; } // 第一个按钮，全变
        if (i & (1 << 1)) { turn++; for (int j=1;j<=n;j++) if (j % 2 == 1) cur[j] = 1 - cur[j]; } // 奇数
        if (i & (1 << 2)) { turn++; for (int j=1;j<=n;j++) if (j % 2 == 0) cur[j] = 1 - cur[j]; } // 偶数
        if (i & (1 << 3)) { turn++; for (int j=1;j<=n;j++) if (j % 3 == 1) cur[j] = 1 - cur[j]; } // 3k + 1
        bool eq = true;
        for (int j=0;j<light_cnt;j++)
            if (cur[lightUp[j]] != 1)
                { eq = false; break; } // 要求亮的没亮
        for (int j=0;j<off_cnt;j++)
            if (cur[lightOff[j]] != 0)
                { eq = false; break; } // 要求灭的没灭
        if ((cnt - turn) % 2 != 0 || turn > cnt) continue; // 操作次数比实际作用的多出非偶数次 或者没法操作这么多次 都是非法
        if (eq == false) continue;
        for (int j=1;j<=n;j++)
            N[state_cnt].s[j] = cur[j] + 48; // '0' = 48
        state_cnt++;
    }
    if (state_cnt == 0)
    {
        cout << "IMPOSSIBLE";
        return 0;
    }
    sort(N,N+state_cnt); // 状态排序
    for (int i=0;i<state_cnt;i++)
    {
        for (int j=1;j<=n;j++)
            cout << N[i].s[j];
        cout << endl;
    }
    return 0;
}

```

---

## 作者：GoAway (赞：1)

使用\_\_int128还有一波位运算水过2333

还有一些优化：

每个操作如果操作两边等于没操作。

所以枚举每个操作0或1就行。

注意判0.

```cpp
#include <bits/stdc++.h>
using namespace std ;
#define LL __int128
int n, m ;
void print ( LL x ) {
    LL tmp = 1LL<<n-1 ; 
    for ( int i = 1 ; i <= n ; i ++, x>>=1 ) putchar( (x&1)+'0') ; putchar('\n') ;
}
LL s[202020] ;
vector <int> Light, Dark ;
bool pd ( LL x, int u ) { return (x>>u-1)&1 ; }
bool Judge ( LL x ) {
    int i, u ;
    LL tmp ;
    for ( i = 0 ; i < Light.size() ; i ++ )
        if ( !pd(x,Light[i]) ) return false ;
    for ( i = 0 ; i < Dark.size() ; i ++ )
        if ( pd(x,Dark[i]) ) return false ;
    return true ;
}
bool cmp ( LL a, LL b ) { return a>b ; } ;
LL change ( LL x ) {
    LL wea = 0 ;
    for ( int i = n ; i ; i --, x >>= 1 ) wea ^= (LL)(x&1) << i-1 ;
    return wea ;
}
int main() {
    int i, j, k, o1, o2, o3, o4, c ;
    LL _1, _2, _3, _4, tmp ;
    _1 = _2 = _3 = _4 = 0 ; tmp = (LL)1 ;
    scanf ( "%d", &n ) ;
    for ( i = 1 ; i <= n ; i ++, tmp<<=(LL)1 ) {
        if (i&1) _2^=tmp ;
        else _3^=tmp ;
        if ( i%3==1 ) _4^=tmp ;
        _1 += tmp ;
    }
    tmp = _1 ;
    scanf ( "%d", &c ) ;
    while ( scanf ( "%d", &k ) ) {
        if ( k == -1 ) break ;
        Light.push_back(k) ;
    }
    while ( scanf ( "%d", &k ) ) {
        if ( k == -1 ) break ;
        Dark.push_back(k) ;
    }
    if ( !c ) {
        if ( Judge(_1) ) print(_1), putchar('\n') ;
        else puts("IMPOSSIBLE") ;
        return 0 ;
    }
    m = 0 ;
    for ( o1 = 0 ; o1 < 2 ; o1 ++ )
        for ( o2 = 0 ; o2 < 2 ; o2 ++ )
            for ( o3 = 0 ; o3 < 2 ; o3 ++ )
                for ( o4 = 0 ; o4 < 2 ; o4 ++ ) {
                    if ( (o1^o2^o3^o4)==(c&1) && (o1+o2+o3+o4)<=c ) {
                        tmp = _1 ;
                        if ( o1 ) tmp ^= _1 ;
                        if ( o2 ) tmp ^= _2 ;
                        if ( o3 ) tmp ^= _3 ;
                        if ( o4 ) tmp ^= _4 ;
                        if ( Judge(tmp) ) s[++m] = tmp ;
                    }
                }
    if ( !m ) {    puts("IMPOSSIBLE") ; return 0 ;    }
    for ( i = 1 ; i <= m ; i ++ )
        s[i] = change(s[i]) ;
    sort(s+1,s+m+1) ;
    for ( i = 1 ; i <= m ; i ++ )
        print(change(s[i])) ;
    return 0 ;
}
```

---

## 作者：D_Fox (赞：0)

# 郑重说明：这是我老师的思路，但代码为本人“原创”，不代表这篇题解是我本人独立思考的结果（谁让他不上洛谷）
各位大牛要不就是打表，要不就是写那些我看不懂的排序算法，为什么不用STL的set处理一下呢？既可以去重，又可以自动排序，代码又简洁明了。
### 对于一个灯来说：按奇数次等于关，按偶数次等于没按。（这个好像很多人都发现了）
上代码：
```
#include <bits/stdc++.h>

using namespace std;

const int N = 102;
const int C = 10002;

int n, c, open[N], fire[N], unfire[N], pf, pu;
set<string> s;
/*
open表示当前情况灯的状态；	fire表示必须亮的灯，pf是它的指针； unfire表示必须灭的灯，pu是它的指针；
s即为最终答案，题目要求刚好满足字典序；
*/
int main() {
	cin >> n >> c;
	int temp;
	while(cin >> temp && temp != -1) fire[pf++] = temp;
	while(cin >> temp && temp != -1) unfire[pu++] = temp;
	for(int i = 0; i <= 1; i++) {//1表示按奇数次，0表示按偶数次；
		for(int j = 0; j <= 1; j++) {
			for(int k = 0; k <= 1; k++) {
				for(int l = 0; l <= 1; l++) {
					if((i + j + k + l) % 2 != c % 2 || i + j + k + l > c) continue;//如果奇偶性不同，则一定按不出c；还有大于c的情况（这个我是很没想到），同样不符合条件；
					for(int a = 0; a < N; a++)
						open[a] = 1;//别忘了初始化；
					if(i) 
						for(int a = 1; a <= n; a++) 
							open[a] = !open[a];
					
					if(j) 
						for(int a = 1; a <= n; a += 2) 
							open[a] = !open[a];
					
					if(k) 
						for(int a = 2; a <= n; a += 2)
							open[a] = !open[a];
					
					if(l) 
						for(int a = 1; a <= n; a += 3) 
							open[a] = !open[a];
						
					//接下来的两个for循环是判断是否符合条件（为什么我写这么长，老师三行搞定？）；
					bool pan = 1;
					for(int a = 0; a < pf; a++) 
						if(open[fire[a]] != 1) 
							pan = 0;
							break;
						
					
					if(pan) 
						for(int a = 0; a < pu; a++) 
							if(open[unfire[a]] != 0) {
								pan = 0;
								break;
							}
						
					
					if(pan) {
						string temp;
						for(int a = 1; a <= n; a++) 
							temp += open[a] + '0';
						
						s.insert(temp);//直接塞进集合，不用任何处理；
					}
				}
			}
		}
	}
	if(s.empty()) cout << "IMPOSSIBLE" << endl;//集合为空，即没有符合条件的情况；
	else //输出set中的元素；
		for(set<string>::iterator it = s.begin(); it != s.end(); it++) 
			cout << *it << endl;
		
	
	return 0;
}

```
## I Love STL !!!

---

## 作者：Celebrate (赞：0)

这一题有100盏灯，感觉很麻烦，所以我们得把它缩小

按钮1需要1个位置

按钮2需要两个位置

按钮3也需要两个位置

按钮4需要3个位置

最小共倍数是6，所以我们用6为一个周期

然后找规律，发现c>3和c=3是一样的，c=1和c=2分别是按两次和按3次按钮

由于c的原因，我就没有用8种变化了

代码如下：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int b[5][7]={
	0,0,0,0,0,0,0,//没有用的 
	0,0,1,0,1,0,1,//21
	0,1,0,0,1,0,0,//36
	0,1,0,1,0,1,0,//42
	0,1,1,1,1,1,1,//63
};
int n,m;
int a[110],len=0,f[11][7],k[7];
int map[11][7],ans=0;
bool v[2][2][2][2][2][2];
void dfs(int d)//四个按钮中选d个按
{
	if(d==m+1) //如果选完了 
	{
		if(v[k[1]][k[2]][k[3]][k[4]][k[5]][k[6]]==true)//如果以前没有过 
		{
			v[k[1]][k[2]][k[3]][k[4]][k[5]][k[6]]=false;//把它变为有 
			len++;for(int i=1;i<=6;i++) f[len][i]=k[i];//记录这个值 
		}
	}
	else
	{
		for(int i=d;i<=4;i++)//从第d个按钮开始按 
		{
			for(int j=1;j<=6;j++) //6个位置 
			{
				k[j]+=b[i][j];if(k[j]==2) k[j]=0;//改变灯的状态 
			}
			dfs(d+1);//往下搜索 
			for(int j=1;j<=6;j++)//回溯 
			{
				k[j]-=b[i][j];if(k[j]==-1) k[j]=1;
			}
		}
	}
}
int main()
{
	for(int i=1;i<=6;i++) k[i]=1;//dfs前初始化，一开始全部都是亮着的 
	int i,j,k,t;
	scanf("%d%d",&n,&m);
	//数组a有3种状态，-1表示可以关也可以开，0表示必须关，1表示必须开 
	for(i=1;i<=n;i++)a[i]=-1;
	while(scanf("%d",&t)!=EOF)//输入 
	{
		if(t==-1) break;
		a[t]=1;//记录 
	}
	while(scanf("%d",&t)!=EOF)
	{
		if(t==-1) break;
		a[t]=0;
	}
	if(m>3) m=3;//凡是大于3的，就把它变成3 
	len=1;for(i=1;i<=6;i++) f[1][i]=1;//第一种方案肯定是全部都开，以后dfs也省事很多 
	memset(v,true,sizeof(v));v[1][1][1][1][1][1]=false;//v记录这种情况是否出现过 
	dfs(1);//递归 
	for(i=1;i<=len;i++)//f的长度为len，寻找符合要求的f 
	{
		k=0;bool bk=true;
		for(j=1;j<=n;j++)
		{
			k++;if(k==6+1) k=1;
			if(a[j]==-1) continue;
			if(f[i][k]!=a[j])//如果不符合要求，就不用管了 
			{
				bk=false;break;
			}
		}
		if(bk==true)//如果符合要求 
		{
			ans++;
			for(j=1;j<=6;j++) map[ans][j]=f[i][j];//map记录符合要求的f 
		}
	}
	for(i=1;i<ans;i++)//把map给排序 
	{
		for(j=i+1;j<=ans;j++)
		{
			bool bk=true;
			for(k=1;k<=6;k++)
			{
				if(map[j][k]<map[i][k])//如果前面的大于后面的 
				{
					bk=false;break;
				}
				if(map[j][k]>map[i][k]) break;//如果前面的小于后面的，就要交换 
			}
			if(bk==false)//如果前面的大于后面的
			{
				for(k=1;k<=6;k++)//交换 
				{
					int t=map[j][k];map[j][k]=map[i][k];map[i][k]=t;
				}
			}
		}
	}
	for(i=1;i<=ans;i++)//输出map 
	{
		for(j=1;j<=n;j++)
		{
			t=j%6;if(t==0) t=6;
			printf("%d",map[i][t]);
		}
		printf("\n");
	}
	if(ans==0) printf("IMPOSSIBLE\n");//如果没有满足条件的 
	return 0;
}
```

---

## 作者：罗旅洲 (赞：0)


```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
using namespace std;
int l[101],d[101],q[110],f,h,n,c,llz=0;    //llz表示罗旅洲是否得到答案,l表示亮的要求，d表示dark的要求 
int u[10]={0,3,0,0,1,0,2,0};            //一个按钮按两下就毫无意义了，所以只有2*2*2*2种方案 
int v[10]={1,4,2,4,4,3,4,0};            //在这十六种中有些还重复：such as按钮2与3按了==按钮1 
                                        //所以算来算去只有8种，但注意顺序保证输出从小到大， 
void aaa(int x){                        
    if(x==0)return ;
    else if(x==1){
    for(int i=1;i<=n;i++)                //暴力写每个按钮，^是异或 
    q[i]^=1;}
    else if(x==3){
    for(int i=2;i<=n;i+=2)
    q[i]^=1;}
    else if(x==2){
    for(int i=1;i<=n;i+=2)
    q[i]^=1;}
    else if(x==4){
    for(int i=1;i<=n;i+=3)
    q[i]^=1;}
}
void dfs(int x){            //x是按钮的次数，其实这是毫无意义的主要针对x为1 
    int za=0,cn=7;            //za是周昂，cn是陈诺 ，这两个人唯一的意义就是来做变量名 
    if(x==1){                            
    cn=3;                    //若x为1，只有4种方案 
    memset(u,0,sizeof(u));
    for(int i=0;i<=3;i++)v[i]=i+1;
}
    for(int _=za;_<=cn;_++){
        aaa(u[_]),aaa(v[_]);                //把这8或4种情况都按一遍，找到符合的 
    bool flag=0;
    for(int i=1;i<=f;i++)                        //对于输入的3,4行条件判断 
        if(q[l[i]]==0){flag=1;break;}
    for(int i=1;i<=h;i++)
        if(q[d[i]]==1){flag=1;break;}    
    if(!flag){
        if(llz)printf("\n");            
        for(int i=1;i<=n;i++)
            printf("%d",q[i]);            
            llz=1;
        }
        aaa(u[_]),aaa(v[_]);                    //按两次就清零了 
    }
}
int main(){
    int i,j,k,m,x;
        scanf("%d%d",&n,&c);
        while(1){
            scanf("%d",&x);                     
            if(x==-1)break;
            l[++f]=x;
        }
        while(1){
            scanf("%d",&x);
            if(x==-1)break;
            d[++h]=x;
        }
        for(i=1;i<=n;i++)q[i]=1;        
        if(c==0){                        //注意c==0的情况，是坑 
            bool flag=0;
            for(int i=1;i<=f;i++)
                if(q[l[i]]==0){flag=1;break;}    //不用操作，直接判断 
            for(int i=1;i<=h;i++)
                if(q[d[i]]==1){flag=1;break;}    
            if(!flag){                        
                if(llz)printf("\n");            //注意空行 
                for(int i=1;i<=n;i++)
                    printf("%d",q[i]);
                    llz=1;}                 
        }
        else dfs(c);
        if(llz==0)printf("IMPOSSIBLE\n");        //没有答案就只能 IMPOSSIBLE
return 0;
}

```

---

## 作者：YczSS (赞：0)

每个按钮按2次和没按效果是一样的。所以每个按钮或者按或者不按，一共有2^4=16种状态。枚举每个按钮是否按下，然后生成结果，排序输出即可（注意判重）。


另外灯1和灯7,2和8,3和9...是一样的因此当N>=6时只需处理前6个,排序时转换为10进制数, 输出时反复输出前6个的状态.


 
```cpp
const
  light:array[1..8,1..6] of integer=
  ((0,0,0,0,0,0),
  (0,0,1,1,1,0),
  (0,1,0,1,0,1),
  (0,1,1,0,1,1),
  (1,0,0,1,0,0),
  (1,0,1,0,1,0),
  (1,1,0,0,0,1),
  (1,1,1,1,1,1));
  min:array[1..8] of integer=(1,2,1,1,2,1,2,0);
{
```
000000--1------1
001110--3+4----2

010101--2------1

011011--4------1

100100--1+4----2

101010--3------1

110001--2+4----2

111111--0------0

 
 
 
```cpp
}
var
  n,i,j,c,t:integer;
  a:array[1..100] of boolean;
  lf:array[1..8] of boolean;
  flag:boolean;
begin
  assign(input,'lamps.in'); reset(input);
  assign(output,'lamps.out'); rewrite(output);
  readln(n);
  readln(c);
  read(t);
  while t<>-1 do begin
    t:=(t-1) mod 6 +1;
    for i:=1 to 8 do
      if not lf[i] then if light[i,t]=0 then lf[i]:=true;
    read(t);
  end;
  readln;
  read(t);
  while t<>-1 do begin
    t:=(t-1) mod 6 +1;
    for i:=1 to 8 do
      if not lf[i] then if light[i,t]=1 then lf[i]:=true;
    read(t);
  end;
  readln;
  for i:=1 to 8 do
    if (not lf[i])and((c-min[i]<0)or(c-min[i]=1)) then
      lf[i]:=true;
  for i:=1 to 8 do
    if not lf[i] then begin
      for j:=1 to n do write(light[i,(j-1)mod 6+1]);
      writeln;
      flag:=true;
    end;
  if not flag then writeln('IMPOSSIBLE');
  close(input);close(output);
end.
```

---

## 作者：plane (赞：0)

第一眼，这道题典型的

搜索
。但是仔细观察，我们不难发现：

1、一个按钮按了两次等于没按。所以不管数据如何，总共有2^4=16种方案

2、仔细观察按钮的功能，我们不难发现，不管怎么按按钮，灯的序列总是六个六个重复的。

3、由1可以知道，只要C mod 16时要求是可以做到的，那么C必然也可以做到。

根据这三条性质，搜索框架就不难确定了（由于我做的时候头脑不清醒，所以用了个四重循环嵌套，一般可以使用DFS进行搜索）。由此可知算法的复杂度应该是常数时间。

在模拟的过程中，一般采用bool数组模拟的方法。但是灯的开关是以0、1串来表示的，而且已证明灯的最终的答案序列是以长度为6的子序列重复存在的，这样我们就可以使用位运算来提高程序的效率。

灯全开着是111111(2)=53(10)

那怎么对灯进行操作呢？很简单。用按位异或进行运算。Pascal里是Xor，C/C++是^


代码:

```cpp
    1 Xor 1 = 0
    1 Xor 0 = 1
    0 Xor 1 = 1
    0 Xor 0 = 0
```
方案一、方案二、方案三和方案四的操作就很显然了。分别是moni xor 111111 、 moni xor 101010、moni xor 010101和moni xor 100100。

```delphi


var a,b:array[1..100]of -1..1;
    c:array[1..8,1..100]of 0..1;
    i,j,x,y,n,t,cc,time:longint;
Procedure King;
var i,j:integer;
    f:boolean;
begin
  for i:=1 to n do if (a[i]<>-1) and (a[i]<>b[i]) then exit;
  for i:=1 to time do
    begin
      f:=true;
      for j:=1 to n do if c[i,j]<>b[j] then f:=false;
      if f then exit;
    end;
  inc(time);
   for i:=1 to n do c[time,i]:=b[i];
end;
Function Large(t1,t2:integer):boolean;
var i:integer;
begin
  i:=1;
  while c[t1,i]=c[t2,i] do inc(i);
  if c[t1,i]>c[t2,i]
  then Large:=true
  else Large:=false;
end;
begin
  readln(n);
  readln(cc);
  read(t);
  for i:=1 to n do a[i]:=-1;
  while t<>-1 do
    begin
      a[t]:=1;
      read(t);
    end;
  read(t);
  while t<>-1 do
    begin
      a[t]:=0;
      read(t);
    end;
  time:=0;
  for i:=0 to 1 do
    for j:=0 to 1 do
      for x:=0 to 1 do
        for y:=0 to 1 do
          if (odd(i+j+x+y)=odd(cc)) and (i+j+x+y<=cc)
          then
            begin
              fillchar(b,sizeof(b),1);
              if i=1
              then for t:=1 to n do b[t]:=(b[t]+1) mod 2;
              if j=1
              then for t:=1 to (n+(n mod 2)) div 2 do b[t*2-1]:=(b[t*2-1]+1) mod 2;
              if x=1
              then for t:=1 to (n+(n mod 2)) div 2 do b[t*2]:=(b[t*2]+1) mod 2;
              if y=1
              then for t:=1 to (n+3-(n mod 3)) div 3 do b[t*3-2]:=(b[t*3-2]+1) mod 2;
              king;
            end;
  for i:=1 to time-1 do
    for j:=i+1 to time do
      if large(i,j)
      then
        begin
          for x:=1 to n do
            begin
              y:=c[i,x];c[i,x]:=c[j,x];c[j,x]:=y;
            end;
        end;
  for i:=1 to time do
    begin
      for j:=1 to n do write(c[i,j]);
      writeln;
    end;
  if time=0 then writeln('IMPOSSIBLE');
end.



```

---

## 作者：thhhty (赞：0)

呐呐蒟蒻又A了一道蓝题就过来发题解了~
事实上木有前面各位大佬们想的16种~~（虽然最后还是八种）~~
事实上这个灯按六位六位看每一组是一样的
也就是说我们模拟六位就好了，对于c的大小（<=2会弄不齐八种）特判一下
总体就八种：（已经按“大小”排好了，0是不开灯，1是开灯，和题目一样）
000000 
001110
010101
011011
100100
101010
110001
111111
当c>=3的时候，就可以分成诺干个（两次一按钮）或（一二三按钮各一次），这样是对结果不变的。因此不用管这么多~
代码：
```c
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int a[10][7],b[10];
bool bm[10];
int main()
{
	memset(bm,true,sizeof(bm));
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	a[1][1]=a[1][2]=a[1][3]=a[1][4]=a[1][5]=a[1][6]=0;//1
	a[2][3]=a[2][4]=a[2][5]=1;//4+2
	a[3][2]=a[3][4]=a[3][6]=1;//2
	a[4][2]=a[4][3]=a[4][5]=a[4][6]=1;//4    >=3||1
	a[5][1]=a[5][4]=1;//4+1
	a[6][1]=a[6][3]=a[6][5]=1;//3
	a[7][1]=a[7][2]=a[7][6]=1;//3+4
	a[8][1]=a[8][2]=a[8][3]=a[8][4]=a[8][5]=a[8][6]=1;//1+1
	int n,c;
	scanf("%d %d",&n,&c);
	while(1)
	{
		int x;
		scanf("%d",&x);
		if(x==-1)break;
		x=(x-1)%6+1;
		b[x]=1;//亮 
	}
	while(1)
	{
		int x;
		scanf("%d",&x);
		if(x==-1)break;
		x=(x-1)%6+1;
		b[x]=2;//灭 
	}
	if(c==0)
	{
		bm[1]=bm[2]=bm[3]=bm[4]=bm[5]=bm[6]=bm[7]=false;
	}
	if(c==1)
	{
		bm[2]=bm[5]=bm[7]=bm[8]=false;
	}
	if(c==2)
	{
		bm[4]=false;
	}
	bool bbk=true;
	for(int i=1;i<=8;i++)
	{
		if(bm[i])
		{
			bool bk=true;
			for(int j=1;j<=6;j++)
			{
				if(b[j]==1&&a[i][j]==0)
				{
					bk=false;
					break;
				}
				if(b[j]==2&&a[i][j]==1)
				{
					bk=false;
					break;
				}
			}
			if(bk)
			{
				bbk=false;
				int len=1;
				while(len<=n)
				{
					int llen=(len-1)%6+1;
					printf("%d",a[i][llen]);
					len++;
				}
				printf("\n");
			}	
		}
	}
	if(bbk)printf("IMPOSSIBLE\n");
	return 0;
}
```

---

## 作者：早右昕 (赞：0)

### 题解~~其实挺水的~~


草草分析完条件后惊奇的发现：

- 不论以什么顺序按开关，电灯总是6个一循环（2\*3）；

- 同一个开关按两次相当于没有按下;


以上条件足以把数据范围强制压缩到n=6,c=(c% 2^4 )的地步，那么就尽管暴力吧。


- 技巧一：四个操作都可以表示为 xor 一个数的形式

- 技巧二：将答案存下后再排序输出，注意排序规则


以下为代码，手写递归（捂脸）：


```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,b[100000];
bool pd(int x) {//判断合法性
    for(int i=0; i<6; i++) {
        if(b[1<<i]==1&&!(x&(1<<i))) return 0;
        if(b[1<<i]==0&&(x&(1<<i))) return 0;
    }
    return 1;
}
bool inv(int x,int y) {//王的♂ 排序规则
    for(int i=0; i<6; i++) {
        if((x&(1<<i))!=(y&(1<<i)))
            return (x&(1<<i))<(y&(1<<i));
    }
    return 0;
}
int d[100]= {-1},h[7],cnt;
void out(int x) {//分解数，输出
    for(int i=0; i<=6; i++) h[i]=x&1,x>>=1;
    for(int i=0; i<n; i++) printf("%d",h[i%6]);
    printf("\n");
}
int main() {
    scanf("%d%d",&n,&m);
    int in;
    memset(b,-1,sizeof b);
    while(~scanf("%d",&in)&&in!=-1) {
        in=(in-1)%6,b[1<<in]=1;
    }
    while(~scanf("%d",&in)&&in!=-1) {
        in=(in-1)%6,b[1<<in]=0;
    }
    m%=16;
    int x=(1<<6)-1;
    int p1=x,p2=21,p3=42,p4=9;
    for(int i=0; i<2; i++) {
        if(i) x^=p1;
        for(int j=0; j<2; j++) {
            if(j) x^=p2;
            for(int k=0; k<2; k++) {
                if(k) x^=p3;
                for(int l=0; l<2; l++) {
                    if(l) x^=p4;
                    if(i+j+k+l<=m && pd(x)) d[++cnt]=x;
                    if(l) x^=p4;
                }
                if(k) x^=p3;
            }
            if(j) x^=p2;
        }
        if(i) x^=p1;
    }
    sort(d+1,d+cnt+1,inv);
    for(int i=1; i<=cnt; i++) {
        if(d[i]!=d[i-1]) out(d[i]);//判重与输出
    }
    if(!cnt) printf("IMPOSSIBLE\n");
    return 0;
}
```

完美。。


---

