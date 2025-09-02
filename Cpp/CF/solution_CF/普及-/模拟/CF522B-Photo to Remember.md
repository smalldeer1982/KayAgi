# Photo to Remember

## 题目描述

One day $ n $ friends met at a party, they hadn't seen each other for a long time and so they decided to make a group photo together.

Simply speaking, the process of taking photos can be described as follows. On the photo, each photographed friend occupies a rectangle of pixels: the $ i $ -th of them occupies the rectangle of width $ w_{i} $ pixels and height $ h_{i} $ pixels. On the group photo everybody stands in a line, thus the minimum pixel size of the photo including all the photographed friends, is $ W×H $ , where $ W $ is the total sum of all widths and $ H $ is the maximum height of all the photographed friends.

As is usually the case, the friends made $ n $ photos — the $ j $ -th ( $ 1<=j<=n $ ) photo had everybody except for the $ j $ -th friend as he was the photographer.

Print the minimum size of each made photo in pixels.

## 样例 #1

### 输入

```
3
1 10
5 5
10 1
```

### 输出

```
75 110 60 ```

## 样例 #2

### 输入

```
3
2 1
1 2
2 1
```

### 输出

```
6 4 6 ```

# 题解

## 作者：zplqwq (赞：6)

Photo to Remember 题解

BY: 赵菩霖

# Section 1 瞎怀念

其实，做这道题的时候还蛮有感受的呢。

我小学毕业了，身边一堆同学都不知道去哪里了

想当年，我还是个学妹呢

如今已经是学姐了。。。。

拍毕业照的时候一定要参考这道题。

不知道下次再见是什么时候了呢

嘻嘻，珍惜好现在吧。

#  Section 2 题目分析

题意比较明确，主要是让你求照片的最小面积。

通过题目，不难得知，照片的最小面积，是除去它本人后最高的那个人的高度和总宽度的乘积。

然后直接每次都查一下最大值即可。

但貌似这样有点慢。

那怎么优化呢？

其实我们可以只求一次最大值，然后呢？

只要这个人不是最高的，它**无法改变其它人的高度**

如果这个人是最高的话，就找**第二高**的就行了

完了？

当然没有！

还需要处理**宽**。

但是宽肯定很好处理，其实就每次用一个变量cnt记录**每个人的宽度**，最后输出的时候就直接输出**cnt-a[i]**即可。

坑点

1. 记住了！如果有两个最大值，需要特殊处理一下
2. 模拟时要细心

# Section 3 代码

```c++
#include<bits/stdc++.h> //万能头文件
using namespace std;
//洛谷真棒
//我爱洛谷
const int N=1000010;
int n,cnt,ret;

int a[N],b[N],sum;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)//处理最大值
	{
		cin>>a[i]>>b[i];
		if(b[i]>cnt)//如果有两个最大值
		{
			ret=cnt;
			cnt=b[i];
		}
		else if(b[i]>ret)
		{
			ret=b[i];
		}
		sum+=a[i];//累加
	}
	for(int i=1;i<=n;i++)//输出
	{
		if(b[i]==cnt)
		{
			cout<<ret*(sum-a[i])<<" ";//处理宽
		}
		else
		{
			cout<<cnt*(sum-a[i])<<" ";
		}
	}
	return 0;
}
```

管理大大求过





---

## 作者：封禁用户 (赞：2)

