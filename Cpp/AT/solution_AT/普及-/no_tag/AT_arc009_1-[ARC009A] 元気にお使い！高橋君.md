# [ARC009A] 元気にお使い！高橋君

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc009/tasks/arc009_1

ある日高橋君はお母さんに近くのスーパーまでおつかいを頼まれました。  
 お母さんに手渡されたおつかいメモには、買ってきて欲しい商品の値段と個数がそれぞれ書かれています。  
 ただしメモに書かれている値段には消費税が含まれていませんが、全ての商品には消費税が $ 5\% $ かかります。  
 高橋君のおつかいに必要な金額を答えなさい。  
 なお、消費税は $ 1 $ 円未満は切り捨てます。 入力は以下の形式で標準入力から与えられる。

> $ N $ $ a_0 $ $ b_0 $ $ a_1 $ $ b_1 $ : : $ a_{N-1} $ $ b_{N-1} $

- 入力は $ N+1 $ 行ある。
- $ 1 $ 行目には、購入する商品の品数を表す整数 $ N(1≦N≦10) $ が与えられる。
- $ 2 $ 行目から $ N $ 行の $ i+2 $ 行目にはある商品の購入したい個数を表す整数 $ a_i(1≦a_i≦10) $ とその単価を表す整数 $ b_i(1≦b_i≦1,000) $ が空白区切りで与えられる。
 
 高橋君のおつかいに必要な金額を標準出力に $ 1 $ 行で出力せよ。  
 なお、最後には改行を出力せよ。 ```

2
4 120
2 130
```

 ```

777
```

- $ 120×4+130×2=740 $ 円に消費税を加えると $ 740×1.05=777 $ 円になります。
 
```

1
1 100
```

 ```

105
```

- $ 100×1×1.05=105 $ 円になります。
 
```

4
3 510
1 835
2 140
6 205
```

 ```

4068
```

- 合計金額 $ 3875 $ 円に消費税を加えると $ 4068.75 $ 円になります。
- $ 1 $ 円未満は切り捨てるので $ 4068 $ 円が答えになります。
 
```

10
8 10
7 189
4 545
1 596
3 209
10 850
9 943
6 921
8 984
10 702
```

 ```

44321
```

# 题解

## 作者：Yoo_ (赞：4)

在提交这篇题解之前，看了看楼下，貌似都是直接开int哦

**其实开double最好吧**，可以练练精度这一块

那么我的代码就来了

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,a[1001],b[1001];//定义啊
	double sum=0;//清一下
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i],&b[i]);//这里无论先输入哪个都可以做出来
		sum+=a[i]*b[i];//价钱=数量*价格
	}
	sum*=1.05;//由乘法分配率可知，如果每一项都要乘上1.05，那么可以把1.05提出来一起乘(1.05=1+5%)
	cout<<(int)sum<<endl;//输出一定要强转，而不是要用 fixed  setprecision什么的，那样会被WA的
    //AT 一定要换行
	return 0;//再见
}
```

---

## 作者：不到前10不改名 (赞：2)

继续来做at，还是我这个弱驹
```
#include<stdio.h>
int main()
{
    int n,s,srx,i,sry;//防伪码
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {scanf("%d%d",&srx,&sry);
    s+=srx*sry;}//累加和
    s*=1.05;//可以强制转换类型，不用double然后强行取整什么的
    printf("%d\n",s);//回车
    return 0;
}
```

---

## 作者：stry (赞：1)

~~这题应该被评为红题啊~~

其实这题只需要让he加上每一次输入的总价(a[i]*b[i])就OK了

记住这题一定要换行！！！

代码来咯：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1010],b[1010];
long long n,he;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i]>>b[i];
        he=he+a[i]*b[i];//一件物品买的个数以及他的单价
    }
    he*=1.05;//别想逃税
    cout<<he<<endl;//一定得换行，不然爆零两行泪
    return 0;
}

```


---

## 作者：wushuang0828 (赞：1)

## **思路：算出总价（总价=数量*单价），加上消费税后，再取整数部分**

### Pascal取整数的函数：trunc

具体代码如下：
```pascal
var
 s1,s2:string;
 s:real;
 a,b,i,n:longint;
begin
 readln(n);
 for i:=1 to n do
  begin
   readln(a,b);//输入数量和价格
   s:=s+a*b;//算出总价
  end;
 s:=s*1.05;//加上消费税后的需要的付的钱
 writeln(trunc(s));//取整数
end.//结束程序
```

---

## 作者：勘探员·引魂人 (赞：0)

**前言：“从今若许闲乘月，~~智障~~ 拄杖无时夜叩门。”这句诗简直是形容了此题：“如果今天可以给个数据样例，连智障在某个夜里也可以AC这道题”**

**思路：用check函数来计算x*y，然后每输入2个数总和就+=x * y，最后输出总和 * 1.05**

```
#include<iostream>
#include<fstream>
#include<algorithm>//美好的程序从文件头开始
using namespace std;
int check(int x,int y)//check函数登场
{
	return x*y;//计算x*y
}
long long n,s,t,h;//定义long long 类型变量
int main()
{
    scanf("%lld",&n);//输入n
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&s,&t);//输入s,t
		h+=check(s,t);//总和+=s*t
	}
	h*=1.05;//总和*=1.05
	cout<<h<<endl;//输出总和（记得换行！）
	
    return 0;//结束喽！！！
}
```

---

## 作者：A_Plus_Gu (赞：0)

此题~~很难~~并不难（但我提交了n遍还没过qaq）

思路：根据题意膜你

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
//inline ll read(){char ch=getchar();ll s=0,w=1;while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}while(ch>='0'&&ch<='9'){s=s*10+ch^48;ch=getchar();}return s*w;}//上面是写挂了的快读，请自行忽略qaq
inline void write(ll x){if(x<0){putchar('-');x=-x;}if(x>=10)write(x/10);putchar(x%10+'0');}
//上面是没有写挂但也没用的快写，也请自行忽略
ll n,ans;
int main(){
	//n=read();
	cin>>n;//输入
	for(int i=1;i<=n;i++){
		ll x,y;
		scanf("%lld %lld",&x,&y);
		ans+=x*y;//计算不包含消费税的总价格
	}
	ans*=1.05;//加上消费税
	write(ans);//输出答案
	puts("");//输出换行！
	return 0;
}
```
注意：AT的题要输出换行！（WA了四五次才意识到qaq）


---

## 作者：Rbu_nas (赞：0)

感谢管理抽出时间审核题解qwq

题目描述：读入n件物品数量及价格，求出税后值

思路：典型的取整问题，只对整钱付款

代码实现：
```cpp
#include <bits/stdc++.h>
using namespace std;

int n,a,b,p; //n物种数量 a物品数量,b单价 p金额

int main()
{
    scanf("%d",&n); 
    for(int i=1; i<=n; i++)
    {
        scanf("%d %d",&a,&b);
        p+=a*b; //累加每一单的price
    }
    printf("%d\n",int(p*1.05)); //这里由题意直接取整，不计零头
    return 0;
}
```

这道题思路还是比较易懂的就不用copy了吧。

---

