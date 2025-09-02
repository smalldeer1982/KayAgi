# HDD is Outdated Technology

## 题目描述

HDD hard drives group data by sectors. All files are split to fragments and each of them are written in some sector of hard drive. Note the fragments can be written in sectors in arbitrary order.

One of the problems of HDD hard drives is the following: the magnetic head should move from one sector to another to read some file.

Find the time need to read file split to $ n $ fragments. The $ i $ -th sector contains the $ f_{i} $ -th fragment of the file ( $ 1\le f_{i}\le n $ ). Note different sectors contains the different fragments. At the start the magnetic head is in the position that contains the first fragment. The file are reading in the following manner: at first the first fragment is read, then the magnetic head moves to the sector that contains the second fragment, then the second fragment is read and so on until the $ n $ -th fragment is read. The fragments are read in the order from the first to the $ n $ -th.

It takes $ |a-b| $ time units to move the magnetic head from the sector $ a $ to the sector $ b $ . Reading a fragment takes no time.

## 说明/提示

In the second example the head moves in the following way:

- 1->2 means movement from the sector 1 to the sector 5, i.e. it takes 4 time units
- 2->3 means movement from the sector 5 to the sector 2, i.e. it takes 3 time units
- 3->4 means movement from the sector 2 to the sector 4, i.e. it takes 2 time units
- 4->5 means movement from the sector 4 to the sector 3, i.e. it takes 1 time units

So the answer to the second example is $ 4+3+2+1=10 $ .

## 样例 #1

### 输入

```
3
3 1 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
1 3 5 4 2
```

### 输出

```
10
```

# 题解

## 作者：zhanghzqwq (赞：4)

##  ~~十年OI一场空，不开longlong见祖宗~~

这道题太水了，没什么好说的，拿个数组记录一下就行了,时间复杂度$O(n)$。最关键的是答案必需要开$long long$。

上代码：
```cpp
#include<cmath>
#include<iostream>
using namespace std;
int a[200005];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		a[x]=i;//记x的位置
	}
	long long ans=0;//一定要开long long
	for(int i=2;i<=n;i++){//从2开始循环
		ans+=abs(a[i]-a[i-1]);
	}
	cout<<ans<<endl;//输出
	return 0;//华丽的结束
}
```


---

## 作者：Ybocean_s (赞：1)

题意：给出每个数的位置，求一共要走几步，其实这道题没有什么难度，要注意的是数组要开大，并且用长整形在统计时。

------------

思路:按照数的顺序将所在的位置存入数组，然后相邻的数相减，即为每走一次所需要的能量，定义一个变量用来统计总共用的能量，输出。

------------

代码：

```cpp
#include<cmath>
#include<iostream>
using namespace std;
int a[1000001]//不能太小。
int main()
{
	int n,x;
	cin>>n;//输入总数。
	for(int i=1;i<=n;i++){
		cin>>x;
		a[x]=i;
	}
	long long js=0;//不开见祖宗。
	for(int i=1;i<=n-1;i++){
		js+=abs(a[i]-a[i+1]);//距离加和。
	}
	cout<<js;
	return 0;//结束。
}
```
重要的部分就在输入排序的地方把每个数放到他本来的地方，撒花。

---

## 作者：wuwenjiong (赞：1)

