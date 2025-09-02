# Holidays

## 题目描述

School holidays come in Berland. The holidays are going to continue for $ n $ days. The students of school № $ N $ are having the time of their lives and the IT teacher Marina Sergeyevna, who has spent all the summer busy checking the BSE (Berland State Examination) results, has finally taken a vacation break! Some people are in charge of the daily watering of flowers in shifts according to the schedule. However when Marina Sergeyevna was making the schedule, she was so tired from work and so lost in dreams of the oncoming vacation that she perhaps made several mistakes. In fact, it is possible that according to the schedule, on some days during the holidays the flowers will not be watered or will be watered multiple times. Help Marina Sergeyevna to find a mistake.

## 说明/提示

Keep in mind that in the second sample the mistake occurs not only on the second day, but also on the sixth day, when nobody waters the flowers. However, you have to print the second day, i.e. the day with the minimal number.

## 样例 #1

### 输入

```
10 5
1 2
3 3
4 6
7 7
8 10
```

### 输出

```
OK
```

## 样例 #2

### 输入

```
10 5
1 2
2 3
4 5
7 8
9 10
```

### 输出

```
2 2
```

## 样例 #3

### 输入

```
10 5
1 2
3 3
5 7
7 7
7 10
```

### 输出

```
4 0
```

# 题解

## 作者：songxiao (赞：11)

~~线段树是啥?差分是啥？统统不需要，~~
纯**模拟**！
所以应该很好理解。

题目大意（比原翻译容易理解）：

```
n天假期，安排m个人来浇花，第i个人负责a~b天，问花是否可以每天都被浇水且不重复。 可以的话输出“OK”，不可以的话输出最早出问题的那天的天号以及那天花被浇了多少次水。

第一行输入n和m，接下来m行每行输入a和b
```

主要思路（有点桶排序的思想，x为桶）：
- 输入n和m
- 循环输入a和b（不用数组，边输入边执行）
- 循环a~b，把x（初始为0）的a~b个元素+1（因为我是从0开始，所以会减1）
- 循环n遍，如果不符合要求直接输出，结束程序
- 程序未结束输出OK

AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,m,a,b;	//RT
    cin>>n>>m;	//输入
    int x[n]={0};	//初始为0
    for(int i=0;i<m;i++)	/循环m遍
    {
        cin>>a>>b;	//输入
        for(int i=a-1;i<b;i++)	//从0开始，所以-1
        {
            x[i]++;	//x相当于“桶”
        }
    }
    for(int i=0;i<n;i++)	//循环n遍模拟每天浇花
    {
        if(x[i]!=1)	//如果有问题
        {
            cout<<i+1<<' '<<x[i];	//主要+1然后输出
            return 0;	//直接结束
        }
    }
    cout<<"OK";	//如果还没结束就是符合要求，输出
    return 0;	//结束
}


```

---

## 作者：ziiidan (赞：9)

一道一维差分的入门级题目 ~~（虽然我线段树快写完了才发现）~~

题目大意；

区间加，看最后是否存在某个位置不为1

一维差分的原理：

1. 打开始位置标记，在结束位置的下一个位置打上相反的标记
2. 前缀和使得标记持续影响一段区间来将差分数组恢复成所求数组，所打的相反的标记使得之前的标记的影响能够控制在实际所需修改的范围内

放上蒟蒻的代码：

```cpp
#include<iostream>
#include<cstdio>

using namespace std;

const int maxn = 105;

int n, m;
int fr, to;

int c[maxn];

inline int read(void)
{
	int s = 0, w = 1;
	char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') w = -1;
	for(; ch <= '9' && ch >= '0'; ch = getchar()) s = s * 10 + ch - '0';
	return s * w;
}

