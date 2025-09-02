# [USACO2.1] 海明码 Hamming Codes

## 题目描述

给出 $n,b,d$，要求找出 $n$ 个由 $0,1$ 组成的编码，每个编码有 $b$ 位），使得两两编码之间至少有 $d$ 个单位的 “Hamming距离”。“  

Hamming距离”是指对于两个编码，他们二进制表示法中的不同二进制位的数目。看下面的两个编码 `0x554` 和 `0x234`（十六进制数）

```
0x554 = 0101 0101 0100
0x234 = 0010 0011 0100
不同位    xxx  xx
```

因为有五个位不同，所以“Hamming距离”是 $5$。


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 64$，$1\le b \le 8$，$1\le d \le 7$。

请解释：“必须与其他所有的数相比，Hamming 距离都符合要求，这个数才正确”

答：如样例输出，$0,7$，$0,25$，比较都符合海明码，同样 $7,25$，$7,30$，比较也符合要求，以此类推。题中至少有 $d$ 个单位，意思就是大于等于 $d$ 个单位的都可以。


USACO 2.1

翻译来自NOCOW


## 样例 #1

### 输入

```
16 7 3```

### 输出

```
0 7 25 30 42 45 51 52 75 76
82 85 97 102 120 127```

# 题解

## 作者：ylsoi (赞：31)

这个题目真的有一点意思，本来看不懂题目，后面就突然明白了只是求几个N个二进制数，然后要求二进制数两两之间不同的位数必须要大于等于D，然后如果有多组解法的话就取小的那个。但是这里我要隆重的介绍一个函数\_\_builtin\_popcount()它可以统计这个数转化为二进制数中一的个数，我们只要亦或一下，再调用这个神奇的函数，就过了。。。。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int maxn=70;
int n,b,d,ans[maxn],len;
int main()
{
    scanf("%d%d%d",&n,&b,&d);
    len++;
    ans[len]=0;
    int i=1;
    while(len<n)
    {
        bool flag=false;
        for(int j=len;j>=1;j--)
        if(__builtin_popcount(ans[j]^i)<d)//和之前的每一个数都要比较
        {
            flag=true;
            break;
        }
        if(!flag)
        {
            len++;
            ans[len]=i;
        }
        i++;
    }
    for(i=1;i<=len;i++)
    {
        printf("%d ",ans[i]);
        if(i%10==0)cout<<endl;
    }
    return 0;
}
```

---

## 作者：AutumnKite (赞：20)

#看到下面Pascal的只有一个，而且比较麻烦，我来补一个#

##其实这道题还是蛮有意思的。##

###我的思路是直接暴搜，枚举每一个数，然后与前面的每个数判断，如果海明距离>=D，则满足要求。###

##然后怎么求海明距离呢？##

#其实很简单，用位运算啦，先xor出来，统计结果有几个1就行了#

可怜Pascal没有神奇的库函数。

统计有几个1有很多方法，但我觉得比较快的一种方法是x-lowbit(x)也就是x-(x and (-x))。

当然也可以用shl和与运算判断每一位。

接下来奉上我那丑陋的代码：

```cpp
var
  n,b,d,i,j,r:longint;
  a:array[0..1000]of longint; //存储海明码
function count(x:longint):longint; //统计x二进制中1的个数
begin
  count:=0;
  while x>0 do 
    begin
      dec(x,x and (-x)); //把最后一个“1”删去
      inc(count); //加一个
    end;
end;
function check(x:longint):boolean; //判断是否满足要求（海明距离>=D）
var
  i:longint;
begin
  for i:=1 to r do 
    if count(x xor a[i])<d then exit(true);
  exit(false);
end;
begin
  readln(n,b,d); r:=0;
  for i:=0 to 1 shl b-1 do //b用来限制位数
    begin
      if check(i) then continue;
      inc(r); a[r]:=i; //新的一个海明码
      if r=n then break; //个数到了就退出
    end;
  for i:=1 to n do 
    if i mod 10=0 then writeln(a[i]) else write(a[i],' '); //格式还是有点坑的，十个一行输出
