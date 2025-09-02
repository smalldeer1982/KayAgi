# 三十六進法

## 题目描述

[problemUrl]: https://atcoder.jp/contests/past202012-open/tasks/past202012_c

$ 16 $ 進法では、一般的に `0123456789ABCDEF` の $ 16 $ 個の数字を使って $ 1 $ つの桁を表しますが、 `0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ` の $ 36 $ 個の数字を使う $ 36 $ 進法を考えます。  
 $ 36 $ 進法では、$ 0 $ の次は $ 1 $ 、 $ 9 $ の次は $ \rm\ A $ 、$ \rm\ Z $ の次は $ 10 $ になります。 整数 $ N $ が $ 10 $ 進表記で与えられるので、 $ 36 $ 進表記に変換してください。

## 说明/提示

### 注意

この問題に対する言及は、2020/12/27 18:00 JST まで禁止されています。言及がなされた場合、賠償が請求される可能性があります。 試験後に総合得点や認定級を公表するのは構いませんが、どの問題が解けたかなどの情報は発信しないようにお願いします。

### 制約

- $ N $ は整数
- $ 0\ \le\ N\ \lt\ 36^3 $

### Sample Explanation 1

$ \rm\ 123=3\times36^1+15(F)\times36^0 $ です。

### Sample Explanation 2

$ \rm\ 2304=1\times36^2+28(S)\times36^1 $ です。

## 样例 #1

### 输入

```
123```

### 输出

```
3F```

## 样例 #2

### 输入

```
2304```

### 输出

```
1S0```

## 样例 #3

### 输入

```
0```

### 输出

```
0```

# 题解

## 作者：G__G (赞：0)

# [醒目的传送门](https://www.luogu.com.cn/problem/AT_past202012_c)

## 题目描述

给定一个十进制数 $n$，将 $n$ 转换成 $36$ 进制数。

## 求解过程

这里，我们要反复除以 $36$，直到商为 $0$，再将所有的余数倒序存储。

因为这里涉及到字母，所以我们要用字符串来存放结果。

## 正解代码

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	string s="";
	long long n;
	cin>>n;
	if(n==0){
		cout<<0<<endl;
		return 0;
	}
	while(n>0){
		char c;
		int x=n%36;
		if(x<=9){
			c=(char)((int)('0')+x);
		}
		else{
			c=(char)((int)('A')+x-10);
		}
		s=c+s;
		n/=36;
	}
	cout<<s<<endl;
	return 0;
} 
```


---

## 作者：NOI_AK_dreeeam (赞：0)

这题先特判 $n$ 是不是 $0$，然后进行进制转换。如果 $n \bmod 36<10$，就直接把 $n \bmod 36+48$ （直接加上 ASCII 值）存入字符串 $s$；否则就加上 $55$ 再存入 $s$。最后**倒序输出** $s_i$。

**_AC code_**

```cpp
#include<bits/stdc++.h>//养成好习惯
using namespace std;
int n,m,x;
string s;
int main(){
    cin>>n;
    if(n==0) cout<<0<<"\n";//特判
    else{
    	while(n!=0){
	    	m=n%36;
	    	if(m<10) s+=m+48;//懒得强制类型转换
	    	else s+=m+55;
	    	n/=36;
	    }
	    for(int i=s.size()-1;i>=0;i--) cout<<s[i]<<"\n";//倒序输出
    }
    return 0;//完美结束
}
```


---

