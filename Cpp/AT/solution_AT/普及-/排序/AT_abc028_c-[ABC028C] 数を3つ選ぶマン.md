# [ABC028C] 数を3つ選ぶマン

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc028/tasks/abc028_c

異なる整数が $ 5 $ 個与えられます。

この中から $ 3 $ つ選んでその和で表すことの出来る整数のうち、$ 3 $ 番目に大きいものを出力してください。

## 说明/提示

### Sample Explanation 1

$ 3 $ つ選んでその和で表すことのできる整数は $ 6,\ 7,\ 8,\ 9,\ 10,\ 11,\ 12 $ です。なので、このなかで $ 3 $ 番目に大きい $ 10 $ を出力します。

## 样例 #1

### 输入

```
1 2 3 4 5```

### 输出

```
10```

## 样例 #2

### 输入

```
1 2 3 5 8```

### 输出

```
14```

# 题解

## 作者：happybob (赞：4)

~~求过~~。


STL大法好！

本题是`set`好题，将三个数加起来存到`set`中，既可以去掉重复的，还能从小到大排序！

但是有个大问题！如何输出那个第三大的？`set`是不能用下标访问的！我们的确可以用`end`返回的迭代器三次自减然后输出，类似第一篇题解。不过我这里给大家介绍另一种迭代器类型，那就是：`reverse_iterator`。

这种迭代器是支持逆序遍历，从`rbegin`的位置，也就是最后一个数据的迭代器，到rend，也就是第一个数据 - 1的迭代器，`rbegin`和`rend`是两个函数，其返回值不能跟`iterator`混用，必须用`reverse_iterator`。

这里说一个小误区，`end`的返回值其实是最后那个数据 + 1的迭代器，而`rbegin`是最后一个数据的迭代器。

还有就是尽管是`reverse_iterator`，遍历还是用自增而非自减。

所以代码：

```cpp
#include <cstdio>
#include <set>
using namespace std;

int a[10];

set<int> sum;

int main()
{
    scanf("%d %d %d %d %d", &a[1], &a[2], &a[3], &a[4], &a[5]);
    for(register int i = 1; i <= 5; i++)
    {
        for(register int j = i + 1; j <= 5; j++)
        {
            for(register int k = j + 1; k <= 5; k++)
            {
                sum.insert(a[i] + a[j] + a[k]);
            }
        }
    }
    int i = 0;
    set<int>::reverse_iterator endd = sum.rbegin(), beginn = sum.rend();
    for(set<int>::reverse_iterator it = endd; it != beginn; ++it) // 迭代器的自增最好名字放前面，并且不要在for循环条件中放函数
    {
        i++;
        if(i == 3) {printf("%d\n", *it); return 0;}
    }
    return 0;
}
```


---

## 作者：⚡YMJcvjk⚡ (赞：4)

**本人P党，转C++了**              
让我们想一下，如果直接枚举（假设有N个数），在最后判断，那么时间复杂度为O(N^3)，超过七八百，基本爆了，如果加优化，即每次枚举（在第2次循环后开始判断），来一次判断，那么时间复杂度就大大减少了。查找第3大的，只要用sort就可以了。
 ```cpp
#include<bits/stdc++.h>//万能头文件
 using namespace std;
  int k,n,i,ans=0,min=100000000,i1,i2,i3;//初始化
  int a[6],b[10005];//b数组为存放和的
  bool p;
  int main()
  {
      for(i=0;i<5;i++)
      cin>>a[i];
      for(i1=0;i1<5;i1++)//枚举
       for(i2=0;i2<5;i2++)
       if(i1!=i2)
        for(i3=0;i3<5;i3++)
        if(i1!=i3&&i2!=i3)
            {
                ans=a[i1]+a[i2]+a[i3];
                p=true;
                for(i=1;i<=k;i++)//查找重复的，如果重复了就不加到b数组里
                if(b[i]==ans)
                {
                    p=false;
                    break;
                }
                if(p==true)
                {
                k++;
                b[k]=ans;
                }
            }
        sort(b+1,b+1+k);//sort排序
        cout<<b[k-2]<<endl;//输出，AT的题要换行!
        return 0;
  }
```
AT题大坑，输出换行

---

## 作者：Egg_eating_master (赞：2)

# STL大法好~

这道题用set不好吗？？！！

用set很快的！！！

几乎不用想事！！！

set是STL中一个自动去重与排序的容器，简直就是为这道题量身定做的！！！

题解里的大佬居然都没想到！！！

上啊！！！

```
#include<bits/stdc++.h>
using namespace std;
set<int>s;//定义一个set
int a[6];
int main(){
	for(int i=1;i<=5;i++)
	    cin>>a[i];//输入~
	for(int i=1;i<=3;i++)
	    for(int j=i+1;j<=4;j++)
	        for(int k=j+1;k<=5;k++)
	            s.insert(a[i]+a[j]+a[k]);//把所有和放到s里面，同时重复的和只保留一个
	set<int>::iterator it=s.end();//定义一个迭代器指向s的尾元素的下一个
	it--;it--;it--;//找到第三大的
	cout<<*it<<endl;//输出~
	return 0;
}
```


