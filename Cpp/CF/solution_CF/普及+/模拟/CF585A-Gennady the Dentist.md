# Gennady the Dentist

## 题目描述

Gennady is one of the best child dentists in Berland. Today $ n $ children got an appointment with him, they lined up in front of his office.

All children love to cry loudly at the reception at the dentist. We enumerate the children with integers from $ 1 $ to $ n $ in the order they go in the line. Every child is associated with the value of his cofidence $ p_{i} $ . The children take turns one after another to come into the office; each time the child that is the first in the line goes to the doctor.

While Gennady treats the teeth of the $ i $ -th child, the child is crying with the volume of $ v_{i} $ . At that the confidence of the first child in the line is reduced by the amount of $ v_{i} $ , the second one — by value $ v_{i}-1 $ , and so on. The children in the queue after the $ v_{i} $ -th child almost do not hear the crying, so their confidence remains unchanged.

If at any point in time the confidence of the $ j $ -th child is less than zero, he begins to cry with the volume of $ d_{j} $ and leaves the line, running towards the exit, without going to the doctor's office. At this the confidence of all the children after the $ j $ -th one in the line is reduced by the amount of $ d_{j} $ .

All these events occur immediately one after the other in some order. Some cries may lead to other cries, causing a chain reaction. Once in the hallway it is quiet, the child, who is first in the line, goes into the doctor's office.

Help Gennady the Dentist to determine the numbers of kids, whose teeth he will cure. Print their numbers in the chronological order.

## 说明/提示

In the first example, Gennady first treats the teeth of the first child who will cry with volume $ 4 $ . The confidences of the remaining children will get equal to $ -2,1,3,1 $ , respectively. Thus, the second child also cries at the volume of $ 1 $ and run to the exit. The confidence of the remaining children will be equal to $ 0,2,0 $ . Then the third child will go to the office, and cry with volume $ 5 $ . The other children won't bear this, and with a loud cry they will run to the exit.

In the second sample, first the first child goes into the office, he will cry with volume $ 4 $ . The confidence of the remaining children will be equal to $ 5,-1,6,8 $ . Thus, the third child will cry with the volume of $ 1 $ and run to the exit. The confidence of the remaining children will be equal to $ 5,5,7 $ . After that, the second child goes to the office and cry with the volume of $ 5 $ . The confidences of the remaining children will be equal to $ 0,3 $ . Then the fourth child will go into the office and cry with the volume of $ 2 $ . Because of this the confidence of the fifth child will be $ 1 $ , and he will go into the office last.

## 样例 #1

### 输入

```
5
4 2 2
4 1 2
5 2 4
3 3 5
5 1 2
```

### 输出

```
2
1 3 ```

## 样例 #2

### 输入

```
5
4 5 1
5 3 9
4 1 2
2 1 8
4 1 9
```

### 输出

```
4
1 2 4 5 ```

# 题解

## 作者：tanghg (赞：2)



这道题目是一道非常有意思的模拟题。

还请注意，十年 OI 一场空，不开 longlong 见祖宗，这题要开 longlong！

### 题目大意：

有 $n$ 个小孩要去拔牙，每个小孩都有对应的喊叫值 $v$，影响值 $d$ 和心理素质 $p$。
医生按照从小到大的顺序拔牙，小孩的哭声会让下一个人的心理素质-这个小孩的 $v$，在下一个小孩减掉   $\space v-1$，剩下同理。
当出现一个心理素质 $<0$ 的小孩时，剩下的所有小孩的心理素质都会减掉这个小孩的 $d$。请问有几个小孩心理素质 $\geq0$ 并且输出他们的编号。

### 思路：

首先可以将代码分为几个部分:

1.  输入。
2.  进行对哭声的处理。
3.  进行对心理素质 $<0$ 的处理。
4. 查找心理素质 $\geq0$ 的孩子。
5. 输出。

定义 $n$ 和 $v,d,p$ 数组，同时定义一个布尔数组$\space t$，用来识别小孩的心理素质是否依然 $ \geq0$。

输入就正常输入。

首先定义一个最大的循环去模拟医生从前往后拔牙，如过这个小孩心理素质已经 $<0$ 了，就跳过。

然后先处理哭声。

我们定义一个 $sad$ 变量等于这个小孩的 $v$。同时在打一个循环从下一个孩子开始一直到第 $n$ 个孩子，依然碰到了 $<0$ 的就跳过，用每个小孩的 $p $ 去减 $sad$ 变量。根据题目，因为声音会越传越小，所以每一轮 $ sad $ 要 $-1$。
然后如果 $sad$ 已经 $<0$ 了，就有必要 break 掉了，要不然后面数 $-$ 负数变 $+$ 就不好办了 

