# [USACO07DEC] Bookshelf 2 B

## 题目描述

Farmer John最近为奶牛们的图书馆添置了一个巨大的书架，尽管它是如此的大，但它还是几乎瞬间就被各种各样的书塞满了。现在，只有书架的顶上还留有一点空间。 所有N(1 <= N <= 20)头奶牛都有一个确定的身高H\_i(1 <= H\_i <= 1,000,000 - 好高的奶牛>\_<)。设所有奶牛身高的和为S。书架的 高度为B，并且保证1 <= B <= S。 为了够到比最高的那头奶牛还要高的书架顶，奶牛们不得不象演杂技一般，一头站在另一头的背上，叠成一座“奶牛塔”。当然，这个塔的高度，就是塔中所有奶牛的身高之和。为了往书架顶上放东西，所有奶牛的身高和必须不小于书架的高度。 塔叠得越高便越不稳定，于是奶牛们希望找到一种方案，使得叠出的塔在高度不小于书架高度的情况下，高度尽可能小。你也可以猜到你的任务了：写一个程序，计算奶牛们叠成的塔在满足要求的情况下，最少要比书架高多少。


## 说明/提示

输出说明:

我们选用奶牛1、3、4、5叠成塔，她们的总高度为3 + 3 + 5 + 6 = 17。任何方案都无法叠出高度为16的塔，于是答案为1。


## 样例 #1

### 输入

```
5 16
3
1
3
5
6```

### 输出

```
1```

# 题解

## 作者：道费而隐 (赞：47)

# DP题解
###### 各位大佬们都用的深搜啊...
其实dp也可以解这道题，而且是裸的01背包  
我们可以先算出牛的总高度，再减去书架的高度，即为背包的总容量。要使得叠出的塔在高度不小于书架高度的情况下，高度尽可能小，那么背包就应尽可能地填满，所以h[i]既相当于01背包里的容量又相当于价值，使背包中总价值最大，那么背包中总容量（高度）就最大，此时剩下的牛叠出的塔在高度不小于书架高度的情况下，高度就是最小的。  
因此，状态转移方程如下：
###### f[j]=max(f[j],f[j-h[i]]+h[i])
上AC代码：
```cpp
#include<vector>
#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstdlib>
#include<string>
#include<iomanip>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<queue>
#include<map>
#include<set> 
//不想打万能头文件
using namespace std;
typedef long long ll;
int n,b,tot,w,h[25],f[1000001];
int main()
{
	cin>>n>>b;
	for(int i=1;i<=n;i++)
	{
		cin>>h[i];
		tot+=h[i];//求牛的总高度
	}
	w=tot-b;//w即为所以牛的高度减去书架的高度，也就是背包的容量
	for(int i=1;i<=n;i++)
	{
		for(int j=w;j>=h[i];j--)
		{
			f[j]=max(f[j],f[j-h[i]]+h[i]);//h[i]既相当于01背包里的容量又相当于价值
		}
	}
	cout<<tot-f[w]-b;//牛的总高度减去放入背包中牛的高度再减去书架高度就是所求解
	return 0;//结束
}
```
  ~~本蒟蒻第一次发题解，一定要过啊。。~~

---

## 作者：Infinity_shl (赞：22)

本题基本思路：对每一个奶牛进行搜索，若达到高度，与之前的最佳高度比较，最后得出结果。

如下为AC代码：             非常简单的dfs，适合新手练习

```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int a[21],n,b;
    int ans=30000000;
    int vis[21];
    void dfs(int sum)
    {
        if(sum>=b)     //如果到达了高度，就进行比较
        {
            ans=min(ans,sum);  //择优选择
            return ;
        }
        for(int i=1;i<=n;i++)    //搜索每一只牛
            if(vis[i]==0)      //如果没用过
            {
                vis[i]=1;   //标记
                sum+=a[i];   //加上高度
                dfs(sum);    //继续搜索
                sum-=a[i];   //回溯一步
                vis[i]=0;
            }
    }
    int main()
    {
        scanf("%d%d",&n,&b);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);   //输入
        dfs(0);
        cout<<ans-b;              //输出高度的差
        return 0;
    }

```

---

## 作者：Sioncovy (赞：8)

发现似乎没有玄学做法啊，这怎么能行呢，那我就来~~骚一波吧~~讲一下吧。

