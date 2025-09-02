# [ABC084B] Postal Code

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc084/tasks/abc084_b

Atcoder国では、郵便番号は $ A+B+1 $ 文字からなり、$ A+1 $ 文字目はハイフン `-`、それ以外の全ての文字は $ 0 $ 以上 $ 9 $ 以下の数字です。

文字列 $ S $ が与えられるので、Atcoder国の郵便番号の形式を満たすかどうか判定してください。

## 说明/提示

### 制約

- $ 1≦A,B≦5 $
- $ |S|=A+B+1 $
- $ S $ は $ 0 $ 以上 $ 9 $ 以下の数字、およびハイフン `-` からなる

### Sample Explanation 1

$ S $ の $ A+1 $ 文字目がハイフンで、それ以外の全ての文字が $ 0 $ 以上 $ 9 $ 以下の数字なので、Atcoder国の郵便番号の形式を満たしています。

### Sample Explanation 2

$ S $ の $ A+1 $ 文字目以外もハイフンとなっており、Atcoder国の郵便番号の形式を満たしていません。

## 样例 #1

### 输入

```
3 4
269-6650```

### 输出

```
Yes```

## 样例 #2

### 输入

```
1 1
---```

### 输出

```
No```

## 样例 #3

### 输入

```
1 2
7444```

### 输出

```
No```

# 题解

## 作者：qwq2003 (赞：2)

很简单的~~水~~题，按题目模拟即可。

AC代码：
```cpp
#include <bits/stdc++.h>   
using namespace std;
int main()
{
    int a,b;    
    string s;      
    cin>>a>>b;
    cin>>s;                     //输入数据
    if(s[a]!='-')                 //如果第A+1个字符不为字符'-'
    //PS：因为我是从0开始输入的，所以要去掉+1
    {
        cout<<"No"<<endl;         //那么就不对
        return 0;
    }
    for(int i=0;i<a+b;i++)
    {
        if(i==a)                  //如果检索到S的第A+1个字符（需要排除）
        {
            continue;             //跳过本次循环
        }
        if(s[i]<'0' || s[i]>'9')  //如果不是个数字
        {
            cout<<"No"<<endl;     //那么就不对
            return 0;
        }
    }
    cout<<"Yes"<<endl;            //都到这里了肯定对
    return 0;                     //完美结束
}
```

#  **拒绝抄袭，创造和谐洛谷**



---

## 作者：RioBlu (赞：2)

本题比较简单

输入$a$,$b$

输入一个字符串

判断从左往右$a$个字符是否不是$1,2,3,4,5,6,7,8,9,0$ 如果不是输出$No$

判断第$a+1$个字符是否不是 $-$ 如果不是输出$NO$

判断从右往左$b$个字符是否不是$1,2,3,4,5,6,7,8,9,0$ 如果不是输出$No$

如果都是输出 Yes

# 来来来，上代码！
```
#include<bits/stdc++.h>
using namespace std;
char n;
int a,b;
int main()
{
    cin>>a>>b;//输入
    for(int s=0;s<a;s++)
    {
    	cin>>n;
    	if(n<'0'||n>'9')//判断前a个
    	{
    		cout<<"No"<<endl;
    		return 0;
		}
	}
	cin>>n;
	if(n!='-')//判断第a+1
	{
    	cout<<"No"<<endl;
    	return 0;
		
	}
	for(int s=0;s<b;s++)
	{
		cin>>n;
    	if(n<'0'||n>'9')//判断判断从右往左的b个
    	{
    		cout<<"No"<<endl;
    		return 0;
		}
	}
	cout<<"Yes"<<endl; //排除完了，只能输出Yes
    return 0;
}
```

---

## 作者：qzhwyce (赞：1)

### 算是一道比较简单的模拟题
大致思路是先判断字符串c的a1个字符是否为‘-’，不是就直接输出No,是的话继续判断‘-’两边的字符串中还有没有‘-’，有的话输出No,否则输出Yes。
~~思路清奇~~

------------

## AC代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
char a[6],b[6],c[12];
int main(){
	int i = 0,j = 0,a1,b1,k = 0,m = 0,n = 0;
	cin>>a1>>b1;
	cin>>c;//输入
	if(c[a1] != '-'){//判断字符串c的a1个字符是否为‘-’
		cout<<"No"<<endl;
		return 0;
	}
	for(i = 0;i <= a1 - 1;i++){//得出‘-’左边的字符串
		a[i] = c[i];
	} 
	for(j = a1 + 1;j <= a1 + b1 ;j++){//得出‘-’右边的字符串
		b[k] = c[j];
		k++;
	}
	for(k = 0;k < 6;k++){
		if(a[k] == '-'||b[k] == '-'){//判断‘-’两边的字符串中还有没有‘-’
			cout<<"No"<<endl;
			return 0;
		}
	}
	cout<<"Yes"<<endl;
	return 0;
}

