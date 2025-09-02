# [USACO08JAN] iCow B

## 题目描述

被无止境的农活压榨得筋疲力尽后，FarmerJohn 打算用他在 MP3 播放器市场新买的 iCow 来听些音乐，放松一下。FJ 的 iCow 里存了 $N(1 \le N \le 1{,}000)$ 首曲子，按 $1..N$ 依次编号。至于曲子播放的顺序，则是按一个 FarmerJohn 自己设计的算法来决定：

- 第 $i$ 首曲子有一个初始权值 $R_i\ (1 \le R_i \le 10{,}000)$。
-  当一首曲子播放完毕，接下来播放的将是所有曲子中权值最大的那首（如果有两首或多首曲子的权值相同，那么这些曲子中编号最小的那首会被选中）。
- 一首曲子在播放结束后，它的权值会被平均地分给其他 $N-1$ 首曲子，它本身的权值清零。
- 如果一首曲子的权值无法被平均分配（也就是说，无法被 $N-1$ 整除），那么被 $N-1$ 除的余数部分将会以 $1$ 为单位，顺次分配给排名靠前的曲子（也就是说，顺序为曲目 $1$ 、曲目 $2 \cdots $ 依次下去。当然，刚播放过的那首曲子需要被跳过），直到多出的部分被分配完。

在选定的下一首曲子播放完毕后，这个算法再次被执行，调整曲子的权值，并选出再接下来播放的曲目。

请你计算一下，按 FJ 的算法，最先播放的 $T\ (1 \le T \le 1000)$ 首曲子分别是哪些。

## 说明/提示

每一首曲子播放前，三首曲子的权值分别为：

- $[10,8,11]$。播放 $\#3$，$11/2 = 5$，权值余量为 $1$。
- $[16,13,0]$。播放 $\#1$，$16/2 = 8$。
- $[0,21,8]$。播放 $\#2$，$21/2 = 10$，权值余量为 $1$。
- $[11,0,18]$。播放 $\#3$，……


## 样例 #1

### 输入

```
3 4
10
8
11
```

### 输出

```
3
1
2
3
```

# 题解

## 作者：xhQYm (赞：27)

一道简单的模拟。

先来分析样例o(*￣▽￣*)ブ：

样例长这样：
```
3 4
10
8
11
```
第一次操作：最大值为11，输出下标3。

之后平均分配值，发现无法整除(n-1)，于是分给10一个1，平均分配一下，此时，样例变成了：
```
3 4
16
13
0
```
很明显，第一个最大，所以第二次输出下标1。

接下来，发现可以直接分配，于是成为了这样：

```
3 4
0
21
8
```
第二个最大，输出下标2。之后不能平均分配，然后。。。。。（被作者吃了）

样例就是这亚子，那怎么做呢？？？

1. 先打擂台找出最大值。

2. 输出最大值。

3. 判断能不能整除(n-1)（因为除去这个数还有n-1个数）

	3.1 如果能整除，给除了自己以外的所有数加上a[i]%(n-1)。
    
   3.2 如果不能，顺序给所有数+1，自己-1。直到能整除，按2.1操作。
   