int main()
{
	n = read(); m = read();
	for(register int i = 1; i <= m; i++) 
	{
		fr = read(); to = read();
		c[fr]++;
		c[to + 1]--;
	}
	for(register int i = 1; i <= n; i++) 
	{
		c[i] = c[i - 1] + c[i];
		if(c[i] == 0) // 如果出现不合法的情况，直接停止
		{
			cout << i << ' ' << 0 << '\n';
			return 0;
		}
		if(c[i] > 1) // 同上
		{
			cout << i << ' ' << c[i] << '\n';
			return 0;
		}
	}
	cout << "OK" << '\n'; // 没有出现不合法的情况，即合法
	return 0;
}
```

有什么疑问可以直接在评论区说或者洛谷私信均可

谢谢阅读

---

## 作者：曼恩薄荷 (赞：4)

题目要求：检查是否每天有且仅有一人来浇水，即对于所有的 _i∈1~n_ m个区间中是否只有一个覆盖到i。

	
题目深化：即区间修改，单点查询————可以使用线段树等数据结构维护。这里选用代码量小的树状数组，用差分优化即可，每次修改在差分数组的l位置+1，r+1位置-1。然后统计i的前缀和即为i被浇水的次数。

上代码：


```cpp
#include<bits/stdc++.h>
using namespace std;

int tree[105];
int n,m;

int lowbit(int k){return k&(-k);}

void add(int x,int v)//修改 
{
	while(x<=n)
	{
		tree[x] += v;
		x += lowbit(x);
	}
}