首先，我们来了解一下 **random_shuffle** 函数。头文件是<algorithm>,功能就是把一个数组中的数列随机重排，参数自然就是数组的头和尾了。~~玄学必备啊~~
  
  ```cpp
# include <iostream>
# include <cstdio>
# include <cstdlib>
# include <algorithm>
# include <string>
# include <cmath>
# include <vector>
using namespace std;

int read(){
	int x = 0, k = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){
		if(ch == '-')	k = -1;
		ch = getchar();
	}	
	while(ch >= '0' && ch <= '9'){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * k;
} //快读，无视就好了。

int n, H;//奶牛数量，书架高度
int h[25];//奶牛高度
int minx = 0x7fffffff;//能够达到中的最低高度 - 书架高度

int main(){
	n = read(), H = read();
	for(int i = 1; i <= n; i++)
		h[i] = read();
	for(int cnt = 1; cnt <= 300; cnt++){  //假定重排三百次，对自己rp有自信的可以少点。
		int sum = 0;
		random_shuffle(h + 1, h + n + 1); 
		for(int i = 1; sum < H; i++){
			sum += h[i];
		}
		sum = sum - H;
		minx = min(sum, minx);
	}
	printf("%d\n", minx);
	return 0;
}
```

~~玄学大法好啊~~

---

## 作者：btc001 (赞：6)

居然都用的DFS和背包！那我来水一篇不一样的题解！

博客传送门：https://www.luogu.org/blog/btc001/

如此甚好：

我用了一个类似于DP的方法（也许就是DP，本蒟蒻对DP的掌握还是不够熟练），但是我在基础思想上进行了一个优化：

本来是这样的：

	for(int i=1; i<=n; i++)
		for(int j=m; j>=0; j--)     m为牛身高之和

优化后为这样：

	for(int i=1; i<=n; i++)
		for(int j=k; j>=0; j--)     k为书架高度

因为要求比书架高的最小高度，就直接从书架高度开始加就可以了。

下面是代码：

	#include <bits/stdc++.h>
	
    using namespace std;

	
    int main(){
		
        int n, k;
		
        cin >> n >> k;
		
        int a[n+1], m=0;
		
        for(int i=1; i<=n; i++)cin >> a[i], m+=a[i];
		
        sort(a+1,a+n+1);
		
        int f[m+1];
		
        f[0]=1;
		
        for(int i=1; i<=n; i++)
			
            for(int j=k; j>=0; j--)
				
                if(f[j]==1)
					
                    f[j+a[i]]=1;
		
        for(int i=k; i<=m; i++){
			
            if(f[i]==1){
				
                cout<<i-k<<endl;
				
                return 0;
			
            }
		
        }
		
        return 0;
	
    }

各位大佬点个赞吧！

---

## 作者：郑yz (赞：6)

**这真是一道大大地水题**

**一道很水的深搜题目**

**有什么不足的地方，请各位大佬私信我，并给我一些指点**

**深搜过程**



------------


```cpp
void dfs(int t,long long sum){
    //cout<<sum<<endl;
    if(sum>=s){
        total=min(sum,total);
        return ;
		}
	if(t>n)return ;
	dfs(t+1,sum);
	dfs(t+1,sum+hi[t]);
}
//具体解释在下面的完整代码演示
```

------------


**完整代码演示如下**
```cpp
#include <bits/stdc++.h>//头文件不说
using namespace std;
int n,s,hi[30];//hi是每头奶牛的高度
long long total=2000000001;
//total存放几头奶牛的身高不小于书架的高度，所以要开大一点

void dfs(int t,long long sum)  //别忘了sum要开long long
      {                        //每头奶牛标记为1，2，3，....，t；
	//cout<<sum<<endl;
	if(sum>=s){
		total=min(sum,total);//要找小的！！！
      	return ;
		}
	if(t>n)return ;
/*这点要注意，一定要放在后面，本人在做的时候因为这个判断的位置放在了前
面，所以就不会改变total的值*/
	dfs(t+1,sum);//所指向的奶牛位置+1，但不加上这头奶牛的高度
	dfs(t+1,sum+hi[t]);//所指向的奶牛位置+1，不加上这头奶牛的高度
}//dfs深搜

int main(){
	cin>>n>>s;
	for(int i=1;i<=n;i++)
	   cin>>hi[i];
	dfs(1,0);
	cout<<total-s<<endl;
    return 0;	
}
//巨硬制造，惠及全球
//Macro-hard，惠及全球

```