## 题目：
输入 $n$ ，接下来输入 $n$ 个数，分别为 $a_1,a_2$ 一直到 $a_n(1\le a_i\le n)$ ，且 $a_i$ 均不相等。从 $a_i$ 到 $a_j$ 的代价就是 $|a_i-a_j|$ 。求：按照升序的顺序从 $1$ 到 $2$ ，到 $3$ 一直到 $n$ ，一共要花费多少代价。
## 思路：
这里需要用**桶排**的思想。不知道的朋友可以去[这里](https://www.cnblogs.com/bqwzx/p/11029264.html)

因为 $1$ 到 $n$ 所有数都一定会出现，且只出现一次，所以我们拿数组的下标记录一个数，而数组的值为下标出现的位置，这样只需要从 $1$ 到 $n$ 循环一次，每次加上移动的代价，最后输出即可。记得开**longlong**。
## 最后，放代码
```cpp
#include<bits/stdc++.h>
#define f(a,b,c) for(a=b;a<=c;a++)
using namespace std;
int j(int x)//求绝对值函数
{
	if(x>0)
		return x;
	else
		return -x;
}
int main()
{
    long long s=0;//不开long long见祖宗
	int n,i,k,a[200005];
	cin>>n;
	f(i,1,n)
	{
		cin>>k;
		a[k]=i;
	}
	f(i,1,n-1)
		s+=j(a[i]-a[i+1]);//累加代价
	cout<<s;
	return 0;
}
```
谢谢！！！

---

## 作者：封禁用户 (赞：1)

欲寻优解请看过来！不要急，耐心看到底~  
题目传送>>[CF612B](https://www.luogu.com.cn/problem/CF612B)  
### 题意简述：  
磁盘寻址检索，扇区依次进行，从第 $i$ 个扇区到第 $j$ 个扇区用时 $|i-j|$，求第 $1$ 扇区到到第 $n$ 扇区总用时。  
### 题目分析：  
磁盘寻址是线性寻址（扇区依次进行），即 $1→2→3→...→n$，且第 $i$ 个扇区到第 $j$ 个扇区用时 $|i-j|$。所以我们即可对输入的每个扇区的位置进行一一对应（使用数组即可），然后从标号小的扇区开始不断求到下一标号扇区的用时，并进行累加，最终即为总用时。  
#### Code1:  
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
typedef long long ll;   //类型定义long long 为ll，避免频繁使用时累手
ll a[200001];   //开数组存对输入的每个扇区的位置进行一一对应
int main()
{
	//freopen("HHD.in","r",stdin);   //定义输入文件名
	//freopen("HHD.out","w",stdout);  //定义输出文件名
	ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
	ll n,ans=0;   //定义目标扇区标号，总用时
	ll zhi;   //定义扇区标号
	cin>>n;
	for(ll i=1;i<=n;i++)
	{
		cin>>zhi;
		a[zhi]=i;   //对输入的每个扇区的位置进行一一对应
	}
	for(ll i=1;i<n;i++)   //注意此处i是小于n
	{
		ans+=abs(a[i+1]-a[i]);   //从标号小的扇区开始不断求到下一标号扇区的用时，并进行累加
	}
	cout<<ans;
	//fclose(stdin);fclose(stdout);   //关闭文件
	return 0;   //结束整个程序
}
```
#### 结果:  
![JieGuo1](https://cdn.luogu.com.cn/upload/image_hosting/f0dq121i.png)  
  
A完之后，瞟了一眼样例及解释，发现目标扇区标号为 $3$ 时，总用时为：$1+2=3$；目标扇区标号为 $5$ 时，总用时为：$4+3+2+1=10$。结合磁盘寻址线性寻址性，我们可以发现求第 $1$ 扇区到到第 $n$ 扇区总用时的式子为：$1+2+...+n-1$，共 $n-1$ 项，且每项相差 $1$，即为等差数列。数学中求等差数列前 $n$ 项和的公式为：$S_n= \frac{n(a_1+a_n)}{2}$，（其中 $a_1$ 为首项，$a_n$ 为末项）。套用公式，我们可以得到此题总用时为：$\frac{n(n-1)}{2}$。  
所以说我们甚至无需读入第二行的 $n$ 个扇区标号，只需读入目标扇区标号 $n$，即可利用推导得到的公式进行求解。  
#### Code2(全网最短C++代码？):  
```cpp
#include<iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	cout<<(n*(n-1))/2;
	return 0;
}
```
#### 结果：  
![JieGuo2](https://cdn.luogu.com.cn/upload/image_hosting/ihns0fnv.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：yf最qhhh (赞：1)

~~首先，让我们说一句：翻译太\*\*恶心了。~~ 如果不是题解里面某位大佬放出的翻译我直接。。。。

咳咳，回归正题。

这道题题目看懂了其实一点也不难，说白了就是输入一串编号，输入时你还要记录一下下标，你要求的是从 $1$ 号走到 $n$ 的代价，从 $f_i$ 走到 $f_j$ 的代价为 $\vert f_i-f_{i-1} \vert$。

所以最终的答案为 $\sum_{i=2}^{n}\vert f_i-f_{i-1} \vert$

对了，**十年oi一场空，不开_____\_见祖宗?**

一定记得 **long long**!!!!!!

最后，代码如下
```cpp
#include<cstdio>
#include<algorithm>
#define ll long long
#define rll register long long
ll arr[200005];
int main(){
	rll n,ans=0,tmp,i;
	scanf("%lld",&n);
	for(i=1;i<=n;i++){
		scanf("%lld",&tmp);
		arr[tmp]=i;//把下标记录，把i赋给它
	}
	for(i=2;i<=n;i++)ans+=std::abs(arr[i]-arr[i-1]);//求最终答案
	printf("%lld",ans);
	return 0;
}

```


---

## 作者：翼德天尊 (赞：1)

## Part 1 题目分析

题目相信大家都看过了，现在给大家讲讲我的思路吧。

1. 首先，因为我们要知道，输入的数 $a$ 表示的是 $f_a$ 在 $i$ 上，而不是 $f_i$ 为 $a$。所以我们输入的时候应该将数组的下标为 $a$，内容为 $i$。

2. 其次，我们可以设置一个 $ans$ 变量，表示答案。然后循环算出 $\sum_{i=2}^{n}\left|f_i-f_{i-1}\right|$ 就是答案了。

3. 最后，注意，假设我们每次都要从左跑到右再从右往左走的话（最坏情况），注意到 $n\le 2\times10^5$，所以答案最多会为:

$\dfrac{(2\times10^5+1)\times(2\times10^5)}{2}=2\times{10^{10}+10^5}$

### 完爆 $\text{int}$！

所以还是用 $\text{long\ long}$ 吧！

## Part 2 AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200005
int n,s[N];
long long ans;
inline int read(){//快读，占了大部分的代码量
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}

int main(){
	n=read();
	for(int i=1;i<=n;i++)
		s[read()]=i;
	for (int i=2;i<=n;i++)
		ans+=abs(s[i]-s[i-1]);
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：pandaSTT (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF612B)

## 前言

难度有些虚高，此题最多入门难度。

## 思路

按照题目要求做模拟。

首先按照题目给出的该位置的位置从小到大排序，然后用结构体记录该位置的题目给出位置（有点绕口，建议多读几遍），最后按照题目要求算出总代价即可。

## 代码

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int read(){
      int k=0,x=0; 
      char s=getchar(); 
      while(s<'0'||s>'9'){
          k|=s=='-'; s=getchar(); 
      }
      while(s>='0'&&s<='9'){ 
          x=(x<<3)+(x<<1)+(s^48); 
          s=getchar(); 
      }
      return k?-x:x; 
  }
  long long n,ans;
  struct nobe{
      int val,id;//该位置的题目给出位置和该位置的位置
      friend bool operator<(nobe x,nobe y){//重载运算符
          return x.val<y.val;
      }
  }a[200005];
  int main(){
      n=read();
      for(int i=1;i<=n;i++){
          a[i].val=read();
          a[i].id=i;
      }
      sort(a+1,a+n+1);
      for(int i=2;i<=n;i++){
          ans+=abs(a[i].id-a[i-1].id);//按照题目求总价值
      }
      cout<<ans;
      return 0;
  }
```


---

## 作者：_caiji_ (赞：0)

首先我们用 $a_i$ 代表值为 $i$ 的数在哪个位置，然后只需要求出 $\sum^{n-1}_{i=1}|a_i-a_{i+1}|$就行了。记得开`long long`。

代码：
```cpp
#include <cstdio>
using namespace std;
int a[200010],n;
long long ans;
int abs(int a){return a<0?-a:a;}
int main(){
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++){
		scanf("%d",&x);
		a[x]=i;
	}
	for(int i=1;i<n;i++){
		ans+=abs(a[i]-a[i+1]);
	}
	printf("%lld",ans);
    return 0;
}
```

---

## 作者：Terraria (赞：0)

看了一眼题解区的题解，好像都比我写得简单好多，但是思路是一样的。

就如题解区的大佬们所说，需要记录下每个数的位置。

又要计数又要记位置，$struct$ 走你！

然后我们需要结构体排序。本来是一个 $cmp$ 能搞定的事情我非得写了个重载。

好了，话不多说，直接上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int num;
	int id;
	bool operator <(const node &x)const{return num<x.num;}
}a[10000009];
int n,ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].num;
		a[i].id=i;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<n;i++) ans+=abs(a[i].id-a[i+1].id);
	cout<<ans;
}
```
看到```#define int long long```了吗？这个东西可以帮你从 $WA$ 转向 $AC$！

