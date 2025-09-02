# (iwi)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/utpc2011/tasks/utpc2011_2



# 题解

## 作者：什么叫中二呀 (赞：12)

## 其实这题并不难~~，只是坑多~~……

我被坑了三次，现在我来讲述一下我的经历。

### 第一次代码：
***
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[10]; 
int l,s;
int main()
{
    gets(a);//输入
    l=strlen(a);//计算长度
    s=l/2;//最多需要更改的字符数
    for(int i=0;i<l/2;i++)
        if(a[i]+a[l-i-1]==')'+'('||a[i]==a[l-i-1])
            s--;//对于上面的判断
            	//如果它们都是括号，则不更改；
                //如果它们都是'i'或'w'，也不更改
    printf("%d\n",s);//输出
    return 0;
}
```
****
结果：AC13个点，WA9个点

为什么呢？

如果是“))))))))))”这样的，就会认为它们是相等的，所以不更改。

可实际上是要改的……

第二次提交：
*****
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[10]; 
int l,s;
bool c(char x,char y)
{
    if(x=='i'&&y=='i')return 1;
    if(x=='w'&&y=='w')return 1;
    if(x=='('&&y==')')return 1;
    if(x==')'&&y=='(')return 1;
    return 0;
}
int main()
{
    gets(a);
    l=strlen(a);
    s=l/2;
    for(int i=0;i<l/2;i++)//重点
        if(c(a[i],a[l-1-i]))
            s--;
    printf("%d\n",s);
    return 0;
}
```
****
结果:AC20个点，WA2个点

大概是没考虑括号不能放中间。