int sum(int x)//查询前缀和 
{
	int ret = 0;
	while(x != 0)
	{
		ret += tree[x];
		x -= lowbit(x);
	}
	return ret;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		add(l,1);//差分数组修改 
		add(r+1,-1);
	}
	for(int i=1;i<=n;i++)//枚举i判断是否合法 
	{
		int s = sum(i);
		if(s != 1)
		{
			printf("%d %d",i,s);//不合法直接跳出 
			return 0;
		}
	}
	puts("OK");//如果都合法就输出OK√ 
	return 0;
}
```

---

## 作者：锦瑟，华年 (赞：3)

好么，又一题水题。

题目：n天假期，安排m个人来浇花，第i个人负责[a[i],b[i]]天，问花是否可以每天都被浇水且不重复。 可以的话输出“OK”，不可以的话输出最早出问题的那天的天号以及那天花被浇了多少次水。（其中，输入第一行为N和M）

1≤n,m≤100 1≤a[i]≤b[i]≤n b[i]≤a[i+1]

好了，很显然，这题是一道明显的差分。

首先，我们来了解一下差分是什么：输入l和r，在l和r之间每个数都加上一个数。

那么我们如何实现呢？简单，开一个桶，在a[l]上加上这个数，再在a[r+1]上减去这个数（使其到了r+1时就自动抵消了）。由于输入通常不是一组l,r，所以，把l,r全部输进来，进行以上操作，最后从头到尾遍历一遍，把a[i]+=a[i-1]即可。

差分代码：

	for(i=1;i<=m;i++){
		int l,r,c;
		scanf("%d%d%d",&l,&r,&c);
		a[l]+=c;a[r+1]-=c;
	}
    for(i=1;i<=n;i++){
		a[i]+=a[i-1];
    }
    
差分做完了之后，只需最后再模拟一遍就可以了。

代码：

	#include<stdio.h>
	using namespace std;
	int a[105];
	int main(){
		int n,m,i;
		scanf("%d%d",&n,&m);
		for(i=1;i<=m;i++){//差分核心程序1
			int l,r;
			scanf("%d%d",&l,&r);
			a[l]+=1;a[r+1]-=1;
		}
		for(i=1;i<=n;i++){
			a[i]+=a[i-1];//差分核心程序2
			if(a[i]!=1){//判断输出
				printf("%d %d",i,a[i]);
				return 0;//一定要结束程序
			}
		}
		printf("OK");
		return 0; 
	}
    
over~，求过，(^_^)。

---

## 作者：CrTsIr400 (赞：2)

~~吓死我了，还以为是线段树~~
#### 后来一看数据范围：
$1<=n,m<=100$
#### 并且
$1<=l<=r<=100$
### 思路：一维差分。
### 当每次输入$l$和$r$时模拟即可。
```cpp
scanf("%d%d",&n,&m);
for(int i=1;i<=m;i++)
{
	scanf("%d%d",&l,&r);
	for(int j=l;j<=r;j++)a[j]++;//模拟差分
}
```
### 时间复杂度：$O(nm)$
~~真不用写线段树~~
##### ~~全洛谷最短代码？~~
```cpp
#include<cstdio>
int a[101],l,r,m,n,b=0;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&l,&r);
		for(int j=l;j<=r;j++)a[j]++;//模拟差分
	}
	for(int i=1;i<=n&&!b;i++)
	if(a[i]!=1)printf("%d %d",i,a[i]),b=1;//如有不合法，标记变量（不用写括号）
	if(b==0)printf("OK");
}
```


---

## 作者：rfsfreffr (赞：2)

~~求数据加强qwq~~

## 其实这题数据可以加到10w甚至100w,因为我有$O(nlogn)$甚至$O(n)$的算法

思路:

首先将数据读入，用一个结构体存储


然后对其的区间开始的时间进行排序:

### 接下来就是代码的核心部分了

经过缜密的思考（也WA了很多次）,发现有一下几种情况:

1.如果$y_i=x_{i+1}$($y_i$表示a[i].y,$x_i$表示a[i].x,为了方便，后面都这么写)

俩区间的情况:

[$x_i$,$y_i$] .[$x_{i+1}$,$y_{i+1}$]

因为$y_i=x_{i+1}$,所以$y_i$就是一个浇水2次或2次以上的一天

2.如果$y_i>x_{i+1}$

即[$x_{i+1}$,$y_{i+1}$]的有一块被[$x_i$,$y_i$]盖住了

因为是求第一个出问题的天数，可以推断出$x_{i+1}$是第一天出问题的

所以$x_{i+1}$就是一个浇水2次或2次以上的一天

3.如果$y_i+1<x_i$ 

则$y_{i+1}$这一天没有浇到水，所以$y_{i+1}$是一个没有被浇到水的一天。

4.如果对于$0<=i<=m-1$的$i$,以上3条都不成立。

如果$y_m<n$ 则$y_m+1$这一天没有浇水。

5.为什么$i$从0开始，因为$x_0=y_0=0$,他的浇水区间为[0,0]。

所以如果每天都有浇到水必须有一个[1,$x$]和他对接，所以要从0开始。

6.否则输出"OK"

时间复杂度:$O(nlogn+n)$

空间复杂度:$O(n)$

# 代码:
~~~
#include<bits/stdc++.h>
#define for_int register int
#define endl '\n'
#define ll long long
#define ld long double
using namespace std;
struct oi{
	int x,y; //表示其浇水的区间为[x,y]
};
bool cmp(oi x,oi y){
	return x.x<y.x;//按照其开始时间排序
}
int n,m,ans=1;
oi a[10001];
void calc(int x,int i){
	for(for_int j=i+1; j<=m; j++){//因为有可能出现区块融合的现象，所以必须继续往后枚举，看看这天浇了几次水
		if(x>=a[j].x&&x<=a[j].y){
			ans++;
		} else {
			cout<<ans<<endl;
			exit(0);//输出之后就关掉程序
		}
	}
}
int main() {
	cin>>n>>m;
	for(for_int i=1; i<=m; i++){
		cin>>a[i].x>>a[i].y;
	}
	sort(a+1,a+1+m,cmp);
	for(for_int i=0; i<=m-1; i++){//1~4点的判断,因为是找第一个出现问题的天数，所以输出完了就return 0;
    //切记i从0开始!!!
		if(a[i].y==a[i+1].x){
			cout<<a[i+1].x<<" ";
			ans++;
			calc(a[i+1].x,i+1);
			cout<<ans<<endl;
			return 0;
		} else if(a[i].y>a[i+1].x){
			cout<<a[i+1].x<<" ";
			ans++;
			calc(a[i+1].x,i+1);
			cout<<ans<<endl;
			return 0;
		} else if(a[i].y+1<a[i+1].x){
			cout<<a[i].y+1<<" "<<0<<endl;
			return 0; 
		}
	}
	if(a[m].y<n){//第5点判断
		cout<<a[m].y+1<<" "<<0<<endl;
		return 0;
	}
	cout<<"OK"<<endl;//如果每天都之浇了一次水输出"OK"
	return 0;
} 
~~~

## 番外:

后来我发现数据时已经按照其开始时间排序的，所以那行sort都不需要了(但题面并没有保证)

这样,时间复杂度会降到$O(n)$


---

## 作者：溪水瑶 (赞：1)

## 为啥我感觉这是桶排序的思想啊！！

不造为啥，他们邀用辣么复杂的想法来做这题，这题用一个数组将他们从a[i]到b[i]里的每一天都加一次，最后循环N次来看看有没有那天是没有浇水的或浇了多次的；
代码简陋，大佬勿喷。
## 这里是代码：
```cpp
#include<bits/stdc++.h>
#define QwQ puts("QwQ")
#define mian main
using namespace std;
int n,m,a,b,c[1001];//c数组用来做统计每天浇水的量；
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);
		for(int j=a;j<=b;j++)
			c[j]++;
	}
	for(int i=1;i<=n;i++){
		if(c[i]!=1){
			printf("%d %d",i,c[i]);
			return 0;
		}
	}
	puts("OK");
	return 0;
}
```


---

## 作者：Cream_ (赞：1)

# 又是一道入门的黄题！
## 这个题。。
### 还是看代码吧。。
#### 都在代码里了。。
~~我的孩子们~~，去追逐吧！！

我还是个**蒟蒻**，别打我。。

```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int a[1001],l,r,n,m,flag;