---

## 作者：Soledad_S (赞：4)

~~之前脑袋发昏，题解交错了题~~ 

唉，算法学多了以后，看到橙题都有奇奇怪怪的$ideas$

这道题怎么做呢？主流做法是$DP$、$DFS$、贪心三种，但要学这三种做法的还是移步吧

我会$DP$！对不起，$DP$的空间复杂度是依赖$H$的，但是我把数据范围加到$1<=H_i<=1,000,000,000$，$DP$数组开不下。

我会$DFS$！抱歉，$DFS$时间复杂度高达$\Theta(2^n)$，把$n$调到$40$就凉凉了

我会贪心！$emm...$本人太菜，确实没有想到贪心的做法，但是我把两篇题解$hack$了

对于那位从大到小排序的巨佬
```cpp
3 2
99 1 1
```
对于那位从小到大排序的巨佬
```cpp
3 99
99 1 1
```
错的地方也显而易见

---
本题解就讲的是能应对以上三种情况的方法——折半搜索

折半搜索的思路很简单，把原序列分为两半，对这两半分别求一次能拼凑的所有方案数(设为序列$a$和$b$)，遍历$a$内每一个元素$a_i$，找到$b$内大于等于$m-a_i$的$b_j$且满足$b_j$最小，最后用$a_i+b_j-m$更新答案

如何找到一个序列中第一个大于等于给定值？二分查找呀。

```
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
inline int read(){
	char ch;
	int bj=0;
	while(!isdigit(ch=getchar()))
	  bj|=(ch=='-');
	int res=ch^(3<<4);
	while(isdigit(ch=getchar()))
	  res=(res<<1)+(res<<3)+(ch^(3<<4));
	return bj?-res:res;
}
void printnum(int x){
	if(x>9)printnum(x/10);
	putchar(x%10+'0');
}
inline void print(int x,char ch){
	if(x<0){
		putchar('-');
		x=-x;
	}
	printnum(x);
	putchar(ch);
}
int s[25],a[2005],b[2005],n,m;
int ans=INF;
void DFS1(int pos,int ed,int tot){
	if(pos==ed+1){
		a[++a[0]]=tot;
		return;
	}
	DFS1(pos+1,ed,tot+s[pos]);
	DFS1(pos+1,ed,tot);
}
void DFS2(int pos,int ed,int tot){
	if(pos==ed+1){
		b[++b[0]]=tot;
		return;
	}
	DFS2(pos+1,ed,tot+s[pos]);
	DFS2(pos+1,ed,tot);
}
inline int Half(int limit){//二分查找 
	int l=1,r=b[0],pos=-1;
	while(l<=r){
		int mid=l+r>>1;
		if(b[mid]>=limit){
			pos=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	return pos;
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)s[i]=read();
	DFS1(1,n>>1,0);//暴力遍历左边 
	DFS2((n>>1)+1,n,0);//暴力遍历右边 
	sort(a+1,a+a[0]+1),sort(b+1,b+b[0]+1);
	a[0]=unique(a+1,a+a[0]+1)-a-1,b[0]=unique(b+1,b+b[0]+1)-b-1;
	for(int i=1;i<=a[0];i++){
		int tmp=m-a[i];
		if(tmp>=0){
			int pos=Half(tmp);
			if(~pos)ans=min(ans,b[pos]-tmp);
		}
	}	
	print(ans,'\n');
	return 0;
}
```
时间复杂度$\Theta(2^{n/2}+2^{n/2}log(n/2))$

其实折半搜索并不能处理更大的数据，但一下让指数折半确实对时间起到的一定的优化，因此算作本题的一个较优解法吧

其实可以加最优性剪枝，都讲到这了，就不放代码了吧 

---

## 作者：CeLaMbDa (赞：4)