好了，就说这么多，现在上`C++`代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010;
int a[N];
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	while(k--)
	{
		int p,maxa=-1; 
		for(int i=1;i<=n;i++)
			if(a[i]>maxa)
				maxa=a[i],p=i;
		printf("%d\n",p);
		a[p]=0;
		if(maxa%(n-1)==0)
		{
			int t=maxa/(n-1);
			for(int i=1;i<=n;i++) 
				if(i!=p) a[i]+=t;
		}
		else
		{
			for(int i=1;i<=n;i++)
			{
				if(maxa%(n-1)==0) break;
				if(i==p) continue;
				else
				{
					a[i]++;
					maxa--;
				}	
			} 
			int t=maxa/(n-1);
			for(int i=1;i<=n;i++)
			{
				if(i!=p) a[i]+=t;
			}
		}
	}
	return 0;
}
```

   

---

## 作者：_LanFeng_ (赞：9)

哇题解真滴少，我来发布一篇。。。

算法标签纯模拟，其实有很多细节需要注意，主要是控制余数；

下面讲一下主要思路：

1.找最大；

2.输出序号，并将权值按算法分配给其他歌曲；

3.重复1，直到输出个数==t。

代码如下：

```cpp
#include<iostream> 
#include<cstdio> 
#include<cmath> 
#include<algorithm> 
#include<cstring>
using namespace std;
int main()
{
    int n,t,i,max=0,a[1001],ti=1,p,p1,p2,j;//ti控制输出个数，p1为余数，p2为商  
    scanf("%d%d",&n,&t);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        if(max<a[i]) max=a[i];//找最大，注意max初始化为0 
    }
    if(n==1)//题目的特殊情况 
    {
        for(i=1;i<=t;i++)
        printf("1\n");
        return 0;
    }
    while(ti<=t)
    {
        for(i=1;i<=n;i++)
        if(a[i]==max) break;//找最大 
        printf("%d\n",i);
        max=0;//注意清零 
        p1=a[i]%(n-1);
        p2=a[i]/(n-1);
        a[i]=0;//权值清零 
        if(p1==0)//可平均分配 
        {
            for(j=1;j<=n;j++)
            {
                if(j!=i)//播放的歌曲会被跳过 
                {
                    a[j]+=p2;
                    if(max<a[j]) max=a[j];
                }
            }
            ti++;
        }
        else//不可平均分配 
        {
            for(j=1;j<=n;j++)
            {
                if(j!=i)
                {
                    a[j]+=p2;
                }
            }
            for(j=1;j<=p1;j++)
            {
                if(j!=i)
                {
                    a[j]++;//以1为单位输送给每个歌曲 
                }
                else p1++;//这里是为了控制i==1，p1==1之类情况 
            }
            for(j=1;j<=n;j++)
            if(max<a[j]) max=a[j];
            ti++;
        }
    }
    return 0;
}

```

---

## 作者：邓晓蓝 (赞：7)

//此题不难啊，纯模拟。按照题目的意思一步一步来

```cpp
var n,q,i,max,maxi,a,b:longint;
    sz:array[0..50000] of longint;
begin
  readln(n,q);
  for i:=1 to n do readln(sz[i]);
  repeat
    dec(q);max:=0;
    for i:=1 to n do
      if sz[i]>max then begin max:=sz[i];maxi:=i;end;  //找目前权值最大的那首歌
    writeln(maxi);
    a:=max div (n-1);    //每首曲子平均分配的权值
    b:=max mod (n-1);   //多出来的权值
    sz[maxi]:=0;
    for i:=1 to n do
      if i<>maxi then sz[i]:=sz[i]+a;
    for i:=1 to n do  //分多出来的权值
      if i<>maxi then
        begin
          if b=0 then break;
          dec(b);
          sz[i]:=sz[i]+1;
        end;
  until q=0;
end.
```

---

## 作者：Mine_King (赞：5)

对于这题，我的评论就是：无语……  
我们老师给我们测试的时候出了这道题，然后我发现洛谷上也有，就来做了一下，当时测试时那是WA声一片，全班没有一个拿到30以上的（惨不忍睹），后来总结了一下原因，主要是——  
**题** **意** **没** **看** **懂** **！**  
所以我来讲一下这题容易弄错的地方：主要就是权值分配给除了它本身以外所有的曲子，播过的也是（因为这点，所有曲子都播完后权值不会复原）。还有要注意的是分配多余的权值是按编号来的，所以**不能排序**  
明白这几点，这题就变成了一个简单的模拟，其他的也就都是写代码时的漏洞了，具体代码如下：  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,r[1005];
int main()
{
	cin>>n>>t;
	for(int i=1;i<=n;i++) cin>>r[i];
	while(t)//也可以用for
	{
		t--;
		int a=0,b=0;//a是当前最大的权值，b是其编号
		for(int i=1;i<=n;i++)
		 if(r[i]>a) a=r[i],b=i;//寻找最大值
		cout<<b<<'\n';//输出
		for(int i=1;i<=n;i++)
		 if(i!=b) r[i]=r[i]+a/(n-1);//分配权值
		if(a%(n-1)!=0)//如果不能均分
		{
			int h=a%(n-1);//h是多余的权值
			for(int i=1;i<=n;i++)
			{
				if(!h) break;//如果分完了，就退出循环，也可以用while
				if(i!=b&&h)
			    {
			 	    r[i]++;
			 	    h--;
			    }
			}
		}
		r[b]=0;//清空权值
	}
	return 0;
}
```
由于是比赛时写的代码，所以并不是很完美，在注释中也注明了几处，这里提醒大家，如果不是很急，代码要尽量写得好一点，这样比赛时也不容易超时。

---

## 作者：PC_DOS (赞：3)