---

## 作者：djh233 (赞：0)

**题意：**

给定一个长度为 $n$ 的包含 $1$ 到 $n$ 的序列，起初，你在位置 $x$ ，满足 $a_x=1$。

然后，您必须从值为 $1$ 的位置跳到值为 $2$ 的位置，再从值为 $2$ 的位置跳到值为 $3$ 的位置，一直跳到值为 $n$ 的位置后结束。

若从位置 $i$ 跳到位置 $j$ ，则需要花费 $|i-j|$ 的体力，问跳到 $n$ 之后需要花费多少体力。

**数据范围：**$1\le n\le 2\cdot 10^5$ 。

**做法：**

维护一个数组 $pos_i$ 代表值为 $i$ 的位置，然后答案为 $\sum\limits_{i=2}^n |pos_i-pos_{i-1}|$ 。

**时间复杂度：** $O(n)$ 。

$Code:$

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int a[200010];
int pos[200010];

void solve()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),pos[a[i]]=i;
    int lst=pos[1];
    ll ans=0;
    for(int i=2;i<=n;i++) ans+=abs(pos[i]-lst),lst=pos[i];
    printf("%lld",ans);
}

int main()
{
    solve();
    return 0;
}

---

## 作者：末置lzy (赞：0)

# CF612B HDD is Outdated Technology
# 题解
题目传送器：[HDD is Outdated Technology](https://www.luogu.com.cn/problem/CF612B#submit)

### 题目翻译

~~由于原本翻译太恶心就自己翻了一下~~

```
硬盘驱动器按扇区分组数据。所有的文件被分割成碎片，每一个都被写入硬盘的某个扇区。注意片段可以按任意顺序在扇区中写入。



硬盘驱动器的一个问题是：磁头应该从一个扇区移动到另一个扇区来读取文件。



查找需要读取的时间将文件拆分为n个片段。第i个扇区包含f{i}fi

-文件的第个片段（1<=f{i}<=n1<=fi<=n）。注意不同的扇区包含不同的片段。开始时磁头位于包含第一个碎片的位置。文件的读取方式如下：首先读取第一个片段，然后磁头移动到包含第二个片段的扇区，然后读取第二个片段，依此类推，直到第n个片段被读取。这些片段按从第一到第n的顺序读。



磁头从扇区a移动到扇区b需要| a-b∣a−b∣时间单位。阅读一个片段不需要时间。
```

### 输入翻译

```
第一行包含一个正整数n n（1<=n<=2·10^{5}1<=n<=2⋅105）-碎片的数量。



第二行包含n个不同的整数f{i}fi（1<=f{i}<=n1<=f i<=n）-在第i个扇区中写入的片段数。
```
### 输出翻译

```
输出唯一的整数-读取文件所需的时间单位数。
```
~~舒服多了qwq~~

**分析**

通过翻译的意思，就是在不同区间内移动内容就行了,输入的内容用一个数组存一下就行了，其实很简单

我理解的就是移动时所耗的部分，输出它就行了，而主要代码就是以下，主要是就是绝对值函数

```cpp
abs(a[i]-a[i-1]);
```
它需要“数学”头文件，如下

```cpp
#include<cmath>
```
~~当然了你用万能头我就没什么话说了qwq~~

#### so

# AC~~不了~~CODE

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int a[1000000];
	int n,x1,ans=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x1;
		a[x1]=i;
	}
	for(int i=2;i<=n;i++)
	{
		ans+=abs(a[i]-a[i-1]);
	}
	cout<<ans;
	return 0;
}
```
这玩意AC不了，后来我想起了某句关于CF的著名言论

~~十年OI一场空，不开longlong见祖宗~~

然后

# AC CODE
共创和谐洛谷，不要抄题解，棕名警告qwq。

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int main()
{
     long long ans=0;
	int a[1000000];
	int n,x1;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x1;
		a[x1]=i;
	}
	for(int i=2;i<=n;i++)
	{
		ans+=abs(a[i]-a[i-1]);
	}
	cout<<ans;
	return 0;
}
```
OK，本篇题解到此结束了

