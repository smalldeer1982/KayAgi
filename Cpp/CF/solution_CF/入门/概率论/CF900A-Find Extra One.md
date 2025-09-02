# Find Extra One

## 题目描述

# 题目简述
平面直角坐标系上有n个点，它们都不在y轴上。现在请你检查是否可以去掉一个点，使所有点都位于y轴的同一边。

## 说明/提示

第一个样例中，删除第二个点。

第二个样例中，无法达到目标。

第三个样例中，随便删除一个点都可以。

## 样例 #1

### 输入

```
3
1 1
-1 -1
2 -1
```

### 输出

```
Yes```

## 样例 #2

### 输入

```
4
1 1
2 2
-1 1
-2 2
```

### 输出

```
No```

## 样例 #3

### 输入

```
3
1 2
2 1
4 60
```

### 输出

```
Yes```

# 题解

## 作者：归山_ (赞：5)

这道题是道**好题~~大水题~~**


但是我依旧不要脸的来发题解了~~~

话不多说了蛮简单的直接上代码

```
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;

int main(){
	int n,a,b,ans=0,sum=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a>>b;
		a<0?ans++:sum++;
	}
	if(ans==1||sum==1||ans==0||sum==0)cout<<"Yes";
	else cout<<"No";
	return 0;
}
```
开心。。。

祝大家ak noip~noi


---

## 作者：FP·荷兰猪 (赞：3)

水题，统计下x>0 和 x<0的数字个数就好了。

源代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,left,right,x,y;
    left=right=0;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x>>y;//统计x>0和x<0的个数
        if(x>0)
            right++;
        else
            left++;
    }
    if(right<=1 || left<=1)//判断，输出
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;
    return 0;
}
```

---

## 作者：piggymichael (赞：2)

就统计一下y轴两边分别有几个。

如果两边都不止一个，去掉一个点肯定不能使所有点位于y轴同一边。

如果有一边只有一个或零个就可以。

上代码：

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int x,y,l=0,r=0,n;
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>x>>y;
		if(x>0)
			r++;//统计y轴右边的
		else
			l++;//统计y轴左边的
		if(r>1&&l>1)//如果已经不满足了，就直接输出，结束程序。
		{
			cout<<"NO"<<endl;//注意NO要大写。
			return 0;
		}
	}
	cout<<"YES"<<endl;//循环的最后一次也满足，就不用再判了，肯定行，注意YES要大写。
	return 0;//程序结束。
}
```
按照题目的意思，统计一下，判断以后就快了地AC了！

---

## 作者：wpy233 (赞：1)

嗯呐，水题+${{{{{{{2^2}^2}^2}^2}^2}^2}^2}$。

题目中要求删掉一个点后可以保证所有的点**都在y轴的同一边**，也就是意味着**所有点的y坐标必须都<0或者都>0**。

而题目~~对我们非常友好~~，保证了不会出现$y=0$的情况，所以只需要开两个变量统计一下y轴两边点的个数，如果两边点的个数有一边$ \leq 1$则成立，反之则不行。
```
#include <bits/stdc++.h>//万能头文件万岁！
using namespace std;
int a=0,b=0;//标记变量
int main()
{
	int n;
	cin>>n;//输入
	int x,y;
	for(int i=1;i<=n;i++)//循环读入x,y
	{
		cin>>x>>y;
		if(x>0) a++;//统计
		else b++;
	}
	if(a>=2&&b>=2) cout<<"No"<<endl;//判断+输出
	else cout<<"Yes"<<endl;
	return 0;
}
```

---

## 作者：文·和 (赞：0)

##### 楼上的巨佬们代码其实还能优化点（吧?）

这道题的思路大体和楼上的巨佬们一样，只是最后的判定方式变了。

在输入时就存好y轴左右的点数，最后如果点数少的那一边点数小于等于1，那么输出Yes，否则输出No.

根据思路贴出代码：

```
#include <bits/stdc++.h>               //万能头很方便
using namespace std;
long long a,b,z,y,i,n;                 //a和b输入，z和y表示左右边的点数
int main(){
cin>>n;
for(i=1;i<=n;i++){
cin>>a>>b;
if(a<0) z++;                           //输入时将左右边的点数存好
else y++;
}
if(min(z,y)<=1) cout<<"Yes";           //如果点数小的一侧可以删完则输出Yes
else cout<<"No";                       //否则输出No
return 0;
}
```

本蒟蒻的题解就到此结束了，求通过qwq

---

## 作者：Eason6 (赞：0)



------------
祖国的花朵，最蒟的是我，大家好，我就是大蒟蒻

------------
这题很水，只需要判断数据给的点能否在一边就行，话不多说，上代码（注释在代码里）：
```
#include<bits/stdc++.h>//万能头文件 
using namespace std;//命名空间 
long long int a[1000005];//用来存坐标的X值 
long long int b[1000005];//用来存y值 
long long int ansa;//在y轴左侧的数量 
long long int ansb;//右侧的数量 
long long int n;//全用long long保险 
int main(){//主函数 
	cin>>n;//输入不多说 
	for(int i=1;i<=n;i++){
		for(int j=1;j<2;j++){/*其实这个for不需要
		只是用来摆看的*/ 
			cin>>a[j];//输入x值 
			cin>>b[j];//输入y值 
			if(a[j]<0 || a[j]==0){
				ansa++;//如是，数量+1 
			}//判断是否在y轴左侧 
			else{
				ansb++;//如是，数量+1 
			}//判断是否在y轴右侧 
		}
	}
	if(ansa>1 && ansb>1){
		cout<<"NO";//如均超过，输出NO 
	}//如果两边数量都超过了1 
	else{
		cout<<"YES";//如果不是，输出YES
	} 
	return 0;//结束程序 
}//perfect 
```
这题没啥好说的，只要清楚只要判断x的值，就能AC呐

---

## 作者：BCZSX (赞：0)

~~这就是一道水题~~

这题就是判断一下y轴两边的点数是否都大于1，如果是，则肯定要删除至少1个点才能使剩余的点全部在y轴同一侧，所以输出No，否则输出Yes！！！
```cpp
#include <cstdio>
#include <iostream>

using namespace std;

int n,x,y,l,r;

int main()
{
    scanf("%d", &n);
    for (int i = 1 ; i <= n ; ++ i)
    {
        scanf("%d%d", &x, &y);
        if (x < 0) ++ l;
        else ++ r;
    }
    if (l > 1 && r > 1) printf("No");
    else printf("Yes");
    return 0;
}
```

---

## 作者：shenmadongdong (赞：0)

~~既然没有Pascal的题解，那本蒟蒻来水一发~~

统计一下x>0与x<0的个数，其中有一个不大于一即可做到

代码：
```
var x,y,n,i,l,r:longint;
begin
  read(n);
  for i:=1 to n do 
    begin
      read(x,y);
      if x>0 then inc(l) else inc(r);//统计
    end;
  if (l<2)or(r<2) then writeln('Yes') else writeln('No');//判断
end.
```

---

## 作者：Erusel (赞：0)

#### 直接统计y轴两边点的个数
#### 如果在一边点的个数<=1,那么就把这个点删去，
```
cout<<"Yes"<<endl;
```
否则
```
cout<<"No"<<endl;
```
代码：
```
#include<bits/stdc++.h>

using namespace std;

int n;
int x,y;
int a1=0,a2=0;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x>>y;
        if(x>0)a1++;
        else a2++;
    }
    if(a1<=1||a2<=1)cout<<"Yes"<<endl;
    else cout<<"No"<<endl;

    return 0;
}
```

---

