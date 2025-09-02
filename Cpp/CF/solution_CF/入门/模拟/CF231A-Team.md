# Team

## 题目描述

## 题目要求
三位选手要去参加编程竞赛，比赛共有N道题目，他们商定: 对于每一道题目，只有两位及以上的选手确认找到解法时才做。
试问，他们一共能做多少题?

## 样例 #1

### 输入

```
3
1 1 0
1 1 1
1 0 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
1 0 0
0 1 1
```

### 输出

```
1
```

# 题解

## 作者：谦谦君子 (赞：3)

这道题其实思路很清晰，读入每行，判断是否有两人或两人以上有思路，如果是，答案加一，不然的话，继续循环。

```cpp
#include<bits/stdc++.h>  //万能头文件
using namespace std;
int main()
{
	int n,i，ans=0,a,b,c;  //n是题目数量，i是循环变量，ans是能解决题目个数，一定要赋0！！！a,b,c表示三位选手是否有思路
    for (i=1;i<=n;++i)
    {
    	cin>>a>>b>>c;
        if (a+b+c>=2)  //用不着判断是否有两个一，直接判断加起来是否大于1就行了
        {
        	ans++;
		}
	}
	return 0;  //最好还是加上return 0,不然考试时可能会WA
}
```

---

## 作者：FC_ARSENAL (赞：2)

# CF231A Team

为什么要用STL呢？这种题似乎不太应该用这种高端东西······

我们其实只需要统计每一次输入进来的三个数字里面有几个1就可以了，完全不需要数组或STL
详见代码

```
#include<cstdio>

int n;
int one=0,ans=0;//定义两个计数器（其义自见）
int in;//临时存储器
//init over
int main()
{
	scanf("%d",&n);
	while(n--){//一共有n道题
		one=0;//千万记得初始化！
		for(int i=0;i<3;i++){//循环3次输入
			scanf("%d",&in);
			if(in==1)one++;//如果是1，那就多一个人会做
		}
		if(one>=2)ans++;//如果超过2个人会做，那么就可以解出来，从而多一分
	}
	printf("%d",ans);//输出答案
	return 0;//done
} 
```

---

## 作者：林家三少 (赞：2)

	我看了好几遍题解，发现没有大佬用枚举？？？
	那就让我来补上吧！
    其实也不用那么麻烦，我们只用枚举以下几种情况：
    
    0的位置1、2、3，分别对应：
    0 1 1
    1 0 1
    1 1 0
    
    这里有一个坑，就是别只想着'0'不然'1'会蓝瘦的
    1 1 1
    
    所以只要解法个数如上，答案++就OK了呀
    
    程序：
    
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int n,ans;  //n是共有几道题，ans是答案
int a,b,c;  //a、b、c分别是一个人的解法
int main()
{
    cin>>n;  //输入题目数
    for(int i=1;i<=n;i++)  //开始循环
    {
    	cin>>a>>b>>c;  //输入解法数
    	if(a==0&&b==1&&c==1)  //第一种情况
    		ans++;  //答案++
    	if(a==1&&b==0&&c==1)  //第二种情况
    		ans++;
    	if(a==1&&b==1&&c==0)  //第三种情况
    		ans++;
    	if(a==1&&b==1&&c==1)  //还有个特殊的
    		ans++;
    }
	cout<<ans<<"\n";  //最后输出答案
	return 0;
}
```



---

## 作者：Suuon_Kanderu (赞：1)

这个题判断1的个数即可，但蒟蒻就有蒟蒻的想法。判断0的个数！！

~~好像没有区别~~
```

#include<bits/stdc++.h>
using namespace std;
int  n,a,ans,x;
int main() 
{ 
    cin>>n;
    ans=n;//注意注意，我把ans置为n，后面就要n--;
    //如果置为0的话，就要x是否<=1；
    for(int i=1;i<=n;i++)
    {
    	x=0;//千万别忘记清零，x是记录0的个数
    	for(int j=1;j<=3;j++)//输入
    	{
    		cin>>a;
    		if(a==0)x++;//记录零的个数
		}
		if(x>=2)ans--;
    	
	}
	cout<<ans<<endl;//输出
   return 0;//习惯养成
}
```

还可以加点优化
```
	   	if(x>=2){ans++;break;}
