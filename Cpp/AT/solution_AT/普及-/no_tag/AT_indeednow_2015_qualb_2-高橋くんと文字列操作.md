# 高橋くんと文字列操作

## 题目描述

[problemUrl]: https://atcoder.jp/contests/indeednow-qualb/tasks/indeednow_2015_qualb_2

高橋くんは文字列 $ s $ を持っており、文字列 $ t $ を作りたいと思っています。 高橋くんは、文字列の末尾の $ 1 $ 文字を先頭に追加し、末尾の $ 1 $ 文字を削除するという操作を文字列 $ s $ に行うことで、文字列 $ s $ を文字列 $ t $ にしたいと考えています。

最小で何回この操作を行えば、文字列 $ s $ を文字列 $ t $ にできるでしょうか？最小の操作回数を出力するプログラムを書いてください。この操作では文字列 $ s $ を文字列 $ t $ に変換することができない場合、$ -1 $ と出力してください。

## 说明/提示

### Sample Explanation 1

`abcd` の末尾の文字を先頭に追加すると、 `dabcd` となり、ここから末尾の文字を削除すると、 `dabc` となります。 よって、$ 1 $ 回の操作で $ s $ は $ t $ に等しくなります。

### Sample Explanation 2

問題文中の操作を $ s $ に $ 2 $ 回行うと $ t $ と等しくなります。 $ 5 $ 回、$ 8 $ 回行っても $ t $ と等しくなりますが、最小のものを求める必要があります。

## 样例 #1

### 输入

```
abcd
dabc```

### 输出

```
1```

## 样例 #2

### 输入

```
abcabcabc
bcabcabca```

### 输出

```
2```

## 样例 #3

### 输入

```
aaa
a```

### 输出

```
-1```

## 样例 #4

### 输入

```
cab
cab```

### 输出

```
0```

# 题解

## 作者：Fcersoka (赞：5)

