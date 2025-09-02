# [ABC031B] 運動管理

## 题目描述

高桥君是ATcoder的吉祥物，为了维持他的魅力，他要每天做运动（题目叫运动管理），他每天做L分钟以上H分钟以下的运动

然而，你（青木君）最近没有看到高桥君运动，在意高桥君运动状况的你询问了高桥君的运动时间，判断是不是需要加长时间

若运动时间超过了H，输出-1，不用再运动；若运动时间在L~h之间，输出0，不用再运动；若运动时间低于L，输出还需要运动多长时间才能到下限L。

## 样例 #1

### 输入

```
300 400
3
240
350
480```

### 输出

```
60
0
-1```

## 样例 #2

### 输入

```
50 80
5
10000
50
81
80
0```

### 输出

```
-1
0
-1
0
50```

# 题解

## 作者：绝艺 (赞：2)

这道题可以一边读入一边做

不一定需要什么数组

对于每次询问直接模拟即可

思路也很简单

# AC Code

```cpp
#include <iostream>
using namespace std;
int l,h,n;//变量名与题中一致
int main(){
	int x;
	cin>>l>>h>>n;
	while(n--){//一边读一边做
		cin>>x;
		if(x>h) cout<<-1<<endl;
		if(x<=h&&x>=l) cout<<0<<endl;
		if(x<l) cout<<l-x<<endl;//简单模拟，要换行
	}
	return 0;//好习惯
}
```


---

## 作者：ACE_ZY (赞：1)

来一篇pascal的题解

题意讲的是

高桥君在运动,她有每天运动的量,输入n天的运动量,求当天是否达标.

**输入格式**

首先输入的目标 两个整数x,y

然后输入n,代表有n天

接下来的n行,表示每天的运动量

**输出格式**

输出n行

输出运动的情况:超过运动时间 输出-1;没超过 输出还差多少时间;在x和y里面的运动时间 输出0

附上代码
```pascal
var
  x,y,s,i,n:longint;
begin
  readln(x,y);//跑的量
  readln(n);//n天
  for i:=1 to n do//一天一天做
  begin
    readln(s);//做一天 输入当天的跑步量
    if s>y then writeln(-1);//如果跑步量大于最大跑步量了 输出-1
    if s<x then writeln(x-s);//如果小于最小跑步量 输出还差的
    if (s>=x) and (s<=y) then writeln(0);//在两个跑步量之间 输出0
  end;
end.
```

望通过 谢谢

---

## 作者：ygl666666 (赞：0)

# 我很弱
# 这题也能使黄题！
就几个判断即可
# 题意&思路
第一个数就是高桥君每天最少的运动量，
第二个是每天最多的运动量。
有三种情况
## ①运动量不足
则需输出还需要的量，即最少量减这个量
## ②运动量在范围之内
则cout<<0;
## ③超时
则cout<<-1;
# 题意分析完，接下来就很容易了。看代码
```
/**/
#include<bits/stdc++.h>
using namespace std;
int L,H,N,a[100001];
int main(){
	ios::sync_with_stdio(false);
	cin>>L>>H>>N;
	for(int i=0;i<N;i++){
		cin>>a[i];
		if(a[i]<L){
			cout<<L-a[i]<<endl;
		}
		if(a[i]>=L&&a[i]<=H){
			cout<<0<<endl;

		}
		if(a[i]>H){
			cout<<-1<<endl;
		}
	}
	return 0;
}
```


---

## 作者：CoderAHC (赞：0)

# 这好像是水题
## 代码送上，比较一遍即可
### 自己理解一下

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int l,h,n;
	cin>>l>>h>>n;
	int e[n];
	for (int i=0;i<n;i++)
		cin>>e[i];
	for (int i=0;i<n;i++)
	{
		if (e[i]>h) cout<<-1<<endl;
		else if (e[i]<=h && e[i]>=l) cout<<0<<endl;
		else cout<<l-e[i]<<endl;
	}
	return 0;
}
```

---

## 作者：liuyifan (赞：0)

题目已被翻译,就不写题意了

解法:对于每个A按题意模拟输出即可

C++ 	code:
```cpp
#include<bits/stdc++.h>//万能头文件,NOIP慎用
#define reg register
using namespace std;//此题中可以不加,但不建议
int x,y,n,a;//四个变量够了
int main()
{
	scanf("%d%d%d",&x,&y,&n);//scanf输入数字是会自动以空格和回车分隔
	for(reg int i=1;i<=n;i++)
	{
		scanf("%d",&a);
		if(a>y)printf("-1\n");
		else if(a<x)printf("%d\n",x-a);
		else printf("0\n"//按题意输出
	}
	retur
}
```

---