发现题解里面没有结构体的，我来发一篇用结构体做的吧。

感觉用结构体做比较清楚，但是需要做多次排序，效率并不是很高啊QwQ。

大致思路:

1. 按照权值iValue和编号iID降序排序，输出第一项编号。

2. 计算权值对剩余曲目数的整除iAdd和模iMod，并给余下的每一个曲目的权值加上iAdd。

3. 按照编号iID排序，给前iMod项的权值加一

奉上代码:
```
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std; //头文件和命名空间
struct Music{ //音乐结构体
	int iID; //编号
	int iValue; //权值
};
bool cmp(Music mscMusic1, Music mscMusic2){ //同时考虑权值和编号的排序比较函数
	if (mscMusic1.iValue != mscMusic2.iValue)
		return (mscMusic1.iValue > mscMusic2.iValue);
	else
		return (mscMusic1.iID < mscMusic2.iID);
}
bool cmpID(Music mscMusic1, Music mscMusic2){ //只考虑编号的排序比较函数
	return mscMusic1.iID < mscMusic2.iID;
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	Music mscTemp; //暂存
	vector<Music> arrMusic; //存放音乐的动态数组
	int nCount, nTimes,i, j, iAdd, iMod; //nCount-曲目总数，nTimes-播放总数，i、j-循环计数器，iAdd-权值对剩余曲目数的整除，iMod-权值对剩余曲目数的模
	cin >> nCount >> nTimes; //读入曲目总数和播放总数
	for (i = 1; i <= nCount; ++i){ //读入每个曲目的信息
		cin >> mscTemp.iValue; //读入初始权值
		mscTemp.iID = i; //记录编号
		arrMusic.push_back(mscTemp); //保存到动态数组
	}
	if (nCount == 1){ //仅有一首曲子
		for (i = 1; i <= nTimes; ++i){ //循环输出"1"
			cout << arrMusic[0].iID << endl;
		}
		goto endapp; //结束
	}
	sort(arrMusic.begin(), arrMusic.end(), cmp); //按照权值iValue和编号iID降序排序
	for (i = 1; i <= nTimes; ++i){ //模拟"播放"
		cout << arrMusic[0].iID << endl; //输出第一项编号
		iAdd = arrMusic[0].iValue / (nCount - 1);
		iMod = arrMusic[0].iValue % (nCount - 1); //计算权值对剩余曲目数的整除iAdd和模iMod
		arrMusic[0].iValue = 0; //第一首歌权值清零
		for (j = 1; j <= nCount - 1; ++j){ //给余下的每一个曲目的权值加上iAdd
			arrMusic[j].iValue += iAdd;
		}
		sort(arrMusic.begin() + 1, arrMusic.end(), cmpID); //按照编号iID排序
		for (j = 1; j <= iMod; ++j){ //给前iMod项的权值加一
			++arrMusic[j].iValue;
		}
		sort(arrMusic.begin(), arrMusic.end(), cmp); //按照权值iValue和编号iID降序排序
	}
	return 0; //结束
}
```

---

## 作者：封禁用户 (赞：3)

这题不难，纯模拟，注意控制余数清零即可

```cpp
#include<iostream>
#include<cstdio>
#define in cin>>
#define out cout<<
#define sp endl
#define sps endl<<endl
using namespace std;
int n,t,a[1005],sum;
int main(){
freopen("shen.in","r",stdin);
freopen("shen.out","w",stdout);
int i;
in n;
in t;
for(i=1;i<=n;i++){//读入
    scanf("%d",&a[i]);
}
while(t--){
    int mx=0,j=1;
    for(i=1;i<=n;i++){//读入
    if(a[i]>mx){mx=a[i];j=i;}
    }
    sum=a[j]/(n-1);//均分值
    out j<<endl;
    for(i=1;i<=n;i++){
        if(i!=j)a[i]+=sum;
    }
        if(a[j]%(n-1)!=0){//余数处理
        sum=a[j]%(n-1);
        for(i=1;i<=n&&sum;i++){
            if(i!=j){a[i]++;sum--;}
        }
    }
    a[j]=0;//清零
}
return 0;
}
```

---

## 作者：七夜 (赞：2)

这道题，唯一难点就是对余数的处理和寻找变化后的最大点

其实对余数处理，一个while循环就解决了，平均分的情况也只需要一个for循环，这么想来，也不怎么难

但是为什么我第一遍还是错了呢，先看只有十分的代码