---

## 作者：pbdean (赞：2)

这是我的第二篇审核成功的题解（如果你们能看得到的话）

下面的好像用了很多很baoli的内容，但是作为一个~~手残党~~，得到和的值我不想这么麻烦。于是写了三重循环（在循环次数最大为10时）~~是不是很无语~~

但是最主要的还是排序算法。作为一个对“排序三慢”青睐有加的小学生，我这次用了~~我平日里最不喜欢用的~~**插序算法！！**

插序算法很简单，把一个值插进原有的序列里就行了（~~当然本来不是这么用的~~）为了去重，还得整个数组扫一遍……

**以下是失败经验，~~不做题的可跳过~~**：{我信心满满的评测，结果让我WA凉WA凉的……

可这个程序没有毛病……

回头看了看题目，日文原题中看到一个“末尾”，一个“改行”，作为中国人的我突然无师自通……输出+endl；

然后AC……

吐槽翻译！

}

以下是代码，码风不好，勿吐槽：
```cpp
#include<iostream>
using namespace std;
bool isort(int* a,int b,int);
int main(){
	int a[5]={0},b[10]={0},len=0;
	cin>>a[0]>>a[1]>>a[2]>>a[3]>>a[4];//手懒 
	for(int i=0;i<3;i++)
		for(int j=i+1;j<4;j++)
			for(int k=j+1;k<5;k++)if(isort(b,a[i]+a[j]+a[k],len))len++;
	cout<<b[2]<<endl;//注意此处
	return 0;
}
bool isort(int* a,int b,int len){
		int j=len-1;
		for(;j>=0;j--)if(a[j]==b) return false;
		j=len-1;
		while((j>=0)&&b>a[j]){
			a[j+1]=a[j];
			j--;
		}
		a[j+1]=b;
	return true;
}
```






---

## 作者：打表大蒟蒻 (赞：1)

这道题其实真的很~~水~~，直接枚举就好了，总共应该是C(5,2)=10种。但这种毫无技术含量的代码~~蒟蒻~~我怎么会敲呢，于是，我潜心研究，发现了一种更~~装~~有技术含量的方法。


------------
中心思想是三层循环找三个数（其实也是枚举啦），把他们加起来扔进一个记录和的数组。sort排序一下，找第三个最大值，这里有个坑，注意，有可能在第三个数前面的两个数是相同的，所以还要跳过，直接输出。
```cpp
#include <iostream>
#include <algorithm>  //STL大法好！！！
using namespace std; 
int main()
{
	int a[5], maxv[10], p=0;  //p记录循环中的maxv数组下标
	for(int i=0;i<5;i++)
		cin>>a[i];  //输入
		
	for(int i=0;i<3;i++)  //进行循环
		for(int j=i+1;j<4;j++)
			for(int k=j+1;k<5;k++)
				maxv[p]=a[i]+a[j]+a[k],p++;  //输进maxv数组
				
	sort(maxv,maxv+10);  //排序
	p=1;   //反复利用是个好习惯
	for(int i=8;i>=0;i--)  //避免有重复的现象
	{
		if(maxv[i]!=maxv[i+1]) p++;  //进行筛查
		if(p==3) {  //找第三个数
			cout<<maxv[i]<<endl;  //输出
			return 0;  //完美结束
		}
	}	
}
```


---

## 作者：wushuang0828 (赞：1)

暴力枚举，暴力出奇迹……

但是记得去重，还要排序……

所以上Pascal代码：
```pascal
var
 i,j,k,t,s,ss:longint;
 a,b:array[0..100] of longint;
begin
 for i:=1 to 5 do
  read(a[i]);//输入5个数，用数组保存，枚举更方便
 for i:=1 to 5 do
  for j:=1 to 5 do
   if i<>j then//优化
    for k:=1 to 5 do
     if (i<>k) and (j<>k) then begin inc(s); b[s]:=a[i]+a[j]+a[k]; end;//存到b数组当中
 for i:=1 to s-1 do
  for j:=i+1 to s do//选择排序，从大到小排
   if b[i]<b[j] then
    begin
     t:=b[i];//交换
     b[i]:=b[j];//交换
     b[j]:=t;//交换
    end;
 for i:=1 to s do
  begin
   if b[i]<>b[i+1] then inc(ss);//去重
   if ss=3 then begin writeln(b[i]); halt; end;//当是第三大的时，就输出，并退出程序
  end;
end.
```

---

## 作者：Core (赞：1)

5个数挑3个数，其实只有C(5,3)=10种可能，所以······枚举就行了。

Code：