下一个部分，处理打破心理防线的小孩要给后面的小孩心理素质 $-d$ 的事情。
 
定义一个 $run=0$ 的变量来加起来所有可能出现的 $ d$。
依然定义一个循环从拔牙的小孩子下一个开始，已经崩溃的不用管。剩下的所有孩子的 $p-run$。如果出现负数或者说 $<0$，$run$ 加上这个小孩的 $d$。同时把这个小孩视作崩溃的小孩也就是把小孩对应的 $ t$ 变成 false。

然后就是到了最后一步，输出。

定义一个数组 $ans$ 和变量 $num,sz$ 如名字，数组用来存编号，$num$ 用来记有多少个小孩依旧坚强。所以只要看 $t$ 依旧是 true 的即可。
但是第一个小孩肯定无所谓，所以要在编号部分先输出  $ 1$。

完整的 code 来啦！

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
ll n,v[10000],d[10000],p[10000],ans[10000],sz,num=0;
bool t[10000];
int main()
{
    cin>>n;
    for (int i = 1; i <=n ; ++i) {
        cin>>v[i]>>d[i]>>p[i];
        t[i]= true;
    }
    for (int i = 1; i <=n ; ++i) {
        if(t[i]==0){
            continue;
        }
        ll sad=v[i];
        for (int j = i+1; j <=n ; ++j) {
            if(t[j]==0){
                continue;
            }
            p[j]-=sad;
            sad--;
            if(sad<0){
                break;
            }
        }
        ll run=0;
        for (int j = i+1; j <=n ; ++j) {
            if(t[j]==0){
                continue;
            }
            p[j]-=run;
            if(p[j]<0){
                run+=d[j];
                t[j]= false;
            }
        }
    }
    for (int i = 1; i <=n ; ++i) {
        if(t[i]) {
            ans[sz++] = i;
            num++;
        }
    }
    cout<<num<<endl;
    cout<<1<<" ";
    for (int i = 1; i <sz ; ++i) {
        cout<<ans[i]<<" ";
    }
    return 0;
}
```




---

## 作者：huwanpeng (赞：1)

看起来**模拟**能解决一切问题（强烈暗示）。

十年 OI 一场空，不开 long long 见祖宗（强烈暗示）。

解决问题：

1. 遍历每一个小孩，判断他有没有吓跑，没有则记下来。

1. 发现一个没跑的小孩后，更新后面小孩的信心值。

1. 对后面信心值为负的小孩进行逃跑处理。

AC Code：

```
#include<iostream>
using namespace std;
long long n,v[4010],d[4010],p[4010];
int brave[4010],tot;//没跑掉的勇敢孩子王 
bool f[4010];//判断孩子是否跑掉 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>v[i]>>d[i]>>p[i];
	}
	for(int i=1;i<=n;i++)
	{
		if(f[i])//孩子跑掉了 
		continue;
		brave[++tot]=i;//新的孩子王诞生了 
		for(int j=i+1;j<=n;j++)
		{
			if(f[j])
			continue;
			if(v[i]==0)
			break;
			p[j]-=v[i];
			v[i]--;//哭声分贝减一 
		}
		long long t=0;
		for(int j=i+1;j<=n;j++)
		{
			if(f[j])
			continue;
			p[j]-=t;
			if(p[j]<0&&!f[j])//刚被吓跑 
			{
				t+=d[j];//加上他的影响值 
				f[j]=true;//f为true表示当前小孩吓跑了 
			}
		}
	}
	cout<<tot<<endl;
	for(int i=1;i<=tot;i++)
	{
		cout<<brave[i]<<" ";
	}
	return 0; 
}
```


---

## 作者：wdgm4 (赞：0)

这是一道大模拟

------------
这道题只需按照题意来做即可，先判断第 $i$ 个人是否已经跑了，如果跑了直接跳过，否则就把他的牙拔掉，再循环一遍计算哭声对后面的影响，把信心为负的人（就是要跑了的人）标记，循环一遍计算对之后人的影响就行了。

还有要开 long long 。

时间复杂度 $O(n^2)$。

------------
代码里也有些注释，还不理解去读读代码吧。

## code

```cpp
#include<bits/stdc++.h>
#define XD 114514
#define yee 1919810

