# NASA的食物计划

## 题目背景

NASA（美国航空航天局）因为航天飞机的隔热瓦等其他安全技术问题一直大伤脑筋，因此在各方压力下终止了航天飞机的历史，但是此类事情会不会在以后发生，谁也无法保证。所以，在遇到这类航天问题时，也许只能让航天员出仓维修。但是过多的维修会消耗航天员大量的能量，因此 NASA 便想设计一种食品方案，使体积和承重有限的条件下多装载一些高卡路里的食物。

## 题目描述

航天飞机的体积有限，当然如果载过重的物品，燃料会浪费很多钱，每件食品都有各自的体积、质量以及所含卡路里。在告诉你体积和质量的最大值的情况下，请输出能达到的食品方案所含卡路里的最大值，当然每个食品只能使用一次。

## 说明/提示

对于 $100\%$ 的数据，$h,t,h_i,t_i \le 400$，$n \le 50$，$k_i \le 500$。

## 样例 #1

### 输入

```
320 350
4
160 40 120
80 110 240
220 70 310
40 400 220
```

### 输出

```
550
```

# 题解

## 作者：龘龘龘龘龘龘 (赞：157)

//这一题和01背包大径相同，只要考虑清楚其中的关系，直接就可以套用01背包中f[j]=max{f[j],f[j-a[i]]+c[i]然后因为有两个关键变量所以设一个二维数组f[j][l];然后f[l]也可以直接套用上面那个公式，只要稍微变动一下就行了，这就不说了；

鄙人是个新手昨晚8.00才正式学背包，代码有点不清楚的请多多包涵；

以下是代码，请各位笑纳：

```cpp
#include<iostream>
using namespace std;
int a[51],b[51],c[51];//题目中有三个变量就设三个变量；
int f[501][501];
int main()
{
    int i,j,l,m,n,k;
    cin>>m>>n>>k;//输入
    for(i=1;i<=k;i++)
      cin>>a[i]>>b[i]>>c[i];//表示每个食品的体积质量和卡路里；
    for(i=1;i<=k;i++)
      for(j=m;j>=a[i];j--)
        for(l=n;l>=b[i];l--)//记住j和l不能同时写在一起，刚开始我就写在一起，调了1分钟才发现
          f[j][l]=max(f[j][l],f[j-a[i]][l-b[i]]+c[i]);//公式；直接套用就是的
      cout<<f[m][n];//输出最优解
      return 0;
}
```

---

## 作者：zhz小蒟蒻 (赞：45)