```
#include<bits/stdc++.h>
#define ll long long
#define INF 1010
#define MAXN 99999
using namespace std;
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
int n,m,a[INF],ma,maxn,mod,z,pop,tot;
int main()
{
    n=read();
    m=read();
    for(int i=1;i<=n;++i)
     {
     	a[i]=read();
     	if(a[i]>ma)
     	 {
     	 	ma=a[i];
     	 	maxn=i;
          }
     }
    for(int e=1;e<=m;++e)
     {
     	a[maxn]=0; 
     	cout<<maxn<<'\n';
     	tot=maxn;
     	pop=ma;
     	maxn=0;
     	ma=0;
     	mod=a[tot]%(n-1);
     	z=0;
     	while(mod>0)
     	  {
     		 z++;
     		 if(z!=tot)
     		  {
     		  	a[z]++;
     		  	mod--;
               }
          }
     	for(int i=1;i<=n;++i)
     	 if(i!=maxn)
     	  {
     	  	a[i]+=pop/(n-1);
     	  	if(a[i]>ma)
     	  	 {
     	  	 	ma=a[i];
     	  	 	maxn=i;
             }
          }
     }
    return 0;
}
```
细心的人一眼就看得出错误在哪，因为错误非常明显

就是我把输出的点都变成了0了，之后再用这个点去取模，肯定取不出来啊

看了一段时间，终于发现这个错误过后，终于A掉了

AC代码如下（附带注释）：

```
#include<bits/stdc++.h>//偷懒专用库 
#define ll long long
#define INF 1010
#define MAXN 99999//三个宏定义 
using namespace std;
inline int read() {
	char c = getchar();
	int x = 0, f = 1;
	while(c < '0' || c > '9') {
		if(c == '-') f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * f;
}//快读，可以提供借鉴 
int n,m,a[INF],ma,maxn,mod,z,pop,tot;//在main函数外面定义，自动默认所有数值为0 
int main() {
	n=read();//读入个数 
	m=read();//读入输出个数 
	for(int i=1; i<=n; ++i) {//进行循环 
		a[i]=read();//读入初始值 
		if(a[i]>ma) {
			ma=a[i];
			maxn=i;
		}//寻找第一个需要输出的数 
	}
	for(int e=1; e<=m; ++e) {//输出m次 
		cout<<maxn<<'\n';
		tot=maxn;//取出序号，一边平分权值的时候遇到这个点跳过 
		pop=ma/(n-1);//取出平均值，整除自动向下取整 
		maxn=0;//重新附初始值为0 
		ma=0;//同上 
		mod=a[tot]%(n-1);//取模 
		a[tot]=0;//把输出的数的权值清零 
		z=0;//重新边0 
		while(mod>0) {//先把不能平均的数加进去 
			z++;//序号加 
			if(z!=tot) {//只要不是输出的点 
				a[z]++;//权值加一 
				mod--;//余数减一 
			}
		}
		for(int i=1; i<=n; ++i)//循环所有的点 
			if(i!=tot) {//只要不是输出的点 
				a[i]+=pop;//让点加上平均权值 
				if(a[i]>ma) { 
					ma=a[i];
					maxn=i;
				}//判断寻找下一个需要输出的点 
			}
	}
	return 0;//别忘记打哦，养成好习惯 
}
```


---

## 作者：sycqwq (赞：1)

做这道题的时候，好舒服，按着他说的模拟就行啦
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,t;
	cin>>n>>t;
	int r[1005];
	for(int i=1;i<=n;i++)	
		cin>>r[i];
	for(int i=1;i<=t;i++)
	{
		int maxn=-1,maxh;//maxh为当前权值最大的序号
		for(int j=1;j<=n;j++)//寻找最大权值的序号
		{
			if(r[j]>maxn)
			{
				maxn=r[j];
				maxh=j;
			}
		}
		cout<<maxh<<endl;//输出
		for(int j=1;j<=n;j++)//开始分配
			if(j!=maxh)//特判，如果是正在播放的就跳过
			{
				r[j]+=(r[maxh]/(n-1));//加上最大的权值的平均值，暂且不考虑不能均分
			}
		maxn=0;
		int t=r[maxh]%(n-1);//t为如果不能均分，还剩余多少
		for(int j=1;j<=n;j++)
		{
			if(j!=maxh)//特判
			{
				
				if(t==0)//注意一下，如果是一开始就等于0，直接退出，如果没有这个的话在能均分的情况下会错误
					break;
				++r[j];//权值+1，因为是以1为单位
				--t;//剩余的权值-1，因为已经分给r[j]了
				if(t==0)//如果分完了，就退出
					break;
			}
		}
		r[maxh]=0;
		
	 } 
    return 0;
}

