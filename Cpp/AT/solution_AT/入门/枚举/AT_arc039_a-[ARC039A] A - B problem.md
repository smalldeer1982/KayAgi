# [ARC039A] A - B problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc039/tasks/arc039_a

高橋君は次のような問題を考えました。

- $ 3 $ 桁の整数 $ A $、$ B $ が与えられるので $ A\ -\ B $ を求める。

しかしあまりにも簡単すぎるので、ちょっと変更して次のような問題にしました。

- $ 3 $ 桁の整数 $ A $、$ B $ が与えられる。
- $ A $ と $ B $ のどちらかを $ 1 $ 桁だけ書き換えてもよい時の、$ A\ -\ B $ の答えになり得る整数の最大値を求める。

なお、一番上の桁が $ 0 $ であるような整数へと書き換えることはできません。 例えば $ 123 $ を $ 023 $ へと書き換えたりすることはできません。

高橋君は自信満々であなたへとこの問題を出題してきました。 ぜひ挑戦してみてください。

## 说明/提示

### Sample Explanation 1

$ A $ を $ 567 $ から $ 967 $ に書き換えれば $ A-B $ は $ 733 $ となり、この値が $ A-B $ の最大値となっています。

### Sample Explanation 2

どちらも書き換えない時に $ A-B $ が最大値となることもあります。

### Sample Explanation 3

答えは負になることもあります。

## 样例 #1

### 输入

```
567 234```

### 输出

```
733```

## 样例 #2

### 输入

```
999 100```

### 输出

```
899```

## 样例 #3

### 输入

```
100 999```

### 输出

```
-99```

# 题解

## 作者：准点的星辰 (赞：9)

看到楼下大佬的简单的枚举，我不禁感叹我的模拟太复杂，可是还是想发一下。


------------

主要思路：从高位开始比较，如果高位并不满足被减数百位等于9，减数等于1，个位和十位被减数为9，减数为0（在这些情况下无法更改，所以往低位寻找更改）。
更改思路：比较9-减数的这位数和被减数这位-1（或0）的大小，如果前面的大，就将被减数这位数改成9，输出，如果前面小就将减数这位改成1(或0)，输出。
代码：
```cpp
#include<iostream> 
#include<cstdio>
using namespace std;
int a,b; 
int main()
{
	scanf("%d%d",&a,&b);
	int c=a/100;
	int d=b/100;
	if (c==9&&d==1)
	{
		c=a/10%10;
		d=b/10%10;
		if (c==9&&d==0)
		{
			c=a%10;
			d=b%10;
			if (9-d>c-0)
			printf("%d\n",999-b);
			else
			printf("%d\n",a-100);
			return 0;
		}
		else
		{
			if (9-d>c-0)
			{
				printf("%d\n",(990+a%10)-b);
				return 0;
			}
			else
			printf("%d\n",a-(100+b%10));
			return 0;	
		}
	}
	else
	{
		if (9-d>c-1)
		printf("%d\n",(9*100+a/10%10*10+a%10)-b);
		else
		printf("%d\n",a-(100+b/10%10*10+b%10));
		return 0;	
	}
	return 0;
}
```
不禁感叹数据太水，第一次写把比较都写成了9-减数和减数-0竟然只wa了两个点……

---

## 作者：LJC00111 (赞：9)

