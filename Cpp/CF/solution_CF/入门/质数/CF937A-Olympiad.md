# Olympiad

## 题目描述

题意：

现在有n个人，每个人都有一些分数（0<=a[i]<=600）,你要做的是统计有多少种分数（0和重复的都不算）。

## 样例 #1

### 输入

```
4
1 3 3 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
1 1 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4
42 0 0 42
```

### 输出

```
1
```

# 题解

## 作者：ZSsst (赞：5)


     #include <stdio.h>
     #include <string.h>
     #define maxn 620
     int main(){
	     int a[maxn],n,x,num=0;
	     scanf("%d",&n);
	     memset(a,0,sizeof(a)); //不是全局变量，要清零
	     for(int i=1;i<=n;i++){
		      scanf("%d",&x);
		      a[x]++;  //相应分数的元素++，避免重复
	     }
	     for(int i=1;i<=600;i++){
		      if(a[i]!=0) num++; //如果不是零就++
		      else continue;
	     }
	     printf("%d\n",num);
         return 0;  //别忘了
      }

---

## 作者：PC_DOS (赞：5)

其实本题就是问输入的数中除了0有多少种数。

通过STL的set类，借助set集合的惟一性，可以非常好地完成要求。

代码:
```
#include <iostream>
#include <set>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	register int i; //循环计数器
	set<int> setScore; //存放分数的集合
	int iTemp, nCount; //iTemp-暂存输入的数；nCount-个数
	cin >> nCount; //读入个数
	for (i = 1; i <= nCount; ++i){ //读入数字
		cin >> iTemp;
		if (iTemp != 0){ //如果不是0
			setScore.insert(iTemp); //将数字置入集合，重复的会被忽略
		}
	}
	cout << setScore.size(); //输出集合大小，也就是方案数
	return 0; //结束
}
```

---

## 作者：tocek_shiki (赞：3)

首先我们看看数据范围，0<=a[i]<=600

第一眼想到的应该是bool f[601]来统计

这种思路是能A

但是

我想讲的是：

## 当0<=a[i]<=1e9时， 该怎么做？

显然不能再bool f[1000000001]了

那么，我们就需要hash了

具体的较为简单的hash方法就是：

# **对一个大质数求余**

具体思路结合代码进行思考


```cpp
#include <bits/stdc++.h>
#define in(a) scanf ("%d", &a)
#define mem(a, b, l) for(int i = 0; i < l; i ++) a[i] = b;
#define out(a) printf ("%d", a)
using namespace std；
//以上为个人习惯，无需太关注
const int dzs = 500017;//这个大质数可以是任何一个1e4以上的，500017只是个人习惯
vector < int > _map[500017];//打一个大质数表
int n;
int ans = 0;
int main()
{
	in (n);
	for (int i = 0; i < n; i ++)
	{
		int t;
		bool f = 1;
		in (t);
		int tmp = t % dzs;
		//对t进行%大质数，找到所属的归类
		for (int j = 0; j < _map[tmp].size(); j ++)//枚举余数是tmp的每一个数，而这每一个数，都存在_map[tmp]里
			if (_map[tmp][j] == t)
			{
				f = 0;//找到重复->标记=0
				//printf ("find it!\n");
				break;
			}
		if (f && t)//注意了：没找到&&t!=0才行
			_map[tmp].push_back (t), ans ++;//更新
	}
	out (ans);
	return 0;
}
```

~~如有疑问欢迎私信骚扰啊~~

---

## 作者：thename (赞：2)

我看到大佬们的题解都那么长，感觉自己不大对；

我这道题使用的标记，就是把每个数放进一个bool数组里，这样就做到了去重；

```
for(int i=0;i<n;i++)
{
	cin>>a[i];
	flag[a[i]]=true;
}
```

然后排序，找最大值，从零到最大值遍历，用一个计数器累计；

```
	sort(a,a+n);
	for(int i=1;i<=a[n-1]+10;i++)
		if(flag[i]==true)
			ans++;
```

最后输出；

贴上我的完整代码：