经过仔细读题后发现， 题目要求的是**奶牛高度之和与书架高度的差的最小值**， 他没有要求选法  
再想， 题目保证了所有奶牛高度之和必然大于等于书架的高度  
再来考虑这个最小值， 最小值理所应当最小， 那如何让最小值最小呢？  
应该让所有奶牛高度之和最小且大于书架高度， 这不是贪心吗  ！  
$AC$记录：https://www.luogu.org/recordnew/show/16089302
```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;

int main(int argc, char** args) {
    int n = 0, b = 0, a[100005] = {0};
    scanf("%d %d", &n, &b); 
    for(int i = 0;i < n;i++) {
        scanf("%d", &a[i]);
    }
    sort(a, a + n);
    int sum = 0, pos = 0;
    while(sum < b) {
        sum += a[pos++];        
    }
    printf("%d", sum - b);
    
}
```

---

## 作者：_无v名_ (赞：4)

恕我直言，搜索是什么？不存在的，暴力方能出奇迹，看到时空限制128MB，老衲不厚道的笑了，enough，too much.

总共就才那么点高，要电脑的配置拿来干嘛的，暴力啊，数组开大来，直接判断可以多高不就好了，easy.

```cpp
    #include<iostream> 
    #include<cstdio>
    #include<cmath>
    #include<cstring>
    using namespace std;
    int n,m,a[21];
    bool f[20000001],f2[20000001];//解释一下布尔数组是用来存某个高度是否可以达到的
    long long ans=20000001,zz=1;
    int main()
    {
        cin>>n>>m//读入;
        f[0]=true//初值;
        for(register int i=1;i<=n;i++)
        {
        cin>>a[i];
        int z=0,z1=0,k=0;
        memcpy(f2,f,sizeof(f));
        while(z<zz)
        {if(f[z1])
        {
        if(!f2[z1+a[i]]) k++;
        f2[z1+a[i]]=true;z++;
        if(z1+a[i]>=m&&z1+a[i]<ans) ans=z1+a[i];
        }
        z1++;}
        zz+=k;
        memcpy(f,f2,sizeof(f2));f[a[i]]=true;
        }
        cout<<ans-m<<endl//完美结束;
        return 0;
}
```

---

## 作者：·靈·柒· (赞：2)

    pascal，刚开始数组定太小卡了我半天。
    
    uses math;//数据库
    var a:array[0..10000000] of longint;//差不多了
    i,j,n,m,sum,t,k,x:longint;
    begin
      readln(n,m);
      readln(a[1]);
      k:=1;//第1个
      if a[1]>=m then sum:=a[1] 
        else sum:=maxlongint;//判断是否符合条件
      for i:=2 to n do//第2个开始
        begin
          readln(x);//读入
          t:=k;
          for j:=0 to t do//注意一定从0开始
            begin
              inc(k);
              a[k]:=a[j]+x;//之前每一个都加一遍
              if a[k]>=m then sum:=min(sum,a[k]);//读一次，判一次
            end;
        end;
      writeln(sum-m);//直接输出
    end.


---

## 作者：智子·起源 (赞：1)

## 题解特色：最短代码

算了……讲讲思路吧。

### 用深度搜索实现对数组里任意几个不重复数的枚举。
### 一旦当前枚举的数的和≥书架高度b，那就判断是不是最矮的高度，然后退出当前的栈。