~~求审核大大通过qwq~~

---

## 作者：昊月星辰 (赞：0)

# 十年OI一场空，不开longlong见祖宗


### 首先审一下题:  ~~不得不说这翻译是真的恶心……~~
一共有$n$个正整数，$f_1-f_n$，每个数的范围都在1-$n$之间。

第$i$个数$f_i$表示数组中下标为$f_i$的数的位置为$i$。

现在要求从下标为1的数移动到下标为$n$的数所需移动的距离。

我们要做的就是对每次移动的距离求和并输出即输出${\sum_{i=1}^{n-1}|f_{i+1}-f_{i}|}$.
### 注意：
最后的结果要开long long！！！

### $Code$:
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
int w=0;
char c=getchar();
while(c>'9'||c<'0') c=getchar();
while(c>='0'&&c<='9'){
w=(w<<3)+(w<<1)+(c^48);
c=getchar();
}
return w;
}//快读
int a[100005];
long long ans;//用于求和
int n;
int main(){
    n=read();
    for(int i=1;i<=n;i++){
       int b;
       b=read();//输入下标
       a[b]=i;//数组中下标为b的数的位置为i
    }
   
    for(int i=1;i<=n-1;i++){
       ans+=abs(a[i+1]-a[i]);//求相邻两数之差的和
    }
    cout<<ans<<endl;//输出
    return 0;
}
```


---

## 作者：Mysterious_bird (赞：0)

emmmm...

这个翻译不是很友好

### 大意：

一个东西放到x号格子里，而这个东西的大小为i

问你从1号格子移动到n号，需要的代价是多少

而移动一次的代价为

```cpp
abs(f[i]-f[i-1])
```

其他没什么好讲的

__**注意，输出时要开long long**__

### code：
```cpp
#include <cstdio>
using namespace std;
const int maxn=333333;
int f[maxn];
int abs(int x)
{
	return x<0?-x:x;
}   //绝对值函数
int main()
{
	int n;
    scanf("%d",&n);
	for(int i=1,a;i<=n;++i)
	{
		scanf("%d",&a);
		f[a]=i;     //赋值
	}
	long long ans=0;    //注意，这里一定要开long long
	for(int i=2;i<=n;i++)   //i=2很关键
        ans+=abs(f[i]-f[i-1]);
	printf("%lld\n",ans);   //lld为long long类型的输出
	return 0;
}
```

---

## 作者：世末OIer (赞：0)

题目大意：

有一个1....n的全排列。现在让你从值为1的那一个位置走到值为2的节点的位置，从2走到3，....从n-1走到n。每一步的距离是两个位置的下标之差的绝对值。问你这总路径是多少。

题解：

记录每一个数所在的位置。循环从1.....n，累加即可。

```cpp
int wz[200005];//记录的位置
int n,x;
int main(){
	rdi(n);
	int i,j;
	for(i=1;i<=n;++i) rdi(x),wz[x]=i;
	ll ans=0;
	for(i=1;i<n;++i) ans=(ll)(ans+abs(wz[i]-wz[i+1]));//累加
	print(ans);
}
```

---