```
#### PS：这是我第一次提交题解，求过

---

## 作者：judgejudge (赞：0)

# 带有优化的判断方法！！！
首先这道题大家的思路都是一样的：判断不为a+1位的字符是否在0—9之间；a+1位的字符是否等于“-”。

但是我们观察一下：**只要发现一个不一样的，就输出No！！！**

**因此我们只要查找到一个不符合条件的，就没有必要在进行判断！！！**

在此有一个小小的方法，结合AC代码一起看：
```cpp
#include <iostream>
using namespace std;
int main(){
	char s;
	int i,j,k=0,n,a,b;
	cin>>a>>b;//输入
	for(i=1;i<=a+b+1;i++){
		cin>>s;
		if(k==0){//我们把k作为是否查找到不符合情况的判断标准，查找到就无需判断
			if(i!=a+1){
				if(s<'0'||s>'9')k=1;//如果不符合，k=1
			}
			else{
				if(s!='-')k=1;//不符合，k=1
			}
		}
	}
	if(k==1)cout<<"No"<<endl;//注意：如果k=1说明一定查找到错误的，输出No
	else cout<<"Yes"<<endl;//反之输出Yes
	return 0;
}
```


---

## 作者：RE_Ripper (赞：0)

首先我们先读入一个字符串，不用管长度。                  在读入的字符串中，优先判断a+1是否为‘-’，如果不是，直接输出然后return 0；不需要过多判断。                         
接着注意，如果a+1位字符没有被处理，那么一定会WA。你只要把a+1位的字符串随机赋予一个数字。剩下只要判断是否码在0~9之间好了。如果超限，直接输出return 0；
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int a,b,s;
int main()
{
	string s1;
	cin>>a>>b;
	cin>>s1;
	if(s1[a]!='-')
	{
		cout<<"No"<<endl;
		return 0;
	}
	s1[a]='1';
	for(int i=0;i<=a+b;i++)
	{
		if(s1[i]<'0'||s1[i]>'9')
		{
			cout<<"No"<<endl;
			return 0;
		}
	}
	cout<<"Yes"<<endl;
	return 0;
} 
```
不要忘记换行~

---

## 作者：wushuang0828 (赞：0)

思路：for循环判断字符串除了第i+1位以外的数有没有是0~9之间的，如果有就做标记，将ss赋值等于1，再来判断ss是否等于1或者字符串的a+1位是否不等于-，如果成立输出No，否则输出Yes。

详见代码：
```pascal
var
 a,b,i,ss:longint;
 s:string;
begin
 readln(a,b);//输入a，b
 readln(s);//输入字符串s
 for i:=1 to a+b+1 do
  if (i<>a+1) and not (s[i] in ['0'..'9']) then ss:=1;//除了s的第a+1个字符，其他有一个或以上不为0~9，有就将ss赋值等于1
 if (ss=1) or (s[a+1]<>'-') then writeln('No')
                            else writeln('Yes');//判断如果除了S的第A+1个字符，其他有一个或以上不为0~9 或 如果第A+1个字符不为字符'-' 输出"No"，否则输出"Yes"
end.
```

---

## 作者：CZQ_King (赞：0)

可以全部输入完后再判断。

------------
思路：输入字符串，判断它除了第$a+1$位以外是否为数字，如果不是，$\color{green}Ture\color{black}\rightarrow \color{red}False$。然后再判断第$a+1$位是否为$'-'$，否则$\color{green}Ture\color{black}\rightarrow \color{red}False$。$\text{(LaTeX真好用)}$

------------
代码：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int a,b;//长度
string str;
bool tf;//判断开关
int main(){
	cin>>a>>b>>str;
	for(int i=0;i<(a+b+1);i++){//可以替换为str.length()
		if(int(str[i])>='0'&&int(str[i])<='9')continue;//如果符合就什么都不做
		else//否则
			if(i!=a){//先判断是不是第a+1位
				tf=1;//False
				break;//尽早结束
			}
            /*if里面不是a+1是因为我的开头是0*/
	}
	if(str[a]!='-')tf=1;//再判断是不是-
	if(tf==0)cout<<"Yes\n";//如果全部符合
	else cout<<"No\n";//有一个不符合
    /*懒得打endl了*/
	return 0;//结束
}
```

---

