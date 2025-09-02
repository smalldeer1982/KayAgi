# 暗算ゲーム

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2014-final/tasks/code_festival_final_b

高橋君は、一桁の暗算が大好きです。数字の列を使って、暗算の練習をしています。

高橋君は、奇数番目の数字が表す数を足し、偶数番目の数字が表す数を引く、という計算を繰り返します。

例えば、`13458`という数字の列が与えられたら、$ 1-3+4-5+8 $を計算します。

高橋君のために、この計算の結果を出力するプログラムを作成してください。

## 说明/提示

### Sample Explanation 1

$ 1-3+4-5+8 $ を計算すると、$ 5 $ になります。

### Sample Explanation 2

出力が負の数になることがあることに注意してください。

## 样例 #1

### 输入

```
13458```

### 输出

```
5```

## 样例 #2

### 输入

```
2525```

### 输出

```
-6```

# 题解

## 作者：封禁用户 (赞：1)

题意：输入一个数，按下列方式计算：

第一个数字-第二个数字+第三个数字-第四个数字...以此类推

例如：13458

答案为1-3+4-5+8=5

2525

为2-5+2-5=-6

s≤1000

（别问我样例是咋弄到10000+的(:з」∠)）

好了题意告诉你了，自己去做吧，我不管你了（滑稽）

Stop！言（wo）归（yao）正（ji）传（xu）

这题得用字符串，基本很简单，不解释：

```pascal
var
    i,ans,j,k:int64;//应该（对应该）要开大点（毕竟我是乱蒙题意，非机翻）不知范围，就开的很大。注：范围是机翻
    a,s:string;
begin
    readln(s);
    k:=1; 
    while i<length(s) do//可怜的64位变量用不了for
    begin
        inc(i);
        a:=s[i];//取第i位数字
        j:=0;//这可以不用，可本萌新有强迫症
        val(a,j);//把第i位字符串变成数字j
        inc(k);//判断当前是要加还是要减
        if(k mod 2=1)then ans:=ans-j
        else ans:=ans+j;
    end;
    writeln(ans);//输出
end.

```
这题其实很水，很快就可以了
我博客（有游戏）：https://yizhixiaoyu.blog.luogu.org/

---

## 作者：CZQ_King (赞：1)

## 这道题很$water$，只需要判断i%2是否等于$0$
## 是的话就加，否则就减。
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
string a;
int ans;
int main(){
    cin>>a;
    for(int i=0;i<a.length();i++){
        if(i%2==0)ans+=int(a[i])-int('0');
        else ans-=int(a[i])-int('0');//判断，一定要减回一个‘0’。因为是字符串。
    }
    cout<<ans<<endl;//输出答案
    return 0;//完美结束
}
```

---

## 作者：温情 (赞：0)

#### 入门的题...当然由入门的蒟蒻写题解了.

思路很简单,直接将输入当作一个字符串读入.然后一个个的计算就好了.

记住一点就行,如果当前读入的是奇数位,比如第1位，那么就加上它,如果读入的是偶数位就减去.

```
#include<iostream>
using namespace std;
int main()
{
	string str;
	long long sum=0;
	cin>>str;
	int len1=str.length();
	for(int i=0;i<len1;i++)
		sum=((i&1)==0?sum+(str[i]-'0'):sum-(str[i]-'0'));  //简单的位运算,可以判断当前是奇数位还是偶数位 
	cout<<sum;
	return 0;
} 
```


...其实位运算也不是那么必要,如果不懂位运算的话,判断奇数偶数位这样即可:

```
	if((i+1)%2)
		sum+=(str[i]-'0');
	else
		sum-=(str[i]-'0');
```


i+1当然是因为循环从0开始但是一个数在奇数位还是偶数位当然是从1开始了.

---

