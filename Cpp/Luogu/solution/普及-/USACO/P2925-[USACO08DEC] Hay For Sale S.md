# [USACO08DEC] Hay For Sale S

## 题目描述

农民 John 面临一个很可怕的事，因为防范力度不大所以他存储的所有稻草都被蟑螂吃光了，他将面临没有稻草喂养奶牛的局面。在奶牛断粮之前，John 拉着他的马车到农民 Don 的农场中买一些稻草给奶牛过冬。已知 John 的马车可以装的下 $C(1\le C\le5\times10^4)$ 立方的稻草。

农民 Don 有 $H(1\le H\le5\times10^3)$ 捆体积不同的稻草可供购买，每一捆稻草有它自己的体积 $V_i(1\le V_i\le C)$。面对这些稻草 John 认真的计算如何充分利用马车的空间购买尽量多的稻草给他的奶牛过冬。

现在给定马车的最大容积 $C$ 和每一捆稻草的体积 $V_i$，John 如何在不超过马车最大容积的情况下买到最大体积的稻草？他不可以把一捆稻草分开来买。

## 样例 #1

### 输入

```
7 3 
2 
6 
5 
```

### 输出

```
7 
```

# 题解

## 作者：XiXi (赞：32)

##### 很简单的01背包，每件物品的价值和重量相同，直接套就行了。还有其中有个点要优化，在中途进行判断就好了，当然开O2优化也行

`

```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int f[111111];
    int main()
    {
        int n,m,i,j,a[111111];
        cin>>m>>n;
        for (i=1;i<=n;i++) scanf("%d",&a[i]);
        for (i=1;i<=n;i++)
        {
            for (j=m;j>=a[i];j--)
            f[j]=max(f[j],f[j-a[i]]+a[i]);
            if (f[m]==m) {printf("%d",m); return 0;}//优化，如果已经达到最好的结果（装满），就直接退掉
        }
        printf("%d",f[m]);
}
```

---

## 作者：Skyjoy (赞：20)

# 很好的01背包模板题

板子：

```cpp
for(int i=1;i<=n;i++){
		for(int j=m;j>=v[i];j--){
			f[j]=max(f[j],f[j-v[i]]+v[i]);
		}
	}
```
n为个数，m为钱数，v为价值。

当然，看看样例，$nm$的复杂度是会TLE的，怎么办？

我们会发现，有时候，马车早早地就被填满了。这时，我们就可以直接结束了。上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[50010],v[5010],c,h;
int main(){
	cin>>c>>h;
	for(int i=1;i<=h;i++){
		cin>>v[i];
	}
	for(int i=1;i<=h;i++){
		for(int j=c;j>=v[i];j--){
			f[j]=max(f[j],f[j-v[i]]+v[i]);//板子 
		}
		if(f[c]==c){//判断是否装满 
			cout<<c;
			return 0;
		}
	}
	cout<<f[c];
	return 0;
}
```
祝所有看到此题解的小伙伴们NOIp2019rp++！！！

---

## 作者：BuXiangJuanLe (赞：9)

像这种求组成某个体积的题，都能用`bitset`水过去，自带常数优化

`b[i]`代表能否组成体积i，易知如果`b[i] = true`，有一个物品体积为v，则`b[i + v] = true`

找到最大的`b[i] == true`的i即为最大体积

```cpp
#include<bits/stdc++.h>
int h, c, v, ans;
std::bitset <50018> b;
int main(){
	b[0] = 1;
	std::cin>>c>>h;
	for(int i=1 ; i<=h ; i++){std::cin>>v; b |= b<<v;}
	for(ans=c ; ans>=0 ; ans--) if(b[ans]) break;
	std::cout<<ans;  
}
```

---

## 作者：fls233666 (赞：4)

**2020年2月13日更新：修复题解的排版格式**

-------

看到这道题时，我马上想到了普及组的一题与这题相似的题目。

