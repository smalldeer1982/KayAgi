# Jzzhu and Children

## 题目描述

`Jzzhu`给学校里的$n$个孩子发糖果，编号从$1$到$n$排成一队，第$i$个孩子想得到至少$a_i$个糖果。  
`Jzzhu`的操作如下：
- 给队首的孩子$m$个糖果
- 如果这个孩子已经得到满足，他就会回家，否则他会到队尾。
- 在队列非空时重复上述两个操作  

在满足上述条件的情况下，求出最后回家的孩子的编号

## 样例 #1

### 输入

```
5 2
1 3 1 4 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
6 4
1 1 2 2 3 3
```

### 输出

```
6
```

# 题解

## 作者：cyffff (赞：6)

# CF450A Jzzhu and Children
[传送门](https://www.luogu.com.cn/problem/CF450A)

一道队列练习题，可以轻松地A掉，不太明白楼下的 $dalao$ 为什么要用 $pair$ ，结构体队列就够了。

## 思路
每次读取队首元素，弹出它，把所需糖果数减去 $m$ 颗，如果结果$>0$，就把结果再次插入到队尾。重复上面的操作直至队列长度为$1$，输出这项的编号就行了。

$tips:$队列插入结构体时的格式为 队列名字$ .push$((结构体类型){结构体的各项}) ，具体见下面的代码。

上AC代码~
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{//定义结构体保存每个孩子的信息
	int id,t;
};
int main(){
	queue<node>p;//定义结构体队列p
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		int t;
		scanf("%d",&t);
		p.push((node){i,t});//插入编号和所需糖果数量
	}
	while(p.size()>1){
		int t=p.front().t,q=p.front().id;
		t-=m;
		p.pop();
		if(t>0){
			p.push((node){q,t});
		}
	}
	cout<<p.front().id;
	return 0;
}
```
再见qwq

---

## 作者：Jsxts_ (赞：4)

看到一道绿色的水题就来做了。

[原题](https://www.luogu.com.cn/problem/CF450A)

这道题$n$与$m$数据范围小，可以直接暴力做出。用一个[队列（queue）](https://blog.csdn.net/ZHLZYF/article/details/83280481)代表当前每个学生在队内的情况。每次取出队首，按照题目要求模拟即可。

注意因为要输出的是编号，所以队列要存两个数，一个是还需多少糖果，一个是编号，用pair解决。

AC代码：

```cpp
#include <cstdio>
#include <iostream>
#include <queue>//队列头文件 
using namespace std;
typedef pair<int,int> pii;//pair 
queue<pii> q;//队列存两个数，id和还需糖果数 
int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i = 1;i <= n;i ++ ) {
		int x;
		scanf("%d",&x);
		q.push(make_pair(x,i));//每一个学生进队列
		//i就是编号 
	}
	while (!q.empty()) {//队列非空 
		int x = q.front().first - m;
		//给队首m个糖果，还需的糖果数量减m 
		int id = q.front().second;
		q.pop(); 
		if (!q.size()) {//如果队列为空，直接输出编号 
			printf("%d",id);
			break;
		}
		if (x > 0) {//还没有得到满足 
			q.push(make_pair(x,id));
		}
	}
	return 0;
}
```

时间：664ms

其他dalao们还有另一种更简单的做法，这里就不说了，这道题是我当做队列练习做的，就用了这种方法。另一种方法可以参考其他的题解。

---

## 作者：luohanzhao (赞：2)

[点我看题~~~~](https://www.luogu.com.cn/problem/CF450A)

~~很显然，这是一道大水题，最多算橙题~~

### 咳嗯，我们进入正题：

我的解法相较各路大佬不同，**无数组，无队列，一边输入一边就在做** ， $ O1 $ 存储 $ On $ 时间复杂度

我们知道轮到最后一个的条件是最后一轮最后一个拿完而我们又可以用 **个数/一轮拿的个数** 向上取整得到轮数

即：


```cpp
ceil(x*1.0/m*1.0);
```

$c$ ++中，$ceil$ 函数即将一个浮点数向上取整。

---
就这样我们判断一下那个最大，用 $mx$ 存一下，这里有技巧，是要 **大于等于** $mx$ 更新, **切记，必须要有等于号，才能把同样轮数的最后一位更上去** 

## $AC code$

```cpp
#include<bits/stdc++.h>
int n,m,mx,sum,x; 
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		x=ceil(x*1.0/m*1.0);
		if(x>=mx)mx=x,sum=i;
	}printf("%d",sum);
	return 0;
} 
```
都看到这里了，点一个赞再走吧

---

## 作者：CobaltChloride (赞：2)

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,i,j,m;
struct p{
	ll c/*个数*/,o/*序号*/;
}a[101];
void f(){
	p b=a[1];
	b.c=a[1].c-m;
	for(i=1;i<n;i++) a[i]=a[i+1];//排队
	a[n]=b;//到队尾
	if(b.c<=0) n--;//走开
}
int main(){
	cin>>n>>m;
	for(i=1;i<=n;i++) cin>>a[i].c,a[i].o=i;//输入
	while(n!=1) f();//直到剩下一个
	cout<<a[1].o;//输出
    return 0;
}
```

