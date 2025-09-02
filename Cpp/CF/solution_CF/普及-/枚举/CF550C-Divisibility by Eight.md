# Divisibility by Eight

## 题目描述

You are given a non-negative integer $ n $ , its decimal representation consists of at most $ 100 $ digits and doesn't contain leading zeroes.

Your task is to determine if it is possible in this case to remove some of the digits (possibly not remove any digit at all) so that the result contains at least one digit, forms a non-negative integer, doesn't have leading zeroes and is divisible by 8. After the removing, it is forbidden to rearrange the digits.

If a solution exists, you should print it.

## 样例 #1

### 输入

```
3454
```

### 输出

```
YES
344
```

## 样例 #2

### 输入

```
10
```

### 输出

```
YES
0
```

## 样例 #3

### 输入

```
111111
```

### 输出

```
NO
```

# 题解

## 作者：灵光一闪 (赞：14)

这题哪要什么dp嘛，直接运用小学知识就可以轻易解决

这题的关键：当一个数想被8整除，末尾3个数一定是8的倍数，so，既然是任意一个……

首先：只要有一个0存在，``cout<<YES<<endl<<"0"<<endl;``

然后就快乐循环辣~
核心代码：
```
    for(int i=0;i<s.size();i++){
        for(int j=i+1;j<s.size();j++){
            for(int k=j+1;k<s.size();k++){
                if(((s[i]-'0')*100+(s[j]-'0')*10+(s[k]-'0'))%8==0){//发现一个
                    puts("YES");//绝对是YES，因为既然这个给定的数没有0（如果有0的话早结束了（见上面））所以s[i]绝对不是0，所以可以放心输出，这个明白了这个代码就明白了
                    cout<<s[i]<<s[j]<<s[k]<<endl;
                    return 0;
                }
            }
            if(((s[i]-'0')*10+(s[j]-'0'))%8==0){
                puts("YES");
                cout<<s[i]<<s[j]<<endl;
                return 0;
            }
        }
        if((s[i]-'0')%8==0){
            puts("YES");
            cout<<s[i]<<endl;
            return 0;
        }
    }
```
完整代码要贴么？算了，贴一下把
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<string>
using namespace std;
int main(){
    string s;
    cin>>s;
    int a=s.find('0');
    if(a<s.size()){
        puts("YES");
        puts("0");
        return 0;
    }
    for(int i=0;i<s.size();i++){
        for(int j=i+1;j<s.size();j++){
            for(int k=j+1;k<s.size();k++){
                if(((s[i]-'0')*100+(s[j]-'0')*10+(s[k]-'0'))%8==0){
                    puts("YES");
                    cout<<s[i]<<s[j]<<s[k]<<endl;
                    return 0;
                }
            }
            if(((s[i]-'0')*10+(s[j]-'0'))%8==0){
                puts("YES");
                cout<<s[i]<<s[j]<<endl;
                return 0;
            }
        }
        if((s[i]-'0')%8==0){
            puts("YES");
            cout<<s[i]<<endl;
            return 0;
        }
    }
    puts("NO");
    return 0;
}
```

---

## 作者：FuriousC (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/CF550C)

**思路：暴力枚举**

特判一下 $0$ 和 $8$ 即可

这里涉及到一个小学数学知识：一个被 $8$ 整除的数的末尾三位一定能被 $8$ 整除

**代码：**

```
#include<bits/stdc++.h>
using namespace std;
int main(){
    string str;
    int a;
    cin>>str;
    a=str.find('0');//先找0
    if(a<str.size()){
        cout<<"YES\n0";//有0就输出YES 0
        return 0;
    }
    for(int i=0;i<str.size();i++){
        a=str[i]-'0';
        for(int j=i+1;j<str.size();j++){
            int b=str[j]-'0';
            for(int k=j+1;k<str.size();k++){//暴力循环
                int c=str[k]-'0';
                if((a*100+b*10+c)%8==0){
                    cout<<"YES\n"<<a<<b<<c;
                    return 0;
                }//找到三位能被8整除的并输出
            }
            if((a*10+b)%8==0){
                cout<<"YES\n"<<a<<b;
                return 0;
            }//找到两位能被8整除的并输出
        }
        if(a%8==0){
            cout<<"YES\n"<<a;
            return 0;
        }//找到一位能被8整除的并输出
    }
    cout<<"NO";//其他情况输出no
    return 0;
}
```


---

## 作者：HuZHUNZHUN (赞：2)

~~这道题很㵘诶~~

如果最后得到一位数的话，只能是 $0$ 或者 $8$ 才可以，

一层循环找 $0$ 和 $8$ 解决。

如果最后得到两位数的话，循环找就可以了，

两层循环枚举两位解决。

如果最后得到三位数的话，循环找就可以了，

三层循环枚举三位解决。

如果最后得到四位数及以上的话，其实能否被 $8$ 整除只和最后三位数有关，

不需要解决。

综上：问题解决了。

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string number;
int a[110];
int main()
{
	ios::sync_with_stdio(false);
	cin>>number;
	int l=number.length();
	for(int i=0;i<l;i++) a[i+1]=number[i]-'0';
	for(int i=1;i<=l;i++)
	{
		if(a[i]==0)
		{
			cout<<"YES\n0"<<endl;
			return 0;
		}
		else if(a[i]==8)
		{
			cout<<"YES\n8"<<endl;
			return 0;
		}
	}
	for(int i=1;i<=l;i++) for(int j=i+1;j<=l;j++)
	{
		if((a[i]*10+a[j])%8==0)
		{
			cout<<"YES\n"<<a[i]<<a[j]<<endl;
			return 0;
		}
	} 
	for(int i=1;i<=l;i++) for(int j=i+1;j<=l;j++) for(int k=j+1;k<=l;k++)
	{
		if((a[i]*100+a[j]*10+a[k])%8==0)
		{
			cout<<"YES\n"<<a[i]<<a[j]<<a[k]<<endl;
			return 0;
		}
	}
	cout<<"NO\n";
	
	return 0;
}

```

