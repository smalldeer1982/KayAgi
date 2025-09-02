# Hungry Student Problem

## 题目描述

Ivan's classes at the university have just finished, and now he wants to go to the local CFK cafe and eat some fried chicken.

CFK sells chicken chunks in small and large portions. A small portion contains $ 3 $ chunks; a large one — $ 7 $ chunks. Ivan wants to eat exactly $ x $ chunks. Now he wonders whether he can buy exactly this amount of chicken.

Formally, Ivan wants to know if he can choose two non-negative integers $ a $ and $ b $ in such a way that $ a $ small portions and $ b $ large ones contain exactly $ x $ chunks.

Help Ivan to answer this question for several values of $ x $ !

## 说明/提示

In the first example Ivan can buy two small portions.

In the second example Ivan cannot buy exactly $ 5 $ chunks, since one small portion is not enough, but two small portions or one large is too much.

## 样例 #1

### 输入

```
2
6
5
```

### 输出

```
YES
NO
```

# 题解

## 作者：da32s1da (赞：12)

一下子想起[P3951 小凯的疑惑](https://www.luogu.org/problemnew/show/P3951)

对于互质的$n,m$，其不能购买的**最大价值**为$x=n*m-n-m$。

其实，其**不能购买的数量**为$y=\frac{x+1}{2}$。

对于这道题，我们求出$x=3*7-3-7=11$，进而得到$y=\frac{11+1}{2}=6$。

于是枚举不能购买的$6$件物品即可。
```
#include<cstdio>
int main(){
    int n,m;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&m);
        if(m==1||m==2||m==4||m==5||m==8||m==11) puts("NO");
        else puts("YES");
    }
}
```

---

## 作者：Amor_Hucsy (赞：2)

~~首先我要吐槽一下翻译，为毛是珂朵莉？~~    
~~因为珂朵莉阔耐鸭~~    

           ↑  
请忽略以上内容，谢谢   

题目本意就是输入一个数，判断这个数能不能用3和7来组合  

直接贴代码：

这里贴个知识：

在计算机里，非0既真  
就是只有0是假的，除0以外都是真的（包括负数）

```
#include<bits/stdc++.h>//←万能头文件
using namespace std;//没这玩意不识别cin和cout
bool luogunb(int a)//用布尔型变量定义个函数，至于函数名，呃呃呃
{
	for(int j=0;j<=a;j+=3)//重复执行
	{
		if((a-j)%7==0) return true;//判断如果得0，返回真（true==真）
	}
	return false;//返回真
}
int main(){//主程序
	int n,a;//定义整型变量n和a
	bool p=false;//定义布尔型变量p，p要等于假
	cin>>n;//
	for(int i=0;i<n;i++)//重复执行
	{
		cin>>a;//输入一个a
		if(luogunb(a)) cout<<"YES"<<endl;//做上面的子程序的判断
		else cout<<"NO"<<endl;//否则就不能
	}
    return 0;//养成一个良好的习惯
} 
```
代码就这些了，祝各位能成功AC，AC了勿忘点个赞qwq  
大家掰掰~

---

## 作者：FP·荷兰猪 (赞：2)

> 题意：珂朵莉要吃x块 ~~几块~~ 鸡块，有3块一盒的小鸡块和7块一盒的大鸡块，能不能买恰好x块鸡块？

分析与解：看到数据范围，我笑了。**x<=100**。~~真不愧是CF的A题啊！~~正好我也懒得写什么dfs，数论。直接枚举小鸡块和大鸡块的盒数，看看能不能凑到x。

PS：此题要先输入n，表示一共有n个输入需要输出YES或NO
```cpp
#include <iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int i,j;
	bool f;
	for (int q=1;q<=n;q++)
	{
		int x;
		cin>>x;
		f=false;
		for (i=0;i<=100/3;i++)//i用来枚举小鸡块的盒数
		{
			for (j=0;j<=100/7;j++)//j用来枚举大鸡块的盒数
			{
				if ((i*3+j*7)==x)//如果鸡块总数恰好等于x，直接输出YES，终止枚举（防止输出多个YES）
				{
					cout<<"YES"<<endl;
					f=true;
					break;
				}
			}
			if (f==true)
			{
				break;
			}
		}
		if (f==false)//找不到合法方案则输出NO
		{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：zhangjiacheng (赞：2)

## 本人蒟蒻，只会用大法师写。。。（别人暴力轻松AC，我却只会用dfs）
```pascal
var n,i,a:longint;f:boolean;
procedure dfs(i:longint);
begin
  if i=a then
  begin
    writeln('YES');//注意：是大写！！！（坑了我一次）
    f:=false;//做标记
    exit;
  end
else if i>a then exit//如果超了，直接exit
else if f then//如果还没有答案，就继续找
begin
  dfs(i+3);dfs(i+7);
end;
end;
begin
  readln(n);
  for i:=1 to n do
  begin
    f:=true;//初始化
    readln(a);
    dfs(0);//从0开始！！
    if f then writeln('NO');//如果没有结果，就输出NO
  end;
end.
```



---

## 作者：partychicken (赞：2)

#### 先%一下dalao，其实并不需要预处理
水题。。。直接暴力枚举
```
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int x;
        bool flag=0;
        cin>>x;
        for(int i=0;i<=x/7;i++)
        {
            if((x-7*i)%3==0)
            {
                cout<<"YES"<<endl;
                flag=1;
                break;
            }
        }
        if(!flag) cout<<"NO"<<endl;
    }
}
```

---

## 作者：封禁用户 (赞：1)

说实话，这道题特别的~~水~~。

我们只需枚举珂朵莉吃了3x+7y个鸡块，可以这样判断：

```
if((a-3*j)%7==0)
```
这样就可以输出YES，退出当前循环：

```
{cout<<"YES";t=1;break;}
```

## 程序如下：


```
#include<iostream>
using namespace std;
int n,a,t;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a;t=0;//t用来表示true和false
		for(int j=0;j<=a/3;j++)//漫长的枚举
		if((a-3*j)%7==0){cout<<"YES";t=1;break;}//t记得变为真
		if(!t)cout<<"NO";//若t=false，输出NO
		cout<<"\n";//记得要换行
	}
	
	return 0;//完美结束
}
```

---

## 作者：陈独秀先生_ (赞：1)

```cpp
\*这道题模拟太难，只得打表*\
#include<bits/stdc++.h>//万能头
using namespace std;
const int s=3;//小型
const int g=7;//大型
int x[1000],a;//题目要求用x;
main(){
    cin>>a;
    for(int i=0;i<a;i++){
        cin>>x[i];
    }
    for(int i=0;i<a;i++){
        if(x[i]<3||x[i]==4||x[i]==5||x[i]==8||x[i]==11)cout<<"NO"<<endl;//这个地方要想到，当x[i]==1,2,4,5,8,11时，柯朵莉吃不到几块~~2333~~
        else{
            cout<<"YES"<<endl;
        }
    }
    return 0;//~~Ok~~
}
```

---

