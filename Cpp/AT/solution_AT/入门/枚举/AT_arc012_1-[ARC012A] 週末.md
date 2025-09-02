# [ARC012A] 週末

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc012/tasks/arc012_1

高橋君は、週末が大好きです。高橋君は英語のデジタルカレンダーを使っているのですが、高橋君は英語の曜日を読むことができません。  
 カレンダーに表示されている曜日が与えられるので、あと何日で週末かを計算するプログラムを作成してください。  
 入力は以下の形式で標準入力から与えられる。

> $ day $

- $ 1 $ 行目に $ day $ が与えられる。
- $ day $ は曜日を表す文字列で `Sunday`(日曜日)、`Monday`(月曜日)、`Tuesday`(火曜日)、`Wednesday`(水曜日)、`Thursday`(木曜日)、`Friday`(金曜日)、`Saturday`(土曜日) のいずれかである。
 
 週末までの日数を出力せよ。なお、週末とは、土曜日および日曜日のことを表す。  
 もし、すでに週末であれば、 $ 0 $ と出力すること。  
 出力は標準出力におこない、末尾には改行をいれること。  
```

Monday
```

 ```

5
```

- 月曜日から土曜日までの日数は、 $ 5 $ 日です。
 
```

Saturday
```

 ```

0
```

- 土曜日は週末に含まれるので、 $ 0 $ と出力します。
 
```

Sunday
```

 ```

0
```

- 日曜日は週末に含まれるので、 $ 0 $ と出力します。
 
```

Wednesday
```

 ```

3
```

- 水曜日から土曜日までにかかる日数は、 $ 3 $ 日です。

# 题解

## 作者：LJC00111 (赞：1)

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1000];
int main()    
{
	gets(a);
	if(a[0]=='M')cout<<"5";
	if(a[0]=='T'&&a[1]=='u')cout<<4;
	if(a[0]=='W')cout<<3;//打表
	if(a[0]=='T'&&a[1]=='h')cout<<2;
	if(a[0]=='F')cout<<1;
	if(a[0]=='S')cout<<0;
    return 0;
}
```
真的特水

---

## 作者：封禁用户 (赞：0)

```pascal
var
    s:string;
    ans,a:longint;
begin
    readln(s);
    if(s='Monday')then a:=1//枚举不解释
    else if(s='Tuesday')then a:=2
    else if(s='Wednesday')then a:=3
    else if(s='Thursday')then a:=4
    else if(s='Friday')then a:=5
    else if(s='Saturday')then a:=6//注意这里！星期六，日距离周末的天数都为零（因为它们就是周末），很多人会根据样例以为周末是星期六！（好像只有我一个人犯）接着把星期天的距离天数变成七！
    else a:=6;
    ans:=6-a;
    writeln(ans);
end.

```
本题解完结啦！撒fa

---

## 作者：幻蓝 (赞：0)

```pascal
var
        k:string;
        w:array[1..7]of string=('Sunday','Monday','Tuesday','Wednesday','Thursday','Friday','Saturday');
        i:longint;
begin
        readln(k);
        for i:=1 to 7 do
            if w[i]=k then
            begin
                if (i=1)or(i=7) then writeln('0')
                else writeln(6-i+1);
            end;
end.
```
按理说很简单，根本不需要说。。。

---

## 作者：LJC00111 (赞：0)



`````cpp
#include<bits/stdc++.h>
using namespace std;
char a[1000];
int main()    
{
	gets(a);
	if(a[0]=='M')cout<<"5";
	if(a[0]=='T'&&a[1]=='u')cout<<4;
	if(a[0]=='W')cout<<3;
	if(a[0]=='T'&&a[1]=='h')cout<<2;
	if(a[0]=='F')cout<<1;
	if(a[0]=='S')cout<<0;
    return 0;
}
````cpp

```

---

## 作者：BIGenius (赞：0)

```
#include<bits/stdc++.h>
using namespace std;
string a;
int main()
{
	cin >> a;
	if(a == "Monday")//枚举周一 
	{
		cout << "5" << endl;
	}
	if(a == "Tuesday")//枚举周二 
	{
		cout << "4" << endl;
	}
	if(a == "Wednesday")//枚举周三 
	{
		cout << "3" << endl;
	}
	if(a == "Thursday")//枚举周四 
	{
		cout << "2" << endl;
	}
	if(a == "Friday")//枚举周五 
	{
		cout << "1" << endl;
	}
	if(a == "Saturday")//枚举周六 
	{
		cout << "0" << endl; 
	}
	if(a == "Sunday")//枚举周日 
	{
		cout << "0" << endl;
	}
	return 0;
}
```

---

