# [ABC005B] おいしいたこ焼きの食べ方

## 题目描述

高橋君打算品尝他试做的章鱼烧。

高橋君喜欢吃刚出锅的热腾腾的章鱼烧，所以他会从最新出锅的章鱼烧开始吃。

现在给出每个章鱼烧是几秒前做好的，请输出最新出锅的章鱼烧是几秒前做好的。

输入将以下述格式从标准输入给出。

> $N$ $T_1$ $T_2$ : $T_N$

- 第 $1$ 行给出一个整数 $N$，表示章鱼烧的个数，$1 \leq N \leq 100$。
- 接下来的 $N$ 行，每行给出一个整数 $T_i$，表示第 $i$ 个章鱼烧是几秒前做好的，$1 \leq T_i \leq 100$。

请输出最新出锅的章鱼烧是几秒前做好的。
另外，输出末尾请换行。

例如：

```
3
1
2
3
```

```
1
```

- 最新出锅的章鱼烧是 1 秒前做好的。

```
3
3
3
3
```

```
3
```

- 所有章鱼烧都是 3 秒前做好的。

```
5
3
1
4
1
5
```

```
1
```

## 说明/提示

无。

由 ChatGPT 4.1 翻译

# 题解

## 作者：小刘xiaol (赞：4)

各位巨佬们，这道题就是一道求最小值的题，~~根本不用不着快排~~

翻译给巨佬们贴这里了

```
高桥决定吃试制的章鱼烧。
高桥君喜欢热腾腾的章鱼烧，所以很快就会从章鱼烧开始吃。

因为每种章鱼小丸子都是几秒前做好的，所以请输出最先做好的章鱼小丸子是在几秒前做好的。

输入格式

输入是以下形式从标准输入被提供的。

$N$
$T1$
$T2$
：
$TN$

第1行表示章鱼烧的个数的整数N(1≤N≤100)N(1≤N≤100)被给予。

接着N N行中会给出表示各个章鱼烧在几秒前完成的整数Ti(1≤Ti≤100)Ti(1≤Ti≤100)Ti(1≤Ti≤100)。

输出格式

请输出最做好的章鱼烧几秒前做好的。

另外，请在输出的末尾另起一行。
```


本题解如果有抄袭现象，本人会尽快删除，谢谢~~

---

## 作者：lsyx0918 (赞：3)

这道题就是找n个数的最小值，题简直太水了！

发射题解！！：
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int main()//主函数
{
    int min=1e9;
    int n;
    int m;//用一个变量能省很多空间
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>m;
        if(m<min) min=m;//比较
    }
    cout<<min<<endl;//输出
    return 0;//拜拜了您嘞
}
```
今日头条新闻：

**多数编程员因在AtCoder中没有打换行，被洛谷网站判全错！！**

---

## 作者：不到前10不改名 (赞：2)

```
//所有人都在用stl排序，只有我一个c党还坚持手写快排...~
#include<stdio.h>
int a[100001];
void abcd(int l,int r)
{int i=l,j=r,t;
int p=a[(l+r)/2];//此段代码详解见AT2823 【ソート】我的题解~
while(i<=j)
{
    while(a[i]<p)
    {i++;}
    while(a[j]>p)
    {j--;}
    if(i<=j)
    {t=a[i]; 
    a[i]=a[j]; 
    a[j]=t;
    i++; 
    j--;}}
    if(l<j)
    abcd(l,j);
    if(i<r)
    abcd(i,r);}
    int main()
    {	
    int i,n;	
 	scanf("%d",&n);   
  	for(i=1;i<=n;i++)   
    scanf("%d",&a[i]);   
    abcd(1,n);  
    printf("%d\n",a[1]);//由于是升序，所以第一个就是最小的数~回车要记住哦！
    return 0;   
    }
    ```

---

## 作者：stry (赞：2)

这题我看了题解，几乎全部是快排，我来搞特殊了，既然全都是快排，那么我就来个数组记数，把shu数组的aa[i]位++，最后从0逐个判断，如果shu的第i位非等于零，那么输出i，退出。

### 下列是程序：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a;
int aa[110],shu[110];
int main()
{
   cin>>a;
   for(int i=0;i<a;i++)
   {
   	cin>>aa[i];
   	shu[aa[i]]++;
   }
   for(int i=0;i<=110;i++)
   {
   if(shu[i]>=1){cout<<i<<"\n"<<"创建美好洛谷，请勿抄程序";break;}	
   }
   return 0;
}
```


---

## 作者：dread (赞：1)

- 我发现这道题居然都是用循环，不然就是用排序来做
- 但我要介绍一种函数，min_element，它就可以实现直接查找函数最小值
- 它的复杂度大概是$O(n\ log\ n)$
- 但$n$是$1 \leq n \leq 100$根本不虚，直接顶上就行了。

## code:

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int a[110];

inline int read() {
	int s = 0, f = 1;
	char ch;
	for(; ch < '0' || ch > '9'; ch = getchar())	if(ch == '-')	f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar())	s = (s << 1) + (s << 3) + ch - '0';
	return s * f;
}