```
#include<iostream>
#include<algorithm>
using namespace std;
int cmp(int a,int b)     //排序时返回较大值函数
{
    return a>b;
}
int x[15];      //情况数组
int main()
{
    int a,b,c,d,e;       //共有5个数
    cin>>a>>b>>c>>d>>e;      //输入
    //暴力枚举10种结果
    x[0]=a+b+c;
    x[1]=a+b+d;
    x[2]=a+b+e;
    x[3]=a+c+d;
    x[4]=a+c+e;
    x[5]=a+d+e;
    x[6]=b+c+d;
    x[7]=b+c+e;
    x[8]=b+d+e;
    x[9]=c+d+e;
    //情况枚举完毕
    for(int i=0;i<10;i++)
    {
        if(x[i]==x[i+1]) x[i]=-1;      //如果有重复赋值为-1就成了最小的，便不会影响第3大。
    }
    sort(x,x+10,cmp);     //由大到小排序
    cout<<x[2]<<endl;     //将第3大输出
    return 0;             //结束程序
}
```

---

## 作者：Cambridge (赞：0)


蒟蒻又来发题解了！

发题解这一路来，本蒟蒻也已经过了49篇题解了，（忽然感觉有大佬会说追求质量而不是数量~~但我还是用心去写好每一篇题解的~~）希望管理员大大能够满足我这个蒟蒻题解50+的心愿吧。

这道题呢我就废话不多说了，首先，我们（~~先输入~~）将所有加起来的得数都用s数组存起来，然后，快捷或者简单一点的第二步就是将s数组从大到小排序（~~我个人觉得从小到大排序没那么快捷~~）。接下来有一个坑点，就是3个数加起来的得数可能会重复，所以我们还要再进行判断。最后的最后，就是输出了。代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>//文件头不解释
using namespace std;
long long n=5,a[10000],s[10000],gs,gss;
bool cmp(long long x,long long y)//从大到小排序
{
	return x>y;
}
int main()
{
for(int i=1; i<=n; i++)cin>>a[i];
for(int i=1; i<=n; i++)
	for(int j=i+1; j<=n; j++)
		for(int k=j+1; k<=n; k++)
			s[++gs]=a[i]+a[j]+a[k];//将所有的得数存起来
sort(s+1,s+1+gs,cmp);
for(int i=2; i<=gs; i++)
{
	if(a[i]!=a[i-1]){gss++;if(i==2)gss++;}//如果不重复
	if(gss>=3){cout<<s[i]<<endl;return 0;}//如果已经是第三大的数
}
    return 0;
}

```

好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

## 作者：A_Plus_Gu (赞：0)

69分代码（自己都不相信会有69分）：

（这个代码不说，因为不是AC代码。）
```
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int main(){
	long long a[10];
	for(int i=1;i<=5;i++){
		cin>>a[i];
	}
	sort(a+1,a+5+1);
	cout<<a[1]+a[4]+a[5]<<endl;
	return 0;
}
```
**考察内容**： 枚举

**思路**： 

1.三个数一个一个的**枚举**，计算三个数的和

2.排序并去重

3.找到第三大的数并输出。

AC代码：
```
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int main(){
	long long a[10],sum[10001],key=1,ton[301],l=0,ans;
    
    for(int i=1;i<=5;i++){
		cin>>a[i];//输入
	}
    //一个一个枚举，并计算三个数的和
	for(int i=1;i<=3;i++){
		for(int j=i+1;j<=4;j++){
			for(int k=j+1;k<=5;k++){
				sum[key]=a[i]+a[j]+a[k];
				key++;
			}
		}
	}
	sort(sum+1,sum+11);//排序
    //看到这里，你可能会问：去重在哪？别急，先往下看，待会你就能找到答案
	key=1;
	for(int i=9;i;i--){
		if(sum[i]!=sum[i+1]) key++;//没错！这一段代码就起到了去重的作用
		if(key==3){找到了第三大的数，就输出
			cout<<sum[i]<<endl;//AT的题目别忘了输出回车
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：zzhhf (赞：0)

我这里有个新方法——
# 桶排 
该这么写呢？

    1：枚举出它们的大小，用桶记录。
    2：开始查询。
    3：如果x[i]不等于0，累加s。
    4：如果s=3输出i。
完整代码还是给一下吧：

    #include<bits/stdc++.h>
    using namespace std;
    int a[10],x[1000];  
    int main()
    {
	int n,i,j,s,b,sum;
	n=5;
	s=0;           //不要忘记重置。
	for(i=1;i<=n;i++)
	  cin>>a[i];       //输入。
	for(i=1;i<n-1;i++)
	  for(j=i+1;j<=n-1;j++)
	    for(int k=j+1;k<=n;k++)   //枚举
	      {
	      	s++;
	      	sum=a[i]+a[j]+a[k];
	      	x[sum]++;      //把数放入桶中。
		  }
	s=0;
	for(i=300;i>=1;i--)
	{
		if(x[i]>0){     //如果是0就不用累加了。
			s++;          //不要忘记累加。
			if(s==3){             //判断输不输出。
				cout<<i<<endl;
				break;
			}
		}
	}
	return 0;
    } 

---