---

## 作者：SqrtSecond (赞：1)

简单的暴力模拟即可。

维护一个队列存放每个孩子排队的位置。

再用一个$a$数组来存放这个孩子还需要的需求量。

如果需求量为负数或$0$他就会回家。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[101],ans;
queue<int> q;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;++i)
	{
		cin>>a[i];
		q.push(i);//进入队列 
	}
	while(!q.empty())
	{
		ans=q.front();q.pop();//更新答案 
		a[ans]-=m;//减少每个孩子的需求 
		if(a[ans]>0)q.push(ans);//回队 
	}
	cout<<ans; 
}
```

---

## 作者：Mysterious_bird (赞：1)

#### 前置知识：
我们在这题用到的算法是STL中的queue

先来熟悉一下queue

定义  #include<queue>    //万能头也包含
  
详细用法:
 
定义一个queue的变量     queue<Type> a
  
查看是否为空范例        a.empty()    是的话返回1，不是返回0;
  
从已有元素后面增加元素 a.push()
  
输出现有元素的个数  a.size()
  
显示第一个元素  a.front()
  
显示最后一个元素 a.back()
  
清除第一个元素 a.pop()
  
好，这题还要用到一个知识，pair

pair比较简单，可以理解成一个打包盒
  
pair <int,int> a
  
上面就是他的定义

### code：
```cpp
#include <cstdio>
#include <queue>    //包含queue的头文件
using namespace std;
queue <pair<int,int> > a;   //定义一个queue，里面有两个相关联的容器
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   //注意，不能从0~n-1，编号是从1开始的
    {
        int x;
        scanf("%d",&x);
        a.push(make_pair(x,i));     //读入x和编号
    }
    int cnt,s;
    while(a.size()!=1)  //重复循环直到队列里只剩最后一个
    {
        s=a.front().first;  //s=队列中第一个元素的前一个量，也就是这个孩子想要的糖
        cnt=a.front().second;   //cnt=队列中第一个元素的后一个量，也就是这个孩子的编号
        a.pop();    //不管怎么样，先弹出，反正已经记录好了
        s-=m;   //给他糖，则需要的糖数就减少
        if(s>0) //如果还不够
        {
            a.push(make_pair(s,cnt)); //接着读入，注意，队列里读入都是往最后压入  
        }
    }
    printf("%d\n",a.front().second);    //输出最后一个孩子的编号
    return 0;
}
```
望通过，谢谢

---

## 作者：溪水瑶 (赞：1)

## 普通的模拟题
这题用一个队列容器来模拟队列元素是pair类型的，first用来存每个小朋友想要的糖数，second用来存小朋友的序号，然后开始模拟，模拟出口是当队列迟到等于1时就输出当前队列里小朋友的序号。
## 具体代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,tot,sum;
queue<pair<int,int> >a;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>x;
		a.push(make_pair(x,i));
	}
	while(a.size()!=1){
		tot=a.front().first;
		sum=a.front().second;
		a.pop();
		tot-=m;
		if(tot>0)a.push(make_pair(tot,sum));
	}
	cout<<a.front().second<<endl;
	return 0;
}
```



---

## 作者：to_be_continued (赞：1)

首先这题只想说 多谢翻译。

翻译非常明显的说出了 队尾这个概念，那么直接用队列做不就好了吗

都没什么好说的 首先用一个队列存下它们的值 然后再用一个队列存下它们的下标，每次做到这个数就减去m。如果这个数大于0，那么就把这个减去m的数加到队尾。最后输出队尾指针，en。 ~~不就好了吗~~

n，m还只有100 a[i]的最大值也只有100 队列里最多也就1000000完全存的下 




```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

int a[101];
int q[1010101][3];//乱开的足够大就好

int main(){
	int n,m;
	scanf("%d%d",&n,&m);//100我连快读都懒得码了
	for (int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		q[i][1]=a[i];//直接进队列
		q[i][2]=i;
	}
	int head=1,tail=n;//首尾指针初始化
	while (head<=tail){//如果head>tail只能说明人都走完了，那就输出q[tail][2]就好了
		q[head][1]-=m;
		if (q[head][1]>0){//如果还有数值的话，加入队尾
			tail++;
			q[tail][1]=q[head][1];
			q[tail][2]=q[head][2];//延续上一个的下标
		}
		head++;
	}
	printf("%d",q[tail][2]);//完美输出
}
```


此人为C++蒟蒻，在此膜拜各位C++巨佬。

---

## 作者：EuphoricStar (赞：0)

这是一道不错的适合新手练习的队列模拟题。

思路：读入每个孩子的糖果需求 $a_i$，并将每个孩子按编号顺序先添加进队列中。

之后，不断取得队首孩子的编号 $p$ 并将其弹出，给这个孩子 $m$ 块糖果，如果它不满足需求（即 $a_p > 0$）则将这个孩子的编号再添加进队尾。