```
#include<iostream>
#include<algorithm> 
using namespace std;
int a[10010],b,c,ans,n;
bool flag[10010];
int main()
{
	cin>>n;//输入 
	for(int i=0;i<n;i++)
	{
		cin>>a[i];//输入； 
		flag[a[i]]=true;//标记数字，去重 
	}
	sort(a,a+n);//排序，寻找最大值； 
	for(int i=1;i<=a[n-1]+10;i++)//从一到最大值遍历，这里a[n-1]+10是为了防止误差 
		if(flag[i]==true)//检查标记 
			ans++;//累计 
	cout<<ans<<endl;//输出总数，完美结束 
	return 0;
}
```


---

## 作者：kenlig (赞：2)

似乎这个题不需要什么高级的算法？
先扔一个Cpp代码，然后讲一讲qwq。
这个首先是读入，然后再读入分数，然后标记b数组。
标记完了之后会要统计多少种分数，那么如果b数组的某个数不为0（就是1）那么说明有这个数。设一个计数器sum，然后存在的话sum自增就好了。
```
#include<iostream>
#include<cstdio>

using namespace std;

bool b[601];
int n,a,i,sum;

int main(){
	cin>>n;
	for(i=1;i<=n;i++) {
		cin>>a;
		b[a]=1;
	}
	for(i=1;i<=601;i++){
		if(b[i]!=0) sum++;
	} 
	cout<<sum;
	return 0;
}
```


---

## 作者：rui_er (赞：1)

看到大家有了这些算法：

set、map、sort+相邻比较、桶排序

我就写个$O(N^2)$的暴力。

根据题意，我们要完成的工作是去重和去0。

刚接触OI时，大家应该学过这种去重方法：对于下标为i的数，查找j∈{0, i-1}并比较。至于去0，加个特判即可。

代码：

```cpp
#include <iostream>
using namespace std;

int main()
{
    int n;
    cin>>n;
    int a[n];
    int cnt = 0;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        if(a[i] == 0) continue;
        bool flag = true;
        for(int j=0;j<i;j++)
        {
            if(a[i] == a[j])
            {
                flag = false;
                break;
            }
        }
        if(flag) ++cnt;
    }
    cout<<cnt<<endl;
    return 0;
}
```

---

## 作者：丁丁の丁丁 (赞：1)

看了看题目本以为是快排，结果数据是1<n<100那就太简单了。下面，本蒟蒻给各位刚学OI的萌新们上传一个通俗易懂的代码
## 代码核心
~~~~
if(a[i]!=a[i+1]&&a[i]!=0) p++;//前面一个排序，判断a[i]（第一个数）和a[i+1]（后面一个数）比较，只要他们俩不相等方案数++，还有一个要点——判断a[i]是不是等于零。
~~~~
### 完整代码
~~~~
#include<bits/stdc++.h>						 
using namespace std;
int main()
{
	long long n,m,i,j,c,p=0;
	cin>>n;
	long long a[n];
	for(m=1;m<=n;m++)
	{
		cin>>a[m];
	}
	for(i=1;i<=n-1;i++)
	for(j=i+1;j<=n;j++)
	{
		if(a[i]>a[j])
		{
			c=a[i];
			a[i]=a[j];
			a[j]=c;
		}
	}//以上部分是排序，刚学OI的萌新也应该知道	
	for(i=1;i<=n;i++)
	{
		if(a[i]!=a[i+1]&&a[i]!=0) p++;	
	}								
	cout<<p;
	return 0;
}
~~~~


---

## 作者：return先生 (赞：1)

主要的思想就是先把他排好序，然后再搜索，如果找到不一样的了，那就可以多添加一种了……