using namespace std;
long long n,v[4010],d[4010],p[4010];
long long len,ans[4010];
bool a[4010];
int main(){
	cin>>n;//输入 
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&v[i],&d[i],&p[i]);
	}
	for(int i=1;i<=n;i++){
		if(a[i]) continue;//如果他已经跑了就跳过 
		ans[++len]=i;//说明他的牙要被拔了 
		long long w=v[i];//哭声对之后人的影响值 
		for(int j=i+1;j<=n;j++){
			if(a[j]) continue;
			p[j]-=w;
			w--;
			if(w<=0) break;
		}
		w=0;
		for(int j=i+1;j<=n;j++){//如果有人跑了对之后人的影响 
			if(a[j]) continue;
			p[j]-=w;
			if(p[j]<0 and !a[j]){
				w+=d[j];//对影响进行累加，发生一系列连锁反应 
				a[j]=1;
			}
		}
	}
	cout<<len<<"\n";//输出 
	for(int i=1;i<=len;i++) printf("%lld ",ans[i]);
	return 0;
}

```


---

## 作者：EthanOI (赞：0)

# 前言
三次因为格式问题没过，好伤心

这是一道很有意思的模拟~~水~~题
# 做法
输入与输出各位大佬应该不用我说，主要看中间的部分。

中间主要分为三个部分：

$\begin{cases}\text{对哭声进行处理}\\\text{将心理素质 <0 的进行查找并处理}\\\text{找出心理素质不小于 0 的进行处理}\end{cases}$

可以先设出 $n$ 以及数组 $d,v,p$，通过一个 bool 变量 $t$，判断小孩的心理素质是否可以继续。

处理哭声与一个小孩退出后后面 $-d$ 都可以靠循环实现，各位大佬应该都会，详情见代码（含注释）

另外，这个数据范围有个坑，要开 long long，毕竟诗曰：十年 OI 一场空，不开 long long 见祖宗
# [$\mathbf{AC\text{ }CODE}$](https://www.luogu.com.cn/record/77916625)
```cpp
#include <bits/stdc++.h>
#define _max 4010
using namespace std;
typedef long long ll;
ll n, v[_max], d[_max], p[_max], ans[_max], cnt;
bool t[_max];
int main()
{
	/*简简单单的输入*/
    cin >> n;
    for (register int i = 1; i <= n; i++)
	{
        cin >> v[i] >> d[i] >> p[i];
        t[i] = true;
    }
    /*中间三个部分的处理*/
    for (register int i = 1; i <= n; i++)
	{
        if (!t[i]) continue; //若此人心理素质小于0：跳过 
        ll m = v[i];
        for (register int j = i + 1; j <= n ; j++)
		{
            if (t[j] == 0) continue; //心理素质已经小于0的就不用减了  
            p[j] -= m;
            m--;                   //每一轮减的数减少1 
            if (m < 0) break;      //小于0时就不用减了 
        }
        /*考虑一个人心里素质不够后后面全部-d*/
        ll _d = 0;
        for (register int j = i + 1; j <= n; j++)
		{
            if (!t[j]) continue; 
            p[j] -= _d;
            if (p[j] < 0) _d += d[j], t[j] = false;
        }
    }
    /*简简单单的输出*/
    for (register int i = 1; i <= n; i++)
        if (t[i]) ans[cnt++] = i;
    cout << cnt << endl << 1 << " ";
    for (register int i = 1; i < cnt; i++)
        cout << ans[i] << " ";
    return 0;
}
```
珍惜生命，远离抄袭，可以看完思路后自己写一遍
# 结语
像这样的模拟题是不错的，主要考察一个人写代码时的准确度，保证没有太多错误

---

## 作者：20100202w (赞：0)

这题就是一道**模拟题** 。

这道题要不断的更新自信心值才行 。


注意，要开 long long 。


方法：
	
   每次循环时先判断自信值是否小于 0 ，然后分别模拟这个孩子对别的孩子的影响，把自信心为正数的放到数组里，答案加一，
 最后分别输出。
 
 代码如下：
 
 ```cpp