int main(){
	cin >> n >> m;
	for (int i = 1;i <= m;i++)
	{
		scanf("%d %d",&l,&r);
		for (int j = l;j <= r;j++)   //统计每天花浇的次数。 
		{
			a[j]++;
		}
	}
	for (int i = 1;i <= n;i++)
	{
		if (a[i] != 1)			//判断没浇或浇了好几次的情况。 
		{
			cout << i << " " << a[i] <<endl;//先日期后浇的次数。 
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		cout << "OK" << endl;
	}
	return 0;
}
```


---

## 作者：yzx72424 (赞：0)

心路历程：看看题目就准备写个模拟

又看了看另一个dalao在写前缀和，再看了看数据，继续写模拟。。。

读入到aa[i] ,bb[i],表示【aa[i] ,bb[i]】浇花。然后一个a[j]数组记录第j天浇花a[j]次，然后找使得a[j]=0或a[j]>1的j的最小值，找到之后直接return 0

```
#include<bits/stdc++.h>
using namespace std;
int aa[105],bb[105],a[101],m,n;
int main(){
		scanf("%d%d",&m,&n);
		for (int i = 0; i <n; i++)scanf("%d%d",&aa[i],&bb[i]);	
	     for(int i=0;i<n;i++)
			for(int j=aa[i];j<=bb[i];j++)
				a[j]++;
 
		for(int j=1;j<=m;j++)
			if(a[j]==0||a[j]>1) 
		    {printf("%d %d",j,a[j]);
		    return 0;
		    }
		 printf("OK");
}

```


---

## 作者：wzm2007 (赞：0)

    模拟即可
    读入时每次在边界范围内每个花加1
    最后从头到尾扫一遍,把不符合条件的输出

------------

    #include<iostream>
    using namespace std;
    int a[110];
    int main()
    {
        int n,m;
        cin>>n>>m;
        for(int i=0;i<m;i++)  //累加
        {
            int x,y;
            cin>>x>>y;
            for(int j=x;j<=y;j++)a[j]++;
        }
        for(int i=1;i<=n;i++)  //扫一遍
            if(a[i]!=1)
            {
                cout<<i<<' '<<a[i];
                return 0;
            }
        cout<<"OK";
        return 0;
    }

---