end.

```

---

## 作者：「QQ红包」 (赞：17)

题解by:redbag

AC记录：http://www.luogu.org/record/show?rid=780846

原题解地址：http://redbag.duapp.com/?p=1177

我的小屋：http://redbag.duapp.com/

欢迎来踩！


其实就是枚举。我开始不知道b干嘛用的后来才发现b是用来限制枚举范围的？其实自己可以开一个很大的数。当然这题也可以用dfs，不过没必要。


题目2大坑点；


1.两两编码之间至少有 D 个单位，意思是海明距可以>=D，而不仅仅是==D


2.输出十个就要换行，而且每一行的第一个之前不能加空格。


海明距的话有两种方式判断，第一种是用位运算，不会位运算之类的自行百度，也就是我的这种方法，比较简洁，还有一种是楼下的方法，用字符串，比较容易理解，但是写起来不太方便。


                 
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
int n;//n：要求的个数
int d,b;//d距离,b位 
int k;//存目前编码个数 
int i,j;//循环控制变量 
int a[65];//存结果 
int find(int x,int y)//寻找距离，用位运算 
{
    int g=x^y;//相同位不同则为1，相同则为0。
    int s=0;//存1的个数 
    while (g!=0)//找1的个数 
    {
        if (g%2==1) s++;//统计
        g/=2; 
    } 
    return s;
} 
int main() 
{
    freopen("hamming.in","r",stdin);
    freopen("hamming.out","w",stdout); 
    scanf("%d%d%d",&n,&b,&d);
    k=1;
    a[k]=0;
    int hehe=1<<b; 
    while (k<n)
        for (i=a[k]+1/*一定要比上一个数大*/;i<=hehe;i++)
        {
            if (find(a[k],i)>=d)//满足条件
            {
                int he=1;//标记用
                for (j=1;j<=k-1;j++)//用a[k]与之前的都判断一次 
                if (find(a[j],i)<d)
                {
                    he=0;//标记该数不符合条件 
                    break;
                }
                if (he==1)//符合条件 
                {
                    k++;//计数 
                    a[k]=i;//储存
                    break;
```
}//符合条件的话跳出
```cpp
            }
        }   
    printf("%d",a[1]);
    for (int ii=2;ii<=n;ii++)
    {
        if (ii%10!=1)printf(" %d",a[ii]);else printf("%d",a[ii]);
        if (ii%10==0) printf("\n");
    }
    if (n%10!=0) printf("\n");
        return 0;
}
```

---

## 作者：zengqinyi (赞：9)

遇到这个题，第一反应直接暴搜


1、从已有答案最后一个数枚举每一个数，然后与前面的每个数判断，如果每个海明距离都>=d，则满足要求。

2、那么问题就是怎么求海明距离了。