[P1049 装箱问题](https://www.luogu.org/problemnew/show/P1049)

显然，两道题都是**01背包**，一个要求其剩下的体积，一个要求其已经装了东西的体积。可以先去做一下 P1049 ，再来看这题。

01背包是所有背包问题中最基础的一种，如果你做完了 P1049 ，这题的二维 dp 方程式就很容易得出，如下：

$dp(i,j)=\begin{cases}dp(i-1,j)&v(i) > j \\ dp(i-1,j-v(i))+v(i)&v(i)\le j \end{cases}$

此处 $dp(i,j)$ 表示前 $i$ 个物品放入容量为 $j$ 的背包能得到的最大价值。

 _因为题目要求体积最大，所以此题中每个物品的体积大小就是这个物品的价值。_ 

但是，二维肯定**爆空间**了。

我们发现，表示前 $i$ 个物品的那一维是多余的，所以我们压缩一下，得到一维 dp 方程式：

$dp(j)= \max(dp(j-v(i))+v(i),dp(j)) \qquad v(i)\le j$

空间复杂度就符合了。下面是代码：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main(){
    int c,h;
    cin>>c>>h;   //读入题目中的c和h
    int v[h+1],dp[c+1];
    for(int i=1;i<=h;i++)
        cin>>v[i];   //读入每个稻草的体积
    memset(dp,0,sizeof(dp));
  
  
    for(int i=1;i<=h;i++)
        for(int j=c;j>=v[i];j--)
            dp[j]=max(dp[j],dp[j-v[i]]+v[i]);
  	//01背包dp
  
    cout<<dp[c];  //输出答案
  //与P1049不同的是，P1049输出的是c-dp[c]
    return 0;
}
```

然后，居然**超时了一个点**！

这个时候，我们把 $\texttt{cin}$ 和 $\texttt{cout}$ 的输入输出全部改成了 $\texttt{scanf}$ 和 $\texttt{printf}$，然后把 $\texttt{max}$ 换成了三目运算符。**虽然只是一些简单的优化，但是这已经足够让代码 AC**。

满分代码如下：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int main(){
    int c,h;
    scanf("%d%d",&c,&h);
    int v[h+1],dp[c+1];
    for(int i=1;i<=h;i++)
        scanf("%d",v+i);
    memset(dp,0,sizeof(dp));
    
    for(int i=1;i<=h;i++)
        for(int j=c;j>=v[i];j--)
            dp[j]=dp[j]<dp[j-v[i]]+v[i]?dp[j-v[i]]+v[i]:dp[j];
            
    printf("%d",dp[c]);
    return 0;
}
```


---

## 作者：zzr8178541919 (赞：2)


### 本题是01背包的经典题型，

#### 不过这里需要用到优化（其实也不叫优化），不然可能超时

#### 在第二个循环的时候可以直接从a[j]开始，这样可以保证用容量去减a[j]的时候一定大于等于0。从而能够节省一个判断的时间

#### （不然可能只有91分哦）

```cpp
include<iostream>
using namespace std;
int a[50500];
int ans[50500];//ans数组就用来统计答案
int main()
{
    int n,m;
    cin>>n>>m;
    for(int j=1;j<=m;j++)
    {
        cin>>a[j];
        for(int i=n;i>=a[j];i--)
        {
            ans[i]=max(ans[i],ans[i-a[j]]+a[j]);
        }
    }
    cout<<ans[n];
    return 0;
}//程序结束
```
### 背包问题其实算是动态规划问题中的一个分支，这道题是一道标准的01背包问题，比较适合初学者。
#### 学背包的时候如果有不懂是正常现象，毕竟初学，可以通过做题练习以及交流的方式使自己的代码能力得到提高






---

## 作者：清风我已逝 (赞：1)

水题

01背包的变形

目的是可以运回的最大体积，体积c的背包，物品体积a[i]

状态转移方程
	
    dp[j]=max(dp[j],dp[j-a[i]]);
    


dp[j]表示体积j是否能够达到


边界条件：
	
    dp[minn]=1;

minn为所有物品里的最小值


奉上代码：

```cpp
#include<cstdio>

#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

using namespace std;
int c,h,a[5005],dp[50005],minn=1e9+7;
int main()
{
	scanf("%d%d",&c,&h);
	for(int i=1;i<=h;++i) {
		scanf("%d",&a[i]);
		minn=min(minn,a[i]);
	}
	dp[minn]=1;
	for(int i=1;i<=h;++i)
		for(int j=c;j>=a[i];--j)
			dp[j]=max(dp[j],dp[j-a[i]]);
	for(int i=c;i>=0;--i)
		if(dp[i]==1){printf("%d",i);break;}
	return 0;
}
```

---

## 作者：Enigmatic (赞：1)

本题是一道典型的01背包问题

每包干草只有拿或不拿两种情况

但是用普通的01背包并不能通过

因为这里有特殊情况

我在每次装完背包都加了一个判断

如果已经装到了C的干草就直接退出

不加判断会超时

当然还有一贯的输入优化

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
int hay[5010];
int dp[50010];
inline void read(int &x)
{
    x=0;
    bool f=0;
    char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-')
    {
        f=1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=x\*10+ch-'0';
        ch=getchar();
    }
    if(f) x=-x;
}
int main()
{
    read(m);
    read(n);
    for(register int i=1;i<=n;i++) read(hay[i]);
    for(register int i=1;i<=n;i++)
    {
        for(register int j=m;j>=hay[i];j--)
            dp[j]=max(dp[j],dp[j-hay[i]]+hay[i]);    
        if(dp[m]==m)
        {
            printf("%d\n",dp[m]);
            return 0;    
        }    
    }
    printf("%d\n",dp[m]);
    return 0;
}

---

## 作者：Snitro (赞：1)

此题如果使用普通的01背包会超时，因此添加几条优化


1、由于需要从小到大遍历车的容量，假设车的容量是a，那么f[a]一定小于等于a


这说明当f[a]取a时就不用再一次对f[a]进行更新了


2、由于车的总容量为c，那么这辆车最多只能装体积为c的干草


因此如果已经可以装体积为c的干草就直接输出结果并退出


[本人博客](http://blog.csdn.net/fine\_rose/article/details/69577919)


```cpp
#include<iostream>
using namespace std;
int c,h;//c容量 h种情况 
int f[50005];
int v[50005];
int main(){
    cin >> c >> h;
    for(int i = 1;i <= h;i++)
        cin >> v[i];
    for(int i = 1;i <= h;i++){
        for(int a = c;a >= v[i];a--){
            if(f[a] == a)
                continue;  //此时f[a]已经取到最大值 就不用再对f[a]进行更新 
            if(f[a - v[i]] + v[i] > f[a])
                f[a] = f[a - v[i]] + v[i];
        }
        if(f[c] == c){//判断是否已经能够装满c体积的干草
            cout << c;//能够装满
            return 0;//退出
        }
    }
    cout << f[c];
    return 0;
}
```

---

## 作者：3269224138刘 (赞：1)

每输入一个数时，记下最大的数，做一遍1到最大数的循环，如果前面的数符合条件，则那个数加上输入的这个数也可以符合条件，再判断新的数它有没有大于背包体积，没有大于就符合条件，最后再从背包体积倒序循环，找到了符合条件的数就输出，结束程序


```cpp
var
  f:array[-5..50005] of boolean;
  n,v,a,max,i,j:Longint;
begin
  f[0]:=true;
  max:=0;
  readln(v,n);
  for j:=1 to n do
  begin
    readln(a);
    for i:=max downto 0 do
    begin
      if (a+i<=v) and (f[i]=true) then
      begin
        f[a+i]:=true;
        if max<a+i then
          max:=a+i;
      end;
    end;
  end;
  for i:=v downto 0 do
    if f[i] then
    begin
      writeln(i);
      halt;
    end;
end.
```

---

## 作者：臻品 (赞：1)

```cpp
 var
  i,j,C,H:longint;
  f:array[0..50000]of longint;
  a:array[0..5000]of longint;
   begin
    readln(C,H);
    f[0]:=1;
    for i:=1 to H do readln(a[i]);
    for i:=1 to H do
     for j:=C downto a[i] do
      if f[j-a[i]]=1 then f[j]:=1;
    j:=C;
    while f[j]=0 do dec(j);
    writeln(j);
   end.
//很裸的背包问题
```

---

## 作者：scq2017 (赞：1)

emmmm 本蒟蒻表示这是标准的01背包....的改编


只是把最大价值改成了最大体积而已

但有一个测试点容易TLE所以要优化
 #### 如果已经装满，直接退出
 
~~还是没有太大变化的...~~

状态转移方程如下

### dp[j]=max(dp[j],dp[j-v[i]]+v[i]);
dp[j]表示当前容积下能装的最大体积是多少

dp[j-v[i]]+v[i]表示如果装下当前的物品所剩的体积能装的最大体积是多少

i=1~H

j=C~v[i]

上代码
```cpp

#include<bits/stdc++.h>//万能头
using namespace std;
int C,H,dp[50005]={0},v[5005];
int main()
{
    cin>>C>>H;
    memset(dp,0,sizeof(0));//初始化
    for(int i=1;i<=H;i++) cin>>v[i];
    for(int i=1;i<=H;i++)
	{	
		for(int j=C;j>=v[i];j--)
		{
			dp[j]=max(dp[j],dp[j-v[i]]+v[i]);
			if(dp[j]==j) continue;//优化
		}
		if(dp[C]==C) //优化
		{
			cout<<C<<endl;
			return 0;
		}
	}
    cout<<dp[C]<<endl;
    return 0;
} ```

---

## 作者：up_grant (赞：0)

本题直接套背包容易超时。大家都知道**当背包空间能整除物品体积时，背包一定可以装满**，后面也就不用再继续动态规划了。因此可以把这个作为一个优化的判断条件（其实是本题的数据太特殊）。整体还是背包的思路。下面是代码
```cpp
#include <iostream>

using namespace std;
int dp[50001];
int main()
{
    register int n,m,cost,value;
    cin>>m>>n;
    for (int i=0;i<=m;++i)
        dp[i]=0;
    for (int i=0;i<n;++i)
    {
        cin>>cost;
        value=cost;
        if (m%cost==0)
        {
            dp[m]=m;
            break;
        }
        for (int j=m;j>=cost;--j)
        {
            dp[j]=max(dp[j],dp[j-cost]+value);
        }
    }
    cout<<dp[m];
    return 0;
}

```

---

## 作者：2017hxz (赞：0)

中间不跳出照样过

这一题少了一个维度，直接用bool即可，判断能否达到该状态

```cpp
#include<iostream>
using namespace std;
int const maxc=50000+10;
int c,n,a[5001];
bool dp[maxc]= {1};
int main()
{
    cin>>c>>n;
    for(int i=1; i<=n; i++)
    {
        cin>>a[i];
        for(int j=c; j>=a[i]; j--)dp[j]=dp[j]||dp[j-a[i]];
    }
    int l=c;
    while(!dp[l])l--;
    cout<<l;
    return 0;
}

```

---

## 作者：PTC06 (赞：0)

一开始90分，最后一个点TLE。原因是本来状态转移方程写的是b[j]=max(b[j],b[j-x]+x) 的，后来发现讨论那里有些关于这个的问题，改成if判断就可以AC了，希望做题者小心。此题是简单的01背包。

01背包的一大特点：每种物品仅有一件，可以选择放或不放。此题符合了这个条件。

可以将此题转化为01背包，认为每个干草的价值和空间相等，用01背包求出价值最大值。

```cpp
void bg(long long x)
{
       for (j=v;j>=x;j--)
       {
           if (b[j]<b[j-x]+x) b[j]=b[j-x]+x;
       }    
}
```
这里的b[j]是原来不放入x所能获得的最大价值，而加入了x之后的所能获得的最大价值，就是b[j-x]加上x自身的价值。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
long long i,v,n,j,temp,b[50000];
void bg(long long x)               //这里是实现01背包的中心思想的部分。判断是本来的b[j]大还是加入了x这个元素之后大。
{
       for (j=v;j>=x;j--)
       {
           if (b[j]<b[j-x]+x) b[j]=b[j-x]+x;        //b[j]是原来没有加入x的，b[j-x]+x是加入了x之后的，将两者的大小判断，取其中更大的。
       }    
}
int main()
{
    scanf("%d%d",&v,&n);          //输入
    for (i=1;i<=n;i++)
    {
        scanf("%d",&temp);              //输入每一个的体积。
        bg(temp);                     //调用自定义函数。
    }
    printf("%d",b[v]);
}
```

---

## 作者：little_gift (赞：0)

##听说01背包过不了，我试了试，结果AC了，最后一个点634ms##

```cpp
var
  n,m,t,i,j:longint;
  f:array[0..50000] of longint; //f[x]:存储当重量为x时最大的价值
begin
  readln(m,n);
  for i:=1 to n do //n个物品
    begin
      readln(t); //读入每个物品的重量
      for j:=m downto t do //从背包容量到重量进行循环
        if f[j]<f[j-t]+t then //如果不取这个物品最大的价值<取了这个物品最大的价值
          f[j]:=f[j-t]+t; //更改当前最大的价值
    end;
  writeln(f[m]); //输出当重量为m时最大的价值
end.
```

---

## 作者：The_Stalker (赞：0)

装箱问题裸题

看到这种解法只有pascal,那我就发一个c++题解

思路类似于桶排：如果某个质量可以取，那么这个质量加上当前物体的质量也可以取

具体看注释

```cpp
#include<bits/stdc++.h>
using namespace std;
long long v,n,a[501],F[100000];
//F[i]表示重量为i的情况是否存在(数组开大防止越界)
int main()
{
	cin>>v>>n;//输入最大质量和个数
	for(int i=1;i<=n;i++)
	cin>>a[i];//a[i]为每个物体的质量
	F[a[n]]=1;
    F[0]=1;//初始化，空的和装最后一个的状态初始化为1
    for(int i=n-1;i>=1;i--)//从后向前搜索防止重复累加
	{
        for(int j=v;j>=0;j--)//从后往前防止重复
        if(F[j]!=0)
        F[j+a[i]]=1;
        //如果F[j]这个状态本来可以取，那么F[j+a[i]]这个状态也可以取。F[j]=1标记F[j]可以取
	}    
	for(int j=v;j>=1;j--)//从最大质量往前搜索
	if(F[j]==1)//找到第一个能取到的即为最大质量
	{        
	cout<<j;//输出能取的最大质量
	return 0;//强制终止程序
	}
}
```

---

