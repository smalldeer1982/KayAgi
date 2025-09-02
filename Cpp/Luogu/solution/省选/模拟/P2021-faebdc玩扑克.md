# faebdc玩扑克

## 题目背景

faebdc 和 zky 在玩一个小游戏


## 题目描述

zky 有 $n$ 个扑克牌，编号从 $1$ 到 $n$，zky 把它排成一个序列，每次把最上方的扑克牌放在牌堆底，然后把下一张扑克牌拿出来输出，最终输出的序列恰好是从 $1$ 到 $n$，faebdc 问你原序列是什么，因为 faebdc 神犇早已在 $\mathcal O (1)$ 的时间得出结果，如果你在 1 s 内答不出来，faebdc 会吃了你。


## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le {10}^6$。

## 样例 #1

### 输入

```
13```

### 输出

```
7 1 12 2 8 3 11 4 9 5 13 6 10 ```

# 题解

## 作者：yummy (赞：54)

看到各位大佬们使用各种方法，数学优化，二分等，本蒟蒻很感(wu)慨(yu)，~~因为我不会呀，~~，然而，经过我的思考，本题完全没有必要死磕，可以使用一种巧妙的方法。

Updated at Aug.28:修改使其更规范，把不容易理解的部分讲的更详细一些。

---

首先，在做此题之前，我们需要了解到的一点是：不管一张牌上面写的数字是几，只要牌的总量不变，牌的位置不变，最终这张牌到达的位置总是不变的。

换言之，一个班级（牌堆）定期换座位（洗牌），如果换座位的规则（操作牌的顺序）一直不变，那么不管某张桌子上坐着谁，这个同学换完座位后到达的位置只和桌子位置有关。

对于本题，我们需要求的一个关键数组是每个位置的同学（牌）换座位（洗牌）之后被换到了哪个位置。为了解决这个问题，我们可以假设这个牌叠是 $1,2,3,...,n$，然后按题意用STL库里的queue模拟一遍，以 $n=10$ 举个栗子。

通过模拟，我们发现，原数列变成了 $2,4,6,8,10,3,7,1,9,5$。

这里，$a_1=2$ 不仅表示按顺序排的牌堆中 $1$ 变到了 $2$ 的位置，还意味着**所有在 $1$ 位置的牌都会被移动到 $2$ 位置。**

于是，更关键的操作：**如果想要让 $2$ 位置出现 $2$，我们需要让原来的 $1$ 位置的牌变成 $2$。**