比如我们要求样例中7和25的海明距离

 ![](https://cdn.luogu.com.cn/upload/pic/7645.png) 

 ![](https://cdn.luogu.com.cn/upload/pic/7646.png) 

核心代码如下：

```cpp
inline bool judge(int x,int y)
{
    int tmp=x^y,anss=0;//anss表示海明码
    //‘^’为按位异或符号，在二进制内，如果两个不一样则为1，一样则为0（例：1100101^1011001=0100100）
    while(tmp>0)
    {
        if(tmp%2==1)anss++;//这一位为1（即这两位不一样）则anss++，
        tmp>>=1;//向右移一位
    }
    if(anss>=d)return true;//如果海明码>=d，则返回真
    else return false;
}
```
3、最后直接输出即可

代码附上：

（PS：自动忽略“inline”、“register”等字样，据说是有加速效果的，但好像已被证伪，只是本人习惯打而已）

```cpp
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cstdio>
using namespace std;
#define rint register int
inline void read(int &x)//读入优化
{
    x=0;int w=1;char ch=getchar();
    while(!isdigit(ch)&&ch!='-')ch=getchar();
    if(ch=='-')w=-1,ch=getchar();
    while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^'0'),ch=getchar();
    x=x*w;
}
int n,b,d,ans[80],e;//n，b，d，分别表示题意中的n，b，d。ans[]存答案，e为答案数
inline bool judge(int x,int y)
{
    int tmp=x^y,anss=0;//anss表示海明码
    //‘^’为按位异或符号，在二进制内，如果两个不一样则为1，一样则为0（例：1100101^1011001=0100100）
    while(tmp>0)
    {
        if(tmp%2==1)anss++;//这一位为1（即这两位不一样）则anss++，
        tmp>>=1;//向右移一位
    }
    if(anss>=d)return true;//如果海明码>=d，则返回真
    else return false;
}
inline bool add(int x)
{
    for(rint i=1;i<=e;i++)
        if(judge(x,ans[i])==0)//如果此数与已有答案中任何一数不符合，则返回false
            return false;
    return true;//如果都符合则返回true
}
int main()
{
    read(n);read(b);read(d);
    b=1<<b;//把1左移b位
    ans[++e]=0;
    while(e<n)//当已有的数不超过n时
        for(rint i=ans[e]+1;i<=b;i++)//从已有答案最后一个数开始枚举，且数的编码<=b位
            if(add(i))
                {ans[++e]=i;break;}
    for(rint i=1;i<=e;i++)
        printf("%d%c",ans[i],i%10==0?'\n':' ');//依次输出每个数，如果是10的倍数则输出换行
    return 0; 
}
```

---

## 作者：SCUT_HYX (赞：7)

# **解题步骤**
### 1.起始（贪心思想

因为我们要尽量缩小这些符合条件的数，所以第一个数为零既可（化为二进制全部为零）

### 2.大体方法

再看看数据范围，

#### 1<=B<=8

### 1<=B<=8

## 1<=B<=8

这~~暗示~~明示了我们可以使用暴力循环枚举【O(2^8)】循环每一个数，在将这个数对答案数组内所有数都判断下是否符合差D位或D位以上就可以了

### 3.如何算出海明距离？

#### 3.1 异或

    1^1=0    1^0=1

    0^1=1    0^0=0

    在C++中的异或指的是按位异或，也就是逐位异或

    eg.6^4=?

     1 1 0=====>6

     1 0 0=====>4
    __________

     0 1 0=====>2

####     所以 有6^4=2

####      不难想到，我们可以用一个数来存放两个待比较数的异或值，因为我们要求两者不同位数个数，就对那个数计算1的位个数就行。



#### 3.2 取出当前位

    对于一个十进制数x，x&1就是判断最后一位为1或0的一个布尔式

    假设最后一位是1，那么

        …………1

    &  000001

------------------------

       000001

####     可得，x&1为真时，x最后一位是1；易得，为假时则为0



#### 3.3 取出第i位

    使用右移符号“>>”

    ">>"表示将二进制数最后几位去掉，于是判断倒数第k位就可以如下：
```cpp
if((x>>k)&1) cnt++;     
```

### ———————————————我是分界————————————————

## AC代码：

```cpp
#include<cstdio>
using namespace std;
int n,b,d;
int a[70],tot=1;
int dis(int x,int y)	//判断距离 
{
    int s=x^y,cnt=0;	//先异或求出判断值 
    while(s)
    {
        cnt+=(s&1);		//统计1的个数 
        s>>=1;			//寻找下一位 
    }
    return cnt;
}
int main()
{
    scanf("%d%d%d",&n,&b,&d);
    int Inf=(1<<b);		//边界(左移根据上面讲的领悟下) 
    int i;
    for(i=a[tot]+1;i<=Inf;++i) //枚举 
    {
        if(dis(a[tot],i)>=d)
        {
            bool flg=1;
            for(int j=1;j<tot;++j)	//跟每一个数组里的数中判断 
                if(dis(a[j],i)<d) {flg=0;break;}
            if(flg) a[++tot]=i;
            if(tot>=n) break;	//找到n个弹出结束 
        }
    }
    for(int i=1;i<=n;++i){
        printf("%d",a[i]);
        if(i%10) printf(" ");
        else printf("\n");		//一定要记得换行QWQ 
    }
    return 0;
}
```

---

## 作者：肖恩Sean (赞：5)

补充说明一下楼下的题解

对于位运算来说（以下讲到的数一律按二进制算）

判断一个数x的末尾是不是1，可以用x&1来做，结果为1就是x末尾为1，反之，x末尾为0；

与位左移配合可以达到楼下题解的效果；

核心代码与楼下题解只有一点不同：

```cpp
int hamming(int x,int y){
    int k=x^y,ans=0;
    while (k>0){
        ans+=k&1;//就是这里^-^
        k>>1;
    }
    return ans;
}
```
但是！
还有一种方法可以说比楼下的要好……

核心代码：

```cpp
int hamming(int x,int y){
    int k=x xor y,ans=0;
    while (k>0){
        ans++;
        k-=k&(-k);
    }
    return ans;
}
```
为什么说比楼下的要好呢，这种方法的循环次数就是k中1的个数，而不是k的位数；
可能这点优化程度不大，当数据量足够大时就很明显了，但是最坏情况和楼下是差不多的

解释一下k&(-k)，结果就是去掉k右起第一个1的左边部分；

对于一个带符号整型，-k的结果就是把k的符号位取反后的补码；

举两个例子：当k=00010101时，-k=11101011；

         k=00010101

       -k=11101011

------------------

k&(-k)=00000001

当k=01001000时，-k=10110111；

         k=01001000

       -k=10111000

------------------

k&(-k)=00001000

也就是说k-=k&(-k)就可以做到，去掉k中最后一个1

那么这个代码就很好理解了

此外分享一位神犇的位运算解析：

```cpp
<http://www.matrix67.com/blog/archives/263>
#include<iostream>
using namespace std;
int n,b,d,a[66],num=0,k=0;
bool is_ok=0;
int hamming(int x,int y){
    int k=x xor y,ans=0;
    while (k>0){
        ans++;
        k-=k&(-k);
    }
    return ans;
}
int main(){
    cin>>n>>b>>d;
    for(;k<n;){
        is_ok=1;
        for (int i=1;i<=k;i++)
            if (hamming(a[i],num)<d){
                is_ok=0;
                break;
            }
        if (is_ok) a[++k]=num;
        num++;
    }
    while (k--){
        cout<<a[n-k]<<" ";
        if ((n-k)%10==0) cout<<endl;
    }
}
```

---

## 作者：羽儇 (赞：2)

$\color{Red}\text{位运算大法好}$



```cpp
#include <cstdio>
using namespace std;
int a[65],N,B,D,L,ans = 1;
int main()
{
	scanf("%d%d%d",&N,&B,&D);
	printf("%d ",0);//开头一定是0的说
	for(int i = 0 ;i < (1 << (B + 1) ) - 1 ; i ++)//枚举所有位数不超过B的数
	{
		int Cnt = 0;
		for(int k = 1 ;k <= ans ;k ++)//枚举之前所记录的每一个编码
		{
			Cnt = 0;//因为每次都要重新看
			L = a[k];//每一个编码
			for(int j = 0 ;j <= B ; j ++)
		    if(((1<<j & i)&&!(1 << j & L))||(!(1<<j & i)&&(1 << j & L)))Cnt ++ ;//记录有多少位（有一个数这位为1，且另一位为0）
		    if(Cnt < D)break;//不符
		}//此时Cnt 有两种情况，因Cnt<D 而被break的，与 全部都走一遍并均符合的
		if(Cnt >= D )//判定
		{
			printf("%d ",i);//直接输出即可，不必最后再一次性输出完
			a[++ans] = i;//记录，因为要和后来者相比较
			if(ans % 10 == 0)printf("\n");//每十个数输出一行
			if(ans == N)break;//输出N个数后完结撒花
		}
	}
	return 0;
}
```



$\color{Red}\text{~~码风清丽~~，对吧}$

不加注释的

```cpp
#include <cstdio>
using namespace std;
int a[65],N,B,D,L,ans = 1;
int main()
{
	scanf("%d%d%d",&N,&B,&D);
	printf("%d ",0);
	for(int i = 0 ;i < (1 << (B + 1) ) - 1 ; i ++)
	{
		int Cnt = 0;
		for(int k = 1 ;k <= ans ;k ++)
		{
			Cnt = 0;
			L = a[k];
			for(int j = 0 ;j <= B ; j ++)
		    if(((1<<j & i)&&!(1 << j & L))||(!(1<<j & i)&&(1 << j & L)))Cnt ++ ;
		    if(Cnt < D)break;
		}
		if(Cnt >= D )
		{
			printf("%d ",i);
			a[++ans] = i;
			if(ans % 10 == 0)printf("\n");
			if(ans == N)break;
		}
	}
	return 0;
}
```


---

## 作者：江山_远方 (赞：1)

这道题其实就是一道简单的模拟题

做法很简单 生成即可

什么？生成？怎么生？

很简单鸭~

我们可以用一个A数组来表示这个数的二进制，a[b+1]为哨兵，只要a[b+1]没有为一，我们就可以在a的个位加上一，然后进位，如果他和前面的海明距离>=d即可，将他加入数组，最后输出这些数的十进制即可

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,b,d,tt;
int a[10],bb[1100][10];
int pd()
{
    for(int i=1;i<=tt;i++)
    {
            int sum=0;
            for(int j=1;j<=b;j++)sum+=(a[j]!=bb[i][j]);
            if(sum<d)return 0;
    }
    return 1;
}//判断与前面数的海明距离是否满足要求
int main()
{
    cin>>n>>b>>d;
    tt=1;
    while(!a[b+1])//哨兵
    {
        a[1]++;
        for(int i=1;i<=b;i++)
        {
            a[i+1]+=a[i]/2;
            a[i]%=2;
        }//进位
        if(pd())
        {
            tt++;
            for(int i=1;i<=b;i++)bb[tt][i]=a[i];
        }//加入数组
        if(tt==n)break;
    }
    for(int i=1;i<=tt;i++)
    {
        int x=0,s=1;
        for(int j=1;j<=b;j++)
        {
            x+=bb[i][j]*s;
            s*=2;
        }
        printf("%d ",x);
        if(i%10==0)printf("\n");
    }//输出十进制
    return 0;
}
```


---

## 作者：Creeper_LKF (赞：1)

```cpp
###//位运算+压行
#include<bits/stdc++.h>
using namespace std;
int ans[257],cnt,n,b,d;
inline bool check(int x,int y){
    int z=x^y,tot=0;//计算两个数的相同位上的情况
    do
        if(z&1) tot++;//如果末位为0
    while(z>>=1);//检查下一位
    return tot>=d;
}
inline bool exe(int tar){
    for(int i=1;i<=cnt;i++)//这个算法的正确性在于算法每次枚举并检查一个二进制码时保证了之前的加入答案的二进制码已经两两互查过
        if(!check(ans[i],tar)) return false;//所以每次对新数据检查时，只要将其与已经加入答案的二进制码对比
    return true;
}
int main(){
    scanf("%d%d%d",&n,&b,&d);
    int maxn=1<<b;//加速循环（在不开-O的情况下）
    for(int i=0;i<=maxn&&cnt<=n;i++)//在2^B进制数下最小这句话其实是具有迷惑性的，实际上就是10进制下最小，也就不用进制转换了
        if(exe(i)) ans[++cnt]=i;
    for(int i=1;i<=n;i++){//DFS和顺序枚举出来的结果应该是不用排序的
        printf("%d ",ans[i]);
        if(!(i%10)) printf("\n");//注意换行
    }
    return 0;
}
```

---

## 作者：Ayano (赞：1)

枚举的思路从0开始一直到256即可（最大的8位2进制11111111就是256）

```cpp
#include<iostream>  
#include<cstdio>  
#include<cstring>
using namespace std;  
int N,B,D;  
int num[266];  
//不需要考虑各个数字原2进制数 只需要前面补0即可 例 1->00000001（7位hamming code）
int num1(int a)
```
{//计算B位数与0的距离，即B位数中1的个数
      
```cpp
    int i,cnt=0;  
    for (i=0;i<B;i++)  
    {  
       cnt=cnt+(a&1);  //--统计1的个数 
       a=a>>1;         //--位运算来表示 /2 
    }  
    return cnt;  
}  
int Hamc(int x,int c,int d)
{  
    int i,temp;  
    for (i=0;i<c;i++)  
    {  
        temp=x^num[i];//异或结果，可以通过计算B位数x中1的个数  
        if (num1(temp)<d)//--距离>=d即可 
          return 0;  
    }  
    return 1;  
}  
int main()  
{   
    scanf("%d%d%d",&N,&B,&D);  
    num[0]=0; //0是一定会出现的。  
    int vis=0;//--统计hamming code满足的个数  
    int i;  
    for (i=1;i<=256;i++) //--枚举 
    {  
        if(Hamc(i,vis+1,D))   
            num[++vis]=i;//--储存答案 
    }  
    i=0;  
    for(i=0;i<N;i++)//--枚举前N个 
    {  
        printf("%d",num[i]);  
        if ((i+1)%10==0||i==N-1)//--格式注意 
            printf("\n"); 
        else if (i<N-1)  
            printf(" ");
    }  
    return 0;  
}
```

---

## 作者：Times_New_man (赞：0)

# $\Huge\texttt{DFS爆搜题}$
## 直接亮代码$:$
```cpp
#include<iostream>
//#include<cstdio>
using namespace std;

int N,B,D,maxval,nums[10000],dist[1000][1000];
//FILE *in,*out
//找出N个由0或1组成的编码(1<=N<=64),每个编码有B位(1<=B<=8),使得两两编码之间至少有D个单位的"Hamming距离"(1<=D<=7)
//maxval:最大可枚举的二进制编码(2的B次方)
//nums[i]:编码的第i位 
//dist[i][j]:i和j的"Hamming"距离 
//FILE :#include<cstdio>,最快文件操作,读取fscanf(),写入fprintf(),现在用不到 

void init()					//预处理海明码距离dist
{
    maxval=1<<B;			//1<<B=2的B次方 
	for(int i=0;i<maxval;i++)
     	for(int j=0;j<maxval;j++)
     	{
     		dist[i][j]=0;
     		for(int k=0;k<B;k++)
     			if(((1<<k)&i)!=((1<<k)&j))			//&:按位与,用<<(位运算,左移)取出每一位 
                //这里优先级死坑,调了我1分钟,!=两边不加括号WA声一片
     				dist[i][j]++;
        }
}

bool dfs(int cur,int start)
//cur:编码中存在了cur个元素 
//start:从第start个元素向后找 
//返回值:找没找到N个数 
{
    if(cur==N)		//全都找到了 
    {
        for(int i=0;i<cur;i++)
        {
            if(i%10)
                cout<<' ';			//10个一空格 
            cout<<nums[i];			//打印每一个编码 
            if(i%10==9||i==cur-1/*死坑的UVA最后要换行,否则WA声一片*/)
                cout<<endl;			//10个一换行 
        }
        return true;
    }
    for(int i=start;i<maxval;i++)		//从i枚举到最大值 
    {
		int ok=1;				//可不可以放入集合 
        for(int j=0;j<cur;j++)		//比较 
            if(dist[nums[j]][i]<D)		//位数不够 
            {
                ok=0;
                break;
            }
        if(ok)
        {
            nums[cur]=i;			//填入集合 
            if(dfs(cur+1,i+1))		//如果找到,就不用继续找 
                return true;
        }
    }
    return false;		//还没找到 
}

int main()
{
	//in=fopen("hamming.in","r");
	//out=fopen("hamming.out","w");
     cin>>N>>B>>D;
     init();		//常用的数据要初始化 
     dfs(0,0);
    return 0;
}
```


---

## 作者：mike_he (赞：0)

利用C++的bitset方便每次位操作。每次从1枚举到2^B次方将符合条件的加入，深搜下一层








```cpp
#include <iostream>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;
#define ull unsigned long long
vector< bitset<8> > ans;
bool vis[1024];
int N,B,D;
void dfs(int idx){
    if(idx > N){ // 如果搜到头了
        for(int i=0;i<ans.size();++i){
            cout<<ans[i].to_ulong()<<" ";
            if((i+1)%10 == 0){
                puts("");
            }
        }
        exit(0); // 由于是DFS，第一次搜到的一定是最优解
    }else{
        for(int i=0;i<=1<<(B+1);++i){ // 最多只有B位，只需要枚举到2^B
            if(!vis[i]){
                vis[i] = true;
                bitset<8> add((ull)i); // 新建一个bitset
                for(int j=0;j<ans.size();++j){
                    bitset<8> k = add ^ ans[j];
                    if(k.count()<D){ // 检查海明距离
                        vis[i] = false;
                        break;
                    }
                }
                if(!vis[i]) continue; // 如果不符合条件直接略过
                else {
                    ans.push_back(add); // 否则加入答案
                    dfs(idx+1); // 搜索下一层
                }
                ans.pop_back(); // 当前答案不符合标准，舍掉
                vis[i] = false;
            }
        }
    }
}
int main(){
    cin>>N>>B>>D;
    dfs(1);
    return 0;
}
```

---

## 作者：Conical (赞：0)

楼下算法讲的很明确了，但是位运算上还是太烦了。在此贴上本人位运算代码，供各位OIER参考。

```cpp
#include<stdio.h>
#include<iostream>
using namespace std;
int N,Ans[128],D,B,M;
inline bool Cmp(int x,int y)
{
    int s=x^y,t,Sum(0),i;
    for(i=0;(1<<i)<=s;i++)
    {
        t=1<<i;
        if(t&s)
            Sum++;
    }
    return Sum<D;
}
inline bool Harm(int x)
{
    int i;
    for(i=1;i<=M;i++)
        if(Cmp(x,Ans[i]))
            return 0;
    return 1;
}
int main()
{
    int i;
    scanf("%d%d%d",&N,&B,&D);
    for(i=0;i<(1<<(B+1))&&M<N;i++)
        if(Harm(i))
            Ans[++M]=i;
    for(i=1;i<=N;i++)
    {
        printf("%d ",Ans[i]);
        if(i%10==0)
            puts("");
    }
    return 0;
}
```

---

## 作者：Stella_Yan (赞：0)

看到楼下大佬把题中的B拿来用,其实本人发现B好像毫无用处。

一个数转换成2^b进制数是最小的,那么它转成十进制肯定也是最小的啊。

输出的序列是一个递增的序列,所以你只要一直往下找,第一个找到的肯定是最小的啦

还有就是：如何判断两个数在二进制中不同的位数？

只要异或一下,两个位相同的值为0,不相同的为1,所以只要统计一个数二进制下有几个1就可以了。

具体分析看代码:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,d;
bool b;
int f[1010];//f[i]表示输出的第i个数
bool isd(int a,int b)//判断两个数的海明距离是否≥d
{
	int t=a^b;//异或的符号是'^'
	int sum=0;//不相同的位数
	while(t>0){
		if(t%2==1){//在二进制下是mod 2
			sum++;
		}
		t>>=1;//右移一位相当于除以2
	}
	if(sum>=d)//判断
		return true;
	return false;
}
int main()
{
	scanf("%d %*d %d",&n,&d);//b没有用,scanf中%*d代表输入的值不赋给一个变量
	int x=0,cnt=1;//cnt代表已经选的数的个数,第一个是0
	f[1]=0;
	for(int i=1;;i++){//既然把b扔掉了,那就不要≤1<<b了,直接一直加到找到n个数为止
		b=0;//这个b代表是否找到答案
		for(int j=0;j<=cnt;j++){//在前面的数找
			if(!isd(i,f[j])){//如果海明距离<d
				b=1;//标记没有找到答案
				break;
			}
		}
		if(!b){//如果找到答案
			f[++cnt]=i;//存储数
			if(cnt==n){//如果找到了n个数就退出
				break;
			}
		}
	}
	for(int i=1;i<=n;i++){//输出
		printf("%d ",f[i]);
		if(i%10==0){//十个一行
			printf("\n");
		}
	}
}
```
[~~第一次在题解里挂blog~~](https://jiying.blog.luogu.org/)

---

## 作者：Celebrate (赞：0)

这一题的第一位必定是0，因为这是最小的

虽然感觉这一题有些麻烦，但是我灵感突发，想到了用一个

f数组记录，f[i][j]表示i的二进制和j的二进制的“Hamming距离”

这样是不会超时的，因为最多八位，最大的变成十进制也就是255

255^2*b*5/2+dfs的时间，最多也就是循环2000万次不到

代码如下：
```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int a[110],n,b,d,f[310][310],max,g[11];
int a1[11],a2[11];
bool bk=false;
inline void kangtuo(int k)//康拓展开，求出二进制k的每一位数 
{
	int i=0;
	while(k>0)
	{
		i++;g[i]=k%2;k/=2;
	}
	i++;for(i=i;i<=b;i++) g[i]=0;//不足的补0，因为一开始g不一定全部为0的
}
inline int find_haiming(int x,int y)//找x和y（十进制）的“Hamming距离” 
{
	int i,s=0;
	kangtuo(x);for(i=1;i<=b;i++) a1[i]=g[i];//记录 
	kangtuo(y);for(i=1;i<=b;i++) a2[i]=g[i];
	for(i=1;i<=b;i++)//求“Hamming距离” 
	{
		if(a1[i]!=a2[i]) s++;
	}
	return s;//返回 
}
inline void _()//求所有数和其他数的“Hamming距离” 
{
	int i,j,t=1;
	for(i=1;i<=b;i++)//求出最大的二进制改十进制的大小，b是因为有b位数 
	{
		max=max+t;
		t*=2;
	}
	for(i=0;i<=max;i++)//暴力搜索 
	{
		for(j=0;j<=max;j++)
		{
			if(f[i][j]!=0) continue;//如果搜索过了，那就不用再搜了 
			if(i==j){f[i][j]=0;f[j][i]=0;continue;}//如果相等，就肯定是0 
			f[i][j]=f[j][i]=find_haiming(i,j);//找“Hamming距离” 
		}
	}
}
//前面的都是优化，现在才开始打真正的代码 
inline bool pd(int k,int x)//判断在前位是否能放下x 
{
	int i;
	for(i=1;i<=k;i++)
		if(f[a[i]][x]<d) //如果不到这个“Hamming距离”，记得题目说是间至少有 D 个单位，而不是刚好等于 
			return false;//返回不行 
	return true;//返回行 
}
int dfs(int k)//搜索到第k个数 
{
	if(k==n+1)//搜索完毕就输出 
	{
		for(int i=1;i<=n;i++)
		{
			printf("%d ",a[i]);
			if(i%10==0) printf("\n");
		}
		exit(0);
	}
	else//继续 
	{
		for(int i=a[k-1]+1;i<=max;i++)//第j个至少比k-1个多1 ,max就不用解释了 
		{
			a[k]=i;//记录 
			if(pd(k-1,i)==true) //如果能放的话，记得：是pd(k-1,i)而不是pd(k,i) 
				dfs(k+1);
			a[k]=0;//回溯 
		}
	}
}
int main()
{
	scanf("%d%d%d",&n,&b,&d);//很美丽的主程序 
	_();a[1]=0;dfs(2);//a[1]肯定是0，因为要找最小的，从第二位开始递归 
	return 0;
}
```

---

