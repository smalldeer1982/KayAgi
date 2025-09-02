# [USACO08OCT] Wheel Rotation G

## 题目描述

Farmer John has an old-time thresher (wheat harvester) that requires belts to be installed on various gears to turn the parts. The engine drives pulley 1 in a clockwise direction which attaches via a belt to pulley 2. Pulley 2 attaches via a belt to pulley 3 and so on through a total of N (2 <= N <= 1,000) pulleys (and N-1 belts).

The diagram above depicts the two ways a belt can be installed between two gears. In this illustration, pulley 1's belt directly drives pulley 2 (a 'straight' connection) and thus they will rotate in the same direction. Pulley 3 drives pulley 4 via a 'crossed belt' that reverses the direction of the rotation.

Given a list of the belt types that connect the pulleys along with the fact that pulley 1 is driven in a clockwise direction by the engine, determine the drive direction of pulley N. Each belt is described by three integers:

```cpp
* S_i -- the driving (source) pulley 
* D_i -- the driven (destination) pulley 
* C_i -- the connection type (0=straight, 1=crossed) 
Unfortunately, FJ lists the belts in random order. 
By way of example, consider the illustration below. N = 4, and pulley 1 is driven clockwise by the thresher engine. Straight 
belts drive pulley 2 and then pulley 3, so they rotate clockwise. The crosswise belt reverses the rotation direction so pulley 4 (pulley N) rotates counterclockwise. 
```
POINTS: 70
约翰有一个过时的收割机，需要在它的各种滑轮上装配皮带才能让收割机的各个部分运作起 来.引擎能够驱动滑轮1向顺时针方向转动，滑轮1通过一条皮带又连接到滑轮2.滑轮2又通过一 条皮带连接到滑轮3，等等，总共有N(2 <= N <= 1000)个滑轮和N - 1条皮带.

皮带连接两个滑轮有两种方式：直接连接和交叉连接.直接连接的两个滑轮旋转方向相同， 即同为顺时针或同为逆时针.交叉连接的两个滑轮旋转方向相反.

现在给出一个列表，里面列出所有皮带的连接方式.已经知道滑轮1被引擎驱动着向顺时针方 向转动.每一条皮带由下面三个数定义：

•驱动滑轮S，输入驱动力的滑轮.

•被驱动滑轮D;，被驱使转动的滑轮.

•连接类型C，0表示直接连接，1表示交叉连接.

不幸的是，约翰的这个列表中，皮带的顺序是混乱的.所以请你写一个程序来求出滑轮N的 转动方向.


## 说明/提示

As in the example illustration.


## 样例 #1

### 输入

```
4 
2 3 0 
3 4 1 
1 2 0 
```

### 输出

```
1 
```

# 题解

## 作者：NTG_Adiord (赞：10)

鬼畜做法

反正跟顺序根本没多大关系。。。。。直接1抑或和就好

代码如下




```
#include <cstdio>
int main(){
	int n,a;bool b;
	scanf("%d",&n);n--;
	while(n--)scanf("%d%d%d",&a,&a,&a),b^=a;
	printf("%d",b);
}

```
太鬼畜了真是



麻烦的做法

链式前向星，记录一下引擎之前是否有动力轮，如果没有那说明这个轮子是第一个轮子

然后遍历算抑或和就完了

~~详情请咨询10086~~

详情参考代码

```
#include <bits/stdc++.h>
using namespace std;
int n;
int l;
int to[1001];
int hea[1001];
int nex[1001];
int wea[1001];
int in[1001];
int ans;
void dr(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int a,b,w;
		scanf("%d%d%d",&a,&b,&w);
		in[b]++;//记录是否被连接
		to[++l]=b;nex[l]=hea[a];hea[a]=l,wea[l]=w;//连边，懒得写建边函数了
	}
}
void wk(){
	for(int i=1;i<=n;i++){
		if(in[i]==0){
			for(int j=i;j;j=to[hea[j]]){
				ans=ans^wea[hea[j]];//两次相反为0,直接算抑或，1^1=0
			}
		}
		printf("%d",ans);
		return;//直接返回
	}
}
int main(){
	dr();//读入
	wk();//输出
	return 0;
}

```

---

## 作者：荷叶下 (赞：4)

#### ~~带水题~~
## 蒟蒻の第二篇题解

------------

### 题意

#### 判断滑轮转动方向 默认为顺时针
#### 如果连接类型为直接连接方向不变
#### 否则改变方向