---

## 作者：Maxrage (赞：2)

这题确实可以用小学数学解决（后三位除8，证明方法就是$a×1000+bcd$中，1000%8=0）。

但是，但是！  
可以打表的！  
好吧不能完全叫打表。  
我们先来看一下可实现性：  
从0————999...99(100个9)  
但是，你不要忘了小学数学！  
他无外乎位数小于三位的数和位数大于三位的数。  
位数大于三位的数，可以用$a×1000+bcd$表示    
也就是说，问题又转换成了找三位数的问题（因为往高了去的都是靠后三位被8整除的）。  
~~我是不会告诉你我怕再写一篇一样的不会被通过才来打表的~~  
换句话说，我们只需要把能被8整除的三位数写出来就可以了。  
然后你又可以说：那也很多啊，怎么，你要...  
### 方法一  
我们可以看到很多可以被八整除的数形如：416,808。  
而他们根！本！就！不！用！枚！举！出！来！  
很简单啊：16、8/0在一开始就会被输出，管你什么别的。  
那同理800多你就不用管了，形如×0×、××0、×00、×16、×24、××8...你都不用管了。  
然后打表。  
### 方法二
我们是谁啊？OIer啊！~~我们的目标是？AK IOI!~~  
我们可以用程序啊！  
这样问题就简单了，造出8倍数的i，然后
~~~
a=s.find("i");
    if(a<s.size())
    {
        printf("YES\ni");
        return 0;
    }
~~~
就完了呗。  
且慢！这有个极大的漏洞！方法一的众人也请注意！  
一个问题：526到底该输出Yes/n56呢，还是NO呢？  
当然，蒟蒻都知道，该输出前者，但是！你这样的程序会输出后者！  
原因很简单，你判断的是连着的！  

#### 改进  
不要怕吗，遇到困难应该继续前进！  
这个题有个温馨提示，顺序不会被打乱的，那就...  
循环套循环！  
比如526：  
~~~
a=s.find("5");
    if(a<s.size()-1)
    {
        for(int i=1...)
        {
         b=s.find("6");
         ...
        }
    }