![](https://cdn.luogu.com.cn/upload/pic/30039.png)

(下行是我们要的答案）

那么，根据这种方法，就可以求解了，复杂度 $O(n)$

为满足一些人的情绪，贴代码——

```
#include<iostream>
#include<cstdio>
#include<queue>//头文件，不用解释
using namespace std;
queue<int>a;
int sc[1000005],ans[1000005];
int n;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        a.push(i);//先制造一叠牌(1,2,...,n)
    for(int i=1;!a.empty();i++)//开始模拟
    {
        a.push(a.front());
        a.pop();
        sc[i]=a.front();
        a.pop();
    }
    for(int i=1;i<=n;i++)//将i放在sc[i]处，经过一通操作后，就在正确的位置了
        ans[sc[i]]=i;
    for(int i=1;i<=n;i++)//输出
        cout<<ans[i]<<" ";
    return 0;
}
```

---

## 作者：谁懂谁伤心 (赞：26)

这题有点类似于P1996约瑟夫问题的逆运算。这题中，我用a数组表示牌堆，即a[i]=j，i表示牌堆中的第i张牌，j表示第i张牌的点数。我们只需要隔一张未被记录的牌记录一张未被记录的牌,记录即是指确定a[i]的数值。（晕了吗？看程序吧）

```cpp

#include <iostream>  
#include <cstdio>  
using namespace std;  
int a[1000001],n,s;  
int main()  
{  
scanf ("%d",&n);  
for (int i=1;i<=n;i++){for (int j=1;j<=2;j++)
{s++; if (s>n)s=1; if (a[s]!=0)j--;}a[s]=i;}  
for (int i=1;i<=n;i++)printf ("%d ",a[i]); return 0;  
}
```

---

## 作者：WorldBest丶牛顿 (赞：10)

先%一下faebdc神犇

**~~人长得又帅，讲课又好听，我超喜欢他的~~**

------------

这道题的话就是把一个从1到n的序列，按照一定规律排下去

规律：每次对空的位置隔一个放下一个数字（有数字的不看）

用1~5来举例子的话，（开始数组为00000）


1. 	0 1 0 0 0（第1位不管，“1”放在第2位）
        
2.  0 1 0 2 0（第3位不管，“2”放在第4位）
        
3.  3 1 0 2 0（第6位超过了5，把它变成1，“3”放在第一位）
        
4.  3 1 0 2 4（第3位不管（有数字的不看），“4”放在第5位）
        
5.  3 1 5 2 4（第3位不管，“5”放在第3位）

最后一行看上去可能有点矛盾，那是因为程序经过了两次第3个位置，在第二次的时候还是放在了第三个位置
    


------------
下面是代码

    

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,now=2;
int a[1000001];

int main()
{
	std::ios::sync_with_stdio(false);
	cin>>n;
	if(n==1){cout<<"1"<<endl; return 0;}//特判一下，比较快
	for(int i=1;i<=n;++i)
	{
		if(!a[now]) a[now]=i;//这个位置是空的话就放进去
		if(i==n) break;//如果放完了就可以退出了
		int cnt=0;
		while(cnt<2)//隔一个位置的的意义相当于找第二个空位
		{
			now++;
			if(now>n) now-=n;//记得随时判断now指针是不是超过了n的长度限制
			while(a[now])
			{
				now++;
				if(now>n) now-=n;
			}	
			cnt++;
		}
	}
	for(int i=1;i<=n;++i) cout<<a[i]<<" ";
	return 0;
}
```

------------

看到旁边的神犇 @衰变 用的方法好像更好呢(已征得本人同意)

ta通过队列不断往前滚动，达到效果

比如1~5

head指向队列的前一个，tail指向队列最后一位
				     
                      ↓  加入5；5前移到head（只有5就不用了）
1. 0 0 0 0 0 0 0 0 0 5 
				   ↓   加入4；5前移到head
2. 0 0 0 0 0 0 0 5 4 	 
			    ↓      加入3；4前移到head
3. 0 0 0 0 0 4 3 5 
		     ↓         加入2；5前移到head
4. 0 0 0 5 2 4 3  
	      ↓            加入1；3前移到head
5. 0 3 1 5 2 4

用tail向前移动来控制队列的长度，使超过n的数字不影响答案

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2000050];//空间两倍比较好写
int main()
{
    int head,tail,n,m;//head指向队列的前一个，tail指向队列最后一位 
    std::ios::sync_with_stdio(false);
    cin>>n;m=n;//m为下一个输入的数字 
    head=2000001;tail=2000001;//刚开始还没有输入的时候长度为0 
    while(tail-head!=n)//head和tail的差为序列长度
    {
        a[head]=m;m--;head--;
        a[head]=a[tail];tail--;head--;
    }
    head++;
    for(int i=head;i<=tail;i++)cout<<a[i]<<" ";
    return 0;
}
```


---

## 作者：_Chirin (赞：10)


这道题就是一个约瑟夫问题，把首尾连起来，从没有被填充的第二个数开始填充，注意是一个环！


```cpp
// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
int a[1000001]={0};
int n;
int chirin(int x)
{
	int t;
	t=x+1;
	if (t>n) t-=n;
	return t;
}
int main()
{
	int i,j,s=0;
	scanf("%d",&n);
	for (i=1;i<=n;i++)	
	{
		for (j=1;j<=2;j++) {
			s++;
			if (s>n) s-=n;
			while (a[s]!=0) {
			   s++;	
			   if (s>n) s-=n;
			}
		}
		a[s]=i;
	}
	for (i=1;i<=n;i++) printf("%d ",a[i]);
	return 0;
}

```

---

## 作者：Simonzhang03022007 (赞：9)


好吧，这道题其实十分的~~难~~易懂。  
我竟然足足做了45分钟（我还是太弱了）
这是本蒟蒻第一次做题解往通过和点赞   
~~请不要抄袭已做处理~~

切入正题
------------
通过读题我们发现其实就是给你一个n，然后再让你输出一个数列。  

~~以下是我的逻辑~~

1. 首先我们发现不管n是几，1永远都在第二个（此处n！=1）      
2. 然后，就是隔一个空位输出下一个数。
3. 如此重复n次就能AC了。

上代码

```
#include <cstdio>
using namespace std;
int a[1000001]={};//这里把所有的数初始化为0
int main(){
	int n;
	scanf("%d",&n);//读入
	int cnt=2;
	a[2]=1;
	int zhi=2;
	for (int i=3;i<=n;i++){
		int yier=0;
		while (yier!=2){//测量空格的数目
			zhi++;
			if (zhi>n){
				zhi-=n; //如果溢出的话从1开始
			}
			if(a[zhi]==0){
				yier++;
			}
		}
		a[zhi]=cnt;
		cnt++;
		if (zhi>n){
			zhi-=n; //同上
		}
	}
	for (int i=1;i<=n;i++){
		if (a[i]==0){
			printf("%d ",n);//因为我上面的程序只执行到n-1所以此处将其不上
		}
		else {
			printf("%d ",a[i]);	//输出
		}
	}
    while(1)
	return 0;//结束
}
```
无注释版
```
#include <cstdio>
using namespace std;
int a[1000001]={};
int main(){
	int n;
	scanf("%d",&n);
	int cnt=2;
	a[2]=1;
	int zhi=2;
	for (int i=3;i<=n;i++){
		int yier=0;
		while (yier!=2){
			zhi++;
			if (zhi>n){
				zhi-=n;
			}
			if(a[zhi]==0){
				yier++;
			}
		}
		a[zhi]=cnt;
		cnt++;
		if (zhi>n){
			zhi-=n;
		}
	}
	for (int i=1;i<=n;i++){
		if (a[i]==0){
			printf("%d ",n);
		}
		else {
			printf("%d ",a[i]);	
		}
	}
         while(1)                  
	return 0;
}
```



---

## 作者：Komes (赞：7)

见没有pascal的代码。我就来个。本人水平不行，写那么长，，别笑。。。。。。






```cpp
Var
        n,i,m,t,wz,l:longint;
        b,f,a:array[1..1000000]of longint;
Begin
//assign(input,'card.in');reset(input);
//assign(output,'card.out');rewrite(output);
        readln(n);
        for i:=1 to n do
                b[i]:=i;
        m:=n;
        t:=1;
        while t<=n do
        begin
                if m=1 then
                begin
                        f[b[1]]:=t;
                        break;
                end;
                l:=2;
                while l<=m do
                begin
                        f[b[l]]:=t;
                        inc(t);
                        inc(l,2);
                end;
                wz:=1;
                if f[b[m]]=0 then
                begin
                        a[wz]:=b[m];
                        inc(wz);
                end;
                for i:=1 to m-1 do
                        if f[b[i]]=0 then
                        begin
                                a[wz]:=b[i];
                                inc(wz);
                        end;
                m:=wz-1;
                fillchar(b,sizeof(b),0);
                for i:=1 to m do
                        b[i]:=a[i];
        end;
        for i:=1 to n do
                write(f[i],' ');
        writeln;
        readln;
//close(input);close(output);
End.
```

---

## 作者：partychicken (赞：4)

### 方法下面已经有大佬说过了，这里给出一种更简洁的实现方式

从最后的状态向前推，我们发现每次操作就是向开头插入当前未在数组中的最大值，然后把数组尾元素插到数组头部

下面是n=13是的操作过程

```cpp
13
13 12
12 11 13
13 10 12 11
11 9 13 10 12
12 8 11 9 13 10
10 7 12 8 11 9 13
13 6 10 7 12 8 11 9
9 5 13 6 10 7 12 8 11
11 4 9 5 13 6 10 7 12 8
8 3 11 4 9 5 13 6 10 7 12
12 2 8 3 11 4 9 5 13 6 10 7
7 1 12 2 8 3 11 4 9 5 13 6 10
```

然后上代码，代码有毒勿抄

```
#include<bits/stdc艹.h>

using namespace std;

deque<int>q;\\deque 大法好

int main()
{
	int n;
	cin>>n;
	for(int i=n;i>=1;i--)
	{
		q.push_front(i);
		q.push_front(q.back());
		q.pop_back();
	}
	for(int &i:q)\\c++11,loop for
	{
		cout<<i<<" "; 
	}
}
```

更短的代码

```
#include<bits/stdc++.h>
using namespace std;
deque<int>q;
int main(){
	int n;cin>>n;
	for(int i=n;i>=1;i--)q.push_front(i),q.push_front(q.back()),q.pop_back();
	for(int &i:q)cout<<i<<" ";
}
```

---

## 作者：hmh13951417981 (赞：3)

## 本题思想，一个牌之后因为要把下一张牌放到牌底
## 所以，如果结果是正序
## 那张牌之后的一张牌将与他隔开一张目前牌堆中的牌


------------

```c
#include<bits/stdc++.h>
using namespace std;
int i,n,a[1000001],now,s;
int main()
{	cin>>n;//输入 
	for(i=1;i<n;i++)//因为在填完n-1个格子后找不到空一格的格子了,所以循环到n-1 
	{s=0;//s为现在找到空了几个格子 
	while(s<2){
		now++;//now为现在查找的格子 
		if(now==n+1) now=1;//如果超过了这个序列就从头再来 
		if(a[now]==0) s++;//如果是空的，累加 
	}a[now]=i;//当找到空了1个格子的格子就可以填了 
	}
	for(i=1;i<=n;i++) {
	if(a[i]==0) a[i]=n;//要是还没填过表面是最后一个数 
	cout<<a[i]<<" ";}//输出 
	return 0;
}
```

---

## 作者：Ender_Star (赞：3)

楼下那个dalao说的不太清楚  
本蒟蒻是这样理解的  
原题相当于约瑟夫问题的逆推  
a数组是放牌的位置  
当a[i]=0时就代表该位置尚未记录（在正推过程中，该位置的牌还在）  
所以我们每隔一个目前a[i]为0的位置（在正推过程中，该位置的牌被跳过）就在下一个目前a[i]为0的位置塞牌  
代码：
```cpp
#include<cstdio>  
using namespace std;  
int n,a[1005000];  
int main(){  
    scanf("%d",&n);int now=1;  
    for (int i=1;i<=n;++i){  
        while (a[now]) {++now;if (now>n) now=1;}  
        ++now;if (now>n) now=1;  
        while (a[now]) {++now;if (now>n) now=1;}  
        a[now]=i;  
    }  
    for (int i=1;i<=n;++i) printf("%d ",a[i]);  
}  
```

---

## 作者：何卓然 (赞：2)

这道题太烦了，对这个 13 的样例我看了好久才找到类似的规律。


因为纸牌的移动只涉及到 头 和 尾，我们可以用一个数据结构 - 队列来维护输出的顺序，计数器为每一个输出过的元素，找到它在数组中的位置并给他赋值。

时间复杂度是线性的。


**Code**






    
```cpp
#include <bits/stdc++.h>
using namespace std;
#define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()
typedef long long LL;
int n,cnt,x,y,a[1000007];
queue<int> q;
int main()
{
    scanf("%d",&n);
    REP(i,1,n+1) q.push(i);
    while(1)
    {
        if (q.size() == 1)
        {
            a[q.front()] = ++cnt;
            break;
        }
        else
        {
            x = q.front(); q.pop();
            y = q.front(); q.pop();
            q.push(x);
            a[y] = ++cnt;
        }
    }
    REP(i,1,n+1) printf("%d ", a[i]);
    return 0;
}

```

---

## 作者：风清醉逍遥 (赞：2)

```
#include <stdio.h>

struct Num
{
	int stage = 0; /*当前位置是否为空*/
	int number = 0; /*当前位置存放的牌*/
};
struct Num num[1000010];

int main()
{
	int n, j = 1, cnt = 0;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		while (cnt < 2)
		{
			if (num[j].stage == 0)
			{
				cnt++; /*记录j经过的牌的张数，cnt为1时表示要放到牌堆底的牌，cnt为2时表示要输出的牌*/
				if (cnt == 2)
				{
					num[j].stage = 1;
					num[j].number = i;
					cnt = 0;
					break;
				}
			}
			j++;
			if (j == n + 1) /*j如超过了数组范围, 则将j移回首项*/
			{
				j = 1;
			}
		}
	}

	for (int i = 1; i <=n; i++)
	{
		printf("%d ", num[i].number);
	}

	return 0;
}
```

---