------------
#### 代码
```cpp
#include <bits/stdc++.h> //万能头是陋习 
using namespace std ;
int n , a , b , c ;
bool flag ; //flag为滑轮转动方向 
int main()
{
	cin >> n ;
	for( int i = 1 ; i < n ; ++i ){
		cin >> a >> b >> c ;
		if( c == 1 ) flag = !flag ; //如果是交叉连接就转变方向 
	}
	cout << flag ? 0 : 1 ; //压行也是陋习
	return 0 ; 
}
```

[AC](https://www.luogu.com.cn/record/40438399)
### 求通过 /*~__~*/



---

## 作者：kgory (赞：1)

这题一开始把我惊到了：**收割机**，外带一堆名词：皮带，驱动滑轮，被驱动滑轮。我还以为跟物理有关呢（~~物理学渣瑟瑟发抖~~）后来仔细看看题目，才发现挺简单的。

就是给你很多两个数的关系，0则两个数数值相同，1就相反。**第一个数的初始值为0**，（这个把样例模拟一遍就知道了）。然后输出答案。

还有一点就是题目中说明的：“皮带的顺序是混乱的”，所以要先按s排序，也就是先让1号和其他数处理。

然后，就只剩代码了...

```
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

int b[1005]; //最终答案

struct Node { //开不开结构体随你，个人认为开可能方便一些
    int s;
    int d;
    int c;
}a[1005];

bool cmp (Node x,Node y) { //直接按s排序
    return x.s<y.s;
}

int main () {
    int n,i;
    scanf ("%d",&n);
    b[1]=0;
    for (i=2;i<=1005;i++) b[i]=1000; //为了后文的比较
    for (i=1;i<=n;i++)
        scanf ("%d%d%d",&a[i].s,&a[i].d,&a[i].c);
    sort (a+1,a+n+1,cmp); //排序
    for (i=1;i<=n;i++) {
        if (a[i].c==0) {  //相同情况
            int s=min (b[a[i].s],b[a[i].d]); 
            b[a[i].s]=b[a[i].d]=s; //完全不用像我这样写，其实一句话就没了
        }
        else {  //不同情况
            if (b[a[i].s]==1) b[a[i].d]=0;
            else if (b[a[i].s]==0) b[a[i].d]=1;
            else if (b[a[i].d]==1) b[a[i].s]=0;
            else if (b[a[i].d]==0) b[a[i].s]=1;
            //4种情况讨论
        }
    }
    printf ("%d\n",b[n]); //答案
    return 0;
}
```
附：我的代码可能还有不完美的地方，请私信找我，谢谢

---

## 作者：codemap (赞：0)

~~这到题的题面真的吓人,其实就是道大水题~~

第一思路:

直接将每条边存为一个结构体,将他们排序,形成链,然后扫一遍枚举$1$的个数

如果为偶数,说明有偶数个交叉连接,抵消了,还是顺时针,输出$0$

否之,没有抵消,逆时针,输出1

所以很容易得出以下代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct node
{
	int u;//前节点
	int v;//后节点
	bool c;
}a[1001];
bool cmp(node x,node y)//排序函数
{
	return x.u<y.u;//从小到大,变成一个链
}
int main()
{
	int n,i,s=0;
	cin>>n;
	for(i=1;i<n;i++)
		cin>>a[i].u>>a[i].v>>a[i].c;
	sort(a+1,a+n,cmp);//排序
	for(i=1;i<n;i++)
		if(a[i].c)//如果是1
			s++;//++
	if(s%2==0)//如果是偶数个
		cout<<0;
	else//否则
		cout<<1;
	return 0;
}
```

然而,写完之后,我马上就发现(应该是我太弱了,大佬们肯定直接就发现了),完全没有必要这样

这道题简化的意思:

给你几条边,他们组成一条链，每条边有一个$bool$变量,问从第一个点到最后一个这些

### 所以,根本不需要用结构体和排序,连数组都不用,直接在输入时枚举就行了

~~我还是太弱了,这都没有直接想出来~~

得出代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int n,i,s=0,a,b;
	bool f;
	cin>>n;
	for(i=1;i<n;i++)
	{
		cin>>a>>b>>f;
		if(f)//如果是1
			s++;//++
	}
	if(s%2==0)//如果是偶数个
		cout<<0;
	else//否则
		cout<<1;
	return 0;//完美结束
}
```
# 请勿抄袭

---