代码：
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int main()
{
	int n,a[300000],x,b[10000],ans=0,js=0,mq;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		if(a[i]!=0)
		{
			if(i==1)
		{
			mq=a[1];
			js+=1;
		}
		if(a[i]==mq)
		{
			b[js]++;
		}
		else
		{
			mq=a[i];
			js++;
		}
		}
	}
	cout<<js; 
	return 0;
}
```

这题只要想法正确了，其实没有什么难的啦！

---

## 作者：Yoo_ (赞：1)

```
//第一次上题解为2018年9月27日，于2018年10月30日进行一个小修改
```
这应该是比较水的一道题了，浏览下其他题解，我这个代码可能有点长。。。
其实这道题可以分为两个部分，在代码里我会做一下解释

这里是去除重复整数的代码（代码里就不加注释了，因为满分代码里面有注释）：
```
#include<bits/stdc++.h>
using namespace std;
int a[20001],sum=0;
bool s[20001];
int main()
{
    int n;
    cin>>n;
    memset(s,true,sizeof(s));
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<=n;i++)
    {
        if(s[i])
        for(int j=i+1;j<=n;j++)
        if(a[i]==a[j])s[j]=false;
    }
    for(int i=1;i<=n;i++)
    {
        if(s[i]==true)
        {
            sum++;
        }
    }
    cout<<sum;
    return 0;
}
```
这道题需要统计个数，所以就加了一个sum，但是没有加0也要去，所以接下来需要加上去零的代码，下面上最终的满分代码：
```
#include<bits/stdc++.h> //万能头就不解释了qwq
using namespace std;
int a[20001],sum=0;//定义数组和计数器
bool s[20001];也是定义。。。
int main()
{
	std::ios::sync_with_stdio(false);//这个加不加没什么太大区别，万一T了呢
    int n;//输入个数
    cin>>n;
    memset(s,true,sizeof(s));
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];//输入需要算的数组
    }
    for(int i=1;i<=n;i++)
    {
        if(s[i])
        for(int j=i+1;j<=n;j++)
        if(a[i]==a[j])s[j]=false;//做一个简单的判断
    }//！！！！！！以上就是去除多余分数
    for(int i=1;i<=n;i++)
    {
        if(s[i]==true&&a[i]!=0)//一定要注意后面有一个a[i]!=0，我第一次做题没加，然后就WA了。
        {
            sum++;//统计分数种类数
        }
    }//！！！！！统计一下
    cout<<sum;//输出最终答案，当然，用ans也行
    return 0;
}
```

将一道题分成两部分解是个很好的思路哦，掌握好了可以将一个大问题化成几个简单些的问题~~qwq~~

---

## 作者：Register (赞：1)

# 一个弱智的桶排，不超过600，好水呀
布尔我都懒得用了

直接上代码
```cpp
#include <iostream>//输入输出流库
#include <cstring>//memset库
#define retunr return//宏定义，总是手滑把return打成retunr#滑稽
using namespace std;//免得std::
int main(){
	int s[601]/*桶*/,a,sum=0/*统计个数*/,n;
	memset(s,0,sizeof(s));//桶清零
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		s[a]++;//塞进桶里
	}
	for(int i=1;i<=600;i++)
		if(s[i]>0) sum++;//判断，不是0就++
	cout<<sum<<endl;//输出
	retunr 0;//哈哈，retunr
}
```
最近有件事我想问问洛谷，昨天我同样也在刷一道桶排的CF水题，我选标签输进去的时候总是不会弹出来，非要我刷新、取消输入很多次才能弹出来？？？

---

## 作者：Fellyhosn (赞：1)

首先，这道题是很简单的，用不着很麻烦的搜索。直接用一个标志数组就OK了

下面上代码

```
#include<iostream>
using namespace std;
int n,i,ans;
int a[101],b[601];\\b是标志数组，a输入数据。
\\由于题目中有（0<=a[i]<=600)，所以只用开一个内存为600的标志数组就行了。
int main()
{
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];//读入数据
		b[a[i]]++;//标志过程，b数组用来存每一个数出现的次数
                  //其实用bool数组来判断也是可以的
	}
	for(i=1;i<=600;i++)  //注意！从1开始
	if(b[i]) ans++;   //如果i这个数在读入时存在过（即个数不为0），ans++
	cout<<ans;       //完美输出
    }
    ```
    总结一下，这道题还是比较水的，适合新手们来做。如果第一次没有想到这个方法的可以来看一下，标志数组的技巧在以后会用到很多次的。

---

## 作者：Ace_Radom (赞：0)

是我蠢还是什么

## 为啥要用**map**？

## **一个bool型数组**就可以了！

就是读入，一个一个查，再循环一遍查找，输出，结束

**丝毫不用什么映射和排序（~~堆啊什么的~~）**

Code：

```
#include<bits/stdc++.h>
using namespace std;
bool bo[601];
//用来记录出现过的分数
//全局变量里bool默认为false
int main(){
	int n,t;
	cin >> n;
	for ( int i = 1 ; i <= n ; i++ )
	{
		cin >> t;
		bo[t] = true;  //把所有的出现过的分数设为true
	}
	int ans = 0;
	for ( int i = 1 ; i <= 601 ; i++ )
    //Warning：由于不算0，所以从一开始
	{
		if ( bo[i] )
			ans++;
        //为true，表明这个分数出现过，ans++
	}
	cout << ans;
	return 0;
}
```

---

## 作者：jinhangjie2006 (赞：0)

这题用桶做比较简单

```cpp
var
  x,a:array[0..600] of longint;
  i,j,c,d,e,b,n:Longint;
 begin
   readln(n);
     for i:=1 to n do
       begin
         read(a[i]);
         inc(x[a[i]]);//累加