题目传送>>[CF522B](https://www.luogu.com.cn/problem/CF522B)  
### 题意简述：  
$n$ 个人并排合照，已知每人高度与宽度，求除第 $i$ 人后的照片最小面积。  
### 题目分析:  
根据题意，要使人们都完整入镜，合照的最小面积应为所有人的总宽度乘于最高人的高度，而除掉第 $i$ 人，宽度只需在原所有人的宽度和上减去该人的宽度即可，而高则需要一个小小的分类讨论。如果除去的第 $i$ 人的高度不是所有人中最高的，则新高度不变，依旧为原所有人中最高人的高；而如果除去的第 $i$ 人的高度是所有人中最高的，则合照的高度终于可以减小了，即变为原所有人中第二高的人的高。  
### Code:  
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct people{   //利用结构体存每人的宽和高
	int w,h;
}a[200001],b[200001];   
bool cmp(people x,people y)   //依据高降序排序
{
	return x.h>y.h;
}
int main()
{
	//freopen("input.in","r",stdin);
	//freopen("print.out","w",stdout);
	ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
	int n;   //定义人数
	int sw=0;   //定义人的总宽度
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].w>>a[i].h;
		b[i].w=a[i].w,b[i].h=a[i].h;   //因为等会排序会改变顺序，故再用一个数组对数据进行备份
		sw+=a[i].w;   //累加人的总宽度
	}
	sort(a+1,a+1+n,cmp);   //排序
	for(int i=1;i<=n;i++)
	{
		cout<<(b[i].h==a[1].h? a[2].h*(sw-b[i].w):a[1].h*(sw-b[i].w))<<" ";    //利用三目运算符判断输出，a[1].h为最高人高度，a[2].h为次高人高度
	}
	return 0;   //结束整个程序
}
```
### 结果（未吸氧）：  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/x6vqfw85.png)  
企鹅的题解到此结束，祝各位 OIers 进步++~

---

## 作者：Phoenix_chaser (赞：1)

## 本题可以用求最大值+模拟
本题题意可知

#### 照片的最小面积，是除去它本人后最高的那个人的高度和总宽度的乘积

但似乎每次都找一遍最大值有些浪费

但我们只去求一次最大值就可以了

因为只要这个人不是最高的，它**不可能改变其它人的高度**

如果这个人是最高的话，就找**第二高**的就行了

### 还有一个问题：

宽度怎么处理

只需要在输入的时候把每个人宽度**累加**

在每次去掉这个人的时候 _**把他自身的宽度减掉**_ 

就很容易实现了

另外如果 _**有两个相同的最高的话**_ 

需要特殊处理
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,a[2000000],ans=0,b[2000000],zuida1=-1,zuida2=-2,vis;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
	{cin>>a[i]>>b[i];
	ans+=a[i];
	if(b[i]>zuida1)
	{zuida1=b[i];
	vis=i;
	//处理最大值
	//有可能有两个最高的 
	}
	}
	for(int i=1;i<=n;i++)
	{
		if(i!=vis)
		zuida2=max(zuida2,b[i]);
	}
	for(int i=1;i<=n;i++)
	{
		if(b[i]==zuida1)
		cout<<zuida2*(ans-a[i])<<' ';
		else 
		cout<<zuida1*(ans-a[i])<<' ';
	}
	return 0;
}
```
## 谢谢观看

### the end


---

## 作者：gshgsh (赞：0)

## 题意简介
某一天，$n$ 个朋友在一起聚会,他们要拍照留念，拍照的时候，每个人有一个高度和宽度，第i个的高度和宽度分别是 $h[i]$ 和 $w[i]$。这些人排成一条直线，照片的最小的面积必须包含所有的的人，所以照片的面积是 $W$ $\times$ $H$，$W$ 是所有人的宽度之和，$H$ 是所有人中高度最高的那个人的高度。现在想要知道当第 $i$ 个人不在照片中的时候，照片的最小面积是多少。

## 思路

思路其实很简单，模拟就行，注意了，这题目限时为 $2$ 秒。
我的思路是：

1. 看最高的人有几个，不是一个的话照片高度恒定。
2. 每个人不在的宽度，乘上当前最高的人。

此作法为$O$ ( $n$ $\log$ $n$ )，本蒟蒻不会 $O$ ( $n$ )。 因为时间限制 $2$ 秒，所以暴力加优化也可以。但是我成功的把时间压缩在 $1$ 秒以内,还是很简单了吧。