```

---

## 作者：犇666 (赞：1)

# 纯模拟，很简单。
只是要注意加上剩下的权值时要跳过播放的歌曲


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,r[1010];
//r为权值 
int main()
{
     
    scanf("%d%d",&n,&t);
    for(int i=1;i<=n;i++){
        scanf("%d",&r[i]);
    }
    for(int i=1;i<=t;i++){
        int hh=0,xx=0;
        for(int j=1;j<=n;j++){
            if(r[j]>hh){
                hh=r[j];
                xx=j;
            }
        }
        printf("%d\n",xx);
        int ff=r[xx]%(n-1),zz=r[xx]/(n-1);
        r[xx]=0;
        for(int j=1;j<=n;j++){
            if(j!=xx){
                r[j]+=zz;
                if(ff){
                    r[j]++;ff--;
                }
            }
        }
    }
    return 0;
}
```


---

## 作者：周羿轩 (赞：1)

###### ~~看题解不多我来发一篇啊~~
# 思路：模拟一遍
这题有几个坑点：

★若n=1，会出现错误：÷0，所以要判特殊情况

★这个我就不清楚为什么了，有没有dalao可以来解释一下，在o的那一句里，如果不使用o，直接用a[big]%(n-1)后面a[big]++，会90分

★若加余数的过程中碰到权值0的，要跳过，但是跳过的这个是不计算在分配里的

★c++里整除整是向下去整的，不需要再次用函数、判断什么的，直接可以用/

★权值相同时取编号小的，所以打擂时不能用>=，只能用>

★一个数后面要换行（艾玛不行了我的节操掉了……咦，滑稽哪去了。。）

代码：
```cpp
#include<bits/stdc++.h>//万能库
uisng/*防抄袭骚操作*/ namespace std;
int n,t,big,a[1010];
int main(){
    cin>>n>>t;//输入
    for(int i=1;i<=n;i++) cin>>a[i];//再输入
    if(n==1){//特殊情况上面讲了
        while(t--) cout<<1<<endl;//只要输出1就可以了
        return 0;//直接结束程序，下面不用else
    }
    while(t--){//循环
        a[big]=0,big=0;//最大的权值归零，因为big最开始是0所以没有问题的（我从1开始用），最大数也要清零
        for(int i=1;i<=n;i++) if(a[i]>a[big]) big=i;//直接将最大的化作序号就可以了，这样不用再判断序号
        cout<<big<<endl;//输出
        for(int i=1;i<=n;i++) if(i!=big) a[i]+=a[big]/(n-1);//分配整除的（向下取整）
        for(int i=1,o=a[big]%(n-1);i<=o;i++)/*余数*/ if(i!=big) a[i]++;/*不用跳过，权值++*/else o++;/再跳一个/
    }
    return 0;//华丽丽的结束
}
```
作为一名小蒟蒻，写个题解不容易，望管理员大大手下留情，放我通过吧，谢谢哈！

---

## 作者：Blue_wonders (赞：1)

## 模拟AC，注意有坑
### 这个坑有点深
- 注意多余的权是从输入的序号1开始，所以用sort极其麻烦
- 一定注意一定注意，能坑死
```
测试输入：
3 4
11 9 10
测试输出：
1 2 3 1
```

