# [ABC002A] 正直者

## 题目描述

输入两个正整数A,B,比较它们哪个最大,输出最大的那个数。

# 题解

## 作者：da32s1da (赞：2)

最大值。嗯。。。。
```
#include<iostream>
using namespace std;
int a,b;
int main()
{
    cin>>a>>b;
    cout<<(a&((b-a)>>31)|b&(~(b-a)>>31))<<endl;
}
```
PS:最小值
```
a&((a-b)>>31)|b&(~(a-b)>>31)
```

---

## 作者：Messi李 (赞：2)

这题也是很water的

输入两个数，判断哪个大，输出哪个

用if 和 else 就可以了

```
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long a,b; //以防万一
    cin>>a>>b; //输入
    if(a>=b) //判断是不是a大于等于b
    {
        cout<<a<<endl; //如果是，输出a
    }
    else cout<<b<<endl; //如果不是，输出b
}
```

---

## 作者：CZQ_King (赞：2)

### $qwq$还以为是高精的，然而，范围是$10^9$。见题解没有$dalao$发高精，本蒟蒻就将错就错吧。
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
string a,b;//定义字符串
int main(){
    cin>>a>>b;
    if(a.length()>b.length()){
        cout<<a<<endl;
        return 0;
    }//如果a的长度大于b，输出a并结束
    if(b.length()>a.length()){
        cout<<b<<endl;
        return 0;
    }//跟上一个注释一样
    for(int i=0;i<a.length();i++){//用i<b.length()也行，因为长度都一样
        if(int(a[i])>int(b[i])){
            cout<<a<<endl;
            return 0;
        }
        if(int(b[i])>int(a[i])){
            cout<<b<<endl;
            return 0;
        }
    }//用ascii码判断
}
```

---

## 作者：两年打铁 (赞：1)

推荐使用max函数，可以自动判断最大值。
```
#include<bits/stdc++.h>
using namespace std;
int a,b;
int main()
{
	cin>>a>>b;
	cout<<max(a,b)<<endl;//非常实用可以直接求出a和b中的最大值。
}
```

最后附上求最小值的min，用法与max相同。

---

## 作者：_Qer (赞：1)

题意：输入两个非负整数，输出较大者

这题用 max(int,int) 会很简单。
max 会返回两个数中更大的那个。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a,b;//两个整数
int main() {
    cin >> a >> b;//输入进来
    cout << max(a,b) << endl;//输出其中较大的，最后回车
    return 0;
}
```

---

## 作者：xyn0901 (赞：0)

我一天刷了二十多道水题了，这题是最水的

5行代码

```pascal
var a,b:longint;
begin
read(a,b);
if a>b then writeln(a) else writeln(b);
end.
```

~~话说这题应该要被封了吧~~

---