### 话不多说，上代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MaxX = 2e5 + 5;
int n, w[MaxX], h[MaxX], s[MaxX], mi = -1e9, ww = 0;

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> w[i] >> h[i];
        s[i] = h[i];
        ww += w[i]; //求出总宽度
    }
    sort(s + 1, s + n + 1); //排序求最高的人的高度
    int h1 = s[n], h2 = -1e5, l1, cnt = 0;  // 求最大和第二大，cnt记录几个最高的人
    for(int i = n; i >= 1; i--)
        if(s[i] != h1)
            h2 = max(h2, s[i]);
    for(int i = 1; i <= n; i++)
        if(h[i] == h1)
        {
            cnt++;
            l1 = i;
        }
    if(cnt >= 2) //华丽的输出
        for(int i = 1; i <= n; i++)
            cout << (ww - w[i])*h1 << endl;
    else
        for(int i = 1; i <= n; i++)
            if(i == l1)
                cout << (ww - w[i])*h2 << endl;
            else
                cout << (ww - w[i])*h1 << endl; 
    return 0;
}
```



---

## 作者：hyc1026 (赞：0)

题意简化：

给定 $n$ 个人的高 $h$ 和宽 $w$，求出不包含第 $i$ 人的照片最小面积。

思路：

照片应该正好使得照片宽度等于剩下所有人的宽度之和，高度为剩下所有人的高度中取最大。

此时判断被踢掉的人是否为最高的即可。

是最高的：面积 $=$ 第二高的高度 $\times$ 宽度总和。

否则：面积 $=$ 最高者的高度 $\times$ 宽度总和。

---

AC Code:

```cpp
#include <bits/stdc++.h>
using namespace std;

int h[200001],w[200001],t[200001];

bool cmp(int x,int y)
{
    return x > y;
} //辅助sort实现从大到小排序功能