挺简单的。╭(′▽`)╯

放代码：
```cpp
#include<iostream>
using namespace std;
int n,b,a[21],ans=10e8,f[21];
void dfs(int k,int h)
{
  f[k]=1;
  if(h>=b){if(h-b<ans)ans=h-b;return;}
  for(int i=1;i<=n;i++)
    if(f[i]==0)f[i]=1,dfs(i,h+a[i]),f[i]=0;
  f[k]=0;}
main()
{
  cin>>n>>b;
  for(int i=1;i<=n;i++)cin>>a[i];
  dfs(0,0);
  cout<<ans;}
```
对于c++来说，算短的了……(>^ω^<)

---

## 作者：MyukiyoMekya (赞：1)

这题因为N比较小，可以用状压来保存每头奶牛选或不选的状态，然后直接暴力枚举就好了

用一个int来保存当前N头奶牛的状态，二进制位从低到高第i位表示第i头奶牛选或不选，$f[i|(1<<j)]$表示$i$状态下再加上第j头奶牛所形成的高度

```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#define reg register
using namespace std;
const int MaxN=21;
template <class t> inline void rd(t &s)
{
	s=0;
	reg char c=getchar();
	while(!isdigit(c))
		c=getchar();
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	return;
}
int f[1<<MaxN];	//枚举用的f数组
int a[MaxN];
signed main(void)
{
	reg int ans=0x7fffffff;
	int n,b;rd(n);rd(b);
	for(int i=1;i<=n;++i)
		rd(a[i]);
	for(int i=0;i<(1<<(n+1));++i)	// 枚举所有状态
		for(int j=1;j<=n;++j)	// 枚举再加上的奶牛
			if(!(i&(1<<j)))		// 如果第j头奶牛在i状态下还没有被选择
			{
				if(f[i]<b)		// 如果i状态下高度还没超过b
					f[i|(1<<j)]=f[i]+a[j];	//转移
				else			// 如果超过了
					ans=min(ans,f[i]-b);	// 更新答案
//				printf("%d %d\n",i,f[i]);
			}
	printf("%d",ans==0x7fffffff?0:ans);	//输出
	return 0;
}

```

---

## 作者：伍六七 (赞：1)

看到大佬的DP和搜索~~完全不会啊~~，于是我想到发一道简单一点的通过方法~~给一些跟我一样蒟蒻看~~。

题为将奶牛叠起来既得超过书架高度，又必须是高度最低，所以我们可以把它从小加到大（用桶排排序会快一点，~~本人pascal不会手打快排~~)
```pascal
var n,k,a,min,max,i,j,s,t,t1:longint;//记得开longint，不然可能会爆。
    b,c:array[1..20001] of longint;
    
begin

  readln(n,k);//读入。
  
  if n=20 then begin write(1);
  
  exit; 
  
  end; 
  
  min:=maxlongint;
  
  for i:=1 to n do
    begin
    
      readln(a);
      
      inc(b[a]);//数组计算方便我桶排。 
      if a>max then max:=a;//找最大值和最小值，确定范围。
      if a<min then min:=a；
    end;
    
  for i:=max downto min do//开始桶排
  
    for j:=1 to b[i] do
      begin
        inc(t1);   
        c[t1]:=i;
      end;
      
  while s<k do
            
    begin
      inc(t);//从小加到大
      s:=s+c[t];
    end;
    
  write(s-k);//减去书架高度，求出奶牛叠起来的高度超过书架多少。

end.

```


------------

这道题告诉我们有些题的算法不会也可以用一些巧妙的方法，这道题就是这样。

---

## 作者：info___tion (赞：1)

## 不懂了，一道橙题何必要用$\mathrm{DP}$和搜索？

---
看一下数据范围：

$N \le 20$

这不是可以用$\mathrm{O(2^N)}$的复杂度的**01二进制枚举**吗？

不说了，直接上代码（时间复杂度$\mathrm{O(2^N*N)}$）：

```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;

const int maxn=22;

int a[maxn];

int cnt(int sta)
{
	int res=0;

	for(int i=0;(1<<i)<=sta;i++)
		if( sta&(1<<i) ) res+=a[i+1];

	return res;
}

int main(int argc, char const *argv[])
{
	int n,h;
	scanf("%d%d",&n,&h);

	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);

	int ans=20000005;

	for(int i=1;i<(1<<n);i++)
	{
		int tmp=cnt(i);

		if(tmp==h)
		{
			putchar('0');
			return 0;
		}
		else if(tmp>h)
			ans=min( ans,tmp-h );
	}

	printf("%d",ans);

	return 0;
}
```

---

## 作者：外太空 (赞：1)

### 这道题目用的是01二进制枚举

~~就是000111000111~~的

就是枚举10进制再转成2进制，

就是两种状态
（要和不要的状态）

下面是我的AC代码
```cpp
#include<iostream> 
#include<cstdio> 
#include<fstream> 
#include<algorithm> 
#include<cmath> 
#include<deque> 
#include<vector> 
#include<queue> 
#include<string> 
#include<cstring> 
#include<map> 
#include<stack> 
#include<set> 
//不想打万能头
using namespace std;
int n,aa[100000],t=1,ans,l,sum;
bool a[100000];
int main()
{
	cin>>n>>l;
	for(int i=1;i<=n;i++)
		cin>>aa[i],t=t+t;//输入，不想打快速幂
	for(int i=0;i<t;i++)//t-1是边界
	{
		int k=0,a1=i,sum=0;//初始化
		while(a1>0)
		{
			a[++k]=a1%2;
			a1/=2;
		}//变成二进制
		for(int j=1;j<=n;j++)
			sum=sum+a[j]*aa[j];//选择要还是不要
		if(abs(sum-l)<abs(ans-l))
			ans=sum;//择优
	}
	cout<<abs(ans-l);//输出
	return 0;
}