#include<iostream>
#include<cstdio>
using namespace std;
struct node{
	long long v,d,p;// long long 类型
	bool f;
}a[4005]; //结构体
long long as[4005],ans;
int main()
{
	long long n;
	scanf("%lld",&n);// n 个小孩
	for(int k=1;k<=n;k++)
	{
		scanf("%lld%lld%lld",&a[k].v,&a[k].d,&a[k].p);
		a[k].f=1; //一开始大家都没跑
	}
	for(int i=1;i<=n;i++)//开始模拟
	{
		if(!a[i].f)//如果已经跑掉，则停止本次循环
			continue;
		long long v1=a[i].v;//当前影响值
		as[++ans]=i; //答案加一
		for(int j=i+1;j<=n;j++)
		{
			if(!a[j].f)continue; 
			if(v1==0)//当已经没有影响值时结束
				break; 
			a[j].p-=v1;//减去影响值
			v1--; //影响值减一
		}
		v1=0;//归零
		for(int j=i+1;j<=n;j++)
		{
			if(a[j].f==0)
				continue;		
			a[j].p-=v1;
			if(a[j].p<0&&a[j].f==1)如果刚跑掉
			{
				v1+=a[j].d;//加上影响值
				a[j].f=0;//已经跑掉了			
			}
		}
	}
	printf("%lld\n",ans);
	for(long long i=1;i<=ans;i++)//输出
		printf("%lld ",as[i]);
	return 0;//养成好习惯
}

```


---

## 作者：Tyyyyyy (赞：0)

## 纯模拟！！！
题目大意已经翻译得很明确了，这里不再叙

述，还不明白的回去再读读[题面](https://www.luogu.com.cn/problem/CF585A)
。

我们可以用一个结构体来存储每个孩子的数据，另外注意这道题要开$long long$不然会炸。

另外需要注意的一点：哭声的影响是随影响个数递减的，所以每次减完要判断影响力是不是小于$0$，不然减负数就等于加了......

为了避免不必要的多次计算，可以在结构体中开一个$bool$变量来存储该孩子是否逃跑了。当遇到该孩子已经逃跑时，哭声和逃跑的影响可以不计算。

先算哭声的影响，这样可以在算逃跑影响时一起计算后面的孩子是否逃跑。

$AC$代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,s,ans[4010];
struct child
{
	long long v,d,p;
	bool run;
}a[4010];
int main()
{
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++)
	scanf("%lld%lld%lld",&a[i].v,&a[i].d,&a[i].p);
	for(long long i=1;i<=n;i++)
	{
		if(a[i].run)continue;//跑了就跳过
		ans[++s]=i;//没跑就计数
		long long x=a[i].v;
		for(long long j=i+1;j<=n;j++)
		{
			if(!a[j].run)
			{
				a[j].p-=x;x--;
				if(x<0)break;
			}
		}
		x=0;
		for(long long j=i+1;j<=n;j++)
		{
			if(!a[j].run)
			{
				a[j].p-=x;
				if(a[j].p<0&&!a[j].run)
				{
					x+=a[j].d;
					a[j].run=1;
				}
			}	
		}
	}
	printf("%lld\n",s);
	for(int i=1;i<=s;i++)printf("%lld ",ans[i]);
	return 0;
}
```


---

## 作者：ephemeral· (赞：0)

## ~~水题~~
# 模拟大法好

按照要求对每个孩子的p值更新即可，注意一点，如果一个孩子已经跑了，那么前面孩子的哭声造成的影响不会在这个孩子处减一而是传递给下一个还没跑的孩子，所以要用一个标记数组标记每个孩子是否跑掉，每次只对没有跑掉的孩子进行更新

详细请看注释
```
#include<stdio.h>
#include<string.h>
#define maxn 4001
typedef long long ll;
int n,vis[maxn],res,ans[maxn];
ll v[maxn],p[maxn],d[maxn];
int main()
{
    while(~scanf("%d",&n))
    {
        memset(vis,0,sizeof(vis));//初始化标记数组 
        res=0;//拔牙的孩子数 
        for(int i=1;i<=n;i++)
            scanf("%lld %lld %lld",&v[i],&d[i],&p[i]); 
        for(int i=1;i<=n;i++)
        {
            if(vis[i])continue;//跑掉就不操作 
            ans[res++]=i;//没跑就拔牙 
            ll temp1=v[i],temp2=0;//temp1为拔牙孩子对后面孩子的影响,temp2为跑掉的孩子对后面孩子的影响 
            for(int j=i+1;j<=n;j++)
                if(!vis[j])//哭声只对没跑的孩子有影响 
                {
                    p[j]-=temp1;
                    temp1--;
                    if(temp1<0)break;//影响结束             
                }           
            for(int j=i+1;j<=n;j++)
            {
                if(!vis[j])//孩子跑掉只对后面没跑的孩子有影响 
                    p[j]-=temp2;
                if(p[j]<0 && !vis[j])//又有孩子跑掉 
                {
                    temp2+=d[j];//影响扩大 
                    vis[j]=1;//标记这个跑了的孩子 
                }
            }
        }
        printf("%d\n",res);
        for(int i=0;i<res;i++)
            printf("%d%c",ans[i],i==res-1?'\n':' ');
    }
    return 0;
} 
```

---

