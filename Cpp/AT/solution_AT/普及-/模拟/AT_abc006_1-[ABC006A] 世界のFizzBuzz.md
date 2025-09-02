# [ABC006A] 世界のFizzBuzz

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc006/tasks/abc006_1

 数字 $ N $ が与えられます。 $ N $ に $ 3 $ が含まれる、もしくは $ 3 $ で割り切れる場合は`YES`、それ以外は `NO` と出力してください。

 入力は以下の形式で標準入力から与えられる。 > $ N $

 整数 $ N(1≦N≦9) $ が $ 1 $ 行で与えられる。  $ N $ に $ 3 $ が含まれる、もしくは $ 3 $ で割り切れる場合は`YES`、それ以外は `NO` と出力してください。

  また、出力の末尾には改行を入れること。  ```
<pre class="prettyprint linenums">
2
```

 ```
<pre class="prettyprint linenums">
NO
```

- $ 2 $ は $ 3 $ で割り切ることができません。また $ 3 $ が含まれている数字でもありません。
 
```
<pre class="prettyprint linenums">
9
```

 ```
<pre class="prettyprint linenums">
YES
```

- $ 9 $ は $ 3 $ で割り切ることができます。
 
```
<pre class="prettyprint linenums">
3
```

 ```
<pre class="prettyprint linenums">
YES
```

- $ 3 $ は $ 3 $ で割り切ることができます。

# 题解

## 作者：梦游的小雪球 (赞：3)

### ~~大家好，我是迷上刷AT题库的梦雪~~
## 题目分析：
### - 输出YES的两种情况：
1. 为3的倍数（a%3==0）
2. 数位中含有3（如13,345,334等）
### - 输出NO的情况
1. 除YES的两种情况外，均为NO。
## 注意：
1. YES和NO均为大写字母
1. 避免重复
1. 日本题，换行最重要
## 现在献上代码（仅供参考）
```
#include<iostream>	//或万能头
using namespace std;
int main(){
	int a;
	cin>>a;
	if(a%3==0){
		cout<<"YES"<<endl;	//若为3的倍数，输出YES
		return 0;	//避免重复
	}
	for(int i=0;i<a;i++){
		if(a%10==3){
			cout<<"YES"<<endl;	//若此数位为3，输出YES
			return 0;	//避免重复
		}
		a=a/10;	//下一位
	}
    cout<<"NO"<<endl;	//不符合以上情况，输出NO
	return 0;
} 
```
[欢迎关注梦雪de博客](https://www.luogu.org/blog/Getchar121/#)


---

## 作者：有限光阴 (赞：2)

## 只是那一瞬间看见了这一道题,我便将其A了
**因为...**

它太水了.

我不是话痨,所以请看代码;
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main(){//主函数
	int a,b;//定义
	cin>>a;//输入
	if(a%3==0){//先判断能否被3整除
		cout<<"YES"<<endl;//可以输出YES,不行继续.
		return 0;
	}
	while(a>0){//循环判断它的每一位是否为3,
		b=a%10;
		a/=10;
		if(b==3){
			cout<<"YES"<<endl;//是就输出YES
		    return 0;
		}
	}
	cout<<"NO"<<endl;//如果以上判断都不成立,输出NO
	return 0;
}
```
希望大家都可以将这道题AC了

谢谢大家参考

---

## 作者：封禁用户 (赞：1)

### 前言

这题随机都能骗个$\sf20$ 分吧。。

更新日志：

$\sf8.3$ 删去无意义解释。


### 思路

读入$n$ 后直接判断是否为$3$ 的倍数。

- 如果是，输出并$\sf return $

- 如果不是，分离整数的各个数位，看是不是$3$ ，最后输出$\sf YES$或$\sf NO$。


可以用一个$\sf while $循环一直除，除到除不下去为止。


### $\sf{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,z=false;
int main()
{
	cin>>n;
	y=n;
	if(n%3==0)
	{
		cout<<"YES"<<endl;
		return 0;
	}
	else
	{
		while(x>0)
		{
			x=y%10;
			y=y/10;
			if(x==3) z=true;
		}
	}
	if(z==false) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	return 0;
}
```

End.

---

## 作者：ygl666666 (赞：0)

# 欢迎！
观看[ygl666666](https://www.luogu.org/user/197603)的题解
## 题意梳理
这道题呢是要判断一个数，他的数位上有没有3和能不能被三整除。
所以我是用了字符数组的方法来做的：我们知道，只要每个数位的和可以被三整除，证明了这个数就是3的倍数。所以判断两次：①数位是否有三②能否整除。
## 分析完毕，接下来看代码
```
/**/
#include<bits/stdc++.h>
using namespace std;
char a[100001];
int main(){
	ios::sync_with_stdio(false);
	gets(a);
	int len=strlen(a),ans=0;
	for(int i=0;i<len;i++){
		ans+=a[i];
		if(a[i]==3){
			cout<<"YES"<<endl;
			return 0;
		}
	}
	if(ans%3==0){
		cout<<"YES"<<endl;
		return 0;
	}
	cout<<"NO"<<endl;
	return 0;
}

```


---

## 作者：junhengqaq (赞：0)

#### 看到没人发题解，于是我就出来溜达溜达。。。
##### 这道题思路不难。


------------

```cpp
n能不能被3整除，可以就输出“YES”。
如果不能，就分离数位,if个位==3,就输出“YES”。
再不能，就输出“NO”拜拜啦。
```
-----------------------

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n;//全局定义n
int main(){
	cin>>n;//输入n
	if(n%3==0){//判断n能不能被3整除
		cout<<"YES"<<endl;
		return 0;//记得加，不然会爆WA
	}
    for(int i=1;i<=100;i++){//最多100位数
    	if(n%10==3){//判断个位是否为3
    		cout<<"YES"<<endl;
		    return 0;
    	}
    	n/=10;//切掉个位
    }
    cout<<"NO"<<endl;//实在不行，输出NO
	return 0;
}
```
### 要注意大写，不然也会爆WA!

---

## 作者：zfn07 (赞：0)

这道题并不难,可直接模拟。
```cpp
#include<bits/stdc++.h>
using namespace std;
bool check(int x){//判断x中是否有3
	while(x){
		if(x%10==3)//如果现在的末位为3
			return 1;//直接退出
		else x/=10;//否则去掉末位
	}
	return 0;//表示没有3
}
int main(){
	int a;
	cin>>a;
	if(a%3==0||check(a)){//如果a是3的倍数或含3
		cout<<"YES"<<endl;//输出YES退出
		return 0;
	}
	cout<<"NO"<<endl;//否则输出NO
	return 0;
} 
```


---