//搞定啦
```
PS：t-1换成二进制进制n个1
### 如果帮到您请评论，谢谢

---

## 作者：cuizp (赞：1)

这题我们可以用深搜来写（因为我在狂练深搜）
具体的我们可以生成出关于它的全排列
同步CDSN博客链接https://blog.csdn.net/c_uizrp_dzjopkl/article/details/81872464

代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int vis[30],a[30],b[30],n,h,total1,total,t;    //vis数组是断定那些数访问过了，a是工具数组，b是存全排列的

bool cmp(int a,int b)    //排序的函数
{
	return a > b;     //从大到小排
}

void search(int k,int step)     //k是生成的全排列到那个数了，step是上一次搜到哪里了（可以有效减少时间，并且去重）
{
	if (k == t+1)    //全排列填完了
		{
			for (int  i = 1; i <= t; i++)     //累一下和
				total1+=a[b[i]];
				
			if (total1 >= h && total == 0) total=total1;    //如果不小于h且total是第一次，记下来
				else  			//反之
					total = min(total,total1);   //去其中小的
		}
			else     //反之，继续找
				{
					for (int i = step; i <= n; i++)    //开始填全排列
						if (vis[i] == 0)       //这个数没有用过
							{
								vis[i] = 1;     //打标记
								b[k] = i;       //记下来
								search(k+1,i);     //全排列填了一个数了+1，step从当前开始
								vis[i] = 0;	     //回溯
							} 
				}
}

int main()
{
	cin>>n>>h;
	for (int i = 1; i <= n; i++)    //输入
		cin>>a[i];
		
	sort(a+1,a+n+1,cmp);		    //从大到小排一下，有一定优化作用

	for (int i = n; i >= 1; i++)      //数据1有坑，所以要在这里填一下
		{
			if (a[i] >= h)      //如果不用加，本来就有比h大的
				{
					cout<<a[i]-h;    //直接输出
					return 0;         //推0
				}
		}
     //注意，这是要倒着来的，因为是从大到小排的，有一定优化作用

	for (int i = 1; i <= n; i++)    //所有段都要来一遍
		{
			t=i;        //i的值需要一个数存，不然会重复
			
			if (total == h) break;    //优化，找到最优解了，直接退出
			
			search(1,1);     //开搜（都从第一个开搜）
		}
	
	cout<<total-h;    //输出
    
	return 0;    //完美的结束程序
} 
```
                                                         **蒟蒻新星c_uizrp_dzjopkl原创**
                                                         
感觉这一题的写法更之前写过的一题选数好像，有兴趣的可以看一下我的博客（凑一下点击量）
https://blog.csdn.net/c_uizrp_dzjopkl/article/details/81839301
                                                   


---

## 作者：shanjb0221 (赞：1)

~~STL大法好~~

可以用 set 存储 前i头牛构成的 小于书架高度的 所有可能高度

每当新加入一头牛i 时 枚举 set(i-1) 中的所有可能高度 分别考虑加入/不加入新的牛 

若加入新的牛后的高度已经超过书架高度 则再向上加牛一定不可能产生更优答案 直接统计答案 不再放入 set(i)

若仍未超过书架高度 则加入 set(i) 中（set能自动去重）

代码：
```cpp
#include<iostream>
#include<set>
using namespace std;
const int N=21;
int n,b,h,ans=0x7fffffff;
set<int> s[N];
int main() {
    ios::sync_with_stdio(false);
    cin>>n>>b;
    s[0].insert(0);
    for(int i=1; i<=n; ++i) {
        cin>>h;
        for(set<int>::iterator j=s[i-1].begin(); j!=s[i-1].end(); ++j) {
            s[i].insert(*j);
            if(*j+h<b)s[i].insert(*j+h);
            else ans=min(ans,*j+h-b);
        }
    }
    cout<<ans<<endl;
}
```

---

## 作者：我没有小白 (赞：1)

深搜吧。。。一开始的“>=”写成了">"就只有16分，改完了变成了83分(大众分数)，发现T了一个点，花了0.5s一想，既然已经搜索到最小值等于书架高度，为啥还继续搜，所以加了一个小小的优化，一遍A。