嗯，本蒟蒻也是在练习背包问题时找到了这题，~~做的过程中还辅助了书~~，好，切入正题  
这道题其实一眼就可以看出，这只是在普通的01背包问题多加了一维,嗯，先呈上01背包问题公式——设f[i][j]为前i个物品中放入容量为j的背包的最优值，则状态转移方程为f[i][j]=max(f[i-1][j],f[i-1][j-w[i]+c[i])  
注:w[i]为重量，c[i]为其代表的价值,整个方程的意思是,从前i-1个物品中放入容量为j的背包的最优值(不包括第i-1个物品)和前i-1个物品中放入第i-1个物品的最大值。  
一般01背包代码:(不压缩成一维)  
```
#include <iostream>//这是以采药为样例
#include <cstdio>
using namespace std;
int main()
{
	int f[1001][1001]={0};
	int a[101],b[101];  
	int i,j,k,n,m,t;
	cin>>t>>n;
	for(i=1;i<=n;i++)
		cin>>a[i]>>b[i];
	for(i=1;i<=n;i++)
	{
		for(j=t;j>=0;j--)
		{
			if(j>=a[i]) f[i][j]=max(f[i-1][j],f[i-1][j-a[i]]+b[i]);
			else f[i][j]=f[i-1][j];
		}
	}
	printf("%d",f[n][t]);
	return 0;
}
```  
我们再来看到本题，因为这是二维的，所以我们设f[i][j][k]为前i个物品中放入体积为j，质量为k的背包的最优值,则只需将01背包的方程做稍微的修改  
f[i][j][k]=max(f[i-1][j][k],f[i-1][j-w[i]][k-z[i]]+c[i]);  
好了，看到这里，你应该会做了吧(当然，像本蒟蒻一样的人除外)
先去试着做一下，不会做，再来看代码:
```
#include <iostream>
#include <cstdio>
using namespace std;
int dp[51][401][401];  //因为我太弱了，不会节省空间
int main()
{
	int w[501],z[501],c[501];
	int i,j,k,n,u,v;
	scanf("%d %d %d",&u,&v,&n);
	for(i=1;i<=n;i++)
		scanf("%d %d %d",&w[i],&z[i],&c[i]);//w数组为体积，z数组为重量,c数组为卡路里
	for(i=1;i<=n;i++)
	{
		for(j=u;j>0;j--)
		{
			for(k=v;k>0;k--)
			{
				if(j>=w[i] && k>=z[i])  //如果j和k大于w[i]和z[i]，判断是前i-1个物品的最优值大，还是加上第i-1个数大
					dp[i][j][k]=max(dp[i-1][j][k],dp[i-1][j-w[i]][k-z[i]]+c[i]);
				else  //如果小了，dp[i][j][k]等于前i-1个数的最优值
					dp[i][j][k]=dp[i-1][j][k];
			}
		}
	}
	printf("%d",dp[n][u][v]); //这个绝对是最大值
	return 0;//一定要记得打return 0，这是个好习惯
}
```

---

## 作者：_maze (赞：20)

本蒟蒻刚学完01背包（今天下午），可是还是感觉不太懂思想，于是老师推荐这道~~水~~题来做一做

好了进入正题，我们学过了01背包，知道了01背包的精髓就在于抉择选还是不选。

```cpp
//重点代码
for(int i=1;i<=n;i++){//n为有多少个物品
	for(int j=v;j>=0;j--){//v为最大容量
		if(j>=a[i]) dp[i][j]=max(dp[i-1][j],dp[i-1][j-a[i]]+b[i]);//选或不选
		else dp[i][j]=dp[i-1][j];//小了就一定不选
	}
}
```

接着我们还学了01背包如何降维，利用滚动数组来存储即可

这道题显然要定义一个二维数组dp[i][j]，首先我们必须明白dp[i][j]的含义

这里不但有空间的限制，还有质量的限制，所以dp[i][j]很显然定义为质量为i空间为j时的最大值

接着我们要找出状态转移方程

状态转移很显然01背包标准版的方程再改一下就可以了

```cpp
dp[j][t]=max(dp[j][t],dp[j-a[i]][t-b[i]]+c[i]);
```

最后，这里有三个参数，就要三重循环

上代码：

```cpp
#include<bits/stdc++.h>
#define chengxiaoke is so cute
using namespace std;
int dp[1001][1001],v,n,a[1001],b[1001],c[1001],k;
int main()
{
	cin>>v>>n>>k;//v体积，n质量，k个数
	for(int i=1;i<=k;i++) cin>>a[i]>>b[i]>>c[i];//输入
	for(int i=1;i<=n;i++) for(int j=v;j>=a[i];j--) for(int t=n;t>=b[i];t--) dp[j][t]=max(dp[j][t],dp[j-a[i]][t-b[i]]+c[i]);//状态转移方程
	cout<<dp[v][n];//输出
	return 0;//完美结束
}

```
~~我就是个压行狂人啊……~~

---

## 作者：juruo_zjc (赞：17)

# 像我这样的蒟蒻往这儿看！

这道题很简单，特别是题目最下方说明中点明这是一道背包题，更是削弱了这道题的难度。


------------
好了言归正传，先定义dp[i][j][k]为取到第i个，花费j体积，k质量得到的最大卡路里。方程和二维的一样，只是多了一个质量。


------------
当这个物品能取时，也就是j>=v[i]&&k>=w[i]时


------------

f[i][j][k]=max(f[i-1][j][k],f[i-1][j-v[i]][k-w[i]]);


------------

否则


------------
f[i][j][k]=f[i-1][j][k];


------------
否则的情况不加会出错，自己想想为什么。程序如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int V,W,K,n,v[524],w[524],kl[524],dp[52][52][52];
int main()
{
	cin>>V>>W>>n;
	for(int i=1;i<=n;i++)scanf("%d%d%d",&v[i],&w[i],&kl[i]);
	for(int i=1;i<=n;i++){
		for(int j=V;j>=0;j--){
			for(int k=W;k>=0;k--){
				if(j>=v[i]&&k>=w[i])
					dp[i][j][k]=max(dp[i-1][j][k],dp[i-1][j-v[i]][k-w[i]]+kl[i]);
				else dp[i][j][k]=dp[i-1][j][k];
			}
		}
	}
	cout<<dp[n][V][W];
	return 0;
}
```


------------
好了，前面的就是用了三维的背包，本题数据较弱，n<50，不会爆空间，但是万一n<1000就凉凉了！于是我们就要思考如何优化空间。


------------
其实和普通背包一样，只要反着推，就可以了。


------------
方程就是：f[j][k]=max(f[j][k],f[j-v[i]][k-w[i]]);
程序如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int V,W,K,n,v[524],w[524],kl[524],dp[524][524];
int main()
{
	cin>>V>>W>>n;
	for(int i=1;i<=n;i++)scanf("%d%d%d",&v[i],&w[i],&kl[i]);
	for(int i=1;i<=n;i++){
		for(int j=V;j>=v[i];j--){
			for(int k=W;k>=w[i];k--){
				dp[j][k]=max(dp[j][k],dp[j-v[i]][k-w[i]]+kl[i]);
			}
		}
	}
	cout<<dp[V][W];
	return 0;
}
```


---

## 作者：hmh13951417981 (赞：13)

# 普通的 01背包问题
# 只是有两个限定条件（体积和质量）
------------

```c
#include<bits/stdc++.h>
using namespace std;
int t[51],z[51],k[51],f[401][401],i,j,l;
//因为要包含两个条件，所以f数组开成二维，前一个下标指体积，后一个指质量
int main()
{	int tj,zl,n;//分别表示体积，质量和总数（很好理解的变量名）
	cin>>tj>>zl>>n;
	for(i=1;i<=n;i++)
		cin>>t[i]>>z[i]>>k[i];//输入体（积），质（量），卡（路里）
	for(i=1;i<=zl;i++)	   //把每个物体选或不选都循环过去
		for(j=tj;j>=t[i];j--)//j表示体积
			for(l=zl;l>=z[i];l--){//l表示重量
				f[j][l]=max(f[j][l],f[j-t[i]][l-z[i]]+k[i]);
                //后面一个量指选了以后，是总体积减去它的体积，
                //总质量减去它的质量时背包的最大卡路里加上它的卡路里
			}
	cout<<f[tj][zl];//输出体积为tj,质量为zl时背包的最大卡路里
	return 0;
}
```

---

## 作者：critnos (赞：10)

# 暴力枚举哪家强，（后面的请自行脑补）
# 谁说背包只能用dp？
~~我不会告诉你是因为我不会~~

当我看到N<50时，我笑了

对于普及-的题目来说，大部分用暴力都能过

暴力和dp的不同之处（除了效率）在于：~~少消耗一些脑细胞~~条件越多暴力的效率越高，因为只要有一个条件不满足就可以停止这个递归（当然，暴力还得用dfs）

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,z,n,mx;
int tj[55],zl[55],k[55]; 
inline void dfs(int st,int sz,int sk,int d)
{
	if(st>t||sz>z) return;
	if(d==n)
	{
		mx=max(mx,sk);
		return;
	}
	dfs(st+tj[d],sz+zl[d],sk+k[d],d+1);
	dfs(st,sz,sk,d+1);
}
int main()
{
    cin>>t>>z>>n;
    for(int i=0;i<n;i++) cin>>tj[i]>>zl[i]>>k[i];
    dfs(0,0,0,0);
    cout<<mx;
}
```
思路~~其实没什么好讲的~~：枚举所有情况，就是第一个拿，不拿，第二个拿，不拿......

当然，这样会超时，所以在每次都判断一下是否超出范围就可以愉快的AC啦

---

## 作者：sunshine：） (赞：8)

其实这道**二维的01背包**就OK了，千万不要想多了。

两个条件一起上！！！GO ON!

想当年，那可都是pascal猿( ⊙ o ⊙ )啊！！！

相信我，01背包会了，这**个so easy!**


```cpp
uses math;  //调用函数库，方便后面的max函数
var
  x,y,z,l,n,i,j,v,k:longint; 
  f:array[0..400,0..400] of longint;
begin
  readln(v,l);
  readln(n);
  for i:=1 to n do
    begin
      readln(x,y,z);
      for j:=v downto x do
        for k:=l downto y do
          f[j,k]:=max(f[j,k],f[j-x,k-y]+z);
    end;
  writeln(f[v,l]);
end.
```

---

## 作者：Skyjoy (赞：6)

# 这是一道变异的01背包

dp初学者最先学的就是01背包，而这道题虽然从体积限制的基础上多了质量限制，但只要略微思考，就会发现dp数组从1维变成2维再套板子就行了。1维转移公式是$f[j]=max(f[j],f[j-v[i]]+w[i])$，2维就是$f[j][l]=max(f[j][l],f[j-v[i]][l-m[i]]+w[i])$

# 接下来就是代码环节了（111ms,1.29MB）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,v[60],m[60],c[60],f[410][410],V,M;//n不解释，v是体积，m是质量，c是卡路里 
int main(){
	cin>>V>>M>>n;
	for(int i=1;i<=n;i++){
		cin>>v[i]>>m[i]>>c[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=V;j>=v[i];j--){
			for(int l=M;l>=m[i];l--){
				f[j][l]=max(f[j][l],f[j-v[i]][l-m[i]]+c[i]);//变异的01背包 
			}
		}
	}
	cout<<f[V][M];
	return 0;
}
```

谢谢大家的观看，祝大家~~NOIp~~某信息联赛2019rp++！！！

---

## 作者：JCZhang (赞：6)

# 讲解


可以看我博客

[here](http://jczhang.top)

这道题是二维费用的背包问题


其实不难 但对蒟蒻来说很难啊


`qwq--qwq`


言归正传


开始讲题


二维费用的背包问题是指：对于每件物品，具有两种不同的费用；选择这件物品必须同时付出这两种代价；对于每种代价都有一个可付出的最大值（背包容量）。问怎样选择物品可以得到最大的价值。设这两种代价分别为代价1和代价2，第i件物品所需的两种代价分别为a[i]和b[i]。两种代价可付出的最大值（两种背包容量）分别为V和U。物品的价值为c[i]。


费用加了一维，只需状态也加一维即可。设fi[u]表示前i件物品付出两种代价分别为v和u时可获得的最大价值。


状态转移方程就是：`f[i][v][u]=max{f[i-1][v][u],f[i-1][v-a[i]][u-b[i]]+c[i]}`。如前述方法，可以只使用二维的数组：当每件物品只可以取一次时变量v和u采用逆序的循环，当物品有如完全背包问题时采用顺序的循环。当物品有如多重背包问题时拆分物品。


代码如下

```cpp
#include<iostream>
#define r register
auto max = [](const int x, const int y) {if (x > y) return x; else return y; };
const int maxn = 1001;
class bing
{
public:
    inline void get() {
        std::cin >> vi >> mi >> n;
        for (r int i = 1; i <= n; ++i)
            std::cin >> v[i] >> m[i] >> u[i];
    }
    inline void opera() {
        for(r int i=1;i<=n;++i)
            for(r int j=vi;j>=v[i];--j)
                for (r int k = mi; k >= m[i]; --k) {
                    f[j][k] = max(f[j][k], f[j - v[i]][k - m[i]] + u[i]);
                }
    }

    ~bing()
    {
        std::cout << f[vi][mi];
    }

private:
    int vi, mi, n;
    int f[maxn][maxn], v[maxn], m[maxn], u[maxn];
};
bing qyb;
int main() {
    qyb.get();
    qyb.opera();
    return 0;
}
```
首先 我写了一个   $λ  $ 函数，即max函数


状态转移方程:






`f[j][k] = max(f[j][k], f[j - v[i]][k - m[i]] + u[i])`



---

## 作者：兀pai (赞：5)

借着这次机会写一写对于背包我的一些理解，也希望大佬们及时更正

------------

## 一、动态规划

动态规划是求解决策过程最优化的数学方法，是指一种过程，并不算

是一类算法

动态规划一般可分为线性动规，区域动规，树形动规，背包动规四类，

本题和本题解都是关于背包问题展开的


------------


## 二、背包问题

背包问题又分01背包和完全背包，二者本质区别就是可以拿物体的次

数，在这里不做区分

#### 01背包：

有N件物品和一个容量为V的背包。第i件物品的体积是c[i]，价值是w[i]。

求解将哪些物品装入背包可使价值总和最大。


从这个题目中可以看出，01背包的特点就是：每种物品仅有一件，可以选择放或不放。

因为动态规划的核心就是要求出状态转移方程

#### 方法一

这里我们先给出状态转移方程  dp[i][j]=max(dp[i-1][j],dp[i-1][j-c[i]]+w[i])

i代表当前一共选择的物品总数量

j代表当前选择的物体总体积

dp[i-1][j]就代表我们之前i-1个物品全部选择

dp[i-1][j-c[i]]+w[i]就代表抛弃前面的不选，只选当前的这一个

而dp[i][j]就是存储当前物体的总价值

那dp[n][V]就是最终的答案，就是可以选择物体的最大重量

#### 方法二

看到前一个状态转移方程，大家是不是隐约有种说不上来多余的感觉？

那恭喜你，你的肝很发达

（是不是在想这跟肝有什么关系，其实我也不知道qwq（逃

那么我们还是先看状态转移方程：

dp[j]=max(dp[j],dp[j-c[i]]+w[i]

是不是爽了很多，因为[i-1]在两边都出现了，可以舍去

这就是01背包问题，是不是不算太难？那我们再来看题解

------------


## 题解

第一次看题我有点小蒙，这怎么会有三个数？？？（黑人疑惑脸）

仔细想了想原来很简单，只是背包问题多了一个条件，多一重循环就好

（用方法一的就设4重循环，用方法二的就舍3重循环，但我不确定4

重会不会爆）

下面来看一看代码
```cpp
#include<iostream>
using namespace std;
int mv,mm,n,v[401],m[401],k[401],dp[401][401];
int main()
```
没营养的前4行

**注意：开数组一定要看好题目，要不然开大了爆零，开小了不过**

```cpp
{
	cin>>mv>>mm>>n;
	for(int i=1;i<=n;i++)  cin>>v[i]>>m[i]>>k[i];
```
没营养的5-7行

```cpp
	for(int i=1;i<=n;i++){
		for(int j=mv;j>=v[i];j--){
			for(int p=mm;p>=m[i];p--){
				dp[j][p]=max(dp[j][p],dp[j-v[i]][p-m[i]]+k[i]);
			}
		}
	}
```
这才是核心代码，仔细看是不是和01背包差不多呢

```cpp
	cout<<dp[mv][mm];
	return 0;
}
```
又是没营养的15-17行

这是我们最爱的完整代码
```cpp
#include<iostream>
using namespace std;
int mv,mm,n,v[401],m[401],k[401],dp[401][401];
int main()
{
	cin>>mv>>mm>>n;
	for(int i=1;i<=n;i++)  cin>>v[i]>>m[i]>>k[i];
	for(int i=1;i<=n;i++){
		for(int j=mv;j>=v[i];j--){
			for(int p=mm;p>=m[i];p--){
				dp[j][p]=max(dp[j][p],dp[j-v[i]][p-m[i]]+k[i]);
			}
		}
	}
	cout<<dp[mv][mm];
	return 0;
}
```
------------

## 友情链接：

dd大神的背包九讲 [https://www.cnblogs.com/jbelial/articles/2116074.html](https://www.cnblogs.com/jbelial/articles/2116074.html)

动态规划部分来自百度
[https://baike.baidu.com/item/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92/529408?fr=aladdin](https://baike.baidu.com/item/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92/529408?fr=aladdin)

百度：01背包
[https://baike.baidu.com/item/01%E8%83%8C%E5%8C%85/4301245?fr=aladdin](https://baike.baidu.com/item/01%E8%83%8C%E5%8C%85/4301245?fr=aladdin)

最近一直在制作个人博客，做好了会分享做法，请大家多多支持

---

## 作者：梅心 (赞：2)

背景：今天，本蒟蒻被别人嘲不会发题解，于是我就找题，正好看到这题，就发了一篇题解
```
#include<bits/stdc++.h>
using namespace std;
int dp[505][505];//当最大体积和重量为505,505时的最大卡路里 
int vol[505], wei[505], ca[505];//每个食物的体积重量和卡路里 
int v, w, n;//最大体积重量和食物数量 
int main()
{
	cin >> v >> w;//输入最大体积和重量 
	cin >> n;//输入有多少个食物 
	for(int i = 1; i <= n; i++)
	{
		cin >> vol[i] >> wei[i] >> ca[i];//输入食物的体积重量和卡路里
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = v; j >= 1; j--)
		{
			for(int k = w; k >= 1; k--)//有两个限制条件，所以三重循环 
			{
				if(j >= vol[i] && k >= wei[i])//如果可以放 
				{
					dp[j][k] = max(dp[j - vol[i]][k - wei[i]] + ca[i], dp[j][k]);//取max 
				}
			}	
		}
	}
	cout << dp[v][w];//当最大体积和重量为v,w时的最大卡路里 
	return 0; 
}
```
求点赞

---

## 作者：luoyoucheng (赞：1)

# 简单的递归
### 从后往前判断每一个可不可以放下
```c

include<iostream>  
using namespace std;  
int a[10000],b[10000],c[10000],t,w,n; //a是体积，b是质量，c是卡路里，t是可容纳下的体积，w是可容纳下的质量  
int dp(int i,int T,int W){ //T是当前还剩多少可用体积，W是还有多少可用质量  
    if(i==0) //最后一个
    {
        if(T>=a[i] and W>=b[i]) //可以放下
		return c[i];
	else //不可以放下
		return 0;
    } 
    else
    {
        if(T>=a[i] and W>=b[i]) //可以放下
            return max(dp(i-1,T-a[i],W-b[i])+c[i],dp(i-1,T,W)); //选第i个或不选
        else //不可以放下
            return dp(i-1,T,W);
    }
}
int main ()
{
    cin>>t>>w>>n;//输入
    for(int i=0;i<n;i++){
        cin>>a[i]>>b[i]>>c[i];
    }
    cout<<dp(n-1,t,w)<<endl; //调用
    return 0;
}
```


---

## 作者：courage (赞：1)

01背包的升级版

f[k][i][j]表示前k个物品，体积为i，质量为j的最大卡路里，状态转移方程：

f[k][i][j]=max{f[k-1][i][j],f[k-1][i-v[k]][j-m[k]]}(注意边界)

可以进行空间优化，仅用二维数组，不过循环顺序必须的逆向的


```cpp

#include<cstdio>
int f[410][410]={0},v,m,n,x,y,z;
inline int max(int a,int b){
    return (a>b?a:b);
}
int main(){
    scanf("%d%d%d",&v,&m,&n);
    while (n--){
        scanf("%d%d%d",&x,&y,&z);
        for (int i=v;i>=x;i--)
            for (int j=m;j>=y;j--)
                f[i][j]=max(f[i][j],f[i-x][j-y]+z);
    }
    printf("%d",f[v][m]);
}

```

---

## 作者：HiroshiRealm (赞：0)

为什么大家这么喜欢DP呢，一个不会DP的蒟蒻很纳闷

为了向其他蒟蒻表示友好，本蒟蒻决定发一发记忆化搜索

（实际上这题还是水题，不用记忆化也是可以水过的）

我用了个结构体，储存每次的质量，体积和价值

```
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include <iostream>
using namespace std;
struct node{
    int big,heavy,value;
}food[100];//big表示体积，heavy表示质量，value表示价值
#define i food[step].big
#define j food[step].heavy
#define k food[step].value
int maxheavy, maxbig, a, b, c, ans[401][401][51];
inline int dfs(int x,int y,int step){
    if(ans[x][y][step] != 0)
        return ans[x][y][step];
    if(step == a + 1)
        return 0;
    if(x >= i && y >= j)//如果剩下的质量和体积够的话
        ans[x][y][step] = max(dfs(x - i, y - j, step + 1) + k , dfs(x, y, step + 1));//取最大值
    else
        ans[x][y][step] = dfs(x, y, step + 1);//不够就只能不选这个东西
    return ans[x][y][step];//返回答案
}
int main() {
    scanf("%d%d%d", &maxbig , &maxheavy, &a);
    for(int x = 1; x <= a; ++ x)
        scanf("%d%d%d", &food[x].big, &food[x].heavy, &food[x].value);
    printf("%d", dfs(maxbig, maxheavy,1));
    return 0;
}

```

---

## 作者：LevenKoko (赞：0)



    

    
```cpp
//看到数据范围，果断搜索；
//剪枝是必要的（大家可以看一下我的提交记录，剪枝AC，不剪枝60其他点都TLE）
//搜索:对于每一种状态都有取和不取两种状态
//剪枝:如果当前状态下的质量已经大于M或体积已经大于V，显然就不要往下搜了 
//代码： 
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<cstring>
using namespace std;
int n,V,M,xv[1005],xm[1005],xp[1005],ans=0; 
void dfs(int step,int nowv,int nowm,int s)//当前状态:nowm现在质量，nowv当前体积，s能总数 
{
    if(step==n+1)
    {
        if(nowv<=V&&nowm<=M)
        ans=max(ans,s);//取大的 
        return;
    }
    //if(nowv>V||nowm>M) return;//神奇的剪枝； 
    dfs(step+1,nowv+xv[step],nowm+xm[step],s+xp[step]),
    dfs(step+1,nowv,nowm,s);//神奇的两种决策 
}
int main()
{
    cin>>V>>M>>n;//神奇的输入1 
    for(int i=1;i<=n;i++)
        cin>>xv[i]>>xm[i]>>xp[i];//神奇的输入2 
    dfs(1,0,0,0);//神奇的搜索； 
    cout<<ans;//神奇的输出； 
    return 0;
}
//过了这道题，P1910的大门向你打开（完全一样的题目）

```

---

## 作者：LMB_001 (赞：0)

其实就是一道01背包，加了一层循环而已，水题，有一些同学是边读入边处理，我还是习惯读入完再处理，致p党

```cpp
uses math;
var
 ti,p,ki:array[1..50] of longint;//体积，卡路里和质量
 f:array[0..400,0..400] of longint;//在体积为i，质量为j时，能取得的卡路里最大量
 i,ans,t,m,j,y,k:longint;
begin
 readln(t,k);//体积限制和质量限制
 readln(m);
 for i:=1 to m do readln(ti[i],ki[i],p[i]);
 for i:=0 to t do 
  for j:=0 to k do f[i,j]:=0;//初始化
 for i:=1 to m do
  for j:=t downto ti[i] do
   for y:=k downto ki[i] do
   f[j,y]:=max(f[j,y],f[j-ti[i],y-ki[i]]+p[i]);//动态转移方程
 ans:=0;
 for i:=1 to t do 
  for j:=1 to k do ans:=max(ans,f[i,j]);//打擂台找最大的
 writeln(ans);//输出了
end.
小弟不才，望各位看官不喜勿喷哦，谢谢
```

---

## 作者：VenusM1nT (赞：0)

//一道01背包升级版 对于初学动规的新人来说略微有一丝挑战性

//这题的状态转移方程可以利用EXCEL来寻找 且很容易找到

//状态转移方程：f[i][j]=max(f[i][j],f[i-a[i].v][j-a[i].m]+a[i].k)，答案则在f[v][m]的位置

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int v,m,n,f[405][405];//这一道题目没有任何必要使用三维，那样只会占内存，因为有一维没卵用= = 
struct node//使用结构体来存储物品的信息，至少对于次序性不好的我这个蒟蒻来说是很方便的 
{
    int v,m,k;
}a[10005];
int main()
{
    scanf("%d%d%d",&v,&m,&n);//读入总信息 
    for(int i=1;i<=n;i++) scanf("%d%d%d",&a[i].v,&a[i].m,&a[i].k);//读入各个物品信息 
    for(int i=1;i<=n;i++)
    {
        for(int j=v;j>=a[i].v;j--)
        {
            for(int k=m;k>=a[i].m;k--) f[j][k]=max(f[j][k],f[j-a[i].v][k-a[i].m]+a[i].k);//状态转移方程在此 
        }
    }
    printf("%d",f[v][m]);//输出，结束。 
    return 0;
}
```

---

## 作者：ABC_ (赞：0)

01背包问题 不过多了一个限制条件  同时满足体积和质量

用f[i][j]表示体积为i质量为j是可以得到的最大卡路里

f[i][j]=max(f[i][j],f[i-v][j-m]+kaluli);

然后ans=max(ans,f[i][j]);

其实很水的一道题



    

```cpp
#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <stack>
#include <queue>
using namespace std;
//scanfromf();
//P1507
const int maxn = 50+5;
int n;
int V, M;
int f[405][405];
int main() {
    scanf("%d%d", &V, &M);
    scanf( "%d", &n);
    memset(f[0], 0, sizeof(f));
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int v, m, kl;
        scanf("%d%d%d", &v, &m, &kl);
        for(int vi=V;vi>=v;vi--)
            for (int mi = M; mi >= m; mi--) {
                f[vi][mi] = max(f[vi][mi], f[vi - v][mi - m] + kl);
                ans = max(ans, f[vi][mi]);
            }
    }
    printf("%d", ans);
    return 0;
}//代码不精，蒟蒻勿喷
```

---

## 作者：✌yww (赞：0)

?//水题背包问题，01，简单dp

状态dp[i][j][l]表示有i个物体，容器体积j，容器最大载重l，的最大卡路里

注意这里做降维处理

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
using namespace std;
int V,M,N;
int v[1200],m[1200],k[1200];
int dp[1200][1200];
int main()
{
    scanf("%d %d %d ",&V,&M,&N);
    for(int i=1; i<=N; i++)
        scanf("%d %d %d",&v[i],&m[i],&k[i]);
    for(int i=1; i<=N; i++)
    {
        //01背包逆序
for(int j=V; j>=v[i]; j--)
        {
            for(int l=M; l>=m[i]; l--)
            {
                dp[j][l]=max(dp[j][l],dp[j-v[i]][l-m[i]]+k[i]);
            }
        }
    }
    printf("%d",dp[V][M]);
    return 0;
}
```

---

## 作者：cenbinbin (赞：0)

双维的dp，既要满足体积，同样也要满足质量。。。

动规方程式：f[j,k]:=f[j-x,k-y]+z;

```cpp
==========================================================
var
  f:array[0..1001,0..1001] of longint;
  m,n,v,i,j,k,x,y,z:longint;
begin
  readln(m,v);
  readln(n);
  for i:=1 to n do
   begin
     readln(x,y,z);//读入
     for j:=m downto x do//枚举体积
      for k:=v downto y do//枚举质量
       if f[j-x,k-y]+z>f[j,k] then f[j,k]:=f[j-x,k-y]+z;//保存最优解
   end;
  writeln(f[m,v]);//输出
end.
```

---

## 作者：Memory_of_winter (赞：0)

这题是2维的0.1背包，一下为程序

```cpp
var
 s:array[0..400,0..400]of longint;
 n,m,o,x,y,z,a,b,c:longint;
begin
 readln(n,m);//读入最大的体积和质量
 readln(o);//读入有几个食物
 for a:=1 to o do
  begin
   readln(x,y,z);读入第a个食物的体积、质量和卡路里
   for b:=n downto x do for c:=m downto y do if (s[b-x,c-y]+z>s[b,c]) then s[b,c]:=s[b-x,c-y]+z;//0.1背包公式
  end;
 writeln(s[n,m]);输出在飞船可承受范围内的最大卡路里
end.
```

---

## 作者：taomiduoduozhu (赞：0)

这题我用的方法很简单，是教材里的背包优化版，如果你用动规解这题，那么就要像楼下的一样，用三维，而且还要找出动态转移方程，我推荐从动规做起，多打草稿，模拟一下样例，多思考，就会做出来。

```cpp
var
  n,m,x,i,j,k:longint;
  w,v,u:array[1..55] of longint;
  f:array[0..400,0..400] of longint;
begin
  readln(n,m);
  readln(x);
  for i:=1 to x do
    readln(w[i],u[i],v[i]);
  for i:=1 to x do
    for j:=n downto w[i] do
      for k:=m downto u[i] do
        if f[j-w[i],k-u[i]]+v[i]>f[j,k] then
          f[j,k]:=f[j-w[i],k-u[i]]+v[i];
  writeln(f[n,m]);
end.
```

---

## 作者：PPPPeppa (赞：0)

###二维背包，还是不太难的，主要是一些关键性语句。###

```cpp
uses math;//调用数据库，不用写函数max或者是min
var
 a,b,c:array[0..1000] of longint;
 f:array[0..5000,0..5000] of longint;//数组不能开小了，不然半天检查不出来错
 t1,t2,v,u,k,m,i,j,l:longint;
begin 
 readln(v,u);
 readln(k);
 for i:=1 to k do read(a[i],b[i],c[i]);
 for i:=1 to k do 
  for j:=v downto a[i] do//只要到a[i]就可以了，没必要到0，当每件物品只能取一次时，采用逆序循环，反之，采用顺序循环
   for l:=u downto b[i] do//同上面一样 
    f[j,l]:=max(f[j,l],f[j-a[i],l-b[i]]+c[i]);//在两者之间选取最大者
 writeln(f[v,u]);
end.
```

---

## 作者：fl_334 (赞：0)

```delphi

//简单二维费用背包问题，只需将01背包+一维即可
var
        v,g,i,j,n,k:longint;
        vv,ww,kk:array[0..1000]of longint;
        f:array[0..5000,0..5000]of longint;   //数组要开足够大
function max(a,b:longint):longint;
begin
        if a>b then exit(a)
        else exit(b);
end;
begin
        readln(v,g);
        readln(n);
        for i:=1 to n do
                readln(vv[i],ww[i],kk[i]);
        for i:=1 to n do
                for j:=v downto vv[i] do
                        for k:=g downto ww[i] do
                                f[j,k]:=max(f[j,k],f[j-vv[i],k-ww[i]]+kk[i]);    //动态转移方程:f[j,k]=max{f[j-vv[i],k-ww[i]]+kk[i]};  简单的二维背包问题，
                                    //不懂看看自己的辅导书
        write(f[v,g]);
end.

```

---

## 作者：汇文客 (赞：0)

此题数据很水，三维也可秒过。

```delphi

for i:=1 to n do
  for j:=0 to vv do
  for k:=0 to ww do
  begin
    f[i,j,k]:=f[i-1,j,k];
    if(j>=v[i])and(k>=w[i])
    and(f[i,j,k]<f[i-1,j-v[i],k-w[i]]+c[i])then
    f[i,j,k]:=f[i-1,j-v[i],k-w[i]]+c[i];

```

---

## 作者：Skywalker_David (赞：0)

一道简单的二维费用的背包问题，与“潜水员”一题相似。

```delphi

var
    a,b,c:array[0..1000] of longint;
    f:array[0..1000,0..1000] of longint;
    t1,t2,v,u,k,i,j,l:longint;
begin
    fillchar(f,sizeof(f),$7f);
    f[0,0]:=0;
    readln(v,u);
    readln(k);
    for i:=1 to k do
        read(a[i],b[i],c[i]);
    for i:=1 to k do
        for j:=v downto 0 do
            for l:=u downto 0 do begin
                t1:=j+a[i];
                t2:=l+b[i];
                if j+a[i]>v then t1:=v;
                if l+b[i]>u then t2:=u;
                if f[t1,t2]>f[j,l]+c[i] then f[t1,t2]:=f[j,l]+c[i];
            end;
    writeln(f[v,u]);
end.

```

---

## 作者：Neil1110 (赞：0)

一道01背包问题，不过要用二维数组（算是升级版？），总体难度还好吧。

```cpp

#include<iostream>
using namespace std;
int main()
{
    int vmax,mmax,n,i,j,k,dp[400][400],c[100],v[100],m[100];    //用一个二维数组dp储存 
    cin>>vmax>>mmax;
    cin>>n;
    for(i=0;i<n;i++)
        cin>>v[i]>>m[i]>>c[i];
    for(i=0;i<n;i++)    //01背包问题动规
    {
        for(j=vmax;j>=v[i];j--)    //体积
        {
            for(k=mmax;k>=m[i];k--)    //质量
            {
                if(dp[j][k]<dp[j-v[i]][k-m[i]]+c[i])    //转移方程 dp[j][k]=max(dp[j][k],dp[j-v[i]][k-m[i]]+c[i])
                    dp[j][k]=dp[j-v[i]][k-m[i]]+c[i];
            }
        }
    }
    cout<<dp[vmax][mmax]<<endl;
    return 0;
} 

```

---

## 作者：lbn187 (赞：0)

简单的二维背包

f[j,k]:=max(f[j-a[i],k-b[i]]+c[i],f[j,k]);

程序：

```cpp
var
  a,b,c:array[0..10000] of longint;
  f:Array[0..1000,0..1000] of longint;
  v,m,n,i,j,k:longint;
begin
  readln(v,m);
  readln(n);
  for i:=1 to n do
    readln(a[i],b[i],c[i]);
  for i:=1 to n do
    for j:=v downto a[i] do
      for k:=m downto b[i] do
        if f[j-a[i],k-b[i]]+c[i]>f[j,k] then f[j,k]:=f[j-a[i],k-b[i]]+c[i];
  writeln(f[v,m]);
end.

```

---