int main()
{
    int n;
    cin >> n;
    int maxh = -1e9, id = 0, sumw = 0;
    for(int i=1; i<=n; i++)
    {
        cin >> w[i] >> h[i];
        t[i] = h[i]; //用于排序
        if(h[i] > maxh)
        {
            maxh = h[i];
            id = i;
        } //记录最高的高度以及该人的编号
        sumw += w[i]; //求总宽度
    }
    sort(t+1,t+n+1,cmp); //用于求第二高（最高的人不在的时候用）
    for(int i=1; i<=n; i++)
    {
        if(id != i) cout << maxh * (sumw-w[i]) << " "; //分类讨论，别忘了宽度总和要减去不在的人
        else cout << t[2] * (sumw-w[i]) << " ";
    }
    return 0;
}
```

---

## 作者：thomas_zjl (赞：0)

这到其实是求和。

找这些数里的最大值和第二大的数值。

而这个代码是最核心的。

```
//f为最大值，s为第二大的数值。
for(int i=1;i<=n;++i){
	if(h[i]>f){//如果这个人的身高大于f。
		s=f;//那么s就接替原来f的位置。
		f=h[i];//f更新成更大的数。
	}
	else if(h[i]>s)//如果这个数比f小，但比s大。
		s=h[i];//那也是要改变数值的。
}
```

接下来，根据题意，算出图片的大小就可以了。

```
#include<bits/stdc++.h>
using namespace std;
int w[200001],h[200001];
int main(){
	int n,sum=0;
	int f=0,s=0;
	scanf("%d",&n);
	int jl=0;
	for(int i=1;i<=n;++i){
		scanf("%d%d",w+i,h+i);
		if(h[i]>f){
			s=f;
			f=h[i];
		}
		else if(h[i]>s)
			s=h[i];
		//算出最大值和第二大的值。
		sum+=w[i];//求总和。
	}
	for(int i=1;i<=n;++i){
		if(f==h[i])
			printf("%d ",s*(sum-w[i]));//如果这个不拍照的人最高的话，那么最高的人为s。
		else
			printf("%d ",f*(sum-w[i]));//其他的不变。
	}
   return 0;
}
```


---

## 作者：wzkdh (赞：0)

### 一道简单的模拟题


------------

题目要求我们求面积，我们知道面积是宽乘以高，所以本题就是求去掉每个人之后的宽和高分别是多少。

宽的话很好求，我们只需要用一个数组记录下每个人的宽，同时用一个变量记录下所有人的宽的总和，那么去掉第$i$个人的宽度就是$sum-a[i]$（sum为宽度总和，a为计录每个人宽度的数组）。

至于高，我们可以发现如果去掉的人不是最高的那一个，那么去掉他并不会影响高度；如果是最高的，那么总高度就是第二高的人，所以我们只需要用两个变量计录下最高与第二高，然后判断当前去掉的人是否最高，之后按照上面的结论计算即可。

### 蒟蒻代码：
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,fh,sh,a[200010],b[200010],sum;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i],&b[i]);
		if(b[i]>fh)
		{
			sh=fh;
			fh=b[i];
		}
		else if(b[i]>sh)
		{
			sh=b[i];
		}
		sum+=a[i];
	}
	for(int i=1;i<=n;i++)
	{
		if(b[i]==fh)
		{
			printf("%d ",sh*(sum-a[i]));
		}
		else
		{
			printf("%d ",fh*(sum-a[i]));
		}
	}
	return 0;
}

---

## 作者：yewanxingkong (赞：0)

# **题目分析**
告诉你一些人的身高和宽度，输出缺少第 $i$个人时照片的面积。

照片面积就是在的所有人宽度乘以在的最高的那个人的高度。

那么思路就出来了，记录下所有人宽度和和每个人的宽度，缺少哪个人照片宽度就是所有人宽度和减去哪个人的宽度。

由于只会缺少一个人，所以高度只需记录最高和第二高的。最高的在的时候高度就是最高的那个人的高度，不在就是第二高的人的高度。
# **代码**
~~加了特别多常数优化~~
```cpp
#include<cstdio>
#include<cctype>
int a[200010],b[200010];
inline char getch(){
	static char buf[100000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	register int x=0,f=1;register char ch=getch();
	while(!isdigit(ch))ch=getch();
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getch();
	}
	return x;
}
inline void write(register int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int main(){
	register int n,maxna=0,maxnb=0,kuan=0;
	n=read();
	for(register int i=0;i<n;++i){
		int x=read(),y=read();
		a[i]=x;
		b[i]=y;
		kuan+=x;
		if(y>maxna){
			maxnb=maxna;
			maxna=y;
		}
		else if(y>maxnb)maxnb=y;
	}
	for(register int i=0;i<n;++i)
		if(b[i]!=maxna){
			write((kuan-a[i])*maxna);
			putchar(' ');
		}
		else{
			write((kuan-a[i])*maxnb);
			putchar(' ');
		}
	return 0;
}

```


---

## 作者：WanderingTrader (赞：0)

一道并不难的模拟，可以用“次大值”方法解决。  
### 题目分析
首先求出 $sum=\large\sum\limits_{i=1}^nw[i]$，那么照片的宽就是 $w[i]-sum$，很好解决。  

至于高，如果只求了一个最大值，那么选到最高的学生时就比较麻烦，所以这里维护两个最大值：$max1,max2$，保证操作完成后 $max1\ge max2\ge h[i]|i\in[1,n]$。

那么每次如果$h[i]=max1$，那就是 $max2$ ，否则就是 $max1$。  

最后把两个数值相乘即可。   
观察数据发现，长方形的长不超过 $2\times 10^6$，宽不超过 $1000$，总数则不超过 $2\times 10^9$，能放入int存储。  
### 代码
初始化：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 200005
int w[N],h[N];
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int main()
{
	int n=read();
	for(int i=1;i<=n;++i)
		w[i]=read(),h[i]=read();
	return 0;
}
```
然后是求最大值和次大值的代码：
```cpp
int max1=INT_MIN,max2=max1;
for(int i=1;i<=n;++i)
{
	if(h[i] > max2) max2 = h[i];
	if(max2 > max1) swap(max2,max1);
}
```
这种方法还是很好想的，不作过多解释。  

顺手把总和求一下：
```cpp
int sum=0;
for(int i=1;i<=n;++i)
		sum+=w[i];
```
那么最后愉快的输出答案：
```cpp
for(int i=1;i<=n;++i)
{
	int length = (h[i]==max1?max2:max1);
	int width = sum-w[i];
	int ans = length*width;
	printf("%d ",ans);
}
printf("\n");
```

也许有人会问：那如果有两个数值都是最大值那怎么办？

根据这种求解方法，此时 $max1=max2$，当我们找到一个 $h[i]=max1$ 的时候，它会输出 $max2$，符合要求，不必担心。


$$\texttt{The End.}$$

---

## 作者：Mysterious_bird (赞：0)

~~亿~~堆人排队拍照，然后每个人出去一下，问除了出去的人，队伍的最大面积是多少

**模拟题**

### 思路：

一个变量记录除了出队的人的总宽度，一个变量记录最高的人的高度

错误代码：

```cpp
for(int i=1;i<=n;i++)
{
    for(int j=1;j<=n;j++)
    {
        if(j!=i)
        {
            maxn=max(maxn,H[i]);
            ans+=W[i];
        }
    }
    printf("%d ",ans*maxn);
}
```

此代码会TLE！！！

**不能读入完了后输出答案时一个个查找最高的，不然会TLE！**

为此，我们只能在输入时做点功夫，一个变量在输入时加进所有人的宽度，**再开一个数组，记录高**

接着，把新开的newH数组从大到小快排（有点懒，直接用了函数），在输出时用

**(总宽度-当前出队的人的宽度)\*当前最高的身高**

但是，问题来了，题目中没说数据不重复，可能会有两个最高的人高度相等

解决方法：

**不用考虑，因为快排并不会去重，及时当前这个人是最高的，第二高的就在他n-1的地方，因此，照常做就行**

### code：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int n,W[200001],H[200001],newH[200001],ans,maxn;    //newH记录高度
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&W[i],&H[i]);
        ans+=W[i];  //在输入时加进所有高度
        newH[i]=H[i];   //newH记录
    }
    sort(newH+1,newH+n+1);  //把newH数组排序，从而得出最高的
    for(int i=1;i<=n;i++)
    {
        int x=ans-W[i];     //总宽度-当前出队的人的宽度
        if(H[i]!=newH[n])   //如果当前出队的人不是最高的那个
            printf("%d ",x*newH[n]);    //输出当前宽度*最高的高度
        else    //如果目前一个是最高的
            printf("%d ",x*newH[n-1]);  //输出当前宽度*第二高的
    }
    return 0;
}
```

---

## 作者：Tarensev (赞：0)

~~那么水的一道题怎么没人来提交呢~~

~~于是我成为了第一个ac并写题解的人~~

翻译已在讨论版里写出

由于数据太大，我们当然不能一个一个找最大的身高，当然，宽度也是

第i个人有两种可能

1. 身高最高
2. 身高不是最高

那我们就只要把最高的和第二高的记录下来就行了

宽度和就可以先把所有人的宽度累加，再减去不在的那个人

我们贴代码吧

```pascal
var w,h:array[1..200000] of longint;
    i,n,max1,max2,x1,s:longint;
begin
 readln(n);
 for i:=1 to n do
  readln(w[i],h[i]);
 max1:=h[1];
 x1:=1;
 for i:=2 to n do if max1<h[i] then
  begin
   max1:=h[i];
   x1:=i;
  end;
 max2:=-1;
 for i:=1 to n do if (max2<h[i])and(i<>x1) then
  max2:=h[i];
 for i:=1 to n do s:=s+w[i];
 for i:=1 to n do
  if i=x1 then writeln((s-w[i])*max2)
   else writeln((s-w[i])*max1);
end.
```
好啦，这就是pascal的题解，有缺点请在评论区尽管指出，我一定会虚心接受的

---