~~~
这样就可以特判了——虽然时间很尴尬。   
或者继续用方法一勤奋的思想，特判这些数  
~~~
a=s.find("526");
    if(a<s.size())
    {
        printf("YES\n56");
        return 0;
    }
~~~
这样也行，就是码量增加，且一忘皆无...

#### code
不是吧阿sir，这破题打表代码都要？


---

## 作者：Creator_157 (赞：2)

### 大体题意：
给你一个数，让你删取其中的某些数使它成为 8 的倍数。

如果可以，输出 “YES”和 删后的数 ；如果不能就输出“NO”。

------------
### 思路：
运用我们 ~~小学二年级~~ 学过**关于8的倍数**的知识就可以写出这道题。

只要 **后三位可以被8整除** 则这个数就可以被8整除，所以我们枚举后三位即可。

当然，这种做法可以简化，当这个数**有一位为0时**可以删去除0外所有位上的数。

------------
### code
```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
string s;
int a;
int main()
{
    cin>>s;
    a=s.find('0');
    if(a<s.size())
    {
        printf("YES\n0");
        return 0;
    }
    for(int i=0;i<s.size();i++)
    {
        for(int j=i+1;j<s.size();j++)
        {
            for(int l=j+1;l<s.size();l++)
            {
                if(((s[i]-'0')*100+(s[j]-'0')*10+(s[l]-'0'))%8==0)
                {
                    printf("YES\n");
                    cout<<s[i]<<s[j]<<s[l];
                    return 0;
                }
            }
            if(((s[i]-'0')*10+(s[j]-'0'))%8==0)
            {
                printf("YES\n");
                cout<<s[i]<<s[j];
                return 0;
            }
        }
        if((s[i]-'0')%8==0)
        {
            printf("YES\n");
            cout<<s[i];
            return 0;
        }
    }
    printf("NO");
    return 0;
}

```


---

## 作者：封禁用户 (赞：1)

[原题传送门](https://codeforces.com/problemset/problem/550/C)
一道模拟题。
## 前置芝士（写给小学生看的）
#### 结论
8 的整除特征：若末三位为 8 的倍数，则整个数为 8 的倍数。
#### 推导
设 $n$ 是 $\geq1000$ 的整数。

$n = 1000a+b$

$\because n\equiv1000a+b\pmod{8 } \ \texttt{且} \ 8\mid 1000a$

$ \therefore n\equiv b \pmod{8} $

## 思路 
根据结论，我们可以打表出一个数组 mult8，表示字符串下8的倍数。

```
for(int i=0;i<1000;i+=8){
   cout<<'"'<<i<<'"'<<",";
}
```
mult8 数组：

```
const string mult8[]={"0","8","16","24","32","40","48","56","64","72","80","88","96","104","112","120","128","136","144","152","160","168","176","184","192","200","208","216","224","232","240","248","256","264","272","280","288","296","304","312","320","328","336","344","352","360","368","376","384","392","400","408","416","424","432","440","448","456","464","472","480","488","496","504","512","520","528","536","544","552","560","568","576","584","592","600","608","616","624","632","640","648","656","664","672","680","688","696","704","712","720","728","736","744","752","760","768","776","784","792","800","808","816","824","832","840","848","856","864","872","880","888","896","904","912","920","928","936","944","952","960","968","976","984","992"};

```

然后，从数组头循环到数组末。
```
for(int i=0;i<len;i++){
//......
}
```
循环里面分情况讨论，如果数组第 i 位是一位数，就循环一遍，搜索是否有它。
```
if(k.length()==1){
	for(int j=0;j<lens;j++){
		if(str[j]==k[0]){
			cout<<"Yes"<<endl;
			cout<<k;
			return 0;
		}
	}
}
```
如果是两位数就写二重循环，逐位判断是否有它。
```
if(k.length()==2){
	for(int j=0;j<lens;j++){
		if(str[j]==k[0]){
			for(int q=j+1;q<lens;q++){
				if(str[q]==k[1]){
					cout<<"Yes"<<endl;
					cout<<k;
					return 0;
				}
			}
		}
	}
}
```
如果是三位数就用三重循环，逐位判断是否有它。
```
if(k.length()==2){
	for(int j=0;j<lens;j++){
		if(str[j]==k[0]){
			for(int q=j+1;q<lens;q++){
				if(str[q]==k[1]){
					for(int t=q+1;t<lens;t++){
						if(str[t]==k[2]){
							cout<<"Yes"<<endl;
							cout<<k;
							return 0;
						}
					}
				}
			}
		}
	}
}
```
（注：上述 k 是 str[i])

