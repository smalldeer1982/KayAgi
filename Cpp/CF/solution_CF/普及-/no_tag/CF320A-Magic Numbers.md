# Magic Numbers

## 题目描述

A magic number is a number formed by concatenation of numbers $ 1 $ , $ 14 $ and $ 144 $ . We can use each of these numbers any number of times. Therefore $ 14144 $ , $ 141414 $ and $ 1411 $ are magic numbers but $ 1444 $ , $ 514 $ and $ 414 $ are not.

You're given a number. Determine if it is a magic number or not.

## 样例 #1

### 输入

```
114114
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
1111
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
441231
```

### 输出

```
NO
```

# 题解

## 作者：田_穗 (赞：7)

### 题目:
魔数是由1，14，144组成的，每个数字可以重复使用，例如：14144，141414和1411就是魔数，而1444，514 和414就不是魔数。判断一个数是不是魔数。
### 解题思路：
(整形版本代码量最少的一个题解)

我采用从后向前排查，也就是从这个整数的末尾开始判断，具体步骤如下：

1. 判断这个整数末尾是否是1，14或144。
2. 若是，则将这个整数的末尾的1，14或144删除。
3. 若不是，则输出 "NO"，结束。
4. 若这个数被去尾一直到只剩下0了，则输出"YES"，结束。

### 代码+注释：
```cpp
#include<stdio.h>
int n;
int main(){
	scanf("%d",&n);//输入
	while(1){
		if(n%10==1) {n/=10;continue;}
     //若末尾为1，则去尾，进入下一个循环
     
		if(n%100==14) {n/=100;continue;}
     //若末尾为14，则去尾，进入下一个循环
     
		if(n%1000==144) {n/=1000;continue;}
     //若末尾为144，则去尾，进入下一个循环
     
		if(n==0) {printf("YES");return 0;}
  //若此数全部去尾成功，则满足题意，输出"YES"，结束
  
		printf("NO");
		return 0;
  //若中途去尾失败，则不满足题意，输出"NO"，结束
	}
}
```
### 纯代码：
```cpp
#include<stdio.h>
int n;
int main(){
	scanf("%lld",&n);
	while(1){
		if(n%10==1) {n/=10;continue;}
		if(n%100==14) {n/=100;continue;}
		if(n%1000==144) {n/=1000;continue;}
		if(n==0) {printf("YES");return 0;}
		printf("NO");
		return 0;
	}
}
```

---

## 作者：Dimly_dust (赞：2)

这题说实话就是水题，像我这么蒟才会WA的。

看题所知魔数有三个成立条件：

1. 此数任意位数不为除 $1$ 和 $4$ 以外的数。（循环判断即可）

2. 无连续三位为 $4$ 。

3. 首位不为除一外的的任何数。

就此次得出答案：

- 字符串版本：

```cpp
#include<bits/stdc++.h>
using namespace std;
string check(string n)
{
	int check4=0;
	if(n[0]!='1') return "NO";
	for(int i=0;i<n.size();i++)
	{
		if(n[i]!='1'&&n[i]!='4') return "NO";
		else if(n[i]=='4')check4++;
		else if(n[i]=='1') check4=0;
		if(check4==3) return "NO";
	}
	return "YES";
}
int main()
{
	string n;
	cin>>n;
	cout<<check(n)<<endl;
	return 0;
}

```
- 普通整形版本（因为数据较小可以使用）：

```cpp
#include<bits/stdc++.h>
using namespace std;
string check(short n)
{
	int check4=0;
        int i;//保留最后一位数
	for(i=n;i>10;i/=10)
	{
		if(i%10!=1&&i%10!=4) return "NO";
		else if(i%10==4)check4++;
		else if(i%10==1) check4=0;
		if(check4==3) return "NO";
	}
	if(i!=1) return "NO";//特判最后一位
	return "YES";
}
int main()
{
	short n;
	cin>>n;
	cout<<check(n)<<endl;
	return 0;
}

```


---

## 作者：修罗海神王 (赞：2)

# 一枚蒟蒻的orz文章
### 这篇文章也许不是最好的，~~但它思路清晰~~，很适合一些跟我差不多的蒟蒻。
好了，我们开始进入正题：

 1、不难发现，只要开头是1的数字，任何都可以组合，所以不需要有1这个数的特判。

2、紧接着，多说无益，毋庸置疑的就是除了1和4之外的数字了，如果这位数字不是1或4，直接标记bo。


## 前方高能
3、如果这一位数字是4，那么不妨将这一位数字定义为一个组合的第二位，也就是说，第i位遇到的4，要么是14的第二位4，要么是144的第二位4，千万不要混淆：将这位数在第一个组合定义为第二位，而在另一个组合又定义成第三位，必须确定一个不变的量。

4、可以看得出来，这一位的前一个数必定是一个'1'，所以，如果前一位不是1，那么也可以标记掉了。否则的话，~~还有希望~~。