比如“iii(iii”,一看就不对称，但是程序输出0……

究其原因，是因为“重点”处已经无视了中间字符。

所以我们也要把中间字符判断一下

AC代码
***
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[20]; 
int l,s;
bool c(char x,char y)
{
    if(x=='i'&&y=='i')return 1;
    if(x=='w'&&y=='w')return 1;
    if(x=='('&&y==')')return 1;
    if(x==')'&&y=='(')return 1;
    return 0;
}
int main()
{
    gets(a);
    l=strlen(a);
    s=(l+1)/2;
    for(int i=0;i<(l+1)/2;i++)
        if(c(a[i],a[l-1-i]))
            s--;
    printf("%d\n",s);
    return 0;
}
```
***
## 最后，还是上面那句话：~~其实这题并不难，只是坑多……~~

---

## 作者：Zachary_Cloud (赞：6)

这题其实可以用~~玄学~~的方式水过去（（

## $Code$ $\&$ $Sol$

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int k;
char check(char b) { //取反操作
	if(b=='(') return ')';
	else if(b==')') return '(';
	else return b;
}
int main() {
	cin>>s; //如果你读入字符串，最好用cin读入，不然可能会出现一些玄学错误
	for (int i=0; i<s.size(); i++) //依次扫过每一个字符
		if (s[i]!=check(s[s.size()-i-1])) k++; //如果它不是字符串另一侧的反向 k++
	cout<<(k+1)/2; //输出k的1/2就可以了
	return 0;
}
```


---

## 作者：BZHZS (赞：3)

```cpp
#include<bits/stdc++.h>
using namespace std;

char a[10];
int sum;

int main()
{
	scanf("%s",a);
	int n=strlen(a);//读取字符长度 
	sum=(n+1)/2;//先认为所有的字符都要修改
		    //因为字符串有可能是奇数,所以要先加上1再计算 
				
	//i和j分别从字符串两端开始判断是否对称 
	//当i>j时,将开始重复计算,所以要在此之前结束循环 
	for(int i=0,j=n-1;i<=j;i++,j--)
	{
		if(a[i]==a[j])
			sum--;
		//由题意可知,只会输入对称字母和括号,所以只要字母一样就不用修改
		//但是这会认为((和))不用修改,()和)(需要修改 
		//所以下面需要对括号特殊判断
		//当字符串为奇数时,最后一次循环i==j
		//即此时a[i]和a[j]都是字符串最中间的字符 
		//此时a[i]和a[j]只要是'('或')',就还需要再修改一次 
		//所以第31行和33行的if语句恰好可以解决此问题 
		if(a[i]=='('&&a[j]==')')
			sum--;
		if(a[i]==')'&&a[j]=='(')
			sum--;
		if(a[i]==')'&&a[j]==')')//31行 
			sum++;
		if(a[i]=='('&&a[j]=='(')//33行 
			sum++;
	}

	cout<<sum<<endl;//记得换行(日本题大多都要换行) 

	return 0;
}
```


---

## 作者：hellhell (赞：2)

### 题目描述

输入一个字符串，问最少几次更改能让字符串变为对称。

字符串只包括 '$i$ ', '$w$ ', '$($ ', '$)$ '

定义对称如下：

- 空串
- 一个字母 '$i$ '
- 一个字母 '$w$ '
- 在两个字母中包含一个对称的字符串
- 在括号中包含一个对称的字符串 

### 思路分析

要想更改最少，要保证原来已经匹配好的不被修改，只修改没有匹配上的。

比如字符串 $(iiw)$ 两边的括号和中间的 $i$ 已经是满足要求的了，只需要更改左边的 $i$ 或者 右边的 $w$ 即可。

顺着这个思路，我们把整个字符串从中间分成两个子串，两个子串从中间往两边对位匹配，求这两个字串的最长公共连续子序列的长度。

#### 注意

这里在匹配两个字串的时候，对于括号，如果两个子串的括号相等，匹配失败，如果不等匹配成功。

对于字母正常匹配即可，相等匹配成功，否则失败。

（如果光看文字理解不了可以看一看代码里的 $check$ 函数）

求得最长公共连续子序列的长度后，用原本字符串的一半的长度减去序列长度，即为所求。

特别的，如果输入的字符串长度为奇数，还要看一下中间的字符。如果中间的字符是括号，那答案要+1，因为没有另一个括号去跟它匹配。

如果是字母，答案不变。

### 代码实现

```c++
#include<bits/stdc++.h>

using namespace std;

string s;
int ans;
int dp[1005];

bool check(char x,char y){
    if((x==y && (x=='i' || x=='w')) || (x=='(' && y==')') || (x==')' && y=='('))
        return true;
    return false;
}

int main(){
    cin>>s;
    int len=s.length();
    memset(dp,0,sizeof(dp));
    if(len==1){
        cout<<0<<endl;
        return 0;
    }
    if(len%2==0){
        for(int i=len/2,j=len/2+1;i>=1 && j<=len;i--,j++){
            if(check(s[i-1],s[j-1]))
                dp[i]=dp[i+1]+1;
            else
                dp[i]=dp[i+1];
        }
        ans=len/2-dp[1];
        cout<<ans<<endl;
        return 0;
    }
    else{
        for(int i=len/2,j=len/2+2;i>=1 && j<=len;i--,j++){
            if(check(s[i-1],s[j-1]))
                dp[i]=dp[i+1]+1;
            else
                dp[i]=dp[i+1];
        }
        ans=len/2-dp[1];
        if(s[len/2]=='i' || s[len/2]=='w'){
            cout<<ans<<endl;
            return 0;
        }
        else{
            ans++;
            cout<<ans<<endl;
            return 0;
        }
    }
    return 0;
}

```





---

## 作者：_caiji_ (赞：1)

- **[题目](https://www.luogu.com.cn/problem/AT26)意思**

给你一个字符串，其中只包含 `i` `w` `(` `)` 四个字符，求**最少**需要几次**更改**操作才能把他变成一个**回文**的字符串。

- **做法**

1. 输入

首先把字符串读进来。这一步没什么好说的， `cin` `scanf` `getline` 等等都行。记得写上 `string` 的头文件。
```cpp
#include<iostream>
#include<string>
using namespace std;
int main(){
    string a;
    cin>>a;//cin是string最好的朋友
  
    return 0;
}
```
2. 循环方法

其它题解的循环相信你们都看过了，现在我给你们介绍一种更简单的：
```cpp
for(int i=0,j=a.size()-1;i<=j;i++,j--){
  
}
```
可能你们第一眼没看懂，没关系，我们来逐个分析：
-  `int i=0,j=a.size()-1` ，这是定义两个指针（准确来说是下标），一个指向字符串开头的字符，一个指向结尾的字符。
-  `i<=j` ，当这两个指针还没相遇（到达中点）时，继续循环。注意 `<=` 。
-  `i++,j--` ，一个指针往前进，一个指针向后退。

这样写，就好判断回文了，直接拿 `a[i]` 和 `a[j]` 比较，至少会好理解一点。

3. 判断回文

定义一个 `check` 函数，如果回文返回 `true` ，否则返回 `false` 。暴力枚举 $4$ 种情况代码会有点长，其实可以精简一点， $2$ 个`if`就够了，具体代码实现：
```cpp
bool check(char a,char b){
    if(a==b&&a>='i') return 1;
    //如果a==b，那无非就4种情况：两个i w ( )。我们可以利用一下ASCLL码的特性，由于iw的ASCLL码比()大，所以直接这样判断就行了
    if(a+b=='('+')') return 1;
    //a+b在这里并不是拼接，而是2个字符的ASCLL码相加。如果a+b=1对括号相加，那它们也是回文的
    return 0;//两种情况都匹配不上，肯定不是回文
}
```
4. 计数

怎么计数，大家都很清楚吧。就是要注意，当这 $2$ 个字符不是回文时才 `ans++` ，不要反了。
```cpp
int ans=0;
for(int i=0,j=a.size()-1;i<=j;i++,j--){
    if(!check(a[i],a[j])) ans++;
    // ^ 这个符号不要漏写
}
```
5. 输出

注意要看清楚题目来源，岛！国！题！要！换！行！
```cpp
cout<<ans<<endl;
```
- **完整代码**

[$\color{white}\colorbox{green}{AC记录}$](https://www.luogu.com.cn/record/43031919)

莫抄袭，UNAC100，空悲切！
```cpp
#include<iostream>
#include<string>
using namespace std;
bool check(char a,char b){
    if(a==b&&a>='i') return 1;
    if(a+b=='('+')') return 1;
    return 0;
}
int main(){
    string a;
    cin>>a;
    int ans=0;
    for(int i=0,j=a.size()-1;i<=j;i++,j--){
        if(!check(a[i],a[j])) ans++;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：_121017_ (赞：0)

这道题其实特别简单，唯二两个坑点就是当字符串长度为奇数时，中间的字符不能是括号，因为这样就不可能匹配了。

其实我们仔细想一下，我们想让字符串可以匹配的话只要把它拆成左右两半，再把其中任意一半翻转过来，只要记录有多少个不匹配的位置就行了。

最后我们在特判一下当字符串为奇数是中间的字符是否是括号就行了。

最后第二个坑点就是输出别忘了换行，不然会 $\color{red}\text{WA}$ 的很惨（别问我为什么知道）。

此题结束。

# code
```cpp
#include<bits/stdc++.h>
using namespace std;
string c;
int cnt;
bool check(int a,int b){
	if(a==b&&(a=='w'||a=='i')){
		return 1;
	}
	if(a==')'&&b=='('){
		return 1;
	}
	if(a=='('&&b==')'){
		return 1;
	}
	return 0;
}
int main(){
	cin>>c;
	for(int i=1;i<=c.size()/2;i++){
		if(!check(c[i-1],c[c.size()-i])){
			cnt++;
		}
	}
	if(c.size()%2&&(c[(c.size()+1)/2-1]=='('||c[(c.size()+1)/2-1]==')')){
		cnt++;
	}
	cout<<cnt<<endl;
	return 0;
}

```


---

## 作者：AdGats (赞：0)

刚刚读题的我天真的以为这是一道评分偏低的普通难题 ~~（我天真的打了段dp最长公共子序列想求加几个字符）~~

没想到~~这么水~~这么适合在座的各位新人（大佬就当没看见好了）


--------------------这里是神圣而不可侵犯的分界线 --------------------

那我们言归正传（强行正经），我先解释一下很~~看不懂~~言简意赅的题意：说白了很简单，就是给你一个只有iwi和()的字符串，然后叫你求一下改几个字符就变成了回文串（这里注意以中间为轴的两个字符不能均为同一侧的括号，如‘（’和‘（’在这两个位置不是回文串，必须成对出现！）

读懂了题，这题就很~~水~~容易浮现出思路了：
	
    1.将以中间为轴对称的两个字符作比较，看看该位置的两个字符是不是一样，一样则不动，不一样则改变，sum++
    2.输出？这么简单woc我还发啥题解（狗头）
    
下面是~~高清无码~~ ac代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string iwi;	//定义字符串，不限长度
bool flag;
int len,sum;
int main(){
	cin>>iwi;//读入字符串，string类型可以直接cin
	len=iwi.size();//得到字符串长度
	for(int i=0;i<=(len-1)/2;i++){ //这个终止条件很重要，我第一次也不小心写成li<=len/2,我错的这个单单适用于奇数情况，偶数会多一个
		flag=false; //预设状态是要改
		if(iwi[i]==iwi[len-i-1]&&iwi[i]=='i')	flag=true;	//看看是不是对称，这两个是看是不是i或w的回文，是则改为不需改的状态；顺便说下有一条题解错就错在他没有判断相等是不是不是括号，这样ta用或的话就会bug
		else if(iwi[i]==iwi[len-i-1]&&iwi[i]=='w')	flag=true;
		else if(iwi[i]=='('&&iwi[len-i-1]==')')	flag=true;//这两个是判断是否是成对的括号，后一个也是，只不过是反过来而已
		else if(iwi[i]==')'&&iwi[len-i-1]=='(')	flag=true;
		if(!flag)	sum++;//如果不回文，动一下其中一个，不考虑全改，因为字符均不可能不在i，w和括号之间
	}
	cout<<sum<<"\n";//漂亮的输出有换行才完美
	return 0;
}

```
怎样，简单吗，点个赞，爱你哦（狗头保命）

---

## 作者：_Imaginary_ (赞：0)

[AT26](https://www.luogu.com.cn/problem/AT26)

这道题要求最少的修改次数使最终变成回文串。

长度为 $n$ 的回文串S有一个显然的性质：$S_i=S_{n-i+1}$。

所以我们可以把一个串分成 $n/2$ 部分，每部分包含两个关于中心对称的字符。

考虑其中的每一个部分，这些情况下无需修改：

- `i i`

- `w w`
- `( )`
- `) (`

所以，大体思路就是枚举每个部分，进行统计。

## 细节

### 1. 中间

单个的括号不平衡，要特判。

### 2. 时间

为了保证不会超时，不要将`i<strlen(s)` 之类的语句放在循环中。建议的写法：

```cpp
int siz=strlen(s);
for(int i=0;i<siz;i++)
```

---

## 作者：lndjy (赞：0)

我来发一个string的题解

思路：答案初始化为长度的一半，因为全部不对称答案就是长度一半，然后第一个和最后一个比，第二个和倒数第二个比，如果已经对称，就不用改了，答案减一，以此类推。

注意坑点，判断中间字符是否对称，比如说中间字符只有一个）就需要改。

代码：
```cpp
#include<iostream>
#include<cstring>
using namespace std;
bool check(char x,char y)//判断是否对称
{
	if(x=='i'&&y=='i')return 1;
    if(x=='w'&&y=='w')return 1;
    if(x=='('&&y==')')return 1;
    if(x==')'&&y=='(')return 1;
    return 0;
}
int main()
{
	string s;
	cin>>s;
	int l=s.size();
	int ans=(l+1)/2;
	for(int i=0;i<(l+1)/2;i++)//坑点，要判断中间字符
	{
		if(check(s[i],s[l-1-i]))//对称答案减一
		ans--;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：stry (赞：0)

### ~~BIG水题~~

就是坑有点多

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[55]; 
int l,s;
bool c(char x,char y)
{
    if(x=='i'&&y=='i')return 1;
    if(x=='w'&&y=='w')return 1;
    if(x=='('&&y==')')return 1;
    if(x==')'&&y=='(')return 1;
    return 0;
}
int main()
{
    gets(a);
    l=strlen(a);
    s=(l+1)/2;
    for(int i=0;i<(l+1)/2;i++)if(c(a[i],a[l-1-i]))s--;
    cout<<s;
    return 0;
}
```

本蒟蒻还没过过一篇题解呢，求过！！！

---