end;
  for i:=1 to 600 do//0不算，所以从1开始算起
    if x[i]<>0 then inc(e);//发现一个数，累加
 writeln(e);//输出
end.
```

---

## 作者：秋本馄淡 (赞：0)

没什么好说的，思路看代码注释

```pascal
var
  n,i,x,t:longint;
  b:array[0..601] of boolean;
begin
  readln(n);  //输入n    吐槽：这都要说！！！
  for i:=1 to n do
  begin
    read(x);  //节省空间，不用数组
    b[x]:=true;  //将b[x]布尔数组设为true，默认是false
  end;
  for i:=1 to 600 do  //看题目中的数据范围，每个数不超过600
    if b[i] then inc(t);  //如果找到出现过的数字那么t+1
  writeln(t); //输出 吐槽：这都要说！！！（首尾呼应[手动滑稽]）
end.
```

---

## 作者：Jinyeke (赞：0)

## 题目:现在有n个人，每个人都有一些分数（0<=a[i]<=600）,你要做的是统计有多少种分数（0和重复的都不算）。
### ##### # 超级水的一道题呀，桶排轻松AC，不多说，放代码（pascal),拒绝Ctil+c；#
```pascal
var
 a:array[0..600] of longint;//数据范围小，所以0~600就够了
 i,j,n,x,s:longint;
begin
 readln(n);
 for i:=1 to n do 
  begin
   read(x);
   if (a[x]=0) and (x<>0) then //判断是否不等于0以及前面没有重复过这个数，累加s（注：0和同样的不能算！）
    begin 
     a[x]:=1;//标记
     s:=s+1;//符合条件累加s
   end;
  end;
writeln(s);//输出一共有多少不同的数
end.
```

---

## 作者：monkeywoora (赞：0)

Python3蒟蒻来水一发题解
```python
a=int(input())
b=input().split()
for i in range(len(b)):
    b[i]=int(b[i])
while 1>0: //其实应该有更好的方法去除0，不过我没想到= =
    if int(b.count(int(0)))==0:
        break
    else:
        b.remove(int(0)) //通过循环去除所有的0
b=list(set(b)) //可以使用Python的set功能来去重。
print(int(len(b))) //在最后，直接打印种类数（即len）即可
```
**注意：在Python3中，输入是按行读入的。。**

诸位管理员，求通过，谢谢！

---

## 作者：frankchenfu (赞：0)

看了这么多题解，没有用`map`做的。

`map`表示映射关系，可以当做哈希表用。
```cpp
#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
map<int,bool>hash;

int main(){
    int n;scanf("%d",&n);
    while(n--){
        int x;scanf("%d",&x);
        if(x)
            hash[x]=1;
    }
    printf("%d\n",hash.size());
    return 0;
}
```

---

## 作者：览遍千秋 (赞：0)

水题解。

开个桶，记录是否出现。

~~（发现本题已经有可以说是恶搞的题解了，就不这么干了）~~

---
代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define maxscore 607
int a[maxscore],n,x,ans;
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		if(x&&!a[x])
		{
			a[x]=1;
			ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：人间凡人 (赞：0)

看到题解中的许多大佬都用了排序或STL等高级算法，但其实这道题并没有那么麻烦。

我们可以发现输入的$a[i]$的范围只有$0$到$600$，那么我们为什么不计数呢？

$F[x]$表示$x$在输入中出现的次数。
这样最后我们只用扫描一下，看$F[x]$大于$0$的数有几个即可。

注意：如果输入中含$0$，是不算入答案中的(见样例$3$)。所以最后扫描的时候应该从$1$到$600$哦！

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,ans,f[605];
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
	    scanf("%d",&x);
	    f[x]++;   
            //记录x在输入中出现的次数	
	}
	for(int i=1;i<=600;i++)//  注意：从1到600 而不是0哦
	    if(f[i])ans++;
	printf("%d\n",ans);
	return 0;
}
```


---

