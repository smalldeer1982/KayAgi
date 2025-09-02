# Splitting in Teams

## 题目描述

There were $ n $ groups of students which came to write a training contest. A group is either one person who can write the contest with anyone else, or two people who want to write the contest in the same team.

The coach decided to form teams of exactly three people for this training. Determine the maximum number of teams of three people he can form. It is possible that he can't use all groups to form teams. For groups of two, either both students should write the contest, or both should not. If two students from a group of two will write the contest, they should be in the same team.

## 说明/提示

In the first example the coach can form one team. For example, he can take students from the first, second and fourth groups.

In the second example he can't make a single team.

In the third example the coach can form three teams. For example, he can do this in the following way:

- The first group (of two people) and the seventh group (of one person),
- The second group (of two people) and the sixth group (of one person),
- The third group (of two people) and the fourth group (of one person).

## 样例 #1

### 输入

```
4
1 1 2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
2 2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
7
2 2 2 1 1 1 1
```

### 输出

```
3
```

## 样例 #4

### 输入

```
3
1 1 1
```

### 输出

```
1
```

# 题解

## 作者：Ackoter (赞：10)

这是一道十分~~水~~难的题目，我们需要将1和2累加，最后以1与2拼在一起，再把多余的3个1拼起来
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[3],b;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) {cin>>b;a[b]++;}
	if(a[1]>a[2]) cout<<a[2]+(a[1]-a[2])/3; else cout<<a[1];//如果1比2小，直接套公式的话(a[1]-a[2])/3会有负数，影响到结果
	return 0;
}
```

---

## 作者：FP·荷兰猪 (赞：2)

这题因为每组人数不是1就是2，所以可以先从头搜一遍，把1和2配对，如果还剩1，就用三个1凑。

上代码：

```cpp
#include <iostream>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int a[n+1],i;
    for (i=1;i<=n;i++)//输入数组
    {
        cin>>a[i];
    }
    int s1,s2;
    s1=0;
    s2=0;
    for (i=1;i<=n;i++)
    {
        if (a[i]==1)//计算1,2出现的次数
        {
            s1++;
        }
        else
        {
            s2++;
        }
    }
    if (s1>s2)
    {
        cout<<s2+(s1-s2)/3<<endl;//先用1,2凑，再用三个1凑
    }
    else
    {
        cout<<s1<<endl;
    }
    return 0;
}
```

---

## 作者：wpy233 (赞：1)

这题其实是一个比较基础的**贪心**。

贪心策略比较容易能想到。蒟蒻我就来给大家讲一讲：

由于只有$2$种数字$1$或$2$，那么如果要让它们的和为$3$，就只有两种方法：

①：$2+1$。

②：$1+1+1$。

我们发现，只有在第一种情况时，$2$才有作用，不然$2$就根本对答案没有任何影响。

故，贪心策略为：先尽量用一个$2$和一个$1$拼，剩下多出来的$1$，就尽量三个一拼。

实现方法：先统计$2$和$1$的个数，对于情况①答案即为$2$和$1$中出现个数小者。接下来再加上把$1$的个数减掉$2$的个数后再$/3$的结果，即为最终答案：

$Code:$

```
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n;
int ans1,ans2;//定义，全局变量自动为0
int main()
{
	int t;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>t;
		if(t==1) ans1++;//分别累加1和2的个数
		else ans2++;
	}
	cout<<min(ans2,ans1)+max(ans1-ans2,0)/3<<endl;
   //方案1+方案2输出
	return 0;
}
```

---

## 作者：文·和 (赞：1)

这道题还算简单，组成3的组合有1、2和1、1、1，而第一种只要两个数，第二种要三个，所以优先判定1、2的情况

具体思路：输入一遍，一遍输入一遍记录1、2的个数a、b，1、2的组合有min（a,b）种

减完后，每有三个1的话ans就加一

贴出代码：

```
#include <bits/stdc++.h>   //万能头
using namespace std;
int n,m,a,b,ans;
int main(){
int i;
cin>>n;   //输入个数
for(i=1;i<=n;i++){
	cin>>m;
	if(m==1) a++;
	else b++;    //记录1和2的个数
} 
ans+=min(a,b);    //答案加上1、2组合的个数
a-=min(a,b);      //a和b减去个数
b-=min(a,b);
ans+=a/3;    //每有三个1，ans就加一
cout<<ans;   //输出
return 0;
}
```

好了，本蒟蒻的题解就到此结束了，求通过qwq


---

## 作者：Jinyeke (赞：1)

#### 題目：n个数，只有1,2，把它们任意分组，和为3的组最多多少。
### 大概思路（步骤）：
### 1.用桶记录下1和2分别有多少个（其实我是懒得加判断）
### 2.判断由1+2组成的有几组
### 3.判断由1+1+1组成的有几组
#### 那么就很好算了：
#### 判断由1+2组成的有几组的代码：
```pascal
for i:=1 to x do 
 if a[2]>=i then 
  begin
   inc(s);
   a[1]:=a[1]-1;
  end;