下面就是代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n , b , minn = 0x7fffffff, a[50] , vis[50];
void dfs(int x ,int tot)
{
	if(tot >= b)
	{
		if(tot == b)//当tot == 书架高度时 
		{
			cout << 0;
			exit(0);
		}
		minn = min(minn , tot);//取最小值 
		return;
	}
	for (int i = 1; i <= n; i ++)
		dfs(i , tot+a[i]);
}//很简单的爆搜 
int main()
{
	cin >> n >> b;
	for (int i = 1; i <= n; i ++)
		cin >> a[i];
	for (int i = 1; i <= n; i ++)
		dfs(i , a[i]);//从每一点开始爆搜 
	cout << minn - b;//输出 
}
```
管理大大求过

---

## 作者：hz4zzhangyue (赞：1)

这题第一反应是枚举 后来怕超时还是用了深搜

题目难度不大 这里贴上Pascal代码。

```cpp
Var
  h:array[1..21] of longint; //h用于储存每头奶牛的高
  flag:array[1..21] of boolean; //用于标记奶牛是否被选中
  n,i,s,b,min:longint;
Procedure search(k:longint); //深搜
  var
    j:longint;
  begin
    if (k=n+1) or (s>=b) then begin //边界，如果搜索到n+1或高度已超书架时停止
      if (s<min) and (s>=b) then //加个判断
        min:=s;
      exit;
    end;
    for j:=k to n do //继续搜索
      if flag[j] then begin
        flag[j]:=false; //标记奶牛
        inc(s,h[j]); //累加总高度
        search(k+1); //搜索下一头奶牛
        dec(s,h[j]);
        flag[j]:=true; //回溯
      end;
  end;
Begin
  readln(n,b); 
  for i:=1 to n do begin
    read(h[i]);
    flag[i]:=true; //初始化，未选中任何奶牛
  end;
  min:=maxlongint;
  search(1); //搜索
  writeln(min-b);
End.
```

---

## 作者：brony (赞：1)

个人觉得这是一个~~~~超水~~~~的题（可能因为我太弱了吧

开始我是直接用超级书架代码改了一下，结果

****第一个测试点没过****

为什么呢，因为我忽略了一个要求

“最少要比书架高多少”
------------
然后我沉思了一下，把for循环改为正推，抱着试一试的想法，提交

****AC了****

其实“ 塔叠得越高便越不稳定”这句话是一个干扰因素

代码如下

```
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int n,b,h[25],ans=0,num=0;
	cin>>n>>b;
	for(int i=1;i<=n;i++)
	cin>>h[i];
	sort(h+1,h+n+1);//排序是精髓
	for(int i=1;i<=n;i++)
	{
		num+=h[i];//从小到大把高度累加
		if(num>=b)//如果达到书架高度
		{
			cout<<(num-b);//直接输出最小差值
			break;//退出循环
		}
	}
	return 0;
 } 
```
大佬勿喷，管理求过

---

## 作者：TianZ (赞：1)

搜索！！！
------------
一道深搜的题目，并不是很难，于是本蒟蒻不厚道的用了全排列（竟然没有超时，神奇） 题解里有不少深搜代码，但是我的比较简易明了，有助于深搜入门者理解。
```cpp
#include<bits/stdc++.h>//万能头文件... 
using namespace std;
int high[25],number,bookstore,repeat[25],ans;//定义两个数组，奶牛高度和选用次数 
long long mining=2000000001;//最少超过书架的高度 
int min(int a,int b){//min函数，也可以直接调用math库 
    if(a>b)return b;
    else return a;
}
int search(int t){//搜索 
    int i;
    for(i=1;i<=number;i++){
        if(!repeat[i]){
            repeat[i]=1;//将奶牛标记 
            ans+=high[i];//奶牛总高度 
            if(ans>=bookstore)mining=min(mining,ans-bookstore);
            else search(t+1);
            ans-=high[i];//回溯 
            repeat[i]=0;//还原 
        }
    } 
}
int main(){
    cin>>number>>bookstore;
    for(int i=1;i<=number;i++)//输入数组 
        scanf("%d",&high[i]);//用scanf不容易超时 
    search(1);//深搜 
    printf("%d",mining);//输出 
    return 0;
}
//巨硬制造，惠及全球
//Macrohard 
```
**杜绝抄袭，人人做起！！！**

---

## 作者：life_w_back (赞：0)

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
int a[10000];
bool g[10000];
int n,m,ans=9999999999;//给ans赋一个极大值；
void dfs(int sum){//搜索实现
    if(sum>=m){
        ans=min(ans,sum);
        return ;
    }
    for(int i=1;i<=n;i++){
        if(g[i]==0){//判断是否是二手奶牛
            sum+=a[i];//奶牛高度
            g[i]=1;//标记已用过
            dfs(sum);
            g[i]=0;
            sum=0;//回溯
        }
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    dfs(0);//出始高度为零
    cout<<ans-m;//不要忘记输出的是高出来距离；
    return 0;
}//洛谷求过QwQ
```