5、最后，终于可以判断是否为组合了。这里注意，如果这位数字已经到达了最后一位，那么就可以断定，他一定是一个合法的组合——14，因为有前面的判断。到了这里，相信大家会有疑惑，如果这位数字所在的组合是144的怎么办啊？不要担心，我们只需要将i加1就行了，因为循环上面也会加1，所以直接跳过了第三位4,。再接着，如果它的下一位是1，那么我们可以来一个小恶作剧，i=i，哈哈~O(∩_∩)O！再接着，就是下一位不是4或1了，也可以将bo标记掉。

6、最后直接根据bo来输出就行啦！

相信认真读的人会打出代码来，所以我用一个反作弊系统来批判一下那些想要直接复制的人，代码里就不加注释了。

来来来（仔细看哦！）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int bo=0,l;
string st;
int main()
{
	cin>>st;l=st.size();
	for(int i=0;i<l;i++)
	{
		int bo1=0;
		if(!(st[i]=='1'||st[i]=='4')) bo=1;
		if(st[i]=='4')
		{
			if(st[i-1]=='1') bo=1;
			  else bo1=1;
			if(bo1&&i!=l-1)
			{
				if(st[i+1]=='4') i++;
				  else if(st[i+1]=='1') i=i;
			             else bo=1;
			}
		}
	}
	if(!bo) cout<<"yES\n";
	  else cout<<"NO\";
	return 0;
}
```
我这反作弊做的太好了吧！O(∩_∩)O哈哈~！

---

## 作者：qwq___qaq (赞：1)

本题解采用的是字符串，也推荐大家使用，主要优点是方便查询每个数位上的数字。
## 方法一
逆序删除，这样我们就可以避免冲突，不能删就输出 `NO`，上到最后都还可以就输出 `YES`，不能吸氧。
### AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
string n;
int main(){
	cin>>n;
	int len=n.size();
	for(int i=len-1;i>=0;){
		if(n[i]=='1')
			i--;//前移一位
		else if(i>='1'&&n[i]=='4'&&n[i-1]=='1')
			i-=2;//前移二位
		else if(i>=2&&n[i]=='4'&&n[i-1]=='4'&&n[i-2]=='1')
			i-=3;//前移三位
		else{
			puts("NO");
			return 0;
		}
	}
	puts("YES");
	return 0;
}
```
## 方法二
正序查找，如果为 1 就往后删，最多删两个，计数变量 `i` 到删完后的下一位，如果不为 1 输出 `NO`，如果全部都删完了就输出 `YES`。
### AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
string n;
int main(){
	cin>>n;
	int len=n.size();
	for(int i=0;i<len;){
		if(n[i]=='1'){
			i++;
			for(int j=1;j<=2;j++)
				if(n[i]=='4')
					i++;
				else
					break;
		} else{
        	puts("NO");
        	return 0;
		}
	}
	puts("YES");
	return 0;
}
```
## 方法三
正序查找，如果有不是 1 和 4 的就输出 `NO`，如果有 连续三个及以上的也输出 `NO`，否则输出 `YES`，这种方法有很多细节要注意
### AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
string n;
int main(){
	cin>>n;
	int len=n.size();
	if(n[0]=='4'){
		puts("NO");
		return 0;
	}//第一位为 4
	if(len==1){
		if(n[0]=='1')
			puts("YES");
		else
			puts("NO");
		return 0;
	}
	if(len==2){
		if(n[0]=='1'&&(n[1]=='4'||n[1]=='1'))
			puts("YES");
		else
			puts("NO");
		return 0;
	}//长度不够 3
	if((n[0]!='1'&&n[0]!='4')||(n[1]!='1'&&n[1]!='4')){
		puts("NO");
		return 0;
	} 特判前 2 位
	for(int i=2;i<len;i++)
		if((n[i]!='1'&&n[i]!='4')||(n[i]=='4'&&n[i-1]=='4'&&n[i-2]=='4')){
			puts("NO");
			return 0;
		}
	puts("YES");
	return 0;
}
```

---

## 作者：chenkaiwen (赞：1)

这一题是一道字符串处理题，我们观察题意和找规律可得，以下几种可能是要被排除的：

1. 开头不是1的直接排除 

2. 其中含有不是1或4的数字直接排除

3. 有连续3个4直接排除

那么我们只要在代码中特判就可以了，代码如下：