int main() {
	n = read();
	for(int i = 1; i <= n; ++i)	a[i] = read();
	printf("%d\n", *min_element(a + 1, a + n + 1));
	return 0;
}
```

---

## 作者：真·峭岩仙道 (赞：1)

这是真心坑题啊。。。我一不小心提交个代码还把测评基卡了。。。。

上标程：
```
#include <bits/stdc++.h>
using namespace std;
int m[105],n;
int main(){
    cin>>n;
    for(int i=0;i<n;i++) cin>>m[i];
    int ans=m[0];
    for(int i=1;i<n;i++){
        if(m[i]<ans) ans=m[i];
    }
    cout<<ans<<endl;
    return 0;
}
```

描述一下思路：先输入个数（别被坑了），所以定义一个足够大的数组，然后一个一个输进去，一个一个判断，最后输出最小就行了。

最后提醒：~~趁我们还年轻~~，加个return 0吧，首先加了没坏处，其次我不小心卡测评机那次就是没加return 0。

---

## 作者：liuyifan (赞：1)

题意:给定N个数T1,T2,...,TN,输出其最小值

做法:sort(c++ stl中的快速排序)

不懂的同学请移步:[P1177](https://www.luogu.org/problemnew/show/P1177)

code:
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,a[10000000];
int main()
{
	scanf("%d",&n)
	for(register int i=1;i<=n;i++)scanf("%d",&a[i]);//循环输入
	sort(a+1,a+n+1);//快排,默认从小到大
	printf("%d\n",a[1])//输出
}
```

---

## 作者：YZ_hang (赞：0)

### 排序入门题

这道题看了题目大家首先肯定会想到排序，因为这道题除了排序就没有其他算法了，只需要一个排序就能直接得出答案

大家都用了很多种不同的排序，我用的是最简单~~最偷懒~~的sort排序，大家应该都知道吧

上代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[101],n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);//都是读入，没什么好讲
	sort(a+1,a+n+1);//这就是传说中的sort语句，表示从a[1]排到a[n]
	printf("%d\n",a[1]);//核心语句就上面一句就完事了，输出就行
	return 0;
}
```
这里顺便给萌新蒟蒻们普及一下sort排序算法，这个算法非常简便，也很常用，在algorithm库里，相当于C++给我们的福利，有了这个我们就不用写一大串的冒泡排序什么的了，直接一个语句就排完了，时间复杂度O(n*log(n))，不稳定，但是非常方便

---

## 作者：zzhz (赞：0)

这题不难，直接上代码     
代码如下：
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int a[10001],n,minn=2147483647;//int范围内最大值
int main(){//主函数
	cin>>n;//输入
	for(int i=1;i<=n;i++)
	cin>>a[i];//输入
	for(int i=1;i<=n;i++){
		if(minn>a[i])minn=a[i];//求出最小值
	}
	cout<<minn<<endl;//输出
	return 0;
}
```
最后提醒一点：    
AT的题一定要换行！     
本蒟蒻心地善良    
但是，    
非紧急情况不要用此功能！    

---

## 作者：ACE_ZY (赞：0)

题意是输入n个数,找最小的

大多数人都是用排序,其实可以不用

pascal:
```pascal
var
  x,n,min,i:longint;
begin
  readln(n);//n个数
  min:=maxlongint;//min定义成最大数
  for i:=1 to n do//边输入边做
  begin
    readln(x);//可以不用数组,读入一个数,边读入边判断
    if x<min then min:=x;//如果x小于min,最小的数就定义成x
  end;
  writeln(min);//最后输出min就行了
end.
```

望通过,谢谢

---

## 作者：CZQ_King (赞：0)

数据范围那么小，居然没有人发桶排？？
### 蒟蒻就来水一发

------------
做法：先桶排，再找到最小的。

------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,a[123],i;
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>x;//不需要用数组
        a[x]=1;//将其设为有
    }
    while(a[i]==0){//直到找到最小的
        i++;
    }
    cout<<i<<endl;//千万不要输出a[i]
    return 0;
}
```

---

## 作者：SCLBJKD (赞：0)

- 题意其实就是输入n个数，找这n个数的最小数

- 输出：最小数，另外，带上
# 换行
## 换行
### 换行

# 重要的事情说三遍！！！

> 没换行你就凉了，直接$WA$

## 思想：

> 定义一个变量minn，初始为0x7f（无限大）

> 依次输入n个数

> 遇到k（输入的数）比minn小，更新minn=k；

> 输出minn，**换行**！！！

### 代码如下
```
#include<bits\stdc++.h>
using namespace std;
int main()
{
	int n,k,minn=0x7f;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>k;
		minn=min(minn,k);//min函数返回小的那个值
	}
	cout<<minn<<endl;
}
```

---

## 作者：u55545554 (赞：0)

一道水题，不多解释……\n
```cpp
#include<bits/stdc++.h>
using namespace std;
#define juruo cout//调皮一下 
long long ans1,ans2;
int main(){
	short n;cin>>n;//数据范围小于short(0<=n<=100) 
	short a[n+1];//蒟蒻省空间做法 
	short minn;//最小值 
	for(int i=1;i<=n;i++)cin>>a[i];//输入
	minn=a[1];//初始化
	for(int i=2;i<=n;i++){//从2开始找即可,与上面一行相照应 
		if(a[i]<minn)minn=a[i];
	} 
	juruo<<minn<<endl;//蒟蒻版完结撒花
	return 0;//滚去继续刷水题 
}
```

---

