# Star in Parentheses

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jag2017summer-day3/tasks/jag2017summer_day3_a



# 题解

## 作者：Mono_pigsicklie (赞：6)

### Emma，其实这道题的题目翻译错了，导致我又RE又WA~~（无力吐槽~~）。

------------

### 题目意思应该是：（来自@da32s1da）

#### 给定一个只含‘（ ’、' ) '、' * ’的字符串。找到*前有几个没有结束的括号，并输出。

#### *只有一个。

#### 给了6个样例，答案在后面：


------------


样例1：((*)())   答案 ：2
                
样例2：(*)  答案：1

样例3：(()())* 答案：0

样例4：()*() 答案：0

样例5：((((((((((*)))))))))) 答案：10

样例6：* 答案：0

pg:别忘了回车

------------

下面是代码：

------------
#### （小声bb：只要改一丢丢，就可以获取双倍经验[P1739 表达式括号匹配](https://www.luogu.org/problemnew/show/P1739)）

------------


```cpp
#include<bits/stdc++.h>
using namespace std;
char c[3000];
int top=0,i=0;
bool judge(char c[]) {
	while(c[i]!='@') {
		if(c[i]=='(')top++;
		if(c[i]==')') {
			if(top>0)top--;
			else return 0;
		}
		if(c[i]=='*') break;
		i++;
	}
	if(top!=0)return 0;
	else return 1;
}
int main() {
	scanf("%s",c);
	getchar();
	if(judge(c))printf("0\n");
	else printf("%d\n",top);
	return 0;
}
```


---

## 作者：PC_DOS (赞：2)

推荐关联题目: [P1739 表达式括号匹配](https://www.luogu.org/problemnew/show/P1739)

这是一道模拟题，我们可以把整个处理过程想象成一个栈操作，但是事实上我们并不需要真正建立一个栈空间，只需要用一个变量iSize模拟一下栈里的元素个数即可:

1. 每读到一个左括号"("，相当于进行了一个入栈操作，元素个数加一。

2. 每读到一个右括号")"，相当于进行了一个出栈操作，元素个数减一。

3. 读到星号时，栈操作结束，此时元素的个数即为未匹配的括号个数。

由于题目保证不会出现")("这类完全非法的括号组合方式，因此可以保证iSize>=0恒成立，不需要特判。

代码:
```
#include <iostream>
#include <string>
using namespace std; //头文件和命名空间
int main(){
    string sInput; //存放输入的字符串
    register int i,iSize=0; //i-循环计数器；iSize-模拟栈空间大小
    cin>>sInput; //读入字符串
    for(i=0;i<sInput.length();++i){ //遍历字符串
        if(sInput[i]=='(') //每读到一个左括号"("，相当于进行了一个入栈操作，元素个数加一
            ++iSize;
        if(sInput[i]=='*') //读到星号时，栈操作结束，退出循环，此时元素的个数即为未匹配的括号个数
            break;
        if(sInput[i]==')') //每读到一个右括号")"，相当于进行了一个出栈操作，元素个数减一
            --iSize;
    }
    cout<<iSize<<endl; //输出栈空间大小，即答案
    return 0; //结束
}
```

---

## 作者：封禁用户 (赞：1)

其实这题很简单：看到左括号，答案+1。看到右括号，答案-1。

#代码如下：
```pascal
var
    s:string;
    i,j,k:longint;
begin
    readln(s);
    k:=pos('*',s);//找“*”号
    for i:=1 to k-1 do//注意要减一
    begin
        if(s[i]='(')then inc(j)//看到左括号，答案+1
        else dec(j);//看到右括号，答案-1。
    end;
    writeln(j);//输出
end.

```

---

## 作者：wubaiting2020 (赞：0)

思路：先读入，在之前记录未完成的括号，在读到星号时结束处理。
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int len,bj1;
    string s;
    cin>>s;//读入
    len=s.length();
    for(int i=0;i<len;i++)
    {
        if(s[i]=='(')bj1++;//如果是左括号，未完成数量++
        if(s[i]==')'&&bj1>0)bj1--;
//如果是右括号，且前面有左括号未完成，就匹配，未完成数量--
//第二个条件是防止“)(”的出现
        if(s[i]=='*'){cout<<bj1<<endl;return 0;}//读入星号时，结束，输出未完成数量
    }
    return 0;
}
```

---

## 作者：CZQ_King (赞：0)

### 这道题的做法：找出左括号和右括号的数量，相减，即可得出答案。
注意：如果左括号的数量小于右括号的数量，相减则会出错，所以还要加一个$abs()$（绝对值）


------------

```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
string a;
int i,l,r;//循环变量，左括号数，右括号数
int main(){
    cin>>a;
    while(a[i]!='*'){//循环直到找到"*"
        if(a[i]=='(')l++;//如果是左括号
        else r++;//右括号
        i++;//查找下一个
    }
    cout<<abs(l-r)<<endl;//输出相减的绝对值
    /*这样也可以：
    	cout<<max(l,r)-min(l,r)<<endl;*/
    return 0;//完美结束
}
```

---