[本人AC证明](https://www.luogu.com.cn/record/31206662)

```cpp
#include<bits/stdc++.h>
#include <iostream>
using namespace std;
string s;
int l,lianxu=0;
int main() {
	ios::sync_with_stdio(0);
	cin>>s;//输入 
	l=s.length();
	if(s[0]!='1'){//开头不是1的直接排除 
		cout<<"NO"<<endl;
		return 0;
	}
	for(int i=0;i<l;i++){
		if(s[i]!='1'&&s[i]!='4'){//不是1或4的数直接排除 
			cout<<"NO"<<endl;
			return 0;
		}
		if(s[i]=='4'){//连续3个4直接排除 
			lianxu++;
		}else{
			lianxu=0;
		}
		if(lianxu==3){
			cout<<"NO"<<endl;
			return 0;
		}
	}
	cout<<"YES"<<endl;//没有被排除的话输出YES 
	return 0;
}
```
感谢观看，请勿抄袭

---

## 作者：PosVII (赞：0)

**前言**

------------

此题巨简单，方法很多。

**暴力搜索**

------------

数据仅有 $9$ 位，纯纯的搜索啊，可以把这个数拆分到数组里，然后每次看末尾是否有 $1$、$14$、$144$ 对于每一种可行的方案搜索即可。

**进阶方法**

------------

我们会发现，$1$、$14$、$144$ 这三个数串是唯一的，即对于某个数串，它后面最多可以接上这三个数串中的一种，当一种数串也接不上时即此数串不能用 $1$、$14$、$144$ 拼出来，那么只需要打循环逐步判断即可。

**code**

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int n; 
int main() {
	cin>>n;
	while(n!=0) {
		if(n%10==1) n/=10;
		else if(n%100==14) n/=100;
		else if(n%1000==144) n/=1000;
		else {
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";
	return 0;
}
```

---

## 作者：梦游的小雪球 (赞：0)

### 梦雪的思路：
- #### 由“魔数由1,14,114组成”我们可以知道：

1. 含有**除“1”，“4”以外**的数字的数不是魔数
```
if(c[i]!='1'&&c[i]!='4'){
	cout<<"NO"<<endl;
	return 0;
}
```

2.含有**3个或3个以上**“4”**相连**的数不是魔数
```
if(c[i]=='4'&&c[i-1]!='1'&&c[i-2]!='1'){
	cout<<"NO"<<endl;
	return 0;
}
```

3.以上问题都没有的即魔数

## AC代码

```
#include<bits/stdc++.h>
using namespace std;
char c[100000002];
int main(){
	cin>>c;
	for(int i=0;i<strlen(c);i++){
		if(c[i]!='1'&&c[i]!='4'){
			cout<<"NO"<<endl;
			return 0;
		}//思路1
		if(c[i]=='4'&&c[i-1]!='1'&&c[i-2]!='1'){
			cout<<"NO"<<endl;
			return 0;
		}//思路2
	}
	cout<<"YES"<<endl;//思路3（因为如果数符合思路1,2程序在中途就会停止，所以能运行至此的一定是魔数）
	return 0;
}
```


---

## 作者：Novice233 (赞：0)

>其实可以把这道题看做字符串匹配问题

>输入的数字就是目标字符串

>而1,14,144就是用来填充的字符串

>每次填字符串时 用substr取子串 然后往里面填充就行了

>~~附上一份智障代码~~

```cpp
#include<bits/stdc++.h>
using namespace std;
string names[5],T;
int f[10005]; 
int main(){
   	names[0]="1";
	names[1]="14";
	names[2]="144";
	string T;
	cin>>T;
	int n=T.size();
	for(int i=1;i<=n;i++){
		f[i]=f[i-1]; 
		for(int j=0;j<3;j++){
			int len=names[j].size();
			if(len<=i&&T.substr(i-len,len)==names[j])
				f[i]=max(f[i],f[i-len]+len);
		}
	}
	if(n==f[n]) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	return 0;
}
```


---

## 作者：sysu_yzc (赞：0)

## 思路
如果首位不为$1$，直接输出$NO$

如果该数中有非$1$或$4$的数码，直接输出$NO$

如果连续出现三个$4$，也直接输出$NO$

否则输出$YES$
## 上代码
```
#include<iostream>
using namespace std;
int main(){
	int t=0;
	char c;
	cin>>c;
	if(c!='1'){
		cout<<"NO";
		return 0;
	}
	while(cin>>c){
		if(c!='1'&&c!='4'){
			cout<<"NO";
			return 0;
		}
		if(c=='1') t=0;
		if(c=='4') t++;
		if(t==3){
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";
	return 0;
}
```

---

## 作者：tryrtj (赞：0)

这一题还是蛮水的，思路也很简单，首先，这个数字只能由1，4组成，只要遇见其他数字直接可以return 0，其次，第一个数字只能为1，毕竟1，14，144都是由1开头的，接下来就是核心思路了

我们可以很容易地发现，如果连续出现n个1，则一定是由n-1个'1'和1个"14"或"144"组成，在任何条件下都成立，但是，如果出现了n个'4'，那么就有限制，因为最多含4的144也只能有2个4，然后必定以1断开，所以这个字符串中的连续的'4'的个数不能超过2，于是程序就很简单了。

```
#include<iostream>
#include<string>
using namespace std;
int main(){
	string s;
	cin>>s;//读入字符串
	int zong=0;
	if(s[0]!='1'){//判断第一个字符是否为'1'
		cout<<"NO"<<endl;
		return 0;
	}
	for(int i=0;i<s.length();i++){
		if((s[i]-'0')!=1&&(s[i]-'0')!=4){
			cout<<"NO"<<endl;//如果不是1或4，直接结束
			return 0;
		}
		if(s[i]=='4'){
			zong++;//统计连续的4的个数
		}
		if(s[i]=='1'){
			zong=0;//清空
		}
		if(zong>2){
			cout<<"NO"<<endl;//判断连续4的个数是否大于2个
			return 0;
		}
	}
	cout<<"YES"<<endl;//输出结果
	return 0;
}
```

---

