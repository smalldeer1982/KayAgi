# [NOIP 1999 普及组] Cantor 表

## 题目描述

现代数学的著名证明之一是 Georg Cantor 证明了有理数是可枚举的。他是用下面这一张表来证明这一命题的：

![](https://cdn.luogu.com.cn/upload/image_hosting/jdjdaf73.png)

我们以 Z 字形给上表的每一项编号。第一项是 $1/1$，然后是 $1/2$，$2/1$，$3/1$，$2/2$，…


## 说明/提示

- 2024-11-18 0:30 数据中加入了样例，放在不计分的子任务 2 中。

## 样例 #1

### 输入

```
7
```

### 输出

```
1/4```

# 题解

## 作者：哦哟筷子 (赞：742)

###  现在是扯淡时间：
 这是本蒟蒻第一次发题解，那么我这么垃圾为什么还要发题解呢
 
~~其实是我看这道题实在是太简单了，居然出现在BOSS区~~

其实是因为我看题解里的**大佬**实在是太**大佬**了，想找一个简单的办法解决这个问题


$update$ : 我写这篇题解也差不多快一年了，中间有很多评论我都没有回复，现在统一更新一下。首先声明一下，我写这篇题解的时候，刚入门，以为$AK$新手村已经很不错了，所以这话说的特别蠢（逃），而且似乎试炼场会被在不久的将来撤下，那这个话的起源都不知道去哪里了$233$.


------------

### 好了，扯淡扯完了
可以恢复正题了（我觉得我这个程序应该是题解里最短的了（小声BB））

$update$:显然这样的程序并不是最短的，评论已经有很多的$dalao$指出了，而且时间复杂度也并不优秀，但是当时就会有一种~~莫名的自信~~ 至于怎么压行，评论区也说得比较明白了，所以评论不用再提供压行思路了

废话不多说，先上代码
```cpp
#include <bits/stdc++.h>
using namespace std; 
int main() {
	int n,k=1;
	cin>>n;
	while (n>k) {
		n=n-k;
		k++;
	}
	if(k%2==0) cout<<n<<"/"<<(k+1-n);
	else cout<<k+1-n<<"/"<<n;
	return 0;
} 
```

（从这一行往下全是$update$）

$update$: 首先我们观察到第$i$行，第$j$列的数就是$i/j$,这是第一个要发现的。

因为题目中要求是以$Z$字型编号

我们看题目中的表是：

$1/1,1/2,1/3$ ……

$2/1,2/2,2/3$ ……

$Z$字型编号以后（把头向左偏45度）：

第一行：$1/1$  ($1$号)

第二行：$1/2$ ($2$号)  $2/1$($3$号)

第三行：$1/3$ **($6$号)**  $2/2$ **($5$号)** $3/1$ **($4$号)**  

$\uparrow$ 观察法易得每一行比上一行多1

代码里那个$while$循环，就是为了通过循环枚举，判断它在编号之后的第几行，第几个位置。



------------
（这个优化有没有都可以$AC$本题，但是评论指出我的时间复杂度不够优秀，因此提一提这个优化，不愿意看的可以直接略过看下一个分割线以后的内容。）

但其实可以直接出结论优化时间复杂度从$O(n)$ 优化到$O(1)$，这样就要考虑到等差数列求和

公式：$S=\frac{n(a_n+a_1)}{2}$

所以，很显然$Z$字型排序之后，第$k$行的数编号$n$满足：

$\frac{k(k-1)}{2} < n \le \frac{k(k+1)}{2}$

这样就可以把那个循环优化掉。代码就不贴了 ~~（因为懒，还怕出错）~~

------------


但当时我才刚学，没想到上面的这个优化（罪恶之源：我太蒻了），只好写了个丑陋的模拟233。

代码当中$k$用来记$Z$字型编号之后的行数，显然第$k$行有$k$个数，因此每次$n$要减去$k$。

最后用$k$判断奇偶，是判断这一行$Z$字型编号是正序（类似第二行）还是倒序（类似第三行）然后用最开始的结论输出原表中的行号除以列号就行了



最后，我只想表达一下自己那么蒟蒻在这里发题解的愧意

还有有问题的话大佬一定要指出！！（害怕）

---

## 作者：「已注销」 (赞：288)

算法1：模拟，按题意一个个枚举

时间复杂度O(n),可以通过本题n≤10^7


算法2：发现Z字形的每条斜线可以快速枚举，即枚举

1/1 , 1/2 , 3/1 , 1/4 , 5/1 , 1/6……找到要求的第n项所在斜线，再一个个枚举或计算得出答案

时间复杂度O(√n),可以通过n≤10^14

算法2.5：枚举第n项在哪一行，计算得出答案，比算法2好写,

时间复杂度同算法2


算法3：发现第i条斜线（即分子分母之和=i+1的所有项）中包含i\*(i-1)/2+1至i\*(i+1)中的每一项，所以可以二分分子分母之和，再根据分子分母之和的奇偶性直接计算第n项

时间复杂度O(㏒₂n),可以通过n≤10^18,加上高精可通过n≤10^1000

二分参考代码：

```cpp
    #include<iostream>
    #include<cmath>
    using namespace std;
    int main(){
        long long l=1,r,mid,n,a;
        cin>>n;
        r=n;
        while(l<r){
            mid=(l+r)/2;
            if(mid*(mid+1)/2<n)l=mid+1;
            else r=mid;
        }
        a=n-l*(l-1)/2;
        if(l%2==0)cout<<a<<'/'<<l+1-a;
        else cout<<l+1-a<<'/'<<a;
        return 0;
}
```

---

## 作者：char32_t (赞：270)

#P1014 【Cantor表】

------------

####模拟题

**建议在Excel上打出Cantor表，再找规律(还有一个好处是可以用来测试)**

~~如图~~ 如表：

1/1    1/2    1/3    1/4    1/5    1/6    1/7    1/8    1/9

2/1    2/2    2/3    2/4    2/5    2/6    2/7    2/8

3/1    3/2    3/3    3/4    3/5    3/6    3/7

4/1    4/2    4/3    4/4    4/5    4/6

5/1    5/2    5/3    5/4    5/5

6/1    6/2    6/3    6/4

7/1    7/2    7/3

8/1    8/2

9/1

**（普及）在单元格中输入分数前先输入一个单引号，避免被判断为日期**


```cpp
    #include<cstdio>
    int main() {
        int n, i=0, j=0;//前i条斜线一共j个数
        scanf("%d", &n);
        while(n>j) {//找到最小的i使得j>=n
            i++;
            j+=i;
        }
        if(i%2==1)
            printf("%d/%d",j-n+1,i+n-j);//i的奇偶决定着斜线上数的顺序,n是第i条斜线上倒数第j-n+1个数
        else
            printf("%d/%d",i+n-j,j-n+1);//若i是偶数，第i条斜线上倒数第i个元素是(i+1-i)/i
        return 0;
}
```

---

## 作者：royzhu (赞：110)

/\*
找规律

第1层1/1

第2层1/2 2/1

第3层3/1 2/2 1/3

第4层1/4 2/3 3/2 4/1

第5层5/1 4/2 3/3 2/4 1/5

\*/
```cpp
#include<cstdio>
int main()
{
    int n;scanf("%d",&n);
    int t=1,ans=0;//t是表示下一次跳到下一次的距离，ans是表示第几层
    while(1)
    {
        if(n>t){n-=t;ans++;t++;}//printf("%d\n",ans);
        else if(n==t&&ans%2==0){printf("1/%d",ans+1);break;}
        //如果在n==t，并且为偶数层，就在第一行 第ans+1个 
        else if(n==t&&ans%2!=0){printf("%d/1",ans+1);break;}
        //如果在n==t，并且为奇数层，就在第ans+1行 第一个
        else if(n<t&&ans%2!=0){printf("%d/%d",ans+n-t+1,t-n+1);break;}
        //如果在n<t，并且为奇数层，t-n+1表示该层最后一个往后走n-1步，ans+n-t+1示该层最后一个往上走t-1步 
        else if(n<t&&ans%2==0){printf("%d/%d",t-n+1,ans+n-t+1);break;}
        // 如果在n<t，并且为偶数层，t-n+1表示该层最后一个往上走n-1步，ans+n-t+1示该层最后一个往后走t-1步 
    }
    return 0;
}
```

---

## 作者：wmxwmx (赞：90)

虽然说这道题是考**模拟**.但是为啥感觉很多人真的都在写模拟....


这道题应该是属于那种给个数据那台计算器都能手打出结论的题哈.


数据小了都不用计算器都能在初中数学范围之内吧。


很明显就是O(1)复杂度(~~这里忽略系统开根的复杂度~~)，求出Z形侧过来的三角形的行数


然后O(1)复杂度(~~又一次忽略系统乘法的复杂度~~)，算出结果。


以下是公式以及简要的解释


已知数据是第![](http://latex.codecogs.com/gif.latex?%5Clarge%20n)个。


明显Z形画出来的三角，从左上到右下的行数是从1开始公差为1的**等差数列**。所以利用**求和公式**，设**行数**为![](http://latex.codecogs.com/gif.latex?%5Clarge%20a)的话则有：


![](http://latex.codecogs.com/gif.latex?%5Clarge%20%5Cfrac%7Ba%5Ctimes%20%28a-1%29%7D%7B2%7D%3C%20n%5Cle%20%5Cfrac%7B%281&plus;a%29%5Ctimes%20a%7D%7B2%7D)


因此我们 设![](http://latex.codecogs.com/gif.latex?%5Clarge%20x)使得



![](http://latex.codecogs.com/gif.latex?%5Clarge%20%5Cfrac%7B%281+x%29%5Ctimes%20x%7D%7B2%7D%3Dn)


根据建立起的函数的**递增性**，可知![](http://latex.codecogs.com/gif.latex?a%3D%5Clceil%20x%5Crceil)


所以通过**求根公式**求出![](http://latex.codecogs.com/gif.latex?%5Clarge%20x)然后**向上取整**就可以在O(1)的时间复杂度求出行数了。


## Which is  ![](http://latex.codecogs.com/gif.latex?%5CLARGE%20a%3D%5Clceil%5Cfrac%7B-1&plus;%5Csqrt%7B1&plus;8%5Ctimes%20n%7D%7D%7B2%7D%5Crceil)


接下来，还要求出所在当行的具体位置，这个就很容易了，只需要知道 到![](http://latex.codecogs.com/gif.latex?a-1)那一行总共有多少个：明显![](http://latex.codecogs.com/gif.latex?%5Cfrac%7Ba%5Ctimes%20%28a-1%29%7D%7B2%7D)个


### 所以要求的也就是![](http://latex.codecogs.com/gif.latex?%5Clarge%20a)那一行的第![](http://latex.codecogs.com/gif.latex?n-%5Cfrac%7Ba%5Ctimes%20%28a-1%29%7D%7B2%7D)个。


接下来是一个对于知道**行数+第几个**的Cantor形式求法：

对于第a行，中所有个体，都有（“/”左边）+（“/”右边）![](http://latex.codecogs.com/gif.latex?%5Clarge%20=a+1)


同时 ![](http://latex.codecogs.com/gif.latex?%5Cforall%20a%5Cin%20N)，![](http://latex.codecogs.com/gif.latex?a%5Cequiv0%28mod%5C%202%29)





### 结果是： <u>(\_第几个\_ )/(a+1- \_第几个\_ )</u>

### <u>而剩下的则“/”**两边相反**即好。</u>

以上就是O(1)（~~其实应该没比二分快多少，相当于让系统做了二分而已~~）解决此题的详解。既然是数学推算，代码就不贴了，没啥意思。


---

## 作者：八个月想一等 (赞：80)

**蒟蒻首发**

~~这个题卡了我三天，用了各种脑残方法最后在~~@八重樱飞（十分感谢）~~的帮助下做了出来~~

~~这个方法真的简单~~

先是找规律

1/1（第一行）

1/2 2/1（第二行）

3/1 2/2 1/3（第三行）

1/4 2/3 3/2 4/1（第四行）

......

顺着看下来就是规律

注意一下每行的第一个数与层数是有关系的

上代码
```c
#include<iostream>
using namespace std;
int main(){
	int x,y,h=1,N,k;
    //x是分子，y是分母，h是行数，N是个数，k是 第N个数 与##~~~~ 对应行的第一个数 的距离（别卡在这，先往后看） 
	cin>>N；
	while(N>h){//用循环来算出行数 
	    N=N-h;
	    h++;
	}//很巧的是循环完后 N的值就是 第N个数对应行 的第几个（敲黑板）
	k=N-1;// 第N个数 与对应行的第一个数 的距离
	if(h%2==0)x=1+k,y=h-k;//判断行数是奇数还是偶数
	// （奇数：分子减k分母加k，偶数反之） 
	else x=h-k,y=1+k;
	cout<<x<<"/"<<y;//然后就算出来了 
	return 0;
}
```
祝各位早日AC

~~为什么我打一下回车显示出来只有一个空格~~

~~令人窒息的投稿~~


---

## 作者：water_lift (赞：62)

## 模拟就好，不要想多
数据太弱，不会卡TLE
先上代码
```cpp
#include<iostream>
#define osi ((x+y)%2==0) //判断x+y的奇偶性
using namespace std;
void nxt(int &x,int& y){//模拟函数，找出x/y的下一个数并存储在x/y中
	if(osi){
		if(x==1)y+=1;
		else x-=1,y+=1;
	}else{
		if(y==1)x+=1;
		else x+=1,y-=1;
	}
}
int main(){
	int n;
	cin>>n;
	int x=1,y=1;//第一个数
	for(int i=2;i<=n;i++)//从第二个数开始模拟，一直到第n个
		nxt(x,y);
	cout<<x<<'/'<<y;
    return -1;//防抄袭标记
}
```
## 解释
#### 1. 找规律：
|x/y|1|2|3|4|（y）|
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
|1|1/1|1/2|1/3|1/4|...|
|2|2/1|2/2|2/3|2/4|...|
|3|3/1|3/2|3/3|3/4|...|
|4|4/1|4/2|4/3|4/4|...|
|（x）|...|...|...|...|...|
不难发现，位于第x行第y列的数正是x/y。**所以在模拟时，只需移动坐标xy**。
#### 2. 接着找
|x/y|1|2|3|4|（y）|
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
|1|1/1（1）|1/2（2）|1/3（6）|1/4（7）|...|
|2|2/1（3）|2/2（5）|2/3（8）|...|...|
|3|3/1（4）|3/2（9）|...|...|...|
|4|4/1（10）|...|...|...|...|
|（x）|...|...|...|...|...|
不难发现，部分情况下，当x==1时，y+=1；y==1时，x+=1。做过八皇后问题的童鞋都知道，“/”对角线坐标特点是x+y为定值（不信可以试试）。可以看出，**x+y为偶数，x==1→y+=1；x+y为奇数，y==1→x+=1**。
#### 3. 继续找
|x/y|1|2|3|4|（y）|
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
|1|1/1（1）|1/2（2）|1/3（6）|1/4（7）|...|
|2|2/1（3）|2/2（5）|2/3（8）|...|...|
|3|3/1（4）|3/2（9）|...|...|...|
|4|4/1（10）|...|...|...|...|
|（x）|...|...|...|...|...|
不难发现，同样按照2的思路，讨论x+y的奇偶，可以得出**x+y为偶数，x-=1,y+=1；x+y为奇数，x+=1,y-=1**（去除2的特殊情况后）。
#### 4. 总结
可以得出如下代码
```cpp
if((x+y)%2==0){
	if(x==1)y+=1;
	else x-=1,y+=1;
}else{
	if(y==1)x+=1;
	else x+=1,y-=1;
}
```
## ~~好像有点啰嗦~~
~~其实本来想打表（没看数据范围）~~
<button type="button" onclick="alert('突然发现luogu可以用html代码!')">按钮</button>

---

## 作者：xytd (赞：25)

第一次发题解，内心非常鸡冻-。-

首先，最重要的一点是
要明白这道题的数排列的顺序

#### Z字型！

本蒟蒻就是被这东西卡了半天没过去

弄明白这一点，代码就比较好实现了

还有一个问题

就是每一行的公式 假设是奇数行的话，很明显是从左向右排列的 1/1,1/2,1/3,1/4,1/5, …

2/1,2/2,2/3,2/4, …

3/1,3/2,3/3, …

4/1,4/2, …

5/1, …观察这几行数（如果觉得不够直观，可以在纸上手动把它翻转一下，或者用exal），显然，奇数行的分子满足这样一个规律

分子=本层及以前所有数的数目和-n（即要求的编号）+1

那么也可以推出奇数行分母以及偶数行分子分母的公式

奇数行分母=cs-(tot-n)（tot即本层及以前所有数的数目和）

偶数行分子=cs-(tot-n) 偶数行分母=tot-n+1

下面贴出AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,cs=0,tot=0;//cs记录层数，tot记录到这一层总共有多少数 
    cin>>n;
    while(tot<n){
        cs++;
        tot+=cs;
    }
    if(cs%2==1)//当是奇数行时 
    cout<<tot-n+1<<"/"<<cs-(tot-n);
    else
    cout<<cs-(tot-n)<<"/"<<tot-n+1;
    return 0;
}
```
### 仅供参考

---

## 作者：Orange_JAMGO (赞：22)

面对各位大佬的神仙AC代码我不禁掩面痛哭

~~请忽略我这个垃圾萌新~~

于是我只好手动拆分本数表：

1/1  》1/2  》2/1  》3/1  》2/2  》1/3  》1/4  》2/3  》3/2  》4/1  》5/1 ......

然后手动寻找规律：
1/1  》（0/2） 》1/2  》2/1  》（3/0）》3/1  》2/2  》1/3  》（0/4）》1/4  》2/3  》3/2  》4/1  》（5/0）》5/1 ......

说白了，规律也不多：

（我们把本表向左旋转45度，再考虑本问题）

~~（我不管你们的电脑显示器能不能旋转，实在不行扭着脖子看）~~

1.奇行每次向后，分子增1，分母减1，偶行相反。

2.当分子/分母减为0时，分子/分母自增为1，奇行换为偶行

按照这个规律写出来的**萌新专属代码**（实在不行在纸上试着模拟这个程序也行，~~只要是知道C++基础语法的人，除了某些**睿智**应该都看得出来~~）如下：

```cpp
#include <iostream>
using namespace std;
int main()
{
    int cnt,l=1,y=1,x=1;//输出如下：x/y
    cin >> cnt;
    for(int i = 1;i<cnt;i++)
    {
        if(l%2 == 1)
        {
            x--;
            y++;
            if(x == 0)
            {
                x++;
                l++;
            }
        }
        else if(l%2 == 0)
        {
            x++;
            y--;
            if(y == 0)
            {
                y++;
                l++;
            }
        }
    }
    cout << x << '/' << y;
    return 0;
}
```

**~~请原谅我小学奥数般的清奇思路~~**


---

## 作者：辣鸡光黄照耀 (赞：19)

好像没有人跟我一样用暴力求解法啊……发一个~~，简洁明了~~！
```
#include<iostream>
int main(){
	long n,a=1,b=1,i=2;//i初始化必须为2，否则出错（当然你如果有解决办法1或0也可以）
	bool judge=true,become=false;//judge不得为false，否则一开始就错了
	std::cin>>n;
	while(i<=n){
		if(judge&&a==1){
			judge=false;
			b++;
			become=true;//这个变量是变换分母分子的关键点
		}
		else if(!judge&&b==1){
			judge=true;
			a++;
			become=true;
		}
		if(become)i++;//因为是替交，所以无需再像下面操作
		else if(judge){//分母增加分子减少
			a--;
			b++;
			i++;
		}
		else{//分子增加分母减少
			a++;
			b--;
			i++;
		}
		become=false;//不要忘，否则上面的if(become)一直为真则出错
	}
	std::cout<<a<<'/'<<b;
	return 0;
}
```

---

## 作者：xun_xun (赞：9)

**惊奇的发现这题没有硬算的题解，作为数学的爱好者，我怎么会放过这个机会呢？**

[原题传送门](https://www.luogu.com.cn/problem/P1014)

 题目大意：有一个名为 Cantor 表的表，要输出表的第 $n$ 个数。~~这不废话吗。~~

首先，将 Cantor 表沿题目的顺序分组，每条斜线为一组，则 $\{1/1\}$ 为一组，$\{1/2、2/1\}$ 为一组……此时，每组有理数个数为 $1$、$2$、$3$……如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/gk89hrkz.png)

再假设第 $n$ 个有理数属于第K组，通过等差数列求和公式可以得到第 $K$ 组之前数的个数为：$\frac{(K-1)\times K}{2}-1$，故 $n$ 和 $K$ 的关系为： 

$ \frac{(K-1)\times K}{2}<n\le\frac{(K+1)\times K}{2}$

使 $n=\frac{(k-1)\times k}{2}+1$（$k$ 是有理数）。当 $n$ 为第 $K$ 组的第一个有理数时，此时的 $k$ 就是 $K$，是整数，我们尝试用 $n$ 来表示 $k$ 。

$$
\begin{aligned}
2n-2&=(k-1)\times k\\
2n-2&=k^2-k\\
2n-2+\frac{1}{4}&=k^2-k+\frac{1}{4}\\
2n-2+\frac{1}{4}&=(k-\frac{1}{2})^2\\
\sqrt{2n-2+\frac{1}{4}}&=k-\frac{1}{2}\\
k&=\sqrt{2n-2+\frac{1}{4}}+\frac{1}{2}
\end{aligned}
$$   

那当 $n$ 不是第 $K$ 组的第一个有理数时，由于 $n$ 介于第 $K$ 组和 $K+1$ 组的第一个有理数之间，所以

$ \frac{(K-1)\times K}{2}+1<\frac{(k-1)\times k}{2}+1<\frac{(K+1)\times K}{2}+1 $

算得的 $k$ 是一个介于 $K$ 和 $K+1$ 之间的分数。所以用 $\lfloor a \rfloor$ 强行向下取整即可硬算出 $n$ 的组别：

$K= \lfloor k \rfloor =\lfloor\sqrt{2n-2+\frac{1}{4}}+\frac{1}{2}\rfloor$

求完 $n$ 的组别 $K$ 后可以用 $n$ 减去前 $K-1$ 组的数量 $(K-1)\times \frac{K}{2}$ 得到 $n$ 在第 $K$ 组的位置（$n$ 是第 $K$ 组的第几个），$K$ 是偶数时分子递增，分母递减；奇数时相反，分完 $K$ 的奇偶性后直接输出答案就好（本人在讨论板发现有很多代码输出的分子分母是反的，请小心这个细节）。

**AC code**
```cpp
#include<bits/stdc++.h>
using namespace std;
float n;
int main(){
	cin>>n;
	int k=int(sqrt(n*2-1.75)+0.5);
	n-=(k-1)*k/2;
	if(k%2==1) cout<<k-n+1<<'/'<<n;
	else cout<<n<<'/'<<k-n+1;
    return 0;
}
```

---

## 作者：HZAUqzx (赞：7)


先观察一下这个 Cantor表

会发现在每一条从左下到右上的斜线上的横纵坐标之和是一个定值
确切的说就是这条线两端点的坐标值

再看第一行是一个等差差数列（差值为等差数列的数列）

那么就可以查找第一行来确定n所在的斜线的位置
然后将n与端点坐标作差找到n的坐标

现在用i模拟第一行数的值
j为i的增量（用以求下一个i，可以减少计算）

直到找到n所在的斜线位置就输出
（并不用判断奇数或偶数）


代码如下

```cpp
#include <iostream>
using namespace std;
long long n, i, j;
int main(){
	cin>>n;

	loop:
		if(i+j>=n) cout<<j+i-n+1 <<"/"<< n-i;
		else{	i=i+j, ++j;
	goto loop;}

	return 0;
}
```

---

## 作者：sqc1999 (赞：6)

有必要那么麻烦吗，4行代码搞定，不解释。。

```cpp

    long long n,a;
    cin>>n;
    for (long long i=1;i<=10000000;i++) if (n-i<=0) {a=i; break;} else n-=i;
    if (a%2==0) cout<<n<<"/"<<a-n+1; else cout<<a-n+1<<"/"<<n;

```

---

## 作者：铃铛 (赞：5)

```c
int main(){
	int pos,add=0,i;
	scanf("%d",&pos);
	for(i=1;;i++){
		add+=i;
		if(add>=pos) break;
	}
	int d=add-pos;
	printf("%d/%d",1+d,i-d);
	return 0;
}

//大概的意思就是，它每一行都是1，2，
//3这样增加的。那就累加到行数大于其位
//数。最后算出位数和行数的差d，因为每
//行i末尾的位置都是（1，i）；和它相差
//d的位置就是（1+d，i-d）
```

---

## 作者：Zn_Hua (赞：5)

在每个转折点找一找规律，可以发现

- 当分母为偶数分子为1时向下走

- 当分子为奇数分母为1时向上走

- 若分子分母某一个为1但另一个不符合以上情况时另一个就+1

Z型的循环加几个if就好了，用两个变量做分子和分母

```cpp
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;
int main()
{
    int n,a=1,b=1;
    cin>>n;
    for(int i=1;i<n;++i)
    {
        if(b%2!=0&&a==1)b++;
        else if(a%2==0&&b==1)a++;
        else if((a+b)%2!=0){b--;a++;}
        else if((a+b)%2==0){b++;a--;}
    }
    cout<<a<<"/"<<b;
    return 0;
}
//很简单的题，刚学不久的可以看一看

```

---

## 作者：Ufowoqqqo (赞：5)

模拟水过，此题最重要的是发现规律。

```delphi

var
 n:longint;

function work(num:longint):longint;
var
 t,i:longint;
begin
 t:=num;
 i:=0;
 while i+t<n do
 begin
  inc(i,t*2-1);
  inc(t,2)
 end;
 if i<n then work:=n-i else work:=i-n+1
end;

begin
 read(n);
 write(work(1),'/',work(2))
end.

```

---

## 作者：发源于 (赞：4)




#[color=red]枚举[/color]

呵呵！就是枚举

数据太小

O(N)能过

本题标程存在于1366题看程序写结果3中

而且那还有很多没必要的

标程如下

```delphi

var i,j,k,n:longint;
begin
     readln(n);
     k:=1;
     i:=1;j:=1;
     while k<n do
     begin
          if (i=1) and (j mod 2=1) then inc(j)
          else if (j=1) and (i mod 2=0) then inc(i)
          else if (i+j) mod 2=0 then begin dec(i);inc(j);end
          else if (i+j) mod 2=1 then begin inc(i);dec(j);end;
          inc(k);
     end;
     writeln(i,'/',j);
end.

```

---

## 作者：Jonas_Max (赞：3)

思路：首先看了一下数据范围，不是很大，可以采用模拟的方法直接暴力求解分子和分母。从0开始左上进入口按Z字按规律“遍历”Cantor表。

如果同时找分子和分母规律的话不是很好找，这里选择分开找。

首先分子，可以发现分子的循环规律：1 2 1/1 2 3 4 3 2 1/1 2 3 4 5 6 5 4 3 2 1/...... 每一次循环的最大值加2且为偶数，第一次base=2。

分母类似，循环规律为：1 /1 2 3 2 1/ 1 2 3 4 5 4 3 2 1/1 2 3 4 5 6 7 6 5 4 3 2 1/...... 每一次循环的最大值加2且为偶数，第一次base=1。


附上代码：




```cpp
#include <stdio.h>
int molecule;//分子
int denominator;//分母
void solve1(int n)//求解分子
{
    int base=2,i,cnt=0,flag=0;//第一个循环中最大为2
    while(!flag)
    {
        for(i=1;i<=base;i++)
        {
            cnt++;
            if(cnt==n)//遍历到正确位置
            {
                flag=1;
                molecule=i;
                break;
            }
        }
        if(flag)return;
        for(i-=2;i>=1;i--)//上一个for循环中最后多自加了一次，这里要减2
        {
            cnt++;
            if(cnt==n)
            {
                flag=1;
                molecule=i;
                break;
            }
        }
    base+=2;
    }
    return;
}
void solve2(int n)//求解分母
{
    int base=1,i,cnt=0,flag=0;//第一个循环中最大为1
    while(!flag)
    {
        for(i=1;i<=base;i++)
        {
            cnt++;
            if(cnt==n)
            {
                flag=1;
                denominator=i;
                break;
            }
        }
        if(flag)return;
        for(i-=2;i>=1;i--)
        {
            cnt++;
            if(cnt==n)
            {
                flag=1;
                denominator=i;
                break;
            }
        }
    base+=2;
    }
    return;
}
int main()
{
    int n;
    scanf("%d",&n);
    solve1(n);//求解分子
    solve2(n);//求解分母
    printf("%d/%d",denominator,molecule);
    return 0;
}
```

---

## 作者：PTC06 (赞：3)

比较简单的一道题，自己感觉思路是众多题解中较简单的。一开始时25分是因为没有看到题目中的“Z字形”。

思路：

把图转一下，变成

1/1
2/1  1/2

3/1 2/2 1/3

...
可以看出，第一行有1个数，第二行2个数，第三行3个数，第n行n个数。那么，很容易求出一个数在第几行，以及它在这行中的位置：

```cpp
    for (i=1;;i++)
    {
        tem+=i;    //每次加i，因为第i行有i个数。
        test=tem-i;   //减去i，表示前面行数里面数字的个数的总和。
        if (test<=n && n<=tem)  //如果前面行数里数字的总和比这个数字本身小，而这个数又比tem加上这个行的数字个数小，说明这个数字在第i行。
        {
            tem-=i;   //tem减去i，成为这个数字之前的所有行的数字个数的总和。
            break;
        }
    }
```
现在求出了它所在的行，也知道了在这行之前的数字的个数，就可以用这个数字减去tem，求出它在这行的位置。我们暂时把它的位置当作分子。
    temp=i+1;       

    first=n-tem;

接下来，因为不难看出，每一行的分数的分母和分子的和是一样的。那么用行数+1（每行的第一个分数的分子=1，分母=行数。）减去分子就得到分母了。

最后，由于只有在偶数行时分母才等于位置，而奇数行则刚好相反，所以最后输出是：

if (i%2==0) cout<<first<<'/'<<second; else cout<<second<<'/'<<first;

下面是程序：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,tem,test,first,second,ceng,temp;
int main()
{
    cin>>n;
    for (i=1;;i++)
    {
        tem+=i;
        test=tem-i;
        if (test<=n && n<=tem)
        {
            tem-=i;
            break;
        }
    }
    temp=i+1;
    first=n-tem;
    second=temp-first;
    if (i%2==0) cout<<first<<'/'<<second; else cout<<second<<'/'<<first;
}
```

---

## 作者：野菜汤 (赞：3)

题解：

规律！这题其实是简单无比的。它的例图看起来虽然奇怪，但只要倒转一个方向，那么

原图应为：[color=red] 1/1

2/1    1/2

3/1   2/2     1/3

………………[/color]

```delphi
var i,j,k,m,n:longint;
begin
  read(n);{读入}
  m:=1;
  while n>m do
  begin
    n:=n-m;{这一步十分关键，通过规律找出第n项所处的位置}
    inc(m);{记录第n项的所在行数}
  end;
  if m mod 2<>0 then write(m-n+1,'/',n)
else write(n,'/',m-n+1);  {按规律输出第n项的数值，注意因程序原因单双数行为反向}
end.

```

本题的解题思路也是十分容易理解的。首先，第n项所在第几行，再加上它在这一行的位置，就可以求出其数值。

那么规律在这里也详细说明：首先是‘/’左边的数，是由行数顺次减一，直到一，右边的数就是从1顺次一直加到当前的行数。

[color=red]在此致歉，因为个人疏漏以及数据点太弱的原因导致原题解在一定基础上误导了各位同学，于是表示诚挚的歉意。其实单双数输出相反这个问题出在程序上，主要是由程序导致的，因为双数行有偶数个数字，而单数行有奇数个数字，故倒向输出。[/color]


---

## 作者：cxh125011501 (赞：3)

数据有点水，我知道O(n)就能过，但1999年的机器这个复杂度可是过不了的，我发个O(n^0.5)的算法，本题还有O(1)算法，等差数列前n项和还有求根公式一起用就可以得出O(1)算法，请大家思考一下，这里不再给出代码。

```cpp
#include<iostream>
using namespace std;
int h(int n){
    int i=1;
    while((i-1)*i/2<n){
        ++i;
    }
    return i-1;
}
int n,l;
int main(){
    while(cin>>n){
    int h=h(n);
    l=n-h*(h-1)/2;
    if(h%2==0)cout<<l<<"/"<<(h+1-l)<<endl;
    else cout<<(h+1-l)<<"/"<<l<<endl;
    }    
}

```

---

## 作者：NKwx_t (赞：2)

# p党福利
#### 第一次发题解
#### 看大佬的方法比较神奇
#### 我的方法应该比较好懂
###### 贴代码


------------
```pascal
var
k,n,s:longint;                                        //k表示数n之前有几排（斜的，具体看下面图）
begin
readln(n);
k:=1;
while k*(k+1)<2*n do k:=k+1;                          //等差数列前k项和s=k(k+1)/2
k:=k-1;                                               //while判断K多加1
s:=trunc(k*(k+1)/2);                                  //求出前一排有多少个
if (s=n) and (k mod 2=0) then writeln(k,'/1')         //s=n时
else if (s=n) and (k mod 2=1) then writeln('1/',k)    //s<>n时
else if s<>n then begin
	if k mod 2=0 then writeln(k+2-n+s,'/',n-s)
	else if k mod 2=1 then writeln(n-s,'/',k+2-n+s);
end;
end.
```
![cantor表](https://ss1.bdstatic.com/70cFuXSh_Q1YnxGkpoWK1HF6hhy/it/u=4091229260,2329352389&fm=27&gp=0.jpg)
第一次发题解感觉有点乱
希望有帮助


---

## 作者：Corrine (赞：2)

本弱驹代码，大神们见笑了！

首先，拿到题目，可以看一下题目中给的数字，发现特别有规律，那么大概可以却定这道题是找规律性的题目，然后，就可以顺着找规律的思路继续。

我们可以将题目中给的数字重新组织一下，可以更加清晰的看出规律：

1/1
2/1  1/2

3/1  2/2   1/3

4/1  3/2   2/3   1/4

ok,这样看起来就更加容易发现规律了，可以发现，每行分子或分母最大数字就是行数，而从左往右看，奇数行和偶数行增加的规律刚好相反，用两个变量i,j描述行和列,就可以看出规律：

偶数行：从右往左：分子=j; 分母=i-j+1

偶数行：从左往右：分子=i-j+1; 分母=j

好的，规律看出来了，代码就好写了

下面上代码

```cpp
#include<cstdio>
int main()
{
    int n,k,s;            //前k挑斜线一共s个数
    scanf("%d",&n)    
    k=0;
    s=0;
    while(s<n)        //找到最小的k使得s>=n
    {
        k++;
        s+=k;
    }
    if(k%2==1)        //k的奇偶决定着斜线上数的顺序,n是第k条斜线上倒数第s-n+1个数
    printf("%d/%d\n",s-n+1,k+n-s);    //若k是奇数，第k条斜线上倒数第i个元素是i/(k+1-i)
    else
    printf("%d/%d\n",k+n-s,s-n+1);    //若k是偶数，第k条斜线上倒数第i个元素是(k+1-i)/i
    return 0;
}
```

---

## 作者：ingu (赞：2)

做为新手村的最后一道题，这道题不算难，但很值得去思考。

思路1：模拟

此题类似蛇形填数，首先要设置好运行的轨迹，轨迹可以使用di[4][2]这样的方向数组来保存，与蛇形填数不同的是，其中两个方向只走一步，所以要判断一下方向。

```cpp
#include <iostream>
using namespace std;
int main()
{
    int di[4][2]={-1,1,0,1,1,-1,1,0},n,s=0,i=2,j=0;
    cin>>n;
    while (s<n) {
        for (int k=0; k<4; k++) {
            while (i+di[k][0] && j+di[k][1]) {
                i+=di[k][0];
                j+=di[k][1];
                s++;
                if (n==s) {
                    cout<<i<<'/'<<j<<endl;break;
                }
                if (k%2==1) {
                    break;
                }
            }
        }
    }
    return 0;
}
```
思路2：直接计算

从题目中稍加分析，可以得到这样的一个图形

1行：1/1

2行：1/2  2/1

3行：3/1  2/2  1/3

4行：1/4  2/3  3/2  4/1

5行：5/1  4/2  3/3  2/4  1/5

可以看出一些规律：1、第k行，有k个数；2、第k行，每对数之和是k+1； 3、奇数行从k开始，偶数行从1开始。

有了这些规律，只需要判断出n在第几行，第几个位置便可以按照奇偶直接输出结果。参考代码：

```cpp
#include <iostream>
using namespace std;
int main()
{
    int n,i=1;
    cin>>n;
    while (n>=i+1) {
        n-=i++;
    }
    if (i%2) {
        cout<<i+1-n<<'/'<<n<<endl;
    }else{
        cout<<n<<'/'<<i+1-n<<endl;
    }
    return 0;
}

```

---

## 作者：eagadsgbsadfhb (赞：2)

[c语言]

```cpp
#include<stdio.h>
int main(){
    int n,j;
    scanf("%d",&n);\输入不解释
    j=1;
    while (n-j>0)
        n=n-j++;\判断是在第几斜行
    if (j%2==0) \记得mod 2是0与是一不同
        printf("%d/%d",n,j-n+1);\是0是往↙的，第n项为n/j-n+1
        else printf("%d/%d",j-n+1,n);\是1是往↗的，第n项为j-n+1/n(与mod2=0的相反)
    return 0;
}
```

---

## 作者：冰翼ACE (赞：2)

这题的重点在发现规律

确定区间长度的方法见注释

我们发现，区间长度+1为分数分母分子之和，而分母就是这个数在这个区间的位置，分子为和减分母

比如样例的7，它在区间【7，8，9，10】中，此时分母分子和为i+1=5，7在区间中的位置为7-7+1=1,所以它的分母为1，分子为和6减分母1为4，输出4/1，样例是错的！！！！

按照NOIP1999普及组原数据，题的顺序为：

1/1
2/1 1/2

3/1 2/2 1/3

4/1 3/2 2/3 1/4

……
而不是像题干中说的那样。

代码如下：

```cpp
#include<stdio.h>
int i=1,s=1,n;//i为区间长度,s为头指针 
int main()
{
    scanf("%d",&n);
    while(1)
    {
        if(n>=s&&n<=s+i-1)//区间长度为分子分母和减1 
        {
           int sum=i+1,place=n-s+1;//place为该数在数列中的位置
           int a1=place,a2=sum-place;//分母，分子
           printf("%d/%d",a2,a1);
           return 0;
        }
        else
        {
            s+=i;//头指针右移 
            i++;//区间长度递增 
        }
    }
    return 0;
}
```

---

## 作者：CoolTeam (赞：2)

刘汝佳的《算法竞赛入门经典》有这题。

其中有一方案是用代数方法。

k代表斜着看的第k列

sk代表前k项的数量。

```cpp
#include<stdio.h>
#include<math.h>
int main(void)
{
    int n,k,sk;
    scanf("%d",&n);
    k=floor( (sqrt(8*n+1) -1 ) /2 -1e-8) +1  ;
    sk=k*(1+k)/2;
    if(k%2==1)
        printf("%d/%d",sk-n+1,k+n-sk);
    else
        printf("%d/%d",k+n-sk,sk-n+1);
    return 0;
}

n<=sk=1+2+……+n=k(k+1)/2. 得出k关于n的代数式。

```

---

## 作者：YZ_DDF (赞：1)

我的做法比较简单易懂，Contar是走蛇形的（新手指引），具体怎么走很多dalao也说过了。

//无限枚举

i（n<=10000000把我吓到了），不难发现，对于contar表这个三角形，按斜线看，第几列就在斜方向有几个数，而且从右上到左下，都有从大到小的数字顺序。就可以确定“/”右边的数字，**i-sum+n**<==>**i-(sum-n)**，这一列的序号从上到下按数字从小到大排列，就可以得出“/”左边的数字是**i-p1+1**<==>**i-(p1-1)**<==>**sum-n+1**。答案就出来了。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main(){
    int n;
    long long i=1,sum=0;
    scanf("%d",&n);
    for(;i<=1000000000000;i++){
    	sum=sum+i;
    	if (sum>=n) break;
    } 
    int p1,p2;
    p1=i-sum+n;
    p2=i-p1+1;
    printf("%d/%d",p2,p1);
    return 0;
}
```
虽然不是正解，但是思维难度简单，就是找找规律

---

## 作者：被袭胸的炮姐 (赞：1)

/\*
这是数字

1/1
2/1 1/2

3/1 2/2 1/3

4/1 3/2 2/3 1/4

5/1 4/2 3/4 2/4 1/5

这是第几个

1
3 2
4 5 6
10 9 8 7

11 12 13 14 15

可以看出,第n行所有的分子分母的和是n+1

\*/


```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
int main()
{
    int p,n=0,i;
    scanf("%d",&p);
    for(i=1;;i++){
       n+=i;
       if(p>=n-i&&p<=n)//找出所在行数,此行最小的编号是n-i,最大编号是n
       break;
       }
    printf("%d/%d",i+1-(p-n+i),i+1-(i-(p-n+i-1)));
    //i+1是此行分母和分子的和,减去p-n+1就得到了分子的数值
    //i+1减去上式就是分母
    return 0;
}

```

---

## 作者：究极yts (赞：1)

**这样想也挺好，很简洁。把数表顺时针旋转45度，再右对齐。观察分子分母的变化规律，即可；需要注意的是“换行器“###的使用；**

```cpp
#include<iostream>
using namespace std;
int main()
{
    int n;
    cin>>n;    //  读入 
    int a[n],b[n],w=1,s=1,i;     //定义换行器 
    for(i=1;i<=n;i++)
    { 
        if(w==s) {w=1;s++;}           // 记录行数等等 
        if(s%2==1){a[i]=w;b[i]=s-w;}
        else{a[i]=s-w;b[i]=w;}
        w++;
    }
    cout<<a[n]<<"/"<<b[n];
    return 0;
}
```

---

## 作者：qwaszx (赞：1)

让我们见证一下O(1)算法的降临。。。。。。

具体思路呢大概就是最快的办法，输入n，找到1+2+3+...+i>=n的第一个数并且保存和s。

然后s-=i，这样就保证比n小了。

接下来就看看规律了：

当这个i是偶数的时候（比如输入7，i就等于4），是从右上到左下排列；而奇数的时候，是从左下到右上排列的。并且分子分母之和为i+1.

所以呢，就要分两种情况：

偶数时，分子上是读入的n减去已经处理过的和s，分母上就是用总和（i+1）减去这个数，即i+1-(n-s)。所以这个数就是(n-s)/(i+1-n+s).

奇数时，情况正好是偶数时的倒数，即(i+1-n+s)/(n-s).

这就是基本思路。如果你用循环做的话大概不到sqrt(n)就够了。算得精确点就是floor((sqrt(1+8n)-1)/2)+1次。

但是你知道我这结果怎么得出来的么。。。。。。

用一个一元二次方程来求解我们的i，即i(i+1)/2=n

化成一般形式得n^2+n-2s=0

然后无脑公式法。。。

就得到了(sqrt(1+8n)-1)/2.

并且我们知道误差不会超过1，所以直接用floor。

这样，就可以通过公式直接得到我们的i以及s。

完美啊。。。。。。

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
int main()
{
    int n,s;
    cin>>n;
    int i=floor((sqrt(1+8*n)-1)/2);
    s=i*(i+1)/2;
    if (n==s)
        s-=i;
    else
        i++;
    if (i%2)
        cout<<i+1-n+s<<'/'<<n-s;
    else
        cout<<n-s<<'/'<<i+1-n+s;
} 
传说中的O(1)算法【注：这是指常数级别，即没有一个循环】
```

---

## 作者：Rumia (赞：1)

可以观察发现，每一个斜行（设为i）开始，分母（设为a）都为行数，分子（设为b）都为1，然后当b<i时，a自加，b自减。

根据这个规律就可以用很短的代码解决问题

```cpp
 #include<iostream>
 using namespace std;
 int main(){
    int a,b,i=1,n;
    cin>>n;
    while(n) for(a=i++,b=1;--n&&b<i-1;a--,b++);             //i代表行数 a为分母 b为分子 
    cout<<a<<'/'<<b;
    return 0;
 }
```

---

## 作者：littleming (赞：1)

很简单的一道题，找规律就可以了




```cpp
#include<iostream> 
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<string> 
#include<algorithm>
using namespace std;
long long n,sum=0,i=1,k;                                            //和为i 
int main()
{
    cin>>n;
    while(sum+i<n)
    {
        sum+=i;i++;
    }
    i++;
    k=n-sum;
    if(i%2==1)    cout<<k<<"/"<<i-k<<endl;                            //从小到大 
    else         cout<<i-k<<"/"<<k<<endl;                            //从大到小 
    return 0;
} 

```

---

## 作者：zero4eva (赞：1)

测试数据有点水。第一项1/0是可以过得。。

就算不找到规律，枚举也都能过，只是个人原因，喜欢找规律= =

都是以横向为基础来展开的，b为分母，a为分子，i逼向n。

你会发现b为奇数时，i+=1，b为偶数时，i+=t,而t又每次i加过之后t+=4。

找到第一行中不大于n的最大i后，再判断b奇偶确定是i--找n，还是i++找n。

代码如下：

```cpp

#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    
    int oi,i,t,a,b;
    i=1,t=4,b=1;
    
    while (i<n)
    {
        oi=i;
        if(b%2 == 0) i+=t,t+=4;
        else i++;
        b++;
    }
    
    if (i==n)
    {
        printf("1/%d\n", b);
        return 0;
    }
    else 
    {
        if (b%2 == 0)
        {
            i=oi,b--;
            for(a=1; b>0&&i!=n; a++,b--,i++);
        }
        else
            for(a=1; b>0&&i!=n; a++,b--,i--);
    }
    
    printf("%d/%d", a, b);
    
    return 0;
} 

```

---

## 作者：jsjhfx (赞：1)

### 完全模拟走$Z$字的过程。
`r`表示当前**row**, `c`表示当前**column**。`up`用来判断$Z$字型走向是**自下而上还是自上而下**。每当**“碰壁”**后将改变`up`的值。`count`用来记录已经走过的值的数量。

下面是`java`实现。
```java
import java.io.*;
import java.util.*;
class Main{
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int N = scan.nextInt();
        int r = 0; int c = 0;
        boolean up = true;
        int count = 1;
        while(count < N){
            if(up){
                if(r==0) up = false;
                else r--;
            }
            else{
                if(c==0) up = true;
                else c--;
            }
            c++;
            count++;
        }
        System.out.println((r+1) + "/" + (c+1));
    }
}
```


---

## 作者：Continue (赞：1)

#模拟即可

##由题意可知，移动方向有四种：

1.向右移动。

2.向下移动。

3.向左下方移动。

4.向右上方移动。

那么此题可采用模拟的方法。

```cpp

#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
    int n;
    scanf("%d",&n);
    int i,j,k;// 用 i/j 表示每一个组合,k 计数 
    i=j=k=1;// 初始化 i j k 
    while(k<n)// 当个数未达到 n 个时，继续循环。以下模拟四种情况 
    {
        if(i==1&&j%2==1)// 当处于第一行，且 j 为奇数 
        {
            j++;k++;// 则向右移动 
        }
        else if(j==1&&i%2==0)// 当处于第一列，且 i 为偶数 
        {
            i++;k++;// 则向下移动 
        }
        else if((i+j)%2==1)// 当 i+j 为奇数 
        {
            i++;j--;k++;// 向左下方移动 
        }
        else// 当 i+j 为偶数 
        {
            i--;j++;k++;// 向右上方移动 
        }
    }
    printf("%d/%d",i,j);// 利用格式化输出输出 
    return 0;
}

```

---

## 作者：Forgetter (赞：0)

很简单的一道题，题目读懂就可以了
思路其他解题我看差不多。
直接上java代码。
```java
import java.io.BufferedInputStream;
import java.util.Scanner;

public class P1014 {
	static int k;
	public static void main(String[] args) {
		Scanner sc = new Scanner(new BufferedInputStream(System.in));
		while(sc.hasNext()){
			k = sc.nextInt();
			hang(xie());
		}
	}
	public static void hang(int n){
		int m = 0;
		int d = k-Sum(n-1); //相对于之前，这一斜线增加了几个
		if(n%2==0){	//斜线为奇数  向右上
			m = d;
			n = n-d+1;
		}	
		else {		//斜线为偶数  向左下
			m = n-d+1;
			n = d;
		}
		System.out.println(m+"/"+n);
	}
	
	//判断是哪一个对角线  n
	public static int xie(){
		int n = 0;
		while(Sum(++n)<k);
		return n;
	}
	
	//1+2+……+n  
	public static int Sum(int n ){
		int sum =0;
		sum=n*(n+1)/2;
		return sum;
	}

}

```

---

## 作者：FlyingAnt (赞：0)

观察这道题。

发现每一行数字个数都是和这行的编号一样的（第一行1个。第二行2个。。。

所以我采用的是求前n项和的方式，

求出到这一行所有的数的个数，即此行最后一个数的编号。

当编号大于所求的数的个数时。停止。

记录本行数字的个数。

设上一行所有数字个数和为sum1，同时代表了在上一行末尾数字编号为sum1；

设本行有t个数。同时代表是第t行。

仔细观察，会发现。

偶数行：分子与编号符合规律：n-sum1.分母与编号符合规律：t-(n-sum1)+1

奇数行：分母与编号符合规律：n-sum1.分子与编号符合规律：t-(n-sum1)+1

按要求输出即可。

付ac代码。（有注释）


```cpp
#include<iostream>
using namespace std;
int main()
{
    int n,sum=0,t,sum1;//题目要求的n，本行最后一个数的编号sum 
                                       //上一行最后一个数的编号sum1，本行数字个数t
    cin>>n;
    for(int i=1;;i++)//找在第几行t和sum1，sum；
    {
        sum+=i;
        t=i;
        if(sum>=n)
        {
            sum1=sum-i;;
            break;//跳出循环
        }
    }
    if(t%2==0)//奇数情况
    {
        cout<<n-sum1<<"/"<<t-(n-sum1)+1;
        return 0;
    }
    else //偶数情况
    {
        cout<<t-(n-sum1)+1<<"/"<<n-sum1;
        return 0;
    }
}
```

---

## 作者：封禁用户 (赞：0)

强烈建议：先自己写一下Cantor数的规律，再看题解及代码。

别人的题解：本题采用的循环遍历的方法，下面附上ac代码。

我的题解：数学方法，附代码：

```cpp
#include<iostream>
using namespace std;
main()
{
    int n,j=1;
    cin>>n;
    while(n-j>0)n-=j++;
    if(j%2==0)cout<<n<<"/"<<j-n+1<<endl;
    else cout<<j-n+1<<"/"<<n<<endl;
    return 0;
}
```

---

## 作者：漓江塔塔主 (赞：0)

\_\_\_\_\_\_\_其实我们可以把这道题放到矩阵中去想\_\_\_\_\_\_\_

———————————————————————

1     2     3     4     5     6     ........  （X轴）

1  ①   ②   ④   ⑦    ...

2  ③   ⑤   ⑧    ...

3  ⑥   ⑨    ...

4  ⑩    ...

5   ...

......
（Y轴）

————————————————————————

上图可知，每走一步 X-1，Y+1；

当X=0时，为一轮，也就返回Y=1；X为上一轮X+1；

于是我们可以单独记一下每轮的X，再记一个每轮走的XX；

于是乎~~~~代码出现了~~~~

————————————————————————





```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int x,z,tot=1,n,yy,xx;
int main() {
    scanf("%d",&n);
    x=1;                    // x记的是每一轮的X的数值；
    xx=x;                  
    yy=1;                  //      从1，1开始走第一步
    while(1){
        if(tot==n)      //   tot记的步数，当走够时跳出；
            break;        
        xx--;
        yy++;          //     每走一步的坐标；
        if(xx==0){
            x++;
            xx=x;
            yy=1;
        }                     ////         判断这一轮走完！！！！！！
        tot+=1;          //       记步数~~~~
    }
    cout<<xx<<"/"<<yy;    //   神奇的输出答案~~~~~
    return 0;      //完美结束~~~~~~
}

```

---

## 作者：Q小Y (赞：0)

其实这道题并不难，centor表是以z字型标号排序的

奇数列斜向上，偶数列斜向下。规律就出来了。

上代码，说实话，真心好短。（不用数组）

```cpp
var
  i,j,n:longint;
begin
  read(n);
  i:=0; j:=n;
  repeat
    inc(i);
        j:=j-i;
  until j<=0;
  j:=j+i;
  if i mod 2=0 then write(j,'/',i+1-j)
    else write(i+1-j,'/',j);
end.
```

---

## 作者：shenyi1343395317 (赞：0)

虽然和大神比起来差远了，但是我还是想来讲一讲我自己的方法.

这题我用数组做，然后找规律

斜着找，我们就会发现 奇数斜向上增加 偶数斜向下增加

通过过程来实现

```cpp
program sss;
  var a:array[-80..1000,-580..1000] of longint;
      i,j,k,ans,n:longint;
      f:boolean;
  procedure xie(n:longint);
  begin
  if (n mod 2)=0 then                   // 偶数斜
   begin
   a[1,n]:=a[1,n-1]+1;
   for i:=2 to n do a[i,n-i+1]:=a[i-1,n-i+2]+1;
   end else                                    //奇数斜
   begin
   a[n,1]:=a[n-1,1]+1;
   for j:=2 to n do a[n-j+1,j]:=a[n-j+2,j-1]+1;
    end;
   end;
  begin
  readln(n);
  a[1,1]:=1;
  if (n=1) then begin write('1/1'); exit; end;  //第一个太麻烦了，直接暴力掉
  for i:=2 to 1000 do
   begin
   xie(i);
   k:=i+1;
   j:=0;
   repeat
   dec(k);
   inc(j);
   if (a[k,j]=n) then begin write(k,'/',j); exit; end;
   until k=1;                                                      //这里费劲心思优化了一下，斜着判断，减少判断次数
   end;
  readln;
  end.

```

---

## 作者：冰冻赤道 (赞：0)

/\*简单的运算；

“z”型循环，

1/1
1/2 2/1

3/1 2/2 1/3

1/4 2/3 3/2 4/1

...
可知奇数行，分子为1，一直加到 行数，分母为行数一直减到1；

偶数项相反；


\*/
    


        
```cpp
#include<iostream>
using namespace std;
int main()
{
    int a,s,i=1;
    cin>>a;
    while(i){
        a-=i;            //计算 a是在第几行停； 
        if(a<=0){
            a+=i;        // 将a恢复到进入这一行时的初始数 
            s=i;        //记录行数；    
            break;
        }
        i++;
    }
    for(int i=1,j=s;i<=s,j>=1;i++,j--){
        a--;
        if(a==0&&s%2==0)    cout<<i<<"/"<<j;//判断行数为奇数还是偶数，偶数输出i  “/”  j； 
        if(a==0&&s%2!=0)    cout<<j<<"/"<<i;//奇数相反； 
    }
    return 0;
}
```

---

## 作者：chuxiaoyang (赞：0)

使用平方根求解，可能在大数据的时候比枚举快一些。本人代码不规范，仅供参考。

因为第n项一定在(a\*a-a)/2和(a\*a+a)/2之间，所以只要求出a，就迎刃而解了！

      
      
```cpp
#include<iostream>
#include<cmath>
using namespace std;
void downfind(int base,int u)
{ int i,j,o;
  for(i=base;i>0;i--)
  {if((i*i-i<=2*u)&&(i*i+i>=2*u)){break;
  }
  }
  o=i;
  j=(i*i-i)/2;
  if(o%2==0){
      cout<<u-j<<"/"<<o-(u-j)+1;
        }else{
            cout<<o-(u-j)+1<<"/"<<u-j;
  }
}
void upfind(int base, int num)
{ int i,j,o;
  for(i=base;i>0;i++)
  {if((i*i-i<=2*num)&&(i*i+i>=2*num)){break;
  }
  }
  o=i;
  j=(i*i-i)/2;
  if(o%2==0){
      cout<<num-j<<"/"<<o-(num-j)+1;
        }else{
            cout<<o-(num-j)+1<<"/"<<num-j;
  }
}
int main(void){
   int a,b,tp;
   cin>>a;
   tp=2*a;
   b=floor(sqrt(tp));
   if(b*b-b>tp) downfind(b,a); else upfind(b,a);
   return 0;
}

```

---

## 作者：bobble (赞：0)

一眼看去，还以为要一个个枚举，把整个表打出来，然后发现图越看越熟悉，将图旋转一下，这不就是小学书上的数字三角之类的吗mdzz……

```cpp
var
    u,d,n,i:longint;
begin
    read(n);
    for i:= 1 to 4500 do
      if (i+i*i) div 2>= n then
                            begin
                                 if odd(i) then begin//如果是单数行就是分子从左往右递增，
                                                  u:=(i+i*i) div 2-n+1;
                                                  d:= n+i-(i+i*i) div 2;
                                                end
                                      else begin//偶数行和单数行相反
                                             d:=(i+i*i) div 2-n+1;
                                             u:= n+i-(i+i*i) div 2;
                                          end;
                                 break;//别忘记跳出循环
                            end;
     write(u,'/',d);//输出结果
end.
```
详见我的博客，传送门在下——面：
好吧，最后来骗骗访问量：  <https://blog-tonylim.rhcloud.com/2016/08/06/%e3%80%901083%e3%80%91codevs-1083-cantor%e8%a1%a8-1999%e5%b9%b4noip%e5%85%a8%e5%9b%bd%e8%81%94%e8%b5%9b%e6%99%ae%e5%8f%8a%e7%bb%84/>


---

## 作者：zjc0201 (赞：0)

```cpp
var n,i,j,k,m:longint;
begin
readln(n);
k:=1;
while i+k<n do//找到在第几斜。
begin
inc(i,k);//到此斜结束的总个数。
inc(k);//每斜比上一斜多一。
end;
if k mod 2=0 then//奇偶分开处理。
write(n-i,'/',k-n+i+1)//规律。
else
write(k-n+i+1,'/',n-i);
end.

```

---