一个一个的枚举即可
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans=-100000,x,y;
int main()
{
    scanf("%d%d",&n,&m);
    x=n,y=m;
    ans=max(ans,(x%100+900-y));//更改n的百位
    ans=max(ans,((x/100)*100+x%10+90)-y);//更改n的十位
    ans=max(ans,x+9-x%10-y);//更改n的个位
    ans=max(ans,x-(y%100+100));//更改m的百位
    ans=max(ans,x-((y/100)*100+y%10));//更改m的十位
    ans=max(ans,x-(y-y%10));//更改m的个位
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：ComeOver· (赞：4)

发现木有c++的就来发一篇，不喜勿喷

贴代码
```cpp
#include <iostream>
using namespace std;

int strToInt(string x){//将string转化为int
	int y=0;
	int p=0;
	for(int i=x.size()-1;i>=0;i--){
		int t=x[i]-'0';
		for(int j=0;j<p;j++){
			t*=10;
		}
		y+=t;
		p++;
	}
	return y;
}

int main() {
	string n,m;
	cin>>n>>m;
	int y=-1000;//答案，初值一定要尽量小
	for(int i=0;i<=2;i++){
		string p=n;//为了为了不修改原值，重新设定变量
		if(i==0){//百位不能有0，特判
			for(int j=1;j<=9;j++){
				p[i]=j+'0';//加‘0’可以直接把char数字转化为int的数字
				int x=strToInt(p);
				y=max(y,x-strToInt(m));
				p=n;
			}
		}
		else{
			for(int j=0;j<=9;j++){
				p[i]=j+'0';
				int x=strToInt(p);
				y=max(y,x-strToInt(m));
				p=n;
			}
		}
	}
	for(int i=0;i<=2;i++){
		string p=m;
		if(i==0){
			for(int j=1;j<=9;j++){
				p[i]=j+'0';
				int x=strToInt(p);
				y=max(y,strToInt(n)-x);//这里是有区别的
				p=m;
			}
		}
		else{
			for(int j=0;j<=9;j++){
				p[i]=j+'0';
				int x=strToInt(p);
				y=max(y,strToInt(n)-x);

				p=m;
			}
		}
	}
	cout<<y<<endl;//要换行
	return 0;
}
```

---

## 作者：sxtm12138 (赞：3)

我总结了一下，这道题的精髓是：
## 能改高位就不要改低位！！！

知道了这一点，这道题就不难做了（其实不知道也不难做）。首先，可以用a/100、(a%100)/10、a%10分别表示a的百位、十位、个位，依次比较a、b的百位、十位、个位，判断是否取到了最佳情况（差最大），如果已经是最佳情况就比较下一位；如果没有就将其中收益较大的改为最佳情况。之后，在a-b的基础上加上最大收益，即为差的最大值。

计算收益：将百位从x改为1或9，收益分别为100(x-1)和100(9-x)，最大收益为(9-1)*100=800，依此类推………

 _详见代码：_ 

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{int a,b;//定义变量
 cin>>a>>b;//输入
 if(a/100-b/100<8) //由于百位不为0，最佳情况为8
   cout<<100*max(9-a/100,b/100-1)+a-b<<endl;//加上较大差值的100倍
 else if((a%100)/10-(b%100)/10<9)//0可以取到，最佳情况为9 
        cout<<10*max(9-(a%100)/10,(b%100)/10)+a-b<<endl;
      else cout<<max(9-a%10,b%10)+a-b<<endl;//前两位都最佳就改个位
return 0;
}

```

---

## 作者：Mr_Sympathetic (赞：2)

###  代码量稍长（~~捂脸~~）但思路简单易懂


由于题目已知是两个三位数的数字，范围很小，因此可以从百位数字到个位数字顺序开始枚举。

具体见代码



#### 贴上代码
```cpp
#include<cstdio>

using namespace std;

int a,b,ans=-0x7fffffff;	//初始化设置为一个极小数

int max(int a,int b) //自定义比大小函数
{
	return a>b?a:b;		//如果a>b返回a 否则返回b
}

int main()
{
	scanf("%d%d",&a,&b);
	int bai=a/100,shi=a%100/10,ge=a%10;
	int bai_=b/100,shi_=b%100/10,ge_=b%10;
    
	for(int i=1; i<=6; ++i)	//一共有6位数字， a三位 b三位
		for(int j=0; j<=9; ++j)	//从0开始枚举
		{
			switch (i)
			{
				case 1:
				{
					if(j)	//如果j!=0则可以取百位
					{
					a=j*100+shi*10+ge;
					b=bai_*100+shi_*10+ge_;
					ans=max(ans,a-b);
					}
					break;
				}
				case 2:		//如果j!=0则可以取百位
				{
					if(j)
					{
					a=bai*100+shi*10+ge;
					b=j*100+shi_*10+ge_;
					ans=max(ans,a-b);
					}
					break;
				}
				case 3:		//十位
				{
					a=bai*100+j*10+ge;
					b=bai_*100+shi_*10+ge_;
					ans=max(ans,a-b);
					break;
				}
				case 4:		//十位
				{
					a=bai*100+shi*10+ge;
					b=bai_*100+j*10+ge_;
					ans=max(ans,a-b);
					break;
				}
				case 5:		//个位
				{
					a=bai*100+shi*10+j;
					b=bai_*100+shi_*10+ge_;
					ans=max(ans,a-b);
					break;
				}
				case 6:		//个位
				{
					a=bai*100+shi*10+ge;
					b=bai_*100+shi_*10+j;
					ans=max(ans,a-b);
					break;
				}
			}
		}
        
	printf("%d\n",ans);
	return 0;
}


//ios::sync_with_stdio(false);
//freopen("in.in","r",stdin);
//freopen("out.out","w",stdout);

```

---