```
#### 判断由1+1+1组成的有几组

    s:=s+a[1] div 3;
    
    
完整代码如下（pascal）：
```pascal
var//定义
 a:array[1..2] of longint;
 i,s,n,x:longint;
begin
 readln(n);
 for i:=1 to n do 
  begin
   read(x);//输入
   inc(a[x]);//桶
  end;
 x:=a[1];
 for i:=1 to x do 
 if a[2]>=i then //判断是否能组成1+2
  begin
   inc(s);//组数+1
   a[1]:=a[1]-1;//1的个数-1
  end;
 s:=s+a[1] div 3;//判断1+1+1的有几组
 write(s);//输出组数
end.
```
### 求过！管理员大大幸苦辣


---

## 作者：不到前10不改名 (赞：1)

//这题明明是一道水的数论题，却给某些闲来无事的大佬拿去搜索233
```
#include<stdio.h>
int srx[3],n,sry,i;//数组越界了QAQ，srx【2】错了好几次（然而居然4个样例全过！！，震惊.ing）
int main()
{
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {scanf("%d",&sry);
    srx[sry]++;}//记录1,2个数
    if(srx[2]>=srx[1])//很明显，二多就不能再组成了
    printf("%d",srx[1]);
    else
    {sry=0;//这个是前面拿它来输入，懒得再写一个变量了qwq，所以清一下0
    sry+=srx[2];
    sry+=(srx[1]-srx[2])/3;//一多还有3个一
    printf("%d",sry);}
    return 0;
}
```

---

## 作者：ACE_ZY (赞：1)

本人一名pascal蒟蒻第一次发布题解 **不喜勿喷! 不喜勿喷! 不喜勿喷!**

看到题目 还以为是找筷子(第一次就是因为这个凉了)

仔细读读 其实很水

****题意是将1和2累加起来 组成3 然后输出一共可以组成的数量**

**但是如果你看过第三个数据 就知道当剩下的1足以组成3了 也是要累加的****

附上代码:
```pascal
var
  s1,s2,x,i,n,sum:longint;
begin
  s1:=0;//习惯 可有可无
  s2:=0;
  readln(n);//n个数
  for i:=1 to n do//输入数字
  begin
    read(x);
    if x=1 then s1:=s1+1;//如果读入的是1 在s1里累加
    if x=2 then s2:=s2+1;//如果读入的是1 在s2里累加
  end;
  if s1>s2 then begin sum:=sum+s2;s1:=s1-s2; end//判断1的个数是否大于2的个数 如果大于 则在sum里累加s2 将s1大于s2的数减去
           else begin sum:=sum+s1;s1:=0; end;//s2多 s1清零 累加sum
  write(sum+s1 div 3);//将sum输出 别忘了剩下的1可以组成3的话也要输出
