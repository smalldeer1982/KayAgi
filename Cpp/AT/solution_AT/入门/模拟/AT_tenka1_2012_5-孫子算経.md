# 孫子算経

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2012-qualB/tasks/tenka1_2012_5

 いま、物が有る。  
 その数は $ 1 $ 以上 $ 127 $ 以下である。   
 $ 3 $ で割ると、 $ a $ 余る。 $ 5 $ で割ると、 $ b $ 余る。 $ 7 $ で割ると、 $ c $ 余る。  
 いくつ物があるとそうなるか小さい順に答えよ。

 入力は以下の形式で標準入力から与えられる。 > $ a $ $ b $ $ c $

- 入力として $ 3 $ つの整数 $ a $ ( $ 0\ \leq\ a\ \leq\ 2 $ ), $ b $ ( $ 0\ \leq\ b\ \leq\ 4 $ ), $ c $ ( $ 0\ \leq\ c\ \leq\ 6 $ ) が空白で区切られて $ 1 $ 行で与えられる。
 
 条件を満たす物の数を小さい順に改行区切りで出力せよ。  
 なお、行の終端には改行が必要である。 ```

2 3 2
```

 ```

23
```

 ```

1 1 1
```

 ```

1
106
```

 ```

2 4 6
```

 ```

104
```

# 题解

## 作者：loi_hjh (赞：2)

本题有点水啊

```cpp
#include<cstdio>
using namespace std;
int a,b,c;
int main(){
	scanf("%d%d%d",&a,&b,&c);
	for(int i=1;i<=127;i++)//完全不用像大佬一样3个for 
		if((i%3==a)&&(i%5==b)&&(i%7==c)) printf("%d\n",i);
	return ~~(0-0);//卖个萌求通过 
}
```

---

## 作者：PC_DOS (赞：2)

由于答案不大于127，因此只需要枚举1到127之间的每一个数字并判断是否满足题意即可。

代码:
```
#include <iostream>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int iMod1, iMod2, iMod3; //三个模数
	register int i; //循环计数器
	while (cin >> iMod1 >> iMod2 >> iMod3){ //读入三个数
		for (i = 1; i <= 127; ++i){ //枚举1到127之间的每一个数字
			if (i%3 == iMod1 && i%5 == iMod2 && i%7 == iMod3){ //判断是否满足
				cout << i << endl; //满足则输出，勿忘换行
			}
		}
	}
	return 0; //结束
}
```

---

## 作者：B_Qu1e7 (赞：1)

提供一种新的~~sb~~方法（思路还是差不多的）
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c;
int main()
{
	//在127的范围内
    cin>>a>>b>>c;
    for(int i=a;i<=127;i+=3)//从a起每3个查找答案
    {
    	for(int j=b;j<=127;j+=5)//从b起每5个查找答案
    	{
    		if(i!=j)continue;
    		for(int k=c;k<=127;k+=7)//从c起每7个查找答案
    		{
    			if(i!=k||j!=k)continue;
                if(i!=0)cout<<i<<endl;
                //这些的意思就是说当ijk相等时就可以输出了
                //记得换行
                //最重要的一点，不能为0，就是这里被坑了
			}
		}
	}
}
```

---

## 作者：TLEWA (赞：0)

这道题在大数据范围下应使用中国剩余定理（如果想联系中国剩余定理，建议去写模板题），可是一看数据范围，果断暴力。

枚举 $1 \sim 128$ 的所有数，然后暴力判断是否符合要求即可。 

代码如下：

```cpp
#include<iostream>
using namespace std;
int main() {
	int a,b,c;
	cin >> a >> b >> c;
	for(int i=1;i^128;++i)
		if(i%3==a&&i%5==b&&i%7==c)
			cout<<i<<endl;
}
```

然后看到题解区里大佬的题解，发现有人挑战最短代码？那我也凑个热闹（

```c
main(a,b,c,i){scanf("%d%d%d",&a,&b,&c);for(i=1;i<128;i++)if(i%3==a&i%5==b&i%7==c)printf("%d\n",i);}
```

99B，吉利的。

---

## 作者：whiteqwq (赞：0)

提供一种新的思路：数学求解
孙子算经曰：三人同行七十稀，五树梅花廿一支，七子团圆正半月，除百零五使得知。

这也是后来的中国剩余定理。

但是测试点很坑，是0的情况不能输出0，所以要加个特判。

其他的都很简单，蒟蒻代码在下：

    #include<bits/stdc++.h>
    using namespace std;
    int a,b,c,d;
    int main()
    {   scanf("%d%d%d",&a,&b,&c);
        d=(a*70+b*21+c*15)%105;
        if(d==0){
            puts("105");
            return 0;
        }
        printf("%d\n",d);
        if(d<23)
            printf("%d\n",d+105);
        return 0;
    }

---

## 作者：封禁用户 (赞：0)

废话不说，直接上模拟！   
~~说实话这是枚举+~~
```pascal
var
    a:longint;
    b,c,d:longint;
begin
    readln(b,c,d);
    for a:=1 to 127 do//数据范围为127，就循环到127
    begin
        if(a mod 3=b)and(a mod 5=c)and(a mod 7=d)then//判断
        writeln(a); //输出
    end;
end.

```
撒花结束~~解束~~！！！ヾ(◍°∇°◍)ﾉﾞ

---

## 作者：Aehnuwx (赞：0)

两行代码题解，或是最短题解？

按照题目模拟即可。时间复杂度$O(n)$。

$code$

```
#include<iostream>
main(){int a, b, c;std::cin>>a>>b>>c;for(int i=1;i<=127;i++)if(i%3==a&&i%5==b&&i%7==c)std::cout<<i<<std::endl;}
```

---

## 作者：陈洋琛 (赞：0)

一道水题，直接枚举就可以了，
献上代码：
	#include <iostream>
	using namespace std;
	int main()
	{
  		int a,b,c;
  		cin>>a>>b>>c; //输入
  		for(int i=1;i<=127;i++) //从1枚举到127
  			if(i%3==a&&i%5==b&&i%7==c) //满足条件时
            	cout<<i<<endl; //输出i，然后换行
  		return 0;
	}
                                                     

---