当队列只剩下一个孩子时停止循环，这个孩子就是最后回家的。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, a[105];
queue<int> q;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), q.push(i);
    while (q.size() > 1)
    {
        int p = q.front();
        q.pop();
        a[p] -= m;
        if (a[p] > 0) q.push(p); 
    }
    printf("%d", q.front());
    return 0;
}
```


---

## 作者：WinterRain208 (赞：0)

CF450A 【Jzzhu and Children】

队列入门题，连手写的欲望都没有，直接用$STL$自带的$queue$。

重点在于记录序号，也不难，再开一个队列维护即可。

### $CODE$

```
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;
const int N=1e5+5;

int n,m,x;
queue < int > q1,q2; 
int main(){
	scanf("%d%d",&n,&m);
	F(i,1,n){
		scanf("%d",&x);
		q1.push(x),q2.push(i);
	}
	int num=n;
	while(!q1.empty()){
		int pos=q1.front();
		if(pos-m<=0){
			if(num==1){
				cout<<q2.front()<<endl;
				return 0;
			}
			else q1.pop(),q2.pop();
			--num;
		}
		else{
			q1.push(pos-m),q2.push(q2.front());
			q1.pop(),q2.pop();
		}
	}
    return 0;
}
```

$wtrl$。

---

## 作者：_Legacy (赞：0)

#### 分析

当我做这题时我在想：

> 这题有没有不用队列做的~~偷懒~~简单方法

我们看，下面的是队列的模拟：

`1号 2号 3号 4号 5号` 

假设1号没满意回到队尾

`2号 4号 1号`

只要1号排的次数最多，只要不求准确离开时间，就不用队列！

再简单一点来说：只要看每个孩子要排几次队，排最多次且最后的孩子最后走。

注意：

1. 因为求的是排队次数，所以要有一个求次数的判断。
2. 因为要看是否为同大小中最后的，判断中应是$a_i\leq \text{max}$。

#### 上代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n,m,a[100000]；
	int maxx=-1,ans=-1;//孩子不可能要-1个糖
	cin >> n >> m;
	for(int i=0;i<n;i++){
		cin >> a[i];
		if(a[i]%m==0) 
			a[i]/=m;
		else
			a[i]/=m,a[i]++;
		//求次数部分
		if(a[i]>=maxx){
			maxx=a[i];
			ans=i+1;
		} 
		//求是否为最后的，最大(或之一)的号数
	} 
	cout << ans;
}
//CF450A
```

[AC记录](https://www.luogu.com.cn/record/32981637)

---

## 作者：修罗海神王 (赞：0)

##### 楼下的各位大佬们好像都用了队列，

## 但本蒟蒻觉得此题拿来练习一下
### 循环&数组插入or弹出，
###### ~~比较好~~

废话不说，先双手呈上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,a[110],b[110];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) {scanf("%d",&a[i]);b[i]=i;}
	x=n;
	while(1)
	{
		if(x==1) {cout<<b[1]<<"\n";break;}
		if(a[1]<=m) {for(int j=1;j<=x-1;j++) a[j]=a[j+1],b[j]=b[j+1];x--;}
		  else {a[1]-=m;a[x+1]=a[1];b[x+1]=b[1];for(int j=1;j<=x;j++) a[j]=a[j+1],b[j]=b[j+1];}
	}
	return 0;
}
```

然后，我们来逐步分析：

    1、输入n,m和a数组，并且将每个i标上编号：
```cpp
cin>>n>>m;
for(int i=1;i<=n;i++) {scanf("%d",&a[i]);b[i]=i;}
```


    2、然后，将n赋值给x，构造死循环：
```cpp
x=n;
while(1)
```

    3、死循环内部，首先写结束条件，
    便是题目中只剩最后一个孩子时，
    输出他的编号，接着跳出死循环：
```cpp
if(x==1) {cout<<b[1]<<"\n";break;}
```

    4、如果这个小朋友的满足欲望糖果数在m之下的话
    （看来这个小朋友并不贪心，害），
    就将他的位置挤掉，所有人上前一格，
    注意编号也要跟着上来哦，最后总数减一：
```cpp
if(a[1]<=m) 
{
    for(int j=1;j<=x-1;j++) 
       a[j]=a[j+1],b[j]=b[j+1];x--;
}
```
    5、否则的话，就将他的满足欲望减去m，表示他已经得到了剩下数量，
    将他的满足欲望数和编号排到队尾+1，
    然后用同上的办法，只不过这次要到x，
    将所有人都调前一格，注意总数这次不必减一，
    因为原来第一个小朋友并未满足，并未离开：
```cpp
else 
{
    a[1]-=m;
    a[x+1]=a[1];
    b[x+1]=b[1];
    for(int j=1;j<=x;j++) 
       a[j]=a[j+1],b[j]=b[j+1];
}
```
    6、输出在之前已经输过了，所以不必再次输出了。
    
# Code：
~~上面好像已经有了~~（逃……

# AC抱回家



---

