# Help General

## 题目描述

Once upon a time in the Kingdom of Far Far Away lived Sir Lancelot, the chief Royal General. He was very proud of his men and he liked to invite the King to come and watch drill exercises which demonstrated the fighting techniques and tactics of the squad he was in charge of. But time went by and one day Sir Lancelot had a major argument with the Fairy Godmother (there were rumors that the argument occurred after the general spoke badly of the Godmother's flying techniques. That seemed to hurt the Fairy Godmother very deeply).

As the result of the argument, the Godmother put a rather strange curse upon the general. It sounded all complicated and quite harmless: "If the squared distance between some two soldiers equals to $ 5 $ , then those soldiers will conflict with each other!"

The drill exercises are held on a rectangular $ n×m $ field, split into $ nm $ square $ 1×1 $ segments for each soldier. Thus, the square of the distance between the soldiers that stand on squares $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ equals exactly $ (x_{1}-x_{2})^{2}+(y_{1}-y_{2})^{2} $ . Now not all $ nm $ squad soldiers can participate in the drill exercises as it was before the Fairy Godmother's curse. Unless, of course, the general wants the soldiers to fight with each other or even worse... For example, if he puts a soldier in the square $ (2,2) $ , then he cannot put soldiers in the squares $ (1,4) $ , $ (3,4) $ , $ (4,1) $ and $ (4,3) $ — each of them will conflict with the soldier in the square $ (2,2) $ .

Your task is to help the general. You are given the size of the drill exercise field. You are asked to calculate the maximum number of soldiers that can be simultaneously positioned on this field, so that no two soldiers fall under the Fairy Godmother's curse.

## 说明/提示

In the first sample test Sir Lancelot can place his 4 soldiers on the $ 2×4 $ court as follows (the soldiers' locations are marked with gray circles on the scheme):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF142B/0d23ce3839b0ce156cddd9663617e134809111ae.png)In the second sample test he can place 6 soldiers on the $ 3×4 $ site in the following manner:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF142B/57bf2bd762016d87a2641e15975b3acd653786ad.png)

## 样例 #1

### 输入

```
2 4
```

### 输出

```
4```

## 样例 #2

### 输入

```
3 4
```

### 输出

```
6```

# 题解

## 作者：封禁用户 (赞：5)

# 0.前言
[我的AC记录](https://www.luogu.com.cn/record/55855397)

[题目传送门](https://www.luogu.com.cn/problem/CF142B)

看见提交题解的几位dalao没有用数学方法，本菜鸡来用数学方法来解一下本题。

此题没有公式，所有所谓的公式都是根据思路推出来的！下面看我的思路趴！

# 1.思路
每个“马”走一步，对应一个位置，所以相当于每个“马”可以待在两个位置的其中一个，要么是棋盘上的初始位置要么是走一步后的位置。

但每个“马”只能选择二者中的一个。

所以，除了 $1$ 和 $2$ 的特殊情况外，棋盘上放的“马”一定等于棋盘空间的**一半**。奇数 $/2+1$，偶数直接 $/2$。（证明在后面！！！）
## 2.特判：处理 $n$ , $m$ 其中一个为 $1$ 或 $2$ 的情况

**首先处理当 $n$ 或 $m$ 其中一个为 $1$ 的情况：**

当 $n$ 或 $m$ 其中一个为 $1$ 时，因为“马”走日，所以全部的格子都可以放。即：


```cpp
	if(n==1||m==1){
		cout<<max(n,m);
		return 0;
	}
```
应该很好理解。

**再处理 $2$：**

当其中一个数为 $2$ 并且另外一个数不为 $4$ 但是为 $2$ 的倍数时，简单试一下就知道结果为 $n+m$ ；

其中一个数为 $2$ 并且另一个数为 $2$ 的倍数时，结果 $\max(n,m)$ 。

再考虑奇数偶数情况即可。（奇数要 $+1$，偶数不用）

```cpp
if(n==2||m==2){
        if(max(n,m)%2==0){
            cout<<max(n,m)<<endl;
                return 0;
        }
        else{
            cout<<max(n,m)+1<<endl;
            return 0;
        }		
  }
```


其余直接输出格子数的 $1/2$。

# 3.code
AC代码如下：


```cpp
  #include<iostream>
  #include<cmath>
  using namespace std;
  int n,m;
  int main(){
      cin>>n>>m;
      if(n==1||m==1){
          cout<<max(n,m);
          return 0;
      }
      if(n==2||m==2){
          if(n==2){
              if(m%2==0&&m%4!=0){
                  cout<<n+m;
                  return 0;
              }
          }
          if(m==2){
              if(n%2==0&&n%4!=0){
                  cout<<n+m;
                  return 0;
              }
          }
          if(max(n,m)%2==0){
              cout<<max(n,m)<<endl;
              return 0;
          }
          else{
              cout<<max(n,m)+1<<endl;
              return 0;
          }
      }
      cout<<(n*m+1)/2;
  }
```
但说实话，当时我也真不知道 $2$ 为什么是这样，仅仅通过样例和一小部分数据就可以推理出来了。
# 4.总结&证明
总结：
在考试的时候，发现各种方法尝试过后都失败时，不妨试试数学的方法，自己尝试造一些数据，根据输入和输出找规律，这种方法尤其适用于只输出一个数的时候。就拿这道题举例，除了特殊情况外都为 $\max(n,m)\times \min(m,n)/2$，加 $1$ 需要判断奇偶性。对于证明，这都是后事了。

证明：
对于这道题的证明因为 $1$ 行格子马无法跳日，所以都可以放。
而对于 $2$ 来说，马可以跳日，所以某一行或某一列没有马（为了好说，所以用来构造，当然也可以有其他构造方法），这时就转换成了 $1$ 行格子的问题，只要把某一行或某一列全部填满，就能保证个数最大化，那具体选行还是列呢？直接用 $\max(n,m)$ 即可。

当格子数某一行或列为 $1$ 时：

![11](https://img-blog.csdnimg.cn/2ef713b7370f47039d6912119d89f19e.png)

$2$ 同理。

一般情况：我们用坐标来表示每只马。

当马为（奇，奇）时，会移动到（偶，奇）；

当马为（偶，偶）时，会移动到（奇，偶）。

这样就能保证我的每只马都在（奇，奇）或（偶，偶），就算跳也只能跳到（偶，奇）或（奇，偶）。

直接说不好说明，大家直接看下图，就能明白了：

偶数情况：

![11](https://img-blog.csdnimg.cn/f1e355054a214866be9f06ad9e473efa.png)

大家看出来了么，每一行刚好是一半！

奇数情况：

![](https://img-blog.csdnimg.cn/9f3da283f69644d49e9778e1f30342a4.png)

大家看出来了么，其实和偶数也差不多，但是 $+1$ 要注意一下。

那为什么这样放就是大的呢？
当这个图任意放一个一定是（偶，奇）或（奇，偶），这是因为我们原来放的马已经将（奇，奇）和（偶，偶）填满。那么这样就好办了，刚才已经说过，（奇，奇）会移动到（偶，奇）；（偶，偶）时，会移动到（奇，偶）。所以你只要在（偶，奇）或（奇，偶）放了马就一定会矛盾，也证明了无法在放下去，所以这样放就是最大的。

这就是所有的构造方法，总的来说就是 $1,2$ 的时候某一行或列全放，一般情况错着位放。

---

## 作者：a___ (赞：5)


以下提供一种不同的方法和规律计算法的详细证明。

--------
思路：将所有能 **相互攻击** 到的格子之间连一条边，问题转为求该图的最大独立集（即求一个 **最大** 点集，使任意两点间 **没有连边** ）。    
问题在于，如何求 **这些** 最大独立集？

----
注意1：别急着走，不讲图论算法相关！   
警告2：篇幅过长警告，直接拖到结尾可查看结论，或者只看加粗部分。   
警告3：图片可能 **过大** 霸屏，但我也不知道咋调。。。。（反正我试了几种方法都不行）   
注意4：以下所说的 **“点”** 和 **“格子”** 表示相同含义，只是因为有时描述为格子不好表述。   
规定5：记原 **网格** 图为 **A图**，经上述 **连边** 处理后的图为 **B图**。

---
首先要作一个证明：B图是一个二分图。即从 **任意点** 出发不可能经 **恰奇数** 次移动回到原点（无奇环证二分图）。
以下是从一个点可以攻击到的若干点示意图：（这里为了省事我直接画到点上了，一个点代表样例的一个格子）
![](https://cdn.luogu.com.cn/upload/image_hosting/u0rula29.png)   
如果我们把攻击的每个方向视为一个向量，那么，奇数次回到原点相当于奇数个向量和为 $ (0,0) $ 。**也就是说，如果经奇数次可以回到原点，设每次移动行号增加 $ x_i $,列号增加 $ y_i $，那么对于某一奇数 $ n $，必有 $ x_1 + x_2 + \dots + x_n = 0 $，同时 $ y_1 + y_2 + \dots + y_n =0 $.**   
两式相加，得 $ (x_1 + y_1) + (x_2 + y_2) + \dots + (x_n + y_n) = 0 $.    
然而，观察上图，发现任意 $ x + y = \pm 1 $ 或 $ \pm 3 $ 。   
由于 **奇数个奇数相加等于奇数**，所以上式和 **一定** 不为 $ 0 $ ，得证。

----
由此，我们可以想到，从某个点开始遍历 **该点所在连通块**，黑白染色，所有 **颜色相同** 的点之间 **一定没有边** 相连（因为不可能奇数步回来）。我们先选点数较多的那一组，可以发现，**在该联通块内**，任意加入或替换使所选点数增加的方案都会导致有点相联。    
举个例子，我把上面那张图处理建图了，向这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/bg8tnrix.png)   
（可以发现任意同色点之间没有边）   
我们先选取所有红色点，共13个。   
将任意红点替换为数量相当的绿点，均发现有出现两点之间有边情况。     
所以，最优解即为染色后点数更多的那一组点。

------
说了那么多，其实大概一看是个二分图直接写就完了。
```cpp
#include<cstdio>
const int N=1010,dx[8]={-1,1,2,2,1,-1,-2,-2},dy[8]={-2,-2,-1,1,2,2,1,-1};
bool b[N][N];
int n,m;
int cnt[2],ans,q[N*N][3],hd,tl;
inline int max(int a,int b){return a>b?a:b;}
int main()
{
    int i,j,k,x,y;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)
    for(j=1;j<=m;j++)
    if(!b[i][j])
    {
        b[q[1][0]=i][q[1][1]=j]=true;
        cnt[0]=1;cnt[1]=0;
        for(hd=tl=1;hd<=tl;hd++)//bfs + 染色
        for(k=0;k<8;k++)
        {
            x=q[hd][0]+dx[k];
            y=q[hd][1]+dy[k];
            if(x>0&&x<=n&&y>0&&y<=m&&!b[x][y])
            {
                cnt[q[++tl][2]=(q[hd][2]^1)]++;
                b[q[tl][0]=x][q[tl][1]=y]=true;
            }
        }
        ans+=max(cnt[0],cnt[1]);//取较多一组点
    }
    printf("%d\n",ans);
    return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/32528852)

-----
$ \uparrow $ 分界线 $ \downarrow $

-----
接下来讲另一种做法（大佬们的做法）：   
还是从证明二分图那里说起。   
先把整张A图 **相邻格黑白染色**，像这样：   
![](https://cdn.luogu.com.cn/upload/image_hosting/m1whkpo2.png)     
发现（篇幅有限请自证）黑块 **只能** 与白块有边相连，而白块 **只能** 与黑块有边相连，所以 **任意同色点** 间没有边，B图是二分图,而且，**这同时还可以证明两种颜色的点点数各占一半**。   

依照刚才的理论，取点数较多的颜色，显然，答案应该是 $ \lfloor (n * m + 1) / 2 \rfloor $ 。所以直接输出就好了，问题结束（？）。   
如果你真这么做了，，，。这是因为，当行数或列数小于等于2时，某些点之间无论如何也相互达不到，这就导致得到的B图 **并不是一个完整的联通图，而是好几个连通块**，然而我们上面总结的取较多的一半点 **仅对单个联通图适用**（3 \* 3 的图是个例外，刚好对上了）。   
![](https://cdn.luogu.com.cn/upload/image_hosting/mtz1lilf.png)    
这里插入一则证明：任何行列数均大于等于3的（除3 \* 3外）均整图联通（可以从任意点到任意点）     
证明如下：如上图，3 \* 3 格子中周围八点联通；只要行列大于等于3，假设我们把一个 3 \* 3 的框（不包括中心点）**从左向右，从上向下平移**，一定可以完全覆盖所有点，而框内点相互联通，所以整图联通。   

------
所以现在的问题就是解决行数或列数小于等于2的情况。   
先考虑行或列数等于1，发现任意点之间不联通，所以直接输出点数 $ n * m $。    
然后是行数或列数等于2。观察上图，发现（篇幅有限，不写证明了），总共会有 **四个联通块**，而且 **每个田字格** 中四个联通块中的点 **均会出现一次且仅一次** 。所以，我们考虑 **分别** 对这四个联通块做处理。根据我们的发现，先将点数除以4，则商为完整田字格数，余数有两种情况：   
第一，恰好整除，则商即为 **每个联通块内都恰有的点数**（参考上图），结合之前的分析，答案为 $ 4 * \lfloor (n * m / 4 + 1) / 2 \rfloor $ 。   
第二，余数为2，则 **其中两个** 联通块点数 **为商**，**另两个** 点数 **比商多1**（参考上图），结合之前的分析，答案为 $ 2 * \lfloor ( \lfloor n * m / 4 \rfloor + 1) / 2 \rfloor + 2 *  \lfloor ( \lceil n * m / 4 \rceil  + 1) / 2 \rfloor $。   
```cpp
if(n==1||m==1)printf("%d\n",n*m);
else if(n==2||m==2)
	if(n*m%4==0)printf("%d\n",((((n*m)>>2)+1)>>1)<<2);
    else printf("%d\n",(((((n*m)>>2)+1)>>1)<<1)+(((((n*m)>>2)+2)>>1)<<1));
else printf("%d\n",(n*m+1)>>1);
```   
[AC记录](https://www.luogu.com.cn/record/32661944)   
当然，如果你想再按商膜二等于0/1再讨论一下，你可以化出和其他题解相同的结果。

-------
总结：   
1. 由于B图是一个或几个二分联通图，黑白染色，取点数较多颜色点数（注意可能不止一个连通块）。时间复杂度 $ \mathbf O (nm) $。   
2. 由于相邻格互相达不到，2 \* m 可以四个一组放，直接使用公式计算答案（公式就在上面）。时间复杂度 $ \mathbf O (1) $。

---

## 作者：liaoxingrui (赞：3)

## Content

给你两个正整数 $n$，$m$，求在 $n \times m$ 的棋盘上能放多少个国际象棋的马，使它们互不攻击。

![马](https://cdn.luogu.com.cn/upload/image_hosting/9yweuvl5.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

## Solution

由图可知，马不会攻击斜着的、横着的、竖着的马。

那么我们就可以这样放马。


```
n=4
m=5

.#.#.
#.#.#
.#.#.
#.#.#

n=5
m=5

.#.#.
#.#.#
.#.#.
#.#.#
.#.#.

. 为马
# 为空格
```

我们发现每两排它的马的个数为 $m$，而 $n$ 和 $m$ 都为奇数时，它会多出一行为 $\frac m 2 + 1$，可得马的个数为 $\frac {n \times m} 2 + n \times m \bmod 2$。

但它还需要特判。

对于 $n = 1$ 的情况，我们可以直接输出 $m$，看上面的图可知，马不会攻击上下左右的马，$m = 1$ 的情况同理。

对于 $n = 2$ 与 $m$ 为 $2$ 的倍数的情况，我们发现马的个数为 $n+m$。


```
n=2
m=6

..##..
..##..
```

将第二行第 2 个和第 5 个向上移可得。

```
......
.####.
```

由与有一点重合与右下多一个的马的个数抵了，所以马的个数为 $n + m$。

但注意 $m$ 要不为 $4$ 的倍数时，不然它的个数为 $m + m \bmod 2$，$m = 2$ 同理。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
	cin>>n>>m;
	if(n==1||m==1)
		cout<<max(n,m);
	else if((n==2&&!(m&1)&&m&3)||(m==2&&!(n&1)&&n&3))
		cout<<n+m;
	else if(n==2||m==2)
		cout<<max(n,m)+(max(n,m)&1);
	else
		cout<<(n*m>>1)+(n*m&1);
	return 0;
}
```

---

## 作者：WhxStar2024 (赞：1)

## 本题思路：
这道题其实并不是非常复杂，我们发现只要马站在黑色的格子上就不会再次跳到黑格子上，那么我们就可以直接算格子总数除二向上取整的答案数即可。

这里我们需要特判一下 $n$ 或 $m$ 等于一或二的情况，在为一时输出最大值，在为二时与每格两列放两列的方法取最大值即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int n,m;
	cin>>n>>m;
	if(n==1) return cout<<m,0;
	if(m==1) return cout<<n,0;
	if(n==2 && m==3) return cout<<4,0;
	if(n==3 && m==2) return cout<<4,0;
	if(n==2 && m==2) return cout<<4,0;
	if(n>m) swap(n,m);
	if(n==2){
		cout<<max((n*m)/2+(n*m)%2,(m/4)*4+min(m%4,2ll)*2);
		return 0;
	} 
	cout<<(n*m)/2+(n*m)%2;
	return 0;
}
```

---

## 作者：shenbairui (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF142B)

### 题目大意

在 $n \times m$ 的棋盘上放置尽可能多的国际象棋中的马，让它们互不攻击。输出放的马的个数。

### 题目分析

我们可以采用分类讨论的方法来分析

设 $\max(n,m)$ 为 $a$，$\min(n,m)$ 为 $b$。

首先是 $b=1$ 时，此时 $n$ 或 $m$ 只有一行，马只能跳到别的行或列去，就算放满，也不会被吃掉，所以答案就是 $a$，具体如下图。 

![](https://cdn.luogu.com.cn/upload/image_hosting/da9w30pi.png)

当 $b=2$ 时，我们把马一个挨一个成一个田子格放，在空一个田字格放。这样的话一个田字格的马，只能打到空白田字格的地方。输出能能放多少格田字格加上隔另一个田字格还有多少格能放，具体图如下。

![](https://cdn.luogu.com.cn/upload/image_hosting/ig4y1i8j.png)

特殊情况都排除完了，就是普通情况了。我们可以直接按照黑白格去放，就不会打到了，具体图如下。

![](https://cdn.luogu.com.cn/upload/image_hosting/g0lpb15p.png)

### 上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
	cin>>n>>m;
	if(min(n,m)==1) cout<<max(n,m); 
	else if(min(n,m)==2){
		if(max(n,m)%4<=2) cout<<max(n,m)+max(n,m)%4; 
		else cout<<max(n,m)+1;
	}
	else cout<<(n*m+1)/2;
	return 0;
}
```

---

## 作者：MujicaSaki (赞：1)

### 思路：

首先了解一下国际象棋马的走法，就是跟象棋一样是先横走或直走一格，再斜着走一格从而完成一步。俗称就是马走日。

当 $min(n,m) = 1$ 时,我们不妨从 $n$ 和 $m$ 选最小的，因为地方太少了，只有一行，很明显怎么放都不能攻击到另一个马，所以答案很明显就是 $n$ 和 $m$ 选最大的也就是 $max(n,m)$ 本质上就是一共有多少个格子。

当 $min(n,m) = 2$ 时，我们把马一个挨一个成一个田子格放，在空一个田字格放。这样的话一个田字格的马，只能打到空白田字格的地方。可以自己试一试，我就不放了。就是输出能能放多少格田字格加上隔另一个田字格还有多少格能放。

特殊情况都排除完了，就是普通情况了。我们可以直接按照黑白格去放，就不会打到了。

![](https://cdn.luogu.com.cn/upload/image_hosting/bskq5r5l.png)

看图很明显就是 $(n*m+1)/2$ 个黑格子，也就是有多少匹马。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
cin>>n>>m;
if(min(n,m)==1) cout<<max(n,m); 
else if(min(n,m)==2){
if(max(n,m)%4<=2) cout<<max(n,m)+max(n,m)%4; 
else cout<<max(n,m)+1;
}
else cout<<(n*m+1)/2;
}
```



---

## 作者：动态WA (赞：1)

~~伪~~py党的题解（既然学校教了py就要学以致用~~水题解~~）

跟其他大佬比起来，题解可能不是那么简洁清晰，我按自己当时的做题思路来讲（逃

第一眼望去，以为是个状压dp，想方程式半天想不出来，于是换了个思路（找规律）

~~无意~~点开题解，了解了大概的思路，也就是要**分类讨论**，讨论时使**行数＜列数**

**当这个棋盘只有一行**，可以发现每一格都能放，此时输出列数。

**当这个棋盘有两行**，能想到两种较为理想的放法，一种是交叉放，另一种是四个一组地放，我们再分类讨论。

假设列数等于4，此时四个一组的方法浪费空间是最多的，但是此时它与交叉放所能放置的数量相等。

再看其他情况，均是四个一组放的数量多。

所以当行数等于2时，我们采用四个一组放。此时数量分两种情况可以求出：

一、最后两列都不能放或者最后一列能放，答案数等于（列数*列数%4）

二、只有最后一列不能放，答案数等于（列数+1）

**当这个棋盘大于两行**，交叉放就是最理想的了，数量则为(行数*列数+1)//2

代码如下：

```python
s=input().split()
n=int(s[0])
m=int(s[1])
if (n>m):
    a=n
    n=m
    m=a
if (n==1):
    print(m)
elif (n==2):
    if (m%4<=2):
        print(m+m%4)
    else: 
        print(m+1)
else:
    print((n*m+1)//2)
```


---

## 作者：xiaohuang (赞：1)

[更好的阅读体验](https://xiaohuang888.github.io/2019/08/01/%E3%80%8E%E9%A2%98%E8%A7%A3%E3%80%8FCoderforces142B%20Help%20General)

### Description in Chinese

在$n \times m$的国际象棋棋盘上放尽可能多的马，让它们互不攻击，求出最多可以放的马的数量。

### Solution

不妨令$n < m$。

然后，我们分情况来考虑：

1. 当$n = 1$时，无论马放在哪里，都不能攻击到其它任何马，所以答案就是$m$；

1. 当$n = 2$时，我们可以这么放：

```
11001100...
11001100...
```

（`1`表示放，`0`表示不放）

这样能保证马互不攻击，因为这是国际象棋，不存在马因特殊情况不能攻击另一匹马。

![](https://s2.ax1x.com/2019/08/01/eUG336.png)

箭头表示攻击到的点。

3. 当$n > 2$时，我们可以按国际象棋的棋盘放，这样马也不能互相攻击。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

int n, m;
int main() {
    scanf("%d%d", &n, &m);
    if (n > m) swap(n, m);//强制使n < m
    int ans;
    if (n == 1) ans = m; else//情况1
    if (n == 2) {//情况2
        if (m % 4 <= 2) ans = m + m % 4; else ans = m + 1;
    } else ans = (n * m + 1) / 2;//情况3
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：SIGSEGV (赞：1)

首先，为了方便处理，因此要使$n > m$。先加入代码

`if (n < m) swap(n,m);`

大力分类讨论:

当m=1时（棋盘只有一行），放满；

当m=2时，按照田字格放；（即放4个空4个），看上去像这样（1：放 0:不放）
| 1 | 1 | 0 | 0 | 1 | 1 | 0 | 0 | 1 | 1 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 1 | 1 | 0 | 0 | 1 | 1 | 0 | 0 | 1 | 1 |

当m>2时，隔一个位置放一个，如
| 1 | 0 |1  |
| -----------: | -----------: | -----------: |
| 0 | 1 | 0 |
| 1 | 0 | 1 |

（按照国际象棋中的黑白格放）

上代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
int main ()
{
    scanf("%d%d",&n,&m);
    if (n < m) swap(n,m);
    if (n == 1 || m == 1) printf("%d\n",n * m); //m=1
    else if ((n == 2 || m == 2) && n * m != 2) //m=2
    {
        if (n % 4 == 0) printf("%d\n",n);
        if (n % 4 == 3) printf("%d\n",n + 1);
        if (n % 4 == 2) printf("%d\n",n + 2);
        if (n % 4 == 1) printf("%d\n",n + 1); 
    }
    else printf("%d\n",(1 + n * m) / 2); //m>2
    
    return 0;
}
```

---

## 作者：_Lazy_zhr_ (赞：0)

结论题，但难把结论想全（至少我是想不全的）。

我们令 $n\le m$。

分三种情况。

若 $n=1$，直接放满即可。

若 $n=2$，以 $m=11$ 为例，此时这样放是最优的（`1` 代表放，`0` 代表不放，下同）：

```
11001100110
11001100110
```

也就是第 $i$ 行第 $j$ 列的位置，当 $j\bmod4\le2$ 时，这个位置放，否则不放。

若 $n\ge 2$，以 $n=5$，$m=5$ 为例，此时这样放是最优的：

```
10101
01010
10101
01010
10101
```

也就是第 $i$ 行第 $j$ 列的位置，当 $i\bmod2=j\bmod2$ 时，这个位置放，否则不放。

代码如下：

```cpp
int n,m;
void solve(){
	cin>>n>>m;
	if(n<m) swap(n,m);
	int ans=n*m;
	if(m==1){
		cout<<ans<<"\n";
		return ;
	}
	else if(m==2){
		swap(n,m);
		cout<<n*((m/4)*2+min(m%4,2));
		return ;
	}
	if(ans%2) cout<<ans/2+1<<"\n";
	else cout<<ans/2<<"\n";
}
```

---

## 作者：Mu_leaf (赞：0)

## [思路]
既然题目声明了是棋盘，不如就将每个格子抽象成黑白两色的国际象棋棋盘。

显然，马不能攻击相同颜色的格子上的马，则要么放黑色格子最优，要么放白色格子最优，我们不关心具体格子在哪，则最多的同色格子数一定是 $\lceil \dfrac{n\times m}{2} \rceil$。

考虑特殊情况，我们钦定 $n<m$。

- 当 $n=1$ 时，由于马不能攻击横向的，所以每个格子可以放上。

- 当 $n=2$ 时，给出以下构造：

![](https://cdn.luogu.com.cn/upload/image_hosting/4yc9fwip.png)

这样会更优。

代码太简单就不放了。

---

## 作者：yzh_Error404 (赞：0)

找规律好题。

马的攻击区域是 $1\times 2$ ，肯定先考虑特殊的。

1. $n=1$ 或 $m=1$

不用想，肯定是全放满，答案就是 $\max(n,m)$。

2. $n=2$ 或 $m=2$ 

可以隔四个摆四个，类似于如下的摆法，答案需要分列数讨论。
```
1 1 0 0 1 1 0 .....

1 1 0 0 1 1 0 .....
```

3. $n$，$m$ 有一个为偶数

可以通过观察发现一个简单的结论，当交错摆的时候，相邻两列的个数之和就是 $n$（或相邻两行的个数之和是 $m$）。

当列数或行数中有一个是偶数时，可以直接推出答案是 $(n\times m)/2$

4. $n$，$m$ 均为奇数

按照情况 $3$ 来摆，最后剩下一列或一行，肯定要摆多一点，所以把相邻两列或两行中较多的一列或一行留给它，答案即为 $\min(n,m)\times \max(n,m)+\max(n,m)/2+1$

代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    if(n==1||m==1)
    {
        printf("%d",max(n,m));
        return 0;
    }
    if(n==2||m==2)//上面情况2的分类讨论，四列为一组，看余数即可
    {
        if(max(n,m)%4==0)printf("%d",max(n,m)/4*4);
        if(max(n,m)%4==1)printf("%d",max(n,m)/4*4+2);
        if(max(n,m)%4==2)printf("%d",max(n,m)/4*4+4);
        if(max(n,m)%4==3)printf("%d",max(n,m)/4*4+4);
        return 0;
    }
    if(n%2==0||m%2==0)
    {
        printf("%d",n*m/2);
        return 0;
    }
    if(n%2!=0&&m%2!=0)
    {
        printf("%d",min(n,m)/2*max(n,m)+max(n,m)/2+1);
        return 0;
    }
    return 0;
}
```

---

## 作者：BADFIVE (赞：0)

**题意**：在一个 $n \star m$ 的棋盘上尽可能多的放马。且让他们互不攻击。   
**思路**：马在国际象棋的行走方法是走日字，如下图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/1wzc7gno.png?x-oss-process=image/resize,m_lfit,h_570,w_725)    
我们可以保证 $n<m$，分三种情况讨论：   
$\cdot$ 当 $n=1$ 时，只有一竖列，所以马无论怎么放都无法互相攻击。所以答案就为 $m$ 。   
$\cdot$ 当 $n=2$ 时，我们可以选择交叉放或者四个为一组的放   
$\cdot$ 当 $n>2$ 时，我们可以选择隔一个位置放一个。答案为： $(n+m+1)/2$   

关键是如何判断一个数字是不是完全平方数，方法就是先开方，转化为整型，然后再平方看是不是等于原来的数字。   
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m,ans=0;
    cin>>n>>m;
    if(n>m)swap(n,m);
    if(n==1)ans=m; 
	else if(n==2){
        if(m%4<=2)ans=m+m%4; 
		else ans=m+1;
    }
	else ans=(n*m+1)/2;
    cout<<ans;
}
```

---