```
这样就使三次1只判断两次。


因为这样做太俗气，我们就用点新奇（rz）的方法来做。

栈：

栈的思想：如果是一，进栈；否则出栈。最后判断栈是否为空，是的话  ans++
```
#include<bits/stdc++.h>
using namespace std;
int  n,ans=0,x;
int main() 
{ 
    stack<int>a;//定义栈
	 cin>>n;
	 for(int i=1;i<=n;i++)
	 {

	 	for(int j=1;j<=3;j++)
	 	{

	 	cin>>x;
	 	if(x==1)a.push(x);//如果为一，进栈
	 	else if(!a.empty())a.pop();
        //否则出栈（别忘判空）
	 	}
	 	if(!a.empty())ans++;	 	
		for(int i=0;i<=3;i++)if(!a.empty())a.pop();
        //这个栈没有个a.clear()就很讨厌，出栈别忘判空
	 }
	 cout<<ans<<endl;//输出
   return 0;
}
```
这个很简单，但不忘判空这点卡了我很多次，蒟蒻一定留意

（大佬绕步）

还有一份给不熟悉STL栈的人的一份函数清单

```

1、push：
s.push(x) 将数据x进栈栈。也就是放在栈顶。
2、top：
s.top()返回栈顶元素。
3、pop:
s.pop()将栈顶元素弹出。注意这是无返回值函数，不要把他和top搞混
4、empty：
s.empty()栈的判空，为空则返回true,否则返回false。
5、size：
s.size() 获取当前栈的元素个数。
```



 累死我了



---

## 作者：rill4474 (赞：1)

## 二话不多说，直接贴代码
```pascal
var
 i,j,k,n,m,s:longint;
begin
read(n);//输入n
for i:=1 to n do
begin
for j:=1 to 3 do 
begin
read(m);//输入选手是否会解
if m=1 then inc(k);//如果会解那么累加
end;
if k>=2 then inc(s);//如果有2个及以上会做那么累加题目
k:=0;//别忘了清零
end;
write(s);//输出
end.
```

---

## 作者：PC_DOS (赞：1)

这是一道模拟题，根据题目要求我们只需要每行读入三个数并计算其中数字"1"的数量，如果"1"的数量大于等于2则给计数器加一，最后输出计数器的值即可。

统计数量的函数可以使用STL的<algorithm>库提供的count()函数实现，该函数常见的使用方法为:
  
```
count(起始迭代器, 结束迭代器(超尾), 计数的值);
```

代码:

```
#include <iostream>
#include <algorithm>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int nCount, nAns = 0, arrVote[3]; //nCount-题目数量；nAns-可解答的题目数量；arrVote-三位选手的表决结果
	cin >> nCount; //读入题目数量
	while (nCount--){ //循环读入表决结果
		cin >> arrVote[0] >> arrVote[1] >> arrVote[2]; //读取表决结果
		if (count(arrVote, arrVote + 3, 1) >= 2) //计算会做的选手的数量，如果不少于2位
			++nAns; //可做题数加一
	}
	cout << nAns; //输出可做题数
	return 0; //结束
}
```

---

## 作者：咕_gu (赞：0)

# 
这是一道大大大~~水题~~
只不过是一道判断三个数中有几个一而已
## 看题面
### 题意翻译
#### 题目要求
三位选手要去参加编程竞赛，比赛共有N道题目，他们商定: 对于每一道题目，只有两位及以上的选手确认找到解法时才做。 试问，他们一共能做多少题?

#### 输入格式
第一行一个整数N，表示题目的数量。 第二行到第N+1行，每行三个整数(0或者1)，其中0表示这位选手无法解出此题，1表示这位选手想到了解法。

#### 输出格式
一行，一个整数，表示他们所能做的题目的数量。
# 上代码
```cpp
#include<iostream>
using namespace std;//使用命名空间std
#define O2 ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);//小小的优化
int main()
{
   O2;
   int n,a,b,c,sum=0;//定义
   cin>>n;//输入
   for(int i=1;i<=n;i++){
   	cin>>a>>b>>c;
   	if(a+b+c>=2) sum++;//如果大于等于两人会这道题，则题目总数加一
   }
   cout<<sum<<endl;//输出
   return 0;//完美地结束主程序
}
```

---