end.//结束
```
差不多就这样 也没什么可以讲的


---

## 作者：百里亦守约 (赞：0)

## 我有可能是这些题解当中时间耗时最长的。。
**思路：**
因为要分组，而且只有1、2，要分出3，就只有**2**种可能。。

**分别是：**

#####  **1+1+1=3**
#####  **1+2=3** 
所以可以先**计数**，然后找到一次就减一次就可以了。。

**上代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,sum;
int x[10005];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>s;
        x[s]++;   //计数
    }
    while(1)
    {
    	if(x[2]>0 && x[1]>0)    //因为1+2=3，所以要消耗1个1和1个2
    	{
    		x[2]--;
    		x[1]--;   //消耗
    		sum++;   //找到一组就加一
    	}
    	if(x[2]==0 || x[1]==0) break;   //如果没有了，那么就退出
    }
    cout<<sum+x[1]/3;   //剩下的就是1+1+1=3的了。
    return 0;
}
```


---

## 作者：moqizhu2005 (赞：0)

# 又是一道~~数论题~~
### 代码和讲解如下
```cpp
#include<iostream>//头文件
using namespace std;
int n,t,a,b,s;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>t;
		if(t==1) a++;//记录1的个数
		else b++;//记录2的个数
	}
	if(b>a) cout<<a;//如果2的个数比1的个数多，那么最多匹配1的个数那么多
	else cout<<b+(a-b)/3;//反之，当2的个数匹配完后，再考虑剩余的1可否凑成3，直接用(a-b)/3即可
	return 0;
}
```

---

## 作者：Dicem (赞：0)

可以直接统计1 和 2 的个数，1默认先和2配对，然后再进行3个1的配对。. . （水题）
```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int two, one;
int main()
{
	scanf("%d", &n);
	int temp;
	for (int i=1;i<=n;++i)  {
		scanf("%d", &temp);
		(temp == 1) ? ++one : ++two;
	}
	if (one == 0)	printf("%d", 0);
	else if (one == two) printf("%d", two);
	else if (one < two)	printf("%d", one);
	else if (one > two) {
		one=one-two;
		printf("%d", two+one/3);
	}
	return 0;
}
```

---

## 作者：Hola_chen (赞：0)

# 非喜勿喷~
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
int main()
{
	//本题思路：数组开一个，输入，找1和2，三种if判断 
	int a[1000];//数组 
	int n;//n 
	int sum1=0,sum2=0,sum=0;//int 
	cin>>n;//输入 n 
	for(int i=1;i<=n;i++)//for输入数组 
	{
		cin>>a[i];//for输入数组 
		if(a[i]==1)
		{
			sum1++;//找1和2，这里找1 
		}
		if(a[i]==2)
		{
			sum2++;//找1和2，这里找2 
		}
	}
	if(sum1==sum2)
	{
		cout<<sum1;//如果他们相等，if判断第一种 
		return 0;//return 
	}
	for(int i=1;i<=n;i++)
	{
	    if(sum1>sum2)//如果1大于2，if判断第二种 
	    {
	    	sum=sum1-sum2;
	    	if(sum1-sum2%3==0&&sum1-sum2>3)
	    	{
	    		sum=sum+sum1-sum2%3;//以二为主 ，找一匹配，有多余的取模 
	    		cout<<sum;
	    		return 0;//return 
			}
		}
		if(sum1<sum2)//如果2大于1，if判断第三种 
	    {
	    	sum=sum2-sum1;//以一为主 ，找二匹配
	    	sum=sum+sum2-sum1;
	    	cout<<sum;
	    	return 0;//return 
		}
    }
    return 0;
}

```

---

## 作者：fallingdust (赞：0)

	#include <iostream>
	#include <cstdio> 
	#include <algorithm> 
	#include <cstring>
	#include <cstdlib>
	#include <cmath> //头文价
	using namespace std;//创建一个流
	int a,minword,answer;//初始化
    //包含记录是1或2的a,1,2的较小数minword,和答案answer
	int one,two;//记录1和2的数量
	int main()
	{
		int n,i;
		scanf ("%d",&n);//读入数量
		for (i=0;i<n;i++)//开始模拟
		{
			scanf ("%d",&a);//读入1或2
			if (a==1) one++;//是1就one++;
			if (a==2) two++;//是2就two++;
		}
		minword=min(one,two);//找小的
		if ((one-minword)>0)//如果是1比2多
		{
			minword+=(one-minword)/3;//判断是否可以用3个1合成一个3
		}
		answer=minword;//记录答案
		cout<<answer;//输出
		return 0;//结束
	}
    
    完美


---