### 算法思路
- 先找最大值，赋值
- 进入m个循环，每个循环输出当时权重最大的值
- - 先输出
- - 将权重最大的音乐分权
- - 最大权重清零
- 结束程序
### AC代码(附详解)
[AC详情](https://www.luogu.org/recordnew/show/16778690)
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,b,c;
int a[1001];
void calculate(int s,int d){
	int o=s/(n-1);//权分给所有人的 
	for(int i=1;i<=n;i++){
		a[i]+=o;
	}
	o=s%(n-1);//分给o个人余数 
	int y=1;
	while(o>0){//计数分给了几个人 
		if(y!=d){//如果这个数是最大权重，那么不能给他 
			a[y]++;//分权 
			o--;//计数+1 
		}
		y++;//依次分权 
		if(y>n)y=1;//如果比最后一个大了，就再从头找 
	}
}
int main(){
	cin>>n>>m;//输入不解释了 
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	b=0;c=0;//b存最大权重，c存权重最大的音乐序号 
	for(int i=1;i<=n;i++){//从所有音乐里找一遍 
		if(b<a[i]){
			b=a[i];
			c=i;
		}
	}
	while(m>0){//m次循环，m次查找 
		cout<<c<<endl;//输出 
		calculate(b,c);//分权函数 
		a[c]=0;//清空最大权重的音乐 
		b=0;//最大权重初始化 
		for(int i=1;i<=n;i++){//再次寻找 
			if(b<a[i]){
				b=a[i];
				c=i;
			}
		}
		m--;//计数器 
	}
	return 0;
	
} 
```


---

## 作者：HPXXZYY (赞：1)

挺水的一题，**纯模拟**

但是，要注意的地方挺多的……

难度：普及-（~~个人认为而已~~）

具体看题解

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1005],n,m,i,j,p,s;
int main(){
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)
    scanf("%d",&a[i]);
    for(p=1;p<=m;p++){
        int maxn=0;
        //注意maxn要清0
        for(i=1;i<=n;i++)
        if (a[i]>maxn){
            maxn=a[i];j=i;
        }
        s=a[j]/(n-1);
        for(i=1;i<=n;i++)
        if (i!=j) a[i]+=s;
        if (a[j]%(n-1)){
            int t=a[j]%(n-1);
            for(i=1;i<=n&&t;i++)
            if (i!=j){
                a[i]++;t--;
                //这里的i!=j不能少！！
            }
        }
        cout<<j<<endl;
        a[j]=0;//a[j]=0一定要放最后！！！
    }
    return 0;
}
```
```减少复制粘贴，共创美好洛谷```

---

## 作者：ZJMZJM (赞：1)

此题为模拟题，就模拟吧

但还是有些坑的，看楼上的大佬们都是把可平均分配和不可平均分配两种分开

判断的，其实没必要。

用一个while就行了

code
```
#include<bits/stdc++.h>//万能头文件
#define For(k,i,j) for(int k=i;k<=j;k++)//for语句的简写(习惯了)
#define N 1005//常数用宏定义
using namespace std;
inline int read()//快读，有点用处，最好背一背
{
    char ch;
    while((ch=getchar())<'0'||ch>'9');
    int res=ch-48;
    while((ch=getchar())>='0'&&ch<='9')
        res=res*10+ch-48;
    return res;
}
int a[N];//数组，表示初始权值
int main()
{
	int n=read(),T=read(),sum=n-1;//sum为平均分时的除数
	For(i,1,n)
		a[i]=read();
	For(i,1,T)
	{
		int Max=0,seq=0; //Max为最大值，seq为编号，注意：在万能头文件下，不可用max等变量，不然ce
		For(j,1,n)
			if(Max<a[j]) Max=a[j],seq=j;//找最大值
		printf("%d\n",seq);//输出
		int shang=Max/sum,yushu=Max%sum;//余数和商的计算
		For(j,1,n)
			if(j!=seq)
				a[j]+=shang;
		int k=1;//为标记
		while(yushu>0)//为重点：当除尽时就会跳过，省略了很多麻烦
		{
			if(k!=seq)
				a[k]++,yushu--;
			k++;
		}//不能用for循环，当k==seq时是不算的，所以会多往后加一个
		a[seq]=0;//清零
	}
    return 0;
} 
```

---

## 作者：_•́へ•́╬_ (赞：1)

# 真·纯模拟
```cpp
#include<bits/stdc++.h>//懒人专用头文件
#define rpt(n) for(int ttxyc=0;ttxyc<n;ttxyc++)
using namespace std;
int n,t,r[1000],i,maxi;
main()
{
	scanf("%d%d%d",&n,&t,r);
	for(i=1;i<n;i++)
	{
		scanf("%d",r+i);//输入
		if(r[maxi]<r[i])maxi=i;//顺便求最大值
	}
	rpt(t)
	{
		printf("%d\n",maxi+1);//输出一次
		for(i=0;i<n;i++)if(i!=maxi)r[i]+=r[maxi]/(n-1);//平均分配
		r[maxi]%=n-1;
		for(i=0;r[maxi];i++)if(i!=maxi)++r[i],--r[maxi];//剩下的继续分配
		maxi=0;
		for(i=1;i<n;i++)if(r[maxi]<r[i])maxi=i;//再求最大值
	}
}/**/
```

---

