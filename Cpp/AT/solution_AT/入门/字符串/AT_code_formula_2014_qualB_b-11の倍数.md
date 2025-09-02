# 11の倍数

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-formula-2014-qualb/tasks/code_formula_2014_qualB_b

$ 11 $ で割り切れる数には、奇数桁の数の和と、偶数桁の数の和を比べると、差が $ 11 $ の倍数になっている、という性質があります。この際、一の位を $ 1 $ 桁目、十の位を $ 2 $ 桁目、というように、小さい数字から数えていくことに注意してください。

例えば、 $ 7392 $ という数字について、偶数桁に存在する数字は、 $ 2 $ 桁目の $ 9 $ と、 $ 4 $ 桁目の $ 7 $ であり、その和は $ 16 $です。 奇数桁に存在する数字は、 $ 1 $ 桁目の $ 2 $ と、 $ 3 $ 桁目の $ 3 $ であり、この和は $ 5 $ です。 $ 16 $ と $ 5 $ の差は $ 11 $ であり、上記の性質を満たします。

あなたは、 与えられた整数が、 $ 11 $ の倍数であるかどうか調べたいです。そのため、偶数桁の数の和と、奇数桁の数の和を求めようと思っています。この $ 2 $ つの値を出力するプログラムを書いてください。

## 说明/提示

### Sample Explanation 1

問題文で説明した例です。

### Sample Explanation 2

$ 11 $ の倍数でない入力も与えられます。

### Sample Explanation 3

大きな数が与えられることがあることにも注意してください。

## 样例 #1

### 输入

```
7392```

### 输出

```
16 5```

## 样例 #2

### 输入

```
12345```

### 输出

```
6 9```

## 样例 #3

### 输入

```
917237645269816381478124891628461341894621418946786785634501961```

### 输出

```
142 163```

# 题解

## 作者：xujian (赞：2)

简单的题解

其实楼下几位dalao还是有点复杂的，这题只需要把奇数位、偶数位全部加起来就可以了。

### 此处如果是偶数位情况下，那么s1记的是奇数，s2记的是奇数。如果是奇数位情况下，那么s1和s2恰好相反。第一个输出是偶数位的情况，第二个输出是奇数位的情况。当奇数位情况输出时，要把输出的s1和s2反过来。

## 一定要记住行尾要换行！！！

以下是代码↓

```cpp
#include<cstdio>
#include<cstring>
char c[1010];
int s1,s2;
int main(){
	gets(c);
	for(int i=strlen(c)-1;i>=0;i--){
		if(i%2)s1+=(c[i]-48);
		else s2+=(c[i]-48);
	}
	if(strlen(c)%2)printf("%d %d\n",s1,s2);
	else printf("%d %d\n",s2,s1);
	return 0;
}
```

---

## 作者：Anguei (赞：2)

由于这道题数据范围特别大，所以需要使用字符串存储。

但是使用自带高精的 Python 也未尝不可。

```python2
n = raw_input()
ou = 0
ji = 0
for i in range(0, len(n), 2) :
	ji += int(n[i])
for i in range(1, len(n), 2):
	ou += int(n[i])
if len(n) % 2:
	print ou, ji
else:
	print ji, ou

```

---

## 作者：Tomone (赞：0)

稍微有点麻烦，不过很好理解
```
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

int n[10001];
int sum1,sum2;

int main(){
	string a; //用字符串输入
	cin>>a;
	for(int i=0;i<a.length();++i)
	    n[i]=a[i]-'0';  //每一位数存到数组里
	for(int i=0;i<a.length();i+=2)
	    sum1+=n[i];      //不确定位数奇偶，先存进去
	for(int i=1;i<a.length();i+=2)
	    sum2+=n[i];
	if((a.length()-1)%2==0) //位数为偶数输出
	   cout<<sum2<<" "<<sum1<<endl;
	if((a.length()-1)%2==1) //位数为奇数输出
	   cout<<sum1<<" "<<sum2<<endl;
}
```
蒟蒻博客 aptx.xin

---

## 作者：_newbie_ (赞：0)

```c
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
    string a;
    cin>>a;	
    int even=0,odd=0;
    int k=0;
    for(int i=a.size()-1;i>=0;i--)
    {
        k++;  //标记，i不可标记位数，用k表示 
        if(k%2==0)
        even+=a[i]-'0';
        else
        odd+=a[i]-'0';
    }
    cout<<even<<" "<<odd<<endl;
    return 0;
}
```

---

## 作者：Kiel (赞：0)

此题注意：

1.(个位是第一位) 

2.1≤N≤10^1000-1(不可以int或long long，只有char类型)

这道题只要读懂题就很简单，没什么好说的。

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1001];
int main(){
    cin>>a;//这儿可以输入（a+1）,但是第7行i要=strlen(a);i>0;i--。
    int ans=0,ans1=0;//ans是偶数，ans1是奇数。
    for(int i=strlen(a)-1,j=1;i>=0;i--,j++){//j用来记住位数。
        if(j%2==0){//判断
            ans+=(a[i]-'0');//加上位数
            //cout<<ans<<endl;调试
        }
        else{
            ans1+=(a[i]-'0');//加上位数
            //cout<<ans1<<endl;调试
        }
    }
    cout<<ans<<" "<<ans1<<endl;//输出要加空格
    return 0;
}
```

------------


---