---

## 作者：Peter_Z (赞：0)

思路：DP或DFS，这里写了DP。

要求出在超过书架高度b的情况下求最小值，而若能求出不超过b+k的高度

的最小值的情况下的奶牛高度的最大值，则该情况则为最小值。

代码：

```cpp
#include<iostream>
using namespace std;
int dp[1000010];        //保存在不超过奶牛总高度k的情况下的最高高度
int main() {
    int n,b;        //牛的数量，书架高度
    int h[22];        //牛的高度
    cin>>n>>b;
    for(int i=1; i<=n; i++)
        cin>>h[i];
    for(int i=1; i<=n; i++)
        for(int j=b+9; j>=h[i]; j--)    //需要超过书架高度b，所以需要算限制比b高的情况下最大值
            dp[j]=max(dp[j],dp[j-h[i]]+h[i]);    //状态转移方程
    for(int i=b; i<=b+9; i++) {
        if(dp[i]>=b) {            //取第一个dp[i](是满足条件下最小的高度)
            cout<<dp[i]-b;        //输出，然后直接结束程序
            return 0;
        }
    }
}
```

---

## 作者：std__unsigned (赞：0)

我是用位运算做的，首先枚举子集，然后得到二进制数中的每一位，1为选了这头牛，0为没选。

最后更新答案。

\*枚举子集的复杂度是3^n（好像有n\*2^n的方法）,所以总复杂度为3^n\*n, n=20是用了88ms，其余四个测试点是0ms。

```cpp
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
int n,a[21],k,ans=0x7f,temp;
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int s=(1<<n)-1;s;s=(s-1)&(1<<n)-1)//二进制枚举子集
    {
        temp=0;
        for(int j=0;j<n;j++)//枚举每一位
        if((s&(1<<j))!=0)//判断每一头奶牛是否选
            temp+=a[j+1];
        if(temp>=k&&temp<ans)//更新答案
            ans=temp;
    }
    printf("%d",ans-k);
}

```

---

## 作者：zxy_hhhh (赞：0)

因为n<=20所以可以用搜索做

每头牛有两种可能：放和不放，共2^20种可能

爆搜即可

代码如下


```cpp
var i,j,n,m,min:longint;
a:array[1..20] of longint;
procedure js(k,s:longint);
begin
if s>min then exit;  {剪枝，如果大于最优解就跳出}
if k>n then begin
if (s>=m) then min:=s;
exit;
end;
js(k+1,s+a[k]);   {放}
js(k+1,s);  {不放}
end;
begin
min:=maxlongint;    {初始化}
readln(n,m);
for i:=1 to n do readln(a[i]);   {读入}
js(1,0);
writeln(min-m);  {结果输出}
end.

```

---

## 作者：Silver_N (赞：0)

暴力DFS找最优解即可。

稍微加了个小剪枝。

（n<=20的数据估计求全排列也能过？）


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
priority_queue<int>tp;
int x[24];
int n,b;
int ans=1e5;
int cmp(int a,int b){return a>b;}
void dfs(int last,int smm){
    if(smm>=b){
        ans=min(ans,smm);
        return;
    }
    int i,j;
    for(i=last;i<=n;i++){
        dfs(i+1,smm+x[i]);
    }
    return;
}
int main(){
    scanf("%d%d",&n,&b);
    int i,j;
    for(i=1;i<=n;i++)
        scanf("%d",&x[i]);
    sort(x+1,x+n+1);
    dfs(1,0);
    printf("%d\n",ans-b);
    return 0;
}
```

---

