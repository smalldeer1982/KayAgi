# [ABC083B] Some Sums

## 题目描述

在 $1$ 以上 $N$ 以下的整数中，求所有 $10$ 进制中各位数的和在 $A$ 和 $B$ 之间的数的总和。

## 样例 #1

### 输入

```
20 2 5```

### 输出

```
84```

## 样例 #2

### 输入

```
10 1 2```

### 输出

```
13```

## 样例 #3

### 输入

```
100 4 16```

### 输出

```
4554```

# 题解

## 作者：Miller2019 (赞：7)

一道简单的模拟题，直接暴力就行了。~~竟然没有  _TLE_ ? !好吧，毕竟是一道红题~~，那我们就直接暴力吧。


------------
这是 **C++** 的代码（好像是最短的）：
```cpp
#include<cstdio>
int n,a,b,k=0,t=1,s,d;	//数据范围说在 10^4 以内，我们开 int 就行了。
int main()
{
	scanf("%d%d%d",&n,&a,&b);	//把变量 n 、 a 和 b 读进来。或"cin>>n>>a>>b;"。
	for(;t<=n;t++)  //循环条件：t<=n，每次 t 自加 1 。
	{
    	s=0,d=t;	//清零。
    	while(d)    //当 d 不等于 0 时，表达式值为真，循环继续运行；反之，表达式值为假，循环结束。
        	s+=d%10,d/=10;	//"s+=d%10"相当于"s=s+d%10";"d/=10"相当于"d=d/10"。
    	if(s>=a&&s<=b)
        	k+=t;   //同上。
	}
	printf("%d",k); 	//把变量 k 输出。或"cout<<k;"。
	return 0;	//Don't forget this.
}
```


------------

### “输出格式
符合条件的数之和（请务必要带上endl！！！）”

~~可是我没加 endl 怎么也 AC 了?应该没问题吧？~~

亲测： 11ms /  128.00KB

这道题建议删除 “字符串”标签，好像根本没字符串的事，~~是我太弱了吗？~~


（绿名蒟蒻第三篇题解。）

---

## 作者：PC_DOS (赞：1)

本题为一道模拟题，只需要根据题目要求，枚举区间内所有的数字，逐个判断是否满足所给限制即可。

代码:

```
#include <iostream>
using namespace std; //头文件和命名空间
inline bool IsAddable(int iNum, int iLBound, int iUBound){ //判断是否满足要求的函数，iNum-判断的数字；iLBound-各位和下界；iUBound-各位和的上界
    int iSum = 0; //各位和
    while (iNum){ //求各位和
        iSum += iNum % 10; //加上最后一位
        iNum /= 10; //消去最后一位
    }
    return (iLBound <= iSum && iSum <= iUBound); //判断
}
int main(){
    ios::sync_with_stdio(false); //输入输出加速
    int iEnd, iLB, iUB; //区间结尾以及各位数字之和的上下界
    cin >> iEnd >> iLB >> iUB; //读入限制条件
    register int i; //循环变量
    register long long iSum = 0; //累加器
    for (i = 1; i <= iEnd; ++i){ //枚举
        if (IsAddable(i, iLB, iUB)) //判断是否相加
            iSum += i; //若满足则累加
    }
    cout << iSum << endl; //输出和，勿忘换行
    return 0; //结束
}
```

---

## 作者：AlwaysForward (赞：0)

# 三篇题解发现P党占了两个，而且下面的巨佬~~的变量名~~好复杂

其实就是一个简单的模拟啦～ 核心部分就是以下循环：

		for(int j=1;;j++){
			s+=d%10;
			d/=10;
			if(d==0)break;
		}
其实也可以换一个方式，用While也可以，两个作用相同：

	      while(d!=0){
			s+=d%10;
			d/=10;
		}//少打一行
        
d为从1到n循环的i，为了不改变i的值从而破坏循环导致死循环，将i赋值与d。而s即为计数器。  
		
        if(s>=a&&s<=b){
			k+=i;
		}
判断s是否于a,b之间。如果是，将计数器k加上这个数。

将上面两个程序段加在一起，从1至n循环n次即可，注意计数器s和k要清零。

最后介绍一下万能头：

    #include<bits/stdc++.h>
这个几乎包含了所有的头，csp考试是可以用的（我用了没有爆零

代码双手奉上：

    #include<bits/stdc++.h>
    using namespace std;
    int main(){
    int n,a,b,k=0;
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++){
		int s=0,d=i;
		for(int j=1;;j++){
			s+=d%10;
			d/=10;
			if(d==0)break;
		}
		if(s>=a&&s<=b){
			k+=i;
		}
	} 
	cout<<k<<endl;   
    }
        

---

## 作者：Anguei (赞：0)

对一个数字 $x$ 的各位数求和，可以使用 python 的 `sum(map(int, list(str(x))))` 分解、求和。

然后这题做完了。

```python
n, a, b = map(int, raw_input().split())
ans = 0
for _ in range(n + 1):
    if a <= sum(map(int, list(str(_)))) <= b: # 分解、求和
        ans += _
print ans

```

---

## 作者：封禁用户 (赞：0)

题意：  
输入：一行 N A B                      
（条件：1≤N≤10^4，≤A≤B≤36，N、A、B均为整数）  
在1到N的范围内（包括1和N，端值可取）    
找数X1..Xn，使得这些（个）数各个数位的和在A到B之间（包括A和B，端值可取）。   
输出：一行（有回车（P党略过））        
X1+X2+..+Xn的值（即上述所找出的数的总和）   
一句话：枚举！                   
逐一判断数字，看是否满足条件。
```pascal
var
    a,b,c,i,j,z:longint;
    s:array[1..10000]of string;//仅用来判断位数
    k:array[1..10000]of longint;//记录数字（10^4=10000）
    ans:qword;//要开大点，如果是1+……+10000用int64会爆
begin
    read(a,b,c);
    for i:=1 to a do
    begin
        str(i,s[i]);//把数字转为字符串
        for j:=1 to length(s[i]) do//判断位数
        begin
            val(s[i][j],z);//一个个数字枚举
            k[i]:=k[i]+z;//把每一位数加起来
        end;
        if(k[i]>=b)and(k[i]<=c)then inc(ans,i);//判断
    end;
    writeln(ans);//输出
end.

```
完结！ヾ(◍°∇°◍)ﾉﾞ

---