由于前面输出过 Yes 之后 return 0 了，最后只要输出 No 就行了。

时间复杂度：$\mathcal O (n^3m)$。（n是字符串长度，m是 mult8 长度即125）考虑最坏情况 $n^3m = 100^3 \times 125 = 1.25 \times 10^8$，不会 TLE。


[AC记录](https://www.luogu.com.cn/record/54434531)

本题完。

---

## 作者：Neoomgg (赞：1)

看见全站python那么少，且来刷一题罢——驯鹿

参考上面大佬的思想，先特判0、8的情况，再暴力枚举。

个人认为，这其实是一道小学奥数题，三位数及以上的数只要后三位整除8，此数及整除8（本蒻蒻一开始漏掉了两位数整除8的情况）。

代码呈上：

```python
n = input()

def pan(n):
    '''特判'''
    for i in n:
        if i == '0':
            print('YES')
            print('0')
            return
        elif i == '8':
            print('YES')
            print('8')
            return
    '''暴力'''
    for i in range(len(n)-1, -1, -1):
        if int(n[i]) % 2 == 0:
            for j in range(i-1, -1, -1):
                '''注意'''
                if int(n[j]+n[i]) % 8 == 0:
                    print('YES')
                    print(n[j]+n[i])
                    return
                '''注意'''
                elif int(n[j]+n[i]) % 4 == 0:
                    for k in range(j-1, -1, -1):
                        if int(n[k]+n[j]+n[i]) % 8 == 0:
                            print('YES')
                            print(n[k]+n[j]+n[i])
                            return
    print('NO')

pan(n)

```

---

## 作者：SSHhh (赞：0)

这道题的思路其实很简单，先用特判处理掉数字中有 0 或者有 8 的情况（也就是直接输出 0 或8），然后剩下的暴力判断即可。。。

那暴力如何去判断呢？我们先来注意一个性质，能被 8 整除的数的后三位一定能被 8 整除。因为本题要求输出任意解，所以只需判断三位数之内 8 的倍数是否在这个数字里面即可。

那么我们用 s[i] 和 e[i] 来记录 i 最先出现和最后出现的位置，然后对于 8~992（实际上是 16~992） 中每一个数，暴力取出三个位上的数 a,b,c ，然后判断 b 有没有在 s[a] 和 e[c]之间出现就可以了。复杂度 O(125N)。（因为此题中 N 特别小，所以直接暴搞就能过）

最后注意一个细节，取出来的数是不含前导 0 的，所以这里必须要加一个特判。

剩下的看代码实现吧：
```cpp
#include<iostream>
using namespace std;
int sum[105],s[10],e[10];
int main()
{
	int n=0;string str;
	cin>>str;
	for(int k=0;k<str.size();k++)
	{
		int i=++n,now=str[k]-'0';sum[i]=now;
		s[now]=(s[now]?s[now]:i),e[now]=i;	//蛇皮方法求 s[i] e[i]
	}
	if(s[0])	{cout<<"YES\n0"; return 0;}	if(s[8])	{cout<<"YES\n8"; return 0;}	//特判 0 和 8
	for(int i=8;i<=992;i+=8)
	{
		int a=i/100,b=i/10%10,c=i%10;	//取出 a,b,c
		if((!s[a] && a) || (!s[b] && a && b) || !s[c])	continue;	//如果 a,b,c 不在数列里，直接跳过
		for(int j=(a?s[a]+1:1);j<e[c];j++)
			if(sum[j]==b || (a==0 && b==0))	{cout<<"YES\n";if(a)cout<<a;if(b)cout<<b;if(c)cout<<c; return 0;}	//暴力判断
	}
	cout<<"NO";
	return 0;
}
```

---