~~又是一道水题呢~~ ！   
[题目传送门](https://www.luogu.com.cn/problem/AT1210)    
这是一道有关于字符串的题 ，题目意思就是让我们把一个字符串反复执行一个操作 ，直到这个字符串变成另外一个给出的字符串 。   
而这个操作呢 ，就是把一个字符串的最后一个字符添加到最前面 ，最后删掉最后一个字符就行了 。    
先讲一下思路 ，用循环把要进行操作的字符串进行如题目所说的操作 ，在每次循环前判断字符串是否变成第2个字符串 ，在每次循环结束后 ，把操作数加1就行了 。   
思路讲完后 ，就是代码了 ,代码如下 。
```cpp
#include<bits/stdc++.h>  //依旧是熟悉的万能头
using namespace std;
bool pd(string a,string b){  //判断是否变成第2个字符串的函数
	for(int i=0;i<a.length();i++){
		if(a[i]!=b[i])  //一个字符一个字符判断
		return false;
	}
	return true;
}
string a,b;
void cz(){ //进行操作的函数
	char temp=a[a.length()-1];//先用一个字符变量储存字符串中最后一个字符
	for(int i=a.length()-1;i>=0;i--)
	swap(a[i],a[i+1]);//把第2个字符与倒数第2个字符之间的所有字符往后移
	a[0]=temp;//把最后一个字符放到第一个字符的位置
}
int main(){
	cin>>a>>b;
	for(int i=1;i<=a.length();i++){
		if(pd(a,b)==true){
		cout<<i-1<<endl;//别忘了换行
		return 0;	
		}
		cz();
	}
	cout<<-1<<endl;//如果不能使字符串a变成字符串b则输出-1
	return 0;//结束
}
```
以上代码仅供参考 ，谢谢 ！

---

## 作者：Blikewsr (赞：3)

 - [[ 原题链接 ]](https://www.luogu.com.cn/problem/AT1210)   
                   
 - 题目描述
 高桥现在有字符串 ， 想将字符串转变为另外一个字符串 。 他打算将文字列末尾的一个字加在最前面 ， 并删掉末尾的一个字 ， 以这种操作来将字符串转为字符串 。  最少要进行几次这种操作才能将字符串转为字符串呢 ？ 请写下输出最小次数的程序 。 如果不能转化的话请输出 $-1$ 。                                      
 - 输入格式
 两行 ， 一行一个字符串 。    
                                
 - 思路                            
  1. 当 $s1 = s2$ ：                                               
     直接输出 $0$ 。                        
  2. 当 $s1$  的长度与  $s2$  的长度不相等 ：                                   
     直接输出 $-1$ 。                            
  3. 先用一个字符变量把 $s1$ 中的最后一个字符保存下来 ， 再把除了第一个字符以外的所有字符都往前移一位 ， 最后再把第一个字符改成刚才用字符变量保存的字符 。                   
  4. 其它的情况 ：                     
     直接输出 $-1$ 。               
                                     
 - 代码实现                                      
 ```cpp
#include<bits/stdc++.h>                          // 万能头      
using namespace std;
string s1,s2;                                    // 定义两个字符串            
char c;                                          // 用来保存最后一个字符的 char 变量 
int ans;                                         // 最少的操作次数           
bool string_bool(string x,string y){             // 判断两个字符串是否一样           
	if(x==y) return true;                        // 如果一样 ， 返回 true        
	return false;                                // 反之                   
}
void string_do(){                                // 执行的函数                  
	for(int i=1;i<s1.size();i++){                // 最多只有 s1.size()-1 次操作             
		ans++;                                   // 操作次数加 1                
		c=s1[s1.size()-1];                       // 先把最后一个字符保存下来            
		for(int j=s1.size()-1;j>=0;j--)          // 最最后一字符开始直到第二个字符           
			s1[j]=s1[j-1];                       // 每个字符都改成它的前一个字符                      
		s1[0]=c;                                 // 再把第一个字符改成之前保存下来的字符                    
		if(string_bool(s1,s2)){                  // 判断两个字符串是否相同              
			cout<<ans<<'\n';                     // 如果一样 ， 就直接输出次数        
			return ;	                         // 并且结束                  
		}
	}
	cout<<(-1)<<'\n';                            // 其他的情况 ， 就说明无法完成 ， 就输出 -1                      
	return ;
}
int main(){
	cin>>s1>>s2;                                 // 输入两个字符串                   
	if(string_bool(s1,s2)){                      // 判断初始的两个字符串是否相同                
		cout<<(0)<<'\n';                         // 如果是 ， 就说明不用操作 ， 直接输出 0              
		return 0;	
	}
	string_do();                                 // 执行 操作            
	return 0;	                                 // 完美结束 
}
```
                
 谢谢 ！        
 

---

## 作者：Kevin_Zhen (赞：3)

## 题目大意
给定两个字符串 $a$ 和 $b$，每次操作可以把 $a$ 字符串队尾的字符扔到队首，问多少次操作后字符串 $a$ 变为 $b$。
## 特判
如果两个字符串长度不相等，则无论如何操作，两字符串都一定不会相等，这时直接输出 $-1$ 即可。
```cpp
if (lena != lenb) {
	printf("-1\n");
	return 0;
}
```
## 变量介绍
1. 字符串 $a$ 和 $b$。
2. $lena$ 记录 $a$ 的长度，$lenb$ 记录 $b$ 的长度。
3. 变量 $cnt$，用于记录已经进行的操作次数。

## 解题过程
读入两个字符串，并记录它们的长度。
```cpp
cin >> a >> b;
lena = a.size(); lenb = b.size();
```
然后特判。
```cpp
if (lena != lenb) {
	printf("-1\n");
	return 0;
}
```
如果两个字符串长度相等，进入循环进行操作。  
首先注意循环的判断条件。
```cpp
a != b && cnt < lena
```
这个判断语句的意思是，如果两个字符串相等了，则不用再进行操作，跳出循环，输出操作次数；而如果操作次数达到了两个字符串的长度，也就是说我们把字符串 $a$ 整个转了一圈、转回了原样，仍然没有跳出循环，那么两个字符串是不会变成一样的，结束循环即可。  

循环内部实现如下。
```cpp
char t = a[lena - 1];
a.insert(a.begin(), t);
a.erase(a.end() - 1);
++cnt;
```
就是记录下 $a$ 的最后一个字符，将它插入到 $a$ 的第一个元素的迭代器处，然后删除 $a$ 末尾的元素，操作次数加 $1$ 即可。

最后输出，如果 $cnt$ 等于两字符串长度，则由我们上方已经推断出的结论得知，两字符串不可能变为一样，输出 $-1$；否则输出 $cnt$。
```cpp
if (cnt == lena) printf("-1\n");
else printf("%d\n", cnt);
```
## AC CODE
```cpp
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

string a, b;
int lena, lenb;
int cnt = 0;

int main() {
	cin >> a >> b;
	lena = a.size(); lenb = b.size();
	if (lena != lenb) {
		printf("-1\n");
		return 0;
	}
	while (a != b && cnt < lena) {
		char t = a[lena - 1];
		a.insert(a.begin(), t);
		a.erase(a.end() - 1);
		++cnt;
	}
	if (cnt == lena) printf("-1\n");
	else printf("%d\n", cnt);
	return 0;
}
```
## 感谢观赏！
## Update：修改了排版错误的问题。

---

## 作者：蒟___ (赞：0)

## 题解——高桥的字符串操作：


如果有难易度评测的话应该是入门到csp-jDay1T1的难度？？

一开始我就在想这道题到底要不要用STL写,又想到如果不用的

话那才能体现本蒟蒻的水平呀~~（说白了就是菜）~~

好的，于是我果断选择了deque~~（stl香啊）~~，

然后，被OJ
kill了，没有然后...

于是最终，就决定是你啦，上吧！! STRING！！！（好中二啊...）

于是此代码便横空出世。

---

### 下面进入正题。

直接放代码啦，因为本题解法比较单一，此代码的思想与其

他dalao思路应该不会有太大差别，

嗯。所以思路直接标注在代码里啦~~~

~~~cpp

#include<iostream>
#include<algorithm>
#include<deque>
#include<cstring>//标准模板库万岁！！！

using namespace std;
//deque<char> a;

signed main(void) {
	ios::sync_with_stdio(false);
	string x, y;
	cin >> x >> y;
	int ans = 0, time = 0;
	
	if (x.size() != y.size()) 	cout << ~0<<endl;//这里允许我小小的皮一下（笑） 
        //如果长度对不上固然不成，输出-1
	else{
		while (time <= x.size() - 1 && x != y) { 
			time++;   //计数器累加
			char del = x[x.size() - 1];//del储存当前末尾值
			x.insert(x.begin(), del), x.erase(x.end() - 1);//将末尾字符移到字符串最前面
		}
		if (time < x.size() - 1) 	cout << time << endl;
		else cout << -1<< endl ;//如果匹配一轮下来对不上就说明字符不一致，也不成
	} 
	return 0;
}

~~~
另外强调一下，【ios::sync_with_stdio(false);】意为将

iostream和c的标准输入输出分开，这样一来，减少了缓冲

时
间的cin和cout就会更快一些，快到和scanf与printf差不太

多的亚子。



总之啦，看到代码先要自行理解（~~你懂的我什么意思的
（误）~~     ）

想必此题对你来说一定会很简单吧！！！++油！！！

---
大概先到这里吧~~~ 拜拜~~~

本蒟蒻继续奋进中...

---

